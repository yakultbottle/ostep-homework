#include <assert.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int rc = fork();
    assert(rc >= 0);

    if (rc == 0) { // child
        printf("hello\n");
    } else { // parent
        // sleep(1);
        usleep(1000);
        printf("goodbye\n");
    }
    return 0;
}
