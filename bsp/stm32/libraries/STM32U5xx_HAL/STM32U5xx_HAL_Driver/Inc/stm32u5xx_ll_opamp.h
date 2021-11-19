/**
  ******************************************************************************
  * @file    stm32u5xx_ll_opamp.h
  * @author  MCD Application Team
  * @brief   Header file of OPAMP LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5xx_LL_OPAMP_H
#define STM32U5xx_LL_OPAMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined (OPAMP1) || defined (OPAMP2)

/** @defgroup OPAMP_LL OPAMP
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup OPAMP_LL_Private_Constants OPAMP Private Constants
  * @{
  */

/* Internal mask for OPAMP power mode:                                        */
/* To select into literal LL_OPAMP_POWERMODE_x the relevant bits for:         */
/* - OPAMP power mode into control register                                   */
/* - OPAMP trimming register offset                                           */

/* Internal register offset for OPAMP trimming configuration */
#define OPAMP_POWERMODE_OTR_REGOFFSET       0x00000000U
#define OPAMP_POWERMODE_LPOTR_REGOFFSET     0x00000002U
#define OPAMP_POWERMODE_OTR_REGOFFSET_MASK  (OPAMP_POWERMODE_OTR_REGOFFSET | OPAMP_POWERMODE_LPOTR_REGOFFSET)

/* Mask for OPAMP power mode into control register */
#define OPAMP_POWERMODE_CSR_BIT_MASK        (OPAMP_CSR_OPALPM | OPAMP_CSR_HSM)

/* Internal mask for OPAMP trimming of transistors differential pair NMOS     */
/* or PMOS.                                                                   */
/* To select into literal LL_OPAMP_TRIMMING_x the relevant bits for:          */
/* - OPAMP trimming selection of transistors differential pair                */
/* - OPAMP trimming values of transistors differential pair                   */
#define OPAMP_TRIMMING_SELECT_MASK          (OPAMP_CSR_CALSEL)
#define OPAMP_TRIMMING_VALUE_MASK           (OPAMP_OTR_TRIMOFFSETP | OPAMP_OTR_TRIMOFFSETN)

/**
  * @}
  */


/* Private macros ------------------------------------------------------------*/
/** @defgroup OPAMP_LL_Private_Macros OPAMP Private Macros
  * @{
  */

/**
  * @brief  Driver macro reserved for internal use: set a pointer to
  *         a register from a register basis from which an offset
  *         is applied.
  * @param  __REG__ Register basis from which the offset is applied.
  * @param  __REG_OFFSET__ Offset to be applied (unit: number of registers).
  * @retval Register address
  */
#define __OPAMP_PTR_REG_OFFSET(__REG__, __REG_OFFSET__)                        \
  ((uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((__REG_OFFSET__) << 1U))))
