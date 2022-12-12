/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     zx.chen      CSI Header File for GCC.
 */

#ifndef _CSI_RV32_GCC_H_
#define _CSI_RV32_GCC_H_

#include <stdlib.h>

#ifndef __ASM
#define __ASM                   __asm     /*!< asm keyword for GNU Compiler */
#endif

#ifndef __INLINE
#define __INLINE                inline    /*!< inline keyword for GNU Compiler */
#endif

#ifndef __ALWAYS_STATIC_INLINE
#define __ALWAYS_STATIC_INLINE  __attribute__((always_inline)) static inline
#endif

#ifndef __STATIC_INLINE
#define __STATIC_INLINE         static inline
#endif

/* ###########################  Core Function Access  ########################### */
/** \ingroup  CSI_Core_FunctionInterface
    \defgroup CSI_Core_RegAccFunctions CSI Core Register Access Functions
  @{
 */
/**
  \brief   Enable IRQ Interrupts
  \details Enables IRQ interrupts by setting the IE-bit in the PSR.
           Can only be executed in Privileged modes.
 */
__ALWAYS_STATIC_INLINE void __enable_irq(void)
{
    __ASM volatile("csrs mstatus, 8");
}

/**
  \brief   Disable IRQ Interrupts
  \details Disables IRQ interrupts by clearing the IE-bit in the PSR.
  Can only be executed in Privileged modes.
 */
__ALWAYS_STATIC_INLINE void __disable_irq(void)
{
    __ASM volatile("csrc mstatus, 8");
}

/**
  \brief   Get MXSTATUS
  \details Returns the content of the MXSTATUS Register.
  \return               MXSTATUS Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MXSTATUS(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mxstatus" : "=r"(result));
    return (result);
}

/**
  \brief   Set MXSTATUS
  \details Writes the given value to the MXSTATUS Register.
  \param [in]    MXSTATUS Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MXSTATUS(uint32_t mxstatus)
{
    __ASM volatile("csrw mxstatus, %0" : : "r"(mxstatus));
}

/**
  \brief   Get MEXSTATUS
  \details Returns the content of the MEXSTATUS Register.
  \return               MEXSTATUS Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MEXSTATUS(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mexstatus" : "=r"(result));
    return (result);
}

/**
  \brief   Set MEXSTATUS
  \details Writes the given value to the MSTATUS Register.
  \param [in]    MEXSTATUS Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MEXSTATUS(uint32_t mexstatus)
{
    __ASM volatile("csrw mexstatus, %0" : : "r"(mexstatus));
}


/**
  \brief   Get MRADDR
  \details Returns the content of the MRADDR Register.
  \return               MRADDR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MRADDR(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mraddr" : "=r"(result));
    return (result);
}

/**
  \brief   Get FXCR
  \details Returns the content of the FXCR Register.
  \return               FXCR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_FXCR(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, fxcr" : "=r"(result));
    return (result);
}


/**
  \brief   Set FXCR
  \details Writes the given value to the FXCR Register.
  \param [in]     FXCR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_FXCR(uint32_t fxcr)
{
    __ASM volatile("csrw fxcr, %0" : : "r"(fxcr));
}

/**
  \brief   Get MSTATUS
  \details Returns the content of the MSTATUS Register.
  \return               MSTATUS Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MSTATUS(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mstatus" : "=r"(result));
    return (result);
}

/**
  \brief   Set MSTATUS
  \details Writes the given value to the MSTATUS Register.
  \param [in]    mstatus  MSTATUS Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MSTATUS(uint32_t mstatus)
{
    __ASM volatile("csrw mstatus, %0" : : "r"(mstatus));
}

/**
  \brief   Get MHCR
  \details Returns the content of the MHCR Register.
  \return               MHCR Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MHCR(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mhcr" : "=r"(result));
    return (result);
}

/**
  \brief   Set MHCR
  \details Writes the given value to the MHCR Register.
  \param [in]    mstatus  MHCR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MHCR(uint32_t mhcr)
{
    __ASM volatile("csrw mhcr, %0" : : "r"(mhcr));
}

/**
  \brief   Get MHINT
  \details Returns the content of the MHINT Register.
  \return               MHINT Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MHINT(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mhint" : "=r"(result));
    return (result);
}

/**
  \brief   Set MHINT
  \details Writes the given value to the MHINT Register.
  \param [in]           MHINT Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MHINT(uint32_t mhint)
{
    __ASM volatile("csrw mhint, %0" : : "r"(mhint));
}

/**
  \brief   Get MISA Register
  \details Returns the content of the MISA Register.
  \return               MISA Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MISA(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, misa" : "=r"(result));
    return (result);
}

/**
  \brief   Set MISA
  \details Writes the given value to the MISA Register.
  \param [in]    misa  MISA Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MISA(uint32_t misa)
{
    __ASM volatile("csrw misa, %0" : : "r"(misa));
}

/**
  \brief   Get MIE Register
  \details Returns the content of the MIE Register.
  \return               MIE Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MIE(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mie" : "=r"(result));
    return (result);
}

/**
  \brief   Set MIE
  \details Writes the given value to the MIE Register.
  \param [in]    mie  MIE Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MIE(uint32_t mie)
{
    __ASM volatile("csrw mie, %0" : : "r"(mie));
}

/**
  \brief   Get MTVEC Register
  \details Returns the content of the MTVEC Register.
  \return               MTVEC Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MTVEC(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mtvec" : "=r"(result));
    return (result);
}

/**
  \brief   Set MTVEC
  \details Writes the given value to the MTVEC Register.
  \param [in]    mtvec  MTVEC Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MTVEC(uint32_t mtvec)
{
    __ASM volatile("csrw mtvec, %0" : : "r"(mtvec));
}

/**
  \brief   Set MTVT
  \details Writes the given value to the MTVT Register.
  \param [in]    mtvt  MTVT Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MTVT(uint32_t mtvt)
{
    __ASM volatile("csrw mtvt, %0" : : "r"(mtvt));
}

/**
  \brief   Get MTVT Register
  \details Returns the content of the MTVT Register.
  \return               MTVT Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MTVT(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mtvt" : "=r"(result));
    return (result);
}

/**
  \brief   Get SP
  \details Returns the content of the SP Register.
  \return               SP Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_SP(void)
{
    uint32_t result;

    __ASM volatile("mv %0, sp" : "=r"(result));
    return (result);
}

/**
  \brief   Set SP
  \details Writes the given value to the SP Register.
  \param [in]    sp  SP Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_SP(uint32_t sp)
{
    __ASM volatile("mv sp, %0" : : "r"(sp): "sp");
}

/**
  \brief   Get MSCRATCH Register
  \details Returns the content of the MSCRATCH Register.
  \return               MSCRATCH Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MSCRATCH(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mscratch" : "=r"(result));
    return (result);
}

/**
  \brief   Set MSCRATCH
  \details Writes the given value to the MSCRATCH Register.
  \param [in]    mscratch  MSCRATCH Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MSCRATCH(uint32_t mscratch)
{
    __ASM volatile("csrw mscratch, %0" : : "r"(mscratch));
}

/**
  \brief   Get MEPC Register
  \details Returns the content of the MEPC Register.
  \return               MEPC Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MEPC(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mepc" : "=r"(result));
    return (result);
}

/**
  \brief   Set MEPC
  \details Writes the given value to the MEPC Register.
  \param [in]    mepc  MEPC Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MEPC(uint32_t mepc)
{
    __ASM volatile("csrw mepc, %0" : : "r"(mepc));
}

/**
  \brief   Get MCAUSE Register
  \details Returns the content of the MCAUSE Register.
  \return               MCAUSE Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MCAUSE(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mcause" : "=r"(result));
    return (result);
}

/**
  \brief   Get MNXTI Register
  \details Returns the content of the MNXTI Register.
  \return               MNXTI Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MNXTI(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mnxti" : "=r"(result));
    return (result);
}

/**
  \brief   Set MNXTI
  \details Writes the given value to the MNXTI Register.
  \param [in]    mnxti  MNXTI Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MNXTI(uint32_t mnxti)
{
    __ASM volatile("csrw mnxti, %0" : : "r"(mnxti));
}

/**
  \brief   Get MINTSTATUS Register
  \details Returns the content of the MINTSTATUS Register.
  \return               MINTSTATUS Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MINTSTATUS(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mintstatus" : "=r"(result));
    return (result);
}

/**
  \brief   Get MTVAL Register
  \details Returns the content of the MTVAL Register.
  \return               MTVAL Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MTVAL(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mtval" : "=r"(result));
    return (result);
}

/**
  \brief   Get MIP Register
  \details Returns the content of the MIP Register.
  \return               MIP Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MIP(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mip" : "=r"(result));
    return (result);
}

/**
  \brief   Set MIP
  \details Writes the given value to the MIP Register.
  \param [in]    mip  MIP Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MIP(uint32_t mip)
{
    __ASM volatile("csrw mip, %0" : : "r"(mip));
}

/**
  \brief   Get MCYCLEL Register
  \details Returns the content of the MCYCLEL Register.
  \return               MCYCLE Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MCYCLE(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mcycle" : "=r"(result));
    return (result);
}

/**
  \brief   Get MCYCLEH Register
  \details Returns the content of the MCYCLEH Register.
  \return               MCYCLEH Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MCYCLEH(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mcycleh" : "=r"(result));
    return (result);
}

/**
  \brief   Get MINSTRET Register
  \details Returns the content of the MINSTRET Register.
  \return               MINSTRET Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MINSTRET(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, minstret" : "=r"(result));
    return (result);
}

/**
  \brief   Get MINSTRETH Register
  \details Returns the content of the MINSTRETH Register.
  \return               MINSTRETH Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MINSTRETH(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, minstreth" : "=r"(result));
    return (result);
}

/**
  \brief   Get MVENDORID Register
  \details Returns the content of the MVENDROID Register.
  \return               MVENDORID Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MVENDORID(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mvendorid" : "=r"(result));
    return (result);
}

/**
  \brief   Get MARCHID Register
  \details Returns the content of the MARCHID Register.
  \return               MARCHID Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MARCHID(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, marchid" : "=r"(result));
    return (result);
}

/**
  \brief   Get MIMPID Register
  \details Returns the content of the MIMPID Register.
  \return               MIMPID Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MIMPID(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mimpid" : "=r"(result));
    return (result);
}

/**
  \brief   Get MHARTID Register
  \details Returns the content of the MHARTID Register.
  \return               MHARTID Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_MHARTID(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mhartid" : "=r"(result));
    return (result);
}

/**
  \brief   Get PMPCFGx Register
  \details Returns the content of the PMPCFGx Register.
  \return               PMPCFGx Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_PMPCFG0(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpcfg0" : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_PMPCFG1(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpcfg1" : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_PMPCFG2(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpcfg2" : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_PMPCFG3(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpcfg3" : "=r"(result));
    return (result);
}

/**
  \brief   Get PMPxCFG Register by index
  \details Returns the content of the PMPxCFG Register.
  \param [in]    idx    PMP region index
  \return               PMPxCFG Register value
 */
