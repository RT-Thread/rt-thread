/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_BACC_DRV_H
#define HPM_BACC_DRV_H

#include "hpm_common.h"
#include "hpm_bacc_regs.h"

/**
 *
 * @brief BACC driver APIs
 * @defgroup bacc_interface BACC driver APIs
 * @ingroup io_interfaces
 * @{
 */

/* @brief Timing gap ratios */
typedef enum {
    bacc_ratio_0 = 0,
    bacc_ratio_1_32768 = 1,
    bacc_ratio_1_16384 = 2,
    bacc_ratio_1_8192 = 3,
    bacc_ratio_1_4096 = 4,
    bacc_ratio_1_2048 = 5,
    bacc_ratio_1_1024 = 6,
    bacc_ratio_1_512 = 7,
    bacc_ratio_1_256 = 8,
    bacc_ratio_1_128 = 9,
    bacc_ratio_1_64 = 10,
    bacc_ratio_1_32 = 11,
    bacc_ratio_1_16 = 12,
    bacc_ratio_1_8 = 13,
    bacc_ratio_1_4 = 14,
    bacc_ratio_1_2 = 15,
} bacc_ratio_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * brief set timing gap after rising edge
 *
 * @param[in] ptr BACC base address
 * @param[in] ratio Ratio of guard band after rising edge
 * @param[in] offset Guard band after rising edge (16 bits)
 */
static inline void bacc_timing_gap_post(BACC_Type *ptr, bacc_ratio_t ratio, uint16_t offset)
{
    ptr->PRE_TIME = BACC_PRE_TIME_POST_RATIO_SET(ratio)
        | BACC_PRE_TIME_POST_OFFSET_SET(offset);
}

/*
 * brief set timing gap before rising edge
 *
 * @param[in] ptr BACC base address
 * @param[in] ratio Ratio of guard band before rising edge
 * @param[in] offset Guard band before rising edge (16 bits)
 */
static inline void bacc_timing_gap_pre(BACC_Type *ptr, bacc_ratio_t ratio, uint16_t offset)
{
    ptr->PRE_TIME = BACC_PRE_TIME_PRE_RATIO_SET(ratio)
        | BACC_PRE_TIME_PRE_OFFSET_SET(offset);
}

/*
 * brief disable fast read
 *
 * @param[in] ptr BACC base address
 */
static inline void bacc_disable_fast_read(BACC_Type *ptr)
{
    ptr->CONFIG &= ~BACC_CONFIG_FAST_READ_MASK;
}

/*
 * brief enable fast read
 *
 * @param[in] ptr BACC base address
 */
static inline void bacc_enable_fast_read(BACC_Type *ptr)
{
    ptr->CONFIG |= BACC_CONFIG_FAST_READ_MASK;
}

/*
 * brief disable fast wirte
 *
 * @param[in] ptr BACC base address
 */
static inline void bacc_disable_fast_write(BACC_Type *ptr)
{
    ptr->CONFIG &= ~BACC_CONFIG_FAST_WRITE_MASK;
}

/*
 * brief enable fast wirte
 *
 * @param[in] ptr BACC base address
 */
static inline void bacc_enable_fast_write(BACC_Type *ptr)
{
    ptr->CONFIG |= BACC_CONFIG_FAST_WRITE_MASK;
}

/*
 * brief set timing of access
 *
 * @param[in] ptr BACC base address
 * @param[in] timing Time in APB clock cycles (16 bits)
 */
static inline void bacc_set_timing(BACC_Type *ptr, uint16_t timing)
{
    ptr->CONFIG = (ptr->CONFIG & ~(BACC_CONFIG_TIMING_MASK))
        | BACC_CONFIG_TIMING_SET(timing);
}

#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#endif /* HPM_BACC_DRV_H */
