/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_sdm_drv.h"

#ifndef HPM_LIN_DRV_RETRY_COUNT
#define HPM_LIN_DRV_RETRY_COUNT (5000U)
#endif


void sdm_get_default_module_control(SDM_Type *ptr, sdm_control_t *control)
{
    control->clk_signal_sync = true;
    control->data_signal_sync = true;
    control->interrupt_en = false;
}

void sdm_init_module(SDM_Type *ptr, sdm_control_t *control)
{
    /* software reset */
    ptr->CTRL |= SDM_CTRL_SFTRST_MASK;
    ptr->CTRL &= ~SDM_CTRL_SFTRST_MASK;

    ptr->CTRL |= SDM_CTRL_SYNC_MCLK_SET(control->clk_signal_sync)
                | SDM_CTRL_SYNC_MDAT_SET(control->data_signal_sync)
                | SDM_CTRL_IE_SET(control->interrupt_en);
}

void sdm_get_channel_common_setting(SDM_Type *ptr, sdm_channel_common_config_t *config)
{
    config->sampling_mode = sdm_sampling_rising_clk_edge;
    config->enable_err_interrupt = false;
    config->enable_data_ready_interrupt = false;
}

void sdm_config_channel_common_setting(SDM_Type *ptr, uint8_t ch_index, sdm_channel_common_config_t *config)
{
    if (config->enable_err_interrupt) {
        ptr->INT_EN |= CHN_ERR_MASK(ch_index);
    }

    if (config->enable_data_ready_interrupt) {
        ptr->INT_EN |= CHN_DRY_MASK(ch_index);
    }

    ptr->CTRL &= ~CHN_SAMPLING_MODE_MASK(ch_index);
    ptr->CTRL |= config->sampling_mode << CHN_SAMPLING_MODE_SHIFT(ch_index);
}

void sdm_get_channel_default_filter_config(SDM_Type *ptr, sdm_filter_config_t *filter_config)
{
    filter_config->fifo_threshold = 8;
    filter_config->en_fifo_threshold_int = true;
    filter_config->manchester_threshold = 0;
    filter_config->wdg_threshold = 255;
    filter_config->en_af_int = 0;
    filter_config->en_data_overflow_int = 1;
    filter_config->en_cic_data_saturation_int = 1;
    filter_config->en_data_ready_int = 1;
    filter_config->sync_source = 0;
    filter_config->fifo_clean_on_sync = 0;
    filter_config->wtsynaclr = 0;
    filter_config->wtsynmclr = 0;
    filter_config->wtsyncen = 0;
    filter_config->output_32bit = 1;
    filter_config->data_ready_flag_by_fifo = 1;
    filter_config->enable = 1;

    filter_config->filter_type = sdm_filter_sinc1;
    filter_config->pwm_signal_sync = 0;
    filter_config->output_offset = 0;
    filter_config->oversampling_rate = 32; /**< 1- 256 */
    filter_config->ignore_invalid_samples = 0;
}

void sdm_get_channel_default_comparator_config(SDM_Type *ptr, sdm_comparator_config_t *cmp_config)
{
    cmp_config->high_threshold = 0xffff;
    cmp_config->zero_cross_threshold = 0xffff;
    cmp_config->low_threshold = 0x0;

    cmp_config->en_zero_cross_threshold_int = false;
    cmp_config->en_clock_invalid_int = false;
    cmp_config->en_high_threshold_int = false;
    cmp_config->en_low_threshold_int = false;
    cmp_config->filter_type = sdm_filter_sinc1;
    cmp_config->oversampling_rate = 32; /**< 1-32, when 32, write 0 into bitfield */
    cmp_config->ignore_invalid_samples = 0;
    cmp_config->enable = true;
}

