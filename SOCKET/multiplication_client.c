#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/multiplication_socket"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num1> <num2>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int client_fd;
    struct sockaddr_un server_addr;
    int nums[2], result;

    // Convert arguments to integers
    nums[0] = atoi(argv[1]);
    nums[1] = atoi(argv[2]);

    // Create socket
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Connect to server
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connect failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // Send numbers to server
    if (write(client_fd, nums, sizeof(nums)) != sizeof(nums)) {
        perror("Write failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // Receive result from server
    if (read(client_fd, &result, sizeof(result)) != sizeof(result)) {
        perror("Read failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    printf("Result from server: %d\n", result);
    close(client_fd);
    return 0;
}
