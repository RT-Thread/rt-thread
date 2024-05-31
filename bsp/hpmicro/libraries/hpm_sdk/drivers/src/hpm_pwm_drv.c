/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_soc_feature.h"
#include "hpm_pwm_drv.h"

hpm_stat_t pwm_load_cmp_shadow_on_match(PWM_Type *pwm_x,
                                         uint8_t index,
                                         pwm_cmp_config_t *config)
{
    if (config->mode != pwm_cmp_mode_output_compare) {
        return status_invalid_argument;
    }
    pwm_config_cmp(pwm_x, index, config);
    pwm_issue_shadow_register_lock_event(pwm_x);
    pwm_x->GCR = ((pwm_x->GCR & ~(PWM_GCR_CMPSHDWSEL_MASK)) | PWM_GCR_CMPSHDWSEL_SET(index));
    return status_success;
}

void pwm_get_captured_count(PWM_Type *pwm_x, uint32_t *buf, pwm_counter_type_t counter, uint8_t start_index, uint8_t num)
{
    uint32_t i;
    if (counter == pwm_counter_type_capture_falling_edge) {
        for (i = start_index; i < start_index + num; i++) {
            *buf = pwm_x->CAPNEG[i];
        }
    } else {
        for (i = start_index; i < start_index + num; i++) {
            *buf = pwm_x->CAPPOS[i];
        }
    }
}

void pwm_get_default_cmp_config(PWM_Type *pwm_x, pwm_cmp_config_t *config)
{
    (void) pwm_x;
    config->mode = pwm_cmp_mode_output_compare;
    config->update_trigger = pwm_shadow_register_update_on_modify;
    config->enable_ex_cmp = false;
#if defined(PWM_SOC_HRPWM_SUPPORT) && PWM_SOC_HRPWM_SUPPORT
    config->enable_hrcmp = false;
    config->hrcmp = 0;
#endif
    config->cmp = 0;
    config->ex_cmp = 0;
    config->half_clock_cmp = 0;
    config->jitter_cmp = 0;
}

void pwm_get_default_output_channel_config(PWM_Type *pwm_x, pwm_output_channel_t *config)
{
    (void) pwm_x;
    config->cmp_start_index = 0;
    config->cmp_end_index = 0;
    config->invert_output = false;
}

void pwm_get_default_pwm_config(PWM_Type *pwm_x, pwm_config_t *config)
{
    (void) pwm_x;
    config->enable_output = false;
    config->update_trigger = pwm_shadow_register_update_on_modify;
    config->fault_mode = pwm_fault_mode_force_output_highz;
    config->fault_recovery_trigger = pwm_fault_recovery_on_fault_clear;
    config->force_source = pwm_force_source_software;
    config->dead_zone_in_half_cycle = 0;
}

void pwm_get_default_pwm_pair_config(PWM_Type *pwm_x, pwm_pair_config_t *config)
{
    pwm_get_default_pwm_config(pwm_x, &config->pwm[0]);
    pwm_get_default_pwm_config(pwm_x, &config->pwm[1]);
}

hpm_stat_t pwm_setup_waveform_in_pair(PWM_Type *pwm_x, uint8_t pwm_index,
                        pwm_pair_config_t *pwm_pair_config, uint8_t cmp_start_index,
                        pwm_cmp_config_t *cmp, uint8_t cmp_num)
{
    uint8_t i;
    pwm_output_channel_t ch_config;

    if ((pwm_index > PWM_SOC_PWM_MAX_COUNT)
        || !cmp_num
        || (cmp_start_index > PWM_SOC_CMP_MAX_COUNT)
        || (cmp_start_index + cmp_num > PWM_SOC_CMP_MAX_COUNT)
        || ((pwm_index > (PWM_SOC_PWM_MAX_COUNT - 1))
                    || (pwm_index & 0x1))) {
        return status_invalid_argument;
    }

    pwm_x->PWMCFG[pwm_index] &= ~PWM_PWMCFG_OEN_MASK;
    pwm_x->PWMCFG[pwm_index + 1] &= ~PWM_PWMCFG_OEN_MASK;

    for (i =  0; i < cmp_num; i++) {
        pwm_config_cmp(pwm_x, cmp_start_index + i, &cmp[i]);
    }
    ch_config.cmp_start_index = cmp_start_index;
    ch_config.cmp_end_index = cmp_start_index + cmp_num - 1;
    ch_config.invert_output = pwm_pair_config->pwm[0].invert_output;
    pwm_config_output_channel(pwm_x, pwm_index, &ch_config);

    ch_config.invert_output = pwm_pair_config->pwm[1].invert_output;
    pwm_config_output_channel(pwm_x, pwm_index + 1, &ch_config);

    pwm_config_pwm(pwm_x, pwm_index, &pwm_pair_config->pwm[0], true);
    pwm_config_pwm(pwm_x, pwm_index + 1, &pwm_pair_config->pwm[1], true);

    return status_success;
}

