/**
  ******************************************************************************
  * @file    stm32g4xx_hal.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the HAL
  *          module driver.
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
#ifndef STM32G4xx_HAL_H
#define STM32G4xx_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal_conf.h"

/** @addtogroup STM32G4xx_HAL_Driver
  * @{
  */

/** @addtogroup HAL HAL
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup HAL_Exported_Constants HAL Exported Constants
  * @{
  */

/** @defgroup HAL_TICK_FREQ Tick Frequency
  * @{
  */
#define HAL_TICK_FREQ_10HZ         100U
#define HAL_TICK_FREQ_100HZ        10U
#define HAL_TICK_FREQ_1KHZ         1U
#define HAL_TICK_FREQ_DEFAULT      HAL_TICK_FREQ_1KHZ

/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Constants SYSCFG Exported Constants
  * @{
  */

/** @defgroup SYSCFG_BootMode Boot Mode
  * @{
  */
#define SYSCFG_BOOT_MAINFLASH          0x00000000U
#define SYSCFG_BOOT_SYSTEMFLASH        SYSCFG_MEMMEMRMP_MODE_0

#if defined (FMC_BANK1)
#define SYSCFG_BOOT_FMC                SYSCFG_MEMMEMRMP_MODE_1
#endif /* FMC_BANK1 */

#define SYSCFG_BOOT_SRAM               (SYSCFG_MEMMEMRMP_MODE_1 | SYSCFG_MEMMEMRMP_MODE_0)

#if defined (QUADSPI)
#define SYSCFG_BOOT_QUADSPI            (SYSCFG_MEMMEMRMP_MODE_2 | SYSCFG_MEMMEMRMP_MODE_1)
#endif /* QUADSPI */

/**
  * @}
  */

/** @defgroup SYSCFG_FPU_Interrupts FPU Interrupts
  * @{
  */
#define SYSCFG_IT_FPU_IOC              SYSCFG_CFGR1_FPU_IE_0  /*!< Floating Point Unit Invalid operation Interrupt */
#define SYSCFG_IT_FPU_DZC              SYSCFG_CFGR1_FPU_IE_1  /*!< Floating Point Unit Divide-by-zero Interrupt */
#define SYSCFG_IT_FPU_UFC              SYSCFG_CFGR1_FPU_IE_2  /*!< Floating Point Unit Underflow Interrupt */
#define SYSCFG_IT_FPU_OFC              SYSCFG_CFGR1_FPU_IE_3  /*!< Floating Point Unit Overflow Interrupt */
#define SYSCFG_IT_FPU_IDC              SYSCFG_CFGR1_FPU_IE_4  /*!< Floating Point Unit Input denormal Interrupt */
#define SYSCFG_IT_FPU_IXC              SYSCFG_CFGR1_FPU_IE_5  /*!< Floating Point Unit Inexact Interrupt */

/**
  * @}
  */

/** @defgroup SYSCFG_CCMSRAMWRP CCM Write protection
  * @{
  */
#define SYSCFG_CCMSRAMWRP_PAGE0          SYSCFG_SWPR_PAGE0  /*!< CCMSRAM Write protection page 0 */
#define SYSCFG_CCMSRAMWRP_PAGE1          SYSCFG_SWPR_PAGE1  /*!< CCMSRAM Write protection page 1 */
#define SYSCFG_CCMSRAMWRP_PAGE2          SYSCFG_SWPR_PAGE2  /*!< CCMSRAM Write protection page 2 */
#define SYSCFG_CCMSRAMWRP_PAGE3          SYSCFG_SWPR_PAGE3  /*!< CCMSRAM Write protection page 3 */
#define SYSCFG_CCMSRAMWRP_PAGE4          SYSCFG_SWPR_PAGE4  /*!< CCMSRAM Write protection page 4 */
#define SYSCFG_CCMSRAMWRP_PAGE5          SYSCFG_SWPR_PAGE5  /*!< CCMSRAM Write protection page 5 */
#define SYSCFG_CCMSRAMWRP_PAGE6          SYSCFG_SWPR_PAGE6  /*!< CCMSRAM Write protection page 6 */
#define SYSCFG_CCMSRAMWRP_PAGE7          SYSCFG_SWPR_PAGE7  /*!< CCMSRAM Write protection page 7 */
#define SYSCFG_CCMSRAMWRP_PAGE8          SYSCFG_SWPR_PAGE8  /*!< CCMSRAM Write protection page 8 */
#define SYSCFG_CCMSRAMWRP_PAGE9          SYSCFG_SWPR_PAGE9  /*!< CCMSRAM Write protection page 9 */
#define SYSCFG_CCMSRAMWRP_PAGE10         SYSCFG_SWPR_PAGE10 /*!< CCMSRAM Write protection page 10 */
#define SYSCFG_CCMSRAMWRP_PAGE11         SYSCFG_SWPR_PAGE11 /*!< CCMSRAM Write protection page 11 */
#define SYSCFG_CCMSRAMWRP_PAGE12         SYSCFG_SWPR_PAGE12 /*!< CCMSRAM Write protection page 12 */
#define SYSCFG_CCMSRAMWRP_PAGE13         SYSCFG_SWPR_PAGE13 /*!< CCMSRAM Write protection page 13 */
#define SYSCFG_CCMSRAMWRP_PAGE14         SYSCFG_SWPR_PAGE14 /*!< CCMSRAM Write protection page 14 */
#define SYSCFG_CCMSRAMWRP_PAGE15         SYSCFG_SWPR_PAGE15 /*!< CCMSRAM Write protection page 15 */
#define SYSCFG_CCMSRAMWRP_PAGE16         SYSCFG_SWPR_PAGE16 /*!< CCMSRAM Write protection page 16 */
#define SYSCFG_CCMSRAMWRP_PAGE17         SYSCFG_SWPR_PAGE17 /*!< CCMSRAM Write protection page 17 */
#define SYSCFG_CCMSRAMWRP_PAGE18         SYSCFG_SWPR_PAGE18 /*!< CCMSRAM Write protection page 18 */
#define SYSCFG_CCMSRAMWRP_PAGE19         SYSCFG_SWPR_PAGE19 /*!< CCMSRAM Write protection page 19 */
#define SYSCFG_CCMSRAMWRP_PAGE20         SYSCFG_SWPR_PAGE20 /*!< CCMSRAM Write protection page 20 */
#define SYSCFG_CCMSRAMWRP_PAGE21         SYSCFG_SWPR_PAGE21 /*!< CCMSRAM Write protection page 21 */
#define SYSCFG_CCMSRAMWRP_PAGE22         SYSCFG_SWPR_PAGE22 /*!< CCMSRAM Write protection page 22 */
#define SYSCFG_CCMSRAMWRP_PAGE23         SYSCFG_SWPR_PAGE23 /*!< CCMSRAM Write protection page 23 */
#define SYSCFG_CCMSRAMWRP_PAGE24         SYSCFG_SWPR_PAGE24 /*!< CCMSRAM Write protection page 24 */
#define SYSCFG_CCMSRAMWRP_PAGE25         SYSCFG_SWPR_PAGE25 /*!< CCMSRAM Write protection page 25 */
#define SYSCFG_CCMSRAMWRP_PAGE26         SYSCFG_SWPR_PAGE26 /*!< CCMSRAM Write protection page 26 */
#define SYSCFG_CCMSRAMWRP_PAGE27         SYSCFG_SWPR_PAGE27 /*!< CCMSRAM Write protection page 27 */
#define SYSCFG_CCMSRAMWRP_PAGE28         SYSCFG_SWPR_PAGE28 /*!< CCMSRAM Write protection page 28 */
#define SYSCFG_CCMSRAMWRP_PAGE29         SYSCFG_SWPR_PAGE29 /*!< CCMSRAM Write protection page 29 */
#define SYSCFG_CCMSRAMWRP_PAGE30         SYSCFG_SWPR_PAGE30 /*!< CCMSRAM Write protection page 30 */
#define SYSCFG_CCMSRAMWRP_PAGE31         SYSCFG_SWPR_PAGE31 /*!< CCMSRAM Write protection page 31 */

/**
  * @}
  */

#if defined(VREFBUF)
/** @defgroup SYSCFG_VREFBUF_VoltageScale VREFBUF Voltage Scale
  * @{
  */
#define SYSCFG_VREFBUF_VOLTAGE_SCALE0  0x00000000U /*!< Voltage reference scale 0 (VREFBUF_OUT = 2.048V) */
#define SYSCFG_VREFBUF_VOLTAGE_SCALE1  VREFBUF_CSR_VRS_0      /*!< Voltage reference scale 1 (VREFBUF_OUT = 2.5V)   */
#define SYSCFG_VREFBUF_VOLTAGE_SCALE2  VREFBUF_CSR_VRS_1      /*!< Voltage reference scale 2 (VREFBUF_OUT = 2.9V)   */

/**
  * @}
  */

/** @defgroup SYSCFG_VREFBUF_HighImpedance VREFBUF High Impedance
  * @{
  */
#define SYSCFG_VREFBUF_HIGH_IMPEDANCE_DISABLE  0x00000000U       /*!< VREF_plus pin is internally connected to Voltage reference buffer output */
#define SYSCFG_VREFBUF_HIGH_IMPEDANCE_ENABLE   VREFBUF_CSR_HIZ       /*!< VREF_plus pin is high impedance */

/**
  * @}
  */
#endif /* VREFBUF */

/** @defgroup SYSCFG_flags_definition Flags
  * @{
  */

#define SYSCFG_FLAG_SRAM_PE             SYSCFG_CFGR2_SPF       /*!< SRAM parity error (first 32kB of SRAM1 + CCM SRAM) */
#define SYSCFG_FLAG_CCMSRAM_BUSY        SYSCFG_SCSR_CCMBSY     /*!< CCMSRAM busy by erase operation */

/**
  * @}
  */

/** @defgroup SYSCFG_FastModePlus_GPIO Fast-mode Plus on GPIO
  * @{
  */

/** @brief  Fast-mode Plus driving capability on a specific GPIO
  */
#define SYSCFG_FASTMODEPLUS_PB6        SYSCFG_CFGR1_I2C_PB6_FMP  /*!< Enable Fast-mode Plus on PB6 */
#define SYSCFG_FASTMODEPLUS_PB7        SYSCFG_CFGR1_I2C_PB7_FMP  /*!< Enable Fast-mode Plus on PB7 */
#if defined(SYSCFG_CFGR1_I2C_PB8_FMP)
#define SYSCFG_FASTMODEPLUS_PB8        SYSCFG_CFGR1_I2C_PB8_FMP  /*!< Enable Fast-mode Plus on PB8 */
#endif /* SYSCFG_CFGR1_I2C_PB8_FMP */
#if defined(SYSCFG_CFGR1_I2C_PB9_FMP)
#define SYSCFG_FASTMODEPLUS_PB9        SYSCFG_CFGR1_I2C_PB9_FMP  /*!< Enable Fast-mode Plus on PB9 */
#endif /* SYSCFG_CFGR1_I2C_PB9_FMP */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup DBGMCU_Exported_Macros DBGMCU Exported Macros
  * @{
  */

/** @brief  Freeze/Unfreeze Peripherals in Debug mode
  */
#if defined(DBGMCU_APB1FZR1_DBG_TIM2_STOP)
#define __HAL_DBGMCU_FREEZE_TIM2()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM2_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM2()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM2_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_TIM2_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_TIM3_STOP)
#define __HAL_DBGMCU_FREEZE_TIM3()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM3_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM3()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM3_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_TIM3_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_TIM4_STOP)
#define __HAL_DBGMCU_FREEZE_TIM4()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM4_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM4()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM4_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_TIM4_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_TIM5_STOP)
#define __HAL_DBGMCU_FREEZE_TIM5()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM5_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM5()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM5_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_TIM5_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_TIM6_STOP)
#define __HAL_DBGMCU_FREEZE_TIM6()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM6_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM6()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM6_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_TIM6_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_TIM7_STOP)
#define __HAL_DBGMCU_FREEZE_TIM7()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM7_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM7()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_TIM7_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_TIM7_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_RTC_STOP)
#define __HAL_DBGMCU_FREEZE_RTC()            SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_RTC_STOP)
#define __HAL_DBGMCU_UNFREEZE_RTC()          CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_RTC_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_RTC_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_WWDG_STOP)
#define __HAL_DBGMCU_FREEZE_WWDG()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_WWDG_STOP)
#define __HAL_DBGMCU_UNFREEZE_WWDG()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_WWDG_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_WWDG_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_IWDG_STOP)
#define __HAL_DBGMCU_FREEZE_IWDG()           SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_IWDG_STOP)
#define __HAL_DBGMCU_UNFREEZE_IWDG()         CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_IWDG_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_IWDG_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_I2C1_STOP)
#define __HAL_DBGMCU_FREEZE_I2C1_TIMEOUT()   SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_I2C1_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C1_TIMEOUT() CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_I2C1_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_I2C1_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_I2C2_STOP)
#define __HAL_DBGMCU_FREEZE_I2C2_TIMEOUT()   SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_I2C2_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C2_TIMEOUT() CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_I2C2_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_I2C2_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_I2C3_STOP)
#define __HAL_DBGMCU_FREEZE_I2C3_TIMEOUT()   SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_I2C3_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C3_TIMEOUT() CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_I2C3_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_I2C3_STOP */

#if defined(DBGMCU_APB1FZR1_DBG_LPTIM1_STOP)
#define __HAL_DBGMCU_FREEZE_LPTIM1()         SET_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_LPTIM1_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPTIM1()       CLEAR_BIT(DBGMCU->APB1FZR1, DBGMCU_APB1FZR1_DBG_LPTIM1_STOP)
#endif /* DBGMCU_APB1FZR1_DBG_LPTIM1_STOP */

#if defined(DBGMCU_APB1FZR2_DBG_I2C4_STOP)
#define __HAL_DBGMCU_FREEZE_I2C4_TIMEOUT()   SET_BIT(DBGMCU->APB1FZR2, DBGMCU_APB1FZR2_DBG_I2C4_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C4_TIMEOUT() CLEAR_BIT(DBGMCU->APB1FZR2, DBGMCU_APB1FZR2_DBG_I2C4_STOP)
#endif /* DBGMCU_APB1FZR2_DBG_I2C4_STOP */

#if defined(DBGMCU_APB2FZ_DBG_TIM1_STOP)
#define __HAL_DBGMCU_FREEZE_TIM1()           SET_BIT(DBGMCU->APB2FZ, DBGMCU_APB2FZ_DBG_TIM1_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM1()         CLEAR_BIT(DBGMCU->APB2FZ, DBGMCU_APB2FZ_DBG_TIM1_STOP)
#endif /* DBGMCU_APB2FZ_DBG_TIM1_STOP */

#if defined(DBGMCU_APB2FZ_DBG_TIM8_STOP)
#define __HAL_DBGMCU_FREEZE_TIM8()           SET_BIT(DBGMCU->APB2FZ, DBGMCU_APB2FZ_DBG_TIM8_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM8()         CLEAR_BIT(DBGMCU->APB2FZ, DBGMCU_APB2FZ_DBG_TIM8_STOP)
#endif /* DBGMCU_APB2FZ_DBG_TIM8_STOP */

#if defined(DBGMCU_APB2FZ_DBG_TIM15_STOP)
#define __HAL_DBGMCU_FREEZE_TIM15()          SET_BIT(DBGMCU->APB2FZ, DBGMCU_APB2FZ_DBG_TIM15_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM15()        CLEAR_BIT(DBGMCU->APB2FZ, DBGMCU_APB2FZ_DBG_TIM15_STOP)
#endif /* DBGMCU_APB2FZ_DBG_TIM15_STOP */

#if defined(DBGMCU_APB2FZ_DBG_TIM16_STOP)
#define __HAL_DBGMCU_FREEZE_TIM16()          SET_BIT(DBGMCU->APB2FZ, DBGMCU_APB2FZ_DBG_TIM16_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM16()        CLEAR_BIT(DBGMCU->APB2FZ, DBGMCU_APB2FZ_DBG_TIM16_STOP)
#endif /* DBGMCU_APB2FZ_DBG_TIM16_STOP */

#if defined(DBGMCU_APB2FZ_DBG_TIM17_STOP)
#define __HAL_DBGMCU_FREEZE_TIM17()          SET_BIT(DBGMCU->APB2FZ, DBGMCU_APB2FZ_DBG_TIM17_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM17()        CLEAR_BIT(DBGMCU->APB2FZ, DBGMCU_APB2FZ_DBG_TIM17_STOP)
#endif /* DBGMCU_APB2FZ_DBG_TIM17_STOP */

#if defined(DBGMCU_APB2FZ_DBG_TIM20_STOP)
#define __HAL_DBGMCU_FREEZE_TIM20()          SET_BIT(DBGMCU->APB2FZ, DBGMCU_APB2FZ_DBG_TIM20_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM20()        CLEAR_BIT(DBGMCU->APB2FZ, DBGMCU_APB2FZ_DBG_TIM20_STOP)
#endif /* DBGMCU_APB2FZ_DBG_TIM20_STOP */

#if defined(DBGMCU_APB2FZ_DBG_HRTIM1_STOP)
#define __HAL_DBGMCU_FREEZE_HRTIM1()         SET_BIT(DBGMCU->APB2FZ, DBGMCU_APB2FZ_DBG_HRTIM1_STOP)
#define __HAL_DBGMCU_UNFREEZE_HRTIM1()       CLEAR_BIT(DBGMCU->APB2FZ, DBGMCU_APB2FZ_DBG_HRTIM1_STOP)
#endif /* DBGMCU_APB2FZ_DBG_HRTIM1_STOP */

/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Macros SYSCFG Exported Macros
  * @{
  */

/** @brief  Main Flash memory mapped at 0x00000000.
  */
#define __HAL_SYSCFG_REMAPMEMORY_FLASH()       CLEAR_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_MEM_MODE)

/** @brief  System Flash memory mapped at 0x00000000.
  */
#define __HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH() MODIFY_REG(SYSCFG->MEMRMP, SYSCFG_MEMRMP_MEM_MODE, SYSCFG_MEMRMP_MEM_MODE_0)

/** @brief  Embedded SRAM mapped at 0x00000000.
  */
#define __HAL_SYSCFG_REMAPMEMORY_SRAM()        MODIFY_REG(SYSCFG->MEMRMP, SYSCFG_MEMRMP_MEM_MODE, (SYSCFG_MEMRMP_MEM_MODE_1|SYSCFG_MEMRMP_MEM_MODE_0))

#if defined (FMC_BANK1)
/** @brief  FMC Bank1 (NOR/PSRAM 1 and 2) mapped at 0x00000000.
  */
#define __HAL_SYSCFG_REMAPMEMORY_FMC()         MODIFY_REG(SYSCFG->MEMRMP, SYSCFG_MEMRMP_MEM_MODE, SYSCFG_MEMRMP_MEM_MODE_1)
#endif /* FMC_BANK1 */

#if defined (QUADSPI)
/** @brief  QUADSPI mapped at 0x00000000.
  */
#define __HAL_SYSCFG_REMAPMEMORY_QUADSPI()     MODIFY_REG(SYSCFG->MEMRMP, SYSCFG_MEMRMP_MEM_MODE, (SYSCFG_MEMRMP_MEM_MODE_2|SYSCFG_MEMRMP_MEM_MODE_1))
#endif /* QUADSPI */

/**
  * @brief  Return the boot mode as configured by user.
  * @retval The boot mode as configured by user. The returned value can be one
  *         of the following values:
  *           @arg @ref SYSCFG_BOOT_MAINFLASH
  *           @arg @ref SYSCFG_BOOT_SYSTEMFLASH
  *           @arg @ref SYSCFG_BOOT_FMC (*)
  *           @arg @ref SYSCFG_BOOT_QUADSPI (*)
  *           @arg @ref SYSCFG_BOOT_SRAM
  * @note   (*) availability depends on devices
  */
#define __HAL_SYSCFG_GET_BOOT_MODE()           READ_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_MEM_MODE)

/** @brief  CCMSRAM page write protection enable macro
  * @param __CCMSRAMWRP__: This parameter can be a value of @ref SYSCFG_CCMSRAMWRP
  * @note   write protection can only be disabled by a system reset
  * @retval None
  */
/* Legacy define */
#define __HAL_SYSCFG_CCMSRAM_WRP_1_31_ENABLE   __HAL_SYSCFG_CCMSRAM_WRP_0_31_ENABLE
#define __HAL_SYSCFG_CCMSRAM_WRP_0_31_ENABLE(__CCMSRAMWRP__)    do {assert_param(IS_SYSCFG_CCMSRAMWRP_PAGE((__CCMSRAMWRP__)));\
                                                                     SET_BIT(SYSCFG->SWPR,(__CCMSRAMWRP__));\
                                                                   }while(0)

/** @brief  CCMSRAM page write protection unlock prior to erase
  * @note   Writing a wrong key reactivates the write protection
  */
#define __HAL_SYSCFG_CCMSRAM_WRP_UNLOCK()    do {SYSCFG->SKR = 0xCA;\
                                                  SYSCFG->SKR = 0x53;\
                                                }while(0)

/** @brief  CCMSRAM erase
  * @note   __SYSCFG_GET_FLAG(SYSCFG_FLAG_CCMSRAM_BUSY) may be used to check end of erase
  */
#define __HAL_SYSCFG_CCMSRAM_ERASE()         SET_BIT(SYSCFG->SCSR, SYSCFG_SCSR_CCMER)

/** @brief  Floating Point Unit interrupt enable/disable macros
  * @param __INTERRUPT__: This parameter can be a value of @ref SYSCFG_FPU_Interrupts
  */
#define __HAL_SYSCFG_FPU_INTERRUPT_ENABLE(__INTERRUPT__)    do {assert_param(IS_SYSCFG_FPU_INTERRUPT((__INTERRUPT__)));\
                                                                 SET_BIT(SYSCFG->CFGR1, (__INTERRUPT__));\
                                                               }while(0)

