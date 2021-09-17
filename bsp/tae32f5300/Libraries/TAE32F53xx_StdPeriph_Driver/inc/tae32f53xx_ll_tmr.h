/**
  ******************************************************************************
  * @file    tae32f53xx_ll_tmr.h
  * @author  MCD Application Team
  * @brief   Header for TMR LL module driver
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32F53XX_LL_TMR_H_
#define _TAE32F53XX_LL_TMR_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup TMR_LL
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup TMR_LL_Exported_Types TMR LL Exported Types
  * @brief    TMR LL Exported Types
  * @{
  */

/**
  * @brief TMR Continuous Mode
  */
typedef enum {
    TMR_CONTINUOUS_MODE_ENABLE          = 0x00000000U,      /*!< TMR performed in Continuous counting mode  */
    TMR_CONTINUOUS_MODE_DISABLE         = TMR_CR_MS,        /*!< TMR performed in Single counting mode      */
} TMR_ContinuousETypeDef;

/**
  * @brief TMR Update Event Enable
  */
typedef enum {
    TMR_UPDATE_ENABLE                  = 0x00000000U,       /*!< Update event generation enabled    */
    TMR_UPDATE_DISABLE                 = TMR_CR_UDIS,       /*!< Update event generation disabled   */
} TMR_UpdateETypeDef;

/**
  * @brief TMR_Update_Request_Source TMR Update Request Source
  */
typedef enum {
    TMR_UPDATE_SOURCE_REGULAR          = 0x00000000U,   /*!< Counter overflow or Setting the UG bit generates an update request */
    TMR_UPDATE_SOURCE_COUNTER          = TMR_CR_URS,    /*!< Only counter overflow generates an update request                  */
} TMR_UpdateSrcETypeDef;

/**
  * @brief TMR Auto-Reload Preload
  */
typedef enum {
    TMR_AUTORELOAD_PRELOAD_DISABLE     = 0x00000000U,      /*!< Disable auto-reload preload feature    */
    TMR_AUTORELOAD_PRELOAD_ENABLE      = TMR_CR_ARPE,      /*!< Enable auto-reload preload feature     */
} TMR_AutoReloadETypeDef;

/**
  * @brief TMR Clock Souce
  */
typedef enum {
    TMR_CLKSOURCE_INTERNAL             = TMR_CR_CKSRC_0,   /*!< Internal clock source                              */
    TMR_CLKSOURCE_ETR_RISING           = TMR_CR_CKSRC_1,   /*!< External clock source rising edge                  */
    TMR_CLKSOURCE_ETR_FALLING          = TMR_CR_CKSRC_2,   /*!< External clock source falling edge                 */
    TMR_CLKSOURCE_ETR_BOTHEDGE         = TMR_CR_CKSRC_3,   /*!< External clock source both rising and falling edge */
} TMR_ClkSrcETypeDef;

/**
  * @brief TMR PWM Wave Export
  */
typedef enum {
    TMR_EXT_PWM_WAVE_DISABLE           = 0x00000000U,     /*!< Disable the export of the PWM Wave */
    TMR_EXT_PWM_WAVE_ENABLE            = TMR_ETER_PWMOE,  /*!< Enable the export of the PWM Wave  */
} TMR_Ext_PWMETypeDef;

/**
  * @brief TMR Capture Compare Event Trigger Export
  */
typedef enum {
    TMR_EXT_CC_TRIGGER_DISABLE         = 0x00000000U,     /*!< Disable the export of the Capture Compare Trigger  */
    TMR_EXT_CC_TRIGGER_ENABLE          = TMR_ETER_CCTE,   /*!< Enable the export of the Capture Compare Trigger   */
} TMR_Ext_CCETypeDef;

/**
  * @brief TMR TRGO Trigger Export
  */
typedef enum {
    TMR_EXT_TRGO_TRIGGER_DISABLE       = 0x00000000U,  /*!< Disable the export of the TRGO signal (source from Update Event) Trigger   */
    TMR_EXT_TRGO_TRIGGER_ENABLE        = TMR_ETER_UTE, /*!< Enable the export of the TRGO signal (source from Update Event) Trigger    */
} TMR_Ext_TRGOETypeDef;

/**
  * @brief TMR Event Source
  */
typedef enum {
    TMR_EVENTSOURCE_UG                 = TMR_EGR_UG,   /*!< Reinitialize the counter and generates an update of the registers  */
    TMR_EVENTSOURCE_CCG                = TMR_EGR_CCG,  /*!< A capture/compare event is generated                               */
} TMR_EventSRCETypeDef;

/** @brief TMR Input Capture Selection
  */
