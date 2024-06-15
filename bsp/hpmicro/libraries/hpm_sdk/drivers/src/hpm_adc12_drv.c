/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_adc12_drv.h"
#include "hpm_soc_feature.h"

void adc12_get_default_config(adc12_config_t *config)
{
    config->res                = adc12_res_12_bits;
    config->conv_mode          = adc12_conv_mode_oneshot;
    config->adc_clk_div        = adc12_clock_divider_1;
    config->wait_dis           = true;
    config->sel_sync_ahb       = true;
    config->adc_ahb_en         = false;
}

void adc12_get_channel_default_config(adc12_channel_config_t *config)
{
    config->ch                 = 0;
    config->diff_sel           = adc12_sample_signal_single_ended;
    config->sample_cycle       = 10;
    config->sample_cycle_shift = 0;
    config->thshdh             = 0xfff;
    config->thshdl             = 0x000;
    config->wdog_int_en        = false;
}

static hpm_stat_t adc12_do_calibration(ADC12_Type *ptr, adc12_sample_signal_t diff_sel)
{
    uint8_t cal_out;
    uint32_t loop_cnt = ADC12_SOC_CALIBRATION_WAITING_LOOP_CNT;

    if (ADC12_IS_SIGNAL_TYPE_INVALID(diff_sel)) {
        return status_invalid_argument;
    }

    /*Set diff_sel temporarily */
    ptr->SAMPLE_CFG[0] &= ~ADC12_SAMPLE_CFG_DIFF_SEL_MASK;
    ptr->SAMPLE_CFG[0] |= ADC12_SAMPLE_CFG_DIFF_SEL_SET(diff_sel);

    /* Set resetcal and resetadc */
    ptr->ANA_CTRL0 |= ADC12_ANA_CTRL0_RESETCAL_MASK | ADC12_ANA_CTRL0_RESETADC_MASK;

    /* Clear resetcal and resetadc */
    ptr->ANA_CTRL0 &= ~(ADC12_ANA_CTRL0_RESETCAL_MASK | ADC12_ANA_CTRL0_RESETADC_MASK);

    /* Set startcal */
    ptr->ANA_CTRL0 |= ADC12_ANA_CTRL0_STARTCAL_MASK;

    /* Clear startcal */
    ptr->ANA_CTRL0 &= ~ADC12_ANA_CTRL0_STARTCAL_MASK;

    /* Set HW rearm_en */
    ptr->ANA_CTRL0 |= ADC12_ANA_CTRL0_REARM_EN_MASK;

    /* Polling calibration status */
    while (ADC12_ANA_STATUS_CALON_GET(ptr->ANA_STATUS) && loop_cnt--) {
        /* TODO: Call a common delay function */
    }

    /* Check if the calibration is timeout */
    if (loop_cnt == 0) {
        return status_timeout;
    }

    /* Read calculation result */
    cal_out = ADC12_ANA_STATUS_CAL_OUT_GET(ptr->ANA_STATUS);

    /* Update cal_out */
    if (diff_sel == adc12_sample_signal_single_ended) {
        ptr->ANA_CTRL0 = (ptr->ANA_CTRL0 & ~ADC12_ANA_CTRL0_CAL_VAL_SE_MASK)
                       | ADC12_ANA_CTRL0_CAL_VAL_SE_SET(cal_out);
    } else {
        ptr->ANA_CTRL0 = (ptr->ANA_CTRL0 & ~ADC12_ANA_CTRL0_CAL_VAL_DIFF_MASK)
                       | ADC12_ANA_CTRL0_CAL_VAL_DIFF_SET(cal_out);
    }

    return status_success;
}

hpm_stat_t adc12_deinit(ADC12_Type *ptr)
{
    /* disable all interrupts */
    ptr->INT_EN = 0;

    return status_success;
}