__STATIC_INLINE uint8_t __get_PMPxCFG(uint32_t idx)
{
    uint32_t pmpcfgx = 0;

    if (idx < 4) {
        pmpcfgx = __get_PMPCFG0();
    } else if (idx >=4 && idx < 8) {
        idx -= 4;
        pmpcfgx = __get_PMPCFG1();
    } else if (idx >=8 && idx < 12) {
        idx -= 8;
        pmpcfgx = __get_PMPCFG2();
    } else if (idx >=12 && idx < 16) {
        idx -= 12;
        pmpcfgx = __get_PMPCFG3();
    } else {
        return 0;
    }

    return (uint8_t)((pmpcfgx & (0xFF << (idx << 3))) >> (idx << 3));
}

/**
  \brief   Set PMPCFGx
  \details Writes the given value to the PMPCFGx Register.
  \param [in]    pmpcfg  PMPCFGx Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_PMPCFG0(uint32_t pmpcfg)
{
    __ASM volatile("csrw pmpcfg0, %0" : : "r"(pmpcfg));
}

__ALWAYS_STATIC_INLINE void __set_PMPCFG1(uint32_t pmpcfg)
{
    __ASM volatile("csrw pmpcfg1, %0" : : "r"(pmpcfg));
}

__ALWAYS_STATIC_INLINE void __set_PMPCFG2(uint32_t pmpcfg)
{
    __ASM volatile("csrw pmpcfg2, %0" : : "r"(pmpcfg));
}

__ALWAYS_STATIC_INLINE void __set_PMPCFG3(uint32_t pmpcfg)
{
    __ASM volatile("csrw pmpcfg3, %0" : : "r"(pmpcfg));
}

/**
  \brief   Set PMPxCFG by index
  \details Writes the given value to the PMPxCFG Register.
  \param [in]    idx      PMPx region index
  \param [in]    pmpxcfg  PMPxCFG Register value to set
 */
__STATIC_INLINE void __set_PMPxCFG(uint32_t idx, uint8_t pmpxcfg)
{
    uint32_t pmpcfgx = 0;

    if (idx < 4) {
        pmpcfgx = __get_PMPCFG0();
        pmpcfgx = (pmpcfgx & ~(0xFF << (idx << 3))) | (pmpxcfg << (idx << 3));
        __set_PMPCFG0(pmpcfgx);
    } else if (idx >=4 && idx < 8) {
        idx -= 4;
        pmpcfgx = __get_PMPCFG1();
        pmpcfgx = (pmpcfgx & ~(0xFF << (idx << 3))) | (pmpxcfg << (idx << 3));
        __set_PMPCFG1(pmpcfgx);
    } else if (idx >=8 && idx < 12) {
        idx -= 8;
        pmpcfgx = __get_PMPCFG2();
        pmpcfgx = (pmpcfgx & ~(0xFF << (idx << 3))) | (pmpxcfg << (idx << 3));
        __set_PMPCFG2(pmpcfgx);
    } else if (idx >=12 && idx < 16) {
        idx -= 12;
        pmpcfgx = __get_PMPCFG3();
        pmpcfgx = (pmpcfgx & ~(0xFF << (idx << 3))) | (pmpxcfg << (idx << 3));
        __set_PMPCFG3(pmpcfgx);
    } else {
        return;
    }
}

/**
  \brief   Get PMPADDRx Register
  \details Returns the content of the PMPADDRx Register.
  \return               PMPADDRx Register value
 */
