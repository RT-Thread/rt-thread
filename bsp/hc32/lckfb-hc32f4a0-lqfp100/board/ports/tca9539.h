/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
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

/**
 * @defgroup HC32F4A0_EV_IO_Function_Sel Expand IO function definition
 * @{
 */
#define EIO_USBFS_OC                    (TCA9539_IO_PIN0)   /* USBFS over-current, input */
#define EIO_USBHS_OC                    (TCA9539_IO_PIN1)   /* USBHS over-current, input */
#define EIO_SDIC1_CD                    (TCA9539_IO_PIN2)   /* SDIC1 card detect, input */
#define EIO_SCI_CD                      (TCA9539_IO_PIN3)   /* Smart card detect, input */
#define EIO_TOUCH_INT                   (TCA9539_IO_PIN4)   /* Touch screen interrupt, input */
#define EIO_LIN_SLEEP                   (TCA9539_IO_PIN5)   /* LIN PHY sleep, output */
#define EIO_RTCS_CTRST                  (TCA9539_IO_PIN6)   /* 'CS' for Resistor touch panel or 'Reset' for Cap touch panel, output */
#define EIO_LCD_RST                     (TCA9539_IO_PIN7)   /* LCD panel reset, output */

#define EIO_CAM_RST                     (TCA9539_IO_PIN0)   /* Camera module reset, output */
#define EIO_CAM_STB                     (TCA9539_IO_PIN1)   /* Camera module standby, output */
#define EIO_USB3300_RST                 (TCA9539_IO_PIN2)   /* USBHS PHY USB3300 reset, output */
#define EIO_ETH_RST                     (TCA9539_IO_PIN3)   /* ETH PHY reset, output */
#define EIO_CAN_STB                     (TCA9539_IO_PIN4)   /* CAN PHY standby, output */
#define EIO_LED_RED                     (TCA9539_IO_PIN5)   /* Red LED, output */
#define EIO_LED_YELLOW                  (TCA9539_IO_PIN6)   /* Yellow LED, output */
#define EIO_LED_BLUE                    (TCA9539_IO_PIN7)   /* Blue LED, output */
/**
 * @}
 */

/**
 * @defgroup BSP_LED_PortPin_Sel BSP LED port/pin definition
 * @{
 */
#define LED_PORT                        (TCA9539_IO_PORT1)
#define LED_RED_PORT                    (TCA9539_IO_PORT1)
#define LED_RED_PIN                     (EIO_LED_RED)
#define LED_YELLOW_PORT                 (TCA9539_IO_PORT1)
#define LED_YELLOW_PIN                  (EIO_LED_YELLOW)
#define LED_BLUE_PORT                   (TCA9539_IO_PORT1)
#define LED_BLUE_PIN                    (EIO_LED_BLUE)
/**
 * @}
 */

/**
 * @defgroup  BSP CAN PHY STB port/pin definition
 * @{
 */
#define CAN_STB_PORT                    (TCA9539_IO_PORT1)
#define CAN_STB_PIN                     (EIO_CAN_STB)
/**
 * @}
 */

int TCA9539_Init(void);
rt_err_t TCA9539_WritePin(uint8_t u8Port, uint8_t u8Pin, uint8_t u8PinState);
rt_err_t TCA9539_ReadPin(uint8_t u8Port, uint8_t u8Pin, uint8_t *pu8PinState);
rt_err_t TCA9539_TogglePin(uint8_t u8Port, uint8_t u8Pin);
rt_err_t TCA9539_ConfigPin(uint8_t u8Port, uint8_t u8Pin, uint8_t u8Dir);

#endif
