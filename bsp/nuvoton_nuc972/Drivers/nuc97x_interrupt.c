/*
 * File      : nuc97x_interrupt.c
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/05/28     Urey         first implementation
 */
#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "nuc97x_conf.h"

#define SYS_MIN_INT_SOURCE       1
#define SYS_MAX_INT_SOURCE       62
#define SYS_NUM_OF_AICREG        16


extern rt_uint32_t rt_interrupt_nest;

rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

struct rt_irq_desc irq_desc[SYS_MAX_INT_SOURCE + 1];

void rt_hw_interrupt_dummy_handler(int vector, void *param)
{
    rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);

    RT_ASSERT(0);
}


rt_uint32_t rt_hw_interrupt_get_active(rt_uint32_t fiq_irq)
{
	rt_uint32_t volatile _mIPER, _mISNR;
	rt_uint32_t	active = 0;

    _mIPER = (inpw(REG_AIC_IPER) >> 2) & 0x3f;
    _mISNR = inpw(REG_AIC_ISNR);
    if ((_mISNR != 0) && (_mIPER == _mISNR))
    	active = _mISNR;

    return active;
}

void rt_hw_interrupt_ack(rt_uint32_t fiq_irq, rt_uint32_t id)
{
    outpw(REG_AIC_EOSCR, 1);
}


extern void Undef_Handler(void);
extern void SWI_Handler(void);
extern void PAbt_Handler(void);
extern void DAbt_Handler(void);
extern void IRQ_Handler(void);
extern void FIQ_Handler(void);

void rt_hw_interrupt_init()
{
	int i;

    *((volatile unsigned int *)REG_AIC_MDCR)=0xFFFFFFFF;  	// disable all interrupt channel
    *((volatile unsigned int *)REG_AIC_MDCRH)=0xFFFFFFFF;  	// disable all interrupt channel


    //re-install exception..
    {
        int i = 0;
        for (i = 0; i < 0x200; ++i) {
            *(unsigned int volatile *)(i * 4) = *(unsigned int volatile *)(0x80000 + i * 4);
        }
    }
//    *(unsigned int volatile *)0x24 = (unsigned int)Undef_Handler;
//    *(unsigned int volatile *)0x28 = (unsigned int)SWI_Handler;
//    *(unsigned int volatile *)0x2C = (unsigned int)PAbt_Handler;
//    *(unsigned int volatile *)0x30 = (unsigned int)DAbt_Handler;
//    *(unsigned int volatile *)0x38 = (unsigned int)IRQ_Handler;
//    *(unsigned int volatile *)0x3C = (unsigned int)FIQ_Handler;

    /* init interrupt nest, and context in thread sp */
    rt_interrupt_nest               = 0;
    rt_interrupt_from_thread        = 0;
    rt_interrupt_to_thread          = 0;
    rt_thread_switch_interrupt_flag = 0;

	for (i = 1; i <= SYS_MAX_INT_SOURCE; i++)
    {
    	rt_hw_interrupt_install(i,rt_hw_interrupt_dummy_handler,RT_NULL,(char *)"dummy");
    	rt_hw_interrupt_mask(i);
    }
}




rt_isr_handler_t rt_hw_interrupt_install(int vector,
										 rt_isr_handler_t handler, void *param,
										 char *name)
{
    rt_isr_handler_t 	old_handler = RT_NULL;
    rt_uint32_t  		_mRegAddr/*, _mRegValue*/;
    rt_uint32_t     	shift;

    if(vector > SYS_MAX_INT_SOURCE)
    	return RT_NULL;

    //set default priority IRQ_LEVEL_7
    _mRegAddr = REG_AIC_SCR1 + ((vector / 4) * 4);
    shift = (vector % 4) * 8;
    outpw(_mRegAddr, (inpw(_mRegAddr) & ~(0x07 << shift)) | (IRQ_LEVEL_7 << shift));

    old_handler = irq_desc[vector].handler;
    if(handler != RT_NULL)
    {
		irq_desc[vector].handler = (rt_isr_handler_t)handler;
		irq_desc[vector].param = param;
#ifdef RT_USING_INTERRUPT_INFO
            rt_snprintf(irq_desc[vector].name, RT_NAME_MAX - 1, "%s", name);
            irq_desc[vector].counter = 0;
#endif
    }

    return old_handler;
}

/* Disable interrupt */
void rt_hw_interrupt_mask(int vector)
{
    if ((vector > SYS_MAX_INT_SOURCE) || (vector < SYS_MIN_INT_SOURCE))
    	return;

    if (vector < 32)
        outpw(REG_AIC_MDCR, (1 << vector));
    else
        outpw(REG_AIC_MDCRH, (1 << (vector - 32)));
}

void rt_hw_interrupt_umask(int vector)
{
    if ((vector > SYS_MAX_INT_SOURCE) || (vector < SYS_MIN_INT_SOURCE))
        return;

    if (vector < 32)
        outpw(REG_AIC_MECR, (1 << vector));
    else
        outpw(REG_AIC_MECRH, (1 << (vector - 32)));
}

void rt_hw_interrupt_set_priority(int vector,int priority)
{
	rt_uint32_t  	_mRegAddr;
	rt_uint32_t 	shift;

    if ((vector > SYS_MAX_INT_SOURCE) || (vector < SYS_MIN_INT_SOURCE))
        return;

    _mRegAddr = REG_AIC_SCR1 + ((vector / 4) * 4);
    shift = (vector % 4) * 8;
    priority &= 0x7;
    outpw(_mRegAddr, (inpw(_mRegAddr) & ~(0x07 << shift)) | (priority << shift));
}

/* TYPE
 * 	#define LOW_LEVEL_SENSITIVE        0x00
 * 	#define HIGH_LEVEL_SENSITIVE       0x40
 * 	#define NEGATIVE_EDGE_TRIGGER      0x80
 * 	#define POSITIVE_EDGE_TRIGGER      0xC0
 */
void rt_hw_interrupt_set_type(int vector,int type)
{
	rt_uint32_t 	_mRegAddr;
	rt_uint32_t     shift;

    if ((vector > SYS_MAX_INT_SOURCE) || (vector < SYS_MIN_INT_SOURCE))
        return ;

    _mRegAddr = REG_AIC_SCR1 + ((vector / 4) * 4);
    shift = (vector % 4) * 8;
    type &= 0xC0;
    outpw(_mRegAddr, (inpw(_mRegAddr) & ~(0xC0 << shift)) | (type << shift));
}

