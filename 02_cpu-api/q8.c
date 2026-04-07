#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    int rc = fork();
    assert(rc >= 0);

    if (rc != 0) { // parent
        int rc2 = fork();
        assert(rc2 >= 0);

        if (rc2 != 0) { // parent
            wait(NULL);
            printf("Hello from parent (pid:%d)\n", (int)getpid());
        } else { // child2
            close(pipefd[1]); // not writing
            dup2(pipefd[0], STDIN_FILENO);

            char buffer[1000];
            // char buf;
            // int i = 0;

            // while (read(STDIN_FILENO, &buf, 1) > 0 && i < 999) {
            //     buffer[i] = buf;
            //     ++i;
            // }
            // buffer[i] = '\0';

            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                printf("Received by child %d: %s\n", (int)getpid(), buffer);
            }

            // printf("Received by child %d: %s\n", (int)getpid(), buffer);
            close(pipefd[0]);
        }
    } else { // child1
        close(pipefd[0]); // not reading
        dup2(pipefd[1], STDOUT_FILENO);

        printf("Message from child %d", (int)getpid());
        close(pipefd[1]);
    }
    return 0;
}
