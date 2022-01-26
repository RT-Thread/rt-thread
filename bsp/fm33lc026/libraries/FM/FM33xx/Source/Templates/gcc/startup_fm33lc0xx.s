  .syntax unified
  .cpu cortex-m0plus
  .fpu softvfp
  .thumb

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

  .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:  
   ldr   r0, =_estack
   mov   sp, r0          /* set stack pointer */

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
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  ldr  r3, = _ebss
  cmp  r2, r3
  bcc  FillZerobss

/* Call the clock system intitialization function.*/
  bl  SystemInit
/* Call static constructors */
//    bl __libc_init_array
/* Call the application's entry point.*/
  bl  main

LoopForever:
  b LoopForever

  .size  Reset_Handler, .-Reset_Handler
  .section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b  Infinite_Loop
  .size  Default_Handler, .-Default_Handler

/******************************************************************************
*
* The minimal vector table for a Cortex M0.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
  .section  .isr_vector,"a",%progbits
  .global  g_pfnVectors
g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  0
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler
  /* External Interrupts */
  .word  WWDT_IRQHandler           /* 0:  WWDT         */
  .word  SVD_IRQHandler            /* 1:  SVD          */
  .word  RTC_IRQHandler            /* 2:  RTC          */
  .word  FLASH_IRQHandler          /* 3:  FLASH        */
  .word  LFDET_IRQHandler          /* 4:  LFDET        */
  .word  ADC_IRQHandler            /* 5:  ADC          */
  .word  IWDT_IRQHandler           /* 6:  IWDT         */
  .word  SPI1_IRQHandler           /* 7:  SPI1         */
  .word  SPI2_IRQHandler           /* 8:  SPI2         */
  .word  LCD_IRQHandler            /* 9:  LCD          */
  .word  UART0_IRQHandler          /* 10: UART0        */
  .word  UART1_IRQHandler          /* 11: UART1        */
  .word  UART4_IRQHandler          /* 12: UART4        */
  .word  UART5_IRQHandler          /* 13: UART5        */
  .word  HFDET_IRQHandler          /* 14: HFDET        */
  .word  U7816_IRQHandler          /* 15: U7816        */
  .word  LPUART1_IRQHandler        /* 16: LPUART1      */
  .word  I2C_IRQHandler            /* 17: I2C          */
  .word  USB_IRQHandler            /* 18: USB          */
  .word  AES_IRQHandler            /* 19: AES          */
  .word  LPTIM_IRQHandler          /* 20: LPTIM        */
  .word  DMA_IRQHandler            /* 21: DMA          */
  .word  WKUP_IRQHandler           /* 22: WKUP         */
  .word  OPAx_IRQHandler           /* 23: OPAx         */
  .word  BSTIM_IRQHandler          /* 24: BSTIM        */
  .word  COMPx_IRQHandler          /* 25: COMPx        */
  .word  GPTIM0_IRQHandler         /* 26: GPTIM0       */
  .word  GPTIM1_IRQHandler         /* 27: GPTIM1       */
  .word  ATIM_IRQHandler           /* 28: ATIM         */
  .word  VREF_IRQHandler           /* 39: VREF         */
  .word  GPIO_IRQHandler           /* 30: GPIO         */
  .word  LPUART0_IRQHandler        /* 31: LPUART0      */

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

   .weak      SVC_Handler
   .thumb_set SVC_Handler,Default_Handler

   .weak      PendSV_Handler
   .thumb_set PendSV_Handler,Default_Handler

   .weak      SysTick_Handler
   .thumb_set SysTick_Handler,Default_Handler

   .weak      WWDT_IRQHandler
   .thumb_set WWDT_IRQHandler,Default_Handler

   .weak      SVD_IRQHandler
   .thumb_set SVD_IRQHandler,Default_Handler

   .weak      RTC_IRQHandler
   .thumb_set RTC_IRQHandler,Default_Handler

   .weak      FLASH_IRQHandler
   .thumb_set FLASH_IRQHandler,Default_Handler

   .weak      LFDET_IRQHandler
   .thumb_set LFDET_IRQHandler,Default_Handler

   .weak      ADC_IRQHandler
   .thumb_set ADC_IRQHandler,Default_Handler

   .weak      IWDT_IRQHandler
   .thumb_set IWDT_IRQHandler,Default_Handler

   .weak      SPI1_IRQHandler
   .thumb_set SPI1_IRQHandler,Default_Handler

   .weak      SPI2_IRQHandler
   .thumb_set SPI2_IRQHandler,Default_Handler

   .weak      LCD_IRQHandler
   .thumb_set LCD_IRQHandler,Default_Handler

   .weak      UART0_IRQHandler
   .thumb_set UART0_IRQHandler,Default_Handler

   .weak      UART1_IRQHandler
   .thumb_set UART1_IRQHandler,Default_Handler

   .weak      UART4_IRQHandler
   .thumb_set UART4_IRQHandler,Default_Handler

   .weak      UART5_IRQHandler
   .thumb_set UART5_IRQHandler,Default_Handler

   .weak      HFDET_IRQHandler
   .thumb_set HFDET_IRQHandler,Default_Handler

   .weak      U7816_IRQHandler
   .thumb_set U7816_IRQHandler,Default_Handler

   .weak      LPUART1_IRQHandler
   .thumb_set LPUART1_IRQHandler,Default_Handler

   .weak      I2C_IRQHandler
   .thumb_set I2C_IRQHandler,Default_Handler

   .weak      USB_IRQHandler
   .thumb_set USB_IRQHandler,Default_Handler

   .weak      AES_IRQHandler
   .thumb_set AES_IRQHandler,Default_Handler

   .weak      LPTIM_IRQHandler
   .thumb_set LPTIM_IRQHandler,Default_Handler

   .weak      DMA_IRQHandler
   .thumb_set DMA_IRQHandler,Default_Handler

   .weak      WKUP_IRQHandler
   .thumb_set WKUP_IRQHandler,Default_Handler

   .weak      OPAx_IRQHandler
   .thumb_set OPAx_IRQHandler,Default_Handler

   .weak      BSTIM_IRQHandler
   .thumb_set BSTIM_IRQHandler,Default_Handler

   .weak      COMPx_IRQHandler
   .thumb_set COMPx_IRQHandler,Default_Handler

   .weak      GPTIM0_IRQHandler
   .thumb_set GPTIM0_IRQHandler,Default_Handler

   .weak      GPTIM1_IRQHandler
   .thumb_set GPTIM1_IRQHandler,Default_Handler

   .weak      ATIM_IRQHandler
   .thumb_set ATIM_IRQHandler,Default_Handler
   
   .weak      VREF_IRQHandler
   .thumb_set VREF_IRQHandler,Default_Handler

   .weak      GPIO_IRQHandler
   .thumb_set GPIO_IRQHandler,Default_Handler
   
   .weak      LPUART0_IRQHandler
   .thumb_set LPUART0_IRQHandler,Default_Handler

