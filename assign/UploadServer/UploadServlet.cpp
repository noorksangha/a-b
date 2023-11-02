#include "UploadServlet.h"
#include <fstream>

UploadServlet::UploadServlet(const std::string& saveDirectory) : saveDirectory(saveDirectory) {}

void UploadServlet::doGet(HttpServletRequest& request, HttpServletResponse& response) {
    response.setStatusCode(200);
    
    std::string httpResponse;
    httpResponse += "<html><body>";
    httpResponse += "<form action=\"/\" method=\"post\" enctype=\"multipart/form-data\">";
    httpResponse += "Caption: <input type=\"text\" name=\"caption\"><br>";
    httpResponse += "Date: <input type=\"text\" name=\"date\"><br>";
    httpResponse += "File: <input type=\"file\" name=\"file\"><br>";
    httpResponse += "<input type=\"submit\" value=\"Upload\">";
    httpResponse += "</form>";
    httpResponse += "</body></html>";
    
    response.writeBody(httpResponse);
}

void UploadServlet::doPost(HttpServletRequest& request, HttpServletResponse& response) {
    std::string request_data;
    // Read data from clientSocket and store in request_data
    // ... This might need some adjustments based on your new design ...

    // Find boundary string from headers in HttpServletRequest object
    std::string boundary = "--" + request.getHeader("Content-Type").substr(request.getHeader("Content-Type").find("boundary=") + 9);

    size_t pos = 0;
    while ((pos = request_data.find(boundary)) != std::string::npos) {
        // Extract the part data
        std::string part_data = request_data.substr(0, pos);

        // Check if this part has a filename header (indicating a file upload)
        size_t filename_pos = part_data.find("filename=\"");
        if (filename_pos != std::string::npos) {
            size_t filename_end = part_data.find("\"", filename_pos + 10);
            std::string filename = part_data.substr(filename_pos + 10, filename_end - filename_pos - 10);

            size_t file_data_start = part_data.find("\r\n\r\n", filename_end) + 4;
            std::string file_data = part_data.substr(file_data_start);

            // Save file_data to a file with the given filename in the "uploads" directory
            std::string filePath = "uploads/" + filename;
            std::ofstream outFile(filePath, std::ios::binary);
            outFile.write(file_data.c_str(), file_data.length());
            outFile.close();

        } else {
            // Handle non-file form parts (like text fields)
            // ...
        }

        // Remove this part from request_data and continue
        request_data = request_data.substr(pos + boundary.length());
    }

    response.setStatusCode(200);
    response.writeBody("File uploaded successfully!");  // Assuming you have writeBody method in HttpServletResponse
}

bool UploadServlet::saveUploadedFile(const std::string& fileName, const std::string& fileContent) {
    std::string filePath = saveDirectory + "/" + fileName;

    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile) {
        return false;
    }

    outFile.write(fileContent.c_str(), fileContent.size());
    outFile.close();

    return true;
}
