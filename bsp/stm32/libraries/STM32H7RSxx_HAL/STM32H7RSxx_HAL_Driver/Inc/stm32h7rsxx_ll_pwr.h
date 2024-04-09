/**
  ******************************************************************************
  * @file    stm32h7rsxx_ll_pwr.h
  * @author  MCD Application Team
  * @brief   Header file of PWR LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7RSxx_LL_PWR_H
#define STM32H7RSxx_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx.h"

/** @addtogroup STM32H7RSxx_LL_Driver
  * @{
  */

#if defined (PWR)

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
#define LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET    (2UL)
#define LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK       (0x1FU)
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
#define LL_PWR_SR_CSSF                 PWR_CSR3_CSSF                           /*!< Clear Stop and Standby flags */
#define LL_PWR_WKUPCR_WKUPC1           PWR_WKUPCR_WKUPC1                       /*!< Clear Wakeup flag 1          */
#define LL_PWR_WKUPCR_WKUPC2           PWR_WKUPCR_WKUPC2                       /*!< Clear Wakeup flag 2          */
#define LL_PWR_WKUPCR_WKUPC3           PWR_WKUPCR_WKUPC3                       /*!< Clear Wakeup flag 3          */
#define LL_PWR_WKUPCR_WKUPC4           PWR_WKUPCR_WKUPC4                       /*!< Clear Wakeup flag 4          */
#define LL_PWR_WKUPCR_WKUPC            PWR_WKUPCR_WKUPC                        /*!< Clear all Wakeup flags       */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_PWR_ReadReg function
  * @{
  */
#define LL_PWR_FLAG_VOSRDY             PWR_CSR4_VOSRDY                         /*!< Voltage scaling ready flag */
#define LL_PWR_FLAG_STOPF              PWR_CSR3_STOPF                          /*!< Stop flag                  */
#define LL_PWR_FLAG_SBF                PWR_CSR3_SBF                            /*!< Standby flag               */
#define LL_PWR_WAKEUP_FLAG1            PWR_WKUPFR_WKUPF1                       /*!< Wakeup flag 1              */
#define LL_PWR_WAKEUP_FLAG2            PWR_WKUPFR_WKUPF2                       /*!< Wakeup flag 2              */
#define LL_PWR_WAKEUP_FLAG3            PWR_WKUPFR_WKUPF3                       /*!< Wakeup flag 3              */
#define LL_PWR_WAKEUP_FLAG4            PWR_WKUPFR_WKUPF4                       /*!< Wakeup flag 4              */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_MODE_PWR Power Down Mode In Deep Sleep Mode
  * @{
  */
#define LL_PWR_POWERDOWN_MODE_DS_STOP     (0U)                                 /*!< Enter to Stop mode when the CPU enters deepsleep    */
#define LL_PWR_POWERDOWN_MODE_DS_STANDBY  PWR_CSR3_PDDS                        /*!< Enter to Standby mode when the CPU enters deepsleep */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_REGU_VOLTAGE Run mode Regulator Voltage Scaling
  * @{
  */
#define LL_PWR_REGU_VOLTAGE_SCALE0     PWR_CSR4_VOS                            /*!< Voltage scaling range 0 (highest frequency) */
#define LL_PWR_REGU_VOLTAGE_SCALE1     (0U)                                    /*!< Voltage scaling range 1 (lowest power)      */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_STOP_MODE_REGU_VOLTAGE Stop mode Regulator Voltage Scaling
  * @{
  */
#define LL_PWR_REGU_STOP_VOLTAGE_SCALE3     PWR_CR1_SVOS                       /*!< Voltage scaling range 3 (highest frequency) when system enters STOP mode */
#define LL_PWR_REGU_STOP_VOLTAGE_SCALE5     (0U)                               /*!< Voltage scaling range 5 (lowest power) when system enters STOP mode      */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PVDLEVEL Power Digital Voltage Level Detector
  * @{
  */
#define LL_PWR_PVDLEVEL_1              (0U)                                    /*!< PVD level 1 */
#define LL_PWR_PVDLEVEL_2              PWR_CR1_PLS_0                           /*!< PVD level 2 */
#define LL_PWR_PVDLEVEL_3              PWR_CR1_PLS_1                           /*!< PVD level 3 */
#define LL_PWR_PVDLEVEL_4              (PWR_CR1_PLS_0 | PWR_CR1_PLS_1)         /*!< PVD level 4 */
#define LL_PWR_PVDLEVEL_5              PWR_CR1_PLS_2                           /*!< PVD level 5 */
#define LL_PWR_PVDLEVEL_6              (PWR_CR1_PLS_0 | PWR_CR1_PLS_2)         /*!< PVD level 6 */
#define LL_PWR_PVDLEVEL_7              (PWR_CR1_PLS_1 | PWR_CR1_PLS_2)         /*!< PVD level 7 */
#define LL_PWR_PVDLEVEL_EXT            (PWR_CR1_PLS_0 | PWR_CR1_PLS_1 | PWR_CR1_PLS_2)
/*!< External voltage level on PVD_IN pin, compared to internal VREFINT level */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_AVDLEVEL Power Analog Voltage Level Detector
  * @{
  */
#define LL_PWR_AVDLEVEL_1              (0U)                                    /*!< Analog Voltage detector level 1 */
#define LL_PWR_AVDLEVEL_2              PWR_CR1_ALS_0                           /*!< Analog Voltage detector level 2 */
#define LL_PWR_AVDLEVEL_3              PWR_CR1_ALS_1                           /*!< Analog Voltage detector level 3 */
#define LL_PWR_AVDLEVEL_4              (PWR_CR1_ALS_0 | PWR_CR1_ALS_1)         /*!< Analog Voltage detector level 4 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_XSPI_CAP1 XSPI 1 capacitor
  * @{
  */
#define LL_PWR_XSPI1_CAPACITOR_OFF     (0U)                                    /*!< XSPI Port 1 Capacitor OFF        */
#define LL_PWR_XSPI1_CAPACITOR_1_DIV_3 PWR_CSR2_XSPICAP1_0                     /*!< XSPI Port 1 Capacitor set to 1/3 */
#define LL_PWR_XSPI1_CAPACITOR_2_DIV_3 PWR_CSR2_XSPICAP1_1                     /*!< XSPI Port 1 Capacitor set to 2/3 */
#define LL_PWR_XSPI1_CAPACITOR_FULL    (PWR_CSR2_XSPICAP1_0 | PWR_CSR2_XSPICAP1_1)
/*!< XSPI Port 1 Capacitor set to full capacitance */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_XSPI_CAP2 XSPI 2 Capacitor
  * @{
  */
#define LL_PWR_XSPI2_CAPACITOR_OFF     (0U)                                    /*!< XSPI Port 2 Capacitor OFF        */
#define LL_PWR_XSPI2_CAPACITOR_1_DIV_3 PWR_CSR2_XSPICAP2_0                     /*!< XSPI Port 2 Capacitor set to 1/3 */
#define LL_PWR_XSPI2_CAPACITOR_2_DIV_3 PWR_CSR2_XSPICAP2_1                     /*!< XSPI Port 2 Capacitor set to 2/3 */
#define LL_PWR_XSPI2_CAPACITOR_FULL    (PWR_CSR2_XSPICAP2_0 | PWR_CSR2_XSPICAP2_1)
/*!< XSPI Port 2 Capacitor set to full capacitance */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_BATT_CHARG_RESISTOR Battery Charge Resistor
  * @{
  */
#define LL_PWR_BATT_CHARG_RESISTOR_5K   (0U)                                   /*!< Charge the Battery through a 5 kO resistor   */
#define LL_PWR_BATT_CHARG_RESISTOR_1_5K PWR_CSR2_VBRS                          /*!< Charge the Battery through a 1.5 kO resistor */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN  Wakeup Pins
  * @{
  */
#define LL_PWR_WAKEUP_PIN1             PWR_WKUPEPR_WKUPEN1                     /*!< Wake-Up pin 1 : PA0  */
#define LL_PWR_WAKEUP_PIN2             PWR_WKUPEPR_WKUPEN2                     /*!< Wake-Up pin 2 : PA2  */
#define LL_PWR_WAKEUP_PIN3             PWR_WKUPEPR_WKUPEN3                     /*!< Wake-Up pin 3 : PC13 */
#define LL_PWR_WAKEUP_PIN4             PWR_WKUPEPR_WKUPEN4                     /*!< Wake-Up pin 4 : PC1  */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN_PULL  Wakeup Pins pull configuration
  * @{
  */
#define LL_PWR_WAKEUP_PIN_NOPULL       (0UL)                                   /*!< Configure Wake-Up pin in no pull   */
#define LL_PWR_WAKEUP_PIN_PULLUP       (1UL)                                   /*!< Configure Wake-Up pin in pull Up   */
#define LL_PWR_WAKEUP_PIN_PULLDOWN     (2UL)                                   /*!< Configure Wake-Up pin in pull Down */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SUPPLY_PWR Power supply source configuration
  * @{
  */
#define LL_PWR_LDO_SUPPLY                     PWR_CSR2_LDOEN                                                              /*!< Core domains are supplied from the LDO                                                                      */
#define LL_PWR_DIRECT_SMPS_SUPPLY             PWR_CSR2_SDEN                                                               /*!< Core domains are supplied from the SMPS                                                                     */
#define LL_PWR_SMPS_1V8_SUPPLIES_LDO          (PWR_CSR2_SDHILEVEL | PWR_CSR2_SDEN | PWR_CSR2_LDOEN)                       /*!< The SMPS 1.8V output supplies the LDO which supplies the Core domains                                       */
#define LL_PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO  (PWR_CSR2_SDHILEVEL | PWR_CSR2_SMPSEXTHP | PWR_CSR2_SDEN | PWR_CSR2_LDOEN)  /*!< The SMPS 1.8V output supplies an external circuits and the LDO. The Core domains are supplied from the LDO  */
#define LL_PWR_SMPS_1V8_SUPPLIES_EXT          (PWR_CSR2_SDHILEVEL | PWR_CSR2_SMPSEXTHP | PWR_CSR2_SDEN | PWR_CSR2_BYPASS) /*!< The SMPS 1.8V output supplies an external source which supplies the Core domains                            */
#define LL_PWR_EXTERNAL_SOURCE_SUPPLY         PWR_CSR2_BYPASS                                                             /*!< The SMPS and the LDO are Bypassed. The Core domains are supplied from an external source                    */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GPIO_PIN_MASK PWR GPIO Pin Mask
  * @{
  */
#define LL_PWR_GPIO_PIN_0              (0x0001U)                               /*!< GPIO port I/O pin 0  */
#define LL_PWR_GPIO_PIN_1              (0x0002U)                               /*!< GPIO port I/O pin 1  */
#define LL_PWR_GPIO_PIN_2              (0x0004U)                               /*!< GPIO port I/O pin 2  */
#define LL_PWR_GPIO_PIN_3              (0x0008U)                               /*!< GPIO port I/O pin 3  */
#define LL_PWR_GPIO_PIN_4              (0x0010U)                               /*!< GPIO port I/O pin 4  */
#define LL_PWR_GPIO_PIN_5              (0x0020U)                               /*!< GPIO port I/O pin 5  */
#define LL_PWR_GPIO_PIN_6              (0x0040U)                               /*!< GPIO port I/O pin 6  */
#define LL_PWR_GPIO_PIN_7              (0x0080U)                               /*!< GPIO port I/O pin 7  */
#define LL_PWR_GPIO_PIN_8              (0x0100U)                               /*!< GPIO port I/O pin 8  */
#define LL_PWR_GPIO_PIN_9              (0x0200U)                               /*!< GPIO port I/O pin 9  */
#define LL_PWR_GPIO_PIN_10             (0x0400U)                               /*!< GPIO port I/O pin 10 */
#define LL_PWR_GPIO_PIN_11             (0x0800U)                               /*!< GPIO port I/O pin 11 */
#define LL_PWR_GPIO_PIN_12             (0x1000U)                               /*!< GPIO port I/O pin 12 */
#define LL_PWR_GPIO_PIN_13             (0x2000U)                               /*!< GPIO port I/O pin 13 */
#define LL_PWR_GPIO_PIN_14             (0x4000U)                               /*!< GPIO port I/O pin 14 */
#define LL_PWR_GPIO_PIN_15             (0x8000U)                               /*!< GPIO port I/O pin 15 */
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

/** @defgroup PWR_LL_EF_Configuration PWR Configuration
  * @{
  */

/**
  * @brief  Enable Power Voltage Detector
  * @rmtoll CR1        PVDE            LL_PWR_EnablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_PVDE);
}

/**
  * @brief  Disable Power Voltage Detector
  * @rmtoll CR1        PVDE            LL_PWR_DisablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_PVDE);
}

/**
  * @brief  Check if Power Voltage Detector is enabled
  * @rmtoll CR1        PVDE            LL_PWR_IsEnabledPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_PVDE) == (PWR_CR1_PVDE)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the voltage threshold detected by the Power Voltage Detector
  * @rmtoll CR1        PLS             LL_PWR_SetPVDLevel
  * @param  PVDLevel This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  *         @arg @ref LL_PWR_PVDLEVEL_EXT
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPVDLevel(uint32_t PVDLevel)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_PLS, PVDLevel);
}

/**
  * @brief  Get the voltage threshold detection
  * @rmtoll CR1        PLS             LL_PWR_GetPVDLevel
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  *         @arg @ref LL_PWR_PVDLEVEL_EXT
  */
__STATIC_INLINE uint32_t LL_PWR_GetPVDLevel(void)
{
  return READ_BIT(PWR->CR1, PWR_CR1_PLS);
}

/**
  * @brief  Enable access to the backup domain
  * @rmtoll CR1        DBP             LL_PWR_EnableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBkUpAccess(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @brief  Disable access to the backup domain
  * @rmtoll CR1        DBP             LL_PWR_DisableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBkUpAccess(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @brief  Check if the backup domain is enabled
  * @rmtoll CR1        DBP             LL_PWR_IsEnabledBkUpAccess
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBkUpAccess(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_DBP) == (PWR_CR1_DBP)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the Flash low-power mode in Stop Mode
  * @rmtoll CR1        FLPS            LL_PWR_EnableFlashLowPower
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableFlashLowPower(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_FLPS);
}

/**
  * @brief  Disable the Flash low-power mode in Stop Mode
  * @rmtoll CR1        FLPS            LL_PWR_DisableFlashLowPower
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableFlashLowPower(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_FLPS);
}

/**
  * @brief  Check if the Flash low-power mode in Stop Mode is enabled
  * @rmtoll CR1        FLPS            LL_PWR_IsEnabledFlashLowPower
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledFlashLowPower(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_FLPS) == (PWR_CR1_FLPS)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the Analog Voltage Booster
  * @rmtoll CR1        BOOSTE          LL_PWR_EnableAnalogBooster
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableAnalogBooster(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_BOOSTE);
}

/**
  * @brief  Disable the Analog Voltage Booster
  * @rmtoll CR1        BOOSTE          LL_PWR_DisableAnalogBooster
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableAnalogBooster(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_BOOSTE);
}

/**
  * @brief  Check if the Analog Voltage Booster is enabled
  * @rmtoll CR1        BOOSTE          LL_PWR_IsEnabledAnalogBooster
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledAnalogBooster(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_BOOSTE) == (PWR_CR1_BOOSTE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the Analog Voltage Ready
  * @rmtoll CR1        AVDREADY        LL_PWR_EnableAnalogVoltageReady
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableAnalogVoltageReady(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_AVDREADY);
}

/**
  * @brief  Disable the Analog Voltage Ready
  * @rmtoll CR1        AVDREADY        LL_PWR_DisableAnalogVoltageReady
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableAnalogVoltageReady(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_AVDREADY);
}

/**
  * @brief  Check if the Analog Voltage Ready is enabled
  * @rmtoll CR1        AVDREADY        LL_PWR_IsEnabledAnalogVoltageReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledAnalogVoltageReady(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_AVDREADY) == (PWR_CR1_AVDREADY)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Analog Power Voltage Monitor
  * @rmtoll CR1        AVDEN           LL_PWR_EnableAVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableAVD(void)
{
  SET_BIT(PWR->CR1, PWR_CR1_AVDEN);
}

/**
  * @brief  Disable Analog Power Voltage Monitor
  * @rmtoll CR1        AVDEN           LL_PWR_DisableAVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableAVD(void)
{
  CLEAR_BIT(PWR->CR1, PWR_CR1_AVDEN);
}

/**
  * @brief  Check if Analog Power Voltage Monitor is enabled
  * @rmtoll CR1        AVDEN           LL_PWR_IsEnabledAVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledAVD(void)
{
  return ((READ_BIT(PWR->CR1, PWR_CR1_AVDEN) == (PWR_CR1_AVDEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Analog Voltage detector level
  * @rmtoll CR1        ALS             LL_PWR_SetAVDLevel
  * @param  AVDLevel This parameter can be one of the following values:
  *         @arg @ref LL_PWR_AVDLEVEL_1
  *         @arg @ref LL_PWR_AVDLEVEL_2
  *         @arg @ref LL_PWR_AVDLEVEL_3
  *         @arg @ref LL_PWR_AVDLEVEL_4
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetAVDLevel(uint32_t AVDLevel)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_ALS, AVDLevel);
}

/**
  * @brief  Get the Analog Voltage detector level selected
  * @rmtoll CR1        ALS             LL_PWR_GetAVDLevel
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_AVDLEVEL_1
  *         @arg @ref LL_PWR_AVDLEVEL_2
  *         @arg @ref LL_PWR_AVDLEVEL_3
  *         @arg @ref LL_PWR_AVDLEVEL_4
  */
__STATIC_INLINE uint32_t LL_PWR_GetAVDLevel(void)
{
  return READ_BIT(PWR->CR1, PWR_CR1_ALS);
}

/**
  * @brief  Enable Backup Regulator
  * @rmtoll CSR1       BREN            LL_PWR_EnableBkUpRegulator
  * @note When set, the Backup Regulator (used to maintain backup SRAM content in Standby and
  *       VBAT modes) is enabled. If BRE is reset, the backup Regulator is switched off. The backup
  *       SRAM can still be used but its content will be lost in the Standby and VBAT modes. Once set,
  *       the application must wait that the Backup Regulator Ready flag (BRR) is set to indicate that
  *       the data written into the RAM will be maintained in the Standby and VBAT modes.
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBkUpRegulator(void)
{
  SET_BIT(PWR->CSR1, PWR_CSR1_BREN);
}

/**
  * @brief  Disable Backup Regulator
  * @rmtoll CSR1       BREN            LL_PWR_DisableBkUpRegulator
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBkUpRegulator(void)
{
  CLEAR_BIT(PWR->CSR1, PWR_CSR1_BREN);
}

/**
  * @brief  Check if the backup Regulator is enabled
  * @rmtoll CSR1       BREN            LL_PWR_IsEnabledBkUpRegulator
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBkUpRegulator(void)
{
  return ((READ_BIT(PWR->CSR1, PWR_CSR1_BREN) == (PWR_CSR1_BREN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable VBAT and Temperature monitoring
  * @rmtoll CSR1       MONEN           LL_PWR_EnableMonitoring
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableMonitoring(void)
{
  SET_BIT(PWR->CSR1, PWR_CSR1_MONEN);
}

/**
  * @brief  Disable VBAT and Temperature monitoring
  * @rmtoll CSR1       MONEN           LL_PWR_DisableMonitoring
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableMonitoring(void)
{
  CLEAR_BIT(PWR->CSR1, PWR_CSR1_MONEN);
}

/**
  * @brief  Check if the VBAT and Temperature monitoring is enabled
  * @rmtoll CSR1       MONEN           LL_PWR_IsEnabledMonitoring
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledMonitoring(void)
{
  return ((READ_BIT(PWR->CSR1, PWR_CSR1_MONEN) == (PWR_CSR1_MONEN)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the PWR supply
  * @rmtoll CSR2       SDHILEVEL       LL_PWR_ConfigSupply
  * @rmtoll CSR2       SMPSEXTHP       LL_PWR_ConfigSupply
  * @rmtoll CSR2       SDEN            LL_PWR_ConfigSupply
  * @rmtoll CSR2       LDOEN           LL_PWR_ConfigSupply
  * @rmtoll CSR2       BYPASS          LL_PWR_ConfigSupply
  * @param  SupplySource This parameter can be one of the following values:
  *         @arg @ref LL_PWR_LDO_SUPPLY
  *         @arg @ref LL_PWR_DIRECT_SMPS_SUPPLY
  *         @arg @ref LL_PWR_SMPS_1V8_SUPPLIES_LDO
  *         @arg @ref LL_PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO
  *         @arg @ref LL_PWR_SMPS_1V8_SUPPLIES_EXT
  *         @arg @ref LL_PWR_EXTERNAL_SOURCE_SUPPLY
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ConfigSupply(uint32_t SupplySource)
{
  /* Set the power supply configuration */
  MODIFY_REG(PWR->CSR2, (PWR_CSR2_SDHILEVEL | PWR_CSR2_SMPSEXTHP | PWR_CSR2_SDEN | PWR_CSR2_LDOEN | PWR_CSR2_BYPASS),
             SupplySource);
}

/**
  * @brief  Get the PWR supply
  * @rmtoll CSR2       SDHILEVEL       LL_PWR_GetSupply
  * @rmtoll CSR2       SMPSEXTHP       LL_PWR_GetSupply
  * @rmtoll CSR2       SDEN            LL_PWR_GetSupply
  * @rmtoll CSR2       LDOEN           LL_PWR_GetSupply
  * @rmtoll CSR2       BYPASS          LL_PWR_GetSupply
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_LDO_SUPPLY
  *         @arg @ref LL_PWR_DIRECT_SMPS_SUPPLY
  *         @arg @ref LL_PWR_SMPS_1V8_SUPPLIES_LDO
  *         @arg @ref LL_PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO
  *         @arg @ref LL_PWR_SMPS_1V8_SUPPLIES_EXT
  *         @arg @ref LL_PWR_EXTERNAL_SOURCE_SUPPLY
  */
__STATIC_INLINE uint32_t LL_PWR_GetSupply(void)
{
  /* Get the power supply configuration */
  return READ_BIT(PWR->CSR2,
                  (PWR_CSR2_SDHILEVEL | PWR_CSR2_SMPSEXTHP | PWR_CSR2_SDEN | PWR_CSR2_LDOEN | PWR_CSR2_BYPASS));
}

/**
  * @brief  Enable VBAT battery charging
  * @rmtoll CSR2       VBE             LL_PWR_EnableBatteryCharging
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBatteryCharging(void)
{
  SET_BIT(PWR->CSR2, PWR_CSR2_VBE);
}

/**
  * @brief  Disable VBAT battery charging
  * @rmtoll CSR2       VBE             LL_PWR_DisableBatteryCharging
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBatteryCharging(void)
{
  CLEAR_BIT(PWR->CSR2, PWR_CSR2_VBE);
}

/**
  * @brief  Check if VBAT battery charging is enabled
  * @rmtoll CSR2       VBE             LL_PWR_IsEnabledBatteryCharging
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBatteryCharging(void)
{
  return ((READ_BIT(PWR->CSR2, PWR_CSR2_VBE) == (PWR_CSR2_VBE)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Battery charge resistor impedance
  * @rmtoll CSR2       VBRS            LL_PWR_SetBattChargResistor
  * @param  Resistor This parameter can be one of the following values:
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_5K
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_1_5K
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetBattChargResistor(uint32_t Resistor)
{
  MODIFY_REG(PWR->CSR2, PWR_CSR2_VBRS, Resistor);
}

/**
  * @brief  Get the Battery charge resistor impedance
  * @rmtoll CSR2       VBRS            LL_PWR_GetBattChargResistor
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_5K
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_1_5K
  */
__STATIC_INLINE uint32_t LL_PWR_GetBattChargResistor(void)
{
  return (READ_BIT(PWR->CSR2, PWR_CSR2_VBRS));
}

/**
  * @brief  Set the XSPI port 1 capacitor value
  * @rmtoll CSR2       XSPICAP1        LL_PWR_SetXSPI1Capacitor
  * @param  Capacitor This parameter can be one of the following values:
  *         @arg @ref LL_PWR_XSPI1_CAPACITOR_OFF
  *         @arg @ref LL_PWR_XSPI1_CAPACITOR_1_DIV_3
  *         @arg @ref LL_PWR_XSPI1_CAPACITOR_2_DIV_3
  *         @arg @ref LL_PWR_XSPI1_CAPACITOR_FULL
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetXSPI1Capacitor(uint32_t Capacitor)
{
  MODIFY_REG(PWR->CSR2, PWR_CSR2_XSPICAP1, Capacitor);
}

/**
  * @brief  Get the XSPI port 1 capacitor value
  * @rmtoll CSR2       XSPICAP1        LL_PWR_GetXSPI1Capacitor
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_XSPI1_CAPACITOR_OFF
  *         @arg @ref LL_PWR_XSPI1_CAPACITOR_1_DIV_3
  *         @arg @ref LL_PWR_XSPI1_CAPACITOR_2_DIV_3
  *         @arg @ref LL_PWR_XSPI1_CAPACITOR_FULL
  */
__STATIC_INLINE uint32_t LL_PWR_GetXSPI1Capacitor(void)
{
  return (READ_BIT(PWR->CSR2, PWR_CSR2_XSPICAP1));
}

/**
  * @brief  Set the XSPI port 2 capacitor value
  * @rmtoll CSR2       XSPICAP2        LL_PWR_SetXSPI2Capacitor
  * @param  Capacitor This parameter can be one of the following values:
  *         @arg @ref LL_PWR_XSPI2_CAPACITOR_OFF
  *         @arg @ref LL_PWR_XSPI2_CAPACITOR_1_DIV_3
  *         @arg @ref LL_PWR_XSPI2_CAPACITOR_2_DIV_3
  *         @arg @ref LL_PWR_XSPI2_CAPACITOR_FULL
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetXSPI2Capacitor(uint32_t Capacitor)
{
  MODIFY_REG(PWR->CSR2, PWR_CSR2_XSPICAP2, Capacitor);
}

/**
  * @brief  Get the XSPI port 2 capacitor value
  * @rmtoll CSR2       XSPICAP2        LL_PWR_GetXSPI2Capacitor
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_XSPI2_CAPACITOR_OFF
  *         @arg @ref LL_PWR_XSPI2_CAPACITOR_1_DIV_3
  *         @arg @ref LL_PWR_XSPI2_CAPACITOR_2_DIV_3
  *         @arg @ref LL_PWR_XSPI2_CAPACITOR_FULL
  */
__STATIC_INLINE uint32_t LL_PWR_GetXSPI2Capacitor(void)
{
  return (uint32_t)(READ_BIT(PWR->CSR2, PWR_CSR2_XSPICAP2));
}

/**
  * @brief  Enable the USB voltage detector
  * @rmtoll CSR2       USB33DEN        LL_PWR_EnableUSBVoltageDetector
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableUSBVoltageDetector(void)
{
  SET_BIT(PWR->CSR2, PWR_CSR2_USB33DEN);
}

/**
  * @brief  Disable the USB voltage detector
  * @rmtoll CSR2       USB33DEN        LL_PWR_DisableUSBVoltageDetector
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableUSBVoltageDetector(void)
{
  CLEAR_BIT(PWR->CSR2, PWR_CSR2_USB33DEN);
}

/**
  * @brief  Check if the USB voltage detector is enabled
  * @rmtoll CSR2       USB33DEN        LL_PWR_IsEnabledUSBVoltageDetector
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUSBVoltageDetector(void)
{
  return ((READ_BIT(PWR->CSR2, PWR_CSR2_USB33DEN) == (PWR_CSR2_USB33DEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the USB regulator
  * @rmtoll CSR2       USBREGEN        LL_PWR_EnableUSBReg
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableUSBReg(void)
{
  SET_BIT(PWR->CSR2, PWR_CSR2_USBREGEN);
}

/**
  * @brief  Disable the USB regulator
  * @rmtoll CSR2       USBREGEN        LL_PWR_DisableUSBReg
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableUSBReg(void)
{
  CLEAR_BIT(PWR->CSR2, PWR_CSR2_USBREGEN);
}

/**
  * @brief  Check if the USB regulator is enabled
  * @rmtoll CSR2       USBREGEN        LL_PWR_IsEnabledUSBReg
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUSBReg(void)
{
  return ((READ_BIT(PWR->CSR2, PWR_CSR2_USBREGEN) == (PWR_CSR2_USBREGEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the USB HS PHY regulator
  * @rmtoll CSR2       USBHSREGEN      LL_PWR_EnableUSBHSPHYReg
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableUSBHSPHYReg(void)
{
  SET_BIT(PWR->CSR2, PWR_CSR2_USBHSREGEN);
}

/**
  * @brief  Disable USB HS PHY regulator
  * @rmtoll CSR2       USBHSREGEN      LL_PWR_DisableUSBHSPHYReg
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableUSBHSPHYReg(void)
{
  CLEAR_BIT(PWR->CSR2, PWR_CSR2_USBHSREGEN);
}

/**
  * @brief  Check if the USB HS PHY regulator is enabled
  * @rmtoll CSR2       USBHSREGEN      LL_PWR_IsEnabledUSBHSPHYReg
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUSBHSPHYReg(void)
{
  return ((READ_BIT(PWR->CSR2, PWR_CSR2_USBHSREGEN) == (PWR_CSR2_USBHSREGEN)) ? 1UL : 0UL);
}

/**
  * @brief Enable UCPD configuration memorization in Standby.
  * @rmtoll UCPDR      UCPD_STBY       LL_PWR_EnableUCPDStandbyMode
  * @retval None
  * @note  This function must be called just before entering Standby mode when using UCPD.
  */
__STATIC_INLINE void LL_PWR_EnableUCPDStandbyMode(void)
{
  /* Memorize UCPD configuration when entering standby mode */
  SET_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STBY);
}

/**
  * @brief Disable UCPD configuration memorization in Standby.
  * @rmtoll UCPDR      UCPD_STBY       LL_PWR_DisableUCPDStandbyMode
  * @retval None
  * @note  This function must be called on exiting the Standby mode and before any UCPD
  *        configuration update.
  */
__STATIC_INLINE void LL_PWR_DisableUCPDStandbyMode(void)
{
  CLEAR_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STBY);
}

/**
  * @brief  Check if the UCPD configuration memorization in Standby is enabled
  * @rmtoll UCPDR      UCPD_STBY       LL_PWR_IsEnabledUCPDStandbyMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUCPDStandbyMode(void)
{
  return ((READ_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STBY) == (PWR_UCPDR_UCPD_STBY)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the UCPD dead battery behavior
  * @rmtoll UCPDR       UCPD_DBDIS      LL_PWR_EnableUCPDDeadBattery
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableUCPDDeadBattery(void)
{
  CLEAR_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS);
}

/**
  * @brief  Disable the UCPD dead battery behavior
  * @rmtoll UCPDR       UCPD_DBDIS      LL_PWR_DisableUCPDDeadBattery
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableUCPDDeadBattery(void)
{
  SET_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS);
}

/**
  * @brief  Check if the UCPD dead battery behavior is enabled
  * @rmtoll UCPDR       UCPD_DBDIS      LL_PWR_IsEnabledUCPDDeadBattery
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUCPDDeadBattery(void)
{
  return ((READ_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS) == (PWR_UCPDR_UCPD_DBDIS)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the XSPI_P1 interface
  * @rmtoll CSR2       EN_XSPIM1      LL_PWR_EnableXSPIM1
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableXSPIM1(void)
{
  SET_BIT(PWR->CSR2, PWR_CSR2_EN_XSPIM1);
}

/**
  * @brief  Disable the XSPI_P1 interface
  * @rmtoll CSR2       EN_XSPIM1      LL_PWR_DisableXSPIM1
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableXSPIM1(void)
{
  CLEAR_BIT(PWR->CSR2, PWR_CSR2_EN_XSPIM1);
}

/**
  * @brief  Check if the XSPI_P1 interface is enabled
  * @rmtoll CSR2       EN_XSPIM1      LL_PWR_IsEnabledXSPIM1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledXSPIM1(void)
{
  return ((READ_BIT(PWR->CSR2, PWR_CSR2_EN_XSPIM1) == (PWR_CSR2_EN_XSPIM1)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the XSPI_P2 interface
  * @rmtoll CSR2       EN_XSPIM2      LL_PWR_EnableXSPIM2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableXSPIM2(void)
{
  SET_BIT(PWR->CSR2, PWR_CSR2_EN_XSPIM2);
}

/**
  * @brief  Disable the XSPI_P2 interface
  * @rmtoll CSR2       EN_XSPIM2      LL_PWR_DisableXSPIM2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableXSPIM2(void)
{
  CLEAR_BIT(PWR->CSR2, PWR_CSR2_EN_XSPIM2);
}

/**
  * @brief  Check if the XSPI_P2 interface is enabled
  * @rmtoll CSR2       EN_XSPIM2      LL_PWR_IsEnabledXSPIM2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledXSPIM2(void)
{
  return ((READ_BIT(PWR->CSR2, PWR_CSR2_EN_XSPIM2) == (PWR_CSR2_EN_XSPIM2)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Power Down mode when device enters deepsleep mode
  * @rmtoll CSR3       PDDS            LL_PWR_SetPowerDownModeDS
  * @param  PDMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_POWERDOWN_MODE_DS_STOP
  *         @arg @ref LL_PWR_POWERDOWN_MODE_DS_STANDBY
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPowerDownModeDS(uint32_t PDMode)
{
  MODIFY_REG(PWR->CSR3, PWR_CSR3_PDDS, PDMode);
}

/**
  * @brief  Get the Power Down mode when device enters deepsleep mode
  * @rmtoll CSR3       PDDS            LL_PWR_GetPowerDownModeDS
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_POWERDOWN_MODE_DS_STOP
  *         @arg @ref LL_PWR_POWERDOWN_MODE_DS_STANDBY
  */
__STATIC_INLINE uint32_t LL_PWR_GetPowerDownModeDS(void)
{
  return (uint32_t)(READ_BIT(PWR->CSR3, PWR_CSR3_PDDS));
}

/**
  * @brief  Set the main internal Regulator output voltage
  * @rmtoll CSR4       VOS             LL_PWR_SetRegulVoltageScaling
  * @param  VoltageScaling This parameter can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE0
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE1
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRegulVoltageScaling(uint32_t VoltageScaling)
{
  MODIFY_REG(PWR->CSR4, PWR_CSR4_VOS, VoltageScaling);
}

/**
  * @brief  Get the main internal Regulator output voltage
  * @rmtoll CSR4       VOS             LL_PWR_GetRegulVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE0
  *         @arg @ref LL_PWR_REGU_VOLTAGE_SCALE1
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulVoltageScaling(void)
{
  return (uint32_t)(READ_BIT(PWR->CSR4, PWR_CSR4_VOS));
}

/**
  * @brief  Set the internal Regulator output voltage in STOP mode
  * @rmtoll CR1        SVOS            LL_PWR_SetStopModeRegulVoltageScaling
  * @param  VoltageScaling This parameter can be one of the following values:
  *         @arg @ref LL_PWR_REGU_STOP_VOLTAGE_SCALE3
  *         @arg @ref LL_PWR_REGU_STOP_VOLTAGE_SCALE5
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetStopModeRegulVoltageScaling(uint32_t VoltageScaling)
{
  MODIFY_REG(PWR->CR1, PWR_CR1_SVOS, VoltageScaling);
}

/**
  * @brief  Get the internal Regulator output voltage in STOP mode
  * @rmtoll CR1        SVOS            LL_PWR_GetStopModeRegulVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_STOP_VOLTAGE_SCALE3
  *         @arg @ref LL_PWR_REGU_STOP_VOLTAGE_SCALE5
  */
__STATIC_INLINE uint32_t LL_PWR_GetStopModeRegulVoltageScaling(void)
{
  return READ_BIT(PWR->CR1, PWR_CR1_SVOS);
}

/**
  * @brief  Enable the WakeUp PINx functionality
  * @rmtoll WKUPEPR    WKUPEN1         LL_PWR_EnableWakeUpPin\n
  *         WKUPEPR    WKUPEN2         LL_PWR_EnableWakeUpPin\n
  *         WKUPEPR    WKUPEN3         LL_PWR_EnableWakeUpPin\n
  *         WKUPEPR    WKUPEN4         LL_PWR_EnableWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableWakeUpPin(uint32_t WakeUpPin)
{
  SET_BIT(PWR->WKUPEPR, WakeUpPin);
}

/**
  * @brief  Disable the WakeUp PINx functionality
  * @rmtoll WKUPEPR   WKUPEN1          LL_PWR_DisableWakeUpPin\n
  *         WKUPEPR   WKUPEN2          LL_PWR_DisableWakeUpPin\n
  *         WKUPEPR   WKUPEN3          LL_PWR_DisableWakeUpPin\n
  *         WKUPEPR   WKUPEN4          LL_PWR_DisableWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableWakeUpPin(uint32_t WakeUpPin)
{
  CLEAR_BIT(PWR->WKUPEPR, WakeUpPin);
}

/**
  * @brief  Check if the WakeUp PINx functionality is enabled
  * @rmtoll WKUPEPR    WKUPEN1         LL_PWR_IsEnabledWakeUpPin\n
  *         WKUPEPR    WKUPEN2         LL_PWR_IsEnabledWakeUpPin\n
  *         WKUPEPR    WKUPEN3         LL_PWR_IsEnabledWakeUpPin\n
  *         WKUPEPR    WKUPEN4         LL_PWR_IsEnabledWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWakeUpPin(uint32_t WakeUpPin)
{
  return ((READ_BIT(PWR->WKUPEPR, WakeUpPin) == (WakeUpPin)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Wake-Up pin polarity low for the event detection
  * @rmtoll WKUPEPR    WKUPP1          LL_PWR_SetWakeUpPinPolarityLow\n
  *         WKUPEPR    WKUPP2          LL_PWR_SetWakeUpPinPolarityLow\n
  *         WKUPEPR    WKUPP3          LL_PWR_SetWakeUpPinPolarityLow\n
  *         WKUPEPR    WKUPP4          LL_PWR_SetWakeUpPinPolarityLow
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityLow(uint32_t WakeUpPin)
{
  SET_BIT(PWR->WKUPEPR, (WakeUpPin << PWR_WKUPEPR_WKUPP1_Pos));
}

/**
  * @brief  Set the Wake-Up pin polarity high for the event detection
  * @rmtoll WKUPEPR    WKUPP1          LL_PWR_SetWakeUpPinPolarityHigh\n
  *         WKUPEPR    WKUPP2          LL_PWR_SetWakeUpPinPolarityHigh\n
  *         WKUPEPR    WKUPP3          LL_PWR_SetWakeUpPinPolarityHigh\n
  *         WKUPEPR    WKUPP4          LL_PWR_SetWakeUpPinPolarityHigh
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityHigh(uint32_t WakeUpPin)
{
  CLEAR_BIT(PWR->WKUPEPR, (WakeUpPin << PWR_WKUPEPR_WKUPP1_Pos));
}

/**
  * @brief  Check if the Wake-Up pin polarity is low for event detection
  * @rmtoll WKUPEPR    WKUPP1          LL_PWR_IsWakeUpPinPolarityLow\n
  *         WKUPEPR    WKUPP2          LL_PWR_IsWakeUpPinPolarityLow\n
  *         WKUPEPR    WKUPP3          LL_PWR_IsWakeUpPinPolarityLow\n
  *         WKUPEPR    WKUPP4          LL_PWR_IsWakeUpPinPolarityLow
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsWakeUpPinPolarityLow(uint32_t WakeUpPin)
{
  return ((READ_BIT(PWR->WKUPEPR, (WakeUpPin << PWR_WKUPEPR_WKUPP1_Pos)) == (WakeUpPin << PWR_WKUPEPR_WKUPP1_Pos)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Wake-Up pin Pull None
  * @rmtoll WKUPEPR    WKUPPUPD1       LL_PWR_SetWakeUpPinPullNone\n
  *         WKUPEPR    WKUPPUPD2       LL_PWR_SetWakeUpPinPullNone\n
  *         WKUPEPR    WKUPPUPD3       LL_PWR_SetWakeUpPinPullNone\n
  *         WKUPEPR    WKUPPUPD4       LL_PWR_SetWakeUpPinPullNone
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
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
  * @rmtoll WKUPEPR    WKUPPUPD1       LL_PWR_SetWakeUpPinPullUp\n
  *         WKUPEPR    WKUPPUPD2       LL_PWR_SetWakeUpPinPullUp\n
  *         WKUPEPR    WKUPPUPD3       LL_PWR_SetWakeUpPinPullUp\n
  *         WKUPEPR    WKUPPUPD4       LL_PWR_SetWakeUpPinPullUp
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
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
  * @rmtoll WKUPEPR    WKUPPUPD1       LL_PWR_SetWakeUpPinPullDown\n
  *         WKUPEPR    WKUPPUPD2       LL_PWR_SetWakeUpPinPullDown\n
  *         WKUPEPR    WKUPPUPD3       LL_PWR_SetWakeUpPinPullDown\n
  *         WKUPEPR    WKUPPUPD4       LL_PWR_SetWakeUpPinPullDown
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
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
  * @rmtoll WKUPEPR    WKUPPUPD1       LL_PWR_GetWakeUpPinPull\n
  *         WKUPEPR    WKUPPUPD2       LL_PWR_GetWakeUpPinPull\n
  *         WKUPEPR    WKUPPUPD3       LL_PWR_GetWakeUpPinPull\n
  *         WKUPEPR    WKUPPUPD4       LL_PWR_GetWakeUpPinPull\
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3
  *         @arg @ref LL_PWR_WAKEUP_PIN4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_NOPULL
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULLUP
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULLDOWN
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeUpPinPull(uint32_t WakeUpPin)
{
  uint32_t regValue = READ_BIT(PWR->WKUPEPR, (PWR_WKUPEPR_WKUPPUPD1 << ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * POSITION_VAL(WakeUpPin)) & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)));

  return (uint32_t)(regValue >> ((PWR_WKUPEPR_WKUPPUPD1_Pos + (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * POSITION_VAL(WakeUpPin))) & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK));
}

/**
  * @brief  Enable the pull-up on I3C1_SCL (PB6)) in standby mode
  * @rmtoll APCR       I3CPB6_PU       LL_PWR_EnableI3CPB6PU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableI3CPB6PU(void)
{
  SET_BIT(PWR->APCR, PWR_APCR_I3CPB6_PU);
}

/**
  * @brief  Disable the pull-up on I3C1_SCL (PB6) in standby mode
  * @rmtoll APCR       I3CPB6_PU       LL_PWR_DisableI3CPB6PU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableI3CPB6PU(void)
{
  CLEAR_BIT(PWR->APCR, PWR_APCR_I3CPB6_PU);
}

/**
  * @brief  Check if the pull-up on I3C1_SCL (PB6) in standby mode is enabled
  * @rmtoll APCR       I3CPB6_PU       LL_PWR_IsEnabledI3CPB6PU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledI3CPB6PU(void)
{
  return ((READ_BIT(PWR->APCR, PWR_APCR_I3CPB6_PU) == (PWR_APCR_I3CPB6_PU)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the pull-up on I3C1_SDA (PB7) in standby mode
  * @rmtoll APCR       I3CPB7_PU       LL_PWR_EnableI3CPB7PU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableI3CPB7PU(void)
{
  SET_BIT(PWR->APCR, PWR_APCR_I3CPB7_PU);
}

/**
  * @brief  Disable the pull-up on I3C1_SDA (PB7) in standby mode
  * @rmtoll APCR       I3CPB7_PU       LL_PWR_DisableI3CPB7PU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableI3CPB7PU(void)
{
  CLEAR_BIT(PWR->APCR, PWR_APCR_I3CPB7_PU);
}

/**
  * @brief  Check if the pull-up on I3C1_SDA (PB7) in standby mode is enabled
  * @rmtoll APCR       I3CPB7_PU       LL_PWR_IsEnabledI3CPB7PU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledI3CPB7PU(void)
{
  return ((READ_BIT(PWR->APCR, PWR_APCR_I3CPB7_PU) == (PWR_APCR_I3CPB7_PU)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the pull-up on I3C1_SCL (PB8) in standby mode
  * @rmtoll APCR       I3CPB8_PU       LL_PWR_EnableI3CPB8PU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableI3CPB8PU(void)
{
  SET_BIT(PWR->APCR, PWR_APCR_I3CPB8_PU);
}

/**
  * @brief  Disable the pull-up on I3C1_SCL (PB8) in standby mode
  * @rmtoll APCR       I3CPB8_PU       LL_PWR_DisableI3CPB8PU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableI3CPB8PU(void)
{
  CLEAR_BIT(PWR->APCR, PWR_APCR_I3CPB8_PU);
}

/**
  * @brief  Check if the pull-up on I3C1_SCL (PB8) in standby mode is enabled
  * @rmtoll APCR       I3CPB8_PU       LL_PWR_IsEnabledI3CPB8PU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledI3CPB8PU(void)
{
  return ((READ_BIT(PWR->APCR, PWR_APCR_I3CPB8_PU) == (PWR_APCR_I3CPB8_PU)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the pull-up on I3C1_SDA (PB9) in standby mode
  * @rmtoll APCR       I3CPB9_PU       LL_PWR_EnableI3CPB9PU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableI3CPB9PU(void)
{
  SET_BIT(PWR->APCR, PWR_APCR_I3CPB9_PU);
}

/**
  * @brief  Disable the pull-up on I3C1_SDA (PB9) in standby mode
  * @rmtoll APCR       I3CPB9_PU       LL_PWR_DisableI3CPB9PU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableI3CPB9PU(void)
{
  CLEAR_BIT(PWR->APCR, PWR_APCR_I3CPB9_PU);
}

/**
  * @brief  Check if the pull-up on I3C1_SDA (PB9) in standby mode is enabled
  * @rmtoll APCR       I3CPB9_PU       LL_PWR_IsEnabledI3CPB9PU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledI3CPB9PU(void)
{
  return ((READ_BIT(PWR->APCR, PWR_APCR_I3CPB9_PU) == (PWR_APCR_I3CPB9_PU)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the pull-up and pull-down configuration
  * @rmtoll APCR          APC           LL_PWR_EnablePUPDConfig
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePUPDConfig(void)
{
  SET_BIT(PWR->APCR, PWR_APCR_APC);
}

/**
  * @brief  Disable the pull-up and pull-down configuration
  * @rmtoll APCR          APC           LL_PWR_DisablePUPDConfig
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePUPDConfig(void)
{
  CLEAR_BIT(PWR->APCR, PWR_APCR_APC);
}

/**
  * @brief  Check if the pull-up and pull-down configuration is enabled.
  * @rmtoll APCR          APC           LL_PWR_IsEnabledPUPDConfig
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPUPDConfig(void)
{
  return ((READ_BIT(PWR->APCR, PWR_APCR_APC) == (PWR_APCR_APC)) ? 1UL : 0UL);
}

/**
  * @brief  Enable GPIO N pull-up in Standby mode
  * @rmtoll PUCRN        PUx        LL_PWR_EnableGPIONPullUp
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_6
  *         @arg @ref LL_PWR_GPIO_PIN_12
  * @retval None.
  */
__STATIC_INLINE void LL_PWR_EnableGPIONPullUp(uint32_t GPIOPin)
{
  SET_BIT(PWR->PUCRN, GPIOPin);
}

/**
  * @brief  Disable GPIO N pull-up in Standby mode
  * @rmtoll PUCRN        PUx        LL_PWR_DisableGPIONPullUp
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_6
  *         @arg @ref LL_PWR_GPIO_PIN_12
  * @retval None.
  */
__STATIC_INLINE void LL_PWR_DisableGPIONPullUp(uint32_t GPIOPin)
{
  CLEAR_BIT(PWR->PUCRN, GPIOPin);
}

/**
  * @brief  Check if GPIO pull-up in Standby mode is enabled
  * @rmtoll PUCRN        PUx        LL_PWR_IsEnabledGPIONPullUp
  * @param  GPIOPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_6
  *         @arg @ref LL_PWR_GPIO_PIN_12
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledGPIONPullUp(uint32_t GPIOPin)
{
  return ((READ_BIT(PWR->PUCRN, GPIOPin) == (GPIOPin)) ? 1UL : 0UL);
}

/**
  * @brief  Enable GPIO O pull-up in Standby mode
  * @rmtoll PUCRO        PUx        LL_PWR_EnableGPIOOPullUp
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_4

  * @retval None.
  */
__STATIC_INLINE void LL_PWR_EnableGPIOOPullUp(uint32_t GPIOPin)
{
  SET_BIT(PWR->PUCRO, GPIOPin);
}

/**
  * @brief  Disable GPIO O pull-up in Standby mode
  * @rmtoll PUCRO        PUx        LL_PWR_DisableGPIOOPullUp
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_4
  * @retval None.
  */
__STATIC_INLINE void LL_PWR_DisableGPIOOPullUp(uint32_t GPIOPin)
{
  CLEAR_BIT(PWR->PUCRO, GPIOPin);
}

/**
  * @brief  Check if GPIO O pull-up in Standby mode is enabled
  * @rmtoll PUCRO        PUx        LL_PWR_IsEnabledGPIOOPullUp
  * @param  GPIOPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_4
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledGPIOOPullUp(uint32_t GPIOPin)
{
  return ((READ_BIT(PWR->PUCRO, GPIOPin) == (GPIOPin)) ? 1UL : 0UL);
}

/**
  * @brief  Enable GPIO N pull-down in Standby mode
  * @rmtoll PDCRN        PDx        LL_PWR_EnableGPIONPullDown
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_2
  *         @arg @ref LL_PWR_GPIO_PIN_6
  *         @arg @ref LL_PWR_GPIO_PIN_8
  *         @arg @ref LL_PWR_GPIO_PIN_12
  * @retval None.
  */
__STATIC_INLINE void LL_PWR_EnableGPIONPullDown(uint32_t GPIOPin)
{
  SET_BIT(PWR->PDCRN, GPIOPin);
}

/**
  * @brief  Disable GPIO N pull-down in Standby mode
  * @rmtoll PDCRN        PDx        LL_PWR_DisableGPIONPullDown
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_2
  *         @arg @ref LL_PWR_GPIO_PIN_6
  *         @arg @ref LL_PWR_GPIO_PIN_8
  *         @arg @ref LL_PWR_GPIO_PIN_12
  * @retval None.
  */
__STATIC_INLINE void LL_PWR_DisableGPIONPullDown(uint32_t GPIOPin)
{
  CLEAR_BIT(PWR->PDCRN, GPIOPin);
}

/**
  * @brief  Check if GPIO N pull-down in Standby mode is enabled
  * @rmtoll PDCRN        PDx        LL_PWR_IsEnabledGPIONPullDown
  * @param  GPIOPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_2
  *         @arg @ref LL_PWR_GPIO_PIN_6
  *         @arg @ref LL_PWR_GPIO_PIN_8
  *         @arg @ref LL_PWR_GPIO_PIN_12
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledGPIONPullDown(uint32_t GPIOPin)
{
  return ((READ_BIT(PWR->PDCRN, GPIOPin) == (GPIOPin)) ? 1UL : 0UL);
}
/**
  * @brief  Enable GPIO O pull-down in Standby mode
  * @rmtoll PDCRO        PDx        LL_PWR_EnableGPIOOPullDown
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_2
  *         @arg @ref LL_PWR_GPIO_PIN_3
  *         @arg @ref LL_PWR_GPIO_PIN_4
  * @retval None.
  */
__STATIC_INLINE void LL_PWR_EnableGPIOOPullDown(uint32_t GPIOPin)
{
  SET_BIT(PWR->PDCRO, GPIOPin);
}

/**
  * @brief  Disable GPIO O pull-down in Standby mode
  * @rmtoll PDCRO        PDx        LL_PWR_DisableGPIOOPullDown
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_2
  *         @arg @ref LL_PWR_GPIO_PIN_3
  *         @arg @ref LL_PWR_GPIO_PIN_4
  * @retval None.
  */
__STATIC_INLINE void LL_PWR_DisableGPIOOPullDown(uint32_t GPIOPin)
{
  CLEAR_BIT(PWR->PDCRO, GPIOPin);
}

/**
  * @brief  Check if GPIO O pull-down in Standby mode is enabled
  * @rmtoll PDCRO        PDx        LL_PWR_IsEnabledGPIOOPullDown
  * @param  GPIOPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_1
  *         @arg @ref LL_PWR_GPIO_PIN_2
  *         @arg @ref LL_PWR_GPIO_PIN_3
  *         @arg @ref LL_PWR_GPIO_PIN_4
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledGPIOOPullDown(uint32_t GPIOPin)
{
  return ((READ_BIT(PWR->PDCRO, GPIOPin) == (GPIOPin)) ? 1UL : 0UL);
}

/**
  * @brief  Enable GPIO P pull-down in Standby mode
  * @rmtoll PDCRP        PDx        LL_PWR_EnableGPIOPPullDown
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_4
  *         @arg @ref LL_PWR_GPIO_PIN_8
  *         @arg @ref LL_PWR_GPIO_PIN_12
  * @retval None.
  */
__STATIC_INLINE void LL_PWR_EnableGPIOPPullDown(uint32_t GPIOPin)
{
  SET_BIT(PWR->PDCRP, GPIOPin);
}

/**
  * @brief  Disable GPIO P pull-down in Standby mode
  * @rmtoll PDCRP        PDx        LL_PWR_DisableGPIOPPullDown
  * @param  GPIOPin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_4
  *         @arg @ref LL_PWR_GPIO_PIN_8
  *         @arg @ref LL_PWR_GPIO_PIN_12
  * @retval None.
  */
__STATIC_INLINE void LL_PWR_DisableGPIOPPullDown(uint32_t GPIOPin)
{
  CLEAR_BIT(PWR->PDCRP, GPIOPin);
}

/**
  * @brief  Check if GPIO P pull-down in Standby mode is enabled
  * @rmtoll PDCRP        PDx        LL_PWR_IsEnabledGPIOPPullDown
  * @param  GPIOPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_GPIO_PIN_0
  *         @arg @ref LL_PWR_GPIO_PIN_4
  *         @arg @ref LL_PWR_GPIO_PIN_8
  *         @arg @ref LL_PWR_GPIO_PIN_12
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledGPIOPPullDown(uint32_t GPIOPin)
{
  return ((READ_BIT(PWR->PDCRP, GPIOPin) == (GPIOPin)) ? 1UL : 0UL);
}
/**
  * @}
  */


/** @defgroup PWR_LL_EF_FLAG_MANAGEMENT PWR FLAG Management
  * @{
  */

/**
  * @brief  Indicate whether the voltage level is ready for current actual used VOS
  * @rmtoll SR1        ACTVOSRDY       LL_PWR_IsActiveFlag_ACTVOSRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_ACTVOSRDY(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_ACTVOSRDY) == (PWR_SR1_ACTVOSRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether VDD voltage is below the selected PVD threshold
  * @rmtoll SR1        PVDO            LL_PWR_IsActiveFlag_PVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_PVDO(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_PVDO) == (PWR_SR1_PVDO)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether VDDA voltage is below the selected AVD threshold
  * @rmtoll SR1        AVDO            LL_PWR_IsActiveFlag_AVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_AVDO(void)
{
  return ((READ_BIT(PWR->SR1, PWR_SR1_AVDO) == (PWR_SR1_AVDO)) ? 1UL : 0UL);
}

/**
  * @brief  Get Backup Regulator ready Flag
  * @rmtoll CSR1       BRRDY           LL_PWR_IsActiveFlag_BRRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_BRRDY(void)
{
  return ((READ_BIT(PWR->CSR1, PWR_CSR1_BRRDY) == (PWR_CSR1_BRRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VBAT level is above or below low threshold
  * @rmtoll CSR1       VBATL           LL_PWR_IsActiveFlag_VBATL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VBATL(void)
{
  return ((READ_BIT(PWR->CSR1, PWR_CSR1_VBATL) == (PWR_CSR1_VBATL)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VBAT level is above or below high threshold
  * @rmtoll CSR1       VBATH           LL_PWR_IsActiveFlag_VBATH
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VBATH(void)
{
  return ((READ_BIT(PWR->CSR1, PWR_CSR1_VBATH) == (PWR_CSR1_VBATH)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the CPU temperature level is above or below low threshold
  * @rmtoll CSR1       TEMPL           LL_PWR_IsActiveFlag_TEMPL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_TEMPL(void)
{
  return ((READ_BIT(PWR->CSR1, PWR_CSR1_TEMPL) == (PWR_CSR1_TEMPL)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the CPU temperature level is above or below high threshold
  * @rmtoll CSR1       TEMPH           LL_PWR_IsActiveFlag_TEMPH
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_TEMPH(void)
{
  return ((READ_BIT(PWR->CSR1, PWR_CSR1_TEMPH) == (PWR_CSR1_TEMPH)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the SMPS external supply is ready or not
  * @rmtoll CSR2       SDEXTRDY        LL_PWR_IsActiveFlag_SDEXTRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_SDEXTRDY(void)
{
  return ((READ_BIT(PWR->CSR2, PWR_CSR2_SDEXTRDY) == (PWR_CSR2_SDEXTRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the USB supply is ready or not
  * @rmtoll CSR2       USB33RDY        LL_PWR_IsActiveFlag_USB33RDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_USB33RDY(void)
{
  return ((READ_BIT(PWR->CSR2, PWR_CSR2_USB33RDY) == (PWR_CSR2_USB33RDY)) ? 1UL : 0UL);
}

/**
  * @brief  Get System Stop Flag
  * @rmtoll CSR3       STOPF           LL_PWR_IsActiveFlag_STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_STOP(void)
{
  return ((READ_BIT(PWR->CSR3, PWR_CSR3_STOPF) == (PWR_CSR3_STOPF)) ? 1UL : 0UL);
}

/**
  * @brief  Get System Standby Flag
  * @rmtoll CSR3       SBF             LL_PWR_IsActiveFlag_SB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_SB(void)
{
  return ((READ_BIT(PWR->CSR3, PWR_CSR3_SBF) == (PWR_CSR3_SBF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the Regulator is ready in the selected voltage range
  *         or if its output voltage is still changing to the required voltage level
  * @rmtoll CSR4       VOSRDY          LL_PWR_IsActiveFlag_VOSRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VOSRDY(void)
{
  return ((READ_BIT(PWR->CSR4, PWR_CSR4_VOSRDY) == (PWR_CSR4_VOSRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 1
  * @rmtoll WKUPFR     WKUPF1          LL_PWR_IsActiveFlag_WU1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU1(void)
{
  return ((READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF1) == (PWR_WKUPFR_WKUPF1)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 2
  * @rmtoll WKUPFR     WKUPF2          LL_PWR_IsActiveFlag_WU2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU2(void)
{
  return ((READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF2) == (PWR_WKUPFR_WKUPF2)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 3
  * @rmtoll WKUPFR     WKUPF3          LL_PWR_IsActiveFlag_WU3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU3(void)
{
  return ((READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF3) == (PWR_WKUPFR_WKUPF3)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 4
  * @rmtoll WKUPFR     WKUPF4          LL_PWR_IsActiveFlag_WU4
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU4(void)
{
  return ((READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF4) == (PWR_WKUPFR_WKUPF4)) ? 1UL : 0UL);
}

/**
  * @brief  Clear STOP and STANDBY and flags
  * @rmtoll CSR3       CSSF            LL_PWR_ClearFlag_STOP_SB
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_STOP_SB(void)
{
  SET_BIT(PWR->CSR3, PWR_CSR3_CSSF);
}

/**
  * @brief  Clear Wake-up Flag 1
  * @rmtoll WKUPCR     WKUPC1          LL_PWR_ClearFlag_WU1
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU1(void)
{
  WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC1);
}

/**
  * @brief  Clear Wake-up Flag 2
  * @rmtoll WKUPCR     WKUPC2          LL_PWR_ClearFlag_WU2
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU2(void)
{
  WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC2);
}

/**
  * @brief  Clear Wake-up Flag 3
  * @rmtoll WKUPCR     WKUPC3          LL_PWR_ClearFlag_WU3
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU3(void)
{
  WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC3);
}

/**
  * @brief  Clear Wake-up Flag 4
  * @rmtoll WKUPCR     WKUPC4          LL_PWR_ClearFlag_WU4
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU4(void)
{
  WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC4);
}

/**
  * @brief  Clear all wake up flags.
  * @rmtoll WUSCR          WKUPC         LL_PWR_ClearFlag_WU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU(void)
{
  WRITE_REG(PWR->WKUPCR, PWR_WKUPCR_WKUPC);
}

/**
  * @}
  */

#if defined (USE_FULL_LL_DRIVER)
/** @defgroup PWR_LL_EF_Init De-initialization function
  * @{
  */
ErrorStatus LL_PWR_DeInit(void);
/**
  * @}
  */
#endif /* defined (USE_FULL_LL_DRIVER) */


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined (PWR) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7RSxx_LL_PWR_H */


