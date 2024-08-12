/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_sei_drv.h"

hpm_stat_t sei_tranceiver_config_init(SEI_Type *ptr, uint8_t idx, sei_tranceiver_config_t *config)
{
    uint32_t tmp;
    uint32_t baudrate;
    uint32_t baud_div;
    uint32_t sync_point;
    uint8_t data_len;
    uint32_t ck0_point;
    uint32_t ck1_point;
    uint32_t txd_point;
    uint32_t rxd_point;

    tmp = SEI_CTRL_XCVR_CTRL_TRISMP_SET(config->tri_sample)
        | SEI_CTRL_XCVR_CTRL_MODE_SET(config->mode);
    ptr->CTRL[idx].XCVR.CTRL = tmp;

    switch (config->mode) {
    case sei_synchronous_master_mode:
        tmp = SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEZ_SET(config->synchronous_master_config.data_idle_high_z)
            | SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEV_SET(config->synchronous_master_config.data_idle_state)
            | SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEZ_SET(config->synchronous_master_config.clock_idle_high_z)
            | SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEV_SET(config->synchronous_master_config.clock_idle_state);
        ptr->CTRL[idx].XCVR.TYPE_CFG = tmp;

        baud_div = (config->src_clk_freq + (config->synchronous_master_config.baudrate >> 1u)) / config->synchronous_master_config.baudrate;
        sync_point = baud_div >> 1u;
        tmp = SEI_CTRL_XCVR_BAUD_CFG_SYNC_POINT_SET(sync_point)
            | SEI_CTRL_XCVR_BAUD_CFG_BAUD_DIV_SET(baud_div - 1u);
        ptr->CTRL[idx].XCVR.BAUD_CFG = tmp;

        ck0_point = baud_div >> 2u;
        ck1_point = ck0_point * 3u;
        tmp = SEI_CTRL_XCVR_CLK_CFG_CK0_POINT_SET(ck0_point)
            | SEI_CTRL_XCVR_CLK_CFG_CK1_POINT_SET(ck1_point);
        ptr->CTRL[idx].XCVR.CLK_CFG = tmp;
        break;

    case sei_synchronous_slave_mode:
        tmp = SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEZ_SET(config->synchronous_slave_config.data_idle_high_z)
            | SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEV_SET(config->synchronous_slave_config.data_idle_state)
            | SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEZ_SET(config->synchronous_slave_config.clock_idle_high_z)
            | SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEV_SET(config->synchronous_slave_config.clock_idle_state);
        ptr->CTRL[idx].XCVR.TYPE_CFG = tmp;

        baud_div = (config->src_clk_freq + (config->synchronous_slave_config.max_baudrate >> 1u)) / config->synchronous_slave_config.max_baudrate;
        sync_point = (baud_div * 3u) >> 3u;
        tmp = SEI_CTRL_XCVR_BAUD_CFG_SYNC_POINT_SET(sync_point)
            | SEI_CTRL_XCVR_BAUD_CFG_BAUD_DIV_SET(baud_div - 1u);
        ptr->CTRL[idx].XCVR.BAUD_CFG = tmp;

        ck0_point = config->synchronous_slave_config.ck0_timeout_us * (config->src_clk_freq / 1000000u);
        if (ck0_point > 0x7FFFu) {
            ck0_point = 0x7FFFu;
        }
        ck1_point = config->synchronous_slave_config.ck1_timeout_us * (config->src_clk_freq / 1000000u);
        if (ck1_point > 0x7FFFu) {
            ck1_point = 0x7FFFu;
        }
        ck1_point += 0x8000u;
        tmp = SEI_CTRL_XCVR_CLK_CFG_CK0_POINT_SET(ck0_point)
            | SEI_CTRL_XCVR_CLK_CFG_CK1_POINT_SET(ck1_point);
        ptr->CTRL[idx].XCVR.CLK_CFG = tmp;
    break;

    case sei_asynchronous_mode:
    default:
        data_len = config->asynchronous_config.data_len;
        if (data_len > 0u) {
            data_len--;
        }
        tmp = SEI_CTRL_XCVR_TYPE_CFG_WAIT_LEN_SET(config->asynchronous_config.wait_len)
            | SEI_CTRL_XCVR_TYPE_CFG_DATA_LEN_SET(data_len)
            | SEI_CTRL_XCVR_TYPE_CFG_PAR_POL_SET(config->asynchronous_config.parity)
            | SEI_CTRL_XCVR_TYPE_CFG_PAR_EN_SET(config->asynchronous_config.parity_enable)
            | SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEZ_SET(config->asynchronous_config.data_idle_high_z)
            | SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEV_SET(config->asynchronous_config.data_idle_state);
        ptr->CTRL[idx].XCVR.TYPE_CFG = tmp;

#if defined(HPM_IP_FEATURE_SEI_ASYNCHRONOUS_MODE_V2) && HPM_IP_FEATURE_SEI_ASYNCHRONOUS_MODE_V2
        baudrate = config->asynchronous_config.baudrate;
        baud_div = (config->src_clk_freq + (baudrate >> 1u)) / baudrate;
        sync_point = baud_div >> 1u;
#else
        baudrate = (config->asynchronous_config.baudrate / 100) * 102;
        baud_div = (config->src_clk_freq + (baudrate >> 1u)) / baudrate;
        sync_point = (baud_div + 2u);
#endif
        tmp = SEI_CTRL_XCVR_BAUD_CFG_SYNC_POINT_SET(sync_point)
            | SEI_CTRL_XCVR_BAUD_CFG_BAUD_DIV_SET(baud_div - 1u);
        ptr->CTRL[idx].XCVR.BAUD_CFG = tmp;

        txd_point = 0;
        rxd_point = baud_div >> 1u;
        tmp = SEI_CTRL_XCVR_DATA_CFG_TXD_POINT_SET(txd_point)
            | SEI_CTRL_XCVR_DATA_CFG_RXD_POINT_SET(rxd_point);
        ptr->CTRL[idx].XCVR.DATA_CFG = tmp;
        break;
    }

    return status_success;
}

