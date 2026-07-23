/**
  ******************************************************************************
  * @file    tae32f53xx_ll_dac.h
  * @author  MCD Application Team
  * @brief   Header file for DAC Module
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
#ifndef _TAE32F53XX_LL_DAC_H_
#define _TAE32F53XX_LL_DAC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup DAC_LL
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup DAC_LL_Exported_Constants DAC LL Exported Constants
  * @brief    DAC LL Exported Constants
  * @{
  */

/** @defgroup DAC_Channel_selection DAC Channel selection
  * @brief    DAC Channel selection
  * @{
  */
#define DAC_CHANNEL_0                       (0x00000001U)   /*!< DAC Channel 0      */
#define DAC_CHANNEL_1                       (0x00000002U)   /*!< DAC Channel 1      */
#define DAC_CHANNEL_2                       (0x00000004U)   /*!< DAC Channel 2      */
#define DAC_CHANNEL_3                       (0x00000008U)   /*!< DAC Channel 3      */
#define DAC_CHANNEL_ALL                     (DAC_CHANNEL_0 | DAC_CHANNEL_1 | DAC_CHANNEL_2 | DAC_CHANNEL_3 )
/**
  * @}
  */

/** @defgroup DAC_Interrupt_definition DAC Interrupt definition
  * @brief    DAC Interrupt definition
  * @{
  */
#define DAC_IT_DIE                          DAC_CR_DIE      /*!< DAC_CHx DONE interrupt     */
#define DAC_IT_DBIE                         DAC_CR_DBIE     /*!< DAC_CHx DONEB interrupt    */
/**
  * @}
  */

/** @defgroup DAC_Flag_definition DAC Flag Definition
  * @{
  */
#define DAC_FLAG_D0IF                       DAC_ISR_D0IF    /*!< DAC Channel0 DONE pending flag     */
#define DAC_FLAG_D1IF                       DAC_ISR_D1IF    /*!< DAC Channel1 DONE pending flag     */
#define DAC_FLAG_D2IF                       DAC_ISR_D2IF    /*!< DAC Channel2 DONE pending flag     */
#define DAC_FLAG_D3IF                       DAC_ISR_D3IF    /*!< DAC Channel0 DONE pending flag     */
#define DAC_FLAG_DB0IF                      DAC_ISR_DB0IF   /*!< DAC Channel0 DONEB pending flag    */
#define DAC_FLAG_DB1IF                      DAC_ISR_DB1IF   /*!< DAC Channel1 DONEB pending flag    */
#define DAC_FLAG_DB2IF                      DAC_ISR_DB2IF   /*!< DAC Channel2 DONEB pending flag    */
#define DAC_FLAG_DB3IF                      DAC_ISR_DB3IF   /*!< DAC Channel3 DONEB pending flag    */
#define DAC_FLAG_ALLIF                     (DAC_FLAG_D0IF  | DAC_FLAG_D1IF  | \
                                            DAC_FLAG_D2IF  | DAC_FLAG_D3IF  | \
                                            DAC_FLAG_DB0IF | DAC_FLAG_DB1IF | \
                                            DAC_FLAG_DB2IF | DAC_FLAG_DB3IF )
