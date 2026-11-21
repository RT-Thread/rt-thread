/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Must match avaota-f2-e907/board/amp_mbox.h slot layout.
 *
 * C907 stores were invisible to E907 when only DE-off / call-all was used.
 * Clean the line by VA (c906+c908 encodings) after each store; invalidate
 * before each load. Avoid l2cache.iall (hangs).
 */

#ifndef AMP_MBOX_H__
#define AMP_MBOX_H__

#include <stdint.h>

#define AMP_SLOT_BASE           0x41000000U
#define AMP_SLOT_C907           (AMP_SLOT_BASE + 0x00U)
#define AMP_SLOT_C907_REPLY     (AMP_SLOT_BASE + 0x04U)
#define AMP_SLOT_E907           (AMP_SLOT_BASE + 0x20U)
#define AMP_SLOT_E907_STEP      (AMP_SLOT_BASE + 0x24U)
#define AMP_SLOT_PING_REQ       (AMP_SLOT_BASE + 0x40U)

#define AMP_E2C_SEQ             (AMP_SLOT_BASE + 0x80U)
#define AMP_E2C_DATA            (AMP_SLOT_BASE + 0x84U)
#define AMP_E2C_ACK             (AMP_SLOT_BASE + 0x88U)
#define AMP_C2E_SEQ             (AMP_SLOT_BASE + 0x90U)
#define AMP_C2E_DATA            (AMP_SLOT_BASE + 0x94U)
#define AMP_C2E_ACK             (AMP_SLOT_BASE + 0x98U)
#define AMP_MSGBOX_PROBE        (AMP_SLOT_BASE + 0xA0U)

#define AMP_MAGIC_C907          0xC907A11CU
#define AMP_MAGIC_E907          0xE907A11CU
#define AMP_PING_REQ            0xA11C0001U

#define AMP_MXSTATUS            0x7c0U
#define AMP_MXSTATUS_THEADISAEE (1UL << 22)

/* Real V861 MSGBOX views (Tina DTB); legacy 0x03003000 is dead. */
#define AMP_MSGBOX_BASE         0x06020000U
#define AMP_MSGBOX_VER          (AMP_MSGBOX_BASE + 0x10U)

static inline void amp_fence(void)
{
    __asm__ volatile("fence ow, ow" ::: "memory");
}

static inline void amp_enable_thead_isa(void)
{
    unsigned long v;
    __asm__ volatile("csrr %0, %1" : "=r"(v) : "i"(AMP_MXSTATUS));
    v |= AMP_MXSTATUS_THEADISAEE;
    __asm__ volatile("csrw %0, %1" :: "i"(AMP_MXSTATUS), "r"(v) : "memory");
}

static inline void amp_sync(void)
{
    __asm__ volatile(".long 0x0180000b" ::: "memory"); /* sync */
}

/* Clean D-cache line by VA: try c906 (rs2=x4) and c908 (rs2=x5) encodings. */
static inline void amp_dcache_clean_va(uint32_t addr)
{
    amp_enable_thead_isa();
    __asm__ volatile(".insn r 0x0b, 0, 1, x0, %0, x4" :: "r"(addr) : "memory");
    __asm__ volatile(".insn r 0x0b, 0, 1, x0, %0, x5" :: "r"(addr) : "memory");
    amp_sync();
    amp_fence();
}

static inline void amp_dcache_inv_va(uint32_t addr)
{
    amp_enable_thead_isa();
    __asm__ volatile(".insn r 0x0b, 0, 1, x0, %0, x6" :: "r"(addr) : "memory"); /* iva */
    __asm__ volatile(".insn r 0x0b, 0, 1, x0, %0, x5" :: "r"(addr) : "memory"); /* c906 may map differently */
    amp_sync();
    amp_fence();
}

static inline void amp_coherent_begin(void)
{
    amp_enable_thead_isa();
    __asm__ volatile(".long 0x0010000b" ::: "memory"); /* dcache.call */
    amp_sync();
    amp_fence();
}

static inline uint32_t amp_read(uint32_t addr)
{
    amp_dcache_inv_va(addr);
    return *(volatile uint32_t *)addr;
}

static inline void amp_write(uint32_t addr, uint32_t value)
{
    *(volatile uint32_t *)addr = value;
    amp_fence();
    amp_dcache_clean_va(addr);
    __asm__ volatile(".long 0x0010000b" ::: "memory"); /* dcache.call */
    amp_sync();
    amp_fence();
}

#endif
