/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_SEI_DRV_H
#define HPM_SEI_DRV_H

#include "hpm_common.h"
#include "hpm_sei_regs.h"
#include "hpm_soc_feature.h"
#include "hpm_soc_ip_feature.h"

/**
 * @brief sei arming action
 */
typedef enum {
    sei_arming_direct_exec = 0,
    sei_arming_wait_trigger
} sei_arming_mode_t;

/**
 * @brief sei watchdog action
 */
typedef enum {
    sei_wdg_exec_next_instr = 0,
    sei_wdg_exec_exception_instr
} sei_wdg_action_t;

/**
 * @brief sei transfer mode
 */
typedef enum {
    sei_synchronous_master_mode = 0,
    sei_synchronous_slave_mode,
    sei_asynchronous_mode
} sei_tranceiver_mode_t;

/**
 * @brief sei asynchronous mode parity
 */
typedef enum {
    sei_asynchronous_parity_even = 0,
    sei_asynchronous_parity_odd
} sei_asynchronous_parity_t;

/**
 * @brief sei ilde state
 */
typedef enum {
    sei_idle_low_state = 0,
    sei_idle_high_state,
} sei_idle_state_t;

/**
 * @brief sei data mode
 */
typedef enum {
    sei_data_mode = 0,
    sei_check_mode,
    sei_crc_mode
} sei_data_mode_t;

/**
 * @brief sei data bit order
 */
typedef enum {
    sei_bit_lsb_first = 0,
    sei_bit_msb_first
} sei_data_bit_order_t;

/**
 * @brief sei data word order
 */
typedef enum {
    sei_word_nonreverse = 0,
    sei_word_reverse
} sei_data_word_order_t;

/**
 * @brief sei state transition condition
 */
typedef enum {
    sei_state_tran_condition_high_match = 0,
    sei_state_tran_condition_low_dismatch,
    sei_state_tran_condition_rise_entry,
    sei_state_tran_condition_fall_leave
} sei_state_tran_condition_t;

/**
 * @brief sei trig in type
 */
typedef enum {
    sei_trig_in0 = 0,
    sei_trig_in1,
    sei_trig_in_period,
    sei_trig_in_soft
} sei_trig_in_type_t;      /**< trig input type */

/**
 * @brief sei irq event
 */
typedef enum {
    sei_irq_stall_event = SEI_CTRL_IRQ_INT_FLAG_STALL_MASK,
    sei_irq_execpt_event = SEI_CTRL_IRQ_INT_FLAG_EXCEPT_MASK,
    sei_irq_wdog_event = SEI_CTRL_IRQ_INT_FLAG_WDOG_MASK,
    sei_irq_instr_ptr0_start_event = SEI_CTRL_IRQ_INT_FLAG_PTR0_ST_MASK,
    sei_irq_instr_ptr1_start_event = SEI_CTRL_IRQ_INT_FLAG_PTR1_ST_MASK,
    sei_irq_instr_value0_start_event = SEI_CTRL_IRQ_INT_FLAG_INSTR0_ST_MASK,
    sei_irq_instr_value1_start_event = SEI_CTRL_IRQ_INT_FLAG_INSTR1_ST_MASK,
    sei_irq_instr_ptr0_end_event = SEI_CTRL_IRQ_INT_FLAG_PTR0_END_MASK,
    sei_irq_instr_ptr1_end_event = SEI_CTRL_IRQ_INT_FLAG_PTR1_END_MASK,
    sei_irq_instr_value0_end_event = SEI_CTRL_IRQ_INT_FLAG_INSTR0_END_MASK,
    sei_irq_instr_value1_end_event = SEI_CTRL_IRQ_INT_FLAG_INSTR1_END_MASK,
    sei_irq_trx_err_event = SEI_CTRL_IRQ_INT_FLAG_TRX_ERR_MASK,
    sei_irq_timeout_event = SEI_CTRL_IRQ_INT_FLAG_TIMEOUT_MASK,
    sei_irq_latch0_event = SEI_CTRL_IRQ_INT_FLAG_LATCH0_MASK,
    sei_irq_latch1_event = SEI_CTRL_IRQ_INT_FLAG_LATCH1_MASK,
    sei_irq_latch2_event = SEI_CTRL_IRQ_INT_FLAG_LATCH2_MASK,
    sei_irq_latch3_event = SEI_CTRL_IRQ_INT_FLAG_LATCH3_MASK,
    sei_irq_sample_err_event = SEI_CTRL_IRQ_INT_FLAG_SMP_ERR_MASK,
    sei_irq_trig0_event = SEI_CTRL_IRQ_INT_FLAG_TRIGER0_MASK,
    sei_irq_trig1_event = SEI_CTRL_IRQ_INT_FLAG_TRIGER1_MASK,
    sei_irq_trig2_event = SEI_CTRL_IRQ_INT_FLAG_TRIGER2_MASK,
    sei_irq_trig3_event = SEI_CTRL_IRQ_INT_FLAG_TRIGER3_MASK,
    sei_irq_trig0_err_event = SEI_CTRL_IRQ_INT_FLAG_TRG_ERR0_MASK,
    sei_irq_trig1_err_event = SEI_CTRL_IRQ_INT_FLAG_TRG_ERR1_MASK,
    sei_irq_trig2_err_event = SEI_CTRL_IRQ_INT_FLAG_TRG_ERR2_MASK,
    sei_irq_trig3_err_event = SEI_CTRL_IRQ_INT_FLAG_TRG_ERR3_MASK,
} sei_irq_event_t;      /**< irq event type */