hpm_stat_t sei_cmd_data_format_config_init(SEI_Type *ptr, bool cmd_data_select, uint8_t idx, sei_data_format_config_t *config)
{
    uint32_t tmp;
    uint8_t word_len;
    uint8_t crc_len;

    if (cmd_data_select)
#if defined(HPM_IP_FEATURE_SEI_HAVE_CTRL2_12) && HPM_IP_FEATURE_SEI_HAVE_CTRL2_12
        assert(idx < 13);
#else
        assert(idx < 2);
#endif
    else
#if defined(HPM_IP_FEATURE_SEI_HAVE_DAT10_31) && HPM_IP_FEATURE_SEI_HAVE_DAT10_31
        assert(idx < 32);
#else
        assert(idx < 10);
#endif

    word_len = config->word_len;
    if (word_len > 0u) {
        word_len--;
    }
    crc_len = config->crc_len;
    if (crc_len > 0u) {
        crc_len--;
    }
    tmp = SEI_DAT_MODE_MODE_SET(config->mode)
        | SEI_DAT_MODE_SIGNED_SET(config->signed_flag)
        | SEI_DAT_MODE_BORDER_SET(config->bit_order)
        | SEI_DAT_MODE_WORDER_SET(config->word_order)
        | SEI_DAT_MODE_CRC_INV_SET(config->crc_invert)
        | SEI_DAT_MODE_CRC_SHIFT_SET(config->crc_shift_mode)
        | SEI_DAT_MODE_WLEN_SET(word_len)
        | SEI_DAT_MODE_CRC_LEN_SET(crc_len);
    if (cmd_data_select) {
        ptr->CTRL[idx].CMD.MODE = tmp;
    } else {
        ptr->DAT[idx].MODE = tmp;
    }

    tmp = SEI_DAT_IDX_LAST_BIT_SET(config->last_bit)
        | SEI_DAT_IDX_FIRST_BIT_SET(config->first_bit)
        | SEI_DAT_IDX_MAX_BIT_SET(config->max_bit)
        | SEI_DAT_IDX_MIN_BIT_SET(config->min_bit);
    if (cmd_data_select) {
        ptr->CTRL[idx].CMD.IDX = tmp;
    } else {
        ptr->DAT[idx].IDX = tmp;
    }

    tmp = SEI_DAT_GOLD_GOLD_VALUE_SET(config->gold_value);
    if (!cmd_data_select) {
        ptr->DAT[idx].GOLD = tmp;
    }

    tmp = SEI_DAT_CRCINIT_CRC_INIT_SET(config->crc_init_value);
    if (!cmd_data_select) {
        ptr->DAT[idx].CRCINIT = tmp;
    }

    tmp = SEI_DAT_CRCPOLY_CRC_POLY_SET(config->crc_poly);
    if (!cmd_data_select) {
        ptr->DAT[idx].CRCPOLY = tmp;
    }

    if (cmd_data_select) {
        ptr->CTRL[idx].CMD.MODE |= SEI_CTRL_CMD_MODE_REWIND_MASK;
    } else {
        ptr->DAT[idx].MODE |= SEI_DAT_MODE_REWIND_MASK;
    }

    return status_success;
}

