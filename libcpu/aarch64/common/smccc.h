/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     GuEe-GUI     The first version
 */

#include <stdint.h>

/*
 * The ARM SMCCC v1.0 calling convention provides the following guarantees about registers:
 *  Register     Modified    Return State
 *  X0...X3      Yes         Result values
 *  X4...X17     Yes         Unpredictable
 *  X18...X30    No          Preserved
 *  SP_EL0       No          Preserved
 *  SP_ELx       No          Preserved
 */

struct arm_smccc_ret
{
    uint64_t x0;    /* Parameter registers */
    uint64_t x1;    /* Parameter registers */
    uint64_t x2;    /* Parameter registers */
    uint64_t x3;    /* Parameter registers */
    uint64_t x6;    /* Parameter register: Optional Session ID register */
};

struct arm_smccc_ret arm_smc_call(uint32_t w0, uint64_t x1, uint64_t x2, uint64_t x3, uint64_t x4, uint64_t x5, uint64_t x6, uint32_t w7);
struct arm_smccc_ret arm_hvc_call(uint32_t w0, uint64_t x1, uint64_t x2, uint64_t x3, uint64_t x4, uint64_t x5, uint64_t x6, uint32_t w7);
