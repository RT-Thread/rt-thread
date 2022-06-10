/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_conf.h"

#ifdef HAL_PWM_MODULE_ENABLED

/** @addtogroup RK_HAL_Driver
  * @{
  */

/** @addtogroup PWM
  * @{
  */

#ifndef __HAL_PWM_H
#define __HAL_PWM_H

#include "hal_def.h"

/***************************** MACRO Definition ******************************/
/** @defgroup PWM_Exported_Definition_Group1 Basic Definition
 *  @{
 */

#define HAL_PWM_NUM_CHANNELS   (HAL_ARRAY_SIZE(((struct PWM_REG *)0)->CHANNELS))
#define PWM_PWRMATCH_MAX_COUNT (10)

/***************************** Structure Definition **************************/

typedef enum {
    HAL_PWM_ONE_SHOT = 0,
    HAL_PWM_CONTINUOUS,
    HAL_PWM_CAPTURE,
} ePWM_Mode;

/**
  * @brief  PWM HW information definition
  */
struct HAL_PWM_DEV {
    struct PWM_REG *pReg;
    uint32_t clkID;
    uint32_t clkGateID;
    uint32_t pclkGateID;
    IRQn_Type irqNum;
};

/**
  * @brief  PWM handle Structure definition
  */
struct HAL_PWM_CONFIG {
    uint8_t channel;
    uint32_t periodNS;
    uint32_t dutyNS;
    bool polarity;
};

/**
  * @brief  PWM capture data
  */
struct PWM_CAPTURE {
    uint32_t period;
    bool pol;
    bool active;
};

/**
  * @brief  PWM match data
  */
struct PWM_MATCH {
    uint32_t match[PWM_PWRMATCH_MAX_COUNT];
    uint8_t matchCount;
    uint16_t lpreMin;
    uint16_t lpreMax;
    uint16_t hpreMin;
    uint16_t hpreMax;
    uint16_t ldMin;
    uint16_t ldMax;
    uint16_t hdZeroMin;
    uint16_t hdZeroMax;
    uint16_t hdOneMin;
    uint16_t hdOneMax;
};

/**
  * @brief  PWM Handle Structure definition
  */

struct PWM_HANDLE {
    struct PWM_REG *pReg;
    uint32_t freq;
    ePWM_Mode mode[HAL_PWM_NUM_CHANNELS];
    struct PWM_CAPTURE result[HAL_PWM_NUM_CHANNELS];
};

/**
  * @}
  */

/***************************** Function Declare ******************************/
/** @defgroup PWM_Public_Function_Declare Public Function Declare
 *  @{
 */

HAL_Status HAL_PWM_IRQHandler(struct PWM_HANDLE *pPWM);
HAL_Status HAL_PWM_SetConfig(struct PWM_HANDLE *pPWM, uint8_t channel,
                             const struct HAL_PWM_CONFIG *config);
HAL_Status HAL_PWM_SetOneshot(struct PWM_HANDLE *pPWM, uint8_t channel, uint32_t count);
HAL_Status HAL_PWM_SetCapturedFreq(struct PWM_HANDLE *pPWM, uint8_t channel, uint32_t freq);
HAL_Status HAL_PWM_SetMatch(struct PWM_HANDLE *pPWM, uint8_t channel, const struct PWM_MATCH *data);
ePWM_Mode HAL_PWM_GetMode(struct PWM_HANDLE *pPWM, uint8_t channel);
HAL_Status HAL_PWM_Enable(struct PWM_HANDLE *pPWM, uint8_t channel, ePWM_Mode mode);
HAL_Status HAL_PWM_Disable(struct PWM_HANDLE *pPWM, uint8_t channel);
HAL_Status HAL_PWM_Init(struct PWM_HANDLE *pPWM, struct PWM_REG *pReg, uint32_t freq);
HAL_Status HAL_PWM_DeInit(struct PWM_HANDLE *pPWM);

/** @} */

#endif

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_PWM_MODULE_ENABLED */
