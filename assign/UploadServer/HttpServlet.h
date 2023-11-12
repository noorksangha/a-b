#ifndef HTTPSERVLET_H
#define HTTPSERVLET_H

#include "HttpServletRequest.h"
#include "HttpServletResponse.h"

class HttpServlet {
public:
    virtual ~HttpServlet() {}

    virtual void doGet(HttpServletRequest& request, HttpServletResponse& response) {}
    virtual void doPost(HttpServletRequest& request, HttpServletResponse& response) {}
};

#endif // HTTPSERVLET_H
