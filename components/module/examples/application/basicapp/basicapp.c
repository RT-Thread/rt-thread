#include <rtthread.h>
#include <interface_help.h>

int a = 0;
int b = 1000000;
int c = 0;

void function(int count1, int count2, int count3)
{
	rt_kprintf("Hello RT-Thread %d %d\n", count1, count2, count3);
}

int rt_application_entry(void)
{
	int i;
	for(i=0; i<1000; i++) 
	{	
		a++;
		b--;
		c++;
		function(a, b, c);
	}

	return 0;
}

