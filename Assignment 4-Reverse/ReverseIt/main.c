/*
 Author: Kristin Ottofy
 Date June 29, 2010
 Program Name: ReverseIt
 */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int BUFSIZE = 4096;
	char buf[BUFSIZE];
	int fd1, fd2;
	int i, n, j, m;
	int fileEnd;
	
	if (argc < 3)
    {
		printf("Not enough parameters.\n");
		exit(3);
    }
	
	//open the source file
	fd1 = open(argv[1], O_RDONLY);
	
	if(fd1<0)
    {
		perror("open source failed because: ");
		exit(4);
    }
	
	// open the destination file
	fd2 = open(argv[2], O_CREAT|O_WRONLY);
	
	if(fd2<0)
    {
		perror("open destination failed because: ");
		exit(4);
    }

	n = BUFSIZE;
	
	/*
     if (i<0)
	 {
	 perror("read problem ");
	 exit(5);
	 }
	 
	 i = write(fd2, buf, i);
	 if (i<0)
	 {
	 perror("write problem ");
	 exit(6);
	 }
	 */
	
	while (fileEnd == 0)
		{
			//read from source
			i = read(fd1, buf, n);
	
			//check end of file
			if (i <= 0)
				fileEnd = 1;
			else
			{
				//write to destination, but make sure consider:
				// the return of write could be smaller than i
				m = 0;
				while (m < i)
				{
					j = 0;
					j = write(fd2, (buf + m), i);
					m = m+j;
				}
			}
	 }
	 
	
	//for ()
    {
		
    }
	
	//close both files
	close(fd1);
	close(fd2);
}
