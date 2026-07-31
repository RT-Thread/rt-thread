/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup GPIO_W
 * @{
 **********************************************************************************************************************/

#ifndef R_GPIO_W_H
#define R_GPIO_W_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_ioport_api.h"
#include "r_gpio_w_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define GPIO_W_PXX_MODE_REG(_port, _pin)    BSP_IO_PXX_MODE_REG(_port, _pin)

#if !defined(BSP_MCU_GROUP_RA6W1)
 #define GPIO_W_MODE_REG_VALID_BITS_MSK    (0x3F3F3FU)
 #define GPIO_W_PRV_FUNC_BITS              (0x003FU)

/* Macro for toggle action triggered by event with initial level */
 #define TOGGLE_GPIO_EVENTx_MASK(event, level)    ((uint32_t) GPIO_W_CFG_PORT_DIRECTION_OUTPUT | \
                                                   (uint32_t) GPIO_W_CFG_ELC_TASK_GPIO_TOGGLE |  \
                                                   (uint32_t) event |                            \
                                                   (uint32_t) (level << GPIO_W_PRV_LEVEL_OFFSET))

/* Macro for set action triggered by event */
 #define SET_GPIO_EVENTx_MASK(event)              ((uint32_t) GPIO_W_CFG_PORT_DIRECTION_OUTPUT | \
                                                   (uint32_t) GPIO_W_CFG_ELC_TASK_GPIO_SET |     \
                                                   (uint32_t) event |                            \
                                                   (uint32_t) GPIO_W_CFG_PORT_OUTPUT_LOW)

/* Macro for reset action triggered by event */
 #define RESET_GPIO_EVENTx_MASK(event)            ((uint32_t) GPIO_W_CFG_PORT_DIRECTION_OUTPUT | \
                                                   (uint32_t) GPIO_W_CFG_ELC_TASK_GPIO_RESET |   \
                                                   (uint32_t) event |                            \
                                                   (uint32_t) GPIO_W_CFG_PORT_OUTPUT_HIGH)
#else
 #define GPIO_W_PRV_MODE_BITS      (0xFF7FU)
 #define GPIO_W_PRV_FUNC_BITS      (0x007FU)
#endif

