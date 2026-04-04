# Homework 1 CPU Introduction

## Question 1

Run the program with the following flags: ./process-run.py -l 5:100,5:100. What
should the CPU utilization be (e.g., the percent of time the CPU is in use?) Why
do you know this? Use the -c and -p flags to see if you were right.

**Answer:** The CPU utilization should be 100%. This is because there is no call
to the IO, so the CPU is always executing one of the threads, so the CPU usage
time is 100% of the time.

```bash
yakultbottle:01_cpu-intro$ python3 ./process-run.py -l 5:100,5:100 -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1
  2        RUN:cpu         READY             1
  3        RUN:cpu         READY             1
  4        RUN:cpu         READY             1
  5        RUN:cpu         READY             1
  6           DONE       RUN:cpu             1
  7           DONE       RUN:cpu             1
  8           DONE       RUN:cpu             1
  9           DONE       RUN:cpu             1
 10           DONE       RUN:cpu             1

Stats: Total Time 10
Stats: CPU Busy 10 (100.00%)
Stats: IO Busy  0 (0.00%)
```

## Question 2

Now run with these flags: ./process-run.py -l 4:100,1:0. These flags specify one
process with 4 instructions (all to use the CPU), and one that simply issues an
I/O and waits for it to be done. How long does it take to complete both
processes? Use -c and -p to find out if you were right.

**Answer:** Depending on which process starts first, the time to completion
differs. If the CPU process starts first, then the I/O process will run after,
and we will waste CPU time while waiting for the I/O process, so it will
complete slower, and vice versa.

```bash
yakultbottle:01_cpu-intro$ python3 ./process-run.py -l 4:100,1:0 -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1
  2        RUN:cpu         READY             1
  3        RUN:cpu         READY             1
  4        RUN:cpu         READY             1
  5           DONE        RUN:io             1
  6           DONE       BLOCKED                           1
  7           DONE       BLOCKED                           1
  8           DONE       BLOCKED                           1
  9           DONE       BLOCKED                           1
 10           DONE       BLOCKED                           1
 11*          DONE   RUN:io_done             1

Stats: Total Time 11
Stats: CPU Busy 6 (54.55%)
Stats: IO Busy  5 (45.45%)
```

I ran it several times, and it seems to always run the first process first, so I
must have misunderstood the program.

## Question 3

Now switch the order of the processes: ./process-run.py -l 1:0,4:100. What
happens now? Does switching the order matter? Why? (As always, use -c and -p to
see if you were right)

**Answer:** Ah, this is what I thought from the previous question. CPU
utilisation will go up as compared to previously, as well as IO utilisation,
since total time will go down.

```bash
yakultbottle:01_cpu-intro$ python3 process-run.py -l 1:0,4:100 -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1
  2        BLOCKED       RUN:cpu             1             1
  3        BLOCKED       RUN:cpu             1             1
  4        BLOCKED       RUN:cpu             1             1
  5        BLOCKED       RUN:cpu             1             1
  6        BLOCKED          DONE                           1
  7*   RUN:io_done          DONE             1

Stats: Total Time 7
Stats: CPU Busy 6 (85.71%)
Stats: IO Busy  5 (71.43%)
```

## Question 4

We’ll now explore some of the other flags. One important flag is -S, which
determines how the system reacts when a process issues an I/O. With the flag set
to SWITCH ON END, the system will NOT switch to another process while one is
doing I/O, instead waiting until the process is completely finished. What
happens when you run the following two processes, one doing I/O and the other
doing CPU work? (-l 1:0,4:100 -c -S SWITCH ON END)

**Answer:** Same as the previous question, where you wait for I/O to finish
before switching, so usage should be the same.

```bash
yakultbottle:01_cpu-intro$ python3 process-run.py -l 1:0,4:100 -c -S SWITCH_ON_END -p
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1
  2        BLOCKED         READY                           1
  3        BLOCKED         READY                           1
  4        BLOCKED         READY                           1
  5        BLOCKED         READY                           1
  6        BLOCKED         READY                           1
  7*   RUN:io_done         READY             1
  8           DONE       RUN:cpu             1
  9           DONE       RUN:cpu             1
 10           DONE       RUN:cpu             1
 11           DONE       RUN:cpu             1

Stats: Total Time 11
Stats: CPU Busy 6 (54.55%)
Stats: IO Busy  5 (45.45%)
```

