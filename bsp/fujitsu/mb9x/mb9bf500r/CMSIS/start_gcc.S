/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-07-01     lgnq         first version
 */

  .syntax unified
  .cpu cortex-m3
  .fpu softvfp
  .thumb

.global  g_pfnVectors
.global  Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word  _sidata
/* start address for the .data section. defined in linker script */
.word  _sdata
/* end address for the .data section. defined in linker script */
.word  _edata
/* start address for the .bss section. defined in linker script */
.word  _sbss
/* end address for the .bss section. defined in linker script */
.word  _ebss

// .equ  Initial_spTop,  0x20000200
.equ  BootRAM,        0xF1E0F85F
/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

  .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:
/* restore original stack pointer */
  ldr   sp, =_estack       /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */
  movs  r1, #0
  b  LoopCopyDataInit

CopyDataInit:
  ldr  r3, =_sidata
  ldr  r3, [r3, r1]
  str  r3, [r0, r1]
  adds  r1, r1, #4

LoopCopyDataInit:
  ldr  r0, =_sdata
  ldr  r3, =_edata
  adds  r2, r0, r1
  cmp  r2, r3
  bcc  CopyDataInit
  ldr  r2, =_sbss
  b  LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
  movs  r3, #0
  str  r3, [r2], #4

LoopFillZerobss:
  ldr  r3, = _ebss
  cmp  r2, r3
  bcc  FillZerobss
/* Call the application's entry point.*/
  bl  main
  bx  lr
