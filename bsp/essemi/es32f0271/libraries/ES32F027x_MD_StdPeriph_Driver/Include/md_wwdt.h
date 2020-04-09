/**
  ******************************************************************************
  * @file    md_wwdt.h
  * @brief   ES32F0271 WWDT HEAD File.
  *
  * @version V0.01
  * @date    4/12/2018
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MD_WWDT_H__
#define __MD_WWDT_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/ 
#include "es32f0271.h"
#include "reg_wwdt.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined (WWDT)
/** @defgroup WWDT WWDT
  * @brief WWDT micro driver
  * @{
  */

/* Public Init Structure ------------------------------------------------------*/
/** @defgroup MD_WWDT_PT_INIT WWDT Public Init Structure
  * @brief   WWDT Init Structure.
  * @{
  */
typedef struct
{
  uint32_t Prescaler;     /*!< Specifies the prescaler value of the WWDT.
                               This parameter can be a value of @ref WWDT_Prescaler */

  uint32_t Window;        /*!< Specifies the WWDT window value to be compared to the downcounter.
                               This parameter must be a number a minimum, 0x40 and a maximum, 0x7F */

  uint32_t Counter;       /*!< Specifies the WWDT free-running downcounter  value.
                               This parameter must be a number between a minimum, 0x40 and a maximum, 0x7F */

  uint32_t EWIMode ;      /*!< Specifies if WWDT Early Wakeup Interupt is enable or not.
                               This parameter can be a value of @ref WWDT_EWI_Mode */

} md_wwdt_inittypedef;
/**
  * @} MD_WWDT_PT_INIT
  */

/* Public constants -----------------------------------------------------------*/
/** @defgroup MD_WWDT_PUBLIC_CONSTANTS WWDT Public Constants
  * @{
  */

/** @defgroup MD_WWDT_Prescaler WWDT Prescaler
  * @{
  */
#define WWDT_PRESCALER_1                    0x00000000U                         /*!< WWDT counter clock = (PCLK1/4096)/1 */
#define WWDT_PRESCALER_2                    1U<<WWDT_CFG_WDGTB_POSS             /*!< WWDT counter clock = (PCLK1/4096)/2, WWDT_CFG_WDGTB_POSS = 7 */
#define WWDT_PRESCALER_4                    2U<<WWDT_CFG_WDGTB_POSS             /*!< WWDT counter clock = (PCLK1/4096)/4, WWDT_CFG_WDGTB_POSS = 7 */
#define WWDT_PRESCALER_8                    WWDT_CFG_WDGTB_MSK                  /*!< WWDT counter clock = (PCLK1/4096)/8, WWDT_CFG_WDGTB_MSK = 3<<7 */
/**
  * @} MD_WWDT_Prescaler
  */

/** @defgroup WWDT_EWI_Mode WWDT Early Wakeup Interrupt Mode
  * @{
  */
#define WWDT_EWI_DISABLE                    0x00000000U                  /*!< EWI Disable */
#define WWDT_EWI_ENABLE                     WWDT_CON_WDGA_MSK            /*!< EWI Enable, WWDT_CON_WDGA_MSK = 1<<7 */
/**
  * @}WWDT_EWI_Mode
  */

/**
  * @} MD_WWDT_PUBLIC_CONSTANTS
  */

/* Public macro ---------------------------------------------------------------*/
/** @defgroup MD_WWDT_Public_Macros WWDT Public Macros
  * @{
  */
  
/**
  * @brief  Set the WWDT_CON value
  * @note   A write of 0 in bit 7 has no effect.
  * @param  WWD WWDT Instance
  * @param  Reg_Value is a 32-bit value
  * @retval None
  */
__STATIC_INLINE void md_wwdt_set_con(WWDT_TypeDef *WWD, uint32_t Reg_Value)
{
  WRITE_REG(WWD->CON, Reg_Value);
}

/**
  * @brief  Get the WWDT_CON value
  * @note   None.
  * @param  WWD WWDT Instance
  * @retval a 32-bit value
  */
__STATIC_INLINE uint32_t md_wwdt_get_con(WWDT_TypeDef *WWD)
{
  return (uint32_t) (READ_REG(WWD->CON));
}

/**
  * @brief  WWDT WDG Enable
  * @note   This bit is set by software and only cleared by hardware after a reset.
  *         A write of 0 has no effect. When WDGA=1, the watchdog can generate a reset.
  * @param  WWD WWDT Instance
  * @retval None
  */
__STATIC_INLINE void md_wwdt_enable_con_wdga(WWDT_TypeDef *WWD)
{
  SET_BIT(WWD->CON, WWDT_CON_WDGA_MSK);
}

