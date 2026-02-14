/**
  ******************************************************************************
  * @file    tae32g58xx_ll_tmr.h
  * @author  MCD Application Team
  * @brief   Header file for TMR LL module
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
#ifndef _TAE32G58XX_LL_TMR_H_
#define _TAE32G58XX_LL_TMR_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup TMR_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup TMR_LL_Exported_Constants TMR LL Exported Constants
  * @brief    TMR LL Exported Constants
  * @{
  */

#define TMR9_CCER_CC3NP_Pos         (15UL)                  /*!< CC3NP (Bit 15)                                         */
#define TMR9_CCER_CC3NP_Msk         (0x8000UL)              /*!< CC3NP (Bitfield-Mask: 0x01)                            */
#define TMR9_CCER_CC3PP_Pos         (14UL)                  /*!< CC3PP (Bit 14)                                         */
#define TMR9_CCER_CC3PP_Msk         (0x4000UL)              /*!< CC3PP (Bitfield-Mask: 0x01)                            */

#define TMR9_CCER_CC2NP_Pos         (11UL)                  /*!< CC2NP (Bit 11)                                         */
#define TMR9_CCER_CC2NP_Msk         (0x800UL)               /*!< CC2NP (Bitfield-Mask: 0x01)                            */
#define TMR9_CCER_CC2PP_Pos         (10UL)                  /*!< CC2PP (Bit 10)                                         */
#define TMR9_CCER_CC2PP_Msk         (0x400UL)               /*!< CC2PP (Bitfield-Mask: 0x01)                            */

#define TMR9_CCER_CC1NP_Pos         (7UL)                   /*!< CC1NP (Bit 7)                                          */
#define TMR9_CCER_CC1NP_Msk         (0x80UL)                /*!< CC1NP (Bitfield-Mask: 0x01)                            */
#define TMR9_CCER_CC1PP_Pos         (6UL)                   /*!< CC1PP (Bit 6)                                          */
#define TMR9_CCER_CC1PP_Msk         (0x40UL)                /*!< CC1PP (Bitfield-Mask: 0x01)                            */

