//*****************************************************************************
//
// Startup code for use with GNU tools.
//
//*****************************************************************************


//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
static void Reset_Handler(void);
static void Default_Handler(void);

//*****************************************************************************
//
// External declaration for the interrupt handler used by the application.
//
//*****************************************************************************
void NMI_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)      __attribute__((weak, alias("Default_Handler")));

void ETH_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void USB_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void DMAC_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void CAN0_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void CAN1_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));

void FP0_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void FP1_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void FP2_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void FP3_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void FP4_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void FP5_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void FP6_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void FP7_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void FP8_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void FP9_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void FP10_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void FP11_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void FP12_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void FP13_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void FP14_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void FP15_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void UART0_IRQHandler(void)     __attribute__((weak, alias("Default_Handler")));
void UART1_IRQHandler(void)     __attribute__((weak, alias("Default_Handler")));
void ADC_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void GPIO_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void I2C1_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void SPI0_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void I2C0_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void RTC_1S_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));
void RTC_1MS_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void WDG_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void TIMER_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void DDRC_SW_PROC_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void ETH_PMT_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void PAD_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void DDRC_LANE_SYNC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART2_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));

//*****************************************************************************
//
// The entry point for the application.
//
//*****************************************************************************
extern int main(void);

//*****************************************************************************
//
// Reserve space for the system stack.
//
//*****************************************************************************
static unsigned long pulStack[512];

//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000.
//
//*****************************************************************************
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))((unsigned long)pulStack + sizeof(pulStack)),
    // The initial stack pointer
    Reset_Handler,              // Reset Handler
    NMI_Handler,                // NMI Handler
    HardFault_Handler,          // Hard Fault Handler
    MemManage_Handler,          // MPU Fault Handler
    BusFault_Handler,           // Bus Fault Handler
    UsageFault_Handler,         // Usage Fault Handler
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    SVC_Handler,                // SVCall Handler
    DebugMon_Handler,           // Debug Monitor Handler
    0,                          // Reserved
    PendSV_Handler,             // PendSV Handler
    SysTick_Handler,            // SysTick Handler

    // External Interrupts
    ETH_IRQHandler,
    USB_IRQHandler,
    DMAC_IRQHandler,
    CAN0_IRQHandler,
    CAN1_IRQHandler,
    FP0_IRQHandler,
    FP1_IRQHandler,
    FP2_IRQHandler,
    FP3_IRQHandler,
    FP4_IRQHandler,
    FP5_IRQHandler,
    FP6_IRQHandler,
    FP7_IRQHandler,
    FP8_IRQHandler,
    FP9_IRQHandler,
    FP10_IRQHandler,
    FP11_IRQHandler,
    FP12_IRQHandler,
    FP13_IRQHandler,
    FP14_IRQHandler,
    FP15_IRQHandler,
    UART0_IRQHandler,
    UART1_IRQHandler,
    ADC_IRQHandler,
    GPIO_IRQHandler,
    SPI1_IRQHandler,
    I2C1_IRQHandler,
    SPI0_IRQHandler,
    I2C0_IRQHandler,
    RTC_1S_IRQHandler,
    RTC_1MS_IRQHandler,
    WDG_IRQHandler,
    TIMER_IRQHandler,
    DDRC_SW_PROC_IRQHandler,
    ETH_PMT_IRQHandler,
    PAD_IRQHandler,
    DDRC_LANE_SYNC_IRQHandler,
    UART2_IRQHandler,
};

//*****************************************************************************
//
// The following are constructs created by the linker, indicating where the
// the "data" and "bss" segments reside in memory.  The initializers for the
// for the "data" segment resides immediately following the "text" segment.
//
//*****************************************************************************
extern unsigned long _etext;
extern unsigned long _data;
extern unsigned long _edata;
extern unsigned long _bss;
extern unsigned long _ebss;

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************
static void Reset_Handler(void)
{
    unsigned long *pulSrc, *pulDest;

    //
    // Copy the data segment initializers from flash to SRAM.
    //
    pulSrc = &_etext;
    for(pulDest = &_data; pulDest < &_edata; )
    {
        *pulDest++ = *pulSrc++;
    }

    //
    // Zero fill the bss segment.
    //
    __asm("    ldr     r0, =_bss\n"
          "    ldr     r1, =_ebss\n"
          "    mov     r2, #0\n"
          "    .thumb_func\n"
          "zero_loop:\n"
          "        cmp     r0, r1\n"
          "        it      lt\n"
          "        strlt   r2, [r0], #4\n"
          "        blt     zero_loop");

    // call system init.	
	SystemInit();

    //
    // Call the application's entry point.
    //
    main();
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void Default_Handler(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}