/**
 * @brief sei select command or data
 */
#define SEI_SELECT_CMD true      /**< select cmd */
#define SEI_SELECT_DATA false    /**< select data */

/**
 * @brief sei const data register index
 */
#define SEI_DATA_CONST_0      (30UL)
#define SEI_DATA_CONST_1      (31UL)

/**
 * @brief sei instruction operation command
 */
#define SEI_INSTR_OP_HALT 0u      /**< op halt */
#define SEI_INSTR_OP_JUMP 1u      /**< op jump */
#define SEI_INSTR_OP_SEND_WDG 2u  /**< op send with watchdog */
#define SEI_INSTR_OP_SEND 3u      /**< op send */
#define SEI_INSTR_OP_WAIT_WDG 4u  /**< op wait with watchdog */
#define SEI_INSTR_OP_WAIT 5u      /**< op wait */
#define SEI_INSTR_OP_RECV_WDG 6u  /**< op recv with watchdog */
#define SEI_INSTR_OP_RECV 7u      /**< op recv */

/**
 * @brief sei instruction synchronous master clock type
 */
#define SEI_INSTR_M_CK_LOW 0u            /**< clock low */
#define SEI_INSTR_M_CK_RISE_FALL 1u      /**< clock rise fall */
#define SEI_INSTR_M_CK_FALL_RISE 2u      /**< clock fall rise */
#define SEI_INSTR_M_CK_HIGH 3u           /**< clock high */

/**
 * @brief sei instruction synchronous slave clock type
 */
#define SEI_INSTR_S_CK_DEFAULT 0u                /**< default */
#define SEI_INSTR_S_CK_TRX_EXCH 1u               /**< rx tx exchange */
#define SEI_INSTR_S_CK_TIMEOUT_EN 2u             /**< enable timeout */
#define SEI_INSTR_S_CK_TRX_EXCH_TIMEOUT_EN 3u    /**< rx tx exchange and enable timeout */

/**
 * @brief sei instruction jump intructions index
 */
#define SEI_JUMP_INIT_INSTR_IDX 0x00u             /**< jump init instr index */
#define SEI_JUMP_WDG_INSTR_IDX 0x01u              /**< jump watchdog instr index */
#define SEI_JUMP_CMD_TABLE_INSTR_IDX0 0x10u       /**< jump command table instr ptr0 */
#define SEI_JUMP_CMD_TABLE_INSTR_IDX1 0x11u       /**< jump command table instr ptr1 */
#define SEI_JUMP_CMD_TABLE_INSTR_IDX2 0x12u       /**< jump command table instr ptr2 */
#define SEI_JUMP_CMD_TABLE_INSTR_IDX3 0x13u       /**< jump command table instr ptr3 */
#define SEI_JUMP_CMD_TABLE_INSTR_IDX4 0x14u       /**< jump command table instr ptr4 */
#define SEI_JUMP_CMD_TABLE_INSTR_IDX5 0x15u       /**< jump command table instr ptr5 */
#define SEI_JUMP_CMD_TABLE_INSTR_IDX6 0x16u       /**< jump command table instr ptr6 */
#define SEI_JUMP_CMD_TABLE_INSTR_IDX7 0x17u       /**< jump command table instr ptr7 */
#define SEI_JUMP_CMD_TABLE_INSTR_IDX8 0x18u       /**< jump command table instr ptr8 */
#define SEI_JUMP_CMD_TABLE_INSTR_IDX9 0x19u       /**< jump command table instr ptr9 */
#define SEI_JUMP_CMD_TABLE_INSTR_IDX10 0x1Au      /**< jump command table instr ptr10 */
#define SEI_JUMP_CMD_TABLE_INSTR_IDX11 0x1Bu      /**< jump command table instr ptr11 */
#define SEI_JUMP_CMD_TABLE_INSTR_IDX12 0x1Cu      /**< jump command table instr ptr12 */
#define SEI_JUMP_CMD_TABLE_INSTR_IDX13 0x1Du      /**< jump command table instr ptr13 */
#define SEI_JUMP_CMD_TABLE_INSTR_IDX14 0x1Eu      /**< jump command table instr ptr14 */
#define SEI_JUMP_CMD_TABLE_INSTR_IDX15 0x1Fu      /**< jump command table instr ptr15 */

