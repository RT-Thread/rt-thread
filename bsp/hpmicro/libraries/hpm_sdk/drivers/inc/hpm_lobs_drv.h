/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_LOBS_DRV_H
#define HPM_LOBS_DRV_H

#include "hpm_common.h"
#include "hpm_soc_ip_feature.h"
#include "hpm_lobs_regs.h"

/**
 * @brief LOBS driver APIs
 * @defgroup lobs_interface LOBS driver APIs
 * @ingroup lobs_interfaces
 * @{
 */

#define LOBS_UNLOCK_KEY 0xc5acce55u

#define LOBS_PIN_DO(x) (x * 3)
#define LOBS_PIN_OE(x) (x * 3 + 1)
#define LOBS_PIN_DI(x) (x * 3 + 2)

/**
 * @brief group mode selection
 *
 */
typedef enum {
    lobs_one_group_128_bits = 0,
    lobs_two_group_8_bits
} lobs_group_mode_t;    /**< lobs_group_mode_t */

/**
 * @brief sample rate selection
 *
 */
typedef enum {
    lobs_sample_1_per_5 = 4,
    lobs_sample_1_per_6 = 5,
    lobs_sample_1_per_7 = 6,
} lobs_sample_rate_t;    /**< lobs_sample_rate_t */

/**
 * @brief burst selection
 *
 */
typedef enum {
    lobs_burst_4 = 3,
    lobs_burst_8 = 5,
    lobs_burst_16 = 7,
} lobs_burst_t;    /**< lobs_burst_t */

/**
 * @brief two group selection
 *
 */
typedef enum {
    lobs_two_group_1 = 0,
    lobs_two_group_2,
} lobs_two_group_sel_t;    /**< lobs_two_group_sel_t */

/**
 * @brief state selection
 *
 */
typedef enum {
    lobs_state_0 = 0,
    lobs_state_1,
    lobs_state_2,
    lobs_state_3,
    lobs_state_4,
} lobs_state_sel_t;    /**< lobs_state_sel_t */

/**
 * @brief compare mode
 *
 */
typedef enum {
    lobs_sig_cmp_mode = 0,
    lobs_cnt_cmp_mode,
} lobs_cmp_mode_t;    /**< lobs_cmp_mode_t */

/**
 * @brief compare condition
 *
 */
typedef enum {
    lobs_cnt_matched = 0,
    lobs_sig_equal_golden,
    lobs_sig_greater_golden,
    lobs_sig_greater_equal_golden,
    lobs_sig_not_equal_golden,
    lobs_sig_less_golden,
    lobs_sig_less_equal_golden,
} lobs_state_chg_condition_t;    /**< lobs_state_chg_condition_t */

/**
 * @brief next state
 *
 */
typedef enum {
    lobs_next_state_finish = 0x00,
    lobs_next_state_0 = 0x01,
    lobs_next_state_1 = 0x02,
    lobs_next_state_2 = 0x04,
    lobs_next_state_3 = 0x08,
    lobs_next_state_4 = 0x10,
} lobs_next_state_t;    /**< lobs_next_state_t */

/**
 * @brief ctrl config structure
 *
 */
typedef struct {
    lobs_group_mode_t group_mode;
    lobs_sample_rate_t sample_rate;
    uint32_t start_addr;
    uint32_t end_addr;
} lobs_ctrl_config_t;    /**< lobs_ctrl_config_t */

/**
 * @brief two group mode config structure
 *
 */
typedef struct {
    bool group_enable;
    uint8_t sig_group_num;
    uint8_t sample_sig_bit[4];
    bool sample_sig_en[4];
} lobs_two_group_mode_config_t;    /**< lobs_two_group_mode_config_t */

/**
 * @brief two group mode config structure
 *
 */
typedef struct {
    uint8_t sig_group_num;
    lobs_cmp_mode_t cmp_mode;
    lobs_state_chg_condition_t state_chg_condition;
    lobs_next_state_t next_state;
    uint32_t cmp_counter;
    uint8_t cmp_sig_bit[4];
    bool cmp_sig_en[4];
    bool cmp_golden_value[4];
} lobs_state_config_t;    /**< lobs_state_config_t */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief set lobs unlock
 *
 * @param[in] lobs LOBS base address
 */