/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup DAC_LL_Exported_Macros DAC LL Exported Macros
  * @brief    DAC LL Exported Macros
  * @{
  */

/**
  * @brief  Enable DAC Channel
  * @param  __INSTANCE__ DAC peripheral
  * @param  __CHN_NB__ Specifies DAC Channel
  *                    This parameter can be a value of 0 to (DAC_CHN_NB - 1)
  * @return None
  */
#define __LL_DAC_ENABLE(__INSTANCE__, __CHN_NB__)                   SET_BIT((__INSTANCE__)->CR[__CHN_NB__], DAC_CR_PEN)

/**
  * @brief  Disable DAC Channel
  * @param  __INSTANCE__ DAC peripheral
  * @param  __CHN_NB__ Specifies DAC Channel
  *                    This parameter can be a value of 0 to (DAC_CHN_NB - 1)
  * @return None
  */
#define __LL_DAC_DISABLE(__INSTANCE__, __CHN_NB__)                  CLEAR_BIT((__INSTANCE__)->CR[__CHN_NB__], DAC_CR_PEN)


/**
  * @brief  Enable DAC Channel Output to IO feature
  * @param  __INSTANCE__ DAC peripheral
  * @param  __CHN_NB__ Specifies DAC Channel
  *                    This parameter can be a value of 0 to (DAC_CHN_NB - 1)
  * @return None
  */
#define __LL_DAC_OUTPUT_ENABLE(__INSTANCE__, __CHN_NB__)            SET_BIT((__INSTANCE__)->CR[__CHN_NB__], DAC_CR_OEN)

/**
  * @brief  Disable DAC Channel Output to IO feature
  * @param  __INSTANCE__ DAC peripheral
  * @param  __CHN_NB__ Specifies DAC Channel
  *                    This parameter can be a value of 0 to (DAC_CHN_NB - 1)
  * @return None
  */
#define __LL_DAC_OUTPUT_DISABLE(__INSTANCE__, __CHN_NB__)           CLEAR_BIT((__INSTANCE__)->CR[__CHN_NB__], DAC_CR_OEN)

/**
  * @brief  Enable the specified DAC Channel Interrupts
  * @param  __INSTANCE__ DAC peripheral
  * @param  __CHN_NB__ Specifies DAC Channel
  *                    This parameter can be a value of 0 to (DAC_CHN_NB - 1)
  * @param  __INTERRUPT__ specifies the DAC Channel interrupt source to enable.
  *         This parameter can be any combination of @ref DAC_Interrupt_definition:
  *             @arg DAC_IT_DIE         : DAC_CHx DONE interrupt
  *             @arg DAC_IT_DBIE        : DAC_CHx DONEB interrupt
  * @return None
  */
#define __LL_DAC_IT_ENABLE(__INSTANCE__, __CHN_NB__, __INTERRUPT__)     SET_BIT((__INSTANCE__)->CR[__CHN_NB__], __INTERRUPT__)

/**
  * @brief  Disable the specified DAC Channel Interrupts
  * @param  __INSTANCE__ DAC peripheral
  * @param  __CHN_NB__ Specifies DAC Channel
  *                    This parameter can be a value of 0 to (DAC_CHN_NB - 1)
  * @param  __INTERRUPT__ specifies the DAC Channel interrupt source to disable.
  *         This parameter can be any combination of @ref DAC_Interrupt_definition:
  *             @arg DAC_IT_DIE         : DAC_CHx DONE interrupt
  *             @arg DAC_IT_DBIE        : DAC_CHx DONEB interrupt
  * @return None
  */
#define __LL_DAC_IT_DISABLE(__INSTANCE__, __CHN_NB__, __INTERRUPT__)    CLEAR_BIT((__INSTANCE__)->CR[__CHN_NB__], __INTERRUPT__)

/**
  * @brief  Check whether the specified DAC Channel interrupt source is set or not.
  * @param  __INSTANCE__ DAC peripheral
  * @param  __CHN_NB__ Specifies DAC Channel
  *                    This parameter can be a value of 0 to (DAC_CHN_NB - 1)
  * @param  __INTERRUPT__ specifies the DAC Channel interrupt source to check.
  *         This parameter can be ONE of @ref DAC_Interrupt_definition:
  *             @arg DAC_IT_DIE         : DAC_CHx DONE interrupt
  *             @arg DAC_IT_DBIE        : DAC_CHx DONEB interrupt
  * @return None
  */
#define __LL_DAC_IT_CHECK_SOURCE(__INSTANCE__, __CHN_NB__, __INTERRUPT__) \
        ((READ_BIT((__INSTANCE__)->CR[__CHN_NB__], (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/**
  * @brief  Check whether the specified pending flag is SET or not.
  * @param  __INSTANCE__ DAC peripheral.
  * @param  __FLAG__ specifies the DAC pending flag to check.
  *         This parameter can be ONE of the following values where x can be a value of
  *         0, 1 ... (DAC_CHN_NB - 1):
  *             @arg DAC_FLAG_DxIF      : DAC_CHx DONE interrupt pending flag
  *             @arg DAC_FLAG_DBxIF     : DAC_CHx DONEB interrupt pending flag
  * @return The new state of __FLAG__ (SET or RESET).
  */
#define __LL_DAC_PENDING_FLAG_GET(__INSTANCE__, __FLAG__)           \
        ((READ_BIT((__INSTANCE__)->ISR, (__FLAG__)) == (__FLAG__)) ? SET : RESET)

/**
  * @brief  Clear the specified pending flags
  * @param  __INSTANCE__ DAC peripheral.
  * @param  __FLAG__ specifies the DAC pending flag to clear.
  *         This parameter can be any combination of the following values where x can be a value of
  *         0, 1 ... (DAC_CHN_NB - 1):
  *             @arg DAC_FLAG_DxIF      : DAC_CHx DONE interrupt pending flag
  *             @arg DAC_FLAG_DBxIF     : DAC_CHx DONEB interrupt pending flag
  *             @arg DAC_FLAG_ALLIF     : DAC All interrupt pending flags
  * @return None
  */
#define __LL_DAC_PENDING_FLAG_CLEAR(__INSTANCE__, __FLAG__)         WRITE_REG((__INSTANCE__)->ISR, (__FLAG__))


/**
  * @brief  Set the data for DAC channel conversion on runtime
  * @param  __INSTANCE__ DAC peripheral.
  * @param  __CHN_NB__ Specifies DAC Channel
  *                    This parameter can be a value of 0 to (DAC_CHN_NB - 1)
  * @param  __DATA__ Data to be loaded
  * @return None
  */
#define __LL_DAC_SET_VALUE(__INSTANCE__, __CHN_NB__, __DATA__)      WRITE_REG((__INSTANCE__)->WDR[__CHN_NB__], __DATA__)


/**
  * @brief  Get the DAC channel conversion value on runtime
  * @param  __INSTANCE__ DAC peripheral.
  * @param  __CHN_NB__ Specifies DAC Channel
  *                    This parameter can be a value of 0 to (DAC_CHN_NB - 1)
  * @return Conversion value
  */
#define __LL_DAC_GET_VALUE(__INSTANCE__, __CHN_NB__)                READ_REG((__INSTANCE__)->RDR[__CHN_NB__])

/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup DAC_LL_Exported_Types DAC LL Exported Types
  * @brief    DAC LL Exported Types
  * @{
  */

/**
  * @brief DAC Channel Output
  */
typedef enum {
    DAC_CHANNEL_OUTPUT_DISABLE = 0x00000000U,   /*!< DAC Channel Disable    */
    DAC_CHANNEL_OUTPUT_ENABLE  = DAC_CR_OEN,    /*!< DAC Channel Enable     */
} DAC_OutputEnETypedef;

/**
  * @brief DAC Channel Interrupt Done
  */
typedef enum {
    DAC_CHANNEL_DONE_IT_DISABLE = 0x00000000U,  /*!< DAC Channel Done Interrupt Disable */
    DAC_CHANNEL_DONE_IT_ENABLE  = DAC_CR_DIE,   /*!< DAC Channel Done Interrupt Enable  */
} DAC_DoneITEnETypedef;

/**
  * @brief DAC Channel Interrupt DoneB
  */
typedef enum {
    DAC_CHANNEL_DONEB_IT_DISABLE = 0x00000000U, /*!< DAC Channel DoneB Interrupt Disable    */
    DAC_CHANNEL_DONEB_IT_ENABLE  = DAC_CR_DBIE, /*!< DAC Channel DoneB Interrupt Enable     */
} DAC_DoneBITEnETypedef;

/**
  * @brief DAC Sawtooth Polarity
  */
typedef enum {
    DAC_SAWTOOTH_POLARITY_DEC = 0x00000000U,    /*!< Sawtooth wave generation, polarity is decrement    */
    DAC_SAWTOOTH_POLARITY_INC = DAC_CR_STDIR,   /*!< Sawtooth wave generation, polarity is increment    */
} DAC_SawthoothPolETypedef;

/**
  * @brief DAC Triangle Initial Direction
  */
typedef enum {
    DAC_TRIANGLE_INITIALDIRECTION_DEC = 0x00000000U,    /*!< Triangle wave generation, initial direction is decrement   */
    DAC_TRIANGLE_INITIALDIRECTION_INC = DAC_CR_TGDIR,   /*!< Triangle wave generation, initial direction is increment   */
} DAC_TriangleInitDirETypedef;

/**
  * @brief DAC Triangle Amplitude
  */
typedef enum {
    DAC_TRIANGLE_AMPLITUDE_1    = 0x00000000U,                                      /*!< Amplitude of 1     */
    DAC_TRIANGLE_AMPLITUDE_3    = DAC_CR_TGAMP_0,                                   /*!< Amplitude of 3     */
    DAC_TRIANGLE_AMPLITUDE_7    = DAC_CR_TGAMP_1,                                   /*!< Amplitude of 7     */
    DAC_TRIANGLE_AMPLITUDE_15   = DAC_CR_TGAMP_1 | DAC_CR_TGAMP_0,                  /*!< Amplitude of 15    */
    DAC_TRIANGLE_AMPLITUDE_31   = DAC_CR_TGAMP_2,                                   /*!< Amplitude of 31    */
    DAC_TRIANGLE_AMPLITUDE_63   = DAC_CR_TGAMP_2 | DAC_CR_TGAMP_0,                  /*!< Amplitude of 63    */
    DAC_TRIANGLE_AMPLITUDE_127  = DAC_CR_TGAMP_2 | DAC_CR_TGAMP_1,                  /*!< Amplitude of 127   */
    DAC_TRIANGLE_AMPLITUDE_255  = DAC_CR_TGAMP_2 | DAC_CR_TGAMP_1 | DAC_CR_TGAMP_0, /*!< Amplitude of 255   */
    DAC_TRIANGLE_AMPLITUDE_511  = DAC_CR_TGAMP_3,                                   /*!< Amplitude of 511   */
    DAC_TRIANGLE_AMPLITUDE_1023 = DAC_CR_TGAMP_3 | DAC_CR_TGAMP_0,                  /*!< Amplitude of 1023  */
    DAC_TRIANGLE_AMPLITUDE_2047 = DAC_CR_TGAMP_3 | DAC_CR_TGAMP_1,                  /*!< Amplitude of 2047  */
    DAC_TRIANGLE_AMPLITUDE_4095 = DAC_CR_TGAMP_3 | DAC_CR_TGAMP_1 | DAC_CR_TGAMP_0, /*!< Amplitude of 4095  */
} DAC_TrangleAmplETypedef;

/**
  * @brief DAC Trigger Selection
  */
typedef enum {
    DAC_TRIGGER_SOFTWARE             = 0x0U,    /*!< Software trigger by setting bit[s] in DAC_SWTR register            */
    DAC_TRIGGER_TMR0_TRGO            = 0x1U,    /*!< TRGO signal exported from TMR0 (source from Update Event)          */
    DAC_TRIGGER_TMR1_TRGO            = 0x2U,    /*!< TRGO signal exported from TMR1 (source from Update Event)          */
    DAC_TRIGGER_TMR2_TRGO            = 0x3U,    /*!< TRGO signal exported from TMR2 (source from Update Event)          */
    DAC_TRIGGER_TMR3_TRGO            = 0x3U,    /*!< TRGO signal exported from TMR3 (source from Update Event)          */
    DAC_TRIGGER_TMR4_TRGO            = 0x4U,    /*!< TRGO signal exported from TMR4 (source from Update Event)          */
    DAC_TRIGGER_TMR5_TRGO            = 0x5U,    /*!< TRGO signal exported from TMR5 (source from Update Event)          */
    DAC_TRIGGER_TMR6_TRGO            = 0x6U,    /*!< TRGO signal exported from TMR6 (source from Update Event)          */
    DAC_TRIGGER_TMR7_TRGO            = 0x7U,    /*!< TRGO signal exported from TMR7 (source from Update Event)          */
    DAC_TRIGGER_HRPWM_DAC_RESET_TRG0 = 0x8U,    /*!< DAC Reset Trigger event from HRPWM Slave timer0                    */
    DAC_TRIGGER_HRPWM_DAC_RESET_TRG1 = 0x9U,    /*!< DAC Reset Trigger event from HRPWM Slave timer1                    */
    DAC_TRIGGER_HRPWM_DAC_RESET_TRG2 = 0xAU,    /*!< DAC Reset Trigger event from HRPWM Slave timer2                    */
    DAC_TRIGGER_HRPWM_DAC_RESET_TRG3 = 0xBU,    /*!< DAC Reset Trigger event from HRPWM Slave timer3                    */
    DAC_TRIGGER_HRPWM_DAC_RESET_TRG4 = 0xCU,    /*!< DAC Reset Trigger event from HRPWM Slave timer4                    */
    DAC_TRIGGER_HRPWM_DAC_RESET_TRG5 = 0xDU,    /*!< DAC Reset Trigger event from HRPWM Slave timer5                    */
    DAC_TRIGGER_HRPWM_DAC_STEP_TRG0  = 0x8U,    /*!< DAC Step  Trigger event from HRPWM Slave timer0                    */
    DAC_TRIGGER_HRPWM_DAC_STEP_TRG1  = 0x9U,    /*!< DAC Step  Trigger event from HRPWM Slave timer1                    */
    DAC_TRIGGER_HRPWM_DAC_STEP_TRG2  = 0xAU,    /*!< DAC Step  Trigger event from HRPWM Slave timer2                    */
    DAC_TRIGGER_HRPWM_DAC_STEP_TRG3  = 0xBU,    /*!< DAC Step  Trigger event from HRPWM Slave timer3                    */
    DAC_TRIGGER_HRPWM_DAC_STEP_TRG4  = 0xCU,    /*!< DAC Step  Trigger event from HRPWM Slave timer4                    */
    DAC_TRIGGER_HRPWM_DAC_STEP_TRG5  = 0xDU,    /*!< DAC Step  Trigger event from HRPWM Slave timer5                    */
    DAC_TRIGGER_HRPWM_ADC_TRG0       = 0xEU,    /*!< DAC0 Step  Trigger event from HRPWM Common ADDA Trigger 0          */
    DAC_TRIGGER_HRPWM_ADC_TRG1       = 0xEU,    /*!< DAC1 Step  Trigger event from HRPWM Common ADDA Trigger 1          */
    DAC_TRIGGER_HRPWM_ADC_TRG2       = 0xEU,    /*!< DAC2 Step  Trigger event from HRPWM Common ADDA Trigger 2          */
    DAC_TRIGGER_HRPWM_ADC_TRG3       = 0xEU,    /*!< DAC3 Step  Trigger event from HRPWM Common ADDA Trigger 3          */
    DAC_TRIGGER_HRPWM_ADC_TRG4       = 0xEU,    /*!< DAC0 Reset Trigger event from HRPWM Common ADDA Trigger 4          */
    DAC_TRIGGER_HRPWM_ADC_TRG5       = 0xEU,    /*!< DAC1 Reset Trigger event from HRPWM Common ADDA Trigger 5          */
    DAC_TRIGGER_HRPWM_ADC_TRG6       = 0xEU,    /*!< DAC2 Reset Trigger event from HRPWM Common ADDA Trigger 6          */
    DAC_TRIGGER_HRPWM_ADC_TRG7       = 0xEU,    /*!< DAC3 Reset Trigger event from HRPWM Common ADDA Trigger 7          */
    DAC_TRIGGER_EXTERNAL_INPUT_IO1   = 0xFU,    /*!< DAC External Trigger from IO1, please see SPEC from more details   */
    DAC_TRIGGER_EXTERNAL_INPUT_IO2   = 0xFU,    /*!< DAC External Trigger from IO2, please see SPEC from more details   */
} DAC_TriggerSrcETypedef;


/**
  * @brief DAC Channel Configuration structure definition
  */
typedef struct __DAC_ChannelConfTypeDef {
    DAC_OutputEnETypedef Output;    /*!< Specifies the DAC conversion output to IO or not.                              */

    uint32_t DoneIntPending;        /*!< Specifies the interrupt for DONE pending flag enable or disable
                                         This parameter can be a value of @ref DAC_Channel_Interrupt_Done
                                         Note: Sawtooth Reset or Tranigle Step convert done will trigger the DONE flag  */

    uint32_t DoneBIntPending;       /*!< Specifies the interrupt for DONEB pending flag enable or disable
                                         This parameter can be a value of @ref DAC_Channel_Interrupt_DoneB
                                         Note: Sawtooth Step convert done will trigger the DONEB flag                   */
} DAC_ChannelConfTypeDef;

/**
  * @brief DAC Sawtooth Wave Configuration structure definition
  */
typedef struct __DAC_SawtoothConfTypeDef {
    uint16_t ResetData;                     /*!< Specifies the Sawtooth wave Reset value.
                                                This parameter can be a number in range from 0 to DAC full range 4095(0xFFF)    */

    uint16_t StepData;                      /*!< Specifies the Sawtooth wave step value.
                                                12.4 bit format, unsigned: 12 bits exponent / 4 bits mantissa
                                                Step value step is 1/16 = 0.0625
                                                Step value range is 0.0000 to 4095.9375 (0xFFF.F)                               */

    DAC_TriggerSrcETypedef ResetTrigger;    /*!< Specifies the external trigger source for the Sawtooth wave reset trigger
                                               Please see the SPEC Document for more details about the trigger selections       */
    DAC_TriggerSrcETypedef StepTrigger;     /*!< Specifies the external trigger source for the Sawtooth wave step trigger
                                                Please see the SPEC Document for more details about the trigger selections      */
    DAC_SawthoothPolETypedef Polarity;      /*!< Specifies the Sawtooth wave step polarity.*/
} DAC_SawtoothConfTypeDef;

/**
  * @brief DAC Triangle Wave Configuration structure definition
  */
typedef struct __DAC_TriangleConfTypeDef {
    DAC_TriangleInitDirETypedef InitialDirection;   /*!< Specifies the Triangle wave initial step direction.                        */
    DAC_TrangleAmplETypedef     Amplitude;          /*!< Specifies max triangle amplitude.                                          */
    DAC_TriggerSrcETypedef      StepTrigger;        /*!< Specifies the external trigger source for the Triangle wave step trigger
                                                        Please see the SPEC Document for more details about the trigger selections  */
} DAC_TriangleConfTypeDef;

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup DAC_LL_Exported_Functions
  * @{
  */

/** @addtogroup DAC_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_DAC_Init(DAC_TypeDef *Instance);
LL_StatusETypeDef LL_DAC_DeInit(DAC_TypeDef *Instance);
void LL_DAC_MspInit(DAC_TypeDef *Instance);
void LL_DAC_MspDeInit(DAC_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup DAC_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_DAC_ChannelConfig(DAC_TypeDef *Instance, uint32_t Channel, DAC_ChannelConfTypeDef *sConfig);
LL_StatusETypeDef LL_DAC_SawtoothWaveGenerate(DAC_TypeDef *Instance, uint32_t Channel, DAC_SawtoothConfTypeDef *sConfig);
LL_StatusETypeDef LL_DAC_TriangleWaveGenerate(DAC_TypeDef *Instance, uint32_t Channel, DAC_TriangleConfTypeDef *sConfig);
/**
  * @}
  */


/** @addtogroup DAC_LL_Exported_Functions_Group3
  * @{
  */
LL_StatusETypeDef LL_DAC_Start(DAC_TypeDef *Instance, uint32_t Channel);
LL_StatusETypeDef LL_DAC_Stop(DAC_TypeDef *Instance, uint32_t Channel);
LL_StatusETypeDef LL_DAC_SetValue(DAC_TypeDef *Instance, uint32_t Channel, uint16_t Data);
uint16_t          LL_DAC_GetValue(DAC_TypeDef *Instance, uint32_t Channel);
LL_StatusETypeDef LL_DAC_SawtoothWaveDataStep(DAC_TypeDef *Instance, uint32_t Channel);
LL_StatusETypeDef LL_DAC_SawtoothWaveDataReset(DAC_TypeDef *Instance, uint32_t Channel);
LL_StatusETypeDef LL_DAC_TriangleWaveStep(DAC_TypeDef *Instance, uint32_t Channel);
/**
  * @}
  */


/** @addtogroup DAC_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_DAC_IRQHandler(DAC_TypeDef *Instance);
void LL_DAC_ConvDoneCallback(DAC_TypeDef *Instance, uint32_t Channel);
void LL_DAC_ConvDoneBCallback(DAC_TypeDef *Instance, uint32_t Channel);
/**
  * @}
  */

/**
  * @}
  */


/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup DAC_LL_Private_Macros DAC LL Private Macros
  * @brief    DAC LL Private Macros
  * @{
  */

/**
  * @brief  Judge is DAC channel number or not
  * @param  CHN_NB channel number to judge
  * @retval 0 isn't DAC channel number
  * @retval 1 is DAC channel number
  */
#define IS_DAC_NUMBER(CHN_NB)                           ((CHN_NB) < DAC_CHN_NB)

/**
  * @brief  Judge is DAC channel or not
  * @param  CHN channel to judge
  * @retval 0 isn't DAC channel
  * @retval 1 is DAC channel
  */
#define IS_DAC_CHANNEL(CHN)                             (((CHN) == DAC_CHANNEL_0) || \
                                                         ((CHN) == DAC_CHANNEL_1) || \
                                                         ((CHN) == DAC_CHANNEL_2) || \
                                                         ((CHN) == DAC_CHANNEL_3))

/**
  * @brief  Judge is DAC channels mask or not
  * @param  CHN channels mask to judge
  * @retval 0 isn't DAC channels mask
  * @retval 1 is DAC channels mask
  */
#define IS_DAC_CHANNELS_MASK(CHN)                       ((((CHN) & DAC_CHANNEL_ALL) != 0x00UL) && \
                                                         (((CHN) & ~(DAC_CHANNEL_ALL)) == 0x00UL))

/**
  * @brief  Judge is DAC channel output select or not
  * @param  OUTPUT output select
  * @retval 0 isn't DAC channel output select
  * @retval 1 is DAC channel output select
  */
#define IS_DAC_CHANNEL_OUTPUT_SEL(OUTPUT)               (((OUTPUT) == DAC_CHANNEL_OUTPUT_DISABLE) || \
                                                         ((OUTPUT) == DAC_CHANNEL_OUTPUT_ENABLE))

/**
  * @brief  Judge is DAC channel done interrupt pending config or not
  * @param  PENDING pending config to judge
  * @retval 0 isn't DAC channel done interrupt pending config
  * @retval 1 is DAC channel done interrupt pending config
  */
#define IS_DAC_CHANNEL_DONE_IT_PENDING_CFG(PENDING)     (((PENDING) == DAC_CHANNEL_DONE_IT_DISABLE) || \
                                                         ((PENDING) == DAC_CHANNEL_DONE_IT_ENABLE))

/**
  * @brief  Judge is DAC channel doneB interrupt pending config or not
  * @param  PENDING pending config to judge
  * @retval 0 isn't DAC channel doneB interrupt pending config
  * @retval 1 is DAC channel doneB interrupt pending config
  */
#define IS_DAC_CHANNEL_DONEB_IT_PENDING_CFG(PENDING)    (((PENDING) == DAC_CHANNEL_DONEB_IT_DISABLE) || \
                                                         ((PENDING) == DAC_CHANNEL_DONEB_IT_ENABLE))

/**
  * @brief  Judge is DAC sawtooth reset data or not
  * @param  DATA data to judge
  * @retval 0 isn't DAC sawtooth reset data
  * @retval 1 is DAC sawtooth reset data
  */
#define IS_DAC_SAWTOOTH_RESET_DATA(DATA)                ((DATA) <= 0xFFFUL)

/**
  * @brief  Judge is DAC sawtooth step data or not
  * @param  DATA data to judge
  * @retval 0 isn't DAC sawtooth step data
  * @retval 1 is DAC sawtooth step data
  */
#define IS_DAC_SAWTOOTH_STEP_DATA(DATA)                 ((DATA) <= 0xFFFFUL)

/**
  * @brief  Judge is DAC sawtooth reset trigger or not
  * @param  TRIGGER trigger to judge
  * @retval 0 isn't DAC sawtooth reset trigger
  * @retval 1 is DAC sawtooth reset trigger
  */
#define IS_DAC_SAWTOOTH_RESET_TRIGGER(TRIGGER)          ((TRIGGER) < 16U)

/**
  * @brief  Judge is DAC sawtooth step trigger or not
  * @param  TRIGGER trigger to judge
  * @retval 0 isn't DAC sawtooth step trigger
  * @retval 1 is DAC sawtooth step trigger
  */
#define IS_DAC_SAWTOOTH_STEP_TRIGGER(TRIGGER)           ((TRIGGER) < 16U)

/**
  * @brief  Judge is DAC sawtooth polarity or not
  * @param  POLARITY polarity to judge
  * @retval 0 isn't DAC sawtooth polarity
  * @retval 1 is DAC sawtooth polarity
  */
#define IS_DAC_SAWTOOTH_POLARITY(POLARITY)              (((POLARITY) == DAC_SAWTOOTH_POLARITY_DEC) || \
                                                         ((POLARITY) == DAC_SAWTOOTH_POLARITY_INC))

/**
  * @brief  Judge is DAC triangle initial direction or not
  * @param  DIR direction to judge
  * @retval 0 isn't DAC triangle initial direction
  * @retval 1 is DAC triangle initial direction
  */
#define IS_DAC_TRIANGLE_INITIALDIRECTION(DIR)           (((DIR) == DAC_TRIANGLE_INITIALDIRECTION_DEC) || \
                                                         ((DIR) == DAC_TRIANGLE_INITIALDIRECTION_INC))

/**
  * @brief  Judge is DAC triangle amplitude or not
  * @param  AMP amplitude to judge
  * @retval 0 isn't DAC triangle amplitude
  * @retval 1 is DAC triangle amplitude
  */
#define IS_DAC_TRIANGLE_AMPLITUDE(AMP)                  (((AMP) == DAC_TRIANGLE_AMPLITUDE_1)     || \
                                                         ((AMP) == DAC_TRIANGLE_AMPLITUDE_3)     || \
                                                         ((AMP) == DAC_TRIANGLE_AMPLITUDE_7)     || \
                                                         ((AMP) == DAC_TRIANGLE_AMPLITUDE_15)    || \
                                                         ((AMP) == DAC_TRIANGLE_AMPLITUDE_31)    || \
                                                         ((AMP) == DAC_TRIANGLE_AMPLITUDE_63)    || \
                                                         ((AMP) == DAC_TRIANGLE_AMPLITUDE_127)   || \
                                                         ((AMP) == DAC_TRIANGLE_AMPLITUDE_255)   || \
                                                         ((AMP) == DAC_TRIANGLE_AMPLITUDE_511)   || \
                                                         ((AMP) == DAC_TRIANGLE_AMPLITUDE_1023)  || \
                                                         ((AMP) == DAC_TRIANGLE_AMPLITUDE_2047)  || \
                                                         ((AMP) == DAC_TRIANGLE_AMPLITUDE_4095))

/**
  * @brief  Judge is DAC triangle step trigger or not
  * @param  TRIGGER trigger to judge
  * @retval 0 isn't DAC triangle step trigger
  * @retval 1 is DAC triangle step trigger
  */
#define IS_DAC_TRIANGLE_STEP_TRIGGER(TRIGGER)           ((TRIGGER) < 16U)

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


#endif /* _TAE32F53XX_LL_DAC_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

