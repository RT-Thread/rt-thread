/**
 * startup_LPC17xx.s
 */

	.syntax unified
	.cpu cortex-m3
	.fpu softvfp
	.thumb

	.word  _sidata
	.word  _sdata
	.word  _edata
	.word  _sbss
	.word  _ebss

/* Vector Table */

    .section ".interrupt_vector"
    .globl  __interrupt_vector
    .type   __interrupt_vector, %object

__interrupt_vector:
    .long   _estack                     /* Top of Stack                 */
    .long   Reset_Handler               /* Reset Handler                */
    .long   NMI_Handler                 /* NMI Handler                  */
    .long   HardFault_Handler           /* Hard Fault Handler           */
    .long   MemManage_Handler           /* MPU Fault Handler            */
    .long   BusFault_Handler            /* Bus Fault Handler            */
    .long   UsageFault_Handler          /* Usage Fault Handler          */
    .long   0                           /* Reserved                     */
    .long   0                           /* Reserved                     */
    .long   0                           /* Reserved                     */
    .long   0                           /* Reserved                     */
    .long   SVC_Handler                 /* SVCall Handler               */
    .long   DebugMon_Handler            /* Debug Monitor Handler        */
    .long   0                           /* Reserved                     */
    .long   PendSV_Handler              /* PendSV Handler               */
    .long   SysTick_Handler             /* SysTick Handler              */

    /* External Interrupts */
    .long   WDT_IRQHandler              /* 16: Watchdog Timer               */
    .long   TIMER0_IRQHandler           /* 17: Timer0                       */
    .long   TIMER1_IRQHandler           /* 18: Timer1                       */
    .long   TIMER2_IRQHandler           /* 19: Timer2                       */
    .long   TIMER3_IRQHandler           /* 20: Timer3                       */
    .long   UART0_IRQHandler            /* 21: UART0                        */
    .long   UART1_IRQHandler            /* 22: UART1                        */
    .long   UART2_IRQHandler            /* 23: UART2                        */
    .long   UART3_IRQHandler            /* 24: UART3                        */
    .long   PWM1_IRQHandler             /* 25: PWM1                         */
    .long   I2C0_IRQHandler             /* 26: I2C0                         */
    .long   I2C1_IRQHandler             /* 27: I2C1                         */
    .long   I2C2_IRQHandler             /* 28: I2C2                         */
    .long   SPI_IRQHandler              /* 29: SPI                          */
    .long   SSP0_IRQHandler             /* 30: SSP0                         */
    .long   SSP1_IRQHandler             /* 31: SSP1                         */
    .long   PLL0_IRQHandler             /* 32: PLL0 Lock (Main PLL)         */
    .long   RTC_IRQHandler              /* 33: Real Time Clock              */
    .long   EINT0_IRQHandler            /* 34: External Interrupt 0         */
    .long   EINT1_IRQHandler            /* 35: External Interrupt 1         */
    .long   EINT2_IRQHandler            /* 36: External Interrupt 2         */
    .long   EINT3_IRQHandler            /* 37: External Interrupt 3         */
    .long   ADC_IRQHandler              /* 38: A/D Converter                */
    .long   BOD_IRQHandler              /* 39: Brown-Out Detect             */
    .long   USB_IRQHandler              /* 40: USB                          */
    .long   CAN_IRQHandler              /* 41: CAN                          */
    .long   DMA_IRQHandler              /* 42: General Purpose DMA          */
    .long   I2S_IRQHandler              /* 43: I2S                          */
    .long   ENET_IRQHandler             /* 44: Ethernet                     */
    .long   RIT_IRQHandler              /* 45: Repetitive Interrupt Timer   */
    .long   MCPWM_IRQHandler            /* 46: Motor Control PWM            */
    .long   QEI_IRQHandler              /* 47: Quadrature Encoder Interface */
    .long   PLL1_IRQHandler             /* 48: PLL1 Lock (USB PLL)          */

    .size   __interrupt_vector, . - __interrupt_vector

/* Reset Handler */
    .section  .text.Reset_Handler
	.weak  Reset_Handler
	.type  Reset_Handler, %function
Reset_Handler:
    .fnstart

/* Copy the data segment initializers from flash to SRAM */
	movs	r1, #0
  	b	LoopCopyDataInit

CopyDataInit:
	ldr	r3, =_sidata
	ldr	r3, [r3, r1]
	str	r3, [r0, r1]
	add	r1, r1, #4

LoopCopyDataInit:
	ldr	r0, =_sdata
	ldr	r3, =_edata
	add	r2, r0, r1
	cmp	r2, r3
	bcc	CopyDataInit
	ldr	r2, =_sbss
	b	LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
	movs	r3, #0
	str	r3, [r2], #4

LoopFillZerobss:
	ldr	r3, = _ebss
	cmp	r2, r3
	bcc	FillZerobss
/* Call the clock system intitialization function.*/
  	bl  SystemInit
/* Call the application's entry point.*/
	bl	main
	bx	lr

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

    IRQ     WDT_IRQHandler
    IRQ     TIMER0_IRQHandler
    IRQ     TIMER1_IRQHandler
    IRQ     TIMER2_IRQHandler
    IRQ     TIMER3_IRQHandler
    IRQ     UART0_IRQHandler
    IRQ     UART1_IRQHandler
    IRQ     UART2_IRQHandler
    IRQ     UART3_IRQHandler
    IRQ     PWM1_IRQHandler
    IRQ     I2C0_IRQHandler
    IRQ     I2C1_IRQHandler
    IRQ     I2C2_IRQHandler
    IRQ     SPI_IRQHandler
    IRQ     SSP0_IRQHandler
    IRQ     SSP1_IRQHandler
    IRQ     PLL0_IRQHandler
    IRQ     RTC_IRQHandler
    IRQ     EINT0_IRQHandler
    IRQ     EINT1_IRQHandler
    IRQ     EINT2_IRQHandler
    IRQ     EINT3_IRQHandler
    IRQ     ADC_IRQHandler
    IRQ     BOD_IRQHandler
    IRQ     USB_IRQHandler
    IRQ     CAN_IRQHandler
    IRQ     DMA_IRQHandler
    IRQ     I2S_IRQHandler
    IRQ     ENET_IRQHandler
    IRQ     RIT_IRQHandler
    IRQ     MCPWM_IRQHandler
    IRQ     QEI_IRQHandler
    IRQ     PLL1_IRQHandler

    .end
