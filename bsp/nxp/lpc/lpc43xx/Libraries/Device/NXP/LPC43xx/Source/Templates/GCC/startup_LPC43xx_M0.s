/*****************************************************************************/
/* startup_LPC43xx.s: Startup file for LPC43xx device series                 */
/*****************************************************************************/
/* Version: CodeSourcery Sourcery G++ Lite (with CS3)                        */
/*****************************************************************************/

	.syntax unified
	.cpu cortex-m0
	.arch armv6-m
	.thumb

	.word  _sidata
	.word  _sdata
	.word  _edata
	.word  _sbss
	.word  _ebss


    .equ    Sign_Value, 0x5A5A5A5A

/* Vector Table */

    .section ".interrupt_vector"
    .globl  __interrupt_vector
    .type   __interrupt_vector, %function

__interrupt_vector:
    .long   _estack                 /* Top of Stack                 */
    .long   Reset_Handler               /* Reset Handler                */
    .long   NMI_Handler                 /* NMI Handler                  */
    .long   HardFault_Handler           /* Hard Fault Handler           */
    .long   MemManage_Handler           /* MPU Fault Handler            */
    .long   BusFault_Handler            /* Bus Fault Handler            */
    .long   UsageFault_Handler          /* Usage Fault Handler          */
    .long   Sign_Value                  /* Reserved                     */
    .long   0                           /* Reserved                     */
    .long   0                           /* Reserved                     */
    .long   0                           /* Reserved                     */
    .long   SVC_Handler                 /* SVCall Handler               */
    .long   DebugMon_Handler            /* Debug Monitor Handler        */
    .long   0                           /* Reserved                     */
    .long   PendSV_Handler              /* PendSV Handler               */
    .long   SysTick_Handler             /* SysTick Handler              */

/* External Interrupts */
    .long   RTC_IRQHandler                 /* 16 D/A Converter             */
    .long   M4CORE_IRQHandler              /* 17 M0 Core                   */
    .long   DMA_IRQHandler                 /* 18 General Purpose DMA       */
    .long   0                              /* 19 EZH/EDM                   */
    .long   FLASHEEPROMAT_IRQHandler       /* 20 Reserved for Typhoon      */
    .long   ETH_IRQHandler                 /* 21 Ethernet                  */
    .long   SDIO_IRQHandler                /* 22 SD/MMC                    */
    .long   LCD_IRQHandler                 /* 23 LCD                       */
    .long   USB0_IRQHandler                /* 24 USB0                      */
    .long   USB1_IRQHandler                /* 25 USB1                      */
    .long   SCT_IRQHandler                 /* 26 State Configurable Timer  */
    .long   RIT_OR_WWDT_IRQHandler         /* 27 Repetitive Interrupt Timer*/
    .long   TIMER0_IRQHandler              /* 28 Timer0                    */
    .long   GINT1_IRQHandler               /* 29 Timer1                    */
    .long   PIN_INT4_IRQHandler            /* 30 Timer2                    */
    .long   TIMER3_IRQHandler              /* 31 Timer3                    */
    .long   MCPWM_IRQHandler               /* 32 Motor Control PWM         */
    .long   ADC0_IRQHandler                /* 33 A/D Converter 0           */
    .long   I2C0_OR_I2C1_IRQHandler        /* 34 I2C0                      */
    .long   SGPIO_IRQHandler               /* 35 I2C1                      */
    .long   SPI_OR_DAC_IRQHandler          /* 36 SPI                       */
    .long   ADC1_IRQHandler                /* 37 A/D Converter 1           */
    .long   SSP0_OR_SSP1_IRQHandler        /* 38 SSP0                      */
    .long   EVENTROUTER_IRQHandler         /* 39 SSP1                      */
    .long   UART0_IRQHandler               /* 40 UART0                     */
    .long   UART1_IRQHandler               /* 41 UART1                     */
    .long   UART2_OR_C_CAN1_IRQHandler     /* 42 UART2                     */
    .long   UART3_IRQHandler               /* 43 UART3                     */
    .long   I2S0_OR_I2S1_OR_QEI_IRQHandler /* 44 I2S0                      */
    .long   C_CAN0_IRQHandler              /* 45 I2S1                      */
    .long   0                              /* 46 SPI Flash Interface       */
    .long   0                              /* 47 SGPIO                     */

    .size   __interrupt_vector, . - __interrupt_vector


    .thumb


/* Reset Handler */
    .section  .text.Reset_Handler
	.weak  Reset_Handler
	.type  Reset_Handler, %function
Reset_Handler:
    .fnstart
