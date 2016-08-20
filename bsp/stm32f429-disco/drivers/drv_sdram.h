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


#define SDRAM_BANK_ADDR     ((uint32_t)0xD0000000)

/**
  * @brief  FMC SDRAM Memory Width
  */
/* #define SDRAM_MEMORY_WIDTH   FMC_SDMemory_Width_8b  */
#define SDRAM_MEMORY_WIDTH    FMC_SDMemory_Width_16b

/**
  * @brief  FMC SDRAM CAS Latency
  */
/* #define SDRAM_CAS_LATENCY   FMC_CAS_Latency_2  */
#define SDRAM_CAS_LATENCY    FMC_CAS_Latency_3

/**
  * @brief  FMC SDRAM Memory clock period
  */
#define SDCLOCK_PERIOD    FMC_SDClock_Period_2        /* Default configuration used with LCD */
/* #define SDCLOCK_PERIOD    FMC_SDClock_Period_3 */

/**
  * @brief  FMC SDRAM Memory Read Burst feature
  */
#define SDRAM_READBURST    FMC_Read_Burst_Disable    /* Default configuration used with LCD */
/* #define SDRAM_READBURST    FMC_Read_Burst_Enable  */

/**
  * @brief  FMC SDRAM Bank Remap
  */
/* #define SDRAM_BANK_REMAP */



/**
 * @brief Uncomment the line below if you want to use user defined Delay function
 *        (for precise timing), otherwise default _delay_ function defined within
 *         this driver is used (less precise timing).
 */

/* #define USE_Delay */

#ifdef USE_Delay
  #define __Delay     Delay      /*  User can provide more timing precise __Delay function
                                    (with 10ms time base), using SysTick for example */
#else
  #define __Delay     delay      /*  Default __Delay function with less precise timing */
#endif

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
