# Homework 5 Multi-Level Feedback Queue

## Question 1

Run a few randomly-generated problems with just two jobs and two queues; compute
the MLFQ execution trace for each. Make your life easier by limiting the length
of each job and turning off I/Os.

**Answer:**

```bash
yakultbottle:05_cpu-sched-mlfq$ python3 mlfq.py -n 2 -j 2 -m 20 -M 100000 -s 1
Here is the list of inputs:
OPTIONS jobs 2
OPTIONS queues 2
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is  10
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  10
OPTIONS boost 0
OPTIONS ioTime 5
OPTIONS stayAfterIO False
OPTIONS iobump False


For each job, three defining characteristics are given:
  startTime : at what time does the job enter the system
  runTime   : the total CPU time needed by the job to finish
  ioFreq    : every ioFreq time units, the job issues an I/O
              (the I/O takes ioTime units to complete)

Job List:
  Job  0: startTime   0 - runTime   3 - ioFreq 84743
  Job  1: startTime   0 - runTime  15 - ioFreq 25507

Compute the execution trace for the given workloads.
If you would like, also compute the response and turnaround
times for each of the jobs.

Use the -c flag to get the exact results when you are finished.
```

Predicted: Job 0 runs to completion then Job 1 runs twice(length > allotment)

```bash
Execution Trace:

[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] JOB BEGINS by JOB 1
[ time 0 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 2 (of 3) ]
[ time 1 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 1 (of 3) ]
[ time 2 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 0 (of 3) ]
[ time 3 ] FINISHED JOB 0
[ time 3 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 14 (of 15) ]
[ time 4 ] Run JOB 1 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 13 (of 15) ]
[ time 5 ] Run JOB 1 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 12 (of 15) ]
[ time 6 ] Run JOB 1 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 11 (of 15) ]
[ time 7 ] Run JOB 1 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 10 (of 15) ]
[ time 8 ] Run JOB 1 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 9 (of 15) ]
[ time 9 ] Run JOB 1 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 8 (of 15) ]
[ time 10 ] Run JOB 1 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 7 (of 15) ]
[ time 11 ] Run JOB 1 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 6 (of 15) ]
[ time 12 ] Run JOB 1 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 5 (of 15) ]
[ time 13 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 4 (of 15) ]
[ time 14 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 3 (of 15) ]
[ time 15 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 2 (of 15) ]
[ time 16 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 1 (of 15) ]
[ time 17 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 0 (of 15) ]
[ time 18 ] FINISHED JOB 1

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround   3
  Job  1: startTime   0 - response   3 - turnaround  18

  Avg  1: startTime n/a - response 1.50 - turnaround 10.50
```

## Question 2

How would you run the scheduler to reproduce each of the examples in the
chapter?

**Answer:**

Example 1: Long running job

```bash
yakultbottle:05_cpu-sched-mlfq$ python3 mlfq.py -n 3 -j 1 -m 1000 -M 100000 -s 1 -c
Here is the list of inputs:
OPTIONS jobs 1
OPTIONS queues 3
OPTIONS allotments for queue  2 is   1
OPTIONS quantum length for queue  2 is  10
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is  10
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  10
...
...

Job List:
  Job  0: startTime   0 - runTime 135 - ioFreq 84743

Execution Trace:

[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 134 (of 135) ]
[ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 133 (of 135) ]
[ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 132 (of 135) ]
[ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 131 (of 135) ]
[ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 130 (of 135) ]
[ time 5 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 129 (of 135) ]
[ time 6 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 128 (of 135) ]
[ time 7 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 127 (of 135) ]
[ time 8 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 126 (of 135) ]
[ time 9 ] Run JOB 0 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 125 (of 135) ]
[ time 10 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 124 (of 135) ]
[ time 11 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 123 (of 135) ]
[ time 12 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 122 (of 135) ]
[ time 13 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 121 (of 135) ]
[ time 14 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 120 (of 135) ]
[ time 15 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 119 (of 135) ]
[ time 16 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 118 (of 135) ]
[ time 17 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 117 (of 135) ]
[ time 18 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 116 (of 135) ]
[ time 19 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 115 (of 135) ]
[ time 20 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 114 (of 135) ]
[ time 21 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 113 (of 135) ]
[ time 22 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 112 (of 135) ]
[ time 23 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 111 (of 135) ]
[ time 24 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 110 (of 135) ]
...
[ time 130 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 4 (of 135) ]
[ time 131 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 3 (of 135) ]
[ time 132 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 2 (of 135) ]
[ time 133 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 1 (of 135) ]
[ time 134 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 0 (of 135) ]
[ time 135 ] FINISHED JOB 0
```

Example 2: Short interactive job

