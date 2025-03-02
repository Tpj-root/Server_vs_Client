// Sender
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER "127.0.0.1"
#define PORT 8888

int main(void) {
    struct sockaddr_in si_other;
    int s, slen = sizeof(si_other);
    char message[100] = "hello";

    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("socket");
        exit(1);
    }

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);

    if (inet_aton(SERVER, &si_other.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    if (sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_other, slen) == -1) {
        perror("sendto");
        exit(1);
    }

    close(s);
    return 0;
}

