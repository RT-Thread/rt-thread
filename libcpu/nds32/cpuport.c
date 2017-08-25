/*
 * File      : cpuport.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date         Author      Notes
 * 2009-01-05   Bernard     first version
 * 2011-02-14   onelife     Modify for EFM32
 * 2011-06-17   onelife     Merge all of the C source code into cpuport.c
 * 2012-12-23   aozima      stack addr align to 8byte.
 * 2012-12-29   Bernard     Add exception hook.
 * 2013-07-09   aozima      enhancement hard fault exception handler.
 */

#include <rtthread.h>

#include "nds32.h"

/*
 * Initialise the stack of a task to look exactly as if a call to
 * SAVE_CONTEXT had been called.
 *
 * See header file for description.
 *
 *
 * Stack Layout:
 *		          High  |-----------------|
 *                      |       $R5       |
 *                      |-----------------|
 *                      |        .        |
 *                      |        .        |
 *                      |-----------------|
 *                      |       $R0       |
 *                      |-----------------|
 *                      |       $R30 (LP) |
 *                      |-----------------|
 *                      |       $R29 (GP) |
 *                      |-----------------|
 *                      |       $R28 (FP) |
 *                      |-----------------|
 *                      |   $R15   $R27   |
 *                      |-----------------|
 *                      |   $R10   $R26   |
 *                      |-----------------|
 *                      |        .        |
 *                      |        .        |
 *                      |-----------------|
 *                      |       $R6       |
 *                      |-----------------|
 *                      |       $IFC_LP   | (Option)
 *                      |-----------------|
 *                      |   $LC/$LE/$LB   | (Option)
 *                      |       (ZOL)     |
 *                      |-----------------|
 *                      |       $IPSW     |
 *                      |-----------------|
 *                      |       $IPC      |
 *                      |-----------------|
 *                      |    Dummy word   | (Option, only exist when IFC & ZOL both configured)
 *                      |-----------------|
 *                      |       $FPU      | (Option)
 *                      |-----------------|
 *                Low
 *
 */

struct stack_frame
{
    rt_uint32_t topOfStack[34];
};

/* flag in interrupt handling */
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;
/* exception hook */
static rt_err_t (*rt_exception_hook)(void *context) = RT_NULL;

rt_base_t rt_hw_interrupt_disable(void)
{
	rt_base_t level = __nds32__mfsr(NDS32_SR_PSW);

	GIE_DISABLE();

	return level;
}

void rt_hw_interrupt_enable(rt_base_t level)
{
	if (level & PSW_mskGIE)
		GIE_ENABLE();
}

/* For relax support, must initial $gp at task init*/
extern uint32_t _SDA_BASE_ __attribute__ ((weak));

/**************************************************************
 * This function will initialize thread stack
 *
 * @param tentry the entry of thread
 * @param parameter the parameter of entry
 * @param stack_addr the beginning stack address
 * @param texit the function will be called when thread exit
 *
 * @return stack address
 **************************************************************/
rt_uint8_t *rt_hw_stack_init(void       *tentry,
                             void       *parameter,
                             rt_uint8_t *stack_addr,
                             void       *texit)
{
	rt_int32_t i;
	rt_uint32_t *pxTopOfStack;

	pxTopOfStack = (rt_uint32_t *)RT_ALIGN_DOWN((rt_uint32_t)stack_addr, 4);

	/* Simulate the stack frame as it would be created by a context switch */
	/* R0 ~ R5 registers */
	for (i = 5; i >= 1; i--)                         /* R5, R4, R3, R2 and R1. */
		*--pxTopOfStack = (rt_uint32_t)0x01010101UL * i;
	*--pxTopOfStack = (rt_uint32_t)parameter;        /* R0 : Argument */

	/* R6 ~ R30 registers */
	*--pxTopOfStack = (rt_uint32_t)texit;   /* R30: $LP */
	*--pxTopOfStack = (rt_uint32_t)&_SDA_BASE_;         /* R29: $GP */
	*--pxTopOfStack = (rt_uint32_t)0x2828282828;        /* R28: $FP */
#ifdef __NDS32_REDUCE_REGS__
	*--pxTopOfStack = (rt_uint32_t)0x1515151515;        /* R15 */
	for (i = 10; i >= 6; i--)                           /* R10 ~ R6 */
		*--pxTopOfStack = (rt_uint32_t)0x01010101UL * i;
#else
	for (i = 27; i >= 6; i--)                           /* R27 ~ R6 */
		*--pxTopOfStack = (rt_uint32_t)0x01010101UL * i;
#endif

	/* IFC system register */
#ifdef __TARGET_IFC_EXT
	*--pxTopOfStack = (rt_uint32_t)0x0;                 /* $IFC_LP */
#endif

	/* ZOL system registers */
#ifdef __TARGET_ZOL_EXT
	*--pxTopOfStack = (rt_uint32_t)0x0;                 /* $LC */
	*--pxTopOfStack = (rt_uint32_t)0x0;                 /* $LE */
	*--pxTopOfStack = (rt_uint32_t)0x0;                 /* $LB */
#endif

	/* IPSW and IPC system registers */
	/* Default IPSW: enable GIE, set CPL to 7, clear IFCON */
	i = (__nds32__mfsr(NDS32_SR_PSW) | PSW_mskGIE | PSW_mskCPL) & ~PSW_mskIFCON;
	*--pxTopOfStack = (rt_uint32_t)i;                /* $IPSW */
	*--pxTopOfStack = (rt_uint32_t)tentry;           /* $IPC */

	/* Dummy word for 8-byte stack alignment */
#if defined(__TARGET_IFC_EXT) && defined(__TARGET_ZOL_EXT)
	*--pxTopOfStack = (rt_uint32_t)0xFFFFFFFF;          /* Dummy */
#endif

	/* FPU registers */
#ifdef __TARGET_FPU_EXT
	for (i = 0; i < FPU_REGS; i++)
		*--pxTopOfStack = (rt_uint32_t)0x0;         /* FPU */
#endif

	return (rt_uint8_t *)pxTopOfStack;
}

/**
 * This function set the hook, which is invoked on fault exception handling.
 *
 * @param exception_handle the exception handling hook function.
 */
void rt_hw_exception_install(rt_err_t (*exception_handle)(void* context))
{
    rt_exception_hook = exception_handle;
}

#ifdef RT_USING_CPU_FFS
/**
 * This function finds the first bit set (beginning with the least significant bit)
 * in value and return the index of that bit.
 *
 * Bits are numbered starting at 1 (the least significant bit).  A return value of
 * zero from any of these functions means that the argument was zero.
 *
 * @return return the index of the first bit set. If value is 0, then this function
 * shall return 0.
 */
#if defined(__CC_ARM)
__asm int __rt_ffs(int value)
{
    CMP     r0, #0x00
    BEQ     exit
    RBIT    r0, r0
    CLZ     r0, r0
    ADDS    r0, r0, #0x01

    exit
    BX      lr
}
#elif defined(__IAR_SYSTEMS_ICC__)
int __rt_ffs(int value)
{
    if (value == 0) return value;

    __ASM("RBIT r0, r0");
    __ASM("CLZ  r0, r0");
    __ASM("ADDS r0, r0, #0x01");
}
#elif defined(__GNUC__)
int __rt_ffs(int value)
{
    return __builtin_ffs(value);
}
#endif

#endif