__ALWAYS_STATIC_INLINE uint32_t __get_PMPADDR0(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpaddr0" : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_PMPADDR1(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpaddr1" : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_PMPADDR2(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpaddr2" : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_PMPADDR3(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpaddr3" : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_PMPADDR4(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpaddr4" : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_PMPADDR5(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpaddr5" : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_PMPADDR6(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpaddr6" : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_PMPADDR7(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpaddr7" : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_PMPADDR8(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpaddr8" : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_PMPADDR9(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpaddr9" : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_PMPADDR10(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpaddr10" : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_PMPADDR11(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpaddr11" : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_PMPADDR12(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpaddr12" : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_PMPADDR13(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpaddr13" : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_PMPADDR14(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpaddr14" : "=r"(result));
    return (result);
}

__ALWAYS_STATIC_INLINE uint32_t __get_PMPADDR15(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, pmpaddr15" : "=r"(result));
    return (result);
}

/**
  \brief   Get PMPADDRx Register by index
  \details Returns the content of the PMPADDRx Register.
  \param [in]    idx    PMP region index
  \return               PMPADDRx Register value
 */
__STATIC_INLINE uint32_t __get_PMPADDRx(uint32_t idx)
{
    switch (idx) {
    case 0: return __get_PMPADDR0();
    case 1: return __get_PMPADDR1();
    case 2: return __get_PMPADDR2();
    case 3: return __get_PMPADDR3();
    case 4: return __get_PMPADDR4();
    case 5: return __get_PMPADDR5();
    case 6: return __get_PMPADDR6();
    case 7: return __get_PMPADDR7();
    case 8: return __get_PMPADDR8();
    case 9: return __get_PMPADDR9();
    case 10: return __get_PMPADDR10();
    case 11: return __get_PMPADDR11();
    case 12: return __get_PMPADDR12();
    case 13: return __get_PMPADDR13();
    case 14: return __get_PMPADDR14();
    case 15: return __get_PMPADDR15();
    default: return 0;
    }
}

/**
  \brief   Set PMPADDRx
  \details Writes the given value to the PMPADDRx Register.
  \param [in]    pmpaddr  PMPADDRx Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_PMPADDR0(uint32_t pmpaddr)
{
    __ASM volatile("csrw pmpaddr0, %0" : : "r"(pmpaddr));
}

__ALWAYS_STATIC_INLINE void __set_PMPADDR1(uint32_t pmpaddr)
{
    __ASM volatile("csrw pmpaddr1, %0" : : "r"(pmpaddr));
}

__ALWAYS_STATIC_INLINE void __set_PMPADDR2(uint32_t pmpaddr)
{
    __ASM volatile("csrw pmpaddr2, %0" : : "r"(pmpaddr));
}

__ALWAYS_STATIC_INLINE void __set_PMPADDR3(uint32_t pmpaddr)
{
    __ASM volatile("csrw pmpaddr3, %0" : : "r"(pmpaddr));
}

__ALWAYS_STATIC_INLINE void __set_PMPADDR4(uint32_t pmpaddr)
{
    __ASM volatile("csrw pmpaddr4, %0" : : "r"(pmpaddr));
}

__ALWAYS_STATIC_INLINE void __set_PMPADDR5(uint32_t pmpaddr)
{
    __ASM volatile("csrw pmpaddr5, %0" : : "r"(pmpaddr));
}

__ALWAYS_STATIC_INLINE void __set_PMPADDR6(uint32_t pmpaddr)
{
    __ASM volatile("csrw pmpaddr6, %0" : : "r"(pmpaddr));
}

__ALWAYS_STATIC_INLINE void __set_PMPADDR7(uint32_t pmpaddr)
{
    __ASM volatile("csrw pmpaddr7, %0" : : "r"(pmpaddr));
}

__ALWAYS_STATIC_INLINE void __set_PMPADDR8(uint32_t pmpaddr)
{
    __ASM volatile("csrw pmpaddr8, %0" : : "r"(pmpaddr));
}

__ALWAYS_STATIC_INLINE void __set_PMPADDR9(uint32_t pmpaddr)
{
    __ASM volatile("csrw pmpaddr9, %0" : : "r"(pmpaddr));
}

__ALWAYS_STATIC_INLINE void __set_PMPADDR10(uint32_t pmpaddr)
{
    __ASM volatile("csrw pmpaddr10, %0" : : "r"(pmpaddr));
}

__ALWAYS_STATIC_INLINE void __set_PMPADDR11(uint32_t pmpaddr)
{
    __ASM volatile("csrw pmpaddr11, %0" : : "r"(pmpaddr));
}

__ALWAYS_STATIC_INLINE void __set_PMPADDR12(uint32_t pmpaddr)
{
    __ASM volatile("csrw pmpaddr12, %0" : : "r"(pmpaddr));
}

__ALWAYS_STATIC_INLINE void __set_PMPADDR13(uint32_t pmpaddr)
{
    __ASM volatile("csrw pmpaddr13, %0" : : "r"(pmpaddr));
}

__ALWAYS_STATIC_INLINE void __set_PMPADDR14(uint32_t pmpaddr)
{
    __ASM volatile("csrw pmpaddr14, %0" : : "r"(pmpaddr));
}

__ALWAYS_STATIC_INLINE void __set_PMPADDR15(uint32_t pmpaddr)
{
    __ASM volatile("csrw pmpaddr15, %0" : : "r"(pmpaddr));
}

/**
  \brief   Set PMPADDRx by index
  \details Writes the given value to the PMPADDRx Register.
  \param [in]    idx      PMP region index
  \param [in]    pmpaddr  PMPADDRx Register value to set
 */
__STATIC_INLINE void __set_PMPADDRx(uint32_t idx, uint32_t pmpaddr)
{
    switch (idx) {
    case 0: __set_PMPADDR0(pmpaddr); break;
    case 1: __set_PMPADDR1(pmpaddr); break;
    case 2: __set_PMPADDR2(pmpaddr); break;
    case 3: __set_PMPADDR3(pmpaddr); break;
    case 4: __set_PMPADDR4(pmpaddr); break;
    case 5: __set_PMPADDR5(pmpaddr); break;
    case 6: __set_PMPADDR6(pmpaddr); break;
    case 7: __set_PMPADDR7(pmpaddr); break;
    case 8: __set_PMPADDR8(pmpaddr); break;
    case 9: __set_PMPADDR9(pmpaddr); break;
    case 10: __set_PMPADDR10(pmpaddr); break;
    case 11: __set_PMPADDR11(pmpaddr); break;
    case 12: __set_PMPADDR12(pmpaddr); break;
    case 13: __set_PMPADDR13(pmpaddr); break;
    case 14: __set_PMPADDR14(pmpaddr); break;
    case 15: __set_PMPADDR15(pmpaddr); break;
    default: return;
    }
}

/**
  \brief   Enable interrupts and exceptions
  \details Enables interrupts and exceptions by setting the IE-bit and EE-bit in the PSR.
           Can only be executed in Privileged modes.
 */
__ALWAYS_STATIC_INLINE void __enable_excp_irq(void)
{
    __enable_irq();
}


/**
  \brief   Disable interrupts and exceptions
  \details Disables interrupts and exceptions by clearing the IE-bit and EE-bit in the PSR.
           Can only be executed in Privileged modes.
 */
__ALWAYS_STATIC_INLINE void __disable_excp_irq(void)
{
    __disable_irq();
}

#define __CSI_GCC_OUT_REG(r) "=r" (r)
#define __CSI_GCC_USE_REG(r) "r" (r)

/**
  \brief   No Operation
  \details No Operation does nothing. This instruction can be used for code alignment purposes.
 */
__ALWAYS_STATIC_INLINE void __NOP(void)
{
    __ASM volatile("nop");
}


/**
  \brief   Wait For Interrupt
  \details Wait For Interrupt is a hint instruction that suspends execution until one of a number of events occurs.
 */
__ALWAYS_STATIC_INLINE void __WFI(void)
{
    __ASM volatile("wfi");
}

/**
  \brief   Wait For Interrupt
  \details Wait For Interrupt is a hint instruction that suspends execution until one interrupt occurs.
 */
__ALWAYS_STATIC_INLINE void __WAIT(void)
{
    __ASM volatile("wfi");
}

/**
  \brief   Doze For Interrupt
  \details Doze For Interrupt is a hint instruction that suspends execution until one interrupt occurs.
 */
__ALWAYS_STATIC_INLINE void __DOZE(void)
{
    __ASM volatile("wfi");
}

/**
  \brief   Stop For Interrupt
  \details Stop For Interrupt is a hint instruction that suspends execution until one interrupt occurs.
 */
__ALWAYS_STATIC_INLINE void __STOP(void)
{
    __ASM volatile("wfi");
}

/**
  \brief   Instruction Synchronization Barrier
  \details Instruction Synchronization Barrier flushes the pipeline in the processor,
           so that all instructions following the ISB are fetched from cache or memory,
           after the instruction has been completed.
 */
__ALWAYS_STATIC_INLINE void __ISB(void)
{
    __ASM volatile("fence");
}


/**
  \brief   Data Synchronization Barrier
  \details Acts as a special kind of Data Memory Barrier.
           It completes when all explicit memory accesses before this instruction complete.
 */
__ALWAYS_STATIC_INLINE void __DSB(void)
{
    __ASM volatile("fence");
}

/**
  \brief   Invalid all icache
  \details invalid all icache.
 */
__ALWAYS_STATIC_INLINE void __ICACHE_IALL(void)
{
    __ASM volatile("icache.iall");
}

/**
  \brief   Invalid Icache by addr
  \details Invalid Icache by addr.
  \param [in] addr  operate addr
 */
__ALWAYS_STATIC_INLINE void __ICACHE_IPA(uint32_t addr)
{
    __ASM volatile("icache.ipa %0" : : "r"(addr));
}

/**
  \brief   Invalid all dcache
  \details invalid all dcache.
 */
__ALWAYS_STATIC_INLINE void __DCACHE_IALL(void)
{
    __ASM volatile("dcache.iall");
}

/**
  \brief   Clear all dcache
  \details clear all dcache.
 */
__ALWAYS_STATIC_INLINE void __DCACHE_CALL(void)
{
    __ASM volatile("dcache.call");
}

/**
  \brief   Clear&invalid all dcache
  \details clear & invalid all dcache.
 */
__ALWAYS_STATIC_INLINE void __DCACHE_CIALL(void)
{
    __ASM volatile("dcache.ciall");
}

/**
  \brief   Invalid Dcache by addr
  \details Invalid Dcache by addr.
  \param [in] addr  operate addr
 */
__ALWAYS_STATIC_INLINE void __DCACHE_IPA(uint32_t addr)
{
    __ASM volatile("dcache.ipa %0" : : "r"(addr));
}

/**
  \brief   Clear Dcache by addr
  \details Clear Dcache by addr.
  \param [in] addr  operate addr
 */
__ALWAYS_STATIC_INLINE void __DCACHE_CPA(uint32_t addr)
{
    __ASM volatile("dcache.cpa %0" : : "r"(addr));
}

/**
  \brief   Clear & Invalid Dcache by addr
  \details Clear & Invalid Dcache by addr.
  \param [in] addr  operate addr
 */
__ALWAYS_STATIC_INLINE void __DCACHE_CIPA(uint32_t addr)
{
    __ASM volatile("dcache.cipa %0" : : "r"(addr));
}


/**
  \brief   Data Memory Barrier
  \details Ensures the apparent order of the explicit memory operations before
           and after the instruction, without ensuring their completion.
 */
__ALWAYS_STATIC_INLINE void __DMB(void)
{
    __ASM volatile("fence");
}

/**
  \brief   Reverse byte order (32 bit)
  \details Reverses the byte order in integer value.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__ALWAYS_STATIC_INLINE uint32_t __REV(uint32_t value)
{
    return __builtin_bswap32(value);
}


/**
  \brief   Reverse byte order (16 bit)
  \details Reverses the byte order in two unsigned short values.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__ALWAYS_STATIC_INLINE uint32_t __REV16(uint32_t value)
{
    uint32_t result;

    result = ((value & 0xFF000000) >> 8) | ((value & 0x00FF0000) << 8) |
             ((value & 0x0000FF00) >> 8) | ((value & 0x000000FF) << 8);

    return (result);
}


/**
  \brief   Reverse byte order in signed short value
  \details Reverses the byte order in a signed short value with sign extension to integer.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__ALWAYS_STATIC_INLINE int32_t __REVSH(int32_t value)
{
    return (short)(((value & 0xFF00) >> 8) | ((value & 0x00FF) << 8));
}


/**
  \brief   Rotate Right in unsigned value (32 bit)
  \details Rotate Right (immediate) provides the value of the contents of a register rotated by a variable number of bits.
  \param [in]    op1  Value to rotate
  \param [in]    op2  Number of Bits to rotate
  \return               Rotated value
 */
__ALWAYS_STATIC_INLINE uint32_t __ROR(uint32_t op1, uint32_t op2)
{
    return (op1 >> op2) | (op1 << (32U - op2));
}


/**
  \brief   Breakpoint
  \details Causes the processor to enter Debug state
           Debug tools can use this to investigate system state when the instruction at a particular address is reached.
 */
__ALWAYS_STATIC_INLINE void __BKPT(void)
{
    __ASM volatile("ebreak");
}

/**
  \brief   Reverse bit order of value
  \details Reverses the bit order of the given value.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__ALWAYS_STATIC_INLINE uint32_t __RBIT(uint32_t value)
{
    uint32_t result;

    int32_t s = 4 /*sizeof(v)*/ * 8 - 1; /* extra shift needed at end */

    result = value;                      /* r will be reversed bits of v; first get LSB of v */

    for (value >>= 1U; value; value >>= 1U) {
        result <<= 1U;
        result |= value & 1U;
        s--;
    }

    result <<= s;                        /* shift when v's highest bits are zero */

    return (result);
}


/**
  \brief   Count leading zeros
  \details Counts the number of leading zeros of a data value.
  \param [in]  value  Value to count the leading zeros
  \return             number of leading zeros in value
 */
#define __CLZ             __builtin_clz
/**
  \details This function saturates a signed value.
  \param [in]    x   Value to be saturated
  \param [in]    y   Bit position to saturate to [1..32]
  \return            Saturated value.
 */
__ALWAYS_STATIC_INLINE int32_t __SSAT(int32_t x, uint32_t y)
{
    int32_t posMax, negMin;
    uint32_t i;

    posMax = 1;

    for (i = 0; i < (y - 1); i++) {
        posMax = posMax * 2;
    }

    if (x > 0) {
        posMax = (posMax - 1);

        if (x > posMax) {
            x = posMax;
        }

//    x &= (posMax * 2 + 1);
    } else {
        negMin = -posMax;

        if (x < negMin) {
            x = negMin;
        }

//    x &= (posMax * 2 - 1);
    }

    return (x);
}

/**
  \brief   Unsigned Saturate
  \details Saturates an unsigned value.
  \param [in]  value  Value to be saturated
  \param [in]    sat  Bit position to saturate to (0..31)
  \return             Saturated value
 */
__ALWAYS_STATIC_INLINE uint32_t __USAT(uint32_t value, uint32_t sat)
{
    uint32_t result;

    if ((((0xFFFFFFFF >> sat) << sat) & value) != 0) {
        result = 0xFFFFFFFF >> (32 - sat);
    } else {
        result = value;
    }

    return (result);
}

/**
  \brief   Unsigned Saturate for internal use
  \details Saturates an unsigned value, should not call directly.
  \param [in]  value  Value to be saturated
  \param [in]    sat  Bit position to saturate to (0..31)
  \return             Saturated value
 */
__ALWAYS_STATIC_INLINE uint32_t __IUSAT(uint32_t value, uint32_t sat)
{
    uint32_t result;

    if (value & 0x80000000) { /* only overflow set bit-31 */
        result = 0;
    } else if ((((0xFFFFFFFF >> sat) << sat) & value) != 0) {
        result = 0xFFFFFFFF >> (32 - sat);
    } else {
        result = value;
    }

    return (result);
}

/**
  \brief   Rotate Right with Extend
  \details This function moves each bit of a bitstring right by one bit.
           The carry input is shifted in at the left end of the bitstring.
  \note    carry input will always 0.
  \param [in]    op1  Value to rotate
  \return               Rotated value
 */
__ALWAYS_STATIC_INLINE uint32_t __RRX(uint32_t op1)
{
    return 0;
}

/**
  \brief   LDRT Unprivileged (8 bit)
  \details Executes a Unprivileged LDRT instruction for 8 bit value.
  \param [in]    addr  Pointer to location
  \return             value of type uint8_t at (*ptr)
 */
__ALWAYS_STATIC_INLINE uint8_t __LDRBT(volatile uint8_t *addr)
{
    uint32_t result;

    __ASM volatile("lb %0, 0(%1)" : "=r"(result) : "r"(addr));

    return ((uint8_t) result);    /* Add explicit type cast here */
}


/**
  \brief   LDRT Unprivileged (16 bit)
  \details Executes a Unprivileged LDRT instruction for 16 bit values.
  \param [in]    addr  Pointer to location
  \return        value of type uint16_t at (*ptr)
 */
__ALWAYS_STATIC_INLINE uint16_t __LDRHT(volatile uint16_t *addr)
{
    uint32_t result;

    __ASM volatile("lh %0, 0(%1)" : "=r"(result) : "r"(addr));

    return ((uint16_t) result);    /* Add explicit type cast here */
}


/**
  \brief   LDRT Unprivileged (32 bit)
  \details Executes a Unprivileged LDRT instruction for 32 bit values.
  \param [in]    addr  Pointer to location
  \return        value of type uint32_t at (*ptr)
 */
__ALWAYS_STATIC_INLINE uint32_t __LDRT(volatile uint32_t *addr)
{
    uint32_t result;

    __ASM volatile("lw %0, 0(%1)" : "=r"(result) : "r"(addr));

    return (result);
}


/**
  \brief   STRT Unprivileged (8 bit)
  \details Executes a Unprivileged STRT instruction for 8 bit values.
  \param [in]  value  Value to store
  \param [in]    addr  Pointer to location
 */
__ALWAYS_STATIC_INLINE void __STRBT(uint8_t value, volatile uint8_t *addr)
{
    __ASM volatile("sb %1, 0(%0)" :: "r"(addr), "r"((uint32_t)value) : "memory");
}


/**
  \brief   STRT Unprivileged (16 bit)
  \details Executes a Unprivileged STRT instruction for 16 bit values.
  \param [in]  value  Value to store
  \param [in]    addr  Pointer to location
 */
__ALWAYS_STATIC_INLINE void __STRHT(uint16_t value, volatile uint16_t *addr)
{
    __ASM volatile("sh %1, 0(%0)" :: "r"(addr), "r"((uint32_t)value) : "memory");
}


/**
  \brief   STRT Unprivileged (32 bit)
  \details Executes a Unprivileged STRT instruction for 32 bit values.
  \param [in]  value  Value to store
  \param [in]    addr  Pointer to location
 */
__ALWAYS_STATIC_INLINE void __STRT(uint32_t value, volatile uint32_t *addr)
{
    __ASM volatile("sw %1, 0(%0)" :: "r"(addr), "r"(value) : "memory");
}

/*@}*/ /* end of group CSI_Core_InstructionInterface */

/* ###################  Compiler specific Intrinsics  ########################### */
/** \defgroup CSI_SIMD_intrinsics CSI SIMD Intrinsics
  Access to dedicated SIMD instructions \n
  Single Instruction Multiple Data (SIMD) extensions are provided to simplify development of application software. SIMD extensions increase the processing capability without materially increasing the power consumption. The SIMD extensions are completely transparent to the operating system (OS), allowing existing OS ports to be used.

  @{
*/

/**
  \brief   Halfword packing instruction. Combines bits[15:0] of val1 with bits[31:16]
           of val2 levitated with the val3.
  \details Combine a halfword from one register with a halfword from another register.
           The second argument can be left-shifted before extraction of the halfword.
  \param [in]    val1   first 16-bit operands
  \param [in]    val2   second 16-bit operands
  \param [in]    val3   value for left-shifting val2. Value range [0..31].
  \return               the combination of halfwords.
  \remark
                 res[15:0]  = val1[15:0]              \n
                 res[31:16] = val2[31:16] << val3
 */
__ALWAYS_STATIC_INLINE uint32_t __PKHBT(uint32_t val1, uint32_t val2, uint32_t val3)
{
    return ((((int32_t)(val1) << 0) & (int32_t)0x0000FFFF) | (((int32_t)(val2) << val3) & (int32_t)0xFFFF0000));
}

/**
  \brief   Halfword packing instruction. Combines bits[31:16] of val1 with bits[15:0]
           of val2 right-shifted with the val3.
  \details Combine a halfword from one register with a halfword from another register.
           The second argument can be right-shifted before extraction of the halfword.
  \param [in]    val1   first 16-bit operands
  \param [in]    val2   second 16-bit operands
  \param [in]    val3   value for right-shifting val2. Value range [1..32].
  \return               the combination of halfwords.
  \remark
                 res[15:0]  = val2[15:0] >> val3        \n
                 res[31:16] = val1[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __PKHTB(uint32_t val1, uint32_t val2, uint32_t val3)
{
    return ((((int32_t)(val1) << 0) & (int32_t)0xFFFF0000) | (((int32_t)(val2) >> val3) & (int32_t)0x0000FFFF));
}

/**
  \brief   Dual 16-bit signed saturate.
  \details This function saturates a signed value.
  \param [in]    x   two signed 16-bit values to be saturated.
  \param [in]    y   bit position for saturation, an integral constant expression in the range 1 to 16.
  \return        the sum of the absolute differences of the following bytes, added to the accumulation value:\n
                 the signed saturation of the low halfword in val1, saturated to the bit position specified in
                 val2 and returned in the low halfword of the return value.\n
                 the signed saturation of the high halfword in val1, saturated to the bit position specified in
                 val2 and returned in the high halfword of the return value.
 */
__ALWAYS_STATIC_INLINE uint32_t __SSAT16(int32_t x, const uint32_t y)
{
    int32_t r = 0, s = 0;

    r = __SSAT((((int32_t)x << 16) >> 16), y) & (int32_t)0x0000FFFF;
    s = __SSAT((((int32_t)x) >> 16), y) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturate.
  \details This function enables you to saturate two signed 16-bit values to a selected unsigned range.
  \param [in]    x   two signed 16-bit values to be saturated.
  \param [in]    y   bit position for saturation, an integral constant expression in the range 1 to 16.
  \return        the saturation of the two signed 16-bit values, as non-negative values:
                 the saturation of the low halfword in val1, saturated to the bit position specified in
                 val2 and returned in the low halfword of the return value.\n
                 the saturation of the high halfword in val1, saturated to the bit position specified in
                 val2 and returned in the high halfword of the return value.
 */
__ALWAYS_STATIC_INLINE uint32_t __USAT16(uint32_t x, const uint32_t y)
{
    int32_t r = 0, s = 0;

    r = __IUSAT(((x << 16) >> 16), y) & 0x0000FFFF;
    s = __IUSAT(((x) >> 16), y) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Quad 8-bit saturating addition.
  \details This function enables you to perform four 8-bit integer additions,
           saturating the results to the 8-bit signed integer range -2^7 <= x <= 2^7 - 1.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the saturated addition of the first byte of each operand in the first byte of the return value.\n
                 the saturated addition of the second byte of each operand in the second byte of the return value.\n
                 the saturated addition of the third byte of each operand in the third byte of the return value.\n
                 the saturated addition of the fourth byte of each operand in the fourth byte of the return value.\n
                 The returned results are saturated to the 8-bit signed integer range -2^7 <= x <= 2^7 - 1.
  \remark
                 res[7:0]   = val1[7:0]   + val2[7:0]        \n
                 res[15:8]  = val1[15:8]  + val2[15:8]       \n
                 res[23:16] = val1[23:16] + val2[23:16]      \n
                 res[31:24] = val1[31:24] + val2[31:24]
 */
__ALWAYS_STATIC_INLINE uint32_t __QADD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = __SSAT(((((int32_t)x << 24) >> 24) + (((int32_t)y << 24) >> 24)), 8) & (int32_t)0x000000FF;
    s = __SSAT(((((int32_t)x << 16) >> 24) + (((int32_t)y << 16) >> 24)), 8) & (int32_t)0x000000FF;
    t = __SSAT(((((int32_t)x <<  8) >> 24) + (((int32_t)y <<  8) >> 24)), 8) & (int32_t)0x000000FF;
    u = __SSAT(((((int32_t)x) >> 24) + (((int32_t)y) >> 24)), 8) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned saturating addition.
  \details This function enables you to perform four unsigned 8-bit integer additions,
           saturating the results to the 8-bit unsigned integer range 0 < x < 2^8 - 1.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the saturated addition of the first byte of each operand in the first byte of the return value.\n
                 the saturated addition of the second byte of each operand in the second byte of the return value.\n
                 the saturated addition of the third byte of each operand in the third byte of the return value.\n
                 the saturated addition of the fourth byte of each operand in the fourth byte of the return value.\n
                 The returned results are saturated to the 8-bit signed integer range 0 <= x <= 2^8 - 1.
  \remark
                 res[7:0]   = val1[7:0]   + val2[7:0]        \n
                 res[15:8]  = val1[15:8]  + val2[15:8]       \n
                 res[23:16] = val1[23:16] + val2[23:16]      \n
                 res[31:24] = val1[31:24] + val2[31:24]
 */
__ALWAYS_STATIC_INLINE uint32_t __UQADD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = __IUSAT((((x << 24) >> 24) + ((y << 24) >> 24)), 8) & 0x000000FF;
    s = __IUSAT((((x << 16) >> 24) + ((y << 16) >> 24)), 8) & 0x000000FF;
    t = __IUSAT((((x <<  8) >> 24) + ((y <<  8) >> 24)), 8) & 0x000000FF;
    u = __IUSAT((((x) >> 24) + ((y) >> 24)), 8) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Quad 8-bit signed addition.
  \details This function performs four 8-bit signed integer additions.
  \param [in]    x  first four 8-bit summands.
  \param [in]    y  second four 8-bit summands.
  \return        the addition of the first bytes from each operand, in the first byte of the return value.\n
                 the addition of the second bytes of each operand, in the second byte of the return value.\n
                 the addition of the third bytes of each operand, in the third byte of the return value.\n
                 the addition of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = val1[7:0]   + val2[7:0]        \n
                 res[15:8]  = val1[15:8]  + val2[15:8]       \n
                 res[23:16] = val1[23:16] + val2[23:16]      \n
                 res[31:24] = val1[31:24] + val2[31:24]
 */
__ALWAYS_STATIC_INLINE uint32_t __SADD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = ((((int32_t)x << 24) >> 24) + (((int32_t)y << 24) >> 24)) & (int32_t)0x000000FF;
    s = ((((int32_t)x << 16) >> 24) + (((int32_t)y << 16) >> 24)) & (int32_t)0x000000FF;
    t = ((((int32_t)x <<  8) >> 24) + (((int32_t)y <<  8) >> 24)) & (int32_t)0x000000FF;
    u = ((((int32_t)x) >> 24) + (((int32_t)y) >> 24)) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned addition.
  \details This function performs four unsigned 8-bit integer additions.
  \param [in]    x  first four 8-bit summands.
  \param [in]    y  second four 8-bit summands.
  \return        the addition of the first bytes from each operand, in the first byte of the return value.\n
                 the addition of the second bytes of each operand, in the second byte of the return value.\n
                 the addition of the third bytes of each operand, in the third byte of the return value.\n
                 the addition of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = val1[7:0]   + val2[7:0]        \n
                 res[15:8]  = val1[15:8]  + val2[15:8]       \n
                 res[23:16] = val1[23:16] + val2[23:16]      \n
                 res[31:24] = val1[31:24] + val2[31:24]
 */
__ALWAYS_STATIC_INLINE uint32_t __UADD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = (((x << 24) >> 24) + ((y << 24) >> 24)) & 0x000000FF;
    s = (((x << 16) >> 24) + ((y << 16) >> 24)) & 0x000000FF;
    t = (((x <<  8) >> 24) + ((y <<  8) >> 24)) & 0x000000FF;
    u = (((x) >> 24) + ((y) >> 24)) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Quad 8-bit saturating subtract.
  \details This function enables you to perform four 8-bit integer subtractions,
           saturating the results to the 8-bit signed integer range -2^7 <= x <= 2^7 - 1.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the subtraction of the first byte of each operand in the first byte of the return value.\n
                 the subtraction of the second byte of each operand in the second byte of the return value.\n
                 the subtraction of the third byte of each operand in the third byte of the return value.\n
                 the subtraction of the fourth byte of each operand in the fourth byte of the return value.\n
                 The returned results are saturated to the 8-bit signed integer range -2^7 <= x <= 2^7 - 1.
  \remark
                 res[7:0]   = val1[7:0]   - val2[7:0]        \n
                 res[15:8]  = val1[15:8]  - val2[15:8]       \n
                 res[23:16] = val1[23:16] - val2[23:16]      \n
                 res[31:24] = val1[31:24] - val2[31:24]
 */
__ALWAYS_STATIC_INLINE uint32_t __QSUB8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = __SSAT(((((int32_t)x << 24) >> 24) - (((int32_t)y << 24) >> 24)), 8) & (int32_t)0x000000FF;
    s = __SSAT(((((int32_t)x << 16) >> 24) - (((int32_t)y << 16) >> 24)), 8) & (int32_t)0x000000FF;
    t = __SSAT(((((int32_t)x <<  8) >> 24) - (((int32_t)y <<  8) >> 24)), 8) & (int32_t)0x000000FF;
    u = __SSAT(((((int32_t)x) >> 24) - (((int32_t)y) >> 24)), 8) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned saturating subtraction.
  \details This function enables you to perform four unsigned 8-bit integer subtractions,
           saturating the results to the 8-bit unsigned integer range 0 < x < 2^8 - 1.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the subtraction of the first byte of each operand in the first byte of the return value.\n
                 the subtraction of the second byte of each operand in the second byte of the return value.\n
                 the subtraction of the third byte of each operand in the third byte of the return value.\n
                 the subtraction of the fourth byte of each operand in the fourth byte of the return value.\n
                 The returned results are saturated to the 8-bit unsigned integer range 0 <= x <= 2^8 - 1.
  \remark
                 res[7:0]   = val1[7:0]   - val2[7:0]        \n
                 res[15:8]  = val1[15:8]  - val2[15:8]       \n
                 res[23:16] = val1[23:16] - val2[23:16]      \n
                 res[31:24] = val1[31:24] - val2[31:24]
 */
__ALWAYS_STATIC_INLINE uint32_t __UQSUB8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = __IUSAT((((x << 24) >> 24) - ((y << 24) >> 24)), 8) & 0x000000FF;
    s = __IUSAT((((x << 16) >> 24) - ((y << 16) >> 24)), 8) & 0x000000FF;
    t = __IUSAT((((x <<  8) >> 24) - ((y <<  8) >> 24)), 8) & 0x000000FF;
    u = __IUSAT((((x) >> 24) - ((y) >> 24)), 8) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Quad 8-bit signed subtraction.
  \details This function enables you to perform four 8-bit signed integer subtractions.
  \param [in]    x  first four 8-bit operands of each subtraction.
  \param [in]    y  second four 8-bit operands of each subtraction.
  \return        the subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the subtraction of the second bytes of each operand, in the second byte of the return value.\n
                 the subtraction of the third bytes of each operand, in the third byte of the return value.\n
                 the subtraction of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = val1[7:0]   - val2[7:0]        \n
                 res[15:8]  = val1[15:8]  - val2[15:8]       \n
                 res[23:16] = val1[23:16] - val2[23:16]      \n
                 res[31:24] = val1[31:24] - val2[31:24]
 */
__ALWAYS_STATIC_INLINE uint32_t __SSUB8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = ((((int32_t)x << 24) >> 24) - (((int32_t)y << 24) >> 24)) & (int32_t)0x000000FF;
    s = ((((int32_t)x << 16) >> 24) - (((int32_t)y << 16) >> 24)) & (int32_t)0x000000FF;
    t = ((((int32_t)x <<  8) >> 24) - (((int32_t)y <<  8) >> 24)) & (int32_t)0x000000FF;
    u = ((((int32_t)x) >> 24) - (((int32_t)y) >> 24)) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned subtract.
  \details This function enables you to perform four 8-bit unsigned integer subtractions.
  \param [in]    x  first four 8-bit operands of each subtraction.
  \param [in]    y  second four 8-bit operands of each subtraction.
  \return        the subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the subtraction of the second bytes of each operand, in the second byte of the return value.\n
                 the subtraction of the third bytes of each operand, in the third byte of the return value.\n
                 the subtraction of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = val1[7:0]   - val2[7:0]        \n
                 res[15:8]  = val1[15:8]  - val2[15:8]       \n
                 res[23:16] = val1[23:16] - val2[23:16]      \n
                 res[31:24] = val1[31:24] - val2[31:24]
 */
__ALWAYS_STATIC_INLINE uint32_t __USUB8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = (((x << 24) >> 24) - ((y << 24) >> 24)) & 0x000000FF;
    s = (((x << 16) >> 24) - ((y << 16) >> 24)) & 0x000000FF;
    t = (((x <<  8) >> 24) - ((y <<  8) >> 24)) & 0x000000FF;
    u = (((x) >> 24) - ((y) >> 24)) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Unsigned sum of quad 8-bit unsigned absolute difference.
  \details This function enables you to perform four unsigned 8-bit subtractions, and add the absolute values
           of the differences together, returning the result as a single unsigned integer.
  \param [in]    x  first four 8-bit operands of each subtraction.
  \param [in]    y  second four 8-bit operands of each subtraction.
  \return        the subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the subtraction of the second bytes of each operand, in the second byte of the return value.\n
                 the subtraction of the third bytes of each operand, in the third byte of the return value.\n
                 the subtraction of the fourth bytes of each operand, in the fourth byte of the return value.\n
                 The sum is returned as a single unsigned integer.
  \remark
                 absdiff1   = val1[7:0]   - val2[7:0]        \n
                 absdiff2   = val1[15:8]  - val2[15:8]       \n
                 absdiff3   = val1[23:16] - val2[23:16]      \n
                 absdiff4   = val1[31:24] - val2[31:24]      \n
                 res[31:0]  = absdiff1 + absdiff2 + absdiff3 + absdiff4
 */
__ALWAYS_STATIC_INLINE uint32_t __USAD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = (((x << 24) >> 24) - ((y << 24) >> 24)) & 0x000000FF;
    s = (((x << 16) >> 24) - ((y << 16) >> 24)) & 0x000000FF;
    t = (((x <<  8) >> 24) - ((y <<  8) >> 24)) & 0x000000FF;
    u = (((x) >> 24) - ((y) >> 24)) & 0x000000FF;

    return (u + t + s + r);
}

/**
  \brief   Unsigned sum of quad 8-bit unsigned absolute difference with 32-bit accumulate.
  \details This function enables you to perform four unsigned 8-bit subtractions, and add the absolute values
           of the differences to a 32-bit accumulate operand.
  \param [in]    x  first four 8-bit operands of each subtraction.
  \param [in]    y  second four 8-bit operands of each subtraction.
  \param [in]  sum  accumulation value.
  \return        the sum of the absolute differences of the following bytes, added to the accumulation value:
                 the subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the subtraction of the second bytes of each operand, in the second byte of the return value.\n
                 the subtraction of the third bytes of each operand, in the third byte of the return value.\n
                 the subtraction of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 absdiff1 = val1[7:0]   - val2[7:0]        \n
                 absdiff2 = val1[15:8]  - val2[15:8]       \n
                 absdiff3 = val1[23:16] - val2[23:16]      \n
                 absdiff4 = val1[31:24] - val2[31:24]      \n
                 sum = absdiff1 + absdiff2 + absdiff3 + absdiff4 \n
                 res[31:0] = sum[31:0] + val3[31:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __USADA8(uint32_t x, uint32_t y, uint32_t sum)
{
    int32_t r, s, t, u;

#ifdef __cplusplus
    r = (abs((long long)((x << 24) >> 24) - ((y << 24) >> 24))) & 0x000000FF;
    s = (abs((long long)((x << 16) >> 24) - ((y << 16) >> 24))) & 0x000000FF;
    t = (abs((long long)((x <<  8) >> 24) - ((y <<  8) >> 24))) & 0x000000FF;
    u = (abs((long long)((x) >> 24) - ((y) >> 24))) & 0x000000FF;
#else
    r = (abs(((x << 24) >> 24) - ((y << 24) >> 24))) & 0x000000FF;
    s = (abs(((x << 16) >> 24) - ((y << 16) >> 24))) & 0x000000FF;
    t = (abs(((x <<  8) >> 24) - ((y <<  8) >> 24))) & 0x000000FF;
    u = (abs(((x) >> 24) - ((y) >> 24))) & 0x000000FF;
#endif
    return (u + t + s + r + sum);
}

/**
  \brief   Dual 16-bit saturating addition.
  \details This function enables you to perform two 16-bit integer arithmetic additions in parallel,
           saturating the results to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the saturated addition of the low halfwords, in the low halfword of the return value.\n
                 the saturated addition of the high halfwords, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  + val2[15:0]        \n
                 res[31:16] = val1[31:16] + val2[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __QADD16(uint32_t x, uint32_t y)
{
    int32_t r = 0, s = 0;

    r = __SSAT(((((int32_t)x << 16) >> 16) + (((int32_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((int32_t)x) >> 16) + (((int32_t)y) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturating addition.
  \details This function enables you to perform two unsigned 16-bit integer additions, saturating
           the results to the 16-bit unsigned integer range 0 < x < 2^16 - 1.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the saturated addition of the low halfwords, in the low halfword of the return value.\n
                 the saturated addition of the high halfwords, in the high halfword of the return value.\n
                 The results are saturated to the 16-bit unsigned integer range 0 < x < 2^16 - 1.
  \remark
                 res[15:0]  = val1[15:0]  + val2[15:0]        \n
                 res[31:16] = val1[31:16] + val2[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __UQADD16(uint32_t x, uint32_t y)
{
    int32_t r = 0, s = 0;

    r = __IUSAT((((x << 16) >> 16) + ((y << 16) >> 16)), 16) & 0x0000FFFF;
    s = __IUSAT((((x) >> 16) + ((y) >> 16)), 16) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed addition.
  \details This function enables you to perform two 16-bit signed integer additions.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the addition of the low halfwords in the low halfword of the return value.\n
                 the addition of the high halfwords in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  + val2[15:0]        \n
                 res[31:16] = val1[31:16] + val2[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __SADD16(uint32_t x, uint32_t y)
{
    int32_t r = 0, s = 0;

    r = ((((int32_t)x << 16) >> 16) + (((int32_t)y << 16) >> 16)) & (int32_t)0x0000FFFF;
    s = ((((int32_t)x) >> 16) + (((int32_t)y) >> 16)) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned addition
  \details This function enables you to perform two 16-bit unsigned integer additions.
  \param [in]    x   first two 16-bit summands for each addition.
  \param [in]    y   second two 16-bit summands for each addition.
  \return        the addition of the low halfwords in the low halfword of the return value.\n
                 the addition of the high halfwords in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  + val2[15:0]        \n
                 res[31:16] = val1[31:16] + val2[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __UADD16(uint32_t x, uint32_t y)
{
    int32_t r = 0, s = 0;

    r = (((x << 16) >> 16) + ((y << 16) >> 16)) & 0x0000FFFF;
    s = (((x) >> 16) + ((y) >> 16)) & 0x0000FFFF;

    return ((s << 16) | (r));
}


/**
  \brief   Dual 16-bit signed addition with halved results.
  \details This function enables you to perform two signed 16-bit integer additions, halving the results.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the halved addition of the low halfwords, in the low halfword of the return value.\n
                 the halved addition of the high halfwords, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  + val2[15:0]) >> 1        \n
                 res[31:16] = (val1[31:16] + val2[31:16]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __SHADD16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((((int32_t)x << 16) >> 16) + (((int32_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((int32_t)x) >> 16) + (((int32_t)y) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned addition with halved results.
  \details This function enables you to perform two unsigned 16-bit integer additions, halving the results.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the halved addition of the low halfwords, in the low halfword of the return value.\n
                 the halved addition of the high halfwords, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  + val2[15:0]) >> 1        \n
                 res[31:16] = (val1[31:16] + val2[31:16]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __UHADD16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((x << 16) >> 16) + ((y << 16) >> 16)) >> 1) & 0x0000FFFF;
    s = ((((x) >> 16) + ((y) >> 16)) >> 1) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Quad 8-bit signed addition with halved results.
  \details This function enables you to perform four signed 8-bit integer additions, halving the results.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the halved addition of the first bytes from each operand, in the first byte of the return value.\n
                 the halved addition of the second bytes from each operand, in the second byte of the return value.\n
                 the halved addition of the third bytes from each operand, in the third byte of the return value.\n
                 the halved addition of the fourth bytes from each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = (val1[7:0]   + val2[7:0]  ) >> 1    \n
                 res[15:8]  = (val1[15:8]  + val2[15:8] ) >> 1    \n
                 res[23:16] = (val1[23:16] + val2[23:16]) >> 1    \n
                 res[31:24] = (val1[31:24] + val2[31:24]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __SHADD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = (((((int32_t)x << 24) >> 24) + (((int32_t)y << 24) >> 24)) >> 1) & (int32_t)0x000000FF;
    s = (((((int32_t)x << 16) >> 24) + (((int32_t)y << 16) >> 24)) >> 1) & (int32_t)0x000000FF;
    t = (((((int32_t)x <<  8) >> 24) + (((int32_t)y <<  8) >> 24)) >> 1) & (int32_t)0x000000FF;
    u = (((((int32_t)x) >> 24) + (((int32_t)y) >> 24)) >> 1) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned addition with halved results.
  \details This function enables you to perform four unsigned 8-bit integer additions, halving the results.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the halved addition of the first bytes from each operand, in the first byte of the return value.\n
                 the halved addition of the second bytes from each operand, in the second byte of the return value.\n
                 the halved addition of the third bytes from each operand, in the third byte of the return value.\n
                 the halved addition of the fourth bytes from each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = (val1[7:0]   + val2[7:0]  ) >> 1    \n
                 res[15:8]  = (val1[15:8]  + val2[15:8] ) >> 1    \n
                 res[23:16] = (val1[23:16] + val2[23:16]) >> 1    \n
                 res[31:24] = (val1[31:24] + val2[31:24]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __UHADD8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = ((((x << 24) >> 24) + ((y << 24) >> 24)) >> 1) & 0x000000FF;
    s = ((((x << 16) >> 24) + ((y << 16) >> 24)) >> 1) & 0x000000FF;
    t = ((((x <<  8) >> 24) + ((y <<  8) >> 24)) >> 1) & 0x000000FF;
    u = ((((x) >> 24) + ((y) >> 24)) >> 1) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Dual 16-bit saturating subtract.
  \details This function enables you to perform two 16-bit integer subtractions in parallel,
           saturating the results to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the saturated subtraction of the low halfwords, in the low halfword of the return value.\n
                 the saturated subtraction of the high halfwords, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  - val2[15:0]        \n
                 res[31:16] = val1[31:16] - val2[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __QSUB16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = __SSAT(((((int32_t)x << 16) >> 16) - (((int32_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((int32_t)x) >> 16) - (((int32_t)y) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturating subtraction.
  \details This function enables you to perform two unsigned 16-bit integer subtractions,
           saturating the results to the 16-bit unsigned integer range 0 < x < 2^16 - 1.
  \param [in]    x   first two 16-bit operands for each subtraction.
  \param [in]    y   second two 16-bit operands for each subtraction.
  \return        the saturated subtraction of the low halfwords, in the low halfword of the return value.\n
                 the saturated subtraction of the high halfwords, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  - val2[15:0]        \n
                 res[31:16] = val1[31:16] - val2[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __UQSUB16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = __IUSAT((((x << 16) >> 16) - ((y << 16) >> 16)), 16) & 0x0000FFFF;
    s = __IUSAT((((x) >> 16) - ((y) >> 16)), 16) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed subtraction.
  \details This function enables you to perform two 16-bit signed integer subtractions.
  \param [in]    x   first two 16-bit operands of each subtraction.
  \param [in]    y   second two 16-bit operands of each subtraction.
  \return        the subtraction of the low halfword in the second operand from the low
                 halfword in the first operand, in the low halfword of the return value. \n
                 the subtraction of the high halfword in the second operand from the high
                 halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  - val2[15:0]        \n
                 res[31:16] = val1[31:16] - val2[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __SSUB16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((int32_t)x << 16) >> 16) - (((int32_t)y << 16) >> 16)) & (int32_t)0x0000FFFF;
    s = ((((int32_t)x) >> 16) - (((int32_t)y) >> 16)) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned subtract.
  \details This function enables you to perform two 16-bit unsigned integer subtractions.
  \param [in]    x   first two 16-bit operands of each subtraction.
  \param [in]    y   second two 16-bit operands of each subtraction.
  \return        the subtraction of the low halfword in the second operand from the low
                 halfword in the first operand, in the low halfword of the return value. \n
                 the subtraction of the high halfword in the second operand from the high
                 halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  - val2[15:0]        \n
                 res[31:16] = val1[31:16] - val2[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __USUB16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((x << 16) >> 16) - ((y << 16) >> 16)) & 0x0000FFFF;
    s = (((x) >> 16) - ((y) >> 16)) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed subtraction with halved results.
  \details This function enables you to perform two signed 16-bit integer subtractions, halving the results.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the halved subtraction of the low halfwords, in the low halfword of the return value.\n
                 the halved subtraction of the high halfwords, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  - val2[15:0]) >> 1        \n
                 res[31:16] = (val1[31:16] - val2[31:16]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __SHSUB16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((((int32_t)x << 16) >> 16) - (((int32_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((int32_t)x) >> 16) - (((int32_t)y) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned subtraction with halved results.
  \details This function enables you to perform two unsigned 16-bit integer subtractions, halving the results.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the halved subtraction of the low halfwords, in the low halfword of the return value.\n
                 the halved subtraction of the high halfwords, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  - val2[15:0]) >> 1        \n
                 res[31:16] = (val1[31:16] - val2[31:16]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __UHSUB16(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((x << 16) >> 16) - ((y << 16) >> 16)) >> 1) & 0x0000FFFF;
    s = ((((x) >> 16) - ((y) >> 16)) >> 1) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Quad 8-bit signed addition with halved results.
  \details This function enables you to perform four signed 8-bit integer subtractions, halving the results.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the halved subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the halved subtraction of the second bytes from each operand, in the second byte of the return value.\n
                 the halved subtraction of the third bytes from each operand, in the third byte of the return value.\n
                 the halved subtraction of the fourth bytes from each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = (val1[7:0]   - val2[7:0]  ) >> 1    \n
                 res[15:8]  = (val1[15:8]  - val2[15:8] ) >> 1    \n
                 res[23:16] = (val1[23:16] - val2[23:16]) >> 1    \n
                 res[31:24] = (val1[31:24] - val2[31:24]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __SHSUB8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = (((((int32_t)x << 24) >> 24) - (((int32_t)y << 24) >> 24)) >> 1) & (int32_t)0x000000FF;
    s = (((((int32_t)x << 16) >> 24) - (((int32_t)y << 16) >> 24)) >> 1) & (int32_t)0x000000FF;
    t = (((((int32_t)x <<  8) >> 24) - (((int32_t)y <<  8) >> 24)) >> 1) & (int32_t)0x000000FF;
    u = (((((int32_t)x) >> 24) - (((int32_t)y) >> 24)) >> 1) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned subtraction with halved results.
  \details This function enables you to perform four unsigned 8-bit integer subtractions, halving the results.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the halved subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the halved subtraction of the second bytes from each operand, in the second byte of the return value.\n
                 the halved subtraction of the third bytes from each operand, in the third byte of the return value.\n
                 the halved subtraction of the fourth bytes from each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = (val1[7:0]   - val2[7:0]  ) >> 1    \n
                 res[15:8]  = (val1[15:8]  - val2[15:8] ) >> 1    \n
                 res[23:16] = (val1[23:16] - val2[23:16]) >> 1    \n
                 res[31:24] = (val1[31:24] - val2[31:24]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __UHSUB8(uint32_t x, uint32_t y)
{
    int32_t r, s, t, u;

    r = ((((x << 24) >> 24) - ((y << 24) >> 24)) >> 1) & 0x000000FF;
    s = ((((x << 16) >> 24) - ((y << 16) >> 24)) >> 1) & 0x000000FF;
    t = ((((x <<  8) >> 24) - ((y <<  8) >> 24)) >> 1) & 0x000000FF;
    u = ((((x) >> 24) - ((y) >> 24)) >> 1) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Dual 16-bit add and subtract with exchange.
  \details This function enables you to exchange the halfwords of the one operand,
           then add the high halfwords and subtract the low halfwords,
           saturating the results to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \param [in]    x   first operand for the subtraction in the low halfword,
                     and the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword,
                     and the second operand for the addition in the low halfword.
  \return        the saturated subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the saturated addition of the high halfword in the first operand and the
                 low halfword in the second operand, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  - val2[31:16]        \n
                 res[31:16] = val1[31:16] + val2[15:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __QASX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = __SSAT(((((int32_t)x << 16) >> 16) - (((int32_t)y) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((int32_t)x) >> 16) + (((int32_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturating addition and subtraction with exchange.
  \details This function enables you to exchange the halfwords of the second operand and
           perform one unsigned 16-bit integer addition and one unsigned 16-bit subtraction,
           saturating the results to the 16-bit unsigned integer range 0 <= x <= 2^16 - 1.
  \param [in]    x   first operand for the subtraction in the low halfword,
                     and the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword,
                     and the second operand for the addition in the low halfword.
  \return        the saturated subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the saturated addition of the high halfword in the first operand and the
                 low halfword in the second operand, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit unsigned integer range 0 <= x <= 2^16 - 1.
  \remark
                 res[15:0]  = val1[15:0]  - val2[31:16]        \n
                 res[31:16] = val1[31:16] + val2[15:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __UQASX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = __IUSAT((((x << 16) >> 16) - ((y) >> 16)), 16) & 0x0000FFFF;
    s = __IUSAT((((x) >> 16) + ((y << 16) >> 16)), 16) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit addition and subtraction with exchange.
  \details It enables you to exchange the halfwords of the second operand, add the high halfwords
           and subtract the low halfwords.
  \param [in]    x   first operand for the subtraction in the low halfword,
                     and the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword,
                     and the second operand for the addition in the low halfword.
  \return        the subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the addition of the high halfword in the first operand and the
                 low halfword in the second operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  - val2[31:16]        \n
                 res[31:16] = val1[31:16] + val2[15:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __SASX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((int32_t)x << 16) >> 16) - (((int32_t)y) >> 16)) & (int32_t)0x0000FFFF;
    s = ((((int32_t)x) >> 16) + (((int32_t)y << 16) >> 16)) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned addition and subtraction with exchange.
  \details This function enables you to exchange the two halfwords of the second operand,
           add the high halfwords and subtract the low halfwords.
  \param [in]    x   first operand for the subtraction in the low halfword,
                     and the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword,
                     and the second operand for the addition in the low halfword.
  \return        the subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the addition of the high halfword in the first operand and the
                 low halfword in the second operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  - val2[31:16]        \n
                 res[31:16] = val1[31:16] + val2[15:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __UASX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((x << 16) >> 16) - ((y) >> 16)) & 0x0000FFFF;
    s = (((x) >> 16) + ((y << 16) >> 16)) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed addition and subtraction with halved results.
  \details This function enables you to exchange the two halfwords of one operand, perform one
           signed 16-bit integer addition and one signed 16-bit subtraction, and halve the results.
  \param [in]    x   first 16-bit operands.
  \param [in]    y   second 16-bit operands.
  \return        the halved subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the halved addition of the low halfword in the second operand from the high
                 halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  - val2[31:16]) >> 1        \n
                 res[31:16] = (val1[31:16] + val2[15:0]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __SHASX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((((int32_t)x << 16) >> 16) - (((int32_t)y) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((int32_t)x) >> 16) + (((int32_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned addition and subtraction with halved results and exchange.
  \details This function enables you to exchange the halfwords of the second operand,
           add the high halfwords and subtract the low halfwords, halving the results.
  \param [in]    x   first operand for the subtraction in the low halfword, and
                     the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword, and
                     the second operand for the addition in the low halfword.
  \return        the halved subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the halved addition of the low halfword in the second operand from the high
                 halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  - val2[31:16]) >> 1        \n
                 res[31:16] = (val1[31:16] + val2[15:0]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __UHASX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((x << 16) >> 16) - ((y) >> 16)) >> 1) & 0x0000FFFF;
    s = ((((x) >> 16) + ((y << 16) >> 16)) >> 1) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit subtract and add with exchange.
  \details This function enables you to exchange the halfwords of one operand,
           then subtract the high halfwords and add the low halfwords,
           saturating the results to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \param [in]    x   first operand for the addition in the low halfword,
                     and the first operand for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword,
                     and the second operand for the subtraction in the low halfword.
  \return        the saturated addition of the low halfword of the first operand and the high
                 halfword of the second operand, in the low halfword of the return value.\n
                 the saturated subtraction of the low halfword of the second operand from the
                 high halfword of the first operand, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  + val2[31:16]        \n
                 res[31:16] = val1[31:16] - val2[15:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __QSAX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = __SSAT(((((int32_t)x << 16) >> 16) + (((int32_t)y) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((int32_t)x) >> 16) - (((int32_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturating subtraction and addition with exchange.
  \details This function enables you to exchange the halfwords of the second operand and perform
           one unsigned 16-bit integer subtraction and one unsigned 16-bit addition, saturating
           the results to the 16-bit unsigned integer range 0 <= x <= 2^16 - 1.
  \param [in]    x   first operand for the addition in the low halfword,
                     and the first operand for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword,
                     and the second operand for the subtraction in the low halfword.
  \return        the saturated addition of the low halfword of the first operand and the high
                 halfword of the second operand, in the low halfword of the return value.\n
                 the saturated subtraction of the low halfword of the second operand from the
                 high halfword of the first operand, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit unsigned integer range 0 <= x <= 2^16 - 1.
  \remark
                 res[15:0]  = val1[15:0]  + val2[31:16]        \n
                 res[31:16] = val1[31:16] - val2[15:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __UQSAX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = __IUSAT((((x << 16) >> 16) + ((y) >> 16)), 16) & 0x0000FFFF;
    s = __IUSAT((((x) >> 16) - ((y << 16) >> 16)), 16) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit unsigned subtract and add with exchange.
  \details This function enables you to exchange the halfwords of the second operand,
           subtract the high halfwords and add the low halfwords.
  \param [in]    x   first operand for the addition in the low halfword,
                     and the first operand for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword,
                     and the second operand for the subtraction in the low halfword.
  \return        the addition of the low halfword of the first operand and the high
                 halfword of the second operand, in the low halfword of the return value.\n
                 the subtraction of the low halfword of the second operand from the
                 high halfword of the first operand, in the high halfword of the return value.\n
  \remark
                 res[15:0]  = val1[15:0]  + val2[31:16]        \n
                 res[31:16] = val1[31:16] - val2[15:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __USAX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((x << 16) >> 16) + ((y) >> 16)) & 0x0000FFFF;
    s = (((x) >> 16) - ((y << 16) >> 16)) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed subtraction and addition with exchange.
  \details This function enables you to exchange the two halfwords of one operand and perform one
           16-bit integer subtraction and one 16-bit addition.
  \param [in]    x   first operand for the addition in the low halfword, and the first operand
                     for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword, and the second
                     operand for the subtraction in the low halfword.
  \return        the addition of the low halfword of the first operand and the high
                 halfword of the second operand, in the low halfword of the return value.\n
                 the subtraction of the low halfword of the second operand from the
                 high halfword of the first operand, in the high halfword of the return value.\n
  \remark
                 res[15:0]  = val1[15:0]  + val2[31:16]        \n
                 res[31:16] = val1[31:16] - val2[15:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __SSAX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((int32_t)x << 16) >> 16) + (((int32_t)y) >> 16)) & (int32_t)0x0000FFFF;
    s = ((((int32_t)x) >> 16) - (((int32_t)y << 16) >> 16)) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}


/**
  \brief   Dual 16-bit signed subtraction and addition with halved results.
  \details This function enables you to exchange the two halfwords of one operand, perform one signed
           16-bit integer subtraction and one signed 16-bit addition, and halve the results.
  \param [in]    x   first 16-bit operands.
  \param [in]    y   second 16-bit operands.
  \return        the halved addition of the low halfword in the first operand and the
                 high halfword in the second operand, in the low halfword of the return value.\n
                 the halved subtraction of the low halfword in the second operand from the
                 high halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  + val2[31:16]) >> 1        \n
                 res[31:16] = (val1[31:16] - val2[15:0]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __SHSAX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = (((((int32_t)x << 16) >> 16) + (((int32_t)y) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((int32_t)x) >> 16) - (((int32_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned subtraction and addition with halved results and exchange.
  \details This function enables you to exchange the halfwords of the second operand,
           subtract the high halfwords and add the low halfwords, halving the results.
  \param [in]    x   first operand for the addition in the low halfword, and
                     the first operand for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword, and
                     the second operand for the subtraction in the low halfword.
  \return        the halved addition of the low halfword in the first operand and the
                 high halfword in the second operand, in the low halfword of the return value.\n
                 the halved subtraction of the low halfword in the second operand from the
                 high halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  + val2[31:16]) >> 1        \n
                 res[31:16] = (val1[31:16] - val2[15:0]) >> 1
 */
__ALWAYS_STATIC_INLINE uint32_t __UHSAX(uint32_t x, uint32_t y)
{
    int32_t r, s;

    r = ((((x << 16) >> 16) + ((y) >> 16)) >> 1) & 0x0000FFFF;
    s = ((((x) >> 16) - ((y << 16) >> 16)) >> 1) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed multiply with exchange returning difference.
  \details This function enables you to perform two 16-bit signed multiplications, subtracting
           one of the products from the other. The halfwords of the second operand are exchanged
           before performing the arithmetic. This produces top * bottom and bottom * top multiplication.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \return        the difference of the products of the two 16-bit signed multiplications.
  \remark
                 p1 = val1[15:0]  * val2[31:16]       \n
                 p2 = val1[31:16] * val2[15:0]        \n
                 res[31:0] = p1 - p2
 */
__ALWAYS_STATIC_INLINE uint32_t __SMUSDX(uint32_t x, uint32_t y)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16))));
}

/**
  \brief   Sum of dual 16-bit signed multiply with exchange.
  \details This function enables you to perform two 16-bit signed multiplications with exchanged
           halfwords of the second operand, adding the products together.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \return        the sum of the products of the two 16-bit signed multiplications with exchanged halfwords of the second operand.
  \remark
                 p1 = val1[15:0]  * val2[31:16]       \n
                 p2 = val1[31:16] * val2[15:0]        \n
                 res[31:0] = p1 + p2
 */
__ALWAYS_STATIC_INLINE uint32_t __SMUADX(uint32_t x, uint32_t y)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16))));
}


