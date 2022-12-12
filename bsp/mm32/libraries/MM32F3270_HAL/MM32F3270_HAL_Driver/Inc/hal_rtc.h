/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_RTC_H__
#define __HAL_RTC_H__

#include "hal_common.h"
#include "hal_rcc.h"

/*!
 * @addtogroup RTC
 * @{
 */

/*!
 * @addtogroup RTC_STATUS
 * @{
 */
#define RTC_STATUS_OPERATION           RTC_CRL_RTOFF_MASK    /*!< Status flag when write operation of RTC register is completed. */
#define RTC_STATUS_SYNC                RTC_CRL_RSF_MASK      /*!< Status flag when registers synchronized. */
#define RTC_STATUS_CLKRDY              RCC_BDCR_LSERDY_MASK  /*!< Status flag when the clock of LSE is ready. */
/*!
 * @}
 */

/*!
 * @addtogroup RTC_INT
 * @{
 */
#define RTC_INT_SEC                   RTC_CRL_SECF_MASK     /*!< Interrupt enable when seconds interrupt generation or overflow of prescaler. After the flag is generated, RTC counter + 1. */
#define RTC_INT_ALARM                 RTC_CRL_ALRF_MASK     /*!< Interrupt enable when the alarm interrupt is generated, in other words, the value of the alarm counter is the same as the RTC counter. */
#define RTC_INT_OVERFLOW              RTC_CRL_OWF_MASK      /*!< Interrupt enable when overflow interrupt generaton or programmable counter overflow. */
/*!
 * @}
 */

/*!
 * @brief Define the callback function called when the RTC interrupt is done.
 */
typedef void (*RTC_Callback_1_Type)(void *param);

/*!
 * @brief This type of structure instance is used to set and get time when set time and get current time.
 */
typedef struct
{
    uint8_t    Secs;           /*!< Specify the clock seconds. */
    uint8_t    Mins;           /*!< Specify the clock minutes. */
    uint8_t    Hours;          /*!< Specify the clock hours. */
    uint8_t    Days;           /*!< Specify the clock days. */
    uint8_t    Months;         /*!< Specify the clock months. */
    uint16_t   Years;          /*!< Specify the clock years. */
    uint16_t   HYears;         /*!< Specify term of highest years. */
    uint16_t   LYears;         /*!< Specify term of lowest years. */
    uint32_t   Div;            /*!< Specify the number of prescaler. */
} RTC_Init_Type;

typedef struct
{
    uint32_t   WaitTime;       /*!< Specify the time limit for wait to the flag to be generated. If the required flag is not generated after this time, considered as timeout. */
    uint32_t   AlarmTime;      /*!< Specify the number of seconds that alarm clock will respond. */
    RTC_Callback_1_Type SecDoneCallback;  /*!< Callback function, called when the rtc seconds interrupt is done. */
    RTC_Callback_1_Type AlarmDoneCallback;   /*!< Callback function, called when the rtc alarm interrupt is done. */
} RTC_Time_Type;

/*!
 * @brief Initialize the RTC module.
 *
 * Open access to BKP, enable clock source and RTC.
 * RTC starts counting after initialization.
 *
 * @return None.
 */
void RTC_Init(void);

/*!
 * @brief Enable the BKP access module.
 *
 * @param enable 'true' to enable the access to RTC and BKP, 'false' to disable the access to RTC and BKP.
 * @return None.
 */
void RTC_EnableAccess(bool enable);

/*!
 * @brief Enable reset of the RTC module.
 *
 * The register of BKP is reset by the backup domain and is not reset during power reset or system reset.
 *
 * @param enable 'true' to enable the BKP reset, 'false' to disable the BKP reset.
 * @return None.
 */
void RTC_EnableReset(bool enable);

/*!
 * @brief Enable the RTC moudle.
 *
 * @param enable 'true' to enable the module, 'false' to disable the module.
 * @return None.
 */
void RTC_Enable(bool enable);

/*!
 * @brief Get the current status flags of the RTC module.
 *
 * @return Status flags. See to @ref RTC_STATUS.
 */
uint32_t RTC_GetStatus(void);

