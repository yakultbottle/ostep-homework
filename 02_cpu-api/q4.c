#include <assert.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int rc = fork();
    assert(rc >= 0);

    if (rc == 0) { // child
        char *full_path[3];
        full_path[0] = strdup("/bin/ls");
        full_path[1] = strdup("-a");
        full_path[2] = NULL;

        char *less_path[3];
        less_path[0] = strdup("ls");
        less_path[1] = strdup("-a");
        less_path[2] = NULL;

        char *my_env[] = {"USER=hacker", NULL};

        execl("/bin/ls", "ls", "-a", NULL);
        execle("/bin/ls", "ls", "-a", NULL, my_env);
        execlp("ls", "ls", "-a", NULL);
        execv(full_path[0], full_path);
        execvp(less_path[0], less_path);
        execve(full_path[0], full_path, my_env);
    } else { // parent
        wait(NULL);
    }
    return 0;
}
