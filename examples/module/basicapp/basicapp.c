#include <rtthread.h>

static int a = 0;
static int b = 1000000;
int c = 100;

static void function(int count1, int count2, int count3)
{
	rt_kprintf("Hello RT-Thread %d %d\n", count1, count2, count3);
}

int main(void)
{
	int i;

	rt_kprintf("application entry\n");
	rt_kprintf("[addr]a-0x%x,b-0x%x,c-0x%x\n", &a, &b, &c);
	rt_kprintf("[value]a-%d,b-%d,c-%d\n", a, b, c);
	
	for(i=0; i<100; i++)  
	{	
		a++;
		b--;
		c++;
		function(a, c, b );
	}
 
	return 0;
}

