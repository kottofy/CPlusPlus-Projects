Author: Kristin Ottofy
Date: May 1, 2011
Project: kottofyGraph



          HOW TO
___________________________________
To compile this program, type "make"

To run this program type "./RRM.out"

The program will then prompt you for a file name that contains the RRM.
2 files have been provided. "rrm.txt" contains the RRM from the Assignment
Requirements page. "rrm2.txt" is a file that contains an easy route to a 
deadlock. 

After giving the program the file, it will reprint the RRM contained in the
file.

Press 'q' or 'Q' where it prompts for the 'R' or 'r' request to quit. 

Then, type "R 1 2" to request that process 1 requests resource 2, for example.
The program is also set up to handle multiple requests such as:
"R 0 0 R 1 1 R 2 2 R 3 3 R 4 4 R 5 5 R 6 6 R 7 7 R 8 8 R 9 9 Q"

NOTE: Processes and Resources range form 0-9, NOT 1-10.

When typing 'Q', the program will display the Wait Table, then quit.



         SAMPLE RUN
-----------------------------------
odin:226$ ./RRM.out 

Input the filename of the RRM: 
rrm.txt

Resource Requirement Matrix
  0 1 2 3 4 5 6 7 8 9 
---------------------
0 1 1 1 1 1 1 1 1 1 1
1 1 0 1 1 1 0 0 0 1 0
2 1 1 0 0 0 0 0 0 0 0
3 1 1 0 0 0 0 0 0 0 0
4 1 1 1 1 1 0 0 0 1 1
5 0 0 0 0 0 1 1 1 0 1
6 0 0 0 1 0 1 0 1 1 1
7 0 0 0 1 1 1 1 0 0 0
8 1 1 1 1 1 1 1 1 1 1
9 0 1 1 1 0 0 0 1 1 1

ENTER 'Q' TO QUIT

Please enter "R" and a process (0-9) and a resource (0-9): 
> r 0 4
Process 0 is requesting allocation of resource 4
Resource is currently not in use. Attempting to allocate...
Allocation Successful!
Please enter "R" and a process (0-9) and a resource (0-9): 
> r 4 4
Process 4 is requesting allocation of resource 4
Resource is already in use
Trying to add to wait table...
Process 4 is waiting on resource 4
Please enter "R" and a process (0-9) and a resource (0-9): 
> r 8 8
Process 8 is requesting allocation of resource 8
Resource is currently not in use. Attempting to allocate...
Allocation Successful!
Please enter "R" and a process (0-9) and a resource (0-9): 
> q

Wait Table: 
Resource  |  Process
--------------------
    4     |     4
Goodbye!
