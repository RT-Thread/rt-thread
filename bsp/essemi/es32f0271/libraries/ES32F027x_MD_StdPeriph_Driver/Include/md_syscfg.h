/**
  ******************************************************************************
  * @file    md_SYSCFG.h
  * @brief   ES32F0271 SYSCFG HEAD File.
  *
  * @version V1.00.02
  * @date    30/11/2018
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MD_SYSCFG_H__
#define __MD_SYSCFG_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/ 
#include <stdbool.h>
#include "es32f0271.h"
#include "reg_syscfg.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined (SYSCFG)

/** @defgroup SYSCFG SYSCFG
  * @brief SYSCFG micro driver
  * @{
  */
  
/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/

/* Public types ---------------------------------------------------------------*/
/** @defgroup MD_SYSCFG_PT_INIT RCC Public Init structures
  * @{
  */

/**
  * @brief MD SYSCFG Init Structure definition
  */


/**
  * @} MD_SYSCFG_PT_INIT
  */

/* Public constants -----------------------------------------------------------*/
/** @defgroup MD_SYSCFG_Public_Constants SYSCFG Public Constants
  * @{
  */

/** @defgroup MD_SYSCFG_REMAP_REALMOD_FLAG Current Memory mapping Status
  * @{
  */
#define MD_SYSCFG_REALMOD_MAIN    (0x00000000UL)  /** @brief Main Flash memory mapped at 0x00000000 */
#define MD_SYSCFG_REALMOD_SYSTEM  (0x00000001UL)  /** @brief System Flash memory mapped at 0x00000000 */
#define MD_SYSCFG_REALMOD_SRAM    (0x00000002UL)  /** @brief SRAM mapped at 0x00000000 */
/**
  * @} MD_SYSCFG_REMAP_REALMOD_FLAG
  */

/** @defgroup MD_SYSCFG_REMAP_MEMMOD_FLAG Memory mapping selection bits
  * @{
  */
#define MD_SYSCFG_MEMMOD_MAIN    (0x00000000UL)  /** @brief Main Flash memory mapped at 0x00000000 */
#define MD_SYSCFG_MEMMOD_SYSTEM  (0x00000001UL)  /** @brief System Flash memory mapped at 0x00000000 */
#define MD_SYSCFG_MEMMOD_SRAM    (0x00000002UL)  /** @brief SRAM mapped at 0x00000000 */
/**
  * @} MD_SYSCFG_REMAP_MEMMOD_FLAG
  */

/** @defgroup MD_SYSCFG_IRSEL_PLR_FLAG IR Polarity
  * @{
  */
#define MD_SYSCFG_PLR_INV_SEL1_AND_SEL2    (0x00000000UL)  /** @brief IR out = ~(SEL1 & SEL2) */
#define MD_SYSCFG_PLR_SEL1_AND_SEL2        (0x00000001UL)  /** @brief IR out = SEL1 & SEL2 */
/**
  * @} MD_SYSCFG_IRSEL_PLR_FLAG
  */

/** @defgroup MD_SYSCFG_IRSEL_SEL2 IR Select 2
  * @{
  */
#define MD_SYSCFG_SEL2_OFF             (0x00000000UL)  /** @brief 0000: OFF */
#define MD_SYSCFG_SEL2_GP16C2T4_CH1    (0x00000001UL)  /** @brief 0001: GP16C2T4_CH1 */
#define MD_SYSCFG_SEL2_GP16C2T4_CH2    (0x00000002UL)  /** @brief 0010: GP16C2T4_CH2 */
#define MD_SYSCFG_SEL2_UART3_TX        (0x00000003UL)  /** @brief 0100: UART3_TX */
#define MD_SYSCFG_SEL2_SUART2_TX       (0x00000004UL)  /** @brief 1000: SUART2_TX */
/**
  * @} MD_SYSCFG_IRSEL_SEL2
  */

/** @defgroup MD_SYSCFG_IRSEL_SEL1 IR Select 1
  * @{
  */
#define MD_SYSCFG_SEL1_OFF             (0x00000000UL)  /** @brief 0000: OFF */
#define MD_SYSCFG_SEL1_GP16C2T2_CH1    (0x00000001UL)  /** @brief 0001: GP16C2T2_CH1 */
#define MD_SYSCFG_SEL1_GP16C2T2_CH2    (0x00000002UL)  /** @brief 0010: GP16C2T2_CH2 */
#define MD_SYSCFG_SEL1_GP16C2T3_CH1    (0x00000003UL)  /** @brief 0100: GP16C2T3_CH1 */
#define MD_SYSCFG_SEL1_GP16C2T3_CH2    (0x00000004UL)  /** @brief 1000: GP16C2T3_CH2 */
/**
  * @} MD_SYSCFG_IRSEL_SEL1
  */

/** @defgroup MD_SYSCFG_CFG_DBGH_EN DBG Halt enable bit
  * @{
  */
#define MD_SYSCFG_DBGH_EN_IWDT         (0x00002000UL)
#define MD_SYSCFG_DBGH_EN_WWDT         (0x00001000UL)
#define MD_SYSCFG_DBGH_EN_BS16T1       (0x00000200UL)
#define MD_SYSCFG_DBGH_EN_GP16C4T3     (0x00000100UL)
#define MD_SYSCFG_DBGH_EN_GP16C4T2     (0x00000080UL)
#define MD_SYSCFG_DBGH_EN_GP16C4T1     (0x00000040UL)
#define MD_SYSCFG_DBGH_EN_GP32C4T1     (0x00000020UL)
#define MD_SYSCFG_DBGH_EN_GP16C2T4     (0x00000010UL)
#define MD_SYSCFG_DBGH_EN_GP16C2T3     (0x00000008UL)
#define MD_SYSCFG_DBGH_EN_GP16C2T2     (0x00000004UL)
#define MD_SYSCFG_DBGH_EN_GP16C2T1     (0x00000002UL)
#define MD_SYSCFG_DBGH_EN_AD16C4T1     (0x00000001UL)
/**
  * @} MD_SYSCFG_CFG_DBGH_EN
  */

/** @defgroup MD_SYSCFG_CFG_VTST Voltage testing
  * @{
  */
#define MD_SYSCFG_VTST_LDO          (0x00000000UL)  /** @brief 00: LDO Buffer Voltage */
#define MD_SYSCFG_VTST_BANDGAP_REF  (0x00000001UL)  /** @brief 01: BandGap Reference Voltage */
#define MD_SYSCFG_VTST_LDO1V2       (0x00000002UL)  /** @brief 10: LDO1V2 Voltage */
#define MD_SYSCFG_VTST_LDO1V5       (0x00000003UL)  /** @brief 11: LDO1V5 Voltage */
/**
  * @} MD_SYSCFG_CFG_VTST
  */

