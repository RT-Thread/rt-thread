#include <rtthread.h>

int a = 0;
int b = 1000000;
int c = 0;

static void function(int count1, int count2, int count3)
{
	rt_kprintf("Hello RT-Thread %d %d\n", count1, count2, count3);
}

int rt_application_init(void)
{
	int i;
	rt_kprintf("application entry\n");
	for(i=0; i<100; i++)  
	{	
		a++;
		b--;
		c++;
		function(a, c, b );
	}
 
	return 0;
}

