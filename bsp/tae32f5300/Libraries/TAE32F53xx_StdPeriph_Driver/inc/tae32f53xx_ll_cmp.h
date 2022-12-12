/**
  ******************************************************************************
  * @file    tae32f53xx_ll_cmp.h
  * @author  MCD Application Team
  * @brief   Header file for CMP Module
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
#ifndef _TAE32F53XX_LL_CMP_H_
#define _TAE32F53XX_LL_CMP_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup CMP_LL
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup CMP_LL_Exported_Constants CMP LL Exported Constants
  * @brief    CMP LL Exported Constants
  * @{
  */

/** @defgroup CMP_Channel_selection CMP Channel selection
  * @{
  */
#define CMP_CHANNEL_0                   (0x00000001U)
#define CMP_CHANNEL_1                   (0x00000002U)
#define CMP_CHANNEL_2                   (0x00000004U)
#define CMP_CHANNEL_3                   (0x00000008U)
#define CMP_CHANNEL_ALL                 (CMP_CHANNEL_0 | CMP_CHANNEL_1 | CMP_CHANNEL_2 | CMP_CHANNEL_3 )
/**
  * @}
  */

/** @defgroup CMP_Interrupt_definition CMP Interrupt definition
  * @{
  */
#define CMP_IT_FALIE                    CMP_CR_FALIE    /*!< CMP_CHx failing edge interrupt */
#define CMP_IT_RISIE                    CMP_CR_RISIE    /*!< CMP_CHx rising edge interrupt */
/**
  * @}
  */

/** @defgroup CMP_Flag_definition CMP Flag Definition
  * @{
  */
#define CMP_FLAG_FAL3IF                 CMP_SR_FALIF_3
#define CMP_FLAG_FAL2IF                 CMP_SR_FALIF_2
#define CMP_FLAG_FAL1IF                 CMP_SR_FALIF_1
#define CMP_FLAG_FAL0IF                 CMP_SR_FALIF_0
#define CMP_FLAG_RIS3IF                 CMP_SR_RISIF_3
#define CMP_FLAG_RIS2IF                 CMP_SR_RISIF_2
#define CMP_FLAG_RIS1IF                 CMP_SR_RISIF_1
#define CMP_FLAG_RIS0IF                 CMP_SR_RISIF_0
#define CMP_FLAG_ALLIF                  (CMP_SR_FALIF_3 | CMP_SR_FALIF_2 | \
                                         CMP_SR_FALIF_1 | CMP_SR_FALIF_0 | \
                                         CMP_SR_RISIF_3 | CMP_SR_RISIF_2 | \
                                         CMP_SR_RISIF_1 | CMP_SR_RISIF_0)
