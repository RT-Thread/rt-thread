#include <stdio.h>
#include <rthw.h>
#include <rtdevice.h>
#include "board.h"
#include <rtthread.h>

/* led thread entry */
#define PINRX 22
#define PINTX 21
void led_thread_entry(void* parameter)
{
    rt_pin_mode(PINRX, GPIO_MODE_OUTPUT_PP);
    rt_pin_mode(PINTX, GPIO_MODE_OUTPUT_PP);
    rt_pin_write(PINRX,1);
    rt_pin_write(PINTX,0);
	while(1)
	{
        rt_thread_delay(RT_TICK_PER_SECOND);
        rt_pin_write(PINRX,rt_pin_read(PINRX)?0:1);
        rt_pin_write(PINTX,rt_pin_read(PINTX)?0:1);
	}
}
