/*
 * File      : cpuport.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-23     Bernard      the first version
 * 2012-03-03     xuzhenglim   modify for rx62N
 */
#include <rthw.h>
#include <rtthread.h>

#include "cpuconfig.h"

#include "machine.h"
#include "iorx62n.h"

#define ENTER_INTERRUPT()  ICU.SWINTR.BIT.SWINT = 1;

extern volatile rt_uint8_t rt_interrupt_nest;


/* switch flag on interrupt and thread pointer to save switch record */
rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;


/* stack frame*/
struct stack_frame
{
    rt_uint32_t ACCLO; 
    rt_uint32_t ACCHI;
    rt_uint32_t FPSW;   
    rt_uint32_t R1;
    rt_uint32_t R2;
    rt_uint32_t R3;
    rt_uint32_t R4;
    rt_uint32_t R5;
    rt_uint32_t R6;
    rt_uint32_t R7;
    rt_uint32_t R8;
    rt_uint32_t R9;
    rt_uint32_t R10;
    rt_uint32_t R11;
    rt_uint32_t R12;
    rt_uint32_t R13;
    rt_uint32_t R14;
    rt_uint32_t R15;
    //there is not R0 register,it is special for stack pointer
    rt_uint32_t PC;  
    rt_uint32_t PSW; 
};

/**
 * Initilial the threah stack.
 * 
 * @author LXZ (2014/11/8)
 * 
 * @param void* tentry       
 * @param void* parameter    
 * @param rt_uint8_t* stack_addr 
 * @param void* texit        
 * 
 * @return rt_uint8_t* 
 */
rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter,
                             rt_uint8_t *stack_addr, void *texit)
{
    unsigned long *stk;
    struct stack_frame *stack_frame;
    unsigned long       i;

    stk      = (unsigned long *)stack_addr;
    *(stk)   = (unsigned long)texit;        
    stack_frame = (struct stack_frame *)(stack_addr - sizeof(struct stack_frame)) ;

    //Initilial all register
    for (i = 0; i < sizeof(struct stack_frame) / sizeof(rt_uint32_t); i ++)
    {
        ((rt_uint32_t *)stack_frame)[i] = 0xdeadbeef;
    }
    
    stack_frame->PSW = (unsigned long)0x00030000 ;   /* psw */
    stack_frame->PC = (unsigned long)tentry;        /* thread entery*/
    stack_frame->R1 = (unsigned long )parameter;   /* r1 : parameter */
    stack_frame->FPSW = 0x00000100;                  /* fpsw */
    
    return(rt_uint8_t *)stack_frame;
}

#ifdef RT_USING_FINSH
extern void list_thread(void);
#endif
extern rt_thread_t rt_current_thread;
/**
 * deal exception 
 * 
 * @author LXZ (2014/11/8)
 * 
 * @param struct stack_frame* exception_contex 
 */
void rt_hw_hard_fault_exception(struct stack_frame* exception_contex)
{
    if (exception_contex != RT_NULL) {
        rt_kprintf("psw: 0x%08x\n", exception_contex->PSW); 
        rt_kprintf("pc: 0x%08x\n", exception_contex->PC);
        rt_kprintf("r0: 0x%08x\n", exception_contex->R1);
        rt_kprintf("r0: 0x%08x\n", exception_contex->R2);
        rt_kprintf("r0: 0x%08x\n", exception_contex->R3);
        rt_kprintf("r0: 0x%08x\n", exception_contex->R4);
        rt_kprintf("r0: 0x%08x\n", exception_contex->R5);
        rt_kprintf("r0: 0x%08x\n", exception_contex->R6);
        rt_kprintf("r0: 0x%08x\n", exception_contex->R7);
        rt_kprintf("r0: 0x%08x\n", exception_contex->R8);
        rt_kprintf("r0: 0x%08x\n", exception_contex->R9);
        rt_kprintf("r0: 0x%08x\n", exception_contex->R10);
        rt_kprintf("r0: 0x%08x\n", exception_contex->R11);
        rt_kprintf("r0: 0x%08x\n", exception_contex->R12);
        rt_kprintf("r0: 0x%08x\n", exception_contex->R13);
        rt_kprintf("r0: 0x%08x\n", exception_contex->R14);
        rt_kprintf("r0: 0x%08x\n", exception_contex->R15);
        rt_kprintf("fpsw: 0x%08x\n", exception_contex->FPSW);
        rt_kprintf("acchi: 0x%08x\n", exception_contex->ACCHI);
        rt_kprintf("acclo: 0x%08x\n", exception_contex->ACCLO);
    }
        rt_kprintf("hard fault on thread: %s\n", rt_current_thread->name);
    #ifdef RT_USING_FINSH
        list_thread();
    #endif
        while (1);
    
}


/**
 * switch thread in interrupt
 * 
 * @author LXZ (2014/11/8)
 * 
 * @param rt_uint32_t from 
 * @param rt_uint32_t to 
 */
void rt_hw_context_switch(rt_uint32_t from, rt_uint32_t to)
{
    if (rt_thread_switch_interrupt_flag == 0)
    {
        rt_thread_switch_interrupt_flag = 1;
        rt_interrupt_from_thread = from;
    }

    rt_interrupt_to_thread = to;
    ENTER_INTERRUPT();
}
/**
 * swithc thread out the interrupt
 * 
 * @author LXZ (2014/11/8)
 * 
 * @param rt_uint32_t from 
 * @param rt_uint32_t to 
 */
void rt_hw_context_switch_interrupt(rt_uint32_t from, rt_uint32_t to)
{
    if (rt_thread_switch_interrupt_flag == 0)
    {
        rt_thread_switch_interrupt_flag = 1;
        rt_interrupt_from_thread = from;
    }

    rt_interrupt_to_thread = to;
    ENTER_INTERRUPT();
}

/**
 * shut down the chip
 * 
 * @author LXZ (2014/11/8)
 */
void rt_hw_cpu_shutdown(void)
{
    rt_kprintf("shutdown...\n");

    RT_ASSERT(0);
}
/**
 * switch to the first thread,it just call one time
 * 
 * @author LXZ (2014/11/8)
 * 
 * @param rt_uint32_t to 
 */
void rt_hw_context_switch_to(rt_uint32_t to)
{

    rt_interrupt_from_thread = 0;
    rt_interrupt_to_thread = to;
    rt_thread_switch_interrupt_flag = 1;
    /* enable interrupt*/
    _IEN( _ICU_SWINT ) = 1;

    /*clear the interrupt flag*/
    _IR( _ICU_SWINT ) = 0;
    _IPR( _ICU_SWINT ) = MAX_SYSCALL_INTERRUPT_PRIORITY + 1;

    /*touch the software interrupt*/
    ENTER_INTERRUPT();
    /*wait for first thread start up*/
    while(1);
}