/**
  \brief   Saturating add.
  \details This function enables you to obtain the saturating add of two integers.
  \param [in]    x   first summand of the saturating add operation.
  \param [in]    y   second summand of the saturating add operation.
  \return        the saturating addition of val1 and val2.
  \remark
                 res[31:0] = SAT(val1 + SAT(val2))
 */
__ALWAYS_STATIC_INLINE int32_t __QADD(int32_t x, int32_t y)
{
    int32_t result;

    if (y >= 0) {
        if ((int32_t)((uint32_t)x + (uint32_t)y) >= x) {
            result = x + y;
        } else {
            result = 0x7FFFFFFF;
        }
    } else {
        if ((int32_t)((uint32_t)x + (uint32_t)y) < x) {
            result = x + y;
        } else {
            result = 0x80000000;
        }
    }

    return result;
}

/**
  \brief   Saturating subtract.
  \details This function enables you to obtain the saturating add of two integers.
  \param [in]    x   first summand of the saturating add operation.
  \param [in]    y   second summand of the saturating add operation.
  \return        the saturating addition of val1 and val2.
  \remark
                 res[31:0] = SAT(val1 - SAT(val2))
 */
__ALWAYS_STATIC_INLINE int32_t __QSUB(int32_t x, int32_t y)
{
    int64_t tmp;
    int32_t result;

    tmp = (int64_t)x - (int64_t)y;

    if (tmp > 0x7fffffff) {
        tmp = 0x7fffffff;
    } else if (tmp < (-2147483647 - 1)) {
        tmp = -2147483647 - 1;
    }

    result = tmp;
    return result;
}