/**
  * @brief  Indicate if WWDT WDG is enabled
  * @note   This bit is set by software and only cleared by hardware after a reset.
  *         A write of 0 has no effect. When WDGA=1, the watchdog can generate a reset.
  * @param  WWD WWDT Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_wwdt_is_enabled_wdga(WWDT_TypeDef *WWD)
{
  return (uint32_t)(READ_BIT(WWD->CON, WWDT_CON_WDGA_MSK) == (WWDT_CON_WDGA_MSK));
}

/**
  * @brief  Set WWDT T 7-bit counter
  * @note   These bits contain the value of the watchdog counter.
  *         It is decremented every (4096 x 2^WDGTB[1:0]) PCLK cycles.
  *         A reset is produced when it is decremented from 0x40 to 0x3F(T6 becomes cleared),
  *         and when it is renewed on the condition the value is more than the window value and the WDGA bit is enabled.
  * @param  WWD WWDT Instance
  * @param  counter is a 7-bit number 
  *         @arg Max Value 0x7F
  *         @arg Min Value 0x40
  * @retval None
  */
__STATIC_INLINE void md_wwdt_set_con_t(WWDT_TypeDef *WWD, uint32_t counter)
{
  MODIFY_REG(WWD->CON, WWDT_CON_T_MSK, counter);
}

/**
  * @brief  Get WWDT T 7-bit counter
  * @note   These bits contain the value of the watchdog counter.
  *         It is decremented every (4096 x 2^WDGTB[1:0]) PCLK cycles.
  *         A reset is produced when it is decremented from 0x40 to 0x3F(T6 becomes cleared),
  *         and when it is renewed on the condition the value is more than the window value and the WDGA bit is enabled.
  * @param  WWD WWDT Instance
  * @retval The retval can be a value of the area:
  *         @arg Max Value 0x7F
  *         @arg Min Value 0x40
  */
__STATIC_INLINE uint32_t md_wwdt_get_con_t(WWDT_TypeDef *WWD)
{
  return (READ_BIT(WWD->CON, WWDT_CON_T_MSK)>>WWDT_CON_T_POSS);
}

/**
  * @brief  Set the WWDT_CFG value
  * @note   None.
  * @param  WWD WWDT Instance
  * @param  Reg_Value is a 32-bit value
  * @retval None
  */
__STATIC_INLINE void md_wwdt_set_cfg(WWDT_TypeDef *WWD, uint32_t Reg_Value)
{
  WRITE_REG(WWD->CFG, Reg_Value);
}

/**
  * @brief  Get the WWDT_CFG value
  * @note   None.
  * @param  WWD WWDT Instance
  * @retval a 32-bit value
  */
__STATIC_INLINE uint32_t md_wwdt_get_cfg(WWDT_TypeDef *WWD)
{
  return (uint32_t) (READ_REG(WWD->CFG));
}

/**
  * @brief  Set WWDT WDGTB 2-bit prescaler value
  * @note   The time base of the prescaler can be modified as follows: 
  *         00: CK Counter Clock (PCLK div 4096) div 1 
  *         01: CK Counter Clock (PCLK div 4096) div 2 
  *         10: CK Counter Clock (PCLK div 4096) div 4 
  *         11: CK Counter Clock (PCLK div 4096) div 8 
  * @param  WWD WWDT Instance
  * @param  prescaler is a 2-bit number 
  *         @arg @ref WWDT_PRESCALER_1 
  *         @arg @ref WWDT_PRESCALER_2 
  *         @arg @ref WWDT_PRESCALER_4 
  *         @arg @ref WWDT_PRESCALER_8 
  * @retval None
  */
__STATIC_INLINE void md_wwdt_set_cfg_wdgtb(WWDT_TypeDef *WWD, uint32_t prescaler)
{
  MODIFY_REG(WWD->CFG, WWDT_CFG_WDGTB_MSK, prescaler);
}

/**
  * @brief  Get WWDT WDGTB 2-bit prescaler value
  * @note   The time base of the prescaler can be modified as follows: 
            00: CK Counter Clock (PCLK div 4096) div 1 
            01: CK Counter Clock (PCLK div 4096) div 2 
            10: CK Counter Clock (PCLK div 4096) div 4 
            11: CK Counter Clock (PCLK div 4096) div 8 
  * @param  WWD WWDT Instance
  * @retval The retval can be one of the following values:
  *         @arg @ref WWDT_PRESCALER_1 
  *         @arg @ref WWDT_PRESCALER_2 
  *         @arg @ref WWDT_PRESCALER_4 
  *         @arg @ref WWDT_PRESCALER_8 
  */
__STATIC_INLINE uint32_t md_wwdt_get_cfg_wdgtb(WWDT_TypeDef *WWD)
{
  return (READ_BIT(WWD->CFG, WWDT_CFG_WDGTB_MSK)>>WWDT_CFG_WDGTB_POSS);
}

/**
  * @brief  Set WWDT W 7-bit window
  * @note   These bits contain the window value to be compared to the downcounter. 
  * @param  WWD WWDT Instance
  * @param  window is a 7-bit number
  *         @arg Max Value 0x7F
  *         @arg Min Value 0x40
  * @retval None
  */
