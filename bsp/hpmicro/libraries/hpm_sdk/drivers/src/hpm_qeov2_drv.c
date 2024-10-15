/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_qeov2_drv.h"

void qeo_wave_get_default_mode_config(QEOV2_Type *base, qeo_wave_mode_t *config)
{
    (void)base;

    config->wave0.above_max_limit = qeo_wave_above_max_limit_max_val;
    config->wave0.high_area0_limit = qeo_wave_high_area_limit_max_val;
    config->wave0.high_area1_limit = qeo_wave_high_area_limit_max_val;
    config->wave0.low_area0_limit = qeo_wave_low_area_limit_zero;
    config->wave0.low_area1_limit = qeo_wave_low_area_limit_zero;
    config->wave0.below_min_limit = qeo_wave_below_min_limit_zero;

    config->wave1.above_max_limit = qeo_wave_above_max_limit_max_val;
    config->wave1.high_area0_limit = qeo_wave_high_area_limit_max_val;
    config->wave1.high_area1_limit = qeo_wave_high_area_limit_max_val;
    config->wave1.low_area0_limit = qeo_wave_low_area_limit_zero;
    config->wave1.low_area1_limit = qeo_wave_low_area_limit_zero;
    config->wave1.below_min_limit = qeo_wave_below_min_limit_zero;

    config->wave2.above_max_limit = qeo_wave_above_max_limit_max_val;
    config->wave2.high_area0_limit = qeo_wave_high_area_limit_max_val;
    config->wave2.high_area1_limit = qeo_wave_high_area_limit_max_val;
    config->wave2.low_area0_limit = qeo_wave_low_area_limit_zero;
    config->wave2.low_area1_limit = qeo_wave_low_area_limit_zero;
    config->wave2.below_min_limit = qeo_wave_below_min_limit_zero;

    config->dq_valid_trig_enable = false;
    config->pos_valid_trig_enable = true;
    config->vd_vq_inject_enable = false;
    config->vd_vq_from_sw = false;

    config->saddle_type = 0;
    config->wave_type = qeo_wave_cosine;
}

void qeo_wave_config_mode(QEOV2_Type *base, qeo_wave_mode_t *config)
{
    base->WAVE.MODE = QEOV2_WAVE_MODE_WAVE2_ABOVE_MAX_LIMIT_SET(config->wave2.above_max_limit)
                    | QEOV2_WAVE_MODE_WAVE2_HIGH_AREA1_LIMIT_SET(config->wave2.high_area1_limit)
                    | QEOV2_WAVE_MODE_WAVE2_HIGH_AREA0_LIMIT_SET(config->wave2.high_area0_limit)
                    | QEOV2_WAVE_MODE_WAVE2_LOW_AREA1_LIMIT_SET(config->wave2.low_area1_limit)
                    | QEOV2_WAVE_MODE_WAVE2_LOW_AREA0_LIMIT_SET(config->wave2.low_area0_limit)
                    | QEOV2_WAVE_MODE_WAVE2_BELOW_MIN_LIMIT_SET(config->wave2.below_min_limit)

                    | QEOV2_WAVE_MODE_WAVE1_ABOVE_MAX_LIMIT_SET(config->wave1.above_max_limit)
                    | QEOV2_WAVE_MODE_WAVE1_HIGH_AREA1_LIMIT_SET(config->wave1.high_area1_limit)
                    | QEOV2_WAVE_MODE_WAVE1_HIGH_AREA0_LIMIT_SET(config->wave1.high_area0_limit)
                    | QEOV2_WAVE_MODE_WAVE1_LOW_AREA1_LIMIT_SET(config->wave1.low_area1_limit)
                    | QEOV2_WAVE_MODE_WAVE1_LOW_AREA0_LIMIT_SET(config->wave1.low_area0_limit)
                    | QEOV2_WAVE_MODE_WAVE1_BELOW_MIN_LIMIT_SET(config->wave1.below_min_limit)

                    | QEOV2_WAVE_MODE_WAVE0_ABOVE_MAX_LIMIT_SET(config->wave0.above_max_limit)
                    | QEOV2_WAVE_MODE_WAVE0_HIGH_AREA1_LIMIT_SET(config->wave0.high_area1_limit)
                    | QEOV2_WAVE_MODE_WAVE0_HIGH_AREA0_LIMIT_SET(config->wave0.high_area0_limit)
                    | QEOV2_WAVE_MODE_WAVE0_LOW_AREA1_LIMIT_SET(config->wave0.low_area1_limit)
                    | QEOV2_WAVE_MODE_WAVE0_LOW_AREA0_LIMIT_SET(config->wave0.low_area0_limit)
                    | QEOV2_WAVE_MODE_WAVE0_BELOW_MIN_LIMIT_SET(config->wave0.below_min_limit)
                    | QEOV2_WAVE_MODE_SADDLE_TYPE_SET(config->saddle_type)
                    | QEOV2_WAVE_MODE_WAVES_OUTPUT_TYPE_SET(config->wave_type)
                    | QEOV2_WAVE_MODE_ENABLE_DQ_VALID_SET(config->dq_valid_trig_enable)
                    | QEOV2_WAVE_MODE_ENABLE_POS_VALID_SET(config->pos_valid_trig_enable)
                    | QEOV2_WAVE_MODE_EN_WAVE_VD_VQ_INJECT_SET(config->vd_vq_inject_enable)
                    | QEOV2_WAVE_MODE_VD_VQ_SEL_SET(config->vd_vq_from_sw);
}

