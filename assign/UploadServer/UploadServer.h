#ifndef UPLOAD_SERVER_H
#define UPLOAD_SERVER_H

#include "UploadServerThread.h"

class UploadServer {
public:
    UploadServer(const std::string& address, int port, const std::string& saveDirectory);
    ~UploadServer();
    void start();

private:
    int serverSocket;
    std::string saveDirectory;
};

#endif // UPLOAD_SERVER_H