#define __HAL_SYSCFG_FPU_INTERRUPT_DISABLE(__INTERRUPT__)   do {assert_param(IS_SYSCFG_FPU_INTERRUPT((__INTERRUPT__)));\
                                                                 CLEAR_BIT(SYSCFG->CFGR1, (__INTERRUPT__));\
                                                               }while(0)

/** @brief  SYSCFG Break ECC lock.
  *         Enable and lock the connection of Flash ECC error connection to TIM1/8/15/16/17 Break input.
  * @note   The selected configuration is locked and can be unlocked only by system reset.
  */
#define __HAL_SYSCFG_BREAK_ECC_LOCK()        SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_ECCL)

/** @brief  SYSCFG Break Cortex-M4 Lockup lock.
  *         Enable and lock the connection of Cortex-M4 LOCKUP (Hardfault) output to TIM1/8/15/16/17 Break input.
  * @note   The selected configuration is locked and can be unlocked only by system reset.
  */
#define __HAL_SYSCFG_BREAK_LOCKUP_LOCK()     SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_CLL)

/** @brief  SYSCFG Break PVD lock.
  *         Enable and lock the PVD connection to Timer1/8/15/16/17 Break input, as well as the PVDE and PLS[2:0] in the PWR_CR2 register.
  * @note   The selected configuration is locked and can be unlocked only by system reset.
  */