/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup OPAMP_LL_ES_INIT OPAMP Exported Init structure
  * @{
  */

/**
  * @brief  Structure definition of some features of OPAMP instance.
  */
typedef struct
{
  uint32_t PowerMode;                   /*!< Set the power mode Normal or Low-Power and the speed mode Normal or High.
                                             This parameter can be a value of @ref OPAMP_LL_EC_POWERMODE
                                             This feature can be modified afterwards using
                                             unitary function @ref LL_OPAMP_SetPowerMode(). */

  uint32_t FunctionalMode;              /*!< Set OPAMP functional mode by setting internal connections:
                                             OPAMP operation in standalone, follower, ...
                                             This parameter can be a value of @ref OPAMP_LL_EC_FUNCTIONAL_MODE
                                             @note If OPAMP is configured in mode PGA, the gain can be configured
                                             using function @ref LL_OPAMP_SetPGAGain().
                                             This feature can be modified afterwards using unitary
                                             function @ref LL_OPAMP_SetFunctionalMode(). */

  uint32_t InputNonInverting;           /*!< Set OPAMP input non-inverting connection.
                                             This parameter can be a value of @ref OPAMP_LL_EC_INPUT_NONINVERTING
                                             This feature can be modified afterwards using
                                             unitary function @ref LL_OPAMP_SetInputNonInverting(). */

  uint32_t InputInverting;              /*!< Set OPAMP inverting input connection.
                                             This parameter can be a value of @ref OPAMP_LL_EC_INPUT_INVERTING
                                             @note OPAMP inverting input is used with OPAMP in mode
                                             standalone or PGA with external capacitors for filtering circuit.
                                             Otherwise (OPAMP in mode follower), OPAMP inverting input is not used
                                             (not connected to GPIO pin), this parameter is discarded.
                                             This feature can be modified afterwards using
                                             unitary function @ref LL_OPAMP_SetInputInverting(). */

} LL_OPAMP_InitTypeDef;

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup OPAMP_LL_Exported_Constants OPAMP Exported Constants
  * @{
  */

/** @defgroup OPAMP_LL_EC_POWERSUPPLY_RANGE OPAMP power supply range
  * @{
  */
#define LL_OPAMP_POWERSUPPLY_RANGE_LOW   0x00000000U            /*!< Power supply range low  */
#define LL_OPAMP_POWERSUPPLY_RANGE_HIGH (OPAMP_CSR_OPARANGE)    /*!< Power supply range high - recommended for performance purpose */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_POWERMODE OPAMP power mode
  * @{
  */
#define LL_OPAMP_POWERMODE_NORMALPOWER_NORMALSPEED        0x00000000U                        /*!< OPAMP power mode normal speed normal    */
#define LL_OPAMP_POWERMODE_NORMALPOWER_HIGHSPEED          OPAMP_CSR_HSM                      /*!< OPAMP power mode normal speed high      */
#define LL_OPAMP_POWERMODE_LOWPOWER_NORMALSPEED           OPAMP_CSR_OPALPM                   /*!< OPAMP power mode low-power speed normal */
#define LL_OPAMP_POWERMODE_LOWPOWER_HIGHSPEED            (OPAMP_CSR_OPALPM | OPAMP_CSR_HSM)  /*!< OPAMP power mode low-power speed high   */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_MODE OPAMP mode calibration or functional.
  * @{
  */
#define LL_OPAMP_MODE_FUNCTIONAL         0x00000000U                                      /*!< OPAMP functional mode  */
#define LL_OPAMP_MODE_CALIBRATION        (OPAMP_CSR_CALON)                                /*!< OPAMP calibration mode */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_FUNCTIONAL_MODE OPAMP functional mode
  * @{
  */
#define LL_OPAMP_MODE_STANDALONE        0x00000000U                                       /*!< OPAMP functional mode, OPAMP operation in standalone */
#define LL_OPAMP_MODE_FOLLOWER          (OPAMP_CSR_OPAMODE_1 | OPAMP_CSR_OPAMODE_0)       /*!< OPAMP functional mode, OPAMP operation in follower   */
#define LL_OPAMP_MODE_PGA               (OPAMP_CSR_OPAMODE_1)                             /*!< OPAMP functional mode, OPAMP operation in PGA        */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_MODE_PGA_GAIN OPAMP PGA gain (relevant when OPAMP is in functional mode PGA)
  * @{
  */
#define LL_OPAMP_PGA_GAIN_2             0x00000000U                                        /*!< OPAMP PGA gain 2  */
#define LL_OPAMP_PGA_GAIN_4             (OPAMP_CSR_PGA_GAIN_0)                             /*!< OPAMP PGA gain 4  */
#define LL_OPAMP_PGA_GAIN_8             (OPAMP_CSR_PGA_GAIN_1)                             /*!< OPAMP PGA gain 8  */
#define LL_OPAMP_PGA_GAIN_16            (OPAMP_CSR_PGA_GAIN_1 | OPAMP_CSR_PGA_GAIN_0)      /*!< OPAMP PGA gain 16 */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_INPUT_NONINVERTING OPAMP input non-inverting
  * @{
  */
#define LL_OPAMP_INPUT_NONINVERT_IO0       0x00000000U             /*!< OPAMP non inverting input connected to GPIO pin (pin PA0 for OPAMP1, pin PA6 for OPAMP2)             */
#define LL_OPAMP_INPUT_NONINV_DAC1_CH1    (OPAMP_CSR_VP_SEL)      /*!< OPAMP non inverting input connected to DAC1 channel output(channel1 for OPAMP1, channel2 for OPAMP2) */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_INPUT_INVERTING OPAMP input inverting
  * @{
  */
#define LL_OPAMP_INPUT_INVERT_IO0         0x00000000U              /*!< OPAMP inverting input connected to GPIO pin (valid also in PGA mode for filtering). Note: OPAMP inverting input is used with OPAMP in mode standalone or PGA with external capacitors for filtering circuit. Otherwise (OPAMP in mode follower), OPAMP inverting input is not used (not connected to GPIO pin).                 */
#define LL_OPAMP_INPUT_INVERT_IO1         (OPAMP_CSR_VM_SEL_0)     /*!< OPAMP inverting input (low leakage input) connected to GPIO pin (available only on package BGA132). Note: OPAMP inverting input is used with OPAMP in mode standalone or PGA with external capacitors for filtering circuit. Otherwise (OPAMP in mode follower), OPAMP inverting input is not used (not connected to GPIO pin). */
#define LL_OPAMP_INPUT_INVERT_CONNECT_NO  (OPAMP_CSR_VM_SEL_1)     /*!< OPAMP inverting input not externally connected (intended for OPAMP in mode follower or PGA without external capacitors for filtering)                                                                                                                                                                                           */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_INPUT_LEGACY OPAMP inputs legacy literals name
  * @{
  */
#define LL_OPAMP_NONINVERTINGINPUT_IO0      LL_OPAMP_INPUT_NONINVERT_IO0
#define LL_OPAMP_NONINVERTINGINPUT_DAC_CH   LL_OPAMP_INPUT_NONINV_DAC1_CH1

#define LL_OPAMP_INVERTINGINPUT_IO0         LL_OPAMP_INPUT_INVERT_IO0
#define LL_OPAMP_INVERTINGINPUT_IO1         LL_OPAMP_INPUT_INVERT_IO1
#define LL_OPAMP_INVERTINGINPUT_CONNECT_NO  LL_OPAMP_INPUT_INVERT_CONNECT_NO

#define LL_OPAMP_INPUT_NONINVERT_DAC1_CH1   LL_OPAMP_INPUT_NONINV_DAC1_CH1
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_TRIMMING_MODE OPAMP trimming mode
  * @{
  */
#define LL_OPAMP_TRIMMING_FACTORY           0x00000000U              /*!< OPAMP trimming factors set to factory values */
#define LL_OPAMP_TRIMMING_USER              (OPAMP_CSR_USERTRIM)     /*!< OPAMP trimming factors set to user values    */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_TRIMMING_TRANSISTORS_DIFF_PAIR OPAMP trimming of transistors differential pair NMOS or PMOS
  * @{
  */
#define LL_OPAMP_TRIMMING_NMOS          (OPAMP_OTR_TRIMOFFSETN)                     /*!< OPAMP trimming of transistors differential pair NMOS */
#define LL_OPAMP_TRIMMING_PMOS          (OPAMP_OTR_TRIMOFFSETP | OPAMP_CSR_CALSEL)  /*!< OPAMP trimming of transistors differential pair PMOS */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_HW_DELAYS  Definitions of OPAMP hardware constraints delays
  * @note   Only OPAMP IP HW delays are defined in OPAMP LL driver driver,
  *         not timeout values.
  *         For details on delays values, refer to descriptions in source code
  *         above each literal definition.
  * @{
  */

/* Delay for OPAMP startup time (transition from state disable to enable).    */
/* Note: OPAMP startup time depends on board application environment:         */
/*       impedance connected to OPAMP output.                                 */
/*       The delay below is specified under conditions:                       */
/*        - OPAMP in mode low power                                           */
/*        - OPAMP in functional mode follower                                 */
/*        - load impedance of 4kOhm (min), 50pF (max)                         */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tWAKEUP").                                                      */
/* Unit: us                                                                   */
#define LL_OPAMP_DELAY_STARTUP_US         ((uint32_t) 30U)  /*!< Delay for OPAMP startup time */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup OPAMP_LL_Exported_Macros OPAMP Exported Macros
  * @{
  */
/** @defgroup OPAMP_LL_EM_WRITE_READ Common write and read registers macro
  * @{
  */
/**
  * @brief  Write a value in OPAMP register
  * @param  __INSTANCE__ OPAMP Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_OPAMP_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG((__INSTANCE__)->__REG__, (__VALUE__))

/**
  * @brief  Read a value in OPAMP register
  * @param  __INSTANCE__ OPAMP Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_OPAMP_ReadReg(__INSTANCE__, __REG__) READ_REG((__INSTANCE__)->__REG__)
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup OPAMP_LL_Exported_Functions OPAMP Exported Functions
  * @{
  */

/** @defgroup OPAMP_LL_EF_Configuration_opamp_common Configuration of OPAMP hierarchical scope: common OPAMP instances
  * @{
  */

/**
  * @brief  Set OPAMP power range.
  * @note   The OPAMP power range applies to several OPAMP instances
  *         (if several OPAMP instances available on the selected device).
  *         It is mandatory to set already the power range to high for performance purpose.
  * @note   On this STM32 series, setting of this feature is conditioned to
  *         OPAMP state:
  *         All OPAMP instances of the OPAMP common group must be disabled.
  *         This check can be done with function @ref LL_OPAMP_IsEnabled() for each
  *         OPAMP instance.
  * @note   LL_OPAMP_POWERSUPPLY_RANGE_HIGH parameter is highly recommended for performance purpose.
  * @rmtoll CSR      OPARANGE       LL_OPAMP_SetCommonPowerRange
  * @param  OPAMPxy_COMMON OPAMP common instance
  * @param  PowerRange This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_POWERSUPPLY_RANGE_LOW
  *         @arg @ref LL_OPAMP_POWERSUPPLY_RANGE_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetCommonPowerRange(OPAMP_Common_TypeDef *OPAMPxy_COMMON, uint32_t PowerRange)
{
  /* Prevent unused parameter warning */
  (void)(*OPAMPxy_COMMON);

  MODIFY_REG(OPAMP1->CSR, OPAMP_CSR_OPARANGE, PowerRange);
}

/**
  * @brief  Get OPAMP power range.
  * @note   The OPAMP power range applies to several OPAMP instances
  *         (if several OPAMP instances available on the selected device).
  * @rmtoll CSR      OPARANGE       LL_OPAMP_GetCommonPowerRange
  * @param  OPAMPxy_COMMON OPAMP common instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_POWERSUPPLY_RANGE_LOW
  *         @arg @ref LL_OPAMP_POWERSUPPLY_RANGE_HIGH
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetCommonPowerRange(OPAMP_Common_TypeDef *OPAMPxy_COMMON)
{
  /* Prevent unused parameter warning */
  (void)(*OPAMPxy_COMMON);

  return (uint32_t)(READ_BIT(OPAMP1->CSR, OPAMP_CSR_OPARANGE));
}

/**
  * @}
  */

/** @defgroup OPAMP_LL_EF_CONFIGURATION_OPAMP_INSTANCE Configuration of OPAMP hierarchical scope: OPAMP instance
  * @{
  */

/**
  * @brief  Set OPAMP power mode.
  * @note   The OPAMP must be disabled to change this configuration.
  * @rmtoll CSR      OPALPM         LL_OPAMP_SetPowerMode
  * @param  OPAMPx OPAMP instance
  * @param  PowerMode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_POWERMODE_NORMALPOWER_NORMALSPEED
  *         @arg @ref LL_OPAMP_POWERMODE_NORMALPOWER_HIGHSPEED
  *         @arg @ref LL_OPAMP_POWERMODE_LOWPOWER_NORMALSPEED
  *         @arg @ref LL_OPAMP_POWERMODE_LOWPOWER_HIGHSPEED
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetPowerMode(OPAMP_TypeDef *OPAMPx, uint32_t PowerMode)
{
  MODIFY_REG(OPAMPx->CSR, OPAMP_POWERMODE_CSR_BIT_MASK, PowerMode);
}

/**
  * @brief  Get OPAMP power mode.
  * @rmtoll CSR      OPALPM & HSM      LL_OPAMP_GetPowerMode
  * @param  OPAMPx OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_POWERMODE_NORMALPOWER_NORMALSPEED
  *         @arg @ref LL_OPAMP_POWERMODE_NORMALPOWER_HIGHSPEED
  *         @arg @ref LL_OPAMP_POWERMODE_LOWPOWER_NORMALSPEED
  *         @arg @ref LL_OPAMP_POWERMODE_LOWPOWER_HIGHSPEED
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetPowerMode(OPAMP_TypeDef *OPAMPx)
{
  uint32_t power_mode = (READ_BIT(OPAMPx->CSR, OPAMP_POWERMODE_CSR_BIT_MASK));

  return (uint32_t)(power_mode);
}

/**
  * @brief  Set OPAMP mode calibration or functional.
  * @note   OPAMP mode corresponds to functional or calibration mode:
  *          - functional mode: OPAMP operation in standalone, follower, ...
  *            Set functional mode using function
  *            @ref LL_OPAMP_SetFunctionalMode().
  *          - calibration mode: offset calibration of the selected
  *            transistors differential pair NMOS or PMOS.
  * @note   On this STM32 series, during calibration, OPAMP functional
  *         mode must be set to standalone or follower mode
  *         (in order to open internal connections to resistors
  *         of PGA mode).
  *         Refer to function @ref LL_OPAMP_SetFunctionalMode().
  * @rmtoll CSR      CALON          LL_OPAMP_SetMode
  * @param  OPAMPx OPAMP instance
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_MODE_FUNCTIONAL
  *         @arg @ref LL_OPAMP_MODE_CALIBRATION
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetMode(OPAMP_TypeDef *OPAMPx, uint32_t Mode)
{
  MODIFY_REG(OPAMPx->CSR, OPAMP_CSR_CALON, Mode);
}

/**
  * @brief  Get OPAMP mode calibration or functional.
  * @note   OPAMP mode corresponds to functional or calibration mode:
  *          - functional mode: OPAMP operation in standalone, follower, ...
  *            Set functional mode using function
  *            @ref LL_OPAMP_SetFunctionalMode().
  *          - calibration mode: offset calibration of the selected
  *            transistors differential pair NMOS or PMOS.
  * @rmtoll CSR      CALON          LL_OPAMP_GetMode
  * @param  OPAMPx OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_MODE_FUNCTIONAL
  *         @arg @ref LL_OPAMP_MODE_CALIBRATION
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetMode(OPAMP_TypeDef *OPAMPx)
{
  return (uint32_t)(READ_BIT(OPAMPx->CSR, OPAMP_CSR_CALON));
}

/**
  * @brief  Set OPAMP functional mode by setting internal connections.
  *         OPAMP operation in standalone, follower, ...
  * @note   This function reset bit of calibration mode to ensure
  *         to be in functional mode, in order to have OPAMP parameters
  *         (inputs selection, ...) set with the corresponding OPAMP mode
  *         to be effective.
  * @rmtoll CSR      OPAMODE        LL_OPAMP_SetFunctionalMode
  * @param  OPAMPx OPAMP instance
  * @param  FunctionalMode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_MODE_STANDALONE
  *         @arg @ref LL_OPAMP_MODE_FOLLOWER
  *         @arg @ref LL_OPAMP_MODE_PGA
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetFunctionalMode(OPAMP_TypeDef *OPAMPx, uint32_t FunctionalMode)
{
  /* Note: Bit OPAMP_CSR_CALON reset to ensure to be in functional mode */
  MODIFY_REG(OPAMPx->CSR, OPAMP_CSR_OPAMODE | OPAMP_CSR_CALON, FunctionalMode);
}

/**
  * @brief  Get OPAMP functional mode from setting of internal connections.
  *         OPAMP operation in standalone, follower, ...
  * @rmtoll CSR      OPAMODE        LL_OPAMP_GetFunctionalMode
  * @param  OPAMPx OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_MODE_STANDALONE
  *         @arg @ref LL_OPAMP_MODE_FOLLOWER
  *         @arg @ref LL_OPAMP_MODE_PGA
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetFunctionalMode(OPAMP_TypeDef *OPAMPx)
{
  return (uint32_t)(READ_BIT(OPAMPx->CSR, OPAMP_CSR_OPAMODE));
}

/**
  * @brief  Set OPAMP PGA gain.
  * @note   Preliminarily, OPAMP must be set in mode PGA
  *         using function @ref LL_OPAMP_SetFunctionalMode().
  * @rmtoll CSR      PGGAIN         LL_OPAMP_SetPGAGain
  * @param  OPAMPx OPAMP instance
  * @param  PGAGain This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_PGA_GAIN_2
  *         @arg @ref LL_OPAMP_PGA_GAIN_4
  *         @arg @ref LL_OPAMP_PGA_GAIN_8
  *         @arg @ref LL_OPAMP_PGA_GAIN_16
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetPGAGain(OPAMP_TypeDef *OPAMPx, uint32_t PGAGain)
{
  MODIFY_REG(OPAMPx->CSR, OPAMP_CSR_PGA_GAIN, PGAGain);
}

/**
  * @brief  Get OPAMP PGA gain.
  * @note   Preliminarily, OPAMP must be set in mode PGA
  *         using function @ref LL_OPAMP_SetFunctionalMode().
  * @rmtoll CSR      PGGAIN         LL_OPAMP_GetPGAGain
  * @param  OPAMPx OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_PGA_GAIN_2
  *         @arg @ref LL_OPAMP_PGA_GAIN_4
  *         @arg @ref LL_OPAMP_PGA_GAIN_8
  *         @arg @ref LL_OPAMP_PGA_GAIN_16
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetPGAGain(OPAMP_TypeDef *OPAMPx)
{
  return (uint32_t)(READ_BIT(OPAMPx->CSR, OPAMP_CSR_PGA_GAIN));
}

/**
  * @}
  */

/** @defgroup OPAMP_LL_EF_CONFIGURATION_INPUTS Configuration of OPAMP inputs
  * @{
  */

/**
  * @brief  Set OPAMP non-inverting input connection.
  * @rmtoll CSR      VPSEL          LL_OPAMP_SetInputNonInverting
  * @param  OPAMPx OPAMP instance
  * @param  InputNonInverting This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO0
  *         @arg @ref LL_OPAMP_INPUT_NONINV_DAC1_CH1
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetInputNonInverting(OPAMP_TypeDef *OPAMPx, uint32_t InputNonInverting)
{
  MODIFY_REG(OPAMPx->CSR, OPAMP_CSR_VP_SEL, InputNonInverting);
}

/**
  * @brief  Get OPAMP non-inverting input connection.
  * @rmtoll CSR      VPSEL          LL_OPAMP_GetInputNonInverting
  * @param  OPAMPx OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO0
  *         @arg @ref LL_OPAMP_INPUT_NONINV_DAC1_CH1
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetInputNonInverting(OPAMP_TypeDef *OPAMPx)
{
  return (uint32_t)(READ_BIT(OPAMPx->CSR, OPAMP_CSR_VP_SEL));
}

/**
  * @brief  Set OPAMP inverting input connection.
  * @note   OPAMP inverting input is used with OPAMP in mode standalone
  *         or PGA with external capacitors for filtering circuit.
  *         Otherwise (OPAMP in mode follower), OPAMP inverting input
  *         is not used (not connected to GPIO pin).
  * @rmtoll CSR      VMSEL          LL_OPAMP_SetInputInverting
  * @param  OPAMPx OPAMP instance
  * @param  InputInverting This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_INPUT_INVERT_IO0
  *         @arg @ref LL_OPAMP_INPUT_INVERT_IO1
  *         @arg @ref LL_OPAMP_INPUT_INVERT_CONNECT_NO
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetInputInverting(OPAMP_TypeDef *OPAMPx, uint32_t InputInverting)
{
  MODIFY_REG(OPAMPx->CSR, OPAMP_CSR_VM_SEL, InputInverting);
}

/**
  * @brief  Get OPAMP inverting input connection.
  * @rmtoll CSR      VMSEL          LL_OPAMP_GetInputInverting
  * @param  OPAMPx OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_INPUT_INVERT_IO0
  *         @arg @ref LL_OPAMP_INPUT_INVERT_IO1
  *         @arg @ref LL_OPAMP_INPUT_INVERT_CONNECT_NO
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetInputInverting(OPAMP_TypeDef *OPAMPx)
{
  return (uint32_t)(READ_BIT(OPAMPx->CSR, OPAMP_CSR_VM_SEL));
}

/**
  * @}
  */

/** @defgroup OPAMP_LL_EF_Configuration_Legacy_Functions Configuration of OPAMP, legacy functions name
  * @{
  */
/* Old functions name kept for legacy purpose, to be replaced by the          */
/* current functions name.                                                    */
__STATIC_INLINE void LL_OPAMP_SetNonInvertingInput(OPAMP_TypeDef *OPAMPx, uint32_t NonInvertingInput)
{
  LL_OPAMP_SetInputNonInverting(OPAMPx, NonInvertingInput);
}

__STATIC_INLINE void LL_OPAMP_SetInvertingInput(OPAMP_TypeDef *OPAMPx, uint32_t InvertingInput)
{
  LL_OPAMP_SetInputInverting(OPAMPx, InvertingInput);
}

/**
  * @}
  */

/** @defgroup OPAMP_LL_EF_OPAMP_TRIMMING Configuration and operation of OPAMP trimming
  * @{
  */

/**
  * @brief  Set OPAMP trimming mode.
  * @rmtoll CSR      USERTRIM       LL_OPAMP_SetTrimmingMode
  * @param  OPAMPx OPAMP instance
  * @param  TrimmingMode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_TRIMMING_FACTORY
  *         @arg @ref LL_OPAMP_TRIMMING_USER
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetTrimmingMode(OPAMP_TypeDef *OPAMPx, uint32_t TrimmingMode)
{
  MODIFY_REG(OPAMPx->CSR, OPAMP_CSR_USERTRIM, TrimmingMode);
}

/**
  * @brief  Get OPAMP trimming mode.
  * @rmtoll CSR      USERTRIM       LL_OPAMP_GetTrimmingMode
  * @param  OPAMPx OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_TRIMMING_FACTORY
  *         @arg @ref LL_OPAMP_TRIMMING_USER
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetTrimmingMode(OPAMP_TypeDef *OPAMPx)
{
  return (uint32_t)(READ_BIT(OPAMPx->CSR, OPAMP_CSR_USERTRIM));
}

/**
  * @brief  Set OPAMP offset to calibrate the selected transistors
  *         differential pair NMOS or PMOS.
  * @note   Preliminarily, OPAMP must be set in mode calibration
  *         using function @ref LL_OPAMP_SetMode().
  * @rmtoll CSR      CALSEL         LL_OPAMP_SetCalibrationSelection
  * @param  OPAMPx OPAMP instance
  * @param  TransistorsDiffPair This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_TRIMMING_NMOS
  *         @arg @ref LL_OPAMP_TRIMMING_PMOS
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetCalibrationSelection(OPAMP_TypeDef *OPAMPx, uint32_t TransistorsDiffPair)
{
  /* Parameter used with mask "OPAMP_TRIMMING_SELECT_MASK" because            */
  /* containing other bits reserved for other purpose.                        */
  MODIFY_REG(OPAMPx->CSR, OPAMP_CSR_CALSEL, (TransistorsDiffPair & OPAMP_TRIMMING_SELECT_MASK));
}

/**
  * @brief  Get OPAMP offset to calibrate the selected transistors
  *         differential pair NMOS or PMOS.
  * @note   Preliminarily, OPAMP must be set in mode calibration
  *         using function @ref LL_OPAMP_SetMode().
  * @rmtoll CSR      CALSEL         LL_OPAMP_GetCalibrationSelection
  * @param  OPAMPx OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_TRIMMING_NMOS
  *         @arg @ref LL_OPAMP_TRIMMING_PMOS
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetCalibrationSelection(OPAMP_TypeDef *OPAMPx)
{
  uint32_t CalibrationSelection = (uint32_t)(READ_BIT(OPAMPx->CSR, OPAMP_CSR_CALSEL));

  return (CalibrationSelection |
          (((CalibrationSelection & OPAMP_CSR_CALSEL) == 0UL) ? OPAMP_OTR_TRIMOFFSETN : OPAMP_OTR_TRIMOFFSETP));
}

/**
  * @brief  Get OPAMP calibration result of toggling output.
  * @note   This functions returns:
  *         0 if OPAMP calibration output is reset
  *         1 if OPAMP calibration output is set
  * @rmtoll CSR      CALOUT         LL_OPAMP_IsCalibrationOutputSet
  * @param  OPAMPx OPAMP instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_OPAMP_IsCalibrationOutputSet(OPAMP_TypeDef *OPAMPx)
{
  return ((READ_BIT(OPAMPx->CSR, OPAMP_CSR_CALOUT) == OPAMP_CSR_CALOUT) ? 1UL : 0UL);
}

/**
  * @brief  Set OPAMP trimming factor for the selected transistors
  *         differential pair NMOS or PMOS, corresponding to the selected
  *         power mode.
  * @rmtoll OTR      TRIMOFFSETN    LL_OPAMP_SetTrimmingValue
  *         OTR      TRIMOFFSETP    LL_OPAMP_SetTrimmingValue
  *         LPOTR    TRIMLPOFFSETN  LL_OPAMP_SetTrimmingValue
  *         LPOTR    TRIMLPOFFSETP  LL_OPAMP_SetTrimmingValue
  * @param  OPAMPx OPAMP instance
  * @param  PowerMode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_POWERMODE_NORMALPOWER_NORMALSPEED
  *         @arg @ref LL_OPAMP_POWERMODE_NORMALPOWER_HIGHSPEED
  *         @arg @ref LL_OPAMP_POWERMODE_LOWPOWER_NORMALSPEED
  *         @arg @ref LL_OPAMP_POWERMODE_LOWPOWER_HIGHSPEED
  * @param  TransistorsDiffPair This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_TRIMMING_NMOS
  *         @arg @ref LL_OPAMP_TRIMMING_PMOS
  * @param  TrimmingValue 0x00...0x1F
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetTrimmingValue(OPAMP_TypeDef *OPAMPx, uint32_t PowerMode, uint32_t TransistorsDiffPair,
                                               uint32_t TrimmingValue)
{
  uint32_t *preg = __OPAMP_PTR_REG_OFFSET(OPAMPx->OTR, (PowerMode & OPAMP_POWERMODE_OTR_REGOFFSET_MASK));

  /* Set bits with position in register depending on parameter                */
  /* "TransistorsDiffPair".                                                   */
  /* Parameter used with mask "OPAMP_TRIMMING_VALUE_MASK" because             */
  /* containing other bits reserved for other purpose.                        */
  MODIFY_REG(*preg,
             (TransistorsDiffPair & OPAMP_TRIMMING_VALUE_MASK),
             TrimmingValue << (
               (TransistorsDiffPair == LL_OPAMP_TRIMMING_NMOS) ? OPAMP_OTR_TRIMOFFSETN_Pos : OPAMP_OTR_TRIMOFFSETP_Pos)
            );
}

/**
  * @brief  Get OPAMP trimming factor for the selected transistors
  *         differential pair NMOS or PMOS, corresponding to the selected
  *         power mode.
  * @rmtoll OTR      TRIMOFFSETN    LL_OPAMP_GetTrimmingValue
  *         OTR      TRIMOFFSETP    LL_OPAMP_GetTrimmingValue
  *         LPOTR    TRIMLPOFFSETN  LL_OPAMP_GetTrimmingValue
  *         LPOTR    TRIMLPOFFSETP  LL_OPAMP_GetTrimmingValue
  * @param  OPAMPx OPAMP instance
  * @param  PowerMode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_POWERMODE_NORMALPOWER_NORMALSPEED
  *         @arg @ref LL_OPAMP_POWERMODE_NORMALPOWER_HIGHSPEED
  *         @arg @ref LL_OPAMP_POWERMODE_LOWPOWER_NORMALSPEED
  *         @arg @ref LL_OPAMP_POWERMODE_LOWPOWER_HIGHSPEED
  * @param  TransistorsDiffPair This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_TRIMMING_NMOS
  *         @arg @ref LL_OPAMP_TRIMMING_PMOS
  * @retval 0x0...0x1F
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetTrimmingValue(OPAMP_TypeDef *OPAMPx, uint32_t PowerMode,
                                                   uint32_t TransistorsDiffPair)
{
  const uint32_t *preg = __OPAMP_PTR_REG_OFFSET(OPAMPx->OTR, (PowerMode & OPAMP_POWERMODE_OTR_REGOFFSET_MASK));

  /* Retrieve bits with position in register depending on parameter           */
  /* "TransistorsDiffPair".                                                   */
  /* Parameter used with mask "OPAMP_TRIMMING_VALUE_MASK" because             */
  /* containing other bits reserved for other purpose.                        */
  return (uint32_t)(
           READ_BIT(*preg, (TransistorsDiffPair & OPAMP_TRIMMING_VALUE_MASK)) >>
           (
             (TransistorsDiffPair == LL_OPAMP_TRIMMING_NMOS) ? OPAMP_OTR_TRIMOFFSETN_Pos : OPAMP_OTR_TRIMOFFSETP_Pos));
}

/**
  * @}
  */

/** @defgroup OPAMP_LL_EF_OPERATION Operation on OPAMP instance
  * @{
  */
/**
  * @brief  Enable OPAMP instance.
  * @note   After enable from off state, OPAMP requires a delay
  *         to fulfill wake up time specification.
  *         Refer to device datasheet, parameter "tWAKEUP".
  * @rmtoll CSR      OPAMPXEN       LL_OPAMP_Enable
  * @param  OPAMPx OPAMP instance
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_Enable(OPAMP_TypeDef *OPAMPx)
{
  SET_BIT(OPAMPx->CSR, OPAMP_CSR_OPAEN);
}

/**
  * @brief  Disable OPAMP instance.
  * @rmtoll CSR      OPAMPXEN       LL_OPAMP_Disable
  * @param  OPAMPx OPAMP instance
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_Disable(OPAMP_TypeDef *OPAMPx)
{
  CLEAR_BIT(OPAMPx->CSR, OPAMP_CSR_OPAEN);
}

/**
  * @brief  Get OPAMP instance enable state
  *         (0: OPAMP is disabled, 1: OPAMP is enabled)
  * @rmtoll CSR      OPAMPXEN       LL_OPAMP_IsEnabled
  * @param  OPAMPx OPAMP instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_OPAMP_IsEnabled(OPAMP_TypeDef *OPAMPx)
{
  return ((READ_BIT(OPAMPx->CSR, OPAMP_CSR_OPAEN) == (OPAMP_CSR_OPAEN)) ? 1UL : 0UL);
}

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup OPAMP_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

ErrorStatus LL_OPAMP_DeInit(OPAMP_TypeDef *OPAMPx);
ErrorStatus LL_OPAMP_Init(OPAMP_TypeDef *OPAMPx, LL_OPAMP_InitTypeDef *OPAMP_InitStruct);
void        LL_OPAMP_StructInit(LL_OPAMP_InitTypeDef *OPAMP_InitStruct);

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

#endif /* OPAMP1 || OPAMP2 */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5xx_LL_OPAMP_H */

