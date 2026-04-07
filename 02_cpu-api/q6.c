#include <assert.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int rc = fork();
    assert(rc >= 0);

    if (rc == 0) { // child
        printf("Yello, from child (pid:%d)\n", (int)getpid());
    } else { // parent
        // int value = waitpid(-1, NULL, 0);
        int value = waitpid(-(int)getpid(), NULL, 0);
        printf("Hello, from parent (pid:%d), waited for child (pid:%d)\n", (int)getpid(), value);
    }
    return 0;
}
