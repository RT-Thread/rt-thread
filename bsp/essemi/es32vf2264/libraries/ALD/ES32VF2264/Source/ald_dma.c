/**
  *********************************************************************************
  *
  * @file    ald_dma.c
  * @brief   DMA module driver.
  *
  * @version V1.0
  * @date    17 Feb. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          17 Feb. 2023    Lisq            The first version
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

#include <string.h>
#include "ald_dma.h"

/** @addtogroup ES32VF2264_ALD
  * @{
  */

/** @defgroup DMA DMA
  * @brief DMA module driver
  * @{
  */

/** @defgroup DMA_Private_Variables DMA Private Variables
  * @{
  */
ald_dma_call_back_t dma_cbk[7];
/**
  * @}
  */

/** @defgroup DMA_Private_Functions DMA Private Functions
  * @{
  */

/**
  * @brief  Configure DMA channel using dma_config_t structure
  * @param  None
  * @param  config: Pointer to dma_config_t which contains
  *            DMA channel parameter. see @ref dma_config_t
  * @retval None
  */
void ald_dma_config_base(ald_dma_config_t *config)
{
    assert_param(config->src != NULL);
    assert_param(config->dst != NULL);
    assert_param(IS_DMA_DATA_SIZE(config->size));
    assert_param(IS_DMA_DATASIZE_TYPE(config->src_data_width));
    assert_param(IS_DMA_DATASIZE_TYPE(config->dst_data_width));
    assert_param(IS_DMA_DATAINC_TYPE(config->src_inc));
    assert_param(IS_DMA_DATAINC_TYPE(config->dst_inc));
    assert_param(IS_DMA_ARBITERCONFIG_TYPE(config->R_power));
    assert_param(IS_DMA_PRIORITY_TYPE(config->priority));
    assert_param(IS_DMA_MSEL_TYPE(config->msel));
    assert_param(IS_DMA_MSIGSEL_TYPE(config->msigsel));
    assert_param(IS_DMA_CHANNEL(config->channel));

    WRITE_REG(DMA->CHANNEL[config->channel].SAR, (uint32_t)config->src);
    MODIFY_REG(DMA->CHANNEL[config->channel].CON, DMA_CON_SDWSEL_MSK, config->src_data_width << DMA_CON_SDWSEL_POSS);
    MODIFY_REG(DMA->CHANNEL[config->channel].CON, DMA_CON_SINC_MSK, config->src_inc << DMA_CON_SINC_POS);
    WRITE_REG(DMA->CHANNEL[config->channel].DAR, (uint32_t)config->dst);
    MODIFY_REG(DMA->CHANNEL[config->channel].CON, DMA_CON_DDWSEL_MSK, config->dst_data_width << DMA_CON_DDWSEL_POSS);
    MODIFY_REG(DMA->CHANNEL[config->channel].CON, DMA_CON_DINC_MSK, config->dst_inc << DMA_CON_DINC_POS);
    MODIFY_REG(DMA->CHANNEL[config->channel].CON, DMA_CON_CIRC_MSK, config->circle_mode << DMA_CON_CIRC_POS);
    MODIFY_REG(DMA->CHANNEL[config->channel].CON, DMA_CON_M2M_MSK, config->mem_to_mem << DMA_CON_M2M_POS);
    MODIFY_REG(DMA->CHANNEL[config->channel].CON, DMA_CON_CHPRI_MSK, config->priority << DMA_CON_CHPRI_POSS);
    MODIFY_REG(DMA->CHANNEL[config->channel].CON, DMA_CON_MAX_BURST_MSK, config->R_power << DMA_CON_MAX_BURST_POSS);
    MODIFY_REG(DMA->CHANNEL[config->channel].NDT, DMA_NDT_TNDT_MSK, config->size << DMA_NDT_TNDT_POSS);
    MODIFY_REG(DMA_MUX->CH_SELCON[config->channel], DMA_SELCON_MSEL_MSK, config->msel << DMA_SELCON_MSEL_POSS);
    MODIFY_REG(DMA_MUX->CH_SELCON[config->channel], DMA_SELCON_MSIGSEL_MSK, config->msigsel << DMA_SELCON_MSIGSEL_POSS);

    return;
}