hpm_stat_t sei_cmd_table_config_init(SEI_Type *ptr, uint8_t idx, uint8_t table_idx, sei_command_table_config_t *config)
{
    uint32_t tmp;

    tmp = SEI_CTRL_CMD_TABLE_MIN_CMD_MIN_SET(config->cmd_min_value);
    ptr->CTRL[idx].CMD_TABLE[table_idx].MIN = tmp;

    tmp = SEI_CTRL_CMD_TABLE_MAX_CMD_MAX_SET(config->cmd_max_value);
    ptr->CTRL[idx].CMD_TABLE[table_idx].MAX = tmp;

    tmp = SEI_CTRL_CMD_TABLE_MSK_CMD_MASK_SET(config->cmd_mask_value);
    ptr->CTRL[idx].CMD_TABLE[table_idx].MSK = tmp;

    tmp = SEI_CTRL_CMD_TABLE_PTA_PTR3_SET(config->instr_idx[3])
        | SEI_CTRL_CMD_TABLE_PTA_PTR2_SET(config->instr_idx[2])
        | SEI_CTRL_CMD_TABLE_PTA_PTR1_SET(config->instr_idx[1])
        | SEI_CTRL_CMD_TABLE_PTA_PTR0_SET(config->instr_idx[0]);
    ptr->CTRL[idx].CMD_TABLE[table_idx].PTA = tmp;

    tmp = SEI_CTRL_CMD_TABLE_PTB_PTR7_SET(config->instr_idx[7])
        | SEI_CTRL_CMD_TABLE_PTB_PTR6_SET(config->instr_idx[6])
        | SEI_CTRL_CMD_TABLE_PTB_PTR5_SET(config->instr_idx[5])
        | SEI_CTRL_CMD_TABLE_PTB_PTR4_SET(config->instr_idx[4]);
    ptr->CTRL[idx].CMD_TABLE[table_idx].PTB = tmp;
#if defined(HPM_IP_FEATURE_SEI_HAVE_PTCD) && HPM_IP_FEATURE_SEI_HAVE_PTCD
    tmp = SEI_CTRL_CMD_TABLE_PTC_PTR11_SET(config->instr_idx[11])
        | SEI_CTRL_CMD_TABLE_PTC_PTR10_SET(config->instr_idx[10])
        | SEI_CTRL_CMD_TABLE_PTC_PTR9_SET(config->instr_idx[9])
        | SEI_CTRL_CMD_TABLE_PTC_PTR8_SET(config->instr_idx[8]);
    ptr->CTRL[idx].CMD_TABLE[table_idx].PTC = tmp;

    tmp = SEI_CTRL_CMD_TABLE_PTD_PTR15_SET(config->instr_idx[15])
        | SEI_CTRL_CMD_TABLE_PTD_PTR14_SET(config->instr_idx[14])
        | SEI_CTRL_CMD_TABLE_PTD_PTR13_SET(config->instr_idx[13])
        | SEI_CTRL_CMD_TABLE_PTD_PTR12_SET(config->instr_idx[12]);
    ptr->CTRL[idx].CMD_TABLE[table_idx].PTD = tmp;
#endif

    return status_success;
}