/** @defgroup MD_SYSCFG_CFG_VRLS These bits are written by software to select the voltage reference level by the ADC/DAC
  * @{
  */
#define MD_SYSCFG_VRLS_1V5          (0x00000000UL)  /** @brief 000: 1.5V */
#define MD_SYSCFG_VRLS_2V           (0x00000001UL)  /** @brief 001: 2.0V */
#define MD_SYSCFG_VRLS_2V5          (0x00000002UL)  /** @brief 010: 2.5V */
#define MD_SYSCFG_VRLS_3V           (0x00000003UL)  /** @brief 011: 3.0V */
#define MD_SYSCFG_VRLS_3V5          (0x00000004UL)  /** @brief 100: 3.5V */
#define MD_SYSCFG_VRLS_4V           (0x00000005UL)  /** @brief 101: 4.0V */
#define MD_SYSCFG_VRLS_4V5          (0x00000006UL)  /** @brief 110: 4.5V */
#define MD_SYSCFG_VRLS_5V           (0x00000007UL)  /** @brief 111: 5.0V(VDD5) */
/**
  * @} MD_SYSCFG_CFG_VRLS
  */

/** @defgroup MD_SYSCFG_PWCON_PVLS These bits are written by software to select the voltage reference level by the ADC/DAC
  * @{
  */
#define MD_SYSCFG_PVLS_R1V9_F2V           (0x00000000UL)    /** @brief 0000: R-1.9V, F-2.0V */
#define MD_SYSCFG_PVLS_R2V1_F2V2          (0x00000001UL)    /** @brief 0001: R-2.1V, F-2.2V */
#define MD_SYSCFG_PVLS_R2V3_F2V4          (0x00000002UL)    /** @brief 0010: R-2.3V, F-2.4V */
#define MD_SYSCFG_PVLS_R2V5_F2V6          (0x00000003UL)    /** @brief 0011: R-2.5V, F-2.6V */
#define MD_SYSCFG_PVLS_R2V7_F2V8          (0x00000004UL)    /** @brief 0100: R-2.7V, F-2.8V */
#define MD_SYSCFG_PVLS_R2V9_F3V           (0x00000005UL)    /** @brief 0101: R-2.9V, F-3.0V */
#define MD_SYSCFG_PVLS_R3V1_F3V2          (0x00000006UL)    /** @brief 0110: R-3.1V, F-3.2V */
#define MD_SYSCFG_PVLS_R3V3_F3V4          (0x00000007UL)    /** @brief 0111: R-3.3V, F-3.4V */
#define MD_SYSCFG_PVLS_R3V5_F3V6          (0x00000008UL)    /** @brief 1000: R-3.5V, F-3.6V */
#define MD_SYSCFG_PVLS_R3V7_F3V8          (0x00000009UL)    /** @brief 1001: R-3.7V, F-3.8V */
#define MD_SYSCFG_PVLS_R3V9_F4V           (0x0000000AUL)    /** @brief 1010: R-3.9V, F-4.0V */
#define MD_SYSCFG_PVLS_R4V1_F4V2          (0x0000000BUL)    /** @brief 1011: R-4.1V, F-4.2V */
#define MD_SYSCFG_PVLS_R4V3_F4V4          (0x0000000CUL)    /** @brief 1100: R-4.3V, F-4.4V */
#define MD_SYSCFG_PVLS_R4V5_F4V6          (0x0000000DUL)    /** @brief 1101: R-4.5V, F-4.6V */
#define MD_SYSCFG_PVLS_R4V7_F4V8          (0x0000000EUL)    /** @brief 1110: R-4.7V, F-4.8V */
#define MD_SYSCFG_PVLS_R4V9_F5V           (0x0000000FUL)    /** @brief 1111: R-4.9V, F-5.0V */
/**
  * @} MD_SYSCFG_PWCON_PVLS
  */

/** @defgroup MD_SYSCFG_WKCON_LPLS Low Power Level Select
  * @{
  */
#define MD_SYSCFG_LPLS_LV0          (0x00000000UL)  /** @brief 0 : Level 0, Sleep Mode (Normal) */
#define MD_SYSCFG_LPLS_LV1          (0x00000001UL)  /** @brief 1 : Level 1, Stop Mode (All Clock OFF) */
#define MD_SYSCFG_LPLS_LV2          (0x00000002UL)  /** @brief 2 : Level 2, Standby Mode (SRAM retention) */
#define MD_SYSCFG_LPLS_LV3          (0x00000003UL)  /** @brief 3 : Level 3, Low Power Mode (LDO off) */
#define MD_SYSCFG_LPLS_LV4          (0x00000004UL)  /** @brief 4 : Level 3, Ultra Low Power Mode(LDO off/BandGap off) */
/**
  * @} MD_SYSCFG_WKCON_LPLS
  */

/** @defgroup MD_SYSCFG_WKCON_WKEG WKEGx:WKUPx pin edge sensitive type select
  * @{
  */
#define MD_SYSCFG_WKCON_WKEG_NRST     (0x00000800UL)
#define MD_SYSCFG_WKCON_WKEG_PVD      (0x00000400UL)
#define MD_SYSCFG_WKCON_WKEG_CMP0     (0x00000200UL)
#define MD_SYSCFG_WKCON_WKEG_RTC      (0x00000100UL)
#define MD_SYSCFG_WKCON_WKEG_PIN7     (0x00000080UL)
#define MD_SYSCFG_WKCON_WKEG_PIN6     (0x00000040UL)
#define MD_SYSCFG_WKCON_WKEG_PIN5     (0x00000020UL)
#define MD_SYSCFG_WKCON_WKEG_PIN4     (0x00000010UL)
#define MD_SYSCFG_WKCON_WKEG_PIN3     (0x00000008UL)
#define MD_SYSCFG_WKCON_WKEG_PIN2     (0x00000004UL)
#define MD_SYSCFG_WKCON_WKEG_PIN1     (0x00000002UL)
#define MD_SYSCFG_WKCON_WKEG_PIN0     (0x00000001UL)
/**
  * @} MD_SYSCFG_WKCON_WKEG
  */

/** @defgroup MD_SYSCFG_WKCON_WKEN WKENx: Enable WKUPx pin or wakeup event
  * @{
  */
#define MD_SYSCFG_WKCON_WKEN_NRST     (0x00000800UL)
#define MD_SYSCFG_WKCON_WKEN_PVD      (0x00000400UL)
#define MD_SYSCFG_WKCON_WKEN_CMP0     (0x00000200UL)
#define MD_SYSCFG_WKCON_WKEN_RTC      (0x00000100UL)
#define MD_SYSCFG_WKCON_WKEN_PIN7     (0x00000080UL)
#define MD_SYSCFG_WKCON_WKEN_PIN6     (0x00000040UL)
#define MD_SYSCFG_WKCON_WKEN_PIN5     (0x00000020UL)
#define MD_SYSCFG_WKCON_WKEN_PIN4     (0x00000010UL)
#define MD_SYSCFG_WKCON_WKEN_PIN3     (0x00000008UL)
#define MD_SYSCFG_WKCON_WKEN_PIN2     (0x00000004UL)
#define MD_SYSCFG_WKCON_WKEN_PIN1     (0x00000002UL)
#define MD_SYSCFG_WKCON_WKEN_PIN0     (0x00000001UL)
/**
  * @} MD_SYSCFG_WKCON_WKEN
  */

