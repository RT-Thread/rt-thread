/*!
 * @file        apm32f0xx_tmr.h
 *
 * @brief       This file contains all functions prototype and macros for the TMR peripheral
 *
 * @version     V1.0.3
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#ifndef __APM32F0XX_TMR_H
#define __APM32F0XX_TMR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup TMR_Driver TMR Driver
  @{
*/

/** @defgroup TMR_Marcos Marcos
  @{
  */

/**@} end of group TMR_Marcos */

/** @defgroup  TMR_Enumerations Enumerations
  @{
*/

/**
 * @brief   Counter_Mode
 */
typedef enum
{
    TMR_COUNTER_MODE_UP = 0,                /*!< Timer Up Counting Mode */
    TMR_COUNTER_MODE_DOWN = 1,              /*!< Timer Down Counting Mode */
    TMR_COUNTER_MODE_CENTERALIGNED1 = 2,    /*!< Timer Center Aligned Mode1 */
    TMR_COUNTER_MODE_CENTERALIGNED2 = 4,    /*!< Timer Center Aligned Mode2 */
    TMR_COUNTER_MODE_CENTERALIGNED3 = 6     /*!< Timer Center Aligned Mode3 */
} TMR_COUNTER_MODE_T;

/**
 * @brief   Clock_Division_CKD
 */
typedef enum
{
    TMR_CKD_DIV1 = 0,    /*!< TDTS = Tck_tim */
    TMR_CKD_DIV2 = 1,    /*!< TDTS = 2 * Tck_tim */
    TMR_CKD_DIV4 = 2     /*!< TDTS = 4 * Tck_tim */
} TMR_CKD_T;

/**
 * @brief   Prescaler_Reload_Mode
 */
typedef enum
{
    TMR_PRESCALER_RELOAD_UPDATA = 0,    /*!< The Prescaler reload at the update event */
    TMR_PRESCALER_RELOAD_IMMEDIATE = 1  /*!< The Prescaler reload immediately */
} TMR_PRESCALER_RELOAD_T;

/**
 * @brief    TMR UpdateSource
 */
typedef enum
{
    TMR_UPDATE_SOURCE_GLOBAL = 0,   /*!< Source of update is Counter overflow/underflow.
                                       - UEG bit of Control event generation register(CEG) is set.
                                       - Update generation through the slave mode controller. */
    TMR_UPDATE_SOURCE_REGULAR = 1   /*!< Source of update is Counter overflow/underflow */
} TMR_UPDATE_SOURCE_T;

/**
 * @brief    TMR OPMode
 */
typedef enum
{
    TMR_OPMODE_REPETITIVE = 0,  /*!< Enable repetitive pulse mode */
    TMR_OPMODE_SINGLE = 1       /*!< Enable single pulse mode */
} TMR_OPMODE_T;

/**
 * @brief TMR Specifies the Off-State selection used in Run mode
 */
typedef enum
{
    TMR_RMOS_STATE_DISABLE = 0,     /*!< Disable run mode off-state */
    TMR_RMOS_STATE_ENABLE = 1       /*!< Enable run mode off-state */
} TMR_RMOS_STATE_T;

/**
 * @brief TMR Closed state configuration in idle mode
 */
typedef enum
{
    TMR_IMOS_STATE_DISABLE = 0,     /*!< Disable idle mode off-state */
    TMR_IMOS_STATE_ENABLE = 1       /*!< Enable idle mode off-state */
} TMR_IMOS_STATE_T;

/**
 * @brief TMR Protect mode configuration values
 */
typedef enum
{
    TMR_LOCK_LEVEL_OFF = 0,  /*!< No lock write protection */
    TMR_LOCK_LEVEL_1 = 1,    /*!< Lock write protection level 1 */
    TMR_LOCK_LEVEL_2 = 2,    /*!< Lock write protection level 2 */
    TMR_LOCK_LEVEL_3 = 3     /*!< Lock write protection level 3 */
} TMR_LOCK_LEVEL_T;

/**
 * @brief TMR break state
 */
typedef enum
{
    TMR_BREAK_STATE_DISABLE,  /*!< Disable brake function */
    TMR_BREAK_STATE_ENABLE    /*!< Enable brake function */
} TMR_BREAK_STATE_T;

/**
 * @brief TMR Specifies the Break Input pin polarity.
 */
typedef enum
{
    TMR_BREAK_POLARITY_LOW,  /*!< BREAK low level valid */
    TMR_BREAK_POLARITY_HIGH  /*!< BREAK high level valid */
} TMR_BREAK_POLARITY_T;

/**
 * @brief TMR Automatic Output feature is enable or disable
 */
typedef enum
{
    TMR_AUTOMATIC_OUTPUT_DISABLE,  /*!< Disable automatic output */
    TMR_AUTOMATIC_OUTPUT_ENABLE    /*!< Enable automatic output */
} TMR_AUTOMATIC_OUTPUT_T;

/**
 * @brief TMR_Output_Compare_and_PWM_modes
 */
