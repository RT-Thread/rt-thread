/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-20     CDT          first version
 */

#ifndef __TCA9539_H__
#define __TCA9539_H__

#include <rtdevice.h>

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

int TCA9539_Init(void);
rt_err_t TCA9539_WritePin(uint8_t u8Port, uint8_t u8Pin, uint8_t u8PinState);
rt_err_t TCA9539_ReadPin(uint8_t u8Port, uint8_t u8Pin, uint8_t *pu8PinState);
rt_err_t TCA9539_TogglePin(uint8_t u8Port, uint8_t u8Pin);
rt_err_t TCA9539_ConfigPin(uint8_t u8Port, uint8_t u8Pin, uint8_t u8Dir);

#endif
