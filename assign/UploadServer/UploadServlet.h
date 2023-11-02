#ifndef UPLOAD_SERVLET_H
#define UPLOAD_SERVLET_H

#include "HttpServletRequest.h"
#include "HttpServletResponse.h"
#include <string>

class UploadServlet {
public:
    UploadServlet(const std::string& saveDirectory);
    void doGet(HttpServletRequest& request, HttpServletResponse& response);
    void doPost(HttpServletRequest& request, HttpServletResponse& response);

private:
    std::string saveDirectory;

    bool saveUploadedFile(const std::string& fileName, const std::string& fileContent);
};

#endif // UPLOAD_SERVLET_H
