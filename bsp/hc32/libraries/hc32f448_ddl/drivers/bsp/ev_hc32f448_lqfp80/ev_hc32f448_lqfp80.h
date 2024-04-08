/**
 *******************************************************************************
 * @file  ev_hc32f448_lqfp80.h
 * @brief This file contains all the functions prototypes of the
 *        EV_HC32F448_LQFP80 BSP driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
   2023-09-30       CDT             Add include file named hc32_ll_fcm.h and add declaration of BSP_XTAL32_Init()
                                    Modify I2C baudrate: 400000 -> 100000
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
#ifndef __EV_HC32F448_LQFP80_H__
#define __EV_HC32F448_LQFP80_H__

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
#include "hc32_ll_efm.h"
#include "hc32_ll_fcg.h"
#include "hc32_ll_fcm.h"
#include "hc32_ll_gpio.h"
#include "hc32_ll_i2c.h"
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
 * @addtogroup EV_HC32F448_LQFP80
 * @{
 */


#if (BSP_EV_HC32F448_LQFP80 == BSP_EV_HC32F4XX)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup BSP_Global_Macros BSP Global Macros
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
 * @defgroup BSP_KEY_Sel BSP Key definition
 * @{
 */
#define BSP_KEY_1               (0x0008UL)    /*!< BSP KEY 1 */
#define BSP_KEY_2               (0x0080UL)    /*!< BSP KEY 2 */
#define BSP_KEY_3               (0x0800UL)    /*!< BSP KEY 3 */
#define BSP_KEY_4               (0x8000UL)    /*!< BSP KEY 4 */
#define BSP_KEY_5               (0x10000UL)   /*!< BSP KEY 5. Independent key. */
/**
 * @}
 */

/**
 * @defgroup EV_HC32F448_LQFP80_KEY_Number EV_HC32F448_LQFP80 KEY Number
 * @{
 */
#define BSP_KEY_ROW_NUM         (2U)
#define BSP_KEY_COL_NUM         (2U)
#define BSP_KEY_INDEPENDENT_NUM (1U)
/**
 * @}
 */

/**
 * @defgroup EV_HC32F448_LQFP80_KEY_PortPin EV_HC32F448_LQFP80 KEY port/pin definition
 * @{
 */
#define BSP_KEY_KEY5_PORT       (GPIO_PORT_B)
#define BSP_KEY_KEY5_PIN        (GPIO_PIN_06)
#define BSP_KEY_KEY5_EXTINT     (EXTINT_CH06)
#define BSP_KEY_KEY5_IRQn       (EXTINT_PORT_EIRQ6_IRQn)
#define BSP_KEY_KEY5_WAKEUP     (INTC_STOP_WKUP_EXTINT_CH6)
#define BSP_KEY_KEY5_EVT        (EVT_SRC_PORT_EIRQ6)

#define BSP_KEYOUT3_PORT        (GPIO_PORT_C)
#define BSP_KEYOUT3_PIN         (GPIO_PIN_06)
#define BSP_KEYOUT3_FUNC        (GPIO_FUNC_8)

#define BSP_KEYOUT7_PORT        (GPIO_PORT_D)
#define BSP_KEYOUT7_PIN         (GPIO_PIN_08)
#define BSP_KEYOUT7_FUNC        (GPIO_FUNC_8)

#define BSP_KEYIN0_PORT         (GPIO_PORT_A)
#define BSP_KEYIN0_PIN          (GPIO_PIN_00)
#define BSP_KEY_ROW0_EXTINT     (EXTINT_CH00)
#define BSP_KEY_ROW0_IRQn       (EXTINT_PORT_EIRQ0_IRQn)

#define BSP_KEYIN1_PORT         (GPIO_PORT_A)
#define BSP_KEYIN1_PIN          (GPIO_PIN_01)
#define BSP_KEY_ROW1_EXTINT     (EXTINT_CH01)
#define BSP_KEY_ROW1_IRQn       (EXTINT_PORT_EIRQ1_IRQn)
/**
 * @}
 */

/**
 * @defgroup EV_HC32F448_LQFP80_KEYSCAN_CONFIG EV_HC32F448_LQFP80 KEYSCAN Configure definition
 * @{
 */
#define BSP_KEYOUT_SELECT       (KEYSCAN_OUT_0T7)
#define BSP_KEYIN_SELECT        (KEYSCAN_IN_0 | KEYSCAN_IN_1)
/**
 * @}
 */

/**
 * @defgroup BSP_PRINT_CONFIG BSP PRINT Configure definition
 * @{
 */
#define BSP_PRINTF_DEVICE               (CM_USART2)
#define BSP_PRINTF_DEVICE_FCG           (FCG3_PERIPH_USART2)

#define BSP_PRINTF_BAUDRATE             (115200UL)
#define BSP_PRINTF_BAUDRATE_ERR_MAX     (0.025F)

#define BSP_PRINTF_PORT                 (GPIO_PORT_C)
#define BSP_PRINTF_PIN                  (GPIO_PIN_10)
#define BSP_PRINTF_PORT_FUNC            (GPIO_FUNC_36)
/**
 * @}
 */

/**
 * @defgroup BSP_XTAL_CONFIG BSP XTAL Configure definition
 * @{
 */
#define BSP_XTAL_PORT                    (GPIO_PORT_H)
#define BSP_XTAL_IN_PIN                  (GPIO_PIN_00)
#define BSP_XTAL_OUT_PIN                 (GPIO_PIN_01)
/**
 * @}
 */

/**
 * @defgroup BSP_XTAL32_CONFIG BSP XTAL32 Configure definition
 * @{
 */
#define BSP_XTAL32_PORT                  (GPIO_PORT_C)
#define BSP_XTAL32_IN_PIN                (GPIO_PIN_14)
#define BSP_XTAL32_OUT_PIN               (GPIO_PIN_15)
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
 * @addtogroup BSP_Global_Functions
 * @{
 */
int32_t BSP_XTAL32_Init(void);
void BSP_CLK_Init(void);

void BSP_KEY_Init(void);
en_flag_status_t BSP_KEY_GetStatus(uint32_t u32Key);

#if (LL_PRINT_ENABLE == DDL_ON)
int32_t BSP_PRINTF_Preinit(void *vpDevice, uint32_t u32Baudrate);
#endif

#if (DDL_ON == BSP_INT_KEY_ENABLE)
/* User Callbacks: User has to implement these functions in his code if they're needed. */
void BSP_KEY_KEY5_IrqCallback(void);
#endif

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

#endif /* BSP_EV_HC32F448_LQFP80 */
/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __EV_HC32F448_LQFP80_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
