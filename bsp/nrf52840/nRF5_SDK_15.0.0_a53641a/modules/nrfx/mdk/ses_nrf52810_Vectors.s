/*****************************************************************************
 *                   SEGGER Microcontroller GmbH & Co. KG                    *
 *            Solutions for real time microcontroller applications           *
 *****************************************************************************
 *                                                                           *
 *               (c) 2017 SEGGER Microcontroller GmbH & Co. KG               *
 *                                                                           *
 *           Internet: www.segger.com   Support: support@segger.com          *
 *                                                                           *
 *****************************************************************************/

/*****************************************************************************
 *                         Preprocessor Definitions                          *
 *                         ------------------------                          *
 * VECTORS_IN_RAM                                                            *
 *                                                                           *
 *   If defined, an area of RAM will large enough to store the vector table  *
 *   will be reserved.                                                       *
 *                                                                           *
 *****************************************************************************/

  .syntax unified
  .code 16

  .section .init, "ax"
  .align 0

/*****************************************************************************
 * Default Exception Handlers                                                *
 *****************************************************************************/

  .thumb_func
  .weak NMI_Handler
NMI_Handler:
  b .

  .thumb_func
  .weak HardFault_Handler
HardFault_Handler:
  b .
  
  .thumb_func
  .weak MemoryManagement_Handler
MemoryManagement_Handler:
  b .
  
  .thumb_func
  .weak BusFault_Handler
BusFault_Handler:
  b .
  
  .thumb_func
  .weak UsageFault_Handler
UsageFault_Handler:
  b .

  .thumb_func
  .weak SVC_Handler
SVC_Handler:
  b .

  .thumb_func
  .weak DebugMon_Handler
DebugMon_Handler:
  b .
  
  .thumb_func
  .weak PendSV_Handler
PendSV_Handler:
  b .

  .thumb_func
  .weak SysTick_Handler
SysTick_Handler:
  b .

  .thumb_func
Dummy_Handler:
  b .

#if defined(__OPTIMIZATION_SMALL)

  .weak POWER_CLOCK_IRQHandler
  .thumb_set POWER_CLOCK_IRQHandler,Dummy_Handler

  .weak RADIO_IRQHandler
  .thumb_set RADIO_IRQHandler,Dummy_Handler

  .weak UARTE0_IRQHandler
  .thumb_set UARTE0_IRQHandler,Dummy_Handler

  .weak TWIM0_TWIS0_IRQHandler
  .thumb_set TWIM0_TWIS0_IRQHandler,Dummy_Handler

  .weak SPIM0_SPIS0_IRQHandler
  .thumb_set SPIM0_SPIS0_IRQHandler,Dummy_Handler

  .weak GPIOTE_IRQHandler
  .thumb_set GPIOTE_IRQHandler,Dummy_Handler

  .weak SAADC_IRQHandler
  .thumb_set SAADC_IRQHandler,Dummy_Handler

  .weak TIMER0_IRQHandler
  .thumb_set TIMER0_IRQHandler,Dummy_Handler

  .weak TIMER1_IRQHandler
  .thumb_set TIMER1_IRQHandler,Dummy_Handler

  .weak TIMER2_IRQHandler
  .thumb_set TIMER2_IRQHandler,Dummy_Handler

  .weak RTC0_IRQHandler
  .thumb_set RTC0_IRQHandler,Dummy_Handler

  .weak TEMP_IRQHandler
  .thumb_set TEMP_IRQHandler,Dummy_Handler

  .weak RNG_IRQHandler
  .thumb_set RNG_IRQHandler,Dummy_Handler

  .weak ECB_IRQHandler
  .thumb_set ECB_IRQHandler,Dummy_Handler

  .weak CCM_AAR_IRQHandler
  .thumb_set CCM_AAR_IRQHandler,Dummy_Handler

  .weak WDT_IRQHandler
  .thumb_set WDT_IRQHandler,Dummy_Handler

  .weak RTC1_IRQHandler
  .thumb_set RTC1_IRQHandler,Dummy_Handler

  .weak QDEC_IRQHandler
  .thumb_set QDEC_IRQHandler,Dummy_Handler

  .weak COMP_IRQHandler
  .thumb_set COMP_IRQHandler,Dummy_Handler

  .weak SWI0_EGU0_IRQHandler
  .thumb_set SWI0_EGU0_IRQHandler,Dummy_Handler

  .weak SWI1_EGU1_IRQHandler
  .thumb_set SWI1_EGU1_IRQHandler,Dummy_Handler

  .weak SWI2_IRQHandler
  .thumb_set SWI2_IRQHandler,Dummy_Handler

  .weak SWI3_IRQHandler
  .thumb_set SWI3_IRQHandler,Dummy_Handler

  .weak SWI4_IRQHandler
  .thumb_set SWI4_IRQHandler,Dummy_Handler

  .weak SWI5_IRQHandler
  .thumb_set SWI5_IRQHandler,Dummy_Handler

  .weak PWM0_IRQHandler
  .thumb_set PWM0_IRQHandler,Dummy_Handler

  .weak PDM_IRQHandler
  .thumb_set PDM_IRQHandler,Dummy_Handler

