/*
 * Copyright (c) 2006 - 2021, RT-Thread Development Team
 * Copyright (c) 2014 - 2020 Xilinx, Inc.  All rights reserved.
 * Copyright (c) 2021 WangHuachen.  All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-19     WangHuachen  first version
 * 2021-05-10     WangHuachen  add more functions
 */

#include <stdint.h>
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

void Xil_DCacheEnable(void);
void Xil_DCacheDisable(void);
void Xil_DCacheInvalidate(void);
void Xil_DCacheInvalidateRange(INTPTR adr, u32 len);
void Xil_DCacheFlush(void);
void Xil_DCacheFlushRange(INTPTR adr, u32 len);
void Xil_DCacheInvalidateLine(INTPTR adr);
void Xil_DCacheFlushLine(INTPTR adr);
void Xil_DCacheStoreLine(INTPTR adr);
void Xil_ICacheEnable(void);
void Xil_ICacheDisable(void);
void Xil_ICacheInvalidate(void);
void Xil_ICacheInvalidateRange(INTPTR adr, u32 len);
void Xil_ICacheInvalidateLine(INTPTR adr);

void Xil_DCacheEnable(void)
{
    register u32 CtrlReg;

    /* enable caches only if they are disabled */
#if defined (__GNUC__)
    CtrlReg = mfcp(XREG_CP15_SYS_CONTROL);
#elif defined (__ICCARM__)
    mfcp(XREG_CP15_SYS_CONTROL, CtrlReg);
#endif
    if ((CtrlReg & XREG_CP15_CONTROL_C_BIT) == 0x00000000U)
    {
        /* invalidate the Data cache */
        Xil_DCacheInvalidate();

        /* enable the Data cache */
        CtrlReg |= (XREG_CP15_CONTROL_C_BIT);

        mtcp(XREG_CP15_SYS_CONTROL, CtrlReg);
    }
}

void Xil_DCacheDisable(void)
{
    register u32 CtrlReg;

    /* clean and invalidate the Data cache */
    Xil_DCacheFlush();

    /* disable the Data cache */
#if defined (__GNUC__)
    CtrlReg = mfcp(XREG_CP15_SYS_CONTROL);
#elif defined (__ICCARM__)
    mfcp(XREG_CP15_SYS_CONTROL, CtrlReg);
#endif

    CtrlReg &= ~(XREG_CP15_CONTROL_C_BIT);

    mtcp(XREG_CP15_SYS_CONTROL, CtrlReg);
}

void Xil_DCacheInvalidate(void)
{
    u32 currmask;

    currmask = mfcpsr();
    mtcpsr(currmask | IRQ_FIQ_MASK);

    mtcp(XREG_CP15_CACHE_SIZE_SEL, 0);

    /*invalidate all D cache*/
    mtcp(XREG_CP15_INVAL_DC_ALL, 0);

    mtcpsr(currmask);
}

void Xil_DCacheInvalidateLine(INTPTR adr)
{
    u32 currmask;

    currmask = mfcpsr();
    mtcpsr(currmask | IRQ_FIQ_MASK);

    mtcp(XREG_CP15_CACHE_SIZE_SEL, 0);
    mtcp(XREG_CP15_INVAL_DC_LINE_MVA_POC, (adr & (~0x1F)));

    /* Wait for invalidate to complete */
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

    if (len != 0U)
    {
        end = tempadr + len;
        tempend = end;
        /* Select L1 Data cache in CSSR */
        mtcp(XREG_CP15_CACHE_SIZE_SEL, 0U);

        if ((tempadr & (cacheline - 1U)) != 0U)
        {
            tempadr &= (~(cacheline - 1U));

            Xil_DCacheFlushLine(tempadr);
        }
        if ((tempend & (cacheline - 1U)) != 0U)
        {
            tempend &= (~(cacheline - 1U));

            Xil_DCacheFlushLine(tempend);
        }

        while (tempadr < tempend)
        {

            /* Invalidate Data cache line */
            asm_inval_dc_line_mva_poc(tempadr);

            tempadr += cacheline;
        }
    }

    dsb();
    mtcpsr(currmask);
}

