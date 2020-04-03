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
#ifndef __CORE_FEATURE_FPU_H__
#define __CORE_FEATURE_FPU_H__
/*!
 * @file     core_feature_fpu.h
 * @brief    FPU feature API header file for Nuclei N/NX Core
 */
/*
 * FPU Feature Configuration Macro:
 * 1. __FPU_PRESENT:  Define whether Floating Point Unit(FPU) is present or not
 *   * 0: Not present
 *   * 1: Single precision FPU present, __RISCV_FLEN == 32
 *   * 2: Double precision FPU present, __RISCV_FLEN == 64
 */
#ifdef __cplusplus
 extern "C" {
#endif

/* ===== FPU Operations ===== */
/**
 * \defgroup NMSIS_Core_FPU_Functions   FPU Functions
 * \ingroup  NMSIS_Core
 * \brief    Functions that related to the RISC-V FPU (F and D extension).
 * \details
 *
 * Nuclei provided floating point unit by RISC-V F and D extension.
 * * `F extension` adds single-precision floating-point computational
 * instructions compliant with the IEEE 754-2008 arithmetic standard, __RISCV_FLEN = 32.
 *   The F extension adds 32 floating-point registers, f0-f31, each 32 bits wide,
 *   and a floating-point control and status register fcsr, which contains the
 *   operating mode and exception status of the floating-point unit.
 * * `D extension` adds double-precision floating-point computational instructions
 * compliant with the IEEE 754-2008 arithmetic standard.
 *   The D extension widens the 32 floating-point registers, f0-f31, to 64 bits, __RISCV_FLEN = 64
 *   @{
 */
#if defined(__FPU_PRESENT) && (__FPU_PRESENT > 0)

#if __FPU_PRESENT == 1
  /** \brief Refer to the width of the floating point register in bits(either 32 or 64) */
  #define __RISCV_FLEN          32
#elif __FPU_PRESENT == 2
  #define __RISCV_FLEN          64
#else
  #define __RISCV_FLEN          __riscv_flen
#endif /* __FPU_PRESENT == 1 */

/** \brief Get FCSR CSR Register */
#define __get_FCSR()            __RV_CSR_READ(CSR_FCSR)
/** \brief Set FCSR CSR Register with val */
#define __set_FCSR(val)         __RV_CSR_WRITE(CSR_FCSR, (val))
/** \brief Get FRM CSR Register */
#define __get_FRM()             __RV_CSR_READ(CSR_FRM)
/** \brief Set FRM CSR Register with val */
#define __set_FRM(val)          __RV_CSR_WRITE(CSR_FRM, (val))
/** \brief Get FFLAGS CSR Register */
#define __get_FFLAGS()          __RV_CSR_READ(CSR_FFLAGS)
/** \brief Set FFLAGS CSR Register with val */
#define __set_FFLAGS(val)       __RV_CSR_WRITE(CSR_FFLAGS, (val))

/** \brief Enable FPU Unit */
#define __enable_FPU()          __RV_CSR_SET(CSR_MSTATUS, MSTATUS_FS)
/**
 * \brief Disable FPU Unit
 * \details
 * * We can save power by disable FPU Unit.
 * * When FPU Unit is disabled, any access to FPU related CSR registers
 * and FPU instructions will cause illegal Instuction Exception.
 * */
#define __disable_FPU()         __RV_CSR_CLEAR(CSR_MSTATUS, MSTATUS_FS)


/**
 * \brief   Load a single-precision value from memory into float point register freg using flw instruction
 * \details The FLW instruction loads a single-precision floating point value from memory
 * address (addr + ofs) into floating point register freg(f0-f31)
 * \param [in]    freg   The floating point register, eg. FREG(0), f0
 * \param [in]    addr   The memory base address, 4 byte aligned required
 * \param [in]    ofs    a 12-bit immediate signed byte offset value, should be an const value
 * \remarks
 * * FLW and FSW operations need to make sure the address is 4 bytes aligned,
 *   otherwise it will cause exception code 4(Load address misaligned) or 6 (Store/AMO address misaligned)
 * * FLW and FSW do not modify the bits being transferred; in particular, the payloads of non-canonical
 * NaNs are preserved
 *
 */
#define __RV_FLW(freg, addr, ofs)                              \
    ({                                                         \
        register rv_csr_t __addr = (rv_csr_t)(addr);           \
        __ASM volatile("flw " STRINGIFY(freg) ", %0(%1)  "     \
                     : : "I"(ofs), "r"(__addr)                 \
                     : "memory");                              \
    })

/**
 * \brief   Store a single-precision value from float point freg into memory using fsw instruction
 * \details The FSW instruction stores a single-precision value from floating point register to memory
 * \param [in]    freg   The floating point register(f0-f31), eg. FREG(0), f0
 * \param [in]    addr   The memory base address, 4 byte aligned required
 * \param [in]    ofs    a 12-bit immediate signed byte offset value, should be an const value
 * \remarks
 * * FLW and FSW operations need to make sure the address is 4 bytes aligned,
 *   otherwise it will cause exception code 4(Load address misaligned) or 6 (Store/AMO address misaligned)
 * * FLW and FSW do not modify the bits being transferred; in particular, the payloads of non-canonical
 * NaNs are preserved
 *
 */
#define __RV_FSW(freg, addr, ofs)                              \
    ({                                                         \
        register rv_csr_t __addr = (rv_csr_t)(addr);           \
        __ASM volatile("fsw " STRINGIFY(freg) ", %0(%1)  "     \
                     : : "I"(ofs), "r"(__addr)                 \
                     : "memory");                              \
    })

/**
 * \brief   Load a double-precision value from memory into float point register freg using fld instruction
 * \details The FLD instruction loads a double-precision floating point value from memory
 * address (addr + ofs) into floating point register freg(f0-f31)
 * \param [in]    freg   The floating point register, eg. FREG(0), f0
 * \param [in]    addr   The memory base address, 8 byte aligned required
 * \param [in]    ofs    a 12-bit immediate signed byte offset value, should be an const value
 * \attention
 * * Function only available for double precision floating point unit, FLEN = 64
 * \remarks
 * * FLD and FSD operations need to make sure the address is 8 bytes aligned,
 *   otherwise it will cause exception code 4(Load address misaligned) or 6 (Store/AMO address misaligned)
 * * FLD and FSD do not modify the bits being transferred; in particular, the payloads of non-canonical
 * NaNs are preserved.
 */
#define __RV_FLD(freg, addr, ofs)                              \
    ({                                                         \
        register rv_csr_t __addr = (rv_csr_t)(addr);           \
        __ASM volatile("fld " STRINGIFY(freg) ", %0(%1)  "     \
                     : : "I"(ofs), "r"(__addr)                 \
                     : "memory");                              \
    })

/**
 * \brief   Store a double-precision value from float point freg into memory using fsd instruction
 * \details The FSD instruction stores double-precision value from floating point register to memory
 * \param [in]    freg   The floating point register(f0-f31), eg. FREG(0), f0
 * \param [in]    addr   The memory base address, 8 byte aligned required
 * \param [in]    ofs    a 12-bit immediate signed byte offset value, should be an const value
 * \attention
 * * Function only available for double precision floating point unit, FLEN = 64
 * \remarks
 * * FLD and FSD operations need to make sure the address is 8 bytes aligned,
 *   otherwise it will cause exception code 4(Load address misaligned) or 6 (Store/AMO address misaligned)
 * * FLD and FSD do not modify the bits being transferred; in particular, the payloads of non-canonical
 * NaNs are preserved.
 *
 */
#define __RV_FSD(freg, addr, ofs)                              \
    ({                                                         \
        register rv_csr_t __addr = (rv_csr_t)(addr);           \
        __ASM volatile("fsd " STRINGIFY(freg) ", %0(%1)  "     \
                     : : "I"(ofs), "r"(__addr)                 \
                     : "memory");                              \
    })

/**
 * \def __RV_FLOAD
 * \brief   Load a float point value from memory into float point register freg using flw/fld instruction
 * \details
 * * For Single-Precison Floating-Point Mode(__FPU_PRESENT == 1, __RISCV_FLEN == 32):
 *   It will call \ref __RV_FLW to load a single-precision floating point value from memory to floating point register
 * * For Double-Precison Floating-Point Mode(__FPU_PRESENT == 2, __RISCV_FLEN == 64):
 *   It will call \ref __RV_FLD to load a double-precision floating point value from memory to floating point register
 *
 * \attention
 * Function behaviour is different for __FPU_PRESENT = 1 or 2, please see the real function this macro represent
 */
/**
 * \def __RV_FSTORE
 * \brief   Store a float value from float point freg into memory using fsw/fsd instruction
 * \details
 * * For Single-Precison Floating-Point Mode(__FPU_PRESENT == 1, __RISCV_FLEN == 32):
 *   It will call \ref __RV_FSW to store floating point register into memory
 * * For Double-Precison Floating-Point Mode(__FPU_PRESENT == 2, __RISCV_FLEN == 64):
 *   It will call \ref __RV_FSD to store floating point register into memory
 *
 * \attention
 * Function behaviour is different for __FPU_PRESENT = 1 or 2, please see the real function this macro represent
 */
#if __FPU_PRESENT == 1
#define __RV_FLOAD              __RV_FLW
#define __RV_FSTORE             __RV_FSW
/** \brief Type of FPU register, depends on the FLEN defined in RISC-V */
typedef uint32_t rv_fpu_t;
#elif __FPU_PRESENT == 2
#define __RV_FLOAD              __RV_FLD
#define __RV_FSTORE             __RV_FSD
/** \brief Type of FPU register, depends on the FLEN defined in RISC-V */
typedef uint64_t rv_fpu_t;
#endif /* __FPU_PRESENT == 2 */

/**
 * \brief   Save FPU context into variables for interrupt nesting
 * \details
 * This macro is used to declare variables which are used for saving
 * FPU context, and it will store the nessary fpu registers into
 * these variables, it need to be used in a interrupt when in this
 * interrupt fpu registers are used.
 * \remarks
 * - It need to be used together with \ref RESTORE_FPU_CONTEXT
 * - Don't use variable names __fpu_context in your ISR code
 * - If you isr code will use fpu registers, and this interrupt is nested.
 * Then you can do it like this:
 * \code
 * void eclic_mtip_handler(void)
 * {
 *     // !!!Interrupt is enabled here!!!
 *     // !!!Higher priority interrupt could nest it!!!
 *
 *     // Necessary only when you need to use fpu registers
 *     // in this isr handler functions
 *     SAVE_FPU_CONTEXT();
 *
 *     // put you own interrupt handling code here
 *
 *     // pair of SAVE_FPU_CONTEXT()
 *     RESTORE_FPU_CONTEXT();
 * }
 * \endcode
 */
#define SAVE_FPU_CONTEXT()                                                  \
        rv_fpu_t __fpu_context[20];                                         \
        __RV_FSTORE(FREG(0),  __fpu_context, 0  << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(1),  __fpu_context, 1  << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(2),  __fpu_context, 2  << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(3),  __fpu_context, 3  << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(4),  __fpu_context, 4  << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(5),  __fpu_context, 5  << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(6),  __fpu_context, 6  << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(7),  __fpu_context, 7  << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(10), __fpu_context, 8  << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(11), __fpu_context, 9  << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(12), __fpu_context, 10 << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(13), __fpu_context, 11 << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(14), __fpu_context, 12 << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(15), __fpu_context, 13 << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(16), __fpu_context, 14 << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(17), __fpu_context, 15 << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(28), __fpu_context, 16 << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(29), __fpu_context, 17 << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(30), __fpu_context, 18 << LOG_FPREGBYTES);         \
        __RV_FSTORE(FREG(31), __fpu_context, 19 << LOG_FPREGBYTES);

/**
 * \brief   Restore necessary fpu registers from variables for interrupt nesting
 * \details
 * This macro is used restore necessary fpu registers from pre-defined variables
 * in \ref SAVE_FPU_CONTEXT macro.
 * \remarks
 * - It need to be used together with \ref SAVE_FPU_CONTEXT
 */
#define RESTORE_FPU_CONTEXT()                                               \
        __RV_FLOAD(FREG(0),  __fpu_context, 0  << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(1),  __fpu_context, 1  << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(2),  __fpu_context, 2  << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(3),  __fpu_context, 3  << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(4),  __fpu_context, 4  << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(5),  __fpu_context, 5  << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(6),  __fpu_context, 6  << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(7),  __fpu_context, 7  << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(10), __fpu_context, 8  << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(11), __fpu_context, 9  << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(12), __fpu_context, 10 << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(13), __fpu_context, 11 << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(14), __fpu_context, 12 << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(15), __fpu_context, 13 << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(16), __fpu_context, 14 << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(17), __fpu_context, 15 << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(28), __fpu_context, 16 << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(29), __fpu_context, 17 << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(30), __fpu_context, 18 << LOG_FPREGBYTES);          \
        __RV_FLOAD(FREG(31), __fpu_context, 19 << LOG_FPREGBYTES);
#else
#define SAVE_FPU_CONTEXT()
#define RESTORE_FPU_CONTEXT()
#endif /* __FPU_PRESENT > 0 */
/** @} */ /* End of Doxygen Group NMSIS_Core_FPU_Functions */

#ifdef __cplusplus
}
#endif
#endif /** __RISCV_EXT_FPU_H__  */
