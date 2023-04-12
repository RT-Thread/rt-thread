/*!
 * @file        apm32s10x_tmr.h
 *
 * @brief       This file contains all the functions prototypes for the TMR firmware library.
 *
 * @version     V1.0.1
 *
 * @date        2022-12-31
 *
 * @attention
 *
 *  Copyright (C) 2022-2023 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __APM32S10X_TMR_H
#define __APM32S10X_TMR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32s10x.h"

/** @addtogroup APM32S10x_StdPeriphDriver
  @{
*/

/** @addtogroup TMR_Driver  TMR Driver
  @{
*/

/** @defgroup TMR_Enumerations Enumerations
  @{
*/

/**
 * @brief TMR Counter Mode
 */
typedef enum
{
    TMR_COUNTER_MODE_UP             = 0x0000,
    TMR_COUNTER_MODE_DOWN           = 0x0010,
    TMR_COUNTER_MODE_CENTERALIGNED1 = 0x0020,
    TMR_COUNTER_MODE_CENTERALIGNED2 = 0x0040,
    TMR_COUNTER_MODE_CENTERALIGNED3 = 0x0060
} TMR_COUNTER_MODE_T;

/**
 * @brief TMR Clock division
 */
typedef enum
{
    TMR_CLOCK_DIV_1,
    TMR_CLOCK_DIV_2,
    TMR_CLOCK_DIV_4
} TMR_CLOCK_DIV_T;

/**
 * @brief TMR Output Compare and PWM modes
 */
typedef enum
{
    TMR_OC_MODE_TMRING     = 0x00,
    TMR_OC_MODE_ACTIVE     = 0x01,
    TMR_OC_MODE_INACTIVE   = 0x02,
    TMR_OC_MODE_TOGGEL     = 0x03,
    TMR_OC_MODE_LOWLEVEL   = 0x04,
    TMR_OC_MODE_HIGHLEVEL  = 0x05,
    TMR_OC_MODE_PWM1       = 0x06,
    TMR_OC_MODE_PWM2       = 0x07
} TMR_OC_MODE_T;

/**
 * @brief TMR Output Compare state
 */
typedef enum
{
    TMR_OC_STATE_DISABLE,
    TMR_OC_STATE_ENABLE
} TMR_OC_STATE_T;

/**
 * @brief TMR Output Compare N state
 */
typedef enum
{
    TMR_OC_NSTATE_DISABLE,
    TMR_OC_NSTATE_ENABLE
} TMR_OC_NSTATE_T;

/**
 * @brief TMR Output Compare Polarity
 */
typedef enum
{
    TMR_OC_POLARITY_HIGH,
    TMR_OC_POLARITY_LOW
} TMR_OC_POLARITY_T;

/**
 * @brief TMR Output Compare N Polarity
 */
typedef enum
{
    TMR_OC_NPOLARITY_HIGH,
    TMR_OC_NPOLARITY_LOW
} TMR_OC_NPOLARITY_T;

/**
 * @brief TMR Output Compare Idle State
 */
typedef enum
{
    TMR_OC_IDLE_STATE_RESET,
    TMR_OC_IDLE_STATE_SET
} TMR_OC_IDLE_STATE_T;

/**
 * @brief TMR Output Compare N Idle State
 */
typedef enum
{
    TMR_OC_NIDLE_STATE_RESET,
    TMR_OC_NIDLE_STATE_SET
} TMR_OC_NIDLE_STATE_T;

/**
 * @brief TMR Input Capture Init structure definition
 */
typedef enum
{
    TMR_CHANNEL_1 = 0x0000,
    TMR_CHANNEL_2 = 0x0004,
    TMR_CHANNEL_3 = 0x0008,
    TMR_CHANNEL_4 = 0x000C
} TMR_CHANNEL_T;

/**
 * @brief TMR Input Capture Polarity
 */
typedef enum
{
    TMR_IC_POLARITY_RISING   = 0x00,
    TMR_IC_POLARITY_FALLING  = 0x02,
    TMR_IC_POLARITY_BOTHEDGE = 0x0A
} TMR_IC_POLARITY_T;

/**
 * @brief TMR Input Capture Selection
 */