/*!
 * @brief Clear the status flags of the RTC module.
 *
 * @param status The mask code of the indicated flags to be clear. See to @ref RTC_STATUS.
 * @return None.
 */
void RTC_ClearStatus(uint32_t status);

/*!
 * @brief Get the current clock source status flags of RTC module.
 *
 * @return Status flags. See to @ref RTC_STATUS.
 */
uint32_t RTC_GetClockStatus(void);

/*!
 * @brief Enable the configration of the RTC module.
 *
 * @param enable 'true' to enable the configration module, 'false' to disable the configration module.
 * @return None.
 */
void RTC_EnableConf(bool enable);

/*!
 * @brief Put the data into prescaler register of the RTC module.
 *
 * @param div Data value to be send into the prescaler register.
 * @return None.
 */
void RTC_PutPrescalerData(uint32_t div);

/*!
 * @brief Put the data into counter register of the RTC module.
 *
 * @param cnt Data value to be send into the counter register.
 * @return None.
 */
void RTC_PutCounterData(uint32_t cnt);

/*!
 * @brief Put the data into alarm register of the RTC module.
 *
 * @param alarm Data value to be send into the alarm register.
 * @return None.
 */
void RTC_PutAlarmData(uint32_t alarm);

/*!
 * @brief Get the data from counter register of the RTC module.
 *
 * @return The data value from counter.
 */
uint32_t RTC_GetCounterData(void);

/*!
 * @brief Get the data from alarm register of the RTC module.
 *
 * @return The data value from alarm register.
 */
uint32_t RTC_GetAlarmData(void);

/*!
 * @brief Enabel interrupt of the RTC module.
 *
 * @param interrupts Interrupt code masks. See to @ref RTC_INT.
 * @param enable 'true' to enable the indicated interrupts, 'false' to disable the indicated interrupts.
 * @return None.
 */
void RTC_EnableInterrupts(uint32_t interrupts, bool enable);

/*!
 * @brief Get the interrupts status flags of the RTC module.
 *
 * @return Interrupt status flags. See to @ref RTC_INT.
 */
uint32_t RTC_GetInterruptStatus(void);

/*!
 * @brief Clear the interrupts status flags of the RTC module.
 *
 * @param interrupts The mask codes of the indicated interrupt flags to be cleared. See to @ref RTC_INT.
 * @return None.
 */
void RTC_ClearInterruptStatus(uint32_t interrupts);

/*!
 * @brief Read the current enabled interrupts the RTC module.
 *
 * @return The mask codes enabled interrupts. See to @ref RTC_INT.
 */
uint32_t RTC_GetEnabledInterrupts(void);

/*!
 * @brief Setup the initialization time of the RTC module.
 *
 * @param init Pointer to the initialization structure. See to @ref RTC_Init_Type.
 * @param time Pointer to the time structure. See to @ref RTC_Time_Type.
 * @return 'true' to set time succeess, 'false' to set time failed.
 */
bool RTC_SetTimeBlocking(RTC_Init_Type * init, RTC_Time_Type * time);

/*!
 * @brief Calculate and get current time.
 *
 * @param init Pointer to the initialization structure. See to @ref RTC_Init_Type.
 * @param time Pointer to the time structure. See to @ref RTC_Time_Type.
 * @return None.
 */
void RTC_CalcTimeBlocking(RTC_Init_Type * init, RTC_Time_Type * time);

/*!
 * @brief Set alarm time of the RTC module.
 *
 * @param time Pointer to the time structure. See to @ref RTC_Time_Type.
 * @return 'true' to set alarm time succeess, 'false' to set alarm time failed.
 */
bool RTC_SetAlarmBlocking(RTC_Time_Type * time);

/*!
 * @brief RTC interrupt handler.
 *
 * @param init Pointer to the RTC current time. See to @ref RTC_Init_Type.
 * @param time Pointer to the RTC interrupt done and interrupt count. See to @ref RTC_Time_Type.
 * @param interrupts Interrupt status flags. See to @ref RTC_INT.
 * @return None.
 */
void RTC_TimeHandler(RTC_Init_Type * init, RTC_Time_Type * time, uint32_t interrupts);

/*!
 *@}
 */

#endif /* __HAL_RTC_H__ */

