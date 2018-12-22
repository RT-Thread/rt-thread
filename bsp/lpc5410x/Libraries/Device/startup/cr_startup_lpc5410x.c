//*****************************************************************************
// LPC5410x Microcontroller Startup code for use with LPCXpresso IDE
//
// Version : 141022
//*****************************************************************************
//
// Copyright(C) NXP Semiconductors, 2014
// All rights reserved.
//
// Software that is described herein is for illustrative purposes only
// which provides customers with programming information regarding the
// LPC products.  This software is supplied "AS IS" without any warranties of
// any kind, and NXP Semiconductors and its licensor disclaim any and
// all warranties, express or implied, including all implied warranties of
// merchantability, fitness for a particular purpose and non-infringement of
// intellectual property rights.  NXP Semiconductors assumes no responsibility
// or liability for the use of the software, conveys no license or rights under any
// patent, copyright, mask work right, or any other intellectual property rights in
// or to any products. NXP Semiconductors reserves the right to make changes
// in the software without notification. NXP Semiconductors also makes no
// representation or warranty that such application will be suitable for the
// specified use without further testing or modification.
//
// Permission to use, copy, modify, and distribute this software and its
// documentation is hereby granted, under NXP Semiconductors' and its
// licensor's relevant copyrights in the software, without fee, provided that it
// is used in conjunction with NXP Semiconductors microcontrollers.  This
// copyright, permission, and disclaimer notice must appear in all copies of
// this code.
//*****************************************************************************

#if defined (__cplusplus)
#ifdef __REDLIB__
#error Redlib does not support C++
#else
//*****************************************************************************
//
// The entry point for the C++ library startup
//
//*****************************************************************************
extern "C" {
    extern void __libc_init_array(void);
}
#endif
#endif

#define WEAK __attribute__ ((weak))
#define ALIAS(f) __attribute__ ((weak, alias (#f)))

//*****************************************************************************
#if defined (__cplusplus)
extern "C" {
#endif

//*****************************************************************************
#if defined (__USE_CMSIS) || defined (__USE_LPCOPEN)
// Declaration of external SystemInit function
extern void SystemInit(void);
#endif

//*****************************************************************************
//
// Forward declaration of the default handlers. These are aliased.
// When the application defines a handler (with the same name), this will
// automatically take precedence over these weak definitions
//
//*****************************************************************************
void ResetISR(void);
#if defined (__MULTICORE_MASTER)
void ResetISR2(void);
#endif
WEAK void NMI_Handler(void);
WEAK void HardFault_Handler(void);
WEAK void MemManage_Handler(void);
WEAK void BusFault_Handler(void);
WEAK void UsageFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void DebugMon_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);
WEAK void IntDefaultHandler(void);

//*****************************************************************************
//
// Forward declaration of the specific IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//
//*****************************************************************************
// External Interrupts - Available on M0/M4
void WDT_IRQHandler(void) ALIAS(IntDefaultHandler);
void BOD_IRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA_IRQHandler(void) ALIAS(IntDefaultHandler);
void GINT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT2_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT3_IRQHandler(void) ALIAS(IntDefaultHandler);
void UTICK_IRQHandler(void) ALIAS(IntDefaultHandler);
void MRT_IRQHandler(void) ALIAS(IntDefaultHandler);
void CT32B0_IRQHandler(void) ALIAS(IntDefaultHandler);
void CT32B1_IRQHandler(void) ALIAS(IntDefaultHandler);
void CT32B2_IRQHandler(void) ALIAS(IntDefaultHandler);
void CT32B3_IRQHandler(void) ALIAS(IntDefaultHandler);
void CT32B4_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART0_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART1_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART2_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART3_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C0_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C1_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C2_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI0_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI1_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC_SEQA_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC_SEQB_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC_THCMP_IRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_IRQHandler(void) ALIAS(IntDefaultHandler);
void MAILBOX_IRQHandler(void) ALIAS(IntDefaultHandler);
// External Interrupts - For M4 only
void GINT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT4_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT5_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT6_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT7_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI2_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI3_IRQHandler(void) ALIAS(IntDefaultHandler);
void RIT_IRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved41_IRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved42_IRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved43_IRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved44_IRQHandler(void) ALIAS(IntDefaultHandler);

