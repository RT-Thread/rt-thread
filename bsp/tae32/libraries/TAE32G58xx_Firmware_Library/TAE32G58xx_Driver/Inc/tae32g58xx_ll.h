/**
  ******************************************************************************
  * @file    tae32g58xx_ll.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the LL
  *          module driver.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32G58XX_LL_H_
#define _TAE32G58XX_LL_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup TAE32G58xx_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup TAE32G58xx_LL_Exported_Constants TAE32G58xx LL Exported Constants
  * @brief    TAE32G58xx LL Exported Constants
  * @{
  */

/**
  * @brief TAE32G58xx LL Driver version number V1.3.1
  */
#define __TAE32G58xx_LL_VERSION_MAIN    (0x01U)     /*!< [31:24] main version       */
#define __TAE32G58xx_LL_VERSION_SUB1    (0x03U)     /*!< [23:16] sub1 version       */
#define __TAE32G58xx_LL_VERSION_SUB2    (0x01U)     /*!< [15:8]  sub2 version       */
#define __TAE32G58xx_LL_VERSION_RC      (0x00U)     /*!< [7:0]  release candidate   */
#define __TAE32G58xx_LL_VERSION         ((__TAE32G58xx_LL_VERSION_MAIN << 24) |\
                                         (__TAE32G58xx_LL_VERSION_SUB1 << 16) |\
                                         (__TAE32G58xx_LL_VERSION_SUB2 << 8 ) |\
                                         (__TAE32G58xx_LL_VERSION_RC))

/**
  * @brief TAE32G58xx SDK Stage String definition
  * @note  Value range: "Alpha" "Beta" "RC" "Trial" "Release"
  */
#define SDK_STAGE_STR                   "Release"


/**
  * @brief Internal High Speed oscillator (HSI) value.
  *        This value is used by the PLL module to compute the system frequency
  *        (when HSI is used as system clock source, directly or through the PLL).
  */
#define HSI_VALUE                       (__LL_SYSCTRL_RC8M_Real_Get(SYSCTRL) == 0xffffffUL ? 8000000U : __LL_SYSCTRL_RC8M_Real_Get(SYSCTRL))

/**
  * @brief Internal Low Speed oscillator (LSI) value.
  *        Defines the value of the Internal Low Speed oscillator in Hz.
  * @note  The real value may vary depending on the variations in voltage and temperature.
  */
#define LSI_VALUE                       (__LL_SYSCTRL_RC32K_Real_Get(SYSCTRL) == 0xffffUL ? 32000U : __LL_SYSCTRL_RC32K_Real_Get(SYSCTRL))


/**
  * @}
  */


/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_conf.h"


/* Exported Types ------------------------------------------------------------*/
/** @defgroup TAE32G58xx_LL_Exported_Types TAE32G58xx LL Exported Types
  * @brief    TAE32G58xx LL Exported Types
  * @{
  */

/**
  * LL Tick Freq Enum Type Definition
  */
typedef enum {
    LL_TICK_FREQ_10HZ    = 100U,                /*!< Tick Frequency 10Hz    */
    LL_TICK_FREQ_100HZ   = 10U,                 /*!< Tick Frequency 100Hz   */
    LL_TICK_FREQ_1KHZ    = 1U,                  /*!< Tick Frequency 1KHz    */
    LL_TICK_FREQ_DEFAULT = LL_TICK_FREQ_1KHZ,   /*!< Tick Frequency default */
} LL_TickFreqETypeDef;

/**
  * LL Extended Configuration Group Mask Enum Type Definition
  */