/** @defgroup MD_SYSCFG_WKSTAT_FG FGx: WKUPx pin or wakeup event flag
  * @{
  */
#define MD_SYSCFG_WKSTAT_FG_NRST     (0x00000800UL)
#define MD_SYSCFG_WKSTAT_FG_PVD      (0x00000400UL)
#define MD_SYSCFG_WKSTAT_FG_CMP0     (0x00000200UL)
#define MD_SYSCFG_WKSTAT_FG_RTC      (0x00000100UL)
#define MD_SYSCFG_WKSTAT_FG_PIN7     (0x00000080UL)
#define MD_SYSCFG_WKSTAT_FG_PIN6     (0x00000040UL)
#define MD_SYSCFG_WKSTAT_FG_PIN5     (0x00000020UL)
#define MD_SYSCFG_WKSTAT_FG_PIN4     (0x00000010UL)
#define MD_SYSCFG_WKSTAT_FG_PIN3     (0x00000008UL)
#define MD_SYSCFG_WKSTAT_FG_PIN2     (0x00000004UL)
#define MD_SYSCFG_WKSTAT_FG_PIN1     (0x00000002UL)
#define MD_SYSCFG_WKSTAT_FG_PIN0     (0x00000001UL)
/**
  * @} MD_SYSCFG_WKSTAT_FG
  */

/**
  * @} MD_SYSCFG_Public_Constants
  */

/* Public macro ---------------------------------------------------------------*/
/** @defgroup MD_SYSCFG_Public_Macros SYSCFG Public Macros
  * @{
  */

/**
  * @brief  Get Current Memory mapping Status
  * @param  syscfg SYSCFG Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_SYSCFG_REALMOD_MAIN
  *         @arg @ref MD_SYSCFG_REALMOD_SYSTEM
  *         @arg @ref MD_SYSCFG_REALMOD_SRAM
  */
__STATIC_INLINE uint32_t md_syscfg_get_remap_REALMOD(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->REMAP, SYSCFG_REMAP_REALMOD_MSK)>>SYSCFG_REMAP_REALMOD_POSS);
}
/**
  * @brief  Set Remap Main Flash Base Address Selection
  * @note   If set 0x1, it means second 4k Byte, If set 0x2, it means third 4k Byte, and so on.
  * @param  syscfg SYSCFG Instance
  * @param  efbase This parameter can be one of the following values:
  *         @arg Max Value 15
  *         @arg Min Value 0
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_remap_efbase(SYSCFG_TypeDef *syscfg, uint32_t efbase)
{
  MODIFY_REG(syscfg->REMAP, SYSCFG_REMAP_EFBASE_MSK, (efbase<<SYSCFG_REMAP_EFBASE_POSS));
}
/**
  * @brief  Get Remap Main Flash Base Address Selection
  * @note   If read 0x1, it means second 4k Byte, If read 0x2, it means third 4k Byte, and so on.
  * @param  syscfg SYSCFG Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 15
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_syscfg_get_remap_efbase(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->REMAP, SYSCFG_REMAP_EFBASE_MSK)>>SYSCFG_REMAP_EFBASE_POSS);
}
/**
  * @brief  Set Memory mapping selection bits
  * @param  syscfg SYSCFG Instance
  * @param  memmod This parameter can be one of the following values:
  *         @arg @ref MD_SYSCFG_MEMMOD_MAIN
  *         @arg @ref MD_SYSCFG_MEMMOD_SYSTEM
  *         @arg @ref MD_SYSCFG_MEMMOD_SRAM
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_remap_memmod(SYSCFG_TypeDef *syscfg, uint32_t memmod)
{
  MODIFY_REG(syscfg->REMAP, SYSCFG_REMAP_MEMMOD_MSK, (memmod<<SYSCFG_REMAP_MEMMOD_POSS));
}
/**
  * @brief  Get Memory mapping selection bits
  * @param  syscfg SYSCFG Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_SYSCFG_MEMMOD_MAIN
  *         @arg @ref MD_SYSCFG_MEMMOD_SYSTEM
  *         @arg @ref MD_SYSCFG_MEMMOD_SRAM
  */
__STATIC_INLINE uint32_t md_syscfg_get_remap_memmod(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->REMAP, SYSCFG_REMAP_MEMMOD_MSK)>>SYSCFG_REMAP_MEMMOD_POSS);
}
/**
  * @brief  Set Start Remap bit
  * @note   This bit set High to start remapping process, that will be auto clear when process was finish.
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_enable_remap_remap(SYSCFG_TypeDef *syscfg)
{
  SET_BIT(syscfg->REMAP, SYSCFG_REMAP_REMAP_MSK);
}
/**
  * @brief  Get Start Remap bit
  * @param  syscfg SYSCFG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_syscfg_get_remap_remap(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->REMAP, SYSCFG_REMAP_REMAP_MSK)>>SYSCFG_REMAP_REMAP_POS);
}

/**
  * @brief  Set IR Polarity
  * @param  syscfg SYSCFG Instance
  * @param  plr This parameter can be one of the following values:
  *         @arg @ref MD_SYSCFG_PLR_INV_SEL1_AND_SEL2
  *         @arg @ref MD_SYSCFG_PLR_SEL1_AND_SEL2
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_irsel_plr(SYSCFG_TypeDef *syscfg, uint32_t plr)
{
  MODIFY_REG(syscfg->IRSEL, SYSCFG_IRSEL_PLR_MSK, (plr<<SYSCFG_IRSEL_PLR_POS));
}
/**
  * @brief  Get IR Polarity
  * @param  syscfg SYSCFG Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_SYSCFG_PLR_INV_SEL1_AND_SEL2
  *         @arg @ref MD_SYSCFG_PLR_SEL1_AND_SEL2
  */
