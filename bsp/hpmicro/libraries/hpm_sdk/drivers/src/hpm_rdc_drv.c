/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"
#include "hpm_rdc_drv.h"

void rdc_output_config(RDC_Type *ptr, rdc_output_cfg_t *cfg)
{
    uint32_t rate;

    rate = cfg->excitation_period_cycle >> (cfg->excitation_precision + 2);
    ptr->EXC_TIMMING = RDC_EXC_TIMMING_SMP_RATE_SET(rate) |
                        RDC_EXC_TIMMING_SMP_NUM_SET(cfg->excitation_precision) |
                        RDC_EXC_TIMMING_PWM_PRD_SET(cfg->pwm_period)|
                        RDC_EXC_TIMMING_SWAP_SET(cfg->output_swap);
    if (cfg->mode == rdc_output_dac) {
        ptr->EXC_SCALING = RDC_EXC_SCALING_AMP_MAN_SET(cfg->amp_man) |
                            RDC_EXC_SCALING_AMP_EXP_SET(cfg->amp_exp);
        ptr->EXC_OFFSET = RDC_EXC_OFFSET_AMP_OFFSET_SET(cfg->amp_offset + 0x800000);
        ptr->OUT_CTL = RDC_OUT_CTL_CH_I_SEL_SET(cfg->dac_chn_i_sel) |
                        RDC_OUT_CTL_CH_Q_SEL_SET(cfg->dac_chn_q_sel);
    } else if (cfg->mode == rdc_output_pwm) {
        ptr->PWM_SCALING = RDC_EXC_SCALING_AMP_MAN_SET(cfg->amp_man) |
                            RDC_EXC_SCALING_AMP_EXP_SET(cfg->amp_exp) |
                            RDC_PWM_SCALING_DITHER_SET(cfg->pwm_dither_enable) |
                            RDC_PWM_SCALING_P_POL_SET(cfg->pwm_exc_p_low_active) |
                            RDC_PWM_SCALING_N_POL_SET(cfg->pwm_exc_n_low_active);
        ptr->PWM_OFFSET = RDC_PWM_OFFSET_AMP_OFFSET_SET(cfg->amp_offset + (rate >> 1));
        ptr->PWM_DZ = RDC_PWM_DZ_DZ_N_SET(cfg->pwm_deadzone_n) |
                        RDC_PWM_DZ_DZ_P_SET(cfg->pwm_deadzone_p);
    }
    if (cfg->trig_by_hw) {
        ptr->EXC_SYNC_DLY = RDC_EXC_SYNC_DLY_DELAY_SET(cfg->hw_trig_delay);
    } else {
        ptr->EXC_SYNC_DLY = RDC_EXC_SYNC_DLY_DISABLE_MASK;
    }
}


void rdc_input_config(RDC_Type *ptr, rdc_input_cfg_t *cfg)
{
    ptr->RDC_CTL = (ptr->RDC_CTL & (~(RDC_RDC_CTL_RECTIFY_SEL_MASK | RDC_RDC_CTL_ACC_LEN_MASK | RDC_RDC_CTL_TS_SEL_MASK)))
                    | RDC_RDC_CTL_RECTIFY_SEL_SET(cfg->rectify_signal_sel)
                    | RDC_RDC_CTL_ACC_LEN_SET(cfg->acc_cycle_len)
                    | RDC_RDC_CTL_TS_SEL_SET(cfg->acc_stamp);
    ptr->IN_CTL = RDC_IN_CTL_PORT_I_SEL_SET(cfg->acc_input_port_i) |
                    RDC_IN_CTL_CH_I_SEL_SET(cfg->acc_input_chn_i) |
                    RDC_IN_CTL_PORT_Q_SEL_SET(cfg->acc_input_port_q) |
                    RDC_IN_CTL_CH_Q_SEL_SET(cfg->acc_input_chn_q);
}

uint32_t rdc_get_acc_avl(RDC_Type *ptr, rdc_input_acc_chn_t chn)
{
    if (chn == rdc_acc_chn_i) {
        return RDC_ACC_I_ACC_GET(ptr->ACC_I);
    } else {
        return RDC_ACC_Q_ACC_GET(ptr->ACC_Q);
    }
}

void rdc_output_trig_offset_config(RDC_Type *ptr, rdc_output_trig_chn_t chn, int32_t offset)
{
    if (chn == trigger_out_0) {
        ptr->TRIG_OUT0_CFG = (ptr->TRIG_OUT0_CFG & (~RDC_TRIG_OUT0_CFG_LEAD_TIM_MASK)) |
                    RDC_TRIG_OUT0_CFG_LEAD_TIM_SET(offset + RDC_TRIG_OUT0_CFG_LEAD_TIM_MASK + 1);
    } else if (chn == trigger_out_1) {
        ptr->TRIG_OUT1_CFG = (ptr->TRIG_OUT1_CFG & (~RDC_TRIG_OUT1_CFG_LEAD_TIM_MASK)) |
                    RDC_TRIG_OUT1_CFG_LEAD_TIM_SET(offset + RDC_TRIG_OUT1_CFG_LEAD_TIM_MASK + 1);
    }
}