#define TMR9_CCER_CC0NP_Pos         (3UL)                   /*!< CC0NP (Bit 3)                                          */
#define TMR9_CCER_CC0NP_Msk         (0x8UL)                 /*!< CC0NP (Bitfield-Mask: 0x01)                            */
#define TMR9_CCER_CC0PP_Pos         (2UL)                   /*!< CC0PP (Bit 2)                                          */
#define TMR9_CCER_CC0PP_Msk         (0x4UL)                 /*!< CC0PP (Bitfield-Mask: 0x01)                            */

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup TMR_LL_Exported_Macros TMR LL Exported Macros
  * @brief    TMR LL Exported Macros
  * @{
  */

/**
  * @brief  TI0 Input Source Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  src TI0 Input Source
  * @return None
  */
#define __LL_TMR_TI0InputSrc_Set(__TMR__, src)          \
        MODIFY_REG((__TMR__)->CR0, TMR9_CR0_TI0S_Msk, (((src) & 0x1UL) << TMR9_CR0_TI0S_Pos))

/**
  * @brief  Dead Zone and Digital Filter Clock Division Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  div Clock Division
  * @return None
  */
#define __LL_TMR_DzDigFilClkDiv_Set(__TMR__, div)       \
        MODIFY_REG((__TMR__)->CR0, TMR9_CR0_DCD_Msk, (((div) & 0x3UL) << TMR9_CR0_DCD_Pos))

/**
  * @brief  Auto Preload Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_AutoPreload_En(__TMR__)                SET_BIT((__TMR__)->CR0, TMR9_CR0_ARE_Msk)

/**
  * @brief  Auto Preload Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_AutoPreload_Dis(__TMR__)               CLEAR_BIT((__TMR__)->CR0, TMR9_CR0_ARE_Msk)

/**
  * @brief  Center Aligned Mode Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  mode Center-Aligned Mode
  * @return None
  */
#define __LL_TMR_CtrAlignMode_Set(__TMR__, mode)        \
        MODIFY_REG((__TMR__)->CR0, TMR9_CR0_CMS_Msk, (((mode) & 0x3UL)<< TMR9_CR0_CMS_Pos))

/**
  * @brief  Counter Direction Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  dir Counter Direction
  * @return None
  */
#define __LL_TMR_CntDir_Set(__TMR__, dir)               \
        MODIFY_REG((__TMR__)->CR0, TMR9_CR0_DIR_Msk, (((dir) & 0x1UL)<< TMR9_CR0_DIR_Pos))

/**
  * @brief  Work Mode Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  mode Work Mode
  * @return None
  */
#define __LL_TMR_WorkMode_Set(__TMR__, mode)            \
        MODIFY_REG((__TMR__)->CR0, TMR9_CR0_OPM_Msk, (((mode) & 0x1UL)<< TMR9_CR0_OPM_Pos))

/**
  * @brief  Update Event Source Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  src Update Event Source
  * @return None
  */
#define __LL_TMR_UpdateEvtSrc_Set(__TMR__, src)         \
        MODIFY_REG((__TMR__)->CR0, TMR9_CR0_URS_Msk, (((src) & 0x1UL) << TMR9_CR0_URS_Pos))

/**
  * @brief  Update Event Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_UpdateEvt_En(__TMR__)                  CLEAR_BIT((__TMR__)->CR0, TMR9_CR0_UDIS_Msk)

/**
  * @brief  Update Event Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_UpdateEvt_Dis(__TMR__)                 SET_BIT((__TMR__)->CR0, TMR9_CR0_UDIS_Msk)

/**
  * @brief  Judege is Update Event Enable or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 Update Event is Disable
  * @retval 1 Update Event is Enable
  */
#define __LL_TMR_IsUpdateEvtEn(__TMR__)                 (!(READ_BIT_SHIFT((__TMR__)->CR0, TMR9_CR0_UDIS_Msk, TMR9_CR0_UDIS_Pos)))

/**
  * @brief  Timer Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_En(__TMR__)                            SET_BIT((__TMR__)->CR0, TMR9_CR0_CEN_Msk)

/**
  * @brief  Timer Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_Dis(__TMR__)                           CLEAR_BIT((__TMR__)->CR0, TMR9_CR0_CEN_Msk)


/**
  * @brief  CH3N Output Idle State Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  sta CH3N Output Idle State
  * @return None
  */
#define __LL_TMR_CH3N_OutputIdleState_Set(__TMR__, sta) \
        MODIFY_REG((__TMR__)->CR1, TMR9_CR1_OIS3N_Msk, (((sta) & 0x1UL) << TMR9_CR1_OIS3N_Pos))

/**
  * @brief  CH3 Output Idle State Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  sta CH3 Output Idle State
  * @return None
  */
#define __LL_TMR_CH3_OutputIdleState_Set(__TMR__, sta)  \
        MODIFY_REG((__TMR__)->CR1, TMR9_CR1_OIS3_Msk, (((sta) & 0x1UL) << TMR9_CR1_OIS3_Pos))

/**
  * @brief  CH2N Output Idle State Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  sta CH2N Output Idle State
  * @return None
  */
#define __LL_TMR_CH2N_OutputIdleState_Set(__TMR__, sta) \
        MODIFY_REG((__TMR__)->CR1, TMR9_CR1_OIS2N_Msk, (((sta) & 0x1UL) << TMR9_CR1_OIS2N_Pos))

/**
  * @brief  CH2 Output Idle State Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  sta CH2 Output Idle State
  * @return None
  */
#define __LL_TMR_CH2_OutputIdleState_Set(__TMR__, sta)  \
        MODIFY_REG((__TMR__)->CR1, TMR9_CR1_OIS2_Msk, (((sta) & 0x1UL) << TMR9_CR1_OIS2_Pos))

/**
  * @brief  CH1N Output Idle State Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  sta CH1N Output Idle State
  * @return None
  */
#define __LL_TMR_CH1N_OutputIdleState_Set(__TMR__, sta) \
        MODIFY_REG((__TMR__)->CR1, TMR9_CR1_OIS1N_Msk, (((sta) & 0x1UL) << TMR9_CR1_OIS1N_Pos))

/**
  * @brief  CH1 Output Idle State Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  sta CH1 Output Idle State
  * @return None
  */
#define __LL_TMR_CH1_OutputIdleState_Set(__TMR__, sta)  \
        MODIFY_REG((__TMR__)->CR1, TMR9_CR1_OIS1_Msk, (((sta) & 0x1UL) << TMR9_CR1_OIS1_Pos))

/**
  * @brief  CH0N Output Idle State Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  sta CH0N Output Idle State
  * @return None
  */
#define __LL_TMR_CH0N_OutputIdleState_Set(__TMR__, sta) \
        MODIFY_REG((__TMR__)->CR1, TMR9_CR1_OIS0N_Msk, (((sta) & 0x1UL) << TMR9_CR1_OIS0N_Pos))

/**
  * @brief  CH0 Output Idle State Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  sta CH0 Output Idle State
  * @return None
  */
#define __LL_TMR_CH0_OutputIdleState_Set(__TMR__, sta)  \
        MODIFY_REG((__TMR__)->CR1, TMR9_CR1_OIS0_Msk, (((sta) & 0x1UL) << TMR9_CR1_OIS0_Pos))

/**
  * @brief  CHxN Output Idle State Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  ch Output Channel @ref TMR_CapCmpChETypeDef
  * @param  sta CHxN Output Idle State
  * @return None
  */
#define __LL_TMR_CHxN_OutputIdleState_Set(__TMR__, ch, sta) \
        MODIFY_REG((__TMR__)->CR1, TMR9_CR1_OIS0N_Msk << (((uint32_t)(ch) % 4) * 2), (((sta) & 0x1UL) << (TMR9_CR1_OIS0N_Pos + ((uint32_t)(ch) % 4) * 2)))

/**
  * @brief  CHx Output Idle State Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  ch Output Channel @ref TMR_CapCmpChETypeDef
  * @param  sta CHx Output Idle State
  * @return None
  */
#define __LL_TMR_CHx_OutputIdleState_Set(__TMR__, ch, sta)  \
        MODIFY_REG((__TMR__)->CR1, TMR9_CR1_OIS0_Msk << (((uint32_t)(ch) % 4) * 2), (((sta) & 0x1UL) << (TMR9_CR1_OIS0_Pos + ((uint32_t)(ch) % 4) * 2)))

/**
  * @brief  Master Mode Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  mode Master Mode
  * @return None
  */
#define __LL_TMR_MstMode_Set(__TMR__, mode)             \
        MODIFY_REG((__TMR__)->CR1, TMR9_CR1_MMS_Msk, (((mode) & 0x7UL) << TMR9_CR1_MMS_Pos))


/**
  * @brief  ETR Input Source Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  src ETR Input Source
  * @return None
  */
#define __LL_TMR_ETRInputSrc_Set(__TMR__, src)          \
        MODIFY_REG((__TMR__)->SCR, TMR9_SCR_ETS_Msk, (((src) & 0xfUL) << TMR9_SCR_ETS_Pos))

/**
  * @brief  ETR Mode Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  mode ETR Mode
  * @return None
  */
#define __LL_TMR_ETRMode_Set(__TMR__, mode)             \
        MODIFY_REG((__TMR__)->SCR, TMR9_SCR_EE_Msk, (((mode) & 0x1UL) << TMR9_SCR_EE_Pos))

/**
  * @brief  ETR Edge Mode Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  mode ETR Edge Mode
  * @return None
  */
#define __LL_TMR_ETREdgeMode_Set(__TMR__, mode)         \
        MODIFY_REG((__TMR__)->SCR, TMR9_SCR_EMS_Msk, (((mode) & 0x3UL) << TMR9_SCR_EMS_Pos))

/**
  * @brief  ETR Filter Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  fil ETR Filter
  * @return None
  */
#define __LL_TMR_ETRFilter_Set(__TMR__, fil)            \
        MODIFY_REG((__TMR__)->SCR, TMR9_SCR_EFS_Msk, (((fil) & 0xfUL) << TMR9_SCR_EFS_Pos))

/**
  * @brief  Trigger Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  tri Trigger
  * @return None
  */
#define __LL_TMR_Trigger_Set(__TMR__, tri)              \
        MODIFY_REG((__TMR__)->SCR, TMR9_SCR_TS_Msk, (((tri) & 0x1fUL) << TMR9_SCR_TS_Pos))

/**
  * @brief  Master/Slave Fast-Sync Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_MstSlvFastSync_En(__TMR__)             SET_BIT((__TMR__)->SCR, TMR9_SCR_FE_Msk)

/**
  * @brief  Master/Slave Fast-Sync Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_MstSlvFastSync_Dis(__TMR__)            CLEAR_BIT((__TMR__)->SCR, TMR9_SCR_FE_Msk)

/**
  * @brief  Slave Mode Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  mode Slave Mode
  * @return None
  */
#define __LL_TMR_SlaveMode_Set(__TMR__, mode)           \
        MODIFY_REG((__TMR__)->SCR, TMR9_SCR_SMS_Msk, (((mode) & 0xfUL) << TMR9_SCR_SMS_Pos))


/**
  * @brief  Break Interrupt Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @note   Include Break0/1 and System Fault Interrupt Enable
  * @return None
  */
#define __LL_TMR_Brk_INT_En(__TMR__)                    SET_BIT((__TMR__)->IER, TMR9_IER_BIE_Msk)

/**
  * @brief  Break Interrupt Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @note   Include Break0/1 and System Fault Interrupt Disable
  * @return None
  */
#define __LL_TMR_Brk_INT_Dis(__TMR__)                   CLEAR_BIT((__TMR__)->IER, TMR9_IER_BIE_Msk)

/**
  * @brief  Judge is Break Interrupt Enable or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 Break Interrupt is Disable
  * @retval 1 Break Interrupt is Enable
  */
#define __LL_TMR_IsBrkIntEn(__TMR__)                    READ_BIT_SHIFT((__TMR__)->IER, TMR9_IER_BIE_Msk, TMR9_IER_BIE_Pos)

/**
  * @brief  Trigger Interrupt Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_Trig_INT_En(__TMR__)                   SET_BIT((__TMR__)->IER, TMR9_IER_TIE_Msk)

/**
  * @brief  Trigger Interrupt Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_Trig_INT_Dis(__TMR__)                  CLEAR_BIT((__TMR__)->IER, TMR9_IER_TIE_Msk)

/**
  * @brief  Judge is Trigger Interrupt Enable or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 Trigger Interrupt is Disable
  * @retval 1 Trigger Interrupt is Enable
  */
#define __LL_TMR_IsTrigIntEn(__TMR__)                   READ_BIT_SHIFT((__TMR__)->IER, TMR9_IER_TIE_Msk, TMR9_IER_TIE_Pos)

/**
  * @brief  Counter Overflow Interrupt Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_Overflow_INT_En(__TMR__)               SET_BIT((__TMR__)->IER, TMR9_IER_OVIE_Msk)

/**
  * @brief  Counter Overflow Interrupt Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_Overflow_INT_Dis(__TMR__)              CLEAR_BIT((__TMR__)->IER, TMR9_IER_OVIE_Msk)

/**
  * @brief  Judge is Counter Overflow Interrupt Enable or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 Counter Overflow Interrupt is Disable
  * @retval 1 Counter Overflow Interrupt is Enable
  */
#define __LL_TMR_IsOverflowIntEn(__TMR__)               READ_BIT_SHIFT((__TMR__)->IER, TMR9_IER_OVIE_Msk, TMR9_IER_OVIE_Pos)

/**
  * @brief  Update Event Interrupt Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_UpdateEvt_INT_En(__TMR__)              SET_BIT((__TMR__)->IER, TMR9_IER_UIE_Msk)

/**
  * @brief  Update Event Interrupt Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_UpdateEvt_INT_Dis(__TMR__)             CLEAR_BIT((__TMR__)->IER, TMR9_IER_UIE_Msk)

/**
  * @brief  Judge is Update Event Interrupt Enable or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 Update Event Interrupt is Disable
  * @retval 1 Update Event Interrupt is Enable
  */
#define __LL_TMR_IsUpdateEvtIntEn(__TMR__)              READ_BIT_SHIFT((__TMR__)->IER, TMR9_IER_UIE_Msk, TMR9_IER_UIE_Pos)

/**
  * @brief  CC3 OverCapture Interrupt Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC3_OverCap_INT_En(__TMR__)            SET_BIT((__TMR__)->IER, TMR9_IER_C3OIE_Msk)

/**
  * @brief  CC3 OverCapture Interrupt Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC3_OverCap_INT_Dis(__TMR__)           CLEAR_BIT((__TMR__)->IER, TMR9_IER_C3OIE_Msk)

/**
  * @brief  Judge is CC3 OverCapture Interrupt Enable or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 CC3 OverCapture Interrupt is Disable
  * @retval 1 CC3 OverCapture Interrupt is Enable
  */
#define __LL_TMR_CC3_IsOverCapIntEn(__TMR__)            READ_BIT_SHIFT((__TMR__)->IER, TMR9_IER_C3OIE_Msk, TMR9_IER_C3OIE_Pos)

/**
  * @brief  CC3 Capture/Compare Interrupt Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC3_CapCmp_INT_En(__TMR__)             SET_BIT((__TMR__)->IER, TMR9_IER_C3MIE_Msk)

/**
  * @brief  CC3 Capture/Compare Interrupt Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC3_CapCmp_INT_Dis(__TMR__)            CLEAR_BIT((__TMR__)->IER, TMR9_IER_C3MIE_Msk)

/**
  * @brief  Judge is CC3 Capture/Compare Interrupt Enable or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 CC3 Capture/Compare Interrupt is Disable
  * @retval 1 CC3 Capture/Compare Interrupt is Enable
  */
#define __LL_TMR_CC3_IsCapCmpIntEn(__TMR__)             READ_BIT_SHIFT((__TMR__)->IER, TMR9_IER_C3MIE_Msk, TMR9_IER_C3MIE_Pos)

/**
  * @brief  CC2 OverCapture Interrupt Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC2_OverCap_INT_En(__TMR__)            SET_BIT((__TMR__)->IER, TMR9_IER_C2OIE_Msk)

/**
  * @brief  CC2 OverCapture Interrupt Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC2_OverCap_INT_Dis(__TMR__)           CLEAR_BIT((__TMR__)->IER, TMR9_IER_C2OIE_Msk)

/**
  * @brief  Judge is CC2 OverCapture Interrupt Enable or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 CC2 OverCapture Interrupt is Disable
  * @retval 1 CC2 OverCapture Interrupt is Enable
  */
#define __LL_TMR_CC2_IsOverCapIntEn(__TMR__)            READ_BIT_SHIFT((__TMR__)->IER, TMR9_IER_C2OIE_Msk, TMR9_IER_C2OIE_Pos)

/**
  * @brief  CC2 Capture/Compare Interrupt Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC2_CapCmp_INT_En(__TMR__)             SET_BIT((__TMR__)->IER, TMR9_IER_C2MIE_Msk)

/**
  * @brief  CC2 Capture/Compare Interrupt Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC2_CapCmp_INT_Dis(__TMR__)            CLEAR_BIT((__TMR__)->IER, TMR9_IER_C2MIE_Msk)

/**
  * @brief  Judge is CC2 Capture/Compare Interrupt Enable or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 CC2 Capture/Compare Interrupt is Disable
  * @retval 1 CC2 Capture/Compare Interrupt is Enable
  */
#define __LL_TMR_CC2_IsCapCmpIntEn(__TMR__)             READ_BIT_SHIFT((__TMR__)->IER, TMR9_IER_C2MIE_Msk, TMR9_IER_C2MIE_Pos)

/**
  * @brief  CC1 OverCapture Interrupt Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC1_OverCap_INT_En(__TMR__)            SET_BIT((__TMR__)->IER, TMR9_IER_C1OIE_Msk)

/**
  * @brief  CC1 OverCapture Interrupt Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC1_OverCap_INT_Dis(__TMR__)           CLEAR_BIT((__TMR__)->IER, TMR9_IER_C1OIE_Msk)

/**
  * @brief  Judge is CC1 OverCapture Interrupt Enable or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 CC1 OverCapture Interrupt is Disable
  * @retval 1 CC1 OverCapture Interrupt is Enable
  */
#define __LL_TMR_CC1_IsOverCapIntEn(__TMR__)            READ_BIT_SHIFT((__TMR__)->IER, TMR9_IER_C1OIE_Msk, TMR9_IER_C1OIE_Pos)

/**
  * @brief  CC1 Capture/Compare Interrupt Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC1_CapCmp_INT_En(__TMR__)             SET_BIT((__TMR__)->IER, TMR9_IER_C1MIE_Msk)

/**
  * @brief  CC1 Capture/Compare Interrupt Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC1_CapCmp_INT_Dis(__TMR__)            CLEAR_BIT((__TMR__)->IER, TMR9_IER_C1MIE_Msk)

/**
  * @brief  Judge is CC1 Capture/Compare Interrupt Enable or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 CC1 Capture/Compare Interrupt is Disable
  * @retval 1 CC1 Capture/Compare Interrupt is Enable
  */
#define __LL_TMR_CC1_IsCapCmpIntEn(__TMR__)             READ_BIT_SHIFT((__TMR__)->IER, TMR9_IER_C1MIE_Msk, TMR9_IER_C1MIE_Pos)

/**
  * @brief  CC0 OverCapture Interrupt Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC0_OverCap_INT_En(__TMR__)            SET_BIT((__TMR__)->IER, TMR9_IER_C0OIE_Msk)

/**
  * @brief  CC0 OverCapture Interrupt Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC0_OverCap_INT_Dis(__TMR__)           CLEAR_BIT((__TMR__)->IER, TMR9_IER_C0OIE_Msk)

/**
  * @brief  Judge is CC0 OverCapture Interrupt Enable or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 CC0 OverCapture Interrupt is Disable
  * @retval 1 CC0 OverCapture Interrupt is Enable
  */
#define __LL_TMR_CC0_IsOverCapIntEn(__TMR__)            READ_BIT_SHIFT((__TMR__)->IER, TMR9_IER_C0OIE_Msk, TMR9_IER_C0OIE_Pos)

/**
  * @brief  CC0 Capture/Compare Interrupt Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC0_CapCmp_INT_En(__TMR__)             SET_BIT((__TMR__)->IER, TMR9_IER_C0MIE_Msk)

/**
  * @brief  CC0 Capture/Compare Interrupt Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC0_CapCmp_INT_Dis(__TMR__)            CLEAR_BIT((__TMR__)->IER, TMR9_IER_C0MIE_Msk)

/**
  * @brief  Judge is CC0 Capture/Compare Interrupt Enable or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 CC0 Capture/Compare Interrupt is Disable
  * @retval 1 CC0 Capture/Compare Interrupt is Enable
  */
#define __LL_TMR_CC0_IsCapCmpIntEn(__TMR__)             READ_BIT_SHIFT((__TMR__)->IER, TMR9_IER_C0MIE_Msk, TMR9_IER_C0MIE_Pos)

/**
  * @brief  CCx OverCapture Interrupt Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @param  ch Capture Channel @ref TMR_CapCmpChETypeDef
  * @return None
  */
#define __LL_TMR_CCx_OverCap_INT_En(__TMR__, ch)        SET_BIT((__TMR__)->IER, TMR9_IER_C0OIE_Msk << (((uint32_t)(ch) % 4) * 2))

/**
  * @brief  CCx OverCapture Interrupt Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @param  ch Capture Channel @ref TMR_CapCmpChETypeDef
  * @return None
  */
#define __LL_TMR_CCx_OverCap_INT_Dis(__TMR__, ch)       CLEAR_BIT((__TMR__)->IER, TMR9_IER_C0OIE_Msk << (((uint32_t)(ch) % 4) * 2))

/**
  * @brief  Judge is CCx OverCapture Interrupt Enable or not
  * @param  __TMR__ Specifies TMR peripheral
  * @param  ch Capture Channel @ref TMR_CapCmpChETypeDef
  * @retval 0 CCx OverCapture Interrupt is Disable
  * @retval 1 CCx OverCapture Interrupt is Enable
  */
#define __LL_TMR_CCx_IsOverCapIntEn(__TMR__, ch)        \
        READ_BIT_SHIFT((__TMR__)->IER, TMR9_IER_C0OIE_Msk << (((uint32_t)(ch) % 4) * 2), (TMR9_IER_C0OIE_Pos + ((uint32_t)(ch) % 4) * 2))

/**
  * @brief  CCx Capture/Compare Interrupt Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @param  ch Capture/Compare Channel @ref TMR_CapCmpChETypeDef
  * @return None
  */
#define __LL_TMR_CCx_CapCmp_INT_En(__TMR__, ch)         SET_BIT((__TMR__)->IER, TMR9_IER_C0MIE_Msk << (((uint32_t)(ch) % 4) * 2))

/**
  * @brief  CCx Capture/Compare Interrupt Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @param  ch Capture/Compare Channel @ref TMR_CapCmpChETypeDef
  * @return None
  */
#define __LL_TMR_CCx_CapCmp_INT_Dis(__TMR__, ch)        CLEAR_BIT((__TMR__)->IER, TMR9_IER_C0MIE_Msk << (((uint32_t)(ch) % 4) * 2))

/**
  * @brief  Judge is CCx Capture/Compare Interrupt Enable or not
  * @param  __TMR__ Specifies TMR peripheral
  * @param  ch Capture/Compare Channel @ref TMR_CapCmpChETypeDef
  * @retval 0 CCx Capture/Compare Interrupt is Disable
  * @retval 1 CCx Capture/Compare Interrupt is Enable
  */
#define __LL_TMR_CCx_IsCapCmpIntEn(__TMR__, ch)         \
        READ_BIT_SHIFT((__TMR__)->IER, TMR9_IER_C0MIE_Msk << (((uint32_t)(ch) % 4) * 2), (TMR9_IER_C0MIE_Pos + ((uint32_t)(ch) % 4) * 2))

/**
  * @brief  All Interrupt Enable Get
  * @param  __TMR__ Specifies TMR peripheral
  * @return All Interrupt Enable
  */
#define __LL_TMR_AllIntEn_Get(__TMR__)                  READ_REG((__TMR__)->IER)


/**
  * @brief  Judge is Counter Running Done or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 Counter isn't Running
  * @retval 1 Counter is Running
  */
#define __LL_TMR_IsCntrRunning(__TMR__)                 (READ_BIT_SHIFT((__TMR__)->SR, TMR6_SR_STS_Msk, TMR6_SR_STS_Pos))

/**
  * @brief  Judge is Compare Update Done or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 Compare Update isn't Done
  * @retval 1 Compare Update is Done
  */
#define __LL_TMR_IsCmpUpdDone(__TMR__)                  (!READ_BIT_SHIFT((__TMR__)->SR, TMR6_SR_CUS_Msk, TMR6_SR_CUS_Pos))

/**
  * @brief  Judge is Period Update Done or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 Period Update isn't Done
  * @retval 1 Period Update is Done
  */
#define __LL_TMR_IsPrdUpdDone(__TMR__)                  (!READ_BIT_SHIFT((__TMR__)->SR, TMR6_SR_PUS_Msk, TMR6_SR_PUS_Pos))

/**
  * @brief  Judge is Break 1 Interrupt Pending or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 1 isn't Break 1 Interrupt Pending
  * @retval 1 is Break 1 Interrupt Pending
  */
#define __LL_TMR_IsBrk1IntPnd(__TMR__)                  READ_BIT_SHIFT((__TMR__)->SR, TMR9_SR_B1IF_Msk, TMR9_SR_B1IF_Pos)

/**
  * @brief  Break 1 Interrupt Pending Clear
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_Brk1IntPnd_Clr(__TMR__)                WRITE_REG((__TMR__)->SR, TMR9_SR_B1IF_Msk)

/**
  * @brief  Judge is System Fault Break Interrupt Pending or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 isn't System Fault Break Interrupt Pending
  * @retval 1 is System Fault Break Interrupt Pending
  */
#define __LL_TMR_IsSysFaultBrkIntPnd(__TMR__)           READ_BIT_SHIFT((__TMR__)->SR, TMR9_SR_SBIF_Msk, TMR9_SR_SBIF_Pos)

/**
  * @brief  System Fault Break Interrupt Pending Clear
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_SysFaultBrkIntPnd_Clr(__TMR__)         WRITE_REG((__TMR__)->SR, TMR9_SR_SBIF_Msk)

/**
  * @brief  Judge is Break 0 Interrupt Pending or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 isn't Break 0 Interrupt Pending
  * @retval 1 is Break 0 Interrupt Pending
  */
#define __LL_TMR_IsBrk0IntPnd(__TMR__)                  READ_BIT_SHIFT((__TMR__)->SR, TMR9_SR_B0IF_Msk, TMR9_SR_B0IF_Pos)

/**
  * @brief  Break 0 Interrupt Pending Clear
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_Brk0IntPnd_Clr(__TMR__)                WRITE_REG((__TMR__)->SR, TMR9_SR_B0IF_Msk)

/**
  * @brief  Judge is Trigger Interrupt Pending or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 isn't Trigger Interrupt Pending
  * @retval 1 is Trigger Interrupt Pending
  */
#define __LL_TMR_IsTrigIntPnd(__TMR__)                  READ_BIT_SHIFT((__TMR__)->SR, TMR9_SR_TIF_Msk, TMR9_SR_TIF_Pos)

/**
  * @brief  Trigger Interrupt Pending Clear
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_TrigIntPnd_Clr(__TMR__)                WRITE_REG((__TMR__)->SR, TMR9_SR_TIF_Msk)

/**
  * @brief  Judge is Overflow Interrupt Pending or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 isn't Overflow Interrupt Pending
  * @retval 1 is Overflow Interrupt Pending
  */
#define __LL_TMR_IsOverflowIntPnd(__TMR__)              READ_BIT_SHIFT((__TMR__)->SR, TMR9_SR_OVIF_Msk, TMR9_SR_OVIF_Pos)

/**
  * @brief  Overflow Interrupt Pending Clear
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_OverflowIntPnd_Clr(__TMR__)            WRITE_REG((__TMR__)->SR, TMR9_SR_OVIF_Msk)

/**
  * @brief  Judge is Update Interrupt Pending or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 isn't Update Interrupt Pending
  * @retval 1 is Update Interrupt Pending
  */
#define __LL_TMR_IsUpdateIntPnd(__TMR__)                READ_BIT_SHIFT((__TMR__)->SR, TMR9_SR_UIF_Msk, TMR9_SR_UIF_Pos)

/**
  * @brief  Update Interrupt Pending Clear
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_UpdateIntPnd_Clr(__TMR__)              WRITE_REG((__TMR__)->SR, TMR9_SR_UIF_Msk)

/**
  * @brief  Judge is CC3 OverCapture Interrupt Pending or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 isn't CC3 OverCapture Interrupt Pending
  * @retval 1 is CC3 OverCapture Interrupt Pending
  */
#define __LL_TMR_CC3_IsOverCapIntPnd(__TMR__)           READ_BIT_SHIFT((__TMR__)->SR, TMR9_SR_CC3OIF_Msk, TMR9_SR_CC3OIF_Pos)

/**
  * @brief  CC3 OverCapture Interrupt Pending Clear
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC3_OverCapIntPnd_Clr(__TMR__)         WRITE_REG((__TMR__)->SR, TMR9_SR_CC3OIF_Msk)

/**
  * @brief  Judge is CC3 Capture/Compare Interrupt Pending or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 isn't CC3 Capture/Compare Interrupt Pending
  * @retval 1 is CC3 Capture/Compare Interrupt Pending
  */
#define __LL_TMR_CC3_IsCapCmpIntPnd(__TMR__)            READ_BIT_SHIFT((__TMR__)->SR, TMR9_SR_CC3MIF_Msk, TMR9_SR_CC3MIF_Pos)

/**
  * @brief  CC3 Capture/Compare Interrupt Pending Clear
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC3_CapCmpIntPnd_Clr(__TMR__)          WRITE_REG((__TMR__)->SR, TMR9_SR_CC3MIF_Msk)

/**
  * @brief  Judge is CC2 OverCapture Interrupt Pending or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 isn't CC2 OverCapture Interrupt Pending
  * @retval 1 is CC2 OverCapture Interrupt Pending
  */
#define __LL_TMR_CC2_IsOverCapIntPnd(__TMR__)           READ_BIT_SHIFT((__TMR__)->SR, TMR9_SR_CC2OIF_Msk, TMR9_SR_CC2OIF_Pos)

/**
  * @brief  CC2 OverCapture Interrupt Pending Clear
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC2_OverCapIntPnd_Clr(__TMR__)         WRITE_REG((__TMR__)->SR, TMR9_SR_CC2OIF_Msk)

/**
  * @brief  Judge is CC2 Capture/Compare Interrupt Pending or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 isn't CC2 Capture/Compare Interrupt Pending
  * @retval 1 is CC2 Capture/Compare Interrupt Pending
  */
#define __LL_TMR_CC2_IsCapCmpIntPnd(__TMR__)            READ_BIT_SHIFT((__TMR__)->SR, TMR9_SR_CC2MIF_Msk, TMR9_SR_CC2MIF_Pos)

/**
  * @brief  CC2 Capture/Compare Interrupt Pending Clear
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC2_CapCmpIntPnd_Clr(__TMR__)          WRITE_REG((__TMR__)->SR, TMR9_SR_CC2MIF_Msk)

/**
  * @brief  Judge is CC1 OverCapture Interrupt Pending or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 isn't CC1 OverCapture Interrupt Pending
  * @retval 1 is CC1 OverCapture Interrupt Pending
  */
#define __LL_TMR_CC1_IsOverCapIntPnd(__TMR__)           READ_BIT_SHIFT((__TMR__)->SR, TMR9_SR_CC1OIF_Msk, TMR9_SR_CC1OIF_Pos)

/**
  * @brief  CC1 OverCapture Interrupt Pending Clear
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC1_OverCapIntPnd_Clr(__TMR__)         WRITE_REG((__TMR__)->SR, TMR9_SR_CC1OIF_Msk)

/**
  * @brief  Judge is CC1 Capture/Compare Interrupt Pending or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 isn't CC1 Capture/Compare Interrupt Pending
  * @retval 1 is CC1 Capture/Compare Interrupt Pending
  */
#define __LL_TMR_CC1_IsCapCmpIntPnd(__TMR__)            READ_BIT_SHIFT((__TMR__)->SR, TMR9_SR_CC1MIF_Msk, TMR9_SR_CC1MIF_Pos)

/**
  * @brief  CC1 Capture/Compare Interrupt Pending Clear
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC1_CapCmpIntPnd_Clr(__TMR__)          WRITE_REG((__TMR__)->SR, TMR9_SR_CC1MIF_Msk)

/**
  * @brief  Judge is CC0 OverCapture Interrupt Pending or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 isn't CC0 OverCapture Interrupt Pending
  * @retval 1 is CC0 OverCapture Interrupt Pending
  */
#define __LL_TMR_CC0_IsOverCapIntPnd(__TMR__)           READ_BIT_SHIFT((__TMR__)->SR, TMR9_SR_CC0OIF_Msk, TMR9_SR_CC0OIF_Pos)

/**
  * @brief  CC0 OverCapture Interrupt Pending Clear
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC0_OverCapIntPnd_Clr(__TMR__)         WRITE_REG((__TMR__)->SR, TMR9_SR_CC0OIF_Msk)

/**
  * @brief  Judge is CC0 Capture/Compare Interrupt Pending or not
  * @param  __TMR__ Specifies TMR peripheral
  * @retval 0 isn't CC0 Capture/Compare Interrupt Pending
  * @retval 1 is CC0 Capture/Compare Interrupt Pending
  */
#define __LL_TMR_CC0_IsCapCmpIntPnd(__TMR__)            READ_BIT_SHIFT((__TMR__)->SR, TMR9_SR_CC0MIF_Msk, TMR9_SR_CC0MIF_Pos)

/**
  * @brief  CC0 Capture/Compare Interrupt Pending Clear
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC0_CapCmpIntPnd_Clr(__TMR__)          WRITE_REG((__TMR__)->SR, TMR9_SR_CC0MIF_Msk)

/**
  * @brief  Judge is CCx OverCapture Interrupt Pending or not
  * @param  __TMR__ Specifies TMR peripheral
  * @param  ch Capture Channel @ref TMR_CapCmpChETypeDef
  * @retval 0 isn't CCx OverCapture Interrupt Pending
  * @retval 1 is CCx OverCapture Interrupt Pending
  */
#define __LL_TMR_CCx_IsOverCapIntPnd(__TMR__, ch)       \
        READ_BIT_SHIFT((__TMR__)->SR, TMR9_SR_CC0OIF_Msk << (((uint32_t)(ch) % 4) * 2), (TMR9_SR_CC0OIF_Pos + ((uint32_t)(ch) % 4) * 2))

/**
  * @brief  CCx OverCapture Interrupt Pending Clear
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CCx_OverCapIntPnd_Clr(__TMR__, ch)     WRITE_REG((__TMR__)->SR, TMR9_SR_CC0OIF_Msk << (((uint32_t)(ch) % 4) * 2))

/**
  * @brief  Judge is CCx Capture/Compare Interrupt Pending or not
  * @param  __TMR__ Specifies TMR peripheral
  * @param  ch Capture/Compare Channel @ref TMR_CapCmpChETypeDef
  * @retval 0 isn't CCx Capture/Compare Interrupt Pending
  * @retval 1 is CCx Capture/Compare Interrupt Pending
  */
#define __LL_TMR_CCx_IsCapCmpIntPnd(__TMR__, ch)        \
        READ_BIT_SHIFT((__TMR__)->SR, TMR9_SR_CC0MIF_Msk << (((uint32_t)(ch) % 4) * 2), (TMR9_SR_CC0MIF_Pos + ((uint32_t)(ch) % 4) * 2))

/**
  * @brief  CCx Capture/Compare Interrupt Pending Clear
  * @param  __TMR__ Specifies TMR peripheral
  * @param  ch Capture/Compare Channel @ref TMR_CapCmpChETypeDef
  * @return None
  */
#define __LL_TMR_CCx_CapCmpIntPnd_Clr(__TMR__, ch)      WRITE_REG((__TMR__)->SR, TMR9_SR_CC0MIF_Msk << (((uint32_t)(ch) % 4) * 2))

/**
  * @brief  All Interrupt Pending Get
  * @param  __TMR__ Specifies TMR peripheral
  * @return All Interrupt Pending
  */
#define __LL_TMR_AllIntPnd_Get(__TMR__)                 READ_REG((__TMR__)->SR)

/**
  * @brief  Counter Start Generation
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CntrStart_Gen(__TMR__)                 SET_BIT((__TMR__)->UGR, TMR6_UGR_SG_Msk)

/**
  * @brief  Judge is Counter Start Generate or not 
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_IsCntrStartGen(__TMR__)                READ_BIT_SHIFT((__TMR__)->UGR, TMR6_UGR_SG_Msk, TMR6_UGR_SG_Pos)

/**
  * @brief  CC3 Capture/Compare Update Event Generation
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC3_CapCmpUpdateEvt_Gen(__TMR__)       SET_BIT((__TMR__)->UGR, TMR9_UGR_CC3UG_Msk)

/**
  * @brief  CC2 Capture/Compare Update Event Generation
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC2_CapCmpUpdateEvt_Gen(__TMR__)       SET_BIT((__TMR__)->UGR, TMR9_UGR_CC2UG_Msk)

/**
  * @brief  CC1 Capture/Compare Update Event Generation
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC1_CapCmpUpdateEvt_Gen(__TMR__)       SET_BIT((__TMR__)->UGR, TMR9_UGR_CC1UG_Msk)

/**
  * @brief  CC0 Capture/Compare Update Event Generation
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC0_CapCmpUpdateEvt_Gen(__TMR__)       SET_BIT((__TMR__)->UGR, TMR9_UGR_CC0UG_Msk)

/**
  * @brief  CCx Capture/Compare Update Event Generation
  * @param  __TMR__ Specifies TMR peripheral
  * @param  ch Capture/Compare Channel @ref TMR_CapCmpChETypeDef
  * @return None
  */
#define __LL_TMR_CCx_CapCmpUpdateEvt_Gen(__TMR__, ch)   SET_BIT((__TMR__)->UGR, TMR9_UGR_CC0UG_Msk << ((uint32_t)(ch) % 4))

/**
  * @brief  Break 1 Event Generation
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_Brk1Evt_Gen(__TMR__)                    SET_BIT((__TMR__)->UGR, TMR9_UGR_B1G_Msk)

/**
  * @brief  Break 0 Event Generation
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_Brk0Evt_Gen(__TMR__)                    SET_BIT((__TMR__)->UGR, TMR9_UGR_B0G_Msk)

/**
  * @brief  Trigger Event Generation
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_TrigEvt_Gen(__TMR__)                   SET_BIT((__TMR__)->UGR, TMR9_UGR_TG_Msk)

/**
  * @brief  Update Event Generation
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_UpdateEvt_Gen(__TMR__)                 SET_BIT((__TMR__)->UGR, TMR9_UGR_UG_Msk)

/**
  * @brief  Event X Generation
  * @param  __TMR__ Specifies TMR peripheral
  * @param  evtx Event X @ref TMR_EvtGenETypeDef
  * @return None
  */
#define __LL_TMR_EvtX_Gen(__TMR__, evtx)                SET_BIT((__TMR__)->UGR, BIT(((evtx) % TMR_EVT_GEN_NUMS)))


/**
  * @brief  CC3 Capture Filter Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  fil CC3 Capture Filter
  * @return None
  */
#define __LL_TMR_CC3_CapFil_Set(__TMR__, fil)           \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_OC3M_Msk, (((fil) & 0xfUL) << TMR9_CCMR_OC3M_Pos))

/**
  * @brief  CC3 Compare Mode Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  mode CC3 Compare Mode
  * @return None
  */
#define __LL_TMR_CC3_CmpMode_Set(__TMR__, mode)         \
    MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_OC3M_Msk, (((mode) & 0xfUL) << TMR9_CCMR_OC3M_Pos))

/**
  * @brief  CC3 Capture Prescaler Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  prd CC3 Capture Prescaler
  * @return None
  */
#define __LL_TMR_CC3_CapPrescaler_Set(__TMR__, prd)     \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_CC3PE_Msk, (((prd) & 0x3UL) << TMR9_CCMR_CC3PE_Pos))

/**
  * @brief  CC3 Compare Auto-Realod Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC3_CmpAutoPreload_En(__TMR__)         \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_CC3PE_Msk, (0x1UL << TMR9_CCMR_CC3PE_Pos))

/**
  * @brief  CC3 Compare Auto-Realod Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC3_CmpAutoPreload_Dis(__TMR__)        \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_CC3PE_Msk, (0x0UL << TMR9_CCMR_CC3PE_Pos))

/**
  * @brief  CC3 Capture/Compare Direction Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  dir CC3 Capture/Compare Direction
  * @return None
  */
