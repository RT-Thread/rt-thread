/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_adc16_drv.h"
#include "hpm_soc_feature.h"

void adc16_get_default_config(adc16_config_t *config)
{
    config->res                = adc16_res_16_bits;
    config->conv_mode          = adc16_conv_mode_oneshot;
    config->adc_clk_div        = adc16_clock_divider_1;
    config->wait_dis           = true;
    config->sel_sync_ahb       = true;
    config->port3_realtime     = false;
    config->adc_ahb_en         = false;
}

void adc16_get_channel_default_config(adc16_channel_config_t *config)
{
    config->ch                 = 0;
    config->sample_cycle       = 10;
    config->sample_cycle_shift = 0;
    config->thshdh             = 0xffff;
    config->thshdl             = 0x0000;
    config->wdog_int_en        = false;
}

static hpm_stat_t adc16_do_calibration(ADC16_Type *ptr)
{
    uint32_t i, j;
    uint32_t clk_div_temp;
    uint32_t adc16_params[ADC16_SOC_PARAMS_LEN];
    int32_t  param01;
    uint32_t param02;
    uint64_t param64;
    uint32_t param32;
    uint32_t temp;

    /* Get input clock divider */
    clk_div_temp = ADC16_CONV_CFG1_CLOCK_DIVIDER_GET(ptr->CONV_CFG1);

    /* Set input clock divider temporarily */
    ptr->CONV_CFG1 = (ptr->CONV_CFG1 & ~ADC16_CONV_CFG1_CLOCK_DIVIDER_MASK)
                   | ADC16_CONV_CFG1_CLOCK_DIVIDER_SET(1);

    /* Enable ADC config clock */
    ptr->ANA_CTRL0 |= ADC16_ANA_CTRL0_ADC_CLK_ON_MASK;

    for (i = 0; i < ADC16_SOC_PARAMS_LEN; i++) {
        adc16_params[i] = 0;
    }

    /* Enable reg_en */
    /* Enable bandgap_en */
    ptr->ADC16_CONFIG0 |= ADC16_ADC16_CONFIG0_REG_EN_MASK
                       |  ADC16_ADC16_CONFIG0_BANDGAP_EN_MASK;

    /* Set cal_avg_cfg for 32 loops */
    ptr->ADC16_CONFIG0 = (ptr->ADC16_CONFIG0 & ~ADC16_ADC16_CONFIG0_CAL_AVG_CFG_MASK)
                       | ADC16_ADC16_CONFIG0_CAL_AVG_CFG_SET(5);

    /* Enable ahb_en */
    ptr->ADC_CFG0 |= ADC16_ADC_CFG0_ADC_AHB_EN_MASK | (1 << 2);

    /* Disable ADC config clock */
    ptr->ANA_CTRL0 &= ~ADC16_ANA_CTRL0_ADC_CLK_ON_MASK;

    /* Recover input clock divider */
    ptr->CONV_CFG1 = (ptr->CONV_CFG1 & ~ADC16_CONV_CFG1_CLOCK_DIVIDER_MASK)
                   | ADC16_CONV_CFG1_CLOCK_DIVIDER_SET(clk_div_temp);

    for (j = 0; j < 4; j++) {
        /* Set startcal */
        ptr->ANA_CTRL0 |= ADC16_ANA_CTRL0_STARTCAL_MASK;

        /* Clear startcal */
        ptr->ANA_CTRL0 &= ~ADC16_ANA_CTRL0_STARTCAL_MASK;

        /* Polling calibration status */
        while (ADC16_ANA_STATUS_CALON_GET(ptr->ANA_STATUS)) {
        }

        /* Read parameters */
        for (i = 0; i < ADC16_SOC_PARAMS_LEN; i++) {
            adc16_params[i] += ADC16_ADC16_PARAMS_PARAM_VAL_GET(ptr->ADC16_PARAMS[i]);
        }
    }

    adc16_params[ADC16_ADC16_PARAMS_ADC16_PARA33] -= 0x800;
    param01 = adc16_params[ADC16_ADC16_PARAMS_ADC16_PARA32] - adc16_params[ADC16_ADC16_PARAMS_ADC16_PARA33];
    adc16_params[ADC16_ADC16_PARAMS_ADC16_PARA32] = adc16_params[ADC16_ADC16_PARAMS_ADC16_PARA00] -
                                                    adc16_params[ADC16_ADC16_PARAMS_ADC16_PARA33];
    adc16_params[ADC16_ADC16_PARAMS_ADC16_PARA00] = 0;

    for (i = 1; i < ADC16_SOC_PARAMS_LEN - 2; i++) {
        adc16_params[i] = adc16_params[ADC16_ADC16_PARAMS_ADC16_PARA32] + adc16_params[i] -
                          adc16_params[ADC16_ADC16_PARAMS_ADC16_PARA33] + adc16_params[i - 1];
    }

    param02 = (param01 + adc16_params[ADC16_ADC16_PARAMS_ADC16_PARA31] + adc16_params[ADC16_ADC16_PARAMS_ADC16_PARA32]) >> 6;
    param64 = 0x10000ll * param02;
    param64 = param64 / (0x20000 - param02 / 2);
    param32 = (uint32_t)param64;

    for (i = 0; i < ADC16_SOC_PARAMS_LEN; i++) {
        adc16_params[i] >>= 6;
    }

    /* Enable ADC config clock */
    ptr->ANA_CTRL0 |= ADC16_ANA_CTRL0_ADC_CLK_ON_MASK;

    ptr->CONV_CFG1 = (ptr->CONV_CFG1 & ~ADC16_CONV_CFG1_CLOCK_DIVIDER_MASK)
                   | ADC16_CONV_CFG1_CLOCK_DIVIDER_SET(1);

    /* Write parameters */
    for (i = 0; i < ADC16_SOC_PARAMS_LEN ; i++) {
        ptr->ADC16_PARAMS[i] = (uint16_t)(adc16_params[i]);
    }

    /* Set ADC16 Config0 */
    temp = ptr->ADC16_CONFIG0;

    temp &= ~(ADC16_ADC16_CONFIG0_CAL_AVG_CFG_MASK | ADC16_ADC16_CONFIG0_CONV_PARAM_MASK);

    temp |= ADC16_ADC16_CONFIG0_REG_EN_MASK
         |  ADC16_ADC16_CONFIG0_BANDGAP_EN_MASK
         |  ADC16_ADC16_CONFIG0_CAL_AVG_CFG_MASK
         |  ADC16_ADC16_CONFIG0_CONV_PARAM_SET(param32);

    ptr->ADC16_CONFIG0 = temp;

    /* Recover input clock divider */
    ptr->CONV_CFG1 = (ptr->CONV_CFG1 & ~ADC16_CONV_CFG1_CLOCK_DIVIDER_MASK)
                   | ADC16_CONV_CFG1_CLOCK_DIVIDER_SET(clk_div_temp);

    /* Disable ADC config clock */
    ptr->ANA_CTRL0 &= ~ADC16_ANA_CTRL0_ADC_CLK_ON_MASK;

    return status_success;
}

