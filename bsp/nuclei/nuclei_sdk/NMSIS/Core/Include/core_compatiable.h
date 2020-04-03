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
#ifndef __CORE_COMPATIABLE_H__
#define __CORE_COMPATIABLE_H__
/*!
 * @file     core_compatiable.h
 * @brief    ARM compatiable function definitions header file
 */
#ifdef __cplusplus
 extern "C" {
#endif

/* ===== ARM Compatiable Functions ===== */
/**
 * \defgroup NMSIS_Core_ARMCompatiable_Functions   ARM Compatiable Functions
 * \ingroup  NMSIS_Core
 * \brief    A few functions that compatiable with ARM CMSIS-Core.
 * \details
 *
 * Here we provided a few functions that compatiable with ARM CMSIS-Core,
 * mostly used in the DSP and NN library.
 * @{
 */
/** \brief Instruction Synchronization Barrier, compatiable with ARM */
#define __ISB()                             __RWMB()

/** \brief Data Synchronization Barrier, compatiable with ARM */
#define __DSB()                             __RWMB()

/** \brief Data Memory Barrier, compatiable with ARM */
#define __DMB()                             __RWMB()

/** \brief LDRT Unprivileged (8 bit), ARM Compatiable */
#define __LDRBT(ptr)                        __LB((ptr))
/** \brief LDRT Unprivileged (16 bit), ARM Compatiable */
#define __LDRHT(ptr)                        __LH((ptr))
/** \brief LDRT Unprivileged (32 bit), ARM Compatiable */
#define __LDRT(ptr)                         __LW((ptr))

/** \brief STRT Unprivileged (8 bit), ARM Compatiable */
#define __STRBT(ptr)                        __SB((ptr))
/** \brief STRT Unprivileged (16 bit), ARM Compatiable */
#define __STRHT(ptr)                        __SH((ptr))
/** \brief STRT Unprivileged (32 bit), ARM Compatiable */
#define __STRT(ptr)                         __SW((ptr))

/* ===== Saturation Operations ===== */
/**
 * \brief   Signed Saturate
 * \details Saturates a signed value.
 * \param [in]  value  Value to be saturated
 * \param [in]    sat  Bit position to saturate to (1..32)
 * \return             Saturated value
 */
__STATIC_FORCEINLINE int32_t __SSAT(int32_t val, uint32_t sat)
{
    if ((sat >= 1U) && (sat <= 32U)) {
        const int32_t max = (int32_t)((1U << (sat - 1U)) - 1U);
        const int32_t min = -1 - max ;
        if (val > max) {
            return max;
        } else if (val < min) {
            return min;
        }
    }
    return val;
}

/**
 * \brief   Unsigned Saturate
 * \details Saturates an unsigned value.
 * \param [in]  value  Value to be saturated
 * \param [in]    sat  Bit position to saturate to (0..31)
 * \return             Saturated value
 */
__STATIC_FORCEINLINE uint32_t __USAT(int32_t val, uint32_t sat)
{
    if (sat <= 31U) {
        const uint32_t max = ((1U << sat) - 1U);
        if (val > (int32_t)max) {
            return max;
        } else if (val < 0) {
            return 0U;
        }
    }
    return (uint32_t)val;
}

/* ===== Data Processing Operations ===== */
/**
 * \brief   Reverse byte order (32 bit)
 * \details Reverses the byte order in unsigned integer value.
 * For example, 0x12345678 becomes 0x78563412.
 * \param [in]    value  Value to reverse
 * \return               Reversed value
 */
__STATIC_FORCEINLINE uint32_t __REV(uint32_t value)
{
    uint32_t result;

    result =  ((value & 0xff000000) >> 24)
        | ((value & 0x00ff0000) >> 8 )
        | ((value & 0x0000ff00) << 8 )
        | ((value & 0x000000ff) << 24);
    return result;
}

/**
 * \brief   Reverse byte order (16 bit)
 * \details Reverses the byte order within each halfword of a word.
 * For example, 0x12345678 becomes 0x34127856.
 * \param [in]    value  Value to reverse
 * \return               Reversed value
 */
__STATIC_FORCEINLINE uint32_t __REV16(uint32_t value)
{
    uint32_t result;
    result =  ((value & 0xff000000) >> 8)
        | ((value & 0x00ff00000) << 8 )
        | ((value & 0x0000ff00) >> 8 )
        | ((value & 0x000000ff) << 8) ;

    return result;
}

/**
 * \brief   Reverse byte order (16 bit)
 * \details Reverses the byte order in a 16-bit value
 * and returns the signed 16-bit result.
 * For example, 0x0080 becomes 0x8000.
 * \param [in]    value  Value to reverse
 * \return               Reversed value
 */
__STATIC_FORCEINLINE int16_t __REVSH(int16_t value)
{
    int16_t result;
    result = ((value & 0xff00) >> 8) | ((value & 0x00ff) << 8);
    return result;
}

/**
 * \brief   Rotate Right in unsigned value (32 bit)
 * \details Rotate Right (immediate) provides the value of
 * the contents of a register rotated by a variable number of bits.
 * \param [in]    op1  Value to rotate
 * \param [in]    op2  Number of Bits to rotate(0-31)
 * \return               Rotated value
 */
__STATIC_FORCEINLINE uint32_t __ROR(uint32_t op1, uint32_t op2)
{
    op2 = op2 & 0x1F;
    if (op2 == 0U) {
      return op1;
    }
    return (op1 >> op2) | (op1 << (32U - op2));
}

/**
 * \brief   Reverse bit order of value
 * \details Reverses the bit order of the given value.
 * \param [in]    value  Value to reverse
 * \return               Reversed value
 */
#if defined(__DSP_PRESENT) && (__DSP_PRESENT == 1)
#define __RBIT(value)           __RV_BITREV((value), 31)
#else
__STATIC_FORCEINLINE uint32_t __RBIT(uint32_t value)
{
    uint32_t result;
    uint32_t s = (4U /*sizeof(v)*/ * 8U) - 1U; /* extra shift needed at end */

    result = value; /* r will be reversed bits of v; first get LSB of v */
    for (value >>= 1U; value != 0U; value >>= 1U) {
        result <<= 1U;
        result |= value & 1U;
        s--;
    }
    result <<= s; /* shift when v's highest bits are zero */
    return result;
}
#endif /* defined(__DSP_PRESENT) && (__DSP_PRESENT == 1) */

/**
 * \brief   Count leading zeros
 * \details Counts the number of leading zeros of a data value.
 * \param [in]  data  Value to count the leading zeros
 * \return             number of leading zeros in value
 */
#if defined(__DSP_PRESENT) && (__DSP_PRESENT == 1)
#define __CLZ(data)         __RV_CLZ32(data)
#else
__STATIC_FORCEINLINE uint8_t __CLZ(uint32_t data)
{
    uint8_t ret = 0;
    uint32_t temp = ~data;
    while (temp & 0x80000000) {
          temp <<= 1;
          ret++;
    }
    return ret;
}
#endif /* defined(__DSP_PRESENT) && (__DSP_PRESENT == 1) */

/** @} */ /* End of Doxygen Group NMSIS_Core_ARMCompatiable_Functions */

#ifdef __cplusplus
}
#endif
#endif /* __CORE_COMPATIABLE_H__ */
