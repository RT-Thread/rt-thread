/***********************************************************************************
 *                           SEGGER Microcontroller GmbH                           *
 *                               The Embedded Experts                              *
 ***********************************************************************************
 *                                                                                 *
 *                   (c) 2014 - 2018 SEGGER Microcontroller GmbH                   *
 *                                                                                 *
 *                  www.segger.com     Support: support@segger.com                 *
 *                                                                                 *
 ***********************************************************************************
 *                                                                                 *
 *        All rights reserved.                                                     *
 *                                                                                 *
 *        Redistribution and use in source and binary forms, with or               *
 *        without modification, are permitted provided that the following          *
 *        conditions are met:                                                      *
 *                                                                                 *
 *        - Redistributions of source code must retain the above copyright         *
 *          notice, this list of conditions and the following disclaimer.          *
 *                                                                                 *
 *        - Neither the name of SEGGER Microcontroller GmbH                        *
 *          nor the names of its contributors may be used to endorse or            *
 *          promote products derived from this software without specific           *
 *          prior written permission.                                              *
 *                                                                                 *
 *        THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND                   *
 *        CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,              *
 *        INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF                 *
 *        MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE                 *
 *        DISCLAIMED.                                                              *
 *        IN NO EVENT SHALL SEGGER Microcontroller GmbH BE LIABLE FOR              *
 *        ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR                 *
 *        CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT        *
 *        OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;          *
 *        OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF            *
 *        LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT                *
 *        (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE        *
 *        USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH         *
 *        DAMAGE.                                                                  *
 *                                                                                 *
 ***********************************************************************************/

/************************************************************************************
 *                         Preprocessor Definitions                                 *
 *                         ------------------------                                 *
 * VECTORS_IN_RAM                                                                   *
 *                                                                                  *
 *   If defined, an area of RAM will large enough to store the vector table         *
 *   will be reserved.                                                              *
 *                                                                                  *
 ************************************************************************************/

  .syntax unified
  .code 16

  .section .init, "ax"
  .align 0
  
/************************************************************************************
 * Default Exception Handlers                                                       *
 ************************************************************************************/


  .thumb_func
  .weak   NMI_Handler
NMI_Handler:
  b     .

  .thumb_func
  .weak   HardFault_Handler
HardFault_Handler:
  b     .

  .thumb_func
  .weak   MemoryManagement_Handler
MemoryManagement_Handler:
  b     .

  .thumb_func
  .weak   BusFault_Handler
BusFault_Handler:
  b     .

  .thumb_func
  .weak   UsageFault_Handler
UsageFault_Handler:
  b     .

  .thumb_func
  .weak   SVC_Handler
SVC_Handler:
  b     .

  .thumb_func
  .weak   DebugMon_Handler
DebugMon_Handler:
  b     .

  .thumb_func
  .weak   PendSV_Handler
PendSV_Handler:
  b     .

  .thumb_func
  .weak   SysTick_Handler
SysTick_Handler:
  b     .

  .thumb_func
  .weak   Dummy_Handler
Dummy_Handler:
  b     .

/************************************************************************************
 * Default Interrupt Handlers                                                       *
 ************************************************************************************/
 
.weak POWER_CLOCK_IRQHandler
.thumb_set POWER_CLOCK_IRQHandler, Dummy_Handler

.weak RADIO_IRQHandler
.thumb_set RADIO_IRQHandler, Dummy_Handler

.weak UARTE0_UART0_IRQHandler
.thumb_set UARTE0_UART0_IRQHandler, Dummy_Handler

.weak TWIM0_TWIS0_TWI0_SPIM1_SPIS1_SPI1_IRQHandler
.thumb_set TWIM0_TWIS0_TWI0_SPIM1_SPIS1_SPI1_IRQHandler, Dummy_Handler

.weak SPIM0_SPIS0_SPI0_IRQHandler
.thumb_set SPIM0_SPIS0_SPI0_IRQHandler, Dummy_Handler

.weak GPIOTE_IRQHandler
.thumb_set GPIOTE_IRQHandler, Dummy_Handler

.weak SAADC_IRQHandler
.thumb_set SAADC_IRQHandler, Dummy_Handler

.weak TIMER0_IRQHandler
.thumb_set TIMER0_IRQHandler, Dummy_Handler

.weak TIMER1_IRQHandler
.thumb_set TIMER1_IRQHandler, Dummy_Handler

