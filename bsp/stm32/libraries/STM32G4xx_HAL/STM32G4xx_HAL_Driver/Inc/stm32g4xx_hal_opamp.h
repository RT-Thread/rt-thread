/**
  ******************************************************************************
  * @file    stm32g4xx_hal_opamp.h
  * @author  MCD Application Team
  * @brief   Header file of OPAMP HAL module.
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
#ifndef STM32G4xx_HAL_OPAMP_H
#define STM32G4xx_HAL_OPAMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal_def.h"

/** @addtogroup STM32G4xx_HAL_Driver
  * @{
  */

/** @addtogroup OPAMP
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup OPAMP_Exported_Types OPAMP Exported Types
  * @{
  */

/**
  * @brief  OPAMP Init structure definition
  */

typedef struct
{
  uint32_t PowerMode;                   /*!< Specifies the power mode Normal or High Speed.
                                             This parameter must be a value of @ref OPAMP_PowerMode */

  uint32_t Mode;                        /*!< Specifies the OPAMP mode
                                             This parameter must be a value of @ref OPAMP_Mode
                                             mode is either Standalone, Follower or PGA */

  uint32_t InvertingInput;              /*!< Specifies the inverting input in Standalone & Pga modes
                                               - In Standalone mode:   i.e when mode is OPAMP_STANDALONE_MODE
                                                 This parameter must be a value of @ref OPAMP_InvertingInput
                                                 InvertingInput is either VINM0 or VINM1
                                               - In PGA mode:          i.e when mode is OPAMP_PGA_MODE
                                                 & in Follower mode    i.e when mode is OPAMP_FOLLOWER_MODE
                                                 This parameter is Not Applicable */

  uint32_t NonInvertingInput;           /*!< Specifies the non inverting input of the opamp:
                                             This parameter must be a value of @ref OPAMP_NonInvertingInput
                                             NonInvertingInput is either VINP0, VINP1, VINP2 or VINP3 */

  FunctionalState InternalOutput;       /*!< Specifies the configuration of the internal output from OPAMP to ADC.
                                             This parameter can be ENABLE or DISABLE
                                             Note: When this output is enabled, regular output to I/O is disabled */

  uint32_t TimerControlledMuxmode;      /*!< Specifies if the Timer controlled Mux mode is enabled or disabled
                                             This parameter must be a single value of @ref OPAMP_TimerControlledMuxmode
                                             or a combination of them to build a more complex switch scheme by
                                             using different timers */

  uint32_t InvertingInputSecondary;     /*!< Specifies the inverting input (secondary) of the opamp when
                                             TimerControlledMuxmode is enabled
                                             i.e. when TimerControlledMuxmode is OPAMP_TIMERCONTROLLEDMUXMODE_ENABLE
                                               - In Standalone mode:   i.e when mode is OPAMP_STANDALONE_MODE
                                                 This parameter must be a value of @ref OPAMP_InvertingInputSecondary
                                                 InvertingInputSecondary is either VINM0 or VINM1
                                               - In PGA mode:          i.e when mode is OPAMP_PGA_MODE
                                                 & in Follower mode    i.e when mode is OPAMP_FOLLOWER_MODE
                                                 This parameter must be a value of @ref OPAMP_InvertingInputSecondary
                                                 and is used to choose secondary mode (PGA or follower) */

  uint32_t NonInvertingInputSecondary;  /*!< Specifies the non inverting input (secondary) of the opamp when
                                             TimerControlledMuxmode is enabled
                                             i.e. when TimerControlledMuxmode is OPAMP_TIMERCONTROLLEDMUXMODE_ENABLE
                                             This parameter must be a value of @ref OPAMP_NonInvertingInputSecondary
                                             NonInvertingInput is either VINP0, VINP1, VINP2 or VINP3 */

  uint32_t PgaConnect;                  /*!< Specifies the inverting pin in PGA mode
                                             i.e. when mode is OPAMP_PGA_MODE
                                             This parameter must be a value of @ref OPAMP_PgaConnect
                                             Either: not connected, connected to VINM0
                                             In this last case, VINM0 can then be used to input signal (negative gain case
                                             with or without bias on VINPx) or to input bias (positive gain case with bias) */

  uint32_t PgaGain;                     /*!< Specifies the gain in PGA mode
                                             i.e. when mode is OPAMP_PGA_MODE.
                                             This parameter must be a value of @ref OPAMP_PgaGain
                                             (2, 4, 8, 16, 32 or 64) for positive gain & (-1, -3 ,-7, -15, -31 or -63) for negative gain */

  uint32_t UserTrimming;                /*!< Specifies the trimming mode
                                             This parameter must be a value of @ref OPAMP_UserTrimming
                                             UserTrimming is either factory or user trimming */

  uint32_t TrimmingValueP;              /*!< Specifies the offset trimming value (PMOS)
                                             i.e. when UserTrimming is OPAMP_TRIMMING_USER.
                                             This parameter must be a number between Min_Data = 1 and Max_Data = 31 */

  uint32_t TrimmingValueN;              /*!< Specifies the offset trimming value (NMOS)
                                             i.e. when UserTrimming is OPAMP_TRIMMING_USER.
                                             This parameter must be a number between Min_Data = 1 and Max_Data = 31 */

} OPAMP_InitTypeDef;

