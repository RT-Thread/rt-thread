/****************************************************************************//**
 * @file     startup_M480.S
 * @version  V1.00
 * @brief    CMSIS Cortex-M4 Core Device Startup File for M480
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
    .syntax unified
    .cpu cortex-m4
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

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

    .section    .text.Reset_Handler
    .weak   Reset_Handler
    .type   Reset_Handler, %function
Reset_Handler:

    // Unlock Register
    ldr r0, =0x40000100
    ldr r1, =0x59
    str r1, [r0]
    ldr r1, =0x16
    str r1, [r0]
    ldr r1, =0x88
    str r1, [r0]

#ifndef ENABLE_SPIM_CACHE
    ldr r0, =0x40000200            // R0 = Clock Controller Register Base Address
    ldr r1, [r0,#0x4]              // R1 = 0x40000204  (AHBCLK)
    orr r1, r1, #0x4000
    str r1, [r0,#0x4]              // CLK->AHBCLK |= CLK_AHBCLK_SPIMCKEN_Msk//

    ldr r0, =0x40007000            // R0 = SPIM Register Base Address
    ldr r1, [r0,#4]                // R1 = SPIM->CTL1
    orr r1, r1,#2                  // R1 |= SPIM_CTL1_CACHEOFF_Msk
    str r1, [r0,#4]                // _SPIM_DISABLE_CACHE()
    ldr r1, [r0,#4]                // R1 = SPIM->CTL1
    orr r1, r1, #4                 // R1 |= SPIM_CTL1_CCMEN_Msk
    str r1, [r0,#4]                // _SPIM_ENABLE_CCM()
#endif

#ifndef __NO_SYSTEM_INIT
	bl	SystemInit
#endif

    // Lock
    ldr     r0, =0x40000100
    ldr     r1, =0
    str     r1, [r0]

/* Copy the data segment initializers from flash to SRAM */
    movs  r1, #0
    b LoopCopyDataInit

CopyDataInit:
    ldr r3, =_sidata
    ldr r3, [r3, r1]
    str r3, [r0, r1]
    adds    r1, r1, #4

LoopCopyDataInit:
    ldr r0, =_sdata
    ldr r3, =_edata
    adds    r2, r0, r1
    cmp r2, r3
    bcc CopyDataInit
    ldr r2, =_sbss
    b   LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
    movs    r3, #0
    str r3, [r2], #4

LoopFillZerobss:
    ldr r3, = _ebss
    cmp r2, r3
    bcc FillZerobss

/* Call the application's entry point.*/
    bl  entry
    bx  lr
.size   Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 * @param  None
 * @retval None
