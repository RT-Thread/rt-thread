  .syntax unified
  .cpu cortex-m33
  .fpu softvfp
  .thumb

.global  g_pfnVectors
.global  Default_Handler
.extern  FPU_Enable
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
 * @retval : None
*/

    .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:
  ldr   sp, =_estack      /* set stack pointer */

/* Call the clock system initialization function.*/
  bl  FPU_Enable

/* Copy the data segment initializers from flash to SRAM */
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit
/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

/* Call static constructors */
    bl __libc_init_array
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
* The minimal vector table for a Cortex M. Note that the proper constructs
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
  .word     UART0_Handler
  .word     UART1_Handler
  .word     TIMR0_Handler
  .word     TIMR1_Handler
  .word     DMA_Handler
  .word     SPI0_Handler
  .word     PWM0_Handler
  .word     WDT_Handler
  .word     UART2_Handler
  .word     PWM1_Handler
  .word     ADC0_Handler
  .word     BTIMR0_Handler
  .word     HALL0_Handler
  .word     PWM2_Handler
  .word     PWMBRK_Handler
  .word     I2C0_Handler
  .word     CAN0_Handler
  .word     SPI1_Handler
  .word     RTC_Handler
  .word     PWM3_Handler
  .word     TIMR2_Handler
  .word     UART3_Handler
  .word     TIMR3_Handler
  .word     ADC1_Handler
  .word     BOD_Handler
  .word     CORDIC_Handler
  .word     BTIMR1_Handler
  .word     PWM4_Handler
  .word     HALL3_Handler
  .word     BTIMR2_Handler
  .word     I2C1_Handler
  .word     BTIMR3_Handler
  .word     ACMP_Handler
  .word     XTALSTOP_Handler
  .word     FSPI_Handler
  .word     GPIOA_Handler
  .word     GPIOB_Handler
  .word     GPIOC_Handler
  .word     GPIOD_Handler
  .word     GPIOM_Handler
  .word     GPION_Handler
  .word     GPIOA0_Handler
  .word     GPIOA1_Handler
  .word     GPIOA5_Handler
  .word     GPIOA6_Handler
  .word     GPIOA10_Handler
  .word     GPIOA11_Handler
  .word     GPIOA12_Handler
  .word     GPIOA13_Handler
  .word     GPIOB0_Handler
  .word     GPIOB1_Handler
  .word     GPIOB2_Handler
  .word     GPIOC0_Handler
  .word     GPIOC1_Handler
  .word     GPIOC2_Handler
  .word     GPIOC3_Handler
  .word     GPIOC4_Handler
  .word     GPIOD3_Handler
  .word     GPIOD4_Handler
  .word     GPIOD5_Handler
  .word     GPIOD6_Handler
  .word     GPIOD7_Handler
  .word     GPIOD8_Handler
  .word     GPIOC9_Handler
  .word     GPIOC10_Handler
  .word     GPIOC11_Handler
  .word     GPIOC12_Handler
  .word     GPIOM0_Handler
  .word     GPIOM1_Handler
  .word     GPIOM2_Handler
  .word     GPIOM3_Handler
  .word     GPIOM4_Handler
  .word     DIV_Handler
  .word     LCD_Handler
  .word     GPIOE_Handler
  .word     JPEG_Handler
  .word     SDIO_Handler
  .word     USB_Handler
  .word     CAN1_Handler
  .word     TIMR4_Handler
  .word     BTIMR4_Handler
  .word     BTIMR5_Handler
  .word     BTIMR6_Handler
  .word     BTIMR7_Handler
  .word     BTIMR8_Handler
  .word     BTIMR9_Handler
  .word     BTIMR10_Handler
  .word     BTIMR11_Handler
  .word     DMA2D_Handler
  .word     QEI_Handler

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

   .weak      UART0_Handler
   .thumb_set UART0_Handler,Default_Handler

   .weak      UART1_Handler
   .thumb_set UART1_Handler,Default_Handler

   .weak      TIMR0_Handler
   .thumb_set TIMR0_Handler,Default_Handler

   .weak      TIMR1_Handler
   .thumb_set TIMR1_Handler,Default_Handler

   .weak      DMA_Handler
   .thumb_set DMA_Handler,Default_Handler

   .weak      SPI0_Handler
   .thumb_set SPI0_Handler,Default_Handler

   .weak      PWM0_Handler
   .thumb_set PWM0_Handler,Default_Handler

   .weak      WDT_Handler
   .thumb_set WDT_Handler,Default_Handler

   .weak      UART2_Handler
   .thumb_set UART2_Handler,Default_Handler

   .weak      PWM1_Handler
   .thumb_set PWM1_Handler,Default_Handler

   .weak      ADC0_Handler
   .thumb_set ADC0_Handler,Default_Handler

   .weak      BTIMR0_Handler
   .thumb_set BTIMR0_Handler,Default_Handler

   .weak      HALL0_Handler
   .thumb_set HALL0_Handler,Default_Handler

   .weak      PWM2_Handler
   .thumb_set PWM2_Handler,Default_Handler

   .weak      PWMBRK_Handler
   .thumb_set PWMBRK_Handler,Default_Handler

   .weak      I2C0_Handler
   .thumb_set I2C0_Handler,Default_Handler

   .weak      CAN0_Handler
   .thumb_set CAN0_Handler,Default_Handler

   .weak      SPI1_Handler
   .thumb_set SPI1_Handler,Default_Handler

   .weak      RTC_Handler
   .thumb_set RTC_Handler,Default_Handler

   .weak      PWM3_Handler
   .thumb_set PWM3_Handler,Default_Handler

   .weak      TIMR2_Handler
   .thumb_set TIMR2_Handler,Default_Handler

   .weak      UART3_Handler
   .thumb_set UART3_Handler,Default_Handler

   .weak      TIMR3_Handler
   .thumb_set TIMR3_Handler,Default_Handler

   .weak      ADC1_Handler
   .thumb_set ADC1_Handler,Default_Handler

   .weak      BOD_Handler
   .thumb_set BOD_Handler,Default_Handler

   .weak      CORDIC_Handler
   .thumb_set CORDIC_Handler,Default_Handler

   .weak      BTIMR1_Handler
   .thumb_set BTIMR1_Handler,Default_Handler

   .weak      PWM4_Handler
   .thumb_set PWM4_Handler,Default_Handler

   .weak      HALL3_Handler
   .thumb_set HALL3_Handler,Default_Handler

   .weak      BTIMR2_Handler
   .thumb_set BTIMR2_Handler,Default_Handler

   .weak      I2C1_Handler
   .thumb_set I2C1_Handler,Default_Handler

   .weak      BTIMR3_Handler
   .thumb_set BTIMR3_Handler,Default_Handler

   .weak      ACMP_Handler
   .thumb_set ACMP_Handler,Default_Handler

   .weak      XTALSTOP_Handler
   .thumb_set XTALSTOP_Handler,Default_Handler

   .weak      FSPI_Handler
   .thumb_set FSPI_Handler,Default_Handler

   .weak      GPIOA_Handler
   .thumb_set GPIOA_Handler,Default_Handler

   .weak      GPIOB_Handler
   .thumb_set GPIOB_Handler,Default_Handler

   .weak      GPIOC_Handler
   .thumb_set GPIOC_Handler,Default_Handler

   .weak      GPIOD_Handler
   .thumb_set GPIOD_Handler,Default_Handler

   .weak      GPIOM_Handler
   .thumb_set GPIOM_Handler,Default_Handler

   .weak      GPION_Handler
   .thumb_set GPION_Handler,Default_Handler

   .weak      GPIOA0_Handler
   .thumb_set GPIOA0_Handler,Default_Handler

   .weak      GPIOA1_Handler
   .thumb_set GPIOA1_Handler,Default_Handler

   .weak      GPIOA5_Handler
   .thumb_set GPIOA5_Handler,Default_Handler

   .weak      GPIOA6_Handler
   .thumb_set GPIOA6_Handler,Default_Handler

   .weak      GPIOA10_Handler
   .thumb_set GPIOA10_Handler,Default_Handler

   .weak      GPIOA11_Handler
   .thumb_set GPIOA11_Handler,Default_Handler

   .weak      GPIOA12_Handler
   .thumb_set GPIOA12_Handler,Default_Handler

   .weak      GPIOA13_Handler
   .thumb_set GPIOA13_Handler,Default_Handler

   .weak      GPIOB0_Handler
   .thumb_set GPIOB0_Handler,Default_Handler

   .weak      GPIOB1_Handler
   .thumb_set GPIOB1_Handler,Default_Handler

   .weak      GPIOB2_Handler
   .thumb_set GPIOB2_Handler,Default_Handler

   .weak      GPIOC0_Handler
   .thumb_set GPIOC0_Handler,Default_Handler

   .weak      GPIOC1_Handler
   .thumb_set GPIOC1_Handler,Default_Handler

   .weak      GPIOC2_Handler
   .thumb_set GPIOC2_Handler,Default_Handler

   .weak      GPIOC3_Handler
   .thumb_set GPIOC3_Handler,Default_Handler

   .weak      GPIOC4_Handler
   .thumb_set GPIOC4_Handler,Default_Handler

   .weak      GPIOD3_Handler
   .thumb_set GPIOD3_Handler,Default_Handler

   .weak      GPIOD4_Handler
   .thumb_set GPIOD4_Handler,Default_Handler

   .weak      GPIOD5_Handler
   .thumb_set GPIOD5_Handler,Default_Handler

   .weak      GPIOD6_Handler
   .thumb_set GPIOD6_Handler,Default_Handler

   .weak      GPIOD7_Handler
   .thumb_set GPIOD7_Handler,Default_Handler

   .weak      GPIOD8_Handler
   .thumb_set GPIOD8_Handler,Default_Handler

   .weak      GPIOC9_Handler
   .thumb_set GPIOC9_Handler,Default_Handler

   .weak      GPIOC10_Handler
   .thumb_set GPIOC10_Handler,Default_Handler

   .weak      GPIOC11_Handler
   .thumb_set GPIOC11_Handler,Default_Handler

   .weak      GPIOC12_Handler
   .thumb_set GPIOC12_Handler,Default_Handler

   .weak      GPIOM0_Handler
   .thumb_set GPIOM0_Handler,Default_Handler

   .weak      GPIOM1_Handler
   .thumb_set GPIOM1_Handler,Default_Handler

   .weak      GPIOM2_Handler
   .thumb_set GPIOM2_Handler,Default_Handler

   .weak      GPIOM3_Handler
   .thumb_set GPIOM3_Handler,Default_Handler

   .weak      GPIOM4_Handler
   .thumb_set GPIOM4_Handler,Default_Handler

   .weak      DIV_Handler
   .thumb_set DIV_Handler,Default_Handler

   .weak      LCD_Handler
   .thumb_set LCD_Handler,Default_Handler

   .weak      GPIOE_Handler
   .thumb_set GPIOE_Handler,Default_Handler

   .weak      JPEG_Handler
   .thumb_set JPEG_Handler,Default_Handler

   .weak      SDIO_Handler
   .thumb_set SDIO_Handler,Default_Handler

   .weak      USB_Handler
   .thumb_set USB_Handler,Default_Handler

   .weak      CAN1_Handler
   .thumb_set CAN1_Handler,Default_Handler

   .weak      TIMR4_Handler
   .thumb_set TIMR4_Handler,Default_Handler

   .weak      BTIMR4_Handler
   .thumb_set BTIMR4_Handler,Default_Handler

   .weak      BTIMR5_Handler
   .thumb_set BTIMR5_Handler,Default_Handler

   .weak      BTIMR6_Handler
   .thumb_set BTIMR6_Handler,Default_Handler

   .weak      BTIMR7_Handler
   .thumb_set BTIMR7_Handler,Default_Handler

   .weak      BTIMR8_Handler
   .thumb_set BTIMR8_Handler,Default_Handler

   .weak      BTIMR9_Handler
   .thumb_set BTIMR9_Handler,Default_Handler

   .weak      BTIMR10_Handler
   .thumb_set BTIMR10_Handler,Default_Handler

   .weak      BTIMR11_Handler
   .thumb_set BTIMR11_Handler,Default_Handler

   .weak      DMA2D_Handler
   .thumb_set DMA2D_Handler,Default_Handler

   .weak      QEI_Handler
   .thumb_set QEI_Handler,Default_Handler
   