//*****************************************************************************
//
// The entry point for the application.
// __main() is the entry point for Redlib based applications
// main() is the entry point for Newlib based applications
//
//*****************************************************************************
#if defined (__REDLIB__)
extern void __main(void);
#endif
extern int main(void);
//*****************************************************************************
//
// External declaration for the pointer to the stack top from the Linker Script
//
//*****************************************************************************
extern void _vStackTop(void);

//*****************************************************************************
#if defined (__cplusplus)
} // extern "C"
#endif
//*****************************************************************************
//
// The vector table.
// This relies on the linker script to place at correct location in memory.
//
//*****************************************************************************
extern void (* const g_pfnVectors[])(void);
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    // Core Level - CM3
        &_vStackTop,            // The initial stack pointer
        ResetISR,               // The reset handler
        NMI_Handler,            // The NMI handler
        HardFault_Handler,      // The hard fault handler
        MemManage_Handler,      // The MPU fault handler
        BusFault_Handler,       // The bus fault handler
        UsageFault_Handler,     // The usage fault handler
        0,                      // Reserved
        0,                      // Reserved
        0,                      // Reserved
        0,                      // Reserved
        SVC_Handler,            // SVCall handler
        DebugMon_Handler,       // Debug monitor handler
        0,                      // Reserved
        PendSV_Handler,         // The PendSV handler
        SysTick_Handler,        // The SysTick handler

        // External Interrupts - Available on M0/M4
        WDT_IRQHandler,         // Watchdog
        BOD_IRQHandler,         // Brown Out Detect
        Reserved_IRQHandler,    // Reserved
        DMA_IRQHandler,         // DMA Controller
        GINT0_IRQHandler,       // GPIO Group0 Interrupt
        PIN_INT0_IRQHandler,    // PIO INT0
        PIN_INT1_IRQHandler,    // PIO INT1
        PIN_INT2_IRQHandler,    // PIO INT2
        PIN_INT3_IRQHandler,    // PIO INT3
        UTICK_IRQHandler,       // UTICK timer
        MRT_IRQHandler,         // Multi-Rate Timer
        CT32B0_IRQHandler,      // Counter Timer 0
        CT32B1_IRQHandler,      // Counter Timer 1
        CT32B2_IRQHandler,      // Counter Timer 2
        CT32B3_IRQHandler,      // Counter Timer 3
        CT32B4_IRQHandler,      // Counter Timer 4
        SCT0_IRQHandler,        // Smart Counter Timer
        UART0_IRQHandler,       // UART0
        UART1_IRQHandler,       // UART1
        UART2_IRQHandler,       // UART2
        UART3_IRQHandler,       // UART3
        I2C0_IRQHandler,        // I2C0 controller
        I2C1_IRQHandler,        // I2C1 controller
        I2C2_IRQHandler,        // I2C2 controller
        SPI0_IRQHandler,        // SPI0 controller
        SPI1_IRQHandler,        // SPI1 controller
        ADC_SEQA_IRQHandler,    // ADC SEQA
        ADC_SEQB_IRQHandler,    // ADC SEQB
        ADC_THCMP_IRQHandler,   // ADC THCMP and OVERRUN ORed
        RTC_IRQHandler,         // RTC Timer
        Reserved_IRQHandler,    // Reserved
        MAILBOX_IRQHandler,     // Mailbox

        // External Interrupts - For M4 only
        GINT1_IRQHandler,       // GPIO Group1 Interrupt
        PIN_INT4_IRQHandler,    // PIO INT4
        PIN_INT5_IRQHandler,    // PIO INT5
        PIN_INT6_IRQHandler,    // PIO INT6
        PIN_INT7_IRQHandler,    // PIO INT7
        SPI2_IRQHandler,        // SPI2 controller
        SPI3_IRQHandler,        // SPI3 controller
        0,                      // Reserved
        RIT_IRQHandler,         // RIT Timer
        Reserved41_IRQHandler,  // Reserved
        Reserved42_IRQHandler,  // Reserved
        Reserved43_IRQHandler,  // Reserved
        Reserved44_IRQHandler,  // Reserved

}; /* End of g_pfnVectors */

