/**
  ******************************************************************************
  * @file    stm32h7xx_ll_pwr.h
  * @author  MCD Application Team
  * @brief   Header file of PWR LL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics.
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
#ifndef STM32H7xx_LL_PWR_H
#define STM32H7xx_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx.h"

/** @addtogroup STM32H7xx_LL_Driver
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

/** @defgroup PWR_LL_WAKEUP_PIN_OFFSET Wake-Up Pins register offsets Defines
  * @brief    Flags defines which can be used with LL_PWR_WriteReg function
  * @{
  */
/* Wake-Up Pins PWR register offsets */
#define LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET    2UL
#define LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK       0x1FU
/**
  * @}
  */
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
#define LL_PWR_FLAG_CPU_CSSF          PWR_CPUCR_CSSF      /*!< Clear CPU STANDBY, STOP and HOLD flags */
#if defined (DUAL_CORE)
#define LL_PWR_FLAG_CPU2_CSSF         PWR_CPU2CR_CSSF     /*!< Clear CPU2 STANDBY, STOP and HOLD flags */
#endif /* DUAL_CORE */
#define LL_PWR_FLAG_WKUPCR_WKUPC6     PWR_WKUPCR_WKUPC6   /*!< Clear WKUP pin 6 */
#define LL_PWR_FLAG_WKUPCR_WKUPC5     PWR_WKUPCR_WKUPC5   /*!< Clear WKUP pin 5 */
#define LL_PWR_FLAG_WKUPCR_WKUPC4     PWR_WKUPCR_WKUPC4   /*!< Clear WKUP pin 4 */
#define LL_PWR_FLAG_WKUPCR_WKUPC3     PWR_WKUPCR_WKUPC3   /*!< Clear WKUP pin 3 */
#define LL_PWR_FLAG_WKUPCR_WKUPC2     PWR_WKUPCR_WKUPC2   /*!< Clear WKUP pin 2 */
#define LL_PWR_FLAG_WKUPCR_WKUPC1     PWR_WKUPCR_WKUPC1   /*!< Clear WKUP pin 1 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_PWR_ReadReg function
  * @{
  */
#define LL_PWR_FLAG_AVDO              PWR_CSR1_AVDO       /*!< Analog Voltage Detect Output */
#define LL_PWR_FLAG_PVDO              PWR_CSR1_PVDO       /*!< Power voltage detector output flag */
#define LL_PWR_FLAG_ACTVOS            PWR_CSR1_ACTVOS     /*!< Current actual used VOS for VDD11 Voltage Scaling */
#define LL_PWR_FLAG_ACTVOSRDY         PWR_CSR1_ACTVOSRDY  /*!< Ready bit for current actual used VOS for VDD11 Voltage Scaling */

#define LL_PWR_FLAG_TEMPH             PWR_CR2_TEMPH       /*!< Temperature high threshold flag */
#define LL_PWR_FLAG_TEMPL             PWR_CR2_TEMPL       /*!< Temperature low threshold flag */
#define LL_PWR_FLAG_VBATH             PWR_CR2_VBATH       /*!< VBAT high threshold flag */
#define LL_PWR_FLAG_VBATL             PWR_CR2_VBATL       /*!< VBAT low threshold flag */
#define LL_PWR_FLAG_BRRDY             PWR_CR2_BRRDY       /*!< Backup Regulator ready flag */

#define LL_PWR_FLAG_USBRDY            PWR_CR3_USB33RDY    /*!< USB supply ready flag */
#define LL_PWR_FLAG_SMPSEXTRDY        PWR_CR3_SMPSEXTRDY  /*!< SMPS External supply ready flag */

#define LL_PWR_FLAG_CPU_SBF_D2        PWR_CPUCR_SBF_D2    /*!< D2 domain DSTANDBY Flag */
#define LL_PWR_FLAG_CPU_SBF_D1        PWR_CPUCR_SBF_D1    /*!< D1 domain DSTANDBY Flag */
#define LL_PWR_FLAG_CPU_SBF           PWR_CPUCR_SBF       /*!< System STANDBY Flag */
#define LL_PWR_FLAG_CPU_STOPF         PWR_CPUCR_STOPF     /*!< STOP Flag */
#if defined (DUAL_CORE)
#define LL_PWR_FLAG_CPU_HOLD2F        PWR_CPUCR_HOLD2F    /*!< CPU2 in hold wakeup flag */
#endif /* DUAL_CORE */

#if defined (DUAL_CORE)
#define LL_PWR_FLAG_CPU2_SBF_D2       PWR_CPU2CR_SBF_D2   /*!< D2 domain DSTANDBY Flag */
#define LL_PWR_FLAG_CPU2_SBF_D1       PWR_CPU2CR_SBF_D1   /*!< D1 domain DSTANDBY Flag */
#define LL_PWR_FLAG_CPU2_SBF          PWR_CPU2CR_SBF      /*!< System STANDBY Flag */
#define LL_PWR_FLAG_CPU2_STOPF        PWR_CPU2CR_STOPF    /*!< STOP Flag */
#define LL_PWR_FLAG_CPU2_HOLD1F       PWR_CPU2CR_HOLD1F   /*!< CPU1 in hold wakeup flag */
#endif /* DUAL_CORE */

#define LL_PWR_D3CR_VOSRDY            PWR_D3CR_VOSRDY     /*!< Voltage scaling ready flag */

#define LL_PWR_WKUPFR_WKUPF6          PWR_WKUPFR_WKUPF6   /*!< Wakeup Pin Flag 6 */
#define LL_PWR_WKUPFR_WKUPF5          PWR_WKUPFR_WKUPF5   /*!< Wakeup Pin Flag 5 */
#define LL_PWR_WKUPFR_WKUPF4          PWR_WKUPFR_WKUPF4   /*!< Wakeup Pin Flag 4 */
#define LL_PWR_WKUPFR_WKUPF3          PWR_WKUPFR_WKUPF3   /*!< Wakeup Pin Flag 3 */
#define LL_PWR_WKUPFR_WKUPF2          PWR_WKUPFR_WKUPF2   /*!< Wakeup Pin Flag 2 */
#define LL_PWR_WKUPFR_WKUPF1          PWR_WKUPFR_WKUPF1   /*!< Wakeup Pin Flag 1 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_MODE_PWR Power mode
  * @{
  */
#define LL_PWR_CPU_MODE_D1STOP        0x00000000U           /*!< Enter D1 domain to Stop mode when the CPU enters deepsleep */
#define LL_PWR_CPU_MODE_D1STANDBY     PWR_CPUCR_PDDS_D1     /*!< Enter D1 domain to Standby mode when the CPU enters deepsleep */
#define LL_PWR_CPU_MODE_D2STOP        0x00000000U           /*!< Enter Stop mode when the CPU enters deepsleep */
#define LL_PWR_CPU_MODE_D2STANDBY     PWR_CPUCR_PDDS_D2     /*!< Enter D3 domain to Standby mode when the CPU enters deepsleep */
#define LL_PWR_CPU_MODE_D3STOP        0x00000000U           /*!< Enter Stop mode when the CPU enters deepsleep */
#define LL_PWR_CPU_MODE_D3STANDBY     PWR_CPUCR_PDDS_D3     /*!< Enter D3 domain to Standby mode when the CPU enter deepsleep */
#define LL_PWR_CPU_MODE_D3RUN         PWR_CPUCR_RUN_D3      /*!< Keep system D3 domain in RUN mode when the CPU enter deepsleep */

#if defined (DUAL_CORE)
#define LL_PWR_CPU2_MODE_D1STOP       0x00000000U           /*!< Enter D1 domain to Stop mode when the CPU2 enters deepsleep */
#define LL_PWR_CPU2_MODE_D1STANDBY    PWR_CPU2CR_PDDS_D1    /*!< Enter D1 domain to Standby mode when the CPU2 enters deepsleep */
#define LL_PWR_CPU2_MODE_D2STOP       0x00000000U           /*!< Enter Stop mode when the CPU2 enters deepsleep */
#define LL_PWR_CPU2_MODE_D2STANDBY    PWR_CPU2CR_PDDS_D2    /*!< Enter D3 domain to Standby mode when the CPU2 enters deepsleep */
#define LL_PWR_CPU2_MODE_D3STOP       0x00000000U           /*!< Enter Stop mode when the CPU2 enters deepsleep */
#define LL_PWR_CPU2_MODE_D3STANDBY    PWR_CPU2CR_PDDS_D3    /*!< Enter D3 domain to Standby mode when the CPU2 enter deepsleep */
#define LL_PWR_CPU2_MODE_D3RUN        PWR_CPU2CR_RUN_D3     /*!< Keep system D3 domain in RUN mode when the CPU2 enter deepsleep */
#endif /* DUAL_CORE */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_REGU_VOLTAGE Run mode Regulator Voltage Scaling
  * @{
  */
#define LL_PWR_REGU_VOLTAGE_SCALE3      PWR_D3CR_VOS_0                    /* Select voltage scale 3 */
#define LL_PWR_REGU_VOLTAGE_SCALE2      PWR_D3CR_VOS_1                    /* Select voltage scale 2 */
#define LL_PWR_REGU_VOLTAGE_SCALE1      (PWR_D3CR_VOS_0 | PWR_D3CR_VOS_1) /* Select voltage scale 1 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_STOP_MODE_REGU_VOLTAGE Stop mode Regulator Voltage Scaling
  * @{
  */
#define LL_PWR_REGU_VOLTAGE_SVOS_SCALE5   PWR_CR1_SVOS_0                    /* Select voltage scale 5 when system enters STOP mode */
#define LL_PWR_REGU_VOLTAGE_SVOS_SCALE4   PWR_CR1_SVOS_1                    /* Select voltage scale 4 when system enters STOP mode */
#define LL_PWR_REGU_VOLTAGE_SVOS_SCALE3   (PWR_CR1_SVOS_0 | PWR_CR1_SVOS_1) /* Select voltage scale 3 when system enters STOP mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_REGU_MODE_DS_MODE  Regulator Mode In Deep Sleep Mode
  * @{
  */
#define LL_PWR_REGU_DSMODE_MAIN           0x00000000U   /*!< Voltage Regulator in main mode during deepsleep mode */
#define LL_PWR_REGU_DSMODE_LOW_POWER      PWR_CR1_LPDS  /*!< Voltage Regulator in low-power mode during deepsleep mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PVDLEVEL Power Digital Voltage Level Detector
  * @{
  */
#define LL_PWR_PVDLEVEL_0   PWR_CR1_PLS_LEV0  /*!< Voltage threshold detected by PVD 1.95 V */
#define LL_PWR_PVDLEVEL_1   PWR_CR1_PLS_LEV1  /*!< Voltage threshold detected by PVD 2.1 V  */
#define LL_PWR_PVDLEVEL_2   PWR_CR1_PLS_LEV2  /*!< Voltage threshold detected by PVD 2.25 V */
#define LL_PWR_PVDLEVEL_3   PWR_CR1_PLS_LEV3  /*!< Voltage threshold detected by PVD 2.4 V  */
#define LL_PWR_PVDLEVEL_4   PWR_CR1_PLS_LEV4  /*!< Voltage threshold detected by PVD 2.55 V */
#define LL_PWR_PVDLEVEL_5   PWR_CR1_PLS_LEV5  /*!< Voltage threshold detected by PVD 2.7 V  */
#define LL_PWR_PVDLEVEL_6   PWR_CR1_PLS_LEV6  /*!< Voltage threshold detected by PVD 2.85 V */
#define LL_PWR_PVDLEVEL_7   PWR_CR1_PLS_LEV7  /*!< External voltage level on PVD_IN pin, compared to internal VREFINT level. */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_AVDLEVEL Power Analog Voltage Level Detector
  * @{
  */
#define LL_PWR_AVDLEVEL_0   PWR_CR1_ALS_LEV0  /*!< Analog Voltage threshold detected by AVD 1.7 V */
#define LL_PWR_AVDLEVEL_1   PWR_CR1_ALS_LEV1  /*!< Analog Voltage threshold detected by AVD 2.1 V */
#define LL_PWR_AVDLEVEL_2   PWR_CR1_ALS_LEV2  /*!< Analog Voltage threshold detected by AVD 2.5 V */
#define LL_PWR_AVDLEVEL_3   PWR_CR1_ALS_LEV3  /*!< Analog Voltage threshold detected by AVD 2.8 V */

/**
  * @}
  */

/** @defgroup PWR_LL_EC_BATT_CHARG_RESISTOR Battery Charge Resistor
  * @{
  */
#define LL_PWR_BATT_CHARG_RESISTOR_5K     0x00000000U   /*!< Charge the Battery through a 5 kO resistor  */
#define LL_PWR_BATT_CHARGRESISTOR_1_5K    PWR_CR3_VBRS  /*!< Charge the Battery through a 1.5 kO resistor  */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN  Wakeup Pins
  * @{
  */
#define LL_PWR_WAKEUP_PIN1    PWR_WKUPEPR_WKUPEN1  /*!< Wake-Up pin 1 : PA0  */
#define LL_PWR_WAKEUP_PIN2    PWR_WKUPEPR_WKUPEN2  /*!< Wake-Up pin 2 : PA2  */
#define LL_PWR_WAKEUP_PIN3    PWR_WKUPEPR_WKUPEN3  /*!< Wake-Up pin 3 : PC1  */
#define LL_PWR_WAKEUP_PIN4    PWR_WKUPEPR_WKUPEN4  /*!< Wake-Up pin 4 : PC13 */
#define LL_PWR_WAKEUP_PIN5    PWR_WKUPEPR_WKUPEN5  /*!< Wake-Up pin 5 : PI8  */
#define LL_PWR_WAKEUP_PIN6    PWR_WKUPEPR_WKUPEN6  /*!< Wake-Up pin 6 : PI11 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN_PULL  Wakeup Pins pull configuration
  * @{
  */
#define LL_PWR_WAKEUP_PIN_NOPULL      0x00000000UL   /*!< Configure Wake-Up pin in no pull */
#define LL_PWR_WAKEUP_PIN_PULLUP      0x00000001UL   /*!< Configure Wake-Up pin in pull Up */
#define LL_PWR_WAKEUP_PIN_PULLDOWN    0x00000002UL   /*!< Configure Wake-Up pin in pull Down */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SUPPLY_PWR Power supply source configuration
  * @{
  */
#define LL_PWR_LDO_SUPPLY                     PWR_CR3_LDOEN   /* Core domains are suppplied from the LDO */
#if defined (SMPS)
#define LL_PWR_DIRECT_SMPS_SUPPLY             PWR_CR3_SMPSEN  /* Core domains are suppplied from the SMPS */
#define LL_PWR_SMPS_1V8_SUPPLIES_LDO          (PWR_CR3_SMPSLEVEL_0 | PWR_CR3_SMPSEN | PWR_CR3_LDOEN)  /* The SMPS 1.8V output supplies the LDO which supplies the Core domains */
#define LL_PWR_SMPS_2V5_SUPPLIES_LDO          (PWR_CR3_SMPSLEVEL_1 | PWR_CR3_SMPSEN | PWR_CR3_LDOEN)  /* The SMPS 2.5V output supplies the LDO which supplies the Core domains */
#define LL_PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO  (PWR_CR3_SMPSLEVEL_0 | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_LDOEN)  /* The SMPS 1.8V output supplies an external circuits and the LDO. The Core domains are suppplied from the LDO */
#define LL_PWR_SMPS_2V5_SUPPLIES_EXT_AND_LDO  (PWR_CR3_SMPSLEVEL_1 | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_LDOEN)  /* The SMPS 2.5V output supplies an external circuits and the LDO. The Core domains are suppplied from the LDO */
#define LL_PWR_SMPS_1V8_SUPPLIES_EXT          (PWR_CR3_SMPSLEVEL_0 | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_BYPASS) /* The SMPS 1.8V output supplies an external source which supplies the Core domains */
#define LL_PWR_SMPS_2V5_SUPPLIES_EXT          (PWR_CR3_SMPSLEVEL_1 | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_BYPASS) /* The SMPS 2.5V output supplies an external source which supplies the Core domains */
#endif /* SMPS */
#define LL_PWR_EXTERNAL_SOURCE_SUPPLY         PWR_CR3_BYPASS  /* The SMPS and the LDO are Bypassed. The Core domains are supplied from an external source */
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

/** @defgroup PWR_LL_EM_WRITE_READ Common write and read registers Macros
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
  * @brief  Set the voltage Regulator mode during deep sleep mode
  * @rmtoll CR1    LPDS         LL_PWR_SetRegulModeDS
  * @param  RegulMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_REGU_DSMODE_MAIN
  *         @arg @ref LL_PWR_REGU_DSMODE_LOW_POWER
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRegulModeDS(uint32_t RegulMode)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_LPDS, RegulMode);
}

/**
  * @brief  Get the voltage Regulator mode during deep sleep mode
  * @rmtoll CR1    LPDS         LL_PWR_GetRegulModeDS
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_DSMODE_MAIN
  *         @arg @ref LL_PWR_REGU_DSMODE_LOW_POWER
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulModeDS(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_LPDS));
}

/**
  * @brief  Enable Power Voltage Detector
  * @rmtoll CR1    PVDEN       LL_PWR_EnablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_PVDEN);
}

/**
  * @brief  Disable Power Voltage Detector
  * @rmtoll CR1    PVDEN       LL_PWR_DisablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_PVDEN);
}

/**
  * @brief  Check if Power Voltage Detector is enabled
  * @rmtoll CR1    PVDEN       LL_PWR_IsEnabledPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_PVDEN) == (PWR_CR1_PVDEN)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the voltage threshold detected by the Power Voltage Detector
  * @rmtoll CR1    PLS       LL_PWR_SetPVDLevel
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
  MODIFY_REG(PWR->CR1, PWR_CR1_PLS, PVDLevel);
}

/**
  * @brief  Get the voltage threshold detection
  * @rmtoll CR1    PLS       LL_PWR_GetPVDLevel
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
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_PLS));
}

/**
  * @brief  Enable access to the backup domain
  * @rmtoll CR1    DBP       LL_PWR_EnableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBkUpAccess(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @brief  Disable access to the backup domain
  * @rmtoll CR1    DBP       LL_PWR_DisableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBkUpAccess(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @brief  Check if the backup domain is enabled
  * @rmtoll CR1    DBP       LL_PWR_IsEnabledBkUpAccess
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBkUpAccess(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_DBP) == (PWR_CR1_DBP)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the Flash Power Down in Stop Mode
  * @rmtoll CR1    FLPS       LL_PWR_EnableFlashPowerDown
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableFlashPowerDown(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_FLPS);
}

/**
  * @brief  Disable the Flash Power Down in Stop Mode
  * @rmtoll CR1    FLPS       LL_PWR_DisableFlashPowerDown
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableFlashPowerDown(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_FLPS);
}

/**
  * @brief  Check if the Flash Power Down in Stop Mode is enabled
  * @rmtoll CR1    FLPS       LL_PWR_IsEnabledFlashPowerDown
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledFlashPowerDown(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_FLPS) == (PWR_CR1_FLPS)) ? 1UL : 0UL);
}

/**
  * @brief  Set the internal Regulator output voltage in STOP mode
  * @rmtoll CR1    SVOS       LL_PWR_SetStopModeRegulVoltageScaling
  * @param  VoltageScaling This parameter can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SVOS_SCALE3
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SVOS_SCALE4
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SVOS_SCALE5
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetStopModeRegulVoltageScaling(uint32_t VoltageScaling)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_SVOS, VoltageScaling);
}

/**
  * @brief  Get the internal Regulator output voltage in STOP mode
  * @rmtoll CR1    SVOS       LL_PWR_GetStopModeRegulVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SVOS_SCALE3
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SVOS_SCALE4
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SVOS_SCALE5
  */
__STATIC_INLINE uint32_t LL_PWR_GetStopModeRegulVoltageScaling(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_SVOS));
}

/**
  * @brief  Enable Analog Power Voltage Detector
  * @rmtoll CR1    AVDEN       LL_PWR_EnableAVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableAVD(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_AVDEN);
}

/**
  * @brief  Disable Analog Power Voltage Detector
  * @rmtoll CR1    AVDEN       LL_PWR_DisableAVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableAVD(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_AVDEN);
}

/**
  * @brief  Check if Analog Power Voltage Detector is enabled
  * @rmtoll CR1    AVDEN       LL_PWR_IsEnabledAVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledAVD(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_AVDEN) == (PWR_CR1_AVDEN)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the voltage threshold to be detected by the Analog Power Voltage Detector
  * @rmtoll CR1    ALS       LL_PWR_SetAVDLevel
  * @param  AVDLevel This parameter can be one of the following values:
  *         @arg @ref LL_PWR_AVDLEVEL_0
  *         @arg @ref LL_PWR_AVDLEVEL_1
  *         @arg @ref LL_PWR_AVDLEVEL_2
  *         @arg @ref LL_PWR_AVDLEVEL_3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetAVDLevel(uint32_t AVDLevel)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_ALS, AVDLevel);
}

/**
  * @brief  Get the Analog Voltage threshold to be detected by the Analog Power Voltage Detector
  * @rmtoll CR1    ALS       LL_PWR_GetAVDLevel
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_AVDLEVEL_0
  *         @arg @ref LL_PWR_AVDLEVEL_1
  *         @arg @ref LL_PWR_AVDLEVEL_2
  *         @arg @ref LL_PWR_AVDLEVEL_3
  */
__STATIC_INLINE uint32_t LL_PWR_GetAVDLevel(void)
{
  return (uint32_t)(READ_BIT(PWR->CR1, PWR_CR1_ALS));
}

/**
  * @brief  Enable Backup Regulator
  * @rmtoll CR2    BREN       LL_PWR_EnableBkUpRegulator
  * @note When set, the Backup Regulator (used to maintain backup SRAM content in Standby and
  *       VBAT modes) is enabled. If BRE is reset, the backup Regulator is switched off. The backup
  *       SRAM can still be used but its content will be lost in the Standby and VBAT modes. Once set,
  *       the application must wait that the Backup Regulator Ready flag (BRR) is set to indicate that
  *       the data written into the RAM will be maintained in the Standby and VBAT modes.
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBkUpRegulator(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_BREN);
}

/**
  * @brief  Disable Backup Regulator
  * @rmtoll CR2    BREN       LL_PWR_DisableBkUpRegulator
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBkUpRegulator(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_BREN);
}

/**
  * @brief  Check if the backup Regulator is enabled
  * @rmtoll CR2    BREN      LL_PWR_IsEnabledBkUpRegulator
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBkUpRegulator(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_BREN) == (PWR_CR2_BREN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable VBAT and Temperature monitoring
  * @rmtoll CR2    MONEN       LL_PWR_EnableMonitoring
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableMonitoring(void)
{
  SET_BIT(PWR->CR2, PWR_CR2_MONEN);
}

/**
  * @brief  Disable VBAT and Temperature monitoring
  * @rmtoll CR2    MONEN       LL_PWR_DisableMonitoring
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableMonitoring(void)
{
  CLEAR_BIT(PWR->CR2, PWR_CR2_MONEN);
}

/**
  * @brief  Check if the VBAT and Temperature monitoring is enabled
  * @rmtoll CR2    MONEN      LL_PWR_IsEnabledMonitoring
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledMonitoring(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_MONEN) == (PWR_CR2_MONEN)) ? 1UL : 0UL);
}

#if defined (SMPS)
/**
  * @brief  Configure the PWR supply
  * @rmtoll CR3          BYPASS          LL_PWR_ConfigSupply
  * @rmtoll CR3          LDOEN           LL_PWR_ConfigSupply
  * @rmtoll CR3          SMPSEN          LL_PWR_ConfigSupply
  * @rmtoll CR3          SMPSEXTHP       LL_PWR_ConfigSupply
  * @rmtoll CR3          SMPSLEVEL       LL_PWR_ConfigSupply
  * @param  SupplySource This parameter can be one of the following values:
  *         @arg @ref LL_PWR_LDO_SUPPLY
  *         @arg @ref LL_PWR_DIRECT_SMPS_SUPPLY
  *         @arg @ref LL_PWR_SMPS_1V8_SUPPLIES_LDO
  *         @arg @ref LL_PWR_SMPS_2V5_SUPPLIES_LDO
  *         @arg @ref LL_PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO
  *         @arg @ref LL_PWR_SMPS_2V5_SUPPLIES_EXT_AND_LDO
  *         @arg @ref LL_PWR_SMPS_1V8_SUPPLIES_EXT
  *         @arg @ref LL_PWR_SMPS_2V5_SUPPLIES_EXT
  *         @arg @ref LL_PWR_EXTERNAL_SOURCE_SUPPLY
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ConfigSupply(uint32_t SupplySource)
{
  /* Set the power supply configuration */
  MODIFY_REG(PWR->CR3, (PWR_CR3_SMPSLEVEL | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_LDOEN | PWR_CR3_BYPASS), SupplySource);
}
#else
/**
  * @brief  Configure the PWR supply
  * @rmtoll CR3          BYPASS          LL_PWR_ConfigSupply
  * @rmtoll CR3          LDOEN           LL_PWR_ConfigSupply
  * @rmtoll CR3          SCUEN           LL_PWR_ConfigSupply
  * @param  SupplySource This parameter can be one of the following values:
  *         @arg @ref LL_PWR_LDO_SUPPLY
  *         @arg @ref LL_PWR_EXTERNAL_SOURCE_SUPPLY
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ConfigSupply(uint32_t SupplySource)
{
  /* Set the power supply configuration */
  MODIFY_REG(PWR->CR3, (PWR_CR3_SCUEN | PWR_CR3_LDOEN | PWR_CR3_BYPASS), SupplySource);
}
#endif /* SMPS */

#if defined(SMPS)
/**
  * @brief  Get the PWR supply
  * @rmtoll CR3          BYPASS          LL_PWR_GetSupply
  * @rmtoll CR3          LDOEN           LL_PWR_GetSupply
  * @rmtoll CR3          SMPSEN          LL_PWR_GetSupply
  * @rmtoll CR3          SMPSEXTHP       LL_PWR_GetSupply
  * @rmtoll CR3          SMPSLEVEL       LL_PWR_GetSupply
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_LDO_SUPPLY
  *         @arg @ref LL_PWR_DIRECT_SMPS_SUPPLY
  *         @arg @ref LL_PWR_SMPS_1V8_SUPPLIES_LDO
  *         @arg @ref LL_PWR_SMPS_2V5_SUPPLIES_LDO
  *         @arg @ref LL_PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO
  *         @arg @ref LL_PWR_SMPS_2V5_SUPPLIES_EXT_AND_LDO
  *         @arg @ref LL_PWR_SMPS_1V8_SUPPLIES_EXT
  *         @arg @ref LL_PWR_SMPS_2V5_SUPPLIES_EXT
  *         @arg @ref LL_PWR_EXTERNAL_SOURCE_SUPPLY
  */
__STATIC_INLINE uint32_t LL_PWR_GetSupply(void)
{
  /* Get the power supply configuration */
  return(uint32_t)(READ_BIT(PWR->CR3, (PWR_CR3_SMPSLEVEL | PWR_CR3_SMPSEXTHP | PWR_CR3_SMPSEN | PWR_CR3_LDOEN | PWR_CR3_BYPASS)));
}

#else

/**
  * @brief  Get the PWR supply
  * @rmtoll CR3          BYPASS          LL_PWR_GetSupply
  * @rmtoll CR3          LDOEN           LL_PWR_GetSupply
  * @rmtoll CR3          SCUEN           LL_PWR_GetSupply
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_LDO_SUPPLY
  *         @arg @ref LL_PWR_EXTERNAL_SOURCE_SUPPLY
  */
__STATIC_INLINE uint32_t LL_PWR_GetSupply(void)
{
  /* Get the power supply configuration */
  return(uint32_t)(READ_BIT(PWR->CR3, (PWR_CR3_SCUEN | PWR_CR3_LDOEN | PWR_CR3_BYPASS)));
}
#endif /* SMPS */

/**
  * @brief  Enable battery charging
  * @rmtoll CR3          VBE           LL_PWR_EnableBatteryCharging
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBatteryCharging(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_VBE);
}

/**
  * @brief  Disable battery charging
  * @rmtoll CR3          VBE           LL_PWR_DisableBatteryCharging
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBatteryCharging(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_VBE);
}

/**
  * @brief  Check if battery charging is enabled
  * @rmtoll CR3          VBE           LL_PWR_IsEnabledBatteryCharging
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBatteryCharging(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_VBE) == (PWR_CR3_VBE)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Battery charge resistor impedance
  * @rmtoll CR3          VBRS          LL_PWR_SetBattChargResistor
  * @param  Resistor This parameter can be one of the following values:
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_5K
  *         @arg @ref LL_PWR_BATT_CHARGRESISTOR_1_5K
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetBattChargResistor(uint32_t Resistor)
{
  MODIFY_REG(PWR->CR3, PWR_CR3_VBRS, Resistor);
}

/**
  * @brief  Get the Battery charge resistor impedance
  * @rmtoll CR3          VBRS          LL_PWR_GetBattChargResistor
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_5K
  *         @arg @ref LL_PWR_BATT_CHARGRESISTOR_1_5K
  */
__STATIC_INLINE uint32_t LL_PWR_GetBattChargResistor(void)
{
  return (uint32_t)(READ_BIT(PWR->CR3, PWR_CR3_VBRS));
}

/**
  * @brief  Enable the USB regulator
  * @rmtoll CR3          USBREGEN           LL_PWR_EnableUSBReg
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableUSBReg(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_USBREGEN);
}

/**
  * @brief  Disable the USB regulator
  * @rmtoll CR3          USBREGEN           LL_PWR_DisableUSBReg
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableUSBReg(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_USBREGEN);
}

/**
  * @brief  Check if the USB regulator is enabled
  * @rmtoll CR3          USBREGEN           LL_PWR_IsEnabledUSBReg
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUSBReg(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_USBREGEN) == (PWR_CR3_USBREGEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the USB voltage detector
  * @rmtoll CR3          USB33DEN           LL_PWR_EnableUSBVoltageDetector
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableUSBVoltageDetector(void)
{
  SET_BIT(PWR->CR3, PWR_CR3_USB33DEN);
}

/**
  * @brief  Disable the USB voltage detector
  * @rmtoll CR3          USB33DEN           LL_PWR_DisableUSBVoltageDetector
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableUSBVoltageDetector(void)
{
  CLEAR_BIT(PWR->CR3, PWR_CR3_USB33DEN);
}

/**
  * @brief  Check if the USB voltage detector is enabled
  * @rmtoll CR3          USB33DEN           LL_PWR_IsEnabledUSBVoltageDetector
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUSBVoltageDetector(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_USB33DEN) == (PWR_CR3_USB33DEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the D1 domain Power Down mode when the CPU enters deepsleep
  * @rmtoll CPUCR     PDDS_D1       LL_PWR_CPU_SetD1PowerMode\n
  * @param  PDMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_CPU_MODE_D1STOP
  *         @arg @ref LL_PWR_CPU_MODE_D1STANDBY
  * @retval None
  */
__STATIC_INLINE void LL_PWR_CPU_SetD1PowerMode(uint32_t PDMode)
{
  MODIFY_REG(PWR->CPUCR, PWR_CPUCR_PDDS_D1, PDMode);
}

#if defined (DUAL_CORE)
/**
  * @brief  Set the D1 domain Power Down mode when the CPU2 enters deepsleep
  * @rmtoll CPU2CR     PDDS_D1       LL_PWR_CPU2_SetD1PowerMode\n
  * @param  PDMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_CPU2_MODE_D1STOP
  *         @arg @ref LL_PWR_CPU2_MODE_D1STANDBY
  * @retval None
  */
__STATIC_INLINE void LL_PWR_CPU2_SetD1PowerMode(uint32_t PDMode)
{
  MODIFY_REG(PWR->CPU2CR, PWR_CPU2CR_PDDS_D1, PDMode);
}
#endif /* DUAL_CORE */

/**
  * @brief  Get the D1 Domain Power Down mode when the CPU enters deepsleep
  * @rmtoll CPUCR     PDDS_D1       LL_PWR_CPU_GetD1PowerMode\n
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_CPU_MODE_D1STOP
  *         @arg @ref LL_PWR_CPU_MODE_D1STANDBY
  */
__STATIC_INLINE uint32_t LL_PWR_CPU_GetD1PowerMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CPUCR, PWR_CPUCR_PDDS_D1));
}

#if defined (DUAL_CORE)
/**
  * @brief  Get the D1 Domain Power Down mode when the CPU2 enters deepsleep
  * @rmtoll CPU2CR     PDDS_D1       LL_PWR_CPU2_GetD1PowerMode\n
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_CPU2_MODE_D1STOP
  *         @arg @ref LL_PWR_CPU2_MODE_D1STANDBY
  */
__STATIC_INLINE uint32_t LL_PWR_CPU2_GetD1PowerMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CPU2CR, PWR_CPU2CR_PDDS_D1));
}
#endif /* DUAL_CORE */

