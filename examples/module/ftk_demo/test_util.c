#include <stdio.h>

char* read_file(const char* file_name, int* length)
{
	struct stat st = {0};
	if(stat(file_name, &st))
	{
		return NULL;
	}
	else
	{
		char* buffer = malloc(st.st_size + 1);
		FILE* fp = fopen(file_name, "rb");
		fread(buffer, 1, st.st_size, fp);
		fclose(fp);
		buffer[st.st_size] = '\0';
		*length = st.st_size;

		return buffer;
	}
}