typedef enum {
    TMR_ICSELECTION_TMR0               = TMR_CCCR_ICSRS_0,  /*!< TMR input capture source TMR0 io (specific to (LS)TMR0/1/2/3). */
    TMR_ICSELECTION_TMR4               = TMR_CCCR_ICSRS_0,  /*!< TMR input capture source TMR4 io (specific to (HS)TMR4/5/6/7). */

    TMR_ICSELECTION_TMR1               = TMR_CCCR_ICSRS_1,  /*!< TMR input capture source TMR1 io (specific to (LS)TMR0/1/2/3). */
    TMR_ICSELECTION_TMR5               = TMR_CCCR_ICSRS_1,  /*!< TMR input capture source TMR5 io (specific to (HS)TMR4/5/6/7). */

    TMR_ICSELECTION_TMR2               = TMR_CCCR_ICSRS_2,  /*!< TMR input capture source TMR2 io (specific to (LS)TMR0/1/2/3). */
    TMR_ICSELECTION_TMR6               = TMR_CCCR_ICSRS_2,  /*!< TMR input capture source TMR6 io (specific to (HS)TMR4/5/6/7). */

    TMR_ICSELECTION_TMR3               = TMR_CCCR_ICSRS_3,  /*!< TMR input capture source TMR3 io (specific to (LS)TMR0/1/2/3). */
    TMR_ICSELECTION_TMR7               = TMR_CCCR_ICSRS_3,  /*!< TMR input capture source TMR7 io (specific to (HS)TMR4/5/6/7). */

    TMR_ICSELECTION_CMP0               = TMR_CCCR_ICSRS_4,  /*!< The internal CMP0 output single
                                                                 will be selected as the input source of LSTMR or HSTMR         */

    TMR_ICSELECTION_CMP1               = TMR_CCCR_ICSRS_5,  /*!< The internal CMP1 output single
                                                                 will be selected as the input source of LSTMR or HSTMR         */

    TMR_ICSELECTION_CMP2               = TMR_CCCR_ICSRS_6,  /*!< The internal CMP2 output single
                                                                 will be selected as the input source of LSTMR or HSTMR         */

    TMR_ICSELECTION_CMP3               = TMR_CCCR_ICSRS_7,  /*!< The internal CMP3 output single
                                                                 will be selected as the input source of LSTMR or HSTMR         */
} TMR_ICSelETypeDef;

/**
  * @brief  TMR Input Capture Polarity
  */
typedef enum {
    TMR_ICPOLARITY_RISING             = 0x00000000U,     /*!< Capture triggered by rising edge on timer input                    */
    TMR_ICPOLARITY_FALLING            = TMR_CCCR_CCP_0,  /*!< Capture triggered by falling edge on timer input                   */
    TMR_ICPOLARITY_BOTHEDGE           = TMR_CCCR_CCP_1,  /*!< Capture triggered by both rising and falling edges on timer input  */
} TMR_ICPolarityETypeDef;

/**
  * @brief TMR Output Compare and PWM Modes
  */
typedef enum {
    TMR_OCMODE_FROZEN                 = TMR_CCCR_OCM_0,  /*!< Frozen             */
    TMR_OCMODE_ACTIVE                 = TMR_CCCR_OCM_1,  /*!< active on match    */
    TMR_OCMODE_INACTIVE               = TMR_CCCR_OCM_2,  /*!< inactive on match  */
    TMR_OCMODE_TOGGLE                 = TMR_CCCR_OCM_3,  /*!< Toggle             */
    TMR_OCMODE_FORCED_INACTIVE        = TMR_CCCR_OCM_4,  /*!< Force inactive     */
    TMR_OCMODE_FORCED_ACTIVE          = TMR_CCCR_OCM_5,  /*!< Force active       */
    TMR_OCMODE_PWM1                   = TMR_CCCR_OCM_6,  /*!< PWM mode 1         */
    TMR_OCMODE_PWM2                   = TMR_CCCR_OCM_7,  /*!< PWM mode 2         */
} TMR_OCModeETypeDef;

/**
  * @brief TMR_OCPreload_Enable TMR OCPreload Enable
  */
typedef enum {
    TMR_OCPRELOAD_DISABLE             = 0x00000000U,     /*!< TMR OCPreload Disable  */
    TMR_OCPRELOAD_ENABLE              = TMR_CCCR_OCPE,   /*!< TMR OCPreload Enable   */
} TMR_OCPreloadETypeDef;

/**
  * @brief TMR Complementary Output Compare Polarity
  */
typedef enum {
    TMR_OCPOLARITY_HIGH               = 0x00000000U,     /*!< Output Compare polarity active high    */
    TMR_OCPOLARITY_LOW                = TMR_CCCR_CCP_0,  /*!< Output Compare polarity active low     */
} TMR_OCPolarityETypeDef;

/**
  * @brief Timer Base Unit Initialization Structure definition
  * @note  Please notice that TMR can enable either Input Capture mode or Output Compare mode.
  */