hpm_stat_t adc16_deinit(ADC16_Type *ptr)
{
    /* disable all interrupts */
    ptr->INT_EN = 0;

    return status_success;
}

hpm_stat_t adc16_init(ADC16_Type *ptr, adc16_config_t *config)
{
    uint32_t clk_div_temp;

    /* Set convert clock number and clock period */
    if (config->adc_clk_div - 1 > ADC16_CONV_CFG1_CLOCK_DIVIDER_MASK)  {
        return status_invalid_argument;
    }

    /* Set ADC minimum conversion cycle and ADC clock divider */
    ptr->CONV_CFG1 = ADC16_CONV_CFG1_CONVERT_CLOCK_NUMBER_SET(config->res)
                   | ADC16_CONV_CFG1_CLOCK_DIVIDER_SET(config->adc_clk_div - 1);

    /* Set ahb_en */
    /* Set the duration of the conversion */
    ptr->ADC_CFG0 = ADC16_ADC_CFG0_SEL_SYNC_AHB_SET(config->sel_sync_ahb)
                  | ADC16_ADC_CFG0_ADC_AHB_EN_SET(config->adc_ahb_en)
                  | ADC16_ADC_CFG0_PORT3_REALTIME_SET(config->port3_realtime);

    /* Set wait_dis */
    ptr->BUF_CFG0 = ADC16_BUF_CFG0_WAIT_DIS_SET(config->wait_dis);

    /* Get input clock divider */
    clk_div_temp = ADC16_CONV_CFG1_CLOCK_DIVIDER_GET(ptr->CONV_CFG1);

    /* Set input clock divider temporarily */
    ptr->CONV_CFG1 = (ptr->CONV_CFG1 & ~ADC16_CONV_CFG1_CLOCK_DIVIDER_MASK)
                   | ADC16_CONV_CFG1_CLOCK_DIVIDER_SET(1);

    /* Enable ADC config clock */
    ptr->ANA_CTRL0 |= ADC16_ANA_CTRL0_ADC_CLK_ON_MASK;

    /* Set end count */
    ptr->ADC16_CONFIG1 &= ~ADC16_ADC16_CONFIG1_COV_END_CNT_MASK;
    ptr->ADC16_CONFIG1 |= ADC16_ADC16_CONFIG1_COV_END_CNT_SET(ADC16_SOC_MAX_CONV_CLK_NUM - config->res + 1);

    /* Disable ADC config clock */
    ptr->ANA_CTRL0 &= ~ADC16_ANA_CTRL0_ADC_CLK_ON_MASK;

    /* Recover input clock divider */
    ptr->CONV_CFG1 = (ptr->CONV_CFG1 & ~ADC16_CONV_CFG1_CLOCK_DIVIDER_MASK)
                   | ADC16_CONV_CFG1_CLOCK_DIVIDER_SET(clk_div_temp);

    /* Do a calibration */
    adc16_do_calibration(ptr);

    return status_success;
}

