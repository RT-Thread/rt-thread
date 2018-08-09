/*
 * FreeRTOS Kernel V10.0.0
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software. If you wish to use our Amazon
 * FreeRTOS name, please do so in a fair use way that does not cause confusion.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the ARM CM4F port.
 *----------------------------------------------------------*/

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
__stackless void vPortStartFirstTask( void );

/*
 * Exception handlers.
 */
__stackless void vPortSVCHandler( void );
__stackless void xPortPendSVHandler( void );


extern uint32_t __Vectors;
extern uint32_t pxCurrentTCB;


/*-----------------------------------------------------------*/

__stackless void vPortStartFirstTask( void )
{
    __asm volatile(
                    " ldr.n r0, 1f          \n" /* Locate the stack using __Vectors table. */
                    " ldr r0, [r0]          \n"
                    " msr msp, r0           \n" /* Set the msp back to the start of the stack. */
                    " cpsie i               \n" /* Globally enable interrupts. */
                    " cpsie f               \n"
                    " dsb                   \n"
                    " isb                   \n"
#ifdef SOFTDEVICE_PRESENT
                    /* Block kernel interrupts only (PendSV) before calling SVC */
                    " mov r0, %1           \n"
                    " msr basepri, r0       \n"
#endif
                    " svc 0                 \n" /* System call to start first task. */
                    "                       \n"
                    " nop                   \n" /* Manual alignment of the label below */
                    "DATA                   \n"
                    "1:                     \n"
                    "   DC32  %c0           \n"
                    : /* Outputs */
                    : /* Inputs */
                        "i"(&__Vectors)
#ifdef SOFTDEVICE_PRESENT
                        ,
                        "i"(configKERNEL_INTERRUPT_PRIORITY  << (8 - configPRIO_BITS))
#endif
                );
}

/*-----------------------------------------------------------*/

__stackless void vPortSVCHandler( void )
{
    __asm volatile (
                    "   ldr.n r3, 1f                    \n" /* Restore the context. */
                    "   ldr r1, [r3]                    \n" /* Use pxCurrentTCBConst to get the pxCurrentTCB address. */
                    "   ldr r0, [r1]                    \n" /* The first item in pxCurrentTCB is the task top of stack. */
                    "   ldmia r0!, {r4-r11, r14}        \n" /* Pop the registers that are not automatically saved on exception entry and the critical nesting count. */
                    "   msr psp, r0                     \n" /* Restore the task stack pointer. */
                    "   isb                             \n"
                    "   mov r0, #0                      \n"
                    "   msr basepri, r0                 \n"
                    "   bx r14                          \n"
                    "                                   \n"
                    "                                   \n" /* Manual alignment of the label below */
                    "DATA                               \n"
                    "1:                                 \n"
                    "   DC32  %c0                       \n"
                    : /* Outputs */
                    : /* Inputs */
                        "i"(&pxCurrentTCB)
                );
}

/*-----------------------------------------------------------*/

__stackless void xPortPendSVHandler( void )
{
    /* This is a naked function. */

    __asm volatile
    (
    "   mrs r0, psp                         \n"
    "   isb                                 \n"
    "                                       \n"
    "   ldr.n r3, 1f                        \n" /* Get the location of the current TCB. */
    "   ldr r2, [r3]                        \n"
    "                                       \n"
    "   tst r14, #0x10                      \n" /* Is the task using the FPU context?  If so, push high vfp registers. */
    "   it eq                               \n"
    "   vstmdbeq r0!, {s16-s31}             \n"
    "                                       \n"
    "   stmdb r0!, {r4-r11, r14}            \n" /* Save the core registers. */
    "                                       \n"
    "   str r0, [r2]                        \n" /* Save the new top of stack into the first member of the TCB. */
    "                                       \n"
    "   stmdb sp!, {r3}                     \n"
    "   mov r0, %0                         \n"
    "   msr basepri, r0                     \n"
    "   dsb                                 \n"
    "   isb                                 \n"
    "   bl %c2                              \n"
    "   mov r0, #0                          \n"
    "   msr basepri, r0                     \n"
    "   ldmia sp!, {r3}                     \n"
    "                                       \n"
    "   ldr r1, [r3]                        \n" /* The first item in pxCurrentTCB is the task top of stack. */
    "   ldr r0, [r1]                        \n"
    "                                       \n"
    "   ldmia r0!, {r4-r11, r14}            \n" /* Pop the core registers. */
    "                                       \n"
    "   tst r14, #0x10                      \n" /* Is the task using the FPU context?  If so, pop the high vfp registers too. */
    "   it eq                               \n"
    "   vldmiaeq r0!, {s16-s31}             \n"
    "                                       \n"
    "   msr psp, r0                         \n"
    "   isb                                 \n"
    "                                       \n"
    "                                       \n"
    "   bx r14                              \n"
    "                                       \n"
    "                                       \n" /* Manual alignment of the label below */
    "DATA                                   \n"
    "1:                                     \n"
    "   DC32  %c1                           \n"
    : /* Outputs */
    : /* Inputs */
        "i"(configMAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS)),
        "i"(&pxCurrentTCB),
        "i"(&vTaskSwitchContext)
    );
}