void rdc_output_trig_enable(RDC_Type *ptr, rdc_output_trig_chn_t chn)
{
    if (chn == trigger_out_0) {
        ptr->TRIG_OUT0_CFG |= RDC_TRIG_OUT0_CFG_ENABLE_MASK;
    } else if (chn == trigger_out_1) {
        ptr->TRIG_OUT1_CFG |= RDC_TRIG_OUT1_CFG_ENABLE_MASK;
    }
}

void rdc_output_trig_disable(RDC_Type *ptr, rdc_output_trig_chn_t chn)
{
    if (chn == trigger_out_0) {
        ptr->TRIG_OUT0_CFG &= ~RDC_TRIG_OUT0_CFG_ENABLE_MASK;
    } else if (chn == trigger_out_1) {
        ptr->TRIG_OUT1_CFG &= ~RDC_TRIG_OUT1_CFG_ENABLE_MASK;
    }
}

int32_t rdc_get_i_maxval(RDC_Type *ptr)
{
    uint32_t val;

    val = ptr->MAX_I;
    if (RDC_MAX_I_VALID_GET(val)) {
        return RDC_MAX_I_MAX_GET(val);
    } else {
        return -1;
    }

}

int32_t rdc_get_i_minval(RDC_Type *ptr)
{
    uint32_t val;

    val = ptr->MIN_I;
    if (RDC_MIN_I_VALID_GET(val)) {
        return RDC_MIN_I_MIN_GET(val);
    } else {
        return -1;
    }
}

int32_t rdc_get_q_maxval(RDC_Type *ptr)
{
    uint32_t val;

    val = ptr->MAX_Q;
    if (RDC_MAX_Q_VALID_GET(val)) {
        return RDC_MAX_Q_MAX_GET(val);
    } else {
        return -1;
    }
}

int32_t rdc_get_q_minval(RDC_Type *ptr)
{
    uint32_t val;

    val = ptr->MIN_Q;
    if (RDC_MIN_Q_VALID_GET(val)) {
        return RDC_MIN_Q_MIN_GET(val);
    } else {
        return -1;
    }
}

void rdc_set_edge_detection_offset(RDC_Type *ptr, rdc_input_acc_chn_t chn, int32_t offset)
{
    if (chn == rdc_acc_chn_i) {
        ptr->THRS_I = RDC_THRS_I_THRS_SET(offset);
    } else {
        ptr->THRS_Q = RDC_THRS_Q_THRS_SET(offset);
    }
}

void rdc_set_acc_config(RDC_Type *ptr, rdc_acc_cfg_t *cfg)
{
    ptr->EDG_DET_CTL = RDC_EDG_DET_CTL_FILTER_SET(cfg->continue_edge_num) |
                        RDC_EDG_DET_CTL_HOLD_SET(cfg->edge_distance);
    if (cfg->right_shift_without_sign < 9) {
        ptr->ACC_SCALING = RDC_ACC_SCALING_ACC_SHIFT_SET(8 - cfg->right_shift_without_sign);
    } else {
        ptr->ACC_SCALING = RDC_ACC_SCALING_ACC_SHIFT_SET(cfg->right_shift_without_sign);
    }
    if (cfg->error_data_remove) {
        ptr->ACC_SCALING |= RDC_ACC_SCALING_TOXIC_LK_MASK;
    } else {
        ptr->ACC_SCALING &= ~RDC_ACC_SCALING_TOXIC_LK_MASK;
    }
    ptr->EXC_PERIOD = RDC_EXC_PERIOD_EXC_PERIOD_SET(cfg->exc_carrier_period);
    ptr->SYNC_DELAY_I = RDC_SYNC_DELAY_I_DELAY_SET(cfg->sync_delay_i);
    ptr->SYNC_DELAY_Q = RDC_SYNC_DELAY_Q_DELAY_SET(cfg->sync_delay_q);
    ptr->AMP_MAX = RDC_AMP_MAX_MAX_SET(cfg->amp_max);
    ptr->AMP_MIN = RDC_AMP_MIN_MIN_SET(cfg->amp_min);
}

void rdc_set_acc_sync_delay(RDC_Type *ptr, rdc_input_acc_chn_t chn, uint32_t delay)
{
    if (chn == rdc_acc_chn_i) {
        ptr->SYNC_DELAY_I = RDC_SYNC_DELAY_I_DELAY_SET(delay);
    } else {
        ptr->SYNC_DELAY_Q = RDC_SYNC_DELAY_Q_DELAY_SET(delay);
    }
}
