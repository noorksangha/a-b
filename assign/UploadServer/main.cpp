#include "HttpServletRequest.h"
#include "HttpServletResponse.h"
#include "UploadServlet.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8082);  // port number

    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    UploadServlet uploadServlet("uploads");  // specify your path

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
        if (newsockfd < 0) {
            perror("ERROR on accept");
            continue;
        }

        HttpServletRequest request;
        HttpServletResponse response;

        request.readFromSocket(newsockfd);

        if (request.getMethod() == "POST" && request.getPath() == "upload") {
    uploadServlet.doPost(request, response);
} else if (request.getMethod() == "GET" && request.getPath() == "/") {
    uploadServlet.doGet(request, response);  // Assuming you have a doGet method defined similarly to doPost in UploadServlet
} else {
    // Handle other types of requests or endpoints
}

        response.writeToSocket(newsockfd);
        close(newsockfd);
    }

    close(sockfd);
    return 0;
}