//*****************************************************************************
// Functions to carry out the initialization of RW and BSS data sections. These
// are written as separate functions rather than being inlined within the
// ResetISR() function in order to cope with MCUs with multiple banks of
// memory.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void data_init(unsigned int romstart, unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int *pulSrc = (unsigned int*) romstart;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = *pulSrc++;
}

__attribute__ ((section(".after_vectors")))
void bss_init(unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = 0;
}

//*****************************************************************************
// The following symbols are constructs generated by the linker, indicating
// the location of various points in the "Global Section Table". This table is
// created by the linker via the Code Red managed linker script mechanism. It
// contains the load address, execution address and length of each RW data
// section and the execution and length of each BSS (zero initialized) section.
//*****************************************************************************
extern unsigned int __data_section_table;
extern unsigned int __data_section_table_end;
extern unsigned int __bss_section_table;
extern unsigned int __bss_section_table_end;

//*****************************************************************************
// Reset entry point for your code.
// Sets up a simple runtime environment and initializes the C/C++
// library.
//*****************************************************************************

#if defined (__MULTICORE_MASTER)
//#define  cpu_ctrl 0x40000300
//#define coproc_boot	0x40000304
//#define set coproc_stack	0x40000308
__attribute__ ((naked, section(".after_vectors.reset")))
void ResetISR(void) {
    asm volatile(
        ".set   cpu_ctrl,       0x40000300\t\n"
        ".set   coproc_boot,    0x40000304\t\n"
        ".set   coproc_stack,   0x40000308\t\n"
        "MOVS   R5, #1\t\n"
        "LDR    R0, =0xE000ED00\t\n"
        "LDR    R1, [R0]\t\n"           // READ CPUID register
        "LDR    R2,=0x410CC601\t\n"     // CM0 R0p1 identifier
        "EORS   R1,R1,R2\t\n"           // XOR to see if we are C0
        "LDR    R3, =cpu_ctrl\t\n"      // get address of CPU_CTRL
        "LDR    R1,[R3]\t\n"            // read cpu_ctrl reg into R1
        "BEQ.N  cm0_boot\t\n"
    "cm4_boot:\t\n"
        "LDR    R0,=coproc_boot\t\n"    // coproc boot address
        "LDR    R0,[R0]\t\n"            // get address to branch to
        "MOVS   R0,R0\t\n"              // Check if 0
        "BEQ.N  check_master_m4\t\n"    // if zero in boot reg, we just branch to  real reset
        "BX     R0\t\n"                 // otherwise, we branch to boot address
    "commonboot:\t\n"
        "LDR    R0, =ResetISR2\t\n"     // Jump to 'real' reset handler
        "BX     R0\t\n"
    "cm0_boot:\t\n"
        "LDR    R0,=coproc_boot\t\n"    // coproc boot address
        "LDR    R0,[R0]\t\n"            // get address to branch to
        "MOVS   R0,R0\t\n"              // Check if 0
        "BEQ.N  check_master_m0\t\n"    // if zero in boot reg, we just branch to  real reset
        "LDR    R1,=coproc_stack\t\n"   // pickup coprocesor stackpointer (from syscon CPSTACK)
        "LDR    R1,[R1]\t\n"
        "MOV    SP,R1\t\n"
        "BX     R0\t\n"                 // goto boot address
    "check_master_m0:\t\n"
        "ANDS   R1,R1,R5\t\n"           // bit test bit0
        "BEQ.N  commonboot\t\n"         // if we get 0, that means we are masters
        "B.N    goto_sleep_pending_reset\t\n"   // Otherwise, there is no startup vector for slave, so we go to sleep
    "check_master_m4:\t\n"
        "ANDS   R1,R1,R5\t\n"           // bit test bit0
        "BNE.N  commonboot\t\n"         // if we get 1, that means we are masters
    "goto_sleep_pending_reset:\t\n"
        "MOV     SP,R5\t\n"             // load 0x1 into SP so that any stacking (eg on NMI) will not cause us to wakeup
            // and write to uninitialised Stack area (instead it will LOCK us up before we cause damage)
            // this code should only be reached if debugger bypassed ROM or we changed master without giving
            // correct start address, the only way out of this is through a debugger change of SP and PC
    "sleepo:\t\n"
        "WFI\t\n"                       // go to sleep
        "B.N    sleepo\t\n"
    );
}


