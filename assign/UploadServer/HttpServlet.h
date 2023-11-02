#ifndef HTTP_SERVLET_H
#define HTTP_SERVLET_H

#include "HttpServletRequest.h"
#include "HttpServletResponse.h"

class HttpServlet {
public:
    HttpServlet();
    virtual ~HttpServlet();

    virtual void doGet(HttpServletRequest& request, HttpServletResponse& response);
    virtual void doPost(HttpServletRequest& request, HttpServletResponse& response);
    virtual void doPut(HttpServletRequest& request, HttpServletResponse& response);
    virtual void doDelete(HttpServletRequest& request, HttpServletResponse& response);

    void service(HttpServletRequest& request, HttpServletResponse& response);
};

#endif // HTTP_SERVLET_H
