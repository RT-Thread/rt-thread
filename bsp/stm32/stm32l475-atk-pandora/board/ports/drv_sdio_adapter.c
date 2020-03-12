/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <rthw.h>
#include <drivers/mmcsd_core.h>
#include <drivers/sdio.h>

#include "stm32l4xx.h"

#ifdef BSP_USING_STM32_SDIO

#include <stm32_sdio.h>

static DMA_HandleTypeDef SDTxDMAHandler;
static DMA_HandleTypeDef SDRxDMAHandler;

static struct rt_mmcsd_host *host;

void SDMMC1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    /* Process All SDIO Interrupt Sources */
    rthw_sdio_irq_process(host);

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
  * @brief  Configures the DMA2 Channel4 for SDIO Tx request.
  * @param  BufferSRC: pointer to the source buffer
  * @param  BufferSize: buffer size
  * @retval None
  */
void SD_LowLevel_DMA_TxConfig(uint32_t *src, uint32_t *dst, uint32_t BufferSize)
{
    DMA2_Channel4->CCR &= ~0x00000001;

    DMA2->IFCR = DMA_ISR_GIF1 << 4;
    
    DMA2_CSELR->CSELR &= ~(0xf << (3 * 4));   // channel 4
    DMA2_CSELR->CSELR |= (uint32_t) (0x07 << (3 * 4)); 
    
    DMA2_Channel4->CCR   = DMA_MEMORY_TO_PERIPH | DMA_PINC_DISABLE | DMA_MINC_ENABLE | \
                           DMA_PDATAALIGN_WORD | DMA_MDATAALIGN_WORD | DMA_NORMAL | DMA_PRIORITY_MEDIUM;
    DMA2_Channel4->CNDTR = BufferSize;
    DMA2_Channel4->CPAR  = (uint32_t)dst;
    DMA2_Channel4->CMAR = (uint32_t)src;

    DMA2_Channel4->CCR  |= 0x00000001;
    
//    HAL_DMA_Start(&SDTxDMAHandler, (uint32_t)src, (uint32_t)dst, BufferSize);
}

/**
  * @brief  Configures the DMA2 Channel4 for SDIO Rx request.
  * @param  BufferDST: pointer to the destination buffer
  * @param  BufferSize: buffer size
  * @retval None
  */
void SD_LowLevel_DMA_RxConfig(uint32_t *src, uint32_t *dst, uint32_t BufferSize)
{

    DMA2_Channel4->CCR &= ~0x00000001;

    DMA2->IFCR = DMA_ISR_GIF1 << 4;
    
    DMA2_CSELR->CSELR &= ~(0xf << (3 * 4));   // channel 4
    DMA2_CSELR->CSELR |= (uint32_t) (0x07 << (3 * 4)); 

    DMA2_Channel4->CCR   = DMA_PERIPH_TO_MEMORY | DMA_PINC_DISABLE | DMA_MINC_ENABLE | \
                           DMA_PDATAALIGN_WORD | DMA_MDATAALIGN_WORD | DMA_NORMAL | DMA_PRIORITY_MEDIUM;
    DMA2_Channel4->CNDTR = BufferSize;
    DMA2_Channel4->CPAR  = (uint32_t)src;
    DMA2_Channel4->CMAR = (uint32_t)dst;

    DMA2_Channel4->CCR  |= 0x00000001;
}

void SD_LowLevel_Init(void)
{
    {
        // clock enable
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        __HAL_RCC_DMA2_CLK_ENABLE();
        __HAL_RCC_SDMMC1_CLK_ENABLE();
    }

    {
        HAL_NVIC_EnableIRQ(SDMMC1_IRQn);
    }

    {
        // init sdio hardware
        GPIO_InitTypeDef GPIO_InitStruct;

        /*Configure GPIO pin Output Level */
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);
        GPIO_InitStruct.Pin = GPIO_PIN_1;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
        rt_thread_delay(1);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET);

        /* Setup GPIO pins for SDIO data & clock */
        /**SDMMC1 GPIO Configuration
        PC8     ------> SDMMC1_D0
        PC9     ------> SDMMC1_D1
        PC10     ------> SDMMC1_D2
        PC11     ------> SDMMC1_D3
        PC12     ------> SDMMC1_CK
        PD2     ------> SDMMC1_CMD
        */
        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
        
        GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_10 | GPIO_PIN_11
                              | GPIO_PIN_12;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;

        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    }

    {
    }
}

static rt_uint32_t stm32_sdio_clock_get(struct stm32_sdio *hw_sdio)
{
    return HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SDMMC1);
}

static rt_err_t DMA_TxConfig(rt_uint32_t *src, rt_uint32_t *dst, int Size)
{
    SD_LowLevel_DMA_TxConfig((uint32_t *)src, (uint32_t *)dst, Size / 4);
    return RT_EOK;
}

static rt_err_t DMA_RxConfig(rt_uint32_t *src, rt_uint32_t *dst, int Size)
{
    SD_LowLevel_DMA_RxConfig((uint32_t *)src, (uint32_t *)dst, Size / 4);
    return RT_EOK;
}

int stm32f4xx_sdio_init(void)
{
    struct stm32_sdio_des sdio_des;

    SD_LowLevel_Init();

    sdio_des.clk_get = stm32_sdio_clock_get;
    sdio_des.hw_sdio = (struct stm32_sdio *)0x40012800U;
    sdio_des.rxconfig = DMA_RxConfig;
    sdio_des.txconfig = DMA_TxConfig;

    host = sdio_host_create(&sdio_des);
    if (host == RT_NULL)
    {
        rt_kprintf("%s host create fail\n");
        return -1;
    }

    return 0;
}
INIT_DEVICE_EXPORT(stm32f4xx_sdio_init);

#endif
