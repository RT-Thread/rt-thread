/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-01-22 16:30:56
 * @LastEditTime: 2021-05-24 14:35:53
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \project_freertos\devices\ft2004\bsp\core\ft_asm.h
 */

#ifndef FT_AARCH32_ASM_H
#define FT_AARCH32_ASM_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_types.h"

#define __ASM __asm
#define __STRINGIFY(x) #x
/* C语言实现MCR指令 */
#define __MCR(coproc, opcode_1, src, CRn, CRm, opcode_2)                                                                                                   \
    __ASM volatile("MCR " __STRINGIFY(p##coproc) ", " __STRINGIFY(opcode_1) ", "                                                                           \
                                                                            "%0, " __STRINGIFY(c##CRn) ", " __STRINGIFY(c##CRm) ", " __STRINGIFY(opcode_2) \
                   :                                                                                                                                       \
                   : "r"(src)                                                                                                                              \
                   : "memory");

/* C语言实现MRC指令 */
#define __MRC(coproc, opcode_1, CRn, CRm, opcode_2)                                                                                                            \
    ({                                                                                                                                                         \
        u32 __dst;                                                                                                                                             \
        __ASM volatile("MRC " __STRINGIFY(p##coproc) ", " __STRINGIFY(opcode_1) ", "                                                                           \
                                                                                "%0, " __STRINGIFY(c##CRn) ", " __STRINGIFY(c##CRm) ", " __STRINGIFY(opcode_2) \
                       : "=r"(__dst)::"memory");                                                                                                               \
        __dst;                                                                                                                                                 \
    })

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

#define IRQ_DISABLE()               \
    __asm volatile("CPSID i" ::     \
                       : "memory"); \
    __asm volatile("DSB");          \
    __asm volatile("ISB");

#define IRQ_ENABLE()                \
    __asm volatile("CPSIE i" ::     \
                       : "memory"); \
    __asm volatile("DSB");          \
    __asm volatile("ISB");

    /* the exception stack without VFP registers */
    struct ft_hw_exp_stack
    {
        u32 r0;
        u32 r1;
        u32 r2;
        u32 r3;
        u32 r4;
        u32 r5;
        u32 r6;
        u32 r7;
        u32 r8;
        u32 r9;
        u32 r10;
        u32 fp;
        u32 ip;
        u32 sp;
        u32 lr;
        u32 pc;
        u32 cpsr;
    };

#ifdef __cplusplus
}
#endif

#endif // !
