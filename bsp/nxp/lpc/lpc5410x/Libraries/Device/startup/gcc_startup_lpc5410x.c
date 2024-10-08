/* Startup code for use with GNU tools.*/
/* Forward declaration of the default fault handlers.*/
static void Reset_Handler(void);
static void Default_Handler(void);

/* External declaration for the interrupt handler used by the application.*/
void NMI_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)      __attribute__((weak, alias("Default_Handler")));

void WDT_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void BOD_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void Reserved_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void DMA_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void GINT0_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));

void PIN_INT0_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void PIN_INT1_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void PIN_INT2_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void PIN_INT3_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void UTICK_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void MRT_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void CT32B0_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void CT32B1_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void CT32B2_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void CT32B3_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void CT32B4_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void SCT0_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void UART0_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void UART1_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void UART2_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void UART3_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void I2C0_IRQHandler(void)     __attribute__((weak, alias("Default_Handler")));
void I2C1_IRQHandler(void)     __attribute__((weak, alias("Default_Handler")));
void I2C2_IRQHandler(void)     __attribute__((weak, alias("Default_Handler")));
void SPI0_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void ADC_SEQA_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void ADC_SEQB_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void ADC_THCMP_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void RTC_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
/*void Reserved_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));*/
void MAILBOX_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void GINT1_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void PIN_INT4_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void PIN_INT5_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void PIN_INT6_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void PIN_INT7_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
/*void Reserved_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));*/
/*void Reserved_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));*/
/*void Reserved_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));*/
void RIT_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void Reserved41_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void Reserved42_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void Reserved43_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void Reserved44_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
/* The entry point for the application.*/
extern int main(void);

/* Reserve space for the system stack.*/
static unsigned long pulStack[512];

/* The vector table.  Note that the proper constructs must be placed on this to*/
/* ensure that it ends up at physical address 0x0000.0000.*/
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))((unsigned long)pulStack + sizeof(pulStack)),
    /* The initial stack pointer*/
    Reset_Handler,              /* Reset Handler*/
    NMI_Handler,                /* NMI Handler*/
    HardFault_Handler,          /* Hard Fault Handler*/
    MemManage_Handler,          /* MPU Fault Handler*/
    BusFault_Handler,           /* Bus Fault Handler*/
    UsageFault_Handler,         /* Usage Fault Handler*/
    0,                          /* Reserved*/
    0,                          /* Reserved*/
    0,                          /* Reserved*/
    0,                          /* Reserved*/
    SVC_Handler,                /* SVCall Handler*/
    DebugMon_Handler,           /* Debug Monitor Handler*/
    0,                          /* Reserved*/
    PendSV_Handler,             /* PendSV Handler*/
    SysTick_Handler,            /* SysTick Handler*/

    /* External Interrupts*/
    WDT_IRQHandler,
    BOD_IRQHandler,
    Reserved_IRQHandler,
    DMA_IRQHandler,
    GINT0_IRQHandler,
    PIN_INT0_IRQHandler,
    PIN_INT1_IRQHandler,
    PIN_INT2_IRQHandler,
    PIN_INT3_IRQHandler,
    UTICK_IRQHandler,
    MRT_IRQHandler,
    CT32B0_IRQHandler,
    CT32B1_IRQHandler,
    CT32B2_IRQHandler,
    CT32B3_IRQHandler,
    CT32B4_IRQHandler,
    SCT0_IRQHandler,
    UART0_IRQHandler,
    UART1_IRQHandler,
    UART2_IRQHandler,
    UART3_IRQHandler,
    I2C0_IRQHandler,
    I2C1_IRQHandler,
    I2C2_IRQHandler,
    SPI0_IRQHandler,
    SPI1_IRQHandler,
    ADC_SEQA_IRQHandler,
    ADC_SEQB_IRQHandler,
    ADC_THCMP_IRQHandler,
    RTC_IRQHandler,
    Reserved_IRQHandler,
    MAILBOX_IRQHandler,
    GINT1_IRQHandler,
    PIN_INT4_IRQHandler,
    PIN_INT5_IRQHandler,
    PIN_INT6_IRQHandler,
    PIN_INT7_IRQHandler,
    Reserved_IRQHandler,
    Reserved_IRQHandler,
    Reserved_IRQHandler,
    RIT_IRQHandler,
    Reserved41_IRQHandler,
    Reserved42_IRQHandler,
    Reserved43_IRQHandler,
    Reserved44_IRQHandler,
};
/* RIT_IRQHandler        */
/*  Reserved41_IRQHandler*/
/* TReserved42_IRQHandler he following are constructs created by the linker, indicating where the*/
/* tReserved43_IRQHandler he "data" and "bss" segments reside in memory.  The initializers for the*/
/* fReserved44_IRQHandler or the "data" segment resides immediately following the "text" segment.*/
extern unsigned long _etext;
extern unsigned long _data;
extern unsigned long _edata;
extern unsigned long _bss;
extern unsigned long _ebss;

