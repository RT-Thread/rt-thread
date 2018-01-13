/*
 * File      : drv_sdcard.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2018, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author         Notes
 * 2018-01-13     Liu2guang      the first version.
 */

#include <rtthread.h>  
#include <rtdevice.h> 
#include "drv_sdcard.h"
#include "stm32f1xx.h" 

#define SD_TIMEOUT ((uint32_t)0x100000)
 
static SD_HandleTypeDef hsdcard = 
{
    .Instance                 = SDIO,
    .Init.ClockEdge           = SDIO_CLOCK_EDGE_RISING,
    .Init.ClockBypass         = SDIO_CLOCK_BYPASS_DISABLE,
    .Init.ClockPowerSave      = SDIO_CLOCK_POWER_SAVE_DISABLE,
    .Init.BusWide             = SDIO_BUS_WIDE_1B,
    .Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_ENABLE,
    .Init.ClockDiv            = 2
}; 

#if defined(USING_SD_RX_DMA)
static DMA_HandleTypeDef hdma = 
{
    .Instance                 = DMA2_Channel4, 
    .Init.Direction           = DMA_PERIPH_TO_MEMORY,
    .Init.PeriphInc           = DMA_PINC_DISABLE,
    .Init.MemInc              = DMA_MINC_ENABLE,
    .Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD,
    .Init.MemDataAlignment    = DMA_MDATAALIGN_WORD,
    .Init.Mode                = DMA_NORMAL,
    .Init.Priority            = DMA_PRIORITY_HIGH
};
#endif

#if !defined(USING_SD_RX_DMA) && defined(USING_SD_TX_DMA) 
static DMA_HandleTypeDef hdma = 
{
    .Instance                 = DMA2_Channel4, 
    .Init.Direction           = DMA_MEMORY_TO_PERIPH,
    .Init.PeriphInc           = DMA_MINC_ENABLE,
    .Init.MemInc              = DMA_PINC_DISABLE, 
    .Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD,
    .Init.MemDataAlignment    = DMA_MDATAALIGN_WORD,
    .Init.Mode                = DMA_NORMAL,
    .Init.Priority            = DMA_PRIORITY_HIGH
};
#endif

static struct rt_semaphore sd_lock;

void SDIO_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_SD_IRQHandler(&hsdcard);
    rt_interrupt_leave();
}

#if defined(USING_SD_RX_DMA) || defined(USING_SD_TX_DMA) 
void DMA2_Channel4_5_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_DMA_IRQHandler(&hdma); 
    rt_interrupt_leave();
}
#endif

uint8_t stm32_read_blocks(uint32_t *data, uint32_t addr, uint32_t num)
{
    uint32_t timeout = 0;
    HAL_SD_StateTypeDef state_return;
    HAL_SD_CardStateTypeDef sd_card_state_return;
    
#if defined(USING_SD_RX_DMA) && defined(USING_SD_TX_DMA) 
    hdma.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma.Init.PeriphInc = DMA_PINC_DISABLE; 
    hdma.Init.MemInc    = DMA_MINC_ENABLE; 
    HAL_DMA_DeInit(&hdma);
    HAL_DMA_Init(&hdma); 
#endif

#if defined(USING_SD_RX_DMA)
    if(HAL_SD_ReadBlocks_DMA(&hsdcard, (uint8_t *)data, addr, num) != HAL_OK)
#else
    if(HAL_SD_ReadBlocks(&hsdcard, (uint8_t *)data, addr, num, SD_TIMEOUT) != HAL_OK)
#endif
    {
        return RT_EIO;
    }
    
    do
    {
        state_return = HAL_SD_GetState(&hsdcard);
        timeout++;
    }while((HAL_SD_STATE_BUSY == state_return) && (SD_TIMEOUT > timeout));
    
    if(HAL_SD_STATE_READY != state_return)
    {
        return RT_ERROR; 
    }
    
    do
    {
        sd_card_state_return = HAL_SD_GetCardState(&hsdcard);
        timeout++;
    }while((HAL_SD_CARD_TRANSFER != sd_card_state_return) && (SD_TIMEOUT > timeout));
    
    if(SD_TIMEOUT <= timeout)
    {
        return RT_ETIMEOUT; 
    }

    return RT_EOK; 
}

uint8_t stm32_write_blocks(uint32_t *data, uint32_t addr, uint32_t num)
{
    uint32_t timeout = 0;
    HAL_SD_StateTypeDef state_return;
    HAL_SD_CardStateTypeDef sd_card_state_return;
    
#if defined(USING_SD_RX_DMA) && defined(USING_SD_TX_DMA) 
    hdma.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma.Init.PeriphInc = DMA_MINC_ENABLE; 
    hdma.Init.MemInc    = DMA_PINC_DISABLE; 
    HAL_DMA_DeInit(&hdma);
    HAL_DMA_Init(&hdma); 
#endif
    
#if defined(USING_SD_TX_DMA)
    if(HAL_SD_WriteBlocks_DMA(&hsdcard, (uint8_t *)data, addr, num) != HAL_OK)
#else
    if(HAL_SD_WriteBlocks(&hsdcard, (uint8_t *)data, addr, num, SD_TIMEOUT) != HAL_OK)
#endif
    {
        return RT_ERROR;
    }
    
    do
    {
        state_return = HAL_SD_GetState(&hsdcard);
        timeout++;
    }while((HAL_SD_STATE_BUSY == state_return) && (SD_TIMEOUT > timeout));
    
    if(HAL_SD_STATE_READY != state_return)
    {
        return RT_ERROR; 
    }
    
    do
    {
        sd_card_state_return = HAL_SD_GetCardState(&hsdcard);
        timeout++;
    }while((HAL_SD_CARD_TRANSFER != sd_card_state_return) && (SD_TIMEOUT > timeout));
    
    if(SD_TIMEOUT <= timeout)
    {
        return RT_ETIMEOUT; 
    }
    
    return RT_EOK; 
}

