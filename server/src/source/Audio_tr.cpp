#include <winsock2.h>
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <thread>   // For threading support

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")

#define SAMPLE_RATE 44100
#define SAMPLE_SIZE 2       // 16-bit PCM, 2 bytes per sample
#define NUM_CHANNELS 1      // Mono
#define BUFFER_SIZE (SAMPLE_RATE * SAMPLE_SIZE / 2)  // Half-second buffer

// Function to receive audio from the client and play it
void receiveAudio(SOCKET socket) {
    // Initialize audio playback
    WAVEFORMATEX format;
    format.wFormatTag = WAVE_FORMAT_PCM;
    format.nChannels = NUM_CHANNELS;
    format.nSamplesPerSec = SAMPLE_RATE;
    format.wBitsPerSample = 8 * SAMPLE_SIZE;
    format.nBlockAlign = NUM_CHANNELS * SAMPLE_SIZE;
    format.nAvgBytesPerSec = SAMPLE_RATE * NUM_CHANNELS * SAMPLE_SIZE;
    format.cbSize = 0;

    HWAVEOUT hWaveOut;
    MMRESULT result = waveOutOpen(&hWaveOut, WAVE_MAPPER, &format, 0, 0, WAVE_FORMAT_DIRECT);
    if (result != MMSYSERR_NOERROR) {
        std::cerr << "Failed to open audio device\n";
        return;
    }

    // Buffer for receiving audio samples
    char buffer[BUFFER_SIZE];

    // Receive and play audio
    while (true) {
        int bytesReceived = recv(socket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived > 0) {
            WAVEHDR waveHeader;
            waveHeader.lpData = buffer;
            waveHeader.dwBufferLength = bytesReceived;
            waveHeader.dwFlags = 0;
            waveHeader.dwLoops = 0;
            waveOutPrepareHeader(hWaveOut, &waveHeader, sizeof(WAVEHDR));
            waveOutWrite(hWaveOut, &waveHeader, sizeof(WAVEHDR));
        }
    }

    // Clean up
    waveOutClose(hWaveOut);
}

// Function to send live audio from server to client
void sendAudio(SOCKET socket) {
    // Initialize audio recording
    WAVEFORMATEX format;
    format.wFormatTag = WAVE_FORMAT_PCM;
    format.nChannels = NUM_CHANNELS;
    format.nSamplesPerSec = SAMPLE_RATE;
    format.wBitsPerSample = 8 * SAMPLE_SIZE;
    format.nBlockAlign = NUM_CHANNELS * SAMPLE_SIZE;
    format.nAvgBytesPerSec = SAMPLE_RATE * NUM_CHANNELS * SAMPLE_SIZE;
    format.cbSize = 0;

    HWAVEIN hWaveIn;
    MMRESULT result = waveInOpen(&hWaveIn, WAVE_MAPPER, &format, 0, 0, WAVE_FORMAT_DIRECT);
    if (result != MMSYSERR_NOERROR) {
        std::cerr << "Failed to open audio input device\n";
        return;
    }

    // Buffer for sending audio samples
    char buffer[BUFFER_SIZE];

    // Prepare and start recording
    WAVEHDR waveHeader;
    waveHeader.lpData = buffer;
    waveHeader.dwBufferLength = BUFFER_SIZE;
    waveHeader.dwFlags = 0;
    waveHeader.dwLoops = 0;
    waveInPrepareHeader(hWaveIn, &waveHeader, sizeof(WAVEHDR));
    waveInAddBuffer(hWaveIn, &waveHeader, sizeof(WAVEHDR));
    waveInStart(hWaveIn);

    // Send recorded audio to client
    while (true) {
        // Wait for recording to complete
        while (!(waveHeader.dwFlags & WHDR_DONE)) {
            Sleep(100);  // Adjust as needed
        }

        // Send recorded audio buffer to client
        send(socket, buffer, waveHeader.dwBytesRecorded, 0);

        // Reset and reuse the buffer
        waveInUnprepareHeader(hWaveIn, &waveHeader, sizeof(WAVEHDR));
        waveHeader.dwFlags = 0;
        waveInPrepareHeader(hWaveIn, &waveHeader, sizeof(WAVEHDR));
        waveInAddBuffer(hWaveIn, &waveHeader, sizeof(WAVEHDR));
    }

    // Clean up
    waveInClose(hWaveIn);
}

int mainnnn() {
    // Initialize Winsock
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);
    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        std::cerr << "WSAStartup failed with error: " << err << "\n";
        return 1;
    }

    // Create a socket for communication
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
        WSACleanup();
        return 1;
    }

    // Bind and listen
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);  // Listen on any interface
    serverAddr.sin_port = htons(12345);  // Example port number
    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        std::cerr << "Listen failed\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server listening...\n";

    // Accept a client connection
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    SOCKET clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrSize);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Client connected\n";

    // Start threads for receiving and sending audio
    std::thread receiveThread(receiveAudio, clientSocket);
    std::thread sendThread(sendAudio, clientSocket);

    // Wait for threads to finish (this shouldn't happen normally in this setup)
    receiveThread.join();
    sendThread.join();

    // Cleanup
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}