/**
  * @brief  Configure DMA channel according to the specified parameter
  *         in the dma_handle_t structure. The DMA mode is basic.
  *         This mode is used to carry data from peripheral to memory
  *         or from memory to peripheral.
  * @param  hperh: Pointer to dma_handle_t structure that contains
  *         configuration information for specified DMA channel.
  * @retval None
  */
void ald_dma_config_basic(ald_dma_handle_t *hperh)
{
    dma_cbk[hperh->config.channel].cplt_tc_cbk = hperh->cplt_tc_cbk;
    dma_cbk[hperh->config.channel].cplt_ht_cbk  = hperh->cplt_ht_cbk;
    dma_cbk[hperh->config.channel].cplt_tc_arg = hperh->cplt_tc_arg;
    dma_cbk[hperh->config.channel].cplt_ht_arg  = hperh->cplt_ht_arg;

    ald_dma_clear_flag_status(hperh->config.channel, ALD_DMA_IT_FLAG_TC);
    ald_dma_clear_flag_status(hperh->config.channel, ALD_DMA_IT_FLAG_HT);
    ald_dma_config_base(&hperh->config);
    ald_dma_channel_config(hperh->config.channel, ENABLE);

    return;
}

/**
  * @brief  Configure DMA channel according to the specified parameter.
  *         The DMA mode is basic. This mode is used to carry data
  *         from peripheral to memory or negative direction. If user want
  *         use the dma easily, they can invoke this function.
  * @param  DMAx: Pointer to DMA peripheral
  * @param  src: Source data begin pointer
  * @param  dst: Destination data begin pointer
  * @param  size: The total number of DMA transfers that DMA cycle contains
  * @param  msel: Input source to DMA channel @ref dma_msel_t
  * @param  msigsel: Input signal to DMA channel @ref dma_msigsel_t
  * @param  channel: Channel index which will be used
  * @param  cbk: DMA complete callback function
  *
  * @retval None
  *
 */
void ald_dma_config_basic_easy(void *src, void *dst, uint16_t size, ald_dma_msel_t msel,
        ald_dma_msigsel_t msigsel, uint8_t channel, void (*cbk)(void *arg))
{
    ald_dma_handle_t hperh;

    ald_dma_config_struct(&hperh.config);

    if (((uint32_t)src) >= 0x40000000)
        hperh.config.src_inc = ALD_DMA_DATA_INC_DISABLE;

    if (((uint32_t)dst) >= 0x40000000)
        hperh.config.dst_inc = ALD_DMA_DATA_INC_DISABLE;

    hperh.config.src     = src;
    hperh.config.dst     = dst;
    hperh.config.size    = size;
    hperh.config.msel    = msel;
    hperh.config.msigsel = msigsel;
    hperh.config.channel = channel;

    hperh.perh        = DMA;
    hperh.cplt_tc_cbk = cbk;
    hperh.cplt_tc_arg = NULL;
    hperh.cplt_ht_cbk = NULL;

    ald_dma_clear_flag_status(channel, ALD_DMA_IT_FLAG_TC);
    ald_dma_clear_flag_status(channel, ALD_DMA_IT_FLAG_HT);
    ald_dma_config_basic(&hperh);

    return;
}

/**
  * @brief  Handle DMA interrupt
  * @retval None
  */
void ald_dma_irq_handler(void)
{
    uint8_t i;

    for (i = 0; i < ALD_DMA_CH_COUNT; ++i)
    {
        if (READ_BIT(DMA->IFM, 1U << (2U * i)))
        {
            if (dma_cbk[i].cplt_tc_cbk != NULL)
                dma_cbk[i].cplt_tc_cbk(dma_cbk[i].cplt_tc_arg);

            DMA->ICR = 1U << (2U * i);
        }

        if (READ_BIT(DMA->IFM, 1U << (2U * i + 1U)))
        {
            if (dma_cbk[i].cplt_ht_cbk != NULL)
                dma_cbk[i].cplt_ht_cbk(dma_cbk[i].cplt_ht_arg);

            DMA->ICR = 1U << (2U * i + 1U);
        }
    }

    return;
}
/**
  * @}
  */

