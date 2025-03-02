// Receiver
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8888

int main(void) {
    struct sockaddr_in si_me, si_other;
    int s, slen = sizeof(si_other);
    char buf[512];

    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("socket");
        exit(1);
    }

    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(s, (struct sockaddr *) &si_me, sizeof(si_me)) == -1) {
        perror("bind");
        exit(1);
    }

    if (recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &si_other, &slen) == -1) {
        perror("recvfrom()");
        exit(1);
    }

    printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
    printf("Data: %s\n", buf);

    close(s);
    return 0;
}

