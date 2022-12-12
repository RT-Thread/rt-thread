/**
  ******************************************************************************
  * @file               ft32f0xx_adc.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for the ADC firmware
  *                     library
  * @version            V1.0.0
  * @data                   2021-07-01
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F0XX_ADC_H
#define __FT32F0XX_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f0xx.h"

/** @addtogroup ADC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  ADC Init structure definition
  */

typedef struct
{
  uint32_t ADC_Resolution;                  /*!< Selects the resolution of the conversion.
                                                 This parameter can be a value of @ref ADC_Resolution */

  FunctionalState ADC_ContinuousConvMode;   /*!< Specifies whether the conversion is performed in
                                                 Continuous or Single mode.
                                                 This parameter can be set to ENABLE or DISABLE. */

  uint32_t ADC_ExternalTrigConvEdge;        /*!< Selects the external trigger Edge and enables the
                                                 trigger of a regular group. This parameter can be a value
                                                 of @ref ADC_external_trigger_edge_conversion */

  uint32_t ADC_ExternalTrigConv;            /*!< Defines the external trigger used to start the analog
                                                 to digital conversion of regular channels. This parameter
                                                 can be a value of @ref ADC_external_trigger_sources_for_channels_conversion */

  uint32_t ADC_DataAlign;                   /*!< Specifies whether the ADC data alignment is left or right.
                                                 This parameter can be a value of @ref ADC_data_align */

  uint32_t  ADC_ScanDirection;              /*!< Specifies in which direction the channels will be scanned
                                                 in the sequence.
                                                 This parameter can be a value of @ref ADC_Scan_Direction */
}ADC_InitTypeDef;


/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants
  * @{
  */
#define IS_ADC_ALL_PERIPH(PERIPH)                  ((PERIPH) == ADC1)

/** @defgroup ADC_JitterOff
  * @{
  */
/* These defines are obsolete and maintained for legacy purpose only. They are replaced  by the ADC_ClockMode */
#define ADC_JitterOff_PCLKDiv2                    ADC_CFGR2_JITOFFDIV2
#define ADC_JitterOff_PCLKDiv4                    ADC_CFGR2_JITOFFDIV4

#define IS_ADC_JITTEROFF(JITTEROFF) (((JITTEROFF) & 0x3FFFFFFF) == (uint32_t)RESET)

/**
  * @}
  */

/** @defgroup ADC_ClockMode
  * @{
  */
#define ADC_ClockMode_AsynClk                  ((uint32_t)0x00000000)   /*!< ADC Asynchronous clock mode */
#define ADC_ClockMode_SynClkDiv2               ADC_CFGR2_CKMODE_0   /*!<  Synchronous clock mode divided by 2 */
#define ADC_ClockMode_SynClkDiv4               ADC_CFGR2_CKMODE_1   /*!<  Synchronous clock mode divided by 4 */
#define IS_ADC_CLOCKMODE(CLOCK) (((CLOCK) == ADC_ClockMode_AsynClk) ||\
                                        ((CLOCK) == ADC_ClockMode_SynClkDiv2) ||\
                                        ((CLOCK) == ADC_ClockMode_SynClkDiv4))

/**
  * @}
  */

/** @defgroup ADC_Resolution
  * @{
  */
#define ADC_Resolution_12b                         ((uint32_t)0x00000000)
#define ADC_Resolution_10b                         ADC_CFGR1_RES_0
#define ADC_Resolution_8b                          ADC_CFGR1_RES_1
#define ADC_Resolution_6b                          ADC_CFGR1_RES

#define IS_ADC_RESOLUTION(RESOLUTION) (((RESOLUTION) == ADC_Resolution_12b) || \
                                       ((RESOLUTION) == ADC_Resolution_10b) || \
                                       ((RESOLUTION) == ADC_Resolution_8b) || \
                                       ((RESOLUTION) == ADC_Resolution_6b))

/**
  * @}
  */

/** @defgroup ADC_external_trigger_edge_conversion
  * @{
  */
