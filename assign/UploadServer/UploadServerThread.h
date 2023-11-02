#ifndef UPLOAD_SERVER_THREAD_H
#define UPLOAD_SERVER_THREAD_H

#include <pthread.h>
#include <string>
#include "UploadServlet.h"
#include "HttpServletRequest.h"
#include "HttpServletResponse.h"

class UploadServerThread {
public:
    UploadServerThread(int clientSocket, const std::string& saveDirectory);
    ~UploadServerThread();

    static void* run(void* args);

private:
    int clientSocket;
    UploadServlet uploadServlet;

    void handleClientConnection();
//void processPOST(HttpServletRequest& request);
};

#endif // UPLOAD_SERVER_THREAD_H