/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup CMP_LL_Exported_Macros CMP LL Exported Macros
  * @brief    CMP LL Exported Macros
  * @{
  */

/**
  * @brief  Enable CMP Channel
  * @param  __INSTANCE__ CMP peripheral
  * @param  __CHN_NB__ Specifies CMP Channel
  *                    This parameter can be a value of 0 to (CMP_CHN_NB - 1)
  * @return None
  */
#define __LL_CMP_ENABLE(__INSTANCE__, __CHN_NB__)                       SET_BIT((__INSTANCE__)->CR[__CHN_NB__], CMP_CR_PEN)

/**
  * @brief  Disable CMP Channel
  * @param  __INSTANCE__ CMP peripheral
  * @param  __CHN_NB__ Specifies CMP Channel
  *                    This parameter can be a value of 0 to (CMP_CHN_NB - 1)
  * @return None
  */
#define __LL_CMP_DISABLE(__INSTANCE__, __CHN_NB__)                      CLEAR_BIT((__INSTANCE__)->CR[__CHN_NB__], CMP_CR_PEN)

/**
  * @brief  Enable the specified CMP Channel Interrupts
  * @param  __INSTANCE__ CMP peripheral
  * @param  __CHN_NB__ Specifies CMP Channel
  *                    This parameter can be a value of 0 to (CMP_CHN_NB - 1)
  * @param  __INTERRUPT__ specifies the CMP Channel interrupt source to enable.
  *         This parameter can be any combination of @ref CMP_Interrupt_definition:
  *             @arg CMP_IT_FALIE       : CMP_CHx failing edge interrupt
  *             @arg CMP_IT_RISIE       : CMP_CHx rising edge interrupt
  * @return None
  */
#define __LL_CMP_IT_ENABLE(__INSTANCE__, __CHN_NB__, __INTERRUPT__)     SET_BIT((__INSTANCE__)->CR[__CHN_NB__], (__INTERRUPT__))

/**
  * @brief  Disable the specified CMP Channel Interrupts
  * @param  __INSTANCE__ CMP peripheral
  * @param  __CHN_NB__ Specifies CMP Channel
  *                    This parameter can be a value of 0 to (CMP_CHN_NB - 1)
  * @param  __INTERRUPT__ specifies the CMP Channel interrupt source to disable.
  *         This parameter can be any combination of @ref CMP_Interrupt_definition:
  *             @arg CMP_IT_FALIE       : CMP_CHx failing edge interrupt
  *             @arg CMP_IT_RISIE       : CMP_CHx rising edge interrupt
  * @return None
  */
#define __LL_CMP_IT_DISABLE(__INSTANCE__, __CHN_NB__, __INTERRUPT__)    CLEAR_BIT((__INSTANCE__)->CR[__CHN_NB__], (__INTERRUPT__))
                                                                    

/**
  * @brief  Check whether the specified CMP Channel interrupt source is set or not.
  * @param  __INSTANCE__ CMP peripheral
  * @param  __CHN_NB__ Specifies CMP Channel
  *                    This parameter can be a value of 0 to (CMP_CHN_NB - 1)
  * @param  __INTERRUPT__ specifies the CMP Channel interrupt source to check.
  *         This parameter can be ONE of @ref CMP_Interrupt_definition:
  *             @arg CMP_IT_FALIE       : CMP_CHx failing edge interrupt
  *             @arg CMP_IT_RISIE       : CMP_CHx rising edge interrupt
  * @return None
  */
#define __LL_CMP_IT_CHECK_SOURCE(__INSTANCE__, __CHN_NB__, __INTERRUPT__)   \
        ((READ_BIT((__INSTANCE__)->CR[__CHN_NB__], (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/**
  * @brief  Check whether the specified pending flag is SET or not.
  * @param  __INSTANCE__ CMP peripheral.
  * @param  __FLAG__ specifies the CMP pending flag to check.
  *         This parameter can be ONE of the following values where x can be a value of
  *         0, 1 ... (CMP_CHN_NB - 1):
  *             @arg CMP_FLAG_FALxIF    : CMP_CHx failing edge interrupt pending flag
  *             @arg CMP_FLAG_RISxIF    : CMP_CHx rising interrupt pending flag
  * @return The new state of __FLAG__ (SET or RESET).
  */
#define __LL_CMP_PENDING_FLAG_GET(__INSTANCE__, __FLAG__)   ((READ_BIT((__INSTANCE__)->SR, (__FLAG__)) == (__FLAG__)) ? SET : RESET)

/**
  * @brief  Clear the specified pending flags
  * @param  __INSTANCE__ CMP peripheral.
  * @param  __FLAG__ specifies the CMP pending flag to clear.
  *         This parameter can be any combination of the following values where x can be a value of
  *         0, 1 ... (CMP_CHN_NB - 1):
  *             @arg CMP_FLAG_FALxIF    : CMP_CHx failing edge interrupt pending flag
  *             @arg CMP_FLAG_RISxIF    : CMP_CHx rising interrupt pending flag
  *             @arg CMP_FLAG_ALLIF     : CMP All interrupt pending flags
  * @return None
  */
#define __LL_CMP_PENDING_FLAG_CLEAR(__INSTANCE__, __FLAG__)             WRITE_REG((__INSTANCE__)->SR, (__FLAG__))


/**
  * @brief  Set the specified CMP Channel output debounce value
  * @param  __INSTANCE__ CMP peripheral.
  * @param  __CHN_NB__ Specifies CMP Channel
  *                    This parameter can be a value of 0 to (CMP_CHN_NB - 1)
  * @param  __VAL__ Specifies debounce value
  *                 This value can be a range from 0 - 0xFFF (in System Clocks)
  * @return None
  */
#define __LL_CMP_DEBOUNCE_VALUE_SET(__INSTANCE__, __CHN_NB__, __VAL__)  WRITE_REG((__INSTANCE__)->DEBR[__CHN_NB__], (__VAL__))
                                                                    
/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup CMP_LL_Exported_Types CMP LL Exported Types
  * @brief    CMP LL Exported Types
  * @{
  */

/**
  * @brief CMP input minus (INM)
  */
typedef enum {
    CMP_INPUT_MINUS_GND = 0x0U,
    /*!< Comparator input minus connected to GND */
    CMP_INPUT_MINUS_IO1 = CMP_CR_INM_0,
    /*!< Comparator input minus connected to IO1, Note: For CMPx instance availability, please refer to SPEC Document */
    CMP_INPUT_MINUS_IO2 = CMP_CR_INM_1,
    /*!< Comparator input minus connected to IO2, Note: For CMPx instance availability, please refer to SPEC Document */
    CMP_INPUT_MINUS_DAC = CMP_CR_INM_1 | CMP_CR_INM_0,
    /*!< Comparator input minus connected to DAC Channel x for CMP Channel x.
        Note: For CMPx & DACx instances availability, please refer to SPEC Document */
} CMP_InputMinusETypeDef;

/**
  * @brief CMP Hysteresis
  */
typedef enum {
    CMP_HYSTERESIS_NONE = 0x0U,                          /*!< No hysteresis          */
    CMP_HYSTERESIS_10MV = CMP_CR_HYST_0,                 /*!< Hysteresis level 10mV  */
    CMP_HYSTERESIS_20MV = CMP_CR_HYST_1,                 /*!< Hysteresis level 20mV  */
    CMP_HYSTERESIS_30MV = CMP_CR_HYST_1 | CMP_CR_HYST_0, /*!< Hysteresis level 30mV  */
} CMP_HysteresisETypeDef;

/** 
  * @brief CMP Blanking Source
  * @note  For CMPx & TMRx instances availability, please refer to SPEC Document
  */
typedef enum {
    CMP_BLANKINGSRC_NONE            = 0x00000000U,

    CMP_BLANKINGSRC_TMR0_PWM_CMP0   = CMP_CR_BLANKING_0,
    /*!< CMP output blanking source TMR0_PWM (specific to CMP Channel0). */
    CMP_BLANKINGSRC_TMR1_PWM_CMP1   = CMP_CR_BLANKING_0,
    /*!< CMP output blanking source TMR1_PWM (specific to CMP Channel1). */
    CMP_BLANKINGSRC_TMR0_PWM_CMP2   = CMP_CR_BLANKING_0,
    /*!< CMP output blanking source TMR0_PWM (specific to CMP Channel2). */
    CMP_BLANKINGSRC_TMR1_PWM_CMP3   = CMP_CR_BLANKING_0,
    /*!< CMP output blanking source TMR1_PWM (specific to CMP Channel3). */

    CMP_BLANKINGSRC_TMR1_PWM_CMP0   = CMP_CR_BLANKING_1,
    /*!< CMP output blanking source TMR1_PWM (specific to CMP Channel0). */
    CMP_BLANKINGSRC_TMR2_PWM_CMP1   = CMP_CR_BLANKING_1,
    /*!< CMP output blanking source TMR2_PWM (specific to CMP Channel1). */
    CMP_BLANKINGSRC_TMR1_PWM_CMP2   = CMP_CR_BLANKING_1,
    /*!< CMP output blanking source TMR1_PWM (specific to CMP Channel2). */
    CMP_BLANKINGSRC_TMR2_PWM_CMP3   = CMP_CR_BLANKING_1,
    /*!< CMP output blanking source TMR2_PWM (specific to CMP Channel3). */

    CMP_BLANKINGSRC_TMR2_PWM_CMP0   = CMP_CR_BLANKING_1 | CMP_CR_BLANKING_0,
    /*!< CMP output blanking source TMR2_PWM (specific to CMP Channel0). */
    CMP_BLANKINGSRC_TMR3_PWM_CMP1   = CMP_CR_BLANKING_1 | CMP_CR_BLANKING_0,
    /*!< CMP output blanking source TMR3_PWM (specific to CMP Channel1). */
    CMP_BLANKINGSRC_TMR2_PWM_CMP2   = CMP_CR_BLANKING_1 | CMP_CR_BLANKING_0,
    /*!< CMP output blanking source TMR2_PWM (specific to CMP Channel2). */
    CMP_BLANKINGSRC_TMR3_PWM_CMP3   = CMP_CR_BLANKING_1 | CMP_CR_BLANKING_0,
    /*!< CMP output blanking source TMR3_PWM (specific to CMP Channel3). */

    CMP_BLANKINGSRC_TMR3_PWM_CMP0   = CMP_CR_BLANKING_2,
    /*!< CMP output blanking source TMR3_PWM (specific to CMP Channel0). */
    CMP_BLANKINGSRC_TMR4_PWM_CMP1   = CMP_CR_BLANKING_2,
    /*!< CMP output blanking source TMR4_PWM (specific to CMP Channel1). */
    CMP_BLANKINGSRC_TMR3_PWM_CMP2   = CMP_CR_BLANKING_2,
    /*!< CMP output blanking source TMR3_PWM (specific to CMP Channel2). */
    CMP_BLANKINGSRC_TMR4_PWM_CMP3   = CMP_CR_BLANKING_2,
    /*!< CMP output blanking source TMR4_PWM (specific to CMP Channel3). */

    CMP_BLANKINGSRC_TMR4_PWM_CMP0   = CMP_CR_BLANKING_2 | CMP_CR_BLANKING_0,
    /*!< CMP output blanking source TMR4_PWM (specific to CMP Channel0). */
    CMP_BLANKINGSRC_TMR5_PWM_CMP1   = CMP_CR_BLANKING_2 | CMP_CR_BLANKING_0,
    /*!< CMP output blanking source TMR5_PWM (specific to CMP Channel1). */
    CMP_BLANKINGSRC_TMR4_PWM_CMP2   = CMP_CR_BLANKING_2 | CMP_CR_BLANKING_0,
    /*!< CMP output blanking source TMR4_PWM (specific to CMP Channel2). */
    CMP_BLANKINGSRC_TMR5_PWM_CMP3   = CMP_CR_BLANKING_2 | CMP_CR_BLANKING_0,
    /*!< CMP output blanking source TMR5_PWM (specific to CMP Channel3). */

    CMP_BLANKINGSRC_TMR5_PWM_CMP0   = CMP_CR_BLANKING_2 | CMP_CR_BLANKING_1,
    /*!< CMP output blanking source TMR5_PWM (specific to CMP Channel0). */
    CMP_BLANKINGSRC_TMR6_PWM_CMP1   = CMP_CR_BLANKING_2 | CMP_CR_BLANKING_1,
    /*!< CMP output blanking source TMR6_PWM (specific to CMP Channel1). */
    CMP_BLANKINGSRC_TMR5_PWM_CMP2   = CMP_CR_BLANKING_2 | CMP_CR_BLANKING_1,
    /*!< CMP output blanking source TMR5_PWM (specific to CMP Channel2). */
    CMP_BLANKINGSRC_TMR6_PWM_CMP3   = CMP_CR_BLANKING_2 | CMP_CR_BLANKING_1,
    /*!< CMP output blanking source TMR6_PWM (specific to CMP Channel3). */

    CMP_BLANKINGSRC_TMR6_PWM_CMP0   = CMP_CR_BLANKING_2 | CMP_CR_BLANKING_1 | CMP_CR_BLANKING_0,
    /*!< CMP output blanking source TMR6_PWM (specific to CMP Channel0). */
    CMP_BLANKINGSRC_TMR7_PWM_CMP1   = CMP_CR_BLANKING_2 | CMP_CR_BLANKING_1 | CMP_CR_BLANKING_0,
    /*!< CMP output blanking source TMR7_PWM (specific to CMP Channel1). */
    CMP_BLANKINGSRC_TMR6_PWM_CMP2   = CMP_CR_BLANKING_2 | CMP_CR_BLANKING_1 | CMP_CR_BLANKING_0,
    /*!< CMP output blanking source TMR6_PWM (specific to CMP Channel2). */
    CMP_BLANKINGSRC_TMR7_PWM_CMP3   = CMP_CR_BLANKING_2 | CMP_CR_BLANKING_1 | CMP_CR_BLANKING_0,
    /*!< CMP output blanking source TMR7_PWM (specific to CMP Channel3). */
} CMP_BlankingSrcETypeDef;

/**
  * @brief CMP Output Debounce
  */
typedef enum {
    CMP_OUTPUT_DEBOUNCE_DISABLE = 0x0U,         /*!< Disable CMP output debounce    */
    CMP_OUTPUT_DEBOUNCE_ENABLE  = CMP_CR_ODEB,  /*!< Enable CMP output debounce     */
} CMP_OutputDebounceETypeDef;

/**
  * @brief CMP output polarity
  */
typedef enum {
    CMP_OUPUT_POLARITY_NON_INVERTED  = 0x0U,
    /*!< CMP output level is not inverted. CMP output HIGH when the input plus(INP) is at a higher voltage than the input minus(INM)    */
    CMP_OUPUT_POLARITY_INVERTED      = CMP_CR_OPOL,
    /*!< CMP output level is inverted. CMP output LOW when the input plus(INP) is at a higher voltage than the input minus(INM)         */
} CMP_OutputPolarityETypeDef;

/**
  * @brief CMP trigger interrupt
  */
typedef enum {
    CMP_TRIGGER_IT_DISABLE          = 0x00000000U,
    /*!< CMP output triggering event without interrupt                                  */
    CMP_TRIGGER_IT_FALLING          = CMP_CR_FALIE,
    /*!< CMP output triggering event with interrupt on falling edge                     */
    CMP_TRIGGER_IT_RISING           = CMP_CR_RISIE,
    /*!< CMP output triggering event with interrupt on rising edge                      */
    CMP_TRIGGER_IT_RISING_FALLING   = CMP_CR_RISIE | CMP_CR_FALIE,
    /*!< CMP output triggering event with interrupt on both rising and falling edges    */
} CMP_TriggerITETypeDef;


/**
  * @brief CMP Channel Configuration structure definition
  */
typedef struct __CMP_ChannelConfTypeDef {
    CMP_InputMinusETypeDef     InputMinus;           /*!< Set comparator input minus (INM).                                     */
    CMP_HysteresisETypeDef     Hysteresis;           /*!< Set comparator hysteresis mode of the input minus(INM).               */
    CMP_BlankingSrcETypeDef    BlankingSource;       /*!< Set comparator blanking source.                                       */
    CMP_OutputDebounceETypeDef OutputDebounce;       /*!< Set comparator output debounce.                                       */
    CMP_OutputPolarityETypeDef OutputPolarity;       /*!< Set comparator output polarity.                                       */
    CMP_TriggerITETypeDef      TriggerInterrupt;     /*!< Set the comparator output triggering with or without interrupt.       */

    uint32_t OutputDebounceValue;                    /*!< Set comparator output debounce vaule. This Should be configured when
                                                         Output Debounce is enabled.
                                                         this value can be a range from 0 - 0xFFF (in System Clocks)            */
} CMP_ChannelConfTypeDef;

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup CMP_LL_Exported_Functions
  * @{
  */

/** @addtogroup CMP_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_CMP_Init(CMP_TypeDef *Instance);
LL_StatusETypeDef LL_CMP_DeInit(CMP_TypeDef *Instance);
void LL_CMP_MspInit(CMP_TypeDef *Instance);
void LL_CMP_MspDeInit(CMP_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup CMP_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_CMP_ChannelConfig(CMP_TypeDef *Instance, uint32_t Channel, CMP_ChannelConfTypeDef *sConfig);
/**
  * @}
  */


/** @addtogroup CMP_LL_Exported_Functions_Group3
  * @{
  */
LL_StatusETypeDef LL_CMP_Start(CMP_TypeDef *Instance, uint32_t Channel);
LL_StatusETypeDef LL_CMP_Stop(CMP_TypeDef *Instance, uint32_t Channel);
/**
  * @}
  */


/** @addtogroup CMP_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_CMP_IRQHandler(CMP_TypeDef *Instance);
void LL_CMP_FailingEdgeTrigCallback(CMP_TypeDef *Instance, uint32_t Channel);
void LL_CMP_RisingEdgeTrigCallback(CMP_TypeDef *Instance, uint32_t Channel);
/**
  * @}
  */

/**
  * @}
  */


/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup CMP_LL_Private_Macros CMP LL Private Macros
  * @brief    CMP LL Private Macros
  * @{
  */

/**
  * @brief  Judge is CMP channel number or not
  * @param  CHN_NB channel number to judge
  * @retval 0 isn't CMP channel number
  * @retval 1 is CMP channel number
  */
#define IS_CMP_NUMBER(CHN_NB)                           ((CHN_NB) < CMP_CHN_NB)

/**
  * @brief  Judge is CMP Channel or not
  * @param  CHN Channel to judge
  * @retval 0 isn't CMP Channel
  * @retval 1 is CMP Channel
  */
#define IS_CMP_CHANNEL(CHN)                            (((CHN) == CMP_CHANNEL_0) || \
                                                        ((CHN) == CMP_CHANNEL_1) || \
                                                        ((CHN) == CMP_CHANNEL_2) || \
                                                        ((CHN) == CMP_CHANNEL_3))

/**
  * @brief  Judge is CMP input minus or not
  * @param  INM input minus to judge
  * @retval 0 isn't CMP input minus
  * @retval 1 is CMP input minus
  */
#define IS_CMP_INPUT_MINUS(INM)                        (((INM) == CMP_INPUT_MINUS_GND) || \
                                                        ((INM) == CMP_INPUT_MINUS_IO1) || \
                                                        ((INM) == CMP_INPUT_MINUS_IO2) || \
                                                        ((INM) == CMP_INPUT_MINUS_DAC))

/**
  * @brief  Judge is CMP hysteresis or not
  * @param  HYST hysteresis to judge
  * @retval 0 isn't CMP hysteresis
  * @retval 1 is CMP hysteresis
  */
#define IS_CMP_HYSTERESIS(HYST)                        (((HYST) == CMP_HYSTERESIS_NONE) || \
                                                        ((HYST) == CMP_HYSTERESIS_10MV) || \
                                                        ((HYST) == CMP_HYSTERESIS_20MV) || \
                                                        ((HYST) == CMP_HYSTERESIS_30MV))

/**
  * @brief  Judge is CMP blanking source or not
  * @param  CHN CMP channel to judge
  * @param  BLANKING blanking to judge
  * @retval 0 isn't CMP blanking source
  * @retval 1 is CMP blanking source
  */
#define IS_CMP_BLANKING_SOURCE(CHN, BLANKING)         (     \
                                                       (((CHN) == CMP_CHANNEL_0) && \
                                                        (((BLANKING) == CMP_BLANKINGSRC_NONE)           ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR0_PWM_CMP0)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR1_PWM_CMP0)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR2_PWM_CMP0)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR3_PWM_CMP0)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR4_PWM_CMP0)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR5_PWM_CMP0)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR6_PWM_CMP0)))    \
                                                      ||    \
                                                       (((CHN) == CMP_CHANNEL_1) && \
                                                        (((BLANKING) == CMP_BLANKINGSRC_NONE)           ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR1_PWM_CMP1)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR2_PWM_CMP1)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR3_PWM_CMP1)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR4_PWM_CMP1)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR5_PWM_CMP1)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR6_PWM_CMP1)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR7_PWM_CMP1)))    \
                                                      ||    \
                                                       (((CHN) == CMP_CHANNEL_2) && \
                                                        (((BLANKING) == CMP_BLANKINGSRC_NONE)           ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR0_PWM_CMP2)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR1_PWM_CMP2)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR2_PWM_CMP2)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR3_PWM_CMP2)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR4_PWM_CMP2)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR5_PWM_CMP2)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR6_PWM_CMP2)))    \
                                                      ||    \
                                                       (((CHN) == CMP_CHANNEL_3) && \
                                                        (((BLANKING) == CMP_BLANKINGSRC_NONE)           ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR1_PWM_CMP3)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR2_PWM_CMP3)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR3_PWM_CMP3)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR4_PWM_CMP3)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR5_PWM_CMP3)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR6_PWM_CMP3)  ||  \
                                                         ((BLANKING) == CMP_BLANKINGSRC_TMR7_PWM_CMP3)))    \
                                                      )