*/
    .section    .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
    b   Infinite_Loop
    .size   Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M4.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
    .section    .isr_vector,"a",%progbits
    .type   g_pfnVectors, %object
    .size   g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
    .word     _estack                   // Top of Stack
    .word     Reset_Handler             // Reset Handler
    .word     NMI_Handler               // NMI Handler
    .word     HardFault_Handler         // Hard Fault Handler
    .word     MemManage_Handler         // MPU Fault Handler
    .word     BusFault_Handler          // Bus Fault Handler
    .word     UsageFault_Handler        // Usage Fault Handler
    .word     0                         // Reserved
    .word     0                         // DCDReserved
    .word     0                         // Reserved
    .word     0                         // Reserved
    .word     SVC_Handler               // SVCall Handler
    .word     DebugMon_Handler          // Debug Monitor Handler
    .word     0                         // Reserved
    .word     PendSV_Handler            // PendSV Handler
    .word     SysTick_Handler           // SysTick Handler

    // External Interrupts
	.word	BOD_IRQHandler        /*  0: BOD                        */
	.word	IRC_IRQHandler        /*  1: IRC                        */
	.word	PWRWU_IRQHandler      /*  2: PWRWU                      */
	.word	RAMPE_IRQHandler      /*  3: RAMPE                      */
	.word	CKFAIL_IRQHandler     /*  4: CKFAIL                     */
	.word	0                     /*  5: Reserved                   */
	.word	RTC_IRQHandler        /*  6: RTC                        */
	.word	TAMPER_IRQHandler     /*  7: TAMPER                     */
	.word	WDT_IRQHandler        /*  8: WDT                        */
	.word	WWDT_IRQHandler       /*  9: WWDT                       */
	.word	EINT0_IRQHandler      /* 10: EINT0                      */
	.word	EINT1_IRQHandler      /* 11: EINT1                      */
	.word	EINT2_IRQHandler      /* 12: EINT2                      */
	.word	EINT3_IRQHandler      /* 13: EINT3                      */
	.word	EINT4_IRQHandler      /* 14: EINT4                      */
	.word	EINT5_IRQHandler      /* 15: EINT5                      */
	.word	GPA_IRQHandler        /* 16: GPA                        */
	.word	GPB_IRQHandler        /* 17: GPB                        */
	.word	GPC_IRQHandler        /* 18: GPC                        */
	.word	GPD_IRQHandler        /* 19: GPD                        */
	.word	GPE_IRQHandler        /* 20: GPE                        */
	.word	GPF_IRQHandler        /* 21: GPF                        */
	.word	QSPI0_IRQHandler      /* 22: QSPI0                      */
	.word	SPI0_IRQHandler       /* 23: SPI0                       */
	.word	BRAKE0_IRQHandler     /* 24: BRAKE0                     */
	.word	EPWM0P0_IRQHandler    /* 25: EPWM0P0                    */
	.word	EPWM0P1_IRQHandler    /* 26: EPWM0P1                    */
	.word	EPWM0P2_IRQHandler    /* 27: EPWM0P2                    */
	.word	BRAKE1_IRQHandler     /* 28: BRAKE1                     */
	.word	EPWM1P0_IRQHandler    /* 29: EPWM1P0                    */
	.word	EPWM1P1_IRQHandler    /* 30: EPWM1P1                    */
	.word	EPWM1P2_IRQHandler    /* 31: EPWM1P2                    */
	.word	TMR0_IRQHandler       /* 32: TIMER0                     */
	.word	TMR1_IRQHandler       /* 33: TIMER1                     */
	.word	TMR2_IRQHandler       /* 34: TIMER2                     */
	.word	TMR3_IRQHandler       /* 35: TIMER3                     */
	.word	UART0_IRQHandler      /* 36: UART0                      */
	.word	UART1_IRQHandler      /* 37: UART1                      */
	.word	I2C0_IRQHandler       /* 38: I2C0                       */
	.word	I2C1_IRQHandler       /* 39: I2C1                       */
	.word	PDMA_IRQHandler       /* 40: PDMA                       */
	.word	DAC_IRQHandler        /* 41: DAC                        */
	.word	EADC00_IRQHandler     /* 42: EADC00                     */
	.word	EADC01_IRQHandler     /* 43: EADC01                     */
	.word	ACMP01_IRQHandler     /* 44: ACMP                       */
	.word	0                     /* 45: Reserved                   */
	.word	EADC02_IRQHandler     /* 46: EADC02                     */
	.word	EADC03_IRQHandler     /* 47: EADC03                     */
	.word	UART2_IRQHandler      /* 48: UART2                      */
	.word	UART3_IRQHandler      /* 49: UART3                      */
	.word	QSPI1_IRQHandler      /* 50: QSPI1                      */
	.word	SPI1_IRQHandler       /* 51: SPI1                       */
	.word	SPI2_IRQHandler       /* 52: SPI2                       */
	.word	USBD_IRQHandler       /* 53: USBD                       */
	.word	OHCI_IRQHandler       /* 54: OHCI                       */
	.word	USBOTG_IRQHandler     /* 55: OTG                        */
	.word	CAN0_IRQHandler       /* 56: CAN0                       */
	.word	CAN1_IRQHandler       /* 57: CAN1                       */
	.word	SC0_IRQHandler        /* 58: SC0                        */
	.word	SC1_IRQHandler        /* 59: SC1                        */
	.word	SC2_IRQHandler        /* 60: SC2                        */
	.word	0                     /* 61: Reserved                   */
	.word	SPI3_IRQHandler       /* 62: SPI3                       */
	.word	0                     /* 63: Reserved                   */
	.word	SDH0_IRQHandler       /* 64: SDH0                       */
	.word	USBD20_IRQHandler     /* 65: HSUSBD                     */
	.word	EMAC_TX_IRQHandler    /* 66: EMAC_TX                    */
	.word	EMAC_RX_IRQHandler    /* 67: EMAC_RX                    */
	.word	I2S0_IRQHandler       /* 68: I2S                        */
	.word	0                     /* 69: Reserved                   */
	.word	OPA0_IRQHandler       /* 70: OPA                        */
	.word	CRYPTO_IRQHandler     /* 71: CRYPTO                     */
	.word	GPG_IRQHandler        /* 72: GPG                        */
	.word	EINT6_IRQHandler      /* 73: EINT6                      */
	.word	UART4_IRQHandler      /* 74: UART4                      */
	.word	UART5_IRQHandler      /* 75: UART5                      */
	.word	USCI0_IRQHandler      /* 76: USCI0                      */
	.word	USCI1_IRQHandler      /* 77: USCI1                      */
	.word	BPWM0_IRQHandler      /* 78: BPWM0                      */
	.word	BPWM1_IRQHandler      /* 79: BPWM1                      */
	.word	SPIM_IRQHandler       /* 80: SPIM                       */
	.word	CCAP_IRQHandler       /* 81: CCAP                       */
	.word	I2C2_IRQHandler       /* 82: I2C2                       */
	.word	0                     /* 83: Reserved                   */
	.word	QEI0_IRQHandler       /* 84: QEI0                       */
	.word	QEI1_IRQHandler       /* 85: QEI1                       */
	.word	ECAP0_IRQHandler      /* 86: ECAP0                      */
	.word	ECAP1_IRQHandler      /* 87: ECAP1                      */
	.word	GPH_IRQHandler        /* 88: GPH                        */
	.word	EINT7_IRQHandler      /* 89: EINT7                      */
	.word	SDH1_IRQHandler       /* 90: SDH1                       */
	.word	0                     /* 91: Reserved                   */
	.word	EHCI_IRQHandler       /* 92:  EHCI                      */
	.word	USBOTG20_IRQHandler   /* 93:  HSOTG                     */
	.word	0                     /* 94: Reserved                   */
	.word	0                     /* 95: Reserved                   */
	.word	0                     /* 96: Reserved                   */
	.word	0                     /* 97: Reserved                   */
	.word	0                     /* 98: Reserved                   */
	.word	0                     /* 99: Reserved                   */
	.word	0                     /* 100: Reserved                  */
	.word	TRNG_IRQHandler       /* 101: TRNG                      */
	.word	UART6_IRQHandler      /* 102: UART6                     */
	.word	UART7_IRQHandler      /* 103: UART7                     */
	.word	EADC10_IRQHandler     /* 104: EADC10                    */
	.word	EADC11_IRQHandler     /* 105: EADC11                    */
	.word	EADC12_IRQHandler     /* 106: EADC12                    */
	.word	EADC13_IRQHandler     /* 107: EADC13                    */
	.word	CAN2_IRQHandler       /* 108: CAN2                      */


