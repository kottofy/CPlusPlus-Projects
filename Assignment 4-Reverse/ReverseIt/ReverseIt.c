/*
Author: Kristin Ottofy
Date: June 29, 2010
Program Name: ReverseIt
*/

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fcntl.h>

#define BUFSIZE 4096

using namespace std;

int main (int argc, char *argv[])
{
  int fd1, fd2;
  char buf1[BUFSIZE];
  int fileEnd;
  int n, i;

  if(argc != 3)
    {
      printf("Not enough parameters.\n");
      exit(3);
    }

  //open the source file
  fd1 = open(argv[1], O_RDONLY);

  if (fd1 < 0)
    {
      perror("open source file failed because: ");
      exit(4);
    }

  //open the destination file
  fd2 = open(argv[2], O_CREAT|O_WRONLY, 0677);

  if(fd2 < 0)
    {
      perror("open destination file failed because: ");
      exit(5);
    }

      //read form source file
      i = read(fd1, buf1, BUFSIZE);

      //check end of file
      if (i <= 0)
	{
	  perror("read problem is: ");
	  exit(6);
	}
      else
	{          
	  int countDown = lseek(fd1,-1,SEEK_END); //counts how many bytes from beg.
          fileEnd = countDown;
          char buf2[countDown];
          int countUp = 0;
          int x = 0;
	  while(fileEnd >= 100) //in each loop subtract 100 from total bytes in source file, count how many 100s, and set the remaining
	    {
	      fileEnd = fileEnd -100;
	      x++;
	    }

	  fileEnd = lseek(fd1, -1, SEEK_END);
	 
	  while (x > 0) //breaking up the source file into 100 byte chunks
	    {
	      while (countDown > fileEnd - 100)
		{
		  buf2[countUp]=buf1[countDown];
		  countDown--;
		  countUp++;
		}
	      x--;
	      fileEnd = fileEnd -100;
	    }

	  while(countDown >= 0)
	    {
       	      buf2[countUp] = buf1[countDown];
	      countDown--; countUp++;
	    }

	      write(fd2, buf2 ,i);
	}
	  // buf1 = source, buf2 = destination copy
	  // search buf1 to end of file, jump back 100 spaces
	  //copy in reverse from lseek end to lseek end-10 
	  //then repeat by lseek current to lseek curr-10
	  //if lseek curr is less than 100, then copy in reverse from lseek cur to lseek 0 (beg)
}
