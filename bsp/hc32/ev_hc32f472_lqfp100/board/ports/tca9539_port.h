/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#ifndef __TCA9539_PORT_H__
#define __TCA9539_PORT_H__

#include "tca9539.h"

/**
 * @defgroup HC32F472_EV_IO_Function_Sel Expand IO function definition
 * @{
 */
#define EIO_USBFS_OC                    (TCA9539_IO_PIN0)   /* USBFS over-current, input */
#define EIO_SCI_CD                      (TCA9539_IO_PIN1)   /* Smart card detect, input */
#define EIO_TOUCH_INT                   (TCA9539_IO_PIN2)   /* Touch screen interrupt, input */
#define EIO_RTCS_CTRST                  (TCA9539_IO_PIN5)   /* 'CS' for Resistor touch panel or 'Reset' for Cap touch panel, output */
#define EIO_LCD_RST                     (TCA9539_IO_PIN6)   /* LCD panel reset, output */
#define EIO_LCD_BKL                     (TCA9539_IO_PIN7)   /* LCD panel back light, output */

#define EIO_LIN2_SLEEP                  (TCA9539_IO_PIN0)   /* LIN1 PHY sleep, output */
#define EIO_LIN1_SLEEP                  (TCA9539_IO_PIN1)   /* LIN2 PHY sleep, output */
#define EIO_CAN1_STB                    (TCA9539_IO_PIN2)   /* CAN1 PHY standby, output */
#define EIO_CAN2_STB                    (TCA9539_IO_PIN3)   /* CAN2 PHY standby, output */
#define EIO_CAN3_STB                    (TCA9539_IO_PIN4)   /* CAN3 PHY standby, output */
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
 * @defgroup BSP_CAN_PortPin_Sel BSP CAN PHY STB port/pin definition
 * @{
 */
#define CAN1_STB_PORT                   (TCA9539_IO_PORT1)
#define CAN1_STB_PIN                    (EIO_CAN1_STB)
#define CAN2_STB_PORT                   (TCA9539_IO_PORT1)
#define CAN2_STB_PIN                    (EIO_CAN2_STB)
#define CAN3_STB_PORT                   (TCA9539_IO_PORT1)
#define CAN3_STB_PIN                    (EIO_CAN3_STB)
/**
 * @}
 */

#endif