hpm_stat_t adc12_init(ADC12_Type *ptr, adc12_config_t *config)
{
    uint32_t adc_clk_div;

    /**
     * disable adc
     * When the adc is processing data, it will generate an error to initialize the adc again,
     * so you need to shut down the adc before initializing it.
     */

    ptr->ANA_CTRL0 &= ~(ADC12_ANA_CTRL0_ENADC_MASK);

    /* Check the resolution */
    if (config->res > adc12_res_12_bits) {
        return status_invalid_argument;
    }

    /* Set resolution */
    ptr->ANA_CTRL1 = (ptr->ANA_CTRL1 & ~ADC12_ANA_CTRL1_SELRES_MASK)
                   | ADC12_ANA_CTRL1_SELRES_SET(config->res);

    /* Set convert clock number and clock period */
    if ((config->adc_clk_div - 1) > ADC12_CONV_CFG1_CLOCK_DIVIDER_MASK)  {
        return status_invalid_argument;
    }

    /* Set ADC minimum conversion cycle and ADC clock divider */
    ptr->CONV_CFG1 = ADC12_CONV_CFG1_CONVERT_CLOCK_NUMBER_SET(2 * config->res + 7)
                   | ADC12_CONV_CFG1_CLOCK_DIVIDER_SET(config->adc_clk_div - 1);

    /* Set ADC Config0 */
    ptr->ADC_CFG0 = ADC12_ADC_CFG0_SEL_SYNC_AHB_SET(config->sel_sync_ahb)
                  | ADC12_ADC_CFG0_ADC_AHB_EN_SET(config->adc_ahb_en);

    /* Set wait_dis */
    ptr->BUF_CFG0 = ADC12_BUF_CFG0_WAIT_DIS_SET(config->wait_dis);

    /*-------------------------------------------------------------------------------
     *                                 Calibration
     *------------------------------------------------------------------------------
     */
    /* Set enldo */
    ptr->ANA_CTRL0 |= ADC12_ANA_CTRL0_ENLDO_MASK;

    /* TODO: wait 20us after setting enlado for adc0~adc2 */

    adc_clk_div = config->adc_clk_div;

    if (adc_clk_div == ADC12_SOC_CLOCK_CLK_DIV) {
        ptr->CONV_CFG1 = (ptr->CONV_CFG1 & ~ADC12_CONV_CFG1_CLOCK_DIVIDER_MASK)
                         | ADC12_CONV_CFG1_CLOCK_DIVIDER_SET(config->adc_clk_div + 1);
    }

    /* Set enadc */
    ptr->ANA_CTRL0 |= ADC12_ANA_CTRL0_ENADC_MASK;

    /* Do a calibration for single-ended mode */
    adc12_do_calibration(ptr, adc12_sample_signal_single_ended);

    /* Do a calibration for differential mode */
    adc12_do_calibration(ptr, adc12_sample_signal_differential);

    /* Set ADC clock divider */
    if (adc_clk_div == ADC12_SOC_CLOCK_CLK_DIV) {
        ptr->CONV_CFG1 = (ptr->CONV_CFG1 & ~ADC12_CONV_CFG1_CLOCK_DIVIDER_MASK)
                       | ADC12_CONV_CFG1_CLOCK_DIVIDER_SET(config->adc_clk_div);
    }

    /*-------------------------------------------------------------------------------
     *                                 End of calibration
     *------------------------------------------------------------------------------
     */

    return status_success;
}

hpm_stat_t adc12_init_channel(ADC12_Type *ptr, adc12_channel_config_t *config)
{
    /* Check the specified channel number */
    if (ADC12_IS_CHANNEL_INVALID(config->ch)) {
        return status_invalid_argument;
    }

    /* Check sample cycle */
    if (ADC12_IS_CHANNEL_SAMPLE_CYCLE_INVALID(config->sample_cycle)) {
        return status_invalid_argument;
    }

    /* Set warning threshold */
    ptr->PRD_CFG[config->ch].PRD_THSHD_CFG = ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDH_SET(config->thshdh)
                                           | ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDL_SET(config->thshdl);

    /* Select single-ended mode or differential mode */
    /* Set ADC sample cycles multiple */
    /* Set ADC sample cycles */
    ptr->SAMPLE_CFG[config->ch] = ADC12_SAMPLE_CFG_DIFF_SEL_SET(config->diff_sel)
                                | ADC12_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_SET(config->sample_cycle_shift)
                                | ADC12_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SET(config->sample_cycle);

    /* Enable watchdog interrupt */
    if (config->wdog_int_en) {
        ptr->INT_EN |= 1 << config->ch;
    }

    return status_success;
}

