/*
 * contextPatch.c
 *
 *  Created on: 2018年1月11日
 *      Author: Administrator
 */
#include <rtthread.h>
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrput_flag;
extern void rt_frist_switch(void);
void rt_hw_context_switch(rt_uint32_t from, rt_uint32_t to)
{
	//rt_thread_switch_interrput_flag=1; rt_thread_switch_interrput_flag只有在中断中才可以设置为1
	rt_interrupt_from_thread=from;
	rt_interrupt_to_thread=to;
	asm("se_sc");
}

void rt_hw_context_switch_to(rt_uint32_t to)
{
	//rt_thread_switch_interrput_flag=1; rt_thread_switch_interrput_flag只有在中断中才可以设置为1
	rt_interrupt_from_thread=0;
	rt_interrupt_to_thread=to;
	rt_frist_switch();
}
void rt_hw_context_switch_interrupt(rt_uint32_t from, rt_uint32_t to)
{
	rt_thread_switch_interrput_flag=1;
	rt_interrupt_from_thread=from;
	rt_interrupt_to_thread=to;
}

