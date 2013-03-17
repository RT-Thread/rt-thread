#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

struct rt_irq_desc {
	char irq_name[RT_NAME_MAX];
	rt_isr_handler_t isr_handle;
	void *param;
	rt_uint32_t interrupt_cnt;
};

#endif