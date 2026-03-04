/*********************************************************************************************************
     Copyright (c) 2024, Nations Technologies Inc.
 
     All rights reserved.

     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
 referred to as NATIONS). This software, and the product of NATIONS described herein 
 (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
 of the People's Republic of China and other applicable jurisdictions worldwide.

     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
 intellectual property rights. Names and brands of third party may be mentioned or referred 
 thereto (if any) for identification purposes only.

     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
 improvements to this software at any time without notice. Please contact NATIONS and obtain 
 the latest version of this software before placing orders.

     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
 no responsibility for the accuracy and reliability of this software.
 
     It is the responsibility of the user of this software to properly design, program, and test 
 the functionality and safety of any application made of this information and any resulting product. 
 In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
 consequential damages arising in any way out of the use of this software or the Product.

     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
 malfunction or failure of which may cause loss of human life, bodily injury or severe property 
 damage. Such applications are deemed, "Insecure Usage".

     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
 harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
 to any customer's Insecure Usage.

     Any express or implied warranty with regard to this software or the Product, including,but not 
 limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
 are disclaimed to the fullest extent permitted by law.

     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
 or otherwise distribute this software for any purposes, in whole or in part.

     NATIONS products and technologies shall not be used for or incorporated into any products or systems
 whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
 User shall comply with any applicable export control laws and regulations promulgated and administered by 
 the governments of any countries asserting jurisdiction over the parties or transactions.
 ************************************************************************************************************/


  .syntax unified
  .cpu cortex-m7
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

  .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
  ldr   r0, =_estack
  mov   sp, r0          /* set stack pointer */

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

/* Call the clock system intitialization function.*/
  bl  SystemInit
/* Call static constructors */
  bl __libc_init_array
/* Call the application's entry point.*/
  bl main

LoopForever:
    b LoopForever


.size Reset_Handler, .-Reset_Handler

/**
\*fun      This is the code that gets called when the processor receives an
\*         unexpected interrupt.  This simply enters an infinite loop, preserving
\*         the system state for examination by a debugger.
**/
    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler
/**
\* The minimal vector table for a Cortex M0.  Note that the proper constructs
\* must be placed on this to ensure that it ends up at physical address 0x00000000.
**/
   .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors


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
  .word  N32SysTick_Handler  
  /* External Interrupts */
  .word  WWDG1_IRQHandler           /*  Window1 Watchdog interrupt  */                     
  .word  PVD_IRQHandler             /*  PVD through EXTI Line16 detection interrupt */
  .word  RTC_TAMPER_IRQHandler      /*  RTC Tamper_Timestamp_Overflow or LSE-CSS through EXTI Line18 interrupt */
  .word  RTC_WKUP_IRQHandler        /*  RTC Wakeup timer through EXTI line 19 interrupt */
  .word  RCC_IRQHandler             /*  RCC interrupt */
  .word  EXTI0_IRQHandler           /*  EXTI Line 0 interrupt    */
  .word  EXTI1_IRQHandler           /*  EXTI Line 1 interrupt    */
  .word  EXTI2_IRQHandler           /*  EXTI Line 2 interrupt    */
  .word  EXTI3_IRQHandler           /*  EXTI Line 3 interrupt    */
  .word  EXTI4_IRQHandler           /*  EXTI Line 4 interrupt    */
  .word  EXTI9_5_IRQHandler         /*  EXTI Line[9:5] interrupt  */
  .word  EXTI15_10_IRQHandler       /*  EXTI Line[15:10] interrupt */
  .word  DMA1_Channel0_IRQHandler   /*  DMA1 Channel 0  */
  .word  DMA1_Channel1_IRQHandler   /*  DMA1 Channel 1  */
  .word  DMA1_Channel2_IRQHandler   /*  DMA1 Channel 2  */
  .word  DMA1_Channel3_IRQHandler   /*  DMA1 Channel 3  */
  .word  DMA1_Channel4_IRQHandler   /*  DMA1 Channel 4  */
  .word  DMA1_Channel5_IRQHandler   /*  DMA1 Channel 5  */
  .word  DMA1_Channel6_IRQHandler   /*  DMA1 Channel 6  */
  .word  DMA1_Channel7_IRQHandler   /*  DMA1 Channel 7  */
  .word  DMA2_Channel0_IRQHandler   /*  DMA2 Channel 0  */
  .word  DMA2_Channel1_IRQHandler   /*  DMA2 Channel 1  */
  .word  DMA2_Channel2_IRQHandler   /*  DMA2 Channel 2  */
  .word  DMA2_Channel3_IRQHandler   /*  DMA2 Channel 3  */
  .word  DMA2_Channel4_IRQHandler   /*  DMA2 Channel 4  */
  .word  DMA2_Channel5_IRQHandler   /*  DMA2 Channel 5  */
  .word  DMA2_Channel6_IRQHandler   /*  DMA2 Channel 6  */
  .word  DMA2_Channel7_IRQHandler   /*  DMA2 Channel 7  */
  .word  DMA3_Channel0_IRQHandler   /*  DMA3 Channel 0  */
  .word  DMA3_Channel1_IRQHandler   /*  DMA3 Channel 1  */
  .word  DMA3_Channel2_IRQHandler   /*  DMA3 Channel 2  */
  .word  DMA3_Channel3_IRQHandler   /*  DMA3 Channel 3  */
  .word  DMA3_Channel4_IRQHandler   /*  DMA3 Channel 4  */
  .word  DMA3_Channel5_IRQHandler   /*  DMA3 Channel 5  */
  .word  DMA3_Channel6_IRQHandler   /*  DMA3 Channel 6  */
  .word  DMA3_Channel7_IRQHandler   /*  DMA3 Channel 7  */
  .word  MDMA_Channel0_IRQHandler   /*  MDMA Channel 0  */
  .word  MDMA_Channel1_IRQHandler   /*  MDMA Channel 1  */
  .word  MDMA_Channel2_IRQHandler   /*  MDMA Channel 2  */
  .word  MDMA_Channel3_IRQHandler   /*  MDMA Channel 3  */
  .word  MDMA_Channel4_IRQHandler   /*  MDMA Channel 4  */
  .word  MDMA_Channel5_IRQHandler   /*  MDMA Channel 5  */
  .word  MDMA_Channel6_IRQHandler   /*  MDMA Channel 6  */
  .word  MDMA_Channel7_IRQHandler   /*  MDMA Channel 7  */
  .word  MDMA_Channel8_IRQHandler   /*  MDMA Channel 8  */
  .word  MDMA_Channel9_IRQHandler   /*  MDMA Channel 9  */
  .word  MDMA_Channel10_IRQHandler  /*  MDMA Channel 10 */
  .word  MDMA_Channel11_IRQHandler  /*  MDMA Channel 11 */
  .word  MDMA_Channel12_IRQHandler  /*  MDMA Channel 12 */
  .word  MDMA_Channel13_IRQHandler  /*  MDMA Channel 13 */
  .word  MDMA_Channel14_IRQHandler  /*  MDMA Channel 14 */
  .word  MDMA_Channel15_IRQHandler  /*  MDMA Channel 15 */
  .word  SDPU_IRQHandler            /*  SDPU global interrupt */
  .word  0                          /*  Reserved */
  .word  0                          /*  Reserved */
  .word  FPU_CPU1_IRQHandler		/*  FPU_CM7 global interrupt	*/	
  .word  ECCMON_IRQHandler          /*  ECCMON global interrupt */
  .word  RTC_ALARM_IRQHandler       /*  RTC Alarm via EXTI17 interrupt */
  .word  I2C1_EV_IRQHandler         /*  I2C1 event interrupt */
  .word  I2C1_ER_IRQHandler         /*  I2C1 error interrupt */
  .word  I2C2_EV_IRQHandler         /*  I2C2 event interrupt */
  .word  I2C2_ER_IRQHandler         /*  I2C2 error interrupt */
  .word  I2C3_EV_IRQHandler         /*  I2C3 event interrupt */
  .word  I2C3_ER_IRQHandler         /*  I2C3 error interrupt */
  .word  I2C4_EV_IRQHandler         /*  I2C4 event interrupt */
  .word  I2C4_ER_IRQHandler         /*  I2C4 error interrupt */
  .word  I2C5_EV_IRQHandler         /*  I2C5 event interrupt */
  .word  I2C5_ER_IRQHandler         /*  I2C5 error interrupt */
  .word  I2C6_EV_IRQHandler         /*  I2C6 event interrupt */
  .word  I2C6_ER_IRQHandler         /*  I2C6 error interrupt */
  .word  I2C7_EV_IRQHandler         /*  I2C7 event interrupt */
  .word  I2C7_ER_IRQHandler         /*  I2C7 error interrupt */
  .word  I2C8_EV_IRQHandler         /*  I2C8 event interrupt */
  .word  I2C8_ER_IRQHandler         /*  I2C8 error interrupt */
  .word  I2C9_EV_IRQHandler         /*  I2C9 event interrupt */
  .word  I2C9_ER_IRQHandler         /*  I2C9 error interrupt */
  .word  I2C10_EV_IRQHandler        /*  I2C10 event interrupt */
  .word  I2C10_ER_IRQHandler        /*  I2C10 error interrupt */
  .word  I2S1_IRQHandler            /*  I2S1 global interrupt */
  .word  I2S2_IRQHandler            /*  I2S1 global interrupt */
  .word  I2S3_IRQHandler            /*  I2S1 global interrupt */
  .word  I2S4_IRQHandler            /*  I2S1 global interrupt */
  .word  xSPI1_IRQHandler           /*  xSPI1 global interrupt */
  .word  xSPI2_IRQHandler           /*  xSPI1 global interrupt */
  .word  SPI1_IRQHandler            /*  SPI1 global interrupt  */
  .word  SPI2_IRQHandler            /*  SPI2 global interrupt  */
  .word  SPI3_IRQHandler            /*  SPI3 global interrupt  */
  .word  SPI4_IRQHandler            /*  SPI4 global interrupt  */
  .word  SPI5_IRQHandler            /*  SPI5 global interrupt  */
  .word  SPI6_IRQHandler            /*  SPI6 global interrupt  */
  .word  SPI7_IRQHandler            /*  SPI7 global interrupt  */
  .word  LCD_EV_IRQHandler          /*  TFT LCD Controller event interrupt */
  .word  LCD_ER_IRQHandler          /*  TFT LCD Controller error interrupt */
  .word  DVP1_IRQHandler            /*  DVP1 global interrupt */
  .word  DVP2_IRQHandler            /*  DVP2 global interrupt */
  .word  DMAMUX2_IRQHandler         /*  DMAMUX2 (MDMA MUX) global interrupt */
  .word  USB1_HS_EPx_OUT_IRQHandler  /*  USB1_HS endpoint out global interrupt */
  .word  USB1_HS_EPx_IN_IRQHandler   /*  USB1_HS endpoint in global interrupt */
  .word  USB1_HS_WKUP_IRQHandler     /*  USB1_HS WKUP interrupt through EXTI line 62 */
  .word  USB1_HS_IRQHandler          /*  USB1_HS global interrupt */
  .word  USB2_HS_EPx_OUT_IRQHandler  /*  USB2_HS  endpoint out global interrupt */
  .word  USB2_HS_EPx_IN_IRQHandler   /*  USB2_HS  endpoint in global interrupt */
  .word  USB2_HS_WKUP_IRQHandler     /*  USB2_HS WKUP interrupt through EXTI line 63 */
  .word  USB2_HS_IRQHandler          /*  USB2_HS global interrupt */
  .word  ETH1_IRQHandler             /*  Ethernet 1 global interrupt */
  .word  ETH1_PMT_LPI_IRQHandler     /*  Ethernet 1 PMT wakeup interrupt and LPI interrupt through EXTI line 83 */
  .word  ETH2_IRQHandler             /*  Ethernet 2 global interrupt */
  .word  ETH2_PMT_LPI_IRQHandler     /*  Ethernet 2  PMT wakeup interrupt and LPI interrupt through EXTI line 84 */
  .word  FDCAN1_INT0_IRQHandler      /*  FDCAN1 global interrupt line 0  */
  .word  FDCAN2_INT0_IRQHandler      /*  FDCAN2 global interrupt line 0  */
  .word  FDCAN3_INT0_IRQHandler      /*  FDCAN3 global interrupt line 0  */
  .word  FDCAN4_INT0_IRQHandler      /*  FDCAN4 global interrupt line 0  */
  .word  FDCAN1_INT1_IRQHandler      /*  FDCAN1 global interrupt line 1  */
  .word  FDCAN2_INT1_IRQHandler      /*  FDCAN2 global interrupt line 1  */
  .word  FDCAN3_INT1_IRQHandler      /*  FDCAN3 global interrupt line 1  */
  .word  FDCAN4_INT1_IRQHandler      /*  FDCAN4 global interrupt line 1  */
  .word  USART1_IRQHandler           /*  USART1 global interrupt  */
  .word  USART2_IRQHandler           /*  USART2 global interrupt  */
  .word  USART3_IRQHandler           /*  USART3 global interrupt  */
  .word  USART4_IRQHandler           /*  USART4 global interrupt  */
  .word  USART5_IRQHandler           /*  USART5 global interrupt  */
  .word  USART6_IRQHandler           /*  USART6 global interrupt  */
  .word  USART7_IRQHandler           /*  USART7 global interrupt  */
  .word  USART8_IRQHandler           /*  USART8 global interrupt  */
  .word  UART9_IRQHandler            /*  UART9 global interrupt   */
  .word  UART10_IRQHandler           /*  UART10 global interrupt  */
  .word  UART11_IRQHandler           /*  UART11 global interrupt  */
  .word  UART12_IRQHandler           /*  UART12 global interrupt  */
  .word  UART13_IRQHandler           /*  UART13 global interrupt  */
  .word  UART14_IRQHandler           /*  UART14 global interrupt  */
  .word  UART15_IRQHandler           /*  UART15 global interrupt  */
  .word  LPUART1_IRQHandler          /*  LPUART1 global interrupt + wakeup through EXTI line 49 */
  .word  LPUART2_IRQHandler          /*  LPUART2 global interrupt + wakeup through EXTI line 52 */
  .word  GPU_IRQHandler              /*  GPU global interrupt */
  .word  0                           /*  Reserved  */
  .word  SDMMC1_IRQHandler           /*  SDMMC1_IRQ + WKUP through EXTI line 24  */
  .word  SDMMC2_IRQHandler           /*  SDMMC2_IRQ + WKUP  through EXTI line 25  */
  .word  ADC1_IRQHandler             /*  ADC1 global interrupt  */
  .word  ADC2_IRQHandler             /*  ADC2 global interrupt  */
  .word  ADC3_IRQHandler             /*  ADC3 global interrupt  */
  .word  COMP1_2_IRQHandler          /*  COMP1 and COMP2 through EXTI line 20 and 21  */
  .word  COMP3_4_IRQHandler          /*  COMP3 and COMP4  through EXTI line 22 and 23  */
  .word  SHRTIM1_INT1_IRQHandler    /*  High Resolution timer 1 interrupt 1  */
  .word  SHRTIM1_INT2_IRQHandler    /*  High Resolution timer 1 interrupt 2  */ 
  .word  SHRTIM1_INT3_IRQHandler    /*  High Resolution timer 1 interrupt 3  */ 
  .word  SHRTIM1_INT4_IRQHandler    /*  High Resolution timer 1 interrupt 4  */ 
  .word  SHRTIM1_INT5_IRQHandler    /*  High Resolution timer 1 interrupt 5  */ 
  .word  SHRTIM1_INT6_IRQHandler    /*  High Resolution timer 1 interrupt 6  */ 
  .word  SHRTIM1_INT7_IRQHandler    /*  High Resolution timer 1 interrupt 7  */ 
  .word  SHRTIM1_INT8_IRQHandler    /*  High Resolution timer 1 interrupt 8  */ 
  .word  SHRTIM2_INT1_IRQHandler    /*  High Resolution timer 2 interrupt 1  */
  .word  SHRTIM2_INT2_IRQHandler    /*  High Resolution timer 2 interrupt 2  */ 
  .word  SHRTIM2_INT3_IRQHandler    /*  High Resolution timer 2 interrupt 3  */ 
  .word  SHRTIM2_INT4_IRQHandler    /*  High Resolution timer 2 interrupt 4  */ 
  .word  SHRTIM2_INT5_IRQHandler    /*  High Resolution timer 2 interrupt 5  */ 
  .word  SHRTIM2_INT6_IRQHandler    /*  High Resolution timer 2 interrupt 6  */ 
  .word  SHRTIM2_INT7_IRQHandler    /*  High Resolution timer 2 interrupt 7  */ 
  .word  SHRTIM2_INT8_IRQHandler    /*  High Resolution timer 2 interrupt 8  */ 
  .word  FDCAN5_INT0_IRQHandler     /*  FDCAN5 global interrupt line 0  */
  .word  FDCAN6_INT0_IRQHandler     /*  FDCAN6 global interrupt line 0  */
  .word  FDCAN7_INT0_IRQHandler     /*  FDCAN7 global interrupt line 0  */
  .word  FDCAN8_INT0_IRQHandler     /*  FDCAN8 global interrupt line 0  */
  .word  FDCAN5_INT1_IRQHandler     /*  FDCAN5 global interrupt line 1  */
  .word  FDCAN6_INT1_IRQHandler     /*  FDCAN6 global interrupt line 1  */
  .word  FDCAN7_INT1_IRQHandler     /*  FDCAN7 global interrupt line 1  */
  .word  FDCAN8_INT1_IRQHandler     /*  FDCAN8 global interrupt line 1  */
  .word  0                           /*  Reserved  */
  .word  0                           /*  Reserved  */
  .word  LPTIM5_WKUP_IRQHandler      /*  LPTIM5 wakeup  through EXTI 86   */
  .word  JPEG_SGDMA_H2P_IRQHandler   /*  JPEG SGDMA Host to Peripheral Interrupt  */
  .word  JPEG_SGDMA_P2H_IRQHandler   /*  JPEG SGDMA Peripheral to Host Interrupt  */
  .word  WAKEUP_IO_IRQHandler        /*  6 WAKEUP IOs through EXTI line 70-75  */
  .word  SEMA4_INT1_IRQHandler       /*  SEMA4 interrupt1  */
  .word  0                           /*  Reserved  */
  .word  WWDG2_RST_IRQHandler        /*  WWDG2 reset interrupt through EXTI line 82  */
  .word  OTPC_IRQHandler             /*  OTPC interrupt  */
  .word  FEMC_IRQHandler             /*  FEMC interrupt  */
  .word  DCMUB_IRQHandler            /*  DCMUB interrupt  */
  .word  DAC1_IRQHandler             /*  DAC1 interrupt  */
  .word  DAC2_IRQHandler             /*  DAC2 interrupt  */
  .word  MDMA_AHBS_ER_IRQHandler     /*  MDMA HABS ERROR through EXTI line55-56  */
  .word  CM7_CATCH_READ_ER_IRQHandler   /*  CM7 Error on Cache Read  through EXTI line 64-65  */
  .word  DAC3_IRQHandler             /*  DAC3 interrupt  */
  .word  DAC4_IRQHandler             /*  DAC4 interrupt  */
  .word  EMC_IRQHandler              /*  EMC event interrupt through EXTI line 88-89  */
  .word  DAC5_IRQHandler             /*  DAC5 interrupt  */
  .word  DAC6_IRQHandler             /*  DAC6 interrupt  */
  .word  0        				     /*  Reserved  */
  .word  0      					 /*  Reserved  */
  .word  0       				     /*  Reserved  */
  .word  0        				     /*  Reserved  */
  .word  0                           /*  Reserved  */  			  
  .word  ATIM1_BRK_IRQHandler        /*  Advanced timer 1 break interrupt  */
  .word  ATIM1_TRG_COM_IRQHandler    /*  Advanced timer 1 trigger and commutation interrupts  */
  .word  ATIM1_CC_IRQHandler         /*  Advanced timer 1 capture/compare interrupt  */
  .word  ATIM1_UP_IRQHandler         /*  Advanced timer 1 update interrupt  */
  .word  ATIM2_BRK_IRQHandler        /*  Advanced timer 2 break interrupt  */
  .word  ATIM2_TRG_COM_IRQHandler    /*  advanced timer 2 trigger and commutation interrupts  */
  .word  ATIM2_CC_IRQHandler         /*  Advanced timer 2 capture/compare interrupt  */
  .word  ATIM2_UP_IRQHandler         /*  Advanced timer 2 update interrupt  */
  .word  ATIM3_BRK_IRQHandler       /*  Advanced timer 3 break interrupt  */
  .word  ATIM3_TRG_COM_IRQHandler   /*  Advanced timer 3 trigger and commutation interrupts  */
  .word  ATIM3_CC_IRQHandler        /*  Advanced timer 3 capture/compare interrupt  */
  .word  ATIM3_UP_IRQHandler        /*  Advanced timer 3 update interrupt  */
  .word  ATIM4_BRK_IRQHandler       /*  Advanced timer 4 break interrupt  */
  .word  ATIM4_TRG_COM_IRQHandler   /*  Advanced timer 4 trigger and commutation interrupts  */
  .word  ATIM4_CC_IRQHandler        /*  Advanced timer 4 capture/compare interrupt  */
  .word  ATIM4_UP_IRQHandler        /*  Advanced timer 4 update interrupt  */
  .word  GTIMA1_IRQHandler          /*  General timer A1 global interrupt  */
  .word  GTIMA2_IRQHandler          /*  General timer A2 global interrupt  */
  .word  GTIMA3_IRQHandler          /*  General timer A3 global interrupt  */
  .word  GTIMA4_IRQHandler          /*  General timer A4 global interrupt  */
  .word  GTIMA5_IRQHandler          /*  General timer A5 global interrupt  */
  .word  GTIMA6_IRQHandler          /*  General timer A6 global interrupt  */
  .word  GTIMA7_IRQHandler          /*  General timer A7 global interrupt  */
  .word  GTIMB1_IRQHandler          /*  General timer B1 global interrupt  */
  .word  GTIMB2_IRQHandler          /*  General timer B2 global interrupt  */
  .word  GTIMB3_IRQHandler          /*  General timer B3 global interrupt  */
  .word  BTIM1_IRQHandler           /*  Base timer 1 global interrupt  */
  .word  BTIM2_IRQHandler           /*  Base timer 2 global interrupt  */
  .word  BTIM3_IRQHandler           /*  Base timer 3 global interrupt  */
  .word  BTIM4_IRQHandler           /*  Base timer 4 global interrupt  */
  .word  LPTIM1_WKUP_IRQHandler     /*  LPTIM1 wakeup interrupt  */
  .word  LPTIM2_WKUP_IRQHandler     /*  LPTIM2 wakeup interrupt  */
  .word  LPTIM3_WKUP_IRQHandler     /*  LPTIM3 wakeup interrupt  */
  .word  LPTIM4_WKUP_IRQHandler     /*  LPTIM4 wakeup interrupt  */
  .word  DSMU_FLT0_IRQHandler       /*  DSMU Filter interrupt 0  */
  .word  DSMU_FLT1_IRQHandler       /*  DSMU Filter interrupt 1  */
  .word  DSMU_FLT2_IRQHandler       /*  DSMU Filter interrupt 2  */
  .word  DSMU_FLT3_IRQHandler       /*  DSMU Filter interrupt 3  */
  .word  FMAC_IRQHandler            /*  FMAC global interrupt  */
  .word  CORDIC_IRQHandler          /*  Cordic global interrupt  */
  .word  DMAMUX1_IRQHandler         /*  DMAMUX1 interrupt  */
  .word  MMU_IRQHandler             /*  MMU interrupt   */  
  .word  SysTick_Handler     
  /* need check to user manual of exti chapter   */