typedef enum
{
    TMR_OC_MODE_TMRING     = 0x00, /*!< Frozen TMR output compare mode */
    TMR_OC_MODE_ACTIVE     = 0x01, /*!< Set output to high when matching */
    TMR_OC_MODE_INACTIVE   = 0x02, /*!< Set output to low when matching */
    TMR_OC_MODE_TOGGEL     = 0x03, /*!< Toggle output when matching */
    TMR_OC_MODE_LOWLEVEL   = 0x04, /*!< Force output to be low */
    TMR_OC_MODE_HIGHLEVEL  = 0x05, /*!< Force output to be high */
    TMR_OC_MODE_PWM1       = 0x06, /*!< PWM1 mode */
    TMR_OC_MODE_PWM2       = 0x07  /*!< PWM2 mode */
} TMR_OC_MODE_T;

/**
 * @brief TMR_Output_Compare_state
 */
typedef enum
{
    TMR_OUTPUT_STATE_DISABLE,   /*!< Disable output compare */
    TMR_OUTPUT_STATE_ENABLE     /*!< Enable output compare */
} TMR_OC_OUTPUT_STATE_T;

/**
 * @brief TMR_Output_Compare_N_state
 */
typedef enum
{
    TMR_OUTPUT_NSTATE_DISABLE,  /*!< Disable complementary output */
    TMR_OUTPUT_NSTATE_ENABLE    /*!< Enable complementary output */
} TMR_OC_OUTPUT_NSTATE_T;

/**
 * @brief TMR_Output_Compare_Polarity
 */
typedef enum
{
    TMR_OC_POLARITY_HIGH,  /*!< Output Compare active high */
    TMR_OC_POLARITY_LOW    /*!< Output Compare active low */
} TMR_OC_POLARITY_T;

/**
 * @brief TMR_Output_Compare_N_Polarity
 */
typedef enum
{
    TMR_OC_NPOLARITY_HIGH,    /*!< Output Compare active high */
    TMR_OC_NPOLARITY_LOW      /*!< Output Compare active low */
} TMR_OC_NPOLARITY_T;

/**
 * @brief TMR_Output_Compare_Idle_State
 */
typedef enum
{
    TMR_OCIDLESTATE_RESET,  /*!< Reset output compare idle state */
    TMR_OCIDLESTATE_SET     /*!< Set output compare idle state */
} TMR_OC_IDLE_STATE_T;

/**
 * @brief TMR_Output_Compare_N_Idle_State
 */
typedef enum
{
    TMR_OCNIDLESTATE_RESET,  /*!< Reset output complementary idle state */
    TMR_OCNIDLESTATE_SET     /*!< Set output complementary idle state */
} TMR_OC_NIDLE_STATE_T;

/**
 * @brief TMR Input Capture Init structure definition
 */
typedef enum
{
    TMR_CHANNEL_1 = 0x0000,  /*!< Timer Channel 1 */
    TMR_CHANNEL_2 = 0x0004,  /*!< Timer Channel 2 */
    TMR_CHANNEL_3 = 0x0008,  /*!< Timer Channel 3 */
    TMR_CHANNEL_4 = 0x000C   /*!< Timer Channel 4 */
} TMR_CHANNEL_T;

/**
 * @brief    TMR ForcedAction
 */
typedef enum
{
    TMR_FORCEDACTION_INACTIVE = 0x04,  /*!< Force inactive level on OC1REF */
    TMR_FORCEDACTION_ACTIVE   = 0x05   /*!< Force active level on OC1REF */
} TMR_FORCED_ACTION_T;

/**
 * @brief    TMR Output_Compare_Preload_State
 */
typedef enum
{
    TMR_OC_PRELOAD_DISABLE,  /*!< Disable preload */
    TMR_OC_PRELOAD_ENABLE    /*!< Enable preload */
} TMR_OC_PRELOAD_T;

/**
 * @brief    TMR Output_Compare_Fast_State
 */
typedef enum
{
    TMR_OCFAST_DISABLE,  /*!< Disable fast output compare */
    TMR_OCFAST_ENABLE    /*!< Enable fast output compare */
} TMR_OCFAST_T;

/**
 * @brief    TMR Output_Compare_Clear_State
 */
typedef enum
{
    TMR_OCCLER_DISABLE,  /*!< Disable output compare clear */
    TMR_OCCLER_ENABLE    /*!< Enable output compare clear */
} TMR_OCCLER_T;

/**
 * @brief    TMR_OCReferenceClear Clear source
 */
typedef enum
{
    TMR_OCCS_ETRF,         /*!< Select ETRF as clear source */
    TMR_OCCS_OCREFCLR      /*!< Select OCREFCLR as clear source */
} TMR_OCCSEL_T;

/**
 * @brief TMR Input_Capture_Polarity
 */
typedef enum
{
    TMR_IC_POLARITY_RISING   = 0x00,  /*!< Rising edge */
    TMR_IC_POLARITY_FALLING  = 0x02,  /*!< Falling edge */
    TMR_IC_POLARITY_BOTHEDGE = 0x0A   /*!< Both rising and falling edge */
} TMR_IC_POLARITY_T;