/** @defgroup DMA_Public_Functions DMA Public Functions
  * @{
  */

/** @defgroup DMA_Public_Functions_Group1 Initialization functions
  * @brief Initialization functions
  *
  * @{
  */

/**
  * @brief  Reset the DMA register
  * @param  None
  * @retval None
  */
void ald_dma_reset(void)
{
    uint32_t i;

    WRITE_REG(DMA->IDR, 0x3FFF);
    WRITE_REG(DMA->ICR, 0x3FFF);

    for (i = 0; i < DMA_CHANNELS; ++i)
    {
        CLEAR_BIT(DMA->CHANNEL[i].CON, DMA_CON_CHEN_MSK);
        WRITE_REG(DMA->CHANNEL[i].CON, 0x0);
        WRITE_REG(DMA->CHANNEL[i].SAR, 0x0);
        WRITE_REG(DMA->CHANNEL[i].DAR, 0x0);
        WRITE_REG(DMA->CHANNEL[i].NDT, 0x0);
        WRITE_REG(DMA_MUX->CH_SELCON[i], 0x0);
    }

    return;
}

/**
  * @brief  DMA module initialization, this function
  *         is invoked by ald_cmu_init().
  * @param  None
  * @retval None
  */
void ald_dma_init(void)
{
    memset(dma_cbk, 0x0, sizeof(dma_cbk));

    ald_dma_reset();
    ald_mcu_irq_config(DMA_IRQn, 4, ENABLE);

    return;
}

/**
  * @brief  Configure dma_config_t structure using default parameter.
  *         User can invoked this function, before configure dma_config_t
  * @param  config: Pointer to dma_config_t structure, see @ref dma_config_t
  * @retval None
  */