hpm_stat_t adc16_init_channel(ADC16_Type *ptr, adc16_channel_config_t *config)
{
    /* Check the specified channel number */
    if (ADC16_IS_CHANNEL_INVALID(config->ch)) {
        return status_invalid_argument;
    }

    /* Check sample cycle */
    if (ADC16_IS_CHANNEL_SAMPLE_CYCLE_INVALID(config->sample_cycle)) {
        return status_invalid_argument;
    }

    /* Set warning threshold */
    ptr->PRD_CFG[config->ch].PRD_THSHD_CFG = ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDH_SET(config->thshdh)
                                           | ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDL_SET(config->thshdl);

    /* Set ADC sample cycles multiple */
    /* Set ADC sample cycles */
    ptr->SAMPLE_CFG[config->ch] = ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SHIFT_SET(config->sample_cycle_shift)
                                | ADC16_SAMPLE_CFG_SAMPLE_CLOCK_NUMBER_SET(config->sample_cycle);

    /* Enable watchdog interrupt */
    if (config->wdog_int_en) {
        ptr->INT_EN |= 1 << config->ch;
    }

    return status_success;
}

hpm_stat_t adc16_get_channel_threshold(ADC16_Type *ptr, uint8_t ch, adc16_channel_threshold_t *config)
{
    /* Check the specified channel number */
    if (ADC16_IS_CHANNEL_INVALID(ch)) {
        return status_invalid_argument;
    }

    config->ch     = ch;
    config->thshdh = ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDH_GET(ptr->PRD_CFG[ch].PRD_THSHD_CFG);
    config->thshdl = ADC16_PRD_CFG_PRD_THSHD_CFG_THSHDL_GET(ptr->PRD_CFG[ch].PRD_THSHD_CFG);

    return status_success;
}

#if defined(ADC_SOC_BUSMODE_ENABLE_CTRL_SUPPORT) && ADC_SOC_BUSMODE_ENABLE_CTRL_SUPPORT
void adc16_enable_oneshot_mode(ADC16_Type *ptr)
{
    ptr->BUF_CFG0 |= ADC16_BUF_CFG0_BUS_MODE_EN_MASK;
}

void adc16_disable_oneshot_mode(ADC16_Type *ptr)
{
    ptr->BUF_CFG0 &= ~ADC16_BUF_CFG0_BUS_MODE_EN_MASK;
}
#endif