/**
  * @brief  Judge is CMP output debounce or not
  * @param  DEB debounce to judge
  * @retval 0 isn't CMP output debounce
  * @retval 1 is CMP output debounce
  */
#define IS_CMP_OUTPUT_DEBOUNCE(DEB)                    (((DEB) == CMP_OUTPUT_DEBOUNCE_DISABLE) || \
                                                        ((DEB) == CMP_OUTPUT_DEBOUNCE_ENABLE))

/**
  * @brief  Jugdge is CMP output debounce value or not
  * @param  VAL value to judge
  * @retval 0 isn't CMP output debounce value
  * @retval 1 is CMP output debounce value
  */
#define IS_CMP_OUTPUT_DEBOUNCE_VAL(VAL)                 ((VAL) <= 0xFFFUL)


/**
  * @brief  Jugdge is CMP output debounce polarity or not
  * @param  POL polarity to judge
  * @retval 0 isn't CMP output debounce polarity
  * @retval 1 is CMP output debounce polarity
  */
#define IS_CMP_OUTPUT_POLARITY(POL)                    (((POL) == CMP_OUPUT_POLARITY_NON_INVERTED) || \
                                                        ((POL) == CMP_OUPUT_POLARITY_INVERTED))

/**
  * @brief  Judge is CMP trigger interrupt or not
  * @param  INTERRUPT trigger interrupt to judge
  * @retval 0 isn't CMP trigger interrupt
  * @retval 1 is CMP trigger interrupt
  */
#define IS_CMP_TRIGGER_IT(INTERRUPT)                   (((INTERRUPT) == CMP_TRIGGER_IT_DISABLE) || \
                                                        ((INTERRUPT) == CMP_TRIGGER_IT_FALLING) || \
                                                        ((INTERRUPT) == CMP_TRIGGER_IT_RISING)  || \
                                                        ((INTERRUPT) == CMP_TRIGGER_IT_RISING_FALLING))

/**
  * @}
  */


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
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


#endif /* _TAE32F53XX_LL_CMP_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

