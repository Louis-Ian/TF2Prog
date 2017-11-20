#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char c0 = 'D';
	int c1;// = atoi(c0);
	int c2;// = c0;

	//printf("C1: %d | C2: %d\n", c1,c2);

	if (c0 >= 'A' && c0 <= 'Z')
  		c1 = c0 - 'A';
	else if (c0 >= 'a' && c0 <= 'z')
  		c1 = c0 - 'a';

  	printf("C1: %d | C2: %d\n", c1,c2);

  	//GOD BLESS STACKOVERFLOW
	return 0;
}