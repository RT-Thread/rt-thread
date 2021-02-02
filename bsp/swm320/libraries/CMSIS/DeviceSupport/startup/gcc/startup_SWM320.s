    .syntax unified
    .arch armv7-m
	.thumb

/* Memory Model
   The HEAP starts at the end of the DATA section and grows upward.
   
   The STACK starts at the end of the RAM and grows downward     */
    .section .stack
    .align 3
    .globl    __StackTop
    .globl    __StackLimit
__StackLimit:
    .space    0x4000
__StackTop:


    .section .heap
    .align 3
    .globl    __HeapBase
    .globl    __HeapLimit
__HeapBase:
    .space    0x4000
__HeapLimit:


    .section .isr_vector
    .align 2
    .globl __isr_vector
__isr_vector:
    .long    __StackTop            
    .long    Reset_Handler         
    .long    NMI_Handler          
    .long    HardFault_Handler     
    .long    MemManage_Handler     
    .long    BusFault_Handler      
    .long    UsageFault_Handler   
    .long    0                    
    .long    0                    
    .long    0                    
    .long    0                     
    .long    SVC_Handler          
    .long    DebugMon_Handler     
    .long    0                     
    .long    PendSV_Handler           
    .long    SysTick_Handler         

    /* External interrupts */
    .long     GPIOA0_Handler
    .long     GPIOA1_Handler
    .long     GPIOA2_Handler
    .long     GPIOA3_Handler
    .long     GPIOA4_Handler
    .long     GPIOA5_Handler
    .long     GPIOA6_Handler
    .long     GPIOA7_Handler
    .long     GPIOB0_Handler
    .long     GPIOB1_Handler
    .long     GPIOB2_Handler
    .long     GPIOB3_Handler
    .long     GPIOB4_Handler
    .long     GPIOB5_Handler
    .long     GPIOB6_Handler
    .long     GPIOB7_Handler
    .long     GPIOC0_Handler
    .long     GPIOC1_Handler
    .long     GPIOC2_Handler
    .long     GPIOC3_Handler
    .long     GPIOC4_Handler
    .long     GPIOC5_Handler
    .long     GPIOC6_Handler
    .long     GPIOC7_Handler                                 
    .long     GPIOM0_Handler
    .long     GPIOM1_Handler
    .long     GPIOM2_Handler
    .long     GPIOM3_Handler
    .long     GPIOM4_Handler
    .long     GPIOM5_Handler
    .long     GPIOM6_Handler
    .long     GPIOM7_Handler                                            
    .long     DMA_Handler
    .long     LCD_Handler
    .long     NORFLC_Handler
    .long     CAN_Handler
    .long     PULSE_Handler
    .long     WDT_Handler
    .long     PWM_Handler
    .long     UART0_Handler
    .long     UART1_Handler
    .long     UART2_Handler
    .long     UART3_Handler
    .long     Default_Handler
    .long     I2C0_Handler
    .long     I2C1_Handler
    .long     SPI0_Handler
    .long     ADC0_Handler
    .long     RTC_Handler
    .long     BOD_Handler
    .long     SDIO_Handler
    .long     GPIOA_Handler
    .long     GPIOB_Handler
    .long     GPIOC_Handler
    .long     GPIOM_Handler
    .long     GPION_Handler
    .long     GPIOP_Handler
    .long     ADC1_Handler
    .long     FPU_Handler
    .long     SPI1_Handler
    .long     TIMR0_Handler
    .long     TIMR1_Handler
    .long     TIMR2_Handler
    .long     TIMR3_Handler
    .long     TIMR4_Handler
    .long     TIMR5_Handler

	.section .text.Reset_Handler
    .align 2
    .globl    Reset_Handler
    .type     Reset_Handler, %function
Reset_Handler:
/* Loop to copy data from read only memory to RAM. The ranges
 * of copy from/to are specified by symbols evaluated in linker script.  */
    ldr    sp, =__StackTop    		 /* set stack pointer */

    ldr    r1, =__data_load__
    ldr    r2, =__data_start__
    ldr    r3, =__data_end__

