/*
 *  Change Logs:
 *  Date            Author          Notes
 *  2021-09-10      swa          the first version
 *
 * Copyright (C) 2021 Shanghai Eastsoft Microelectronics Co., Ltd. All rights reserved.
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
 *
 */

#ifndef __ES_CONF_INFO_DMA_H__
#define __ES_CONF_INFO_DMA_H__

#include "es_conf_info_map.h"
#include <rtdevice.h>
#include <ald_dma.h>
#ifdef BSP_USING_DMA0
#define   ES_CONF_DMA_ENABLE
#endif

enum ES_DMA_CHANNELS
{
#if defined(ES_CONF_UART0_DMA_TX)||defined(BSP_UART0_TX_USING_DMA)
    ES_UART0_DMATX_CHANNEL,
#endif
#if defined(ES_CONF_UART0_DMA_RX)||defined(BSP_UART0_RX_USING_DMA)
    ES_UART0_DMARX_CHANNEL,
#endif
#if defined(ES_CONF_UART1_DMA_TX)||defined(BSP_UART1_TX_USING_DMA)
    ES_UART1_DMATX_CHANNEL,
#endif
#if defined(ES_CONF_UART1_DMA_RX)||defined(BSP_UART1_RX_USING_DMA)
    ES_UART1_DMARX_CHANNEL,
#endif
#if defined(ES_CONF_UART2_DMA_TX)||defined(BSP_UART2_TX_USING_DMA)
    ES_UART2_DMATX_CHANNEL,
#endif
#if defined(ES_CONF_UART2_DMA_RX)||defined(BSP_UART2_RX_USING_DMA)
    ES_UART2_DMARX_CHANNEL,
#endif
#if defined(ES_CONF_UART3_DMA_TX)||defined(BSP_UART3_TX_USING_DMA)
    ES_UART3_DMATX_CHANNEL,
#endif
#if defined(ES_CONF_UART3_DMA_RX)||defined(BSP_UART3_RX_USING_DMA)
    ES_UART3_DMARX_CHANNEL,
#endif
#if defined(ES_CONF_UART4_DMA_TX)||defined(BSP_UART4_TX_USING_DMA)
    ES_UART4_DMATX_CHANNEL,
#endif
#if defined(ES_CONF_UART4_DMA_RX)||defined(BSP_UART4_RX_USING_DMA)
    ES_UART4_DMARX_CHANNEL,
#endif
#if defined(ES_CONF_UART5_DMA_TX)||defined(BSP_UART5_TX_USING_DMA)
    ES_UART5_DMATX_CHANNEL,
#endif
#if defined(ES_CONF_UART5_DMA_RX)||defined(BSP_UART5_RX_USING_DMA)
    ES_UART5_DMARX_CHANNEL,
#endif
    ES_DMA_CHANNEL_NUM
};
#define ES_DMA_INVAILD_CHANNEL (DMA_CH_COUNT)
#define ES_DMA_USER_CHANNEL (ES_DMA_CHANNEL_NUM)

#endif /* __ES_CONF_INFO_DMA_H__ */
