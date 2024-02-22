/**
 *******************************************************************************
 * @file  ev_hc32f448_lqfp80_tca9539.c
 * @brief This file provides firmware functions for IO expand IC TCA9539.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ev_hc32f448_lqfp80_tca9539.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F448_LQFP80
 * @{
 */

/**
 * @defgroup EV_HC32F448_LQFP80_TCA9539 HC32F448 EVB LQFP80 TCA9539
 * @{
 */

#if ((BSP_TCA9539_ENABLE == DDL_ON) && (BSP_EV_HC32F448_LQFP80 == BSP_EV_HC32F4XX))

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static stc_tca9539_ll_t stcTca9539Config = {0};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F448_LQFP80_TCA9539_Global_Functions HC32F448 LQFP80 EVB TCA9539 Global Functions
 * @{
 */

/**
 * @brief  BSP TCA9539 reset.
 * @param  None
 * @retval None
 */
static void BSP_TCA9539_Reset(void)
{
    stc_gpio_init_t stcGpioInit;

    /* Set to low before output enable */
    GPIO_ResetPins(EIO_RST_PORT, EIO_RST_PIN);
    (void)GPIO_StructInit(&stcGpioInit);
    /* SET to output */
    stcGpioInit.u16PinDir = PIN_DIR_OUT;
    (void)GPIO_Init(EIO_RST_PORT, EIO_RST_PIN, &stcGpioInit);
    /* Reset the device */
    DDL_DelayMS(3UL);
    GPIO_SetPins(EIO_RST_PORT, EIO_RST_PIN);
}

/**
 * @brief  Initializes I2C for TCA9539.
 * @param  None
 * @retval None
 */
static void BSP_TCA9539_I2C_Init(void)
{
    stc_gpio_init_t stcGpioInit;
    /* Configuration I2C GPIO */
    (void)GPIO_StructInit(&stcGpioInit);
    (void)GPIO_Init(BSP_TCA9539_I2C_SCL_PORT, BSP_TCA9539_I2C_SCL_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_TCA9539_I2C_SDA_PORT, BSP_TCA9539_I2C_SDA_PIN, &stcGpioInit);
    GPIO_SetFunc(BSP_TCA9539_I2C_SCL_PORT, BSP_TCA9539_I2C_SCL_PIN, BSP_TCA9539_I2C_SCL_FUNC);
    GPIO_SetFunc(BSP_TCA9539_I2C_SDA_PORT, BSP_TCA9539_I2C_SDA_PIN, BSP_TCA9539_I2C_SDA_FUNC);
    /* Enable I2C Peripheral*/
    FCG_Fcg1PeriphClockCmd(BSP_TCA9539_I2C_FCG, ENABLE);
    (void)BSP_I2C_Init(BSP_TCA9539_I2C_UNIT);
}

/**
 * @brief  BSP TCA9539 write data.
 * @param  [in] pu8Reg:             Register to be written.
 * @param  [in] pu8Buf:             The pointer to the buffer contains the data to be written.
 * @param  [in] u32Len:             Buffer size in byte.
 * @retval None
 */
static void BSP_TCA9539_I2C_Write(const uint8_t *pu8Reg, const uint8_t *pu8Buf, uint32_t u32Len)
{
    (void)BSP_I2C_Write(BSP_TCA9539_I2C_UNIT, BSP_TCA9539_DEV_ADDR, pu8Reg, BSP_TCA9539_REG_ADDR_LEN, pu8Buf, u32Len);
}

/**
 * @brief  BSP TCA9539 Read data.
 * @param  [in] pu8Reg:             Register to be read.
 * @param  [in] pu8Buf:             The pointer to the buffer contains the data to be read.
 * @param  [in] u32Len:             Buffer size in byte.
 * @retval None
 */
static void BSP_TCA9539_I2C_Read(const uint8_t *pu8Reg, uint8_t *pu8Buf, uint32_t u32Len)
{
    (void)BSP_I2C_Read(BSP_TCA9539_I2C_UNIT, BSP_TCA9539_DEV_ADDR, pu8Reg, BSP_TCA9539_REG_ADDR_LEN, pu8Buf, u32Len);
}

/**
 * @brief  Expand IO initialize.
 * @param  None
 * @retval None
 */
void BSP_IO_Init(void)
{
    /* Configuration the low layer of TCA9539 */
    stcTca9539Config.Init          = BSP_TCA9539_I2C_Init;
    stcTca9539Config.Write         = BSP_TCA9539_I2C_Write;
    stcTca9539Config.Read          = BSP_TCA9539_I2C_Read;
    stcTca9539Config.Reset         = BSP_TCA9539_Reset;
    stcTca9539Config.IntInit       = NULL;
    /* Configuration the TCA9539 */
    (void)TCA9539_Init(&stcTca9539Config);
}

/**
 * @brief  Expand IO interrupt initialize.
 * @param  None
 * @retval None
 */
void BSP_IO_IntInit(void)
{
    (void)TCA9539_IntInit(&stcTca9539Config);
}

/**
 * @brief  Set EIO port pin output value
 * @param  [in] u8Port                  Port number @ref HC32F448_EV_IO_Port_Definition.
 * @param  [in] u8Pin                   Pin number @ref HC32F448_EV_IO_Function_Sel.
 * @param  [in] u8PinState              Pin state @ref HC32F448_EV_IO_Pin_State_Definition.
 * @retval None
 */
void BSP_IO_WritePortPin(uint8_t u8Port, uint8_t u8Pin, uint8_t u8PinState)
{
    (void)TCA9539_WritePin(&stcTca9539Config, u8Port, u8Pin, u8PinState);
}

/**
 * @brief  Get EIO port pin input value
 * @param  [in] u8Port                  Port number @ref HC32F448_EV_IO_Port_Definition.
 * @param  [in] u8Pin                   Pin number @ref HC32F448_EV_IO_Function_Sel.
 * @retval Pin state
 */
uint8_t BSP_IO_ReadPortPin(uint8_t u8Port, uint8_t u8Pin)
{
    uint8_t u8Value;

    (void)TCA9539_ReadPin(&stcTca9539Config, u8Port, u8Pin, &u8Value);
    return u8Value;
}

/**
 * @brief  Toggle EIO port pin
 * @param  [in] u8Port                  Port number @ref HC32F448_EV_IO_Port_Definition.
 * @param  [in] u8Pin                   Pin number @ref HC32F448_EV_IO_Function_Sel.
 * @retval None
 */
void BSP_IO_TogglePortPin(uint8_t u8Port, uint8_t u8Pin)
{
    (void)TCA9539_TogglePin(&stcTca9539Config, u8Port, u8Pin);
}

/**
 * @brief  Config EIO port pin direction
 * @param  [in] u8Port                  Port number @ref HC32F448_EV_IO_Port_Definition.
 * @param  [in] u8Pin                   Pin number @ref HC32F448_EV_IO_Function_Sel.
 * @param  [in] u8Dir                   Pin direction @ref HC32F448_EV_IO_Direction_Definition.
 * @retval None
 */
void BSP_IO_ConfigPortPin(uint8_t u8Port, uint8_t u8Pin, uint8_t u8Dir)
{
    (void)TCA9539_ConfigPin(&stcTca9539Config, u8Port, u8Pin, u8Dir);
}

/**
 * @brief  CAN PYH STB pin initialization.
 * @param  None
 * @retval None
 */
void BSP_CAN_STB_IO_Init(void)
{
    /* SET STB pin high before output */
    BSP_IO_WritePortPin(CAN1_STB_PORT, CAN1_STB_PIN, EIO_PIN_SET);
    BSP_IO_WritePortPin(CAN2_STB_PORT, CAN2_STB_PIN, EIO_PIN_SET);
    /* STB pin set to output */
    BSP_IO_ConfigPortPin(CAN1_STB_PORT, CAN1_STB_PIN, EIO_DIR_OUT);
    BSP_IO_ConfigPortPin(CAN2_STB_PORT, CAN2_STB_PIN, EIO_DIR_OUT);
}

/**
 * @brief  CAN PYH STB pin control
 * @param  [in] u8Cmd
 *   @arg  EIO_PIN_SET
 *   @arg  EIO_PIN_RESET
 * @retval None
 */
void BSP_CAN_STBCmd(uint8_t u8Cmd)
{
    BSP_IO_WritePortPin(CAN1_STB_PORT, CAN1_STB_PIN, u8Cmd);
    BSP_IO_WritePortPin(CAN2_STB_PORT, CAN2_STB_PIN, u8Cmd);
}

/**
 * @brief  Cap panel reset pin config.
 * @param  [in] u8Cmd
 *   @arg  EIO_PIN_SET
 *   @arg  EIO_PIN_RESET
 * @retval None
 */
void BSP_CT_RSTCmd(uint8_t u8Cmd)
{
    BSP_IO_ConfigPortPin(LCD_CTRST_PORT, LCD_CTRST_PIN, EIO_DIR_OUT);
    BSP_IO_WritePortPin(LCD_CTRST_PORT, LCD_CTRST_PIN, u8Cmd);
    BSP_IO_ConfigPortPin(LCD_CTRST_PORT, LCD_CTRST_PIN, EIO_DIR_IN);
}

/**
 * @brief  LCD ctrl IO initialize.
 * @param  None
 * @retval None
 */
void BSP_LCD_IO_Init(void)
{
    /* Init LCD backlight IO */
    BSP_IO_WritePortPin(LCD_BKL_PORT, LCD_BKL_PIN, EIO_PIN_RESET);
    BSP_IO_ConfigPortPin(LCD_BKL_PORT, LCD_BKL_PIN, EIO_DIR_OUT);

    /* Init LCD and touch panel control IO before direction setting */
    BSP_IO_WritePortPin(LCD_RST_PORT, LCD_RST_PIN, EIO_PIN_SET);

    /* LCD panel control IO set to output */
    BSP_IO_ConfigPortPin(LCD_RST_PORT, LCD_RST_PIN, EIO_DIR_OUT);

    /* Init touch panel control IO before direction setting */
    BSP_IO_WritePortPin(LCD_CTRST_PORT, LCD_CTRST_PIN, EIO_PIN_RESET);
    BSP_IO_WritePortPin(LCD_CTINT_PORT, LCD_CTINT_PIN, EIO_PIN_RESET);

    BSP_IO_ConfigPortPin(LCD_CTRST_PORT, LCD_CTRST_PIN, EIO_DIR_OUT);
    BSP_IO_ConfigPortPin(LCD_CTINT_PORT, LCD_CTINT_PIN, EIO_DIR_OUT);
    DDL_DelayMS(100UL);

    BSP_IO_WritePortPin(LCD_CTINT_PORT, LCD_CTINT_PIN, EIO_PIN_SET);
    DDL_DelayMS(100UL);

    BSP_IO_WritePortPin(LCD_CTRST_PORT, LCD_CTRST_PIN, EIO_PIN_SET);
    DDL_DelayMS(10UL);

    BSP_IO_WritePortPin(LCD_CTINT_PORT, LCD_CTINT_PIN, EIO_PIN_RESET);
    DDL_DelayMS(100UL);

    BSP_IO_ConfigPortPin(LCD_CTRST_PORT, LCD_CTRST_PIN, EIO_DIR_IN);
    BSP_IO_ConfigPortPin(LCD_CTINT_PORT, LCD_CTINT_PIN, EIO_DIR_IN);
}

/**
 * @brief  LCD reset pin config.
 * @param  [in] u8Cmd
 *   @arg  EIO_PIN_SET
 *   @arg  EIO_PIN_RESET
 * @retval None
 */
void BSP_LCD_RSTCmd(uint8_t u8Cmd)
{
    BSP_IO_WritePortPin(LCD_RST_PORT, LCD_RST_PIN, u8Cmd);
}

/**
 * @brief  LCD backlight pin config.
 * @param  [in] u8Cmd
 *   @arg  EIO_PIN_SET
 *   @arg  EIO_PIN_RESET
 * @retval None
 */
void BSP_LCD_BKLCmd(uint8_t u8Cmd)
{
    BSP_IO_WritePortPin(LCD_BKL_PORT, LCD_BKL_PIN, u8Cmd);
}

/**
 * @brief  LED initialize.
 * @param  None
 * @retval None
 */
void BSP_LED_Init(void)
{
    /* Turn off LED before output */
    BSP_IO_WritePortPin(LED_PORT, (LED_RED_PIN | LED_YELLOW_PIN | LED_BLUE_PIN), LED_OFF);
    /* LED pins set to output */
    BSP_IO_ConfigPortPin(LED_PORT, (LED_RED_PIN | LED_YELLOW_PIN | LED_BLUE_PIN), EIO_DIR_OUT);
}

/**
 * @brief  Turn on LEDs.
 * @param  [in] u8Led LED
 *   @arg  LED_RED
 *   @arg  LED_YELLOW
 *   @arg  LED_BLUE
 * @retval None
 */
void BSP_LED_On(uint8_t u8Led)
{
    BSP_IO_WritePortPin(LED_PORT, u8Led, LED_ON);
}

/**
 * @brief  Turn off LEDs.
 * @param  [in] u8Led LED
 *   @arg  LED_RED
 *   @arg  LED_YELLOW
 *   @arg  LED_BLUE
 * @retval None
 */
void BSP_LED_Off(uint8_t u8Led)
{
    BSP_IO_WritePortPin(LED_PORT, u8Led, LED_OFF);
}

/**
 * @brief  Toggle LEDs.
 * @param  [in] u8Led LED
 *   @arg  LED_RED
 *   @arg  LED_YELLOW
 *   @arg  LED_BLUE
 * @retval None
 */
void BSP_LED_Toggle(uint8_t u8Led)
{
    BSP_IO_TogglePortPin(LED_PORT, u8Led);
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
