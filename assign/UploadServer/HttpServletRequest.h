#ifndef HTTPSERVLETREQUEST_H
#define HTTPSERVLETREQUEST_H

#include <map>
#include <string>
#include <sstream>

class HttpServletRequest {
    std::map<std::string, std::string> params;
    int clientSocket;

public:
    HttpServletRequest(int socket);
    std::string getParameter(const std::string& name);
    void parseInputStream();
    std::string extractFilename(const std::string& contentDisposition);

private:
    std::string readLine();
};

#endif // HTTPSERVLETREQUEST_H
