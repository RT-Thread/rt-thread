/*!
 * @file        apm32f4xx_tmr.h
 *
 * @brief       This file contains all the functions prototypes for the TMR firmware library.
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
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
#ifndef __APM32F4XX_TMR_H
#define __APM32F4XX_TMR_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "apm32f4xx.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @addtogroup TMR_Driver
  @{
*/

/** @defgroup TMR_Enumerations
  @{
*/

/**
 * @brief TMR Output Compare and PWM modes
 */
typedef enum
{
    TMR_OC_MODE_TMRING     = 0x00,  /*!< Frozen TMR output compare mode */
    TMR_OC_MODE_ACTIVE     = 0x01,  /*!< Set output to high when matching */
    TMR_OC_MODE_INACTIVE   = 0x02,  /*!< Set output to low when matching */
    TMR_OC_MODE_TOGGLE     = 0x03,  /*!< Toggle output when matching */
    TMR_OC_MODE_LOWLEVEL   = 0x04,  /*!< Force output to be low */
    TMR_OC_MODE_HIGHLEVEL  = 0x05,  /*!< Force output to be high */
    TMR_OC_MODE_PWM1       = 0x06,  /*!< PWM1 mode */
    TMR_OC_MODE_PWM2       = 0x07   /*!< PWM2 mode */
} TMR_OC_MODE_T;

/**
 * @brief TMR Single Pulse Mode
 */
typedef enum
{
    TMR_SPM_REPETITIVE, /*!< Enable repetitive pulse mode */
    TMR_SPM_SINGLE      /*!< Enable single pulse mode */
} TMR_SPM_T;

/**
 * @brief TMR Input Capture Init structure definition
 */
typedef enum
{
    TMR_CHANNEL_1 = 0x0000, /*!< Timer Channel 1 */
    TMR_CHANNEL_2 = 0x0004, /*!< Timer Channel 2 */
    TMR_CHANNEL_3 = 0x0008, /*!< Timer Channel 3 */
    TMR_CHANNEL_4 = 0x000C  /*!< Timer Channel 4 */
} TMR_CHANNEL_T;

/**
 * @brief TMR Clock division
 */

typedef enum
{
    TMR_CLOCK_DIV_1,    /*!< TDTS = Tck_tim */
    TMR_CLOCK_DIV_2,    /*!< TDTS = 2 * Tck_tim */
    TMR_CLOCK_DIV_4     /*!< TDTS = 4 * Tck_tim */
} TMR_CLOCK_DIV_T;

/**
 * @brief TMR Counter Mode
 */
typedef enum
{
    TMR_COUNTER_MODE_UP              = 0x00,    /*!< Timer Up Counting Mode */
    TMR_COUNTER_MODE_DOWN            = 0x01,    /*!< Timer Down Counting Mode */
    TMR_COUNTER_MODE_CENTER_ALIGNED1 = 0x10,    /*!< Timer Center Aligned Mode1 */
    TMR_COUNTER_MODE_CENTER_ALIGNED2 = 0x20,    /*!< Timer Center Aligned Mode2 */
    TMR_COUNTER_MODE_CENTER_ALIGNED3 = 0x30     /*!< Timer Center Aligned Mode3 */
} TMR_COUNTER_MODE_T;

/**
 * @brief TMR Output Compare Polarity
 */
typedef enum
{
    TMR_OC_POLARITY_HIGH,   /*!< Output Compare active high */
    TMR_OC_POLARITY_LOW     /*!< Output Compare active low */
} TMR_OC_POLARITY_T;

/**
 * @brief TMR Output Compare N Polarity
 */
typedef enum
{
    TMR_OC_NPOLARITY_HIGH,  /*!< Output Compare active high */
    TMR_OC_NPOLARITY_LOW    /*!< Output Compare active low */
} TMR_OC_NPOLARITY_T;

/**
 * @brief TMR Output Compare state
 */
typedef enum
{
    TMR_OC_STATE_DISABLE,   /*!< Disable output compare */
    TMR_OC_STATE_ENABLE     /*!< Enable output compare */
} TMR_OC_STATE_T;

/**
 * @brief TMR Output Compare N state
 */
typedef enum
{
    TMR_OC_NSTATE_DISABLE,  /*!< Disable complementary output */
    TMR_OC_NSTATE_ENABLE    /*!< Enable complementary output */
} TMR_OC_NSTATE_T;

/**
 * @brief TMR BRK state
 */
typedef enum
{
    TMR_BRK_STATE_DISABLE,  /*!< Disable brake function */
    TMR_BRK_STATE_ENABLE    /*!< Enable brake function */
} TMR_BRK_STATE_T;