#define ADC_ExternalTrigConvEdge_None              ((uint32_t)0x00000000)
#define ADC_ExternalTrigConvEdge_Rising            ADC_CFGR1_EXTEN_0
#define ADC_ExternalTrigConvEdge_Falling           ADC_CFGR1_EXTEN_1
#define ADC_ExternalTrigConvEdge_RisingFalling     ADC_CFGR1_EXTEN

#define IS_ADC_EXT_TRIG_EDGE(EDGE) (((EDGE) == ADC_ExternalTrigConvEdge_None) || \
                                    ((EDGE) == ADC_ExternalTrigConvEdge_Rising) || \
                                    ((EDGE) == ADC_ExternalTrigConvEdge_Falling) || \
                                    ((EDGE) == ADC_ExternalTrigConvEdge_RisingFalling))
/**
  * @}
  */

/** @defgroup ADC_external_trigger_sources_for_channels_conversion
  * @{
  */

/* TIM1 */
#define ADC_ExternalTrigConv_T1_TRGO               ((uint32_t)0x00000000)
#define ADC_ExternalTrigConv_T1_CC4                ADC_CFGR1_EXTSEL_0

/* TIM2 */
#define ADC_ExternalTrigConv_T2_TRGO               ADC_CFGR1_EXTSEL_1

/* TIM3 */
#define ADC_ExternalTrigConv_T3_TRGO               ((uint32_t)(ADC_CFGR1_EXTSEL_0 | ADC_CFGR1_EXTSEL_1))

/* TIM15 */
#define ADC_ExternalTrigConv_T15_TRGO              ADC_CFGR1_EXTSEL_2

#define IS_ADC_EXTERNAL_TRIG_CONV(CONV) (((CONV) == ADC_ExternalTrigConv_T1_TRGO) || \
                                         ((CONV) == ADC_ExternalTrigConv_T1_CC4)   || \
                                         ((CONV) == ADC_ExternalTrigConv_T2_TRGO)  || \
                                         ((CONV) == ADC_ExternalTrigConv_T3_TRGO)  || \
                                         ((CONV) == ADC_ExternalTrigConv_T15_TRGO))
/**
  * @}
  */

/** @defgroup ADC_data_align
  * @{
  */

#define ADC_DataAlign_Right                        ((uint32_t)0x00000000)
#define ADC_DataAlign_Left                         ADC_CFGR1_ALIGN

#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DataAlign_Right) || \
                                  ((ALIGN) == ADC_DataAlign_Left))
/**
  * @}
  */

/** @defgroup ADC_Scan_Direction
  * @{
  */

#define ADC_ScanDirection_Upward                   ((uint32_t)0x00000000)
#define ADC_ScanDirection_Backward                 ADC_CFGR1_SCANDIR

#define IS_ADC_SCAN_DIRECTION(DIRECTION) (((DIRECTION) == ADC_ScanDirection_Upward) || \
                                          ((DIRECTION) == ADC_ScanDirection_Backward))
/**
  * @}
  */

/** @defgroup ADC_DMA_Mode
  * @{
  */

#define ADC_DMAMode_OneShot                        ((uint32_t)0x00000000)
#define ADC_DMAMode_Circular                       ADC_CFGR1_DMACFG

#define IS_ADC_DMA_MODE(MODE) (((MODE) == ADC_DMAMode_OneShot) || \
                               ((MODE) == ADC_DMAMode_Circular))
/**
  * @}
  */

/** @defgroup ADC_analog_watchdog_selection
  * @{
  */