/**
  * @brief  HAL State structures definition
  */

typedef enum
{
  HAL_OPAMP_STATE_RESET               = 0x00000000UL, /*!< OPAMP is not yet Initialized          */

  HAL_OPAMP_STATE_READY               = 0x00000001UL, /*!< OPAMP is initialized and ready for use */
  HAL_OPAMP_STATE_CALIBBUSY           = 0x00000002UL, /*!< OPAMP is enabled in auto calibration mode */

  HAL_OPAMP_STATE_BUSY                = 0x00000004UL, /*!< OPAMP is enabled and running in normal mode */
  HAL_OPAMP_STATE_BUSYLOCKED          = 0x00000005UL, /*!< OPAMP control register is locked
                                                         only system reset allows reconfiguring the opamp. */

} HAL_OPAMP_StateTypeDef;

/**
  * @brief OPAMP Handle Structure definition
  */
#if (USE_HAL_OPAMP_REGISTER_CALLBACKS == 1)
typedef struct __OPAMP_HandleTypeDef
#else
typedef struct
#endif
{
  OPAMP_TypeDef       *Instance;                    /*!< OPAMP instance's registers base address   */
  OPAMP_InitTypeDef   Init;                         /*!< OPAMP required parameters */
  HAL_StatusTypeDef Status;                         /*!< OPAMP peripheral status   */
  HAL_LockTypeDef   Lock;                           /*!< Locking object          */
  __IO HAL_OPAMP_StateTypeDef  State;               /*!< OPAMP communication state */

#if (USE_HAL_OPAMP_REGISTER_CALLBACKS == 1)
  void (* MspInitCallback)(struct __OPAMP_HandleTypeDef *hopamp);
  void (* MspDeInitCallback)(struct __OPAMP_HandleTypeDef *hopamp);
#endif /* USE_HAL_OPAMP_REGISTER_CALLBACKS */

} OPAMP_HandleTypeDef;

/**
  * @brief OPAMP_TrimmingValueTypeDef definition
  */

typedef  uint32_t OPAMP_TrimmingValueTypeDef;
/**
  * @}
  */

#if (USE_HAL_OPAMP_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL OPAMP Callback ID enumeration definition
  */
typedef enum
{
  HAL_OPAMP_MSPINIT_CB_ID                     = 0x01UL,  /*!< OPAMP MspInit Callback ID           */
  HAL_OPAMP_MSPDEINIT_CB_ID                   = 0x02UL,  /*!< OPAMP MspDeInit Callback ID         */
  HAL_OPAMP_ALL_CB_ID                          = 0x03UL   /*!< OPAMP All ID                        */
} HAL_OPAMP_CallbackIDTypeDef;