## Question 5

Now, run the same processes, but with the switching behavior set to switch to
another process whenever one is WAITING for I/O (-l 1:0,4:100 -c -S SWITCH ON
IO). What happens now? Use -c and -p to confirm that you are right.

**Answer:** Total time should decrease, and utilisation of both CPU and I/O
should increase as a result.

```bash
yakultbottle:01_cpu-intro$ python3 process-run.py -l 1:0,4:100 -c -p -S SWITCH_ON_IO
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1
  2        BLOCKED       RUN:cpu             1             1
  3        BLOCKED       RUN:cpu             1             1
  4        BLOCKED       RUN:cpu             1             1
  5        BLOCKED       RUN:cpu             1             1
  6        BLOCKED          DONE                           1
  7*   RUN:io_done          DONE             1

Stats: Total Time 7
Stats: CPU Busy 6 (85.71%)
Stats: IO Busy  5 (71.43%)
```

## Question 6

One other important behavior is what to do when an I/O completes. With -I IO RUN
LATER, when an I/O completes, the process that issued it is not necessarily run
right away; rather, whatever was running at the time keeps running. What happens
when you run this combination of processes? (./process-run.py -l
3:0,5:100,5:100,5:100 -S SWITCH ON IO -I IO RUN LATER -c -p) Are system
resources being effectively utilized?

**Answer:** System resources are being effectively utilized. This is because the
CPU does not wait after issuing an I/O request, and also that the system does
not instantly jump back to the waiting process before finishing the current
process. This reduces overhead lost to context switching, although this is not
simulated with process-run.py.

```bash
yakultbottle:01_cpu-intro$ python3 process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p
Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
  1         RUN:io         READY         READY         READY             1
  2        BLOCKED       RUN:cpu         READY         READY             1             1
  3        BLOCKED       RUN:cpu         READY         READY             1             1
  4        BLOCKED       RUN:cpu         READY         READY             1             1
  5        BLOCKED       RUN:cpu         READY         READY             1             1
  6        BLOCKED       RUN:cpu         READY         READY             1             1
  7*         READY          DONE       RUN:cpu         READY             1
  8          READY          DONE       RUN:cpu         READY             1
  9          READY          DONE       RUN:cpu         READY             1
 10          READY          DONE       RUN:cpu         READY             1
 11          READY          DONE       RUN:cpu         READY             1
 12          READY          DONE          DONE       RUN:cpu             1
 13          READY          DONE          DONE       RUN:cpu             1
 14          READY          DONE          DONE       RUN:cpu             1
 15          READY          DONE          DONE       RUN:cpu             1
 16          READY          DONE          DONE       RUN:cpu             1
 17    RUN:io_done          DONE          DONE          DONE             1
 18         RUN:io          DONE          DONE          DONE             1
 19        BLOCKED          DONE          DONE          DONE                           1
 20        BLOCKED          DONE          DONE          DONE                           1
 21        BLOCKED          DONE          DONE          DONE                           1
 22        BLOCKED          DONE          DONE          DONE                           1
 23        BLOCKED          DONE          DONE          DONE                           1
 24*   RUN:io_done          DONE          DONE          DONE             1
 25         RUN:io          DONE          DONE          DONE             1
 26        BLOCKED          DONE          DONE          DONE                           1
 27        BLOCKED          DONE          DONE          DONE                           1
 28        BLOCKED          DONE          DONE          DONE                           1
 29        BLOCKED          DONE          DONE          DONE                           1
 30        BLOCKED          DONE          DONE          DONE                           1
 31*   RUN:io_done          DONE          DONE          DONE             1

Stats: Total Time 31
Stats: CPU Busy 21 (67.74%)
Stats: IO Busy  15 (48.39%)
```

