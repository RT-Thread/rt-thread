/*******************************************************************************
* File Name: cycfg_dmas.c
*
* Description:
* DMA configuration
* This file was automatically generated and should not be modified.
* Tools Package 2.4.0.5972
* mtb-pdl-cat1 2.4.0.14850
* personalities 6.0.0.0
* udd 3.0.0.2024
*
********************************************************************************
* Copyright 2022 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
********************************************************************************/

#include "cycfg_dmas.h"

const cy_stc_dma_descriptor_config_t TxDma_Descriptor_0_config =
{
    .retrigger = CY_DMA_RETRIG_4CYC,
    .interruptType = CY_DMA_DESCR,
    .triggerOutType = CY_DMA_1ELEMENT,
    .channelState = CY_DMA_CHANNEL_ENABLED,
    .triggerInType = CY_DMA_1ELEMENT,
    .dataSize = CY_DMA_BYTE,
    .srcTransferSize = CY_DMA_TRANSFER_SIZE_DATA,
    .dstTransferSize = CY_DMA_TRANSFER_SIZE_WORD,
    .descriptorType = CY_DMA_SINGLE_TRANSFER,
    .srcAddress = NULL,
    .dstAddress = NULL,
    .srcXincrement = 1,
    .dstXincrement = 0,
    .xCount = 1,
    .srcYincrement = 1,
    .dstYincrement = 1,
    .yCount = 1,
    .nextDescriptor = NULL,
};
cy_stc_dma_descriptor_t TxDma_Descriptor_0 =
{
    .ctl = 0UL,
    .src = 0UL,
    .dst = 0UL,
    .xCtl = 0UL,
    .yCtl = 0UL,
    .nextPtr = 0UL,
};
const cy_stc_dma_channel_config_t TxDma_channelConfig =
{
    .descriptor = &TxDma_Descriptor_0,
    .preemptable = false,
    .priority = 3,
    .enable = false,
    .bufferable = false,
};
const cy_stc_dma_crc_config_t TxDma_crcConfig =
{
    .dataReverse = false,
    .dataXor = 0,
    .reminderReverse = false,
    .reminderXor = 0,
    .polynomial = 79764919,
};
#if defined (CY_USING_HAL)
    const cyhal_resource_inst_t TxDma_obj =
    {
        .type = CYHAL_RSC_DMA,
        .block_num = 0U,
        .channel_num = TxDma_CHANNEL,
    };
#endif //defined (CY_USING_HAL)
const cy_stc_dma_descriptor_config_t RxDma_Descriptor_0_config =
{
    .retrigger = CY_DMA_RETRIG_4CYC,
    .interruptType = CY_DMA_1ELEMENT,
    .triggerOutType = CY_DMA_1ELEMENT,
    .channelState = CY_DMA_CHANNEL_ENABLED,
    .triggerInType = CY_DMA_1ELEMENT,
    .dataSize = CY_DMA_BYTE,
    .srcTransferSize = CY_DMA_TRANSFER_SIZE_WORD,
    .dstTransferSize = CY_DMA_TRANSFER_SIZE_DATA,
    .descriptorType = CY_DMA_SINGLE_TRANSFER,
    .srcAddress = NULL,
    .dstAddress = NULL,
    .srcXincrement = 0,
    .dstXincrement = 1,
    .xCount = 1,
    .srcYincrement = 1,
    .dstYincrement = 1,
    .yCount = 1,
    .nextDescriptor = &RxDma_Descriptor_1,
};
const cy_stc_dma_descriptor_config_t RxDma_Descriptor_1_config =
{
    .retrigger = CY_DMA_RETRIG_4CYC,
    .interruptType = CY_DMA_DESCR,
    .triggerOutType = CY_DMA_1ELEMENT,
    .channelState = CY_DMA_CHANNEL_ENABLED,
    .triggerInType = CY_DMA_1ELEMENT,
    .dataSize = CY_DMA_BYTE,
    .srcTransferSize = CY_DMA_TRANSFER_SIZE_WORD,
    .dstTransferSize = CY_DMA_TRANSFER_SIZE_DATA,
    .descriptorType = CY_DMA_SINGLE_TRANSFER,
    .srcAddress = NULL,
    .dstAddress = NULL,
    .srcXincrement = 0,
    .dstXincrement = 1,
    .xCount = 1,
    .srcYincrement = 1,
    .dstYincrement = 1,
    .yCount = 1,
    .nextDescriptor = &RxDma_Descriptor_0,
};
cy_stc_dma_descriptor_t RxDma_Descriptor_0 =
{
    .ctl = 0UL,
    .src = 0UL,
    .dst = 0UL,
    .xCtl = 0UL,
    .yCtl = 0UL,
    .nextPtr = 0UL,
};
cy_stc_dma_descriptor_t RxDma_Descriptor_1 =
{
    .ctl = 0UL,
    .src = 0UL,
    .dst = 0UL,
    .xCtl = 0UL,
    .yCtl = 0UL,
    .nextPtr = 0UL,
};
const cy_stc_dma_channel_config_t RxDma_channelConfig =
{
    .descriptor = &RxDma_Descriptor_0,
    .preemptable = false,
    .priority = 3,
    .enable = false,
    .bufferable = false,
};
const cy_stc_dma_crc_config_t RxDma_crcConfig =
{
    .dataReverse = false,
    .dataXor = 0,
    .reminderReverse = false,
    .reminderXor = 0,
    .polynomial = 79764919,
};
#if defined (CY_USING_HAL)
    const cyhal_resource_inst_t RxDma_obj =
    {
        .type = CYHAL_RSC_DMA,
        .block_num = 0U,
        .channel_num = RxDma_CHANNEL,
    };
#endif //defined (CY_USING_HAL)


void init_cycfg_dmas(void)
{
#if defined (CY_USING_HAL)
    cyhal_hwmgr_reserve(&TxDma_obj);
#endif //defined (CY_USING_HAL)

#if defined (CY_USING_HAL)
    cyhal_hwmgr_reserve(&RxDma_obj);
#endif //defined (CY_USING_HAL)
}
