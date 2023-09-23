/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_DAO_DRV_H
#define HPM_DAO_DRV_H

#include "hpm_common.h"
#include "hpm_dao_regs.h"
#include "hpm_i2s_common.h"

/**
 * @brief DAO driver APIs
 * @defgroup dao_interface DAO driver APIs
 * @ingroup io_interfaces
 * @{
 */

/**
 * @brief DAO channel selection
 */
#define DAO_CHANNEL_LEFT_ONLY DAO_CTRL_LEFT_EN_MASK
#define DAO_CHANNEL_RIGHT_ONLY DAO_CTRL_RIGHT_EN_MASK
#define DAO_CHANNEL_BOTH \
    (DAO_CTRL_RIGHT_EN_MASK | DAO_CTRL_LEFT_EN_MASK)

/**
 * @brief DAO default output
 */
#define DAO_DEFAULT_OUTPUT_ALL_LOW (0U)
#define DAO_DEFAULT_OUTPUT_ALL_HIGH (1U)
#define DAO_DEFAULT_OUTPUT_P_HIGH_N_LOW (2U)
#define DAO_DEFAULT_OUTPUT_DISABLED (3U)

/**
 * @brief DAO config
 */
typedef struct dao_config {
    bool enable_mono_output;
    uint8_t default_output_level;
    uint8_t channel_count;
} dao_config_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief config high pass filter
 *
 * @param [in] ptr DAO base address
 * @param [in] hpf_coef_ma high pass filter a coefficient's complement
 * @param [in] hpf_coef_b high pass filter b coefficient
 * @param [in] enable
 *  @arg true: enable
 *  @arg false: disable
 */
static inline void dao_config_hpf(DAO_Type *ptr,
                                     uint32_t hpf_coef_ma,
                                     uint32_t hpf_coef_b,
                                     bool enable)
{
    ptr->HPF_MA = DAO_HPF_MA_COEF_SET(hpf_coef_ma);
    ptr->HPF_B = DAO_HPF_B_COEF_SET(hpf_coef_b);
    ptr->CTRL = (ptr->CTRL & ~DAO_CTRL_HPF_EN_MASK)
        | (enable ? DAO_CTRL_HPF_EN_MASK : 0);
}

/**
 * @brief enable high pass filter
 *
 * @param [in] ptr DAO base address
 */
static inline void dao_enable_hpf(DAO_Type *ptr)
{
    ptr->CTRL |= DAO_CTRL_HPF_EN_MASK;
}

/**
 * @brief disable high pass filter
 *
 * @param [in] ptr DAO base address
 */
static inline void dao_disable_hpf(DAO_Type *ptr)
{
    ptr->CTRL &= ~DAO_CTRL_HPF_EN_MASK;
}

/**
 * @brief enable channel
 *
 * @param [in] ptr DAO base address
 * @param [in] ch channel number
 */
static inline void dao_enable_channel(DAO_Type *ptr, uint32_t ch)
{
    ptr->CTRL |= ch;
}

/**
 * @brief disable channel
 *
 * @param [in] ptr DAO base address
 * @param [in] ch channel number
 */
static inline void dao_disable_channel(DAO_Type *ptr, uint32_t ch)
{
    ptr->CTRL &= ~ch;
}

/**
 * @brief enable mono output
 *
 * @param [in] ptr DAO base address
 */
static inline void dao_enable_mono_output(DAO_Type *ptr)
{
    ptr->CTRL |= DAO_CTRL_MONO_MASK;
}

/**
 * @brief disable mono output
 *
 * @param [in] ptr DAO base address
 */
static inline void dao_disable_mono_output(DAO_Type *ptr)
{
    ptr->CTRL &= ~DAO_CTRL_MONO_MASK;
}

/**
 * @brief enable remap
 *
 * @param [in] ptr DAO base address
 */
static inline void dao_enable_remap(DAO_Type *ptr)
{
    ptr->CTRL |= DAO_CTRL_REMAP_MASK;
}

/**
 * @brief disable remap
 *
 * @param [in] ptr DAO base address
 */
static inline void dao_disable_remap(DAO_Type *ptr)
{
    ptr->CTRL &= ~DAO_CTRL_REMAP_MASK;
}

/**
 * @brief invert output
 *
 * @param [in] ptr DAO base address
 * @param [in] invert
 *  @arg true: invert output
 *  @arg false: not invert output
 */
static inline void dao_invert_output(DAO_Type *ptr, bool invert)
{
    ptr->CTRL = (ptr->CTRL & DAO_CTRL_INVERT_MASK)
                | DAO_CTRL_INVERT_SET(invert);
}

/**
 * @brief force pads output with certain level
 *
 * @param [in] ptr DAO base address
 * @param [in] output output level
 */
static inline void dao_force_output(DAO_Type *ptr, uint8_t output)
{
    ptr->CTRL = (ptr->CTRL & DAO_CTRL_FALSE_LEVEL_MASK)
                | DAO_CTRL_FALSE_LEVEL_SET(output);
}

/**
 * @brief enable false run
 * when false run mode is enabled, the module continues to consume data, no actual output on pads.
 * @param [in] ptr DAO base address
 * @param [in] enable
 *  @arg true: enable
 *  @arg false: disable
 */
static inline void dao_enable_false_run(DAO_Type *ptr, bool enable)
{
    ptr->CTRL = (ptr->CTRL & DAO_CTRL_FALSE_RUN_MASK)
                | DAO_CTRL_FALSE_RUN_SET(enable);
}

/**
 * @brief software reset
 *
 * @param [in] ptr DAO base address
 */
static inline void dao_software_reset(DAO_Type *ptr)
{
    ptr->CMD |= DAO_CMD_SFTRST_MASK;
    ptr->CMD &= ~DAO_CMD_SFTRST_MASK;
}

/**
 * @brief check whether DAO is running
 *
 * @param [in] ptr DAO base address
 * @retval true if dao is running
 */
static inline bool dao_is_running(DAO_Type *ptr)
{
    return ptr->CMD & DAO_CMD_RUN_MASK;
}

/**
 * @brief start
 *
 * @param [in] ptr DAO base address
 */
static inline void dao_start(DAO_Type *ptr)
{
    ptr->CMD |= DAO_CMD_RUN_MASK;
}

/**
 * @brief stop
 *
 * @param [in] ptr DAO base address
 */
static inline void dao_stop(DAO_Type *ptr)
{
    ptr->CMD &= ~DAO_CMD_RUN_MASK;
}

/**
 * @brief initlization
 *
 * @param [in] ptr DAO base address
 * @param [in] config dao_config_t
 * @retval hpm_stat_t status_invalid_argument or status_success
 */
hpm_stat_t dao_init(DAO_Type *ptr, dao_config_t *config);

/**
 * @brief get default config
 *
 * @param [in] ptr DAO base address
 * @param [out] config dao_config_t
 */
void dao_get_default_config(DAO_Type *ptr, dao_config_t *config);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* HPM_DAO_DRV_H */
