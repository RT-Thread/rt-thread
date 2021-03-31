/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-19     WangHuachen  first version
 */
#include <rthw.h>
#include <rtdef.h>

#include "xpseudo_asm_gcc.h"
#include "xreg_cortexr5.h"

#define IRQ_FIQ_MASK 0xC0   /* Mask IRQ and FIQ interrupts in cpsr */

typedef intptr_t INTPTR;
typedef rt_uint32_t u32;

#if defined (__GNUC__)
#define asm_inval_dc_line_mva_poc(param) __asm__ __volatile__("mcr " \
        XREG_CP15_INVAL_DC_LINE_MVA_POC :: "r" (param))

#define asm_clean_inval_dc_line_sw(param) __asm__ __volatile__("mcr " \
        XREG_CP15_CLEAN_INVAL_DC_LINE_SW :: "r" (param))

#define asm_clean_inval_dc_line_mva_poc(param) __asm__ __volatile__("mcr " \
        XREG_CP15_CLEAN_INVAL_DC_LINE_MVA_POC :: "r" (param))

#define asm_inval_ic_line_mva_pou(param) __asm__ __volatile__("mcr " \
        XREG_CP15_INVAL_IC_LINE_MVA_POU :: "r" (param))
#elif defined (__ICCARM__)
#define asm_inval_dc_line_mva_poc(param) __asm volatile("mcr " \
        XREG_CP15_INVAL_DC_LINE_MVA_POC :: "r" (param))

#define asm_clean_inval_dc_line_sw(param) __asm volatile("mcr " \
        XREG_CP15_CLEAN_INVAL_DC_LINE_SW :: "r" (param))

#define asm_clean_inval_dc_line_mva_poc(param) __asm volatile("mcr " \
        XREG_CP15_CLEAN_INVAL_DC_LINE_MVA_POC :: "r" (param))

#define asm_inval_ic_line_mva_pou(param) __asm volatile("mcr " \
        XREG_CP15_INVAL_IC_LINE_MVA_POU :: "r" (param))
#endif


void Xil_ICacheInvalidateRange(INTPTR adr, u32 len)
{
    u32 LocalAddr = adr;
    const u32 cacheline = 32U;
    u32 end;
    u32 currmask;

    currmask = mfcpsr();
    mtcpsr(currmask | IRQ_FIQ_MASK);
    if (len != 0x00000000U) {
        /* Back the starting address up to the start of a cache line
         * perform cache operations until adr+len
         */
        end = LocalAddr + len;
        LocalAddr = LocalAddr & ~(cacheline - 1U);

        /* Select cache L0 I-cache in CSSR */
        mtcp(XREG_CP15_CACHE_SIZE_SEL, 1U);

        while (LocalAddr < end) {

            /* Invalidate L1 I-cache line */
            asm_inval_ic_line_mva_pou(LocalAddr);

            LocalAddr += cacheline;
        }
    }

    /* Wait for invalidate to complete */
    dsb();
    mtcpsr(currmask);
}

void Xil_DCacheFlushLine(INTPTR adr)
{
    u32 currmask;

    currmask = mfcpsr();
    mtcpsr(currmask | IRQ_FIQ_MASK);

    mtcp(XREG_CP15_CACHE_SIZE_SEL, 0);

    mtcp(XREG_CP15_CLEAN_INVAL_DC_LINE_MVA_POC, (adr & (~0x1F)));

        /* Wait for flush to complete */
    dsb();
    mtcpsr(currmask);
}

void Xil_DCacheInvalidateRange(INTPTR adr, u32 len)
{
    const u32 cacheline = 32U;
    u32 end;
    u32 tempadr = adr;
    u32 tempend;
    u32 currmask;

    currmask = mfcpsr();
    mtcpsr(currmask | IRQ_FIQ_MASK);

    if (len != 0U) {
        end = tempadr + len;
        tempend = end;
        /* Select L1 Data cache in CSSR */
        mtcp(XREG_CP15_CACHE_SIZE_SEL, 0U);

        if ((tempadr & (cacheline-1U)) != 0U) {
            tempadr &= (~(cacheline - 1U));

            Xil_DCacheFlushLine(tempadr);
        }
        if ((tempend & (cacheline-1U)) != 0U) {
            tempend &= (~(cacheline - 1U));

            Xil_DCacheFlushLine(tempend);
        }

        while (tempadr < tempend) {

        /* Invalidate Data cache line */
        asm_inval_dc_line_mva_poc(tempadr);

        tempadr += cacheline;
        }
    }

    dsb();
    mtcpsr(currmask);
}

void Xil_DCacheFlushRange(INTPTR adr, u32 len)
{
    u32 LocalAddr = adr;
    const u32 cacheline = 32U;
    u32 end;
    u32 currmask;

    currmask = mfcpsr();
    mtcpsr(currmask | IRQ_FIQ_MASK);

    if (len != 0x00000000U) {
        /* Back the starting address up to the start of a cache line
         * perform cache operations until adr+len
         */
        end = LocalAddr + len;
        LocalAddr &= ~(cacheline - 1U);

        while (LocalAddr < end) {
            /* Flush Data cache line */
            asm_clean_inval_dc_line_mva_poc(LocalAddr);

            LocalAddr += cacheline;
        }
    }
    dsb();
    mtcpsr(currmask);
}

void rt_hw_cpu_icache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_INVALIDATE)
        Xil_ICacheInvalidateRange((INTPTR)addr, size);
}

void rt_hw_cpu_dcache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_FLUSH)
        Xil_DCacheFlushRange((intptr_t)addr, size);
    else if (ops == RT_HW_CACHE_INVALIDATE)
        Xil_DCacheInvalidateRange((intptr_t)addr, size);
}

rt_base_t rt_hw_cpu_icache_status(void)
{
    register u32 CtrlReg;
#if defined (__GNUC__)
    CtrlReg = mfcp(XREG_CP15_SYS_CONTROL);
#elif defined (__ICCARM__)
     mfcp(XREG_CP15_SYS_CONTROL,CtrlReg);
#endif
    return CtrlReg & XREG_CP15_CONTROL_I_BIT;
}

rt_base_t rt_hw_cpu_dcache_status(void)
{
    register u32 CtrlReg;
#if defined (__GNUC__)
    CtrlReg = mfcp(XREG_CP15_SYS_CONTROL);
#elif defined (__ICCARM__)
     mfcp(XREG_CP15_SYS_CONTROL,CtrlReg);
#endif
    return CtrlReg & XREG_CP15_CONTROL_C_BIT;
}