#define __LL_TMR_CC3_CapCmpDir_Set(__TMR__, dir)        \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_CC3S_Msk, (((dir) & 0x3UL) << TMR9_CCMR_CC3S_Pos))

/**
  * @brief  CC2 Capture Filter Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  fil CC2 Capture Filter
  * @return None
  */
#define __LL_TMR_CC2_CapFil_Set(__TMR__, fil)           \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_OC2M_Msk, (((fil) & 0xfUL) << TMR9_CCMR_OC2M_Pos))

/**
  * @brief  CC2 Compare Mode Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  mode CC2 Compare Mode
  * @return None
  */
#define __LL_TMR_CC2_CmpMode_Set(__TMR__, mode)         \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_OC2M_Msk, (((mode) & 0xfUL) << TMR9_CCMR_OC2M_Pos))

/**
  * @brief  CC2 Capture Prescaler Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  prd CC2 Capture Prescaler
  * @return None
  */
#define __LL_TMR_CC2_CapPrescaler_Set(__TMR__, prd)     \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_CC2PE_Msk, (((prd) & 0x3UL) << TMR9_CCMR_CC2PE_Pos))

/**
  * @brief  CC2 Compare Auto-Realod Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC2_CmpAutoPreload_En(__TMR__)         \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_CC2PE_Msk, (0x1UL << TMR9_CCMR_CC2PE_Pos))

/**
  * @brief  CC2 Compare Auto-Realod Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC2_CmpAutoPreload_Dis(__TMR__)        \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_CC2PE_Msk, (0x0UL << TMR9_CCMR_CC2PE_Pos))

/**
  * @brief  CC2 Capture/Compare Direction Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  dir CC2 Capture/Compare Direction
  * @return None
  */
#define __LL_TMR_CC2_CapCmpDir_Set(__TMR__, dir)        \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_CC2S_Msk, (((dir) & 0x3UL) << TMR9_CCMR_CC2S_Pos))

/**
  * @brief  CC1 Capture Filter Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  fil CC1 Capture Filter
  * @return None
  */
#define __LL_TMR_CC1_CapFil_Set(__TMR__, fil)           \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_OC1M_Msk, (((fil) & 0xfUL) << TMR9_CCMR_OC1M_Pos))

/**
  * @brief  CC1 Compare Mode Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  mode CC1 Compare Mode
  * @return None
  */
#define __LL_TMR_CC1_CmpMode_Set(__TMR__, mode)         \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_OC1M_Msk, (((mode) & 0xfUL) << TMR9_CCMR_OC1M_Pos))

/**
  * @brief  CC1 Capture Prescaler Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  prd CC1 Capture Prescaler
  * @return None
  */
#define __LL_TMR_CC1_CapPrescaler_Set(__TMR__, prd)     \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_CC1PE_Msk, (((prd) & 0x3UL) << TMR9_CCMR_CC1PE_Pos))

/**
  * @brief  CC1 Compare Auto-Realod Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC1_CmpAutoPreload_En(__TMR__)         \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_CC1PE_Msk, (0x1UL << TMR9_CCMR_CC1PE_Pos))

/**
  * @brief  CC1 Compare Auto-Realod Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC1_CmpAutoPreload_Dis(__TMR__)        \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_CC1PE_Msk, (0x0UL << TMR9_CCMR_CC1PE_Pos))

/**
  * @brief  CC1 Capture/Compare Direction Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  dir CC1 Capture/Compare Direction
  * @return None
  */
#define __LL_TMR_CC1_CapCmpDir_Set(__TMR__, dir)        \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_CC1S_Msk, (((dir) & 0x3UL) << TMR9_CCMR_CC1S_Pos))

/**
  * @brief  CC0 Capture Filter Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  fil CC0 Capture Filter
  * @return None
  */
#define __LL_TMR_CC0_CapFil_Set(__TMR__, fil)           \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_OC0M_Msk, (((fil) & 0xfUL) << TMR9_CCMR_OC0M_Pos))

/**
  * @brief  CC0 Compare Mode Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  mode CC0 Compare Mode
  * @return None
  */
#define __LL_TMR_CC0_CmpMode_Set(__TMR__, mode)         \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_OC0M_Msk, (((mode) & 0xfUL) << TMR9_CCMR_OC0M_Pos))

/**
  * @brief  CC0 Capture Prescaler Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  prd CC0 Capture Prescaler
  * @return None
  */
#define __LL_TMR_CC0_CapPrescaler_Set(__TMR__, prd)     \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_CC0PE_Msk, (((prd) & 0x3UL) << TMR9_CCMR_CC0PE_Pos))

/**
  * @brief  CC0 Compare Auto-Realod Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC0_CmpAutoPreload_En(__TMR__)         \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_CC0PE_Msk, (0x1UL << TMR9_CCMR_CC0PE_Pos))

/**
  * @brief  CC0 Compare Auto-Realod Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC0_CmpAutoPreload_Dis(__TMR__)        \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_CC0PE_Msk, (0x0UL << TMR9_CCMR_CC0PE_Pos))

/**
  * @brief  CC0 Capture/Compare Direction Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  dir CC0 Capture/Compare Direction
  * @return None
  */
#define __LL_TMR_CC0_CapCmpDir_Set(__TMR__, dir)        \
        MODIFY_REG((__TMR__)->CCMR, TMR9_CCMR_CC0S_Msk, (((dir) & 0x3UL) << TMR9_CCMR_CC0S_Pos))


/**
  * @brief  CC3N Compare Polarity Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param pol CC3N Compare Polarity
  * @return None
  */
#define __LL_TMR_CC3N_CmpPol_Set(__TMR__, pol)          \
        MODIFY_REG((__TMR__)->CCER, TMR9_CCER_CC3NP_Msk, (((pol) & 0x1UL) << TMR9_CCER_CC3NP_Pos))

/**
  * @brief  CC3 Compare Polarity Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param pol CC3 Compare Polarity
  * @return None
  */
#define __LL_TMR_CC3_CmpPol_Set(__TMR__, pol)           \
        MODIFY_REG((__TMR__)->CCER, TMR9_CCER_CC3PP_Msk, (((pol) & 0x1UL) << TMR9_CCER_CC3PP_Pos))

/**
  * @brief  CC3 Capture Polarity Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  pol CC3 Capture Polarity
  * @return None
  */
#define __LL_TMR_CC3_CapPol_Set(__TMR__, pol)           \
        MODIFY_REG((__TMR__)->CCER, TMR9_CCER_CC3P_Msk, (((pol) & 0x3UL) << TMR9_CCER_CC3P_Pos))

/**
  * @brief  CC3N Compare Complementary Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC3N_Cmp_En(__TMR__)                   SET_BIT((__TMR__)->CCER, TMR9_CCER_CC3NE_Msk)

/**
  * @brief  CC3N Compare Complementary Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC3N_Cmp_Dis(__TMR__)                  CLEAR_BIT((__TMR__)->CCER, TMR9_CCER_CC3NE_Msk)

/**
  * @brief  CC3 Compare Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC3_Cmp_En(__TMR__)                    SET_BIT((__TMR__)->CCER, TMR9_CCER_CC3E_Msk)

/**
  * @brief  CC3 Compare Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC3_Cmp_Dis(__TMR__)                   CLEAR_BIT((__TMR__)->CCER, TMR9_CCER_CC3E_Msk)

/**
  * @brief  CC3 Capture Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC3_Cap_En(__TMR__)                    SET_BIT((__TMR__)->CCER, TMR9_CCER_CC3E_Msk)

/**
  * @brief  CC3 Capture Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC3_Cap_Dis(__TMR__)                   CLEAR_BIT((__TMR__)->CCER, TMR9_CCER_CC3E_Msk)

/**
  * @brief  CC2N Compare Polarity Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param pol CC2N Compare Polarity
  * @return None
  */
#define __LL_TMR_CC2N_CmpPol_Set(__TMR__, pol)          \
        MODIFY_REG((__TMR__)->CCER, TMR9_CCER_CC2NP_Msk, (((pol) & 0x1UL) << TMR9_CCER_CC2NP_Pos))

/**
  * @brief  CC2 Compare Polarity Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param pol CC2 Compare Polarity
  * @return None
  */
#define __LL_TMR_CC2_CmpPol_Set(__TMR__, pol)           \
        MODIFY_REG((__TMR__)->CCER, TMR9_CCER_CC2PP_Msk, (((pol) & 0x1UL) << TMR9_CCER_CC2PP_Pos))

/**
  * @brief  CC2 Capture Polarity Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  pol CC2 Capture Polarity
  * @return None
  */
#define __LL_TMR_CC2_CapPol_Set(__TMR__, pol)           \
        MODIFY_REG((__TMR__)->CCER, TMR9_CCER_CC2P_Msk, (((pol) & 0x3UL) << TMR9_CCER_CC2P_Pos))

/**
  * @brief  CC2N Compare Complementary Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC2N_Cmp_En(__TMR__)                   SET_BIT((__TMR__)->CCER, TMR9_CCER_CC2NE_Msk)

/**
  * @brief  CC2N Compare Complementary Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC2N_Cmp_Dis(__TMR__)                  CLEAR_BIT((__TMR__)->CCER, TMR9_CCER_CC2NE_Msk)

/**
  * @brief  CC2 Compare Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC2_Cmp_En(__TMR__)                    SET_BIT((__TMR__)->CCER, TMR9_CCER_CC2E_Msk)

/**
  * @brief  CC2 Compare Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC2_Cmp_Dis(__TMR__)                   CLEAR_BIT((__TMR__)->CCER, TMR9_CCER_CC2E_Msk)

/**
  * @brief  CC2 Capture Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC2_Cap_En(__TMR__)                    SET_BIT((__TMR__)->CCER, TMR9_CCER_CC2E_Msk)

/**
  * @brief  CC2 Capture Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC2_Cap_Dis(__TMR__)                   CLEAR_BIT((__TMR__)->CCER, TMR9_CCER_CC2E_Msk)

/**
  * @brief  CC1N Compare Polarity Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param pol CC1N Compare Polarity
  * @return None
  */
#define __LL_TMR_CC1N_CmpPol_Set(__TMR__, pol)          \
        MODIFY_REG((__TMR__)->CCER, TMR9_CCER_CC1NP_Msk, (((pol) & 0x1UL) << TMR9_CCER_CC1NP_Pos))

/**
  * @brief  CC1 Compare Polarity Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param pol CC1 Compare Polarity
  * @return None
  */
#define __LL_TMR_CC1_CmpPol_Set(__TMR__, pol)           \
        MODIFY_REG((__TMR__)->CCER, TMR9_CCER_CC1PP_Msk, (((pol) & 0x1UL) << TMR9_CCER_CC1PP_Pos))

/**
  * @brief  CC1 Capture Polarity Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  pol CC1 Capture Polarity
  * @return None
  */
#define __LL_TMR_CC1_CapPol_Set(__TMR__, pol)           \
        MODIFY_REG((__TMR__)->CCER, TMR9_CCER_CC1P_Msk, (((pol) & 0x3UL) << TMR9_CCER_CC1P_Pos))

/**
  * @brief  CC1N Compare Complementary Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC1N_Cmp_En(__TMR__)                   SET_BIT((__TMR__)->CCER, TMR9_CCER_CC1NE_Msk)

/**
  * @brief  CC1N Compare Complementary Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC1N_Cmp_Dis(__TMR__)                  CLEAR_BIT((__TMR__)->CCER, TMR9_CCER_CC1NE_Msk)

/**
  * @brief  CC1 Compare Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC1_Cmp_En(__TMR__)                    SET_BIT((__TMR__)->CCER, TMR9_CCER_CC1E_Msk)

/**
  * @brief  CC1 Compare Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC1_Cmp_Dis(__TMR__)                   CLEAR_BIT((__TMR__)->CCER, TMR9_CCER_CC1E_Msk)

/**
  * @brief  CC1 Capture Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC1_Cap_En(__TMR__)                    SET_BIT((__TMR__)->CCER, TMR9_CCER_CC1E_Msk)

/**
  * @brief  CC1 Capture Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC1_Cap_Dis(__TMR__)                   CLEAR_BIT((__TMR__)->CCER, TMR9_CCER_CC1E_Msk)

/**
  * @brief  CC0N Compare Polarity Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param pol CC0N Compare Polarity
  * @return None
  */
#define __LL_TMR_CC0N_CmpPol_Set(__TMR__, pol)          \
        MODIFY_REG((__TMR__)->CCER, TMR9_CCER_CC0NP_Msk, (((pol) & 0x1UL) << TMR9_CCER_CC0NP_Pos))

/**
  * @brief  CC0 Compare Polarity Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param pol CC0 Compare Polarity
  * @return None
  */
#define __LL_TMR_CC0_CmpPol_Set(__TMR__, pol)           \
        MODIFY_REG((__TMR__)->CCER, TMR9_CCER_CC0PP_Msk, (((pol) & 0x1UL) << TMR9_CCER_CC0PP_Pos))

/**
  * @brief  CC0 Capture Polarity Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  pol CC0 Capture Polarity
  * @return None
  */
#define __LL_TMR_CC0_CapPol_Set(__TMR__, pol)           \
        MODIFY_REG((__TMR__)->CCER, TMR9_CCER_CC0P_Msk, (((pol) & 0x3UL) << TMR9_CCER_CC0P_Pos))

/**
  * @brief  CC0N Compare Complementary Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC0N_Cmp_En(__TMR__)                   SET_BIT((__TMR__)->CCER, TMR9_CCER_CC0NE_Msk)

/**
  * @brief  CC0N Compare Complementary Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC0N_Cmp_Dis(__TMR__)                  CLEAR_BIT((__TMR__)->CCER, TMR9_CCER_CC0NE_Msk)

/**
  * @brief  CC0 Compare Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC0_Cmp_En(__TMR__)                    SET_BIT((__TMR__)->CCER, TMR9_CCER_CC0E_Msk)

/**
  * @brief  CC0 Compare Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC0_Cmp_Dis(__TMR__)                   CLEAR_BIT((__TMR__)->CCER, TMR9_CCER_CC0E_Msk)

/**
  * @brief  CC0 Capture Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC0_Cap_En(__TMR__)                    SET_BIT((__TMR__)->CCER, TMR9_CCER_CC0E_Msk)

/**
  * @brief  CC0 Capture Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CC0_Cap_Dis(__TMR__)                   CLEAR_BIT((__TMR__)->CCER, TMR9_CCER_CC0E_Msk)

/**
  * @brief  CCx Capture Polarity Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  ch Capture Channel @ref TMR_CapCmpChETypeDef
  * @param  pol CCx Capture Polarity
  * @return None
  */
#define __LL_TMR_CCx_CapPol_Set(__TMR__, ch, pol)       MODIFY_REG((__TMR__)->CCER, TMR9_CCER_CC0P_Msk << (((uint32_t)(ch) % 4) * 4),\
        (((pol) & 0x3UL) << (TMR9_CCER_CC0P_Pos + ((uint32_t)(ch) % 4) * 4)))


/**
  * @brief  Break 1 Filter Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  fil Break 1 Filter
  * @return None
  */
#define __LL_TMR_Brk1Fil_Set(__TMR__, fil)              \
        MODIFY_REG((__TMR__)->DCR, TMR9_DCR_BK1F_Msk, (((fil) & 0xffUL) << TMR9_DCR_BK1F_Pos))

/**
  * @brief  Break 1 Polarity Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  pol Break 1 Polarity
  * @return None
  */
#define __LL_TMR_Brk1Pol_Set(__TMR__, pol)              \
        MODIFY_REG((__TMR__)->DCR, TMR9_DCR_BK1P_Msk, (((pol) & 0x1UL) << TMR9_DCR_BK1P_Pos))

/**
  * @brief  Break 1 Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_Brk1_En(__TMR__)                       SET_BIT((__TMR__)->DCR, TMR9_DCR_BK1E_Msk)

/**
  * @brief  Break 1 Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_Brk1_Dis(__TMR__)                      CLEAR_BIT((__TMR__)->DCR, TMR9_DCR_BK1E_Msk)

/**
  * @brief  Break 0 Filter Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  fil Break 0 Filter
  * @return None
  */
#define __LL_TMR_Brk0Fil_Set(__TMR__, fil)              \
        MODIFY_REG((__TMR__)->DCR, TMR9_DCR_BK0F_Msk, (((fil) & 0xffUL) << TMR9_DCR_BK0F_Pos))

/**
  * @brief  Break 0 Polarity Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  pol Break 0 Polarity
  * @return None
  */
#define __LL_TMR_Brk0Pol_Set(__TMR__, pol)              \
        MODIFY_REG((__TMR__)->DCR, TMR9_DCR_BK0P_Msk, (((pol) & 0x1UL) << TMR9_DCR_BK0P_Pos))

/**
  * @brief  Break 0 Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_Brk0_En(__TMR__)                       SET_BIT((__TMR__)->DCR, TMR9_DCR_BK0E_Msk)

/**
  * @brief  Break 0 Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_Brk0_Dis(__TMR__)                      CLEAR_BIT((__TMR__)->DCR, TMR9_DCR_BK0E_Msk)

/**
  * @brief  Main Output Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_MainOutput_En(__TMR__)                 SET_BIT((__TMR__)->DCR, TMR9_DCR_MOE_Msk)

/**
  * @brief  Main Output Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_MainOutput_Dis(__TMR__)                CLEAR_BIT((__TMR__)->DCR, TMR9_DCR_MOE_Msk)

/**
  * @brief  Auto Output Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_AutoOutput_En(__TMR__)                 SET_BIT((__TMR__)->DCR, TMR9_DCR_AOE_Msk)

/**
  * @brief  Auto Output Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_AutoOutput_Dis(__TMR__)                CLEAR_BIT((__TMR__)->DCR, TMR9_DCR_AOE_Msk)

/**
  * @brief  Run Mode Off State Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  sta Run Mode Off State
  * @return None
  */
#define __LL_TMR_RunModeOffSta(__TMR__, sta)            \
        MODIFY_REG((__TMR__)->DCR, TMR9_DCR_OSSR_Msk, (((sta) & 0x1UL) << TMR9_DCR_OSSR_Pos))

/**
  * @brief  Idle Mode Off State Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  sta Idle Mode Off State
  * @return None
  */
#define __LL_TMR_IdleModeOffSta(__TMR__, sta)           \
        MODIFY_REG((__TMR__)->DCR, TMR9_DCR_OSSI_Msk, (((sta) & 0x1UL) << TMR9_DCR_OSSI_Pos))

/**
  * @brief  Dead Time Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  time Dead Time
  * @return None
  */
#define __LL_TMR_DeadTime_Set(__TMR__, time)            \
        MODIFY_REG((__TMR__)->DCR, TMR9_DCR_DTG_Msk, (((time) & 0xffUL) << TMR9_DCR_DTG_Pos))


/**
  * @brief  CH3 Trigger Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CH3_Trig_En(__TMR__)                   SET_BIT((__TMR__)->TTCR, TMR9_TTCR_TC3E_Msk)

/**
  * @brief  CH3 Trigger Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CH3_Trig_Dis(__TMR__)                  CLEAR_BIT((__TMR__)->TTCR, TMR9_TTCR_TC3E_Msk)

/**
  * @brief  CH2 Trigger Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CH2_Trig_En(__TMR__)                   SET_BIT((__TMR__)->TTCR, TMR9_TTCR_TC2E_Msk)

/**
  * @brief  CH2 Trigger Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CH2_Trig_Dis(__TMR__)                  CLEAR_BIT((__TMR__)->TTCR, TMR9_TTCR_TC2E_Msk)

/**
  * @brief  CH1 Trigger Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CH1_Trig_En(__TMR__)                   SET_BIT((__TMR__)->TTCR, TMR9_TTCR_TC1E_Msk)

/**
  * @brief  CH1 Trigger Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CH1_Trig_Dis(__TMR__)                  CLEAR_BIT((__TMR__)->TTCR, TMR9_TTCR_TC1E_Msk)

/**
  * @brief  CH0 Trigger Enable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CH0_Trig_En(__TMR__)                   SET_BIT((__TMR__)->TTCR, TMR9_TTCR_TC0E_Msk)

/**
  * @brief  CH0 Trigger Disable
  * @param  __TMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_TMR_CH0_Trig_Dis(__TMR__)                  CLEAR_BIT((__TMR__)->TTCR, TMR9_TTCR_TC0E_Msk)

/**
  * @brief  Compare/Caputre Trigger Width Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  width Compare/Caputre Trigger Width
  * @return None
  */
#define __LL_TMR_CapCmpTrigWidth_Set(__TMR__, width)    \
        MODIFY_REG((__TMR__)->TTCR, TMR9_TTCR_TCW_Msk, (((width) & 0xfUL) << TMR9_TTCR_TCW_Pos))

/**
  * @brief  Trigger Output Width Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  width Trigger Output Width
  * @return None
  */
#define __LL_TMR_TrigOutputWidth_Set(__TMR__, width)    \
        MODIFY_REG((__TMR__)->TTCR, TMR9_TTCR_TOW_Msk, (((width) & 0xfUL) << TMR9_TTCR_TOW_Pos))


/**
  * @brief  Counter Period Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  period Counter Period
  * @return None
  */
#define __LL_TMR_CounterPeriod_Set(__TMR__, period)     WRITE_REG((__TMR__)->CPR, period)

/**
  * @brief  Counter Period Get
  * @param  __TMR__ Specifies TMR peripheral
  * @return Counter Period
  */
