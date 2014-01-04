/*****************************************************************************/
/* startup_LPC18xx.s: Startup file for LPC18xx device series                 */
/*****************************************************************************/
/* Version: CodeSourcery Sourcery G++ Lite (with CS3)                        */
/*****************************************************************************/


/*
//*** <<< Use Configuration Wizard in Context Menu >>> ***
*/


/*
// <h> Stack Configuration
//   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
// </h>
*/

    .equ    Stack_Size, 0x00000200
    .equ    Sign_Value, 0x5A5A5A5A
    .section ".stack", "w"
    .align  3
    .globl  __cs3_stack_mem
    .globl  __cs3_stack_size
__cs3_stack_mem:
    .if     Stack_Size
    .space  Stack_Size
    .endif
    .size   __cs3_stack_mem,  . - __cs3_stack_mem
    .set    __cs3_stack_size, . - __cs3_stack_mem


/*
// <h> Heap Configuration
//   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
// </h>
*/

    .equ    Heap_Size,  0x00001000

    .section ".heap", "w"
    .align  3
    .globl  __cs3_heap_start
    .globl  __cs3_heap_end
__cs3_heap_start:
    .if     Heap_Size
    .space  Heap_Size
    .endif
__cs3_heap_end:


/* Vector Table */

    .section ".cs3.interrupt_vector"
    .globl  __cs3_interrupt_vector_cortex_m
    .type   __cs3_interrupt_vector_cortex_m, %object

__cs3_interrupt_vector_cortex_m:
    .long   _estack                     /* Top of Stack                 */
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
    .long	DAC_IRQHandler	 			/* 16 D/A Converter */
	.long	MX_CORE_IRQHandler			/* 17 M0/M4 IRQ handler (LPC43XX ONLY) */
	.long	DMA_IRQHandler				/* 18 General Purpose DMA */
	.long	UnHandled_Vector			/* 19 Reserved */
	.long	FLASHEEPROM_IRQHandler		/* 20 ORed flash bank A, flash bank B, EEPROM interrupts */
	.long	ETH_IRQHandler				/* 21 Ethernet */
	.long	SDIO_IRQHandler				/* 22 SD/MMC */
	.long	LCD_IRQHandler				/* 23 LCD */
	.long	USB0_IRQHandler				/* 24 USB0*/
	.long	USB1_IRQHandler				/* 25 USB1*/
	.long	SCT_IRQHandler				/* 26 State Configurable Timer*/
	.long	RIT_IRQHandler				/* 27 Repetitive Interrupt Timer*/
	.long	TIMER0_IRQHandler			/* 28 Timer0*/
	.long	TIMER1_IRQHandler			/* 29 Timer1*/
	.long	TIMER2_IRQHandler			/* 30 Timer2*/
	.long	TIMER3_IRQHandler			/* 31 Timer3*/
	.long	MCPWM_IRQHandler			/* 32 Motor Control PWM*/
	.long	ADC0_IRQHandler				/* 33 A/D Converter 0*/
	.long	I2C0_IRQHandler				/* 34 I2C0*/
	.long	I2C1_IRQHandler				/* 35 I2C1*/
	.long	SPI_IRQHandler				/* 36 SPI (LPC43XX ONLY)*/
	.long	ADC1_IRQHandler				/* 37 A/D Converter 1*/
	.long	SSP0_IRQHandler				/* 38 SSP0*/
	.long	SSP1_IRQHandler				/* 39 SSP1*/
	.long	UART0_IRQHandler			/* 40 UART0*/
	.long	UART1_IRQHandler			/* 41 UART1*/
	.long	UART2_IRQHandler			/* 42 UART2*/
	.long	UART3_IRQHandler			/* 43 UART3*/
	.long	I2S0_IRQHandler				/* 44 I2S*/
	.long 	I2S1_IRQHandler				/* 45 AES Engine*/
	.long 	SPIFI_IRQHandler			/* 46 SPI Flash Interface*/
	.long	SGPIO_IRQHandler			/* 47 SGPIO*/
	.long	GPIO0_IRQHandler			/* 48 GPIO0*/
	.long	GPIO1_IRQHandler			/* 49 GPIO1*/
	.long	GPIO2_IRQHandler			/* 50 GPIO2*/
	.long	GPIO3_IRQHandler			/* 51 GPIO3*/
	.long	GPIO4_IRQHandler			/* 52 GPIO4*/
	.long	GPIO5_IRQHandler			/* 53 GPIO5*/
	.long	GPIO6_IRQHandler			/* 54 GPIO6*/
	.long	GPIO7_IRQHandler			/* 55 GPIO7*/
	.long	GINT0_IRQHandler			/* 56 GINT0*/
	.long	GINT1_IRQHandler			/* 57 GINT1*/
	.long	EVRT_IRQHandler				/* 58 Event Router*/
	.long	CAN1_IRQHandler				/* 59 C_CAN1*/
	.long	UnHandled_Vector			/* 60 Reserved*/
	.long	VADC_IRQHandler				/* 61 VADC*/
	.long	ATIMER_IRQHandler			/* 62 ATIMER*/
	.long	RTC_IRQHandler				/* 63 RTC*/
	.long	UnHandled_Vector			/* 64 Reserved*/
	.long	WDT_IRQHandler				/* 65 WDT*/
	.long	UnHandled_Vector			/* 66 M0s*/
	.long	CAN0_IRQHandler				/* 67 C_CAN0*/
	.long 	QEI_IRQHandler				/* 68 QEI*/

    .size   __cs3_interrupt_vector_cortex_m, . - __cs3_interrupt_vector_cortex_m


    .thumb


