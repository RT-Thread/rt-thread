/**
  ******************************************************************************
  * @file    stm32g4xx_ll_opamp.h
  * @author  MCD Application Team
  * @brief   Header file of OPAMP LL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G4xx_LL_OPAMP_H
#define STM32G4xx_LL_OPAMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx.h"

/** @addtogroup STM32G4xx_LL_Driver
  * @{
  */

#if defined (OPAMP1) || defined (OPAMP2) || defined (OPAMP3) || defined (OPAMP4) || defined (OPAMP5) || defined (OPAMP6)

/** @defgroup OPAMP_LL OPAMP
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup OPAMP_LL_Private_Constants OPAMP Private Constants
  * @{
  */

/* Internal mask for OPAMP trimming of transistors differential pair NMOS     */
/* or PMOS.                                                                   */
/* To select into literal LL_OPAMP_TRIMMING_x the relevant bits for:          */
/* - OPAMP trimming selection of transistors differential pair                */
/* - OPAMP trimming values of transistors differential pair                   */
#define OPAMP_TRIMMING_SELECT_MASK          (OPAMP_CSR_CALSEL)
#define OPAMP_TRIMMING_VALUE_MASK           (OPAMP_CSR_TRIMOFFSETN | OPAMP_CSR_TRIMOFFSETP)

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
  ((__IO uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((__REG_OFFSET__) << 2))))




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
  uint32_t PowerMode;                   /*!< Set OPAMP power mode.
                                             This parameter can be a value of @ref OPAMP_LL_EC_POWERMODE

                                             This feature can be modified afterwards using unitary function @ref LL_OPAMP_SetPowerMode(). */


  uint32_t FunctionalMode;              /*!< Set OPAMP functional mode by setting internal connections: OPAMP operation in standalone, follower, ...
                                             This parameter can be a value of @ref OPAMP_LL_EC_FUNCTIONAL_MODE
                                             @note If OPAMP is configured in mode PGA, the gain can be configured using function @ref LL_OPAMP_SetPGAGain().

                                             This feature can be modified afterwards using unitary function @ref LL_OPAMP_SetFunctionalMode(). */

  uint32_t InputNonInverting;           /*!< Set OPAMP input non-inverting connection.
                                             This parameter can be a value of @ref OPAMP_LL_EC_INPUT_NONINVERTING

                                             This feature can be modified afterwards using unitary function @ref LL_OPAMP_SetInputNonInverting(). */

  uint32_t InputInverting;              /*!< Set OPAMP inverting input connection.
                                             This parameter can be a value of @ref OPAMP_LL_EC_INPUT_INVERTING
                                             @note OPAMP inverting input is used with OPAMP in mode standalone or PGA with external capacitors for filtering circuit. Otherwise (OPAMP in mode follower), OPAMP inverting input is not used (not connected to GPIO pin), this parameter is discarded.

                                             This feature can be modified afterwards using unitary function @ref LL_OPAMP_SetInputInverting(). */

} LL_OPAMP_InitTypeDef;

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup OPAMP_LL_Exported_Constants OPAMP Exported Constants
  * @{
  */

/** @defgroup OPAMP_LL_EC_MODE OPAMP mode calibration or functional.
  * @{
  */
#define LL_OPAMP_MODE_FUNCTIONAL        (0x00000000UL)                              /*!< OPAMP functional mode */
#define LL_OPAMP_MODE_CALIBRATION       (OPAMP_CSR_CALON)                           /*!< OPAMP calibration mode */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_FUNCTIONAL_MODE OPAMP functional mode
  * @{
  */
#define LL_OPAMP_MODE_STANDALONE        (0x00000000UL)                                                /*!< OPAMP functional mode, OPAMP operation in standalone */
#define LL_OPAMP_MODE_FOLLOWER          (OPAMP_CSR_VMSEL_1 | OPAMP_CSR_VMSEL_0)                       /*!< OPAMP functional mode, OPAMP operation in follower */
#define LL_OPAMP_MODE_PGA               (OPAMP_CSR_VMSEL_1)                                           /*!< OPAMP functional mode, OPAMP operation in PGA */
#define LL_OPAMP_MODE_PGA_IO0           (OPAMP_CSR_PGGAIN_4|OPAMP_CSR_VMSEL_1)                        /*!< In PGA mode, the inverting input is connected to VINM0 for filtering */
#define LL_OPAMP_MODE_PGA_IO0_BIAS      (OPAMP_CSR_PGGAIN_3|OPAMP_CSR_VMSEL_1)                        /*!< In PGA mode, the inverting input is connected to VINM0
                                                                                                          - Input signal on VINM0, bias on VINPx: negative gain
                                                                                                          - Bias on VINM0, input signal on VINPx: positive gain */
#define LL_OPAMP_MODE_PGA_IO0_IO1_BIAS  (OPAMP_CSR_PGGAIN_4|OPAMP_CSR_PGGAIN_3|OPAMP_CSR_VMSEL_1)     /*!< In PGA mode, the inverting input is connected to VINM0
                                                                                                          - Input signal on VINM0, bias on VINPx: negative gain
                                                                                                          - Bias on VINM0, input signal on VINPx: positive gain
                                                                                                          And VINM1 is connected too for filtering */

/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_MODE_PGA_GAIN OPAMP PGA gain (relevant when OPAMP is in functional mode PGA)
  * @note Gain sign:
  *         - is positive if the @ref OPAMP_LL_EC_FUNCTIONAL_MODE configuration is
  *           @ref LL_OPAMP_MODE_PGA or LL_OPAMP_MODE_PGA_IO0
  *         - may be positive or negative if the @ref OPAMP_LL_EC_FUNCTIONAL_MODE configuration is
  *           @ref LL_OPAMP_MODE_PGA_IO0_BIAS or LL_OPAMP_MODE_PGA_IO0_IO1_BIAS
  *       see @ref OPAMP_LL_EC_FUNCTIONAL_MODE for more details
  * @{
  */
#define LL_OPAMP_PGA_GAIN_2_OR_MINUS_1             (0x00000000UL)                                                 /*!< OPAMP PGA gain 2  or -1  */
#define LL_OPAMP_PGA_GAIN_4_OR_MINUS_3             (                                          OPAMP_CSR_PGGAIN_0) /*!< OPAMP PGA gain 4  or -3  */
#define LL_OPAMP_PGA_GAIN_8_OR_MINUS_7             (                     OPAMP_CSR_PGGAIN_1                     ) /*!< OPAMP PGA gain 8  or -7  */
#define LL_OPAMP_PGA_GAIN_16_OR_MINUS_15           (                     OPAMP_CSR_PGGAIN_1 | OPAMP_CSR_PGGAIN_0) /*!< OPAMP PGA gain 16 or -15 */
#define LL_OPAMP_PGA_GAIN_32_OR_MINUS_31           (OPAMP_CSR_PGGAIN_2                                          ) /*!< OPAMP PGA gain 32 or -31 */
#define LL_OPAMP_PGA_GAIN_64_OR_MINUS_63           (OPAMP_CSR_PGGAIN_2 |                      OPAMP_CSR_PGGAIN_0) /*!< OPAMP PGA gain 64 or -63 */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_INPUT_NONINVERTING OPAMP input non-inverting
  * @{
  */
#define LL_OPAMP_INPUT_NONINVERT_IO0         (0x00000000UL)        /*!< OPAMP non inverting input connected to I/O VINP0
                                                                        (PA1  for OPAMP1, PA7  for OPAMP2, PB0  for OPAMP3, PB13 for OPAMP4, PB14 for OPAMP5, PB12 for OPAMP6)
                                                                        Note: On this STM32 serie, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
#define LL_OPAMP_INPUT_NONINVERT_IO1         OPAMP_CSR_VPSEL_0     /*!< OPAMP non inverting input connected to I/O VINP1
                                                                        (PA3  for OPAMP1, PB14 for OPAMP2, PB13 for OPAMP3, PD11 for OPAMP4, PD12 for OPAMP5, PD9  for OPAMP6)
                                                                        Note: On this STM32 serie, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
#define LL_OPAMP_INPUT_NONINVERT_IO2         OPAMP_CSR_VPSEL_1     /*!< OPAMP non inverting input connected to I/O VINP2
                                                                        (PA7  for OPAMP1, PB0  for OPAMP2, PA1  for OPAMP3, PB11 for OPAMP4, PC3  for OPAMP5, PB13 for OPAMP6)
                                                                        Note: On this STM32 serie, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
#define LL_OPAMP_INPUT_NONINVERT_IO3         OPAMP_CSR_VPSEL       /*!< OPAMP non inverting input connected to I/O VINP3
                                                                        (PD14 for OPAMP2) */
#define LL_OPAMP_INPUT_NONINVERT_DAC         OPAMP_CSR_VPSEL       /*!< OPAMP non inverting input connected internally to DAC channel
                                                                        (DAC3_CH1 for OPAMP1, DAC3_CH2  for OPAMP3, DAC4_CH1 for OPAMP4, DAC4_CH2 for OPAMP5, DAC3_CH1 for OPAMP6)
                                                                        Note: On this STM32 serie, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_INPUT_INVERTING OPAMP input inverting
  * @note OPAMP inverting input is used with OPAMP in mode standalone or PGA with negative gain or bias.
  *       Otherwise (OPAMP in mode follower), OPAMP inverting input is not used (not connected to GPIO pin).
  * @{
  */
#define LL_OPAMP_INPUT_INVERT_IO0         (0x00000000UL)           /*!< OPAMP inverting input connected to I/O VINM0
                                                                        (PA3  for OPAMP1, PA5  for OPAMP2, PB2  for OPAMP3, PB10 for OPAMP4, PB15 for OPAMP5, PA1  for OPAMP6)
                                                                        Note: On this STM32 serie, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
#define LL_OPAMP_INPUT_INVERT_IO1         OPAMP_CSR_VMSEL_0        /*!< OPAMP inverting input connected to I/0 VINM1
                                                                        (PC5  for OPAMP1, PC5  for OPAMP2, PB10 for OPAMP3, PB8  for OPAMP4, PA3  for OPAMP5, PB1  for OPAMP6)
                                                                        Note: On this STM32 serie, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
#define LL_OPAMP_INPUT_INVERT_CONNECT_NO  OPAMP_CSR_VMSEL_1        /*!< OPAMP inverting input not externally connected (intended for OPAMP in mode follower or PGA with positive gain without bias).
                                                                        Note: On this STM32 serie, this literal include cases of value 0x11 for mode follower and value 0x10 for mode PGA. */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_INPUT_NONINVERTING_SECONDARY OPAMP input non-inverting secondary
  * @{
  */
#define LL_OPAMP_INPUT_NONINVERT_IO0_SEC         (0x00000000UL)       /*!< OPAMP secondary non inverting input connected to I/O VINP0
                                                                           (PA1  for OPAMP1, PA7  for OPAMP2, PB0  for OPAMP3, PB13 for OPAMP4, PB14 for OPAMP5, PB12 for OPAMP6)
                                                                           Note: On this STM32 serie, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
#define LL_OPAMP_INPUT_NONINVERT_IO1_SEC         OPAMP_TCMR_VPSSEL_0  /*!< OPAMP secondary non inverting input connected to I/O VINP1
                                                                           (PA3  for OPAMP1, PB14 for OPAMP2, PB13 for OPAMP3, PD11 for OPAMP4, PD12 for OPAMP5, PD9  for OPAMP6)
                                                                           Note: On this STM32 serie, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
#define LL_OPAMP_INPUT_NONINVERT_IO2_SEC         OPAMP_TCMR_VPSSEL_1  /*!< OPAMP secondary non inverting input connected to I/O VINP2
                                                                           (PA7  for OPAMP1, PB0  for OPAMP2, PA1  for OPAMP3, PB11 for OPAMP4, PC3  for OPAMP5, PB13 for OPAMP6)
                                                                           Note: On this STM32 serie, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
#define LL_OPAMP_INPUT_NONINVERT_IO3_SEC         OPAMP_TCMR_VPSSEL    /*!< OPAMP secondary non inverting input connected to I/O VINP3
                                                                           (PD14 for OPAMP2) */
#define LL_OPAMP_INPUT_NONINVERT_DAC_SEC         OPAMP_TCMR_VPSSEL    /*!< OPAMP secondary non inverting input connected internally to DAC channel
                                                                           (DAC3_CH1 for OPAMP1, DAC3_CH2  for OPAMP3, DAC4_CH1 for OPAMP4, DAC4_CH2 for OPAMP5, DAC3_CH1 for OPAMP6)
                                                                           Note: On this STM32 serie, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_INPUT_INVERTING_SECONDARY OPAMP input inverting secondary
  * @note OPAMP inverting input is used with OPAMP in mode standalone or PGA with negative gain or bias.
  *       Otherwise (OPAMP in mode follower), OPAMP inverting input is not used (not connected to GPIO pin).
  * @{
  */
#define LL_OPAMP_INPUT_INVERT_IO0_SEC         (0x00000000UL)          /*!< OPAMP secondary mode is standalone mode - Only applicable if @ref LL_OPAMP_MODE_STANDALONE
                                                                           has been configured by call to @ref LL_OPAMP_Init() or @ref LL_OPAMP_SetFunctionalMode().
                                                                           OPAMP secondary inverting input connected to I/O VINM0.
                                                                           (PA3  for OPAMP1, PA5  for OPAMP2, PB2  for OPAMP3, PB10 for OPAMP4, PB15 for OPAMP5, PA1  for OPAMP6)
                                                                           Note: On this STM32 serie, all OPAMPx are not available on all devices. Refer to device datasheet for more details  */
#define LL_OPAMP_INPUT_INVERT_IO1_SEC         OPAMP_TCMR_VMSSEL       /*!< OPAMP secondary mode is standalone mode - Only applicable if @ref LL_OPAMP_MODE_STANDALONE
                                                                           has been configured by call to @ref LL_OPAMP_Init() or @ref LL_OPAMP_SetFunctionalMode().
                                                                           OPAMP secondary inverting input connected to I/0 VINM1
                                                                           (PC5  for OPAMP1, PC5  for OPAMP2, PB10 for OPAMP3, PB8  for OPAMP4, PA3  for OPAMP5, PB1  for OPAMP6)
                                                                           Note: On this STM32 serie, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
#define LL_OPAMP_INPUT_INVERT_PGA_SEC         (0x00000000UL)          /*!< OPAMP secondary mode is PGA mode - Only applicable if configured mode through call to @ref LL_OPAMP_Init()
                                                                           or @ref LL_OPAMP_SetFunctionalMode() is NOT @ref LL_OPAMP_MODE_STANDALONE.
                                                                           OPAMP secondary inverting input is:
                                                                             - Not connected if configured mode is @ref LL_OPAMP_MODE_FOLLOWER or @ref LL_OPAMP_MODE_PGA
                                                                             - Connected to VINM0 and possibly VINM1 if any of the other modes as been configured
                                                                           (see @ref OPAMP_LL_EC_FUNCTIONAL_MODE description for more details on PGA connection modes) */
#define LL_OPAMP_INPUT_INVERT_FOLLOWER_SEC    OPAMP_TCMR_VMSSEL       /*!< OPAMP secondary mode is Follower mode - Only applicable if configured mode through call to @ref LL_OPAMP_Init()
                                                                           or @ref LL_OPAMP_SetFunctionalMode() is NOT @ref LL_OPAMP_MODE_STANDALONE.
                                                                           OPAMP secondary inverting input is not connected. */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_INTERNAL_OUPUT_MODE OPAMP internal output mode
  * @{
  */
#define LL_OPAMP_INTERNAL_OUPUT_DISABLED       (0x00000000UL)         /*!< OPAMP internal output to ADC disabled. */
#define LL_OPAMP_INTERNAL_OUPUT_ENABLED        OPAMP_CSR_OPAMPINTEN   /*!< OPAMP internal output to ADC enabled.
                                                                             - OPAMP1 internal output is connected to ADC1/Channel13
                                                                             - OPAMP2 internal output is connected to ADC2/Channel16
                                                                             - OPAMP3 internal output is connected to ADC2/Channel18 & ADC3/Channel13
                                                                             - OPAMP4 internal output is connected to ADC5/Channel5
                                                                             - OPAMP5 internal output is connected to ADC5/Channel3
                                                                             - OPAMP6 internal output is connected to ADC4/Channel17
                                                                           Note: On this STM32 serie, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_INPUT_MUX_MODE OPAMP inputs multiplexer mode
  * @note The switch can be controlled either by a single timer or a combination of them,
  *       in this case application has to 'ORed' the values below
  *       ex LL_OPAMP_INPUT_MUX_TIM1_CH6 | LL_OPAMP_INPUT_MUX_TIM20_CH6
  * @{
  */
#define LL_OPAMP_INPUT_MUX_DISABLE       (0x00000000UL)         /*!< OPAMP inputs timer controlled multiplexer mode disabled. */
#define LL_OPAMP_INPUT_MUX_TIM1_CH6      OPAMP_TCMR_T1CMEN      /*!< OPAMP inputs timer controlled multiplexer mode enabled, controlled by TIM1 OC6. */
#define LL_OPAMP_INPUT_MUX_TIM8_CH6      OPAMP_TCMR_T8CMEN      /*!< OPAMP inputs timer controlled multiplexer mode enabled, controlled by TIM8 OC6. */
#define LL_OPAMP_INPUT_MUX_TIM20_CH6     OPAMP_TCMR_T20CMEN     /*!< OPAMP inputs timer controlled multiplexer mode enabled, controlled by TIM20 OC6.
                                                                     Note: On this STM32 serie, TIM20 is not available on all devices. Refer to device datasheet for more details */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_POWER_MODE OPAMP PowerMode
  * @{
  */
#define LL_OPAMP_POWERMODE_NORMAL        (0x00000000UL)         /*!< OPAMP output in normal mode */
#define LL_OPAMP_POWERMODE_HIGHSPEED     OPAMP_CSR_HIGHSPEEDEN  /*!< OPAMP output in highspeed mode */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_TRIMMING_MODE OPAMP trimming mode
  * @{
  */
#define LL_OPAMP_TRIMMING_FACTORY       (0x00000000UL)           /*!< OPAMP trimming factors set to factory values */
#define LL_OPAMP_TRIMMING_USER          OPAMP_CSR_USERTRIM      /*!< OPAMP trimming factors set to user values */
/**
  * @}
  */

/** @defgroup OPAMP_LL_EC_TRIMMING_TRANSISTORS_DIFF_PAIR OPAMP trimming of transistors differential pair NMOS or PMOS
  * @{
  */
#define LL_OPAMP_TRIMMING_NMOS_VREF_90PC_VDDA  (OPAMP_CSR_TRIMOFFSETN | OPAMP_CSR_CALSEL_1 | OPAMP_CSR_CALSEL_0) /*!< OPAMP trimming of transistors differential pair NMOS (internal reference voltage set to 0.9*Vdda). Default parameters to be used for calibration using two trimming steps (one with each transistors differential pair NMOS and PMOS). */
#define LL_OPAMP_TRIMMING_NMOS_VREF_50PC_VDDA  (OPAMP_CSR_TRIMOFFSETN | OPAMP_CSR_CALSEL_1                     ) /*!< OPAMP trimming of transistors differential pair NMOS (internal reference voltage set to 0.5*Vdda). */
#define LL_OPAMP_TRIMMING_PMOS_VREF_10PC_VDDA  (OPAMP_CSR_TRIMOFFSETP                      | OPAMP_CSR_CALSEL_0) /*!< OPAMP trimming of transistors differential pair PMOS (internal reference voltage set to 0.1*Vdda). Default parameters to be used for calibration using two trimming steps (one with each transistors differential pair NMOS and PMOS). */
#define LL_OPAMP_TRIMMING_PMOS_VREF_3_3PC_VDDA (OPAMP_CSR_TRIMOFFSETP                                          ) /*!< OPAMP trimming of transistors differential pair PMOS (internal reference voltage set to 0.33*Vdda). */
#define LL_OPAMP_TRIMMING_NMOS          (LL_OPAMP_TRIMMING_NMOS_VREF_90PC_VDDA) /*!< OPAMP trimming of transistors differential pair NMOS (internal reference voltage set to 0.9*Vdda). Default parameters to be used for calibration using two trimming steps (one with each transistors differential pair NMOS and PMOS). */
#define LL_OPAMP_TRIMMING_PMOS          (LL_OPAMP_TRIMMING_PMOS_VREF_10PC_VDDA) /*!< OPAMP trimming of transistors differential pair PMOS (internal reference voltage set to 0.1*Vdda). Default parameters to be used for calibration using two trimming steps (one with each transistors differential pair NMOS and PMOS). */
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
/*        - OPAMP in functional mode follower                                 */
/*        - load impedance of 4kOhm (min), 50pF (max)                         */
/* Literal set to maximum value (refer to device datasheet,                   */
/* parameter "tWAKEUP").                                                      */
/* Unit: us                                                                   */
#define LL_OPAMP_DELAY_STARTUP_US         (6)  /*!< Delay for OPAMP startup time */
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

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup OPAMP_LL_Exported_Functions OPAMP Exported Functions
  * @{
  */

/** @defgroup OPAMP_LL_EF_CONFIGURATION_OPAMP_INSTANCE Configuration of OPAMP hierarchical scope: OPAMP instance
  * @{
  */

/**
  * @brief  Set OPAMP mode calibration or functional.
  * @note   OPAMP mode corresponds to functional or calibration mode:
  *          - functional mode: OPAMP operation in standalone, follower, ...
  *            Set functional mode using function
  *            @ref LL_OPAMP_SetFunctionalMode().
  *          - calibration mode: offset calibration of the selected
  *            transistors differential pair NMOS or PMOS.
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
  * @rmtoll CSR      VMSEL          LL_OPAMP_SetFunctionalMode
  * @param  OPAMPx OPAMP instance
  * @param  FunctionalMode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_MODE_STANDALONE
  *         @arg @ref LL_OPAMP_MODE_FOLLOWER
  *         @arg @ref LL_OPAMP_MODE_PGA
  *         @arg @ref LL_OPAMP_MODE_PGA_IO0
  *         @arg @ref LL_OPAMP_MODE_PGA_IO0_BIAS
  *         @arg @ref LL_OPAMP_MODE_PGA_IO0_IO1_BIAS
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetFunctionalMode(OPAMP_TypeDef *OPAMPx, uint32_t FunctionalMode)
{
  /* Note: Bit OPAMP_CSR_CALON reset to ensure to be in functional mode */
  MODIFY_REG(OPAMPx->CSR, OPAMP_CSR_PGGAIN_4 | OPAMP_CSR_PGGAIN_3 | OPAMP_CSR_VMSEL | OPAMP_CSR_CALON, FunctionalMode);
}

/**
  * @brief  Get OPAMP functional mode from setting of internal connections.
  *         OPAMP operation in standalone, follower, ...
  * @rmtoll CSR      VMSEL          LL_OPAMP_GetFunctionalMode
  * @param  OPAMPx OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_MODE_STANDALONE
  *         @arg @ref LL_OPAMP_MODE_FOLLOWER
  *         @arg @ref LL_OPAMP_MODE_PGA
  *         @arg @ref LL_OPAMP_MODE_PGA_IO0
  *         @arg @ref LL_OPAMP_MODE_PGA_IO0_BIAS
  *         @arg @ref LL_OPAMP_MODE_PGA_IO0_IO1_BIAS
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetFunctionalMode(OPAMP_TypeDef *OPAMPx)
{
  return (uint32_t)(READ_BIT(OPAMPx->CSR, OPAMP_CSR_PGGAIN_4 | OPAMP_CSR_PGGAIN_3 | OPAMP_CSR_VMSEL));
}

/**
  * @brief  Set OPAMP PGA gain.
  * @note   Preliminarily, OPAMP must be set in mode PGA
  *         using function @ref LL_OPAMP_SetFunctionalMode().
  * @rmtoll CSR      PGGAIN         LL_OPAMP_SetPGAGain
  * @param  OPAMPx OPAMP instance
  * @param  PGAGain This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_PGA_GAIN_2_OR_MINUS_1
  *         @arg @ref LL_OPAMP_PGA_GAIN_4_OR_MINUS_3
  *         @arg @ref LL_OPAMP_PGA_GAIN_8_OR_MINUS_7
  *         @arg @ref LL_OPAMP_PGA_GAIN_16_OR_MINUS_15
  *         @arg @ref LL_OPAMP_PGA_GAIN_32_OR_MINUS_31
  *         @arg @ref LL_OPAMP_PGA_GAIN_64_OR_MINUS_63
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetPGAGain(OPAMP_TypeDef *OPAMPx, uint32_t PGAGain)
{
  MODIFY_REG(OPAMPx->CSR, OPAMP_CSR_PGGAIN_2 | OPAMP_CSR_PGGAIN_1 | OPAMP_CSR_PGGAIN_0, PGAGain);
}

/**
  * @brief  Get OPAMP PGA gain.
  * @note   Preliminarily, OPAMP must be set in mode PGA
  *         using function @ref LL_OPAMP_SetFunctionalMode().
  * @rmtoll CSR      PGGAIN         LL_OPAMP_GetPGAGain
  * @param  OPAMPx OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_PGA_GAIN_2_OR_MINUS_1
  *         @arg @ref LL_OPAMP_PGA_GAIN_4_OR_MINUS_3
  *         @arg @ref LL_OPAMP_PGA_GAIN_8_OR_MINUS_7
  *         @arg @ref LL_OPAMP_PGA_GAIN_16_OR_MINUS_15
  *         @arg @ref LL_OPAMP_PGA_GAIN_32_OR_MINUS_31
  *         @arg @ref LL_OPAMP_PGA_GAIN_64_OR_MINUS_63
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetPGAGain(OPAMP_TypeDef *OPAMPx)
{
  return (uint32_t)(READ_BIT(OPAMPx->CSR, OPAMP_CSR_PGGAIN_2 | OPAMP_CSR_PGGAIN_1 | OPAMP_CSR_PGGAIN_0));
}

/**
  * @brief  Set OPAMP power mode normal or highspeed.
  * @note   OPAMP highspeed mode allows output stage to have a better slew rate.
  * @rmtoll CSR      HIGHSPEEDEN     LL_OPAMP_SetPowerMode
  * @param  OPAMPx OPAMP instance
  * @param  PowerMode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_POWERMODE_NORMAL
  *         @arg @ref LL_OPAMP_POWERMODE_HIGHSPEED
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetPowerMode(OPAMP_TypeDef *OPAMPx, uint32_t PowerMode)
{
  MODIFY_REG(OPAMPx->CSR, OPAMP_CSR_HIGHSPEEDEN, PowerMode);
}

/**
  * @brief  Get OPAMP power mode normal or highspeed.
  * @note   OPAMP highspeed mode allows output stage to have a better slew rate.
  * @rmtoll CSR      HIGHSPEEDEN     LL_OPAMP_GetPowerMode
  * @param  OPAMPx OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_POWERMODE_NORMAL
  *         @arg @ref LL_OPAMP_POWERMODE_HIGHSPEED
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetPowerMode(OPAMP_TypeDef *OPAMPx)
{
  return (uint32_t)(READ_BIT(OPAMPx->CSR, OPAMP_CSR_HIGHSPEEDEN));
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
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO1
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO2
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO3
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_DAC
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetInputNonInverting(OPAMP_TypeDef *OPAMPx, uint32_t InputNonInverting)
{
  MODIFY_REG(OPAMPx->CSR, OPAMP_CSR_VPSEL, InputNonInverting);
}

/**
  * @brief  Get OPAMP non-inverting input connection.
  * @rmtoll CSR      VPSEL          LL_OPAMP_GetInputNonInverting
  * @param  OPAMPx OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO0
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO1
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO2
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO3
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_DAC
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetInputNonInverting(OPAMP_TypeDef *OPAMPx)
{
  return (uint32_t)(READ_BIT(OPAMPx->CSR, OPAMP_CSR_VPSEL));
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
  /* Manage cases of OPAMP inverting input not connected (0x10 and 0x11)      */
  /* to not modify OPAMP mode follower or PGA.                                */
  /* Bit OPAMP_CSR_VMSEL_1 is set by OPAMP mode (follower, PGA). */
  MODIFY_REG(OPAMPx->CSR, (~(InputInverting >> 1)) & OPAMP_CSR_VMSEL_0, InputInverting);
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
  register uint32_t input_inverting = READ_BIT(OPAMPx->CSR, OPAMP_CSR_VMSEL);

  /* Manage cases 0x10 and 0x11 to return the same value: OPAMP inverting     */
  /* input not connected.                                                     */
  return (input_inverting & ~((input_inverting >> 1) & OPAMP_CSR_VMSEL_0));
}

/**
  * @brief  Set OPAMP non-inverting input secondary connection.
  * @rmtoll TCMR     VPSSEL         LL_OPAMP_SetInputNonInvertingSecondary
  * @param  OPAMPx OPAMP instance
  * @param  InputNonInverting This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO0_SEC
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO1_SEC
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO2_SEC
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO3_SEC
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_DAC_SEC
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetInputNonInvertingSecondary(OPAMP_TypeDef *OPAMPx, uint32_t InputNonInverting)
{
  MODIFY_REG(OPAMPx->TCMR, OPAMP_TCMR_VPSSEL, InputNonInverting);
}

/**
  * @brief  Get OPAMP non-inverting input secondary connection.
  * @rmtoll TCMR     VPSSEL         LL_OPAMP_GetInputNonInvertingSecondary
  * @param  OPAMPx OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO0_SEC
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO1_SEC
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO2_SEC
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_IO3_SEC
  *         @arg @ref LL_OPAMP_INPUT_NONINVERT_DAC_SEC
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetInputNonInvertingSecondary(OPAMP_TypeDef *OPAMPx)
{
  return (uint32_t)(READ_BIT(OPAMPx->TCMR, OPAMP_TCMR_VPSSEL));
}

/**
  * @brief  Set OPAMP inverting input secondary connection.
  * @note   OPAMP inverting input is used with OPAMP in mode standalone
  *         or PGA with external capacitors for filtering circuit.
  *         Otherwise (OPAMP in mode follower), OPAMP inverting input
  *         is not used (not connected to GPIO pin).
  * @rmtoll TCMR     VMSSEL         LL_OPAMP_SetInputInvertingSecondary
  * @param  OPAMPx OPAMP instance
  * @param  InputInverting This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_INPUT_INVERT_IO0_SEC
  *         @arg @ref LL_OPAMP_INPUT_INVERT_IO1_SEC
  *         @arg @ref LL_OPAMP_INPUT_INVERT_PGA_SEC
  *         @arg @ref LL_OPAMP_INPUT_INVERT_FOLLOWER_SEC
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetInputInvertingSecondary(OPAMP_TypeDef *OPAMPx, uint32_t InputInverting)
{
  MODIFY_REG(OPAMPx->TCMR, OPAMP_TCMR_VMSSEL, InputInverting);
}

/**
  * @brief  Get OPAMP inverting input secondary connection.
  * @rmtoll TCMR     VMSSEL         LL_OPAMP_GetInputInvertingSecondary
  * @param  OPAMPx OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_INPUT_INVERT_IO0_SEC
  *         @arg @ref LL_OPAMP_INPUT_INVERT_IO1_SEC
  *         @arg @ref LL_OPAMP_INPUT_INVERT_PGA_SEC
  *         @arg @ref LL_OPAMP_INPUT_INVERT_FOLLOWER_SEC
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetInputInvertingSecondary(OPAMP_TypeDef *OPAMPx)
{
  return (uint32_t)(READ_BIT(OPAMPx->TCMR, OPAMP_TCMR_VMSSEL));
}

/**
  * @brief  Set OPAMP inputs multiplexer mode.
  * @rmtoll TCMR     TCMEN          LL_OPAMP_SetInputsMuxMode
  * @param  OPAMPx OPAMP instance
  * @param  InputsMuxMode This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_INPUT_MUX_DISABLE
  *         @arg @ref LL_OPAMP_INPUT_MUX_TIM1_CH6
  *         @arg @ref LL_OPAMP_INPUT_MUX_TIM8_CH6
  *         @arg @ref LL_OPAMP_INPUT_MUX_TIM20_CH6  (1)
  *         On this STM32 serie, this value is not available on all devices. Refer to datasheet for details.
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetInputsMuxMode(OPAMP_TypeDef *OPAMPx, uint32_t InputsMuxMode)
{
  MODIFY_REG(OPAMPx->TCMR, OPAMP_TCMR_T1CMEN | OPAMP_TCMR_T8CMEN | OPAMP_TCMR_T20CMEN, InputsMuxMode);
}

/**
  * @brief  Get OPAMP inputs multiplexer mode.
  * @rmtoll TCMR     TCMEN          LL_OPAMP_GetInputsMuxMode
  * @param  OPAMPx OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_INPUT_MUX_DISABLE
  *         @arg @ref LL_OPAMP_INPUT_MUX_TIM1_CH6
  *         @arg @ref LL_OPAMP_INPUT_MUX_TIM8_CH6
  *         @arg @ref LL_OPAMP_INPUT_MUX_TIM20_CH6  (1)
  *         On this STM32 serie, this value is not available on all devices. Refer to datasheet for details.
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetInputsMuxMode(OPAMP_TypeDef *OPAMPx)
{
  return (uint32_t)(READ_BIT(OPAMPx->TCMR, OPAMP_TCMR_T1CMEN | OPAMP_TCMR_T8CMEN | OPAMP_TCMR_T20CMEN));
}

/**
  * @brief  Set OPAMP internal output.
  * @note   OPAMP internal output is used to link OPAMP output to ADC input internally.
  * @rmtoll CSR      OPAMPINTEN     LL_OPAMP_SetInternalOutput
  * @param  OPAMPx OPAMP instance
  * @param  InternalOutput This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_INTERNAL_OUPUT_DISABLED
  *         @arg @ref LL_OPAMP_INTERNAL_OUPUT_ENABLED
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetInternalOutput(OPAMP_TypeDef *OPAMPx, uint32_t InternalOutput)
{
  MODIFY_REG(OPAMPx->CSR, OPAMP_CSR_OPAMPINTEN, InternalOutput);
}

/**
  * @brief  Get OPAMP internal output state.
  * @rmtoll CSR      OPAMPINTEN     LL_OPAMP_GetInternalOutput
  * @param  OPAMPx OPAMP instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_OPAMP_INTERNAL_OUPUT_DISABLED
  *         @arg @ref LL_OPAMP_INTERNAL_OUPUT_ENABLED
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetInternalOutput(OPAMP_TypeDef *OPAMPx)
{
  return READ_BIT(OPAMPx->CSR, OPAMP_CSR_OPAMPINTEN);
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
  *         @arg @ref LL_OPAMP_TRIMMING_NMOS            (1)
  *         @arg @ref LL_OPAMP_TRIMMING_PMOS            (1)
  *         @arg @ref LL_OPAMP_TRIMMING_NMOS_VREF_50PC_VDDA
  *         @arg @ref LL_OPAMP_TRIMMING_PMOS_VREF_3_3PC_VDDA
  *
  *         (1) Default parameters to be used for calibration
  *             using two trimming steps (one with each transistors differential
  *             pair NMOS and PMOS)
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
  *         @arg @ref LL_OPAMP_TRIMMING_NMOS            (1)
  *         @arg @ref LL_OPAMP_TRIMMING_PMOS            (1)
  *         @arg @ref LL_OPAMP_TRIMMING_NMOS_VREF_50PC_VDDA
  *         @arg @ref LL_OPAMP_TRIMMING_PMOS_VREF_3_3PC_VDDA
  *
  *         (1) Default parameters to be used for calibration
  *             using two trimming steps (one with each transistors differential
  *             pair NMOS and PMOS)
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetCalibrationSelection(OPAMP_TypeDef *OPAMPx)
{
  register uint32_t CalibrationSelection = (uint32_t)(READ_BIT(OPAMPx->CSR, OPAMP_CSR_CALSEL));

  return (CalibrationSelection |
          (((CalibrationSelection & OPAMP_CSR_CALSEL_1) == 0UL) ? OPAMP_CSR_TRIMOFFSETP : OPAMP_CSR_TRIMOFFSETN));
}

/**
  * @brief  Get OPAMP calibration result of toggling output.
  * @note   This functions returns:
  *         0 if OPAMP calibration output is reset
  *         1 if OPAMP calibration output is set
  * @rmtoll CSR      OUTCAL         LL_OPAMP_IsCalibrationOutputSet
  * @param  OPAMPx OPAMP instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_OPAMP_IsCalibrationOutputSet(OPAMP_TypeDef *OPAMPx)
{
  return ((READ_BIT(OPAMPx->CSR, OPAMP_CSR_OUTCAL) == OPAMP_CSR_OUTCAL) ? 1UL : 0UL);
}

/**
  * @brief  Set OPAMP trimming factor for the selected transistors
  *         differential pair NMOS or PMOS, corresponding to the selected
  *         power mode.
  * @rmtoll CSR      TRIMOFFSETN    LL_OPAMP_SetTrimmingValue\n
  *         CSR      TRIMOFFSETP    LL_OPAMP_SetTrimmingValue
  * @param  OPAMPx OPAMP instance
  * @param  TransistorsDiffPair This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_TRIMMING_NMOS
  *         @arg @ref LL_OPAMP_TRIMMING_PMOS
  * @param  TrimmingValue 0x00...0x1F
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_SetTrimmingValue(OPAMP_TypeDef *OPAMPx, uint32_t TransistorsDiffPair,
                                               uint32_t TrimmingValue)
{
  MODIFY_REG(OPAMPx->CSR,
             (TransistorsDiffPair & OPAMP_TRIMMING_VALUE_MASK),
             TrimmingValue << ((TransistorsDiffPair == LL_OPAMP_TRIMMING_NMOS) ? OPAMP_CSR_TRIMOFFSETN_Pos : OPAMP_CSR_TRIMOFFSETP_Pos));
}

/**
  * @brief  Get OPAMP trimming factor for the selected transistors
  *         differential pair NMOS or PMOS, corresponding to the selected
  *         power mode.
  * @rmtoll CSR      TRIMOFFSETN    LL_OPAMP_GetTrimmingValue\n
  *         CSR      TRIMOFFSETP    LL_OPAMP_GetTrimmingValue
  * @param  OPAMPx OPAMP instance
  * @param  TransistorsDiffPair This parameter can be one of the following values:
  *         @arg @ref LL_OPAMP_TRIMMING_NMOS
  *         @arg @ref LL_OPAMP_TRIMMING_PMOS
  * @retval 0x0...0x1F
  */
__STATIC_INLINE uint32_t LL_OPAMP_GetTrimmingValue(OPAMP_TypeDef *OPAMPx, uint32_t TransistorsDiffPair)
{
  return (uint32_t)(READ_BIT(OPAMPx->CSR, (TransistorsDiffPair & OPAMP_TRIMMING_VALUE_MASK))
                    >> ((TransistorsDiffPair == LL_OPAMP_TRIMMING_NMOS) ? OPAMP_CSR_TRIMOFFSETN_Pos : OPAMP_CSR_TRIMOFFSETP_Pos));
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
  *         to fullfill wake up time specification.
  *         Refer to device datasheet, parameter "tWAKEUP".
  * @rmtoll CSR      OPAMPXEN       LL_OPAMP_Enable
  * @param  OPAMPx OPAMP instance
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_Enable(OPAMP_TypeDef *OPAMPx)
{
  SET_BIT(OPAMPx->CSR, OPAMP_CSR_OPAMPxEN);
}

/**
  * @brief  Disable OPAMP instance.
  * @rmtoll CSR      OPAMPXEN       LL_OPAMP_Disable
  * @param  OPAMPx OPAMP instance
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_Disable(OPAMP_TypeDef *OPAMPx)
{
  CLEAR_BIT(OPAMPx->CSR, OPAMP_CSR_OPAMPxEN);
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
  return ((READ_BIT(OPAMPx->CSR, OPAMP_CSR_OPAMPxEN) == (OPAMP_CSR_OPAMPxEN)) ? 1UL : 0UL);
}

/**
  * @brief  Lock OPAMP instance.
  * @note   Once locked, OPAMP configuration can be accessed in read-only.
  * @note   The only way to unlock the OPAMP is a device hardware reset.
  * @rmtoll CSR      LOCK           LL_OPAMP_Lock
  * @param  OPAMPx OPAMP instance
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_Lock(OPAMP_TypeDef *OPAMPx)
{
  SET_BIT(OPAMPx->CSR, OPAMP_CSR_LOCK);
}

/**
  * @brief  Get OPAMP lock state
  *         (0: OPAMP is unlocked, 1: OPAMP is locked).
  * @note   Once locked, OPAMP configuration can be accessed in read-only.
  * @note   The only way to unlock the OPAMP is a device hardware reset.
  * @rmtoll CSR      LOCK           LL_OPAMP_IsLocked
  * @param  OPAMPx OPAMP instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_OPAMP_IsLocked(OPAMP_TypeDef *OPAMPx)
{
  return ((READ_BIT(OPAMPx->CSR, OPAMP_CSR_LOCK) == (OPAMP_CSR_LOCK)) ? 1UL : 0UL);
}

/**
  * @brief  Lock OPAMP instance timer controlled mux
  * @note   Once locked, OPAMP timer controlled mux configuration can be accessed in read-only.
  * @note   The only way to unlock the OPAMP timer controlled mux is a device hardware reset.
  * @rmtoll TCMR     LOCK           LL_OPAMP_LockTimerMux
  * @param  OPAMPx OPAMP instance
  * @retval None
  */
__STATIC_INLINE void LL_OPAMP_LockTimerMux(OPAMP_TypeDef *OPAMPx)
{
  SET_BIT(OPAMPx->TCMR, OPAMP_TCMR_LOCK);
}

/**
  * @brief  Get OPAMP timer controlled mux lock state
  *         (0: OPAMP timer controlled mux is unlocked, 1: OPAMP timer controlled mux is locked).
  * @note   Once locked, OPAMP timer controlled mux configuration can be accessed in read-only.
  * @note   The only way to unlock the OPAMP timer controlled mux is a device hardware reset.
  * @rmtoll TCMR     LOCK           LL_OPAMP_IsTimerMuxLocked
  * @param  OPAMPx OPAMP instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_OPAMP_IsTimerMuxLocked(OPAMP_TypeDef *OPAMPx)
{
  return ((READ_BIT(OPAMPx->TCMR, OPAMP_TCMR_LOCK) == (OPAMP_TCMR_LOCK)) ? 1UL : 0UL);
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

#endif /* OPAMP1 || OPAMP2 || OPAMP3 || OPAMP4 || OPAMP5 || OPAMP6 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32G4xx_LL_OPAMP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