#define __HAL_SYSCFG_BREAK_PVD_LOCK()        SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_PVDL)

/** @brief  SYSCFG Break SRAM parity lock.
  *         Enable and lock the SRAM parity error (first 32kB of SRAM1 + CCM SRAM) signal connection to TIM1/8/15/16/17 Break input.
  * @note   The selected configuration is locked and can be unlocked by system reset.
  */
#define __HAL_SYSCFG_BREAK_SRAMPARITY_LOCK() SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_SPL)

/** @brief  Check SYSCFG flag is set or not.
  * @param  __FLAG__: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg @ref SYSCFG_FLAG_SRAM_PE   SRAM Parity Error Flag
  *            @arg @ref SYSCFG_FLAG_CCMSRAM_BUSY CCMSRAM Erase Ongoing
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_SYSCFG_GET_FLAG(__FLAG__)      ((((((__FLAG__) == SYSCFG_SCSR_CCMBSY)? SYSCFG->SCSR : SYSCFG->CFGR2)\
                                                & (__FLAG__))!= 0U) ? 1U : 0U)

/** @brief  Set the SPF bit to clear the SRAM Parity Error Flag.
  */
#define __HAL_SYSCFG_CLEAR_FLAG()            SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_SPF)

/** @brief  Fast-mode Plus driving capability enable/disable macros
  * @param __FASTMODEPLUS__: This parameter can be a value of :
  *     @arg @ref SYSCFG_FASTMODEPLUS_PB6 Fast-mode Plus driving capability activation on PB6
  *     @arg @ref SYSCFG_FASTMODEPLUS_PB7 Fast-mode Plus driving capability activation on PB7
  *     @arg @ref SYSCFG_FASTMODEPLUS_PB8 Fast-mode Plus driving capability activation on PB8
  *     @arg @ref SYSCFG_FASTMODEPLUS_PB9 Fast-mode Plus driving capability activation on PB9
  */
