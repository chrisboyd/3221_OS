Chris Boyd
216 869 356
York EECS 3221 W2020 Final Project

Compile
$ make

Run
$ ./disk_sched input.txt output.txt

Note: 
For the C-SCAN algorithm, in OSC 11.2.3 it states 

"When the head reaches the other end, however, it immediately returns to the
beginning of the disk without servicing any requests on the return trip."

I interpretted this to mean, that if the last request of the set is at
cylinder 99, the head immediately goes to 0 and counts that movement in the
total for the set of disk requests.
