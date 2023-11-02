#include "HttpServletRequest.h"
#include <sys/socket.h>
#include <iostream>
#include <sstream>


HttpServletRequest::HttpServletRequest() {}

void HttpServletRequest::readFromSocket(int socket) {
std::cout << "Received HTTP request:" << std::endl;
std::cout << "--------------------------" << std::endl;

    char buffer[8192]; 
    int bytesReceived = recv(socket, buffer, sizeof(buffer) - 1, 0);

    if (bytesReceived < 0) {
        std::cerr << "Error reading from socket" << std::endl;
        return;
    }

    buffer[bytesReceived] = '\0'; 

    std::string request(buffer);

    size_t pos = request.find(' ');
if (pos != std::string::npos) {
    method = request.substr(0, pos);
    size_t endPos = request.find(' ', pos + 1);
    if (endPos != std::string::npos) {
        path = request.substr(pos + 1, endPos - pos - 1);
    }
}


    size_t headers_start = request.find("\r\n") + 2; 
    size_t headers_end = request.find("\r\n\r\n");   
    std::string headers_str = request.substr(headers_start, headers_end - headers_start);

    std::stringstream ss(headers_str);
    std::string header;
    while (std::getline(ss, header, '\n')) {
        size_t colon_pos = header.find(':');
        if (colon_pos != std::string::npos) {
            std::string key = header.substr(0, colon_pos);
            std::string value = header.substr(colon_pos + 2); 
            headers[key] = value;
        }
    }

    size_t body_start = headers_end + 4; // Added 4 to account for the "\r\n\r\n"
    if (body_start < request.size()) {
        body = request.substr(body_start);
    }

    // TODO: Parse form data if the content type indicates URL encoded form data.
}

const std::string& HttpServletRequest::getMethod() const {
    return method;
    
}

const std::string& HttpServletRequest::getPath() const {
    return path;
}

const std::string& HttpServletRequest::getHeader(const std::string& name) const {
    static const std::string emptyString = ""; // A static empty string to return safely

    auto it = headers.find(name);
    if (it != headers.end()) {
        return it->second;
    }
    return emptyString;
}

const std::string& HttpServletRequest::getBody() const {
    return body;
}