__attribute__ ((section(".after_vectors.reset")))
void ResetISR2(void) {

#else
__attribute__ ((section(".after_vectors.reset")))
void ResetISR(void) {
#endif

    // If this is not the CM0+ core...
#if !defined (CORE_M0PLUS)
    // If this is not a slave project...
#if !defined (__MULTICORE_M0SLAVE) && \
    !defined (__MULTICORE_M4SLAVE)
    // Optionally enable RAM banks that may be off by default at reset
#if !defined (DONT_ENABLE_DISABLED_RAMBANKS)
    volatile unsigned int *SYSCON_SYSAHBCLKCTRL0 = (unsigned int *) 0x400000c0;
    // Ensure that SRAM2(4) bit in SYSAHBCLKCTRL0 are set
    *SYSCON_SYSAHBCLKCTRL0 |= (1 << 4);
#endif
#endif
#endif

    //
    // Copy the data sections from flash to SRAM.
    //
    unsigned int LoadAddr, ExeAddr, SectionLen;
    unsigned int *SectionTableAddr;

    // Load base address of Global Section Table
    SectionTableAddr = &__data_section_table;

    // Copy the data sections from flash to SRAM.
    while (SectionTableAddr < &__data_section_table_end) {
        LoadAddr = *SectionTableAddr++;
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        data_init(LoadAddr, ExeAddr, SectionLen);
    }
    // At this point, SectionTableAddr = &__bss_section_table;
    // Zero fill the bss segment
    while (SectionTableAddr < &__bss_section_table_end) {
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        bss_init(ExeAddr, SectionLen);
    }

#if !defined (__USE_LPCOPEN)
// LPCOpen init code deals with FP and VTOR initialisation
#if defined (__VFP_FP__) && !defined (__SOFTFP__)
    /*
     * Code to enable the Cortex-M4 FPU only included
     * if appropriate build options have been selected.
     * Code taken from Section 7.1, Cortex-M4 TRM (DDI0439C)
     */
    // CPACR is located at address 0xE000ED88
    asm("LDR.W R0, =0xE000ED88");
    // Read CPACR
    asm("LDR R1, [R0]");
    // Set bits 20-23 to enable CP10 and CP11 coprocessors
    asm(" ORR R1, R1, #(0xF << 20)");
    // Write back the modified value to the CPACR
    asm("STR R1, [R0]");
#endif // (__VFP_FP__) && !(__SOFTFP__)
    // ******************************
    // Check to see if we are running the code from a non-zero
    // address (eg RAM, external flash), in which case we need
    // to modify the VTOR register to tell the CPU that the
    // vector table is located at a non-0x0 address.

    // Note that we do not use the CMSIS register access mechanism,
    // as there is no guarantee that the project has been configured
    // to use CMSIS.
    unsigned int * pSCB_VTOR = (unsigned int *) 0xE000ED08;
    if ((unsigned int *) g_pfnVectors != (unsigned int *) 0x00000000) {
        // CMSIS : SCB->VTOR = <address of vector table>
        *pSCB_VTOR = (unsigned int) g_pfnVectors;
    }
#endif
#if defined (__USE_CMSIS) || defined (__USE_LPCOPEN)
    SystemInit();
#endif

#if defined (__cplusplus)
    //
    // Call C++ library initialisation
    //
    __libc_init_array();
#endif

#if defined (__REDLIB__)
    // Call the Redlib library, which in turn calls main()
    __main();
#else
    main();
#endif

    //
    // main() shouldn't return, but if it does, we'll just enter an infinite loop
    //
    while (1) {
        ;
    }
}

//*****************************************************************************
// Default exception handlers. Override the ones here by defining your own
// handler routines in your application code.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void NMI_Handler(void) {
    while (1) {
    }
}

__attribute__ ((section(".after_vectors")))
void HardFault_Handler(void) {
    while (1) {
    }
}

__attribute__ ((section(".after_vectors")))
void SVC_Handler(void) {
    while (1) {
    }
}

__attribute__ ((section(".after_vectors")))
void PendSV_Handler(void) {
    while (1) {
    }
}

__attribute__ ((section(".after_vectors")))
void SysTick_Handler(void) {
    while (1) {
    }
}

//*****************************************************************************
//
// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.
//
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void IntDefaultHandler(void) {
    while (1) {
    }
}

