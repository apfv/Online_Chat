#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include "Time.h"

#include <iostream>
#include <winsock2.h>

class Client {
private:
    std::string name;
    SOCKET clientSocket{};

public:
    Client();
    ~Client();

    void Start();

private:
    void SenderMessage();
    void ReceiverMessage() const;
};

#endif //CLIENT_CLIENT_H
