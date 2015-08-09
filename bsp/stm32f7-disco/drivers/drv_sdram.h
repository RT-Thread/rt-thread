/*
 * File      : drv_sdram.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 *  2015-08-03     xiaonong     The first version for STM32F7
 */

#ifndef __DRV_SDRAM_H__
#define __DRV_SDRAM_H__

#include <rtthread.h>
#include <board.h>


/** @defgroup STM32746G_DISCOVERY_SDRAM_Exported_Constants STM32746G_DISCOVERY_SDRAM Exported Constants
  * @{
  */ 
#define SDRAM_DEVICE_ADDR  ((uint32_t)EXT_SDRAM_BEGIN)
#define SDRAM_DEVICE_SIZE  ((uint32_t)EXT_SDRAM_SIZE)  /* SDRAM device size in MBytes */

/* #define SDRAM_MEMORY_WIDTH            FMC_SDRAM_MEM_BUS_WIDTH_8  */
#define SDRAM_MEMORY_WIDTH               FMC_SDRAM_MEM_BUS_WIDTH_16

#define SDCLOCK_PERIOD                   FMC_SDRAM_CLOCK_PERIOD_2
/* #define SDCLOCK_PERIOD                FMC_SDRAM_CLOCK_PERIOD_3 */   

#define REFRESH_COUNT                    ((uint32_t)0x0603)   /* SDRAM refresh counter (100Mhz SD clock) */
   
#define SDRAM_TIMEOUT                    ((uint32_t)0xFFFF)

/* DMA definitions for SDRAM DMA transfer */
#define SDRAM_DMA_CLK_ENABLE                 __HAL_RCC_DMA2_CLK_ENABLE
#define SDRAM_DMA_CLK_DISABLE                __HAL_RCC_DMA2_CLK_DISABLE
#define SDRAM_DMA_CHANNEL                DMA_CHANNEL_0
#define SDRAM_DMA_STREAM                 DMA2_Stream0  
#define SDRAM_DMA_IRQn                   DMA2_Stream0_IRQn
#define SDRAM_DMA_IRQHandler             DMA2_Stream0_IRQHandler    
/**
  * @brief  FMC SDRAM Mode definition register defines
  */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000) 
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200) 

rt_err_t sdram_hw_init(void);
rt_err_t sdram_hw_deinit(void);
rt_err_t SDRAM_WriteDataDMA(uint32_t Address, uint32_t *Data, uint32_t DataSize);
rt_err_t SDRAM_WriteData(uint32_t Address, uint32_t *Data, uint32_t DataSize);
rt_err_t SDRAM_ReadDataDMA(uint32_t Address, uint32_t *Data, uint32_t DataSize);
rt_err_t SDRAM_ReadData(uint32_t Address, uint32_t *Data, uint32_t DataSize);

#endif