.size  Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b  Infinite_Loop
  .size  Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M3.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
  .section  .isr_vector,"a",%progbits
  .type  g_pfnVectors, %object
  .size  g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  MemManage_Handler
  .word  BusFault_Handler
  .word  UsageFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  DebugMon_Handler
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler

  .word  CSV_IRQHandler
  .word  SWDT_IRQHandler
  .word  LVD_IRQHandler
  .word  WFG_IRQHandler
  .word  EXINT0_7_IRQHandler
  .word  EXINT8_15_IRQHandler
  .word  DTIM_QDU_IRQHandler
  .word  MFS0RX_IRQHandler
  .word  MFS0TX_IRQHandler
  .word  MFS1RX_IRQHandler
  .word  MFS1TX_IRQHandler
  .word  MFS2RX_IRQHandler
  .word  MFS2TX_IRQHandler
  .word  MFS3RX_IRQHandler
  .word  MFS3TX_IRQHandler
  .word  MFS4RX_IRQHandler
  .word  MFS4TX_IRQHandler
  .word  MFS5RX_IRQHandler
  .word  MFS5TX_IRQHandler
  .word  MFS6RX_IRQHandler
  .word  MFS6TX_IRQHandler
  .word  MFS7RX_IRQHandler
  .word  MFS7TX_IRQHandler
  .word  PPG_IRQHandler
  .word  OSC_PLL_WC_IRQHandler
  .word  ADC0_IRQHandler
  .word  ADC1_IRQHandler
  .word  ADC2_IRQHandler
  .word  FRTIM_IRQHandler
  .word  INCAP_IRQHandler
  .word  OUTCOMP_IRQHandler
  .word  BTIM_IRQHandler
  .word  CAN0_IRQHandler
  .word  CAN1_IRQHandler
  .word  USBF_IRQHandler
  .word  USBF_USBH_IRQHandler
  .word  RESERVED_1_IRQHandler
  .word  RESERVED_2_IRQHandler
  .word  DMAC0_IRQHandler
  .word  DMAC1_IRQHandler
  .word  DMAC2_IRQHandler
  .word  DMAC3_IRQHandler
  .word  DMAC4_IRQHandler
  .word  DMAC5_IRQHandler
  .word  DMAC6_IRQHandler
  .word  DMAC7_IRQHandler
  .word  RESERVED_3_IRQHandler
  .word  RESERVED_4_IRQHandler

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

  .weak  NMI_Handler
  .thumb_set NMI_Handler,Default_Handler

  .weak  HardFault_Handler
  .thumb_set HardFault_Handler,Default_Handler

  .weak  MemManage_Handler
  .thumb_set MemManage_Handler,Default_Handler

  .weak  BusFault_Handler
  .thumb_set BusFault_Handler,Default_Handler

  .weak  UsageFault_Handler
  .thumb_set UsageFault_Handler,Default_Handler

  .weak  SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

  .weak  DebugMon_Handler
  .thumb_set DebugMon_Handler,Default_Handler

  .weak  PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak  SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak  CSV_IRQHandler
  .thumb_set CSV_IRQHandler,Default_Handler

  .weak  SWDT_IRQHandler
  .thumb_set SWDT_IRQHandler,Default_Handler

  .weak  LVD_IRQHandler
  .thumb_set LVD_IRQHandler,Default_Handler

  .weak  WFG_IRQHandler
  .thumb_set WFG_IRQHandler,Default_Handler

  .weak  EXINT0_7_IRQHandler
  .thumb_set EXINT0_7_IRQHandler,Default_Handler

  .weak  EXINT8_15_IRQHandler
  .thumb_set EXINT8_15_IRQHandler,Default_Handler

  .weak  DTIM_QDU_IRQHandler
  .thumb_set DTIM_QDU_IRQHandler,Default_Handler

  .weak  MFS0RX_IRQHandler
  .thumb_set MFS0RX_IRQHandler,Default_Handler

  .weak  MFS0TX_IRQHandler
  .thumb_set MFS0TX_IRQHandler,Default_Handler

  .weak  MFS1RX_IRQHandler
  .thumb_set MFS1RX_IRQHandler,Default_Handler

  .weak  MFS1TX_IRQHandler
  .thumb_set MFS1TX_IRQHandler,Default_Handler

  .weak  MFS2RX_IRQHandler
  .thumb_set MFS2RX_IRQHandler,Default_Handler

  .weak  MFS2TX_IRQHandler
  .thumb_set MFS2TX_IRQHandler,Default_Handler

  .weak  MFS3RX_IRQHandler
  .thumb_set MFS3RX_IRQHandler,Default_Handler

  .weak  MFS3TX_IRQHandler
  .thumb_set MFS3TX_IRQHandler,Default_Handler

  .weak  MFS4RX_IRQHandler
  .thumb_set MFS4RX_IRQHandler,Default_Handler

  .weak  MFS4TX_IRQHandler
  .thumb_set MFS4TX_IRQHandler,Default_Handler

  .weak  MFS5RX_IRQHandler
  .thumb_set MFS5RX_IRQHandler,Default_Handler

  .weak  MFS5TX_IRQHandler
  .thumb_set MFS5TX_IRQHandler,Default_Handler

  .weak  MFS6RX_IRQHandler
  .thumb_set MFS6RX_IRQHandler,Default_Handler

  .weak  MFS6TX_IRQHandler
  .thumb_set MFS6TX_IRQHandler,Default_Handler

  .weak  MFS7RX_IRQHandler
  .thumb_set MFS7RX_IRQHandler,Default_Handler

  .weak  MFS7TX_IRQHandler
  .thumb_set MFS7TX_IRQHandler,Default_Handler

  .weak  PPG_IRQHandler
  .thumb_set PPG_IRQHandler,Default_Handler

  .weak  OSC_PLL_WC_IRQHandler
  .thumb_set OSC_PLL_WC_IRQHandler,Default_Handler

  .weak  ADC0_IRQHandler
  .thumb_set ADC0_IRQHandler,Default_Handler

  .weak  ADC1_IRQHandler
  .thumb_set ADC1_IRQHandler,Default_Handler

  .weak  ADC2_IRQHandler
  .thumb_set ADC2_IRQHandler,Default_Handler

  .weak  FRTIM_IRQHandler
  .thumb_set FRTIM_IRQHandler,Default_Handler

  .weak  INCAP_IRQHandler
  .thumb_set INCAP_IRQHandler,Default_Handler

  .weak  OUTCOMP_IRQHandler
  .thumb_set OUTCOMP_IRQHandler,Default_Handler

  .weak  BTIM_IRQHandler
  .thumb_set BTIM_IRQHandler,Default_Handler

  .weak  CAN0_IRQHandler
  .thumb_set CAN0_IRQHandler,Default_Handler

  .weak  CAN1_IRQHandler
  .thumb_set CAN1_IRQHandler,Default_Handler

  .weak  USBF_IRQHandler
  .thumb_set USBF_IRQHandler,Default_Handler

  .weak  USBF_USBH_IRQHandler
  .thumb_set USBF_USBH_IRQHandler,Default_Handler

  .weak  RESERVED_1_IRQHandler
  .thumb_set RESERVED_1_IRQHandler,Default_Handler

  .weak  RESERVED_2_IRQHandler
  .thumb_set RESERVED_2_IRQHandler,Default_Handler

  .weak  DMAC0_IRQHandler
  .thumb_set DMAC0_IRQHandler,Default_Handler

  .weak  DMAC1_IRQHandler
  .thumb_set DMAC1_IRQHandler,Default_Handler

  .weak  DMAC2_IRQHandler
  .thumb_set DMAC2_IRQHandler,Default_Handler

  .weak  DMAC3_IRQHandler
  .thumb_set DMAC3_IRQHandler,Default_Handler

  .weak  DMAC4_IRQHandler
  .thumb_set DMAC4_IRQHandler,Default_Handler

  .weak  DMAC5_IRQHandler
  .thumb_set DMAC5_IRQHandler,Default_Handler

  .weak  DMAC6_IRQHandler
  .thumb_set DMAC6_IRQHandler,Default_Handler

  .weak  DMAC7_IRQHandler
  .thumb_set DMAC7_IRQHandler,Default_Handler

  .weak  RESERVED_3_IRQHandler
  .thumb_set RESERVED_3_IRQHandler,Default_Handler

  .weak  RESERVED_4_IRQHandler
  .thumb_set RESERVED_4_IRQHandler,Default_Handler