/**
  * @brief  Set the D2 domain Power Down mode when the CPU enters deepsleep
  * @rmtoll CPUCR     PDDS_D2       LL_PWR_CPU_SetD2PowerMode\n
  * @param  PDMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_CPU_MODE_D2STOP
  *         @arg @ref LL_PWR_CPU_MODE_D2STANDBY
  * @retval None
  */
__STATIC_INLINE void LL_PWR_CPU_SetD2PowerMode(uint32_t PDMode)
{
  MODIFY_REG(PWR->CPUCR, PWR_CPUCR_PDDS_D2, PDMode);
}

#if defined (DUAL_CORE)
/**
  * @brief  Set the D2 domain Power Down mode when the CPU2 enters deepsleep
  * @rmtoll CPU2CR     PDDS_D2       LL_PWR_CPU2_SetD2PowerMode\n
  * @param  PDMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_CPU2_MODE_D2STOP
  *         @arg @ref LL_PWR_CPU2_MODE_D2STANDBY
  * @retval None
  */
__STATIC_INLINE void LL_PWR_CPU2_SetD2PowerMode(uint32_t PDMode)
{
  MODIFY_REG(PWR->CPU2CR, PWR_CPU2CR_PDDS_D2, PDMode);
}
#endif /* DUAL_CORE */

