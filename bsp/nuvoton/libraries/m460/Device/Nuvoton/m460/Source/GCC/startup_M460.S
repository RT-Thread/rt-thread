
/****************************************************************************//**
 * @file     startup_M460.S
 * @version  V3.00
 * @brief    CMSIS Cortex-M4 Core Device Startup File for M460
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
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
	.long	_estack               /* Top of Stack */
	.long	Reset_Handler         /* Reset Handler */
	.long	NMI_Handler           /* NMI Handler */
	.long	HardFault_Handler     /* Hard Fault Handler */
	.long	MemManage_Handler     /* MPU Fault Handler */
	.long	BusFault_Handler      /* Bus Fault Handler */
	.long	UsageFault_Handler    /* Usage Fault Handler */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	SVC_Handler           /* SVCall Handler */
	.long	DebugMon_Handler      /* Debug Monitor Handler */
	.long	0                     /* Reserved */
	.long	PendSV_Handler        /* PendSV Handler */
	.long	SysTick_Handler       /* SysTick Handler */

	/* External interrupts */
	.long	BOD_IRQHandler        /*  0: BOD                        */
	.long	IRC_IRQHandler        /*  1: IRC                        */
	.long	PWRWU_IRQHandler      /*  2: PWRWU                      */
	.long	RAMPE_IRQHandler      /*  3: RAMPE                      */
	.long	CKFAIL_IRQHandler     /*  4: CKFAIL                     */
	.long	ISP_IRQHandler        /*  5: ISP                   */
	.long	RTC_IRQHandler        /*  6: RTC                        */
	.long	TAMPER_IRQHandler     /*  7: TAMPER                     */
	.long	WDT_IRQHandler        /*  8: WDT                        */
	.long	WWDT_IRQHandler       /*  9: WWDT                       */
	.long	EINT0_IRQHandler      /* 10: EINT0                      */
	.long	EINT1_IRQHandler      /* 11: EINT1                      */
	.long	EINT2_IRQHandler      /* 12: EINT2                      */
	.long	EINT3_IRQHandler      /* 13: EINT3                      */
	.long	EINT4_IRQHandler      /* 14: EINT4                      */
	.long	EINT5_IRQHandler      /* 15: EINT5                      */
	.long	GPA_IRQHandler        /* 16: GPA                        */
	.long	GPB_IRQHandler        /* 17: GPB                        */
	.long	GPC_IRQHandler        /* 18: GPC                        */
	.long	GPD_IRQHandler        /* 19: GPD                        */
	.long	GPE_IRQHandler        /* 20: GPE                        */
	.long	GPF_IRQHandler        /* 21: GPF                        */
	.long	QSPI0_IRQHandler      /* 22: QSPI0                      */
	.long	SPI0_IRQHandler       /* 23: SPI0                       */
	.long	BRAKE0_IRQHandler     /* 24: BRAKE0                     */
	.long	EPWM0P0_IRQHandler    /* 25: EPWM0P0                    */
	.long	EPWM0P1_IRQHandler    /* 26: EPWM0P1                    */
	.long	EPWM0P2_IRQHandler    /* 27: EPWM0P2                    */
	.long	BRAKE1_IRQHandler     /* 28: BRAKE1                     */
	.long	EPWM1P0_IRQHandler    /* 29: EPWM1P0                    */
	.long	EPWM1P1_IRQHandler    /* 30: EPWM1P1                    */
	.long	EPWM1P2_IRQHandler    /* 31: EPWM1P2                    */
	.long	TMR0_IRQHandler       /* 32: TIMER0                     */
	.long	TMR1_IRQHandler       /* 33: TIMER1                     */
	.long	TMR2_IRQHandler       /* 34: TIMER2                     */
	.long	TMR3_IRQHandler       /* 35: TIMER3                     */
	.long	UART0_IRQHandler      /* 36: UART0                      */
	.long	UART1_IRQHandler      /* 37: UART1                      */
	.long	I2C0_IRQHandler       /* 38: I2C0                       */
	.long	I2C1_IRQHandler       /* 39: I2C1                       */
	.long	PDMA0_IRQHandler      /* 40: PDMA0                      */
	.long	DAC_IRQHandler        /* 41: DAC                        */
	.long	EADC00_IRQHandler     /* 42: EADC00                     */
	.long	EADC01_IRQHandler     /* 43: EADC01                     */
	.long	ACMP01_IRQHandler     /* 44: ACMP01                     */
	.long	ACMP23_IRQHandler     /* 45: ACMP23                     */
	.long	EADC02_IRQHandler     /* 46: EADC02                     */
	.long	EADC03_IRQHandler     /* 47: EADC03                     */
	.long	UART2_IRQHandler      /* 48: UART2                      */
	.long	UART3_IRQHandler      /* 49: UART3                      */
	.long	QSPI1_IRQHandler      /* 50: QSPI1                      */
	.long	SPI1_IRQHandler       /* 51: SPI1                       */
	.long	SPI2_IRQHandler       /* 52: SPI2                       */
	.long	USBD_IRQHandler       /* 53: USBD                       */
	.long	OHCI_IRQHandler       /* 54: OHCI                       */
	.long	USBOTG_IRQHandler     /* 55: OTG                        */
	.long	BMC_Handler           /* 56: BMC                        */
	.long	SPI5_IRQHandler       /* 57: SPI5                       */
	.long	SC0_IRQHandler        /* 58: SC0                        */
	.long	SC1_IRQHandler        /* 59: SC1                        */
	.long	SC2_IRQHandler        /* 60: SC2                        */
	.long	GPJ_IRQHandler        /* 61: GPJ                        */
	.long	SPI3_IRQHandler       /* 62: SPI3                       */
	.long	SPI4_IRQHandler       /* 63: SPI4                       */
	.long	SDH0_IRQHandler       /* 64: SDH0                       */
	.long	USBD20_IRQHandler     /* 65: HSUSBD                     */
	.long	EMAC0_IRQHandler      /* 66: EMAC0                      */
	.long	0                     /* 67: Reserved                   */
	.long	I2S0_IRQHandler       /* 68: I2S0                       */
	.long	I2S1_IRQHandler       /* 69: I2S1                       */
	.long	SPI6_IRQHandler       /* 70: SPI6                       */
	.long	CRPT_IRQHandler       /* 71: CRPT                       */
	.long	GPG_IRQHandler        /* 72: GPG                        */
	.long	EINT6_IRQHandler      /* 73: EINT6                      */
	.long	UART4_IRQHandler      /* 74: UART4                      */
	.long	UART5_IRQHandler      /* 75: UART5                      */
	.long	USCI0_IRQHandler      /* 76: USCI0                      */
	.long	SPI7_IRQHandler       /* 77: SPI7                       */
	.long	BPWM0_IRQHandler      /* 78: BPWM0                      */
	.long	BPWM1_IRQHandler      /* 79: BPWM1                      */
	.long	SPIM_IRQHandler       /* 80: SPIM                       */
	.long	CCAP_IRQHandler       /* 81: CCAP                       */
	.long	I2C2_IRQHandler       /* 82: I2C2                       */
	.long	I2C3_IRQHandler       /* 83: I2C3                       */
	.long	EQEI0_IRQHandler      /* 84: EQEI0                      */
	.long	EQEI1_IRQHandler      /* 85: EQEI1                      */
	.long	ECAP0_IRQHandler      /* 86: ECAP0                      */
	.long	ECAP1_IRQHandler      /* 87: ECAP1                      */
	.long	GPH_IRQHandler        /* 88: GPH                        */
	.long	EINT7_IRQHandler      /* 89: EINT7                      */
	.long	SDH1_IRQHandler       /* 90: SDH1                       */
	.long	PSIO_IRQHandler       /* 91: PSIO                       */
	.long	EHCI_IRQHandler       /* 92: EHCI                       */
	.long	USBOTG20_IRQHandler   /* 93: HSOTG                      */
	.long	ECAP2_IRQHandler      /* 94: ECAP2                      */
	.long	ECAP3_IRQHandler      /* 95: ECAP3                      */
	.long	KPI_IRQHandler        /* 96: KPI                        */
	.long	HBI_IRQHandler        /* 97: HBI                        */
	.long	PDMA1_IRQHandler      /* 98: PDMA1                      */
	.long	UART8_IRQHandler      /* 99: UART8                      */
	.long	UART9_IRQHandler      /* 100: UART9                     */
	.long	TRNG_IRQHandler       /* 101: TRNG                      */
	.long	UART6_IRQHandler      /* 102: UART6                     */
	.long	UART7_IRQHandler      /* 103: UART7                     */
	.long	EADC10_IRQHandler     /* 104: EADC10                    */
	.long	EADC11_IRQHandler     /* 105: EADC11                    */
	.long	EADC12_IRQHandler     /* 106: EADC12                    */
	.long	EADC13_IRQHandler     /* 107: EADC13                    */
	.long	SPI8_IRQHandler       /* 108: SPI8                      */
	.long	KS_IRQHandler         /* 109: KS                        */
	.long	GPI_IRQHandler        /* 110: GPI                       */
	.long	SPI9_IRQHandler       /* 111: SPI9                      */
	.long	CANFD00_IRQHandler    /* 112: CANFD00                   */
	.long	CANFD01_IRQHandler    /* 113: CANFD01                   */
	.long	CANFD10_IRQHandler    /* 114: CANFD10                   */
	.long	CANFD10_IRQHandler    /* 115: CANFD10                   */
	.long	EQEI2_IRQHandler      /* 116: EQEI2                     */
	.long	EQEI3_IRQHandler      /* 117: EQEI3                     */
	.long	I2C4_IRQHandler       /* 118: I2C4                      */
	.long	SPI10_IRQHandler      /* 119: SPI10                     */
	.long	CANFD20_IRQHandler    /* 120: CANFD20                   */
	.long	CANFD21_IRQHandler    /* 121: CANFD21                   */
	.long	CANFD30_IRQHandler    /* 122: CANFD30                   */
	.long	CANFD30_IRQHandler    /* 123: CANFD30                   */
	.long	EADC20_IRQHandler     /* 124: EADC20                    */
	.long	EADC21_IRQHandler     /* 125: EADC21                    */
	.long	EADC22_IRQHandler     /* 126: EADC22                    */
	.long	EADC23_IRQHandler     /* 127: EADC23                    */

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
	.macro	def_irq_handler	handler_name
	.weak	\handler_name
	.set	\handler_name, Default_Handler
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
	def_irq_handler	ISP_IRQHandler
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
	def_irq_handler	PDMA0_IRQHandler
	def_irq_handler	DAC_IRQHandler
	def_irq_handler	EADC00_IRQHandler
	def_irq_handler	EADC01_IRQHandler
	def_irq_handler	ACMP01_IRQHandler
	def_irq_handler	ACMP23_IRQHandler
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
	def_irq_handler	BMC_Handler
	def_irq_handler	SPI5_IRQHandler
	def_irq_handler	SC0_IRQHandler
	def_irq_handler	SC1_IRQHandler
	def_irq_handler	SC2_IRQHandler
	def_irq_handler	GPJ_IRQHandler
	def_irq_handler	SPI3_IRQHandler
	def_irq_handler	SPI4_IRQHandler
	def_irq_handler	SDH0_IRQHandler
	def_irq_handler	USBD20_IRQHandler
	def_irq_handler	EMAC0_IRQHandler
	def_irq_handler	I2S0_IRQHandler
	def_irq_handler	I2S1_IRQHandler
	def_irq_handler	SPI6_IRQHandler
	def_irq_handler	CRPT_IRQHandler
	def_irq_handler	GPG_IRQHandler
	def_irq_handler	EINT6_IRQHandler
	def_irq_handler	UART4_IRQHandler
	def_irq_handler	UART5_IRQHandler
	def_irq_handler	USCI0_IRQHandler
	def_irq_handler	SPI7_IRQHandler
	def_irq_handler	BPWM0_IRQHandler
	def_irq_handler	BPWM1_IRQHandler
	def_irq_handler	SPIM_IRQHandler
	def_irq_handler CCAP_IRQHandler
	def_irq_handler	I2C2_IRQHandler
	def_irq_handler	I2C3_IRQHandler
	def_irq_handler	EQEI0_IRQHandler
	def_irq_handler	EQEI1_IRQHandler
	def_irq_handler	ECAP0_IRQHandler
	def_irq_handler	ECAP1_IRQHandler
	def_irq_handler	GPH_IRQHandler
	def_irq_handler	EINT7_IRQHandler
	def_irq_handler	SDH1_IRQHandler
	def_irq_handler	PSIO_IRQHandler
	def_irq_handler	EHCI_IRQHandler
	def_irq_handler	USBOTG20_IRQHandler
	def_irq_handler	ECAP2_IRQHandler
	def_irq_handler	ECAP3_IRQHandler
	def_irq_handler	KPI_IRQHandler
	def_irq_handler HBI_IRQHandler
	def_irq_handler PDMA1_IRQHandler
	def_irq_handler	UART8_IRQHandler
	def_irq_handler	UART9_IRQHandler
	def_irq_handler	TRNG_IRQHandler
	def_irq_handler	UART6_IRQHandler
	def_irq_handler	UART7_IRQHandler
	def_irq_handler	EADC10_IRQHandler
	def_irq_handler	EADC11_IRQHandler
	def_irq_handler	EADC12_IRQHandler
	def_irq_handler	EADC13_IRQHandler
	def_irq_handler	SPI8_IRQHandler
	def_irq_handler	KS_IRQHandler
	def_irq_handler	GPI_IRQHandler
	def_irq_handler	SPI9_IRQHandler
	def_irq_handler	CANFD00_IRQHandler
	def_irq_handler	CANFD01_IRQHandler
	def_irq_handler	CANFD10_IRQHandler
	def_irq_handler	CANFD11_IRQHandler
	def_irq_handler EQEI2_IRQHandler
	def_irq_handler EQEI3_IRQHandler
	def_irq_handler I2C4_IRQHandler
	def_irq_handler	SPI10_IRQHandler
	def_irq_handler	CANFD20_IRQHandler
	def_irq_handler	CANFD21_IRQHandler
	def_irq_handler	CANFD30_IRQHandler
	def_irq_handler	CANFD31_IRQHandler
	def_irq_handler	EADC20_IRQHandler
	def_irq_handler	EADC21_IRQHandler
	def_irq_handler	EADC22_IRQHandler
	def_irq_handler	EADC23_IRQHandler

	.end
