/**************************************************************************//**
 * @file     pmsis_gcc.h
 * @brief    CMSIS compiler GCC header file
 * @version  V5.0.2
 * @date     4. April 2020
 ******************************************************************************/
/*
 * Copyright (c) 2009-2017 ARM Limited. All rights reserved.
 * Copyright (c) 2020 ETH Zurich
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
/*
   Modifications copyright (C) 2018 GreenWaves Technologies

   - Add __RISCV_ARCH_GAP__ macro define
   - Delete and Change some Cortex-M registers access functions, and replace them by
     RISC-V 32-bit GAP8 registers access functions
   - Add some GAP8 builtin functions
*/

#ifndef __CMSIS_GCC_H
#define __CMSIS_GCC_H

#include <stdint.h>

#define __RISCV_ARCH_PULP__ 1
/* ignore some GCC warnings */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"

/* Fallback for __has_builtin */
#ifndef __has_builtin
  #define __has_builtin(x) (0)
#endif

/* CMSIS compiler specific defines */
#ifndef   __ASM
  #define __ASM                                  __asm
#endif
#ifndef   __INLINE
  #define __INLINE                               inline
#endif
#ifndef   __STATIC_INLINE
  #define __STATIC_INLINE                        static inline
#endif
#ifndef   __NO_RETURN
  #define __NO_RETURN                            __attribute__((noreturn))
#endif
#ifndef   __USED
  #define __USED                                 __attribute__((used))
#endif
#ifndef   __WEAK
  #define __WEAK                                 __attribute__((weak))
#endif
#ifndef   __PACKED
  #define __PACKED                               __attribute__((packed, aligned(1)))
#endif
#ifndef   __PACKED_STRUCT
  #define __PACKED_STRUCT                        struct __attribute__((packed, aligned(1)))
#endif
#ifndef   __PACKED_UNION
  #define __PACKED_UNION                         union __attribute__((packed, aligned(1)))
