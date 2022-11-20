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
 * FilePath: faarch32.h
 * Date: 2022-02-10 14:53:41
 * LastEditTime: 2022-02-17 17:28:37
 * Description:  This files is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   Huanghe     2021/7/3     init
 * 1.1   Wangxiaodong  2021/9/24    modify sys_icc_bpr_set and sys_icc_bpr_get
 */

#ifndef BSP_AARCH32_ASM_H
#define BSP_AARCH32_ASM_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ftypes.h"

#define __ASM __asm
#define __STATIC_INLINE static inline
#define __STRINGIFY(x) #x
/* C语言实现MCR指令 */
#define __MCR(coproc, opcode_1, src, CRn, CRm, opcode_2)                                                                                                   \
    __ASM volatile("MCR " __STRINGIFY(p##coproc) ", " __STRINGIFY(opcode_1) ", "                                                                           \
                                                                            "%0, " __STRINGIFY(c##CRn) ", " __STRINGIFY(c##CRm) ", " __STRINGIFY(opcode_2) \
                   :                                                                                                                                       \
                   : "r"(src)                                                                                                                              \
                   : "memory");

/* C语言实现MRC指令 */
#define __MRC(coproc, opcode_1, CRn, CRm, opcode_2)                                                                                                                \
    (                                                                                                                                                              \
        {                                                                                                                                                          \
            u32 __dst;                                                                                                                                             \
            __ASM volatile("MRC " __STRINGIFY(p##coproc) ", " __STRINGIFY(opcode_1) ", "                                                                           \
                                                                                    "%0, " __STRINGIFY(c##CRn) ", " __STRINGIFY(c##CRm) ", " __STRINGIFY(opcode_2) \
                           : "=r"(__dst)::"memory");                                                                                                               \
            __dst;                                                                                                                                                 \
        })

/* C语言实现MRRC指令 */
#define __MRRC(coproc, opcode_1, dst_1, dst_2, CRm) (                                              \
    {                                                                                              \
        __asm__ __volatile__(                                                                      \
            "MRRC " __STRINGIFY(p##coproc) ", " __STRINGIFY(opcode_1) ", "                         \
                                                                      "%0,%1," __STRINGIFY(c##CRm) \
            : "=r"(dst_1), "=r"(dst_2));                                                           \
    })

/**
 * @name: aarch32_cntp_ctl_get
 * @msg:  Read the register that holds the timer value for the EL1 physical timer.
 * @return {__STATIC_INLINEu32}: TimerValue, bits [31:0] The TimerValue view of the EL1 physical timer.
 */
__attribute__((always_inline)) __STATIC_INLINE u32 aarch32_cntp_ctl_get(void)
{
    /* MRC p15(coproc) 0(opcode1) CR14(n) CR2(m)  1(opcode2) */
    return __MRC(15, 0, 14, 2, 1);
}

/**
 * @name: aarch32_cntp_tlb_get
 * @msg:
 * @return {*}
 * @param {__STATIC_INLINE u32} aarch32_cntp_ctl_get
 */
__attribute__((always_inline)) __STATIC_INLINE u32 aarch32_cntp_tlb_get(void)
{
    return __MRC(15, 0, 0, 2, 0);
}

/**
 * @name: aarch32_cntp_ctl_set
 * @msg:  Read the register that holds the timer value for the EL1 physical timer.
 * @return {__STATIC_INLINEu32}: TimerValue, bits [31:0] The TimerValue view of the EL1 physical timer.
 */
__attribute__((always_inline)) __STATIC_INLINE void aarch32_cntp_ctl_set(u32 regVal)
{
    /* MRC p15(coproc) regVal 0(opcode1) CR14(n) CR2(m)  1(opcode2) */
    __MCR(15, 0, regVal, 14, 2, 1);
}

/**
 * @name: arm_aarch32_cntfrq_get
 * @msg:  This register is provided so that software can discover the frequency of the system counter.
 * @return {__STATIC_INLINEu32}:  frequency of the system counter
 */
__attribute__((always_inline)) __STATIC_INLINE u32 aarch32_cntfrq_get(void)
{
    return __MRC(15, 0, 14, 0, 0);
}

/**
 * @name: aarch32_cntpct_get
 * @msg: get the 64-bit physical count value
 * @return {*}
 * @param {__STATIC_INLINE u64} aarch32_cntpct_get
 */
__attribute__((always_inline)) __STATIC_INLINE u64 aarch32_cntpct_get()
{
    u64 cnt = 0;
    u32 cnt_low = 0, cnt_high = 0;
    __MRRC(15, 0, cnt_low, cnt_high, 14);
    cnt = (u64)cnt_high << 32 | cnt_low;
    return cnt;
}

/**
 * @name: aarch32_cntp_tval_set
 * @msg:  write the register that control register for the EL1 physical timer.
 * @in param {u32}: TimerValue, bits [31:0] The TimerValue view of the EL1 physical timer.
 */
__attribute__((always_inline)) __STATIC_INLINE void aarch32_cntp_tval_set(u32 RegValue)
{
    __MCR(15, 0, RegValue, 14, 2, 0);
}

/**
 * @name: aarch32_sctrl_get
 * @msg: read the register that control system
 */
__attribute__((always_inline)) __STATIC_INLINE u32 aarch32_sctrl_get()
{
    return __MRC(15, 0, 1, 0, 0);
}

/**
     * @name: aarch32_sctrl_set
     * @msg: read the register that control system
     */
#define AARCH32_SCTRL_CACHE_BIT (1 << 2) /* 1: enable, 0: disable */
__attribute__((always_inline)) __STATIC_INLINE void aarch32_sctrl_set(u32 RegVal)
{
    __MCR(15, 0, RegVal, 1, 0, 0);
}

/**********************************************/

__attribute__((always_inline)) __STATIC_INLINE u32 __get_VBAR(void)
{
    return __MRC(15, 0, 12, 0, 0);
}

__attribute__((always_inline)) __STATIC_INLINE void __set_VBAR(u32 vbar)
{
    __MCR(15, 0, vbar, 12, 0, 0);
}

__attribute__((always_inline)) __STATIC_INLINE void sys_icc_igrpen0_set(u32 value)
{
    __MCR(15, 0, value, 12, 12, 6);
}

__attribute__((always_inline)) __STATIC_INLINE u32 sys_icc_igrpen0_get(void)
{
    return __MRC(15, 0, 12, 12, 6);
}

__attribute__((always_inline)) __STATIC_INLINE void sys_icc_igrpen1_set(u32 value)
{
    __MCR(15, 0, value, 12, 12, 7);
}

__attribute__((always_inline)) __STATIC_INLINE u32 sys_icc_igrpen1_get(void)
{
    return __MRC(15, 0, 12, 12, 7);
}

__attribute__((always_inline)) __STATIC_INLINE void sys_icc_ctlr_set(u32 value)
{
    __MCR(15, 0, value, 12, 12, 4);
}

__attribute__((always_inline)) __STATIC_INLINE u32 sys_icc_ctlr_get(void)
{
    return __MRC(15, 0, 12, 12, 4);
}

__attribute__((always_inline)) __STATIC_INLINE u32 sys_icc_hppir0_get(void)
{
    return __MRC(15, 0, 12, 8, 2);
}

__attribute__((always_inline)) __STATIC_INLINE void sys_icc_bpr_set(u32 value)
{
    __MCR(15, 0, value, 12, 12, 3);
}

__attribute__((always_inline)) __STATIC_INLINE u32 sys_icc_bpr_get(void)
{
    return __MRC(15, 0, 12, 12, 3);
}

__attribute__((always_inline)) __STATIC_INLINE u32 sys_icc_hppir1_get(void)
{
    return __MRC(15, 0, 12, 12, 2);
}

__attribute__((always_inline)) __STATIC_INLINE void sys_icc_eoir0_set(u32 value)
{
    __MCR(15, 0, value, 12, 8, 1);
}

__attribute__((always_inline)) __STATIC_INLINE void sys_icc_eoir1_set(u32 value)
{
    __MCR(15, 0, value, 12, 12, 1);
}

__attribute__((always_inline)) __STATIC_INLINE void sys_icc_pmr_set(u32 value)
{
    __MCR(15, 0, value, 4, 6, 0);
}

__attribute__((always_inline)) __STATIC_INLINE u32 sys_icc_pmr_get(void)
{
    return __MRC(15, 0, 4, 6, 0);
}

__attribute__((always_inline)) __STATIC_INLINE u32 sys_icc_iar1_get(void)
{
    return __MRC(15, 0, 12, 12, 0);
}

__attribute__((always_inline)) __STATIC_INLINE void sys_icc_sre_set(u32 value)
{
    __MCR(15, 0, value, 12, 12, 5);
}

__attribute__((always_inline)) __STATIC_INLINE u32 sys_icc_sre_get(void)
{
    return __MRC(15, 0, 12, 12, 5);
}

__attribute__((always_inline)) __STATIC_INLINE u32 sys_icc_rpr_get(void)
{
    return __MRC(15, 0, 12, 11, 3);
}

/*   Generic Timer registers  */
/**
     * @name: arm_aarch32_cntfrq_get
     * @msg:  This register is provided so that software can discover the frequency of the system counter.
     * @return {__STATIC_INLINEu32}:  frequency of the system counter
     */
__attribute__((always_inline)) __STATIC_INLINE u32 arm_aarch32_cntfrq_get(void)
{
    return __MRC(15, 0, 14, 0, 0);
}

/* arm_aarch32_cnttimer_set */
__attribute__((always_inline)) __STATIC_INLINE void arm_aarch32_cnttimer_set(u32 RegValue)
{
    __MCR(15, 0, RegValue, 14, 2, 2);
}

/**
     * @name: arm_aarch32_cnthv_tval_get
     * @msg:  Provides AArch32 access to the timer value for the EL2 virtual timer.
     * @return {__STATIC_INLINEu32}: EL2 virtual timer Cnt.
     */
__attribute__((always_inline)) __STATIC_INLINE u32 arm_aarch32_cnthv_tval_get(void)
{
    return __MRC(15, 0, 14, 3, 0);
}

/**
     * @name: arm_aarch32_cnthv_ctl_set
     * @msg:  Provides AArch32 access to the control register for the EL2 virtual timer.
     * @in param {u32}: RegValue;ENABLE: bit [0] 0 Timer disabled,1 Timer enabled.
     *                  IMASK,bit [1]: 0 Timer interrupt is not masked by the IMASK bit.   1 Timer interrupt is masked by the IMASK bit.
     *                  ISTATUS, bit [2]:  0 Timer condition is not met. 1 Timer condition is met. rea-only
     */
__attribute__((always_inline)) __STATIC_INLINE void arm_aarch32_cnthv_ctl_set(u32 RegValue)
{
    __MCR(15, 0, RegValue, 14, 3, 1);
}

/**
     * @name: arm_aarch32_cnthv_ctl_get
     * @msg:  Provides AArch32 access to the control register for the EL2 virtual timer.
     * @return {__STATIC_INLINEu32}: RegValue;ENABLE: bit [0] 0 Timer disabled,1 Timer enabled.
     *                  IMASK,bit [1]: 0 Timer interrupt is not masked by the IMASK bit.   1 Timer interrupt is masked by the IMASK bit.
     *                  ISTATUS, bit [2]:  0 Timer condition is not met. 1 Timer condition is met. read-only
     */
__attribute__((always_inline)) __STATIC_INLINE u32 arm_aarch32_cnthv_ctl_get(void)
{
    return __MRC(15, 0, 14, 3, 1);
}

/**
     * @name: arm_aarch32_cnthv_tval_set
     * @msg:  Provides AArch32 access to the timer value for the EL2 virtual timer.
     * @in param {u32}: TimerValue, bits [31:0] The TimerValue view of the EL2 virtual timer.
     */
__attribute__((always_inline)) __STATIC_INLINE void arm_aarch32_cnthv_tval_set(u32 RegValue)
{
    __MCR(15, 0, RegValue, 14, 3, 0);
}

/**
     * @name: arm_aarch32_cntvct_get
     * @msg:  Read the register that holds the 64-bit virtual count value. The virtual count value is equal to the physical count value visible in CNTPCT minus the virtual offset visible in CNTVOFF.
     * @return {__STATIC_INLINEu64}Bits [63:0] Virtual count value.
     */
__attribute__((always_inline)) __STATIC_INLINE u64 arm_aarch32_cntvct_get(void)
{
    /* "r0" --- low,
        "r1" --- hi
      */
    u32 low;
    u32 hi;
    __asm__ volatile(
        ".word 0xec510f1e \n" /* mrrc p15, 1, r0, r1, c14 */
        "mov %0, r0 \n"
        "mov %1, r1 \n"
        : "=&r"(low), "=&r"(hi));
    return (((u64)hi) << 32) | low;
}

/* physical */

/**
     * @name: arm_aarch32_cntp_tval_get
     * @msg:  Read the register that holds the timer value for the EL1 physical timer.
     * @return {__STATIC_INLINEu32}: TimerValue, bits [31:0] The TimerValue view of the EL1 physical timer.
     */
__attribute__((always_inline)) __STATIC_INLINE u32 arm_aarch32_cntp_tval_get(void)
{
    return __MRC(15, 0, 14, 2, 0);
}

/**
     * @name: arm_aarch32_cntp_tval_set
     * @msg:  write the register that control register for the EL1 physical timer.
     * @in param {u32}: TimerValue, bits [31:0] The TimerValue view of the EL1 physical timer.
     */
__attribute__((always_inline)) __STATIC_INLINE void arm_aarch32_cntp_tval_set(u32 RegValue)
{
    __MCR(15, 0, RegValue, 14, 2, 0);
}

/**
     * @name: arm_aarch32_cntp_ctl_set
     * @msg:  write the register that control register for the EL1 physical timer.
     * @in param {u32}: ENABLE, bit[0] Enables the timer ; IMASK, bit [1] Timer interrupt mask bit; ISTATUS, bit [2] The status of the timer.
     */
__attribute__((always_inline)) __STATIC_INLINE void arm_aarch32_cntp_ctl_set(u32 RegValue)
{
    __MCR(15, 0, RegValue, 14, 2, 1);
}

/**
     * @name: arm_aarch32_cntp_ctl_get
     * @msg:  Read the register that control register for the EL1 physical timer.
     * @return {__STATIC_INLINEu32}: ENABLE, bit[0] Enables the timer ; IMASK, bit [1] Timer interrupt mask bit; ISTATUS, bit [2] The status of the timer.
     */
__attribute__((always_inline)) __STATIC_INLINE u32 arm_aarch32_cntp_ctl_get(void)
{
    return __MRC(15, 0, 14, 2, 1);
}

/**
     * @name: arm_aarch32_cntpct_get
     * @msg:  Read the register that holds the 64-bit physical count value.
     * @return {__STATIC_INLINEu64} CompareValue, bits [63:0] Physical count value.
     */
__attribute__((always_inline)) __STATIC_INLINE u64 arm_aarch32_cntpct_get(void)
{
    /* "r0" --- low,
        "r1" --- hi
      */
    u32 low;
    u32 hi;
    __asm__ volatile(

        ".word 0xec510f0e \n" /* mrrc p15, 0, r0, r1, c14 */
        "mov %0, r0 \n"
        "mov %1, r1 \n"
        : "=&r"(low), "=&r"(hi));
    return (((u64)hi) << 32) | low;
}

#define INTERRUPT_DISABLE()         \
    __asm volatile("CPSID i" ::     \
                       : "memory"); \
    __asm volatile("DSB");          \
    __asm volatile("ISB");

#define INTERRUPT_ENABLE()          \
    __asm volatile("CPSIE i" ::     \
                       : "memory"); \
    __asm volatile("DSB");          \
    __asm volatile("ISB");

#ifdef __cplusplus
}
#endif

#endif // !