typedef enum
{
    TMR_IC_SELECTION_DIRECT_TI   = 0x01,
    TMR_IC_SELECTION_INDIRECT_TI = 0x02,
    TMR_IC_SELECTION_TRC         = 0x03
} TMR_IC_SELECTION_T;

/**
 * @brief TMR Input Capture Prescaler
 */
typedef enum
{
    TMR_IC_PSC_1,
    TMR_IC_PSC_2,
    TMR_IC_PSC_4,
    TMR_IC_PSC_8
} TMR_IC_PSC_T;

/**
 * @brief TMR Specifies the Off-State selection used in Run mode
 */
typedef enum
{
    TMR_RMOS_STATE_DISABLE,
    TMR_RMOS_STATE_ENABLE
} TMR_RMOS_STATE_T;

/**
 * @brief TMR Closed state configuration in idle mode
 */
typedef enum
{
    TMR_IMOS_STATE_DISABLE,
    TMR_IMOS_STATE_ENABLE
} TMR_IMOS_STATE_T;

/**
 * @brief TMR Protect mode configuration values
 */
typedef enum
{
    TMR_LOCK_LEVEL_OFF,
    TMR_LOCK_LEVEL_1,
    TMR_LOCK_LEVEL_2,
    TMR_LOCK_LEVEL_3
} TMR_LOCK_LEVEL_T;

/**
 * @brief TMR BRK state
 */
typedef enum
{
    TMR_BRK_STATE_DISABLE,
    TMR_BRK_STATE_ENABLE
} TMR_BRK_STATE_T;

/**
 * @brief TMR Specifies the Break Input pin polarity.
 */
typedef enum
{
    TMR_BRK_POLARITY_LOW,
    TMR_BRK_POLARITY_HIGH
} TMR_BRK_POLARITY_T;

/**
 * @brief TMR Specifies the Break Input pin polarity.
 */
typedef enum
{
    TMR_AUTOMATIC_OUTPUT_DISABLE,
    TMR_AUTOMATIC_OUTPUT_ENABLE
} TMR_AUTOMATIC_OUTPUT_T;

/**
 * @brief    TMR_interrupt_sources
 */
typedef enum
{
    TMR_INT_UPDATE = 0x0001,
    TMR_INT_CC1    = 0x0002,
    TMR_INT_CC2    = 0x0004,
    TMR_INT_CC3    = 0x0008,
    TMR_INT_CC4    = 0x0010,
    TMR_INT_COM    = 0x0020,
    TMR_INT_TRG    = 0x0040,
    TMR_INT_BRK    = 0x0080
} TMR_INT_T;

/**
 * @brief    TMR event sources
 */
typedef enum
{
    TMR_EVENT_UPDATE = 0x001,
    TMR_EVENT_CC1    = 0x002,
    TMR_EVENT_CC2    = 0x004,
    TMR_EVENT_CC3    = 0x008,
    TMR_EVENT_CC4    = 0x010,
    TMR_EVENT_COM    = 0x020,
    TMR_EVENT_TRG    = 0x040,
    TMR_EVENT_BRK    = 0x080
} TMR_EVENT_T;

/**
 * @brief    TMR DMA Base Address
 */
typedef enum
{
    TMR_DMA_BASE_CTRL1   = 0x0000,
    TMR_DMA_BASE_CTRL2   = 0x0001,
    TMR_DMA_BASE_SMCTRL  = 0x0002,
    TMR_DMA_BASE_DIEN    = 0x0003,
    TMR_DMA_BASE_STS     = 0x0004,
    TMR_DMA_BASE_CEG     = 0x0005,
    TMR_DMA_BASE_CCM1    = 0x0006,
    TMR_DMA_BASE_CCM2    = 0x0007,
    TMR_DMA_BASE_CCEN    = 0x0008,
    TMR_DMA_BASE_CNT     = 0x0009,
    TMR_DMA_BASE_PSC     = 0x000A,
    TMR_DMA_BASE_AUTORLD = 0x000B,
    TMR_DMA_BASE_REPCNT  = 0x000C,
    TMR_DMA_BASE_CC1     = 0x000D,
    TMR_DMA_BASE_CC2     = 0x000E,
    TMR_DMA_BASE_CC3     = 0x000F,
    TMR_DMA_BASE_CC4     = 0x0010,
    TMR_DMA_BASE_BDT     = 0x0011,
    TMR_DMA_BASE_DCTRL   = 0x0012
} TMR_DMA_BASE_T;

