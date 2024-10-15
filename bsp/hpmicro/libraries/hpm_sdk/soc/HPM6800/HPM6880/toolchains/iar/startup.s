/*
 * Copyright (c) 2023-2024 HPMicro
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "hpm_csr_regs.h"



    MODULE ?startup

    /* Forward declaration of sections */
    SECTION CSTACK:DATA:NOROOT(3)
    SECTION SAFESTACK:DATA:NOROOT(3)
    SECTION `.vector_table`:CODE:NOROOT(3)

    EXTERN _clean_up
    EXTERN reset_handler
    EXTERN __low_level_init
    EXTERN irq_handler_trap
    EXTERN __iar_static_base$$GPREL
    EXTERN __iar_data_init2
    EXTERN l1c_ic_disable
    EXTERN l1c_ic_enable
    EXTERN l1c_dc_invalidate_all
    EXTERN l1c_dc_enable
    EXTERN l1c_dc_disable
    // --------------------------------------------------

    SECTION `.startup`:CODE:ROOT(2)
    EXTERN __iar_program_start
    PUBLIC _start

    EXTERN reset_handler
_start:
__iar_cstart_init_gp:
    .option push
    .option norelax
    /* Initialize global pointer */
    la gp, __iar_static_base$$GPREL
    .option pop

    /* reset mstatus to 0 */
    csrrw x0, mstatus, x0

#ifdef __riscv_flen
__iar_cstart_init_fpu:
    /* Enable FPU */
    li t0, CSR_MSTATUS_FS_MASK
    csrrs t0, mstatus, t0
    /* Initialize FCSR */
    fscsr zero
#endif

#ifdef INIT_EXT_RAM_FOR_DATA
    EXTERN _init_ext_ram
__iar_cstart_init_ext_ram:
    la t0, SFE(SAFESTACK)
    mv sp, t0
    call _init_ext_ram
#endif

__iar_cstart_init_stack:
    /* Initialize Stack pointer */
    la t0, SFE(CSTACK)
    mv sp, t0

#ifdef __nds_execit
__iar_cstart_init_uitb:
    EXTERN  `.exec.itable$$Base`
    la      a0, `.exec.itable$$Base`
    csrw    0x800, a0
#endif

#ifdef CONFIG_NOT_ENABLE_ICACHE
    call    l1c_ic_disable
#else
    call    l1c_ic_enable
#endif
#ifdef CONFIG_NOT_ENABLE_DCACHE
    call    l1c_dc_invalidate_all
    call    l1c_dc_disable
#else
    call    l1c_dc_enable
    call    l1c_dc_invalidate_all
#endif

    /* Call IAR low-levle API to initialize BSS, RW Data, RAM Function, etc */
    call __low_level_init
    call __iar_data_init2
    fence.i

#ifndef NO_CLEANUP_AT_START
    /* clean up */
    call _clean_up
#endif


__iar_cstart_init_mvec:
 #if defined(CONFIG_FREERTOS) && CONFIG_FREERTOS
    EXTERN freertos_risc_v_trap_handler
    #define HANDLER_TRAP freertos_risc_v_trap_handler

    /* Use mscratch to store isr level */
    csrw mscratch, x0
#elif defined(CONFIG_UCOS_III) && CONFIG_UCOS_III
    EXTERN ucos_risc_v_trap_handler
    #define HANDLER_TRAP ucos_risc_v_trap_handler

    /* Use mscratch to store isr level */
    csrw mscratch, x0
#elif defined(CONFIG_THREADX) && CONFIG_THREADX
    EXTERN tx_risc_v_trap_handler
    #define HANDLER_TRAP tx_risc_v_trap_handler
    #define HANDLER_S_TRAP tx_risc_v_trap_handler

    /* Use mscratch to store isr level */
    csrw mscratch, x0
#elif defined(CONFIG_RTTHREAD) && CONFIG_RTTHREAD
    EXTERN rtt_risc_v_trap_handler
    #define HANDLER_TRAP rtt_risc_v_trap_handler
    #define HANDLER_S_TRAP rtt_risc_v_trap_handler

    /* Use mscratch to store isr level */
    csrw mscratch, x0
#else
    #define HANDLER_TRAP irq_handler_trap
#endif

#if !defined(USE_NONVECTOR_MODE) || (USE_NONVECTOR_MODE == 0)
    /* Initial machine trap-vector Base */
    la t0, SFB(`.vector_table`)
    csrw mtvec, t0

    /* Enable vectored external PLIC interrupt */
    csrsi CSR_MMISC_CTL, 2
#else
    /* Initial machine trap-vector Base */
    la t0, HANDLER_TRAP
    csrw mtvec, t0

    /* Disable vectored external PLIC interrupt */
    csrci CSR_MMISC_CTL, 2
#endif

    /* Jump to reset handler once all settings have done */
    call reset_handler

__iar_cstart_exit
    j __iar_cstart_exit

#include "../vectors.h"
