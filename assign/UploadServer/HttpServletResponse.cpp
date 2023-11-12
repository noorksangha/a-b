#include "HttpServletResponse.h"
#include <iostream>

HttpServletResponse::HttpServletResponse(std::ostream& os) : outputStream(os) {}

void HttpServletResponse::setContentType(const std::string& type) {
    outputStream << "HTTP/1.1 200 OK\r\n"
                 << "Content-Type: " << type << "; charset=UTF-8\r\n"
                 << "\r\n";
}

std::ostream& HttpServletResponse::getWriter() {
    return outputStream;
}