__STATIC_INLINE void md_wwdt_set_cfg_w(WWDT_TypeDef *WWD, uint32_t window)
{
  MODIFY_REG(WWD->CFG, WWDT_CFG_W_MSK, window);
}

/**
  * @brief  Get WWDT W 7-bit window
  * @note   These bits contain the window value to be compared to the downcounter. 
  * @param  WWD WWDT Instance
  * @retval The retval can be a value of the area:
  *         @arg Max Value 0x7F
  *         @arg Min Value 0x40
  */
__STATIC_INLINE uint32_t md_wwdt_get_cfg_w(WWDT_TypeDef *WWD)
{
  return (READ_BIT(WWD->CFG, WWDT_CFG_W_MSK)>>WWDT_CFG_W_POSS);
}

/**
  * @brief  WWDT Early wakeup interrupt Enable
  * @note   A write of 1 in IER to enable this interrupt.
  * @param  WWD WWDT Instance
  * @retval None
  */
__STATIC_INLINE void md_wwdt_enable_ier_ewis(WWDT_TypeDef *WWD)
{
  SET_BIT(WWD->IER, WWDT_IER_EWIS_MSK);
}

/**
  * @brief  WWDT Early wakeup interrupt Disable
  * @note   A write of 1 in IDR to disable this interrupt.
  * @param  WWD WWDT Instance
  * @retval None
  */
__STATIC_INLINE void md_wwdt_disable_idr_ewis(WWDT_TypeDef *WWD)
{
  SET_BIT(WWD->IDR, WWDT_IDR_EWIS_MSK);
}

/**
  * @brief  Indicate if WWDT EWI is enabled
  * @note   To check EWI enable or not.
  * @param  WWD WWDT Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_wwdt_is_enabled_ivs_ewis(WWDT_TypeDef *WWD)
{
  return (uint32_t) (READ_BIT(WWD->IVS, WWDT_IVS_EWIS_MSK) == (WWDT_IVS_EWIS_MSK));
}

/**
  * @brief  Get the early wakeup interrupt flag status
  * @note   This bit is set by hardware when the counter has reached the value 0x40. 
            It can be cleared by software by writing 1 in WWDT_ICR. This bit is 
            also set if the interrupt is not enabled.
  * @param  WWD WWDT Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_wwdt_is_active_rif_ewif(WWDT_TypeDef *WWD)
{
  return (uint32_t) (READ_BIT(WWD->RIF, WWDT_RIF_EWIF_MSK) == (WWDT_RIF_EWIF_MSK));
}

/**
  * @brief  Get the early wakeup interrupt flag masked status
  * @note   This bit is set by hardware when the counter has reached the value 0x40 
            and the interrupt is enabled. 
  * @param  WWD WWDT Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_wwdt_is_active_ifm_ewim(WWDT_TypeDef *WWD)
{
  return (uint32_t) (READ_BIT(WWD->IFM, WWDT_IFM_EWIM_MSK) == (WWDT_IFM_EWIM_MSK));
}

/**
  * @brief  Clear the early wakeup interrupt flag
  * @param  WWD WWDT Instance
  * @retval None
  */
__STATIC_INLINE void md_wwdt_clear_icr_ewic(WWDT_TypeDef *WWD)
{
  SET_BIT(WWD->ICR, WWDT_ICR_EWIC_MSK);
}

/**
  * @} MD_WWDT_Public_Macros
  */

/** @defgroup MD_WWDT_PF_Init WWDT Init Function
  * @{
  */
void md_wwdt_init(WWDT_TypeDef *WWD, md_wwdt_inittypedef *WWDT_InitStruct);
/**
  * @} MD_WWDT_PF_Init
  */

#endif

/* Private macros ------------------------------------------------------------*/

/** @defgroup MD_WWDT_Private_Macros WWDG Private Macros
  * @{
  */
#define IS_MD_WWDT_ALL_INSTANCE(__INSTANCE__) (__INSTANCE__ == WWDT)

#define IS_MD_WWDT_PRESCALER(__VALUE__)       (((__VALUE__) == WWDT_PRESCALER_1)   \
                                           ||  ((__VALUE__) == WWDT_PRESCALER_2)   \
                                           ||  ((__VALUE__) == WWDT_PRESCALER_4)   \
                                           ||  ((__VALUE__) == WWDT_PRESCALER_8))

#define IS_MD_WWDT_WINDOW(__VALUE__)          (((__VALUE__) >= 0x40) && ((__VALUE__) <= 0x7F))

#define IS_MD_WWDT_COUNTER(__VALUE__)         (((__VALUE__) >= 0x40) && ((__VALUE__) <= 0x7F))

#define IS_MD_WWDT_EWI_MODE(__VALUE__)        (((__VALUE__) == WWDT_EWI_ENABLE)    \
                                           ||  ((__VALUE__) == WWDT_EWI_DISABLE))
/**
  * @} MD_WWDT_Private_Macros
  */

/**
  * @} WWDT
  */
/**
  * @} Micro_Driver
  */

#ifdef __cplusplus
}
#endif

#endif

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
