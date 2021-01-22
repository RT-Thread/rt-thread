/**
  ******************************************************************************
  * @file    md_ADC.h
  * @brief   ES32F0271 DAC Header File.
  *
  * @version V1.00.01
  * @date    01/14/2019
  * @author  Eastsoft AE Team
  * @note
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MD_DAC_H__
#define __MD_DAC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/
#include "es32f0271.h"
#include "reg_dac.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined DAC

/** @defgroup DAC DAC
  * @brief DAC micro driver
  * @{
  */

/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/
/* Public types ---------------------------------------------------------------*/
/* Public constants -----------------------------------------------------------*/
/* Public functions -----------------------------------------------------------*/

/** @defgroup MD_DAC_Public_Constants DAC Public Constants
  * @{
  */
  
/** @defgroup MD_DAC_CON DAC_CON Register
  * @{
  */

#define MD_ADC_CON_TSEL_SW               (0x00000000U<<DAC_CON_T_SEL_POSS)   /** @brief data DAC SW */
#define MD_ADC_CON_TSEL_BS16T1           (0x00000001U<<DAC_CON_T_SEL_POSS)   /** @brief data DAC BS16T1 */
#define MD_ADC_CON_TSEL_GP32C4T1         (0x00000003U<<DAC_CON_T_SEL_POSS)   /** @brief data DAC GP32C4T1 */
#define MD_ADC_CON_TSEL_GP16C4T1         (0x00000004U<<DAC_CON_T_SEL_POSS)   /** @brief data DAC GP16C4T1 */
#define MD_ADC_CON_TSEL_GP16C4T2         (0x00000005U<<DAC_CON_T_SEL_POSS)   /** @brief data DAC GP16C4T2 */
#define MD_ADC_CON_TSEL_GP16C4T3         (0x00000006U<<DAC_CON_T_SEL_POSS)   /** @brief data DAC GP16C4T3 */
#define MD_ADC_CON_TSEL_GP16C2T1         (0x00000007U<<DAC_CON_T_SEL_POSS)   /** @brief data DAC GP16C2T1 */
#define MD_ADC_CON_TSEL_GP16C2T2         (0x00000008U<<DAC_CON_T_SEL_POSS)   /** @brief data DAC GP16C2T2 */
#define MD_ADC_CON_TSEL_GP16C2T3         (0x00000009U<<DAC_CON_T_SEL_POSS)   /** @brief data DAC GP16C2T3 */
#define MD_ADC_CON_TSEL_GP16C2T4         (0x0000000AU<<DAC_CON_T_SEL_POSS)   /** @brief data DAC GP16C2T4 */
#define MD_ADC_CON_TSEL_AD16C4T1         (0x0000000BU<<DAC_CON_T_SEL_POSS)   /** @brief data DAC AD16C4T1 */
#define MD_ADC_CON_TSEL_GPIO             (0x0000000CU<<DAC_CON_T_SEL_POSS)   /** @brief data DAC GPIO */
#define MD_ADC_CON_TSEL_RTC              (0x0000000DU<<DAC_CON_T_SEL_POSS)   /** @brief data DAC RTC */
#define MD_ADC_CON_TSEL_CMP1             (0x0000000EU<<DAC_CON_T_SEL_POSS)   /** @brief data DAC CMP1 */
#define MD_ADC_CON_TSEL_CMP2             (0x0000000FU<<DAC_CON_T_SEL_POSS)   /** @brief data DAC CMP2 */

