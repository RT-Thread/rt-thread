/**
  ******************************************************************************
  * @file    stm32l5xx_ll_system.h
  * @author  MCD Application Team
  * @brief   Header file of SYSTEM LL module.
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
    The LL SYSTEM driver contains a set of generic APIs that can be
    used by user:
      (+) Some of the FLASH features need to be handled in the SYSTEM file.
      (+) Access to DBGCMU registers
      (+) Access to SYSCFG registers
      (+) Access to VREFBUF registers

  @endverbatim
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
#ifndef STM32L5xx_LL_SYSTEM_H
#define STM32L5xx_LL_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l5xx.h"

/** @addtogroup STM32L5xx_LL_Driver
  * @{
  */

#if defined (FLASH) || defined (SYSCFG) || defined (DBGMCU) || defined (VREFBUF)

/** @defgroup SYSTEM_LL SYSTEM
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Private_Constants SYSTEM Private Constants
  * @{
  */
/**
  * @brief VREFBUF VREF_SC0 & VREF_SC1 calibration values
  */
#define VREFBUF_SC0_CAL_ADDR   ((uint8_t*) (0x0BFA0579UL)) /*!<  Address of VREFBUF trimming value for VRS=0,
                                                                 VREF_SC0 in STM32L5 datasheet */
#define VREFBUF_SC1_CAL_ADDR   ((uint8_t*) (0x0BFA0530UL)) /*!<  Address of VREFBUF trimming value for VRS=1,
                                                                 VREF_SC1 in STM32L5 datasheet */

/**
  * @brief Power-down in Run mode Flash key
  */