#define __LL_TMR_CounterPeriod_Get(__TMR__)             READ_REG((__TMR__)->CPR)


/**
  * @brief  Prescaler Division Value Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  val Prescaler Division Value
  * @return None
  */
#define __LL_TMR_PrescalerDivVal_Set(__TMR__, val)      WRITE_REG((__TMR__)->PSCR, ((val) & 0xffffUL))

/**
  * @brief  Prescaler Division Value Get
  * @param  __TMR__ Specifies TMR peripheral
  * @return Prescaler Division Value
  */
#define __LL_TMR_PrescalerDivVal_Get(__TMR__)           READ_REG((__TMR__)->PSCR)


/**
  * @brief  Counter Value Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  val Counter Value
  * @return None
  */
#define __LL_TMR_CounterVal_Set(__TMR__, val)           WRITE_REG((__TMR__)->CNTR, ((val) & 0xffffUL))

/**
  * @brief  Counter Value Get
  * @param  __TMR__ Specifies TMR peripheral
  * @return Counter Value
  */
#define __LL_TMR_CounterVal_Get(__TMR__)                READ_REG((__TMR__)->CNTR)


/**
  * @brief  Counter Repeat Value Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  val Counter Repeat Value
  * @return None
  */
#define __LL_TMR_CounterRepeatVal_Set(__TMR__, val)     WRITE_REG((__TMR__)->CRR, ((val) & 0xffUL))

/**
  * @brief  Counter Repeat Value Get
  * @param  __TMR__ Specifies TMR peripheral
  * @return Counter Repeat Value
  */
#define __LL_TMR_CounterRepeatVal_Get(__TMR__)          READ_REG((__TMR__)->CRR)


/**
  * @brief  CC0 Capture Value Get
  * @param  __TMR__ Specifies TMR peripheral
  * @return CC0 Capture Value
  */
#define __LL_TMR_CC0_CapVal_Get(__TMR__)                READ_REG((__TMR__)->CC0R)

/**
  * @brief  CC0 Compare Value Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  val CC0 Compare Value
  * @return None
  */
#define __LL_TMR_CC0_CmpVal_Set(__TMR__, val)           WRITE_REG((__TMR__)->CC0R, val)

/**
  * @brief  CC0 Compare Value Get
  * @param  __TMR__ Specifies TMR peripheral
  * @return CC0 Compare Value
  */
#define __LL_TMR_CC0_CmpVal_Get(__TMR__)                READ_REG((__TMR__)->CC0R)

/**
  * @brief  CC1 Capture Value Get
  * @param  __TMR__ Specifies TMR peripheral
  * @return CC1 Capture Value
  */
#define __LL_TMR_CC1_CapVal_Get(__TMR__)                READ_REG((__TMR__)->CC1R)

/**
  * @brief  CC1 Compare Value Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  val CC1 Compare Value
  * @return None
  */
#define __LL_TMR_CC1_CmpVal_Set(__TMR__, val)           WRITE_REG((__TMR__)->CC1R, val)

/**
  * @brief  CC1 Compare Value Get
  * @param  __TMR__ Specifies TMR peripheral
  * @return CC1 Compare Value
  */
#define __LL_TMR_CC1_CmpVal_Get(__TMR__)                READ_REG((__TMR__)->CC1R)


/**
  * @brief  CC2 Capture Value Get
  * @param  __TMR__ Specifies TMR peripheral
  * @return CC2 Capture Value
  */
#define __LL_TMR_CC2_CapVal_Get(__TMR__)                READ_REG((__TMR__)->CC2R)

/**
  * @brief  CC2 Compare Value Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  val CC2 Compare Value
  * @return None
  */
#define __LL_TMR_CC2_CmpVal_Set(__TMR__, val)           WRITE_REG((__TMR__)->CC2R, val)

/**
  * @brief  CC2 Compare Value Get
  * @param  __TMR__ Specifies TMR peripheral
  * @return CC2 Compare Value
  */
#define __LL_TMR_CC2_CmpVal_Get(__TMR__)                READ_REG((__TMR__)->CC2R)


/**
  * @brief  CC3 Capture Value Get
  * @param  __TMR__ Specifies TMR peripheral
  * @return CC3 Capture Value
  */
#define __LL_TMR_CC3_CapVal_Get(__TMR__)                READ_REG((__TMR__)->CC3R)

/**
  * @brief  CC3 Compare Value Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  val CC3 Compare Value
  * @return None
  */
#define __LL_TMR_CC3_CmpVal_Set(__TMR__, val)           WRITE_REG((__TMR__)->CC3R, val)

/**
  * @brief  CC3 Compare Value Get
  * @param  __TMR__ Specifies TMR peripheral
  * @return CC3 Compare Value
  */
#define __LL_TMR_CC3_CmpVal_Get(__TMR__)                READ_REG((__TMR__)->CC3R)


/**
  * @brief  CH3 Capture Input Source Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  src CH3 Capture Input Source @ref TMR_TrigInputSrcETypeDef
  * @return None
  */
#define __LL_TMR_CH3_CapInputSrc_Set(__TMR__, src)      \
        MODIFY_REG((__TMR__)->CIR, TMR9_CIR_C3TIS_Msk, (((src) & 0xfUL) << TMR9_CIR_C3TIS_Pos))

/**
  * @brief  CH2 Capture Input Source Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  src CH2 Capture Input Source @ref TMR_TrigInputSrcETypeDef
  * @return None
  */
#define __LL_TMR_CH2_CapInputSrc_Set(__TMR__, src)      \
        MODIFY_REG((__TMR__)->CIR, TMR9_CIR_C2TIS_Msk, (((src) & 0xfUL) << TMR9_CIR_C2TIS_Pos))

/**
  * @brief  CH1 Capture Input Source Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  src CH1 Capture Input Source @ref TMR_TrigInputSrcETypeDef
  * @return None
  */
#define __LL_TMR_CH1_CapInputSrc_Set(__TMR__, src)      \
        MODIFY_REG((__TMR__)->CIR, TMR9_CIR_C1TIS_Msk, (((src) & 0xfUL) << TMR9_CIR_C1TIS_Pos))

/**
  * @brief  CH0 Capture Input Source Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  src CH0 Capture Input Source @ref TMR_TrigInputSrcETypeDef
  * @return None
  */
#define __LL_TMR_CH0_CapInputSrc_Set(__TMR__, src)      \
        MODIFY_REG((__TMR__)->CIR, TMR9_CIR_C0TIS_Msk, (((src) & 0xfUL) << TMR9_CIR_C0TIS_Pos))


/** @brief  Break1 Input Polarity Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  pol Break1 Input Polarity Mask
  * @return None
  */
#define __LL_TMR_Brk1_InputPol_Set(__TMR__, pol)        \
        MODIFY_REG((__TMR__)->BPR, TMR9_BPR_B1POL_Msk, (((pol) & 0xffffUL) << TMR9_BPR_B1POL_Pos))

/** @brief  Break0 Input Polarity Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  pol Break0 Input Polarity Mask
  * @return None
  */
#define __LL_TMR_Brk0_InputPol_Set(__TMR__, pol)        \
        MODIFY_REG((__TMR__)->BPR, TMR9_BPR_B0POL_Msk, (((pol) & 0xffffUL) << TMR9_BPR_B0POL_Pos))


/** @brief  Break 1 Input Enable Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  en Break 1 Input Enable Mask
  * @return None
  */
#define __LL_TMR_Brk1_InputEn_Set(__TMR__, en)          \
        MODIFY_REG((__TMR__)->BER, TMR9_BER_B1IEN_Msk, (((en) & 0xffffUL) << TMR9_BER_B1IEN_Pos))

/** @brief  Break 0 Input Enable Set
  * @param  __TMR__ Specifies TMR peripheral
  * @param  en Break 0 Input Enable Mask
  * @return None
  */
#define __LL_TMR_Brk0_InputEn_Set(__TMR__, en)          \
        MODIFY_REG((__TMR__)->BER, TMR9_BER_B0IEN_Msk, (((en) & 0xffffUL) << TMR9_BER_B0IEN_Pos))


/**
  * @brief  Auto Preload Enable
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_AutoPreload_En(__LPTMR__)            SET_BIT((__LPTMR__)->CR0, TMR6_CR0_ARE_Msk)

/**
  * @brief  Auto Preload Disable
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_AutoPreload_Dis(__LPTMR__)           CLEAR_BIT((__LPTMR__)->CR0, TMR6_CR0_ARE_Msk)

/**
  * @brief  Judge is Auto Preload Enable or not
  * @param  __LPTMR__ Specifies TMR peripheral
  * @retval 0 Auto Preload is Disable
  * @retval 1 Auto Preload is Enable
  */
#define __LL_LPTMR_IsAutoPreloadEn(__LPTMR__)           READ_BIT_SHIFT((__LPTMR__)->CR0, TMR6_CR0_ARE_Msk, TMR6_CR0_ARE_Pos)

/**
  * @brief  Work Mode Set
  * @param  __LPTMR__ Specifies TMR peripheral
  * @param  mode Work Mode
  * @return None
  */
#define __LL_LPTMR_WorkMode_Set(__LPTMR__, mode)        \
        MODIFY_REG((__LPTMR__)->CR0, TMR6_CR0_OPM_Msk, (((mode) & 0x1UL)<< TMR6_CR0_OPM_Pos))

/**
  * @brief  Work Mode Get
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return Work Mode
  */
#define __LL_LPTMR_WorkMode_Get(__LPTMR__)              READ_BIT_SHIFT((__LPTMR__)->CR0, TMR6_CR0_OPM_Msk, TMR6_CR0_OPM_Pos)

/**
  * @brief  Timer Enable
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_En(__LPTMR__)                        SET_BIT((__LPTMR__)->CR0, TMR6_CR0_CEN_Msk)

/**
  * @brief  Timer Disable
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_Dis(__LPTMR__)                       CLEAR_BIT((__LPTMR__)->CR0, TMR6_CR0_CEN_Msk)

/**
  * @brief  Judge is Timer Enable or not
  * @param  __LPTMR__ Specifies TMR peripheral
  * @retval 0 Timer is Disable
  * @retval 1 Timer is Enable
  */
#define __LL_LPTMR_IsEn(__LPTMR__)                      READ_BIT_SHIFT((__LPTMR__)->CR0, TMR6_CR0_CEN_Msk, TMR6_CR0_CEN_Pos)


/**
  * @brief  ETR Mode Set
  * @param  __LPTMR__ Specifies TMR peripheral
  * @param  mode ETR Mode
  * @return None
  */
#define __LL_LPTMR_ETRMode_Set(__LPTMR__, mode)         \
        MODIFY_REG((__LPTMR__)->SCR, TMR6_SCR_EE_Msk, (((mode) & 0x1UL) << TMR6_SCR_EE_Pos))

/**
  * @brief  ETR Mode Get
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return ETR Mode
  */
#define __LL_LPTMR_ETRMode_Get(__LPTMR__)               READ_BIT_SHIFT((__LPTMR__)->SCR, TMR6_SCR_EE_Msk, TMR6_SCR_EE_Pos)

/**
  * @brief  ETR Edge Mode Set
  * @param  __LPTMR__ Specifies TMR peripheral
  * @param  mode ETR Edge Mode
  * @return None
  */
#define __LL_LPTMR_ETREdgeMode_Set(__LPTMR__, mode)     \
        MODIFY_REG((__LPTMR__)->SCR, TMR6_SCR_EMS_Msk, (((mode) & 0x3UL) << TMR6_SCR_EMS_Pos))

/**
  * @brief  ETR Edge Mode Get
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return ETR Edge Mode
  */
#define __LL_LPTMR_ETREdgeMode_Get(__LPTMR__)           READ_BIT_SHIFT((__LPTMR__)->SCR, TMR6_SCR_EMS_Msk, TMR6_SCR_EMS_Pos)

/**
  * @brief  ETR Filter Set
  * @param  __LPTMR__ Specifies TMR peripheral
  * @param  fil ETR Filter
  * @return None
  */
#define __LL_LPTMR_ETRFilter_Set(__LPTMR__, fil)        \
        MODIFY_REG((__LPTMR__)->SCR, TMR6_SCR_EFS_Msk, (((fil) & 0xfUL) << TMR6_SCR_EFS_Pos))

/**
  * @brief  ETR Filter Get
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return ETR Filter
  */
#define __LL_LPTMR_ETRFilter_Get(__LPTMR__)             READ_BIT_SHIFT((__LPTMR__)->SCR, TMR6_SCR_EFS_Msk, TMR6_SCR_EFS_Pos)

/**
  * @brief  Trigger Set
  * @param  __LPTMR__ Specifies TMR peripheral
  * @param  tri Trigger
  * @return None
  */
#define __LL_LPTMR_Trigger_Set(__LPTMR__, tri)          \
        MODIFY_REG((__LPTMR__)->SCR, TMR6_SCR_TS_Msk, (((tri) & 0x1fUL) << TMR6_SCR_TS_Pos))

/**
  * @brief  Trigger Get
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return Trigger
  */
#define __LL_LPTMR_Trigger_Get(__LPTMR__)               READ_BIT_SHIFT((__LPTMR__)->SCR, TMR6_SCR_TS_Msk, TMR6_SCR_TS_Pos)

/**
  * @brief  Slave Mode Set
  * @param  __LPTMR__ Specifies TMR peripheral
  * @param  mode Slave Mode
  * @return None
  */
#define __LL_LPTMR_SlaveMode_Set(__LPTMR__, mode)       \
        MODIFY_REG((__LPTMR__)->SCR, TMR6_SCR_SMS_Msk, (((mode) & 0xfUL) << TMR6_SCR_SMS_Pos))

/**
  * @brief  Slave Mode Get
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return Slave Mode
  */
#define __LL_LPTMR_SlaveMode_Get(__LPTMR__)             READ_BIT_SHIFT((__LPTMR__)->SCR, TMR6_SCR_SMS_Msk, TMR6_SCR_SMS_Pos)


/**
  * @brief  Trigger Interrupt Enable
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_Trig_INT_En(__LPTMR__)               SET_BIT((__LPTMR__)->IER, TMR6_IER_TIE_Msk)

/**
  * @brief  Trigger Interrupt Disable
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_Trig_INT_Dis(__LPTMR__)              CLEAR_BIT((__LPTMR__)->IER, TMR6_IER_TIE_Msk)

/**
  * @brief  Judge is Trigger Interrupt Enable or not
  * @param  __LPTMR__ Specifies TMR peripheral
  * @retval 0 Trigger Interrupt is Disable
  * @retval 1 Trigger Interrupt is Enable
  */
#define __LL_LPTMR_IsTrigIntEn(__LPTMR__)               READ_BIT_SHIFT((__LPTMR__)->IER, TMR6_IER_TIE_Msk, TMR6_IER_TIE_Pos)

/**
  * @brief  Update Event Interrupt Enable
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_UpdateEvt_INT_En(__LPTMR__)          SET_BIT((__LPTMR__)->IER, TMR6_IER_UIE_Msk)

/**
  * @brief  Update Event Interrupt Disable
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_UpdateEvt_INT_Dis(__LPTMR__)         CLEAR_BIT((__LPTMR__)->IER, TMR6_IER_UIE_Msk)

/**
  * @brief  Judge is Update Event Interrupt Enable or not
  * @param  __LPTMR__ Specifies TMR peripheral
  * @retval 0 Update Event Interrupt is Disable
  * @retval 1 Update Event Interrupt is Enable
  */
#define __LL_LPTMR_IsUpdateEvtIntEn(__LPTMR__)          READ_BIT_SHIFT((__LPTMR__)->IER, TMR6_IER_UIE_Msk, TMR6_IER_UIE_Pos)

/**
  * @brief  Compare Interrupt Enable
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_Cmp_INT_En(__LPTMR__)                SET_BIT((__LPTMR__)->IER, TMR6_IER_CIE_Msk)

/**
  * @brief  Compare Interrupt Disable
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_Cmp_INT_Dis(__LPTMR__)               CLEAR_BIT((__LPTMR__)->IER, TMR6_IER_CIE_Msk)

/**
  * @brief  Judge is Compare Interrupt Enable or not
  * @param  __LPTMR__ Specifies TMR peripheral
  * @retval 0 Compare Interrupt is Disable
  * @retval 1 Compare Interrupt is Enable
  */
#define __LL_LPTMR_IsCmpIntEn(__LPTMR__)                READ_BIT_SHIFT((__LPTMR__)->IER, TMR6_IER_CIE_Msk, TMR6_IER_CIE_Pos)


/**
  * @brief  Judge is Counter Running Done or not
  * @param  __LPTMR__ Specifies TMR peripheral
  * @retval 0 Counter isn't Running
  * @retval 1 Counter is Running
  */
#define __LL_LPTMR_IsCntrRunning(__LPTMR__)             (READ_BIT_SHIFT((__LPTMR__)->SR, TMR6_SR_STS_Msk, TMR6_SR_STS_Pos))

/**
  * @brief  Judge is Compare Update Done or not
  * @param  __LPTMR__ Specifies TMR peripheral
  * @retval 0 Compare Update isn't Done
  * @retval 1 Compare Update is Done
  */
#define __LL_LPTMR_IsCmpUpdDone(__LPTMR__)              (!READ_BIT_SHIFT((__LPTMR__)->SR, TMR6_SR_CUS_Msk, TMR6_SR_CUS_Pos))

/**
  * @brief  Judge is Period Update Done or not
  * @param  __LPTMR__ Specifies TMR peripheral
  * @retval 0 Period Update isn't Done
  * @retval 1 Period Update is Done
  */
#define __LL_LPTMR_IsPrdUpdDone(__LPTMR__)              (!READ_BIT_SHIFT((__LPTMR__)->SR, TMR6_SR_PUS_Msk, TMR6_SR_PUS_Pos))

/**
  * @brief  Judge is Trigger Interrupt Pending or not
  * @param  __LPTMR__ Specifies TMR peripheral
  * @retval 0 isn't Trigger Interrupt Pending
  * @retval 1 is Trigger Interrupt Pending
  */
#define __LL_LPTMR_IsTrigIntPnd(__LPTMR__)              READ_BIT_SHIFT((__LPTMR__)->SR, TMR6_SR_TIF_Msk, TMR6_SR_TIF_Pos)

/**
  * @brief  Trigger Interrupt Pending Clear
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_TrigIntPnd_Clr(__LPTMR__)            WRITE_REG((__LPTMR__)->SR, TMR6_SR_TIF_Msk)

/**
  * @brief  Judge is Update Interrupt Pending or not
  * @param  __LPTMR__ Specifies TMR peripheral
  * @retval 0 isn't Update Interrupt Pending
  * @retval 1 is Update Interrupt Pending
  */
#define __LL_LPTMR_IsUpdateIntPnd(__LPTMR__)            READ_BIT_SHIFT((__LPTMR__)->SR, TMR6_SR_UIF_Msk, TMR6_SR_UIF_Pos)

/**
  * @brief  Update Interrupt Pending Clear
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_UpdateIntPnd_Clr(__LPTMR__)          WRITE_REG((__LPTMR__)->SR, TMR6_SR_UIF_Msk)

/**
  * @brief  Judge is Compare Interrupt Pending or not
  * @param  __LPTMR__ Specifies TMR peripheral
  * @retval 0 isn't Compare Interrupt Pending
  * @retval 1 is Compare Interrupt Pending
  */
#define __LL_LPTMR_IsCmpIntPnd(__LPTMR__)               READ_BIT_SHIFT((__LPTMR__)->SR, TMR6_SR_CIF_Msk, TMR6_SR_CIF_Pos)

/**
  * @brief  Compare Interrupt Pending Clear
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_CmpIntPnd_Clr(__LPTMR__)             WRITE_REG((__LPTMR__)->SR, TMR6_SR_CIF_Msk)


/**
  * @brief  Counter Start Generation
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_CntrStart_Gen(__LPTMR__)             SET_BIT((__LPTMR__)->UGR, TMR6_UGR_SG_Msk)

/**
  * @brief  Judge is Counter Start Generate or not 
  * @param  __LPTMR__ Specifies TMR peripheral
  * @retval 0 Counter isn't Starting
  * @retval 1 Counter is Starting
  */
#define __LL_LPTMR_IsCntrStartGen(__LPTMR__)            READ_BIT_SHIFT((__LPTMR__)->UGR, TMR6_UGR_SG_Msk, TMR6_UGR_SG_Pos)

/**
  * @brief  Compare Update Event Generation
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_CmpUpdateEvt_Gen(__LPTMR__)          SET_BIT((__LPTMR__)->UGR, TMR6_UGR_CG_Msk)

/**
  * @brief  Compare Update Event Status Get
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return Compare Update Event Status
  */
#define __LL_LPTMR_CmpUpdateEvtSta_Get(__LPTMR__)       READ_BIT_SHIFT((__LPTMR__)->UGR, TMR6_UGR_CG_Msk, TMR6_UGR_CG_Pos)

/**
  * @brief  Trigger Event Generation
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_TrigEvt_Gen(__LPTMR__)               SET_BIT((__LPTMR__)->UGR, TMR6_UGR_TG_Msk)

/**
  * @brief  Update Event Generation
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_UpdateEvt_Gen(__LPTMR__)             SET_BIT((__LPTMR__)->UGR, TMR6_UGR_UG_Msk)

/**
  * @brief  Event X Generation
  * @param  __LPTMR__ Specifies TMR peripheral
  * @param  evtx Event X @ref TMR_EvtGenETypeDef
  * @return None
  */