#define MD_ADC_CON_MAMP_1                (0x00000000U<<DAC_CON_MAMP_POSS)    /** @brief data DAC AMPLITUDE 1 */
#define MD_ADC_CON_MAMP_3                (0x00000001U<<DAC_CON_MAMP_POSS)    /** @brief data DAC AMPLITUDE 3 */
#define MD_ADC_CON_MAMP_7                (0x00000002U<<DAC_CON_MAMP_POSS)    /** @brief data DAC AMPLITUDE 7 */
#define MD_ADC_CON_MAMP_15               (0x00000003U<<DAC_CON_MAMP_POSS)    /** @brief data DAC AMPLITUDE 15 */
#define MD_ADC_CON_MAMP_31               (0x00000004U<<DAC_CON_MAMP_POSS)    /** @brief data DAC AMPLITUDE 31 */
#define MD_ADC_CON_MAMP_63               (0x00000005U<<DAC_CON_MAMP_POSS)    /** @brief data DAC AMPLITUDE 63 */
#define MD_ADC_CON_MAMP_127              (0x00000006U<<DAC_CON_MAMP_POSS)    /** @brief data DAC AMPLITUDE 127 */
#define MD_ADC_CON_MAMP_255              (0x00000007U<<DAC_CON_MAMP_POSS)    /** @brief data DAC AMPLITUDE 255 */
#define MD_ADC_CON_MAMP_511              (0x00000008U<<DAC_CON_MAMP_POSS)    /** @brief data DAC AMPLITUDE 511 */
#define MD_ADC_CON_MAMP_1023             (0x00000009U<<DAC_CON_MAMP_POSS)    /** @brief data DAC AMPLITUDE 1023 */
#define MD_ADC_CON_MAMP_2047             (0x0000000AU<<DAC_CON_MAMP_POSS)    /** @brief data DAC AMPLITUDE 2047 */
#define MD_ADC_CON_MAMP_4095             (0x0000000BU<<DAC_CON_MAMP_POSS)    /** @brief data DAC AMPLITUDE 4095 */

#define MD_ADC_CON_WAVE_DISABLE          (0x00000000U<<DAC_CON_WAVE_POSS)    /** @brief data DAC WAVE DISABLE */
#define MD_ADC_CON_WAVE_UP               (0x00000001U<<DAC_CON_WAVE_POSS)    /** @brief data DAC WAVE UP */
#define MD_ADC_CON_WAVE_DOWN             (0x00000002U<<DAC_CON_WAVE_POSS)    /** @brief data DAC WAVE DOWN */
#define MD_ADC_CON_WAVE_TRIANGLE         (0x00000003U<<DAC_CON_WAVE_POSS)    /** @brief data DAC WAVE TRIANGLE */

/**
  * @} MD_DAC_CON DAC_CON Register
  */

/**
  * @} MD_ADC_Public_Constants
  */

/* Public macro ---------------------------------------------------------------*/
/** @defgroup MD_ADC_Public_Macros ADC Public Macros
  * @{
  */

/**
  * @brief  DAC INVREN enable.
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_dac_enable_con_invren(DAC_TypeDef *DACx)
{
  SET_BIT(DACx->CON, DAC_CON_INVREN_MSK);
}

/**
  * @brief  DAC INVREN Disable.
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_dac_disable_con_invren(DAC_TypeDef *DACx)
{
  CLEAR_BIT(DACx->CON, DAC_CON_INVREN_MSK);
}

/**
  * @brief  Check if DAC INVREN is enabled.
  * @param  None
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dac_is_enabled_con_invren(DAC_TypeDef *DACx)
{
  return (READ_BIT(DACx->CON, DAC_CON_INVREN_MSK) == (DAC_CON_INVREN_MSK));
}

/**
  * @brief  TRIGGER enable.
  * @param  DACx DAC Instance
  * @retval None
  */
__STATIC_INLINE void md_dac_enable_con_trien(DAC_TypeDef *DACx)
{
  SET_BIT(DACx->CON, DAC_CON_TRIEN_MSK);
}

/**
  * @brief  TRIGGER Disable.
  * @param  DACx DAC Instance
  * @retval None
  */
__STATIC_INLINE void md_dac_disable_en_trien(DAC_TypeDef *DACx)
{
  CLEAR_BIT(DACx->CON, DAC_CON_TRIEN_MSK);
}