/**
 * @brief sei engine config structure
 */
typedef struct {
    sei_arming_mode_t arming_mode;
    uint8_t data_cdm_idx;
    uint8_t data_base_idx;
    uint8_t init_instr_idx;
    bool wdg_enable;
    sei_wdg_action_t wdg_action;
    uint8_t wdg_instr_idx;
    uint16_t wdg_time;
} sei_engine_config_t;      /**< engine config struct */

/**
 * @brief sei tranceiver synchronous master mode config structure
 */
typedef struct {
    bool data_idle_high_z;
    sei_idle_state_t data_idle_state;
    bool clock_idle_high_z;
    sei_idle_state_t clock_idle_state;
    uint32_t baudrate;
} sei_tranceiver_synchronous_master_config_t;      /**< tranceiver synchronous master config struct */

/**
 * @brief sei tranceiver synchronous master mode config structure
 */
typedef struct {
    bool data_idle_high_z;
    sei_idle_state_t data_idle_state;
    bool clock_idle_high_z;
    sei_idle_state_t clock_idle_state;
    uint32_t max_baudrate;
    uint16_t ck0_timeout_us;
    uint16_t ck1_timeout_us;
} sei_tranceiver_synchronous_slave_config_t;      /**< tranceiver synchronous slave config struct */

/**
 * @brief sei tranceiver asynchronous mode config structure
 */
typedef struct {
    uint8_t wait_len;
    uint8_t data_len;
    bool parity_enable;
    sei_asynchronous_parity_t parity;
    bool data_idle_high_z;
    sei_idle_state_t data_idle_state;
    uint32_t baudrate;
} sei_tranceiver_asynchronous_config_t;      /**< tranceiver asynchronous config struct */

/**
 * @brief sei tranceiver config structure
 */
typedef struct {
    sei_tranceiver_mode_t mode;
    bool tri_sample;
    uint32_t src_clk_freq;
    sei_tranceiver_synchronous_master_config_t synchronous_master_config;
    sei_tranceiver_synchronous_slave_config_t synchronous_slave_config;
    sei_tranceiver_asynchronous_config_t asynchronous_config;
} sei_tranceiver_config_t;             /**< tranceiver config struct */

/**
 * @brief sei trigger input config structure
 */
typedef struct {
    bool trig_in0_enable;
    uint8_t trig_in0_select;
    bool trig_in1_enable;
    uint8_t trig_in1_select;
    bool trig_period_enable;
    sei_arming_mode_t trig_period_arming_mode;
    bool trig_period_sync_enable;
    uint8_t trig_period_sync_select;
    uint32_t trig_period_time;
#if defined(HPM_IP_FEATURE_SEI_TIMEOUT_REWIND_FEATURE) && HPM_IP_FEATURE_SEI_TIMEOUT_REWIND_FEATURE
    uint8_t rewind_enable;
    uint8_t rewind_select;
#endif
} sei_trigger_input_config_t;      /**< trigger input config struct */

/**
 * @brief sei trigger output config structure
 */
typedef struct {
    uint8_t src_latch_select;
    bool trig_out_enable;
    uint8_t trig_out_select;
} sei_trigger_output_config_t;      /**< trigger output config struct */

/**
 * @brief sei data format config structure
 */
typedef struct {
    sei_data_mode_t mode;
    bool signed_flag;
    sei_data_bit_order_t bit_order;
    sei_data_word_order_t word_order;
    uint8_t word_len;
    bool crc_invert;
    bool crc_shift_mode;
    uint8_t crc_len;
    uint8_t last_bit;
    uint8_t first_bit;
    uint8_t max_bit;
    uint8_t min_bit;
    uint32_t gold_value;
    uint32_t crc_init_value;
    uint32_t crc_poly;
} sei_data_format_config_t;      /**< cmd or data format config struct */

/**
 * @brief sei command table config structure
 */
typedef struct {
    uint32_t cmd_min_value;
    uint32_t cmd_max_value;
    uint32_t cmd_mask_value;
    uint8_t instr_idx[16];
} sei_command_table_config_t;      /**< cmd table config struct */

/**
 * @brief sei state transition config structure
 */
typedef struct {
    bool disable_instr_ptr_check;
    sei_state_tran_condition_t instr_ptr_cfg;
    uint8_t instr_ptr_value;
    bool disable_clk_check;
    sei_state_tran_condition_t clk_cfg;
    bool disable_txd_check;
    sei_state_tran_condition_t txd_cfg;
    bool disable_rxd_check;
    sei_state_tran_condition_t rxd_cfg;
    bool disable_timeout_check;
    sei_state_tran_condition_t timeout_cfg;
} sei_state_transition_config_t;      /**< state transition config struct */

/**
 * @brief sei state transition latch config structure
 */
typedef struct {
    bool enable;
    uint8_t output_select;
    uint16_t delay;
} sei_state_transition_latch_config_t;      /**< state transition latch config struct */

