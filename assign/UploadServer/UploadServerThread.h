#ifndef UPLOADSERVERTHREAD_H
#define UPLOADSERVERTHREAD_H

#include <thread>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include "HttpServletRequest.h"
#include "HttpServletResponse.h"
#include "UploadServlet.h"

class UploadServerThread {
    int clientSocket;
    std::thread thread;

public:
    UploadServerThread(int socket);
    void start();
    void run();
};

#endif // UPLOADSERVERTHREAD_H