#define __LL_LPTMR_EvtX_Gen(__LPTMR__, evtx)            SET_BIT((__LPTMR__)->UGR, BIT(((evtx) % TMR_EVT_GEN_NUMS)))


/**
  * @brief  Compare Auto-Realod Enable
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_CmpAutoPreload_En(__LPTMR__)         \
        MODIFY_REG((__LPTMR__)->CCMR, TMR6_CCMR_RLD_Msk, (0x1UL << TMR6_CCMR_RLD_Pos))

/**
  * @brief  Compare Auto-Realod Disable
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_CmpAutoPreload_Dis(__LPTMR__)        \
        MODIFY_REG((__LPTMR__)->CCMR, TMR6_CCMR_RLD_Msk, (0x0UL << TMR6_CCMR_RLD_Pos))

/**
  * @brief  Judge is Compare Auto-Realod Enable or not
  * @param  __LPTMR__ Specifies TMR peripheral
  * @retval 0 isn't Compare Auto-Realod Enable
  * @retval 1 is Compare Auto-Realod Enable
  */
#define __LL_LPTMR_IsCmpAutoPreloadEn(__LPTMR__)         \
        READ_BIT_SHIFT((__LPTMR__)->CCMR, TMR6_CCMR_RLD_Msk, TMR6_CCMR_RLD_Pos)


/**
  * @brief  Compare Polarity Set
  * @param  __LPTMR__ Specifies TMR peripheral
  * @param  pol Compare Polarity @TMR_CmpPolETypeDef
  * @return None
  */
#define __LL_LPTMR_CmpPol_Set(__LPTMR__, pol)           \
        MODIFY_REG((__LPTMR__)->CCER, TMR6_CCER_CCP_Msk, (((pol) & 0x1UL) << TMR6_CCER_CCP_Pos))

/**
  * @brief  Compare Polarity Get
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return Compare Polarity
  */
#define __LL_LPTMR_CmpPol_Get(__LPTMR__)                READ_BIT_SHIFT((__LPTMR__)->CCER, TMR6_CCER_CCP_Msk, TMR6_CCER_CCP_Pos)

/**
  * @brief  Compare Enable
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_Cmp_En(__LPTMR__)                    SET_BIT((__LPTMR__)->CCER, TMR6_CCER_CCE_Msk)

/**
  * @brief  Compare Disable
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return None
  */
#define __LL_LPTMR_Cmp_Dis(__LPTMR__)                   CLEAR_BIT((__LPTMR__)->CCER, TMR6_CCER_CCE_Msk)

/**
  * @brief  Judge is Compare Enable or not 
  * @param  __LPTMR__ Specifies TMR peripheral
  * @retval 0 isn't Compare Enable
  * @retval 1 is Compare Enable
  */
#define __LL_LPTMR_IsCmpEn(__LPTMR__)                   READ_BIT_SHIFT((__LPTMR__)->CCER, TMR6_CCER_CCE_Msk, TMR6_CCER_CCE_Pos)


/**
  * @brief  Counter Period Set
  * @param  __LPTMR__ Specifies TMR peripheral
  * @param  period Counter Period
  * @return None
  */
#define __LL_LPTMR_CounterPeriod_Set(__LPTMR__, period) \
        MODIFY_REG((__LPTMR__)->CPR, TMR6_CPR_CPV_Msk, (((period) & 0xffffUL) << TMR6_CPR_CPV_Pos))

/**
  * @brief  Counter Period Get
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return Counter Period
  */
#define __LL_LPTMR_CounterPeriod_Get(__LPTMR__)         READ_BIT_SHIFT((__LPTMR__)->CPR, TMR6_CPR_CPV_Msk, TMR6_CPR_CPV_Pos)


/**
  * @brief  Prescaler Division Value Set
  * @param  __LPTMR__ Specifies TMR peripheral
  * @param  val Prescaler Division Value
  * @return None
  */
#define __LL_LPTMR_PrescalerDivVal_Set(__LPTMR__, val)  \
        MODIFY_REG((__LPTMR__)->PSCR, TMR6_PSCR_PSC_Msk, (((val) & 0xffUL) << TMR6_PSCR_PSC_Pos))

/**
  * @brief  Prescaler Division Value Get
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return Prescaler Division Value
  */
#define __LL_LPTMR_PrescalerDivVal_Get(__LPTMR__)       READ_BIT_SHIFT((__LPTMR__)->PSCR, TMR6_PSCR_PSC_Msk, TMR6_PSCR_PSC_Pos)


/**
  * @brief  Counter Value Set
  * @param  __LPTMR__ Specifies TMR peripheral
  * @param  val Counter Value
  * @return None
  */
#define __LL_LPTMR_CounterVal_Set(__LPTMR__, val)       MODIFY_REG((__LPTMR__)->CNTR, TMR6_CNTR_CNT_Msk, (((val) & 0xffffUL) << TMR6_CNTR_CNT_Pos))

/**
  * @brief  Counter Value Get
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return Counter Value
  */
#define __LL_LPTMR_CounterVal_Get(__LPTMR__)            READ_BIT_SHIFT((__LPTMR__)->CNTR, TMR6_CNTR_CNT_Msk, TMR6_CNTR_CNT_Pos)


/**
  * @brief  Compare Value Set
  * @param  __LPTMR__ Specifies TMR peripheral
  * @param  val Compare Value
  * @return None
  */
#define __LL_LPTMR_CmpVal_Set(__LPTMR__, val)           \
        MODIFY_REG((__LPTMR__)->CC0R, TMR6_CC0R_CMP_Msk, (((val) & 0xffffUL) << TMR6_CC0R_CMP_Pos))

/**
  * @brief  Compare Value Get
  * @param  __LPTMR__ Specifies TMR peripheral
  * @return Compare Value
  */
#define __LL_LPTMR_CmpVal_Get(__LPTMR__)                READ_BIT_SHIFT((__LPTMR__)->CC0R, TMR6_CC0R_CMP_Msk, TMR6_CC0R_CMP_Pos)


