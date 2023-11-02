#include "UploadServlet.h"
#include <fstream>
#include <iostream>


UploadServlet::UploadServlet(const std::string& saveDirectory) : saveDirectory(saveDirectory) {}

bool UploadServlet::saveUploadedFile(const std::string& fileName, const std::string& fileContent, std::string& errorMsg) {
    std::string filePath = saveDirectory + "/" + fileName;
    std::ofstream outFile(filePath, std::ios::binary);
    
    if (!outFile) {
        errorMsg = "Failed to open the file for writing.";
        return false;
    }

    outFile.write(fileContent.c_str(), fileContent.size());
    if (!outFile) {
        errorMsg = "Failed to write data to the file.";
        return false;
    }

    outFile.close();
    return true;
}
void UploadServlet::doGet(HttpServletRequest& request, HttpServletResponse& response) {
    response.setStatusCode(200);
    std::cout << "Entered doGet method." << std::endl;

    
    std::string httpResponse;
    httpResponse += "<html><body>";
    httpResponse += "<form action=\"/\" method=\"POST\" enctype=\"multipart/form-data\">";
    httpResponse += "Caption: <input type=\"text\" name=\"caption\"><br>";
    httpResponse += "Date: <input type=\"text\" name=\"date\"><br>";
    httpResponse += "File: <input type=\"file\" name=\"file\"><br>";
    httpResponse += "<input type=\"submit\" value=\"Upload\">";
    httpResponse += "</form>";
    httpResponse += "</body></html>";
    
    response.writeBody(httpResponse);
}

void UploadServlet::doPost(HttpServletRequest& request, HttpServletResponse& response) {
    std::cout << "Entered doPost method." << std::endl;

    std::string request_data = request.getBody();

    std::string contentType = request.getHeader("Content-Type");
    size_t boundaryPos = contentType.find("boundary=");
    if (boundaryPos == std::string::npos) {
        response.setStatusCode(400); // Bad Request
        response.writeBody("Missing boundary in content-type!");
        return;
    }

    std::string boundary = "--" + contentType.substr(boundaryPos + 9);
    std::string lastBoundary = boundary + "--";

    size_t pos = 0;
    while ((pos = request_data.find(boundary)) != std::string::npos) {
        request_data = request_data.substr(pos + boundary.length());

        if (request_data.substr(0, 2) == "--") {
            // End of the multipart data
            break;
        }

        size_t nextBoundaryPos = request_data.find(boundary);
        std::string part_data = request_data.substr(0, nextBoundaryPos);

        size_t filename_pos = part_data.find("filename=\"");
        if (filename_pos != std::string::npos) {
            size_t filename_end = part_data.find("\"", filename_pos + 10);
            std::string filename = part_data.substr(filename_pos + 10, filename_end - filename_pos - 10);

            size_t file_data_start = part_data.find("\r\n\r\n", filename_end) + 4;
            std::string file_data = part_data.substr(file_data_start, nextBoundaryPos - file_data_start);

            std::string file_save_error;
            if (!saveUploadedFile(filename, file_data, file_save_error)) {
                response.setStatusCode(500);  // Internal Server Error
                response.writeBody("Error: " + file_save_error);
                return;
            }
        }

        request_data = request_data.substr(nextBoundaryPos);
    }

    response.setStatusCode(200);
    response.writeBody("All files uploaded successfully!");
}