/**
  * @brief  Get the D2 Domain Power Down mode when the CPU enters deepsleep
  * @rmtoll CPUCR     PDDS_D2       LL_PWR_CPU_GetD2PowerMode\n
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_CPU_MODE_D2STOP
  *         @arg @ref LL_PWR_CPU_MODE_D2STANDBY
  */
__STATIC_INLINE uint32_t LL_PWR_CPU_GetD2PowerMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CPUCR, PWR_CPUCR_PDDS_D2));
}

#if defined (DUAL_CORE)
/**
  * @brief  Get the D2 Domain Power Down mode when the CPU2 enters deepsleep
  * @rmtoll CPU2CR     PDDS_D2       LL_PWR_CPU2_GetD2PowerMode\n
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_CPU2_MODE_D2STOP
  *         @arg @ref LL_PWR_CPU2_MODE_D2STANDBY
  */
__STATIC_INLINE uint32_t LL_PWR_CPU2_GetD2PowerMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CPU2CR, PWR_CPU2CR_PDDS_D2));
}
#endif /* DUAL_CORE */

/**
  * @brief  Set the D3 domain Power Down mode when the CPU enters deepsleep
  * @rmtoll CPUCR     PDDS_D3       LL_PWR_CPU_SetD3PowerMode\n
  * @param  PDMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_CPU_MODE_D3STOP
  *         @arg @ref LL_PWR_CPU_MODE_D3STANDBY
  * @retval None
  */
