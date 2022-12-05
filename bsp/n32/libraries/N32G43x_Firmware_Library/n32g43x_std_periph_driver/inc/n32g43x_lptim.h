/** ----------------------------------------------------------------------------
 *         Nationz Technology Software Support  -  NATIONZ  -
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022, Nationz Corporation  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaiimer below.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the disclaimer below in the documentation and/or
 * other materials provided with the distribution.
 *
 * Nationz's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONZ "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * -----------------------------------------------------------------------------
 */
/** ****************************************************************************
 * @copyright      Nationz Co.,Ltd
 *                 Copyright (c) 2019 All Rights Reserved
 *******************************************************************************
 * @file     n32g43x_lptim.h
 * @author
 * @date
 * @version  v1.2.0
 * @brief
 ******************************************************************************/
#ifndef __n32g43x_LPTIM_H
#define __n32g43x_LPTIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "n32g43x.h"

/** @addtogroup n32g43x_StdPeriph_Driver
  * @{
  */

/** @addtogroup LPTIM
  * @{
  */

//#if defined (LPTIM)


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/
/** @defgroup LPTIM_ES_INIT LPTIM Exported Init structure
  * @{
  */

/**
  * @brief  LPTIM Init structure definition
  */
typedef struct
{
  uint32_t ClockSource;    /*!< Specifies the source of the clock used by the LPTIM instance.
                                This parameter can be a value of @ref LPTIM_EC_CLK_SOURCE.

                                This feature can be modified afterwards using unitary function @ref LPTIM_SetClockSource().*/

  uint32_t Prescaler;      /*!< Specifies the prescaler division ratio.
                                This parameter can be a value of @ref LPTIM_EC_PRESCALER.

                                This feature can be modified afterwards using using unitary function @ref LPTIM_SetPrescaler().*/

  uint32_t Waveform;       /*!< Specifies the waveform shape.
                                This parameter can be a value of @ref LPTIM_EC_OUTPUT_WAVEFORM.

                                This feature can be modified afterwards using unitary function @ref LPTIM_ConfigOutput().*/

  uint32_t Polarity;       /*!< Specifies waveform polarity.
                                This parameter can be a value of @ref LPTIM_EC_OUTPUT_POLARITY.

                                This feature can be modified afterwards using unitary function @ref LPTIM_ConfigOutput().*/
} LPTIM_InitType;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup LPTIM_Exported_Constants LPTIM Exported Constants
  * @{
  */

/** @defgroup LPTIM_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LPTIM_ReadReg function
  * @{
  */
#define LPTIM_INTSTS_CMPM_FLAG                    LPTIM_INTSTS_CMPM      /*!< Compare match */
#define LPTIM_INTSTS_ARRM_FLAG                    LPTIM_INTSTS_ARRM     /*!< Autoreload match */
#define LPTIM_INTSTS_EXTRIG_FLAG                  LPTIM_INTSTS_EXTRIG    /*!< External trigger edge event */
#define LPTIM_INTSTS_CMPUPD_FLAG                  LPTIM_INTSTS_CMPUPD     /*!< Compare register update OK */
#define LPTIM_INTSTS_ARRUPD_FLAG                  LPTIM_INTSTS_ARRUPD    /*!< Autoreload register update OK */
#define LPTIM_INTSTS_UP_FLAG                      LPTIM_INTSTS_UP         /*!< Counter direction change down to up */
#define LPTIM_INTSTS_DOWN_FLAG                    LPTIM_INTSTS_DOWN       /*!< Counter direction change up to down */
/**
  * @}
  */

/** @defgroup LPTIM_EC_IT IT Defines
  * @brief    IT defines which can be used with LPTIM_ReadReg and  LPTIM_WriteReg functions
  * @{
  */
#define LPTIM_INTEN_CMPMIE_ENABLE                   LPTIM_INTEN_CMPMIE       /*!< Compare match Interrupt Enable */
#define LPTIM_INTEN_ARRMIE_ENABLE                   LPTIM_INTEN_ARRMIE      /*!< Autoreload match Interrupt Enable */
#define LPTIM_INTEN_EXTRIGIE_ENABLE                 LPTIM_INTEN_EXTRIGIE     /*!< External trigger valid edge Interrupt Enable */
#define LPTIM_INTEN_CMPUPDIE_ENABLE                 LPTIM_INTEN_CMPUPDIE      /*!< Compare register update OK Interrupt Enable */
#define LPTIM_INTEN_ARRUPDIE_ENABLE                 LPTIM_INTEN_ARRUPDIE     /*!< Autoreload register update OK Interrupt Enable */
#define LPTIM_INTEN_UPIE_ENABLE                     LPTIM_INTEN_UPIE          /*!< Direction change to UP Interrupt Enable */
#define LPTIM_INTEN_DOWNIE_ENABLE                   LPTIM_INTEN_DOWNIE        /*!< Direction change to down Interrupt Enable */
/**
  * @}
  */

/** @defgroup LPTIM_EC_OPERATING_MODE Operating Mode
  * @{
  */
#define LPTIM_OPERATING_MODE_CONTINUOUS    LPTIM_CTRL_TSTCM  /*!<LP Timer starts in continuous mode*/
#define LPTIM_OPERATING_MODE_ONESHOT       LPTIM_CTRL_SNGMST /*!<LP Tilmer starts in single mode*/
/**
  * @}
  */

/** @defgroup LPTIM_EC_UPDATE_MODE Update Mode
  * @{
  */
#define LPTIM_UPDATE_MODE_IMMEDIATE        0x00000000U        /*!<Preload is disabled: registers are updated after each APB bus write access*/
#define LPTIM_UPDATE_MODE_ENDOFPERIOD      LPTIM_CFG_RELOAD    /*!<preload is enabled: registers are updated at the end of the current LPTIM period*/
/**
  * @}
  */

/** @defgroup LPTIM_EC_COUNTER_MODE Counter Mode
  * @{
  */
#define LPTIM_COUNTER_MODE_INTERNAL        0x00000000U          /*!<The counter is incremented following each internal clock pulse*/
#define LPTIM_COUNTER_MODE_EXTERNAL        LPTIM_CFG_CNTMEN     /*!<The counter is incremented following each valid clock pulse on the LPTIM external Input1*/
/**
  * @}
  */

/** @defgroup LPTIM_EC_OUTPUT_WAVEFORM Output Waveform Type
  * @{
  */
#define LPTIM_OUTPUT_WAVEFORM_PWM          0x00000000U     /*!<LPTIM  generates either a PWM waveform or a One pulse waveform depending on chosen operating mode CONTINOUS or SINGLE*/
#define LPTIM_OUTPUT_WAVEFORM_SETONCE      LPTIM_CFG_WAVE  /*!<LPTIM  generates a Set Once waveform*/
/**
  * @}
  */

/** @defgroup LPTIM_EC_OUTPUT_POLARITY Output Polarity
  * @{
  */
#define LPTIM_OUTPUT_POLARITY_REGULAR      0x00000000U             /*!<The LPTIM output reflects the compare results between LPTIMx_ARR and LPTIMx_CMP registers*/
#define LPTIM_OUTPUT_POLARITY_INVERSE      LPTIM_CFG_WAVEPOL         /*!<The LPTIM output reflects the inverse of the compare results between LPTIMx_ARR and LPTIMx_CMP registers*/
/**
  * @}
  */

/** @defgroup LPTIM_EC_PRESCALER Prescaler Value
  * @{
  */
#define LPTIM_PRESCALER_DIV1               0x00000000U                               /*!<Prescaler division factor is set to 1*/
#define LPTIM_PRESCALER_DIV2               LPTIM_CFG_CLKPRE_0                        /*!<Prescaler division factor is set to 2*/
#define LPTIM_PRESCALER_DIV4               LPTIM_CFG_CLKPRE_1                        /*!<Prescaler division factor is set to 4*/
#define LPTIM_PRESCALER_DIV8               (LPTIM_CFG_CLKPRE_1 | LPTIM_CFG_CLKPRE_0) /*!<Prescaler division factor is set to 8*/
#define LPTIM_PRESCALER_DIV16              LPTIM_CFG_CLKPRE_2                        /*!<Prescaler division factor is set to 16*/
#define LPTIM_PRESCALER_DIV32              (LPTIM_CFG_CLKPRE_2 | LPTIM_CFG_CLKPRE_0) /*!<Prescaler division factor is set to 32*/
#define LPTIM_PRESCALER_DIV64              (LPTIM_CFG_CLKPRE_2 | LPTIM_CFG_CLKPRE_1) /*!<Prescaler division factor is set to 64*/
#define LPTIM_PRESCALER_DIV128             LPTIM_CFG_CLKPRE                          /*!<Prescaler division factor is set to 128*/
/**
  * @}
  */

/** @defgroup LPTIM_EC_TRIG_SOURCE Trigger Source
  * @{
  */
#define LPTIM_TRIG_SOURCE_GPIO             0x00000000U                               /*!<External input trigger is connected to TIMx_ETR input*/
#define LPTIM_TRIG_SOURCE_RTCALARMA        LPTIM_CFG_TRGSEL_0                          /*!<External input trigger is connected to RTC Alarm A*/
#define LPTIM_TRIG_SOURCE_RTCALARMB        LPTIM_CFG_TRGSEL_1                          /*!<External input trigger is connected to RTC Alarm B*/
#define LPTIM_TRIG_SOURCE_RTCTAMP1         (LPTIM_CFG_TRGSEL_1 | LPTIM_CFG_TRGSEL_0)     /*!<External input trigger is connected to RTC Tamper 1*/
#define LPTIM_TRIG_SOURCE_RTCTAMP2         LPTIM_CFG_TRGSEL_2                          /*!<External input trigger is connected to RTC Tamper 2*/
#define LPTIM_TRIG_SOURCE_RTCTAMP3         (LPTIM_CFG_TRGSEL_2 | LPTIM_CFG_TRGSEL_0)     /*!<External input trigger is connected to RTC Tamper 3*/
#define LPTIM_TRIG_SOURCE_COMP1            (LPTIM_CFG_TRGSEL_2 | LPTIM_CFG_TRGSEL_1)     /*!<External input trigger is connected to COMP1 output*/
#define LPTIM_TRIG_SOURCE_COMP2            LPTIM_CFG_TRGSEL                            /*!<External input trigger is connected to COMP2 output*/
/**
  * @}
  */

/** @defgroup LPTIM_EC_TRIG_FILTER Trigger Filter
  * @{
  */
#define LPTIM_TRIG_FILTER_NONE             0x00000000U           /*!<Any trigger active level change is considered as a valid trigger*/
#define LPTIM_TRIG_FILTER_2                LPTIM_CFG_TRIGFLT_0 /*!<Trigger active level change must be stable for at least 2 clock periods before it is considered as valid trigger*/
#define LPTIM_TRIG_FILTER_4                LPTIM_CFG_TRIGFLT_1 /*!<Trigger active level change must be stable for at least 4 clock periods before it is considered as valid trigger*/
#define LPTIM_TRIG_FILTER_8                LPTIM_CFG_TRIGFLT   /*!<Trigger active level change must be stable for at least 8 clock periods before it is considered as valid trigger*/
/**
  * @}
  */

/** @defgroup LPTIM_EC_TRIG_POLARITY Trigger Polarity
  * @{
  */
#define LPTIM_TRIG_POLARITY_RISING         LPTIM_CFG_TRGEN_0 /*!<LPTIM counter starts when a rising edge is detected*/
#define LPTIM_TRIG_POLARITY_FALLING        LPTIM_CFG_TRGEN_1 /*!<LPTIM counter starts when a falling edge is detected*/
#define LPTIM_TRIG_POLARITY_RISING_FALLING LPTIM_CFG_TRGEN   /*!<LPTIM counter starts when a rising or a falling edge is detected*/
/**
  * @}
  */

/** @defgroup LPTIM_EC_CLK_SOURCE Clock Source
  * @{
  */
#define LPTIM_CLK_SOURCE_INTERNAL          0x00000000U    /*!<LPTIM is clocked by internal clock source (APB clock or any of the embedded oscillators)*/
#define LPTIM_CLK_SOURCE_EXTERNAL          LPTIM_CFG_CLKSEL /*!<LPTIM is clocked by an external clock source through the LPTIM external Input1*/
/**
  * @}
  */

/** @defgroup LPTIM_EC_CLK_FILTER Clock Filter
  * @{
  */
#define LPTIM_CLK_FILTER_NONE              0x00000000U           /*!<Any external clock signal level change is considered as a valid transition*/
#define LPTIM_CLK_FILTER_2                 LPTIM_CFG_CLKFLT_0 /*!<External clock signal level change must be stable for at least 2 clock periods before it is considered as valid transition*/
#define LPTIM_CLK_FILTER_4                 LPTIM_CFG_CLKFLT_1 /*!<External clock signal level change must be stable for at least 4 clock periods before it is considered as valid transition*/
#define LPTIM_CLK_FILTER_8                 LPTIM_CFG_CLKFLT   /*!<External clock signal level change must be stable for at least 8 clock periods before it is considered as valid transition*/
/**
  * @}
  */

/** @defgroup LPTIM_EC_CLK_POLARITY Clock Polarity
  * @{
  */
#define LPTIM_CLK_POLARITY_RISING          0x00000000U        /*!< The rising edge is the active edge used for counting*/
#define LPTIM_CLK_POLARITY_FALLING         LPTIM_CFG_CLKPOL_0   /*!< The falling edge is the active edge used for counting*/
#define LPTIM_CLK_POLARITY_RISING_FALLING  LPTIM_CFG_CLKPOL_1   /*!< Both edges are active edges*/
/**
  * @}
  */

/** @defgroup LPTIM_EC_ENCODER_MODE Encoder Mode
  * @{
  */
#define LPTIM_ENCODER_MODE_RISING          0x00000000U        /*!< The rising edge is the active edge used for counting*/
#define LPTIM_ENCODER_MODE_FALLING         LPTIM_CFG_CLKPOL_0   /*!< The falling edge is the active edge used for counting*/
#define LPTIM_ENCODER_MODE_RISING_FALLING  LPTIM_CFG_CLKPOL_1   /*!< Both edges are active edges*/
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup LPTIM_Exported_Macros LPTIM Exported Macros
  * @{
  */

/** @defgroup LPTIM_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in LPTIM register
  * @param  __INSTANCE__ LPTIM Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LPTIM_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG((__INSTANCE__)->(__REG__), (__VALUE__))

/**
  * @brief  Read a value in LPTIM register
  * @param  __INSTANCE__ LPTIM Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LPTIM_ReadReg(__INSTANCE__, __REG__) READ_REG((__INSTANCE__)->(__REG__))
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup LPTIM_Exported_Functions LPTIM Exported Functions
  * @{
  */

/** @defgroup LPTIM_EF_Init Initialisation and deinitialisation functions
  * @{
  */

void LPTIM_DeInit(LPTIM_Module *LPTIMx);
void LPTIM_StructInit(LPTIM_InitType *LPTIM_InitStruct);
ErrorStatus LPTIM_Init(LPTIM_Module *LPTIMx, LPTIM_InitType *LPTIM_InitStruct);
void LPTIM_Disable(LPTIM_Module *LPTIMx);



void LPTIM_Enable(LPTIM_Module *LPTIMx);
uint32_t LPTIM_IsEnabled(LPTIM_Module *LPTIMx);
void LPTIM_StartCounter(LPTIM_Module *LPTIMx, uint32_t OperatingMode);
void LPTIM_SetUpdateMode(LPTIM_Module *LPTIMx, uint32_t UpdateMode);
uint32_t LPTIM_GetUpdateMode(LPTIM_Module *LPTIMx);
void LPTIM_SetAutoReload(LPTIM_Module *LPTIMx, uint32_t AutoReload);
uint32_t LPTIM_GetAutoReload(LPTIM_Module *LPTIMx);
void LPTIM_SetCompare(LPTIM_Module *LPTIMx, uint32_t CompareValue);
uint32_t LPTIM_GetCompare(LPTIM_Module *LPTIMx);
uint32_t LPTIM_GetCounter(LPTIM_Module *LPTIMx);
void LPTIM_SetCounterMode(LPTIM_Module *LPTIMx, uint32_t CounterMode);
uint32_t LPTIM_GetCounterMode(LPTIM_Module *LPTIMx);
void LPTIM_ConfigOutput(LPTIM_Module *LPTIMx, uint32_t Waveform, uint32_t Polarity);
void LPTIM_SetWaveform(LPTIM_Module *LPTIMx, uint32_t Waveform);
uint32_t LPTIM_GetWaveform(LPTIM_Module *LPTIMx);
void LPTIM_SetPolarity(LPTIM_Module *LPTIMx, uint32_t Polarity);
uint32_t LPTIM_GetPolarity(LPTIM_Module *LPTIMx);
void LPTIM_SetPrescaler(LPTIM_Module *LPTIMx, uint32_t Prescaler);
uint32_t LPTIM_GetPrescaler(LPTIM_Module *LPTIMx);
void LPTIM_EnableTimeout(LPTIM_Module *LPTIMx);
void LPTIM_DisableTimeout(LPTIM_Module *LPTIMx);
uint32_t LPTIM_IsEnabledTimeout(LPTIM_Module *LPTIMx);
void LPTIM_TrigSw(LPTIM_Module *LPTIMx);
void LPTIM_ConfigTrigger(LPTIM_Module *LPTIMx, uint32_t Source, uint32_t Filter, uint32_t Polarity);
uint32_t LPTIM_GetTriggerSource(LPTIM_Module *LPTIMx);
uint32_t LPTIM_GetTriggerFilter(LPTIM_Module *LPTIMx);
uint32_t LPTIM_GetTriggerPolarity(LPTIM_Module *LPTIMx);
void LPTIM_SetClockSource(LPTIM_Module *LPTIMx, uint32_t ClockSource);
uint32_t LPTIM_GetClockSource(LPTIM_Module *LPTIMx);
void LPTIM_ConfigClock(LPTIM_Module *LPTIMx, uint32_t ClockFilter, uint32_t ClockPolarity);
uint32_t LPTIM_GetClockPolarity(LPTIM_Module *LPTIMx);
uint32_t LPTIM_GetClockFilter(LPTIM_Module *LPTIMx);
void LPTIM_SetEncoderMode(LPTIM_Module *LPTIMx, uint32_t EncoderMode);
uint32_t LPTIM_GetEncoderMode(LPTIM_Module *LPTIMx);
void LPTIM_EnableEncoderMode(LPTIM_Module *LPTIMx);
void LPTIM_DisableEncoderMode(LPTIM_Module *LPTIMx);
uint32_t LPTIM_IsEnabledEncoderMode(LPTIM_Module *LPTIMx);
void LPTIM_ClearFLAG_CMPM(LPTIM_Module *LPTIMx);
uint32_t LPTIM_IsActiveFlag_CMPM(LPTIM_Module *LPTIMx);
void LPTIM_ClearFLAG_ARRM(LPTIM_Module *LPTIMx);
uint32_t LPTIM_IsActiveFlag_ARRM(LPTIM_Module *LPTIMx);
void LPTIM_ClearFlag_EXTTRIG(LPTIM_Module *LPTIMx);
uint32_t LPTIM_IsActiveFlag_EXTTRIG(LPTIM_Module *LPTIMx);
void LPTIM_ClearFlag_CMPOK(LPTIM_Module *LPTIMx);
uint32_t LPTIM_IsActiveFlag_CMPOK(LPTIM_Module *LPTIMx);
void LPTIM_ClearFlag_ARROK(LPTIM_Module *LPTIMx);
uint32_t LPTIM_IsActiveFlag_ARROK(LPTIM_Module *LPTIMx);
void LPTIM_ClearFlag_UP(LPTIM_Module *LPTIMx);
uint32_t LPTIM_IsActiveFlag_UP(LPTIM_Module *LPTIMx);
void LPTIM_ClearFlag_DOWN(LPTIM_Module *LPTIMx);
uint32_t LPTIM_IsActiveFlag_DOWN(LPTIM_Module *LPTIMx);
void LPTIM_EnableIT_CMPM(LPTIM_Module *LPTIMx);
void LPTIM_DisableIT_CMPM(LPTIM_Module *LPTIMx);
uint32_t LPTIM_IsEnabledIT_CMPM(LPTIM_Module *LPTIMx);
void LPTIM_EnableIT_ARRM(LPTIM_Module *LPTIMx);
void LPTIM_DisableIT_ARRM(LPTIM_Module *LPTIMx);
uint32_t LPTIM_IsEnabledIT_ARRM(LPTIM_Module *LPTIMx);
void LPTIM_EnableIT_EXTTRIG(LPTIM_Module *LPTIMx);
void LPTIM_DisableIT_EXTTRIG(LPTIM_Module *LPTIMx);
uint32_t LPTIM_IsEnabledIT_EXTTRIG(LPTIM_Module *LPTIMx);
void LPTIM_EnableIT_CMPOK(LPTIM_Module *LPTIMx);
void LPTIM_DisableIT_CMPOK(LPTIM_Module *LPTIMx);
uint32_t LPTIM_IsEnabledIT_CMPOK(LPTIM_Module *LPTIMx);
void LPTIM_EnableIT_ARROK(LPTIM_Module *LPTIMx);
void LPTIM_DisableIT_ARROK(LPTIM_Module *LPTIMx);
uint32_t LPTIM_IsEnabledIT_ARROK(LPTIM_Module *LPTIMx);
void LPTIM_EnableIT_UP(LPTIM_Module *LPTIMx);
void LPTIM_DisableIT_UP(LPTIM_Module *LPTIMx);
uint32_t LPTIM_IsEnabledIT_UP(LPTIM_Module *LPTIMx);
void LPTIM_EnableIT_DOWN(LPTIM_Module *LPTIMx);
void LPTIM_DisableIT_DOWN(LPTIM_Module *LPTIMx);
uint32_t LPTIM_IsEnabledIT_DOWN(LPTIM_Module *LPTIMx);
void LPTIM_EnableNoEncoderMode(LPTIM_Module *LPTIMx);
/**
  * @}
  */

/**
  * @}
  */

//#endif /* LPTIM */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __n32g43x_LPTIM_H */

/******************* (C) COPYRIGHT 2019 NATIONZ *****END OF FILE****/