hpm_stat_t sei_state_transition_config_init(SEI_Type *ptr, uint8_t idx, uint8_t latch_idx, uint8_t state, sei_state_transition_config_t *config)
{
#if defined(HPM_IP_FEATURE_SEI_RX_LATCH_FEATURE) && HPM_IP_FEATURE_SEI_RX_LATCH_FEATURE
    uint32_t tmp;
    tmp = SEI_CTRL_LATCH_TRAN_POINTER_SET(config->instr_ptr_value)
        | SEI_CTRL_LATCH_TRAN_CFG_TM_SET(config->timeout_cfg)
        | SEI_CTRL_LATCH_TRAN_CFG_TXD_SET(config->txd_cfg)
        | SEI_CTRL_LATCH_TRAN_CFG_RXD_SET(config->rxd_cfg)
        | SEI_CTRL_LATCH_TRAN_CFG_CLK_SET(config->clk_cfg)
        | SEI_CTRL_LATCH_TRAN_CFG_PTR_SET(config->instr_ptr_cfg)
        | SEI_CTRL_LATCH_TRAN_OV_TM_SET(config->disable_timeout_check)
        | SEI_CTRL_LATCH_TRAN_OV_TXD_SET(config->disable_txd_check)
        | SEI_CTRL_LATCH_TRAN_OV_RXD_SET(config->disable_rxd_check)
        | SEI_CTRL_LATCH_TRAN_OV_CLK_SET(config->disable_clk_check)
        | SEI_CTRL_LATCH_TRAN_OV_PTR_SET(config->disable_instr_ptr_check);
#else
    uint32_t tmp = 0x08u;
    tmp |= SEI_CTRL_LATCH_TRAN_POINTER_SET(config->instr_ptr_value)
        | SEI_CTRL_LATCH_TRAN_CFG_TM_SET(config->timeout_cfg)
        | SEI_CTRL_LATCH_TRAN_CFG_TXD_SET(config->txd_cfg)
        | SEI_CTRL_LATCH_TRAN_CFG_CLK_SET(config->clk_cfg)
        | SEI_CTRL_LATCH_TRAN_CFG_PTR_SET(config->instr_ptr_cfg)
        | SEI_CTRL_LATCH_TRAN_OV_TM_SET(config->disable_timeout_check)
        | SEI_CTRL_LATCH_TRAN_OV_TXD_SET(config->disable_txd_check)
        | SEI_CTRL_LATCH_TRAN_OV_CLK_SET(config->disable_clk_check)
        | SEI_CTRL_LATCH_TRAN_OV_PTR_SET(config->disable_instr_ptr_check);
#endif
    ptr->CTRL[idx].LATCH[latch_idx].TRAN[state] = tmp;
    return status_success;
}

hpm_stat_t sei_state_transition_latch_config_init(SEI_Type *ptr, uint8_t idx, uint8_t latch_idx, sei_state_transition_latch_config_t *config)
{
    uint32_t tmp;

    tmp = SEI_CTRL_LATCH_CFG_DELAY_SET(config->delay)
        | SEI_CTRL_LATCH_CFG_SELECT_SET(config->output_select)
        | SEI_CTRL_LATCH_CFG_EN_SET(config->enable);
    ptr->CTRL[idx].LATCH[latch_idx].CFG = tmp;

    return status_success;
}

hpm_stat_t sei_sample_config_init(SEI_Type *ptr, uint8_t idx, sei_sample_config_t *config)
{
    uint32_t tmp;

    tmp = SEI_CTRL_POS_SMP_CFG_ONCE_SET(config->sample_once)
        | SEI_CTRL_POS_SMP_CFG_LAT_SEL_SET(config->latch_select)
        | SEI_CTRL_POS_SMP_CFG_WINDOW_SET(config->sample_window);
    ptr->CTRL[idx].POS.SMP_CFG = tmp;

    ptr->CTRL[idx].POS.SMP_DAT = SEI_CTRL_POS_SMP_DAT_DAT_SEL_SET(config->data_register_select);

    tmp = SEI_CTRL_POS_SMP_EN_ACC_EN_SET(config->acc_data_use_rx)
        | SEI_CTRL_POS_SMP_EN_ACC_SEL_SET(config->acc_data_idx)
        | SEI_CTRL_POS_SMP_EN_SPD_EN_SET(config->spd_data_use_rx)
        | SEI_CTRL_POS_SMP_EN_SPD_SEL_SET(config->spd_data_idx)
        | SEI_CTRL_POS_SMP_EN_REV_EN_SET(config->rev_data_use_rx)
        | SEI_CTRL_POS_SMP_EN_REV_SEL_SET(config->rev_data_idx)
        | SEI_CTRL_POS_SMP_EN_POS_EN_SET(config->pos_data_use_rx)
        | SEI_CTRL_POS_SMP_EN_POS_SEL_SET(config->pos_data_idx);
    ptr->CTRL[idx].POS.SMP_EN = tmp;

    return status_success;
}