```bash
yakultbottle:05_cpu-sched-mlfq$ python3 mlfq.py -l 0,200,10000:100,15,10000 -c
Here is the list of inputs:
OPTIONS jobs 2
OPTIONS queues 3
OPTIONS allotments for queue  2 is   1
OPTIONS quantum length for queue  2 is  10
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is  10
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  10
...

Job List:
  Job  0: startTime   0 - runTime 200 - ioFreq 10000
  Job  1: startTime 100 - runTime  15 - ioFreq 10000


Execution Trace:

[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 199 (of 200) ]
[ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 198 (of 200) ]
[ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 197 (of 200) ]
[ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 196 (of 200) ]
[ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 195 (of 200) ]
[ time 5 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 194 (of 200) ]
[ time 6 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 193 (of 200) ]
[ time 7 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 192 (of 200) ]
[ time 8 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 191 (of 200) ]
[ time 9 ] Run JOB 0 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 190 (of 200) ]
[ time 10 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 189 (of 200) ]
[ time 11 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 188 (of 200) ]
[ time 12 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 187 (of 200) ]
[ time 13 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 186 (of 200) ]
[ time 14 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 185 (of 200) ]
[ time 15 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 184 (of 200) ]
[ time 16 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 183 (of 200) ]
[ time 17 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 182 (of 200) ]
[ time 18 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 181 (of 200) ]
[ time 19 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 180 (of 200) ]
[ time 20 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 179 (of 200) ]
[ time 21 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 178 (of 200) ]
[ time 22 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 177 (of 200) ]
[ time 23 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 176 (of 200) ]
...
[ time 96 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 103 (of 200) ]
[ time 97 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 102 (of 200) ]
[ time 98 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 101 (of 200) ]
[ time 99 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 100 (of 200) ]
[ time 100 ] JOB BEGINS by JOB 1
[ time 100 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 14 (of 15) ]
[ time 101 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 13 (of 15) ]
[ time 102 ] Run JOB 1 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 12 (of 15) ]
[ time 103 ] Run JOB 1 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 11 (of 15) ]
[ time 104 ] Run JOB 1 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 10 (of 15) ]
[ time 105 ] Run JOB 1 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 9 (of 15) ]
[ time 106 ] Run JOB 1 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 8 (of 15) ]
[ time 107 ] Run JOB 1 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 7 (of 15) ]
[ time 108 ] Run JOB 1 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 6 (of 15) ]
[ time 109 ] Run JOB 1 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 5 (of 15) ]
[ time 110 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 4 (of 15) ]
[ time 111 ] Run JOB 1 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 3 (of 15) ]
[ time 112 ] Run JOB 1 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 2 (of 15) ]
[ time 113 ] Run JOB 1 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 1 (of 15) ]
[ time 114 ] Run JOB 1 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 0 (of 15) ]
[ time 115 ] FINISHED JOB 1
[ time 115 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 99 (of 200) ]
[ time 116 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 98 (of 200) ]
[ time 117 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 97 (of 200) ]
[ time 118 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 96 (of 200) ]
[ time 119 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 95 (of 200) ]
...
[ time 210 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 4 (of 200) ]
[ time 211 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 3 (of 200) ]
[ time 212 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 2 (of 200) ]
[ time 213 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 1 (of 200) ]
[ time 214 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 0 (of 200) ]
[ time 215 ] FINISHED JOB 0

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround 215
  Job  1: startTime 100 - response   0 - turnaround  15

  Avg  1: startTime n/a - response 0.00 - turnaround 115.00
```

Example 3: I/O intensive + CPU intensive