/**
 * @brief    TMR DMA Burst Length
 */
typedef enum
{
    TMR_DMA_BURSTLENGTH_1TRANSFER   = 0x0000,
    TMR_DMA_BURSTLENGTH_2TRANSFERS  = 0x0100,
    TMR_DMA_BURSTLENGTH_3TRANSFERS  = 0x0200,
    TMR_DMA_BURSTLENGTH_4TRANSFERS  = 0x0300,
    TMR_DMA_BURSTLENGTH_5TRANSFERS  = 0x0400,
    TMR_DMA_BURSTLENGTH_6TRANSFERS  = 0x0500,
    TMR_DMA_BURSTLENGTH_7TRANSFERS  = 0x0600,
    TMR_DMA_BURSTLENGTH_8TRANSFERS  = 0x0700,
    TMR_DMA_BURSTLENGTH_9TRANSFERS  = 0x0800,
    TMR_DMA_BURSTLENGTH_10TRANSFERS = 0x0900,
    TMR_DMA_BURSTLENGTH_11TRANSFERS = 0x0A00,
    TMR_DMA_BURSTLENGTH_12TRANSFERS = 0x0B00,
    TMR_DMA_BURSTLENGTH_13TRANSFERS = 0x0C00,
    TMR_DMA_BURSTLENGTH_14TRANSFERS = 0x0D00,
    TMR_DMA_BURSTLENGTH_15TRANSFERS = 0x0E00,
    TMR_DMA_BURSTLENGTH_16TRANSFERS = 0x0F00,
    TMR_DMA_BURSTLENGTH_17TRANSFERS = 0x1000,
    TMR_DMA_BURSTLENGTH_18TRANSFERS = 0x1100,
} TMR_DMA_BURSTLENGTH_T;

/**
 * @brief    TMR DMA Soueces
 */
typedef enum
{
    TMR_DMA_SOURCE_UPDATE    = 0x0100,
    TMR_DMA_SOURCE_CC1       = 0x0200,
    TMR_DMA_SOURCE_CC2       = 0x0400,
    TMR_DMA_SOURCE_CC3       = 0x0800,
    TMR_DMA_SOURCE_CC4       = 0x1000,
    TMR_DMA_SOURCE_COM       = 0x2000,
    TMR_DMA_SOURCE_TRG       = 0x4000
} TMR_DMA_SOURCE_T;

/**
 * @brief    TMR Internal Trigger Selection
 */
typedef enum
{
    TMR_TRIGGER_SOURCE_ITR0     = 0x00,
    TMR_TRIGGER_SOURCE_ITR1     = 0x01,
    TMR_TRIGGER_SOURCE_ITR2     = 0x02,
    TMR_TRIGGER_SOURCE_ITR3     = 0x03,
    TMR_TRIGGER_SOURCE_TI1F_ED  = 0x04,
    TMR_TRIGGER_SOURCE_TI1FP1   = 0x05,
    TMR_TRIGGER_SOURCE_TI2FP2   = 0x06,
    TMR_TRIGGER_SOURCE_ETRF     = 0x07
} TMR_TRIGGER_SOURCE_T;

/**
 * @brief    TMR  The external Trigger Prescaler.
 */
typedef enum
{
    TMR_EXTTRG_PSC_OFF   = 0x00,
    TMR_EXTTRG_PSC_DIV2  = 0x01,
    TMR_EXTTRG_PSC_DIV4  = 0x02,
    TMR_EXTTRG_PSC_DIV8  = 0x03
} TMR_EXTTRG_PSC_T;

/**
 * @brief    TMR External Trigger Polarity
 */
typedef enum
{
    TMR_EXTTGR_POL_NONINVERTED,
    TMR_EXTTRG_POL_INVERTED
} TMR_EXTTRG_POL_T;

/**
 * @brief    TMR Prescaler Reload Mode
 */
