/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <assert.h>
#include "hpm_lobs_drv.h"

void lobs_deinit(LOBS_Type *lobs)
{
    lobs_set_state_enable(lobs, lobs_state_0, false);
    lobs_set_state_enable(lobs, lobs_state_1, false);
    lobs_set_state_enable(lobs, lobs_state_2, false);
    lobs_set_state_enable(lobs, lobs_state_3, false);
    lobs_set_state_enable(lobs, lobs_state_4, false);
    lobs_set_pre_trig_enable(lobs, false);
    lobs_set_enable(lobs, false);
}

void lobs_ctrl_config(LOBS_Type *lobs, lobs_ctrl_config_t *config)
{
    uint8_t burst_len;

    assert((config->start_addr & 0x03) == 0);
    assert((config->end_addr & 0x03) == 0);

    if (config->sample_rate == lobs_sample_1_per_5) {
        burst_len = lobs_burst_16;
    } else if (config->sample_rate == lobs_sample_1_per_6) {
        burst_len = lobs_burst_8;
    } else {
        burst_len = lobs_burst_4;
    }
    lobs->STREAMCTRL = LOBS_STREAMCTRL_SEL_SET(config->group_mode)
                     | LOBS_STREAMCTRL_SAMPLE_SET(config->sample_rate)
                     | LOBS_STREAMCTRL_BURST_SET(burst_len);
    lobs->STARTADDR = config->start_addr;
    lobs->ENDADDR = config->end_addr - 4u;
}

void lobs_two_group_mode_config(LOBS_Type *lobs, lobs_two_group_sel_t group, lobs_two_group_mode_config_t *config)
{
    assert(config->sig_group_num < 12);

    if (group == lobs_two_group_1) {
        lobs->GRPSELA = (lobs->GRPSELA & ~LOBS_GRPSELA_NUM1_MASK) | LOBS_GRPSELA_NUM1_SET(config->sig_group_num);
        lobs->SIGSELA1 = LOBS_SIGSELA1_NUM1_SET(config->sample_sig_bit[0]) | LOBS_SIGSELA1_NUM2_SET(config->sample_sig_bit[1])
                       | LOBS_SIGSELA1_NUM3_SET(config->sample_sig_bit[2]) | LOBS_SIGSELA1_NUM4_SET(config->sample_sig_bit[3]);
        lobs->SIGENA = (lobs->SIGENA & ~LOBS_SIGENA_EN1_MASK)
                      | LOBS_SIGENA_EN1_SET((config->sample_sig_en[0]) | (config->sample_sig_en[1] << 1)
                                          | (config->sample_sig_en[2] << 2) | (config->sample_sig_en[3] << 3));
        lobs->GRPENA = (lobs->GRPENA & ~LOBS_GRPENA_EN1_MASK) | LOBS_GRPENA_EN1_SET(config->group_enable);
    } else if (group == lobs_two_group_2) {
        lobs->GRPSELA = (lobs->GRPSELA & ~LOBS_GRPSELA_NUM2_MASK) | LOBS_GRPSELA_NUM2_SET(config->sig_group_num);
        lobs->SIGSELA2 = LOBS_SIGSELA2_NUM1_SET(config->sample_sig_bit[0]) | LOBS_SIGSELA2_NUM2_SET(config->sample_sig_bit[1])
                       | LOBS_SIGSELA2_NUM3_SET(config->sample_sig_bit[2]) | LOBS_SIGSELA2_NUM4_SET(config->sample_sig_bit[3]);
        lobs->SIGENA = (lobs->SIGENA & ~LOBS_SIGENA_EN2_MASK)
                      | LOBS_SIGENA_EN2_SET((config->sample_sig_en[0]) | (config->sample_sig_en[1] << 1)
                                          | (config->sample_sig_en[2] << 2) | (config->sample_sig_en[3] << 3));
        lobs->GRPENA = (lobs->GRPENA & ~LOBS_GRPENA_EN2_MASK) | LOBS_GRPENA_EN2_SET(config->group_enable);
    } else {
        ;
    }
}