/**
  * @brief  HAL OPAMP Callback pointer definition
  */
typedef void (*pOPAMP_CallbackTypeDef)(OPAMP_HandleTypeDef *hopamp);
#endif /* USE_HAL_OPAMP_REGISTER_CALLBACKS */


/* Exported constants --------------------------------------------------------*/
/** @defgroup OPAMP_Exported_Constants OPAMP Exported Constants
  * @{
  */
/** @defgroup OPAMP_Mode OPAMP Mode
  * @{
  */
#define OPAMP_STANDALONE_MODE            (0x00000000UL)         /*!< standalone mode */
#define OPAMP_PGA_MODE                   OPAMP_CSR_VMSEL_1      /*!< PGA mode */
#define OPAMP_FOLLOWER_MODE              OPAMP_CSR_VMSEL        /*!< follower mode */
/**
  * @}
  */

/** @defgroup OPAMP_NonInvertingInput OPAMP Non Inverting Input
  * @{
  */
#define OPAMP_NONINVERTINGINPUT_IO0         (0x00000000UL)        /*!< Non inverting input connected to I/O VINP0
                                                                       (PA1  for OPAMP1, PA7  for OPAMP2, PB0  for OPAMP3, PB13 for OPAMP4, PB14 for OPAMP5, PB12 for OPAMP6)
                                                                       Note: On this STM32 series, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
#define OPAMP_NONINVERTINGINPUT_IO1         OPAMP_CSR_VPSEL_0     /*!< Non inverting input connected to I/O VINP1
                                                                       (PA3  for OPAMP1, PB14 for OPAMP2, PB13 for OPAMP3, PD11 for OPAMP4, PD12 for OPAMP5, PD9  for OPAMP6)
                                                                       Note: On this STM32 series, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
#define OPAMP_NONINVERTINGINPUT_IO2         OPAMP_CSR_VPSEL_1     /*!< Non inverting input connected to I/O VINP2
                                                                       (PA7  for OPAMP1, PB0  for OPAMP2, PA1  for OPAMP3, PB11 for OPAMP4, PC3  for OPAMP5, PB13 for OPAMP6)
                                                                       Note: On this STM32 series, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
#define OPAMP_NONINVERTINGINPUT_IO3         OPAMP_CSR_VPSEL       /*!< Non inverting input connected to I/O VINP3
                                                                       (PD14 for OPAMP2) */
#define OPAMP_NONINVERTINGINPUT_DAC         OPAMP_CSR_VPSEL       /*!< Non inverting input connected internally to DAC channel
                                                                       (DAC3_CH1 for OPAMP1, DAC3_CH2  for OPAMP3, DAC4_CH1 for OPAMP4, DAC4_CH2 for OPAMP5, DAC3_CH1 for OPAMP6)
                                                                       Note: On this STM32 series, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
/**
  * @}
  */

/** @defgroup OPAMP_InvertingInput OPAMP Inverting Input
  * @{
  */
#define OPAMP_INVERTINGINPUT_IO0       (0x00000000UL)              /*!< Inverting input connected to I/O VINM0
                                                                       (PA3  for OPAMP1, PA5  for OPAMP2, PB2  for OPAMP3, PB10 for OPAMP4, PB15 for OPAMP5, PA1  for OPAMP6)
                                                                       Note: On this STM32 series, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
#define OPAMP_INVERTINGINPUT_IO1       OPAMP_CSR_VMSEL_0           /*!< Inverting input connected to I/0 VINM1
                                                                       (PC5  for OPAMP1, PC5  for OPAMP2, PB10 for OPAMP3, PB8  for OPAMP4, PA3  for OPAMP5, PB1  for OPAMP6)
                                                                       Note: On this STM32 series, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
/**
  * @}
  */

/** @defgroup OPAMP_TimerControlledMuxmode OPAMP Timer Controlled Mux mode
  * @note The switch can be controlled either by a single timer or a combination of them,
  *       in this case application has to 'ORed' the values below
  *       ex OPAMP_TIMERCONTROLLEDMUXMODE_TIM1_CH6 | OPAMP_TIMERCONTROLLEDMUXMODE_TIM20_CH6
  * @{
  */