void qeo_abz_get_default_mode_config(QEOV2_Type *base, qeo_abz_mode_t *config)
{
    (void)base;

    config->a_inv_pol = false;
    config->b_inv_pol = false;
    config->z_inv_pol = false;
    config->enable_wdog = false;
    config->sync_step_position = true;
    config->reverse_align_clk_falling_edge = false;
    config->output_type = qeo_abz_output_abz;
}

void qeo_abz_config_mode(QEOV2_Type *base, qeo_abz_mode_t *config)
{
    base->ABZ.MODE &= ~(QEOV2_ABZ_MODE_Z_POLARITY_MASK
                        | QEOV2_ABZ_MODE_B_POLARITY_MASK
                        | QEOV2_ABZ_MODE_A_POLARITY_MASK
                        | QEOV2_ABZ_MODE_Z_TYPE_MASK
                        | QEOV2_ABZ_MODE_B_TYPE_MASK
                        | QEOV2_ABZ_MODE_A_TYPE_MASK
                        | QEOV2_ABZ_MODE_REVERSE_EDGE_TYPE_MASK
                        | QEOV2_ABZ_MODE_POSITION_SYNC_MODE_MASK
                        | QEOV2_ABZ_MODE_EN_WDOG_MASK);

    base->ABZ.MODE = QEOV2_ABZ_MODE_Z_POLARITY_SET(config->z_inv_pol)
                    | QEOV2_ABZ_MODE_B_POLARITY_SET(config->b_inv_pol)
                    | QEOV2_ABZ_MODE_A_POLARITY_SET(config->a_inv_pol)
                    | QEOV2_ABZ_MODE_REVERSE_EDGE_TYPE_SET(config->reverse_align_clk_falling_edge)
                    | QEOV2_ABZ_MODE_POSITION_SYNC_MODE_SET(config->sync_step_position)
                    | QEOV2_ABZ_MODE_EN_WDOG_SET(config->enable_wdog)
                    | QEOV2_ABZ_MODE_B_TYPE_SET(config->output_type)
                    | QEOV2_ABZ_MODE_A_TYPE_SET(config->output_type);

    if ((config->output_type == qeo_abz_output_pulse_revise) || (config->output_type == qeo_abz_output_up_down)) {
        base->ABZ.MODE |= QEOV2_ABZ_MODE_Z_TYPE_SET(qeo_z_as_no_output_signal);
    } else if (config->output_type == qeo_abz_output_three_phase) {
        base->ABZ.MODE |= QEOV2_ABZ_MODE_Z_TYPE_SET(qeo_z_as_third_phase_signal);
    } else {
        base->ABZ.MODE |= QEOV2_ABZ_MODE_Z_TYPE_SET(qeo_z_as_zero_signal_mode0);
    }
}