/**
  \brief   Dual 16-bit signed multiply with single 32-bit accumulator.
  \details This function enables you to perform two signed 16-bit multiplications,
           adding both results to a 32-bit accumulate operand.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of each multiplication added to the accumulate value, as a 32-bit integer.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 res[31:0] = p1 + p2 + val3[31:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __SMLAD(uint32_t x, uint32_t y, uint32_t sum)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16)) +
                       (((int32_t)sum))));
}

/**
  \brief   Pre-exchanged dual 16-bit signed multiply with single 32-bit accumulator.
  \details This function enables you to perform two signed 16-bit multiplications with exchanged
           halfwords of the second operand, adding both results to a 32-bit accumulate operand.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of each multiplication with exchanged halfwords of the second
                 operand added to the accumulate value, as a 32-bit integer.
  \remark
                 p1 = val1[15:0]  * val2[31:16]     \n
                 p2 = val1[31:16] * val2[15:0]      \n
                 res[31:0] = p1 + p2 + val3[31:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __SMLADX(uint32_t x, uint32_t y, uint32_t sum)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16)) +
                       (((int32_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with exchange subtract with 32-bit accumulate.
  \details This function enables you to perform two 16-bit signed multiplications, take the
           difference of the products, subtracting the high halfword product from the low
           halfword product, and add the difference to a 32-bit accumulate operand.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the difference of the product of each multiplication, added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[15:0]       \n
                 p2 = val1[31:16] * val2[31:16]      \n
                 res[31:0] = p1 - p2 + val3[31:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __SMLSD(uint32_t x, uint32_t y, uint32_t sum)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16)) +
                       (((int32_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with exchange subtract with 32-bit accumulate.
  \details This function enables you to exchange the halfwords in the second operand, then perform two 16-bit
           signed multiplications. The difference of the products is added to a 32-bit accumulate operand.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the difference of the product of each multiplication, added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[31:16]     \n
                 p2 = val1[31:16] * val2[15:0]      \n
                 res[31:0] = p1 - p2 + val3[31:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __SMLSDX(uint32_t x, uint32_t y, uint32_t sum)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16)) +
                       (((int32_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with single 64-bit accumulator.
  \details This function enables you to perform two signed 16-bit multiplications, adding both results
           to a 64-bit accumulate operand. Overflow is only possible as a result of the 64-bit addition.
           This overflow is not detected if it occurs. Instead, the result wraps around modulo2^64.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of each multiplication added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 sum = p1 + p2 + val3[63:32][31:0]  \n
                 res[63:32] = sum[63:32]            \n
                 res[31:0]  = sum[31:0]
 */
