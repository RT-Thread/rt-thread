/**
  ******************************************************************************
  * @file    tae32g58xx_ll_cmp.h
  * @author  MCD Application Team
  * @brief   Header file for CMP LL module
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
#ifndef _TAE32G58XX_LL_CMP_H_
#define _TAE32G58XX_LL_CMP_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup CMP_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup CMP_LL_Exported_Macros CMP LL Exported Macros
  * @brief    CMP LL Exported Macros
  * @{
  */

/**
  * @brief  Output Invert Enable
  * @param  __CMP__ Specifies CMP peripheral
  * @return None
  */
#define __LL_CMP_OutputInvert_En(__CMP__)           SET_BIT((__CMP__)->CR, CMP0_CR_OPOL_Msk)

/**
  * @brief  Output Invert Disable
  * @param  __CMP__ Specifies CMP peripheral
  * @return None
  */
#define __LL_CMP_OutputInvert_Dis(__CMP__)          CLEAR_BIT((__CMP__)->CR, CMP0_CR_OPOL_Msk)

/**
  * @brief  Input Source Set
  * @param  __CMP__ Specifies CMP peripheral
  * @param  src Input Source
  * @return None
  */
#define __LL_CMP_InputSrc_Set(__CMP__, src)         MODIFY_REG((__CMP__)->CR, CMP0_CR_ODEB_Msk, (((src) & 0x1UL) << CMP0_CR_ODEB_Pos))

/**
  * @brief  Output Synchronization Enable
  * @param  __CMP__ Specifies CMP peripheral
  * @return None
  */
#define __LL_CMP_OutputSync_En(__CMP__)             \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) ? (SET_BIT((__CMP__)->CR, CMP0_CR_ODEB_Msk)) : 0)

/**
  * @brief  Output Synchronization Disable
  * @param  __CMP__ Specifies CMP peripheral
  * @return None
  */
#define __LL_CMP_OutputSync_Dis(__CMP__)            \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) ? (CLEAR_BIT((__CMP__)->CR, CMP0_CR_ODEB_Msk)) : 0)

/**
  * @brief  Judge is Output Synchronization Enable or not
  * @param  __CMP__ Specifies CMP peripheral
  * @retval 0 is Output Synchronization Disable
  * @retval 1 is Output Synchronization Enable
  */
#define __LL_CMP_IsOutputSyncEn(__CMP__)            \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) ? (READ_BIT_SHIFT((__CMP__)->CR, CMP0_CR_ODEB_Msk, CMP0_CR_ODEB_Pos)) : 0)

/**
  * @brief  Blank Event Set
  * @param  __CMP__ Specifies CMP peripheral
  * @param  evt Blank Event
  * @return None
  */
#define __LL_CMP_BlkEvt_Set(__CMP__, evt)           MODIFY_REG((__CMP__)->CR, CMP0_CR_BLANKING_Msk, (((evt) & 0x7UL) << CMP0_CR_BLANKING_Pos))

/**
  * @brief  Blank Event Get
  * @param  __CMP__ Specifies CMP peripheral
  * @return Blank Event
  */
#define __LL_CMP_BlkEvt_Get(__CMP__)                READ_BIT_SHIFT((__CMP__)->CR, CMP0_CR_BLANKING_Msk, CMP0_CR_BLANKING_Pos)

/**
  * @brief  CMP Negative In Source Set
  * @param  __CMP__ Specifies CMP peripheral
  * @param  src CMP Negative In Source
  * @return None
  */
#define __LL_CMP_NegInSrc_Set(__CMP__, src)         MODIFY_REG((__CMP__)->CR, CMP0_CR_INM_Msk, (((src) & 0x3UL) << CMP0_CR_INM_Pos))

/**
  * @brief  CMP Hysteresis Set
  * @param  __CMP__ Specifies CMP peripheral
  * @param  hyst CMP Hysteresis
  * @return None
  */