hpm_stat_t adc12_get_channel_threshold(ADC12_Type *ptr, uint8_t ch, adc12_channel_threshold_t *config)
{
    /* Check the specified channel number */
    if (ADC12_IS_CHANNEL_INVALID(ch)) {
        return status_invalid_argument;
    }

    config->ch     = ch;
    config->thshdh = ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDH_GET(ptr->PRD_CFG[ch].PRD_THSHD_CFG);
    config->thshdl = ADC12_PRD_CFG_PRD_THSHD_CFG_THSHDL_GET(ptr->PRD_CFG[ch].PRD_THSHD_CFG);

    return status_success;
}

hpm_stat_t adc12_init_seq_dma(ADC12_Type *ptr, adc12_dma_config_t *dma_config)
{
    /* Check the DMA buffer length  */
    if (ADC12_IS_SEQ_DMA_BUFF_LEN_INVLAID(dma_config->buff_len_in_4bytes)) {
        return status_invalid_argument;
    }

    /* Reset ADC DMA  */
    ptr->SEQ_DMA_CFG |= ADC12_SEQ_DMA_CFG_DMA_RST_MASK;

    /* Reset memory to clear all of cycle bits */
    memset(dma_config->start_addr, 0x00, dma_config->buff_len_in_4bytes * sizeof(uint32_t));

    /* De-reset ADC DMA */
    ptr->SEQ_DMA_CFG &= ~ADC12_SEQ_DMA_CFG_DMA_RST_MASK;

    /* Set ADC DMA target address which should be 4-byte aligned */
    ptr->SEQ_DMA_ADDR = (uint32_t)dma_config->start_addr & ADC12_SEQ_DMA_ADDR_TAR_ADDR_MASK;

    /* Set ADC DMA memory dword length */
    ptr->SEQ_DMA_CFG = (ptr->SEQ_DMA_CFG & ~ADC12_SEQ_DMA_CFG_BUF_LEN_MASK)
                     | ADC12_SEQ_DMA_CFG_BUF_LEN_SET(dma_config->buff_len_in_4bytes - 1);

    /* Set stop_en and stop_pos */
    if (dma_config->stop_en) {
        ptr->SEQ_DMA_CFG = (ptr->SEQ_DMA_CFG & ~ADC12_SEQ_DMA_CFG_STOP_POS_MASK)
                         | ADC12_SEQ_DMA_CFG_STOP_EN_MASK
                         | ADC12_SEQ_DMA_CFG_STOP_POS_SET(dma_config->stop_pos);
    }

    return status_success;
}

hpm_stat_t adc12_set_prd_config(ADC12_Type *ptr, adc12_prd_config_t *config)
{
    /* Check the specified channel number */
    if (ADC12_IS_CHANNEL_INVALID(config->ch)) {
        return status_invalid_argument;
    }

    /* Check the prescale */
    if (config->prescale > (ADC12_PRD_CFG_PRD_CFG_PRESCALE_MASK >> ADC12_PRD_CFG_PRD_CFG_PRESCALE_SHIFT)) {
        return status_invalid_argument;
    }

    /* Set periodic prescale */
    ptr->PRD_CFG[config->ch].PRD_CFG = (ptr->PRD_CFG[config->ch].PRD_CFG & ~ADC12_PRD_CFG_PRD_CFG_PRESCALE_MASK)
                                     | ADC12_PRD_CFG_PRD_CFG_PRESCALE_SET(config->prescale);

    /* Set period count */
    ptr->PRD_CFG[config->ch].PRD_CFG = (ptr->PRD_CFG[config->ch].PRD_CFG & ~ADC12_PRD_CFG_PRD_CFG_PRD_MASK)
                                     | ADC12_PRD_CFG_PRD_CFG_PRD_SET(config->period_count);

    return status_success;
}

hpm_stat_t adc12_trigger_seq_by_sw(ADC12_Type *ptr)
{
    if (ADC12_INT_STS_SEQ_SW_CFLCT_GET(ptr->INT_STS)) {
        return status_fail;
    }
    ptr->SEQ_CFG0 |= ADC12_SEQ_CFG0_SW_TRIG_MASK;

    return status_success;
}