/**
 * @brief sei sample config structure
 */
typedef struct {
    uint8_t acc_data_idx;
    uint8_t spd_data_idx;
    uint8_t rev_data_idx;
    uint8_t pos_data_idx;
    bool acc_data_use_rx;      /**< true - use rx data, false - use override data */
    bool spd_data_use_rx;      /**< true - use rx data, false - use override data */
    bool rev_data_use_rx;      /**< true - use rx data, false - use override data */
    bool pos_data_use_rx;      /**< true - use rx data, false - use override data */
    uint8_t latch_select;
    bool sample_once;
    uint16_t sample_window;
    uint32_t data_register_select;
} sei_sample_config_t;      /**< sample config struct */

/**
 * @brief sei update config structure
 */
typedef struct {
    uint8_t acc_data_idx;
    uint8_t spd_data_idx;
    uint8_t rev_data_idx;
    uint8_t pos_data_idx;
    bool acc_data_use_rx;      /**< true - use rx data, false - use override data */
    bool spd_data_use_rx;      /**< true - use rx data, false - use override data */
    bool rev_data_use_rx;      /**< true - use rx data, false - use override data */
    bool pos_data_use_rx;      /**< true - use rx data, false - use override data */
    bool time_use_override;    /**< true - use override data, false - use timestamp data */
    bool update_on_err;
    uint8_t latch_select;
    uint32_t data_register_select;
} sei_update_config_t;      /**< update config struct */


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Set the SEI engine enable or disable
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] enable enable or disable
 *  @arg true enable
 *  @arg false disable
 */
static inline void sei_set_engine_enable(SEI_Type *ptr, uint8_t idx, bool enable)
{
    if (enable) {
        ptr->CTRL[idx].ENGINE.CTRL |= SEI_CTRL_ENGINE_CTRL_ENABLE_MASK;
    } else {
        ptr->CTRL[idx].ENGINE.CTRL &= ~SEI_CTRL_ENGINE_CTRL_ENABLE_MASK;
    }
}

/**
 * @brief Rewind the SEI engine
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 */
static inline void sei_set_engine_rewind(SEI_Type *ptr, uint8_t idx)
{
    ptr->CTRL[idx].ENGINE.CTRL |= SEI_CTRL_ENGINE_CTRL_REWIND_MASK;
}

/**
 * @brief Set the SEI trigger input trig in0 enable or disable
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] enable enable or disable
 *  @arg true enable
 *  @arg false disable
 */
static inline void sei_set_trig_input_in0_enable(SEI_Type *ptr, uint8_t idx, bool enable)
{
    if (enable) {
        ptr->CTRL[idx].TRG.IN_CFG |= SEI_CTRL_TRG_IN_CFG_IN0_EN_MASK;
    } else {
        ptr->CTRL[idx].TRG.IN_CFG &= ~SEI_CTRL_TRG_IN_CFG_IN0_EN_MASK;
    }
}

/**
 * @brief Set the SEI trigger input trig in1 enable or disable
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] enable enable or disable
 *  @arg true enable
 *  @arg false disable
 */
static inline void sei_set_trig_input_in1_enable(SEI_Type *ptr, uint8_t idx, bool enable)
{
    if (enable) {
        ptr->CTRL[idx].TRG.IN_CFG |= SEI_CTRL_TRG_IN_CFG_IN1_EN_MASK;
    } else {
        ptr->CTRL[idx].TRG.IN_CFG &= ~SEI_CTRL_TRG_IN_CFG_IN1_EN_MASK;
    }
}

/**
 * @brief Set the SEI trigger input period enable or disable
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] enable enable or disable
 *  @arg true enable
 *  @arg false disable
 */
static inline void sei_set_trig_input_period_enable(SEI_Type *ptr, uint8_t idx, bool enable)
{
    if (enable) {
        ptr->CTRL[idx].TRG.IN_CFG |= SEI_CTRL_TRG_IN_CFG_PRD_EN_MASK;
    } else {
        ptr->CTRL[idx].TRG.IN_CFG &= ~SEI_CTRL_TRG_IN_CFG_PRD_EN_MASK;
    }
}

/**
 * @brief Set the SEI trigger input soft enable or disable
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 *  @arg true enable
 *  @arg false disable
 */
static inline void sei_set_trig_input_soft_enable(SEI_Type *ptr, uint8_t idx)
{
    ptr->CTRL[idx].TRG.SW |= SEI_CTRL_TRG_SW_SOFT_MASK;
}

/**
 * @brief Set the SEI trigger input command value
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] type trigger input type @ref sei_trig_in_type_t
 * @param [in] data command data
 */
static inline void sei_set_trig_input_command_value(SEI_Type *ptr, uint8_t idx, sei_trig_in_type_t type, uint32_t data)
{
    ptr->CTRL[idx].TRG_TABLE.CMD[type] = data;
}