/**
 * @brief TMR Input_Capture_Selection
 */
typedef enum
{
    TMR_IC_SELECTION_DIRECT_TI   = 0x01,  /*!< Input capture mapping in TI1 */
    TMR_IC_SELECTION_INDIRECT_TI = 0x02,  /*!< Input capture mapping in TI2 */
    TMR_IC_SELECTION_TRC         = 0x03   /*!< Input capture mapping in TRC */
} TMR_IC_SELECTION_T;

/**
 * @brief TMR_Input_Capture_Prescaler
 */
typedef enum
{
    TMR_ICPSC_DIV1 = 0x00,   /*!< No prescaler */
    TMR_ICPSC_DIV2 = 0x01,   /*!< Capture is done once every 2 events */
    TMR_ICPSC_DIV4 = 0x02,   /*!< capture is done once every 4 events */
    TMR_ICPSC_DIV8 = 0x03    /*!< capture is done once every 8 events */
} TMR_IC_PRESCALER_T;

/**
 * @brief    TMR_interrupt_sources
 */
typedef enum
{
    TMR_INT_UPDATE = 0x0001,  /*!< Timer update Interrupt source */
    TMR_INT_CH1    = 0x0002,  /*!< Timer Capture Compare 1 Interrupt source */
    TMR_INT_CH2    = 0x0004,  /*!< Timer Capture Compare 2 Interrupt source */
    TMR_INT_CH3    = 0x0008,  /*!< Timer Capture Compare 3 Interrupt source */
    TMR_INT_CH4    = 0x0010,  /*!< Timer Capture Compare 4 Interrupt source */
    TMR_INT_CCU    = 0x0020,  /*!< Timer Commutation Interrupt */
    TMR_INT_TRG    = 0x0040,  /*!< Timer Trigger Interrupt source */
    TMR_INT_BRK    = 0x0080   /*!< Timer Break Interrupt source */
} TMR_INT_T;

/**
 * @brief    TMR_event_sources
 */
typedef enum
{
    TMR_EVENT_UPDATE = 0x0001,  /*!< Timer update Interrupt source */
    TMR_EVENT_CH1    = 0x0002,  /*!< Timer Capture Compare 1 Event source */
    TMR_EVENT_CH2    = 0x0004,  /*!< Timer Capture Compare 2 Event source */
    TMR_EVENT_CH3    = 0x0008,  /*!< Timer Capture Compare 3 Event source */
    TMR_EVENT_CH4    = 0x0010,  /*!< Timer Capture Compare 4 Event source */
    TMR_EVENT_CCU    = 0x0020,  /*!< Timer Commutation Event source */
    TMR_EVENT_TRG    = 0x0040,  /*!< Timer Trigger Event source */
    TMR_EVENT_BRK    = 0x0080   /*!< Timer Break Event source */
} TMR_EVENT_T;

/**
 * @brief    TMR_interrupt_flag
 */
typedef enum
{
    TMR_INT_FLAG_UPDATE = 0x0001,  /*!< Timer update Interrupt source */
    TMR_INT_FLAG_CH1    = 0x0002,  /*!< Timer Capture Compare 1 Interrupt source */
    TMR_INT_FLAG_CH2    = 0x0004,  /*!< Timer Capture Compare 2 Interrupt source */
    TMR_INT_FLAG_CH3    = 0x0008,  /*!< Timer Capture Compare 3 Interrupt source */
    TMR_INT_FLAG_CH4    = 0x0010,  /*!< Timer Capture Compare 4 Interrupt source */
    TMR_INT_FLAG_CCU    = 0x0020,  /*!< Timer Commutation Interrupt source */
    TMR_INT_FLAG_TRG    = 0x0040,  /*!< Timer Trigger Interrupt source */
    TMR_INT_FLAG_BRK    = 0x0080   /*!< Timer Break Interrupt source */
} TMR_INT_FLAG_T;

/**
 * @brief    TMR Flag
 */
typedef enum
{
    TMR_FLAG_UPDATE  = 0x0001,  /*!< Timer update Flag */
    TMR_FLAG_CH1     = 0x0002,  /*!< Timer Capture Compare 1 Flag */
    TMR_FLAG_CH2     = 0x0004,  /*!< Timer Capture Compare 2 Flag */
    TMR_FLAG_CH3     = 0x0008,  /*!< Timer Capture Compare 3 Flag */
    TMR_FLAG_CH4     = 0x0010,  /*!< Timer Capture Compare 4 Flag */
    TMR_FLAG_CCU     = 0x0020,  /*!< Timer Commutation Flag */
    TMR_FLAG_TRG     = 0x0040,  /*!< Timer Trigger Flag */
    TMR_FLAG_BRK     = 0x0080,  /*!< Timer Break Flag (Only for TMR1 and TMR8) */
    TMR_FLAG_CH1OC   = 0x0200,  /*!< Timer Capture Compare 1 Repetition Flag */
    TMR_FLAG_CH2OC   = 0x0400,  /*!< Timer Capture Compare 2 Repetition Flag */
    TMR_FLAG_CH3OC   = 0x0800,  /*!< Timer Capture Compare 3 Repetition Flag */
    TMR_FLAG_CH4OC   = 0x1000   /*!< Timer Capture Compare 4 Repetition Flag */
} TMR_FLAG_T;