#define __HAL_SYSCFG_FASTMODEPLUS_ENABLE(__FASTMODEPLUS__)  do {assert_param(IS_SYSCFG_FASTMODEPLUS((__FASTMODEPLUS__)));\
                                                                 SET_BIT(SYSCFG->CFGR1, (__FASTMODEPLUS__));\
                                                               }while(0)

#define __HAL_SYSCFG_FASTMODEPLUS_DISABLE(__FASTMODEPLUS__) do {assert_param(IS_SYSCFG_FASTMODEPLUS((__FASTMODEPLUS__)));\
                                                                 CLEAR_BIT(SYSCFG->CFGR1, (__FASTMODEPLUS__));\
                                                               }while(0)

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup SYSCFG_Private_Macros SYSCFG Private Macros
  * @{
  */

#define IS_SYSCFG_FPU_INTERRUPT(__INTERRUPT__) ((((__INTERRUPT__) & SYSCFG_IT_FPU_IOC) == SYSCFG_IT_FPU_IOC) || \
                                                (((__INTERRUPT__) & SYSCFG_IT_FPU_DZC) == SYSCFG_IT_FPU_DZC) || \
                                                (((__INTERRUPT__) & SYSCFG_IT_FPU_UFC) == SYSCFG_IT_FPU_UFC) || \
                                                (((__INTERRUPT__) & SYSCFG_IT_FPU_OFC) == SYSCFG_IT_FPU_OFC) || \
                                                (((__INTERRUPT__) & SYSCFG_IT_FPU_IDC) == SYSCFG_IT_FPU_IDC) || \
                                                (((__INTERRUPT__) & SYSCFG_IT_FPU_IXC) == SYSCFG_IT_FPU_IXC))

