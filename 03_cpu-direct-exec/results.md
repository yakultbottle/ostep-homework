# Measuring time for a single context switch

To force the CPU onto a single core, I used this piece of code which sets the
current process to use only CPU 0.

```c
cpu_set_t cpu;
CPU_ZERO(&cpu);
CPU_SET(0, &cpu);
sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpu);
```

For measuring time I used `clock_gettime()` from `time.h`, as opposed to the
suggestion of `gettimeofday()`, which is only microsecond precise. I then
created two pipes, and another process, such that I could send a message back
and forth on the two pipes to force a context switch (as per the book's
instructions). I thought I could get away with only one pipe, but apparently
despite having a read and write end, they're implemented as a single buffer. So
if you do a write into a read on the same pipe, it will just read its own input,
no context switching. I then looped this 100k times, and averaged the readings.
I noticed that the numbers were different if I changed the number of loops from
100k to 1M, about 1500-1600ns to 1100ns. This is either due to caching, branch
prediction(unlikely), or CPU frequency scaling(most likely?). I think branch
preduction is unlikely because I'm quite sure the branch saturates extremely
quickly for a loop. Like we're talking they would mispredict four times max for
each for loop(at a guess), which is maybe 100 cycles total after rounding up.
Caching would be the same story, except I think there's a small chance the cache
manager or whatever is way smarter, and so maaaybe it gets upgraded to higher
levels of cache? I think CPU frequency scaling def makes the most sense.

```bash
yakultbottle:03_cpu-direct-exec$ lscpu | rg MHz
CPU max MHz:                             5200.0000
CPU min MHz:                             400.0000
```

Either way, I solved this problem at 100k loops by deciding to warm it up first
with 100k loops, then starting the timer and doing 100k loops. Stupid, but
definitely any issue with the frequency scaling or whatsoever should be solved
by then. And it worked, now all measurements stable around 1100ns, +/- single
digit ns.

```bash
yakultbottle:03_cpu-direct-exec$ ./measure.out
Time for one context switch: 1100ns
```
