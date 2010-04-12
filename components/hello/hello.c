#include <rtthread.h>

static int a = 0;
int b = 1000000;

void function(int count1, int count2)
{
	rt_kprintf("Hello RT-Thread %d %d\n", count1, count2);
}

int rtm_main(void)
{
	int i;
	for(i=0; i<1000; i++) 
	{	
		a++;
		b--;
		function(a, b);
	}

	return 0;
}
