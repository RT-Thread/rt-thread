/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_dac_drv.h"

void dac_get_default_config(dac_config_t *config)
{
    config->sync_mode = false;
    config->dac_mode = dac_mode_direct;
    config->ana_div = dac_ana_div_2;
}

hpm_stat_t dac_init(DAC_Type *ptr, dac_config_t *config)
{
    if (config->dac_mode > dac_mode_buffer) {
        return status_invalid_argument;
    }

    if (config->ana_div > dac_ana_div_8) {
        return status_invalid_argument;
    }

    /* reset DAC output data */
    ptr->CFG0_BAK &= ~DAC_CFG0_SW_DAC_DATA_MASK;

    /* set sync mode */
    ptr->CFG0_BAK &= ~DAC_CFG0_SYNC_MODE_MASK;
    ptr->CFG0_BAK |= DAC_CFG0_SYNC_MODE_SET(config->sync_mode);

    /* set DAC mode */
    ptr->CFG0_BAK &= ~DAC_CFG0_DAC_MODE_MASK;
    ptr->CFG0_BAK |= DAC_CFG0_DAC_MODE_SET(config->dac_mode);

    /* refresh the CFG0 */
    ptr->CFG0 = ptr->CFG0_BAK;

    /* set DAC clock config */
    ptr->CFG1 &= ~DAC_CFG1_ANA_DIV_CFG_MASK;
    ptr->CFG1 |= DAC_CFG1_ANA_DIV_CFG_SET(config->ana_div);

    if (config->dac_mode == dac_mode_direct) {
        /* set ANA_CLK_EN */
        ptr->CFG1 |= DAC_CFG1_ANA_CLK_EN_MASK;
    }

    return status_success;
}

hpm_stat_t dac_set_step_config(DAC_Type *ptr, uint8_t step_cfg_idx, dac_step_config_t *config)
{
    uint16_t temp;

    /* check the validity */
    if (step_cfg_idx > DAC_STEP_CFG_STEP3) {
        return status_invalid_argument;
    }

    if (config->up_down == dac_step_up) {
        if (config->start_point > config->end_point) {
            return status_invalid_argument;
        }
    } else {
        if (config->start_point < config->end_point) {
            return status_invalid_argument;
        }
    }

    /* check if the output data can reach the end point */
    if (config->step_num != 0) {
        if (config->start_point <= config->end_point) {
            temp = config->end_point - config->start_point;
        } else {
            temp = config->start_point - config->end_point;
        }

        if (temp % config->step_num != 0) {
            return status_invalid_argument;
        }
    }

    /* set the round mode */
    ptr->STEP_CFG[step_cfg_idx] &= ~DAC_STEP_CFG_ROUND_MODE_MASK;
    ptr->STEP_CFG[step_cfg_idx] |= DAC_STEP_CFG_ROUND_MODE_SET(config->round_mode);

    /* set the step direction */
    ptr->STEP_CFG[step_cfg_idx] &= ~DAC_STEP_CFG_UP_DOWN_MASK;
    ptr->STEP_CFG[step_cfg_idx] |= DAC_STEP_CFG_UP_DOWN_SET(config->up_down);

    /* set the start point */
    ptr->STEP_CFG[step_cfg_idx] &= ~DAC_STEP_CFG_START_POINT_MASK;
    ptr->STEP_CFG[step_cfg_idx] |= DAC_STEP_CFG_START_POINT_SET(config->start_point);

    /* set the end point */
    ptr->STEP_CFG[step_cfg_idx] &= ~DAC_STEP_CFG_END_POINT_MASK;
    ptr->STEP_CFG[step_cfg_idx] |= DAC_STEP_CFG_END_POINT_SET(config->end_point);

    /* set the step value */
    ptr->STEP_CFG[step_cfg_idx] &= ~DAC_STEP_CFG_STEP_NUM_MASK;
    ptr->STEP_CFG[step_cfg_idx] |= DAC_STEP_CFG_STEP_NUM_SET(config->step_num);

    return status_success;
}

hpm_stat_t dac_set_buffer_config(DAC_Type *ptr, dac_buffer_config_t *config)
{
    if (config->buf0.len == 0) {
        return status_invalid_argument;
    }

    /* disable the internal DMA */
    ptr->CFG0_BAK &= ~DAC_CFG0_DMA_AHB_EN_MASK;

    /* refresh the CFG0 */
    ptr->CFG0 = ptr->CFG0_BAK;

    /* set buffer data mode */
    ptr->CFG0_BAK &= ~DAC_CFG0_BUF_DATA_MODE_MASK;
    ptr->CFG0_BAK |= DAC_CFG0_BUF_DATA_MODE_SET(config->buf_data_mode);

    /* set burst type */
    ptr->CFG0_BAK &= ~DAC_CFG0_HBURST_CFG_MASK;
    ptr->CFG0_BAK |= DAC_CFG0_HBURST_CFG_SET(config->burst);

    /* reset DMA and FIFO */
    ptr->CFG2 |= DAC_CFG2_DMA_RST1_MASK | DAC_CFG2_DMA_RST0_MASK | DAC_CFG2_FIFO_CLR_MASK;

    /* set buffer 0 start address for DMA */
    ptr->BUF_ADDR[DAC_BUF_ADDR_BUF0] &= ~DAC_BUF_ADDR_BUF_START_ADDR_MASK;
    ptr->BUF_ADDR[DAC_BUF_ADDR_BUF0] |= config->buf0.start_addr & DAC_BUF_ADDR_BUF_START_ADDR_MASK;

    /* set buffer 0 stop */
    ptr->BUF_ADDR[DAC_BUF_ADDR_BUF0] &= ~DAC_BUF_ADDR_BUF_STOP_MASK;
    ptr->BUF_ADDR[DAC_BUF_ADDR_BUF0] |= DAC_BUF_ADDR_BUF_STOP_SET(config->buf0.stop);

    /* set buffer 0 length */
    ptr->BUF_LENGTH &= ~DAC_BUF_LENGTH_BUF0_LEN_MASK;
    ptr->BUF_LENGTH |= DAC_BUF_LENGTH_BUF0_LEN_SET(config->buf0.len - 1);

    /* set buffer 1 start address for DMA */
    ptr->BUF_ADDR[DAC_BUF_ADDR_BUF1] &= ~DAC_BUF_ADDR_BUF_START_ADDR_MASK;
    ptr->BUF_ADDR[DAC_BUF_ADDR_BUF1] |= config->buf1.start_addr & DAC_BUF_ADDR_BUF_START_ADDR_MASK;

    /* set buffer 1 stop */
    ptr->BUF_ADDR[DAC_BUF_ADDR_BUF1] &= ~DAC_BUF_ADDR_BUF_STOP_MASK;
    ptr->BUF_ADDR[DAC_BUF_ADDR_BUF1] |= DAC_BUF_ADDR_BUF_STOP_SET(config->buf1.stop);

    /* set buffer 1 length */
    ptr->BUF_LENGTH &= ~DAC_BUF_LENGTH_BUF1_LEN_MASK;
    ptr->BUF_LENGTH |= DAC_BUF_LENGTH_BUF1_LEN_SET(config->buf1.len - 1);

    /* enable the internal DMA */
    ptr->CFG0_BAK |= DAC_CFG0_DMA_AHB_EN_MASK;

    /* refresh the CFG0 */
    ptr->CFG0 = ptr->CFG0_BAK;

    return status_success;
}

hpm_stat_t dac_set_direct_config(DAC_Type *ptr, uint16_t data)
{
    if (data > DAC_SOC_MAX_DATA) {
        return status_invalid_argument;
    }

    /* set dac data to analog output */
    ptr->CFG0_BAK &= ~DAC_CFG0_SW_DAC_DATA_MASK;
    ptr->CFG0_BAK |= DAC_CFG0_SW_DAC_DATA_SET(data);

    /* refresh the CFG0 */
    ptr->CFG0 = ptr->CFG0_BAK;

    return status_success;
}

hpm_stat_t dac_set_output_frequency(DAC_Type *ptr, uint32_t dac_input_freq, uint32_t dac_output_freq)
{
    if (dac_output_freq > DAC_SOC_MAX_OUTPUT_FREQ) {
        return status_invalid_argument;
    }

    /* set output frequency config */
    ptr->CFG1 &= ~DAC_CFG1_DIV_CFG_MASK;
    ptr->CFG1 |= DAC_CFG1_DIV_CFG_SET(dac_input_freq % dac_output_freq ?  (dac_input_freq / dac_output_freq + 1) : (dac_input_freq / dac_output_freq));

    return status_success;
}

hpm_stat_t dac_set_step_sw_trigger(DAC_Type *ptr, uint8_t step_sw_trig_idx)
{
    if (step_sw_trig_idx > DAC_STEP_CFG_STEP3) {
        return status_invalid_argument;
    }

    /* disable hw trigger */
    ptr->CFG0_BAK &= ~DAC_CFG0_HW_TRIG_EN_MASK;

    /* refresh the CFG0 */
    ptr->CFG0 = ptr->CFG0_BAK;

    /* enable sw trigger */
    ptr->CFG2 |= 1 << step_sw_trig_idx;

    return status_success;
}

void dac_set_buffer_sw_trigger(DAC_Type *ptr)
{
    /* disable hw trigger */
    ptr->CFG0_BAK &= ~DAC_CFG0_HW_TRIG_EN_MASK;

    /* refresh the CFG0 */
    ptr->CFG0 = ptr->CFG0_BAK;

    /* enable sw trigger */
    ptr->CFG2 |= DAC_CFG2_BUF_SW_TRIG_MASK;
}

void dac_set_buffer_DMA_reset(DAC_Type *ptr)
{
    ptr->CFG2 |= DAC_CFG2_DMA_RST1_MASK | DAC_CFG2_DMA_RST0_MASK | DAC_CFG2_FIFO_CLR_MASK;
}

void dac_set_hw_trigger_enable(DAC_Type *ptr, bool enable)
{
    ptr->CFG0_BAK &= ~DAC_CFG0_HW_TRIG_EN_MASK;
    ptr->CFG0_BAK |= DAC_CFG0_HW_TRIG_EN_SET(enable);

    /* refresh the CFG0 */
    ptr->CFG0 = ptr->CFG0_BAK;
}

void dac_enable_conversion(DAC_Type *ptr, bool enable)
{
    ptr->ANA_CFG0 &= ~DAC_ANA_CFG0_DAC12BIT_EN_MASK;
    ptr->ANA_CFG0 |= DAC_ANA_CFG0_DAC12BIT_EN_SET(enable);
}

hpm_stat_t dac_external_DMA_request_enable(DAC_Type *ptr, uint8_t buf_idx, bool enable)
{
    if (buf_idx > DAC_BUF_ADDR_BUF1) {
        return status_invalid_argument;
    }

    ptr->DMA_EN &= ~(1 << buf_idx);
    ptr->DMA_EN |= enable << buf_idx;

    return status_success;
}

void dac_enable_interrupts(DAC_Type *ptr, uint32_t mask)
{
    ptr->IRQ_EN |= mask;
}

uint32_t dac_get_status_flags(DAC_Type *ptr)
{
    return ptr->IRQ_STS;
}

void dac_set_status_flags(DAC_Type *ptr, uint32_t mask)
{
    ptr->IRQ_STS |= mask;
}

uint8_t dac_get_current_buffer_index(DAC_Type *ptr)
{
    return DAC_STATUS0_CUR_BUF_INDEX_GET(ptr->STATUS0);
}

uint16_t dac_get_current_buffer_offset(DAC_Type *ptr)
{
    return DAC_STATUS0_CUR_BUF_OFFSET_GET(ptr->STATUS0);
}