static rt_err_t stm32_sdcard_init(rt_device_t dev)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    if(rt_sem_init(&sd_lock, "sdlock", 1, RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        return RT_ERROR;
    }
    
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    GPIO_InitStruct.Pin   = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | 
                            GPIO_PIN_12;
    GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP; 
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; 
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct); 
    
    GPIO_InitStruct.Pin   = GPIO_PIN_2;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    
#if defined(USING_SD_RX_DMA) || defined(USING_SD_TX_DMA) 
    __HAL_RCC_DMA2_CLK_ENABLE();
    
#if defined(USING_SD_RX_DMA)
    __HAL_LINKDMA(&hsdcard, hdmarx, hdma); 
#endif

#if defined(USING_SD_TX_DMA)
    __HAL_LINKDMA(&hsdcard, hdmatx, hdma); 
#endif
    
    HAL_DMA_DeInit(&hdma);
    if(HAL_DMA_Init(&hdma) != HAL_OK)
    {
        rt_kprintf("HAL_DMA_Init error\n");
        return RT_EIO;
    }
#endif
    
    HAL_NVIC_SetPriority(DMA2_Channel4_5_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(DMA2_Channel4_5_IRQn); 
    
    __HAL_RCC_SDIO_CLK_ENABLE();
    
    HAL_SD_DeInit(&hsdcard);
    if(HAL_SD_Init(&hsdcard) != HAL_OK)
    {
        rt_kprintf("HAL_SD_Init error\n");
        return RT_EIO; 
    }
    
    HAL_NVIC_SetPriority(SDIO_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(SDIO_IRQn);
    
    if(HAL_SD_ConfigWideBusOperation(&hsdcard, SDIO_BUS_WIDE_4B) != HAL_OK) 
    {
        rt_kprintf("HAL_SD_ConfigWideBusOperation error\n");
        return RT_EIO;
    }
    
    return RT_EOK; 
}

static rt_err_t stm32_sdcard_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK; 
}

static rt_err_t stm32_sdcard_close(rt_device_t dev) 
{
    return RT_EOK; 
} 

static rt_size_t stm32_sdcard_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    int ret = RT_EOK; 
    
    rt_sem_take(&sd_lock, RT_WAITING_FOREVER);
    ret = stm32_read_blocks((uint32_t *)buffer, pos, size); 
    rt_sem_release(&sd_lock);
    
    if(ret != RT_EOK)
    {
        return ret; 
    }
    
    return size; 
} 

static rt_size_t stm32_sdcard_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    int ret = RT_EOK;
    
    rt_sem_take(&sd_lock, RT_WAITING_FOREVER);
    ret = stm32_write_blocks((uint32_t *)buffer, pos, size); 
    rt_sem_release(&sd_lock);
    
    if(ret != RT_EOK)
    {
        return ret; 
    }
    
    return size; 
} 

static rt_err_t stm32_sdcard_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);
    
    // RT_DEVICE_CTRL_BLK_GETGEOME 
    if(cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        HAL_SD_CardInfoTypeDef sdcard_info;
        struct rt_device_blk_geometry *geometry;
        
        HAL_SD_GetCardInfo(&hsdcard, &sdcard_info);
        
        geometry = (struct rt_device_blk_geometry *)args;

        geometry->bytes_per_sector = 512;
        geometry->block_size       = sdcard_info.BlockSize;
        geometry->sector_count     = sdcard_info.BlockNbr;
    }

    return RT_EOK;
} 

static struct rt_device device = 
{
    .type    = RT_Device_Class_Block, 
    .init    = stm32_sdcard_init,
    .open    = stm32_sdcard_open, 
    .read    = stm32_sdcard_read,
    .write   = stm32_sdcard_write,
    .control = stm32_sdcard_control,
    .close   = stm32_sdcard_close
};

/* SDCARDÇý¶¯³õÊ¼»¯ */ 
int rt_hw_sdcard_init(void)
{
    rt_err_t ret = RT_EOK; 
    
    ret = rt_device_register(&device, "sd0", 
                             RT_DEVICE_FLAG_REMOVABLE | 
                             RT_DEVICE_FLAG_RDWR      | 
                             RT_DEVICE_FLAG_STANDALONE); 
    if(ret != RT_EOK)
    {
        return ret; 
    }
    
    return RT_EOK; 
}
INIT_BOARD_EXPORT(rt_hw_sdcard_init); 