/**
 * @brief TMR Specifies the Break Input pin polarity.
 */
typedef enum
{
    TMR_BRK_POLARITY_LOW,   /*!< BRK low level valid */
    TMR_BRK_POLARITY_HIGH   /*!< BRK high level valid */
} TMR_BRK_POLARITY_T;

/**
 * @brief TMR Specifies the Break Input pin polarity.
 */
typedef enum
{
    TMR_AUTOMATIC_OUTPUT_DISABLE,   /*!< Disable automatic output */
    TMR_AUTOMATIC_OUTPUT_ENABLE     /*!< Enable automatic output */
} TMR_AUTOMATIC_OUTPUT_T;

/**
 * @brief TMR Protect mode configuration values
 */
typedef enum
{
    TMR_LOCK_LEVEL_OFF, /*!< No lock write protection */
    TMR_LOCK_LEVEL_1,   /*!< Lock write protection level 1 */
    TMR_LOCK_LEVEL_2,   /*!< Lock write protection level 2 */
    TMR_LOCK_LEVEL_3    /*!< Lock write protection level 3 */
} TMR_LOCK_LEVEL_T;

/**
 * @brief TMR Specifies the Off-State selection used in Run mode
 */
typedef enum
{
    TMR_RMOS_STATE_DISABLE, /*!< Disable run mode off-state */
    TMR_RMOS_STATE_ENABLE   /*!< Enable run mode off-state */
} TMR_RMOS_STATE_T;

/**
 * @brief TMR Closed state configuration in idle mode
 */
typedef enum
{
    TMR_IMOS_STATE_DISABLE, /*!< Disable idle mode off-state */
    TMR_IMOS_STATE_ENABLE   /*!< Enable idle mode off-state */
} TMR_IMOS_STATE_T;

/**
 * @brief TMR Output Compare Idle State
 */
typedef enum
{
    TMR_OC_IDLE_STATE_RESET,    /*!< Reset output compare idle state */
    TMR_OC_IDLE_STATE_SET       /*!< Set output compare idle state */
} TMR_OC_IDLE_STATE_T;

/**
 * @brief TMR Output Compare N Idle State
 */
typedef enum
{
    TMR_OC_NIDLE_STATE_RESET,   /*!< Reset output complementary idle state */
    TMR_OC_NIDLE_STATE_SET      /*!< Set output complementary idle state */
} TMR_OC_NIDLE_STATE_T;

/**
 * @brief TMR Input Capture Polarity
 */
typedef enum
{
    TMR_IC_POLARITY_RISING   = 0x00,    /*!< Rising edge */
    TMR_IC_POLARITY_FALLING  = 0x02,    /*!< Falling edge */
    TMR_IC_POLARITY_BOTHEDGE = 0x0A     /*!< Both rising and falling edge */
} TMR_IC_POLARITY_T;

/**
 * @brief TMR Input Capture Selection
 */
typedef enum
{
    TMR_IC_SELECTION_DIRECT_TI   = 0x01,    /*!< Input capture mapping in TI1 */
    TMR_IC_SELECTION_INDIRECT_TI = 0x02,    /*!< Input capture mapping in TI2 */
    TMR_IC_SELECTION_TRC         = 0x03     /*!< Input capture mapping in TRC */
} TMR_IC_SELECTION_T;

/**
 * @brief TMR Input Capture Prescaler
 */
typedef enum
{
    TMR_IC_PSC_1,   /*!< No prescaler */
    TMR_IC_PSC_2,   /*!< Capture is done once every 2 events */
    TMR_IC_PSC_4,   /*!< capture is done once every 4 events */
    TMR_IC_PSC_8    /*!< capture is done once every 8 events */
} TMR_IC_PSC_T;

/**
 * @brief TMR_interrupt_sources
 */
typedef enum
{
    TMR_INT_UPDATE = 0x0001,    /*!< Timer update Interrupt source */
    TMR_INT_CC1    = 0x0002,    /*!< Timer Capture Compare 1 Interrupt source */
    TMR_INT_CC2    = 0x0004,    /*!< Timer Capture Compare 2 Interrupt source */
    TMR_INT_CC3    = 0x0008,    /*!< Timer Capture Compare 3 Interrupt source */
    TMR_INT_CC4    = 0x0010,    /*!< Timer Capture Compare 4 Interrupt source */
    TMR_INT_COM    = 0x0020,    /*!< Timer Commutation Interrupt source (Only for TMR1 and TMR8) */
    TMR_INT_TRG    = 0x0040,    /*!< Timer Trigger Interrupt source */
    TMR_INT_BRK    = 0x0080     /*!< Timer Break Interrupt source (Only for TMR1 and TMR8) */
} TMR_INT_T;