__STATIC_INLINE uint32_t md_syscfg_get_irsel_plr(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->IRSEL, SYSCFG_IRSEL_PLR_MSK)>>SYSCFG_IRSEL_PLR_POS);
}
/**
  * @brief  Set IR Select 2
  * @param  syscfg SYSCFG Instance
  * @param  sel2 This parameter can be one of the following values:
  *         @arg @ref MD_SYSCFG_SEL2_OFF
  *         @arg @ref MD_SYSCFG_SEL2_GP16C2T4_CH1
  *         @arg @ref MD_SYSCFG_SEL2_GP16C2T4_CH2
  *         @arg @ref MD_SYSCFG_SEL2_UART3_TX
  *         @arg @ref MD_SYSCFG_SEL2_SUART2_TX
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_irsel_sel2(SYSCFG_TypeDef *syscfg, uint32_t sel2)
{
  MODIFY_REG(syscfg->IRSEL, SYSCFG_IRSEL_SEL2_MSK, (sel2<<SYSCFG_IRSEL_SEL2_POSS));
}
/**
  * @brief  Get IR Select 2
  * @param  syscfg SYSCFG Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_SYSCFG_SEL2_OFF
  *         @arg @ref MD_SYSCFG_SEL2_GP16C2T4_CH1
  *         @arg @ref MD_SYSCFG_SEL2_GP16C2T4_CH2
  *         @arg @ref MD_SYSCFG_SEL2_UART3_TX
  *         @arg @ref MD_SYSCFG_SEL2_SUART2_TX
  */
__STATIC_INLINE uint32_t md_syscfg_get_irsel_sel2(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->IRSEL, SYSCFG_IRSEL_SEL2_MSK)>>SYSCFG_IRSEL_SEL2_POSS);
}
/**
  * @brief  Set IR Select 1
  * @param  syscfg SYSCFG Instance
  * @param  sel1 This parameter can be one of the following values:
  *         @arg @ref MD_SYSCFG_SEL1_OFF
  *         @arg @ref MD_SYSCFG_SEL1_GP16C2T2_CH1
  *         @arg @ref MD_SYSCFG_SEL1_GP16C2T2_CH2
  *         @arg @ref MD_SYSCFG_SEL1_GP16C2T3_CH1
  *         @arg @ref MD_SYSCFG_SEL1_GP16C2T3_CH2
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_irsel_sel1(SYSCFG_TypeDef *syscfg, uint32_t sel1)
{
  MODIFY_REG(syscfg->IRSEL, SYSCFG_IRSEL_SEL1_MSK, (sel1<<SYSCFG_IRSEL_SEL1_POSS));
}
/**
  * @brief  Get IR Select 1
  * @param  syscfg SYSCFG Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_SYSCFG_SEL1_OFF
  *         @arg @ref MD_SYSCFG_SEL1_GP16C2T2_CH1
  *         @arg @ref MD_SYSCFG_SEL1_GP16C2T2_CH2
  *         @arg @ref MD_SYSCFG_SEL1_GP16C2T3_CH1
  *         @arg @ref MD_SYSCFG_SEL1_GP16C2T3_CH2
  */
__STATIC_INLINE uint32_t md_syscfg_get_irsel_sel1(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->IRSEL, SYSCFG_IRSEL_SEL1_MSK)>>SYSCFG_IRSEL_SEL1_POSS);
}

/**
  * @brief  Set DBG Halt enable bit
  * @note   0: The counter clock is fed even if the core is halted
  *         1: The counter clock is stopped when the core is halted
  * @param  syscfg SYSCFG Instance
  * @param  sel1 This parameter can be one of the following values:
  *         @arg @ref MD_SYSCFG_DBGH_EN_IWDT
  *         @arg @ref MD_SYSCFG_DBGH_EN_WWDT
  *         @arg @ref MD_SYSCFG_DBGH_EN_BS16T1
  *         @arg @ref MD_SYSCFG_DBGH_EN_GP16C4T3
  *         @arg @ref MD_SYSCFG_DBGH_EN_GP16C4T2
  *         @arg @ref MD_SYSCFG_DBGH_EN_GP16C4T1
  *         @arg @ref MD_SYSCFG_DBGH_EN_GP32C4T1
  *         @arg @ref MD_SYSCFG_DBGH_EN_GP16C2T4
  *         @arg @ref MD_SYSCFG_DBGH_EN_GP16C2T3
  *         @arg @ref MD_SYSCFG_DBGH_EN_GP16C2T2
  *         @arg @ref MD_SYSCFG_DBGH_EN_GP16C2T1
  *         @arg @ref MD_SYSCFG_DBGH_EN_AD16C4T1
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_cfg_dbgh_en(SYSCFG_TypeDef *syscfg, uint32_t sel1)
{
  MODIFY_REG(syscfg->CFG, SYSCFG_CFG_DBGH_EN_MSK, (sel1<<SYSCFG_CFG_DBGH_EN_POSS));
}
/**
  * @brief  Get DBG Halt enable bit
  * @param  syscfg SYSCFG Instance
  * @retval State of bit (1 or 0).
  *         0: The counter clock is fed even if the core is halted
  *         1: The counter clock is stopped when the core is halted
  */
__STATIC_INLINE uint32_t md_syscfg_get_cfg_dbgh_en(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->CFG, SYSCFG_CFG_DBGH_EN_MSK)>>SYSCFG_CFG_DBGH_EN_POSS);
}
/**
  * @brief  PVD lock enable bit
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_enable_cfg_pvdlck(SYSCFG_TypeDef *syscfg)
{
  SET_BIT(syscfg->CFG, SYSCFG_CFG_PVD_LCK_MSK);
}
/**
  * @brief  PVD lock disable bit
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_disable_cfg_pvdlck(SYSCFG_TypeDef *syscfg)
{
  CLEAR_BIT(syscfg->CFG, SYSCFG_CFG_PVD_LCK_MSK);
}
/**
  * @brief  Get PVD lock bit
  * @param  syscfg SYSCFG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_syscfg_get_cfg_pvdlck(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->CFG, SYSCFG_CFG_PVD_LCK_MSK)>>SYSCFG_CFG_PVD_LCK_POS);
}
/**
  * @brief  Clock security system lock enable bit
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_enable_cfg_csslck(SYSCFG_TypeDef *syscfg)
{
  SET_BIT(syscfg->CFG, SYSCFG_CFG_CSS_LCK_MSK);
}
/**
  * @brief  Clock security system lock enable bit
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_disable_cfg_csslck(SYSCFG_TypeDef *syscfg)
{
  CLEAR_BIT(syscfg->CFG, SYSCFG_CFG_CSS_LCK_MSK);
}
/**
  * @brief  Clock security system lock enable bit
  * @param  syscfg SYSCFG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_syscfg_get_cfg_csslck(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->CFG, SYSCFG_CFG_CSS_LCK_MSK)>>SYSCFG_CFG_CSS_LCK_POS);
}
/**
  * @brief  Cortex-M0 LOCKUP bit enable bit
  * @note   This bit is set by software and cleared by a system reset.
  *         It can be use to enable and lock the connection of Cortex-M0 LOCKUP (Hardfault) output to AD16C4T/GP16C2T1-4 Break input.
  * @note   1: Cortex-M0 LOCKUP output connected to AD16C4T/GP16C2T1/GP16C2T2/GP16C2T3/GP16C2T4 Break input
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_enable_cfg_cpulck(SYSCFG_TypeDef *syscfg)
{
  SET_BIT(syscfg->CFG, SYSCFG_CFG_CPU_LCK_MSK);
}
/**
  * @brief  Cortex-M0 LOCKUP bit disable bit
  * @note   0: Cortex-M0 LOCKUP output disconnected from AD16C4T / GP16C2T1-4 Break input
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_disable_cfg_cpulck(SYSCFG_TypeDef *syscfg)
{
  CLEAR_BIT(syscfg->CFG, SYSCFG_CFG_CPU_LCK_MSK);
}
/**
  * @brief  Get Cortex-M0 LOCKUP bit
  * @param  syscfg SYSCFG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_syscfg_get_cfg_cpulck(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->CFG, SYSCFG_CFG_CPU_LCK_MSK)>>SYSCFG_CFG_CPU_LCK_POS);
}
/**
  * @brief  Set Voltage testing, This bit is set and cleared by software.
  * @param  syscfg SYSCFG Instance
  * @param  vtst This parameter can be one of the following values:
  *         @arg @ref MD_SYSCFG_VTST_LDO
  *         @arg @ref MD_SYSCFG_VTST_BANDGAP_REF
  *         @arg @ref MD_SYSCFG_VTST_LDO1V2
  *         @arg @ref MD_SYSCFG_VTST_LDO1V5
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_cfg_vtst(SYSCFG_TypeDef *syscfg, uint32_t vtst)
{
  MODIFY_REG(syscfg->CFG, SYSCFG_CFG_VTST_MSK, (vtst<<SYSCFG_CFG_VTST_POSS));
}
/**
  * @brief  Get Voltage testing, This bit is set and cleared by software.
  * @param  syscfg SYSCFG Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_SYSCFG_VTST_LDO
  *         @arg @ref MD_SYSCFG_VTST_BANDGAP_REF
  *         @arg @ref MD_SYSCFG_VTST_LDO1V2
  *         @arg @ref MD_SYSCFG_VTST_LDO1V5
  */