#define __LL_CMP_Hyst_Set(__CMP__, hyst)            MODIFY_REG((__CMP__)->CR, CMP0_CR_HYST_Msk, (((hyst) & 0x3UL) << CMP0_CR_HYST_Pos))

/**
  * @brief  CMP Positive In Source Set
  * @param  __CMP__ Specifies CMP peripheral
  * @param  src CMP Positive In Source
  * @return None
  */
#define __LL_CMP_PosiInSrc_Set(__CMP__, src)        MODIFY_REG((__CMP__)->CR, CMP0_CR_INP_Msk, (((src) & 0x1UL) << CMP0_CR_INP_Pos))

/**
  * @brief  CMP Software Blanking Enable
  * @param  __CMP__ Specifies CMP peripheral
  * @return None
  */
#define __LL_CMP_SwBlanking_En(__CMP__)             SET_BIT((__CMP__)->CR, CMP0_CR_CBLK_Msk)

/**
  * @brief  CMP Software Blanking Disable
  * @param  __CMP__ Specifies CMP peripheral
  * @return None
  */
#define __LL_CMP_SwBlanking_Dis(__CMP__)            CLEAR_BIT((__CMP__)->CR, CMP0_CR_CBLK_Msk)

/**
  * @brief  Judge is CMP Software Blanking Enable or not
  * @param  __CMP__ Specifies CMP peripheral
  * @retval 0 is Software Blanking Disable
  * @retval 1 is Software Blanking Enable
  */
#define __LL_CMP_IsSwBlankingEn(__CMP__)            READ_BIT_SHIFT((__CMP__)->CR, CMP0_CR_CBLK_Msk, CMP0_CR_CBLK_Pos)

/**
  * @brief  CMP Enable
  * @param  __CMP__ Specifies CMP peripheral
  * @return None
  */
#define __LL_CMP_En(__CMP__)                        SET_BIT((__CMP__)->CR, CMP0_CR_CEN_Msk)

/**
  * @brief  CMP Disable
  * @param  __CMP__ Specifies CMP peripheral
  * @return None
  */
#define __LL_CMP_Dis(__CMP__)                       CLEAR_BIT((__CMP__)->CR, CMP0_CR_CEN_Msk)


/**
  * @brief  CMP Output Debounce Set
  * @param  __CMP__ Specifies CMP peripheral
  * @param  dbc CMP Output Debounce
  * @return None
  */
#define __LL_CMP_OutputDbc_Set(__CMP__, dbc)        WRITE_REG((__CMP__)->DEBR, ((dbc) & 0xffUL))


/**
  * @brief  CMP Falling Edge Interrupt Enable
  * @param  __CMP__ Specifies CMP peripheral
  * @return None
  */
#define __LL_CMP_FallingEdge_INT_En(__CMP__)        SET_BIT((__CMP__)->IER, CMP0_IER_FALIE_Msk)

/**
  * @brief  CMP Falling Edge Interrupt Disable
  * @param  __CMP__ Specifies CMP peripheral
  * @return None
  */
#define __LL_CMP_FallingEdge_INT_Dis(__CMP__)       CLEAR_BIT((__CMP__)->IER, CMP0_IER_FALIE_Msk)

/**
  * @brief  Judge is CMP Falling Edge Interrupt Enable or not
  * @param  __CMP__ Specifies CMP peripheral
  * @retval 0 CMP Falling Edge Interrupt is Disable
  * @retval 1 CMP Falling Edge Interrupt is Enable
  */
#define __LL_CMP_IsFallingEdgeIntEn(__CMP__)        READ_BIT_SHIFT((__CMP__)->IER, CMP0_IER_FALIE_Msk, CMP0_IER_FALIE_Pos)

/**
  * @brief  CMP Rising Edge Interrupt Enable
  * @param  __CMP__ Specifies CMP peripheral
  * @return None
  */
#define __LL_CMP_RisingEdge_INT_En(__CMP__)         SET_BIT((__CMP__)->IER, CMP0_IER_RISIE_Msk)

