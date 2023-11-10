/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: faarch64.h
 * Date: 2022-02-10 14:53:41
 * LastEditTime: 2022-02-17 17:32:07
 * Description:  This file is for system register related macro definition functions
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe     2021/7/3     first release
 */

#ifndef FAARCH64_H
#define FAARCH64_H

#include <stdint.h>
#include "ftypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* CurrentEL, Current Exception Level */
#define CURRENT_EL_MASK 0x3
#define CURRENT_EL_SHIFT 2

/* DAIF, Interrupt Mask Bits */
#define DAIF_DBG_BIT (1 << 3) /* Debug mask bit */
#define DAIF_ABT_BIT (1 << 2) /* Asynchronous abort mask bit */
#define DAIF_IRQ_BIT (1 << 1) /* IRQ mask bit */
#define DAIF_FIQ_BIT (1 << 0) /* FIQ mask bit */

/*
 * Interrupt flags
 */
#define AARCH64_DAIF_FIQ (1) /* FIQ */
#define AARCH64_DAIF_IRQ (2) /* IRQ */

/* Timer */
#define CNTV_CTL_ENABLE (1 << 0)  /* Enables the timer */
#define CNTV_CTL_IMASK (1 << 1)   /* Timer interrupt mask bit */
#define CNTV_CTL_ISTATUS (1 << 2) /* The status of the timer interrupt. This bit is read-only */

/* AArch64 Memory Model Feature Register 0  */

#define ID_AA64MMFR0_EL1_4K_NO_SURPOORT (0xFULL << 28)

/*
 * AArch64 SPSR
*/
#define AARCH64_SPSR_EL3h 0b1101
#define AARCH64_SPSR_EL3t 0b1100
#define AARCH64_SPSR_EL2h 0b1001
#define AARCH64_SPSR_EL2t 0b1000
#define AARCH64_SPSR_EL1h 0b0101
#define AARCH64_SPSR_EL1t 0b0100
#define AARCH64_SPSR_EL0t 0b0000
#define AARCH64_SPSR_RW (1 << 4)
#define AARCH64_SPSR_F (1 << 6)
#define AARCH64_SPSR_I (1 << 7)
#define AARCH64_SPSR_A (1 << 8)
#define AARCH64_SPSR_D (1 << 9)
#define AARCH64_SPSR_IL (1 << 20)
#define AARCH64_SPSR_SS (1 << 21)
#define AARCH64_SPSR_V (1 << 28)
#define AARCH64_SPSR_C (1 << 29)
#define AARCH64_SPSR_Z (1 << 30)
#define AARCH64_SPSR_N (1 << 31)

/*
* Multiprocessor Affinity Register
*/
#define MPIDR_EL1_AFF3_LSB 32
#define MPIDR_EL1_U (1 << 30)
#define MPIDR_EL1_MT (1 << 24)
#define MPIDR_EL1_AFF2_LSB 16
#define MPIDR_EL1_AFF1_LSB 8
#define MPIDR_EL1_AFF0_LSB 0
#define MPIDR_EL1_AFF_WIDTH 8

/*
* Data Cache Zero ID Register
*/
#define DCZID_EL0_BS_LSB 0
#define DCZID_EL0_BS_WIDTH 4
#define DCZID_EL0_DZP_LSB 5
#define DCZID_EL0_DZP (1 << 5)

/*
* System Control Register
*/
#define SCTLR_EL1_UCI (1 << 26)
#define SCTLR_ELx_EE (1 << 25)
#define SCTLR_EL1_E0E (1 << 24)
#define SCTLR_ELx_WXN (1 << 19)
#define SCTLR_EL1_nTWE (1 << 18)
#define SCTLR_EL1_nTWI (1 << 16)
#define SCTLR_EL1_UCT (1 << 15)
#define SCTLR_EL1_DZE (1 << 14)
#define SCTLR_ELx_I (1 << 12)
#define SCTLR_EL1_UMA (1 << 9)
#define SCTLR_EL1_SED (1 << 8)
#define SCTLR_EL1_ITD (1 << 7)
#define SCTLR_EL1_THEE (1 << 6)
#define SCTLR_EL1_CP15BEN (1 << 5)
#define SCTLR_EL1_SA0 (1 << 4)
#define SCTLR_ELx_SA (1 << 3)
#define SCTLR_ELx_C (1 << 2)
#define SCTLR_ELx_A (1 << 1)
#define SCTLR_ELx_M (1 << 0)

/*
* Architectural Feature Access Control Register
*/
#define CPACR_EL1_TTA (1 << 28)
#define CPACR_EL1_FPEN (3 << 20)

/*
* Architectural Feature Trap Register
*/
#define CPTR_ELx_TCPAC (1 << 31)
#define CPTR_ELx_TTA (1 << 20)
#define CPTR_ELx_TFP (1 << 10)

