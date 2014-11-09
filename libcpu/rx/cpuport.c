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


/* 栈结构 */
struct stack_frame
{
    rt_uint32_t ACCLO; //累加器
    rt_uint32_t ACCHI;
    rt_uint32_t FPSW;   /*浮点状态字*/
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
    //没有R0，R0是栈指针
    rt_uint32_t PC;  //程序入口
    rt_uint32_t PSW; //系统状态寄存器
};

/**
 * 线程栈初始化
 * 
 * @author LXZ (2014/11/8)
 * 
 * @param void* tentry       入口函数
 * @param void* parameter    参数
 * @param rt_uint8_t* stack_addr 栈地址
 * @param void* texit        线程结束退出入口
 * 
 * @return rt_uint8_t* 
 */
rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter,
                             rt_uint8_t *stack_addr, void *texit)
{
    unsigned long *stk;
    struct stack_frame *stack_frame;
    unsigned long       i;

    		/*关于任务的退出，rx62n是跟cm3不一样的，cm3具有LR返回寄存器，
		但是在rx62n是没有的，所以当执行完一个任务后（比如说init任务
		是一个直接退出的函数，那该怎么办，动态建立的任务应该释放内
		存的，根据这个，发现在rts的后面有个弹回pc的动作，也就是说
		一个函数返回，它最后弹的栈应该是pc,所以栈底明显第一个字节是
		退出函数了*/
    stk      = (unsigned long *)stack_addr;
    *(stk)   = (unsigned long)texit;        /* 退出任务 */
    //计算栈的开始位置
    stack_frame = (struct stack_frame *)(stack_addr - sizeof(struct stack_frame)) ;

    //初始化栈 
    for (i = 0; i < sizeof(struct stack_frame) / sizeof(rt_uint32_t); i ++)
    {
        ((rt_uint32_t *)stack_frame)[i] = 0xdeadbeef;
    }
    //必要CPU状态寄存器初始化
    stack_frame->PSW = (unsigned long)0x00030000 ;   /* psw */
    stack_frame->PC = (unsigned long)tentry;        /* 程序运行到的地方*/
    stack_frame->R1 = (unsigned long )parameter;   /* r1 : 参数 */
    stack_frame->FPSW = 0x00000100;                  /* fpsw */
    /* 返回栈顶地址 */
    return(rt_uint8_t *)stack_frame;
}

#ifdef RT_USING_FINSH
extern void list_thread(void);
#endif
extern rt_thread_t rt_current_thread;
/**
 * 异常处理
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


/* 
*  
* 关于上下文切换，也就是任务切换， 需要知道的是，rx是不支持嵌套中断的，进入中断后会先关掉中断使能 
* 所以想在中断中直接切换任务是不可能的，而如果中断中直接调用中断切换函数也没用，因为栈不对，所以一 
* 般要保证一点就是不管是中断里还是中断外，要切换任务，首先必须先准备好参数 并启动软件中断，这样在 
* 返回用户任务的时候会立刻进入软件中断处理任务切换。  
*/
/**
 * 中断中的任务切换
 * 
 * @author LXZ (2014/11/8)
 * 
 * @param rt_uint32_t from 
 * @param rt_uint32_t to 
 */
void rt_hw_context_switch(rt_uint32_t from, rt_uint32_t to)
{
    /* 判断中断标志是否置位,是的话需要保存切换前的线程*/
    if (rt_thread_switch_interrupt_flag == 0)
    {
        rt_thread_switch_interrupt_flag = 1;
        rt_interrupt_from_thread = from;
    }

    rt_interrupt_to_thread = to;
    ENTER_INTERRUPT();
}
/**
 * 中断外任务切换
 * 
 * @author LXZ (2014/11/8)
 * 
 * @param rt_uint32_t from 
 * @param rt_uint32_t to 
 */
void rt_hw_context_switch_interrupt(rt_uint32_t from, rt_uint32_t to)
{
    /* 判断中断标志是否置位,是的话需要保存切换前的线程*/
    if (rt_thread_switch_interrupt_flag == 0)
    {
        rt_thread_switch_interrupt_flag = 1;
        rt_interrupt_from_thread = from;
    }

    rt_interrupt_to_thread = to;
    ENTER_INTERRUPT();
}

/**
 * 挂起
 * 
 * @author LXZ (2014/11/8)
 */
void rt_hw_cpu_shutdown(void)
{
    rt_kprintf("shutdown...\n");

    RT_ASSERT(0);
}
/**
 * 切换到第一个任务，只有在线程要开始的时候才会用到
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
    /* 启动中断*/
    _IEN( _ICU_SWINT ) = 1;

    /*确定中断已经清除（退出中断）*/
    _IR( _ICU_SWINT ) = 0;
    _IPR( _ICU_SWINT ) = MAX_SYSCALL_INTERRUPT_PRIORITY + 1;

    /*触发软件中断*/
    ENTER_INTERRUPT();
    //等待第一次任务触发
    while(1);
}