static inline void lobs_unlock(LOBS_Type *lobs)
{
    lobs->LAR = LOBS_UNLOCK_KEY;
}

/**
 * @brief set lobs lock
 *
 * @param[in] lobs LOBS base address
 */
static inline void lobs_lock(LOBS_Type *lobs)
{
    lobs->LAR = 0;
}

/**
 * @brief set lobs enable or disable
 *
 * @param[in] lobs LOBS base address
 * @param[in] enable true - enable; false - disable.
 */
static inline void lobs_set_enable(LOBS_Type *lobs, bool enable)
{
    lobs->CTRL = (lobs->CTRL & ~LOBS_CTRL_RUN_MASK) | LOBS_CTRL_RUN_SET(enable);
}

/**
 * @brief set lobs pre-trig enable or disable
 *
 * @param[in] lobs LOBS base address
 * @param[in] enable true - enable; false - disable.
 */
static inline void lobs_set_pre_trig_enable(LOBS_Type *lobs, bool enable)
{
    lobs->PTACTION = (lobs->PTACTION & ~LOBS_PTACTION_TRACE_MASK) | LOBS_PTACTION_TRACE_SET(enable);
}

/**
 * @brief set lobs state enable or disable
 *
 * @param[in] lobs LOBS base address
 * @param[in] state one of state, @ref lobs_state_sel_t
 * @param[in] enable true - enable; false - disable.
 */
static inline void lobs_set_state_enable(LOBS_Type *lobs, lobs_state_sel_t state, bool enable)
{
    lobs->STATE[state].ACTION = (lobs->STATE[state].ACTION & ~LOBS_STATE_ACTION_TRACE_MASK) | LOBS_STATE_ACTION_TRACE_SET(enable);
}

/**
 * @brief get lobs final address
 *
 * @param[in] lobs LOBS base address
 *
 * @return uint32_t trace final address
 */
static inline uint32_t lobs_get_final_address(LOBS_Type *lobs)
{
    return lobs->FINALADDR;
}

/**
 * @brief check lobs trace finish
 *
 * @param[in] lobs LOBS base address
 *
 * @return bool true - trace finish; false - trace not finish
 */
static inline bool lobs_is_trace_finish(LOBS_Type *lobs)
{
    return (LOBS_CTSR_FINALSTATE_GET(lobs->CTSR) != 0) ? true : false;
}

/**
 * @brief clear lobs fifo overflow flag
 *
 * @param[in] lobs LOBS base address
 *
 */
static inline void lobs_clear_fifo_overflow_flag(LOBS_Type *lobs)
{
    lobs->STREAMCTRL |= LOBS_STREAMCTRL_FULL_CLEAR_MASK;
}

/**
 * @brief lobs deinit
 *
 * @param[in] lobs LOBS base address
 */
void lobs_deinit(LOBS_Type *lobs);

/**
 * @brief lobs control config
 *
 * @param[in] lobs LOBS base address
 * @param[in] config control config structure pointer
 */
void lobs_ctrl_config(LOBS_Type *lobs, lobs_ctrl_config_t *config);

/**
 * @brief lobs two group mode config
 *
 * @param[in] lobs LOBS base address
 * @param[in] group one of the two group, @ref lobs_two_group_sel_t
 * @param[in] config two group mode config structure pointer
 */
void lobs_two_group_mode_config(LOBS_Type *lobs, lobs_two_group_sel_t group, lobs_two_group_mode_config_t *config);

/**
 * @brief lobs state config
 *
 * @param[in] lobs LOBS base address
 * @param[in] state one of state, @ref lobs_state_sel_t
 * @param[in] config state config structure pointer
 */
void lobs_state_config(LOBS_Type *lobs, lobs_state_sel_t state, lobs_state_config_t *config);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_LOBS_DRV_H */
