#include "HttpServlet.h"

HttpServlet::HttpServlet() {}

HttpServlet::~HttpServlet() {}

void HttpServlet::doGet(HttpServletRequest& request, HttpServletResponse& response) {
    response.setStatusCode(405); // Method Not Allowed
    response.writeBody("GET method is not supported by this servlet.");
}

void HttpServlet::doPost(HttpServletRequest& request, HttpServletResponse& response) {
    response.setStatusCode(405); // Method Not Allowed
    response.writeBody("POST method is not supported by this servlet.");
}

void HttpServlet::doPut(HttpServletRequest& request, HttpServletResponse& response) {
    response.setStatusCode(405); // Method Not Allowed
    response.writeBody("PUT method is not supported by this servlet.");
}

void HttpServlet::doDelete(HttpServletRequest& request, HttpServletResponse& response) {
    response.setStatusCode(405); // Method Not Allowed
    response.writeBody("DELETE method is not supported by this servlet.");
}

void HttpServlet::service(HttpServletRequest& request, HttpServletResponse& response) {
    std::string method = request.getMethod();
    if (method == "GET") {
        doGet(request, response);
    } else if (method == "POST") {
        doPost(request, response);
    } else if (method == "PUT") {
        doPut(request, response);
    } else if (method == "DELETE") {
        doDelete(request, response);
    } else {
        response.setStatusCode(501); // Not Implemented
        response.writeBody("This HTTP method is not supported.");
    }
}