hpm_stat_t pwm_setup_waveform(PWM_Type *pwm_x,
                        uint8_t pwm_index, pwm_config_t *pwm_config,
                        uint8_t cmp_start_index, pwm_cmp_config_t *cmp, uint8_t cmp_num)
{
    uint8_t i;
    pwm_output_channel_t ch_config;
    if (!cmp_num
        || (cmp_start_index > PWM_SOC_CMP_MAX_COUNT)
        || (cmp_start_index + cmp_num > PWM_SOC_CMP_MAX_COUNT)) {
        return status_invalid_argument;
    }

    for (i =  0; i < cmp_num; i++) {
        pwm_config_cmp(pwm_x, cmp_start_index + i, &cmp[i]);
    }
    ch_config.cmp_start_index = cmp_start_index;
    ch_config.cmp_end_index = cmp_start_index + cmp_num - 1;
    ch_config.invert_output = pwm_config->invert_output;
    pwm_config_output_channel(pwm_x, pwm_index, &ch_config);
    if (pwm_index < PWM_SOC_PWM_MAX_COUNT) {
        pwm_config_pwm(pwm_x, pwm_index, pwm_config, false);
    }
    return status_success;
}

hpm_stat_t pwm_update_raw_cmp_edge_aligned(PWM_Type *pwm_x, uint8_t cmp_index, uint32_t target_cmp)
{
    pwm_shadow_register_unlock(pwm_x);
    pwm_cmp_update_cmp_value(pwm_x, cmp_index, target_cmp, 0);
    return status_success;
}

hpm_stat_t pwm_update_raw_cmp_central_aligned(PWM_Type *pwm_x, uint8_t cmp1_index,
                                       uint8_t cmp2_index, uint32_t target_cmp1, uint32_t target_cmp2)
{
    uint32_t reload = PWM_RLD_RLD_GET(pwm_x->RLD);
    if (!target_cmp1) {
        target_cmp1 = reload + 1;
    }
    if (!target_cmp2) {
        target_cmp2 = reload + 1;
    }
    pwm_shadow_register_unlock(pwm_x);
    pwm_cmp_update_cmp_value(pwm_x, cmp1_index, target_cmp1, 0);
    pwm_cmp_update_cmp_value(pwm_x, cmp2_index, target_cmp2, 0);
    return status_success;
}
#if defined(PWM_SOC_HRPWM_SUPPORT) && PWM_SOC_HRPWM_SUPPORT

hpm_stat_t pwm_update_raw_hrcmp_edge_aligned(PWM_Type *pwm_x, uint8_t cmp_index, uint32_t target_cmp,
            uint16_t target_hrcmp)
{
    pwm_shadow_register_unlock(pwm_x);
    pwm_cmp_update_hrcmp_value(pwm_x, cmp_index, target_cmp, target_hrcmp);
    return status_success;
}

hpm_stat_t pwm_update_raw_hrcmp_central_aligned(PWM_Type *pwm_x, uint8_t cmp1_index,
                                       uint8_t cmp2_index, uint32_t target_cmp1, uint32_t target_cmp2,
                                        uint16_t target_hrcmp1, uint16_t target_hrcmp2)
{
    uint32_t reload = PWM_RLD_RLD_GET(pwm_x->RLD);
    if (!target_cmp1) {
        target_cmp1 = reload + 1;
    }
    if (!target_cmp2) {
        target_cmp2 = reload + 1;
    }
    pwm_shadow_register_unlock(pwm_x);
    pwm_cmp_update_hrcmp_value(pwm_x, cmp1_index, target_cmp1, target_hrcmp1);
    pwm_cmp_update_hrcmp_value(pwm_x, cmp2_index, target_cmp2, target_hrcmp2);
    return status_success;
}
#endif
