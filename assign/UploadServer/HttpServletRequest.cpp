#include "HttpServletRequest.h"
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <vector>
HttpServletRequest::HttpServletRequest(int socket) : clientSocket(socket) {}

std::string HttpServletRequest::getParameter(const std::string& name) {
    auto it = params.find(name);
    return it != params.end() ? it->second : "";
}


void HttpServletRequest::parseInputStream() {
    std::cout << "Parsing input data in request now." << std::endl;

    std::string boundary;
    std::string line;
    bool isFileData = false;
    std::ostringstream fileContentStream;

    // Read the boundary line
    boundary = readLine();
    if (!boundary.empty()) {
        std::cout << "Boundary is found: " << boundary << std::endl;
    }

    // Parse form data
    while (!(line = readLine()).empty() && line != boundary + "--") {
        if (line.find("Content-Disposition: form-data; name=\"file\"") != std::string::npos) {
            std::string originalFilename = extractFilename(line);

            params["filename"] = originalFilename;
            std::cout << "Filename placed in map: " << originalFilename << std::endl;

            readLine(); // Skip Content-Type line
            readLine(); // Skip empty line

            isFileData = true;
            continue;
        } else if (line.find("Content-Disposition: form-data; name=\"caption\"") != std::string::npos) {
            readLine(); // Skip empty line
            std::string caption = readLine();
            params["caption"] = caption;
            std::cout << "Caption placed in map: " << caption << std::endl;
        } else if (line.find("Content-Disposition: form-data; name=\"date\"") != std::string::npos) {
            readLine(); // Skip empty line
            std::string date = readLine();
            params["date"] = date;
            std::cout << "Date placed in map: " << date << std::endl;
        }

        if (isFileData && line != "--" + boundary) {
            fileContentStream << line << "\n";
        } else if (line == "--" + boundary) {
            isFileData = false;
        }
    }

    // Store file data as a string for simplicity
    params["fileData"] = fileContentStream.str();
    std::cout << "Placed file data in map." << std::endl;
}

std::string HttpServletRequest::extractFilename(const std::string& contentDisposition) {
    size_t start = contentDisposition.find("filename=\"");
    if (start != std::string::npos) {
        start += 10; // Length of "filename=\""
        size_t end = contentDisposition.find("\"", start);
        if (end != std::string::npos) {
            return contentDisposition.substr(start, end - start);
        }
    }
    return "";
}


std::string HttpServletRequest::readLine() {
    std::string line;
    char ch;
    while (read(clientSocket, &ch, 1) > 0) {
        if (ch == '\n') {
            break;
        }
        line.push_back(ch);
    }
    return line;
}
