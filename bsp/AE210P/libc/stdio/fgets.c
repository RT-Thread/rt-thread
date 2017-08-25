#include "uart/uart.h"
#include "rtdef.h"
#include "rtthread.h"

#include <stdio.h>

__attribute__((used))
int fgetc(FILE *stream)
{
	int c;

	while (!drv_uart_is_kbd_hit()) {
		rt_thread_delay(1);
	}

	c = drv_uart_get_char();

	if (c == '\r')
		c = '\n';

	fputc(c, stream);

	return c;
}

__attribute__((used))
char *fgets(char *s, int size, FILE *stream)
{
	char *p = s;

	int i = 0;

	for (i = 0; i < size - 1; i++){

		int c = fgetc(stream);

		if(c == '\n'){

			*p++ = '\n';
			break;
		}
		else if(c == '\0'){

			break;
		}
		else if(c < 0){

			return (void*)0;
		}
		else{
			*p++ = c;
		}
	}

	*p = '\0';

	return s;
}

__attribute__((used))
int getc(FILE *stream)
{
	return fgetc(stream);
}

__attribute__((used))
int getchar(void)
{
	return fgetc((void*)0);
}

__attribute__((used))
int ungetc(int c, FILE *stream);
