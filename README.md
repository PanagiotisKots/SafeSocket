<h2>SafeSocket++</h2> 
<br>

- is a console-based program (for now), fully developed in C++ for networking and user communication. It is designed to facilitate communication between computers 
on the same local network using socket technology. It includes a server and client structure, allowing a client to connect to the server and 
enable full communication between two or more computers through a predefined port and IP.

<br><br>

- The program includes menus in both profiles (server - client), offering options such as -help, single server-client connection / multiple connections, 
and a variety of other functions. Currently, it is in version 1.0, and some features are still pending. Further improvements and new versions are 
expected to be made available on the program's GitHub repository with its first official release.


<br><br>


- Structurally, it is a communication and networking program designed to be easy to use and extend. It is organized into various modules that serve different functions and communicate 
with each other to ensure the proper operation of the application. Using object-oriented programming (OOP), each module consists of various classes and objects that offer specific 
functionalities and capabilities. This structure allows for code reuse and easy management and maintenance of the program. Additionally, the use of OOP provides the capability for the 
program's scalability, as new modules and features can be added easily without affecting the functionality of the existing ones.

<br><br>


- The object-oriented approach contributes to better organization and code management, making SafeSocket++ a flexible 
and efficient OPEN-SOURCE 🐧 tool for communication and networking in local private networks.


<br><br><br><br>


<h2>Compilation and Execution</h2>


- The program is designed to be compatible with most Windows operating systems commonly used in the market, both older and future systems. On our end, the program has been tested and delivered through
the DEV-C/C++ development environment, adding the command -lws2_32 to the linker, which is necessary for using sockets on Windows.

- After this setup, proceed to compile the program using the 'rebuild all' option. Once the executable files for the server and the client are created (preferably on separate machines within the same network),
first run the server, and then, through the user options, execute the client executable file.

- It is important to note that this specific version is not cross-platform and cannot be executed on Linux or macOS operating systems (for now).

- Similarly, the program can be compiled in a similar development environment with an installed compiler, as well as in a custom assembly environment, provided it is compiled with commands such as gcc -o server.exe ........ -lws2_32.
Additionally, any Integrated Development Environment (IDE) with a C++ compiler, such as Visual Studio, Code::Blocks, CLion, Xcode, and many others, can be used. Just ensure the -lws2_32 command is added to the linker's settings.

- After compiling the source code and creating the executable files for the server and the client, you can run the server first and then the client, using the appropriate program options.