/**
 * @brief TMR DMA Base Address
 */
typedef enum
{
    TMR_DMA_BASE_CTRL1   = 0x0000,  /*!< TMR CTRL1 DMA base address setup */
    TMR_DMA_BASE_CTRL2   = 0x0001,  /*!< TMR CTRL2 DMA base address setup */
    TMR_DMA_BASE_SMCTRL  = 0x0002,  /*!< TMR SMCTRL DMA base address setup */
    TMR_DMA_BASE_DIEN    = 0x0003,  /*!< TMR DIEN DMA base address setup */
    TMR_DMA_BASE_STS     = 0x0004,  /*!< TMR STS DMA base address setup */
    TMR_DMA_BASE_CEG     = 0x0005,  /*!< TMR CEG DMA base address setup */
    TMR_DMA_BASE_CCM1    = 0x0006,  /*!< TMR CCM1 DMA base address setup */
    TMR_DMA_BASE_CCM2    = 0x0007,  /*!< TMR CCM2 DMA base address setup */
    TMR_DMA_BASE_CCEN    = 0x0008,  /*!< TMR CCEN DMA base address setup */
    TMR_DMA_BASE_CNT     = 0x0009,  /*!< TMR CNT DMA base address setup */
    TMR_DMA_BASE_PSC     = 0x000A,  /*!< TMR PSC DMA base address setup */
    TMR_DMA_BASE_AUTORLD = 0x000B,  /*!< TMR AUTORLD DMA base address setup */
    TMR_DMA_BASE_REPCNT  = 0x000C,  /*!< TMR REPCNT DMA base address setup */
    TMR_DMA_BASE_CC1     = 0x000D,  /*!< TMR CC1 DMA base address setup */
    TMR_DMA_BASE_CC2     = 0x000E,  /*!< TMR CC2 DMA base address setup */
    TMR_DMA_BASE_CC3     = 0x000F,  /*!< TMR CC3 DMA base address setup */
    TMR_DMA_BASE_CC4     = 0x0010,  /*!< TMR CC4 DMA base address setup */
    TMR_DMA_BASE_BDT     = 0x0011,  /*!< TMR BDT DMA base address setup */
    TMR_DMA_BASE_DCTRL   = 0x0012   /*!< TMR DCTRL DMA base address setup */
} TMR_DMA_BASE_T;

/**
 * @brief TMR DMA Soueces
 */
typedef enum
{
    TMR_DMA_SOURCE_UPDATE    = 0x0100,  /*!< TMR update DMA souces */
    TMR_DMA_SOURCE_CH1       = 0x0200,  /*!< TMR Capture Compare 1 DMA souces */
    TMR_DMA_SOURCE_CH2       = 0x0400,  /*!< TMR Capture Compare 2 DMA souces */
    TMR_DMA_SOURCE_CH3       = 0x0800,  /*!< TMR Capture Compare 3 DMA souces */
    TMR_DMA_SOURCE_CH4       = 0x1000,  /*!< TMR Capture Compare 4 DMA souces */
    TMR_DMA_SOURCE_COM       = 0x2000,  /*!< TMR Commutation DMA souces */
    TMR_DMA_SOURCE_TRG       = 0x4000   /*!< TMR Trigger DMA souces */
} TMR_DMA_SOURCE_T;

/**
 * @brief TMR  The external Trigger Prescaler.
 */
typedef enum
{
    TMR_EXTTRG_PSC_OFF   = 0x00,    /*!< ETRP Prescaler OFF */
    TMR_EXTTRG_PSC_DIV2  = 0x01,    /*!< ETRP frequency divided by 2 */
    TMR_EXTTRG_PSC_DIV4  = 0x02,    /*!< ETRP frequency divided by 4 */
    TMR_EXTTRG_PSC_DIV8  = 0x03     /*!< ETRP frequency divided by 8 */
} TMR_EXTTRG_PSC_T;

/**
 * @brief TMR Internal Trigger Selection
 */
