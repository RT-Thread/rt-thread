/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_BACC_H
#define HPM_BACC_H

typedef struct {
    __RW uint32_t CONFIG;                      /* 0x0: Access timing for access */
    __R  uint8_t  RESERVED0[4];                /* 0x4 - 0x7: Reserved */
    __RW uint32_t PRE_TIME;                    /* 0x8: Timing gap before rising edge */
    __RW uint32_t POST_TIME;                   /* 0xC: Timing gap after rising edge */
} BACC_Type;


/* Bitfield definition for register: CONFIG */
/*
 * FAST_WRITE (RW)
 *
 * Use fast write
 * 0: Write normally
 * 1: boost write
 */
#define BACC_CONFIG_FAST_WRITE_MASK (0x20000000UL)
#define BACC_CONFIG_FAST_WRITE_SHIFT (29U)
#define BACC_CONFIG_FAST_WRITE_SET(x) (((uint32_t)(x) << BACC_CONFIG_FAST_WRITE_SHIFT) & BACC_CONFIG_FAST_WRITE_MASK)
#define BACC_CONFIG_FAST_WRITE_GET(x) (((uint32_t)(x) & BACC_CONFIG_FAST_WRITE_MASK) >> BACC_CONFIG_FAST_WRITE_SHIFT)

/*
 * FAST_READ (RW)
 *
 * Use fast read
 * 0: Read normally
 * 1: boost read
 */
#define BACC_CONFIG_FAST_READ_MASK (0x10000000UL)
#define BACC_CONFIG_FAST_READ_SHIFT (28U)
#define BACC_CONFIG_FAST_READ_SET(x) (((uint32_t)(x) << BACC_CONFIG_FAST_READ_SHIFT) & BACC_CONFIG_FAST_READ_MASK)
#define BACC_CONFIG_FAST_READ_GET(x) (((uint32_t)(x) & BACC_CONFIG_FAST_READ_MASK) >> BACC_CONFIG_FAST_READ_SHIFT)

/*
 * TIMING (RW)
 *
 * Time in APB clock cycles, for battery timing penerate
 */
#define BACC_CONFIG_TIMING_MASK (0xFFFFU)
#define BACC_CONFIG_TIMING_SHIFT (0U)
#define BACC_CONFIG_TIMING_SET(x) (((uint32_t)(x) << BACC_CONFIG_TIMING_SHIFT) & BACC_CONFIG_TIMING_MASK)
#define BACC_CONFIG_TIMING_GET(x) (((uint32_t)(x) & BACC_CONFIG_TIMING_MASK) >> BACC_CONFIG_TIMING_SHIFT)

/* Bitfield definition for register: PRE_TIME */
/*
 * PRE_RATIO (RW)
 *
 * Ratio of guard band before rising edge
 * 0: 0
 * 1: 1/32768 of low level width
 * 2: 1/16384 of low level width
 * 14: 1/4 of low level width
 * 15: 1/2 of low level width
 */
#define BACC_PRE_TIME_PRE_RATIO_MASK (0xF0000UL)
#define BACC_PRE_TIME_PRE_RATIO_SHIFT (16U)
#define BACC_PRE_TIME_PRE_RATIO_SET(x) (((uint32_t)(x) << BACC_PRE_TIME_PRE_RATIO_SHIFT) & BACC_PRE_TIME_PRE_RATIO_MASK)
#define BACC_PRE_TIME_PRE_RATIO_GET(x) (((uint32_t)(x) & BACC_PRE_TIME_PRE_RATIO_MASK) >> BACC_PRE_TIME_PRE_RATIO_SHIFT)

/*
 * PRE_OFFSET (RW)
 *
 * guard band before rising edge
 * this value will be added to ratio number
 */
#define BACC_PRE_TIME_PRE_OFFSET_MASK (0xFFFFU)
#define BACC_PRE_TIME_PRE_OFFSET_SHIFT (0U)
#define BACC_PRE_TIME_PRE_OFFSET_SET(x) (((uint32_t)(x) << BACC_PRE_TIME_PRE_OFFSET_SHIFT) & BACC_PRE_TIME_PRE_OFFSET_MASK)
#define BACC_PRE_TIME_PRE_OFFSET_GET(x) (((uint32_t)(x) & BACC_PRE_TIME_PRE_OFFSET_MASK) >> BACC_PRE_TIME_PRE_OFFSET_SHIFT)

/* Bitfield definition for register: POST_TIME */
/*
 * POST_RATIO (RW)
 *
 * Ratio of guard band after rising edge
 * 0: 0
 * 1: 1/32768 of high level width
 * 2: 1/16384 of high level width
 * 14: 1/4 of high level width
 * 15: 1/2 of high level width
 */
#define BACC_POST_TIME_POST_RATIO_MASK (0xF0000UL)
#define BACC_POST_TIME_POST_RATIO_SHIFT (16U)
#define BACC_POST_TIME_POST_RATIO_SET(x) (((uint32_t)(x) << BACC_POST_TIME_POST_RATIO_SHIFT) & BACC_POST_TIME_POST_RATIO_MASK)
#define BACC_POST_TIME_POST_RATIO_GET(x) (((uint32_t)(x) & BACC_POST_TIME_POST_RATIO_MASK) >> BACC_POST_TIME_POST_RATIO_SHIFT)

/*
 * POST_OFFSET (RW)
 *
 * guard band after rising edge
 * this value will be added to ratio number
 */
#define BACC_POST_TIME_POST_OFFSET_MASK (0xFFFFU)
#define BACC_POST_TIME_POST_OFFSET_SHIFT (0U)
#define BACC_POST_TIME_POST_OFFSET_SET(x) (((uint32_t)(x) << BACC_POST_TIME_POST_OFFSET_SHIFT) & BACC_POST_TIME_POST_OFFSET_MASK)
#define BACC_POST_TIME_POST_OFFSET_GET(x) (((uint32_t)(x) & BACC_POST_TIME_POST_OFFSET_MASK) >> BACC_POST_TIME_POST_OFFSET_SHIFT)




#endif /* HPM_BACC_H */