hpm_stat_t adc16_init_seq_dma(ADC16_Type *ptr, adc16_dma_config_t *dma_config)
{
     /* Check the DMA buffer length  */
    if (ADC16_IS_SEQ_DMA_BUFF_LEN_INVLAID(dma_config->buff_len_in_4bytes)) {
        return status_invalid_argument;
    }

    /* Reset ADC DMA  */
    ptr->SEQ_DMA_CFG |= ADC16_SEQ_DMA_CFG_DMA_RST_MASK;

    /* Reset memory to clear all of cycle bits */
    memset(dma_config->start_addr, 0x00, dma_config->buff_len_in_4bytes * sizeof(uint32_t));

    /* De-reset ADC DMA */
    ptr->SEQ_DMA_CFG &= ~ADC16_SEQ_DMA_CFG_DMA_RST_MASK;

    /* Set ADC DMA target address which should be 4-byte aligned */
    ptr->SEQ_DMA_ADDR = (uint32_t)dma_config->start_addr & ADC16_SEQ_DMA_ADDR_TAR_ADDR_MASK;

    /* Set ADC DMA memory dword length */
    ptr->SEQ_DMA_CFG = (ptr->SEQ_DMA_CFG & ~ADC16_SEQ_DMA_CFG_BUF_LEN_MASK)
                     | ADC16_SEQ_DMA_CFG_BUF_LEN_SET(dma_config->buff_len_in_4bytes - 1);

    #if defined(ADC_SOC_SEQ_HCFG_EN) && ADC_SOC_SEQ_HCFG_EN
    /* Set high-half buffer length */
    ptr->SEQ_HIGH_CFG = (ptr->SEQ_HIGH_CFG & ~ADC16_SEQ_HIGH_CFG_BUF_LEN_HIGH_MASK)
                      | ADC16_SEQ_HIGH_CFG_BUF_LEN_HIGH_SET(((dma_config->buff_len_in_4bytes - 1) >> 12));
    #endif

    /* Set stop_en and stop_pos */
    if (dma_config->stop_en) {
        ptr->SEQ_DMA_CFG = (ptr->SEQ_DMA_CFG & ~ADC16_SEQ_DMA_CFG_STOP_POS_MASK)
                         | ADC16_SEQ_DMA_CFG_STOP_EN_MASK
                         | ADC16_SEQ_DMA_CFG_STOP_POS_SET(dma_config->stop_pos);

        #if defined(ADC_SOC_SEQ_HCFG_EN) && ADC_SOC_SEQ_HCFG_EN
        ptr->SEQ_HIGH_CFG = (ptr->SEQ_HIGH_CFG & ~ADC16_SEQ_HIGH_CFG_STOP_POS_HIGH_MASK)
                          | ADC16_SEQ_HIGH_CFG_STOP_POS_HIGH_SET(((dma_config->stop_pos) >> 12));
        #endif
    }

    return status_success;
}

hpm_stat_t adc16_set_prd_config(ADC16_Type *ptr, adc16_prd_config_t *config)
{
    /* Check the specified channel number */
    if (ADC16_IS_CHANNEL_INVALID(config->ch)) {
        return status_invalid_argument;
    }

    /* Check the prescale */
    if (config->prescale > (ADC16_PRD_CFG_PRD_CFG_PRESCALE_MASK >> ADC16_PRD_CFG_PRD_CFG_PRESCALE_SHIFT)) {
        return status_invalid_argument;
    }

    /* Set periodic prescale */
    ptr->PRD_CFG[config->ch].PRD_CFG = (ptr->PRD_CFG[config->ch].PRD_CFG & ~ADC16_PRD_CFG_PRD_CFG_PRESCALE_MASK)
                                     | ADC16_PRD_CFG_PRD_CFG_PRESCALE_SET(config->prescale);

    /* Set period count */
    ptr->PRD_CFG[config->ch].PRD_CFG = (ptr->PRD_CFG[config->ch].PRD_CFG & ~ADC16_PRD_CFG_PRD_CFG_PRD_MASK)
                                     | ADC16_PRD_CFG_PRD_CFG_PRD_SET(config->period_count);

    return status_success;
}

