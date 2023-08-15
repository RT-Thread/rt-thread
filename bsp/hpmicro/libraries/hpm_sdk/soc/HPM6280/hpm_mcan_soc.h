/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_MCAN_SOC_H
#define HPM_MCAN_SOC_H

#include <stdint.h>
#include "hpm_mcan_regs.h"

/**
 * @brief TSU External Timebase Sources
 */
#define MCAN_TSU_EXT_TIMEBASE_SRC_MIN   (0U)
#define MCAN_TSU_EXT_TIMEBASE_SRC_MCAN0 (MCAN_TSU_EXT_TIMEBASE_SRC_MIN)
#define MCAN_TSU_EXT_TIMEBASE_SRC_MCAN1 (1U)
#define MCAN_TSU_EXT_TIMEBASE_SRC_MCAN2 (2U)
#define MCAN_TSU_EXT_TIMEBASE_SRC_MCAN3 (3U)
#define MCAN_TSU_EXT_TIMEBASE_SRC_PTP   (4U)
#define MCAN_TSU_EXT_TIMEBASE_SRC_MAX   (MCAN_TSU_EXT_TIMEBASE_SRC_PTP)

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
    ptr->GLB_CTL = (ptr->GLB_CTL & ~MCAN_GLB_CTL_TSU_TBIN_SEL_MASK) | MCAN_GLB_CTL_TSU_TBIN_SEL_SET(src);
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
    return (uint32_t) &ptr->MESSAGE_BUFF[0];
}

/**
 * @brief Get the MCAN RAM offset in the dedicated/shared RAM for
 * @param [in] ptr MCAN base
 * @return RAM offset for MCAN
 */
static inline uint32_t mcan_get_ram_offset(MCAN_Type *ptr)
{
    return 0U;
}

/**
 * @brief Get MCAN RAM size
 * @param [in] ptr MCAN base
 * @return RAM size in bytes
 */
static inline uint32_t mcan_get_ram_size(MCAN_Type *ptr)
{
    return sizeof(ptr->MESSAGE_BUFF);
}

#ifdef __cpluspus
}
#endif

#endif /* HPM_MCAN_SOC_H */