/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup TMR_LL_Exported_Types TMR LL Exported Types
  * @brief    TMR LL Exported Types
  * @{
  */

/**
  * @brief Timer Trigger Input Source Definition
  */
typedef enum {
    //TMR0_TI
    TMR0_TI0_HSE            =  0,         /*!< TMR0 TI0(Only for CH1): HSE
                                               @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR0_TI0_CMP0_OUT       =  0,         /*!< TMR0 TI0: CMP0_OUT.    */
    TMR0_TI1_CMP1_OUT       =  1,         /*!< TMR0 TI1: CMP1_OUT     */
    TMR0_TI2_CMP2_OUT       =  2,         /*!< TMR0 TI2: CMP2_OUT     */
    TMR0_TI3_CMP3_OUT       =  3,         /*!< TMR0 TI3: CMP3_OUT     */
    TMR0_TI4_CMP4_OUT       =  4,         /*!< TMR0 TI4: CMP4_OUT     */
    TMR0_TI5_CMP5_OUT       =  5,         /*!< TMR0 TI5: CMP5_OUT     */
    TMR0_TI6_CMP6_OUT       =  6,         /*!< TMR0 TI6: CMP6_OUT     */
    TMR0_TI7_CMP7_OUT       =  7,         /*!< TMR0 TI7: CMP7_OUT     */
    TMR0_TI8_CMP8_OUT       =  8,         /*!< TMR0 TI8: CMP8_OUT     */
    TMR0_TI8_HSI            =  8,         /*!< TMR0 TI8(Only for CH0): HSI
                                               @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR0_TI9_RSV,                         /*!< TMR0 TI9: Reserved     */
    TMR0_TI10_RSV,                        /*!< TMR0 TI10: Reserved    */
    TMR0_TI11_RSV,                        /*!< TMR0 TI11: Reserved    */
    TMR0_TI12_TMR0_CH0      = 12,         /*!< TMR0 TI12: TMR0_CH0    */
    TMR0_TI13_TMR0_CH1      = 13,         /*!< TMR0 TI13: TMR0_CH1    */
    TMR0_TI14_TMR0_CH0N     = 14,         /*!< TMR0 TI14: TMR0_CH0N   */
    TMR0_TI15_TMR0_CH1N     = 15,         /*!< TMR0 TI15: TMR0_CH1N   */

    //TMR1_TI
    TMR1_TI0_HSE            =  0,         /*!< TMR1 TI0(Only for CH1): HSE
                                               @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR1_TI0_CMP0_OUT       =  0,         /*!< TMR1 TI0: CMP0_OUT     */
    TMR1_TI1_CMP1_OUT       =  1,         /*!< TMR1 TI1: CMP1_OUT     */
    TMR1_TI2_CMP2_OUT       =  2,         /*!< TMR1 TI2: CMP2_OUT     */
    TMR1_TI3_CMP3_OUT       =  3,         /*!< TMR1 TI3: CMP3_OUT     */
    TMR1_TI4_CMP4_OUT       =  4,         /*!< TMR1 TI4: CMP4_OUT     */
    TMR1_TI5_CMP5_OUT       =  5,         /*!< TMR1 TI5: CMP5_OUT     */
    TMR1_TI6_CMP6_OUT       =  6,         /*!< TMR1 TI6: CMP6_OUT     */
    TMR1_TI7_CMP7_OUT       =  7,         /*!< TMR1 TI7: CMP7_OUT     */
    TMR1_TI8_CMP8_OUT       =  8,         /*!< TMR1 TI8: CMP8_OUT     */
    TMR1_TI8_HSI            =  8,         /*!< TMR1 TI8(Only for CH0): HSI
                                               @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR1_TI9_RSV,                         /*!< TMR1 TI9: Reserved     */
    TMR1_TI10_RSV,                        /*!< TMR1 TI10: Reserved    */
    TMR1_TI11_RSV,                        /*!< TMR1 TI11: Reserved    */
    TMR1_TI12_TMR1_CH0      = 12,         /*!< TMR1 TI12: TMR1_CH0    */
    TMR1_TI13_TMR1_CH1      = 13,         /*!< TMR1 TI13: TMR1_CH1    */
    TMR1_TI14_TMR1_CH0N     = 14,         /*!< TMR1 TI14: TMR1_CH0N   */
    TMR1_TI15_TMR1_CH1N     = 15,         /*!< TMR1 TI15: TMR1_CH1N   */

    //TMR2_TI
    TMR2_TI0_HSE            =  0,         /*!< TMR2 TI0(Only for CH1): HSE
                                               @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR2_TI0_CMP0_OUT       =  0,         /*!< TMR2 TI0: CMP0_OUT     */
    TMR2_TI1_CMP1_OUT       =  1,         /*!< TMR2 TI1: CMP1_OUT     */
    TMR2_TI2_CMP2_OUT       =  2,         /*!< TMR2 TI2: CMP2_OUT     */
    TMR2_TI3_CMP3_OUT       =  3,         /*!< TMR2 TI3: CMP3_OUT     */
    TMR2_TI4_CMP4_OUT       =  4,         /*!< TMR2 TI4: CMP4_OUT     */
    TMR2_TI5_CMP5_OUT       =  5,         /*!< TMR2 TI5: CMP5_OUT     */
    TMR2_TI6_CMP6_OUT       =  6,         /*!< TMR2 TI6: CMP6_OUT     */
    TMR2_TI7_CMP7_OUT       =  7,         /*!< TMR2 TI7: CMP7_OUT     */
    TMR2_TI8_CMP8_OUT       =  8,         /*!< TMR2 TI8: CMP8_OUT     */
    TMR2_TI8_HSI            =  8,         /*!< TMR2 TI8(Only for CH0): HSI
                                               @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR2_TI9_RSV,                         /*!< TMR2 TI9: Reserved     */
    TMR2_TI10_RSV,                        /*!< TMR2 TI10: Reserved    */
    TMR2_TI11_RSV,                        /*!< TMR2 TI11: Reserved    */
    TMR2_TI12_TMR2_CH0      = 12,         /*!< TMR2 TI12: TMR2_CH0    */
    TMR2_TI13_TMR2_CH1      = 13,         /*!< TMR2 TI13: TMR2_CH1    */
    TMR2_TI14_TMR2_CH0N     = 14,         /*!< TMR2 TI14: TMR2_CH0N   */
    TMR2_TI15_TMR2_CH1N     = 15,         /*!< TMR2 TI15: TMR2_CH1N   */

    //TMR3_TI
    TMR3_TI0_CMP0_OUT       =  0,         /*!< TMR3 TI0: CMP0_OUT     */
    TMR3_TI1_CMP1_OUT       =  1,         /*!< TMR3 TI1: CMP1_OUT     */
    TMR3_TI2_CMP2_OUT       =  2,         /*!< TMR3 TI2: CMP2_OUT     */
    TMR3_TI3_CMP3_OUT       =  3,         /*!< TMR3 TI3: CMP3_OUT     */
    TMR3_TI4_CMP4_OUT       =  4,         /*!< TMR3 TI4: CMP4_OUT     */
    TMR3_TI5_CMP5_OUT       =  5,         /*!< TMR3 TI5: CMP5_OUT     */
    TMR3_TI6_CMP6_OUT       =  6,         /*!< TMR3 TI6: CMP6_OUT     */
    TMR3_TI7_CMP7_OUT       =  7,         /*!< TMR3 TI7: CMP7_OUT     */
    TMR3_TI8_CMP8_OUT       =  8,         /*!< TMR3 TI8: CMP8_OUT     */
    TMR3_TI8_HSI            =  8,         /*!< TMR3 TI8(Only for CH0): HSI
                                               @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR3_TI8_HSE            =  8,         /*!< TMR3 TI8(Only for CH1): HSE
                                               @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR3_TI8_LSI            =  8,         /*!< TMR3 TI8(Only for CH2): LSI
                                               @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR3_TI9_RSV,                         /*!< TMR3 TI9: Reserved     */
    TMR3_TI10_RSV,                        /*!< TMR3 TI10: Reserved    */
    TMR3_TI11_RSV,                        /*!< TMR3 TI11: Reserved    */
    TMR3_TI12_TMR3_CH0      = 12,         /*!< TMR3 TI12: TMR3_CH0    */
    TMR3_TI13_TMR3_CH1      = 13,         /*!< TMR3 TI13: TMR3_CH1    */
    TMR3_TI14_TMR3_CH2      = 14,         /*!< TMR3 TI14: TMR3_CH2    */
    TMR3_TI15_TMR3_CH3      = 15,         /*!< TMR3 TI15: TMR3_CH3    */

    //TMR4_TI
    TMR4_TI0_CMP0_OUT       =  0,         /*!< TMR4 TI0: CMP0_OUT     */
    TMR4_TI1_CMP1_OUT       =  1,         /*!< TMR4 TI1: CMP1_OUT     */
    TMR4_TI2_CMP2_OUT       =  2,         /*!< TMR4 TI2: CMP2_OUT     */
    TMR4_TI3_CMP3_OUT       =  3,         /*!< TMR4 TI3: CMP3_OUT     */
    TMR4_TI4_CMP4_OUT       =  4,         /*!< TMR4 TI4: CMP4_OUT     */
    TMR4_TI5_CMP5_OUT       =  5,         /*!< TMR4 TI5: CMP5_OUT     */
    TMR4_TI6_CMP6_OUT       =  6,         /*!< TMR4 TI6: CMP6_OUT     */
    TMR4_TI7_CMP7_OUT       =  7,         /*!< TMR4 TI7: CMP7_OUT     */
    TMR4_TI8_CMP8_OUT       =  8,         /*!< TMR4 TI8: CMP8_OUT     */
    TMR4_TI8_HSI            =  8,         /*!< TMR4 TI8(Only for CH0): HSI
                                               @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR4_TI8_HSE            =  8,         /*!< TMR4 TI8(Only for CH1): HSE
                                               @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR4_TI8_LSI            =  8,         /*!< TMR4 TI8(Only for CH2): LSI
                                               @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR4_TI9_RSV,                         /*!< TMR4 TI9: Reserved     */
    TMR4_TI10_RSV,                        /*!< TMR4 TI10: Reserved    */
    TMR4_TI11_RSV,                        /*!< TMR4 TI11: Reserved    */
    TMR4_TI12_TMR4_CH0      = 12,         /*!< TMR4 TI12: TMR4_CH0    */
    TMR4_TI13_TMR4_CH1      = 13,         /*!< TMR4 TI13: TMR4_CH1    */
    TMR4_TI14_TMR4_CH2      = 14,         /*!< TMR4 TI14: TMR4_CH2    */
    TMR4_TI15_TMR4_CH3      = 15,         /*!< TMR4 TI15: TMR4_CH3    */

    //TMR9_TI
    TMR9_TI0_CMP0_OUT       =  0,         /*!< TMR9 TI0: CMP0_OUT     */
    TMR9_TI0_CMP8_OUT       =  0,         /*!< TMR9 TI0(Only for CH3): CMP8_OUT
                                               @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR9_TI1_CMP1_OUT       =  1,         /*!< TMR9 TI1: CMP1_OUT     */
    TMR9_TI2_CMP2_OUT       =  2,         /*!< TMR9 TI2: CMP2_OUT     */
    TMR9_TI3_CMP3_OUT       =  3,         /*!< TMR9 TI3: CMP3_OUT     */
    TMR9_TI4_CMP4_OUT       =  4,         /*!< TMR9 TI4: CMP4_OUT     */
    TMR9_TI5_CMP5_OUT       =  5,         /*!< TMR9 TI5: CMP5_OUT     */
    TMR9_TI6_CMP6_OUT       =  6,         /*!< TMR9 TI6: CMP6_OUT     */
    TMR9_TI7_CMP7_OUT       =  7,         /*!< TMR9 TI7: CMP7_OUT     */
    TMR9_TI7_HSI            =  7,         /*!< TMR9 TI7(Only for CH0): HSI
                                               @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR9_TI7_HSE            =  7,         /*!< TMR9 TI7(Only for CH1): HSE
                                               @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR9_TI7_LSI            =  7,         /*!< TMR9 TI7(Only for CH2): LSI
                                               @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR9_TI8_TMR9_CH0       =  8,         /*!< TMR9 TI8: TMR9_CH0     */
    TMR9_TI9_TMR9_CH1       =  9,         /*!< TMR9 TI9: TMR9_CH1     */
    TMR9_TI10_TMR9_CH2      = 10,         /*!< TMR9 TI10: TMR9_CH2    */
    TMR9_TI11_TMR9_CH3      = 11,         /*!< TMR9 TI11: TMR9_CH3    */
    TMR9_TI12_TMR9_CH0N     = 12,         /*!< TMR9 TI12: TMR9_CH0N   */
    TMR9_TI13_TMR9_CH1N     = 13,         /*!< TMR9 TI13: TMR9_CH1N   */
    TMR9_TI14_TMR9_CH2N     = 14,         /*!< TMR9 TI14: TMR9_CH2N   */
    TMR9_TI15_TMR9_CH3N     = 15,         /*!< TMR9 TI15: TMR9_CH3N   */

    //TMR10_TI
    TMR10_TI0_CMP0_OUT      =  0,         /*!< TMR10 TI0(Only for CH3): CMP0_OUT
                                               @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR10_TI0_CMP1_OUT      =  0,         /*!< TMR10 TI0: CMP1_OUT    */
    TMR10_TI1_CMP2_OUT      =  1,         /*!< TMR10 TI1: CMP2_OUT    */
    TMR10_TI2_CMP3_OUT      =  2,         /*!< TMR10 TI2: CMP3_OUT    */
    TMR10_TI3_CMP4_OUT      =  3,         /*!< TMR10 TI3: CMP4_OUT    */
    TMR10_TI4_CMP5_OUT      =  4,         /*!< TMR10 TI4: CMP5_OUT    */
    TMR10_TI5_CMP6_OUT      =  5,         /*!< TMR10 TI5: CMP6_OUT    */
    TMR10_TI6_CMP7_OUT      =  6,         /*!< TMR10 TI6: CMP7_OUT    */
    TMR10_TI7_CMP8_OUT      =  7,         /*!< TMR10 TI7: CMP8_OUT    */
    TMR10_TI7_HSI           =  7,         /*!< TMR10 TI7(Only for CH0): HSI
                                              @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR10_TI7_HSE           =  7,         /*!< TMR10 TI7(Only for CH1): HSE
                                              @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR10_TI7_LSI           =  7,         /*!< TMR10 TI7(Only for CH2): LSI
                                               @Note: New feature for TAE32G5800 Ver.C or higher chips.(SYSCTRL->CIDR.DCN >= 2) */
    TMR10_TI8_TMR10_CH0     =  8,         /*!< TMR10 TI8: TMR10_CH0   */
    TMR10_TI9_TMR10_CH1     =  9,         /*!< TMR10 TI9: TMR10_CH1   */
    TMR10_TI10_TMR10_CH2    = 10,         /*!< TMR10 TI10: TMR10_CH2  */
    TMR10_TI11_TMR10_CH3    = 11,         /*!< TMR10 TI11: TMR10_CH3  */
    TMR10_TI12_TMR10_CH0N   = 12,         /*!< TMR10 TI12: TMR10_CH0N */
    TMR10_TI13_TMR10_CH1N   = 13,         /*!< TMR10 TI13: TMR10_CH1N */
    TMR10_TI14_TMR10_CH2N   = 14,         /*!< TMR10 TI14: TMR10_CH2N */
    TMR10_TI15_TMR10_CH3N   = 15,         /*!< TMR10 TI15: TMR10_CH3N */
} TMR_TrigInputSrcETypeDef;

/**
  * @brief Timer Break Input Source Definition
  */
typedef enum {
    //TMR0_Break
    TMR0_BK0_CMP0_OUT   = BIT(0),       /*!< TMR0 BK0: CMP0_OUT         */
    TMR0_BK1_CMP1_OUT   = BIT(1),       /*!< TMR0 BK1: CMP1_OUT         */
    TMR0_BK2_CMP2_OUT   = BIT(2),       /*!< TMR0 BK2: CMP2_OUT         */
    TMR0_BK3_CMP3_OUT   = BIT(3),       /*!< TMR0 BK3: CMP3_OUT         */
    TMR0_BK4_CMP4_OUT   = BIT(4),       /*!< TMR0 BK4: CMP4_OUT         */
    TMR0_BK5_CMP5_OUT   = BIT(5),       /*!< TMR0 BK5: CMP5_OUT         */
    TMR0_BK6_CMP6_OUT   = BIT(6),       /*!< TMR0 BK6: CMP6_OUT         */
    TMR0_BK7_CMP7_OUT   = BIT(7),       /*!< TMR0 BK7: CMP7_OUT         */
    TMR0_BK8_CMP8_OUT   = BIT(8),       /*!< TMR0 BK8: CMP8_OUT         */
    TMR0_BK9_TMR0_BK    = BIT(9),       /*!< TMR0 BK9: TMR0_BK          */
    TMR0_BK10_ADC0_AWD0 = BIT(10),      /*!< TMR0 BK10: ADC0_AWD0       */
    TMR0_BK11_ADC1_AWD0 = BIT(11),      /*!< TMR0 BK11: ADC1_AWD0       */
    TMR0_BK12_PDM0_CMPH = BIT(12),      /*!< TMR0 BK12: PDM0_CMPH       */
    TMR0_BK13_PDM1_CMPH = BIT(13),      /*!< TMR0 BK13: PDM1_CMPH       */
    TMR0_BK14_PDM2_CMPH = BIT(14),      /*!< TMR0 BK14: PDM2_CMPH       */
    TMR0_BK15_PDM3_CMPH = BIT(15),      /*!< TMR0 BK15: PDM3_CMPH       */

    //TMR1_Break
    TMR1_BK0_CMP0_OUT   = BIT(0),       /*!< TMR1 BK0: CMP0_OUT         */
    TMR1_BK1_CMP1_OUT   = BIT(1),       /*!< TMR1 BK1: CMP1_OUT         */
    TMR1_BK2_CMP2_OUT   = BIT(2),       /*!< TMR1 BK2: CMP2_OUT         */
    TMR1_BK3_CMP3_OUT   = BIT(3),       /*!< TMR1 BK3: CMP3_OUT         */
    TMR1_BK4_CMP4_OUT   = BIT(4),       /*!< TMR1 BK4: CMP4_OUT         */
    TMR1_BK5_CMP5_OUT   = BIT(5),       /*!< TMR1 BK5: CMP5_OUT         */
    TMR1_BK6_CMP6_OUT   = BIT(6),       /*!< TMR1 BK6: CMP6_OUT         */
    TMR1_BK7_CMP7_OUT   = BIT(7),       /*!< TMR1 BK7: CMP7_OUT         */
    TMR1_BK8_CMP8_OUT   = BIT(8),       /*!< TMR1 BK8: CMP8_OUT         */
    TMR1_BK9_TMR1_BK    = BIT(9),       /*!< TMR1 BK9: TMR1_BK          */
    TMR1_BK10_ADC0_AWD0 = BIT(10),      /*!< TMR1 BK10: ADC0_AWD0       */
    TMR1_BK11_ADC1_AWD0 = BIT(11),      /*!< TMR1 BK11: ADC1_AWD0       */
    TMR1_BK12_PDM0_CMPH = BIT(12),      /*!< TMR1 BK12: PDM0_CMPH       */
    TMR1_BK13_PDM1_CMPH = BIT(13),      /*!< TMR1 BK13: PDM1_CMPH       */
    TMR1_BK14_PDM2_CMPH = BIT(14),      /*!< TMR1 BK14: PDM2_CMPH       */
    TMR1_BK15_PDM3_CMPH = BIT(15),      /*!< TMR1 BK15: PDM3_CMPH       */

    //TMR2_Break
    TMR2_BK0_CMP0_OUT   = BIT(0),       /*!< TMR2 BK0: CMP0_OUT         */
    TMR2_BK1_CMP1_OUT   = BIT(1),       /*!< TMR2 BK1: CMP1_OUT         */
    TMR2_BK2_CMP2_OUT   = BIT(2),       /*!< TMR2 BK2: CMP2_OUT         */
    TMR2_BK3_CMP3_OUT   = BIT(3),       /*!< TMR2 BK3: CMP3_OUT         */
    TMR2_BK4_CMP4_OUT   = BIT(4),       /*!< TMR2 BK4: CMP4_OUT         */
    TMR2_BK5_CMP5_OUT   = BIT(5),       /*!< TMR2 BK5: CMP5_OUT         */
    TMR2_BK6_CMP6_OUT   = BIT(6),       /*!< TMR2 BK6: CMP6_OUT         */
    TMR2_BK7_CMP7_OUT   = BIT(7),       /*!< TMR2 BK7: CMP7_OUT         */
    TMR2_BK8_CMP8_OUT   = BIT(8),       /*!< TMR2 BK8: CMP8_OUT         */
    TMR2_BK9_TMR2_BK    = BIT(9),       /*!< TMR2 BK9: TMR2_BK          */
    TMR2_BK10_ADC0_AWD0 = BIT(10),      /*!< TMR2 BK10: ADC0_AWD0       */
    TMR2_BK11_ADC1_AWD0 = BIT(11),      /*!< TMR2 BK11: ADC1_AWD0       */
    TMR2_BK12_PDM0_CMPH = BIT(12),      /*!< TMR2 BK12: PDM0_CMPH       */
    TMR2_BK13_PDM1_CMPH = BIT(13),      /*!< TMR2 BK13: PDM1_CMPH       */
    TMR2_BK14_PDM2_CMPH = BIT(14),      /*!< TMR2 BK14: PDM2_CMPH       */
    TMR2_BK15_PDM3_CMPH = BIT(15),      /*!< TMR2 BK15: PDM3_CMPH       */

    //TMR9_Break0
    TMR9_BK0_0_CMP0_OUT   = BIT(0),     /*!< TMR9 BK0_0: CMP0_OUT       */
    TMR9_BK0_1_CMP1_OUT   = BIT(1),     /*!< TMR9 BK0_1: CMP1_OUT       */
    TMR9_BK0_2_CMP2_OUT   = BIT(2),     /*!< TMR9 BK0_2: CMP2_OUT       */
    TMR9_BK0_3_CMP3_OUT   = BIT(3),     /*!< TMR9 BK0_3: CMP3_OUT       */
    TMR9_BK0_4_CMP4_OUT   = BIT(4),     /*!< TMR9 BK0_4: CMP4_OUT       */
    TMR9_BK0_5_CMP5_OUT   = BIT(5),     /*!< TMR9 BK0_5: CMP5_OUT       */
    TMR9_BK0_6_CMP6_OUT   = BIT(6),     /*!< TMR9 BK0_6: CMP6_OUT       */
    TMR9_BK0_7_CMP7_OUT   = BIT(7),     /*!< TMR9 BK0_7: CMP7_OUT       */
    TMR9_BK0_8_CMP8_OUT   = BIT(8),     /*!< TMR9 BK0_8: CMP8_OUT       */
    TMR9_BK0_9_TMR9_BK0   = BIT(9),     /*!< TMR9 BK0_9: TMR9_BK0       */
    TMR9_BK0_10_ADC0_AWD0 = BIT(10),    /*!< TMR9 BK0_10: ADC0_AWD0     */
    TMR9_BK0_11_ADC1_AWD0 = BIT(11),    /*!< TMR9 BK0_11: ADC1_AWD0     */
    TMR9_BK0_12_PDM0_CMPH = BIT(12),    /*!< TMR9 BK0_12: PDM0_CMPH     */
    TMR9_BK0_13_PDM1_CMPH = BIT(13),    /*!< TMR9 BK0_13: PDM1_CMPH     */
    TMR9_BK0_14_PDM2_CMPH = BIT(14),    /*!< TMR9 BK0_14: PDM2_CMPH     */
    TMR9_BK0_15_PDM3_CMPH = BIT(15),    /*!< TMR9 BK0_15: PDM3_CMPH     */

    //TMR9_Break1
    TMR9_BK1_0_CMP0_OUT   = BIT(0),     /*!< TMR9 BK1_0: CMP0_OUT       */
    TMR9_BK1_1_CMP1_OUT   = BIT(1),     /*!< TMR9 BK1_1: CMP1_OUT       */
    TMR9_BK1_2_CMP2_OUT   = BIT(2),     /*!< TMR9 BK1_2: CMP2_OUT       */
    TMR9_BK1_3_CMP3_OUT   = BIT(3),     /*!< TMR9 BK1_3: CMP3_OUT       */
    TMR9_BK1_4_CMP4_OUT   = BIT(4),     /*!< TMR9 BK1_4: CMP4_OUT       */
    TMR9_BK1_5_CMP5_OUT   = BIT(5),     /*!< TMR9 BK1_5: CMP5_OUT       */
    TMR9_BK1_6_CMP6_OUT   = BIT(6),     /*!< TMR9 BK1_6: CMP6_OUT       */
    TMR9_BK1_7_CMP7_OUT   = BIT(7),     /*!< TMR9 BK1_7: CMP7_OUT       */
    TMR9_BK1_8_CMP8_OUT   = BIT(8),     /*!< TMR9 BK1_8: CMP8_OUT       */
    TMR9_BK1_9_TMR9_BK1   = BIT(9),     /*!< TMR9 BK1_9: TMR9_BK1       */
    TMR9_BK1_10_ADC0_AWD0 = BIT(10),    /*!< TMR9 BK1_10: ADC0_AWD0     */
    TMR9_BK1_11_ADC1_AWD0 = BIT(11),    /*!< TMR9 BK1_11: ADC1_AWD0     */
    TMR9_BK1_12_PDM0_CMPH = BIT(12),    /*!< TMR9 BK1_12: PDM0_CMPH     */
    TMR9_BK1_13_PDM1_CMPH = BIT(13),    /*!< TMR9 BK1_13: PDM1_CMPH     */
    TMR9_BK1_14_PDM2_CMPH = BIT(14),    /*!< TMR9 BK1_14: PDM2_CMPH     */
    TMR9_BK1_15_PDM3_CMPH = BIT(15),    /*!< TMR9 BK1_15: PDM3_CMPH     */

    //TMR10_Break0
    TMR10_BK0_0_CMP0_OUT   = BIT(0),    /*!< TMR10 BK0_0: CMP0_OUT      */
    TMR10_BK0_1_CMP1_OUT   = BIT(1),    /*!< TMR10 BK0_1: CMP1_OUT      */
    TMR10_BK0_2_CMP2_OUT   = BIT(2),    /*!< TMR10 BK0_2: CMP2_OUT      */
    TMR10_BK0_3_CMP3_OUT   = BIT(3),    /*!< TMR10 BK0_3: CMP3_OUT      */
    TMR10_BK0_4_CMP4_OUT   = BIT(4),    /*!< TMR10 BK0_4: CMP4_OUT      */
    TMR10_BK0_5_CMP5_OUT   = BIT(5),    /*!< TMR10 BK0_5: CMP5_OUT      */
    TMR10_BK0_6_CMP6_OUT   = BIT(6),    /*!< TMR10 BK0_6: CMP6_OUT      */
    TMR10_BK0_7_CMP7_OUT   = BIT(7),    /*!< TMR10 BK0_7: CMP7_OUT      */
    TMR10_BK0_8_CMP8_OUT   = BIT(8),    /*!< TMR10 BK0_8: CMP8_OUT      */
    TMR10_BK0_9_TMR10_BK0  = BIT(9),    /*!< TMR10 BK0_9: TMR10_BK0     */
    TMR10_BK0_10_ADC0_AWD0 = BIT(10),   /*!< TMR10 BK0_10: ADC0_AWD0    */
    TMR10_BK0_11_ADC1_AWD0 = BIT(11),   /*!< TMR10 BK0_11: ADC1_AWD0    */
    TMR10_BK0_12_PDM0_CMPH = BIT(12),   /*!< TMR10 BK0_12: PDM0_CMPH    */
    TMR10_BK0_13_PDM1_CMPH = BIT(13),   /*!< TMR10 BK0_13: PDM1_CMPH    */
    TMR10_BK0_14_PDM2_CMPH = BIT(14),   /*!< TMR10 BK0_14: PDM2_CMPH    */
    TMR10_BK0_15_PDM3_CMPH = BIT(15),   /*!< TMR10 BK0_15: PDM3_CMPH    */

    //TMR10_Break1
    TMR10_BK1_0_CMP0_OUT   = BIT(0),    /*!< TMR10 BK1_0: CMP0_OUT      */
    TMR10_BK1_1_CMP1_OUT   = BIT(1),    /*!< TMR10 BK1_1: CMP1_OUT      */
    TMR10_BK1_2_CMP2_OUT   = BIT(2),    /*!< TMR10 BK1_2: CMP2_OUT      */
    TMR10_BK1_3_CMP3_OUT   = BIT(3),    /*!< TMR10 BK1_3: CMP3_OUT      */
    TMR10_BK1_4_CMP4_OUT   = BIT(4),    /*!< TMR10 BK1_4: CMP4_OUT      */
    TMR10_BK1_5_CMP5_OUT   = BIT(5),    /*!< TMR10 BK1_5: CMP5_OUT      */
    TMR10_BK1_6_CMP6_OUT   = BIT(6),    /*!< TMR10 BK1_6: CMP6_OUT      */
    TMR10_BK1_7_CMP7_OUT   = BIT(7),    /*!< TMR10 BK1_7: CMP7_OUT      */
    TMR10_BK1_8_CMP8_OUT   = BIT(8),    /*!< TMR10 BK1_8: CMP8_OUT      */
    TMR10_BK1_9_TMR10_BK1  = BIT(9),    /*!< TMR10 BK1_9: TMR10_BK1     */
    TMR10_BK1_10_ADC0_AWD0 = BIT(10),   /*!< TMR10 BK1_10: ADC0_AWD0    */
    TMR10_BK1_11_ADC1_AWD0 = BIT(11),   /*!< TMR10 BK1_11: ADC1_AWD0    */
    TMR10_BK1_12_PDM0_CMPH = BIT(12),   /*!< TMR10 BK1_12: PDM0_CMPH    */
    TMR10_BK1_13_PDM1_CMPH = BIT(13),   /*!< TMR10 BK1_13: PDM1_CMPH    */
    TMR10_BK1_14_PDM2_CMPH = BIT(14),   /*!< TMR10 BK1_14: PDM2_CMPH    */
    TMR10_BK1_15_PDM3_CMPH = BIT(15),   /*!< TMR10 BK1_15: PDM3_CMPH    */
} TMR_BrkInputSrcETypeDef;

/**
  * @brief Timer TI0 Input Source Definition
  */
typedef enum {
    TMR_TI0_INPUT_SRC_CH0 = 0,      /*!< TI0 Input Source CH0       */
    TMR_TI0_INPUT_SRC_CHx_XOR,      /*!< TI0 Input Source CH0~2 XOR */
} TMR_TI0InputSrcETypeDef;

/**
  * @brief Timer Dead Zone and Digital Filter Clock Division Definition
  */
typedef enum {
    TMR_DZ_DIG_FIL_CLK_DIV_1 = 0,   /*!< Dead Zone and Digital Filter Clock Division 1  */
    TMR_DZ_DIG_FIL_CLK_DIV_2,       /*!< Dead Zone and Digital Filter Clock Division 2  */
    TMR_DZ_DIG_FIL_CLK_DIV_4,       /*!< Dead Zone and Digital Filter Clock Division 4  */
    TMR_DZ_DIG_FIL_CLK_DIV_8,       /*!< Dead Zone and Digital Filter Clock Division 8  */
} TMR_DzDigFilClkDivETypeDef;

/**
  * @brief Timer Center Aligned Mode Definition
  */
typedef enum {
    TMR_CTR_ALIGN_MODE_EDGE = 0,    /*!< Center-Aligned Mode Edge   */
    TMR_CTR_ALIGN_MODE_1,           /*!< Center-Aligned Mode 1      */
    TMR_CTR_ALIGN_MODE_2,           /*!< Center-Aligned Mode 2      */
    TMR_CTR_ALIGN_MODE_3,           /*!< Center-Aligned Mode 3      */
} TMR_CtrAlignModeETypeDef;

/**
  * @brief Timer Counter Direction Definition
  */
typedef enum {
    TMR_CNT_DIR_INC = 0,            /*!< Counter Direction Increase */
    TMR_CNT_DIR_DEC,                /*!< Counter Direction Decrease */
} TMR_CntDirETypeDef;

/**
  * @brief Timer Work Mode Definition
  */
typedef enum {
    TMR_WORK_MODE_CONTINUE = 0,     /*!< Timer Work Mode Continue   */
    TMR_WORK_MODE_SINGLE,           /*!< Timer Work Mode Single     */
} TMR_WorkModeETypeDef;

/**
  * @brief Timer Update Event Source Definition
  */
typedef enum {
    TMR_UPDATE_EVT_SRC_OV_UG = 0,   /*!< Timer Update Event Source Overflow and User Generation */
    TMR_UPDATE_EVT_SRC_OV,          /*!< Timer Update Event Source Overflow                     */
} TMR_UpdateEvtSrcETypeDef;

/**
  * @brief Timer Output Idle State Definition
  */
typedef enum {
    TMR_OUTPUT_IDLE_STA_LOW = 0,    /*!<  Output Idle State Low     */
    TMR_OUTPUT_IDLE_STA_HIGH,       /*!<  Output Idle State High    */
} TMR_OutputIdleStaETypeDef;

/**
  * @brief Timer Master Mode Definition
  */
typedef enum {
    TMR_MST_MODE_RESET = 0,         /*!< Master Mode Counter Reset (UGR)    */
    TMR_MST_MODE_ENABLE,            /*!< Master Mode Counter Enable         */
    TMR_MST_MODE_UPDATE,            /*!< Master Mode Counter Update         */
    TMR_MST_MODE_CAP_CMP_EVT,       /*!< Master Mode Capture/Compare Event  */
    TMR_MST_MODE_CMP0_OUT,          /*!< Master Mode Compare0 Output        */
    TMR_MST_MODE_CMP1_OUT,          /*!< Master Mode Compare1 Output        */
    TMR_MST_MODE_CMP2_OUT,          /*!< Master Mode Compare2 Output        */
    TMR_MST_MODE_CMP3_OUT,          /*!< Master Mode Compare3 Output        */
} TMR_MstModeETypeDef;

/**
  * @brief Timer ETR Input Source Definition
  */
typedef enum {
    TMR_ETR_INPUT_SRC_PAD = 0,          /*!< ETR Input Source Pad       */

    TMR_ETR_INPUT_SRC_CMP0,             /*!< ETR Input Source CMP0      */
    TMR_ETR_INPUT_SRC_CMP1,             /*!< ETR Input Source CMP1      */
    TMR_ETR_INPUT_SRC_CMP2,             /*!< ETR Input Source CMP2      */
    TMR_ETR_INPUT_SRC_CMP3,             /*!< ETR Input Source CMP3      */
    TMR_ETR_INPUT_SRC_CMP4,             /*!< ETR Input Source CMP4      */
    TMR_ETR_INPUT_SRC_CMP5,             /*!< ETR Input Source CMP5      */
    TMR_ETR_INPUT_SRC_CMP6,             /*!< ETR Input Source CMP6      */

    TMR_ETR_INPUT_SRC_PDM0,             /*!< ETR Input Source PDM0      */
    TMR_ETR_INPUT_SRC_PDM1,             /*!< ETR Input Source PDM1      */

    TMR9_ETR_INPUT_SRC_ADC0WDG0  = 0xA, /*!< ETR Input Source ADC0WDG0  */
    TMR9_ETR_INPUT_SRC_ADC0WDG1  = 0xB, /*!< ETR Input Source ADC0WDG1  */
    TMR9_ETR_INPUT_SRC_ADC0WDG2  = 0xC, /*!< ETR Input Source ADC0WDG2  */
    TMR9_ETR_INPUT_SRC_HSE       = 0xC, /*!< ETR Input Source HSE
                                             @Note: Remark for TAE32G5800 Ver.C or higher chips only.(SYSCTRL->CIDR.DCN >= 2) */
    TMR9_ETR_INPUT_SRC_ADC1WDG0  = 0xD, /*!< ETR Input Source ADC1WDG0  */
    TMR9_ETR_INPUT_SRC_ADC1WDG1  = 0xE, /*!< ETR Input Source ADC1WDG1  */
    TMR9_ETR_INPUT_SRC_ADC1WDG2  = 0xF, /*!< ETR Input Source ADC1WDG2  */
    TMR9_ETR_INPUT_SRC_HSI       = 0xF, /*!< ETR Input Source HSI
                                             @Note: Remark for TAE32G5800 Ver.C or higher chips only.(SYSCTRL->CIDR.DCN >= 2) */

    TMR10_ETR_INPUT_SRC_ADC2WDG0 = 0xA, /*!< ETR Input Source ADC2WDG0  */
    TMR10_ETR_INPUT_SRC_ADC2WDG1 = 0xB, /*!< ETR Input Source ADC2WDG1  */
    TMR10_ETR_INPUT_SRC_ADC2WDG2 = 0xC, /*!< ETR Input Source ADC2WDG2  */
    TMR10_ETR_INPUT_SRC_HSE      = 0xC, /*!< ETR Input Source HSE
                                             @Note: Remark for TAE32G5800 Ver.C or higher chips only.(SYSCTRL->CIDR.DCN >= 2) */
    TMR10_ETR_INPUT_SRC_ADC3WDG0 = 0xD, /*!< ETR Input Source ADC3WDG0  */
    TMR10_ETR_INPUT_SRC_ADC3WDG1 = 0xE, /*!< ETR Input Source ADC3WDG1  */
    TMR10_ETR_INPUT_SRC_ADC3WDG2 = 0xF, /*!< ETR Input Source ADC3WDG2  */
    TMR10_ETR_INPUT_SRC_HSI      = 0xF, /*!< ETR Input Source HSI
                                             @Note: Remark for TAE32G5800 Ver.C or higher chips only.(SYSCTRL->CIDR.DCN >= 2) */
} TMR_ETRInputSrcETypeDef;

/**
  * @brief Timer ETR Mode Definition
  */
typedef enum {
    TMR_ETR_MODE_EXT_CLK_1 = 0,     /*!< ETR Mode External Clock Mode 1 */
    TMR_ETR_MODE_EXT_CLK_2,         /*!< ETR Mode External Clock Mode 2 */
} TMR_ETRModeETypeDef;

/**
  * @brief Timer ETR Edge Mode Definition
  */
typedef enum {
    TMR_ETR_EDGE_MODE_CLOSE = 0,        /*!< ETR Edge Mode Close                        */
    TMR_ETR_EDGE_MODE_RISING,           /*!< ETR Edge Mode Close Rising Edge            */
    TMR_ETR_EDGE_MODE_FALLING,          /*!< ETR Edge Mode Close Falling Edge           */
    TMR_ETR_EDGE_MODE_RISING_FALLING,   /*!< ETR Edge Mode Close Rising&Falling Edge    */
} TMR_ETREdgeModeETypeDef;

/**
  * @brief Timer Trigger Definition
  */
typedef enum {
    TMR_TRIG_ITR0 = 0,              /*!< Trigger ITR0                       */
    TMR_TRIG_ITR1,                  /*!< Trigger ITR1                       */
    TMR_TRIG_ITR2,                  /*!< Trigger ITR2                       */
    TMR_TRIG_ITR3,                  /*!< Trigger ITR3                       */
    TMR_TRIG_ITR4,                  /*!< Trigger ITR4                       */
    TMR_TRIG_ITR5,                  /*!< Trigger ITR5                       */
    TMR_TRIG_ITR6,                  /*!< Trigger ITR6                       */
    TMR_TRIG_ITR7,                  /*!< Trigger ITR7                       */
    TMR_TRIG_ITR8,                  /*!< Trigger ITR8                       */
    TMR_TRIG_ITR9,                  /*!< Trigger ITR9                       */
    TMR_TRIG_ITR10,                 /*!< Trigger ITR10                      */
    TMR_TRIG_ITR11,                 /*!< Trigger ITR11                      */
    TMR_TRIG_ITR12,                 /*!< Trigger ITR12                      */
    TMR_TRIG_ITR13,                 /*!< Trigger ITR13                      */
    TMR_TRIG_ITR14,                 /*!< Trigger ITR14                      */
    TMR_TRIG_ITR15,                 /*!< Trigger ITR15                      */

    TMR_TRIG_CH0_FE,                /*!< Trigger CH0_FE                     */
    TMR_TRIG_CH0_F,                 /*!< Trigger CH0_F                      */
    TMR_TRIG_CH1_F,                 /*!< Trigger CH1_F                      */
    TMR_TRIG_CH2_F,                 /*!< Trigger CH2_F                      */
    TMR_TRIG_CH3_F,                 /*!< Trigger CH3_F                      */
    TMR_TRIG_ETR_FE,                /*!< Trigger ETR_FE                     */
    TMR_TRIG_ETR_F,                 /*!< Trigger ETR_F                      */

    //TMR0_ITR
    TMR0_TRIG_ITR0_TMR7_TRGO = 0,   /*!< TMR0 Trigger ITR0: TMR7_TRGO       */
    TMR0_TRIG_ITR1_TMR8_TRGO,       /*!< TMR0 Trigger ITR1: TMR8_TRGO       */
    TMR0_TRIG_ITR2_TMR1_TRGO,       /*!< TMR0 Trigger ITR2: TMR1_TRGO       */
    TMR0_TRIG_ITR3_TMR2_TRGO,       /*!< TMR0 Trigger ITR3: TMR2_TRGO       */
    TMR0_TRIG_ITR4_TMR3_TRGO,       /*!< TMR0 Trigger ITR4: TMR3_TRGO       */
    TMR0_TRIG_ITR5_TMR4_TRGO,       /*!< TMR0 Trigger ITR5: TMR4_TRGO       */
    TMR0_TRIG_ITR6_TMR1_OC0,        /*!< TMR0 Trigger ITR6: TMR1_OC0        */
    TMR0_TRIG_ITR7_TMR2_OC0,        /*!< TMR0 Trigger ITR7: TMR2_OC0        */
    TMR0_TRIG_ITR8_TMR3_OC0,        /*!< TMR0 Trigger ITR8: TMR3_OC0        */
    TMR0_TRIG_ITR9_TMR4_OC0,        /*!< TMR0 Trigger ITR9: TMR4_OC0        */
    TMR0_TRIG_ITR10_TMR9_TRGO,      /*!< TMR0 Trigger ITR10: TMR9_TRGO      */
    TMR0_TRIG_ITR11_TMR9_OC0,       /*!< TMR0 Trigger ITR11: TMR9_OC0       */
    TMR0_TRIG_ITR12_TMR9_OC1,       /*!< TMR0 Trigger ITR12: TMR9_OC1       */
    TMR0_TRIG_ITR13_TMR10_TRGO,     /*!< TMR0 Trigger ITR13: TMR10_TRGO     */
    TMR0_TRIG_ITR14_TMR10_OC0,      /*!< TMR0 Trigger ITR14: TMR10_OC0      */
    TMR0_TRIG_ITR15_HRPWM_SYNCO,    /*!< TMR0 Trigger ITR15: HRPWM_SYNCO    */

    //TMR1_ITR
    TMR1_TRIG_ITR0_TMR7_TRGO = 0,   /*!< TMR1 Trigger ITR0: TMR7_TRGO       */
    TMR1_TRIG_ITR1_TMR8_TRGO,       /*!< TMR1 Trigger ITR1: TMR8_TRGO       */
    TMR1_TRIG_ITR2_TMR0_TRGO,       /*!< TMR1 Trigger ITR2: TMR0_TRGO       */
    TMR1_TRIG_ITR3_TMR2_TRGO,       /*!< TMR1 Trigger ITR3: TMR2_TRGO       */
    TMR1_TRIG_ITR4_TMR3_TRGO,       /*!< TMR1 Trigger ITR4: TMR3_TRGO       */
    TMR1_TRIG_ITR5_TMR4_TRGO,       /*!< TMR1 Trigger ITR5: TMR4_TRGO       */
    TMR1_TRIG_ITR6_TMR0_OC0,        /*!< TMR1 Trigger ITR6: TMR0_OC0        */
    TMR1_TRIG_ITR7_TMR2_OC0,        /*!< TMR1 Trigger ITR7: TMR2_OC0        */
    TMR1_TRIG_ITR8_TMR3_OC0,        /*!< TMR1 Trigger ITR8: TMR3_OC0        */
    TMR1_TRIG_ITR9_TMR4_OC0,        /*!< TMR1 Trigger ITR9: TMR4_OC0        */
    TMR1_TRIG_ITR10_TMR9_TRGO,      /*!< TMR1 Trigger ITR10: TMR9_TRGO      */
    TMR1_TRIG_ITR11_TMR9_OC0,       /*!< TMR1 Trigger ITR11: TMR9_OC0       */
    TMR1_TRIG_ITR12_TMR9_OC1,       /*!< TMR1 Trigger ITR12: TMR9_OC1       */
    TMR1_TRIG_ITR13_TMR10_TRGO,     /*!< TMR1 Trigger ITR13: TMR10_TRGO     */
    TMR1_TRIG_ITR14_TMR10_OC0,      /*!< TMR1 Trigger ITR14: TMR10_OC0      */
    TMR1_TRIG_ITR15_HRPWM_SYNCO,    /*!< TMR1 Trigger ITR15: HRPWM_SYNCO    */

    //TMR2_ITR
    TMR2_TRIG_ITR0_TMR7_TRGO = 0,   /*!< TMR2 Trigger ITR0: TMR7_TRGO       */
    TMR2_TRIG_ITR1_TMR8_TRGO,       /*!< TMR2 Trigger ITR1: TMR8_TRGO       */
    TMR2_TRIG_ITR2_TMR0_TRGO,       /*!< TMR2 Trigger ITR2: TMR0_TRGO       */
    TMR2_TRIG_ITR3_TMR1_TRGO,       /*!< TMR2 Trigger ITR3: TMR1_TRGO       */
    TMR2_TRIG_ITR4_TMR3_TRGO,       /*!< TMR2 Trigger ITR4: TMR3_TRGO       */
    TMR2_TRIG_ITR5_TMR4_TRGO,       /*!< TMR2 Trigger ITR5: TMR4_TRGO       */
    TMR2_TRIG_ITR6_TMR0_OC0,        /*!< TMR2 Trigger ITR6: TMR0_OC0        */
    TMR2_TRIG_ITR7_TMR1_OC0,        /*!< TMR2 Trigger ITR7: TMR1_OC0        */
    TMR2_TRIG_ITR8_TMR3_OC0,        /*!< TMR2 Trigger ITR8: TMR3_OC0        */
    TMR2_TRIG_ITR9_TMR4_OC0,        /*!< TMR2 Trigger ITR9: TMR4_OC0        */
    TMR2_TRIG_ITR10_TMR9_TRGO,      /*!< TMR2 Trigger ITR10: TMR9_TRGO      */
    TMR2_TRIG_ITR11_TMR9_OC0,       /*!< TMR2 Trigger ITR11: TMR9_OC0       */
    TMR2_TRIG_ITR12_TMR9_OC1,       /*!< TMR2 Trigger ITR12: TMR9_OC1       */
    TMR2_TRIG_ITR13_TMR10_TRGO,     /*!< TMR2 Trigger ITR13: TMR10_TRGO     */
    TMR2_TRIG_ITR14_TMR10_OC0,      /*!< TMR2 Trigger ITR14: TMR10_OC0      */
    TMR2_TRIG_ITR15_HRPWM_SYNCO,    /*!< TMR2 Trigger ITR15: HRPWM_SYNCO    */

    //TMR3_ITR
    TMR3_TRIG_ITR0_TMR7_TRGO = 0,   /*!< TMR3 Trigger ITR0: TMR7_TRGO       */
    TMR3_TRIG_ITR1_TMR8_TRGO,       /*!< TMR3 Trigger ITR1: TMR8_TRGO       */
    TMR3_TRIG_ITR2_TMR0_TRGO,       /*!< TMR3 Trigger ITR2: TMR0_TRGO       */
    TMR3_TRIG_ITR3_TMR1_TRGO,       /*!< TMR3 Trigger ITR3: TMR1_TRGO       */
    TMR3_TRIG_ITR4_TMR2_TRGO,       /*!< TMR3 Trigger ITR4: TMR2_TRGO       */
    TMR3_TRIG_ITR5_TMR4_TRGO,       /*!< TMR3 Trigger ITR5: TMR4_TRGO       */
    TMR3_TRIG_ITR6_TMR0_OC0,        /*!< TMR3 Trigger ITR6: TMR0_OC0        */
    TMR3_TRIG_ITR7_TMR1_OC0,        /*!< TMR3 Trigger ITR7: TMR1_OC0        */
    TMR3_TRIG_ITR8_TMR2_OC0,        /*!< TMR3 Trigger ITR8: TMR2_OC0        */
    TMR3_TRIG_ITR9_TMR4_OC0,        /*!< TMR3 Trigger ITR9: TMR4_OC0        */
    TMR3_TRIG_ITR10_TMR9_TRGO,      /*!< TMR3 Trigger ITR10: TMR9_TRGO      */
    TMR3_TRIG_ITR11_TMR9_OC0,       /*!< TMR3 Trigger ITR11: TMR9_OC0       */
    TMR3_TRIG_ITR12_TMR9_OC1,       /*!< TMR3 Trigger ITR12: TMR9_OC1       */
    TMR3_TRIG_ITR13_TMR10_TRGO,     /*!< TMR3 Trigger ITR13: TMR10_TRGO     */
    TMR3_TRIG_ITR14_TMR10_OC0,      /*!< TMR3 Trigger ITR14: TMR10_OC0      */
    TMR3_TRIG_ITR15_HRPWM_SYNCO,    /*!< TMR3 Trigger ITR15: HRPWM_SYNCO    */

    //TMR4_ITR
    TMR4_TRIG_ITR0_TMR7_TRGO = 0,   /*!< TMR4 Trigger ITR0: TMR7_TRGO       */
    TMR4_TRIG_ITR1_TMR8_TRGO,       /*!< TMR4 Trigger ITR1: TMR8_TRGO       */
    TMR4_TRIG_ITR2_TMR0_TRGO,       /*!< TMR4 Trigger ITR2: TMR0_TRGO       */
    TMR4_TRIG_ITR3_TMR1_TRGO,       /*!< TMR4 Trigger ITR3: TMR1_TRGO       */
    TMR4_TRIG_ITR4_TMR2_TRGO,       /*!< TMR4 Trigger ITR4: TMR2_TRGO       */
    TMR4_TRIG_ITR5_TMR3_TRGO,       /*!< TMR4 Trigger ITR5: TMR3_TRGO       */
    TMR4_TRIG_ITR6_TMR0_OC0,        /*!< TMR4 Trigger ITR6: TMR0_OC0        */
    TMR4_TRIG_ITR7_TMR1_OC0,        /*!< TMR4 Trigger ITR7: TMR1_OC0        */
    TMR4_TRIG_ITR8_TMR2_OC0,        /*!< TMR4 Trigger ITR8: TMR2_OC0        */
    TMR4_TRIG_ITR9_TMR3_OC0,        /*!< TMR4 Trigger ITR9: TMR3_OC0        */
    TMR4_TRIG_ITR10_TMR9_TRGO,      /*!< TMR4 Trigger ITR10: TMR9_TRGO      */
    TMR4_TRIG_ITR11_TMR9_OC0,       /*!< TMR4 Trigger ITR11: TMR9_OC0       */
    TMR4_TRIG_ITR12_TMR9_OC1,       /*!< TMR4 Trigger ITR12: TMR9_OC1       */
    TMR4_TRIG_ITR13_TMR10_TRGO,     /*!< TMR4 Trigger ITR13: TMR10_TRGO     */
    TMR4_TRIG_ITR14_TMR10_OC0,      /*!< TMR4 Trigger ITR14: TMR10_OC0      */
    TMR4_TRIG_ITR15_HRPWM_SYNCO,    /*!< TMR4 Trigger ITR15: HRPWM_SYNCO    */

    //TMR9_ITR
    TMR9_TRIG_ITR0_TMR7_TRGO = 0,   /*!< TMR9 Trigger ITR0: TMR7_TRGO       */
    TMR9_TRIG_ITR1_TMR8_TRGO,       /*!< TMR9 Trigger ITR1: TMR8_TRGO       */
    TMR9_TRIG_ITR2_TMR0_TRGO,       /*!< TMR9 Trigger ITR2: TMR0_TRGO       */
    TMR9_TRIG_ITR3_TMR1_TRGO,       /*!< TMR9 Trigger ITR3: TMR1_TRGO       */
    TMR9_TRIG_ITR4_TMR2_TRGO,       /*!< TMR9 Trigger ITR4: TMR2_TRGO       */
    TMR9_TRIG_ITR5_TMR3_TRGO,       /*!< TMR9 Trigger ITR5: TMR3_TRGO       */
    TMR9_TRIG_ITR6_TMR4_TRGO,       /*!< TMR9 Trigger ITR6: TMR4_TRGO       */
    TMR9_TRIG_ITR7_TMR0_OC0,        /*!< TMR9 Trigger ITR7: TMR0_OC0        */
    TMR9_TRIG_ITR8_TMR1_OC0,        /*!< TMR9 Trigger ITR8: TMR1_OC0        */
    TMR9_TRIG_ITR9_TMR2_OC0,        /*!< TMR9 Trigger ITR9: TMR2_OC0        */
    TMR9_TRIG_ITR10_TMR3_OC0,       /*!< TMR9 Trigger ITR10: TMR3_OC0       */
    TMR9_TRIG_ITR11_TMR4_OC0,       /*!< TMR9 Trigger ITR11: TMR4_OC0       */
    TMR9_TRIG_ITR12_TMR10_TRGO,     /*!< TMR9 Trigger ITR12: TMR10_TRGO     */
    TMR9_TRIG_ITR13_TMR10_OC0,      /*!< TMR9 Trigger ITR13: TMR10_OC0      */
    TMR9_TRIG_ITR14_TMR10_OC1,      /*!< TMR9 Trigger ITR14: TMR10_OC1      */
    TMR9_TRIG_ITR15_HRPWM_SYNCO,    /*!< TMR9 Trigger ITR15: HRPWM_SYNCO    */

    //TMR10_ITR
    TMR10_TRIG_ITR0_TMR7_TRGO = 0,   /*!< TMR10 Trigger ITR0: TMR7_TRGO     */
    TMR10_TRIG_ITR1_TMR8_TRGO,       /*!< TMR10 Trigger ITR1: TMR8_TRGO     */
    TMR10_TRIG_ITR2_TMR0_TRGO,       /*!< TMR10 Trigger ITR2: TMR0_TRGO     */
    TMR10_TRIG_ITR3_TMR1_TRGO,       /*!< TMR10 Trigger ITR3: TMR1_TRGO     */
    TMR10_TRIG_ITR4_TMR2_TRGO,       /*!< TMR10 Trigger ITR4: TMR2_TRGO     */
    TMR10_TRIG_ITR5_TMR3_TRGO,       /*!< TMR10 Trigger ITR5: TMR3_TRGO     */
    TMR10_TRIG_ITR6_TMR4_TRGO,       /*!< TMR10 Trigger ITR6: TMR4_TRGO     */
    TMR10_TRIG_ITR7_TMR0_OC0,        /*!< TMR10 Trigger ITR7: TMR0_OC0      */
    TMR10_TRIG_ITR8_TMR1_OC0,        /*!< TMR10 Trigger ITR8: TMR1_OC0      */
    TMR10_TRIG_ITR9_TMR2_OC0,        /*!< TMR10 Trigger ITR9: TMR2_OC0      */
    TMR10_TRIG_ITR10_TMR3_OC0,       /*!< TMR10 Trigger ITR10: TMR3_OC0     */
    TMR10_TRIG_ITR11_TMR4_OC0,       /*!< TMR10 Trigger ITR11: TMR4_OC0     */
    TMR10_TRIG_ITR12_TMR9_TRGO,      /*!< TMR10 Trigger ITR12: TMR9_TRGO    */
    TMR10_TRIG_ITR13_TMR9_OC0,       /*!< TMR10 Trigger ITR13: TMR9_OC0     */
    TMR10_TRIG_ITR14_TMR9_OC1,       /*!< TMR10 Trigger ITR14: TMR9_OC1     */
    TMR10_TRIG_ITR15_HRPWM_SYNCO,    /*!< TMR10 Trigger ITR15: HRPWM_SYNCO  */
} TMR_TrigETypeDef;

/**
  * @brief Timer Slave Mode Definition
  */
typedef enum {
    TMR_SLV_MODE_DIS = 0,           /*!< Slave Mode Disable         */
    TMR_SLV_MODE_RST = 4,           /*!< Slave Mode Reset           */
    TMR_SLV_MODE_GATING,            /*!< Slave Mode Gating          */
    TMR_SLV_MODE_TRIG,              /*!< Slave Mode Trigger         */
    TMR_SLV_MODE_EXTCLK,            /*!< Slave Mode Ext CLK         */
    TMR_SLV_MODE_RST_TRIG,          /*!< Slave Mode Reset&Trigger   */
} TMR_SlvModeETypeDef;

/**
  * @brief Timer Event Generation Definition
  */
typedef enum {
    TMR_EVT_GEN_UPDATE = 0,         /*!< Timer Event Generation Update              */
    TMR_EVT_GEN_TRIGGER,            /*!< Timer Event Generation Trigger             */
    TMR_EVT_GEN_BREAK0,             /*!< Timer Event Generation Break 0             */
    TMR_EVT_GEN_BREAK1,             /*!< Timer Event Generation Break 1             */
    TMR_EVT_GEN_CAP_CMP_0,          /*!< Timer Event Generation Capture/Compare 0   */
    TMR_EVT_GEN_CAP_CMP_1,          /*!< Timer Event Generation Capture/Compare 1   */
    TMR_EVT_GEN_CAP_CMP_2,          /*!< Timer Event Generation Capture/Compare 2   */
    TMR_EVT_GEN_CAP_CMP_3 = 7,      /*!< Timer Event Generation Capture/Compare 3   */
    TMR_EVT_GEN_CNTR_START = 12,    /*!< Timer Event Generation Counter Start       */
    TMR_EVT_GEN_NUMS,               /*!< Timer Event Generation Numbres             */
} TMR_EvtGenETypeDef;


/**
  * @brief Timer Compare Mode Definition
  */
typedef enum {
    TMR_CMP_MODE_FREEZE = 0,        /*!< Compare Mode Freeze                */
    TMR_CMP_MODE_ACTIVE,            /*!< Compare Mode Active                */
    TMR_CMP_MODE_INACTIVE,          /*!< Compare Mode Inactive              */
    TMR_CMP_MODE_TOGGLE,            /*!< Compare Mode Toggle                */
    TMR_CMP_MODE_FORCE_INACTIVE,    /*!< Compare Mode Force Inactive        */
    TMR_CMP_MODE_FORCE_ACTIVE,      /*!< Compare Mode Force Active          */
    TMR_CMP_MODE_PWM1,              /*!< Compare Mode PWM1                  */
    TMR_CMP_MODE_PWM2,              /*!< Compare Mode PWM2                  */
    TMR_CMP_MODE_RETRIG_OPM1,       /*!< Compare Mode Repeat Trigger OPM1   */
    TMR_CMP_MODE_RETRIG_OPM2,       /*!< Compare Mode Repeat Trigger OPM2   */
    TMR_CMP_MODE_COMB_PWM1 = 12,    /*!< Compare Mode Combination PWM1      */
    TMR_CMP_MODE_COMB_PWM2,         /*!< Compare Mode Combination PWM2      */
    TMR_CMP_MODE_ASYM_PWM1,         /*!< Compare Mode Asymmetric PWM1       */
    TMR_CMP_MODE_ASYM_PWM2,         /*!< Compare Mode Asymmetric PWM2       */
} TMR_CmpModeETypeDef;

/**
  * @brief Timer Capture Prescaler Definition
  */
typedef enum {
    TMR_CAP_PRESCALER_1 = 0,        /*!< Capture Prescaler 1    */
    TMR_CAP_PRESCALER_2,            /*!< Capture Prescaler 2    */
    TMR_CAP_PRESCALER_4,            /*!< Capture Prescaler 4    */
    TMR_CAP_PRESCALER_8,            /*!< Capture Prescaler 8    */
} TMR_CapPrescalerETypeDef;

/**
  * @brief Timer Capture Input Map Definition
  */
typedef enum {
    TMR_CAP0_INPUT_MAP_CH0 = 1,     /*!< Capture0 Input Map CH0     */
    TMR_CAP0_INPUT_MAP_CH1,         /*!< Capture0 Input Map CH1     */

    TMR_CAP1_INPUT_MAP_CH1 = 1,     /*!< Capture1 Input Map CH1     */
    TMR_CAP1_INPUT_MAP_CH0,         /*!< Capture1 Input Map CH0     */

    TMR_CAP2_INPUT_MAP_CH2 = 1,     /*!< Capture2 Input Map CH2     */
    TMR_CAP2_INPUT_MAP_CH3,         /*!< Capture2 Input Map CH3     */

    TMR_CAP3_INPUT_MAP_CH3 = 1,     /*!< Capture3 Input Map CH3     */
    TMR_CAP3_INPUT_MAP_CH2,         /*!< Capture3 Input Map CH2     */

    TMR_CAP_INPUT_MAP_TRGI = 3,     /*!< Capture Input Map TRGI     */
} TMR_CapInputMapETypeDef;

/**
  * @brief Timer Compare Polarity Definition
  */
typedef enum {
    TMR_CMP_POL_HIGH = 0,           /*!< Compare Polarity High Active   */
    TMR_CMP_POL_LOW,                /*!< Compare Polarity Low Active    */
} TMR_CmpPolETypeDef;

/**
  * @brief Timer Capture Polarity Definition
  */
typedef enum {
    TMR_CAP_POL_CLOSE = 0,          /*!< Capture Polarity Close                         */
    TMR_CAP_POL_RISING,             /*!< Capture Polarity Rising                        */
    TMR_CAP_POL_FALLING,            /*!< Capture Polarity Falling                       */
    TMR_CAP_POL_BOTH_EDGE,          /*!< Capture Polarity both Rising and Falling edge  */
} TMR_CapPolETypeDef;

/**
  * @brief Timer Break Polarity Definition
  */
typedef enum {
    TMR_BRK_POL_HIGH = 0,           /*!< Break Polarity High Active */
    TMR_BRK_POL_LOW,                /*!< Break Polarity Low Active  */
} TMR_BrkPolETypeDef;

/**
  * @brief Timer Run-Mode Off-State Definition
  */
typedef enum {
    TMR_RUN_OFF_STA_0 = 0,          /*!< Run-Mode Off-State 0   */
    TMR_RUN_OFF_STA_1,              /*!< Run-Mode Off-State 1   */
} TMR_RunOffStaETypeDef;

/**
  * @brief Timer Idle-Mode Off-State Definition
  */
typedef enum {
    TMR_IDLE_OFF_STA_0 = 0,         /*!< Idle-Mode Off-State 0  */
    TMR_IDLE_OFF_STA_1,             /*!< Idle-Mode Off-State 1  */
} TMR_IdleOffStaETypeDef;

/**
  * @brief Timer Capture Input Source Definition
  */
typedef enum {
    TMR_CAP_INPUT_SRC_IN0 = 0,      /*!< Capture Input Source IN0   */
    TMR_CAP_INPUT_SRC_IN1,          /*!< Capture Input Source IN1   */
    TMR_CAP_INPUT_SRC_IN2,          /*!< Capture Input Source IN2   */
    TMR_CAP_INPUT_SRC_IN3,          /*!< Capture Input Source IN3   */
    TMR_CAP_INPUT_SRC_IN4,          /*!< Capture Input Source IN4   */
    TMR_CAP_INPUT_SRC_IN5,          /*!< Capture Input Source IN5   */
    TMR_CAP_INPUT_SRC_IN6,          /*!< Capture Input Source IN6   */
    TMR_CAP_INPUT_SRC_IN7,          /*!< Capture Input Source IN7   */
    TMR_CAP_INPUT_SRC_IN8,          /*!< Capture Input Source IN8   */
    TMR_CAP_INPUT_SRC_IN9,          /*!< Capture Input Source IN9   */
    TMR_CAP_INPUT_SRC_IN10,         /*!< Capture Input Source IN10  */
    TMR_CAP_INPUT_SRC_IN11,         /*!< Capture Input Source IN11  */
    TMR_CAP_INPUT_SRC_IN12,         /*!< Capture Input Source IN12  */
    TMR_CAP_INPUT_SRC_IN13,         /*!< Capture Input Source IN13  */
    TMR_CAP_INPUT_SRC_IN14,         /*!< Capture Input Source IN14  */
    TMR_CAP_INPUT_SRC_IN15,         /*!< Capture Input Source IN15  */
} TMR_CapInputSrcETypeDef;

/**
  * @brief Timer Break Input Polarity Definition
  */
typedef enum {
    TMR_BRKx_INPUT_POL_HIGH = 0,        /*!< BRKx Input Polarity High Active    */

    TMR_BRK0_INPUT_POL_LOW  = BIT(0),   /*!< BRK0 Input Polarity Low Active     */
    TMR_BRK1_INPUT_POL_LOW  = BIT(1),   /*!< BRK1 Input Polarity Low Active     */
    TMR_BRK2_INPUT_POL_LOW  = BIT(2),   /*!< BRK2 Input Polarity Low Active     */
    TMR_BRK3_INPUT_POL_LOW  = BIT(3),   /*!< BRK3 Input Polarity Low Active     */
    TMR_BRK4_INPUT_POL_LOW  = BIT(4),   /*!< BRK4 Input Polarity Low Active     */
    TMR_BRK5_INPUT_POL_LOW  = BIT(5),   /*!< BRK5 Input Polarity Low Active     */
    TMR_BRK6_INPUT_POL_LOW  = BIT(6),   /*!< BRK6 Input Polarity Low Active     */
    TMR_BRK7_INPUT_POL_LOW  = BIT(7),   /*!< BRK7 Input Polarity Low Active     */
    TMR_BRK8_INPUT_POL_LOW  = BIT(8),   /*!< BRK8 Input Polarity Low Active     */
    TMR_BRK9_INPUT_POL_LOW  = BIT(9),   /*!< BRK9 Input Polarity Low Active     */
    TMR_BRK10_INPUT_POL_LOW = BIT(10),  /*!< BRK10 Input Polarity Low Active    */
    TMR_BRK11_INPUT_POL_LOW = BIT(11),  /*!< BRK11 Input Polarity Low Active    */
    TMR_BRK12_INPUT_POL_LOW = BIT(12),  /*!< BRK12 Input Polarity Low Active    */
    TMR_BRK13_INPUT_POL_LOW = BIT(13),  /*!< BRK13 Input Polarity Low Active    */
    TMR_BRK14_INPUT_POL_LOW = BIT(14),  /*!< BRK14 Input Polarity Low Active    */
    TMR_BRK15_INPUT_POL_LOW = BIT(15),  /*!< BRK15 Input Polarity Low Active    */
} TMR_BrkInputPolETypeDef;


/**
  * @brief Timer Capture/Compare Channel Definition
  */
typedef enum {
    TMR_CAP_CMP_CH_0 = 0,           /*!< Channel 0  */
    TMR_CAP_CMP_CH_1,               /*!< Channel 1  */
    TMR_CAP_CMP_CH_2,               /*!< Channel 2  */
    TMR_CAP_CMP_CH_3,               /*!< Channel 3  */
} TMR_CapCmpChETypeDef;

/**
  * @brief Low Power Timer Clock Source Selection Definition
  */
typedef enum {
    TMR_LP_CLK_SRC_APB0CLK = 0,     /*!< Low Power Timer Clock Source APB0CLK     */
    TMR_LP_CLK_SRC_HSI,             /*!< Low Power Timer Clock Source HSI         */
    TMR_LP_CLK_SRC_HSE,             /*!< Low Power Timer Clock Source HSE         */
    TMR_LP_CLK_SRC_LSI,             /*!< Low Power Timer Clock Source LSI         */
} TMR_LowPwrClkSrcETypeDef;

/**
  * @brief Timer Base Unit Initialization Structure Definition
  */
typedef struct __TMR_BaseInitTypeDef {
    //Base Config
    bool auto_preload_en;                       /*!< Auto Preload Enable                        */
    TMR_WorkModeETypeDef work_mode;             /*!< Work Mode: Continue/Single                 */
    TMR_MstModeETypeDef  mst_mode;              /*!< Master Mode, it is invalid with LPTMR      */

    uint32_t period;                            /*!< Period Value, TMR3&4: 32bit, Other: 16bit  */
    uint16_t prescaler;                         /*!< Clock Prescaler, TMR6: 8bit, Other: 16bit  */

    //TRGO Config
    uint8_t  trgo_width;                        /*!< TRGO Output Width                          */

    //Event Config
    bool update_evt_en;                         /*!< Update Event Enable                        */
    TMR_UpdateEvtSrcETypeDef update_evt_src;    /*!< Update Event Source                        */

    //Advance Config
    uint8_t rep_cnt;                            /*!< Repeat Counter                             */
    TMR_CtrAlignModeETypeDef   ctr_align_mode;  /*!< Center Align Mode                          */
    TMR_CntDirETypeDef         cnt_dir;         /*!< Counter Direction                          */
    TMR_DzDigFilClkDivETypeDef dz_clk_div;      /*!< Dead Zone Clock Dividsion                  */
} TMR_BaseInitTypeDef;

/**
  * @brief Timer Input Capture Initialization Structure Definition
  * @note  Please notice that TMR can work on Input Capture mode or Output Compare mode
  */
typedef struct __TMR_InputCapInitTypeDef {
    uint8_t filter;                             /*!< Input Capture Filter               */
    TMR_CapPolETypeDef       pol;               /*!< Input Capture Polarity             */
    TMR_CapInputMapETypeDef  input_map;         /*!< Input Capture Map                  */
    TMR_CapPrescalerETypeDef prescaler;         /*!< Input Capture Prescaler            */
    TMR_TrigInputSrcETypeDef input_src;         /*!< Input Capture Trigger Input Source */
} TMR_InputCapInitTypeDef;

/**
  * @brief Timer Output Compare Initialization Structure Definition
  * @note  Please notice that TMR can work on Input Capture mode or Output Compare mode
  */
typedef struct __TMR_OutputCmpInitTypeDef {
    bool     auto_preload_en;                   /*!< Output Compare Auto Preload Enable */
    bool     trig_output_en;                    /*!< Trigger Output Enable              */
    uint8_t  trgcc_width;                       /*!< TRGCC Output Width                 */
    uint32_t match_val;                         /*!< Output Compare Match Value         */
    TMR_CmpModeETypeDef mode;                   /*!< Output Compare Mode                */

    bool OC_en;                                 /*!< OC Enable                          */
    bool OCN_en;                                /*!< OCN Enable                         */
    TMR_CmpPolETypeDef OC_pol;                  /*!< OC Polarity                        */
    TMR_CmpPolETypeDef OCN_pol;                 /*!< OCN Polarity                       */
    TMR_OutputIdleStaETypeDef OC_idle_sta;      /*!< OC Idle State                      */
    TMR_OutputIdleStaETypeDef OCN_idle_sta;     /*!< OCN Idle State                     */
} TMR_OutputCmpInitTypeDef;

/**
  * @brief Timer Slave Initialization Structure Definition
  */
typedef struct __TMR_SlvInitTypeDef {
    bool    fast_sync_en;                       /*!< Mst/Slv Fast Sync Enable   */
    uint8_t etr_filter;                         /*!< ETR Filter                 */
    TMR_ETRModeETypeDef     etr_mode;           /*!< ETR Mode                   */
    TMR_ETREdgeModeETypeDef etr_edge_mode;      /*!< ETR Edge Mode              */
    TMR_ETRInputSrcETypeDef etr_input_src;      /*!< ETR Input Source           */
    TMR_SlvModeETypeDef slv_mode;               /*!< Slave Mode                 */
    TMR_TrigETypeDef    trig;                   /*!< Trigger Selection          */
} TMR_SlvInitTypeDef;

/**
  * @brief Timer Break and DeadZone Initialization Structure Definition
  * @note  brk0_input_src/brk1_input_src is combination of TMR_BrkInputSrcETypeDef
  *        brk0_input_pol/brk1_input_pol is combination of TMR_BrkInputPolETypeDef
  */
typedef struct __TMR_BrkDzInitTypeDef {
    bool auto_output_en;                        /*!< Automatic Output Enable    */
    bool main_output_en;                        /*!< Main Output Enable         */
    uint8_t dead_time;                          /*!< Dead Time                  */

    bool brk0_enable;                           /*!< Break 0 Enable             */
    bool brk1_enable;                           /*!< Break 1 Enable             */
    uint8_t brk0_filter;                        /*!< Break 0 Filter             */
    uint8_t brk1_filter;                        /*!< Break 1 Filter             */
    TMR_BrkPolETypeDef brk0_pol;                /*!< Break 0 Polarity           */
    TMR_BrkPolETypeDef brk1_pol;                /*!< Break 1 Polarity           */
    uint16_t brk0_input_src;                    /*!< Break 0 Input Source       */
    uint16_t brk1_input_src;                    /*!< Break 1 Input Source       */
    uint16_t brk0_input_pol;                    /*!< Break 0 Input Polarity     */
    uint16_t brk1_input_pol;                    /*!< Break 1 Input Polarity     */

    TMR_RunOffStaETypeDef  run_off_sta;         /*!< Run-Mode Off-State         */
    TMR_IdleOffStaETypeDef idle_off_sta;        /*!< Idle-Mode Off-State        */
} TMR_BrkDzInitTypeDef;

/**
  * @brief Timer Low Power Initialization Structure Definition
  */
typedef struct __TMR_LowPwrInitTypeDef {
    TMR_LowPwrClkSrcETypeDef   lp_clk_src;      /*!< Low Power Timer Clock Source               */
} TMR_LowPwrInitTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup TMR_LL_Exported_Functions
  * @{
  */

/** @addtogroup TMR_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_TMR_Init(TMR_TypeDef *Instance);
LL_StatusETypeDef LL_TMR_DeInit(TMR_TypeDef *Instance);
void LL_TMR_MspInit(TMR_TypeDef *Instance);
void LL_TMR_MspDeInit(TMR_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup TMR_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_TMR_Base_Cfg(TMR_TypeDef *Instance, TMR_BaseInitTypeDef *cfg);
LL_StatusETypeDef LL_TMR_InputCap_Cfg(TMR_TypeDef *Instance, TMR_CapCmpChETypeDef ch, TMR_InputCapInitTypeDef *cfg);
LL_StatusETypeDef LL_TMR_OutputCmp_Cfg(TMR_TypeDef *Instance, TMR_CapCmpChETypeDef ch, TMR_OutputCmpInitTypeDef *cfg);
LL_StatusETypeDef LL_TMR_Slv_Cfg(TMR_TypeDef *Instance, TMR_SlvInitTypeDef *cfg);
LL_StatusETypeDef LL_TMR_BrkDz_Cfg(TMR_TypeDef *Instance, TMR_BrkDzInitTypeDef *cfg);
LL_StatusETypeDef LL_TMR_LowPwr_Cfg(TMR_TypeDef *Instance, TMR_LowPwrInitTypeDef *cfg);
LL_StatusETypeDef LL_TMR_LowPwrBase_Cfg(TMR_TypeDef *Instance, TMR_BaseInitTypeDef *cfg, uint32_t timeout);
LL_StatusETypeDef LL_TMR_LowPwrOutputCmp_Cfg(TMR_TypeDef *Instance, TMR_CapCmpChETypeDef ch, TMR_OutputCmpInitTypeDef *cfg, uint32_t timeout);
LL_StatusETypeDef LL_TMR_LowPwrSlv_Cfg(TMR_TypeDef *Instance, TMR_SlvInitTypeDef *cfg);
/**
  * @}
  */


/** @addtogroup TMR_LL_Exported_Functions_Group3
  * @{
  */
LL_StatusETypeDef LL_TMR_Start(TMR_TypeDef *Instance);
LL_StatusETypeDef LL_TMR_Stop(TMR_TypeDef *Instance);
LL_StatusETypeDef LL_TMR_Start_IT(TMR_TypeDef *Instance);
LL_StatusETypeDef LL_TMR_Stop_IT(TMR_TypeDef *Instance);
LL_StatusETypeDef LL_TMR_CapCmpInt_Cfg(TMR_TypeDef *Instance, TMR_CapCmpChETypeDef ch, bool int_en);
LL_StatusETypeDef LL_TMR_EvtGen(TMR_TypeDef *Instance, TMR_EvtGenETypeDef evt);
uint32_t LL_TMR_InputCapVal_Get(TMR_TypeDef *Instance, TMR_CapCmpChETypeDef ch);

LL_StatusETypeDef LL_TMR_LowPwrStart(TMR_TypeDef *Instance);
LL_StatusETypeDef LL_TMR_LowPwrStop(TMR_TypeDef *Instance);
LL_StatusETypeDef LL_TMR_LowPwrCmpInt_Cfg(TMR_TypeDef *Instance, TMR_CapCmpChETypeDef ch, bool int_en);
LL_StatusETypeDef LL_TMR_LowPwrEvtGen(TMR_TypeDef *Instance, TMR_EvtGenETypeDef evt);
/**
  * @}
  */


/** @addtogroup TMR_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_TMR_IRQHandler(TMR_TypeDef *Instance);
void LL_TMR_Upd_IRQHandler(TMR_TypeDef *Instance);
void LL_TMR_Trg_IRQHandler(TMR_TypeDef *Instance);
void LL_TMR_Brk_IRQHandler(TMR_TypeDef *Instance);
void LL_TMR_CC_IRQHandler(TMR_TypeDef *Instance);

void LL_TMR_OverflowCallback(TMR_TypeDef *Instance);
void LL_TMR_UpdateCallback(TMR_TypeDef *Instance);

void LL_TMR_TrigCallback(TMR_TypeDef *Instance);
void LL_TMR_Brk0Callback(TMR_TypeDef *Instance);
void LL_TMR_Brk1Callback(TMR_TypeDef *Instance);
void LL_TMR_SysFaultBrkCallback(TMR_TypeDef *Instance);

void LL_TMR_CH3_OverCapCallback(TMR_TypeDef *Instance);
void LL_TMR_CH3_CapCmpCallback(TMR_TypeDef *Instance);
void LL_TMR_CH2_OverCapCallback(TMR_TypeDef *Instance);
void LL_TMR_CH2_CapCmpCallback(TMR_TypeDef *Instance);
void LL_TMR_CH1_OverCapCallback(TMR_TypeDef *Instance);
void LL_TMR_CH1_CapCmpCallback(TMR_TypeDef *Instance);
void LL_TMR_CH0_OverCapCallback(TMR_TypeDef *Instance);
void LL_TMR_CH0_CapCmpCallback(TMR_TypeDef *Instance);
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

#endif /* _TAE32G58XX_LL_TMR_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

