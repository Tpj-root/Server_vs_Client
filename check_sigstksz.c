#include <stdio.h>
#include <signal.h>

int main() {
    printf("SIGSTKSZ: %d\n", SIGSTKSZ);
    return 0;
}
