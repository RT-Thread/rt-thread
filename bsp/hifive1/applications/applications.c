#include <rtthread.h>

static void rt_init_thread_entry(void* parameter)
{
#ifdef RT_USING_COMPONENTS_INIT
    /* initialization RT-Thread Components */
    rt_components_init();
#endif
    rt_thread_delay( RT_TIMER_TICK_PER_SECOND*2 ); /* sleep 0.5 second and switch to other thread */
}
#include <encoding.h>
#include <platform.h>
static void led_thread_entry(void* parameter)
{
    unsigned int count=0;

    rt_hw_led_init();
    while (0)
    {
/*        rt_hw_led_on(0);*/
        rt_thread_delay( RT_TIMER_TICK_PER_SECOND/2 ); /* sleep 0.5 second and switch to other thread */

        /* led1 off */
        rt_hw_led_off(0);

        rt_thread_delay( RT_TIMER_TICK_PER_SECOND*2);
    }
}
static rt_uint8_t led_stack[ 1024];
static struct rt_thread led_thread;
void rt_application_init()
{
    rt_thread_t init_thread;

    rt_err_t result;
	/* init led thread */
	result = rt_thread_init(&led_thread,
			"led",
			led_thread_entry,
			RT_NULL,
			(rt_uint8_t*)&led_stack[0],
			sizeof(led_stack),
			20,
			5);
	if (result == RT_EOK)
	{
		rt_thread_startup(&led_thread);
	}

	init_thread = rt_thread_create("init",
			rt_init_thread_entry,
		       	RT_NULL,
			512,
		       	8,
		       	20);
	if (init_thread != RT_NULL)
		rt_thread_startup(init_thread);
	return;
}
