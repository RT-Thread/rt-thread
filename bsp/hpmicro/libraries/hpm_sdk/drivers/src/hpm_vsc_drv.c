/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_vsc_drv.h"

void vsc_get_default_config(VSC_Type *vsc, vsc_config_t *config)
{
    (void)vsc;

    config->phase_mode = vsc_abc_phase;
    config->a_adc_config.adc_sel = vsc_sel_adc0;
    config->b_adc_config.adc_sel = vsc_sel_adc1;
    config->c_adc_config.adc_sel = vsc_sel_adc2;
    config->a_adc_config.adc_chn = 0;
    config->b_adc_config.adc_chn = 0;
    config->c_adc_config.adc_chn = 0;
    config->a_adc_config.adc_offset = 0x80000000;
    config->b_adc_config.adc_offset = 0x80000000;
    config->c_adc_config.adc_offset = 0x80000000;

    config->a_data_cnt = 1;
    config->a_data_opr_config.opr_0 = vsc_data_opr_plus_mul_1;
    config->a_data_opr_config.opr_1 = vsc_data_opr_plus_mul_1;
    config->a_data_opr_config.opr_2 = vsc_data_opr_plus_mul_1;
    config->a_data_opr_config.opr_3 = vsc_data_opr_plus_mul_1;
    config->b_data_cnt = 1;
    config->b_data_opr_config.opr_0 = vsc_data_opr_plus_mul_1;
    config->b_data_opr_config.opr_1 = vsc_data_opr_plus_mul_1;
    config->b_data_opr_config.opr_2 = vsc_data_opr_plus_mul_1;
    config->b_data_opr_config.opr_3 = vsc_data_opr_plus_mul_1;
    config->c_data_cnt = 1;
    config->c_data_opr_config.opr_0 = vsc_data_opr_plus_mul_1;
    config->c_data_opr_config.opr_1 = vsc_data_opr_plus_mul_1;
    config->c_data_opr_config.opr_2 = vsc_data_opr_plus_mul_1;
    config->c_data_opr_config.opr_3 = vsc_data_opr_plus_mul_1;

    config->pos_cap_mode = vsc_pos_use_last_data_when_adc_sample_finish;
    config->pole_pairs = 1;
}

void vsc_config_init(VSC_Type *vsc, vsc_config_t *config)
{
    vsc->ABC_MODE = VSC_ABC_MODE_PHASE_ABSENT_MODE_SET(config->phase_mode)
                  | VSC_ABC_MODE_VALUE_C_WIDTH_SET(config->c_data_cnt)
                  | VSC_ABC_MODE_VALUE_B_WIDTH_SET(config->b_data_cnt)
                  | VSC_ABC_MODE_VALUE_A_WIDTH_SET(config->a_data_cnt)
                  | VSC_ABC_MODE_VALUE_C_LOC_SET(config->c_adc_config.adc_sel)
                  | VSC_ABC_MODE_VALUE_B_LOC_SET(config->b_adc_config.adc_sel)
                  | VSC_ABC_MODE_VALUE_A_LOC_SET(config->a_adc_config.adc_sel);

    vsc->ADC_CHAN_ASSIGN = VSC_ADC_CHAN_ASSIGN_VALUE_C_CHAN_SET(config->c_adc_config.adc_chn)
                         | VSC_ADC_CHAN_ASSIGN_VALUE_B_CHAN_SET(config->b_adc_config.adc_chn)
                         | VSC_ADC_CHAN_ASSIGN_VALUE_A_CHAN_SET(config->a_adc_config.adc_chn);

    vsc->VALUE_A_DATA_OPT = VSC_VALUE_A_DATA_OPT_OPT_3_SET(config->a_data_opr_config.opr_3)
                          | VSC_VALUE_A_DATA_OPT_OPT_2_SET(config->a_data_opr_config.opr_2)
                          | VSC_VALUE_A_DATA_OPT_OPT_1_SET(config->a_data_opr_config.opr_1)
                          | VSC_VALUE_A_DATA_OPT_OPT_0_SET(config->a_data_opr_config.opr_0);

    vsc->VALUE_B_DATA_OPT = VSC_VALUE_B_DATA_OPT_OPT_3_SET(config->b_data_opr_config.opr_3)
                          | VSC_VALUE_B_DATA_OPT_OPT_2_SET(config->b_data_opr_config.opr_2)
                          | VSC_VALUE_B_DATA_OPT_OPT_1_SET(config->b_data_opr_config.opr_1)
                          | VSC_VALUE_B_DATA_OPT_OPT_0_SET(config->b_data_opr_config.opr_0);

    vsc->VALUE_C_DATA_OPT = VSC_VALUE_C_DATA_OPT_OPT_3_SET(config->c_data_opr_config.opr_3)
                          | VSC_VALUE_C_DATA_OPT_OPT_2_SET(config->c_data_opr_config.opr_2)
                          | VSC_VALUE_C_DATA_OPT_OPT_1_SET(config->c_data_opr_config.opr_1)
                          | VSC_VALUE_C_DATA_OPT_OPT_0_SET(config->c_data_opr_config.opr_0);

    vsc->VALUE_A_OFFSET = VSC_VALUE_A_OFFSET_VALUE_A_OFFSET_SET(config->a_adc_config.adc_offset);
    vsc->VALUE_B_OFFSET = VSC_VALUE_B_OFFSET_VALUE_B_OFFSET_SET(config->b_adc_config.adc_offset);
    vsc->VALUE_C_OFFSET = VSC_VALUE_C_OFFSET_VALUE_C_OFFSET_SET(config->c_adc_config.adc_offset);

    vsc_config_pos_capture_mode(vsc, config->pos_cap_mode);
    vsc_set_pos_pole_pairs(vsc, config->pole_pairs);
}

void vsc_sw_inject_abc_value(VSC_Type *vsc, int32_t value_a, int32_t value_b, int32_t value_c)
{
    vsc->TRIGGER_SW = VSC_TRIGGER_SW_TRIGGER_SW_MASK;
    vsc->VALUE_A_SW = VSC_VALUE_A_SW_VALUE_A_SW_SET((uint32_t)value_a);
    vsc->VALUE_B_SW = VSC_VALUE_B_SW_VALUE_B_SW_SET((uint32_t)value_b);
    vsc->VALUE_C_SW = VSC_VALUE_C_SW_VALUE_C_SW_SET((uint32_t)value_c);
    vsc->VALUE_SW_READY = VSC_VALUE_SW_READY_VALUE_SW_READY_MASK;
}

void vsc_sw_inject_pos_value(VSC_Type *vsc, uint32_t pos)
{
    vsc->POSITION_SW = VSC_POSITION_SW_POSITION_SW_SET(pos);
}