#define GPIO_W_PRV_LEVEL_BITS      (0x400000U)
#define GPIO_W_PRV_LEVEL_OFFSET    (22U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* TODO: This cannot be maintained, use similar solution as RA's BSP_OVERRIDE_IOPORT_PERIPHERAL_T. */
/** Superset of all peripheral functions.  */
typedef enum e_gpio_w_peripheral
{
    GPIO_W_PERIPHERAL_DEBUG = 0,              /**< Pin will function as a DEBUG pin (controlled by SYS_CTRL_REG[DEBUGGER_ENABLE]) */
    GPIO_W_PERIPHERAL_TRACE = 0,              /**< Pin will function as a TRACE pin (controlled by DEBUG_REG[ETM_TRACE_MAP_ON_PINS_EN]) */
    GPIO_W_PERIPHERAL_ACOMP = 0,              /**< Pin will function as an ACOMP Channel pin */
    GPIO_W_PERIPHERAL_QSPI  = 0,              /**< Pin will function as a QSPIC pin */

#if BSP_MCU_GROUP_RA6B1 || BSP_MCU_GROUP_RA6U1
    GPIO_W_PERIPHERAL_GPIO             = 0,   /**< GPIO */
    GPIO_W_PERIPHERAL_UART_RX          = 1,   /**< GPIO as UART RX */
    GPIO_W_PERIPHERAL_UART_TX          = 2,   /**< GPIO as UART TX */
    GPIO_W_PERIPHERAL_UART2_RX         = 3,   /**< GPIO as UART2 RX */
    GPIO_W_PERIPHERAL_UART2_TX         = 4,   /**< GPIO as UART2 TX */
    GPIO_W_PERIPHERAL_UART2_CTSN       = 5,   /**< GPIO as UART2 CTSN */
    GPIO_W_PERIPHERAL_UART2_RTSN       = 6,   /**< GPIO as UART2 RTSN */
    GPIO_W_PERIPHERAL_UART2_IRDA_RX    = 7,   /**< GPIO as IRDA RX */
    GPIO_W_PERIPHERAL_UART2_IRDA_TX    = 8,   /**< GPIO as IRDA TX*/
    GPIO_W_PERIPHERAL_UART3_RX         = 9,   /**< GPIO as UART3 RX */
    GPIO_W_PERIPHERAL_UART3_TX         = 10,  /**< GPIO as UART3 TX */
    GPIO_W_PERIPHERAL_UART3_CTSN       = 11,  /**< GPIO as UART3 CTSN */
    GPIO_W_PERIPHERAL_ISO_RST          = 11,  /**< GPIO as ISO7816 reset */
    GPIO_W_PERIPHERAL_UART3_RTSN       = 12,  /**< GPIO as UART3 RTSN */
    GPIO_W_PERIPHERAL_ISO_CARDINSERT   = 12,  /**< GPIO as ISO7816 card insert */
    GPIO_W_PERIPHERAL_UART4_RX         = 13,  /**< GPIO as UART4 RX */
    GPIO_W_PERIPHERAL_UART4_TX         = 14,  /**< GPIO as UART4 TX */
    GPIO_W_PERIPHERAL_UART4_CTSN       = 15,  /**< GPIO as UART4 CTSN */
    GPIO_W_PERIPHERAL_UART4_RTSN       = 16,  /**< GPIO as UART4 RTSN */
    GPIO_W_PERIPHERAL_ISO_CLK          = 17,  /**< GPIO as ISO CLK */
    GPIO_W_PERIPHERAL_ISO_DATA         = 18,  /**< GPIO as ISO DATA */
    GPIO_W_PERIPHERAL_SPI_DI           = 19,  /**< GPIO as SPI DI */
    GPIO_W_PERIPHERAL_SPI_DO           = 20,  /**< GPIO as SPI DO */
    GPIO_W_PERIPHERAL_SPI_CLK          = 21,  /**< GPIO as SPI CLK */
    GPIO_W_PERIPHERAL_SPI_CS           = 22,  /**< GPIO as SPI EN */
    GPIO_W_PERIPHERAL_SPI_CS2          = 23,  /**< GPIO as SPI EN2 */
    GPIO_W_PERIPHERAL_SPI2_DI          = 24,  /**< GPIO as SPI2 DI */
    GPIO_W_PERIPHERAL_SPI2_DO          = 25,  /**< GPIO as SPI2 DO */
    GPIO_W_PERIPHERAL_SPI2_CLK         = 26,  /**< GPIO as SPI2 CLK */
    GPIO_W_PERIPHERAL_SPI2_CS          = 27,  /**< GPIO as SPI2 EN */
    GPIO_W_PERIPHERAL_SPI2_CS2         = 28,  /**< GPIO as SPI2 EN2 */
    GPIO_W_PERIPHERAL_SPI3_DI          = 29,  /**< GPIO as SPI3 DI */
    GPIO_W_PERIPHERAL_SPI3_DO          = 30,  /**< GPIO as SPI3 DO */
    GPIO_W_PERIPHERAL_SPI3_CLK         = 31,  /**< GPIO as SPI3 CLK */
    GPIO_W_PERIPHERAL_SPI3_CS          = 32,  /**< GPIO as SPI3 EN */
    GPIO_W_PERIPHERAL_SPI3_CS2         = 33,  /**< GPIO as SPI3 EN2 */
    GPIO_W_PERIPHERAL_I2C_SCL          = 34,  /**< GPIO as I2C SCL */
    GPIO_W_PERIPHERAL_I2C_SDA          = 35,  /**< GPIO as I2C SDA */
    GPIO_W_PERIPHERAL_I2C2_SCL         = 36,  /**< GPIO as I2C2 SCL */
    GPIO_W_PERIPHERAL_I2C2_SDA         = 37,  /**< GPIO as I2C2 SDA */
    GPIO_W_PERIPHERAL_I2C3_SCL         = 38,  /**< GPIO as I2C3 SCL */
    GPIO_W_PERIPHERAL_I2C3_SDA         = 39,  /**< GPIO as I2C3 SDA */
    GPIO_W_PERIPHERAL_I3C_SCL          = 40,  /**< GPIO as I3C SCL */
    GPIO_W_PERIPHERAL_I3C_SDA          = 41,  /**< GPIO as I3C SDA */
    GPIO_W_PERIPHERAL_USB_SOF          = 42,  /**< GPIO as USB SOF */
    GPIO_W_PERIPHERAL_CAN_RX           = 43,  /**< GPIO as CAN RX */
    GPIO_W_PERIPHERAL_CAN_TX           = 44,  /**< GPIO as CAN TX */
    GPIO_W_PERIPHERAL_ADC              = 45,  /**< GPIO as ADC (dedicated pin) */
    GPIO_W_PERIPHERAL_USB              = 46,  /**< GPIO as USB (dedicated pins) */
    GPIO_W_PERIPHERAL_IRGEN            = 47,  /**< GPIO as IR generator */
    GPIO_W_PERIPHERAL_KBSCN_COL        = 48,  /**< GPIO as Keyboard Scanner */
    GPIO_W_PERIPHERAL_PCM_DI           = 49,  /**< GPIO as PCM DI */
    GPIO_W_PERIPHERAL_PCM_DO           = 50,  /**< GPIO as PCM DO */
    GPIO_W_PERIPHERAL_PCM_FSC          = 51,  /**< GPIO as PCM FSC */
    GPIO_W_PERIPHERAL_PCM_CLK          = 52,  /**< GPIO as PCM CLK */
    GPIO_W_PERIPHERAL_PDM_DATA         = 53,  /**< GPIO as PDM DATA */
    GPIO_W_PERIPHERAL_PDM_CLK          = 54,  /**< GPIO as PDM CLK */
    GPIO_W_PERIPHERAL_TIMX_PWM         = 55,  /**< GPIO as TIMx PWM (dedicated pins) */
    GPIO_W_PERIPHERAL_TIMX_1SHOT_PULSE = 56,  /**< GPIO as TIMx 1SHOT pulse (dedicated pins) */
    GPIO_W_PERIPHERAL_CLOCK            = 57,  /**< GPIO as CLOCK */
    GPIO_W_PERIPHERAL_COEX_EXT_ACT     = 58,  /**< GPIO as COEX EXT ACT */
    GPIO_W_PERIPHERAL_COEX_SMART_ACT   = 59,  /**< GPIO as COEX SMART ACT */
    GPIO_W_PERIPHERAL_COEX_SMART_PRI   = 60,  /**< GPIO as COEX SMART PRI */
    GPIO_W_PERIPHERAL_RF_DIAG          = 61,  /**< GPIO as RF DIAG (dedicated pins) */
    GPIO_W_PERIPHERAL_RFFE_SCLK        = 62,  /**< GPIO as RFFE SCLK */
    GPIO_W_PERIPHERAL_RFFE_SDATA       = 63,  /**< GPIO as RFFE SDATA */
#elif BSP_MCU_GROUP_RA6B2
    GPIO_W_PERIPHERAL_GPIO             = 0,   /**< GPIO */
    GPIO_W_PERIPHERAL_UART_RX          = 1,   /**< GPIO as UART RX */
    GPIO_W_PERIPHERAL_UART_TX          = 2,   /**< GPIO as UART TX */
    GPIO_W_PERIPHERAL_UART2_RX         = 3,   /**< GPIO as UART2 RX */
    GPIO_W_PERIPHERAL_UART2_TX         = 4,   /**< GPIO as UART2 TX */
    GPIO_W_PERIPHERAL_UART2_CTSN       = 5,   /**< GPIO as UART2 CTSN */
    GPIO_W_PERIPHERAL_UART2_RTSN       = 6,   /**< GPIO as UART2 RTSN */
    GPIO_W_PERIPHERAL_UART2_IRDA_RX    = 7,   /**< GPIO as IRDA RX */
    GPIO_W_PERIPHERAL_UART2_IRDA_TX    = 8,   /**< GPIO as IRDA TX*/
    GPIO_W_PERIPHERAL_UART3_RX         = 9,   /**< GPIO as UART3 RX */
    GPIO_W_PERIPHERAL_UART3_TX         = 10,  /**< GPIO as UART3 TX */
    GPIO_W_PERIPHERAL_UART3_CTSN       = 11,  /**< GPIO as UART3 CTSN */
    GPIO_W_PERIPHERAL_UART3_RTSN       = 12,  /**< GPIO as UART3 RTSN */
    GPIO_W_PERIPHERAL_ISO_CLK          = 13,  /**< GPIO as ISO CLK */
    GPIO_W_PERIPHERAL_ISO_DATA         = 14,  /**< GPIO as ISO DATA */
    GPIO_W_PERIPHERAL_SPI_DI           = 15,  /**< GPIO as SPI DI */
    GPIO_W_PERIPHERAL_SPI_DO           = 16,  /**< GPIO as SPI DO */
    GPIO_W_PERIPHERAL_SPI_CLK          = 17,  /**< GPIO as SPI CLK */
    GPIO_W_PERIPHERAL_SPI_CS           = 18,  /**< GPIO as SPI EN */
    GPIO_W_PERIPHERAL_SPI_CS2          = 19,  /**< GPIO as SPI EN2 */
    GPIO_W_PERIPHERAL_SPI2_DI          = 20,  /**< GPIO as SPI2 DI */
    GPIO_W_PERIPHERAL_SPI2_DO          = 21,  /**< GPIO as SPI2 DO */
    GPIO_W_PERIPHERAL_SPI2_CLK         = 22,  /**< GPIO as SPI2 CLK */
    GPIO_W_PERIPHERAL_SPI2_CS          = 23,  /**< GPIO as SPI2 EN */
    GPIO_W_PERIPHERAL_SPI2_CS2         = 24,  /**< GPIO as SPI2 EN2 */
    GPIO_W_PERIPHERAL_SPI3_DI          = 25,  /**< GPIO as SPI3 DI */
    GPIO_W_PERIPHERAL_SPI3_DO          = 26,  /**< GPIO as SPI3 DO */
    GPIO_W_PERIPHERAL_SPI3_CLK         = 27,  /**< GPIO as SPI3 CLK */
    GPIO_W_PERIPHERAL_SPI3_CS          = 28,  /**< GPIO as SPI3 EN */
    GPIO_W_PERIPHERAL_SPI3_CS2         = 29,  /**< GPIO as SPI3 EN2 */
    GPIO_W_PERIPHERAL_I2C_SCL          = 30,  /**< GPIO as I2C SCL */
    GPIO_W_PERIPHERAL_I2C_SDA          = 31,  /**< GPIO as I2C SDA */
    GPIO_W_PERIPHERAL_I2C2_SCL         = 32,  /**< GPIO as I2C2 SCL */
    GPIO_W_PERIPHERAL_I2C2_SDA         = 33,  /**< GPIO as I2C2 SDA */
    GPIO_W_PERIPHERAL_I3C_SCL          = 34,  /**< GPIO as I3C SCL */
    GPIO_W_PERIPHERAL_I3C_SDA          = 35,  /**< GPIO as I3C SDA */
    GPIO_W_PERIPHERAL_CAN_RX           = 36,  /**< GPIO as CAN RX */
    GPIO_W_PERIPHERAL_CAN_TX           = 37,  /**< GPIO as CAN TX */
    GPIO_W_PERIPHERAL_ADC              = 38,  /**< GPIO as ADC (dedicated pin) */
    GPIO_W_PERIPHERAL_IRGEN            = 39,  /**< GPIO as IR generator */
    GPIO_W_PERIPHERAL_KBSCN_COL        = 40,  /**< GPIO as Keyboard Scanner */
    GPIO_W_PERIPHERAL_PCM_DI           = 41,  /**< GPIO as PCM DI */
    GPIO_W_PERIPHERAL_PCM_DO           = 42,  /**< GPIO as PCM DO */
    GPIO_W_PERIPHERAL_PCM_FSC          = 43,  /**< GPIO as PCM FSC */
    GPIO_W_PERIPHERAL_PCM_CLK          = 44,  /**< GPIO as PCM CLK */
    GPIO_W_PERIPHERAL_PDM_DATA         = 45,  /**< GPIO as PDM DATA */
    GPIO_W_PERIPHERAL_PDM_CLK          = 46,  /**< GPIO as PDM CLK */
    GPIO_W_PERIPHERAL_TIMX_PWM         = 47,  /**< GPIO as TIMx PWM (dedicated pins) */
    GPIO_W_PERIPHERAL_TIMX_1SHOT_PULSE = 48,  /**< GPIO as TIMx 1SHOT pulse (dedicated pins) */
    GPIO_W_PERIPHERAL_CLOCK            = 49,  /**< GPIO as CLOCK */
    GPIO_W_PERIPHERAL_COEX_EXT_ACT     = 50,  /**< GPIO as COEX EXT ACT */
    GPIO_W_PERIPHERAL_COEX_SMART_ACT   = 51,  /**< GPIO as COEX SMART ACT */
    GPIO_W_PERIPHERAL_COEX_SMART_PRI   = 52,  /**< GPIO as COEX SMART PRI */
    GPIO_W_PERIPHERAL_RF_DIAG          = 53,  /**< GPIO as RF DIAG (dedicated pins) */
#elif BSP_MCU_GROUP_RA6W1
    GPIO_W_PERIPHERAL_GPIO        = 0,        /**< GPIO */
    GPIO_W_PERIPHERAL_UART_RX     = 1,        /**< GPIO as UART RX */
    GPIO_W_PERIPHERAL_UART_TX     = 2,        /**< GPIO as UART TX */
    GPIO_W_PERIPHERAL_UART_CTSN   = 3,        /**< GPIO as UART CTSN */
    GPIO_W_PERIPHERAL_UART_RTSN   = 4,        /**< GPIO as UART RTSN */
    GPIO_W_PERIPHERAL_UART_TXDOE  = 5,        /**< GPIO as UART TXDOE */
    GPIO_W_PERIPHERAL_UART2_RX    = 6,        /**< GPIO as UART2 RX */
    GPIO_W_PERIPHERAL_UART2_TX    = 7,        /**< GPIO as UART2 TX */
    GPIO_W_PERIPHERAL_UART2_CTSN  = 8,        /**< GPIO as UART2 CTSN */
    GPIO_W_PERIPHERAL_UART2_RTSN  = 9,        /**< GPIO as UART2 RTSN */
    GPIO_W_PERIPHERAL_UART2_TXDOE = 10,       /**< GPIO as UART2 TXDOE */
    GPIO_W_PERIPHERAL_UART3_RX    = 11,       /**< GPIO as UART3 RX */
    GPIO_W_PERIPHERAL_UART3_TX    = 12,       /**< GPIO as UART3 TX */
    GPIO_W_PERIPHERAL_UART3_CTSN  = 13,       /**< GPIO as UART3 CTSN */
    GPIO_W_PERIPHERAL_UART3_RTSN  = 14,       /**< GPIO as UART3 RTSN */
    GPIO_W_PERIPHERAL_UART3_TXDOE = 15,       /**< GPIO as UART3 TXDOE */
    GPIO_W_PERIPHERAL_SPI_DI      = 16,       /**< GPIO as SPI DI */
    GPIO_W_PERIPHERAL_SPI_DO      = 17,       /**< GPIO as SPI DO */
    GPIO_W_PERIPHERAL_SPI_CLK     = 18,       /**< GPIO as SPI CLK */
    GPIO_W_PERIPHERAL_SPI_CSN0    = 19,       /**< GPIO as SPI CSN0 */
    GPIO_W_PERIPHERAL_SPI_CSN1    = 20,       /**< GPIO as SPI CSN1 */
    GPIO_W_PERIPHERAL_SPI2_DI     = 21,       /**< GPIO as SPI2 DI */
    GPIO_W_PERIPHERAL_SPI2_DO     = 22,       /**< GPIO as SPI2 DO */
    GPIO_W_PERIPHERAL_SPI2_CLK    = 23,       /**< GPIO as SPI2 CLK */
    GPIO_W_PERIPHERAL_SPI2_CSN0   = 24,       /**< GPIO as SPI2 CSN0 */
    GPIO_W_PERIPHERAL_SPI2_CSN1   = 25,       /**< GPIO as SPI2 CSN1 */
    GPIO_W_PERIPHERAL_I2C_SCL     = 26,       /**< GPIO as I2C SCL */
    GPIO_W_PERIPHERAL_I2C_SDA     = 27,       /**< GPIO as I2C SDA */
    GPIO_W_PERIPHERAL_I2C2_SCL    = 28,       /**< GPIO as I2C2 SCL */
    GPIO_W_PERIPHERAL_I2C2_SDA    = 29,       /**< GPIO as I2C2 SDA */
    GPIO_W_PERIPHERAL_ADC         = 30,       /**< GPIO as ADC (dedicated pin) */
    GPIO_W_PERIPHERAL_PCM_DI      = 31,       /**< GPIO as PCM DI */
    GPIO_W_PERIPHERAL_PCM_DO      = 32,       /**< GPIO as PCM DO */
    GPIO_W_PERIPHERAL_PCM_FSC     = 33,       /**< GPIO as PCM FSC */
    GPIO_W_PERIPHERAL_PCM_CLK     = 34,       /**< GPIO as PCM CLK */
    GPIO_W_PERIPHERAL_DMICA_DI    = 35,       /**< GPIO as DMICA DI */
    GPIO_W_PERIPHERAL_DMIC_CLK    = 36,       /**< GPIO as DMIC CLK */
    GPIO_W_PERIPHERAL_MCLK        = 37,       /**< GPIO as MCLK */
    GPIO_W_PERIPHERAL_TIM_PWM     = 38,       /**< GPIO as TIM PWM */
    GPIO_W_PERIPHERAL_TIM2_PWM    = 39,       /**< GPIO as TIM2 PWM */
    GPIO_W_PERIPHERAL_TIM3_PWM    = 40,       /**< GPIO as TIM3 PWM */
    GPIO_W_PERIPHERAL_TIM4_PWM    = 41,       /**< GPIO as TIM4 PWM */
    GPIO_W_PERIPHERAL_TIM5_PWM    = 42,       /**< GPIO as TIM5 PWM */
    GPIO_W_PERIPHERAL_TIM6_PWM    = 43,       /**< GPIO as TIM6 PWM */
    GPIO_W_PERIPHERAL_TIM7_PWM    = 44,       /**< GPIO as TIM7 PWM */
    GPIO_W_PERIPHERAL_TIM8_PWM    = 45,       /**< GPIO as TIM8 PWM */
    GPIO_W_PERIPHERAL_TIM_1SHOT   = 46,       /**< GPIO as TIM 1SHOT */
    GPIO_W_PERIPHERAL_TIM2_1SHOT  = 47,       /**< GPIO as TIM2 1SHOT */
    GPIO_W_PERIPHERAL_TIM3_1SHOT  = 48,       /**< GPIO as TIM3 1SHOT */
    GPIO_W_PERIPHERAL_TIM4_1SHOT  = 49,       /**< GPIO as TIM4 1SHOT */
    GPIO_W_PERIPHERAL_TIM5_1SHOT  = 50,       /**< GPIO as TIM5 1SHOT */
    GPIO_W_PERIPHERAL_TIM6_1SHOT  = 51,       /**< GPIO as TIM6 1SHOT */
    GPIO_W_PERIPHERAL_TIM7_1SHOT  = 52,       /**< GPIO as TIM7 1SHOT */
    GPIO_W_PERIPHERAL_TIM8_1SHOT  = 53,       /**< GPIO as TIM8 1SHOT */
    GPIO_W_PERIPHERAL_CLOCK       = 54,       /**< GPIO as CLOCK */
    GPIO_W_PERIPHERAL_FEM_BS      = 55,       /**< GPIO as FEM_BS */
    GPIO_W_PERIPHERAL_FEM_CS      = 56,       /**< GPIO as FEM_CS */
    GPIO_W_PERIPHERAL_FEM_CTRL0   = 57,       /**< GPIO as FEM CTRL0 */
    GPIO_W_PERIPHERAL_FEM_CTRL1   = 58,       /**< GPIO as FEM CTRL1 */
    GPIO_W_PERIPHERAL_FEM_CTRL2   = 59,       /**< GPIO as FEM CTRL2 */
    GPIO_W_PERIPHERAL_BT_COEX_CBT = 60,       /**< GPIO as BT COEX CBT */
    GPIO_W_PERIPHERAL_BT_WLAN_ACT = 61,       /**< GPIO as BT WLAN ACT */
    GPIO_W_PERIPHERAL_BT_ACT      = 62,       /**< GPIO as BT ACT */
    GPIO_W_PERIPHERAL_BT_PRI      = 63,       /**< GPIO as BT PRI */
    GPIO_W_PERIPHERAL_RF_SW1      = 64,       /**< GPIO as RF SW1 */
    GPIO_W_PERIPHERAL_RF_SW2      = 65,       /**< GPIO as RF SW2 */
    GPIO_W_PERIPHERAL_EXT_INTR    = 66,       /**< GPIO as EXT INTR */

    GPIO_W_PERIPHERAL_SWCLK       = 99,       /**< GPIO as SWCLK */
    GPIO_W_PERIPHERAL_SWDIO       = 100,      /**< GPIO as SWDIO */
    GPIO_W_PERIPHERAL_WPROTECT    = 101,      /**< GPIO as WPROTECT */
    GPIO_W_PERIPHERAL_CDETECT     = 102,      /**< GPIO as CDETECT */
    GPIO_W_PERIPHERAL_ZB_WLAN_ACT = 103,      /**< GPIO as ZB WLAN ACT */
    GPIO_W_PERIPHERAL_ZB_ACT      = 104,      /**< GPIO as ZB ACT */
    GPIO_W_PERIPHERAL_ZB_PRI      = 105,      /**< GPIO as ZB PRI */
    GPIO_W_PERIPHERAL_BTCOEX_ASC0 = 106,      /**< GPIO as BTCOEX ASC0 */
    GPIO_W_PERIPHERAL_BTCOEX_ASC1 = 107,      /**< GPIO as BTCOEX ASC1 */
    GPIO_W_PERIPHERAL_BTCOEX_ASC2 = 108,      /**< GPIO as BTCOEX ASC2 */
#elif BSP_MCU_GROUP_RA6W3
    GPIO_W_PERIPHERAL_GPIO              = 0,  /**< GPIO */
    GPIO_W_PERIPHERAL_UART2_TX          = 1,  /**< GPIO as UART2 TX */
    GPIO_W_PERIPHERAL_UART2_RX          = 2,  /**< GPIO as UART2 RX */
    GPIO_W_PERIPHERAL_UART2_RTSN        = 3,  /**< GPIO as UART2 RTSN */
    GPIO_W_PERIPHERAL_UART2_CTSN        = 4,  /**< GPIO as UART2 CTSN */
    GPIO_W_PERIPHERAL_UART3_TX          = 5,  /**< GPIO as UART3 TX */
    GPIO_W_PERIPHERAL_UART3_RX          = 6,  /**< GPIO as UART3 RX */
    GPIO_W_PERIPHERAL_UART3_RTSN        = 7,  /**< GPIO as UART3 RTSN */
    GPIO_W_PERIPHERAL_UART3_CTSN        = 8,  /**< GPIO as UART3 CTSN */
    GPIO_W_PERIPHERAL_UART4_TX          = 9,  /**< GPIO as UART4 TX */
    GPIO_W_PERIPHERAL_UART4_RX          = 10, /**< GPIO as UART4 RX */
    GPIO_W_PERIPHERAL_UART4_RTSN        = 11, /**< GPIO as UART4 RTSN */
    GPIO_W_PERIPHERAL_UART4_CTSN        = 12, /**< GPIO as UART4 CTSN */
    GPIO_W_PERIPHERAL_I2C_SDA           = 13, /**< GPIO as I2C SDA */
    GPIO_W_PERIPHERAL_I2C_SCL           = 14, /**< GPIO as I2C SCL */
    GPIO_W_PERIPHERAL_I2C2_SDA          = 15, /**< GPIO as I2C2 SDA */
    GPIO_W_PERIPHERAL_I2C2_SCL          = 16, /**< GPIO as I2C2 SCL */
    GPIO_W_PERIPHERAL_SPI2_CLK          = 17, /**< GPIO as SPI2 CLK */
    GPIO_W_PERIPHERAL_SPI2_DI           = 18, /**< GPIO as SPI2 DI */
    GPIO_W_PERIPHERAL_SPI2_DO           = 19, /**< GPIO as SPI2 DO */
    GPIO_W_PERIPHERAL_SPI2_CS           = 20, /**< GPIO as SPI2 CS */
    GPIO_W_PERIPHERAL_SPI3_CLK          = 21, /**< GPIO as SPI3 CLK */
    GPIO_W_PERIPHERAL_SPI3_DI           = 22, /**< GPIO as SPI3 DI */
    GPIO_W_PERIPHERAL_SPI3_DO           = 23, /**< GPIO as SPI3 DO */
    GPIO_W_PERIPHERAL_SPI3_CS           = 24, /**< GPIO as SPI3 CS */
    GPIO_W_PERIPHERAL_TIM1_PWM          = 25, /**< GPIO as TIM1 PWM */
    GPIO_W_PERIPHERAL_TIM2_PWM          = 26, /**< GPIO as TIM2 PWM */
    GPIO_W_PERIPHERAL_TIM3_PWM          = 27, /**< GPIO as TIM3 PWM */
    GPIO_W_PERIPHERAL_TIM4_PWM          = 28, /**< GPIO as TIM4 PWM */
    GPIO_W_PERIPHERAL_TIM5_PWM          = 29, /**< GPIO as TIM5 PWM */
    GPIO_W_PERIPHERAL_TIM6_PWM          = 30, /**< GPIO as TIM6 PWM */
    GPIO_W_PERIPHERAL_TIM7_PWM          = 31, /**< GPIO as TIM7 PWM */
    GPIO_W_PERIPHERAL_TIM8_PWM          = 32, /**< GPIO as TIM8 PWM */
    GPIO_W_PERIPHERAL_TIM9_PWM          = 33, /**< GPIO as TIM9 PWM */
    GPIO_W_PERIPHERAL_TIM10_PWM         = 34, /**< GPIO as TIM10 PWM */
    GPIO_W_PERIPHERAL_TIM1_1SHOT_PULSE  = 35, /**< GPIO as TIM1 1SHOT pulse */
    GPIO_W_PERIPHERAL_TIM2_1SHOT_PULSE  = 36, /**< GPIO as TIM2 1SHOT pulse */
    GPIO_W_PERIPHERAL_TIM3_1SHOT_PULSE  = 37, /**< GPIO as TIM3 1SHOT pulse */
    GPIO_W_PERIPHERAL_TIM4_1SHOT_PULSE  = 38, /**< GPIO as TIM4 1SHOT pulse */
    GPIO_W_PERIPHERAL_TIM5_1SHOT_PULSE  = 39, /**< GPIO as TIM5 1SHOT pulse */
    GPIO_W_PERIPHERAL_TIM6_1SHOT_PULSE  = 40, /**< GPIO as TIM6 1SHOT pulse */
    GPIO_W_PERIPHERAL_TIM7_1SHOT_PULSE  = 41, /**< GPIO as TIM7 1SHOT pulse */
    GPIO_W_PERIPHERAL_TIM8_1SHOT_PULSE  = 42, /**< GPIO as TIM8 1SHOT pulse */
    GPIO_W_PERIPHERAL_TIM9_1SHOT_PULSE  = 43, /**< GPIO as TIM9 1SHOT pulse */
    GPIO_W_PERIPHERAL_TIM10_1SHOT_PULSE = 44, /**< GPIO as TIM10 1SHOT pulse */
    GPIO_W_PERIPHERAL_USB_SOF           = 45, /**< GPIO as USB SOF */
    GPIO_W_PERIPHERAL_ADC               = 46, /**< GPIO as ADC (dedicated pin) */
    GPIO_W_PERIPHERAL_PCM_DI            = 47, /**< GPIO as PCM DI */
    GPIO_W_PERIPHERAL_PCM_MCLK          = 48, /**< GPIO as PCM ΜCLK */
    GPIO_W_PERIPHERAL_PCM_DO            = 49, /**< GPIO as PCM DO */
    GPIO_W_PERIPHERAL_PCM_BCLK          = 50, /**< GPIO as PCM ΒCLK */
    GPIO_W_PERIPHERAL_PCM_CLK           = 51, /**< GPIO as PCM CLK */
    GPIO_W_PERIPHERAL_DMIC_CLK          = 52, /**< GPIO as DMIC CLK */
    GPIO_W_PERIPHERAL_DMIC_DATA         = 53, /**< GPIO as DMIC DATA */
    GPIO_W_PERIPHERAL_TEST_CLOCK        = 54, /**< GPIO as TEST CLOCK */
    GPIO_W_PERIPHERAL_CMAC_DIAG         = 55, /**< GPIO as CMAC DIAG */
    GPIO_W_PERIPHERAL_COEX_REQ          = 56, /**< GPIO as COEX REQ */
    GPIO_W_PERIPHERAL_COEX_CNT          = 57, /**< GPIO as COEX CNT */
    GPIO_W_PERIPHERAL_COEX_PRI          = 58, /**< GPIO as COEX PRI */
#endif
} gpio_w_peripheral_t;