typedef enum
{
    TMR_PSC_RELOAD_UPDATE,
    TMR_PSC_RELOAD_IMMEDIATE
} TMR_PSC_RELOAD_T;

/**
 * @brief    TMR Encoder Mode
 */
typedef enum
{
    TMR_ENCODER_MODE_TI1      = 0x01,
    TMR_ENCODER_MODE_TI2      = 0x02,
    TMR_ENCODER_MODE_TI12     = 0x03
} TMR_ENCODER_MODE_T;

/**
 * @brief    TMR Forced Action
 */
typedef enum
{
    TMR_FORCED_ACTION_INACTIVE = 0x04,
    TMR_FORCED_ACTION_ACTIVE   = 0x05
} TMR_FORCED_ACTION_T;

/**
 * @brief    TMR Output Compare Preload State
 */
typedef enum
{
    TMR_OC_PRELOAD_DISABLE,
    TMR_OC_PRELOAD_ENABLE
} TMR_OC_PRELOAD_T;

/**
 * @brief    TMR Output Compare Preload State
 */
typedef enum
{
    TMR_OC_FAST_DISABLE,
    TMR_OC_FAST_ENABLE
} TMR_OC_FAST_T;

/**
 * @brief    TMR Output Compare Preload State
 */
typedef enum
{
    TMR_OC_CLEAR_DISABLE,
    TMR_OC_CLEAR_ENABLE
} TMR_OC_CLEAR_T;

/**
 * @brief    TMR UpdateSource
 */
typedef enum
{
    TMR_UPDATE_SOURCE_GLOBAL,
    TMR_UPDATE_SOURCE_REGULAR,
} TMR_UPDATE_SOURCE_T;

/**
 * @brief    TMR Single Pulse Mode
 */
typedef enum
{
    TMR_SPM_REPETITIVE,
    TMR_SPM_SINGLE,
} TMR_SPM_T;

/**
 * @brief    TMR Trigger Output Source
 */
typedef enum
{
    TMR_TRGO_SOURCE_RESET,
    TMR_TRGO_SOURCE_ENABLE,
    TMR_TRGO_SOURCE_UPDATE,
    TMR_TRGO_SOURCE_OC1,
    TMR_TRGO_SOURCE_OC1REF,
    TMR_TRGO_SOURCE_OC2REF,
    TMR_TRGO_SOURCE_OC3REF,
    TMR_TRGO_SOURCE_OC4REF
} TMR_TRGO_SOURCE_T;

/**
 * @brief    TMR Slave Mode
 */
typedef enum
{
    TMR_SLAVE_MODE_RESET     = 0x04,
    TMR_SLAVE_MODE_GATED     = 0x05,
    TMR_SLAVE_MODE_TRIGGER   = 0x06,
    TMR_SLAVE_MODE_EXTERNAL1 = 0x07
} TMR_SLAVE_MODE_T;

/**
 * @brief    TMR Flag
 */
typedef enum
{
    TMR_FLAG_UPDATE  = 0x0001,
    TMR_FLAG_CC1     = 0x0002,
    TMR_FLAG_CC2     = 0x0004,
    TMR_FLAG_CC3     = 0x0008,
    TMR_FLAG_CC4     = 0x0010,
    TMR_FLAG_COM     = 0x0020,
    TMR_FLAG_TRG     = 0x0040,
    TMR_FLAG_BRK     = 0x0080,
    TMR_FLAG_CC1RC   = 0x0200,
    TMR_FLAG_CC2RC   = 0x0400,
    TMR_FLAG_CC3RC   = 0x0800,
    TMR_FLAG_CC4RC   = 0x1000
} TMR_FLAG_T;

/**@} end of group TMR_Enumerations */

/** @defgroup TMR_Structures Structures
  @{
*/

/**
 * @brief    TMR Base Configure structure definition
 */
typedef struct
{
    TMR_COUNTER_MODE_T     countMode;
    TMR_CLOCK_DIV_T        clockDivision;
    uint16_t               period;            /*!< This must between 0x0000 and 0xFFFF */
    uint16_t               division;          /*!< This must between 0x0000 and 0xFFFF */
    uint8_t                repetitionCounter; /*!< This must between 0x00 and 0xFF, only for TMR1. */
} TMR_BaseConfig_T; ;

