
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std; 

void rot13(char *str);


int main(int argc, char ** argv )
{
  char buf[4096];
  int i;  

  if (argc < 2 )  {
	printf("Usage: %s e (for encode) or  %s d (for decode) \n", argv[0], argv[0]);
	exit(-1);
  }

  i=0;
  while (cin.get(buf[i]) && i<4095) {
        i++;
	if (cin.fail())
		break;	
  }
  
  buf[i]=0;
 
  switch (argv[1][0]) {
	case 'e':
	case 'd':
		rot13(buf);
		cout << buf; 
		break;
	default:
		printf("Usage: %s e (for encode) or  %s d (for decode) \n", argv[0], argv[0]);
  } 

}
