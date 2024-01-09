/**
 *******************************************************************************
 * @file  ev_hc32f460_lqfp100_v2.h
 * @brief This file contains all the functions prototypes of the
 *        EV_HC32F460_LQFP100_V2 BSP driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-10-31       CDT             Add XTAL/XTAL32 IO define
   2023-09-30       CDT             Add include file named hc32_ll_fcm.h and add declaration of BSP_XTAL32_Init()
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
#ifndef __EV_HC32F460_LQFP100_V2_H__
#define __EV_HC32F460_LQFP100_V2_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_aos.h"
#include "hc32_ll_clk.h"
#include "hc32_ll_dma.h"
#include "hc32_ll_efm.h"
#include "hc32_ll_fcg.h"
#include "hc32_ll_fcm.h"
#include "hc32_ll_gpio.h"
#include "hc32_ll_i2c.h"
#include "hc32_ll_i2s.h"
#include "hc32_ll_interrupts.h"
#include "hc32_ll_keyscan.h"
#include "hc32_ll_pwc.h"
#include "hc32_ll_spi.h"
#include "hc32_ll_sram.h"
#include "hc32_ll_usart.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F460_LQFP100_V2
 * @{
 */

/**
 * @addtogroup EV_HC32F460_LQFP100_V2_BASE
 * @{
 */