/**
 * @brief    TMR DMA Base Address
 */
typedef enum
{
    TMR_DMABASE_CTRL1   = 0x0000,  /*!< TMR CTRL1 DMA base address setup */
    TMR_DMABASE_CTRL2   = 0x0001,  /*!< TMR CTRL2 DMA base address setup */
    TMR_DMABASE_SMCTRL  = 0x0002,  /*!< TMR SMCTRL DMA base address setup */
    TMR_DMABASE_DIEN    = 0x0003,  /*!< TMR DIEN DMA base address setup */
    TMR_DMABASE_STS     = 0x0004,  /*!< TMR STS DMA base address setup */
    TMR_DMABASE_CEG     = 0x0005,  /*!< TMR CEG DMA base address setup */
    TMR_DMABASE_CCM1    = 0x0006,  /*!< TMR CCM1 DMA base address setup */
    TMR_DMABASE_CCM2    = 0x0007,  /*!< TMR CCM2 DMA base address setup */
    TMR_DMABASE_CHCTRL  = 0x0008,  /*!< TMR CHCTRL DMA base address setup */
    TMR_DMABASE_CNT     = 0x0009,  /*!< TMR CNT DMA base address setup */
    TMR_DMABASE_DIV     = 0x000A,  /*!< TMR DIV DMA base address setup */
    TMR_DMABASE_AUTORLD = 0x000B,  /*!< TMR AUTORLD DMA base address setup */
    TMR_DMABASE_REPCNT  = 0x000C,  /*!< TMR REPCNT DMA base address setup */
    TMR_DMABASE_CH1CC   = 0x000D,  /*!< TMR CH1CC DMA base address setup */
    TMR_DMABASE_CH2CC   = 0x000E,  /*!< TMR CH2CC DMA base address setup */
    TMR_DMABASE_CH3CC   = 0x000F,  /*!< TMR CH3CC DMA base address setup */
    TMR_DMABASE_CH4CC   = 0x0010,  /*!< TMR CH4CC DMA base address setup */
    TMR_DMABASE_BDT     = 0x0011,  /*!< TMR BDT DMA base address setup */
    TMR_DMABASE_DMAB    = 0x0012   /*!< TMR DMAB DMA base address setup */
} TMR_DMA_BASE_ADDERSS_T;

/**
 * @brief    TMR DMA Burst Lenght
 */
typedef enum
{
    TMR_DMA_BURSTLENGHT_1TRANSFER   = 0x0000,  /*!< Select TMR DMA burst Length 1 */
    TMR_DMA_BURSTLENGHT_2TRANSFERS  = 0x0100,  /*!< Select TMR DMA burst Length 2 */
    TMR_DMA_BURSTLENGHT_3TRANSFERS  = 0x0200,  /*!< Select TMR DMA burst Length 3 */
    TMR_DMA_BURSTLENGHT_4TRANSFERS  = 0x0300,  /*!< Select TMR DMA burst Length 4 */
    TMR_DMA_BURSTLENGHT_5TRANSFERS  = 0x0400,  /*!< Select TMR DMA burst Length 5 */
    TMR_DMA_BURSTLENGHT_6TRANSFERS  = 0x0500,  /*!< Select TMR DMA burst Length 6 */
    TMR_DMA_BURSTLENGHT_7TRANSFERS  = 0x0600,  /*!< Select TMR DMA burst Length 7 */
    TMR_DMA_BURSTLENGHT_8TRANSFERS  = 0x0700,  /*!< Select TMR DMA burst Length 8 */
    TMR_DMA_BURSTLENGHT_9TRANSFERS  = 0x0800,  /*!< Select TMR DMA burst Length 9 */
    TMR_DMA_BURSTLENGHT_10TRANSFERS = 0x0900,  /*!< Select TMR DMA burst Length 10 */
    TMR_DMA_BURSTLENGHT_11TRANSFERS = 0x0A00,  /*!< Select TMR DMA burst Length 11 */
    TMR_DMA_BURSTLENGHT_12TRANSFERS = 0x0B00,  /*!< Select TMR DMA burst Length 12 */
    TMR_DMA_BURSTLENGHT_13TRANSFERS = 0x0C00,  /*!< Select TMR DMA burst Length 13 */
    TMR_DMA_BURSTLENGHT_14TRANSFERS = 0x0D00,  /*!< Select TMR DMA burst Length 14 */
    TMR_DMA_BURSTLENGHT_15TRANSFERS = 0x0E00,  /*!< Select TMR DMA burst Length 15 */
    TMR_DMA_BURSTLENGHT_16TRANSFERS = 0x0F00,  /*!< Select TMR DMA burst Length 16 */
    TMR_DMA_BURSTLENGHT_17TRANSFERS = 0x1000,  /*!< Select TMR DMA burst Length 17 */
    TMR_DMA_BURSTLENGHT_18TRANSFERS = 0x1100,  /*!< Select TMR DMA burst Length 18 */
} TMR_DMA_BURST_LENGHT_T;

