/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-4-30     misonyo     the first version.
 */

#ifndef __DRV_SOUND_H_
#define __DRV_SOUND_H_

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <rtdef.h>

#include <rthw.h>
#include "fsl_sai.h"
#include "fsl_dmamux.h"
#include "fsl_sai_edma.h"

#define AUD_DMA_FIFO_SIZE (2048)
#define CODEC_I2C_NAME ("i2c1")
/* Select Audio/Video PLL (786.48 MHz) as sai1 clock source */
#define DEMO_SAI1_CLOCK_SOURCE_SELECT (2U)
/* Clock pre divider for sai1 clock source */
#define DEMO_SAI1_CLOCK_SOURCE_PRE_DIVIDER (0U)
/* Clock divider for sai1 clock source */
#define DEMO_SAI1_CLOCK_SOURCE_DIVIDER (63U)
/* Get frequency of sai1 clock */
#define AUD_BLOCK_CNT   2
#define AUD_BLOCK_SIZE  1024
#define AUD_FIFO_SIZE   (AUD_BLOCK_SIZE * AUD_BLOCK_CNT)
#define DEMO_SAI_CLK_FREQ                                                        \
    (CLOCK_GetFreq(kCLOCK_AudioPllClk) / (DEMO_SAI1_CLOCK_SOURCE_DIVIDER + 1U) / \
     (DEMO_SAI1_CLOCK_SOURCE_PRE_DIVIDER + 1U))


#define AUD_DMA_FIFO_SIZE (2048)
struct saidma_tx_config
{
    edma_handle_t edma;
    rt_uint8_t channel;
    dma_request_source_t request;
    sai_edma_handle_t txHandle;
};
struct saidma_rx_config
{
    edma_handle_t edma;
    rt_uint8_t channel;
    dma_request_source_t request;
    sai_edma_handle_t rxHandle;
};

struct drv_sai {
    I2S_Type *base;
    IRQn_Type irqn;
    struct saidma_tx_config *dma_tx;
    struct saidma_rx_config *dma_rx;
    rt_uint8_t dma_flag;
    int txBlockIndex;
    int rxBlockIndex;
};

void sai_init(void);
int rt_hw_sound_init(void);

#endif
