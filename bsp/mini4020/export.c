#include <rtthread.h>
#include <finsh.h>

void testkkkk(void)
{
	rt_kprintf("Hello wangmengmeng!\n");	
	return;
}
FINSH_FUNCTION_EXPORT(testkkkk,a test);