/**
 * @brief    TMR DMA Soueces
 */
typedef enum
{
    TMR_DMA_UPDATE    = 0x0100,  /*!< TMR update DMA souces */
    TMR_DMA_CH1       = 0x0200,  /*!< TMR Capture Compare 1 DMA souces */
    TMR_DMA_CH2       = 0x0400,  /*!< TMR Capture Compare 2 DMA souces */
    TMR_DMA_CH3       = 0x0800,  /*!< TMR Capture Compare 3 DMA souces */
    TMR_DMA_CH4       = 0x1000,  /*!< TMR Capture Compare 4 DMA souces */
    TMR_DMA_CCU       = 0x2000,  /*!< TMR Commutation DMA souces */
    TMR_DMA_TRG       = 0x4000   /*!< TMR Trigger DMA souces */
} TMR_DMA_SOUCES_T;

/**
 * @brief    TMR Internal_Trigger_Selection
 */
typedef enum
{
    TMR_TS_ITR0     = 0x00,  /*!< Internal Trigger 0 */
    TMR_TS_ITR1     = 0x01,  /*!< Internal Trigger 1 */
    TMR_TS_ITR2     = 0x02,  /*!< Internal Trigger 2 */
    TMR_TS_ITR3     = 0x03,  /*!< Internal Trigger 3 */
    TMR_TS_TI1F_ED  = 0x04,  /*!< TI1 Edge Detector */
    TMR_TS_TI1FP1   = 0x05,  /*!< Filtered Timer Input 1 */
    TMR_TS_TI2FP2   = 0x06,  /*!< Filtered Timer Input 2 */
    TMR_TS_ETRF     = 0x07   /*!< External Trigger input */
} TMR_INPUT_TRIGGER_SOURCE_T;

/**
 * @brief    TMR  The external Trigger Prescaler.
 */
typedef enum
{
    TMR_ExtTRGPSC_OFF   = 0x00,  /*!< ETRP Prescaler OFF */
    TMR_EXTTRGPSC_DIV2  = 0x01,  /*!< ETRP frequency divided by 2 */
    TMR_EXTTRGPSC_DIV4  = 0x02,  /*!< ETRP frequency divided by 4 */
    TMR_EXTTRGPSC_DIV8  = 0x03   /*!< ETRP frequency divided by 8 */
} TMR_EXTTRG_PRESCALER_T;

/**
 * @brief    TMR External_Trigger_Polarity
 */
typedef enum
{
    TMR_EXTTRGPOLARITY_INVERTED      = 0x01,  /*!< Active low or falling edge active */
    TMR_EXTTGRPOLARITY_NONINVERTED   = 0x00   /*!< Active high or rising edge active */
} TMR_EXTTRG_POLARITY_T;

/**
 * @brief    TMR OPMode
 */
typedef enum
{
    TMR_TRGOSOURCE_RESET,   /*!< Select reset signal as TRGO source  */
    TMR_TRGOSOURCE_ENABLE,  /*!< Select enable signal as TRGO source */
    TMR_TRGOSOURCE_UPDATE,  /*!< Select update signal as TRGO source */
    TMR_TRGOSOURCE_OC1,     /*!< Select OC1 signal as TRGO source */
    TMR_TRGOSOURCE_OC1REF,  /*!< Select OC1REF signal as TRGO source */
    TMR_TRGOSOURCE_OC2REF,  /*!< Select OC2REF signal as TRGO source */
    TMR_TRGOSOURCE_OC3REF,  /*!< Select OC3REF signal as TRGO source */
    TMR_TRGOSOURCE_OC4REF   /*!< Select OC4REF signal as TRGO source */
} TMR_TRGOSOURCE_T;

/**
 * @brief    TMR OPMode
 */
typedef enum
{
    TMR_SLAVEMODE_RESET     = 0x04,  /*!< Reset mode */
    TMR_SLAVEMODE_GATED     = 0x05,  /*!< Gated mode */
    TMR_SLAVEMODE_TRIGGER   = 0x06,  /*!< Trigger mode */
    TMR_SLAVEMODE_EXTERNALL = 0x07   /*!< External 1 mode */
} TMR_SLAVEMODE_T;

/**
 * @brief    TMR Encoder_Mode
 */
typedef enum
{
    TMR_ENCODER_MODE_TI1      = 0x01,  /*!< Encoder mode 1 */
    TMR_ENCODER_MODE_TI2      = 0x02,  /*!< Encoder mode 2 */
    TMR_ENCODER_MODE_TI12     = 0x03   /*!< Encoder mode 3 */
} TMR_ENCODER_MODE_T;