typedef enum
{
    TMR_TRIGGER_SOURCE_ITR0     = 0x00, /*!< Internal Trigger 0 */
    TMR_TRIGGER_SOURCE_ITR1     = 0x01, /*!< Internal Trigger 1 */
    TMR_TRIGGER_SOURCE_ITR2     = 0x02, /*!< Internal Trigger 2 */
    TMR_TRIGGER_SOURCE_ITR3     = 0x03, /*!< Internal Trigger 3 */
    TMR_TRIGGER_SOURCE_TI1F_ED  = 0x04, /*!< TI1 Edge Detector */
    TMR_TRIGGER_SOURCE_TI1FP1   = 0x05, /*!< Filtered Timer Input 1 */
    TMR_TRIGGER_SOURCE_TI2FP2   = 0x06, /*!< Filtered Timer Input 2 */
    TMR_TRIGGER_SOURCE_ETRF     = 0x07  /*!< External Trigger input */
} TMR_TRIGGER_SOURCE_T;

/**
 * @brief TMR External Trigger Polarity
 */
typedef enum
{
    TMR_EXTTGR_POL_NONINVERTED, /*!< Active high or rising edge active */
    TMR_EXTTRG_POL_INVERTED     /*!< Active low or falling edge active */
} TMR_EXTTRG_POL_T;

/**
 * @brief TMR Prescaler Reload Mode
 */
typedef enum
{
    TMR_PSC_RELOAD_UPDATE,      /*!< The Prescaler reload at the update event */
    TMR_PSC_RELOAD_IMMEDIATE    /*!< The Prescaler reload immediately */
} TMR_PSC_RELOAD_T;

/**
 * @brief TMR Forced Action
 */
typedef enum
{
    TMR_FORCED_ACTION_INACTIVE = 0x04,  /*!< Force inactive level on OC1REF */
    TMR_FORCED_ACTION_ACTIVE   = 0x05   /*!< Force active level on OC1REF */
} TMR_FORCED_ACTION_T;

/**
 * @brief TMR Encoder Mode
 */
typedef enum
{
    TMR_ENCODER_MODE_TI1      = 0x01,   /*!< Encoder mode 1 */
    TMR_ENCODER_MODE_TI2      = 0x02,   /*!< Encoder mode 2 */
    TMR_ENCODER_MODE_TI12     = 0x03    /*!< Encoder mode 3 */
} TMR_ENCODER_MODE_T;

/**
 * @brief TMR event sources
 */
typedef enum
{
    TMR_EVENT_UPDATE = 0x001,   /*!< Timer update Interrupt source */
    TMR_EVENT_CH1    = 0x002,   /*!< Timer Capture Compare 1 Event source */
    TMR_EVENT_CH2    = 0x004,   /*!< Timer Capture Compare 1 Event source */
    TMR_EVENT_CH3    = 0x008,   /*!< Timer Capture Compare 3 Event source */
    TMR_EVENT_CH4    = 0x010,   /*!< Timer Capture Compare 4 Event source */
    TMR_EVENT_COM    = 0x020,   /*!< Timer Commutation Event source (Only for TMR1 and TMR8) */
    TMR_EVENT_TRG    = 0x040,   /*!< Timer Trigger Event source */
    TMR_EVENT_BRK    = 0x080    /*!< Timer Break Event source (Only for TMR1 and TMR8) */
} TMR_EVENT_T;

/**
 * @brief TMR UpdateSource
 */
typedef enum
{
    TMR_UPDATE_SOURCE_GLOBAL,   /*!< Source of update is
                                    - Counter overflow/underflow.
                                    - UEG bit of Control event generation register(CEG) is set.
                                    - Update generation through the slave mode controller. */
    TMR_UPDATE_SOURCE_REGULAR   /*!< Source of update is Counter overflow/underflow */
} TMR_UPDATE_SOURCE_T;

/**
 * @brief TMR Output Compare Preload State
 */
typedef enum
{
    TMR_OC_PRELOAD_DISABLE, /*!< Enable preload */
    TMR_OC_PRELOAD_ENABLE   /*!< Disable preload */
} TMR_OC_PRELOAD_T;

/**
 * @brief TMR Output Compare Preload State
 */
typedef enum
{
    TMR_OC_FAST_DISABLE,    /*!< Disable fast output compare */
    TMR_OC_FAST_ENABLE      /*!< Enable fast output compare */
} TMR_OC_FAST_T;

/**
 * @brief TMR Output Compare Preload State
 */
typedef enum
{
    TMR_OC_CLEAR_DISABLE,   /*!< Disable output compare clear */
    TMR_OC_CLEAR_ENABLE     /*!< Enable output compare clear */
} TMR_OC_CLEAR_T;

/**
 * @brief TMR Trigger Output Source
 */