__STATIC_INLINE void LL_PWR_CPU_SetD3PowerMode(uint32_t PDMode)
{
  MODIFY_REG(PWR->CPUCR, PWR_CPUCR_PDDS_D3 , PDMode);
}

#if defined (DUAL_CORE)
/**
  * @brief  Set the D3 domain Power Down mode when the CPU2 enters deepsleep
  * @rmtoll CPU2CR     PDDS_D3       LL_PWR_CPU2_SetD3PowerMode\n
  * @param  PDMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_CPU2_MODE_D3STOP
  *         @arg @ref LL_PWR_CPU2_MODE_D3STANDBY
  * @retval None
  */
__STATIC_INLINE void LL_PWR_CPU2_SetD3PowerMode(uint32_t PDMode)
{
  MODIFY_REG(PWR->CPU2CR, PWR_CPU2CR_PDDS_D3, PDMode);
}
#endif /* DUAL_CORE */

/**
  * @brief  Get the D3 Domain Power Down mode when the CPU enters deepsleep
  * @rmtoll CPUCR     PDDS_D3       LL_PWR_CPU_GetD3PowerMode\n
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_CPU_MODE_D3STOP
  *         @arg @ref LL_PWR_CPU_MODE_D3STANDBY
  */
__STATIC_INLINE uint32_t LL_PWR_CPU_GetD3PowerMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CPUCR, PWR_CPUCR_PDDS_D3));
}