// TIN_HACK_WIFI - TEMP for keeping r_ble_gtl.c compatible with both rrq and da during the transition
#define IOPORT_CFG_IRQ_ENABLE            GPIO_W_CFG_IRQ_ENABLE

/** GPIO_W private control block. DO NOT MODIFY. Initialization occurs when R_GPIO_W_Open() is called. */
typedef struct st_gpio_w_instance_ctrl
{
    uint32_t            open;
    void const        * p_context;
    volatile uint32_t * p_reg_p0_data;
    volatile uint32_t * p_reg_p0_set_data;
    volatile uint32_t * p_reg_p0_reset_data;
    volatile uint32_t * p_reg_p0_00_mode;
} gpio_w_instance_ctrl_t;

/* TIN-TODO: HW dependent types should be guarded with features, not device families. */
#if !defined(BSP_MCU_GROUP_RA6W1)

/** Pins power configuration structure */
typedef struct e_pad_power_t
{
    uint32_t p0_pwr;                   /**< Pins output power for P0 */
    uint32_t p1_pwr;                   /**< Pins output power for P1 */
 #if BSP_FEATURE_IO_PORT2_GPIO_COUNT > 0
    uint16_t p2_pwr;                   /**< Pins output Power for P2 */
 #endif
} pad_power_t;

