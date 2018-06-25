/*
 * File      : stack.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-14     Fred         first implementation for 
 */

#include <rtthread.h>
#include "compiler_api.h"
/**
 * @addtogroup PowerPC
 */
/*@{*/

/**
 * This function will initialize thread stack
 *
 * @param tentry the entry of thread
 * @param parameter the parameter of entry
 * @param stack_addr the beginning stack address
 * @param texit the function will be called when thread exit
 *
 * @return stack address
 */
#define MFMSR(dest)         __asm__ volatile ("mfmsr %0"     : "=r" (dest))
#define portCRITICAL_INTERRUPT_ENABLE   ( 1UL << 17UL )
#define portEXTERNAL_INTERRUPT_ENABLE   ( 1UL << 15UL )
#define portPROBLEM_STATE               ( 1UL << 14UL )
#define portMACHINE_CHECK_ENABLE        ( 1UL << 12UL )

#define portINITIAL_MSR                 ( portCRITICAL_INTERRUPT_ENABLE | \
                                          portEXTERNAL_INTERRUPT_ENABLE | \
                                          portMACHINE_CHECK_ENABLE )
/*
--- Stack frame layout 栈顶---------------------------
		保留八个字节
		MSR
		SRR0
		SRR1
		XER
		CTR
		LR
		CR
		R31
		R30
		R29
		R28
		R27
		R26
		R25
		R24
		R23
		R22
		R21
		R20
		R19
		R18
		R17
		R16
		R15
		R14
		R13
		R12
		R11
		R10
		R9
		R8
		R7
		R6
		R5
		R4
		R3
		R2
		R1
		R0
----------------栈底------------------------------
--- Total: 8 + 156 ------------------------------
*/
rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter,
    rt_uint8_t *stack_addr, void *texit)//这里已经减去4了
{
    unsigned long *stk;
    register rt_uint32_t msr, srr1;

    MFMSR(msr);

    srr1 = portINITIAL_MSR | msr;
    stk      = (unsigned long *)stack_addr;
    --stk;		//这里又减去4了

	*(--stk) = msr;                                                      /* MSR */
	*(--stk)  = ( rt_uint32_t ) tentry;                                    /* SRR0 */
	*(--stk) = srr1;                                                     /* SRR1 */
    *(--stk) = 0;                                                        /* XER */
	*(--stk) = 0;                                                        /* CTR */
	*(--stk) =( rt_uint32_t ) texit;                             	   /* LR  */
	*(--stk) = 0;                                                        /* CR  */

	*(--stk) = 0x31L;                                                    /* r31 */
	*(--stk)= 0x30L;                                                    /* r30 */
	*(--stk) = 0x29L;                                                    /* r29 */
	*(--stk) = 0x28L;                                                    /* r28 */
	*(--stk) = 0x27L;                                                    /* r27 */
	*(--stk) = 0x26L;                                                    /* r26 */
	*(--stk) = 0x25L;                                                    /* r25 */
	*(--stk) = 0x24L;                                                    /* r24 */
	*(--stk) = 0x23L;                                                    /* r23 */
	*(--stk) = 0x22L;                                                    /* r22 */
	*(--stk) = 0x21L;                                                    /* r21 */
	*(--stk) = 0x20L;                                                    /* r20 */
	*(--stk) = 0x19L;                                                    /* r19 */
	*(--stk) = 0x18L;                                                    /* r18 */
	*(--stk) = 0x17L;                                                    /* r17 */
	*(--stk) = 0x16L;                                                    /* r16 */
	*(--stk) = 0x15L;                                                    /* r15 */
	*(--stk) = 0x14L;                                                    /* r14 */
	*(--stk) = 0x13L;														/* r13 */
	*(--stk) = 0x12L;                                                    /* r12 */
	*(--stk) = 0x11L;                                                    /* r11 */
	*(--stk) = 0x10L;                                                    /* r10 */
	*(--stk) = 0x9L;                                                     /* r09 */
	*(--stk) = 0x8L;                                                     /* r08 */
	*(--stk) = 0x7L;                                                     /* r07 */
	*(--stk) = 0x6L;                                                     /* r06 */
	*(--stk) = 0x5L;                                                     /* r05 */
	*(--stk) = 0x4L;                                                     /* r04 */
	*(--stk) = ( rt_uint32_t ) parameter;                          	/* r03 */
	*(--stk) = 0x2L;                          							/* r02*/
	*(--stk) = 0x1A2B;                          							/* r01 */
	*(--stk) = 0x0L;                                                     /* r00 */
	return (rt_uint8_t *)stk;



# if 0
    *(--stk) = msr;                 /*msr*/
    *(--stk) = msr;/* srr0: machine status register */
    *(--stk) = (rt_uint32_t)tentry; /* srr1: entry point */
    *(--stk) = (rt_uint32_t)texit;  /* lr: link register */
    *(--stk) = 0x0F0F0F0F;          /* ctr: counter register */
    *(--stk) = 0x0F0F0F0F;          /* xer: fixed-point exception register */
    *(--stk) = 0x0F0F0F0F;          /* cr : condition register */
    //*(--stk) = 0x00;                /* usprg0 */ XPC系列 没有这个

    *(--stk) = 31;            /* r31 */
    *(--stk) = 30;            /* r30 */
    *(--stk) = 29;            /* r29 */
    *(--stk) = 28;            /* r28 */
    *(--stk) = 27;            /* r27 */
    *(--stk) = 26;            /* r26 */
    *(--stk) = 25;            /* r25 */
    *(--stk) = 24;            /* r24 */
    *(--stk) = 23;            /* r23 */
    *(--stk) = 22;            /* r22 */
    *(--stk) = 21;            /* r21 */
    *(--stk) = 20;            /* r20 */
    *(--stk) = 19;            /* r19 */
    *(--stk) = 18;            /* r18 */
    *(--stk) = 17;            /* r17 */
    *(--stk) = 16;            /* r16 */
    *(--stk) = 15;            /* r15 */
    *(--stk) = 14;            /* r14 */
    *(--stk) = 13;            /* r13: thread id */
    *(--stk) = 12;            /* r12 */
    *(--stk) = 11;            /* r11 */
    *(--stk) = 10;            /* r10 */
    *(--stk) = 0x09;            /* r09 */
    *(--stk) = 0x08;            /* r08 */
    *(--stk) = 0x07;            /* r07 */
    *(--stk) = 0x06;            /* r06 */
    *(--stk) = 0x05;            /* r05 */
    *(--stk) = 0x04;            /* r04 */
    *(--stk) = (rt_uint32_t)parameter;  /* r03: parameter and return  */
    *(--stk) = 0x02;            /* r02: toc */
                                /* r01: sp */
    *(--stk) = 0x0;             /* r00 */

    /* return task's current stack address */
    return (rt_uint8_t *)stk;
#endif
}

/*@}*/
