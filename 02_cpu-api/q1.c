#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int x = 100;
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child
        wait(NULL);
        printf("Yello, from child (pid:%d), x is %d\n", (int)getpid(), x);
        x = 50;
        printf("Yello again, from child (pid:%d), x is %d\n", (int)getpid(), x);
    } else { // parent
        x = 150;
        printf("Hello, from parent (pid:%d), x is %d\n", (int)getpid(), x);
    }
    return 0;
}
