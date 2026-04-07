#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    int fd = open("./q2.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    assert(fd > -1);
    printf("fd is %d\n", fd);

    int rc = fork();
    assert(rc >= 0);

    if (rc == 0) { // child
        assert(fd > -1);
        printf("Yello, from child (pid:%d), fd is %d\n", (int)getpid(), fd);
        char *msg = "Yello, from child\n";
        int success = write(fd, msg, strlen(msg));
        assert(success == (int)strlen(msg));
    } else { // parent
        assert(fd > -1);
        printf("Hello, from parent (pid:%d), fd is %d\n", (int)getpid(), fd);
        char *msg = "Hello, from parent\n";
        int success = write(fd, msg, strlen(msg));
        assert(success == (int)strlen(msg));
    }

    close(fd);
    return 0;
}
