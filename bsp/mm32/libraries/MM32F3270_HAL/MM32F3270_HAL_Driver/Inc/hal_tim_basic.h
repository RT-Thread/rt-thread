/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_TIM_BASIC_H__
#define __HAL_TIM_BASIC_H__

#include "hal_common.h"

/*!
 * @addtogroup TIM_BASIC
 * @{
 */

/*!
 * @brief TIM_BASIC driver version number.
 */
#define TIM_BASIC_DRIVER_VERSION 0u /*!< TIM_BASIC_0. */

/*!
 * @addtogroup TIM_BASIC_INT
 * @brief Enable interrupt.
 * @{
 */
#define TIM_BASIC_INT_UPDATE_PERIOD           (1u << 0u) /*!< Timer update period interrupt switchers. */
/*!
 * @}
 */

/*!
 * @addtogroup TIM_BASIC_DMA
 * @brief Enable DMA.
 * @{
 */
#define TIM_BASIC_DMA_UPDATE_PERIOD           (1u << 8u) /*!< Timer update period interrupt switchers. */
/*!
 * @}
 */

/*!
 * @addtogroup TIM_BASIC_INT_STATUS
 * @brief Check interrupt status.
 * @{
 */
#define TIM_BASIC_STATUS_UPDATE_PERIOD            (1u << 0u) /*!< Timer update period interrupt flag. */
/*!
 * @}
 */

/*!
 * @addtogroup TIM_BASIC_SWTRG
 * @brief Events to be triggered by software.
 * @{
 */
#define TIM_BASIC_SWTRG_UPDATE_PERIOD            (1u << 0u) /*!< Timer update period trigger. */
/*!
 * @}
 */

/*!
 * @brief Counter period working mode.
 */
typedef enum
{
    TIM_BASIC_PeriodMode_Continuous = 0u, /*!< The counter would count from zero to indicated period value then generate an update circularly. */
    TIM_BASIC_PeriodMode_OneTimeRun = 1u, /*!< The counter would count from zero to indicated period value then generate an update then stop. */
} TIM_BASIC_PeriodMode_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref TIM_BASIC_Init() to initialize the TIM module time base unit.
 */
typedef struct
{
    uint32_t ClockFreqHz;                   /*!< Frequence of clock source for counter. */
    uint32_t StepFreqHz;                    /*!< Step length value. Counter's StepFreqHz = ClockSourceFreqHz / (ClockSourceDiv+1). */
    uint32_t Period;                        /*!< Counter counting period length, from 0 to Period. */
    bool EnablePreloadPeriod;               /*!< Enable the preload of period value. If enable, it will be updated in next period, otherwise immediately. */
    TIM_BASIC_PeriodMode_Type PeriodMode;   /*!< Counting working mode. */
} TIM_BASIC_Init_Type;

/*!
 * @brief Set the timer's step for indicated TIM module.
 *
 * @param TIMx TIM_BASIC instance.
 * @param init Pointer to the initialization structure. See to @ref TIM_BASIC_Init_Type.
 * @return 'true' to set the timer's step successfully, 'false' to fail because the invalid StepFreqHz.
 */
bool TIM_BASIC_Init(TIM_BASIC_Type * TIMx, TIM_BASIC_Init_Type * init);

/*!
 * @brief Start counting.
 *
 * @param TIMx TIM_BASIC instance.
 * @return None.
 */
void TIM_BASIC_Start(TIM_BASIC_Type * TIMx);

/*!
 * @brief Stop counting immediately.
 *
 * @param TIMx TIM_BASIC instance.
 * @return None.
 */
void TIM_BASIC_Stop(TIM_BASIC_Type * TIMx);

/*!
 * @brief Get the indicated TIMx Counter value.
 *
 * @param TIMx TIM_BASIC_Type instance.
 * @return The current value of the counter register.
 */
uint32_t TIM_BASIC_GetCounterValue(TIM_BASIC_Type * TIMx);

/*!
 * @brief Enable the TIM_BASIC interrupts.
 *
 * @param TIMx TIM_BASIC_Type instance.
 * @param interrupts Interrupts to be enabled.See to @ref TIM_BASIC_INT.
 * @param enable 'true' to enable the indicated interrupts or DMAs, 'false' to disable the indicated interrupts or DMAs.
 * @return None.
 */
void TIM_BASIC_EnableInterrupts(TIM_BASIC_Type *TIMx, uint32_t interrupts, bool enable);

/*!
 * @brief Enable the TIM_BASIC DMAs.
 *
 * @param TIMx TIM_BASIC_Type instance.
 * @param dmas DMA masks to be enabled. See to @ref TIM_BASIC_DMA.
 * @param enable 'true' to enable the indicated interrupts or DMAs, 'false' to disable the indicated interrupts or DMAs.
 * @return None.
 */
void TIM_BASIC_EnableDMA(TIM_BASIC_Type *TIMx, uint32_t dmas, bool enable);

/*!
 * @brief Software trigger events to call interrupts or DMAs.
 *
 * Can simultaneously trigger multiple events.
 *
 * @param TIMx TIM_BASIC instance. See to @ref TIM_BASIC_SWTRG.
 * @param swtrgs Trigger the events to generate interrupts.
 */
void TIM_BASIC_DoSwTrigger(TIM_BASIC_Type *TIMx, uint32_t swtrgs);

/*!
 * @brief Get the status of the indicated timer.
 *
 * @param TIMx TIM_BASIC_Type instance.
 * @return Interrupt status flags. See to @ref TIM_BASIC_INT_STATUS.
 */
uint32_t TIM_BASIC_GetInterruptStatus(TIM_BASIC_Type * TIMx);

/*!
 * @brief Clear the status of indicated interrupt.
 *
 * @param TIMx TIM_BASIC_Type instance.
 * @param status The required clear flag type. See to @ref TIM_BASIC_INT_STATUS.
 * @return None.
 */
void TIM_BASIC_ClearInterruptStatus(TIM_BASIC_Type *TIMx, uint32_t status);

/*!
 *@}
 */
#endif /* __HAL_TIM_BASIC_H__ */

