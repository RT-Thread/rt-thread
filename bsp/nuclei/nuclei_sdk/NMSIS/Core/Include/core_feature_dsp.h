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
#ifndef __CORE_FEATURE_DSP__
#define __CORE_FEATURE_DSP__

/*!
 * @file     core_feature_dsp.h
 * @brief    DSP feature API header file for Nuclei N/NX Core
 */
/*
 * DSP Feature Configuration Macro:
 * 1. __DSP_PRESENT:  Define whether Digital Signal Processing Unit(DSP) is present or not
 *   * 0: Not present
 *   * 1: Present
 */
#ifdef __cplusplus
 extern "C" {
#endif

#if defined(__DSP_PRESENT) && (__DSP_PRESENT == 1)

/* ###########################  CPU SIMD DSP Intrinsic Functions ########################### */
/**
 * \defgroup NMSIS_Core_DSP_Intrinsic   Intrinsic Functions for SIMD Instructions
 * \ingroup  NMSIS_Core
 * \brief    Functions that generate RISC-V DSP SIMD instructions.
 * \details
 *
 * The following functions generate specified RISC-V SIMD instructions that cannot be directly accessed by compiler.
 * * **DSP ISA Extension Instruction Summary**
 *   + **Shorthand Definitions**
 *     - r.H == rH1: r[31:16], r.L == r.H0: r[15:0]
 *     - r.B3: r[31:24], r.B2: r[23:16], r.B1: r[15:8], r.B0: r[7:0]
 *     - r.B[x]: r[(x*8+7):(x*8+0)]
 *     - r.H[x]: r[(x*16+7):(x*16+0)]
 *     - r.W[x]: r[(x*32+31):(x*32+0)]
 *     - r[xU]: the upper 32-bit of a 64-bit number; xU represents the GPR number that contains this upper part 32-bit value.
 *     - r[xL]: the lower 32-bit of a 64-bit number; xL represents the GPR number that contains this lower part 32-bit value.
 *     - r[xU].r[xL]: a 64-bit number that is formed from a pair of GPRs.
 *     - s>>: signed arithmetic right shift:
 *     - u>>: unsigned logical right shift
 *     - SAT.Qn(): Saturate to the range of [-2^n, 2^n-1], if saturation happens, set PSW.OV.
 *     - SAT.Um(): Saturate to the range of [0, 2^m-1], if saturation happens, set PSW.OV.
 *     - RUND(): Indicate `rounding`, i.e., add 1 to the most significant discarded bit for right shift or MSW-type multiplication instructions.
 *     - Sign or Zero Extending functions:
 *       - SEm(data): Sign-Extend data to m-bit.:
 *       - ZEm(data): Zero-Extend data to m-bit.
 *     - ABS(x): Calculate the absolute value of `x`.
 *     - CONCAT(x,y): Concatinate `x` and `y` to form a value.
 *     - u<: Unsinged less than comparison.
 *     - u<=: Unsinged less than & equal comparison.
 *     - u>: Unsinged greater than comparison.
 *     - s*: Signed multiplication.
 *     - u*: Unsigned multiplication.
 *
 *   @{
 */
/** @} */ /* End of Doxygen Group NMSIS_Core_DSP_Intrinsic */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_SIMD_DATA_PROCESS      SIMD Data Processing Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic
 * \brief    SIMD Data Processing Instructions
 * \details
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB      SIMD 16-bit Add/Subtract Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_SIMD_DATA_PROCESS
 * \brief    SIMD 16-bit Add/Subtract Instructions
 * \details
 * Based on the combination of the types of the two 16-bit arithmetic operations, the SIMD 16-bit
 * add/subtract instructions can be classified into 6 main categories: Addition (two 16-bit addition),
 * Subtraction (two 16-bit subtraction), Crossed Add & Sub (one addition and one subtraction), and
 * Crossed Sub & Add (one subtraction and one addition), Straight Add & Sub (one addition and one
 * subtraction), and Straight Sub & Add (one subtraction and one addition).
 * Based on the way of how an overflow condition is handled, the SIMD 16-bit add/subtract
 * instructions can be classified into 5 groups: Wrap-around (dropping overflow), Signed Halving
 * (keeping overflow by dropping 1 LSB bit), Unsigned Halving, Signed Saturation (clipping overflow),
 * and Unsigned Saturation.
 * Together, there are 30 SIMD 16-bit add/subtract instructions.
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_ADDSUB      SIMD 8-bit Addition & Subtraction Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_SIMD_DATA_PROCESS
 * \brief    SIMD 8-bit Addition & Subtraction Instructions
 * \details
 * Based on the types of the four 8-bit arithmetic operations, the SIMD 8-bit add/subtract instructions
 * can be classified into 2 main categories: Addition (four 8-bit addition), and Subtraction (four 8-bit
 * subtraction).
 * Based on the way of how an overflow condition is handled for singed or unsigned operation, the
 * SIMD 8-bit add/subtract instructions can be classified into 5 groups: Wrap-around (dropping
 * overflow), Signed Halving (keeping overflow by dropping 1 LSB bit), Unsigned Halving, Signed
 * Saturation (clipping overflow), and Unsigned Saturation.
 * Together, there are 10 SIMD 8-bit add/subtract instructions.
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_SHIFT      SIMD 16-bit Shift Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_SIMD_DATA_PROCESS
 * \brief    SIMD 16-bit Shift Instructions
 * \details
 * there are 14 SIMD 16-bit shift instructions.
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_SHIFT      SIMD 8-bit Shift Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_SIMD_DATA_PROCESS
 * \brief    SIMD 8-bit Shift Instructions
 * \details
 *  there are 14 SIMD 8-bit shift instructions.
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_CMP      SIMD 16-bit Compare Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_SIMD_DATA_PROCESS
 * \brief    SIMD 16-bit Compare Instructions
 * \details
 *  there are 5 SIMD 16-bit Compare instructions.
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_CMP      SIMD 8-bit Compare Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_SIMD_DATA_PROCESS
 * \brief    SIMD 8-bit Compare Instructions
 * \details
 *  there are 5  SIMD 8-bit Compare instructions.
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_MULTIPLY      SIMD 16-bit Multiply Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_SIMD_DATA_PROCESS
 * \brief    SIMD 16-bit Multiply Instructions
 * \details
 * there are 6 SIMD 16-bit Multiply instructions.
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_MULTIPLY      SIMD 8-bit Multiply Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_SIMD_DATA_PROCESS
 * \brief    SIMD 8-bit Multiply Instructions
 * \details
 *  there are 6 SIMD 8-bit Multiply instructions.
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_MISC      SIMD 16-bit Miscellaneous Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_SIMD_DATA_PROCESS
 * \brief    SIMD 16-bit Miscellaneous Instructions
 * \details
 *  there are 10 SIMD 16-bit Misc instructions.
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_MISC      SIMD 8-bit Miscellaneous Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_SIMD_DATA_PROCESS
 * \brief    SIMD 8-bit Miscellaneous Instructions
 * \details
 *  there are 10 SIMD 8-bit Miscellaneous instructions.
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_UNPACK      SIMD 8-bit Unpacking Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_SIMD_DATA_PROCESS
 * \brief    SIMD 8-bit Unpacking Instructions
 * \details
 *  there are 8 SIMD 8-bit Unpacking instructions.
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_NON_SIMD      Non-SIMD Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic
 * \brief    Non-SIMD Instructions
 * \details
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q15_SAT_ALU      Non-SIMD Q15 saturation ALU Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NON_SIMD
 * \brief    Non-SIMD Q15 saturation ALU Instructions
 * \details
 * there are 7 Non-SIMD Q15 saturation ALU Instructions
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q31_SAT_ALU      Non-SIMD Q31 saturation ALU Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NON_SIMD
 * \brief    Non-SIMD Q31 saturation ALU Instructions
 * \details
 *  there are Non-SIMD Q31 saturation ALU Instructions
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_32B_COMPUTATION      32-bit Computation Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NON_SIMD
 * \brief    32-bit Computation Instructions
 * \details
 * there are 8 32-bit Computation Instructions
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_OV_FLAG_SC      OV (Overflow) flag Set/Clear Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NON_SIMD
 * \brief    OV (Overflow) flag Set/Clear Instructions
 * \details
 * The following table lists the user instructions related to Overflow (OV) flag manipulation. there are 2 OV (Overflow) flag Set/Clear Instructions
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_MISC      Non-SIMD Miscellaneous Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NON_SIMD
 * \brief    Non-SIMD Miscellaneous Instructions
 * \details
 * There are 13 Miscellaneous Instructions here.
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_PART_SIMD_DATA_PROCESS      Partial-SIMD Data Processing Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic
 * \brief    Partial-SIMD Data Processing Instructions
 * \details
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_PACK      SIMD 16-bit Packing Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_PART_SIMD_DATA_PROCESS
 * \brief    SIMD 16-bit Packing Instructions
 * \details
 * there are 4 SIMD16-bit Packing Instructions.
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X32_MAC      Signed MSW 32x32 Multiply and Add Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_PART_SIMD_DATA_PROCESS
 * \brief    Signed MSW 32x32 Multiply and Add Instructions
 * \details
 *  there are 8 Signed MSW 32x32 Multiply and Add Instructions
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X16_MAC      Signed MSW 32x16 Multiply and Add Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_PART_SIMD_DATA_PROCESS
 * \brief    Signed MSW 32x16 Multiply and Add Instructions
 * \details
 * there are 15 Signed MSW 32x16 Multiply and Add Instructions
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB      Signed 16-bit Multiply 32-bit Add/Subtract Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_PART_SIMD_DATA_PROCESS
 * \brief    Signed 16-bit Multiply 32-bit Add/Subtract Instructions
 * \details
 *  there are 18 Signed 16-bit Multiply 32-bit Add/Subtract Instructions
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_64B_ADDSUB      Signed 16-bit Multiply 64-bit Add/Subtract Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_PART_SIMD_DATA_PROCESS
 * \brief    Signed 16-bit Multiply 64-bit Add/Subtract Instructions
 * \details
 *  there is Signed 16-bit Multiply 64-bit Add/Subtract Instructions
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_PART_SIMD_MISC      Partial-SIMD Miscellaneous Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_PART_SIMD_DATA_PROCESS
 * \brief    Partial-SIMD Miscellaneous Instructions
 * \details
 *  there are  7 Partial-SIMD Miscellaneous Instructions
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_8B_MULT_32B_ADD      8-bit Multiply with 32-bit Add Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_PART_SIMD_DATA_PROCESS
 * \brief    8-bit Multiply with 32-bit Add Instructions
 * \details
 * there are  3 8-bit Multiply with 32-bit Add Instructions
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_64B_PROFILE      64-bit Profile Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic
 * \brief    64-bit Profile Instructions
 * \details
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_64B_ADDSUB      64-bit Addition & Subtraction Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_64B_PROFILE
 * \brief    64-bit Addition & Subtraction Instructions
 * \details
 * there are 10 64-bit Addition & Subtraction Instructions.
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_32B_MULT_64B_ADDSUB      32-bit Multiply with 64-bit Add/Subtract Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_64B_PROFILE
 * \brief    32-bit Multiply with 64-bit Add/Subtract Instructions
 * \details
 *  there are 32-bit Multiply 64-bit Add/Subtract Instructions
 */

/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_64B_ADDSUB      Signed 16-bit Multiply with 64-bit Add/Subtract Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic_64B_PROFILE
 * \brief    Signed 16-bit Multiply with 64-bit Add/Subtract Instructions
 * \details
 * there are 10 Signed 16-bit Multiply with 64-bit Add/Subtract Instructions
 */

/* ===== Inline Function Start for 3.1. ADD8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_ADDSUB
 * \brief ADD8 (SIMD 8-bit Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * ADD8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit integer element additions simultaneously.
 *
 * **Description**:\n
 * This instruction adds the 8-bit integer elements in Rs1 with the 8-bit integer elements
 * in Rs2, and then writes the 8-bit element results to Rd.
 *
 * **Note**:\n
 * This instruction can be used for either signed or unsigned addition.
 *
 * **Operations**:\n
 * ~~~
 * Rd.B[x] = Rs1.B[x] + Rs2.B[x];
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_ADD8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("add8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.1. ADD8 ===== */

/* ===== Inline Function Start for 3.2. ADD16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief ADD16 (SIMD 16-bit Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * ADD16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit integer element additions simultaneously.
 *
 * **Description**:\n
 * This instruction adds the 16-bit integer elements in Rs1 with the 16-bit integer
 * elements in Rs2, and then writes the 16-bit element results to Rd.
 *
 * **Note**:\n
 * This instruction can be used for either signed or unsigned addition.
 *
 * **Operations**:\n
 * ~~~
 * Rd.H[x] = Rs1.H[x] + Rs2.H[x];
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_ADD16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("add16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.2. ADD16 ===== */

/* ===== Inline Function Start for 3.3. ADD64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_64B_ADDSUB
 * \brief ADD64 (64-bit Addition)
 * \details
 * **Type**: 64-bit Profile
 *
 * **Syntax**:\n
 * ~~~
 * ADD64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Add two 64-bit signed or unsigned integers.
 *
 * **RV32 Description**:\n
 * This instruction adds the 64-bit integer of an even/odd pair of registers specified
 * by Rs1(4,1) with the 64-bit integer of an even/odd pair of registers specified by Rs2(4,1), and then
 * writes the 64-bit result to an even/odd pair of registers specified by Rd(4,1).
 * Rx(4,1), i.e., value d, determines the even/odd pair group of two registers. Specifically, the register
 * pair includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 *
 * **RV64 Description**:\n
 * This instruction has the same behavior as the ADD instruction in RV64I.
 *
 * **Note**:\n
 * This instruction can be used for either signed or unsigned addition.
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 *  t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 *  a_L = CONCAT(Rs1(4,1),1'b0); a_H = CONCAT(Rs1(4,1),1'b1);
 *  b_L = CONCAT(Rs2(4,1),1'b0); b_H = CONCAT(Rs2(4,1),1'b1);
 *  R[t_H].R[t_L] = R[a_H].R[a_L] + R[b_H].R[b_L];
 * RV64:
 *  Rd = Rs1 + Rs2;
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_ADD64(unsigned long long a, unsigned long long b)
{
    unsigned long long result;
    __ASM volatile("add64 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.3. ADD64 ===== */

/* ===== Inline Function Start for 3.4. AVE ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_MISC
 * \brief AVE (Average with Rounding)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * AVE Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Calculate the average of the contents of two general registers.
 *
 * **Description**:\n
 * This instruction calculates the average value of two signed integers stored in Rs1 and
 * Rs2, rounds up a half-integer result to the nearest integer, and writes the result to Rd.
 *
 * **Operations**:\n
 * ~~~
 * Sum = CONCAT(Rs1[MSB],Rs1[MSB:0]) + CONCAT(Rs2[MSB],Rs2[MSB:0]) + 1;
 * Rd = Sum[(MSB+1):1];
 * for RV32: MSB=31,
 * for RV64: MSB=63
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_AVE(long a, long b)
{
    long result;
    __ASM volatile("ave %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.4. AVE ===== */

/* ===== Inline Function Start for 3.5. BITREV ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_MISC
 * \brief BITREV (Bit Reverse)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * BITREV Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Reverse the bit positions of the source operand within a specified width starting from bit
 * 0. The reversed width is a variable from a GPR.
 *
 * **Description**:\n
 * This instruction reverses the bit positions of the content of Rs1. The reversed bit width
 * is calculated as Rs2[4:0]+1 (RV32) or Rs2[5:0]+1 (RV64). The upper bits beyond the reversed width
 * are filled with zeros. After the bit reverse operation, the result is written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * msb = Rs2[4:0]; (for RV32)
 * msb = Rs2[5:0]; (for RV64)
 * rev[0:msb] = Rs1[msb:0];
 * Rd = ZE(rev[msb:0]);
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_BITREV(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("bitrev %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.5. BITREV ===== */

/* ===== Inline Function Start for 3.6. BITREVI ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_MISC
 * \brief BITREVI (Bit Reverse Immediate)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * (RV32) BITREVI Rd, Rs1, imm[4:0]
 * (RV64) BITREVI Rd, Rs1, imm[5:0]
 * ~~~
 *
 * **Purpose**:\n
 * Reverse the bit positions of the source operand within a specified width starting from bit
 * 0. The reversed width is an immediate value.
 *
 * **Description**:\n
 * This instruction reverses the bit positions of the content of Rs1. The reversed bit width
 * is calculated as imm[4:0]+1 (RV32) or imm[5:0]+1 (RV64). The upper bits beyond the reversed width
 * are filled with zeros. After the bit reverse operation, the result is written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * msb = imm[4:0]; (RV32)
 * msb = imm[5:0]; (RV64)
 * rev[0:msb] = Rs1[msb:0];
 * Rd = ZE(rev[msb:0]);
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_BITREVI(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("bitrevi %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.6. BITREVI ===== */

/* ===== Inline Function Start for 3.7. BPICK ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_MISC
 * \brief BPICK (Bit-wise Pick)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * BPICK Rd, Rs1, Rs2, Rc
 * ~~~
 *
 * **Purpose**:\n
 * Select from two source operands based on a bit mask in the third operand.
 *
 * **Description**:\n
 * This instruction selects individual bits from Rs1 or Rs2, based on the bit mask value in
 * Rc. If a bit in Rc is 1, the corresponding bit is from Rs1; otherwise, the corresponding bit is from Rs2.
 * The selection results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd[x] = Rc[x]? Rs1[x] : Rs2[x];
 * for RV32, x=31...0
 * for RV64, x=63...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \param [in]  c
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_BPICK(unsigned long a, unsigned long b, unsigned long c)
{
    unsigned long result;
    __ASM volatile("bpick %0, %1, %2, %3" : "=r"(result) : "r"(a), "r"(b), "r"(c));
    return result;
}
/* ===== Inline Function End for 3.7. BPICK ===== */

/* ===== Inline Function Start for 3.8. CLROV ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_OV_FLAG_SC
 * \brief CLROV (Clear OV flag)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * CLROV # pseudo mnemonic
 * ~~~
 *
 * **Purpose**:\n
 * This pseudo instruction is an alias to `CSRRCI x0, ucode, 1` instruction.
 *
 *
 */
__STATIC_FORCEINLINE void __RV_CLROV(void)
{
    __ASM volatile("clrov ");
}
/* ===== Inline Function End for 3.8. CLROV ===== */

/* ===== Inline Function Start for 3.9. CLRS8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_MISC
 * \brief CLRS8 (SIMD 8-bit Count Leading Redundant Sign)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * CLRS8 Rd, Rs1
 * ~~~
 *
 * **Purpose**:\n
 * Count the number of redundant sign bits of the 8-bit elements of a general register.
 *
 * **Description**:\n
 * Starting from the bits next to the sign bits of the 8-bit elements of Rs1, this instruction
 * counts the number of redundant sign bits and writes the result to the corresponding 8-bit elements
 * of Rd.
 *
 * **Operations**:\n
 * ~~~
 * snum[x] = Rs1.B[x];
 * cnt[x] = 0;
 * for (i = 6 to 0) {
 *   if (snum[x](i) == snum[x](7)) {
 *     cnt[x] = cnt[x] + 1;
 *   } else {
 *     break;
 *   }
 * }
 * Rd.B[x] = cnt[x];
 * for RV32: x=3...0
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_CLRS8(unsigned long a)
{
    unsigned long result;
    __ASM volatile("clrs8 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.9. CLRS8 ===== */

/* ===== Inline Function Start for 3.10. CLRS16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_MISC
 * \brief CLRS16 (SIMD 16-bit Count Leading Redundant Sign)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * CLRS16 Rd, Rs1
 * ~~~
 *
 * **Purpose**:\n
 * Count the number of redundant sign bits of the 16-bit elements of a general register.
 *
 * **Description**:\n
 * Starting from the bits next to the sign bits of the 16-bit elements of Rs1, this
 * instruction counts the number of redundant sign bits and writes the result to the corresponding 16-
 * bit elements of Rd.
 *
 * **Operations**:\n
 * ~~~
 * snum[x] = Rs1.H[x];
 * cnt[x] = 0;
 * for (i = 14 to 0) {
 *   if (snum[x](i) == snum[x](15)) {
 *     cnt[x] = cnt[x] + 1;
 *   } else {
 *     break;
 *   }
 * }
 * Rd.H[x] = cnt[x];
 * for RV32: x=1...0
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_CLRS16(unsigned long a)
{
    unsigned long result;
    __ASM volatile("clrs16 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.10. CLRS16 ===== */

/* ===== Inline Function Start for 3.11. CLRS32 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_PART_SIMD_MISC
 * \brief CLRS32 (SIMD 32-bit Count Leading Redundant Sign)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * CLRS32 Rd, Rs1
 * ~~~
 *
 * **Purpose**:\n
 * Count the number of redundant sign bits of the 32-bit elements of a general register.
 *
 * **Description**:\n
 * Starting from the bits next to the sign bits of the 32-bit elements of Rs1, this
 * instruction counts the number of redundant sign bits and writes the result to the corresponding 32-
 * bit elements of Rd.
 *
 * **Operations**:\n
 * ~~~
 * snum[x] = Rs1.W[x];
 * cnt[x] = 0;
 * for (i = 30 to 0) {
 *   if (snum[x](i) == snum[x](31)) {
 *     cnt[x] = cnt[x] + 1;
 *   } else {
 *     break;
 *   }
 * }
 * Rd.W[x] = cnt[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_CLRS32(unsigned long a)
{
    unsigned long result;
    __ASM volatile("clrs32 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.11. CLRS32 ===== */

/* ===== Inline Function Start for 3.12. CLO8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_MISC
 * \brief CLO8 (SIMD 8-bit Count Leading One)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * CLO8 Rd, Rs1
 * ~~~
 *
 * **Purpose**:\n
 * Count the number of leading one bits of the 8-bit elements of a general register.
 *
 * **Description**:\n
 * Starting from the most significant bits of the 8-bit elements of Rs1, this instruction
 * counts the number of leading one bits and writes the results to the corresponding 8-bit elements of
 * Rd.
 *
 * **Operations**:\n
 * ~~~
 * snum[x] = Rs1.B[x];
 * cnt[x] = 0;
 *   for (i = 7 to 0) {
 *   if (snum[x](i) == 1) {
 *     cnt[x] = cnt[x] + 1;
 *   } else {
 *     break;
 *   }
 * }
 * Rd.B[x] = cnt[x];
 * for RV32: x=3...0
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_CLO8(unsigned long a)
{
    unsigned long result;
    __ASM volatile("clo8 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.12. CLO8 ===== */

/* ===== Inline Function Start for 3.13. CLO16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_MISC
 * \brief CLO16 (SIMD 16-bit Count Leading One)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * CLO16 Rd, Rs1
 * ~~~
 *
 * **Purpose**:\n
 * Count the number of leading one bits of the 16-bit elements of a general register.
 *
 * **Description**:\n
 * Starting from the most significant bits of the 16-bit elements of Rs1, this instruction
 * counts the number of leading one bits and writes the results to the corresponding 16-bit elements
 * of Rd.
 *
 * **Operations**:\n
 * ~~~
 * snum[x] = Rs1.H[x];
 * cnt[x] = 0;
 * for (i = 15 to 0) {
 *   if (snum[x](i) == 1) {
 *     cnt[x] = cnt[x] + 1;
 *   } else {
 *     break;
 *   }
 * }
 * Rd.H[x] = cnt[x];
 * for RV32: x=1...0
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_CLO16(unsigned long a)
{
    unsigned long result;
    __ASM volatile("clo16 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.13. CLO16 ===== */

/* ===== Inline Function Start for 3.14. CLO32 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_PART_SIMD_MISC
 * \brief CLO32 (SIMD 32-bit Count Leading One)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * CLO32 Rd, Rs1
 * ~~~
 *
 * **Purpose**:\n
 * Count the number of leading one bits of the 32-bit elements of a general register.
 *
 * **Description**:\n
 * Starting from the most significant bits of the 32-bit elements of Rs1, this instruction
 * counts the number of leading one bits and writes the results to the corresponding 32-bit elements
 * of Rd.
 *
 * **Operations**:\n
 * ~~~
 * snum[x] = Rs1.W[x];
 * cnt[x] = 0;
 * for (i = 31 to 0) {
 *   if (snum[x](i) == 1) {
 *     cnt[x] = cnt[x] + 1;
 *   } else {
 *     break;
 *   }
 * }
 * Rd.W[x] = cnt[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_CLO32(unsigned long a)
{
    unsigned long result;
    __ASM volatile("clo32 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.14. CLO32 ===== */

/* ===== Inline Function Start for 3.15. CLZ8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_MISC
 * \brief CLZ8 (SIMD 8-bit Count Leading Zero)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * CLZ8 Rd, Rs1
 * ~~~
 *
 * **Purpose**:\n
 * Count the number of leading zero bits of the 8-bit elements of a general register.
 *
 * **Description**:\n
 * Starting from the most significant bits of the 8-bit elements of Rs1, this instruction
 * counts the number of leading zero bits and writes the results to the corresponding 8-bit elements of
 * Rd.
 *
 * **Operations**:\n
 * ~~~
 * snum[x] = Rs1.B[x];
 * cnt[x] = 0;
 * for (i = 7 to 0) {
 *   if (snum[x](i) == 0) {
 *     cnt[x] = cnt[x] + 1;
 *   } else {
 *     break;
 *   }
 * }
 * Rd.B[x] = cnt[x];
 * for RV32: x=3...0
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_CLZ8(unsigned long a)
{
    unsigned long result;
    __ASM volatile("clz8 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.15. CLZ8 ===== */

/* ===== Inline Function Start for 3.16. CLZ16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_MISC
 * \brief CLZ16 (SIMD 16-bit Count Leading Zero)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * CLZ16 Rd, Rs1
 * ~~~
 *
 * **Purpose**:\n
 * Count the number of leading zero bits of the 16-bit elements of a general register.
 *
 * **Description**:\n
 * Starting from the most significant bits of the 16-bit elements of Rs1, this instruction
 * counts the number of leading zero bits and writes the results to the corresponding 16-bit elements
 * of Rd.
 *
 * **Operations**:\n
 * ~~~
 * snum[x] = Rs1.H[x];
 * cnt[x] = 0;
 * for (i = 15 to 0) {
 *   if (snum[x](i) == 0) {
 *     cnt[x] = cnt[x] + 1;
 *   } else {
 *     break;
 *   }
 * }
 * Rd.H[x] = cnt[x];
 * for RV32: x=1...0
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_CLZ16(unsigned long a)
{
    unsigned long result;
    __ASM volatile("clz16 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.16. CLZ16 ===== */

/* ===== Inline Function Start for 3.17. CLZ32 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_PART_SIMD_MISC
 * \brief CLZ32 (SIMD 32-bit Count Leading Zero)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * CLZ32 Rd, Rs1
 * ~~~
 *
 * **Purpose**:\n
 * Count the number of leading zero bits of the 32-bit elements of a general register.
 *
 * **Description**:\n
 * Starting from the most significant bits of the 32-bit elements of Rs1, this instruction
 * counts the number of leading zero bits and writes the results to the corresponding 32-bit elements
 * of Rd.
 *
 * **Operations**:\n
 * ~~~
 * snum[x] = Rs1.W[x];
 * cnt[x] = 0;
 * for (i = 31 to 0) {
 *   if (snum[x](i) == 0) {
 *     cnt[x] = cnt[x] + 1;
 *   } else {
 *     break;
 *   }
 * }
 * Rd.W[x] = cnt[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_CLZ32(unsigned long a)
{
    unsigned long result;
    __ASM volatile("clz32 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.17. CLZ32 ===== */

/* ===== Inline Function Start for 3.18. CMPEQ8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_CMP
 * \brief CMPEQ8 (SIMD 8-bit Integer Compare Equal)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * CMPEQ8 Rs, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit integer elements equal comparisons simultaneously.
 *
 * **Description**:\n
 * This instruction compares the 8-bit integer elements in Rs1 with the 8-bit integer
 * elements in Rs2 to see if they are equal. If they are equal, the result is 0xFF; otherwise, the result is
 * 0x0. The 8-bit element comparison results are written to Rd.
 *
 * **Note**:\n
 * This instruction can be used for either signed or unsigned numbers.
 *
 * **Operations**:\n
 * ~~~
 * Rd.B[x] = (Rs1.B[x] == Rs2.B[x])? 0xff : 0x0;
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_CMPEQ8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("cmpeq8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.18. CMPEQ8 ===== */

/* ===== Inline Function Start for 3.19. CMPEQ16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_CMP
 * \brief CMPEQ16 (SIMD 16-bit Integer Compare Equal)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * CMPEQ16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit integer elements equal comparisons simultaneously.
 *
 * **Description**:\n
 * This instruction compares the 16-bit integer elements in Rs1 with the 16-bit integer
 * elements in Rs2 to see if they are equal. If they are equal, the result is 0xFFFF; otherwise, the result
 * is 0x0. The 16-bit element comparison results are written to Rt.
 *
 * **Note**:\n
 * This instruction can be used for either signed or unsigned numbers.
 *
 * **Operations**:\n
 * ~~~
 * Rd.H[x] = (Rs1.H[x] == Rs2.H[x])? 0xffff : 0x0;
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_CMPEQ16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("cmpeq16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.19. CMPEQ16 ===== */

/* ===== Inline Function Start for 3.20. CRAS16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief CRAS16 (SIMD 16-bit Cross Addition & Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * CRAS16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit integer element addition and 16-bit integer element subtraction in a 32-bit
 * chunk simultaneously. Operands are from crossed positions in 32-bit chunks.
 *
 * **Description**:\n
 * This instruction adds the 16-bit integer element in [31:16] of 32-bit chunks in Rs1 with
 * the 16-bit integer element in [15:0] of 32-bit chunks in Rs2, and writes the result to [31:16] of 32-bit
 * chunks in Rd; at the same time, it subtracts the 16-bit integer element in [31:16] of 32-bit chunks in
 * Rs2 from the 16-bit integer element in [15:0] of 32-bit chunks, and writes the result to [15:0] of 32-
 * bit chunks in Rd.
 *
 * **Note**:\n
 * This instruction can be used for either signed or unsigned operations.
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:16] = Rs1.W[x][31:16] + Rs2.W[x][15:0];
 * Rd.W[x][15:0] = Rs1.W[x][15:0] - Rs2.W[x][31:16];
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_CRAS16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("cras16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.20. CRAS16 ===== */

/* ===== Inline Function Start for 3.21. CRSA16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief CRSA16 (SIMD 16-bit Cross Subtraction & Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * CRSA16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit integer element subtraction and 16-bit integer element addition in a 32-bit
 * chunk simultaneously. Operands are from crossed positions in 32-bit chunks.
 *
 * **Description**:\n
 * This instruction subtracts the 16-bit integer element in [15:0] of 32-bit chunks in Rs2
 * from the 16-bit integer element in [31:16] of 32-bit chunks in Rs1, and writes the result to [31:16] of
 * 32-bit chunks in Rd; at the same time, it adds the 16-bit integer element in [31:16] of 32-bit chunks
 * in Rs2 with the 16-bit integer element in [15:0] of 32-bit chunks in Rs1, and writes the result to
 * [15:0] of 32-bit chunks in Rd.
 *
 * **Note**:\n
 * This instruction can be used for either signed or unsigned operations.
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:16] = Rs1.W[x][31:16] - Rs2.W[x][15:0];
 * Rd.W[x][15:0] = Rs1.W[x][15:0] + Rs2.W[x][31:16];
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_CRSA16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("crsa16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.21. CRSA16 ===== */

/* ===== Inline Function Start for 3.22. INSB ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_MISC
 * \brief INSB (Insert Byte)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * (RV32) INSB Rd, Rs1, imm[1:0]
 * (RV64) INSB Rd, Rs1, imm[2:0]
 * ~~~
 *
 * **Purpose**:\n
 * Insert byte 0 of a 32-bit or 64-bit register into one of the byte elements of another register.
 *
 * **Description**:\n
 * This instruction inserts byte 0 of Rs1 into byte `imm[1:0]` (RV32) or `imm[2:0]` (RV64)
 * of Rd.
 *
 * **Operations**:\n
 * ~~~
 * bpos = imm[1:0]; (RV32)
 * bpos = imm[2:0]; (RV64)
 * Rd.B[bpos] = Rs1.B[0]
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_INSB(unsigned long t, unsigned long a, unsigned long b)
{
    __ASM volatile("insb %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.22. INSB ===== */

/* ===== Inline Function Start for 3.23. KABS8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_MISC
 * \brief KABS8 (SIMD 8-bit Saturating Absolute)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KABS8 Rd, Rs1
 * ~~~
 *
 * **Purpose**:\n
 * Get the absolute value of 8-bit signed integer elements simultaneously.
 *
 * **Description**:\n
 * This instruction calculates the absolute value of 8-bit signed integer elements stored
 * in Rs1 and writes the element results to Rd. If the input number is 0x80, this instruction generates
 * 0x7f as the output and sets the OV bit to 1.
 *
 * **Operations**:\n
 * ~~~
 * src = Rs1.B[x];
 * if (src == 0x80) {
 *   src = 0x7f;
 *   OV = 1;
 * } else if (src[7] == 1)
 *   src = -src;
 * }
 * Rd.B[x] = src;
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KABS8(unsigned long a)
{
    unsigned long result;
    __ASM volatile("kabs8 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.23. KABS8 ===== */

/* ===== Inline Function Start for 3.24. KABS16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_MISC
 * \brief KABS16 (SIMD 16-bit Saturating Absolute)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KABS16 Rd, Rs1
 * ~~~
 *
 * **Purpose**:\n
 * Get the absolute value of 16-bit signed integer elements simultaneously.
 *
 * **Description**:\n
 * This instruction calculates the absolute value of 16-bit signed integer elements stored
 * in Rs1 and writes the element results to Rd. If the input number is 0x8000, this instruction
 * generates 0x7fff as the output and sets the OV bit to 1.
 *
 * **Operations**:\n
 * ~~~
 * src = Rs1.H[x];
 * if (src == 0x8000) {
 *   src = 0x7fff;
 *   OV = 1;
 * } else if (src[15] == 1)
 *   src = -src;
 * }
 * Rd.H[x] = src;
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KABS16(unsigned long a)
{
    unsigned long result;
    __ASM volatile("kabs16 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.24. KABS16 ===== */

/* ===== Inline Function Start for 3.25. KABSW ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q31_SAT_ALU
 * \brief KABSW (Scalar 32-bit Absolute Value with Saturation)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * KABSW Rd, Rs1
 * ~~~
 *
 * **Purpose**:\n
 * Get the absolute value of a signed 32-bit integer in a general register.
 *
 * **Description**:\n
 * This instruction calculates the absolute value of a signed 32-bit integer stored in Rs1.
 * The result is sign-extended (for RV64) and written to Rd. This instruction with the minimum
 * negative integer input of 0x80000000 will produce a saturated output of maximum positive integer
 * of 0x7fffffff and the OV flag will be set to 1.
 *
 * **Operations**:\n
 * ~~~
 * if (Rs1.W[0] >= 0) {
 *   res = Rs1.W[0];
 * } else {
 *   If (Rs1.W[0] == 0x80000000) {
 *     res = 0x7fffffff;
 *     OV = 1;
 *   } else {
 *     res = -Rs1.W[0];
 *   }
 * }
 * Rd = SE32(res);
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KABSW(signed long a)
{
    unsigned long result;
    __ASM volatile("kabsw %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.25. KABSW ===== */

/* ===== Inline Function Start for 3.26. KADD8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_ADDSUB
 * \brief KADD8 (SIMD 8-bit Signed Saturating Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KADD8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit signed integer element saturating additions simultaneously.
 *
 * **Description**:\n
 * This instruction adds the 8-bit signed integer elements in Rs1 with the 8-bit signed
 * integer elements in Rs2. If any of the results are beyond the Q7 number range (-2^7 <= Q7 <= 2^7-1), they
 * are saturated to the range and the OV bit is set to 1. The saturated results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * res[x] = Rs1.B[x] + Rs2.B[x];
 * if (res[x] > 127) {
 *   res[x] = 127;
 *   OV = 1;
 * } else if (res[x] < -128) {
 *   res[x] = -128;
 *   OV = 1;
 * }
 * Rd.B[x] = res[x];
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KADD8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("kadd8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.26. KADD8 ===== */

/* ===== Inline Function Start for 3.27. KADD16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief KADD16 (SIMD 16-bit Signed Saturating Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KADD16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit signed integer element saturating additions simultaneously.
 *
 * **Description**:\n
 * This instruction adds the 16-bit signed integer elements in Rs1 with the 16-bit signed
 * integer elements in Rs2. If any of the results are beyond the Q15 number range (-2^15 <= Q15 <= 2^15-1),
 * they are saturated to the range and the OV bit is set to 1. The saturated results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * res[x] = Rs1.H[x] + Rs2.H[x];
 * if (res[x] > 32767) {
 *   res[x] = 32767;
 *   OV = 1;
 * } else if (res[x] < -32768) {
 *   res[x] = -32768;
 *   OV = 1;
 * }
 * Rd.H[x] = res[x];
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KADD16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("kadd16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.27. KADD16 ===== */

/* ===== Inline Function Start for 3.28. KADD64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_64B_ADDSUB
 * \brief KADD64 (64-bit Signed Saturating Addition)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * KADD64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Add two 64-bit signed integers. The result is saturated to the Q63 range.
 *
 * **RV32 Description**:\n
 * This instruction adds the 64-bit signed integer of an even/odd pair of registers
 * specified by Rs1(4,1) with the 64-bit signed integer of an even/odd pair of registers specified by
 * Rs2(4,1). If the 64-bit result is beyond the Q63 number range (-2^63 <= Q63 <= 2^63-1), it is saturated to the
 * range and the OV bit is set to 1. The saturated result is written to an even/odd pair of registers
 * specified by Rd(4,1).
 * Rx(4,1), i.e., value d, determines the even/odd pair group of two registers. Specifically, the register
 * pair includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 *
 * **RV64 Description**:\n
 * This instruction adds the 64-bit signed integer in Rs1 with the 64-bit signed
 * integer in Rs2. If the result is beyond the Q63 number range (-2^63 <= Q63 <= 2^63-1), it is saturated to the
 * range and the OV bit is set to 1. The saturated result is written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 *  t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 *  a_L = CONCAT(Rs1(4,1),1'b0); a_H = CONCAT(Rs1(4,1),1'b1);
 *  b_L = CONCAT(Rs2(4,1),1'b0); b_H = CONCAT(Rs2(4,1),1'b1);
 *  result = R[a_H].R[a_L] + R[b_H].R[b_L];
 *  if (result > (2^63)-1) {
 *    result = (2^63)-1; OV = 1;
 *  } else if (result < -2^63) {
 *    result = -2^63; OV = 1;
 *  }
 *  R[t_H].R[t_L] = result;
 * RV64:
 *  result = Rs1 + Rs2;
 *  if (result > (2^63)-1) {
 *    result = (2^63)-1; OV = 1;
 *  } else if (result < -2^63) {
 *    result = -2^63; OV = 1;
 *  }
 *  Rd = result;
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_KADD64(long long a, long long b)
{
    long long result;
    __ASM volatile("kadd64 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.28. KADD64 ===== */

/* ===== Inline Function Start for 3.29. KADDH ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q15_SAT_ALU
 * \brief KADDH (Signed Addition with Q15 Saturation)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * KADDH Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Add the signed lower 32-bit content of two registers with Q15 saturation.
 *
 * **Description**:\n
 * The signed lower 32-bit content of Rs1 is added with the signed lower 32-bit content of
 * Rs2. And the result is saturated to the 16-bit signed integer range of [-2^15, 2^15-1] and then sign-
 * extended and written to Rd. If saturation happens, this instruction sets the OV flag.
 *
 * **Operations**:\n
 * ~~~
 * tmp = Rs1.W[0] + Rs2.W[0];
 * if (tmp > 32767) {
 *   res = 32767;
 *   OV = 1;
 * } else if (tmp < -32768) {
 *   res = -32768;
 *   OV = 1
 * } else {
 *   res = tmp;
 * }
 * Rd = SE(tmp[15:0]);
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KADDH(int a, int b)
{
    long result;
    __ASM volatile("kaddh %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.29. KADDH ===== */

/* ===== Inline Function Start for 3.30. KADDW ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q31_SAT_ALU
 * \brief KADDW (Signed Addition with Q31 Saturation)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * KADDW Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Add the lower 32-bit signed content of two registers with Q31 saturation.
 *
 * **Description**:\n
 * The lower 32-bit signed content of Rs1 is added with the lower 32-bit signed content of
 * Rs2. And the result is saturated to the 32-bit signed integer range of [-2^31, 2^31-1] and then sign-
 * extended and written to Rd. If saturation happens, this instruction sets the OV flag.
 *
 * **Operations**:\n
 * ~~~
 * tmp = Rs1.W[0] + Rs2.W[0];
 * if (tmp > (2^31)-1) {
 *   res = (2^31)-1;
 *   OV = 1;
 * } else if (tmp < -2^31) {
 *   res = -2^31;
 *   OV = 1
 * } else {
 *   res = tmp;
 * }
 * Rd = res[31:0]; // RV32
 * Rd = SE(res[31:0]) // RV64
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KADDW(int a, int b)
{
    long result;
    __ASM volatile("kaddw %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.30. KADDW ===== */

/* ===== Inline Function Start for 3.31. KCRAS16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief KCRAS16 (SIMD 16-bit Signed Saturating Cross Addition & Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KCRAS16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit signed integer element saturating addition and 16-bit signed integer element
 * saturating subtraction in a 32-bit chunk simultaneously. Operands are from crossed positions in 32-
 * bit chunks.
 *
 * **Description**:\n
 * This instruction adds the 16-bit signed integer element in [31:16] of 32-bit chunks in
 * Rs1 with the 16-bit signed integer element in [15:0] of 32-bit chunks in Rs2; at the same time, it
 * subtracts the 16-bit signed integer element in [31:16] of 32-bit chunks in Rs2 from the 16-bit signed
 * integer element in [15:0] of 32-bit chunks in Rs1. If any of the results are beyond the Q15 number
 * range (-2^15 <= Q15 <= 2^15-1), they are saturated to the range and the OV bit is set to 1. The saturated
 * results are written to [31:16] of 32-bit chunks in Rd for addition and [15:0] of 32-bit chunks in Rd for
 * subtraction.
 *
 * **Operations**:\n
 * ~~~
 * res1 = Rs1.W[x][31:16] + Rs2.W[x][15:0];
 * res2 = Rs1.W[x][15:0] - Rs2.W[x][31:16];
 * for (res in [res1, res2]) {
 *   if (res > (2^15)-1) {
 *     res = (2^15)-1;
 *     OV = 1;
 *   } else if (res < -2^15) {
 *     res = -2^15;
 *     OV = 1;
 *   }
 * }
 * Rd.W[x][31:16] = res1;
 * Rd.W[x][15:0] = res2;
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KCRAS16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("kcras16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.31. KCRAS16 ===== */

/* ===== Inline Function Start for 3.32. KCRSA16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief KCRSA16 (SIMD 16-bit Signed Saturating Cross Subtraction & Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KCRSA16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit signed integer element saturating subtraction and 16-bit signed integer element
 * saturating addition in a 32-bit chunk simultaneously. Operands are from crossed positions in 32-bit
 * chunks.
 *
 * **Description**:\n
 * This instruction subtracts the 16-bit signed integer element in [15:0] of 32-bit chunks
 * in Rs2 from the 16-bit signed integer element in [31:16] of 32-bit chunks in Rs1; at the same time, it
 * adds the 16-bit signed integer element in [31:16] of 32-bit chunks in Rs2 with the 16-bit signed
 * integer element in [15:0] of 32-bit chunks in Rs1. If any of the results are beyond the Q15 number
 * range (-2^15 <= Q15 <= 2^15-1), they are saturated to the range and the OV bit is set to 1. The saturated
 * results are written to [31:16] of 32-bit chunks in Rd for subtraction and [15:0] of 32-bit chunks in Rd
 * for addition.
 *
 * **Operations**:\n
 * ~~~
 * res1 = Rs1.W[x][31:16] - Rs2.W[x][15:0];
 * res2 = Rs1.W[x][15:0] + Rs2.W[x][31:16];
 * for (res in [res1, res2]) {
 *   if (res > (2^15)-1) {
 *     res = (2^15)-1;
 *     OV = 1;
 *   } else if (res < -2^15) {
 *     res = -2^15;
 *     OV = 1;
 *   }
 * }
 * Rd.W[x][31:16] = res1;
 * Rd.W[x][15:0] = res2;
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KCRSA16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("kcrsa16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.32. KCRSA16 ===== */

/* ===== Inline Function Start for 3.33.1. KDMBB ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q31_SAT_ALU
 * \brief KDMBB (Signed Saturating Double Multiply B16 x B16)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * KDMxy Rd, Rs1, Rs2 (xy = BB, BT, TT)
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed Q15 integer contents of two 16-bit data in the corresponding portion
 * of the lower 32-bit chunk in registers and then double and saturate the Q31 result. The result is
 * written into the destination register for RV32 or sign-extended to 64-bits and written into the
 * destination register for RV64. If saturation happens, an overflow flag OV will be set.
 *
 * **Description**:\n
 * Multiply the top or bottom 16-bit Q15 content of the lower 32-bit portion in Rs1 with
 * the top or bottom 16-bit Q15 content of the lower 32-bit portion in Rs2. The Q30 result is then
 * doubled and saturated into a Q31 value. The Q31 value is then written into Rd (sign-extended in
 * RV64). When both the two Q15 inputs are 0x8000, saturation will happen. The result will be
 * saturated to 0x7FFFFFFF and the overflow flag OV will be set.
 *
 * **Operations**:\n
 * ~~~
 * aop = Rs1.H[0]; bop = Rs2.H[0]; // KDMBB
 * aop = Rs1.H[0]; bop = Rs2.H[1]; // KDMBT
 * aop = Rs1.H[1]; bop = Rs2.H[1]; // KDMTT
 * If (0x8000 != aop | 0x8000 != bop) {
 *   Mresult = aop * bop;
 *   resQ31 = Mresult << 1;
 *   Rd = resQ31; // RV32
 *   Rd = SE(resQ31); // RV64
 * } else {
 *   resQ31 = 0x7FFFFFFF;
 *   Rd = resQ31; // RV32
 *   Rd = SE(resQ31); // RV64
 *   OV = 1;
 * }
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KDMBB(unsigned int a, unsigned int b)
{
    long result;
    __ASM volatile("kdmbb %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.33.1. KDMBB ===== */

/* ===== Inline Function Start for 3.33.2. KDMBT ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q31_SAT_ALU
 * \brief KDMBT (Signed Saturating Double Multiply B16 x T16)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * KDMxy Rd, Rs1, Rs2 (xy = BB, BT, TT)
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed Q15 integer contents of two 16-bit data in the corresponding portion
 * of the lower 32-bit chunk in registers and then double and saturate the Q31 result. The result is
 * written into the destination register for RV32 or sign-extended to 64-bits and written into the
 * destination register for RV64. If saturation happens, an overflow flag OV will be set.
 *
 * **Description**:\n
 * Multiply the top or bottom 16-bit Q15 content of the lower 32-bit portion in Rs1 with
 * the top or bottom 16-bit Q15 content of the lower 32-bit portion in Rs2. The Q30 result is then
 * doubled and saturated into a Q31 value. The Q31 value is then written into Rd (sign-extended in
 * RV64). When both the two Q15 inputs are 0x8000, saturation will happen. The result will be
 * saturated to 0x7FFFFFFF and the overflow flag OV will be set.
 *
 * **Operations**:\n
 * ~~~
 * aop = Rs1.H[0]; bop = Rs2.H[0]; // KDMBB
 * aop = Rs1.H[0]; bop = Rs2.H[1]; // KDMBT
 * aop = Rs1.H[1]; bop = Rs2.H[1]; // KDMTT
 * If (0x8000 != aop | 0x8000 != bop) {
 *   Mresult = aop * bop;
 *   resQ31 = Mresult << 1;
 *   Rd = resQ31; // RV32
 *   Rd = SE(resQ31); // RV64
 * } else {
 *   resQ31 = 0x7FFFFFFF;
 *   Rd = resQ31; // RV32
 *   Rd = SE(resQ31); // RV64
 *   OV = 1;
 * }
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KDMBT(unsigned int a, unsigned int b)
{
    long result;
    __ASM volatile("kdmbt %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.33.2. KDMBT ===== */

/* ===== Inline Function Start for 3.33.3. KDMTT ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q31_SAT_ALU
 * \brief KDMTT (Signed Saturating Double Multiply T16 x T16)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * KDMxy Rd, Rs1, Rs2 (xy = BB, BT, TT)
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed Q15 integer contents of two 16-bit data in the corresponding portion
 * of the lower 32-bit chunk in registers and then double and saturate the Q31 result. The result is
 * written into the destination register for RV32 or sign-extended to 64-bits and written into the
 * destination register for RV64. If saturation happens, an overflow flag OV will be set.
 *
 * **Description**:\n
 * Multiply the top or bottom 16-bit Q15 content of the lower 32-bit portion in Rs1 with
 * the top or bottom 16-bit Q15 content of the lower 32-bit portion in Rs2. The Q30 result is then
 * doubled and saturated into a Q31 value. The Q31 value is then written into Rd (sign-extended in
 * RV64). When both the two Q15 inputs are 0x8000, saturation will happen. The result will be
 * saturated to 0x7FFFFFFF and the overflow flag OV will be set.
 *
 * **Operations**:\n
 * ~~~
 * aop = Rs1.H[0]; bop = Rs2.H[0]; // KDMBB
 * aop = Rs1.H[0]; bop = Rs2.H[1]; // KDMBT
 * aop = Rs1.H[1]; bop = Rs2.H[1]; // KDMTT
 * If (0x8000 != aop | 0x8000 != bop) {
 *   Mresult = aop * bop;
 *   resQ31 = Mresult << 1;
 *   Rd = resQ31; // RV32
 *   Rd = SE(resQ31); // RV64
 * } else {
 *   resQ31 = 0x7FFFFFFF;
 *   Rd = resQ31; // RV32
 *   Rd = SE(resQ31); // RV64
 *   OV = 1;
 * }
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KDMTT(unsigned int a, unsigned int b)
{
    long result;
    __ASM volatile("kdmtt %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.33.3. KDMTT ===== */

/* ===== Inline Function Start for 3.34.1. KDMABB ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q31_SAT_ALU
 * \brief KDMABB (Signed Saturating Double Multiply Addition B16 x B16)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * KDMAxy Rd, Rs1, Rs2 (xy = BB, BT, TT)
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed Q15 integer contents of two 16-bit data in the corresponding portion
 * of the lower 32-bit chunk in registers and then double and saturate the Q31 result, add the result
 * with the sign-extended lower 32-bit chunk destination register and write the saturated addition
 * result into the destination register. If saturation happens, an overflow flag OV will be set.
 *
 * **Description**:\n
 * Multiply the top or bottom 16-bit Q15 content of the lower 32-bit portion in Rs1 with
 * the top or bottom 16-bit Q15 content of the lower 32-bit portion in Rs2. The Q30 result is then
 * doubled and saturated into a Q31 value. The Q31 value is then added with the content of Rd. If the
 * addition result is beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the range and
 * the OV flag is set to 1. The result after saturation is written to Rd.
 * When both the two Q15 inputs are 0x8000, saturation will happen and the overflow flag OV will be
 * set.
 *
 * **Operations**:\n
 * ~~~
 * aop = Rs1.H[0]; bop = Rs2.H[0]; // KDMABB
 * aop = Rs1.H[0]; bop = Rs2.H[1]; // KDMABT
 * aop = Rs1.H[1]; bop = Rs2.H[1]; // KDMATT
 * If (0x8000 != aop | 0x8000 != bop) {
 *   Mresult = aop * bop;
 *   resQ31 = Mresult << 1;
 * } else {
 *   resQ31 = 0x7FFFFFFF;
 *   OV = 1;
 * }
 * resadd = Rd + resQ31; // RV32
 * resadd = Rd.W[0] + resQ31; // RV64
 * if (resadd > (2^31)-1) {
 *   resadd = (2^31)-1;
 *   OV = 1;
 * } else if (resadd < -2^31) {
 *   resadd = -2^31;
 *   OV = 1;
 * }
 * Rd = resadd; // RV32
 * Rd = SE(resadd); // RV64
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KDMABB(long t, unsigned int a, unsigned int b)
{
    __ASM volatile("kdmabb %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.34.1. KDMABB ===== */

/* ===== Inline Function Start for 3.34.2. KDMABT ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q31_SAT_ALU
 * \brief KDMABT (Signed Saturating Double Multiply Addition B16 x T16)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * KDMAxy Rd, Rs1, Rs2 (xy = BB, BT, TT)
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed Q15 integer contents of two 16-bit data in the corresponding portion
 * of the lower 32-bit chunk in registers and then double and saturate the Q31 result, add the result
 * with the sign-extended lower 32-bit chunk destination register and write the saturated addition
 * result into the destination register. If saturation happens, an overflow flag OV will be set.
 *
 * **Description**:\n
 * Multiply the top or bottom 16-bit Q15 content of the lower 32-bit portion in Rs1 with
 * the top or bottom 16-bit Q15 content of the lower 32-bit portion in Rs2. The Q30 result is then
 * doubled and saturated into a Q31 value. The Q31 value is then added with the content of Rd. If the
 * addition result is beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the range and
 * the OV flag is set to 1. The result after saturation is written to Rd.
 * When both the two Q15 inputs are 0x8000, saturation will happen and the overflow flag OV will be
 * set.
 *
 * **Operations**:\n
 * ~~~
 * aop = Rs1.H[0]; bop = Rs2.H[0]; // KDMABB
 * aop = Rs1.H[0]; bop = Rs2.H[1]; // KDMABT
 * aop = Rs1.H[1]; bop = Rs2.H[1]; // KDMATT
 * If (0x8000 != aop | 0x8000 != bop) {
 *   Mresult = aop * bop;
 *   resQ31 = Mresult << 1;
 * } else {
 *   resQ31 = 0x7FFFFFFF;
 *   OV = 1;
 * }
 * resadd = Rd + resQ31; // RV32
 * resadd = Rd.W[0] + resQ31; // RV64
 * if (resadd > (2^31)-1) {
 *   resadd = (2^31)-1;
 *   OV = 1;
 * } else if (resadd < -2^31) {
 *   resadd = -2^31;
 *   OV = 1;
 * }
 * Rd = resadd; // RV32
 * Rd = SE(resadd); // RV64
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KDMABT(long t, unsigned int a, unsigned int b)
{
    __ASM volatile("kdmabt %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.34.2. KDMABT ===== */

/* ===== Inline Function Start for 3.34.3. KDMATT ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q31_SAT_ALU
 * \brief KDMATT (Signed Saturating Double Multiply Addition T16 x T16)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * KDMAxy Rd, Rs1, Rs2 (xy = BB, BT, TT)
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed Q15 integer contents of two 16-bit data in the corresponding portion
 * of the lower 32-bit chunk in registers and then double and saturate the Q31 result, add the result
 * with the sign-extended lower 32-bit chunk destination register and write the saturated addition
 * result into the destination register. If saturation happens, an overflow flag OV will be set.
 *
 * **Description**:\n
 * Multiply the top or bottom 16-bit Q15 content of the lower 32-bit portion in Rs1 with
 * the top or bottom 16-bit Q15 content of the lower 32-bit portion in Rs2. The Q30 result is then
 * doubled and saturated into a Q31 value. The Q31 value is then added with the content of Rd. If the
 * addition result is beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the range and
 * the OV flag is set to 1. The result after saturation is written to Rd.
 * When both the two Q15 inputs are 0x8000, saturation will happen and the overflow flag OV will be
 * set.
 *
 * **Operations**:\n
 * ~~~
 * aop = Rs1.H[0]; bop = Rs2.H[0]; // KDMABB
 * aop = Rs1.H[0]; bop = Rs2.H[1]; // KDMABT
 * aop = Rs1.H[1]; bop = Rs2.H[1]; // KDMATT
 * If (0x8000 != aop | 0x8000 != bop) {
 *   Mresult = aop * bop;
 *   resQ31 = Mresult << 1;
 * } else {
 *   resQ31 = 0x7FFFFFFF;
 *   OV = 1;
 * }
 * resadd = Rd + resQ31; // RV32
 * resadd = Rd.W[0] + resQ31; // RV64
 * if (resadd > (2^31)-1) {
 *   resadd = (2^31)-1;
 *   OV = 1;
 * } else if (resadd < -2^31) {
 *   resadd = -2^31;
 *   OV = 1;
 * }
 * Rd = resadd; // RV32
 * Rd = SE(resadd); // RV64
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KDMATT(long t, unsigned int a, unsigned int b)
{
    __ASM volatile("kdmatt %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.34.3. KDMATT ===== */

/* ===== Inline Function Start for 3.35.1. KHM8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_MULTIPLY
 * \brief KHM8 (SIMD Signed Saturating Q7 Multiply)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KHM8 Rd, Rs1, Rs2
 * KHMX8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do Q7xQ7 element multiplications simultaneously. The Q14 results are then reduced to Q7
 * numbers again.
 *
 * **Description**:\n
 * For the `KHM8` instruction, multiply the top 8-bit Q7 content of 16-bit chunks in Rs1
 * with the top 8-bit Q7 content of 16-bit chunks in Rs2. At the same time, multiply the bottom 8-bit Q7
 * content of 16-bit chunks in Rs1 with the bottom 8-bit Q7 content of 16-bit chunks in Rs2.
 * For the `KHMX16` instruction, multiply the top 8-bit Q7 content of 16-bit chunks in Rs1 with the
 * bottom 8-bit Q7 content of 16-bit chunks in Rs2. At the same time, multiply the bottom 8-bit Q7
 * content of 16-bit chunks in Rs1 with the top 8-bit Q7 content of 16-bit chunks in Rs2.
 * The Q14 results are then right-shifted 7-bits and saturated into Q7 values. The Q7 results are then
 * written into Rd. When both the two Q7 inputs of a multiplication are 0x80, saturation will happen.
 * The result will be saturated to 0x7F and the overflow flag OV will be set.
 *
 * **Operations**:\n
 * ~~~
 * if (is `KHM8`) {
 *   op1t = Rs1.B[x+1]; op2t = Rs2.B[x+1]; // top
 *   op1b = Rs1.B[x]; op2b = Rs2.B[x]; // bottom
 * } else if (is `KHMX8`) {
 *   op1t = Rs1.H[x+1]; op2t = Rs2.H[x]; // Rs1 top
 *   op1b = Rs1.H[x]; op2b = Rs2.H[x+1]; // Rs1 bottom
 * }
 * for ((aop,bop,res) in [(op1t,op2t,rest), (op1b,op2b,resb)]) {
 *   if (0x80 != aop | 0x80 != bop) {
 *     res = (aop s* bop) >> 7;
 *   } else {
 *     res= 0x7F;
 *     OV = 1;
 *   }
 * }
 * Rd.H[x/2] = concat(rest, resb);
 * for RV32, x=0,2
 * for RV64, x=0,2,4,6
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KHM8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("khm8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.35.1. KHM8 ===== */

/* ===== Inline Function Start for 3.35.2. KHMX8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_MULTIPLY
 * \brief KHMX8 (SIMD Signed Saturating Crossed Q7 Multiply)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KHM8 Rd, Rs1, Rs2
 * KHMX8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do Q7xQ7 element multiplications simultaneously. The Q14 results are then reduced to Q7
 * numbers again.
 *
 * **Description**:\n
 * For the `KHM8` instruction, multiply the top 8-bit Q7 content of 16-bit chunks in Rs1
 * with the top 8-bit Q7 content of 16-bit chunks in Rs2. At the same time, multiply the bottom 8-bit Q7
 * content of 16-bit chunks in Rs1 with the bottom 8-bit Q7 content of 16-bit chunks in Rs2.
 * For the `KHMX16` instruction, multiply the top 8-bit Q7 content of 16-bit chunks in Rs1 with the
 * bottom 8-bit Q7 content of 16-bit chunks in Rs2. At the same time, multiply the bottom 8-bit Q7
 * content of 16-bit chunks in Rs1 with the top 8-bit Q7 content of 16-bit chunks in Rs2.
 * The Q14 results are then right-shifted 7-bits and saturated into Q7 values. The Q7 results are then
 * written into Rd. When both the two Q7 inputs of a multiplication are 0x80, saturation will happen.
 * The result will be saturated to 0x7F and the overflow flag OV will be set.
 *
 * **Operations**:\n
 * ~~~
 * if (is `KHM8`) {
 *   op1t = Rs1.B[x+1]; op2t = Rs2.B[x+1]; // top
 *   op1b = Rs1.B[x]; op2b = Rs2.B[x]; // bottom
 * } else if (is `KHMX8`) {
 *   op1t = Rs1.H[x+1]; op2t = Rs2.H[x]; // Rs1 top
 *   op1b = Rs1.H[x]; op2b = Rs2.H[x+1]; // Rs1 bottom
 * }
 * for ((aop,bop,res) in [(op1t,op2t,rest), (op1b,op2b,resb)]) {
 *   if (0x80 != aop | 0x80 != bop) {
 *     res = (aop s* bop) >> 7;
 *   } else {
 *     res= 0x7F;
 *     OV = 1;
 *   }
 * }
 * Rd.H[x/2] = concat(rest, resb);
 * for RV32, x=0,2
 * for RV64, x=0,2,4,6
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KHMX8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("khmx8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.35.2. KHMX8 ===== */

/* ===== Inline Function Start for 3.36.1. KHM16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_MULTIPLY
 * \brief KHM16 (SIMD Signed Saturating Q15 Multiply)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KHM16 Rd, Rs1, Rs2
 * KHMX16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do Q15xQ15 element multiplications simultaneously. The Q30 results are then reduced to
 * Q15 numbers again.
 *
 * **Description**:\n
 * For the `KHM16` instruction, multiply the top 16-bit Q15 content of 32-bit chunks in
 * Rs1 with the top 16-bit Q15 content of 32-bit chunks in Rs2. At the same time, multiply the bottom
 * 16-bit Q15 content of 32-bit chunks in Rs1 with the bottom 16-bit Q15 content of 32-bit chunks in
 * Rs2.
 * For the `KHMX16` instruction, multiply the top 16-bit Q15 content of 32-bit chunks in Rs1 with the
 * bottom 16-bit Q15 content of 32-bit chunks in Rs2. At the same time, multiply the bottom 16-bit Q15
 * content of 32-bit chunks in Rs1 with the top 16-bit Q15 content of 32-bit chunks in Rs2.
 * The Q30 results are then right-shifted 15-bits and saturated into Q15 values. The Q15 results are
 * then written into Rd. When both the two Q15 inputs of a multiplication are 0x8000, saturation will
 * happen. The result will be saturated to 0x7FFF and the overflow flag OV will be set.
 *
 * **Operations**:\n
 * ~~~
 * if (is `KHM16`) {
 *   op1t = Rs1.H[x+1]; op2t = Rs2.H[x+1]; // top
 *   op1b = Rs1.H[x]; op2b = Rs2.H[x]; // bottom
 * } else if (is `KHMX16`) {
 *   op1t = Rs1.H[x+1]; op2t = Rs2.H[x]; // Rs1 top
 *   op1b = Rs1.H[x]; op2b = Rs2.H[x+1]; // Rs1 bottom
 * }
 * for ((aop,bop,res) in [(op1t,op2t,rest), (op1b,op2b,resb)]) {
 *   if (0x8000 != aop | 0x8000 != bop) {
 *     res = (aop s* bop) >> 15;
 *   } else {
 *     res= 0x7FFF;
 *     OV = 1;
 *   }
 * }
 * Rd.W[x/2] = concat(rest, resb);
 * for RV32: x=0
 * for RV64: x=0,2
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KHM16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("khm16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.36.1. KHM16 ===== */

/* ===== Inline Function Start for 3.36.2. KHMX16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_MULTIPLY
 * \brief KHMX16 (SIMD Signed Saturating Crossed Q15 Multiply)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KHM16 Rd, Rs1, Rs2
 * KHMX16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do Q15xQ15 element multiplications simultaneously. The Q30 results are then reduced to
 * Q15 numbers again.
 *
 * **Description**:\n
 * For the `KHM16` instruction, multiply the top 16-bit Q15 content of 32-bit chunks in
 * Rs1 with the top 16-bit Q15 content of 32-bit chunks in Rs2. At the same time, multiply the bottom
 * 16-bit Q15 content of 32-bit chunks in Rs1 with the bottom 16-bit Q15 content of 32-bit chunks in
 * Rs2.
 * For the `KHMX16` instruction, multiply the top 16-bit Q15 content of 32-bit chunks in Rs1 with the
 * bottom 16-bit Q15 content of 32-bit chunks in Rs2. At the same time, multiply the bottom 16-bit Q15
 * content of 32-bit chunks in Rs1 with the top 16-bit Q15 content of 32-bit chunks in Rs2.
 * The Q30 results are then right-shifted 15-bits and saturated into Q15 values. The Q15 results are
 * then written into Rd. When both the two Q15 inputs of a multiplication are 0x8000, saturation will
 * happen. The result will be saturated to 0x7FFF and the overflow flag OV will be set.
 *
 * **Operations**:\n
 * ~~~
 * if (is `KHM16`) {
 *   op1t = Rs1.H[x+1]; op2t = Rs2.H[x+1]; // top
 *   op1b = Rs1.H[x]; op2b = Rs2.H[x]; // bottom
 * } else if (is `KHMX16`) {
 *   op1t = Rs1.H[x+1]; op2t = Rs2.H[x]; // Rs1 top
 *   op1b = Rs1.H[x]; op2b = Rs2.H[x+1]; // Rs1 bottom
 * }
 * for ((aop,bop,res) in [(op1t,op2t,rest), (op1b,op2b,resb)]) {
 *   if (0x8000 != aop | 0x8000 != bop) {
 *     res = (aop s* bop) >> 15;
 *   } else {
 *     res= 0x7FFF;
 *     OV = 1;
 *   }
 * }
 * Rd.W[x/2] = concat(rest, resb);
 * for RV32: x=0
 * for RV64: x=0,2
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KHMX16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("khmx16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.36.2. KHMX16 ===== */

/* ===== Inline Function Start for 3.37.1. KHMBB ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q15_SAT_ALU
 * \brief KHMBB (Signed Saturating Half Multiply B16 x B16)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * KHMxy Rd, Rs1, Rs2 (xy = BB, BT, TT)
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed Q15 number contents of two 16-bit data in the corresponding portion
 * of the lower 32-bit chunk in registers and then right-shift 15 bits to turn the Q30 result into a Q15
 * number again and saturate the Q15 result into the destination register. If saturation happens, an
 * overflow flag OV will be set.
 *
 * **Description**:\n
 * Multiply the top or bottom 16-bit Q15 content of the lower 32-bit portion in Rs1 with
 * the top or bottom 16-bit Q15 content of the lower 32-bit portion in Rs2. The Q30 result is then right-
 * shifted 15-bits and saturated into a Q15 value. The Q15 value is then sing-extended and written into
 * Rd. When both the two Q15 inputs are 0x8000, saturation will happen. The result will be saturated
 * to 0x7FFF and the overflow flag OV will be set.
 *
 * **Operations**:\n
 * ~~~
 * aop = Rs1.H[0]; bop = Rs2.H[0]; // KHMBB
 * aop = Rs1.H[0]; bop = Rs2.H[1]; // KHMBT
 * aop = Rs1.H[1]; bop = Rs2.H[1]; // KHMTT
 * If (0x8000 != aop | 0x8000 != bop) {
 *   Mresult[31:0] = aop * bop;
 *   res[15:0] = Mresult[30:15];
 * } else {
 *   res[15:0] = 0x7FFF;
 *   OV = 1;
 * }
 * Rd = SE32(res[15:0]); // Rv32
 * Rd = SE64(res[15:0]); // RV64
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KHMBB(unsigned int a, unsigned int b)
{
    long result;
    __ASM volatile("khmbb %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.37.1. KHMBB ===== */

/* ===== Inline Function Start for 3.37.2. KHMBT ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q15_SAT_ALU
 * \brief KHMBT (Signed Saturating Half Multiply B16 x T16)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * KHMxy Rd, Rs1, Rs2 (xy = BB, BT, TT)
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed Q15 number contents of two 16-bit data in the corresponding portion
 * of the lower 32-bit chunk in registers and then right-shift 15 bits to turn the Q30 result into a Q15
 * number again and saturate the Q15 result into the destination register. If saturation happens, an
 * overflow flag OV will be set.
 *
 * **Description**:\n
 * Multiply the top or bottom 16-bit Q15 content of the lower 32-bit portion in Rs1 with
 * the top or bottom 16-bit Q15 content of the lower 32-bit portion in Rs2. The Q30 result is then right-
 * shifted 15-bits and saturated into a Q15 value. The Q15 value is then sing-extended and written into
 * Rd. When both the two Q15 inputs are 0x8000, saturation will happen. The result will be saturated
 * to 0x7FFF and the overflow flag OV will be set.
 *
 * **Operations**:\n
 * ~~~
 * aop = Rs1.H[0]; bop = Rs2.H[0]; // KHMBB
 * aop = Rs1.H[0]; bop = Rs2.H[1]; // KHMBT
 * aop = Rs1.H[1]; bop = Rs2.H[1]; // KHMTT
 * If (0x8000 != aop | 0x8000 != bop) {
 *   Mresult[31:0] = aop * bop;
 *   res[15:0] = Mresult[30:15];
 * } else {
 *   res[15:0] = 0x7FFF;
 *   OV = 1;
 * }
 * Rd = SE32(res[15:0]); // Rv32
 * Rd = SE64(res[15:0]); // RV64
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KHMBT(unsigned int a, unsigned int b)
{
    long result;
    __ASM volatile("khmbt %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.37.2. KHMBT ===== */

/* ===== Inline Function Start for 3.37.3. KHMTT ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q15_SAT_ALU
 * \brief KHMTT (Signed Saturating Half Multiply T16 x T16)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * KHMxy Rd, Rs1, Rs2 (xy = BB, BT, TT)
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed Q15 number contents of two 16-bit data in the corresponding portion
 * of the lower 32-bit chunk in registers and then right-shift 15 bits to turn the Q30 result into a Q15
 * number again and saturate the Q15 result into the destination register. If saturation happens, an
 * overflow flag OV will be set.
 *
 * **Description**:\n
 * Multiply the top or bottom 16-bit Q15 content of the lower 32-bit portion in Rs1 with
 * the top or bottom 16-bit Q15 content of the lower 32-bit portion in Rs2. The Q30 result is then right-
 * shifted 15-bits and saturated into a Q15 value. The Q15 value is then sing-extended and written into
 * Rd. When both the two Q15 inputs are 0x8000, saturation will happen. The result will be saturated
 * to 0x7FFF and the overflow flag OV will be set.
 *
 * **Operations**:\n
 * ~~~
 * aop = Rs1.H[0]; bop = Rs2.H[0]; // KHMBB
 * aop = Rs1.H[0]; bop = Rs2.H[1]; // KHMBT
 * aop = Rs1.H[1]; bop = Rs2.H[1]; // KHMTT
 * If (0x8000 != aop | 0x8000 != bop) {
 *   Mresult[31:0] = aop * bop;
 *   res[15:0] = Mresult[30:15];
 * } else {
 *   res[15:0] = 0x7FFF;
 *   OV = 1;
 * }
 * Rd = SE32(res[15:0]); // Rv32
 * Rd = SE64(res[15:0]); // RV64
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KHMTT(unsigned int a, unsigned int b)
{
    long result;
    __ASM volatile("khmtt %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.37.3. KHMTT ===== */

/* ===== Inline Function Start for 3.38.1. KMABB ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB
 * \brief KMABB (SIMD Saturating Signed Multiply Bottom Halfs & Add)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMABB Rd, Rs1, Rs2
 * KMABT Rd, Rs1, Rs2
 * KMATT Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 16-bit content of 32-bit elements in a register with the 16-bit content
 * of 32-bit elements in another register and add the result to the content of 32-bit elements in the
 * third register. The addition result may be saturated and is written to the third register.
 * * KMABB: rd.W[x] + bottom*bottom (per 32-bit element)
 * * KMABT rd.W[x] + bottom*top (per 32-bit element)
 * * KMATT rd.W[x] + top*top (per 32-bit element)
 *
 * **Description**:\n
 * For the `KMABB` instruction, it multiplies the bottom 16-bit content of 32-bit elements in Rs1 with
 * the bottom 16-bit content of 32-bit elements in Rs2.
 * For the `KMABT` instruction, it multiplies the bottom 16-bit content of 32-bit elements in Rs1 with
 * the top 16-bit content of 32-bit elements in Rs2.
 * For the `KMATT` instruction, it multiplies the top 16-bit content of 32-bit elements in Rs1 with the
 * top 16-bit content of 32-bit elements in Rs2.
 * The multiplication result is added to the content of 32-bit elements in Rd. If the addition result is
 * beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the range and the OV bit is set to
 * 1. The results after saturation are written to Rd. The 16-bit contents of Rs1 and Rs2 are treated as
 * signed integers.
 *
 * **Operations**:\n
 * ~~~
 * res[x] = Rd.W[x] + (Rs1.W[x].H[0] * Rs2.W[x].H[0]); // KMABB
 * res[x] = Rd.W[x] + (Rs1.W[x].H[0] * Rs2.W[x].H[1]); // KMABT
 * res[x] = Rd.W[x] + (Rs1.W[x].H[1] * Rs2.W[x].H[1]); // KMATT
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMABB(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("kmabb %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.38.1. KMABB ===== */

/* ===== Inline Function Start for 3.38.2. KMABT ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB
 * \brief KMABT (SIMD Saturating Signed Multiply Bottom & Top Halfs & Add)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMABB Rd, Rs1, Rs2
 * KMABT Rd, Rs1, Rs2
 * KMATT Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 16-bit content of 32-bit elements in a register with the 16-bit content
 * of 32-bit elements in another register and add the result to the content of 32-bit elements in the
 * third register. The addition result may be saturated and is written to the third register.
 * * KMABB: rd.W[x] + bottom*bottom (per 32-bit element)
 * * KMABT rd.W[x] + bottom*top (per 32-bit element)
 * * KMATT rd.W[x] + top*top (per 32-bit element)
 *
 * **Description**:\n
 * For the `KMABB` instruction, it multiplies the bottom 16-bit content of 32-bit elements in Rs1 with
 * the bottom 16-bit content of 32-bit elements in Rs2.
 * For the `KMABT` instruction, it multiplies the bottom 16-bit content of 32-bit elements in Rs1 with
 * the top 16-bit content of 32-bit elements in Rs2.
 * For the `KMATT` instruction, it multiplies the top 16-bit content of 32-bit elements in Rs1 with the
 * top 16-bit content of 32-bit elements in Rs2.
 * The multiplication result is added to the content of 32-bit elements in Rd. If the addition result is
 * beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the range and the OV bit is set to
 * 1. The results after saturation are written to Rd. The 16-bit contents of Rs1 and Rs2 are treated as
 * signed integers.
 *
 * **Operations**:\n
 * ~~~
 * res[x] = Rd.W[x] + (Rs1.W[x].H[0] * Rs2.W[x].H[0]); // KMABB
 * res[x] = Rd.W[x] + (Rs1.W[x].H[0] * Rs2.W[x].H[1]); // KMABT
 * res[x] = Rd.W[x] + (Rs1.W[x].H[1] * Rs2.W[x].H[1]); // KMATT
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMABT(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("kmabt %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.38.2. KMABT ===== */

/* ===== Inline Function Start for 3.38.3. KMATT ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB
 * \brief KMATT (SIMD Saturating Signed Multiply Top Halfs & Add)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMABB Rd, Rs1, Rs2
 * KMABT Rd, Rs1, Rs2
 * KMATT Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 16-bit content of 32-bit elements in a register with the 16-bit content
 * of 32-bit elements in another register and add the result to the content of 32-bit elements in the
 * third register. The addition result may be saturated and is written to the third register.
 * * KMABB: rd.W[x] + bottom*bottom (per 32-bit element)
 * * KMABT rd.W[x] + bottom*top (per 32-bit element)
 * * KMATT rd.W[x] + top*top (per 32-bit element)
 *
 * **Description**:\n
 * For the `KMABB` instruction, it multiplies the bottom 16-bit content of 32-bit elements in Rs1 with
 * the bottom 16-bit content of 32-bit elements in Rs2.
 * For the `KMABT` instruction, it multiplies the bottom 16-bit content of 32-bit elements in Rs1 with
 * the top 16-bit content of 32-bit elements in Rs2.
 * For the `KMATT` instruction, it multiplies the top 16-bit content of 32-bit elements in Rs1 with the
 * top 16-bit content of 32-bit elements in Rs2.
 * The multiplication result is added to the content of 32-bit elements in Rd. If the addition result is
 * beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the range and the OV bit is set to
 * 1. The results after saturation are written to Rd. The 16-bit contents of Rs1 and Rs2 are treated as
 * signed integers.
 *
 * **Operations**:\n
 * ~~~
 * res[x] = Rd.W[x] + (Rs1.W[x].H[0] * Rs2.W[x].H[0]); // KMABB
 * res[x] = Rd.W[x] + (Rs1.W[x].H[0] * Rs2.W[x].H[1]); // KMABT
 * res[x] = Rd.W[x] + (Rs1.W[x].H[1] * Rs2.W[x].H[1]); // KMATT
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMATT(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("kmatt %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.38.3. KMATT ===== */

/* ===== Inline Function Start for 3.39.1. KMADA ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB
 * \brief KMADA (SIMD Saturating Signed Multiply Two Halfs and Two Adds)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMADA Rd, Rs1, Rs2
 * KMAXDA Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from 32-bit elements in two registers; and then adds
 * the two 32-bit results and 32-bit elements in a third register together. The addition result may be
 * saturated.
 * * KMADA: rd.W[x] + top*top + bottom*bottom (per 32-bit element)
 * * KMAXDA: rd.W[x] + top*bottom + bottom*top (per 32-bit element)
 *
 * **Description**:\n
 * For the `KMADA instruction, it multiplies the bottom 16-bit content of 32-bit elements in Rs1 with
 * the bottom 16-bit content of 32-bit elements in Rs2 and then adds the result to the result of
 * multiplying the top 16-bit content of 32-bit elements in Rs1 with the top 16-bit content of 32-bit
 * elements in Rs2.
 * For the `KMAXDA` instruction, it multiplies the top 16-bit content of 32-bit elements in Rs1 with the
 * bottom 16-bit content of 32-bit elements in Rs2 and then adds the result to the result of multiplying
 * the bottom 16-bit content of 32-bit elements in Rs1 with the top 16-bit content of 32-bit elements in
 * Rs2.
 * The result is added to the content of 32-bit elements in Rd. If the addition result is beyond the Q31
 * number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the range and the OV bit is set to 1. The 32-bit
 * results after saturation are written to Rd. The 16-bit contents of Rs1 and Rs2 are treated as signed
 * integers.
 *
 * **Operations**:\n
 * ~~~
 * // KMADA
 * res[x] = Rd.W[x] + (Rs1.W[x].H[1] * Rs2.W[x].H[1]) + (Rs1.W[x].H[0] * Rs2.W[x].H[0]);
 * // KMAXDA
 * res[x] = Rd.W[x] + (Rs1.W[x].H[1] * Rs2.W[x].H[0]) + (Rs1.W[x].H[0] * Rs2.W[x].H[1]);
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 * OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMADA(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("kmada %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.39.1. KMADA ===== */

/* ===== Inline Function Start for 3.39.2. KMAXDA ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB
 * \brief KMAXDA (SIMD Saturating Signed Crossed Multiply Two Halfs and Two Adds)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMADA Rd, Rs1, Rs2
 * KMAXDA Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from 32-bit elements in two registers; and then adds
 * the two 32-bit results and 32-bit elements in a third register together. The addition result may be
 * saturated.
 * * KMADA: rd.W[x] + top*top + bottom*bottom (per 32-bit element)
 * * KMAXDA: rd.W[x] + top*bottom + bottom*top (per 32-bit element)
 *
 * **Description**:\n
 * For the `KMADA instruction, it multiplies the bottom 16-bit content of 32-bit elements in Rs1 with
 * the bottom 16-bit content of 32-bit elements in Rs2 and then adds the result to the result of
 * multiplying the top 16-bit content of 32-bit elements in Rs1 with the top 16-bit content of 32-bit
 * elements in Rs2.
 * For the `KMAXDA` instruction, it multiplies the top 16-bit content of 32-bit elements in Rs1 with the
 * bottom 16-bit content of 32-bit elements in Rs2 and then adds the result to the result of multiplying
 * the bottom 16-bit content of 32-bit elements in Rs1 with the top 16-bit content of 32-bit elements in
 * Rs2.
 * The result is added to the content of 32-bit elements in Rd. If the addition result is beyond the Q31
 * number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the range and the OV bit is set to 1. The 32-bit
 * results after saturation are written to Rd. The 16-bit contents of Rs1 and Rs2 are treated as signed
 * integers.
 *
 * **Operations**:\n
 * ~~~
 * // KMADA
 * res[x] = Rd.W[x] + (Rs1.W[x].H[1] * Rs2.W[x].H[1]) + (Rs1.W[x].H[0] * Rs2.W[x].H[0]);
 * // KMAXDA
 * res[x] = Rd.W[x] + (Rs1.W[x].H[1] * Rs2.W[x].H[0]) + (Rs1.W[x].H[0] * Rs2.W[x].H[1]);
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 * OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMAXDA(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("kmaxda %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.39.2. KMAXDA ===== */

/* ===== Inline Function Start for 3.40.1. KMADS ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB
 * \brief KMADS (SIMD Saturating Signed Multiply Two Halfs & Subtract & Add)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMADS Rd, Rs1, Rs2
 * KMADRS Rd, Rs1, Rs2
 * KMAXDS Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from 32-bit elements in two registers; and then
 * perform a subtraction operation between the two 32-bit results. Then add the subtraction result to
 * the corresponding 32-bit elements in a third register. The addition result may be saturated.
 * * KMADS: rd.W[x] + (top*top - bottom*bottom) (per 32-bit element)
 * * KMADRS: rd.W[x] + (bottom*bottom - top*top) (per 32-bit element)
 * * KMAXDS: rd.W[x] + (top*bottom - bottom*top) (per 32-bit element)
 *
 * **Description**:\n
 * For the `KMADS` instruction, it multiplies the bottom 16-bit content of 32-bit elements in Rs1 with
 * the bottom 16-bit content of 32-bit elements in Rs2 and then subtracts the result from the result of
 * multiplying the top 16-bit content of 32-bit elements in Rs1 with the top 16-bit content of 32-bit
 * elements in Rs2.
 * For the `KMADRS` instruction, it multiplies the top 16-bit content of 32-bit elements in Rs1 with the
 * top 16-bit content of 32-bit elements in Rs2 and then subtracts the result from the result of
 * multiplying the bottom 16-bit content of 32-bit elements in Rs1 with the bottom 16-bit content of 32-
 * bit elements in Rs2.
 * For the `KMAXDS` instruction, it multiplies the bottom 16-bit content of 32-bit elements in Rs1 with
 * the top 16-bit content of 32-bit elements in Rs2 and then subtracts the result from the result of
 * multiplying the top 16-bit content of 32-bit elements in Rs1 with the bottom 16-bit content of 32-bit
 * elements in Rs2.
 * The subtraction result is then added to the content of the corresponding 32-bit elements in Rd. If the
 * addition result is beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the range and
 * the OV bit is set to 1. The 32-bit results after saturation are written to Rd. The 16-bit contents of Rs1
 * and Rs2 are treated as signed integers.
 *
 * **Operations**:\n
 * ~~~
 * // KMADS
 * res[x] = Rd.W[x] + (Rs1.W[x].H[1] * Rs2.W[x].H[1]) - (Rs1.W[x].H[0] * Rs2.W[x].H[0]);
 * // KMADRS
 * res[x] = Rd.W[x] + (Rs1.W[x].H[0] * Rs2.W[x].H[0]) - (Rs1.W[x].H[1] * Rs2.W[x].H[1]);
 * // KMAXDS
 * res[x] = Rd.W[x] + (Rs1.W[x].H[1] * Rs2.W[x].H[0]) - (Rs1.W[x].H[0] * Rs2.W[x].H[1]);
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMADS(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("kmads %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.40.1. KMADS ===== */

/* ===== Inline Function Start for 3.40.2. KMADRS ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB
 * \brief KMADRS (SIMD Saturating Signed Multiply Two Halfs & Reverse Subtract & Add)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMADS Rd, Rs1, Rs2
 * KMADRS Rd, Rs1, Rs2
 * KMAXDS Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from 32-bit elements in two registers; and then
 * perform a subtraction operation between the two 32-bit results. Then add the subtraction result to
 * the corresponding 32-bit elements in a third register. The addition result may be saturated.
 * * KMADS: rd.W[x] + (top*top - bottom*bottom) (per 32-bit element)
 * * KMADRS: rd.W[x] + (bottom*bottom - top*top) (per 32-bit element)
 * * KMAXDS: rd.W[x] + (top*bottom - bottom*top) (per 32-bit element)
 *
 * **Description**:\n
 * For the `KMADS` instruction, it multiplies the bottom 16-bit content of 32-bit elements in Rs1 with
 * the bottom 16-bit content of 32-bit elements in Rs2 and then subtracts the result from the result of
 * multiplying the top 16-bit content of 32-bit elements in Rs1 with the top 16-bit content of 32-bit
 * elements in Rs2.
 * For the `KMADRS` instruction, it multiplies the top 16-bit content of 32-bit elements in Rs1 with the
 * top 16-bit content of 32-bit elements in Rs2 and then subtracts the result from the result of
 * multiplying the bottom 16-bit content of 32-bit elements in Rs1 with the bottom 16-bit content of 32-
 * bit elements in Rs2.
 * For the `KMAXDS` instruction, it multiplies the bottom 16-bit content of 32-bit elements in Rs1 with
 * the top 16-bit content of 32-bit elements in Rs2 and then subtracts the result from the result of
 * multiplying the top 16-bit content of 32-bit elements in Rs1 with the bottom 16-bit content of 32-bit
 * elements in Rs2.
 * The subtraction result is then added to the content of the corresponding 32-bit elements in Rd. If the
 * addition result is beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the range and
 * the OV bit is set to 1. The 32-bit results after saturation are written to Rd. The 16-bit contents of Rs1
 * and Rs2 are treated as signed integers.
 *
 * **Operations**:\n
 * ~~~
 * // KMADS
 * res[x] = Rd.W[x] + (Rs1.W[x].H[1] * Rs2.W[x].H[1]) - (Rs1.W[x].H[0] * Rs2.W[x].H[0]);
 * // KMADRS
 * res[x] = Rd.W[x] + (Rs1.W[x].H[0] * Rs2.W[x].H[0]) - (Rs1.W[x].H[1] * Rs2.W[x].H[1]);
 * // KMAXDS
 * res[x] = Rd.W[x] + (Rs1.W[x].H[1] * Rs2.W[x].H[0]) - (Rs1.W[x].H[0] * Rs2.W[x].H[1]);
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMADRS(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("kmadrs %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.40.2. KMADRS ===== */

/* ===== Inline Function Start for 3.40.3. KMAXDS ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB
 * \brief KMAXDS (SIMD Saturating Signed Crossed Multiply Two Halfs & Subtract & Add)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMADS Rd, Rs1, Rs2
 * KMADRS Rd, Rs1, Rs2
 * KMAXDS Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from 32-bit elements in two registers; and then
 * perform a subtraction operation between the two 32-bit results. Then add the subtraction result to
 * the corresponding 32-bit elements in a third register. The addition result may be saturated.
 * * KMADS: rd.W[x] + (top*top - bottom*bottom) (per 32-bit element)
 * * KMADRS: rd.W[x] + (bottom*bottom - top*top) (per 32-bit element)
 * * KMAXDS: rd.W[x] + (top*bottom - bottom*top) (per 32-bit element)
 *
 * **Description**:\n
 * For the `KMADS` instruction, it multiplies the bottom 16-bit content of 32-bit elements in Rs1 with
 * the bottom 16-bit content of 32-bit elements in Rs2 and then subtracts the result from the result of
 * multiplying the top 16-bit content of 32-bit elements in Rs1 with the top 16-bit content of 32-bit
 * elements in Rs2.
 * For the `KMADRS` instruction, it multiplies the top 16-bit content of 32-bit elements in Rs1 with the
 * top 16-bit content of 32-bit elements in Rs2 and then subtracts the result from the result of
 * multiplying the bottom 16-bit content of 32-bit elements in Rs1 with the bottom 16-bit content of 32-
 * bit elements in Rs2.
 * For the `KMAXDS` instruction, it multiplies the bottom 16-bit content of 32-bit elements in Rs1 with
 * the top 16-bit content of 32-bit elements in Rs2 and then subtracts the result from the result of
 * multiplying the top 16-bit content of 32-bit elements in Rs1 with the bottom 16-bit content of 32-bit
 * elements in Rs2.
 * The subtraction result is then added to the content of the corresponding 32-bit elements in Rd. If the
 * addition result is beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the range and
 * the OV bit is set to 1. The 32-bit results after saturation are written to Rd. The 16-bit contents of Rs1
 * and Rs2 are treated as signed integers.
 *
 * **Operations**:\n
 * ~~~
 * // KMADS
 * res[x] = Rd.W[x] + (Rs1.W[x].H[1] * Rs2.W[x].H[1]) - (Rs1.W[x].H[0] * Rs2.W[x].H[0]);
 * // KMADRS
 * res[x] = Rd.W[x] + (Rs1.W[x].H[0] * Rs2.W[x].H[0]) - (Rs1.W[x].H[1] * Rs2.W[x].H[1]);
 * // KMAXDS
 * res[x] = Rd.W[x] + (Rs1.W[x].H[1] * Rs2.W[x].H[0]) - (Rs1.W[x].H[0] * Rs2.W[x].H[1]);
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMAXDS(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("kmaxds %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.40.3. KMAXDS ===== */

/* ===== Inline Function Start for 3.41. KMAR64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_32B_MULT_64B_ADDSUB
 * \brief KMAR64 (Signed Multiply and Saturating Add to 64-Bit Data)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * KMAR64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the 32-bit signed elements in two registers and add the 64-bit multiplication
 * results to the 64-bit signed data of a pair of registers (RV32) or a register (RV64). The result is
 * saturated to the Q63 range and written back to the pair of registers (RV32) or the register (RV64).
 *
 * **RV32 Description**:\n
 * This instruction multiplies the 32-bit signed data of Rs1 with that of Rs2. It adds
 * the 64-bit multiplication result to the 64-bit signed data of an even/odd pair of registers specified by
 * Rd(4,1) with unlimited precision. If the 64-bit addition result is beyond the Q63 number range (-2^63 <=
 * Q63 <= 2^63-1), it is saturated to the range and the OV bit is set to 1. The saturated result is written back
 * to the even/odd pair of registers specified by Rd(4,1).
 * Rx(4,1), i.e., value d, determines the even/odd pair group of two registers. Specifically, the register
 * pair includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 *
 * **RV64 Description**:\n
 * This instruction multiplies the 32-bit signed elements of Rs1 with that of Rs2. It
 * adds the 64-bit multiplication results to the 64-bit signed data of Rd with unlimited precision. If the
 * 64-bit addition result is beyond the Q63 number range (-2^63 <= Q63 <= 2^63-1), it is saturated to the range
 * and the OV bit is set to 1. The saturated result is written back to Rd.
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * result = R[t_H].R[t_L] + (Rs1 * Rs2);
 * if (result > (2^63)-1) {
 *   result = (2^63)-1; OV = 1;
 * } else if (result < -2^63) {
 *   result = -2^63; OV = 1;
 * }
 * R[t_H].R[t_L] = result;
 * RV64:
 * // `result` has unlimited precision
 * result = Rd + (Rs1.W[0] * Rs2.W[0]) + (Rs1.W[1] * Rs2.W[1]);
 * if (result > (2^63)-1) {
 *   result = (2^63)-1; OV = 1;
 * } else if (result < -2^63) {
 *   result = -2^63; OV = 1;
 * }
 * Rd = result;
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_KMAR64(long long t, long a, long b)
{
    __ASM volatile("kmar64 %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.41. KMAR64 ===== */

/* ===== Inline Function Start for 3.42.1. KMDA ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB
 * \brief KMDA (SIMD Signed Multiply Two Halfs and Add)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMDA Rd, Rs1, Rs2
 * KMXDA Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from the 32-bit elements of two registers; and then
 * adds the two 32-bit results together. The addition result may be saturated.
 * * KMDA: top*top + bottom*bottom (per 32-bit element)
 * * KMXDA: top*bottom + bottom*top (per 32-bit element)
 *
 * **Description**:\n
 * For the `KMDA` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2 and then adds the result to the result of
 * multiplying the top 16-bit content of the 32-bit elements of Rs1 with the top 16-bit content of the 32-
 * bit elements of Rs2.
 * For the `KMXDA` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the top 16-bit content of the 32-bit elements of Rs2 and then adds the result to the result of
 * multiplying the top 16-bit content of the 32-bit elements of Rs1 with the bottom 16-bit content of the
 * 32-bit elements of Rs2.
 * The addition result is checked for saturation. If saturation happens, the result is saturated to 2^31-1.
 * The final results are written to Rd. The 16-bit contents are treated as signed integers.
 *
 * **Operations**:\n
 * ~~~
 * if  Rs1.W[x]  !=  0x80008000)  or  (Rs2.W[x]  !=  0x80008000  {  //  KMDA  Rd.W[x]  =  Rs1.W[x].H[1]  *
 * Rs2.W[x].H[1]) + (Rs1.W[x].H[0] * Rs2.W[x].H[0]; // KMXDA Rd.W[x] = Rs1.W[x].H[1] * Rs2.W[x].H[0])
 * +  (Rs1.W[x].H[0]  *  Rs2.W[x].H[1];  }  else  {  Rd.W[x]  =  0x7fffffff;  OV  =  1;  }  for  RV32:  x=0  for  RV64:
 * x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMDA(unsigned long a, unsigned long b)
{
    long result;
    __ASM volatile("kmda %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.42.1. KMDA ===== */

/* ===== Inline Function Start for 3.42.2. KMXDA ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB
 * \brief KMXDA (SIMD Signed Crossed Multiply Two Halfs and Add)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMDA Rd, Rs1, Rs2
 * KMXDA Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from the 32-bit elements of two registers; and then
 * adds the two 32-bit results together. The addition result may be saturated.
 * * KMDA: top*top + bottom*bottom (per 32-bit element)
 * * KMXDA: top*bottom + bottom*top (per 32-bit element)
 *
 * **Description**:\n
 * For the `KMDA` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2 and then adds the result to the result of
 * multiplying the top 16-bit content of the 32-bit elements of Rs1 with the top 16-bit content of the 32-
 * bit elements of Rs2.
 * For the `KMXDA` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the top 16-bit content of the 32-bit elements of Rs2 and then adds the result to the result of
 * multiplying the top 16-bit content of the 32-bit elements of Rs1 with the bottom 16-bit content of the
 * 32-bit elements of Rs2.
 * The addition result is checked for saturation. If saturation happens, the result is saturated to 2^31-1.
 * The final results are written to Rd. The 16-bit contents are treated as signed integers.
 *
 * **Operations**:\n
 * ~~~
 * if  Rs1.W[x]  !=  0x80008000)  or  (Rs2.W[x]  !=  0x80008000  {  //  KMDA  Rd.W[x]  =  Rs1.W[x].H[1]  *
 * Rs2.W[x].H[1]) + (Rs1.W[x].H[0] * Rs2.W[x].H[0]; // KMXDA Rd.W[x] = Rs1.W[x].H[1] * Rs2.W[x].H[0])
 * +  (Rs1.W[x].H[0]  *  Rs2.W[x].H[1];  }  else  {  Rd.W[x]  =  0x7fffffff;  OV  =  1;  }  for  RV32:  x=0  for  RV64:
 * x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMXDA(unsigned long a, unsigned long b)
{
    long result;
    __ASM volatile("kmxda %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.42.2. KMXDA ===== */

/* ===== Inline Function Start for 3.43.1. KMMAC ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X32_MAC
 * \brief KMMAC (SIMD Saturating MSW Signed Multiply Word and Add)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMMAC Rd, Rs1, Rs2
 * KMMAC.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit integer elements of two registers and add the most significant
 * 32-bit results with the signed 32-bit integer elements of a third register. The addition results are
 * saturated first and then written back to the third register. The `.u` form performs an additional
 * rounding up operation on the multiplication results before adding the most significant 32-bit part
 * of the results.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit elements of Rs1 with the signed 32-bit elements of Rs2
 * and adds the most significant 32-bit multiplication results with the signed 32-bit elements of Rd. If
 * the addition result is beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the range
 * and the OV bit is set to 1. The results after saturation are written to Rd. The `.u` form of the
 * instruction additionally rounds up the most significant 32-bit of the 64-bit multiplication results by
 * adding a 1 to bit 31 of the results.
 *
 * **Operations**:\n
 * ~~~
 * Mres[x][63:0] = Rs1.W[x] * Rs2.W[x];
 * if (`.u` form) {
 *   Round[x][32:0] = Mres[x][63:31] + 1;
 *   res[x] = Rd.W[x] + Round[x][32:1];
 * } else {
 *   res[x] = Rd.W[x] + Mres[x][63:32];
 * }
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMMAC(long t, long a, long b)
{
    __ASM volatile("kmmac %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.43.1. KMMAC ===== */

/* ===== Inline Function Start for 3.43.2. KMMAC.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X32_MAC
 * \brief KMMAC.u (SIMD Saturating MSW Signed Multiply Word and Add with Rounding)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMMAC Rd, Rs1, Rs2
 * KMMAC.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit integer elements of two registers and add the most significant
 * 32-bit results with the signed 32-bit integer elements of a third register. The addition results are
 * saturated first and then written back to the third register. The `.u` form performs an additional
 * rounding up operation on the multiplication results before adding the most significant 32-bit part
 * of the results.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit elements of Rs1 with the signed 32-bit elements of Rs2
 * and adds the most significant 32-bit multiplication results with the signed 32-bit elements of Rd. If
 * the addition result is beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the range
 * and the OV bit is set to 1. The results after saturation are written to Rd. The `.u` form of the
 * instruction additionally rounds up the most significant 32-bit of the 64-bit multiplication results by
 * adding a 1 to bit 31 of the results.
 *
 * **Operations**:\n
 * ~~~
 * Mres[x][63:0] = Rs1.W[x] * Rs2.W[x];
 * if (`.u` form) {
 *   Round[x][32:0] = Mres[x][63:31] + 1;
 *   res[x] = Rd.W[x] + Round[x][32:1];
 * } else {
 *   res[x] = Rd.W[x] + Mres[x][63:32];
 * }
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMMAC_U(long t, long a, long b)
{
    __ASM volatile("kmmac.u %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.43.2. KMMAC.u ===== */

/* ===== Inline Function Start for 3.44.1. KMMAWB ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X16_MAC
 * \brief KMMAWB (SIMD Saturating MSW Signed Multiply Word and Bottom Half and Add)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMMAWB Rd, Rs1, Rs2
 * KMMAWB.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit integer elements of one register and the bottom 16-bit of the
 * corresponding 32-bit elements of another register and add the most significant 32-bit results with
 * the corresponding signed 32-bit elements of a third register. The addition result is written to the
 * corresponding 32-bit elements of the third register. The `.u` form rounds up the multiplication
 * results from the most significant discarded bit before the addition operations.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit elements of Rs1 with the signed bottom 16-bit content
 * of the corresponding 32-bit elements of Rs2 and adds the most significant 32-bit multiplication
 * results with the corresponding signed 32-bit elements of Rd. If the addition result is beyond the Q31
 * number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the range and the OV bit is set to 1. The results
 * after saturation are written to the corresponding 32-bit elements of Rd. The `.u` form of the
 * instruction rounds up the most significant 32-bit of the 48-bit multiplication results by adding a 1 to
 * bit 15 of the result before the addition operations.
 *
 * **Operations**:\n
 * ~~~
 * Mres[x][47:0] = Rs1.W[x] * Rs2.W[x].H[0];
 * if (`.u` form) {
 *   Round[x][32:0] = Mres[x][47:15] + 1;
 *   res[x] = Rd.W[x] + Round[x][32:1];
 * } else {
 *   res[x] = Rd.W[x] + Mres[x][47:16];
 * }
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMMAWB(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("kmmawb %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.44.1. KMMAWB ===== */

/* ===== Inline Function Start for 3.44.2. KMMAWB.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X16_MAC
 * \brief KMMAWB.u (SIMD Saturating MSW Signed Multiply Word and Bottom Half and Add with Rounding)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMMAWB Rd, Rs1, Rs2
 * KMMAWB.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit integer elements of one register and the bottom 16-bit of the
 * corresponding 32-bit elements of another register and add the most significant 32-bit results with
 * the corresponding signed 32-bit elements of a third register. The addition result is written to the
 * corresponding 32-bit elements of the third register. The `.u` form rounds up the multiplication
 * results from the most significant discarded bit before the addition operations.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit elements of Rs1 with the signed bottom 16-bit content
 * of the corresponding 32-bit elements of Rs2 and adds the most significant 32-bit multiplication
 * results with the corresponding signed 32-bit elements of Rd. If the addition result is beyond the Q31
 * number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the range and the OV bit is set to 1. The results
 * after saturation are written to the corresponding 32-bit elements of Rd. The `.u` form of the
 * instruction rounds up the most significant 32-bit of the 48-bit multiplication results by adding a 1 to
 * bit 15 of the result before the addition operations.
 *
 * **Operations**:\n
 * ~~~
 * Mres[x][47:0] = Rs1.W[x] * Rs2.W[x].H[0];
 * if (`.u` form) {
 *   Round[x][32:0] = Mres[x][47:15] + 1;
 *   res[x] = Rd.W[x] + Round[x][32:1];
 * } else {
 *   res[x] = Rd.W[x] + Mres[x][47:16];
 * }
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMMAWB_U(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("kmmawb.u %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.44.2. KMMAWB.u ===== */

/* ===== Inline Function Start for 3.45.1. KMMAWB2 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X16_MAC
 * \brief KMMAWB2 (SIMD Saturating MSW Signed Multiply Word and Bottom Half & 2 and Add)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMMAWB2 Rd, Rs1, Rs2
 * KMMAWB2.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit elements of one register and the bottom 16-bit of the
 * corresponding 32-bit elements of another register, double the multiplication results and add the
 * saturated most significant 32-bit results with the corresponding signed 32-bit elements of a third
 * register. The saturated addition result is written to the corresponding 32-bit elements of the third
 * register. The `.u` form rounds up the multiplication results from the most significant discarded bit
 * before the addition operations.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit Q31 elements of Rs1 with the signed bottom 16-bit Q15
 * content of the corresponding 32-bit elements of Rs2, doubles the Q46 results to Q47 numbers and
 * adds the saturated most significant 32-bit Q31 multiplication results with the corresponding signed
 * 32-bit elements of Rd. If the addition result is beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is
 * saturated to the range and the OV bit is set to 1. The results after saturation are written to the
 * corresponding 32-bit elements of Rd. The `.u` form of the instruction rounds up the most significant
 * 32-bit of the 48-bit Q47 multiplication results by adding a 1 to bit 15 (i.e., bit 14 before doubling) of
 * the result before the addition operations.
 *
 * **Operations**:\n
 * ~~~
 * if ((Rs1.W[x] == 0x80000000) & (Rs2.W[x].H[0] == 0x8000)) {
 *   addop.W[x] = 0x7fffffff;
 *   OV = 1;
 * } else {
 *   Mres[x][47:0] = Rs1.W[x] s* Rs2.W[x].H[0];
 *   if (`.u` form) {
 *     Mres[x][47:14] = Mres[x][47:14] + 1;
 *   }
 *   addop.W[x] = Mres[x][46:15]; // doubling
 * }
 * res[x] = Rd.W[x] + addop.W[x];
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMMAWB2(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("kmmawb2 %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.45.1. KMMAWB2 ===== */

/* ===== Inline Function Start for 3.45.2. KMMAWB2.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X16_MAC
 * \brief KMMAWB2.u (SIMD Saturating MSW Signed Multiply Word and Bottom Half & 2 and Add with Rounding)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMMAWB2 Rd, Rs1, Rs2
 * KMMAWB2.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit elements of one register and the bottom 16-bit of the
 * corresponding 32-bit elements of another register, double the multiplication results and add the
 * saturated most significant 32-bit results with the corresponding signed 32-bit elements of a third
 * register. The saturated addition result is written to the corresponding 32-bit elements of the third
 * register. The `.u` form rounds up the multiplication results from the most significant discarded bit
 * before the addition operations.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit Q31 elements of Rs1 with the signed bottom 16-bit Q15
 * content of the corresponding 32-bit elements of Rs2, doubles the Q46 results to Q47 numbers and
 * adds the saturated most significant 32-bit Q31 multiplication results with the corresponding signed
 * 32-bit elements of Rd. If the addition result is beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is
 * saturated to the range and the OV bit is set to 1. The results after saturation are written to the
 * corresponding 32-bit elements of Rd. The `.u` form of the instruction rounds up the most significant
 * 32-bit of the 48-bit Q47 multiplication results by adding a 1 to bit 15 (i.e., bit 14 before doubling) of
 * the result before the addition operations.
 *
 * **Operations**:\n
 * ~~~
 * if ((Rs1.W[x] == 0x80000000) & (Rs2.W[x].H[0] == 0x8000)) {
 *   addop.W[x] = 0x7fffffff;
 *   OV = 1;
 * } else {
 *   Mres[x][47:0] = Rs1.W[x] s* Rs2.W[x].H[0];
 *   if (`.u` form) {
 *     Mres[x][47:14] = Mres[x][47:14] + 1;
 *   }
 *   addop.W[x] = Mres[x][46:15]; // doubling
 * }
 * res[x] = Rd.W[x] + addop.W[x];
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMMAWB2_U(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("kmmawb2.u %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.45.2. KMMAWB2.u ===== */

/* ===== Inline Function Start for 3.46.1. KMMAWT ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X16_MAC
 * \brief KMMAWT (SIMD Saturating MSW Signed Multiply Word and Top Half and Add)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMMAWT Rd, Rs1, Rs2
 * KMMAWT.u Rd Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit integer elements of one register and the signed top 16-bit of the
 * corresponding 32-bit elements of another register and add the most significant 32-bit results with
 * the corresponding signed 32-bit elements of a third register. The addition results are written to the
 * corresponding 32-bit elements of the third register. The `.u` form rounds up the multiplication
 * results from the most significant discarded bit before the addition operations.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit elements of Rs1 with the signed top 16-bit of the
 * corresponding 32-bit elements of Rs2 and adds the most significant 32-bit multiplication results
 * with the corresponding signed 32-bit elements of Rd. If the addition result is beyond the Q31
 * number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the range and the OV bit is set to 1. The results
 * after saturation are written to the corresponding 32-bit elements of Rd. The `.u` form of the
 * instruction rounds up the most significant 32-bit of the 48-bit multiplication results by adding a 1 to
 * bit 15 of the result before the addition operations.
 *
 * **Operations**:\n
 * ~~~
 * Mres[x][47:0] = Rs1.W[x] * Rs2.W[x].H[1];
 * if (`.u` form) {
 *   Round[x][32:0] = Mres[x][47:15] + 1;
 *   res[x] = Rd.W[x] + Round[x][32:1];
 * } else {
 *   res[x] = Rd.W[x] + Mres[x][47:16];
 * }
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMMAWT(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("kmmawt %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.46.1. KMMAWT ===== */

/* ===== Inline Function Start for 3.46.2. KMMAWT.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X16_MAC
 * \brief KMMAWT.u (SIMD Saturating MSW Signed Multiply Word and Top Half and Add with Rounding)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMMAWT Rd, Rs1, Rs2
 * KMMAWT.u Rd Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit integer elements of one register and the signed top 16-bit of the
 * corresponding 32-bit elements of another register and add the most significant 32-bit results with
 * the corresponding signed 32-bit elements of a third register. The addition results are written to the
 * corresponding 32-bit elements of the third register. The `.u` form rounds up the multiplication
 * results from the most significant discarded bit before the addition operations.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit elements of Rs1 with the signed top 16-bit of the
 * corresponding 32-bit elements of Rs2 and adds the most significant 32-bit multiplication results
 * with the corresponding signed 32-bit elements of Rd. If the addition result is beyond the Q31
 * number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the range and the OV bit is set to 1. The results
 * after saturation are written to the corresponding 32-bit elements of Rd. The `.u` form of the
 * instruction rounds up the most significant 32-bit of the 48-bit multiplication results by adding a 1 to
 * bit 15 of the result before the addition operations.
 *
 * **Operations**:\n
 * ~~~
 * Mres[x][47:0] = Rs1.W[x] * Rs2.W[x].H[1];
 * if (`.u` form) {
 *   Round[x][32:0] = Mres[x][47:15] + 1;
 *   res[x] = Rd.W[x] + Round[x][32:1];
 * } else {
 *   res[x] = Rd.W[x] + Mres[x][47:16];
 * }
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMMAWT_U(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("kmmawt.u %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.46.2. KMMAWT.u ===== */

/* ===== Inline Function Start for 3.47.1. KMMAWT2 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X16_MAC
 * \brief KMMAWT2 (SIMD Saturating MSW Signed Multiply Word and Top Half & 2 and Add)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMMAWT2 Rd, Rs1, Rs2
 * KMMAWT2.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit elements of one register and the top 16-bit of the
 * corresponding 32-bit elements of another register, double the multiplication results and add the
 * saturated most significant 32-bit results with the corresponding signed 32-bit elements of a third
 * register. The saturated addition result is written to the corresponding 32-bit elements of the third
 * register. The `.u` form rounds up the multiplication results from the most significant discarded bit
 * before the addition operations.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit Q31 elements of Rs1 with the signed top 16-bit Q15
 * content of the corresponding 32-bit elements of Rs2, doubles the Q46 results to Q47 numbers and
 * adds the saturated most significant 32-bit Q31 multiplication results with the corresponding signed
 * 32-bit elements of Rd. If the addition result is beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is
 * saturated to the range and the OV bit is set to 1. The results after saturation are written to the
 * corresponding 32-bit elements of Rd. The `.u` form of the instruction rounds up the most significant
 * 32-bit of the 48-bit Q47 multiplication results by adding a 1 to bit 15 (i.e., bit 14 before doubling) of
 * the result before the addition operations.
 *
 * **Operations**:\n
 * ~~~
 * if ((Rs1.W[x] == 0x80000000) & (Rs2.W[x].H[1] == 0x8000)) {
 *   addop.W[x] = 0x7fffffff;
 *   OV = 1;
 * } else {
 *   Mres[x][47:0] = Rs1.W[x] s* Rs2.W[x].H[1];
 *   if (`.u` form) {
 *     Mres[x][47:14] = Mres[x][47:14] + 1;
 *   }
 *   addop.W[x] = Mres[x][46:15]; // doubling
 * }
 * res[x] = Rd.W[x] + addop.W[x];
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMMAWT2(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("kmmawt2 %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.47.1. KMMAWT2 ===== */

/* ===== Inline Function Start for 3.47.2. KMMAWT2.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X16_MAC
 * \brief KMMAWT2.u (SIMD Saturating MSW Signed Multiply Word and Top Half & 2 and Add with Rounding)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMMAWT2 Rd, Rs1, Rs2
 * KMMAWT2.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit elements of one register and the top 16-bit of the
 * corresponding 32-bit elements of another register, double the multiplication results and add the
 * saturated most significant 32-bit results with the corresponding signed 32-bit elements of a third
 * register. The saturated addition result is written to the corresponding 32-bit elements of the third
 * register. The `.u` form rounds up the multiplication results from the most significant discarded bit
 * before the addition operations.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit Q31 elements of Rs1 with the signed top 16-bit Q15
 * content of the corresponding 32-bit elements of Rs2, doubles the Q46 results to Q47 numbers and
 * adds the saturated most significant 32-bit Q31 multiplication results with the corresponding signed
 * 32-bit elements of Rd. If the addition result is beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is
 * saturated to the range and the OV bit is set to 1. The results after saturation are written to the
 * corresponding 32-bit elements of Rd. The `.u` form of the instruction rounds up the most significant
 * 32-bit of the 48-bit Q47 multiplication results by adding a 1 to bit 15 (i.e., bit 14 before doubling) of
 * the result before the addition operations.
 *
 * **Operations**:\n
 * ~~~
 * if ((Rs1.W[x] == 0x80000000) & (Rs2.W[x].H[1] == 0x8000)) {
 *   addop.W[x] = 0x7fffffff;
 *   OV = 1;
 * } else {
 *   Mres[x][47:0] = Rs1.W[x] s* Rs2.W[x].H[1];
 *   if (`.u` form) {
 *     Mres[x][47:14] = Mres[x][47:14] + 1;
 *   }
 *   addop.W[x] = Mres[x][46:15]; // doubling
 * }
 * res[x] = Rd.W[x] + addop.W[x];
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMMAWT2_U(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("kmmawt2.u %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.47.2. KMMAWT2.u ===== */

/* ===== Inline Function Start for 3.48.1. KMMSB ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X32_MAC
 * \brief KMMSB (SIMD Saturating MSW Signed Multiply Word and Subtract)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMMSB Rd, Rs1, Rs2
 * KMMSB.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit integer elements of two registers and subtract the most
 * significant 32-bit results from the signed 32-bit elements of a third register. The subtraction results
 * are written to the third register. The `.u` form performs an additional rounding up operation on
 * the multiplication results before subtracting the most significant 32-bit part of the results.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit elements of Rs1 with the signed 32-bit elements of Rs2
 * and subtracts the most significant 32-bit multiplication results from the signed 32-bit elements of
 * Rd. If the subtraction result is beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the
 * range and the OV bit is set to 1. The results after saturation are written to Rd. The `.u` form of the
 * instruction additionally rounds up the most significant 32-bit of the 64-bit multiplication results by
 * adding a 1 to bit 31 of the results.
 *
 * **Operations**:\n
 * ~~~
 * Mres[x][63:0] = Rs1.W[x] * Rs2.W[x];
 * if (`.u` form) {
 *   Round[x][32:0] = Mres[x][63:31] + 1;
 *   res[x] = Rd.W[x] - Round[x][32:1];
 * } else {
 *   res[x] = Rd.W[x] - Mres[x][63:32];
 * }
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMMSB(long t, long a, long b)
{
    __ASM volatile("kmmsb %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.48.1. KMMSB ===== */

/* ===== Inline Function Start for 3.48.2. KMMSB.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X32_MAC
 * \brief KMMSB.u (SIMD Saturating MSW Signed Multiply Word and Subtraction with Rounding)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMMSB Rd, Rs1, Rs2
 * KMMSB.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit integer elements of two registers and subtract the most
 * significant 32-bit results from the signed 32-bit elements of a third register. The subtraction results
 * are written to the third register. The `.u` form performs an additional rounding up operation on
 * the multiplication results before subtracting the most significant 32-bit part of the results.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit elements of Rs1 with the signed 32-bit elements of Rs2
 * and subtracts the most significant 32-bit multiplication results from the signed 32-bit elements of
 * Rd. If the subtraction result is beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is saturated to the
 * range and the OV bit is set to 1. The results after saturation are written to Rd. The `.u` form of the
 * instruction additionally rounds up the most significant 32-bit of the 64-bit multiplication results by
 * adding a 1 to bit 31 of the results.
 *
 * **Operations**:\n
 * ~~~
 * Mres[x][63:0] = Rs1.W[x] * Rs2.W[x];
 * if (`.u` form) {
 *   Round[x][32:0] = Mres[x][63:31] + 1;
 *   res[x] = Rd.W[x] - Round[x][32:1];
 * } else {
 *   res[x] = Rd.W[x] - Mres[x][63:32];
 * }
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMMSB_U(long t, long a, long b)
{
    __ASM volatile("kmmsb.u %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.48.2. KMMSB.u ===== */

/* ===== Inline Function Start for 3.49.1. KMMWB2 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X16_MAC
 * \brief KMMWB2 (SIMD Saturating MSW Signed Multiply Word and Bottom Half & 2)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMMWB2 Rd, Rs1, Rs2
 * KMMWB2.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit integer elements of one register and the bottom 16-bit of the
 * corresponding 32-bit elements of another register, double the multiplication results and write the
 * saturated most significant 32-bit results to the corresponding 32-bit elements of a register. The `.u`
 * form rounds up the results from the most significant discarded bit.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit Q31 elements of Rs1 with the signed bottom 16-bit Q15
 * content of the corresponding 32-bit elements of Rs2, doubles the Q46 results to Q47 numbers and
 * writes the saturated most significant 32-bit Q31 multiplication results to the corresponding 32-bit
 * elements of Rd. The `.u` form of the instruction rounds up the most significant 32-bit of the 48-bit
 * Q47 multiplication results by adding a 1 to bit 15 (i.e., bit 14 before doubling) of the results.
 *
 * **Operations**:\n
 * ~~~
 * if ((Rs1.W[x] == 0x80000000) & (Rs2.W[x].H[0] == 0x8000)) {
 *   Rd.W[x] = 0x7fffffff;
 *   OV = 1;
 * } else {
 *   Mres[x][47:0] = Rs1.W[x] s* Rs2.W[x].H[0];
 *   if (`.u` form) {
 *     Round[x][32:0] = Mres[x][46:14] + 1;
 *     Rd.W[x] = Round[x][32:1];
 *   } else {
 *     Rd.W[x] = Mres[x][46:15];
 *   }
 * }
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMMWB2(long a, unsigned long b)
{
    long result;
    __ASM volatile("kmmwb2 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.49.1. KMMWB2 ===== */

/* ===== Inline Function Start for 3.49.2. KMMWB2.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X16_MAC
 * \brief KMMWB2.u (SIMD Saturating MSW Signed Multiply Word and Bottom Half & 2 with Rounding)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMMWB2 Rd, Rs1, Rs2
 * KMMWB2.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit integer elements of one register and the bottom 16-bit of the
 * corresponding 32-bit elements of another register, double the multiplication results and write the
 * saturated most significant 32-bit results to the corresponding 32-bit elements of a register. The `.u`
 * form rounds up the results from the most significant discarded bit.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit Q31 elements of Rs1 with the signed bottom 16-bit Q15
 * content of the corresponding 32-bit elements of Rs2, doubles the Q46 results to Q47 numbers and
 * writes the saturated most significant 32-bit Q31 multiplication results to the corresponding 32-bit
 * elements of Rd. The `.u` form of the instruction rounds up the most significant 32-bit of the 48-bit
 * Q47 multiplication results by adding a 1 to bit 15 (i.e., bit 14 before doubling) of the results.
 *
 * **Operations**:\n
 * ~~~
 * if ((Rs1.W[x] == 0x80000000) & (Rs2.W[x].H[0] == 0x8000)) {
 *   Rd.W[x] = 0x7fffffff;
 *   OV = 1;
 * } else {
 *   Mres[x][47:0] = Rs1.W[x] s* Rs2.W[x].H[0];
 *   if (`.u` form) {
 *     Round[x][32:0] = Mres[x][46:14] + 1;
 *     Rd.W[x] = Round[x][32:1];
 *   } else {
 *     Rd.W[x] = Mres[x][46:15];
 *   }
 * }
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMMWB2_U(long a, unsigned long b)
{
    long result;
    __ASM volatile("kmmwb2.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.49.2. KMMWB2.u ===== */

/* ===== Inline Function Start for 3.50.1. KMMWT2 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X16_MAC
 * \brief KMMWT2 (SIMD Saturating MSW Signed Multiply Word and Top Half & 2)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMMWT2 Rd, Rs1, Rs2
 * KMMWT2.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit integer elements of one register and the top 16-bit of the
 * corresponding 32-bit elements of another register, double the multiplication results and write the
 * saturated most significant 32-bit results to the corresponding 32-bit elements of a register. The `.u`
 * form rounds up the results from the most significant discarded bit.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit Q31 elements of Rs1 with the signed top 16-bit Q15
 * content of the corresponding 32-bit elements of Rs2, doubles the Q46 results to Q47 numbers and
 * writes the saturated most significant 32-bit Q31 multiplication results to the corresponding 32-bit
 * elements of Rd. The `.u` form of the instruction rounds up the most significant 32-bit of the 48-bit
 * Q47 multiplication results by adding a 1 to bit 15 (i.e., bit 14 before doubling) of the results.
 *
 * **Operations**:\n
 * ~~~
 * if ((Rs1.W[x] == 0x80000000) & (Rs2.W[x].H[1] == 0x8000)) {
 *   Rd.W[x] = 0x7fffffff;
 *   OV = 1;
 * } else {
 *   Mres[x][47:0] = Rs1.W[x] s* Rs2.W[x].H[1];
 *   if (`.u` form) {
 *     Round[x][32:0] = Mres[x][46:14] + 1;
 *     Rd.W[x] = Round[x][32:1];
 *   } else {
 *     Rd.W[x] = Mres[x][46:15];
 *   }
 * }
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMMWT2(long a, unsigned long b)
{
    long result;
    __ASM volatile("kmmwt2 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.50.1. KMMWT2 ===== */

/* ===== Inline Function Start for 3.50.2. KMMWT2.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X16_MAC
 * \brief KMMWT2.u (SIMD Saturating MSW Signed Multiply Word and Top Half & 2 with Rounding)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMMWT2 Rd, Rs1, Rs2
 * KMMWT2.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit integer elements of one register and the top 16-bit of the
 * corresponding 32-bit elements of another register, double the multiplication results and write the
 * saturated most significant 32-bit results to the corresponding 32-bit elements of a register. The `.u`
 * form rounds up the results from the most significant discarded bit.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit Q31 elements of Rs1 with the signed top 16-bit Q15
 * content of the corresponding 32-bit elements of Rs2, doubles the Q46 results to Q47 numbers and
 * writes the saturated most significant 32-bit Q31 multiplication results to the corresponding 32-bit
 * elements of Rd. The `.u` form of the instruction rounds up the most significant 32-bit of the 48-bit
 * Q47 multiplication results by adding a 1 to bit 15 (i.e., bit 14 before doubling) of the results.
 *
 * **Operations**:\n
 * ~~~
 * if ((Rs1.W[x] == 0x80000000) & (Rs2.W[x].H[1] == 0x8000)) {
 *   Rd.W[x] = 0x7fffffff;
 *   OV = 1;
 * } else {
 *   Mres[x][47:0] = Rs1.W[x] s* Rs2.W[x].H[1];
 *   if (`.u` form) {
 *     Round[x][32:0] = Mres[x][46:14] + 1;
 *     Rd.W[x] = Round[x][32:1];
 *   } else {
 *     Rd.W[x] = Mres[x][46:15];
 *   }
 * }
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMMWT2_U(long a, unsigned long b)
{
    long result;
    __ASM volatile("kmmwt2.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.50.2. KMMWT2.u ===== */

/* ===== Inline Function Start for 3.51.1. KMSDA ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB
 * \brief KMSDA (SIMD Saturating Signed Multiply Two Halfs & Add & Subtract)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMSDA Rd, Rs1, Rs2
 * KMSXDA Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from the 32-bit elements of two registers; and then
 * subtracts the two 32-bit results from the corresponding 32-bit elements of a third register. The
 * subtraction result may be saturated.
 * * KMSDA: rd.W[x] - top*top - bottom*bottom (per 32-bit element)
 * * KMSXDA: rd.W[x] - top*bottom - bottom*top (per 32-bit element)
 *
 * **Description**:\n
 * For the `KMSDA` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2 and multiplies the top 16-bit content of
 * the 32-bit elements of Rs1 with the top 16-bit content of the 32-bit elements of Rs2.
 * For the `KMSXDA` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the top 16-bit content of the 32-bit elements of Rs2 and multiplies the top 16-bit content of the
 * 32-bit elements of Rs1 with the bottom 16-bit content of the 32-bit elements of Rs2.
 * The two 32-bit multiplication results are then subtracted from the content of the corresponding 32-
 * bit elements of Rd. If the subtraction result is beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is
 * saturated to the range and the OV bit is set to 1. The results after saturation are written to Rd. The
 * 16-bit contents are treated as signed integers.
 *
 * **Operations**:\n
 * ~~~
 * // KMSDA
 * res[x] = Rd.W[x] - (Rs1.W[x].H[1] * Rs2.W[x].H[1]) - (Rs1.W[x].H[0] * Rs2.W[x].H[0]);
 * // KMSXDA
 * res[x] = Rd.W[x] - (Rs1.W[x].H[1] * Rs2.W[x].H[0]) - (Rs1.W[x].H[0] * Rs2.W[x].H[1]);
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMSDA(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("kmsda %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.51.1. KMSDA ===== */

/* ===== Inline Function Start for 3.51.2. KMSXDA ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB
 * \brief KMSXDA (SIMD Saturating Signed Crossed Multiply Two Halfs & Add & Subtract)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KMSDA Rd, Rs1, Rs2
 * KMSXDA Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from the 32-bit elements of two registers; and then
 * subtracts the two 32-bit results from the corresponding 32-bit elements of a third register. The
 * subtraction result may be saturated.
 * * KMSDA: rd.W[x] - top*top - bottom*bottom (per 32-bit element)
 * * KMSXDA: rd.W[x] - top*bottom - bottom*top (per 32-bit element)
 *
 * **Description**:\n
 * For the `KMSDA` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2 and multiplies the top 16-bit content of
 * the 32-bit elements of Rs1 with the top 16-bit content of the 32-bit elements of Rs2.
 * For the `KMSXDA` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the top 16-bit content of the 32-bit elements of Rs2 and multiplies the top 16-bit content of the
 * 32-bit elements of Rs1 with the bottom 16-bit content of the 32-bit elements of Rs2.
 * The two 32-bit multiplication results are then subtracted from the content of the corresponding 32-
 * bit elements of Rd. If the subtraction result is beyond the Q31 number range (-2^31 <= Q31 <= 2^31-1), it is
 * saturated to the range and the OV bit is set to 1. The results after saturation are written to Rd. The
 * 16-bit contents are treated as signed integers.
 *
 * **Operations**:\n
 * ~~~
 * // KMSDA
 * res[x] = Rd.W[x] - (Rs1.W[x].H[1] * Rs2.W[x].H[1]) - (Rs1.W[x].H[0] * Rs2.W[x].H[0]);
 * // KMSXDA
 * res[x] = Rd.W[x] - (Rs1.W[x].H[1] * Rs2.W[x].H[0]) - (Rs1.W[x].H[0] * Rs2.W[x].H[1]);
 * if (res[x] > (2^31)-1) {
 *   res[x] = (2^31)-1;
 *   OV = 1;
 * } else if (res[x] < -2^31) {
 *   res[x] = -2^31;
 *   OV = 1;
 * }
 * Rd.W[x] = res[x];
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KMSXDA(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("kmsxda %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.51.2. KMSXDA ===== */

/* ===== Inline Function Start for 3.52. KMSR64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_32B_MULT_64B_ADDSUB
 * \brief KMSR64 (Signed Multiply and Saturating Subtract from 64-Bit Data)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * KMSR64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the 32-bit signed elements in two registers and subtract the 64-bit multiplication
 * results from the 64-bit signed data of a pair of registers (RV32) or a register (RV64). The result is
 * saturated to the Q63 range and written back to the pair of registers (RV32) or the register (RV64).
 *
 * **RV32 Description**:\n
 * This instruction multiplies the 32-bit signed data of Rs1 with that of Rs2. It
 * subtracts the 64-bit multiplication result from the 64-bit signed data of an even/odd pair of registers
 * specified by Rd(4,1) with unlimited precision. If the 64-bit subtraction result is beyond the Q63
 * number range (-2^63 <= Q63 <= 2^63-1), it is saturated to the range and the OV bit is set to 1. The saturated
 * result is written back to the even/odd pair of registers specified by Rd(4,1).
 * Rx(4,1), i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 *
 * **RV64 Description**:\n
 * This instruction multiplies the 32-bit signed elements of Rs1 with that of Rs2. It
 * subtracts the 64-bit multiplication results from the 64-bit signed data in Rd with unlimited
 * precision. If the 64-bit subtraction result is beyond the Q63 number range (-2^63 <= Q63 <= 2^63-1), it is
 * saturated to the range and the OV bit is set to 1. The saturated result is written back to Rd.
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * result = R[t_H].R[t_L] - (Rs1 * Rs2);
 * if (result > (2^63)-1) {
 *   result = (2^63)-1; OV = 1;
 * } else if (result < -2^63) {
 *   result = -2^63; OV = 1;
 * }
 * R[t_H].R[t_L] = result;
 * RV64:
 * // `result` has unlimited precision
 * result = Rd - (Rs1.W[0] * Rs2.W[0]) - (Rs1.W[1] * Rs2.W[1]);
 * if (result > (2^63)-1) {
 *   result = (2^63)-1; OV = 1;
 * } else if (result < -2^63) {
 *   result = -2^63; OV = 1;
 * }
 * Rd = result;
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_KMSR64(long long t, long a, long b)
{
    __ASM volatile("kmsr64 %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.52. KMSR64 ===== */

/* ===== Inline Function Start for 3.53. KSLLW ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q31_SAT_ALU
 * \brief KSLLW (Saturating Shift Left Logical for Word)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * KSLLW Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do logical left shift operation with saturation on a 32-bit word. The shift amount is a
 * variable from a GPR.
 *
 * **Description**:\n
 * The first word data in Rs1 is left-shifted logically. The shifted out bits are filled with
 * zero and the shift amount is specified by the low-order 5-bits of the value in the Rs2 register. Any
 * shifted value greater than 2^31-1 is saturated to 2^31-1. Any shifted value smaller than -2^31 is saturated
 * to -2^31. And the saturated result is sign-extended and written to Rd. If any saturation is performed,
 * set OV bit to 1.
 *
 * **Operations**:\n
 * ~~~
 * sa = Rs2[4:0];
 * res[(31+sa):0] = Rs1.W[0] << sa;
 * if (res > (2^31)-1) {
 *   res = 0x7fffffff; OV = 1;
 * } else if (res < -2^31) {
 *   res = 0x80000000; OV = 1;
 * }
 * Rd[31:0] = res[31:0]; // RV32
 * Rd[63:0] = SE(res[31:0]); // RV64
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KSLLW(long a, unsigned int b)
{
    long result;
    __ASM volatile("ksllw %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.53. KSLLW ===== */

/* ===== Inline Function Start for 3.54. KSLLIW ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q31_SAT_ALU
 * \brief KSLLIW (Saturating Shift Left Logical Immediate for Word)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * KSLLIW Rd, Rs1, imm5u
 * ~~~
 *
 * **Purpose**:\n
 * Do logical left shift operation with saturation on a 32-bit word. The shift amount is an
 * immediate value.
 *
 * **Description**:\n
 * The first word data in Rs1 is left-shifted logically. The shifted out bits are filled with
 * zero and the shift amount is specified by the imm5u constant. Any shifted value greater than 2^31-1 is
 * saturated to 2^31-1. Any shifted value smaller than -2^31 is saturated to -2^31. And the saturated result is
 * sign-extended and written to Rd. If any saturation is performed, set OV bit to 1.
 *
 * **Operations**:\n
 * ~~~
 * sa = imm5u;
 * res[(31+sa):0] = Rs1.W[0] << sa;
 * if (res > (2^31)-1) {
 *   res = 0x7fffffff; OV = 1;
 * } else if (res < -2^31) {
 *   res = 0x80000000; OV = 1;
 * }
 * Rd[31:0] = res[31:0]; // RV32
 * Rd[63:0] = SE(res[31:0]); // RV64
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KSLLIW(long a, unsigned int b)
{
    long result;
    __ASM volatile("kslliw %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.54. KSLLIW ===== */

/* ===== Inline Function Start for 3.55. KSLL8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_SHIFT
 * \brief KSLL8 (SIMD 8-bit Saturating Shift Left Logical)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KSLL8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit elements logical left shift operations with saturation simultaneously. The shift
 * amount is a variable from a GPR.
 *
 * **Description**:\n
 * The 8-bit data elements in Rs1 are left-shifted logically. The shifted out bits are filled
 * with zero and the shift amount is specified by the low-order 3-bits of the value in the Rs2 register.
 * Any shifted value greater than 2^7-1 is saturated to 2^7-1. Any shifted value smaller than -2^7 is
 * saturated to -2^7. And the saturated results are written to Rd. If any saturation is performed, set OV
 * bit to 1.
 *
 * **Operations**:\n
 * ~~~
 * sa = Rs2[2:0];
 * if (sa != 0) {
 *   res[(7+sa):0] = Rs1.B[x] << sa;
 *   if (res > (2^7)-1) {
 *     res = 0x7f; OV = 1;
 *   } else if (res < -2^7) {
 *     res = 0x80; OV = 1;
 *   }
 *   Rd.B[x] = res[7:0];
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KSLL8(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("ksll8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.55. KSLL8 ===== */

/* ===== Inline Function Start for 3.56. KSLLI8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_SHIFT
 * \brief KSLLI8 (SIMD 8-bit Saturating Shift Left Logical Immediate)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KSLLI8 Rd, Rs1, imm3u
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit elements logical left shift operations with saturation simultaneously. The shift
 * amount is an immediate value.
 *
 * **Description**:\n
 * The 8-bit data elements in Rs1 are left-shifted logically. The shifted out bits are filled
 * with zero and the shift amount is specified by the imm3u constant. Any shifted value greater than
 * 2^7-1 is saturated to 2^7-1. Any shifted value smaller than -2^7 is saturated to -2^7. And the saturated
 * results are written to Rd. If any saturation is performed, set OV bit to 1.
 *
 * **Operations**:\n
 * ~~~
 * sa = imm3u[2:0];
 * if (sa != 0) {
 *   res[(7+sa):0] = Rs1.B[x] << sa;
 *   if (res > (2^7)-1) {
 *     res = 0x7f; OV = 1;
 *   } else if (res < -2^7) {
 *     res = 0x80; OV = 1;
 *   }
 *   Rd.B[x] = res[7:0];
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KSLLI8(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("kslli8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.56. KSLLI8 ===== */

/* ===== Inline Function Start for 3.57. KSLL16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_SHIFT
 * \brief KSLL16 (SIMD 16-bit Saturating Shift Left Logical)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KSLL16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit elements logical left shift operations with saturation simultaneously. The shift
 * amount is a variable from a GPR.
 *
 * **Description**:\n
 * The 16-bit data elements in Rs1 are left-shifted logically. The shifted out bits are filled
 * with zero and the shift amount is specified by the low-order 4-bits of the value in the Rs2 register.
 * Any shifted value greater than 2^15-1 is saturated to 2^15-1. Any shifted value smaller than -2^15 is
 * saturated to -2^15. And the saturated results are written to Rd. If any saturation is performed, set OV
 * bit to 1.
 *
 * **Operations**:\n
 * ~~~
 * sa = Rs2[3:0];
 * if (sa != 0) {
 *   res[(15+sa):0] = Rs1.H[x] << sa;
 *   if (res > (2^15)-1) {
 *     res = 0x7fff; OV = 1;
 *   } else if (res < -2^15) {
 *     res = 0x8000; OV = 1;
 *   }
 *   Rd.H[x] = res[15:0];
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KSLL16(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("ksll16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.57. KSLL16 ===== */

/* ===== Inline Function Start for 3.58. KSLLI16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_SHIFT
 * \brief KSLLI16 (SIMD 16-bit Saturating Shift Left Logical Immediate)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KSLLI16 Rd, Rs1, imm4u
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit elements logical left shift operations with saturation simultaneously. The shift
 * amount is an immediate value.
 *
 * **Description**:\n
 * The 16-bit data elements in Rs1 are left-shifted logically. The shifted out bits are filled
 * with zero and the shift amount is specified by the imm4u constant. Any shifted value greater than
 * 2^15-1 is saturated to 2^15-1. Any shifted value smaller than -2^15 is saturated to -2^15. And the saturated
 * results are written to Rd. If any saturation is performed, set OV bit to 1.
 *
 * **Operations**:\n
 * ~~~
 * sa = imm4u[3:0];
 * if (sa != 0) {
 *   res[(15+sa):0] = Rs1.H[x] << sa;
 *   if (res > (2^15)-1) {
 *     res = 0x7fff; OV = 1;
 *   } else if (res < -2^15) {
 *     res = 0x8000; OV = 1;
 *   }
 *   Rd.H[x] = res[15:0];
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KSLLI16(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("kslli16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.58. KSLLI16 ===== */

/* ===== Inline Function Start for 3.59.1. KSLRA8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_SHIFT
 * \brief KSLRA8 (SIMD 8-bit Shift Left Logical with Saturation or Shift Right Arithmetic)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KSLRA8 Rd, Rs1, Rs2
 * KSLRA8.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit elements logical left (positive) or arithmetic right (negative) shift operation with
 * Q7 saturation for the left shift. The `.u` form performs additional rounding up operations for the
 * right shift.
 *
 * **Description**:\n
 * The 8-bit data elements of Rs1 are left-shifted logically or right-shifted arithmetically
 * based on the value of Rs2[3:0]. Rs2[3:0] is in the signed range of [-2^3, 2^3-1]. A positive Rs2[3:0] means
 * logical left shift and a negative Rs2[3:0] means arithmetic right shift. The shift amount is the
 * absolute value of Rs2[3:0]. However, the behavior of `Rs2[3:0]==-2^3 (0x8)` is defined to be
 * equivalent to the behavior of `Rs2[3:0]==-(2^3-1) (0x9)`.
 * The left-shifted results are saturated to the 8-bit signed integer range of [-2^7, 2^7-1]. For the `.u` form
 * of the instruction, the right-shifted results are added a 1 to the most significant discarded bit
 * position for rounding effect. After the shift, saturation, or rounding, the final results are written to
 * Rd. If any saturation happens, this instruction sets the OV flag. The value of Rs2[31:4] will not affect
 * this instruction.
 *
 * **Operations**:\n
 * ~~~
 * if (Rs2[3:0] < 0) {
 *   sa = -Rs2[3:0];
 *   sa = (sa == 8)? 7 : sa;
 *   if (`.u` form) {
 *     res[7:-1] = SE9(Rs1.B[x][7:sa-1]) + 1;
 *     Rd.B[x] = res[7:0];
 *   } else {
 *     Rd.B[x] = SE8(Rs1.B[x][7:sa]);
 *   }
 * } else {
 *   sa = Rs2[2:0];
 *   res[(7+sa):0] = Rs1.B[x] <<(logic) sa;
 *   if (res > (2^7)-1) {
 *     res[7:0] = 0x7f; OV = 1;
 *   } else if (res < -2^7) {
 *     res[7:0] = 0x80; OV = 1;
 *   }
 *   Rd.B[x] = res[7:0];
 * }
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KSLRA8(unsigned long a, int b)
{
    unsigned long result;
    __ASM volatile("kslra8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.59.1. KSLRA8 ===== */

/* ===== Inline Function Start for 3.59.2. KSLRA8.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_SHIFT
 * \brief KSLRA8.u (SIMD 8-bit Shift Left Logical with Saturation or Rounding Shift Right Arithmetic)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KSLRA8 Rd, Rs1, Rs2
 * KSLRA8.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit elements logical left (positive) or arithmetic right (negative) shift operation with
 * Q7 saturation for the left shift. The `.u` form performs additional rounding up operations for the
 * right shift.
 *
 * **Description**:\n
 * The 8-bit data elements of Rs1 are left-shifted logically or right-shifted arithmetically
 * based on the value of Rs2[3:0]. Rs2[3:0] is in the signed range of [-2^3, 2^3-1]. A positive Rs2[3:0] means
 * logical left shift and a negative Rs2[3:0] means arithmetic right shift. The shift amount is the
 * absolute value of Rs2[3:0]. However, the behavior of `Rs2[3:0]==-2^3 (0x8)` is defined to be
 * equivalent to the behavior of `Rs2[3:0]==-(2^3-1) (0x9)`.
 * The left-shifted results are saturated to the 8-bit signed integer range of [-2^7, 2^7-1]. For the `.u` form
 * of the instruction, the right-shifted results are added a 1 to the most significant discarded bit
 * position for rounding effect. After the shift, saturation, or rounding, the final results are written to
 * Rd. If any saturation happens, this instruction sets the OV flag. The value of Rs2[31:4] will not affect
 * this instruction.
 *
 * **Operations**:\n
 * ~~~
 * if (Rs2[3:0] < 0) {
 *   sa = -Rs2[3:0];
 *   sa = (sa == 8)? 7 : sa;
 *   if (`.u` form) {
 *     res[7:-1] = SE9(Rs1.B[x][7:sa-1]) + 1;
 *     Rd.B[x] = res[7:0];
 *   } else {
 *     Rd.B[x] = SE8(Rs1.B[x][7:sa]);
 *   }
 * } else {
 *   sa = Rs2[2:0];
 *   res[(7+sa):0] = Rs1.B[x] <<(logic) sa;
 *   if (res > (2^7)-1) {
 *     res[7:0] = 0x7f; OV = 1;
 *   } else if (res < -2^7) {
 *     res[7:0] = 0x80; OV = 1;
 *   }
 *   Rd.B[x] = res[7:0];
 * }
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KSLRA8_U(unsigned long a, int b)
{
    unsigned long result;
    __ASM volatile("kslra8.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.59.2. KSLRA8.u ===== */

/* ===== Inline Function Start for 3.60.1. KSLRA16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_SHIFT
 * \brief KSLRA16 (SIMD 16-bit Shift Left Logical with Saturation or Shift Right Arithmetic)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KSLRA16 Rd, Rs1, Rs2
 * KSLRA16.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit elements logical left (positive) or arithmetic right (negative) shift operation with
 * Q15 saturation for the left shift. The `.u` form performs additional rounding up operations for the
 * right shift.
 *
 * **Description**:\n
 * The 16-bit data elements of Rs1 are left-shifted logically or right-shifted arithmetically
 * based on the value of Rs2[4:0]. Rs2[4:0] is in the signed range of [-2^4, 2^4-1]. A positive Rs2[4:0] means
 * logical left shift and a negative Rs2[4:0] means arithmetic right shift. The shift amount is the
 * absolute value of Rs2[4:0]. However, the behavior of `Rs2[4:0]==-2^4 (0x10)` is defined to be
 * equivalent to the behavior of `Rs2[4:0]==-(2^4-1) (0x11)`.
 * The left-shifted results are saturated to the 16-bit signed integer range of [-2^15, 2^15-1]. For the `.u`
 * form of the instruction, the right-shifted results are added a 1 to the most significant discarded bit
 * position for rounding effect. After the shift, saturation, or rounding, the final results are written to
 * Rd. If any saturation happens, this instruction sets the OV flag. The value of Rs2[31:5] will not affect
 * this instruction.
 *
 * **Operations**:\n
 * ~~~
 * if (Rs2[4:0] < 0) {
 *   sa = -Rs2[4:0];
 *   sa = (sa == 16)? 15 : sa;
 *   if (`.u` form) {
 *     res[15:-1] = SE17(Rs1.H[x][15:sa-1]) + 1;
 *     Rd.H[x] = res[15:0];
 *   } else {
 *     Rd.H[x] = SE16(Rs1.H[x][15:sa]);
 *   }
 * } else {
 *   sa = Rs2[3:0];
 *   res[(15+sa):0] = Rs1.H[x] <<(logic) sa;
 *   if (res > (2^15)-1) {
 *     res[15:0] = 0x7fff; OV = 1;
 *   } else if (res < -2^15) {
 *     res[15:0] = 0x8000; OV = 1;
 *   }
 *   d.H[x] = res[15:0];
 * }
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KSLRA16(unsigned long a, int b)
{
    unsigned long result;
    __ASM volatile("kslra16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.60.1. KSLRA16 ===== */

/* ===== Inline Function Start for 3.60.2. KSLRA16.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_SHIFT
 * \brief KSLRA16.u (SIMD 16-bit Shift Left Logical with Saturation or Rounding Shift Right Arithmetic)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KSLRA16 Rd, Rs1, Rs2
 * KSLRA16.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit elements logical left (positive) or arithmetic right (negative) shift operation with
 * Q15 saturation for the left shift. The `.u` form performs additional rounding up operations for the
 * right shift.
 *
 * **Description**:\n
 * The 16-bit data elements of Rs1 are left-shifted logically or right-shifted arithmetically
 * based on the value of Rs2[4:0]. Rs2[4:0] is in the signed range of [-2^4, 2^4-1]. A positive Rs2[4:0] means
 * logical left shift and a negative Rs2[4:0] means arithmetic right shift. The shift amount is the
 * absolute value of Rs2[4:0]. However, the behavior of `Rs2[4:0]==-2^4 (0x10)` is defined to be
 * equivalent to the behavior of `Rs2[4:0]==-(2^4-1) (0x11)`.
 * The left-shifted results are saturated to the 16-bit signed integer range of [-2^15, 2^15-1]. For the `.u`
 * form of the instruction, the right-shifted results are added a 1 to the most significant discarded bit
 * position for rounding effect. After the shift, saturation, or rounding, the final results are written to
 * Rd. If any saturation happens, this instruction sets the OV flag. The value of Rs2[31:5] will not affect
 * this instruction.
 *
 * **Operations**:\n
 * ~~~
 * if (Rs2[4:0] < 0) {
 *   sa = -Rs2[4:0];
 *   sa = (sa == 16)? 15 : sa;
 *   if (`.u` form) {
 *     res[15:-1] = SE17(Rs1.H[x][15:sa-1]) + 1;
 *     Rd.H[x] = res[15:0];
 *   } else {
 *     Rd.H[x] = SE16(Rs1.H[x][15:sa]);
 *   }
 * } else {
 *   sa = Rs2[3:0];
 *   res[(15+sa):0] = Rs1.H[x] <<(logic) sa;
 *   if (res > (2^15)-1) {
 *     res[15:0] = 0x7fff; OV = 1;
 *   } else if (res < -2^15) {
 *     res[15:0] = 0x8000; OV = 1;
 *   }
 *   d.H[x] = res[15:0];
 * }
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KSLRA16_U(unsigned long a, int b)
{
    unsigned long result;
    __ASM volatile("kslra16.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.60.2. KSLRA16.u ===== */

/* ===== Inline Function Start for 3.61. KSLRAW ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q31_SAT_ALU
 * \brief KSLRAW (Shift Left Logical with Q31 Saturation or Shift Right Arithmetic)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * KSLRAW Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Perform a logical left (positive) or arithmetic right (negative) shift operation with Q31
 * saturation for the left shift on a 32-bit data.
 *
 * **Description**:\n
 * The lower 32-bit content of Rs1 is left-shifted logically or right-shifted arithmetically
 * based on the value of Rs2[5:0]. Rs2[5:0] is in the signed range of [-25, 25-1]. A positive Rs2[5:0] means
 * logical left shift and a negative Rs2[5:0] means arithmetic right shift. The shift amount is the
 * absolute value of Rs2[5:0] clamped to the actual shift range of [0, 31].
 * The left-shifted result is saturated to the 32-bit signed integer range of [-2^31, 2^31-1]. After the shift
 * operation, the final result is bit-31 sign-extended and written to Rd. If any saturation happens, this
 * instruction sets the OV flag. The value of Rs2[31:6] will not affected the operation of this instruction.
 *
 * **Operations**:\n
 * ~~~
 * if (Rs2[5:0] < 0) {
 *   sa = -Rs2[5:0];
 *   sa = (sa == 32)? 31 : sa;
 *   res[31:0] = Rs1.W[0] >>(arith) sa;
 * } else {
 *   sa = Rs2[5:0];
 *   tmp = Rs1.W[0] <<(logic) sa;
 *   if (tmp > (2^31)-1) {
 *     res[31:0] = (2^31)-1;
 *     OV = 1;
 *   } else if (tmp < -2^31) {
 *     res[31:0] = -2^31;
 *     OV = 1
 *   } else {
 *     res[31:0] = tmp[31:0];
 *   }
 * }
 * Rd = res[31:0]; // RV32
 * Rd = SE64(res[31:0]); // RV64
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KSLRAW(int a, int b)
{
    long result;
    __ASM volatile("kslraw %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.61. KSLRAW ===== */

/* ===== Inline Function Start for 3.62. KSLRAW.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q31_SAT_ALU
 * \brief KSLRAW.u (Shift Left Logical with Q31 Saturation or Rounding Shift Right Arithmetic)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * KSLRAW.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Perform a logical left (positive) or arithmetic right (negative) shift operation with Q31
 * saturation for the left shift and a rounding up operation for the right shift on a 32-bit data.
 *
 * **Description**:\n
 * The lower 32-bit content of Rs1 is left-shifted logically or right-shifted arithmetically
 * based on the value of Rs2[5:0]. Rs2[5:0] is in the signed range of [-25, 25-1]. A positive Rs2[5:0] means
 * logical left shift and a negative Rs2[5:0] means arithmetic right shift. The shift amount is the
 * absolute value of Rs2[5:0] clamped to the actual shift range of [0, 31].
 * The left-shifted result is saturated to the 32-bit signed integer range of [-2^31, 2^31-1]. The right-shifted
 * result is added a 1 to the most significant discarded bit position for rounding effect. After the shift,
 * saturation, or rounding, the final result is bit-31 sign-extended and written to Rd. If any saturation
 * happens, this instruction sets the OV flag. The value of Rs2[31:6] will not affect the operation of this
 * instruction.
 *
 * **Operations**:\n
 * ~~~
 * if (Rs2[5:0] < 0) {
 *   sa = -Rs2[5:0];
 *   sa = (sa == 32)? 31 : sa;
 *   res[31:-1] = SE33(Rs1[31:(sa-1)]) + 1;
 *   rst[31:0] = res[31:0];
 * } else {
 *   sa = Rs2[5:0];
 *   tmp = Rs1.W[0] <<(logic) sa;
 *   if (tmp > (2^31)-1) {
 *     rst[31:0] = (2^31)-1;
 *     OV = 1;
 *   } else if (tmp < -2^31) {
 *     rst[31:0] = -2^31;
 *     OV = 1
 *   } else {
 *     rst[31:0] = tmp[31:0];
 *   }
 * }
 * Rd = rst[31:0]; // RV32
 * Rd = SE64(rst[31:0]); // RV64
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KSLRAW_U(int a, int b)
{
    long result;
    __ASM volatile("kslraw.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.62. KSLRAW.u ===== */

/* ===== Inline Function Start for 3.63. KSTAS16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief KSTAS16 (SIMD 16-bit Signed Saturating Straight Addition & Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KSTAS16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit signed integer element saturating addition and 16-bit signed integer element
 * saturating subtraction in a 32-bit chunk simultaneously. Operands are from corresponding
 * positions in 32-bit chunks.
 *
 * **Description**:\n
 * This instruction adds the 16-bit signed integer element in [31:16] of 32-bit chunks in
 * Rs1 with the 16-bit signed integer element in [31:16] of 32-bit chunks in Rs2; at the same time, it
 * subtracts the 16-bit signed integer element in [15:0] of 32-bit chunks in Rs2 from the 16-bit signed
 * integer element in [15:0] of 32-bit chunks in Rs1. If any of the results are beyond the Q15 number
 * range (-2^15 <= Q15 <= 2^15-1), they are saturated to the range and the OV bit is set to 1. The saturated
 * results are written to [31:16] of 32-bit chunks in Rd for addition and [15:0] of 32-bit chunks in Rd for
 * subtraction.
 *
 * **Operations**:\n
 * ~~~
 * res1 = Rs1.W[x][31:16] + Rs2.W[x][31:16];
 * res2 = Rs1.W[x][15:0] - Rs2.W[x][15:0];
 * for (res in [res1, res2]) {
 *   if (res > (2^15)-1) {
 *     res = (2^15)-1;
 *     OV = 1;
 *   } else if (res < -2^15) {
 *     res = -2^15;
 *     OV = 1;
 *   }
 * }
 * Rd.W[x][31:16] = res1;
 * Rd.W[x][15:0] = res2;
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KSTAS16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("kstas16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.63. KSTAS16 ===== */

/* ===== Inline Function Start for 3.64. KSTSA16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief KSTSA16 (SIMD 16-bit Signed Saturating Straight Subtraction & Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KSTSA16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit signed integer element saturating subtraction and 16-bit signed integer element
 * saturating addition in a 32-bit chunk simultaneously. Operands are from corresponding positions in
 * 32-bit chunks.
 *
 * **Description**:\n
 * This instruction subtracts the 16-bit signed integer element in [31:16] of 32-bit chunks
 * in Rs2 from the 16-bit signed integer element in [31:16] of 32-bit chunks in Rs1; at the same time, it
 * adds the 16-bit signed integer element in [15:0] of 32-bit chunks in Rs2 with the 16-bit signed integer
 * element in [15:0] of 32-bit chunks in Rs1. If any of the results are beyond the Q15 number range (-2^15
 * <= Q15 <= 2^15-1), they are saturated to the range and the OV bit is set to 1. The saturated results are
 * written to [31:16] of 32-bit chunks in Rd for subtraction and [15:0] of 32-bit chunks in Rd for
 * addition.
 *
 * **Operations**:\n
 * ~~~
 * res1 = Rs1.W[x][31:16] - Rs2.W[x][31:16];
 * res2 = Rs1.W[x][15:0] + Rs2.W[x][15:0];
 * for (res in [res1, res2]) {
 *   if (res > (2^15)-1) {
 *     res = (2^15)-1;
 *     OV = 1;
 *   } else if (res < -2^15) {
 *     res = -2^15;
 *     OV = 1;
 *   }
 * }
 * Rd.W[x][31:16] = res1;
 * Rd.W[x][15:0] = res2;
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KSTSA16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("kstsa16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.64. KSTSA16 ===== */

/* ===== Inline Function Start for 3.65. KSUB8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_ADDSUB
 * \brief KSUB8 (SIMD 8-bit Signed Saturating Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KSUB8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit signed elements saturating subtractions simultaneously.
 *
 * **Description**:\n
 * This instruction subtracts the 8-bit signed integer elements in Rs2 from the 8-bit
 * signed integer elements in Rs1. If any of the results are beyond the Q7 number range (-2^7 <= Q7 <= 27
 * -1), they are saturated to the range and the OV bit is set to 1. The saturated results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * res[x] = Rs1.B[x] - Rs2.B[x];
 * if (res[x] > (2^7)-1) {
 *   res[x] = (2^7)-1;
 *   OV = 1;
 * } else if (res[x] < -2^7) {
 *   res[x] = -2^7;
 *   OV = 1;
 * }
 * Rd.B[x] = res[x];
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KSUB8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("ksub8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.65. KSUB8 ===== */

/* ===== Inline Function Start for 3.66. KSUB16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief KSUB16 (SIMD 16-bit Signed Saturating Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KSUB16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit signed integer elements saturating subtractions simultaneously.
 *
 * **Description**:\n
 * This instruction subtracts the 16-bit signed integer elements in Rs2 from the 16-bit
 * signed integer elements in Rs1. If any of the results are beyond the Q15 number range (-2^15 <= Q15 <=
 * 2^15-1), they are saturated to the range and the OV bit is set to 1. The saturated results are written to
 * Rd.
 *
 * **Operations**:\n
 * ~~~
 * res[x] = Rs1.H[x] - Rs2.H[x];
 * if (res[x] > (2^15)-1) {
 *   res[x] = (2^15)-1;
 *   OV = 1;
 * } else if (res[x] < -2^15) {
 *   res[x] = -2^15;
 *   OV = 1;
 * }
 * Rd.H[x] = res[x];
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_KSUB16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("ksub16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.66. KSUB16 ===== */

/* ===== Inline Function Start for 3.67. KSUB64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_64B_ADDSUB
 * \brief KSUB64 (64-bit Signed Saturating Subtraction)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * KSUB64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Perform a 64-bit signed integer subtraction. The result is saturated to the Q63 range.
 *
 * **RV32 Description**:\n
 * This instruction subtracts the 64-bit signed integer of an even/odd pair of
 * registers specified by Rs2(4,1) from the 64-bit signed integer of an even/odd pair of registers
 * specified by Rs1(4,1). If the 64-bit result is beyond the Q63 number range (-2^63 <= Q63 <= 2^63-1), it is
 * saturated to the range and the OV bit is set to 1. The saturated result is then written to an even/odd
 * pair of registers specified by Rd(4,1).
 * Rx(4,1), i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the operand and the even `2d`
 * register of the pair contains the low 32-bit of the operand.
 *
 * **RV64 Description**:\n
 * This instruction subtracts the 64-bit signed integer of Rs2 from the 64-bit signed
 * integer of Rs1. If the 64-bit result is beyond the Q63 number range (-2^63 <= Q63 <= 2^63-1), it is saturated
 * to the range and the OV bit is set to 1. The saturated result is then written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * a_L = CONCAT(Rs1(4,1),1'b0); a_H = CONCAT(Rs1(4,1),1'b1);
 * b_L = CONCAT(Rs2(4,1),1'b0); b_H = CONCAT(Rs2(4,1),1'b1);
 * result = R[a_H].R[a_L] - R[b_H].R[b_L];
 * if (result > (2^63)-1) {
 *   result = (2^63)-1; OV = 1;
 * } else if (result < -2^63) {
 *   result = -2^63; OV = 1;
 * }
 * R[t_H].R[t_L] = result;
 * RV64:
 * result = Rs1 - Rs2;
 * if (result > (2^63)-1) {
 *   result = (2^63)-1; OV = 1;
 * } else if (result < -2^63) {
 *   result = -2^63; OV = 1;
 * }
 * Rd = result;
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_KSUB64(long long a, long long b)
{
    long long result;
    __ASM volatile("ksub64 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.67. KSUB64 ===== */

/* ===== Inline Function Start for 3.68. KSUBH ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q15_SAT_ALU
 * \brief KSUBH (Signed Subtraction with Q15 Saturation)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * KSUBH Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Subtract the signed lower 32-bit content of two registers with Q15 saturation.
 *
 * **Description**:\n
 * The signed lower 32-bit content of Rs2 is subtracted from the signed lower 32-bit
 * content of Rs1. And the result is saturated to the 16-bit signed integer range of [-2^15, 2^15-1] and then
 * sign-extended and written to Rd. If saturation happens, this instruction sets the OV flag.
 *
 * **Operations**:\n
 * ~~~
 * tmp = Rs1.W[0] - Rs2.W[0];
 * if (tmp > (2^15)-1) {
 *   res = (2^15)-1;
 *   OV = 1;
 * } else if (tmp < -2^15) {
 *   res = -2^15;
 *   OV = 1
 * } else {
 *   res = tmp;
 * }
 * Rd = SE(res[15:0]);
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KSUBH(int a, int b)
{
    long result;
    __ASM volatile("ksubh %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.68. KSUBH ===== */

/* ===== Inline Function Start for 3.69. KSUBW ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q31_SAT_ALU
 * \brief KSUBW (Signed Subtraction with Q31 Saturation)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * KSUBW Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Subtract the signed lower 32-bit content of two registers with Q31 saturation.
 *
 * **Description**:\n
 * The signed lower 32-bit content of Rs2 is subtracted from the signed lower 32-bit
 * content of Rs1. And the result is saturated to the 32-bit signed integer range of [-2^31, 2^31-1] and then
 * sign-extened and written to Rd. If saturation happens, this instruction sets the OV flag.
 *
 * **Operations**:\n
 * ~~~
 * tmp = Rs1.W[0] - Rs2.W[0];
 * if (tmp > (2^31)-1) {
 *   res = (2^31)-1;
 *   OV = 1;
 * } else if (tmp < -2^31) {
 * res = -2^31;
 *   OV = 1
 * } else {
 *   res = tmp;
 * }
 * Rd = res[31:0]; // RV32
 * Rd = SE(res[31:0]); // RV64
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KSUBW(int a, int b)
{
    long result;
    __ASM volatile("ksubw %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.69. KSUBW ===== */

/* ===== Inline Function Start for 3.70.1. KWMMUL ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X32_MAC
 * \brief KWMMUL (SIMD Saturating MSW Signed Multiply Word & Double)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KWMMUL Rd, Rs1, Rs2
 * KWMMUL.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit integer elements of two registers, shift the results left 1-bit,
 * saturate, and write the most significant 32-bit results to a register. The `.u` form additionally
 * rounds up the multiplication results from the most signification discarded bit.
 *
 * **Description**:\n
 * This instruction multiplies the 32-bit elements of Rs1 with the 32-bit elements of Rs2. It then shifts
 * the multiplication results one bit to the left and takes the most significant 32-bit results. If the
 * shifted result is greater than 2^31-1, it is saturated to 2^31-1 and the OV flag is set to 1. The final element
 * result is written to Rd. The 32-bit elements of Rs1 and Rs2 are treated as signed integers. The `.u`
 * form of the instruction additionally rounds up the 64-bit multiplication results by adding a 1 to bit
 * 30 before the shift and saturation operations.
 *
 * **Operations**:\n
 * ~~~
 * if ((0x80000000 != Rs1.W[x]) | (0x80000000 != Rs2.W[x])) {
 *   Mres[x][63:0] = Rs1.W[x] * Rs2.W[x];
 *   if (`.u` form) {
 *     Round[x][33:0] = Mres[x][63:30] + 1;
 *     Rd.W[x] = Round[x][32:1];
 *   } else {
 *     Rd.W[x] = Mres[x][62:31];
 *   }
 * } else {
 *   Rd.W[x] = 0x7fffffff;
 *   OV = 1;
 * }
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KWMMUL(long a, long b)
{
    long result;
    __ASM volatile("kwmmul %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.70.1. KWMMUL ===== */

/* ===== Inline Function Start for 3.70.2. KWMMUL.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X32_MAC
 * \brief KWMMUL.u (SIMD Saturating MSW Signed Multiply Word & Double with Rounding)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * KWMMUL Rd, Rs1, Rs2
 * KWMMUL.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit integer elements of two registers, shift the results left 1-bit,
 * saturate, and write the most significant 32-bit results to a register. The `.u` form additionally
 * rounds up the multiplication results from the most signification discarded bit.
 *
 * **Description**:\n
 * This instruction multiplies the 32-bit elements of Rs1 with the 32-bit elements of Rs2. It then shifts
 * the multiplication results one bit to the left and takes the most significant 32-bit results. If the
 * shifted result is greater than 2^31-1, it is saturated to 2^31-1 and the OV flag is set to 1. The final element
 * result is written to Rd. The 32-bit elements of Rs1 and Rs2 are treated as signed integers. The `.u`
 * form of the instruction additionally rounds up the 64-bit multiplication results by adding a 1 to bit
 * 30 before the shift and saturation operations.
 *
 * **Operations**:\n
 * ~~~
 * if ((0x80000000 != Rs1.W[x]) | (0x80000000 != Rs2.W[x])) {
 *   Mres[x][63:0] = Rs1.W[x] * Rs2.W[x];
 *   if (`.u` form) {
 *     Round[x][33:0] = Mres[x][63:30] + 1;
 *     Rd.W[x] = Round[x][32:1];
 *   } else {
 *     Rd.W[x] = Mres[x][62:31];
 *   }
 * } else {
 *   Rd.W[x] = 0x7fffffff;
 *   OV = 1;
 * }
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_KWMMUL_U(long a, long b)
{
    long result;
    __ASM volatile("kwmmul.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.70.2. KWMMUL.u ===== */

/* ===== Inline Function Start for 3.71. MADDR32 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_MISC
 * \brief MADDR32 (Multiply and Add to 32-Bit Word)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * MADDR32 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the 32-bit contents of two registers and add the lower 32-bit multiplication result
 * to the 32-bit content of a destination register. Write the final result back to the destination register.
 *
 * **Description**:\n
 * This instruction multiplies the lower 32-bit content of Rs1 with that of Rs2. It adds the
 * lower 32-bit multiplication result to the lower 32-bit content of Rd and writes the final result (RV32)
 * or sign-extended result (RV64) back to Rd. The contents of Rs1 and Rs2 can be either signed or
 * unsigned integers.
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 * Mresult = Rs1 * Rs2;
 * Rd = Rd + Mresult.W[0];
 * RV64:
 * Mresult = Rs1.W[0] * Rs2.W[0];
 * tres[31:0] = Rd.W[0] + Mresult.W[0];
 * Rd = SE64(tres[31:0]);
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_MADDR32(unsigned long t, unsigned long a, unsigned long b)
{
    __ASM volatile("maddr32 %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.71. MADDR32 ===== */

/* ===== Inline Function Start for 3.72. MAXW ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_32B_COMPUTATION
 * \brief MAXW (32-bit Signed Word Maximum)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * MAXW Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Get the larger value from the 32-bit contents of two general registers.
 *
 * **Description**:\n
 * This instruction compares two signed 32-bit integers stored in Rs1 and Rs2, picks the
 * larger value as the result, and writes the result to Rd.
 *
 * **Operations**:\n
 * ~~~
 * if (Rs1.W[0] >= Rs2.W[0]) {
 *   Rd = SE(Rs1.W[0]);
 * } else {
 *   Rd = SE(Rs2.W[0]);
 * }
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_MAXW(int a, int b)
{
    long result;
    __ASM volatile("maxw %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.72. MAXW ===== */

/* ===== Inline Function Start for 3.73. MINW ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_32B_COMPUTATION
 * \brief MINW (32-bit Signed Word Minimum)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * MINW Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Get the smaller value from the 32-bit contents of two general registers.
 *
 * **Description**:\n
 * This instruction compares two signed 32-bit integers stored in Rs1 and Rs2, picks the
 * smaller value as the result, and writes the result to Rd.
 *
 * **Operations**:\n
 * ~~~
 * if (Rs1.W[0] >= Rs2.W[0]) { Rd = SE(Rs2.W[0]); } else { Rd = SE(Rs1.W[0]); }
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_MINW(int a, int b)
{
    long result;
    __ASM volatile("minw %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.73. MINW ===== */

/* ===== Inline Function Start for 3.74. MSUBR32 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_MISC
 * \brief MSUBR32 (Multiply and Subtract from 32-Bit Word)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * MSUBR32 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the 32-bit contents of two registers and subtract the lower 32-bit multiplication
 * result from the 32-bit content of a destination register. Write the final result back to the destination
 * register.
 *
 * **Description**:\n
 * This instruction multiplies the lower 32-bit content of Rs1 with that of Rs2, subtracts
 * the lower 32-bit multiplication result from the lower 32-bit content of Rd, then writes the final
 * result (RV32) or sign-extended result (RV64) back to Rd. The contents of Rs1 and Rs2 can be either
 * signed or unsigned integers.
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 * Mresult = Rs1 * Rs2;
 * Rd = Rd - Mresult.W[0];
 * RV64:
 * Mresult = Rs1.W[0] * Rs2.W[0];
 * tres[31:0] = Rd.W[0] - Mresult.W[0];
 * Rd = SE64(tres[31:0]);
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_MSUBR32(unsigned long t, unsigned long a, unsigned long b)
{
    __ASM volatile("msubr32 %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.74. MSUBR32 ===== */

/* ===== Inline Function Start for 3.75. MULR64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_32B_COMPUTATION
 * \brief MULR64 (Multiply Word Unsigned to 64-bit Data)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * MULR64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the 32-bit unsigned integer contents of two registers and write the 64-bit result.
 *
 * **RV32 Description**:\n
 * This instruction multiplies the 32-bit content of Rs1 with that of Rs2 and writes the 64-bit
 * multiplication result to an even/odd pair of registers containing Rd. Rd(4,1) index d determines the
 * even/odd pair group of the two registers. Specifically, the register pair includes register 2d and
 * 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 * The lower 32-bit contents of Rs1 and Rs2 are treated as unsigned integers.
 *
 * **RV64 Description**:\n
 * This instruction multiplies the lower 32-bit content of Rs1 with that of Rs2 and writes the 64-bit
 * multiplication result to Rd.
 * The lower 32-bit contents of Rs1 and Rs2 are treated as unsigned integers.
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 * Mresult = CONCAT(1`b0,Rs1) u* CONCAT(1`b0,Rs2);
 * R[Rd(4,1).1(0)][31:0] = Mresult[63:32];
 * R[Rd(4,1).0(0)][31:0] = Mresult[31:0];
 * RV64:
 * Rd = Mresult[63:0];
 * Mresult = CONCAT(1`b0,Rs1.W[0]) u* CONCAT(1`b0,Rs2.W[0]);
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_MULR64(unsigned long a, unsigned long b)
{
    unsigned long long result;
    __ASM volatile("mulr64 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.75. MULR64 ===== */

/* ===== Inline Function Start for 3.76. MULSR64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_32B_COMPUTATION
 * \brief MULSR64 (Multiply Word Signed to 64-bit Data)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * MULSR64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the 32-bit signed integer contents of two registers and write the 64-bit result.
 *
 * **RV32 Description**:\n
 * This instruction multiplies the lower 32-bit content of Rs1 with the lower 32-bit content of Rs2 and
 * writes the 64-bit multiplication result to an even/odd pair of registers containing Rd. Rd(4,1) index d
 * determines the even/odd pair group of the two registers. Specifically, the register pair includes
 * register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 * The lower 32-bit contents of Rs1 and Rs2 are treated as signed integers.
 *
 * **RV64 Description**:\n
 * This instruction multiplies the lower 32-bit content of Rs1 with the lower 32-bit content of Rs2 and
 * writes the 64-bit multiplication result to Rd.
 * The lower 32-bit contents of Rs1 and Rs2 are treated as signed integers.
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 * Mresult = Ra s* Rb;
 * R[Rd(4,1).1(0)][31:0] = Mresult[63:32];
 * R[Rd(4,1).0(0)][31:0] = Mresult[31:0];
 * RV64:
 * Mresult = Ra.W[0] s* Rb.W[0];
 * Rd = Mresult[63:0];
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_MULSR64(long a, long b)
{
    long long result;
    __ASM volatile("mulsr64 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.76. MULSR64 ===== */

/* ===== Inline Function Start for 3.77. PBSAD ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_PART_SIMD_MISC
 * \brief PBSAD (Parallel Byte Sum of Absolute Difference)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * PBSAD Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Calculate the sum of absolute difference of unsigned 8-bit data elements.
 *
 * **Description**:\n
 * This instruction subtracts the un-signed 8-bit elements of Rs2 from those of Rs1. Then
 * it adds the absolute value of each difference together and writes the result to Rd.
 *
 * **Operations**:\n
 * ~~~
 * absdiff[x] = ABS(Rs1.B[x] - Rs2.B[x]);
 * Rd = SUM(absdiff[x]);
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_PBSAD(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("pbsad %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.77. PBSAD ===== */

/* ===== Inline Function Start for 3.78. PBSADA ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_PART_SIMD_MISC
 * \brief PBSADA (Parallel Byte Sum of Absolute Difference Accum)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * PBSADA Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Calculate the sum of absolute difference of four unsigned 8-bit data elements and
 * accumulate it into a register.
 *
 * **Description**:\n
 * This instruction subtracts the un-signed 8-bit elements of Rs2 from those of Rs1. It
 * then adds the absolute value of each difference together along with the content of Rd and writes the
 * accumulated result back to Rd.
 *
 * **Operations**:\n
 * ~~~
 * absdiff[x] = ABS(Rs1.B[x] - Rs2.B[x]);
 * Rd = Rd + SUM(absdiff[x]);
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_PBSADA(unsigned long t, unsigned long a, unsigned long b)
{
    __ASM volatile("pbsada %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.78. PBSADA ===== */

/* ===== Inline Function Start for 3.79.1. PKBB16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_PACK
 * \brief PKBB16 (Pack Two 16-bit Data from Both Bottom Half)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * PKBB16 Rd, Rs1, Rs2
 * PKBT16 Rd, Rs1, Rs2
 * PKTT16 Rd, Rs1, Rs2
 * PKTB16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Pack 16-bit data from 32-bit chunks in two registers.
 * * PKBB16: bottom.bottom
 * * PKBT16 bottom.top
 * * PKTT16 top.top
 * * PKTB16 top.bottom
 *
 * **Description**:\n
 * (PKBB16) moves Rs1.W[x][15:0] to Rd.W[x][31:16] and moves Rs2.W[x] [15:0] to
 * Rd.W[x] [15:0].
 * (PKBT16) moves Rs1.W[x] [15:0] to Rd.W[x] [31:16] and moves Rs2.W[x] [31:16] to Rd.W[x] [15:0].
 * (PKTT16) moves Rs1.W[x] [31:16] to Rd.W[x] [31:16] and moves Rs2.W[x] [31:16] to Rd.W[x] [15:0].
 * (PKTB16) moves Rs1.W[x] [31:16] to Rd.W[x] [31:16] and moves Rs2.W[x] [15:0] to Rd.W[x] [15:0].
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:0] = CONCAT(Rs1.W[x][15:0], Rs2.W[x][15:0]); // PKBB16
 * Rd.W[x][31:0] = CONCAT(Rs1.W[x][15:0], Rs2.W[x][31:16]); // PKBT16
 * Rd.W[x][31:0] = CONCAT(Rs1.W[x][31:16], Rs2.W[x][15:0]); // PKTB16
 * Rd.W[x][31:0] = CONCAT(Rs1.W[x][31:16], Rs2.W[x][31:16]); // PKTT16
 * for RV32: x=0,
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_PKBB16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("pkbb16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.79.1. PKBB16 ===== */

/* ===== Inline Function Start for 3.79.2. PKBT16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_PACK
 * \brief PKBT16 (Pack Two 16-bit Data from Bottom and Top Half)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * PKBB16 Rd, Rs1, Rs2
 * PKBT16 Rd, Rs1, Rs2
 * PKTT16 Rd, Rs1, Rs2
 * PKTB16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Pack 16-bit data from 32-bit chunks in two registers.
 * * PKBB16: bottom.bottom
 * * PKBT16 bottom.top
 * * PKTT16 top.top
 * * PKTB16 top.bottom
 *
 * **Description**:\n
 * (PKBB16) moves Rs1.W[x][15:0] to Rd.W[x][31:16] and moves Rs2.W[x] [15:0] to
 * Rd.W[x] [15:0].
 * (PKBT16) moves Rs1.W[x] [15:0] to Rd.W[x] [31:16] and moves Rs2.W[x] [31:16] to Rd.W[x] [15:0].
 * (PKTT16) moves Rs1.W[x] [31:16] to Rd.W[x] [31:16] and moves Rs2.W[x] [31:16] to Rd.W[x] [15:0].
 * (PKTB16) moves Rs1.W[x] [31:16] to Rd.W[x] [31:16] and moves Rs2.W[x] [15:0] to Rd.W[x] [15:0].
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:0] = CONCAT(Rs1.W[x][15:0], Rs2.W[x][15:0]); // PKBB16
 * Rd.W[x][31:0] = CONCAT(Rs1.W[x][15:0], Rs2.W[x][31:16]); // PKBT16
 * Rd.W[x][31:0] = CONCAT(Rs1.W[x][31:16], Rs2.W[x][15:0]); // PKTB16
 * Rd.W[x][31:0] = CONCAT(Rs1.W[x][31:16], Rs2.W[x][31:16]); // PKTT16
 * for RV32: x=0,
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_PKBT16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("pkbt16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.79.2. PKBT16 ===== */

/* ===== Inline Function Start for 3.79.3. PKTT16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_PACK
 * \brief PKTT16 (Pack Two 16-bit Data from Both Top Half)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * PKBB16 Rd, Rs1, Rs2
 * PKBT16 Rd, Rs1, Rs2
 * PKTT16 Rd, Rs1, Rs2
 * PKTB16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Pack 16-bit data from 32-bit chunks in two registers.
 * * PKBB16: bottom.bottom
 * * PKBT16 bottom.top
 * * PKTT16 top.top
 * * PKTB16 top.bottom
 *
 * **Description**:\n
 * (PKBB16) moves Rs1.W[x][15:0] to Rd.W[x][31:16] and moves Rs2.W[x] [15:0] to
 * Rd.W[x] [15:0].
 * (PKBT16) moves Rs1.W[x] [15:0] to Rd.W[x] [31:16] and moves Rs2.W[x] [31:16] to Rd.W[x] [15:0].
 * (PKTT16) moves Rs1.W[x] [31:16] to Rd.W[x] [31:16] and moves Rs2.W[x] [31:16] to Rd.W[x] [15:0].
 * (PKTB16) moves Rs1.W[x] [31:16] to Rd.W[x] [31:16] and moves Rs2.W[x] [15:0] to Rd.W[x] [15:0].
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:0] = CONCAT(Rs1.W[x][15:0], Rs2.W[x][15:0]); // PKBB16
 * Rd.W[x][31:0] = CONCAT(Rs1.W[x][15:0], Rs2.W[x][31:16]); // PKBT16
 * Rd.W[x][31:0] = CONCAT(Rs1.W[x][31:16], Rs2.W[x][15:0]); // PKTB16
 * Rd.W[x][31:0] = CONCAT(Rs1.W[x][31:16], Rs2.W[x][31:16]); // PKTT16
 * for RV32: x=0,
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_PKTT16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("pktt16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.79.3. PKTT16 ===== */

/* ===== Inline Function Start for 3.79.4. PKTB16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_PACK
 * \brief PKTB16 (Pack Two 16-bit Data from Top and Bottom Half)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * PKBB16 Rd, Rs1, Rs2
 * PKBT16 Rd, Rs1, Rs2
 * PKTT16 Rd, Rs1, Rs2
 * PKTB16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Pack 16-bit data from 32-bit chunks in two registers.
 * * PKBB16: bottom.bottom
 * * PKBT16 bottom.top
 * * PKTT16 top.top
 * * PKTB16 top.bottom
 *
 * **Description**:\n
 * (PKBB16) moves Rs1.W[x][15:0] to Rd.W[x][31:16] and moves Rs2.W[x] [15:0] to
 * Rd.W[x] [15:0].
 * (PKBT16) moves Rs1.W[x] [15:0] to Rd.W[x] [31:16] and moves Rs2.W[x] [31:16] to Rd.W[x] [15:0].
 * (PKTT16) moves Rs1.W[x] [31:16] to Rd.W[x] [31:16] and moves Rs2.W[x] [31:16] to Rd.W[x] [15:0].
 * (PKTB16) moves Rs1.W[x] [31:16] to Rd.W[x] [31:16] and moves Rs2.W[x] [15:0] to Rd.W[x] [15:0].
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:0] = CONCAT(Rs1.W[x][15:0], Rs2.W[x][15:0]); // PKBB16
 * Rd.W[x][31:0] = CONCAT(Rs1.W[x][15:0], Rs2.W[x][31:16]); // PKBT16
 * Rd.W[x][31:0] = CONCAT(Rs1.W[x][31:16], Rs2.W[x][15:0]); // PKTB16
 * Rd.W[x][31:0] = CONCAT(Rs1.W[x][31:16], Rs2.W[x][31:16]); // PKTT16
 * for RV32: x=0,
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_PKTB16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("pktb16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.79.4. PKTB16 ===== */

/* ===== Inline Function Start for 3.80. RADD8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_ADDSUB
 * \brief RADD8 (SIMD 8-bit Signed Halving Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * RADD8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit signed integer element additions simultaneously. The element results are halved
 * to avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction adds the 8-bit signed integer elements in Rs1 with the 8-bit signed
 * integer elements in Rs2. The results are first arithmetically right-shifted by 1 bit and then written to
 * Rd.
 *
 * **Examples**:\n
 * ~~~
 * * Rs1 = 0x7F, Rs2 = 0x7F, Rd = 0x7F
 * * Rs1 = 0x80, Rs2 = 0x80, Rd = 0x80
 * * Rs1 = 0x40, Rs2 = 0x80, Rd = 0xE0
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * Rd.B[x] = (Rs1.B[x] + Rs2.B[x]) s>> 1; for RV32: x=3...0, for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_RADD8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("radd8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.80. RADD8 ===== */

/* ===== Inline Function Start for 3.81. RADD16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief RADD16 (SIMD 16-bit Signed Halving Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * RADD16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit signed integer element additions simultaneously. The results are halved to avoid
 * overflow or saturation.
 *
 * **Description**:\n
 * This instruction adds the 16-bit signed integer elements in Rs1 with the 16-bit signed
 * integer elements in Rs2. The results are first arithmetically right-shifted by 1 bit and then written to
 * Rd.
 *
 * **Examples**:\n
 * ~~~
 * * Rs1 = 0x7FFF, Rs2 = 0x7FFF, Rd = 0x7FFF
 * * Rs1 = 0x8000, Rs2 = 0x8000, Rd = 0x8000
 * * Rs1 = 0x4000, Rs2 = 0x8000, Rd = 0xE000
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * Rd.H[x] = (Rs1.H[x] + Rs2.H[x]) s>> 1; for RV32: x=1...0, for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_RADD16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("radd16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.81. RADD16 ===== */

/* ===== Inline Function Start for 3.82. RADD64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_64B_ADDSUB
 * \brief RADD64 (64-bit Signed Halving Addition)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * RADD64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Add two 64-bit signed integers. The result is halved to avoid overflow or saturation.
 *
 * **RV32 Description**:\n
 * This instruction adds the 64-bit signed integer of an even/odd pair of registers
 * specified by Rs1(4,1) with the 64-bit signed integer of an even/odd pair of registers specified by
 * Rs2(4,1). The 64-bit addition result is first arithmetically right-shifted by 1 bit and then written to an
 * even/odd pair of registers specified by Rd(4,1).
 * Rx(4,1), i.e., value d, determines the even/odd pair group of two registers. Specifically, the register
 * pair includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 *
 * **RV64 Description**:\n
 * This instruction adds the 64-bit signed integer in Rs1 with the 64-bit signed
 * integer in Rs2. The 64-bit addition result is first arithmetically right-shifted by 1 bit and then
 * written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * a_L = CONCAT(Rs1(4,1),1'b0); a_H = CONCAT(Rs1(4,1),1'b1);
 * b_L = CONCAT(Rs2(4,1),1'b0); b_H = CONCAT(Rs2(4,1),1'b1);
 * R[t_H].R[t_L] = (R[a_H].R[a_L] + R[b_H].R[b_L]) s>> 1;
 * RV64:
 * Rd = (Rs1 + Rs2) s>> 1;
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_RADD64(long long a, long long b)
{
    long long result;
    __ASM volatile("radd64 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.82. RADD64 ===== */

/* ===== Inline Function Start for 3.83. RADDW ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_32B_COMPUTATION
 * \brief RADDW (32-bit Signed Halving Addition)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * RADDW Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Add 32-bit signed integers and the results are halved to avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction adds the first 32-bit signed integer in Rs1 with the first 32-bit signed
 * integer in Rs2. The result is first arithmetically right-shifted by 1 bit and then sign-extended and
 * written to Rd.
 *
 * **Examples**:\n
 * ~~~
 * * Rs1 = 0x7FFFFFFF, Rs2 = 0x7FFFFFFF, Rd = 0x7FFFFFFF
 * * Rs1 = 0x80000000, Rs2 = 0x80000000, Rd = 0x80000000
 * * Rs1 = 0x40000000, Rs2 = 0x80000000, Rd = 0xE0000000
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 * Rd[31:0] = (Rs1[31:0] + Rs2[31:0]) s>> 1;
 * RV64:
 * resw[31:0] = (Rs1[31:0] + Rs2[31:0]) s>> 1;
 * Rd[63:0] = SE(resw[31:0]);
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_RADDW(int a, int b)
{
    long result;
    __ASM volatile("raddw %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.83. RADDW ===== */

/* ===== Inline Function Start for 3.84. RCRAS16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief RCRAS16 (SIMD 16-bit Signed Halving Cross Addition & Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * RCRAS16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit signed integer element addition and 16-bit signed integer element subtraction in
 * a 32-bit chunk simultaneously. Operands are from crossed positions in 32-bit chunks. The results
 * are halved to avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction adds the 16-bit signed integer element in [31:16] of 32-bit chunks in
 * Rs1 with the 16-bit signed integer element in [15:0] of 32-bit chunks in Rs2, and subtracts the 16-bit
 * signed integer element in [31:16] of 32-bit chunks in Rs2 from the 16-bit signed integer element in
 * [15:0] of 32-bit chunks in Rs1. The element results are first arithmetically right-shifted by 1 bit and
 * then written to [31:16] of 32-bit chunks in Rd and [15:0] of 32-bit chunks in Rd.
 *
 * **Examples**:\n
 * ~~~
 * Please see `RADD16` and `RSUB16` instructions.
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:16] = (Rs1.W[x][31:16] + Rs2.W[x][15:0]) s>> 1;
 * Rd.W[x][15:0] = (Rs1.W[x][15:0] - Rs2.W[x][31:16]) s>> 1;
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_RCRAS16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("rcras16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.84. RCRAS16 ===== */

/* ===== Inline Function Start for 3.85. RCRSA16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief RCRSA16 (SIMD 16-bit Signed Halving Cross Subtraction & Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * RCRSA16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit signed integer element subtraction and 16-bit signed integer element addition in
 * a 32-bit chunk simultaneously. Operands are from crossed positions in 32-bit chunks. The results
 * are halved to avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction subtracts the 16-bit signed integer element in [15:0] of 32-bit chunks
 * in Rs2 from the 16-bit signed integer element in [31:16] of 32-bit chunks in Rs1, and adds the 16-bit
 * signed element integer in [15:0] of 32-bit chunks in Rs1 with the 16-bit signed integer element in
 * [31:16] of 32-bit chunks in Rs2. The two results are first arithmetically right-shifted by 1 bit and
 * then written to [31:16] of 32-bit chunks in Rd and [15:0] of 32-bit chunks in Rd.
 *
 * **Examples**:\n
 * ~~~
 * Please see `RADD16` and `RSUB16` instructions.
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:16] = (Rs1.W[x][31:16] - Rs2.W[x][15:0]) s>> 1;
 * Rd.W[x][15:0] = (Rs1.W[x][15:0] + Rs2.W[x][31:16]) s>> 1;
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_RCRSA16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("rcrsa16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.85. RCRSA16 ===== */

/* ===== Inline Function Start for 3.86. RDOV ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_OV_FLAG_SC
 * \brief RDOV (Read OV flag)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * RDOV Rd  # pseudo mnemonic
 * ~~~
 *
 * **Purpose**:\n
 * This pseudo instruction is an alias to `CSRR Rd, ucode` instruction which maps to the real
 * instruction of `CSRRS Rd, ucode, x0`.
 *
 *
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_RDOV(void)
{
    unsigned long result;
    __ASM volatile("rdov %0" : "=r"(result));
    return result;
}
/* ===== Inline Function End for 3.86. RDOV ===== */

/* ===== Inline Function Start for 3.87. RSTAS16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief RSTAS16 (SIMD 16-bit Signed Halving Straight Addition & Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * RSTAS16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit signed integer element addition and 16-bit signed integer element subtraction in
 * a 32-bit chunk simultaneously. Operands are from corresponding positions in 32-bit chunks. The
 * results are halved to avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction adds the 16-bit signed integer element in [31:16] of 32-bit chunks in
 * Rs1 with the 16-bit signed integer element in [31:16] of 32-bit chunks in Rs2, and subtracts the 16-bit
 * signed integer element in [15:0] of 32-bit chunks in Rs2 from the 16-bit signed integer element in
 * [15:0] of 32-bit chunks in Rs1. The element results are first arithmetically right-shifted by 1 bit and
 * then written to [31:16] of 32-bit chunks in Rd and [15:0] of 32-bit chunks in Rd.
 *
 * **Examples**:\n
 * ~~~
 * Please see `RADD16` and `RSUB16` instructions.
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:16] = (Rs1.W[x][31:16] + Rs2.W[x][31:16]) s>> 1;
 * Rd.W[x][15:0] = (Rs1.W[x][15:0] - Rs2.W[x][15:0]) s>> 1;
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_RSTAS16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("rstas16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.87. RSTAS16 ===== */

/* ===== Inline Function Start for 3.88. RSTSA16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief RSTSA16 (SIMD 16-bit Signed Halving Straight Subtraction & Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * RSTSA16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit signed integer element subtraction and 16-bit signed integer element addition in
 * a 32-bit chunk simultaneously. Operands are from corresponding positions in 32-bit chunks. The
 * results are halved to avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction subtracts the 16-bit signed integer element in [31:16] of 32-bit chunks
 * in Rs2 from the 16-bit signed integer element in [31:16] of 32-bit chunks in Rs1, and adds the 16-bit
 * signed element integer in [15:0] of 32-bit chunks in Rs1 with the 16-bit signed integer element in
 * [15:0] of 32-bit chunks in Rs2. The two results are first arithmetically right-shifted by 1 bit and then
 * written to [31:16] of 32-bit chunks in Rd and [15:0] of 32-bit chunks in Rd.
 *
 * **Examples**:\n
 * ~~~
 * Please see `RADD16` and `RSUB16` instructions.
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:16] = (Rs1.W[x][31:16] - Rs2.W[x][31:16]) s>> 1;
 * Rd.W[x][15:0] = (Rs1.W[x][15:0] + Rs2.W[x][15:0]) s>> 1;
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_RSTSA16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("rstsa16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.88. RSTSA16 ===== */

/* ===== Inline Function Start for 3.89. RSUB8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_ADDSUB
 * \brief RSUB8 (SIMD 8-bit Signed Halving Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * RSUB8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit signed integer element subtractions simultaneously. The results are halved to
 * avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction subtracts the 8-bit signed integer elements in Rs2 from the 8-bit
 * signed integer elements in Rs1. The results are first arithmetically right-shifted by 1 bit and then
 * written to Rd.
 *
 * **Examples**:\n
 * ~~~
 * * Rs1 = 0x7F, Rs2 = 0x80, Rd = 0x7F
 * * Rs1 = 0x80, Rs2 = 0x7F, Rd = 0x80
 * * Rs1= 0x80, Rs2 = 0x40, Rd = 0xA0
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * Rd.B[x] = (Rs1.B[x] - Rs2.B[x]) s>> 1;
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_RSUB8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("rsub8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.89. RSUB8 ===== */

/* ===== Inline Function Start for 3.90. RSUB16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief RSUB16 (SIMD 16-bit Signed Halving Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * RSUB16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit signed integer element subtractions simultaneously. The results are halved to
 * avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction subtracts the 16-bit signed integer elements in Rs2 from the 16-bit
 * signed integer elements in Rs1. The results are first arithmetically right-shifted by 1 bit and then
 * written to Rd.
 *
 * **Examples**:\n
 * ~~~
 * * Ra = 0x7FFF, Rb = 0x8000, Rt = 0x7FFF
 * * Ra = 0x8000, Rb = 0x7FFF, Rt = 0x8000
 * * Ra = 0x8000, Rb = 0x4000, Rt = 0xA000
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * Rd.H[x] = (Rs1.H[x] - Rs2.H[x]) s>> 1;
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_RSUB16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("rsub16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.90. RSUB16 ===== */

/* ===== Inline Function Start for 3.91. RSUB64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_64B_ADDSUB
 * \brief RSUB64 (64-bit Signed Halving Subtraction)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * RSUB64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Perform a 64-bit signed integer subtraction. The result is halved to avoid overflow or
 * saturation.
 *
 * **RV32 Description**:\n
 * This instruction subtracts the 64-bit signed integer of an even/odd pair of
 * registers specified by Rb(4,1) from the 64-bit signed integer of an even/odd pair of registers
 * specified by Ra(4,1). The subtraction result is first arithmetically right-shifted by 1 bit and then
 * written to an even/odd pair of registers specified by Rt(4,1).
 * Rx(4,1), i.e., value d, determines the even/odd pair group of two registers. Specifically, the register
 * pair includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 *
 * **RV64 Description**:\n
 * This instruction subtracts the 64-bit signed integer in Rs2 from the 64-bit signed
 * integer in Rs1. The 64-bit subtraction result is first arithmetically right-shifted by 1 bit and then
 * written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * a_L = CONCAT(Rs1(4,1),1'b0); a_H = CONCAT(Rs1(4,1),1'b1);
 * b_L = CONCAT(Rs2(4,1),1'b0); b_H = CONCAT(Rs2(4,1),1'b1);
 * R[t_H].R[t_L] = (R[a_H].R[a_L] - R[b_H].R[b_L]) s>> 1;
 * RV64:
 * Rd = (Rs1 - Rs2) s>> 1;
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_RSUB64(long long a, long long b)
{
    long long result;
    __ASM volatile("rsub64 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.91. RSUB64 ===== */

/* ===== Inline Function Start for 3.92. RSUBW ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_32B_COMPUTATION
 * \brief RSUBW (32-bit Signed Halving Subtraction)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * RSUBW Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Subtract 32-bit signed integers and the result is halved to avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction subtracts the first 32-bit signed integer in Rs2 from the first 32-bit
 * signed integer in Rs1. The result is first arithmetically right-shifted by 1 bit and then sign-extended
 * and written to Rd.
 *
 * **Examples**:\n
 * ~~~
 * * Rs1 = 0x7FFFFFFF, Rs2 = 0x80000000, Rd = 0x7FFFFFFF
 * * Rs1 = 0x80000000, Rs2 = 0x7FFFFFFF, Rd = 0x80000000
 * * Rs1 = 0x80000000, Rs2 = 0x40000000, Rd = 0xA0000000
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 * Rd[31:0] = (Rs1[31:0] - Rs2[31:0]) s>> 1;
 * RV64:
 * resw[31:0] = (Rs1[31:0] - Rs2[31:0]) s>> 1;
 * Rd[63:0] = SE(resw[31:0]);
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_RSUBW(int a, int b)
{
    long result;
    __ASM volatile("rsubw %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.92. RSUBW ===== */

/* ===== Inline Function Start for 3.93. SCLIP8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_MISC
 * \brief SCLIP8 (SIMD 8-bit Signed Clip Value)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SCLIP8 Rd, Rs1, imm3u[2:0]
 * ~~~
 *
 * **Purpose**:\n
 * Limit the 8-bit signed integer elements of a register into a signed range simultaneously.
 *
 * **Description**:\n
 * This instruction limits the 8-bit signed integer elements stored in Rs1 into a signed
 * integer range between 2^imm3u-1 and -2^imm3u, and writes the limited results to Rd. For example, if
 * imm3u is 3, the 8-bit input values should be saturated between 7 and -8. If saturation is performed,
 * set OV bit to 1.
 *
 * **Operations**:\n
 * ~~~
 * src = Rs1.B[x];
 * if (src > (2^imm3u)-1) {
 *   src = (2^imm3u)-1;
 *   OV = 1;
 * } else if (src < -2^imm3u) {
 *   src = -2^imm3u;
 *   OV = 1;
 * }
 * Rd.B[x] = src
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SCLIP8(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("sclip8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.93. SCLIP8 ===== */

/* ===== Inline Function Start for 3.94. SCLIP16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_MISC
 * \brief SCLIP16 (SIMD 16-bit Signed Clip Value)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SCLIP16 Rd, Rs1, imm4u[3:0]
 * ~~~
 *
 * **Purpose**:\n
 * Limit the 16-bit signed integer elements of a register into a signed range simultaneously.
 *
 * **Description**:\n
 * This instruction limits the 16-bit signed integer elements stored in Rs1 into a signed
 * integer range between 2imm4u-1 and -2imm4u, and writes the limited results to Rd. For example, if
 * imm4u is 3, the 16-bit input values should be saturated between 7 and -8. If saturation is performed,
 * set OV bit to 1.
 *
 * **Operations**:\n
 * ~~~
 * src = Rs1.H[x];
 * if (src > (2^imm4u)-1) {
 *   src = (2^imm4u)-1;
 *   OV = 1;
 * } else if (src < -2^imm4u) {
 *   src = -2^imm4u;
 *   OV = 1;
 * }
 * Rd.H[x] = src
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SCLIP16(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("sclip16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.94. SCLIP16 ===== */

/* ===== Inline Function Start for 3.95. SCLIP32 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_PART_SIMD_MISC
 * \brief SCLIP32 (SIMD 32-bit Signed Clip Value)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * SCLIP32 Rd, Rs1, imm5u[4:0]
 * ~~~
 *
 * **Purpose**:\n
 * Limit the 32-bit signed integer elements of a register into a signed range simultaneously.
 *
 * **Description**:\n
 * This instruction limits the 32-bit signed integer elements stored in Rs1 into a signed
 * integer range between 2imm5u-1 and -2imm5u, and writes the limited results to Rd. For example, if
 * imm5u is 3, the 32-bit input values should be saturated between 7 and -8. If saturation is performed,
 * set OV bit to 1.
 *
 * **Operations**:\n
 * ~~~
 * src = Rs1.W[x];
 * if (src > (2^imm5u)-1) {
 *   src = (2^imm5u)-1;
 *   OV = 1;
 * } else if (src < -2^imm5u) {
 *   src = -2^imm5u;
 *   OV = 1;
 * }
 * Rd.W[x] = src
 * for RV32: x=0,
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_SCLIP32(long a, unsigned int b)
{
    long result;
    __ASM volatile("sclip32 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.95. SCLIP32 ===== */

/* ===== Inline Function Start for 3.96. SCMPLE8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_CMP
 * \brief SCMPLE8 (SIMD 8-bit Signed Compare Less Than & Equal)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SCMPLE8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit signed integer elements less than & equal comparisons simultaneously.
 *
 * **Description**:\n
 * This instruction compares the 8-bit signed integer elements in Rs1 with the 8-bit
 * signed integer elements in Rs2 to see if the one in Rs1 is less than or equal to the one in Rs2. If it is
 * true, the result is 0xFF; otherwise, the result is 0x0. The element comparison results are written to
 * Rd
 *
 * **Operations**:\n
 * ~~~
 * Rd.B[x] = (Rs1.B[x] {le} Rs2.B[x])? 0xff : 0x0;
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SCMPLE8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("scmple8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.96. SCMPLE8 ===== */

/* ===== Inline Function Start for 3.97. SCMPLE16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_CMP
 * \brief SCMPLE16 (SIMD 16-bit Signed Compare Less Than & Equal)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SCMPLE16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit signed integer elements less than & equal comparisons simultaneously.
 *
 * **Description**:\n
 * This instruction compares the 16-bit signed integer elements in Rs1 with the 16-bit
 * signed integer elements in Rs2 to see if the one in Rs1 is less than or equal to the one in Rs2. If it is
 * true, the result is 0xFFFF; otherwise, the result is 0x0. The element comparison results are written
 * to Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.H[x] = (Rs1.H[x] {le} Rs2.H[x])? 0xffff : 0x0;
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SCMPLE16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("scmple16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.97. SCMPLE16 ===== */

/* ===== Inline Function Start for 3.98. SCMPLT8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_CMP
 * \brief SCMPLT8 (SIMD 8-bit Signed Compare Less Than)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SCMPLT8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit signed integer elements less than comparisons simultaneously.
 *
 * **Description**:\n
 * This instruction compares the 8-bit signed integer elements in Rs1 with the 8-bit
 * signed integer elements in Rs2 to see if the one in Rs1 is less than the one in Rs2. If it is true, the
 * result is 0xFF; otherwise, the result is 0x0. The element comparison results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.B[x] = (Rs1.B[x] < Rs2.B[x])? 0xff : 0x0;
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SCMPLT8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("scmplt8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.98. SCMPLT8 ===== */

/* ===== Inline Function Start for 3.99. SCMPLT16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_CMP
 * \brief SCMPLT16 (SIMD 16-bit Signed Compare Less Than)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SCMPLT16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit signed integer elements less than comparisons simultaneously.
 *
 * **Description**:\n
 * This instruction compares the 16-bit signed integer elements in Rs1 with the two 16-
 * bit signed integer elements in Rs2 to see if the one in Rs1 is less than the one in Rs2. If it is true, the
 * result is 0xFFFF; otherwise, the result is 0x0. The element comparison results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.H[x] = (Rs1.H[x] < Rs2.H[x])? 0xffff : 0x0;
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SCMPLT16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("scmplt16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.99. SCMPLT16 ===== */

/* ===== Inline Function Start for 3.100. SLL8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_SHIFT
 * \brief SLL8 (SIMD 8-bit Shift Left Logical)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SLL8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit elements logical left shift operations simultaneously. The shift amount is a
 * variable from a GPR.
 *
 * **Description**:\n
 * The 8-bit elements in Rs1 are left-shifted logically. And the results are written to Rd.
 * The shifted out bits are filled with zero and the shift amount is specified by the low-order 3-bits of
 * the value in the Rs2 register.
 *
 * **Operations**:\n
 * ~~~
 * sa = Rs2[2:0];
 * Rd.B[x] = Rs1.B[x] << sa;
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SLL8(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("sll8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.100. SLL8 ===== */

/* ===== Inline Function Start for 3.101. SLLI8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_SHIFT
 * \brief SLLI8 (SIMD 8-bit Shift Left Logical Immediate)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SLLI8 Rd, Rs1, imm3u
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit elements logical left shift operations simultaneously. The shift amount is an
 * immediate value.
 *
 * **Description**:\n
 * The 8-bit elements in Rs1 are left-shifted logically. And the results are written to Rd.
 * The shifted out bits are filled with zero and the shift amount is specified by the imm3u constant.
 *
 * **Operations**:\n
 * ~~~
 * sa = imm3u[2:0];
 * Rd.B[x] = Rs1.B[x] << sa;
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SLLI8(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("slli8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.101. SLLI8 ===== */

/* ===== Inline Function Start for 3.102. SLL16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_SHIFT
 * \brief SLL16 (SIMD 16-bit Shift Left Logical)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SLL16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit elements logical left shift operations simultaneously. The shift amount is a
 * variable from a GPR.
 *
 * **Description**:\n
 * The 16-bit elements in Rs1 are left-shifted logically. And the results are written to Rd.
 * The shifted out bits are filled with zero and the shift amount is specified by the low-order 4-bits of
 * the value in the Rs2 register.
 *
 * **Operations**:\n
 * ~~~
 * sa = Rs2[3:0];
 * Rd.H[x] = Rs1.H[x] << sa;
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SLL16(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("sll16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.102. SLL16 ===== */

/* ===== Inline Function Start for 3.103. SLLI16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_SHIFT
 * \brief SLLI16 (SIMD 16-bit Shift Left Logical Immediate)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SLLI16 Rd, Rs1, imm4[3:0]
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit element logical left shift operations simultaneously. The shift amount is an
 * immediate value.
 *
 * **Description**:\n
 * The 16-bit elements in Rs1 are left-shifted logically. The shifted out bits are filled with
 * zero and the shift amount is specified by the imm4[3:0] constant. And the results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * sa = imm4[3:0];
 * Rd.H[x] = Rs1.H[x] << sa;
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SLLI16(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("slli16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.103. SLLI16 ===== */

/* ===== Inline Function Start for 3.104. SMAL ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_64B_ADDSUB
 * \brief SMAL (Signed Multiply Halfs & Add 64-bit)
 * \details
 * **Type**: Partial-SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMAL Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed bottom 16-bit content of the 32-bit elements of a register with the top
 * 16-bit content of the same 32-bit elements of the same register, and add the results with a 64-bit
 * value of an even/odd pair of registers (RV32) or a register (RV64). The addition result is written back
 * to another even/odd pair of registers (RV32) or a register (RV64).
 *
 * **RV32 Description**:\n
 * This instruction multiplies the bottom 16-bit content of the lower 32-bit of Rs2 with the top 16-bit
 * content of the lower 32-bit of Rs2 and adds the result with the 64-bit value of an even/odd pair of
 * registers specified by Rs1(4,1). The 64-bit addition result is written back to an even/odd pair of
 * registers specified by Rd(4,1). The 16-bit values of Rs2, and the 64-bit value of the Rs1(4,1) register-
 * pair are treated as signed integers.
 * Rx(4,1), i.e., d, determines the even/odd pair group of the two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the operand and the even `2d`
 * register of the pair contains the low 32-bit of the operand.
 *
 * **RV64 Description**:\n
 * This instruction multiplies the bottom 16-bit content of the 32-bit elements of Rs2 with the top 16-bit
 * content of the same 32-bit elements of Rs2 and adds the results with the 64-bit value of Rs1. The 64-
 * bit addition result is written back to Rd. The 16-bit values of Rs2, and the 64-bit value of Rs1 are
 * treated as signed integers.
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 * Mres[31:0] = Rs2.H[1] * Rs2.H[0];
 * Idx0 = CONCAT(Rs1(4,1),1'b0); Idx1 = CONCAT(Rs1(4,1),1'b1); +
 * Idx2 = CONCAT(Rd(4,1),1'b0); Idx3 = CONCAT(Rd(4,1),1'b1);
 * R[Idx3].R[Idx2] = R[Idx1].R[Idx0] + SE64(Mres[31:0]);
 * RV64:
 * Mres[0][31:0] = Rs2.W[0].H[1] * Rs2.W[0].H[0];
 * Mres[1][31:0] = Rs2.W[1].H[1] * Rs2.W[1].H[0];
 * Rd = Rs1 + SE64(Mres[1][31:0]) + SE64(Mres[0][31:0]);
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_SMAL(long long a, unsigned long b)
{
    long long result;
    __ASM volatile("smal %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.104. SMAL ===== */

/* ===== Inline Function Start for 3.105.1. SMALBB ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_64B_ADDSUB
 * \brief SMALBB (Signed Multiply Bottom Halfs & Add 64-bit)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * SMALBB Rd, Rs1, Rs2
 * SMALBT Rd, Rs1, Rs2
 * SMALTT Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 16-bit content of the 32-bit elements of a register with the 16-bit
 * content of the corresponding 32-bit elements of another register and add the results with a 64-bit
 * value of an even/odd pair of registers (RV32) or a register (RV64). The addition result is written back
 * to the register-pair (RV32) or the register (RV64).
 * * SMALBB: rt pair + bottom*bottom (all 32-bit elements)
 * * SMALBT rt pair + bottom*top (all 32-bit elements)
 * * SMALTT rt pair + top*top (all 32-bit elements)
 *
 * **RV32 Description**:\n
 * For the `SMALBB` instruction, it multiplies the bottom 16-bit content of Rs1 with the bottom 16-bit
 * content of Rs2.
 * For the `SMALBT` instruction, it multiplies the bottom 16-bit content of Rs1 with the top 16-bit
 * content of Rs2.
 * For the `SMALTT` instruction, it multiplies the top 16-bit content of Rs1 with the top 16-bit content
 * of Rs2.
 * The multiplication result is added with the 64-bit value of an even/odd pair of registers specified by
 * Rd(4,1). The 64-bit addition result is written back to the register-pair. The 16-bit values of Rs1 and
 * Rs2, and the 64-bit value of the register-pair are treated as signed integers.
 * Rd(4,1), i.e., d, determines the even/odd pair group of the two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the operand and the even `2d`
 * register of the pair contains the low 32-bit of the operand.
 *
 * **RV64 Description**:\n
 * For the `SMALBB` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2.
 * For the `SMALBT` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the top 16-bit content of the 32-bit elements of Rs2.
 * For the `SMALTT` instruction, it multiplies the top 16-bit content of the 32-bit elements of Rs1 with
 * the top 16-bit content of the 32-bit elements of Rs2.
 * The multiplication results are added with the 64-bit value of Rd. The 64-bit addition result is written
 * back to Rd. The 16-bit values of Rs1 and Rs2, and the 64-bit value of Rd are treated as signed
 * integers.
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 * Mres[31:0] = Rs1.H[0] * Rs2.H[0]; // SMALBB
 * Mres[31:0] = Rs1.H[0] * Rs2.H[1]; // SMALBT
 * Mres[31:0] = Rs1.H[1] * Rs2.H[1]; // SMALTT
 * Idx0 = CONCAT(Rd(4,1),1'b0); Idx1 = CONCAT(Rd(4,1),1'b1);
 * R[Idx1].R[Idx0] = R[Idx1].R[Idx0] + SE64(Mres[31:0]);
 * RV64:
 * // SMALBB
 * Mres[0][31:0] = Rs1.W[0].H[0] * Rs2.W[0].H[0];
 * Mres[1][31:0] = Rs1.W[1].H[0] * Rs2.W[1].H[0];
 * // SMALBT
 * Mres[0][31:0] = Rs1.W[0].H[0] * Rs2.W[0].H[1];
 * Mres[1][31:0] = Rs1.W[1].H[0] * Rs2.W[1].H[1];
 * // SMALTT
 * Mres[0][31:0] = Rs1.W[0].H[1] * Rs2.W[0].H[1];
 * Mres[1][31:0] = Rs1.W[1].H[1] * Rs2.W[1].H[1];
 * Rd = Rd + SE64(Mres[0][31:0]) + SE64(Mres[1][31:0]);
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_SMALBB(long long t, unsigned long a, unsigned long b)
{
    __ASM volatile("smalbb %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.105.1. SMALBB ===== */

/* ===== Inline Function Start for 3.105.2. SMALBT ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_64B_ADDSUB
 * \brief SMALBT (Signed Multiply Bottom Half & Top Half & Add 64-bit)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * SMALBB Rd, Rs1, Rs2
 * SMALBT Rd, Rs1, Rs2
 * SMALTT Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 16-bit content of the 32-bit elements of a register with the 16-bit
 * content of the corresponding 32-bit elements of another register and add the results with a 64-bit
 * value of an even/odd pair of registers (RV32) or a register (RV64). The addition result is written back
 * to the register-pair (RV32) or the register (RV64).
 * * SMALBB: rt pair + bottom*bottom (all 32-bit elements)
 * * SMALBT rt pair + bottom*top (all 32-bit elements)
 * * SMALTT rt pair + top*top (all 32-bit elements)
 *
 * **RV32 Description**:\n
 * For the `SMALBB` instruction, it multiplies the bottom 16-bit content of Rs1 with the bottom 16-bit
 * content of Rs2.
 * For the `SMALBT` instruction, it multiplies the bottom 16-bit content of Rs1 with the top 16-bit
 * content of Rs2.
 * For the `SMALTT` instruction, it multiplies the top 16-bit content of Rs1 with the top 16-bit content
 * of Rs2.
 * The multiplication result is added with the 64-bit value of an even/odd pair of registers specified by
 * Rd(4,1). The 64-bit addition result is written back to the register-pair. The 16-bit values of Rs1 and
 * Rs2, and the 64-bit value of the register-pair are treated as signed integers.
 * Rd(4,1), i.e., d, determines the even/odd pair group of the two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the operand and the even `2d`
 * register of the pair contains the low 32-bit of the operand.
 *
 * **RV64 Description**:\n
 * For the `SMALBB` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2.
 * For the `SMALBT` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the top 16-bit content of the 32-bit elements of Rs2.
 * For the `SMALTT` instruction, it multiplies the top 16-bit content of the 32-bit elements of Rs1 with
 * the top 16-bit content of the 32-bit elements of Rs2.
 * The multiplication results are added with the 64-bit value of Rd. The 64-bit addition result is written
 * back to Rd. The 16-bit values of Rs1 and Rs2, and the 64-bit value of Rd are treated as signed
 * integers.
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 * Mres[31:0] = Rs1.H[0] * Rs2.H[0]; // SMALBB
 * Mres[31:0] = Rs1.H[0] * Rs2.H[1]; // SMALBT
 * Mres[31:0] = Rs1.H[1] * Rs2.H[1]; // SMALTT
 * Idx0 = CONCAT(Rd(4,1),1'b0); Idx1 = CONCAT(Rd(4,1),1'b1);
 * R[Idx1].R[Idx0] = R[Idx1].R[Idx0] + SE64(Mres[31:0]);
 * RV64:
 * // SMALBB
 * Mres[0][31:0] = Rs1.W[0].H[0] * Rs2.W[0].H[0];
 * Mres[1][31:0] = Rs1.W[1].H[0] * Rs2.W[1].H[0];
 * // SMALBT
 * Mres[0][31:0] = Rs1.W[0].H[0] * Rs2.W[0].H[1];
 * Mres[1][31:0] = Rs1.W[1].H[0] * Rs2.W[1].H[1];
 * // SMALTT
 * Mres[0][31:0] = Rs1.W[0].H[1] * Rs2.W[0].H[1];
 * Mres[1][31:0] = Rs1.W[1].H[1] * Rs2.W[1].H[1];
 * Rd = Rd + SE64(Mres[0][31:0]) + SE64(Mres[1][31:0]);
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_SMALBT(long long t, unsigned long a, unsigned long b)
{
    __ASM volatile("smalbt %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.105.2. SMALBT ===== */

/* ===== Inline Function Start for 3.105.3. SMALTT ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_64B_ADDSUB
 * \brief SMALTT (Signed Multiply Top Halfs & Add 64-bit)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * SMALBB Rd, Rs1, Rs2
 * SMALBT Rd, Rs1, Rs2
 * SMALTT Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 16-bit content of the 32-bit elements of a register with the 16-bit
 * content of the corresponding 32-bit elements of another register and add the results with a 64-bit
 * value of an even/odd pair of registers (RV32) or a register (RV64). The addition result is written back
 * to the register-pair (RV32) or the register (RV64).
 * * SMALBB: rt pair + bottom*bottom (all 32-bit elements)
 * * SMALBT rt pair + bottom*top (all 32-bit elements)
 * * SMALTT rt pair + top*top (all 32-bit elements)
 *
 * **RV32 Description**:\n
 * For the `SMALBB` instruction, it multiplies the bottom 16-bit content of Rs1 with the bottom 16-bit
 * content of Rs2.
 * For the `SMALBT` instruction, it multiplies the bottom 16-bit content of Rs1 with the top 16-bit
 * content of Rs2.
 * For the `SMALTT` instruction, it multiplies the top 16-bit content of Rs1 with the top 16-bit content
 * of Rs2.
 * The multiplication result is added with the 64-bit value of an even/odd pair of registers specified by
 * Rd(4,1). The 64-bit addition result is written back to the register-pair. The 16-bit values of Rs1 and
 * Rs2, and the 64-bit value of the register-pair are treated as signed integers.
 * Rd(4,1), i.e., d, determines the even/odd pair group of the two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the operand and the even `2d`
 * register of the pair contains the low 32-bit of the operand.
 *
 * **RV64 Description**:\n
 * For the `SMALBB` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2.
 * For the `SMALBT` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the top 16-bit content of the 32-bit elements of Rs2.
 * For the `SMALTT` instruction, it multiplies the top 16-bit content of the 32-bit elements of Rs1 with
 * the top 16-bit content of the 32-bit elements of Rs2.
 * The multiplication results are added with the 64-bit value of Rd. The 64-bit addition result is written
 * back to Rd. The 16-bit values of Rs1 and Rs2, and the 64-bit value of Rd are treated as signed
 * integers.
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 * Mres[31:0] = Rs1.H[0] * Rs2.H[0]; // SMALBB
 * Mres[31:0] = Rs1.H[0] * Rs2.H[1]; // SMALBT
 * Mres[31:0] = Rs1.H[1] * Rs2.H[1]; // SMALTT
 * Idx0 = CONCAT(Rd(4,1),1'b0); Idx1 = CONCAT(Rd(4,1),1'b1);
 * R[Idx1].R[Idx0] = R[Idx1].R[Idx0] + SE64(Mres[31:0]);
 * RV64:
 * // SMALBB
 * Mres[0][31:0] = Rs1.W[0].H[0] * Rs2.W[0].H[0];
 * Mres[1][31:0] = Rs1.W[1].H[0] * Rs2.W[1].H[0];
 * // SMALBT
 * Mres[0][31:0] = Rs1.W[0].H[0] * Rs2.W[0].H[1];
 * Mres[1][31:0] = Rs1.W[1].H[0] * Rs2.W[1].H[1];
 * // SMALTT
 * Mres[0][31:0] = Rs1.W[0].H[1] * Rs2.W[0].H[1];
 * Mres[1][31:0] = Rs1.W[1].H[1] * Rs2.W[1].H[1];
 * Rd = Rd + SE64(Mres[0][31:0]) + SE64(Mres[1][31:0]);
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_SMALTT(long long t, unsigned long a, unsigned long b)
{
    __ASM volatile("smaltt %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.105.3. SMALTT ===== */

/* ===== Inline Function Start for 3.106.1. SMALDA ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_64B_ADDSUB
 * \brief SMALDA (Signed Multiply Two Halfs and Two Adds 64-bit)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * SMALDA Rd, Rs1, Rs2
 * SMALXDA Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from the 32-bit elements of two registers; and then
 * adds the two 32-bit results and the 64-bit value of an even/odd pair of registers together.
 * * SMALDA: rt pair+ top*top + bottom*bottom (all 32-bit elements)
 * * SMALXDA: rt pair+ top*bottom + bottom*top (all 32-bit elements)
 *
 * **RV32 Description**:\n
 * For the `SMALDA` instruction, it multiplies the bottom 16-bit content of Rs1 with the bottom 16-bit
 * content of Rs2 and then adds the result to the result of multiplying the top 16-bit content of Rs1 with
 * the top 16-bit content of Rs2 with unlimited precision.
 * For the `SMALXDA` instruction, it multiplies the top 16-bit content of Rs1 with the bottom 16-bit
 * content of Rs2 and then adds the result to the result of multiplying the bottom 16-bit content of Rs1
 * with the top 16-bit content of Rs2 with unlimited precision.
 * The result is added to the 64-bit value of an even/odd pair of registers specified by Rd(4,1). The 64-
 * bit addition result is written back to the register-pair. The 16-bit values of Rs1 and Rs2, and the 64-
 * bit value of the register-pair are treated as signed integers.
 * Rd(4,1), i.e., d, determines the even/odd pair group of the two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the operand and the even `2d`
 * register of the pair contains the low 32-bit of the operand.
 *
 * **RV64 Description**:\n
 * For the `SMALDA` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2 and then adds the result to the result of
 * multiplying the top 16-bit content of the 32-bit elements of Rs1 with the top 16-bit content of the 32-
 * bit elements of Rs2 with unlimited precision.
 * For the `SMALXDA` instruction, it multiplies the top 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2 and then adds the result to the result of
 * multiplying the bottom 16-bit content of the 32-bit elements of Rs1 with the top 16-bit content of the
 * 32-bit elements of Rs2 with unlimited precision.
 * The results are added to the 64-bit value of Rd. The 64-bit addition result is written back to Rd. The
 * 16-bit values of Rs1 and Rs2, and the 64-bit value of Rd are treated as signed integers.
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 * // SMALDA
 * Mres0[31:0] = (Rs1.H[0] * Rs2.H[0]);
 * Mres1[31:0] = (Rs1.H[1] * Rs2.H[1]);
 * // SMALXDA
 * Mres0[31:0] = (Rs1.H[0] * Rs2.H[1]);
 * Mres1[31:0] = (Rs1.H[1] * Rs2.H[0]);
 * Idx0 = CONCAT(Rd(4,1),1'b0); Idx1 = CONCAT(Rd(4,1),1'b1);
 * R[Idx1].R[Idx0] = R[Idx1].R[Idx0] + SE64(Mres0[31:0]) + SE64(Mres1[31:0]);
 * RV64:
 * // SMALDA
 * Mres0[0][31:0] = (Rs1.W[0].H[0] * Rs2.W[0].H[0]);
 * Mres1[0][31:0] = (Rs1.W[0].H[1] * Rs2.W[0].H[1]);
 * Mres0[1][31:0] = (Rs1.W[1].H[0] * Rs2.W[1].H[0]);
 * Mres1[1][31:0] = (Rs1.W[1].H[1] * Rs2.W[1].H[1]);
 * // SMALXDA
 * Mres0[0][31:0] = (Rs1.W[0].H[0] * Rs2.W[0].H[1]);
 * Mres1[0][31:0] = (Rs1.W[0].H[1] * Rs2.W[0].H[0]);
 * Mres0[1][31:0] = (Rs1.W[1].H[0] * Rs2.W[1].H[1]);
 * Mres1[1][31:0] = (Rs1.W[1].H[1] * Rs2.W[1].H[0]);
 * Rd = Rd + SE64(Mres0[0][31:0]) + SE64(Mres1[0][31:0]) + SE64(Mres0[1][31:0]) +
 * SE64(Mres1[1][31:0]);
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_SMALDA(long long t, unsigned long a, unsigned long b)
{
    __ASM volatile("smalda %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.106.1. SMALDA ===== */

/* ===== Inline Function Start for 3.106.2. SMALXDA ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_64B_ADDSUB
 * \brief SMALXDA (Signed Crossed Multiply Two Halfs and Two Adds 64-bit)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * SMALDA Rd, Rs1, Rs2
 * SMALXDA Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from the 32-bit elements of two registers; and then
 * adds the two 32-bit results and the 64-bit value of an even/odd pair of registers together.
 * * SMALDA: rt pair+ top*top + bottom*bottom (all 32-bit elements)
 * * SMALXDA: rt pair+ top*bottom + bottom*top (all 32-bit elements)
 *
 * **RV32 Description**:\n
 * For the `SMALDA` instruction, it multiplies the bottom 16-bit content of Rs1 with the bottom 16-bit
 * content of Rs2 and then adds the result to the result of multiplying the top 16-bit content of Rs1 with
 * the top 16-bit content of Rs2 with unlimited precision.
 * For the `SMALXDA` instruction, it multiplies the top 16-bit content of Rs1 with the bottom 16-bit
 * content of Rs2 and then adds the result to the result of multiplying the bottom 16-bit content of Rs1
 * with the top 16-bit content of Rs2 with unlimited precision.
 * The result is added to the 64-bit value of an even/odd pair of registers specified by Rd(4,1). The 64-
 * bit addition result is written back to the register-pair. The 16-bit values of Rs1 and Rs2, and the 64-
 * bit value of the register-pair are treated as signed integers.
 * Rd(4,1), i.e., d, determines the even/odd pair group of the two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the operand and the even `2d`
 * register of the pair contains the low 32-bit of the operand.
 *
 * **RV64 Description**:\n
 * For the `SMALDA` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2 and then adds the result to the result of
 * multiplying the top 16-bit content of the 32-bit elements of Rs1 with the top 16-bit content of the 32-
 * bit elements of Rs2 with unlimited precision.
 * For the `SMALXDA` instruction, it multiplies the top 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2 and then adds the result to the result of
 * multiplying the bottom 16-bit content of the 32-bit elements of Rs1 with the top 16-bit content of the
 * 32-bit elements of Rs2 with unlimited precision.
 * The results are added to the 64-bit value of Rd. The 64-bit addition result is written back to Rd. The
 * 16-bit values of Rs1 and Rs2, and the 64-bit value of Rd are treated as signed integers.
 *
 * **Operations**:\n
 * ~~~
 * RV32:
 * // SMALDA
 * Mres0[31:0] = (Rs1.H[0] * Rs2.H[0]);
 * Mres1[31:0] = (Rs1.H[1] * Rs2.H[1]);
 * // SMALXDA
 * Mres0[31:0] = (Rs1.H[0] * Rs2.H[1]);
 * Mres1[31:0] = (Rs1.H[1] * Rs2.H[0]);
 * Idx0 = CONCAT(Rd(4,1),1'b0); Idx1 = CONCAT(Rd(4,1),1'b1);
 * R[Idx1].R[Idx0] = R[Idx1].R[Idx0] + SE64(Mres0[31:0]) + SE64(Mres1[31:0]);
 * RV64:
 * // SMALDA
 * Mres0[0][31:0] = (Rs1.W[0].H[0] * Rs2.W[0].H[0]);
 * Mres1[0][31:0] = (Rs1.W[0].H[1] * Rs2.W[0].H[1]);
 * Mres0[1][31:0] = (Rs1.W[1].H[0] * Rs2.W[1].H[0]);
 * Mres1[1][31:0] = (Rs1.W[1].H[1] * Rs2.W[1].H[1]);
 * // SMALXDA
 * Mres0[0][31:0] = (Rs1.W[0].H[0] * Rs2.W[0].H[1]);
 * Mres1[0][31:0] = (Rs1.W[0].H[1] * Rs2.W[0].H[0]);
 * Mres0[1][31:0] = (Rs1.W[1].H[0] * Rs2.W[1].H[1]);
 * Mres1[1][31:0] = (Rs1.W[1].H[1] * Rs2.W[1].H[0]);
 * Rd = Rd + SE64(Mres0[0][31:0]) + SE64(Mres1[0][31:0]) + SE64(Mres0[1][31:0]) +
 * SE64(Mres1[1][31:0]);
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_SMALXDA(long long t, unsigned long a, unsigned long b)
{
    __ASM volatile("smalxda %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.106.2. SMALXDA ===== */

/* ===== Inline Function Start for 3.107.1. SMALDS ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_64B_ADDSUB
 * \brief SMALDS (Signed Multiply Two Halfs & Subtract & Add 64-bit)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * SMALDS Rd, Rs1, Rs2
 * SMALDRS Rd, Rs1, Rs2
 * SMALXDS Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from the 32-bit elements of two registers; and then
 * perform a subtraction operation between the two 32-bit results. Then add the subtraction result to
 * the 64-bit value of an even/odd pair of registers (RV32) or a register (RV64). The addition result is
 * written back to the register-pair.
 * * SMALDS: rt pair + (top*top - bottom*bottom) (all 32-bit elements)
 * * SMALDRS: rt pair + (bottom*bottom - top*top) (all 32-bit elements)
 * * SMALXDS: rt pair + (top*bottom - bottom*top) (all 32-bit elements)
 *
 * **RV32 Description**:\n
 * For the `SMALDS` instruction, it multiplies the bottom 16-bit content of Rs1 with the bottom 16-bit
 * content of Rs2 and then subtracts the result from the result of multiplying the top 16-bit content of
 * Rs1 with the top 16-bit content of Rs2.
 * For the `SMALDRS` instruction, it multiplies the top 16-bit content of Rs1 with the top 16-bit content
 * of Rs2 and then subtracts the result from the result of multiplying the bottom 16-bit content of Rs1
 * with the bottom 16-bit content of Rs2.
 * For the `SMALXDS` instruction, it multiplies the bottom 16-bit content of Rs1 with the top 16-bit
 * content of Rs2 and then subtracts the result from the result of multiplying the top 16-bit content of
 * Rs1 with the bottom 16-bit content of Rs2.
 * The subtraction result is then added to the 64-bit value of an even/odd pair of registers specified by
 * Rd(4,1). The 64-bit addition result is written back to the register-pair. The 16-bit values of Rs1 and
 * Rs2, and the 64-bit value of the register-pair are treated as signed integers.
 * Rd(4,1), i.e., d, determines the even/odd pair group of the two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the operand and the even `2d`
 * register of the pair contains the low 32-bit of the operand.
 *
 * **RV64 Description**:\n
 * For the `SMALDS` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2 and then subtracts the result from the
 * result of multiplying the top 16-bit content of the 32-bit elements of Rs1 with the top 16-bit content
 * of the 32-bit elements of Rs2.
 * For the `SMALDRS` instruction, it multiplies the top 16-bit content of the 32-bit elements of Rs1 with
 * the top 16-bit content of the 32-bit elements of Rs2 and then subtracts the result from the result of
 * multiplying the bottom 16-bit content of the 32-bit elements of Rs1 with the bottom 16-bit content of
 * the 32-bit elements of Rs2.
 * For the `SMALXDS` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the top 16-bit content of the 32-bit elements of Rs2 and then subtracts the result from the
 * result of multiplying the top 16-bit content of the 32-bit elements of Rs1 with the bottom 16-bit
 * content of the 32-bit elements of Rs2.
 * The subtraction results are then added to the 64-bit value of Rd. The 64-bit addition result is written
 * back to Rd. The 16-bit values of Rs1 and Rs2, and the 64-bit value of Rd are treated as signed
 * integers.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * Mres[31:0] = (Rs1.H[1] * Rs2.H[1]) - (Rs1.H[0] * Rs2.H[0]); // SMALDS
 * Mres[31:0] = (Rs1.H[0] * Rs2.H[0]) - (Rs1.H[1] * Rs2.H[1]); // SMALDRS
 * Mres[31:0] = (Rs1.H[1] * Rs2.H[0]) - (Rs1.H[0] * Rs2.H[1]); // SMALXDS
 * Idx0 = CONCAT(Rd(4,1),1'b0); Idx1 = CONCAT(Rd(4,1),1'b1);
 * R[Idx1].R[Idx0] = R[Idx1].R[Idx0] + SE64(Mres[31:0]);
 * * RV64:
 * // SMALDS
 * Mres[0][31:0] = (Rs1.W[0].H[1] * Rs2.W[0].H[1]) - (Rs1.W[0].H[0] * Rs2.W[0].H[0]);
 * Mres[1][31:0] = (Rs1.W[1].H[1] * Rs2.W[0].H[1]) - (Rs1.W[1].H[0] * Rs2.W[1].H[0]);
 * // SMALDRS
 * Mres[0][31:0] = (Rs1.W[0].H[0] * Rs2.W[0].H[0]) - (Rs1.W[0].H[1] * Rs2.W[0].H[1]);
 * Mres[1][31:0] = (Rs1.W[1].H[0] * Rs2.W[0].H[0]) - (Rs1.W[1].H[1] * Rs2.W[1].H[1]);
 * // SMALXDS
 * Mres[0][31:0] = (Rs1.W[0].H[1] * Rs2.W[0].H[0]) - (Rs1.W[0].H[0] * Rs2.W[0].H[1]);
 * Mres[1][31:0] = (Rs1.W[1].H[1] * Rs2.W[0].H[0]) - (Rs1.W[1].H[0] * Rs2.W[1].H[1]);
 * Rd = Rd + SE64(Mres[0][31:0]) + SE64(Mres[1][31:0]);
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_SMALDS(long long t, unsigned long a, unsigned long b)
{
    __ASM volatile("smalds %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.107.1. SMALDS ===== */

/* ===== Inline Function Start for 3.107.2. SMALDRS ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_64B_ADDSUB
 * \brief SMALDRS (Signed Multiply Two Halfs & Reverse Subtract & Add 64- bit)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * SMALDS Rd, Rs1, Rs2
 * SMALDRS Rd, Rs1, Rs2
 * SMALXDS Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from the 32-bit elements of two registers; and then
 * perform a subtraction operation between the two 32-bit results. Then add the subtraction result to
 * the 64-bit value of an even/odd pair of registers (RV32) or a register (RV64). The addition result is
 * written back to the register-pair.
 * * SMALDS: rt pair + (top*top - bottom*bottom) (all 32-bit elements)
 * * SMALDRS: rt pair + (bottom*bottom - top*top) (all 32-bit elements)
 * * SMALXDS: rt pair + (top*bottom - bottom*top) (all 32-bit elements)
 *
 * **RV32 Description**:\n
 * For the `SMALDS` instruction, it multiplies the bottom 16-bit content of Rs1 with the bottom 16-bit
 * content of Rs2 and then subtracts the result from the result of multiplying the top 16-bit content of
 * Rs1 with the top 16-bit content of Rs2.
 * For the `SMALDRS` instruction, it multiplies the top 16-bit content of Rs1 with the top 16-bit content
 * of Rs2 and then subtracts the result from the result of multiplying the bottom 16-bit content of Rs1
 * with the bottom 16-bit content of Rs2.
 * For the `SMALXDS` instruction, it multiplies the bottom 16-bit content of Rs1 with the top 16-bit
 * content of Rs2 and then subtracts the result from the result of multiplying the top 16-bit content of
 * Rs1 with the bottom 16-bit content of Rs2.
 * The subtraction result is then added to the 64-bit value of an even/odd pair of registers specified by
 * Rd(4,1). The 64-bit addition result is written back to the register-pair. The 16-bit values of Rs1 and
 * Rs2, and the 64-bit value of the register-pair are treated as signed integers.
 * Rd(4,1), i.e., d, determines the even/odd pair group of the two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the operand and the even `2d`
 * register of the pair contains the low 32-bit of the operand.
 *
 * **RV64 Description**:\n
 * For the `SMALDS` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2 and then subtracts the result from the
 * result of multiplying the top 16-bit content of the 32-bit elements of Rs1 with the top 16-bit content
 * of the 32-bit elements of Rs2.
 * For the `SMALDRS` instruction, it multiplies the top 16-bit content of the 32-bit elements of Rs1 with
 * the top 16-bit content of the 32-bit elements of Rs2 and then subtracts the result from the result of
 * multiplying the bottom 16-bit content of the 32-bit elements of Rs1 with the bottom 16-bit content of
 * the 32-bit elements of Rs2.
 * For the `SMALXDS` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the top 16-bit content of the 32-bit elements of Rs2 and then subtracts the result from the
 * result of multiplying the top 16-bit content of the 32-bit elements of Rs1 with the bottom 16-bit
 * content of the 32-bit elements of Rs2.
 * The subtraction results are then added to the 64-bit value of Rd. The 64-bit addition result is written
 * back to Rd. The 16-bit values of Rs1 and Rs2, and the 64-bit value of Rd are treated as signed
 * integers.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * Mres[31:0] = (Rs1.H[1] * Rs2.H[1]) - (Rs1.H[0] * Rs2.H[0]); // SMALDS
 * Mres[31:0] = (Rs1.H[0] * Rs2.H[0]) - (Rs1.H[1] * Rs2.H[1]); // SMALDRS
 * Mres[31:0] = (Rs1.H[1] * Rs2.H[0]) - (Rs1.H[0] * Rs2.H[1]); // SMALXDS
 * Idx0 = CONCAT(Rd(4,1),1'b0); Idx1 = CONCAT(Rd(4,1),1'b1);
 * R[Idx1].R[Idx0] = R[Idx1].R[Idx0] + SE64(Mres[31:0]);
 * * RV64:
 * // SMALDS
 * Mres[0][31:0] = (Rs1.W[0].H[1] * Rs2.W[0].H[1]) - (Rs1.W[0].H[0] * Rs2.W[0].H[0]);
 * Mres[1][31:0] = (Rs1.W[1].H[1] * Rs2.W[0].H[1]) - (Rs1.W[1].H[0] * Rs2.W[1].H[0]);
 * // SMALDRS
 * Mres[0][31:0] = (Rs1.W[0].H[0] * Rs2.W[0].H[0]) - (Rs1.W[0].H[1] * Rs2.W[0].H[1]);
 * Mres[1][31:0] = (Rs1.W[1].H[0] * Rs2.W[0].H[0]) - (Rs1.W[1].H[1] * Rs2.W[1].H[1]);
 * // SMALXDS
 * Mres[0][31:0] = (Rs1.W[0].H[1] * Rs2.W[0].H[0]) - (Rs1.W[0].H[0] * Rs2.W[0].H[1]);
 * Mres[1][31:0] = (Rs1.W[1].H[1] * Rs2.W[0].H[0]) - (Rs1.W[1].H[0] * Rs2.W[1].H[1]);
 * Rd = Rd + SE64(Mres[0][31:0]) + SE64(Mres[1][31:0]);
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_SMALDRS(long long t, unsigned long a, unsigned long b)
{
    __ASM volatile("smaldrs %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.107.2. SMALDRS ===== */

/* ===== Inline Function Start for 3.107.3. SMALXDS ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_64B_ADDSUB
 * \brief SMALXDS (Signed Crossed Multiply Two Halfs & Subtract & Add 64- bit)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * SMALDS Rd, Rs1, Rs2
 * SMALDRS Rd, Rs1, Rs2
 * SMALXDS Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from the 32-bit elements of two registers; and then
 * perform a subtraction operation between the two 32-bit results. Then add the subtraction result to
 * the 64-bit value of an even/odd pair of registers (RV32) or a register (RV64). The addition result is
 * written back to the register-pair.
 * * SMALDS: rt pair + (top*top - bottom*bottom) (all 32-bit elements)
 * * SMALDRS: rt pair + (bottom*bottom - top*top) (all 32-bit elements)
 * * SMALXDS: rt pair + (top*bottom - bottom*top) (all 32-bit elements)
 *
 * **RV32 Description**:\n
 * For the `SMALDS` instruction, it multiplies the bottom 16-bit content of Rs1 with the bottom 16-bit
 * content of Rs2 and then subtracts the result from the result of multiplying the top 16-bit content of
 * Rs1 with the top 16-bit content of Rs2.
 * For the `SMALDRS` instruction, it multiplies the top 16-bit content of Rs1 with the top 16-bit content
 * of Rs2 and then subtracts the result from the result of multiplying the bottom 16-bit content of Rs1
 * with the bottom 16-bit content of Rs2.
 * For the `SMALXDS` instruction, it multiplies the bottom 16-bit content of Rs1 with the top 16-bit
 * content of Rs2 and then subtracts the result from the result of multiplying the top 16-bit content of
 * Rs1 with the bottom 16-bit content of Rs2.
 * The subtraction result is then added to the 64-bit value of an even/odd pair of registers specified by
 * Rd(4,1). The 64-bit addition result is written back to the register-pair. The 16-bit values of Rs1 and
 * Rs2, and the 64-bit value of the register-pair are treated as signed integers.
 * Rd(4,1), i.e., d, determines the even/odd pair group of the two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the operand and the even `2d`
 * register of the pair contains the low 32-bit of the operand.
 *
 * **RV64 Description**:\n
 * For the `SMALDS` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2 and then subtracts the result from the
 * result of multiplying the top 16-bit content of the 32-bit elements of Rs1 with the top 16-bit content
 * of the 32-bit elements of Rs2.
 * For the `SMALDRS` instruction, it multiplies the top 16-bit content of the 32-bit elements of Rs1 with
 * the top 16-bit content of the 32-bit elements of Rs2 and then subtracts the result from the result of
 * multiplying the bottom 16-bit content of the 32-bit elements of Rs1 with the bottom 16-bit content of
 * the 32-bit elements of Rs2.
 * For the `SMALXDS` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the top 16-bit content of the 32-bit elements of Rs2 and then subtracts the result from the
 * result of multiplying the top 16-bit content of the 32-bit elements of Rs1 with the bottom 16-bit
 * content of the 32-bit elements of Rs2.
 * The subtraction results are then added to the 64-bit value of Rd. The 64-bit addition result is written
 * back to Rd. The 16-bit values of Rs1 and Rs2, and the 64-bit value of Rd are treated as signed
 * integers.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * Mres[31:0] = (Rs1.H[1] * Rs2.H[1]) - (Rs1.H[0] * Rs2.H[0]); // SMALDS
 * Mres[31:0] = (Rs1.H[0] * Rs2.H[0]) - (Rs1.H[1] * Rs2.H[1]); // SMALDRS
 * Mres[31:0] = (Rs1.H[1] * Rs2.H[0]) - (Rs1.H[0] * Rs2.H[1]); // SMALXDS
 * Idx0 = CONCAT(Rd(4,1),1'b0); Idx1 = CONCAT(Rd(4,1),1'b1);
 * R[Idx1].R[Idx0] = R[Idx1].R[Idx0] + SE64(Mres[31:0]);
 * * RV64:
 * // SMALDS
 * Mres[0][31:0] = (Rs1.W[0].H[1] * Rs2.W[0].H[1]) - (Rs1.W[0].H[0] * Rs2.W[0].H[0]);
 * Mres[1][31:0] = (Rs1.W[1].H[1] * Rs2.W[0].H[1]) - (Rs1.W[1].H[0] * Rs2.W[1].H[0]);
 * // SMALDRS
 * Mres[0][31:0] = (Rs1.W[0].H[0] * Rs2.W[0].H[0]) - (Rs1.W[0].H[1] * Rs2.W[0].H[1]);
 * Mres[1][31:0] = (Rs1.W[1].H[0] * Rs2.W[0].H[0]) - (Rs1.W[1].H[1] * Rs2.W[1].H[1]);
 * // SMALXDS
 * Mres[0][31:0] = (Rs1.W[0].H[1] * Rs2.W[0].H[0]) - (Rs1.W[0].H[0] * Rs2.W[0].H[1]);
 * Mres[1][31:0] = (Rs1.W[1].H[1] * Rs2.W[0].H[0]) - (Rs1.W[1].H[0] * Rs2.W[1].H[1]);
 * Rd = Rd + SE64(Mres[0][31:0]) + SE64(Mres[1][31:0]);
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_SMALXDS(long long t, unsigned long a, unsigned long b)
{
    __ASM volatile("smalxds %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.107.3. SMALXDS ===== */

/* ===== Inline Function Start for 3.108. SMAR64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_32B_MULT_64B_ADDSUB
 * \brief SMAR64 (Signed Multiply and Add to 64-Bit Data)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * SMAR64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the 32-bit signed elements in two registers and add the 64-bit multiplication
 * result to the 64-bit signed data of a pair of registers (RV32) or a register (RV64). The result is written
 * back to the pair of registers (RV32) or a register (RV64).
 *
 * **RV32 Description**:\n
 * This instruction multiplies the 32-bit signed data of Rs1 with that of Rs2. It adds
 * the 64-bit multiplication result to the 64-bit signed data of an even/odd pair of registers specified by
 * Rd(4,1). The addition result is written back to the even/odd pair of registers specified by Rd(4,1).
 * Rx(4,1), i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 *
 * **RV64 Description**:\n
 * This instruction multiplies the 32-bit signed elements of Rs1 with that of Rs2. It
 * adds the 64-bit multiplication results to the 64-bit signed data of Rd. The addition result is written
 * back to Rd.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * R[t_H].R[t_L] = R[t_H].R[t_L] + (Rs1 * Rs2);
 * * RV64:
 * Rd = Rd + (Rs1.W[0] * Rs2.W[0]) + (Rs1.W[1] * Rs2.W[1]);
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_SMAR64(long long t, long a, long b)
{
    __ASM volatile("smar64 %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.108. SMAR64 ===== */

/* ===== Inline Function Start for 3.109. SMAQA ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_8B_MULT_32B_ADD
 * \brief SMAQA (Signed Multiply Four Bytes with 32-bit Adds)
 * \details
 * **Type**: Partial-SIMD (Reduction)
 *
 * **Syntax**:\n
 * ~~~
 * SMAQA Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do four signed 8-bit multiplications from 32-bit chunks of two registers; and then adds
 * the four 16-bit results and the content of corresponding 32-bit chunks of a third register together.
 *
 * **Description**:\n
 * This instruction multiplies the four signed 8-bit elements of 32-bit chunks of Rs1 with the four
 * signed 8-bit elements of 32-bit chunks of Rs2 and then adds the four results together with the signed
 * content of the corresponding 32-bit chunks of Rd. The final results are written back to the
 * corresponding 32-bit chunks in Rd.
 *
 * **Operations**:\n
 * ~~~
 * res[x] = Rd.W[x] +
 *    (Rs1.W[x].B[3] s* Rs2.W[x].B[3]) + (Rs1.W[x].B[2] s* Rs2.W[x].B[2]) +
 *    (Rs1.W[x].B[1] s* Rs2.W[x].B[1]) + (Rs1.W[x].B[0] s* Rs2.W[x].B[0]);
 * Rd.W[x] = res[x];
 * for RV32: x=0,
 * for RV64: x=1,0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_SMAQA(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("smaqa %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.109. SMAQA ===== */

/* ===== Inline Function Start for 3.110. SMAQA.SU ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_8B_MULT_32B_ADD
 * \brief SMAQA.SU (Signed and Unsigned Multiply Four Bytes with 32-bit Adds)
 * \details
 * **Type**: Partial-SIMD (Reduction)
 *
 * **Syntax**:\n
 * ~~~
 * SMAQA.SU Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do four `signed x unsigned` 8-bit multiplications from 32-bit chunks of two registers; and
 * then adds the four 16-bit results and the content of corresponding 32-bit chunks of a third register
 * together.
 *
 * **Description**:\n
 * This instruction multiplies the four signed 8-bit elements of 32-bit chunks of Rs1 with the four
 * unsigned 8-bit elements of 32-bit chunks of Rs2 and then adds the four results together with the
 * signed content of the corresponding 32-bit chunks of Rd. The final results are written back to the
 * corresponding 32-bit chunks in Rd.
 *
 * **Operations**:\n
 * ~~~
 * res[x] = Rd.W[x] +
 *    (Rs1.W[x].B[3] su* Rs2.W[x].B[3]) + (Rs1.W[x].B[2] su* Rs2.W[x].B[2]) +
 *    (Rs1.W[x].B[1] su* Rs2.W[x].B[1]) + (Rs1.W[x].B[0] su* Rs2.W[x].B[0]);
 * Rd.W[x] = res[x];
 * for RV32: x=0,
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_SMAQA_SU(long t, unsigned long a, unsigned long b)
{
    __ASM volatile("smaqa.su %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.110. SMAQA.SU ===== */

/* ===== Inline Function Start for 3.111. SMAX8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_MISC
 * \brief SMAX8 (SIMD 8-bit Signed Maximum)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMAX8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit signed integer elements finding maximum operations simultaneously.
 *
 * **Description**:\n
 * This instruction compares the 8-bit signed integer elements in Rs1 with the 8-bit
 * signed integer elements in Rs2 and selects the numbers that is greater than the other one. The
 * selected results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.B[x] = (Rs1.B[x] > Rs2.B[x])? Rs1.B[x] : Rs2.B[x];
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SMAX8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("smax8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.111. SMAX8 ===== */

/* ===== Inline Function Start for 3.112. SMAX16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_MISC
 * \brief SMAX16 (SIMD 16-bit Signed Maximum)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMAX16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit signed integer elements finding maximum operations simultaneously.
 *
 * **Description**:\n
 * This instruction compares the 16-bit signed integer elements in Rs1 with the 16-bit
 * signed integer elements in Rs2 and selects the numbers that is greater than the other one. The
 * selected results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.H[x] = (Rs1.H[x] > Rs2.H[x])? Rs1.H[x] : Rs2.H[x];
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SMAX16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("smax16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.112. SMAX16 ===== */

/* ===== Inline Function Start for 3.113.1. SMBB16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB
 * \brief SMBB16 (SIMD Signed Multiply Bottom Half & Bottom Half)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMBB16 Rd, Rs1, Rs2
 * SMBT16 Rd, Rs1, Rs2
 * SMTT16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 16-bit content of the 32-bit elements of a register with the signed 16-
 * bit content of the 32-bit elements of another register and write the result to a third register.
 * * SMBB16: W[x].bottom*W[x].bottom
 * * SMBT16: W[x].bottom *W[x].top
 * * SMTT16: W[x].top * W[x].top
 *
 * **Description**:\n
 * For the `SMBB16` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2.
 * For the `SMBT16` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the top 16-bit content of the 32-bit elements of Rs2.
 * For the `SMTT16` instruction, it multiplies the top 16-bit content of the 32-bit elements of Rs1 with
 * the top 16-bit content of the 32-bit elements of Rs2.
 * The multiplication results are written to Rd. The 16-bit contents of Rs1 and Rs2 are treated as signed
 * integers.
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x] = Rs1.W[x].H[0] * Rs2.W[x].H[0]; // SMBB16
 * Rd.W[x] = Rs1.W[x].H[0] * Rs2.W[x].H[1]; // SMBT16
 * Rd.W[x] = Rs1.W[x].H[1] * Rs2.W[x].H[1]; // SMTT16
 * for RV32: x=0,
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_SMBB16(unsigned long a, unsigned long b)
{
    long result;
    __ASM volatile("smbb16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.113.1. SMBB16 ===== */

/* ===== Inline Function Start for 3.113.2. SMBT16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB
 * \brief SMBT16 (SIMD Signed Multiply Bottom Half & Top Half)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMBB16 Rd, Rs1, Rs2
 * SMBT16 Rd, Rs1, Rs2
 * SMTT16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 16-bit content of the 32-bit elements of a register with the signed 16-
 * bit content of the 32-bit elements of another register and write the result to a third register.
 * * SMBB16: W[x].bottom*W[x].bottom
 * * SMBT16: W[x].bottom *W[x].top
 * * SMTT16: W[x].top * W[x].top
 *
 * **Description**:\n
 * For the `SMBB16` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2.
 * For the `SMBT16` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the top 16-bit content of the 32-bit elements of Rs2.
 * For the `SMTT16` instruction, it multiplies the top 16-bit content of the 32-bit elements of Rs1 with
 * the top 16-bit content of the 32-bit elements of Rs2.
 * The multiplication results are written to Rd. The 16-bit contents of Rs1 and Rs2 are treated as signed
 * integers.
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x] = Rs1.W[x].H[0] * Rs2.W[x].H[0]; // SMBB16
 * Rd.W[x] = Rs1.W[x].H[0] * Rs2.W[x].H[1]; // SMBT16
 * Rd.W[x] = Rs1.W[x].H[1] * Rs2.W[x].H[1]; // SMTT16
 * for RV32: x=0,
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_SMBT16(unsigned long a, unsigned long b)
{
    long result;
    __ASM volatile("smbt16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.113.2. SMBT16 ===== */

/* ===== Inline Function Start for 3.113.3. SMTT16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB
 * \brief SMTT16 (SIMD Signed Multiply Top Half & Top Half)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMBB16 Rd, Rs1, Rs2
 * SMBT16 Rd, Rs1, Rs2
 * SMTT16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 16-bit content of the 32-bit elements of a register with the signed 16-
 * bit content of the 32-bit elements of another register and write the result to a third register.
 * * SMBB16: W[x].bottom*W[x].bottom
 * * SMBT16: W[x].bottom *W[x].top
 * * SMTT16: W[x].top * W[x].top
 *
 * **Description**:\n
 * For the `SMBB16` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2.
 * For the `SMBT16` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the top 16-bit content of the 32-bit elements of Rs2.
 * For the `SMTT16` instruction, it multiplies the top 16-bit content of the 32-bit elements of Rs1 with
 * the top 16-bit content of the 32-bit elements of Rs2.
 * The multiplication results are written to Rd. The 16-bit contents of Rs1 and Rs2 are treated as signed
 * integers.
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x] = Rs1.W[x].H[0] * Rs2.W[x].H[0]; // SMBB16
 * Rd.W[x] = Rs1.W[x].H[0] * Rs2.W[x].H[1]; // SMBT16
 * Rd.W[x] = Rs1.W[x].H[1] * Rs2.W[x].H[1]; // SMTT16
 * for RV32: x=0,
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_SMTT16(unsigned long a, unsigned long b)
{
    long result;
    __ASM volatile("smtt16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.113.3. SMTT16 ===== */

/* ===== Inline Function Start for 3.114.1. SMDS ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB
 * \brief SMDS (SIMD Signed Multiply Two Halfs and Subtract)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMDS Rd, Rs1, Rs2
 * SMDRS Rd, Rs1, Rs2
 * SMXDS Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from the 32-bit elements of two registers; and then
 * perform a subtraction operation between the two 32-bit results.
 * * SMDS: top*top - bottom*bottom (per 32-bit element)
 * * SMDRS: bottom*bottom - top*top (per 32-bit element)
 * * SMXDS: top*bottom - bottom*top (per 32-bit element)
 *
 * **Description**:\n
 * For the `SMDS` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1 with
 * the bottom 16-bit content of the 32-bit elements of Rs2 and then subtracts the result from the result
 * of multiplying the top 16-bit content of the 32-bit elements of Rs1 with the top 16-bit content of the
 * 32-bit elements of Rs2.
 * For the `SMDRS` instruction, it multiplies the top 16-bit content of the 32-bit elements of Rs1 with
 * the top 16-bit content of the 32-bit elements of Rs2 and then subtracts the result from the result of
 * multiplying the bottom 16-bit content of the 32-bit elements of Rs1 with the bottom 16-bit content of
 * the 32-bit elements of Rs2.
 * For the `SMXDS` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the top 16-bit content of the 32-bit elements of Rs2 and then subtracts the result from the
 * result of multiplying the top 16-bit content of the 32-bit elements of Rs1 with the bottom 16-bit
 * content of the 32-bit elements of Rs2.
 * The subtraction result is written to the corresponding 32-bit element of Rd. The 16-bit contents of
 * multiplication are treated as signed integers.
 *
 * **Operations**:\n
 * ~~~
 * * SMDS:
 * Rd.W[x] = (Rs1.W[x].H[1] * Rs2.W[x].H[1]) - (Rs1.W[x].H[0] * Rs2.W[x].H[0]);
 * * SMDRS:
 * Rd.W[x] = (Rs1.W[x].H[0] * Rs2.W[x].H[0]) - (Rs1.W[x].H[1] * Rs2.W[x].H[1]);
 * * SMXDS:
 * Rd.W[x] = (Rs1.W[x].H[1] * Rs2.W[x].H[0]) - (Rs1.W[x].H[0] * Rs2.W[x].H[1]);
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_SMDS(unsigned long a, unsigned long b)
{
    long result;
    __ASM volatile("smds %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.114.1. SMDS ===== */

/* ===== Inline Function Start for 3.114.2. SMDRS ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB
 * \brief SMDRS (SIMD Signed Multiply Two Halfs and Reverse Subtract)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMDS Rd, Rs1, Rs2
 * SMDRS Rd, Rs1, Rs2
 * SMXDS Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from the 32-bit elements of two registers; and then
 * perform a subtraction operation between the two 32-bit results.
 * * SMDS: top*top - bottom*bottom (per 32-bit element)
 * * SMDRS: bottom*bottom - top*top (per 32-bit element)
 * * SMXDS: top*bottom - bottom*top (per 32-bit element)
 *
 * **Description**:\n
 * For the `SMDS` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1 with
 * the bottom 16-bit content of the 32-bit elements of Rs2 and then subtracts the result from the result
 * of multiplying the top 16-bit content of the 32-bit elements of Rs1 with the top 16-bit content of the
 * 32-bit elements of Rs2.
 * For the `SMDRS` instruction, it multiplies the top 16-bit content of the 32-bit elements of Rs1 with
 * the top 16-bit content of the 32-bit elements of Rs2 and then subtracts the result from the result of
 * multiplying the bottom 16-bit content of the 32-bit elements of Rs1 with the bottom 16-bit content of
 * the 32-bit elements of Rs2.
 * For the `SMXDS` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the top 16-bit content of the 32-bit elements of Rs2 and then subtracts the result from the
 * result of multiplying the top 16-bit content of the 32-bit elements of Rs1 with the bottom 16-bit
 * content of the 32-bit elements of Rs2.
 * The subtraction result is written to the corresponding 32-bit element of Rd. The 16-bit contents of
 * multiplication are treated as signed integers.
 *
 * **Operations**:\n
 * ~~~
 * * SMDS:
 * Rd.W[x] = (Rs1.W[x].H[1] * Rs2.W[x].H[1]) - (Rs1.W[x].H[0] * Rs2.W[x].H[0]);
 * * SMDRS:
 * Rd.W[x] = (Rs1.W[x].H[0] * Rs2.W[x].H[0]) - (Rs1.W[x].H[1] * Rs2.W[x].H[1]);
 * * SMXDS:
 * Rd.W[x] = (Rs1.W[x].H[1] * Rs2.W[x].H[0]) - (Rs1.W[x].H[0] * Rs2.W[x].H[1]);
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_SMDRS(unsigned long a, unsigned long b)
{
    long result;
    __ASM volatile("smdrs %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.114.2. SMDRS ===== */

/* ===== Inline Function Start for 3.114.3. SMXDS ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_32B_ADDSUB
 * \brief SMXDS (SIMD Signed Crossed Multiply Two Halfs and Subtract)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMDS Rd, Rs1, Rs2
 * SMDRS Rd, Rs1, Rs2
 * SMXDS Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from the 32-bit elements of two registers; and then
 * perform a subtraction operation between the two 32-bit results.
 * * SMDS: top*top - bottom*bottom (per 32-bit element)
 * * SMDRS: bottom*bottom - top*top (per 32-bit element)
 * * SMXDS: top*bottom - bottom*top (per 32-bit element)
 *
 * **Description**:\n
 * For the `SMDS` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1 with
 * the bottom 16-bit content of the 32-bit elements of Rs2 and then subtracts the result from the result
 * of multiplying the top 16-bit content of the 32-bit elements of Rs1 with the top 16-bit content of the
 * 32-bit elements of Rs2.
 * For the `SMDRS` instruction, it multiplies the top 16-bit content of the 32-bit elements of Rs1 with
 * the top 16-bit content of the 32-bit elements of Rs2 and then subtracts the result from the result of
 * multiplying the bottom 16-bit content of the 32-bit elements of Rs1 with the bottom 16-bit content of
 * the 32-bit elements of Rs2.
 * For the `SMXDS` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the top 16-bit content of the 32-bit elements of Rs2 and then subtracts the result from the
 * result of multiplying the top 16-bit content of the 32-bit elements of Rs1 with the bottom 16-bit
 * content of the 32-bit elements of Rs2.
 * The subtraction result is written to the corresponding 32-bit element of Rd. The 16-bit contents of
 * multiplication are treated as signed integers.
 *
 * **Operations**:\n
 * ~~~
 * * SMDS:
 * Rd.W[x] = (Rs1.W[x].H[1] * Rs2.W[x].H[1]) - (Rs1.W[x].H[0] * Rs2.W[x].H[0]);
 * * SMDRS:
 * Rd.W[x] = (Rs1.W[x].H[0] * Rs2.W[x].H[0]) - (Rs1.W[x].H[1] * Rs2.W[x].H[1]);
 * * SMXDS:
 * Rd.W[x] = (Rs1.W[x].H[1] * Rs2.W[x].H[0]) - (Rs1.W[x].H[0] * Rs2.W[x].H[1]);
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_SMXDS(unsigned long a, unsigned long b)
{
    long result;
    __ASM volatile("smxds %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.114.3. SMXDS ===== */

/* ===== Inline Function Start for 3.115. SMIN8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_MISC
 * \brief SMIN8 (SIMD 8-bit Signed Minimum)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMIN8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit signed integer elements finding minimum operations simultaneously.
 *
 * **Description**:\n
 * This instruction compares the 8-bit signed integer elements in Rs1 with the 8-bit
 * signed integer elements in Rs2 and selects the numbers that is less than the other one. The selected
 * results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.B[x] = (Rs1.B[x] < Rs2.B[x])? Rs1.B[x] : Rs2.B[x];
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SMIN8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("smin8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.115. SMIN8 ===== */

/* ===== Inline Function Start for 3.116. SMIN16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_MISC
 * \brief SMIN16 (SIMD 16-bit Signed Minimum)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMIN16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit signed integer elements finding minimum operations simultaneously.
 *
 * **Description**:\n
 * This instruction compares the 16-bit signed integer elements in Rs1 with the 16-bit
 * signed integer elements in Rs2 and selects the numbers that is less than the other one. The selected
 * results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.H[x] = (Rs1.H[x] < Rs2.H[x])? Rs1.H[x] : Rs2.H[x];
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SMIN16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("smin16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.116. SMIN16 ===== */

/* ===== Inline Function Start for 3.117.1. SMMUL ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X32_MAC
 * \brief SMMUL (SIMD MSW Signed Multiply Word)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMMUL Rd, Rs1, Rs2
 * SMMUL.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the 32-bit signed integer elements of two registers and write the most significant
 * 32-bit results to the corresponding 32-bit elements of a register. The `.u` form performs an
 * additional rounding up operation on the multiplication results before taking the most significant
 * 32-bit part of the results.
 *
 * **Description**:\n
 * This instruction multiplies the 32-bit elements of Rs1 with the 32-bit elements of Rs2 and writes the
 * most significant 32-bit multiplication results to the corresponding 32-bit elements of Rd. The 32-bit
 * elements of Rs1 and Rs2 are treated as signed integers. The `.u` form of the instruction rounds up
 * the most significant 32-bit of the 64-bit multiplication results by adding a 1 to bit 31 of the results.
 * * For `smmul/RV32` instruction, it is an alias to `mulh/RV32` instruction.
 *
 * **Operations**:\n
 * ~~~
 * Mres[x][63:0] = Rs1.W[x] * Rs2.W[x];
 * if (`.u` form) {
 *   Round[x][32:0] = Mres[x][63:31] + 1;
 *   Rd.W[x] = Round[x][32:1];
 * } else {
 *   Rd.W[x] = Mres[x][63:32];
 * }
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_SMMUL(long a, long b)
{
    long result;
    __ASM volatile("smmul %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.117.1. SMMUL ===== */

/* ===== Inline Function Start for 3.117.2. SMMUL.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X32_MAC
 * \brief SMMUL.u (SIMD MSW Signed Multiply Word with Rounding)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMMUL Rd, Rs1, Rs2
 * SMMUL.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the 32-bit signed integer elements of two registers and write the most significant
 * 32-bit results to the corresponding 32-bit elements of a register. The `.u` form performs an
 * additional rounding up operation on the multiplication results before taking the most significant
 * 32-bit part of the results.
 *
 * **Description**:\n
 * This instruction multiplies the 32-bit elements of Rs1 with the 32-bit elements of Rs2 and writes the
 * most significant 32-bit multiplication results to the corresponding 32-bit elements of Rd. The 32-bit
 * elements of Rs1 and Rs2 are treated as signed integers. The `.u` form of the instruction rounds up
 * the most significant 32-bit of the 64-bit multiplication results by adding a 1 to bit 31 of the results.
 * * For `smmul/RV32` instruction, it is an alias to `mulh/RV32` instruction.
 *
 * **Operations**:\n
 * ~~~
 * Mres[x][63:0] = Rs1.W[x] * Rs2.W[x];
 * if (`.u` form) {
 *   Round[x][32:0] = Mres[x][63:31] + 1;
 *   Rd.W[x] = Round[x][32:1];
 * } else {
 *   Rd.W[x] = Mres[x][63:32];
 * }
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_SMMUL_U(long a, long b)
{
    long result;
    __ASM volatile("smmul.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.117.2. SMMUL.u ===== */

/* ===== Inline Function Start for 3.118.1. SMMWB ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X16_MAC
 * \brief SMMWB (SIMD MSW Signed Multiply Word and Bottom Half)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMMWB Rd, Rs1, Rs2
 * SMMWB.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit integer elements of one register and the bottom 16-bit of the
 * corresponding 32-bit elements of another register, and write the most significant 32-bit results to
 * the corresponding 32-bit elements of a register. The `.u` form rounds up the results from the most
 * significant discarded bit.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit elements of Rs1 with the signed bottom 16-bit content
 * of the corresponding 32-bit elements of Rs2 and writes the most significant 32-bit multiplication
 * results to the corresponding 32-bit elements of Rd. The `.u` form of the instruction rounds up the
 * most significant 32-bit of the 48-bit multiplication results by adding a 1 to bit 15 of the results.
 *
 * **Operations**:\n
 * ~~~
 * Mres[x][47:0] = Rs1.W[x] * Rs2.W[x].H[0];
 * if (`.u` form) {
 *   Round[x][32:0] = Mres[x][47:15] + 1;
 *   Rd.W[x] = Round[x][32:1];
 * } else {
 *   Rd.W[x] = Mres[x][47:16];
 * }
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_SMMWB(long a, unsigned long b)
{
    long result;
    __ASM volatile("smmwb %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.118.1. SMMWB ===== */

/* ===== Inline Function Start for 3.118.2. SMMWB.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X16_MAC
 * \brief SMMWB.u (SIMD MSW Signed Multiply Word and Bottom Half with Rounding)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMMWB Rd, Rs1, Rs2
 * SMMWB.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit integer elements of one register and the bottom 16-bit of the
 * corresponding 32-bit elements of another register, and write the most significant 32-bit results to
 * the corresponding 32-bit elements of a register. The `.u` form rounds up the results from the most
 * significant discarded bit.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit elements of Rs1 with the signed bottom 16-bit content
 * of the corresponding 32-bit elements of Rs2 and writes the most significant 32-bit multiplication
 * results to the corresponding 32-bit elements of Rd. The `.u` form of the instruction rounds up the
 * most significant 32-bit of the 48-bit multiplication results by adding a 1 to bit 15 of the results.
 *
 * **Operations**:\n
 * ~~~
 * Mres[x][47:0] = Rs1.W[x] * Rs2.W[x].H[0];
 * if (`.u` form) {
 *   Round[x][32:0] = Mres[x][47:15] + 1;
 *   Rd.W[x] = Round[x][32:1];
 * } else {
 *   Rd.W[x] = Mres[x][47:16];
 * }
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_SMMWB_U(long a, unsigned long b)
{
    long result;
    __ASM volatile("smmwb.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.118.2. SMMWB.u ===== */

/* ===== Inline Function Start for 3.119.1. SMMWT ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X16_MAC
 * \brief SMMWT (SIMD MSW Signed Multiply Word and Top Half)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMMWT Rd, Rs1, Rs2
 * SMMWT.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit integer elements of one register and the top 16-bit of the
 * corresponding 32-bit elements of another register, and write the most significant 32-bit results to
 * the corresponding 32-bit elements of a register. The `.u` form rounds up the results from the most
 * significant discarded bit.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit elements of Rs1 with the top signed 16-bit content of
 * the corresponding 32-bit elements of Rs2 and writes the most significant 32-bit multiplication
 * results to the corresponding 32-bit elements of Rd. The `.u` form of the instruction rounds up the
 * most significant 32-bit of the 48-bit multiplication results by adding a 1 to bit 15 of the results.
 *
 * **Operations**:\n
 * ~~~
 * Mres[x][47:0] = Rs1.W[x] * Rs2.W[x].H[1];
 * if (`.u` form) {
 *   Round[x][32:0] = Mres[x][47:15] + 1;
 *   Rd.W[x] = Round[x][32:1];
 * } else {
 *   Rd.W[x] = Mres[x][47:16];
 * }
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_SMMWT(long a, unsigned long b)
{
    long result;
    __ASM volatile("smmwt %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.119.1. SMMWT ===== */

/* ===== Inline Function Start for 3.119.2. SMMWT.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_MSW_32X16_MAC
 * \brief SMMWT.u (SIMD MSW Signed Multiply Word and Top Half with Rounding)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMMWT Rd, Rs1, Rs2
 * SMMWT.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the signed 32-bit integer elements of one register and the top 16-bit of the
 * corresponding 32-bit elements of another register, and write the most significant 32-bit results to
 * the corresponding 32-bit elements of a register. The `.u` form rounds up the results from the most
 * significant discarded bit.
 *
 * **Description**:\n
 * This instruction multiplies the signed 32-bit elements of Rs1 with the top signed 16-bit content of
 * the corresponding 32-bit elements of Rs2 and writes the most significant 32-bit multiplication
 * results to the corresponding 32-bit elements of Rd. The `.u` form of the instruction rounds up the
 * most significant 32-bit of the 48-bit multiplication results by adding a 1 to bit 15 of the results.
 *
 * **Operations**:\n
 * ~~~
 * Mres[x][47:0] = Rs1.W[x] * Rs2.W[x].H[1];
 * if (`.u` form) {
 *   Round[x][32:0] = Mres[x][47:15] + 1;
 *   Rd.W[x] = Round[x][32:1];
 * } else {
 *   Rd.W[x] = Mres[x][47:16];
 * }
 * for RV32: x=0
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_SMMWT_U(long a, unsigned long b)
{
    long result;
    __ASM volatile("smmwt.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.119.2. SMMWT.u ===== */

/* ===== Inline Function Start for 3.120.1. SMSLDA ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_64B_ADDSUB
 * \brief SMSLDA (Signed Multiply Two Halfs & Add & Subtract 64-bit)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * SMSLDA Rd, Rs1, Rs2
 * SMSLXDA Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from the 32-bit elements of two registers; and then
 * subtracts the two 32-bit results from the 64-bit value of an even/odd pair of registers (RV32) or a
 * register (RV64). The subtraction result is written back to the register-pair.
 * * SMSLDA: rd pair - top*top - bottom*bottom (all 32-bit elements)
 * * SMSLXDA: rd pair - top*bottom - bottom*top (all 32-bit elements)
 *
 * **RV32 Description**:\n
 * For the `SMSLDA` instruction, it multiplies the bottom 16-bit content of Rs1 with the bottom 16-bit
 * content Rs2 and multiplies the top 16-bit content of Rs1 with the top 16-bit content of Rs2.
 * For the `SMSLXDA` instruction, it multiplies the top 16-bit content of Rs1 with the bottom 16-bit
 * content of Rs2 and multiplies the bottom 16-bit content of Rs1 with the top 16-bit content of Rs2.
 * The two multiplication results are subtracted from the 64-bit value of an even/odd pair of registers
 * specified by Rd(4,1). The 64-bit subtraction result is written back to the register-pair. The 16-bit
 * values of Rs1 and Rs2, and the 64-bit value of the register-pair are treated as signed integers.
 * Rd(4,1), i.e., d, determines the even/odd pair group of the two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 *
 * **RV64 Description**:\n
 * For the `SMSLDA` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2 and multiplies the top 16-bit content of
 * the 32-bit elements of Rs1 with the top 16-bit content of the 32-bit elements of Rs2.
 * For the `SMSLXDA` instruction, it multiplies the top 16-bit content of the 32-bit elements of Rs1 with
 * the bottom 16-bit content of the 32-bit elements of Rs2 and multiplies the bottom 16-bit content of
 * the 32-bit elements of Rs1 with the top 16-bit content of the 32-bit elements of Rs2.
 * The four multiplication results are subtracted from the 64-bit value of Rd. The 64-bit subtraction
 * result is written back to Rd. The 16-bit values of Rs1 and Rs2, and the 64-bit value of Rd are treated
 * as signed integers.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * // SMSLDA
 * Mres0[31:0] = (Rs1.H[0] * Rs2.H[0]);
 * Mres1[31:0] = (Rs1.H[1] * Rs2.H[1]);
 * // SMSLXDA
 * Mres0[31:0] = (Rs1.H[0] * Rs2.H[1]);
 * Mres1[31:0] = (Rs1.H[1] * Rs2.H[0]);
 * Idx0 = CONCAT(Rd(4,1),1'b0); Idx1 = CONCAT(Rd(4,1),1'b1);
 * R[Idx1].R[Idx0] = R[Idx1].R[Idx0] - SE64(Mres0[31:0]) - SE64(Mres1[31:0]);
 * * RV64:
 * // SMSLDA
 * Mres0[0][31:0] = (Rs1.W[0].H[0] * Rs2.W[0].H[0]);
 * Mres1[0][31:0] = (Rs1.W[0].H[1] * Rs2.W[0].H[1]);
 * Mres0[1][31:0] = (Rs1.W[1].H[0] * Rs2.W[1].H[0]);
 * Mres1[1][31:0] = (Rs1.W[1].H[1] * Rs2.W[1].H[1]);
 * // SMSLXDA
 * Mres0[0][31:0] = (Rs1.W[0].H[0] * Rs2.W[0].H[1]);
 * Mres1[0][31:0] = (Rs1.W[0].H[1] * Rs2.W[0].H[0]);
 * Mres0[1][31:0] = (Rs1.W[1].H[0] * Rs2.W[1].H[1]);
 * Mres1[1][31:0] = (Rs1.W[1].H[1] * Rs2.W[1].H[0]);
 * Rd = Rd - SE64(Mres0[0][31:0]) - SE64(Mres1[0][31:0]) - SE64(Mres0[1][31:0]) -
 * SE64(Mres1[1][31:0]);
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_SMSLDA(long long t, unsigned long a, unsigned long b)
{
    __ASM volatile("smslda %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.120.1. SMSLDA ===== */

/* ===== Inline Function Start for 3.120.2. SMSLXDA ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIGNED_16B_MULT_64B_ADDSUB
 * \brief SMSLXDA (Signed Crossed Multiply Two Halfs & Add & Subtract 64- bit)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * SMSLDA Rd, Rs1, Rs2
 * SMSLXDA Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do two signed 16-bit multiplications from the 32-bit elements of two registers; and then
 * subtracts the two 32-bit results from the 64-bit value of an even/odd pair of registers (RV32) or a
 * register (RV64). The subtraction result is written back to the register-pair.
 * * SMSLDA: rd pair - top*top - bottom*bottom (all 32-bit elements)
 * * SMSLXDA: rd pair - top*bottom - bottom*top (all 32-bit elements)
 *
 * **RV32 Description**:\n
 * For the `SMSLDA` instruction, it multiplies the bottom 16-bit content of Rs1 with the bottom 16-bit
 * content Rs2 and multiplies the top 16-bit content of Rs1 with the top 16-bit content of Rs2.
 * For the `SMSLXDA` instruction, it multiplies the top 16-bit content of Rs1 with the bottom 16-bit
 * content of Rs2 and multiplies the bottom 16-bit content of Rs1 with the top 16-bit content of Rs2.
 * The two multiplication results are subtracted from the 64-bit value of an even/odd pair of registers
 * specified by Rd(4,1). The 64-bit subtraction result is written back to the register-pair. The 16-bit
 * values of Rs1 and Rs2, and the 64-bit value of the register-pair are treated as signed integers.
 * Rd(4,1), i.e., d, determines the even/odd pair group of the two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 *
 * **RV64 Description**:\n
 * For the `SMSLDA` instruction, it multiplies the bottom 16-bit content of the 32-bit elements of Rs1
 * with the bottom 16-bit content of the 32-bit elements of Rs2 and multiplies the top 16-bit content of
 * the 32-bit elements of Rs1 with the top 16-bit content of the 32-bit elements of Rs2.
 * For the `SMSLXDA` instruction, it multiplies the top 16-bit content of the 32-bit elements of Rs1 with
 * the bottom 16-bit content of the 32-bit elements of Rs2 and multiplies the bottom 16-bit content of
 * the 32-bit elements of Rs1 with the top 16-bit content of the 32-bit elements of Rs2.
 * The four multiplication results are subtracted from the 64-bit value of Rd. The 64-bit subtraction
 * result is written back to Rd. The 16-bit values of Rs1 and Rs2, and the 64-bit value of Rd are treated
 * as signed integers.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * // SMSLDA
 * Mres0[31:0] = (Rs1.H[0] * Rs2.H[0]);
 * Mres1[31:0] = (Rs1.H[1] * Rs2.H[1]);
 * // SMSLXDA
 * Mres0[31:0] = (Rs1.H[0] * Rs2.H[1]);
 * Mres1[31:0] = (Rs1.H[1] * Rs2.H[0]);
 * Idx0 = CONCAT(Rd(4,1),1'b0); Idx1 = CONCAT(Rd(4,1),1'b1);
 * R[Idx1].R[Idx0] = R[Idx1].R[Idx0] - SE64(Mres0[31:0]) - SE64(Mres1[31:0]);
 * * RV64:
 * // SMSLDA
 * Mres0[0][31:0] = (Rs1.W[0].H[0] * Rs2.W[0].H[0]);
 * Mres1[0][31:0] = (Rs1.W[0].H[1] * Rs2.W[0].H[1]);
 * Mres0[1][31:0] = (Rs1.W[1].H[0] * Rs2.W[1].H[0]);
 * Mres1[1][31:0] = (Rs1.W[1].H[1] * Rs2.W[1].H[1]);
 * // SMSLXDA
 * Mres0[0][31:0] = (Rs1.W[0].H[0] * Rs2.W[0].H[1]);
 * Mres1[0][31:0] = (Rs1.W[0].H[1] * Rs2.W[0].H[0]);
 * Mres0[1][31:0] = (Rs1.W[1].H[0] * Rs2.W[1].H[1]);
 * Mres1[1][31:0] = (Rs1.W[1].H[1] * Rs2.W[1].H[0]);
 * Rd = Rd - SE64(Mres0[0][31:0]) - SE64(Mres1[0][31:0]) - SE64(Mres0[1][31:0]) -
 * SE64(Mres1[1][31:0]);
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_SMSLXDA(long long t, unsigned long a, unsigned long b)
{
    __ASM volatile("smslxda %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.120.2. SMSLXDA ===== */

/* ===== Inline Function Start for 3.121. SMSR64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_32B_MULT_64B_ADDSUB
 * \brief SMSR64 (Signed Multiply and Subtract from 64- Bit Data)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * SMSR64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the 32-bit signed elements in two registers and subtract the 64-bit multiplication
 * results from the 64-bit signed data of a pair of registers (RV32) or a register (RV64). The result is
 * written back to the pair of registers (RV32) or a register (RV64).
 *
 * **RV32 Description**:\n
 * This instruction multiplies the 32-bit signed data of Rs1 with that of Rs2. It
 * subtracts the 64-bit multiplication result from the 64-bit signed data of an even/odd pair of registers
 * specified by Rd(4,1). The subtraction result is written back to the even/odd pair of registers
 * specified by Rd(4,1).
 * Rx(4,1), i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 *
 * **RV64 Description**:\n
 * This instruction multiplies the 32-bit signed elements of Rs1 with that of Rs2. It
 * subtracts the 64-bit multiplication results from the 64-bit signed data of Rd. The subtraction result is
 * written back to Rd.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * R[t_H].R[t_L] = R[t_H].R[t_L] - (Rs1 * Rs2);
 * * RV64:
 * Rd = Rd - (Rs1.W[0] * Rs2.W[0]) - (Rs1.W[1] * Rs2.W[1]);
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long long __RV_SMSR64(long long t, long a, long b)
{
    __ASM volatile("smsr64 %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.121. SMSR64 ===== */

/* ===== Inline Function Start for 3.122.1. SMUL8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_MULTIPLY
 * \brief SMUL8 (SIMD Signed 8-bit Multiply)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMUL8 Rd, Rs1, Rs2
 * SMULX8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do signed 8-bit multiplications and generate four 16-bit results simultaneously.
 *
 * **RV32 Description**:\n
 * For the `SMUL8` instruction, multiply the 8-bit data elements of Rs1 with the
 * corresponding 8-bit data elements of Rs2.
 * For the `SMULX8` instruction, multiply the first and second 8-bit data elements of Rs1 with the
 * second and first 8-bit data elements of Rs2. At the same time, multiply the third and fourth 8-bit data
 * elements of Rs1 with the fourth and third 8-bit data elements of Rs2.
 * The four 16-bit results are then written into an even/odd pair of registers specified by Rd(4,1).
 * Rd(4,1), i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the two 16-bit results calculated from the top part of
 * Rs1 and the even `2d` register of the pair contains the two 16-bit results calculated from the bottom
 * part of Rs1.
 *
 * **RV64 Description**:\n
 * For the `SMUL8` instruction, multiply the 8-bit data elements of Rs1 with the
 * corresponding 8-bit data elements of Rs2.
 * For the `SMULX8` instruction, multiply the first and second 8-bit data elements of Rs1 with the
 * second and first 8-bit data elements of Rs2. At the same time, multiply the third and fourth 8-bit data
 * elements of Rs1 with the fourth and third 8-bit data elements of Rs2.
 * The four 16-bit results are then written into Rd. The Rd.W[1] contains the two 16-bit results
 * calculated from the top part of Rs1 and the Rd.W[0] contains the two 16-bit results calculated from
 * the bottom part of Rs1.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * if (is `SMUL8`) {
 *   op1t[x/2] = Rs1.B[x+1]; op2t[x/2] = Rs2.B[x+1]; // top
 *   op1b[x/2] = Rs1.B[x]; op2b[x/2] = Rs2.B[x]; // bottom
 * } else if (is `SMULX8`) {
 *   op1t[x/2] = Rs1.B[x+1]; op2t[x/2] = Rs2.B[x]; // Rs1 top
 *   op1b[x/2] = Rs1.B[x]; op2b[x/2] = Rs2.B[x+1]; // Rs1 bottom
 * }
 * rest[x/2] = op1t[x/2] s* op2t[x/2];
 * resb[x/2] = op1b[x/2] s* op2b[x/2];
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * R[t_H].H[1] = rest[1]; R[t_H].H[0] = resb[1];
 * R[t_L].H[1] = rest[0]; R[t_L].H[0] = resb[0];
 * x = 0 and 2
 * * RV64:
 * if (is `SMUL8`) {
 *   op1t[x/2] = Rs1.B[x+1]; op2t[x/2] = Rs2.B[x+1]; // top
 *   op1b[x/2] = Rs1.B[x]; op2b[x/2] = Rs2.B[x]; // bottom
 * } else if (is `SMULX8`) {
 *   op1t[x/2] = Rs1.B[x+1]; op2t[x/2] = Rs2.B[x]; // Rs1 top
 *   op1b[x/2] = Rs1.B[x]; op2b[x/2] = Rs2.B[x+1]; // Rs1 bottom
 * }
 * rest[x/2] = op1t[x/2] s* op2t[x/2];
 * resb[x/2] = op1b[x/2] s* op2b[x/2];
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * Rd.W[1].H[1] = rest[1]; Rd.W[1].H[0] = resb[1];
 * Rd.W[0].H[1] = rest[0]; Rd.W[0].H[0] = resb[0];
 * x = 0 and 2
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_SMUL8(unsigned int a, unsigned int b)
{
    unsigned long long result;
    __ASM volatile("smul8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.122.1. SMUL8 ===== */

/* ===== Inline Function Start for 3.122.2. SMULX8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_MULTIPLY
 * \brief SMULX8 (SIMD Signed Crossed 8-bit Multiply)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMUL8 Rd, Rs1, Rs2
 * SMULX8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do signed 8-bit multiplications and generate four 16-bit results simultaneously.
 *
 * **RV32 Description**:\n
 * For the `SMUL8` instruction, multiply the 8-bit data elements of Rs1 with the
 * corresponding 8-bit data elements of Rs2.
 * For the `SMULX8` instruction, multiply the first and second 8-bit data elements of Rs1 with the
 * second and first 8-bit data elements of Rs2. At the same time, multiply the third and fourth 8-bit data
 * elements of Rs1 with the fourth and third 8-bit data elements of Rs2.
 * The four 16-bit results are then written into an even/odd pair of registers specified by Rd(4,1).
 * Rd(4,1), i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the two 16-bit results calculated from the top part of
 * Rs1 and the even `2d` register of the pair contains the two 16-bit results calculated from the bottom
 * part of Rs1.
 *
 * **RV64 Description**:\n
 * For the `SMUL8` instruction, multiply the 8-bit data elements of Rs1 with the
 * corresponding 8-bit data elements of Rs2.
 * For the `SMULX8` instruction, multiply the first and second 8-bit data elements of Rs1 with the
 * second and first 8-bit data elements of Rs2. At the same time, multiply the third and fourth 8-bit data
 * elements of Rs1 with the fourth and third 8-bit data elements of Rs2.
 * The four 16-bit results are then written into Rd. The Rd.W[1] contains the two 16-bit results
 * calculated from the top part of Rs1 and the Rd.W[0] contains the two 16-bit results calculated from
 * the bottom part of Rs1.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * if (is `SMUL8`) {
 *   op1t[x/2] = Rs1.B[x+1]; op2t[x/2] = Rs2.B[x+1]; // top
 *   op1b[x/2] = Rs1.B[x]; op2b[x/2] = Rs2.B[x]; // bottom
 * } else if (is `SMULX8`) {
 *   op1t[x/2] = Rs1.B[x+1]; op2t[x/2] = Rs2.B[x]; // Rs1 top
 *   op1b[x/2] = Rs1.B[x]; op2b[x/2] = Rs2.B[x+1]; // Rs1 bottom
 * }
 * rest[x/2] = op1t[x/2] s* op2t[x/2];
 * resb[x/2] = op1b[x/2] s* op2b[x/2];
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * R[t_H].H[1] = rest[1]; R[t_H].H[0] = resb[1];
 * R[t_L].H[1] = rest[0]; R[t_L].H[0] = resb[0];
 * x = 0 and 2
 * * RV64:
 * if (is `SMUL8`) {
 *   op1t[x/2] = Rs1.B[x+1]; op2t[x/2] = Rs2.B[x+1]; // top
 *   op1b[x/2] = Rs1.B[x]; op2b[x/2] = Rs2.B[x]; // bottom
 * } else if (is `SMULX8`) {
 *   op1t[x/2] = Rs1.B[x+1]; op2t[x/2] = Rs2.B[x]; // Rs1 top
 *   op1b[x/2] = Rs1.B[x]; op2b[x/2] = Rs2.B[x+1]; // Rs1 bottom
 * }
 * rest[x/2] = op1t[x/2] s* op2t[x/2];
 * resb[x/2] = op1b[x/2] s* op2b[x/2];
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * Rd.W[1].H[1] = rest[1]; Rd.W[1].H[0] = resb[1];
 * Rd.W[0].H[1] = rest[0]; Rd.W[0].H[0] = resb[0];
 * x = 0 and 2
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_SMULX8(unsigned int a, unsigned int b)
{
    unsigned long long result;
    __ASM volatile("smulx8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.122.2. SMULX8 ===== */

/* ===== Inline Function Start for 3.123.1. SMUL16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_MULTIPLY
 * \brief SMUL16 (SIMD Signed 16-bit Multiply)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMUL16 Rd, Rs1, Rs2
 * SMULX16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do signed 16-bit multiplications and generate two 32-bit results simultaneously.
 *
 * **RV32 Description**:\n
 * For the `SMUL16` instruction, multiply the top 16-bit Q15 content of Rs1 with
 * the top 16-bit Q15 content of Rs2. At the same time, multiply the bottom 16-bit Q15 content of Rs1
 * with the bottom 16-bit Q15 content of Rs2.
 * For the `SMULX16` instruction, multiply the top 16-bit Q15 content of Rs1 with the bottom 16-bit
 * Q15 content of Rs2. At the same time, multiply the bottom 16-bit Q15 content of Rs1 with the top 16-
 * bit Q15 content of Rs2.
 * The two Q30 results are then written into an even/odd pair of registers specified by Rd(4,1). Rd(4,1),
 * i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair includes
 * register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the 32-bit result calculated from the top part of Rs1 and
 * the even `2d` register of the pair contains the 32-bit result calculated from the bottom part of Rs1.
 *
 * **RV64 Description**:\n
 * For the `SMUL16` instruction, multiply the top 16-bit Q15 content of the lower
 * 32-bit word in Rs1 with the top 16-bit Q15 content of the lower 32-bit word in Rs2. At the same time,
 * multiply the bottom 16-bit Q15 content of the lower 32-bit word in Rs1 with the bottom 16-bit Q15
 * content of the lower 32-bit word in Rs2.
 * For the `SMULX16` instruction, multiply the top 16-bit Q15 content of the lower 32-bit word in Rs1
 * with the bottom 16-bit Q15 content of the lower 32-bit word in Rs2. At the same time, multiply the
 * bottom 16-bit Q15 content of the lower 32-bit word in Rs1 with the top 16-bit Q15 content of the
 * lower 32-bit word in Rs2.
 * The two 32-bit Q30 results are then written into Rd. The result calculated from the top 16-bit of the
 * lower 32-bit word in Rs1 is written to Rd.W[1]. And the result calculated from the bottom 16-bit of
 * the lower 32-bit word in Rs1 is written to Rd.W[0]
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * if (is `SMUL16`) {
 *   op1t = Rs1.H[1]; op2t = Rs2.H[1]; // top
 *   op1b = Rs1.H[0]; op2b = Rs2.H[0]; // bottom
 * } else if (is `SMULX16`) {
 *   op1t = Rs1.H[1]; op2t = Rs2.H[0]; // Rs1 top
 *   op1b = Rs1.H[0]; op2b = Rs2.H[1]; // Rs1 bottom
 * }
 * for ((aop,bop,res) in [(op1t,op2t,rest), (op1b,op2b,resb)]) {
 *   res = aop s* bop;
 * }
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * R[t_H] = rest;
 * R[t_L] = resb;
 * * RV64:
 * if (is `SMUL16`) {
 *   op1t = Rs1.H[1]; op2t = Rs2.H[1]; // top
 *   op1b = Rs1.H[0]; op2b = Rs2.H[0]; // bottom
 * } else if (is `SMULX16`) {
 *   op1t = Rs1.H[1]; op2t = Rs2.H[0]; // Rs1 top
 *   op1b = Rs1.H[0]; op2b = Rs2.H[1]; // Rs1 bottom
 * }
 * for ((aop,bop,res) in [(op1t,op2t,rest), (op1b,op2b,resb)]) {
 *   res = aop s* bop;
 * }
 * Rd.W[1] = rest;
 * Rd.W[0] = resb;
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_SMUL16(unsigned int a, unsigned int b)
{
    unsigned long long result;
    __ASM volatile("smul16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.123.1. SMUL16 ===== */

/* ===== Inline Function Start for 3.123.2. SMULX16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_MULTIPLY
 * \brief SMULX16 (SIMD Signed Crossed 16-bit Multiply)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SMUL16 Rd, Rs1, Rs2
 * SMULX16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do signed 16-bit multiplications and generate two 32-bit results simultaneously.
 *
 * **RV32 Description**:\n
 * For the `SMUL16` instruction, multiply the top 16-bit Q15 content of Rs1 with
 * the top 16-bit Q15 content of Rs2. At the same time, multiply the bottom 16-bit Q15 content of Rs1
 * with the bottom 16-bit Q15 content of Rs2.
 * For the `SMULX16` instruction, multiply the top 16-bit Q15 content of Rs1 with the bottom 16-bit
 * Q15 content of Rs2. At the same time, multiply the bottom 16-bit Q15 content of Rs1 with the top 16-
 * bit Q15 content of Rs2.
 * The two Q30 results are then written into an even/odd pair of registers specified by Rd(4,1). Rd(4,1),
 * i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair includes
 * register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the 32-bit result calculated from the top part of Rs1 and
 * the even `2d` register of the pair contains the 32-bit result calculated from the bottom part of Rs1.
 *
 * **RV64 Description**:\n
 * For the `SMUL16` instruction, multiply the top 16-bit Q15 content of the lower
 * 32-bit word in Rs1 with the top 16-bit Q15 content of the lower 32-bit word in Rs2. At the same time,
 * multiply the bottom 16-bit Q15 content of the lower 32-bit word in Rs1 with the bottom 16-bit Q15
 * content of the lower 32-bit word in Rs2.
 * For the `SMULX16` instruction, multiply the top 16-bit Q15 content of the lower 32-bit word in Rs1
 * with the bottom 16-bit Q15 content of the lower 32-bit word in Rs2. At the same time, multiply the
 * bottom 16-bit Q15 content of the lower 32-bit word in Rs1 with the top 16-bit Q15 content of the
 * lower 32-bit word in Rs2.
 * The two 32-bit Q30 results are then written into Rd. The result calculated from the top 16-bit of the
 * lower 32-bit word in Rs1 is written to Rd.W[1]. And the result calculated from the bottom 16-bit of
 * the lower 32-bit word in Rs1 is written to Rd.W[0]
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * if (is `SMUL16`) {
 *   op1t = Rs1.H[1]; op2t = Rs2.H[1]; // top
 *   op1b = Rs1.H[0]; op2b = Rs2.H[0]; // bottom
 * } else if (is `SMULX16`) {
 *   op1t = Rs1.H[1]; op2t = Rs2.H[0]; // Rs1 top
 *   op1b = Rs1.H[0]; op2b = Rs2.H[1]; // Rs1 bottom
 * }
 * for ((aop,bop,res) in [(op1t,op2t,rest), (op1b,op2b,resb)]) {
 *   res = aop s* bop;
 * }
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * R[t_H] = rest;
 * R[t_L] = resb;
 * * RV64:
 * if (is `SMUL16`) {
 *   op1t = Rs1.H[1]; op2t = Rs2.H[1]; // top
 *   op1b = Rs1.H[0]; op2b = Rs2.H[0]; // bottom
 * } else if (is `SMULX16`) {
 *   op1t = Rs1.H[1]; op2t = Rs2.H[0]; // Rs1 top
 *   op1b = Rs1.H[0]; op2b = Rs2.H[1]; // Rs1 bottom
 * }
 * for ((aop,bop,res) in [(op1t,op2t,rest), (op1b,op2b,resb)]) {
 *   res = aop s* bop;
 * }
 * Rd.W[1] = rest;
 * Rd.W[0] = resb;
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_SMULX16(unsigned int a, unsigned int b)
{
    unsigned long long result;
    __ASM volatile("smulx16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.123.2. SMULX16 ===== */

/* ===== Inline Function Start for 3.124. SRA.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_MISC
 * \brief SRA.u (Rounding Shift Right Arithmetic)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * SRA.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Perform an arithmetic right shift operation with rounding. The shift amount is a variable
 * from a GPR.
 *
 * **Description**:\n
 * This instruction right-shifts the content of Rs1 arithmetically. The shifted out bits are
 * filled with the sign-bit and the shift amount is specified by the low-order 5-bits (RV32) or 6-bits
 * (RV64) of the Rs2 register. For the rounding operation, a value of 1 is added to the most significant
 * discarded bit of the data to calculate the final result. And the result is written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * sa = Rs2[4:0];
 * if (sa > 0) {
 *   res[31:-1] = SE33(Rs1[31:(sa-1)]) + 1;
 *   Rd = res[31:0];
 * } else {
 *   Rd = Rs1;
 * }
 * * RV64:
 * sa = Rs2[5:0];
 * if (sa > 0) {
 *   res[63:-1] = SE65(Rs1[63:(sa-1)]) + 1;
 *   Rd = res[63:0];
 * } else {
 *   Rd = Rs1;
 * }
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_SRA_U(long a, unsigned int b)
{
    long result;
    __ASM volatile("sra.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.124. SRA.u ===== */

/* ===== Inline Function Start for 3.125. SRAI.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_MISC
 * \brief SRAI.u (Rounding Shift Right Arithmetic Immediate)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * SRAI.u Rd, Rs1, imm6u[4:0] (RV32)
 * SRAI.u Rd, Rs1, imm6u[5:0] (RV64)
 * ~~~
 *
 * **Purpose**:\n
 * Perform an arithmetic right shift operation with rounding. The shift amount is an
 * immediate value.
 *
 * **Description**:\n
 * This instruction right-shifts the content of Rs1 arithmetically. The shifted out bits are
 * filled with the sign-bit and the shift amount is specified by the imm6u[4:0] (RV32) or imm6u[5:0]
 * (RV64) constant . For the rounding operation, a value of 1 is added to the most significant discarded
 * bit of the data to calculate the final result. And the result is written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * sa = imm6u[4:0];
 * if (sa > 0) {
 *   res[31:-1] = SE33(Rs1[31:(sa-1)]) + 1;
 *   Rd = res[31:0];
 * } else {
 *   Rd = Rs1;
 * }
 * * RV64:
 * sa = imm6u[5:0];
 * if (sa > 0) {
 *   res[63:-1] = SE65(Rs1[63:(sa-1)]) + 1;
 *   Rd = res[63:0];
 * } else {
 *   Rd = Rs1;
 * }
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE long __RV_SRAI_U(long a, unsigned int b)
{
    long result;
    __ASM volatile("srai.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.125. SRAI.u ===== */

/* ===== Inline Function Start for 3.126.1. SRA8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_SHIFT
 * \brief SRA8 (SIMD 8-bit Shift Right Arithmetic)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SRA8 Rd, Rs1, Rs2
 * SRA8.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit element arithmetic right shift operations simultaneously. The shift amount is a
 * variable from a GPR. The `.u` form performs additional rounding up operations on the shifted
 * results.
 *
 * **Description**:\n
 * The 8-bit data elements in Rs1 are right-shifted arithmetically, that is, the shifted out
 * bits are filled with the sign-bit of the data elements. The shift amount is specified by the low-order
 * 3-bits of the value in the Rs2 register. For the rounding operation of the `.u` form, a value of 1 is
 * added to the most significant discarded bit of each 8-bit data element to calculate the final results.
 * And the results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * sa = Rs2[2:0];
 * if (sa > 0) {
 *   if (`.u` form) { // SRA8.u
 *     res[7:-1] = SE9(Rs1.B[x][7:sa-1]) + 1;
 *     Rd.B[x] = res[7:0];
 *   } else { // SRA8
 *     Rd.B[x] = SE8(Rd.B[x][7:sa])
 *   }
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SRA8(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("sra8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.126.1. SRA8 ===== */

/* ===== Inline Function Start for 3.126.2. SRA8.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_SHIFT
 * \brief SRA8.u (SIMD 8-bit Rounding Shift Right Arithmetic)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SRA8 Rd, Rs1, Rs2
 * SRA8.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit element arithmetic right shift operations simultaneously. The shift amount is a
 * variable from a GPR. The `.u` form performs additional rounding up operations on the shifted
 * results.
 *
 * **Description**:\n
 * The 8-bit data elements in Rs1 are right-shifted arithmetically, that is, the shifted out
 * bits are filled with the sign-bit of the data elements. The shift amount is specified by the low-order
 * 3-bits of the value in the Rs2 register. For the rounding operation of the `.u` form, a value of 1 is
 * added to the most significant discarded bit of each 8-bit data element to calculate the final results.
 * And the results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * sa = Rs2[2:0];
 * if (sa > 0) {
 *   if (`.u` form) { // SRA8.u
 *     res[7:-1] = SE9(Rs1.B[x][7:sa-1]) + 1;
 *     Rd.B[x] = res[7:0];
 *   } else { // SRA8
 *     Rd.B[x] = SE8(Rd.B[x][7:sa])
 *   }
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SRA8_U(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("sra8.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.126.2. SRA8.u ===== */

/* ===== Inline Function Start for 3.127.1. SRAI8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_SHIFT
 * \brief SRAI8 (SIMD 8-bit Shift Right Arithmetic Immediate)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SRAI8 Rd, Rs1, imm3u
 * SRAI8.u Rd, Rs1, imm3u
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit element arithmetic right shift operations simultaneously. The shift amount is an
 * immediate value. The `.u` form performs additional rounding up operations on the shifted results.
 *
 * **Description**:\n
 * The 8-bit data elements in Rs1 are right-shifted arithmetically, that is, the shifted out
 * bits are filled with the sign-bit of the data elements. The shift amount is specified by the imm3u
 * constant. For the rounding operation of the `.u` form, a value of 1 is added to the most significant
 * discarded bit of each 8-bit data element to calculate the final results. And the results are written to
 * Rd.
 *
 * **Operations**:\n
 * ~~~
 * sa = imm3u[2:0];
 * if (sa > 0) {
 *   if (`.u` form) { // SRA8.u
 *     res[7:-1] = SE9(Rs1.B[x][7:sa-1]) + 1;
 *     Rd.B[x] = res[7:0];
 *   } else { // SRA8
 *     Rd.B[x] = SE8(Rd.B[x][7:sa])
 *   }
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SRAI8(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("srai8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.127.1. SRAI8 ===== */

/* ===== Inline Function Start for 3.127.2. SRAI8.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_SHIFT
 * \brief SRAI8.u (SIMD 8-bit Rounding Shift Right Arithmetic Immediate)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SRAI8 Rd, Rs1, imm3u
 * SRAI8.u Rd, Rs1, imm3u
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit element arithmetic right shift operations simultaneously. The shift amount is an
 * immediate value. The `.u` form performs additional rounding up operations on the shifted results.
 *
 * **Description**:\n
 * The 8-bit data elements in Rs1 are right-shifted arithmetically, that is, the shifted out
 * bits are filled with the sign-bit of the data elements. The shift amount is specified by the imm3u
 * constant. For the rounding operation of the `.u` form, a value of 1 is added to the most significant
 * discarded bit of each 8-bit data element to calculate the final results. And the results are written to
 * Rd.
 *
 * **Operations**:\n
 * ~~~
 * sa = imm3u[2:0];
 * if (sa > 0) {
 *   if (`.u` form) { // SRA8.u
 *     res[7:-1] = SE9(Rs1.B[x][7:sa-1]) + 1;
 *     Rd.B[x] = res[7:0];
 *   } else { // SRA8
 *     Rd.B[x] = SE8(Rd.B[x][7:sa])
 *   }
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SRAI8_U(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("srai8.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.127.2. SRAI8.u ===== */

/* ===== Inline Function Start for 3.128.1. SRA16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_SHIFT
 * \brief SRA16 (SIMD 16-bit Shift Right Arithmetic)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SRA16 Rd, Rs1, Rs2
 * SRA16.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit element arithmetic right shift operations simultaneously. The shift amount is a
 * variable from a GPR. The `.u` form performs additional rounding up operations on the shifted
 * results.
 *
 * **Description**:\n
 * The 16-bit data elements in Rs1 are right-shifted arithmetically, that is, the shifted out
 * bits are filled with the sign-bit of the data elements. The shift amount is specified by the low-order
 * 4-bits of the value in the Rs2 register. For the rounding operation of the `.u` form, a value of 1 is
 * added to the most significant discarded bit of each 16-bit data element to calculate the final results.
 * And the results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * sa = Rs2[3:0];
 * if (sa != 0) {
 *   if (`.u` form) { // SRA16.u
 *     res[15:-1] = SE17(Rs1.H[x][15:sa-1]) + 1;
 *     Rd.H[x] = res[15:0];
 *   } else { // SRA16
 *     Rd.H[x] = SE16(Rs1.H[x][15:sa])
 *   }
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SRA16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("sra16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.128.1. SRA16 ===== */

/* ===== Inline Function Start for 3.128.2. SRA16.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_SHIFT
 * \brief SRA16.u (SIMD 16-bit Rounding Shift Right Arithmetic)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SRA16 Rd, Rs1, Rs2
 * SRA16.u Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit element arithmetic right shift operations simultaneously. The shift amount is a
 * variable from a GPR. The `.u` form performs additional rounding up operations on the shifted
 * results.
 *
 * **Description**:\n
 * The 16-bit data elements in Rs1 are right-shifted arithmetically, that is, the shifted out
 * bits are filled with the sign-bit of the data elements. The shift amount is specified by the low-order
 * 4-bits of the value in the Rs2 register. For the rounding operation of the `.u` form, a value of 1 is
 * added to the most significant discarded bit of each 16-bit data element to calculate the final results.
 * And the results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * sa = Rs2[3:0];
 * if (sa != 0) {
 *   if (`.u` form) { // SRA16.u
 *     res[15:-1] = SE17(Rs1.H[x][15:sa-1]) + 1;
 *     Rd.H[x] = res[15:0];
 *   } else { // SRA16
 *     Rd.H[x] = SE16(Rs1.H[x][15:sa])
 *   }
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SRA16_U(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("sra16.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.128.2. SRA16.u ===== */

/* ===== Inline Function Start for 3.129.1. SRAI16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_SHIFT
 * \brief SRAI16 (SIMD 16-bit Shift Right Arithmetic Immediate)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SRAI16 Rd, Rs1, imm4u
 * SRAI16.u Rd, Rs1, imm4u
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit elements arithmetic right shift operations simultaneously. The shift amount is
 * an immediate value. The `.u` form performs additional rounding up operations on the shifted
 * results.
 *
 * **Description**:\n
 * The 16-bit data elements in Rs1 are right-shifted arithmetically, that is, the shifted out
 * bits are filled with the sign-bit of the 16-bit data elements. The shift amount is specified by the
 * imm4u constant. For the rounding operation of the `.u` form, a value of 1 is added to the most
 * significant discarded bit of each 16-bit data to calculate the final results. And the results are written
 * to Rd.
 *
 * **Operations**:\n
 * ~~~
 * sa = imm4u[3:0];
 * if (sa > 0) {
 *   if (`.u` form) { // SRAI16.u
 *     res[15:-1] = SE17(Rs1.H[x][15:sa-1]) + 1;
 *     Rd.H[x] = res[15:0];
 *   } else { // SRAI16
 *     Rd.H[x] = SE16(Rs1.H[x][15:sa]);
 *   }
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SRAI16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("srai16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.129.1. SRAI16 ===== */

/* ===== Inline Function Start for 3.129.2. SRAI16.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_SHIFT
 * \brief SRAI16.u (SIMD 16-bit Rounding Shift Right Arithmetic Immediate)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SRAI16 Rd, Rs1, imm4u
 * SRAI16.u Rd, Rs1, imm4u
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit elements arithmetic right shift operations simultaneously. The shift amount is
 * an immediate value. The `.u` form performs additional rounding up operations on the shifted
 * results.
 *
 * **Description**:\n
 * The 16-bit data elements in Rs1 are right-shifted arithmetically, that is, the shifted out
 * bits are filled with the sign-bit of the 16-bit data elements. The shift amount is specified by the
 * imm4u constant. For the rounding operation of the `.u` form, a value of 1 is added to the most
 * significant discarded bit of each 16-bit data to calculate the final results. And the results are written
 * to Rd.
 *
 * **Operations**:\n
 * ~~~
 * sa = imm4u[3:0];
 * if (sa > 0) {
 *   if (`.u` form) { // SRAI16.u
 *     res[15:-1] = SE17(Rs1.H[x][15:sa-1]) + 1;
 *     Rd.H[x] = res[15:0];
 *   } else { // SRAI16
 *     Rd.H[x] = SE16(Rs1.H[x][15:sa]);
 *   }
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SRAI16_U(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("srai16.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.129.2. SRAI16.u ===== */

/* ===== Inline Function Start for 3.130.1. SRL8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_SHIFT
 * \brief SRL8 (SIMD 8-bit Shift Right Logical)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SRL8 Rt, Ra, Rb
 * SRL8.u Rt, Ra, Rb
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit elements logical right shift operations simultaneously. The shift amount is a
 * variable from a GPR. The `.u` form performs additional rounding up operations on the shifted
 * results.
 *
 * **Description**:\n
 * The 8-bit data elements in Rs1 are right-shifted logically, that is, the shifted out bits are
 * filled with zero. The shift amount is specified by the low-order 3-bits of the value in the Rs2 register.
 * For the rounding operation of the `.u` form, a value of 1 is added to the most significant discarded
 * bit of each 8-bit data element to calculate the final results. And the results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * sa = Rs2[2:0];
 * if (sa > 0) {
 *   if (`.u` form) { // SRL8.u
 *     res[8:0] = ZE9(Rs1.B[x][7:sa-1]) + 1;
 *     Rd.B[x] = res[8:1];
 *   } else { // SRL8
 *     Rd.B[x] = ZE8(Rs1.B[x][7:sa]);
 *   }
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SRL8(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("srl8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.130.1. SRL8 ===== */

/* ===== Inline Function Start for 3.130.2. SRL8.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_SHIFT
 * \brief SRL8.u (SIMD 8-bit Rounding Shift Right Logical)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SRL8 Rt, Ra, Rb
 * SRL8.u Rt, Ra, Rb
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit elements logical right shift operations simultaneously. The shift amount is a
 * variable from a GPR. The `.u` form performs additional rounding up operations on the shifted
 * results.
 *
 * **Description**:\n
 * The 8-bit data elements in Rs1 are right-shifted logically, that is, the shifted out bits are
 * filled with zero. The shift amount is specified by the low-order 3-bits of the value in the Rs2 register.
 * For the rounding operation of the `.u` form, a value of 1 is added to the most significant discarded
 * bit of each 8-bit data element to calculate the final results. And the results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * sa = Rs2[2:0];
 * if (sa > 0) {
 *   if (`.u` form) { // SRL8.u
 *     res[8:0] = ZE9(Rs1.B[x][7:sa-1]) + 1;
 *     Rd.B[x] = res[8:1];
 *   } else { // SRL8
 *     Rd.B[x] = ZE8(Rs1.B[x][7:sa]);
 *   }
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SRL8_U(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("srl8.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.130.2. SRL8.u ===== */

/* ===== Inline Function Start for 3.131.1. SRLI8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_SHIFT
 * \brief SRLI8 (SIMD 8-bit Shift Right Logical Immediate)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SRLI8 Rt, Ra, imm3u
 * SRLI8.u Rt, Ra, imm3u
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit elements logical right shift operations simultaneously. The shift amount is an
 * immediate value. The `.u` form performs additional rounding up operations on the shifted results.
 *
 * **Description**:\n
 * The 8-bit data elements in Rs1 are right-shifted logically, that is, the shifted out bits are
 * filled with zero. The shift amount is specified by the imm3u constant. For the rounding operation of
 * the `.u` form, a value of 1 is added to the most significant discarded bit of each 8-bit data element to
 * calculate the final results. And the results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * sa = imm3u[2:0];
 * if (sa > 0) {
 *   if (`.u` form) { // SRLI8.u
 *     res[8:0] = ZE9(Rs1.B[x][7:sa-1]) + 1;
 *     Rd.B[x] = res[8:1];
 *   } else { // SRLI8
 *     Rd.B[x] = ZE8(Rs1.B[x][7:sa]);
 *   }
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SRLI8(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("srli8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.131.1. SRLI8 ===== */

/* ===== Inline Function Start for 3.131.2. SRLI8.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_SHIFT
 * \brief SRLI8.u (SIMD 8-bit Rounding Shift Right Logical Immediate)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SRLI8 Rt, Ra, imm3u
 * SRLI8.u Rt, Ra, imm3u
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit elements logical right shift operations simultaneously. The shift amount is an
 * immediate value. The `.u` form performs additional rounding up operations on the shifted results.
 *
 * **Description**:\n
 * The 8-bit data elements in Rs1 are right-shifted logically, that is, the shifted out bits are
 * filled with zero. The shift amount is specified by the imm3u constant. For the rounding operation of
 * the `.u` form, a value of 1 is added to the most significant discarded bit of each 8-bit data element to
 * calculate the final results. And the results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * sa = imm3u[2:0];
 * if (sa > 0) {
 *   if (`.u` form) { // SRLI8.u
 *     res[8:0] = ZE9(Rs1.B[x][7:sa-1]) + 1;
 *     Rd.B[x] = res[8:1];
 *   } else { // SRLI8
 *     Rd.B[x] = ZE8(Rs1.B[x][7:sa]);
 *   }
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SRLI8_U(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("srli8.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.131.2. SRLI8.u ===== */

/* ===== Inline Function Start for 3.132.1. SRL16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_SHIFT
 * \brief SRL16 (SIMD 16-bit Shift Right Logical)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SRL16 Rt, Ra, Rb
 *  SRL16.u Rt, Ra, Rb
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit elements logical right shift operations simultaneously. The shift amount is a variable from a GPR. The `.u` form performs additional rounding upoperations on the shifted results.
 *
 * **Description**:\n
 * The 16-bit data elements in Rs1 are right-shifted logically, that is, the shifted out bits
 * are filled with zero. The shift amount is specified by the low-order 4-bits of the value in the Rs2
 * register. For the rounding operation of the `.u` form, a value of 1 is added to the most significant
 * discarded bit of each 16-bit data element to calculate the final results. And the results are written to
 * Rd.
 *
 * **Operations**:\n
 * ~~~
 * sa = Rs2[3:0];
 * if (sa > 0) {
 *   if (`.u` form) { // SRL16.u
 *     res[16:0] = ZE17(Rs1.H[x][15:sa-1]) + 1;
 *     Rd.H[x] = res[16:1];
 *   } else { // SRL16
 *     Rd.H[x] = ZE16(Rs1.H[x][15:sa]);
 *   }
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SRL16(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("srl16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.132.1. SRL16 ===== */

/* ===== Inline Function Start for 3.132.2. SRL16.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_SHIFT
 * \brief SRL16.u (SIMD 16-bit Rounding Shift Right Logical)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SRL16 Rt, Ra, Rb
 *  SRL16.u Rt, Ra, Rb
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit elements logical right shift operations simultaneously. The shift amount is a variable from a GPR. The `.u` form performs additional rounding upoperations on the shifted results.
 *
 * **Description**:\n
 * The 16-bit data elements in Rs1 are right-shifted logically, that is, the shifted out bits
 * are filled with zero. The shift amount is specified by the low-order 4-bits of the value in the Rs2
 * register. For the rounding operation of the `.u` form, a value of 1 is added to the most significant
 * discarded bit of each 16-bit data element to calculate the final results. And the results are written to
 * Rd.
 *
 * **Operations**:\n
 * ~~~
 * sa = Rs2[3:0];
 * if (sa > 0) {
 *   if (`.u` form) { // SRL16.u
 *     res[16:0] = ZE17(Rs1.H[x][15:sa-1]) + 1;
 *     Rd.H[x] = res[16:1];
 *   } else { // SRL16
 *     Rd.H[x] = ZE16(Rs1.H[x][15:sa]);
 *   }
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SRL16_U(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("srl16.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.132.2. SRL16.u ===== */

/* ===== Inline Function Start for 3.133.1. SRLI16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_SHIFT
 * \brief SRLI16 (SIMD 16-bit Shift Right Logical Immediate)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SRLI16 Rt, Ra, imm4u
 * SRLI16.u Rt, Ra, imm4u
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit elements logical right shift operations simultaneously. The shift amount is an
 * immediate value. The `.u` form performs additional rounding up operations on the shifted results.
 *
 * **Description**:\n
 * The 16-bit data elements in Rs1 are right-shifted logically, that is, the shifted out bits
 * are filled with zero. The shift amount is specified by the imm4u constant. For the rounding
 * operation of the `.u` form, a value of 1 is added to the most significant discarded bit of each 16-bit
 * data element to calculate the final results. And the results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * sa = imm4u;
 * if (sa > 0) {
 *   if (`.u` form) { // SRLI16.u
 *     res[16:0] = ZE17(Rs1.H[x][15:sa-1]) + 1;
 *     Rd.H[x] = res[16:1];
 *   } else { // SRLI16
 *     Rd.H[x] = ZE16(Rs1.H[x][15:sa]);
 *   }
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SRLI16(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("srli16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.133.1. SRLI16 ===== */

/* ===== Inline Function Start for 3.133.2. SRLI16.u ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_SHIFT
 * \brief SRLI16.u (SIMD 16-bit Rounding Shift Right Logical Immediate)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SRLI16 Rt, Ra, imm4u
 * SRLI16.u Rt, Ra, imm4u
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit elements logical right shift operations simultaneously. The shift amount is an
 * immediate value. The `.u` form performs additional rounding up operations on the shifted results.
 *
 * **Description**:\n
 * The 16-bit data elements in Rs1 are right-shifted logically, that is, the shifted out bits
 * are filled with zero. The shift amount is specified by the imm4u constant. For the rounding
 * operation of the `.u` form, a value of 1 is added to the most significant discarded bit of each 16-bit
 * data element to calculate the final results. And the results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * sa = imm4u;
 * if (sa > 0) {
 *   if (`.u` form) { // SRLI16.u
 *     res[16:0] = ZE17(Rs1.H[x][15:sa-1]) + 1;
 *     Rd.H[x] = res[16:1];
 *   } else { // SRLI16
 *     Rd.H[x] = ZE16(Rs1.H[x][15:sa]);
 *   }
 * } else {
 *   Rd = Rs1;
 * }
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SRLI16_U(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("srli16.u %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.133.2. SRLI16.u ===== */

/* ===== Inline Function Start for 3.134. STAS16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief STAS16 (SIMD 16-bit Straight Addition & Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * STAS16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit integer element addition and 16-bit integer element subtraction in a 32-bit
 * chunk simultaneously. Operands are from corresponding positions in 32-bit chunks.
 *
 * **Description**:\n
 * This instruction adds the 16-bit integer element in [31:16] of 32-bit chunks in Rs1 with
 * the 16-bit integer element in [31:16] of 32-bit chunks in Rs2, and writes the result to [31:16] of 32-bit
 * chunks in Rd; at the same time, it subtracts the 16-bit integer element in [15:0] of 32-bit chunks in
 * Rs2 from the 16-bit integer element in [15:0] of 32-bit chunks, and writes the result to [15:0] of 32-
 * bit chunks in Rd.
 *
 * **Note**:\n
 * This instruction can be used for either signed or unsigned operations.
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:16] = Rs1.W[x][31:16] + Rs2.W[x][31:16];
 * Rd.W[x][15:0] = Rs1.W[x][15:0] - Rs2.W[x][15:0];
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_STAS16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("stas16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.134. STAS16 ===== */

/* ===== Inline Function Start for 3.135. STSA16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief STSA16 (SIMD 16-bit Straight Subtraction & Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * STSA16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit integer element subtraction and 16-bit integer element addition in a 32-bit
 * chunk simultaneously. Operands are from corresponding positions in 32-bit chunks.
 *
 * **Description**:\n
 * This instruction subtracts the 16-bit integer element in [31:16] of 32-bit chunks in Rs2
 * from the 16-bit integer element in [31:16] of 32-bit chunks in Rs1, and writes the result to [31:16] of
 * 32-bit chunks in Rd; at the same time, it adds the 16-bit integer element in [15:0] of 32-bit chunks in
 * Rs2 with the 16-bit integer element in [15:0] of 32-bit chunks in Rs1, and writes the result to [15:0] of
 * 32-bit chunks in Rd.
 *
 * **Note**:\n
 * This instruction can be used for either signed or unsigned operations.
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:16] = Rs1.W[x][31:16] - Rs2.W[x][31:16];
 * Rd.W[x][15:0] = Rs1.W[x][15:0] + Rs2.W[x][15:0];
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_STSA16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("stsa16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.135. STSA16 ===== */

/* ===== Inline Function Start for 3.136. SUB8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_ADDSUB
 * \brief SUB8 (SIMD 8-bit Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SUB8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit integer element subtractions simultaneously.
 *
 * **Description**:\n
 * This instruction subtracts the 8-bit integer elements in Rs2 from the 8-bit integer
 * elements in Rs1, and then writes the result to Rd.
 *
 * **Note**:\n
 * This instruction can be used for either signed or unsigned subtraction.
 *
 * **Operations**:\n
 * ~~~
 * Rd.B[x] = Rs1.B[x] - Rs2.B[x];
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SUB8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("sub8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.136. SUB8 ===== */

/* ===== Inline Function Start for 3.137. SUB16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief SUB16 (SIMD 16-bit Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * SUB16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit integer element subtractions simultaneously.
 *
 * **Description**:\n
 * This instruction subtracts the 16-bit integer elements in Rs2 from the 16-bit integer
 * elements in Rs1, and then writes the result to Rd.
 *
 * **Note**:\n
 * This instruction can be used for either signed or unsigned subtraction.
 *
 * **Operations**:\n
 * ~~~
 * Rd.H[x] = Rs1.H[x] - Rs2.H[x];
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SUB16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("sub16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.137. SUB16 ===== */

/* ===== Inline Function Start for 3.138. SUB64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_64B_ADDSUB
 * \brief SUB64 (64-bit Subtraction)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * SUB64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Perform a 64-bit signed or unsigned integer subtraction.
 *
 * **RV32 Description**:\n
 * This instruction subtracts the 64-bit integer of an even/odd pair of registers
 * specified by Rs2(4,1) from the 64-bit integer of an even/odd pair of registers specified by Rs1(4,1),
 * and then writes the 64-bit result to an even/odd pair of registers specified by Rd(4,1).
 * Rx(4,1), i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the operand and the even `2d`
 * register of the pair contains the low 32-bit of the operand.
 *
 * **RV64 Description**:\n
 * This instruction subtracts the 64-bit integer of Rs2 from the 64-bit integer of Rs1,
 * and then writes the 64-bit result to Rd.
 *
 * **Note**:\n
 * This instruction can be used for either signed or unsigned subtraction.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * a_L = CONCAT(Rs1(4,1),1'b0); a_H = CONCAT(Rs1(4,1),1'b1);
 * b_L = CONCAT(Rs2(4,1),1'b0); b_H = CONCAT(Rs2(4,1),1'b1);
 * R[t_H].R[t_L] = R[a_H].R[a_L] - R[b_H].R[b_L];
 * * RV64:
 * Rd = Rs1 - Rs2;
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_SUB64(unsigned long long a, unsigned long long b)
{
    unsigned long long result;
    __ASM volatile("sub64 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.138. SUB64 ===== */

/* ===== Inline Function Start for 3.139.1. SUNPKD810 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_UNPACK
 * \brief SUNPKD810 (Signed Unpacking Bytes 1 & 0)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * SUNPKD8xy Rd, Rs1
 * xy = {10, 20, 30, 31, 32}
 * ~~~
 *
 * **Purpose**:\n
 * Unpack byte *x and byte y* of 32-bit chunks in a register into two 16-bit signed halfwords
 * of 32-bit chunks in a register.
 *
 * **Description**:\n
 * For the `SUNPKD8(x)(*y*)` instruction, it unpacks byte *x and byte y* of 32-bit chunks in Rs1 into
 * two 16-bit signed halfwords and writes the results to the top part and the bottom part of 32-bit
 * chunks in Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[m].H[1] = SE16(Rs1.W[m].B[x])
 * Rd.W[m].H[0] = SE16(Rs1.W[m].B[y])
 * // SUNPKD810, x=1,y=0
 * // SUNPKD820, x=2,y=0
 * // SUNPKD830, x=3,y=0
 * // SUNPKD831, x=3,y=1
 * // SUNPKD832, x=3,y=2
 * for RV32: m=0,
 * for RV64: m=1...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SUNPKD810(unsigned long a)
{
    unsigned long result;
    __ASM volatile("sunpkd810 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.139.1. SUNPKD810 ===== */

/* ===== Inline Function Start for 3.139.2. SUNPKD820 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_UNPACK
 * \brief SUNPKD820 (Signed Unpacking Bytes 2 & 0)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * SUNPKD8xy Rd, Rs1
 * xy = {10, 20, 30, 31, 32}
 * ~~~
 *
 * **Purpose**:\n
 * Unpack byte *x and byte y* of 32-bit chunks in a register into two 16-bit signed halfwords
 * of 32-bit chunks in a register.
 *
 * **Description**:\n
 * For the `SUNPKD8(x)(*y*)` instruction, it unpacks byte *x and byte y* of 32-bit chunks in Rs1 into
 * two 16-bit signed halfwords and writes the results to the top part and the bottom part of 32-bit
 * chunks in Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[m].H[1] = SE16(Rs1.W[m].B[x])
 * Rd.W[m].H[0] = SE16(Rs1.W[m].B[y])
 * // SUNPKD810, x=1,y=0
 * // SUNPKD820, x=2,y=0
 * // SUNPKD830, x=3,y=0
 * // SUNPKD831, x=3,y=1
 * // SUNPKD832, x=3,y=2
 * for RV32: m=0,
 * for RV64: m=1...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SUNPKD820(unsigned long a)
{
    unsigned long result;
    __ASM volatile("sunpkd820 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.139.2. SUNPKD820 ===== */

/* ===== Inline Function Start for 3.139.3. SUNPKD830 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_UNPACK
 * \brief SUNPKD830 (Signed Unpacking Bytes 3 & 0)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * SUNPKD8xy Rd, Rs1
 * xy = {10, 20, 30, 31, 32}
 * ~~~
 *
 * **Purpose**:\n
 * Unpack byte *x and byte y* of 32-bit chunks in a register into two 16-bit signed halfwords
 * of 32-bit chunks in a register.
 *
 * **Description**:\n
 * For the `SUNPKD8(x)(*y*)` instruction, it unpacks byte *x and byte y* of 32-bit chunks in Rs1 into
 * two 16-bit signed halfwords and writes the results to the top part and the bottom part of 32-bit
 * chunks in Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[m].H[1] = SE16(Rs1.W[m].B[x])
 * Rd.W[m].H[0] = SE16(Rs1.W[m].B[y])
 * // SUNPKD810, x=1,y=0
 * // SUNPKD820, x=2,y=0
 * // SUNPKD830, x=3,y=0
 * // SUNPKD831, x=3,y=1
 * // SUNPKD832, x=3,y=2
 * for RV32: m=0,
 * for RV64: m=1...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SUNPKD830(unsigned long a)
{
    unsigned long result;
    __ASM volatile("sunpkd830 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.139.3. SUNPKD830 ===== */

/* ===== Inline Function Start for 3.139.4. SUNPKD831 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_UNPACK
 * \brief SUNPKD831 (Signed Unpacking Bytes 3 & 1)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * SUNPKD8xy Rd, Rs1
 * xy = {10, 20, 30, 31, 32}
 * ~~~
 *
 * **Purpose**:\n
 * Unpack byte *x and byte y* of 32-bit chunks in a register into two 16-bit signed halfwords
 * of 32-bit chunks in a register.
 *
 * **Description**:\n
 * For the `SUNPKD8(x)(*y*)` instruction, it unpacks byte *x and byte y* of 32-bit chunks in Rs1 into
 * two 16-bit signed halfwords and writes the results to the top part and the bottom part of 32-bit
 * chunks in Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[m].H[1] = SE16(Rs1.W[m].B[x])
 * Rd.W[m].H[0] = SE16(Rs1.W[m].B[y])
 * // SUNPKD810, x=1,y=0
 * // SUNPKD820, x=2,y=0
 * // SUNPKD830, x=3,y=0
 * // SUNPKD831, x=3,y=1
 * // SUNPKD832, x=3,y=2
 * for RV32: m=0,
 * for RV64: m=1...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SUNPKD831(unsigned long a)
{
    unsigned long result;
    __ASM volatile("sunpkd831 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.139.4. SUNPKD831 ===== */

/* ===== Inline Function Start for 3.139.5. SUNPKD832 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_UNPACK
 * \brief SUNPKD832 (Signed Unpacking Bytes 3 & 2)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * SUNPKD8xy Rd, Rs1
 * xy = {10, 20, 30, 31, 32}
 * ~~~
 *
 * **Purpose**:\n
 * Unpack byte *x and byte y* of 32-bit chunks in a register into two 16-bit signed halfwords
 * of 32-bit chunks in a register.
 *
 * **Description**:\n
 * For the `SUNPKD8(x)(*y*)` instruction, it unpacks byte *x and byte y* of 32-bit chunks in Rs1 into
 * two 16-bit signed halfwords and writes the results to the top part and the bottom part of 32-bit
 * chunks in Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[m].H[1] = SE16(Rs1.W[m].B[x])
 * Rd.W[m].H[0] = SE16(Rs1.W[m].B[y])
 * // SUNPKD810, x=1,y=0
 * // SUNPKD820, x=2,y=0
 * // SUNPKD830, x=3,y=0
 * // SUNPKD831, x=3,y=1
 * // SUNPKD832, x=3,y=2
 * for RV32: m=0,
 * for RV64: m=1...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SUNPKD832(unsigned long a)
{
    unsigned long result;
    __ASM volatile("sunpkd832 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.139.5. SUNPKD832 ===== */

/* ===== Inline Function Start for 3.140. SWAP8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_MISC
 * \brief SWAP8 (Swap Byte within Halfword)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * SWAP8 Rd, Rs1
 * ~~~
 *
 * **Purpose**:\n
 * Swap the bytes within each halfword of a register.
 *
 * **Description**:\n
 * This instruction swaps the bytes within each halfword of Rs1 and writes the result to
 * Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.H[x] = CONCAT(Rs1.H[x][7:0],Rs1.H[x][15:8]);
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SWAP8(unsigned long a)
{
    unsigned long result;
    __ASM volatile("swap8 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.140. SWAP8 ===== */

/* ===== Inline Function Start for 3.141. SWAP16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_MISC
 * \brief SWAP16 (Swap Halfword within Word)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * SWAP16 Rd, Rs1
 * ~~~
 *
 * **Purpose**:\n
 * Swap the 16-bit halfwords within each word of a register.
 *
 * **Description**:\n
 * This instruction swaps the 16-bit halfwords within each word of Rs1 and writes the
 * result to Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x] = CONCAT(Rs1.W[x][15:0],Rs1.H[x][31:16]);
 * for RV32: x=0,
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_SWAP16(unsigned long a)
{
    unsigned long result;
    __ASM volatile("swap16 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.141. SWAP16 ===== */

/* ===== Inline Function Start for 3.142. UCLIP8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_MISC
 * \brief UCLIP8 (SIMD 8-bit Unsigned Clip Value)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UCLIP8 Rt, Ra, imm3u
 * ~~~
 *
 * **Purpose**:\n
 * Limit the 8-bit signed elements of a register into an unsigned range simultaneously.
 *
 * **Description**:\n
 * This instruction limits the 8-bit signed elements stored in Rs1 into an unsigned integer
 * range between 2^imm3u-1 and 0, and writes the limited results to Rd. For example, if imm3u is 3, the 8-
 * bit input values should be saturated between 7 and 0. If saturation is performed, set OV bit to 1.
 *
 * **Operations**:\n
 * ~~~
 * src = Rs1.H[x];
 * if (src > (2^imm3u)-1) {
 *   src = (2^imm3u)-1;
 *   OV = 1;
 * } else if (src < 0) {
 *   src = 0;
 *   OV = 1;
 * }
 * Rd.H[x] = src;
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UCLIP8(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("uclip8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.142. UCLIP8 ===== */

/* ===== Inline Function Start for 3.143. UCLIP16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_MISC
 * \brief UCLIP16 (SIMD 16-bit Unsigned Clip Value)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UCLIP16 Rt, Ra, imm4u
 * ~~~
 *
 * **Purpose**:\n
 * Limit the 16-bit signed elements of a register into an unsigned range simultaneously.
 *
 * **Description**:\n
 * This instruction limits the 16-bit signed elements stored in Rs1 into an unsigned
 * integer range between 2imm4u-1 and 0, and writes the limited results to Rd. For example, if imm4u is
 * 3, the 16-bit input values should be saturated between 7 and 0. If saturation is performed, set OV bit
 * to 1.
 *
 * **Operations**:\n
 * ~~~
 * src = Rs1.H[x];
 * if (src > (2^imm4u)-1) {
 *   src = (2^imm4u)-1;
 *   OV = 1;
 * } else if (src < 0) {
 *   src = 0;
 *   OV = 1;
 * }
 * Rd.H[x] = src;
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UCLIP16(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("uclip16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.143. UCLIP16 ===== */

/* ===== Inline Function Start for 3.144. UCLIP32 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_PART_SIMD_MISC
 * \brief UCLIP32 (SIMD 32-bit Unsigned Clip Value)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UCLIP32 Rd, Rs1, imm5u[4:0]
 * ~~~
 *
 * **Purpose**:\n
 * Limit the 32-bit signed integer elements of a register into an unsigned range
 * simultaneously.
 *
 * **Description**:\n
 * This instruction limits the 32-bit signed integer elements stored in Rs1 into an
 * unsigned integer range between 2imm5u-1 and 0, and writes the limited results to Rd. For example, if
 * imm5u is 3, the 32-bit input values should be saturated between 7 and 0. If saturation is performed,
 * set OV bit to 1.
 *
 * **Operations**:\n
 * ~~~
 * src = Rs1.W[x];
 * if (src > (2^imm5u)-1) {
 *   src = (2^imm5u)-1;
 *   OV = 1;
 * } else if (src < 0) {
 *   src = 0;
 *   OV = 1;
 * }
 * Rd.W[x] = src
 * for RV32: x=0,
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UCLIP32(unsigned long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("uclip32 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.144. UCLIP32 ===== */

/* ===== Inline Function Start for 3.145. UCMPLE8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_CMP
 * \brief UCMPLE8 (SIMD 8-bit Unsigned Compare Less Than & Equal)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UCMPLE8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit unsigned integer elements less than & equal comparisons simultaneously.
 *
 * **Description**:\n
 * This instruction compares the 8-bit unsigned integer elements in Rs1 with the 8-bit
 * unsigned integer elements in Rs2 to see if the one in Rs1 is less than or equal to the one in Rs2. If it
 * is true, the result is 0xFF; otherwise, the result is 0x0. The four comparison results are written to
 * Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.B[x] = (Rs1.B[x] <=u Rs2.B[x])? 0xff : 0x0;
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UCMPLE8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("ucmple8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.145. UCMPLE8 ===== */

/* ===== Inline Function Start for 3.146. UCMPLE16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_CMP
 * \brief UCMPLE16 (SIMD 16-bit Unsigned Compare Less Than & Equal)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UCMPLE16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit unsigned integer elements less than & equal comparisons simultaneously.
 *
 * **Description**:\n
 * This instruction compares the 16-bit unsigned integer elements in Rs1 with the 16-bit
 * unsigned integer elements in Rs2 to see if the one in Rs1 is less than or equal to the one in Rs2. If it
 * is true, the result is 0xFFFF; otherwise, the result is 0x0. The element comparison results are
 * written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.H[x] = (Rs1.H[x] <=u Rs2.H[x])? 0xffff : 0x0;
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UCMPLE16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("ucmple16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.146. UCMPLE16 ===== */

/* ===== Inline Function Start for 3.147. UCMPLT8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_CMP
 * \brief UCMPLT8 (SIMD 8-bit Unsigned Compare Less Than)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UCMPLT8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit unsigned integer elements less than comparisons simultaneously.
 *
 * **Description**:\n
 * This instruction compares the 8-bit unsigned integer elements in Rs1 with the 8-bit
 * unsigned integer elements in Rs2 to see if the one in Rs1 is less than the one in Rs2. If it is true, the
 * result is 0xFF; otherwise, the result is 0x0. The element comparison results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.B[x] = (Rs1.B[x] <u Rs2.B[x])? 0xff : 0x0;
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UCMPLT8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("ucmplt8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.147. UCMPLT8 ===== */

/* ===== Inline Function Start for 3.148. UCMPLT16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_CMP
 * \brief UCMPLT16 (SIMD 16-bit Unsigned Compare Less Than)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UCMPLT16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit unsigned integer elements less than comparisons simultaneously.
 *
 * **Description**:\n
 * This instruction compares the 16-bit unsigned integer elements in Rs1 with the 16-bit
 * unsigned integer elements in Rs2 to see if the one in Rs1 is less than the one in Rs2. If it is true, the
 * result is 0xFFFF; otherwise, the result is 0x0. The element comparison results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.H[x] = (Rs1.H[x] <u Rs2.H[x])? 0xffff : 0x0;
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UCMPLT16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("ucmplt16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.148. UCMPLT16 ===== */

/* ===== Inline Function Start for 3.149. UKADD8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_ADDSUB
 * \brief UKADD8 (SIMD 8-bit Unsigned Saturating Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UKADD8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit unsigned integer element saturating additions simultaneously.
 *
 * **Description**:\n
 * This instruction adds the 8-bit unsigned integer elements in Rs1 with the 8-bit
 * unsigned integer elements in Rs2. If any of the results are beyond the 8-bit unsigned number range
 * (0 <= RES <= 28-1), they are saturated to the range and the OV bit is set to 1. The saturated results are
 * written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * res[x] = Rs1.B[x] + Rs2.B[x];
 * if (res[x] > (2^8)-1) {
 *   res[x] = (2^8)-1;
 *   OV = 1;
 * }
 * Rd.B[x] = res[x];
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UKADD8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("ukadd8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.149. UKADD8 ===== */

/* ===== Inline Function Start for 3.150. UKADD16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief UKADD16 (SIMD 16-bit Unsigned Saturating Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UKADD16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit unsigned integer element saturating additions simultaneously.
 *
 * **Description**:\n
 * This instruction adds the 16-bit unsigned integer elements in Rs1 with the 16-bit
 * unsigned integer elements in Rs2. If any of the results are beyond the 16-bit unsigned number
 * range (0 <= RES <= 2^16-1), they are saturated to the range and the OV bit is set to 1. The saturated
 * results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * res[x] = Rs1.H[x] + Rs2.H[x];
 * if (res[x] > (2^16)-1) {
 *   res[x] = (2^16)-1;
 *   OV = 1;
 * }
 * Rd.H[x] = res[x];
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UKADD16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("ukadd16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.150. UKADD16 ===== */

/* ===== Inline Function Start for 3.151. UKADD64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_64B_ADDSUB
 * \brief UKADD64 (64-bit Unsigned Saturating Addition)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * UKADD64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Add two 64-bit unsigned integers. The result is saturated to the U64 range.
 *
 * **RV32 Description**:\n
 * This instruction adds the 64-bit unsigned integer of an even/odd pair of registers
 * specified by Rs1(4,1) with the 64-bit unsigned integer of an even/odd pair of registers specified by
 * Rs2(4,1). If the 64-bit result is beyond the U64 number range (0 <= U64 <= 2^64-1), it is saturated to the
 * range and the OV bit is set to 1. The saturated result is written to an even/odd pair of registers
 * specified by Rd(4,1).
 * Rx(4,1), i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 *
 * **RV64 Description**:\n
 * This instruction adds the 64-bit unsigned integer in Rs1 with the 64-bit unsigned
 * integer in Rs2. If the 64-bit result is beyond the U64 number range (0 <= U64 <= 2^64-1), it is saturated to
 * the range and the OV bit is set to 1. The saturated result is written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * t_L = CONCAT(Rt(4,1),1'b0); t_H = CONCAT(Rt(4,1),1'b1);
 * a_L = CONCAT(Ra(4,1),1'b0); a_H = CONCAT(Ra(4,1),1'b1);
 * b_L = CONCAT(Rb(4,1),1'b0); b_H = CONCAT(Rb(4,1),1'b1);
 * result = R[a_H].R[a_L] + R[b_H].R[b_L];
 * if (result > (2^64)-1) {
 *   result = (2^64)-1; OV = 1;
 * }
 * R[t_H].R[t_L] = result;
 * * RV64:
 * result = Rs1 + Rs2;
 * if (result > (2^64)-1) {
 *   result = (2^64)-1; OV = 1;
 * }
 * Rd = result;
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_UKADD64(unsigned long long a, unsigned long long b)
{
    unsigned long long result;
    __ASM volatile("ukadd64 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.151. UKADD64 ===== */

/* ===== Inline Function Start for 3.152. UKADDH ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q15_SAT_ALU
 * \brief UKADDH (Unsigned Addition with U16 Saturation)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * UKADDH Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Add the unsigned lower 32-bit content of two registers with U16 saturation.
 *
 * **Description**:\n
 * The unsigned lower 32-bit content of Rs1 is added with the unsigned lower 32-bit
 * content of Rs2. And the result is saturated to the 16-bit unsigned integer range of [0, 2^16-1] and then
 * sign-extended and written to Rd. If saturation happens, this instruction sets the OV flag.
 *
 * **Operations**:\n
 * ~~~
 * tmp = Rs1.W[0] + Rs2.W[0];
 * if (tmp > (2^16)-1) {
 *   tmp = (2^16)-1;
 *   OV = 1;
 * }
 * Rd = SE(tmp[15:0]);
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UKADDH(unsigned int a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("ukaddh %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.152. UKADDH ===== */

/* ===== Inline Function Start for 3.153. UKADDW ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q31_SAT_ALU
 * \brief UKADDW (Unsigned Addition with U32 Saturation)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * UKADDW Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Add the unsigned lower 32-bit content of two registers with U32 saturation.
 *
 * **Description**:\n
 * The unsigned lower 32-bit content of Rs1 is added with the unsigned lower 32-bit
 * content of Rs2. And the result is saturated to the 32-bit unsigned integer range of [0, 2^32-1] and then
 * sign-extended and written to Rd. If saturation happens, this instruction sets the OV flag.
 *
 * **Operations**:\n
 * ~~~
 * tmp = Rs1.W[0] + Rs2.W[0];
 * if (tmp > (2^32)-1) {
 *   tmp[31:0] = (2^32)-1;
 *   OV = 1;
 * }
 * Rd = tmp[31:0]; // RV32
 * Rd = SE(tmp[31:0]); // RV64
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UKADDW(unsigned int a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("ukaddw %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.153. UKADDW ===== */

/* ===== Inline Function Start for 3.154. UKCRAS16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief UKCRAS16 (SIMD 16-bit Unsigned Saturating Cross Addition & Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UKCRAS16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do one 16-bit unsigned integer element saturating addition and one 16-bit unsigned
 * integer element saturating subtraction in a 32-bit chunk simultaneously. Operands are from crossed
 * positions in 32-bit chunks.
 *
 * **Description**:\n
 * This instruction adds the 16-bit unsigned integer element in [31:16] of 32-bit chunks in
 * Rs1 with the 16-bit unsigned integer element in [15:0] of 32-bit chunks in Rs2; at the same time, it
 * subtracts the 16-bit unsigned integer element in [31:16] of 32-bit chunks in Rs2 from the 16-bit
 * unsigned integer element in [15:0] of 32-bit chunks in Rs1. If any of the results are beyond the 16-bit
 * unsigned number range (0 <= RES <= 2^16-1), they are saturated to the range and the OV bit is set to 1.
 * The saturated results are written to [31:16] of 32-bit chunks in Rd for addition and [15:0] of 32-bit
 * chunks in Rd for subtraction.
 *
 * **Operations**:\n
 * ~~~
 * res1 = Rs1.W[x][31:16] + Rs2.W[x][15:0];
 * res2 = Rs1.W[x][15:0] - Rs2.W[x][31:16];
 * if (res1 > (2^16)-1) {
 *   res1 = (2^16)-1;
 *   OV = 1;
 * }
 * if (res2 < 0) {
 *   res2 = 0;
 *   OV = 1;
 * }
 * Rd.W[x][31:16] = res1;
 * Rd.W[x][15:0] = res2;
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UKCRAS16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("ukcras16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.154. UKCRAS16 ===== */

/* ===== Inline Function Start for 3.155. UKCRSA16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief UKCRSA16 (SIMD 16-bit Unsigned Saturating Cross Subtraction & Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UKCRSA16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do one 16-bit unsigned integer element saturating subtraction and one 16-bit unsigned
 * integer element saturating addition in a 32-bit chunk simultaneously. Operands are from crossed
 * positions in 32-bit chunks.
 *
 * **Description**:\n
 * This instruction subtracts the 16-bit unsigned integer element in [15:0] of 32-bit
 * chunks in Rs2 from the 16-bit unsigned integer element in [31:16] of 32-bit chunks in Rs1; at the
 * same time, it adds the 16-bit unsigned integer element in [31:16] of 32-bit chunks in Rs2 with the 16-
 * bit unsigned integer element in [15:0] of 32-bit chunks in Rs1. If any of the results are beyond the
 * 16-bit unsigned number range (0 <= RES <= 2^16-1), they are saturated to the range and the OV bit is set
 * to 1. The saturated results are written to [31:16] of 32-bit chunks in Rd for subtraction and [15:0] of
 * 32-bit chunks in Rd for addition.
 *
 * **Operations**:\n
 * ~~~
 * res1 = Rs1.W[x][31:16] - Rs2.W[x][15:0];
 * res2 = Rs1.W[x][15:0] + Rs2.W[x][31:16];
 * if (res1 < 0) {
 *   res1 = 0;
 *   OV = 1;
 * } else if (res2 > (2^16)-1) {
 *   res2 = (2^16)-1;
 *   OV = 1;
 * }
 * Rd.W[x][31:16] = res1;
 * Rd.W[x][15:0] = res2;
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UKCRSA16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("ukcrsa16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.155. UKCRSA16 ===== */

/* ===== Inline Function Start for 3.156. UKMAR64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_32B_MULT_64B_ADDSUB
 * \brief UKMAR64 (Unsigned Multiply and Saturating Add to 64-Bit Data)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * UKMAR64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the 32-bit unsigned elements in two registers and add the 64-bit multiplication
 * results to the 64-bit unsigned data of a pair of registers (RV32) or a register (RV64). The result is
 * saturated to the U64 range and written back to the pair of registers (RV32) or the register (RV64).
 *
 * **RV32 Description**:\n
 * This instruction multiplies the 32-bit unsigned data of Rs1 with that of Rs2. It
 * adds the 64-bit multiplication result to the 64-bit unsigned data of an even/odd pair of registers
 * specified by Rd(4,1) with unlimited precision. If the 64-bit addition result is beyond the U64 number
 * range (0 <= U64 <= 2^64-1), it is saturated to the range and the OV bit is set to 1. The saturated result is
 * written back to the even/odd pair of registers specified by Rd(4,1).
 * Rx(4,1), i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 *
 * **RV64 Description**:\n
 * This instruction multiplies the 32-bit unsigned elements of Rs1 with that of Rs2.
 * It adds the 64-bit multiplication results to the 64-bit unsigned data in Rd with unlimited precision. If
 * the 64-bit addition result is beyond the U64 number range (0 <= U64 <= 2^64-1), it is saturated to the
 * range and the OV bit is set to 1. The saturated result is written back to Rd.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * result = R[t_H].R[t_L] + (Rs1 * Rs2);
 * if (result > (2^64)-1) {
 *   result = (2^64)-1; OV = 1;
 * }
 * R[t_H].R[t_L] = result;
 * * RV64:
 * // `result` has unlimited precision
 * result = Rd + (Rs1.W[0] u* Rs2.W[0]) + (Rs1.W[1] u* Rs2.W[1]);
 * if (result > (2^64)-1) {
 *   result = (2^64)-1; OV = 1;
 * }
 * Rd = result;
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_UKMAR64(unsigned long long t, unsigned long a, unsigned long b)
{
    __ASM volatile("ukmar64 %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.156. UKMAR64 ===== */

/* ===== Inline Function Start for 3.157. UKMSR64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_32B_MULT_64B_ADDSUB
 * \brief UKMSR64 (Unsigned Multiply and Saturating Subtract from 64-Bit Data)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * UKMSR64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the 32-bit unsigned elements in two registers and subtract the 64-bit
 * multiplication results from the 64-bit unsigned data of a pair of registers (RV32) or a register (RV64).
 * The result is saturated to the U64 range and written back to the pair of registers (RV32) or a register
 * (RV64).
 *
 * **RV32 Description**:\n
 * This instruction multiplies the 32-bit unsigned data of Rs1 with that of Rs2. It
 * subtracts the 64-bit multiplication result from the 64-bit unsigned data of an even/odd pair of
 * registers specified by Rd(4,1) with unlimited precision. If the 64-bit subtraction result is beyond the
 * U64 number range (0 <= U64 <= 2^64-1), it is saturated to the range and the OV bit is set to 1. The
 * saturated result is written back to the even/odd pair of registers specified by Rd(4,1).
 * Rx(4,1), i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 *
 * **RV64 Description**:\n
 * This instruction multiplies the 32-bit unsigned elements of Rs1 with that of Rs2.
 * It subtracts the 64-bit multiplication results from the 64-bit unsigned data of Rd with unlimited
 * precision. If the 64-bit subtraction result is beyond the U64 number range (0 <= U64 <= 2^64-1), it is
 * saturated to the range and the OV bit is set to 1. The saturated result is written back to Rd.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * result = R[t_H].R[t_L] - (Rs1 u* Rs2);
 * if (result < 0) {
 *   result = 0; OV = 1;
 * }
 * R[t_H].R[t_L] = result;
 * * RV64:
 * // `result` has unlimited precision
 * result = Rd - (Rs1.W[0] u* Rs2.W[0]) - (Rs1.W[1] u* Rs2.W[1]);
 * if (result < 0) {
 *   result = 0; OV = 1;
 * }
 * Rd = result;
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_UKMSR64(unsigned long long t, unsigned long a, unsigned long b)
{
    __ASM volatile("ukmsr64 %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.157. UKMSR64 ===== */

/* ===== Inline Function Start for 3.158. UKSTAS16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief UKSTAS16 (SIMD 16-bit Unsigned Saturating Straight Addition & Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UKSTAS16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do one 16-bit unsigned integer element saturating addition and one 16-bit unsigned
 * integer element saturating subtraction in a 32-bit chunk simultaneously. Operands are from
 * corresponding positions in 32-bit chunks.
 *
 * **Description**:\n
 * This instruction adds the 16-bit unsigned integer element in [31:16] of 32-bit chunks in
 * Rs1 with the 16-bit unsigned integer element in [31:16] of 32-bit chunks in Rs2; at the same time, it
 * subtracts the 16-bit unsigned integer element in [15:0] of 32-bit chunks in Rs2 from the 16-bit
 * unsigned integer element in [15:0] of 32-bit chunks in Rs1. If any of the results are beyond the 16-bit
 * unsigned number range (0 <= RES <= 2^16-1), they are saturated to the range and the OV bit is set to 1.
 * The saturated results are written to [31:16] of 32-bit chunks in Rd for addition and [15:0] of 32-bit
 * chunks in Rd for subtraction.
 *
 * **Operations**:\n
 * ~~~
 * res1 = Rs1.W[x][31:16] + Rs2.W[x][31:16];
 * res2 = Rs1.W[x][15:0] - Rs2.W[x][15:0];
 * if (res1 > (2^16)-1) {
 *   res1 = (2^16)-1;
 *   OV = 1;
 * }
 * if (res2 < 0) {
 *   res2 = 0;
 *   OV = 1;
 * }
 * Rd.W[x][31:16] = res1;
 * Rd.W[x][15:0] = res2;
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UKSTAS16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("ukstas16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.158. UKSTAS16 ===== */

/* ===== Inline Function Start for 3.159. UKSTSA16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief UKSTSA16 (SIMD 16-bit Unsigned Saturating Straight Subtraction & Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UKSTSA16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do one 16-bit unsigned integer element saturating subtraction and one 16-bit unsigned
 * integer element saturating addition in a 32-bit chunk simultaneously. Operands are from
 * corresponding positions in 32-bit chunks.
 *
 * **Description**:\n
 * This instruction subtracts the 16-bit unsigned integer element in [31:16] of 32-bit
 * chunks in Rs2 from the 16-bit unsigned integer element in [31:16] of 32-bit chunks in Rs1; at the
 * same time, it adds the 16-bit unsigned integer element in [15:0] of 32-bit chunks in Rs2 with the 16-
 * bit unsigned integer element in [15:0] of 32-bit chunks in Rs1. If any of the results are beyond the
 * 16-bit unsigned number range (0 <= RES <= 2^16-1), they are saturated to the range and the OV bit is set
 * to 1. The saturated results are written to [31:16] of 32-bit chunks in Rd for subtraction and [15:0] of
 * 32-bit chunks in Rd for addition.
 *
 * **Operations**:\n
 * ~~~
 * res1 = Rs1.W[x][31:16] - Rs2.W[x][31:16];
 * res2 = Rs1.W[x][15:0] + Rs2.W[x][15:0];
 * if (res1 < 0) {
 *   res1 = 0;
 *   OV = 1;
 * } else if (res2 > (2^16)-1) {
 *   res2 = (2^16)-1;
 *   OV = 1;
 * }
 * Rd.W[x][31:16] = res1;
 * Rd.W[x][15:0] = res2;
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UKSTSA16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("ukstsa16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.159. UKSTSA16 ===== */

/* ===== Inline Function Start for 3.160. UKSUB8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_ADDSUB
 * \brief UKSUB8 (SIMD 8-bit Unsigned Saturating Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UKSUB8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit unsigned integer elements saturating subtractions simultaneously.
 *
 * **Description**:\n
 * This instruction subtracts the 8-bit unsigned integer elements in Rs2 from the 8-bit
 * unsigned integer elements in Rs1. If any of the results are beyond the 8-bit unsigned number range
 * (0 <= RES <= 28-1), they are saturated to the range and the OV bit is set to 1. The saturated results are
 * written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * res[x] = Rs1.B[x] - Rs2.B[x];
 * if (res[x] < 0) {
 *   res[x] = 0;
 *   OV = 1;
 * }
 * Rd.B[x] = res[x];
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UKSUB8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("uksub8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.160. UKSUB8 ===== */

/* ===== Inline Function Start for 3.161. UKSUB16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief UKSUB16 (SIMD 16-bit Unsigned Saturating Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UKSUB16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit unsigned integer elements saturating subtractions simultaneously.
 *
 * **Description**:\n
 * This instruction subtracts the 16-bit unsigned integer elements in Rs2 from the 16-bit
 * unsigned integer elements in Rs1. If any of the results are beyond the 16-bit unsigned number
 * range (0 <= RES <= 2^16-1), they are saturated to the range and the OV bit is set to 1. The saturated
 * results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * res[x] = Rs1.H[x] - Rs2.H[x];
 * if (res[x] < 0) {
 *   res[x] = 0;
 *   OV = 1;
 * }
 * Rd.H[x] = res[x];
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UKSUB16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("uksub16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.161. UKSUB16 ===== */

/* ===== Inline Function Start for 3.162. UKSUB64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_64B_ADDSUB
 * \brief UKSUB64 (64-bit Unsigned Saturating Subtraction)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * UKSUB64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Perform a 64-bit signed integer subtraction. The result is saturated to the U64 range.
 *
 * **RV32 Description**:\n
 * This instruction subtracts the 64-bit unsigned integer of an even/odd pair of
 * registers specified by Rs2(4,1) from the 64-bit unsigned integer of an even/odd pair of registers
 * specified by Rs1(4,1). If the 64-bit result is beyond the U64 number range (0 <= U64 <= 2^64-1), it is
 * saturated to the range and the OV bit is set to 1. The saturated result is then written to an even/odd
 * pair of registers specified by Rd(4,1).
 * Rx(4,1), i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the operand and the even `2d`
 * register of the pair contains the low 32-bit of the operand.
 *
 * **RV64 Description**:\n
 * This instruction subtracts the 64-bit unsigned integer of Rs2 from the 64-bit
 * unsigned integer of an even/odd pair of Rs1. If the 64-bit result is beyond the U64 number range (0 <=
 * U64 <= 2^64-1), it is saturated to the range and the OV bit is set to 1. The saturated result is then written
 * to Rd.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * a_L = CONCAT(Rs1(4,1),1'b0); a_H = CONCAT(Rs1(4,1),1'b1);
 * b_L = CONCAT(Rs2(4,1),1'b0); b_H = CONCAT(Rs2(4,1),1'b1);
 * result = R[a_H].R[a_L] - R[b_H].R[b_L];
 * if (result < 0) {
 *   result = 0; OV = 1;
 * }
 * R[t_H].R[t_L] = result;
 * * RV64
 * result = Rs1 - Rs2;
 * if (result < 0) {
 *   result = 0; OV = 1;
 * }
 * Rd = result;
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_UKSUB64(unsigned long long a, unsigned long long b)
{
    unsigned long long result;
    __ASM volatile("uksub64 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.162. UKSUB64 ===== */

/* ===== Inline Function Start for 3.163. UKSUBH ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q15_SAT_ALU
 * \brief UKSUBH (Unsigned Subtraction with U16 Saturation)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * UKSUBH Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Subtract the unsigned lower 32-bit content of two registers with U16 saturation.
 *
 * **Description**:\n
 * The unsigned lower 32-bit content of Rs2 is subtracted from the unsigned lower 32-bit
 * content of Rs1. And the result is saturated to the 16-bit unsigned integer range of [0, 2^16-1] and then
 * sign-extended and written to Rd. If saturation happens, this instruction sets the OV flag.
 *
 * **Operations**:\n
 * ~~~
 * tmp = Rs1.W[0] - Rs2.W[0];
 * if (tmp > (2^16)-1) {
 *   tmp = (2^16)-1;
 *   OV = 1;
 * }
 * else if (tmp < 0) {
 *   tmp = 0;
 *   OV = 1;
 * }
 * Rd = SE(tmp[15:0]);
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UKSUBH(unsigned int a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("uksubh %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.163. UKSUBH ===== */

/* ===== Inline Function Start for 3.164. UKSUBW ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_Q31_SAT_ALU
 * \brief UKSUBW (Unsigned Subtraction with U32 Saturation)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * UKSUBW Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Subtract the unsigned lower 32-bit content of two registers with unsigned 32-bit
 * saturation.
 *
 * **Description**:\n
 * The unsigned lower 32-bit content of Rs2 is subtracted from the unsigned lower 32-bit
 * content of Rs1. And the result is saturated to the 32-bit unsigned integer range of [0, 2^32-1] and then
 * sign-extended and written to Rd. If saturation happens, this instruction sets the OV flag.
 *
 * **Operations**:\n
 * ~~~
 * tmp = Rs1.W[0] - Rs2.W[0];
 * if (tmp < 0) {
 *   tmp[31:0] = 0;
 *   OV = 1;
 * }
 * Rd = tmp[31:0]; // RV32
 * Rd = SE(tmp[31:0]); // RV64
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UKSUBW(unsigned int a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("uksubw %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.164. UKSUBW ===== */

/* ===== Inline Function Start for 3.165. UMAR64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_32B_MULT_64B_ADDSUB
 * \brief UMAR64 (Unsigned Multiply and Add to 64-Bit Data)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * UMAR64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the 32-bit unsigned elements in two registers and add the 64-bit multiplication
 * results to the 64-bit unsigned data of a pair of registers (RV32) or a register (RV64). The result is
 * written back to the pair of registers (RV32) or a register (RV64).
 *
 * **RV32 Description**:\n
 * This instruction multiplies the 32-bit unsigned data of Rs1 with that of Rs2. It
 * adds the 64-bit multiplication result to the 64-bit unsigned data of an even/odd pair of registers
 * specified by Rd(4,1). The addition result is written back to the even/odd pair of registers specified by
 * Rd(4,1).
 * Rx(4,1), i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 *
 * **RV64 Description**:\n
 * This instruction multiplies the 32-bit unsigned elements of Rs1 with that of Rs2.
 * It adds the 64-bit multiplication results to the 64-bit unsigned data of Rd. The addition result is
 * written back to Rd.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * R[t_H].R[t_L] = R[t_H].R[t_L] + (Rs1 * Rs2);
 * * RV64:
 * Rd = Rd + (Rs1.W[0] u* Rs2.W[0]) + (Rs1.W[1] u* Rs2.W[1]);
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_UMAR64(unsigned long long t, unsigned long a, unsigned long b)
{
    __ASM volatile("umar64 %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.165. UMAR64 ===== */

/* ===== Inline Function Start for 3.166. UMAQA ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_8B_MULT_32B_ADD
 * \brief UMAQA (Unsigned Multiply Four Bytes with 32- bit Adds)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * UMAQA Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do four unsigned 8-bit multiplications from 32-bit chunks of two registers; and then adds
 * the four 16-bit results and the content of corresponding 32-bit chunks of a third register together.
 *
 * **Description**:\n
 * This instruction multiplies the four unsigned 8-bit elements of 32-bit chunks of Rs1 with the four
 * unsigned 8-bit elements of 32-bit chunks of Rs2 and then adds the four results together with the
 * unsigned content of the corresponding 32-bit chunks of Rd. The final results are written back to the
 * corresponding 32-bit chunks in Rd.
 *
 * **Operations**:\n
 * ~~~
 * res[x] = Rd.W[x] + (Rs1.W[x].B[3] u* Rs2.W[x].B[3]) +
 *          (Rs1.W[x].B[2] u* Rs2.W[x].B[2]) + (Rs1.W[x].B[1] u* Rs2.W[x].B[1]) +
 *          (Rs1.W[x].B[0] u* Rs2.W[x].B[0]);
 * Rd.W[x] = res[x];
 * for RV32: x=0,
 * for RV64: x=1...0
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UMAQA(unsigned long t, unsigned long a, unsigned long b)
{
    __ASM volatile("umaqa %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.166. UMAQA ===== */

/* ===== Inline Function Start for 3.167. UMAX8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_MISC
 * \brief UMAX8 (SIMD 8-bit Unsigned Maximum)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UMAX8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit unsigned integer elements finding maximum operations simultaneously.
 *
 * **Description**:\n
 * This instruction compares the 8-bit unsigned integer elements in Rs1 with the four 8-
 * bit unsigned integer elements in Rs2 and selects the numbers that is greater than the other one. The
 * two selected results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.B[x] = (Rs1.B[x] >u Rs2.B[x])? Rs1.B[x] : Rs2.B[x];
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UMAX8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("umax8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.167. UMAX8 ===== */

/* ===== Inline Function Start for 3.168. UMAX16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_MISC
 * \brief UMAX16 (SIMD 16-bit Unsigned Maximum)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UMAX16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit unsigned integer elements finding maximum operations simultaneously.
 *
 * **Description**:\n
 * This instruction compares the 16-bit unsigned integer elements in Rs1 with the 16-bit
 * unsigned integer elements in Rs2 and selects the numbers that is greater than the other one. The
 * selected results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.H[x] = (Rs1.H[x] >u Rs2.H[x])? Rs1.H[x] : Rs2.H[x];
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UMAX16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("umax16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.168. UMAX16 ===== */

/* ===== Inline Function Start for 3.169. UMIN8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_MISC
 * \brief UMIN8 (SIMD 8-bit Unsigned Minimum)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UMIN8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit unsigned integer elements finding minimum operations simultaneously.
 *
 * **Description**:\n
 * This instruction compares the 8-bit unsigned integer elements in Rs1 with the 8-bit
 * unsigned integer elements in Rs2 and selects the numbers that is less than the other one. The
 * selected results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.B[x] = (Rs1.B[x] <u Rs2.B[x])? Rs1.B[x] : Rs2.B[x];
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UMIN8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("umin8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.169. UMIN8 ===== */

/* ===== Inline Function Start for 3.170. UMIN16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_MISC
 * \brief UMIN16 (SIMD 16-bit Unsigned Minimum)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UMIN16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit unsigned integer elements finding minimum operations simultaneously.
 *
 * **Description**:\n
 * This instruction compares the 16-bit unsigned integer elements in Rs1 with the 16-bit
 * unsigned integer elements in Rs2 and selects the numbers that is less than the other one. The
 * selected results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.H[x] = (Rs1.H[x] <u Rs2.H[x])? Rs1.H[x] : Rs2.H[x];
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_UMIN16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("umin16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.170. UMIN16 ===== */

/* ===== Inline Function Start for 3.171. UMSR64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_32B_MULT_64B_ADDSUB
 * \brief UMSR64 (Unsigned Multiply and Subtract from 64-Bit Data)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * UMSR64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Multiply the 32-bit unsigned elements in two registers and subtract the 64-bit
 * multiplication results from the 64-bit unsigned data of a pair of registers (RV32) or a register (RV64).
 * The result is written back to the pair of registers (RV32) or a register (RV64).
 *
 * **RV32 Description**:\n
 * This instruction multiplies the 32-bit unsigned data of Rs1 with that of Rs2. It
 * subtracts the 64-bit multiplication result from the 64-bit unsigned data of an even/odd pair of
 * registers specified by Rd(4,1). The subtraction result is written back to the even/odd pair of registers
 * specified by Rd(4,1).
 * Rx(4,1), i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 *
 * **RV64 Description**:\n
 * This instruction multiplies the 32-bit unsigned elements of Rs1 with that of Rs2.
 * It subtracts the 64-bit multiplication results from the 64-bit unsigned data of Rd. The subtraction
 * result is written back to Rd.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * R[t_H].R[t_L] = R[t_H].R[t_L] - (Rs1 * Rs2);
 * * RV64:
 * Rd = Rd - (Rs1.W[0] u* Rs2.W[0]) - (Rs1.W[1] u* Rs2.W[1]);
 * ~~~
 *
 * \param [in]  t
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_UMSR64(unsigned long long t, unsigned long a, unsigned long b)
{
    __ASM volatile("umsr64 %0, %1, %2" : "+r"(t) : "r"(a), "r"(b));
    return t;
}
/* ===== Inline Function End for 3.171. UMSR64 ===== */

/* ===== Inline Function Start for 3.172.1. UMUL8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_MULTIPLY
 * \brief UMUL8 (SIMD Unsigned 8-bit Multiply)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UMUL8 Rd, Rs1, Rs2
 * UMULX8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do unsigned 8-bit multiplications and generate four 16-bit results simultaneously.
 *
 * **RV32 Description**:\n
 * For the `UMUL8` instruction, multiply the unsigned 8-bit data elements of Rs1
 * with the corresponding unsigned 8-bit data elements of Rs2.
 * For the `UMULX8` instruction, multiply the first and second unsigned 8-bit data elements of Rs1
 * with the second and first unsigned 8-bit data elements of Rs2. At the same time, multiply the third
 * and fourth unsigned 8-bit data elements of Rs1 with the fourth and third unsigned 8-bit data
 * elements of Rs2.
 * The four 16-bit results are then written into an even/odd pair of registers specified by Rd(4,1).
 * Rd(4,1), i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the two 16-bit results calculated from the top part of
 * Rs1 and the even `2d` register of the pair contains the two 16-bit results calculated from the bottom
 * part of Rs1.
 *
 * **RV64 Description**:\n
 * For the `UMUL8` instruction, multiply the unsigned 8-bit data elements of Rs1
 * with the corresponding unsigned 8-bit data elements of Rs2.
 * For the `UMULX8` instruction, multiply the first and second unsigned 8-bit data elements of Rs1
 * with the second and first unsigned 8-bit data elements of Rs2. At the same time, multiply the third
 * and fourth unsigned 8-bit data elements of Rs1 with the fourth and third unsigned 8-bit data
 * elements of Rs2.
 * The four 16-bit results are then written into Rd. The Rd.W[1] contains the two 16-bit results
 * calculated from the top part of Rs1 and the Rd.W[0] contains the two 16-bit results calculated from
 * the bottom part of Rs1.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * if (is `UMUL8`) {
 *   op1t[x/2] = Rs1.B[x+1]; op2t[x/2] = Rs2.B[x+1]; // top
 *   op1b[x/2] = Rs1.B[x]; op2b[x/2] = Rs2.B[x]; // bottom
 * } else if (is `UMULX8`) {
 *   op1t[x/2] = Rs1.B[x+1]; op2t[x/2] = Rs2.B[x]; // Rs1 top
 *   op1b[x/2] = Rs1.B[x]; op2b[x/2] = Rs2.B[x+1]; // Rs1 bottom
 * }
 * rest[x/2] = op1t[x/2] u* op2t[x/2];
 * resb[x/2] = op1b[x/2] u* op2b[x/2];
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * R[t_H].H[1] = rest[1]; R[t_H].H[0] = resb[1];
 * R[t_L].H[1] = rest[0]; R[t_L].H[0] = resb[0];
 * x = 0 and 2
 * * RV64:
 * if (is `UMUL8`) {
 *     op1t[x/2] = Rs1.B[x+1]; op2t[x/2] = Rs2.B[x+1]; // top
 *     op1b[x/2] = Rs1.B[x]; op2b[x/2] = Rs2.B[x]; // bottom
 * } else if (is `UMULX8`) {
 *     op1t[x/2] = Rs1.B[x+1]; op2t[x/2] = Rs2.B[x]; // Rs1 top
 *     op1b[x/2]  =  Rs1.B[x]; op2b[x/2]  =  Rs2.B[x+1];  //  Rs1  bottom
 * }
 * rest[x/2]  =  op1t[x/2]  u*  op2t[x/2];
 * resb[x/2]  =  op1b[x/2]  u*  op2b[x/2];
 * t_L  =  CONCAT(Rd(4,1),1'b0); t_H  =  CONCAT(Rd(4,1),1'b1);
 * Rd.W[1].H[1] = rest[1]; Rd.W[1].H[0] = resb[1];
 * Rd.W[0].H[1] = rest[0]; Rd.W[0].H[0] = resb[0]; x = 0 and 2
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_UMUL8(unsigned int a, unsigned int b)
{
    unsigned long long result;
    __ASM volatile("umul8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.172.1. UMUL8 ===== */

/* ===== Inline Function Start for 3.172.2. UMULX8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_MULTIPLY
 * \brief UMULX8 (SIMD Unsigned Crossed 8-bit Multiply)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UMUL8 Rd, Rs1, Rs2
 * UMULX8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do unsigned 8-bit multiplications and generate four 16-bit results simultaneously.
 *
 * **RV32 Description**:\n
 * For the `UMUL8` instruction, multiply the unsigned 8-bit data elements of Rs1
 * with the corresponding unsigned 8-bit data elements of Rs2.
 * For the `UMULX8` instruction, multiply the first and second unsigned 8-bit data elements of Rs1
 * with the second and first unsigned 8-bit data elements of Rs2. At the same time, multiply the third
 * and fourth unsigned 8-bit data elements of Rs1 with the fourth and third unsigned 8-bit data
 * elements of Rs2.
 * The four 16-bit results are then written into an even/odd pair of registers specified by Rd(4,1).
 * Rd(4,1), i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the two 16-bit results calculated from the top part of
 * Rs1 and the even `2d` register of the pair contains the two 16-bit results calculated from the bottom
 * part of Rs1.
 *
 * **RV64 Description**:\n
 * For the `UMUL8` instruction, multiply the unsigned 8-bit data elements of Rs1
 * with the corresponding unsigned 8-bit data elements of Rs2.
 * For the `UMULX8` instruction, multiply the first and second unsigned 8-bit data elements of Rs1
 * with the second and first unsigned 8-bit data elements of Rs2. At the same time, multiply the third
 * and fourth unsigned 8-bit data elements of Rs1 with the fourth and third unsigned 8-bit data
 * elements of Rs2.
 * The four 16-bit results are then written into Rd. The Rd.W[1] contains the two 16-bit results
 * calculated from the top part of Rs1 and the Rd.W[0] contains the two 16-bit results calculated from
 * the bottom part of Rs1.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * if (is `UMUL8`) {
 *   op1t[x/2] = Rs1.B[x+1]; op2t[x/2] = Rs2.B[x+1]; // top
 *   op1b[x/2] = Rs1.B[x]; op2b[x/2] = Rs2.B[x]; // bottom
 * } else if (is `UMULX8`) {
 *   op1t[x/2] = Rs1.B[x+1]; op2t[x/2] = Rs2.B[x]; // Rs1 top
 *   op1b[x/2] = Rs1.B[x]; op2b[x/2] = Rs2.B[x+1]; // Rs1 bottom
 * }
 * rest[x/2] = op1t[x/2] u* op2t[x/2];
 * resb[x/2] = op1b[x/2] u* op2b[x/2];
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * R[t_H].H[1] = rest[1]; R[t_H].H[0] = resb[1];
 * R[t_L].H[1] = rest[0]; R[t_L].H[0] = resb[0];
 * x = 0 and 2
 * * RV64:
 * if (is `UMUL8`) {
 *     op1t[x/2] = Rs1.B[x+1]; op2t[x/2] = Rs2.B[x+1]; // top
 *     op1b[x/2] = Rs1.B[x]; op2b[x/2] = Rs2.B[x]; // bottom
 * } else if (is `UMULX8`) {
 *     op1t[x/2] = Rs1.B[x+1]; op2t[x/2] = Rs2.B[x]; // Rs1 top
 *     op1b[x/2]  =  Rs1.B[x]; op2b[x/2]  =  Rs2.B[x+1];  //  Rs1  bottom
 * }
 * rest[x/2]  =  op1t[x/2]  u*  op2t[x/2];
 * resb[x/2]  =  op1b[x/2]  u*  op2b[x/2];
 * t_L  =  CONCAT(Rd(4,1),1'b0); t_H  =  CONCAT(Rd(4,1),1'b1);
 * Rd.W[1].H[1] = rest[1]; Rd.W[1].H[0] = resb[1];
 * Rd.W[0].H[1] = rest[0]; Rd.W[0].H[0] = resb[0]; x = 0 and 2
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_UMULX8(unsigned int a, unsigned int b)
{
    unsigned long long result;
    __ASM volatile("umulx8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.172.2. UMULX8 ===== */

/* ===== Inline Function Start for 3.173.1. UMUL16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_MULTIPLY
 * \brief UMUL16 (SIMD Unsigned 16-bit Multiply)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UMUL16 Rd, Rs1, Rs2
 * UMULX16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do unsigned 16-bit multiplications and generate two 32-bit results simultaneously.
 *
 * **RV32 Description**:\n
 * For the `UMUL16` instruction, multiply the top 16-bit U16 content of Rs1 with
 * the top 16-bit U16 content of Rs2. At the same time, multiply the bottom 16-bit U16 content of Rs1
 * with the bottom 16-bit U16 content of Rs2.
 * For the `UMULX16` instruction, multiply the top 16-bit U16 content of Rs1 with the bottom 16-bit
 * U16 content of Rs2. At the same time, multiply the bottom 16-bit U16 content of Rs1 with the top 16-
 * bit U16 content of Rs2.
 * The two U32 results are then written into an even/odd pair of registers specified by Rd(4,1). Rd(4,1),
 * i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair includes
 * register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the 32-bit result calculated from the top part of Rs1 and
 * the even `2d` register of the pair contains the 32-bit result calculated from the bottom part of Rs1.
 *
 * **RV64 Description**:\n
 * For the `UMUL16` instruction, multiply the top 16-bit U16 content of the lower
 * 32-bit word in Rs1 with the top 16-bit U16 content of the lower 32-bit word in Rs2. At the same time,
 * multiply the bottom 16-bit U16 content of the lower 32-bit word in Rs1 with the bottom 16-bit U16
 * content of the lower 32-bit word in Rs2.
 * For the `UMULX16` instruction, multiply the top 16-bit U16 content of the lower 32-bit word in Rs1
 * with the bottom 16-bit U16 content of the lower 32-bit word in Rs2. At the same time, multiply the
 * bottom 16-bit U16 content of the lower 32-bit word in Rs1 with the top 16-bit U16 content of the
 * lower 32-bit word in Rs2.
 * The two 32-bit U32 results are then written into Rd. The result calculated from the top 16-bit of the
 * lower 32-bit word in Rs1 is written to Rd.W[1]. And the result calculated from the bottom 16-bit of
 * the lower 32-bit word in Rs1 is written to Rd.W[0]
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * if (is `UMUL16`) {
 *   op1t = Rs1.H[1]; op2t = Rs2.H[1]; // top
 *   op1b = Rs1.H[0]; op2b = Rs2.H[0]; // bottom
 * } else if (is `UMULX16`) {
 *   op1t = Rs1.H[1]; op2t = Rs2.H[0]; // Rs1 top
 *   op1b = Rs1.H[0]; op2b = Rs2.H[1]; // Rs1 bottom
 * }
 * for ((aop,bop,res) in [(op1t,op2t,rest), (op1b,op2b,resb)]) {
 *   res = aop u* bop;
 * }
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * R[t_H] = rest;
 * R[t_L] = resb;
 * * RV64:
 * if (is `UMUL16`) {
 *   op1t = Rs1.H[1]; op2t = Rs2.H[1]; // top
 *   op1b = Rs1.H[0]; op2b = Rs2.H[0]; // bottom
 * } else if (is `UMULX16`) {
 *   op1t = Rs1.H[1]; op2t = Rs2.H[0]; // Rs1 top
 *   op1b = Rs1.H[0]; op2b = Rs2.H[1]; // Rs1 bottom
 * }
 * for ((aop,bop,res) in [(op1t,op2t,rest), (op1b,op2b,resb)]) {
 *   res = aop u* bop;
 * }
 * Rd.W[1] = rest;
 * Rd.W[0] = resb;
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_UMUL16(unsigned int a, unsigned int b)
{
    unsigned long long result;
    __ASM volatile("umul16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.173.1. UMUL16 ===== */

/* ===== Inline Function Start for 3.173.2. UMULX16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_MULTIPLY
 * \brief UMULX16 (SIMD Unsigned Crossed 16-bit Multiply)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * UMUL16 Rd, Rs1, Rs2
 * UMULX16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do unsigned 16-bit multiplications and generate two 32-bit results simultaneously.
 *
 * **RV32 Description**:\n
 * For the `UMUL16` instruction, multiply the top 16-bit U16 content of Rs1 with
 * the top 16-bit U16 content of Rs2. At the same time, multiply the bottom 16-bit U16 content of Rs1
 * with the bottom 16-bit U16 content of Rs2.
 * For the `UMULX16` instruction, multiply the top 16-bit U16 content of Rs1 with the bottom 16-bit
 * U16 content of Rs2. At the same time, multiply the bottom 16-bit U16 content of Rs1 with the top 16-
 * bit U16 content of Rs2.
 * The two U32 results are then written into an even/odd pair of registers specified by Rd(4,1). Rd(4,1),
 * i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair includes
 * register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the 32-bit result calculated from the top part of Rs1 and
 * the even `2d` register of the pair contains the 32-bit result calculated from the bottom part of Rs1.
 *
 * **RV64 Description**:\n
 * For the `UMUL16` instruction, multiply the top 16-bit U16 content of the lower
 * 32-bit word in Rs1 with the top 16-bit U16 content of the lower 32-bit word in Rs2. At the same time,
 * multiply the bottom 16-bit U16 content of the lower 32-bit word in Rs1 with the bottom 16-bit U16
 * content of the lower 32-bit word in Rs2.
 * For the `UMULX16` instruction, multiply the top 16-bit U16 content of the lower 32-bit word in Rs1
 * with the bottom 16-bit U16 content of the lower 32-bit word in Rs2. At the same time, multiply the
 * bottom 16-bit U16 content of the lower 32-bit word in Rs1 with the top 16-bit U16 content of the
 * lower 32-bit word in Rs2.
 * The two 32-bit U32 results are then written into Rd. The result calculated from the top 16-bit of the
 * lower 32-bit word in Rs1 is written to Rd.W[1]. And the result calculated from the bottom 16-bit of
 * the lower 32-bit word in Rs1 is written to Rd.W[0]
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * if (is `UMUL16`) {
 *   op1t = Rs1.H[1]; op2t = Rs2.H[1]; // top
 *   op1b = Rs1.H[0]; op2b = Rs2.H[0]; // bottom
 * } else if (is `UMULX16`) {
 *   op1t = Rs1.H[1]; op2t = Rs2.H[0]; // Rs1 top
 *   op1b = Rs1.H[0]; op2b = Rs2.H[1]; // Rs1 bottom
 * }
 * for ((aop,bop,res) in [(op1t,op2t,rest), (op1b,op2b,resb)]) {
 *   res = aop u* bop;
 * }
 * t_L = CONCAT(Rd(4,1),1'b0); t_H = CONCAT(Rd(4,1),1'b1);
 * R[t_H] = rest;
 * R[t_L] = resb;
 * * RV64:
 * if (is `UMUL16`) {
 *   op1t = Rs1.H[1]; op2t = Rs2.H[1]; // top
 *   op1b = Rs1.H[0]; op2b = Rs2.H[0]; // bottom
 * } else if (is `UMULX16`) {
 *   op1t = Rs1.H[1]; op2t = Rs2.H[0]; // Rs1 top
 *   op1b = Rs1.H[0]; op2b = Rs2.H[1]; // Rs1 bottom
 * }
 * for ((aop,bop,res) in [(op1t,op2t,rest), (op1b,op2b,resb)]) {
 *   res = aop u* bop;
 * }
 * Rd.W[1] = rest;
 * Rd.W[0] = resb;
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_UMULX16(unsigned int a, unsigned int b)
{
    unsigned long long result;
    __ASM volatile("umulx16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.173.2. UMULX16 ===== */

/* ===== Inline Function Start for 3.174. URADD8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_ADDSUB
 * \brief URADD8 (SIMD 8-bit Unsigned Halving Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * URADD8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit unsigned integer element additions simultaneously. The results are halved to
 * avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction adds the 8-bit unsigned integer elements in Rs1 with the 8-bit
 * unsigned integer elements in Rs2. The results are first logically right-shifted by 1 bit and then
 * written to Rd.
 *
 * **Examples**:\n
 * ~~~
 * * Ra = 0x7F, Rb = 0x7F, Rt = 0x7F
 * * Ra = 0x80, Rb = 0x80, Rt = 0x80
 * * Ra = 0x40, Rb = 0x80, Rt = 0x60
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * Rd.B[x] = (Rs1.B[x] + Rs2.B[x]) u>> 1;
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_URADD8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("uradd8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.174. URADD8 ===== */

/* ===== Inline Function Start for 3.175. URADD16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief URADD16 (SIMD 16-bit Unsigned Halving Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * URADD16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit unsigned integer element additions simultaneously. The results are halved to
 * avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction adds the 16-bit unsigned integer elements in Rs1 with the 16-bit
 * unsigned integer elements in Rs2. The results are first logically right-shifted by 1 bit and then
 * written to Rd.
 *
 * **Examples**:\n
 * ~~~
 * * Ra = 0x7FFF, Rb = 0x7FFF Rt = 0x7FFF
 * * Ra = 0x8000, Rb = 0x8000 Rt = 0x8000
 * * Ra = 0x4000, Rb = 0x8000 Rt = 0x6000
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * Rd.H[x] = (Rs1.H[x] + Rs2.H[x]) u>> 1;
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_URADD16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("uradd16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.175. URADD16 ===== */

/* ===== Inline Function Start for 3.176. URADD64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_64B_ADDSUB
 * \brief URADD64 (64-bit Unsigned Halving Addition)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * URADD64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Add two 64-bit unsigned integers. The result is halved to avoid overflow or saturation.
 *
 * **RV32 Description**:\n
 * This instruction adds the 64-bit unsigned integer of an even/odd pair of registers
 * specified by Rs1(4,1) with the 64-bit unsigned integer of an even/odd pair of registers specified by
 * Rs2(4,1). The 64-bit addition result is first logically right-shifted by 1 bit and then written to an
 * even/odd pair of registers specified by Rd(4,1).
 * Rx(4,1), i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 *
 * **RV64 Description**:\n
 * This instruction adds the 64-bit unsigned integer in Rs1 with the 64-bit unsigned
 * integer Rs2. The 64-bit addition result is first logically right-shifted by 1 bit and then written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * t_L = CONCAT(Rt(4,1),1'b0); t_H = CONCAT(Rt(4,1),1'b1);
 * a_L = CONCAT(Ra(4,1),1'b0); a_H = CONCAT(Ra(4,1),1'b1);
 * b_L = CONCAT(Rb(4,1),1'b0); b_H = CONCAT(Rb(4,1),1'b1);
 * R[t_H].R[t_L] = (R[a_H].R[a_L] + R[b_H].R[b_L]) u>> 1;
 * * RV64:
 * Rd = (Rs1 + Rs2) u>> 1;
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_URADD64(unsigned long long a, unsigned long long b)
{
    unsigned long long result;
    __ASM volatile("uradd64 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.176. URADD64 ===== */

/* ===== Inline Function Start for 3.177. URADDW ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_32B_COMPUTATION
 * \brief URADDW (32-bit Unsigned Halving Addition)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * URADDW Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Add 32-bit unsigned integers and the results are halved to avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction adds the first 32-bit unsigned integer in Rs1 with the first 32-bit
 * unsigned integer in Rs2. The result is first logically right-shifted by 1 bit and then sign-extended and
 * written to Rd.
 *
 * **Examples**:\n
 * ~~~
 * * Ra = 0x7FFFFFFF, Rb = 0x7FFFFFFF Rt = 0x7FFFFFFF
 * * Ra = 0x80000000, Rb = 0x80000000 Rt = 0x80000000
 * * Ra = 0x40000000, Rb = 0x80000000 Rt = 0x60000000
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * Rd[31:0] = (Rs1[31:0] + Rs2[31:0]) u>> 1;
 * * RV64:
 * resw[31:0] = (Rs1[31:0] + Rs2[31:0]) u>> 1;
 * Rd[63:0] = SE(resw[31:0]);
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_URADDW(unsigned int a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("uraddw %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.177. URADDW ===== */

/* ===== Inline Function Start for 3.178. URCRAS16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief URCRAS16 (SIMD 16-bit Unsigned Halving Cross Addition & Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * URCRAS16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit unsigned integer element addition and 16-bit unsigned integer element
 * subtraction in a 32-bit chunk simultaneously. Operands are from crossed positions in 32-bit chunks.
 * The results are halved to avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction adds the 16-bit unsigned integer in [31:16] of 32-bit chunks in Rs1
 * with the 16-bit unsigned integer in [15:0] of 32-bit chunks in Rs2, and subtracts the 16-bit unsigned
 * integer in [31:16] of 32-bit chunks in Rs2 from the 16-bit unsigned integer in [15:0] of 32-bit chunks
 * in Rs1. The element results are first logically right-shifted by 1 bit and then written to [31:16] of 32-
 * bit chunks in Rd and [15:0] of 32-bit chunks in Rd.
 *
 * **Examples**:\n
 * ~~~
 * Please see `URADD16` and `URSUB16` instructions.
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:16] = (Rs1.W[x][31:16] + Rs2.W[x][15:0]) u>> 1;
 * Rd.W[x][15:0] = (Rs1.W[x][15:0] - Rs2.W[x][31:16]) u>> 1;
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_URCRAS16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("urcras16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.178. URCRAS16 ===== */

/* ===== Inline Function Start for 3.179. URCRSA16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief URCRSA16 (SIMD 16-bit Unsigned Halving Cross Subtraction & Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * URCRSA16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit unsigned integer element subtraction and 16-bit unsigned integer element
 * addition in a 32-bit chunk simultaneously. Operands are from crossed positions in 32-bit chunks.
 * The results are halved to avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction subtracts the 16-bit unsigned integer in [15:0] of 32-bit chunks in Rs2
 * from the 16-bit unsigned integer in [31:16] of 32-bit chunks in Rs1, and adds the 16-bit unsigned
 * integer in [15:0] of 32-bit chunks in Rs1 with the 16-bit unsigned integer in [31:16] of 32-bit chunks
 * in Rs2. The two results are first logically right-shifted by 1 bit and then written to [31:16] of 32-bit
 * chunks in Rd and [15:0] of 32-bit chunks in Rd.
 *
 * **Examples**:\n
 * ~~~
 * Please see `URADD16` and `URSUB16` instructions.
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:16] = (Rs1.W[x][31:16] - Rs2.W[x][15:0]) u>> 1;
 * Rd.W[x][15:0] = (Rs1.W[x][15:0] + Rs2.W[x][31:16]) u>> 1;
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_URCRSA16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("urcrsa16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.179. URCRSA16 ===== */

/* ===== Inline Function Start for 3.180. URSTAS16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief URSTAS16 (SIMD 16-bit Unsigned Halving Straight Addition & Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * URSTAS16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit unsigned integer element addition and 16-bit unsigned integer element
 * subtraction in a 32-bit chunk simultaneously. Operands are from corresponding positions in 32-bit
 * chunks. The results are halved to avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction adds the 16-bit unsigned integer in [31:16] of 32-bit chunks in Rs1
 * with the 16-bit unsigned integer in [31:16] of 32-bit chunks in Rs2, and subtracts the 16-bit unsigned
 * integer in [15:0] of 32-bit chunks in Rs2 from the 16-bit unsigned integer in [15:0] of 32-bit chunks
 * in Rs1. The element results are first logically right-shifted by 1 bit and then written to [31:16] of 32-
 * bit chunks in Rd and [15:0] of 32-bit chunks in Rd.
 *
 * **Examples**:\n
 * ~~~
 * Please see `URADD16` and `URSUB16` instructions.
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:16] = (Rs1.W[x][31:16] + Rs2.W[x][31:16]) u>> 1;
 * Rd.W[x][15:0] = (Rs1.W[x][15:0] - Rs2.W[x][15:0]) u>> 1;
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_URSTAS16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("urstas16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.180. URSTAS16 ===== */

/* ===== Inline Function Start for 3.181. URSTSA16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief URSTSA16 (SIMD 16-bit Unsigned Halving Straight Subtraction & Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * URCRSA16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit unsigned integer element subtraction and 16-bit unsigned integer element
 * addition in a 32-bit chunk simultaneously. Operands are from corresponding positions in 32-bit
 * chunks. The results are halved to avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction subtracts the 16-bit unsigned integer in [31:16] of 32-bit chunks in Rs2
 * from the 16-bit unsigned integer in [31:16] of 32-bit chunks in Rs1, and adds the 16-bit unsigned
 * integer in [15:0] of 32-bit chunks in Rs1 with the 16-bit unsigned integer in [15:0] of 32-bit chunks in
 * Rs2. The two results are first logically right-shifted by 1 bit and then written to [31:16] of 32-bit
 * chunks in Rd and [15:0] of 32-bit chunks in Rd.
 *
 * **Examples**:\n
 * ~~~
 * Please see `URADD16` and `URSUB16` instructions.
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:16] = (Rs1.W[x][31:16] - Rs2.W[x][31:16]) u>> 1;
 * Rd.W[x][15:0] = (Rs1.W[x][15:0] + Rs2.W[x][15:0]) u>> 1;
 * for RV32, x=0
 * for RV64, x=1...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_URSTSA16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("urstsa16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.181. URSTSA16 ===== */

/* ===== Inline Function Start for 3.182. URSUB8 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_ADDSUB
 * \brief URSUB8 (SIMD 8-bit Unsigned Halving Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * URSUB8 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit unsigned integer element subtractions simultaneously. The results are halved to
 * avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction subtracts the 8-bit unsigned integer elements in Rs2 from the 8-bit
 * unsigned integer elements in Rs1. The results are first logically right-shifted by 1 bit and then
 * written to Rd.
 *
 * **Examples**:\n
 * ~~~
 * * Ra = 0x7F, Rb = 0x80 Rt = 0xFF
 * * Ra = 0x80, Rb = 0x7F Rt = 0x00
 * * Ra = 0x80, Rb = 0x40 Rt = 0x20
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * Rd.B[x] = (Rs1.B[x] - Rs2.B[x]) u>> 1;
 * for RV32: x=3...0,
 * for RV64: x=7...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_URSUB8(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("ursub8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.182. URSUB8 ===== */

/* ===== Inline Function Start for 3.183. URSUB16 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_16B_ADDSUB
 * \brief URSUB16 (SIMD 16-bit Unsigned Halving Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * URSUB16 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit unsigned integer element subtractions simultaneously. The results are halved to
 * avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction subtracts the 16-bit unsigned integer elements in Rs2 from the 16-bit
 * unsigned integer elements in Rs1. The results are first logically right-shifted by 1 bit and then
 * written to Rd.
 *
 * **Examples**:\n
 * ~~~
 * * Ra = 0x7FFF, Rb = 0x8000 Rt = 0xFFFF
 * * Ra = 0x8000, Rb = 0x7FFF Rt = 0x0000
 * * Ra = 0x8000, Rb = 0x4000 Rt = 0x2000
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * Rd.H[x] = (Rs1.H[x] - Rs2.H[x]) u>> 1;
 * for RV32: x=1...0,
 * for RV64: x=3...0
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_URSUB16(unsigned long a, unsigned long b)
{
    unsigned long result;
    __ASM volatile("ursub16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.183. URSUB16 ===== */

/* ===== Inline Function Start for 3.184. URSUB64 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_64B_ADDSUB
 * \brief URSUB64 (64-bit Unsigned Halving Subtraction)
 * \details
 * **Type**: DSP (64-bit Profile)
 *
 * **Syntax**:\n
 * ~~~
 * URSUB64 Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Perform a 64-bit unsigned integer subtraction. The result is halved to avoid overflow or
 * saturation.
 *
 * **RV32 Description**:\n
 * This instruction subtracts the 64-bit unsigned integer of an even/odd pair of
 * registers specified by Rs2(4,1) from the 64-bit unsigned integer of an even/odd pair of registers
 * specified by Rs1(4,1). The subtraction result is first logically right-shifted by 1 bit and then written
 * to an even/odd pair of registers specified by Rd(4,1).
 * Rx(4,1), i.e., d, determines the even/odd pair group of two registers. Specifically, the register pair
 * includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the result and the even `2d` register
 * of the pair contains the low 32-bit of the result.
 *
 * **RV64 Description**:\n
 * This instruction subtracts the 64-bit unsigned integer in Rs2 from the 64-bit
 * unsigned integer in Rs1. The subtraction result is first logically right-shifted by 1 bit and then
 * written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * t_L = CONCAT(Rt(4,1),1'b0); t_H = CONCAT(Rt(4,1),1'b1);
 * a_L = CONCAT(Ra(4,1),1'b0); a_H = CONCAT(Ra(4,1),1'b1);
 * b_L = CONCAT(Rb(4,1),1'b0); b_H = CONCAT(Rb(4,1),1'b1);
 * R[t_H].R[t_L] = (R[a_H].R[a_L] - R[b_H].R[b_L]) u>> 1;
 * * RV64:
 * Rd = (Rs1 - Rs2) u>> 1;
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_URSUB64(unsigned long long a, unsigned long long b)
{
    unsigned long long result;
    __ASM volatile("ursub64 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.184. URSUB64 ===== */

/* ===== Inline Function Start for 3.185. URSUBW ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_32B_COMPUTATION
 * \brief URSUBW (32-bit Unsigned Halving Subtraction)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * URSUBW Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Subtract 32-bit unsigned integers and the result is halved to avoid overflow or saturation.
 *
 * **Description**:\n
 * This instruction subtracts the first 32-bit signed integer in Rs2 from the first 32-bit
 * signed integer in Rs1. The result is first logically right-shifted by 1 bit and then sign-extended and
 * written to Rd.
 *
 * **Examples**:\n
 * ~~~
 * * Ra = 0x7FFFFFFF, Rb = 0x80000000 Rt = 0xFFFFFFFF
 * * Ra = 0x80000000, Rb = 0x7FFFFFFF Rt = 0x00000000
 * * Ra = 0x80000000, Rb = 0x40000000 Rt = 0x20000000
 * ~~~
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * Rd[31:0] = (Rs1[31:0] - Rs2[31:0]) u>> 1;
 * * RV64:
 * resw[31:0] = (Rs1[31:0] - Rs2[31:0]) u>> 1;
 * Rd[63:0] = SE(resw[31:0]);
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_URSUBW(unsigned int a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("ursubw %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.185. URSUBW ===== */

/* ===== Inline Function Start for 3.186. WEXTI ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_MISC
 * \brief WEXTI (Extract Word from 64-bit Immediate)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * WEXTI Rd, Rs1, #LSBloc
 * ~~~
 *
 * **Purpose**:\n
 * Extract a 32-bit word from a 64-bit value stored in an even/odd pair of registers (RV32) or
 * a register (RV64) starting from a specified immediate LSB bit position.
 *
 * **RV32 Description**:\n
 * This instruction extracts a 32-bit word from a 64-bit value of an even/odd pair of registers specified
 * by Rs1(4,1) starting from a specified immediate LSB bit position, #LSBloc. The extracted word is
 * written to Rd.
 * Rs1(4,1), i.e., d, determines the even/odd pair group of the two registers. Specifically, the register
 * pair includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the 64-bit value and the even `2d`
 * register of the pair contains the low 32-bit of the 64-bit value.
 *
 * **RV64 Description**:\n
 * This instruction extracts a 32-bit word from a 64-bit value in Rs1 starting from a specified
 * immediate LSB bit position, #LSBloc. The extracted word is sign-extended and written to lower 32-
 * bit of Rd.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * Idx0 = CONCAT(Rs1(4,1),1'b0); Idx1 = CONCAT(Rs2(4,1),1'b1);
 * src[63:0] = Concat(R[Idx1], R[Idx0]);
 * Rd = src[31+LSBloc:LSBloc];
 * * RV64:
 * ExtractW = Rs1[31+LSBloc:LSBloc];
 * Rd = SE(ExtractW)
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_WEXTI(long long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("wexti %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.186. WEXTI ===== */

/* ===== Inline Function Start for 3.187. WEXT ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_NON_SIMD_MISC
 * \brief WEXT (Extract Word from 64-bit)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * WEXT Rd, Rs1, Rs2
 * ~~~
 *
 * **Purpose**:\n
 * Extract a 32-bit word from a 64-bit value stored in an even/odd pair of registers (RV32) or
 * a register (RV64) starting from a specified LSB bit position in a register.
 *
 * **RV32 Description**:\n
 * This instruction extracts a 32-bit word from a 64-bit value of an even/odd pair of registers specified
 * by Rs1(4,1) starting from a specified LSB bit position, specified in Rs2[4:0]. The extracted word is
 * written to Rd.
 * Rs1(4,1), i.e., d, determines the even/odd pair group of the two registers. Specifically, the register
 * pair includes register 2d and 2d+1.
 * The odd `2d+1` register of the pair contains the high 32-bit of the 64-bit value and the even `2d`
 * register of the pair contains the low 32-bit of the 64-bit value.
 *
 * **Operations**:\n
 * ~~~
 * * RV32:
 * Idx0 = CONCAT(Rs1(4,1),1'b0); Idx1 = CONCAT(Rs1(4,1),1'b1);
 * src[63:0] = Concat(R[Idx1], R[Idx0]);
 * LSBloc = Rs2[4:0];
 * Rd = src[31+LSBloc:LSBloc];
 * * RV64:
 * LSBloc = Rs2[4:0];
 * ExtractW = Rs1[31+LSBloc:LSBloc];
 * Rd = SE(ExtractW)
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_WEXT(long long a, unsigned int b)
{
    unsigned long result;
    __ASM volatile("wext %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for 3.187. WEXT ===== */

/* ===== Inline Function Start for 3.188.1. ZUNPKD810 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_UNPACK
 * \brief ZUNPKD810 (Unsigned Unpacking Bytes 1 & 0)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * ZUNPKD8xy Rd, Rs1
 * xy = {10, 20, 30, 31, 32}
 * ~~~
 *
 * **Purpose**:\n
 * Unpack byte x and byte y of 32-bit chunks in a register into two 16-bit unsigned
 * halfwords of 32-bit chunks in a register.
 *
 * **Description**:\n
 * For the `ZUNPKD8(x)(*y*)` instruction, it unpacks byte *x and byte y* of 32-bit chunks in Rs1 into
 * two 16-bit unsigned halfwords and writes the results to the top part and the bottom part of 32-bit
 * chunks in Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[m].H[1] = ZE16(Rs1.W[m].B[x])
 * Rd.W[m].H[0] = ZE16(Rs1.W[m].B[y])
 * // ZUNPKD810, x=1,y=0
 * // ZUNPKD820, x=2,y=0
 * // ZUNPKD830, x=3,y=0
 * // ZUNPKD831, x=3,y=1
 * // ZUNPKD832, x=3,y=2
 * for RV32: m=0,
 * for RV64: m=1...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_ZUNPKD810(unsigned long a)
{
    unsigned long result;
    __ASM volatile("zunpkd810 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.188.1. ZUNPKD810 ===== */

/* ===== Inline Function Start for 3.188.2. ZUNPKD820 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_UNPACK
 * \brief ZUNPKD820 (Unsigned Unpacking Bytes 2 & 0)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * ZUNPKD8xy Rd, Rs1
 * xy = {10, 20, 30, 31, 32}
 * ~~~
 *
 * **Purpose**:\n
 * Unpack byte x and byte y of 32-bit chunks in a register into two 16-bit unsigned
 * halfwords of 32-bit chunks in a register.
 *
 * **Description**:\n
 * For the `ZUNPKD8(x)(*y*)` instruction, it unpacks byte *x and byte y* of 32-bit chunks in Rs1 into
 * two 16-bit unsigned halfwords and writes the results to the top part and the bottom part of 32-bit
 * chunks in Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[m].H[1] = ZE16(Rs1.W[m].B[x])
 * Rd.W[m].H[0] = ZE16(Rs1.W[m].B[y])
 * // ZUNPKD810, x=1,y=0
 * // ZUNPKD820, x=2,y=0
 * // ZUNPKD830, x=3,y=0
 * // ZUNPKD831, x=3,y=1
 * // ZUNPKD832, x=3,y=2
 * for RV32: m=0,
 * for RV64: m=1...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_ZUNPKD820(unsigned long a)
{
    unsigned long result;
    __ASM volatile("zunpkd820 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.188.2. ZUNPKD820 ===== */

/* ===== Inline Function Start for 3.188.3. ZUNPKD830 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_UNPACK
 * \brief ZUNPKD830 (Unsigned Unpacking Bytes 3 & 0)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * ZUNPKD8xy Rd, Rs1
 * xy = {10, 20, 30, 31, 32}
 * ~~~
 *
 * **Purpose**:\n
 * Unpack byte x and byte y of 32-bit chunks in a register into two 16-bit unsigned
 * halfwords of 32-bit chunks in a register.
 *
 * **Description**:\n
 * For the `ZUNPKD8(x)(*y*)` instruction, it unpacks byte *x and byte y* of 32-bit chunks in Rs1 into
 * two 16-bit unsigned halfwords and writes the results to the top part and the bottom part of 32-bit
 * chunks in Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[m].H[1] = ZE16(Rs1.W[m].B[x])
 * Rd.W[m].H[0] = ZE16(Rs1.W[m].B[y])
 * // ZUNPKD810, x=1,y=0
 * // ZUNPKD820, x=2,y=0
 * // ZUNPKD830, x=3,y=0
 * // ZUNPKD831, x=3,y=1
 * // ZUNPKD832, x=3,y=2
 * for RV32: m=0,
 * for RV64: m=1...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_ZUNPKD830(unsigned long a)
{
    unsigned long result;
    __ASM volatile("zunpkd830 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.188.3. ZUNPKD830 ===== */

/* ===== Inline Function Start for 3.188.4. ZUNPKD831 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_UNPACK
 * \brief ZUNPKD831 (Unsigned Unpacking Bytes 3 & 1)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * ZUNPKD8xy Rd, Rs1
 * xy = {10, 20, 30, 31, 32}
 * ~~~
 *
 * **Purpose**:\n
 * Unpack byte x and byte y of 32-bit chunks in a register into two 16-bit unsigned
 * halfwords of 32-bit chunks in a register.
 *
 * **Description**:\n
 * For the `ZUNPKD8(x)(*y*)` instruction, it unpacks byte *x and byte y* of 32-bit chunks in Rs1 into
 * two 16-bit unsigned halfwords and writes the results to the top part and the bottom part of 32-bit
 * chunks in Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[m].H[1] = ZE16(Rs1.W[m].B[x])
 * Rd.W[m].H[0] = ZE16(Rs1.W[m].B[y])
 * // ZUNPKD810, x=1,y=0
 * // ZUNPKD820, x=2,y=0
 * // ZUNPKD830, x=3,y=0
 * // ZUNPKD831, x=3,y=1
 * // ZUNPKD832, x=3,y=2
 * for RV32: m=0,
 * for RV64: m=1...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_ZUNPKD831(unsigned long a)
{
    unsigned long result;
    __ASM volatile("zunpkd831 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.188.4. ZUNPKD831 ===== */

/* ===== Inline Function Start for 3.188.5. ZUNPKD832 ===== */
/**
 * \ingroup NMSIS_Core_DSP_Intrinsic_SIMD_8B_UNPACK
 * \brief ZUNPKD832 (Unsigned Unpacking Bytes 3 & 2)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * ZUNPKD8xy Rd, Rs1
 * xy = {10, 20, 30, 31, 32}
 * ~~~
 *
 * **Purpose**:\n
 * Unpack byte x and byte y of 32-bit chunks in a register into two 16-bit unsigned
 * halfwords of 32-bit chunks in a register.
 *
 * **Description**:\n
 * For the `ZUNPKD8(x)(*y*)` instruction, it unpacks byte *x and byte y* of 32-bit chunks in Rs1 into
 * two 16-bit unsigned halfwords and writes the results to the top part and the bottom part of 32-bit
 * chunks in Rd.
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[m].H[1] = ZE16(Rs1.W[m].B[x])
 * Rd.W[m].H[0] = ZE16(Rs1.W[m].B[y])
 * // ZUNPKD810, x=1,y=0
 * // ZUNPKD820, x=2,y=0
 * // ZUNPKD830, x=3,y=0
 * // ZUNPKD831, x=3,y=1
 * // ZUNPKD832, x=3,y=2
 * for RV32: m=0,
 * for RV64: m=1...0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_ZUNPKD832(unsigned long a)
{
    unsigned long result;
    __ASM volatile("zunpkd832 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for 3.188.5. ZUNPKD832 ===== */

/* XXXXX Nuclei Extended DSP Instructions for RV32 XXXXX */
/**
 * \defgroup NMSIS_Core_DSP_Intrinsic_NUCLEI_CUSTOM      Nuclei Customized DSP Instructions
 * \ingroup  NMSIS_Core_DSP_Intrinsic
 * \brief    Nuclei Customized DSP Instructions
 * \details
 */
/* ===== Inline Function Start for A.1. DKHM8 ===== */
/**
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NUCLEI_CUSTOM
 * \brief DKHM8 (64-bit SIMD Signed Saturating Q7 Multiply)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * DKHM8 Rd, Rs1, Rs2
 * # Rd, Rs1, Rs2 are all even/odd pair of registers
 * ~~~
 *
 * **Purpose**:\n
 * Do Q7xQ7 element multiplications simultaneously. The Q14 results are then reduced to Q7
 * numbers again.
 *
 * **Description**:\n
 * For the `DKHM8` instruction, multiply the top 8-bit Q7 content of 16-bit chunks in Rs1
 * with the top 8-bit Q7 content of 16-bit chunks in Rs2. At the same time, multiply the bottom 8-bit Q7
 * content of 16-bit chunks in Rs1 with the bottom 8-bit Q7 content of 16-bit chunks in Rs2.
 *
 * The Q14 results are then right-shifted 7-bits and saturated into Q7 values. The Q7 results are then
 * written into Rd. When both the two Q7 inputs of a multiplication are 0x80, saturation will happen.
 * The result will be saturated to 0x7F and the overflow flag OV will be set.
 *
 * **Operations**:\n
 * ~~~
 * op1t = Rs1.B[x+1]; op2t = Rs2.B[x+1]; // top
 * op1b = Rs1.B[x]; op2b = Rs2.B[x]; // bottom
 * for ((aop,bop,res) in [(op1t,op2t,rest), (op1b,op2b,resb)]) {
 *   if (0x80 != aop | 0x80 != bop) {
 *     res = (aop s* bop) >> 7;
 *   } else {
 *     res= 0x7F;
 *     OV = 1;
 *   }
 * }
 * Rd.H[x/2] = concat(rest, resb);
 * for RV32, x=0,2,4,6
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_DKHM8(unsigned long long a, unsigned long long b)
{
    unsigned long long result;
    __ASM volatile("dkhm8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for A.1. DKHM8 ===== */

/* ===== Inline Function Start for A.2. DKHM16 ===== */
/**
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NUCLEI_CUSTOM
 * \brief DKHM16 (64-bit SIMD Signed Saturating Q15 Multiply)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * DKHM16 Rd, Rs1, Rs2
 * # Rd, Rs1, Rs2 are all even/odd pair of registers
 * ~~~
 *
 * **Purpose**:\n
 * Do Q15xQ15 element multiplications simultaneously. The Q30 results are then reduced to
 * Q15 numbers again.
 *
 * **Description**:\n
 * For the `DKHM16` instruction, multiply the top 16-bit Q15 content of 32-bit chunks in
 * Rs1 with the top 16-bit Q15 content of 32-bit chunks in Rs2. At the same time, multiply the bottom
 * 16-bit Q15 content of 32-bit chunks in Rs1 with the bottom 16-bit Q15 content of 32-bit chunks in
 * Rs2.
 *
 * The Q30 results are then right-shifted 15-bits and saturated into Q15 values. The Q15 results are
 * then written into Rd. When both the two Q15 inputs of a multiplication are 0x8000, saturation will
 * happen. The result will be saturated to 0x7FFF and the overflow flag OV will be set.
 *
 * **Operations**:\n
 * ~~~
 * op1t = Rs1.H[x+1]; op2t = Rs2.H[x+1]; // top
 * op1b = Rs1.H[x]; op2b = Rs2.H[x]; // bottom
 * for ((aop,bop,res) in [(op1t,op2t,rest), (op1b,op2b,resb)]) {
 *   if (0x8000 != aop | 0x8000 != bop) {
 *     res = (aop s* bop) >> 15;
 *   } else {
 *     res= 0x7FFF;
 *     OV = 1;
 *   }
 * }
 * Rd.W[x/2] = concat(rest, resb);
 * for RV32: x=0, 2
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_DKHM16(unsigned long long a, unsigned long long b)
{
    unsigned long long result;
    __ASM volatile("dkhm16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for A.2. DKHM16 ===== */

/* ===== Inline Function Start for A.3. DKABS8 ===== */
/**
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NUCLEI_CUSTOM
 * \brief DKABS8 (64-bit SIMD 8-bit Saturating Absolute)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * DKABS8 Rd, Rs1
 * # Rd, Rs1 are all even/odd pair of registers
 * ~~~
 *
 * **Purpose**:\n
 * Get the absolute value of 8-bit signed integer elements simultaneously.
 *
 * **Description**:\n
 * This instruction calculates the absolute value of 8-bit signed integer elements stored
 * in Rs1 and writes the element results to Rd. If the input number is 0x80, this instruction generates
 * 0x7f as the output and sets the OV bit to 1.
 *
 * **Operations**:\n
 * ~~~
 * src = Rs1.B[x];
 * if (src == 0x80) {
 *   src = 0x7f;
 *   OV = 1;
 * } else if (src[7] == 1)
 *   src = -src;
 * }
 * Rd.B[x] = src;
 * for RV32: x=7...0,
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_DKABS8(unsigned long long a)
{
    unsigned long long result;
    __ASM volatile("dkabs8 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for A.3. DKABS8 ===== */

/* ===== Inline Function Start for A.4. DKABS16 ===== */
/**
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NUCLEI_CUSTOM
 * \brief DKABS16 (64-bit SIMD 16-bit Saturating Absolute)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * DKABS16 Rd, Rs1
 * # Rd, Rs1 are all even/odd pair of registers
 * ~~~
 *
 * **Purpose**:\n
 * Get the absolute value of 16-bit signed integer elements simultaneously.
 *
 * **Description**:\n
 * This instruction calculates the absolute value of 16-bit signed integer elements stored
 * in Rs1 and writes the element results to Rd. If the input number is 0x8000, this instruction
 * generates 0x7fff as the output and sets the OV bit to 1.
 *
 * **Operations**:\n
 * ~~~
 * src = Rs1.H[x];
 * if (src == 0x8000) {
 *   src = 0x7fff;
 *   OV = 1;
 * } else if (src[15] == 1)
 *   src = -src;
 * }
 * Rd.H[x] = src;
 * for RV32: x=3...0,
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_DKABS16(unsigned long long a)
{
    unsigned long long result;
    __ASM volatile("dkabs16 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for A.4. DKABS16 ===== */

/* ===== Inline Function Start for A.5. DKSLRA8 ===== */
/**
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NUCLEI_CUSTOM
 * \brief DKSLRA8 (64-bit SIMD 8-bit Shift Left Logical with Saturation or Shift Right Arithmetic)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * DKSLRA8 Rd, Rs1, Rs2
 * # Rd, Rs1 are all even/odd pair of registers
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit elements logical left (positive) or arithmetic right (negative) shift operation with
 * Q7 saturation for the left shift.
 *
 * **Description**:\n
 * The 8-bit data elements of Rs1 are left-shifted logically or right-shifted arithmetically
 * based on the value of Rs2[3:0]. Rs2[3:0] is in the signed range of [-2^3, 2^3-1]. A positive Rs2[3:0] means
 * logical left shift and a negative Rs2[3:0] means arithmetic right shift. The shift amount is the
 * absolute value of Rs2[3:0]. However, the behavior of `Rs2[3:0]==-2^3 (0x8)` is defined to be
 * equivalent to the behavior of `Rs2[3:0]==-(2^3-1) (0x9)`.
 * The left-shifted results are saturated to the 8-bit signed integer range of [-2^7, 2^7-1].
 * If any saturation happens, this instruction sets the OV flag. The value of Rs2[31:4] will not affect
 * this instruction.
 *
 * **Operations**:\n
 * ~~~
 * if (Rs2[3:0] < 0) {
 *   sa = -Rs2[3:0];
 *   sa = (sa == 8)? 7 : sa;
 *   Rd.B[x] = SE8(Rs1.B[x][7:sa]);
 * } else {
 *   sa = Rs2[2:0];
 *   res[(7+sa):0] = Rs1.B[x] <<(logic) sa;
 *   if (res > (2^7)-1) {
 *     res[7:0] = 0x7f; OV = 1;
 *   } else if (res < -2^7) {
 *     res[7:0] = 0x80; OV = 1;
 *   }
 *   Rd.B[x] = res[7:0];
 * }
 * for RV32: x=7...0,
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_DKSLRA8(unsigned long long a, int b)
{
    unsigned long long result;
    __ASM volatile("dkslra8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for A.5. DKSLRA8 ===== */

/* ===== Inline Function Start for A.6. DKSLRA16 ===== */
/**
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NUCLEI_CUSTOM
 * \brief DKSLRA16 (64-bit SIMD 16-bit Shift Left Logical with Saturation or Shift Right Arithmetic)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * DKSLRA16 Rd, Rs1, Rs2
 * # Rd, Rs1 are all even/odd pair of registers
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit elements logical left (positive) or arithmetic right (negative) shift operation with
 * Q15 saturation for the left shift.
 *
 * **Description**:\n
 * The 16-bit data elements of Rs1 are left-shifted logically or right-shifted arithmetically
 * based on the value of Rs2[4:0]. Rs2[4:0] is in the signed range of [-2^4, 2^4-1]. A positive Rs2[4:0] means
 * logical left shift and a negative Rs2[4:0] means arithmetic right shift. The shift amount is the
 * absolute value of Rs2[4:0]. However, the behavior of `Rs2[4:0]==-2^4 (0x10)` is defined to be
 * equivalent to the behavior of `Rs2[4:0]==-(2^4-1) (0x11)`.
 * The left-shifted results are saturated to the 16-bit signed integer range of [-2^15, 2^15-1].
 * After the shift, saturation, or rounding, the final results are written to
 * Rd. If any saturation happens, this instruction sets the OV flag. The value of Rs2[31:5] will not affect
 * this instruction.
 *
 * **Operations**:\n
 * ~~~
 * if (Rs2[4:0] < 0) {
 *   sa = -Rs2[4:0];
 *   sa = (sa == 16)? 15 : sa;
 *   Rd.H[x] = SE16(Rs1.H[x][15:sa]);
 * } else {
 *   sa = Rs2[3:0];
 *   res[(15+sa):0] = Rs1.H[x] <<(logic) sa;
 *   if (res > (2^15)-1) {
 *     res[15:0] = 0x7fff; OV = 1;
 *   } else if (res < -2^15) {
 *     res[15:0] = 0x8000; OV = 1;
 *   }
 *   d.H[x] = res[15:0];
 * }
 * for RV32: x=3...0,
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_DKSLRA16(unsigned long long a, int b)
{
    unsigned long long result;
    __ASM volatile("dkslra16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for A.6. DKSLRA16 ===== */

/* ===== Inline Function Start for A.7. DKADD8 ===== */
/**
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NUCLEI_CUSTOM
 * \brief DKADD8 (64-bit SIMD 8-bit Signed Saturating Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * DKADD8 Rd, Rs1, Rs2
 * # Rd, Rs1, Rs2 are all even/odd pair of registers
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit signed integer element saturating additions simultaneously.
 *
 * **Description**:\n
 * This instruction adds the 8-bit signed integer elements in Rs1 with the 8-bit signed
 * integer elements in Rs2. If any of the results are beyond the Q7 number range (-2^7 <= Q7 <= 2^7-1), they
 * are saturated to the range and the OV bit is set to 1. The saturated results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * res[x] = Rs1.B[x] + Rs2.B[x];
 * if (res[x] > 127) {
 *   res[x] = 127;
 *   OV = 1;
 * } else if (res[x] < -128) {
 *   res[x] = -128;
 *   OV = 1;
 * }
 * Rd.B[x] = res[x];
 * for RV32: x=7...0,
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_DKADD8(unsigned long long a, unsigned long long b)
{
    unsigned long long result;
    __ASM volatile("dkadd8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for A.7. DKADD8 ===== */

/* ===== Inline Function Start for A.8. DKADD16 ===== */
/**
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NUCLEI_CUSTOM
 * \brief DKADD16 (64-bit SIMD 16-bit Signed Saturating Addition)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * DKADD16 Rd, Rs1, Rs2
 * # Rd, Rs1, Rs2 are all even/odd pair of registers
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit signed integer element saturating additions simultaneously.
 *
 * **Description**:\n
 * This instruction adds the 16-bit signed integer elements in Rs1 with the 16-bit signed
 * integer elements in Rs2. If any of the results are beyond the Q15 number range (-2^15 <= Q15 <= 2^15-1),
 * they are saturated to the range and the OV bit is set to 1. The saturated results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * res[x] = Rs1.H[x] + Rs2.H[x];
 * if (res[x] > 32767) {
 *   res[x] = 32767;
 *   OV = 1;
 * } else if (res[x] < -32768) {
 *   res[x] = -32768;
 *   OV = 1;
 * }
 * Rd.H[x] = res[x];
 * for RV32: x=3...0,
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_DKADD16(unsigned long long a, unsigned long long b)
{
    unsigned long long result;
    __ASM volatile("dkadd16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for A.8. DKADD16 ===== */

/* ===== Inline Function Start for A.10. DKSUB8 ===== */
/**
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NUCLEI_CUSTOM
 * \brief DKSUB8 (64-bit SIMD 8-bit Signed Saturating Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * DKSUB8 Rd, Rs1, Rs2
 * # Rd, Rs1, Rs2 are all even/odd pair of registers
 * ~~~
 *
 * **Purpose**:\n
 * Do 8-bit signed elements saturating subtractions simultaneously.
 *
 * **Description**:\n
 * This instruction subtracts the 8-bit signed integer elements in Rs2 from the 8-bit
 * signed integer elements in Rs1. If any of the results are beyond the Q7 number range (-2^7 <= Q7 <= 2^7-1),
 * they are saturated to the range and the OV bit is set to 1. The saturated results are written to Rd.
 *
 * **Operations**:\n
 * ~~~
 * res[x] = Rs1.B[x] - Rs2.B[x];
 * if (res[x] > (2^7)-1) {
 *   res[x] = (2^7)-1;
 *   OV = 1;
 * } else if (res[x] < -2^7) {
 *   res[x] = -2^7;
 *   OV = 1;
 * }
 * Rd.B[x] = res[x];
 * for RV32: x=7...0,
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_DKSUB8(unsigned long long a, unsigned long long b)
{
    unsigned long long result;
    __ASM volatile("dksub8 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for A.9. DKSUB8 ===== */

/* ===== Inline Function Start for A.10. DKSUB16 ===== */
/**
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NUCLEI_CUSTOM
 * \brief DKSUB16 (64-bit SIMD 16-bit Signed Saturating Subtraction)
 * \details
 * **Type**: SIMD
 *
 * **Syntax**:\n
 * ~~~
 * DKSUB16 Rd, Rs1, Rs2
 * # Rd, Rs1, Rs2 are all even/odd pair of registers
 * ~~~
 *
 * **Purpose**:\n
 * Do 16-bit signed integer elements saturating subtractions simultaneously.
 *
 * **Description**:\n
 * This instruction subtracts the 16-bit signed integer elements in Rs2 from the 16-bit
 * signed integer elements in Rs1. If any of the results are beyond the Q15 number range (-2^15 <= Q15 <=
 * 2^15-1), they are saturated to the range and the OV bit is set to 1. The saturated results are written to
 * Rd.
 *
 * **Operations**:\n
 * ~~~
 * res[x] = Rs1.H[x] - Rs2.H[x];
 * if (res[x] > (2^15)-1) {
 *   res[x] = (2^15)-1;
 *   OV = 1;
 * } else if (res[x] < -2^15) {
 *   res[x] = -2^15;
 *   OV = 1;
 * }
 * Rd.H[x] = res[x];
 * for RV32: x=3...0,
 * ~~~
 *
 * \param [in]  a
 * \param [in]  b
 * \return
 */
__STATIC_FORCEINLINE unsigned long long __RV_DKSUB16(unsigned long long a, unsigned long long b)
{
    unsigned long long result;
    __ASM volatile("dksub16 %0, %1, %2" : "=r"(result) : "r"(a), "r"(b));
    return result;
}
/* ===== Inline Function End for A.10. DKSUB16 ===== */

/* ===== Inline Function Start for A.11.1. EXPD80 ===== */
/**
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NUCLEI_CUSTOM
 * \brief EXPD80 (Expand and Copy Byte 0 to 32bit)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * EXPD80 Rd, Rs1
 * ~~~
 *
 * **Purpose**:\n
 * Copy 8-bit data from 32-bit chunks into 4 bytes in a register.
 *
 * **Description**:\n
 * Moves Rs1.B[0][7:0] to Rd.[0][7:0], Rd.[1][7:0], Rd.[2][7:0], Rd.[3][7:0]
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:0] = CONCAT(Rs1.B[0][7:0], Rs1.B[0][7:0], Rs1.B[0][7:0], Rs1.B[0][7:0]);
 * for RV32: x=0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_EXPD80(unsigned long a)
{
    unsigned long result;
    __ASM volatile("expd80 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for A11.1. EXPD80 ===== */

/* ===== Inline Function Start for A.11.2. EXPD81 ===== */
/**
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NUCLEI_CUSTOM
 * \brief EXPD81 (Expand and Copy Byte 1 to 32bit)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * EXPD81 Rd, Rs1
 * ~~~
 *
 * **Purpose**:\n
 * Copy 8-bit data from 32-bit chunks into 4 bytes in a register.
 *
 * **Description**:\n
 * Moves Rs1.B[1][7:0] to Rd.[0][7:0], Rd.[1][7:0], Rd.[2][7:0], Rd.[3][7:0]
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:0] = CONCAT(Rs1.B[1][7:0], Rs1.B[1][7:0], Rs1.B[1][7:0], Rs1.B[1][7:0]);
 * for RV32: x=0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_EXPD81(unsigned long a)
{
    unsigned long result;
    __ASM volatile("expd81 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for A11.2. EXPD81 ===== */

/* ===== Inline Function Start for A.11.3. EXPD82 ===== */
/**
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NUCLEI_CUSTOM
 * \brief EXPD82 (Expand and Copy Byte 2 to 32bit)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * EXPD82 Rd, Rs1
 * ~~~
 *
 * **Purpose**:\n
 * Copy 8-bit data from 32-bit chunks into 4 bytes in a register.
 *
 * **Description**:\n
 * Moves Rs1.B[2][7:0] to Rd.[0][7:0], Rd.[1][7:0], Rd.[2][7:0], Rd.[3][7:0]
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:0] = CONCAT(Rs1.B[2][7:0], Rs1.B[2][7:0], Rs1.B[2][7:0], Rs1.B[2][7:0]);
 * for RV32: x=0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_EXPD82(unsigned long a)
{
    unsigned long result;
    __ASM volatile("expd82 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for A11.3. EXPD82 ===== */

/* ===== Inline Function Start for A.11.4. EXPD83 ===== */
/**
 * \ingroup  NMSIS_Core_DSP_Intrinsic_NUCLEI_CUSTOM
 * \brief EXPD83 (Expand and Copy Byte 3 to 32bit)
 * \details
 * **Type**: DSP
 *
 * **Syntax**:\n
 * ~~~
 * EXPD83 Rd, Rs1
 * ~~~
 *
 * **Purpose**:\n
 * Copy 8-bit data from 32-bit chunks into 4 bytes in a register.
 *
 * **Description**:\n
 * Moves Rs1.B[3][7:0] to Rd.[0][7:0], Rd.[1][7:0], Rd.[2][7:0], Rd.[3][7:0]
 *
 * **Operations**:\n
 * ~~~
 * Rd.W[x][31:0] = CONCAT(Rs1.B[3][7:0], Rs1.B[3][7:0], Rs1.B[3][7:0], Rs1.B[3][7:0]);
 * for RV32: x=0
 * ~~~
 *
 * \param [in]  a
 * \return
 */
__STATIC_FORCEINLINE unsigned long __RV_EXPD83(unsigned long a)
{
    unsigned long result;
    __ASM volatile("expd83 %0, %1" : "=r"(result) : "r"(a));
    return result;
}
/* ===== Inline Function End for A11.4. EXPD83 ===== */

#if defined(__RISCV_FEATURE_DSP) && (__RISCV_FEATURE_DSP == 1)
/* XXXXX ARM Compatiable SIMD API XXXXX */
/** \brief Q setting quad 8-bit saturating addition. */
#define __QADD8(x, y)               __RV_KADD8(x, y)
/** \brief Q setting quad 8-bit saturating subtract. */
#define __QSUB8(x, y)               __RV_KSUB8((x), (y))
/** \brief Q setting dual 16-bit saturating addition. */
#define __QADD16(x, y)              __RV_KADD16((x), (y))
/** \brief Dual 16-bit signed addition with halved results. */
#define __SHADD16(x, y)             __RV_RADD16((x), (y))
/** \brief Q setting dual 16-bit saturating subtract. */
#define __QSUB16(x, y)              __RV_KSUB16((x), (y))
/** \brief Dual 16-bit signed subtraction with halved results. */
#define __SHSUB16(x, y)             __RV_RSUB16((x), (y))
/** \brief Q setting dual 16-bit add and subtract with exchange. */
#define __QASX(x, y)                __RV_KCRAS16((x), (y))
/** \brief Dual 16-bit signed addition and subtraction with halved results.*/
#define __SHASX(x, y)               __RV_RCRAS16((x), (y))
/** \brief Q setting dual 16-bit subtract and add with exchange. */
#define __QSAX(x, y)                __RV_KCRSA16((x), (y))
/** \brief Dual 16-bit signed subtraction and addition with halved results.*/
#define __SHSAX(x, y)               __RV_RCRSA16((x), (y))
/** \brief Dual 16-bit signed multiply with exchange returning difference. */
#define __SMUSDX(x, y)              __RV_SMXDS((y), (x))
/** \brief Q setting sum of dual 16-bit signed multiply with exchange. */
__STATIC_FORCEINLINE int32_t __SMUADX (int32_t op1, int32_t op2)
{
    return (int32_t)__RV_KMXDA(op1, op2);
}
/** \brief Q setting saturating add. */
#define __QADD(x, y)                __RV_KADDW((x), (y))
/** \brief Q setting saturating subtract. */
#define __QSUB(x, y)                __RV_KSUBW((x), (y))
/** \brief Q setting dual 16-bit signed multiply with single 32-bit accumulator. */
__STATIC_FORCEINLINE int32_t __SMLAD(int32_t op1, int32_t op2, int32_t op3)
{
    return (int32_t)__RV_KMADA(op3, op1, op2);
}
/** \brief Q setting pre-exchanged dual 16-bit signed multiply with single 32-bit accumulator.  */
__STATIC_FORCEINLINE int32_t __SMLADX(int32_t op1, int32_t op2, int32_t op3)
{
    return (int32_t)__RV_KMAXDA(op3, op1, op2);
}
/** \brief Q setting dual 16-bit signed multiply with exchange subtract with 32-bit accumulate.  */
__STATIC_FORCEINLINE int32_t __SMLSDX(int32_t op1, int32_t op2, int32_t op3)
{
    return (op3 - (int32_t)__RV_SMXDS(op1, op2));
}
/** \brief Dual 16-bit signed multiply with single 64-bit accumulator. */
__STATIC_FORCEINLINE int64_t __SMLALD(int32_t op1, int32_t op2, int64_t acc)
{
    return (int64_t)__RV_SMALDA(acc, op1, op2);
}
/** \brief Dual 16-bit signed multiply with exchange with single 64-bit accumulator.  */
__STATIC_FORCEINLINE int64_t __SMLALDX(int32_t op1, int32_t op2, int64_t acc)
{
    return (int64_t)__RV_SMALXDA(acc, op1, op2);
}
/** \brief Q setting sum of dual 16-bit signed multiply. */
__STATIC_FORCEINLINE int32_t __SMUAD(int32_t op1, int32_t op2)
{
    return (int32_t)__RV_KMDA(op1, op2);
}
/** \brief Dual 16-bit signed multiply returning difference. */
__STATIC_FORCEINLINE int32_t __SMUSD(int32_t op1, int32_t op2)
{
    return (int32_t)__RV_SMDRS(op1, op2);
}
/** \brief Dual extract 8-bits and sign extend each to 16-bits. */
#define __SXTB16(x)             __RV_SUNPKD820(x)
/** \brief Dual extracted 8-bit to 16-bit signed addition. TODO Need test */
__STATIC_FORCEINLINE int32_t __SXTAB16(uint32_t op1, uint32_t op2)
{
    return __RV_ADD16(op1, __RV_SUNPKD830(op2));
}
/** \brief 32-bit signed multiply with 32-bit truncated accumulator. */
__STATIC_FORCEINLINE int32_t __SMMLA(int32_t op1, int32_t op2, int32_t op3)
{
    int32_t mul;
    mul = (int32_t)__RV_SMMUL(op1, op2);
    return (op3 + mul);
}
#define __DKHM8                 __RV_DKHM8
#define __DKHM16                __RV_DKHM16
#define __DKSUB16               __RV_DKSUB16
#define __SMAQA                 __RV_SMAQA
#define __MULSR64               __RV_MULSR64
#define __DQADD8                __RV_DKADD8
#define __DQSUB8                __RV_DKSUB8
#define __DKADD16               __RV_DKADD16
#define __PKBB16                __RV_PKBB16
#define __DKSLRA16              __RV_DKSLRA16
#define __DKSLRA8               __RV_DKSLRA8
#define __KABSW                 __RV_KABSW
#define __DKABS8                __RV_DKABS8
#define __DKABS16               __RV_DKABS16
#define __SMALDA                __RV_SMALDA
#define __SMSLDA                __RV_SMSLDA
#define __SMALBB                __RV_SMALBB
#define __SUB64                 __RV_SUB64
#define __ADD64                 __RV_ADD64
#define __SMBB16                __RV_SMBB16
#define __SMBT16                __RV_SMBT16
#define __SMTT16                __RV_SMTT16
#define __EXPD80                __RV_EXPD80
#define __SMAX8                 __RV_SMAX8
#define __SMAX16                __RV_SMAX16
#define __PKTT16                __RV_PKTT16
#define __KADD16                __RV_KADD16
#define __SADD16                __RV_ADD16

#endif /* (__RISCV_FEATURE_DSP == 1) */

#endif /* defined(__DSP_PRESENT) && (__DSP_PRESENT == 1) */

/** \brief Halfword packing instruction. Combines bits[15:0] of val1 with bits[31:16] of val2 levitated with the val3. */
#define __PKHBT(ARG1,ARG2,ARG3)          ( ((((uint32_t)(ARG1))          ) & 0x0000FFFFUL) |  \
                                           ((((uint32_t)(ARG2)) << (ARG3)) & 0xFFFF0000UL)  )
/** \brief Halfword packing instruction. Combines bits[31:16] of val1 with bits[15:0] of val2 right-shifted with the val3. */
#define __PKHTB(ARG1,ARG2,ARG3)          ( ((((uint32_t)(ARG1))          ) & 0xFFFF0000UL) |  \
                                           ((((uint32_t)(ARG2)) >> (ARG3)) & 0x0000FFFFUL)  )

#ifdef __cplusplus
}
#endif

#endif /* __CORE_FEATURE_DSP__ */