#if defined (DUAL_CORE)
/**
  * @brief  Get the D3 Domain Power Down mode when the CPU2 enters deepsleep
  * @rmtoll CPU2CR     PDDS_D3       LL_PWR_CPU2_GetD3PowerMode\n
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_CPU2_MODE_D3STOP
  *         @arg @ref LL_PWR_CPU2_MODE_D3STANDBY
  */
__STATIC_INLINE uint32_t LL_PWR_CPU2_GetD3PowerMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CPU2CR, PWR_CPU2CR_PDDS_D3));
}
#endif /* DUAL_CORE */

#if defined (DUAL_CORE)
/**
  * @brief  Hold the CPU1 and allocated peripherals when exiting from STOP mode
  * @rmtoll CPU2CR     HOLD1       LL_PWR_HoldCPU1\n
  * @retval None
  */
__STATIC_INLINE void LL_PWR_HoldCPU1(void)
{
  SET_BIT(PWR->CPU2CR, PWR_CPU2CR_HOLD1);
}

/**
  * @brief  Release the CPU1 and allocated peripherals
  * @rmtoll CPU2CR     HOLD1       LL_PWR_ReleaseCPU1\n
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ReleaseCPU1(void)
{
  CLEAR_BIT(PWR->CPU2CR, PWR_CPU2CR_HOLD1);
}

/**
  * @brief  Ckeck if the CPU1 and allocated peripherals are held
  * @rmtoll CPU2CR     HOLD1       LL_PWR_IsCPU1Held\n
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsCPU1Held(void)
{
  return ((READ_BIT(PWR->CPU2CR, PWR_CPU2CR_HOLD1) == (PWR_CPU2CR_HOLD1))  ? 1UL : 0UL);
}

/**
  * @brief  Hold the CPU2 and allocated peripherals when exiting from STOP mode
  * @rmtoll CPUCR     HOLD2       LL_PWR_HoldCPU2\n
  * @retval None
  */
__STATIC_INLINE void LL_PWR_HoldCPU2(void)
{
  SET_BIT(PWR->CPUCR, PWR_CPUCR_HOLD2);
}

/**
  * @brief  Release the CPU2 and allocated peripherals
  * @rmtoll CPUCR     HOLD2       LL_PWR_ReleaseCPU2\n
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ReleaseCPU2(void)
{
  CLEAR_BIT(PWR->CPUCR, PWR_CPUCR_HOLD2);
}

/**
  * @brief  Ckeck if the CPU2 and allocated peripherals are held
  * @rmtoll CPUCR     HOLD2       LL_PWR_IsCPU2Held\n
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsCPU2Held(void)
{
  return ((READ_BIT(PWR->CPUCR, PWR_CPUCR_HOLD2) == (PWR_CPUCR_HOLD2)) ? 1UL : 0UL);
}
#endif /* DUAL_CORE */

/**
  * @brief  D3 domain remains in Run mode regardless of CPU subsystem modes
  * @rmtoll CPUCR     RUN_D3       LL_PWR_CPU_EnableD3RunInLowPowerMode\n
  * @retval None
  */
