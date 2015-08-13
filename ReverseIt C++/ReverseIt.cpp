/*
 Author: Kristin Ottofy
 Date: June 29, 2010
 Program Name: ReverseIt
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fcntl.h>

using namespace std;

int main (int argc, char *argv[])
{
	int fd1, fd2;	//fd1 will be the source file, fd2 will be the destination file
	int fileEnd;	//fileEnd will be set to 
	int readInt;	//readInt is used to determine if reading the file creates an error
	
	//check to make sure user has entered right number of parameters
	if(argc < 2)
    {
		printf("Not enough parameters.\n");
		exit(3);
    }
	
	//open the source file and check for error
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0)
    {
		perror("open source file failed because: ");
		exit(4);
    }
	
	//open the destination file and check for error
	fd2 = open(argv[2], O_CREAT|O_WRONLY, 0677);
	if(fd2 < 0)
    {
		perror("open destination file failed because: ");
		exit(5);
    }
	
	//count how many bytes in source file to set size of buf1
	fileEnd = lseek(fd1, 0, SEEK_END);	
		
	//initialize buf1 to size of source file
	char buf1[fileEnd];	
	
	//set cursor back to beginning so read reads from beginning of file
	lseek(fd1, 0, SEEK_SET);		
	
	//read form source file
	readInt = read(fd1, buf1, fileEnd);
	
	//check end of file
	if (readInt <= 0)
	{
		perror("read problem is: ");
		exit(6);
	}
	else	//else if there is no read errors
	{          
		//counts how many bytes from beg minus EOF
		int countDown = lseek(fd1,-1,SEEK_END); 
		
		//buf2 will be used to write the destination file
		char buf2[fileEnd];		//set to fileEnd which is how many bytes are in the source file
		
		//countUp will be used in buf2
		int countUp = 0;	
		
		//c will be used to count how many 100 byte chunks are in the source file, C is Roman Numeral for 100
		int  c = 0;			
		
		//in each loop subtract 100 from total bytes in source file, count how many 100 byte chunks
		while(fileEnd >= 100) 
	    {
			fileEnd = fileEnd -100;
			c++;
	    }
		
		//offset fileEnd by -1 to avoid the EOF byte
		fileEnd = lseek(fd1, -1, SEEK_END);
		
		//breaking up the source file into 100 byte chunks
		while (c > 0) 
	    {
			//copy character of buf1 to buf2 backwards in 100 byte chunk
			while (countDown > fileEnd - 100)
			{
				buf2[countUp]=buf1[countDown];
				countDown--;
				countUp++;
			}
			
			//subract 1 from c since the program just went through the last set of 100
			c--;	
			
			//subtract 100 from fileEnd so that the loop will copy characters of the next lower set of 100
			fileEnd = fileEnd -100;
	    }
		
		//for the remaining bytes (less than 100), copy buf1 characters to buf2 from where last left off
		while(countDown >= 0)
	    {
			buf2[countUp] = buf1[countDown];
			countDown--; 
			countUp++;
	    }
		
		//reset fileEnd to total bytes of source file to set to the number of bytes needed for the destination file
		fileEnd = lseek(fd1, 0, SEEK_END);
		
		//write buf2 to the destination file
		write(fd2, buf2 ,fileEnd);
		
		//close both files
		close(fd1);
		close(fd2);
	}
}