/* This is the code that gets called when the processor first starts execution*/
/* following a reset event.  Only the absolutely necessary set is performed,*/
/* after which the application supplied entry() routine is called.  Any fancy*/
/* actions (such as making decisions based on the reset cause register, and*/
/* resetting the bits in that register) are left solely in the hands of the*/
/* application.*/
static void Reset_Handler(void)
{
    unsigned long *pulSrc, *pulDest;

    /* Copy the data segment initializers from flash to SRAM.*/
    pulSrc = &_etext;
    /* cppcheck-suppress comparePointers */
    for(pulDest = &_data; pulDest < &_edata; )
    {
        *pulDest++ = *pulSrc++;
    }


#if !defined (__USE_LPCOPEN)
/* LPCOpen init code deals with FP and VTOR initialisation*/
#if defined (__VFP_FP__) && !defined (__SOFTFP__)
    /*
     * Code to enable the Cortex-M4 FPU only included
     * if appropriate build options have been selected.
     * Code taken from Section 7.1, Cortex-M4 TRM (DDI0439C)
     */
    /* CPACR is located at address 0xE000ED88*/
    asm("LDR.W R0, =0xE000ED88");
    /* Read CPACR*/
    asm("LDR R1, [R0]");
    /* Set bits 20-23 to enable CP10 and CP11 coprocessors*/
    asm(" ORR R1, R1, #(0xF << 20)");
    /* Write back the modified value to the CPACR*/
    asm("STR R1, [R0]");
#endif /* (__VFP_FP__) && !(__SOFTFP__)*/
    /* Check to see if we are running the code from a non-zero*/
    /* address (eg RAM, external flash), in which case we need*/
    /* to modify the VTOR register to tell the CPU that the*/
    /* vector table is located at a non-0x0 address.*/

    /* Note that we do not use the CMSIS register access mechanism,*/
    /* as there is no guarantee that the project has been configured*/
    /* to use CMSIS.*/
    unsigned int * pSCB_VTOR = (unsigned int *) 0xE000ED08;
    if ((unsigned int *) g_pfnVectors != (unsigned int *) 0x00000000)
    {
        /* CMSIS : SCB->VTOR = <address of vector table>*/
        *pSCB_VTOR = (unsigned int) g_pfnVectors;
    }
#endif

    /* Zero fill the bss segment.*/
    __asm("    ldr     r0, =_bss\n"
          "    ldr     r1, =_ebss\n"
          "    mov     r2, #0\n"
          "    .thumb_func\n"
          "zero_loop:\n"
          "        cmp     r0, r1\n"
          "        it      lt\n"
          "        strlt   r2, [r0], #4\n"
          "        blt     zero_loop");

    /* call system init.*/
    extern void SystemInit(void);
    SystemInit();

    /* Call the application's entry point.*/
    main();
}

/* This is the code that gets called when the processor receives an unexpected*/
/* interrupt.  This simply enters an infinite loop, preserving the system state*/
/* for examination by a debugger.*/
static void Default_Handler(void)
{
    /* Go into an infinite loop.*/
    while(1)
    {
    }
}