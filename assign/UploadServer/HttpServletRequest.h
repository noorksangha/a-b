#include "HttpServletResponse.h"
#include <iostream>
#include <sys/socket.h> 

HttpServletResponse::HttpServletResponse() : statusCode(200), statusMessage("OK") {}

void HttpServletResponse::writeToSocket(int socket) const {
    std::string response;
    response += "HTTP/1.1 " + std::to_string(statusCode) + " " + statusMessage + "\r\n";
    response += "Content-Length: " + std::to_string(body.length()) + "\r\n";
    for (const auto& header : headers) {
        response += header.first + ": " + header.second + "\r\n";
    }
    response += "\r\n";
    response += body;

    int bytesSent = send(socket, response.c_str(), response.length(), 0);
    if (bytesSent < 0) {
        std::cerr << "Error writing to socket" << std::endl;
    }
}

int HttpServletResponse::getStatusCode() const {
    return statusCode;
}

const std::string& HttpServletResponse::getStatusMessage() const {
    return statusMessage;
}

void HttpServletResponse::setStatusCode(int code) {
    statusCode = code;
}

void HttpServletResponse::setStatusMessage(const std::string& message) {
    statusMessage = message;
}


void HttpServletResponse::writeBody(const std::string& data) {
    body += data;
}

const std::string& HttpServletResponse::getHeader(const std::string& name) const {
    static const std::string emptyString = "";
    auto it = headers.find(name);
    if (it != headers.end()) {
        return it->second;
    }
    return emptyString;
}

void HttpServletResponse::setHeader(const std::string& name, const std::string& value) {
    headers[name] = value;
}
