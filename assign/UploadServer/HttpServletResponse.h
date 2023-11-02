#ifndef HTTP_SERVLET_RESPONSE_H
#define HTTP_SERVLET_RESPONSE_H

#include <string>
#include <map>

class HttpServletResponse {
public:
    HttpServletResponse();
    ~HttpServletResponse() = default;

    // Writes the HTTP response to a given socket
    void writeToSocket(int socket) const;

    // Setter methods
    void setStatusCode(int code);
    void setStatusMessage(const std::string& message);
    void setHeader(const std::string& key, const std::string& value);
    void writeBody(const std::string& data);

    // Getter methods
    int getStatusCode() const;
    const std::string& getStatusMessage() const;
    const std::string& getHeader(const std::string& key) const;
    const std::string& getBody() const;

private:
    int statusCode;                           
    std::string statusMessage;                
    std::map<std::string, std::string> headers; 
    std::string body;
};

#endif // HTTP_SERVLET_RESPONSE_H
