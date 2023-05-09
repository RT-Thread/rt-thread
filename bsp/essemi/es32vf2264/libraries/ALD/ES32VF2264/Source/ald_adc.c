/**
  ******************************************************************************
  * @file    ald_adc.c
  * @brief   This file provides firmware functions to manage the following
  *          functionalities of the Analog to Digital Convertor (ADC)
  *          peripheral:
  *           + Initialization functions
  *             ++ Initialization and Configuration of ADC
  *           + Operation functions
  *             ++ Start, stop, get result of conversions of normal
  *                group, using 3 possible modes: polling, interruption or DMA.
  *           + Control functions
  *             ++ Channels configuration on normal group
  *             ++ Channels configuration on insert group
  *             ++ Analog Watchdog configuration
  *           + State functions
  *             ++ ADC state machine management
  *             ++ Interrupts and flags management
  *
  * @version V1.0
  * @date    06 Mar. 2023
  * @author  AE Team.
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          06 Mar. 2023    Lisq            The first version
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  * SPDX-License-Identifier: Apache-2.0
  *
  * Licensed under the Apache License, Version 2.0 (the License); you may
  * not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  * www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an AS IS BASIS, WITHOUT
  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  **********************************************************************************
  */


#include "ald_adc.h"

/** @addtogroup ES32VF2264_ALD
  * @{
  */

/** @defgroup ADC ADC
  * @brief ADC module driver
  * @{
  */

/** @addtogroup ADC_Private_Functions
  * @{
  */
static void adc_dma_normal_conv_cplt(void *arg);
/**
  * @}
  */

/** @defgroup ADC_Public_Functions ADC Public Functions
  * @{
  */

/** @defgroup ADC_Public_Functions_Group1 Initialization functions
  * @brief    Initialization and Configuration functions
  * @{
  */

/**
  * @brief  Initializes the ADC peripheral and normal group according to
  *         parameters specified in structure "adc_handle_t".
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_init(ald_adc_handle_t *hperh)
{
    assert_param(IS_ADC_TYPE(hperh->perh));
    assert_param(IS_ADC_DATA_ALIGN_TYPE(hperh->init.align));
    assert_param(IS_FUNC_STATE(hperh->init.scan));
    assert_param(IS_ADC_CLK_DIV_TYPE(hperh->init.div));
    assert_param(IS_ADC_NEG_REF_VOLTAGE_TYPE(hperh->init.n_ref));
    assert_param(IS_POS_REF_VOLTAGE_TYPE(hperh->init.p_ref));
    assert_param(IS_ADC_CONV_BIT_TYPE(hperh->init.data_bit));
    assert_param(IS_ADC_NCH_NR_TYPE(hperh->init.nch_nr));
    assert_param(IS_ADC_DISC_NR_TYPE(hperh->init.disc_nr));
    assert_param(IS_FUNC_STATE(hperh->init.cont));
    assert_param(IS_ADC_NCHESEL_MODE_TYPE(hperh->init.nche_sel));

    if (hperh->state ==  ALD_ADC_STATE_RESET ) {
        hperh->error_code = ALD_ADC_ERROR_NONE;
        hperh->lock       = UNLOCK;
    }

    ALD_ADC_DISABLE(hperh);
    ald_adc_reset(hperh);
    hperh->state = ALD_ADC_STATE_BUSY;
    MODIFY_REG(hperh->perh->CON1, ADC_CON1_ALIGN_MSK, hperh->init.align << ADC_CON1_ALIGN_POS);
    MODIFY_REG(hperh->perh->CON0, ADC_CON0_RSEL_MSK, hperh->init.data_bit << ADC_CON0_RSEL_POSS);

    /* Enable discontinuous mode only if continuous mode is disable */
    if (hperh->init.disc == ALD_ADC_NCH_DISC_EN) {
        hperh->init.scan = ENABLE;
        hperh->init.cont = DISABLE;
        SET_BIT(hperh->perh->CON0, ADC_CON0_NCHDCEN_MSK);
        MODIFY_REG(hperh->perh->CON0, ADC_CON0_ETRGN_MSK, hperh->init.disc_nr << ADC_CON0_ETRGN_POSS);
    }
    else if (hperh->init.disc == ALD_ADC_ICH_DISC_EN) {
        hperh->init.scan = ENABLE;
        hperh->init.cont = DISABLE;
        SET_BIT(hperh->perh->CON0, ADC_CON0_ICHDCEN_MSK);
        MODIFY_REG(hperh->perh->CON0, ADC_CON0_ETRGN_MSK, hperh->init.disc_nr << ADC_CON0_ETRGN_POSS);
    }
    else {
        CLEAR_BIT(hperh->perh->CON0, ADC_CON0_NCHDCEN_MSK);
        CLEAR_BIT(hperh->perh->CON0, ADC_CON0_ICHDCEN_MSK);
    }

    if ((hperh->init.scan == ENABLE) || (hperh->init.disc == ALD_ADC_NCH_DISC_EN))
        MODIFY_REG(hperh->perh->CHSL, ADC_CHSL_NSL_MSK, hperh->init.nch_nr << ADC_CHSL_NSL_POSS);

    MODIFY_REG(hperh->perh->CON1, ADC_CON1_CM_MSK, hperh->init.cont << ADC_CON1_CM_POS);
    MODIFY_REG(hperh->perh->CON0, ADC_CON0_SCANEN_MSK, hperh->init.scan << ADC_CON0_SCANEN_POS);

    WRITE_REG(hperh->perh->CCR, 0x0);
    MODIFY_REG(hperh->perh->CCR, ADC_CCR_PWRMODSEL_MSK, DISABLE << ADC_CCR_PWRMODSEL_POS);
    MODIFY_REG(hperh->perh->CCR, ADC_CCR_VREFEN_MSK, ENABLE << ADC_CCR_VREFEN_POS);
    MODIFY_REG(hperh->perh->CCR, ADC_CCR_IREFEN_MSK, ENABLE << ADC_CCR_IREFEN_POS);
    MODIFY_REG(hperh->perh->CCR, ADC_CCR_VRNSEL_MSK, hperh->init.n_ref << ADC_CCR_VRNSEL_POS);
    MODIFY_REG(hperh->perh->CCR, ADC_CCR_VRPSEL_MSK, hperh->init.p_ref << ADC_CCR_VRPSEL_POS);
    MODIFY_REG(hperh->perh->CCR, ADC_CCR_POSDIV_MSK, hperh->init.div << ADC_CCR_POSDIV_POSS);
    MODIFY_REG(hperh->perh->CON1, ADC_CON1_NCHESEL_MSK, hperh->init.nche_sel << ADC_CON1_NCHESEL_POS);
    ALD_ADC_ENABLE(hperh);

    hperh->error_code = ALD_ADC_ERROR_NONE;
    hperh->state      = ALD_ADC_STATE_READY;
    return ALD_OK;
}

/**
  * @brief  Deinitialize the ADC peripheral registers to their default reset
  *         values.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_reset(ald_adc_handle_t *hperh)
{
    assert_param(IS_ADC_TYPE(hperh->perh));

    ALD_ADC_DISABLE(hperh);
    WRITE_REG(hperh->perh->CLR, 0x30F);
    WRITE_REG(hperh->perh->CON0, 0x0);
    WRITE_REG(hperh->perh->CON1, 0x0);
    WRITE_REG(hperh->perh->CCR, 0x0);
    WRITE_REG(hperh->perh->WDTH, 0xFFF);
    WRITE_REG(hperh->perh->WDTL, 0x0);
    WRITE_REG(hperh->perh->NCHOFF, 0x0);
    WRITE_REG(hperh->perh->ICHOFF1, 0x0);
    WRITE_REG(hperh->perh->ICHOFF2, 0x0);
    WRITE_REG(hperh->perh->ICHOFF3, 0x0);
    WRITE_REG(hperh->perh->ICHOFF4, 0x0);
    WRITE_REG(hperh->perh->ICHS, 0x0);
    WRITE_REG(hperh->perh->NCHS1, 0x0);
    WRITE_REG(hperh->perh->NCHS2, 0x0);
    WRITE_REG(hperh->perh->NCHS3, 0x0);
    WRITE_REG(hperh->perh->NCHS4, 0x0);
    WRITE_REG(hperh->perh->SMPT1, 0x0);
    WRITE_REG(hperh->perh->SMPT2, 0x0);
    WRITE_REG(hperh->perh->SMPT3, 0x0);
    WRITE_REG(hperh->perh->CHSL, 0x0);

    hperh->state      = ALD_ADC_STATE_RESET;
    hperh->error_code = ALD_ADC_ERROR_NONE;
    return ALD_OK;
}
/**
  * @}
  */

/** @defgroup ADC_Public_Functions_Group2 IO operation functions
 *  @brief    Input and Output operation functions
 *  @{
 */

/**
  * @brief  Enables ADC, starts conversion of normal group.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_normal_start(ald_adc_handle_t *hperh)
{
    assert_param(IS_ADC_TYPE(hperh->perh));

    ALD_ADC_ENABLE(hperh);
    WRITE_REG(hperh->perh->CLR, ALD_ADC_FLAG_NCH | ALD_ADC_FLAG_NCHS);
    SET_BIT(hperh->perh->CON1, ADC_CON1_NCHTRG_MSK);

    return ALD_OK;
}

/**
  * @brief  Stop ADC conversion of normal group (and insert channels in
  *         case of auto_injection mode), disable ADC peripheral.
  * @note:  ADC peripheral disable is forcing stop of potential
  *         conversion on insert group. If insert group is under use, it
  *         should be preliminarily stopped using ald_adc_insert_stop function.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_normal_stop(ald_adc_handle_t *hperh)
{
    assert_param(IS_ADC_TYPE(hperh->perh));

    ALD_ADC_DISABLE(hperh);
    hperh->state = ALD_ADC_STATE_READY;

    return ALD_OK;
}

/**
  * @brief  Wait for normal group conversion to be completed.
  * @note   This function cannot be used in a particular setup: ADC configured  in DMA mode.
  *         In this case, DMA resets the flag EOC and polling cannot be performed on each conversion.
  * @note   When use this function,you should be pay attention to the hperh->init.reocs_mode,
  *         if it is ADC_REOCS_MODE_ALL, it means the function will wait all normal rank conversion  finished.
  *         if it is ADC_REOCS_MODE_ONE, it means the funcion will wait every normal rank conversion finished.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  timeout: Timeout value in millisecond.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_normal_poll_for_conversion(ald_adc_handle_t *hperh, uint32_t timeout)
{
    uint32_t _tick;

    assert_param(IS_ADC_TYPE(hperh->perh));

    _tick = ald_get_tick();
    while (!(READ_BIT(hperh->perh->STAT, ADC_STAT_NCHE_MSK))) {
        if (timeout != ALD_MAX_DELAY ) {
            if ((timeout == 0) || ((ald_get_tick() - _tick) > timeout)) {
                hperh->state = ALD_ADC_STATE_TIMEOUT;
                return ALD_TIMEOUT;
            }
        }
    }

    WRITE_REG(hperh->perh->CLR, ALD_ADC_FLAG_NCHS | ALD_ADC_FLAG_NCH);
    return ALD_OK;
}

/**
  * @brief  Poll for conversion event.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  event_type: the ADC event type.
  *          This parameter can be one of the following values:
  *            ADC_awd_event: ADC Analog watchdog event.
  * @param  timeout: Timeout value in millisecond.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_poll_for_event(ald_adc_handle_t *hperh, ald_adc_event_type_t event_type, uint32_t timeout)
{
    uint32_t _tick;

    assert_param(IS_ADC_TYPE(hperh->perh));
    assert_param(IS_ADC_EVENT_TYPE(event_type));

    _tick = ald_get_tick();
    while (ald_adc_get_flag_status(hperh, (ald_adc_flag_t)event_type) == RESET) {
        if (timeout != ALD_MAX_DELAY ) {
            if ((timeout == 0) || ((ald_get_tick() - _tick) > timeout)) {
                hperh->state = ALD_ADC_STATE_TIMEOUT;
                return ALD_TIMEOUT;
            }
        }
    }

    CLEAR_BIT(hperh->state, ALD_ADC_STATE_BUSY_WDG);
    return ALD_OK;
}

/**
  * @brief  Enables ADC, starts conversion of normal group with interruption.
  *         Interruptions enabled in this function:
  *          - REOC (end of conversion of normal group)
  *         Each of these interruptions has its dedicated callback function.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_normal_start_by_it(ald_adc_handle_t *hperh)
{
    assert_param(IS_ADC_TYPE(hperh->perh));

    SET_BIT(hperh->state, ALD_ADC_STATE_BUSY_N);
    ALD_ADC_ENABLE(hperh);
    WRITE_REG(hperh->perh->CLR, ALD_ADC_FLAG_NCH);
    ald_adc_interrupt_config(hperh, ALD_ADC_IT_NCH, ENABLE);
    SET_BIT(hperh->perh->CON1, ADC_CON1_NCHTRG_MSK);

    return ALD_OK;
}

/**
  * @brief  Stop ADC conversion of normal group (and insert group in
  *         case of auto_injection mode), disable interrution of
  *         end-of-conversion, disable ADC peripheral.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_normal_stop_by_it(ald_adc_handle_t *hperh)
{
    assert_param(IS_ADC_TYPE(hperh->perh));

    ALD_ADC_DISABLE(hperh);
    ald_adc_interrupt_config(hperh, ALD_ADC_IT_NCH, DISABLE);
    CLEAR_BIT(hperh->state, ALD_ADC_STATE_BUSY_N);

    return ALD_OK;
}

/**
  * @brief  Enables ADC, starts conversion of normal group and transfers result
  *         through DMA.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  buf: The destination Buffer address.
  * @param  size: The length of data to be transferred from ADC peripheral to memory.
  * @param  channel: The DMA channel
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_start_by_dma(ald_adc_handle_t *hperh, uint16_t *buf, uint16_t size, uint8_t channel)
{
    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    assert_param(IS_ADC_TYPE(hperh->perh));

    SET_BIT(hperh->state, ALD_ADC_STATE_BUSY_N);

    if (hperh->hdma.perh == NULL)
        hperh->hdma.perh = DMA;

    SET_BIT(hperh->perh->CON1, ADC_CON1_DMA_MSK);

    ald_dma_interrupt_config(channel, ALD_DMA_IT_FLAG_TC, ENABLE);
    hperh->hdma.cplt_tc_cbk = adc_dma_normal_conv_cplt;
    hperh->hdma.cplt_tc_arg = hperh;
    ald_dma_config_struct(&hperh->hdma.config);
    hperh->hdma.config.src            = (void *)&hperh->perh->NCHDR;
    hperh->hdma.config.dst            = (void *)buf;
    hperh->hdma.config.size           = size;
    hperh->hdma.config.src_data_width = ALD_DMA_DATA_SIZE_HALFWORD;
    hperh->hdma.config.dst_data_width = ALD_DMA_DATA_SIZE_HALFWORD;
    hperh->hdma.config.src_inc        = ALD_DMA_DATA_INC_DISABLE;
    hperh->hdma.config.dst_inc        = ALD_DMA_DATA_INC_ENABLE;
    hperh->hdma.config.msel           = ALD_DMA_MSEL_ADC;
    hperh->hdma.config.msigsel        = ALD_DMA_MSIGSEL_ADC;
    hperh->hdma.config.circle_mode    = ENABLE;
    hperh->hdma.config.channel        = channel;
    ald_dma_config_basic(&hperh->hdma);

    ALD_ADC_ENABLE(hperh);
    SET_BIT(hperh->perh->CON1, ADC_CON1_NCHTRG_MSK);

    return ALD_OK;
}

/**
  * @brief  Stop ADC conversion of normal group (and insert group in
  *         case of auto_insert mode), disable ADC DMA transfer, disable
  *         ADC peripheral.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  channel: The DMA channel
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_stop_by_dma(ald_adc_handle_t *hperh, uint8_t channel)
{
    assert_param(IS_ADC_TYPE(hperh->perh));

    ALD_ADC_DISABLE(hperh);
    CLEAR_BIT(hperh->perh->CON1, ADC_CON1_DMA_MSK);
    ald_dma_channel_config(channel, DISABLE);
    CLEAR_BIT(hperh->state, ALD_ADC_STATE_BUSY_N);

    return ALD_OK;
}

/**
  * @brief  DMA transfer complete callback.
  * @param  arg: argument of the call back.
  * @retval None
  */
static void adc_dma_timer_trigger_cplt(void *arg)
{
    ald_adc_timer_config_t *hperh = (ald_adc_timer_config_t *)arg;

    ald_timer_base_stop(&hperh->h_timer);
    CLEAR_BIT(hperh->h_adc.perh->CON1, ADC_CON1_DMA_MSK);
    ALD_ADC_DISABLE(&hperh->h_adc);
    ald_dma_channel_config(hperh->dma_ch, DISABLE);
    CLEAR_BIT(hperh->h_adc.state, ALD_ADC_STATE_BUSY_N);

    if (hperh->h_adc.normal_cplt_cbk)
        hperh->h_adc.normal_cplt_cbk(&hperh->h_adc);

    return;
}

/**
  * @brief  Config timer trigger adc insert channel conversion.
  * @param  config: Pointer to a adc_timer_config_t structure that
  *         contains the configuration information for the specified function.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_timer_trigger_insert(ald_adc_timer_config_t *config)
{
    config->h_pis.perh               = PIS;
    config->h_pis.init.producer_clk  = ALD_PIS_CLK_PCLK;
    config->h_pis.init.producer_edge = ALD_PIS_EDGE_NONE;
    config->h_pis.init.consumer_clk  = ALD_PIS_CLK_PCLK;

    if (config->p_timer == AD16C4T)
        config->h_pis.init.producer_src  = ALD_PIS_TIMER0_UPDATA;
    else if (config->p_timer == GP16C4T0)
        config->h_pis.init.producer_src  = ALD_PIS_TIMER5_UPDATA;
    else if (config->p_timer == GP16C4T1)
        config->h_pis.init.producer_src  = ALD_PIS_TIMER6_UPDATA;
    else if (config->p_timer == GP16C4T2)
        config->h_pis.init.producer_src  = ALD_PIS_TIMER7_UPDATA;
    else
        return ALD_ERROR;

    config->h_pis.init.consumer_trig = ALD_PIS_CH5_ADC0_INSERT;

    ald_pis_create(&config->h_pis);

    /* Initialize TIMER */
    config->h_timer.perh           = config->p_timer;
    config->h_timer.init.prescaler = 0;
    config->h_timer.init.mode      = ALD_TIMER_CNT_MODE_UP;
    config->h_timer.init.period    = ((ald_cmu_get_pclk_clock() / 1000000) * config->time);
    config->h_timer.init.clk_div   = ALD_TIMER_CLOCK_DIV1;
    config->h_timer.init.re_cnt    = 0;
    ald_timer_base_init(&config->h_timer);

    config->h_adc.perh            = config->p_adc;
    config->h_adc.init.align      = ALD_ADC_DATAALIGN_RIGHT;
    config->h_adc.init.scan       = DISABLE;
    config->h_adc.init.cont       = DISABLE;
    config->h_adc.init.ich_nr     = ALD_ADC_ICH_NR_1;
    config->h_adc.init.disc       = ALD_ADC_ALL_DISABLE;
    config->h_adc.init.disc_nr    = ALD_ADC_DISC_NR_1;
    config->h_adc.init.data_bit   = ALD_ADC_CONV_BIT_12;
    config->h_adc.init.div        = ALD_ADC_CKDIV_128;
    config->h_adc.init.nche_sel   = ALD_ADC_NCHESEL_MODE_ONE;
    config->h_adc.init.n_ref      = config->n_ref;
    config->h_adc.init.p_ref      = config->p_ref;
    config->h_adc.normal_cplt_cbk = config->cplt_cbk;
    config->h_adc.insert_cplt_cbk = NULL;
    config->h_adc.wdg_cbk         = NULL;
    config->h_adc.error_cbk       = NULL;
    config->h_adc.ovr_cbk         = NULL;
    ald_adc_init(&config->h_adc);

    config->h_adc.perh->CON1   |= 0x00100000;   /* rising edge trigger insert channel convert */
    config->i_config.ch         = config->adc_ch;
    config->i_config.idx        = ALD_ADC_ICH_IDX_1;
    config->i_config.samp       = ALD_ADC_SAMPLETIME_4;
    config->i_config.nr         = ALD_ADC_ICH_NR_1;
    config->i_config.auto_m     = DISABLE;
    ald_adc_insert_channel_config(&config->h_adc, &config->i_config);

    ALD_ADC_ENABLE(&config->h_adc);
    ald_timer_base_start(&config->h_timer);

    return ALD_OK;
}

/**
  * @brief  Config Timer trigger adc function
  * @param  config: Pointer to a adc_timer_config_t structure that
  *         contains the configuration information for the specified function.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_timer_trigger_adc_by_dma(ald_adc_timer_config_t *config)
{
    config->h_pis.perh               = PIS;
    config->h_pis.init.producer_clk  = ALD_PIS_CLK_PCLK;
    config->h_pis.init.producer_edge = ALD_PIS_EDGE_NONE;
    config->h_pis.init.consumer_clk  = ALD_PIS_CLK_PCLK;

    if (config->p_timer == AD16C4T)
        config->h_pis.init.producer_src  = ALD_PIS_TIMER0_UPDATA;
    else if (config->p_timer == GP16C4T0)
        config->h_pis.init.producer_src  = ALD_PIS_TIMER5_UPDATA;
    else if (config->p_timer == GP16C4T1)
        config->h_pis.init.producer_src  = ALD_PIS_TIMER6_UPDATA;
    else if (config->p_timer == GP16C4T2)
        config->h_pis.init.producer_src  = ALD_PIS_TIMER7_UPDATA;
    else
        return ALD_ERROR;

    config->h_pis.init.consumer_trig = ALD_PIS_CH4_ADC0_NORMAL;

    ald_pis_create(&config->h_pis);

    /* Initialize TIMER */
    config->h_timer.perh           = config->p_timer;
    config->h_timer.init.prescaler = 0;
    config->h_timer.init.mode      = ALD_TIMER_CNT_MODE_UP;
    config->h_timer.init.period    = ((ald_cmu_get_pclk_clock() / 1000000) * config->time);
    config->h_timer.init.clk_div   = ALD_TIMER_CLOCK_DIV1;
    config->h_timer.init.re_cnt    = 0;
    ald_timer_base_init(&config->h_timer);

    config->h_adc.perh            = config->p_adc;
    config->h_adc.init.align      = ALD_ADC_DATAALIGN_RIGHT;
    config->h_adc.init.scan       = DISABLE;
    config->h_adc.init.cont       = DISABLE;
    config->h_adc.init.nch_nr     = ALD_ADC_NCH_NR_1;
    config->h_adc.init.disc       = ALD_ADC_ALL_DISABLE;
    config->h_adc.init.disc_nr    = ALD_ADC_DISC_NR_1;
    config->h_adc.init.data_bit   = ALD_ADC_CONV_BIT_12;
    config->h_adc.init.div        = ALD_ADC_CKDIV_128;
    config->h_adc.init.nche_sel   = ALD_ADC_NCHESEL_MODE_ONE;
    config->h_adc.init.n_ref      = config->n_ref;
    config->h_adc.init.p_ref      = config->p_ref;
    config->h_adc.normal_cplt_cbk = config->cplt_cbk;
    config->h_adc.insert_cplt_cbk = NULL;
    config->h_adc.wdg_cbk         = NULL;
    config->h_adc.error_cbk       = NULL;
    config->h_adc.ovr_cbk         = NULL;
    ald_adc_init(&config->h_adc);

    config->h_adc.perh->CON1 |= 0x10000000;
    config->config.ch   = config->adc_ch;
    config->config.idx  = ALD_ADC_NCH_IDX_1;
    config->config.samp = ALD_ADC_SAMPLETIME_4;
    ald_adc_normal_channel_config(&config->h_adc, &config->config);

    config->h_dma.cplt_tc_cbk = adc_dma_timer_trigger_cplt;
    config->h_dma.cplt_tc_arg = config;

    ald_dma_config_struct(&config->h_dma.config);
    config->h_dma.perh              = DMA;
    config->h_dma.config.src        = (void *)&config->h_adc.perh->NCHDR;
    config->h_dma.config.dst        = (void *)config->buf;
    config->h_dma.config.size       = config->size;
    config->h_dma.config.src_data_width = ALD_DMA_DATA_SIZE_HALFWORD;
    config->h_dma.config.dst_data_width = ALD_DMA_DATA_SIZE_HALFWORD;
    config->h_dma.config.src_inc    = ALD_DMA_DATA_INC_DISABLE;
    config->h_dma.config.dst_inc    = ALD_DMA_DATA_INC_ENABLE;
    config->h_dma.config.msel       = ALD_DMA_MSEL_ADC;
    config->h_dma.config.msigsel    = ALD_DMA_MSIGSEL_ADC;
    config->h_dma.config.channel    = config->dma_ch;
    ald_dma_config_basic(&config->h_dma);
    ald_dma_interrupt_config(config->dma_ch, ALD_DMA_IT_FLAG_TC, ENABLE);

    SET_BIT(config->h_adc.perh->CON1, ADC_CON1_DMA_MSK);
    ALD_ADC_ENABLE(&config->h_adc);
    ald_timer_base_start(&config->h_timer);

    return ALD_OK;
}

/**
  * @brief  Get ADC normal group conversion result.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval ADC group normal conversion data
  */
uint32_t ald_adc_normal_get_value(ald_adc_handle_t *hperh)
{
    assert_param(IS_ADC_TYPE(hperh->perh));

    return hperh->perh->NCHDR;
}

/**
  * @brief  Enables ADC, starts conversion of insert group.
  *         Interruptions enabled in this function: None.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_insert_start(ald_adc_handle_t *hperh)
{
    assert_param(IS_ADC_TYPE(hperh->perh));

    ALD_ADC_ENABLE(hperh);
    WRITE_REG(hperh->perh->CLR, ALD_ADC_FLAG_ICH);

    if (!(READ_BIT(hperh->perh->CON0, ADC_CON0_IAUTO_MSK)))
        SET_BIT(hperh->perh->CON1, ADC_CON1_ICHTRG_MSK);

    return ALD_OK;
}

/**
  * @brief  Stop conversion of insert channels. Disable ADC peripheral if
  *         no normal conversion is on going.
  * @note   If ADC must be disabled and if conversion is on going on
  *         normal group, function ald_adc_normal_stop must be used to stop both
  *         insert and normal groups, and disable the ADC.
  * @note   If insert group mode auto-injection is enabled,
  *         function ald_adc_normal_stop must be used.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_insert_stop(ald_adc_handle_t *hperh)
{
    assert_param(IS_ADC_TYPE(hperh->perh));

    ALD_ADC_DISABLE(hperh);
    hperh->state = ALD_ADC_STATE_READY;
    return ALD_OK;
}

/**
  * @brief  Wait for insert group conversion to be completed.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  timeout: Timeout value in millisecond.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_insert_poll_for_conversion(ald_adc_handle_t *hperh, uint32_t timeout)
{
    uint32_t _tick;

    assert_param(IS_ADC_TYPE(hperh->perh));

    _tick = ald_get_tick();

    while (!(READ_BIT(hperh->perh->STAT, ADC_STAT_ICHE_MSK))) {
        if (timeout != ALD_MAX_DELAY) {
            if ((timeout == 0) || ((ald_get_tick() - _tick) > timeout)) {
                hperh->state |= ALD_ADC_STATE_TIMEOUT;
                return ALD_TIMEOUT;
            }
        }
    }

    WRITE_REG(hperh->perh->CLR, ALD_ADC_FLAG_ICHS | ALD_ADC_FLAG_ICH);
    return ALD_OK;
}

/**
  * @brief  Enables ADC, starts conversion of insert group with interruption.
  *          - JEOC (end of conversion of insert group)
  *         Each of these interruptions has its dedicated callback function.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval Status, see @ref ald_status_t..
  */
ald_status_t ald_adc_insert_start_by_it(ald_adc_handle_t *hperh)
{
    assert_param(IS_ADC_TYPE(hperh->perh));

    SET_BIT(hperh->state, ALD_ADC_STATE_BUSY_I);
    ALD_ADC_ENABLE(hperh);
    WRITE_REG(hperh->perh->CLR, ALD_ADC_FLAG_ICHS | ALD_ADC_FLAG_ICH);
    ald_adc_interrupt_config(hperh, ALD_ADC_IT_ICH, ENABLE);

    if (!(READ_BIT(hperh->perh->CON0, ADC_CON0_IAUTO_MSK)))
        SET_BIT(hperh->perh->CON1, ADC_CON1_ICHTRG_MSK);

    return ALD_OK;
}

/**
  * @brief  Stop conversion of insert channels, disable interruption of
  *         end-of-conversion. Disable ADC peripheral if no normal conversion
  *         is on going.
  * @note   If ADC must be disabled and if conversion is on going on
  *         normal group, function ald_adc_normal_stop must be used to stop both
  *         insert and normal groups, and disable the ADC.
  * @note   If insert group mode auto-injection is enabled,
  *         function ald_adc_normal_stop must be used.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval None
  */
ald_status_t ald_adc_insert_stop_by_it(ald_adc_handle_t *hperh)
{
    assert_param(IS_ADC_TYPE(hperh->perh));

    CLEAR_BIT(hperh->state, ALD_ADC_STATE_BUSY_I);
    ALD_ADC_DISABLE(hperh);
    ald_adc_interrupt_config(hperh, ALD_ADC_IT_ICH, DISABLE);
    return ALD_OK;
}

/**
  * @brief  Get ADC insert group conversion result.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  idx: Index of converted ADC insert channel.
  * @retval ADC group insert conversion data
  */
uint32_t ald_adc_insert_get_value(ald_adc_handle_t *hperh, ald_adc_ich_idx_t idx)
{
    uint32_t tmp;

    assert_param(IS_ADC_TYPE(hperh->perh));
    assert_param(IS_ADC_ICH_IDX_TYPE(idx));

    switch (idx) {
    case ALD_ADC_ICH_IDX_1:
        tmp = hperh->perh->ICHDR1;
        break;
    case ALD_ADC_ICH_IDX_2:
        tmp = hperh->perh->ICHDR2;
        break;
    case ALD_ADC_ICH_IDX_3:
        tmp = hperh->perh->ICHDR3;
        break;
    case ALD_ADC_ICH_IDX_4:
        tmp = hperh->perh->ICHDR4;
        break;
    default:
        tmp = hperh->perh->ICHDR1;
        break;
    }

    return tmp;
}

/**
  * @brief  Handles ADC interrupt request
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval None
  */
void ald_adc_irq_handler(ald_adc_handle_t *hperh)
{
    assert_param(IS_ADC_TYPE(hperh->perh));

    if (ald_adc_get_it_status(hperh, ALD_ADC_IT_NCH) && ald_adc_get_flag_status(hperh, ALD_ADC_FLAG_NCH)) {
        WRITE_REG(hperh->perh->CLR, ALD_ADC_FLAG_NCH | ALD_ADC_FLAG_NCHS);
        CLEAR_BIT(hperh->state, ALD_ADC_STATE_BUSY_N);

        if (hperh->normal_cplt_cbk)
            hperh->normal_cplt_cbk(hperh);
    }

    if (ald_adc_get_it_status(hperh, ALD_ADC_IT_ICH) && ald_adc_get_flag_status(hperh, ALD_ADC_FLAG_ICH)) {
        WRITE_REG(hperh->perh->CLR, ALD_ADC_FLAG_ICH | ALD_ADC_FLAG_ICHS);
        CLEAR_BIT(hperh->state, ALD_ADC_STATE_BUSY_I);

        if (hperh->insert_cplt_cbk)
            hperh->insert_cplt_cbk(hperh);
    }

    if (ald_adc_get_it_status(hperh, ALD_ADC_IT_AWD) && ald_adc_get_flag_status(hperh, ALD_ADC_FLAG_AWD)) {
        CLEAR_BIT(hperh->state, ALD_ADC_STATE_BUSY_WDG);
        WRITE_REG(hperh->perh->CLR, ALD_ADC_FLAG_AWD);

        if (hperh->wdg_cbk)
            hperh->wdg_cbk(hperh);
    }

    if (ald_adc_get_it_status(hperh, ALD_ADC_IT_OVR) && ald_adc_get_flag_status(hperh, ALD_ADC_FLAG_OVR)) {
        WRITE_REG(hperh->perh->CLR, ALD_ADC_FLAG_OVR);
        hperh->error_code |= ALD_ADC_ERROR_OVR;
        hperh->state      |= ALD_ADC_STATE_ERROR;

        if (hperh->ovr_cbk)
            hperh->ovr_cbk(hperh);
    }
}

/**
  * @}
  */

/** @defgroup ADC_Public_Functions_Group3 Peripheral Control functions
 *  @brief    Peripheral Control functions
 *  @{
 */

/**
  * @brief  Configures the the selected channel to be linked to the normal
  *         group.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  config: Structure of ADC channel for normal group.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_normal_channel_config(ald_adc_handle_t *hperh, ald_adc_nch_conf_t *config)
{
    assert_param(IS_ADC_TYPE(hperh->perh));
    assert_param(IS_ADC_CHANNELS_TYPE(config->ch));
    assert_param(IS_ADC_NCH_IDX_TYPE(config->idx));
    assert_param(IS_ADC_SAMPLING_TIMES_TYPE(config->samp));

    if (config->idx <= ALD_ADC_NCH_IDX_4 ) {
        hperh->perh->NCHS1 &= ~(0x1f << (uint32_t)((config->idx - 1) << 3));
        hperh->perh->NCHS1 |= (config->ch << (uint32_t)((config->idx - 1) << 3));
    }
    else if (config->idx <= ALD_ADC_NCH_IDX_8) {
        hperh->perh->NCHS2 &= ~(0x1f << (uint32_t)((config->idx - 5) << 3));
        hperh->perh->NCHS2 |= (config->ch << (uint32_t)((config->idx - 5) << 3));
    }
    else if (config->idx <= ALD_ADC_NCH_IDX_12) {
        hperh->perh->NCHS3 &= ~(0x1f << (uint32_t)((config->idx - 9) << 3));
        hperh->perh->NCHS3 |= (config->ch << (uint32_t)((config->idx - 9) << 3));
    }
    else {
        hperh->perh->NCHS4 &= ~(0x1f << (uint32_t)((config->idx - 13) << 3));
        hperh->perh->NCHS4 |= (config->ch << (uint32_t)((config->idx - 13) << 3));
    }

    if (config->ch < ALD_ADC_CHANNEL_8) {
        hperh->perh->SMPT1 &= ~(0xf << (uint32_t)(config->ch << 2));
        hperh->perh->SMPT1 |= config->samp << (uint32_t)(config->ch << 2);
    }
    else if (config->ch < ALD_ADC_CHANNEL_16) {
        hperh->perh->SMPT2 &= ~(0xf << (uint32_t)((config->ch - ALD_ADC_CHANNEL_8) << 2));
        hperh->perh->SMPT2 |= config->samp << (uint32_t)((config->ch - ALD_ADC_CHANNEL_8) << 2);
    }
    else {
        hperh->perh->SMPT3 &= ~(0xf << (uint32_t)((config->ch - ALD_ADC_CHANNEL_16) << 2));
        hperh->perh->SMPT3 |= config->samp << (uint32_t)((config->ch - ALD_ADC_CHANNEL_16) << 2);
    }

    return ALD_OK;
}

/**
  * @brief  Configures the the selected channel to be linked to the insert
  *         group.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  config: Structure of ADC channel for insert group.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_adc_insert_channel_config(ald_adc_handle_t *hperh, ald_adc_ich_conf_t *config)
{
    ald_status_t tmp_status = ALD_OK;

    assert_param(IS_ADC_TYPE(hperh->perh));
    assert_param(IS_ADC_CHANNELS_TYPE(config->ch));
    assert_param(IS_ADC_ICH_IDX_TYPE(config->idx));
    assert_param(IS_ADC_SAMPLING_TIMES_TYPE(config->samp));
    assert_param(IS_ADC_IST_OFFSET_TYPE(config->offset));
    assert_param(IS_ADC_ICH_NR_TYPE(config->nr));
    assert_param(IS_FUNC_STATE(config->auto_m));

    MODIFY_REG(hperh->perh->CHSL, ADC_CHSL_ISL_MSK, config->nr << ADC_CHSL_ISL_POSS);
    hperh->perh->ICHS &= ~(0x1f << (uint32_t)((config->idx - 1) << 3));
    hperh->perh->ICHS |= config->ch << (uint32_t)((config->idx - 1) << 3);

    if (config->auto_m == ENABLE)
        SET_BIT(hperh->perh->CON0, ADC_CON0_IAUTO_MSK);
    else
        CLEAR_BIT(hperh->perh->CON0, ADC_CON0_IAUTO_MSK);

    if (hperh->init.disc == ALD_ADC_ICH_DISC_EN) {
        if (config->auto_m == DISABLE) {
            SET_BIT(hperh->perh->CON0, ADC_CON0_ICHDCEN_MSK);
        }
        else {
            hperh->state      |= ALD_ADC_STATE_ERROR;
            hperh->error_code |= ALD_ADC_ERROR_INTERNAL;
            tmp_status         = ALD_ERROR;
        }
    }

    if (config->ch < 8) {
        hperh->perh->SMPT1 &=  ~(0x0f << (uint32_t)(config->ch << 2));
        hperh->perh->SMPT1 |= config->samp << (uint32_t)(config->ch << 2);
    }
    else if (config->ch < 16) {
        hperh->perh->SMPT2 &=  ~(0x0f << (uint32_t)((config->ch - 8) << 2));
        hperh->perh->SMPT2 |= config->samp << (uint32_t)((config->ch - 8) << 2);
    }
    else {
        hperh->perh->SMPT3 &=  ~(0x0f << (uint32_t)((config->ch - 16) << 2));
        hperh->perh->SMPT3 |= config->samp << (uint32_t)((config->ch - 16) << 2);
    }

    switch (config->idx) {
    case ALD_ADC_ICH_IDX_1:
        hperh->perh->ICHOFF1 = config->offset;
        break;
    case ALD_ADC_ICH_IDX_2:
        hperh->perh->ICHOFF2 = config->offset;
        break;
    case ALD_ADC_ICH_IDX_3:
        hperh->perh->ICHOFF3 = config->offset;
        break;
    case ALD_ADC_ICH_IDX_4:
        hperh->perh->ICHOFF4 = config->offset;
        break;
    default:
        break;
    }

    return tmp_status;
}

/**
  * @brief  Configures the analog watchdog.
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @param  config: Structure of ADC analog watchdog configuration
  * @retval ALD status
  */
ald_status_t ald_adc_analog_wdg_config(ald_adc_handle_t *hperh, ald_adc_analog_wdg_conf_t *config)
{
    assert_param(IS_ADC_TYPE(hperh->perh));
    assert_param(IS_ADC_ANALOG_WTD_MODE_TYPE(config->mode));
    assert_param(IS_FUNC_STATE(config->interrupt));
    assert_param(IS_HTR_TYPE(config->high_thrd));
    assert_param(IS_LTR_TYPE(config->low_thrd));

    if ((config->mode == ALD_ADC_ANAWTD_SING_NM)
        || (config->mode == ALD_ADC_ANAWTD_SING_IST)
            || (config->mode == ALD_ADC_ANAWTD_SING_NMIST))
        assert_param(IS_ADC_CHANNELS_TYPE(config->ch));

    if (config->interrupt == DISABLE)
        ald_adc_interrupt_config(hperh, ALD_ADC_IT_AWD, DISABLE);
    else
        ald_adc_interrupt_config(hperh, ALD_ADC_IT_AWD, ENABLE);

    CLEAR_BIT(hperh->perh->CON0, ADC_CON0_ICHWDTEN_MSK);
    CLEAR_BIT(hperh->perh->CON0, ADC_CON0_NCHWDEN_MSK);
    CLEAR_BIT(hperh->perh->CON0, ADC_CON0_AWDSGL_MSK);
    hperh->perh->CON0 |= config->mode;

    if (READ_BIT(hperh->perh->CON0, ADC_CON0_AWDSGL_MSK))
        MODIFY_REG(hperh->perh->CON0, ADC_CON0_AWDCH_MSK, config->ch << ADC_CON0_AWDCH_POSS);

    WRITE_REG(hperh->perh->WDTL, config->low_thrd);
    WRITE_REG(hperh->perh->WDTH, config->high_thrd);
    SET_BIT(hperh->state, ALD_ADC_STATE_BUSY_WDG);

    return ALD_OK;
}

/**
  * @brief  Enables or disables the specified ADC interrupts.
  * @param  hperh: Pointer to a adc_handle_t structure.
  * @param  it: Specifies the ADC interrupt sources to be enabled or disabled.
  *         This parameter can be one of the @ref adc_it_t.
  * @param  state: New status
  *           - ENABLE
  *           - DISABLE
  * @retval None
  */
void ald_adc_interrupt_config(ald_adc_handle_t *hperh, ald_adc_it_t it, type_func_t state)
{
    assert_param(IS_ADC_TYPE(hperh->perh));
    assert_param(IS_ADC_IT_TYPE(it));
    assert_param(IS_FUNC_STATE(state));

    if (state == ENABLE)
        SET_BIT(hperh->perh->CON0, it);
    else
        CLEAR_BIT(hperh->perh->CON0, it);

    return;
}

/**
  * @brief  Checks whether the specified ADC interrupt has occurred or not.
  * @param  hperh: Pointer to a adc_handle_t structure.
  * @param  it: Specifies the ADC interrupt source to check.
  *         This parameter can be one of the @ref adc_it_t.
  * @retval Status
  *           - SET
  *           - RESET
  */
it_status_t ald_adc_get_it_status(ald_adc_handle_t *hperh, ald_adc_it_t it)
{
    assert_param(IS_ADC_TYPE(hperh->perh));
    assert_param(IS_ADC_IT_TYPE(it));

    if (READ_BIT(hperh->perh->CON0, it))
        return SET;

    return RESET;
}

/** @brief  Check whether the specified ADC flag is set or not.
  * @param  hperh: Pointer to a adc_handle_t structure.
  * @param  flag: specifies the flag to check.
  *         This parameter can be one of the @ref adc_flag_t.
  * @retval Status
  *           - SET
  *           - RESET
  */
flag_status_t ald_adc_get_flag_status(ald_adc_handle_t *hperh, ald_adc_flag_t flag)
{
    assert_param(IS_ADC_TYPE(hperh->perh));
    assert_param(IS_ADC_FLAGS_TYPE(flag));

    if (READ_BIT(hperh->perh->STAT, flag))
        return SET;

    return RESET;
}

/** @brief  Clear the specified ADC pending flags.
  * @param  hperh: Pointer to a adc_handle_t structure.
  * @param  flag: specifies the flag to check.
  *         This parameter can be one of the @ref adc_flag_t.
  * @retval None
  */
void ald_adc_clear_flag_status(ald_adc_handle_t *hperh, ald_adc_flag_t flag)
{
    assert_param(IS_ADC_TYPE(hperh->perh));
    assert_param(IS_ADC_FLAGS_TYPE(flag));

    WRITE_REG(hperh->perh->CLR, flag);
    return;
}
/**
  * @}
  */

/** @defgroup ADC_Public_Functions_Group4 Peripheral State functions
 *  @brief    Peripheral State functions
 *  @{
 */

/**
  * @brief  return the ADC state
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval state
  */
uint32_t ald_adc_get_state(ald_adc_handle_t *hperh)
{
    return hperh->state;
}

/**
  * @brief  Return the ADC error code
  * @param  hperh: Pointer to a adc_handle_t structure that contains
  *         the configuration information for the specified ADC module.
  * @retval ADC Error Code
  */
uint32_t ald_adc_get_error(ald_adc_handle_t *hperh)
{
    return hperh->error_code;
}

/**
  *@}
  */

/**
  *@}
  */

/** @defgroup ADC_Private_Functions ADC Private Functions
  * @{
  */

/**
  * @brief  DMA transfer complete callback.
  * @param  arg: argument of the call back.
  * @retval None
  */
static void adc_dma_normal_conv_cplt(void *arg)
{
    ald_adc_handle_t *hperh = (ald_adc_handle_t *)arg;

    CLEAR_BIT(hperh->perh->CON1, ADC_CON1_DMA_MSK);

    if (hperh->normal_cplt_cbk)
        hperh->normal_cplt_cbk(hperh);

}

/**
  *@}
  */
/**
  *@}
  */

/**
  *@}
  */
