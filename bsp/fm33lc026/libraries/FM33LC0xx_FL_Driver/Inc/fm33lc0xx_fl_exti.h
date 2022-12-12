/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_exti.h
  * @author  FMSH Application Team
  * @brief   Head file of EXTI FL Module
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


/* Define to prevent recursive inclusion---------------------------------------------------------------*/
#ifndef __FM33LC0XX_FL_EXTI_H
#define __FM33LC0XX_FL_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup EXTI EXTI
  * @brief EXTI FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup EXTI_FL_ES_INIT EXTI Exported Init structures
  * @{
  */

/**
  * @brief FL EXTI Common Init Sturcture definition
  */
typedef struct
{
    /*! EXTI时钟源配置 */
    uint32_t clockSource;

} FL_EXTI_CommonInitTypeDef;

/**
  * @brief FL EXTI Init Sturcture definition
  */
typedef struct
{
    /*! EXTI输入配置 */
    uint32_t input;

    /*! EXTI触发边沿配置 */
    uint32_t triggerEdge;

    /*! EXTI数字滤波配置 */
    uint32_t filter;

} FL_EXTI_InitTypeDef;

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup EXTI_FL_Exported_Constants EXTI Exported Constants
  * @{
  */



#define    FL_GPIO_EXTI_INPUT_GROUP0                              (0x0U << 0U)
#define    FL_GPIO_EXTI_INPUT_GROUP1                              (0x1U << 0U)
#define    FL_GPIO_EXTI_INPUT_GROUP2                              (0x2U << 0U)
#define    FL_GPIO_EXTI_INPUT_GROUP3                              (0x3U << 0U)



/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup EXTI_FL_Exported_Functions EXTI Exported Functions
  * @{
  */

/**
  * @}
  */

/** @defgroup EXTI_FL_EF_Init Initialization and de-initialization functions
  * @{
  */

FL_ErrorStatus  FL_EXTI_CommonInit(FL_EXTI_CommonInitTypeDef *init);
FL_ErrorStatus  FL_EXTI_CommonDeinit(void);
void            FL_EXTI_CommonStructInit(FL_EXTI_CommonInitTypeDef *init);

FL_ErrorStatus  FL_EXTI_Init(uint32_t extiLineX, FL_EXTI_InitTypeDef *init);
FL_ErrorStatus  FL_EXTI_DeInit(uint32_t extiLineX);
void            FL_EXTI_StructInit(FL_EXTI_InitTypeDef *init);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __FM33LC0XX_FL_EXTI_H */

/*************************Py_Code_Generator Version: 0.1-0.14-0.2 @ 2021-03-16*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
