#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <gdiplus.h>
#include <fstream>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

// Function to get the CLSID of a specified image format
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
    UINT num = 0;
    UINT size = 0;

    GetImageEncodersSize(&num, &size);
    if (size == 0)
        return -1;

    ImageCodecInfo* pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
    if (pImageCodecInfo == NULL)
        return -1;

    GetImageEncoders(num, size, pImageCodecInfo);

    for (UINT j = 0; j < num; ++j) {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;
        }
    }

    free(pImageCodecInfo);
    return -1;
}

void sendScreen(SOCKET clientSocket) {
    // Initialize GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Main loop for capturing and sending screen content
    while (true) {
        // Capture screen
        HDC hScreenDC = GetDC(NULL);
        HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
        int width = GetDeviceCaps(hScreenDC, HORZRES);
        int height = GetDeviceCaps(hScreenDC, VERTRES);
        HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
        HGDIOBJ oldObject = SelectObject(hMemoryDC, hBitmap);
        BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);

        // Convert HBITMAP to JPEG format
        CLSID jpegClsid;
        GetEncoderClsid(L"image/jpeg", &jpegClsid);
        EncoderParameters encoderParams;
        encoderParams.Count = 1;
        encoderParams.Parameter[0].Guid = EncoderQuality;
        encoderParams.Parameter[0].Type = EncoderParameterValueTypeLong;
        encoderParams.Parameter[0].NumberOfValues = 1;
        ULONG quality = 80; // Adjust quality as needed (0-100)
        encoderParams.Parameter[0].Value = &quality;

        // Encode image to JPEG in memory
        IStream* pStream = NULL;
        HRESULT hr = CreateStreamOnHGlobal(NULL, TRUE, &pStream);
        if (hr == S_OK) {
            Bitmap bitmap(hBitmap, NULL);
            bitmap.Save(pStream, &jpegClsid, &encoderParams);
            STATSTG stat;
            LARGE_INTEGER liOffset;
            liOffset.QuadPart = 0;
            pStream->Stat(&stat, STATFLAG_NONAME);
            HGLOBAL hMem = GlobalAlloc(GHND, stat.cbSize.LowPart);
            BYTE* pbyteGlobal = (BYTE*)GlobalLock(hMem);
            pStream->Seek(liOffset, STREAM_SEEK_SET, NULL);
            pStream->Read(pbyteGlobal, stat.cbSize.LowPart, NULL);
            GlobalUnlock(hMem);

            // Send JPEG image data to client
            send(clientSocket, (char*)pbyteGlobal, stat.cbSize.LowPart, 0);

            // Clean up
            GlobalFree(hMem);
            pStream->Release();
        }

        // Clean up
        ReleaseDC(NULL, hScreenDC);
        DeleteDC(hMemoryDC);
        DeleteObject(hBitmap);
        SelectObject(hMemoryDC, oldObject);

        // Sleep for a short interval to control frame rate (adjust as needed)
        Sleep(100);
    }

    // Shutdown GDI+
    GdiplusShutdown(gdiplusToken);
}

int mai() {
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

    // Start sending screen content to client
    sendScreen(clientSocket);

    // Cleanup
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}