/**
 * @brief    TMR Remap Select
 */
typedef enum
{
    TMR_REMAP_GPIO      = 0x00,  /*!< TMR input is connected to GPIO */
    TMR_REMAP_RTC_CLK   = 0x01,  /*!< TMR input is connected to RTC clock */
    TMR_REMAP_HSEDiv32  = 0x02,  /*!< TMR input is connected to HSE clock/32 */
    TMR_REMAP_MCO       = 0x03   /*!< TMR input is connected to MCO */
} TMR_REMAP_T;

/**@} end of group TMR_Enumerations*/

/** @defgroup TMR_Structures Stuctures
  @{
*/

/**
  * @brief  TMR Time Base Init structure definition
  * @note   This sturcture is used with all TMRx.
  */
typedef struct
{
    uint16_t              div;                /*!< This must between 0x0000 and 0xFFFF */
    TMR_COUNTER_MODE_T    counterMode;        /*!< TMR counter mode selection */
    uint32_t              period;             /*!< This must between 0x0000 and 0xFFFF */
    TMR_CKD_T             clockDivision;      /*!< TMR clock division selection */
    uint8_t               repetitionCounter;  /*!< This must between 0x00 and 0xFF, only for TMR1 and TMR8. */
} TMR_TimeBase_T;

/**
 * @brief    TMR BDT structure definition
 */
typedef struct
{
    TMR_RMOS_STATE_T        RMOS_State;       /*!< TMR Specifies the Off-State selection used in Run mode selection */
    TMR_IMOS_STATE_T        IMOS_State;       /*!< TMR Closed state configuration in idle mode selection */
    TMR_LOCK_LEVEL_T        lockLevel;        /*!< TMR Protect mode configuration values selection */
    uint8_t                 deadTime;         /*!< Setup dead time */
    TMR_BREAK_STATE_T       breakState;       /*!< Setup TMR BRK state */
    TMR_BREAK_POLARITY_T    breakPolarity;    /*!< Setup TMR BRK polarity */
    TMR_AUTOMATIC_OUTPUT_T  automaticOutput;  /*!< Setup break input pin polarity */
} TMR_BDTInit_T;
/**
 * @brief    TMR Config struct definition
 */
typedef struct
{
    TMR_OC_MODE_T           OC_Mode;            /*!< Specifies the TMR mode. */

    TMR_OC_OUTPUT_STATE_T   OC_OutputState;     /*!< Specifies the TMR Output Compare state. */

    TMR_OC_OUTPUT_NSTATE_T  OC_OutputNState;    /*!< Specifies the TMR complementary Output Compare state.  @note This parameter is valid only for TMR1 and TMR8. */

    TMR_OC_POLARITY_T       OC_Polarity;        /*!<  Specifies the output polarity. */

    TMR_OC_NPOLARITY_T      OC_NPolarity;       /*!<  Specifies the complementary output polarity.  @note This parameter is valid only for TMR1 and TMR8. */

    TMR_OC_IDLE_STATE_T     OC_Idlestate;       /*!<  Specifies the TMR Output Compare pin state during Idle state. @note This parameter is valid only for TMR1 and TMR8. */

    TMR_OC_NIDLE_STATE_T    OC_NIdlestate;      /*!<  Specifies the TMR Output Compare pin state during Idle state. @note This parameter is valid only for TMR1 and TMR8. */

    uint16_t              Pulse;                /*!< Specifies the pulse value to be loaded into the Capture Compare Register. */

} TMR_OCConfig_T;

/**
 * @brief    TMR Input Capture Config struct definition
 */
typedef struct
{
    TMR_CHANNEL_T channel;          /*!<  Specifies the TMR channel. */

    TMR_IC_POLARITY_T ICpolarity;   /*!< Specifies the active edge of the input signal. */

    TMR_IC_SELECTION_T ICselection; /*!<  Specifies the input. */

    TMR_IC_PRESCALER_T ICprescaler; /*!<  Specifies the Input Capture Prescaler. */

    uint16_t  ICfilter;             /*!< Specifies the input capture filter. */

} TMR_ICConfig_T;

/**@} end of group TMR_Structures*/

/** @defgroup  TMR_Variables Variables
  @{
  */

/**@} end of group TMR_Variables */

