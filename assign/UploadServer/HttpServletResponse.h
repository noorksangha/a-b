#ifndef HTTPSERVLETRESPONSE_H
#define HTTPSERVLETRESPONSE_H

#include <string>
#include <ostream>

class HttpServletResponse {
    std::ostream& outputStream;

public:
    HttpServletResponse(std::ostream& os);
    void setContentType(const std::string& type);
    std::ostream& getWriter();
};

#endif // HTTPSERVLETRESPONSE_H
