/*
 * Copyright (c) 2019 Nuclei Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __CORE_FEATURE_BASE__
#define __CORE_FEATURE_BASE__
/*!
 * @file     core_feature_base.h
 * @brief    Base core feature API for Nuclei N/NX Core
 */
#include <stdint.h>
#include "riscv_encoding.h"

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * \defgroup NMSIS_Core_Registers     Register Define and Type Definitions
 * \brief   Type definitions and defines for core registers.
 *
 * @{
 */
#ifndef __RISCV_XLEN
  /** \brief Refer to the width of an integer register in bits(either 32 or 64) */
  #ifndef __riscv_xlen
    #define __RISCV_XLEN    32
  #else
    #define __RISCV_XLEN    __riscv_xlen
  #endif
#endif /* __RISCV_XLEN */

/** \brief Type of Control and Status Register(CSR), depends on the XLEN defined in RISC-V */
#if __RISCV_XLEN == 32
  typedef uint32_t rv_csr_t;
#elif __RISCV_XLEN == 64
  typedef uint64_t rv_csr_t;
#else
  typedef uint32_t rv_csr_t;
#endif
/** @} */ /* End of Doxygen Group NMSIS_Core_Registers */
/**
 * \defgroup NMSIS_Core_Base_Registers     Base Register Define and Type Definitions
 * \ingroup NMSIS_Core_Registers
 * \brief   Type definitions and defines for base core registers.
 *
 * @{
 */
/**
 * \brief  Union type to access MISA register.
 */
typedef union {
    struct {
        rv_csr_t a:1;                           /*!< bit:     0  Atomic extension */
        rv_csr_t b:1;                           /*!< bit:     1  Tentatively reserved for Bit-Manipulation extension */
        rv_csr_t c:1;                           /*!< bit:     2  Compressed extension */
        rv_csr_t d:1;                           /*!< bit:     3  Double-precision floating-point extension */
        rv_csr_t e:1;                           /*!< bit:     4  RV32E base ISA */
        rv_csr_t f:1;                           /*!< bit:     5  Single-precision floating-point extension */
        rv_csr_t g:1;                           /*!< bit:     6  Additional standard extensions present */
        rv_csr_t h:1;                           /*!< bit:     7  Hypervisor extension */
        rv_csr_t i:1;                           /*!< bit:     8  RV32I/64I/128I base ISA */
        rv_csr_t j:1;                           /*!< bit:     9  Tentatively reserved for Dynamically Translated Languages extension */
        rv_csr_t _reserved1:1;                  /*!< bit:     10 Reserved  */
        rv_csr_t l:1;                           /*!< bit:     11 Tentatively reserved for Decimal Floating-Point extension  */
        rv_csr_t m:1;                           /*!< bit:     12 Integer Multiply/Divide extension */
        rv_csr_t n:1;                           /*!< bit:     13 User-level interrupts supported  */
        rv_csr_t _reserved2:1;                  /*!< bit:     14 Reserved  */
        rv_csr_t p:1;                           /*!< bit:     15 Tentatively reserved for Packed-SIMD extension  */
        rv_csr_t q:1;                           /*!< bit:     16 Quad-precision floating-point extension  */
        rv_csr_t _resreved3:1;                  /*!< bit:     17 Reserved  */
        rv_csr_t s:1;                           /*!< bit:     18 Supervisor mode implemented  */
        rv_csr_t t:1;                           /*!< bit:     19 Tentatively reserved for Transactional Memory extension  */
        rv_csr_t u:1;                           /*!< bit:     20 User mode implemented  */
        rv_csr_t v:1;                           /*!< bit:     21 Tentatively reserved for Vector extension  */
        rv_csr_t _reserved4:1;                  /*!< bit:     22 Reserved  */
        rv_csr_t x:1;                           /*!< bit:     23 Non-standard extensions present  */
#if defined(__RISCV_XLEN) && __RISCV_XLEN == 64
        rv_csr_t _reserved5:38;                 /*!< bit:     24..61 Reserved  */
        rv_csr_t mxl:2;                         /*!< bit:     62..63 Machine XLEN  */
#else
        rv_csr_t _reserved5:6;                  /*!< bit:     24..29 Reserved  */
        rv_csr_t mxl:2;                         /*!< bit:     30..31 Machine XLEN  */
#endif
    } b;                                        /*!< Structure used for bit  access */
    rv_csr_t d;                                 /*!< Type      used for csr data access */
} CSR_MISA_Type;

/**
 * \brief  Union type to access MSTATUS configure register.
 */
typedef union {
    struct {
#if defined(__RISCV_XLEN) && __RISCV_XLEN == 64
        rv_csr_t _reserved0:3;                  /*!< bit:     0..2  Reserved */
        rv_csr_t mie:1;                         /*!< bit:     3  Machine mode interrupt enable flag */
        rv_csr_t _reserved1:3;                  /*!< bit:     4..6  Reserved */
        rv_csr_t mpie:1;                        /*!< bit:     7  mirror of MIE flag */
        rv_csr_t _reserved2:3;                  /*!< bit:     8..10  Reserved */
        rv_csr_t mpp:2;                         /*!< bit:     11..12 mirror of Privilege Mode */
        rv_csr_t fs:2;                          /*!< bit:     13..14 FS status flag */
        rv_csr_t xs:2;                          /*!< bit:     15..16 XS status flag */
        rv_csr_t mprv:1;                        /*!< bit:     Machine mode PMP */
        rv_csr_t _reserved3:14;                 /*!< bit:     18..31 Reserved */
        rv_csr_t uxl:2;                         /*!< bit:     32..33 user mode xlen */
        rv_csr_t _reserved6:29;                 /*!< bit:     34..62 Reserved  */
        rv_csr_t sd:1;                          /*!< bit:     Dirty status for XS or FS */
#else
        rv_csr_t _reserved0:1;                  /*!< bit:     0  Reserved */
        rv_csr_t sie:1;                         /*!< bit:     1  supervisor interrupt enable flag */
        rv_csr_t _reserved1:1;                  /*!< bit:     2  Reserved */
        rv_csr_t mie:1;                         /*!< bit:     3  Machine mode interrupt enable flag */
        rv_csr_t _reserved2:1;                  /*!< bit:     4  Reserved */
        rv_csr_t spie:1;                        /*!< bit:     3  Supervisor Privilede mode interrupt enable flag */
        rv_csr_t _reserved3:1;                  /*!< bit:     Reserved */
        rv_csr_t mpie:1;                        /*!< bit:     mirror of MIE flag */
        rv_csr_t _reserved4:3;                  /*!< bit:     Reserved */
        rv_csr_t mpp:2;                         /*!< bit:     mirror of Privilege Mode */
        rv_csr_t fs:2;                          /*!< bit:     FS status flag */
        rv_csr_t xs:2;                          /*!< bit:     XS status flag */
        rv_csr_t mprv:1;                        /*!< bit:     Machine mode PMP */
        rv_csr_t sum:1;                         /*!< bit:     Supervisor Mode load and store protection */
        rv_csr_t _reserved6:12;                 /*!< bit:     19..30 Reserved  */
        rv_csr_t sd:1;                          /*!< bit:     Dirty status for XS or FS */
#endif
    } b;                                        /*!< Structure used for bit  access */
    rv_csr_t d;                                 /*!< Type      used for csr data access */
} CSR_MSTATUS_Type;

/**
 * \brief  Union type to access MTVEC configure register.
 */
typedef union {
    struct {
        rv_csr_t mode:6;                        /*!< bit:     0..5   interrupt mode control */
#if defined(__RISCV_XLEN) && __RISCV_XLEN == 64
        rv_csr_t addr:58;                       /*!< bit:     6..63  mtvec address */
#else
        rv_csr_t addr:26;                       /*!< bit:     6..31  mtvec address */
#endif
    } b;                                        /*!< Structure used for bit  access */
    rv_csr_t d;                                 /*!< Type      used for csr data access */
} CSR_MTVEC_Type;

/**
 * \brief  Union type to access MCAUSE configure register.
 */
typedef union {
    struct {
        rv_csr_t exccode:12;                    /*!< bit:     11..0  exception or interrupt code */
        rv_csr_t _reserved0:4;                  /*!< bit:     15..12  Reserved */
        rv_csr_t mpil:8;                        /*!< bit:     23..16  Previous interrupt level */
        rv_csr_t _reserved1:3;                  /*!< bit:     26..24  Reserved */
        rv_csr_t mpie:1;                        /*!< bit:     27  Interrupt enable flag before enter interrupt */
        rv_csr_t mpp:2;                         /*!< bit:     29..28  Privilede mode flag before enter interrupt */
        rv_csr_t minhv:1;                       /*!< bit:     30  Machine interrupt vector table */
#if defined(__RISCV_XLEN) && __RISCV_XLEN == 64
        rv_csr_t _reserved2:32;                 /*!< bit:     31..62  Reserved */
        rv_csr_t interrupt:1;                   /*!< bit:     63  trap type. 0 means exception and 1 means interrupt */
#else
        rv_csr_t interrupt:1;                   /*!< bit:     31  trap type. 0 means exception and 1 means interrupt */
#endif
    } b;                                        /*!< Structure used for bit  access */
    rv_csr_t d;                                 /*!< Type      used for csr data access */
} CSR_MCAUSE_Type;

/**
 * \brief  Union type to access MCOUNTINHIBIT configure register.
 */
typedef union {
    struct {
        rv_csr_t cy:1;                          /*!< bit:     0     1 means disable mcycle counter */
        rv_csr_t _reserved0:1;                  /*!< bit:     1     Reserved */
        rv_csr_t ir:1;                          /*!< bit:     2     1 means disable minstret counter */
#if defined(__RISCV_XLEN) && __RISCV_XLEN == 64
        rv_csr_t _reserved1:61;                 /*!< bit:     3..63 Reserved */
#else
        rv_csr_t _reserved1:29;                 /*!< bit:     3..31 Reserved */
#endif
    } b;                                        /*!< Structure used for bit  access */
    rv_csr_t d;                                 /*!< Type      used for csr data access */
} CSR_MCOUNTINHIBIT_Type;

/**
 * \brief  Union type to access msubm configure register.
 */
typedef union {
    struct {
        rv_csr_t _reserved0:6;                  /*!< bit:     0..5   Reserved */
        rv_csr_t typ:2;                         /*!< bit:     6..7   current trap type */
        rv_csr_t ptyp:2;                        /*!< bit:     8..9   previous trap type */
#if defined(__RISCV_XLEN) && __RISCV_XLEN == 64
        rv_csr_t _reserved1:54;                 /*!< bit:     10..63 Reserved */
#else
        rv_csr_t _reserved1:22;                 /*!< bit:     10..31 Reserved */
#endif
    } b;                                        /*!< Structure used for bit  access */
    rv_csr_t d;                                 /*!< Type      used for csr data access */
} CSR_MSUBM_Type;

/**
 * \brief  Union type to access MMISC_CTRL configure register.
 */
typedef union {
    struct {
        rv_csr_t _reserved0:3;                  /*!< bit:     0..2  Reserved */
        rv_csr_t bpu:1;                         /*!< bit:     3     dynamic prediction enable flag */
        rv_csr_t _reserved1:2;                  /*!< bit:     4..5  Reserved */
        rv_csr_t misalign:1;                    /*!< bit:     6     misaligned access support flag */
        rv_csr_t _reserved2:2;                  /*!< bit:     7..8  Reserved */
        rv_csr_t nmi_cause:1;                   /*!< bit:     9     mnvec control and nmi mcase exccode */
#if defined(__RISCV_XLEN) && __RISCV_XLEN == 64
        rv_csr_t _reserved3:54;                 /*!< bit:     10..63 Reserved */
#else
        rv_csr_t _reserved3:22;                 /*!< bit:     10..31 Reserved */
#endif
    } b;                                        /*!< Structure used for bit  access */
    rv_csr_t d;                                 /*!< Type      used for csr data access */
} CSR_MMISCCTRL_Type;


/**
 * \brief  Union type to access MSAVESTATUS configure register.
 */
typedef union {
    struct {
        rv_csr_t mpie1:1;                       /*!< bit:     0     interrupt enable flag of fisrt level NMI/exception nestting */
        rv_csr_t mpp1:2;                        /*!< bit:     1..2  privilede mode of fisrt level NMI/exception nestting */
        rv_csr_t _reserved0:3;                  /*!< bit:     3..5  Reserved */
        rv_csr_t ptyp1:2;                       /*!< bit:     6..7  NMI/exception type of before first nestting */
        rv_csr_t mpie2:1;                       /*!< bit:     8     interrupt enable flag of second level NMI/exception nestting */
        rv_csr_t mpp2:2;                        /*!< bit:     9..10 privilede mode of second level NMI/exception nestting */
        rv_csr_t _reserved1:3;                  /*!< bit:     11..13     Reserved */
        rv_csr_t ptyp2:2;                       /*!< bit:     14..15     NMI/exception type of before second nestting */
#if defined(__RISCV_XLEN) && __RISCV_XLEN == 64
        rv_csr_t _reserved2:48;                 /*!< bit:     16..63 Reserved*/
#else
        rv_csr_t _reserved2:16;                 /*!< bit:     16..31 Reserved*/
#endif
    } b;                                        /*!< Structure used for bit  access */
    rv_csr_t w;                                 /*!< Type      used for csr data access */
} CSR_MSAVESTATUS_Type;
/** @} */ /* End of Doxygen Group NMSIS_Core_Base_Registers */

/* ###########################  Core Function Access  ########################### */
/**
 * \defgroup NMSIS_Core_CSR_Register_Access    Core CSR Register Access
 * \ingroup  NMSIS_Core
 * \brief    Functions to access the Core CSR Registers
 * \details
 *
 * The following functions or macros provide access to Core CSR registers.
 * - \ref NMSIS_Core_CSR_Encoding
 * - \ref NMSIS_Core_CSR_Registers
 *   @{
 */


#ifndef __ASSEMBLY__

/**
 * \brief CSR operation Macro for csrrw instruction.
 * \details
 * Read the content of csr register to __v,
 * then write content of val into csr register, then return __v
 * \param csr   CSR macro definition defined in
 *              \ref NMSIS_Core_CSR_Registers, eg. \ref CSR_MSTATUS
 * \param val   value to store into the CSR register
 * \return the CSR register value before written
 */
#define __RV_CSR_SWAP(csr, val)                                 \
    ({                                                          \
        register rv_csr_t __v = (unsigned long)(val);           \
        __ASM volatile("csrrw %0, " STRINGIFY(csr) ", %1"       \
                     : "=r"(__v)                                \
                     : "rK"(__v)                                \
                     : "memory");                               \
        __v;                                                    \
    })

/**
 * \brief CSR operation Macro for csrr instruction.
 * \details
 * Read the content of csr register to __v and return it
 * \param csr   CSR macro definition defined in
 *              \ref NMSIS_Core_CSR_Registers, eg. \ref CSR_MSTATUS
 * \return the CSR register value
 */
#define __RV_CSR_READ(csr)                                      \
    ({                                                          \
        register rv_csr_t __v;                                  \
        __ASM volatile("csrr %0, " STRINGIFY(csr)               \
                     : "=r"(__v)                                \
                     :                                          \
                     : "memory");                               \
        __v;                                                    \
    })

/**
 * \brief CSR operation Macro for csrw instruction.
 * \details
 * Write the content of val to csr register
 * \param csr   CSR macro definition defined in
 *              \ref NMSIS_Core_CSR_Registers, eg. \ref CSR_MSTATUS
 * \param val   value to store into the CSR register
 */
#define __RV_CSR_WRITE(csr, val)                                \
    ({                                                          \
        register rv_csr_t __v = (rv_csr_t)(val);                \
        __ASM volatile("csrw " STRINGIFY(csr) ", %0"            \
                     :                                          \
                     : "rK"(__v)                                \
                     : "memory");                               \
    })

/**
 * \brief CSR operation Macro for csrrs instruction.
 * \details
 * Read the content of csr register to __v,
 * then set csr register to be __v | val, then return __v
 * \param csr   CSR macro definition defined in
 *              \ref NMSIS_Core_CSR_Registers, eg. \ref CSR_MSTATUS
 * \param val   Mask value to be used wih csrrs instruction
 * \return the CSR register value before written
 */
#define __RV_CSR_READ_SET(csr, val)                             \
    ({                                                          \
        register rv_csr_t __v = (rv_csr_t)(val);                \
        __ASM volatile("csrrs %0, " STRINGIFY(csr) ", %1"       \
                     : "=r"(__v)                                \
                     : "rK"(__v)                                \
                     : "memory");                               \
        __v;                                                    \
    })

/**
 * \brief CSR operation Macro for csrs instruction.
 * \details
 * Set csr register to be csr_content | val
 * \param csr   CSR macro definition defined in
 *              \ref NMSIS_Core_CSR_Registers, eg. \ref CSR_MSTATUS
 * \param val   Mask value to be used wih csrs instruction
 */
#define __RV_CSR_SET(csr, val)                                  \
    ({                                                          \
        register rv_csr_t __v = (rv_csr_t)(val);                \
        __ASM volatile("csrs " STRINGIFY(csr) ", %0"            \
                     :                                          \
                     : "rK"(__v)                                \
                     : "memory");                               \
    })

/**
 * \brief CSR operation Macro for csrrc instruction.
 * \details
 * Read the content of csr register to __v,
 * then set csr register to be __v & ~val, then return __v
 * \param csr   CSR macro definition defined in
 *              \ref NMSIS_Core_CSR_Registers, eg. \ref CSR_MSTATUS
 * \param val   Mask value to be used wih csrrc instruction
 * \return the CSR register value before written
 */
#define __RV_CSR_READ_CLEAR(csr, val)                           \
    ({                                                          \
        register rv_csr_t __v = (rv_csr_t)(val);                \
        __ASM volatile("csrrc %0, " STRINGIFY(csr) ", %1"       \
                     : "=r"(__v)                                \
                     : "rK"(__v)                                \
                     : "memory");                               \
        __v;                                                    \
    })

/**
 * \brief CSR operation Macro for csrc instruction.
 * \details
 * Set csr register to be csr_content & ~val
 * \param csr   CSR macro definition defined in
 *              \ref NMSIS_Core_CSR_Registers, eg. \ref CSR_MSTATUS
 * \param val   Mask value to be used wih csrc instruction
 */
#define __RV_CSR_CLEAR(csr, val)                                \
    ({                                                          \
        register rv_csr_t __v = (rv_csr_t)(val);                \
        __ASM volatile("csrc " STRINGIFY(csr) ", %0"            \
                     :                                          \
                     : "rK"(__v)                                \
                     : "memory");                               \
    })
#endif /* __ASSEMBLY__ */

/**
 * \brief   Enable IRQ Interrupts
 * \details Enables IRQ interrupts by setting the MIE-bit in the MSTATUS Register.
 * \remarks
 *          Can only be executed in Privileged modes.
 */
__STATIC_FORCEINLINE void __enable_irq(void)
{
    __RV_CSR_SET(CSR_MSTATUS, MSTATUS_MIE);
}

/**
 * \brief   Disable IRQ Interrupts
 * \details Disables IRQ interrupts by clearing the MIE-bit in the MSTATUS Register.
 * \remarks
 *          Can only be executed in Privileged modes.
 */
__STATIC_FORCEINLINE void __disable_irq(void)
{
    __RV_CSR_CLEAR(CSR_MSTATUS, MSTATUS_MIE);
}

/**
 * \brief   Read whole 64 bits value of mcycle counter
 * \details This function will read the whole 64 bits of MCYCLE register
 * \return  The whole 64 bits value of MCYCLE
 * \remarks It will work for both RV32 and RV64 to get full 64bits value of MCYCLE
 */
__STATIC_FORCEINLINE uint64_t __get_rv_cycle(void)
{
#if __RISCV_XLEN == 32
    volatile uint32_t high0, low, high;
    uint64_t full;

    high0 = __RV_CSR_READ(CSR_MCYCLEH);
    low = __RV_CSR_READ(CSR_MCYCLE);
    high = __RV_CSR_READ(CSR_MCYCLEH);
    if (high0 != high) {
        low = __RV_CSR_READ(CSR_MCYCLE);
    }
    full = (((uint64_t)high) << 32) | low;
    return full;
#elif __RISCV_XLEN == 64
    return (uint64_t)__RV_CSR_READ(CSR_MCYCLE);
#else // TODO Need cover for XLEN=128 case in future
    return (uint64_t)__RV_CSR_READ(CSR_MCYCLE);
#endif
}

/**
 * \brief   Read whole 64 bits value of machine instruction-retired counter
 * \details This function will read the whole 64 bits of MINSTRET register
 * \return  The whole 64 bits value of MINSTRET
 * \remarks It will work for both RV32 and RV64 to get full 64bits value of MINSTRET
 */
__STATIC_FORCEINLINE uint64_t __get_rv_instret(void)
{
#if __RISCV_XLEN == 32
    volatile uint32_t high0, low, high;
    uint64_t full;

    high0 = __RV_CSR_READ(CSR_MINSTRETH);
    low = __RV_CSR_READ(CSR_MINSTRET);
    high = __RV_CSR_READ(CSR_MINSTRETH);
    if (high0 != high) {
        low = __RV_CSR_READ(CSR_MINSTRET);
    }
    full = (((uint64_t)high) << 32) | low;
    return full;
#elif __RISCV_XLEN == 64
    return (uint64_t)__RV_CSR_READ(CSR_MINSTRET);
#else // TODO Need cover for XLEN=128 case in future
    return (uint64_t)__RV_CSR_READ(CSR_MINSTRET);
#endif
}

/**
 * \brief   Read whole 64 bits value of real-time clock
 * \details This function will read the whole 64 bits of TIME register
 * \return  The whole 64 bits value of TIME CSR
 * \remarks It will work for both RV32 and RV64 to get full 64bits value of TIME
 * \attention only available when user mode available
 */
__STATIC_FORCEINLINE uint64_t __get_rv_time(void)
{
#if __RISCV_XLEN == 32
    volatile uint32_t high0, low, high;
    uint64_t full;

    high0 = __RV_CSR_READ(CSR_TIMEH);
    low = __RV_CSR_READ(CSR_TIME);
    high = __RV_CSR_READ(CSR_TIMEH);
    if (high0 != high) {
        low = __RV_CSR_READ(CSR_TIME);
    }
    full = (((uint64_t)high) << 32) | low;
    return full;
#elif __RISCV_XLEN == 64
    return (uint64_t)__RV_CSR_READ(CSR_TIME);
#else // TODO Need cover for XLEN=128 case in future
    return (uint64_t)__RV_CSR_READ(CSR_TIME);
#endif
}

/** @} */ /* End of Doxygen Group NMSIS_Core_CSR_Register_Access */

/* ###########################  CPU Intrinsic Functions ########################### */
/**
 * \defgroup NMSIS_Core_CPU_Intrinsic   Intrinsic Functions for CPU Intructions
 * \ingroup  NMSIS_Core
 * \brief    Functions that generate RISC-V CPU instructions.
 * \details
 *
 * The following functions generate specified RISC-V instructions that cannot be directly accessed by compiler.
 *   @{
 */

/**
 * \brief   NOP Instruction
 * \details
 * No Operation does nothing.
 * This instruction can be used for code alignment purposes.
 */
__STATIC_FORCEINLINE void __NOP(void)
{
    __ASM volatile("nop");
}

/**
 * \brief   Wait For Interrupt
 * \details
 * Wait For Interrupt is is executed using CSR_WFE.WFE=0 and WFI instruction.
 * It will suspends execution until interrupt, NMI or Debug happened.
 * When Core is waked up by interrupt, if
 * 1. mstatus.MIE == 1(interrupt enabled), Core will enter ISR code
 * 2. mstatus.MIE == 0(interrupt disabled), Core will resume previous execution
 */
__STATIC_FORCEINLINE void __WFI(void)
{
    __RV_CSR_CLEAR(CSR_WFE, WFE_WFE);
    __ASM volatile("wfi");
}

/**
 * \brief   Wait For Event
 * \details
 * Wait For Event is executed using CSR_WFE.WFE=1 and WFI instruction.
 * It will suspends execution until event, NMI or Debug happened.
 * When Core is waked up, Core will resume previous execution
 */
__STATIC_FORCEINLINE void __WFE(void)
{
    __RV_CSR_SET(CSR_WFE, WFE_WFE);
    __ASM volatile("wfi");
    __RV_CSR_CLEAR(CSR_WFE, WFE_WFE);
}

/**
 * \brief   Breakpoint Instruction
 * \details
 * Causes the processor to enter Debug state.
 * Debug tools can use this to investigate system state
 * when the instruction at a particular address is reached.
 */
__STATIC_FORCEINLINE void __EBREAK(void)
{
    __ASM volatile("ebreak");
}

/**
 * \brief   Environment Call Instruction
 * \details
 * The ECALL instruction is used to make a service request to
 * the execution environment.
 */
__STATIC_FORCEINLINE void __ECALL(void)
{
    __ASM volatile("ecall");
}

/**
 * \brief WFI Sleep Mode enumeration
 */
typedef enum WFI_SleepMode {
    WFI_SHALLOW_SLEEP = 0,      /*!< Shallow sleep mode, the core_clk will poweroff */
    WFI_DEEP_SLEEP = 1          /*!< Deep sleep mode, the core_clk and core_ano_clk will poweroff */
} WFI_SleepMode_Type;

/**
 * \brief   Set Sleep mode of WFI
 * \details
 * Set the SLEEPVALUE CSR register to control the
 * WFI Sleep mode.
 * \param[in] mode      The sleep mode to be set
 */
__STATIC_FORCEINLINE void __set_wfi_sleepmode(WFI_SleepMode_Type mode)
{
    __RV_CSR_WRITE(CSR_SLEEPVALUE, mode);
}

/**
 * \brief   Send TX Event
 * \details
 * Set the CSR TXEVT to control send a TX Event.
 * The Core will output signal tx_evt as output event signal.
 */
__STATIC_FORCEINLINE void __TXEVT(void)
{
    __RV_CSR_SET(CSR_TXEVT, 0x1);
}

/**
 * \brief   Enable MCYCLE counter
 * \details
 * Clear the CY bit of MCOUNTINHIBIT to 0 to enable MCYCLE Counter
 */
__STATIC_FORCEINLINE void __enable_mcycle_counter(void)
{
    __RV_CSR_CLEAR(CSR_MCOUNTINHIBIT, MCOUNTINHIBIT_CY);
}

/**
 * \brief   Disable MCYCLE counter
 * \details
 * Set the CY bit of MCOUNTINHIBIT to 1 to disable MCYCLE Counter
 */
__STATIC_FORCEINLINE void __disable_mcycle_counter(void)
{
    __RV_CSR_SET(CSR_MCOUNTINHIBIT, MCOUNTINHIBIT_CY);
}

/**
 * \brief   Enable MINSTRET counter
 * \details
 * Clear the IR bit of MCOUNTINHIBIT to 0 to enable MINSTRET Counter
 */
__STATIC_FORCEINLINE void __enable_minstret_counter(void)
{
    __RV_CSR_CLEAR(CSR_MCOUNTINHIBIT, MCOUNTINHIBIT_IR);
}

/**
 * \brief   Disable MINSTRET counter
 * \details
 * Set the IR bit of MCOUNTINHIBIT to 1 to disable MINSTRET Counter
 */
__STATIC_FORCEINLINE void __disable_minstret_counter(void)
{
    __RV_CSR_SET(CSR_MCOUNTINHIBIT, MCOUNTINHIBIT_IR);
}

/**
 * \brief   Enable MCYCLE & MINSTRET counter
 * \details
 * Clear the IR and CY bit of MCOUNTINHIBIT to 1 to enable MINSTRET & MCYCLE Counter
 */
__STATIC_FORCEINLINE void __enable_all_counter(void)
{
    __RV_CSR_CLEAR(CSR_MCOUNTINHIBIT, MCOUNTINHIBIT_IR|MCOUNTINHIBIT_CY);
}

/**
 * \brief   Disable MCYCLE & MINSTRET counter
 * \details
 * Set the IR and CY bit of MCOUNTINHIBIT to 1 to disable MINSTRET & MCYCLE Counter
 */
__STATIC_FORCEINLINE void __disable_all_counter(void)
{
    __RV_CSR_SET(CSR_MCOUNTINHIBIT, MCOUNTINHIBIT_IR|MCOUNTINHIBIT_CY);
}

/**
 * \brief Execute fence instruction, p -> pred, s -> succ
 * \details
 * the FENCE instruction ensures that all memory accesses from instructions preceding
 * the fence in program order (the `predecessor set`) appear earlier in the global memory order than
 * memory accesses from instructions appearing after the fence in program order (the `successor set`).
 * For details, please refer to The RISC-V Instruction Set Manual
 * \param p     predecessor set, such as iorw, rw, r, w
 * \param s     successor set, such as iorw, rw, r, w
 **/
#define __FENCE(p, s) __ASM volatile ("fence " #p "," #s : : : "memory")

/**
 * \brief   Fence.i Instruction
 * \details
 * The FENCE.I instruction is used to synchronize the instruction
 * and data streams.
 */
__STATIC_FORCEINLINE void __FENCE_I(void)
{
    __ASM volatile("fence.i");
}

/** \brief Read & Write Memory barrier */
#define __RWMB()        __FENCE(iorw,iorw)

/** \brief Read Memory barrier */
#define __RMB()         __FENCE(ir,ir)

/** \brief Write Memory barrier */
#define __WMB()         __FENCE(ow,ow)

/** \brief SMP Read & Write Memory barrier */
#define __SMP_RWMB()    __FENCE(rw,rw)

/** \brief SMP Read Memory barrier */
#define __SMP_RMB()     __FENCE(r,r)

/** \brief SMP Write Memory barrier */
#define __SMP_WMB()     __FENCE(w,w)

/** \brief CPU relax for busy loop */
#define __CPU_RELAX()   __ASM volatile ("" : : : "memory")


/* ===== Load/Store Operations ===== */
/**
 * \brief  Load 8bit value from address (8 bit)
 * \details Load 8 bit value.
 * \param [in]    addr  Address pointer to data
 * \return              value of type uint8_t at (*addr)
 */
__STATIC_FORCEINLINE uint8_t __LB(volatile void *addr)
{
    uint8_t result;

    __ASM volatile ("lb %0, 0(%1)" : "=r" (result) : "r" (addr));
    return result;
}

/**
 * \brief  Load 16bit value from address (16 bit)
 * \details Load 16 bit value.
 * \param [in]    addr  Address pointer to data
 * \return              value of type uint16_t at (*addr)
 */
__STATIC_FORCEINLINE uint16_t __LH(volatile void *addr)
{
    uint16_t result;

    __ASM volatile ("lh %0, 0(%1)" : "=r" (result) : "r" (addr));
    return result;
}

/**
 * \brief  Load 32bit value from address (32 bit)
 * \details Load 32 bit value.
 * \param [in]    addr  Address pointer to data
 * \return              value of type uint32_t at (*addr)
 */
__STATIC_FORCEINLINE uint32_t __LW(volatile void *addr)
{
    uint32_t result;

    __ASM volatile ("lw %0, 0(%1)" : "=r" (result) : "r" (addr));
    return result;
}

#if __RISCV_XLEN != 32
/**
 * \brief  Load 64bit value from address (64 bit)
 * \details Load 64 bit value.
 * \param [in]    addr  Address pointer to data
 * \return              value of type uint64_t at (*addr)
 * \remarks RV64 only macro
 */
__STATIC_FORCEINLINE uint64_t __LD(volatile void *addr)
{
    uint64_t result;
    __ASM volatile ("ld %0, 0(%1)" : "=r" (result) : "r" (addr));
    return result;
}
#endif

/**
 * \brief  Write 8bit value to address (8 bit)
 * \details Write 8 bit value.
 * \param [in]    addr  Address pointer to data
 * \param [in]    val   Value to set
 */
__STATIC_FORCEINLINE void __SB(volatile void *addr, uint8_t val)
{
    __ASM volatile ("sb %0, 0(%1)" : : "r" (val), "r" (addr));
}

/**
 * \brief  Write 16bit value to address (16 bit)
 * \details Write 16 bit value.
 * \param [in]    addr  Address pointer to data
 * \param [in]    val   Value to set
 */
__STATIC_FORCEINLINE void __SH(volatile void *addr, uint16_t val)
{
    __ASM volatile ("sh %0, 0(%1)" : : "r" (val), "r" (addr));
}

/**
 * \brief  Write 32bit value to address (32 bit)
 * \details Write 32 bit value.
 * \param [in]    addr  Address pointer to data
 * \param [in]    val   Value to set
 */
__STATIC_FORCEINLINE void __SW(volatile void *addr, uint32_t val)
{
    __ASM volatile ("sw %0, 0(%1)" : : "r" (val), "r" (addr));
}

#if __RISCV_XLEN != 32
/**
 * \brief  Write 64bit value to address (64 bit)
 * \details Write 64 bit value.
 * \param [in]    addr  Address pointer to data
 * \param [in]    val   Value to set
 */
__STATIC_FORCEINLINE void __SD(volatile void *addr, uint64_t val)
{
    __ASM volatile ("sd %0, 0(%1)" : : "r" (val), "r" (addr));
}
#endif

/**
 * \brief  Compare and Swap 32bit value using LR and SC
 * \details Compare old value with memory, if identical,
 * store new value in memory. Return the initial value in memory.
 * Success is indicated by comparing return value with OLD.
 * memory address, return 0 if successful, otherwise return !0
 * \param [in]    addr      Address pointer to data, address need to be 4byte aligned
 * \param [in]    oldval    Old value of the data in address
 * \param [in]    newval    New value to be stored into the address
 * \return  return the initial value in memory
 */
__STATIC_FORCEINLINE uint32_t __CAS_W(volatile uint32_t *addr, uint32_t oldval, uint32_t newval)
{
    register uint32_t result;
    register uint32_t rc;

    __ASM volatile (                                \
            "0:     lr.w %0, %2      \n"            \
            "       bne  %0, %z3, 1f \n"            \
            "       sc.w %1, %z4, %2 \n"            \
            "       bnez %1, 0b      \n"            \
            "1:\n"                                  \
            : "=&r"(result), "=&r"(rc), "+A"(*addr) \
            : "r"(oldval), "r"(newval)              \
            : "memory");
    return result;
}

/**
 * \brief  Atomic Swap 32bit value into memory
 * \details Atomically swap new 32bit value into memory using amoswap.d.
 * \param [in]    addr      Address pointer to data, address need to be 4byte aligned
 * \param [in]    newval    New value to be stored into the address
 * \return  return the original value in memory
 */
__STATIC_FORCEINLINE uint32_t __AMOSWAP_W(volatile uint32_t *addr, uint32_t newval)
{
    register uint32_t result;

    __ASM volatile ("amoswap.w %0, %2, %1" : \
            "=r"(result), "+A"(*addr) : "r"(newval) : "memory");
    return result;
}

/**
 * \brief  Atomic Add with 32bit value
 * \details Atomically ADD 32bit value with value in memory using amoadd.d.
 * \param [in]    addr   Address pointer to data, address need to be 4byte aligned
 * \param [in]    value  value to be ADDed
 * \return  return memory value + add value
 */
__STATIC_FORCEINLINE int32_t __AMOADD_W(volatile int32_t *addr, int32_t value)
{
    register int32_t result;

    __ASM volatile ("amoadd.w %0, %2, %1" : \
            "=r"(result), "+A"(*addr) : "r"(value) : "memory");
    return *addr;
}

/**
 * \brief  Atomic And with 32bit value
 * \details Atomically AND 32bit value with value in memory using amoand.d.
 * \param [in]    addr   Address pointer to data, address need to be 4byte aligned
 * \param [in]    value  value to be ANDed
 * \return  return memory value & and value
 */
__STATIC_FORCEINLINE int32_t __AMOAND_W(volatile int32_t *addr, int32_t value)
{
    register int32_t result;

    __ASM volatile ("amoand.w %0, %2, %1" : \
            "=r"(result), "+A"(*addr) : "r"(value) : "memory");
    return *addr;
}

/**
 * \brief  Atomic OR with 32bit value
 * \details Atomically OR 32bit value with value in memory using amoor.d.
 * \param [in]    addr   Address pointer to data, address need to be 4byte aligned
 * \param [in]    value  value to be ORed
 * \return  return memory value | and value
 */
__STATIC_FORCEINLINE int32_t __AMOOR_W(volatile int32_t *addr, int32_t value)
{
    register int32_t result;

    __ASM volatile ("amoor.w %0, %2, %1" : \
            "=r"(result), "+A"(*addr) : "r"(value) : "memory");
    return *addr;
}

/**
 * \brief  Atomic XOR with 32bit value
 * \details Atomically XOR 32bit value with value in memory using amoxor.d.
 * \param [in]    addr   Address pointer to data, address need to be 4byte aligned
 * \param [in]    value  value to be XORed
 * \return  return memory value ^ and value
 */
__STATIC_FORCEINLINE int32_t __AMOXOR_W(volatile int32_t *addr, int32_t value)
{
    register int32_t result;

    __ASM volatile ("amoxor.w %0, %2, %1" : \
            "=r"(result), "+A"(*addr) : "r"(value) : "memory");
    return *addr;
}

/**
 * \brief  Atomic unsigned MAX with 32bit value
 * \details Atomically unsigned max compare 32bit value with value in memory using amomaxu.d.
 * \param [in]    addr   Address pointer to data, address need to be 4byte aligned
 * \param [in]    value  value to be compared
 * \return  return the bigger value
 */
__STATIC_FORCEINLINE uint32_t __AMOMAXU_W(volatile uint32_t *addr, uint32_t value)
{
    register uint32_t result;

    __ASM volatile ("amomaxu.w %0, %2, %1" : \
            "=r"(result), "+A"(*addr) : "r"(value) : "memory");
    return *addr;
}

/**
 * \brief  Atomic signed MAX with 32bit value
 * \details Atomically signed max compare 32bit value with value in memory using amomax.d.
 * \param [in]    addr   Address pointer to data, address need to be 4byte aligned
 * \param [in]    value  value to be compared
 * \return the bigger value
 */
__STATIC_FORCEINLINE int32_t __AMOMAX_W(volatile int32_t *addr, int32_t value)
{
    register int32_t result;

    __ASM volatile ("amomax.w %0, %2, %1" : \
            "=r"(result), "+A"(*addr) : "r"(value) : "memory");
    return *addr;
}

/**
 * \brief  Atomic unsigned MIN with 32bit value
 * \details Atomically unsigned min compare 32bit value with value in memory using amominu.d.
 * \param [in]    addr   Address pointer to data, address need to be 4byte aligned
 * \param [in]    value  value to be compared
 * \return the smaller value
 */
__STATIC_FORCEINLINE uint32_t __AMOMINU_W(volatile uint32_t *addr, uint32_t value)
{
    register uint32_t result;

    __ASM volatile ("amominu.w %0, %2, %1" : \
            "=r"(result), "+A"(*addr) : "r"(value) : "memory");
    return *addr;
}

/**
 * \brief  Atomic signed MIN with 32bit value
 * \details Atomically signed min compare 32bit value with value in memory using amomin.d.
 * \param [in]    addr   Address pointer to data, address need to be 4byte aligned
 * \param [in]    value  value to be compared
 * \return  the smaller value
 */
__STATIC_FORCEINLINE int32_t __AMOMIN_W(volatile int32_t *addr, int32_t value)
{
    register int32_t result;

    __ASM volatile ("amomin.w %0, %2, %1" : \
            "=r"(result), "+A"(*addr) : "r"(value) : "memory");
    return *addr;
}

#if __RISCV_XLEN == 64
/**
 * \brief  Compare and Swap 64bit value using LR and SC
 * \details Compare old value with memory, if identical,
 * store new value in memory. Return the initial value in memory.
 * Success is indicated by comparing return value with OLD.
 * memory address, return 0 if successful, otherwise return !0
 * \param [in]    addr      Address pointer to data, address need to be 8byte aligned
 * \param [in]    oldval    Old value of the data in address
 * \param [in]    newval    New value to be stored into the address
 * \return  return the initial value in memory
 */
__STATIC_FORCEINLINE uint64_t __CAS_D(volatile uint64_t *addr, uint64_t oldval, uint64_t newval)
{
    register uint64_t result;
    register uint64_t rc;

    __ASM volatile (                                \
            "0:     lr.d %0, %2      \n"            \
            "       bne  %0, %z3, 1f \n"            \
            "       sc.d %1, %z4, %2 \n"            \
            "       bnez %1, 0b      \n"            \
            "1:\n"                                  \
            : "=&r"(result), "=&r"(rc), "+A"(*addr) \
            : "r"(oldval), "r"(newval)              \
            : "memory");
    return result;
}

/**
 * \brief  Atomic Swap 64bit value into memory
 * \details Atomically swap new 64bit value into memory using amoswap.d.
 * \param [in]    addr      Address pointer to data, address need to be 8byte aligned
 * \param [in]    newval    New value to be stored into the address
 * \return  return the original value in memory
 */
__STATIC_FORCEINLINE uint64_t __AMOSWAP_D(volatile uint64_t *addr, uint64_t newval)
{
    register uint64_t result;

    __ASM volatile ("amoswap.d %0, %2, %1" : \
            "=r"(result), "+A"(*addr) : "r"(newval) : "memory");
    return result;
}

/**
 * \brief  Atomic Add with 64bit value
 * \details Atomically ADD 64bit value with value in memory using amoadd.d.
 * \param [in]    addr   Address pointer to data, address need to be 8byte aligned
 * \param [in]    value  value to be ADDed
 * \return  return memory value + add value
 */
__STATIC_FORCEINLINE int64_t __AMOADD_D(volatile int64_t *addr, int64_t value)
{
    register int64_t result;

    __ASM volatile ("amoadd.d %0, %2, %1" : \
            "=r"(result), "+A"(*addr) : "r"(value) : "memory");
    return *addr;
}

/**
 * \brief  Atomic And with 64bit value
 * \details Atomically AND 64bit value with value in memory using amoand.d.
 * \param [in]    addr   Address pointer to data, address need to be 8byte aligned
 * \param [in]    value  value to be ANDed
 * \return  return memory value & and value
 */
__STATIC_FORCEINLINE int64_t __AMOAND_D(volatile int64_t *addr, int64_t value)
{
    register int64_t result;

    __ASM volatile ("amoand.d %0, %2, %1" : \
            "=r"(result), "+A"(*addr) : "r"(value) : "memory");
    return *addr;
}

/**
 * \brief  Atomic OR with 64bit value
 * \details Atomically OR 64bit value with value in memory using amoor.d.
 * \param [in]    addr   Address pointer to data, address need to be 8byte aligned
 * \param [in]    value  value to be ORed
 * \return  return memory value | and value
 */
__STATIC_FORCEINLINE int64_t __AMOOR_D(volatile int64_t *addr, int64_t value)
{
    register int64_t result;

    __ASM volatile ("amoor.d %0, %2, %1" : \
            "=r"(result), "+A"(*addr) : "r"(value) : "memory");
    return *addr;
}

/**
 * \brief  Atomic XOR with 64bit value
 * \details Atomically XOR 64bit value with value in memory using amoxor.d.
 * \param [in]    addr   Address pointer to data, address need to be 8byte aligned
 * \param [in]    value  value to be XORed
 * \return  return memory value ^ and value
 */
__STATIC_FORCEINLINE int64_t __AMOXOR_D(volatile int64_t *addr, int64_t value)
{
    register int64_t result;

    __ASM volatile ("amoxor.d %0, %2, %1" : \
            "=r"(result), "+A"(*addr) : "r"(value) : "memory");
    return *addr;
}

/**
 * \brief  Atomic unsigned MAX with 64bit value
 * \details Atomically unsigned max compare 64bit value with value in memory using amomaxu.d.
 * \param [in]    addr   Address pointer to data, address need to be 8byte aligned
 * \param [in]    value  value to be compared
 * \return  return the bigger value
 */
__STATIC_FORCEINLINE uint64_t __AMOMAXU_D(volatile uint64_t *addr, uint64_t value)
{
    register uint64_t result;

    __ASM volatile ("amomaxu.d %0, %2, %1" : \
            "=r"(result), "+A"(*addr) : "r"(value) : "memory");
    return *addr;
}

/**
 * \brief  Atomic signed MAX with 64bit value
 * \details Atomically signed max compare 64bit value with value in memory using amomax.d.
 * \param [in]    addr   Address pointer to data, address need to be 8byte aligned
 * \param [in]    value  value to be compared
 * \return the bigger value
 */
__STATIC_FORCEINLINE int64_t __AMOMAX_D(volatile int64_t *addr, int64_t value)
{
    register int64_t result;

    __ASM volatile ("amomax.d %0, %2, %1" : \
            "=r"(result), "+A"(*addr) : "r"(value) : "memory");
    return *addr;
}

/**
 * \brief  Atomic unsigned MIN with 64bit value
 * \details Atomically unsigned min compare 64bit value with value in memory using amominu.d.
 * \param [in]    addr   Address pointer to data, address need to be 8byte aligned
 * \param [in]    value  value to be compared
 * \return the smaller value
 */
__STATIC_FORCEINLINE uint64_t __AMOMINU_D(volatile uint64_t *addr, uint64_t value)
{
    register uint64_t result;

    __ASM volatile ("amominu.d %0, %2, %1" : \
            "=r"(result), "+A"(*addr) : "r"(value) : "memory");
    return *addr;
}

/**
 * \brief  Atomic signed MIN with 64bit value
 * \details Atomically signed min compare 64bit value with value in memory using amomin.d.
 * \param [in]    addr   Address pointer to data, address need to be 8byte aligned
 * \param [in]    value  value to be compared
 * \return  the smaller value
 */
__STATIC_FORCEINLINE int64_t __AMOMIN_D(volatile int64_t *addr, int64_t value)
{
    register int64_t result;

    __ASM volatile ("amomin.d %0, %2, %1" : \
            "=r"(result), "+A"(*addr) : "r"(value) : "memory");
    return *addr;
}
#endif /* __RISCV_XLEN == 64  */

/** @} */ /* End of Doxygen Group NMSIS_Core_CPU_Intrinsic */

#ifdef __cplusplus
}
#endif
#endif /* __CORE_FEATURE_BASE__ */