__STATIC_INLINE uint32_t md_syscfg_get_cfg_vtst(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->CFG, SYSCFG_CFG_VTST_MSK)>>SYSCFG_CFG_VTST_POSS);
}
/**
  * @brief  Enable External NRST Pin reset request
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_enable_cfg_nrstreq(SYSCFG_TypeDef *syscfg)
{
  SET_BIT(syscfg->CFG, SYSCFG_CFG_NRSTREQ_MSK);
}
/**
  * @brief  Disable External NRST Pin reset request
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_disable_cfg_nrstreq(SYSCFG_TypeDef *syscfg)
{
  CLEAR_BIT(syscfg->CFG, SYSCFG_CFG_NRSTREQ_MSK);
}
/**
  * @brief  External NRST Pin reset request
  * @param  syscfg SYSCFG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_syscfg_get_cfg_nrstreq(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->CFG, SYSCFG_CFG_NRSTREQ_MSK)>>SYSCFG_CFG_NRSTREQ_POS);
}
/**
  * @brief  ADC/DAC current generator enabled
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_enable_cfg_currgen(SYSCFG_TypeDef *syscfg)
{
  SET_BIT(syscfg->CFG, SYSCFG_CFG_CURRGEN_MSK);
}
/**
  * @brief  ADC/DAC current generator disabled
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_disable_cfg_currgen(SYSCFG_TypeDef *syscfg)
{
  CLEAR_BIT(syscfg->CFG, SYSCFG_CFG_CURRGEN_MSK);
}
/**
  * @brief  ADC/DAC current generator status
  * @param  syscfg SYSCFG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_syscfg_get_cfg_currgen(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->CFG, SYSCFG_CFG_CURRGEN_MSK)>>SYSCFG_CFG_CURRGEN_POS);
}
/**
  * @brief  Temperature sensor enabled
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_enable_cfg_tempen(SYSCFG_TypeDef *syscfg)
{
  SET_BIT(syscfg->CFG, SYSCFG_CFG_TEMPEN_MSK);
}
/**
  * @brief  Temperature sensor disabled
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_disable_cfg_tempen(SYSCFG_TypeDef *syscfg)
{
  CLEAR_BIT(syscfg->CFG, SYSCFG_CFG_TEMPEN_MSK);
}
/**
  * @brief  Get Temperature sensor status
  * @param  syscfg SYSCFG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_syscfg_get_cfg_tempen(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->CFG, SYSCFG_CFG_TEMPEN_MSK)>>SYSCFG_CFG_TEMPEN_POS);
}
/**
  * @brief  Voltage reference enabled
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_enable_cfg_vrefen(SYSCFG_TypeDef *syscfg)
{
  SET_BIT(syscfg->CFG, SYSCFG_CFG_VREFEN_MSK);
}
/**
  * @brief  Voltage reference disabled
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_disable_cfg_vrefen(SYSCFG_TypeDef *syscfg)
{
  CLEAR_BIT(syscfg->CFG, SYSCFG_CFG_VREFEN_MSK);
}
/**
  * @brief  Get Voltage reference status
  * @param  syscfg SYSCFG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_syscfg_get_cfg_vrefen(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->CFG, SYSCFG_CFG_VREFEN_MSK)>>SYSCFG_CFG_VREFEN_POS);
}
/**
  * @brief  Set These bits are written by software to select the voltage reference level by the ADC/DAC:
  * @param  syscfg SYSCFG Instance
  * @param  vlrs This parameter can be one of the following values:
  *         @arg @ref MD_SYSCFG_VRLS_1V5
  *         @arg @ref MD_SYSCFG_VRLS_2V
  *         @arg @ref MD_SYSCFG_VRLS_2V5
  *         @arg @ref MD_SYSCFG_VRLS_3V
  *         @arg @ref MD_SYSCFG_VRLS_3V5
  *         @arg @ref MD_SYSCFG_VRLS_4V
  *         @arg @ref MD_SYSCFG_VRLS_4V5
  *         @arg @ref MD_SYSCFG_VRLS_5V
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_cfg_vlrs(SYSCFG_TypeDef *syscfg, uint32_t vlrs)
{
  MODIFY_REG(syscfg->CFG, SYSCFG_CFG_VRLS_MSK, (vlrs<<SYSCFG_CFG_VRLS_POSS));
}
/**
  * @brief  Get These bits are written by software to select the voltage reference level by the ADC/DAC:
  * @param  syscfg SYSCFG Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_SYSCFG_VRLS_1V5
  *         @arg @ref MD_SYSCFG_VRLS_2V
  *         @arg @ref MD_SYSCFG_VRLS_2V5
  *         @arg @ref MD_SYSCFG_VRLS_3V
  *         @arg @ref MD_SYSCFG_VRLS_3V5
  *         @arg @ref MD_SYSCFG_VRLS_4V
  *         @arg @ref MD_SYSCFG_VRLS_4V5
  *         @arg @ref MD_SYSCFG_VRLS_5V
  */