/*  Single section scheme.
 *
 *  The ranges of copy from/to are specified by following symbols
 *    _sidata: LMA of start of the section to copy from. Usually end of text
 *    _sdata: VMA of start of the section to copy to
 *    _edata: VMA of end of the section to copy to
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
	ldr	r1, =_sidata
	ldr	r2, =_sdata
	ldr	r3, =_edata

	subs	r3, r2
	ble	.L_loop1_done

.L_loop1:
	subs	r3, #4
	ldr	r0, [r1,r3]
	str	r0, [r2,r3]
	bgt	.L_loop1

.L_loop1_done:

/*  Single BSS section scheme.
 *
 *  The BSS section is specified by following symbols
 *    __bss_start: start of the BSS section.
 *    __bss_end: end of the BSS section.
 *
 *  Both addresses must be aligned to 4 bytes boundary.
 */
	ldr	r1, =__bss_start
	ldr	r2, =__bss_end

	movs	r0, 0

	subs	r2, r1
	ble	.L_loop3_done

.L_loop3:
	subs	r2, #4
	str	r0, [r1, r2]
	bgt	.L_loop3
.L_loop3_done:

    ldr     R0, =SystemInit
    blx     R0
    ldr     R0,=main
    bx      R0

    .pool
    .cantunwind
    .fnend
    .size   Reset_Handler,.-Reset_Handler

    .section ".text"

/* Exception Handlers */

    .weak   NMI_Handler
    .type   NMI_Handler, %function
NMI_Handler:
    B       .
    .size   NMI_Handler, . - NMI_Handler

    .weak   HardFault_Handler
    .type   HardFault_Handler, %function
HardFault_Handler:
    B       .
    .size   HardFault_Handler, . - HardFault_Handler

    .weak   MemManage_Handler
    .type   MemManage_Handler, %function
MemManage_Handler:
    B       .
    .size   MemManage_Handler, . - MemManage_Handler

    .weak   BusFault_Handler
    .type   BusFault_Handler, %function
BusFault_Handler:
    B       .
    .size   BusFault_Handler, . - BusFault_Handler

    .weak   UsageFault_Handler
    .type   UsageFault_Handler, %function
UsageFault_Handler:
    B       .
    .size   UsageFault_Handler, . - UsageFault_Handler

    .weak   SVC_Handler
    .type   SVC_Handler, %function
SVC_Handler:
    B       .
    .size   SVC_Handler, . - SVC_Handler

    .weak   DebugMon_Handler
    .type   DebugMon_Handler, %function
DebugMon_Handler:
    B       .
    .size   DebugMon_Handler, . - DebugMon_Handler

    .weak   PendSV_Handler
    .type   PendSV_Handler, %function
PendSV_Handler:
    B       .
    .size   PendSV_Handler, . - PendSV_Handler

    .weak   SysTick_Handler
    .type   SysTick_Handler, %function
SysTick_Handler:
    B       .
    .size   SysTick_Handler, . - SysTick_Handler


/* IRQ Handlers */

    .globl  Default_Handler
    .type   Default_Handler, %function
Default_Handler:
    B       .
    .size   Default_Handler, . - Default_Handler

    .macro  IRQ handler
    .weak   \handler
    .set    \handler, Default_Handler
    .endm

    IRQ    RTC_IRQHandler
    IRQ    M4CORE_IRQHandler
    IRQ    DMA_IRQHandler
    IRQ    FLASHEEPROMAT_IRQHandler
    IRQ    ETH_IRQHandler
    IRQ    SDIO_IRQHandler
    IRQ    LCD_IRQHandler
    IRQ    USB0_IRQHandler
    IRQ    USB1_IRQHandler
    IRQ    SCT_IRQHandler
    IRQ    RIT_OR_WWDT_IRQHandler
    IRQ    TIMER0_IRQHandler
    IRQ    GINT1_IRQHandler
    IRQ    PIN_INT4_IRQHandler
    IRQ    TIMER3_IRQHandler
    IRQ    MCPWM_IRQHandler
    IRQ    ADC0_IRQHandler
    IRQ    I2C0_OR_I2C1_IRQHandler
    IRQ    SGPIO_IRQHandler
    IRQ    SPI_OR_DAC_IRQHandler
    IRQ    ADC1_IRQHandler
    IRQ    SSP0_OR_SSP1_IRQHandler
    IRQ    EVENTROUTER_IRQHandler
    IRQ    UART0_IRQHandler
    IRQ    UART1_IRQHandler
    IRQ    UART2_OR_C_CAN1_IRQHandler
    IRQ    UART3_IRQHandler
    IRQ    I2S0_OR_I2S1_OR_QEI_IRQHandler
    IRQ    C_CAN0_IRQHandler

    .end
