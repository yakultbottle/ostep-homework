#include <assert.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int rc = fork();
    assert(rc >= 0);

    if (rc == 0) { // child
        close(STDOUT_FILENO);
        printf("Yello, from child (pid:%d)\n", (int)getpid());
    } else { // parent
        printf("Hello, from parent (pid:%d)\n", (int)getpid());
    }
    return 0;
}