/**
 * @brief Get the SEI trigger input time
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] type trigger input type @ref sei_trig_in_type_t
 * @retval trigger input time
 */
static inline uint32_t sei_get_trig_input_time(SEI_Type *ptr, uint8_t idx, sei_trig_in_type_t type)
{
    return ptr->CTRL[idx].TRG_TABLE.TIME[type];
}

/**
 * @brief Get the SEI latch time
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] latch_idx
 *  @arg SEI_LATCH_0
 *  @arg SEI_LATCH_1
 *  @arg SEI_LATCH_2
 *  @arg SEI_LATCH_3
 * @retval latch time
 */
static inline uint32_t sei_get_latch_time(SEI_Type *ptr, uint8_t idx, uint8_t latch_idx)
{
    return ptr->CTRL[idx].LATCH[latch_idx].TIME;
}

/**
 * @brief Set the SEI tranceiver rx point
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] point rx point value
 */
static inline void sei_set_xcvr_rx_point(SEI_Type *ptr, uint8_t idx, uint16_t point)
{
    uint32_t tmp;

    assert(point > 0);
    tmp = ptr->CTRL[idx].XCVR.DATA_CFG;
    tmp &= ~SEI_CTRL_XCVR_DATA_CFG_RXD_POINT_MASK;
    tmp |= SEI_CTRL_XCVR_DATA_CFG_RXD_POINT_SET(point);
    ptr->CTRL[idx].XCVR.DATA_CFG = tmp;
}

/**
 * @brief Set the SEI tranceiver tx point
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] point tx point value
 */
static inline void sei_set_xcvr_tx_point(SEI_Type *ptr, uint8_t idx, uint16_t point)
{
    uint32_t tmp;

    assert(point > 0);
    tmp = ptr->CTRL[idx].XCVR.DATA_CFG;
    tmp &= ~SEI_CTRL_XCVR_DATA_CFG_TXD_POINT_MASK;
    tmp |= SEI_CTRL_XCVR_DATA_CFG_TXD_POINT_SET(point);
    ptr->CTRL[idx].XCVR.DATA_CFG = tmp;
}

/**
 * @brief Set the SEI tranceiver ck0 point
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] point ck0 point value
 */
static inline void sei_set_xcvr_ck0_point(SEI_Type *ptr, uint8_t idx, uint16_t point)
{
    uint32_t tmp;

    assert(point > 0);
    tmp = ptr->CTRL[idx].XCVR.CLK_CFG;
    tmp &= ~SEI_CTRL_XCVR_CLK_CFG_CK0_POINT_MASK;
    tmp |= SEI_CTRL_XCVR_CLK_CFG_CK0_POINT_SET(point);
    ptr->CTRL[idx].XCVR.CLK_CFG = tmp;
}

/**
 * @brief Set the SEI tranceiver ck1 point
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] point ck1 point value
 */
static inline void sei_set_xcvr_ck1_point(SEI_Type *ptr, uint8_t idx, uint16_t point)
{
    uint32_t tmp;

    assert(point > 0);
    tmp = ptr->CTRL[idx].XCVR.CLK_CFG;
    tmp &= ~SEI_CTRL_XCVR_CLK_CFG_CK1_POINT_MASK;
    tmp |= SEI_CTRL_XCVR_CLK_CFG_CK1_POINT_SET(point);
    ptr->CTRL[idx].XCVR.CLK_CFG = tmp;
}

/**
 * @brief Get the SEI tranceiver ck0 point
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @retval ck0 point value
 */
static inline uint16_t sei_get_xcvr_ck0_point(SEI_Type *ptr, uint8_t idx)
{
    return SEI_CTRL_XCVR_CLK_CFG_CK0_POINT_GET(ptr->CTRL[idx].XCVR.CLK_CFG);
}

/**
 * @brief Get the SEI tranceiver ck1 point
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @retval ck1 point value
 */
static inline uint16_t sei_get_xcvr_ck1_point(SEI_Type *ptr, uint8_t idx)
{
    return SEI_CTRL_XCVR_CLK_CFG_CK1_POINT_GET(ptr->CTRL[idx].XCVR.CLK_CFG);
}

/**
 * @brief Set the SEI command value
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] cmd command value
 */
static inline void sei_set_command_value(SEI_Type *ptr, uint8_t idx, uint32_t cmd)
{
    ptr->CTRL[idx].CMD.CMD = cmd;
}

/**
 * @brief Get the SEI command value
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @retval command value
 */
static inline uint32_t sei_get_command_value(SEI_Type *ptr, uint8_t idx)
{
    return ptr->CTRL[idx].CMD.CMD;
}

/**
 * @brief Rewind the SEI command
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 */
static inline void sei_set_command_rewind(SEI_Type *ptr, uint8_t idx)
{
    ptr->CTRL[idx].CMD.MODE |= SEI_CTRL_CMD_MODE_REWIND_MASK;
}

