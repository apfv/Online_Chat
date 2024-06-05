#include "Client.h"

#include <thread>
#include <iostream>
#include <winsock2.h>


Client::Client() : clientSocket(INVALID_SOCKET) {}

Client::~Client() {

    if (clientSocket != INVALID_SOCKET) {
        closesocket(clientSocket);
        WSACleanup();
    }
}

void Client::Start() {

    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "                                                    " << std::endl;
    std::cout << "                       Client                       " << std::endl;
    std::cout << "                                                    " << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << std::endl;


    WSADATA data;
    if (WSAStartup(MAKEWORD(2, 2), &data)) {
        std::cout << "Error : WSADATA Failed :(" << std::endl;
        return;
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Error : SOCKET Failed :(" << std::endl;
        WSACleanup();
        return;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cout << "Error : Connect To Server Failed :(" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return;
    }

    std::cout << "Connected to the server." << std::endl;

    std::cout << "Enter your chat name: ";
    std::getline(std::cin, name);
    std::cout << "Start your chat " << name  << ", enjoy :)" << std::endl;

    std::thread senderThread(&Client::SenderMessage, this);
    std::thread receiverThread(&Client::ReceiverMessage, this);

    senderThread.join();
    receiverThread.join();
}

void Client::SenderMessage() {

    std::string message;

    while (true) {

        std::getline(std::cin, message);

        std::string msg = "[ " + name + "] : " + message;

        int length = send(clientSocket, msg.c_str(), msg.length(), 0);

        if (length == SOCKET_ERROR) {
            std::cout << "Error : Send Failed :(" << std::endl;
            break;
        }
    }
}

void Client::ReceiverMessage() const {

    char buffer[2048];

    while (true) {

        int length = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (length <= 0) {
            std::cout << "Error : Receive Failed :(" << std::endl;
            break;
        } else {

            std::string message(buffer, length);

            Time time;
            Time::getTime();

            std::cout << " " << message << std::endl;
        }
    }
}