#define ADC_AnalogWatchdog_Channel_0                 ((uint32_t)0x00000000)
#define ADC_AnalogWatchdog_Channel_1                 ((uint32_t)0x04000000)
#define ADC_AnalogWatchdog_Channel_2                 ((uint32_t)0x08000000)
#define ADC_AnalogWatchdog_Channel_3                 ((uint32_t)0x0C000000)
#define ADC_AnalogWatchdog_Channel_4                 ((uint32_t)0x10000000)
#define ADC_AnalogWatchdog_Channel_5                 ((uint32_t)0x14000000)
#define ADC_AnalogWatchdog_Channel_6                 ((uint32_t)0x18000000)
#define ADC_AnalogWatchdog_Channel_7                 ((uint32_t)0x1C000000)
#define ADC_AnalogWatchdog_Channel_8                 ((uint32_t)0x20000000)
#define ADC_AnalogWatchdog_Channel_9                 ((uint32_t)0x24000000)
#define ADC_AnalogWatchdog_Channel_10                ((uint32_t)0x28000000)
#define ADC_AnalogWatchdog_Channel_11                ((uint32_t)0x2C000000)
#define ADC_AnalogWatchdog_Channel_12                ((uint32_t)0x30000000)
#define ADC_AnalogWatchdog_Channel_13                ((uint32_t)0x34000000)
#define ADC_AnalogWatchdog_Channel_14                ((uint32_t)0x38000000)
#define ADC_AnalogWatchdog_Channel_15                ((uint32_t)0x3C000000)
#define ADC_AnalogWatchdog_Channel_16                ((uint32_t)0x40000000)
#define ADC_AnalogWatchdog_Channel_17                ((uint32_t)0x44000000)
#define ADC_AnalogWatchdog_Channel_18                ((uint32_t)0x48000000)


#define IS_ADC_ANALOG_WATCHDOG_CHANNEL(CHANNEL) (((CHANNEL) == ADC_AnalogWatchdog_Channel_0)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_1)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_2)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_3)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_4)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_5)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_6)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_7)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_8)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_9)  || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_10) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_11) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_12) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_13) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_14) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_15) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_16) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_17) || \
                                                 ((CHANNEL) == ADC_AnalogWatchdog_Channel_18))
/**
  * @}
  */

/** @defgroup ADC_sampling_times
  * @{
  */

#define ADC_SampleTime_1_5Cycles                     ((uint32_t)0x00000000)
#define ADC_SampleTime_7_5Cycles                     ((uint32_t)0x00000001)
#define ADC_SampleTime_13_5Cycles                    ((uint32_t)0x00000002)
#define ADC_SampleTime_28_5Cycles                    ((uint32_t)0x00000003)
#define ADC_SampleTime_41_5Cycles                    ((uint32_t)0x00000004)
#define ADC_SampleTime_55_5Cycles                    ((uint32_t)0x00000005)
#define ADC_SampleTime_71_5Cycles                    ((uint32_t)0x00000006)
#define ADC_SampleTime_239_5Cycles                   ((uint32_t)0x00000007)

#define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == ADC_SampleTime_1_5Cycles)   || \
                                  ((TIME) == ADC_SampleTime_7_5Cycles)   || \
                                  ((TIME) == ADC_SampleTime_13_5Cycles)  || \
                                  ((TIME) == ADC_SampleTime_28_5Cycles)  || \
                                  ((TIME) == ADC_SampleTime_41_5Cycles)  || \
                                  ((TIME) == ADC_SampleTime_55_5Cycles)  || \
                                  ((TIME) == ADC_SampleTime_71_5Cycles)  || \
                                  ((TIME) == ADC_SampleTime_239_5Cycles))
/**
  * @}
  */

/** @defgroup ADC_thresholds
  * @{
  */

#define IS_ADC_THRESHOLD(THRESHOLD) ((THRESHOLD) <= 0xFFF)

/**
  * @}
  */

/** @defgroup ADC_channels
  * @{
  */