typedef enum
{
    TMR_TRGO_SOURCE_RESET,  /*!< Select reset signal as TRGO source  */
    TMR_TRGO_SOURCE_ENABLE, /*!< Select enable signal as TRGO source */
    TMR_TRGO_SOURCE_UPDATE, /*!< Select update signal as TRGO source */
    TMR_TRGO_SOURCE_OC1,    /*!< Select OC1 signal as TRGO source */
    TMR_TRGO_SOURCE_OC1REF, /*!< Select OC1REF signal as TRGO source */
    TMR_TRGO_SOURCE_OC2REF, /*!< Select OC2REF signal as TRGO source */
    TMR_TRGO_SOURCE_OC3REF, /*!< Select OC3REF signal as TRGO source */
    TMR_TRGO_SOURCE_OC4REF  /*!< Select OC4REF signal as TRGO source */
} TMR_TRGO_SOURCE_T;

/**
 * @brief TMR Slave Mode
 */
typedef enum
{
    TMR_SLAVE_MODE_RESET     = 0x04,    /*!< Reset mode */
    TMR_SLAVE_MODE_GATED     = 0x05,    /*!< Gated mode */
    TMR_SLAVE_MODE_TRIGGER   = 0x06,    /*!< Trigger mode */
    TMR_SLAVE_MODE_EXTERNAL1 = 0x07     /*!< External 1 mode */
} TMR_SLAVE_MODE_T;

/**
 * @brief TMR Remap
 */
typedef enum
{
    TMR2_TMR8_TRGO     = 0x0000,    /*!< TMR2 ITR1 input is connected to TMR8 Trigger output(default) */
    TMR2_PTP_TRG       = 0x0400,    /*!< TMR2 ITR1 input is connected to ETH PTP trigger output */
    TMR2_OTG_FSUSB_SOF = 0x0800,    /*!< TMR2 ITR1 input is connected to OTG FS SOF */
    TMR2_OTG_HSUSB_SOF = 0x0C00,    /*!< TMR2 ITR1 input is connected to OTG HS SOF */
    TMR5_GPIO          = 0x0000,    /*!< TMR5 CH4 input is connected to GPIO */
    TMR5_LSI           = 0x0040,    /*!< TMR5 CH4 input is connected to LSI clock */
    TMR5_LSE           = 0x0080,    /*!< TMR5 CH4 input is connected to LSE clock */
    TMR5_RTC           = 0x00C0,    /*!< TMR5 CH4 input is connected to RTC Output event */
    TMRx_GPIO          = 0x0000,    /*!< TMR10/11/13/14 CH1 input is connected to GPIO */
    TMRx_RTCCLK        = 0x0001,    /*!< TMR10/11/13/14 CH1 input is connected to RTC clock */
    TMRx_HSECLK        = 0x0002,    /*!< TMR10/11/13/14 CH1 input is connected to HSE clock/32 */
    TMRx_MCO           = 0x0003     /*!< TMR10/11/13/14 CH1 input is connected to MCO */
} TMR_REMAP_T;

/**
 * @brief TMR Flag
 */
typedef enum
{
    TMR_FLAG_UPDATE  = 0x0001,  /*!< Timer update Flag */
    TMR_FLAG_CC1     = 0x0002,  /*!< Timer Capture Compare 1 Flag */
    TMR_FLAG_CC2     = 0x0004,  /*!< Timer Capture Compare 2 Flag */
    TMR_FLAG_CC3     = 0x0008,  /*!< Timer Capture Compare 3 Flag */
    TMR_FLAG_CC4     = 0x0010,  /*!< Timer Capture Compare 4 Flag */
    TMR_FLAG_COM     = 0x0020,  /*!< Timer Commutation Flag (Only for TMR1 and TMR8) */
    TMR_FLAG_TRG     = 0x0040,  /*!< Timer Trigger Flag */
    TMR_FLAG_BRK     = 0x0080,  /*!< Timer Break Flag (Only for TMR1 and TMR8) */
    TMR_FLAG_CC1RC   = 0x0200,  /*!< Timer Capture Compare 1 Repetition Flag */
    TMR_FLAG_CC2RC   = 0x0400,  /*!< Timer Capture Compare 2 Repetition Flag */
    TMR_FLAG_CC3RC   = 0x0800,  /*!< Timer Capture Compare 3 Repetition Flag */
    TMR_FLAG_CC4RC   = 0x1000   /*!< Timer Capture Compare 4 Repetition Flag */
} TMR_FLAG_T;

/**
 * @brief TMR DMA Burst Length
 */