void lobs_state_config(LOBS_Type *lobs, lobs_state_sel_t state, lobs_state_config_t *config)
{
    uint8_t cmp_reg_index;
    uint8_t cmp_bit_index;
    uint8_t sample_rate;

    assert(config->sig_group_num < 12);
    assert((config->cmp_sig_en[0] && (config->cmp_sig_bit[0] < 128)) || (!config->cmp_sig_en[0]));
    assert((config->cmp_sig_en[1] && (config->cmp_sig_bit[1] < 128)) || (!config->cmp_sig_en[1]));
    assert((config->cmp_sig_en[2] && (config->cmp_sig_bit[2] < 128)) || (!config->cmp_sig_en[2]));
    assert((config->cmp_sig_en[3] && (config->cmp_sig_bit[3] < 128)) || (!config->cmp_sig_en[3]));
    assert(((config->cmp_mode == lobs_cnt_cmp_mode) && (config->state_chg_condition == lobs_cnt_matched)) || (config->cmp_mode != lobs_cnt_cmp_mode));

    lobs->STATE[state].SIGSEL = LOBS_STATE_SIGSEL_EN_SET(1u << (config->sig_group_num));
    lobs->STATE[state].TRIGCTRL = LOBS_STATE_TRIGCTRL_TRACE_SET(2)
                                | LOBS_STATE_TRIGCTRL_COMPSEL_SET(config->cmp_mode)
                                | LOBS_STATE_TRIGCTRL_COMP_SET(config->state_chg_condition);
    lobs->STATE[state].NEXTSTATE = LOBS_STATE_NEXTSTATE_NEXTSTATE_SET(config->next_state);

    sample_rate = LOBS_STREAMCTRL_SAMPLE_GET(lobs->STREAMCTRL);
    if (sample_rate == lobs_sample_1_per_7) {
        lobs->STATE[state].COUNTCOMP = LOBS_STATE_COUNTCOMP_VALUE_SET(config->cmp_counter * 7u);
    } else if (sample_rate == lobs_sample_1_per_6) {
        lobs->STATE[state].COUNTCOMP = LOBS_STATE_COUNTCOMP_VALUE_SET(config->cmp_counter * 6u);
    } else if (sample_rate == lobs_sample_1_per_5) {
        lobs->STATE[state].COUNTCOMP = LOBS_STATE_COUNTCOMP_VALUE_SET(config->cmp_counter * 5u);
    } else {
        assert(0);
    }

    lobs->STATE[state].SIGMASK = LOBS_STATE_SIGMASK_NUM0_SET(config->cmp_sig_bit[0]) | LOBS_STATE_SIGMASK_NUM1_SET(config->cmp_sig_bit[1])
                               | LOBS_STATE_SIGMASK_NUM2_SET(config->cmp_sig_bit[2]) | LOBS_STATE_SIGMASK_NUM3_SET(config->cmp_sig_bit[3]);
    lobs->STATE[state].COMPEN = LOBS_STATE_COMPEN_EN_SET((config->cmp_sig_en[0]) | (config->cmp_sig_en[1] << 1)
                                                       | (config->cmp_sig_en[2] << 2) | (config->cmp_sig_en[3] << 3));
    lobs->STATE[state].EXTMASK = 0;
    lobs->STATE[state].EXTCOMP = 0;

    for (uint8_t i = 0; i < 4; i++) {
        if (config->cmp_sig_en[i]) {
            cmp_reg_index = config->cmp_sig_bit[i] / 32;
            cmp_bit_index = config->cmp_sig_bit[i] % 32;
            if (cmp_reg_index == 0) {
                lobs->STATE[state].SIGCOMP0 = (lobs->STATE[state].SIGCOMP0 & ~(1u << cmp_bit_index)) | (config->cmp_golden_value[i] << cmp_bit_index);
            } else if (cmp_reg_index == 1) {
                lobs->STATE[state].SIGCOMP1 = (lobs->STATE[state].SIGCOMP1 & ~(1u << cmp_bit_index)) | (config->cmp_golden_value[i] << cmp_bit_index);
            } else if (cmp_reg_index == 2) {
                lobs->STATE[state].SIGCOMP2 = (lobs->STATE[state].SIGCOMP2 & ~(1u << cmp_bit_index)) | (config->cmp_golden_value[i] << cmp_bit_index);
            } else if (cmp_reg_index == 3) {
                lobs->STATE[state].SIGCOMP3 = (lobs->STATE[state].SIGCOMP3 & ~(1u << cmp_bit_index)) | (config->cmp_golden_value[i] << cmp_bit_index);
            } else {
                ;
            }
        }
    }
}