void sdm_config_channel_filter(SDM_Type *ptr, uint8_t ch_index, sdm_filter_config_t *filter_config)
{
    /* fifo setting */
    ptr->CH[ch_index].SDFIFOCTRL = SDM_CH_SDFIFOCTRL_THRSH_SET(filter_config->fifo_threshold)
                                | SDM_CH_SDFIFOCTRL_D_RDY_INT_EN_SET(filter_config->en_fifo_threshold_int);

    ptr->CH[ch_index].SDCTRLE = SDM_CH_SDCTRLE_SGD_ORDR_SET(filter_config->filter_type)
                                | SDM_CH_SDCTRLE_PWMSYNC_SET(filter_config->pwm_signal_sync)
                                | SDM_CH_SDCTRLE_CIC_SCL_SET(filter_config->output_offset)
                                | SDM_CH_SDCTRLE_CIC_DEC_RATIO_SET(filter_config->oversampling_rate - 1)
                                | SDM_CH_SDCTRLE_IGN_INI_SAMPLES_SET(filter_config->ignore_invalid_samples);

    ptr->CH[ch_index].SDCTRLP = SDM_CH_SDCTRLP_MANCH_THR_SET(filter_config->manchester_threshold)
                                | SDM_CH_SDCTRLP_WDOG_THR_SET(filter_config->wdg_threshold)
                                | SDM_CH_SDCTRLP_AF_IE_SET(filter_config->en_af_int)
                                | SDM_CH_SDCTRLP_DFFOVIE_SET(filter_config->en_data_overflow_int)
                                | SDM_CH_SDCTRLP_DSATIE_SET(filter_config->en_cic_data_saturation_int)
                                | SDM_CH_SDCTRLP_DRIE_SET(filter_config->en_data_ready_int)
                                | SDM_CH_SDCTRLP_SYNCSEL_SET(filter_config->sync_source)
                                | SDM_CH_SDCTRLP_FFSYNCCLREN_SET(filter_config->fifo_clean_on_sync)
                                | SDM_CH_SDCTRLP_WTSYNACLR_SET(filter_config->wtsynaclr)
                                | SDM_CH_SDCTRLP_WTSYNMCLR_SET(filter_config->wtsynmclr)
                                | SDM_CH_SDCTRLP_WTSYNCEN_SET(filter_config->wtsyncen)
                                | SDM_CH_SDCTRLP_D32_SET(filter_config->output_32bit)
                                | SDM_CH_SDCTRLP_DR_OPT_SET(filter_config->data_ready_flag_by_fifo);

    ptr->CH[ch_index].SDCTRLP |= SDM_CH_SDCTRLP_EN_SET(filter_config->enable);
}

void sdm_config_channel_comparator(SDM_Type *ptr,  uint8_t ch_index, sdm_comparator_config_t *cmp_config)
{
    ptr->CH[ch_index].SCHTL = cmp_config->high_threshold;
    ptr->CH[ch_index].SCLLT = cmp_config->low_threshold;
    ptr->CH[ch_index].SCHTLZ = cmp_config->zero_cross_threshold;

    ptr->CH[ch_index].SCCTRL = SDM_CH_SCCTRL_HZ_EN_SET(cmp_config->en_zero_cross_threshold_int)
                                | SDM_CH_SCCTRL_MF_IE_SET(cmp_config->en_clock_invalid_int)
                                | SDM_CH_SCCTRL_HL_IE_SET(cmp_config->en_high_threshold_int)
                                | SDM_CH_SCCTRL_LL_IE_SET(cmp_config->en_low_threshold_int)
                                | SDM_CH_SCCTRL_SGD_ORDR_SET(cmp_config->filter_type)
                                | SDM_CH_SCCTRL_CIC_DEC_RATIO_SET(cmp_config->oversampling_rate)
                                | SDM_CH_SCCTRL_IGN_INI_SAMPLES_SET(cmp_config->ignore_invalid_samples);

    ptr->CH[ch_index].SCCTRL |= SDM_CH_SCCTRL_EN_SET(cmp_config->enable);
}

hpm_stat_t sdm_receive_one_filter_data(SDM_Type *ptr, uint8_t ch_index, bool using_fifo, int8_t *data, uint8_t data_len_in_bytes)
{
    uint32_t retry = 0;
    int32_t output;

    while (!sdm_get_channel_data_ready_status(ptr, ch_index)) {
        if (retry > HPM_LIN_DRV_RETRY_COUNT) {
            break;
        }
        retry++;
    }

    if (retry > HPM_LIN_DRV_RETRY_COUNT) {
        return status_timeout;
    }

    if (using_fifo) {
        output = ptr->CH[ch_index].SDFIFO;
    } else {
        output = ptr->CH[ch_index].SDATA;
    }

    for (uint8_t i = 0; i < data_len_in_bytes; i++) {
        *(data++) = (int8_t)(output >> (i * 8));
    }

    return status_success;
}

hpm_stat_t sdm_receive_filter_data(SDM_Type *ptr, uint8_t ch_index, bool using_fifo, int8_t *data, uint32_t count, uint8_t data_len_in_bytes)
{
    for (uint32_t i = 0; i < count; i++) {
        if (status_success != sdm_receive_one_filter_data(ptr, ch_index, using_fifo, data, data_len_in_bytes)) {
            return status_fail;
        }

        for (uint8_t i = 0; i < data_len_in_bytes; i++) {
            data++;
        }
    }
    return status_success;
}