/** Pins driving strength configuration structure */
typedef struct e_pad_weak_t
{
 #if BSP_FEATURE_IO_HAS_WEAK_CONFIG_PER_PORT
    uint32_t p0_pwr;                   /**< Pins driving strength for P0 */
    uint32_t p1_pwr;                   /**< Pins driving strength for P1 */
  #if BSP_FEATURE_IO_PORT2_GPIO_COUNT > 0
    uint32_t p2_pwr;                   /**< Pins driving strength for P2 */
  #endif
 #else
    uint32_t aggregate;
 #endif
} pad_weak_t;

/* TIN-TODO: Selecting a clock output is supported through GPIO_CLK_SEL_REG but was not implemented. */
/** Map clock output to selectable pin structure */
typedef struct e_sel_pin_clk_out_t
{
    bsp_io_clk_func_t clk_sel;         /**< Select which clock to map */
    bool              clk_en;          /**< Enable mapping of the selected clock signal */
} sel_pin_clk_out_t;

/** Extended configuration struct */
typedef struct st_gpio_w_extended_cfg
{
    pad_power_t         power;             /**< Pins power configuration */
    pad_weak_t          weak_pad_power;    /**< Pins driving strength configuration */
    bsp_io_clk_output_t fixed_pin_clk_out; /**< Map clock output to fixed pin */
    sel_pin_clk_out_t   sel_pin_clk_out;   /**< Map clock output to selectable pin */
} gpio_w_extended_cfg_t;
#endif

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const ioport_api_t g_ioport_on_gpio_w;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/

