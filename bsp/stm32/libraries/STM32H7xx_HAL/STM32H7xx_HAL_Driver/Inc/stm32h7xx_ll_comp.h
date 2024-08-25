/**
  ******************************************************************************
  * @file    stm32h7xx_ll_comp.h
  * @author  MCD Application Team
  * @brief   Header file of COMP LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32H7xx_LL_COMP_H
#define __STM32H7xx_LL_COMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx.h"

/** @addtogroup STM32H7xx_LL_Driver
  * @{
  */

#if defined (COMP1) || defined (COMP2)

/** @defgroup COMP_LL COMP
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup COMP_LL_Private_Constants COMP Private Constants
  * @{
  */

/* COMP registers bits positions */
#define LL_COMP_OUTPUT_LEVEL_BITOFFSET_POS (30U) /* Value equivalent to POSITION_VAL(COMP_CSR_VALUE) */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup COMP_LL_Private_Macros COMP Private Macros
  * @{
  */
/**
  * @}
  */
/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup COMP_LL_ES_INIT COMP Exported Init structure
  * @{
  */

/**
  * @brief  Structure definition of some features of COMP instance.
  */
typedef struct
{
  uint32_t PowerMode;                   /*!< Set comparator operating mode to adjust power and speed.
                                             This parameter can be a value of @ref COMP_LL_EC_POWERMODE
                                             
                                             This feature can be modified afterwards using unitary function @ref LL_COMP_SetPowerMode(). */

  uint32_t InputPlus;                   /*!< Set comparator input plus (non-inverting input).
                                             This parameter can be a value of @ref COMP_LL_EC_INPUT_PLUS
                                             
                                             This feature can be modified afterwards using unitary function @ref LL_COMP_SetInputPlus(). */

  uint32_t InputMinus;                  /*!< Set comparator input minus (inverting input).
                                             This parameter can be a value of @ref COMP_LL_EC_INPUT_MINUS
                                             
                                             This feature can be modified afterwards using unitary function @ref LL_COMP_SetInputMinus(). */

  uint32_t InputHysteresis;             /*!< Set comparator hysteresis mode of the input minus.
                                             This parameter can be a value of @ref COMP_LL_EC_INPUT_HYSTERESIS
                                             
                                             This feature can be modified afterwards using unitary function @ref LL_COMP_SetInputHysteresis(). */

  uint32_t OutputPolarity;              /*!< Set comparator output polarity.
                                             This parameter can be a value of @ref COMP_LL_EC_OUTPUT_POLARITY
                                             
                                             This feature can be modified afterwards using unitary function @ref LL_COMP_SetOutputPolarity(). */

  uint32_t OutputBlankingSource;        /*!< Set comparator blanking source.
                                             This parameter can be a value of @ref COMP_LL_EC_OUTPUT_BLANKING_SOURCE
                                             
                                             This feature can be modified afterwards using unitary function @ref LL_COMP_SetOutputBlankingSource(). */

} LL_COMP_InitTypeDef;

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup COMP_LL_Exported_Constants COMP Exported Constants
  * @{
  */

/** @defgroup COMP_LL_EC_COMMON_WINDOWMODE Comparator common modes - Window mode
  * @{
  */
#define LL_COMP_WINDOWMODE_DISABLE                 (0x00000000UL)          /*!< Window mode disable: Comparators 1 and 2 are independent */
#define LL_COMP_WINDOWMODE_COMP1_INPUT_PLUS_COMMON (COMP_CFGRx_WINMODE)    /*!< Window mode enable: Comparators instances pair COMP1 and COMP2 have their input plus connected together. The common input is COMP1 input plus (COMP2 input plus is no more accessible). */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_POWERMODE Comparator modes - Power mode
  * @{
  */
#define LL_COMP_POWERMODE_HIGHSPEED     (0x00000000UL)                                /*!< COMP power mode to high speed */
#define LL_COMP_POWERMODE_MEDIUMSPEED   (COMP_CFGRx_PWRMODE_0)                        /*!< COMP power mode to medium speed */
#define LL_COMP_POWERMODE_ULTRALOWPOWER (COMP_CFGRx_PWRMODE_1 | COMP_CFGRx_PWRMODE_0) /*!< COMP power mode to ultra-low power */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_INPUT_PLUS Comparator inputs - Input plus (input non-inverting) selection
  * @{
  */
#define LL_COMP_INPUT_PLUS_IO1          (0x00000000UL)                           /*!< Comparator input plus connected to IO1 (pin PB0 for COMP1, pin PE9 for COMP2) */
#define LL_COMP_INPUT_PLUS_IO2          (COMP_CFGRx_INPSEL)                      /*!< Comparator input plus connected to IO2 (pin PB2 for COMP1, pin PE11 for COMP2) */
#if defined (COMP_CFGRx_INP2SEL)
#define LL_COMP_INPUT_PLUS_DAC2_CH1     (COMP_CFGRx_INP2SEL)                     /*!< Comparator input plus 2 connected to (DAC2_CH1 for COMP1)                      */
#endif
/**
  * @}
  */

/** @defgroup COMP_LL_EC_INPUT_MINUS Comparator inputs - Input minus (input inverting) selection
  * @{
  */
#define LL_COMP_INPUT_MINUS_1_4VREFINT      (                                                                                        COMP_CFGRx_SCALEN | COMP_CFGRx_BRGEN)   /*!< Comparator input minus connected to 1/4 VrefInt  */
#define LL_COMP_INPUT_MINUS_1_2VREFINT      (                                                                  COMP_CFGRx_INMSEL_0 | COMP_CFGRx_SCALEN | COMP_CFGRx_BRGEN)   /*!< Comparator input minus connected to 1/2 VrefInt  */
#define LL_COMP_INPUT_MINUS_3_4VREFINT      (                                            COMP_CFGRx_INMSEL_1                       | COMP_CFGRx_SCALEN | COMP_CFGRx_BRGEN)   /*!< Comparator input minus connected to 3/4 VrefInt  */
#define LL_COMP_INPUT_MINUS_VREFINT         (                                            COMP_CFGRx_INMSEL_1 | COMP_CFGRx_INMSEL_0 | COMP_CFGRx_SCALEN                   )   /*!< Comparator input minus connected to VrefInt */
#define LL_COMP_INPUT_MINUS_DAC1_CH1        (                      COMP_CFGRx_INMSEL_2                                                                                   )   /*!< Comparator input minus connected to DAC1 channel 1 (DAC_OUT1)  */
#define LL_COMP_INPUT_MINUS_DAC1_CH2        (                      COMP_CFGRx_INMSEL_2                       | COMP_CFGRx_INMSEL_0                                       )   /*!< Comparator input minus connected to DAC1 channel 2 (DAC_OUT2)  */
#define LL_COMP_INPUT_MINUS_IO1             (                      COMP_CFGRx_INMSEL_2 | COMP_CFGRx_INMSEL_1                                                             )   /*!< Comparator input minus connected to IO1 (pin PB1 for COMP1, pin PE10 for COMP2) */
#define LL_COMP_INPUT_MINUS_IO2             (                      COMP_CFGRx_INMSEL_2 | COMP_CFGRx_INMSEL_1 | COMP_CFGRx_INMSEL_0                                       )   /*!< Comparator input minus connected to IO2 (pin PC4 for COMP1, pin PE7 for COMP2) */
#if defined (COMP_CFGRx_INMSEL_3)
#define LL_COMP_INPUT_MINUS_TPSENS_DAC2CH1  (COMP_CFGRx_INMSEL_3                                                                                                         )   /*!< Comparator input minus connected to  (temp sensor which is exist in ADC for COMP1, DAC2_CH1 for COMP2) */
#define LL_COMP_INPUT_MINUS_VBAT_VDDAP      (COMP_CFGRx_INMSEL_3                                             | COMP_CFGRx_INMSEL_0                                       )   /*!< Comparator input minus connected to  (VBAT/4 for COMP1, VDDAP for COMP2) */
#endif
/**
  * @}
  */

/** @defgroup COMP_LL_EC_INPUT_HYSTERESIS Comparator input - Hysteresis
  * @{
  */
#define LL_COMP_HYSTERESIS_NONE         (0x00000000UL)                            /*!< No hysteresis */
#define LL_COMP_HYSTERESIS_LOW          (                    COMP_CFGRx_HYST_0)   /*!< Hysteresis level low */
#define LL_COMP_HYSTERESIS_MEDIUM       (COMP_CFGRx_HYST_1                    )   /*!< Hysteresis level medium */
#define LL_COMP_HYSTERESIS_HIGH         (COMP_CFGRx_HYST_1 | COMP_CFGRx_HYST_0)   /*!< Hysteresis level high */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_OUTPUT_POLARITY Comparator output - Output polarity
  * @{
  */
#define LL_COMP_OUTPUTPOL_NONINVERTED   (0x00000000UL)          /*!< COMP output polarity is not inverted: comparator output is high when the plus (non-inverting) input is at a higher voltage than the minus (inverting) input */
#define LL_COMP_OUTPUTPOL_INVERTED      (COMP_CFGRx_POLARITY)   /*!< COMP output polarity is inverted: comparator output is low when the plus (non-inverting) input is at a lower voltage than the minus (inverting) input */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_OUTPUT_BLANKING_SOURCE Comparator output - Blanking source
  * @{
  */
#define LL_COMP_BLANKINGSRC_NONE      (0x00000000UL)                                  /*!<Comparator output without blanking */
#define LL_COMP_BLANKINGSRC_TIM1_OC5  (COMP_CFGRx_BLANKING_0)                         /*!< Comparator output blanking source TIM1 OC5 (common to all COMP instances: COMP1, COMP2) */
#define LL_COMP_BLANKINGSRC_TIM2_OC3  (COMP_CFGRx_BLANKING_1)                         /*!< Comparator output blanking source TIM2 OC3 (common to all COMP instances: COMP1, COMP2) */
#define LL_COMP_BLANKINGSRC_TIM3_OC3  (COMP_CFGRx_BLANKING_0 |COMP_CFGRx_BLANKING_1)  /*!< Comparator output blanking source TIM3 OC3 (common to all COMP instances: COMP1, COMP2) */
#define LL_COMP_BLANKINGSRC_TIM3_OC4  (COMP_CFGRx_BLANKING_2)                         /*!< Comparator output blanking source TIM3 OC4 (common to all COMP instances: COMP1, COMP2) */
#define LL_COMP_BLANKINGSRC_TIM8_OC5  (COMP_CFGRx_BLANKING_2|COMP_CFGRx_BLANKING_0)   /*!< Comparator output blanking source TIM8 OC5 (common to all COMP instances: COMP1, COMP2) */
#define LL_COMP_BLANKINGSRC_TIM15_OC1 (COMP_CFGRx_BLANKING_2|COMP_CFGRx_BLANKING_1)   /*!< Comparator output blanking source TIM15 OC1 (common to all COMP instances: COMP1, COMP2) */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_OUTPUT_LEVEL Comparator output - Output level
  * @{
  */
#define LL_COMP_OUTPUT_LEVEL_LOW        (0x00000000UL)           /*!< Comparator output level low (if the polarity is not inverted, otherwise to be complemented) */
#define LL_COMP_OUTPUT_LEVEL_HIGH       (0x00000001UL)           /*!< Comparator output level high (if the polarity is not inverted, otherwise to be complemented) */
/**
  * @}
  */
/** @defgroup COMP_LL_EC_OUTPUT_BKIN_TIMER Comparator output - Output to BKIN timer
  * @{
  */
#define LL_COMP_AF_PA6          COMP_OR_AFOPA6       /*!< Comparator Alternate Function PA6 source selected to timer BKIN input  */
#define LL_COMP_AF_PA8          COMP_OR_AFOPA8       /*!< Comparator Alternate Function PA8 source selected to timer BKIN input  */
#define LL_COMP_AF_PB12         COMP_OR_AFOPB12      /*!< Comparator Alternate Function PB12 source selected to timer BKIN input */
#define LL_COMP_AF_PE6          COMP_OR_AFOPE6       /*!< Comparator Alternate Function PE6 source selected to timer BKIN input  */
#define LL_COMP_AF_PE15         COMP_OR_AFOPE15      /*!< Comparator Alternate Function PE15 source selected to timer BKIN input */
#define LL_COMP_AF_PG2          COMP_OR_AFOPG2       /*!< Comparator Alternate Function PG2 source selected to timer BKIN input  */
#define LL_COMP_AF_PG3          COMP_OR_AFOPG3       /*!< Comparator Alternate Function PG3 source selected to timer BKIN input  */
#define LL_COMP_AF_PG4          COMP_OR_AFOPG4       /*!< Comparator Alternate Function PG4 source selected to timer BKIN input  */
#define LL_COMP_AF_PI1          COMP_OR_AFOPI1       /*!< Comparator Alternate Function PI1 source selected to timer BKIN input  */
#define LL_COMP_AF_PI4          COMP_OR_AFOPI4       /*!< Comparator Alternate Function PI4 source selected to timer BKIN input  */
#define LL_COMP_AF_PK2          COMP_OR_AFOPK2       /*!< Comparator Alternate Function PK2 source selected to timer BKIN input  */
/**
  * @}
  */

/** @defgroup COMP_LL_EC_HW_DELAYS  Definitions of COMP hardware constraints delays
  * @note   Only COMP IP HW delays are defined in COMP LL driver driver,
  *         not timeout values.
  *         For details on delays values, refer to descriptions in source code
  *         above each literal definition.
  * @{
  */

/* Delay for comparator startup time.                                         */
/* Note: Delay required to reach propagation delay specification.             */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tSTART").                                                       */
/* Unit: us                                                                   */
#define LL_COMP_DELAY_STARTUP_US          ( 80UL)  /*!< Delay for COMP startup time */

/* Delay for comparator voltage scaler stabilization time.                    */
/* Note: Voltage scaler is used when selecting comparator input               */
/*       based on VrefInt: VrefInt or subdivision of VrefInt.                 */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tSTART_SCALER").                                                */
/* Unit: us                                                                   */
#define LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US ( 200UL)  /*!< Delay for COMP voltage scaler stabilization time */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup COMP_LL_Exported_Macros COMP Exported Macros
  * @{
  */
/** @defgroup COMP_LL_EM_WRITE_READ Common write and read registers macro
  * @{
  */

/**
  * @brief  Write a value in COMP register
  * @param  __INSTANCE__ comparator instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_COMP_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in COMP register
  * @param  __INSTANCE__ comparator instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_COMP_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/** @defgroup COMP_LL_EM_HELPER_MACRO COMP helper macro
  * @{
  */

/**
  * @brief  Helper macro to select the COMP common instance
  *         to which is belonging the selected COMP instance.
  * @note   COMP common register instance can be used to
  *         set parameters common to several COMP instances.
  *         Refer to functions having argument "COMPxy_COMMON" as parameter.
  * @param  __COMPx__ COMP instance
  * @retval COMP common instance or value "0" if there is no COMP common instance.
  */
#define __LL_COMP_COMMON_INSTANCE(__COMPx__)                                   \
  (COMP12_COMMON)

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup COMP_LL_Exported_Functions COMP Exported Functions
  * @{
  */

/** @defgroup COMP_LL_EF_Configuration_comparator_common Configuration of COMP hierarchical scope: common to several COMP instances
  * @{
  */

/**
  * @brief  Set window mode of a pair of comparators instances
  *         (2 consecutive COMP instances odd and even COMP<x> and COMP<x+1>).
  * @rmtoll CFGRx    WINMODE        LL_COMP_SetCommonWindowMode
  * @param  COMPxy_COMMON Comparator common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_COMP_COMMON_INSTANCE() )
  * @param  WindowMode This parameter can be one of the following values:
  *         @arg @ref LL_COMP_WINDOWMODE_DISABLE
  *         @arg @ref LL_COMP_WINDOWMODE_COMP1_INPUT_PLUS_COMMON
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetCommonWindowMode(COMP_Common_TypeDef *COMPxy_COMMON, uint32_t WindowMode)
{
  /* Note: On this STM32 series, window mode can be set only                   */
  /*       from COMP instance: COMP2.                                         */
  MODIFY_REG(COMPxy_COMMON->CFGR, COMP_CFGRx_WINMODE, WindowMode);
}

/**
  * @brief  Get window mode of a pair of comparators instances
  *         (2 consecutive COMP instances odd and even COMP<x> and COMP<x+1>).
  * @rmtoll CFGRx    WINMODE        LL_COMP_GetCommonWindowMode
  * @param  COMPxy_COMMON Comparator common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_COMP_COMMON_INSTANCE() )
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_WINDOWMODE_DISABLE
  *         @arg @ref LL_COMP_WINDOWMODE_COMP1_INPUT_PLUS_COMMON
  */
__STATIC_INLINE uint32_t LL_COMP_GetCommonWindowMode(COMP_Common_TypeDef *COMPxy_COMMON)
{
  return (uint32_t)(READ_BIT(COMPxy_COMMON->CFGR, COMP_CFGRx_WINMODE));
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_Configuration_comparator_modes Configuration of comparator modes
  * @{
  */

/**
  * @brief  Set comparator instance operating mode to adjust power and speed.
  * @rmtoll CFGRx    PWRMODE        LL_COMP_SetPowerMode
  * @param  COMPx Comparator instance
  * @param  PowerMode This parameter can be one of the following values:
  *         @arg @ref LL_COMP_POWERMODE_HIGHSPEED
  *         @arg @ref LL_COMP_POWERMODE_MEDIUMSPEED
  *         @arg @ref LL_COMP_POWERMODE_ULTRALOWPOWER
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetPowerMode(COMP_TypeDef *COMPx, uint32_t PowerMode)
{
  MODIFY_REG(COMPx->CFGR, COMP_CFGRx_PWRMODE, PowerMode);
}

/**
  * @brief  Get comparator instance operating mode to adjust power and speed.
  * @rmtoll CFGRx    PWRMODE        LL_COMP_GetPowerMode
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_POWERMODE_HIGHSPEED
  *         @arg @ref LL_COMP_POWERMODE_MEDIUMSPEED
  *         @arg @ref LL_COMP_POWERMODE_ULTRALOWPOWER
  */
__STATIC_INLINE uint32_t LL_COMP_GetPowerMode(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMPx->CFGR, COMP_CFGRx_PWRMODE));
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_Configuration_comparator_inputs Configuration of comparator inputs
  * @{
  */

/**
  * @brief  Set comparator inputs minus (inverting) and plus (non-inverting).
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @note   On this STM32 series, scaler bridge is configurable:
  *         to optimize power consumption, this function enables the
  *         voltage scaler bridge only when required
  *         (when selecting comparator input based on VrefInt: VrefInt or
  *         subdivision of VrefInt).
  *         - For scaler bridge power consumption values, 
  *           refer to device datasheet, parameter "IDDA(SCALER)".
  *         - Voltage scaler requires a delay for voltage stabilization.
  *           Refer to device datasheet, parameter "tSTART_SCALER".
  *         - Scaler bridge is common for all comparator instances,
  *           therefore if at least one of the comparator instance
  *           is requiring the scaler bridge, it remains enabled.
  * @rmtoll CFGRx      INMSEL         LL_COMP_ConfigInputs\n
  *         CFGRx      INPSEL         LL_COMP_ConfigInputs\n
  *         CFGRx      BRGEN          LL_COMP_ConfigInputs\n
  *         CFGRx      SCALEN         LL_COMP_ConfigInputs
  * @param  COMPx Comparator instance
  * @param  InputMinus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_MINUS_1_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_1_2VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_3_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH1
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH2 
  *         @arg @ref LL_COMP_INPUT_MINUS_IO1
  *         @arg @ref LL_COMP_INPUT_MINUS_IO2
  *         @arg @ref LL_COMP_INPUT_MINUS_TPSENS_DAC2CH1
  *         @arg @ref LL_COMP_INPUT_MINUS_VBAT_VDDAP
  * @param  InputPlus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_PLUS_IO1
  *         @arg @ref LL_COMP_INPUT_PLUS_IO2
  *         @arg @ref LL_COMP_INPUT_PLUS_DAC2_CH1
  * @retval None
  */
__STATIC_INLINE void LL_COMP_ConfigInputs(COMP_TypeDef *COMPx, uint32_t InputMinus, uint32_t InputPlus)
{
#if defined (COMP_CFGRx_INP2SEL)
  MODIFY_REG(COMPx->CFGR,
             COMP_CFGRx_INMSEL | COMP_CFGRx_INPSEL | 
             COMP_CFGRx_INP2SEL | 
             COMP_CFGRx_SCALEN | COMP_CFGRx_BRGEN,
             InputMinus | InputPlus);
#else
  MODIFY_REG(COMPx->CFGR,
             COMP_CFGRx_INMSEL | COMP_CFGRx_INPSEL | 
             COMP_CFGRx_SCALEN | COMP_CFGRx_BRGEN,
             InputMinus | InputPlus);
#endif
}

/**
  * @brief  Set comparator input plus (non-inverting).
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll CFGRx    INPSEL         LL_COMP_SetInputPlus
  * @param  COMPx Comparator instance
  * @param  InputPlus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_PLUS_IO1
  *         @arg @ref LL_COMP_INPUT_PLUS_IO2
  *         @arg @ref LL_COMP_INPUT_PLUS_DAC2_CH1
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetInputPlus(COMP_TypeDef *COMPx, uint32_t InputPlus)
{
#if defined (COMP_CFGRx_INP2SEL)
  MODIFY_REG(COMPx->CFGR, COMP_CFGRx_INPSEL | COMP_CFGRx_INP2SEL , InputPlus);
#else
  MODIFY_REG(COMPx->CFGR, COMP_CFGRx_INPSEL , InputPlus);
#endif
}

/**
  * @brief  Get comparator input plus (non-inverting).
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll CFGRx    INPSEL         LL_COMP_GetInputPlus
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_PLUS_IO1
  *         @arg @ref LL_COMP_INPUT_PLUS_IO2
  *         @arg @ref LL_COMP_INPUT_PLUS_DAC2_CH1
  */
__STATIC_INLINE uint32_t LL_COMP_GetInputPlus(COMP_TypeDef *COMPx)
{
#if defined (COMP_CFGRx_INP2SEL)
  return (uint32_t)(READ_BIT(COMPx->CFGR, COMP_CFGRx_INPSEL | COMP_CFGRx_INP2SEL));
#else
  return (uint32_t)(READ_BIT(COMPx->CFGR, COMP_CFGRx_INPSEL));
#endif
}

/**
  * @brief  Set comparator input minus (inverting).
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @note   On this STM32 series, scaler bridge is configurable:
  *         to optimize power consumption, this function enables the
  *         voltage scaler bridge only when required
  *         (when selecting comparator input based on VrefInt: VrefInt or
  *         subdivision of VrefInt).
  *         - For scaler bridge power consumption values, 
  *           refer to device datasheet, parameter "IDDA(SCALER)".
  *         - Voltage scaler requires a delay for voltage stabilization.
  *           Refer to device datasheet, parameter "tSTART_SCALER".
  *         - Scaler bridge is common for all comparator instances,
  *           therefore if at least one of the comparator instance
  *           is requiring the scaler bridge, it remains enabled.
  * @rmtoll CFGRx     INMSEL         LL_COMP_SetInputMinus\n
  *         CFGRx     BRGEN          LL_COMP_SetInputMinus\n
  *         CFGRx     SCALEN         LL_COMP_SetInputMinus
  * @param  COMPx Comparator instance
  * @param  InputMinus This parameter can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_MINUS_1_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_1_2VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_3_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH1
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH2
  *         @arg @ref LL_COMP_INPUT_MINUS_IO1
  *         @arg @ref LL_COMP_INPUT_MINUS_IO2
  *         @arg @ref LL_COMP_INPUT_MINUS_TPSENS_DAC2CH1
  *         @arg @ref LL_COMP_INPUT_MINUS_VBAT_VDDAP
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetInputMinus(COMP_TypeDef *COMPx, uint32_t InputMinus)
{
  MODIFY_REG(COMPx->CFGR, COMP_CFGRx_INMSEL | COMP_CFGRx_SCALEN | COMP_CFGRx_BRGEN, InputMinus);
}

/**
  * @brief  Get comparator input minus (inverting).
  * @note   In case of comparator input selected to be connected to IO:
  *         GPIO pins are specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll CFGRx     INMSEL         LL_COMP_GetInputMinus\n
  *         CFGRx     BRGEN          LL_COMP_GetInputMinus\n
  *         CFGRx     SCALEN         LL_COMP_GetInputMinus
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_INPUT_MINUS_1_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_1_2VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_3_4VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_VREFINT
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH1
  *         @arg @ref LL_COMP_INPUT_MINUS_DAC1_CH2  
  *         @arg @ref LL_COMP_INPUT_MINUS_IO1
  *         @arg @ref LL_COMP_INPUT_MINUS_IO2
  *         @arg @ref LL_COMP_INPUT_MINUS_TPSENS_DAC2CH1
  *         @arg @ref LL_COMP_INPUT_MINUS_VBAT_VDDAP
  */
__STATIC_INLINE uint32_t LL_COMP_GetInputMinus(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMPx->CFGR, COMP_CFGRx_INMSEL | COMP_CFGRx_SCALEN | COMP_CFGRx_BRGEN));
}

/**
  * @brief  Set comparator instance hysteresis mode of the input minus (inverting input).
  * @rmtoll CFGRx    HYST           LL_COMP_SetInputHysteresis
  * @param  COMPx Comparator instance
  * @param  InputHysteresis This parameter can be one of the following values:
  *         @arg @ref LL_COMP_HYSTERESIS_NONE
  *         @arg @ref LL_COMP_HYSTERESIS_LOW
  *         @arg @ref LL_COMP_HYSTERESIS_MEDIUM
  *         @arg @ref LL_COMP_HYSTERESIS_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetInputHysteresis(COMP_TypeDef *COMPx, uint32_t InputHysteresis)
{
  MODIFY_REG(COMPx->CFGR, COMP_CFGRx_HYST, InputHysteresis);
}

/**
  * @brief  Get comparator instance hysteresis mode of the minus (inverting) input.
  * @rmtoll CSR      HYST           LL_COMP_GetInputHysteresis
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_HYSTERESIS_NONE
  *         @arg @ref LL_COMP_HYSTERESIS_LOW
  *         @arg @ref LL_COMP_HYSTERESIS_MEDIUM
  *         @arg @ref LL_COMP_HYSTERESIS_HIGH
  */
__STATIC_INLINE uint32_t LL_COMP_GetInputHysteresis(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMPx->CFGR, COMP_CFGRx_HYST));
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_Configuration_comparator_output Configuration of comparator output
  * @{
  */

/**
  * @brief  Set comparator instance output polarity.
  * @rmtoll CFGRx    POLARITY       LL_COMP_SetOutputPolarity
  * @param  COMPx Comparator instance
  * @param  OutputPolarity This parameter can be one of the following values:
  *         @arg @ref LL_COMP_OUTPUTPOL_NONINVERTED
  *         @arg @ref LL_COMP_OUTPUTPOL_INVERTED
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetOutputPolarity(COMP_TypeDef *COMPx, uint32_t OutputPolarity)
{
  MODIFY_REG(COMPx->CFGR, COMP_CFGRx_POLARITY, OutputPolarity);
}

/**
  * @brief  Get comparator instance output polarity.
  * @rmtoll CFGRx    POLARITY       LL_COMP_GetOutputPolarity
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_OUTPUTPOL_NONINVERTED
  *         @arg @ref LL_COMP_OUTPUTPOL_INVERTED
  */
__STATIC_INLINE uint32_t LL_COMP_GetOutputPolarity(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMPx->CFGR, COMP_CFGRx_POLARITY));
}

/**
  * @brief  Set comparator instance blanking source.
  * @note   Blanking source may be specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @note   Availability of parameters of blanking source from timer
  *         depends on timers availability on the selected device.
  * @rmtoll CFGR     BLANKING       LL_COMP_SetOutputBlankingSource
  * @param  COMPx Comparator instance
  * @param  BlankingSource This parameter can be one of the following values:
  *         @arg @ref LL_COMP_BLANKINGSRC_NONE
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5  
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM2_OC3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC4
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM15_OC1 
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetOutputBlankingSource(COMP_TypeDef *COMPx, uint32_t BlankingSource)
{
  MODIFY_REG(COMPx->CFGR, COMP_CFGRx_BLANKING, BlankingSource);
}

/**
  * @brief  Get comparator instance blanking source.
  * @note   Availability of parameters of blanking source from timer
  *         depends on timers availability on the selected device.
  * @note   Blanking source may be specific to each comparator instance.
  *         Refer to description of parameters or to reference manual.
  * @rmtoll CFGR     BLANKING       LL_COMP_GetOutputBlankingSource
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_BLANKINGSRC_NONE
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM1_OC5 
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM2_OC3 
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC3
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM3_OC4 
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM8_OC5  
  *         @arg @ref LL_COMP_BLANKINGSRC_TIM15_OC1  
  */
__STATIC_INLINE uint32_t LL_COMP_GetOutputBlankingSource(COMP_TypeDef *COMPx)
{
  return (uint32_t)(READ_BIT(COMPx->CFGR, COMP_CFGRx_BLANKING));
}

/** @brief  Set the output alternate function in the Option register
  *         in order to be used with the alternate function
  *         of the timer break input.
  * @rmtoll OR    AFOP       COMP_LL_EC_OUTPUT_BKIN_TIMER
  * @param  COMPx specifies the instance.
  * @param  CompAFx specifies the Alternate Function source selection.
  *          This parameter can be one of the following values:
  *            @arg @ref LL_COMP_AF_PA6
  *            @arg @ref LL_COMP_AF_PA8
  *            @arg @ref LL_COMP_AF_PB12
  *            @arg @ref LL_COMP_AF_PE6
  *            @arg @ref LL_COMP_AF_PE15
  *            @arg @ref LL_COMP_AF_PG2
  *            @arg @ref LL_COMP_AF_PG3
  *            @arg @ref LL_COMP_AF_PG4
  *            @arg @ref LL_COMP_AF_PI1
  *            @arg @ref LL_COMP_AF_PI4
  *            @arg @ref LL_COMP_AF_PK2
  * @retval None
  */
__STATIC_INLINE void LL_COMP_SetOutputAlternateFunction(COMP_TypeDef *COMPx, uint32_t CompAFx)
{
  MODIFY_REG(COMP12->OR, 0x7FFUL, (COMPx == COMP1) ? ((~CompAFx) & 0x7FFUL) : CompAFx);
}

/** @brief  Get the output alternate function from the Option register.
  * @rmtoll OR     AFOP       COMP_LL_EC_OUTPUT_BKIN_TIMER
  * @param  COMPx specifies the Comparator instance.
  * @retval Returned value can be one of the following values:
  *            @arg @ref LL_COMP_AF_PA6
  *            @arg @ref LL_COMP_AF_PA8
  *            @arg @ref LL_COMP_AF_PB12
  *            @arg @ref LL_COMP_AF_PE6
  *            @arg @ref LL_COMP_AF_PE15
  *            @arg @ref LL_COMP_AF_PG2
  *            @arg @ref LL_COMP_AF_PG3
  *            @arg @ref LL_COMP_AF_PG4
  *            @arg @ref LL_COMP_AF_PI1
  *            @arg @ref LL_COMP_AF_PI4
  *            @arg @ref LL_COMP_AF_PK2
  */
__STATIC_INLINE uint32_t LL_COMP_GetOutputAlternateFunction(COMP_TypeDef *COMPx )
{
  return (uint32_t) ((COMPx == COMP1) ? ((~COMP12->OR) & 0x7FFUL) : (COMP12->OR &  0x7FFUL));
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_Operation Operation on comparator instance
  * @{
  */

/**
  * @brief  Enable comparator instance.
  * @note   After enable from off state, comparator requires a delay
  *         to reach reach propagation delay specification.
  *         Refer to device datasheet, parameter "tSTART".
  * @rmtoll CFGR     EN             LL_COMP_Enable
  * @param  COMPx Comparator instance
  * @retval None
  */
__STATIC_INLINE void LL_COMP_Enable(COMP_TypeDef *COMPx)
{
  SET_BIT(COMPx->CFGR, COMP_CFGRx_EN);
}

/**
  * @brief  Disable comparator instance.
  * @rmtoll CFGR     EN             LL_COMP_Disable
  * @param  COMPx Comparator instance
  * @retval None
  */
__STATIC_INLINE void LL_COMP_Disable(COMP_TypeDef *COMPx)
{
  CLEAR_BIT(COMPx->CFGR, COMP_CFGRx_EN);
}

/**
  * @brief  Get comparator enable state
  *         (0: COMP is disabled, 1: COMP is enabled)
  * @rmtoll CFGR     EN             LL_COMP_IsEnabled
  * @param  COMPx Comparator instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_COMP_IsEnabled(COMP_TypeDef *COMPx)
{
  return ((READ_BIT(COMPx->CFGR, COMP_CFGRx_EN) == (COMP_CFGRx_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Lock comparator instance.
  * @note   Once locked, comparator configuration can be accessed in read-only.
  * @note   The only way to unlock the comparator is a device hardware reset.
  * @rmtoll CFGR     LOCK           LL_COMP_Lock
  * @param  COMPx Comparator instance
  * @retval None
  */
__STATIC_INLINE void LL_COMP_Lock(COMP_TypeDef *COMPx)
{
  SET_BIT(COMPx->CFGR, COMP_CFGRx_LOCK);
}

/**
  * @brief  Get comparator lock state
  *         (0: COMP is unlocked, 1: COMP is locked).
  * @note   Once locked, comparator configuration can be accessed in read-only.
  * @note   The only way to unlock the comparator is a device hardware reset.
  * @rmtoll CFGR     LOCK           LL_COMP_IsLocked
  * @param  COMPx Comparator instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_COMP_IsLocked(COMP_TypeDef *COMPx)
{
  return ((READ_BIT(COMPx->CFGR, COMP_CFGRx_LOCK) == (COMP_CFGRx_LOCK)) ? 1UL : 0UL);
}

/**
  * @brief  Read comparator instance output level.
  * @note   The comparator output level depends on the selected polarity
  *         (Refer to function @ref LL_COMP_SetOutputPolarity()).
  *         If the comparator polarity is not inverted:
  *          - Comparator output is low when the input plus
  *            is at a lower voltage than the input minus
  *          - Comparator output is high when the input plus
  *            is at a higher voltage than the input minus
  *         If the comparator polarity is inverted:
  *          - Comparator output is high when the input plus
  *            is at a lower voltage than the input minus
  *          - Comparator output is low when the input plus
  *            is at a higher voltage than the input minus
  * @rmtoll CFGR     VALUE          LL_COMP_ReadOutputLevel
  * @param  COMPx Comparator instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_COMP_OUTPUT_LEVEL_LOW
  *         @arg @ref LL_COMP_OUTPUT_LEVEL_HIGH
  */
__STATIC_INLINE uint32_t LL_COMP_ReadOutputLevel(COMP_TypeDef *COMPx)
{
  if (COMPx == COMP1)
  {
    return (uint32_t)(READ_BIT(COMP12->SR, COMP_SR_C1VAL));
  }
  else
  {
    return (uint32_t)((READ_BIT(COMP12->SR, COMP_SR_C2VAL))>> 1); 
  }
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_FLAG_Management Comparator flag Management
  * @{
  */

/**
  * @brief  Get comparator output trigger flag (latched)
  * @rmtoll SR       C1IF           LL_COMP_IsActiveFlag_OutputTrig
  * @param  COMPx Comparator instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_COMP_IsActiveFlag_OutputTrig(COMP_TypeDef *COMPx)
{
   if (COMPx == COMP1)
  {
    return ((READ_BIT(COMP12->SR, COMP_SR_C1IF) == (COMP_SR_C1IF)) ? 1UL : 0UL);
  }
  else
  {
    return ((READ_BIT(COMP12->SR, COMP_SR_C2IF) == (COMP_SR_C2IF)) ? 1UL : 0UL);
  }
}

/**
  * @brief  Clear comparator comparator output trigger flag (latched)
  * @rmtoll ICFR     CC1IF          LL_COMP_ClearFlag_OutputTrig
  * @param  COMPx Comparator instance
  * @retval None
  */
__STATIC_INLINE void LL_COMP_ClearFlag_OutputTrig(COMP_TypeDef *COMPx)
{
  if (COMPx == COMP1)
  {
    SET_BIT(COMP12->ICFR, COMP_ICFR_C1IF);
  }
  else
  {
    SET_BIT(COMP12->ICFR, COMP_ICFR_C2IF);
  }
}

/**
  * @}
  */

/** @defgroup COMP_LL_EF_IT_Management Comparartor IT management
  * @{
  */

/**
  * @brief  Enable comparator output trigger interrupt
  * @rmtoll ICFR     ITEN           LL_COMP_EnableIT_OutputTrig
  * @param  COMPx Comparator instance
  * @retval None
  */
__STATIC_INLINE void LL_COMP_EnableIT_OutputTrig(COMP_TypeDef *COMPx)
{
  SET_BIT(COMPx->CFGR, COMP_CFGRx_ITEN);
}

/**
  * @brief  Disable comparator output trigger interrupt
  * @rmtoll ICFR     ITEN           LL_COMP_DisableIT_OutputTrig
  * @param  COMPx Comparator instance
  * @retval None
  */
__STATIC_INLINE void LL_COMP_DisableIT_OutputTrig(COMP_TypeDef *COMPx)
{
  CLEAR_BIT(COMPx->CFGR, COMP_CFGRx_ITEN);
}

/**
  * @brief  Get comparator output trigger interrupt state
  * @rmtoll ICFR     ITEN           LL_COMP_IsEnabledIT_OutputTrig
  * @param  COMPx Comparator instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_COMP_IsEnabledIT_OutputTrig(COMP_TypeDef *COMPx)
{
  return ((READ_BIT(COMPx->CFGR, COMP_CFGRx_ITEN) == (COMP_CFGRx_ITEN)) ? 1UL : 0UL);
}

/**
  * @}
  */
  
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup COMP_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

ErrorStatus LL_COMP_DeInit(COMP_TypeDef *COMPx);
ErrorStatus LL_COMP_Init(COMP_TypeDef *COMPx, LL_COMP_InitTypeDef *COMP_InitStruct);
void        LL_COMP_StructInit(LL_COMP_InitTypeDef *COMP_InitStruct);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

/**
  * @}
  */

#endif /* COMP1 || COMP2 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32H7xx_LL_COMP_H */