typedef enum
{
    TMR_DMA_BURSTLENGTH_1TRANSFER   = 0x0000,   /*!< Select TMR DMA burst Length 1 */
    TMR_DMA_BURSTLENGTH_2TRANSFERS  = 0x0100,   /*!< Select TMR DMA burst Length 2 */
    TMR_DMA_BURSTLENGTH_3TRANSFERS  = 0x0200,   /*!< Select TMR DMA burst Length 3 */
    TMR_DMA_BURSTLENGTH_4TRANSFERS  = 0x0300,   /*!< Select TMR DMA burst Length 4 */
    TMR_DMA_BURSTLENGTH_5TRANSFERS  = 0x0400,   /*!< Select TMR DMA burst Length 5 */
    TMR_DMA_BURSTLENGTH_6TRANSFERS  = 0x0500,   /*!< Select TMR DMA burst Length 6 */
    TMR_DMA_BURSTLENGTH_7TRANSFERS  = 0x0600,   /*!< Select TMR DMA burst Length 7 */
    TMR_DMA_BURSTLENGTH_8TRANSFERS  = 0x0700,   /*!< Select TMR DMA burst Length 8 */
    TMR_DMA_BURSTLENGTH_9TRANSFERS  = 0x0800,   /*!< Select TMR DMA burst Length 9 */
    TMR_DMA_BURSTLENGTH_10TRANSFERS = 0x0900,   /*!< Select TMR DMA burst Length 10 */
    TMR_DMA_BURSTLENGTH_11TRANSFERS = 0x0A00,   /*!< Select TMR DMA burst Length 11 */
    TMR_DMA_BURSTLENGTH_12TRANSFERS = 0x0B00,   /*!< Select TMR DMA burst Length 12 */
    TMR_DMA_BURSTLENGTH_13TRANSFERS = 0x0C00,   /*!< Select TMR DMA burst Length 13 */
    TMR_DMA_BURSTLENGTH_14TRANSFERS = 0x0D00,   /*!< Select TMR DMA burst Length 14 */
    TMR_DMA_BURSTLENGTH_15TRANSFERS = 0x0E00,   /*!< Select TMR DMA burst Length 15 */
    TMR_DMA_BURSTLENGTH_16TRANSFERS = 0x0F00,   /*!< Select TMR DMA burst Length 16 */
    TMR_DMA_BURSTLENGTH_17TRANSFERS = 0x1000,   /*!< Select TMR DMA burst Length 17 */
    TMR_DMA_BURSTLENGTH_18TRANSFERS = 0x1100    /*!< Select TMR DMA burst Length 18 */
} TMR_DMA_BURSTLENGTH_T;

/**@} end of group TMR_Enumerations*/

/** @addtogroup TMR_Structure Data Structure
  @{
*/

/**
 * @brief TMR Time Base Init structure definition
 * @note  This structure is used with all TMR except for TMR6 and TMR7.
 */
typedef struct
{
    TMR_COUNTER_MODE_T countMode;           /*!< TMR counter mode selection */
    TMR_CLOCK_DIV_T    clockDivision;       /*!< TMR clock division selection */
    uint16_t           period;              /*!< This must between 0x0000 and 0xFFFF */
    uint16_t           division;            /*!< This must between 0x0000 and 0xFFFF */
    uint8_t            repetitionCounter;   /*!< This must between 0x00 and 0xFF, only for TMR1 and TMR8. */
} TMR_BaseConfig_T;

/**
 * @brief TMR Config struct definition
 */
typedef struct
{
    TMR_OC_MODE_T        mode;          /*!< TMR Output Compare and PWM modes selection */
    TMR_OC_STATE_T       outputState;   /*!< TMR Output Compare state selection */
    TMR_OC_NSTATE_T      outputNState;  /*!< TMR Output Compare N state selection */
    TMR_OC_POLARITY_T    polarity;      /*!< TMR Output Compare Polarity selection */
    TMR_OC_NPOLARITY_T   nPolarity;     /*!< TMR Output Compare N Polarity selection */
    TMR_OC_IDLE_STATE_T  idleState;     /*!< TMR Output Compare Idle State selection */
    TMR_OC_NIDLE_STATE_T nIdleState;    /*!< TMR Output Compare N Idle State selection */
    uint16_t             pulse;         /*!< This must between 0x0000 and 0xFFFF */
} TMR_OCConfig_T;

/**
 * @brief TMR Input Capture Config struct definition
 */
typedef struct
{
    TMR_CHANNEL_T      channel;     /*!< Timer channel selection */
    TMR_IC_POLARITY_T  polarity;    /*!< TMR input capture polarity selection */
    TMR_IC_SELECTION_T selection;   /*!< TMR Input capture selection */
    TMR_IC_PSC_T       prescaler;   /*!< TMR Input Capture selection */
    uint16_t           filter;      /*!< This must between 0x00 and 0x0F */
} TMR_ICConfig_T;