/*
* Secure Configuration Register
*/
#define SCR_EL3_TWE (1 << 13)
#define SCR_EL3_TWI (1 << 12)
#define SCR_EL3_ST (1 << 11)
#define SCR_EL3_RW (1 << 10)
#define SCR_EL3_SIF (1 << 9)
#define SCR_EL3_HCE (1 << 8)
#define SCR_EL3_SMD (1 << 7)
#define SCR_EL3_EA (1 << 3)
#define SCR_EL3_FIQ (1 << 2)
#define SCR_EL3_IRQ (1 << 1)
#define SCR_EL3_NS (1 << 0)

/*
* Hypervisor Configuration Register
*/
#define HCR_EL2_ID (1 << 33)
#define HCR_EL2_CD (1 << 32)
#define HCR_EL2_RW (1 << 31)
#define HCR_EL2_TRVM (1 << 30)
#define HCR_EL2_HVC (1 << 29)
#define HCR_EL2_TDZ (1 << 28)

#define INTERRUPT_ENABLE() __asm__ __volatile__("msr daifclr, #2" :: \
        : "memory")

#define INTERRUPT_DISABLE() __asm__ __volatile__("msr daifset, #2" :: \
        : "memory")

#define MODE_EL_SHIFT (0x2)
#define MODE_EL_MASK (0x3)

#define MODE_EL3 (0x3)
#define MODE_EL2 (0x2)
#define MODE_EL1 (0x1)
#define MODE_EL0 (0x0)

#define GET_EL(_mode) (((_mode) >> MODE_EL_SHIFT) & MODE_EL_MASK)

/* pseudo assembler instructions */
#define MFCPSR() (            \
{                         \
    u32 rval = 0U;        \
    __asm__ __volatile__( \
                          "mrs	%0, DAIF\n"  \
                          : "=r"(rval));    \
    rval;                 \
})

#define MTCPSR(v) __asm__ __volatile__( \
                                        "msr	DAIF,%0\n"                     \
                                        :                                   \
                                        : "r"(v)                            \
                                        : "cc")

#define CPSIEI() __asm__ __volatile__("cpsie	i\n")
#define CPSIDI() __asm__ __volatile__("cpsid	i\n")

#define CPSIEF() __asm__ __volatile__("cpsie	f\n")
#define CPSIDF() __asm__ __volatile__("cpsid	f\n")

/* memory synchronization operations */

/* Instruction Synchronization Barrier */
#define ISB_SY() __asm__ __volatile__("isb sy")
#define ISB() __asm__ __volatile__("isb" \
                                   :     \
                                   :     \
                                   : "memory")

/* Data Synchronization Barrier */
#define DSB_SY() __asm__ __volatile__("dsb sy")
#define DSB() __asm__ __volatile__("dsb sy" \
                                   :     \
                                   :     \
                                   : "memory")

/* Data Memory Barrier */
#define DMB_SY() __asm__ __volatile__("dmb sy")
#define DMB() __asm__ __volatile__("dmb" \
                                   :     \
                                   :     \
                                   : "memory")
#define WMB()    __asm__ __volatile__("dsb st"\
                                      :    \
                                      :    \
                                      :  "memory")

/* Wait For Interrupt */
#define wfi() asm volatile("wfi" \
                           :     \
                           :     \
                           : "memory")

/* Count leading zeroes (clz) */
#define CLZ(arg) (            \
{                         \
    uint32_t rval;        \
    __asm__ __volatile__( \
                          "clz	%0,%1"       \
                          : "=r"(rval)      \
                          : "r"(arg));      \
    rval;                 \
})

#define MTCPDC(reg, val) __asm__ __volatile__("dc " #reg ",%0" \
        :                \
        : "r"(val))
#define MTCPIC(reg, val) __asm__ __volatile__("ic " #reg ",%0" \
        :                \
        : "r"(val))

#define MTCPICALL(reg) __asm__ __volatile__("ic " #reg)
#define MTCPTLBI(reg) __asm__ __volatile__("tlbi " #reg)
#define MTCPAT(reg, val) __asm__ __volatile__("at " #reg ",%0" \
        :                \
        : "r"(val))

#define AARCH64_READ_SYSREG(reg) (          \
{                                       \
    uint64_t val;                       \
    __asm__ __volatile__("mrs %0," #reg \
                         : "=r"(val));  \
    val;                                \
})

#define AARCH64_WRITE_SYSREG(reg, val) (           \
{                                              \
    __asm__ __volatile__("msr " #reg ",%0" \
                         :                 \
                         : "r"(val));      \
})

#define AARCH64_ZERO_SYSREG(reg) __asm__ volatile("msr " #reg " ,xzr" :: \
        : "memory")


#ifdef __cplusplus
}
#endif

#endif // V8_SYSTEM_H