hpm_stat_t sei_update_config_init(SEI_Type *ptr, uint8_t idx, sei_update_config_t *config)
{
    uint32_t tmp;

    tmp = SEI_CTRL_POS_UPD_CFG_TIME_OVRD_SET(config->time_use_override)
        | SEI_CTRL_POS_UPD_CFG_ONERR_SET(config->update_on_err)
        | SEI_CTRL_POS_UPD_CFG_LAT_SEL_SET(config->latch_select);
    ptr->CTRL[idx].POS.UPD_CFG = tmp;

    ptr->CTRL[idx].POS.UPD_DAT = SEI_CTRL_POS_UPD_DAT_DAT_SEL_SET(config->data_register_select);

    tmp = SEI_CTRL_POS_UPD_EN_ACC_EN_SET(config->acc_data_use_rx)
        | SEI_CTRL_POS_UPD_EN_ACC_SEL_SET(config->acc_data_idx)
        | SEI_CTRL_POS_UPD_EN_SPD_EN_SET(config->spd_data_use_rx)
        | SEI_CTRL_POS_UPD_EN_SPD_SEL_SET(config->spd_data_idx)
        | SEI_CTRL_POS_UPD_EN_REV_EN_SET(config->rev_data_use_rx)
        | SEI_CTRL_POS_UPD_EN_REV_SEL_SET(config->rev_data_idx)
        | SEI_CTRL_POS_UPD_EN_POS_EN_SET(config->pos_data_use_rx)
        | SEI_CTRL_POS_UPD_EN_POS_SEL_SET(config->pos_data_idx);
    ptr->CTRL[idx].POS.UPD_EN = tmp;

    return status_success;
}

hpm_stat_t sei_trigger_input_config_init(SEI_Type *ptr, uint8_t idx, sei_trigger_input_config_t *config)
{
    uint32_t tmp;
    uint32_t period;

    tmp = SEI_CTRL_TRG_PRD_CFG_ARMING_SET(config->trig_period_arming_mode)
        | SEI_CTRL_TRG_PRD_CFG_SYNC_SET(config->trig_period_sync_enable);
    ptr->CTRL[idx].TRG.PRD_CFG = tmp;

    period = config->trig_period_time;
    if (period > 0) {
        period--;
    }
    ptr->CTRL[idx].TRG.PRD = SEI_CTRL_TRG_PRD_PERIOD_SET(period);

    tmp = SEI_CTRL_TRG_IN_CFG_PRD_EN_SET(config->trig_period_enable)
        | SEI_CTRL_TRG_IN_CFG_SYNC_SEL_SET(config->trig_period_sync_select)
        | SEI_CTRL_TRG_IN_CFG_IN1_EN_SET(config->trig_in1_enable)
        | SEI_CTRL_TRG_IN_CFG_IN1_SEL_SET(config->trig_in1_select)
        | SEI_CTRL_TRG_IN_CFG_IN0_EN_SET(config->trig_in0_enable)
        | SEI_CTRL_TRG_IN_CFG_IN0_SEL_SET(config->trig_in0_select)
#if defined(HPM_IP_FEATURE_SEI_TIMEOUT_REWIND_FEATURE) && HPM_IP_FEATURE_SEI_TIMEOUT_REWIND_FEATURE
        | SEI_CTRL_TRG_IN_CFG_REWIND_EN_SET(config->rewind_enable)
        | SEI_CTRL_TRG_IN_CFG_REWIND_SEL_SET(config->rewind_select)
#endif
        ;
    ptr->CTRL[idx].TRG.IN_CFG = tmp;

    return status_success;
}

