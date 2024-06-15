/**
  ******************************************************************************
  * @file    stm32h7rsxx_ll_system.h
  * @author  MCD Application Team
  * @brief   Header file of SYSTEM LL module.
  *
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
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
    The LL SYSTEM driver contains a set of generic APIs that can be
    used by user:
      (+) Some of the FLASH features need to be handled in the SYSTEM file.
      (+) Access to DBGCMU registers
      (+) Access to SBS registers
      (+) Access to VREFBUF registers

  @endverbatim
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7RSxx_LL_SYSTEM_H
#define STM32H7RSxx_LL_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx.h"

/** @addtogroup STM32H7RSxx_LL_Driver
  * @{
  */

#if defined (FLASH) || defined (SBS) || defined (DBGMCU) || defined (VREFBUF)

/** @defgroup SYSTEM_LL SYSTEM
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Private_Constants SYSTEM Private Constants
  * @{
  */
#define LL_SBS_REGISTER_PINPOS_SHFT   16U                                 /*!< Define used to shift pin position in EXTICR register */
#define LL_SBS_HDPL_INCREMENT_VALUE   0x6AU                               /*!< Define used for the HDPL increment */
#define LL_SBS_DBG_UNLOCK             (0xB4U << SBS_DBGCR_DBG_UNLOCK_Pos) /*!< Define used to unlock debug */
#define LL_SBS_ACCESS_PORT_UNLOCK     0xB4U                               /*!< Define used to unlock access port */
#define LL_SBS_DBG_CONFIG_LOCK        0xC3U                               /*!< Define used to lock debug configuration */
#define LL_SBS_DBG_CONFIG_UNLOCK      0xB4U                               /*!< Define used to unlock debug configuration */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Constants SYSTEM Exported Constants
  * @{
  */

/** @defgroup SYSTEM_LL_EC_SBS_HDPL SBS hide protection level
  * @{
  */
#define LL_SBS_HDPL0                  0xB4U /*!< Hide protection level 0 */
#define LL_SBS_HDPL1                  0x51U /*!< Hide protection level 1 */
#define LL_SBS_HDPL2                  0x8AU /*!< Hide protection level 2 */
#define LL_SBS_HDPL3                  0x6FU /*!< Hide protection level 3 */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_SBS_AXISRAM_WS SBS AXISRAM wait state number (when ECC=0)
  * @{
  */
#define LL_SBS_AXISRAM_NO_WS          0U                    /*!< No wait state added when accessing AXISRAM */
#define LL_SBS_AXISRAM_ONE_WS         SBS_PMCR_AXISRAM_WS   /*!< One wait state added when accessing AXISRAM */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_SBS_ETH_PHYSEL SBS Ethernet PHY interface selection
  * @{
  */
#define LL_SBS_ETH_PHYSEL_GMII_MII    0U                    /*!< GMII or MII interface */
#define LL_SBS_ETH_PHYSEL_RMII        SBS_PMCR_ETH_PHYSEL_2 /*!< RMII interface */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_SBS_BOOSTVDDSEL SBS Booster Vdd selection
  * @{
  */
#define LL_SBS_BOOSTVDDSEL_VDDA       0U                   /*!< Vdda selected as analog switch booster voltage supply */
#define LL_SBS_BOOSTVDDSEL_VDD        SBS_PMCR_BOOSTVDDSEL /*!< Vdd selected as analog switch booster voltage supply */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_SBS_XSPI2_COMP_CODESEL SBS XSPI2 compensation cell code selection
  * @{
  */
#define LL_SBS_XSPI2_CODE_CELL        0U                           /*!< Code applied to compensation cell from cell */
#define LL_SBS_XSPI2_CODE_REG         SBS_CCCSR_XSPI2_COMP_CODESEL /*!< Code applied to compensation cell from register */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_SBS_XSPI1_COMP_CODESEL SBS XSPI1 compensation cell code selection
  * @{
  */
#define LL_SBS_XSPI1_CODE_CELL        0U                           /*!< Code applied to compensation cell from cell */
#define LL_SBS_XSPI1_CODE_REG         SBS_CCCSR_XSPI1_COMP_CODESEL /*!< Code applied to compensation cell from register */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_SBS_COMP_CODESEL SBS I/O compensation cell code selection
  * @{
  */
#define LL_SBS_IO_CODE_CELL           0U                     /*!< Code applied to compensation cell from cell */
#define LL_SBS_IO_CODE_REG            SBS_CCCSR_COMP_CODESEL /*!< Code applied to compensation cell from register */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_SBS_TIMBREAK SBS break lockup input timer peripherals
  * @{
  */
#define LL_SBS_TIMBREAK_PVD           SBS_BKLOCKR_PVD_BL      /*!< Connect the PVD output with TIM1/15/16/17 break input                                 */
#define LL_SBS_TIMBREAK_FLASHECC      SBS_BKLOCKR_FLASHECC_BL /*!< Connect the Flash ECC double error detection flag with TIM1/15/16/17 break input      */
#define LL_SBS_TIMBREAK_CM7LCKUP      SBS_BKLOCKR_CM7LCKUP_BL /*!< Connect the Cortex M7 lockup output with TIM1/15/16/17 break input                    */
#define LL_SBS_TIMBREAK_BKRAMECC      SBS_BKLOCKR_BKRAMECC_BL /*!< Connect the Backup RAM ECC double error detection flag with TIM1/15/16/17 break input */
#define LL_SBS_TIMBREAK_DTCMECC       SBS_BKLOCKR_DTCMECC_BL  /*!< Connect the DTCM ECC double error detection flag with TIM1/15/16/17 break input       */
#define LL_SBS_TIMBREAK_ITCMECC       SBS_BKLOCKR_ITCMECC_BL  /*!< Connect the ITCM ECC double error detection flag with TIM1/15/16/17 break input       */
#define LL_SBS_TIMBREAK_ARAM3ECC      SBS_BKLOCKR_ARAM3ECC_BL /*!< Connect the AXISRAM3 ECC double error detection flag with TIM1/15/16/17 break input    */
#define LL_SBS_TIMBREAK_ARAM1ECC      SBS_BKLOCKR_ARAM1ECC_BL /*!< Connect the AXISRAM1 ECC double error detection flag with TIM1/15/16/17 break input    */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_SBS_EXTI_PORT SBS EXTI PORT
  * @{
  */
#define LL_SBS_EXTI_PORTA             0U                                                   /*!< EXTI PORT A */
#define LL_SBS_EXTI_PORTB             SBS_EXTICR1_PC_EXTI0_0                               /*!< EXTI PORT B */
#define LL_SBS_EXTI_PORTC             SBS_EXTICR1_PC_EXTI0_1                               /*!< EXTI PORT C */
#define LL_SBS_EXTI_PORTD             (SBS_EXTICR1_PC_EXTI0_1 | SBS_EXTICR1_PC_EXTI0_0)    /*!< EXTI PORT D */
#define LL_SBS_EXTI_PORTE             SBS_EXTICR1_PC_EXTI0_2                               /*!< EXTI PORT E */
#define LL_SBS_EXTI_PORTF             (SBS_EXTICR1_PC_EXTI0_2 | SBS_EXTICR1_PC_EXTI0_0)    /*!< EXTI PORT F */
#define LL_SBS_EXTI_PORTG             (SBS_EXTICR1_PC_EXTI0_2 | SBS_EXTICR1_PC_EXTI0_1)    /*!< EXTI PORT G */
#define LL_SBS_EXTI_PORTH             (SBS_EXTICR1_PC_EXTI0_2 | SBS_EXTICR1_PC_EXTI0_1 | \
                                       SBS_EXTICR1_PC_EXTI0_0)                             /*!< EXTI PORT H */
#define LL_SBS_EXTI_PORTM             (SBS_EXTICR1_PC_EXTI0_3 | SBS_EXTICR1_PC_EXTI0_2)    /*!< EXTI PORT M */
#define LL_SBS_EXTI_PORTN             (SBS_EXTICR1_PC_EXTI0_3 | SBS_EXTICR1_PC_EXTI0_2 | \
                                       SBS_EXTICR1_PC_EXTI0_0)                             /*!< EXTI PORT N */
#define LL_SBS_EXTI_PORTO             (SBS_EXTICR1_PC_EXTI0_3 | SBS_EXTICR1_PC_EXTI0_2 | \
                                       SBS_EXTICR1_PC_EXTI0_1)                             /*!< EXTI PORT 0 */
#define LL_SBS_EXTI_PORTP             (SBS_EXTICR1_PC_EXTI0_3 | SBS_EXTICR1_PC_EXTI0_2 | \
                                       SBS_EXTICR1_PC_EXTI0_1 | SBS_EXTICR1_PC_EXTI0_0)    /*!< EXTI PORT P */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_SBS_EXTI_LINE SBS EXTI LINE
  * @{
  */
#define LL_SBS_EXTI_LINE0             ((0U  << LL_SBS_REGISTER_PINPOS_SHFT) | 0U)  /*!< EXTI_POSITION_0  | EXTICR[0] */
#define LL_SBS_EXTI_LINE1             ((4U  << LL_SBS_REGISTER_PINPOS_SHFT) | 0U)  /*!< EXTI_POSITION_8  | EXTICR[0] */
#define LL_SBS_EXTI_LINE2             ((8U  << LL_SBS_REGISTER_PINPOS_SHFT) | 0U)  /*!< EXTI_POSITION_16 | EXTICR[0] */
#define LL_SBS_EXTI_LINE3             ((12U << LL_SBS_REGISTER_PINPOS_SHFT) | 0U)  /*!< EXTI_POSITION_24 | EXTICR[0] */
#define LL_SBS_EXTI_LINE4             ((0U  << LL_SBS_REGISTER_PINPOS_SHFT) | 1U)  /*!< EXTI_POSITION_0  | EXTICR[1] */
#define LL_SBS_EXTI_LINE5             ((4U  << LL_SBS_REGISTER_PINPOS_SHFT) | 1U)  /*!< EXTI_POSITION_8  | EXTICR[1] */
#define LL_SBS_EXTI_LINE6             ((8U  << LL_SBS_REGISTER_PINPOS_SHFT) | 1U)  /*!< EXTI_POSITION_16 | EXTICR[1] */
#define LL_SBS_EXTI_LINE7             ((12U << LL_SBS_REGISTER_PINPOS_SHFT) | 1U)  /*!< EXTI_POSITION_24 | EXTICR[1] */
#define LL_SBS_EXTI_LINE8             ((0U  << LL_SBS_REGISTER_PINPOS_SHFT) | 2U)  /*!< EXTI_POSITION_0  | EXTICR[2] */
#define LL_SBS_EXTI_LINE9             ((4U  << LL_SBS_REGISTER_PINPOS_SHFT) | 2U)  /*!< EXTI_POSITION_8  | EXTICR[2] */
#define LL_SBS_EXTI_LINE10            ((8U  << LL_SBS_REGISTER_PINPOS_SHFT) | 2U)  /*!< EXTI_POSITION_16 | EXTICR[2] */
#define LL_SBS_EXTI_LINE11            ((12U << LL_SBS_REGISTER_PINPOS_SHFT) | 2U)  /*!< EXTI_POSITION_24 | EXTICR[2] */
#define LL_SBS_EXTI_LINE12            ((0U  << LL_SBS_REGISTER_PINPOS_SHFT) | 3U)  /*!< EXTI_POSITION_0  | EXTICR[3] */
#define LL_SBS_EXTI_LINE13            ((4U  << LL_SBS_REGISTER_PINPOS_SHFT) | 3U)  /*!< EXTI_POSITION_8  | EXTICR[3] */
#define LL_SBS_EXTI_LINE14            ((8U  << LL_SBS_REGISTER_PINPOS_SHFT) | 3U)  /*!< EXTI_POSITION_16 | EXTICR[3] */
#define LL_SBS_EXTI_LINE15            ((12U << LL_SBS_REGISTER_PINPOS_SHFT) | 3U)  /*!< EXTI_POSITION_24 | EXTICR[3] */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_DBGMCU_DCRT DBGMCU Debug credential reset type
  * @{
  */
#define LL_DBGMCU_DCRT_SYSTEM         0U              /*!< System reset revoke the debug authentication credentials */
#define LL_DBGMCU_DCRT_POWER          DBGMCU_CR_DCRT  /*!< Power reset revoke the debug authentication credentials */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_DBGMCU_AHB5_STOP DBGMCU AHB5 GRP1 STOP
  * @{
  */
#define LL_DBGMCU_AHB5_GRP1_HPDMA0_STOP    DBGMCU_AHB5FZR_HPDMA_0   /*!< The counter clock of HPDMA0 is stopped when the core is halted*/
#define LL_DBGMCU_AHB5_GRP1_HPDMA1_STOP    DBGMCU_AHB5FZR_HPDMA_1   /*!< The counter clock of HPDMA1 is stopped when the core is halted*/
#define LL_DBGMCU_AHB5_GRP1_HPDMA2_STOP    DBGMCU_AHB5FZR_HPDMA_2   /*!< The counter clock of HPDMA2 is stopped when the core is halted*/
#define LL_DBGMCU_AHB5_GRP1_HPDMA3_STOP    DBGMCU_AHB5FZR_HPDMA_3   /*!< The counter clock of HPDMA3 is stopped when the core is halted*/
#define LL_DBGMCU_AHB5_GRP1_HPDMA4_STOP    DBGMCU_AHB5FZR_HPDMA_4   /*!< The counter clock of HPDMA4 is stopped when the core is halted*/
#define LL_DBGMCU_AHB5_GRP1_HPDMA5_STOP    DBGMCU_AHB5FZR_HPDMA_5   /*!< The counter clock of HPDMA5 is stopped when the core is halted*/
#define LL_DBGMCU_AHB5_GRP1_HPDMA6_STOP    DBGMCU_AHB5FZR_HPDMA_6   /*!< The counter clock of HPDMA6 is stopped when the core is halted*/
#define LL_DBGMCU_AHB5_GRP1_HPDMA7_STOP    DBGMCU_AHB5FZR_HPDMA_7   /*!< The counter clock of HPDMA7 is stopped when the core is halted*/
#define LL_DBGMCU_AHB5_GRP1_HPDMA8_STOP    DBGMCU_AHB5FZR_HPDMA_8   /*!< The counter clock of HPDMA8 is stopped when the core is halted*/
#define LL_DBGMCU_AHB5_GRP1_HPDMA9_STOP    DBGMCU_AHB5FZR_HPDMA_9   /*!< The counter clock of HPDMAM9 is stopped when the core is halted*/
#define LL_DBGMCU_AHB5_GRP1_HPDMA10_STOP   DBGMCU_AHB5FZR_HPDMA_10  /*!< The counter clock of HPDMAM10 is stopped when the core is halted*/
#define LL_DBGMCU_AHB5_GRP1_HPDMA11_STOP   DBGMCU_AHB5FZR_HPDMA_11  /*!< The counter clock of HPDMAM11 is stopped when the core is halted*/
#define LL_DBGMCU_AHB5_GRP1_HPDMA12_STOP   DBGMCU_AHB5FZR_HPDMA_12  /*!< The counter clock of HPDMAM12 is stopped when the core is halted*/
#define LL_DBGMCU_AHB5_GRP1_HPDMA13_STOP   DBGMCU_AHB5FZR_HPDMA_13  /*!< The counter clock of HPDMAM13 is stopped when the core is halted*/
#define LL_DBGMCU_AHB5_GRP1_HPDMA14_STOP   DBGMCU_AHB5FZR_HPDMA_14  /*!< The counter clock of HPDMAM14 is stopped when the core is halted*/
#define LL_DBGMCU_AHB5_GRP1_HPDMA15_STOP   DBGMCU_AHB5FZR_HPDMA_15  /*!< The counter clock of HPDMAM15 is stopped when the core is halted*/
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_DBGMCU_AHB1_STOP DBGMCU AHB1 GRP1 STOP
  * @{
  */
#define LL_DBGMCU_AHB1_GRP1_GPDMA0_STOP    DBGMCU_AHB1FZR_GPDMA_0   /*!< The counter clock of GPDMA0 is stopped when the core is halted*/
#define LL_DBGMCU_AHB1_GRP1_GPDMA1_STOP    DBGMCU_AHB1FZR_GPDMA_1   /*!< The counter clock of GPDMA1 is stopped when the core is halted*/
#define LL_DBGMCU_AHB1_GRP1_GPDMA2_STOP    DBGMCU_AHB1FZR_GPDMA_2   /*!< The counter clock of GPDMA2 is stopped when the core is halted*/
#define LL_DBGMCU_AHB1_GRP1_GPDMA3_STOP    DBGMCU_AHB1FZR_GPDMA_3   /*!< The counter clock of GPDMA3 is stopped when the core is halted*/
#define LL_DBGMCU_AHB1_GRP1_GPDMA4_STOP    DBGMCU_AHB1FZR_GPDMA_4   /*!< The counter clock of GPDMA4 is stopped when the core is halted*/
#define LL_DBGMCU_AHB1_GRP1_GPDMA5_STOP    DBGMCU_AHB1FZR_GPDMA_5   /*!< The counter clock of GPDMA5 is stopped when the core is halted*/
#define LL_DBGMCU_AHB1_GRP1_GPDMA6_STOP    DBGMCU_AHB1FZR_GPDMA_6   /*!< The counter clock of GPDMA6 is stopped when the core is halted*/
#define LL_DBGMCU_AHB1_GRP1_GPDMA7_STOP    DBGMCU_AHB1FZR_GPDMA_7   /*!< The counter clock of GPDMA7 is stopped when the core is halted*/
#define LL_DBGMCU_AHB1_GRP1_GPDMA8_STOP    DBGMCU_AHB1FZR_GPDMA_8   /*!< The counter clock of GPDMA8 is stopped when the core is halted*/
#define LL_DBGMCU_AHB1_GRP1_GPDMA9_STOP    DBGMCU_AHB1FZR_GPDMA_9   /*!< The counter clock of GPDMAM9 is stopped when the core is halted*/
#define LL_DBGMCU_AHB1_GRP1_GPDMA10_STOP   DBGMCU_AHB1FZR_GPDMA_10  /*!< The counter clock of GPDMAM10 is stopped when the core is halted*/
#define LL_DBGMCU_AHB1_GRP1_GPDMA11_STOP   DBGMCU_AHB1FZR_GPDMA_11  /*!< The counter clock of GPDMAM11 is stopped when the core is halted*/
#define LL_DBGMCU_AHB1_GRP1_GPDMA12_STOP   DBGMCU_AHB1FZR_GPDMA_12  /*!< The counter clock of GPDMAM12 is stopped when the core is halted*/
#define LL_DBGMCU_AHB1_GRP1_GPDMA13_STOP   DBGMCU_AHB1FZR_GPDMA_13  /*!< The counter clock of GPDMAM13 is stopped when the core is halted*/
#define LL_DBGMCU_AHB1_GRP1_GPDMA14_STOP   DBGMCU_AHB1FZR_GPDMA_14  /*!< The counter clock of GPDMAM14 is stopped when the core is halted*/
#define LL_DBGMCU_AHB1_GRP1_GPDMA15_STOP   DBGMCU_AHB1FZR_GPDMA_15  /*!< The counter clock of GPDMAM15 is stopped when the core is halted*/
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_DBGMCU_APB1_STOP DBGMCU APB1 GRP1 STOP
  * @{
  */
#define LL_DBGMCU_APB1_GRP1_TIM2_STOP      DBGMCU_APB1FZR_TIM2   /*!< The counter clock of TIM2 is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_TIM3_STOP      DBGMCU_APB1FZR_TIM3   /*!< The counter clock of TIM3 is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_TIM4_STOP      DBGMCU_APB1FZR_TIM4   /*!< The counter clock of TIM4 is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_TIM5_STOP      DBGMCU_APB1FZR_TIM5   /*!< The counter clock of TIM5 is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_TIM6_STOP      DBGMCU_APB1FZR_TIM6   /*!< The counter clock of TIM6 is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_TIM7_STOP      DBGMCU_APB1FZR_TIM7   /*!< The counter clock of TIM7 is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_TIM12_STOP     DBGMCU_APB1FZR_TIM12  /*!< The counter clock of TIM12 is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_TIM13_STOP     DBGMCU_APB1FZR_TIM13  /*!< The counter clock of TIM13 is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_TIM14_STOP     DBGMCU_APB1FZR_TIM14  /*!< The counter clock of TIM14 is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_LPTIM1_STOP    DBGMCU_APB1FZR_LPTIM1 /*!< The counter clock of LPTIM1 is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_WWDG_STOP      DBGMCU_APB1FZR_WWDG   /*!< The window watchdog counter clock is stopped when the core is halted*/
#define LL_DBGMCU_APB1_GRP1_I2C1_STOP      DBGMCU_APB1FZR_I2C1   /*!< The I2C1 SMBus timeout is frozen*/
#define LL_DBGMCU_APB1_GRP1_I2C2_STOP      DBGMCU_APB1FZR_I2C2   /*!< The I2C2 SMBus timeout is frozen*/
#define LL_DBGMCU_APB1_GRP1_I2C3_STOP      DBGMCU_APB1FZR_I2C3   /*!< The I2C3 SMBus timeout is frozen*/
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_DBGMCU_APB2_STOP DBGMCU APB2 GRP1 STOP
  * @{
  */
#define LL_DBGMCU_APB2_GRP1_TIM1_STOP      DBGMCU_APB2FZR_TIM1     /*!< The counter clock of TIM1 is stopped when the core is halted*/
#define LL_DBGMCU_APB2_GRP1_TIM9_STOP      DBGMCU_APB2FZR_TIM9     /*!< The counter clock of TIM9 is stopped when the core is halted*/
#define LL_DBGMCU_APB2_GRP1_TIM15_STOP     DBGMCU_APB2FZR_TIM15    /*!< The counter clock of TIM15 is stopped when the core is halted*/
#define LL_DBGMCU_APB2_GRP1_TIM16_STOP     DBGMCU_APB2FZR_TIM16    /*!< The counter clock of TIM16 is stopped when the core is halted*/
#define LL_DBGMCU_APB2_GRP1_TIM17_STOP     DBGMCU_APB2FZR_TIM17    /*!< The counter clock of TIM17 is stopped when the core is halted*/
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_DBGMCU_APB4_STOP DBGMCU APB4 GRP1 STOP
  * @{
  */
#define LL_DBGMCU_APB4_GRP1_LPTIM2_STOP    DBGMCU_APB4FZR_LPTIM2 /*!< The counter clock of LPTIM2 is stopped when the core is halted*/
#define LL_DBGMCU_APB4_GRP1_LPTIM3_STOP    DBGMCU_APB4FZR_LPTIM3 /*!< The counter clock of LPTIM2 is stopped when the core is halted*/
#define LL_DBGMCU_APB4_GRP1_LPTIM4_STOP    DBGMCU_APB4FZR_LPTIM4 /*!< The counter clock of LPTIM4 is stopped when the core is halted*/
#define LL_DBGMCU_APB4_GRP1_LPTIM5_STOP    DBGMCU_APB4FZR_LPTIM5 /*!< The counter clock of LPTIM5 is stopped when the core is halted*/
#define LL_DBGMCU_APB4_GRP1_IWDG_STOP      DBGMCU_APB4FZR_IWDG   /*!< The counter clock of IWDG is stopped when the core is halted*/
#define LL_DBGMCU_APB4_GRP1_RTC_STOP       DBGMCU_APB4FZR_RTC    /*!< The counter clock of RTC is stopped when the core is halted*/
/**
  * @}
  */


#if defined(VREFBUF)
/** @defgroup SYSTEM_LL_EC_VOLTAGE VREFBUF VOLTAGE
  * @{
  */
#define LL_VREFBUF_VOLTAGE_SCALE0          VREFBUF_CSR_VRS_OUT1   /*!< Voltage reference scale 0 (VREF_OUT1) */
#define LL_VREFBUF_VOLTAGE_SCALE1          VREFBUF_CSR_VRS_OUT2   /*!< Voltage reference scale 1 (VREF_OUT2) */
#define LL_VREFBUF_VOLTAGE_SCALE2          VREFBUF_CSR_VRS_OUT3   /*!< Voltage reference scale 2 (VREF_OUT3) */
#define LL_VREFBUF_VOLTAGE_SCALE3          VREFBUF_CSR_VRS_OUT4   /*!< Voltage reference scale 3 (VREF_OUT4) */
/**
  * @}
  */
#endif /* VREFBUF */

/** @defgroup SYSTEM_LL_EC_LATENCY FLASH LATENCY
  * @{
  */
#define LL_FLASH_LATENCY_0        0                                                                 /*!< FLASH Zero wait state      */
#define LL_FLASH_LATENCY_1        FLASH_ACR_LATENCY_0                                               /*!< FLASH One wait state       */
#define LL_FLASH_LATENCY_2        FLASH_ACR_LATENCY_1                                               /*!< FLASH Two wait states      */
#define LL_FLASH_LATENCY_3        (FLASH_ACR_LATENCY_1 | FLASH_ACR_LATENCY_0)                       /*!< FLASH Three wait states    */
#define LL_FLASH_LATENCY_4        FLASH_ACR_LATENCY_2                                               /*!< FLASH Four wait states     */
#define LL_FLASH_LATENCY_5        (FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_0)                       /*!< FLASH Five wait state      */
#define LL_FLASH_LATENCY_6        (FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_1)                       /*!< FLASH Six wait state       */
#define LL_FLASH_LATENCY_7        (FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_1 | FLASH_ACR_LATENCY_0) /*!< FLASH Seven wait states    */
#define LL_FLASH_LATENCY_8        FLASH_ACR_LATENCY_3                                               /*!< FLASH Eight wait states    */
#define LL_FLASH_LATENCY_9        (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_0)                       /*!< FLASH Nine wait states     */
#define LL_FLASH_LATENCY_10       (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_1)                       /*!< FLASH Ten wait state       */
#define LL_FLASH_LATENCY_11       (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_1 | FLASH_ACR_LATENCY_0) /*!< FLASH Eleven wait state    */
#define LL_FLASH_LATENCY_12       (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_2)                       /*!< FLASH Twelve wait states   */
#define LL_FLASH_LATENCY_13       (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_0) /*!< FLASH Thirteen wait states */
#define LL_FLASH_LATENCY_14       (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_1) /*!< FLASH Fourteen wait states */
#define LL_FLASH_LATENCY_15       FLASH_ACR_LATENCY                                                 /*!< FLASH Fifteen wait states  */
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

/** @defgroup SYSTEM_LL_EF_SBS SBS
  * @{
  */

/**
  * @brief  Get initial vector for Cortex-M7
  * @rmtoll SBS_BOOTSR INITVTOR      LL_SBS_GetBootAddress
  * @retval Returned value is the physical boot address used by the Cortex-M7 after reset
  */
__STATIC_INLINE uint32_t LL_SBS_GetBootAddress(void)
{
  return (uint32_t)(READ_BIT(SBS->BOOTSR, SBS_BOOTSR_INITVTOR));
}

/**
  * @brief  Increment hide protection level
  * @rmtoll SBS_HDPLCR INCR_HDPL     LL_SBS_IncrementHDPL
  * @retval None
  */
__STATIC_INLINE void LL_SBS_IncrementHDPL(void)
{
  MODIFY_REG(SBS->HDPLCR, SBS_HDPLCR_INCR_HDPL, LL_SBS_HDPL_INCREMENT_VALUE);
}

/**
  * @brief  Get current hide protection level
  * @rmtoll SBS_HDPLSR HDPL          LL_SBS_GetCurrentHDPL
  * @retval Returned value is the current hide protection level of the device:
  *         @arg @ref LL_SBS_HDPL0
  *         @arg @ref LL_SBS_HDPL1
  *         @arg @ref LL_SBS_HDPL2
  *         @arg @ref LL_SBS_HDPL3
  */
__STATIC_INLINE uint32_t LL_SBS_GetCurrentHDPL(void)
{
  return (uint32_t)(READ_BIT(SBS->HDPLSR, SBS_HDPLSR_HDPL));
}

/**
  * @brief  Set the authenticated debug hide protection level
  * @rmtoll SBS_DBGCR DBG_AUTH_HDPL     LL_SBS_SetAuthDbgHDPL
  * @param  Level This parameter can be one of the following values:
  *         @arg @ref LL_SBS_HDPL1
  *         @arg @ref LL_SBS_HDPL2
  *         @arg @ref LL_SBS_HDPL3
  * @retval None
  */
__STATIC_INLINE void LL_SBS_SetAuthDbgHDPL(uint32_t Level)
{
  MODIFY_REG(SBS->DBGCR, SBS_DBGCR_DBG_AUTH_HDPL, (Level << SBS_DBGCR_DBG_AUTH_HDPL_Pos));
}

/**
  * @brief  Get current hide protection level
  * @rmtoll SBS_DBGCR DBG_AUTH_HDPL     LL_SBS_GetAuthDbgHDPL
  * @retval Returned value is the hide protection level where the authenticated debug is opened:
  *         @arg @ref LL_SBS_HDPL1
  *         @arg @ref LL_SBS_HDPL2
  *         @arg @ref LL_SBS_HDPL3
  */
__STATIC_INLINE uint32_t LL_SBS_GetAuthDbgHDPL(void)
{
  return (uint32_t)(READ_BIT(SBS->DBGCR, SBS_DBGCR_DBG_AUTH_HDPL) >> SBS_DBGCR_DBG_AUTH_HDPL_Pos);
}

/**
  * @brief  Unlock the debug
  * @rmtoll SBS_DBGCR DBG_UNLOCK     LL_SBS_UnlockDebug
  * @retval None
  */
__STATIC_INLINE void LL_SBS_UnlockDebug(void)
{
  MODIFY_REG(SBS->DBGCR, SBS_DBGCR_DBG_UNLOCK, LL_SBS_DBG_UNLOCK);
}

/**
  * @brief  Check if the debug is unlocked
  * @rmtoll SBS_DBGCR DBG_UNLOCK     LL_SBS_IsUnlockedDebug
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsUnlockedDebug(void)
{
  return ((READ_BIT(SBS->DBGCR, SBS_DBGCR_DBG_UNLOCK) == LL_SBS_DBG_UNLOCK) ? 1UL : 0UL);
}

/**
  * @brief  Unlock the access port
  * @rmtoll SBS_DBGCR AP_UNLOCK     LL_SBS_UnlockAccessPort
  * @retval None
  */
__STATIC_INLINE void LL_SBS_UnlockAccessPort(void)
{
  MODIFY_REG(SBS->DBGCR, SBS_DBGCR_AP_UNLOCK, LL_SBS_ACCESS_PORT_UNLOCK);
}

/**
  * @brief  Check if the access port is unlocked
  * @rmtoll SBS_DBGCR AP_UNLOCK     LL_SBS_IsUnlockedAccessPort
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsUnlockedAccessPort(void)
{
  return ((READ_BIT(SBS->DBGCR, SBS_DBGCR_AP_UNLOCK) == LL_SBS_ACCESS_PORT_UNLOCK) ? 1UL : 0UL);
}

/**
  * @brief  Lock the debug configuration
  * @rmtoll SBS_DBGLOCKR DBGCFG_LOCK     LL_SBS_LockDebugConfig
  * @retval None
  */
__STATIC_INLINE void LL_SBS_LockDebugConfig(void)
{
  MODIFY_REG(SBS->DBGLOCKR, SBS_DBGLOCKR_DBGCFG_LOCK, LL_SBS_DBG_CONFIG_LOCK);
}

/**
  * @brief  Unlock the debug configuration
  * @rmtoll SBS_DBGLOCKR DBGCFG_LOCK     LL_SBS_UnlockDebugConfig
  * @retval None
  */
__STATIC_INLINE void LL_SBS_UnlockDebugConfig(void)
{
  MODIFY_REG(SBS->DBGLOCKR, SBS_DBGLOCKR_DBGCFG_LOCK, LL_SBS_DBG_CONFIG_UNLOCK);
}

/**
  * @brief  Check if the debug configuration is unlocked
  * @rmtoll SBS_DBGLOCKR DBGCFG_LOCK     LL_SBS_IsUnlockedDebugConfig
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsUnlockedDebugConfig(void)
{
  return ((READ_BIT(SBS->DBGLOCKR, SBS_DBGLOCKR_DBGCFG_LOCK) == LL_SBS_DBG_CONFIG_UNLOCK) ? 1UL : 0UL);
}

/**
  * @brief  Set the command to be passed to RSS
  * @rmtoll SBS_RSSCMDR RSSCMD     LL_SBS_SetRSSCmd
  * @param  Command This parameter can have a value between 0 and 0xFFFF
  * @retval None
  */
__STATIC_INLINE void LL_SBS_SetRSSCmd(uint32_t Command)
{
  MODIFY_REG(SBS->RSSCMDR, SBS_RSSCMDR_RSSCMD, Command);
}

/**
  * @brief  Get the command which will be passed to RSS
  * @rmtoll SBS_RSSCMDR RSSCMD     LL_SBS_GetRSSCmd
  * @retval Returned value is the command which will be passed to RSS (value between 0 and 0xFFFF)
  */
__STATIC_INLINE uint32_t LL_SBS_GetRSSCmd(void)
{
  return (uint32_t)(READ_BIT(SBS->RSSCMDR, SBS_RSSCMDR_RSSCMD));
}

/**
  * @brief  Set the number of AXISRAM wait state (when ECC=0)
  * @rmtoll SBS_PMCR AXISRAM_WS     LL_SBS_SetAXISRAMWaitState
  * @param  WaitState This parameter can be one of the following values:
  *         @arg @ref LL_SBS_AXISRAM_NO_WS
  *         @arg @ref LL_SBS_AXISRAM_ONE_WS
  * @retval None
  */
__STATIC_INLINE void LL_SBS_SetAXISRAMWaitState(uint32_t WaitState)
{
  MODIFY_REG(SBS->PMCR, SBS_PMCR_AXISRAM_WS, WaitState);
}

/**
  * @brief  Get the number of AXISRAM wait state (when ECC=0)
  * @rmtoll SBS_PMCR AXISRAM_WS     LL_SBS_GetAXISRAMWaitState
  * @retval Returned value is the number of wait state when accessing AXISRAM:
  *         @arg @ref LL_SBS_AXISRAM_NO_WS
  *         @arg @ref LL_SBS_AXISRAM_ONE_WS
  */
__STATIC_INLINE uint32_t LL_SBS_GetAXISRAMWaitState(void)
{
  return (uint32_t)(READ_BIT(SBS->PMCR, SBS_PMCR_AXISRAM_WS));
}

/**
  * @brief  Configure the Ethernet PHY interface
  * @rmtoll SBS_PMCR ETH_PHYSEL     LL_SBS_SetEthernetPhy
  * @param  Interface This parameter can be one of the following values:
  *         @arg @ref LL_SBS_ETH_PHYSEL_GMII_MII
  *         @arg @ref LL_SBS_ETH_PHYSEL_RMII
  * @retval None
  */
__STATIC_INLINE void LL_SBS_SetEthernetPhy(uint32_t Interface)
{
  MODIFY_REG(SBS->PMCR, SBS_PMCR_ETH_PHYSEL, Interface);
}

/**
  * @brief  Get the selected Ethernet PHY interface
  * @rmtoll SBS_PMCR ETH_PHYSEL     LL_SBS_GetEthernetPhy
  * @retval Returned value is the selected Ethernet PHY interface:
  *         @arg @ref LL_SBS_ETH_PHYSEL_GMII_MII
  *         @arg @ref LL_SBS_ETH_PHYSEL_RMII
  */
__STATIC_INLINE uint32_t LL_SBS_GetEthernetPhy(void)
{
  return (uint32_t)(READ_BIT(SBS->PMCR, SBS_PMCR_ETH_PHYSEL));
}

/**
  * @brief  Configure the analog switch supply voltage for booster
  * @rmtoll SBS_PMCR BOOSTVDDSEL     LL_SBS_SetBoosterVoltage
  * @param  Voltage This parameter can be one of the following values:
  *         @arg @ref LL_SBS_BOOSTVDDSEL_VDDA
  *         @arg @ref LL_SBS_BOOSTVDDSEL_VDD
  * @retval None
  */
__STATIC_INLINE void LL_SBS_SetBoosterVoltage(uint32_t Voltage)
{
  MODIFY_REG(SBS->PMCR, SBS_PMCR_BOOSTVDDSEL, Voltage);
}

/**
  * @brief  Get the selected analog switch supply voltage for booster
  * @rmtoll SBS_PMCR BOOSTVDDSEL     LL_SBS_GetBoosterVoltage
  * @retval Returned value is the selected analog switch supply voltage:
  *         @arg @ref LL_SBS_BOOSTVDDSEL_VDDA
  *         @arg @ref LL_SBS_BOOSTVDDSEL_VDD
  */
__STATIC_INLINE uint32_t LL_SBS_GetBoosterVoltage(void)
{
  return (uint32_t)(READ_BIT(SBS->PMCR, SBS_PMCR_BOOSTVDDSEL));
}

/**
  * @brief  Enable the booster
  * @rmtoll SBS_PMCR BOOSTEN     LL_SBS_EnableBooster
  * @retval None
  */
__STATIC_INLINE void LL_SBS_EnableBooster(void)
{
  SET_BIT(SBS->PMCR, SBS_PMCR_BOOSTEN);
}

/**
  * @brief  Disable the booster
  * @rmtoll SBS_PMCR BOOSTEN     LL_SBS_DisableBooster
  * @retval None
  */
__STATIC_INLINE void LL_SBS_DisableBooster(void)
{
  CLEAR_BIT(SBS->PMCR, SBS_PMCR_BOOSTEN);
}

/**
  * @brief  Check if the booster is enabled
  * @rmtoll SBS_PMCR BOOSTEN     LL_SBS_IsEnabledBooster
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledBooster(void)
{
  return ((READ_BIT(SBS->PMCR, SBS_PMCR_BOOSTEN) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Enable Floating Point Unit Invalid operation Interrupt
  * @rmtoll SBS_FPUIMR FPU_IE_0      LL_SBS_EnableIT_FPU_IOC
  * @retval None
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_IOC(void)
{
  SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_0);
}

/**
  * @brief  Enable Floating Point Unit Divide-by-zero Interrupt
  * @rmtoll SBS_FPUIMR FPU_IE_1      LL_SBS_EnableIT_FPU_DZC
  * @retval None
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_DZC(void)
{
  SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_1);
}

/**
  * @brief  Enable Floating Point Unit Underflow Interrupt
  * @rmtoll SBS_FPUIMR FPU_IE_2      LL_SBS_EnableIT_FPU_UFC
  * @retval None
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_UFC(void)
{
  SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_2);
}

/**
  * @brief  Enable Floating Point Unit Overflow Interrupt
  * @rmtoll SBS_FPUIMR FPU_IE_3      LL_SBS_EnableIT_FPU_OFC
  * @retval None
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_OFC(void)
{
  SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_3);
}

/**
  * @brief  Enable Floating Point Unit Input denormal Interrupt
  * @rmtoll SBS_FPUIMR FPU_IE_4      LL_SBS_EnableIT_FPU_IDC
  * @retval None
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_IDC(void)
{
  SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_4);
}

/**
  * @brief  Enable Floating Point Unit Inexact Interrupt
  * @rmtoll SBS_FPUIMR FPU_IE_5      LL_SBS_EnableIT_FPU_IXC
  * @retval None
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_IXC(void)
{
  SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_5);
}

/**
  * @brief  Disable Floating Point Unit Invalid operation Interrupt
  * @rmtoll SBS_FPUIMR FPU_IE_0      LL_SBS_DisableIT_FPU_IOC
  * @retval None
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_IOC(void)
{
  CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_0);
}

/**
  * @brief  Disable Floating Point Unit Divide-by-zero Interrupt
  * @rmtoll SBS_FPUIMR FPU_IE_1      LL_SBS_DisableIT_FPU_DZC
  * @retval None
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_DZC(void)
{
  CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_1);
}

/**
  * @brief  Disable Floating Point Unit Underflow Interrupt
  * @rmtoll SBS_FPUIMR FPU_IE_2      LL_SBS_DisableIT_FPU_UFC
  * @retval None
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_UFC(void)
{
  CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_2);
}

/**
  * @brief  Disable Floating Point Unit Overflow Interrupt
  * @rmtoll SBS_FPUIMR FPU_IE_3      LL_SBS_DisableIT_FPU_OFC
  * @retval None
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_OFC(void)
{
  CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_3);
}

/**
  * @brief  Disable Floating Point Unit Input denormal Interrupt
  * @rmtoll SBS_FPUIMR FPU_IE_4      LL_SBS_DisableIT_FPU_IDC
  * @retval None
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_IDC(void)
{
  CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_4);
}

/**
  * @brief  Disable Floating Point Unit Inexact Interrupt
  * @rmtoll SBS_FPUIMR FPU_IE_5      LL_SBS_DisableIT_FPU_IXC
  * @retval None
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_IXC(void)
{
  CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_5);
}

/**
  * @brief  Check if Floating Point Unit Invalid operation Interrupt source is enabled or disabled.
  * @rmtoll SBS_FPUIMR FPU_IE_0      LL_SBS_IsEnabledIT_FPU_IOC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_IOC(void)
{
  return ((READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_0) == SBS_FPUIMR_FPU_IE_0) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Divide-by-zero Interrupt source is enabled or disabled.
  * @rmtoll SBS_FPUIMR FPU_IE_1      LL_SBS_IsEnabledIT_FPU_DZC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_DZC(void)
{
  return ((READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_1) == SBS_FPUIMR_FPU_IE_1) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Underflow Interrupt source is enabled or disabled.
  * @rmtoll SBS_FPUIMR FPU_IE_2      LL_SBS_IsEnabledIT_FPU_UFC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_UFC(void)
{
  return ((READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_2) == SBS_FPUIMR_FPU_IE_2) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Overflow Interrupt source is enabled or disabled.
  * @rmtoll SBS_FPUIMR FPU_IE_3      LL_SBS_IsEnabledIT_FPU_OFC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_OFC(void)
{
  return ((READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_3) == SBS_FPUIMR_FPU_IE_3) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Input denormal Interrupt source is enabled or disabled.
  * @rmtoll SBS_FPUIMR FPU_IE_4      LL_SBS_IsEnabledIT_FPU_IDC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_IDC(void)
{
  return ((READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_4) == SBS_FPUIMR_FPU_IE_4) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Inexact Interrupt source is enabled or disabled.
  * @rmtoll SBS_FPUIMR FPU_IE_5      LL_SBS_IsEnabledIT_FPU_IXC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_IXC(void)
{
  return ((READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_5) == SBS_FPUIMR_FPU_IE_5) ? 1UL : 0UL);
}

/**
  * @brief  Check if the automatic erase of BKPRAM and PKARAM memories are done
  * @rmtoll SBS_MESR MEF     LL_SBS_IsDoneMemoryErase
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsDoneMemoryErase(void)
{
  return (READ_BIT(SBS->MESR, SBS_MESR_MEF));
}

/**
  * @brief  Enable the XSPI2 speed optimization
  * @rmtoll SBS_CCCSR XSPI2_IOHSLV     LL_SBS_EnableXSPI2SpeedOptim
  * @retval None
  */
__STATIC_INLINE void LL_SBS_EnableXSPI2SpeedOptim(void)
{
  SET_BIT(SBS->CCCSR, SBS_CCCSR_XSPI2_IOHSLV);
}

/**
  * @brief  Disable the XSPI2 speed optimization
  * @rmtoll SBS_CCCSR XSPI2_IOHSLV     LL_SBS_DisableXSPI2SpeedOptim
  * @retval None
  */
__STATIC_INLINE void LL_SBS_DisableXSPI2SpeedOptim(void)
{
  CLEAR_BIT(SBS->CCCSR, SBS_CCCSR_XSPI2_IOHSLV);
}

/**
  * @brief  Check if the XSPI2 speed optimization is enabled
  * @rmtoll SBS_CCCSR XSPI2_IOHSLV     LL_SBS_IsEnabledXSPI2SpeedOptim
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledXSPI2SpeedOptim(void)
{
  return ((READ_BIT(SBS->CCCSR, SBS_CCCSR_XSPI2_IOHSLV) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Enable the XSPI1 speed optimization
  * @rmtoll SBS_CCCSR XSPI1_IOHSLV     LL_SBS_EnableXSPI1SpeedOptim
  * @retval None
  */
__STATIC_INLINE void LL_SBS_EnableXSPI1SpeedOptim(void)
{
  SET_BIT(SBS->CCCSR, SBS_CCCSR_XSPI1_IOHSLV);
}

/**
  * @brief  Disable the XSPI1 speed optimization
  * @rmtoll SBS_CCCSR XSPI1_IOHSLV     LL_SBS_DisableXSPI1SpeedOptim
  * @retval None
  */
__STATIC_INLINE void LL_SBS_DisableXSPI1SpeedOptim(void)
{
  CLEAR_BIT(SBS->CCCSR, SBS_CCCSR_XSPI1_IOHSLV);
}

/**
  * @brief  Check if the XSPI1 speed optimization is enabled
  * @rmtoll SBS_CCCSR XSPI1_IOHSLV     LL_SBS_IsEnabledXSPI1SpeedOptim
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledXSPI1SpeedOptim(void)
{
  return ((READ_BIT(SBS->CCCSR, SBS_CCCSR_XSPI1_IOHSLV) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Enable the I/O speed optimization
  * @rmtoll SBS_CCCSR IOHSLV     LL_SBS_EnableIOSpeedOptim
  * @retval None
  */
__STATIC_INLINE void LL_SBS_EnableIOSpeedOptim(void)
{
  SET_BIT(SBS->CCCSR, SBS_CCCSR_IOHSLV);
}

/**
  * @brief  Disable the I/O speed optimization
  * @rmtoll SBS_CCCSR IOHSLV     LL_SBS_DisableIOSpeedOptim
  * @retval None
  */
__STATIC_INLINE void LL_SBS_DisableIOSpeedOptim(void)
{
  CLEAR_BIT(SBS->CCCSR, SBS_CCCSR_IOHSLV);
}

/**
  * @brief  Check if the I/O speed optimization is enabled
  * @rmtoll SBS_CCCSR IOHSLV     LL_SBS_IsEnabledIOSpeedOptim
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIOSpeedOptim(void)
{
  return ((READ_BIT(SBS->CCCSR, SBS_CCCSR_IOHSLV) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Check if the XSPI2 compensation cell is ready
  * @rmtoll SBS_CCCSR XSPI2_COMP_RDY     LL_SBS_IsReadyXSPI2CompCell
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsReadyXSPI2CompCell(void)
{
  return ((READ_BIT(SBS->CCCSR, SBS_CCCSR_XSPI2_COMP_RDY) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Check if the XSPI1 compensation cell is ready
  * @rmtoll SBS_CCCSR XSPI1_COMP_RDY     LL_SBS_IsReadyXSPI1CompCell
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsReadyXSPI1CompCell(void)
{
  return ((READ_BIT(SBS->CCCSR, SBS_CCCSR_XSPI1_COMP_RDY) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Check if the I/O compensation cell is ready
  * @rmtoll SBS_CCCSR COMP_RDY     LL_SBS_IsReadyIOCompCell
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsReadyIOCompCell(void)
{
  return ((READ_BIT(SBS->CCCSR, SBS_CCCSR_COMP_RDY) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Configure the code for the XSPI2 compensation cell
  * @rmtoll SBS_CCCSR XSPI2_COMP_CODESEL     LL_SBS_SetXSPI2CompCellCode
  * @param  Code This parameter can be one of the following values:
  *         @arg @ref LL_SBS_XSPI2_CODE_CELL
  *         @arg @ref LL_SBS_XSPI2_CODE_REG
  * @retval None
  */
__STATIC_INLINE void LL_SBS_SetXSPI2CompCellCode(uint32_t Code)
{
  MODIFY_REG(SBS->CCCSR, SBS_CCCSR_XSPI2_COMP_CODESEL, Code);
}

/**
  * @brief  Get the selected code for the XSPI2 compensation cell
  * @rmtoll SBS_CCCSR XSPI2_COMP_CODESEL     LL_SBS_GetXSPI2CompCellCode
  * @retval Returned value is the selected code for the XSPI2 compensation cell:
  *         @arg @ref LL_SBS_XSPI2_CODE_CELL
  *         @arg @ref LL_SBS_XSPI2_CODE_REG
  */
__STATIC_INLINE uint32_t LL_SBS_GetXSPI2CompCellCode(void)
{
  return (uint32_t)(READ_BIT(SBS->CCCSR, SBS_CCCSR_XSPI2_COMP_CODESEL));
}

/**
  * @brief  Enable the XSPI2 compensation cell
  * @rmtoll SBS_PMCR XSPI2_COMP_EN     LL_SBS_EnableXSPI2CompCell
  * @retval None
  */
__STATIC_INLINE void LL_SBS_EnableXSPI2CompCell(void)
{
  SET_BIT(SBS->CCCSR, SBS_CCCSR_XSPI2_COMP_EN);
}

/**
  * @brief  Disable the XSPI2 compensation cell
  * @rmtoll SBS_CCCSR XSPI2_COMP_EN     LL_SBS_DisableXSPI2CompCell
  * @retval None
  */
__STATIC_INLINE void LL_SBS_DisableXSPI2CompCell(void)
{
  CLEAR_BIT(SBS->CCCSR, SBS_CCCSR_XSPI2_COMP_EN);
}

/**
  * @brief  Check if the XSPI2 compensation cell is enabled
  * @rmtoll SBS_CCCSR XSPI2_COMP_EN     LL_SBS_IsEnabledXSPI2CompCell
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledXSPI2CompCell(void)
{
  return ((READ_BIT(SBS->CCCSR, SBS_CCCSR_XSPI2_COMP_EN) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Configure the code for the XSPI1 compensation cell
  * @rmtoll SBS_CCCSR XSPI1_COMP_CODESEL     LL_SBS_SetXSPI1CompCellCode
  * @param  Code This parameter can be one of the following values:
  *         @arg @ref LL_SBS_XSPI1_CODE_CELL
  *         @arg @ref LL_SBS_XSPI1_CODE_REG
  * @retval None
  */
__STATIC_INLINE void LL_SBS_SetXSPI1CompCellCode(uint32_t Code)
{
  MODIFY_REG(SBS->CCCSR, SBS_CCCSR_XSPI1_COMP_CODESEL, Code);
}

/**
  * @brief  Get the selected code for the XSPI2 compensation cell
  * @rmtoll SBS_CCCSR XSPI1_COMP_CODESEL     LL_SBS_GetXSPI1CompCellCode
  * @retval Returned value is the selected code for the XSPI1 compensation cell:
  *         @arg @ref LL_SBS_XSPI1_CODE_CELL
  *         @arg @ref LL_SBS_XSPI1_CODE_REG
  */
__STATIC_INLINE uint32_t LL_SBS_GetXSPI1CompCellCode(void)
{
  return (uint32_t)(READ_BIT(SBS->CCCSR, SBS_CCCSR_XSPI1_COMP_CODESEL));
}

/**
  * @brief  Enable the XSPI1 compensation cell
  * @rmtoll SBS_PMCR XSPI1_COMP_EN     LL_SBS_EnableXSPI1CompCell
  * @retval None
  */
__STATIC_INLINE void LL_SBS_EnableXSPI1CompCell(void)
{
  SET_BIT(SBS->CCCSR, SBS_CCCSR_XSPI1_COMP_EN);
}

/**
  * @brief  Disable the XSPI1 compensation cell
  * @rmtoll SBS_CCCSR XSPI1_COMP_EN     LL_SBS_DisableXSPI1CompCell
  * @retval None
  */
__STATIC_INLINE void LL_SBS_DisableXSPI1CompCell(void)
{
  CLEAR_BIT(SBS->CCCSR, SBS_CCCSR_XSPI1_COMP_EN);
}

/**
  * @brief  Check if the XSPI1 compensation cell is enabled
  * @rmtoll SBS_CCCSR XSPI1_COMP_EN     LL_SBS_IsEnabledXSPI1CompCell
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledXSPI1CompCell(void)
{
  return ((READ_BIT(SBS->CCCSR, SBS_CCCSR_XSPI1_COMP_EN) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Configure the code for the I/O compensation cell
  * @rmtoll SBS_CCCSR COMP_CODESEL     LL_SBS_SetIOCompCellCode
  * @param  Code This parameter can be one of the following values:
  *         @arg @ref LL_SBS_IO_CODE_CELL
  *         @arg @ref LL_SBS_IO_CODE_REG
  * @retval None
  */
__STATIC_INLINE void LL_SBS_SetIOCompCellCode(uint32_t Code)
{
  MODIFY_REG(SBS->CCCSR, SBS_CCCSR_COMP_CODESEL, Code);
}

/**
  * @brief  Get the selected code for the I/O compensation cell
  * @rmtoll SBS_CCCSR COMP_CODESEL     LL_SBS_GetIOCompCellCode
  * @retval Returned value is the selected code for the I/O compensation cell:
  *         @arg @ref LL_SBS_IO_CODE_CELL
  *         @arg @ref LL_SBS_IO_CODE_REG
  */
__STATIC_INLINE uint32_t LL_SBS_GetIOCompCellCode(void)
{
  return (uint32_t)(READ_BIT(SBS->CCCSR, SBS_CCCSR_COMP_CODESEL));
}

/**
  * @brief  Enable the I/O compensation cell
  * @rmtoll SBS_PMCR COMP_EN     LL_SBS_EnableIOCompCell
  * @retval None
  */
__STATIC_INLINE void LL_SBS_EnableIOCompCell(void)
{
  SET_BIT(SBS->CCCSR, SBS_CCCSR_COMP_EN);
}

/**
  * @brief  Disable the I/O compensation cell
  * @rmtoll SBS_CCCSR COMP_EN     LL_SBS_DisableIOCompCell
  * @retval None
  */
__STATIC_INLINE void LL_SBS_DisableIOCompCell(void)
{
  CLEAR_BIT(SBS->CCCSR, SBS_CCCSR_COMP_EN);
}

/**
  * @brief  Check if the I/O compensation cell is enabled
  * @rmtoll SBS_CCCSR COMP_EN     LL_SBS_IsEnabledIOCompCell
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIOCompCell(void)
{
  return ((READ_BIT(SBS->CCCSR, SBS_CCCSR_COMP_EN) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Get the XSPI2 PMOS compensation
  * @rmtoll SBS_CCVALR XSPI2_PSRC     LL_SBS_GetXSPI2PmosComp
  * @retval Returned value is the slew-rate compensation for XSPI2 PMOS transistors (value between 0 and 0xF)
  */
__STATIC_INLINE uint32_t LL_SBS_GetXSPI2PmosComp(void)
{
  return (uint32_t)((READ_BIT(SBS->CCVALR, SBS_CCVALR_XSPI2_PSRC)) >> SBS_CCVALR_XSPI2_PSRC_Pos);
}

/**
  * @brief  Get the XSPI2 NMOS compensation
  * @rmtoll SBS_CCVALR XSPI2_NSRC     LL_SBS_GetXSPI2NmosComp
  * @retval Returned value is the slew-rate compensation for XSPI2 NMOS transistors (value between 0 and 0xF)
  */
__STATIC_INLINE uint32_t LL_SBS_GetXSPI2NmosComp(void)
{
  return (uint32_t)((READ_BIT(SBS->CCVALR, SBS_CCVALR_XSPI2_NSRC)) >> SBS_CCVALR_XSPI2_NSRC_Pos);
}

/**
  * @brief  Get the XSPI1 PMOS compensation
  * @rmtoll SBS_CCVALR XSPI1_PSRC     LL_SBS_GetXSPI1PmosComp
  * @retval Returned value is the slew-rate compensation for XSPI1 PMOS transistors (value between 0 and 0xF)
  */
__STATIC_INLINE uint32_t LL_SBS_GetXSPI1PmosComp(void)
{
  return (uint32_t)((READ_BIT(SBS->CCVALR, SBS_CCVALR_XSPI1_PSRC)) >> SBS_CCVALR_XSPI1_PSRC_Pos);
}

/**
  * @brief  Get the XSPI NMOS compensation
  * @rmtoll SBS_CCVALR XSPI1_NSRC     LL_SBS_GetXSPI1NmosComp
  * @retval Returned value is the slew-rate compensation for XSPI1 NMOS transistors (value between 0 and 0xF)
  */
__STATIC_INLINE uint32_t LL_SBS_GetXSPI1NmosComp(void)
{
  return (uint32_t)((READ_BIT(SBS->CCVALR, SBS_CCVALR_XSPI1_NSRC)) >> SBS_CCVALR_XSPI1_NSRC_Pos);
}

/**
  * @brief  Get the I/O PMOS compensation
  * @rmtoll SBS_CCVALR PSRC     LL_SBS_GetIOPmosComp
  * @retval Returned value is the slew-rate compensation for I/O PMOS transistors (value between 0 and 0xF)
  */
__STATIC_INLINE uint32_t LL_SBS_GetIOPmosComp(void)
{
  return (uint32_t)((READ_BIT(SBS->CCVALR, SBS_CCVALR_PSRC)) >> SBS_CCVALR_PSRC_Pos);
}

/**
  * @brief  Get the I/O NMOS compensation
  * @rmtoll SBS_CCVALR NSRC     LL_SBS_GetIONmosComp
  * @retval Returned value is the slew-rate compensation for I/O NMOS transistors (value between 0 and 0xF)
  */
__STATIC_INLINE uint32_t LL_SBS_GetIONmosComp(void)
{
  return (uint32_t)(READ_BIT(SBS->CCVALR, SBS_CCVALR_NSRC));
}

/**
  * @brief  Set the XSPI2 software PMOS compensation
  * @rmtoll SBS_CCSWVALR XSPI2_SW_PSRC     LL_SBS_SetXSPI2SwPmosComp
  * @param  Compensation This parameter can have a value between 0 and 0xF
  * @retval None
  */
__STATIC_INLINE void LL_SBS_SetXSPI2SwPmosComp(uint32_t Compensation)
{
  MODIFY_REG(SBS->CCSWVALR, SBS_CCSWVALR_XSPI2_SW_PSRC, (Compensation << SBS_CCSWVALR_XSPI2_SW_PSRC_Pos));
}

/**
  * @brief  Get the XSPI2 PMOS compensation
  * @rmtoll SBS_CCSWVALR XSPI2_SW_PSRC     LL_SBS_GetXSPI2SwPmosComp
  * @retval Returned value is the slew-rate compensation for XSPI2 PMOS transistors (value between 0 and 0xF)
  */
__STATIC_INLINE uint32_t LL_SBS_GetXSPI2SwPmosComp(void)
{
  return (uint32_t)((READ_BIT(SBS->CCSWVALR, SBS_CCSWVALR_XSPI2_SW_PSRC)) >> SBS_CCSWVALR_XSPI2_SW_PSRC_Pos);
}

/**
  * @brief  Set the XSPI2 software NMOS compensation
  * @rmtoll SBS_CCSWVALR XSPI2_SW_NSRC     LL_SBS_SetXSPI2SwNmosComp
  * @param  Compensation This parameter can have a value between 0 and 0xF
  * @retval None
  */
__STATIC_INLINE void LL_SBS_SetXSPI2SwNmosComp(uint32_t Compensation)
{
  MODIFY_REG(SBS->CCSWVALR, SBS_CCSWVALR_XSPI2_SW_NSRC, (Compensation << SBS_CCSWVALR_XSPI2_SW_NSRC_Pos));
}

/**
  * @brief  Get the XSPI2 software NMOS compensation
  * @rmtoll SBS_CCSWVALR XSPI2_SW_NSRC     LL_SBS_GetXSPI2SwNmosComp
  * @retval Returned value is the slew-rate compensation for XSPI2 NMOS transistors (value between 0 and 0xF)
  */
__STATIC_INLINE uint32_t LL_SBS_GetXSPI2SwNmosComp(void)
{
  return (uint32_t)((READ_BIT(SBS->CCSWVALR, SBS_CCSWVALR_XSPI2_SW_NSRC)) >> SBS_CCSWVALR_XSPI2_SW_NSRC_Pos);
}

/**
  * @brief  Set the XSPI1 software PMOS compensation
  * @rmtoll SBS_CCSWVALR XSPI2_SW_PSRC     LL_SBS_SetXSPI1SwPmosComp
  * @param  Compensation This parameter can have a value between 0 and 0xF
  * @retval None
  */
__STATIC_INLINE void LL_SBS_SetXSPI1SwPmosComp(uint32_t Compensation)
{
  MODIFY_REG(SBS->CCSWVALR, SBS_CCSWVALR_XSPI1_SW_PSRC, (Compensation << SBS_CCSWVALR_XSPI1_SW_PSRC_Pos));
}

/**
  * @brief  Get the XSPI1 PMOS compensation
  * @rmtoll SBS_CCSWVALR XSPI1_SW_PSRC     LL_SBS_GetXSPI1SwPmosComp
  * @retval Returned value is the slew-rate compensation for XSPI1 PMOS transistors (value between 0 and 0xF)
  */
__STATIC_INLINE uint32_t LL_SBS_GetXSPI1SwPmosComp(void)
{
  return (uint32_t)((READ_BIT(SBS->CCSWVALR, SBS_CCSWVALR_XSPI1_SW_PSRC)) >> SBS_CCSWVALR_XSPI1_SW_PSRC_Pos);
}

/**
  * @brief  Set the XSPI1 software NMOS compensation
  * @rmtoll SBS_CCSWVALR XSPI1_SW_NSRC     LL_SBS_SetXSPI1SwNmosComp
  * @param  Compensation This parameter can have a value between 0 and 0xF
  * @retval None
  */
__STATIC_INLINE void LL_SBS_SetXSPI1SwNmosComp(uint32_t Compensation)
{
  MODIFY_REG(SBS->CCSWVALR, SBS_CCSWVALR_XSPI1_SW_NSRC, (Compensation << SBS_CCSWVALR_XSPI1_SW_NSRC_Pos));
}

/**
  * @brief  Get the XSPI1 software NMOS compensation
  * @rmtoll SBS_CCSWVALR XSPI1_SW_NSRC     LL_SBS_GetXSPI1SwNmosComp
  * @retval Returned value is the slew-rate compensation for XSPI1 NMOS transistors (value between 0 and 0xF)
  */
__STATIC_INLINE uint32_t LL_SBS_GetXSPI1SwNmosComp(void)
{
  return (uint32_t)((READ_BIT(SBS->CCSWVALR, SBS_CCSWVALR_XSPI1_SW_NSRC)) >> SBS_CCSWVALR_XSPI1_SW_NSRC_Pos);
}

/**
  * @brief  Set the I/O software PMOS compensation
  * @rmtoll SBS_CCSWVALR SW_PSRC     LL_SBS_SetIOSwPmosComp
  * @param  Compensation This parameter can have a value between 0 and 0xF
  * @retval None
  */
__STATIC_INLINE void LL_SBS_SetIOSwPmosComp(uint32_t Compensation)
{
  MODIFY_REG(SBS->CCSWVALR, SBS_CCSWVALR_SW_PSRC, (Compensation << SBS_CCSWVALR_SW_PSRC_Pos));
}

/**
  * @brief  Get the I/O PMOS compensation
  * @rmtoll SBS_CCSWVALR SW_PSRC     LL_SBS_GetIOSwPmosComp
  * @retval Returned value is the slew-rate compensation for I/O PMOS transistors (value between 0 and 0xF)
  */
__STATIC_INLINE uint32_t LL_SBS_GetIOSwPmosComp(void)
{
  return (uint32_t)((READ_BIT(SBS->CCSWVALR, SBS_CCSWVALR_SW_PSRC)) >> SBS_CCSWVALR_SW_PSRC_Pos);
}

/**
  * @brief  Set the I/O software NMOS compensation
  * @rmtoll SBS_CCSWVALR SW_NSRC     LL_SBS_SetIOSwNmosComp
  * @param  Compensation This parameter can have a value between 0 and 0xF
  * @retval None
  */
__STATIC_INLINE void LL_SBS_SetIOSwNmosComp(uint32_t Compensation)
{
  MODIFY_REG(SBS->CCSWVALR, SBS_CCSWVALR_SW_NSRC, (Compensation << SBS_CCSWVALR_SW_NSRC_Pos));
}

/**
  * @brief  Get the I/O software NMOS compensation
  * @rmtoll SBS_CCSWVALR SW_NSRC     LL_SBS_GetIOSwNmosComp
  * @retval Returned value is the slew-rate compensation for I/O NMOS transistors (value between 0 and 0xF)
  */
__STATIC_INLINE uint32_t LL_SBS_GetIOSwNmosComp(void)
{
  return (uint32_t)((READ_BIT(SBS->CCSWVALR, SBS_CCSWVALR_SW_NSRC)) >> SBS_CCSWVALR_SW_NSRC_Pos);
}

/**
  * @brief  Set connections to TIM1/15/16/17 Break inputs
  * @rmtoll SBS_BKLOCKR PVD_BL          LL_SBS_SetTIMBreakInputs\n
  *         SBS_BKLOCKR FLASHECC_BL     LL_SBS_SetTIMBreakInputs\n
  *         SBS_BKLOCKR CM7LCKUP_BL     LL_SBS_SetTIMBreakInputs\n
  *         SBS_BKLOCKR BKRAMECC_BL     LL_SBS_SetTIMBreakInputs\n
  *         SBS_BKLOCKR DTCMECC_BL      LL_SBS_SetTIMBreakInputs\n
  *         SBS_BKLOCKR ITCMECC_BL      LL_SBS_SetTIMBreakInputs\n
  *         SBS_BKLOCKR ARAM3ECC_BL     LL_SBS_SetTIMBreakInputs\n
  *         SBS_BKLOCKR ARAM1ECC_BL     LL_SBS_SetTIMBreakInputs
  * @param  Break This parameter can be a combination of the following values:
  *         @arg @ref LL_SBS_TIMBREAK_PVD
  *         @arg @ref LL_SBS_TIMBREAK_FLASHECC
  *         @arg @ref LL_SBS_TIMBREAK_CM7LCKUP
  *         @arg @ref LL_SBS_TIMBREAK_BKRAMECC
  *         @arg @ref LL_SBS_TIMBREAK_DTCMECC
  *         @arg @ref LL_SBS_TIMBREAK_ITCMECC
  *         @arg @ref LL_SBS_TIMBREAK_ARAM3ECC
  *         @arg @ref LL_SBS_TIMBREAK_ARAM1ECC
  * @retval None
  */
__STATIC_INLINE void LL_SBS_SetTIMBreakInputs(uint32_t Break)
{
  MODIFY_REG(SBS->BKLOCKR,
             (SBS_BKLOCKR_PVD_BL | SBS_BKLOCKR_FLASHECC_BL | SBS_BKLOCKR_CM7LCKUP_BL | SBS_BKLOCKR_BKRAMECC_BL | \
              SBS_BKLOCKR_DTCMECC_BL | SBS_BKLOCKR_ITCMECC_BL | SBS_BKLOCKR_ARAM3ECC_BL | SBS_BKLOCKR_ARAM1ECC_BL)
             , Break);
}

/**
  * @brief  Get connections to TIM1/15/16/17 Break inputs
  * @rmtoll SBS_BKLOCKR CLL           LL_SBS_GetTIMBreakInputs\n
  *         SBS_BKLOCKR SPL           LL_SBS_GetTIMBreakInputs\n
  *         SBS_BKLOCKR PVDL          LL_SBS_GetTIMBreakInputs\n
  *         SBS_BKLOCKR ECCL          LL_SBS_GetTIMBreakInputs
  * @retval Returned value can be can be a combination of the following values:
  *         @arg @ref LL_SBS_TIMBREAK_PVD
  *         @arg @ref LL_SBS_TIMBREAK_FLASHECC
  *         @arg @ref LL_SBS_TIMBREAK_CM7LCKUP
  *         @arg @ref LL_SBS_TIMBREAK_BKRAMECC
  *         @arg @ref LL_SBS_TIMBREAK_DTCMECC
  *         @arg @ref LL_SBS_TIMBREAK_ITCMECC
  *         @arg @ref LL_SBS_TIMBREAK_ARAM3ECC
  *         @arg @ref LL_SBS_TIMBREAK_ARAM1ECC
  */
__STATIC_INLINE uint32_t LL_SBS_GetTIMBreakInputs(void)
{
  return (uint32_t)(READ_BIT(SBS->BKLOCKR,
                             (SBS_BKLOCKR_PVD_BL | SBS_BKLOCKR_FLASHECC_BL | SBS_BKLOCKR_CM7LCKUP_BL | \
                              SBS_BKLOCKR_BKRAMECC_BL | SBS_BKLOCKR_DTCMECC_BL | SBS_BKLOCKR_ITCMECC_BL | \
                              SBS_BKLOCKR_ARAM3ECC_BL | SBS_BKLOCKR_ARAM1ECC_BL)));
}

/**
  * @brief  Configure source input for the EXTI external interrupt.
  * @rmtoll SBS_EXTICR1 EXTI0         LL_SBS_SetEXTISource\n
  *         SBS_EXTICR1 EXTI1         LL_SBS_SetEXTISource\n
  *         SBS_EXTICR1 EXTI2         LL_SBS_SetEXTISource\n
  *         SBS_EXTICR1 EXTI3         LL_SBS_SetEXTISource\n
  *         SBS_EXTICR2 EXTI4         LL_SBS_SetEXTISource\n
  *         SBS_EXTICR2 EXTI5         LL_SBS_SetEXTISource\n
  *         SBS_EXTICR2 EXTI6         LL_SBS_SetEXTISource\n
  *         SBS_EXTICR2 EXTI7         LL_SBS_SetEXTISource\n
  *         SBS_EXTICR3 EXTI8         LL_SBS_SetEXTISource\n
  *         SBS_EXTICR3 EXTI9         LL_SBS_SetEXTISource\n
  *         SBS_EXTICR3 EXTI10        LL_SBS_SetEXTISource\n
  *         SBS_EXTICR3 EXTI11        LL_SBS_SetEXTISource\n
  *         SBS_EXTICR4 EXTI12        LL_SBS_SetEXTISource\n
  *         SBS_EXTICR4 EXTI13        LL_SBS_SetEXTISource\n
  *         SBS_EXTICR4 EXTI14        LL_SBS_SetEXTISource\n
  *         SBS_EXTICR4 EXTI15        LL_SBS_SetEXTISource
  * @param  Port This parameter can be one of the following values:
  *         @arg @ref LL_SBS_EXTI_PORTA
  *         @arg @ref LL_SBS_EXTI_PORTB
  *         @arg @ref LL_SBS_EXTI_PORTC
  *         @arg @ref LL_SBS_EXTI_PORTD
  *         @arg @ref LL_SBS_EXTI_PORTE
  *         @arg @ref LL_SBS_EXTI_PORTF
  *         @arg @ref LL_SBS_EXTI_PORTG
  *         @arg @ref LL_SBS_EXTI_PORTH
  *         @arg @ref LL_SBS_EXTI_PORTM
  *         @arg @ref LL_SBS_EXTI_PORTN
  *         @arg @ref LL_SBS_EXTI_PORTO
  *         @arg @ref LL_SBS_EXTI_PORTP
  *
  *         (*) value not defined in all devices
  * @param  Line This parameter can be one of the following values:
  *         @arg @ref LL_SBS_EXTI_LINE0
  *         @arg @ref LL_SBS_EXTI_LINE1
  *         @arg @ref LL_SBS_EXTI_LINE2
  *         @arg @ref LL_SBS_EXTI_LINE3
  *         @arg @ref LL_SBS_EXTI_LINE4
  *         @arg @ref LL_SBS_EXTI_LINE5
  *         @arg @ref LL_SBS_EXTI_LINE6
  *         @arg @ref LL_SBS_EXTI_LINE7
  *         @arg @ref LL_SBS_EXTI_LINE8
  *         @arg @ref LL_SBS_EXTI_LINE9
  *         @arg @ref LL_SBS_EXTI_LINE10
  *         @arg @ref LL_SBS_EXTI_LINE11
  *         @arg @ref LL_SBS_EXTI_LINE12
  *         @arg @ref LL_SBS_EXTI_LINE13
  *         @arg @ref LL_SBS_EXTI_LINE14
  *         @arg @ref LL_SBS_EXTI_LINE15
  * @retval None
  */
__STATIC_INLINE void LL_SBS_SetEXTISource(uint32_t Port, uint32_t Line)
{
  MODIFY_REG(SBS->EXTICR[Line & 0x03U],
             SBS_EXTICR1_PC_EXTI0 << (Line >> LL_SBS_REGISTER_PINPOS_SHFT),
             Port << (Line >> LL_SBS_REGISTER_PINPOS_SHFT));
}

/**
  * @brief  Get the configured defined for specific EXTI Line
  * @rmtoll SBS_EXTICR1 EXTI0         LL_SBS_GetEXTISource\n
  *         SBS_EXTICR1 EXTI1         LL_SBS_GetEXTISource\n
  *         SBS_EXTICR1 EXTI2         LL_SBS_GetEXTISource\n
  *         SBS_EXTICR1 EXTI3         LL_SBS_GetEXTISource\n
  *         SBS_EXTICR2 EXTI4         LL_SBS_GetEXTISource\n
  *         SBS_EXTICR2 EXTI5         LL_SBS_GetEXTISource\n
  *         SBS_EXTICR2 EXTI6         LL_SBS_GetEXTISource\n
  *         SBS_EXTICR2 EXTI7         LL_SBS_GetEXTISource\n
  *         SBS_EXTICR3 EXTI8         LL_SBS_GetEXTISource\n
  *         SBS_EXTICR3 EXTI9         LL_SBS_GetEXTISource\n
  *         SBS_EXTICR3 EXTI10        LL_SBS_GetEXTISource\n
  *         SBS_EXTICR3 EXTI11        LL_SBS_GetEXTISource\n
  *         SBS_EXTICR4 EXTI12        LL_SBS_GetEXTISource\n
  *         SBS_EXTICR4 EXTI13        LL_SBS_GetEXTISource\n
  *         SBS_EXTICR4 EXTI14        LL_SBS_GetEXTISource\n
  *         SBS_EXTICR4 EXTI15        LL_SBS_GetEXTISource
  * @param  Line This parameter can be one of the following values:
  *         @arg @ref LL_SBS_EXTI_LINE0
  *         @arg @ref LL_SBS_EXTI_LINE1
  *         @arg @ref LL_SBS_EXTI_LINE2
  *         @arg @ref LL_SBS_EXTI_LINE3
  *         @arg @ref LL_SBS_EXTI_LINE4
  *         @arg @ref LL_SBS_EXTI_LINE5
  *         @arg @ref LL_SBS_EXTI_LINE6
  *         @arg @ref LL_SBS_EXTI_LINE7
  *         @arg @ref LL_SBS_EXTI_LINE8
  *         @arg @ref LL_SBS_EXTI_LINE9
  *         @arg @ref LL_SBS_EXTI_LINE10
  *         @arg @ref LL_SBS_EXTI_LINE11
  *         @arg @ref LL_SBS_EXTI_LINE12
  *         @arg @ref LL_SBS_EXTI_LINE13
  *         @arg @ref LL_SBS_EXTI_LINE14
  *         @arg @ref LL_SBS_EXTI_LINE15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SBS_EXTI_PORTA
  *         @arg @ref LL_SBS_EXTI_PORTB
  *         @arg @ref LL_SBS_EXTI_PORTC
  *         @arg @ref LL_SBS_EXTI_PORTD
  *         @arg @ref LL_SBS_EXTI_PORTE
  *         @arg @ref LL_SBS_EXTI_PORTF
  *         @arg @ref LL_SBS_EXTI_PORTG
  *         @arg @ref LL_SBS_EXTI_PORTH
  *         @arg @ref LL_SBS_EXTI_PORTM
  *         @arg @ref LL_SBS_EXTI_PORTN
  *         @arg @ref LL_SBS_EXTI_PORTO
  *         @arg @ref LL_SBS_EXTI_PORTP
  */
__STATIC_INLINE uint32_t LL_SBS_GetEXTISource(uint32_t Line)
{
  return (uint32_t)(READ_BIT(SBS->EXTICR[Line & 0x03U],
                             (SBS_EXTICR1_PC_EXTI0 << (Line >> LL_SBS_REGISTER_PINPOS_SHFT))) >> (Line >> LL_SBS_REGISTER_PINPOS_SHFT));
}

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
  * @brief  Enable the Debug Module during sleep mode
  * @rmtoll DBGMCU_CR    DBG_SLEEP      LL_DBGMCU_EnableDBGSleepMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGSleepMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Disable the Debug Module during sleep mode
  * @rmtoll DBGMCU_CR    DBG_SLEEP      LL_DBGMCU_DisableDBGSleepMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGSleepMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Indicate if the Debug Module during sleep mode is enabled
  * @rmtoll DBGMCU_CR    DBG_SLEEP      LL_DBGMCU_IsEnabledDBGSleepMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDBGSleepMode(void)
{
  return ((READ_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP) == (DBGMCU_CR_DBG_SLEEP)) ? 1UL : 0UL);
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
  * @brief  Indicate if the Debug Module during STOP mode is enabled
  * @rmtoll DBGMCU_CR    DBG_STOP      LL_DBGMCU_IsEnabledDBGStopMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDBGStopMode(void)
{
  return ((READ_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP) == (DBGMCU_CR_DBG_STOP)) ? 1UL : 0UL);
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
  * @brief  Indicate if the Debug Module during STANDBY mode is enabled
  * @rmtoll DBGMCU_CR    DBG_STANDBY   LL_DBGMCU_IsEnabledDBGStandbyMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDBGStandbyMode(void)
{
  return ((READ_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY) == (DBGMCU_CR_DBG_STANDBY)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the debug credentials reset type
  * @rmtoll DBGMCU_CR DCRT     LL_DBGMCU_SetDbgCredentialResetType
  * @param  Type This parameter can be one of the following values:
  *         @arg @ref LL_DBGMCU_DCRT_SYSTEM
  *         @arg @ref LL_DBGMCU_DCRT_POWER
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_SetDbgCredentialResetType(uint32_t Type)
{
  MODIFY_REG(DBGMCU->CR, DBGMCU_CR_DCRT, Type);
}

/**
  * @brief  Get the selected debug credentials reset type
  * @rmtoll DBGMCU_CR DCRT     LL_DBGMCU_GetDbgCredentialResetType
  * @retval Returned value is the debug credentials reset type:
  *         @arg @ref LL_DBGMCU_DCRT_SYSTEM
  *         @arg @ref LL_DBGMCU_DCRT_POWER
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetDbgCredentialResetType(void)
{
  return (uint32_t)(READ_BIT(DBGMCU->CR, DBGMCU_CR_DCRT));
}

/**
  * @brief  Enable the clock for Trace port
  * @rmtoll DBGMCU_CR    TRACECLKEN      LL_DBGMCU_EnableTraceClock
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableTraceClock(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_TRACECLKEN);
}

/**
  * @brief  Disable the clock for Trace port
  * @rmtoll DBGMCU_CR    TRACECLKEN      LL_DBGMCU_DisableTraceClock
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableTraceClock(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_TRACECLKEN);
}

/**
  * @brief  Indicate if the clock for Trace port is enabled
  * @rmtoll DBGMCU_CR    TRACE_EN      LL_DBGMCU_IsEnabledTraceClock
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledTraceClock(void)
{
  return ((READ_BIT(DBGMCU->CR, DBGMCU_CR_TRACECLKEN) == (DBGMCU_CR_TRACECLKEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the clock for debug port
  * @rmtoll DBGMCU_CR    D1DBGCKEN      LL_DBGMCU_EnableDebugClock
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDebugClock(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBGCKEN);
}

/**
  * @brief  Disable the clock for debug port
  * @rmtoll DBGMCU_CR    D1DBGCKEN      LL_DBGMCU_DisableDebugClock
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDebugClock(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBGCKEN);
}

/**
  * @brief  Indicate if the clock for debug port is enabled
  * @rmtoll DBGMCU_CR    D1DBGCKEN      LL_DBGMCU_IsEnabledDebugClock
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDebugClock(void)
{
  return ((READ_BIT(DBGMCU->CR, DBGMCU_CR_DBGCKEN) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Enable the external trigger output
  * @rmtoll DBGMCU_CR    TRGOEN      LL_DBGMCU_EnableTriggerOutput
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableTriggerOutput(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_TRGOEN);
}

/**
  * @brief  Disable the external trigger output
  * @rmtoll DBGMCU_CR    TRGOEN      LL_DBGMCU_DisableTriggerOutput
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableTriggerOutput(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_TRGOEN);
}

/**
  * @brief  Indicate if the external trigger output is enabled
  * @rmtoll DBGMCU_CR    TRGOEN      LL_DBGMCU_IsEnabledTriggerOutput
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledTriggerOutput(void)
{
  return ((READ_BIT(DBGMCU->CR, DBGMCU_CR_TRGOEN) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Freeze APB1 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB1FZR DBG_xxxx_STOP  LL_DBGMCU_APB1_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM4_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM5_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM6_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM7_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM12_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM13_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM14_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C3_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APB1FZR, Periphs);
}

/**
  * @brief  UnFreeze APB1 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB1FZR DBG_xxxx_STOP  LL_DBGMCU_APB1_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM4_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM5_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM6_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM7_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM12_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM13_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM14_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C3_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APB1FZR, Periphs);
}

/**
  * @brief  Freeze APB4 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB4FZR DBG_xxxx_STOP  LL_DBGMCU_APB4_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB4_GRP1_LPTIM2_STOP
  *         @arg @ref LL_DBGMCU_APB4_GRP1_LPTIM3_STOP
  *         @arg @ref LL_DBGMCU_APB4_GRP1_LPTIM4_STOP
  *         @arg @ref LL_DBGMCU_APB4_GRP1_LPTIM5_STOP
  *         @arg @ref LL_DBGMCU_APB4_GRP1_IWDG_STOP
  *         @arg @ref LL_DBGMCU_APB4_GRP1_RTC_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB4_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APB4FZR, Periphs);
}

/**
  * @brief  UnFreeze APB4 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB4FZR DBG_xxxx_STOP  LL_DBGMCU_APB4_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB4_GRP1_LPTIM2_STOP
  *         @arg @ref LL_DBGMCU_APB4_GRP1_LPTIM3_STOP
  *         @arg @ref LL_DBGMCU_APB4_GRP1_LPTIM4_STOP
  *         @arg @ref LL_DBGMCU_APB4_GRP1_LPTIM5_STOP
  *         @arg @ref LL_DBGMCU_APB4_GRP1_IWDG_STOP
  *         @arg @ref LL_DBGMCU_APB4_GRP1_RTC_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB4_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APB4FZR, Periphs);
}

/**
  * @brief  freeze APB2 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB2FZR DBG_xxxx_STOP  LL_DBGMCU_APB2_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM9_STOP
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
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM9_STOP
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
  * @brief  freeze AHB5 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_AHB5FZR DBG_xxxx_STOP  LL_DBGMCU_AHB5_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA0_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA1_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA2_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA3_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA4_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA5_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA6_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA7_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA8_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA9_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA10_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA11_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA12_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA13_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA14_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA15_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_AHB5_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->AHB5FZR, Periphs);
}

/**
  * @brief  Unfreeze AHB5 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_AHB5FZR DBG_xxxx_STOP  LL_DBGMCU_AHB5_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA0_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA1_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA2_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA3_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA4_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA5_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA6_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA7_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA8_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA9_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA10_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA11_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA12_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA13_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA14_STOP
  *         @arg @ref LL_DBGMCU_AHB5_GRP1_HPDMA15_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_AHB5_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->AHB5FZR, Periphs);
}

/**
  * @brief  freeze AHB1 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_AHB1FZR DBG_xxxx_STOP  LL_DBGMCU_AHB1_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA0_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA1_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA2_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA3_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA4_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA5_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA6_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA7_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA8_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA9_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA10_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA11_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA12_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA13_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA14_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA15_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_AHB1_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->AHB1FZR, Periphs);
}

/**
  * @brief  Unfreeze AHB1 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_AHB1FZR DBG_xxxx_STOP  LL_DBGMCU_AHB1_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA0_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA1_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA2_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA3_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA4_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA5_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA6_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA7_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA8_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA9_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA10_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA11_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA12_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA13_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA14_STOP
  *         @arg @ref LL_DBGMCU_AHB1_GRP1_GPDMA15_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->AHB1FZR, Periphs);
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
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE2
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE3
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
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE2
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE3
  */
__STATIC_INLINE uint32_t LL_VREFBUF_GetVoltageScaling(void)
{
  return (uint32_t)(READ_BIT(VREFBUF->CSR, VREFBUF_CSR_VRS));
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
  * @brief  Unlock the Flash
  * @rmtoll FLASH_KEYR    CUKEY       LL_FLASH_Unlock
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_Unlock(void)
{
  /* Unlock Flash */
  FLASH->KEYR = 0x45670123U;
  FLASH->KEYR = 0xCDEF89ABU;
}

/**
  * @brief  Lock the Flash
  * @rmtoll FLASH_CR    LOCK       LL_FLASH_Lock
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_Lock(void)
{
  /* Lock Flash */
  SET_BIT(FLASH->CR, FLASH_CR_LOCK);
}

/**
  * @brief  Check if Flash is locked
  * @rmtoll FLASH_CR    LOCK       LL_FLASH_IsLocked
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsLocked(void)
{
  return ((READ_BIT(FLASH->CR, FLASH_CR_LOCK) == FLASH_CR_LOCK) ? 1UL : 0UL);
}

/**
  * @brief  Unlock the Option Bytes update
  * @rmtoll FLASH_OPTKEYR    OCUKEY       LL_FLASH_OptionBytes_Unlock
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_OptionBytes_Unlock(void)
{
  /* Unlock Option Bytes */
  FLASH->OPTKEYR = 0x08192A3BU;
  FLASH->OPTKEYR = 0x4C5D6E7FU;
}

/**
  * @brief  Lock the Option Bytes update
  * @rmtoll FLASH_OPTCR    OPTLOCK       LL_FLASH_OptionBytes_Lock
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_OptionBytes_Lock(void)
{
  /* Lock option bytes */
  SET_BIT(FLASH->OPTCR, FLASH_OPTCR_OPTLOCK);
}

/**
  * @brief  Check if Option Bytes update is locked
  * @rmtoll FLASH_OPTCR    OPTLOCK       LL_FLASH_OptionBytes_IsLocked
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_OptionBytes_IsLocked(void)
{
  return ((READ_BIT(FLASH->OPTCR, FLASH_OPTCR_OPTLOCK) == FLASH_OPTCR_OPTLOCK) ? 1UL : 0UL);
}

/**
  * @brief  Enable Option Bytes programming
  * @rmtoll FLASH_OPTCR    PG_OPT       LL_FLASH_OptionBytes_EnableProg
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_OptionBytes_EnableProg(void)
{
  /* Set PG_OPT Bit */
  SET_BIT(FLASH->OPTCR, FLASH_OPTCR_PG_OPT);
}

/**
  * @brief  Disable Option Bytes programming
  * @rmtoll FLASH_OPTCR    PG_OPT       LL_FLASH_OptionBytes_DisableProg
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_OptionBytes_DisableProg(void)
{
  /* Clear PG_OPT Bit */
  CLEAR_BIT(FLASH->OPTCR, FLASH_OPTCR_PG_OPT);
}

/**
  * @brief  Check if Option Bytes programming is enabled
  * @rmtoll FLASH_OPTCR    PG_OPT       LL_FLASH_OptionBytes_IsEnabledProg
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_OptionBytes_IsEnabledProg(void)
{
  return ((READ_BIT(FLASH->OPTCR, FLASH_OPTCR_PG_OPT) == FLASH_OPTCR_PG_OPT) ? 1UL : 0UL);
}

/**
  * @brief  Check if operation pending
  * @rmtoll FLASH_SR    QW       LL_FLASH_IsPendingOperation
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsPendingOperation(void)
{
  return ((READ_BIT(FLASH->SR, FLASH_SR_QW) == FLASH_SR_QW) ? 1UL : 0UL);
}

/**
  * @brief  Enable the I2C in Flash User Option bytes
  * @rmtoll FLASH_OBW2SR    I2C_NI3C       LL_FLASH_OptionBytes_EnableI2C
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_OptionBytes_EnableI2C(void)
{
  /* Set I2C_N3C Bit */
  SET_BIT(FLASH->OBW2SRP, FLASH_OBW2SRP_I2C_NI3C);
}

/**
  * @brief  Enable the I3C in Flash User Option bytes
  * @rmtoll FLASH_OBW2SR    I2C_NI3C       LL_FLASH_OptionBytes_EnableI3C
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_OptionBytes_EnableI3C(void)
{
  /* Clear I2C_N3C Bit */
  CLEAR_BIT(FLASH->OBW2SRP, FLASH_OBW2SRP_I2C_NI3C);
}

/**
  * @brief  Check if I2C is enabled in Flash User Option Bytes
  * @rmtoll FLASH_OBW2SR    I2C_NI3C       LL_FLASH_OptionBytes_IsI2CEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_OptionBytes_IsI2CEnabled(void)
{
  return ((READ_BIT(FLASH->OBW2SR, FLASH_OBW2SR_I2C_NI3C) == FLASH_OBW2SR_I2C_NI3C) ? 1UL : 0UL);
}

/**
  * @brief  Check if I3C is enabled in Flash User Option Bytes
  * @rmtoll FLASH_OBW2SR    I2C_NI3C       LL_FLASH_OptionBytes_IsI3CEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_OptionBytes_IsI3CEnabled(void)
{
  return ((READ_BIT(FLASH->OBW2SR, FLASH_OBW2SR_I2C_NI3C) == 0U) ? 1UL : 0UL);
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

#endif /* defined (FLASH) || defined (SBS) || defined (DBGMCU) || defined (VREFBUF) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7RSxx_LL_SYSTEM_H */