#define FLASH_PDKEY1                  0x04152637U /*!< Flash power down key1 */
#define FLASH_PDKEY2                  0xFAFBFCFDU /*!< Flash power down key2: used with FLASH_PDKEY1
                                                       to unlock the RUN_PD bit in FLASH_ACR */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Constants SYSTEM Exported Constants
  * @{
  */

/** @defgroup SYSTEM_LL_EC_I2C_FASTMODEPLUS SYSCFG I2C FASTMODEPLUS
  * @{
  */
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB6     SYSCFG_CFGR1_I2C_PB6_FMP  /*!< Enable Fast Mode Plus on PB6       */
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB7     SYSCFG_CFGR1_I2C_PB7_FMP  /*!< Enable Fast Mode Plus on PB7       */
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB8     SYSCFG_CFGR1_I2C_PB8_FMP  /*!< Enable Fast Mode Plus on PB8       */
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB9     SYSCFG_CFGR1_I2C_PB9_FMP  /*!< Enable Fast Mode Plus on PB9       */
#define LL_SYSCFG_I2C_FASTMODEPLUS_I2C1    SYSCFG_CFGR1_I2C1_FMP     /*!< Enable Fast Mode Plus on I2C1 pins */
#define LL_SYSCFG_I2C_FASTMODEPLUS_I2C2    SYSCFG_CFGR1_I2C2_FMP     /*!< Enable Fast Mode Plus on I2C2 pins */
#define LL_SYSCFG_I2C_FASTMODEPLUS_I2C3    SYSCFG_CFGR1_I2C3_FMP     /*!< Enable Fast Mode Plus on I2C3 pins */
#define LL_SYSCFG_I2C_FASTMODEPLUS_I2C4    SYSCFG_CFGR1_I2C4_FMP     /*!< Enable Fast Mode Plus on I2C4 pins */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_TIMBREAK SYSCFG TIMER BREAK
  * @{
  */
#define LL_SYSCFG_TIMBREAK_ECC             SYSCFG_CFGR2_ECCL  /*!< Enables and locks the ECC error signal
                                                                   with Break Input of TIM1/8/15/16/17                           */
#define LL_SYSCFG_TIMBREAK_PVD             SYSCFG_CFGR2_PVDL  /*!< Enables and locks the PVD connection
                                                                   with TIM1/8/15/16/17 Break Input
                                                                   and also the PVDE and PLS bits of the Power Control Interface */
#define LL_SYSCFG_TIMBREAK_SRAM2_PARITY    SYSCFG_CFGR2_SPL   /*!< Enables and locks the SRAM2_PARITY error signal
                                                                   with Break Input of TIM1/8/15/16/17                           */
#define LL_SYSCFG_TIMBREAK_LOCKUP          SYSCFG_CFGR2_CLL   /*!< Enables and locks the LOCKUP output of CortexM4
                                                                   with Break Input of TIM1/15/16/17                             */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_SRAM2WRP SYSCFG SRAM2 WRP
  * @{
  */
#define LL_SYSCFG_SRAM2WRP_PAGE0           SYSCFG_SWPR_P0WP  /*!< SRAM2 Write protection page 0  */
#define LL_SYSCFG_SRAM2WRP_PAGE1           SYSCFG_SWPR_P1WP  /*!< SRAM2 Write protection page 1  */
#define LL_SYSCFG_SRAM2WRP_PAGE2           SYSCFG_SWPR_P2WP  /*!< SRAM2 Write protection page 2  */
#define LL_SYSCFG_SRAM2WRP_PAGE3           SYSCFG_SWPR_P3WP  /*!< SRAM2 Write protection page 3  */
#define LL_SYSCFG_SRAM2WRP_PAGE4           SYSCFG_SWPR_P4WP  /*!< SRAM2 Write protection page 4  */
#define LL_SYSCFG_SRAM2WRP_PAGE5           SYSCFG_SWPR_P5WP  /*!< SRAM2 Write protection page 5  */
#define LL_SYSCFG_SRAM2WRP_PAGE6           SYSCFG_SWPR_P6WP  /*!< SRAM2 Write protection page 6  */
#define LL_SYSCFG_SRAM2WRP_PAGE7           SYSCFG_SWPR_P7WP  /*!< SRAM2 Write protection page 7  */
#define LL_SYSCFG_SRAM2WRP_PAGE8           SYSCFG_SWPR_P8WP  /*!< SRAM2 Write protection page 8  */
#define LL_SYSCFG_SRAM2WRP_PAGE9           SYSCFG_SWPR_P9WP  /*!< SRAM2 Write protection page 9  */
#define LL_SYSCFG_SRAM2WRP_PAGE10          SYSCFG_SWPR_P10WP /*!< SRAM2 Write protection page 10 */
#define LL_SYSCFG_SRAM2WRP_PAGE11          SYSCFG_SWPR_P11WP /*!< SRAM2 Write protection page 11 */
#define LL_SYSCFG_SRAM2WRP_PAGE12          SYSCFG_SWPR_P12WP /*!< SRAM2 Write protection page 12 */
#define LL_SYSCFG_SRAM2WRP_PAGE13          SYSCFG_SWPR_P13WP /*!< SRAM2 Write protection page 13 */
#define LL_SYSCFG_SRAM2WRP_PAGE14          SYSCFG_SWPR_P14WP /*!< SRAM2 Write protection page 14 */
#define LL_SYSCFG_SRAM2WRP_PAGE15          SYSCFG_SWPR_P15WP /*!< SRAM2 Write protection page 15 */
#define LL_SYSCFG_SRAM2WRP_PAGE16          SYSCFG_SWPR_P16WP /*!< SRAM2 Write protection page 16 */
#define LL_SYSCFG_SRAM2WRP_PAGE17          SYSCFG_SWPR_P17WP /*!< SRAM2 Write protection page 17 */
#define LL_SYSCFG_SRAM2WRP_PAGE18          SYSCFG_SWPR_P18WP /*!< SRAM2 Write protection page 18 */
#define LL_SYSCFG_SRAM2WRP_PAGE19          SYSCFG_SWPR_P19WP /*!< SRAM2 Write protection page 19 */
#define LL_SYSCFG_SRAM2WRP_PAGE20          SYSCFG_SWPR_P20WP /*!< SRAM2 Write protection page 20 */
#define LL_SYSCFG_SRAM2WRP_PAGE21          SYSCFG_SWPR_P21WP /*!< SRAM2 Write protection page 21 */
#define LL_SYSCFG_SRAM2WRP_PAGE22          SYSCFG_SWPR_P22WP /*!< SRAM2 Write protection page 22 */
#define LL_SYSCFG_SRAM2WRP_PAGE23          SYSCFG_SWPR_P23WP /*!< SRAM2 Write protection page 23 */
#define LL_SYSCFG_SRAM2WRP_PAGE24          SYSCFG_SWPR_P24WP /*!< SRAM2 Write protection page 24 */
#define LL_SYSCFG_SRAM2WRP_PAGE25          SYSCFG_SWPR_P25WP /*!< SRAM2 Write protection page 25 */
#define LL_SYSCFG_SRAM2WRP_PAGE26          SYSCFG_SWPR_P26WP /*!< SRAM2 Write protection page 26 */
#define LL_SYSCFG_SRAM2WRP_PAGE27          SYSCFG_SWPR_P27WP /*!< SRAM2 Write protection page 27 */
#define LL_SYSCFG_SRAM2WRP_PAGE28          SYSCFG_SWPR_P28WP /*!< SRAM2 Write protection page 28 */
#define LL_SYSCFG_SRAM2WRP_PAGE29          SYSCFG_SWPR_P29WP /*!< SRAM2 Write protection page 29 */
#define LL_SYSCFG_SRAM2WRP_PAGE30          SYSCFG_SWPR_P30WP /*!< SRAM2 Write protection page 30 */
#define LL_SYSCFG_SRAM2WRP_PAGE31          SYSCFG_SWPR_P31WP /*!< SRAM2 Write protection page 31 */
#define LL_SYSCFG_SRAM2WRP_PAGE32          SYSCFG_SWPR2_P32WP /*!< SRAM2 Write protection page 32 */
#define LL_SYSCFG_SRAM2WRP_PAGE33          SYSCFG_SWPR2_P33WP /*!< SRAM2 Write protection page 33 */
#define LL_SYSCFG_SRAM2WRP_PAGE34          SYSCFG_SWPR2_P34WP /*!< SRAM2 Write protection page 34 */
#define LL_SYSCFG_SRAM2WRP_PAGE35          SYSCFG_SWPR2_P35WP /*!< SRAM2 Write protection page 35 */
#define LL_SYSCFG_SRAM2WRP_PAGE36          SYSCFG_SWPR2_P36WP /*!< SRAM2 Write protection page 36 */
#define LL_SYSCFG_SRAM2WRP_PAGE37          SYSCFG_SWPR2_P37WP /*!< SRAM2 Write protection page 37 */
#define LL_SYSCFG_SRAM2WRP_PAGE38          SYSCFG_SWPR2_P38WP /*!< SRAM2 Write protection page 38 */
#define LL_SYSCFG_SRAM2WRP_PAGE39          SYSCFG_SWPR2_P39WP /*!< SRAM2 Write protection page 39 */
#define LL_SYSCFG_SRAM2WRP_PAGE40          SYSCFG_SWPR2_P40WP /*!< SRAM2 Write protection page 40 */
#define LL_SYSCFG_SRAM2WRP_PAGE41          SYSCFG_SWPR2_P41WP /*!< SRAM2 Write protection page 41 */
#define LL_SYSCFG_SRAM2WRP_PAGE42          SYSCFG_SWPR2_P42WP /*!< SRAM2 Write protection page 42 */
#define LL_SYSCFG_SRAM2WRP_PAGE43          SYSCFG_SWPR2_P43WP /*!< SRAM2 Write protection page 43 */
#define LL_SYSCFG_SRAM2WRP_PAGE44          SYSCFG_SWPR2_P44WP /*!< SRAM2 Write protection page 44 */
#define LL_SYSCFG_SRAM2WRP_PAGE45          SYSCFG_SWPR2_P45WP /*!< SRAM2 Write protection page 45 */
#define LL_SYSCFG_SRAM2WRP_PAGE46          SYSCFG_SWPR2_P46WP /*!< SRAM2 Write protection page 46 */
#define LL_SYSCFG_SRAM2WRP_PAGE47          SYSCFG_SWPR2_P47WP /*!< SRAM2 Write protection page 47 */
#define LL_SYSCFG_SRAM2WRP_PAGE48          SYSCFG_SWPR2_P48WP /*!< SRAM2 Write protection page 48 */
#define LL_SYSCFG_SRAM2WRP_PAGE49          SYSCFG_SWPR2_P49WP /*!< SRAM2 Write protection page 49 */
#define LL_SYSCFG_SRAM2WRP_PAGE50          SYSCFG_SWPR2_P50WP /*!< SRAM2 Write protection page 50 */
#define LL_SYSCFG_SRAM2WRP_PAGE51          SYSCFG_SWPR2_P51WP /*!< SRAM2 Write protection page 51 */
#define LL_SYSCFG_SRAM2WRP_PAGE52          SYSCFG_SWPR2_P52WP /*!< SRAM2 Write protection page 52 */
#define LL_SYSCFG_SRAM2WRP_PAGE53          SYSCFG_SWPR2_P53WP /*!< SRAM2 Write protection page 53 */
#define LL_SYSCFG_SRAM2WRP_PAGE54          SYSCFG_SWPR2_P54WP /*!< SRAM2 Write protection page 54 */
#define LL_SYSCFG_SRAM2WRP_PAGE55          SYSCFG_SWPR2_P55WP /*!< SRAM2 Write protection page 55 */
#define LL_SYSCFG_SRAM2WRP_PAGE56          SYSCFG_SWPR2_P56WP /*!< SRAM2 Write protection page 56 */
#define LL_SYSCFG_SRAM2WRP_PAGE57          SYSCFG_SWPR2_P57WP /*!< SRAM2 Write protection page 57 */
#define LL_SYSCFG_SRAM2WRP_PAGE58          SYSCFG_SWPR2_P58WP /*!< SRAM2 Write protection page 58 */
#define LL_SYSCFG_SRAM2WRP_PAGE59          SYSCFG_SWPR2_P59WP /*!< SRAM2 Write protection page 59 */
#define LL_SYSCFG_SRAM2WRP_PAGE60          SYSCFG_SWPR2_P60WP /*!< SRAM2 Write protection page 60 */
#define LL_SYSCFG_SRAM2WRP_PAGE61          SYSCFG_SWPR2_P61WP /*!< SRAM2 Write protection page 61 */
#define LL_SYSCFG_SRAM2WRP_PAGE62          SYSCFG_SWPR2_P62WP /*!< SRAM2 Write protection page 62 */
#define LL_SYSCFG_SRAM2WRP_PAGE63          SYSCFG_SWPR2_P63WP /*!< SRAM2 Write protection page 63 */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_SECURE_ATTRIBUTES Secure attributes
  * @note Only available when system implements security (TZEN=1)
  * @{
  */
#define LL_SYSCFG_CLOCK_SEC                SYSCFG_SECCFGR_SYSCFGSEC  /*!< SYSCFG clock configuration secure-only access */
#define LL_SYSCFG_CLOCK_NSEC               0U                        /*!< SYSCFG clock configuration secure/non-secure access */
#define LL_SYSCFG_CLASSB_SEC               SYSCFG_SECCFGR_CLASSBSEC  /*!< Class B configuration secure-only access */
#define LL_SYSCFG_CLASSB_NSEC              0U                        /*!< Class B configuration secure/non-secure access */
#define LL_SYSCFG_SRAM2_SEC                SYSCFG_SECCFGR_SRAM2SEC   /*!< SRAM2 configuration secure-only access */
#define LL_SYSCFG_SRAM2_NSEC               0U                        /*!< SRAM2 configuration secure/non-secure access */
#define LL_SYSCFG_FPU_SEC                  SYSCFG_SECCFGR_FPUSEC     /*!< FPU configuration secure-only access */
#define LL_SYSCFG_FPU_NSEC                 0U                        /*!< FPU configuration secure/non-secure access */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_TRACE DBGMCU TRACE Pin Assignment
  * @{
  */
#define LL_DBGMCU_TRACE_NONE               0x00000000U                                     /*!< TRACE pins not assigned (default state) */
#define LL_DBGMCU_TRACE_ASYNCH             DBGMCU_CR_TRACE_IOEN                            /*!< TRACE pin assignment for Asynchronous Mode */
#define LL_DBGMCU_TRACE_SYNCH_SIZE1        (DBGMCU_CR_TRACE_IOEN | DBGMCU_CR_TRACE_MODE_0) /*!< TRACE pin assignment for Synchronous Mode with a TRACEDATA size of 1 */
#define LL_DBGMCU_TRACE_SYNCH_SIZE2        (DBGMCU_CR_TRACE_IOEN | DBGMCU_CR_TRACE_MODE_1) /*!< TRACE pin assignment for Synchronous Mode with a TRACEDATA size of 2 */
#define LL_DBGMCU_TRACE_SYNCH_SIZE4        (DBGMCU_CR_TRACE_IOEN | DBGMCU_CR_TRACE_MODE)   /*!< TRACE pin assignment for Synchronous Mode with a TRACEDATA size of 4 */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB1_GRP1_STOP DBGMCU APB1 GRP1 STOP
  * @{
  */
#define LL_DBGMCU_APB1_GRP1_TIM2_STOP      DBGMCU_APB1FZR1_DBG_TIM2_STOP   /*!< The counter clock of TIM2 is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_TIM3_STOP      DBGMCU_APB1FZR1_DBG_TIM3_STOP   /*!< The counter clock of TIM3 is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_TIM4_STOP      DBGMCU_APB1FZR1_DBG_TIM4_STOP   /*!< The counter clock of TIM4 is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_TIM5_STOP      DBGMCU_APB1FZR1_DBG_TIM5_STOP   /*!< The counter clock of TIM5 is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_TIM6_STOP      DBGMCU_APB1FZR1_DBG_TIM6_STOP   /*!< The counter clock of TIM6 is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_TIM7_STOP      DBGMCU_APB1FZR1_DBG_TIM7_STOP   /*!< The counter clock of TIM7 is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_RTC_STOP       DBGMCU_APB1FZR1_DBG_RTC_STOP    /*!< The clock of the RTC counter is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_WWDG_STOP      DBGMCU_APB1FZR1_DBG_WWDG_STOP   /*!< The window watchdog counter clock is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_IWDG_STOP      DBGMCU_APB1FZR1_DBG_IWDG_STOP   /*!< The independent watchdog counter clock is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_I2C1_STOP      DBGMCU_APB1FZR1_DBG_I2C1_STOP   /*!< The I2C1 SMBus timeout is frozen*/
#define LL_DBGMCU_APB1_GRP1_I2C2_STOP      DBGMCU_APB1FZR1_DBG_I2C2_STOP   /*!< The I2C2 SMBus timeout is frozen*/
#define LL_DBGMCU_APB1_GRP1_I2C3_STOP      DBGMCU_APB1FZR1_DBG_I2C3_STOP   /*!< The I2C3 SMBus timeout is frozen*/
#define LL_DBGMCU_APB1_GRP1_FDCAN1_STOP    DBGMCU_APB1FZR1_DBG_FDCAN1_STOP /*!< The FDCAN1 receive registers are frozen*/
#define LL_DBGMCU_APB1_GRP1_LPTIM1_STOP    DBGMCU_APB1FZR1_DBG_LPTIM1_STOP /*!< The counter clock of LPTIM1 is stopped when the core is halted*/
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB1_GRP2_STOP DBGMCU APB1 GRP2 STOP
  * @{
  */
#define LL_DBGMCU_APB1_GRP2_I2C4_STOP      DBGMCU_APB1FZR2_DBG_I2C4_STOP   /*!< The I2C4 SMBus timeout is frozen*/
#define LL_DBGMCU_APB1_GRP2_LPTIM2_STOP    DBGMCU_APB1FZR2_DBG_LPTIM2_STOP /*!< The counter clock of LPTIM2 is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP2_LPTIM3_STOP    DBGMCU_APB1FZR2_DBG_LPTIM3_STOP /*!< The counter clock of LPTIM2 is stopped when the core is halted*/
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB2_GRP1_STOP DBGMCU APB2 GRP1 STOP
  * @{
  */
#define LL_DBGMCU_APB2_GRP1_TIM1_STOP      DBGMCU_APB2FZR_DBG_TIM1_STOP     /*!< The counter clock of TIM1 is stopped when the core is halted*/
#define LL_DBGMCU_APB2_GRP1_TIM8_STOP      DBGMCU_APB2FZR_DBG_TIM8_STOP     /*!< The counter clock of TIM8 is stopped when the core is halted*/
#define LL_DBGMCU_APB2_GRP1_TIM15_STOP     DBGMCU_APB2FZR_DBG_TIM15_STOP    /*!< The counter clock of TIM15 is stopped when the core is halted*/
#define LL_DBGMCU_APB2_GRP1_TIM16_STOP     DBGMCU_APB2FZR_DBG_TIM16_STOP    /*!< The counter clock of TIM16 is stopped when the core is halted*/
#define LL_DBGMCU_APB2_GRP1_TIM17_STOP     DBGMCU_APB2FZR_DBG_TIM17_STOP    /*!< The counter clock of TIM17 is stopped when the core is halted*/
/**
  * @}
  */

#if defined(VREFBUF)
/** @defgroup SYSTEM_LL_EC_VOLTAGE VREFBUF VOLTAGE
  * @{
  */
#define LL_VREFBUF_VOLTAGE_SCALE0          ((uint32_t)0x00000000) /*!< Voltage reference scale 0 (VREF_OUT1) */
#define LL_VREFBUF_VOLTAGE_SCALE1          VREFBUF_CSR_VRS        /*!< Voltage reference scale 1 (VREF_OUT2) */
/**
  * @}
  */
#endif /* VREFBUF */

/** @defgroup SYSTEM_LL_EC_LATENCY FLASH LATENCY
  * @{
  */
#define LL_FLASH_LATENCY_0                 FLASH_ACR_LATENCY_0WS   /*!< FLASH zero wait state */
#define LL_FLASH_LATENCY_1                 FLASH_ACR_LATENCY_1WS   /*!< FLASH one wait state */
#define LL_FLASH_LATENCY_2                 FLASH_ACR_LATENCY_2WS   /*!< FLASH two wait states */
#define LL_FLASH_LATENCY_3                 FLASH_ACR_LATENCY_3WS   /*!< FLASH three wait states */
#define LL_FLASH_LATENCY_4                 FLASH_ACR_LATENCY_4WS   /*!< FLASH four wait states */
#define LL_FLASH_LATENCY_5                 FLASH_ACR_LATENCY_5WS   /*!< FLASH five wait states */
#define LL_FLASH_LATENCY_6                 FLASH_ACR_LATENCY_6WS   /*!< FLASH six wait state */
#define LL_FLASH_LATENCY_7                 FLASH_ACR_LATENCY_7WS   /*!< FLASH Seven wait states */
#define LL_FLASH_LATENCY_8                 FLASH_ACR_LATENCY_8WS   /*!< FLASH Eight wait states */
#define LL_FLASH_LATENCY_9                 FLASH_ACR_LATENCY_9WS   /*!< FLASH nine wait states */
#define LL_FLASH_LATENCY_10                FLASH_ACR_LATENCY_10WS  /*!< FLASH ten wait states */
#define LL_FLASH_LATENCY_11                FLASH_ACR_LATENCY_11WS  /*!< FLASH eleven wait states */
#define LL_FLASH_LATENCY_12                FLASH_ACR_LATENCY_12WS  /*!< FLASH twelve wait states */
#define LL_FLASH_LATENCY_13                FLASH_ACR_LATENCY_13WS  /*!< FLASH thirteen wait states */
#define LL_FLASH_LATENCY_14                FLASH_ACR_LATENCY_14WS  /*!< FLASH fourteen wait states */
#define LL_FLASH_LATENCY_15                FLASH_ACR_LATENCY_15WS  /*!< FLASH fifteen wait states */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Functions SYSTEM Exported Functions
  * @{
  */

/** @defgroup SYSTEM_LL_EF_SYSCFG SYSCFG
  * @{
  */

/**
  * @brief  Enable I/O analog switches supplied by VDD.
  * @rmtoll SYSCFG_CFGR1 ANASWVDD      LL_SYSCFG_EnableAnalogSwitchVdd
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableAnalogSwitchVdd(void)
{
  SET_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_ANASWVDD);
}

/**
  * @brief  Disable I/O analog switches supplied by VDD.
  * @note   I/O analog switches are supplied by VDDA or booster
  *         when booster in on.
  *         Dedicated voltage booster (supplied by VDD) is the recommended
  *         configuration with low VDDA voltage operation.
  * @rmtoll SYSCFG_CFGR1 ANASWVDD      LL_SYSCFG_DisableAnalogSwitchVdd
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableAnalogSwitchVdd(void)
{
  CLEAR_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_ANASWVDD);
}

/**
  * @brief  Enable I/O analog switch voltage booster.
  * @note   When voltage booster is enabled, I/O analog switches are supplied
  *         by a dedicated voltage booster, from VDD power domain. This is
  *         the recommended configuration with low VDDA voltage operation.
  * @note   The I/O analog switch voltage booster is relevant for peripherals
  *         using I/O in analog input: ADC, COMP, OPAMP.
  *         However, COMP and OPAMP inputs have a high impedance and
  *         voltage booster do not impact performance significantly.
  *         Therefore, the voltage booster is mainly intended for
  *         usage with ADC.
  * @rmtoll SYSCFG_CFGR1 BOOSTEN       LL_SYSCFG_EnableAnalogBooster
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableAnalogBooster(void)
{
  SET_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_BOOSTEN);
}

/**
  * @brief  Disable I/O analog switch voltage booster.
  * @note   When voltage booster is enabled, I/O analog switches are supplied
  *         by a dedicated voltage booster, from VDD power domain. This is
  *         the recommended configuration with low VDDA voltage operation.
  * @note   The I/O analog switch voltage booster is relevant for peripherals
  *         using I/O in analog input: ADC, COMP, OPAMP.
  *         However, COMP and OPAMP inputs have a high impedance and
  *         voltage booster do not impact performance significantly.
  *         Therefore, the voltage booster is mainly intended for
  *         usage with ADC.
  * @rmtoll SYSCFG_CFGR1 BOOSTEN       LL_SYSCFG_DisableAnalogBooster
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableAnalogBooster(void)
{
  CLEAR_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_BOOSTEN);
}

/**
  * @brief  Enable the I2C fast mode plus driving capability.
  * @rmtoll SYSCFG_CFGR1 I2C_PBx_FMP   LL_SYSCFG_EnableFastModePlus\n
  *         SYSCFG_CFGR1 I2Cx_FMP      LL_SYSCFG_EnableFastModePlus
  * @param  ConfigFastModePlus This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB6
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB7
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB8
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB9
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C1
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C2
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C3
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C4
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableFastModePlus(uint32_t ConfigFastModePlus)
{
  SET_BIT(SYSCFG->CFGR1, ConfigFastModePlus);
}

/**
  * @brief  Disable the I2C fast mode plus driving capability.
  * @rmtoll SYSCFG_CFGR1 I2C_PBx_FMP   LL_SYSCFG_DisableFastModePlus\n
  *         SYSCFG_CFGR1 I2Cx_FMP      LL_SYSCFG_DisableFastModePlus
  * @param  ConfigFastModePlus This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB6
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB7
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB8
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB9
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C1
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C2
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C3
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C4
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableFastModePlus(uint32_t ConfigFastModePlus)
{
  CLEAR_BIT(SYSCFG->CFGR1, ConfigFastModePlus);
}

/**
  * @brief  Enable Floating Point Unit Invalid operation Interrupt
  * @rmtoll SYSCFG_FPUIMR FPU_IE_0      LL_SYSCFG_EnableIT_FPU_IOC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableIT_FPU_IOC(void)
{
  SET_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_0);
}

/**
  * @brief  Enable Floating Point Unit Divide-by-zero Interrupt
  * @rmtoll SYSCFG_FPUIMR FPU_IE_1      LL_SYSCFG_EnableIT_FPU_DZC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableIT_FPU_DZC(void)
{
  SET_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_1);
}

/**
  * @brief  Enable Floating Point Unit Underflow Interrupt
  * @rmtoll SYSCFG_FPUIMR FPU_IE_2      LL_SYSCFG_EnableIT_FPU_UFC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableIT_FPU_UFC(void)
{
  SET_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_2);
}

/**
  * @brief  Enable Floating Point Unit Overflow Interrupt
  * @rmtoll SYSCFG_FPUIMR FPU_IE_3      LL_SYSCFG_EnableIT_FPU_OFC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableIT_FPU_OFC(void)
{
  SET_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_3);
}

/**
  * @brief  Enable Floating Point Unit Input denormal Interrupt
  * @rmtoll SYSCFG_FPUIMR FPU_IE_4      LL_SYSCFG_EnableIT_FPU_IDC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableIT_FPU_IDC(void)
{
  SET_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_4);
}

/**
  * @brief  Enable Floating Point Unit Inexact Interrupt
  * @rmtoll SYSCFG_FPUIMR FPU_IE_5      LL_SYSCFG_EnableIT_FPU_IXC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableIT_FPU_IXC(void)
{
  SET_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_5);
}

/**
  * @brief  Disable Floating Point Unit Invalid operation Interrupt
  * @rmtoll SYSCFG_FPUIMR FPU_IE_0      LL_SYSCFG_DisableIT_FPU_IOC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableIT_FPU_IOC(void)
{
  CLEAR_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_0);
}

/**
  * @brief  Disable Floating Point Unit Divide-by-zero Interrupt
  * @rmtoll SYSCFG_FPUIMR FPU_IE_1      LL_SYSCFG_DisableIT_FPU_DZC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableIT_FPU_DZC(void)
{
  CLEAR_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_1);
}

/**
  * @brief  Disable Floating Point Unit Underflow Interrupt
  * @rmtoll SYSCFG_FPUIMR FPU_IE_2      LL_SYSCFG_DisableIT_FPU_UFC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableIT_FPU_UFC(void)
{
  CLEAR_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_2);
}

/**
  * @brief  Disable Floating Point Unit Overflow Interrupt
  * @rmtoll SYSCFG_FPUIMR FPU_IE_3      LL_SYSCFG_DisableIT_FPU_OFC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableIT_FPU_OFC(void)
{
  CLEAR_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_3);
}

/**
  * @brief  Disable Floating Point Unit Input denormal Interrupt
  * @rmtoll SYSCFG_FPUIMR FPU_IE_4      LL_SYSCFG_DisableIT_FPU_IDC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableIT_FPU_IDC(void)
{
  CLEAR_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_4);
}

/**
  * @brief  Disable Floating Point Unit Inexact Interrupt
  * @rmtoll SYSCFG_FPUIMR FPU_IE_5      LL_SYSCFG_DisableIT_FPU_IXC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableIT_FPU_IXC(void)
{
  CLEAR_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_5);
}

/**
  * @brief  Check if Floating Point Unit Invalid operation Interrupt source is enabled or disabled.
  * @rmtoll SYSCFG_FPUIMR FPU_IE_0      LL_SYSCFG_IsEnabledIT_FPU_IOC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIT_FPU_IOC(void)
{
  return ((READ_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_0) == SYSCFG_FPUIMR_FPU_IE_0) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Divide-by-zero Interrupt source is enabled or disabled.
  * @rmtoll SYSCFG_FPUIMR FPU_IE_1      LL_SYSCFG_IsEnabledIT_FPU_DZC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIT_FPU_DZC(void)
{
  return ((READ_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_1) == SYSCFG_FPUIMR_FPU_IE_1) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Underflow Interrupt source is enabled or disabled.
  * @rmtoll SYSCFG_FPUIMR FPU_IE_2      LL_SYSCFG_IsEnabledIT_FPU_UFC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIT_FPU_UFC(void)
{
  return ((READ_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_2) == SYSCFG_FPUIMR_FPU_IE_2) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Overflow Interrupt source is enabled or disabled.
  * @rmtoll SYSCFG_FPUIMR FPU_IE_3      LL_SYSCFG_IsEnabledIT_FPU_OFC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIT_FPU_OFC(void)
{
  return ((READ_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_3) == SYSCFG_FPUIMR_FPU_IE_3) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Input denormal Interrupt source is enabled or disabled.
  * @rmtoll SYSCFG_FPUIMR FPU_IE_4      LL_SYSCFG_IsEnabledIT_FPU_IDC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIT_FPU_IDC(void)
{
  return ((READ_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_4) == SYSCFG_FPUIMR_FPU_IE_4) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Inexact Interrupt source is enabled or disabled.
  * @rmtoll SYSCFG_FPUIMR FPU_IE_5      LL_SYSCFG_IsEnabledIT_FPU_IXC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIT_FPU_IXC(void)
{
  return ((READ_BIT(SYSCFG->FPUIMR, SYSCFG_FPUIMR_FPU_IE_5) == SYSCFG_FPUIMR_FPU_IE_5) ? 1UL : 0UL);
}

/**
  * @brief  Enable SRAM2 Erase (starts a hardware SRAM2 erase operation. This bit is
  * automatically cleared at the end of the SRAM2 erase operation.)
  * @note This bit is write-protected: setting this bit is possible only after the
  *       correct key sequence is written in the SYSCFG_SKR register as described in
  *       the Reference Manual.
  * @rmtoll SYSCFG_SCSR  SRAM2ER       LL_SYSCFG_EnableSRAM2Erase
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableSRAM2Erase(void)
{
  /* Starts a hardware SRAM2 erase operation*/
  SET_BIT(SYSCFG->SCSR, SYSCFG_SCSR_SRAM2ER);
}

/**
  * @brief  Check if SRAM2 erase operation is on going
  * @rmtoll SYSCFG_SCSR  SRAM2BSY      LL_SYSCFG_IsSRAM2EraseOngoing
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsSRAM2EraseOngoing(void)
{
  return ((READ_BIT(SYSCFG->SCSR, SYSCFG_SCSR_SRAM2BSY) == SYSCFG_SCSR_SRAM2BSY) ? 1UL : 0UL);
}

/**
  * @brief  Set connections to TIM1/8/15/16/17 Break inputs
  * @rmtoll SYSCFG_CFGR2 CLL           LL_SYSCFG_SetTIMBreakInputs\n
  *         SYSCFG_CFGR2 SPL           LL_SYSCFG_SetTIMBreakInputs\n
  *         SYSCFG_CFGR2 PVDL          LL_SYSCFG_SetTIMBreakInputs\n
  *         SYSCFG_CFGR2 ECCL          LL_SYSCFG_SetTIMBreakInputs
  * @param  Break This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_TIMBREAK_ECC
  *         @arg @ref LL_SYSCFG_TIMBREAK_PVD
  *         @arg @ref LL_SYSCFG_TIMBREAK_SRAM2_PARITY
  *         @arg @ref LL_SYSCFG_TIMBREAK_LOCKUP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetTIMBreakInputs(uint32_t Break)
{
  MODIFY_REG(SYSCFG->CFGR2, SYSCFG_CFGR2_CLL | SYSCFG_CFGR2_SPL | SYSCFG_CFGR2_PVDL | SYSCFG_CFGR2_ECCL, Break);
}

/**
  * @brief  Get connections to TIM1/8/15/16/17 Break inputs
  * @rmtoll SYSCFG_CFGR2 CLL           LL_SYSCFG_GetTIMBreakInputs\n
  *         SYSCFG_CFGR2 SPL           LL_SYSCFG_GetTIMBreakInputs\n
  *         SYSCFG_CFGR2 PVDL          LL_SYSCFG_GetTIMBreakInputs\n
  *         SYSCFG_CFGR2 ECCL          LL_SYSCFG_GetTIMBreakInputs
  * @retval Returned value can be can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_TIMBREAK_ECC
  *         @arg @ref LL_SYSCFG_TIMBREAK_PVD
  *         @arg @ref LL_SYSCFG_TIMBREAK_SRAM2_PARITY
  *         @arg @ref LL_SYSCFG_TIMBREAK_LOCKUP
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetTIMBreakInputs(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_CLL | SYSCFG_CFGR2_SPL | SYSCFG_CFGR2_PVDL | SYSCFG_CFGR2_ECCL));
}

/**
  * @brief  Check if SRAM2 parity error detected
  * @rmtoll SYSCFG_CFGR2 SPF           LL_SYSCFG_IsActiveFlag_SP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_SP(void)
{
  return ((READ_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_SPF) == SYSCFG_CFGR2_SPF) ? 1UL : 0UL);
}

/**
  * @brief  Clear SRAM2 parity error flag
  * @rmtoll SYSCFG_CFGR2 SPF           LL_SYSCFG_ClearFlag_SP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_ClearFlag_SP(void)
{
  SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_SPF);
}

/**
  * @brief  Enable SRAM2 page write protection
  * @note Write protection is cleared only by a system reset
  * @rmtoll SYSCFG_SWPR  PxWP         LL_SYSCFG_EnableSRAM2PageWRP_0_31
  * @param  SRAM2WRP This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE0
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE1
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE2
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE3
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE4
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE5
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE6
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE7
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE8
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE9
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE10
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE11
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE12
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE13
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE14
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE15
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE16
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE17
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE18
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE19
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE20
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE21
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE22
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE23
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE24
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE25
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE26
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE27
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE28
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE29
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE30
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE31
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableSRAM2PageWRP_0_31(uint32_t SRAM2WRP)
{
  SET_BIT(SYSCFG->SWPR, SRAM2WRP);
}

/**
  * @brief  Enable SRAM2 page write protection for Pages in range 32 to 63
  * @note Write protection is cleared only by a system reset
  * @rmtoll SYSCFG_SWPR2 PxWP          LL_SYSCFG_EnableSRAM2PageWRP_32_63
  * @param  SRAM2WRP This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE32
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE33
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE34
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE35
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE36
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE37
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE38
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE39
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE40
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE41
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE42
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE43
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE44
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE45
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE46
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE47
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE48
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE49
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE50
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE51
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE52
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE53
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE54
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE55
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE56
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE57
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE58
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE59
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE60
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE61
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE62
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE63
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableSRAM2PageWRP_32_63(uint32_t SRAM2WRP)
{
  SET_BIT(SYSCFG->SWPR2, SRAM2WRP);
}

/**
  * @brief  SRAM2 page write protection lock prior to erase
  * @rmtoll SYSCFG_SKR   KEY           LL_SYSCFG_LockSRAM2WRP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_LockSRAM2WRP(void)
{
  /* Writing a wrong key reactivates the write protection */
  WRITE_REG(SYSCFG->SKR, 0x00);
}

/**
  * @brief  SRAM2 page write protection unlock prior to erase
  * @rmtoll SYSCFG_SKR   KEY           LL_SYSCFG_UnlockSRAM2WRP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_UnlockSRAM2WRP(void)
{
  /* unlock the write protection of the SRAM2ER bit */
  WRITE_REG(SYSCFG->SKR, 0xCA);
  WRITE_REG(SYSCFG->SKR, 0x53);
}

/** @defgroup SYSTEM_LL_EF_SYSCFG_Secure_Management Secure Management
  * @{
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/**
  * @brief  Configure Secure mode
  * @note Only available from secure state when system implements security (TZEN=1)
  * @rmtoll SYSCFG_SECCFGR SYSCFGSEC    LL_SYSCFG_ConfigSecure\n
  *         SYSCFG_SECCFGR CLASSBSEC    LL_SYSCFG_ConfigSecure\n
  *         SYSCFG_SECCFGR SRAM2SEC     LL_SYSCFG_ConfigSecure\n
  *         SYSCFG_SECCFGR FPUSEC       LL_SYSCFG_ConfigSecure
  * @param  Configuration This parameter shall be the full combination
  *         of the following values:
  *         @arg @ref LL_SYSCFG_CLOCK_SEC or @arg @ref LL_SYSCFG_CLOCK_NSEC
  *         @arg @ref LL_SYSCFG_CLASSB_SEC or @arg @ref LL_SYSCFG_CLASSB_NSEC
  *         @arg @ref LL_SYSCFG_SRAM2_SEC or @arg @ref LL_SYSCFG_SRAM2_NSEC
  *         @arg @ref LL_SYSCFG_FPU_SEC or @arg @ref LL_SYSCFG_FPU_NSEC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_ConfigSecure(uint32_t Configuration)
{
  WRITE_REG(SYSCFG->SECCFGR, Configuration);
}

#endif /* __ARM_FEATURE_CMSE && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @brief  Get Secure mode configuration
  * @note Only available when system implements security (TZEN=1)
  * @rmtoll SYSCFG_SECCFGR SYSCFGSEC    LL_SYSCFG_ConfigSecure\n
  *         SYSCFG_SECCFGR CLASSBSEC    LL_SYSCFG_ConfigSecure\n
  *         SYSCFG_SECCFGR SRAM2SEC     LL_SYSCFG_ConfigSecure\n
  *         SYSCFG_SECCFGR FPUSEC       LL_SYSCFG_ConfigSecure
  * @retval Returned value is the combination of the following values:
  *         @arg @ref LL_SYSCFG_CLOCK_SEC or @arg @ref LL_SYSCFG_CLOCK_NSEC
  *         @arg @ref LL_SYSCFG_CLASSB_SEC or @arg @ref LL_SYSCFG_CLASSB_NSEC
  *         @arg @ref LL_SYSCFG_SRAM2_SEC or @arg @ref LL_SYSCFG_SRAM2_NSEC
  *         @arg @ref LL_SYSCFG_FPU_SEC or @arg @ref LL_SYSCFG_FPU_NSEC
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetConfigSecure(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->SECCFGR, 0xFU));
}

/**
  * @}
  */

/**
  * @}
  */


/** @defgroup SYSTEM_LL_EF_DBGMCU DBGMCU
  * @{
  */

/**
  * @brief  Return the device identifier
  * @rmtoll DBGMCU_IDCODE DEV_ID        LL_DBGMCU_GetDeviceID
  * @retval Values between Min_Data=0x00 and Max_Data=0xFFFF (ex: device ID is 0x6415)
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetDeviceID(void)
{
  return (uint32_t)(READ_BIT(DBGMCU->IDCODE, DBGMCU_IDCODE_DEV_ID));
}

/**
  * @brief  Return the device revision identifier
  * @note This field indicates the revision of the device.
  * @rmtoll DBGMCU_IDCODE REV_ID        LL_DBGMCU_GetRevisionID
  * @retval Values between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetRevisionID(void)
{
  return (uint32_t)(READ_BIT(DBGMCU->IDCODE, DBGMCU_IDCODE_REV_ID) >> DBGMCU_IDCODE_REV_ID_Pos);
}

/**
  * @brief  Enable the Debug Module during STOP mode
  * @rmtoll DBGMCU_CR    DBG_STOP      LL_DBGMCU_EnableDBGStopMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGStopMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Disable the Debug Module during STOP mode
  * @rmtoll DBGMCU_CR    DBG_STOP      LL_DBGMCU_DisableDBGStopMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGStopMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Enable the Debug Module during STANDBY mode
  * @rmtoll DBGMCU_CR    DBG_STANDBY   LL_DBGMCU_EnableDBGStandbyMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGStandbyMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  Disable the Debug Module during STANDBY mode
  * @rmtoll DBGMCU_CR    DBG_STANDBY   LL_DBGMCU_DisableDBGStandbyMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGStandbyMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  Enable the clock for Trace port
  * @rmtoll DBGMCU_CR    TRACE_EN      LL_DBGMCU_EnableTraceClock
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableTraceClock(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_TRACE_EN);
}

/**
  * @brief  Disable the clock for Trace port
  * @rmtoll DBGMCU_CR    TRACE_EN      LL_DBGMCU_DisableTraceClock
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableTraceClock(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_TRACE_EN);
}

/**
  * @brief  Indicate if the clock for Trace port is enabled
  * @rmtoll DBGMCU_CR    TRACE_EN      LL_DBGMCU_IsEnabledTraceClock
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledTraceClock(void)
{
  return ((READ_BIT(DBGMCU->CR, DBGMCU_CR_TRACE_EN) == (DBGMCU_CR_TRACE_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Set Trace pin assignment control
  * @rmtoll DBGMCU_CR    TRACE_IOEN    LL_DBGMCU_SetTracePinAssignment\n
  *         DBGMCU_CR    TRACE_MODE    LL_DBGMCU_SetTracePinAssignment
  * @param  PinAssignment This parameter can be one of the following values:
  *         @arg @ref LL_DBGMCU_TRACE_NONE
  *         @arg @ref LL_DBGMCU_TRACE_ASYNCH
  *         @arg @ref LL_DBGMCU_TRACE_SYNCH_SIZE1
  *         @arg @ref LL_DBGMCU_TRACE_SYNCH_SIZE2
  *         @arg @ref LL_DBGMCU_TRACE_SYNCH_SIZE4
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_SetTracePinAssignment(uint32_t PinAssignment)
{
  MODIFY_REG(DBGMCU->CR, DBGMCU_CR_TRACE_IOEN | DBGMCU_CR_TRACE_MODE, PinAssignment);
}

/**
  * @brief  Get Trace pin assignment control
  * @rmtoll DBGMCU_CR    TRACE_IOEN    LL_DBGMCU_GetTracePinAssignment\n
  *         DBGMCU_CR    TRACE_MODE    LL_DBGMCU_GetTracePinAssignment
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DBGMCU_TRACE_NONE
  *         @arg @ref LL_DBGMCU_TRACE_ASYNCH
  *         @arg @ref LL_DBGMCU_TRACE_SYNCH_SIZE1
  *         @arg @ref LL_DBGMCU_TRACE_SYNCH_SIZE2
  *         @arg @ref LL_DBGMCU_TRACE_SYNCH_SIZE4
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetTracePinAssignment(void)
{
  return (uint32_t)(READ_BIT(DBGMCU->CR, DBGMCU_CR_TRACE_IOEN | DBGMCU_CR_TRACE_MODE));
}

/**
  * @brief  Freeze APB1 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB1FZR1 DBG_xxxx_STOP  LL_DBGMCU_APB1_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM4_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM5_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM6_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM7_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_FDCAN1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APB1FZR1, Periphs);
}

/**
  * @brief  Freeze APB1 peripherals (group2 peripherals)
  * @rmtoll DBGMCU_APB1FZR2 DBG_xxxx_STOP  LL_DBGMCU_APB1_GRP2_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP2_I2C4_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_LPTIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_LPTIM3_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP2_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APB1FZR2, Periphs);
}

/**
  * @brief  Unfreeze APB1 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB1FZR1 DBG_xxxx_STOP  LL_DBGMCU_APB1_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM4_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM5_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM6_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM7_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_FDCAN1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APB1FZR1, Periphs);
}

/**
  * @brief  Unfreeze APB1 peripherals (group2 peripherals)
  * @rmtoll DBGMCU_APB1FZR2 DBG_xxxx_STOP  LL_DBGMCU_APB1_GRP2_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP2_I2C4_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_LPTIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_LPTIM3_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP2_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APB1FZR2, Periphs);
}

/**
  * @brief  Freeze APB2 peripherals
  * @rmtoll DBGMCU_APB2FZR DBG_TIMx_STOP  LL_DBGMCU_APB2_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM8_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM15_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM17_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB2_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APB2FZR, Periphs);
}

/**
  * @brief  Unfreeze APB2 peripherals
  * @rmtoll DBGMCU_APB2FZR DBG_TIMx_STOP  LL_DBGMCU_APB2_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM8_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM15_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM17_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB2_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APB2FZR, Periphs);
}

/**
  * @}
  */

#if defined(VREFBUF)
/** @defgroup SYSTEM_LL_EF_VREFBUF VREFBUF
  * @{
  */

/**
  * @brief  Enable Internal voltage reference
  * @rmtoll VREFBUF_CSR  ENVR          LL_VREFBUF_Enable
  * @retval None
  */
__STATIC_INLINE void LL_VREFBUF_Enable(void)
{
  SET_BIT(VREFBUF->CSR, VREFBUF_CSR_ENVR);
}

/**
  * @brief  Disable Internal voltage reference
  * @rmtoll VREFBUF_CSR  ENVR          LL_VREFBUF_Disable
  * @retval None
  */
__STATIC_INLINE void LL_VREFBUF_Disable(void)
{
  CLEAR_BIT(VREFBUF->CSR, VREFBUF_CSR_ENVR);
}

/**
  * @brief  Enable high impedance (VREF+pin is high impedance)
  * @rmtoll VREFBUF_CSR  HIZ           LL_VREFBUF_EnableHIZ
  * @retval None
  */
__STATIC_INLINE void LL_VREFBUF_EnableHIZ(void)
{
  SET_BIT(VREFBUF->CSR, VREFBUF_CSR_HIZ);
}

/**
  * @brief  Disable high impedance (VREF+pin is internally connected to the voltage reference buffer output)
  * @rmtoll VREFBUF_CSR  HIZ           LL_VREFBUF_DisableHIZ
  * @retval None
  */
__STATIC_INLINE void LL_VREFBUF_DisableHIZ(void)
{
  CLEAR_BIT(VREFBUF->CSR, VREFBUF_CSR_HIZ);
}

/**
  * @brief  Set the Voltage reference scale
  * @rmtoll VREFBUF_CSR  VRS           LL_VREFBUF_SetVoltageScaling
  * @param  Scale This parameter can be one of the following values:
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE0
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE1
  * @retval None
  */
__STATIC_INLINE void LL_VREFBUF_SetVoltageScaling(uint32_t Scale)
{
  MODIFY_REG(VREFBUF->CSR, VREFBUF_CSR_VRS, Scale);
}

/**
  * @brief  Get the Voltage reference scale
  * @rmtoll VREFBUF_CSR  VRS           LL_VREFBUF_GetVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE0
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE1
  */
__STATIC_INLINE uint32_t LL_VREFBUF_GetVoltageScaling(void)
{
  return (uint32_t)(READ_BIT(VREFBUF->CSR, VREFBUF_CSR_VRS));
}

/**
  * @brief  Get the VREFBUF trimming value for VRS=0 (VREF_SC0)
  * @retval Between 0 and 0x3F
  */
__STATIC_INLINE uint32_t LL_VREFBUF_SC0_GetCalibration(void)
{
  return (uint32_t)(*VREFBUF_SC0_CAL_ADDR);
}

/**
  * @brief  Get the VREFBUF trimming value for VRS=1 (VREF_SC1)
  * @retval Between 0 and 0x3F
  */
__STATIC_INLINE uint32_t LL_VREFBUF_SC1_GetCalibration(void)
{
  return (uint32_t)(*VREFBUF_SC1_CAL_ADDR);
}

/**
  * @brief  Check if Voltage reference buffer is ready
  * @rmtoll VREFBUF_CSR  VRR           LL_VREFBUF_IsVREFReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_VREFBUF_IsVREFReady(void)
{
  return ((READ_BIT(VREFBUF->CSR, VREFBUF_CSR_VRR) == VREFBUF_CSR_VRR) ? 1UL : 0UL);
}

/**
  * @brief  Get the trimming code for VREFBUF calibration
  * @rmtoll VREFBUF_CCR  TRIM          LL_VREFBUF_GetTrimming
  * @retval Between 0 and 0x3F
  */
__STATIC_INLINE uint32_t LL_VREFBUF_GetTrimming(void)
{
  return (uint32_t)(READ_BIT(VREFBUF->CCR, VREFBUF_CCR_TRIM));
}

/**
  * @brief  Set the trimming code for VREFBUF calibration (Tune the internal reference buffer voltage)
  * @rmtoll VREFBUF_CCR  TRIM          LL_VREFBUF_SetTrimming
  * @param  Value Between 0 and 0x3F
  * @retval None
  */
__STATIC_INLINE void LL_VREFBUF_SetTrimming(uint32_t Value)
{
  WRITE_REG(VREFBUF->CCR, Value);
}

/**
  * @}
  */
#endif /* VREFBUF */

/** @defgroup SYSTEM_LL_EF_FLASH FLASH
  * @{
  */

/**
  * @brief  Set FLASH Latency
  * @rmtoll FLASH_ACR    LATENCY       LL_FLASH_SetLatency
  * @param  Latency This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0
  *         @arg @ref LL_FLASH_LATENCY_1
  *         @arg @ref LL_FLASH_LATENCY_2
  *         @arg @ref LL_FLASH_LATENCY_3
  *         @arg @ref LL_FLASH_LATENCY_4
  *         @arg @ref LL_FLASH_LATENCY_5
  *         @arg @ref LL_FLASH_LATENCY_6
  *         @arg @ref LL_FLASH_LATENCY_7
  *         @arg @ref LL_FLASH_LATENCY_8
  *         @arg @ref LL_FLASH_LATENCY_9
  *         @arg @ref LL_FLASH_LATENCY_10
  *         @arg @ref LL_FLASH_LATENCY_11
  *         @arg @ref LL_FLASH_LATENCY_12
  *         @arg @ref LL_FLASH_LATENCY_13
  *         @arg @ref LL_FLASH_LATENCY_14
  *         @arg @ref LL_FLASH_LATENCY_15
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetLatency(uint32_t Latency)
{
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, Latency);
}

/**
  * @brief  Get FLASH Latency
  * @rmtoll FLASH_ACR    LATENCY       LL_FLASH_GetLatency
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0
  *         @arg @ref LL_FLASH_LATENCY_1
  *         @arg @ref LL_FLASH_LATENCY_2
  *         @arg @ref LL_FLASH_LATENCY_3
  *         @arg @ref LL_FLASH_LATENCY_4
  *         @arg @ref LL_FLASH_LATENCY_5
  *         @arg @ref LL_FLASH_LATENCY_6
  *         @arg @ref LL_FLASH_LATENCY_7
  *         @arg @ref LL_FLASH_LATENCY_8
  *         @arg @ref LL_FLASH_LATENCY_9
  *         @arg @ref LL_FLASH_LATENCY_10
  *         @arg @ref LL_FLASH_LATENCY_11
  *         @arg @ref LL_FLASH_LATENCY_12
  *         @arg @ref LL_FLASH_LATENCY_13
  *         @arg @ref LL_FLASH_LATENCY_14
  *         @arg @ref LL_FLASH_LATENCY_15
  */
__STATIC_INLINE uint32_t LL_FLASH_GetLatency(void)
{
  return (uint32_t)(READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY));
}

/**
  * @brief  Enable Flash Power-down mode during run mode or Low-power run mode
  * @note Flash memory can be put in power-down mode only when the code is executed
  *       from RAM
  * @note Flash must not be accessed when power down is enabled
  * @note Flash must not be put in power-down while a program or an erase operation
  *       is on-going
  * @rmtoll FLASH_ACR    RUN_PD        LL_FLASH_EnableRunPowerDown\n
  *         FLASH_PDKEYR PDKEY1        LL_FLASH_EnableRunPowerDown\n
  *         FLASH_PDKEYR PDKEY2        LL_FLASH_EnableRunPowerDown
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableRunPowerDown(void)
{
  /* Following values must be written consecutively to unlock the RUN_PD bit in
     FLASH_ACR */
  WRITE_REG(FLASH->PDKEYR, FLASH_PDKEY1);
  WRITE_REG(FLASH->PDKEYR, FLASH_PDKEY2);
  SET_BIT(FLASH->ACR, FLASH_ACR_RUN_PD);
}

/**
  * @brief  Disable Flash Power-down mode during run mode or Low-power run mode
  * @rmtoll FLASH_ACR    RUN_PD        LL_FLASH_DisableRunPowerDown\n
  *         FLASH_PDKEYR PDKEY1        LL_FLASH_DisableRunPowerDown\n
  *         FLASH_PDKEYR PDKEY2        LL_FLASH_DisableRunPowerDown
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableRunPowerDown(void)
{
  /* Following values must be written consecutively to unlock the RUN_PD bit in
     FLASH_ACR */
  WRITE_REG(FLASH->PDKEYR, FLASH_PDKEY1);
  WRITE_REG(FLASH->PDKEYR, FLASH_PDKEY2);
  CLEAR_BIT(FLASH->ACR, FLASH_ACR_RUN_PD);
}

/**
  * @brief  Enable Flash Power-down mode during Sleep or Low-power sleep mode
  * @note Flash must not be put in power-down while a program or an erase operation
  *       is on-going
  * @rmtoll FLASH_ACR    SLEEP_PD      LL_FLASH_EnableSleepPowerDown
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableSleepPowerDown(void)
{
  SET_BIT(FLASH->ACR, FLASH_ACR_SLEEP_PD);
}

/**
  * @brief  Disable Flash Power-down mode during Sleep or Low-power sleep mode
  * @rmtoll FLASH_ACR    SLEEP_PD      LL_FLASH_DisableSleepPowerDown
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableSleepPowerDown(void)
{
  CLEAR_BIT(FLASH->ACR, FLASH_ACR_SLEEP_PD);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined (FLASH) || defined (SYSCFG) || defined (DBGMCU) || defined (VREFBUF) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32L5xx_LL_SYSTEM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
