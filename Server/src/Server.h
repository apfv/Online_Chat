#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "Time.h"

#include <vector>
#include <winsock2.h>

class Server {
public:
    Server();
    ~Server();

    void Start();

private:
    static void InteractWithClient(SOCKET clientSocket, std::vector<SOCKET> &clients);
};

#endif //SERVER_SERVER_H
