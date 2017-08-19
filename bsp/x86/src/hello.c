
#include <stdio.h>

int main(int argc, char* argv[])
{
	int i;
	char str[32] = "Hello World\n";

	for(i=0; i<argc; i++)
	{
		printf("argv[%d]='%s'\n", i, argv[i]);
	}

	printf(str);

	return 0xdeadbeef;
}