/**
 * @brief TMR BDT structure definition
 */
typedef struct
{
    TMR_RMOS_STATE_T       RMOS;            /*!< TMR Specifies the Off-State selection used in Run mode selection */
    TMR_IMOS_STATE_T       IMOS;            /*!< TMR Closed state configuration in idle mode selection */
    TMR_LOCK_LEVEL_T       lockLevel;       /*!< TMR Protect mode configuration values selection */
    uint16_t               deadTime;        /*!< Setup dead time */
    TMR_BRK_STATE_T        BRKState;        /*!< Setup TMR BRK state */
    TMR_BRK_POLARITY_T     BRKPolarity;     /*!< Setup TMR BRK polarity */
    TMR_AUTOMATIC_OUTPUT_T automaticOutput; /*!< Setup break input pin polarity */
} TMR_BDTConfig_T;

/**@} end of group TMR_Structure*/

/** @defgroup TMR_Functions
  @{
*/

/* Reset and Configuration */
void TMR_Reset(TMR_T* tmr);
void TMR_ConfigTimeBase(TMR_T* tmr, TMR_BaseConfig_T* baseConfig);
void TMR_ConfigTimeBaseStructInit(TMR_BaseConfig_T* baseConfig);
void TMR_ConfigPrescaler(TMR_T* tmr, uint16_t prescaler, TMR_PSC_RELOAD_T reload);
void TMR_ConfigCounterMode(TMR_T* tmr, TMR_COUNTER_MODE_T countMode);
void TMR_ConfigCounter(TMR_T* tmr, uint16_t counter);
void TMR_ConfigAutoreload(TMR_T* tmr, uint16_t autoReload);
uint16_t TMR_ReadCounter(TMR_T* tmr);
uint16_t TMR_ReadPrescaler(TMR_T* tmr);
void TMR_EnableUpdate(TMR_T* tmr);
void TMR_DisableUpdate(TMR_T* tmr);
void TMR_ConfigUpdateRequest(TMR_T* tmr, TMR_UPDATE_SOURCE_T updateSource);
void TMR_EnableAutoReload(TMR_T* tmr);
void TMR_DisableAutoReload(TMR_T* tmr);
void TMR_ConfigSinglePulseMode(TMR_T* tmr, TMR_SPM_T singlePulseMode);
void TMR_ConfigClockDivision(TMR_T* tmr, TMR_CLOCK_DIV_T clockDivision);
void TMR_Enable(TMR_T* tmr);
void TMR_Disable(TMR_T* tmr);

/* Output Compare */
void TMR_ConfigOC1(TMR_T* tmr, TMR_OCConfig_T* OCConfig);
void TMR_ConfigOC2(TMR_T* tmr, TMR_OCConfig_T* OCConfig);
void TMR_ConfigOC3(TMR_T* tmr, TMR_OCConfig_T* OCConfig);
void TMR_ConfigOC4(TMR_T* tmr, TMR_OCConfig_T* OCConfig);
void TMR_ConfigOCStructInit(TMR_OCConfig_T* OCConfig);
void TMR_SelectOCxMode(TMR_T* tmr, TMR_CHANNEL_T channel, TMR_OC_MODE_T mode);
void TMR_ConfigCompare1(TMR_T* tmr, uint32_t compare1);
void TMR_ConfigCompare2(TMR_T* tmr, uint32_t compare2);
void TMR_ConfigCompare3(TMR_T* tmr, uint32_t compare3);
void TMR_ConfigCompare4(TMR_T* tmr, uint32_t compare4);
void TMR_ConfigForcedOC1(TMR_T* tmr, TMR_FORCED_ACTION_T forcesAction);
void TMR_ConfigForcedOC2(TMR_T* tmr, TMR_FORCED_ACTION_T forcesAction);
void TMR_ConfigForcedOC3(TMR_T* tmr, TMR_FORCED_ACTION_T forcesAction);
void TMR_ConfigForcedOC4(TMR_T* tmr, TMR_FORCED_ACTION_T forcesAction);
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

/* Input Capture */
void TMR_ConfigIC(TMR_T* tmr, TMR_ICConfig_T* ICConfig);
void TMR_ConfigICStructInit(TMR_ICConfig_T* ICConfig);
void TMR_ConfigPWM(TMR_T* tmr, TMR_ICConfig_T* PWMConfig);
uint32_t TMR_ReadCaputer1(TMR_T* tmr);
uint32_t TMR_ReadCaputer2(TMR_T* tmr);
uint32_t TMR_ReadCaputer3(TMR_T* tmr);
uint32_t TMR_ReadCaputer4(TMR_T* tmr);
void TMR_ConfigIC1Prescaler(TMR_T* tmr, TMR_IC_PSC_T prescaler);
void TMR_ConfigIC2Prescaler(TMR_T* tmr, TMR_IC_PSC_T prescaler);
void TMR_ConfigIC3Prescaler(TMR_T* tmr, TMR_IC_PSC_T prescaler);
void TMR_ConfigIC4Prescaler(TMR_T* tmr, TMR_IC_PSC_T prescaler);

