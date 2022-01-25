/**
  ******************************************************************************
  * @file    tae32f53xx_ll_adc.h
  * @author  MCD Application Team
  * @brief   Header file of ADC LL module.
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
#ifndef _TAE32F53XX_LL_ADC_H_
#define _TAE32F53XX_LL_ADC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup ADC_LL
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Constants ADC LL Exported Constants
  * @brief    ADC LL Exported Constants
  * @{
  */

/**
  * @brief regular trigger edge
  *        Internal mask for ADC group regular trigger:
  *        To select into literal LL_ADC_REG_TRIG_x the relevant bits for:
  */
#define ADC_REG_TRIG_EXT_EDGE_DEFAULT       (ADC_LR_EXTEN_0)

/**
  * @brief Mask containing trigger source masks for each of possible
  *        trigger edge selection duplicated with shifts [0; 4; 8; 12]
  *        corresponding to {SW start; ext trigger; ext trigger; ext trigger}
  */
#define ADC_REG_TRIG_SOURCE_MASK            (((ADC_REG_TRIG_SOFTWARE & ADC_LR_EXTSEL)   << (4U * 0UL)) |    \
                                             ((ADC_LR_EXTSEL) << (4U * 1UL)) |                              \
                                             ((ADC_LR_EXTSEL) << (4U * 2UL)) |                              \
                                             ((ADC_LR_EXTSEL) << (4U * 3UL))  )

/**
  * @brief Mask containing trigger edge masks for each of possible
  *        trigger edge selection duplicated with shifts [0; 4; 8; 12]
  *        corresponding to {SW start; ext trigger; ext trigger; ext trigger}
  */
#define ADC_REG_TRIG_EDGE_MASK              (((ADC_REG_TRIG_SOFTWARE & ADC_LR_EXTEN)   << (4U * 0UL)) | \
                                             ((ADC_REG_TRIG_EXT_EDGE_DEFAULT) << (4U * 1UL)) |          \
                                             ((ADC_REG_TRIG_EXT_EDGE_DEFAULT) << (4U * 2UL)) |          \
                                             ((ADC_REG_TRIG_EXT_EDGE_DEFAULT) << (4U * 3UL))  )

/**
  * @brief Definition of ADC group regular trigger bits information
  */
#define ADC_REG_TRIG_EXTSEL_BITOFFSET_POS  (ADC_LR_EXTSEL_Pos)

/**
  * @brief Definition of ADC group regular trigger bits information
  */
#define ADC_REG_TRIG_EXTEN_BITOFFSET_POS   (ADC_LR_EXTEN_Pos)

/**
  * @brief Internal mask for ADC group injected trigger:
  *        To select into literal LL_ADC_INJ_TRIG_x the relevant bits for:
  */
#define ADC_INJ_TRIG_EXT_EDGE_DEFAULT      (ADC_JLR_JEXTEN_0)

/**
  * @brief Mask containing trigger source masks for each of possible
  *        trigger edge selection duplicated with shifts [0; 4; 8; 12]
  *        corresponding to {SW start; ext trigger; ext trigger; ext trigger}
  */
#define ADC_INJ_TRIG_SOURCE_MASK            (((ADC_INJ_TRIG_SOFTWARE & ADC_JLR_JEXTSEL)  << (4U * 0UL)) |   \
                                             ((ADC_JLR_JEXTSEL) << (4U * 1UL)) |                            \
                                             ((ADC_JLR_JEXTSEL) << (4U * 2UL)) |                            \
                                             ((ADC_JLR_JEXTSEL) << (4U * 3UL))  )

/**
  * @brief Mask containing trigger edge masks for each of possible
  *        trigger edge selection duplicated with shifts [0; 4; 8; 12]
  *        corresponding to {SW start; ext trigger; ext trigger; ext trigger}
  */
#define ADC_INJ_TRIG_EDGE_MASK              (((ADC_INJ_TRIG_SOFTWARE & ADC_JLR_JEXTEN)  << (4U * 0UL)) |    \
                                             ((ADC_INJ_TRIG_EXT_EDGE_DEFAULT) << (4U * 1UL)) |              \
                                             ((ADC_INJ_TRIG_EXT_EDGE_DEFAULT) << (4U * 2UL)) |              \
                                             ((ADC_INJ_TRIG_EXT_EDGE_DEFAULT) << (4U * 3UL))  )

/**
  * @brief Definition of ADC group injected trigger bits information
  */
#define ADC_INJ_TRIG_EXTSEL_BITOFFSET_POS  (ADC_JLR_JEXTSEL_Pos)

/**
  * @brief Definition of ADC group injected trigger bits information
  */
#define ADC_INJ_TRIG_EXTEN_BITOFFSET_POS   (ADC_JLR_JEXTEN_Pos)

/**
  * @brief Definition of ADC group injected trigger bits information
  */
#define ADC_SINGLEDIFF_CHANNEL_SHIFT       (0x00000001UL)

/**
  * @brief Definition of ADC group injected trigger bits information
  */
#define ADC_JSQX_REGOFFSET                 (0x00000002UL)

/**
  * @brief Definition of ADC group injected trigger bits information
  */
#define ADC_SMPRX_REGOFFSET                (0x00000002UL)

/**
  * @brief Definition of ADC group injected trigger bits information
  */
#define ADC_SMPRX_REGOFFSET_POS            (25UL) /* Position of bits ADC_SMPRx_REGOFFSET in ADC_CHANNEL_SMPRX_REGOFFSET_MASK */


/**
  * @brief ADC register CR bits: Software can read as well as set this bit. Writing '0' has no effect on the bit value.
  */
#define ADC_CR0_BITS_PROPERTY_RS           (ADC_CR0_JADSTP | ADC_CR0_ADSTP | ADC_CR0_JADSTART | ADC_CR0_ADSTART)



/** @defgroup ADC_LL_AWD_CHANNELS ADC LL AWD CHANNELS
  * @brief    Analog watchdog Monitored channels
  * @{
  */

/** @brief ADC analog watchdog monitoring disabled */
#define ADC_AWD_DISABLE                 (0x00000000UL)
/** @brief ADC analog watchdog monitoring enable */
#define ADC_AWD_ALL_CHANNELS            (0x00000FFFUL)
/** @brief ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN0 */
#define ADC_AWD_CHANNEL_0               (ADC_AWD0CR_AWD0CH_0 )
/** @brief ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN1 */
#define ADC_AWD_CHANNEL_1               (ADC_AWD0CR_AWD0CH_1 )
/** @brief ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN2 */
#define ADC_AWD_CHANNEL_2               (ADC_AWD0CR_AWD0CH_2 )
/** @brief ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN3 */
#define ADC_AWD_CHANNEL_3               (ADC_AWD0CR_AWD0CH_3 )
/** @brief ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN4 */
#define ADC_AWD_CHANNEL_4               (ADC_AWD0CR_AWD0CH_4 )
/** @brief ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN5 */
#define ADC_AWD_CHANNEL_5               (ADC_AWD0CR_AWD0CH_5 )
/** @brief ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN6 */
#define ADC_AWD_CHANNEL_6               (ADC_AWD0CR_AWD0CH_6 )
/** @brief ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN7 */
#define ADC_AWD_CHANNEL_7               (ADC_AWD0CR_AWD0CH_7 )
/** @brief ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN8 */
#define ADC_AWD_CHANNEL_8               (ADC_AWD0CR_AWD0CH_8 )
/** @brief ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN9 */
#define ADC_AWD_CHANNEL_9               (ADC_AWD0CR_AWD0CH_9 )
/** @brief ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN10 */
#define ADC_AWD_CHANNEL_10              (ADC_AWD0CR_AWD0CH_10)
/** @brief ADC analog watchdog monitoring of ADC external channel (channel connected to GPIO pin) ADCx_IN11 */
#define ADC_AWD_CHANNEL_TEMPSENSOR      (ADC_AWD0CR_AWD0CH_11)

/**
  * @}
  */


/** @defgroup ADC_LL_IT ADC LL IT
  * @brief    ADC interruptions for configuration (interruption enable or disable)
  * @note     IT defines which can be used with LL_ADC_ReadReg and  LL_ADC_WriteReg functions
  * @{
  */
#define ADC_IT_ADRDY                    ADC_IER_ADRDYIE    /*!< ADC interruption ADC instance ready                             */
#define ADC_IT_EOC                      ADC_IER_EOCIE      /*!< ADC interruption ADC group regular end of unitary conversion    */
#define ADC_IT_EOS                      ADC_IER_EOSIE      /*!< ADC interruption ADC group regular end of sequence conversions  */
#define ADC_IT_OVR                      ADC_IER_OVRIE      /*!< ADC interruption ADC group regular overrun                      */
#define ADC_IT_EOSMP                    ADC_IER_EOSMPIE    /*!< ADC interruption ADC group regular end of sampling phase        */
#define ADC_IT_JEOC                     ADC_IER_JEOCIE     /*!< ADC interruption ADC group injected end of unitary conversion   */
#define ADC_IT_JEOS                     ADC_IER_JEOSIE     /*!< ADC interruption ADC group injected end of sequence conversions */
#define ADC_IT_AWD0                     ADC_IER_AWD0IE     /*!< ADC interruption ADC analog watchdog 0                          */
#define ADC_IT_AWD1                     ADC_IER_AWD1IE     /*!< ADC interruption ADC analog watchdog 1                          */
#define ADC_IT_AWD2                     ADC_IER_AWD2IE     /*!< ADC interruption ADC analog watchdog 2                          */
/**
  * @}
  */


/** @defgroup ADC_FLAG ADC FLAG
  * @brief    Flags defines which can be used with LL_ADC_ReadReg function
  * @{
  */
#define ADC_FLAG_ADRDY                  ADC_ISR_ADRDY      /*!< ADC flag ADC instance ready                             */
#define ADC_FLAG_EOC                    ADC_ISR_EOC        /*!< ADC flag ADC group regular end of unitary conversion    */
#define ADC_FLAG_EOS                    ADC_ISR_EOS        /*!< ADC flag ADC group regular end of sequence conversions  */
#define ADC_FLAG_OVR                    ADC_ISR_OVR        /*!< ADC flag ADC group regular overrun                      */
#define ADC_FLAG_EOSMP                  ADC_ISR_EOSMP      /*!< ADC flag ADC group regular end of sampling phase        */
#define ADC_FLAG_JEOC                   ADC_ISR_JEOC       /*!< ADC flag ADC group injected end of unitary conversion   */
#define ADC_FLAG_JEOS                   ADC_ISR_JEOS       /*!< ADC flag ADC group injected end of sequence conversions */
#define ADC_FLAG_AWD0                   ADC_ISR_AWD0       /*!< ADC flag ADC analog watchdog 1                          */
#define ADC_FLAG_AWD1                   ADC_ISR_AWD1       /*!< ADC flag ADC analog watchdog 2                          */
#define ADC_FLAG_AWD2                   ADC_ISR_AWD2       /*!< ADC flag ADC analog watchdog 3                          */

#define ADC_AWD_THRESHOLDS_HIGH_POS    (16U)                /*!< ADC AWD Thresholds high pos                            */
/**
  * @}
  */


