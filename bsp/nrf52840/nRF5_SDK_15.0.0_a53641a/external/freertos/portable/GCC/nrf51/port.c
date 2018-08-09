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
 * Implementation of functions defined in portable.h for the ARM CM0 port.
 *----------------------------------------------------------*/

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
void vPortStartFirstTask( void ) __attribute__ (( naked ));

/*
 * Exception handlers.
 */
void vPortSVCHandler( void );
void xPortPendSVHandler( void ) __attribute__ (( naked ));


/*-----------------------------------------------------------*/

void vPortStartFirstTask( void )
{
    __asm volatile(
    "   .syntax unified           \n"
    "                             \n"
#if defined(__SES_ARM)
    " ldr r0, =_vectors \n"     /* Locate the stack using _vectors table. */
#else
    " ldr r0, =__isr_vector \n" /* Locate the stack using __isr_vector table. */
#endif
    "   ldr r0, [r0]              \n"
    "   msr msp, r0               \n" /* Set the msp back to the start of the stack. */
    "                             \n"
    "   ldr r3, =pxCurrentTCB \n" /* Obtain location of pxCurrentTCB. */
    "   ldr r1, [r3]              \n"
    "   ldr r0, [r1]              \n" /* The first item in pxCurrentTCB is the task top of stack. */
    "   adds r0, #32              \n" /* Discard everything up to r0 */
    "   msr psp, r0               \n" /* This is now the new top of stack to use in the task. */
    "   movs r0, #2               \n" /* Switch to the psp stack. */
    "   msr CONTROL, r0           \n"
    "   pop {r0-r5}               \n" /* Pop the registers that are saved automatically. */
    "   mov lr, r5                \n" /* lr is now in r5. */
    "   cpsie i                   \n" /* The first task has its context and interrupts can be enabled. */
    "   pop {pc}                  \n" /* Finally, pop the PC to jump to the user defined task code. */
    "                             \n"
    "   .align 2                  \n"
    );
}

/*-----------------------------------------------------------*/

void vPortSVCHandler( void )
{
    /* This function is no longer used, but retained for backward
    compatibility. */
}

/*-----------------------------------------------------------*/

void xPortPendSVHandler( void )
{
    /* This is a naked function. */

    __asm volatile
    (
    "   .syntax unified                     \n"
    "                                       \n"
    "   mrs r0, psp                         \n"
    "                                       \n"
    "   ldr r3, =pxCurrentTCB               \n" /* Get the location of the current TCB. */
    "   ldr r2, [r3]                        \n"
    "                                       \n"
    "   subs r0, #32                        \n" /* Make space for the remaining low registers. */
    "   str r0, [r2]                        \n" /* Save the new top of stack. */
    "   stmia r0!, {r4-r7}                  \n" /* Store the low registers that are not saved automatically. */
    "   mov r4, r8                          \n" /* Store the high registers. */
    "   mov r5, r9                          \n"
    "   mov r6, r10                         \n"
    "   mov r7, r11                         \n"
    "   stmia r0!, {r4-r7}                  \n"
    "                                       \n"
    "   push {r3, r14}                      \n"
    "   bl vPortSafeTaskSwitchContext       \n"
    "   pop {r2, r3}                        \n" /* lr goes in r3. r2 now holds tcb pointer. */
    "                                       \n"
    "   ldr r1, [r2]                        \n"
    "   ldr r0, [r1]                        \n" /* The first item in pxCurrentTCB is the task top of stack. */
    "   adds r0, #16                        \n" /* Move to the high registers. */
    "   ldmia r0!, {r4-r7}                  \n" /* Pop the high registers. */
    "   mov r8, r4                          \n"
    "   mov r9, r5                          \n"
    "   mov r10, r6                         \n"
    "   mov r11, r7                         \n"
    "                                       \n"
    "   msr psp, r0                         \n" /* Remember the new top of stack for the task. */
    "                                       \n"
    "   subs r0, #32                        \n" /* Go back for the low registers that are not automatically restored. */
    "   ldmia r0!, {r4-r7}                  \n" /* Pop low registers.  */
    "                                       \n"
    "   bx r3                               \n"
    "                                       \n"
    "   .align 2                            \n"
    );
}
