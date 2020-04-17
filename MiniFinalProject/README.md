## EECS3221-Z Final Project
**Out:** April 17, 2020 at 00:00  
**Due:** April 19, 2020 at 23:59

### Description
Write a program in `C` language that implements the following disk-scheduling algorithms: 
1. FCFS   
2. SCAN 
3. C-SCAN

These algorithms have been explained in the OSC book, sections `11.2.1`, `11.2.2` and, `11.2.3`, respectively.

Your program will service a disk with 100 cylinders numbered 0 to 99. 
The program will read a random series of 25 unique cylinder requests from a file called `input.txt` and service 
them according to each of the algorithms listed above. The program will be passed the initial position of the disk head and 
write the seek sequence and the total amount of head movement required by each algorithm in a file called 
`output.txt`. 

The two files provided here serve as a sample input and the correct corresponding output. You may use these two 
files to test your program. Note that your program will be tested with different `input.txt` files when grading. 

#### Hints
1. Assume that the *initial head position* is always 33. 
2. In SCAN algorithm, assume that the disk arm is moving toward 0 from the initial head position.
3. In C_SCAN algorithm, assume that the disk arm is moving toward 99 from the initial head position.
4. Your program should produce the `output.txt` with the same format as the sample file provided here.

### Submission and Evaluation 
You need to submit your `C source code`, `input.txt`, `output.txt` and a `Makefile` that compiles your code in one 
zip file. Please make sure not to submit any other files such as object files, etc. Also, note that 
if we cannot `make` your project on the OSC virtual machine, eg. compilation error, the grade will be 0. 
The following table shows the grading schema.

| Item        | Mark           |
| ------------- |:-------------:|
| FCFS Algorithm      | 5 |
| SCAN Algorithm      | 10 |
| C_SCAN Algorithm    | 10 |
| **Sum**             | **25** | 