__STATIC_INLINE uint32_t md_syscfg_get_cfg_vlrs(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->CFG, SYSCFG_CFG_VRLS_MSK)>>SYSCFG_CFG_VRLS_POSS);
}

/**
  * @brief  WKCON0-7 IO Setting Value LOCKED enabled
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_enable_pwcon_iolock(SYSCFG_TypeDef *syscfg)
{
  MODIFY_REG(syscfg->PWCON, SYSCFG_PWCON_IOLOCK_MSK, (ENABLE<<SYSCFG_PWCON_IOLOCK_POS));
}
/**
  * @brief  WKCON0-7 IO Setting Value LOCKED disabled
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_disable_pwcon_iolock(SYSCFG_TypeDef *syscfg)
{
  MODIFY_REG(syscfg->PWCON, SYSCFG_PWCON_IOLOCK_MSK, (DISABLE<<SYSCFG_PWCON_IOLOCK_POS));
}
/**
  * @brief  Get WKCON0-7 IO Setting Value LOCKED status
  * @param  syscfg SYSCFG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_syscfg_get_pwcon_iolock(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->PWCON, SYSCFG_PWCON_IOLOCK_MSK)>>SYSCFG_PWCON_IOLOCK_POS);
}
/**
  * @brief  Set BandGap Trimming Value
  * @param  syscfg SYSCFG Instance
  * @param  bgtrim This parameter can be one of the following values:
  *         @arg Max Value 15
  *         @arg Min Value 0
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_pwcon_bgtrim(SYSCFG_TypeDef *syscfg, uint32_t bgtrim)
{
  MODIFY_REG(syscfg->PWCON, SYSCFG_PWCON_BGTRIM_MSK, (bgtrim<<SYSCFG_PWCON_BGTRIM_POSS));
}
/**
  * @brief  Get BandGap Trimming Value
  * @param  syscfg SYSCFG Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 15
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_syscfg_get_pwcon_bgtrim(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->PWCON, SYSCFG_PWCON_BGTRIM_MSK)>>SYSCFG_PWCON_BGTRIM_POSS);
}
/**
  * @brief  HSI auto calibration result value LOCK
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_enable_pwcon_hrclock(SYSCFG_TypeDef *syscfg)
{
  SET_BIT(syscfg->PWCON, SYSCFG_PWCON_HRCLOCK_MSK);
}
/**
  * @brief  HSI auto calibration result value unLOCK
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_disable_pwcon_hrclock(SYSCFG_TypeDef *syscfg)
{
  CLEAR_BIT(syscfg->PWCON, SYSCFG_PWCON_HRCLOCK_MSK);
}
/**
  * @brief  Get HSI auto calibration result value
  * @param  syscfg SYSCFG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_syscfg_get_pwcon_hrclock(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->PWCON, SYSCFG_PWCON_HRCLOCK_MSK)>>SYSCFG_PWCON_HRCLOCK_POS);
}
/**
  * @brief  Set HSI auto calibration result value
  * @param  syscfg SYSCFG Instance
  * @param  hsitrim This parameter can be one of the following values:
  *         @arg Max Value 255
  *         @arg Min Value 0
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_pwcon_hrctrim(SYSCFG_TypeDef *syscfg, uint32_t hsitrim)
{
  MODIFY_REG(syscfg->PWCON, SYSCFG_PWCON_HRCTRIM_MSK, (hsitrim<<SYSCFG_PWCON_HRCTRIM_POSS));
}
/**
  * @brief  Get HSI auto calibration result value
  * @param  syscfg SYSCFG Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 255
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_syscfg_get_pwcon_hrctrim(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->PWCON, SYSCFG_PWCON_HRCTRIM_MSK)>>SYSCFG_PWCON_HRCTRIM_POSS);
}
/**
  * @brief  Set LSI Driver Select
  * @param  syscfg SYSCFG Instance
  * @param  loscdrv This parameter can be one of the following values:
  *         @arg Max Value 7
  *         @arg Min Value 0
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_pwcon_loscdrv(SYSCFG_TypeDef *syscfg, uint32_t loscdrv)
{
  MODIFY_REG(syscfg->PWCON, SYSCFG_PWCON_LOSCDRV_MSK, (loscdrv<<SYSCFG_PWCON_LOSCDRV_POSS));
}
/**
  * @brief  Get LSI Driver Select
  * @param  syscfg SYSCFG Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 7
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_syscfg_get_pwcon_loscdrv(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->PWCON, SYSCFG_PWCON_LOSCDRV_MSK)>>SYSCFG_PWCON_LOSCDRV_POSS);
}
/**
  * @brief  Power voltage detector(PVD) enable
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_enable_pwcon_pvden(SYSCFG_TypeDef *syscfg)
{
  SET_BIT(syscfg->PWCON, SYSCFG_PWCON_PVDEN_MSK);
}
/**
  * @brief  Power voltage detector(PVD) disable
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_disable_pwcon_pvden(SYSCFG_TypeDef *syscfg)
{
  CLEAR_BIT(syscfg->PWCON, SYSCFG_PWCON_PVDEN_MSK);
}
/**
  * @brief  Get Power voltage detector(PVD) status
  * @param  syscfg SYSCFG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_syscfg_get_pwcon_pvden(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->PWCON, SYSCFG_PWCON_PVDEN_MSK)>>SYSCFG_PWCON_PVDEN_POS);
}
/**
  * @brief  Set power voltage detector
  * @note   These bits are written by software to select the voltage threshold detected by the power voltage detector
  * @param  syscfg SYSCFG Instance
  * @param  pvls This parameter can be one of the following values:
  *         @arg @ref MD_SYSCFG_PVLS_R1V9_F2V
  *         @arg @ref MD_SYSCFG_PVLS_R2V1_F2V2
  *         @arg @ref MD_SYSCFG_PVLS_R2V3_F2V4
  *         @arg @ref MD_SYSCFG_PVLS_R2V5_F2V6
  *         @arg @ref MD_SYSCFG_PVLS_R2V7_F2V8
  *         @arg @ref MD_SYSCFG_PVLS_R2V9_F3V
  *         @arg @ref MD_SYSCFG_PVLS_R3V1_F3V2
  *         @arg @ref MD_SYSCFG_PVLS_R3V3_F3V4
  *         @arg @ref MD_SYSCFG_PVLS_R3V5_F3V6
  *         @arg @ref MD_SYSCFG_PVLS_R3V7_F3V8
  *         @arg @ref MD_SYSCFG_PVLS_R3V9_F4V
  *         @arg @ref MD_SYSCFG_PVLS_R4V1_F4V2
  *         @arg @ref MD_SYSCFG_PVLS_R4V3_F4V4
  *         @arg @ref MD_SYSCFG_PVLS_R4V5_F4V6
  *         @arg @ref MD_SYSCFG_PVLS_R4V7_F4V8
  *         @arg @ref MD_SYSCFG_PVLS_R4V9_F5V
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_pwcon_pvls(SYSCFG_TypeDef *syscfg, uint32_t pvls)
{
  MODIFY_REG(syscfg->PWCON, SYSCFG_PWCON_PVLS_MSK, (pvls<<SYSCFG_PWCON_PVLS_POSS));
}
/**
  * @brief  Get power voltage detector
  * @param  syscfg SYSCFG Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_SYSCFG_PVLS_R1V9_F2V
  *         @arg @ref MD_SYSCFG_PVLS_R2V1_F2V2
  *         @arg @ref MD_SYSCFG_PVLS_R2V3_F2V4
  *         @arg @ref MD_SYSCFG_PVLS_R2V5_F2V6
  *         @arg @ref MD_SYSCFG_PVLS_R2V7_F2V8
  *         @arg @ref MD_SYSCFG_PVLS_R2V9_F3V
  *         @arg @ref MD_SYSCFG_PVLS_R3V1_F3V2
  *         @arg @ref MD_SYSCFG_PVLS_R3V3_F3V4
  *         @arg @ref MD_SYSCFG_PVLS_R3V5_F3V6
  *         @arg @ref MD_SYSCFG_PVLS_R3V7_F3V8
  *         @arg @ref MD_SYSCFG_PVLS_R3V9_F4V
  *         @arg @ref MD_SYSCFG_PVLS_R4V1_F4V2
  *         @arg @ref MD_SYSCFG_PVLS_R4V3_F4V4
  *         @arg @ref MD_SYSCFG_PVLS_R4V5_F4V6
  *         @arg @ref MD_SYSCFG_PVLS_R4V7_F4V8
  *         @arg @ref MD_SYSCFG_PVLS_R4V9_F5V
  */