#define IS_SYSCFG_BREAK_CONFIG(__CONFIG__) (((__CONFIG__) == SYSCFG_BREAK_ECC)           || \
                                            ((__CONFIG__) == SYSCFG_BREAK_PVD)           || \
                                            ((__CONFIG__) == SYSCFG_BREAK_SRAMPARITY)    || \
                                            ((__CONFIG__) == SYSCFG_BREAK_LOCKUP))

#if (CCMSRAM_SIZE == 0x00008000UL) || (CCMSRAM_SIZE == 0x00004000UL)
#define IS_SYSCFG_CCMSRAMWRP_PAGE(__PAGE__)  ((__PAGE__) > 0U)
#elif (CCMSRAM_SIZE == 0x00002800UL)
#define IS_SYSCFG_CCMSRAMWRP_PAGE(__PAGE__)  (((__PAGE__) > 0U) && ((__PAGE__) <= 0x000003FFU))
#endif /* CCMSRAM_SIZE */

#if defined(VREFBUF)
#define IS_SYSCFG_VREFBUF_VOLTAGE_SCALE(__SCALE__)  (((__SCALE__) == SYSCFG_VREFBUF_VOLTAGE_SCALE0) || \
                                                     ((__SCALE__) == SYSCFG_VREFBUF_VOLTAGE_SCALE1) || \
                                                     ((__SCALE__) == SYSCFG_VREFBUF_VOLTAGE_SCALE2))