fsp_err_t R_GPIO_W_Open(ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg);
fsp_err_t R_GPIO_W_Close(ioport_ctrl_t * const p_ctrl);
fsp_err_t R_GPIO_W_PinsCfg(ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg);
fsp_err_t R_GPIO_W_PinCfg(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, uint32_t cfg);
fsp_err_t R_GPIO_W_PinEventInputRead(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_event);
fsp_err_t R_GPIO_W_PinEventOutputWrite(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t pin_value);
fsp_err_t R_GPIO_W_PinRead(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_value);
fsp_err_t R_GPIO_W_PinWrite(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t level);
fsp_err_t R_GPIO_W_PortDirectionSet(ioport_ctrl_t * const p_ctrl,
                                    bsp_io_port_t         port,
                                    ioport_size_t         direction_values,
                                    ioport_size_t         mask);
fsp_err_t R_GPIO_W_PortEventInputRead(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * event_data);
fsp_err_t R_GPIO_W_PortEventOutputWrite(ioport_ctrl_t * const p_ctrl,
                                        bsp_io_port_t         port,
                                        ioport_size_t         event_data,
                                        ioport_size_t         mask_value);
fsp_err_t R_GPIO_W_PortRead(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * p_port_value);
fsp_err_t R_GPIO_W_PortWrite(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t value, ioport_size_t mask);

/*******************************************************************************************************************//**
 * @} (end defgroup GPIO_W)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_GPIO_W_H
