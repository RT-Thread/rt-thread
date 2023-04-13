/**
  ******************************************************************************
  * @file     startup_at32f421.s
  * @brief    at32f421xx devices vector table for gcc toolchain.
  *           this module performs:
  *           - set the initial sp
  *           - set the initial pc == reset_handler,
  *           - set the vector table entries with the exceptions isr address
  *           - configure the clock system and the external sram to
  *             be used as data memory (optional, to be enabled by user)
  *           - branches to main in the c library (which eventually
  *             calls main()).
  *           after reset the cortex-m4 processor is in thread mode,
  *           priority is privileged, and the stack is set to main.
  ******************************************************************************
  */

  .syntax unified
  .cpu cortex-m4
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
/* stack used for SystemInit_ExtMemCtl; always internal RAM used */

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval None
*/

    .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:

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

/* Call the clock system intitialization function.*/
  bl  SystemInit
/* Call static constructors */
//  bl __libc_init_array
/* Call the application's entry point.*/
  bl  entry
  bx  lr
.size  Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 * @param  None
 * @retval None
*/
    .section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b  Infinite_Loop
  .size  Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M3. Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
*******************************************************************************/
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

  /* External Interrupts */
  .word  WWDT_IRQHandler                     /* Window Watchdog Timer                   */
  .word  PVM_IRQHandler                      /* PVM through EXINT Line detect           */
  .word  ERTC_IRQHandler                     /* ERTC                                    */
  .word  FLASH_IRQHandler                    /* Flash                                   */
  .word  CRM_IRQHandler                      /* CRM                                     */
  .word  EXINT1_0_IRQHandler                 /* EXINT Line 1 & 0                        */
  .word  EXINT3_2_IRQHandler                 /* EXINT Line 3 & 2                        */
  .word  EXINT15_4_IRQHandler                /* EXINT Line 15 ~ 4                       */
  .word  0                                   /* Reserved                                */
  .word  DMA1_Channel1_IRQHandler            /* DMA1 Channel 1                          */
  .word  DMA1_Channel3_2_IRQHandler          /* DMA1 Channel 3 & 2                      */
  .word  DMA1_Channel5_4_IRQHandler          /* DMA1 Channel 5 & 4                      */
  .word  ADC1_CMP_IRQHandler                 /* ADC1 & Comparator                       */
  .word  TMR1_BRK_OVF_TRG_HALL_IRQHandler    /* TMR1 brake overflow trigger and hall    */
  .word  TMR1_CH_IRQHandler                  /* TMR1 channel                            */
  .word  0                                   /* Reserved                                */
  .word  TMR3_GLOBAL_IRQHandler              /* TMR3                                    */
  .word  TMR6_GLOBAL_IRQHandler              /* TMR6                                    */
  .word  0                                   /* Reserved                                */
  .word  TMR14_GLOBAL_IRQHandler             /* TMR14                                   */
  .word  TMR15_GLOBAL_IRQHandler             /* TMR15                                   */
  .word  TMR16_GLOBAL_IRQHandler             /* TMR16                                   */
  .word  TMR17_GLOBAL_IRQHandler             /* TMR17                                   */
  .word  I2C1_EVT_IRQHandler                 /* I2C1 Event                              */
  .word  I2C2_EVT_IRQHandler                 /* I2C2 Event                              */
  .word  SPI1_IRQHandler                     /* SPI1                                    */
  .word  SPI2_IRQHandler                     /* SPI2                                    */
  .word  USART1_IRQHandler                   /* USART1                                  */
  .word  USART2_IRQHandler                   /* USART2                                  */
  .word  0                                   /* Reserved                                */
  .word  0                                   /* Reserved                                */
  .word  0                                   /* Reserved                                */
  .word  I2C1_ERR_IRQHandler                 /* I2C1 Error                              */
  .word  0                                   /* Reserved                                */
  .word  I2C2_ERR_IRQHandler                 /* I2C2 Error                              */

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/
   .weak      NMI_Handler
   .thumb_set NMI_Handler,Default_Handler

   .weak      HardFault_Handler
   .thumb_set HardFault_Handler,Default_Handler

   .weak      MemManage_Handler
   .thumb_set MemManage_Handler,Default_Handler

   .weak      BusFault_Handler
   .thumb_set BusFault_Handler,Default_Handler

   .weak      UsageFault_Handler
   .thumb_set UsageFault_Handler,Default_Handler

   .weak      SVC_Handler
   .thumb_set SVC_Handler,Default_Handler

   .weak      DebugMon_Handler
   .thumb_set DebugMon_Handler,Default_Handler

   .weak      PendSV_Handler
   .thumb_set PendSV_Handler,Default_Handler

   .weak      SysTick_Handler
   .thumb_set SysTick_Handler,Default_Handler

   .weak      WWDT_IRQHandler
   .thumb_set WWDT_IRQHandler,Default_Handler

   .weak      PVM_IRQHandler
   .thumb_set PVM_IRQHandler,Default_Handler

   .weak      ERTC_IRQHandler
   .thumb_set ERTC_IRQHandler,Default_Handler

   .weak      FLASH_IRQHandler
   .thumb_set FLASH_IRQHandler,Default_Handler

   .weak      CRM_IRQHandler
   .thumb_set CRM_IRQHandler,Default_Handler

   .weak      EXINT1_0_IRQHandler
   .thumb_set EXINT1_0_IRQHandler,Default_Handler

   .weak      EXINT3_2_IRQHandler
   .thumb_set EXINT3_2_IRQHandler,Default_Handler

   .weak      EXINT15_4_IRQHandler
   .thumb_set EXINT15_4_IRQHandler,Default_Handler

   .weak      DMA1_Channel1_IRQHandler
   .thumb_set DMA1_Channel1_IRQHandler,Default_Handler

   .weak      DMA1_Channel3_2_IRQHandler
   .thumb_set DMA1_Channel3_2_IRQHandler,Default_Handler

   .weak      DMA1_Channel5_4_IRQHandler
   .thumb_set DMA1_Channel5_4_IRQHandler,Default_Handler

   .weak      ADC1_CMP_IRQHandler
   .thumb_set ADC1_CMP_IRQHandler,Default_Handler

   .weak      TMR1_BRK_OVF_TRG_HALL_IRQHandler
   .thumb_set TMR1_BRK_OVF_TRG_HALL_IRQHandler,Default_Handler

   .weak      TMR1_CH_IRQHandler
   .thumb_set TMR1_CH_IRQHandler,Default_Handler

   .weak      TMR3_GLOBAL_IRQHandler
   .thumb_set TMR3_GLOBAL_IRQHandler,Default_Handler

   .weak      TMR6_GLOBAL_IRQHandler
   .thumb_set TMR6_GLOBAL_IRQHandler,Default_Handler

   .weak      TMR14_GLOBAL_IRQHandler
   .thumb_set TMR14_GLOBAL_IRQHandler,Default_Handler

   .weak      TMR15_GLOBAL_IRQHandler
   .thumb_set TMR15_GLOBAL_IRQHandler,Default_Handler

   .weak      TMR16_GLOBAL_IRQHandler
   .thumb_set TMR16_GLOBAL_IRQHandler,Default_Handler

   .weak      TMR17_GLOBAL_IRQHandler
   .thumb_set TMR17_GLOBAL_IRQHandler,Default_Handler

   .weak      I2C1_EVT_IRQHandler
   .thumb_set I2C1_EVT_IRQHandler,Default_Handler

   .weak      I2C2_EVT_IRQHandler
   .thumb_set I2C2_EVT_IRQHandler,Default_Handler

   .weak      SPI1_IRQHandler
   .thumb_set SPI1_IRQHandler,Default_Handler

   .weak      SPI2_IRQHandler
   .thumb_set SPI2_IRQHandler,Default_Handler

   .weak      USART1_IRQHandler
   .thumb_set USART1_IRQHandler,Default_Handler

   .weak      USART2_IRQHandler
   .thumb_set USART2_IRQHandler,Default_Handler

   .weak      I2C1_ERR_IRQHandler
   .thumb_set I2C1_ERR_IRQHandler,Default_Handler

   .weak      I2C2_ERR_IRQHandler
   .thumb_set I2C2_ERR_IRQHandler,Default_Handler