__STATIC_INLINE void LL_PWR_CPU_EnableD3RunInLowPowerMode(void)
{
  SET_BIT(PWR->CPUCR, PWR_CPUCR_RUN_D3);
}

#if defined (DUAL_CORE)
/**
  * @brief  D3 domain remains in Run mode regardless of CPU2 subsystem modes
  * @rmtoll CPU2CR     RUN_D3       LL_PWR_CPU2_EnableD3RunInLowPowerMode\n
  * @retval None
  */
__STATIC_INLINE void LL_PWR_CPU2_EnableD3RunInLowPowerMode(void)
{
  SET_BIT(PWR->CPU2CR, PWR_CPU2CR_RUN_D3);
}
#endif /* DUAL_CORE */

/**
  * @brief  D3 domain follows CPU subsystem modes
  * @rmtoll CPUCR     RUN_D3       LL_PWR_CPU_DisableD3RunInLowPowerMode\n
  * @retval None
  */
__STATIC_INLINE void LL_PWR_CPU_DisableD3RunInLowPowerMode(void)
{
  CLEAR_BIT(PWR->CPUCR, PWR_CPUCR_RUN_D3);
}

#if defined (DUAL_CORE)
/**
  * @brief  D3 domain follows CPU2 subsystem modes
  * @rmtoll CPU2CR     RUN_D3       LL_PWR_CPU2_DisableD3RunInLowPowerMode\n
  * @retval None
  */
__STATIC_INLINE void LL_PWR_CPU2_DisableD3RunInLowPowerMode(void)
{
  CLEAR_BIT(PWR->CPU2CR, PWR_CPU2CR_RUN_D3);
}
#endif /* DUAL_CORE */

/**
  * @brief  Check if D3 is kept in Run mode when CPU enters low power mode
  * @rmtoll CPUCR     RUN_D3    LL_PWR_CPU_IsEnabledD3RunInLowPowerMode\n
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_CPU_IsEnabledD3RunInLowPowerMode(void)
{
  return ((READ_BIT(PWR->CPUCR, PWR_CPUCR_RUN_D3) == (PWR_CPUCR_RUN_D3)) ? 1UL : 0UL);
}

#if defined (DUAL_CORE)
/**
  * @brief  Check if D3 is kept in Run mode when CPU2 enters low power mode
  * @rmtoll CPU2CR     RUN_D3    LL_PWR_CPU2_IsEnabledD3RunInLowPowerMode\n
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_CPU2_IsEnabledD3RunInLowPowerMode(void)
{
  return ((READ_BIT(PWR->CPU2CR, PWR_CPU2CR_RUN_D3) == (PWR_CPU2CR_RUN_D3)) ? 1UL : 0UL);
}
#endif /* DUAL_CORE */

/**
  * @brief  Set the main internal Regulator output voltage
  * @rmtoll D3CR    VOS       LL_PWR_SetRegulVoltageScaling
  * @param  VoltageScaling This parameter can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE1
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE2
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRegulVoltageScaling(uint32_t VoltageScaling)
{
  MODIFY_REG(PWR->D3CR, PWR_D3CR_VOS, VoltageScaling);
}

/**
  * @brief  Get the main internal Regulator output voltage
  * @rmtoll D3CR    VOS       LL_PWR_GetRegulVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE1
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE2
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE3
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulVoltageScaling(void)
{
  return (uint32_t)(READ_BIT(PWR->D3CR, PWR_D3CR_VOS));
}

/**
  * @brief  Enable the WakeUp PINx functionality
  * @rmtoll WKUPEPR   WKUPEN1       LL_PWR_EnableWakeUpPin\n
  *         WKUPEPR   WKUPEN2       LL_PWR_EnableWakeUpPin\n
  *         WKUPEPR   WKUPEN3       LL_PWR_EnableWakeUpPin\n
  *         WKUPEPR   WKUPEN4       LL_PWR_EnableWakeUpPin\n
  *         WKUPEPR   WKUPEN5       LL_PWR_EnableWakeUpPin\n
  *         WKUPEPR   WKUPEN6       LL_PWR_EnableWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableWakeUpPin(uint32_t WakeUpPin)
{
  SET_BIT(PWR->WKUPEPR, WakeUpPin);
}

/**
  * @brief  Disable the WakeUp PINx functionality
  * @rmtoll WKUPEPR   WKUPEN1       LL_PWR_DisableWakeUpPin\n
  *         WKUPEPR   WKUPEN2       LL_PWR_DisableWakeUpPin\n
  *         WKUPEPR   WKUPEN3       LL_PWR_DisableWakeUpPin\n
  *         WKUPEPR   WKUPEN4       LL_PWR_DisableWakeUpPin\n
  *         WKUPEPR   WKUPEN5       LL_PWR_DisableWakeUpPin\n
  *         WKUPEPR   WKUPEN6       LL_PWR_DisableWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableWakeUpPin(uint32_t WakeUpPin)
{
  CLEAR_BIT(PWR->WKUPEPR, WakeUpPin);
}

/**
  * @brief  Check if the WakeUp PINx functionality is enabled
  * @rmtoll WKUPEPR   WKUPEN1       LL_PWR_IsEnabledWakeUpPin\n
  *         WKUPEPR   WKUPEN2       LL_PWR_IsEnabledWakeUpPin\n
  *         WKUPEPR   WKUPEN3       LL_PWR_IsEnabledWakeUpPin\n
  *         WKUPEPR   WKUPEN4       LL_PWR_IsEnabledWakeUpPin\n
  *         WKUPEPR   WKUPEN5       LL_PWR_IsEnabledWakeUpPin\n
  *         WKUPEPR   WKUPEN6       LL_PWR_IsEnabledWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWakeUpPin(uint32_t WakeUpPin)
{
  return ((READ_BIT(PWR->WKUPEPR, WakeUpPin) == (WakeUpPin)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Wake-Up pin polarity low for the event detection
  * @rmtoll WKUPEPR   WKUPP1       LL_PWR_SetWakeUpPinPolarityLow\n
  *         WKUPEPR   WKUPP2       LL_PWR_SetWakeUpPinPolarityLow\n
  *         WKUPEPR   WKUPP3       LL_PWR_SetWakeUpPinPolarityLow\n
  *         WKUPEPR   WKUPP4       LL_PWR_SetWakeUpPinPolarityLow\n
  *         WKUPEPR   WKUPP5       LL_PWR_SetWakeUpPinPolarityLow\n
  *         WKUPEPR   WKUPP6       LL_PWR_SetWakeUpPinPolarityLow
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityLow(uint32_t WakeUpPin)
{
  SET_BIT(PWR->WKUPEPR, (WakeUpPin << PWR_WKUPEPR_WKUPP1_Pos));
}

/**
  * @brief  Set the Wake-Up pin polarity high for the event detection
  * @rmtoll WKUPEPR   WKUPP1       LL_PWR_SetWakeUpPinPolarityHigh\n
  *         WKUPEPR   WKUPP2       LL_PWR_SetWakeUpPinPolarityHigh\n
  *         WKUPEPR   WKUPP3       LL_PWR_SetWakeUpPinPolarityHigh\n
  *         WKUPEPR   WKUPP4       LL_PWR_SetWakeUpPinPolarityHigh\n
  *         WKUPEPR   WKUPP5       LL_PWR_SetWakeUpPinPolarityHigh\n
  *         WKUPEPR   WKUPP6       LL_PWR_SetWakeUpPinPolarityHigh
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityHigh(uint32_t WakeUpPin)
{
  CLEAR_BIT(PWR->WKUPEPR, (WakeUpPin << PWR_WKUPEPR_WKUPP1_Pos));
}

/**
  * @brief  Get the Wake-Up pin polarity for the event detection
  * @rmtoll WKUPEPR   WKUPP1       LL_PWR_IsWakeUpPinPolarityLow\n
  *         WKUPEPR   WKUPP2       LL_PWR_IsWakeUpPinPolarityLow\n
  *         WKUPEPR   WKUPP3       LL_PWR_IsWakeUpPinPolarityLow\n
  *         WKUPEPR   WKUPP4       LL_PWR_IsWakeUpPinPolarityLow\n
  *         WKUPEPR   WKUPP5       LL_PWR_IsWakeUpPinPolarityLow\n
  *         WKUPEPR   WKUPP6       LL_PWR_IsWakeUpPinPolarityLow
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsWakeUpPinPolarityLow(uint32_t WakeUpPin)
{
  return ((READ_BIT(PWR->WKUPEPR, (WakeUpPin << PWR_WKUPEPR_WKUPP1_Pos)) == (WakeUpPin << PWR_WKUPEPR_WKUPP1_Pos)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Wake-Up pin Pull None
  * @rmtoll WKUPEPR   WKUPPUPD1       LL_PWR_SetWakeUpPinPullNone\n
  *         WKUPEPR   WKUPPUPD2       LL_PWR_SetWakeUpPinPullNone\n
  *         WKUPEPR   WKUPPUPD3       LL_PWR_SetWakeUpPinPullNone\n
  *         WKUPEPR   WKUPPUPD4       LL_PWR_SetWakeUpPinPullNone\n
  *         WKUPEPR   WKUPPUPD5       LL_PWR_SetWakeUpPinPullNone\n
  *         WKUPEPR   WKUPPUPD6       LL_PWR_SetWakeUpPinPullNone
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPullNone(uint32_t WakeUpPin)
{
  MODIFY_REG(PWR->WKUPEPR, \
            (PWR_WKUPEPR_WKUPPUPD1 << ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * POSITION_VAL(WakeUpPin)) & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)), \
            (LL_PWR_WAKEUP_PIN_NOPULL << ((PWR_WKUPEPR_WKUPPUPD1_Pos + (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * POSITION_VAL(WakeUpPin))) & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)));
}

/**
  * @brief  Set the Wake-Up pin Pull Up
  * @rmtoll WKUPEPR   WKUPPUPD1       LL_PWR_SetWakeUpPinPullUp\n
  *         WKUPEPR   WKUPPUPD2       LL_PWR_SetWakeUpPinPullUp\n
  *         WKUPEPR   WKUPPUPD3       LL_PWR_SetWakeUpPinPullUp\n
  *         WKUPEPR   WKUPPUPD4       LL_PWR_SetWakeUpPinPullUp\n
  *         WKUPEPR   WKUPPUPD5       LL_PWR_SetWakeUpPinPullUp\n
  *         WKUPEPR   WKUPPUPD6       LL_PWR_SetWakeUpPinPullUp
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPullUp(uint32_t WakeUpPin)
{
  MODIFY_REG(PWR->WKUPEPR, \
            (PWR_WKUPEPR_WKUPPUPD1 << ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * POSITION_VAL(WakeUpPin)) & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)), \
            (LL_PWR_WAKEUP_PIN_PULLUP << ((PWR_WKUPEPR_WKUPPUPD1_Pos + (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * POSITION_VAL(WakeUpPin))) & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)));
}

/**
  * @brief  Set the Wake-Up pin Pull Down
  * @rmtoll WKUPEPR   WKUPPUPD1       LL_PWR_SetWakeUpPinPullDown\n
  *         WKUPEPR   WKUPPUPD2       LL_PWR_SetWakeUpPinPullDown\n
  *         WKUPEPR   WKUPPUPD3       LL_PWR_SetWakeUpPinPullDown\n
  *         WKUPEPR   WKUPPUPD4       LL_PWR_SetWakeUpPinPullDown\n
  *         WKUPEPR   WKUPPUPD5       LL_PWR_SetWakeUpPinPullDown\n
  *         WKUPEPR   WKUPPUPD6       LL_PWR_SetWakeUpPinPullDown
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPullDown(uint32_t WakeUpPin)
{
  MODIFY_REG(PWR->WKUPEPR, \
            (PWR_WKUPEPR_WKUPPUPD1 << ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * POSITION_VAL(WakeUpPin)) & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)), \
            (LL_PWR_WAKEUP_PIN_PULLDOWN << ((PWR_WKUPEPR_WKUPPUPD1_Pos + (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * POSITION_VAL(WakeUpPin))) & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)));
}

/**
  * @brief  Get the Wake-Up pin pull
  * @rmtoll WKUPEPR   WKUPPUPD1       LL_PWR_GetWakeUpPinPull\n
  *         WKUPEPR   WKUPPUPD2       LL_PWR_GetWakeUpPinPull\n
  *         WKUPEPR   WKUPPUPD3       LL_PWR_GetWakeUpPinPull\n
  *         WKUPEPR   WKUPPUPD4       LL_PWR_GetWakeUpPinPull\n
  *         WKUPEPR   WKUPPUPD5       LL_PWR_GetWakeUpPinPull\n
  *         WKUPEPR   WKUPPUPD6       LL_PWR_GetWakeUpPinPull
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  *         @arg @ref LL_PWR_WAKEUP_PIN5
  *         @arg @ref LL_PWR_WAKEUP_PIN6
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_NOPULL
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULLUP
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULLDOWN
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeUpPinPull(uint32_t WakeUpPin)
{
  register uint32_t regValue = READ_BIT(PWR->WKUPEPR, (PWR_WKUPEPR_WKUPPUPD1 << ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * POSITION_VAL(WakeUpPin)) & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)));

  return (uint32_t)(regValue >> ((PWR_WKUPEPR_WKUPPUPD1_Pos + (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * POSITION_VAL(WakeUpPin))) & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK));
}

/**
  * @}
  */

