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
  .weak SVC_Handler
SVC_Handler:
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

  .weak UART0_IRQHandler
  .thumb_set UART0_IRQHandler,Dummy_Handler

  .weak SPI0_TWI0_IRQHandler
  .thumb_set SPI0_TWI0_IRQHandler,Dummy_Handler

  .weak SPI1_TWI1_IRQHandler
  .thumb_set SPI1_TWI1_IRQHandler,Dummy_Handler

  .weak GPIOTE_IRQHandler
  .thumb_set GPIOTE_IRQHandler,Dummy_Handler

  .weak ADC_IRQHandler
  .thumb_set ADC_IRQHandler,Dummy_Handler

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

  .weak LPCOMP_IRQHandler
  .thumb_set LPCOMP_IRQHandler,Dummy_Handler

  .weak SWI0_IRQHandler
  .thumb_set SWI0_IRQHandler,Dummy_Handler

  .weak SWI1_IRQHandler
  .thumb_set SWI1_IRQHandler,Dummy_Handler

  .weak SWI2_IRQHandler
  .thumb_set SWI2_IRQHandler,Dummy_Handler

  .weak SWI3_IRQHandler
  .thumb_set SWI3_IRQHandler,Dummy_Handler

  .weak SWI4_IRQHandler
  .thumb_set SWI4_IRQHandler,Dummy_Handler

  .weak SWI5_IRQHandler
  .thumb_set SWI5_IRQHandler,Dummy_Handler

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
  .weak UART0_IRQHandler
UART0_IRQHandler:
  b .

  .thumb_func
  .weak SPI0_TWI0_IRQHandler
SPI0_TWI0_IRQHandler:
  b .

  .thumb_func
  .weak SPI1_TWI1_IRQHandler
SPI1_TWI1_IRQHandler:
  b .

  .thumb_func
  .weak GPIOTE_IRQHandler
GPIOTE_IRQHandler:
  b .

  .thumb_func
  .weak ADC_IRQHandler
ADC_IRQHandler:
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
  .weak LPCOMP_IRQHandler
LPCOMP_IRQHandler:
  b .

  .thumb_func
  .weak SWI0_IRQHandler
SWI0_IRQHandler:
  b .

  .thumb_func
  .weak SWI1_IRQHandler
SWI1_IRQHandler:
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
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word SVC_Handler
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word PendSV_Handler
  .word SysTick_Handler
  .word POWER_CLOCK_IRQHandler
  .word RADIO_IRQHandler
  .word UART0_IRQHandler
  .word SPI0_TWI0_IRQHandler
  .word SPI1_TWI1_IRQHandler
  .word Dummy_Handler /* Reserved */
  .word GPIOTE_IRQHandler
  .word ADC_IRQHandler
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
  .word LPCOMP_IRQHandler
  .word SWI0_IRQHandler
  .word SWI1_IRQHandler
  .word SWI2_IRQHandler
  .word SWI3_IRQHandler
  .word SWI4_IRQHandler
  .word SWI5_IRQHandler
_vectors_end:

#ifdef VECTORS_IN_RAM
  .section .vectors_ram, "ax"
  .align 0
  .global _vectors_ram

_vectors_ram:
  .space _vectors_end - _vectors, 0
#endif