__ALWAYS_STATIC_INLINE uint64_t __SMLALD(uint32_t x, uint32_t y, uint64_t sum)
{
    return ((uint64_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16)) +
                       (((uint64_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with exchange with single 64-bit accumulator.
  \details This function enables you to exchange the halfwords of the second operand, and perform two
           signed 16-bit multiplications, adding both results to a 64-bit accumulate operand. Overflow
           is only possible as a result of the 64-bit addition. This overflow is not detected if it occurs.
           Instead, the result wraps around modulo2^64.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of each multiplication added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[31:16]     \n
                 p2 = val1[31:16] * val2[15:0]      \n
                 sum = p1 + p2 + val3[63:32][31:0]  \n
                 res[63:32] = sum[63:32]            \n
                 res[31:0]  = sum[31:0]
 */
__ALWAYS_STATIC_INLINE uint64_t __SMLALDX(uint32_t x, uint32_t y, uint64_t sum)
{
    return ((uint64_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16)) +
                       (((uint64_t)sum))));
}

/**
  \brief   dual 16-bit signed multiply subtract with 64-bit accumulate.
  \details This function It enables you to perform two 16-bit signed multiplications, take the difference
           of the products, subtracting the high halfword product from the low halfword product, and add the
           difference to a 64-bit accumulate operand. Overflow cannot occur during the multiplications or the
           subtraction. Overflow can occur as a result of the 64-bit addition, and this overflow is not
           detected. Instead, the result wraps round to modulo2^64.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the difference of the product of each multiplication, added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 res[63:32][31:0] = p1 - p2 + val3[63:32][31:0]
 */
__ALWAYS_STATIC_INLINE uint64_t __SMLSLD(uint32_t x, uint32_t y, uint64_t sum)
{
    return ((uint64_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16)) +
                       (((uint64_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with exchange subtract with 64-bit accumulate.
  \details This function enables you to exchange the halfwords of the second operand, perform two 16-bit multiplications,
           adding the difference of the products to a 64-bit accumulate operand. Overflow cannot occur during the
           multiplications or the subtraction. Overflow can occur as a result of the 64-bit addition, and this overflow
           is not detected. Instead, the result wraps round to modulo2^64.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the difference of the product of each multiplication, added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[31:16]      \n
                 p2 = val1[31:16] * val2[15:0]       \n
                 res[63:32][31:0] = p1 - p2 + val3[63:32][31:0]
 */
__ALWAYS_STATIC_INLINE uint64_t __SMLSLDX(uint32_t x, uint32_t y, uint64_t sum)
{
    return ((uint64_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16)) +
                       (((uint64_t)sum))));
}

/**
  \brief   32-bit signed multiply with 32-bit truncated accumulator.
  \details This function enables you to perform a signed 32-bit multiplications, adding the most
           significant 32 bits of the 64-bit result to a 32-bit accumulate operand.
  \param [in]    x   first operand for multiplication.
  \param [in]    y   second operand for multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of multiplication (most significant 32 bits) is added to the accumulate value, as a 32-bit integer.
  \remark
                 p = val1 * val2      \n
                 res[31:0] = p[63:32] + val3[31:0]
 */
__ALWAYS_STATIC_INLINE uint32_t __SMMLA(int32_t x, int32_t y, int32_t sum)
{
    return (uint32_t)((int32_t)((int64_t)((int64_t)x * (int64_t)y) >> 32) + sum);
}

/**
  \brief   Sum of dual 16-bit signed multiply.
  \details This function enables you to perform two 16-bit signed multiplications, adding the products together.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \return        the sum of the products of the two 16-bit signed multiplications.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 res[31:0] = p1 + p2
 */
__ALWAYS_STATIC_INLINE uint32_t __SMUAD(uint32_t x, uint32_t y)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16))));
}