/**
\* Provide weak aliases for each Exception handler to the Default_Handler.
\* As they are weak aliases, any function with the same name will override
\* this definition.
**/

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

  .weak      N32SysTick_Handler
  .thumb_set N32SysTick_Handler,Default_Handler
  
  .weak      WWDG1_IRQHandler
  .thumb_set WWDG1_IRQHandler,Default_Handler

  .weak      PVD_IRQHandler
  .thumb_set PVD_IRQHandler,Default_Handler

  .weak      RTC_TAMPER_IRQHandler
  .thumb_set RTC_TAMPER_IRQHandler,Default_Handler

  .weak      RTC_WKUP_IRQHandler
  .thumb_set RTC_WKUP_IRQHandler,Default_Handler

  .weak      RCC_IRQHandler
  .thumb_set RCC_IRQHandler,Default_Handler

  .weak      EXTI0_IRQHandler
  .thumb_set EXTI0_IRQHandler,Default_Handler

  .weak      EXTI1_IRQHandler
  .thumb_set EXTI1_IRQHandler,Default_Handler

  .weak      EXTI2_IRQHandler
  .thumb_set EXTI2_IRQHandler,Default_Handler

  .weak      EXTI3_IRQHandler
  .thumb_set EXTI3_IRQHandler,Default_Handler

  .weak      EXTI4_IRQHandler
  .thumb_set EXTI4_IRQHandler,Default_Handler

  .weak      EXTI9_5_IRQHandler
  .thumb_set EXTI9_5_IRQHandler,Default_Handler

  .weak      EXTI15_10_IRQHandler
  .thumb_set EXTI15_10_IRQHandler,Default_Handler

  .weak      DMA1_Channel0_IRQHandler
  .thumb_set DMA1_Channel0_IRQHandler,Default_Handler

  .weak      DMA1_Channel1_IRQHandler
  .thumb_set DMA1_Channel1_IRQHandler,Default_Handler

  .weak      DMA1_Channel2_IRQHandler
  .thumb_set DMA1_Channel2_IRQHandler,Default_Handler

  .weak      DMA1_Channel3_IRQHandler
  .thumb_set DMA1_Channel3_IRQHandler,Default_Handler

  .weak      DMA1_Channel4_IRQHandler
  .thumb_set DMA1_Channel4_IRQHandler,Default_Handler

  .weak      DMA1_Channel5_IRQHandler
  .thumb_set DMA1_Channel5_IRQHandler,Default_Handler

  .weak      DMA1_Channel6_IRQHandler
  .thumb_set DMA1_Channel6_IRQHandler,Default_Handler

  .weak      DMA1_Channel7_IRQHandler
  .thumb_set DMA1_Channel7_IRQHandler,Default_Handler

  .weak      DMA2_Channel0_IRQHandler
  .thumb_set DMA2_Channel0_IRQHandler,Default_Handler

  .weak      DMA2_Channel1_IRQHandler
  .thumb_set DMA2_Channel1_IRQHandler,Default_Handler

  .weak      DMA2_Channel2_IRQHandler
  .thumb_set DMA2_Channel2_IRQHandler,Default_Handler

  .weak      DMA2_Channel3_IRQHandler
  .thumb_set DMA2_Channel3_IRQHandler,Default_Handler

  .weak      DMA2_Channel4_IRQHandler
  .thumb_set DMA2_Channel4_IRQHandler,Default_Handler

  .weak      DMA2_Channel5_IRQHandler
  .thumb_set DMA2_Channel5_IRQHandler,Default_Handler

  .weak      DMA2_Channel6_IRQHandler
  .thumb_set DMA2_Channel6_IRQHandler,Default_Handler

  .weak      DMA2_Channel7_IRQHandler
  .thumb_set DMA2_Channel7_IRQHandler,Default_Handler

  .weak      DMA3_Channel0_IRQHandler
  .thumb_set DMA3_Channel0_IRQHandler,Default_Handler

  .weak      DMA3_Channel1_IRQHandler
  .thumb_set DMA3_Channel1_IRQHandler,Default_Handler

  .weak      DMA3_Channel2_IRQHandler
  .thumb_set DMA3_Channel2_IRQHandler,Default_Handler

  .weak      DMA3_Channel3_IRQHandler
  .thumb_set DMA3_Channel3_IRQHandler,Default_Handler

  .weak      DMA3_Channel4_IRQHandler
  .thumb_set DMA3_Channel4_IRQHandler,Default_Handler

  .weak      DMA3_Channel5_IRQHandler
  .thumb_set DMA3_Channel5_IRQHandler,Default_Handler

  .weak      DMA3_Channel6_IRQHandler
  .thumb_set DMA3_Channel6_IRQHandler,Default_Handler

  .weak      DMA3_Channel7_IRQHandler
  .thumb_set DMA3_Channel7_IRQHandler,Default_Handler
  
  .weak      MDMA_Channel0_IRQHandler
  .thumb_set MDMA_Channel0_IRQHandler,Default_Handler

  .weak      MDMA_Channel1_IRQHandler
  .thumb_set MDMA_Channel1_IRQHandler,Default_Handler

  .weak      MDMA_Channel2_IRQHandler
  .thumb_set MDMA_Channel2_IRQHandler,Default_Handler

  .weak      MDMA_Channel3_IRQHandler
  .thumb_set MDMA_Channel3_IRQHandler,Default_Handler

  .weak      MDMA_Channel4_IRQHandler
  .thumb_set MDMA_Channel4_IRQHandler,Default_Handler

  .weak      MDMA_Channel5_IRQHandler
  .thumb_set MDMA_Channel5_IRQHandler,Default_Handler

  .weak      MDMA_Channel6_IRQHandler
  .thumb_set MDMA_Channel6_IRQHandler,Default_Handler

  .weak      MDMA_Channel7_IRQHandler
  .thumb_set MDMA_Channel7_IRQHandler,Default_Handler

  .weak      MDMA_Channel8_IRQHandler
  .thumb_set MDMA_Channel8_IRQHandler,Default_Handler

  .weak      MDMA_Channel9_IRQHandler
  .thumb_set MDMA_Channel9_IRQHandler,Default_Handler

  .weak      MDMA_Channel10_IRQHandler
  .thumb_set MDMA_Channel10_IRQHandler,Default_Handler

  .weak      MDMA_Channel11_IRQHandler
  .thumb_set MDMA_Channel11_IRQHandler,Default_Handler

  .weak      MDMA_Channel12_IRQHandler
  .thumb_set MDMA_Channel12_IRQHandler,Default_Handler

  .weak      MDMA_Channel13_IRQHandler
  .thumb_set MDMA_Channel13_IRQHandler,Default_Handler

  .weak      MDMA_Channel14_IRQHandler
  .thumb_set MDMA_Channel14_IRQHandler,Default_Handler

  .weak      MDMA_Channel15_IRQHandler
  .thumb_set MDMA_Channel15_IRQHandler,Default_Handler

  .weak      SDPU_IRQHandler
  .thumb_set SDPU_IRQHandler,Default_Handler

  .weak      FPU_CPU1_IRQHandler
  .thumb_set FPU_CPU1_IRQHandler,Default_Handler

  .weak      ECCMON_IRQHandler
  .thumb_set ECCMON_IRQHandler,Default_Handler

  .weak      RTC_ALARM_IRQHandler
  .thumb_set RTC_ALARM_IRQHandler,Default_Handler

  .weak      I2C1_EV_IRQHandler
  .thumb_set I2C1_EV_IRQHandler,Default_Handler

  .weak      I2C1_ER_IRQHandler
  .thumb_set I2C1_ER_IRQHandler,Default_Handler

  .weak      I2C2_EV_IRQHandler
  .thumb_set I2C2_EV_IRQHandler,Default_Handler

  .weak      I2C2_ER_IRQHandler
  .thumb_set I2C2_ER_IRQHandler,Default_Handler

  .weak      I2C3_EV_IRQHandler
  .thumb_set I2C3_EV_IRQHandler,Default_Handler

  .weak      I2C3_ER_IRQHandler
  .thumb_set I2C3_ER_IRQHandler,Default_Handler

  .weak      I2C4_EV_IRQHandler
  .thumb_set I2C4_EV_IRQHandler,Default_Handler

  .weak      I2C4_ER_IRQHandler
  .thumb_set I2C4_ER_IRQHandler,Default_Handler

  .weak      I2C5_EV_IRQHandler
  .thumb_set I2C5_EV_IRQHandler,Default_Handler

  .weak      I2C5_ER_IRQHandler
  .thumb_set I2C5_ER_IRQHandler,Default_Handler

  .weak      I2C6_EV_IRQHandler
  .thumb_set I2C6_EV_IRQHandler,Default_Handler

  .weak      I2C6_ER_IRQHandler
  .thumb_set I2C6_ER_IRQHandler,Default_Handler

  .weak      I2C7_EV_IRQHandler
  .thumb_set I2C7_EV_IRQHandler,Default_Handler

  .weak      I2C7_ER_IRQHandler
  .thumb_set I2C7_ER_IRQHandler,Default_Handler

  .weak      I2C8_EV_IRQHandler
  .thumb_set I2C8_EV_IRQHandler,Default_Handler

  .weak      I2C8_ER_IRQHandler
  .thumb_set I2C8_ER_IRQHandler,Default_Handler

  .weak      I2C9_EV_IRQHandler
  .thumb_set I2C9_EV_IRQHandler,Default_Handler

  .weak      I2C9_ER_IRQHandler
  .thumb_set I2C9_ER_IRQHandler,Default_Handler

  .weak      I2C10_EV_IRQHandler
  .thumb_set I2C10_EV_IRQHandler,Default_Handler

  .weak      I2C10_ER_IRQHandler
  .thumb_set I2C10_ER_IRQHandler,Default_Handler

  .weak      I2S1_IRQHandler
  .thumb_set I2S1_IRQHandler,Default_Handler

  .weak      I2S2_IRQHandler
  .thumb_set I2S2_IRQHandler,Default_Handler

  .weak      I2S3_IRQHandler
  .thumb_set I2S3_IRQHandler,Default_Handler

  .weak      I2S4_IRQHandler
  .thumb_set I2S4_IRQHandler,Default_Handler

  .weak      xSPI1_IRQHandler
  .thumb_set xSPI1_IRQHandler,Default_Handler

  .weak      xSPI2_IRQHandler
  .thumb_set xSPI2_IRQHandler,Default_Handler

  .weak      SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,Default_Handler

  .weak      SPI2_IRQHandler
  .thumb_set SPI2_IRQHandler,Default_Handler

  .weak      SPI3_IRQHandler
  .thumb_set SPI3_IRQHandler,Default_Handler

  .weak      SPI4_IRQHandler
  .thumb_set SPI4_IRQHandler,Default_Handler

  .weak      SPI5_IRQHandler
  .thumb_set SPI5_IRQHandler,Default_Handler

  .weak      SPI6_IRQHandler
  .thumb_set SPI6_IRQHandler,Default_Handler

  .weak      SPI7_IRQHandler
  .thumb_set SPI7_IRQHandler,Default_Handler

  .weak      LCD_EV_IRQHandler
  .thumb_set LCD_EV_IRQHandler,Default_Handler

  .weak      LCD_ER_IRQHandler
  .thumb_set LCD_ER_IRQHandler,Default_Handler

  .weak      DVP1_IRQHandler
  .thumb_set DVP1_IRQHandler,Default_Handler

  .weak      DVP2_IRQHandler
  .thumb_set DVP2_IRQHandler,Default_Handler

  .weak      DMAMUX2_IRQHandler
  .thumb_set DMAMUX2_IRQHandler,Default_Handler

  .weak      USB1_HS_EPx_OUT_IRQHandler
  .thumb_set USB1_HS_EPx_OUT_IRQHandler,Default_Handler

  .weak      USB1_HS_EPx_IN_IRQHandler
  .thumb_set USB1_HS_EPx_IN_IRQHandler,Default_Handler

  .weak      USB1_HS_WKUP_IRQHandler
  .thumb_set USB1_HS_WKUP_IRQHandler,Default_Handler

  .weak      USB1_HS_IRQHandler
  .thumb_set USB1_HS_IRQHandler,Default_Handler

  .weak      USB2_HS_EPx_OUT_IRQHandler
  .thumb_set USB2_HS_EPx_OUT_IRQHandler,Default_Handler

  .weak      USB2_HS_EPx_IN_IRQHandler
  .thumb_set USB2_HS_EPx_IN_IRQHandler,Default_Handler

  .weak      USB2_HS_WKUP_IRQHandler
  .thumb_set USB2_HS_WKUP_IRQHandler,Default_Handler

  .weak      USB2_HS_IRQHandler
  .thumb_set USB2_HS_IRQHandler,Default_Handler

  .weak      ETH1_IRQHandler
  .thumb_set ETH1_IRQHandler,Default_Handler

  .weak      ETH1_PMT_LPI_IRQHandler
  .thumb_set ETH1_PMT_LPI_IRQHandler,Default_Handler

  .weak      ETH2_IRQHandler
  .thumb_set ETH2_IRQHandler,Default_Handler

  .weak      ETH2_PMT_LPI_IRQHandler
  .thumb_set ETH2_PMT_LPI_IRQHandler,Default_Handler

  .weak      FDCAN1_INT0_IRQHandler
  .thumb_set FDCAN1_INT0_IRQHandler,Default_Handler

  .weak      FDCAN2_INT0_IRQHandler
  .thumb_set FDCAN2_INT0_IRQHandler,Default_Handler

  .weak      FDCAN3_INT0_IRQHandler
  .thumb_set FDCAN3_INT0_IRQHandler,Default_Handler

  .weak      FDCAN4_INT0_IRQHandler
  .thumb_set FDCAN4_INT0_IRQHandler,Default_Handler

  .weak      FDCAN1_INT1_IRQHandler
  .thumb_set FDCAN1_INT1_IRQHandler,Default_Handler

  .weak      FDCAN2_INT1_IRQHandler
  .thumb_set FDCAN2_INT1_IRQHandler,Default_Handler

  .weak      FDCAN3_INT1_IRQHandler
  .thumb_set FDCAN3_INT1_IRQHandler,Default_Handler

  .weak      FDCAN4_INT1_IRQHandler
  .thumb_set FDCAN4_INT1_IRQHandler,Default_Handler

  .weak      USART1_IRQHandler
  .thumb_set USART1_IRQHandler,Default_Handler

  .weak      USART2_IRQHandler
  .thumb_set USART2_IRQHandler,Default_Handler

  .weak      USART3_IRQHandler
  .thumb_set USART3_IRQHandler,Default_Handler

  .weak      USART4_IRQHandler
  .thumb_set USART4_IRQHandler,Default_Handler

  .weak      USART5_IRQHandler
  .thumb_set USART5_IRQHandler,Default_Handler

  .weak      USART6_IRQHandler
  .thumb_set USART6_IRQHandler,Default_Handler

  .weak      USART7_IRQHandler
  .thumb_set USART7_IRQHandler,Default_Handler

  .weak      USART8_IRQHandler
  .thumb_set USART8_IRQHandler,Default_Handler

  .weak      UART9_IRQHandler 
  .thumb_set UART9_IRQHandler,Default_Handler

  .weak      UART10_IRQHandler
  .thumb_set UART10_IRQHandler,Default_Handler

  .weak      UART11_IRQHandler
  .thumb_set UART11_IRQHandler,Default_Handler

  .weak      UART12_IRQHandler
  .thumb_set UART12_IRQHandler,Default_Handler

  .weak      UART13_IRQHandler
  .thumb_set UART13_IRQHandler,Default_Handler

  .weak      UART14_IRQHandler
  .thumb_set UART14_IRQHandler,Default_Handler

  .weak      UART15_IRQHandler
  .thumb_set UART15_IRQHandler,Default_Handler
  
  .weak      LPUART1_IRQHandler
  .thumb_set LPUART1_IRQHandler,Default_Handler

  .weak      LPUART2_IRQHandler
  .thumb_set LPUART2_IRQHandler,Default_Handler

  .weak      GPU_IRQHandler
  .thumb_set GPU_IRQHandler,Default_Handler

  .weak      SDMMC1_IRQHandler
  .thumb_set SDMMC1_IRQHandler,Default_Handler

  .weak      SDMMC2_IRQHandler
  .thumb_set SDMMC2_IRQHandler,Default_Handler

  .weak      ADC1_IRQHandler
  .thumb_set ADC1_IRQHandler,Default_Handler

  .weak      ADC2_IRQHandler
  .thumb_set ADC2_IRQHandler,Default_Handler

  .weak      ADC3_IRQHandler
  .thumb_set ADC3_IRQHandler,Default_Handler

  .weak      COMP1_2_IRQHandler
  .thumb_set COMP1_2_IRQHandler,Default_Handler

  .weak      COMP3_4_IRQHandler
  .thumb_set COMP3_4_IRQHandler,Default_Handler

  .weak      SHRTIM1_INT1_IRQHandler
  .thumb_set SHRTIM1_INT1_IRQHandler,Default_Handler

  .weak      SHRTIM1_INT2_IRQHandler
  .thumb_set SHRTIM1_INT2_IRQHandler,Default_Handler

  .weak      SHRTIM1_INT3_IRQHandler
  .thumb_set SHRTIM1_INT3_IRQHandler,Default_Handler

  .weak      SHRTIM1_INT4_IRQHandler
  .thumb_set SHRTIM1_INT4_IRQHandler,Default_Handler

  .weak      SHRTIM1_INT5_IRQHandler
  .thumb_set SHRTIM1_INT5_IRQHandler,Default_Handler

  .weak      SHRTIM1_INT6_IRQHandler
  .thumb_set SHRTIM1_INT6_IRQHandler,Default_Handler

  .weak      SHRTIM1_INT7_IRQHandler
  .thumb_set SHRTIM1_INT7_IRQHandler,Default_Handler

  .weak      SHRTIM1_INT8_IRQHandler
  .thumb_set SHRTIM1_INT8_IRQHandler,Default_Handler

  .weak      SHRTIM2_INT1_IRQHandler
  .thumb_set SHRTIM2_INT1_IRQHandler,Default_Handler

  .weak      SHRTIM2_INT2_IRQHandler
  .thumb_set SHRTIM2_INT2_IRQHandler,Default_Handler

  .weak      SHRTIM2_INT3_IRQHandler
  .thumb_set SHRTIM2_INT3_IRQHandler,Default_Handler

  .weak      SHRTIM2_INT4_IRQHandler
  .thumb_set SHRTIM2_INT4_IRQHandler,Default_Handler

  .weak      SHRTIM2_INT5_IRQHandler
  .thumb_set SHRTIM2_INT5_IRQHandler,Default_Handler

  .weak      SHRTIM2_INT6_IRQHandler
  .thumb_set SHRTIM2_INT6_IRQHandler,Default_Handler

  .weak      SHRTIM2_INT7_IRQHandler
  .thumb_set SHRTIM2_INT7_IRQHandler,Default_Handler

  .weak      SHRTIM2_INT8_IRQHandler
  .thumb_set SHRTIM2_INT8_IRQHandler,Default_Handler

  .weak      FDCAN5_INT0_IRQHandler
  .thumb_set FDCAN5_INT0_IRQHandler,Default_Handler

  .weak      FDCAN6_INT0_IRQHandler
  .thumb_set FDCAN6_INT0_IRQHandler,Default_Handler

  .weak      FDCAN7_INT0_IRQHandler
  .thumb_set FDCAN7_INT0_IRQHandler,Default_Handler

  .weak      FDCAN8_INT0_IRQHandler
  .thumb_set FDCAN8_INT0_IRQHandler,Default_Handler

  .weak      FDCAN5_INT1_IRQHandler
  .thumb_set FDCAN5_INT1_IRQHandler,Default_Handler

  .weak      FDCAN6_INT1_IRQHandler
  .thumb_set FDCAN6_INT1_IRQHandler,Default_Handler

  .weak      FDCAN7_INT1_IRQHandler
  .thumb_set FDCAN7_INT1_IRQHandler,Default_Handler

  .weak      FDCAN8_INT1_IRQHandler
  .thumb_set FDCAN8_INT1_IRQHandler,Default_Handler

  .weak      LPTIM5_WKUP_IRQHandler
  .thumb_set LPTIM5_WKUP_IRQHandler,Default_Handler

  .weak      JPEG_SGDMA_H2P_IRQHandler
  .thumb_set JPEG_SGDMA_H2P_IRQHandler,Default_Handler

  .weak      JPEG_SGDMA_P2H_IRQHandler
  .thumb_set JPEG_SGDMA_P2H_IRQHandler,Default_Handler

  .weak      WAKEUP_IO_IRQHandler
  .thumb_set WAKEUP_IO_IRQHandler,Default_Handler 

  .weak      SEMA4_INT1_IRQHandler
  .thumb_set SEMA4_INT1_IRQHandler,Default_Handler

  .weak      WWDG2_RST_IRQHandler
  .thumb_set WWDG2_RST_IRQHandler,Default_Handler

  .weak      OTPC_IRQHandler
  .thumb_set OTPC_IRQHandler,Default_Handler

  .weak      FEMC_IRQHandler
  .thumb_set FEMC_IRQHandler,Default_Handler

  .weak      DCMUB_IRQHandler
  .thumb_set DCMUB_IRQHandler,Default_Handler

  .weak      DAC1_IRQHandler
  .thumb_set DAC1_IRQHandler,Default_Handler

  .weak      DAC2_IRQHandler
  .thumb_set DAC2_IRQHandler,Default_Handler

  .weak      MDMA_AHBS_ER_IRQHandler
  .thumb_set MDMA_AHBS_ER_IRQHandler,Default_Handler

  .weak      CM7_CATCH_READ_ER_IRQHandler
  .thumb_set CM7_CATCH_READ_ER_IRQHandler,Default_Handler

  .weak      DAC3_IRQHandler
  .thumb_set DAC3_IRQHandler,Default_Handler

  .weak      DAC4_IRQHandler
  .thumb_set DAC4_IRQHandler,Default_Handler

  .weak      EMC_IRQHandler
  .thumb_set EMC_IRQHandler,Default_Handler

  .weak      DAC5_IRQHandler
  .thumb_set DAC5_IRQHandler,Default_Handler

  .weak      DAC6_IRQHandler
  .thumb_set DAC6_IRQHandler,Default_Handler
		  
  .weak      ATIM1_BRK_IRQHandler
  .thumb_set ATIM1_BRK_IRQHandler,Default_Handler

  .weak      ATIM1_TRG_COM_IRQHandler
  .thumb_set ATIM1_TRG_COM_IRQHandler,Default_Handler

  .weak      ATIM1_CC_IRQHandler
  .thumb_set ATIM1_CC_IRQHandler,Default_Handler

  .weak      ATIM1_UP_IRQHandler
  .thumb_set ATIM1_UP_IRQHandler,Default_Handler

  .weak      ATIM2_BRK_IRQHandler
  .thumb_set ATIM2_BRK_IRQHandler,Default_Handler

  .weak      ATIM2_TRG_COM_IRQHandler
  .thumb_set ATIM2_TRG_COM_IRQHandler,Default_Handler

  .weak      ATIM2_CC_IRQHandler
  .thumb_set ATIM2_CC_IRQHandler,Default_Handler

  .weak      ATIM2_UP_IRQHandler
  .thumb_set ATIM2_UP_IRQHandler,Default_Handler

  .weak      ATIM3_BRK_IRQHandler 
  .thumb_set ATIM3_BRK_IRQHandler,Default_Handler

  .weak      ATIM3_TRG_COM_IRQHandler
  .thumb_set ATIM3_TRG_COM_IRQHandler,Default_Handler

  .weak      ATIM3_CC_IRQHandler
  .thumb_set ATIM3_CC_IRQHandler,Default_Handler

  .weak      ATIM3_UP_IRQHandler 
  .thumb_set ATIM3_UP_IRQHandler,Default_Handler

  .weak      ATIM4_BRK_IRQHandler
  .thumb_set ATIM4_BRK_IRQHandler,Default_Handler

  .weak      ATIM4_TRG_COM_IRQHandler
  .thumb_set ATIM4_TRG_COM_IRQHandler,Default_Handler

  .weak      ATIM4_CC_IRQHandler
  .thumb_set ATIM4_CC_IRQHandler,Default_Handler

  .weak      ATIM4_UP_IRQHandler
  .thumb_set ATIM4_UP_IRQHandler,Default_Handler

  .weak      GTIMA1_IRQHandler
  .thumb_set GTIMA1_IRQHandler,Default_Handler

  .weak      GTIMA2_IRQHandler
  .thumb_set GTIMA2_IRQHandler,Default_Handler

  .weak      GTIMA3_IRQHandler
  .thumb_set GTIMA3_IRQHandler,Default_Handler

  .weak      GTIMA4_IRQHandler
  .thumb_set GTIMA4_IRQHandler,Default_Handler

  .weak      GTIMA5_IRQHandler
  .thumb_set GTIMA5_IRQHandler,Default_Handler

  .weak      GTIMA6_IRQHandler
  .thumb_set GTIMA6_IRQHandler,Default_Handler

  .weak      GTIMA7_IRQHandler
  .thumb_set GTIMA7_IRQHandler,Default_Handler

  .weak      GTIMB1_IRQHandler
  .thumb_set GTIMB1_IRQHandler,Default_Handler

  .weak      GTIMB2_IRQHandler
  .thumb_set GTIMB2_IRQHandler,Default_Handler

  .weak      GTIMB3_IRQHandler
  .thumb_set GTIMB3_IRQHandler,Default_Handler

  .weak      BTIM1_IRQHandler
  .thumb_set BTIM1_IRQHandler,Default_Handler

  .weak      BTIM2_IRQHandler
  .thumb_set BTIM2_IRQHandler,Default_Handler

  .weak      BTIM3_IRQHandler
  .thumb_set BTIM3_IRQHandler,Default_Handler

  .weak      BTIM4_IRQHandler
  .thumb_set BTIM4_IRQHandler,Default_Handler

  .weak      LPTIM1_WKUP_IRQHandler
  .thumb_set LPTIM1_WKUP_IRQHandler,Default_Handler

  .weak      LPTIM2_WKUP_IRQHandler
  .thumb_set LPTIM2_WKUP_IRQHandler,Default_Handler

  .weak      LPTIM3_WKUP_IRQHandler
  .thumb_set LPTIM3_WKUP_IRQHandler,Default_Handler

  .weak      LPTIM4_WKUP_IRQHandler
  .thumb_set LPTIM4_WKUP_IRQHandler,Default_Handler

  .weak      DSMU_FLT0_IRQHandler
  .thumb_set DSMU_FLT0_IRQHandler,Default_Handler

  .weak      DSMU_FLT1_IRQHandler
  .thumb_set DSMU_FLT1_IRQHandler,Default_Handler

  .weak      DSMU_FLT2_IRQHandler
  .thumb_set DSMU_FLT2_IRQHandler,Default_Handler

  .weak      DSMU_FLT3_IRQHandler
  .thumb_set DSMU_FLT3_IRQHandler,Default_Handler

  .weak      FMAC_IRQHandler
  .thumb_set FMAC_IRQHandler,Default_Handler

  .weak      CORDIC_IRQHandler
  .thumb_set CORDIC_IRQHandler,Default_Handler

  .weak      DMAMUX1_IRQHandler
  .thumb_set DMAMUX1_IRQHandler,Default_Handler

  .weak      MMU_IRQHandler
  .thumb_set MMU_IRQHandler,Default_Handler   

  .weak      SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler   


