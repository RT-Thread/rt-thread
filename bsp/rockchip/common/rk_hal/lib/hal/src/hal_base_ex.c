/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_base.h"

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup HAL_BASE_EX
 *  @{
 */

/** @addtogroup HAL_BASE_EX_How_To_Use How To Use
 *  @{

 The HAL_BASE_EX driver can be used as follows:

 @} */

/** @defgroup HAL_BASE_EX_Private_Definition Private Definition
 *  @{
 */
/********************* Private MACRO Definition ******************************/

/********************* Private Structure Definition **************************/

/********************* Private Variable Definition ***************************/

/********************* Private Function Definition ***************************/

/** @} */
/********************* Public Function Definition ***************************/
/** @defgroup HAL_BASE_EX_Exported_Functions_Group5 Other Functions
 *  @{
 */

/**
 * @brief  uint64_t numerator / uint32_t denominator with remainder
 * @param  numerator
 * @param  denominator
 * @param  pRemainder [out] pointer to unsigned 32bit remainder
 * @return uint64_t result. sets *pRemainder if pRemainder is not null
 */
uint64_t HAL_DivU64Rem(uint64_t numerator, uint32_t denominator, uint32_t *pRemainder)
{
    uint64_t remainder = numerator;
    uint64_t b = denominator;
    uint64_t result;
    uint64_t d = 1;
    uint32_t high = numerator >> 32;

    result = 0;
    if (high >= denominator) {
        high /= denominator;
        result = (uint64_t)high << 32;
        remainder -= (uint64_t)(high * denominator) << 32;
    }

    while ((int64_t)b > 0 && b < remainder) {
        b = b + b;
        d = d + d;
    }

    do {
        if (remainder >= b) {
            remainder -= b;
            result += d;
        }
        b >>= 1;
        d >>= 1;
    } while (d);

    if (pRemainder) {
        *pRemainder = remainder;
    }

    return result;
}

/** @} */

/** @} */

/** @} */