hpm_stat_t sei_trigger_output_config_init(SEI_Type *ptr, uint8_t idx, sei_trigger_output_config_t *config)
{
    uint32_t tmp;

    tmp = ptr->CTRL[idx].TRG.OUT_CFG;
    if (config->src_latch_select == SEI_LATCH_0) {
        tmp &= ~(SEI_CTRL_TRG_OUT_CFG_OUT0_SEL_MASK | SEI_CTRL_TRG_OUT_CFG_OUT0_EN_MASK);
        tmp |= SEI_CTRL_TRG_OUT_CFG_OUT0_EN_SET(config->trig_out_enable) | SEI_CTRL_TRG_OUT_CFG_OUT0_SEL_SET(config->trig_out_select);
    } else if (config->src_latch_select == SEI_LATCH_1) {
        tmp &= ~(SEI_CTRL_TRG_OUT_CFG_OUT1_SEL_MASK | SEI_CTRL_TRG_OUT_CFG_OUT1_EN_MASK);
        tmp |= SEI_CTRL_TRG_OUT_CFG_OUT1_EN_SET(config->trig_out_enable) | SEI_CTRL_TRG_OUT_CFG_OUT1_SEL_SET(config->trig_out_select);
    } else if (config->src_latch_select == SEI_LATCH_2) {
        tmp &= ~(SEI_CTRL_TRG_OUT_CFG_OUT2_SEL_MASK | SEI_CTRL_TRG_OUT_CFG_OUT2_EN_MASK);
        tmp |= SEI_CTRL_TRG_OUT_CFG_OUT2_EN_SET(config->trig_out_enable) | SEI_CTRL_TRG_OUT_CFG_OUT2_SEL_SET(config->trig_out_select);
    } else if (config->src_latch_select == SEI_LATCH_3) {
        tmp &= ~(SEI_CTRL_TRG_OUT_CFG_OUT3_SEL_MASK | SEI_CTRL_TRG_OUT_CFG_OUT3_EN_MASK);
        tmp |= SEI_CTRL_TRG_OUT_CFG_OUT3_EN_SET(config->trig_out_enable) | SEI_CTRL_TRG_OUT_CFG_OUT3_SEL_SET(config->trig_out_select);
    } else {
        return status_invalid_argument;
    }
    ptr->CTRL[idx].TRG.OUT_CFG = tmp;

    return status_success;
}

hpm_stat_t sei_engine_config_init(SEI_Type *ptr, uint8_t idx, sei_engine_config_t *config)
{
    uint32_t tmp;

    tmp = SEI_CTRL_ENGINE_PTR_CFG_DAT_CDM_SET(config->data_cdm_idx)
        | SEI_CTRL_ENGINE_PTR_CFG_DAT_BASE_SET(config->data_base_idx)
        | SEI_CTRL_ENGINE_PTR_CFG_POINTER_WDOG_SET(config->wdg_instr_idx)
        | SEI_CTRL_ENGINE_PTR_CFG_POINTER_INIT_SET(config->init_instr_idx);
    ptr->CTRL[idx].ENGINE.PTR_CFG = tmp;

    ptr->CTRL[idx].ENGINE.WDG_CFG = SEI_CTRL_ENGINE_WDG_CFG_WDOG_TIME_SET(config->wdg_time);

    tmp = SEI_CTRL_ENGINE_CTRL_WATCH_SET(config->wdg_enable)
        | SEI_CTRL_ENGINE_CTRL_EXCEPT_SET(config->wdg_action)
        | SEI_CTRL_ENGINE_CTRL_ARMING_SET(config->arming_mode);
    ptr->CTRL[idx].ENGINE.CTRL = tmp;

    return status_success;
}

void sei_set_instr(SEI_Type *ptr, uint8_t idx, uint8_t op, uint8_t ck, uint8_t crc, uint8_t data, uint8_t opr)
{
    uint32_t tmp;

#if !defined(HPM_IP_FEATURE_SEI_HAVE_INTR64_255) || !HPM_IP_FEATURE_SEI_HAVE_INTR64_255
    assert(idx < 64);
#endif
    if ((op != SEI_INSTR_OP_HALT) && (op != SEI_INSTR_OP_JUMP) && (opr > 0)) {
        opr--;
    }
    if (opr > 0x1F) {
        opr = 0x1F;
    }
    tmp = SEI_INSTR_OP_SET(op)
        | SEI_INSTR_CK_SET(ck)
        | SEI_INSTR_CRC_SET(crc)
        | SEI_INSTR_DAT_SET(data)
        | SEI_INSTR_OPR_SET(opr);

    ptr->INSTR[idx] = tmp;
}