#define OPAMP_TIMERCONTROLLEDMUXMODE_DISABLE    (0x00000000UL)       /*!< Timer controlled Mux mode disabled */
#define OPAMP_TIMERCONTROLLEDMUXMODE_TIM1_CH6   OPAMP_TCMR_T1CMEN    /*!< Timer controlled Mux mode enabled using TIM1 OC6 */
#define OPAMP_TIMERCONTROLLEDMUXMODE_TIM8_CH6   OPAMP_TCMR_T8CMEN    /*!< Timer controlled Mux mode enabled using TIM8 OC6 */
#if defined(TIM20)
#define OPAMP_TIMERCONTROLLEDMUXMODE_TIM20_CH6  OPAMP_TCMR_T20CMEN   /*!< Timer controlled Mux mode enabled using TIM20 OC6
                                                                          Note: On this STM32 series, TIM20 is not available on all devices. Refer to device datasheet for more details */
#endif
/**
  * @}
  */

/** @defgroup OPAMP_NonInvertingInputSecondary OPAMP Non Inverting Input Secondary
  * @{
  */
#define OPAMP_SEC_NONINVERTINGINPUT_IO0         (0x00000000UL)        /*!< Secondary non inverting input connected to I/O VINP0
                                                                           (PA1  for OPAMP1, PA7  for OPAMP2, PB0  for OPAMP3, PB13 for OPAMP4, PB14 for OPAMP5, PB12 for OPAMP6)
                                                                           Note: On this STM32 series, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
#define OPAMP_SEC_NONINVERTINGINPUT_IO1         OPAMP_TCMR_VPSSEL_0   /*!< Secondary non inverting input connected to I/O VINP1
                                                                           (PA3  for OPAMP1, PB14 for OPAMP2, PB13 for OPAMP3, PD11 for OPAMP4, PD12 for OPAMP5, PD9  for OPAMP6)
                                                                           Note: On this STM32 series, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
#define OPAMP_SEC_NONINVERTINGINPUT_IO2         OPAMP_TCMR_VPSSEL_1   /*!< Secondary non inverting input connected to I/O VINP2
                                                                           (PA7  for OPAMP1, PB0  for OPAMP2, PA1  for OPAMP3, PB11 for OPAMP4, PC3  for OPAMP5, PB13 for OPAMP6)
                                                                           Note: On this STM32 series, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
#define OPAMP_SEC_NONINVERTINGINPUT_IO3         OPAMP_TCMR_VPSSEL     /*!< Secondary non inverting input connected to I/O VINP3
                                                                           (PD14 for OPAMP2) */
#define OPAMP_SEC_NONINVERTINGINPUT_DAC         OPAMP_TCMR_VPSSEL     /*!< Secondary non inverting input connected internally to DAC channel
                                                                           (DAC3_CH1 for OPAMP1, DAC3_CH2  for OPAMP3, DAC4_CH1 for OPAMP4, DAC4_CH2 for OPAMP5, DAC3_CH1 for OPAMP6)
                                                                           Note: On this STM32 series, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
/**
  * @}
  */

/** @defgroup OPAMP_InvertingInputSecondary OPAMP Inverting Input Secondary
  * @{
  */
#define OPAMP_SEC_INVERTINGINPUT_IO0       (0x00000000UL)              /*!< OPAMP secondary mode is standalone mode - Only applicable if @ref OPAMP_STANDALONE_MODE
                                                                            has been configured by call to @ref HAL_OPAMP_Init().
                                                                            Secondary inverting input connected to I/O VINM0
                                                                            (PA3  for OPAMP1, PA5  for OPAMP2, PB2  for OPAMP3, PB10 for OPAMP4, PB15 for OPAMP5, PA1  for OPAMP6)
                                                                            Note: On this STM32 series, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