typedef struct __TMR_TB_InitTypeDef {
    TMR_ClkSrcETypeDef ClockSource;             /*!< Specifies the Clock Source.                                    */

    uint32_t Prescaler;                         /*!< Specifies the prescaler value used to divide the TMR clock.
                                                   This parameter can be a number in range of:
                                                   For low-speed timer(TMR0/1/2/3): from Min 0x0 to Max 0x0000FFFF
                                                   For high-speed timer(TMR4/5/6/7): from Min 0x0 to Max 0xFFFFFFFF */

    uint32_t StartValue;                        /*!< Specifies the timer counter start value.
                                                   This parameter can be a number in range of:
                                                   For low-speed timer(TMR0/1/2/3): from Min 0x0 to Max 0x0000FFFF
                                                   For high-speed timer(TMR4/5/6/7): from Min 0x0 to Max 0xFFFFFFFF */

    uint32_t EndValue;                          /*!< Specifies the timer counter end value.
                                                   This parameter can be a number in range of:
                                                   For low-speed timer(TMR0/1/2/3): from Min 0x0 to Max 0x0000FFFF
                                                   For high-speed timer(TMR4/5/6/7): from Min 0x0 to Max 0xFFFFFFFF */

    TMR_ContinuousETypeDef ContinuousMode;      /*!< Specifies the timer continuous mode enable or disable.         */

    TMR_AutoReloadETypeDef AutoReloadPreload;   /*!< Specifies the auto-reload preload.                             */

    TMR_UpdateETypeDef UpdateEnable;            /*!< Specifies the Update event enable or not.                      */

    TMR_UpdateSrcETypeDef UpdateSource;         /*!< Specifies the Update request Source                            */
} TMR_TB_InitTypeDef;

/**
  * @brief Timer Input Capture Initialization Structure definition
  * @note  Please notice that TMR can enable either Input Capture mode or Output Compare mode.
  */
typedef struct __TMR_IC_InitTypeDef {
    LL_FuncStatusETypeDef ICEnable;     /*!< Specifies enable the Input Capture feature or not.
                                             This parameter can be ENABLE or DISABLE                                */

    TMR_ICPolarityETypeDef ICPolarity;  /*!< Specifies the active edge of the input signal.                         */

    TMR_ICSelETypeDef    ICSelection;   /*!< Specifies the input source to be used.                                 */

    uint32_t             ICFilter;      /*!< Specifies the input capture filter.
                                             This parameter can be a number between 0x0 and 0xFF                    */
} TMR_IC_InitTypeDef;

/**
  * @brief Timer Output Compare Initialization Structure definition
  * @note  Please notice that TMR can enable either Input Capture mode or Output Compare mode.
  */
typedef struct __TMR_OC_InitTypeDef {
    LL_FuncStatusETypeDef  OCEnable;    /*!< Specifies enable the Output Compare feature or not.
                                             This parameter can be ENABLE or DISABLE                                */

    TMR_OCPolarityETypeDef OCPolarity;  /*!< Specifies the output polarity.                                         */

    TMR_OCPreloadETypeDef  OCPreload;   /*!< Timer Output Compare Preload Enable                                    */

    TMR_OCModeETypeDef     OCMode;      /*!< Specifies the TMR mode.                                                */

    uint32_t               OCValue;     /*!< Specifies the compare value which loaded into Capture Compare Register.
                                             This parameter can be a number in range of:
                                               For low-speed timer(TMR0/1/2/3): from Min 0x0 to Max 0x0000FFFF
                                               For high-speed timer(TMR4/5/6/7): from Min 0x0 to Max 0xFFFFFFFF     */
} TMR_OC_InitTypeDef;

/**
  * @brief Timer Export Trigger Initialization Structure definition
  */
typedef struct __TMR_EXT_InitTypeDef {
    LL_FuncStatusETypeDef ExtEnable;    /*!< Specifies enable the Export Event Trigger feature or not.
                                             This parameter can be ENABLE or DISABLE                                                */

    TMR_Ext_PWMETypeDef  ExtPWMWave;    /*!< Specifies PWM Wave (output compare) export to internal signal or not.                  */

    TMR_Ext_CCETypeDef   ExtCCTrigger;  /*!< Specifies Capture Compare Trigger Event export to internal signal or not.              */

    TMR_Ext_TRGOETypeDef ExtTRGOTrigger;/*!< Specifies TMR TRGO signal (source from Update Event) export to internal signal or not. */
} TMR_EXT_InitTypeDef;

/**
  * @brief Timer Initialization Structure definition
  * @note  Please notice that TMR can be configured to either Input Capture mode or Output Compare mode.
  *        Witch means that either ICEnable or OCEnable in the Initialization Structure can be enable the feature.
  */
