/**
 *******************************************************************************
 * @file  tca9539.h
 * @brief This file contains all the functions prototypes of the TCA9539 driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __TCA9539_H__
#define __TCA9539_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup Components
 * @{
 */

/**
 * @addtogroup TCA9539
  * @{
  */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup TCA9539_Global_Types TCA9539 Global Types
 * @{
 */

/**
 * @brief TCA9539 low layer structure definition
 */
typedef struct {
    /* Methods */
    void (*Init)(void);
    void (*Write)(const uint8_t *, const uint8_t *, uint32_t);
    void (*Read)(const uint8_t *, uint8_t *, uint32_t);
    void (*Reset)(void);
    void (*IntInit)(void);
} stc_tca9539_ll_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TCA9539_Global_Macros TCA9539 Global Macros
 * @{
 */

/**
 * @defgroup TCA9539_REGISTER_Definition TCA9539 Register Definition
 * @{
 */
#define TCA9539_REG_INPUT_PORT0         (0x00U)
#define TCA9539_REG_INPUT_PORT1         (0x01U)
#define TCA9539_REG_OUTPUT_PORT0        (0x02U)
#define TCA9539_REG_OUTPUT_PORT1        (0x03U)
#define TCA9539_REG_INVERT_PORT0        (0x04U)
#define TCA9539_REG_INVERT_PORT1        (0x05U)
#define TCA9539_REG_CONFIG_PORT0        (0x06U)
#define TCA9539_REG_CONFIG_PORT1        (0x07U)
/**
 * @}
 */

/**
 * @defgroup TCA9539_Port_Definition TCA9539 Port Definition
 * @{
 */
#define TCA9539_IO_PORT0                (0x00U)
#define TCA9539_IO_PORT1                (0x01U)
/**
 * @}
 */

/**
 * @defgroup TCA9539_Pin_Definition TCA9539 Pin Definition
 * @{
 */
#define TCA9539_IO_PIN0                 (0x01U)
#define TCA9539_IO_PIN1                 (0x02U)
#define TCA9539_IO_PIN2                 (0x04U)
#define TCA9539_IO_PIN3                 (0x08U)
#define TCA9539_IO_PIN4                 (0x10U)
#define TCA9539_IO_PIN5                 (0x20U)
#define TCA9539_IO_PIN6                 (0x40U)
#define TCA9539_IO_PIN7                 (0x80U)
#define TCA9539_IO_PIN_ALL              (0xFFU)
/**
 * @}
 */

/**
 * @defgroup TCA9539_Direction_Definition TCA9539 Direction Definition
 * @{
 */
#define TCA9539_DIR_OUT                 (0x00U)
#define TCA9539_DIR_IN                  (0x01U)
/**
 * @}
 */

/**
 * @defgroup TCA9539_Pin_State_Definition TCA9539 Pin State Definition
 * @{
 */
#define TCA9539_PIN_RESET               (0x00U)
#define TCA9539_PIN_SET                 (0x01U)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @defgroup TCA9539_Global_Functions TCA9539 Global Functions
 * @{
 */
int32_t TCA9539_Init(const stc_tca9539_ll_t *pstcTca9539LL);
int32_t TCA9539_IntInit(const stc_tca9539_ll_t *pstcTca9539LL);
int32_t TCA9539_Reset(const stc_tca9539_ll_t *pstcTca9539LL);

int32_t TCA9539_WritePin(const stc_tca9539_ll_t *pstcTca9539LL, uint8_t u8Port, uint8_t u8Pin, uint8_t u8PinState);
int32_t TCA9539_ReadPin(const stc_tca9539_ll_t *pstcTca9539LL, uint8_t u8Port, uint8_t u8Pin, uint8_t *pu8PinState);
int32_t TCA9539_TogglePin(const stc_tca9539_ll_t *pstcTca9539LL, uint8_t u8Port, uint8_t u8Pin);
int32_t TCA9539_ConfigPin(const stc_tca9539_ll_t *pstcTca9539LL, uint8_t u8Port, uint8_t u8Pin, uint8_t u8Dir);

/**
 * @}
 */

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

#endif /* __TCA9539_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
