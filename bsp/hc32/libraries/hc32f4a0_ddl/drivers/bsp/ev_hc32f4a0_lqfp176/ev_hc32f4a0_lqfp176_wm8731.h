/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_wm8731.h
 * @brief This file contains all the functions prototypes for wm8731 of the
 *        board EV_HC32F4A0_LQFP176.
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
#ifndef __EV_HC32F4A0_LQFP176_WM8731_H__
#define __EV_HC32F4A0_LQFP176_WM8731_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "wm8731.h"
#include "ev_hc32f4a0_lqfp176.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176_WM8731
 * @{
 */

#if ((BSP_WM8731_ENABLE == DDL_ON) && (BSP_EV_HC32F4A0_LQFP176 == BSP_EV_HC32F4XX))

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F4A0_LQFP176_WM8731_Global_Macros  EV_HC32F4A0_LQFP176 WM8731 Global Macros
 * @{
 */

/* WM8731 device address */
#define BSP_WM8731_DEV_ADDR                     (0x1AU)
#define BSP_WM8731_REG_ADDR_LEN                 (1U)

/**
 * @defgroup BSP_WM8731_I2C_Configure BSP WM8731 I2C Configure
 * @{
 */
/* I2C configuration define */
#define BSP_WM8731_I2C_UNIT                     (CM_I2C1)
#define BSP_WM8731_I2C_FCG                      (FCG1_PERIPH_I2C1)

/* SCL = PD3 */
#define BSP_WM8731_I2C_SCL_PORT                 (GPIO_PORT_D)
#define BSP_WM8731_I2C_SCL_PIN                  (GPIO_PIN_03)
#define BSP_WM8731_I2C_SCL_FUNC                 (GPIO_FUNC_49)
/* SDA = PF10 */
#define BSP_WM8731_I2C_SDA_PORT                 (GPIO_PORT_F)
#define BSP_WM8731_I2C_SDA_PIN                  (GPIO_PIN_10)
#define BSP_WM8731_I2C_SDA_FUNC                 (GPIO_FUNC_48)
/**
 * @}
 */

/**
 * @defgroup BSP_WM8731_DMA_Configure BSP WM8731 DMA Configure
 * @{
 */
/* I2S DMA configuration define */
#define BSP_WM8731_DMA_UNIT                     (CM_DMA1)
#define BSP_WM8731_DMA_CLK                      (FCG0_PERIPH_DMA1 | FCG0_PERIPH_AOS)

#define BSP_WM8731_DMA_SD_CH                    (DMA_CH0)
#define BSP_WM8731_DMA_SD_INT_CH                (DMA_INT_TC_CH0)
#define BSP_WM8731_DMA_SD_TRIG_CH               (AOS_DMA1_0)
#define BSP_WM8731_DMA_SD_INT_SRC               (INT_SRC_DMA1_TC0)
#define BSP_WM8731_DMA_SD_IRQ                   (INT006_IRQn)

#define BSP_WM8731_DMA_SDIN_CH                  (DMA_CH1)
#define BSP_WM8731_DMA_SDIN_INT_CH              (DMA_INT_TC_CH1)
#define BSP_WM8731_DMA_SDIN_TRIG_CH             (AOS_DMA1_1)
#define BSP_WM8731_DMA_SDIN_INT_SRC             (INT_SRC_DMA1_TC1)
#define BSP_WM8731_DMA_SDIN_IRQ                 (INT007_IRQn)
/**
 * @}
 */

/**
 * @defgroup BSP_WM8731_I2S_Configure BSP WM8731 I2S Configure
 * @{
 */
/* I2S configuration define */
#define BSP_WM8731_I2S_UNIT                     (CM_I2S1)
#define BSP_WM8731_I2S_CLK                      (FCG1_PERIPH_I2S1)
#define BSP_WM8731_I2S_CLK_CH                   (CLK_I2S1)
#define BSP_WM8731_I2S_CLK_SRC                  (CLK_PERIPHCLK_PCLK)
#define BSP_WM8731_I2S_SD_EVT_SRC               (EVT_SRC_I2S1_TXIRQOUT)
#define BSP_WM8731_I2S_SDIN_EVT_SRC             (EVT_SRC_I2S1_RXIRQOUT)
/* CK = PF6 */
#define BSP_WM8731_I2S_CK_PORT                  (GPIO_PORT_F)
#define BSP_WM8731_I2S_CK_PIN                   (GPIO_PIN_06)
#define BSP_WM8731_I2S_CK_FUNC                  (GPIO_FUNC_54)
/* WS = PF8 */
#define BSP_WM8731_I2S_WS_PORT                  (GPIO_PORT_F)
#define BSP_WM8731_I2S_WS_PIN                   (GPIO_PIN_08)
#define BSP_WM8731_I2S_WS_FUNC                  (GPIO_FUNC_55)
/* SD = PF7 */
#define BSP_WM8731_I2S_SD_PORT                  (GPIO_PORT_F)
#define BSP_WM8731_I2S_SD_PIN                   (GPIO_PIN_07)
#define BSP_WM8731_I2S_SD_FUNC                  (GPIO_FUNC_56)
/* SDIN = PI2 */
#define BSP_WM8731_I2S_SDIN_PORT                (GPIO_PORT_I)
#define BSP_WM8731_I2S_SDIN_PIN                 (GPIO_PIN_02)
#define BSP_WM8731_I2S_SDIN_FUNC                (GPIO_FUNC_17)
/* EXCK = PG7 */
#define BSP_WM8731_I2S_EXCK_PORT                (GPIO_PORT_G)
#define BSP_WM8731_I2S_EXCK_PIN                 (GPIO_PIN_07)
#define BSP_WM8731_I2S_EXCK_FUNC                (GPIO_FUNC_17)
/* MCK = PA5 */
#define BSP_WM8731_I2S_MCK_PORT                 (GPIO_PORT_A)
#define BSP_WM8731_I2S_MCK_PIN                  (GPIO_PIN_05)
#define BSP_WM8731_I2S_MCK_FUNC                 (GPIO_FUNC_17)

/* The data size for transfer and receive */
#define BSP_WM8731_DMA_BLK_SIZE                 (1U)
#define BSP_WM8731_DMA_BLK_LEN                  (512U)
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
 * @addtogroup EV_HC32F4A0_LQFP176_WM8731_Global_Functions
 * @{
 */
void BSP_WM8731_DeInit(void);
int32_t BSP_WM8731_Init(uint8_t u8InputDevice, uint8_t u8OutputDevice,
                        uint8_t u8Volume, uint32_t u32AudioFreq, uint8_t u8DataWidth);
void BSP_WM8731_Play(uint32_t *pu32WriteBuf, uint16_t u16Size);
void BSP_WM8731_Record(uint32_t *pu32ReadBuf, uint16_t u16Size);
void BSP_WM8731_Stop(void);
void BSP_WM8731_SetFreq(uint32_t u32AudioFreq);
void BSP_WM8731_SetVolume(uint8_t u8Volume);

/* User has to implement these functions in his code if they are needed */
void BSP_WM8731_TransCompleteCallBack(void);
void BSP_WM8731_ReceiveCompleteCallBack(void);
void BSP_I2S_DeInit(void);
int32_t BSP_I2S_Init(uint32_t u32AudioFreq);

/**
 * @}
 */

#endif /* (BSP_WM8731_ENABLE && BSP_EV_HC32F4A0_LQFP176) */

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

#endif /* __EV_HC32F4A0_LQFP176_WM8731_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
