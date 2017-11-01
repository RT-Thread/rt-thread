/*
 * File      : drv_sdram.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2016 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-08-20     xuzhuoyi     The first version for STM32F42x
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DRV_SDRAM_H
#define __DRV_SDRAM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <rtthread.h>
#include <board.h>


#define SDRAM_BANK_ADDR                 ((uint32_t)0XC0000000)

/* #define SDRAM_MEMORY_WIDTH            FMC_SDRAM_MEM_BUS_WIDTH_8 */
#define SDRAM_MEMORY_WIDTH            FMC_SDRAM_MEM_BUS_WIDTH_16

#define SDCLOCK_PERIOD                   FMC_SDRAM_CLOCK_PERIOD_2 
/* #define SDCLOCK_PERIOD                FMC_SDRAM_CLOCK_PERIOD_3 */

#define SDRAM_TIMEOUT     ((uint32_t)0xFFFF)

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

#define BUFFER_SIZE         ((uint32_t)0x0100)
#define WRITE_READ_ADDR     ((uint32_t)0x0800)
#define REFRESH_COUNT       ((uint32_t)0x02AB)   /* SDRAM refresh counter (90MHz SD clock) */
/**
  * @}
  */

/** @defgroup STM32429I_DISCO_SDRAM_Exported_Functions
  * @{
  */
void  SDRAM_Init(void);
void  SDRAM_GPIOConfig(void);
void  SDRAM_InitSequence(void);
void  SDRAM_WriteBuffer(uint32_t* pBuffer, uint32_t uwWriteAddress, uint32_t uwBufferSize);
void  SDRAM_ReadBuffer(uint32_t* pBuffer, uint32_t uwReadAddress, uint32_t uwBufferSize);

#ifdef __cplusplus
}
#endif

#endif