/**
 * @brief Set the SEI data value
 * @param [in] ptr SEI base address
 * @param [in] idx SEI data index, such as SEI_DAT_2, SEI_DAT_3, etc.
 * @param [in] data data value
 */
static inline void sei_set_data_value(SEI_Type *ptr, uint8_t idx, uint32_t data)
{
    ptr->DAT[idx].DATA = data;
}

/**
 * @brief Get the SEI data value
 * @param [in] ptr SEI base address
 * @param [in] idx SEI data index, such as SEI_DAT_2, SEI_DAT_3, etc.
 * @retval data value
 */
static inline uint32_t sei_get_data_value(SEI_Type *ptr, uint8_t idx)
{
    return ptr->DAT[idx].DATA;
}

/**
 * @brief Rewind the SEI data
 * @param [in] ptr SEI base address
 * @param [in] idx SEI data index, such as SEI_DAT_2, SEI_DAT_3, etc.
 */
static inline void sei_set_data_rewind(SEI_Type *ptr, uint8_t idx)
{
    ptr->DAT[idx].MODE |= SEI_DAT_MODE_REWIND_MASK;
}

/**
 * @brief Set the SEI sample position (singleturn) override value
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] data position (singleturn) override value
 */
static inline void sei_set_sample_pos_override_value(SEI_Type *ptr, uint8_t idx, uint32_t data)
{
    ptr->CTRL[idx].POS.SMP_POS = data;
}

/**
 * @brief Set the SEI sample revolution (multiturn) override value
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] data revolution (multiturn) override value
 */
static inline void sei_set_sample_rev_override_value(SEI_Type *ptr, uint8_t idx, uint32_t data)
{
    ptr->CTRL[idx].POS.SMP_REV = data;
}

/**
 * @brief Set the SEI sample speed override value
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] data speed override value
 */
static inline void sei_set_sample_spd_override_value(SEI_Type *ptr, uint8_t idx, uint32_t data)
{
    ptr->CTRL[idx].POS.SMP_SPD = data;
}

/**
 * @brief Set the SEI sample acceleration override value
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] data acceleration override value
 */
static inline void sei_set_sample_acc_override_value(SEI_Type *ptr, uint8_t idx, uint32_t data)
{
    ptr->CTRL[idx].POS.SMP_ACC = data;
}

/**
 * @brief Set the SEI update position (singleturn) override value
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] data position (singleturn) override value
 */
static inline void sei_set_update_pos_override_value(SEI_Type *ptr, uint8_t idx, uint32_t data)
{
    ptr->CTRL[idx].POS.UPD_POS = data;
}

/**
 * @brief Set the SEI update revolution (multiturn) override value
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] data revolution (multiturn) override value
 */
static inline void sei_set_update_rev_override_value(SEI_Type *ptr, uint8_t idx, uint32_t data)
{
    ptr->CTRL[idx].POS.UPD_REV = data;
}

/**
 * @brief Set the SEI update speed override value
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] data speed override value
 */
static inline void sei_set_update_spd_override_value(SEI_Type *ptr, uint8_t idx, uint32_t data)
{
    ptr->CTRL[idx].POS.UPD_SPD = data;
}

/**
 * @brief Set the SEI update acceleration override value
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] data acceleration override value
 */
static inline void sei_set_update_acc_override_value(SEI_Type *ptr, uint8_t idx, uint32_t data)
{
    ptr->CTRL[idx].POS.UPD_ACC = data;
}

/**
 * @brief Set the SEI update time override value
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] data time override value
 */
static inline void sei_set_update_time_override_value(SEI_Type *ptr, uint8_t idx, uint32_t data)
{
    ptr->CTRL[idx].POS.UPD_TIME = data;
}

/**
 * @brief Set the SEI irq match pointer0
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] instr_idx match instr0 index
 */
static inline void sei_set_irq_match_instr0_ptr(SEI_Type *ptr, uint8_t idx, uint8_t instr_idx)
{
    ptr->CTRL[idx].IRQ.POINTER0 = SEI_CTRL_IRQ_POINTER0_POINTER_SET(instr_idx);
}

/**
 * @brief Set the SEI irq match pointer1
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] instr_idx match instr1 index
 */
static inline void sei_set_irq_match_instr1_ptr(SEI_Type *ptr, uint8_t idx, uint8_t instr_idx)
{
    ptr->CTRL[idx].IRQ.POINTER1 = SEI_CTRL_IRQ_POINTER1_POINTER_SET(instr_idx);
}

/**
 * @brief Set the SEI irq match instr0
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] instr_value match instr0 value
 */
static inline void sei_set_irq_match_instr0_value(SEI_Type *ptr, uint8_t idx, uint32_t instr_value)
{
    ptr->CTRL[idx].IRQ.INSTR0 = SEI_CTRL_IRQ_INSTR0_INSTR_SET(instr_value);
}

/**
 * @brief Set the SEI irq match instr1
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] instr_value match instr1 value
 */
