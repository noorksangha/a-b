#include "UploadServer.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

UploadServer::UploadServer(const std::string& address, int port, const std::string& saveDirectory)
    : saveDirectory(saveDirectory) {

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
}

UploadServer::~UploadServer() {
    close(serverSocket);
}

void UploadServer::start() {
    listen(serverSocket, 5);

    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);

        if (clientSocket < 0) {
            std::cerr << "Failed to accept client connection" << std::endl;
            continue;
        }

        UploadServerThread* serverThread = new UploadServerThread(clientSocket, saveDirectory);
        pthread_t thread;
        pthread_create(&thread, nullptr, UploadServerThread::run, serverThread);
        pthread_detach(thread);
    }
}