typedef enum {
    LL_EXT_CFG_GRP_MASK_ADC       = BIT(0),       /*!< Extended Configuration Group Mask ADC     */
    LL_EXT_CFG_GRP_MASK_CAN       = BIT(1),       /*!< Extended Configuration Group Mask CAN     */
    LL_EXT_CFG_GRP_MASK_CMP       = BIT(2),       /*!< Extended Configuration Group Mask CMP     */
    LL_EXT_CFG_GRP_MASK_CORDIC    = BIT(3),       /*!< Extended Configuration Group Mask CORDIC  */
    LL_EXT_CFG_GRP_MASK_DAC       = BIT(4),       /*!< Extended Configuration Group Mask DAC     */
    LL_EXT_CFG_GRP_MASK_DMA       = BIT(5),       /*!< Extended Configuration Group Mask DMA     */
    LL_EXT_CFG_GRP_MASK_EFLASH    = BIT(6),       /*!< Extended Configuration Group Mask EFLASH  */
    LL_EXT_CFG_GRP_MASK_GPIO      = BIT(7),       /*!< Extended Configuration Group Mask GPIO    */
    LL_EXT_CFG_GRP_MASK_HRPWM     = BIT(8),       /*!< Extended Configuration Group Mask HRPWM   */
    LL_EXT_CFG_GRP_MASK_I2C       = BIT(9),       /*!< Extended Configuration Group Mask I2C     */
    LL_EXT_CFG_GRP_MASK_IIR       = BIT(10),      /*!< Extended Configuration Group Mask IIR     */
    LL_EXT_CFG_GRP_MASK_IWDG      = BIT(11),      /*!< Extended Configuration Group Mask IWDG    */
    LL_EXT_CFG_GRP_MASK_PDM       = BIT(12),      /*!< Extended Configuration Group Mask PDM     */
    LL_EXT_CFG_GRP_MASK_QEI       = BIT(13),      /*!< Extended Configuration Group Mask QEI     */
    LL_EXT_CFG_GRP_MASK_RCU       = BIT(14),      /*!< Extended Configuration Group Mask RCU     */
    LL_EXT_CFG_GRP_MASK_SPI       = BIT(15),      /*!< Extended Configuration Group Mask SPI     */
    LL_EXT_CFG_GRP_MASK_SYSCTRL   = BIT(16),      /*!< Extended Configuration Group Mask SYSCTRL */
    LL_EXT_CFG_GRP_MASK_TMR       = BIT(17),      /*!< Extended Configuration Group Mask TMR     */
    LL_EXT_CFG_GRP_MASK_UART      = BIT(18),      /*!< Extended Configuration Group Mask UART    */
    LL_EXT_CFG_GRP_MASK_USB       = BIT(19),      /*!< Extended Configuration Group Mask USB     */
    LL_EXT_CFG_GRP_MASK_WWDG      = BIT(20),      /*!< Extended Configuration Group Mask WWDG    */
    LL_EXT_CFG_GRP_MASK_XIF       = BIT(21),      /*!< Extended Configuration Group Mask XIF     */

    LL_EXT_CFG_GRP_MASK_ALL       = 0xFFFFFFFFUL  /*!< Extended Configuration Group Mask ALL     */
} LL_ExtCfgEnGrpETypeDef;

/**
  * @brief Extended Configuration Enable Structure Definition
  */
typedef struct __LL_ExtCfgEnTypeDef {
    volatile uint32_t GrpMask;
    uint32_t Reserved[7];
} LL_ExtCfgEnTypeDef;

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup TAE32G58xx_LL_Exported_Functions
  * @{
  */

/** @addtogroup TAE32G58xx_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_Init(void);
LL_StatusETypeDef LL_DeInit(void);
void LL_MspInit(void);
void LL_MspDeInit(void);

LL_StatusETypeDef LL_InitTick(uint32_t TickPriority);
/**
  * @}
  */


/** @addtogroup TAE32G58xx_LL_Exported_Functions_Group2
  * @{
  */
void LL_IncTick(void);
uint32_t LL_GetTick(void);
uint32_t LL_GetTickPrio(void);
LL_StatusETypeDef LL_SetTickFreq(LL_TickFreqETypeDef Freq);
LL_TickFreqETypeDef LL_GetTickFreq(void);
void LL_SuspendTick(void);
void LL_ResumeTick(void);
void LL_Delay(uint32_t Delay);
uint32_t LL_GetHalVersion(void);
LL_StatusETypeDef LL_GetUID(uint32_t UID[]);
/**
  * @}
  */


/** @addtogroup TAE32G58xx_LL_Exported_Functions_Group3
  * @{
  */
void LL_ShowInfo(void);
void delay_ms(uint32_t ms);
void printf_array(void *ptr, uint32_t len);
/**
  * @}
  */

/** @addtogroup TAE32G58xx_LL_Exported_Functions_Group4
  * @{
  */
void LL_ExtCfgEnDeInit(void);
LL_StatusETypeDef LL_ExtCfgEnGrpSel(LL_ExtCfgEnGrpETypeDef grp, bool set);
bool LL_IsExtCfgEnGrp(LL_ExtCfgEnGrpETypeDef grp);
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
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