#define IS_SYSCFG_VREFBUF_HIGH_IMPEDANCE(__VALUE__)  (((__VALUE__) == SYSCFG_VREFBUF_HIGH_IMPEDANCE_DISABLE) || \
                                                      ((__VALUE__) == SYSCFG_VREFBUF_HIGH_IMPEDANCE_ENABLE))

#define IS_SYSCFG_VREFBUF_TRIMMING(__VALUE__)  (((__VALUE__) > 0U) && ((__VALUE__) <= VREFBUF_CCR_TRIM))
#endif /* VREFBUF */

#if defined(SYSCFG_FASTMODEPLUS_PB8) && defined(SYSCFG_FASTMODEPLUS_PB9)
#define IS_SYSCFG_FASTMODEPLUS(__PIN__) ((((__PIN__) & SYSCFG_FASTMODEPLUS_PB6) == SYSCFG_FASTMODEPLUS_PB6) || \
                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB7) == SYSCFG_FASTMODEPLUS_PB7) || \
                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB8) == SYSCFG_FASTMODEPLUS_PB8) || \
                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB9) == SYSCFG_FASTMODEPLUS_PB9))
#elif defined(SYSCFG_FASTMODEPLUS_PB8)
#define IS_SYSCFG_FASTMODEPLUS(__PIN__) ((((__PIN__) & SYSCFG_FASTMODEPLUS_PB6) == SYSCFG_FASTMODEPLUS_PB6) || \
                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB7) == SYSCFG_FASTMODEPLUS_PB7) || \
                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB8) == SYSCFG_FASTMODEPLUS_PB8))