#define OPAMP_SEC_INVERTINGINPUT_IO1       OPAMP_TCMR_VMSSEL           /*!< OPAMP secondary mode is standalone mode - Only applicable if @ref OPAMP_STANDALONE_MODE
                                                                            has been configured by call to @ref HAL_OPAMP_Init().
                                                                            Secondary inverting input connected to I/0 VINM1
                                                                            (PC5  for OPAMP1, PC5  for OPAMP2, PB10 for OPAMP3, PB8  for OPAMP4, PA3  for OPAMP5, PB1  for OPAMP6)
                                                                            Note: On this STM32 series, all OPAMPx are not available on all devices. Refer to device datasheet for more details */
#define OPAMP_SEC_INVERTINGINPUT_PGA       (0x00000000UL)              /*!< OPAMP secondary mode is PGA mode - Only applicable if configured mode through call to @ref HAL_OPAMP_Init()
                                                                           is @ref OPAMP_PGA_MODE or @ref OPAMP_FOLLOWER_MODE.
                                                                           OPAMP secondary inverting input is:
                                                                             - Not connected if configured mode is @ref OPAMP_FOLLOWER_MODE
                                                                             - Not connected if configured mode is @ref OPAMP_PGA_MODE and PGA connect mode is @ref OPAMP_PGA_CONNECT_INVERTINGINPUT_NO
                                                                             - Connected to VINM0 and possibly VINM1 if any of the other modes as been configured
                                                                           (see @ref OPAMP_PgaConnect description for more details on PGA connection modes) */
#define OPAMP_SEC_INVERTINGINPUT_FOLLOWER  OPAMP_TCMR_VMSSEL           /*!< OPAMP secondary mode is Follower mode - Only applicable if configured mode through call to @ref HAL_OPAMP_Init()
                                                                           is @ref OPAMP_PGA_MODE or @ref OPAMP_FOLLOWER_MODE.
                                                                           OPAMP secondary inverting input is not connected. */
/**
  * @}
  */

/** @defgroup OPAMP_PgaConnect OPAMP Pga Connect
  * @{
  */
#define OPAMP_PGA_CONNECT_INVERTINGINPUT_NO               (0x00000000UL)                            /*!< In PGA mode, the inverting input is not connected */
#define OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0              OPAMP_CSR_PGGAIN_4                        /*!< In PGA mode, the inverting input is connected to VINM0 for filtering */
#define OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS         OPAMP_CSR_PGGAIN_3                        /*!< In PGA mode, the inverting input is connected to VINM0
                                                                                                      - Input signal on VINM0, bias on VINPx: negative gain
                                                                                                      - Bias on VINM0, input signal on VINPx: positive gain */
#define OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_IO1_BIAS     (OPAMP_CSR_PGGAIN_4|OPAMP_CSR_PGGAIN_3)   /*!< In PGA mode, the inverting input is connected to VINM0
                                                                                                      - Input signal on VINM0, bias on VINPx: negative gain
                                                                                                      - Bias on VINM0, input signal on VINPx: positive gain
                                                                                                      And VINM1 is connected too for filtering */
/**
  * @}
  */

/** @defgroup OPAMP_PgaGain OPAMP Pga Gain
  * @note Gain sign:
  *         - is positive if the @ref OPAMP_PgaConnect configuration is
  *           @ref OPAMP_PGA_CONNECT_INVERTINGINPUT_NO or OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0
  *         - may be positive or negative if the @ref OPAMP_PgaConnect configuration is
  *           @ref OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS or OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_IO1_BIAS
  *       see @ref OPAMP_PgaConnect for more details
  * @{
  */