/* Note: the sequence length can not be larger or equal than 2 in HPM6750EVK Revision A0 */
hpm_stat_t adc12_set_seq_config(ADC12_Type *ptr, adc12_seq_config_t *config)
{
    /* Check sequence length */
    if (ADC12_IS_SEQ_LEN_INVLAID(config->seq_len)) {
        return status_invalid_argument;
    }

    ptr->SEQ_CFG0 = ADC12_SEQ_CFG0_SEQ_LEN_SET(config->seq_len - 1)
                  | ADC12_SEQ_CFG0_RESTART_EN_SET(config->restart_en)
                  | ADC12_SEQ_CFG0_CONT_EN_SET(config->cont_en)
                  | ADC12_SEQ_CFG0_SW_TRIG_EN_SET(config->sw_trig_en)
                  | ADC12_SEQ_CFG0_HW_TRIG_EN_SET(config->hw_trig_en);

    /* Set sequence queue */
    for (int i = 0; i < config->seq_len; i++) {
        /* Check the specified channel number */
        if (ADC12_IS_CHANNEL_INVALID(config->queue[i].ch)) {
            return status_invalid_argument;
        }

        ptr->SEQ_QUE[i] = ADC12_SEQ_QUE_SEQ_INT_EN_SET(config->queue[i].seq_int_en)
                        | ADC12_SEQ_QUE_CHAN_NUM_4_0_SET(config->queue[i].ch);
    }

    return status_success;
}

hpm_stat_t adc12_trigger_pmt_by_sw(ADC12_Type *ptr, uint8_t trig_ch)
{
    ptr->TRG_SW_STA = ADC12_TRG_SW_STA_TRG_SW_STA_MASK | ADC12_TRG_SW_STA_TRIG_SW_INDEX_SET(trig_ch);

    return status_success;
}

hpm_stat_t adc12_set_pmt_config(ADC12_Type *ptr, adc12_pmt_config_t *config)
{
    uint32_t temp = 0;

    /* Check the specified trigger length */
    if (ADC12_IS_TRIG_LEN_INVLAID(config->trig_len)) {
        return status_invalid_argument;
    }

	/* Check the triggier channel */
    if (ADC12_IS_TRIG_CH_INVLAID(config->trig_ch)) {
        return status_invalid_argument;
    }

    temp |= ADC12_CONFIG_TRIG_LEN_SET(config->trig_len - 1);

    for (int i = 0; i < config->trig_len; i++) {
        if (ADC12_IS_CHANNEL_INVALID(config->adc_ch[i])) {
            return status_invalid_argument;
        }

        temp |= config->inten[i] << (ADC12_CONFIG_INTEN0_SHIFT + i * ADC_SOC_CONFIG_INTEN_CHAN_BIT_SIZE)
             |  config->adc_ch[i] << (ADC12_CONFIG_CHAN0_SHIFT + i * ADC_SOC_CONFIG_INTEN_CHAN_BIT_SIZE);
    }

    ptr->CONFIG[config->trig_ch] = temp;

    return status_success;
}

hpm_stat_t adc12_get_oneshot_result(ADC12_Type *ptr, uint8_t ch, uint16_t *result)
{
    uint32_t bus_res;

    /* Check the specified channel number */
    if (ADC12_IS_CHANNEL_INVALID(ch)) {
        return status_invalid_argument;
    }

    bus_res = ptr->BUS_RESULT[ch];
    *result = ADC12_BUS_RESULT_CHAN_RESULT_GET(bus_res);

    if (ADC12_BUF_CFG0_WAIT_DIS_GET(ptr->BUF_CFG0)) {
        if (!ADC12_BUS_RESULT_VALID_GET(bus_res)) {
            return status_fail;
        }
    }

    return status_success;
}

hpm_stat_t adc12_get_prd_result(ADC12_Type *ptr, uint8_t ch, uint16_t *result)
{
    /* Check the specified channel number */
    if (ADC12_IS_CHANNEL_INVALID(ch)) {
        return status_invalid_argument;
    }

    *result = ADC12_PRD_CFG_PRD_RESULT_CHAN_RESULT_GET(ptr->PRD_CFG[ch].PRD_RESULT);

    return status_success;
}