typedef struct __TMR_InitTypeDef {
    TMR_TB_InitTypeDef  TBInit;         /*!< Timer Base Unit Initialization Structure definition                    */

    TMR_IC_InitTypeDef  ICInit;         /*!< Timer Input Capture Initialization Structure definition                */

    TMR_OC_InitTypeDef  OCInit;         /*!< Timer Output Compare Initialization Structure                          */

    TMR_EXT_InitTypeDef ExtInit;        /*!< Timer Export Event Trigger feature Initialization Structure            */
} TMR_InitTypeDef;

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup TMR_LL_Exported_Constants TMR LL Exported Constants
  * @brief    TMR LL Exported Constants
  * @{
  */

/** @defgroup TMR_Interrupt_definition  TMR Interrupt Definition
  * @{
  */
#define TMR_IT_UIE                          TMR_CR_UIE      /*!< Update interrupt           */
#define TMR_IT_OVIE                         TMR_CR_OVIE     /*!< Counter Overflow interrupt */
/**
  * @}
  */

/** @defgroup TMR_CC_Interrupt_definition  TMR Capture/Compare Interrupt Definition
  * @{
  */
#define TMR_IT_ICIE                         TMR_CCCR_ICIE   /*!< Input Capture interrupt                */
#define TMR_IT_ICOIE                        TMR_CCCR_ICOIE  /*!< Input Capture OverCapture interrupt    */
#define TMR_IT_OCIE                         TMR_CCCR_OCIE   /*!< Output Compare Match interrupt         */
/**
  * @}
  */

/** @defgroup TMR_Flag_definition TMR Flag Definition
  * @{
  */
#define TMR_FLAG_OVIF                       TMR_ISR_OVIF    /*!< Timer Counter Overflow Interrupt Flag          */
#define TMR_FLAG_ICOIF                      TMR_ISR_ICOIF   /*!< Timer Input Capture OverCapture Interrupt Flag */
#define TMR_FLAG_ICIF                       TMR_ISR_ICIF    /*!< Timer Input Capture Interrupt Flag             */
#define TMR_FLAG_OCIF                       TMR_ISR_OCIF    /*!< Timer Output Compare Interrupt Flag            */
#define TMR_FLAG_UIF                        TMR_ISR_UIF     /*!< Timer Counter Update Interrupt Flag            */
/**
  * @}
  */

/** @defgroup TMR_Sync_definition Timer Group synchronization Definition
  * @{
  */
#define TMRGRP_SYNC_TMR0                    TMRGRP_SYNC0EN     /*!< Select TMR0(specific to TMRGRP0)       */
#define TMRGRP_SYNC_TMR4                    TMRGRP_SYNC0EN     /*!< Select TMR4(specific to TMRGRP1)       */

#define TMRGRP_SYNC_TMR1                    TMRGRP_SYNC1EN     /*!< Select TMR1(specific to TMRGRP0)       */
#define TMRGRP_SYNC_TMR5                    TMRGRP_SYNC1EN     /*!< Select TMR5(specific to TMRGRP1)       */

#define TMRGRP_SYNC_TMR2                    TMRGRP_SYNC2EN     /*!< Select TMR2(specific to TMRGRP0)       */
#define TMRGRP_SYNC_TMR6                    TMRGRP_SYNC2EN     /*!< Select TMR6(specific to TMRGRP1)       */

#define TMRGRP_SYNC_TMR3                    TMRGRP_SYNC3EN     /*!< Select TMR2(specific to TMRGRP0)       */
#define TMRGRP_SYNC_TMR7                    TMRGRP_SYNC3EN     /*!< Select TMR6(specific to TMRGRP1)       */

#define TMRGRP_SYNC_ALL                     TMRGRP_SYNCALLEN   /*!< Select all TMRs in TMRGRPx(x = 0 or 1) */
/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup TMR_LL_Exported_Macros TMR LL Exported Macros
  * @brief    TMR LL Exported Macros
  * @{
  */

/**
  * @brief  Enable TMR Base Unit on runtime
  * @param  __INSTANCE__ TMR peripheral
  * @return None
  */
#define __LL_TMR_ENABLE(__INSTANCE__)                               SET_BIT((__INSTANCE__)->CR, TMR_CR_CEN)

/**
  * @brief  Disable TMR Base Unit on runtime
  * @param  __INSTANCE__ TMR peripheral
  * @return None
  */
#define __LL_TMR_DISABLE(__INSTANCE__)                              CLEAR_BIT((__INSTANCE__)->CR, TMR_CR_CEN)

/**
  * @brief  Enable TMR Capture/Compare feature on runtime
  * @param  __INSTANCE__ TMR peripheral
  * @return None
  */
#define __LL_TMR_CC_ENABLE(__INSTANCE__)                            SET_BIT((__INSTANCE__)->CCCR, TMR_CCCR_CCE)

/**
  * @brief  Disable TMR Capture/Compare feature on runtime
  * @param  __INSTANCE__ TMR peripheral
  * @return None
  */
#define __LL_TMR_CC_DISABLE(__INSTANCE__)                           CLEAR_BIT((__INSTANCE__)->CCCR, TMR_CCCR_CCE)


/**
  * @brief  Enable the specified TMR Basic Unit Interrupt
  * @param  __INSTANCE__ TMR peripheral
  * @param  __INTERRUPT__  specifies the TMR base unit interrupt source to enable.
  *         This parameter can be any combination of @ref TMR_Interrupt_definition:
  *             @arg TMR_IT_UIE: Update interrupt
  *             @arg TMR_IT_OVIE: Counter Overflow interrupt
  * @return None
  */
#define __LL_TMR_IT_ENABLE(__INSTANCE__, __INTERRUPT__)             SET_BIT((__INSTANCE__)->CR, (__INTERRUPT__))

/**
  * @brief  Disable the specified TMR Basic Unit Interrupt
  * @param  __INSTANCE__ TMR peripheral
  * @param  __INTERRUPT__  specifies the TMR base unit interrupt source to disable.
  *          This parameter can be any combination of @ref TMR_Interrupt_definition:
  *             @arg TMR_IT_UIE: Update interrupt
  *             @arg TMR_IT_OVIE: Counter Overflow interrupt
  * @return None
  */
#define __LL_TMR_IT_DISABLE(__INSTANCE__, __INTERRUPT__)            CLEAR_BIT((__INSTANCE__)->CR, (__INTERRUPT__))

/**
  * @brief  Check whether the specified TMR Basic Unit interrupt source is set or not.
  * @param  __INSTANCE__ TMR peripheral
  * @param  __INTERRUPT__ specifies the TMR interrupt source to check.
  *          This parameter can be any combination of @ref TMR_Interrupt_definition:
  *             @arg TMR_IT_UIE: Update interrupt
  *             @arg TMR_IT_OVIE: Counter Overflow interrupt
  * @return The state of __INTERRUPT__ (SET or RESET).
  */
#define __LL_TMR_IT_CHECK_SOURCE(__INSTANCE__, __INTERRUPT__)       ((READ_BIT((__INSTANCE__)->CR, (__INTERRUPT__)) \
                                                                      == (__INTERRUPT__)) ? SET : RESET)

