# Homework 2 CPU API

## Question 1

Write a program that calls fork(). Before calling fork(), have the main process
access a variable (e.g., x) and set its value to something (e.g., 100). What
value is the variable in the child process? What happens to the variable when
both the child and parent change the value of x?

**Answer:** The value of the variable in the child process is the same as the
parent. Furthermore, you can see that a copy of the variable is made, as
changing the parent does not change the child.

```c
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
```

```bash
yakultbottle:02_cpu-api$ ./q1
Hello, from parent (pid:302392), x is 150
Yello, from child (pid:302393), x is 100
Yello again, from child (pid:302393), x is 50
```

## Question 2

Write a program that opens a file (with the open() system call) and then calls
fork() to create a new process. Can both the child and parent access the file
descriptor returned by open()? What happens when they are writing to the file
concurrently, i.e., at the same time?

**Answer:** Both the child and parent can access the file descriptor
simultaneously, as can be proven by the fact that they print the same file
descriptor value and writing to it returns a success. It also manages to
coherently write to the file, before closing it. I know that multiple files can
maintain a file descriptor to a file, but to see it work seamlessly with read
and writes is crazy to me.

```c
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
```

```bash
yakultbottle:02_cpu-api$ make
gcc -Wall -Wextra -g -o q2.out q2.c
yakultbottle:02_cpu-api$ ./q2.out
fd is 3
Hello, from parent (pid:498278), fd is 3
Yello, from child (pid:498279), fd is 3
yakultbottle:02_cpu-api$ cat q2.txt
Hello, from parent
Yello, from child
```

## Question 3

Write another program using fork(). The child process should print “hello”; the
parent process should print “goodbye”. You should try to ensure that the child
process always prints first; can you do this without calling wait() in the
parent?

**Answer:** Trivially done with the `sleep` or `usleep` functions, although of
course this can also be done with a long enough for loop. Care should be taken
that a for loop counting numbers doesn't get optimised away by the compiler
though I bet

```c
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
```

## Question 4

Write a program that calls fork() and then calls some form of exec() to run the
program /bin/ls. See if you can try all of the variants of exec(), including
execl(), execle(), execlp(), execv(), execvp(), and execvP(). Why do you think
there are so many variants of the same basic call?

**Answer:** Probably mostly legacy reasons, the new function signatures were
introduced to provide a new benefit, such as a variable amount of arguments that
doesn't need to be known before the function was called, or being able to set
environment variables.

Addendum, seems the linux kernel exclusively uses `execve()` under the hood. All
others are a layer of convenience for the C programmer, ie passing the work to
the library to search through the $PATH.

Addendum addendum that `exec()` transforms the program into the program it
called, so my code as below would only run the first `execl()`.

```c
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
```

## Question 5

Now write a program that uses wait() to wait for the child process to finish in
the parent. What does wait() return? What happens if you use wait() in the
child?

**Answer:** `wait()` returns the pid of the child process it is waiting for.
Clearly the convention is to wait in the parent for the child. If you use
`wait()` in the child, the code executes as expected, but the return value is
-1, the value used for returning an error.

```c
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
```

```bash
yakultbottle:02_cpu-api$ ./q5.out
Hello, from parent (pid:315419)
Yello, from child (pid:315420), wait value: -1
```

## Question 6

Write a slight modification of the previous program, this time using waitpid()
instead of wait(). When would waitpid() be useful?

**Answer:** `waitpid()` has a couple of additional options for waiting for
processes. For example, I can choose to wait for a process by its specific PID,
so more guarantees about correctness can be made. Another example is I can
choose to wait for something in my process group.

Addendum, I missed the functionality of the options, which allow for you to wait
without blocking and to detect state changes to child processes.

```c
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
```

## Question 7

Write a program that creates a child process, and then in the child closes
standard output (STDOUT FILENO). What happens if the child calls printf() to
print some output after closing the descriptor?

**Answer:** The child's printf is not printed anywhere. It vanishes into the
ether.

Addendum, if I checked printf's return value it would have returned -1.

```c
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
```

```bash
yakultbottle:02_cpu-api$ ./q7.out
Hello, from parent (pid:389941)
```

## Question 8

Write a program that creates two children, and connects the standard output of
one to the standard input of the other, using the pipe() system call.

**Answer:** Still don't fully understand `pipe()`. I don't understand the need
for pipe to exist before if I'm going to overwrite the descriptors with dup2
anyway.

Addendum, `pipe()` should be called before so both parent and child(or in this
case, both siblings) know about the pipe's existence. Think of it as literal
cloning, where after cloning each person goes into a different room. If before
being cloned we get a pipe item, all further clone branches are aware of this
pipe. However if it happens after cloning, then only that clone is aware. To
stop the analogy, this is because the state of the file descriptors is copied
over at the instant of copying. Then, for each child we manually change the file
descriptor on each end of the pipe to connect to stdin and stdout, but we could
still manually read and write from the original assigned ports if we so wished.

```c
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
```

```bash
yakultbottle:02_cpu-api$ ./q8.out
Hello from parent (pid:529109)
Received by child 529111: Message from child 529110
```