/* Advanced-control timers (TMR1 and TMR8) specific features */
void TMR_ConfigBDT(TMR_T* tmr, TMR_BDTConfig_T* BDTConfig);
void TMR_ConfigBDTStructInit( TMR_BDTConfig_T* BDTConfig);
void TMR_EnablePWMOutputs(TMR_T* tmr);
void TMR_DisablePWMOutputs(TMR_T* tmr);
void TMR_EnableSelectCOM(TMR_T* tmr);
void TMR_DisableSelectCOM(TMR_T* tmr);
void TMR_EnableCCPreload(TMR_T* tmr);
void TMR_DisableCCPreload(TMR_T* tmr);

/* DMA management */
void TMR_ConfigDMA(TMR_T* tmr, TMR_DMA_BASE_T baseAddress, TMR_DMA_BURSTLENGTH_T burstLength);
void TMR_EnableDMASoure(TMR_T* tmr, uint16_t dmaSource);
void TMR_DisableDMASoure(TMR_T* tmr, uint16_t dmaSource);
void TMR_EnableCCDMA(TMR_T* tmr);
void TMR_DisableCCDMA(TMR_T* tmr);

/* Clocks management */
void TMR_ConfigInternalClock(TMR_T* tmr);
void TMR_ConfigIntTrigExternalClock(TMR_T* tmr, TMR_TRIGGER_SOURCE_T triggerSource);
void TMR_ConfigTrigExternalClock(TMR_T* tmr, TMR_TRIGGER_SOURCE_T triggerSource,
                                 TMR_IC_POLARITY_T ICpolarity, uint16_t ICfilter);
void TMR_ConfigETRClockMode1(TMR_T* tmr, TMR_EXTTRG_PSC_T prescaler,
                             TMR_EXTTRG_POL_T polarity, uint16_t filter);
void TMR_ConfigETRClockMode2(TMR_T* tmr, TMR_EXTTRG_PSC_T prescaler,
                             TMR_EXTTRG_POL_T polarity, uint16_t filter);

/* Synchronization management */
void TMR_SelectInputTrigger(TMR_T* tmr, TMR_TRIGGER_SOURCE_T triggerSource);
void TMR_SelectOutputTrigger(TMR_T* tmr, TMR_TRGO_SOURCE_T TRGOSource);
void TMR_SelectSlaveMode(TMR_T* tmr, TMR_SLAVE_MODE_T slaveMode);
void TMR_EnableMasterSlaveMode(TMR_T* tmr);
void TMR_DisableMasterSlaveMode(TMR_T* tmr);
void TMR_ConfigETR(TMR_T* tmr, TMR_EXTTRG_PSC_T prescaler,
                   TMR_EXTTRG_POL_T polarity, uint16_t filter);

/* Interface */
void TMR_ConfigEncodeInterface(TMR_T* tmr, TMR_ENCODER_MODE_T encodeMode,  \
                               TMR_IC_POLARITY_T IC1Polarity,TMR_IC_POLARITY_T IC2Polarity);
void TMR_EnableHallSensor(TMR_T* tmr);
void TMR_DisableHallSensor(TMR_T* tmr);

/* Remapping  */
void TMR_ConfigRemap(TMR_T* tmr, uint32_t remap);

/* Interrupts and flags  */
void TMR_EnableInterrupt(TMR_T* tmr, uint16_t interrupt);
void TMR_DisableInterrupt(TMR_T* tmr, uint16_t interrupt);
void TMR_GenerateEvent(TMR_T* tmr, uint16_t eventSources);
uint16_t TMR_ReadStatusFlag(TMR_T* tmr, TMR_FLAG_T flag);
void TMR_ClearStatusFlag(TMR_T* tmr, uint16_t flag);
uint16_t TMR_ReadIntFlag(TMR_T* tmr,  TMR_INT_T flag);
void TMR_ClearIntFlag(TMR_T* tmr,  uint16_t flag);

#ifdef __cplusplus
}
#endif

#endif /*__APM32F4XX_TMR_H */

/**@} end of group TMR_Enumerations */
/**@} end of group TMR_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