.Lflash_to_ram_loop:
    cmp     r2, r3
    ittt    lo
    ldrlo   r0, [r1], #4
    strlo   r0, [r2], #4
    blo    .Lflash_to_ram_loop


    ldr    r2, =__bss_start__
    ldr    r3, =__bss_end__

.Lbss_to_ram_loop:
    cmp     r2, r3
    ittt    lo
    movlo   r0, #0
    strlo   r0, [r2], #4
    blo    .Lbss_to_ram_loop

    ldr    r0, =main
    bx     r0
    .pool    


    .text
/* Macro to define default handlers. 
   Default handler will be weak symbol and just dead loops. */
    .macro    def_default_handler    handler_name
    .align 1
    .thumb_func
    .weak    \handler_name
    .type    \handler_name, %function
\handler_name :
    b    .
    .endm

    def_default_handler    NMI_Handler
    def_default_handler    HardFault_Handler
    def_default_handler    MemManage_Handler
    def_default_handler    BusFault_Handler
    def_default_handler    UsageFault_Handler
    def_default_handler    SVC_Handler
    def_default_handler    DebugMon_Handler
    def_default_handler    PendSV_Handler
    def_default_handler    SysTick_Handler

    def_default_handler    GPIOA0_Handler
    def_default_handler    GPIOA1_Handler
    def_default_handler    GPIOA2_Handler
    def_default_handler    GPIOA3_Handler
    def_default_handler    GPIOA4_Handler
    def_default_handler    GPIOA5_Handler
    def_default_handler    GPIOA6_Handler
    def_default_handler    GPIOA7_Handler
    def_default_handler    GPIOB0_Handler
    def_default_handler    GPIOB1_Handler
    def_default_handler    GPIOB2_Handler
    def_default_handler    GPIOB3_Handler
    def_default_handler    GPIOB4_Handler
    def_default_handler    GPIOB5_Handler
    def_default_handler    GPIOB6_Handler
    def_default_handler    GPIOB7_Handler
    def_default_handler    GPIOC0_Handler
    def_default_handler    GPIOC1_Handler
    def_default_handler    GPIOC2_Handler
    def_default_handler    GPIOC3_Handler
    def_default_handler    GPIOC4_Handler
    def_default_handler    GPIOC5_Handler
    def_default_handler    GPIOC6_Handler
    def_default_handler    GPIOC7_Handler                                 
    def_default_handler    GPIOM0_Handler
    def_default_handler    GPIOM1_Handler
    def_default_handler    GPIOM2_Handler
    def_default_handler    GPIOM3_Handler
    def_default_handler    GPIOM4_Handler
    def_default_handler    GPIOM5_Handler
    def_default_handler    GPIOM6_Handler
    def_default_handler    GPIOM7_Handler                                            
    def_default_handler    DMA_Handler
    def_default_handler    LCD_Handler
    def_default_handler    NORFLC_Handler
    def_default_handler    CAN_Handler
    def_default_handler    PULSE_Handler
    def_default_handler    WDT_Handler
    def_default_handler    PWM_Handler
    def_default_handler    UART0_Handler
    def_default_handler    UART1_Handler
    def_default_handler    UART2_Handler
    def_default_handler    UART3_Handler
    def_default_handler    I2C0_Handler
    def_default_handler    I2C1_Handler
    def_default_handler    SPI0_Handler
    def_default_handler    ADC0_Handler
    def_default_handler    RTC_Handler
    def_default_handler    BOD_Handler
    def_default_handler    SDIO_Handler
    def_default_handler    GPIOA_Handler
    def_default_handler    GPIOB_Handler
    def_default_handler    GPIOC_Handler
    def_default_handler    GPIOM_Handler
    def_default_handler    GPION_Handler
    def_default_handler    GPIOP_Handler
    def_default_handler    ADC1_Handler
    def_default_handler    FPU_Handler
    def_default_handler    SPI1_Handler
    def_default_handler    TIMR0_Handler
    def_default_handler    TIMR1_Handler
    def_default_handler    TIMR2_Handler
    def_default_handler    TIMR3_Handler
    def_default_handler    TIMR4_Handler
    def_default_handler    TIMR5_Handler

    def_default_handler    Default_Handler

    .end