void ald_dma_config_struct(ald_dma_config_t *config)
{
    config->size           = 0;
    config->src_data_width = ALD_DMA_DATA_SIZE_BYTE;
    config->dst_data_width = ALD_DMA_DATA_SIZE_BYTE;
    config->src_inc        = ALD_DMA_DATA_INC_DISABLE;
    config->dst_inc        = ALD_DMA_DATA_INC_DISABLE;
    config->R_power        = ALD_DMA_R_POWER_1;
    config->priority       = ALD_DMA_LOW_PRIORITY;
    config->mem_to_mem     = DISABLE;
    config->circle_mode    = DISABLE;
    config->msel           = ALD_DMA_MSEL_NONE;
    config->msigsel        = ALD_DMA_MSIGSEL_NONE;
    config->channel        = ALD_DMA_CH_0;

    return;
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup DMA_Public_Functions_Group2 DMA Control functions
  * @brief DMA control functions
  *
  * @verbatim
    ===================================================================

                    #### DMA control functions ####

    ===================================================================
    [..]
    This subsection provides some functions allowing to control DMA:
    (+) ald_dma_channel_config(): Control DMA channel ENABLE/DISABLE.
    (+) ald_dma_interrupt_config(): Control DMA channel interrupt ENABLE or
        DISABLE.
    (+) ald_dma_get_it_status(): Check whether the specified channel
        interrupt is SET or RESET.
    (+) ald_dma_get_flag_status(): Check whether the specified channel
        flag is SET or RESET.
    (+) ald_dma_clear_flag_status(): Clear the specified channel
        pending flag

    @endverbatim
  * @{
  */

/**
  * @brief  Configure channel enable or disable. It will unbind descriptor with
  *         channel, when channel has been disable.
  * @param  None
  * @param  channel: channel index
  * @param  state: status of channel:
  *           @arg ENABLE: Enable the channel
  *           @arg DISABLE: Disable the channel
  * @retval None
  */
void ald_dma_channel_config(uint8_t channel, type_func_t state)
{
    assert_param(IS_DMA_CHANNEL(channel));
    assert_param(IS_FUNC_STATE(state));

    if (state)
    {
        SET_BIT(DMA->CHANNEL[channel].CON, DMA_CON_CHEN_MSK);
    }
    else
    {
        CLEAR_BIT(DMA->CHANNEL[channel].CON, DMA_CON_CHEN_MSK);
        WRITE_REG(DMA->CHANNEL[channel].CON, 0x0);
        WRITE_REG(DMA->CHANNEL[channel].SAR, 0x0);
        WRITE_REG(DMA->CHANNEL[channel].DAR, 0x0);
        WRITE_REG(DMA->CHANNEL[channel].NDT, 0x0);
        WRITE_REG(DMA_MUX->CH_SELCON[channel], 0x0);
    }

    return;
}

/**
  * @brief  Configure the interrupt enable or disable
  * @param  channel: Channel index.
  *           @arg 0~6: Channel index
  * @param  it: IT type.
  *           @arg DMA_IT_FLAG_TC
  *           @arg DMA_IT_FLAG_HT
  * @param  state: status of channel:
  *           @arg ENABLE: Enable the channel
  *           @arg DISABLE: Disable the channel
  *
  * @retval None
  */
void ald_dma_interrupt_config(uint8_t channel, ald_dma_it_flag_t it, type_func_t state)
{
    assert_param(IS_DMA_CHANNEL(channel));
    assert_param(IS_DMA_IT_TYPE(it));
    assert_param(IS_FUNC_STATE(state));

    if (state)
        SET_BIT(DMA->IER, 1U << (channel * 2U + it));
    else
        SET_BIT(DMA->IDR, 1U << (channel * 2U + it));

    return;
}

/**
  * @brief  Check whether the specified channel interrupt
  *         is set or reset
  * @param  it: IT type.
  *           @arg DMA_IT_FLAG_TC
  *           @arg DMA_IT_FLAG_HT
  * @param  channel: Channel index
  *           @arg 0~6: Channel index
  * @retval Status:
  *           - SET: Channel interrupt is set
  *           - RESET: Channel interrupt is reset
  */
it_status_t ald_dma_get_it_status(uint8_t channel, ald_dma_it_flag_t it)
{
    assert_param(IS_DMA_CHANNEL(channel));
    assert_param(IS_DMA_IT_TYPE(it));

    if (READ_BIT(DMA->IVS, 1 << (channel * 2U + it)))
        return SET;

    return RESET;
}

/**
  * @brief  Check whether the specified channel flag
  *         is set or reset
  * @param  channel: Channel index
  *           @arg 0~6: Channel index
  * @param  it: IT type.
  *           @arg DMA_IT_FLAG_TC
  *           @arg DMA_IT_FLAG_HT
  * @retval Status:
  *           - SET: Channel flag is set
  *           - RESET: Channel flag is reset
  */
flag_status_t ald_dma_get_flag_status(uint8_t channel, ald_dma_it_flag_t it)
{
    assert_param(IS_DMA_CHANNEL(channel));
    assert_param(IS_DMA_IT_TYPE(it));

    if (READ_BIT(DMA->IFM, 1 << (channel * 2U + it)))
        return SET;

    return RESET;
}

/**
  * @brief  Clear the specified channel pending flag
  * @param  channel: Channel index
  *           @arg 0~6: Channel index
  * @param  it: IT type.
  *           @arg DMA_IT_FLAG_TC
  *           @arg DMA_IT_FLAG_HT
  * @retval None
  */
void ald_dma_clear_flag_status(uint8_t channel, ald_dma_it_flag_t it)
{
    assert_param(IS_DMA_CHANNEL(channel));
    assert_param(IS_DMA_IT_TYPE(it));

    SET_BIT(DMA->ICR, 1U << (channel * 2U + it));
    return;
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