__STATIC_INLINE uint32_t md_syscfg_get_pwcon_pvls(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->PWCON, SYSCFG_PWCON_PVLS_MSK)>>SYSCFG_PWCON_PVLS_POSS);
}

/**
  * @brief  Clear Wake Flag enable
  * @param  syscfg SYSCFG Instance
  * @retval None
  */
__STATIC_INLINE void md_syscfg_enable_wkcon_wkclr(SYSCFG_TypeDef *syscfg)
{
  SET_BIT(syscfg->WKCON, SYSCFG_WKCON_WKCLR_MSK);
}
/**
  * @brief  Set Low Power Level Select
  * @param  syscfg SYSCFG Instance
  * @param  lpls The parameter can be one of the following values:
  *         @arg @ref MD_SYSCFG_LPLS_LV0
  *         @arg @ref MD_SYSCFG_LPLS_LV1
  *         @arg @ref MD_SYSCFG_LPLS_LV2
  *         @arg @ref MD_SYSCFG_LPLS_LV3
  *         @arg @ref MD_SYSCFG_LPLS_LV4
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_wkcon_lpls(SYSCFG_TypeDef *syscfg, uint32_t lpls)
{
  MODIFY_REG(syscfg->WKCON, SYSCFG_WKCON_LPLS_MSK, (lpls<<SYSCFG_WKCON_LPLS_POSS));
}
/**
  * @brief  Get Low Power Level Select
  * @param  syscfg SYSCFG Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_SYSCFG_LPLS_LV0
  *         @arg @ref MD_SYSCFG_LPLS_LV1
  *         @arg @ref MD_SYSCFG_LPLS_LV2
  *         @arg @ref MD_SYSCFG_LPLS_LV3
  *         @arg @ref MD_SYSCFG_LPLS_LV4
  */
__STATIC_INLINE uint32_t md_syscfg_get_wkcon_lpls(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->WKCON, SYSCFG_WKCON_LPLS_MSK)>>SYSCFG_WKCON_LPLS_POSS);
}
/**
  * @brief  Set WKUPx pin edge sensitive type select
  * @note   0 : Falling Edge-sensitive (default)
  *         1 : Rising Edge-sensitive
  * @param  syscfg SYSCFG Instance
  * @param  wkeg This parameter can be one of the following values:
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_NRST
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_PVD
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_CMP0
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_RTC
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_PIN7
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_PIN6
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_PIN5
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_PIN4
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_PIN3
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_PIN2
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_PIN1
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_PIN0
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_wkcon_wkeg(SYSCFG_TypeDef *syscfg, uint32_t wkeg)
{
  MODIFY_REG(syscfg->WKCON, SYSCFG_WKCON_WKEG_MSK, (wkeg<<SYSCFG_WKCON_WKEG_POSS));
}
/**
  * @brief  Get WKCON pin0 edge sensitive type select
  * @param  syscfg SYSCFG Instance
  * @retval State of bit.
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_NRST
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_PVD
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_CMP0
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_RTC
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_PIN7
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_PIN6
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_PIN5
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_PIN4
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_PIN3
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_PIN2
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_PIN1
  *         @arg @ref MD_SYSCFG_WKCON_WKEG_PIN0
  */
__STATIC_INLINE uint32_t md_syscfg_get_wkcon_wkeg(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->WKCON, SYSCFG_WKCON_WKEG_MSK)>>SYSCFG_WKCON_WKEG_POSS);
}

/**
  * @brief  Set Enable WKUPx pin or wakeup event
  * @note   0: WKUPx pin is used for general purpose I/Os. An event on the WKUPx pin does not wakeup the device from Standby mode.
  *         1: WKUPx pin is used for wakeup from Standby mode.
  * @param  syscfg SYSCFG Instance
  * @param  wken This parameter can be one of the following values:
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_NRST
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_PVD
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_CMP0
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_RTC
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_PIN7
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_PIN6
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_PIN5
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_PIN4
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_PIN3
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_PIN2
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_PIN1
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_PIN0
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_wkcon_wken(SYSCFG_TypeDef *syscfg, uint32_t wken)
{
  MODIFY_REG(syscfg->WKCON, SYSCFG_WKCON_WKEN_MSK, (wken<<SYSCFG_WKCON_WKEN_POSS));
}
/**
  * @brief  Get WKCON pin0 or wakeup event
  * @param  syscfg SYSCFG Instance
  * @retval State of bit.
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_NRST
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_PVD
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_CMP0
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_RTC
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_PIN7
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_PIN6
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_PIN5
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_PIN4
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_PIN3
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_PIN2
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_PIN1
  *         @arg @ref MD_SYSCFG_WKCON_WKEN_PIN0
  */