static inline void sei_set_irq_match_instr1_value(SEI_Type *ptr, uint8_t idx, uint32_t instr_value)
{
    ptr->CTRL[idx].IRQ.INSTR1 = SEI_CTRL_IRQ_INSTR1_INSTR_SET(instr_value);
}

/**
 * @brief Set the SEI irq enable or disable
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] irq_mask irq mask, @ref sei_irq_event_t
 * @param [in] enable enable or disable
 *  @arg true enable
 *  @arg false disable
 */
static inline void sei_set_irq_enable(SEI_Type *ptr, uint8_t idx, uint32_t irq_mask, bool enable)
{
    if (enable) {
        ptr->CTRL[idx].IRQ.INT_EN |= irq_mask;
    } else {
        ptr->CTRL[idx].IRQ.INT_EN &= ~irq_mask;
    }
}

/**
 * @brief Get the SEI irq status
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] irq_mask irq mask, @ref sei_irq_event_t
 *
 * @retval true-has irq req, false-no irq req.
 */
static inline bool sei_get_irq_status(SEI_Type *ptr, uint8_t idx, uint32_t irq_mask)
{
    return ((ptr->CTRL[idx].IRQ.INT_FLAG & irq_mask) == irq_mask) ? true : false;
}

/**
 * @brief Clear the SEI irq flag
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] irq_mask irq mask, @ref sei_irq_event_t
 */
static inline void sei_clear_irq_flag(SEI_Type *ptr, uint8_t idx, uint32_t irq_mask)
{
    ptr->CTRL[idx].IRQ.INT_FLAG = irq_mask;
}

/**
 * @brief Init SEI tranceiver configuration
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] config tranceiver configuration @ref sei_tranceiver_config_t
 * @retval API execution status
 */
hpm_stat_t sei_tranceiver_config_init(SEI_Type *ptr, uint8_t idx, sei_tranceiver_config_t *config);

/**
 * @brief Init SEI command or data format configuration
 * @param [in] ptr SEI base address
 * @param [in] cmd_data_select
 *   @arg @ref SEI_SELECT_CMD select command
 *   @arg @ref SEI_SELECT_DATA select data
 * @param [in] idx SEI ctrl index or data index, decided by cmd_data_select, such as SEI_CTRL_0, SEI_CTRL_1, SEI_DAT_2, SEI_DAT_3, etc.
 * @param [in] config command or data format configuration @ref sei_data_format_config_t
 * @retval API execution status
 */
hpm_stat_t sei_cmd_data_format_config_init(SEI_Type *ptr, bool cmd_data_select, uint8_t idx, sei_data_format_config_t *config);

/**
 * @brief Init SEI command table configuration
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] table_idx command table index, 0 - 7
 * @param [in] config command table configuration @ref sei_command_table_config_t
 * @retval API execution status
 */
hpm_stat_t sei_cmd_table_config_init(SEI_Type *ptr, uint8_t idx, uint8_t table_idx, sei_command_table_config_t *config);

/**
 * @brief Init SEI state transition configuration
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] latch_idx latch index
 *  @arg SEI_LATCH_0
 *  @arg SEI_LATCH_1
 *  @arg SEI_LATCH_2
 *  @arg SEI_LATCH_3
 * @param [in] state transition state
 *  @arg SEI_CTRL_LATCH_TRAN_0_1
 *  @arg SEI_CTRL_LATCH_TRAN_1_2
 *  @arg SEI_CTRL_LATCH_TRAN_2_3
 *  @arg SEI_CTRL_LATCH_TRAN_3_0
 * @param [in] config state transition configuration @ref sei_state_transition_config_t
 * @retval API execution status
 */
hpm_stat_t sei_state_transition_config_init(SEI_Type *ptr, uint8_t idx, uint8_t latch_idx, uint8_t state, sei_state_transition_config_t *config);

/**
 * @brief Init SEI state transition latch configuration
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] latch_idx latch index
 *  @arg SEI_LATCH_0
 *  @arg SEI_LATCH_1
 *  @arg SEI_LATCH_2
 *  @arg SEI_LATCH_3
 * @param [in] config state transition latch configuration @ref sei_state_transition_latch_config_t
 * @retval API execution status
 */
hpm_stat_t sei_state_transition_latch_config_init(SEI_Type *ptr, uint8_t idx, uint8_t latch_idx, sei_state_transition_latch_config_t *config);

/**
 * @brief Init SEI sample configuration
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] config sample configuration @ref sei_sample_config_t
 * @retval API execution status
 */
hpm_stat_t sei_sample_config_init(SEI_Type *ptr, uint8_t idx, sei_sample_config_t *config);

/**
 * @brief Init SEI update configuration
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] config update configuration @ref sei_update_config_t
 * @retval API execution status
 */
hpm_stat_t sei_update_config_init(SEI_Type *ptr, uint8_t idx, sei_update_config_t *config);