#define OPAMP_PGA_GAIN_2_OR_MINUS_1          (0x00000000UL)                                                      /*!< PGA gain could be 2  or -1  */
#define OPAMP_PGA_GAIN_4_OR_MINUS_3          (                                          OPAMP_CSR_PGGAIN_0)      /*!< PGA gain could be 4  or -3  */
#define OPAMP_PGA_GAIN_8_OR_MINUS_7          (                     OPAMP_CSR_PGGAIN_1                     )      /*!< PGA gain could be 8  or -7  */
#define OPAMP_PGA_GAIN_16_OR_MINUS_15        (                     OPAMP_CSR_PGGAIN_1 | OPAMP_CSR_PGGAIN_0)      /*!< PGA gain could be 16 or -15 */
#define OPAMP_PGA_GAIN_32_OR_MINUS_31        (OPAMP_CSR_PGGAIN_2                                          )      /*!< PGA gain could be 32 or -31 */
#define OPAMP_PGA_GAIN_64_OR_MINUS_63        (OPAMP_CSR_PGGAIN_2 |                      OPAMP_CSR_PGGAIN_0)      /*!< PGA gain could be 64 or -63 */
/**
  * @}
  */

/** @defgroup OPAMP_PowerMode OPAMP PowerMode
  * @{
  */
#define OPAMP_POWERMODE_NORMALSPEED   (0x00000000UL)         /*!< Output in normal mode */
#define OPAMP_POWERMODE_HIGHSPEED     OPAMP_CSR_HIGHSPEEDEN  /*!< Output in highspeed mode */
/**
  * @}
  */

/** @defgroup OPAMP_UserTrimming OPAMP User Trimming
  * @{
  */
#define OPAMP_TRIMMING_FACTORY        (0x00000000UL)                       /*!< Factory trimming */
#define OPAMP_TRIMMING_USER           OPAMP_CSR_USERTRIM                   /*!< User trimming */
/**
  * @}
  */

/** @defgroup OPAMP_FactoryTrimming OPAMP Factory Trimming
  * @{
  */
#define OPAMP_FACTORYTRIMMING_DUMMY    (0xFFFFFFFFUL)                         /*!< Dummy trimming value */

#define OPAMP_FACTORYTRIMMING_N        (0x00000000UL)                         /*!< Offset trimming N */
#define OPAMP_FACTORYTRIMMING_P        (0x00000001UL)                         /*!< Offset trimming P */
/**
  * @}
  */

/** @defgroup OPAMP_VREF OPAMP VREF
  * @{
  */
#define OPAMP_VREF_3VDDA                    (0x00000000UL)          /*!< OPAMP Vref = 3.3% VDDA */
#define OPAMP_VREF_10VDDA                    OPAMP_CSR_CALSEL_0     /*!< OPAMP Vref = 10% VDDA  */
#define OPAMP_VREF_50VDDA                    OPAMP_CSR_CALSEL_1     /*!< OPAMP Vref = 50% VDDA  */
#define OPAMP_VREF_90VDDA                    OPAMP_CSR_CALSEL       /*!< OPAMP Vref = 90% VDDA  */
/**
  * @}
  */

/**
  * @}
  */


/* Private constants ---------------------------------------------------------*/
/** @defgroup OPAMP_Private_Constants OPAMP Private Constants
  * @brief   OPAMP Private constants and defines
  * @{
  */
/** @defgroup OPAMP_Input OPAMP Input
  * @{
  */
#define OPAMP_INPUT_INVERTING                 ( 24UL) /*!< Inverting input */
#define OPAMP_INPUT_NONINVERTING              ( 19UL) /*!< Non inverting input */

#define IS_OPAMP_INPUT(INPUT) (((INPUT) == OPAMP_INPUT_INVERTING) || \
                               ((INPUT) == OPAMP_INPUT_NONINVERTING))
/**
  * @}
  */

/**
  * @}
  */


/* Private macro -------------------------------------------------------------*/

/** @defgroup OPAMP_Private_Macros OPAMP Private Macros
  * @{
  */

#define IS_OPAMP_FUNCTIONAL_NORMALMODE(INPUT) (((INPUT) == OPAMP_STANDALONE_MODE) || \
                                               ((INPUT) == OPAMP_PGA_MODE) || \
                                               ((INPUT) == OPAMP_FOLLOWER_MODE))