void qeo_abz_get_default_z_output_mode(QEOV2_Type *base, qeo_z_output_mode_t *mode)
{
    (void)base;

    /* z output width 1/4 ab period */
    mode->type = qeo_z_as_zero_signal_mode0;
    mode->start_line = 0;
    mode->end_line = 0;
    mode->start_step = 0;
    mode->end_step = 0;
    mode->width = 0; /* used for qeo_z_as_zero_signal_mode1 */
}

void qeo_abz_config_z_output_mode(QEOV2_Type *base, qeo_z_output_mode_t *mode)
{
    if (mode->type == qeo_z_as_zero_signal_mode0) {
        base->ABZ.Z_START = mode->start_line;
        base->ABZ.Z_END = mode->end_line;
        base->ABZ.Z_OFFSET = QEOV2_ABZ_Z_OFFSET_Z_START_OFFSET_SET(mode->start_step) | QEOV2_ABZ_Z_OFFSET_Z_END_OFFSET_SET(mode->end_step);
    } else if (mode->type == qeo_z_as_zero_signal_mode1) {
        base->ABZ.Z_START = mode->start_line;
        base->ABZ.Z_PULSE_WIDTH = mode->width;
    }

    base->ABZ.MODE = (base->ABZ.MODE & ~QEOV2_ABZ_MODE_Z_TYPE_MASK) | QEOV2_ABZ_MODE_Z_TYPE_SET(mode->type);
}

hpm_stat_t qeo_abz_set_max_frequency(QEOV2_Type *base, uint32_t src_freq, uint32_t freq)
{
    uint32_t count;

    if ((freq > 0xffffffffU / 4U) || ((src_freq % (freq * 4U)) != 0)) {
        return status_invalid_argument;
    }
    count = src_freq / (freq * 4U);
    base->ABZ.LINE_WIDTH = QEOV2_ABZ_LINE_WIDTH_LINE_SET(count);

    return status_success;
}

hpm_stat_t qeo_abz_set_wdog_frequency(QEOV2_Type *base, uint32_t src_freq, uint32_t freq)
{
    uint32_t count;

    if ((src_freq % freq) != 0) {
        return status_invalid_argument;
    }
    count = src_freq / freq;
    base->ABZ.WDOG_WIDTH = QEOV2_ABZ_WDOG_WIDTH_WIDTH_SET(count);
    base->ABZ.MODE |= QEOV2_ABZ_MODE_EN_WDOG_MASK;

    return status_success;
}

void qeo_pwm_get_default_safety_table_config(QEOV2_Type *base, qeo_pwm_safety_output_table_t *table)
{
    (void)base;

    table->pwm7_output = qeo_pwm_safety_output_highz;
    table->pwm6_output = qeo_pwm_safety_output_highz;
    table->pwm5_output = qeo_pwm_safety_output_highz;
    table->pwm4_output = qeo_pwm_safety_output_highz;
    table->pwm3_output = qeo_pwm_safety_output_highz;
    table->pwm2_output = qeo_pwm_safety_output_highz;
    table->pwm1_output = qeo_pwm_safety_output_highz;
    table->pwm0_output = qeo_pwm_safety_output_highz;
}

void qeo_pwm_get_default_phase_table_config(QEOV2_Type *base, qeo_pwm_phase_output_table_t *table)
{
    (void)base;

    table->pwm7_output = qeo_pwm_output_force_0;
    table->pwm6_output = qeo_pwm_output_force_0;
    table->pwm5_output = qeo_pwm_output_force_0;
    table->pwm4_output = qeo_pwm_output_force_0;
    table->pwm3_output = qeo_pwm_output_force_0;
    table->pwm2_output = qeo_pwm_output_force_0;
    table->pwm1_output = qeo_pwm_output_force_0;
    table->pwm0_output = qeo_pwm_output_force_0;
}