Oh. That's weird of the scheduler. After finishing the CPU process, I thought it
would go back to the OG process that was blocked instead of starting a new
process.

## Question 7

Now run the same processes, but with -I IO RUN IMMEDIATE set, which immediately
runs the process that issued the I/O. How does this behavior differ? Why might
running a process that just completed an I/O again be a good idea?

**Answer:** So THIS should be what I described previously. And running a process
that just completed an I/O might be a good idea in general because a process
that interacts with I/O is likely to need to do so again.

```bash
yakultbottle:01_cpu-intro$ python3 process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p
Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
  1         RUN:io         READY         READY         READY             1
  2        BLOCKED       RUN:cpu         READY         READY             1             1
  3        BLOCKED       RUN:cpu         READY         READY             1             1
  4        BLOCKED       RUN:cpu         READY         READY             1             1
  5        BLOCKED       RUN:cpu         READY         READY             1             1
  6        BLOCKED       RUN:cpu         READY         READY             1             1
  7*   RUN:io_done          DONE         READY         READY             1
  8         RUN:io          DONE         READY         READY             1
  9        BLOCKED          DONE       RUN:cpu         READY             1             1
 10        BLOCKED          DONE       RUN:cpu         READY             1             1
 11        BLOCKED          DONE       RUN:cpu         READY             1             1
 12        BLOCKED          DONE       RUN:cpu         READY             1             1
 13        BLOCKED          DONE       RUN:cpu         READY             1             1
 14*   RUN:io_done          DONE          DONE         READY             1
 15         RUN:io          DONE          DONE         READY             1
 16        BLOCKED          DONE          DONE       RUN:cpu             1             1
 17        BLOCKED          DONE          DONE       RUN:cpu             1             1
 18        BLOCKED          DONE          DONE       RUN:cpu             1             1
 19        BLOCKED          DONE          DONE       RUN:cpu             1             1
 20        BLOCKED          DONE          DONE       RUN:cpu             1             1
 21*   RUN:io_done          DONE          DONE          DONE             1

Stats: Total Time 21
Stats: CPU Busy 21 (100.00%)
Stats: IO Busy  15 (71.43%)
```

## Question 8

Now run with some randomly generated processes, e.g., -s 1 -l 3:50,3:50, -s 2 -l
3:50,3:50, -s 3 -l 3:50,3:50. See if you can predict how the trace will turn
out. What happens when you use -I IO RUN IMMEDIATE vs. -I IO RUN LATER? What
happens when you use -S SWITCH ON IO vs. -S SWITCH ON END?

