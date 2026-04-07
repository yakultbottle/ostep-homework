#include <assert.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int rc = fork();
    assert(rc >= 0);

    if (rc == 0) { // child
        int value = wait(NULL);
        // printf("Yello, from child (pid:%d)\n", (int)getpid());
        printf("Yello, from child (pid:%d), wait value: %d\n", (int)getpid(), value);
    } else { // parent
        // int value = wait(NULL);
        // printf("Hello, from parent (pid:%d), wait value: %d\n", (int)getpid(), value);
        printf("Hello, from parent (pid:%d)\n", (int)getpid());
    }
    return 0;
}