.weak TIMER2_IRQHandler
.thumb_set TIMER2_IRQHandler, Dummy_Handler

.weak RTC0_IRQHandler
.thumb_set RTC0_IRQHandler, Dummy_Handler

.weak TEMP_IRQHandler
.thumb_set TEMP_IRQHandler, Dummy_Handler

.weak RNG_IRQHandler
.thumb_set RNG_IRQHandler, Dummy_Handler

.weak ECB_IRQHandler
.thumb_set ECB_IRQHandler, Dummy_Handler

.weak CCM_AAR_IRQHandler
.thumb_set CCM_AAR_IRQHandler, Dummy_Handler

.weak WDT_IRQHandler
.thumb_set WDT_IRQHandler, Dummy_Handler

.weak RTC1_IRQHandler
.thumb_set RTC1_IRQHandler, Dummy_Handler

.weak QDEC_IRQHandler
.thumb_set QDEC_IRQHandler, Dummy_Handler

.weak COMP_IRQHandler
.thumb_set COMP_IRQHandler, Dummy_Handler

.weak SWI0_EGU0_IRQHandler
.thumb_set SWI0_EGU0_IRQHandler, Dummy_Handler

.weak SWI1_EGU1_IRQHandler
.thumb_set SWI1_EGU1_IRQHandler, Dummy_Handler

.weak SWI2_IRQHandler
.thumb_set SWI2_IRQHandler, Dummy_Handler

.weak SWI3_IRQHandler
.thumb_set SWI3_IRQHandler, Dummy_Handler

.weak SWI4_IRQHandler
.thumb_set SWI4_IRQHandler, Dummy_Handler

.weak SWI5_IRQHandler
.thumb_set SWI5_IRQHandler, Dummy_Handler

.weak PWM0_IRQHandler
.thumb_set PWM0_IRQHandler, Dummy_Handler

.weak PDM_IRQHandler
.thumb_set PDM_IRQHandler, Dummy_Handler

/************************************************************************************
 * Reset Handler Extensions                                                         *
 ************************************************************************************/

  .extern Reset_Handler
  .global nRFInitialize

  .thumb_func
nRFInitialize:
  bx lr
 
 
/************************************************************************************
 * Vector Table                                                                     *
 ************************************************************************************/

  .section .vectors, "ax"
  .align 0
  .global _vectors
  .extern __stack_end__

_vectors:
  .word __stack_end__
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word MemoryManagement_Handler
  .word BusFault_Handler
  .word UsageFault_Handler
  .word 0                           /*Reserved */
  .word 0                           /*Reserved */
  .word 0                           /*Reserved */
  .word 0                           /*Reserved */
  .word SVC_Handler
  .word DebugMon_Handler
  .word 0                           /*Reserved */
  .word PendSV_Handler
  .word SysTick_Handler

/* External Interrupts */
  .word   POWER_CLOCK_IRQHandler
  .word   RADIO_IRQHandler
  .word   UARTE0_UART0_IRQHandler
  .word   TWIM0_TWIS0_TWI0_SPIM1_SPIS1_SPI1_IRQHandler
  .word   SPIM0_SPIS0_SPI0_IRQHandler
  .word   0                           /*Reserved */
  .word   GPIOTE_IRQHandler
  .word   SAADC_IRQHandler
  .word   TIMER0_IRQHandler
  .word   TIMER1_IRQHandler
  .word   TIMER2_IRQHandler
  .word   RTC0_IRQHandler
  .word   TEMP_IRQHandler
  .word   RNG_IRQHandler
  .word   ECB_IRQHandler
  .word   CCM_AAR_IRQHandler
  .word   WDT_IRQHandler
  .word   RTC1_IRQHandler
  .word   QDEC_IRQHandler
  .word   COMP_IRQHandler
  .word   SWI0_EGU0_IRQHandler
  .word   SWI1_EGU1_IRQHandler
  .word   SWI2_IRQHandler
  .word   SWI3_IRQHandler
  .word   SWI4_IRQHandler
  .word   SWI5_IRQHandler
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   PWM0_IRQHandler
  .word   PDM_IRQHandler
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
  .word   0                           /*Reserved */
_vectors_end:

#ifdef VECTORS_IN_RAM
  .section .vectors_ram, "ax"
  .align 0
  .global _vectors_ram

_vectors_ram:
  .space _vectors_end - _vectors, 0
#endif