#define ADC_Channel_0                              ADC_CHSELR_CHSEL0
#define ADC_Channel_1                              ADC_CHSELR_CHSEL1
#define ADC_Channel_2                              ADC_CHSELR_CHSEL2
#define ADC_Channel_3                              ADC_CHSELR_CHSEL3
#define ADC_Channel_4                              ADC_CHSELR_CHSEL4
#define ADC_Channel_5                              ADC_CHSELR_CHSEL5
#define ADC_Channel_6                              ADC_CHSELR_CHSEL6
#define ADC_Channel_7                              ADC_CHSELR_CHSEL7
#define ADC_Channel_8                              ADC_CHSELR_CHSEL8
#define ADC_Channel_9                              ADC_CHSELR_CHSEL9
#define ADC_Channel_10                             ADC_CHSELR_CHSEL10
#define ADC_Channel_11                             ADC_CHSELR_CHSEL11
#define ADC_Channel_12                             ADC_CHSELR_CHSEL12
#define ADC_Channel_13                             ADC_CHSELR_CHSEL13
#define ADC_Channel_14                             ADC_CHSELR_CHSEL14
#define ADC_Channel_15                             ADC_CHSELR_CHSEL15
#define ADC_Channel_16                             ADC_CHSELR_CHSEL16
#define ADC_Channel_17                             ADC_CHSELR_CHSEL17
#define ADC_Channel_18                             ADC_CHSELR_CHSEL18
#define ADC_Channel_19                             ADC_CHSELR_CHSEL19
#define ADC_Channel_20                             ADC_CHSELR_CHSEL20
#define ADC_Channel_21                             ADC_CHSELR_CHSEL21

#define ADC_Channel_TempSensor                     ((uint32_t)ADC_Channel_16)
#define ADC_Channel_Vrefint                        ((uint32_t)ADC_Channel_17)
#if defined (FT32F072xB)
    #define ADC_Channel_OP1                            ((uint32_t)ADC_Channel_18)
    #define ADC_Channel_OP2                            ((uint32_t)ADC_Channel_19)
    #define ADC_Channel_IOSH1                          ((uint32_t)ADC_Channel_20)
    #define ADC_Channel_IOSH2                          ((uint32_t)ADC_Channel_21)

    #define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) != (uint32_t)RESET) && (((CHANNEL) & 0xFFC00000) == (uint32_t)RESET))

#else
    #define ADC_Channel_IOSH                          ((uint32_t)ADC_Channel_18)
    #define ADC_Channel_OP                            ((uint32_t)ADC_Channel_19)

    #define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) != (uint32_t)RESET) && (((CHANNEL) & 0xFFF00000) == (uint32_t)RESET))

#endif