/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Types ADC LL Exported Types
  * @brief    ADC LL Exported Types
  * @{
  */

/**
  * @brief Oversampling - Data shift
  */
typedef enum {
    ADC_OVSS_SHIFT_NONE            = 0x0,
    /*!< ADC oversampling no shift (sum of the ADC conversions data is not divided to result as the ADC oversampling conversion data) */
    ADC_OVSS_SHIFT_RIGHT_1         = ADC_CR1_OVSS_0,
    /*!< ADC oversampling shift of 1 (sum of the ADC conversions data is divided by 2 to result as the ADC oversampling conversion data) */
    ADC_OVSS_SHIFT_RIGHT_2         = ADC_CR1_OVSS_1,
    /*!< ADC oversampling shift of 2 (sum of the ADC conversions data is divided by 4 to result as the ADC oversampling conversion data) */
    ADC_OVSS_SHIFT_RIGHT_3         = ADC_CR1_OVSS_1 | ADC_CR1_OVSS_0,
    /*!< ADC oversampling shift of 3 (sum of the ADC conversions data is divided by 8 to result as the ADC oversampling conversion data) */
    ADC_OVSS_SHIFT_RIGHT_4         = ADC_CR1_OVSS_2,
    /*!< ADC oversampling shift of 4 (sum of the ADC conversions data is divided by 16 to result as the ADC oversampling conversion data) */
    ADC_OVSS_SHIFT_RIGHT_5         = ADC_CR1_OVSS_2 | ADC_CR1_OVSS_0,
    /*!< ADC oversampling shift of 5 (sum of the ADC conversions data is divided by 32 to result as the ADC oversampling conversion data) */
    ADC_OVSS_SHIFT_RIGHT_6         = ADC_CR1_OVSS_2 | ADC_CR1_OVSS_1,
    /*!< ADC oversampling shift of 6 (sum of the ADC conversions data is divided by 64 to result as the ADC oversampling conversion data) */
    ADC_OVSS_SHIFT_RIGHT_7         = ADC_CR1_OVSS_2 | ADC_CR1_OVSS_1 | ADC_CR1_OVSS_0,
    /*!< ADC oversampling shift of 7 (sum of the ADC conversions data is divided by 128 to result as the ADC oversampling conversion data) */
    ADC_OVSS_SHIFT_RIGHT_8         = ADC_CR1_OVSS_3,
    /*!< ADC oversampling shift of 8 (sum of the ADC conversions data is divided by 256 to result as the ADC oversampling conversion data) */
} ADC_OverSampShiftETypeDef;

/**
  * @brief Oversampling - Ratio
  */
typedef enum {
    ADC_OVSR_RATIO_2             = 0x0,
    /*!< ADC oversampling ratio of 2 (before potential shift) */
    ADC_OVSR_RATIO_4             = ADC_CR1_OVSR_0,
    /*!< ADC oversampling ratio of 4 (before potential shift) */
    ADC_OVSR_RATIO_8             = ADC_CR1_OVSR_1,
    /*!< ADC oversampling ratio of 8 (before potential shift) */
    ADC_OVSR_RATIO_16            = ADC_CR1_OVSR_1 | ADC_CR1_OVSR_0,
    /*!< ADC oversampling ratio of 16 (before potential shift) */
    ADC_OVSR_RATIO_32            = ADC_CR1_OVSR_2,
    /*!< ADC oversampling ratio of 32 (before potential shift) */
    ADC_OVSR_RATIO_64            = ADC_CR1_OVSR_2 | ADC_CR1_OVSR_0,
    /*!< ADC oversampling ratio of 64 (before potential shift) */
    ADC_OVSR_RATIO_128           = ADC_CR1_OVSR_2 | ADC_CR1_OVSR_1,
    /*!< ADC oversampling ratio of 128 (before potential shift) */
    ADC_OVSR_RATIO_256           = ADC_CR1_OVSR_2 | ADC_CR1_OVSR_1 | ADC_CR1_OVSR_0,
    /*!< ADC oversampling ratio of 256 (before potential shift) */
} ADC_OverSampRatioETypeDef;

/**
  * @brief Oversampling scope
  */
typedef enum {
    ADC_OVS_DISABLE                 = 0x0,
    /*!< ADC oversampling disabled. */
    ADC_OVS_GRP_REGULAR_CONTINUED   = ADC_CR1_ROVSE,
    /*!< ADC oversampling on conversions of ADC group regular. If group injected interrupts group regular:
    when ADC group injected is triggered, the oversampling on ADC group regular is temporary stopped and continued afterwards. */
    ADC_OVS_GRP_REGULAR_RESUMED     = ADC_CR1_ROVSM | ADC_CR1_ROVSE,
    /*!< ADC oversampling on conversions of ADC group regular. If group injected interrupts group regular:
    when ADC group injected is triggered, the oversampling on ADC group regular is resumed from start (oversampler buffer reset). */
    ADC_OVS_GRP_INJECTED            = ADC_CR1_JOVSE,
    /*!< ADC oversampling on conversions of ADC group injected. */
    ADC_OVS_GRP_INJ_REG_RESUMED     = ADC_CR1_JOVSE | ADC_CR1_ROVSE,
    /*!< ADC oversampling on conversions of both ADC groups regular and injected. If group injected interrupting group regular:
    when ADC group injected is triggered, the oversampling on ADC group regular is resumed from start (oversampler buffer reset). */
} ADC_OverSampModeETypeDef;

/**
  * @brief Oversampling scope for ADC group regular valid
  */
typedef enum {
    ADC_OVS_CONTINUED_MODE          = 0x0,
    /*!< Oversampling buffer maintained during injection sequence */
    ADC_OVS_RESUMED_MODE            = ADC_CR1_ROVSM,
    /*!< Oversampling buffer zeroed during injection sequence     */
} ADC_OverSampROVSMETypeDef;

/**
  * @brief Discontinuous mode Trigger over sample
  */
typedef enum {
    ADC_OVS_TRIG_CONT             = 0x0,
    /*!< ADC oversampling discontinuous mode: continuous mode (all conversions of oversampling ratio are done from 1 trigger) */
    ADC_OVS_TRIG_DISCONT          = ADC_CR1_TROVS,
    /*!< ADC oversampling discontinuous mode: discontinuous mode (each conversion of oversampling ratio needs a trigger) */
} ADC_OverSampTROVSETypeDef;

/**
  * @brief Synchronization
  */
typedef enum {
    ADC_SYNCEN_DIS              = 0x0,
    /*!< ADC synchronization is disable */
    ADC_SYNCEN_EN               = ADC_CR1_SYNCEN,
    /*!< ADC synchronization is enabled */
} ADC_SyncEnETypeDef;

/**
  * @brief ADC TBIMOD SEL
  */
typedef enum {
    ADC_TBIMOD_MUX_CLOSE            = 0x0,
    ADC_TBIMOD_A_SH                 = ADC_CR1_OVSR_2,
    ADC_TBIMOD_A_ADC                = ADC_CR1_OVSR_2 | ADC_CR1_OVSR_0,
    ADC_TBIMOD_B_SH                 = ADC_CR1_OVSR_2 | ADC_CR1_OVSR_1,
    ADC_TBIMOD_B_ADC                = ADC_CR1_OVSR_2 | ADC_CR1_OVSR_1 | ADC_CR1_OVSR_0,
} ADC_TestBuffModeETypeDef;

/**
  * @brief ADC ANOLOG CTL
  */
typedef enum {
    ADC_ANOLOG_CTL_DEFAULT        = ADC_CR2_ISEL_1 | ADC_CR2_CH_EN | ADC_CR2_FADC_EN | ADC_CR2_REF_EN | ADC_CR2_BIAS_EN,
    ADC_ANOLOG_CTL_A_SH           = ADC_ANOLOG_CTL_DEFAULT | ADC_TBIMOD_A_SH,
    ADC_ANOLOG_CTL_A_ADC          = ADC_ANOLOG_CTL_DEFAULT | ADC_TBIMOD_A_ADC,
    ADC_ANOLOG_CTL_B_SH           = ADC_ANOLOG_CTL_DEFAULT | ADC_TBIMOD_B_SH,
    ADC_ANOLOG_CTL_B_ADC          = ADC_ANOLOG_CTL_DEFAULT | ADC_TBIMOD_B_ADC,
} ADC_AnologCtlETypeDef;

/**
  * @brief Channel Sampling time
  */
typedef enum {
    ADC_SAMPLINGTIME_6CYCLES       = 0x0,
    /*!< Sampling time 6 ADC clock cycles */
    ADC_SAMPLINGTIME_18CYCLES      = ADC_SMPR0_SMP0_0,
    /*!< Sampling time 18 ADC clock cycles */
    ADC_SAMPLINGTIME_42CYCLES      = ADC_SMPR0_SMP0_1,
    /*!< Sampling time 42 ADC clock cycles */
    ADC_SAMPLINGTIME_90CYCLES      = ADC_SMPR0_SMP0_1 | ADC_SMPR0_SMP0_0,
    /*!< Sampling time 90 ADC clock cycles */
    ADC_SAMPLINGTIME_186CYCLES     = ADC_SMPR0_SMP0_2,
    /*!< Sampling time 186 ADC clock cycles */
    ADC_SAMPLINGTIME_378CYCLES     = ADC_SMPR0_SMP0_2 | ADC_SMPR0_SMP0_0,
    /*!< Sampling time 378 ADC clock cycles */
    ADC_SAMPLINGTIME_762CYCLES     = ADC_SMPR0_SMP0_2 | ADC_SMPR0_SMP0_1,
    /*!< Sampling time 762 ADC clock cycles */
    ADC_SAMPLINGTIME_1530CYCLES    = ADC_SMPR0_SMP0_2 | ADC_SMPR0_SMP0_1 | ADC_SMPR0_SMP0_0,
    /*!< Sampling time 1530 ADC clock cycles */
} ADC_SampTimeETypeDef;

/**
  * @brief ADC CALCULATE OFFST GROUP SELECT
  */
typedef enum {
    ADC_CAL_OFFSET_GROUP0        = 0x0,
    /*ADC calibration offset/gain register gruop 0 -- OFR0*/
    ADC_CAL_OFFSET_GROUP1        = ADC_CALR0_CAL0_0,
    /*ADC calibration offset/gain register gruop 1 -- OFR1*/
    ADC_CAL_OFFSET_GROUP2        =  ADC_CALR0_CAL0_1,
    /*ADC calibration offset/gain register gruop 2 -- OFR2*/
    ADC_CAL_OFFSET_GROUP3        =  ADC_CALR0_CAL0_1 | ADC_CALR0_CAL0_0,
    /*ADC calibration offset/gain register gruop 3 -- OFR3*/
} ADC_CalrGroupETypeDef;

/**
  * @brief  Trigger edge
  */
typedef enum {
    LL_ADC_REG_TRIG_SOFT            = 0x0,
    /*!< ADC group regular conversion software trigger */
    ADC_REG_TRIG_EXT_RISING         = ADC_LR_EXTEN_0,
    /*!< ADC group regular conversion trigger polarity set to rising edge */
    ADC_REG_TRIG_EXT_FALLING        = ADC_LR_EXTEN_1,
    /*!< ADC group regular conversion trigger polarity set to falling edge */
    ADC_REG_TRIG_EXT_RISINGFALLING  = ADC_LR_EXTEN_1 | ADC_LR_EXTEN_0,
    /*!< ADC group regular conversion trigger polarity set to both rising and falling edges */
} ADC_RegTrigEdgeETypeDef;

/**
  * @brief Continuous mode
  */
typedef enum {
    ADC_REG_CONV_SINGLE          = 0x0,
    /*!< ADC conversions are performed in single mode: one conversion per trigger */
    ADC_REG_CONV_CONTINUOUS      = ADC_CR1_CONT,
    /*!< ADC conversions are performed in continuous mode: after the first trigger,
     following conversions launched successively automatically */
} ADC_RegConvModeETypeDef;

/**
  * @brief Overrun behavior on conversion data
  */
typedef enum {
    ADC_OVR_DATA_PRESERVED      = 0x0,
    /*!< ADC group regular behavior in case of overrun: data preserved */
    ADC_OVR_DATA_OVERWRITTEN    = ADC_CR1_OVRMOD,
    /*!< ADC group regular behavior in case of overrun: data overwritten */
} ADC_OverRunModeETypeDef;

/**
  * @brief Sequencer discontinuous mode
  */
typedef enum {
    ADC_REG_SEQ_DISCON_DISABLE     = 0x0,
    /*!< ADC group regular sequencer discontinuous mode disable */
    ADC_REG_SEQ_DISNUM_1RANK       = ADC_CR1_DISCEN,
    /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every rank */
    ADC_REG_SEQ_DISNUM_2RANKS      = ADC_CR1_DISCNUM_0 | ADC_CR1_DISCEN,
    /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 2 ranks */
    ADC_REG_SEQ_DISNUM_3RANKS      = ADC_CR1_DISCNUM_1 | ADC_CR1_DISCEN,
    /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 3 ranks */
    ADC_REG_SEQ_DISNUM_4RANKS      = ADC_CR1_DISCNUM_1 | ADC_CR1_DISCNUM_0 | ADC_CR1_DISCEN,
    /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 4 ranks */
    ADC_REG_SEQ_DISNUM_5RANKS      = ADC_CR1_DISCNUM_2 | ADC_CR1_DISCEN,
    /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 5 ranks */
    ADC_REG_SEQ_DISNUM_6RANKS      = ADC_CR1_DISCNUM_2 | ADC_CR1_DISCNUM_0 | ADC_CR1_DISCEN,
    /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 6 ranks */
    ADC_REG_SEQ_DISNUM_7RANKS      = ADC_CR1_DISCNUM_2 | ADC_CR1_DISCNUM_1 | ADC_CR1_DISCEN,
    /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 7 ranks */
    ADC_REG_SEQ_DISNUM_8RANKS      = ADC_CR1_DISCNUM_2 | ADC_CR1_DISCNUM_1 | ADC_CR1_DISCNUM_0 | ADC_CR1_DISCEN,
    /*!< ADC group regular sequencer discontinuous mode enable with sequence interruption every 8 ranks */
} ADC_RegDiscontETypeDef;

/**
  * @brief Sequencer length
  */
typedef enum {
    ADC_REG_SEQ_LENGTH_1        = 0x0,
    /*!< ADC group regular sequencer disable (equivalent to sequencer of 1 rank: ADC conversion on only 1 channel) */
    ADC_REG_SEQ_LENGTH_2        = ADC_LR_LEN_0,
    /*!< ADC group regular sequencer enable with 2 ranks in the sequence */
    ADC_REG_SEQ_LENGTH_3        = ADC_LR_LEN_1,
    /*!< ADC group regular sequencer enable with 3 ranks in the sequence */
    ADC_REG_SEQ_LENGTH_4        = ADC_LR_LEN_1 | ADC_LR_LEN_0,
    /*!< ADC group regular sequencer enable with 4 ranks in the sequence */
    ADC_REG_SEQ_LENGTH_5        = ADC_LR_LEN_2,
    /*!< ADC group regular sequencer enable with 5 ranks in the sequence */
    ADC_REG_SEQ_LENGTH_6        = ADC_LR_LEN_2 | ADC_LR_LEN_0,
    /*!< ADC group regular sequencer enable with 6 ranks in the sequence */
    ADC_REG_SEQ_LENGTH_7        = ADC_LR_LEN_2 | ADC_LR_LEN_1,
    /*!< ADC group regular sequencer enable with 7 ranks in the sequence */
    ADC_REG_SEQ_LENGTH_8        = ADC_LR_LEN_2 | ADC_LR_LEN_1 | ADC_LR_LEN_0,
    /*!< ADC group regular sequencer enable with 8 ranks in the sequence */
    ADC_REG_SEQ_LENGTH_9        = ADC_LR_LEN_3,
    /*!< ADC group regular sequencer enable with 9 ranks in the sequence */
    ADC_REG_SEQ_LENGTH_10       = ADC_LR_LEN_3 | ADC_LR_LEN_0,
    /*!< ADC group regular sequencer enable with 10 ranks in the sequence */
    ADC_REG_SEQ_LENGTH_11       = ADC_LR_LEN_3 | ADC_LR_LEN_1,
    /*!< ADC group regular sequencer enable with 11 ranks in the sequence */
    ADC_REG_SEQ_LENGTH_12       = ADC_LR_LEN_3 | ADC_LR_LEN_1 | ADC_LR_LEN_0,
    /*!< ADC group regular sequencer enable with 12 ranks in the sequence */
    ADC_REG_SEQ_LENGTH_13       = ADC_LR_LEN_3 | ADC_LR_LEN_2,
    /*!< ADC group regular sequencer enable with 13 ranks in the sequence */
    ADC_REG_SEQ_LENGTH_14       = ADC_LR_LEN_3 | ADC_LR_LEN_2 | ADC_LR_LEN_0,
    /*!< ADC group regular sequencer enable with 14 ranks in the sequence */
    ADC_REG_SEQ_LENGTH_15       = ADC_LR_LEN_3 | ADC_LR_LEN_2 | ADC_LR_LEN_1,
    /*!< ADC group regular sequencer enable with 15 ranks in the sequence */
    ADC_REG_SEQ_LENGTH_16       = ADC_LR_LEN_3 | ADC_LR_LEN_2 | ADC_LR_LEN_1 | ADC_LR_LEN_0,
    /*!< ADC group regular sequencer enable with 16 ranks in the sequence */
} ADC_RegSeqLengthETypeDef;

/**
  * @brief Sequencer ranks
  */
typedef enum {
    ADC_REG_RANK_1             = 0x0UL,
    /*!< ADC group regular sequencer rank 1 */
    ADC_REG_RANK_2             = 0x1UL,
    /*!< ADC group regular sequencer rank 2 */
    ADC_REG_RANK_3             = 0x2UL,
    /*!< ADC group regular sequencer rank 3 */
    ADC_REG_RANK_4             = 0x3UL,
    /*!< ADC group regular sequencer rank 4 */
    ADC_REG_RANK_5             = 0x4UL,
    /*!< ADC group regular sequencer rank 5 */
    ADC_REG_RANK_6             = 0x5UL,
    /*!< ADC group regular sequencer rank 6 */
    ADC_REG_RANK_7             = 0x6UL,
    /*!< ADC group regular sequencer rank 7 */
    ADC_REG_RANK_8             = 0x7UL,
    /*!< ADC group regular sequencer rank 8 */
    ADC_REG_RANK_9             = 0x8UL,
    /*!< ADC group regular sequencer rank 9 */
    ADC_REG_RANK_10            = 0x9UL,
    /*!< ADC group regular sequencer rank 10 */
    ADC_REG_RANK_11            = 0xAUL,
    /*!< ADC group regular sequencer rank 11 */
    ADC_REG_RANK_12            = 0xBUL,
    /*!< ADC group regular sequencer rank 12 */
    ADC_REG_RANK_13            = 0xCUL,
    /*!< ADC group regular sequencer rank 13 */
    ADC_REG_RANK_14            = 0xDUL,
    /*!< ADC group regular sequencer rank 14 */
    ADC_REG_RANK_15            = 0xEUL,
    /*!< ADC group regular sequencer rank 15 */
    ADC_REG_RANK_16            = 0xFUL,
    /*!< ADC group regular sequencer rank 16 */
} ADC_RegSeqRankETypeDef;

/**
  * @brief Trigger source
  */
typedef enum {
    ADC_REG_TRIG_SOFTWARE               = 0x0,
    /*!<ADC group regular conversion trigger internal: SW start. */
    ADC_REG_TRIG_EXT_TIM0_CC            = ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: TIM0 CC(capture compare: input capture or output capture). Trigger edge set to rising edge*/
    ADC_REG_TRIG_EXT_TIM1_CC            = ADC_LR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: TIM1 CC(capture compare: input capture or output capture). Trigger edge set to rising edge*/
    ADC_REG_TRIG_EXT_TIM2_CC            = ADC_LR_EXTSEL_1 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: TIM2 CC(capture compare: input capture or output capture). Trigger edge set to rising edge*/
    ADC_REG_TRIG_EXT_TIM3_CC            = ADC_LR_EXTSEL_1 | ADC_LR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: TIM3 CC(capture compare: input capture or output capture). Trigger edge set to rising edge*/
    ADC_REG_TRIG_EXT_TIM4_CC            = ADC_LR_EXTSEL_2 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: TIM4 CC(capture compare: input capture or output capture). Trigger edge set to rising edge*/
    ADC_REG_TRIG_EXT_TIM5_CC            = ADC_LR_EXTSEL_2 | ADC_LR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: TIM5 CC(capture compare: input capture or output capture). Trigger edge set to rising edge*/
    ADC_REG_TRIG_EXT_TIM6_CC            = ADC_LR_EXTSEL_2 | ADC_LR_EXTSEL_1 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: TIM6 CC(capture compare: input capture or output capture). Trigger edge set to rising edge*/
    ADC_REG_TRIG_EXT_TIM7_CC            = ADC_LR_EXTSEL_2 | ADC_LR_EXTSEL_1 | ADC_LR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: TIM7 CC(capture compare: input capture or output capture). Trigger edge set to rising edge*/
    ADC_REG_TRIG_EXT_TIM0_TRGO          = ADC_LR_EXTSEL_3 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: TIM0 TRGO. Trigger edge set to rising edge (default setting). */
    ADC_REG_TRIG_EXT_TIM1_TRGO          = ADC_LR_EXTSEL_3 | ADC_LR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: TIM1 TRGO. Trigger edge set to rising edge (default setting). */
    ADC_REG_TRIG_EXT_TIM2_TRGO          = ADC_LR_EXTSEL_3 | ADC_LR_EXTSEL_1 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: TIM2 TRGO. Trigger edge set to rising edge (default setting). */
    ADC_REG_TRIG_EXT_TIM3_TRGO          = ADC_LR_EXTSEL_3 | ADC_LR_EXTSEL_1 | ADC_LR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: TIM3 TRGO. Trigger edge set to rising edge (default setting). */
    ADC_REG_TRIG_EXT_TIM4_TRGO          = ADC_LR_EXTSEL_3 | ADC_LR_EXTSEL_2 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: TIM4 TRGO. Trigger edge set to rising edge (default setting). */
    ADC_REG_TRIG_EXT_TIM5_TRGO          = ADC_LR_EXTSEL_3 | ADC_LR_EXTSEL_2 | ADC_LR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: TIM5 TRGO. Trigger edge set to rising edge (default setting). */
    ADC_REG_TRIG_EXT_TIM6_TRGO          = ADC_LR_EXTSEL_3 | ADC_LR_EXTSEL_2 | ADC_LR_EXTSEL_1 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: TIM6 TRGO. Trigger edge set to rising edge (default setting). */
    ADC_REG_TRIG_EXT_TIM7_TRGO          = ADC_LR_EXTSEL_3 | ADC_LR_EXTSEL_2 | ADC_LR_EXTSEL_1 | ADC_LR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: TIM7 TRGO. Trigger edge set to rising edge (default setting). */
    ADC_REG_TRIG_EXT_HRPWM_ADC_TRG0     = ADC_LR_EXTSEL_4 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: HRPWM_ADC_TRG0. Trigger edge set to rising edge (default setting). */
    ADC_REG_TRIG_EXT_HRPWM_ADC_TRG1     = ADC_LR_EXTSEL_4 | ADC_LR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: HRPWM_ADC_TRG1. Trigger edge set to rising edge (default setting). */
    ADC_REG_TRIG_EXT_HRPWM_ADC_TRG2     = ADC_LR_EXTSEL_4 | ADC_LR_EXTSEL_1 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: HRPWM_ADC_TRG2. Trigger edge set to rising edge (default setting). */
    ADC_REG_TRIG_EXT_HRPWM_ADC_TRG3     = ADC_LR_EXTSEL_4 | ADC_LR_EXTSEL_1 | ADC_LR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: HRPWM_ADC_TRG3. Trigger edge set to rising edge (default setting). */
    ADC_REG_TRIG_EXT_HRPWM_ADC_TRG4     = ADC_LR_EXTSEL_4 | ADC_LR_EXTSEL_2 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: HRPWM_ADC_TRG4. Trigger edge set to rising edge (default setting). */
    ADC_REG_TRIG_EXT_HRPWM_ADC_TRG5     = ADC_LR_EXTSEL_4 | ADC_LR_EXTSEL_2 | ADC_LR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: HRPWM_ADC_TRG5. Trigger edge set to rising edge (default setting). */
    ADC_REG_TRIG_EXT_HRPWM_ADC_TRG6     = ADC_LR_EXTSEL_4 | ADC_LR_EXTSEL_2 | ADC_LR_EXTSEL_1 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: HRPWM_ADC_TRG6. Trigger edge set to rising edge (default setting). */
    ADC_REG_TRIG_EXT_HRPWM_ADC_TRG7     = ADC_LR_EXTSEL_4 | ADC_LR_EXTSEL_2 | ADC_LR_EXTSEL_1 | ADC_LR_EXTSEL_0 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: HRPWM_ADC_TRG7. Trigger edge set to rising edge (default setting). */
    ADC_REG_TRIG_EXT_PIN                = ADC_LR_EXTSEL_4 | ADC_LR_EXTSEL_3 | ADC_REG_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group regular conversion trigger from external peripheral: external GPIO PIN: PA8. Trigger edge set to rising edge (default setting). */
} ADC_RegExtTrigSrcETypeDef;

/**
  * @brief Trigger edge
  */
typedef enum {
    ADC_INJ_TRIG_EXT_RISING         = ADC_JLR_JEXTEN_0,
    /*!< ADC group injected conversion trigger polarity set to rising edge */
    ADC_INJ_TRIG_EXT_FALLING        = ADC_JLR_JEXTEN_1,
    /*!< ADC group injected conversion trigger polarity set to falling edge */
    ADC_INJ_TRIG_EXT_RISINGFALLING  = ADC_JLR_JEXTEN_1 | ADC_JLR_JEXTEN_0,
    /*!< ADC group injected conversion trigger polarity set to both rising and falling edges */
} ADC_InjExtTrigEdgeETypeDef;

/**
  * @brief Automatic trigger mode
  */
typedef enum {
    ADC_INJ_TRIG_INDEPENDENT       = 0x0,
    /*!< ADC group injected conversion trigger independent. Setting mandatory if ADC group injected injected trigger source is set to an external trigger.      */
    ADC_INJ_TRIG_FROM_GRP_REGULAR  = ADC_CR1_JAUTO,
    /*!< ADC group injected conversion trigger from ADC group regular. Setting compliant only with group injected trigger source set to SW start,
      without any further action on  ADC group injected conversion start or stop: in this case, ADC group injected is controlled only from ADC group regular.   */
} ADC_InjAutoTrigETypeDef;

/**
  * @brief Sequencer scan length
  */
typedef enum {
    ADC_INJ_SEQ_LENGTH_1        = 0x0,
    /*!< ADC group injected sequencer disable (equivalent to sequencer of 1 rank: ADC conversion on only 1 channel) */
    ADC_INJ_SEQ_LENGTH_2        = ADC_JLR_JLEN_0,
    /*!< ADC group injected sequencer enable with 2 ranks in the sequence */
    ADC_INJ_SEQ_LENGTH_3        = ADC_JLR_JLEN_1,
    /*!< ADC group injected sequencer enable with 3 ranks in the sequence */
    ADC_INJ_SEQ_LENGTH_4        = ADC_JLR_JLEN_1 | ADC_JLR_JLEN_0,
    /*!< ADC group injected sequencer enable with 4 ranks in the sequence */
} ADC_InjSeqLengthETypeDef;

/**
  * @brief Sequencer ranks
  */
typedef enum {
    ADC_INJ_RANK_1            = ADC_JSQR_JSQ1_Pos,
    /*!< ADC group injected sequencer position 1 */
    ADC_INJ_RANK_2            = ADC_JSQR_JSQ2_Pos,
    /*!< ADC group injected sequencer position 2 */
    ADC_INJ_RANK_3            = ADC_JSQR_JSQ3_Pos,
    /*!< ADC group injected sequencer position 3 */
    ADC_INJ_RANK_4            = ADC_JSQR_JSQ4_Pos,
    /*!< ADC group injected sequencer position 4 */
} ADC_InjSeqRankETypeDef;

/**
  * @brief Sequencer discontinuous mode
  */
typedef enum {
    ADC_INJ_SEQ_DISCONT_DISABLE     = 0x0,
    /*!< ADC group injected sequencer discontinuous mode disable */
    ADC_INJ_SEQ_DISCONT_ENABLE      = ADC_CR1_JDISCEN,
    /*!< ADC group injected sequencer discontinuous mode enable with sequence interruption every rank */
} ADC_InjDiscontEnETypeDef;

/**
  * @brief Trigger source
  */
typedef enum {
    ADC_INJ_TRIG_SOFTWARE               = 0x0,
    /*!<ADC group injected conversion trigger internal: SW start. */
    ADC_INJ_TRIG_EXT_TIM0_CC            = ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: TIM0 CC(capture compare: input capture or output capture). Trigger edge set to rising edge*/
    ADC_INJ_TRIG_EXT_TIM1_CC            = ADC_JLR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: TIM1 CC(capture compare: input capture or output capture). Trigger edge set to rising edge*/
    ADC_INJ_TRIG_EXT_TIM2_CC            = ADC_JLR_JEXTSEL_1 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: TIM2 CC(capture compare: input capture or output capture). Trigger edge set to rising edge*/
    ADC_INJ_TRIG_EXT_TIM3_CC            = ADC_JLR_JEXTSEL_1 | ADC_JLR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: TIM3 CC(capture compare: input capture or output capture). Trigger edge set to rising edge*/
    ADC_INJ_TRIG_EXT_TIM4_CC            = ADC_JLR_JEXTSEL_2 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: TIM4 CC(capture compare: input capture or output capture). Trigger edge set to rising edge*/
    ADC_INJ_TRIG_EXT_TIM5_CC            = ADC_JLR_JEXTSEL_2 | ADC_JLR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: TIM5 CC(capture compare: input capture or output capture). Trigger edge set to rising edge*/
    ADC_INJ_TRIG_EXT_TIM6_CC            = ADC_JLR_JEXTSEL_2 | ADC_JLR_JEXTSEL_1 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: TIM6 CC(capture compare: input capture or output capture). Trigger edge set to rising edge*/
    ADC_INJ_TRIG_EXT_TIM7_CC            = ADC_JLR_JEXTSEL_2 | ADC_JLR_JEXTSEL_1 | ADC_JLR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: TIM7 CC(capture compare: input capture or output capture). Trigger edge set to rising edge*/
    ADC_INJ_TRIG_EXT_TIM0_TRGO          = ADC_JLR_JEXTSEL_3 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: TIM0 TRGO. Trigger edge set to rising edge (default setting). */
    ADC_INJ_TRIG_EXT_TIM1_TRGO          = ADC_JLR_JEXTSEL_3 | ADC_JLR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: TIM1 TRGO. Trigger edge set to rising edge (default setting). */
    ADC_INJ_TRIG_EXT_TIM2_TRGO          = ADC_JLR_JEXTSEL_3 | ADC_JLR_JEXTSEL_1 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: TIM2 TRGO. Trigger edge set to rising edge (default setting). */
    ADC_INJ_TRIG_EXT_TIM3_TRGO          = ADC_JLR_JEXTSEL_3 | ADC_JLR_JEXTSEL_1 | ADC_JLR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: TIM3 TRGO. Trigger edge set to rising edge (default setting). */
    ADC_INJ_TRIG_EXT_TIM4_TRGO          = ADC_JLR_JEXTSEL_3 | ADC_JLR_JEXTSEL_2 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: TIM4 TRGO. Trigger edge set to rising edge (default setting). */
    ADC_INJ_TRIG_EXT_TIM5_TRGO          = ADC_JLR_JEXTSEL_3 | ADC_JLR_JEXTSEL_2 | ADC_JLR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: TIM5 TRGO. Trigger edge set to rising edge (default setting). */
    ADC_INJ_TRIG_EXT_TIM6_TRGO          = ADC_JLR_JEXTSEL_3 | ADC_JLR_JEXTSEL_2 | ADC_JLR_JEXTSEL_1 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: TIM6 TRGO. Trigger edge set to rising edge (default setting). */
    ADC_INJ_TRIG_EXT_TIM7_TRGO          = ADC_JLR_JEXTSEL_3 | ADC_JLR_JEXTSEL_2 | ADC_JLR_JEXTSEL_1 | ADC_JLR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: TIM7 TRGO. Trigger edge set to rising edge (default setting). */
    ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG0     = ADC_JLR_JEXTSEL_4 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: HRPWM_ADC_TRG0. Trigger edge set to rising edge (default setting). */
    ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG1     = ADC_JLR_JEXTSEL_4 | ADC_JLR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: HRPWM_ADC_TRG1. Trigger edge set to rising edge (default setting). */
    ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG2     = ADC_JLR_JEXTSEL_4 | ADC_JLR_JEXTSEL_1 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: HRPWM_ADC_TRG2. Trigger edge set to rising edge (default setting). */
    ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG3     = ADC_JLR_JEXTSEL_4 | ADC_JLR_JEXTSEL_1 | ADC_JLR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: HRPWM_ADC_TRG3. Trigger edge set to rising edge (default setting). */
    ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG4     = ADC_JLR_JEXTSEL_4 | ADC_JLR_JEXTSEL_2 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: HRPWM_ADC_TRG4. Trigger edge set to rising edge (default setting). */
    ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG5     = ADC_JLR_JEXTSEL_4 | ADC_JLR_JEXTSEL_2 | ADC_JLR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: HRPWM_ADC_TRG5. Trigger edge set to rising edge (default setting). */
    ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG6     = ADC_JLR_JEXTSEL_4 | ADC_JLR_JEXTSEL_2 | ADC_JLR_JEXTSEL_1 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: HRPWM_ADC_TRG6. Trigger edge set to rising edge (default setting). */
    ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG7     = ADC_JLR_JEXTSEL_4 | ADC_JLR_JEXTSEL_2 | ADC_JLR_JEXTSEL_1 | ADC_JLR_JEXTSEL_0 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: HRPWM_ADC_TRG7. Trigger edge set to rising edge (default setting). */
    ADC_INJ_TRIG_EXT_PIN                = ADC_JLR_JEXTSEL_4 | ADC_JLR_JEXTSEL_3 | ADC_INJ_TRIG_EXT_EDGE_DEFAULT,
    /*!<ADC group injected conversion trigger from external peripheral: external GPIO PIN: PA9. Trigger edge set to rising edge (default setting). */
} ADC_InjExtTrigSrcETypeDef;

/**
  * @brief Single or differential ending
  */
typedef enum {
    ADC_DIFSEL_DIFFER          = 0x1UL,
    /*!< ADC the channel works in differential input mode*/
    ADC_DIFSEL_SINGLE          = 0x0UL,
    /*!< ADC the channel works in single input mode*/
} ADC_DiffSelETypeDef;

/**
  * @brief select ecu group
  */
typedef enum {
    ADC_ECR_GROUP0            = 0x0UL,
    /*!< Select the first set of registers associated with the ECU  -- ECR0*/
    ADC_ECR_GROUP1            = 0x1UL,
    /*!< Select the second set of registers associated with the ECU  -- ECR1*/
    ADC_ECR_GROUP2            = 0x2UL,
    /*!< Select the third set of registers associated with the ECU  -- ECR2*/
    ADC_ECR_GROUP3            = 0x3UL,
    /*!< Select the forth set of registers associated with the ECU  -- ECR3*/
} ADC_EcuGroupETypeDef;

/**
  * @brief ADC CALIB GROUP
  */
typedef enum {
    ADC_CALIB_GROUP0          = 0x0UL,
    ADC_CALIB_GROUP1          = 0x1UL,
    ADC_CALIB_GROUP2          = 0x2UL,
    ADC_CALIB_GROUP3          = 0x3UL,
} ADC_CalibGroupETypeDef;

/**
  * @brief Analog watchdog number
  */
typedef enum {
    ADC_AWD0               = 0x0UL,
    ADC_AWD1               = 0x1UL,
    ADC_AWD2               = 0x2UL,
} ADC_AnologWDETypeDef;

/**
  * @brief Analog watchdog Thresholds
  */
typedef enum {
    ADC_AWD_THRESHOLD_HIGH          = (int32_t)ADC_TR1_HT1,
    /*!< ADC analog watchdog threshold high */
    ADC_AWD_THRESHOLD_LOW           = ADC_TR1_LT1,
    /*!< ADC analog watchdog threshold low */
    ADC_AWD_THRESHOLDS_HIGH_LOW     = (int32_t)(ADC_TR1_HT1 | ADC_TR1_LT1),
    /*!< ADC analog watchdog both thresholds high and low concatenated into the same data */
} ADC_AnologThresholdETypeDef;

/**
  * @brief Analog watchdog filtering config
  */
typedef enum {
    ADC_AWD_FILTERING_NONE    = 0x0,
    /*!< ADC analog wathdog no filtering, one out-of-window sample is needed to raise flag */
    ADC_AWD_FILTERING_1       = ADC_AWD0CR_AWD0FILT_0,
    /*!< ADC analog wathdog 2 consecutives out-of-window samples are needed to raise flag  */
    ADC_AWD_FILTERING_2       = ADC_AWD0CR_AWD0FILT_1,
    /*!< ADC analog wathdog 3 consecutives out-of-window samples are needed to raise flag  */
    ADC_AWD_FILTERING_3       = ADC_AWD0CR_AWD0FILT_1 | ADC_AWD0CR_AWD0FILT_0,
    /*!< ADC analog wathdog 4 consecutives out-of-window samples are needed to raise flag  */
    ADC_AWD_FILTERING_4       = ADC_AWD0CR_AWD0FILT_2,
    /*!< ADC analog wathdog 5 consecutives out-of-window samples are needed to raise flag  */
    ADC_AWD_FILTERING_5       = ADC_AWD0CR_AWD0FILT_2 | ADC_AWD0CR_AWD0FILT_0,
    /*!< ADC analog wathdog 6 consecutives out-of-window samples are needed to raise flag  */
    ADC_AWD_FILTERING_6       = ADC_AWD0CR_AWD0FILT_2 | ADC_AWD0CR_AWD0FILT_1,
    /*!< ADC analog wathdog 7 consecutives out-of-window samples are needed to raise flag  */
    ADC_AWD_FILTERING_7       = ADC_AWD0CR_AWD0FILT_2 | ADC_AWD0CR_AWD0FILT_1 | ADC_AWD0CR_AWD0FILT_0,
    /*!< ADC analog wathdog 8 consecutives out-of-window samples are needed to raise flag  */
    ADC_AWD_FILTERING_8       = ADC_AWD0CR_AWD0FILT_3,
    /*!< ADC analog wathdog 9 consecutives out-of-window samples are needed to raise flag  */
    ADC_AWD_FILTERING_9       = ADC_AWD0CR_AWD0FILT_3 | ADC_AWD0CR_AWD0FILT_0,
    /*!< ADC analog wathdog 10 consecutives out-of-window samples are needed to raise flag */
    ADC_AWD_FILTERING_10      = ADC_AWD0CR_AWD0FILT_3 | ADC_AWD0CR_AWD0FILT_1,
    /*!< ADC analog wathdog 11 consecutives out-of-window samples are needed to raise flag */
    ADC_AWD_FILTERING_11      = ADC_AWD0CR_AWD0FILT_3 | ADC_AWD0CR_AWD0FILT_1 | ADC_AWD0CR_AWD0FILT_0,
    /*!< ADC analog wathdog 12 consecutives out-of-window samples are needed to raise flag */
    ADC_AWD_FILTERING_12      = ADC_AWD0CR_AWD0FILT_3 | ADC_AWD0CR_AWD0FILT_2,
    /*!< ADC analog wathdog 13 consecutives out-of-window samples are needed to raise flag */
    ADC_AWD_FILTERING_13      = ADC_AWD0CR_AWD0FILT_3 | ADC_AWD0CR_AWD0FILT_2 | ADC_AWD0CR_AWD0FILT_0,
    /*!< ADC analog wathdog 14 consecutives out-of-window samples are needed to raise flag */
    ADC_AWD_FILTERING_14      = ADC_AWD0CR_AWD0FILT_3 | ADC_AWD0CR_AWD0FILT_2 | ADC_AWD0CR_AWD0FILT_1,
    /*!< ADC analog wathdog 15 consecutives out-of-window samples are needed to raise flag */
    ADC_AWD_FILTERING_15      = ADC_AWD0CR_AWD0FILT_3 | ADC_AWD0CR_AWD0FILT_2 | ADC_AWD0CR_AWD0FILT_1 | ADC_AWD0CR_AWD0FILT_0,
    /*!< ADC analog wathdog 16 consecutives out-of-window samples are needed to raise flag */
} ADC_AnologWDFliterETypeDef;

/**
  * @brief ADC Transfer data mode set ADC_DMA_CR->TCR
  */
typedef enum {
    ADC_REG_DMA_TRANSFER_DISABLE   = 0x0,
    ADC_REG_DMA_TRANSFER_SINGLE    = ADC_DMA_TCR_START,
    ADC_REG_DMA_TRANSFER_CIRCLE    = ADC_DMA_TCR_CIRC | ADC_DMA_TCR_START,
} ADC_DMATransferModeETypeDef;

/**
  * @brief ADC instance Channel number
  */
typedef enum {
    ADC_CHANNEL_0               = 0UL,
    /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN0  */
    ADC_CHANNEL_1               = 1UL,
    /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN1  */
    ADC_CHANNEL_2               = 2UL,
    /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN2  */
    ADC_CHANNEL_3               = 3UL,
    /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN3  */
    ADC_CHANNEL_4               = 4UL,
    /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN4  */
    ADC_CHANNEL_5               = 5UL,
    /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN5  */
    ADC_CHANNEL_6               = 6UL,
    /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN6  */
    ADC_CHANNEL_7               = 7UL,
    /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN7  */
    ADC_CHANNEL_8               = 8UL,
    /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN8  */
    ADC_CHANNEL_9               = 9UL,
    /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN9  */
    ADC_CHANNEL_10              = 10UL,
    /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN10 */
    ADC_CHANNEL_TEMPSENSOR      = 11UL,
    /*!< ADC external channel (channel connected to GPIO pin) ADCx_IN11 */
} ADC_ChannelSelETypeDef;


/**
  * @brief ADC group regular oversampling structure definition
  */
typedef struct __ADC_OversamplingTypeDef {
    ADC_OverSampROVSMETypeDef OverSampResetMode;    /*!< Set ADC over sample reset mode,only regular group is valid */
    ADC_OverSampTROVSETypeDef TrigOverSamp;         /*!< Set ADC trigger over sample                                */
    ADC_OverSampShiftETypeDef OverSampShiftBit;     /*!< Set ADC over sample shift bit                              */
    ADC_OverSampRatioETypeDef OverSampRatio;        /*!< Set ADC over sample ratio                                  */
} ADC_OversamplingTypeDef;

/** @defgroup LL_ADC_INIT ADC Exported Init structure
  * @brief    Structure definition of some features of ADC instance.
  * @note     These parameters have an impact on ADC scope: ADC instance.
  *           Affects both group regular and group injected.
  *           Refer to corresponding unitary functions into
  * @note     The setting of these parameters by function reference LL_ADC_Init()
  *           is conditioned to ADC state:
  *           ADC instance must be disabled.
  */
typedef struct __ADC_InitTypeDef {
    uint32_t NormInterrupt;                     /*!< Set ADC Normal interrupt paramter cconfig.
                                                    This parameter can be combination value of reference LL_ADC_IT                      */
    ADC_SyncEnETypeDef      Synchronization;    /*!< Set ADC synchronization                                                            */
    ADC_AnologCtlETypeDef   AnologCfg;          /*!< Set ADC anolog paramter cconfig                                                    */
    ADC_OverRunModeETypeDef Overrun;            /*!< Set ADC group regular behavior in case of overrun: data preserved or overwritten   */
    LL_FuncStatusETypeDef   RegOversampMode;    /*!< Specify whether the regular group oversampling feature is enabled or disabled      */
    LL_FuncStatusETypeDef   InjOversampMode;    /*!< Specify whether the injected group oversampling feature is enabled or disabled     */
    ADC_OversamplingTypeDef OverSampling;       /*!< Specify the Oversampling parameters.Caution:  this setting overwrites the
                                                    previous oversampling configuration if oversampling is already enabled.             */
} ADC_InitTypeDef;

/**
  * @brief  Structure definition of some features of ADC group regular.
  * @note   These parameters have an impact on ADC scope: ADC group regular.
  *         Refer to corresponding unitary functions into
  *         (functions with prefix "REG").
  */
typedef struct __ADC_REG_InitTypeDef {
    ADC_ChannelSelETypeDef Channel;             /*!< Set ADC group regular conversion Channel.                                      */
    LL_FuncStatusETypeDef SampInterrupt;        /*!< Configures the ADC conversion Channel Sample interrupt.                        */
    ADC_RegSeqRankETypeDef SequencerPos;        /*!< Set SQR is configured in combination with length for the number of conversions */
    ADC_RegExtTrigSrcETypeDef TriggerSource;    /*!< Set ADC group regular conversion trigger source: internal (SW start)
                                                    or from external peripheral(timer event,hrpwm trigger , up edge).               */
    ADC_RegSeqLengthETypeDef SequencerLength;   /*!< Set ADC group regular sequencer length.                                        */
    ADC_RegDiscontETypeDef SequencerDiscont;    /*!< Set ADC group regular sequencer discontinuous mode: sequence subdivided
                                                     and scan conversions interrupted every selected number of ranks.               */
    ADC_RegConvModeETypeDef ContinuousMode;     /*!< Set ADC continuous conversion mode on ADC group regular, whether ADC
                                                    conversions are performedin single mode (one conversion per trigger). or in
                                                    continuous mode (after the first trigger,following conversions launched
                                                    successively automatically).                                                    */
    ADC_DiffSelETypeDef DifferSel;              /*!< Set ADC group regular channel is differential or single mode                   */
    ADC_SampTimeETypeDef SampTimClk;            /*!< Set ADC group regular channel sample clk length                                */
} ADC_REG_InitTypeDef;

/**
  * @brief  Structure definition of some features of ADC group injected.
  * @note   These parameters have an impact on ADC scope: ADC group injected.
  *         (functions with prefix "INJ").
  */
typedef struct __ADC_INJ_InitTypeDef {
    ADC_ChannelSelETypeDef Channel;            /*!< Set ADC group injected conversion Channel.                                          */
    ADC_InjSeqRankETypeDef SequencerPos;       /*!< Set JSQR is configured in combination with length for the number of 
                                                conversions the channel is placed on.                                                   */
    ADC_InjExtTrigSrcETypeDef TriggerSource;   /*!< Set ADC group injected conversion trigger source: internal (SW start)
                                                 or from external peripheral (timer event, external interrupt line).                    */
    ADC_InjSeqLengthETypeDef SequencerLength;  /*!< Set ADC group injected sequencer length.                                            */
    ADC_InjDiscontEnETypeDef SequencerDiscont; /*!< Set ADC group injected sequencer discontinuous mode: sequence 
                                                subdivided and scan conversions interrupted every selected number of ranks.             */
    ADC_InjAutoTrigETypeDef TrigAuto;          /*!< Set ADC group injected conversion trigger: independent or from ADC group regular.   */

} ADC_INJ_InitTypeDef;

/**
  * @brief  Structure definition of some features of ADC to ECU.
  * @note   These parameters have an impact on ADC scope: ADC to ECU.
  *         Electric quantity parameter calculation configuration.
  */
typedef struct __ADC_ECUConfTypeDef {
    ADC_EcuGroupETypeDef   GroupSel;            /*!< Each ADC has four sets of ECU configurations, and the ECU is divided into four events. */
    ADC_ChannelSelETypeDef AddrDataSel;         /*!< Set ADC to ECU: The ECU fetches data from the channel address of the ADC .             */
    ADC_AnologWDETypeDef   PingPongUpZero;      /*!< Set Sinusoidal wave above zero detection of the selected watchdog.                     */
    ADC_AnologWDETypeDef   PingPongDownZero;    /*!< SetSinusoidal wave down through zero detection of the selected watchdog.               */
    ADC_ChannelSelETypeDef AWD2SourceSel;       /*!< Set Watchdog 2 monitors channel sources.                                               */
    ADC_ChannelSelETypeDef AWD1SourceSel;       /*!< Set Watchdog 1 monitors channel sources.                                               */
    ADC_ChannelSelETypeDef AWD0SourceSel;       /*!< Set Watchdog 0 monitors channel sources.                                               */
} ADC_ECUConfTypeDef;

/**
  * @brief  Structure definition of ADC analog watchdog
  * @note   The setting of these parameters by function HAL_ADC_AnalogWDGConfig() is conditioned to ADC state.
  *         ADC state can be either:
  *          - For all parameters except 'HighThreshold', 'LowThreshold': ADC disabled or ADC enabled without conversion on going
  *           on ADC groups regular and injected.
  *          - For parameters 'HighThreshold', 'LowThreshold': ADC enabled with conversion on going on regular and injected groups.
  */
typedef struct __ADC_AnalogWDGCfgTypeDef {

    uint32_t Channel;                     /*!< Select which ADC channel to monitor by analog watchdog.
                                            This parameter can be combination value of reference LL_ADC_AWD_CHANNELS.           */

    int16_t HighThreshold;                /*!< Configure the ADC analog watchdog High threshold value.
                                            This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF.    */

    int16_t LowThreshold;                 /*!< Configures the ADC analog watchdog Low threshold value.
                                            This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF.    */

    ADC_AnologWDETypeDef WatchdogNumber;  /*!< Select which ADC analog watchdog is monitoring the selected channel.             */

    ADC_AnologWDFliterETypeDef Filtering; /*!< Specify whether filtering should be use and the number of samples to consider.
                                            Before setting flag or raising interrupt, analog watchdog can wait to have several
                                            consecutive out-of-window samples. This parameter allows to configure this number.  */
} ADC_AnalogWDGCfgTypeDef;

/**
  * @brief  Structure definition of ADC DMA Transfer
  * @note   The setting of these parameters by function LL_ADC_DMATransferConfig() is conditioned to ADC state.
  *         Each channel corresponds to a set of DMA, and only regular channels can use DMA.
  */
typedef struct __ADC_DMATransferCfgTypeDef {
    ADC_ChannelSelETypeDef Channel;           /*!< Select which ADC direct memory access the selected channel.                      */
    LL_FuncStatusETypeDef HalfInterrupt;      /*!< Configures the ADC direct memory access Half interrupt.                          */
    LL_FuncStatusETypeDef FullInterrupt;      /*!< Configures the ADC direct memory access Full interrupt.                          */
    ADC_DMATransferModeETypeDef TransferMode; /*!< Configure the DMA transfer mode to be single or cyclic.                          */
    uint32_t Address;                         /*!< Configure the address of the DMA transfer Buffer ,Only SECTION_RAMB,
                                                   SECTION_RAMB can be configured .                                                 */
    uint32_t Length;                          /*!< Configure the length of data (byte units) for a single DMA transfer.
                                                 This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF.   */
} ADC_DMATransferCfgTypeDef;


/**
  * @brief  Calibration parameter definitions for ADC groups regular and injected
  */
typedef struct __ADC_CalibrationTypeDef {
    ADC_ChannelSelETypeDef Channel;             /*!< Select which ADC channel congfigure Calibration parameters.                    */
    ADC_CalibGroupETypeDef CalibrationGroup;    /*!< Set ADC calibration group parameter selection.                                 */

    int16_t  Offset;                            /*!< Configure ADC calibration offset,default value is 0x0.
                                                    This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */

    uint16_t Gain;                              /*!< Configure ADC calibration gain defaulr value is 0x2000.
                                                    This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */
} ADC_CalibrationTypeDef;

/**
  * @brief  Read ADC self-calibration data
  */
typedef struct {
    int16_t  SingleOffset;                      /*!< Read ADC single-ended self-calibration data*/

    uint16_t SingleGain;                        /*!< Read ADC single-ended self-calibration data*/
    
    int16_t  DiffOffset;                        /*!< Read ADC differential self-calibration data*/

    uint16_t DiffGain;                          /*!< Read ADC differential self-calibration data*/
    
    int16_t  SingleBuffOffset;                  /*!< Read ADC single-ended plus BUFF self-calibration data*/

    uint16_t SingleBuffGain;                    /*!< Read ADC single-ended plus BUFF self-calibration data*/
    
} ADC_CalibrationDataTypeDef;

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Macros ADC LL Exported Macros
  * @brief    ADC LL Exported Macros
  * @{
  */

/**
  * @brief  Driver macro reserved for internal use: set a pointer to
  *         a register from a register basis from which an offset
  *         is applied.
  * @param  __REG__ Register basis from which the offset is applied.
  * @param  __REG_OFFFSET__ Offset to be applied (unit: number of registers).
  * @retval Pointer to register address
  */
#define __ADC_PTR_REG_OFFSET(__REG__, __REG_OFFFSET__)      \
    ((__IO uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((__REG_OFFFSET__) << 2UL))))


/** @addtogroup ADC_LL_Operation_ADC_Group_Regular Operation on ADC hierarchical scope: group regular
  * @{
  */
/**
  * @brief  Start ADC group regular conversion.
  * @note   This function is relevant for both
  *         internal trigger (SW start) and external trigger:
  *         - If ADC trigger has been set to software start, ADC conversion
  *           starts immediately.
  *         - If ADC trigger has been set to external trigger, ADC conversion
  *           will start at next trigger event (on the selected trigger edge)
  *           following the ADC start conversion command.
  * @note   Setting of this feature is conditioned to
  *         ADC state:
  *         ADC must be enabled without conversion on going on group regular,
  *         without conversion stop command on going on group regular,
  *         without ADC disable command on going.
  * @param  Instance ADC instance
  * @retval None
  */
#define  __LL_ADC_REG_StartConversion(__INSTANCE__) MODIFY_REG((__INSTANCE__)->CR0, ADC_CR0_BITS_PROPERTY_RS, ADC_CR0_ADSTART)

/**
  * @brief  Stop ADC group regular conversion.
  * @note   Setting of this feature is conditioned to ADC state:
  *         ADC must be enabled with conversion on going on group regular,
  *         without ADC disable command on going.
  * @param  Instance ADC instance
  * @retval None
  */
#define __LL_ADC_REG_StopConversion(__INSTANCE__)   MODIFY_REG((__INSTANCE__)->CR0, ADC_CR0_BITS_PROPERTY_RS, ADC_CR0_ADSTP)

/**
  * @brief  Get ADC group regular conversion state.
  * @param  Instance ADC instance
  * @retval 0: no conversion is on going on ADC group regular.
  */
#define __LL_ADC_REG_IsConversionOngoing(__INSTANCE__)      \
        ((READ_BIT((__INSTANCE__)->CR0, ADC_CR0_ADSTART) == (ADC_CR0_ADSTART)) ? 1UL : 0UL)

/**
  * @brief  Get ADC group regular command of conversion stop state
  * @param  Instance ADC instance
  * @retval 0: no command of conversion stop is on going on ADC group regular.
  */
#define __LL_ADC_REG_IsStopConversionOngoing(__INSTANCE__)  \
        ((READ_BIT((__INSTANCE__)->CR0, ADC_CR0_ADSTP) == (ADC_CR0_ADSTP)) ? 1UL : 0UL)

/**
  * @brief  Get ADC group regular conversion data, range fit for
  *         all ADC configurations.
  * @param  Instance ADC instance
  * @retval Value between Min_Data=0x0000 and Max_Data=0xFFFF
  */
#define __LL_ADC_REG_ReadConversionData(__INSTANCE__)       (READ_BIT((__INSTANCE__)->DR, ADC_DR_RDATA))

/**
  * @brief  Get ADC group regular every channel conversion data, range fit for
  *         all ADC configurations.
  * @param  Instance ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref ADC_CHANNEL_1
  *         @arg @ref ADC_CHANNEL_2
  *         @arg @ref ADC_CHANNEL_3
  *         @arg @ref ADC_CHANNEL_4
  *         @arg @ref ADC_CHANNEL_5
  *         @arg @ref ADC_CHANNEL_6
  *         @arg @ref ADC_CHANNEL_7
  *         @arg @ref ADC_CHANNEL_8
  *         @arg @ref ADC_CHANNEL_9
  *         @arg @ref ADC_CHANNEL_10
  *         @arg @ref ADC_CHANNEL_TEMPSENSOR
  * @retval Value between Min_Data=0x0000 and Max_Data=0xFFFF
  */
#define __LL_ADC_REG_ReadChannelConversionData(__INSTANCE__, __CHANNEL__)   \
        (READ_BIT((__INSTANCE__)->CDR[__CHANNEL__], ADC_CDR_RDATA))

/**
  * @}
  */

/** @addtogroup ADC_LL_Configuration_ADC_Group_Regular Configuration of ADC hierarchical scope: group regular
  * @{
  */
/**
  * @brief  Set for the ADC selected offset number 1, 2, 3 or 4:
  *         Channel to which the offset programmed will be applied
  * @param  Instance ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref ADC_CHANNEL_0
  *         @arg @ref ADC_CHANNEL_1
  *         @arg @ref ADC_CHANNEL_2
  *         @arg @ref ADC_CHANNEL_3
  *         @arg @ref ADC_CHANNEL_4
  *         @arg @ref ADC_CHANNEL_5
  *         @arg @ref ADC_CHANNEL_6
  *         @arg @ref ADC_CHANNEL_7
  *         @arg @ref ADC_CHANNEL_8
  *         @arg @ref ADC_CHANNEL_9
  *         @arg @ref ADC_CHANNEL_10
  *         @arg @ref ADC_CHANNEL_TEMPSENSOR
  * @param GroupSel value can be one of the following values:
  *         @arg @ref ADC_OFFSET_1
  *         @arg @ref ADC_OFFSET_2
  *         @arg @ref ADC_OFFSET_3
  *         @arg @ref ADC_OFFSET_4
  */
#define __LL_ADC_SetCalGroup(__INSTANCE__, __CHANNEL__,  __GROUPSEL__)                                          \
        (__CHANNEL__ > 7) ?                                                                                     \
        MODIFY_REG((__INSTANCE__)->CALR1,  ADC_CALR1_CAL8 << ((__CHANNEL__ - 8) << ADC_SMPRX_REGOFFSET),        \
        ((__GROUPSEL__) << ((__CHANNEL__ - 8) << ADC_SMPRX_REGOFFSET))) :                                       \
        MODIFY_REG((__INSTANCE__)->CALR0, ADC_CALR0_CAL0 << ((__CHANNEL__) << ADC_SMPRX_REGOFFSET),             \
        ((__GROUPSEL__)   << ((__CHANNEL__) << ADC_SMPRX_REGOFFSET)))


/**
 * @brief  Set ADC selected offset number 1, 2, 3 or 4.
 * @note   This function set the 2 items of offset configuration:
 *         - ADC channel to which the offset programmed will be applied
 *           (Single mode)
 *         - Offset level (offset to be subtracted from the raw
 *           converted data).
 * @note   Caution: Offset format is dependent to ADC resolution:
 *         offset has to be left-aligned on bit 11, the LSB (right bits)
 *         are set to 0.
 * @note   This function enables the offset, by default. It can be forced
 *         to disable state using function LL_ADC_SetOffsetState().
 * @param  Instance ADC instance
 * @param  Offsety This parameter can be one of the following values:
 *         @arg @ref ADC_OFFSET_1
 *         @arg @ref ADC_OFFSET_2
 *         @arg @ref ADC_OFFSET_3
 *         @arg @ref ADC_OFFSET_4
 * @param  OffsetValue Value between Min_Data=0x0000 and Max_Data=0xFFFF
 * @retval None
 */
#define __LL_ADC_SetOffset(__INSTANCE__, __OFFSETY__, __VALUE__)    \
        MODIFY_REG((__INSTANCE__)->OFR[__OFFSETY__], ADC_OFR0_OFFSET, (__VALUE__))

/**
  * @brief  Get for the ADC selected offset number 1, 2, 3 or 4:
  *         Offset level (offset to be subtracted from the raw
  *         converted data). Single mode.
  * @param  Instance ADC instance
  * @param  Offsety This parameter can be one of the following values:
  *         @arg @ref ADC_OFFSET_1
  *         @arg @ref ADC_OFFSET_2
  *         @arg @ref ADC_OFFSET_3
  *         @arg @ref ADC_OFFSET_4
  * @retval Value between Min_Data=0x0000 and Max_Data=0xFFFF
  */
#define __LL_ADC_GetOffset(__INSTANCE__, __OFFSETY__)       READ_BIT((__INSTANCE__)->OFR[__OFFSETY__], ADC_OFR0_OFFSET)

/**
  * @brief  Set ADC selected gain compensation number 1, 2, 3 or 4.Single mode.
  * @note   This function set the gain compensation coefficient
  *         that is applied to raw converted data using the formula:
  *           DATA = DATA(raw) * (gain compensation coef) >> 12
  * @param  Instance ADC instance
  * @param  Gainy This parameter can be one of the following values:
  *         @arg @ref ADC_GAIN_1
  *         @arg @ref ADC_GAIN_2
  *         @arg @ref ADC_GAIN_3
  *         @arg @ref ADC_GAIN_4
  * @param  GainCompensation This parameter can be:
  *         0           Gain compensation will be disabled and value set to 0
  *         1 -> 8192  Gain compensation will be enabled with specified value(default)
  * @retval None
  */
#define __LL_ADC_SetGainCompensation(__INSTANCE__,__GAINY__, __VALUE__)     \
        MODIFY_REG((__INSTANCE__)->GCR[(__GAINY__)], ADC_GCR0_GAIN, (__VALUE__))

/**
  * @brief  Get the ADC gain compensation value
  * @param  Instance ADC instance
  * @param  Gainy This parameter can be one of the following values:
  *         @arg @ref ADC_GAIN_1
  *         @arg @ref ADC_GAIN_2
  *         @arg @ref ADC_GAIN_3
  *         @arg @ref ADC_GAIN_4
  * @retval Returned value can be:
  *         0           Gain compensation is disabled
  *         1 -> 8192   Gain compensation is enabled with returned value
  */
#define __LL_ADC_GetGainCompensation(__INSTANCE__,__GAINY__)    READ_BIT((__INSTANCE__)->GCR[(__GAINY__)], ADC_GCR0_GAIN)

/**
 * @brief  Set ADC selected offset number 1, 2, 3 or 4.
 * @note   This function set the 2 items of offset configuration:
 *         - ADC channel to which the offset programmed will be applied
 *           (Single mode)
 *         - Offset level (offset to be subtracted from the raw
 *           converted data).
 * @note   Caution: Offset format is dependent to ADC resolution:
 *         offset has to be left-aligned on bit 11, the LSB (right bits)
 *         are set to 0.
 * @note   This function enables the offset, by default. It can be forced
 *         to disable state using function LL_ADC_SetOffsetState().
 * @param  Instance ADC instance
 * @param  Doffsety This parameter can be one of the following values:
 *         @arg @ref ADC_OFFSET_1
 *         @arg @ref ADC_OFFSET_2
 *         @arg @ref ADC_OFFSET_3
 *         @arg @ref ADC_OFFSET_4
 * @param  OffsetValue Value between Min_Data=0x0000 and Max_Data=0xFFFF
 * @retval None
 */
#define __LL_ADC_SetDiffOffset(__INSTANCE__, __DOFFSETY__, __VALUE__)   \
        MODIFY_REG((__INSTANCE__)->DOFR[(__DOFFSETY__)], ADC_DOFR0_OFFSET, (__VALUE__))

/**
  * @brief  Get for the ADC selected offset number 1, 2, 3 or 4:
  *         Offset level (offset to be subtracted from the raw
  *         converted data). Single mode.
  * @param  Instance ADC instance
  * @param  Doffsety This parameter can be one of the following values:
  *         @arg @ref ADC_OFFSET_1
  *         @arg @ref ADC_OFFSET_2
  *         @arg @ref ADC_OFFSET_3
  *         @arg @ref ADC_OFFSET_4
  * @retval Value between Min_Data=0x0000 and Max_Data=0xFFFF
  */
#define __LL_ADC_GetDiffOffset(__INSTANCE__, __DOFFSETY__)  READ_BIT((__INSTANCE__)->DOFR[(__DOFFSETY__)], ADC_DOFR0_OFFSET)

/**
  * @brief  Set ADC selected gain compensation number 1, 2, 3 or 4.Single mode.
  * @note   This function set the gain compensation coefficient
  *         that is applied to raw converted data using the formula:
  *           DATA = DATA(raw) * (gain compensation coef) >> 12
  * @param  Instance ADC instance
  * @param  Dgainy This parameter can be one of the following values:
  *         @arg @ref ADC_GAIN_1
  *         @arg @ref ADC_GAIN_2
  *         @arg @ref ADC_GAIN_3
  *         @arg @ref ADC_GAIN_4
  * @param  GainCompensation This parameter can be:
  *         0           Gain compensation will be disabled and value set to 0
  *         1 -> 8192  Gain compensation will be enabled with specified value(default)
  * @retval None
  */
#define __LL_ADC_SetDiffGainCompensation(__INSTANCE__,__DGAINY__, __VALUE__)    \
        MODIFY_REG((__INSTANCE__)->DGCR[(__DGAINY__)], ADC_DGCR0_GAIN, (__VALUE__))

/**
  * @brief  Get the ADC gain compensation value ,Differential.
  * @param  Instance ADC instance
  * @param  Dgainy This parameter can be one of the following values:
  *         @arg @ref ADC_GAIN_1
  *         @arg @ref ADC_GAIN_2
  *         @arg @ref ADC_GAIN_3
  *         @arg @ref ADC_GAIN_4
  * @retval Returned value can be:
  *         0           Gain compensation is disabled
  *         1 -> 8192  Gain compensation is enabled with returned value
  */
#define __LL_ADC_GetDiffGainCompensation(__INSTANCE__,__DGAINY__)   READ_BIT((__INSTANCE__)->DGCR[(__DGAINY__)], ADC_DGCR0_GAIN)

/**
  * @brief  Set ADC group regular conversion trigger source:
  *         internal (SW start) or from external peripheral (timer event,
  *         external interrupt line).
  * @note   setting trigger source to external trigger
  *         also set trigger polarity to rising edge.
  *         ADC must be without conversion on going on group regular.
  * @param  Instance ADC instance
  * @param  TriggerSource This parameter can be one of the following values:
  *         @arg @ref ADC_REG_TRIG_SOFTWARE)
  *         @arg @ref ADC_REG_TRIG_EXT_TIM0_CC
  *         @arg @ref ADC_REG_TRIG_EXT_TIM1_CC
  *         @arg @ref ADC_REG_TRIG_EXT_TIM2_CC
  *         @arg @ref ADC_REG_TRIG_EXT_TIM3_CC
  *         @arg @ref ADC_REG_TRIG_EXT_TIM4_CC
  *         @arg @ref ADC_REG_TRIG_EXT_TIM5_CC
  *         @arg @ref ADC_REG_TRIG_EXT_TIM6_CC
  *         @arg @ref ADC_REG_TRIG_EXT_TIM7_CC
  *         @arg @ref ADC_REG_TRIG_EXT_TIM0_TRGO
  *         @arg @ref ADC_REG_TRIG_EXT_TIM1_TRGO
  *         @arg @ref ADC_REG_TRIG_EXT_TIM2_TRGO
  *         @arg @ref ADC_REG_TRIG_EXT_TIM3_TRGO
  *         @arg @ref ADC_REG_TRIG_EXT_TIM4_TRGO
  *         @arg @ref ADC_REG_TRIG_EXT_TIM5_TRGO
  *         @arg @ref ADC_REG_TRIG_EXT_TIM6_TRGO
  *         @arg @ref ADC_REG_TRIG_EXT_TIM7_TRGO
  *         @arg @ref ADC_REG_TRIG_EXT_HRPWM_ADC_TRG0
  *         @arg @ref ADC_REG_TRIG_EXT_HRPWM_ADC_TRG1
  *         @arg @ref ADC_REG_TRIG_EXT_HRPWM_ADC_TRG2
  *         @arg @ref ADC_REG_TRIG_EXT_HRPWM_ADC_TRG3
  *         @arg @ref ADC_REG_TRIG_EXT_HRPWM_ADC_TRG4
  *         @arg @ref ADC_REG_TRIG_EXT_HRPWM_ADC_TRG5
  *         @arg @ref ADC_REG_TRIG_EXT_HRPWM_ADC_TRG6
  *         @arg @ref ADC_REG_TRIG_EXT_HRPWM_ADC_TRG7
  *         @arg @ref ADC_REG_TRIG_EXT_PIN
  * @retval None
  */
#define __LL_ADC_REG_SetTriggerSource(__INSTANCE__, __TRIGSRC__)    \
        MODIFY_REG((__INSTANCE__)->LR, ADC_LR_EXTEN | ADC_LR_EXTSEL, (__TRIGSRC__))

/**
  * @brief  Get ADC group regular conversion trigger source:
  *         internal (SW start) or from external peripheral (timer event,
  *         external interrupt line).
  * @note   To determine whether group regular trigger source is
  *         internal (SW start) or external, without detail
  *         of which peripheral is selected as external trigger,
  *         use function @ref LL_ADC_REG_IsTriggerSourceSWStart.
  * @param  Instance ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref ADC_REG_TRIG_SOFTWARE)
  *         @arg @ref ADC_REG_TRIG_EXT_TIM0_CC
  *         @arg @ref ADC_REG_TRIG_EXT_TIM1_CC
  *         @arg @ref ADC_REG_TRIG_EXT_TIM2_CC
  *         @arg @ref ADC_REG_TRIG_EXT_TIM3_CC
  *         @arg @ref ADC_REG_TRIG_EXT_TIM4_CC
  *         @arg @ref ADC_REG_TRIG_EXT_TIM5_CC
  *         @arg @ref ADC_REG_TRIG_EXT_TIM6_CC
  *         @arg @ref ADC_REG_TRIG_EXT_TIM7_CC
  *         @arg @ref ADC_REG_TRIG_EXT_TIM0_TRGO
  *         @arg @ref ADC_REG_TRIG_EXT_TIM1_TRGO
  *         @arg @ref ADC_REG_TRIG_EXT_TIM2_TRGO
  *         @arg @ref ADC_REG_TRIG_EXT_TIM3_TRGO
  *         @arg @ref ADC_REG_TRIG_EXT_TIM4_TRGO
  *         @arg @ref ADC_REG_TRIG_EXT_TIM5_TRGO
  *         @arg @ref ADC_REG_TRIG_EXT_TIM6_TRGO
  *         @arg @ref ADC_REG_TRIG_EXT_TIM7_TRGO
  *         @arg @ref ADC_REG_TRIG_EXT_HRPWM_ADC_TRG0
  *         @arg @ref ADC_REG_TRIG_EXT_HRPWM_ADC_TRG1
  *         @arg @ref ADC_REG_TRIG_EXT_HRPWM_ADC_TRG2
  *         @arg @ref ADC_REG_TRIG_EXT_HRPWM_ADC_TRG3
  *         @arg @ref ADC_REG_TRIG_EXT_HRPWM_ADC_TRG4
  *         @arg @ref ADC_REG_TRIG_EXT_HRPWM_ADC_TRG5
  *         @arg @ref ADC_REG_TRIG_EXT_HRPWM_ADC_TRG6
  *         @arg @ref ADC_REG_TRIG_EXT_HRPWM_ADC_TRG7
  *         @arg @ref ADC_REG_TRIG_EXT_PIN)
  */
#define __LL_ADC_REG_GetTriggerSource(__INSTANCE__)         (READ_BIT((__INSTANCE__)->LR, ADC_LR_EXTSEL)

/**
  * @brief  Get ADC group regular conversion trigger source internal (SW start)
  *         or external.
  * @note   In case of group regular trigger source set to external trigger,
  *         to determine which peripheral is selected as external trigger,
  *         use function @ref LL_ADC_REG_GetTriggerSource().
  * @param  Instance ADC instance
  * @retval Value "0" if trigger source external trigger
  *         Value "1" if trigger source SW start.
  */
#define __LL_ADC_REG_IsTriggerSourceSWStart(__INSTANCE__)   \
        ((READ_BIT((__INSTANCE__)->LR, ADC_LR_EXTEN) == (ADC_REG_TRIG_SOFTWARE)) ? 1UL : 0UL)

/**
  * @brief  Set ADC group regular conversion trigger polarity.
  * @note   Applicable only for trigger source set to external trigger.
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @param  Instance ADC instance
  * @param  ExternalTriggerEdge This parameter can be one of the following values:
  *         @arg @ref ADC_REG_TRIG_EXT_RISING
  *         @arg @ref ADC_REG_TRIG_EXT_FALLING
  *         @arg @ref ADC_REG_TRIG_EXT_RISINGFALLING
  * @retval None
  */
#define __LL_ADC_REG_SetTriggerEdge(__INSTANCE__, __EXIT_EDGE__)     MODIFY_REG((__INSTANCE__)->LR, ADC_LR_EXTEN, (__EXIT_EDGE__))

/**
  * @brief  Get ADC group regular conversion trigger polarity.
  * @note   Applicable only for trigger source set to external trigger.
  * @param  Instance ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref ADC_REG_TRIG_EXT_RISING
  *         @arg @ref ADC_REG_TRIG_EXT_FALLING
  *         @arg @ref ADC_REG_TRIG_EXT_RISINGFALLING
  */
#define __LL_ADC_REG_GetTriggerEdge(__INSTANCE__)                   READ_BIT((__INSTANCE__)->LR, ADC_LR_EXTEN)

/**
  * @brief  Set ADC group regular sequencer length.
  * @note   Description of ADC group regular sequencer features:
  *         - For devices with sequencer fully configurable
  *           sequencer length and each rank affectation to a channel
  *           are configurable.
  *           This function performs configuration of:
  *           - Sequence length: Number of ranks in the scan sequence.
  * @note   Sequencer length value 0 is equivalent to sequencer of 1 rank:
  *         ADC conversion on only 1 channel.
  * @param  Instance ADC instance
  * @param  SequencerNbRanks This parameter can be one of the following values:
  *         @arg @ref ADC_REG_SEQ_ENABLE_1
  *         @arg @ref ADC_REG_SEQ_ENABLE_2
  *         @arg @ref ADC_REG_SEQ_ENABLE_3
  *         @arg @ref ADC_REG_SEQ_ENABLE_4
  *         @arg @ref ADC_REG_SEQ_ENABLE_5
  *         @arg @ref ADC_REG_SEQ_ENABLE_6
  *         @arg @ref ADC_REG_SEQ_ENABLE_7
  *         @arg @ref ADC_REG_SEQ_ENABLE_8
  *         @arg @ref ADC_REG_SEQ_ENABLE_9
  *         @arg @ref ADC_REG_SEQ_ENABLE_10
  *         @arg @ref ADC_REG_SEQ_ENABLE_11
  *         @arg @ref ADC_REG_SEQ_ENABLE_12
  *         @arg @ref ADC_REG_SEQ_ENABLE_13
  *         @arg @ref ADC_REG_SEQ_ENABLE_14
  *         @arg @ref ADC_REG_SEQ_ENABLE_15
  *         @arg @ref ADC_REG_SEQ_ENABLE_16
  * @retval None
  */
#define __LL_ADC_REG_SetSequencerLength(__INSTANCE__, __SEQUENCERANKS__)    \
        MODIFY_REG((__INSTANCE__)->LR, ADC_LR_LEN, (__SEQUENCERANKS__))

/**
  * @brief  Get ADC group regular sequencer length.
  * @note   Description of ADC group regular sequencer features:
  *         - For devices with sequencer fully configurable
  *           sequencer length and each rank affectation to a channel
  *           are configurable.
  *           This function retrieves:
  *           - Sequence length: Number of ranks in the scan sequence.
  * @note   Sequencer length value 0 is equivalent to sequencer of 1 rank:
  *         ADC conversion on only 1 channel.
  * @param  Instance ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref ADC_REG_SEQ_ENABLE_1
  *         @arg @ref ADC_REG_SEQ_ENABLE_2
  *         @arg @ref ADC_REG_SEQ_ENABLE_3
  *         @arg @ref ADC_REG_SEQ_ENABLE_4
  *         @arg @ref ADC_REG_SEQ_ENABLE_5
  *         @arg @ref ADC_REG_SEQ_ENABLE_6
  *         @arg @ref ADC_REG_SEQ_ENABLE_7
  *         @arg @ref ADC_REG_SEQ_ENABLE_8
  *         @arg @ref ADC_REG_SEQ_ENABLE_9
  *         @arg @ref ADC_REG_SEQ_ENABLE_10
  *         @arg @ref ADC_REG_SEQ_ENABLE_11
  *         @arg @ref ADC_REG_SEQ_ENABLE_12
  *         @arg @ref ADC_REG_SEQ_ENABLE_13
  *         @arg @ref ADC_REG_SEQ_ENABLE_14
  *         @arg @ref ADC_REG_SEQ_ENABLE_15
  *         @arg @ref ADC_REG_SEQ_ENABLE_16
  */
#define __LL_ADC_REG_GetSequencerLength(__INSTANCE__)       READ_BIT((__INSTANCE__)->LR, ADC_LR_LEN)

/**
  * @brief  Set ADC group regular sequencer discontinuous mode:
  *         sequence subdivided and conversions interrupted every selected
  *         number of ranks.
  * @note   It is not possible to enable both ADC group regular
  *         continuous mode and sequencer discontinuous mode.
  * @note   It is not possible to enable both ADC auto-injected mode
  *         and ADC group regular sequencer discontinuous mode.
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @param  Instance ADC instance
  * @param  SeqDiscont This parameter can be one of the following values:
  *         @arg @ref ADC_REG_SEQ_DISCON_DISABLE
  *         @arg @ref ADC_REG_SEQ_DISNUM_1
  *         @arg @ref ADC_REG_SEQ_DISNUM_2
  *         @arg @ref ADC_REG_SEQ_DISNUM_3
  *         @arg @ref ADC_REG_SEQ_DISNUM_4
  *         @arg @ref ADC_REG_SEQ_DISNUM_5
  *         @arg @ref ADC_REG_SEQ_DISNUM_6
  *         @arg @ref ADC_REG_SEQ_DISNUM_7
  *         @arg @ref ADC_REG_SEQ_DISNUM_8
  * @retval None
  */
#define __LL_ADC_REG_SetSequencerDiscont(__INSTANCE__, __SEQDISCONT__)      \
        MODIFY_REG((__INSTANCE__)->CR1, ADC_CR1_DISCEN | ADC_CR1_DISCNUM, (__SEQDISCONT__))

/**
  * @brief  Get ADC group regular sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @param  Instance ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref ADC_REG_SEQ_DISCONT_DISABLE
  *         @arg @ref ADC_REG_SEQ_DISCONT_1
  *         @arg @ref ADC_REG_SEQ_DISCONT_2
  *         @arg @ref ADC_REG_SEQ_DISCONT_3
  *         @arg @ref ADC_REG_SEQ_DISCONT_4
  *         @arg @ref ADC_REG_SEQ_DISCONT_5
  *         @arg @ref ADC_REG_SEQ_DISCONT_6
  *         @arg @ref ADC_REG_SEQ_DISCONT_7
  *         @arg @ref ADC_REG_SEQ_DISCONT_8
  */
#define __LL_ADC_REG_GetSequencerDiscont(__INSTANCE__)      READ_BIT((__INSTANCE__)->CR1, ADC_CR1_DISCEN | ADC_CR1_DISCNUM)

/**
  * @brief  Set ADC group regular sequence: channel on the selected
  *         scan sequence rank.
  * @note   This function performs configuration of:
  *         - Channels ordering into each rank of scan sequence:
  *           whatever channel can be placed into whatever rank.
  * @note   ADC group regular sequencer is fully configurable: sequencer length and each rank
  *         affectation to a channel are configurable.
  *         Refer to description of function @ref LL_ADC_REG_SetSequencerLength().
  * @param  Instance ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref ADC_REG_RANK_1
  *         @arg @ref ADC_REG_RANK_2
  *         @arg @ref ADC_REG_RANK_3
  *         @arg @ref ADC_REG_RANK_4
  *         @arg @ref ADC_REG_RANK_5
  *         @arg @ref ADC_REG_RANK_6
  *         @arg @ref ADC_REG_RANK_7
  *         @arg @ref ADC_REG_RANK_8
  *         @arg @ref ADC_REG_RANK_9
  *         @arg @ref ADC_REG_RANK_10
  *         @arg @ref ADC_REG_RANK_11
  *         @arg @ref ADC_REG_RANK_12
  *         @arg @ref ADC_REG_RANK_13
  *         @arg @ref ADC_REG_RANK_14
  *         @arg @ref ADC_REG_RANK_15
  *         @arg @ref ADC_REG_RANK_16
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref ADC_CHANNEL_0
  *         @arg @ref ADC_CHANNEL_1
  *         @arg @ref ADC_CHANNEL_2
  *         @arg @ref ADC_CHANNEL_3
  *         @arg @ref ADC_CHANNEL_4
  *         @arg @ref ADC_CHANNEL_5
  *         @arg @ref ADC_CHANNEL_6
  *         @arg @ref ADC_CHANNEL_7
  *         @arg @ref ADC_CHANNEL_8
  *         @arg @ref ADC_CHANNEL_9
  *         @arg @ref ADC_CHANNEL_10
  *         @arg @ref ADC_CHANNEL_TEMPSENSOR
  * @retval None
  */
#define __LL_ADC_REG_SetSequencerRanks(__INSTANCE__, __RANK__, __CHANNEL__)                           \
        (__RANK__) > 7 ?                                                                              \
        MODIFY_REG((__INSTANCE__)->SQR1, ADC_SQR1_SQ9 << ((__RANK__ - 8) << ADC_SMPRX_REGOFFSET),   \
        ((__CHANNEL__)   << ((__RANK__ - 8) << ADC_SMPRX_REGOFFSET))) :                               \
        MODIFY_REG((__INSTANCE__)->SQR0, ADC_SQR0_SQ1 << ((__RANK__) << ADC_SMPRX_REGOFFSET),         \
        ((__CHANNEL__)   << ((__RANK__) << ADC_SMPRX_REGOFFSET)))

/**
  * @brief  Get ADC group regular sequence: channel on the selected
  *         scan sequence rank.
  * @note   ADC group regular sequencer is fully configurable: sequencer length and each rank
  *         affectation to a channel are configurable.
  *         Refer to description of function @ref LL_ADC_REG_SetSequencerLength().
  * @param  Instance ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref ADC_REG_RANK_1
  *         @arg @ref ADC_REG_RANK_2
  *         @arg @ref ADC_REG_RANK_3
  *         @arg @ref ADC_REG_RANK_4
  *         @arg @ref ADC_REG_RANK_5
  *         @arg @ref ADC_REG_RANK_6
  *         @arg @ref ADC_REG_RANK_7
  *         @arg @ref ADC_REG_RANK_8
  *         @arg @ref ADC_REG_RANK_9
  *         @arg @ref ADC_REG_RANK_10
  *         @arg @ref ADC_REG_RANK_11
  *         @arg @ref ADC_REG_RANK_12
  *         @arg @ref ADC_REG_RANK_13
  *         @arg @ref ADC_REG_RANK_14
  *         @arg @ref ADC_REG_RANK_15
  *         @arg @ref ADC_REG_RANK_16
  * @retval Returned value can be one of the following values:
  *         @arg @ref ADC_CHANNEL_0
  *         @arg @ref ADC_CHANNEL_1
  *         @arg @ref ADC_CHANNEL_2
  *         @arg @ref ADC_CHANNEL_3
  *         @arg @ref ADC_CHANNEL_4
  *         @arg @ref ADC_CHANNEL_5
  *         @arg @ref ADC_CHANNEL_6
  *         @arg @ref ADC_CHANNEL_7
  *         @arg @ref ADC_CHANNEL_8
  *         @arg @ref ADC_CHANNEL_9
  *         @arg @ref ADC_CHANNEL_10
  *         @arg @ref ADC_CHANNEL_TEMPSENSOR
  */
#define __LL_ADC_REG_GetSequencerRanks(__INSTANCE__, __RANK__)                                    \
    (__RANK__) > 7 ?                                                                              \
    (READ_BIT((__INSTANCE__)->SQR1, ADC_SQR1_SQ9 << ((__RANK__ - 8) << ADC_SMPRX_REGOFFSET))) : \
    (READ_BIT((__INSTANCE__)->SQR0, ADC_SQR0_SQ1 << ((__RANK__) << ADC_SMPRX_REGOFFSET)))

/**
  * @brief  Set ADC continuous conversion mode on ADC group regular.
  * @note   Description of ADC continuous conversion mode:
  *         - single mode: one conversion per trigger
  *         - continuous mode: after the first trigger, following
  *           conversions launched successively automatically.
  * @note   It is not possible to enable both ADC group regular
  *         continuous mode and sequencer discontinuous mode.
  * @param  Instance ADC instance
  * @param  Continuous This parameter can be one of the following values:
  *         @arg @ref ADC_REG_CONV_SINGLE
  *         @arg @ref ADC_REG_CONV_CONTINUOUS
  * @retval None
  */
#define __LL_ADC_REG_SetContinuousMode(__INSTANCE__, __COUNT__)      MODIFY_REG((__INSTANCE__)->CR1, ADC_CR1_CONT, (__COUNT__))

/**
  * @brief  Get ADC continuous conversion mode on ADC group regular.
  * @note   Description of ADC continuous conversion mode:
  *         - single mode: one conversion per trigger
  *         - continuous mode: after the first trigger, following
  *           conversions launched successively automatically.
  * @param  Instance ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref ADC_REG_CONV_SINGLE
  *         @arg @ref ADC_REG_CONV_CONTINUOUS
  */
#define __LL_ADC_REG_GetContinuousMode(__INSTANCE__)                 READ_BIT((__INSTANCE__)->CR1, ADC_CR1_CONT)

/**
  * @brief  Set ADC group regular conversion data transfer: no transfer or
  *         transfer by DMA.
  * @note   If transfer by DMA selected, This ADC mode is intended to be used with DMA mode circular.
  * @note   If ADC DMA is set to single and DMA is set to mode non-circular:
  *         when DMA transfers size will be reached, DMA will stop transfers of
  *         ADC conversions data ADC will raise an overrun error
  *        (overrun flag and interruption if enabled).
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular.
  * @param  Instance ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref ADC_CHANNEL_0
  *         @arg @ref ADC_CHANNEL_1
  *         @arg @ref ADC_CHANNEL_2
  *         @arg @ref ADC_CHANNEL_3
  *         @arg @ref ADC_CHANNEL_4
  *         @arg @ref ADC_CHANNEL_5
  *         @arg @ref ADC_CHANNEL_6
  *         @arg @ref ADC_CHANNEL_7
  *         @arg @ref ADC_CHANNEL_8
  *         @arg @ref ADC_CHANNEL_9
  *         @arg @ref ADC_CHANNEL_10
  *         @arg @ref ADC_CHANNEL_TEMPSENSOR
  * @param  DMATransfer This parameter can be one of the following values:
  *         @arg @ref ADC_REG_DMA_TRANSFER_SINGLE
  *         @arg @ref ADC_REG_DMA_TRANSFER_CIRCLE
  * @retval None
  */
#define __LL_ADC_REG_SetDMATransfer(__INSTANCE__, __CHANNLE__, __DMAMODE__)     \
        MODIFY_REG((__INSTANCE__)->DMA_CR[__CHANNLE__].TCR, ADC_DMA_TCR_CIRC | ADC_DMA_TCR_START, (__DMAMODE__))

/**
  * @brief  Get ADC group regular conversion data transfer: no transfer or
  *         transfer by DMA.
  * @note   If transfer by DMA selected:
  *         This ADC mode is intended to be used with DMA mode circular.
  * @note   If ADC DMA is set to single and DMA is set to mode non-circular:
  *         when DMA transfers size will be reached, DMA will stop transfers of
  *         ADC conversions data ADC will raise an overrun error
  *         (overrun flag and interruption if enabled).
  * @param  Instance ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref ADC_CHANNEL_0
  *         @arg @ref ADC_CHANNEL_1
  *         @arg @ref ADC_CHANNEL_2
  *         @arg @ref ADC_CHANNEL_3
  *         @arg @ref ADC_CHANNEL_4
  *         @arg @ref ADC_CHANNEL_5
  *         @arg @ref ADC_CHANNEL_6
  *         @arg @ref ADC_CHANNEL_7
  *         @arg @ref ADC_CHANNEL_8
  *         @arg @ref ADC_CHANNEL_9
  *         @arg @ref ADC_CHANNEL_10
  *         @arg @ref ADC_CHANNEL_TEMPSENSOR
  * @retval Returned value can be one of the following values:
  *         @arg @ref ADC_REG_DMA_TRANSFER_SINGLE
  *         @arg @ref ADC_REG_DMA_TRANSFER_CIRCLE
  */
#define __LL_ADC_REG_GetDMATransfer(__INSTANCE__, __CHANNLE__)  \
        READ_BIT((__INSTANCE__)->DMA_CR[__CHANNLE__].TCR, ADC_DMA_TCR_CIRC | ADC_DMA_TCR_START)

/**
  * @brief  Set the DMA transfer address.
  * @note   If transfer by DMA selected:
  *         This ADC mode is intended to be used with DMA mode circular.
  * @note   If ADC DMA is set to single and DMA is set to mode non-circular:
  *         when DMA transfers size will be reached, DMA will stop transfers of
  *         ADC conversions data ADC will raise an overrun error
  *         (overrun flag and interruption if enabled).
  * @param  Instance ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref ADC_CHANNEL_0
  *         @arg @ref ADC_CHANNEL_1
  *         @arg @ref ADC_CHANNEL_2
  *         @arg @ref ADC_CHANNEL_3
  *         @arg @ref ADC_CHANNEL_4
  *         @arg @ref ADC_CHANNEL_5
  *         @arg @ref ADC_CHANNEL_6
  *         @arg @ref ADC_CHANNEL_7
  *         @arg @ref ADC_CHANNEL_8
  *         @arg @ref ADC_CHANNEL_9
  *         @arg @ref ADC_CHANNEL_10
  *         @arg @ref ADC_CHANNEL_TEMPSENSOR
  * @param  Address   dma transfer buffer addresss
  * @retval None
  */
#define __LL_ADC_REG_SetDMAAddr(__INSTANCE__, __CHANNLE__, __ADDR__)         \
    MODIFY_REG((__INSTANCE__)->DMA_CR[__CHANNLE__].TAR, ADC_DMA_TAR_ADDR, (__ADDR__))

/**
  * @brief  Set the DMA transfer length
  * @param  __INSTANCE__ Special ADC Peripheral
  * @param  __CHANNLE__ ADC Channel
  * @param  __LENGTH__ dma transfer length
  * @return None
  */
#define __LL_ADC_REG_SetDMALength(__INSTANCE__, __CHANNLE__, __LENGTH__)    \
    MODIFY_REG((__INSTANCE__)->DMA_CR[__CHANNLE__].TLR, ADC_DMA_TLR_LENG, (__LENGTH__))

/**
  * @brief  Set ADC group regular behavior in case of overrun:
  *         data preserved or overwritten.
  * @note   Compatibility with devices without feature overrun:
  *         other devices without this feature have a behavior
  *         equivalent to data overwritten.
  *         The default setting of overrun is data preserved.
  *         ADC must be disabled or enabled without conversion on going
  *         on group regular.
  * @param  Instance ADC instance
  * @param  Overrun This parameter can be one of the following values:
  *         @arg @ref ADC_REG_OVR_DATA_PRESERVED
  *         @arg @ref ADC_REG_OVR_DATA_OVERWRITTEN
  * @retval None
  */
#define __LL_ADC_REG_SetOverrun(__INSTANCE__, __OVRRUN__)        MODIFY_REG((__INSTANCE__)->CR1, ADC_CR1_OVRMOD, (__OVRRUN__))

/**
  * @brief  Get ADC group regular behavior in case of overrun:
  *         data preserved or overwritten.
  * @param  Instance ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref ADC_REG_OVR_DATA_PRESERVED
  *         @arg @ref ADC_REG_OVR_DATA_OVERWRITTEN
  */
#define __LL_ADC_REG_GetOverrun(__INSTANCE__)                    READ_BIT((__INSTANCE__)->CR1, ADC_CR1_OVRMOD)

/**
  * @}
  */


/** @addtogroup ADC_LL_Configuration_ADC_Group_Injected Configuration of ADC hierarchical scope: group injected
  * @{
  */
/**
  * @brief  Set ADC group injected conversion trigger source:
  *         internal (SW start) or from external peripheral (timer event,
  *         external interrupt line).
  * @note   setting trigger source to external trigger also set trigger polarity to rising edge
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @param  Instance ADC instance
  * @param  TriggerSource This parameter can be one of the following values:
  *         @arg @ref  ADC_INJ_TRIG_SOFTWARE
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM0_CC
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM1_CC
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM2_CC
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM3_CC
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM4_CC
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM5_CC
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM6_CC
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM7_CC
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM0_TRGO
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM1_TRGO
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM2_TRGO
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM3_TRGO
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM4_TRGO
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM5_TRGO
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM6_TRGO
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM7_TRGO
  *         @arg @ref  ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG0
  *         @arg @ref  ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG1
  *         @arg @ref  ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG2
  *         @arg @ref  ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG3
  *         @arg @ref  ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG4
  *         @arg @ref  ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG5
  *         @arg @ref  ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG6
  *         @arg @ref  ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG7
  *         @arg @ref  ADC_INJ_TRIG_EXT_PIN
  * @retval None
  */
#define __LL_ADC_INJ_SetTriggerSource(__INSTANCE__, __TRIGSRC__)        \
        MODIFY_REG((__INSTANCE__)->JLR, ADC_JLR_JEXTSEL | ADC_JLR_JEXTEN, (__TRIGSRC__))

/**
  * @brief  Get ADC group injected conversion trigger source:
  *         internal (SW start) or from external peripheral (timer event,
  *         external interrupt line).
  * @note   To determine whether group injected trigger source is
  *         internal (SW start) or external, without detail
  *         of which peripheral is selected as external trigger,
  * @note   setting trigger source to external trigger also set trigger polarity to rising edge
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @param  Instance ADC instance
  * @param  TriggerSource This parameter can be one of the following values:
  *         @arg @ref  ADC_INJ_TRIG_SOFTWARE
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM0_CC
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM1_CC
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM2_CC
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM3_CC
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM4_CC
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM5_CC
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM6_CC
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM7_CC
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM0_TRGO
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM1_TRGO
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM2_TRGO
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM3_TRGO
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM4_TRGO
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM5_TRGO
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM6_TRGO
  *         @arg @ref  ADC_INJ_TRIG_EXT_TIM7_TRGO
  *         @arg @ref  ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG0
  *         @arg @ref  ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG1
  *         @arg @ref  ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG2
  *         @arg @ref  ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG3
  *         @arg @ref  ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG4
  *         @arg @ref  ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG5
  *         @arg @ref  ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG6
  *         @arg @ref  ADC_INJ_TRIG_EXT_HRPWM_ADC_TRG7
  *         @arg @ref  ADC_INJ_TRIG_EXT_PIN
  * @retval None
  */
#define __LL_ADC_INJ_GetTriggerSource(__INSTANCE__)          READ_BIT((__INSTANCE__)->JLR, ADC_JLR_JEXTSEL)

/**
  * @brief  Get ADC group injected conversion trigger source internal (SW start)
            or external
  * @note   In case of group injected trigger source set to external trigger,
  *         to determine which peripheral is selected as external trigger,
  *         use function @ref LL_ADC_INJ_GetTriggerSource.
  * @param  Instance ADC instance
  * @retval Value "0" if trigger source external trigger
  *         Value "1" if trigger source SW start.
  */
#define __LL_ADC_INJ_IsTriggerSourceSWStart(__INSTANCE__)    \
        ((READ_BIT((__INSTANCE__)->JLR, ADC_JLR_JEXTEN) == (ADC_INJ_TRIG_SOFTWARE & ADC_JLR_JEXTEN)) ? 1UL : 0UL)

/**
  * @brief  Set ADC group injected conversion trigger polarity.
  *         Applicable only for trigger source set to external trigger.
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @param  Instance ADC instance
  * @param  ExternalTriggerEdge This parameter can be one of the following values:
  *         @arg @ref ADC_INJ_TRIG_EXT_RISING
  *         @arg @ref ADC_INJ_TRIG_EXT_FALLING
  *         @arg @ref ADC_INJ_TRIG_EXT_RISINGFALLING
  * @retval None
  */
#define __LL_ADC_INJ_SetTriggerEdge(__INSTANCE__, __TRIG_EDGE__)    \
        MODIFY_REG((__INSTANCE__)->JLR, ADC_JLR_JEXTEN, (__TRIG_EDGE__))

/**
  * @brief  Get ADC group injected conversion trigger polarity.
  *         Applicable only for trigger source set to external trigger.
  * @param  Instance ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref ADC_INJ_TRIG_EXT_RISING
  *         @arg @ref ADC_INJ_TRIG_EXT_FALLING
  *         @arg @ref ADC_INJ_TRIG_EXT_RISINGFALLING
  */
#define __LL_ADC_INJ_GetTriggerEdge(__INSTANCE__)            READ_BIT((__INSTANCE__)->JLR, ADC_JLR_JEXTEN)

/**
  * @brief  Set ADC group injected sequencer length.
  * @note   This function performs configuration of:
  *         - Sequence length: Number of ranks in the scan sequence.
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @param  Instance ADC instance
  * @param  SequencerNbRanks This parameter can be one of the following values:
  *         @arg @ref ADC_INJ_SEQ_LENGTH_1
  *         @arg @ref ADC_INJ_SEQ_LENGTH_2
  *         @arg @ref ADC_INJ_SEQ_LENGTH_3
  *         @arg @ref ADC_INJ_SEQ_LENGTH_4
  * @retval None
  */
#define __LL_ADC_INJ_SetSequencerLength(__INSTANCE__, __SEQUENCERANK__)     \
        MODIFY_REG((__INSTANCE__)->JLR, ADC_JLR_JLEN, (__SEQUENCERANK__))

/**
  * @brief  Get ADC group injected sequencer length and scan direction.
  * @note   This function retrieves:
  *         - Sequence length: Number of ranks in the scan sequence.
  * @param  Instance ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref ADC_INJ_SEQ_LENGTH_1
  *         @arg @ref ADC_INJ_SEQ_LENGTH_2
  *         @arg @ref ADC_INJ_SEQ_LENGTH_3
  *         @arg @ref ADC_INJ_SEQ_LENGTH_4
  */
#define __LL_ADC_INJ_GetSequencerLength(__INSTANCE__)        READ_BIT((__INSTANCE__)->JLR, ADC_JLR_JLEN)

/**
  * @brief  Set ADC group injected sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @note   It is not possible to enable both ADC group injected
  *         auto-injected mode and sequencer discontinuous mode.
  * @param  Instance ADC instance
  * @param  SeqDiscont This parameter can be one of the following values:
  *         @arg @ref ADC_INJ_SEQ_DISCONT_DISABLE
  *         @arg @ref ADC_INJ_SEQ_DISCONT_ENABLE
  * @retval None
  */
#define __LL_ADC_INJ_SetSequencerDiscont(__INSTANCE__, __SEQDISCONT__)      \
        MODIFY_REG((__INSTANCE__)->CR1, ADC_CR1_JDISCEN, (__SEQDISCONT__))

/**
  * @brief  Get ADC group injected sequencer discontinuous mode:
  *         sequence subdivided and scan conversions interrupted every selected
  *         number of ranks.
  * @param  Instance ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref ADC_INJ_SEQ_DISCONT_DISABLE
  *         @arg @ref ADC_INJ_SEQ_DISCONT_ENABLE
  */
#define __LL_ADC_INJ_GetSequencerDiscont(__INSTANCE__)      READ_BIT((__INSTANCE__)->CR1, ADC_CR1_JDISCEN)

/**
  * @brief  Set ADC group injected sequence: channel on the selected
  *         sequence rank.
  * @note   Depending on devices and packages, some channels may not be available.
  * @note   setting of this feature is conditioned to ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups injected.
  * @param  Instance ADC instance
  * @param  Rank Position  This parameter can be one of the following values:
  *         @arg @ref ADC_INJ_RANK_1
  *         @arg @ref ADC_INJ_RANK_2
  *         @arg @ref ADC_INJ_RANK_3
  *         @arg @ref ADC_INJ_RANK_4
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref ADC_CHANNEL_0
  *         @arg @ref ADC_CHANNEL_1
  *         @arg @ref ADC_CHANNEL_2
  *         @arg @ref ADC_CHANNEL_3
  *         @arg @ref ADC_CHANNEL_4
  *         @arg @ref ADC_CHANNEL_5
  *         @arg @ref ADC_CHANNEL_6
  *         @arg @ref ADC_CHANNEL_7
  *         @arg @ref ADC_CHANNEL_8
  *         @arg @ref ADC_CHANNEL_9
  *         @arg @ref ADC_CHANNEL_10
  *         @arg @ref ADC_CHANNEL_TEMPSENSOR
  * @retval None
  */
#define __LL_ADC_INJ_SetSequencerRanks(__INSTANCE__, __RANK__, __CHANNEL__)     \
        MODIFY_REG((__INSTANCE__)->JSQR, (ADC_JSQR_JSQ1 << (__RANK__)), (__CHANNEL__) << (__RANK__))

/**
  * @brief  Get ADC group injected sequence: channel on the selected
  *         sequence rank.
  * @note   Depending on devices and packages, some channels may not be available.
  *         Refer to device datasheet for channels availability.
  * @note   setting of this feature is conditioned to ADC state:
  *         ADC must not be disabled. Can be enabled with or without conversion
  *         on going on either groups regular or injected.
  * @param  Instance ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref ADC_INJ_RANK_1
  *         @arg @ref ADC_INJ_RANK_2
  *         @arg @ref ADC_INJ_RANK_3
  *         @arg @ref ADC_INJ_RANK_4
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref ADC_CHANNEL_0
  *         @arg @ref ADC_CHANNEL_1
  *         @arg @ref ADC_CHANNEL_2
  *         @arg @ref ADC_CHANNEL_3
  *         @arg @ref ADC_CHANNEL_4
  *         @arg @ref ADC_CHANNEL_5
  *         @arg @ref ADC_CHANNEL_6
  *         @arg @ref ADC_CHANNEL_7
  *         @arg @ref ADC_CHANNEL_8
  *         @arg @ref ADC_CHANNEL_9
  *         @arg @ref ADC_CHANNEL_10
  *         @arg @ref ADC_CHANNEL_TEMPSENSOR
  * @retval None
  */
#define __LL_ADC_INJ_GetSequencerRanks(__INSTANCE__, __RANK__)  READ_BIT((__INSTANCE__)->JSQR, (ADC_JSQR_JSQ1 << (__RANK__)))

/**
  * @brief  Set ADC group injected conversion trigger:
  *         independent or from ADC group regular.
  * @note   This mode can be used to extend number of data registers
  *         updated after one ADC conversion trigger and with data
  *         permanently kept , up to 5 data registers:
  *         1 data register on ADC group regular, 4 data registers
  *         on ADC group injected.
  * @note   If ADC group injected injected trigger source is set to an
  *         external trigger, this feature must be must be set to
  *         independent trigger.
  *         ADC group injected automatic trigger is compliant only with
  *         group injected trigger source set to SW start, without any
  *         further action on  ADC group injected conversion start or stop:
  * @note   It is not possible to enable both ADC group injected
  *         auto-injected mode and sequencer discontinuous mode.
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @param  Instance ADC instance
  * @param  TrigAuto This parameter can be one of the following values:
  *         @arg @ref ADC_INJ_TRIG_INDEPENDENT
  *         @arg @ref ADC_INJ_TRIG_FROM_GRP_REGULAR
  * @retval None
  */
#define __LL_ADC_INJ_SetTrigAuto(__INSTANCE__, __TRIGAUTO__)    MODIFY_REG((__INSTANCE__)->CR1, ADC_CR1_JAUTO, (__TRIGAUTO__))

/**
  * @brief  Get ADC group injected conversion trigger:
  *         independent or from ADC group regular.
  * @param  Instance ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref ADC_INJ_TRIG_INDEPENDENT
  *         @arg @ref ADC_INJ_TRIG_FROM_GRP_REGULAR
  */
#define __LL_ADC_INJ_GetTrigAuto(__INSTANCE__)                   READ_BIT((__INSTANCE__)->CR1, ADC_CR1_JAUTO)

/**
  * @}
  */


/** @addtogroup ADC_LL_Configuration_Channels Configuration of ADC hierarchical scope: channels
  * @{
  */
/**
  * @brief  Set sampling time of the selected ADC channel Unit: ADC clock cycles.
  * @note   On this device, sampling time is on channel scope: independently
  *         of channel mapped on ADC group regular or injected.
  * @note   sampling time constraints must be respected (sampling time can be
  *         adjusted in function of ADC clock frequency and sampling time
  *         setting).
  * @note   Conversion time is the addition of sampling time and processing time.
  *         ADC processing time is: 12.5 ADC clock cycles at ADC resolution 12 bits
  * @param  Instance ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref ADC_CHANNEL_0
  *         @arg @ref ADC_CHANNEL_1
  *         @arg @ref ADC_CHANNEL_2
  *         @arg @ref ADC_CHANNEL_3
  *         @arg @ref ADC_CHANNEL_4
  *         @arg @ref ADC_CHANNEL_5
  *         @arg @ref ADC_CHANNEL_6
  *         @arg @ref ADC_CHANNEL_7
  *         @arg @ref ADC_CHANNEL_8
  *         @arg @ref ADC_CHANNEL_9
  *         @arg @ref ADC_CHANNEL_10
  *         @arg @ref ADC_CHANNEL_TEMPSENSOR
  * @param  SamplingTime This parameter can be one of the following values:
  *         @arg @ref ADC_SAMPLINGTIME_6CYCLES
  *         @arg @ref ADC_SAMPLINGTIME_18CYCLES
  *         @arg @ref ADC_SAMPLINGTIME_42CYCLES
  *         @arg @ref ADC_SAMPLINGTIME_90CYCLES
  *         @arg @ref ADC_SAMPLINGTIME_186CYCLES
  *         @arg @ref ADC_SAMPLINGTIME_378CYCLES
  *         @arg @ref ADC_SAMPLINGTIME_762CYCLES
  *         @arg @ref ADC_SAMPLINGTIME_1530CYCLES
  * @retval None
  */

#define __LL_ADC_SetChannelSamplingTime(__INSTANCE__, __CHANNEL__, __SAMPTIME__)                         \
    (__CHANNEL__ > 7) ?                                                                                  \
    MODIFY_REG((__INSTANCE__)->SMPR1,  ADC_SMPR1_SMP8 << ((__CHANNEL__ - 8) << ADC_SMPRX_REGOFFSET),    \
    ((__SAMPTIME__) << ((__CHANNEL__ - 8) << ADC_SMPRX_REGOFFSET))) :                                    \
    MODIFY_REG((__INSTANCE__)->SMPR0, ADC_SMPR0_SMP0 << ((__CHANNEL__) << ADC_SMPRX_REGOFFSET),          \
    ((__SAMPTIME__)   << ((__CHANNEL__) << ADC_SMPRX_REGOFFSET)))

/**
  * @brief  Get sampling time of the selected ADC channel Unit: ADC clock cycles.
  * @note   sampling time is on channel scope: independently
  *         of channel mapped on ADC group regular or injected.
  * @note   Conversion time is the addition of sampling time and processing time.
  * @param  Instance ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref ADC_CHANNEL_0
  *         @arg @ref ADC_CHANNEL_1
  *         @arg @ref ADC_CHANNEL_2
  *         @arg @ref ADC_CHANNEL_3
  *         @arg @ref ADC_CHANNEL_4
  *         @arg @ref ADC_CHANNEL_5
  *         @arg @ref ADC_CHANNEL_6
  *         @arg @ref ADC_CHANNEL_7
  *         @arg @ref ADC_CHANNEL_8
  *         @arg @ref ADC_CHANNEL_9
  *         @arg @ref ADC_CHANNEL_10
  *         @arg @ref ADC_CHANNEL_TEMPSENSOR
  * @param  SamplingTime This parameter can be one of the following values:
  *         @arg @ref ADC_SAMPLINGTIME_6CYCLES
  *         @arg @ref ADC_SAMPLINGTIME_18CYCLES
  *         @arg @ref ADC_SAMPLINGTIME_42CYCLES
  *         @arg @ref ADC_SAMPLINGTIME_90CYCLES
  *         @arg @ref ADC_SAMPLINGTIME_186CYCLES
  *         @arg @ref ADC_SAMPLINGTIME_378CYCLES
  *         @arg @ref ADC_SAMPLINGTIME_762CYCLES
  *         @arg @ref ADC_SAMPLINGTIME_1530CYCLES
  */
#define __LL_ADC_GetChannelSamplingTime(__INSTANCE__, __CHANNEL__)  (__CHANNEL__ > 7) ?                   \
    (READ_BIT((__INSTANCE__)->SMPR1, ADC_SMPR1_SMP8 << (((__CHANNEL__ - 8) << ADC_SMPRX_REGOFFSET)))) : \
    (READ_BIT((__INSTANCE__)->SMPR0, ADC_SMPR0_SMP0 << (((__INSTANCE__) << ADC_SMPRX_REGOFFSET))))


/**
  * @brief  Set mode single-ended or differential input of the selected
  *         ADC channel.
  *         In differential mode: Differential measurement is carried out
  *         between the selected channel 'i' (positive input) and
  *         channel 'i+1' (negative input). Only channel 'i' has to be
  *         configured, channel 'i+1' is configured automatically.
  * @note   For example, internal channels (VrefInt, TempSensor, ...) are
  *         not available in differential mode.
  * @note   When configuring a channel 'i' in differential mode,
  *         the channel 'i+1' is not usable separately.refer to device datasheet
  *         for more details.
  * @note   For ADC channels configured in differential mode, both inputs
  *         should be biased at (Vref+)/2 +/-200mV.
  *         (Vref+ is the analog voltage reference)
  * @param  Instance ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref ADC_CHANNEL_0
  *         @arg @ref ADC_CHANNEL_1
  *         @arg @ref ADC_CHANNEL_2
  *         @arg @ref ADC_CHANNEL_3
  *         @arg @ref ADC_CHANNEL_4
  *         @arg @ref ADC_CHANNEL_5
  *         @arg @ref ADC_CHANNEL_6
  *         @arg @ref ADC_CHANNEL_7
  *         @arg @ref ADC_CHANNEL_8
  *         @arg @ref ADC_CHANNEL_9
  *         @arg @ref ADC_CHANNEL_10
  *         @arg @ref ADC_CHANNEL_TEMPSENSOR
  * @param  SingleDiff This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_SINGLE_ENDED
  *         @arg @ref LL_ADC_DIFFERENTIAL_ENDED
  * @retval None
  */
#define __LL_ADC_SetChannelSingleDiff(__INSTANCE__, __CHANNEL__, __SINGLEDIFF__)        \
    MODIFY_REG((__INSTANCE__)->DIFSEL,                                                  \
               ADC_SINGLEDIFF_CHANNEL_SHIFT << (__CHANNEL__),                           \
               (((__SINGLEDIFF__) & ADC_SINGLEDIFF_CHANNEL_SHIFT) << (__CHANNEL__)))

/**
  * @brief  Get mode single-ended or differential input of the selected
  *         ADC channel.
  *         In differential mode: Differential measurement is carried out
  *         between the selected channel 'i' (positive input) and
  *         channel 'i+1' (negative input). Only channel 'i' has to be
  *         configured, channel 'i+1' is configured automatically.
  * @note   For example, internal channels (VrefInt, TempSensor, ...) are
  *         not available in differential mode.
  * @note   When configuring a channel 'i' in differential mode,
  *         the channel 'i+1' is not usable separately.refer to device datasheet
  *         for more details.
  * @note   For ADC channels configured in differential mode, both inputs
  *         should be biased at (Vref+)/2 +/-200mV.
  *         (Vref+ is the analog voltage reference)
  * @param  Instance ADC instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref ADC_CHANNEL_0
  *         @arg @ref ADC_CHANNEL_1
  *         @arg @ref ADC_CHANNEL_2
  *         @arg @ref ADC_CHANNEL_3
  *         @arg @ref ADC_CHANNEL_4
  *         @arg @ref ADC_CHANNEL_5
  *         @arg @ref ADC_CHANNEL_6
  *         @arg @ref ADC_CHANNEL_7
  *         @arg @ref ADC_CHANNEL_8
  *         @arg @ref ADC_CHANNEL_9
  *         @arg @ref ADC_CHANNEL_10
  *         @arg @ref ADC_CHANNEL_TEMPSENSOR
  * @retval  SingleDiff This parameter can be a combination of the following values:
  *         @arg @ref LL_ADC_SINGLE_ENDED
  *         @arg @ref LL_ADC_DIFFERENTIAL_ENDED
  */
#define __LL_ADC_GetChannelSingleDiff(__INSTANCE__, __CHANNEL__)                                \
        ((READ_BIT((__INSTANCE__)->DIFSEL, ADC_SINGLEDIFF_CHANNEL_SHIFT << (__CHANNEL__)) ==    \
        (ADC_SINGLEDIFF_CHANNEL_SHIFT << (__CHANNEL__))) ? 0x1U  : 0x0U)

/**
  * @}
  */


/** @addtogroup ADC_LL_Configuration_ADC_AnalogWatchdog Configuration of ADC transversal scope: analog watchdog
  * @{
  */
/**
  * @brief  Set ADC analog watchdog monitored channels:
  *         a single channel, multiple channels or all channels,
  * @note   Once monitored channels are selected, analog watchdog
  *         is enabled.
  * @note   In case of need to define a single channel to monitor
  *         with analog watchdog from sequencer channel definition,
  * @note   Analog watchdog instance:
  *         - AWD standard (instance AWD0\1\2):
  *           - channels monitored: can monitor 1 channel or all channels.
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @param  Instance ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref ADC_AWD0
  *         @arg @ref ADC_AWD1
  *         @arg @ref ADC_AWD2
  * @param  AWDChannelGroup This parameter can combination of the following values:
  *         @arg @ref ADC_AWD_DISABLE
  *         @arg @ref ADC_AWD_ALL_CHANNELS
  *         @arg @ref ADC_AWD_CHANNEL_0
  *         @arg @ref ADC_AWD_CHANNEL_1
  *         @arg @ref ADC_AWD_CHANNEL_2
  *         @arg @ref ADC_AWD_CHANNEL_3
  *         @arg @ref ADC_AWD_CHANNEL_4
  *         @arg @ref ADC_AWD_CHANNEL_5
  *         @arg @ref ADC_AWD_CHANNEL_6
  *         @arg @ref ADC_AWD_CHANNEL_7
  *         @arg @ref ADC_AWD_CHANNEL_8
  *         @arg @ref ADC_AWD_CHANNEL_9
  *         @arg @ref ADC_AWD_CHANNEL_10
  *         @arg @ref ADC_AWD_CHANNEL_11
  * @retval None
  */
#define __LL_ADC_SetAnalogWDMonitChannels(__INSTANCE__, __AWDY__, __AWDCHANNEL__)   \
        MODIFY_REG((__INSTANCE__)->AWDCR[__AWDY__], ADC_AWD0CR_AWD0CH, __AWDCHANNEL__)

/**
  * @brief  Get ADC analog watchdog monitored channel.
  * @note   Usage of the returned channel number:
  * @note   Once monitored channels are selected, analog watchdog is enabled.
  * @note   In case of need to define a single channel to monitor
  *         with analog watchdog from sequencer channel definition,
  * @param  Instance ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref ADC_AWD0
  *         @arg @ref ADC_AWD1
  *         @arg @ref ADC_AWD2
  * @retval Returned value can be one of the following values:
  *         @arg @ref ADC_AWD_DISABLE
  *         @arg @ref ADC_AWD_ALL_CHANNELS
  *         @arg @ref ADC_AWD_CHANNEL_0
  *         @arg @ref ADC_AWD_CHANNEL_1
  *         @arg @ref ADC_AWD_CHANNEL_2
  *         @arg @ref ADC_AWD_CHANNEL_3
  *         @arg @ref ADC_AWD_CHANNEL_4
  *         @arg @ref ADC_AWD_CHANNEL_5
  *         @arg @ref ADC_AWD_CHANNEL_6
  *         @arg @ref ADC_AWD_CHANNEL_7
  *         @arg @ref ADC_AWD_CHANNEL_8
  *         @arg @ref ADC_AWD_CHANNEL_9
  *         @arg @ref ADC_AWD_CHANNEL_10
  *         @arg @ref ADC_AWD_CHANNEL_11
  */
#define __LL_ADC_GetAnalogWDMonitChannels(__INSTANCE__, __AWDY__)    \
        READ_BIT((Instance->AWDCR[AWDy]), ADC_AWD0CR_AWD0CH & ADC_AWD_ALL_CHANNELS)

/**
  * @brief  Set ADC analog watchdog thresholds value of both thresholds
  *         high and low.
  * @note   If value of only one threshold high or low must be set,
  *         use function @ref LL_ADC_SetAnalogWDThresholds().
  * @note   In case of ADC resolution different of 16 bits.
  * @note   Analog watchdog instance:
  *         - AWD standard (instance AWD0\1\2):
  *           - channels monitored: can monitor 1 channel or all channels.
  *           - groups monitored: ADC groups regular and-or injected.
  * @note   ADC data register bitfield [15:0] (16 most significant bits).
  * @param  Instance ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref ADC_AWD0
  *         @arg @ref ADC_AWD1
  *         @arg @ref ADC_AWD2
  * @param  AWDThresholdHighValue Value between Min_Data=0x0000 and Max_Data=0xFFFF
  * @param  AWDThresholdLowValue Value between Min_Data=0x0000 and Max_Data=0xFFFF
  * @retval None
  */
#define __LL_ADC_ConfigAnalogWDThresholds(__INSTANCE__, __AWDY__, __HIGHVALUE__, __LOWVALUE__)  \
        WRITE_REG((__INSTANCE__)->TR[__AWDY__], ((__HIGHVALUE__) << ADC_AWD_THRESHOLDS_HIGH_POS) | (__LOWVALUE__))

/**
  * @brief  Set ADC analog watchdog threshold value of threshold
  *         high or low.
  * @note   If value of only one threshold high or low must be set,
  *         use function @ref LL_ADC_SetAnalogWDThresholds().
  * @note   In case of ADC resolution different of 16 bits.
  * @note   Analog watchdog instance:
  *         - AWD standard (instance AWD0\1\2):
  *           - channels monitored: can monitor 1 channel or all channels.
  *           - groups monitored: ADC groups regular and-or injected.
  * @note   ADC data register bitfield [15:0] (16 most significant bits).
  * @param  Instance ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref ADC_AWD0
  *         @arg @ref ADC_AWD1
  *         @arg @ref ADC_AWD2
  * @param  AWDThresholdsHighLow This parameter can be one of the following values:
  *         @arg @ref ADC_AWD_THRESHOLD_HIGH
  *         @arg @ref ADC_AWD_THRESHOLD_LOW
  * @param  AWDThresholdValue Value between Min_Data=0x0000 and Max_Data=0xFFFF
  * @retval None
  */
#define __LL_ADC_SetAnalogWDThresholds(__INSTANCE__, __AWDY__, __SIGN__, __VALUE__)     \
        MODIFY_REG((__INSTANCE__)->TR[__AWDY__], (__SIGN__),                             \
        ((((__VALUE__) << ADC_AWD_THRESHOLDS_HIGH_POS) | (__VALUE__)) & __SIGN__))

/**
  * @brief  Set ADC analog watchdog filtering configuration
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @param  Instance ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref ADC_AWD0\1\2
  * @param  FilteringConfig This parameter can be one of the following values:
  *         @arg @ref ADC_AWD_FILTERING_NONE
  *         @arg @ref ADC_AWD_FILTERING_2
  *         @arg @ref ADC_AWD_FILTERING_3
  *         @arg @ref ADC_AWD_FILTERING_4
  *         @arg @ref ADC_AWD_FILTERING_5
  *         @arg @ref ADC_AWD_FILTERING_6
  *         @arg @ref ADC_AWD_FILTERING_7
  *         @arg @ref ADC_AWD_FILTERING_8
  *         @arg @ref ADC_AWD_FILTERING_9
  *         @arg @ref ADC_AWD_FILTERING_10
  *         @arg @ref ADC_AWD_FILTERING_11
  *         @arg @ref ADC_AWD_FILTERING_12
  *         @arg @ref ADC_AWD_FILTERING_13
  *         @arg @ref ADC_AWD_FILTERING_14
  *         @arg @ref ADC_AWD_FILTERING_15
  *         @arg @ref ADC_AWD_FILTERING_16
  * @retval None
  */
#define __LL_ADC_SetAWDFilteringConfiguration(__INSTANCE__, __AWDY__, __AWDFILTER__)         \
    MODIFY_REG((__INSTANCE__)->AWDCR[__AWDY__], ADC_AWD0CR_AWD0FILT, (__AWDFILTER__))

/**
  * @brief  Get ADC analog watchdog filtering configuration
  *  @note  On this TMF5 serie, this feature is only available on first
  *         analog watchdog (AWD0\1\2)
  * @param  Instance ADC instance
  * @param  AWDy This parameter can be one of the following values:
  *         @arg @ref ADC_AWD0\1\2
  * @param  FilteringConfig This parameter can be one of the following values:
  *         @arg @ref ADC_AWD_FILTERING_NONE
  *         @arg @ref ADC_AWD_FILTERING_2
  *         @arg @ref ADC_AWD_FILTERING_3
  *         @arg @ref ADC_AWD_FILTERING_4
  *         @arg @ref ADC_AWD_FILTERING_5
  *         @arg @ref ADC_AWD_FILTERING_6
  *         @arg @ref ADC_AWD_FILTERING_7
  *         @arg @ref ADC_AWD_FILTERING_8
  *         @arg @ref ADC_AWD_FILTERING_9
  *         @arg @ref ADC_AWD_FILTERING_10
  *         @arg @ref ADC_AWD_FILTERING_11
  *         @arg @ref ADC_AWD_FILTERING_12
  *         @arg @ref ADC_AWD_FILTERING_13
  *         @arg @ref ADC_AWD_FILTERING_14
  *         @arg @ref ADC_AWD_FILTERING_15
  *         @arg @ref ADC_AWD_FILTERING_16
  */
#define __LL_ADC_GetAWDFilteringConfiguration(__INSTANCE__, __AWDY__)   \
        READ_BIT((__INSTANCE__)->AWDCR[__AWDY__], ADC_AWD0CR_AWD0FILT)
/**
  * @}
  */


/** @addtogroup ADC_LL_Configuration_ADC_oversampling Configuration of ADC transversal scope: oversampling
  * @{
  */
/**
  * @brief  Set ADC oversampling scope: ADC groups regular and-or injected.
  * @note   If both groups regular and injected are selected,
  *         specify behavior of ADC group injected interrupting
  *         group regular: when ADC group injected is triggered,
  *         the oversampling on ADC group regular is either
  *         temporary stopped and continued, or resumed from start
  *         (oversampler buffer reset).
  *         ADC must be disabled or enabled without conversion on going
  *         on either groups regular or injected.
  * @param  Instance ADC instance
  * @param  This parameter can be one of the following values:
  *         @arg @ref ADC_OVS_DISABLE
  *         @arg @ref ADC_OVS_GRP_REGULAR_CONTINUED
  *         @arg @ref ADC_OVS_GRP_REGULAR_RESUMED
  *         @arg @ref ADC_OVS_GRP_INJECTED
  *         @arg @ref ADC_OVS_GRP_INJ_REG_RESUMED
  * @retval None
  */
#define __LL_ADC_SetOverSamplingScope(__INSTANCE__, __OVRSCOPE__)   \
        MODIFY_REG((__INSTANCE__)->CR1, ADC_CR1_ROVSE | ADC_CR1_JOVSE | ADC_CR1_ROVSM, __OVRSCOPE__)

/**
  * @brief  Get ADC oversampling scope: ADC groups regular and-or injected.
  * @note   If both groups regular and injected are selected,
  *         specify behavior of ADC group injected interrupting
  *         group regular: when ADC group injected is triggered,
  *         the oversampling on ADC group regular is either
  *         temporary stopped and continued, or resumed from start
  *         (oversampler buffer reset).
  * @param  Instance ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref ADC_OVS_DISABLE
  *         @arg @ref ADC_OVS_GRP_REGULAR_CONTINUED
  *         @arg @ref ADC_OVS_GRP_REGULAR_RESUMED
  *         @arg @ref ADC_OVS_GRP_INJECTED
  *         @arg @ref ADC_OVS_GRP_INJ_REG_RESUMED
  */
#define __LL_ADC_GetOverSamplingScope(__INSTANCE__)     \
        READ_BIT((__INSTANCE__)->CR1, ADC_CR1_ROVSE | ADC_CR1_JOVSE | ADC_CR1_ROVSM)

/**
  * @brief  Set ADC oversampling discontinuous mode (triggered mode)
  *         on the selected ADC group.
  * @note   Number of oversampled conversions are done either in:
  *         - continuous mode (all conversions of oversampling ratio
  *           are done from 1 trigger)
  *         - discontinuous mode (each conversion of oversampling ratio
  *           needs a trigger)
  * @note   oversampling discontinuous mode (triggered mode) can be used only
  *         when oversampling is set on group regular only and in resumed mode.
  * @param  Instance ADC instance
  * @param  OverSamplingDiscont This parameter can be one of the following values:
  *         @arg @ref ADC_OVS_REG_CONT
  *         @arg @ref ADC_OVS_REG_DISCONT
  * @retval None
  */
#define __LL_ADC_SetOverSamplingDiscont(__INSTANCE__, __TROVS__)     MODIFY_REG((__INSTANCE__)->CR1, ADC_CR1_TROVS, (__TROVS__))

/**
  * @brief  Get ADC oversampling discontinuous mode (triggered mode)
  *         on the selected ADC group.
  * @note   Number of oversampled conversions are done either in:
  *         - continuous mode (all conversions of oversampling ratio
  *           are done from 1 trigger)
  *         - discontinuous mode (each conversion of oversampling ratio
  *           needs a trigger)
  * @param  Instance ADC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref ADC_OVS_REG_CONT
  *         @arg @ref ADC_OVS_REG_DISCONT
  */
#define __LL_ADC_GetOverSamplingDiscont(__INSTANCE__)                READ_BIT((__INSTANCE__)->CR1, ADC_CR1_TROVS)

/**
  * @brief  Set ADC oversampling
  *         (impacting both ADC groups regular and injected)
  * @note   This function set the 2 items of oversampling configuration:
  *         - ratio
  *         - shift
  * @param  Instance ADC instance
  * @param  Ratio This parameter can be one of the following values:
  *         @arg @ref ADC_OVSR_RATIO_2
  *         @arg @ref ADC_OVSR_RATIO_4
  *         @arg @ref ADC_OVSR_RATIO_8
  *         @arg @ref ADC_OVSR_RATIO_16
  *         @arg @ref ADC_OVSR_RATIO_32
  *         @arg @ref ADC_OVSR_RATIO_64
  *         @arg @ref ADC_OVSR_RATIO_128
  *         @arg @ref ADC_OVSR_RATIO_256
  * @param  Shift This parameter can be one of the following values:
  *         @arg @ref ADC_OVSS_SHIFT_NONE
  *         @arg @ref ADC_OVSS_SHIFT_RIGHT_1
  *         @arg @ref ADC_OVSS_SHIFT_RIGHT_2
  *         @arg @ref ADC_OVSS_SHIFT_RIGHT_3
  *         @arg @ref ADC_OVSS_SHIFT_RIGHT_4
  *         @arg @ref ADC_OVSS_SHIFT_RIGHT_5
  *         @arg @ref ADC_OVSS_SHIFT_RIGHT_6
  *         @arg @ref ADC_OVSS_SHIFT_RIGHT_7
  *         @arg @ref ADC_OVSS_SHIFT_RIGHT_8
  * @retval None
  */
#define __LL_ADC_ConfigOverSamplingRatioShift(__INSTANCE__, __RATIO__, __SHIFT__)   \
        MODIFY_REG((__INSTANCE__)->CR1, (ADC_CR1_OVSS | ADC_CR1_OVSR), (__SHIFT__ | __RATIO__))

/**
  * @brief  Get ADC oversampling ratio
  *        (impacting both ADC groups regular and injected)
  * @param  Instance ADC instance
  * @retval Ratio This parameter can be one of the following values:
  *         @arg @ref ADC_OVSR_RATIO_2
  *         @arg @ref ADC_OVSR_RATIO_4
  *         @arg @ref ADC_OVSR_RATIO_8
  *         @arg @ref ADC_OVSR_RATIO_16
  *         @arg @ref ADC_OVSR_RATIO_32
  *         @arg @ref ADC_OVSR_RATIO_64
  *         @arg @ref ADC_OVSR_RATIO_128
  *         @arg @ref ADC_OVSR_RATIO_256
  */
#define __LL_ADC_GetOverSamplingRatio(__INSTANCE__)          READ_BIT((__INSTANCE__)->CR1, ADC_CR1_OVSR)

/**
  * @brief  Get ADC oversampling shift
  *        (impacting both ADC groups regular and injected)
  * @param  Instance ADC instance
  * @retval Shift This parameter can be one of the following values:
  *         @arg @ref ADC_OVS_SHIFT_NONE
  *         @arg @ref ADC_OVS_SHIFT_RIGHT_1
  *         @arg @ref ADC_OVS_SHIFT_RIGHT_2
  *         @arg @ref ADC_OVS_SHIFT_RIGHT_3
  *         @arg @ref ADC_OVS_SHIFT_RIGHT_4
  *         @arg @ref ADC_OVS_SHIFT_RIGHT_5
  *         @arg @ref ADC_OVS_SHIFT_RIGHT_6
  *         @arg @ref ADC_OVS_SHIFT_RIGHT_7
  *         @arg @ref ADC_OVS_SHIFT_RIGHT_8
  */
#define __LL_ADC_GetOverSamplingShift(__INSTANCE__)          READ_BIT((__INSTANCE__)->CR1, ADC_CR1_OVSS)
/**
  * @}
  */


/** @addtogroup ADC_LL_Operation_ADC_Group_Injected Operation on ADC hierarchical scope: group injected
  * @{
  */
/**
  * @brief  Start ADC group injected conversion.
  * @note   This function is relevant for both internal trigger (SW start) and external trigger:
  *         - If ADC trigger has been set to software start, ADC conversion
  *           starts immediately.
  *         - If ADC trigger has been set to external trigger, ADC conversion
  *           will start at next trigger event (on the selected trigger edge)
  *           following the ADC start conversion command.
  * @note   Setting of this feature is conditioned to ADC state:
  *         ADC must be enabled without conversion on going on group injected,
  *         without conversion stop command on going on group injected.
  * @param  Instance ADC instance
  * @retval None
  */
#define __LL_ADC_INJ_StartConversion(__INSTANCE__)   MODIFY_REG((__INSTANCE__)->CR0, ADC_CR0_BITS_PROPERTY_RS, ADC_CR0_JADSTART)

/**
  * @brief  Stop ADC group injected conversion.
  * @note   Setting of this feature is conditioned to ADC state:
  *         ADC must be enabled with conversion on going on group injected,
  *         without ADC disable command on going.
  * @param  Instance ADC instance
  * @retval None
  */
#define __LL_ADC_INJ_StopConversion(__INSTANCE__)    MODIFY_REG((__INSTANCE__)->CR0, ADC_CR0_BITS_PROPERTY_RS, ADC_CR0_JADSTP)

/**
  * @brief  Get ADC group injected conversion state.
  * @param  Instance ADC instance
  * @retval 0: no conversion is on going on ADC group injected.
  */
#define __LL_ADC_INJ_IsConversionOngoing(__INSTANCE__)          \
        ((READ_BIT((__INSTANCE__)->CR0, ADC_CR0_JADSTART) == (ADC_CR0_JADSTART)) ? 1UL : 0UL)

/**
  * @brief  Get ADC group injected command of conversion stop state
  * @param  Instance ADC instance
  * @retval 0: no command of conversion stop is on going on ADC group injected.
  */
#define __LL_ADC_INJ_IsStopConversionOngoing(__INSTANCE__)      \
        ((READ_BIT((__INSTANCE__)->CR0, ADC_CR0_JADSTP) == (ADC_CR0_JADSTP)) ? 1UL : 0UL)

/**
  * @brief  Get ADC group injected conversion data, range fit for
  *         all ADC configurations.
  * @param  Instance ADC instance
  * @param  Rank This parameter can be one of the following values:
  *         @arg @ref ADC_INJ_RANK_1
  *         @arg @ref ADC_INJ_RANK_2
  *         @arg @ref ADC_INJ_RANK_3
  *         @arg @ref ADC_INJ_RANK_4
  * @retval Value between Min_Data=0x0000 and Max_Data=0xFFFF
  */
#define __LL_ADC_INJ_ReadConversionData(__INSTANCE__, __RANK__)     \
        READ_BIT((__INSTANCE__)->JDR[(__RANK__) >> ADC_JSQX_REGOFFSET], ADC_JDR0_JDATA)

/**
  * @}
  */


/** @addtogroup ADC_LL_ECU related register interface functions are configured in the ADC
  * @{
  */
/**
  * @brief  Sets the source channel for the data Address flag bit.
  * @note   The linkage with the ECU must work in DMA cycle mode.
  * @param  Instance ADC instance
  * @param  GroupSel ADC_ECR_GROUP_SEL
  * @param  Channel ADC_CHANNEL
  * @retval None
  */
#define __LL_ADC_ECU_SetAddrDataFlag(__INSTANCE__, __GROUP__, __CHANNLE__)  \
        MODIFY_REG((__INSTANCE__)->ECR[__GROUP__], ADC_ECR0_ADSRC, ((__CHANNLE__) << ADC_ECR0_ADSRC_Pos))

/**
  * @brief  Set PINGPONG to rise and fall over zero and choose which watchdog to monitor.
  * @note   Try to use different watchdogs for ascending and
  *         descending zero - crossing monitoring.
  * @param  Instance ADC instance
  * @param  GroupSel ADC_ECR_GROUP_SEL
  * @param  UpZeroAWD the range of value AWD0\1\2
  * @param  DownZeroAWD the range of value AWD0\1\2
  * @retval None
  */
#define __LL_ADC_ECU_SetUpDownPPFlag(__INSTANCE__, __GROUP__, __UPAWD__, __DOWNAWD__)           \
        MODIFY_REG((__INSTANCE__)->ECR[__GROUP__],                                              \
               ADC_ECR0_PSRCU | ADC_ECR0_PSRCD,                                                 \
               (((__UPAWD__) << ADC_ECR0_PSRCU_Pos) | ((__DOWNAWD__) << ADC_ECR0_PSRCD_Pos)))

/**
  * @brief  Set up a watch-dog 2 monitoring channel.
  * @note   The selected channel for ascending and descending zero crossing
  *         monitoring watchdog must be configured to be the same.
  * @param  Instance ADC instance
  * @param  GroupSel ADC_ECR_GROUP_SEL
  * @param  Channel ADC_CHANNEL
  * @retval None
  */
#define __LL_ADC_ECU_SetAWD2Channel(__INSTANCE__, __GROUP__, __CHANNLE__)   \
        MODIFY_REG((__INSTANCE__)->ECR[__GROUP__], ADC_ECR0_AWD2SEL, ((__CHANNLE__) << ADC_ECR0_AWD2SEL_Pos))

/**
  * @brief  Set up a watch-dog 1 monitoring channel.
  * @note   The selected channel for ascending and descending zero crossing
  *         monitoring watchdog must be configured to be the same.
  * @param  Instance ADC instance
  * @param  GroupSel ADC_ECR_GROUP_SEL
  * @param  Channel ADC_CHANNEL
  * @retval None
  */
#define __LL_ADC_ECU_SetAWD1Channel(__INSTANCE__, __GROUP__, __CHANNLE__)   \
        MODIFY_REG((__INSTANCE__)->ECR[__GROUP__], ADC_ECR0_AWD1SEL, ((__CHANNLE__) << ADC_ECR0_AWD1SEL_Pos))

/**
  * @brief  Set up a watch-dog 0 monitoring channel.
  * @note   The selected channel for ascending and descending zero crossing
  *         monitoring watchdog must be configured to be the same.
  * @param  Instance ADC instance
  * @param  GroupSel ADC_ECR_GROUP_SEL
  * @param  Channel ADC_CHANNEL
  * @retval None
  */
#define __LL_ADC_ECU_SetAWD0Channel(__INSTANCE__, __GROUP__, __CHANNLE__)   \
        MODIFY_REG((__INSTANCE__)->ECR[__GROUP__], ADC_ECR0_AWD0SEL, ((__CHANNLE__) << ADC_ECR0_AWD0SEL_Pos))

/**
  * @}
  */
  

/** @addtogroup ADC_LL_FLAG_Management ADC normal flag management
  * @{
  */
/**
  * @brief  Get flag ADC ready.
  * @note   Flag ADC_FLAG_ADRDY is raised when the ADC
  *         is enabled and when conversion clock is active.
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define __LL_ADC_GET_FLAG_ADRDY(__INSTANCE__)   ((READ_BIT((__INSTANCE__)->ISR, ADC_FLAG_ADRDY) == (ADC_FLAG_ADRDY)) ? 1UL : 0UL)

/**
  * @brief  Get flag ADC group regular end of unitary conversion.
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define __LL_ADC_GET_FLAG_EOC(__INSTANCE__)     ((READ_BIT((__INSTANCE__)->ISR, ADC_FLAG_EOC) == (ADC_FLAG_EOC)) ? 1UL : 0UL)

/**
  * @brief  Get flag ADC group regular end of sequence conversions.
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define __LL_ADC_GET_FLAG_EOS(__INSTANCE__)     ((READ_BIT((__INSTANCE__)->ISR, ADC_FLAG_EOS) == (ADC_FLAG_EOS)) ? 1UL : 0UL)

/**
  * @brief  Get flag ADC group regular overrun.
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define __LL_ADC_GET_FLAG_OVR(__INSTANCE__)     ((READ_BIT((__INSTANCE__)->ISR, ADC_FLAG_OVR) == (ADC_FLAG_OVR)) ? 1UL : 0UL)

/**
  * @brief  Get flag ADC group regular end of sampling phase.
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define __LL_ADC_GET_FLAG_EOSMP(__INSTANCE__)   ((READ_BIT((__INSTANCE__)->ISR, ADC_FLAG_EOSMP) == (ADC_FLAG_EOSMP)) ? 1UL : 0UL)

/**
  * @brief  Get flag ADC group injected end of unitary conversion.
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define __LL_ADC_GET_FLAG_JEOC(__INSTANCE__)    ((READ_BIT((__INSTANCE__)->ISR, ADC_FLAG_JEOC) == (ADC_FLAG_JEOC)) ? 1UL : 0UL)

/**
  * @brief  Get flag ADC group injected end of sequence conversions.
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define __LL_ADC_GET_FLAG_JEOS(__INSTANCE__)    ((READ_BIT((__INSTANCE__)->ISR, ADC_FLAG_JEOS) == (ADC_FLAG_JEOS)) ? 1UL : 0UL)

/**
  * @brief  Get flag ADC analog watchdog 0 flag
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define __LL_ADC_GET_FLAG_AWD0(__INSTANCE__)    ((READ_BIT((__INSTANCE__)->ISR, ADC_FLAG_AWD0) == (ADC_FLAG_AWD0)) ? 1UL : 0UL)

/**
  * @brief  Get flag ADC analog watchdog 1.
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define __LL_ADC_GET_FLAG_AWD1(__INSTANCE__)    ((READ_BIT((__INSTANCE__)->ISR, ADC_FLAG_AWD1) == (ADC_FLAG_AWD1)) ? 1UL : 0UL)

/**
  * @brief  Get flag ADC analog watchdog 2.
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define __LL_ADC_GET_FLAG_AWD2(__INSTANCE__)    ((READ_BIT((__INSTANCE__)->ISR, ADC_FLAG_AWD2) == (ADC_FLAG_AWD2)) ? 1UL : 0UL)

/**
  * @brief  Clear flag ADC ready.
  * @note   Flag ADC_FLAG_ADRDY is raised when the ADC
  *         is enabled and when conversion clock is active.
  * @param  __INSTANCE__ ADC instance
  * @retval None
  */
#define __LL_ADC_CLEAR_FLAG_ADRDY(__INSTANCE__) WRITE_REG((__INSTANCE__)->ISR, ADC_FLAG_ADRDY)

/**
  * @brief  Clear flag ADC group regular end of unitary conversion.
  * @param  __INSTANCE__ ADC instance
  * @retval None
  */
#define __LL_ADC_CLEAR_FLAG_EOC(__INSTANCE__)    WRITE_REG((__INSTANCE__)->ISR, ADC_FLAG_EOC)

/**
  * @brief  Clear flag ADC group regular end of sequence conversions.
  * @param  __INSTANCE__ ADC instance
  * @retval None
  */
#define __LL_ADC_CLEAR_FLAG_EOS(__INSTANCE__)    WRITE_REG((__INSTANCE__)->ISR, ADC_FLAG_EOS)

/**
  * @brief  Clear flag ADC group regular overrun.
  * @param  __INSTANCE__ ADC instance
  * @retval None
  */
#define __LL_ADC_CLEAR_FLAG_OVR(__INSTANCE__)    WRITE_REG((__INSTANCE__)->ISR, ADC_FLAG_OVR)

/**
  * @brief  Clear flag ADC group regular end of sampling phase.
  * @param  __INSTANCE__ ADC instance
  * @retval None
  */
#define __LL_ADC_CLEAR_FLAG_EOSMP(__INSTANCE__)  WRITE_REG((__INSTANCE__)->ISR, ADC_FLAG_EOSMP)

/**
  * @brief  Clear flag ADC group injected end of unitary conversion.
  * @param  __INSTANCE__ ADC instance
  * @retval None
  */
#define __LL_ADC_CLEAR_FLAG_JEOC(__INSTANCE__)   WRITE_REG((__INSTANCE__)->ISR, ADC_FLAG_JEOC)

/**
  * @brief  Clear flag ADC group injected end of sequence conversions.
  * @param  __INSTANCE__ ADC instance
  * @retval None
  */
#define __LL_ADC_CLEAR_FLAG_JEOS(__INSTANCE__)   WRITE_REG((__INSTANCE__)->ISR, ADC_FLAG_JEOS)

/**
  * @brief  Clear flag ADC analog watchdog 0.
  * @param  __INSTANCE__ ADC instance
  * @retval None
  */
#define __LL_ADC_CLEAR_FLAG_AWD0(__INSTANCE__)   WRITE_REG((__INSTANCE__)->ISR, ADC_FLAG_AWD0)

/**
  * @brief  Clear flag ADC analog watchdog 1.
  * @param  __INSTANCE__ ADC instance
  * @retval None
  */
#define __LL_ADC_CLEAR_FLAG_AWD1(__INSTANCE__)   WRITE_REG((__INSTANCE__)->ISR, ADC_FLAG_AWD1)

/**
  * @brief  Clear flag ADC analog watchdog 2.
  * @param  __INSTANCE__ ADC instance
  * @retval None
  */
#define __LL_ADC_CLEAR_FLAG_AWD2(__INSTANCE__)   WRITE_REG((__INSTANCE__)->ISR, ADC_FLAG_AWD2)

/**
  * @}
  */


/** @addtogroup ADC_LL_IT_Management ADC IT management
  * @{
  */
/**
  * @brief  Enable the specified ADC interrupt.
  * @param  __INSTANCE__   ADC instance
  * @param  __INTERRUPT__  specifies the ADC flags to clear.
  *         This parameter can be any combination of @ref ADC_Flag_definition:
  *             @arg ADC_IT_ADRDY    ADC flag ADC instance ready
  *             @arg ADC_IT_EOC      ADC flag ADC group regular end of unitary conversion
  *             @arg ADC_IT_EOS      ADC flag ADC group regular end of sequence conversions
  *             @arg ADC_IT_OVR      ADC flag ADC group regular overrun
  *             @arg ADC_IT_EOSMP    ADC flag ADC group regular end of sampling phase
  *             @arg ADC_IT_JEOC     ADC flag ADC group injected end of unitary conversion
  *             @arg ADC_IT_JEOS     ADC flag ADC group injected end of sequence conversions
  *             @arg ADC_IT_AWD0     ADC flag ADC analog watchdog 1
  *             @arg ADC_IT_AWD1     ADC flag ADC analog watchdog 2
  *             @arg ADC_IT_AWD2     ADC flag ADC analog watchdog 3
  * @retval None
  */
#define __LL_ADC_ENABLE_IT(__INSTANCE__, __INTERRUPT__)      SET_BIT((__INSTANCE__)->IER, __INTERRUPT__)

/**
  * @brief  Disable the specified ADC interrupt.
  * @param  __INSTANCE__   ADC instance
  * @param  __INTERRUPT__  specifies the TMR flags to clear.
  *         This parameter can be any combination of @ref TMR_Flag_definition:
  *             @arg ADC_IT_ADRDY    ADC flag ADC instance ready
  *             @arg ADC_IT_EOC      ADC flag ADC group regular end of unitary conversion
  *             @arg ADC_IT_EOS      ADC flag ADC group regular end of sequence conversions
  *             @arg ADC_IT_OVR      ADC flag ADC group regular overrun
  *             @arg ADC_IT_EOSMP    ADC flag ADC group regular end of sampling phase
  *             @arg ADC_IT_JEOC     ADC flag ADC group injected end of unitary conversion
  *             @arg ADC_IT_JEOS     ADC flag ADC group injected end of sequence conversions
  *             @arg ADC_IT_AWD0     ADC flag ADC analog watchdog 1
  *             @arg ADC_IT_AWD1     ADC flag ADC analog watchdog 2
  *             @arg ADC_IT_AWD2     ADC flag ADC analog watchdog 3
  * @retval None
  */
#define __LL_ADC_DISABLE_IT(__INSTANCE__, __INTERRUPT__)     CLEAR_BIT((__INSTANCE__)->IER, __INTERRUPT__)

/**
  * @brief  Get state of interruption ADC ready
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */

#define __LL_ADC_GET_IT_ADRDY(__INSTANCE__)     ((READ_BIT((__INSTANCE__)->IER, ADC_IT_ADRDY) == (ADC_IT_ADRDY)) ? 1UL : 0UL)
/**
  * @brief  Get state of interruption ADC group regular end of unitary conversion
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define  __LL_ADC_GET_IT_EOC(__INSTANCE__)      ((READ_BIT((__INSTANCE__)->IER, ADC_IT_EOC) == (ADC_IT_EOC)) ? 1UL : 0UL)

/**
  * @brief  Get state of interruption ADC group regular end of sequence conversions
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define  __LL_ADC_GET_IT_EOS(__INSTANCE__)      ((READ_BIT((__INSTANCE__)->IER, ADC_IT_EOS) == (ADC_IT_EOS)) ? 1UL : 0UL)

/**
  * @brief  Get state of interruption ADC group regular overrun
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define  __LL_ADC_GET_IT_OVR(__INSTANCE__)      ((READ_BIT((__INSTANCE__)->IER, ADC_IT_OVR) == (ADC_IT_OVR)) ? 1UL : 0UL)

/**
  * @brief  Get state of interruption ADC group regular end of sampling
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define  __LL_ADC_GET_IT_EOSMP(__INSTANCE__)    ((READ_BIT((__INSTANCE__)->IER, ADC_IT_EOSMP) == (ADC_IT_EOSMP)) ? 1UL : 0UL)

/**
  * @brief  Get state of interruption ADC group injected end of unitary conversion
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define  __LL_ADC_GET_IT_JEOC(__INSTANCE__)     ((READ_BIT((__INSTANCE__)->IER, ADC_IT_JEOC) == (ADC_IT_JEOC)) ? 1UL : 0UL)

/**
  * @brief  Get state of interruption ADC group injected end of sequence conversions
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define  __LL_ADC_GET_IT_JEOS(__INSTANCE__)     ((READ_BIT((__INSTANCE__)->IER, ADC_IT_JEOS) == (ADC_IT_JEOS)) ? 1UL : 0UL)
/**
  * @brief  Get state of interruption Get ADC analog watchdog 0
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define  __LL_ADC_GET_IT_AWD0(__INSTANCE__)      ((READ_BIT((__INSTANCE__)->IER, ADC_IT_AWD0) == (ADC_IT_AWD0)) ? 1UL : 0UL)

/**
  * @brief  Get state of interruption ADC analog watchdog 1
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define  __LL_ADC_GET_IT_AWD1(__INSTANCE__)      ((READ_BIT((__INSTANCE__)->IER, ADC_IT_AWD1) == (ADC_IT_AWD1)) ? 1UL : 0UL)

/**
  * @brief  Get state of interruption Get ADC analog watchdog 2
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @param  __INSTANCE__ ADC instance
  * @retval State of bit (1 or 0).
  */
#define  __LL_ADC_GET_IT_AWD2(__INSTANCE__)     ((READ_BIT((__INSTANCE__)->IER, ADC_IT_AWD2) == (ADC_IT_AWD2)) ? 1UL : 0UL)

/**
  * @}
  */


/** @addtogroup ADC_LL_SAMP_INT_FLAG ADC Sample interrupt management
  * @{
  */
/**
  * @brief  Enable interruption ADC every channel Sample done.
  * @param  __INSTANCE__ ADC instance
  * @param  Channel 0~11
  * @retval None
  */
#define __LL_ADC_ENABLE_IT_DONE(__INSTANCE__, __CHANNEL__)      \
        SET_BIT((__INSTANCE__)->SIER, (ADC_SIER_CHANNEL_0 << (__CHANNEL__)))

/**
  * @brief  Disable interruption ADC every channel Sample done.
  * @param  __INSTANCE__ ADC instance
  * @param  Channel 0~11
  * @retval None
  */
#define __LL_ADC_DISABLE_IT_DONE(__INSTANCE__, __CHANNEL__)     \
    CLEAR_BIT((__INSTANCE__)->SIER, (ADC_SIER_CHANNEL_0 << (__CHANNEL__)))

/**
  * @brief  Get state of interruption Get ADC every channel Sample done.
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @param  __INSTANCE__ ADC instance
  * @param  Channel 0~11
  * @retval State of bit (1 or 0).
  */
#define __LL_ADC_GET_IT_DONE(__INSTANCE__, __CHANNEL__)                             \
        ((READ_BIT((__INSTANCE__)->SIER, (ADC_SIER_CHANNEL_0 << (__CHANNEL__))) ==  \
        ((ADC_SIER_CHANNEL_0 << (__CHANNEL__)))) ? 1UL : 0UL)

/**
  * @brief  Clear flag ADC every channel Sample done.
  * @param  __INSTANCE__ ADC instance
  * @param  Channel 0~11
  * @retval None
  */
#define __LL_ADC_CLEAR_FLAG_DONE(__INSTANCE__, __CHANNEL__)     \
        WRITE_REG((__INSTANCE__)->SISR, (ADC_SISR_CHANNEL_0 << (__CHANNEL__)))

/**
  * @brief  Get flagADC every channel Sample done.
  * @param  __INSTANCE__ ADC instance
  * @param  Channel 0~11
  * @retval State of bit (1 or 0).
  */
#define __LL_ADC_GET_FLAG_DONE(__INSTANCE__, __CHANNEL__)                           \
        ((READ_BIT((__INSTANCE__)->SISR, (ADC_SISR_CHANNEL_0 << (__CHANNEL__))) ==  \
        (ADC_SISR_CHANNEL_0 << (__CHANNEL__))) ? 1UL : 0UL)

/**
  * @}
  */


/** @addtogroup ADC_LL_HALF_INT_FLAG ADC Half interrupt management
  * @{
  */
/**
  * @brief  Enable interruption ADC every channel Sample done.
  * @param  __INSTANCE__ ADC instance
  * @param  Channel 0~11
  * @retval None
  */
#define __LL_ADC_ENABLE_IT_HALF(__INSTANCE__, __CHANNEL__)      \
        SET_BIT((__INSTANCE__)->HIER, (ADC_HIER_CHANNEL_0 << (__CHANNEL__)))

/**
  * @brief  Disable interruption ADC every channel Sample done.
  * @param  __INSTANCE__ ADC instance
  * @param  Channel 0~11
  * @retval None
  */
#define __LL_ADC_DISABLE_IT_HALF(__INSTANCE__, __CHANNEL__)     \
        CLEAR_BIT((__INSTANCE__)->HIER, (ADC_HIER_CHANNEL_0 << (__CHANNEL__)))

/**
  * @brief  Get state of interruption Get ADC every channel Sample done.
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @param  __INSTANCE__ ADC instance
  * @param  Channel 0~11
  * @retval State of bit (1 or 0).
  */
#define __LL_ADC_GET_IT_HALF(__INSTANCE__, __CHANNEL__)                             \
        ((READ_BIT((__INSTANCE__)->HIER, (ADC_HIER_CHANNEL_0 << (__CHANNEL__))) ==  \
        ((ADC_HIER_CHANNEL_0 << (__CHANNEL__)))) ? 1UL : 0UL)

/**
  * @brief  Clear flag ADC every channel Sample done.
  * @param  __INSTANCE__ ADC instance
  * @param  Channel 0~11
  * @retval None
  */
#define __LL_ADC_CLEAR_FLAG_HALF(__INSTANCE__, __CHANNEL__)     \
        WRITE_REG((__INSTANCE__)->HISR, (ADC_HISR_CHANNEL_0 << (__CHANNEL__)))

/**
  * @brief  Get flagADC every channel Sample done.
  * @param  __INSTANCE__ ADC instance
  * @param  Channel 0~11
  * @retval State of bit (1 or 0).
  */
#define __LL_ADC_GET_FLAG_HALF(__INSTANCE__, __CHANNEL__)                        \
    ((READ_BIT((__INSTANCE__)->HISR, (ADC_HISR_CHANNEL_0 << (__CHANNEL__))) ==  \
    (ADC_HISR_CHANNEL_0 << (__CHANNEL__))) ? 1UL : 0UL)

/**
  * @}
  */


/** @addtogroup ADC_LL_FULL_INT_FLAG ADC Full interrupt management
 * @{
 */
/**
  * @brief  Enable interruption ADC every channel Sample done.
  * @param  __INSTANCE__ ADC instance
  * @param  Channel 0~11
  * @retval None
  */
#define __LL_ADC_ENABLE_IT_FULL(__INSTANCE__, __CHANNEL__)      \
        SET_BIT((__INSTANCE__)->FIER, (ADC_FIER_CHANNEL_0 << (__CHANNEL__)))
/**
  * @brief  Disable interruption ADC every channel Sample done.
  * @param  __INSTANCE__ ADC instance
  * @param  Channel 0~11
  * @retval None
  */
#define __LL_ADC_DISABLE_IT_FULL(__INSTANCE__, __CHANNEL__)     \
        CLEAR_BIT((__INSTANCE__)->FIER, (ADC_FIER_CHANNEL_0 << (__CHANNEL__)))

/**
  * @brief  Get state of interruption Get ADC every channel Sample done.
  *         (0: interrupt disabled, 1: interrupt enabled).
  * @param  __INSTANCE__ ADC instance
  * @param  Channel 0~11
  * @retval State of bit (1 or 0).
  */
#define __LL_ADC_GET_IT_FULL(__INSTANCE__, __CHANNEL__)                             \
        ((READ_BIT((__INSTANCE__)->FIER, (ADC_FIER_CHANNEL_0 << (__CHANNEL__))) ==  \
        ((ADC_FIER_CHANNEL_0 << (__CHANNEL__)))) ? 1UL : 0UL)

/**
  * @brief  Clear flag ADC every channel Sample done.
  * @param  __INSTANCE__ ADC instance
  * @param  Channel 0~11
  * @retval None
  */
#define __LL_ADC_CLEAR_FLAG_FULL(__INSTANCE__, __CHANNEL__)     \
        WRITE_REG((__INSTANCE__)->FISR, (ADC_FISR_CHANNEL_0 << (__CHANNEL__)))

/**
  * @brief  Get flagADC every channel Sample done.
  * @param  __INSTANCE__ ADC instance
  * @param  Channel 0~11
  * @retval State of bit (1 or 0).
  */
#define __LL_ADC_GET_FLAG_FULL(__INSTANCE__, __CHANNEL__)                           \
        ((READ_BIT((__INSTANCE__)->FISR, (ADC_FISR_CHANNEL_0 << (__CHANNEL__))) ==  \
        (ADC_FISR_CHANNEL_0 << (__CHANNEL__))) ? 1UL : 0UL)

/**
  * @}
  */


/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADC_LL_Exported_Functions
  * @{
  */

/** @addtogroup ADC_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_ADC_Init(ADC_TypeDef *Instance, ADC_InitTypeDef *ADC_InitStruct);
LL_StatusETypeDef LL_ADC_DeInit(ADC_TypeDef *Instance);
LL_StatusETypeDef LL_ADC_REG_Init(ADC_TypeDef *Instance, ADC_REG_InitTypeDef *ADC_REG_InitStruct);
LL_StatusETypeDef LL_ADC_INJ_Init(ADC_TypeDef *Instance, ADC_INJ_InitTypeDef *ADC_INJ_InitStruct);
void LL_ADC_MspInit(ADC_TypeDef *Instance);
void LL_ADC_MspDeInit(ADC_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup ADC_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_ADC_ECU_Config(ADC_TypeDef *Instance, ADC_ECUConfTypeDef *ADC_ECU_Config);
LL_StatusETypeDef LL_ADC_AnalogWDGConfig(ADC_TypeDef *Instance, ADC_AnalogWDGCfgTypeDef *AnalogWDGConfig);
LL_StatusETypeDef LL_ADC_DMATransferConfig(ADC_TypeDef *Instance, ADC_DMATransferCfgTypeDef *DMATransferConfig);
LL_StatusETypeDef LL_ADC_CalibrationConfig(ADC_TypeDef *Instance, ADC_CalibrationTypeDef *CalibrationConfig);
float             LL_ADC_TemperatureCovert(uint16_t voltage_data);
/**
  * @}
  */


/** @addtogroup ADC_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_ADC_AdRdyCallback(ADC_TypeDef *Instance);
void LL_ADC_EosmpCallback(ADC_TypeDef *Instance);
void LL_ADC_AnologWD2Callback(ADC_TypeDef *Instance);
void LL_ADC_AnologWD1Callback(ADC_TypeDef *Instance);
void LL_ADC_AnologWD0Callback(ADC_TypeDef *Instance);
void LL_ADC_OverRunCallback(ADC_TypeDef *Instance);
void LL_ADC_JeosCallback(ADC_TypeDef *Instance);
void LL_ADC_EosCallback(ADC_TypeDef *Instance);
void LL_ADC_JeocCallback(ADC_TypeDef *Instance);
void LL_ADC_EocCallback(ADC_TypeDef *Instance);
void LL_ADC_SampCallback(ADC_TypeDef *Instance, uint8_t Channel);
void LL_ADC_HalfCallback(ADC_TypeDef *Instance, uint8_t Channel);
void LL_ADC_FullCallback(ADC_TypeDef *Instance, uint8_t Channel);

void LL_ADC_NORM_IRQHandler(ADC_TypeDef *Instance);
void LL_ADC_SAMP_IRQHandler(ADC_TypeDef *Instance, uint8_t Channel);
void LL_ADC_HALF_IRQHandler(ADC_TypeDef *Instance, uint8_t Channel);
void LL_ADC_FULL_IRQHandler(ADC_TypeDef *Instance, uint8_t Channel);
/**
  * @}
  */

/**
  * @}
  */


/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup ADC_LL_Private_Macros ADC LL Private Macros
  * @brief    ADC LL Private Macros
  * @{
  */

/**
  * @brief  Judge is ADC synchronization or not
  * @param  __SYNCHRONZATION__ synchronization to judge
  * @retval 0 isn't ADC synchronization
  * @retval 1 is ADC synchronization
  */
#define IS_ADC_SYNCHRONIZATION(__SYNCHRONZATION__)                    \
    (   ((__SYNCHRONZATION__) == ADC_SYNCEN_DIS)                      \
        || ((__SYNCHRONZATION__) == ADC_SYNCEN_EN)                    \
    )

/**
  * @brief  Judge is ADC over samp mode set or not
  * @param  __OVER_SAMP_MODE__ over samp mode to judge
  * @retval 0 isn't ADC over samp mode set
  * @retval 1 is ADC over samp mode set
  */
#define IS_ADC_OVERSAMPMODE_SET(__OVER_SAMP_MODE__)                   \
    (   ((__OVER_SAMP_MODE__) == ADC_OVS_CONTINUED_MODE)              \
        || ((__OVER_SAMP_MODE__) == ADC_OVS_RESUMED_MODE)             \
    )

/**
  * @brief  Judge is ADC trig over samp or not
  * @param  __TRIG_OVER_SAMP__ trig over samp to judge
  * @retval 0 isn't ADC trig over samp
  * @retval 1 is ADC trig over samp
  */
#define IS_ADC_TRIGOVERSAMP(__TRIG_OVER_SAMP__)                       \
    (   ((__TRIG_OVER_SAMP__) == ADC_OVS_TRIG_CONT)                   \
        || ((__TRIG_OVER_SAMP__) == ADC_OVS_TRIG_DISCONT)             \
    )

/**
  * @brief  Judge is ADC over samp shift or not
  * @param  __OVER_SAMP_SHIFT__ over samp shift to judge
  * @retval 0 isn't ADC over samp shift
  * @retval 1 is ADC over samp shift
  */
#define IS_ADC_OVERSAMPSHIFT(__OVER_SAMP_SHIFT__)                     \
    (   ((__OVER_SAMP_SHIFT__) == ADC_OVSS_SHIFT_NONE)                \
        || ((__OVER_SAMP_SHIFT__) == ADC_OVSS_SHIFT_RIGHT_1)          \
        || ((__OVER_SAMP_SHIFT__) == ADC_OVSS_SHIFT_RIGHT_2)          \
        || ((__OVER_SAMP_SHIFT__) == ADC_OVSS_SHIFT_RIGHT_3)          \
        || ((__OVER_SAMP_SHIFT__) == ADC_OVSS_SHIFT_RIGHT_4)          \
        || ((__OVER_SAMP_SHIFT__) == ADC_OVSS_SHIFT_RIGHT_5)          \
        || ((__OVER_SAMP_SHIFT__) == ADC_OVSS_SHIFT_RIGHT_6)          \
        || ((__OVER_SAMP_SHIFT__) == ADC_OVSS_SHIFT_RIGHT_7)          \
        || ((__OVER_SAMP_SHIFT__) == ADC_OVSS_SHIFT_RIGHT_8)          \
    )

/**
  * @brief  Judge is ADC over samp ratio or not
  * @param  __OVER_SAMP_RATIO__ over samp ratio to judge
  * @retval 0 isn't ADC over samp ratio
  * @retval 1 is ADC over samp ratio
  */
#define IS_ADC_OVERSAMPRATIO(__OVER_SAMP_RATIO__)                     \
    (   ((__OVER_SAMP_RATIO__) == ADC_OVSR_RATIO_2)                   \
        || ((__OVER_SAMP_RATIO__) == ADC_OVSR_RATIO_4)                \
        || ((__OVER_SAMP_RATIO__) == ADC_OVSR_RATIO_8)                \
        || ((__OVER_SAMP_RATIO__) == ADC_OVSR_RATIO_16)               \
        || ((__OVER_SAMP_RATIO__) == ADC_OVSR_RATIO_32)               \
        || ((__OVER_SAMP_RATIO__) == ADC_OVSR_RATIO_64)               \
        || ((__OVER_SAMP_RATIO__) == ADC_OVSR_RATIO_128)              \
        || ((__OVER_SAMP_RATIO__) == ADC_OVSR_RATIO_256)              \
    )

/**
  * @brief  Judge is ADC anolog set or not
  * @param  __ANOLOG_SET__ anolog set to judge
  * @retval 0 isn't ADC anolog set
  * @retval 1 is ADC anolog set
  */
#define IS_ADC_ANOLOGSET(__ANOLOG_SET__)                              \
    (   ((__ANOLOG_SET__) == ADC_ANOLOG_CTL_DEFAULT)                  \
        || ((__ANOLOG_SET__) == ADC_ANOLOG_CTL_A_SH)                  \
        || ((__ANOLOG_SET__) == ADC_ANOLOG_CTL_A_ADC)                 \
        || ((__ANOLOG_SET__) == ADC_ANOLOG_CTL_B_SH)                  \
        || ((__ANOLOG_SET__) == ADC_ANOLOG_CTL_B_ADC)                 \
    )

/**
  * @brief  Judge is ADC channel or not
  * @param  __ADC_CHANNEL__ ADC channel to judge
  * @retval 0 isn't ADC channel
  * @retval 1 is ADC channel
  */
#define IS_ADC_CHANNEL(__ADC_CHANNEL__)                               \
    (   ((__ADC_CHANNEL__) == ADC_CHANNEL_0)                          \
        || ((__ADC_CHANNEL__) == ADC_CHANNEL_1)                       \
        || ((__ADC_CHANNEL__) == ADC_CHANNEL_2)                       \
        || ((__ADC_CHANNEL__) == ADC_CHANNEL_3)                       \
        || ((__ADC_CHANNEL__) == ADC_CHANNEL_4)                       \
        || ((__ADC_CHANNEL__) == ADC_CHANNEL_5)                       \
        || ((__ADC_CHANNEL__) == ADC_CHANNEL_6)                       \
        || ((__ADC_CHANNEL__) == ADC_CHANNEL_7)                       \
        || ((__ADC_CHANNEL__) == ADC_CHANNEL_8)                       \
        || ((__ADC_CHANNEL__) == ADC_CHANNEL_9)                       \
        || ((__ADC_CHANNEL__) == ADC_CHANNEL_10)                      \
        || ((__ADC_CHANNEL__) == ADC_CHANNEL_TEMPSENSOR)              \
    )


/**
  * @brief  Judge is ADC reg trig source or not
  * @param  __REG_TRIG_SOURCE__ reg trig source to judge
  * @retval 0 isn't ADC reg trig source
  * @retval 1 is ADC reg trig source
  */
#define IS_ADC_REG_TRIG_SOURCE( __REG_TRIG_SOURCE__)                            \
    (   ((__REG_TRIG_SOURCE__) == ADC_REG_TRIG_SOFTWARE)                        \
        || (((__REG_TRIG_SOURCE__) & (ADC_LR_EXTSEL_Msk | ADC_LR_EXTEN_Msk)) != 0x00U)  \
    )

/**
  * @brief  Judge is ADC reg continuous mode or not
  * @param  __REG_CONTINUOUS_MODE__ reg continuous mode to judge
  * @retval 0 isn't ADC reg continuous mode
  * @retval 1 is ADC reg continuous mode
  */
#define IS_ADC_REG_CONTINUOUS_MODE(__REG_CONTINUOUS_MODE__)                     \
    (   ((__REG_CONTINUOUS_MODE__) == ADC_REG_CONV_SINGLE)                      \
        || ((__REG_CONTINUOUS_MODE__) == ADC_REG_CONV_CONTINUOUS)               \
    )

/**
  * @brief  Judge is ADC reg seq discont or not
  * @param  __REG_DISCONT_MODE__ reg seq discont to judge
  * @retval 0 isn't ADC reg seq discont
  * @retval 1 is ADC reg seq discont
  */
#define IS_ADC_REG_SEQ_DISCONT(__REG_DISCONT_MODE__)                            \
    (   ((__REG_DISCONT_MODE__) == ADC_REG_SEQ_DISCON_DISABLE)                  \
        || ((__REG_DISCONT_MODE__) == ADC_REG_SEQ_DISNUM_1RANK)                 \
        || ((__REG_DISCONT_MODE__) == ADC_REG_SEQ_DISNUM_2RANKS)                \
        || ((__REG_DISCONT_MODE__) == ADC_REG_SEQ_DISNUM_3RANKS)                \
        || ((__REG_DISCONT_MODE__) == ADC_REG_SEQ_DISNUM_4RANKS)                \
        || ((__REG_DISCONT_MODE__) == ADC_REG_SEQ_DISNUM_5RANKS)                \
        || ((__REG_DISCONT_MODE__) == ADC_REG_SEQ_DISNUM_6RANKS)                \
        || ((__REG_DISCONT_MODE__) == ADC_REG_SEQ_DISNUM_7RANKS)                \
        || ((__REG_DISCONT_MODE__) == ADC_REG_SEQ_DISNUM_8RANKS)                \
    )

/**
  * @brief  Judge is ADC reg differ sel or not
  * @param  __DIFSEL_MODE__ differ sel mode to judge
  * @retval 0 isn't ADC reg differ sel
  * @retval 1 is ADC reg differ sel
  */
#define IS_ADC_REG_DIFFERSEL(__DIFSEL_MODE__)                                   \
    (   ((__DIFSEL_MODE__) == ADC_DIFSEL_DIFFER)                                \
        || ((__DIFSEL_MODE__) == ADC_DIFSEL_SINGLE)                             \
    )

/**
  * @brief  Judge is ADC reg samp time clock or not
  * @param  __REG_SAMPTIMCLK__ reg samp time clock to judge
  * @retval 0 isn't ADC reg samp time clock
  * @retval 1 is ADC reg samp time clock
  */
#define IS_ADC_REG_SAMPTIMCLK(__REG_SAMPTIMCLK__)                               \
    (   ((__REG_SAMPTIMCLK__) == ADC_SAMPLINGTIME_6CYCLES)                      \
        || (((__REG_SAMPTIMCLK__) & ADC_SMPR0_SMP0_Msk) != 0x00U)               \
    )

/**
  * @brief  Judge is ADC LL cal coef sel or not
  * @param  __CALCOEFSEL__ cal coef sel to judge
  * @retval 0 isn't ADC LL cal coef sel
  * @retval 1 is ADC LL cal coef sel
  */
#define IS_LL_ADC_CALCOEFSEL(__CALCOEFSEL__)                                    \
    (   ((__CALCOEFSEL__) == ADC_CALIB_GROUP0)                                 \
        || ((__CALCOEFSEL__) == ADC_CALIB_GROUP1)                              \
        || ((__CALCOEFSEL__) == ADC_CALIB_GROUP2)                              \
        || ((__CALCOEFSEL__) == ADC_CALIB_GROUP3)                              \
    )

/**
  * @brief  Judge is ADC over data behavior or not
  * @param  __REG_OVR_DATA_BEHAVIOR__ over data behavior to judge
  * @retval 0 isn't ADC over data behavior
  * @retval 1 is ADC over data behavior
  */
#define IS_ADC_OVR_DATA_BEHAVIOR(__REG_OVR_DATA_BEHAVIOR__)                     \
    (   ((__REG_OVR_DATA_BEHAVIOR__) == ADC_OVR_DATA_PRESERVED)                 \
        || ((__REG_OVR_DATA_BEHAVIOR__) == ADC_OVR_DATA_OVERWRITTEN)          \
    )

/**
  * @brief  Judge is ADC reg dma transfer or not
  * @param  __REG_DMA_TRANSFER__ reg dma transfer to judge
  * @retval 0 isn't ADC reg dma transfer
  * @retval 1 is ADC reg dma transfer
  */
#define IS_ADC_REG_DMA_TRANSFER(__REG_DMA_TRANSFER__)                           \
    (   ((__REG_DMA_TRANSFER__) == ADC_REG_DMA_TRANSFER_SINGLE)                 \
        || ((__REG_DMA_TRANSFER__) == ADC_REG_DMA_TRANSFER_CIRCLE)              \
        || ((__REG_DMA_TRANSFER__) == ADC_REG_DMA_TRANSFER_DISABLE)             \
    )

/**
  * @brief  Judge is ADC reg awd filter or not
  * @param  __REG_AWD_FILTER__ reg awd filter to judge
  * @retval 0 isn't ADC reg awd filter
  * @retval 1 is ADC reg awd filter
  */
#define IS_ADC_REG_AWD_FILTER(__REG_AWD_FILTER__)                               \
    (   (((__REG_AWD_FILTER__) & ADC_AWD0CR_AWD0FILT_Msk) != 0x00U)             \
        || ((__REG_AWD_FILTER__) == ADC_AWD_FILTERING_NONE)                     \
    )

/**
  * @brief  Judge is ADC reg awd sel or not
  * @param  __REG_AWD_SEL__ reg awd sel to judge
  * @retval 0 isn't ADC reg awd sel
  * @retval 1 is ADC reg awd sel
  */
#define IS_ADC_REG_AWD_SEL(__REG_AWD_SEL__)                                     \
    (   ((__REG_AWD_SEL__) == ADC_AWD2)                                      \
        || ((__REG_AWD_SEL__) == ADC_AWD0)                                   \
        || ((__REG_AWD_SEL__) == ADC_AWD1)                                   \
    )

/**
  * @brief  Judge is ADC awd channel or not
  * @param  __AWD_CHANNEL__ awd channel to judge
  * @retval 0 isn't ADC awd channel
  * @retval 1 is ADC awd channel
  */
#define IS_ADC_AWD_CHANNEL(__AWD_CHANNEL__)                                     \
    (   (((__AWD_CHANNEL__) & ADC_AWD0CR_AWD0CH_Msk) != 0x00U)                  \
        || (((__AWD_CHANNEL__) & (ADC_AWD0CR_AWD0CH_Msk)) == 0x00U)             \
    )

/**
  * @brief  Judge is ADC reg seq length or not
  * @param  __REG_SEQ_LENGTH__ reg seq length to judge
  * @retval 0 isn't ADC reg seq length
  * @retval 1 is ADC reg seq length
  */
#define IS_ADC_REG_SEQ_LENGTH(__REG_SEQ_LENGTH__)                               \
    (   ((__REG_SEQ_LENGTH__) == ADC_REG_SEQ_LENGTH_1)                          \
        || (((__REG_SEQ_LENGTH__) & ADC_LR_LEN_Msk) != 0x00U)                   \
    )

/**
  * @brief  Judge is ADC reg seq pos or not
  * @param  __REG_SEQ_POS_ reg seq pos to judge
  * @retval 0 isn't ADC reg seq pos
  * @retval 1 is ADC reg seq pos
  */
#define IS_ADC_REG_SEQ_POS(__REG_SEQ_POS_)                                      \
    (   ((__REG_SEQ_POS_) == ADC_REG_RANK_1)                                    \
        || ((__REG_SEQ_POS_) == ADC_REG_RANK_2)                                 \
        || ((__REG_SEQ_POS_) == ADC_REG_RANK_3)                                 \
        || ((__REG_SEQ_POS_) == ADC_REG_RANK_4)                                 \
        || ((__REG_SEQ_POS_) == ADC_REG_RANK_5)                                 \
        || ((__REG_SEQ_POS_) == ADC_REG_RANK_6)                                 \
        || ((__REG_SEQ_POS_) == ADC_REG_RANK_7)                                 \
        || ((__REG_SEQ_POS_) == ADC_REG_RANK_8)                                 \
        || ((__REG_SEQ_POS_) == ADC_REG_RANK_9)                                 \
        || ((__REG_SEQ_POS_) == ADC_REG_RANK_10)                                \
        || ((__REG_SEQ_POS_) == ADC_REG_RANK_11)                                \
        || ((__REG_SEQ_POS_) == ADC_REG_RANK_12)                                \
        || ((__REG_SEQ_POS_) == ADC_REG_RANK_13)                                \
        || ((__REG_SEQ_POS_) == ADC_REG_RANK_14)                                \
        || ((__REG_SEQ_POS_) == ADC_REG_RANK_15)                                \
        || ((__REG_SEQ_POS_) == ADC_REG_RANK_16)                                \
    )

/**
  * @brief  Judge is ADC reg seq discont mode or not
  * @param  __REG_SEQ_DISCONT_MODE__ reg seq discont mode to judge
  * @retval 0 isn't ADC reg seq discont mode
  * @retval 1 is ADC reg seq discont mode
  */
#define IS_ADC_REG_SEQ_DISCONT_MODE(__REG_SEQ_DISCONT_MODE__)                   \
    (   ((__REG_SEQ_DISCONT_MODE__) == ADC_REG_SEQ_DISCON_DISABLE)              \
        || ((__REG_SEQ_DISCONT_MODE__) == ADC_REG_SEQ_DISNUM_1RANK)             \
        || ((__REG_SEQ_DISCONT_MODE__) == ADC_REG_SEQ_DISNUM_2RANKS)            \
        || ((__REG_SEQ_DISCONT_MODE__) == ADC_REG_SEQ_DISNUM_3RANKS)            \
        || ((__REG_SEQ_DISCONT_MODE__) == ADC_REG_SEQ_DISNUM_4RANKS)            \
        || ((__REG_SEQ_DISCONT_MODE__) == ADC_REG_SEQ_DISNUM_5RANKS)            \
        || ((__REG_SEQ_DISCONT_MODE__) == ADC_REG_SEQ_DISNUM_6RANKS)            \
        || ((__REG_SEQ_DISCONT_MODE__) == ADC_REG_SEQ_DISNUM_7RANKS)            \
        || ((__REG_SEQ_DISCONT_MODE__) == ADC_REG_SEQ_DISNUM_8RANKS)            \
    )


/**
  * @brief  Judge is ADC inj trig source or not
  * @param  __INJ_TRIG_SOURCE__ inj trig source to judge
  * @retval 0 isn't ADC inj trig source
  * @retval 1 is ADC inj trig source
  */
#define IS_ADC_INJ_TRIG_SOURCE( __INJ_TRIG_SOURCE__)                            \
    (   ((__INJ_TRIG_SOURCE__) == ADC_INJ_TRIG_SOFTWARE)                        \
        || (((__INJ_TRIG_SOURCE__) & (ADC_JLR_JEXTSEL_Msk | ADC_JLR_JEXTEN_Msk)) != 0x00U) \
    )

/**
  * @brief  Judge is ADC inj trig ext edge or not
  * @param  __INJ_TRIG_EXT_EDGE__ inj trig ext edge to judge
  * @retval 0 isn't ADC inj trig ext edge
  * @retval 1 is ADC inj trig ext edge
  */
#define IS_ADC_INJ_TRIG_EXT_EDGE(__INJ_TRIG_EXT_EDGE__)                         \
    (   ((__INJ_TRIG_EXT_EDGE__) == ADC_INJ_TRIG_EXT_RISING)                    \
        || ((__INJ_TRIG_EXT_EDGE__) == ADC_INJ_TRIG_EXT_FALLING)                \
        || ((__INJ_TRIG_EXT_EDGE__) == ADC_INJ_TRIG_EXT_RISINGFALLING)          \
    )

/**
  * @brief  Judge is ADC inj trig auto or not
  * @param  __INJ_TRIG_AUTO__ inj trig auto to judge
  * @retval 0 isn't ADC inj trig auto
  * @retval 1 is ADC inj trig auto
  */
#define IS_ADC_INJ_TRIG_AUTO(__INJ_TRIG_AUTO__)                                 \
    (   ((__INJ_TRIG_AUTO__) == ADC_INJ_TRIG_INDEPENDENT)                       \
        || ((__INJ_TRIG_AUTO__) == ADC_INJ_TRIG_FROM_GRP_REGULAR)               \
    )

/**
  * @brief  Judge is ADC inj seq scan length or not
  * @param  __INJ_SEQ_LENGTH__ inj seq scan length to judge
  * @retval 0 isn't ADC inj seq scan length
  * @retval 1 is ADC inj seq scan length
  */
#define IS_ADC_INJ_SEQ_SCAN_LENGTH(__INJ_SEQ_LENGTH__)                          \
    (   ((__INJ_SEQ_LENGTH__) == ADC_INJ_SEQ_LENGTH_1)                          \
        || ((__INJ_SEQ_LENGTH__) == ADC_INJ_SEQ_LENGTH_2)                       \
        || ((__INJ_SEQ_LENGTH__) == ADC_INJ_SEQ_LENGTH_3)                       \
        || ((__INJ_SEQ_LENGTH__) == ADC_INJ_SEQ_LENGTH_4)                       \
    )

/**
  * @brief  Judge is ADC inj jseq pos or not
  * @param  __INJ_SEQ_LENGTH__ inj jseq pos to judge
  * @retval 0 isn't ADC inj jseq pos
  * @retval 1 is ADC inj jseq pos
  */
#define IS_ADC_INJ_JSEQ_POS(__INJ_SEQ_LENGTH__)                                 \
    (   ((__INJ_SEQ_LENGTH__) == ADC_INJ_RANK_1)                                \
        || ((__INJ_SEQ_LENGTH__) == ADC_INJ_RANK_2)                             \
        || ((__INJ_SEQ_LENGTH__) == ADC_INJ_RANK_3)                             \
        || ((__INJ_SEQ_LENGTH__) == ADC_INJ_RANK_4)                             \
    )

/**
  * @brief  Judge is ADC inj seq scan discont mode or not
  * @param  __INJ_SEQ_DISCONT_MODE__ inj seq scan discont mode to judge
  * @retval 0 isn't ADC inj seq scan discont mode
  * @retval 1 is ADC inj seq scan discont mode
  */
#define IS_ADC_INJ_SEQ_SCAN_DISCONT_MODE(__INJ_SEQ_DISCONT_MODE__)              \
    (   ((__INJ_SEQ_DISCONT_MODE__) == ADC_INJ_SEQ_DISCONT_DISABLE)             \
        || ((__INJ_SEQ_DISCONT_MODE__) == ADC_INJ_SEQ_DISCONT_ENABLE)           \
    )


/**
  * @brief  Judge is ADC ECU group sel or not
  * @param  __ECU_GROUP_SEL__ ECU group sel to judge
  * @retval 0 isn't ADC ECU group sel
  * @retval 1 is ADC ECU group sel
  */
#define IS_ADC_ECU_GROUPSEL(__ECU_GROUP_SEL__)                                  \
    (   ((__ECU_GROUP_SEL__) == ADC_CALIB_GROUP0)                              \
        || ((__ECU_GROUP_SEL__) == ADC_CALIB_GROUP1)                           \
        || ((__ECU_GROUP_SEL__) == ADC_CALIB_GROUP2)                           \
        || ((__ECU_GROUP_SEL__) == ADC_CALIB_GROUP3)                           \
    )

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


#endif /* _TAE32F53XX_LL_ADC_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