#elif defined(SYSCFG_FASTMODEPLUS_PB9)
#define IS_SYSCFG_FASTMODEPLUS(__PIN__) ((((__PIN__) & SYSCFG_FASTMODEPLUS_PB6) == SYSCFG_FASTMODEPLUS_PB6) || \
                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB7) == SYSCFG_FASTMODEPLUS_PB7) || \
                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB9) == SYSCFG_FASTMODEPLUS_PB9))
#else
#define IS_SYSCFG_FASTMODEPLUS(__PIN__) ((((__PIN__) & SYSCFG_FASTMODEPLUS_PB6) == SYSCFG_FASTMODEPLUS_PB6) || \
                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB7) == SYSCFG_FASTMODEPLUS_PB7))
#endif /* SYSCFG_FASTMODEPLUS_PB */
/**
  * @}
  */

/** @defgroup HAL_Private_Macros HAL Private Macros
  * @{
  */
#define IS_TICKFREQ(FREQ) (((FREQ) == HAL_TICK_FREQ_10HZ)  || \
                           ((FREQ) == HAL_TICK_FREQ_100HZ) || \
                           ((FREQ) == HAL_TICK_FREQ_1KHZ))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup HAL_Exported_Functions
  * @{
  */

/** @addtogroup HAL_Exported_Functions_Group1
  * @{
  */
/* Initialization and Configuration functions  ******************************/
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group2 HAL Control functions
  * @{
  */

/* Peripheral Control functions  ************************************************/
void HAL_IncTick(void);
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
uint32_t HAL_GetTickPrio(void);
HAL_StatusTypeDef HAL_SetTickFreq(uint32_t Freq);
uint32_t HAL_GetTickFreq(void);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
uint32_t HAL_GetHalVersion(void);
uint32_t HAL_GetREVID(void);
uint32_t HAL_GetDEVID(void);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group3
  * @{
  */

/* DBGMCU Peripheral Control functions  *****************************************/
void HAL_DBGMCU_EnableDBGSleepMode(void);
void HAL_DBGMCU_DisableDBGSleepMode(void);
void HAL_DBGMCU_EnableDBGStopMode(void);
void HAL_DBGMCU_DisableDBGStopMode(void);
void HAL_DBGMCU_EnableDBGStandbyMode(void);
void HAL_DBGMCU_DisableDBGStandbyMode(void);

/**
  * @}
  */

/* Exported variables ---------------------------------------------------------*/
/** @addtogroup HAL_Exported_Variables
  * @{
  */
extern __IO uint32_t uwTick;
extern uint32_t uwTickPrio;
extern uint32_t uwTickFreq;
/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group4
  * @{
  */

/* SYSCFG Control functions  ****************************************************/
void HAL_SYSCFG_CCMSRAMErase(void);
void HAL_SYSCFG_EnableMemorySwappingBank(void);
void HAL_SYSCFG_DisableMemorySwappingBank(void);

#if defined(VREFBUF)
void HAL_SYSCFG_VREFBUF_VoltageScalingConfig(uint32_t VoltageScaling);
void HAL_SYSCFG_VREFBUF_HighImpedanceConfig(uint32_t Mode);
void HAL_SYSCFG_VREFBUF_TrimmingConfig(uint32_t TrimmingValue);
HAL_StatusTypeDef HAL_SYSCFG_EnableVREFBUF(void);
void HAL_SYSCFG_DisableVREFBUF(void);
#endif /* VREFBUF */

void HAL_SYSCFG_EnableIOSwitchBooster(void);
void HAL_SYSCFG_DisableIOSwitchBooster(void);
void HAL_SYSCFG_EnableIOSwitchVDD(void);
void HAL_SYSCFG_DisableIOSwitchVDD(void);

void HAL_SYSCFG_CCMSRAM_WriteProtectionEnable(uint32_t Page);

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

#endif /* STM32G4xx_HAL_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