/** @defgroup PWR_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Indicate whether VDD voltage is below the selected PVD threshold
  * @rmtoll CSR1   PVDO       LL_PWR_IsActiveFlag_PVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_PVDO(void)
{
  return ((READ_BIT(PWR->CSR1, PWR_CSR1_PVDO) == (PWR_CSR1_PVDO)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the voltage level is ready for current actual used VOS
  * @rmtoll CSR1   ACTVOSRDY       LL_PWR_IsActiveFlag_ACTVOS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_ACTVOS(void)
{
  return ((READ_BIT(PWR->CSR1, PWR_CSR1_ACTVOSRDY) == (PWR_CSR1_ACTVOSRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether VDDA voltage is below the selected AVD threshold
  * @rmtoll CSR1   AVDO       LL_PWR_IsActiveFlag_AVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_AVDO(void)
{
  return ((READ_BIT(PWR->CSR1, PWR_CSR1_AVDO) == (PWR_CSR1_AVDO)) ? 1UL : 0UL);
}

/**
  * @brief  Get Backup Regulator ready Flag
  * @rmtoll CR2   BRRDY       LL_PWR_IsActiveFlag_BRR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_BRR(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_BRRDY) == (PWR_CR2_BRRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VBAT level is above or below low threshold
  * @rmtoll CR2   VBATL       LL_PWR_IsActiveFlag_VBATL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VBATL(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_VBATL) == (PWR_CR2_VBATL)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VBAT level is above or below high threshold
  * @rmtoll CR2   VBATH       LL_PWR_IsActiveFlag_VBATH
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VBATH(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_VBATH) == (PWR_CR2_VBATH)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the CPU temperature level is above or below low threshold
  * @rmtoll CR2   TEMPL       LL_PWR_IsActiveFlag_TEMPL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_TEMPL(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_TEMPL) == (PWR_CR2_TEMPL)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the CPU temperature level is above or below high threshold
  * @rmtoll CR2   TEMPH       LL_PWR_IsActiveFlag_TEMPH
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_TEMPH(void)
{
  return ((READ_BIT(PWR->CR2, PWR_CR2_TEMPH) == (PWR_CR2_TEMPH)) ? 1UL : 0UL);
}

#if defined (SMPS)
/**
  * @brief  Indicate whether the SMPS external supply is ready or not
  * @rmtoll CR3   SMPSEXTRDY       LL_PWR_IsActiveFlag_SMPSEXT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_SMPSEXT(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_SMPSEXTRDY) == (PWR_CR3_SMPSEXTRDY)) ? 1UL : 0UL);
}
#endif /* SMPS */

