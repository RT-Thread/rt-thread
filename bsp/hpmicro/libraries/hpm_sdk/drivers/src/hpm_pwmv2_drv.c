/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_soc_feature.h"
#include "hpm_pwmv2_drv.h"

void pwmv2_deinit(PWMV2_Type *pwm_x)
{
    pwm_x->IRQ_EN_CMP = 0;
    pwm_x->IRQ_EN_RELOAD = 0;
    pwm_x->IRQ_EN_CAP_POS = 0;
    pwm_x->IRQ_EN_CAP_NEG = 0;
    pwm_x->IRQ_EN_FAULT = 0;
    pwm_x->IRQ_EN_BURSTEND = 0;
    pwm_x->IRQ_EN = 0;
    pwm_x->DMA_EN = 0;
    pwm_x->IRQ_STS |= pwm_x->IRQ_STS;
    pwm_x->IRQ_STS_CMP = 0;
    pwm_x->IRQ_STS_RELOAD = 0;
    pwm_x->IRQ_STS_CAP_POS = 0;
    pwm_x->IRQ_STS_CAP_NEG = 0;
    pwm_x->IRQ_STS_FAULT = 0;
    pwm_x->IRQ_STS_BURSTEND = 0;
    for (uint8_t i = 0; i < PWM_SOC_CMP_MAX_COUNT; i++) {
        pwm_x->CMP[i].CFG = 0;
    }
    for (uint8_t i = 0; i < PWM_SOC_OUTPUT_TO_PWM_MAX_COUNT; i++) {
        pwm_x->PWM[i].CFG0 = 0;
        pwm_x->PWM[i].CFG1 = 0;
        pwm_x->PWM[i].DEAD_AREA = 0;
    }
    for (uint8_t i = 0; i < PWMV2_SOC_CAL_COUNT_MAX; i++) {
        pwm_x->CAL[i].CFG0 = 0;
        pwm_x->CAL[i].CFG1 = 0;
    }
}

void pwmv2_config_cmp(PWMV2_Type *pwm_x, uint8_t index, pwmv2_cmp_config_t *config)
{
    pwmv2_select_cmp_source(pwm_x, index, config->cmp_source, config->cmp_source_index);
    pwmv2_cmp_update_trig_time(pwm_x, index, config->update_trigger);
    if (config->update_trigger == pwm_shadow_register_update_on_trigmux) {
        pwmv2_select_cmp_trigmux(pwm_x, index, config->update_trigger_index);
    }
    if (index >= PWM_CMP_UNABLE_OUTPUT_INDEX) {
        pwmv2_cmp_select_counter(pwm_x, index, config->cmp_source_index);
    }
    if (config->cmp_source == cmp_value_from_shadow_val) {
        pwmv2_shadow_register_unlock(pwm_x);
        if (config->enable_hrcmp) {
            pwmv2_set_shadow_val(pwm_x, config->cmp_source_index, config->cmp, config->hrcmp, config->enable_half_cmp);
        } else {
            pwmv2_set_shadow_val(pwm_x, config->cmp_source_index, config->cmp, 0, config->enable_half_cmp);
        }
        pwmv2_shadow_register_lock(pwm_x);
    }
}

void pwmv2_config_async_fault_source(PWMV2_Type *pwm_x, pwm_channel_t index, pwmv2_async_fault_source_config_t *config)
{
    pwm_x->PWM[index].CFG0 = (pwm_x->PWM[index].CFG0 & ~(PWMV2_PWM_CFG0_FAULT_SEL_ASYNC_MASK | PWMV2_PWM_CFG0_FAULT_POL_ASYNC_MASK))
        | PWMV2_PWM_CFG0_FAULT_SEL_ASYNC_SET(config->async_signal_from_pad_index)
        | PWMV2_PWM_CFG0_FAULT_POL_ASYNC_SET(config->fault_async_pad_level);
}

