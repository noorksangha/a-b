#include "UploadServerThread.h"

UploadServerThread::UploadServerThread(int socket) : clientSocket(socket) {}

void UploadServerThread::start() {
    thread = std::thread(&UploadServerThread::run, this);
    thread.detach();
}

void UploadServerThread::run() {
    try {
        char buffer[1024];
        int bytes_read = read(clientSocket, buffer, sizeof(buffer));
        std::string inputLine(buffer, bytes_read);

        HttpServletRequest req(clientSocket);
std::ostringstream responseStream;
HttpServletResponse res(responseStream);
        UploadServlet httpServlet;

        if (inputLine.find("GET / ") != std::string::npos) {
            std::cout << "Calling doGet method" << std::endl;
            httpServlet.doGet(req, res);
        } else if (inputLine.find("POST /upload HTTP/1.1") != std::string::npos) {
            std::cout << "Calling doPost method" << std::endl;
            httpServlet.doPost(req, res);
        }

        std::string response = responseStream.str();
        send(clientSocket, response.c_str(), response.length(), 0);
        std::cout << "Wrote out response" << std::endl;
        close(clientSocket);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