void qeo_pwm_get_default_mode_config(QEOV2_Type *base, qeo_pwm_mode_t *config)
{
    (void)base;

    config->phase_num = 4;
    config->shield_hardware_trig_safety = false;
    config->revise_pairs_output = false;
}

void qeo_pwm_config_mode(QEOV2_Type *base, qeo_pwm_mode_t *config)
{
    base->PWM.MODE &= ~(QEOV2_PWM_MODE_PWM_SAFETY_BYPASS_MASK
                        | QEOV2_PWM_MODE_REVISE_UP_DN_MASK
                        | QEOV2_PWM_MODE_PHASE_NUM_MASK);
    base->PWM.MODE |= QEOV2_PWM_MODE_PWM_SAFETY_BYPASS_SET(config->shield_hardware_trig_safety)
                    | QEOV2_PWM_MODE_REVISE_UP_DN_SET(config->revise_pairs_output)
                    | QEOV2_PWM_MODE_PHASE_NUM_SET(config->phase_num);
}

void qeo_pwm_config_phase_table(QEOV2_Type *base, uint8_t index, qeo_pwm_phase_output_table_t *table)
{
    base->PWM.PHASE_TABLE[index] = QEOV2_PWM_PHASE_TABLE_PWM7_SET(table->pwm7_output)
                                | QEOV2_PWM_PHASE_TABLE_PWM6_SET(table->pwm6_output)
                                | QEOV2_PWM_PHASE_TABLE_PWM5_SET(table->pwm5_output)
                                | QEOV2_PWM_PHASE_TABLE_PWM4_SET(table->pwm4_output)
                                | QEOV2_PWM_PHASE_TABLE_PWM3_SET(table->pwm3_output)
                                | QEOV2_PWM_PHASE_TABLE_PWM2_SET(table->pwm2_output)
                                | QEOV2_PWM_PHASE_TABLE_PWM1_SET(table->pwm1_output)
                                | QEOV2_PWM_PHASE_TABLE_PWM0_SET(table->pwm0_output);
}

void qeo_pwm_config_safety_table(QEOV2_Type *base, qeo_pwm_safety_output_table_t *table)
{
    /*< clear safety table */
    base->PWM.MODE &= ~(QEOV2_PWM_MODE_PWM7_SAFETY_MASK
                    | QEOV2_PWM_MODE_PWM6_SAFETY_MASK
                    | QEOV2_PWM_MODE_PWM5_SAFETY_MASK
                    | QEOV2_PWM_MODE_PWM4_SAFETY_MASK
                    | QEOV2_PWM_MODE_PWM3_SAFETY_MASK
                    | QEOV2_PWM_MODE_PWM2_SAFETY_MASK
                    | QEOV2_PWM_MODE_PWM1_SAFETY_MASK
                    | QEOV2_PWM_MODE_PWM0_SAFETY_MASK);
    /*< set safety table */
    base->PWM.MODE |= QEOV2_PWM_MODE_PWM7_SAFETY_SET(table->pwm7_output)
                    | QEOV2_PWM_MODE_PWM6_SAFETY_SET(table->pwm6_output)
                    | QEOV2_PWM_MODE_PWM5_SAFETY_SET(table->pwm5_output)
                    | QEOV2_PWM_MODE_PWM4_SAFETY_SET(table->pwm4_output)
                    | QEOV2_PWM_MODE_PWM3_SAFETY_SET(table->pwm3_output)
                    | QEOV2_PWM_MODE_PWM2_SAFETY_SET(table->pwm2_output)
                    | QEOV2_PWM_MODE_PWM1_SAFETY_SET(table->pwm1_output)
                    | QEOV2_PWM_MODE_PWM0_SAFETY_SET(table->pwm0_output);
}
