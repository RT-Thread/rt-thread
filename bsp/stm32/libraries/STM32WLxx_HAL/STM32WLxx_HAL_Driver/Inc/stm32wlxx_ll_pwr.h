/**
  ******************************************************************************
  * @file    stm32wlxx_ll_pwr.h
  * @author  MCD Application Team
  * @brief   Header file of PWR LL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#ifndef __STM32WLxx_LL_PWR_H
#define __STM32WLxx_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx.h"

/** @addtogroup STM32WLxx_LL_Driver
  * @{
  */

#if defined(PWR)

/** @defgroup PWR_LL PWR
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup PWR_LL_Private_Constants PWR Private Constants
  * @{
  */
#define PWR_FLASH_POWER_MODE_UNLOCK_CODE  (0x0000C1B0UL)
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_LL_EC_CLEAR_FLAG Clear Flags Defines
  * @brief    Flags defines which can be used with LL_PWR_WriteReg function
  * @{
  */
#define LL_PWR_SCR_CWUF                    PWR_SCR_CWUF
#define LL_PWR_SCR_CWUF3                   PWR_SCR_CWUF3
#define LL_PWR_SCR_CWUF2                   PWR_SCR_CWUF2
#define LL_PWR_SCR_CWUF1                   PWR_SCR_CWUF1
#define LL_PWR_SCR_CWPVDF                  PWR_SCR_CWPVDF
#define LL_PWR_SCR_CWRFBUSYF               PWR_SCR_CWRFBUSYF
#define LL_PWR_SCR_CC2HF                   PWR_SCR_CC2HF
#define LL_PWR_EXTSCR_C2CSSF               PWR_EXTSCR_C2CSSF
#define LL_PWR_EXTSCR_C1CSSF               PWR_EXTSCR_C1CSSF
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_PWR_ReadReg function
  * @{
  */
#define LL_PWR_SR1_WUFI                    PWR_SR1_WUFI
#define LL_PWR_SR1_WUF3                    PWR_SR1_WUF3
#define LL_PWR_SR1_WUF2                    PWR_SR1_WUF2
#define LL_PWR_SR1_WUF1                    PWR_SR1_WUF1
#define LL_PWR_SR1_WPVDF                   PWR_SR1_WPVDF

#define LL_PWR_SR2_LDORDY                  PWR_SR2_LDORDY
#define LL_PWR_SR2_PVMO3                   PWR_SR2_PVMO3
#define LL_PWR_SR2_PVDO                    PWR_SR2_PVDO
#define LL_PWR_SR2_RFEOL                   PWR_SR2_RFEOLF
#define LL_PWR_SR2_VOSF                    PWR_SR2_VOSF
#define LL_PWR_SR2_REGLPF                  PWR_SR2_REGLPF
#define LL_PWR_SR2_REGLPS                  PWR_SR2_REGLPS
#define LL_PWR_SR2_REGMRS                  PWR_SR2_REGMRS

/* SMPS flags */
#define LL_PWR_SR2_SMPSRDY                 PWR_SR2_SMPSRDY

/* Radio flags */
#define LL_PWR_SR1_WRFBUSY                 PWR_SR1_WRFBUSYF   /* Radio busy flag for wake-up and interruption (triggered status: wake-up event or interruption occurred at least once. Can be cleared by software) */
#define LL_PWR_SR2_RFBUSYS                 PWR_SR2_RFBUSYS    /* Radio busy signal flag (current status) */
#define LL_PWR_SR2_RFBUSYMS                PWR_SR2_RFBUSYMS   /* Radio busy masked signal flag (current status) */

/* Multicore flags */
#define LL_PWR_EXTSCR_C1SBF                PWR_EXTSCR_C1SBF    /* System Standby flag for CPU1 */
#define LL_PWR_EXTSCR_C1STOP2F             PWR_EXTSCR_C1STOP2F /* System Stop 2 flag for CPU1 */
#define LL_PWR_EXTSCR_C1STOPF              PWR_EXTSCR_C1STOPF  /* System Stop 0 or stop 1 flag for CPU1 */
#define LL_PWR_EXTSCR_C1DS                 PWR_EXTSCR_C1DS     /* CPU1 deepsleep mode */
#if defined(DUAL_CORE)
#define LL_PWR_EXTSCR_C2SBF                PWR_EXTSCR_C2SBF    /* System Standby flag for CPU2 */
#define LL_PWR_EXTSCR_C2STOP2F             PWR_EXTSCR_C2STOP2F /* System Stop 2 flag for CPU2 */
#define LL_PWR_EXTSCR_C2STOPF              PWR_EXTSCR_C2STOPF  /* System Stop 0 or stop 1 flag for CPU2 */
#define LL_PWR_EXTSCR_C2DS                 PWR_EXTSCR_C2DS     /* CPU2 deepsleep mode */
#define LL_PWR_SR2_C2BOOTS                 PWR_SR2_C2BOOTS     /* CPU2 boot request source information flag */
#define LL_PWR_SR1_C2HF                    PWR_SR1_C2HF        /* CPU2 hold interrupt flag */
#endif
/**
  * @}
  */

/** @defgroup PWR_LL_EC_REGU_VOLTAGE REGU VOLTAGE
  * @{
  */
#define LL_PWR_REGU_VOLTAGE_SCALE1         (PWR_CR1_VOS_0) /* Regulator voltage output range 1 mode, typical output voltage at 1.2 V, system frequency up to 64 MHz. */
#define LL_PWR_REGU_VOLTAGE_SCALE2         (PWR_CR1_VOS_1) /* Regulator voltage output range 2 mode, typical output voltage at 1.0 V, system frequency up to 16 MHz. */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_MODE_PWR MODE PWR
  * @{
  */
#define LL_PWR_MODE_STOP0                  (0x000000000UL)
#define LL_PWR_MODE_STOP1                  (PWR_CR1_LPMS_0)
#define LL_PWR_MODE_STOP2                  (PWR_CR1_LPMS_1)
#define LL_PWR_MODE_STANDBY                (PWR_CR1_LPMS_1 | PWR_CR1_LPMS_0)
#define LL_PWR_MODE_SHUTDOWN               (PWR_CR1_LPMS_2 | PWR_CR1_LPMS_1 | PWR_CR1_LPMS_0)
/**
  * @}
  */

/** @defgroup PWR_LL_EC_FLASH_LPRUN_POWER_DOWN_MODE Flash power-down mode during low-power run mode
  * @{
  */
#define LL_PWR_FLASH_LPRUN_MODE_IDLE       (0x000000000UL)
#define LL_PWR_FLASH_LPRUN_MODE_POWER_DOWN (PWR_CR1_FPDR)
/**
  * @}
  */

/** @defgroup PWR_LL_EC_FLASH_SLEEP_POWER_DOWN_MODE Flash power-down mode during sleep mode
  * @{
  */
#define LL_PWR_FLASH_SLEEP_MODE_IDLE       (0x000000000UL)
#define LL_PWR_FLASH_SLEEP_MODE_POWER_DOWN (PWR_CR1_FPDS)
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PVM Peripheral voltage monitoring
  * @{
  */
#define LL_PWR_PVM_VDDA_1_62V              (PWR_CR2_PVME3)     /* Monitoring VDDA vs. 1.62V  */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PVDLEVEL PVDLEVEL
  * @{
  */
#define LL_PWR_PVDLEVEL_0                  (0x00000000UL)                                  /* VPVD0 around 2.0 V */
#define LL_PWR_PVDLEVEL_1                  (PWR_CR2_PLS_0)                                 /* VPVD1 around 2.2 V */
#define LL_PWR_PVDLEVEL_2                  (PWR_CR2_PLS_1)                                 /* VPVD2 around 2.4 V */
#define LL_PWR_PVDLEVEL_3                  (PWR_CR2_PLS_1 | PWR_CR2_PLS_0)                 /* VPVD3 around 2.5 V */
#define LL_PWR_PVDLEVEL_4                  (PWR_CR2_PLS_2)                                 /* VPVD4 around 2.6 V */
#define LL_PWR_PVDLEVEL_5                  (PWR_CR2_PLS_2 | PWR_CR2_PLS_0)                 /* VPVD5 around 2.8 V */
#define LL_PWR_PVDLEVEL_6                  (PWR_CR2_PLS_2 | PWR_CR2_PLS_1)                 /* VPVD6 around 2.9 V */
#define LL_PWR_PVDLEVEL_7                  (PWR_CR2_PLS_2 | PWR_CR2_PLS_1 | PWR_CR2_PLS_0) /* External input analog voltage (Compare internally to VREFINT) */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_EOL_OPERATING_MODES Monitoring of supply voltage for radio operating level (radio End Of Life)
  * @{
  */
#define LL_PWR_RADIO_EOL_DISABLE                  (0x00000000UL)    /*!< Monitoring of supply voltage for radio operating level (radio End Of Life) disable */
#define LL_PWR_RADIO_EOL_ENABLE                   (PWR_CR5_RFEOLEN) /*!< Monitoring of supply voltage for radio operating level (radio End Of Life) enable */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP WAKEUP
  * @{
  */
#define LL_PWR_WAKEUP_PIN1                 (PWR_CR3_EWUP1)
#define LL_PWR_WAKEUP_PIN2                 (PWR_CR3_EWUP2)
#define LL_PWR_WAKEUP_PIN3                 (PWR_CR3_EWUP3)
/**
  * @}
  */

/** @defgroup PWR_LL_EC_BATT_CHARG_RESISTOR BATT CHARG RESISTOR
  * @{
  */
#define LL_PWR_BATT_CHARG_RESISTOR_5K      (0x00000000UL)
#define LL_PWR_BATT_CHARGRESISTOR_1_5K     (PWR_CR4_VBRS)
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GPIO GPIO
  * @{
  */
#define LL_PWR_GPIO_A                      ((uint32_t)(&(PWR->PUCRA)))
#define LL_PWR_GPIO_B                      ((uint32_t)(&(PWR->PUCRB)))
#define LL_PWR_GPIO_C                      ((uint32_t)(&(PWR->PUCRC)))
#define LL_PWR_GPIO_H                      ((uint32_t)(&(PWR->PUCRH)))
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GPIO_BIT GPIO BIT
  * @{
  */
/* Note: LL_PWR_GPIO_BIT_x defined from port B because all pins are available */
/*       for PWR pull-up and pull-down.                                       */
#define LL_PWR_GPIO_BIT_0                  (PWR_PUCRB_PB0)
#define LL_PWR_GPIO_BIT_1                  (PWR_PUCRB_PB1)
#define LL_PWR_GPIO_BIT_2                  (PWR_PUCRB_PB2)
#define LL_PWR_GPIO_BIT_3                  (PWR_PUCRB_PB3)
#define LL_PWR_GPIO_BIT_4                  (PWR_PUCRB_PB4)
#define LL_PWR_GPIO_BIT_5                  (PWR_PUCRB_PB5)
#define LL_PWR_GPIO_BIT_6                  (PWR_PUCRB_PB6)
#define LL_PWR_GPIO_BIT_7                  (PWR_PUCRB_PB7)
#define LL_PWR_GPIO_BIT_8                  (PWR_PUCRB_PB8)
#define LL_PWR_GPIO_BIT_9                  (PWR_PUCRB_PB9)
#define LL_PWR_GPIO_BIT_10                 (PWR_PUCRB_PB10)
#define LL_PWR_GPIO_BIT_11                 (PWR_PUCRB_PB11)
#define LL_PWR_GPIO_BIT_12                 (PWR_PUCRB_PB12)
#define LL_PWR_GPIO_BIT_13                 (PWR_PUCRB_PB13)
#define LL_PWR_GPIO_BIT_14                 (PWR_PUCRB_PB14)
#define LL_PWR_GPIO_BIT_15                 (PWR_PUCRB_PB15)
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SMPS_OPERATING_MODES SMPS step down converter operating modes
  * @{
  */
#define LL_PWR_SMPS_BYPASS                 (0x00000000UL)    /*!< SMPS step down in bypass mode (disable). */
#define LL_PWR_SMPS_STEP_DOWN              (PWR_CR5_SMPSEN)  /*!< SMPS step down in step down mode if system low power mode is run, LP run or Stop 0. If system low power mode is Stop 1, Stop 2, Standby, Shutdown, then SMPS is forced in mode open to preserve energy stored in decoupling capacitor as long as possible. Note: In case of a board without SMPS coil mounted, SMPS should not be activated. */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_RADIO_BUSY_POLARITY Radio busy signal polarity
  * @{
  */
#define LL_PWR_RADIO_BUSY_POLARITY_RISING  (0x00000000UL)     /*!< Radio busy signal polarity to rising edge (detection on high level). */
#define LL_PWR_RADIO_BUSY_POLARITY_FALLING (PWR_CR4_WRFBUSYP) /*!< Radio busy signal polarity to falling edge (detection on low level). */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_RADIO_BUSY_TRIGGER Radio busy trigger
  * @{
  */
#define LL_PWR_RADIO_BUSY_TRIGGER_NONE     (0x00000000UL)     /*!< Radio busy trigger action: no wake-up from low-power mode and no interruption sent to the selected CPU. */
#define LL_PWR_RADIO_BUSY_TRIGGER_WU_IT    (PWR_CR3_EWRFBUSY) /*!< Radio busy trigger action: wake-up from low-power mode Standby and interruption sent to the selected CPU. */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_RADIO_IRQ_TRIGGER Radio IRQ trigger
  * @{
  */
#define LL_PWR_RADIO_IRQ_TRIGGER_NONE      (0x00000000UL)     /*!< Radio IRQ trigger action: no wake-up from low-power mode and no interruption sent to the selected CPU. */
#define LL_PWR_RADIO_IRQ_TRIGGER_WU_IT     (PWR_CR3_EWRFIRQ)  /*!< Radio IRQ trigger action: wake-up from low-power mode Standby and interruption sent to the selected CPU. */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_RADIO_SPI_NSS_SRC Radio Sub-GHz radio SPI NSS source
  * @{
  */
#define LL_PWR_SUBGHZSPI_NSS_SRC_SW        (0x00000000UL)            /*!< Sub-GHz radio SPI NSS controlled by software. Refer to function @ref LL_PWR_UnselectSUBGHZSPI_NSS(). */
#define LL_PWR_SUBGHZSPI_NSS_SRC_LPTIM3    (PWR_CR1_SUBGHZSPINSSSEL) /*!< Sub-GHz radio SPI NSS controlled by LPTIM3. */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Macros PWR Exported Macros
  * @{
  */

/** @defgroup PWR_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in PWR register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_PWR_WriteReg(__REG__, __VALUE__) WRITE_REG(PWR->__REG__, (__VALUE__))

/**
  * @brief  Read a value in PWR register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_PWR_ReadReg(__REG__) READ_REG(PWR->__REG__)
/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_LL_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Switch from run main mode to run low-power mode.
  * @rmtoll CR1          LPR           LL_PWR_EnterLowPowerRunMode
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnterLowPowerRunMode(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_LPR);
}

/**
  * @brief  Switch from run main mode to low-power mode.
  * @rmtoll CR1          LPR           LL_PWR_ExitLowPowerRunMode
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ExitLowPowerRunMode(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_LPR);
}

/**
  * @brief  Check if the regulator is in low-power mode
  * @rmtoll CR1          LPR           LL_PWR_IsEnabledLowPowerRunMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledLowPowerRunMode(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_LPR) == (PWR_CR1_LPR)) ? 1UL : 0UL);
}

/**
  * @brief  Set the main internal regulator output voltage
  * @note   A delay is required for the internal regulator to be ready
  *         after the voltage scaling has been changed.
  *         Check whether regulator reached the selected voltage level
  *         can be done using function @ref LL_PWR_IsActiveFlag_VOS().
  * @rmtoll CR1          VOS           LL_PWR_SetRegulVoltageScaling
  * @param  VoltageScaling This parameter can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE1
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRegulVoltageScaling(uint32_t VoltageScaling)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_VOS, VoltageScaling);
}

/**
  * @brief  Get the main internal regulator output voltage
  * @rmtoll CR1          VOS           LL_PWR_GetRegulVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE1
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE2
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulVoltageScaling(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_VOS));
}

/**
  * @brief  Enable access to the backup domain
  * @rmtoll CR1          DBP           LL_PWR_EnableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBkUpAccess(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @brief  Disable access to the backup domain
  * @rmtoll CR1          DBP           LL_PWR_DisableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBkUpAccess(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @brief  Check if the backup domain is enabled
  * @rmtoll CR1          DBP           LL_PWR_IsEnabledBkUpAccess
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBkUpAccess(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_DBP) == (PWR_CR1_DBP)) ? 1UL : 0UL);
}

/**
  * @brief  Set Low-Power mode
  * @rmtoll CR1          LPMS          LL_PWR_SetPowerMode
  * @param  LowPowerMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_MODE_STOP0
  *         @arg @ref LL_PWR_MODE_STOP1
  *         @arg @ref LL_PWR_MODE_STOP2
  *         @arg @ref LL_PWR_MODE_STANDBY
  *         @arg @ref LL_PWR_MODE_SHUTDOWN
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPowerMode(uint32_t LowPowerMode)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_LPMS, LowPowerMode);
}

/**
  * @brief  Get Low-Power mode
  * @rmtoll CR1          LPMS          LL_PWR_GetPowerMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_MODE_STOP0
  *         @arg @ref LL_PWR_MODE_STOP1
  *         @arg @ref LL_PWR_MODE_STOP2
  *         @arg @ref LL_PWR_MODE_STANDBY
  *         @arg @ref LL_PWR_MODE_SHUTDOWN
  */
__STATIC_INLINE uint32_t LL_PWR_GetPowerMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_LPMS));
}

/**
  * @brief  Set flash power-down mode during low-power run mode
  * @rmtoll CR1          FPDR          LL_PWR_SetFlashPowerModeLPRun
  * @param  FlashLowPowerMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_FLASH_LPRUN_MODE_IDLE
  *         @arg @ref LL_PWR_FLASH_LPRUN_MODE_POWER_DOWN
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetFlashPowerModeLPRun(uint32_t FlashLowPowerMode)
{
  /* Unlock bit FPDR */
  WRITE_REG(PWR->CR1, PWR_FLASH_POWER_MODE_UNLOCK_CODE);

  /* Update bit FPDR */
  MODIFY_REG(PWR->CR1, PWR_CR1_FPDR, FlashLowPowerMode);
}

/**
  * @brief  Get flash power-down mode during low-power run mode
  * @rmtoll CR1          FPDR          LL_PWR_GetFlashPowerModeLPRun
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_FLASH_LPRUN_MODE_IDLE
  *         @arg @ref LL_PWR_FLASH_LPRUN_MODE_POWER_DOWN
  */
__STATIC_INLINE uint32_t LL_PWR_GetFlashPowerModeLPRun(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_FPDR));
}

/**
  * @brief  Set flash power-down mode during sleep mode
  * @rmtoll CR1          FPDS          LL_PWR_SetFlashPowerModeSleep
  * @param  FlashLowPowerMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_FLASH_SLEEP_MODE_IDLE
  *         @arg @ref LL_PWR_FLASH_SLEEP_MODE_POWER_DOWN
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetFlashPowerModeSleep(uint32_t FlashLowPowerMode)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_FPDS, FlashLowPowerMode);
}

/**
  * @brief  Get flash power-down mode during sleep mode
  * @rmtoll CR1          FPDS          LL_PWR_GetFlashPowerModeSleep
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_FLASH_SLEEP_MODE_IDLE
  *         @arg @ref LL_PWR_FLASH_SLEEP_MODE_POWER_DOWN
  */
__STATIC_INLINE uint32_t LL_PWR_GetFlashPowerModeSleep(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_FPDS));
}

/**
  * @brief  Enable the Power Voltage Monitoring on a peripheral
  * @rmtoll CR2          PVME3         LL_PWR_EnablePVM
  * @param  PeriphVoltage This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVM_VDDA_1_62V
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePVM(uint32_t PeriphVoltage)
{
  SET_BIT(PWR->CR2, PeriphVoltage);
}

/**
  * @brief  Disable the Power Voltage Monitoring on a peripheral
  * @rmtoll CR2          PVME3         LL_PWR_DisablePVM
  * @param  PeriphVoltage This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVM_VDDA_1_62V
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePVM(uint32_t PeriphVoltage)
{
  CLEAR_BIT(PWR->CR2, PeriphVoltage);
}

/**
  * @brief  Check if Power Voltage Monitoring is enabled on a peripheral
  * @rmtoll CR2          PVME3         LL_PWR_IsEnabledPVM
  * @param  PeriphVoltage This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVM_VDDA_1_62V
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVM(uint32_t PeriphVoltage)
{
  return ((READ_BIT(PWR->CR2, PeriphVoltage) == (PeriphVoltage)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the voltage threshold detected by the Power Voltage Detector
  * @rmtoll CR2          PLS           LL_PWR_SetPVDLevel
  * @param  PVDLevel This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_0
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPVDLevel(uint32_t PVDLevel)
{
  MODIFY_REG(PWR->CR2, PWR_CR2_PLS, PVDLevel);
}

/**
  * @brief  Get the voltage threshold detection
  * @rmtoll CR2          PLS           LL_PWR_GetPVDLevel
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_0
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  */
__STATIC_INLINE uint32_t LL_PWR_GetPVDLevel(void)
{
  return (uint32_t)(READ_BIT(PWR->CR2, PWR_CR2_PLS));
}

/**
  * @brief  Enable Power Voltage Detector
  * @rmtoll CR2          PVDE          LL_PWR_EnablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_PVDE);
}

/**
  * @brief  Disable Power Voltage Detector
  * @rmtoll CR2          PVDE          LL_PWR_DisablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_PVDE);
}

/**
  * @brief  Check if Power Voltage Detector is enabled
  * @rmtoll CR2          PVDE          LL_PWR_IsEnabledPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_PVDE) == (PWR_CR2_PVDE)) ? 1UL : 0UL);
}

/**
  * @brief  Set monitoring of supply voltage for radio operating level
  *         (radio End Of Life), radio must be in active mode.
  * @rmtoll CR5          RFEOLEN       LL_PWR_SetRadioEOL
  * @param  RadioEOL This parameter can be one of the following values:
  *         @arg @ref LL_PWR_RADIO_EOL_DISABLE
  *         @arg @ref LL_PWR_RADIO_EOL_ENABLE
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRadioEOL(uint32_t RadioEOL)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_RFEOLEN, RadioEOL);
}

/**
  * @brief  Get monitoring of supply voltage for radio operating level (radio End Of Life)
  * @rmtoll CR5          RFEOLEN       LL_PWR_GetRadioEOL
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_RADIO_EOL_DISABLE
  *         @arg @ref LL_PWR_RADIO_EOL_ENABLE
  */
__STATIC_INLINE uint32_t LL_PWR_GetRadioEOL(void)
{
  return (uint32_t)(READ_BIT(PWR->CR5, PWR_CR5_RFEOLEN));
}

/**
  * @brief  Enable Internal Wake-up line
  * @rmtoll CR3          EIWF          LL_PWR_EnableInternWU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableInternWU(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_EIWUL);
}

/**
  * @brief  Disable Internal Wake-up line
  * @rmtoll CR3          EIWF          LL_PWR_DisableInternWU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableInternWU(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_EIWUL);
}

/**
  * @brief  Check if Internal Wake-up line is enabled
  * @rmtoll CR3          EIWF          LL_PWR_IsEnabledInternWU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledInternWU(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_EIWUL) == (PWR_CR3_EIWUL)) ? 1UL : 0UL);
}

/**
  * @brief  Enable pull-up and pull-down configuration
  * @rmtoll CR3          APC           LL_PWR_EnablePUPDCfg
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePUPDCfg(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_APC);
}

/**
  * @brief  Disable pull-up and pull-down configuration
  * @rmtoll CR3          APC           LL_PWR_DisablePUPDCfg
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePUPDCfg(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_APC);
}

/**
  * @brief  Check if pull-up and pull-down configuration is enabled
  * @rmtoll CR3          APC           LL_PWR_IsEnabledPUPDCfg
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPUPDCfg(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_APC) == (PWR_CR3_APC)) ? 1UL : 0UL);
}

/**
  * @brief  Enable SRAM2 content retention in Standby mode
  * @rmtoll CR3          RRS           LL_PWR_EnableSRAM2Retention
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableSRAM2Retention(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_RRS);
}

/**
  * @brief  Disable SRAM2 content retention in Standby mode
  * @rmtoll CR3          RRS           LL_PWR_DisableSRAM2Retention
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableSRAM2Retention(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_RRS);
}

/**
  * @brief  Check if SRAM2 content retention in Standby mode is enabled
  * @rmtoll CR3          RRS           LL_PWR_IsEnabledSRAM2Retention
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSRAM2Retention(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_RRS) == (PWR_CR3_RRS)) ? 1UL : 0UL);
}

/**
  * @brief  Enable wake-up power voltage detection with trigger for CPU1
  * @note   Wake-up power voltage detection status can be checked
  *         using function @ref LL_PWR_IsActiveFlag_WPVD().
  * @rmtoll CR3          EWPVD         LL_PWR_EnableWPVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableWPVD(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_EWPVD);
}

/**
  * @brief  Disable wake-up power voltage detection with trigger for CPU1
  * @rmtoll CR3          EWPVD         LL_PWR_DisableWPVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableWPVD(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_EWPVD);
}

/**
  * @brief  Check if wake-up power voltage detection is enabled with trigger for CPU1
  * @rmtoll CR3          EWPVD         LL_PWR_IsEnabledWPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWPVD(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_EWPVD) == (PWR_CR3_EWPVD)) ? 1UL : 0UL);
}

/**
  * @brief  Enable periodical sampling of supply voltage in Stop and Standby
  *         modes for detecting condition of PDR and BOR reset.
  * @note   Caution: When enabled, and if the supply voltage drops below
  *         the minimum operating condition between two supply voltage samples,
  *         the reset condition is missed and no reset is generated.
  * @rmtoll CR3          ULPEN         LL_PWR_EnableBORPVD_ULP
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBORPVD_ULP(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_ULPEN);
}

/**
  * @brief  Disable periodical sampling of supply voltage in Stop and Standby
  *         modes for detecting condition of PDR and BOR reset.
  * @rmtoll CR3          ULPEN         LL_PWR_DisableBORPVD_ULP
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBORPVD_ULP(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_ULPEN);
}

/**
  * @brief  Check if periodical sampling of supply voltage in Stop and Standby
  *         modes is enabled.
  * @rmtoll CR3          ULPEN         LL_PWR_IsEnabledBORPVD_ULP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBORPVD_ULP(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_ULPEN) == (PWR_CR3_ULPEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the WakeUp PINx functionality
  * @rmtoll CR3          EWUP1         LL_PWR_EnableWakeUpPin\n
  *         CR3          EWUP2         LL_PWR_EnableWakeUpPin\n
  *         CR3          EWUP3         LL_PWR_EnableWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableWakeUpPin(uint32_t WakeUpPin)
{
  SET_BIT(PWR->CR3, WakeUpPin);
}

/**
  * @brief  Disable the WakeUp PINx functionality
  * @rmtoll CR3          EWUP1         LL_PWR_DisableWakeUpPin\n
  *         CR3          EWUP2         LL_PWR_DisableWakeUpPin\n
  *         CR3          EWUP3         LL_PWR_DisableWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableWakeUpPin(uint32_t WakeUpPin)
{
  CLEAR_BIT(PWR->CR3, WakeUpPin);
}

/**
  * @brief  Check if the WakeUp PINx functionality is enabled
  * @rmtoll CR3          EWUP1         LL_PWR_IsEnabledWakeUpPin\n
  *         CR3          EWUP2         LL_PWR_IsEnabledWakeUpPin\n
  *         CR3          EWUP3         LL_PWR_IsEnabledWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWakeUpPin(uint32_t WakeUpPin)
{
  return ((READ_BIT(PWR->CR3, WakeUpPin) == (WakeUpPin)) ? 1UL : 0UL);
}

/**
  * @brief  Set the resistor impedance
  * @rmtoll CR4          VBRS          LL_PWR_SetBattChargResistor
  * @param  Resistor This parameter can be one of the following values:
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_5K
  *         @arg @ref LL_PWR_BATT_CHARGRESISTOR_1_5K
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetBattChargResistor(uint32_t Resistor)
{
  MODIFY_REG(PWR->CR4, PWR_CR4_VBRS, Resistor);
}

/**
  * @brief  Get the resistor impedance
  * @rmtoll CR4          VBRS          LL_PWR_GetBattChargResistor
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_5K
  *         @arg @ref LL_PWR_BATT_CHARGRESISTOR_1_5K
  */
__STATIC_INLINE uint32_t LL_PWR_GetBattChargResistor(void)
{
  return (uint32_t)(READ_BIT(PWR->CR4, PWR_CR4_VBRS));
}

/**
  * @brief  Enable battery charging
  * @rmtoll CR4          VBE           LL_PWR_EnableBatteryCharging
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBatteryCharging(void)
{
  SET_BIT(PWR->CR4, PWR_CR4_VBE);
}

/**
  * @brief  Disable battery charging
  * @rmtoll CR4          VBE           LL_PWR_DisableBatteryCharging
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBatteryCharging(void)
{
  CLEAR_BIT(PWR->CR4, PWR_CR4_VBE);
}

/**
  * @brief  Check if battery charging is enabled
  * @rmtoll CR4          VBE           LL_PWR_IsEnabledBatteryCharging
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBatteryCharging(void)
{
  return ((READ_BIT(PWR->CR4, PWR_CR4_VBE) == (PWR_CR4_VBE)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Wake-Up pin polarity low for the event detection
  * @rmtoll CR4          WP1           LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR4          WP2           LL_PWR_SetWakeUpPinPolarityLow\n
  *         CR4          WP3           LL_PWR_SetWakeUpPinPolarityLow
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityLow(uint32_t WakeUpPin)
{
  SET_BIT(PWR->CR4, WakeUpPin);
}

/**
  * @brief  Set the Wake-Up pin polarity high for the event detection
  * @rmtoll CR4          WP1           LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR4          WP2           LL_PWR_SetWakeUpPinPolarityHigh\n
  *         CR4          WP3           LL_PWR_SetWakeUpPinPolarityHigh
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityHigh(uint32_t WakeUpPin)
{
  CLEAR_BIT(PWR->CR4, WakeUpPin);
}

/**
  * @brief  Get the Wake-Up pin polarity for the event detection
  * @rmtoll CR4          WP1           LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR4          WP2           LL_PWR_IsWakeUpPinPolarityLow\n
  *         CR4          WP3           LL_PWR_IsWakeUpPinPolarityLow
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsWakeUpPinPolarityLow(uint32_t WakeUpPin)
{
  return ((READ_BIT(PWR->CR4, WakeUpPin) == (WakeUpPin)) ? 1UL : 0UL);
}

/**
  * @brief  Enable GPIO pull-up state in Standby and Shutdown modes
  * @note   Some pins are not configurable for pulling in Standby and Shutdown
  *         modes. Refer to reference manual for available pins and ports.
  * @rmtoll PUCRA        PU0-15        LL_PWR_EnableGPIOPullUp\n
  *         PUCRB        PU0-15        LL_PWR_EnableGPIOPullUp\n
  *         PUCRC        PU0-15        LL_PWR_EnableGPIOPullUp\n
  *         PUCRH        PU0-15        LL_PWR_EnableGPIOPullUp
  * @param  GPIO This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_A
  *         @arg @ref LL_PWR_GPIO_B
  *         @arg @ref LL_PWR_GPIO_C
  *         @arg @ref LL_PWR_GPIO_H
  * @param  GPIONumber This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_BIT_0
  *         @arg @ref LL_PWR_GPIO_BIT_1
  *         @arg @ref LL_PWR_GPIO_BIT_2
  *         @arg @ref LL_PWR_GPIO_BIT_3
  *         @arg @ref LL_PWR_GPIO_BIT_4
  *         @arg @ref LL_PWR_GPIO_BIT_5
  *         @arg @ref LL_PWR_GPIO_BIT_6
  *         @arg @ref LL_PWR_GPIO_BIT_7
  *         @arg @ref LL_PWR_GPIO_BIT_8
  *         @arg @ref LL_PWR_GPIO_BIT_9
  *         @arg @ref LL_PWR_GPIO_BIT_10
  *         @arg @ref LL_PWR_GPIO_BIT_11
  *         @arg @ref LL_PWR_GPIO_BIT_12
  *         @arg @ref LL_PWR_GPIO_BIT_13
  *         @arg @ref LL_PWR_GPIO_BIT_14
  *         @arg @ref LL_PWR_GPIO_BIT_15
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber)
{
  SET_BIT(*((__IO uint32_t *)GPIO), GPIONumber);
}

/**
  * @brief  Disable GPIO pull-up state in Standby and Shutdown modes
  * @note   Some pins are not configurable for pulling in Standby and Shutdown
  *         modes. Refer to reference manual for available pins and ports.
  * @rmtoll PUCRA        PU0-15        LL_PWR_DisableGPIOPullUp\n
  *         PUCRB        PU0-15        LL_PWR_DisableGPIOPullUp\n
  *         PUCRC        PU0-15        LL_PWR_DisableGPIOPullUp\n
  *         PUCRH        PU0-15        LL_PWR_DisableGPIOPullUp
  * @param  GPIO This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_A
  *         @arg @ref LL_PWR_GPIO_B
  *         @arg @ref LL_PWR_GPIO_C
  *         @arg @ref LL_PWR_GPIO_H
  * @param  GPIONumber This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_BIT_0
  *         @arg @ref LL_PWR_GPIO_BIT_1
  *         @arg @ref LL_PWR_GPIO_BIT_2
  *         @arg @ref LL_PWR_GPIO_BIT_3
  *         @arg @ref LL_PWR_GPIO_BIT_4
  *         @arg @ref LL_PWR_GPIO_BIT_5
  *         @arg @ref LL_PWR_GPIO_BIT_6
  *         @arg @ref LL_PWR_GPIO_BIT_7
  *         @arg @ref LL_PWR_GPIO_BIT_8
  *         @arg @ref LL_PWR_GPIO_BIT_9
  *         @arg @ref LL_PWR_GPIO_BIT_10
  *         @arg @ref LL_PWR_GPIO_BIT_11
  *         @arg @ref LL_PWR_GPIO_BIT_12
  *         @arg @ref LL_PWR_GPIO_BIT_13
  *         @arg @ref LL_PWR_GPIO_BIT_14
  *         @arg @ref LL_PWR_GPIO_BIT_15
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber)
{
  CLEAR_BIT(*((__IO uint32_t *)GPIO), GPIONumber);
}

/**
  * @brief  Check if GPIO pull-up state is enabled
  * @rmtoll PUCRA        PU0-15        LL_PWR_IsEnabledGPIOPullUp\n
  *         PUCRB        PU0-15        LL_PWR_IsEnabledGPIOPullUp\n
  *         PUCRC        PU0-15        LL_PWR_IsEnabledGPIOPullUp\n
  *         PUCRH        PU0-15        LL_PWR_IsEnabledGPIOPullUp
  * @param  GPIO This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_A
  *         @arg @ref LL_PWR_GPIO_B
  *         @arg @ref LL_PWR_GPIO_C
  *         @arg @ref LL_PWR_GPIO_H
  * @param  GPIONumber This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_BIT_0
  *         @arg @ref LL_PWR_GPIO_BIT_1
  *         @arg @ref LL_PWR_GPIO_BIT_2
  *         @arg @ref LL_PWR_GPIO_BIT_3
  *         @arg @ref LL_PWR_GPIO_BIT_4
  *         @arg @ref LL_PWR_GPIO_BIT_5
  *         @arg @ref LL_PWR_GPIO_BIT_6
  *         @arg @ref LL_PWR_GPIO_BIT_7
  *         @arg @ref LL_PWR_GPIO_BIT_8
  *         @arg @ref LL_PWR_GPIO_BIT_9
  *         @arg @ref LL_PWR_GPIO_BIT_10
  *         @arg @ref LL_PWR_GPIO_BIT_11
  *         @arg @ref LL_PWR_GPIO_BIT_12
  *         @arg @ref LL_PWR_GPIO_BIT_13
  *         @arg @ref LL_PWR_GPIO_BIT_14
  *         @arg @ref LL_PWR_GPIO_BIT_15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber)
{
  return ((READ_BIT(*((__IO uint32_t *)(GPIO)), GPIONumber) == (GPIONumber)) ? 1UL : 0UL);
}

/**
  * @brief  Enable GPIO pull-down state in Standby and Shutdown modes
  * @note   Some pins are not configurable for pulling in Standby and Shutdown
  *         modes. Refer to reference manual for available pins and ports.
  * @rmtoll PDCRA        PD0-15        LL_PWR_EnableGPIOPullDown\n
  *         PDCRB        PD0-15        LL_PWR_EnableGPIOPullDown\n
  *         PDCRC        PD0-15        LL_PWR_EnableGPIOPullDown\n
  *         PDCRH        PD0-15        LL_PWR_EnableGPIOPullDown
  * @param  GPIO This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_A
  *         @arg @ref LL_PWR_GPIO_B
  *         @arg @ref LL_PWR_GPIO_C
  *         @arg @ref LL_PWR_GPIO_H
  * @param  GPIONumber This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_BIT_0
  *         @arg @ref LL_PWR_GPIO_BIT_1
  *         @arg @ref LL_PWR_GPIO_BIT_2
  *         @arg @ref LL_PWR_GPIO_BIT_3
  *         @arg @ref LL_PWR_GPIO_BIT_4
  *         @arg @ref LL_PWR_GPIO_BIT_5
  *         @arg @ref LL_PWR_GPIO_BIT_6
  *         @arg @ref LL_PWR_GPIO_BIT_7
  *         @arg @ref LL_PWR_GPIO_BIT_8
  *         @arg @ref LL_PWR_GPIO_BIT_9
  *         @arg @ref LL_PWR_GPIO_BIT_10
  *         @arg @ref LL_PWR_GPIO_BIT_11
  *         @arg @ref LL_PWR_GPIO_BIT_12
  *         @arg @ref LL_PWR_GPIO_BIT_13
  *         @arg @ref LL_PWR_GPIO_BIT_14
  *         @arg @ref LL_PWR_GPIO_BIT_15
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber)
{
  SET_BIT(*((__IO uint32_t *)(GPIO + 4U)), GPIONumber);
}

/**
  * @brief  Disable GPIO pull-down state in Standby and Shutdown modes
  * @note   Some pins are not configurable for pulling in Standby and Shutdown
  *         modes. Refer to reference manual for available pins and ports.
  * @rmtoll PDCRA        PD0-15        LL_PWR_DisableGPIOPullDown\n
  *         PDCRB        PD0-15        LL_PWR_DisableGPIOPullDown\n
  *         PDCRC        PD0-15        LL_PWR_DisableGPIOPullDown\n
  *         PDCRH        PD0-15        LL_PWR_DisableGPIOPullDown
  * @param  GPIO This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_A
  *         @arg @ref LL_PWR_GPIO_B
  *         @arg @ref LL_PWR_GPIO_C
  *         @arg @ref LL_PWR_GPIO_H
  * @param  GPIONumber This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_BIT_0
  *         @arg @ref LL_PWR_GPIO_BIT_1
  *         @arg @ref LL_PWR_GPIO_BIT_2
  *         @arg @ref LL_PWR_GPIO_BIT_3
  *         @arg @ref LL_PWR_GPIO_BIT_4
  *         @arg @ref LL_PWR_GPIO_BIT_5
  *         @arg @ref LL_PWR_GPIO_BIT_6
  *         @arg @ref LL_PWR_GPIO_BIT_7
  *         @arg @ref LL_PWR_GPIO_BIT_8
  *         @arg @ref LL_PWR_GPIO_BIT_9
  *         @arg @ref LL_PWR_GPIO_BIT_10
  *         @arg @ref LL_PWR_GPIO_BIT_11
  *         @arg @ref LL_PWR_GPIO_BIT_12
  *         @arg @ref LL_PWR_GPIO_BIT_13
  *         @arg @ref LL_PWR_GPIO_BIT_14
  *         @arg @ref LL_PWR_GPIO_BIT_15
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber)
{
  CLEAR_BIT(*((__IO uint32_t *)(GPIO + 4U)), GPIONumber);
}

/**
  * @brief  Check if GPIO pull-down state is enabled
  * @rmtoll PDCRA        PD0-15        LL_PWR_IsEnabledGPIOPullDown\n
  *         PDCRB        PD0-15        LL_PWR_IsEnabledGPIOPullDown\n
  *         PDCRC        PD0-15        LL_PWR_IsEnabledGPIOPullDown\n
  *         PDCRH        PD0-15        LL_PWR_IsEnabledGPIOPullDown
  * @param  GPIO This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_A
  *         @arg @ref LL_PWR_GPIO_B
  *         @arg @ref LL_PWR_GPIO_C
  *         @arg @ref LL_PWR_GPIO_H
  * @param  GPIONumber This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_BIT_0
  *         @arg @ref LL_PWR_GPIO_BIT_1
  *         @arg @ref LL_PWR_GPIO_BIT_2
  *         @arg @ref LL_PWR_GPIO_BIT_3
  *         @arg @ref LL_PWR_GPIO_BIT_4
  *         @arg @ref LL_PWR_GPIO_BIT_5
  *         @arg @ref LL_PWR_GPIO_BIT_6
  *         @arg @ref LL_PWR_GPIO_BIT_7
  *         @arg @ref LL_PWR_GPIO_BIT_8
  *         @arg @ref LL_PWR_GPIO_BIT_9
  *         @arg @ref LL_PWR_GPIO_BIT_10
  *         @arg @ref LL_PWR_GPIO_BIT_11
  *         @arg @ref LL_PWR_GPIO_BIT_12
  *         @arg @ref LL_PWR_GPIO_BIT_13
  *         @arg @ref LL_PWR_GPIO_BIT_14
  *         @arg @ref LL_PWR_GPIO_BIT_15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber)
{
  return ((READ_BIT(*((__IO uint32_t *)(GPIO + 4U)), GPIONumber) == (GPIONumber)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup PWR_LL_EF_Configuration_SMPS Configuration of SMPS
  * @{
  */

/**
  * @brief  Set SMPS operating mode
  * @note   In case of a board without SMPS coil mounted, SMPS should not be activated.
  * @rmtoll CR5          SMPSEN        LL_PWR_SMPS_SetMode
  * @param  OperatingMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SMPS_BYPASS
  *         @arg @ref LL_PWR_SMPS_STEP_DOWN
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SMPS_SetMode(uint32_t OperatingMode)
{
  MODIFY_REG(PWR->CR5, PWR_CR5_SMPSEN, OperatingMode);
}

/**
  * @brief  Get SMPS operating mode
  * @rmtoll CR5          SMPSEN        LL_PWR_SMPS_GetMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SMPS_BYPASS
  *         @arg @ref LL_PWR_SMPS_STEP_DOWN
  */
__STATIC_INLINE uint32_t LL_PWR_SMPS_GetMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CR5, PWR_CR5_SMPSEN));
}

/**
  * @brief  Get SMPS effective operating mode
  * @note   SMPS operating mode can be changed by hardware, therefore
  *         requested operating mode can differ from effective low power mode.
  *         - dependency SubGhz Radio IP: can switch SMPS on for radio activity.
  * @note   In case of a board without SMPS coil mounted, SMPS should not be activated
  *         and this function is not relevant.
  * @rmtoll SR2          SMPSRDY       LL_PWR_SMPS_GetEffectiveMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SMPS_BYPASS
  *         @arg @ref LL_PWR_SMPS_STEP_DOWN
  */
__STATIC_INLINE uint32_t LL_PWR_SMPS_GetEffectiveMode(void)
{
  /* Return a value corresponding to definition of literals                   */
  /* LL_PWR_SMPS_BYPASS or LL_PWR_SMPS_STEP_DOWN.                             */
  return (uint32_t)(READ_BIT(PWR->SR2, PWR_SR2_SMPSRDY) << (PWR_CR5_SMPSEN_Pos - PWR_SR2_SMPSRDY_Pos));
}

/**
  * @brief  SMPS step down converter enable
  * @note   This function can be used for specific usage of the SMPS,
  *         for general usage of the SMPS the function
  *         @ref LL_PWR_SMPS_SetMode() should be used instead.
  * @rmtoll CR5          SMPSEN        LL_PWR_SMPS_Enable
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SMPS_Enable(void)
{
  SET_BIT(PWR->CR5, PWR_CR5_SMPSEN);
}

/**
  * @brief  SMPS step down converter enable
  * @note   This function can be used for specific usage of the SMPS,
  *         for general usage of the SMPS the function
  *         @ref LL_PWR_SMPS_SetMode() should be used instead.
  * @rmtoll CR5          SMPSEN        LL_PWR_SMPS_Disable
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SMPS_Disable(void)
{
  CLEAR_BIT(PWR->CR5, PWR_CR5_SMPSEN);
}

/**
  * @brief  Check if the SMPS step down converter is enabled
  * @rmtoll CR5          SMPSEN        LL_PWR_SMPS_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_SMPS_IsEnabled(void)
{
  return ((READ_BIT(PWR->CR5, PWR_CR5_SMPSEN) == (PWR_CR5_SMPSEN)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup PWR_LL_EF_Configuration_Radio Configuration of radio
  * @{
  */

/**
  * @brief  Set radio busy signal polarity
  * @rmtoll CR4          RFBUSYP       LL_PWR_SetRadioBusyPolarity
  * @param  RadioBusyPolarity This parameter can be one of the following values:
  *         @arg @ref LL_PWR_RADIO_BUSY_POLARITY_RISING
  *         @arg @ref LL_PWR_RADIO_BUSY_POLARITY_FALLING
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRadioBusyPolarity(uint32_t RadioBusyPolarity)
{
  MODIFY_REG(PWR->CR4, PWR_CR4_WRFBUSYP, RadioBusyPolarity);
}

/**
  * @brief  Get radio busy signal polarity
  * @rmtoll CR4          RFBUSYP       LL_PWR_GetRadioBusyPolarity
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_RADIO_BUSY_POLARITY_RISING
  *         @arg @ref LL_PWR_RADIO_BUSY_POLARITY_FALLING
  */
__STATIC_INLINE uint32_t LL_PWR_GetRadioBusyPolarity(void)
{
  return (uint32_t)(READ_BIT(PWR->CR4, PWR_CR4_WRFBUSYP));
}

/**
  * @brief  Set radio busy trigger action for CPU1: wake-up from low-power mode
  *         Standby.
  * @note   Signal polarity can be configured using function
  *         @ref LL_PWR_SetRadioBusyPolarity().
  * @rmtoll CR3          ERFBUSY       LL_PWR_SetRadioBusyTrigger
  * @param  RadioBusyTrigger This parameter can be one of the following values:
  *         @arg @ref LL_PWR_RADIO_BUSY_TRIGGER_NONE
  *         @arg @ref LL_PWR_RADIO_BUSY_TRIGGER_WU_IT
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRadioBusyTrigger(uint32_t RadioBusyTrigger)
{
  MODIFY_REG(PWR->CR3, PWR_CR3_EWRFBUSY, RadioBusyTrigger);
}

/**
  * @brief  Get radio busy trigger action for CPU1: wake-up from low-power mode
  *         Standby.
  * @rmtoll CR3          ERFBUSY       LL_PWR_GetRadioBusyTrigger
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_RADIO_BUSY_TRIGGER_NONE
  *         @arg @ref LL_PWR_RADIO_BUSY_TRIGGER_WU_IT
  */
__STATIC_INLINE uint32_t LL_PWR_GetRadioBusyTrigger(void)
{
  return (uint32_t)(READ_BIT(PWR->CR3, PWR_CR3_EWRFBUSY));
}

/**
  * @brief  Set radio IRQ trigger action for CPU1: wake-up from low-power mode
  *         Standby.
  * @rmtoll CR3          ERFIRQ        LL_PWR_SetRadioIRQTrigger
  * @param  RadioIRQTrigger This parameter can be one of the following values:
  *         @arg @ref LL_PWR_RADIO_IRQ_TRIGGER_NONE
  *         @arg @ref LL_PWR_RADIO_IRQ_TRIGGER_WU_IT
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRadioIRQTrigger(uint32_t RadioIRQTrigger)
{
  MODIFY_REG(PWR->CR3, PWR_CR3_EWRFIRQ, RadioIRQTrigger);
}

/**
  * @brief  Get radio IRQ trigger action for CPU1: wake-up from low-power mode
  *         Standby.
  * @rmtoll CR3          ERFIRQ        LL_PWR_GetRadioIRQTrigger
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_RADIO_IRQ_TRIGGER_NONE
  *         @arg @ref LL_PWR_RADIO_IRQ_TRIGGER_WU_IT
  */
__STATIC_INLINE uint32_t LL_PWR_GetRadioIRQTrigger(void)
{
  return (uint32_t)(READ_BIT(PWR->CR3, PWR_CR3_EWRFIRQ));
}

/**
  * @brief  Set sub-GHz radio SPI NSS control source
  * @rmtoll CR1          SUBGHZSPINSSSEL LL_PWR_SetSUBGHZSPI_NSSSource
  * @param  RadioSPI_NSSSource This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SUBGHZSPI_NSS_SRC_SW
  *         @arg @ref LL_PWR_SUBGHZSPI_NSS_SRC_LPTIM3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetSUBGHZSPI_NSSSource(uint32_t RadioSPI_NSSSource)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_SUBGHZSPINSSSEL, RadioSPI_NSSSource);
}

/**
  * @brief  Get sub-GHz radio SPI NSS control source
  * @rmtoll CR1          SUBGHZSPINSSSEL LL_PWR_GetSUBGHZSPI_NSSSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SUBGHZSPI_NSS_SRC_SW
  *         @arg @ref LL_PWR_SUBGHZSPI_NSS_SRC_LPTIM3
  */
__STATIC_INLINE uint32_t LL_PWR_GetSUBGHZSPI_NSSSource(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_SUBGHZSPINSSSEL));
}

/**
  * @brief  Set sub-GHz radio SPI NSS at logical level high.
  * @rmtoll SUBGHZSPICR  NSS           LL_PWR_UnselectSUBGHZSPI_NSS
  * @retval None
  */
__STATIC_INLINE void LL_PWR_UnselectSUBGHZSPI_NSS(void)
{
  SET_BIT(PWR->SUBGHZSPICR, PWR_SUBGHZSPICR_NSS);
}

/**
  * @brief  Set sub-GHz radio SPI NSS at logical level low.
  * @rmtoll SUBGHZSPICR  NSS           LL_PWR_SelectSUBGHZSPI_NSS
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SelectSUBGHZSPI_NSS(void)
{
  CLEAR_BIT(PWR->SUBGHZSPICR, PWR_SUBGHZSPICR_NSS);
}

/**
  * @brief  Check whether sub-GHz radio SPI NSS is at logical level high or low.
  * @rmtoll SUBGHZSPICR  NSS           LL_PWR_IsSUBGHZSPI_NSS_Selected
  * @retval State of bit (1 for SUBGHZSPI_NSS selected or 0 for SUBGHZSPI_NSS unselected).
  */
__STATIC_INLINE uint32_t LL_PWR_IsSUBGHZSPI_NSS_Selected(void)
{
  return ((READ_BIT(PWR->SUBGHZSPICR, PWR_SUBGHZSPICR_NSS) != (PWR_SUBGHZSPICR_NSS)) ? 1UL : 0UL);
}

/**
  * @}
  */

#if defined(DUAL_CORE)
/** @defgroup PWR_LL_EF_Configuration_Radio_CPU2 Configuration of radio for CPU2
  * @{
  */

/**
  * @brief  Set radio busy trigger action for CPU2: wake-up from low-power mode,
  *         interruption.
  * @note   Signal polarity can be configured using function
  *         @ref LL_PWR_SetRadioBusyPolarity().
  * @rmtoll C2CR3        ERFBUSY       LL_C2_PWR_SetRadioBusyTrigger
  * @param  RadioBusyTrigger This parameter can be one of the following values:
  *         @arg @ref LL_PWR_RADIO_BUSY_TRIGGER_NONE
  *         @arg @ref LL_PWR_RADIO_BUSY_TRIGGER_WU_IT
  * @retval None
  */
__STATIC_INLINE void LL_C2_PWR_SetRadioBusyTrigger(uint32_t RadioBusyTrigger)
{
  MODIFY_REG(PWR->C2CR3, PWR_C2CR3_EWRFBUSY, RadioBusyTrigger);
}

/**
  * @brief  Get radio busy trigger action for CPU2: wake-up from low-power mode,
  *         interruption.
  * @rmtoll C2CR3        ERFBUSY       LL_C2_PWR_GetRadioBusyTrigger
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_RADIO_BUSY_TRIGGER_NONE
  *         @arg @ref LL_PWR_RADIO_BUSY_TRIGGER_WU_IT
  */
__STATIC_INLINE uint32_t LL_C2_PWR_GetRadioBusyTrigger(void)
{
  /* Note: Bit shift performed for literals to be generic between CPU1 and CPU2 */
  return (uint32_t)(READ_BIT(PWR->C2CR3, PWR_C2CR3_EWRFBUSY));
}

/**
  * @brief  Set radio IRQ trigger action for CPU2: wake-up from low-power mode,
  *         interruption.
  * @rmtoll C2CR3        ERFIRQ        LL_C2_PWR_SetRadioIRQTrigger
  * @param  RadioIRQTrigger This parameter can be one of the following values:
  *         @arg @ref LL_PWR_RADIO_IRQ_TRIGGER_NONE
  *         @arg @ref LL_PWR_RADIO_IRQ_TRIGGER_WU_IT
  * @retval None
  */
__STATIC_INLINE void LL_C2_PWR_SetRadioIRQTrigger(uint32_t RadioIRQTrigger)
{
  MODIFY_REG(PWR->C2CR3, PWR_C2CR3_EWRFIRQ, RadioIRQTrigger);
}

/**
  * @brief  Get radio IRQ trigger action for CPU2: wake-up from low-power mode,
  *         interruption.
  * @rmtoll C2CR3        ERFIRQ        LL_C2_PWR_GetRadioIRQTrigger
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_RADIO_IRQ_TRIGGER_NONE
  *         @arg @ref LL_PWR_RADIO_IRQ_TRIGGER_WU_IT
  */
__STATIC_INLINE uint32_t LL_C2_PWR_GetRadioIRQTrigger(void)
{
  return (uint32_t)(READ_BIT(PWR->C2CR3, PWR_C2CR3_EWRFIRQ));
}

/**
  * @}
  */

/** @defgroup PWR_LL_EF_Configuration_Multicore Configuration of multicore, intended to be executed by CPU1
  * @{
  */

/**
  * @brief  Boot CPU2 after reset or wakeup from Stop or Standby modes.
  * @note   CPU2 can boot from configuration of this function or from
  *         an illegal access. For information of boot source,
  *         refer to function @ref LL_PWR_IsActiveFlag_C2BOOTS().
  * @rmtoll CR4          C2BOOT        LL_PWR_EnableBootC2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBootC2(void)
{
  SET_BIT(PWR->CR4, PWR_CR4_C2BOOT);
}

/**
  * @brief  Do not allow CPU2 to boot after reset or wakeup from Stop or Standby
  *         modes.
  * @rmtoll CR4          C2BOOT        LL_PWR_DisableBootC2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBootC2(void)
{
  CLEAR_BIT(PWR->CR4, PWR_CR4_C2BOOT);
}

/**
  * @brief  Check if bit to boot CPU2 after reset or wakeup from Stop or Standby
  *         modes is set
  * @note   CPU2 can boot from configuration of this function or from
  *         an illegal access. For information of boot source,
  *         refer to function @ref LL_PWR_IsActiveFlag_C2BOOTS().
  * @rmtoll CR4          C2BOOT        LL_PWR_IsEnabledBootC2
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBootC2(void)
{
  return ((READ_BIT(PWR->CR4, PWR_CR4_C2BOOT) == (PWR_CR4_C2BOOT)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup PWR_LL_EF_Configuration_CPU2 Configuration of CPU2, intended to be executed by CPU2
  * @{
  */

/**
  * @brief  Set Low-Power mode for CPU2
  * @rmtoll C2CR1        LPMS          LL_C2_PWR_SetPowerMode
  * @param  LowPowerMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_MODE_STOP0
  *         @arg @ref LL_PWR_MODE_STOP1
  *         @arg @ref LL_PWR_MODE_STOP2
  *         @arg @ref LL_PWR_MODE_STANDBY
  *         @arg @ref LL_PWR_MODE_SHUTDOWN
  * @retval None
  */
__STATIC_INLINE void LL_C2_PWR_SetPowerMode(uint32_t LowPowerMode)
{
  MODIFY_REG(PWR->C2CR1, PWR_C2CR1_LPMS, LowPowerMode);
}

/**
  * @brief  Get Low-Power mode for CPU2
  * @rmtoll C2CR1        LPMS          LL_C2_PWR_GetPowerMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_MODE_STOP0
  *         @arg @ref LL_PWR_MODE_STOP1
  *         @arg @ref LL_PWR_MODE_STOP2
  *         @arg @ref LL_PWR_MODE_STANDBY
  *         @arg @ref LL_PWR_MODE_SHUTDOWN
  */
__STATIC_INLINE uint32_t LL_C2_PWR_GetPowerMode(void)
{
  return (uint32_t)(READ_BIT(PWR->C2CR1, PWR_C2CR1_LPMS));
}

/**
  * @brief  Set flash power-down mode during low-power run mode for CPU2
  * @rmtoll C2CR1        FPDR          LL_C2_PWR_SetFlashPowerModeLPRun
  * @param  FlashLowPowerMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_FLASH_LPRUN_MODE_IDLE
  *         @arg @ref LL_PWR_FLASH_LPRUN_MODE_POWER_DOWN
  * @retval None
  */
__STATIC_INLINE void LL_C2_PWR_SetFlashPowerModeLPRun(uint32_t FlashLowPowerMode)
{
  /* Unlock bit FPDR */
  WRITE_REG(PWR->C2CR1, PWR_FLASH_POWER_MODE_UNLOCK_CODE);

  /* Update bit FPDR */
  MODIFY_REG(PWR->C2CR1, PWR_C2CR1_FPDR, FlashLowPowerMode);
}

/**
  * @brief  Get flash power-down mode during low-power run mode for CPU2
  * @rmtoll C2CR1        FPDR          LL_C2_PWR_GetFlashPowerModeLPRun
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_FLASH_LPRUN_MODE_IDLE
  *         @arg @ref LL_PWR_FLASH_LPRUN_MODE_POWER_DOWN
  */
__STATIC_INLINE uint32_t LL_C2_PWR_GetFlashPowerModeLPRun(void)
{
  return (uint32_t)(READ_BIT(PWR->C2CR1, PWR_C2CR1_FPDR));
}

/**
  * @brief  Set flash power-down mode during sleep mode for CPU2
  * @rmtoll C2CR1        FPDS          LL_C2_PWR_SetFlashPowerModeSleep
  * @param  FlashLowPowerMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_FLASH_SLEEP_MODE_IDLE
  *         @arg @ref LL_PWR_FLASH_SLEEP_MODE_POWER_DOWN
  * @retval None
  */
__STATIC_INLINE void LL_C2_PWR_SetFlashPowerModeSleep(uint32_t FlashLowPowerMode)
{
  MODIFY_REG(PWR->C2CR1, PWR_C2CR1_FPDS, FlashLowPowerMode);
}

/**
  * @brief  Get flash power-down mode during sleep mode for CPU2
  * @rmtoll C2CR1        FPDS          LL_C2_PWR_GetFlashPowerModeSleep
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_FLASH_SLEEP_MODE_IDLE
  *         @arg @ref LL_PWR_FLASH_SLEEP_MODE_POWER_DOWN
  */
__STATIC_INLINE uint32_t LL_C2_PWR_GetFlashPowerModeSleep(void)
{
  return (uint32_t)(READ_BIT(PWR->C2CR1, PWR_C2CR1_FPDS));
}


/**
  * @brief  Enable Internal Wake-up line for CPU2
  * @rmtoll C2CR3        EIWUL         LL_C2_PWR_EnableInternWU
  * @retval None
  */
__STATIC_INLINE void LL_C2_PWR_EnableInternWU(void)
{
  SET_BIT(PWR->C2CR3, PWR_C2CR3_EIWUL);
}

/**
  * @brief  Disable Internal Wake-up line for CPU2
  * @rmtoll C2CR3        EIWUL         LL_C2_PWR_DisableInternWU
  * @retval None
  */
__STATIC_INLINE void LL_C2_PWR_DisableInternWU(void)
{
  CLEAR_BIT(PWR->C2CR3, PWR_C2CR3_EIWUL);
}

/**
  * @brief  Check if Internal Wake-up line is enabled for CPU2
  * @rmtoll C2CR3        EIWUL         LL_C2_PWR_IsEnabledInternWU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C2_PWR_IsEnabledInternWU(void)
{
  return ((READ_BIT(PWR->C2CR3, PWR_C2CR3_EIWUL) == (PWR_C2CR3_EIWUL)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the WakeUp PINx functionality
  * @rmtoll C2CR3        EWUP1         LL_C2_PWR_EnableWakeUpPin\n
  *         C2CR3        EWUP2         LL_C2_PWR_EnableWakeUpPin\n
  *         C2CR3        EWUP3         LL_C2_PWR_EnableWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  * @retval None
  */
__STATIC_INLINE void LL_C2_PWR_EnableWakeUpPin(uint32_t WakeUpPin)
{
  SET_BIT(PWR->C2CR3, WakeUpPin);
}

/**
  * @brief  Disable the WakeUp PINx functionality
  * @rmtoll C2CR3        EWUP1         LL_C2_PWR_EnableWakeUpPin\n
  *         C2CR3        EWUP2         LL_C2_PWR_EnableWakeUpPin\n
  *         C2CR3        EWUP3         LL_C2_PWR_EnableWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  * @retval None
  */
__STATIC_INLINE void LL_C2_PWR_DisableWakeUpPin(uint32_t WakeUpPin)
{
  CLEAR_BIT(PWR->C2CR3, WakeUpPin);
}

/**
  * @brief  Check if the WakeUp PINx functionality is enabled
  * @rmtoll C2CR3        EWUP1         LL_C2_PWR_EnableWakeUpPin\n
  *         C2CR3        EWUP2         LL_C2_PWR_EnableWakeUpPin\n
  *         C2CR3        EWUP3         LL_C2_PWR_EnableWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  * @retval None
  */
__STATIC_INLINE uint32_t LL_C2_PWR_IsEnabledWakeUpPin(uint32_t WakeUpPin)
{
  return ((READ_BIT(PWR->C2CR3, WakeUpPin) == (WakeUpPin)) ? 1UL : 0UL);
}

/**
  * @brief  Enable pull-up and pull-down configuration for CPU2
  * @rmtoll C2CR3        APC           LL_C2_PWR_EnablePUPDCfg
  * @retval None
  */
__STATIC_INLINE void LL_C2_PWR_EnablePUPDCfg(void)
{
  SET_BIT(PWR->C2CR3, PWR_C2CR3_APC);
}

/**
  * @brief  Disable pull-up and pull-down configuration for CPU2
  * @rmtoll C2CR3        APC           LL_C2_PWR_DisablePUPDCfg
  * @retval None
  */
__STATIC_INLINE void LL_C2_PWR_DisablePUPDCfg(void)
{
  CLEAR_BIT(PWR->C2CR3, PWR_C2CR3_APC);
}

/**
  * @brief  Check if pull-up and pull-down configuration is enabled for CPU2
  * @rmtoll C2CR3        APC           LL_C2_PWR_IsEnabledPUPDCfg
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C2_PWR_IsEnabledPUPDCfg(void)
{
  return ((READ_BIT(PWR->C2CR3, PWR_C2CR3_APC) == (PWR_C2CR3_APC)) ? 1UL : 0UL);
}

/**
  * @brief  Enable wake-up power voltage detection with trigger for CPU2
  * @note   Wake-up power voltage detection status can be checked
  *         using function @ref LL_PWR_IsActiveFlag_WPVD().
  * @rmtoll C2CR3        EWPVD         LL_C2_PWR_EnableWPVD
  * @retval None
  */
__STATIC_INLINE void LL_C2_PWR_EnableWPVD(void)
{
  SET_BIT(PWR->C2CR3, PWR_C2CR3_EWPVD);
}

/**
  * @brief  Disable wake-up power voltage detection with trigger for CPU2
  * @rmtoll C2CR3        EWPVD         LL_C2_PWR_DisableWPVD
  * @retval None
  */
__STATIC_INLINE void LL_C2_PWR_DisableWPVD(void)
{
  CLEAR_BIT(PWR->C2CR3, PWR_C2CR3_EWPVD);
}

/**
  * @brief  Check if wake-up power voltage detection is enabled with trigger for CPU2
  * @rmtoll C2CR3        EWPVD         LL_C2_PWR_IsEnabledWPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C2_PWR_IsEnabledWPVD(void)
{
  return ((READ_BIT(PWR->C2CR3, PWR_C2CR3_EWPVD) == (PWR_C2CR3_EWPVD)) ? 1UL : 0UL);
}

/**
  * @brief  Enable CPU2 wake-up from low-power mode on illegal access occurrence
  * @note   Can be configured from CPU2 only
  * @rmtoll SECCFGR      C2EWILA       LL_PWR_C2_EnableWakeUp_ILAC
  * @retval None
  */
__STATIC_INLINE void LL_PWR_C2_EnableWakeUp_ILAC(void)
{
  SET_BIT(PWR->SECCFGR, PWR_SECCFGR_C2EWILA);
}

/**
  * @brief  Disable CPU2 wake-up from low-power mode on illegal access occurrence
  * @note   Can be configured from CPU2 only
  * @rmtoll SECCFGR      C2EWILA       LL_PWR_C2_DisableWakeUp_ILAC
  * @retval None
  */
__STATIC_INLINE void LL_PWR_C2_DisableWakeUp_ILAC(void)
{
  CLEAR_BIT(PWR->SECCFGR, PWR_SECCFGR_C2EWILA);
}

/**
  * @brief  Check if bit to wake-up CPU2 from low-power mode on illegal access
  *         occurrence is set
  * @note   Can be used from CPU2 only
  * @rmtoll SECCFGR      C2EWILA       LL_PWR_C2_IsEnabledWakeUp_ILAC
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_PWR_C2_IsEnabledWakeUp_ILAC(void)
{
  return ((READ_BIT(PWR->SECCFGR, PWR_SECCFGR_C2EWILA) == (PWR_SECCFGR_C2EWILA)) ? 1UL : 0UL);
}
#endif

/**
  * @}
  */

/** @defgroup PWR_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Get Internal Wake-up line Flag
  * @rmtoll SR1          WUFI          LL_PWR_IsActiveFlag_InternWU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_InternWU(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WUFI) == (PWR_SR1_WUFI)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 3
  * @rmtoll SR1          WUF3          LL_PWR_IsActiveFlag_WU3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU3(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WUF3) == (PWR_SR1_WUF3)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 2
  * @rmtoll SR1          WUF2          LL_PWR_IsActiveFlag_WU2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU2(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WUF2) == (PWR_SR1_WUF2)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 1
  * @rmtoll SR1          WUF1          LL_PWR_IsActiveFlag_WU1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU1(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WUF1) == (PWR_SR1_WUF1)) ? 1UL : 0UL);
}

/**
  * @brief  Clear Wake-up Flags
  * @rmtoll SCR          CWUF          LL_PWR_ClearFlag_WU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU(void)
{
  WRITE_REG(PWR->SCR, PWR_SCR_CWUF);
}

/**
  * @brief  Clear Wake-up Flag 3
  * @rmtoll SCR          CWUF3         LL_PWR_ClearFlag_WU3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU3(void)
{
  WRITE_REG(PWR->SCR, PWR_SCR_CWUF3);
}

/**
  * @brief  Clear Wake-up Flag 2
  * @rmtoll SCR          CWUF2         LL_PWR_ClearFlag_WU2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU2(void)
{
  WRITE_REG(PWR->SCR, PWR_SCR_CWUF2);
}

/**
  * @brief  Clear Wake-up Flag 1
  * @rmtoll SCR          CWUF1         LL_PWR_ClearFlag_WU1
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU1(void)
{
  WRITE_REG(PWR->SCR, PWR_SCR_CWUF1);
}

/**
  * @brief  Indicate whether VDDA voltage is below or above PVM3 threshold
  * @rmtoll SR2          PVMO3         LL_PWR_IsActiveFlag_PVMO3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_PVMO3(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_PVMO3) == (PWR_SR2_PVMO3)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether VDD voltage is below or above the selected PVD threshold
  * @rmtoll SR2          PVDO          LL_PWR_IsActiveFlag_PVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_PVDO(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_PVDO) == (PWR_SR2_PVDO)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether supply voltage is below radio operating level.
  * @rmtoll SR2          RFEOLF        LL_PWR_IsActiveFlag_RFEOL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_RFEOL(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_RFEOLF) == (PWR_SR2_RFEOLF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the regulator reached the selected voltage level
  * @note   Regulator voltage level is selected using function
  *         @ref LL_PWR_SetRegulVoltageScaling().
  * @rmtoll SR2          VOSF          LL_PWR_IsActiveFlag_VOS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VOS(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_VOSF) == (PWR_SR2_VOSF)) ? 1UL : 0UL);
}

/**
  * @brief  Get wake-up power voltage detection flag
  * @rmtoll SR1          WPVD          LL_PWR_IsActiveFlag_WPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WPVD(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WPVDF) == (PWR_SR1_WPVDF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear wake-up power voltage detection flag
  * @rmtoll SCR          CWPVD         LL_PWR_ClearFlag_WPVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WPVD(void)
{
  WRITE_REG(PWR->SCR, PWR_SCR_CWPVDF);
}

/**
  * @brief  Get main LDO ready flag
  * @rmtoll SR2          LDORDY        LL_PWR_IsActiveFlag_LDORDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_LDORDY(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_LDORDY) == (PWR_SR2_LDORDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the regulator is ready in main mode or is in low-power mode
  * @note   Return value "0" means the main regulator is ready and used. Return value "1" means the low-power regulator is used.
  * @rmtoll SR2          REGLPF        LL_PWR_IsActiveFlag_REGLPF
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_REGLPF(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_REGLPF) == (PWR_SR2_REGLPF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the low-power regulator is ready after a power-on
  *         reset, Standby or Shutdown mode.
  * @note   If the Standby mode is entered while REGLPS bit is still
  *         cleared (i.e. backup SRAM2 disabled), the wakeup time
  *         from Standby mode may be increased.
  * @note   Take care, return value "0" means the regulator is ready. Return value "1" means the output voltage range is still changing.
  * @rmtoll SR2          REGLPS        LL_PWR_IsActiveFlag_REGLPS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_REGLPS(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_REGLPS) == (PWR_SR2_REGLPS)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the main regulator is supplied from the LDO or SMPS
  *         or directly supplied from VDD.
  * @note   Return value "0" for main regulator supplied directly from VDD, return value "1" for main regulator supplied directly from LDO or SMPS.
  * @rmtoll SR2          REGMRS        LL_PWR_IsActiveFlag_REGMRS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_REGMRS(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_REGMRS) == (PWR_SR2_REGMRS)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the flash memory is ready
  * @rmtoll SR2          FLASHRDY      LL_PWR_IsActiveFlag_FLASHRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_FLASHRDY(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_FLASHRDY) == (PWR_SR2_FLASHRDY)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup PWR_LL_EF_FLAG_Management_SMPS FLAG management for SMPS
  * @{
  */

/**
  * @brief  Get SMPS ready flag
  * @rmtoll SR1          SMPSRDY       LL_PWR_IsActiveFlag_SMPSRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_SMPSRDY(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_SMPSRDY) == (PWR_SR2_SMPSRDY)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup PWR_LL_EF_FLAG_Management_Radio FLAG management for radio
  * @{
  */

/**
  * @brief  Get radio busy flag (triggered status: wake-up event
  *         or interruption occurred at least once. Can be cleared by software).
  * @note   This radio busy triggered status is based on radio busy masked
  *         signal.
  *         To get radio busy masked signal current status, use function
  *         @ref LL_PWR_IsActiveFlag_RFBUSYMS()
  * @rmtoll SR1          RFBUSYF       LL_PWR_IsActiveFlag_RFBUSY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_RFBUSY(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_WRFBUSYF) == (PWR_SR1_WRFBUSYF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear radio busy flag
  * @rmtoll SCR          CRFBUSYF      LL_PWR_ClearFlag_RFBUSY
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_RFBUSY(void)
{
  WRITE_REG(PWR->SCR, PWR_SCR_CWRFBUSYF);
}

/**
  * @brief  Get radio busy signal flag (current status:
  *         set and cleared by hardware reflecting the real time signal level).
  * @note   The get radio busy flag triggered status, use function
  *         @ref LL_PWR_IsActiveFlag_RFBUSY()
  * @rmtoll SR2          RFBUSYS       LL_PWR_IsActiveFlag_RFBUSYS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_RFBUSYS(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_RFBUSYS) == (PWR_SR2_RFBUSYS)) ? 1UL : 0UL);
}

/**
  * @brief  Get radio busy masked signal flag (current status:
  *         set and cleared by hardware reflecting the real time signal level).
  * @note   The get radio busy flag triggered status, use function
  *         @ref LL_PWR_IsActiveFlag_RFBUSY()
  * @rmtoll SR2          RFBUSYMS      LL_PWR_IsActiveFlag_RFBUSYMS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_RFBUSYMS(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_RFBUSYMS) == (PWR_SR2_RFBUSYMS)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup PWR_LL_EF_FLAG_Management_Multicore FLAG management for multicore
  * @{
  */

#if defined(DUAL_CORE)
/**
  * @brief  Get CPU2 hold interrupt flag
  * @rmtoll SR1          C2HF          LL_PWR_IsActiveFlag_C2H
  * @retval State of bit: 0 or 1 (CPU2 wake-up request and C2BOOT disabled,
  *         (except for illegal access wake-up),
  *         refer to function @ref LL_PWR_EnableBootC2()).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_C2H(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_C2HF) == (PWR_SR1_C2HF)) ? 1UL : 0UL);
}

/**
  * @brief  Get CPU2 boot or wake-up request source information
  * @rmtoll SR2          C2BOOTS       LL_PWR_IsActiveFlag_C2BOOTS
  * @retval State of bit: 0 (boot from an illegal access event)
  *         or 1 (boot from a SW request from function @ref LL_PWR_EnableBootC2()).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_C2BOOTS(void)
{
  return ((READ_BIT(PWR->SR2, PWR_SR2_C2BOOTS) == (PWR_SR2_C2BOOTS)) ? 1UL : 0UL);
}
#endif

/**
  * @brief  Get system Stop 0 or Stop 1 flag for CPU1
  * @rmtoll EXTSCR       C1STOPF       LL_PWR_IsActiveFlag_C1STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_C1STOP(void)
{
  return ((READ_BIT(PWR->EXTSCR, PWR_EXTSCR_C1STOPF) == (PWR_EXTSCR_C1STOPF)) ? 1UL : 0UL);
}

/**
  * @brief  Get system Stop 2 flag for CPU1
  * @rmtoll EXTSCR       C1STOP2F      LL_PWR_IsActiveFlag_C1STOP2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_C1STOP2(void)
{
  return ((READ_BIT(PWR->EXTSCR, PWR_EXTSCR_C1STOP2F) == (PWR_EXTSCR_C1STOP2F)) ? 1UL : 0UL);
}

/**
  * @brief  Get system Standby flag for CPU1
  * @rmtoll EXTSCR       C1SBF         LL_PWR_IsActiveFlag_C1SB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_C1SB(void)
{
  return ((READ_BIT(PWR->EXTSCR, PWR_EXTSCR_C1SBF) == (PWR_EXTSCR_C1SBF)) ? 1UL : 0UL);
}

/**
  * @brief  Get deepsleep mode for CPU1
  * @rmtoll EXTSCR       C1DS          LL_PWR_IsActiveFlag_C1DS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_C1DS(void)
{
  return ((READ_BIT(PWR->EXTSCR, PWR_EXTSCR_C1DS) == (PWR_EXTSCR_C1DS)) ? 1UL : 0UL);
}

#if defined(DUAL_CORE)
/**
  * @brief  System Stop 0 or Stop 1 flag for CPU2
  * @rmtoll EXTSCR       C2STOPF       LL_PWR_IsActiveFlag_C2STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_C2STOP(void)
{
  return ((READ_BIT(PWR->EXTSCR, PWR_EXTSCR_C2STOPF) == (PWR_EXTSCR_C2STOPF)) ? 1UL : 0UL);
}

/**
  * @brief  System Stop 2 flag for CPU2
  * @rmtoll EXTSCR       C2STOP2F      LL_PWR_IsActiveFlag_C2STOP2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_C2STOP2(void)
{
  return ((READ_BIT(PWR->EXTSCR, PWR_EXTSCR_C2STOP2F) == (PWR_EXTSCR_C2STOP2F)) ? 1UL : 0UL);
}

/**
  * @brief  System Standby flag for CPU2
  * @rmtoll EXTSCR       C2SBF         LL_PWR_IsActiveFlag_C2SB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_C2SB(void)
{
  return ((READ_BIT(PWR->EXTSCR, PWR_EXTSCR_C2SBF) == (PWR_EXTSCR_C2SBF)) ? 1UL : 0UL);
}

/**
  * @brief  Get deepsleep mode for CPU2
  * @rmtoll EXTSCR       C2DS          LL_PWR_IsActiveFlag_C2DS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_C2DS(void)
{
  return ((READ_BIT(PWR->EXTSCR, PWR_EXTSCR_C2DS) == (PWR_EXTSCR_C2DS)) ? 1UL : 0UL);
}

/**
  * @brief  Clear CPU2 hold interrupt flag
  * @rmtoll SCR          CC2HF         LL_PWR_ClearFlag_C2H
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_C2H(void)
{
  WRITE_REG(PWR->SCR, PWR_SCR_CC2HF);
}
#endif

/**
  * @brief  Clear standby and stop flags for CPU1
  * @rmtoll EXTSCR       C1CSSF        LL_PWR_ClearFlag_C1STOP_C1STB
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_C1STOP_C1STB(void)
{
  WRITE_REG(PWR->EXTSCR, PWR_EXTSCR_C1CSSF);
}

#if defined(DUAL_CORE)
/**
  * @brief  Clear standby and stop flags for CPU2
  * @rmtoll EXTSCR       C2CSSF        LL_PWR_ClearFlag_C2STOP_C2STB
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_C2STOP_C2STB(void)
{
  WRITE_REG(PWR->EXTSCR, PWR_EXTSCR_C2CSSF);
}
#endif

/**
  * @}
  */

#if defined(DUAL_CORE)
/** @defgroup PWR_LL_EF_IT_Management_Multicore PWR IT management for multicore
  * @{
  */

/**
  * @brief  Enable CPU2 hold interrupt for CPU1
  * @rmtoll CR3          EC2H          LL_PWR_EnableIT_HoldCPU2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableIT_HoldCPU2(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_EC2H);
}

/**
  * @brief  Disable CPU2 hold interrupt for CPU1
  * @rmtoll CR3          EC2H          LL_PWR_DisableIT_HoldCPU2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableIT_HoldCPU2(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_EC2H);
}

/**
  * @brief  Check if CPU2 hold interrupt is enabled for CPU2
  * @rmtoll CR3          EC2H          LL_PWR_IsEnabledIT_HoldCPU2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledIT_HoldCPU2(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_EC2H) == (PWR_CR3_EC2H)) ? 1UL : 0UL);
}

/**
  * @}
  */
#endif

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup PWR_LL_EF_Init De-initialization function
  * @{
  */
ErrorStatus LL_PWR_DeInit(void);
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

#endif /* defined(PWR) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32WLxx_LL_PWR_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
