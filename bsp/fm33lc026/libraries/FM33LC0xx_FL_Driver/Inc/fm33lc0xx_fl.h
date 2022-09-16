/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl.h
  * @author  FMSH Application Team
  * @brief   Header file of FL Driver Library
  *******************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * You can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  *******************************************************************************************************
  */

/* Define to prevent recursive inclusion --------------------------------------------------------------*/
#ifndef __FM33LC0XX_FL_H
#define __FM33LC0XX_FL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_conf.h"
#include "fm33lc0xx_fl_def.h"

/* Macros ---------------------------------------------------------------------------------------------*/
/** @defgroup FL_Exported_Macros FL Driver Library Exported Macros
  * @{
  */

/**
  * @brief FM33LC0xx FL Driver Library version number
  */
#define __FM33LC0xx_FL_VERSION_MAIN   (0x02) /*!< [31:24] main version */
#define __FM33LC0xx_FL_VERSION_SUB1   (0x03) /*!< [23:16] sub1 version */
#define __FM33LC0xx_FL_VERSION_SUB2   (0x01) /*!< [15:0]  sub2 version */
#define __FM33LC0xx_FL_VERSION        ((__FM33LC0xx_FL_VERSION_MAIN  << 24)\
                                         |(__FM33LC0xx_FL_VERSION_SUB1 << 16)\
                                         |(__FM33LC0xx_FL_VERSION_SUB2))

/**
  * @brief Macros used by delay support functions
  */
#define FL_DELAY_US                (SystemCoreClock/1000000)
#define FL_DELAY_MS                (SystemCoreClock/1000)

/**
  * @}
  */

/* Struct Defines -------------------------------------------------------------------------------------*/
/** @defgroup FL_ET_NVIC FL Driver Library NVIC Init Sturcture Defines
  * @{
  */

typedef struct
{
    /** 中断抢占优先级 */
    uint32_t preemptPriority;

} FL_NVIC_ConfigTypeDef;

/**
  * @}
  */

/* Exported Functions ---------------------------------------------------------------------------------*/
/** @defgroup FL_EF_DELAY   FL Driver Library Exported Delay Support Functions
  * @{
  */

void FL_DelayInit(void);
void FL_DelayUs(uint32_t count);
void FL_DelayMs(uint32_t count);
void FL_DelayUsStart(uint32_t count);
void FL_DelayMsStart(uint32_t count);
bool FL_DelayEnd(void);

/**
  * @}
  */

/** @defgroup FL_EF_INIT   FL Driver Library Exported Init Functions
  * @{
  */

void FL_Init(void);

/**
  * @}
  */

/** @defgroup FL_EF_NVIC   FL Driver Library Exported NVIC Configuration Functions
  * @{
  */

void FL_NVIC_Init(FL_NVIC_ConfigTypeDef *configStruct, IRQn_Type irq);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __FM33LC0XX_FL_H */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
