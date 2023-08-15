/*
 * Copyright (c) 2021-2023 HPMicro
 *
 *
 */

#include "hpm_common.h"
#include "hpm_soc.h"
#include "hpm_l1c_drv.h"
#include <rtthread.h>

void system_init(void);

extern int entry(void);

extern void __libc_init_array(void);
extern void __libc_fini_array(void);

void system_init(void)
{
    disable_global_irq(CSR_MSTATUS_MIE_MASK);
    disable_irq_from_intc();
    enable_irq_from_intc();
    enable_global_irq(CSR_MSTATUS_MIE_MASK);
#ifndef CONFIG_NOT_ENABLE_ICACHE
    l1c_ic_enable();
#endif
#ifndef CONFIG_NOT_ENABLE_DCACHE
    l1c_dc_enable();
#endif
}

__attribute__((weak)) void c_startup(void)
{
    uint32_t i, size;
#ifdef FLASH_XIP
    extern uint8_t __vector_ram_start__[], __vector_ram_end__[], __vector_load_addr__[];
    size = __vector_ram_end__ - __vector_ram_start__;
    for (i = 0; i < size; i++) {
        *(__vector_ram_start__ + i) = *(__vector_load_addr__ + i);
    }
#endif

    extern uint8_t __etext[];
    extern uint8_t __bss_start__[], __bss_end__[];
    extern uint8_t __tbss_start__[], __tbss_end__[];
    extern uint8_t __tdata_start__[], __tdata_end__[];
    extern uint8_t __data_start__[], __data_end__[];
    extern uint8_t __noncacheable_bss_start__[], __noncacheable_bss_end__[];
    extern uint8_t __ramfunc_start__[], __ramfunc_end__[];
    extern uint8_t __noncacheable_init_start__[], __noncacheable_init_end__[];

    /* tbss section */
    size = __tbss_end__ - __tbss_start__;
    for (i = 0; i < size; i++) {
        *(__tbss_start__ + i) = 0;
    }

    /* bss section */
    size = __bss_end__ - __bss_start__;
    for (i = 0; i < size; i++) {
        *(__bss_start__ + i) = 0;
    }

    /* noncacheable bss section */
    size = __noncacheable_bss_end__ - __noncacheable_bss_start__;
    for (i = 0; i < size; i++) {
        *(__noncacheable_bss_start__ + i) = 0;
    }

    /* tdata section LMA: etext */
    size = __tdata_end__ - __tdata_start__;
    for (i = 0; i < size; i++) {
        *(__tdata_start__ + i) = *(__etext + i);
    }

    /* data section LMA: etext */
    size = __data_end__ - __data_start__;
    for (i = 0; i < size; i++) {
        *(__data_start__ + i) = *(__etext + (__tdata_end__ - __tdata_start__) + i);
    }

    /* ramfunc section LMA: etext + data length */
    size = __ramfunc_end__ - __ramfunc_start__;
    for (i = 0; i < size; i++) {
        *(__ramfunc_start__ + i) = *(__etext + (__data_end__ - __tdata_start__) + i);
    }

    /* noncacheable init section LMA: etext + data length + ramfunc length */
    size = __noncacheable_init_end__ - __noncacheable_init_start__;
    for (i = 0; i < size; i++) {
        *(__noncacheable_init_start__ + i) = *(__etext + (__data_end__ - __tdata_start__) + (__ramfunc_end__ - __ramfunc_start__) + i);
    }
}

__attribute__((weak)) int main(void)
{
    while(1);
}

void reset_handler(void)
{
    /**
     * Disable preemptive interrupt
     */
    HPM_PLIC->FEATURE = 0;
    /*
     * Initialize LMA/VMA sections.
     * Relocation for any sections that need to be copied from LMA to VMA.
     */
    c_startup();

    /* Call platform specific hardware initialization */
    system_init();

    /* Do global constructors */
    __libc_init_array();



    /* Entry function */
    entry();
}


__attribute__((weak)) void _init()
{
}
