#include <rtthread.h>
#include <rtm.h>

void function1(void)
{
	rt_kprintf("Hello RT-Thread function1\n");
}

void function2(void)
{
	rt_kprintf("Hello RT-Thread function2\n");
}

void function3(void)
{
	rt_kprintf("Hello RT-Thread function3\n");
}

void function4(void)
{
	rt_kprintf("Hello RT-Thread function4\n");
}

void function5(void)
{
	rt_kprintf("Hello RT-Thread function5\n");
}

RTM_EXPORT(function1)
RTM_EXPORT(function2)
RTM_EXPORT(function3)
RTM_EXPORT(function4)
RTM_EXPORT(function5)