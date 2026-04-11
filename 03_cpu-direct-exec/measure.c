#define _GNU_SOURCE
#include <assert.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define NUM_LOOPS 100000

int main() {
    cpu_set_t cpu;
    CPU_ZERO(&cpu);
    CPU_SET(0, &cpu);
    sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpu);

    struct timespec start, end;

    int p2c[2];
    int c2p[2];

    if (pipe(p2c) == -1 || pipe(c2p) == -1) {
        perror("pipe failed");
        exit(1);
    }

    int rc = fork();
    assert(rc >= 0);

    if (rc != 0) { // parent
        char string = '1';
        char buffer;

        for (int i = 0; i < NUM_LOOPS; ++i) {
            write(p2c[1], &string, 1);
            read(c2p[0], &buffer, 1);
        }

        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int i = 0; i < NUM_LOOPS; ++i) {
            write(p2c[1], &string, 1);
            read(c2p[0], &buffer, 1);
        }

        clock_gettime(CLOCK_MONOTONIC, &end);

        long seconds = end.tv_sec - start.tv_sec;
        long nanoseconds = end.tv_nsec - start.tv_nsec;
        long total_nanoseconds = (seconds * 1000000000L) + nanoseconds;

        printf("Time for one context switch: %ldns\n", (total_nanoseconds / NUM_LOOPS) / 2);
        // printf("Buffer read proof: %c\n", buffer);
    } else { // child
        char buffer;

        for (int i = 0; i < NUM_LOOPS; ++i) {
            read(p2c[0], &buffer, 1);
            write(c2p[1], &buffer, 1);
        }

        for (int i = 0; i < NUM_LOOPS; ++i) {
            read(p2c[0], &buffer, 1);
            write(c2p[1], &buffer, 1);
        }
    }

    close(p2c[0]);
    close(p2c[1]);
    close(c2p[0]);
    close(c2p[1]);

    return 0;
}
