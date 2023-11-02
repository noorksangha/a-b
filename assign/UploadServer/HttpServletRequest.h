#ifndef HTTP_SERVLET_REQUEST_H
#define HTTP_SERVLET_REQUEST_H

#include <string>
#include <map>

class HttpServletRequest {
public:
    HttpServletRequest();
    
    // Reads the HTTP request from a given socket
    void readFromSocket(int socket);

    // Getter methods
    const std::string& getMethod() const;
    const std::string& getPath() const;
    const std::string& getHeader(const std::string& key) const;
    const std::string& getBody() const;


    // TODO: Add more methods or attributes if necessary, like query parameters parsing

private:
    std::string method;                           // HTTP method (e.g., "GET", "POST")
    std::string path;                             // Requested path (e.g., "/")
    std::string body;                             // Request body
    std::map<std::string, std::string> headers;   // HTTP headers
    std::map<std::string, std::string> form_data; // Form data (key-value pairs from the body)
};

#endif // HTTP_SERVLET_REQUEST_H