/**
 * @brief    TMR Output Compare Configure structure definition
 */
typedef struct
{
    TMR_OC_MODE_T          mode;
    TMR_OC_STATE_T         outputState;
    TMR_OC_NSTATE_T        outputNState;
    TMR_OC_POLARITY_T      polarity;
    TMR_OC_NPOLARITY_T     nPolarity;
    TMR_OC_IDLE_STATE_T    idleState;
    TMR_OC_NIDLE_STATE_T   nIdleState;
    uint16_t               pulse;     /*!< This must between 0x0000 and 0xFFFF */
} TMR_OCConfig_T;

/**
 * @brief    TMR BDT structure definition
 */
typedef struct
{
    TMR_RMOS_STATE_T       RMOS;
    TMR_IMOS_STATE_T       IMOS;
    TMR_LOCK_LEVEL_T       lockLevel;
    uint16_t               deadTime;
    TMR_BRK_STATE_T        BRKState;
    TMR_BRK_POLARITY_T     BRKPolarity;
    TMR_AUTOMATIC_OUTPUT_T automaticOutput;
} TMR_BDTConfig_T;

/**
 * @brief    TMR Input Capture Configure structure definition
 */
typedef struct
{
    TMR_CHANNEL_T          channel;
    TMR_IC_POLARITY_T      polarity;
    TMR_IC_SELECTION_T     selection;
    TMR_IC_PSC_T           prescaler;
    uint16_t               filter;    /*!< This must between 0x00 and 0x0F */
} TMR_ICConfig_T;

/**@} end of group TMR_Structures */

/** @defgroup  TMR_Functions Functions
  @{
*/

/* Reset and Configuration */
void TMR_Reset(TMR_T* tmr);
void TMR_ConfigTimeBase(TMR_T* tmr, TMR_BaseConfig_T* baseConfig);
void TMR_ConfigOC1(TMR_T* tmr, TMR_OCConfig_T* OCConfig);
void TMR_ConfigOC2(TMR_T* tmr, TMR_OCConfig_T* OCConfig);
void TMR_ConfigOC3(TMR_T* tmr, TMR_OCConfig_T* OCConfig);
void TMR_ConfigOC4(TMR_T* tmr, TMR_OCConfig_T* OCConfig);
void TMR_ConfigIC(TMR_T* tmr, TMR_ICConfig_T* ICConfig);
void TMR_ConfigBDT(TMR_T* tmr, TMR_BDTConfig_T* BDTConfig);
void TMR_ConfigTimeBaseStructInit(TMR_BaseConfig_T* baseConfig);
void TMR_ConfigOCStructInit(TMR_OCConfig_T* OCConfig);
void TMR_ConfigICStructInit(TMR_ICConfig_T* ICConfig);
void TMR_ConfigBDTStructInit(TMR_BDTConfig_T* BDTConfig);
void TMR_ConfigSinglePulseMode(TMR_T* tmr, TMR_SPM_T singlePulseMode);
void TMR_ConfigClockDivision(TMR_T* tmr, TMR_CLOCK_DIV_T clockDivision);
void TMR_Enable(TMR_T* tmr);
void TMR_Disable(TMR_T* tmr);

/* PWM Configuration */
void TMR_ConfigPWM(TMR_T* tmr, TMR_ICConfig_T* PWMConfig);
void TMR_EnablePWMOutputs(TMR_T* tmr);
void TMR_DisablePWMOutputs(TMR_T* tmr);

/* DMA */
void TMR_ConfigDMA(TMR_T* tmr, TMR_DMA_BASE_T baseAddress, TMR_DMA_BURSTLENGTH_T burstLength);
void TMR_EnableDMASoure(TMR_T* tmr, uint16_t dmaSource);
void TMR_DisableDMASoure(TMR_T* tmr, uint16_t dmaSource);

/* Configuration */
void TMR_ConfigInternalClock(TMR_T* tmr);
void TMR_ConfigIntTrigExternalClock(TMR_T* tmr, TMR_TRIGGER_SOURCE_T triggerSource);
void TMR_ConfigTrigExternalClock(TMR_T* tmr, TMR_TRIGGER_SOURCE_T triggerSource,
                                 TMR_IC_POLARITY_T ICpolarity, uint16_t ICfilter);
