/*
 * Copyright (c) 2021-2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_COMMON_H
#define _HPM_COMMON_H

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/**
 *
 * @brief COMMON driver APIs
 * @defgroup common_interface COMMON driver APIs
 * @{
 *
 */

#define __R volatile const /* Define "read-only" permission */
#define __RW volatile      /* Define "read-write" permission */
#define __W volatile       /* Define "write-only" permission */

#ifndef __I
#define __I __R
#endif

#ifndef __IO
#define __IO __RW
#endif

#ifndef __O
#define __O __W
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a)   (sizeof(a) / sizeof((a)[0]))
#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#define HPM_BITSMASK(val, offset) ((uint32_t)(val) << (offset))
#define IS_HPM_BITMASK_SET(val, mask) (((uint32_t)(val) & (uint32_t)(mask)) != 0U)
#define IS_HPM_BIT_SET(val, offset) (((uint32_t)(val) & (1UL << (offset))) != 0U)
#define IS_HPM_BITMASK_CLR(val, mask) (((uint32_t)(val) & (uint32_t)(mask)) == 0U)
#define IS_HPM_BIT_CLR(val, offset) (((uint32_t)(val) & (1UL << (offset))) == 0U)

#define HPM_BREAK_IF(cond)   if (cond) { break; }
#define HPM_CONTINUE_IF(cond) if (cond) { continue; }

#define HPM_CHECK_RET(x)               \
    do {                               \
        stat = (x);                    \
        if (status_success != stat) { \
            return stat;               \
        }                              \
    } while (false)

#define SIZE_1KB (1024UL)
#define SIZE_1MB (1048576UL)

typedef uint32_t hpm_stat_t;

/* @brief Enum definition for the Status group
 * Rule:
 *  [Group] 0-999 for the SoC driver and the corresponding components
 *       1000 or above for the application status group
 *  [Code]  Valid value: 0-999
 *
 */
#define MAKE_STATUS(group, code) ((uint32_t)(group)*1000U + (uint32_t)(code))
/* @brief System status group definitions */
enum {
    status_group_common = 0,
    status_group_uart = 1,
    status_group_i2c = 2,
    status_group_spi = 3,
    status_group_usb = 4,
    status_group_i2s = 5,
    status_group_xpi = 6,
    status_group_l1c,
    status_group_dma,
    status_group_femc,
    status_group_sdp,
    status_group_xpi_nor,
    status_group_otp,
    status_group_lcdc,
    status_group_mbx,
    status_group_rng,
    status_group_pdma,
    status_group_wdg,
    status_group_pmic_sec,
    status_group_can,
    status_group_sdxc,
    status_group_pcfg,
    status_group_clk,
    status_group_pllctl,
    status_group_pllctlv2,
    status_group_ffa,
    status_group_mcan,

    status_group_middleware_start = 500,
    status_group_sdmmc = status_group_middleware_start,
    status_group_audio_codec,
    status_group_dma_manager,
};

/* @brief Common status code definitions */
enum {
    status_success = MAKE_STATUS(status_group_common, 0),
    status_fail = MAKE_STATUS(status_group_common, 1),
    status_invalid_argument = MAKE_STATUS(status_group_common, 2),
    status_timeout = MAKE_STATUS(status_group_common, 3),
};

#if defined(__GNUC__)

/* alway_inline */
#define ATTR_ALWAYS_INLINE __attribute__((always_inline))

/* weak */
#define ATTR_WEAK __attribute__((weak))

/* alignment */
#define ATTR_ALIGN(alignment) __attribute__((aligned(alignment)))

/* place var_declare at section_name, e.x. PLACE_AT(".target_section", var); */
#define ATTR_PLACE_AT(section_name) __attribute__((section(section_name)))

#define ATTR_PLACE_AT_WITH_ALIGNMENT(section_name, alignment) \
ATTR_PLACE_AT(section_name) ATTR_ALIGN(alignment)

#define ATTR_PLACE_AT_NONCACHEABLE ATTR_PLACE_AT(".noncacheable.bss")
#define ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(alignment) \
    ATTR_PLACE_AT_NONCACHEABLE ATTR_ALIGN(alignment)

#define ATTR_PLACE_AT_NONCACHEABLE_BSS ATTR_PLACE_AT(".noncacheable.bss")
#define ATTR_PLACE_AT_NONCACHEABLE_BSS_WITH_ALIGNMENT(alignment) \
    ATTR_PLACE_AT_NONCACHEABLE_BSS ATTR_ALIGN(alignment)

/* initialize variable x with y using PLACE_AT_NONCACHEABLE_INIT(x) = {y}; */
#define ATTR_PLACE_AT_NONCACHEABLE_INIT ATTR_PLACE_AT(".noncacheable.init")
#define ATTR_PLACE_AT_NONCACHEABLE_INIT_WITH_ALIGNMENT(alignment) \
    ATTR_PLACE_AT_NONCACHEABLE_INIT ATTR_ALIGN(alignment)

#define ATTR_RAMFUNC ATTR_PLACE_AT(".fast")
#define ATTR_RAMFUNC_WITH_ALIGNMENT(alignment) \
    ATTR_RAMFUNC ATTR_ALIGN(alignment)

#define ATTR_SHARE_MEM ATTR_PLACE_AT(".sh_mem")

#define NOP() __asm volatile("nop")
#define WFI() __asm volatile("wfi")

#else
#error Unknown toolchain
#endif

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief   Count bits set to 1
 *
 * @param value Data to be counted
 *
 * @return number of bits set to 1
 */
static inline uint32_t count_set_bits(uint32_t value)
{
    if (value == 0) {
        return 0;
    }
    return 1 + count_set_bits(value & (value - 1));
}

/**
 * @brief   Count bits set to 1 from least significant bit
 *
 * @param value Data to be counted
 *
 * @return number of bits set to 1
 * @return 0xFFFFFFFF if no bit was set to 1
 */
static inline uint32_t get_first_set_bit_from_lsb(uint32_t value)
{
    uint32_t i = 0;
    if (!value) {
        return 0xFFFFFFFFUL;
    }
    while (value && !(value & 0x1)) {
        value >>= 1;
        i++;
    }
    return i;
}

/**
 * @brief   Count bits set to 1 from most significant bit
 *
 * @param value Data to be counted
 *
 * @return number of bits set to 1
 * @return 0xFFFFFFFF if no bit was set to 1
 */
static inline uint32_t get_first_set_bit_from_msb(uint32_t value)
{
    uint32_t i = 31;
    if (!value) {
        return 0xFFFFFFFFUL;
    }
    while (value && !(value & 0x80000000)) {
        value <<= 1;
        value &= ~1;
        i--;
    }
    return i;
}

#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#endif /* _HPM_COMMON_H */
