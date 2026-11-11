    MODULE ?cstartup

    EXTERN __iar_program_start

    SECTION CSTACK:DATA:NOROOT(3)

    PUBLIC start_flash
    SECTION .intvec:CODE:REORDER(2)
start_flash
    LDR R0, =hardware_init
    BX R0

    PUBLIC hard_fault_handler
hard_fault_handler
    BL HARD_FAULT_IRQHandler

    PUBLIC svc_handler
svc_handler
    BL SVC_IRQHandler

    PUBLIC pendsv_handler
pendsv_handler
    BL PENDSV_IRQHandler

    PUBLIC systick
systick
    BL SYSTICK_IRQHandler

    PUBLIC irq0
irq0
    movs r0,#0
    b isr

    PUBLIC irq1
irq1
    movs r0,#1
    b isr

    PUBLIC irq2
irq2
    movs r0,#2
    b isr

    PUBLIC irq3
irq3
    movs r0,#3
    b isr

    PUBLIC irq4
irq4
    movs r0,#4
    b isr

    PUBLIC irq5
irq5
    movs r0,#5
    b isr

    PUBLIC irq6
irq6
    movs r0,#6
    b isr

    PUBLIC irq7
irq7
    movs r0,#7
    b isr

    PUBLIC irq8
irq8
    movs r0,#8
    b isr

    PUBLIC irq9
irq9
    movs r0,#9
    b isr

    PUBLIC irq10
irq10
    movs r0,#10
    b isr

    PUBLIC irq11
irq11
    movs r0,#11
    b isr

    PUBLIC irq12
irq12
    movs r0,#12
    b isr

    PUBLIC irq13
irq13
    movs r0,#13
    b isr

    PUBLIC irq14
irq14
    movs r0,#14
    b isr

    PUBLIC irq15
irq15
    movs r0,#15
    b isr

    PUBLIC irq16
irq16
    movs r0,#16
    b isr

    PUBLIC irq17
irq17
    movs r0,#17
    b isr

    PUBLIC irq18
irq18
    movs r0,#18
    b isr

    PUBLIC irq19
irq19
    movs r0,#19
    b isr

    PUBLIC irq20
irq20
    movs r0,#20
    b isr

    PUBLIC irq21
irq21
    movs r0,#21
    b isr

    PUBLIC irq22
irq22
    movs r0,#22
    b isr

    PUBLIC irq23
irq23
    movs r0,#23
    b isr

    PUBLIC irq24
irq24
    movs r0,#24
    b isr

    PUBLIC irq25
irq25
    movs r0,#25
    b isr

    PUBLIC irq26
irq26
    movs r0,#26
    b isr

    PUBLIC irq27
irq27
    movs r0,#27
    b isr

    PUBLIC irq28
irq28
    movs r0,#28
    b isr

    PUBLIC irq29
irq29
    movs r0,#29
    b isr

    PUBLIC irq30
irq30
    movs r0,#30
    b isr

    PUBLIC irq31
irq31
    movs r0,#31
    b isr

    PUBLIC isr
isr
    ldr r1,=__vector_table
    ldr r0,[r0, r1]
    bx r0


    PUBWEAK HARD_FAULT_IRQHandler
    PUBWEAK SVC_IRQHandler
    PUBWEAK PENDSV_IRQHandler
    PUBWEAK SYSTICK_IRQHandler
    PUBWEAK USB_IRQHandler
    PUBWEAK IIC_IRQHandler
    PUBWEAK QSPI_IRQHandler
    PUBWEAK SPI0_IRQHandler
    PUBWEAK SPI1_IRQHandler
    PUBWEAK UART0_IRQHandler
    PUBWEAK UART1_IRQHandler
    PUBWEAK MEMCP_IRQHandler
    PUBWEAK RSA_IRQHandler
    PUBWEAK SCI0_IRQHandler
    PUBWEAK SCI1_IRQHandler
    PUBWEAK BT_IRQHandler
    PUBWEAK GPIO_IRQHandler
    PUBWEAK TIMER0_IRQHandler
    PUBWEAK TIMER1_IRQHandler
    PUBWEAK TIMER2_IRQHandler
    PUBWEAK TIMER3_IRQHandler
    PUBWEAK TIMER4_IRQHandler
    PUBWEAK TIMER5_IRQHandler
    PUBWEAK TIMER6_IRQHandler
    PUBWEAK TIMER7_IRQHandler
    PUBWEAK TIMER8_IRQHandler
    PUBWEAK SM4_IRQHandler
    PUBWEAK SEC_IRQHandler
    PUBWEAK MSR_IRQHandler
    PUBWEAK TRNG_IRQHandler
    PUBWEAK WDT_IRQHandler


HARD_FAULT_IRQHandler
SVC_IRQHandler
PENDSV_IRQHandler
SYSTICK_IRQHandler

USB_IRQHandler
IIC_IRQHandler
QSPI_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
MEMCP_IRQHandler
RSA_IRQHandler
SCI0_IRQHandler
SCI1_IRQHandler
BT_IRQHandler
GPIO_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
TIMER4_IRQHandler
TIMER5_IRQHandler
TIMER6_IRQHandler
TIMER7_IRQHandler
TIMER8_IRQHandler
SM4_IRQHandler
SEC_IRQHandler
MSR_IRQHandler
TRNG_IRQHandler
WDT_IRQHandler
    B       .

    PUBLIC delay
delay
    subs r0,#1
    bne delay
    nop
    bx lr

    PUBLIC __vector_table
    ALIGNROM 2
    data
__vector_table
    DCD USB_IRQHandler
    DCD IIC_IRQHandler
    DCD QSPI_IRQHandler
    DCD SPI0_IRQHandler
    DCD SPI1_IRQHandler
    DCD UART0_IRQHandler
    DCD UART1_IRQHandler
    DCD MEMCP_IRQHandler
    DCD RSA_IRQHandler
    DCD SCI0_IRQHandler
    DCD SCI1_IRQHandler
    DCD BT_IRQHandler
    DCD GPIO_IRQHandler
    DCD TIMER0_IRQHandler
    DCD TIMER1_IRQHandler
    DCD TIMER2_IRQHandler
    DCD TIMER3_IRQHandler
    DCD TIMER4_IRQHandler
    DCD TIMER5_IRQHandler
    DCD TIMER6_IRQHandler
    DCD TIMER7_IRQHandler
    DCD TIMER8_IRQHandler
    DCD SM4_IRQHandler
    DCD SEC_IRQHandler
    DCD MSR_IRQHandler
    DCD TRNG_IRQHandler
    DCD WDT_IRQHandler


    PUBLIC hardware_init
    SECTION .intvec:CODE:REORDER(2)
    CODE
hardware_init
    LDR R0, =sfe(CSTACK)
    mov	sp, R0
    LDR R0, =__iar_program_start
    BX 	R0
    END