void TMR_ConfigETRClockMode1(TMR_T* tmr, TMR_EXTTRG_PSC_T prescaler,
                             TMR_EXTTRG_POL_T polarity, uint16_t filter);
void TMR_ConfigETRClockMode2(TMR_T* tmr, TMR_EXTTRG_PSC_T prescaler,
                             TMR_EXTTRG_POL_T polarity, uint16_t filter);
void TMR_ConfigETR(TMR_T* tmr, TMR_EXTTRG_PSC_T prescaler,
                   TMR_EXTTRG_POL_T polarity, uint16_t filter);
void TMR_ConfigPrescaler(TMR_T* tmr, uint16_t prescaler, TMR_PSC_RELOAD_T pscReloadMode);
void TMR_ConfigCounterMode(TMR_T* tmr, TMR_COUNTER_MODE_T countMode);
void TMR_SelectInputTrigger(TMR_T* tmr, TMR_TRIGGER_SOURCE_T triggerSouce);
void TMR_ConfigEncodeInterface(TMR_T* tmr, TMR_ENCODER_MODE_T encodeMode, TMR_IC_POLARITY_T IC1Polarity,
                               TMR_IC_POLARITY_T IC2Polarity);
void TMR_ConfigForcedOC1(TMR_T* tmr, TMR_FORCED_ACTION_T forcesAction);
void TMR_ConfigForcedOC2(TMR_T* tmr, TMR_FORCED_ACTION_T forcesAction);
void TMR_ConfigForcedOC3(TMR_T* tmr, TMR_FORCED_ACTION_T forcesAction);
void TMR_ConfigForcedOC4(TMR_T* tmr, TMR_FORCED_ACTION_T forcesAction);
void TMR_EnableAutoReload(TMR_T* tmr);
void TMR_DisableAutoReload(TMR_T* tmr);
void TMR_EnableSelectCOM(TMR_T* tmr);
void TMR_DisableSelectCOM(TMR_T* tmr);
void TMR_EnableCCDMA(TMR_T* tmr);
void TMR_DisableCCDMA(TMR_T* tmr);
void TMR_EnableCCPreload(TMR_T* tmr);
void TMR_DisableCCPreload(TMR_T* tmr);
void TMR_ConfigOC1Preload(TMR_T* tmr, TMR_OC_PRELOAD_T OCPreload);
void TMR_ConfigOC2Preload(TMR_T* tmr, TMR_OC_PRELOAD_T OCPreload);
void TMR_ConfigOC3Preload(TMR_T* tmr, TMR_OC_PRELOAD_T OCPreload);
void TMR_ConfigOC4Preload(TMR_T* tmr, TMR_OC_PRELOAD_T OCPreload);
void TMR_ConfigOC1Fast(TMR_T* tmr, TMR_OC_FAST_T OCFast);
void TMR_ConfigOC2Fast(TMR_T* tmr, TMR_OC_FAST_T OCFast);
void TMR_ConfigOC3Fast(TMR_T* tmr, TMR_OC_FAST_T OCFast);
void TMR_ConfigOC4Fast(TMR_T* tmr, TMR_OC_FAST_T OCFast);
void TMR_ClearOC1Ref(TMR_T* tmr, TMR_OC_CLEAR_T OCClear);
void TMR_ClearOC2Ref(TMR_T* tmr, TMR_OC_CLEAR_T OCClear);
void TMR_ClearOC3Ref(TMR_T* tmr, TMR_OC_CLEAR_T OCClear);
void TMR_ClearOC4Ref(TMR_T* tmr, TMR_OC_CLEAR_T OCClear);
void TMR_ConfigOC1Polarity(TMR_T* tmr, TMR_OC_POLARITY_T OCPolarity);
void TMR_ConfigOC1NPolarity(TMR_T* tmr, TMR_OC_NPOLARITY_T OCNPolarity);
void TMR_ConfigOC2Polarity(TMR_T* tmr, TMR_OC_POLARITY_T OCPolarity);
void TMR_ConfigOC2NPolarity(TMR_T* tmr, TMR_OC_NPOLARITY_T OCNPolarity);
void TMR_ConfigOC3Polarity(TMR_T* tmr, TMR_OC_POLARITY_T OCPolarity);
void TMR_ConfigOC3NPolarity(TMR_T* tmr, TMR_OC_NPOLARITY_T OCNPolarity);
void TMR_ConfigOC4Polarity(TMR_T* tmr, TMR_OC_POLARITY_T OCPolarity);
void TMR_EnableCCxChannel(TMR_T* tmr, TMR_CHANNEL_T channel);
void TMR_DisableCCxChannel(TMR_T* tmr, TMR_CHANNEL_T channel);
void TMR_EnableCCxNChannel(TMR_T* tmr, TMR_CHANNEL_T channel);
void TMR_DisableCCxNChannel(TMR_T* tmr, TMR_CHANNEL_T channel);
void TMR_SelectOCxMode(TMR_T* tmr, TMR_CHANNEL_T channel, TMR_OC_MODE_T OCMode);
void TMR_EnableUpdate(TMR_T* tmr);
void TMR_DisableUpdate(TMR_T* tmr);
void TMR_ConfigUpdateRequest(TMR_T* tmr, TMR_UPDATE_SOURCE_T updateSource);
void TMR_EnableHallSensor(TMR_T* tmr);
void TMR_DisableHallSensor(TMR_T* tmr);
void TMR_SelectOutputTrigger(TMR_T* tmr, TMR_TRGO_SOURCE_T TRGOSource);
void TMR_SelectSlaveMode(TMR_T* tmr, TMR_SLAVE_MODE_T slaveMode);
void TMR_EnableMasterSlaveMode(TMR_T* tmr);
void TMR_DisableMasterSlaveMode(TMR_T* tmr);
void TMR_ConfigCounter(TMR_T* tmr, uint16_t counter);
void TMR_ConfigAutoreload(TMR_T* tmr, uint16_t autoReload);
void TMR_ConfigCompare1(TMR_T* tmr, uint16_t compare1);
void TMR_ConfigCompare2(TMR_T* tmr, uint16_t compare2);
void TMR_ConfigCompare3(TMR_T* tmr, uint16_t compare3);
void TMR_ConfigCompare4(TMR_T* tmr, uint16_t compare4);
void TMR_ConfigIC1Prescal(TMR_T* tmr, TMR_IC_PSC_T prescaler);
void TMR_ConfigIC2Prescal(TMR_T* tmr, TMR_IC_PSC_T prescaler);
void TMR_ConfigIC3Prescal(TMR_T* tmr, TMR_IC_PSC_T prescaler);
void TMR_ConfigIC4Prescal(TMR_T* tmr, TMR_IC_PSC_T prescaler);
uint16_t TMR_ReadCaputer1(TMR_T* tmr);
uint16_t TMR_ReadCaputer2(TMR_T* tmr);
uint16_t TMR_ReadCaputer3(TMR_T* tmr);
uint16_t TMR_ReadCaputer4(TMR_T* tmr);
uint16_t TMR_ReadCounter(TMR_T* tmr);
uint16_t TMR_ReadPrescaler(TMR_T* tmr);

/* Interrupts and Event */
void TMR_EnableInterrupt(TMR_T* tmr, uint16_t interrupt);
void TMR_DisableInterrupt(TMR_T* tmr, uint16_t interrupt);
void TMR_GenerateEvent(TMR_T* tmr, uint16_t eventSources);

/* flags */
uint16_t TMR_ReadStatusFlag(TMR_T* tmr, TMR_FLAG_T flag);
void TMR_ClearStatusFlag(TMR_T* tmr, uint16_t flag);
uint16_t TMR_ReadIntFlag(TMR_T* tmr, TMR_INT_T flag);
void TMR_ClearIntFlag(TMR_T* tmr, uint16_t flag);

/**@} end of group TMR_Functions */
/**@} end of group TMR_Driver */
/**@} end of group APM32S10x_StdPeriphDriver */

#ifdef __cplusplus
}
#endif

#endif /* __APM32S10X_TMR_H */