/**
  \brief   Dual 16-bit signed multiply returning difference.
  \details This function enables you to perform two 16-bit signed multiplications, taking the difference
           of the products by subtracting the high halfword product from the low halfword product.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \return        the difference of the products of the two 16-bit signed multiplications.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 res[31:0] = p1 - p2
 */
__ALWAYS_STATIC_INLINE uint32_t __SMUSD(uint32_t x, uint32_t y)
{
    return ((uint32_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16))));
}

/**
  \brief   Dual extracted 8-bit to 16-bit signed addition.
  \details This function enables you to extract two 8-bit values from the second operand (at bit positions
           [7:0] and [23:16]), sign-extend them to 16-bits each, and add the results to the first operand.
  \param [in]    x   values added to the sign-extended to 16-bit values.
  \param [in]    y   two 8-bit values to be extracted and sign-extended.
  \return        the addition of val1 and val2, where the 8-bit values in val2[7:0] and
                 val2[23:16] have been extracted and sign-extended prior to the addition.
  \remark
                 res[15:0]  = val1[15:0] + SignExtended(val2[7:0])      \n
                 res[31:16] = val1[31:16] + SignExtended(val2[23:16])
 */
__ALWAYS_STATIC_INLINE uint32_t __SXTAB16(uint32_t x, uint32_t y)
{
    return ((uint32_t)((((((int32_t)y << 24) >> 24) + (((int32_t)x << 16) >> 16)) & (int32_t)0x0000FFFF) |
                       (((((int32_t)y <<  8) >>  8)  + (((int32_t)x >> 16) << 16)) & (int32_t)0xFFFF0000)));
}