#if defined (FT32F072xB)
    /**
      * @}ADC_IOSH1_SMPSEL
      */
    #define ADC_IOSH1_SMPSEL_PB1                        ((uint32_t)0x00000000)
    #define ADC_IOSH1_SMPSEL_OP1OUT                     ((uint32_t)0x00000400)

    #define ADC_IOSH2_SMPSEL_PB0                        ((uint32_t)0x00000000)
    #define ADC_IOSH2_SMPSEL_OP2OUT                     ((uint32_t)0x00004000)

    #define IS_ADC_SMPSEL(SEL)                      (   ((SEL) == ADC_IOSH2_SMPSEL_PB1) || \
                                                        ((SEL) == ADC_IOSH2_SMPSEL_OP1OUT) || \
                                                        ((SEL) == ADC_IOSH1_SMPSEL_OP2OUT) )
    /**
      * @}IS_ADC_SMPEN
      */
    #define ADC_IOSH1_SMPEN                  ((uint32_t)0x00000200)
    #define ADC_IOSH2_SMPEN                  ((uint32_t)0x00002000)

    #define IS_ADC_SMPEN(SMPEN)                     (   ((SMPEN) == ADC_IOSH1_SMPEN) || \
                                                        ((SMPEN) == ADC_IOSH2_SMPEN) )
    /**
      * @}IS_ADC_SMPMOD
      */
    #define IS_ADC_SMPMOD(SMPMOD)           (   ((SMPMOD) == ADC_CR2_IOSH1_SMPMOD) || \
                                                ((SMPMOD) == ADC_CR2_IOSH2_SMPMOD) )

    #define ADC_SMP_SOFTWARE_MODE           ((uint32_t)0x00000000)
    #define ADC_SMP_HARDWARE_MODE           ((uint32_t)0x00000001)

    #define IS_ADC_MODE(MODE)               (   ((MODE) == ADC_SMP_SOFTWARE_MODE) || \
                                                ((MODE) == ADC_SMP_HARDWARE_MODE) )

    /**
      * @}IS_ADC_AMPEN
      */
    #define ADC_IOSH1_AMPEN                  ((uint32_t)0x00000100)
    #define ADC_IOSH2_AMPEN                  ((uint32_t)0x00001000)

    #define IS_ADC_AMPEN(AMPEN)                     (   ((AMPEN) == ADC_IOSH1_AMPEN) || \
                                                        ((AMPEN) == ADC_IOSH2_AMPEN) )
    /**
      * @}IS_ADC_EXTDLY
      */
    #define IS_ADC_EXTDLY(EXTDLY)               (  ((EXTDLY) >=0 ) && ((EXTDLY) <= 0x000003FF))

    /**
      * @}IS_ADC_RTEN
      */
    #define IS_ADC_RTEN(RTEN)               (   ((RTEN) == ADC_RTENR_RTEN) || \
                                                ((RTEN) == ADC_RTENR_RTEN_0) || \
                                                ((RTEN) == ADC_RTENR_RTEN_1) || \
                                                ((RTEN) == ADC_RTENR_RTEN_2) || \
                                                ((RTEN) == ADC_RTENR_RTEN_3) || \
                                                ((RTEN) == ADC_RTENR_RTEN_4) || \
                                                ((RTEN) == ADC_RTENR_RTEN_5) || \
                                                ((RTEN) == ADC_RTENR_RTEN_6) || \
                                                ((RTEN) == ADC_RTENR_RTEN_7) || \
                                                ((RTEN) == ADC_RTENR_RTEN_8) || \
                                                ((RTEN) == ADC_RTENR_RTEN_9) || \
                                                ((RTEN) == ADC_RTENR_RTEN_10) || \
                                                ((RTEN) == ADC_RTENR_RTEN_11) || \
                                                ((RTEN) == ADC_RTENR_RTEN_12) || \
                                                ((RTEN) == ADC_RTENR_RTEN_13) || \
                                                ((RTEN) == ADC_RTENR_RTEN_14) || \
                                                ((RTEN) == ADC_RTENR_RTEN_15) || \
                                                ((RTEN) == ADC_RTENR_RTEN_16) || \
                                                ((RTEN) == ADC_RTENR_RTEN_17) || \
                                                ((RTEN) == ADC_RTENR_RTEN_18)   )

    /**
      * @}IS_ADC_FTEN
      */
    #define IS_ADC_FTEN(FTEN)               (   ((FTEN) == ADC_FTENR_FTEN) || \
                                                ((FTEN) == ADC_FTENR_FTEN_0) || \
                                                ((FTEN) == ADC_FTENR_FTEN_1) || \
                                                ((FTEN) == ADC_FTENR_FTEN_2) || \
                                                ((FTEN) == ADC_FTENR_FTEN_3) || \
                                                ((FTEN) == ADC_FTENR_FTEN_4) || \
                                                ((FTEN) == ADC_FTENR_FTEN_5) || \
                                                ((FTEN) == ADC_FTENR_FTEN_6) || \
                                                ((FTEN) == ADC_FTENR_FTEN_7) || \
                                                ((FTEN) == ADC_FTENR_FTEN_8) || \
                                                ((FTEN) == ADC_FTENR_FTEN_9) || \
                                                ((FTEN) == ADC_FTENR_FTEN_10) || \
                                                ((FTEN) == ADC_FTENR_FTEN_11) || \
                                                ((FTEN) == ADC_FTENR_FTEN_12) || \
                                                ((FTEN) == ADC_FTENR_FTEN_13) || \
                                                ((FTEN) == ADC_FTENR_FTEN_14) || \
                                                ((FTEN) == ADC_FTENR_FTEN_15) || \
                                                ((FTEN) == ADC_FTENR_FTEN_16) || \
                                                ((FTEN) == ADC_FTENR_FTEN_17) || \
                                                ((FTEN) == ADC_FTENR_FTEN_18))