#if (BSP_EV_HC32F460_LQFP100_V2 == BSP_EV_HC32F4XX)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F460_LQFP100_V2_Global_Macros EV_HC32F460_LQFP100_V2 Global Macros
 * @{
 */

/**
 * @defgroup BSP_I2C_Configuration BSP I2C Configuration
 * @{
 */
#define BSP_I2C_BAUDRATE        (100000UL)
#define BSP_I2C_TIMEOUT         (0x40000U)
/**
 * @}
 */

/**
 * @defgroup EV_HC32F460_LQFP100_V2_KEY_Sel EV_HC32F460_LQFP100_V2 KEY definition
 * @{
 */
#define BSP_KEY_1               (0x0001UL)    /*!< BSP KEY 1 */
#define BSP_KEY_2               (0x0002UL)    /*!< BSP KEY 2 */
#define BSP_KEY_3               (0x0004UL)    /*!< BSP KEY 3 */
#define BSP_KEY_4               (0x0010UL)    /*!< BSP KEY 4 */
#define BSP_KEY_5               (0x0020UL)    /*!< BSP KEY 5 */
#define BSP_KEY_6               (0x0040UL)    /*!< BSP KEY 6 */
#define BSP_KEY_7               (0x0100UL)    /*!< BSP KEY 7 */
#define BSP_KEY_8               (0x0200UL)    /*!< BSP KEY 8 */
#define BSP_KEY_9               (0x0400UL)    /*!< BSP KEY 9 */
#define BSP_KEY_10              (0x0800UL)    /*!< BSP KEY 10. Independent key. */
/**
 * @}
 */

/**
 * @defgroup EV_HC32F460_LQFP100_V2_LED_Sel EV_HC32F460_LQFP100_V2 LED definition
 * @{
 */
#define LED_RED                 (0x01U)
#define LED_GREEN               (0x02U)
#define LED_YELLOW              (0x04U)
#define LED_BLUE                (0x08U)
#define LED_ALL                 (LED_RED | LED_GREEN | LED_YELLOW | LED_BLUE)
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup EV_HC32F460_LQFP100_V2_Local_Macros EV_HC32F460_LQFP100_V2 Local Macros
 * @{
 */

/**
 * @defgroup EV_HC32F460_LQFP100_V2_LED_Number EV_HC32F460_LQFP100_V2 LED Number
 * @{
 */
#define BSP_LED_NUM             (4U)
/**
 * @}
 */

/**
 * @defgroup EV_HC32F460_LQFP100_V2_LED_PortPin_Sel EV_HC32F460_LQFP100_V2 LED port/pin definition
 * @{
 */
#define BSP_LED_RED_PORT        (GPIO_PORT_D)
#define BSP_LED_RED_PIN         (GPIO_PIN_03)
#define BSP_LED_GREEN_PORT      (GPIO_PORT_D)
#define BSP_LED_GREEN_PIN       (GPIO_PIN_04)
#define BSP_LED_YELLOW_PORT     (GPIO_PORT_D)
#define BSP_LED_YELLOW_PIN      (GPIO_PIN_05)
#define BSP_LED_BLUE_PORT       (GPIO_PORT_D)
#define BSP_LED_BLUE_PIN        (GPIO_PIN_06)
/**
 * @}
 */

/**
 * @defgroup EV_HC32F460_LQFP100_V2_KEY_Number EV_HC32F460_LQFP100_V2 KEY Number
 * @{
 */
#define BSP_KEY_ROW_NUM         (3U)
#define BSP_KEY_COL_NUM         (3U)
#define BSP_KEY_INDEPENDENT_NUM (1U)
/**
 * @}
 */

/**
 * @defgroup EV_HC32F460_LQFP100_V2_KEY_PortPin EV_HC32F460_LQFP100_V2 KEY port/pin definition
 * @{
 */
#define BSP_KEY_KEY10_PORT      (GPIO_PORT_B)
#define BSP_KEY_KEY10_PIN       (GPIO_PIN_01)
#define BSP_KEY_KEY10_EXTINT    (EXTINT_CH01)
#define BSP_KEY_KEY10_INT_SRC   (INT_SRC_PORT_EIRQ1)
#define BSP_KEY_KEY10_IRQn      (INT025_IRQn)
#define BSP_KEY_KEY10_WAKEUP    (INTC_STOP_WKUP_EXTINT_CH1)
#define BSP_KEY_KEY10_EVT       (EVT_SRC_PORT_EIRQ1)

#define BSP_KEYOUT0_PORT        (GPIO_PORT_A)
#define BSP_KEYOUT0_PIN         (GPIO_PIN_04)
#define BSP_KEYOUT1_PORT        (GPIO_PORT_A)
#define BSP_KEYOUT1_PIN         (GPIO_PIN_05)
#define BSP_KEYOUT2_PORT        (GPIO_PORT_A)
#define BSP_KEYOUT2_PIN         (GPIO_PIN_06)

#define BSP_KEYIN0_PORT         (GPIO_PORT_D)
#define BSP_KEYIN0_PIN          (GPIO_PIN_12)
#define BSP_KEY_ROW0_EXTINT     (EXTINT_CH12)
#define BSP_KEY_ROW0_INT_SRC    (INT_SRC_PORT_EIRQ12)
#define BSP_KEY_ROW0_IRQn       (INT029_IRQn)

#define BSP_KEYIN1_PORT         (GPIO_PORT_D)
#define BSP_KEYIN1_PIN          (GPIO_PIN_13)
#define BSP_KEY_ROW1_EXTINT     (EXTINT_CH13)
#define BSP_KEY_ROW1_INT_SRC    (INT_SRC_PORT_EIRQ13)
#define BSP_KEY_ROW1_IRQn       (INT030_IRQn)

#define BSP_KEYIN2_PORT         (GPIO_PORT_D)
#define BSP_KEYIN2_PIN          (GPIO_PIN_14)
#define BSP_KEY_ROW2_EXTINT     (EXTINT_CH14)
#define BSP_KEY_ROW2_INT_SRC    (INT_SRC_PORT_EIRQ14)
#define BSP_KEY_ROW2_IRQn       (INT031_IRQn)
/**
 * @}
 */

/**
 * @defgroup EV_HC32F460_LQFP100_V2_KEYSCAN_CONFIG EV_HC32F460_LQFP100_V2 KEYSCAN Configure definition
 * @{
 */
#define BSP_KEYOUT_SELECT       (KEYSCAN_OUT_0T2)
#define BSP_KEYIN_SELECT        (KEYSCAN_IN_12 | KEYSCAN_IN_13 | KEYSCAN_IN_14)
/**
 * @}
 */

/**
 * @defgroup EV_HC32F460_LQFP100_V2_PRINT_CONFIG EV_HC32F460_LQFP100_V2 PRINT Configure definition
 * @{
 */
#define BSP_PRINTF_DEVICE               (CM_USART4)
#define BSP_PRINTF_DEVICE_FCG           (FCG1_PERIPH_USART4)

#define BSP_PRINTF_BAUDRATE             (115200)
#define BSP_PRINTF_BAUDRATE_ERR_MAX     (0.025F)

#define BSP_PRINTF_PORT                 (GPIO_PORT_E)
#define BSP_PRINTF_PIN                  (GPIO_PIN_06)
#define BSP_PRINTF_PORT_FUNC            (GPIO_FUNC_36)
/**
 * @}
 */

/**
 * @defgroup EV_HC32F460_LQFP100_V2_XTAL_CONFIG EV_HC32F460_LQFP100_V2 XTAL Configure definition
 * @{
 */
#define BSP_XTAL_PORT                   (GPIO_PORT_H)
#define BSP_XTAL_IN_PIN                 (GPIO_PIN_01)
#define BSP_XTAL_OUT_PIN                (GPIO_PIN_00)
/**
 * @}
 */

/**
 * @defgroup EV_HC32F460_LQFP100_V2_XTAL32_CONFIG EV_HC32F460_LQFP100_V2 XTAL32 Configure definition
 * @{
 */
#define BSP_XTAL32_PORT                 (GPIO_PORT_C)
#define BSP_XTAL32_IN_PIN               (GPIO_PIN_15)
#define BSP_XTAL32_OUT_PIN              (GPIO_PIN_14)
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
 * @addtogroup EV_HC32F460_LQFP100_V2_Global_Functions
 * @{
 */
int32_t BSP_XTAL32_Init(void);
void BSP_CLK_Init(void);

void BSP_KEY_Init(void);
en_flag_status_t BSP_KEY_GetStatus(uint32_t u32Key);

void BSP_LED_Init(void);
void BSP_LED_On(uint8_t u8Led);
void BSP_LED_Off(uint8_t u8Led);
void BSP_LED_Toggle(uint8_t u8Led);

#if (LL_PRINT_ENABLE == DDL_ON)
int32_t BSP_PRINTF_Preinit(void *vpDevice, uint32_t u32Baudrate);
#endif

/* It can't get the status of the KEYx by calling BSP_KEY_GetStatus when you re-implement BSP_KEY_KEYx_IrqHandler. */
void BSP_KEY_KEY10_IrqHandler(void);

#if (LL_I2C_ENABLE == DDL_ON)
int32_t BSP_I2C_Init(CM_I2C_TypeDef *I2Cx);
void BSP_I2C_DeInit(CM_I2C_TypeDef *I2Cx);
int32_t BSP_I2C_Write(CM_I2C_TypeDef *I2Cx, uint16_t u16DevAddr, const uint8_t *pu8Reg, uint8_t u8RegLen, const uint8_t *pu8Buf, uint32_t u32Len);
int32_t BSP_I2C_Read(CM_I2C_TypeDef *I2Cx, uint16_t u16DevAddr, const uint8_t *pu8Reg, uint8_t u8RegLen, uint8_t *pu8Buf, uint32_t u32Len);
int32_t BSP_I2C_GetDevStatus(CM_I2C_TypeDef *I2Cx, uint16_t u16DevAddr);
#endif /* LL_I2C_ENABLE */

/**
 * @}
 */

#endif /* BSP_EV_HC32F460_LQFP100_V2 */
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

#endif /* __EV_HC32F460_LQFP100_V2_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
