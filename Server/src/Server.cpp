#include "Server.h"

#include <thread>
#include <iostream>

Server::Server() = default;

Server::~Server() = default;

void Server::Start() {

    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "                                                    " << std::endl;
    std::cout << "                       Server                       " << std::endl;
    std::cout << "                                                    " << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << std::endl;

    WSADATA data;

    if (WSAStartup(MAKEWORD(2, 2), &data)) {
        std::cout << "Error : WSADATA Failed :(" << std::endl;
        return;
    }


    //                           IP version ,       TCP IP    , Port
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == INVALID_SOCKET) {
        std::cout << "Error : SOCKET Failed :(" << std::endl;
        WSACleanup();
        return;
    }


    // Create address structure
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;                 // TCP IP
    serverAddress.sin_port = htons(8080);     // Port


    // Bind socket
    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cout << "Error : Bind Failed :(" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }


    // Listen
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cout << "Error : Listen Failed :(" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }


    std::cout << "Server has started to listening on port (8080) ..." << std::endl;

    std::vector<SOCKET> clients;

    while (true) {

        // Accept

        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);

        if (clientSocket == INVALID_SOCKET) {
            std::cout << "Error : Accept Failed :(" << std::endl;
            std::cout << "Error : Invalid client socket" << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return;
        }

        clients.push_back(clientSocket);

        std::thread t(InteractWithClient, clientSocket, std::ref(clients));

        t.detach();

        if (clients.size() == 10) {
            break;
        }
    }

    closesocket(serverSocket);
    WSACleanup();
}

void Server::InteractWithClient(SOCKET clientSocket, std::vector<SOCKET> &clients) {

    std::cout << "Connection established with client." << std::endl;

    // Time

    Time time;

    // Send / Receive

    char buffer[1024];

    while (true) {

        int bytesReceive = recv(clientSocket, buffer, sizeof(buffer), 0);

        std::string message (buffer, bytesReceive);

        Time::getTime();

        std::cout << " - " << message << std::endl;

        for (int i = 0; i < clients.size(); ++i) {
            if (clients.at(i) != clientSocket) {
                send(clients.at(i), message.c_str(), message.length(), 0);
            }
        }


        if (message == "H") {
            break;
        }
    }

    closesocket(clientSocket);
    WSACleanup();
}
