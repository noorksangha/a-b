#ifndef UPLOADSERVLET_H
#define UPLOADSERVLET_H

#include "HttpServlet.h"
#include "HttpServletRequest.h"
#include "HttpServletResponse.h"
#include <string>
#include <fstream>
#include <filesystem>

class UploadServlet : public HttpServlet {
    const std::string UPLOAD_DIR = "uploads";

public:
    void doGet(HttpServletRequest& request, HttpServletResponse& response) override;
    void doPost(HttpServletRequest& request, HttpServletResponse& response) override;
};

#endif // UPLOADSERVLET_H
