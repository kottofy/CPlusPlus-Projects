README.txt

Author: Kristin Ottofy
Date: July 12, 2010
Program Name: linklist

This program will take an input of numbers, stopping when the user types 0. It 
will then do a series of functions. First, it will print the numbers as a list, 
wait for the user to enter another number, append that number to the list , and 
print the list with the addition. Next, the program will reverse the list of 
numbers, including the appended number, and print out the list in reverse. 
After, it will wait for the user to enter another number, then search through 
the list and delete all numbers in the list that are the same as the inputted 
number. It will print the new list without the matched numbers. Next, the 
program will reverse the list, print the newly reversed list, wait for the user
to enter another nuber, then append the inputted number to the end of the list, 
and print the list. Finally, the program will sort through the list and print 
the list in order from smallest value to largest.

To run this program:
      Note: A complete sample run is available below
Step 1: Make sure you are in the directory above the files linklist.c, 
linklistlib.c, linklist.h, and Makefile.
Step 2: Compile the program by typing "make all" followed by the enter button.
Step 3: Run the program by typing "./simplelist" followed by the enter button.

Now the program will wait for you to enter a series of numbers, each followed by 
the enter button. When you are done inputting numbers, type 0 followed by the 
enter button.
Ex. 	*input entered by the user is denoted by "<-input"
1	<-input
2	<-input
3	<-input
4	<-input	
5	<-input
0	<-input
before sort
List Start:
5 4 3 2 1 
List End.

Now the program is waiting for you to enter another number. After you enter 
another number, hit the enter button, and the program will append and reverse 
the list.
Ex. 	*input entered by the user is denoted by "<-input"
9	<-input
after 1st append
List Start:
5 4 3 2 1 9 
List End.
after 1st reverse
List Start:
9 1 2 3 4 5 
List End.

Now the program is waiting for you to enter another number followed by the enter 
button. The program will then delete all numbers in the list that match the 
inputted number, reverse the list, and print out the reversed list.

3	<-input
after 1st delete
List Start:
9 1 2 4 5 
List End.
after 2nd reverse
List Start:
5 4 2 1 9 
List End.

Now the program is waiting for you to enter another number, followed by the enter
button. The program will then append that number to the list and print the list.
Finally the list will be sorted and print, and the program will end.

after 2nd append
List Start:
5 4 2 1 9 3 
List End.

after sort
List Start:
1 2 3 4 5 9 
List End.


Complete sample run:
*input entered by the user is denoted by "<-input"

1	<-input
2	<-input
3	<-input
4	<-input	
5	<-input
0	<-input
before sort
List Start:
5 4 3 2 1 
List End.
9	<-input
after 1st append
List Start:
5 4 3 2 1 9 
List End.
after 1st reverse
List Start:
9 1 2 3 4 5 
List End.
3	<-input
after 1st delete
List Start:
9 1 2 4 5 
List End.
after 2nd reverse
List Start:
5 4 2 1 9 
List End.
after 2nd append
List Start:
5 4 2 1 9 3 
List End.

after sort
List Start:
1 2 3 4 5 9 
List End.
odin:505$ 