#define IS_OPAMP_NONINVERTING_INPUT(INPUT) (((INPUT) == OPAMP_NONINVERTINGINPUT_IO0) || \
                                            ((INPUT) == OPAMP_NONINVERTINGINPUT_IO1) || \
                                            ((INPUT) == OPAMP_NONINVERTINGINPUT_IO2) || \
                                            ((INPUT) == OPAMP_NONINVERTINGINPUT_IO3) || \
                                            ((INPUT) == OPAMP_NONINVERTINGINPUT_DAC))

#define IS_OPAMP_INVERTING_INPUT(INPUT) (((INPUT) == OPAMP_INVERTINGINPUT_IO0) || \
                                         ((INPUT) == OPAMP_INVERTINGINPUT_IO1))

#if defined(TIM20)
#define IS_OPAMP_TIMERCONTROLLED_MUXMODE(MUXMODE)  \
  ((MUXMODE) <= (OPAMP_TIMERCONTROLLEDMUXMODE_TIM1_CH6 |    \
                 OPAMP_TIMERCONTROLLEDMUXMODE_TIM8_CH6 |    \
                 OPAMP_TIMERCONTROLLEDMUXMODE_TIM20_CH6))
#else
#define IS_OPAMP_TIMERCONTROLLED_MUXMODE(MUXMODE)  \
  ((MUXMODE) <= (OPAMP_TIMERCONTROLLEDMUXMODE_TIM1_CH6 |    \
                 OPAMP_TIMERCONTROLLEDMUXMODE_TIM8_CH6))
#endif

#define IS_OPAMP_SEC_NONINVERTING_INPUT(INPUT) (((INPUT) == OPAMP_SEC_NONINVERTINGINPUT_IO0) || \
                                                ((INPUT) == OPAMP_SEC_NONINVERTINGINPUT_IO1) || \
                                                ((INPUT) == OPAMP_SEC_NONINVERTINGINPUT_IO2) || \
                                                ((INPUT) == OPAMP_SEC_NONINVERTINGINPUT_IO3) || \
                                                ((INPUT) == OPAMP_SEC_NONINVERTINGINPUT_DAC))

#define IS_OPAMP_SEC_INVERTING_INPUT(INPUT) (((INPUT) == OPAMP_SEC_INVERTINGINPUT_IO0) || \
                                             ((INPUT) == OPAMP_SEC_INVERTINGINPUT_IO1) || \
                                             ((INPUT) == OPAMP_SEC_INVERTINGINPUT_PGA) || \
                                             ((INPUT) == OPAMP_SEC_INVERTINGINPUT_FOLLOWER))

#define IS_OPAMP_PGACONNECT(CONNECT) (((CONNECT) == OPAMP_PGA_CONNECT_INVERTINGINPUT_NO)            || \
                                      ((CONNECT) == OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0)           || \
                                      ((CONNECT) == OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS)      || \
                                      ((CONNECT) == OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_IO1_BIAS))

#define IS_OPAMP_PGA_GAIN(GAIN) (((GAIN) == OPAMP_PGA_GAIN_2_OR_MINUS_1)   || \
                                 ((GAIN) == OPAMP_PGA_GAIN_4_OR_MINUS_3)   || \
                                 ((GAIN) == OPAMP_PGA_GAIN_8_OR_MINUS_7)   || \
                                 ((GAIN) == OPAMP_PGA_GAIN_16_OR_MINUS_15) || \
                                 ((GAIN) == OPAMP_PGA_GAIN_32_OR_MINUS_31) || \
                                 ((GAIN) == OPAMP_PGA_GAIN_64_OR_MINUS_63))

#define IS_OPAMP_POWERMODE(POWERMODE) (((POWERMODE) == OPAMP_POWERMODE_NORMAL) || \
                                       ((POWERMODE) == OPAMP_POWERMODE_HIGHSPEED) )

#define IS_OPAMP_TRIMMING(TRIMMING) (((TRIMMING) == OPAMP_TRIMMING_FACTORY) || \
                                     ((TRIMMING) == OPAMP_TRIMMING_USER))