```bash
yakultbottle:05_cpu-sched-mlfq$ python3 mlfq.py -l 0,100,5:0,200,10000 -c -S
Here is the list of inputs:
OPTIONS jobs 2
OPTIONS queues 3
OPTIONS allotments for queue  2 is   1
OPTIONS quantum length for queue  2 is  10
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is  10
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  10
...

Job List:
  Job  0: startTime   0 - runTime 100 - ioFreq   5
  Job  1: startTime   0 - runTime 200 - ioFreq 10000


Execution Trace:

[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] JOB BEGINS by JOB 1
[ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 99 (of 100) ]
[ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 98 (of 100) ]
[ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 97 (of 100) ]
[ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 96 (of 100) ]
[ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 95 (of 100) ]
[ time 5 ] IO_START by JOB 0
IO DONE
[ time 5 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 199 (of 200) ]
[ time 6 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 198 (of 200) ]
[ time 7 ] Run JOB 1 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 197 (of 200) ]
[ time 8 ] Run JOB 1 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 196 (of 200) ]
[ time 9 ] Run JOB 1 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 195 (of 200) ]
[ time 10 ] IO_DONE by JOB 0
[ time 10 ] Run JOB 1 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 194 (of 200) ]
[ time 11 ] Run JOB 1 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 193 (of 200) ]
[ time 12 ] Run JOB 1 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 192 (of 200) ]
[ time 13 ] Run JOB 1 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 191 (of 200) ]
[ time 14 ] Run JOB 1 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 190 (of 200) ]
[ time 15 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 94 (of 100) ]
[ time 16 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 93 (of 100) ]
[ time 17 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 92 (of 100) ]
[ time 18 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 91 (of 100) ]
[ time 19 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 90 (of 100) ]
[ time 20 ] IO_START by JOB 0
IO DONE
[ time 20 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 189 (of 200) ]
[ time 21 ] Run JOB 1 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 188 (of 200) ]
[ time 22 ] Run JOB 1 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 187 (of 200) ]
[ time 23 ] Run JOB 1 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 186 (of 200) ]
[ time 24 ] Run JOB 1 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 185 (of 200) ]
[ time 25 ] IO_DONE by JOB 0
[ time 25 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 89 (of 100) ]
[ time 26 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 88 (of 100) ]
[ time 27 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 87 (of 100) ]
[ time 28 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 86 (of 100) ]
[ time 29 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 85 (of 100) ]
[ time 30 ] IO_START by JOB 0
IO DONE
...
[ time 190 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 104 (of 200) ]
[ time 191 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 103 (of 200) ]
[ time 192 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 102 (of 200) ]
[ time 193 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 101 (of 200) ]
[ time 194 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 100 (of 200) ]
[ time 195 ] IO_DONE by JOB 0
[ time 195 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 4 (of 100) ]
[ time 196 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 3 (of 100) ]
[ time 197 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 2 (of 100) ]
[ time 198 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 1 (of 100) ]
[ time 199 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 0 (of 100) ]
[ time 200 ] FINISHED JOB 0
[ time 200 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 99 (of 200) ]
[ time 201 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 98 (of 200) ]
[ time 202 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 97 (of 200) ]
[ time 203 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 96 (of 200) ]
[ time 204 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 95 (of 200) ]
...
[ time 296 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 3 (of 200) ]
[ time 297 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 2 (of 200) ]
[ time 298 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 1 (of 200) ]
[ time 299 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 0 (of 200) ]
[ time 300 ] FINISHED JOB 1

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround 200
  Job  1: startTime   0 - response   5 - turnaround 300

  Avg  1: startTime n/a - response 2.50 - turnaround 250.00
```

## Question 3

How would you configure the scheduler parameters to behave just like a
round-robin scheduler?

**Answer:**

I would use one queue, and set the quantum to what I desired.

```bash
python3 mlfq.py -n 1 -q 5
```

## Question 4

Craft a workload with two jobs and scheduler parameters so that one job takes
advantage of the older Rules 4a and 4b (turned on with the -S flag) to game the
scheduler and obtain 99% of the CPU over a particular time interval.

```bash
yakultbottle:05_cpu-sched-mlfq$ python3 mlfq.py -l 0,1000,99:0,1000,10000 -q 100 -S -c
Here is the list of inputs:
OPTIONS jobs 2
OPTIONS queues 3
OPTIONS allotments for queue  2 is   1
OPTIONS quantum length for queue  2 is 100
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is 100
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is 100
...

Job List:
  Job  0: startTime   0 - runTime 1000 - ioFreq  99
  Job  1: startTime   0 - runTime 1000 - ioFreq 10000

...

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround 1145
  Job  1: startTime   0 - response  99 - turnaround 2000

  Avg  1: startTime n/a - response 49.50 - turnaround 1572.50
```

Failed a little bit, I was monopolising the CPU, but more like 99-5 rather than
actually 99%. This is half because the job getting ignored never got downgraded
to the lowest, but also because it seemed to queue the other job for the
duration of the I/O? Based on the logs I thought I/O was actually 0 length long.
So anyway I need to do explicitly set I/0 length to 1:

```bash
yakultbottle:05_cpu-sched-mlfq$ python3 mlfq.py -l 0,1000,99:0,1000,10000 -q 100 -i 1 -S -c
```

## Question 5

Given a system with a quantum length of 10 ms in its highest queue, how often
would you have to boost jobs back to the highest priority level (with the -B
flag) in order to guarantee that a single long running (and potentially
starving) job gets at least 5% of the CPU?

**Answer:**

If there is a single long running job with a boost option by the scheduler, then
what will happen is that from a low priority, it gets boosted, runs the full
length of the quanta, and then gets downgraded again until the next boost.
Working backwards, this gives us 10ms being 5%, so 100% is 200ms.

## Question 6

One question that arises in scheduling is which end of a queue to add a job that
just finished I/O; the -I flag changes this behavior for this scheduling
simulator. Play around with some workloads and see if you can see the effect of
this flag.

**Answer:**

It depends. Let us assume that all jobs are currently in their "correct" queues,
ie I/O or short jobs in higher priority, and the system is currently swamped, so
there are multiple I/O jobs in a higher priority queue. Then, by placing these
at the front of the queue, you can try to get to the "next" I/O operation
sooner, increasing throughput. However, also possible is that you cut off
another I/O intensive job in the middle of the CPU, and increased switching
leads to increased overhead. Idk I'm just rambling

Addendum: It improves response time. I'm so stupid. But also, it definitely
comes at the tradeoff I pointed out, as response time always comes at the cost
of throughput also. Obviously for an I/O job response time is much more
critical.