/**
  * @brief  Enable the specified Capture/Compare Interrupt
  * @param  __INSTANCE__ TMR peripheral
  * @param  __INTERRUPT__ specifies the TMR Capture/Compare interrupt source to enable.
  *         This parameter can be any combination of @ref TMR_CC_Interrupt_definition:
  *             @arg TMR_IT_ICIE: Input Capture interrupt
  *             @arg TMR_IT_ICOIE: Input Capture OverCapture interrupt
  *             @arg TMR_IT_OCIE: Output Compare Match interrupt
  * @return None
  */
#define __LL_TMR_CC_IT_ENABLE(__INSTANCE__, __INTERRUPT__)          SET_BIT((__INSTANCE__)->CCCR, (__INTERRUPT__))

/**
  * @brief  Disable Input Capture Interrupt
  * @param  __INSTANCE__ TMR peripheral
  * @param  __INTERRUPT__ specifies the TMR Capture/Compare interrupt source to disable.
  *         This parameter can be any combination of @ref TMR_CC_Interrupt_definition:
  *             @arg TMR_IT_ICIE: Input Capture interrupt
  *             @arg TMR_IT_ICOIE: Input Capture OverCapture interrupt
  *             @arg TMR_IT_OCIE: Output Compare Matched interrupt
  * @return None
  */
#define __LL_TMR_CC_IT_DISABLE(__INSTANCE__, __INTERRUPT__)         CLEAR_BIT((__INSTANCE__)->CCCR, (__INTERRUPT__))


/**
  * @brief  Check whether the specified TMR Capture/Compare interrupt source is set or not.
  * @param  __INSTANCE__ TMR peripheral
  * @param  __INTERRUPT__ specifies the TMR Capture/Compare interrupt source to check.
  *         This parameter can be any combination of @ref TMR_CC_Interrupt_definition:
  *             @arg TMR_IT_ICIE: Input Capture interrupt
  *             @arg TMR_IT_ICOIE: Input Capture OverCapture interrupt
  *             @arg TMR_IT_OCIE: Output Compare Matched interrupt
  * @return he state of __INTERRUPT__ (SET or RESET).
  */
