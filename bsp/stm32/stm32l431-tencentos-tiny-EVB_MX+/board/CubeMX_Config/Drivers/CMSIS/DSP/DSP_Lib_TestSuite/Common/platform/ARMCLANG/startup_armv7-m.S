/* File: startup_armv7-m.S
 * Purpose: startup file for armv7-m architecture devices.
 *          Should be used with ARMCLANG
 * Version: V2.00
 * Date: 16 November 2015
 *
 */
/* Copyright (c) 2011 - 2015 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/
/*
  ;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/


    .syntax unified
    .arch   armv7-m

/* .eabi_attribute Tag_ABI_align8_preserved,1    www.support.code-red-tech.com/CodeRedWiki/Preserve8 */
.eabi_attribute 25, 1   /* Tag_ABI_align_preserved */

    .global    Image$$ARM_LIB_STACK$$ZI$$Limit


    .section RESET, "x"
    .align  2
    .globl  __Vectors
    .globl  __Vectors_End
    .globl  __Vectors_Size
__Vectors:
    .long   Image$$ARM_LIB_STACK$$ZI$$Limit            /* Top of Stack */
    .long   Reset_Handler         /* Reset Handler */
    .long   NMI_Handler           /* NMI Handler */
    .long   HardFault_Handler     /* Hard Fault Handler */
    .long   MemManage_Handler     /* MPU Fault Handler */
    .long   BusFault_Handler      /* Bus Fault Handler */
    .long   UsageFault_Handler    /* Usage Fault Handler */
    .long   0                     /* Reserved */
    .long   0                     /* Reserved */
    .long   0                     /* Reserved */
    .long   0                     /* Reserved */
    .long   SVC_Handler           /* SVCall Handler */
    .long   DebugMon_Handler      /* Debug Monitor Handler */
    .long   0                     /* Reserved */
    .long   PendSV_Handler        /* PendSV Handler */
    .long   SysTick_Handler       /* SysTick Handler */
__Vectors_End:

    .equ    __Vectors_Size, __Vectors_End - __Vectors


    .text
    .thumb
    .align  2

    .globl  Reset_Handler
    .weak   Reset_Handler
    .type   Reset_Handler, %function
    .thumb_func
Reset_Handler:
    bl      SystemInit
    bl      __main

    .globl  NMI_Handler
    .weak   NMI_Handler
    .type   NMI_Handler, %function
    .thumb_func
NMI_Handler:
    bkpt    #0
    b       .

    .globl  HardFault_Handler
    .weak   HardFault_Handler
    .type   HardFault_Handler, %function
    .thumb_func
HardFault_Handler:
    bkpt    #0
    b       .

    .globl  MemManage_Handler
    .weak   MemManage_Handler
    .type   MemManage_Handler, %function
    .thumb_func
MemManage_Handler:
    bkpt    #0
    b       .

    .globl  BusFault_Handler
    .weak   BusFault_Handler
    .type   BusFault_Handler, %function
    .thumb_func
BusFault_Handler:
    bkpt    #0
    b       .

    .globl  UsageFault_Handler
    .weak   UsageFault_Handler
    .type   UsageFault_Handler, %function
    .thumb_func
UsageFault_Handler:
    bkpt    #0
    b       .

    .globl  SVC_Handler
    .weak   SVC_Handler
    .type   SVC_Handler, %function
    .thumb_func
SVC_Handler:
    bkpt    #0
    b       .

    .globl  DebugMon_Handler
    .weak   DebugMon_Handler
    .type   DebugMon_Handler, %function
    .thumb_func
DebugMon_Handler:
    bkpt    #0
    b       .

    .globl  PendSV_Handler
    .weak   PendSV_Handler
    .type   PendSV_Handler, %function
    .thumb_func
PendSV_Handler:
    bkpt    #0
    b       .

    .globl  SysTick_Handler
    .weak   SysTick_Handler
    .type   SysTick_Handler, %function
    .thumb_func
SysTick_Handler:
    bkpt    #0
    b       .

    .end