#define IS_OPAMP_FACTORYTRIMMING(TRIMMING) (((TRIMMING) == OPAMP_FACTORYTRIMMING_N) || \
                                            ((TRIMMING) == OPAMP_FACTORYTRIMMING_P))

#define IS_OPAMP_TRIMMINGVALUE(TRIMMINGVALUE) ((TRIMMINGVALUE) <= 0x1FUL)

#define IS_OPAMP_VREF(VREF) (((VREF) == OPAMP_VREF_3VDDA)  || \
                             ((VREF) == OPAMP_VREF_10VDDA) || \
                             ((VREF) == OPAMP_VREF_50VDDA) || \
                             ((VREF) == OPAMP_VREF_90VDDA))
/**
  * @}
  */


/* Exported macros -----------------------------------------------------------*/
/** @defgroup OPAMP_Exported_Macros OPAMP Exported Macros
  * @{
  */

/** @brief Reset OPAMP handle state
  * @param  __HANDLE__ OPAMP handle.
  * @retval None
  */
#define __HAL_OPAMP_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_OPAMP_STATE_RESET)

/**
  * @}
  */

/* Include OPAMP HAL Extended module */
#include "stm32g4xx_hal_opamp_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @defgroup OPAMP_Exported_Functions OPAMP Exported Functions
  * @{
  */

/** @defgroup OPAMP_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */

/* Initialization/de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_OPAMP_Init(OPAMP_HandleTypeDef *hopamp);
HAL_StatusTypeDef HAL_OPAMP_DeInit(OPAMP_HandleTypeDef *hopamp);
void HAL_OPAMP_MspInit(OPAMP_HandleTypeDef *hopamp);
void HAL_OPAMP_MspDeInit(OPAMP_HandleTypeDef *hopamp);
/**
  * @}
  */


/** @defgroup OPAMP_Exported_Functions_Group2 Input and Output operation functions
  * @{
  */

/* I/O operation functions  *****************************************************/
HAL_StatusTypeDef HAL_OPAMP_Start(OPAMP_HandleTypeDef *hopamp);
HAL_StatusTypeDef HAL_OPAMP_Stop(OPAMP_HandleTypeDef *hopamp);
HAL_StatusTypeDef HAL_OPAMP_SelfCalibrate(OPAMP_HandleTypeDef *hopamp);

/**
  * @}
  */

/** @defgroup OPAMP_Exported_Functions_Group3 Peripheral Control functions
  * @{
  */

/* Peripheral Control functions  ************************************************/
#if (USE_HAL_OPAMP_REGISTER_CALLBACKS == 1)
/* OPAMP callback registering/unregistering */
HAL_StatusTypeDef HAL_OPAMP_RegisterCallback(OPAMP_HandleTypeDef *hopamp, HAL_OPAMP_CallbackIDTypeDef CallbackId,
                                             pOPAMP_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_OPAMP_UnRegisterCallback(OPAMP_HandleTypeDef *hopamp, HAL_OPAMP_CallbackIDTypeDef CallbackId);
#endif /* USE_HAL_OPAMP_REGISTER_CALLBACKS */

HAL_StatusTypeDef HAL_OPAMP_Lock(OPAMP_HandleTypeDef *hopamp);
HAL_StatusTypeDef HAL_OPAMP_LockTimerMux(OPAMP_HandleTypeDef *hopamp);

/**
  * @}
  */

/** @defgroup OPAMP_Exported_Functions_Group4 Peripheral State functions
  * @{
  */

/* Peripheral State functions  **************************************************/
HAL_OPAMP_StateTypeDef HAL_OPAMP_GetState(OPAMP_HandleTypeDef *hopamp);
OPAMP_TrimmingValueTypeDef HAL_OPAMP_GetTrimOffset(OPAMP_HandleTypeDef *hopamp, uint32_t trimmingoffset);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /* STM32G4xx_HAL_OPAMP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