hpm_stat_t adc16_trigger_seq_by_sw(ADC16_Type *ptr)
{
    if (ADC16_INT_STS_SEQ_SW_CFLCT_GET(ptr->INT_STS)) {
        return status_fail;
    }
    ptr->SEQ_CFG0 |= ADC16_SEQ_CFG0_SW_TRIG_MASK;

    return status_success;
}

/* Note: the sequence length can not be larger or equal than 2 in HPM6750EVK Revision A0 */
hpm_stat_t adc16_set_seq_config(ADC16_Type *ptr, adc16_seq_config_t *config)
{
    /* Check sequence length */
    if (ADC16_IS_SEQ_LEN_INVLAID(config->seq_len)) {
        return status_invalid_argument;
    }

    ptr->SEQ_CFG0 = ADC16_SEQ_CFG0_SEQ_LEN_SET(config->seq_len - 1)
                  | ADC16_SEQ_CFG0_RESTART_EN_SET(config->restart_en)
                  | ADC16_SEQ_CFG0_CONT_EN_SET(config->cont_en)
                  | ADC16_SEQ_CFG0_SW_TRIG_EN_SET(config->sw_trig_en)
                  | ADC16_SEQ_CFG0_HW_TRIG_EN_SET(config->hw_trig_en);

    /* Set sequence queue */
    for (int i = 0; i < config->seq_len; i++) {
        /* Check the specified channel number */
        if (ADC16_IS_CHANNEL_INVALID(config->queue[i].ch)) {
            return status_invalid_argument;
        }

        ptr->SEQ_QUE[i] = ADC16_SEQ_QUE_SEQ_INT_EN_SET(config->queue[i].seq_int_en)
                        | ADC16_SEQ_QUE_CHAN_NUM_4_0_SET(config->queue[i].ch);
    }

    return status_success;
}

hpm_stat_t adc16_trigger_pmt_by_sw(ADC16_Type *ptr, uint8_t trig_ch)
{
    ptr->TRG_SW_STA = ADC16_TRG_SW_STA_TRG_SW_STA_MASK | ADC16_TRG_SW_STA_TRIG_SW_INDEX_SET(trig_ch);

    return status_success;
}

hpm_stat_t adc16_set_pmt_config(ADC16_Type *ptr, adc16_pmt_config_t *config)
{
    uint32_t temp = 0;

    /* Check the specified trigger length */
    if (ADC16_IS_TRIG_LEN_INVLAID(config->trig_len)) {
        return status_invalid_argument;
    }

    /* Check the triggier channel */
    if (ADC16_IS_TRIG_CH_INVLAID(config->trig_ch)) {
        return status_invalid_argument;
    }

    temp |= ADC16_CONFIG_TRIG_LEN_SET(config->trig_len - 1);

    for (int i = 0; i < config->trig_len; i++) {
        if (ADC16_IS_CHANNEL_INVALID(config->adc_ch[i])) {
            return status_invalid_argument;
        }

        temp |= config->inten[i] << (ADC16_CONFIG_INTEN0_SHIFT + i * ADC_SOC_CONFIG_INTEN_CHAN_BIT_SIZE)
             |  config->adc_ch[i] << (ADC16_CONFIG_CHAN0_SHIFT + i * ADC_SOC_CONFIG_INTEN_CHAN_BIT_SIZE);
    }

    ptr->CONFIG[config->trig_ch] = temp;

    return status_success;
}

hpm_stat_t adc16_set_pmt_queue_enable(ADC16_Type *ptr, uint8_t trig_ch, bool enable)
{
    (void) ptr;
    /* Check the specified trigger channel */
    if (ADC16_IS_TRIG_CH_INVLAID(trig_ch)) {
        return status_invalid_argument;
    }

#if defined(ADC_SOC_PREEMPT_ENABLE_CTRL_SUPPORT) && ADC_SOC_PREEMPT_ENABLE_CTRL_SUPPORT
    /* Set queue enable control */
    ptr->CONFIG[trig_ch] &= ~ADC16_CONFIG_QUEUE_EN_MASK;
    ptr->CONFIG[trig_ch] |= ADC16_CONFIG_QUEUE_EN_SET(enable);
    return status_success;
#else
    (void) enable;
    return status_success;
#endif
}

/* one shot mode */
hpm_stat_t adc16_get_oneshot_result(ADC16_Type *ptr, uint8_t ch, uint16_t *result)
{
    uint32_t bus_res;

    /* Check the specified channel number */
    if (ADC16_IS_CHANNEL_INVALID(ch)) {
        return status_invalid_argument;
    }

    bus_res = ptr->BUS_RESULT[ch];
    *result = ADC16_BUS_RESULT_CHAN_RESULT_GET(bus_res);

    if (ADC16_BUF_CFG0_WAIT_DIS_GET(ptr->BUF_CFG0)) {
        if (!ADC16_BUS_RESULT_VALID_GET(bus_res)) {
            return status_fail;
        }
    }

    return status_success;
}

/* period mode */
hpm_stat_t adc16_get_prd_result(ADC16_Type *ptr, uint8_t ch, uint16_t *result)
{
    /* Check the specified channel number */
    if (ADC16_IS_CHANNEL_INVALID(ch)) {
        return status_invalid_argument;
    }

    *result = ADC16_PRD_CFG_PRD_RESULT_CHAN_RESULT_GET(ptr->PRD_CFG[ch].PRD_RESULT);

    return status_success;
}

#if defined(ADC16_SOC_TEMP_CH_EN) && ADC16_SOC_TEMP_CH_EN
void adc16_enable_temp_sensor(ADC16_Type *ptr)
{
    uint32_t clk_div_temp;

    /* Get input clock divider */
    clk_div_temp = ADC16_CONV_CFG1_CLOCK_DIVIDER_GET(ptr->CONV_CFG1);

    /* Set input clock divider temporarily */
    ptr->CONV_CFG1 = (ptr->CONV_CFG1 & ~ADC16_CONV_CFG1_CLOCK_DIVIDER_MASK) | ADC16_CONV_CFG1_CLOCK_DIVIDER_SET(1);

    /* Enable ADC config clock */
    ptr->ANA_CTRL0 |= ADC16_ANA_CTRL0_ADC_CLK_ON_MASK;

    /* Enable the temperature sensor */
    ptr->ADC16_CONFIG0 |= ADC16_ADC16_CONFIG0_TEMPSNS_EN_MASK | ADC16_ADC16_CONFIG0_REG_EN_MASK
                        | ADC16_ADC16_CONFIG0_BANDGAP_EN_MASK | ADC16_ADC16_CONFIG0_CAL_AVG_CFG_SET(5);

    /* Disable ADC config clock */
    ptr->ANA_CTRL0 &= ~ADC16_ANA_CTRL0_ADC_CLK_ON_MASK;

    /* Recover input clock divider */
    ptr->CONV_CFG1 = (ptr->CONV_CFG1 & ~ADC16_CONV_CFG1_CLOCK_DIVIDER_MASK) | ADC16_CONV_CFG1_CLOCK_DIVIDER_SET(clk_div_temp);
}

void adc16_disable_temp_sensor(ADC16_Type *ptr)
{
    uint32_t clk_div_temp;

    /* Get input clock divider */
    clk_div_temp = ADC16_CONV_CFG1_CLOCK_DIVIDER_GET(ptr->CONV_CFG1);

    /* Set input clock divider temporarily */
    ptr->CONV_CFG1 = (ptr->CONV_CFG1 & ~ADC16_CONV_CFG1_CLOCK_DIVIDER_MASK)
                   | ADC16_CONV_CFG1_CLOCK_DIVIDER_SET(1);

    /* Enable ADC config clock */
    ptr->ANA_CTRL0 |= ADC16_ANA_CTRL0_ADC_CLK_ON_MASK;

    /* Disable the temp sensor */
    ptr->ADC16_CONFIG0 &= ~ADC16_ADC16_CONFIG0_TEMPSNS_EN_MASK;

    /* Disable ADC config clock */
    ptr->ANA_CTRL0 &= ~ADC16_ANA_CTRL0_ADC_CLK_ON_MASK;

    /* Recover input clock divider */
    ptr->CONV_CFG1 = (ptr->CONV_CFG1 & ~ADC16_CONV_CFG1_CLOCK_DIVIDER_MASK)
                   | ADC16_CONV_CFG1_CLOCK_DIVIDER_SET(clk_div_temp);
}
#endif