/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro  def_irq_handler handler_name
    .weak   \handler_name
    .set    \handler_name, Default_Handler
    .endm

	def_irq_handler	NMI_Handler
	def_irq_handler	HardFault_Handler
	def_irq_handler	MemManage_Handler
	def_irq_handler	BusFault_Handler
	def_irq_handler	UsageFault_Handler
	def_irq_handler	SVC_Handler
	def_irq_handler	DebugMon_Handler
	def_irq_handler	PendSV_Handler
	def_irq_handler	SysTick_Handler

	def_irq_handler	BOD_IRQHandler
	def_irq_handler	IRC_IRQHandler
	def_irq_handler	PWRWU_IRQHandler
	def_irq_handler	RAMPE_IRQHandler
	def_irq_handler	CKFAIL_IRQHandler
	def_irq_handler	RTC_IRQHandler
	def_irq_handler	TAMPER_IRQHandler
	def_irq_handler	WDT_IRQHandler
	def_irq_handler	WWDT_IRQHandler
	def_irq_handler	EINT0_IRQHandler
	def_irq_handler	EINT1_IRQHandler
	def_irq_handler	EINT2_IRQHandler
	def_irq_handler	EINT3_IRQHandler
	def_irq_handler	EINT4_IRQHandler
	def_irq_handler	EINT5_IRQHandler
	def_irq_handler	GPA_IRQHandler
	def_irq_handler	GPB_IRQHandler
	def_irq_handler	GPC_IRQHandler
	def_irq_handler	GPD_IRQHandler
	def_irq_handler	GPE_IRQHandler
	def_irq_handler	GPF_IRQHandler
	def_irq_handler	QSPI0_IRQHandler
	def_irq_handler	SPI0_IRQHandler
	def_irq_handler	BRAKE0_IRQHandler
	def_irq_handler	EPWM0P0_IRQHandler
	def_irq_handler	EPWM0P1_IRQHandler
	def_irq_handler	EPWM0P2_IRQHandler
	def_irq_handler	BRAKE1_IRQHandler
	def_irq_handler	EPWM1P0_IRQHandler
	def_irq_handler	EPWM1P1_IRQHandler
	def_irq_handler	EPWM1P2_IRQHandler
	def_irq_handler	TMR0_IRQHandler
	def_irq_handler	TMR1_IRQHandler
	def_irq_handler	TMR2_IRQHandler
	def_irq_handler	TMR3_IRQHandler
	def_irq_handler	UART0_IRQHandler
	def_irq_handler	UART1_IRQHandler
	def_irq_handler	I2C0_IRQHandler
	def_irq_handler	I2C1_IRQHandler
	def_irq_handler	PDMA_IRQHandler
	def_irq_handler	DAC_IRQHandler
	def_irq_handler	EADC00_IRQHandler
	def_irq_handler	EADC01_IRQHandler
	def_irq_handler	ACMP01_IRQHandler
	def_irq_handler	EADC02_IRQHandler
	def_irq_handler	EADC03_IRQHandler
	def_irq_handler	UART2_IRQHandler
	def_irq_handler	UART3_IRQHandler
	def_irq_handler	QSPI1_IRQHandler
	def_irq_handler	SPI1_IRQHandler
	def_irq_handler	SPI2_IRQHandler
	def_irq_handler	USBD_IRQHandler
	def_irq_handler	OHCI_IRQHandler
	def_irq_handler	USBOTG_IRQHandler
	def_irq_handler	CAN0_IRQHandler
	def_irq_handler	CAN1_IRQHandler
	def_irq_handler	SC0_IRQHandler
	def_irq_handler	SC1_IRQHandler
	def_irq_handler	SC2_IRQHandler
	def_irq_handler	SPI3_IRQHandler
	def_irq_handler	SDH0_IRQHandler
	def_irq_handler	USBD20_IRQHandler
	def_irq_handler	EMAC_TX_IRQHandler
	def_irq_handler	EMAC_RX_IRQHandler
	def_irq_handler	I2S0_IRQHandler
	def_irq_handler	OPA0_IRQHandler
	def_irq_handler	CRYPTO_IRQHandler
	def_irq_handler	GPG_IRQHandler
	def_irq_handler	EINT6_IRQHandler
	def_irq_handler	UART4_IRQHandler
	def_irq_handler	UART5_IRQHandler
	def_irq_handler	USCI0_IRQHandler
	def_irq_handler	USCI1_IRQHandler
	def_irq_handler	BPWM0_IRQHandler
	def_irq_handler	BPWM1_IRQHandler
	def_irq_handler	SPIM_IRQHandler
	def_irq_handler CCAP_IRQHandler
	def_irq_handler	I2C2_IRQHandler
	def_irq_handler	QEI0_IRQHandler
	def_irq_handler	QEI1_IRQHandler
	def_irq_handler	ECAP0_IRQHandler
	def_irq_handler	ECAP1_IRQHandler
	def_irq_handler	GPH_IRQHandler
	def_irq_handler	EINT7_IRQHandler
	def_irq_handler	SDH1_IRQHandler
	def_irq_handler	EHCI_IRQHandler
	def_irq_handler	USBOTG20_IRQHandler
	def_irq_handler	TRNG_IRQHandler
	def_irq_handler	UART6_IRQHandler
	def_irq_handler	UART7_IRQHandler
	def_irq_handler	EADC10_IRQHandler
	def_irq_handler	EADC11_IRQHandler
	def_irq_handler	EADC12_IRQHandler
	def_irq_handler	EADC13_IRQHandler
	def_irq_handler	CAN2_IRQHandler