#else
    /**
      * @}IS_ADC_AMPEN
      */
    #define ADC_IOSH1_AMPEN                  ((uint32_t)0x00000100)
    #define ADC_IOSH_AMPEN                  ADC_IOSH1_AMPEN

    #define IS_ADC_AMPEN(AMPEN)                     (   ((AMPEN) == ADC_IOSH1_AMPEN))

    /**
      * @}IS_ADC_SMPEN
      */
    #define ADC_IOSH1_SMPEN                  ((uint32_t)0x00000200)
    #define ADC_IOSH_SMPEN                  ADC_IOSH1_SMPEN

    #define IS_ADC_SMPEN(SMPEN)                     (   ((SMPEN) == ADC_IOSH1_SMPEN) )

#endif


/**
  * @}
  */

/** @defgroup ADC_interrupts_definition
  * @{
  */

#define ADC_IT_ADRDY                               ADC_IER_ADRDYIE
#define ADC_IT_EOSMP                               ADC_IER_EOSMPIE
#define ADC_IT_EOC                                 ADC_IER_EOCIE
#define ADC_IT_EOSEQ                               ADC_IER_EOSEQIE
#define ADC_IT_OVR                                 ADC_IER_OVRIE
#define ADC_IT_AWD                                 ADC_IER_AWDIE

#define IS_ADC_CONFIG_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFFFF60) == (uint32_t)RESET))

#define IS_ADC_GET_IT(IT) (((IT) == ADC_IT_ADRDY) || ((IT) == ADC_IT_EOSMP) || \
                           ((IT) == ADC_IT_EOC)   || ((IT) == ADC_IT_EOSEQ) || \
                           ((IT) == ADC_IT_OVR)   || ((IT) == ADC_IT_AWD))

#define IS_ADC_CLEAR_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFFFF60) == (uint32_t)RESET))

/**
  * @}
  */

/** @defgroup ADC_flags_definition
  * @{
  */

#define ADC_FLAG_ADRDY                             ADC_ISR_ADRDY
#define ADC_FLAG_EOSMP                             ADC_ISR_EOSMP
#define ADC_FLAG_EOC                               ADC_ISR_EOC
#define ADC_FLAG_EOSEQ                             ADC_ISR_EOSEQ
#define ADC_FLAG_OVR                               ADC_ISR_OVR
#define ADC_FLAG_AWD                               ADC_ISR_AWD

#define ADC_FLAG_ADEN                              ((uint32_t)0x01000001)
#define ADC_FLAG_ADDIS                             ((uint32_t)0x01000002)
#define ADC_FLAG_ADSTART                           ((uint32_t)0x01000004)
#define ADC_FLAG_ADSTP                             ((uint32_t)0x01000010)
#define ADC_FLAG_ADCAL                             ((uint32_t)0x81000000)

#define IS_ADC_CLEAR_FLAG(FLAG) (((FLAG) != (uint32_t)RESET) && (((FLAG) & 0xFFFFFF60) == (uint32_t)RESET))

#define IS_ADC_GET_FLAG(FLAG) (((FLAG) == ADC_FLAG_ADRDY)   || ((FLAG) == ADC_FLAG_EOSMP) || \
                               ((FLAG) == ADC_FLAG_EOC)     || ((FLAG) == ADC_FLAG_EOSEQ) || \
                               ((FLAG) == ADC_FLAG_AWD)     || ((FLAG) == ADC_FLAG_OVR)   || \
                               ((FLAG) == ADC_FLAG_ADEN)    || ((FLAG) == ADC_FLAG_ADDIS) || \
                               ((FLAG) == ADC_FLAG_ADSTART) || ((FLAG) == ADC_FLAG_ADSTP) || \
                               ((FLAG) == ADC_FLAG_ADCAL))