/**
  * @brief  Check if DAC TRIGGER is enabled.
  * @param  DACx DAC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dac_is_enabled_con_trien(DAC_TypeDef *DACx)
{
  return (READ_BIT(DACx->EN, DAC_CON_TRIEN_MSK) == (DAC_CON_TRIEN_MSK));
}

/**
  * @brief  Set DACx DIV register.
  * @note   This bits can only be written none zero value.
  * @param  DACx DAC Instance.
  * @param  DIV value.
  * @retval None
  */
__STATIC_INLINE void md_dac_set_div(DAC_TypeDef *DACx, uint32_t div)
{
  WRITE_REG(DACx->DIV, div);
}

/**
  * @brief  Set DACx DAC_CON WAVE value.
  * @param  DACx DAC Instance.
  * @param  WAVE value.
  * @retval None
  */
__STATIC_INLINE void md_dac_set_con_wave(DAC_TypeDef *DACx, uint32_t wave)
{
  MODIFY_REG(DACx->CON, DAC_CON_MAMP_MSK, wave<<DAC_CON_MAMP_POSS);
}

/**
  * @brief  Set DACx DAC_CON WAVE value.
  * @param  DACx DAC Instance.
  * @param  WAVE value.
  * @retval None
  */
__STATIC_INLINE void md_dac_set_con_mamp(DAC_TypeDef *DACx, uint32_t mamp)
{
  MODIFY_REG(DACx->CON, DAC_CON_MAMP_MSK, mamp<<DAC_CON_MAMP_POSS);
}

/**
  * @brief  Set DACx DAC_CON T_SEL value.
  * @param  DACx DAC Instance.
  * @param  WAVE value.
  * @retval None
  */
__STATIC_INLINE void md_dac_set_con_tsel(DAC_TypeDef *DACx, uint32_t tsel)
{
  MODIFY_REG(DACx->CON, DAC_CON_T_SEL_MSK, tsel<<DAC_CON_T_SEL_POSS);
}

/**
  * @brief  TRIGGER Enable.
  * @param  DACx DAC Instance
  * @retval None
  */
__STATIC_INLINE void md_dac_enable_trig(DAC_TypeDef *DACx)
{
  SET_BIT(DACx->TRIG, DAC_TRIG_S_TRIG_MSK);
}

/**
  * @brief  Check if Transmit FIFO full.
  * @note   This bit is set and cleared by hardware when the TX FIFO is no
  *         longer full.
  * @param  DACx DAC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dac_is_active_flag_stat_txfull(DAC_TypeDef *DACx)
{
  return (READ_BIT(DACx->STAT, DAC_STAT_TX_FULL_MSK) == (DAC_STAT_TX_FULL_MSK));
}

/**
  * @brief  Check if Transmit DAC is busy.
  * @param  DACx DAC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_dac_is_active_flag_stat_busy(DAC_TypeDef *DACx)
{
  return (READ_BIT(DACx->STAT, DAC_STAT_BUSY_MSK) == (DAC_STAT_BUSY_MSK));
}

/**
  * @brief  DAC enable.
  * @param  DACx DAC Instance
  * @retval None
  */
__STATIC_INLINE void md_dac_enable_en_dacen(DAC_TypeDef *DACx)
{
  SET_BIT(DACx->EN, DAC_EN_DAC_EN_MSK);
}

/**
  * @brief  DAC Disable.
  * @param  DACx DAC Instance
  * @retval None
  */
__STATIC_INLINE void md_dac_disable_en_dacen(DAC_TypeDef *DACx)
{
  CLEAR_BIT(DACx->EN, DAC_EN_DAC_EN_MSK);
}

/**
  * @brief  Set DACx data register.
  * @param  DACx DAC Instance.
  * @param  Tx data value.
  * @retval None
  */
__STATIC_INLINE void md_dac_set_txdata(DAC_TypeDef *DACx, uint32_t data)
{
  WRITE_REG(DACx->DATA, data);
}

#endif

/**
  * @} MD_GPIO_Public_Macros
  */

/** @} ADC
  */

/**
  * @} Micro_Driver
  */


#ifdef __cplusplus
}
#endif

#endif

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