/**
 * @brief Init SEI trigger input configuration
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] config trigger input configuration @ref sei_trigger_input_config_t
 * @retval API execution status
 */
hpm_stat_t sei_trigger_input_config_init(SEI_Type *ptr, uint8_t idx, sei_trigger_input_config_t *config);

/**
 * @brief Init SEI trigger output configuration
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] config trigger output configuration @ref sei_trigger_output_config_t
 * @retval API execution status
 */
hpm_stat_t sei_trigger_output_config_init(SEI_Type *ptr, uint8_t idx, sei_trigger_output_config_t *config);

/**
 * @brief Init SEI engine configuration
 * @param [in] ptr SEI base address
 * @param [in] idx SEI ctrl index, such as SEI_CTRL_0, SEI_CTRL_1, etc.
 * @param [in] config engine configuration @ref sei_engine_config_t
 * @retval API execution status
 */
hpm_stat_t sei_engine_config_init(SEI_Type *ptr, uint8_t idx, sei_engine_config_t *config);

/**
 * @brief Set SEI Intsructions
 * @param [in] ptr SEI base address
 * @param [in] idx SEI instruction index.
 * @param [in] op SEI instruction operation
 *  @arg @ref SEI_INSTR_OP_HALT
 *  @arg @ref SEI_INSTR_OP_JUMP
 *  @arg @ref SEI_INSTR_OP_SEND_WDG
 *  @arg @ref SEI_INSTR_OP_SEND
 *  @arg @ref SEI_INSTR_OP_WAIT_WDG
 *  @arg @ref SEI_INSTR_OP_WAIT
 *  @arg @ref SEI_INSTR_OP_RECV_WDG
 *  @arg @ref SEI_INSTR_OP_RECV
 * @param [in] ck SEI instruction clock
 *   [1] synchronous master clock type
 *       @arg @ref SEI_INSTR_M_CK_LOW
 *       @arg @ref SEI_INSTR_M_CK_RISE_FALL
 *       @arg @ref SEI_INSTR_M_CK_FALL_RISE
 *       @arg @ref SEI_INSTR_M_CK_HIGH
 *   [2] synchronous slave clock type
 *       @arg @ref SEI_INSTR_S_CK_DEFAULT
 *       @arg @ref SEI_INSTR_S_CK_TRX_EXCH
 *       @arg @ref SEI_INSTR_S_CK_TIMEOUT_EN
 *       @arg @ref SEI_INSTR_S_CK_TRX_EXCH_TIMEOUT_EN
 * @param [in] crc SEI instruction crc register, such as SEI_DAT_0, SEI_DAT_1, etc.
 * @param [in] data SEI instruction data register, such as SEI_DAT_0, SEI_DAT_1, etc.
 * @param [in] opr SEI instruction operand.
 *   [1] When OP is SEI_INSTR_OP_HALT, opr is the halt time in baudrate, 0 represents infinite time.
 *   [2] When OP is SEI_INSTR_OP_JUMP, opr is command table pointer, init pointer or wdg pointer.
 *       @arg @ref SEI_JUMP_INIT_INSTR_IDX
 *       @arg @ref SEI_JUMP_WDG_INSTR_IDX
 *       @arg @ref SEI_JUMP_CMD_TABLE_INSTR_IDX0
 *       @arg @ref SEI_JUMP_CMD_TABLE_INSTR_IDX1
 *       @arg @ref SEI_JUMP_CMD_TABLE_INSTR_IDX2
 *       @arg @ref SEI_JUMP_CMD_TABLE_INSTR_IDX3
 *       @arg @ref SEI_JUMP_CMD_TABLE_INSTR_IDX4
 *       @arg @ref SEI_JUMP_CMD_TABLE_INSTR_IDX5
 *       @arg @ref SEI_JUMP_CMD_TABLE_INSTR_IDX6
 *       @arg @ref SEI_JUMP_CMD_TABLE_INSTR_IDX7
 *       @arg @ref SEI_JUMP_CMD_TABLE_INSTR_IDX8
 *       @arg @ref SEI_JUMP_CMD_TABLE_INSTR_IDX9
 *       @arg @ref SEI_JUMP_CMD_TABLE_INSTR_IDX10
 *       @arg @ref SEI_JUMP_CMD_TABLE_INSTR_IDX11
 *       @arg @ref SEI_JUMP_CMD_TABLE_INSTR_IDX12
 *       @arg @ref SEI_JUMP_CMD_TABLE_INSTR_IDX13
 *       @arg @ref SEI_JUMP_CMD_TABLE_INSTR_IDX14
 *       @arg @ref SEI_JUMP_CMD_TABLE_INSTR_IDX15
 *   [3] Other OP, this area is the data length.
 */
void sei_set_instr(SEI_Type *ptr, uint8_t idx, uint8_t op, uint8_t ck, uint8_t crc, uint8_t data, uint8_t opr);


#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif
