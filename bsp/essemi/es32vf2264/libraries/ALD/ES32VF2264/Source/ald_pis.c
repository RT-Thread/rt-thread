/**
  *********************************************************************************
  *
  * @file    ald_pis.c
  * @brief   PIS module driver.
  *
  * @version V1.0
  * @date    03 Mar. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          03 Mar. 2023    Lisq            The first version
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

#include "ald_pis.h"

/** @addtogroup ES32VF2264_ALD
  * @{
  */

/** @defgroup PIS PIS
  * @brief PIS module driver
  * @{
  */
/** @defgroup PIS_Public_Functions PIS Public Functions
  * @{
  */

/** @defgroup PIS_Public_Functions_Group1 Initialization functions
  * @brief Initialization and Configuration functions
  * @{
  */

/**
  * @brief  Create the PIS mode according to the specified parameters in
  *         the pis_handle_t and create the associated handle.
  * @param  hperh: Pointer to a pis_handle_t structure that contains
  *         the configuration information for the specified PIS module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_pis_create(ald_pis_handle_t *hperh)
{
    if (hperh == NULL)
        return ALD_ERROR;

    assert_param(IS_PIS_SRC(hperh->init.producer_src));
    assert_param(IS_PIS_TRIG(hperh->init.consumer_trig));
    assert_param(IS_PIS_CLOCK(hperh->init.producer_clk));
    assert_param(IS_PIS_CLOCK(hperh->init.consumer_clk));
    assert_param(IS_PIS_EDGE(hperh->init.producer_edge));
    assert_param(IS_PIS_SIGNAL_MODE(hperh->init.producer_signal));

    __LOCK(hperh);
    hperh->perh = PIS;

    /* get location of consumer in channel and position of con0/con1
     * accord to comsumer_trig information */
    hperh->consumer_ch  = (ald_pis_ch_t)(hperh->init.consumer_trig & 0x0F);
    hperh->consumer_con = (ald_pis_con_t)((hperh->init.consumer_trig >> 4) & 0x0F);
    hperh->consumer_pos = (1U << (uint32_t)((hperh->init.consumer_trig >> 8) & 0xFF));

    if (hperh->perh->CH_CON[hperh->consumer_ch] != 0) {
        __UNLOCK(hperh);
        return ALD_BUSY;
    }

    MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_SRCS_MSK, ((hperh->init.producer_src) >> 4) << PIS_CH0_CON_SRCS_POSS);
    MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_MSIGS_MSK, ((hperh->init.producer_src) & 0xf) << PIS_CH0_CON_MSIGS_POSS);

    if (hperh->init.producer_clk == hperh->init.consumer_clk) {
        MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_SYNCSEL_MSK, ALD_PIS_SYN_DIRECT << PIS_CH0_CON_SYNCSEL_POSS);
        MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_TSCKS_MSK, (hperh->init.consumer_clk) << PIS_CH0_CON_TSCKS_POSS);
    }
    else {
        if (hperh->init.producer_signal == ALD_PIS_OUT_LEVEL) {
            if (hperh->init.consumer_clk == ALD_PIS_CLK_PCLK)
                MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_SYNCSEL_MSK, ALD_PIS_SYN_LEVEL_ASY_APB << PIS_CH0_CON_SYNCSEL_POSS);
            if (hperh->init.consumer_clk == ALD_PIS_CLK_HCLK)
                MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_SYNCSEL_MSK, ALD_PIS_SYN_LEVEL_ASY_AHB << PIS_CH0_CON_SYNCSEL_POSS);
        }

        if (hperh->init.producer_signal == ALD_PIS_OUT_PULSE) {
            if (hperh->init.consumer_clk == ALD_PIS_CLK_PCLK)
                MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_SYNCSEL_MSK, ALD_PIS_SYN_PULSE_ASY_APB << PIS_CH0_CON_SYNCSEL_POSS);
            if (hperh->init.consumer_clk == ALD_PIS_CLK_HCLK)
                MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_SYNCSEL_MSK, ALD_PIS_SYN_PULSE_ASY_AHB << PIS_CH0_CON_SYNCSEL_POSS);
        }
    }

    MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_TSCKS_MSK, hperh->init.consumer_clk << PIS_CH0_CON_TSCKS_POSS);
    MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_EDGS_MSK, hperh->init.producer_edge << PIS_CH0_CON_EDGS_POSS);
    hperh->check_info = hperh->perh->CH_CON[hperh->consumer_ch];

    /* enable consumer bit, switch pin of consumer */
    if (hperh->init.input_chan == ALD_PIS_CHAN_INPUT) {
        switch (hperh->consumer_con) {
        case ALD_PIS_CON_0:
            PIS->TAR_CON0 |= hperh->consumer_pos;
            break;
        case ALD_PIS_CON_1:
            PIS->TAR_CON1 |= hperh->consumer_pos;
            break;
        default:
            break;
        }
    }

    __UNLOCK(hperh);
    return ALD_OK;
}

/**
  * @brief  Destroy the PIS mode according to the specified parameters in
  *         the pis_init_t and create the associated handle.
  * @param  hperh: Pointer to a pis_handle_t structure that contains
  *         the configuration information for the specified PIS module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_pis_destroy(ald_pis_handle_t *hperh)
{
    assert_param(IS_PIS(hperh->perh));

    if (hperh->check_info != hperh->perh->CH_CON[hperh->consumer_ch])
        return ALD_ERROR;

    __LOCK(hperh);

    CLEAR_BIT(PIS->CH_OER, (1U << (uint32_t)hperh->consumer_ch));
    WRITE_REG(hperh->perh->CH_CON[hperh->consumer_ch], 0x0);

    switch (hperh->consumer_con) {
    case ALD_PIS_CON_0:
        PIS->TAR_CON0 &= ~(hperh->consumer_pos);
        break;
    case ALD_PIS_CON_1:
        PIS->TAR_CON1 &= ~(hperh->consumer_pos);
        break;
    default:
        break;
    }

    hperh->state = ALD_PIS_STATE_RESET;
    __UNLOCK(hperh);

    return ALD_OK;
}
/**
  * @}
  */

/** @defgroup PIS_Public_Functions_Group2 Operation functions
  * @brief PIS output enable or disable functions
  * @{
  */

/**
  * @brief  Start the PIS output function.
  * @param  hperh: Pointer to a pis_handle_t structure that contains
  *         the configuration information for the specified PIS module.
  * @param  ch: The PIS channel enable output
  *     This parameter can be one of the following values:
  *     @arg PIS_OUT_CH_0
  *     @arg PIS_OUT_CH_1
  *     @arg PIS_OUT_CH_2
  *     @arg PIS_OUT_CH_3
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_pis_output_start(ald_pis_handle_t *hperh, ald_pis_out_ch_t ch)
{
    assert_param(IS_PIS(hperh->perh));
    assert_param(IS_PIS_OUPUT_CH(ch));
    __LOCK(hperh);
    SET_BIT(PIS->CH_OER, (0x1UL << (uint32_t)ch));
    __UNLOCK(hperh);

    return ALD_OK;
}

/**
  * @brief  Stop the PIS output function.
  * @param  hperh: Pointer to a pis_handle_t structure that contains
  *         the configuration information for the specified PIS module.
  * @param  ch: The PIS channel disable output
  *     This parameter can be one of the following values:
  *     @arg PIS_OUT_CH_0
  *     @arg PIS_OUT_CH_1
  *     @arg PIS_OUT_CH_2
  *     @arg PIS_OUT_CH_3
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_pis_output_stop(ald_pis_handle_t *hperh, ald_pis_out_ch_t ch)
{
    assert_param(IS_PIS(hperh->perh));
    assert_param(IS_PIS_OUPUT_CH(ch));
    __LOCK(hperh);
    CLEAR_BIT(PIS->CH_OER, (0x1UL << (uint32_t)ch));
    __UNLOCK(hperh);

    return ALD_OK;
}
/**
  * @}
  */

/** @defgroup PIS_Public_Functions_Group3 Peripheral State and Errors functions
  *  @brief   PIS State and Errors functions
  * @{
  */

/**
  * @brief  Returns the PIS state.
  * @param  hperh: Pointer to a pis_handle_t structure that contains
  *         the configuration information for the specified PIS module.
  * @retval ALD state
  */
ald_pis_state_t ald_pis_get_state(ald_pis_handle_t *hperh)
{
    assert_param(IS_PIS(hperh->perh));
    return hperh->state;
}

/**
  * @}
  */

/** @defgroup PIS_Public_Functions_Group4 modulate output functions
  *  @brief   PIS modulate output signal functions
  * @{
  */

/**
  * @brief  Config the PIS modulate signal function
  * @param  hperh: Pointer to a pis_handle_t structure that contains
  *         the configuration information for the specified PIS module.
  * @param  config: Pointer to a pis_modulate_config_t structure that
  *         contains the selected target (UART0,UART1,UART2,UART3 or
  *         LPUART0) how to modulate the target output signal.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_pis_modu_config(ald_pis_handle_t *hperh, ald_pis_modulate_config_t *config)
{
    assert_param(IS_PIS(hperh->perh));
    assert_param(IS_PIS_MODU_TARGET(config->target));
    assert_param(IS_PIS_MODU_LEVEL(config->level));
    assert_param(IS_PIS_MODU_SRC(config->src));
    assert_param(IS_PIS_MODU_CHANNEL(config->channel));
    __LOCK(hperh);

    switch (config->target) {
    case ALD_PIS_UART0_TX:
        MODIFY_REG(hperh->perh->UART0_TXMCR, PIS_UART0_TXMCR_TXMLVLS_MSK, config->level << PIS_UART0_TXMCR_TXMLVLS_POS);
        MODIFY_REG(hperh->perh->UART0_TXMCR, PIS_UART0_TXMCR_TXMSS_MSK, config->src << PIS_UART0_TXMCR_TXMSS_POSS);
        MODIFY_REG(hperh->perh->UART0_TXMCR, PIS_UART0_TXMCR_TXSIGS_MSK, config->channel << PIS_UART0_TXMCR_TXSIGS_POSS);
        break;

    case ALD_PIS_UART1_TX:
        MODIFY_REG(hperh->perh->UART1_TXMCR, PIS_UART1_TXMCR_TXMLVLS_MSK, config->level << PIS_UART1_TXMCR_TXMLVLS_POS);
        MODIFY_REG(hperh->perh->UART1_TXMCR, PIS_UART1_TXMCR_TXMSS_MSK, config->src << PIS_UART1_TXMCR_TXMSS_POSS);
        MODIFY_REG(hperh->perh->UART1_TXMCR, PIS_UART1_TXMCR_TXSIGS_MSK, config->channel << PIS_UART1_TXMCR_TXSIGS_POSS);
        break;

    case ALD_PIS_UART2_TX:
        MODIFY_REG(hperh->perh->UART2_TXMCR, PIS_UART2_TXMCR_TXMLVLS_MSK, config->level << PIS_UART2_TXMCR_TXMLVLS_POS);
        MODIFY_REG(hperh->perh->UART2_TXMCR, PIS_UART2_TXMCR_TXMSS_MSK, config->src << PIS_UART2_TXMCR_TXMSS_POSS);
        MODIFY_REG(hperh->perh->UART2_TXMCR, PIS_UART2_TXMCR_TXSIGS_MSK, config->channel << PIS_UART2_TXMCR_TXSIGS_POSS);
        break;

    case ALD_PIS_UART3_TX:
        MODIFY_REG(hperh->perh->UART3_TXMCR, PIS_UART3_TXMCR_TXMLVLS_MSK, config->level << PIS_UART3_TXMCR_TXMLVLS_POS);
        MODIFY_REG(hperh->perh->UART3_TXMCR, PIS_UART3_TXMCR_TXMSS_MSK, config->src << PIS_UART3_TXMCR_TXMSS_POSS);
        MODIFY_REG(hperh->perh->UART3_TXMCR, PIS_UART3_TXMCR_TXSIGS_MSK, config->channel << PIS_UART3_TXMCR_TXSIGS_POSS);
        break;

    case ALD_PIS_UART4_TX:
        MODIFY_REG(hperh->perh->UART4_TXMCR, PIS_UART4_TXMCR_TXMLVLS_MSK, config->level << PIS_UART4_TXMCR_TXMLVLS_POS);
        MODIFY_REG(hperh->perh->UART4_TXMCR, PIS_UART4_TXMCR_TXMSS_MSK, config->src << PIS_UART4_TXMCR_TXMSS_POSS);
        MODIFY_REG(hperh->perh->UART4_TXMCR, PIS_UART4_TXMCR_TXSIGS_MSK, config->channel << PIS_UART4_TXMCR_TXSIGS_POSS);
        break;

    default:
        break;
    }

    __UNLOCK(hperh);
    return ALD_OK;
}
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