/** @defgroup  TMR_Functions Functions
  @{
*/
/* TimeBase management */
void TMR_Reset(TMR_T* TMRx);
void TMR_ConfigTimeBase(TMR_T* TMRx, TMR_TimeBase_T* timeBaseConfig);
void TMR_ConfigTimeBaseStruct(TMR_TimeBase_T* timeBaseConfig);
void TMR_ConfigDIV(TMR_T* TMRx, uint16_t div, TMR_PRESCALER_RELOAD_T mode);
void TMR_ConfigCounterMode(TMR_T* TMRx, TMR_COUNTER_MODE_T mode);
void TMR_SetCounter(TMR_T* TMRx, uint32_t counter);
void TMR_SetAutoReload(TMR_T* TMRx, uint32_t autoReload);
uint32_t TMR_ReadCounter(TMR_T* TMRx);
uint32_t TMR_ReadDiv(TMR_T* TMRx);
void TMR_EnableNGUpdate(TMR_T* TMRx);
void TMR_DisableNGUpdate(TMR_T* TMRx);
void TMR_ConfigUPdateRequest(TMR_T* TMRx, TMR_UPDATE_SOURCE_T source);
void TMR_EnableAUTOReload(TMR_T* TMRx);
void TMR_DisableAUTOReload(TMR_T* TMRx);
void TMR_SetClockDivision(TMR_T* TMRx, TMR_CKD_T clockDivision);
void TMR_Enable(TMR_T* TMRx);
void TMR_Disable(TMR_T* TMRx);
void TMR_ConfigBDT(TMR_T* TMRx, TMR_BDTInit_T* structure);
void TMR_ConfigBDTStructInit(TMR_BDTInit_T* structure);

void TMR_EnablePWMOutputs(TMR_T* TMRx);
void TMR_DisablePWMOutputs(TMR_T* TMRx);

void TMR_OC1Config(TMR_T* TMRx, TMR_OCConfig_T* OCcongigStruct);
void TMR_OC2Config(TMR_T* TMRx, TMR_OCConfig_T* OCcongigStruct);
void TMR_OC3Config(TMR_T* TMRx, TMR_OCConfig_T* OCcongigStruct);
void TMR_OC4Config(TMR_T* TMRx, TMR_OCConfig_T* OCcongigStruct);
void TMR_OCConfigStructInit(TMR_OCConfig_T* OCcongigStruct);

void TMR_SelectOCxMode(TMR_T* TMRx, TMR_CHANNEL_T channel, TMR_OC_MODE_T mode);
void TMR_SelectSlaveMode(TMR_T* TMRx, TMR_SLAVEMODE_T mode);
void TMR_SelectOnePulseMode(TMR_T* TMRx, TMR_OPMODE_T OPMode);

void TMR_SetCompare1(TMR_T* TMRx, uint32_t compare);
void TMR_SetCompare2(TMR_T* TMRx, uint32_t compare);
void TMR_SetCompare3(TMR_T* TMRx, uint32_t compare);
void TMR_SetCompare4(TMR_T* TMRx, uint32_t compare);

void TMR_ForcedOC1Config(TMR_T* TMRx, TMR_FORCED_ACTION_T action);
void TMR_ForcedOC2Config(TMR_T* TMRx, TMR_FORCED_ACTION_T action);
void TMR_ForcedOC3Config(TMR_T* TMRx, TMR_FORCED_ACTION_T action);
void TMR_ForcedOC4Config(TMR_T* TMRx, TMR_FORCED_ACTION_T action);

void TMR_EnableCCPreload(TMR_T* TMRx);
void TMR_DisableCCPreload(TMR_T* TMRx);

void TMR_OC1PreloadConfig(TMR_T* TMRx, TMR_OC_PRELOAD_T OCPreload);
void TMR_OC2PreloadConfig(TMR_T* TMRx, TMR_OC_PRELOAD_T OCPreload);
void TMR_OC3PreloadConfig(TMR_T* TMRx, TMR_OC_PRELOAD_T OCPreload);
void TMR_OC4PreloadConfig(TMR_T* TMRx, TMR_OC_PRELOAD_T OCPreload);

void TMR_OC1FastConfit(TMR_T* TMRx, TMR_OCFAST_T OCFast);
void TMR_OC2FastConfit(TMR_T* TMRx, TMR_OCFAST_T OCFast);
void TMR_OC3FastConfit(TMR_T* TMRx, TMR_OCFAST_T OCFast);
void TMR_OC4FastConfit(TMR_T* TMRx, TMR_OCFAST_T OCFast);

void TMR_OC1PolarityConfig(TMR_T* TMRx, TMR_OC_POLARITY_T OCPolarity);
void TMR_OC1NPolarityConfig(TMR_T* TMRx, TMR_OC_NPOLARITY_T OCNPolarity);
void TMR_OC2PolarityConfig(TMR_T* TMRx, TMR_OC_POLARITY_T OCPolarity);
void TMR_OC2NPolarityConfig(TMR_T* TMRx, TMR_OC_NPOLARITY_T OCNPolarity);
void TMR_OC3PolarityConfig(TMR_T* TMRx, TMR_OC_POLARITY_T OCPolarity);
void TMR_OC3NPolarityConfig(TMR_T* TMRx, TMR_OC_NPOLARITY_T OCNPolarity);
void TMR_OC4PolarityConfig(TMR_T* TMRx, TMR_OC_POLARITY_T OCPolarity);

void TMR_SelectOCREFClear(TMR_T* TMRx, TMR_OCCSEL_T OCReferenceClear);