#define ADC_Vrefsel_0_625V                                  ((uint32_t)0x00000002)
#define ADC_Vrefsel_1_5V                                    ((uint32_t)0x00000006)
#define ADC_Vrefsel_2_5V                                    ((uint32_t)0x0000000A)
#define ADC_Vrefsel_VDDA                                    ((uint32_t)(~(uint32_t)0x0000000E))
#define IS_ADC_Vrefsel(Vref)    (   (   (Vref) == ADC_Vrefsel_0_625V)   || \
                                    (   (Vref) == ADC_Vrefsel_1_5V  )   || \
                                    (   (Vref) == ADC_Vrefsel_2_5V  )   || \
                                    (   (Vref) == ADC_Vrefsel_VDDA  )   )

#define ADC_VrefEN                                      ((uint32_t)0x00000002)


/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the ADC configuration to the default reset state *****/
void ADC_DeInit(ADC_TypeDef* ADCx);

/* Initialization and Configuration functions *********************************/
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
void ADC_ClockModeConfig(ADC_TypeDef* ADCx, uint32_t ADC_ClockMode);
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
/* This Function is obsolete and maintained for legacy purpose only.
   ADC_ClockModeConfig() function should be used instead */
void ADC_JitterCmd(ADC_TypeDef* ADCx, uint32_t ADC_JitterOff, FunctionalState NewState);

/* Power saving functions *****************************************************/
void ADC_AutoPowerOffCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_WaitModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);

/* Analog Watchdog configuration functions ************************************/
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold,uint16_t LowThreshold);
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog_Channel);
void ADC_AnalogWatchdogSingleChannelCmd(ADC_TypeDef* ADCx, FunctionalState NewState);

/* Temperature Sensor , Vrefint and Vbat management function ... ******************/
void ADC_TempSensorCmd(FunctionalState NewState);
void ADC_VrefintCmd(FunctionalState NewState);
void ADC_VbatCmd(FunctionalState NewState);
void ADC_VrefDecibCmd(FunctionalState NewState);
void ADC_IoshSmpCmd(uint32_t SmpEn, FunctionalState NewState);
void ADC_IoshAmpCmd(uint32_t AmpEn, FunctionalState NewState);

/* Channels Configuration functions *******************************************/
void ADC_ChannelConfig(ADC_TypeDef* ADCx, uint32_t ADC_Channel, uint32_t ADC_SampleTime);
void ADC_ContinuousModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_OverrunModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
uint32_t ADC_GetCalibrationFactor(ADC_TypeDef* ADCx);
void ADC_StopOfConversion(ADC_TypeDef* ADCx);
void ADC_StartOfConversion(ADC_TypeDef* ADCx);
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx);

#if defined (FT32F072xB)
void ADC_IoshSmpSel(uint32_t Ioshx, uint32_t SmpSel);
void ADC_IoshSmpMod(uint32_t SmpModBit, uint32_t Mode);
void ADC_ExtModeCmd(FunctionalState NewState);
void ADC_TrgdDisSmpCmd(FunctionalState NewState);
void ADC_ExtDlyConfig(uint32_t ExtDly);
void ADC_RtenCmd(uint32_t Rtenx, FunctionalState NewState);
void ADC_FtenCmd(uint32_t Ftenx, FunctionalState NewState);

#endif


/* Regular Channels DMA Configuration functions *******************************/
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_DMARequestModeConfig(ADC_TypeDef* ADCx, uint32_t ADC_DMARequestMode);

/* Interrupts and flags management functions **********************************/
void ADC_ITConfig(ADC_TypeDef* ADCx, uint32_t ADC_IT, FunctionalState NewState);
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint32_t ADC_IT);
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint32_t ADC_IT);
void ADC_VrefselConfig(uint32_t ADC_Vrefsel);
#ifdef __cplusplus
}
#endif

#endif /*__ft32F0XX_ADC_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