__STATIC_INLINE uint32_t md_syscfg_get_wkcon_wken(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->WKCON, SYSCFG_WKCON_WKEN_MSK)>>SYSCFG_WKCON_WKEN_POSS);
}
/**
  * @brief  Set SYSCFG WCON register
  * @param  syscfg SYSCFG Instance
  * @param  uint32_t wcon
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_wkcon(SYSCFG_TypeDef *syscfg, uint32_t wcon)
{
  WRITE_REG(syscfg->WKCON, wcon);
}

/**
  * @brief  Get Wakeup Flag
  * @param  syscfg SYSCFG Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_syscfg_get_wkstat_flag(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->WKSTAT, SYSCFG_WKSTAT_FLAG_MSK)>>SYSCFG_WKSTAT_FLAG_POS);
}
/**
  * @brief  Get WKCON pin0 or wakeup event flag.
  * @note   When this bit was set to 1, a wakeup event occurs.
  * @param  syscfg SYSCFG Instance
  * @retval State of bit.
  *         @arg @ref MD_SYSCFG_WKSTAT_FG_NRST
  *         @arg @ref MD_SYSCFG_WKSTAT_FG_PVD
  *         @arg @ref MD_SYSCFG_WKSTAT_FG_CMP0
  *         @arg @ref MD_SYSCFG_WKSTAT_FG_RTC
  *         @arg @ref MD_SYSCFG_WKSTAT_FG_PIN7
  *         @arg @ref MD_SYSCFG_WKSTAT_FG_PIN6
  *         @arg @ref MD_SYSCFG_WKSTAT_FG_PIN5
  *         @arg @ref MD_SYSCFG_WKSTAT_FG_PIN4
  *         @arg @ref MD_SYSCFG_WKSTAT_FG_PIN3
  *         @arg @ref MD_SYSCFG_WKSTAT_FG_PIN2
  *         @arg @ref MD_SYSCFG_WKSTAT_FG_PIN1
  *         @arg @ref MD_SYSCFG_WKSTAT_FG_PIN0
  */
__STATIC_INLINE uint32_t md_syscfg_get_wkstat_fg(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->WKSTAT, SYSCFG_WKSTAT_FG_MSK)>>SYSCFG_WKSTAT_FG_POSS);
}


/**
  * @brief  Set Backup Register 0.
  * @note   This field was saved in the always on block, reset by power reset.
  * @param  syscfg SYSCFG Instance
  * @param  bkreg0 This parameter can be one of the following values:
  *         @arg Max Value 0xFFFFFFFF
  *         @arg Min Value 0
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_bkreg0(SYSCFG_TypeDef *syscfg, uint32_t bkreg0)
{
  MODIFY_REG(syscfg->BKREG0, SYSCFG_BKREG0_BKREG0_MSK, (bkreg0<<SYSCFG_BKREG0_BKREG0_POSS));
}
/**
  * @brief  Get Backup Register 0.
  * @param  syscfg SYSCFG Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xFFFFFFFF
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_syscfg_get_bkreg0(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->BKREG0, SYSCFG_BKREG0_BKREG0_MSK)>>SYSCFG_BKREG0_BKREG0_POSS);
}

/**
  * @brief  Set Backup Register 1.
  * @note   This field was saved in the always on block, reset by power reset.
  * @param  syscfg SYSCFG Instance
  * @param  bkreg1 This parameter can be one of the following values:
  *         @arg Max Value 0xFFFFFFFF
  *         @arg Min Value 0
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_bkreg1(SYSCFG_TypeDef *syscfg, uint32_t bkreg1)
{
  MODIFY_REG(syscfg->BKREG1, SYSCFG_BKREG1_BKREG1_MSK, (bkreg1<<SYSCFG_BKREG1_BKREG1_POSS));
}
/**
  * @brief  Get Backup Register 1.
  * @param  syscfg SYSCFG Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xFFFFFFFF
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_syscfg_get_bkreg1(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->BKREG1, SYSCFG_BKREG1_BKREG1_MSK)>>SYSCFG_BKREG1_BKREG1_POSS);
}

/**
  * @brief  Set Backup Register 2.
  * @note   This field was saved in the always on block, reset by power reset.
  * @param  syscfg SYSCFG Instance
  * @param  bkreg2 This parameter can be one of the following values:
  *         @arg Max Value 0xFFFFFFFF
  *         @arg Min Value 0
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_bkreg2(SYSCFG_TypeDef *syscfg, uint32_t bkreg2)
{
  MODIFY_REG(syscfg->BKREG2, SYSCFG_BKREG2_BKREG2_MSK, (bkreg2<<SYSCFG_BKREG2_BKREG2_POSS));
}
/**
  * @brief  Get Backup Register 2.
  * @param  syscfg SYSCFG Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xFFFFFFFF
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_syscfg_get_bkreg2(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->BKREG2, SYSCFG_BKREG2_BKREG2_MSK)>>SYSCFG_BKREG2_BKREG2_POSS);
}

/**
  * @brief  Set Backup Register 3.
  * @note   This field was saved in the always on block, reset by power reset.
  * @param  syscfg SYSCFG Instance
  * @param  bkreg3 This parameter can be one of the following values:
  *         @arg Max Value 0xFFFFFFFF
  *         @arg Min Value 0
  * @retval None
  */
__STATIC_INLINE void md_syscfg_set_bkreg3(SYSCFG_TypeDef *syscfg, uint32_t bkreg3)
{
  MODIFY_REG(syscfg->BKREG3, SYSCFG_BKREG3_BKREG3_MSK, (bkreg3<<SYSCFG_BKREG3_BKREG3_POSS));
}
/**
  * @brief  Get Backup Register 3.
  * @param  syscfg SYSCFG Instance
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xFFFFFFFF
  *         @arg Min Value 0
  */
__STATIC_INLINE uint32_t md_syscfg_get_bkreg3(SYSCFG_TypeDef *syscfg)
{
  return (READ_BIT(syscfg->BKREG3, SYSCFG_BKREG3_BKREG3_MSK)>>SYSCFG_BKREG3_BKREG3_POSS);
}

/**
  * @} MD_SYSCFG_Public_Macros
  */

/* Public functions -----------------------------------------------------------*/
/** @defgroup MD_SYSCFG_Public_Functions SYSCFG Public Functions
  * @{
  */

/** @defgroup MD_SYSCFG_PF_Basic_Configuration Basic Configuration
  * @{
  */

/**
  * @} MD_SYSCFG_PF_Basic_Configuration
  */

/** @defgroup MD_SYSCFG_PF_Data_Access Data Access
  * @{
  */

/**
  * @} MD_SYSCFG_PF_Data_Access
  */

/** @defgroup MD_SYSCFG_PF_Init Initialization and de-initialization functions
  * @{
  */

/**
  * @} MD_SYSCFG_PF_Init
  */

/**
  * @} MD_SYSCFG_Public_Functions
  */

#endif

/**
  * @} SYSCFG
  */

/**
  * @} Micro_Driver
  */


#ifdef __cplusplus
}

#endif

#endif

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