/**
  * @brief  Indicate whether the USB supply is ready or not
  * @rmtoll CR3   USBRDY       LL_PWR_IsActiveFlag_USB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_USB(void)
{
  return ((READ_BIT(PWR->CR3, PWR_CR3_USB33RDY) == (PWR_CR3_USB33RDY)) ? 1UL : 0UL);
}

#if defined (DUAL_CORE)
/**
  * @brief  Get HOLD2 Flag
  * @rmtoll CPUCR   HOLD2F       LL_PWR_IsActiveFlag_HOLD2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_HOLD2(void)
{
  return ((READ_BIT(PWR->CPUCR, PWR_CPUCR_HOLD2F) == (PWR_CPUCR_HOLD2F)) ? 1UL : 0UL);
}

/**
  * @brief  Get HOLD1 Flag
  * @rmtoll CPU2CR   HOLD1F       LL_PWR_IsActiveFlag_HOLD1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_HOLD1(void)
{
  return ((READ_BIT(PWR->CPU2CR, PWR_CPU2CR_HOLD1F) == (PWR_CPU2CR_HOLD1F)) ? 1UL : 0UL);
}
#endif /* DUAL_CORE */

/**
  * @brief  Get CPU System Stop Flag
  * @rmtoll CPUCR   STOPF       LL_PWR_CPU_IsActiveFlag_STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_CPU_IsActiveFlag_STOP(void)
{
  return ((READ_BIT(PWR->CPUCR, PWR_CPUCR_STOPF) == (PWR_CPUCR_STOPF)) ? 1UL : 0UL);
}

#if defined (DUAL_CORE)
/**
  * @brief  Get CPU2 System Stop Flag
  * @rmtoll CPU2CR   STOPF       LL_PWR_CPU2_IsActiveFlag_STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_CPU2_IsActiveFlag_STOP(void)
{
  return ((READ_BIT(PWR->CPU2CR, PWR_CPU2CR_STOPF) == (PWR_CPU2CR_STOPF)) ? 1UL : 0UL);
}
#endif /* DUAL_CORE */

/**
  * @brief  Get CPU System Standby Flag
  * @rmtoll CPUCR   SBF       LL_PWR_CPU_IsActiveFlag_SB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_CPU_IsActiveFlag_SB(void)
{
  return ((READ_BIT(PWR->CPUCR, PWR_CPUCR_SBF) == (PWR_CPUCR_SBF)) ? 1UL : 0UL);
}

#if defined (DUAL_CORE)
/**
  * @brief  Get CPU2 System Standby Flag
  * @rmtoll CPU2CR   SBF       LL_PWR_CPU2_IsActiveFlag_SB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_CPU2_IsActiveFlag_SB(void)
{
  return ((READ_BIT(PWR->CPU2CR, PWR_CPU2CR_SBF) == (PWR_CPU2CR_SBF)) ? 1UL : 0UL);
}
#endif /* DUAL_CORE */

/**
  * @brief  Get CPU D1 Domain Standby Flag
  * @rmtoll CPUCR   SBF_D1       LL_PWR_CPU_IsActiveFlag_SB_D1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_CPU_IsActiveFlag_SB_D1(void)
{
  return ((READ_BIT(PWR->CPUCR, PWR_CPUCR_SBF_D1) == (PWR_CPUCR_SBF_D1)) ? 1UL : 0UL);
}

#if defined (DUAL_CORE)
/**
  * @brief  Get CPU2 D1 Domain Standby Flag
  * @rmtoll CPU2CR   SBF_D1       LL_PWR_CPU2_IsActiveFlag_SB_D1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_CPU2_IsActiveFlag_SB_D1(void)
{
  return ((READ_BIT(PWR->CPU2CR, PWR_CPU2CR_SBF_D1) == (PWR_CPU2CR_SBF_D1)) ? 1UL : 0UL);
}
#endif /* DUAL_CORE */

/**
  * @brief  Get CPU D2 Domain Standby Flag
  * @rmtoll CPUCR   SBF_D2       LL_PWR_CPU_IsActiveFlag_SB_D2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_CPU_IsActiveFlag_SB_D2(void)
{
  return ((READ_BIT(PWR->CPUCR, PWR_CPUCR_SBF_D2) == (PWR_CPUCR_SBF_D2)) ? 1UL : 0UL);
}

#if defined (DUAL_CORE)
/**
  * @brief  Get CPU2 D2 Domain Standby Flag
  * @rmtoll CPU2CR   SBF_D2       LL_PWR_CPU2_IsActiveFlag_SB_D2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_CPU2_IsActiveFlag_SB_D2(void)
{
  return ((READ_BIT(PWR->CPU2CR, PWR_CPU2CR_SBF_D2) == (PWR_CPU2CR_SBF_D2)) ? 1UL : 0UL);
}
#endif /* DUAL_CORE */

/**
  * @brief  Indicate whether the Regulator is ready in the selected voltage range
  *         or if its output voltage is still changing to the required voltage level
  * @rmtoll D3CR   VOSRDY       LL_PWR_IsActiveFlag_VOS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VOS(void)
{
  return ((READ_BIT(PWR->D3CR, PWR_D3CR_VOSRDY) == (PWR_D3CR_VOSRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 6
  * @rmtoll WKUPFR          WKUPF6          LL_PWR_IsActiveFlag_WU6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU6(void)
{
  return ((READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF6) == (PWR_WKUPFR_WKUPF6)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 5
  * @rmtoll WKUPFR          WKUPF5          LL_PWR_IsActiveFlag_WU5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU5(void)
{
  return ((READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF5) == (PWR_WKUPFR_WKUPF5)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 4
  * @rmtoll WKUPFR          WKUPF4          LL_PWR_IsActiveFlag_WU4
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU4(void)
{
  return ((READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF4) == (PWR_WKUPFR_WKUPF4)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 3
  * @rmtoll WKUPFR          WKUPF3          LL_PWR_IsActiveFlag_WU3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU3(void)
{
  return ((READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF3) == (PWR_WKUPFR_WKUPF3)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 2
  * @rmtoll WKUPFR          WKUPF2          LL_PWR_IsActiveFlag_WU2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU2(void)
{
  return ((READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF2) == (PWR_WKUPFR_WKUPF2)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 1
  * @rmtoll WKUPFR          WKUPF1          LL_PWR_IsActiveFlag_WU1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU1(void)
{
  return ((READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF1) == (PWR_WKUPFR_WKUPF1)) ? 1UL : 0UL);
}

/**
  * @brief  Clear CPU STANDBY, STOP and HOLD flags
  * @rmtoll CPUCR   CSSF       LL_PWR_ClearFlag_CPU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_CPU(void)
{
  SET_BIT(PWR->CPUCR, PWR_CPUCR_CSSF);
}

#if defined (DUAL_CORE)
/**
  * @brief  Clear CPU2 STANDBY, STOP and HOLD flags
  * @rmtoll CPU2CR   CSSF       LL_PWR_ClearFlag_CPU2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_CPU2(void)
{
  SET_BIT(PWR->CPU2CR, PWR_CPU2CR_CSSF);
}
#endif /* DUAL_CORE */

/**
  * @brief  Clear Wake-up Flag 6
  * @rmtoll WKUPCR          WKUPC6         LL_PWR_ClearFlag_WU6
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU6(void)
{
  WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC6);
}

/**
  * @brief  Clear Wake-up Flag 5
  * @rmtoll WKUPCR          WKUPC5         LL_PWR_ClearFlag_WU5
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU5(void)
{
  WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC5);
}

/**
  * @brief  Clear Wake-up Flag 4
  * @rmtoll WKUPCR          WKUPC4         LL_PWR_ClearFlag_WU4
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU4(void)
{
  WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC4);
}

/**
  * @brief  Clear Wake-up Flag 3
  * @rmtoll WKUPCR          WKUPC3         LL_PWR_ClearFlag_WU3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU3(void)
{
  WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC3);
}

/**
  * @brief  Clear Wake-up Flag 2
  * @rmtoll WKUPCR          WKUPC2         LL_PWR_ClearFlag_WU2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU2(void)
{
  WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC2);
}

/**
  * @brief  Clear Wake-up Flag 1
  * @rmtoll WKUPCR          WKUPC1         LL_PWR_ClearFlag_WU1
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU1(void)
{
  WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC1);
}

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

#endif /* STM32H7xx_LL_PWR_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
