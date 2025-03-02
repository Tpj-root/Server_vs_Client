#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);
    ssize_t sent_bytes;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to port
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Receive data from client
        recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &addr_len);
        printf("Received: %s\n", buffer);

        // Add SAB protocol prefix
        char sab_message[BUFFER_SIZE];
        snprintf(sab_message, sizeof(sab_message), "sab://%s", buffer);

        // Send response to client
        sent_bytes = sendto(sockfd, sab_message, strlen(sab_message), 0, (struct sockaddr*)&client_addr, addr_len);
        if (sent_bytes < 0) {
            perror("Send failed");
            break;
        }

        printf("Response sent: %s\n", sab_message);
    }

    close(sockfd);
    return 0;
}
