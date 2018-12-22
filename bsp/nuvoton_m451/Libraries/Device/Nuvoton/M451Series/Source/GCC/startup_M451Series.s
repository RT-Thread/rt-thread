/**
  ******************************************************************************
  * @file      startup_M451Series.s
  * @author    RT-Thread Develop Team
  * @version   V1.0.0
  * @date      2016-12-07
  * @brief     M451Series Devices vector table for GCC toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M4 processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  *            It's ported from startup_M051Series.s
  ******************************************************************************
*/
    
  .syntax unified
  .cpu cortex-m4
  .fpu softvfp
  .thumb

.global g_pfnVectors
.global Default_Handler

/* start address for the initialization values of the .data section. 
defined in linker script */
.word _sidata
/* start address for the .data section. defined in linker script */  
.word _sdata
/* end address for the .data section. defined in linker script */
.word _edata
/* start address for the .bss section. defined in linker script */
.word _sbss
/* end address for the .bss section. defined in linker script */
.word _ebss

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called. 
 * @param  None
 * @retval : None
*/

    .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:

  /* Unlock Register */
  ldr     r0, =0x40000100
  ldr     r1, =0x59
  str     r1, [R0]
  ldr     r1, =0x16
  str     r1, [R0]
  ldr     r1, =0x88
  str     r1, [r0]

  /* Init POR */
  ldr     r2, =0x40000024
  ldr     r1, =0x00005AA5
  str     r1, [r2]

  /* Select INV Type*/
  ldr     r2, =0x40000200
  ldr     r1, [r2]
  bic     r1, r1, #0x1000
  str     r1, [r2]
  
  /* Lock register */
  movs r1, #0
  str r1, [r0] 

  /* Copy the data segment initializers from flash to SRAM */  
  movs r1, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r3, =_sidata
  ldr r3, [r3, r1]
  str r3, [r0, r1]
  adds r1, r1, #4
    
LoopCopyDataInit:
  ldr r0, =_sdata
  ldr r3, =_edata
  adds r2, r0, r1
  cmp r2, r3
  bcc CopyDataInit
  ldr r2, =_sbss
  b LoopFillZerobss
/* Zero fill the bss segment. */  
FillZerobss:
  movs r3, #0
/* Here I changed*/
  str  r3, [r2], #4
    
LoopFillZerobss:
  ldr r3, = _ebss
  cmp r2, r3
  bcc FillZerobss
  /* Call the clock system intitialization function.*/
  bl  SystemInit
  /* Call the application's entry point.*/
  bl main
  bx lr
.size Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an 
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval None
*/
    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler
/*******************************************************************************
*
* The minimal vector table for a Cortex M0. Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*******************************************************************************/
  .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
  .word _estack
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word MemManage_Handler
  .word BusFault_Handler
  .word UsageFault_Handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word SVC_Handler
  .word DebugMon_Handler
  .word 0
  .word PendSV_Handler
  .word SysTick_Handler
  /* External Interrupts */
  .word BOD_IRQHandler            /* 0: Brown Out detection        */
  .word IRC_IRQHandler            /* 1: Internal RC                */
  .word PWRWU_IRQHandler          /* 2: Power down wake up         */
  .word RAMPE_IRQHandler          /* 3: RAM parity error           */
  .word CLKFAIL_IRQHandler        /* 4: Clock detection fail       */
  .word Default_Handler           /* 5: Reserved                   */
  .word RTC_IRQHandler            /* 6: Real Time Clock            */
  .word TAMPER_IRQHandler         /* 7: Tamper detection           */
  .word WDT_IRQHandler            /* 8: Watchdog timer             */
  .word WWDT_IRQHandler           /* 9: Window watchdog timer      */
  .word EINT0_IRQHandler          /* 10: External Input 0          */
  .word EINT1_IRQHandler          /* 11: External Input 1          */
  .word EINT2_IRQHandler          /* 12: External Input 2          */
  .word EINT3_IRQHandler          /* 13: External Input 3          */
  .word EINT4_IRQHandler          /* 14: External Input 4          */
  .word EINT5_IRQHandler          /* 15: External Input 5          */
  .word GPA_IRQHandler            /* 16: GPIO Port A               */
  .word GPB_IRQHandler            /* 17: GPIO Port B               */
  .word GPC_IRQHandler            /* 18: GPIO Port C               */
  .word GPD_IRQHandler            /* 19: GPIO Port D               */
  .word GPE_IRQHandler            /* 20: GPIO Port E               */
  .word GPF_IRQHandler            /* 21: GPIO Port F               */
  .word SPI0_IRQHandler           /* 22: SPI0                      */
  .word SPI1_IRQHandler           /* 23: SPI1                      */
  .word BRAKE0_IRQHandler         /* 24:                           */
  .word PWM0P0_IRQHandler         /* 25:                           */
  .word PWM0P1_IRQHandler         /* 26:                           */
  .word PWM0P2_IRQHandler         /* 27:                           */
  .word BRAKE1_IRQHandler         /* 28:                           */
  .word PWM1P0_IRQHandler         /* 29:                           */
  .word PWM1P1_IRQHandler         /* 30:                           */
  .word PWM1P2_IRQHandler         /* 31:                           */
  .word TMR0_IRQHandler           /* 32: Timer 0                   */
  .word TMR1_IRQHandler           /* 33: Timer 1                   */
  .word TMR2_IRQHandler           /* 34: Timer 2                   */
  .word TMR3_IRQHandler           /* 35: Timer 3                   */
  .word UART0_IRQHandler          /* 36: UART0                     */
  .word UART1_IRQHandler          /* 37: UART1                     */
  .word I2C0_IRQHandler           /* 38: I2C0                      */
  .word I2C1_IRQHandler           /* 39: I2C1                      */
  .word PDMA_IRQHandler           /* 40: Peripheral DMA            */
  .word DAC_IRQHandler            /* 41: DAC                       */
  .word ADC00_IRQHandler          /* 42: ADC0 interrupt source 0   */
  .word ADC01_IRQHandler          /* 43: ADC0 interrupt source 1   */
  .word ACMP01_IRQHandler         /* 44: ACMP0 and ACMP1           */
  .word Default_Handler           /* 45: Reserved                  */
  .word ADC02_IRQHandler          /* 46: ADC0 interrupt source 2   */
  .word ADC03_IRQHandler          /* 47: ADC0 interrupt source 3   */
  .word UART2_IRQHandler          /* 48: UART2                     */
  .word UART3_IRQHandler          /* 49: UART3                     */
  .word Default_Handler           /* 50: Reserved                  */
  .word SPI2_IRQHandler           /* 51: SPI2                      */
  .word Default_Handler           /* 52: Reserved                  */
  .word USBD_IRQHandler           /* 53: USB device                */
  .word USBH_IRQHandler           /* 54: USB host                  */
  .word USBOTG_IRQHandler         /* 55: USB OTG                   */
  .word CAN0_IRQHandler           /* 56: CAN0                      */
  .word Default_Handler           /* 57: Reserved                  */
  .word SC0_IRQHandler            /* 58:                           */
  .word Default_Handler           /* 59: Reserved.                 */
  .word Default_Handler           /* 60:                           */
  .word Default_Handler           /* 61:                           */
  .word Default_Handler           /* 62:                           */
  .word TK_IRQHandler             /* 63:                           */
                                                                   
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
   
   .weak      BOD_IRQHandler
   .thumb_set BOD_IRQHandler, Default_Handler
   
   .weak      IRC_IRQHandler
   .thumb_set IRC_IRQHandler, Default_Handler
   
   .weak      PWRWU_IRQHandler
   .thumb_set PWRWU_IRQHandler, Default_Handler
   
   .weak      RAMPE_IRQHandler
   .thumb_set RAMPE_IRQHandler, Default_Handler
   
   .weak      CLKFAIL_IRQHandler
   .thumb_set CLKFAIL_IRQHandler, Default_Handler
   
   .weak      Default_Handler
   .thumb_set Default_Handler, Default_Handler
   
   .weak      RTC_IRQHandler
   .thumb_set RTC_IRQHandler, Default_Handler
   
   .weak      TAMPER_IRQHandler
   .thumb_set TAMPER_IRQHandler, Default_Handler
   
   .weak      WDT_IRQHandler
   .thumb_set WDT_IRQHandler, Default_Handler
   
   .weak      WWDT_IRQHandler
   .thumb_set WWDT_IRQHandler, Default_Handler
   
   .weak      EINT0_IRQHandler
   .thumb_set EINT0_IRQHandler, Default_Handler
   
   .weak      EINT1_IRQHandler
   .thumb_set EINT1_IRQHandler, Default_Handler
   
   .weak      EINT2_IRQHandler
   .thumb_set EINT2_IRQHandler, Default_Handler
   
   .weak      EINT3_IRQHandler
   .thumb_set EINT3_IRQHandler, Default_Handler
   
   .weak      EINT4_IRQHandler
   .thumb_set EINT4_IRQHandler, Default_Handler
   
   .weak      EINT5_IRQHandler
   .thumb_set EINT5_IRQHandler, Default_Handler
   
   .weak      GPA_IRQHandler
   .thumb_set GPA_IRQHandler, Default_Handler
   
   .weak      GPB_IRQHandler
   .thumb_set GPB_IRQHandler, Default_Handler
   
   .weak      GPC_IRQHandler
   .thumb_set GPC_IRQHandler, Default_Handler
   
   .weak      GPD_IRQHandler
   .thumb_set GPD_IRQHandler, Default_Handler
   
   .weak      GPE_IRQHandler
   .thumb_set GPE_IRQHandler, Default_Handler
   
   .weak      GPF_IRQHandler
   .thumb_set GPF_IRQHandler, Default_Handler
   
   .weak      SPI0_IRQHandler
   .thumb_set SPI0_IRQHandler, Default_Handler
   
   .weak      SPI1_IRQHandler
   .thumb_set SPI1_IRQHandler, Default_Handler
   
   .weak      BRAKE0_IRQHandler
   .thumb_set BRAKE0_IRQHandler, Default_Handler
   
   .weak      PWM0P0_IRQHandler
   .thumb_set PWM0P0_IRQHandler, Default_Handler
   
   .weak      PWM0P1_IRQHandler
   .thumb_set PWM0P1_IRQHandler, Default_Handler
   
   .weak      PWM0P2_IRQHandler
   .thumb_set PWM0P2_IRQHandler, Default_Handler
   
   .weak      BRAKE1_IRQHandler
   .thumb_set BRAKE1_IRQHandler, Default_Handler
   
   .weak      PWM1P0_IRQHandler
   .thumb_set PWM1P0_IRQHandler, Default_Handler
   
   .weak      PWM1P1_IRQHandler
   .thumb_set PWM1P1_IRQHandler, Default_Handler
   
   .weak      PWM1P2_IRQHandler
   .thumb_set PWM1P2_IRQHandler, Default_Handler
   
   .weak      TMR0_IRQHandler
   .thumb_set TMR0_IRQHandler, Default_Handler
   
   .weak      TMR1_IRQHandler
   .thumb_set TMR1_IRQHandler, Default_Handler
   
   .weak      TMR2_IRQHandler
   .thumb_set TMR2_IRQHandler, Default_Handler
   
   .weak      TMR3_IRQHandler
   .thumb_set TMR3_IRQHandler, Default_Handler
   
   .weak      UART0_IRQHandler
   .thumb_set UART0_IRQHandler, Default_Handler
   
   .weak      UART1_IRQHandler
   .thumb_set UART1_IRQHandler, Default_Handler
   
   .weak      I2C0_IRQHandler
   .thumb_set I2C0_IRQHandler, Default_Handler
   
   .weak      I2C1_IRQHandler
   .thumb_set I2C1_IRQHandler, Default_Handler
   
   .weak      PDMA_IRQHandler
   .thumb_set PDMA_IRQHandler, Default_Handler
   
   .weak      DAC_IRQHandler
   .thumb_set DAC_IRQHandler, Default_Handler
   
   .weak      ADC00_IRQHandler
   .thumb_set ADC00_IRQHandler, Default_Handler
   
   .weak      ADC01_IRQHandler
   .thumb_set ADC01_IRQHandler, Default_Handler
   
   .weak      ACMP01_IRQHandler
   .thumb_set ACMP01_IRQHandler, Default_Handler
   
   .weak      Default_Handler
   .thumb_set Default_Handler, Default_Handler
   
   .weak      ADC02_IRQHandler
   .thumb_set ADC02_IRQHandler, Default_Handler
   
   .weak      ADC03_IRQHandler
   .thumb_set ADC03_IRQHandler, Default_Handler
   
   .weak      UART2_IRQHandler
   .thumb_set UART2_IRQHandler, Default_Handler
   
   .weak      UART3_IRQHandler
   .thumb_set UART3_IRQHandler, Default_Handler
   
   .weak      Default_Handler
   .thumb_set Default_Handler, Default_Handler
   
   .weak      SPI2_IRQHandler
   .thumb_set SPI2_IRQHandler, Default_Handler
   
   .weak      Default_Handler
   .thumb_set Default_Handler, Default_Handler
   
   .weak      USBD_IRQHandler
   .thumb_set USBD_IRQHandler, Default_Handler
   
   .weak      USBH_IRQHandler
   .thumb_set USBH_IRQHandler, Default_Handler
   
   .weak      USBOTG_IRQHandler
   .thumb_set USBOTG_IRQHandler, Default_Handler
   
   .weak      CAN0_IRQHandler
   .thumb_set CAN0_IRQHandler, Default_Handler
   
   .weak      Default_Handler
   .thumb_set Default_Handler, Default_Handler
   
   .weak      SC0_IRQHandler
   .thumb_set SC0_IRQHandler, Default_Handler
   
   .weak      Default_Handler
   .thumb_set Default_Handler, Default_Handler
   
   .weak      Default_Handler
   .thumb_set Default_Handler, Default_Handler
   
   .weak      Default_Handler
   .thumb_set Default_Handler, Default_Handler
   
   .weak      Default_Handler
   .thumb_set Default_Handler, Default_Handler
   
   .weak      TK_IRQHandler
   .thumb_set TK_IRQHandler, Default_Handler
/************************ END OF FILE ***********************/

