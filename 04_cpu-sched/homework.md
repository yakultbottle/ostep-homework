# Homework 4 Scheduling Introduction

## Question 1

Compute the response time and turnaround time when running three jobs of length
200 with the SJF and FIFO schedulers.

**Answer:**

```
FIFO:
Turnaround: 200, 400, 600 -> avg 400
Response: 0, 200, 400 -> avg 200

SJF:
Turnaround: 200, 400, 600 -> avg 400
Response: 0, 200, 400 -> avg 200
```

Correct answer:

```bash
Final statistics:
  Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
  Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
  Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00

  Average -- Response: 200.00  Turnaround 400.00  Wait 200.00
```

## Question 2

Now do the same but with jobs of different lengths: 100, 200, and 300.

**Answer:**

```
FIFO:
Turnaround: 300, 500, 600 -> avg 466.6
Response: 0, 300, 500 -> avg 266.6

SJF:
Turnaround: 100, 300, 600 -> avg 333.3
Response: 0, 100, 300 -> avg 133.3

Wait time is same as response for non-preemptive policies
```

Correct answer:

```bash
yakultbottle:04_cpu-sched$ python3 scheduler.py -l 300,200,100 -p FIFO -c
ARG policy FIFO
ARG jlist 300,200,100

** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 300.00 secs ( DONE at 300.00 )
  [ time 300 ] Run job 1 for 200.00 secs ( DONE at 500.00 )
  [ time 500 ] Run job 2 for 100.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 300.00  Wait 0.00
  Job   1 -- Response: 300.00  Turnaround 500.00  Wait 300.00
  Job   2 -- Response: 500.00  Turnaround 600.00  Wait 500.00

  Average -- Response: 266.67  Turnaround 466.67  Wait 266.67
```

```bash
yakultbottle:04_cpu-sched$ python3 scheduler.py -l 300,200,100 -p SJF -c
ARG policy SJF
ARG jlist 300,200,100

** Solutions **

Execution trace:
  [ time   0 ] Run job 2 for 100.00 secs ( DONE at 100.00 )
  [ time 100 ] Run job 1 for 200.00 secs ( DONE at 300.00 )
  [ time 300 ] Run job 0 for 300.00 secs ( DONE at 600.00 )

Final statistics:
  Job   2 -- Response: 0.00  Turnaround 100.00  Wait 0.00
  Job   1 -- Response: 100.00  Turnaround 300.00  Wait 100.00
  Job   0 -- Response: 300.00  Turnaround 600.00  Wait 300.00

  Average -- Response: 133.33  Turnaround 333.33  Wait 133.33
```

## Question 3

Now do the same, but also with the RR scheduler and a time-slice of 1.

**Answer:**

```
RR:
Turnaround: 600, 500, 300 -> avg 466.6
Response: 0, 1, 2 -> avg 1
Wait: 300, 300, 200 -> 266.6
```

Correct answer:

```bash
yakultbottle:04_cpu-sched$ python3 scheduler.py -l 300,200,100 -p RR -q 1 -c
ARG policy RR
ARG jlist 300,200,100

** Solutions **

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 600.00  Wait 300.00
  Job   1 -- Response: 1.00  Turnaround 500.00  Wait 300.00
  Job   2 -- Response: 2.00  Turnaround 300.00  Wait 200.00

  Average -- Response: 1.00  Turnaround 466.67  Wait 266.67
```

## Question 4

For what types of workloads does SJF deliver the same turnaround times as FIFO?

**Answer:**

When the best case scenario happens for FIFO, shortest jobs come first. eg 100,
200, 300. That or jobs are all equal length

## Question 5

For what types of workloads and quantum lengths does SJF deliver the same
response times as RR?

**Answer:**

Since SJF will never preempt, it is basically a worst case response time when
compared to RR. As such, the quantum length for RR needs to be as long as the
longest job (ignoring the last job), such that RR acts like SJF.

## Question 6

What happens to response time with SJF as job lengths increase? Can you use the
simulator to demonstrate the trend?

**Answer:**

Response time with SJF will increase, since it has to run jobs to completion.

```bash
yakultbottle:04_cpu-sched$ python3 scheduler.py -l 300,200,100 -p SJF -c
ARG policy SJF

** Solutions **

Final statistics:
  Job   2 -- Response: 0.00  Turnaround 100.00  Wait 0.00
  Job   1 -- Response: 100.00  Turnaround 300.00  Wait 100.00
  Job   0 -- Response: 300.00  Turnaround 600.00  Wait 300.00

  Average -- Response: 133.33  Turnaround 333.33  Wait 133.33

yakultbottle:04_cpu-sched$ python3 scheduler.py -l 600,400,200 -p SJF -c
ARG policy SJF

** Solutions **

Final statistics:
  Job   2 -- Response: 0.00  Turnaround 200.00  Wait 0.00
  Job   1 -- Response: 200.00  Turnaround 600.00  Wait 200.00
  Job   0 -- Response: 600.00  Turnaround 1200.00  Wait 600.00

  Average -- Response: 266.67  Turnaround 666.67  Wait 266.67
```

## Question 7

What happens to response time with RR as quantum lengths increase? Can you write
an equation that gives the worst-case response time, given N jobs?

**Answer:**

Response time increases linearly with quantum length, until it is longer than
the job length.

Let's say that the quantum length is Q. Then, the equation should be:

For the single job with the worst response time:
(N - 1) * Q
For the overall average response time:
((N - 1) * Q / 2)