/**
  * @brief  CMP Rising Edge Interrupt Disable
  * @param  __CMP__ Specifies CMP peripheral
  * @return None
  */
#define __LL_CMP_RisingEdge_INT_Dis(__CMP__)        CLEAR_BIT((__CMP__)->IER, CMP0_IER_RISIE_Msk)

/**
  * @brief  Judge is CMP Rising Edge Interrupt Enable or not
  * @param  __CMP__ Specifies CMP peripheral
  * @retval 0 CMP Rising Edge Interrupt is Disable
  * @retval 1 CMP Rising Edge Interrupt is Enable
  */
#define __LL_CMP_IsRisingEdgeIntEn(__CMP__)         READ_BIT_SHIFT((__CMP__)->IER, CMP0_IER_RISIE_Msk, CMP0_IER_RISIE_Pos)


/**
  * @brief  CMP Output Status Read Before Polarity
  * @param  __CMP__ Specifies CMP peripheral
  * @retval 0 CMP output low
  * @retval 1 CMP output high
  */
#define __LL_CMP_Output_Read(__CMP__)               READ_BIT_SHIFT((__CMP__)->ISR, CMP0_ISR_OVAL_Msk, CMP0_ISR_OVAL_Pos)

/**
  * @brief  Judge is CMP Falling Edge Interrupt Pending or not
  * @param  __CMP__ Specifies CMP peripheral
  * @retval 0 isn't CMP Falling Edge Interrupt Pending
  * @retval 1 is CMP Falling Edge Interrupt Pending
  */
#define __LL_CMP_IsFallingEdgeIntPnd(__CMP__)       READ_BIT_SHIFT((__CMP__)->ISR, CMP0_ISR_FAL_Msk, CMP0_ISR_FAL_Pos)

/**
  * @brief  CMP Falling Edge Interrupt Pending Clear
  * @param  __CMP__ Specifies CMP peripheral
  * @return None
  */
#define __LL_CMP_FallingEdgeIntPnd_Clr(__CMP__)     WRITE_REG((__CMP__)->ISR, CMP0_ISR_FAL_Msk)

/**
  * @brief  Judge is CMP Rising Edge Interrupt Pending or not
  * @param  __CMP__ Specifies CMP peripheral
  * @retval 0 isn't CMP Rising Edge Interrupt Pending
  * @retval 1 is CMP Rising Edge Interrupt Pending
  */
#define __LL_CMP_IsRisingEdgeIntPnd(__CMP__)        READ_BIT_SHIFT((__CMP__)->ISR, CMP0_ISR_RIS_Msk, CMP0_ISR_RIS_Pos)

/**
  * @brief  CMP Rising Edge Interrupt Pending Clear
  * @param  __CMP__ Specifies CMP peripheral
  * @return None
  */