void TMR_EnableCCxChannel(TMR_T* TMRx, TMR_CHANNEL_T channel);
void TMR_DisableCCxChannel(TMR_T* TMRx, TMR_CHANNEL_T channel);
void TMR_EnableCCxNChannel(TMR_T* TMRx, TMR_CHANNEL_T channel);
void TMR_DisableCCxNChannel(TMR_T* TMRx, TMR_CHANNEL_T channel);

void TMR_EnableAUTOReload(TMR_T* TMRx);
void TMR_DisableAUTOReload(TMR_T* TMRx);
void TMR_EnableSelectCOM(TMR_T* TMRx);
void TMR_DisableSelectCOM(TMR_T* TMRx);

void TMR_ICConfig(TMR_T* TMRx, TMR_ICConfig_T* ICconfigstruct);
void TMR_ICConfigStructInit(TMR_ICConfig_T* ICconfigstruct);

void TMR_PWMConfig(TMR_T* TMRx, TMR_ICConfig_T* ICconfigstruct);

uint16_t TMR_ReadCaputer1(TMR_T* TMRx);
uint16_t TMR_ReadCaputer2(TMR_T* TMRx);
uint16_t TMR_ReadCaputer3(TMR_T* TMRx);
uint16_t TMR_ReadCaputer4(TMR_T* TMRx);

void TMR_SetIC1Prescal(TMR_T* TMRx, TMR_IC_PRESCALER_T prescaler);
void TMR_SetIC2Prescal(TMR_T* TMRx, TMR_IC_PRESCALER_T prescaler);
void TMR_SetIC3Prescal(TMR_T* TMRx, TMR_IC_PRESCALER_T prescaler);
void TMR_SetIC4Prescal(TMR_T* TMRx, TMR_IC_PRESCALER_T prescaler);

/* Interrupts and Event management functions */
void TMR_EnableInterrupt(TMR_T* TMRx, uint16_t interrupt);
void TMR_DisableInterrupt(TMR_T* TMRx, uint16_t interrupt);
void TMR_GenerateEvent(TMR_T* TMRx, uint16_t event);

uint16_t TMR_ReadStatusFlag(TMR_T* TMRx, TMR_FLAG_T flag);
void TMR_ClearStatusFlag(TMR_T* TMRx, uint16_t flag);
uint16_t TMR_ReadIntFlag(TMR_T* TMRx,  TMR_INT_FLAG_T flag);
void TMR_ClearIntFlag(TMR_T* TMRx,  uint16_t flag);

void TMR_ConfigDMA(TMR_T* TMRx, TMR_DMA_BASE_ADDERSS_T address, TMR_DMA_BURST_LENGHT_T lenght);
void TMR_EnableDMASoure(TMR_T* TMRx, uint16_t souces);
void TMR_DisableDMASoure(TMR_T* TMRx, uint16_t souces);
void TMR_EnableCCDMA(TMR_T* TMRx);
void TMR_DisableCCDMA(TMR_T* TMRx);

/* Clocks management */
void TMR_ConfigInternalClock(TMR_T* TMRx);
void TMR_ConfigITRxExternalClock(TMR_T* TMRx, TMR_INPUT_TRIGGER_SOURCE_T input);
void TMR_ConfigTIxExternalClock(TMR_T* TMRx, TMR_INPUT_TRIGGER_SOURCE_T input,
                                TMR_IC_POLARITY_T ICpolarity, uint16_t ICfilter);
void TMR_ConfigExternalClockMode1(TMR_T* TMRx, TMR_EXTTRG_PRESCALER_T prescaler,
                                  TMR_EXTTRG_POLARITY_T polarity, uint16_t filter);
void TMR_ConfigExternalClockMode2(TMR_T* TMRx, TMR_EXTTRG_PRESCALER_T prescaler,
                                  TMR_EXTTRG_POLARITY_T polarity, uint16_t filter);
/* Synchronization management */
void TMR_SelectInputTrigger(TMR_T* TMRx, TMR_INPUT_TRIGGER_SOURCE_T input);
void TMR_SelectOutputTrigger(TMR_T* TMRx, TMR_TRGOSOURCE_T source);
void TMR_EnableMasterSlaveMode(TMR_T* TMRx);
void TMR_DisableMasterSlaveMode(TMR_T* TMRx);
void TMR_ConfigExternalTrigger(TMR_T* TMRx, TMR_EXTTRG_PRESCALER_T prescaler,
                               TMR_EXTTRG_POLARITY_T polarity, uint16_t filter);

/* Specific interface management */
void TMR_ConfigEncodeInterface(TMR_T* TMRx, TMR_ENCODER_MODE_T encodeMode, TMR_IC_POLARITY_T IC1Polarity,
                               TMR_IC_POLARITY_T IC2Polarity);
void TMR_EnableHallSensor(TMR_T* TMRx);
void TMR_DisableHallSensor(TMR_T* TMRx);

/* Specific remapping management */
void TMR_ConfigRemap(TMR_T* TMRx, TMR_REMAP_T remap);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_TMR_H */

/**@} end of group TMR_Functions */
/**@} end of group TMR_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