#else

  .thumb_func
  .weak POWER_CLOCK_IRQHandler
POWER_CLOCK_IRQHandler:
  b .

  .thumb_func
  .weak RADIO_IRQHandler
RADIO_IRQHandler:
  b .

  .thumb_func
  .weak UARTE0_IRQHandler
UARTE0_IRQHandler:
  b .

  .thumb_func
  .weak TWIM0_TWIS0_IRQHandler
TWIM0_TWIS0_IRQHandler:
  b .

  .thumb_func
  .weak SPIM0_SPIS0_IRQHandler
SPIM0_SPIS0_IRQHandler:
  b .

  .thumb_func
  .weak GPIOTE_IRQHandler
GPIOTE_IRQHandler:
  b .

  .thumb_func
  .weak SAADC_IRQHandler
SAADC_IRQHandler:
  b .

  .thumb_func
  .weak TIMER0_IRQHandler
TIMER0_IRQHandler:
  b .

  .thumb_func
  .weak TIMER1_IRQHandler
TIMER1_IRQHandler:
  b .

  .thumb_func
  .weak TIMER2_IRQHandler
TIMER2_IRQHandler:
  b .

  .thumb_func
  .weak RTC0_IRQHandler
RTC0_IRQHandler:
  b .

  .thumb_func
  .weak TEMP_IRQHandler
TEMP_IRQHandler:
  b .

  .thumb_func
  .weak RNG_IRQHandler
RNG_IRQHandler:
  b .

  .thumb_func
  .weak ECB_IRQHandler
ECB_IRQHandler:
  b .

  .thumb_func
  .weak CCM_AAR_IRQHandler
CCM_AAR_IRQHandler:
  b .

  .thumb_func
  .weak WDT_IRQHandler
WDT_IRQHandler:
  b .

  .thumb_func
  .weak RTC1_IRQHandler
RTC1_IRQHandler:
  b .

  .thumb_func
  .weak QDEC_IRQHandler
QDEC_IRQHandler:
  b .

  .thumb_func
  .weak COMP_IRQHandler
COMP_IRQHandler:
  b .

  .thumb_func
  .weak SWI0_EGU0_IRQHandler
SWI0_EGU0_IRQHandler:
  b .

  .thumb_func
  .weak SWI1_EGU1_IRQHandler
SWI1_EGU1_IRQHandler:
  b .

  .thumb_func
  .weak SWI2_IRQHandler
SWI2_IRQHandler:
  b .

  .thumb_func
  .weak SWI3_IRQHandler
SWI3_IRQHandler:
  b .

  .thumb_func
  .weak SWI4_IRQHandler
SWI4_IRQHandler:
  b .

  .thumb_func
  .weak SWI5_IRQHandler
SWI5_IRQHandler:
  b .

  .thumb_func
  .weak PWM0_IRQHandler
PWM0_IRQHandler:
  b .

  .thumb_func
  .weak PDM_IRQHandler
PDM_IRQHandler:
  b .

#endif

/*****************************************************************************
 * Vector Table                                                              *
 *****************************************************************************/

  .section .vectors, "ax"
  .align 0
  .global _vectors
  .extern __stack_end__
  .extern Reset_Handler

_vectors:
  .word __stack_end__
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word MemoryManagement_Handler
  .word BusFault_Handler
  .word UsageFault_Handler
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word SVC_Handler
  .word DebugMon_Handler
  .word 0 /* Reserved */
  .word PendSV_Handler
  .word SysTick_Handler
  .word POWER_CLOCK_IRQHandler
  .word RADIO_IRQHandler
  .word UARTE0_IRQHandler
  .word TWIM0_TWIS0_IRQHandler
  .word SPIM0_SPIS0_IRQHandler
  .word 0
  .word GPIOTE_IRQHandler
  .word SAADC_IRQHandler
  .word TIMER0_IRQHandler
  .word TIMER1_IRQHandler
  .word TIMER2_IRQHandler
  .word RTC0_IRQHandler
  .word TEMP_IRQHandler
  .word RNG_IRQHandler
  .word ECB_IRQHandler
  .word CCM_AAR_IRQHandler
  .word WDT_IRQHandler
  .word RTC1_IRQHandler
  .word QDEC_IRQHandler
  .word COMP_IRQHandler
  .word SWI0_EGU0_IRQHandler
  .word SWI1_EGU1_IRQHandler
  .word SWI2_IRQHandler
  .word SWI3_IRQHandler
  .word SWI4_IRQHandler
  .word SWI5_IRQHandler
  .word 0
  .word 0
  .word PWM0_IRQHandler
  .word PDM_IRQHandler
_vectors_end:

#ifdef VECTORS_IN_RAM
  .section .vectors_ram, "ax"
  .align 0
  .global _vectors_ram

_vectors_ram:
  .space _vectors_end - _vectors, 0
#endif