#define __LL_CMP_RisingEdgeIntPnd_Clr(__CMP__)      WRITE_REG((__CMP__)->ISR, CMP0_ISR_RIS_Msk)

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup CMP_LL_Exported_Types CMP LL Exported Types
  * @brief    CMP LL Exported Types
  * @{
  */

/**
  * @brief CMP Input Source Definition
  */
typedef enum {
    CMP_INPUT_SRC_ANOLOG = 0,       /*!< CMP Input Source Analog    */
    CMP_INPUT_SRC_DEBOUNCE,         /*!< CMP Input Source Debounce  */
} CMP_InputSrcETypeDef;

/**
  * @brief CMP Blank Event Definition
  */
typedef enum {
    CMP_BLK_EVT_NONE = 0,           /*!< CMP Blank Event None       */
    CMP_BLK_EVT_TMR0_OC0,           /*!< CMP Blank Event TMR0 OC0   */
    CMP_BLK_EVT_TMR1_OC0,           /*!< CMP Blank Event TMR1 OC0   */
    CMP_BLK_EVT_TMR2_OC0,           /*!< CMP Blank Event TMR2 OC0   */
    CMP_BLK_EVT_TMR3_OC0,           /*!< CMP Blank Event TMR3 OC0   */
    CMP_BLK_EVT_TMR4_OC0,           /*!< CMP Blank Event TMR4 OC0   */
    CMP_BLK_EVT_TMR9_OC0,           /*!< CMP Blank Event TMR9 OC0   */
    CMP_BLK_EVT_TMR10_OC0,          /*!< CMP Blank Event TMR10 OC0  */
} CMP_BlkEvtETypeDef;

/**
  * @brief CMP Positive IN Source Definition
  */
typedef enum {
    CMP_POSI_IN_SRC_CMP_INP0 = 0,   /*!< CMP Positive IN Source CMP_INP0    */
    CMP_POSI_IN_SRC_CMP_INP1,       /*!< CMP Positive IN Source CMP_INP1    */
} CMP_PosiInSrcETypeDef;

/**
  * @brief CMP Negative IN Source Definition
  */
typedef enum {
    CMP_NEG_IN_SRC_CMP_INN0 = 0,    /*!< CMP Negative IN Source CMP_INN0    */
    CMP_NEG_IN_SRC_CMP_INN1,        /*!< CMP Negative IN Source CMP_INN1    */
    CMP_NEG_IN_SRC_DACy_OUT,        /*!< CMP Negative IN Source DACy_OUT    */
    CMP_NEG_IN_SRC_DACz_OUT,        /*!< CMP Negative IN Source DACz_OUT    */
} CMP_NegInSrcETypeDef;

/**
  * @brief CMP Hysteresis Definition
  */
typedef enum {
    CMP_HYST_0mv = 0,               /*!< CMP Hysteresis 0mv     */
    CMP_HYST_10mv,                  /*!< CMP Hysteresis 10mv    */
    CMP_HYST_20mv,                  /*!< CMP Hysteresis 20mv    */
    CMP_HYST_30mv,                  /*!< CMP Hysteresis 30mv    */
} CMP_HystETypeDef;


/**
  * @brief CMP Initialization Structure Definition
  */
typedef struct __CMP_InitTypeDef {
    bool    rising_int_en;              /*!< CMP Rising Interrupt Enable    */
    bool    falling_int_en;             /*!< CMP Falling Interrupt Enable   */
    bool    output_invert_en;           /*!< CMP Output Invert Enable       */
    uint8_t output_dbc;                 /*!< CMP Output Debounce            */

    CMP_HystETypeDef      hyst;         /*!< CMP Hysteresis Range Select    */
    CMP_BlkEvtETypeDef    blk_evt;      /*!< CMP Blank Event Select         */
    CMP_InputSrcETypeDef  input_src;    /*!< CMP Input Source Select        */
    CMP_NegInSrcETypeDef  neg_in_src;   /*!< CMP Negative In Source Select  */
    CMP_PosiInSrcETypeDef posi_in_src;  /*!< CMP Positive In Source Select  */

    bool    output_sync_en;             /*!< CMP Output Sync Enable         */
} CMP_InitTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup CMP_LL_Exported_Functions
  * @{
  */

/** @addtogroup CMP_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_CMP_Init(CMP_TypeDef *Instance, CMP_InitTypeDef *init);
LL_StatusETypeDef LL_CMP_DeInit(CMP_TypeDef *Instance);
void LL_CMP_MspInit(CMP_TypeDef *Instance);
void LL_CMP_MspDeInit(CMP_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup CMP_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_CMP_Start(CMP_TypeDef *Instance);
LL_StatusETypeDef LL_CMP_Stop(CMP_TypeDef *Instance);
LL_StatusETypeDef LL_CMP_SwBlanking_En(CMP_TypeDef *Instance);
LL_StatusETypeDef LL_CMP_SwBlanking_Dis(CMP_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup CMP_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_CMP_IRQHandler(CMP_TypeDef *Instance);
void LL_CMP_RisingEdgeCallback(CMP_TypeDef *Instance);
void LL_CMP_FallingEdgeCallback(CMP_TypeDef *Instance);
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

#endif /* _TAE32G58XX_LL_CMP_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

