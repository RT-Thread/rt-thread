/*
 * Copyright (c) 2023-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_MCAN_SOC_H
#define HPM_MCAN_SOC_H

#include <stdint.h>
#include "hpm_mcan_regs.h"
#include "hpm_soc.h"
#include "hpm_soc_feature.h"

#define MCAN_SOC_TSU_SRC_TWO_STAGES     (1U)

#define HPM_MCAN_EXT_TBSEL_NUM  (4U)
#define HPM_MCAN_TBSEL_BASE (0xF02FF000UL)
#define HPM_MCAN_TBSEL (*(volatile uint32_t *)HPM_MCAN_TBSEL_BASE)
#define HPM_MCAN_TBSEL_BITWIDTH (6U)
#define HPM_MCAN_TBSEL_MASK ((1UL << HPM_MCAN_TBSEL_BITWIDTH) - 1UL)
#define HPM_MCAN_TBSEL0_SHIFT (8U)

/**
 * @brief MCAN MSG BUF base address (AHB_RAM)
 */
#define MCAN_MSG_BUF_SIZE_IN_WORDS (640U)
#define MCAN_IP_SLOT_SIZE (0x4000U)

/**
 * @brief TSU External Timebase Sources
 */
#define MCAN_TSU_EXT_TIMEBASE_SRC_MIN     (0U)
#define MCAN_TSU_EXT_TIMEBASE_SRC_TBSEL_0 (MCAN_TSU_EXT_TIMEBASE_SRC_MIN)
#define MCAN_TSU_EXT_TIMEBASE_SRC_TBSEL_1 (1U)
#define MCAN_TSU_EXT_TIMEBASE_SRC_TBSEL_2 (2U)
#define MCAN_TSU_EXT_TIMEBASE_SRC_TBSEL_3 (3U)
#define MCAN_TSU_EXT_TIMEBASE_SRC_MAX     (MCAN_TSU_EXT_TIMEBASE_SRC_TBSEL_3)

/**
 * @brief MCAN TSU timebase option for each External Timebase
 */
#define MCAN_TSU_TBSEL_PTPC0 (0x20)
#define MCAN_TSU_TBSEL_MCAN0 (0x00)
#define MCAN_TSU_TBSEL_MCAN1 (0x01)
#define MCAN_TSU_TBSEL_MCAN2 (0x02)
#define MCAN_TSU_TBSEL_MCAN3 (0x03)


ATTR_PLACE_AT(".ahb_sram") extern uint32_t mcan_soc_msg_buf[MCAN_MSG_BUF_SIZE_IN_WORDS * MCAN_SOC_MAX_COUNT];

#ifdef __cpluspus
extern "C" {
#endif

/**
 * @brief Set External Timebase Source for MCAN TSU
 * @param [in] ptr MCAN base
 * @param [in] src External Timebase source
 */
static inline void mcan_set_tsu_ext_timebase_src(MCAN_Type *ptr, uint8_t src)
{
    if (src < HPM_MCAN_EXT_TBSEL_NUM) {
        ptr->GLB_CTL = (ptr->GLB_CTL & ~MCAN_GLB_CTL_TSU_TBIN_SEL_MASK) | MCAN_GLB_CTL_TSU_TBIN_SEL_SET(src);
    }
}

/**
 * @brief Set the Source for specified external timebase
 *
 * @param [in] ptr MCAN base
 * @param [in] ext_tbsel External TBSEL index
 * @param [in] tbsel_option Timebase source selection
 */
static inline void mcan_set_tsu_tbsel_option(MCAN_Type *ptr, uint8_t ext_tbsel, uint8_t tbsel_option)
{
    (void) ptr;
    if (ext_tbsel < HPM_MCAN_EXT_TBSEL_NUM) {
        uint32_t tbsel_shift = (ext_tbsel * HPM_MCAN_TBSEL_BITWIDTH) + HPM_MCAN_TBSEL0_SHIFT;
        uint32_t tbsel_mask = HPM_MCAN_TBSEL_MASK << tbsel_shift;
        HPM_MCAN_TBSEL = (HPM_MCAN_TBSEL & ~tbsel_mask) | (((uint32_t) tbsel_option << tbsel_shift) & tbsel_mask);
    }
}

/**
 * @brief Enable Standby Pin for MCAN
 * @param [in] ptr MCAN base
 */
static inline void mcan_enable_standby_pin(MCAN_Type *ptr)
{
    ptr->GLB_CTL |= MCAN_GLB_CTL_M_CAN_STBY_MASK;
}

/**
 * @brief Disable Standby pin for MCAN
 * @param [in] ptr MCAN base
 */
static inline void mcan_disable_standby_pin(MCAN_Type *ptr)
{
    ptr->GLB_CTL &= ~MCAN_GLB_CTL_M_CAN_STBY_MASK;
}

/**
 * @brief Get RAM base for MCAN
 * @param [in] ptr MCAN base
 * @return RAM base for MCAN
 */
static inline uint32_t mcan_get_ram_base(MCAN_Type *ptr)
{
    (void) ptr;
    return (uint32_t) &mcan_soc_msg_buf[0];
}

/**
 * @brief Get the MCAN RAM offset in the dedicated/shared RAM for
 * @param [in] ptr MCAN base
 * @return RAM offset for MCAN
 */
static inline uint32_t mcan_get_ram_offset(MCAN_Type *ptr)
{
    uint32_t index = ((uint32_t) ptr - HPM_MCAN0_BASE) / MCAN_IP_SLOT_SIZE;

    return (index * MCAN_MSG_BUF_SIZE_IN_WORDS * sizeof(uint32_t));
}

/**
 * @brief Get MCAN RAM size
 * @param [in] ptr MCAN base
 * @return RAM size in bytes
 */
static inline uint32_t mcan_get_ram_size(MCAN_Type *ptr)
{
    (void) ptr;
    return (MCAN_MSG_BUF_SIZE_IN_WORDS * sizeof(uint32_t));
}

#ifdef __cpluspus
}
#endif

#endif /* HPM_MCAN_SOC_H */
