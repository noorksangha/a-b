#include "UploadServerThread.h"
#include <unistd.h>  // for close()
#include <iostream>
#include <sys/socket.h>  // for send()
#include <fstream>  // for ofstream

UploadServerThread::UploadServerThread(int clientSocket, const std::string& saveDirectory)
    : clientSocket(clientSocket), uploadServlet(saveDirectory) {}

UploadServerThread::~UploadServerThread() {
    close(clientSocket);
}

void* UploadServerThread::run(void* args) {
    UploadServerThread* serverThread = static_cast<UploadServerThread*>(args);
    serverThread->handleClientConnection();
    delete serverThread;
    return nullptr;
}


void UploadServerThread::handleClientConnection() {
    HttpServletRequest request;
    HttpServletResponse response;

    // Read the incoming request from clientSocket and populate the HttpServletRequest object.
    request.readFromSocket(clientSocket);  // assuming you have a method like this
    std::cout << "Received " << request.getMethod() << " request." << std::endl;
    std::string method = request.getMethod();  // Assuming you have a getMethod() in HttpServletRequest

    // Check the type of the request and handle accordingly
    if (method == "GET" && request.getPath() == "/") {
        uploadServlet.doGet(request, response);
    } else if (method == "POST" && request.getPath() == "/") {
        uploadServlet.doPost(request, response);
    } else {
        // Handle other types of requests or send a 404 Not Found response
        std::string httpResponse = "HTTP/1.1 404 Not Found\r\n\r\nPage not found!";
        send(clientSocket, httpResponse.c_str(), httpResponse.size(), 0);
    }

    // Send the response back to the client.
    response.writeToSocket(clientSocket);  // assuming you have a method like this
}