#endif
#ifndef   __UNALIGNED_UINT32        /* deprecated */
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed)) T_UINT32 { uint32_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT32(x)                  (((struct T_UINT32 *)(x))->v)
#endif
#ifndef   __UNALIGNED_UINT16_WRITE
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  __PACKED_STRUCT T_UINT16_WRITE { uint16_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT16_WRITE(addr, val)    (void)((((struct T_UINT16_WRITE *)(void *)(addr))->v) = (val))
#endif
#ifndef   __UNALIGNED_UINT16_READ
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  __PACKED_STRUCT T_UINT16_READ { uint16_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT16_READ(addr)          (((const struct T_UINT16_READ *)(const void *)(addr))->v)
#endif
#ifndef   __UNALIGNED_UINT32_WRITE
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  __PACKED_STRUCT T_UINT32_WRITE { uint32_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT32_WRITE(addr, val)    (void)((((struct T_UINT32_WRITE *)(void *)(addr))->v) = (val))
#endif
#ifndef   __UNALIGNED_UINT32_READ
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  __PACKED_STRUCT T_UINT32_READ { uint32_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT32_READ(addr)          (((const struct T_UINT32_READ *)(const void *)(addr))->v)
#endif
#ifndef   __ALIGNED
  #define __ALIGNED(x)                           __attribute__((aligned(x)))
#endif
#ifndef   __RESTRICT
  #define __RESTRICT                             __restrict
#endif


#define __get_BASEPRI()      0
#define __get_PRIMASK()      1
/*@} end of CMSIS_Core_RegAccFunctions */

/* ##########################  Core Instruction Access  ######################### */
/** \defgroup CMSIS_Core_InstructionInterface CMSIS Core Instruction Interface
  Access to dedicated instructions
  @{
*/

/* Define macros for porting to both thumb1 and thumb2.
 * For thumb1, use low register (r0-r7), specified by constraint "l"
 * Otherwise, use general registers, specified by constraint "r" */
#if defined (__thumb__) && !defined (__thumb2__)
#define __CMSIS_GCC_OUT_REG(r) "=l" (r)
#define __CMSIS_GCC_RW_REG(r) "+l" (r)
#define __CMSIS_GCC_USE_REG(r) "l" (r)
#else
#define __CMSIS_GCC_OUT_REG(r) "=r" (r)
#define __CMSIS_GCC_RW_REG(r) "+r" (r)
#define __CMSIS_GCC_USE_REG(r) "r" (r)
#endif

/**
  \brief   No Operation
  \details No Operation does nothing. This instruction can be used for code alignment purposes.
 */
//__attribute__((always_inline)) __STATIC_INLINE void __NOP(void)
//{
//  __ASM volatile ("nop");
//}
#define __NOP()                             __ASM volatile ("nop")       /* This implementation generates debug information */

/**
  \brief   Wait For Interrupt
  \details Wait For Interrupt is a hint instruction that suspends execution until one of a number of events occurs.
 */
//__attribute__((always_inline)) __STATIC_INLINE void __WFI(void)
//{
//  __ASM volatile ("wfi");
//}
#define __WFI()                             __ASM volatile ("wfi")       /* This implementation generates debug information */


/**
  \brief   Wait For Event
  \details Wait For Event is a hint instruction that permits the processor to enter
           a low-power state until one of a number of events occurs.
 */
//__attribute__((always_inline)) __STATIC_INLINE void __WFE(void)
//{
//  __ASM volatile ("wfe");
//}
#define __WFE()                             __ASM volatile ("wfe")       /* This implementation generates debug information */


/**
  \brief   Send Event
  \details Send Event is a hint instruction. It causes an event to be signaled to the CPU.
 */
//__attribute__((always_inline)) __STATIC_INLINE void __SEV(void)
//{
//  __ASM volatile ("sev");
//}
#define __SEV()                             __ASM volatile ("sev")       /* This implementation generates debug information */


/**
  \brief   Instruction Synchronization Barrier
  \details Instruction Synchronization Barrier flushes the pipeline in the processor,
           so that all instructions following the ISB are fetched from cache or memory,
           after the instruction has been completed.
 */
__attribute__((always_inline)) __STATIC_INLINE void __ISB(void)
{
  //  __ASM volatile ("isb 0xF":::"memory");
}


/**
  \brief   Data Synchronization Barrier
  \details Acts as a special kind of Data Memory Barrier.
           It completes when all explicit memory accesses before this instruction complete.
 */
__attribute__((always_inline)) __STATIC_INLINE void __DSB(void)
{
//  __ASM volatile ("dsb 0xF":::"memory");
}


/**
  \brief   Data Memory Barrier
  \details Ensures the apparent order of the explicit memory operations before
           and after the instruction, without ensuring their completion.
 */
__attribute__((always_inline)) __STATIC_INLINE void __DMB(void)
{
  //  __ASM volatile ("dmb 0xF":::"memory");
}


/**
  \brief   Count leading zeros
  \details Counts the number of leading zeros of a data value.
  \param [in]  value  Value to count the leading zeros
  \return             number of leading zeros in value
 */
#define __CLZ             __builtin_clz


/**
  \ingroup PULP_BUILTIN_MARCO
  @{
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __ExtInsMaskFast(uint32_t size, uint32_t offset) { return ((((size - 1))<<5) | (offset)); }
__attribute__((always_inline)) __STATIC_INLINE uint32_t __ExtInsMaskSafe(uint32_t size, uint32_t offset) { return ((((size - 1) & 0x1F)<<5) | (offset & 0x1F)); }

/*! @brief Packing of scalars into vectors */
#define __VEC_PACK2(x, y)                     __builtin_pulp_pack2((int16_t)  x, (int16_t)  y)
#define __VEC_PACKU2(x, y)                    __builtin_pulp_pack2((uint16_t) x, (uint16_t) y)
#define __VEC_PACK4(x, y, z, t)               __builtin_pulp_pack4((int8_t)   x, (int8_t)   y, (int8_t)  z, (int8_t)  t)
#define __VEC_PACKU4(x, y, z, t)              __builtin_pulp_pack4((uint8_t)  x, (uint8_t)  y, (uint8_t) z, (uint8_t) t)

/*! @brief Max */
#define __MAX(x, y)              __builtin_pulp_maxsi((x), (y))
#define __MAX2(x, y)             __builtin_pulp_max2(x, y)
#define __MAX4(x, y)             __builtin_pulp_max4(x, y)

#define __MAXU2(x, y)            __builtin_pulp_maxu2(x, y)
#define __MAXU4(x, y)            __builtin_pulp_maxu4(x, y)

/*! @brief Min */
#define __MIN2(x, y)             __builtin_pulp_min2(x, y)
#define __MIN4(x, y)             __builtin_pulp_min4(x, y)

#define __MINU2(x, y)            __builtin_pulp_minu2(x, y)
#define __MINU4(x, y)            __builtin_pulp_minu4(x, y)

/*! @brief Clip */
#define __CLIP(x, precision)     __builtin_pulp_clip(x, -(1<<(precision)), (1<<precision)-1)
#define __CLIPU(x, precision)    __builtin_pulp_clipu(x, 0, (1<<precision)-1)

/*! @brief Abs */
#define __ABS2(x)                __builtin_pulp_abs2(x)
#define __ABS4(x)                __builtin_pulp_abs4(x)

/* Unary minus */
#define __NEG2(x)                __builtin_pulp_neg2(x)
#define __NEG4(x)                __builtin_pulp_neg4(x)

/* Addition */
#define __ADD2(x, y)             __builtin_pulp_add2(x, y)
#define __ADD4(x, y)             __builtin_pulp_add4(x, y)

/* Substraction */
#define __SUB2(x, y)             __builtin_pulp_sub2(x, y)
#define __SUB4(x, y)             __builtin_pulp_sub4(x, y)

/* Average */
#define __AVG2(x, y)             __builtin_pulp_avg2(x, y)
#define __AVG4(x, y)             __builtin_pulp_avg4(x, y)

/* Average unsigned */
#define __AVGU2(x, y)            __builtin_pulp_avgu2(x, y)
#define __AVGU4(x, y)            __builtin_pulp_avgu4(x, y)

/* Bitwise and */
#define __AND2(x, y)             __builtin_pulp_and2(x, y)
#define __AND4(x, y)             __builtin_pulp_and4(x, y)

/* Bitwise or */
#define __OR2(x, y)              __builtin_pulp_or2(x, y)
#define __OR4(x, y)              __builtin_pulp_or4(x, y)

/* Bitwise exor */
#define __EXOR2(x, y)            __builtin_pulp_exor2(x, y)
#define __EXOR4(x, y)            __builtin_pulp_exor4(x, y)

/* Logical shift right */
#define __SRL2(x, y)             __builtin_pulp_srl2(x, y)
#define __SRL4(x, y)             __builtin_pulp_srl4(x, y)

/* Arithmetic shift right */
#define __SRA2(x, y)             __builtin_pulp_sra2(x, y)
#define __SRA4(x, y)             __builtin_pulp_sra4(x, y)

/* Logical shift left */
#define __SLL2(x, y)             __builtin_pulp_sll2(x, y)
#define __SLL4(x, y)             __builtin_pulp_sll4(x, y)

/*! @brief Mac */
#define __MAC(acc, x, y)         __builtin_pulp_mac(x, y, acc)
#define __MSU(acc, x, y)         __builtin_pulp_msu(x, y, acc)
#define __MACS(acc, x, y)        __builtin_pulp_macs(x, y, acc)
#define __MACHHS(acc, x, y)      __builtin_pulp_machhs(x, y, acc)
#define __MACU(acc, x, y)        __builtin_pulp_macu(x, y, acc)
#define __MACHHU(acc, x, y)      __builtin_pulp_machhu(x, y, acc)

#define __MACSN(acc, x, y, n)      __builtin_pulp_macsN(x, y, acc, n)
#define __MACUN(acc, x, y, n)      __builtin_pulp_macuN(x, y, acc, n)
#define __MACSRN(acc, x, y, n)     __builtin_pulp_macsRN(x, y, acc, n, (1<<(n-1)))
#define __MACURN(acc, x, y, n)     __builtin_pulp_macuRN(x, y, acc, n, (1<<(n-1)))

#define __MACHHSN(acc, x, y, n)    __builtin_pulp_machhsN(x, y, acc, n)
#define __MACHHUN(acc, x, y, n)    __builtin_pulp_machhuN(x, y, acc, n)
#define __MACHHSRN(acc, x, y, n)   __builtin_pulp_machhsN(x, y, acc, n, (1<<(n-1)))
#define __MACHHURN(acc, x, y, n)   __builtin_pulp_machhuN(x, y, acc, n, (1<<(n-1)))

/*! @brief Multiplications */
#define __MULS(x, y)            __builtin_pulp_muls(x, y)
#define __MULU(x, y)            __builtin_pulp_mulu(x, y)
#define __MULHHS(x, y)          __builtin_pulp_mulhhs(x, y)
#define __MULHHU(x, y)          __builtin_pulp_mulhhu(x, y)

#define __MULSN(x, y, n)        __builtin_pulp_mulsN(x, y, n)
#define __MULSRN(x, y, n)       __builtin_pulp_mulsRN(x, y, n, (1<<(n-1)))
#define __MULUN(x, y, n)        __builtin_pulp_muluN(x, y, n)
#define __MULURN(x, y, n)       __builtin_pulp_muluRN(x, y, n, (1<<(n-1)))

#define __MULHHSN(x, y, n)      __builtin_pulp_mulhhsN(x, y, n)
#define __MULHHSRN(x, y, n)     __builtin_pulp_mulhhsRN(x, y, n, (1<<(n-1)))
#define __MULHHUN(x, y, n)      __builtin_pulp_mulhhuN(x, y, n)
#define __MULHHURN(x, y, n)     __builtin_pulp_mulhhuRN(x, y, n, (1<<(n-1)))

/*! @brief Vectorial product and sum of products */
#define __DOTP2(x, y)           __builtin_pulp_dotsp2(x, y)
#define __DOTPU2(x, y)          __builtin_pulp_dotup2(x, y)
#define __DOTPUS2(x, y)         __builtin_pulp_dotusp2(x, y)

#define __SUM_DOTP2(x, y, z)    __builtin_pulp_sdotsp2(x, y, z)
#define __SUM_DOTPU2(x, y, z)   __builtin_pulp_sdotup2(x, y, z)
#define __SUM_DOTPUS2(x, y, z)  __builtin_pulp_sdotusp2(x, y, z)

#define __DOTP4(x, y)           __builtin_pulp_dotsp4(x, y)
#define __DOTPU4(x, y)          __builtin_pulp_dotup4(x, y)
#define __DOTPUS4(x, y)         __builtin_pulp_dotusp4(x, y)

#define __SUM_DOTP4(x, y, z)    __builtin_pulp_sdotsp4(x, y, z)
#define __SUM_DOTPU4(x, y, z)   __builtin_pulp_sdotup4(x, y, z)
#define __SUM_DOTPUS4(x, y, z)  __builtin_pulp_sdotusp4(x, y, z)


/*! @brief Complex Multiplication, Q15x15 into Q15, with optional post scaling by 1 or 2 */
#define __CPLX_MULS(x, y)        __builtin_pulp_cplxmuls(x, y)
#define __CPLX_MULS_DIV2(x, y)   __builtin_pulp_cplxmulsdiv2(x, y)
#define __CPLX_MULS_DIV4(x, y)   __builtin_pulp_cplxmulsdiv4(x, y)

/*! @brief Complex conjugate */
#define __CPLX_CONJ(x)           __builtin_pulp_cplx_conj(x)

/*! @brief Complex rotation by -pi/2 */
#define __CPLX_MJ(x)             __builtin_pulp_cplxmjrot2(x)

/*! @brief Complex substration, result rotated by -pi/2 */
#define __SUB2_ROTMJ(x, y)       __builtin_pulp_sub2rotmj(x, y)

/*! @brief Complex addition with post scaling by 1 or 2 */
#define __ADD2_DIV2(x, y)        __builtin_pulp_add2div2(x, y)
#define __ADD2_DIV4(x, y)        __builtin_pulp_add2div4(x, y)

/*! @brief Complex subtraction with post scaling by 1 or 2 */
#define __SUB2_DIV2(x, y)        __builtin_pulp_sub2div2(x, y)
#define __SUB2_DIV4(x, y)        __builtin_pulp_sub2div4(x, y)

/*! @brief Viterbi Max and Viterbi Select, pair of Q15 */
#define __VIT_MAX(x, y)          __builtin_pulp_vitmax2(x, y)
#define __VIT_SEL(x, y)          __builtin_pulp_vitsel2(x, y)

/*! @brief Position of the most significant bit of x */
#define __FL1(x)                 __builtin_pulp_fl1(x)

/*! @brief Number of sign bits */
#define __CLB(x)                 __builtin_pulp_clb(x)

/*! @brief Bit Extraction */
#define __BIT_EXTRACT(src, size, off)           __builtin_pulp_bextract(src, size, off)
#define __BIT_EXTRACTU(src, size, off)          __builtin_pulp_bextractu(src, size, off)

#define __BIT_EXTRACT_R(src, size, off)         __builtin_pulp_bextract_r(src,  __ExtInsMaskFast(size, off))
#define __BIT_EXTRACTU_R(src, size, off)        __builtin_pulp_bextractu_r(src, __ExtInsMaskFast(size, off))

#define __BIT_EXTRACT_R_SAFE(src, size, off)    __builtin_pulp_bextract_r(src,  __ExtInsMaskSafe(size, off))
#define __BIT_EXTRACTU_R_SAFE(src, size, off)   __builtin_pulp_bextractu_r(src, __ExtInsMaskSafe(size, off))

/*! @brief Bit insertion */
#define __BIT_INSERT(dst, src, size, off)        __builtin_pulp_binsert(dst, ~(((1<<size)-1)<<off), src, (((1<<size)-1)<<off), off)
#define __BIT_INSERT_R(dst, src, size, off)      __builtin_pulp_binsert_r(dst, src, __ExtInsMaskFast(size, off))
#define __BIT_INSERT_R_SAFE(dst, src, size, off) __builtin_pulp_binsert_r(dst, src, __ExtInsMaskSafe(size, off))

/*! @brief 1 bit rotation to the right, 32 bits input */
#define __ROTR(x)                                __builtin_pulp_rotr(x)

/*! @brief Add with normalization and rounding */
#define __ADD_ROUND_NORM(x, y, scale)            __builtin_pulp_addRN(x, y, scale, (1<<(scale-1)))
#define __ADD_ROUND_NORM_REG(x, y, scale)        __builtin_pulp_addRN_r(x, y, scale)
#define __ADD_ROUND_NORMU(x, y, scale)           __builtin_pulp_adduRN(x, y, scale, (1<<(scale-1)))
#define __ADD_ROUND_NORMU_REG(x, y, scale)       __builtin_pulp_adduRN_r(x, y, scale)

/*! @brief Normalization and rounding */
#define __ROUND_NORM(x, scale)                   __builtin_pulp_addRN(x, 0, scale, (1<<(scale-1)))
#define __ROUND_NORM_REG(x, scale)               __builtin_pulp_addRN_r(x, 0, scale)
#define __ROUND_NORMU(x, scale)                  __builtin_pulp_adduRN(x, 0, scale, (1<<(scale-1)))
#define __ROUND_NORMU_REG(x, scale)              __builtin_pulp_adduRN_r(x, 0, scale)
/*@} end of group PULP_BUILTIN_MARCO */

/**
  \ingroup PULP_VECTOR_TYPE
  @{
 */
typedef   signed short v2s   __attribute__((vector_size (4)));
typedef unsigned short v2u   __attribute__((vector_size (4)));

typedef   signed char  v4s   __attribute__((vector_size (4)));
typedef unsigned char  v4u   __attribute__((vector_size (4)));

typedef signed char    v4qi   __attribute__((vector_size (4)));
typedef unsigned char  v4qu   __attribute__((vector_size (4)));

typedef signed short   v2hi   __attribute__((vector_size (4)));
typedef unsigned short v2hu   __attribute__((vector_size (4)));
/*@} end of group PULP_VECTOR_TYPE */

#pragma GCC diagnostic pop

#endif /* __CMSIS_GCC_H */
