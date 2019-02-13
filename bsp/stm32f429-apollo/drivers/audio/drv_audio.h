/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-14     ZeroFree     first implementation
 */

#ifndef __DRV_AUDIO_H__
#define __DRV_AUDIO_H__

#include <rtthread.h>
#include <drivers/audio.h>
#include <audio_pipe.h>

/* SAIA DMA Stream TX definitions */
#define SAIA_TX_DMAx_CLK_ENABLE()        __HAL_RCC_DMA2_CLK_ENABLE()
#define SAIA_TX_DMAx_CLK_DISABLE()       __HAL_RCC_DMA2_CLK_DISABLE()
#define SAIA_TX_DMAx_STREAM              DMA2_Stream3
#define SAIA_TX_DMAx_CHANNEL             DMA_CHANNEL_0
#define SAIA_TX_DMAx_IRQ                 DMA2_Stream3_IRQn
#define SAIA_TX_DMAx_PERIPH_DATA_SIZE    DMA_PDATAALIGN_HALFWORD
#define SAIA_TX_DMAx_MEM_DATA_SIZE       DMA_MDATAALIGN_HALFWORD
#define SAIA_TX_DMAx_IRQHandler          DMA2_Stream3_IRQHandler

/* SAIB DMA Stream TX definitions */
#define SAIA_RX_DMAx_CLK_ENABLE()        __HAL_RCC_DMA2_CLK_ENABLE()
#define SAIA_RX_DMAx_CLK_DISABLE()       __HAL_RCC_DMA2_CLK_DISABLE()
#define SAIA_RX_DMAx_STREAM              DMA2_Stream5
#define SAIA_RX_DMAx_CHANNEL             DMA_CHANNEL_0
#define SAIA_RX_DMAx_IRQ                 DMA2_Stream5_IRQn
#define SAIA_RX_DMAx_PERIPH_DATA_SIZE    DMA_PDATAALIGN_HALFWORD
#define SAIA_RX_DMAx_MEM_DATA_SIZE       DMA_MDATAALIGN_HALFWORD
#define SAIA_RX_DMAx_IRQHandler          DMA2_Stream5_IRQHandler

int SAIA_SampleRate_Set(uint32_t samplerate);
int rt_hw_audio_init(char *i2c_bus_name);

#endif