/**
  \brief   Extracted 16-bit to 32-bit unsigned addition.
  \details This function enables you to extract two 8-bit values from one operand, zero-extend
           them to 16 bits each, and add the results to two 16-bit values from another operand.
  \param [in]    x   values added to the zero-extended to 16-bit values.
  \param [in]    y   two 8-bit values to be extracted and zero-extended.
  \return        the addition of val1 and val2, where the 8-bit values in val2[7:0] and
                 val2[23:16] have been extracted and zero-extended prior to the addition.
  \remark
                 res[15:0]  = ZeroExt(val2[7:0]   to 16 bits) + val1[15:0]      \n
                 res[31:16] = ZeroExt(val2[31:16] to 16 bits) + val1[31:16]
 */
__ALWAYS_STATIC_INLINE uint32_t __UXTAB16(uint32_t x, uint32_t y)
{
    return ((uint32_t)(((((y << 24) >> 24) + ((x << 16) >> 16)) & 0x0000FFFF) |
                       ((((y <<  8) >>  8) + ((x >> 16) << 16)) & 0xFFFF0000)));
}

/**
  \brief   Dual extract 8-bits and sign extend each to 16-bits.
  \details This function enables you to extract two 8-bit values from an operand and sign-extend them to 16 bits each.
  \param [in]    x   two 8-bit values in val[7:0] and val[23:16] to be sign-extended.
  \return        the 8-bit values sign-extended to 16-bit values.\n
                 sign-extended value of val[7:0] in the low halfword of the return value.\n
                 sign-extended value of val[23:16] in the high halfword of the return value.
  \remark
                 res[15:0]  = SignExtended(val[7:0])       \n
                 res[31:16] = SignExtended(val[23:16])
 */
__ALWAYS_STATIC_INLINE uint32_t __SXTB16(uint32_t x)
{
    return ((uint32_t)(((((int32_t)x << 24) >> 24) & (int32_t)0x0000FFFF) |
                       ((((int32_t)x <<  8) >>  8) & (int32_t)0xFFFF0000)));
}

/**
  \brief   Dual extract 8-bits and zero-extend to 16-bits.
  \details This function enables you to extract two 8-bit values from an operand and zero-extend them to 16 bits each.
  \param [in]    x   two 8-bit values in val[7:0] and val[23:16] to be zero-extended.
  \return        the 8-bit values sign-extended to 16-bit values.\n
                 sign-extended value of val[7:0] in the low halfword of the return value.\n
                 sign-extended value of val[23:16] in the high halfword of the return value.
  \remark
                 res[15:0]  = SignExtended(val[7:0])       \n
                 res[31:16] = SignExtended(val[23:16])
 */
__ALWAYS_STATIC_INLINE uint32_t __UXTB16(uint32_t x)
{
    return ((uint32_t)((((x << 24) >> 24) & 0x0000FFFF) |
                       (((x <<  8) >>  8) & 0xFFFF0000)));
}

#endif /* _CSI_RV32_GCC_H_ */
