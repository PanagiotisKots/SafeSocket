<h2>SafeSocket++</h2> 
<br>

- is a console-based program (for now), fully developed in C++ for networking and user communication. It is designed to facilitate communication between computers 
on the same local network using socket technology. It includes a server and client structure, allowing a client to connect to the server and 
enable full communication between two or more computers through a predefined port and IP.

<br>

- The program includes menus in both profiles (server - client), offering options such as -help, single server-client connection / multiple connections, 
and a variety of other functions. Currently, it is in version 0.1, and some features are still pending. Further improvements and new versions are 
expected to be made available on the program's GitHub repository with its first official release.

<br>


- Structurally, it is a communication and networking program designed to be easy to use and extend. It is organized into various modules that serve different functions and communicate 
with each other to ensure the proper operation of the application. Using object-oriented programming (OOP), each module consists of various classes and objects that offer specific 
functionalities and capabilities. This structure allows for code reuse and easy management and maintenance of the program. Additionally, the use of OOP provides the capability for the 
program's scalability, as new modules and features can be added easily without affecting the functionality of the existing ones.

<br>


- The object-oriented approach contributes to better organization and code management, making SafeSocket++ a flexible 
and efficient OPEN-SOURCE 🐧 tool for communication and networking in local private networks.


<br><br>


<h2>Compilation and Execution</h2>

<br>

- The program is designed to be compatible with most Windows operating systems commonly used in the market, both older and future systems. On our end, the program has been tested and delivered through
the DEV-C/C++ development environment, adding the command -lws2_32 to the linker, which is necessary for using sockets on Windows.

<br>

- After this setup, proceed to compile the program using the 'rebuild all' option. Once the executable files for the server and the client are created (preferably on separate machines within the same network),
first run the server, and then, through the user options, execute the client executable file.


 🛑 Note The server must start first to listen for incoming connections

<br>

- It is important to note that this specific version is not cross-platform and cannot be executed on Linux or macOS operating systems (for now).
<br>

- Similarly, the program can be compiled in a similar development environment with an installed compiler, as well as in a custom assembly environment, provided it is compiled with commands such as gcc -o server.exe ........ -lws2_32.
Additionally, any Integrated Development Environment (IDE) with a C++ compiler, such as Visual Studio, Code::Blocks, CLion, Xcode, and many others, can be used. Just ensure the -lws2_32 command is added to the linker's settings.
<br>

- After compiling the source code and creating the executable files for the server and the client, you can run the server first and then the client, using the appropriate program options.

<br><br>










<h2>Usage</h2>

<h3>Communication between computers on a local network </h3>

<br>

- Communication between computers on a local network (LAN) can be easily achieved using our application,
  offering a variety of features and functionalities that make interaction between users simple and efficient.

- One of its key features is real-time message exchange. Users can send and receive messages instantly, without delays, facilitating collaboration and communication
  in a work or educational environment. Whether it’s a quick question or an extensive discussion, our application supports it seamlessly.

- The ease of use of our application makes it ideal for any organization or team looking to improve communication in private networks.
  With a user-friendly interface and simple installation and usage procedures, even less experienced users can take full advantage of its capabilities.

- Overall, SafeSocket++ provides a comprehensive solution for communication and collaboration on a local network, offering all the necessary tools for real-time message exchange.












<br><br>


<h2>SafeSocket++ v0.1 - First Official pre Release</h2>

<br>

 We are excited to announce the first official pre release version of SafeSocket++.
This release includes both server and client executables, allowing seamless communication between  computers on the same LAN.

<h3>Features</h3>


    Real-time message exchange between users
    Easy setup and usage
    User-friendly interface
    Single server-client connection or multiple connections
    Comprehensive menus with various options

<h3>Installation and Usage</h3>


    Download the server.exe and client.exe files from the release assets below.
    Place the executables on separate machines within the same network.
    Run server.exe on one machine.
    Run client.exe on another machine and follow the user options to connect to the server.

<h3>System Requirements</h3>


    Compatible with Windows operating systems
    Requires -lws2_32 linker command for socket functionality
    if you choose to compile it yourself

<h3>Notes</h3>


    This version is not cross-platform and currently does not support Linux or macOS.
    Further improvements and new features will be available in upcoming releases.


- We look forward to your feedback and contributions. For more details and to report any issues,
  please feel free to add to the repo👾

- Download the executables from the assets below and start communicating efficiently within your
  local network🌐

- Thank you for using SafeSocket++🤝














<h2>Overview</h2>


![Image Description](https://github.com/PanagiotisKots/SafeSocket/blob/main/V%20-%200.1/img/img1.jpg)
<img src="https://github.com/PanagiotisKots/SafeSocket/blob/main/V%20-%200.1/img/img2.jpg" alt="Image Description" width="410" height="350">  <img src="https://github.com/PanagiotisKots/SafeSocket/blob/main/V%20-%200.1/img/img3.jpg" alt="Image Description" width="410" height="350">




<h2>Demo Video</h2>


Watch this video to see SafeSocket++ in action:

[![Click to watch video](https://upload.wikimedia.org/wikipedia/commons/6/6a/Youtube_Music_icon.svg)](https://youtu.be/J8wKHlkof-0)