/* Reset Handler */

    .section  .text.Reset_Handler
    .thumb_func
    .globl  Reset_Handler
    .type  Reset_Handler, %function
Reset_Handler:
    .fnstart
/* .if (RAM_MODE) */
 .if 0
/* Clear .bss section (Zero init) */
	MOV     R0, #0
	LDR     R1, =__bss_start__
	LDR     R2, =__bss_end__
	CMP     R1,R2
	BEQ     BSSIsEmpty
LoopZI:
	CMP     R1, R2
	BHS		BSSIsEmpty
	STR   	R0, [R1]
	ADD		R1, #4
	BLO     LoopZI
BSSIsEmpty:
    LDR     R0,=main
    BX      R0
.else
    LDR     R0, =SystemInit
    BLX     R0
    LDR     R0,=main
    BX      R0
.endif
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

    .globl  UnHandled_Vector
    .type   UnHandled_Vector, %function
UnHandled_Vector:
    B       .
    .size   UnHandled_Vector, . - UnHandled_Vector
    
    .macro  IRQ handler
    .weak   \handler
    .set    \handler, Default_Handler
    .endm

    IRQ DAC_IRQHandler
    IRQ MX_CORE_IRQHandler
	IRQ DMA_IRQHandler
	IRQ FLASHEEPROM_IRQHandler
	IRQ ETH_IRQHandler
	IRQ SDIO_IRQHandler
	IRQ LCD_IRQHandler
	IRQ USB0_IRQHandler
	IRQ USB1_IRQHandler
	IRQ SCT_IRQHandler
	IRQ RIT_IRQHandler
	IRQ TIMER0_IRQHandler
	IRQ TIMER1_IRQHandler
	IRQ TIMER2_IRQHandler
	IRQ TIMER3_IRQHandler
	IRQ MCPWM_IRQHandler
	IRQ ADC0_IRQHandler
	IRQ I2C0_IRQHandler
	IRQ I2C1_IRQHandler
	IRQ SPI_IRQHandler
	IRQ ADC1_IRQHandler
	IRQ SSP0_IRQHandler
	IRQ SSP1_IRQHandler
	IRQ UART0_IRQHandler
	IRQ UART1_IRQHandler
	IRQ UART2_IRQHandler
	IRQ UART3_IRQHandler
	IRQ I2S0_IRQHandler
	IRQ I2S1_IRQHandler
	IRQ SPIFI_IRQHandler
	IRQ	SGPIO_IRQHandler
	IRQ	GPIO0_IRQHandler
	IRQ	GPIO1_IRQHandler
	IRQ	GPIO2_IRQHandler
	IRQ	GPIO3_IRQHandler
	IRQ	GPIO4_IRQHandler
	IRQ	GPIO5_IRQHandler
	IRQ	GPIO6_IRQHandler
	IRQ	GPIO7_IRQHandler
	IRQ	GINT0_IRQHandler
	IRQ	GINT1_IRQHandler
	IRQ	EVRT_IRQHandler
	IRQ	CAN1_IRQHandler
	IRQ	VADC_IRQHandler
	IRQ	ATIMER_IRQHandler
	IRQ	RTC_IRQHandler
	IRQ	WDT_IRQHandler
	IRQ	CAN0_IRQHandler
	IRQ	QEI_IRQHandler
    .end