void pwmv2_config_pwm(PWMV2_Type *pwm_x, pwm_channel_t index,
                                  pwmv2_config_t *config, bool enable_pair_mode)
{
    pwm_x->PWM[index].CFG0 = PWMV2_PWM_CFG0_TRIG_SEL4_SET(config->enable_four_cmp) |
                            PWMV2_PWM_CFG0_OUT_POLARITY_SET(config->invert_output) |
                            PWMV2_PWM_CFG0_POL_UPDATE_SEL_SET(config->update_polarity_time);
    pwm_x->PWM[index].CFG1 = PWMV2_PWM_CFG1_HIGHZ_EN_N_SET(config->enable_output) |
                            PWMV2_PWM_CFG1_FORCE_UPDATE_TIME_SET(config->force_shadow_trigger) |
                            PWMV2_PWM_CFG1_FAULT_MODE_SET(config->fault_mode) |
                            PWMV2_PWM_CFG1_FAULT_REC_TIME_SET(config->fault_recovery_trigger) |
                            PWMV2_PWM_CFG1_PAIR_MODE_SET(enable_pair_mode) |
                            PWMV2_PWM_CFG1_PWM_LOGIC_SET(config->logic) |
                            PWMV2_PWM_CFG1_FORCE_TIME_SET(config->force_trigger) |
                            PWMV2_PWM_CFG1_FORCE_TRIG_SEL_SET(config->force_shadow_trigmux_index) |
                            PWMV2_PWM_CFG1_FORCE_ACT_SEL_SET(config->force_trigmux_index) |
                            PWMV2_PWM_CFG1_PWM_FORCE_SEL_SET(config->fault_recovery_trigmux_index);
    pwmv2_config_async_fault_source(pwm_x, index, &config->async_fault_source);
    if (enable_pair_mode) {
        pwmv2_set_dead_area(pwm_x, index, config->dead_zone_in_half_cycle);
    }
}

hpm_stat_t pwmv2_setup_waveform(PWMV2_Type *pwm_x,
                        pwm_channel_t chn, pwmv2_config_t *pwm_config,
                        uint8_t cmp_start_index, pwmv2_cmp_config_t *cmp, uint8_t cmp_num)
{
    uint8_t i;

    for (i =  0; i < cmp_num; i++) {
        pwmv2_config_cmp(pwm_x, cmp_start_index + i, &cmp[i]);
    }
    pwmv2_config_pwm(pwm_x, chn, pwm_config, false);

    return status_success;
}

hpm_stat_t pwmv2_setup_waveform_in_pair(PWMV2_Type *pwm_x, pwm_channel_t chn,
                        pwmv2_pair_config_t *pwm_pair_config, uint8_t cmp_start_index,
                        pwmv2_cmp_config_t *cmp, uint8_t cmp_num)
{
    uint8_t i;

    for (i =  0; i < cmp_num; i++) {
        pwmv2_config_cmp(pwm_x, cmp_start_index + i, &cmp[i]);
    }
    pwmv2_config_pwm(pwm_x, chn, &pwm_pair_config->pwm[0], true);
    pwmv2_config_pwm(pwm_x, chn + 1, &pwm_pair_config->pwm[1], true);

    return status_success;
}

void pwmv2_setup_cmp_calculate(PWMV2_Type *pwm_x, uint8_t cal_index, pwmv2_cmp_calculate_cfg_t *cal)
{
    pwm_x->CAL[cal_index].CFG0 = PWMV2_CAL_CFG0_CAL_LU_PARAM_SET(cal->up_limit_param) |
            PWMV2_CAL_CFG0_CAL_LL_PARAM_SET(cal->low_limit_param) |
            PWMV2_CAL_CFG0_CAL_T_PARAM_SET(cal->t_param) |
            PWMV2_CAL_CFG0_CAL_D_PARAM_SET(cal->d_param);
    pwm_x->CAL[cal_index].CFG1 = PWMV2_CAL_CFG1_CAL_T_INDEX_SET(cal->counter_index) |
            PWMV2_CAL_CFG1_CAL_IN_INDEX_SET(cal->in_index) |
            PWMV2_CAL_CFG1_CAL_LU_EN_SET(cal->enable_up_limit) |
            PWMV2_CAL_CFG1_CAL_LIM_UP_SET(cal->up_limit_offset_index) |
            PWMV2_CAL_CFG1_CAL_LL_EN_SET(cal->enbale_low_limit) |
            PWMV2_CAL_CFG1_CAL_LIM_LO_SET (cal->low_limit_offset_index) |
            PWMV2_CAL_CFG1_CAL_IN_OFF_SET(cal->in_offset_index);
}
