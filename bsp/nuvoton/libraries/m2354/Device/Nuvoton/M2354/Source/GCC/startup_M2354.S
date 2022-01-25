/****************************************************************************//**
 * @file     startup_M2354.S
 * @version  V1.00
 * @brief    CMSIS Device Startup File
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2018-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/



    .syntax unified
    .arch   armv8 - m.base
    .fpu softvfp
    .thumb

    .global g_pfnVectors
    .global Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word   _sidata
/* start address for the .data section. defined in linker script */
.word   _sdata
/* end address for the .data section. defined in linker script */
.word   _edata
/* start address for the .bss section. defined in linker script */
.word   _sbss
/* end address for the .bss section. defined in linker script */
.word   _ebss

    .section .text.Reset_Handler
    .weak Reset_Handler
    .type Reset_Handler, %function

Reset_Handler:

    /* Check SecureWorld */
    MOV     R0, R15
    LSLS    R0, R0, #3
    BMI.N   GotoSystemInit

    /* Unlock Register */
    LDR     R0, =0x40000100
    LDR     R1, =0x59
    STR     R1, [R0]
    LDR     R1, =0x16
    STR     R1, [R0]
    LDR     R1, =0x88
    STR     R1, [R0]

    /* power gating */
    /* M32(0x400001f4) = 0xfffffffful; */
    LDR     R0, =0x400001f4
    LDR     R1, =0xffffffff
    STR     R1, [R0]

    /* M32(0x400000dC) = 0ul; */
    LDR     R0, =0x400000dC
    LDR     R1, =0x0
    STR     R1, [R0]

    /* Enable GPIO clks, SRAM clks, Trace clk */
    /* CLK->AHBCLK |= (0xffful << 20) | (1ul << 14); */

    LDR     R0, =0x40000200
    LDR     R1, [R0,#0x4]

    LDR     R2, =0xfff02000

    ORRS    R1, R1, R2
    STR     R1, [R0,#0x4]

GotoSystemInit:

    /* Lock register */
    LDR     R0, =0x40000100
    MOVS    R1, #0
    STR     R1, [R0]

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
    str r3, [r2, #4]
    adds r2, r2, #4

LoopFillZerobss:
    ldr r3, = _ebss
    cmp r2, r3
    bcc FillZerobss
    /* Call the clock system intitialization function.*/
    bl  SystemInit

/* Call the application's entry point.*/
    bl  entry
    bx  lr
.size Reset_Handler, .-Reset_Handler


    .pool
    .size   Reset_Handler, . - Reset_Handler

    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
    b Infinite_Loop
    .size Default_Handler, .-Default_Handler

    /*    Macro to define default handlers. Default handler
     *    will be weak symbol and just dead loops. They can be
     *    overwritten by other handlers */

    .macro  def_irq_handler handler_name
    .weak   \handler_name
    .set    \handler_name, Default_Handler
    .endm

    def_irq_handler NMI_Handler
    def_irq_handler HardFault_Handler
    def_irq_handler SVC_Handler
    def_irq_handler PendSV_Handler
    def_irq_handler SysTick_Handler

    def_irq_handler BOD_IRQHandler
    def_irq_handler IRC_IRQHandler
    def_irq_handler PWRWU_IRQHandler
    def_irq_handler SRAM_IRQHandler
    def_irq_handler CLKFAIL_IRQHandler

    def_irq_handler RTC_IRQHandler
    def_irq_handler RTC_TAMPER_IRQHandler
    def_irq_handler WDT_IRQHandler
    def_irq_handler WWDT_IRQHandler
    def_irq_handler EINT0_IRQHandler
    def_irq_handler EINT1_IRQHandler
    def_irq_handler EINT2_IRQHandler
    def_irq_handler EINT3_IRQHandler
    def_irq_handler EINT4_IRQHandler
    def_irq_handler EINT5_IRQHandler
    def_irq_handler GPA_IRQHandler
    def_irq_handler GPB_IRQHandler
    def_irq_handler GPC_IRQHandler
    def_irq_handler GPD_IRQHandler
    def_irq_handler GPE_IRQHandler
    def_irq_handler GPF_IRQHandler
    def_irq_handler QSPI0_IRQHandler
    def_irq_handler SPI0_IRQHandler
    def_irq_handler BRAKE0_IRQHandler
    def_irq_handler EPWM0_P0_IRQHandler
    def_irq_handler EPWM0_P1_IRQHandler
    def_irq_handler EPWM0_P2_IRQHandler
    def_irq_handler BRAKE1_IRQHandler
    def_irq_handler EPWM1_P0_IRQHandler
    def_irq_handler EPWM1_P1_IRQHandler
    def_irq_handler EPWM1_P2_IRQHandler
    def_irq_handler TMR0_IRQHandler
    def_irq_handler TMR1_IRQHandler
    def_irq_handler TMR2_IRQHandler
    def_irq_handler TMR3_IRQHandler
    def_irq_handler UART0_IRQHandler
    def_irq_handler UART1_IRQHandler
    def_irq_handler I2C0_IRQHandler
    def_irq_handler I2C1_IRQHandler
    def_irq_handler PDMA0_IRQHandler
    def_irq_handler DAC_IRQHandler
    def_irq_handler EADC0_IRQHandler
    def_irq_handler EADC1_IRQHandler
    def_irq_handler ACMP01_IRQHandler

    def_irq_handler EADC2_IRQHandler
    def_irq_handler EADC3_IRQHandler
    def_irq_handler UART2_IRQHandler
    def_irq_handler UART3_IRQHandler

    def_irq_handler SPI1_IRQHandler
    def_irq_handler SPI2_IRQHandler
    def_irq_handler USBD_IRQHandler
    def_irq_handler USBH_IRQHandler
    def_irq_handler USBOTG_IRQHandler
    def_irq_handler CAN0_IRQHandler

    def_irq_handler SC0_IRQHandler
    def_irq_handler SC1_IRQHandler
    def_irq_handler SC2_IRQHandler

    def_irq_handler SPI3_IRQHandler

    def_irq_handler SDH0_IRQHandler



    def_irq_handler I2S0_IRQHandler

    def_irq_handler OPA0_IRQHandler
    def_irq_handler CRPT_IRQHandler
    def_irq_handler GPG_IRQHandler
    def_irq_handler EINT6_IRQHandler
    def_irq_handler UART4_IRQHandler
    def_irq_handler UART5_IRQHandler
    def_irq_handler USCI0_IRQHandler
    def_irq_handler USCI1_IRQHandler
    def_irq_handler BPWM0_IRQHandler
    def_irq_handler BPWM1_IRQHandler


    def_irq_handler I2C2_IRQHandler

    def_irq_handler QEI0_IRQHandler
    def_irq_handler QEI1_IRQHandler
    def_irq_handler ECAP0_IRQHandler
    def_irq_handler ECAP1_IRQHandler
    def_irq_handler GPH_IRQHandler
    def_irq_handler EINT7_IRQHandler








    def_irq_handler PDMA1_IRQHandler
    def_irq_handler SCU_IRQHandler
    def_irq_handler LCD_IRQHandler
    def_irq_handler TRNG_IRQHandler







    def_irq_handler KS_IRQHandler
    def_irq_handler TAMPER_IRQHandler
    def_irq_handler EWDT_IRQHandler
    def_irq_handler EWWDT_IRQHandler
    def_irq_handler NS_ISP_IRQHandler   
    def_irq_handler TMR4_IRQHandler
    def_irq_handler TMR5_IRQHandler


    .align  2
    .thumb_func
    .global __PC
    .type   __PC, % function

__PC:
    MOV     r0, lr
    BLX     lr
    .size   __PC, . - __PC

/*******************************************************************************
*
* The minimal vector table for a Cortex M23. Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*******************************************************************************/

  .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, . - g_pfnVectors

g_pfnVectors:
    .long   _estack            /* Top of Stack */
    .long   Reset_Handler         /* Reset Handler */
    .long   NMI_Handler           /* NMI Handler */
    .long   HardFault_Handler     /* Hard Fault Handler */
    .long   0                     /* Reserved */
    .long   0                     /* Reserved */
    .long   0                     /* Reserved */
    .long   0                     /* Reserved */
    .long   0                     /* Reserved */
    .long   0                     /* Reserved */
    .long   0                     /* Reserved */
    .long   SVC_Handler           /* SVCall Handler */
    .long   0                     /* Reserved */
    .long   0                     /* Reserved */
    .long   PendSV_Handler        /* PendSV Handler */
    .long   SysTick_Handler       /* SysTick Handler */

    /* External interrupts */
    .long   BOD_IRQHandler        /* 0   */
    .long   IRC_IRQHandler        /* 1   */
    .long   PWRWU_IRQHandler      /* 2   */
    .long   SRAM_IRQHandler       /* 3   */
    .long   CLKFAIL_IRQHandler    /* 4   */
    .long   Default_Handler       /* 5   */
    .long   RTC_IRQHandler        /* 6   */
    .long   RTC_TAMPER_IRQHandler /* 7   */
    .long   WDT_IRQHandler        /* 8   */
    .long   WWDT_IRQHandler       /* 9   */
    .long   EINT0_IRQHandler      /* 10  */
    .long   EINT1_IRQHandler      /* 11  */
    .long   EINT2_IRQHandler      /* 12  */
    .long   EINT3_IRQHandler      /* 13  */
    .long   EINT4_IRQHandler      /* 14  */
    .long   EINT5_IRQHandler      /* 15  */
    .long   GPA_IRQHandler        /* 16  */
    .long   GPB_IRQHandler        /* 17  */
    .long   GPC_IRQHandler        /* 18  */
    .long   GPD_IRQHandler        /* 19  */
    .long   GPE_IRQHandler        /* 20  */
    .long   GPF_IRQHandler        /* 21  */
    .long   QSPI0_IRQHandler      /* 22  */
    .long   SPI0_IRQHandler       /* 23  */
    .long   BRAKE0_IRQHandler     /* 24  */
    .long   EPWM0_P0_IRQHandler   /* 25  */
    .long   EPWM0_P1_IRQHandler   /* 26  */
    .long   EPWM0_P2_IRQHandler   /* 27  */
    .long   BRAKE1_IRQHandler     /* 28  */
    .long   EPWM1_P0_IRQHandler   /* 29  */
    .long   EPWM1_P1_IRQHandler   /* 30  */
    .long   EPWM1_P2_IRQHandler   /* 31  */
    .long   TMR0_IRQHandler       /* 32  */
    .long   TMR1_IRQHandler       /* 33  */
    .long   TMR2_IRQHandler       /* 34  */
    .long   TMR3_IRQHandler       /* 35  */
    .long   UART0_IRQHandler      /* 36  */
    .long   UART1_IRQHandler      /* 37  */
    .long   I2C0_IRQHandler       /* 38  */
    .long   I2C1_IRQHandler       /* 39  */
    .long   PDMA0_IRQHandler      /* 40  */
    .long   DAC_IRQHandler        /* 41  */
    .long   EADC0_IRQHandler      /* 42  */
    .long   EADC1_IRQHandler      /* 43  */
    .long   ACMP01_IRQHandler     /* 44  */
    .long   Default_Handler       /* 45  */
    .long   EADC2_IRQHandler      /* 46  */
    .long   EADC3_IRQHandler      /* 47  */
    .long   UART2_IRQHandler      /* 48  */
    .long   UART3_IRQHandler      /* 49  */
    .long   Default_Handler       /* 50  */
    .long   SPI1_IRQHandler       /* 51  */
    .long   SPI2_IRQHandler       /* 52  */
    .long   USBD_IRQHandler       /* 53  */
    .long   USBH_IRQHandler       /* 54  */
    .long   USBOTG_IRQHandler     /* 55  */
    .long   CAN0_IRQHandler       /* 56  */
    .long   Default_Handler       /* 57  */
    .long   SC0_IRQHandler        /* 58  */
    .long   SC1_IRQHandler        /* 59  */
    .long   SC2_IRQHandler        /* 60  */
    .long   Default_Handler       /* 61  */
    .long   SPI3_IRQHandler       /* 62  */
    .long   Default_Handler       /* 63  */
    .long   SDH0_IRQHandler       /* 64  */
    .long   Default_Handler       /* 65  */
    .long   Default_Handler       /* 66  */
    .long   Default_Handler       /* 67  */
    .long   I2S0_IRQHandler       /* 68  */
    .long   Default_Handler       /* 69  */
    .long   OPA0_IRQHandler       /* 70  */
    .long   CRPT_IRQHandler       /* 71  */
    .long   GPG_IRQHandler        /* 72  */
    .long   EINT6_IRQHandler      /* 73  */
    .long   UART4_IRQHandler      /* 74  */
    .long   UART5_IRQHandler      /* 75  */
    .long   USCI0_IRQHandler      /* 76  */
    .long   USCI1_IRQHandler      /* 77  */
    .long   BPWM0_IRQHandler      /* 78  */
    .long   BPWM1_IRQHandler      /* 79  */
    .long   Default_Handler       /* 80  */
    .long   Default_Handler       /* 81  */
    .long   I2C2_IRQHandler       /* 82  */
    .long   Default_Handler       /* 83  */
    .long   QEI0_IRQHandler       /* 84  */
    .long   QEI1_IRQHandler       /* 85  */
    .long   ECAP0_IRQHandler      /* 86  */
    .long   ECAP1_IRQHandler      /* 87  */
    .long   GPH_IRQHandler        /* 88  */
    .long   EINT7_IRQHandler      /* 89  */
    .long   Default_Handler       /* 90  */
    .long   Default_Handler       /* 91  */
    .long   Default_Handler       /* 92  */
    .long   Default_Handler       /* 93  */
    .long   Default_Handler       /* 94  */
    .long   Default_Handler       /* 95  */
    .long   Default_Handler       /* 96  */
    .long   Default_Handler       /* 97  */
    .long   PDMA1_IRQHandler      /* 98  */
    .long   SCU_IRQHandler        /* 99  */
    .long   LCD_IRQHandler        /* 100 */
    .long   TRNG_IRQHandler       /* 101 */
    .long   Default_Handler       /* 102 */
    .long   Default_Handler       /* 103 */
    .long   Default_Handler       /* 104 */
    .long   Default_Handler       /* 105 */
    .long   Default_Handler       /* 106 */
    .long   Default_Handler       /* 107 */
    .long   Default_Handler       /* 108 */
    .long   KS_IRQHandler         /* 109 */ 
    .long   TAMPER_IRQHandler     /* 110 */ 
    .long   EWDT_IRQHandler       /* 111 */ 
    .long   EWWDT_IRQHandler      /* 112 */ 
    .long   NS_ISP_IRQHandler     /* 113 */ 
    .long   TMR4_IRQHandler       /* 114 */ 
    .long   TMR5_IRQHandler       /* 115 */

    .end