void Xil_DCacheFlush(void)
{
    register u32 CsidReg, C7Reg;
    u32 CacheSize, LineSize, NumWays;
    u32 Way, WayIndex, Set, SetIndex, NumSet;
    u32 currmask;

    currmask = mfcpsr();
    mtcpsr(currmask | IRQ_FIQ_MASK);

    /* Select cache level 0 and D cache in CSSR */
    mtcp(XREG_CP15_CACHE_SIZE_SEL, 0);

#if defined (__GNUC__)
    CsidReg = mfcp(XREG_CP15_CACHE_SIZE_ID);
#elif defined (__ICCARM__)
    mfcp(XREG_CP15_CACHE_SIZE_ID, CsidReg);
#endif
    /* Determine Cache Size */

    CacheSize = (CsidReg >> 13U) & 0x000001FFU;
    CacheSize += 0x00000001U;
    CacheSize *= (u32)128;    /* to get number of bytes */

    /* Number of Ways */
    NumWays = (CsidReg & 0x000003ffU) >> 3U;
    NumWays += 0x00000001U;

    /* Get the cacheline size, way size, index size from csidr */
    LineSize = (CsidReg & 0x00000007U) + 0x00000004U;

    NumSet = CacheSize / NumWays;
    NumSet /= (0x00000001U << LineSize);

    Way = 0U;
    Set = 0U;

    /* Invalidate all the cachelines */
    for (WayIndex = 0U; WayIndex < NumWays; WayIndex++)
    {
        for (SetIndex = 0U; SetIndex < NumSet; SetIndex++)
        {
            C7Reg = Way | Set;
            /* Flush by Set/Way */
            asm_clean_inval_dc_line_sw(C7Reg);

            Set += (0x00000001U << LineSize);
        }
        Set = 0U;
        Way += 0x40000000U;
    }

    /* Wait for flush to complete */
    dsb();
    mtcpsr(currmask);

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

void Xil_DCacheFlushRange(INTPTR adr, u32 len)
{
    u32 LocalAddr = adr;
    const u32 cacheline = 32U;
    u32 end;
    u32 currmask;

    currmask = mfcpsr();
    mtcpsr(currmask | IRQ_FIQ_MASK);

    if (len != 0x00000000U)
    {
        /* Back the starting address up to the start of a cache line
         * perform cache operations until adr+len
         */
        end = LocalAddr + len;
        LocalAddr &= ~(cacheline - 1U);

        while (LocalAddr < end)
        {
            /* Flush Data cache line */
            asm_clean_inval_dc_line_mva_poc(LocalAddr);

            LocalAddr += cacheline;
        }
    }
    dsb();
    mtcpsr(currmask);
}

void Xil_DCacheStoreLine(INTPTR adr)
{
    u32 currmask;

    currmask = mfcpsr();
    mtcpsr(currmask | IRQ_FIQ_MASK);

    mtcp(XREG_CP15_CACHE_SIZE_SEL, 0);
    mtcp(XREG_CP15_CLEAN_DC_LINE_MVA_POC, (adr & (~0x1F)));

    /* Wait for store to complete */
    dsb();
    isb();

    mtcpsr(currmask);
}

void Xil_ICacheEnable(void)
{
    register u32 CtrlReg;

    /* enable caches only if they are disabled */
#if defined (__GNUC__)
    CtrlReg = mfcp(XREG_CP15_SYS_CONTROL);
#elif defined (__ICCARM__)
    mfcp(XREG_CP15_SYS_CONTROL, CtrlReg);
#endif
    if ((CtrlReg & XREG_CP15_CONTROL_I_BIT) == 0x00000000U)
    {
        /* invalidate the instruction cache */
        mtcp(XREG_CP15_INVAL_IC_POU, 0);

        /* enable the instruction cache */
        CtrlReg |= (XREG_CP15_CONTROL_I_BIT);

        mtcp(XREG_CP15_SYS_CONTROL, CtrlReg);
    }
}

void Xil_ICacheDisable(void)
{
    register u32 CtrlReg;

    dsb();

    /* invalidate the instruction cache */
    mtcp(XREG_CP15_INVAL_IC_POU, 0);

    /* disable the instruction cache */
#if defined (__GNUC__)
    CtrlReg = mfcp(XREG_CP15_SYS_CONTROL);
#elif defined (__ICCARM__)
    mfcp(XREG_CP15_SYS_CONTROL, CtrlReg);
#endif

    CtrlReg &= ~(XREG_CP15_CONTROL_I_BIT);

    mtcp(XREG_CP15_SYS_CONTROL, CtrlReg);
}

void Xil_ICacheInvalidate(void)
{
    u32 currmask;

    currmask = mfcpsr();
    mtcpsr(currmask | IRQ_FIQ_MASK);

    mtcp(XREG_CP15_CACHE_SIZE_SEL, 1);

    /* invalidate the instruction cache */
    mtcp(XREG_CP15_INVAL_IC_POU, 0);

    /* Wait for invalidate to complete */
    dsb();
    mtcpsr(currmask);
}

void Xil_ICacheInvalidateLine(INTPTR adr)
{
    u32 currmask;

    currmask = mfcpsr();
    mtcpsr(currmask | IRQ_FIQ_MASK);

    mtcp(XREG_CP15_CACHE_SIZE_SEL, 1);
    mtcp(XREG_CP15_INVAL_IC_LINE_MVA_POU, (adr & (~0x1F)));

    /* Wait for invalidate to complete */
    dsb();
    mtcpsr(currmask);
}

void Xil_ICacheInvalidateRange(INTPTR adr, u32 len)
{
    u32 LocalAddr = adr;
    const u32 cacheline = 32U;
    u32 end;
    u32 currmask;

    currmask = mfcpsr();
    mtcpsr(currmask | IRQ_FIQ_MASK);
    if (len != 0x00000000U)
    {
        /* Back the starting address up to the start of a cache line
         * perform cache operations until adr+len
         */
        end = LocalAddr + len;
        LocalAddr = LocalAddr & ~(cacheline - 1U);

        /* Select cache L0 I-cache in CSSR */
        mtcp(XREG_CP15_CACHE_SIZE_SEL, 1U);

        while (LocalAddr < end)
        {

            /* Invalidate L1 I-cache line */
            asm_inval_ic_line_mva_pou(LocalAddr);

            LocalAddr += cacheline;
        }
    }

    /* Wait for invalidate to complete */
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
    mfcp(XREG_CP15_SYS_CONTROL, CtrlReg);
#endif
    return CtrlReg & XREG_CP15_CONTROL_I_BIT;
}

rt_base_t rt_hw_cpu_dcache_status(void)
{
    register u32 CtrlReg;
#if defined (__GNUC__)
    CtrlReg = mfcp(XREG_CP15_SYS_CONTROL);
#elif defined (__ICCARM__)
    mfcp(XREG_CP15_SYS_CONTROL, CtrlReg);
#endif
    return CtrlReg & XREG_CP15_CONTROL_C_BIT;
}
