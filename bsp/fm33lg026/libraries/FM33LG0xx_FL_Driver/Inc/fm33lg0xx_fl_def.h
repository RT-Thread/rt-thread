/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_def.h
  * @author  FMSH Application Team
  * @brief   Header file of FL Driver Library Defines
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
#ifndef __FM33LG0XX_FL_DEF_H
#define __FM33LG0XX_FL_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx.h"
#include "fm33_assert.h"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* Macros ---------------------------------------------------------------------------------------------*/
/** @defgroup FL_Exported_Macros FL Driver Library Private Macros
  * @{
  */

/**
  * @brief Bit-wise operation macros used by FL driver library functions
  */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#define CLEAR_REG(REG)        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

/**
  * @}
  */

/* Types ----------------------------------------------------------------------------------------------*/
/** @defgroup FL_PT_Return FL Driver Library Private Return Type Defines
  * @{
  */

typedef enum
{
    FL_RESET = 0U,
    FL_SET = !FL_RESET
} FL_FlagStatus, FL_ITStatus;

typedef enum
{
    FL_DISABLE = 0U,
    FL_ENABLE = !FL_DISABLE
} FL_FunState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == FL_DISABLE) || ((STATE) == FL_ENABLE))

typedef enum
{
    FL_FAIL = 0U,
    FL_PASS = !FL_FAIL
} FL_ErrorStatus;

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __FM33LG0XX_FL_DEF_H */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
