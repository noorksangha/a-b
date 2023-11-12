#include "UploadServlet.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <filesystem>

void UploadServlet::doGet(HttpServletRequest& request, HttpServletResponse& response) {
    std::ostream& out = response.getWriter();
    response.setContentType("text/html");
    out << "<html><body>";
    out << "<h1>File Upload Form</h1>";
    out << "<form method='POST' action='/upload' enctype='multipart/form-data'>";
    out << "<input type='file' name='file' /><br />";
    out << "<input type='text' name='caption' placeholder='Caption' /><br />";
    out << "<input type='text' name='date' placeholder='Date' /><br />";
    out << "<input type='submit' value='Upload' />";
    out << "</form>";
    out << "</body></html>";
}

void UploadServlet::doPost(HttpServletRequest& request, HttpServletResponse& response) {
    request.parseInputStream();

    // Create directory if it does not exist
    if (!std::filesystem::exists(UPLOAD_DIR)) {
        std::filesystem::create_directory(UPLOAD_DIR);
    }

    // Get all the values
    std::string caption = request.getParameter("caption");
    std::string date = request.getParameter("date");
    std::string filename = request.getParameter("filename");
    std::string fileData = request.getParameter("fileData"); // Assuming fileData is stored as a string

    std::string filePath = UPLOAD_DIR + "/" + caption + "_" + date + "_" + filename;
    std::ofstream fileStream(filePath, std::ios::binary);
    if (fileStream.is_open() && !fileData.empty()) {
        fileStream.write(fileData.data(), fileData.size());
        std::cout << "File uploaded successfully" << std::endl;
    } else {
        std::cout << "File data was null, could not be uploaded" << std::endl;
    }

    // Get and sort the list of files
    std::vector<std::filesystem::path> files;
    for (const auto& entry : std::filesystem::directory_iterator(UPLOAD_DIR)) {
        files.push_back(entry.path());
    }
    std::sort(files.begin(), files.end());

    // Generate and send an HTML response
    std::ostream& out = response.getWriter();
    response.setContentType("text/html");

    out << "<html><body>";
    out << "<h1>Uploaded Files</h1>";
    out << "<ul>";
    for (const auto& file : files) {
        if (std::filesystem::is_directory(file)) {
            out << "<li><button type=\"button\">" << file.filename() << "</button></li>";
        } else {
            out << "<li>" << file.filename() << "</li>";
        }
    }
    out << "</ul>";
    out << "</body></html>";
}