#define __LL_TMR_CC_IT_CHECK_SOURCE(__INSTANCE__, __INTERRUPT__)    \
        ((READ_BIT((__INSTANCE__)->CCCR, (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/**
  * @brief  Check whether the specified TMR interrupt flag is set or not.
  * @param  __INSTANCE__ TMR peripheral.
  * @param  __FLAG__  specifies the TMR flags to check.
  *         This parameter can be any combination of @ref TMR_Flag_definition:
  *             @arg TMR_FLAG_OVIF:     Counter Overflow Interrupt Flag
  *             @arg TMR_FLAG_ICOIF:    Input Capture OverCapture Interrupt Flag
  *             @arg TMR_FLAG_ICIF:     Input Capture Interrupt Flag
  *             @arg TMR_FLAG_OCIF:     Output Compare Interrupt Flag
  *             @arg TMR_FLAG_UIF:      Counter Update Interrupt Flag
  * @return The state of __FLAG__ (SET or RESET).
  */
#define __LL_TMR_GET_FLAG(__INSTANCE__, __FLAG__)                   \
        ((READ_BIT((__INSTANCE__)->ISR, (__FLAG__)) == (__FLAG__)) ? SET : RESET)

/**
  * @brief  Clear the specified TMR interrupt flags
  * @param  __INSTANCE__ TMR peripheral
  * @param  __FLAG__ specifies the TMR flags to clear.
  *         This parameter can be any combination of @ref TMR_Flag_definition:
  *             @arg TMR_FLAG_OVIF:     Counter Overflow Interrupt Flag
  *             @arg TMR_FLAG_ICOIF:    Input Capture OverCapture Interrupt Flag
  *             @arg TMR_FLAG_ICIF:     Input Capture Interrupt Flag
  *             @arg TMR_FLAG_OCIF:     Output Compare Interrupt Flag
  *             @arg TMR_FLAG_UIF:      Counter Update Interrupt Flag
  * @return None
  */
#define __LL_TMR_CLEAR_FLAG(__INSTANCE__, __FLAG__)                 WRITE_REG((__INSTANCE__)->ISR, (__FLAG__))

/**
  * @brief  Enable TMR Auto-Reload feature
  * @param  __INSTANCE__ TMR peripheral
  * @return None
  */
#define __LL_TMR_AUTORELOAD_ENABLE(__INSTANCE__)                    SET_BIT((__INSTANCE__)->CR, TMR_CR_ARPE)

/**
  * @brief  Disable TMR Auto-Reload feature
  * @param  __INSTANCE__ TMR peripheral
  * @return None
  */
#define __LL_TMR_AUTORELOAD_DISABLE(__INSTANCE__)                   CLEAR_BIT((__INSTANCE__)->CR, TMR_CR_ARPE)

/**
  * @brief  Enable TMR Output Compare Preload feature
  * @param  __INSTANCE__ TMR peripheral
  * @return None
  */
#define __LL_TMR_OC_PRELOAD_ENABLE(__INSTANCE__)                    SET_BIT((__INSTANCE__)->CCCR, TMR_CCCR_OCPE)

/**
  * @brief  Disable TMR Output Compare Preload feature
  * @param  __INSTANCE__ TMR peripheral
  * @return None
  */
#define __LL_TMR_OC_PRELOAD_DISABLE(__INSTANCE__)                   CLEAR_BIT((__INSTANCE__)->CCCR, TMR_CCCR_OCPE)

/**
  * @brief  Enable TMR Update event (UDIS)
  * @param  __INSTANCE__ TMR peripheral
  * @return None
  */
#define __LL_TMR_UPDATE_ENABLE(__INSTANCE__)                        CLEAR_BIT((__INSTANCE__)->CR, TMR_CR_UDIS)

/**
  * @brief  Disable TMR Update event (UDIS)
  * @param  __INSTANCE__ TMR peripheral
  * @return None
  */
#define __LL_TMR_UPDATE_DISABLE(__INSTANCE__)                       SET_BIT((__INSTANCE__)->CR, TMR_CR_UDIS)

/**
  * @brief  Selection of the Update Request Source (URS) bit of the TMRx_CR register.
  * @param  __INSTANCE__ TMR peripheral
  * @param  __SOURCE__ specifies the Update Request Source
  *         This parameter can be one of the following values in @ref TMR_Update_Request_Source:
  *           @arg TMR_UPDATE_SOURCE_REGULAR: Counter overflow or Setting the UG bit generates an update request
  *           @arg TMR_UPDATE_SOURCE_COUNTER: Only counter overflow generates an update request
  * @note   To generate the update request, Update event should be enabled(reset UDIS bit in TMRx_CR register).
  * @return None
  */
#define __LL_TMR_UPDATE_SOURCE(__INSTANCE__, __SOURCE__)            MODIFY_REG((__INSTANCE__)->CR, TMR_CR_URS_Msk, (__SOURCE__))

/**
  * @brief  Set the TMR Prescaler on runtime.
  * @param  __INSTANCE__ TMR peripheral
  * @param  __PRESC__ specifies the Prescaler new value.
  * @retval None
  */
#define __LL_TMR_SET_PRESCALER(__INSTANCE__, __PRESC__)             WRITE_REG((__INSTANCE__)->PSCR, (__PRESC__))

/**
  * @brief  Get the TMR Prescaler on runtime.
  * @param  __INSTANCE__ TMR peripheral
  * @retval 16-bit or 32-bit value of the timer prescaler register (TMRx_PSCR)
  */
#define __LL_TMR_GET_PRESCALER(__INSTANCE__)                        READ_REG((__INSTANCE__)->PSCR)

/**
  * @brief  Set the TMR Start value on runtime.
  * @param  __INSTANCE__ TMR peripheral
  * @param  __START__ specifies the new starting value.
  * @retval None
  */
#define __LL_TMR_SET_START_VAL(__INSTANCE__, __START__)             WRITE_REG((__INSTANCE__)->CSVR, (__START__))

/**
  * @brief  Get the TMR Start value on runtime.
  * @param  __INSTANCE__ TMR peripheral
  * @retval 16-bit or 32-bit value of the timer start value register (TMRx_CSVR)
  */
#define __LL_TMR_GET_START_VAL(__INSTANCE__)                        READ_REG((__INSTANCE__)->CSVR)

/**
  * @brief  Set the TMR End value on runtime.
  * @param  __INSTANCE__ TMR peripheral
  * @param  __END__ specifies the new ending value.
  * @retval None
  */
#define __LL_TMR_SET_END_VAL(__INSTANCE__, __END__)                 WRITE_REG((__INSTANCE__)->CEVR, (__END__))

/**
  * @brief  Get the TMR End value on runtime.
  * @param  __INSTANCE__ TMR peripheral
  * @retval 16-bit or 32-bit value of the timer end value register (TMRx_CEVR)
  */
#define __LL_TMR_GET_END_VAL(__INSTANCE__)                          READ_REG((__INSTANCE__)->CEVR)

/**
  * @brief  Set the TMR Counter Register value on runtime.
  * @param  __INSTANCE__ TMR peripheral
  * @param  __COUNTER__ specifies the Counter register new value.
  * @return None
  */
#define __LL_TMR_SET_COUNTER(__INSTANCE__, __COUNTER__)             WRITE_REG((__INSTANCE__)->CNTR, (__COUNTER__))

/**
  * @brief  Get the TMR Counter Register value on runtime.
  * @param  __INSTANCE__ TMR peripheral
  * @return 16-bit or 32-bit value of the timer counter register (TMRx_CNTR)
  */
#define __LL_TMR_GET_COUNTER(__INSTANCE__)                          READ_REG((__INSTANCE__)->CNTR)

/**
  * @brief  Set the TMR Capture Compare Register(TMRx_CCR) value on runtime.
  * @note   This macro normally used when the TMR is configured in Output Compare mode.
  *         User can use the macro to change the compare value on runtime without calling
  *         another time Config function.
  * @note   The new value will take effect immediately when Output Compare Preload (OCPE)
  *         is disabled. Otherwise it will take effect by following condition:
  *           - Update event generated by counter overflow only (if Update event enabled)
  *           - Compare Matching event with the older value.
  *           - Software generate by setting the CCG bit in TMRx_EGR register
  * @param  __INSTANCE__ TMR peripheral
  * @param  __COMPARE__ specifies the Counter register new value.
  * @return None
  */
#define __LL_TMR_SET_COMPARE(__INSTANCE__, __COMPARE__)             WRITE_REG((__INSTANCE__)->CCR, (__COMPARE__))

/**
  * @brief  Get the TMR Capture Compare Register(TMRx_CCR) value on runtime.
  * @note   This macro normally used when the TMR is configured in Input Capture mode.
  *         User can use the macro to get the new capture value on runtime when a Capture event
  *         is generated by fllowing condition:
  *           - Input source trigger an edge matches the Input Capture Polarity edge configuration (CCP)
  *           - Software generate by setting the CCG bit in TMRx_EGR register
  * @param  __INSTANCE__ TMR peripheral
  * @return 16-bit or 32-bit value of the timer capture compare register (TMRx_CCR)
  */
#define __LL_TMR_GET_CAPTURE(__INSTANCE__)                          READ_REG((__INSTANCE__)->CCR)

/**
  * @brief  Set the input channel polarity.
  * @param  __INSTANCE__ Timer peripheral
  * @param  __POLARITY__ This parameter can be one of the following values in @ref TMR_Input_Capture_Polarity:
  *         @arg @ref TMR_ICPOLARITY_RISING :Capture triggered by rising edge on timer input
  *         @arg @ref TMR_ICPOLARITY_FALLING :Capture triggered by falling edge on timer input
  *         @arg @ref TMR_ICPOLARITY_BOTHEDGE :Capture triggered by both rising and falling edges on timer input
  * @retval None
  */
#define __LL_TMR_POLARITY_SET(__INSTANCE__, __POLARITY__)           MODIFY_REG((__INSTANCE__)->CCCR, TMR_CCCR_CCP_Msk, (__POLARITY__))

/**
  * @brief  Set the TMR Ouput Compare Mode on runtime.
  * @param  __INSTANCE__ TMR peripheral
  * @param  __OCMODE__ TMR Output Compare and PWM Modes
  *         This parameter can be one of @ref TMR_Output_Compare_and_PWM_modes
  * @return None
  */
#define __LL_TMR_SET_OCMODE(__INSTANCE__, __OCMODE__)               MODIFY_REG((__INSTANCE__)->CCCR, TMR_CCCR_OCM_Msk, (__OCMODE__))

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup TMR_LL_Exported_Functions
  * @{
  */

/** @addtogroup TMR_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_TMR_Init(TMR_TypeDef *Instance, TMR_InitTypeDef *Init);
LL_StatusETypeDef LL_TMR_DeInit(TMR_TypeDef *Instance);
void LL_TMR_MspInit(TMR_TypeDef *Instance);
void LL_TMR_MspDeInit(TMR_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup TMR_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_TMR_TB_Config(TMR_TypeDef *Instance, TMR_TB_InitTypeDef *sConfig);
LL_StatusETypeDef LL_TMR_IC_Config(TMR_TypeDef *Instance, TMR_IC_InitTypeDef *sConfig);
LL_StatusETypeDef LL_TMR_OC_Config(TMR_TypeDef *Instance, TMR_OC_InitTypeDef *sConfig);
LL_StatusETypeDef LL_TMR_EXT_Config(TMR_TypeDef *Instance, TMR_EXT_InitTypeDef *sConfig);
/**
  * @}
  */


/** @addtogroup TMR_LL_Exported_Functions_Group3
  * @{
  */
LL_StatusETypeDef LL_TMR_Start(TMR_TypeDef *Instance);
LL_StatusETypeDef LL_TMR_Stop(TMR_TypeDef *Instance);
LL_StatusETypeDef LL_TMR_Start_IT(TMR_TypeDef *Instance);
LL_StatusETypeDef LL_TMR_Stop_IT(TMR_TypeDef *Instance);
LL_StatusETypeDef LL_TMR_Start_Synchro(TMRGRP_TypeDef *TMRGRPx, uint32_t SynchroMask);
LL_StatusETypeDef LL_TMR_Stop_Synchro(TMRGRP_TypeDef *TMRGRPx, uint32_t SynchroMask);
LL_StatusETypeDef LL_TMR_EventGenerate(TMR_TypeDef *Instance, TMR_EventSRCETypeDef EventSource);
/**
  * @}
  */


/** @addtogroup TMR_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_TMR_IRQHandler(TMR_TypeDef *Instance);
void LL_TMR_TB_UpdateCallback(TMR_TypeDef *Instance);
void LL_TMR_TB_OverflowCallback(TMR_TypeDef *Instance);
void LL_TMR_IC_CaptureCallback(TMR_TypeDef *Instance);
void LL_TMR_IC_OverCaptureCallback(TMR_TypeDef *Instance);
void LL_TMR_OC_CompareMatchedCallback(TMR_TypeDef *Instance);
/**
  * @}
  */

/**
  * @}
  */


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup TMR_LL_Private_Macros TMR LL Private Macros
  * @brief    TMR LL Private Macros
  * @{
  */

/**
  * @brief  Judge is LSTMR instance or not
  * @param  __INSTANCE__ instance to judge
  * @retval 0 isn't LSTMR instance
  * @retval 1 is LSTMR instance
  */
#define IS_TMR_LSTMR_INSTANCE(__INSTANCE__)            (((__INSTANCE__) == TMR0)    || \
                                                        ((__INSTANCE__) == TMR1)    || \
                                                        ((__INSTANCE__) == TMR2)    || \
                                                        ((__INSTANCE__) == TMR3))

/**
  * @brief  Judge is HSTMR instance or not
  * @param  __INSTANCE__ instance to judge
  * @retval 0 isn't HSTMR instance
  * @retval 1 is HSTMR instance
  */
#define IS_TMR_HSTMR_INSTANCE(__INSTANCE__)            (((__INSTANCE__) == TMR4)    || \
                                                        ((__INSTANCE__) == TMR5)    || \
                                                        ((__INSTANCE__) == TMR6)    || \
                                                        ((__INSTANCE__) == TMR7))

/**
  * @brief  Judge is LSTMR prescaler or not
  * @param  __PRESCALER__ prescaler to judge
  * @retval 0 isn't LSTMR prescaler
  * @retval 1 is LSTMR prescaler
  */
#define IS_TMR_LSTMR_PRESCALER(__PRESCALER__)           ((__PRESCALER__) <= 0xFFFFU )

/**
  * @brief  Judge is HSTMR prescaler or not
  * @param  __PRESCALER__ prescaler to judge
  * @retval 0 isn't HSTMR prescaler
  * @retval 1 is HSTMR prescaler
  */
#define IS_TMR_HSTMR_PRSCALER(__PRESCALER__)            ((__PRESCALER__) <= 0xFFFFFFFFU )

/**
  * @brief  Judge is LSTMR start value or not
  * @param  __VAL__ value to judge
  * @retval 0 is LSTMR start value
  * @retval 1 is LSTMR start value
  */
#define IS_TMR_LSTMR_START_VAL(__VAL__)                 ((__VAL__) <= 0xFFFFUL)

/**
  * @brief  Judge is HSTMR start value or not
  * @param  __VAL__ value to judge
  * @retval 0 is HSTMR start value
  * @retval 1 is HSTMR start value
  */
#define IS_TMR_HSTMR_START_VAL(__VAL__)                 ((__VAL__) <= 0xFFFFFFFFUL)

/**
  * @brief  Judge is LSTMR end value or not
  * @param  __VAL__ value to judge
  * @retval 0 is LSTMR end value
  * @retval 1 is LSTMR end value
  */
#define IS_TMR_LSTMR_END_VAL(__VAL__)                   ((__VAL__) <= 0xFFFFUL)

/**
  * @brief  Judge is HSTMR end value or not
  * @param  __VAL__ value to judge
  * @retval 0 is HSTMR end value
  * @retval 1 is HSTMR end value
  */
#define IS_TMR_HSTMR_END_VAL(__VAL__)                   ((__VAL__) <= 0xFFFFFFFFUL)

/**
  * @brief  Judge is LSTMR compare value or not
  * @param  __VAL__ value to judge
  * @retval 0 isn't LSTMR compare value
  * @retval 1 is LSTMR compare value
  */
#define IS_TMR_LSTMR_COMPARE_VAL(__VAL__)               ((__VAL__) <= 0xFFFFUL)

/**
  * @brief  Judge is HSTMR compare value or not
  * @param  __VAL__ value to judge
  * @retval 0 isn't HSTMR compare value
  * @retval 1 is HSTMR compare value
  */
#define IS_TMR_HSTMR_COMPARE_VAL(__VAL__)               ((__VAL__) <= 0xFFFFFFFFUL)


/**
  * @brief  Judge is TMR input capture filter or not
  * @param  __FILTER__ filter to judge
  * @retval 0 isn't TMR input capture filter
  * @retval 1 is TMR input capture filter
  */
#define IS_TMR_ICFILTER(__FILTER__)                     ((__FILTER__) <= 0xFFUL)

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32F53XX_LL_TMR_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