```bash
yakultbottle:01_cpu-intro$ python3 process-run.py -s 1 -l 3:50,3:50 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1
  2         RUN:io         READY             1
  3        BLOCKED       RUN:cpu             1             1
  4        BLOCKED       RUN:cpu             1             1
  5        BLOCKED       RUN:cpu             1             1
  6        BLOCKED          DONE                           1
  7        BLOCKED          DONE                           1
  8*   RUN:io_done          DONE             1
  9         RUN:io          DONE             1
 10        BLOCKED          DONE                           1
 11        BLOCKED          DONE                           1
 12        BLOCKED          DONE                           1
 13        BLOCKED          DONE                           1
 14        BLOCKED          DONE                           1
 15*   RUN:io_done          DONE             1

Stats: Total Time 15
Stats: CPU Busy 8 (53.33%)
Stats: IO Busy  10 (66.67%)

yakultbottle:01_cpu-intro$ python3 process-run.py -s 2 -l 3:50,3:50 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1
  2        BLOCKED       RUN:cpu             1             1
  3        BLOCKED        RUN:io             1             1
  4        BLOCKED       BLOCKED                           2
  5        BLOCKED       BLOCKED                           2
  6        BLOCKED       BLOCKED                           2
  7*   RUN:io_done       BLOCKED             1             1
  8         RUN:io       BLOCKED             1             1
  9*       BLOCKED   RUN:io_done             1             1
 10        BLOCKED        RUN:io             1             1
 11        BLOCKED       BLOCKED                           2
 12        BLOCKED       BLOCKED                           2
 13        BLOCKED       BLOCKED                           2
 14*   RUN:io_done       BLOCKED             1             1
 15        RUN:cpu       BLOCKED             1             1
 16*          DONE   RUN:io_done             1

Stats: Total Time 16
Stats: CPU Busy 10 (62.50%)
Stats: IO Busy  14 (87.50%)

yakultbottle:01_cpu-intro$ python3 process-run.py -s 3 -l 3:50,3:50 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1
  2         RUN:io         READY             1
  3        BLOCKED        RUN:io             1             1
  4        BLOCKED       BLOCKED                           2
  5        BLOCKED       BLOCKED                           2
  6        BLOCKED       BLOCKED                           2
  7        BLOCKED       BLOCKED                           2
  8*   RUN:io_done       BLOCKED             1             1
  9*         READY   RUN:io_done             1
 10          READY        RUN:io             1
 11        RUN:cpu       BLOCKED             1             1
 12           DONE       BLOCKED                           1
 13           DONE       BLOCKED                           1
 14           DONE       BLOCKED                           1
 15           DONE       BLOCKED                           1
 16*          DONE   RUN:io_done             1
 17           DONE       RUN:cpu             1

Stats: Total Time 17
Stats: CPU Busy 9 (52.94%)
Stats: IO Busy  11 (64.71%)

yakultbottle:01_cpu-intro$ python3 process-run.py -s 1 -l 3:50,3:50 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1
  2         RUN:io         READY             1
  3        BLOCKED       RUN:cpu             1             1
  4        BLOCKED       RUN:cpu             1             1
  5        BLOCKED       RUN:cpu             1             1
  6        BLOCKED          DONE                           1
  7        BLOCKED          DONE                           1
  8*   RUN:io_done          DONE             1
  9         RUN:io          DONE             1
 10        BLOCKED          DONE                           1
 11        BLOCKED          DONE                           1
 12        BLOCKED          DONE                           1
 13        BLOCKED          DONE                           1
 14        BLOCKED          DONE                           1
 15*   RUN:io_done          DONE             1

Stats: Total Time 15
Stats: CPU Busy 8 (53.33%)
Stats: IO Busy  10 (66.67%)

yakultbottle:01_cpu-intro$ python3 process-run.py -s 2 -l 3:50,3:50 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1
  2        BLOCKED       RUN:cpu             1             1
  3        BLOCKED        RUN:io             1             1
  4        BLOCKED       BLOCKED                           2
  5        BLOCKED       BLOCKED                           2
  6        BLOCKED       BLOCKED                           2
  7*   RUN:io_done       BLOCKED             1             1
  8         RUN:io       BLOCKED             1             1
  9*       BLOCKED   RUN:io_done             1             1
 10        BLOCKED        RUN:io             1             1
 11        BLOCKED       BLOCKED                           2
 12        BLOCKED       BLOCKED                           2
 13        BLOCKED       BLOCKED                           2
 14*   RUN:io_done       BLOCKED             1             1
 15        RUN:cpu       BLOCKED             1             1
 16*          DONE   RUN:io_done             1

Stats: Total Time 16
Stats: CPU Busy 10 (62.50%)
Stats: IO Busy  14 (87.50%)

yakultbottle:01_cpu-intro$ python3 process-run.py -s 3 -l 3:50,3:50 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1
  2         RUN:io         READY             1
  3        BLOCKED        RUN:io             1             1
  4        BLOCKED       BLOCKED                           2
  5        BLOCKED       BLOCKED                           2
  6        BLOCKED       BLOCKED                           2
  7        BLOCKED       BLOCKED                           2
  8*   RUN:io_done       BLOCKED             1             1
  9*       RUN:cpu         READY             1
 10           DONE   RUN:io_done             1
 11           DONE        RUN:io             1
 12           DONE       BLOCKED                           1
 13           DONE       BLOCKED                           1
 14           DONE       BLOCKED                           1
 15           DONE       BLOCKED                           1
 16           DONE       BLOCKED                           1
 17*          DONE   RUN:io_done             1
 18           DONE       RUN:cpu             1

Stats: Total Time 18
Stats: CPU Busy 9 (50.00%)
Stats: IO Busy  11 (61.11%)

yakultbottle:01_cpu-intro$ python3 process-run.py -s 1 -l 3:50,3:50 -S SWITCH_ON_END -I IO_RUN_IMMEDIATE -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1
  2         RUN:io         READY             1
  3        BLOCKED         READY                           1
  4        BLOCKED         READY                           1
  5        BLOCKED         READY                           1
  6        BLOCKED         READY                           1
  7        BLOCKED         READY                           1
  8*   RUN:io_done         READY             1
  9         RUN:io         READY             1
 10        BLOCKED         READY                           1
 11        BLOCKED         READY                           1
 12        BLOCKED         READY                           1
 13        BLOCKED         READY                           1
 14        BLOCKED         READY                           1
 15*   RUN:io_done         READY             1
 16           DONE       RUN:cpu             1
 17           DONE       RUN:cpu             1
 18           DONE       RUN:cpu             1

Stats: Total Time 18
Stats: CPU Busy 8 (44.44%)
Stats: IO Busy  10 (55.56%)

yakultbottle:01_cpu-intro$ python3 process-run.py -s 2 -l 3:50,3:50 -S SWITCH_ON_END -I IO_RUN_IMMEDIATE -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1
  2        BLOCKED         READY                           1
  3        BLOCKED         READY                           1
  4        BLOCKED         READY                           1
  5        BLOCKED         READY                           1
  6        BLOCKED         READY                           1
  7*   RUN:io_done         READY             1
  8         RUN:io         READY             1
  9        BLOCKED         READY                           1
 10        BLOCKED         READY                           1
 11        BLOCKED         READY                           1
 12        BLOCKED         READY                           1
 13        BLOCKED         READY                           1
 14*   RUN:io_done         READY             1
 15        RUN:cpu         READY             1
 16           DONE       RUN:cpu             1
 17           DONE        RUN:io             1
 18           DONE       BLOCKED                           1
 19           DONE       BLOCKED                           1
 20           DONE       BLOCKED                           1
 21           DONE       BLOCKED                           1
 22           DONE       BLOCKED                           1
 23*          DONE   RUN:io_done             1
 24           DONE        RUN:io             1
 25           DONE       BLOCKED                           1
 26           DONE       BLOCKED                           1
 27           DONE       BLOCKED                           1
 28           DONE       BLOCKED                           1
 29           DONE       BLOCKED                           1
 30*          DONE   RUN:io_done             1

yakultbottle:01_cpu-intro$ python3 process-run.py -s 3 -l 3:50,3:50 -S SWITCH_ON_END -I IO_RUN_IMMEDIATE -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1
  2         RUN:io         READY             1
  3        BLOCKED         READY                           1
  4        BLOCKED         READY                           1
  5        BLOCKED         READY                           1
  6        BLOCKED         READY                           1
  7        BLOCKED         READY                           1
  8*   RUN:io_done         READY             1
  9        RUN:cpu         READY             1
 10           DONE        RUN:io             1
 11           DONE       BLOCKED                           1
 12           DONE       BLOCKED                           1
 13           DONE       BLOCKED                           1
 14           DONE       BLOCKED                           1
 15           DONE       BLOCKED                           1
 16*          DONE   RUN:io_done             1
 17           DONE        RUN:io             1
 18           DONE       BLOCKED                           1
 19           DONE       BLOCKED                           1
 20           DONE       BLOCKED                           1
 21           DONE       BLOCKED                           1
 22           DONE       BLOCKED                           1
 23*          DONE   RUN:io_done             1
 24           DONE       RUN:cpu             1

Stats: Total Time 24
Stats: CPU Busy 9 (37.50%)
Stats: IO Busy  15 (62.50%)

Stats: Total Time 30
Stats: CPU Busy 10 (33.33%)
Stats: IO Busy  20 (66.67%)

yakultbottle:01_cpu-intro$ python3 process-run.py -s 1 -l 3:50,3:50 -S SWITCH_ON_END -I IO_RUN_LATER -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1
  2         RUN:io         READY             1
  3        BLOCKED         READY                           1
  4        BLOCKED         READY                           1
  5        BLOCKED         READY                           1
  6        BLOCKED         READY                           1
  7        BLOCKED         READY                           1
  8*   RUN:io_done         READY             1
  9         RUN:io         READY             1
 10        BLOCKED         READY                           1
 11        BLOCKED         READY                           1
 12        BLOCKED         READY                           1
 13        BLOCKED         READY                           1
 14        BLOCKED         READY                           1
 15*   RUN:io_done         READY             1
 16           DONE       RUN:cpu             1
 17           DONE       RUN:cpu             1
 18           DONE       RUN:cpu             1

Stats: Total Time 18
Stats: CPU Busy 8 (44.44%)
Stats: IO Busy  10 (55.56%)

yakultbottle:01_cpu-intro$ python3 process-run.py -s 2 -l 3:50,3:50 -S SWITCH_ON_END -I IO_RUN_LATER -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1
  2        BLOCKED         READY                           1
  3        BLOCKED         READY                           1
  4        BLOCKED         READY                           1
  5        BLOCKED         READY                           1
  6        BLOCKED         READY                           1
  7*   RUN:io_done         READY             1
  8         RUN:io         READY             1
  9        BLOCKED         READY                           1
 10        BLOCKED         READY                           1
 11        BLOCKED         READY                           1
 12        BLOCKED         READY                           1
 13        BLOCKED         READY                           1
 14*   RUN:io_done         READY             1
 15        RUN:cpu         READY             1
 16           DONE       RUN:cpu             1
 17           DONE        RUN:io             1
 18           DONE       BLOCKED                           1
 19           DONE       BLOCKED                           1
 20           DONE       BLOCKED                           1
 21           DONE       BLOCKED                           1
 22           DONE       BLOCKED                           1
 23*          DONE   RUN:io_done             1
 24           DONE        RUN:io             1
 25           DONE       BLOCKED                           1
 26           DONE       BLOCKED                           1
 27           DONE       BLOCKED                           1
 28           DONE       BLOCKED                           1
 29           DONE       BLOCKED                           1
 30*          DONE   RUN:io_done             1

Stats: Total Time 30
Stats: CPU Busy 10 (33.33%)
Stats: IO Busy  20 (66.67%)

yakultbottle:01_cpu-intro$ python3 process-run.py -s 3 -l 3:50,3:50 -S SWITCH_ON_END -I IO_RUN_LATER -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1
  2         RUN:io         READY             1
  3        BLOCKED         READY                           1
  4        BLOCKED         READY                           1
  5        BLOCKED         READY                           1
  6        BLOCKED         READY                           1
  7        BLOCKED         READY                           1
  8*   RUN:io_done         READY             1
  9        RUN:cpu         READY             1
 10           DONE        RUN:io             1
 11           DONE       BLOCKED                           1
 12           DONE       BLOCKED                           1
 13           DONE       BLOCKED                           1
 14           DONE       BLOCKED                           1
 15           DONE       BLOCKED                           1
 16*          DONE   RUN:io_done             1
 17           DONE        RUN:io             1
 18           DONE       BLOCKED                           1
 19           DONE       BLOCKED                           1
 20           DONE       BLOCKED                           1
 21           DONE       BLOCKED                           1
 22           DONE       BLOCKED                           1
 23*          DONE   RUN:io_done             1
 24           DONE       RUN:cpu             1

Stats: Total Time 24
Stats: CPU Busy 9 (37.50%)
Stats: IO Busy  15 (62.50%)
```

If you can be bothered to read the output, you can see that SWITCH_ON_END always
matters. It is strictly speaking a negative effect. IO_RUN_IMMEDIATE and
IO_RUN_LATER on the other hand are much more subjective, since the perceived
improvement does not make a difference to this simulator. The idea is that for
real world programs, this should make a bigger difference, since they are not
perfectly random.
