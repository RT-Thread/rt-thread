/**
 *******************************************************************************
 * @file  ev_hc32f448_lqfp80_tca9539.h
 * @brief This file contains all the functions prototypes of the
 *        ev_hc32f448_lqfp80_tca9539 driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
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
#ifndef __EV_HC32F448_LQFP80_TCA9539_H__
#define __EV_HC32F448_LQFP80_TCA9539_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "tca9539.h"
#include "ev_hc32f448_lqfp80.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F448_LQFP80
  * @{
  */

/**
 * @addtogroup EV_HC32F448_LQFP80_TCA9539
  * @{
  */

#if ((BSP_TCA9539_ENABLE == DDL_ON) && (BSP_EV_HC32F448_LQFP80 == BSP_EV_HC32F4XX))

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup BSP_TCA9539_I2C_Configure BSP TCA9539 I2C Configure
 * @{
 */
#define EIO_RST_PORT                    (GPIO_PORT_B)
#define EIO_RST_PIN                     (GPIO_PIN_15)

/* I2C unit define */
#define BSP_TCA9539_I2C_UNIT            (CM_I2C1)
#define BSP_TCA9539_I2C_FCG             (FCG1_PERIPH_I2C1)

/* Define port and pin for SDA and SCL */
#define BSP_TCA9539_I2C_SCL_PORT        (GPIO_PORT_E)
#define BSP_TCA9539_I2C_SCL_PIN         (GPIO_PIN_01)
#define BSP_TCA9539_I2C_SDA_PORT        (GPIO_PORT_E)
#define BSP_TCA9539_I2C_SDA_PIN         (GPIO_PIN_00)
#define BSP_TCA9539_I2C_SCL_FUNC        (GPIO_FUNC_49)
#define BSP_TCA9539_I2C_SDA_FUNC        (GPIO_FUNC_48)

/* Define for TCA9539 */
#define BSP_TCA9539_DEV_ADDR            (0x74U)
#define BSP_TCA9539_REG_ADDR_LEN        (1U)
/**
 * @}
 */

/**
 * @defgroup HC32F448_EV_IO_Exported_Constants IO Exported Constants
 * @{
 */

/**
 * @defgroup HC32F448_EV_IO_Port_Definition HC32F448_EV_IO Port Definition
 * @{
 */
#define EIO_PORT0                       (TCA9539_IO_PORT0)
#define EIO_PORT1                       (TCA9539_IO_PORT1)
/**
 * @}
 */

/**
 * @defgroup HC32F448_EV_IO_Direction_Definition HC32F448_EV_IO Direction Definition
 * @{
 */
#define EIO_DIR_OUT                     (TCA9539_DIR_OUT)
#define EIO_DIR_IN                      (TCA9539_DIR_IN)
/**
 * @}
 */

/**
 * @defgroup HC32F448_EV_IO_Pin_State_Definition HC32F448_EV_IO Pin State Definition
 * @{
 */
#define EIO_PIN_RESET                   (TCA9539_PIN_RESET)
#define EIO_PIN_SET                     (TCA9539_PIN_SET)
/**
 * @}
 */

/**
 * @defgroup HC32F448_EV_IO_Function_Sel Expand IO function definition
 * @{
 */
#define EIO_SCI_CD                      (TCA9539_IO_PIN1)   /* Smart card detect, input */
#define EIO_TOUCH_INT                   (TCA9539_IO_PIN2)   /* Touch screen interrupt, input */
#define EIO_TOUCH_CTRST                 (TCA9539_IO_PIN5)   /* 'Reset' for Cap touch panel, output */
#define EIO_LCD_RST                     (TCA9539_IO_PIN6)   /* LCD panel reset, output */
#define EIO_LCD_BKL                     (TCA9539_IO_PIN7)   /* LCD panel back light, output */

#define EIO_LIN_SLEEP                   (TCA9539_IO_PIN1)   /* LIN PHY sleep, output */
#define EIO_CAN1_STB                    (TCA9539_IO_PIN2)   /* CAN1 PHY standby, output */
#define EIO_CAN2_STB                    (TCA9539_IO_PIN3)   /* CAN2 PHY standby, output */
#define EIO_LED_RED                     (TCA9539_IO_PIN5)   /* Red LED, output */
#define EIO_LED_YELLOW                  (TCA9539_IO_PIN6)   /* Yellow LED, output */
#define EIO_LED_BLUE                    (TCA9539_IO_PIN7)   /* Blue LED, output */
/**
 * @}
 */

/**
 * @defgroup BSP_CAN_PortPin_Sel BSP CAN PHY STB port/pin definition
 * @{
 */
#define CAN1_STB_PORT                   (EIO_PORT1)
#define CAN1_STB_PIN                    (EIO_CAN1_STB)
#define CAN2_STB_PORT                   (EIO_PORT1)
#define CAN2_STB_PIN                    (EIO_CAN2_STB)
/**
 * @}
 */

/**
 * @defgroup BSP_LCD_PortPin_Sel BSP LCD panel port/pin definition
 * @{
 */
#define LCD_RST_PORT                    (EIO_PORT0)
#define LCD_RST_PIN                     (EIO_LCD_RST)
#define LCD_CTRST_PORT                  (EIO_PORT0)
#define LCD_CTRST_PIN                   (EIO_TOUCH_CTRST)
#define LCD_CTINT_PORT                  (EIO_PORT0)
#define LCD_CTINT_PIN                   (EIO_TOUCH_INT)
#define LCD_BKL_PORT                    (EIO_PORT0)
#define LCD_BKL_PIN                     (EIO_LCD_BKL)
/**
 * @}
 */

/**
 * @defgroup BSP_LED_PortPin_Sel BSP LED port/pin definition
 * @{
 */
#define LED_PORT                        (EIO_PORT1)
#define LED_RED_PORT                    (EIO_PORT1)
#define LED_RED_PIN                     (EIO_LED_RED)
#define LED_YELLOW_PORT                 (EIO_PORT1)
#define LED_YELLOW_PIN                  (EIO_LED_YELLOW)
#define LED_BLUE_PORT                   (EIO_PORT1)
#define LED_BLUE_PIN                    (EIO_LED_BLUE)
/**
 * @}
 */

/**
 * @defgroup BSP_LED_Sel BSP LED definition
 * @{
 */
#define LED_RED                         (EIO_LED_RED)
#define LED_YELLOW                      (EIO_LED_YELLOW)
#define LED_BLUE                        (EIO_LED_BLUE)
#define LED_ALL                         (LED_RED | LED_YELLOW | LED_BLUE)
/**
 * @}
 */

/**
 * @defgroup BSP_LED_OnOff_Sel BSP LED ON/OFF definition
 * @{
 */
#define LED_OFF                         (EIO_PIN_RESET)
#define LED_ON                          (EIO_PIN_SET)
/**
 * @}
 */

/**
 * @defgroup BSP_LIN_PHY_PortPin_Sel BSP LIN phy port/pin definition
 * @{
 */
#define LIN_SLEEP_PORT                  (EIO_PORT1)
#define LIN_SLEEP_PIN                   (EIO_LIN_SLEEP)
/**
 * @}
 */

/**
 * @defgroup BSP_Smartcard_PortPin_Sel BSP smartcard port/pin definition
 * @{
 */
#define SMARTCARD_CD_PORT               (EIO_PORT0)
#define SMARTCARD_CD_PIN                (EIO_SCI_CD)
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
 * @defgroup EV_HC32F448_LQFP80_TCA9539_Exported_Functions HC32F448 LQFP80 EVB TCA9539 Exported Functions
 * @{
 */
void BSP_IO_Init(void);
void BSP_IO_IntInit(void);

void BSP_IO_WritePortPin(uint8_t u8Port, uint8_t u8Pin, uint8_t u8PinState);
void BSP_IO_ConfigPortPin(uint8_t u8Port, uint8_t u8Pin, uint8_t u8Dir);
uint8_t BSP_IO_ReadPortPin(uint8_t u8Port, uint8_t u8Pin);
void BSP_IO_TogglePortPin(uint8_t u8Port, uint8_t u8Pin);

void BSP_CAN_STB_IO_Init(void);
void BSP_CAN_STBCmd(uint8_t u8Cmd);

void BSP_CT_RSTCmd(uint8_t u8Cmd);

void BSP_LCD_IO_Init(void);
void BSP_LCD_RSTCmd(uint8_t u8Cmd);
void BSP_LCD_BKLCmd(uint8_t u8Cmd);

void BSP_LED_Init(void);
void BSP_LED_On(uint8_t u8Led);
void BSP_LED_Off(uint8_t u8Led);
void BSP_LED_Toggle(uint8_t u8Led);

/**
 * @}
 */

#endif /* BSP_TCA9539_ENABLE && BSP_EV_HC32F448_LQFP80 */

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

#endif /* __EV_HC32F448_LQFP80_TCA9539__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
