/**
  ******************************************************************************
  * @file    tae32g58xx_ll_adc.h
  * @author  MCD Application Team
  * @brief   Header file for ADC LL module
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
#ifndef _TAE32G58XX_LL_ADC_H_
#define _TAE32G58XX_LL_ADC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup ADC_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Macros ADC LL Exported Macros
  * @brief    ADC LL Exported Macros
  * @{
  */

/**
  * @brief  ADC 32bits Register offset
  * @note   Register must be 32bits
  * @param  __REG__  Register basis from which the offset is applied
  * @param  offset   Numbers of register to Offset
  * @return Register value after offset
  */
#define __LL_ADC_REG_OFFSET(__REG__, offset)            \
    (*((__IO uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((offset) << 2UL)))))

/**
  * @brief  ADC DMA Register offset
  * @param  __REG__  Register basis from which the offset is applied
  * @param  offset   Offset in ADC_DMA_TypeDef type
  * @return ADC_DMA_TypeDef type struct
  */
#define __LL_ADC_DMA_REG_OFFSET(__REG__, offset)        \
    (*((__IO ADC_DMA_TypeDef *)((uint32_t) ((uint32_t)(&(__REG__)) + ((offset) * (sizeof(ADC_DMA_TypeDef)))))))

/**
  * @brief  Calibration Mode Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  mode Calibration Mode @ref ADC_CalModeETypeDef
  * @return None
  */
#define __LL_ADC_CalMode_Set(__ADC__, mode)             \
        MODIFY_REG((__ADC__)->CR, ADC0_CR_ADCALDIF_Msk, (((mode) & 0x1UL) << ADC0_CR_ADCALDIF_Pos))

/**
  * @brief  Calibration Mode Get
  * @param  __ADC__ Specifies ADC peripheral
  * @return Calibration Mode @ref ADC_CalModeETypeDef
  */
#define __LL_ADC_CalMode_Get(__ADC__)                   READ_BIT_SHIFT((__ADC__)->CR, ADC0_CR_ADCALDIF_Msk, ADC0_CR_ADCALDIF_Pos)

/**
  * @brief  Calibration Start 
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_Cal_Start(__ADC__)                     SET_BIT((__ADC__)->CR, ADC0_CR_ADCAL_Msk)

/**
  * @brief  Judge is Calibration Starting or not 
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_IsCalStarting(__ADC__)                 READ_BIT_SHIFT((__ADC__)->CR, ADC0_CR_ADCAL_Msk, ADC0_CR_ADCAL_Pos)

/**
  * @brief  Injected Conversion Stop
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_INJ_Conv_Stop(__ADC__)                 SET_BIT((__ADC__)->CR, ADC0_CR_JADSTP_Msk)

/**
  * @brief  Judge is Injected Conversion Stopping or not
  * @param  __ADC__ Specifies ADC peripheral
  * @retval 0 Injected Conversion has Stopped
  * @retval 1 Injected Conversion is Stopping
  */
#define __LL_ADC_INJ_IsConvStopping(__ADC__)            READ_BIT_SHIFT((__ADC__)->CR, ADC0_CR_JADSTP_Msk, ADC0_CR_JADSTP_Pos)

/**
  * @brief  Regular Conversion Stop
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_REG_Conv_Stop(__ADC__)                 SET_BIT((__ADC__)->CR, ADC0_CR_ADSTP_Msk)

/**
  * @brief  Judge is Regular Conversion Stopping or not
  * @param  __ADC__ Specifies ADC peripheral
  * @retval 0 Regular Conversion has Stopped
  * @retval 1 Regular Conversion is Stopping
  */
#define __LL_ADC_REG_IsConvStopping(__ADC__)            READ_BIT_SHIFT((__ADC__)->CR, ADC0_CR_ADSTP_Msk, ADC0_CR_ADSTP_Pos)

/**
  * @brief  Injected Conversion Start
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_INJ_Conv_Start(__ADC__)                SET_BIT((__ADC__)->CR, ADC0_CR_JADSTART_Msk)

/**
  * @brief  Judge is Injected Conversion Running or not
  * @param  __ADC__ Specifies ADC peripheral
  * @retval 0 Injected Conversion isn't Running
  * @retval 1 Injected Conversion is Running
  */
#define __LL_ADC_INJ_IsConvRunning(__ADC__)             READ_BIT_SHIFT((__ADC__)->CR, ADC0_CR_JADSTART_Msk, ADC0_CR_JADSTART_Pos)

/**
  * @brief  Regular Conversion Start
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_REG_Conv_Start(__ADC__)                SET_BIT((__ADC__)->CR, ADC0_CR_ADSTART_Msk)

/**
  * @brief  Judge is Regular Conversion Running or not
  * @param  __ADC__ Specifies ADC peripheral
  * @retval 0 Regular Conversion isn't Running
  * @retval 1 Regular Conversion is Running
  */
#define __LL_ADC_REG_IsConvRunning(__ADC__)             READ_BIT_SHIFT((__ADC__)->CR, ADC0_CR_ADSTART_Msk, ADC0_CR_ADSTART_Pos)

/**
  * @brief  ADC Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_Dis(__ADC__)                           SET_BIT((__ADC__)->CR, ADC0_CR_ADDIS_Msk)

/**
  * @brief  Judge is ADC Stopping or not
  * @param  __ADC__ Specifies ADC peripheral
  * @retval 0 ADC has Stopped
  * @retval 1 ADC is Stopping
  */
#define __LL_ADC_IsStopping(__ADC__)                    READ_BIT_SHIFT((__ADC__)->CR, ADC0_CR_ADDIS_Msk, ADC0_CR_ADDIS_Pos)

/**
  * @brief  ADC Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_En(__ADC__)                            SET_BIT((__ADC__)->CR, ADC0_CR_ADEN_Msk)

/**
  * @brief  Judge is ADC Running or not
  * @param  __ADC__ Specifies ADC peripheral
  * @retval 0 ADC isn't Running
  * @retval 1 ADC is Running
  */
#define __LL_ADC_IsRunning(__ADC__)                     READ_BIT_SHIFT((__ADC__)->CR, ADC0_CR_ADEN_Msk, ADC0_CR_ADEN_Pos)


/**
  * @brief  Auto-calibration Ratio Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ratio Auto-calibration Ratio @ref ADC_OverSampRatioETypeDef
  * @return None
  */
#define __LL_ADC_AutoCalRatio_Set(__ADC__, ratio)       \
        MODIFY_REG((__ADC__)->CFGR0, ADC0_CFGR0_OVSCAL_Msk, (((ratio) & 0x7UL) << ADC0_CFGR0_OVSCAL_Pos))

/**
  * @brief  Auto-calibration Ratio Get
  * @param  __ADC__ Specifies ADC peripheral
  * @return Auto-calibration Ratio @ref ADC_OverSampRatioETypeDef
  */
#define __LL_ADC_AutoCalRatio_Get(__ADC__)              READ_BIT_SHIFT((__ADC__)->CFGR0, ADC0_CFGR0_OVSCAL_Msk, ADC0_CFGR0_OVSCAL_Pos)

/**
  * @brief  Regular Conversion Mode Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  mode Regular Conversion Mode
  * @return None
  */
#define __LL_ADC_REG_ConvMode_Set(__ADC__, mode)        \
        MODIFY_REG((__ADC__)->CFGR0, ADC0_CFGR0_CONT_Msk, (((mode) & 0x1UL) << ADC0_CFGR0_CONT_Pos))

/**
  * @brief  Injected Auto Conversion Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_INJ_AutoConv_En(__ADC__)               SET_BIT((__ADC__)->CFGR0, ADC0_CFGR0_JAUTO_Msk)

/**
  * @brief  Injected Auto Conversion Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_INJ_AutoConv_Dis(__ADC__)              CLEAR_BIT((__ADC__)->CFGR0, ADC0_CFGR0_JAUTO_Msk)

/**
  * @brief  Injected Discontinuous Conversion Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_INJ_DisContConv_En(__ADC__)            SET_BIT((__ADC__)->CFGR0, ADC0_CFGR0_JDISCEN_Msk)

/**
  * @brief  Injected Discontinuous Conversion Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_INJ_DisContConv_Dis(__ADC__)           CLEAR_BIT((__ADC__)->CFGR0, ADC0_CFGR0_JDISCEN_Msk)

/**
  * @brief  Regular Discontinuous Conversion Numbers Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  num Regular Discontinuous Conversion Numbers
  * @return None
  */
#define __LL_ADC_REG_DisContConvNum_Set(__ADC__, num)   \
        MODIFY_REG((__ADC__)->CFGR0, ADC0_CFGR0_DISCNUM_Msk, (((num) & 0x7UL) << ADC0_CFGR0_DISCNUM_Pos))

/**
  * @brief  Regular Discontinuous Conversion Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_REG_DisContConv_En(__ADC__)            SET_BIT((__ADC__)->CFGR0, ADC0_CFGR0_DISCEN_Msk)

/**
  * @brief  Regular Discontinuous Conversion Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_REG_DisContConv_Dis(__ADC__)           CLEAR_BIT((__ADC__)->CFGR0, ADC0_CFGR0_DISCEN_Msk)

/**
  * @brief  Overrun Mode Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  mode Overrun Mode
  * @return None
  */
#define __LL_ADC_OverRunMode_Set(__ADC__, mode)         \
        MODIFY_REG((__ADC__)->CFGR0, ADC0_CFGR0_OVRMOD_Msk, (((mode) & 0x1UL) << ADC0_CFGR0_OVRMOD_Pos))

/**
  * @brief  System DMA Request Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_SysDmaReq_En(__ADC__)                  SET_BIT((__ADC__)->CFGR0, ADC0_CFGR0_SDMAEN_Msk)

/**
  * @brief  System DMA Request Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_SysDmaReq_Dis(__ADC__)                 CLEAR_BIT((__ADC__)->CFGR0, ADC0_CFGR0_SDMAEN_Msk)

/**
  * @brief  Judge is System DMA Request Enable or not
  * @param  __ADC__ Specifies ADC peripheral
  * @retval 0 is System DMA Request Disable
  * @retval 1 is System DMA Request Enable
  */
#define __LL_ADC_IsSysDmaReqEn(__ADC__)                 READ_BIT_SHIFT((__ADC__)->CFGR0, ADC0_CFGR0_SDMAEN_Msk, ADC0_CFGR0_SDMAEN_Pos)

/**
  * @brief  Trigger Over Sample Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_TrigOverSample_En(__ADC__)             SET_BIT((__ADC__)->CFGR0, ADC0_CFGR0_TROVS_Msk)

/**
  * @brief  Trigger Over Sample Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_TrigOverSamp_Dis(__ADC__)              CLEAR_BIT((__ADC__)->CFGR0, ADC0_CFGR0_TROVS_Msk)

/**
  * @brief  Over Sample Right Shift Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  shift Over Sample Right Shift bits
  * @return None
  */
#define __LL_ADC_OverSampRightShift_Set(__ADC__, shift) \
        MODIFY_REG((__ADC__)->CFGR0, ADC0_CFGR0_OVSS_Msk, (((shift) & 0xfUL) << ADC0_CFGR0_OVSS_Pos))

/**
  * @brief  Normal Channel Oversample Mode Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  mode Normal Channel Oversample Mode
  * @return None
  */
#define __LL_ADC_NormOverSampMode_Set(__ADC__, mode)    \
        MODIFY_REG((__ADC__)->CFGR0, ADC0_CFGR0_ROVSM_Msk, (((mode) & 0x1UL) << ADC0_CFGR0_ROVSM_Pos))

/**
  * @brief  Over Sample Ratio Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ratio Over Sample Ratio @ref ADC_OverSampRatioETypeDef
  * @return None
  */
#define __LL_ADC_OverSampRatio_Set(__ADC__, ratio)      \
        MODIFY_REG((__ADC__)->CFGR0, ADC0_CFGR0_OVSR_Msk, (((ratio) & 0x7UL) << ADC0_CFGR0_OVSR_Pos))

/**
  * @brief  Injected Oversample Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_INJ_OverSamp_En(__ADC__)               SET_BIT((__ADC__)->CFGR0, ADC0_CFGR0_JOVSE_Msk)

/**
  * @brief  Injected Oversample Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_INJ_OverSamp_Dis(__ADC__)              CLEAR_BIT((__ADC__)->CFGR0, ADC0_CFGR0_JOVSE_Msk)

/**
  * @brief  Regular Oversample Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_REG_OverSamp_En(__ADC__)               SET_BIT((__ADC__)->CFGR0, ADC0_CFGR0_ROVSE_Msk)

/**
  * @brief  Regular Oversample Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_REG_OverSamp_Dis(__ADC__)              CLEAR_BIT((__ADC__)->CFGR0, ADC0_CFGR0_ROVSE_Msk)


/**
  * @brief  AWDG2 Monitor Injected Sequence Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG2_MonitorINJ_En(__ADC__)           SET_BIT((__ADC__)->CFGR1, ADC0_CFGR1_JAWD2EN_Msk)

/**
  * @brief  AWDG2 Monitor Injected Sequence Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG2_MonitorINJ_Dis(__ADC__)          CLEAR_BIT((__ADC__)->CFGR1, ADC0_CFGR1_JAWD2EN_Msk)

/**
  * @brief  AWDG1 Monitor Injected Sequence Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG1_MonitorINJ_En(__ADC__)           SET_BIT((__ADC__)->CFGR1, ADC0_CFGR1_JAWD1EN_Msk)

/**
  * @brief  AWDG1 Monitor Injected Sequence Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG1_MonitorINJ_Dis(__ADC__)          CLEAR_BIT((__ADC__)->CFGR1, ADC0_CFGR1_JAWD1EN_Msk)

/**
  * @brief  AWDG0 Monitor Injected Sequence Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG0_MonitorINJ_En(__ADC__)           SET_BIT((__ADC__)->CFGR1, ADC0_CFGR1_JAWD0EN_Msk)

/**
  * @brief  AWDG0 Monitor Injected Sequence Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG0_MonitorINJ_Dis(__ADC__)          CLEAR_BIT((__ADC__)->CFGR1, ADC0_CFGR1_JAWD0EN_Msk)

/**
  * @brief  AWDG Monitor Injected Sequence Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @param  num AWDG Number @ref ADC_AWDG_NumETypeDef
  * @return None
  */
#define __LL_ADC_AWDG_MonitorINJ_En(__ADC__, num)       \
        SET_BIT((__ADC__)->CFGR1, BIT(((num) % ADC_AWDG_NUMS) + ADC0_CFGR1_JAWD0EN_Pos))

/**
  * @brief  AWDG Monitor Injected Sequence Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @param  num AWDG Number @ref ADC_AWDG_NumETypeDef
  * @return None
  */
#define __LL_ADC_AWDG_MonitorINJ_Dis(__ADC__, num)      \
        CLEAR_BIT((__ADC__)->CFGR1, BIT(((num) % ADC_AWDG_NUMS) + ADC0_CFGR1_JAWD0EN_Pos))

/**
  * @brief  AWDG2 Monitor Regular Sequence Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG2_MonitorREG_En(__ADC__)           SET_BIT((__ADC__)->CFGR1, ADC0_CFGR1_AWD2EN_Msk)

/**
  * @brief  AWDG2 Monitor Regular Sequence Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG2_MonitorREG_Dis(__ADC__)          CLEAR_BIT((__ADC__)->CFGR1, ADC0_CFGR1_AWD2EN_Msk)

/**
  * @brief  AWDG1 Monitor Regular Sequence Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG1_MonitorREG_En(__ADC__)           SET_BIT((__ADC__)->CFGR1, ADC0_CFGR1_AWD1EN_Msk)

/**
  * @brief  AWDG1 Monitor Regular Sequence Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG1_MonitorREG_Dis(__ADC__)          CLEAR_BIT((__ADC__)->CFGR1, ADC0_CFGR1_AWD1EN_Msk)

/**
  * @brief  AWDG0 Monitor Regular Sequence Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG0_MonitorREG_En(__ADC__)           SET_BIT((__ADC__)->CFGR1, ADC0_CFGR1_AWD0EN_Msk)

/**
  * @brief  AWDG0 Monitor Regular Sequence Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG0_MonitorREG_Dis(__ADC__)          CLEAR_BIT((__ADC__)->CFGR1, ADC0_CFGR1_AWD0EN_Msk)

/**
  * @brief  AWDG Monitor Regular Sequence Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @param  num AWDG Number @ref ADC_AWDG_NumETypeDef
  * @return None
  */
#define __LL_ADC_AWDG_MonitorREG_En(__ADC__, num)       \
        SET_BIT((__ADC__)->CFGR1, BIT(((num) % ADC_AWDG_NUMS) + ADC0_CFGR1_AWD0EN_Pos))

/**
  * @brief  AWDG Monitor Regular Sequence Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @param  num AWDG Number @ref ADC_AWDG_NumETypeDef
  * @return None
  */
#define __LL_ADC_AWDG_MonitorREG_Dis(__ADC__, num)      \
        CLEAR_BIT((__ADC__)->CFGR1, BIT(((num) % ADC_AWDG_NUMS) + ADC0_CFGR1_AWD0EN_Pos))

/**
  * @brief  ADC Bias Current Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  cur ADC Bias Current
  * @return None
  */
#define __LL_ADC_BiasCur_Set(__ADC__, cur)              \
        MODIFY_REG((__ADC__)->CFGR1, ADC0_CFGR1_ISEL_Msk, (((cur) & 0x3UL) << ADC0_CFGR1_ISEL_Pos))

/**
  * @brief  ADC Channel Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_Channel_En(__ADC__)                    SET_BIT((__ADC__)->CFGR1, ADC0_CFGR1_CHEN_Msk)

/**
  * @brief  ADC Channel Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_Channel_Dis(__ADC__)                   CLEAR_BIT((__ADC__)->CFGR1, ADC0_CFGR1_CHEN_Msk)

/**
  * @brief  ADC Reference Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_Ref_En(__ADC__)                        SET_BIT((__ADC__)->CFGR1, ADC0_CFGR1_REFEN_Msk)

/**
  * @brief  ADC Reference Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_Ref_Dis(__ADC__)                       CLEAR_BIT((__ADC__)->CFGR1, ADC0_CFGR1_REFEN_Msk)

/**
  * @brief  ADC Bias Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_Bias_En(__ADC__)                       SET_BIT((__ADC__)->CFGR1, ADC0_CFGR1_BIASEN_Msk)

/**
  * @brief  ADC Bias Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_Bias_Dis(__ADC__)                      CLEAR_BIT((__ADC__)->CFGR1, ADC0_CFGR1_BIASEN_Msk)


/**
  * @brief  Judge is Sample End Interrupt Pending or not
  * @param  __ADC__ Specifies ADC peripheral
  * @retval 0 isn't Sample End Interrupt Pending
  * @retval 1 is Sample End Interrupt Pending
  */
#define __LL_ADC_IsSampEndIntPnd(__ADC__)               READ_BIT_SHIFT((__ADC__)->ISR, ADC0_ISR_EOSMP_Msk, ADC0_ISR_EOSMP_Pos)

/**
  * @brief  Sample End Interrupt Pending Clear
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_SampEndIntPnd_Clr(__ADC__)             WRITE_REG((__ADC__)->ISR, ADC0_ISR_EOSMP_Msk)

/**
  * @brief  Judge is ADC Ready Interrupt Pending or not
  * @param  __ADC__ Specifies ADC peripheral
  * @retval 0 isn't ADC Ready Interrupt Pending
  * @retval 1 is ADC Ready Interrupt Pending
  */
#define __LL_ADC_IsReadyIntPnd(__ADC__)                 READ_BIT_SHIFT((__ADC__)->ISR, ADC0_ISR_ADRDY_Msk, ADC0_ISR_ADRDY_Pos)

/**
  * @brief  ADC Ready Interrupt Pending Clear
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_ReadyIntPnd_Clr(__ADC__)               WRITE_REG((__ADC__)->ISR, ADC0_ISR_ADRDY_Msk)

/**
  * @brief  Judge is AWDG2 Interrupt Pending or not
  * @param  __ADC__ Specifies ADC peripheral
  * @retval 0 isn't AWDG2 Interrupt Pending
  * @retval 1 is AWDG2 Interrupt Pending
  */
#define __LL_ADC_IsAWDG2IntPnd(__ADC__)                 READ_BIT_SHIFT((__ADC__)->ISR, ADC0_ISR_AWD2_Msk, ADC0_ISR_AWD2_Pos)

/**
  * @brief  AWDG2 Interrupt Pending Clear
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG2IntPnd_Clr(__ADC__)               WRITE_REG((__ADC__)->ISR, ADC0_ISR_AWD2_Msk)

/**
  * @brief  Judge is AWDG1 Interrupt Pending or not
  * @param  __ADC__ Specifies ADC peripheral
  * @retval 0 isn't AWDG1 Interrupt Pending
  * @retval 1 is AWDG1 Interrupt Pending
  */
#define __LL_ADC_IsAWDG1IntPnd(__ADC__)                 READ_BIT_SHIFT((__ADC__)->ISR, ADC0_ISR_AWD1_Msk, ADC0_ISR_AWD1_Pos)

/**
  * @brief  AWDG1 Interrupt Pending Clear
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG1IntPnd_Clr(__ADC__)               WRITE_REG((__ADC__)->ISR, ADC0_ISR_AWD1_Msk)

/**
  * @brief  Judge is AWDG0 Interrupt Pending or not
  * @param  __ADC__ Specifies ADC peripheral
  * @retval 0 isn't AWDG0 Interrupt Pending
  * @retval 1 is AWDG0 Interrupt Pending
  */
#define __LL_ADC_IsAWDG0IntPnd(__ADC__)                 READ_BIT_SHIFT((__ADC__)->ISR, ADC0_ISR_AWD0_Msk, ADC0_ISR_AWD0_Pos)

/**
  * @brief  AWDG0 Interrupt Pending Clear
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG0IntPnd_Clr(__ADC__)               WRITE_REG((__ADC__)->ISR, ADC0_ISR_AWD0_Msk)

/**
  * @brief  Judge is Overflow Interrupt Pending or not
  * @param  __ADC__ Specifies ADC peripheral
  * @retval 0 isn't Overflow Interrupt Pending
  * @retval 1 is Overflow Interrupt Pending
  */
#define __LL_ADC_IsOverflowIntPnd(__ADC__)              READ_BIT_SHIFT((__ADC__)->ISR, ADC0_ISR_OVR_Msk, ADC0_ISR_OVR_Pos)

/**
  * @brief  Overflow Interrupt Pending Clear
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_OverflowIntPnd_Clr(__ADC__)            WRITE_REG((__ADC__)->ISR, ADC0_ISR_OVR_Msk)

/**
  * @brief  Judge is Injected Sequence End Interrupt Pending or not
  * @param  __ADC__ Specifies ADC peripheral
  * @retval 0 isn't Injected Sequence End Interrupt Pending
  * @retval 1 is Injected Sequence End Interrupt Pending
  */
#define __LL_ADC_INJ_IsSeqEndIntPnd(__ADC__)            READ_BIT_SHIFT((__ADC__)->ISR, ADC0_ISR_JEOS_Msk, ADC0_ISR_JEOS_Pos)

/**
  * @brief  Injected Sequence End Interrupt Pending Clear
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_INJ_SeqEndIntPnd_Clr(__ADC__)          WRITE_REG((__ADC__)->ISR, ADC0_ISR_JEOS_Msk)

/**
  * @brief  Judge is Injected Conversion End Interrupt Pending or not
  * @param  __ADC__ Specifies ADC peripheral
  * @retval 0 isn't Injected Conversion End Interrupt Pending
  * @retval 1 is Injected Conversion End Interrupt Pending
  */
#define __LL_ADC_INJ_IsConvEndIntPnd(__ADC__)           READ_BIT_SHIFT((__ADC__)->ISR, ADC0_ISR_JEOC_Msk, ADC0_ISR_JEOC_Pos)

/**
  * @brief  Injected Conversion End Interrupt Pending Clear
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_INJ_ConvEndIntPnd_Clr(__ADC__)         WRITE_REG((__ADC__)->ISR, ADC0_ISR_JEOC_Msk)

/**
  * @brief  Judge is Regular Sequence End Interrupt Pending or not
  * @param  __ADC__ Specifies ADC peripheral
  * @retval 0 isn't Regular Sequence End Interrupt Pending
  * @retval 1 is Regular Sequence End Interrupt Pending
  */
#define __LL_ADC_REG_IsSeqEndIntPnd(__ADC__)            READ_BIT_SHIFT((__ADC__)->ISR, ADC0_ISR_EOS_Msk, ADC0_ISR_EOS_Pos)

/**
  * @brief  Regular Sequence End Interrupt Pending Clear
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_REG_SeqEndIntPnd_Clr(__ADC__)          WRITE_REG((__ADC__)->ISR, ADC0_ISR_EOS_Msk)

/**
  * @brief  Judge is Regular Conversion End Interrupt Pending or not
  * @param  __ADC__ Specifies ADC peripheral
  * @retval 0 isn't Regular Conversion End Interrupt Pending
  * @retval 1 is Regular Conversion End Interrupt Pending
  */
#define __LL_ADC_REG_IsConvEndIntPnd(__ADC__)           READ_BIT_SHIFT((__ADC__)->ISR, ADC0_ISR_EOC_Msk, ADC0_ISR_EOC_Pos)

/**
  * @brief  Regular Conversion End Interrupt Pending Clear
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_REG_ConvEndIntPnd_Clr(__ADC__)         WRITE_REG((__ADC__)->ISR, ADC0_ISR_EOC_Msk)

/**
  * @brief  ADC Normal All Interrupt Pending Get
  * @param  __ADC__ Specifies ADC peripheral
  * @return ADC Normal All Interrupt Pending
  */
#define __LL_ADC_NormAllIntPending_Get(__ADC__)         READ_REG((__ADC__)->ISR)


/**
  * @brief  Sample End Interrupt Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_SampEnd_INT_En(__ADC__)                SET_BIT((__ADC__)->IER, ADC0_IER_EOSMPIE_Msk)

/**
  * @brief  Sample End Interrupt Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_SampEnd_INT_Dis(__ADC__)               CLEAR_BIT((__ADC__)->IER, ADC0_IER_EOSMPIE_Msk)

/**
  * @brief  ADC Ready Interrupt Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_Ready_INT_En(__ADC__)                  SET_BIT((__ADC__)->IER, ADC0_IER_ADRDYIE_Msk)

/**
  * @brief  ADC Ready Interrupt Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_Ready_INT_Dis(__ADC__)                 CLEAR_BIT((__ADC__)->IER, ADC0_IER_ADRDYIE_Msk)

/**
  * @brief  AWDG2 Interrupt Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG2_INT_En(__ADC__)                  SET_BIT((__ADC__)->IER, ADC0_IER_AWD2IE_Msk)

/**
  * @brief  AWDG2 Interrupt Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG2_INT_Dis(__ADC__)                 CLEAR_BIT((__ADC__)->IER, ADC0_IER_AWD2IE_Msk)

/**
  * @brief  AWDG1 Interrupt Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG1_INT_En(__ADC__)                  SET_BIT((__ADC__)->IER, ADC0_IER_AWD1IE_Msk)

/**
  * @brief  AWDG1 Interrupt Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG1_INT_Dis(__ADC__)                 CLEAR_BIT((__ADC__)->IER, ADC0_IER_AWD1IE_Msk)

/**
  * @brief  AWDG0 Interrupt Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG0_INT_En(__ADC__)                  SET_BIT((__ADC__)->IER, ADC0_IER_AWD0IE_Msk)

/**
  * @brief  AWDG0 Interrupt Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_AWDG0_INT_Dis(__ADC__)                 CLEAR_BIT((__ADC__)->IER, ADC0_IER_AWD0IE_Msk)

/**
  * @brief  Overflow Interrupt Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_Overflow_INT_En(__ADC__)               SET_BIT((__ADC__)->IER, ADC0_IER_OVRIE_Msk)

/**
  * @brief  Overflow Interrupt Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_Overflow_INT_Dis(__ADC__)              CLEAR_BIT((__ADC__)->IER, ADC0_IER_OVRIE_Msk)

/**
  * @brief  Injected Sequence End Interrupt Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_INJ_SeqEnd_INT_En(__ADC__)             SET_BIT((__ADC__)->IER, ADC0_IER_JEOSIE_Msk)

/**
  * @brief  Injected Sequence End Interrupt Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_INJ_SeqEnd_INT_Dis(__ADC__)            CLEAR_BIT((__ADC__)->IER, ADC0_IER_JEOSIE_Msk)

/**
  * @brief  Injected Conversion End Interrupt Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_INJ_ConvEnd_INT_En(__ADC__)            SET_BIT((__ADC__)->IER, ADC0_IER_JEOCIE_Msk)

/**
  * @brief  Injected Conversion End Interrupt Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_INJ_ConvEnd_INT_Dis(__ADC__)           CLEAR_BIT((__ADC__)->IER, ADC0_IER_JEOCIE_Msk)

/**
  * @brief  Regular Sequence End Interrupt Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_REG_SeqEnd_INT_En(__ADC__)             SET_BIT((__ADC__)->IER, ADC0_IER_EOSIE_Msk)

/**
  * @brief  Regular Sequence End Interrupt Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_REG_SeqEnd_INT_Dis(__ADC__)            CLEAR_BIT((__ADC__)->IER, ADC0_IER_EOSIE_Msk)

/**
  * @brief  Regular Conversion End Interrupt Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_REG_ConvEnd_INT_En(__ADC__)            SET_BIT((__ADC__)->IER, ADC0_IER_EOCIE_Msk)

/**
  * @brief  Regular Conversion End Interrupt Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @return None
  */
#define __LL_ADC_REG_ConvEnd_INT_Dis(__ADC__)           CLEAR_BIT((__ADC__)->IER, ADC0_IER_EOCIE_Msk)

/**
  * @brief  ADC Normal All Interrupt Enable Status Get
  * @param  __ADC__ Specifies ADC peripheral
  * @return ADC Normal All Interrupt Enable Status
  */
#define __LL_ADC_NormAllIntEn_Get(__ADC__)              READ_REG((__ADC__)->IER)


/**
  * @brief  ADC Channel Conversion Mode Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @param  mode ADC Channel Conversion Mode
  * @return None
  */
#define __LL_ADC_ChConvMode_Set(__ADC__, ch, mode)      MODIFY_REG((__ADC__)->SIGSEL, BIT(ch), (((mode) & 0x1UL) << (ch)))


/**
  * @brief  ADC Channel Sample Time Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @param  time ADC Channel Sample Time
  * @return None
  */
#define __LL_ADC_ChSampTime_Set(__ADC__, ch, time)                                              \
        MODIFY_REG(__LL_ADC_REG_OFFSET((__ADC__)->SMPR0, ch / 8 % ((ADC_CH_NUMS + 7) / 8)),    \
        (ADC0_SMPR0_SMP0_Msk >> ADC0_SMPR0_SMP0_Pos) << ((ch % 8) * 4),                         \
        (((time) & (ADC0_SMPR0_SMP0_Msk >> ADC0_SMPR0_SMP0_Pos)) << ((ch % 8) * 4)))


/**
  * @brief  ADC Channel Calibration Coefficient Group Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @param  grp Calibration Coefficient Group
  * @return None
  */
#define __LL_ADC_ChCalCoefGrp_Set(__ADC__, ch, grp)                                          \
        MODIFY_REG(__LL_ADC_REG_OFFSET((__ADC__)->CALR0, ch / 8 % ((ADC_CH_NUMS + 7) / 8)), \
        (ADC0_CALR0_CAL0_Msk >> ADC0_CALR0_CAL0_Pos) << ((ch % 8) * 4),                      \
        (((grp) & (ADC0_CALR0_CAL0_Msk >> ADC0_CALR0_CAL0_Pos)) << ((ch % 8) * 4)))

/**
  * @brief  ADC Channel Saturation Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @param  sat_dis bool type Saturation Disable
  * @return None
  */
#define __LL_ADC_ChSat_Set(__ADC__, ch, sat_dis)        MODIFY_REG(__LL_ADC_REG_OFFSET((__ADC__)->CALR0, ch / 8 % ((ADC_CH_NUMS + 7) / 8)), \
        0x1UL << (3 + (ch % 8) * 4), (((!!sat_dis) & 0x1UL) << (3 + (ch % 8) * 4)))


/**
  * @brief  ADC Regular Sequence Channel Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  seq ADC_REG_SeqNumETypeDef type Regular Sequence Number
  * @param  ch ADC_ChETypeDef type Channel Number
  * @return None
  */
#define __LL_ADC_REG_SeqCh_Set(__ADC__, seq, ch)                                                                                 \
        MODIFY_REG(__LL_ADC_REG_OFFSET((__ADC__)->SQR0, seq / 5 % ((ADC_REG_SEQ_NUMS + 4) / 5)), (ADC0_SQR0_SQ1_Msk >> ADC0_SQR0_SQ1_Pos) << ((seq % 5) * 6), \
        (((ch) & (ADC0_SQR0_SQ1_Msk >> ADC0_SQR0_SQ1_Pos)) << ((seq % 5) * 6)))


/**
  * @brief  Regular Sequence Length Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  len Regular Sequence Length
  * @return None
  */
#define __LL_ADC_REG_SeqLen_Set(__ADC__, len)           \
        MODIFY_REG((__ADC__)->LR, ADC0_LR_LEN_Msk, (((len) & 0xfUL) << ADC0_LR_LEN_Pos))

/**
  * @brief  Regular Sequence Trigger Polarity Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  pol Regular Sequence Trigger Polarity
  * @return None
  */
#define __LL_ADC_REG_SeqTrigPol_Set(__ADC__, pol)       \
        MODIFY_REG((__ADC__)->LR, ADC0_LR_EXTEN_Msk, (((pol) & 0x3UL) << ADC0_LR_EXTEN_Pos))

/**
  * @brief  Regular Sequence Trigger Event Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  evt Regular Sequence Trigger Event
  * @return None
  */
#define __LL_ADC_REG_SeqTrigEvt_Set(__ADC__, evt)       \
        MODIFY_REG((__ADC__)->LR, ADC0_LR_EXTSEL_Msk, (((evt) & 0x1fUL) << ADC0_LR_EXTSEL_Pos))


/**
  * @brief  Regular Sequence Data Read
  * @param  __ADC__ Specifies ADC peripheral
  * @return Regular Sequence Data
  */
#define __LL_ADC_REG_SeqDat_Read(__ADC__)               READ_REG((__ADC__)->DR)


/**
  * @brief   ADC Maximum Regular Data Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  val ADC Maximum Regular Dat
  * @return None
  */
#define __LL_ADC_REG_MaxDat_Set(__ADC__, val)           \
        MODIFY_REG((__ADC__)->MAXDR, ADC0_MAXDR_MAXDATA_Msk, (((val) & 0xffffUL) << ADC0_MAXDR_MAXDATA_Pos))

/**
  * @brief   ADC Maximum Regular Data Get
  * @param  __ADC__ Specifies ADC peripheral
  * @return ADC Maximum Regular Dat
  */
#define __LL_ADC_REG_MaxDat_Get(__ADC__)                READ_BIT_SHIFT((__ADC__)->MAXDR, ADC0_MAXDR_MAXDATA_Msk, ADC0_MAXDR_MAXDATA_Pos)


/**
  * @brief   ADC Minimum Regular Data Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  val ADC Minimum Regular Dat
  * @return None
  */
#define __LL_ADC_REG_MinDat_Set(__ADC__, val)           \
        MODIFY_REG((__ADC__)->MINDR, ADC0_MINDR_MINDATA_Msk, (((val) & 0xffffUL) << ADC0_MINDR_MINDATA_Pos))

/**
  * @brief   ADC Minimum Regular Data Get
  * @param  __ADC__ Specifies ADC peripheral
  * @return ADC Minimum Regular Dat
  */
#define __LL_ADC_REG_MinDat_Get(__ADC__)                READ_BIT_SHIFT((__ADC__)->MINDR, ADC0_MINDR_MINDATA_Msk, ADC0_MINDR_MINDATA_Pos)


/**
  * @brief  ADC Injected Sequence Channel Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  seq ADC_INJ_SeqNumETypeDef type Injected Sequence Number
  * @param  ch ADC_ChETypeDef type Channel Number
  * @return None
  */
#define __LL_ADC_INJ_SeqCh_Set(__ADC__, seq, ch)                                                    \
        MODIFY_REG((__ADC__)->JSQR, (ADC0_JSQR_JSQ1_Msk >> ADC0_JSQR_JSQ1_Pos) << ((seq % 5) * 6),\
        (((ch) & (ADC0_JSQR_JSQ1_Msk >> ADC0_JSQR_JSQ1_Pos)) << ((seq % 5) * 6)))


/**
  * @brief  Injected Sequence Length Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  len Injected Sequence Length
  * @return None
  */
#define __LL_ADC_INJ_SeqLen_Set(__ADC__, len)           \
        MODIFY_REG((__ADC__)->JLR, ADC0_JLR_JLEN_Msk, (((len) & 0x3UL) << ADC0_JLR_JLEN_Pos))

/**
  * @brief  Injected Sequence Trigger Polarity Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  pol Injected Sequence Trigger Polarity
  * @return None
  */
#define __LL_ADC_INJ_SeqTrigPol_Set(__ADC__, pol)       \
        MODIFY_REG((__ADC__)->JLR, ADC0_JLR_JEXTEN_Msk, (((pol) & 0x3UL) << ADC0_JLR_JEXTEN_Pos))

/**
  * @brief  Injected Sequence Trigger Event Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  evt Injected Sequence Trigger Event
  * @return None
  */
#define __LL_ADC_INJ_SeqTrigEvt_Set(__ADC__, evt)       \
        MODIFY_REG((__ADC__)->JLR, ADC0_JLR_JEXTSEL_Msk, (((evt) & 0x1fUL) << ADC0_JLR_JEXTSEL_Pos))


/**
  * @brief   ADC Maximum Injected Data Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  val ADC Maximum Injected Dat
  * @return None
  */
#define __LL_ADC_INJ_MaxDat_Set(__ADC__, val)           \
        MODIFY_REG((__ADC__)->MAXJDR, ADC0_MAXJDR_MAXDATA_Msk, (((val) & 0xffffUL) << ADC0_MAXJDR_MAXDATA_Pos))

/**
  * @brief   ADC Maximum Injected Data Get
  * @param  __ADC__ Specifies ADC peripheral
  * @return ADC Maximum Injected Dat
  */
#define __LL_ADC_INJ_MaxDat_Get(__ADC__)                READ_BIT_SHIFT((__ADC__)->MAXJDR, ADC0_MAXJDR_MAXDATA_Msk, ADC0_MAXJDR_MAXDATA_Pos)


/**
  * @brief   ADC Minimum Injected Data Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  val ADC Minimum Injected Dat
  * @return None
  */
#define __LL_ADC_INJ_MinDat_Set(__ADC__, val)           \
        MODIFY_REG((__ADC__)->MINJDR, ADC0_MINJDR_MINDATA_Msk, (((val) & 0xffffUL) << ADC0_MINJDR_MINDATA_Pos))

/**
  * @brief   ADC Minimum Injected Data Get
  * @param  __ADC__ Specifies ADC peripheral
  * @return ADC Minimum Injected Dat
  */
#define __LL_ADC_INJ_MinDat_Get(__ADC__)                READ_BIT_SHIFT((__ADC__)->MINJDR, ADC0_MINJDR_MINDATA_Msk, ADC0_MINJDR_MINDATA_Pos)


/**
  * @brief  Injected Sequence Data Read
  * @param  __ADC__ Specifies ADC peripheral
  * @param  seq ADC_INJ_SeqNumETypeDef type Injected Sequence Number
  * @return Injected Sequence Data
  */
#define __LL_ADC_INJ_SeqDat_Read(__ADC__, seq)          READ_REG(__LL_ADC_REG_OFFSET((__ADC__)->JDR0, ((seq) % ADC_INJ_SEQ_NUMS)))


/**
  * @brief  AWDG Threshold High Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  num AWDG Number @ref ADC_AWDG_NumETypeDef
  * @param  thres AWDG Threshold High
  * @return None
  */
#define __LL_ADC_AWDG_ThresHigh_Set(__ADC__, num, thres)    \
        MODIFY_REG(__LL_ADC_REG_OFFSET((__ADC__)->TR0, ((num) % ADC_AWDG_NUMS)), ADC0_TR0_HT0_Msk, (((thres) & 0xffffUL) << ADC0_TR0_HT0_Pos))

/**
  * @brief  AWDG Threshold Low Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  num AWDG Number @ref ADC_AWDG_NumETypeDef
  * @param  thres AWDG Threshold Low
  * @return None
  */
#define __LL_ADC_AWDG_ThresLow_Set(__ADC__, num, thres)     \
        MODIFY_REG(__LL_ADC_REG_OFFSET((__ADC__)->TR0, ((num) % ADC_AWDG_NUMS)), ADC0_TR0_LT0_Msk, (((thres) & 0xffffUL) << ADC0_TR0_LT0_Pos))


/**
  * @brief  AWDG Filter Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  num AWDG Number @ref ADC_AWDG_NumETypeDef
  * @param  fil AWDG Filter
  * @return None
  */
#define __LL_ADC_AWDG_Filter_Set(__ADC__, num, fil)     MODIFY_REG(__LL_ADC_REG_OFFSET((__ADC__)->AWD0CR, ((num) % ADC_AWDG_NUMS)), \
        ADC0_AWD0CR_AWDFILT_Msk, (((fil) & 0xfUL) << ADC0_AWD0CR_AWDFILT_Pos))

/**
  * @brief  AWDG Channel Monitor Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @param  num AWDG Number @ref ADC_AWDG_NumETypeDef
  * @param  ch ADC_ChETypeDef type Channel Number
  * @return None
  */
#define __LL_ADC_AWDG_ChMonitor_En(__ADC__, num, ch)    \
        SET_BIT(__LL_ADC_REG_OFFSET((__ADC__)->AWD0CR, ((num) % ADC_AWDG_NUMS)), BIT(((ch) % ADC_CH_NUMS)))

/**
  * @brief  AWDG Channel Monitor Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @param  num AWDG Number @ref ADC_AWDG_NumETypeDef
  * @param  ch ADC_ChETypeDef type Channel Number
  * @return None
  */
#define __LL_ADC_AWDG_ChMonitor_Dis(__ADC__, num, ch)   \
        CLEAR_BIT(__LL_ADC_REG_OFFSET((__ADC__)->AWD0CR, ((num) % ADC_AWDG_NUMS)), BIT(((ch) % ADC_CH_NUMS)))


/**
  * @brief  Offset Coefficient Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  grp ADC_CalCoefGrpETypeDef type Calibration Coefficient Group
  * @param  coef Offset Coefficient
  * @return None
  */
#define __LL_ADC_OffsetCoef_Set(__ADC__, grp, coef)     \
        WRITE_REG(__LL_ADC_REG_OFFSET((__ADC__)->OFR0, ((grp) % ADC_CAL_COEF_GRP_NUMS)), ((coef) & 0xffffUL))


/**
  * @brief  Gain Coefficient Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  grp ADC_CalCoefGrpETypeDef type Calibration Coefficient Group
  * @param  coef Gain Coefficient
  * @return None
  */
#define __LL_ADC_GainCoef_Set(__ADC__, grp, coef)       \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) ?     \
        (WRITE_REG(__LL_ADC_REG_OFFSET((__ADC__)->GCR0, ((grp) % ADC_CAL_COEF_GRP_NUMS)), ((coef) & 0x7fffUL))) : \
        (WRITE_REG(__LL_ADC_REG_OFFSET((__ADC__)->GCR0, ((grp) % ADC_CAL_COEF_GRP_NUMS)), ((coef) & 0x3fffUL))))


/**
  * @brief  Judge is Channel Conversion Done Interrupt Pending or not
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @retval 0 isn't Channel Conversion Done Interrupt Pending
  * @retval 1 is Channel Conversion Done Interrupt Pending
  */
#define __LL_ADC_IsChConvDoneIntPnd(__ADC__, ch)        READ_BIT_SHIFT((__ADC__)->DISR, BIT(((ch) % ADC_CH_NUMS)), ((ch) % ADC_CH_NUMS))

/**
  * @brief  Channel Conversion Done Interrupt Pending Clear
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @return None
  */
#define __LL_ADC_ChConvDoneIntPnd_Clr(__ADC__, ch)      WRITE_REG((__ADC__)->DISR, BIT(((ch) % ADC_CH_NUMS)))

/**
  * @brief  ADC Sample All Interrupt Pending Get
  * @param  __ADC__ Specifies ADC peripheral
  * @return ADC Sample All Interrupt Pending
  */
#define __LL_ADC_SampAllIntPending_Get(__ADC__)         READ_REG((__ADC__)->DISR)


/**
  * @brief  Channel Conversion Done Interrupt Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @return None
  */
#define __LL_ADC_ChConvDone_INT_En(__ADC__, ch)         SET_BIT((__ADC__)->DIER, BIT(((ch) % ADC_CH_NUMS)))

/**
  * @brief  Channel Conversion Done Interrupt Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @return None
  */
#define __LL_ADC_ChConvDone_INT_Dis(__ADC__, ch)        CLEAR_BIT((__ADC__)->DIER, BIT(((ch) % ADC_CH_NUMS)))

/**
  * @brief  Judge is Channel Conversion Done Interrupt Enable or not
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @retval 0 Channel Conversion Done Interrupt is Disable
  * @retval 1 Channel Conversion Done Interrupt is Enable
  */
#define __LL_ADC_IsChConvDoneIntEn(__ADC__, ch)         READ_BIT_SHIFT((__ADC__)->DIER, BIT(((ch) % ADC_CH_NUMS)), ((ch) % ADC_CH_NUMS))

/**
  * @brief  ADC Sample All Interrupt Enable Status Get
  * @param  __ADC__ Specifies ADC peripheral
  * @return ADC Sample All Interrupt Enable Status
  */
#define __LL_ADC_SampAllIntEn_Get(__ADC__)              READ_REG((__ADC__)->DIER)


/**
  * @brief  Channel Data Read
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @return Channel Data
  */
#define __LL_ADC_ChDat_Read(__ADC__, ch)                READ_REG(__LL_ADC_REG_OFFSET((__ADC__)->CDR0, ((ch) % ADC_CH_NUMS)))


/**
  * @brief  Judge is Channel DMA Transfer Half Complete Interrupt Pending or not
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @retval 0 isn't Channel DMA Transfer Half Complete Interrupt Pending
  * @retval 1 is Channel DMA Transfer Half Complete Interrupt Pending
  */
#define __LL_ADC_IsChDMAHalfCpltIntPnd(__ADC__, ch)     READ_BIT_SHIFT((__ADC__)->HISR, BIT(((ch) % ADC_CH_NUMS)), ((ch) % ADC_CH_NUMS))

/**
  * @brief  Channel DMA Transfer Half Complete Interrupt Pending Clear
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @return None
  */
#define __LL_ADC_ChDMAHalfCpltIntPnd_Clr(__ADC__, ch)   WRITE_REG((__ADC__)->HISR, BIT(((ch) % ADC_CH_NUMS)))

/**
  * @brief  ADC DMA Transfer Half Complete All Interrupt Pending Get
  * @param  __ADC__ Specifies ADC peripheral
  * @return ADC DMA Transfer Half Complete All Interrupt Pending
  */
#define __LL_ADC_DMAHalfCpltAllIntPending_Get(__ADC__)  READ_REG((__ADC__)->HISR)


/**
  * @brief  Channel DMA Transfer Half Complete Interrupt Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @return None
  */
#define __LL_ADC_ChDMAHalfCplt_INT_En(__ADC__, ch)      SET_BIT((__ADC__)->HIER, BIT(((ch) % ADC_CH_NUMS)))

/**
  * @brief  Channel DMA Transfer Half Complete Interrupt Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @return None
  */
#define __LL_ADC_ChDMAHalfCplt_INT_Dis(__ADC__, ch)     CLEAR_BIT((__ADC__)->HIER, BIT(((ch) % ADC_CH_NUMS)))

/**
  * @brief  Judge is Channel DMA Transfer Half Complete Interrupt Enable or not
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @retval 0 Channel DMA Transfer Half Complete Interrupt is Disable
  * @retval 1 Channel DMA Transfer Half Complete Interrupt is Enable
  */
#define __LL_ADC_IsChDMAHalfCpltIntEn(__ADC__, ch)      READ_BIT_SHIFT((__ADC__)->HIER, BIT(((ch) % ADC_CH_NUMS)), ((ch) % ADC_CH_NUMS))

/**
  * @brief  ADC DMA Transfer Half Complete All Interrupt Enable Status Get
  * @param  __ADC__ Specifies ADC peripheral
  * @return ADC DMA Transfer Half Complete All Interrupt Enable Status
  */
#define __LL_ADC_DMAHalfCpltAllIntEn_Get(__ADC__)       READ_REG((__ADC__)->HIER)


/**
  * @brief  Judge is Channel DMA Transfer Complete Interrupt Pending or not
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @retval 0 isn't Channel DMA Transfer Complete Interrupt Pending
  * @retval 1 is Channel DMA Transfer Complete Interrupt Pending
  */
#define __LL_ADC_IsChDMACpltIntPnd(__ADC__, ch)         READ_BIT_SHIFT((__ADC__)->FISR, BIT(((ch) % ADC_CH_NUMS)), ((ch) % ADC_CH_NUMS))

/**
  * @brief  Channel DMA Transfer Complete Interrupt Pending Clear
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @return None
  */
#define __LL_ADC_ChDMACpltIntPnd_Clr(__ADC__, ch)       WRITE_REG((__ADC__)->FISR, BIT(((ch) % ADC_CH_NUMS)))

/**
  * @brief  ADC DMA Transfer Complete All Interrupt Pending Get
  * @param  __ADC__ Specifies ADC peripheral
  * @return ADC DMA Transfer Complete All Interrupt Pending
  */
#define __LL_ADC_DMACpltAllIntPending_Get(__ADC__)      READ_REG((__ADC__)->FISR)


/**
  * @brief  Channel DMA Transfer Complete Interrupt Enable
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @return None
  */
#define __LL_ADC_ChDMACplt_INT_En(__ADC__, ch)          SET_BIT((__ADC__)->FIER, BIT(((ch) % ADC_CH_NUMS)))

/**
  * @brief  Channel DMA Transfer Complete Interrupt Disable
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @return None
  */
#define __LL_ADC_ChDMACplt_INT_Dis(__ADC__, ch)         CLEAR_BIT((__ADC__)->FIER, BIT(((ch) % ADC_CH_NUMS)))

/**
  * @brief  Judge is Channel DMA Transfer Complete Interrupt Enable or not
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @retval 0 Channel DMA Transfer Complete Interrupt is Disable
  * @retval 1 Channel DMA Transfer Complete Interrupt is Enable
  */
#define __LL_ADC_IsChDMACpltIntEn(__ADC__, ch)          READ_BIT_SHIFT((__ADC__)->FIER, BIT(((ch) % ADC_CH_NUMS)), ((ch) % ADC_CH_NUMS))

/**
  * @brief  ADC DMA Transfer Complete All Interrupt Enable Status Get
  * @param  __ADC__ Specifies ADC peripheral
  * @return ADC DMA Transfer Complete All Interrupt Enable Status
  */
#define __LL_ADC_DMACpltAllIntEn_Get(__ADC__)           READ_REG((__ADC__)->FIER)


/**
  * @brief  Channel DMA Fix Address Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @param  en bool type DMA Fix Address Enable
  * @return Channel Data
  */
#define __LL_ADC_ChDMAFixAddr_Set(__ADC__, ch, en)                                      \
        MODIFY_REG(__LL_ADC_DMA_REG_OFFSET((__ADC__)->TCR0, ((ch) % ADC_CH_NUMS)).TCR,  \
        ADC0_TCR0_FIX_Msk, ((!!(en)) << ADC0_TCR0_FIX_Pos))

/**
  * @brief  Channel DMA Circulation Mode Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @param  en bool type DMA Circulation Mode Enable
  * @return Channel Data
  */
#define __LL_ADC_ChDMACircMode_Set(__ADC__, ch, en)                                     \
        MODIFY_REG(__LL_ADC_DMA_REG_OFFSET((__ADC__)->TCR0, ((ch) % ADC_CH_NUMS)).TCR,  \
        ADC0_TCR0_CIRC_Msk, ((!!(en)) << ADC0_TCR0_CIRC_Pos))

/**
  * @brief  Channel DMA Stop
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @return None
  */
#define __LL_ADC_ChDMA_Stop(__ADC__, ch)                \
        SET_BIT(__LL_ADC_DMA_REG_OFFSET((__ADC__)->TCR0, ((ch) % ADC_CH_NUMS)).TCR, ADC0_TCR0_STP_Msk)

/**
  * @brief  Judge is Channel DMA Stopping or not
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @retval 0 isn't Channel DMA Stopping
  * @retval 1 is Channel DMA Stopping
  */
#define __LL_ADC_IsChDMAStopping(__ADC__, ch)           \
        READ_BIT_SHIFT(__LL_ADC_DMA_REG_OFFSET((__ADC__)->TCR0, ((ch) % ADC_CH_NUMS)).TCR, ADC0_TCR0_STP_Msk, ADC0_TCR0_STP_Pos)

/**
  * @brief  Channel DMA Start
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @return None
  */
#define __LL_ADC_ChDMA_Start(__ADC__, ch)               \
        SET_BIT(__LL_ADC_DMA_REG_OFFSET((__ADC__)->TCR0, ((ch) % ADC_CH_NUMS)).TCR, ADC0_TCR0_START_Msk)


/**
  * @brief  Channel DMA Transfer Address Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @param  addr Channel DMA Transfer Address
  * @return None
  */
#define __LL_ADC_ChDMATransAddr_Set(__ADC__, ch, addr)  \
        WRITE_REG(__LL_ADC_DMA_REG_OFFSET((__ADC__)->TCR0, ((ch) % ADC_CH_NUMS)).TAR, addr)


/**
  * @brief  Channel DMA Transfer Length Set
  * @param  __ADC__ Specifies ADC peripheral
  * @param  ch ADC_ChETypeDef type Channel Number
  * @param  len Channel DMA Transfer Length
  * @return None
  */
#define __LL_ADC_ChDMATransLen_Set(__ADC__, ch, len)    \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) ?     \
        (WRITE_REG(__LL_ADC_DMA_REG_OFFSET((__ADC__)->TCR0, ((ch) % ADC_CH_NUMS)).TLR, ((len) & 0xffffUL))) : \
        (WRITE_REG(__LL_ADC_DMA_REG_OFFSET((__ADC__)->TCR0, ((ch) % ADC_CH_NUMS)).TLR, ((len) & 0x1fffUL))))


/**
  * @brief  Daul ADC Sample Phase Delay Set
  * @note   Only Master ADC Valid
  * @param  __ADC__ Specifies ADC peripheral
  * @param  dly Daul ADC Sample Phase Delay
  * @return None
  */
#define __LL_ADC_DualSampPhaseDly_Set(__ADC__, dly)     \
        MODIFY_REG((__ADC__)->CCR, ADC0_CCR_DELAY_Msk, (((dly) & 0x3ffUL) << ADC0_CCR_DELAY_Pos))

/**
  * @brief  Daul ADC Mode Set
  * @note   Dual mode Only Master ADC Valid
  *         Quad mode Only Master ADC0/2 Valid
  * @param  __ADC__ Specifies ADC peripheral
  * @param  mode Daul ADC Mode
  * @return None
  */
#define __LL_ADC_DualMode_Set(__ADC__, mode)            \
        MODIFY_REG((__ADC__)->CCR, ADC0_CCR_DUAL_Msk, (((mode) & 0xfUL) << ADC0_CCR_DUAL_Pos))

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup ADC_LL_Exported_Types ADC LL Exported Types
  * @brief    ADC LL Exported Types
  * @{
  */

/**
  * @brief ADC Channel Definition
  */
typedef enum {
    ADC_CH_0 = 0,                   /*!< ADC Channel 0  */
    ADC_CH_1,                       /*!< ADC Channel 1  */
    ADC_CH_2,                       /*!< ADC Channel 2  */
    ADC_CH_3,                       /*!< ADC Channel 3  */
    ADC_CH_4,                       /*!< ADC Channel 4  */
    ADC_CH_5,                       /*!< ADC Channel 5  */
    ADC_CH_6,                       /*!< ADC Channel 6  */
    ADC_CH_7,                       /*!< ADC Channel 7  */
    ADC_CH_8,                       /*!< ADC Channel 8  */
    ADC_CH_9,                       /*!< ADC Channel 9  */
    ADC_CH_10,                      /*!< ADC Channel 10 */
    ADC_CH_11,                      /*!< ADC Channel 11 */
    ADC_CH_12,                      /*!< ADC Channel 12 */
    ADC_CH_13,                      /*!< ADC Channel 13 */
    ADC_CH_14,                      /*!< ADC Channel 14 */
    ADC_CH_15,                      /*!< ADC Channel 15 */
    ADC_CH_16,                      /*!< ADC Channel 16 */
    ADC_CH_17,                      /*!< ADC Channel 17 */
    ADC_CH_18,                      /*!< ADC Channel 18 */
    ADC_CH_19,                      /*!< ADC Channel 19 */
    ADC_CH_NUMS,                    /*!< ADC Ch Nums    */
} ADC_ChETypeDef;

/**
  * @brief ADC Regular Sequence Number Definition
  */
typedef enum {
    ADC_REG_SEQ_NUM_1 = 0,          /*!< ADC Regular Sequence Number 1  */
    ADC_REG_SEQ_NUM_2,              /*!< ADC Regular Sequence Number 2  */
    ADC_REG_SEQ_NUM_3,              /*!< ADC Regular Sequence Number 3  */
    ADC_REG_SEQ_NUM_4,              /*!< ADC Regular Sequence Number 4  */
    ADC_REG_SEQ_NUM_5,              /*!< ADC Regular Sequence Number 5  */
    ADC_REG_SEQ_NUM_6,              /*!< ADC Regular Sequence Number 6  */
    ADC_REG_SEQ_NUM_7,              /*!< ADC Regular Sequence Number 7  */
    ADC_REG_SEQ_NUM_8,              /*!< ADC Regular Sequence Number 8  */
    ADC_REG_SEQ_NUM_9,              /*!< ADC Regular Sequence Number 9  */
    ADC_REG_SEQ_NUM_10,             /*!< ADC Regular Sequence Number 10 */
    ADC_REG_SEQ_NUM_11,             /*!< ADC Regular Sequence Number 11 */
    ADC_REG_SEQ_NUM_12,             /*!< ADC Regular Sequence Number 12 */
    ADC_REG_SEQ_NUM_13,             /*!< ADC Regular Sequence Number 13 */
    ADC_REG_SEQ_NUM_14,             /*!< ADC Regular Sequence Number 14 */
    ADC_REG_SEQ_NUM_15,             /*!< ADC Regular Sequence Number 15 */
    ADC_REG_SEQ_NUM_16,             /*!< ADC Regular Sequence Number 16 */
    ADC_REG_SEQ_NUMS,               /*!< ADC Regular Sequence Numbers   */
} ADC_REG_SeqNumETypeDef;

/**
  * @brief ADC Injected Sequence Number Definition
  */
typedef enum {
    ADC_INJ_SEQ_NUM_1 = 0,          /*!< ADC Injected Sequence Number 1   */
    ADC_INJ_SEQ_NUM_2,              /*!< ADC Injected Sequence Number 2   */
    ADC_INJ_SEQ_NUM_3,              /*!< ADC Injected Sequence Number 3   */
    ADC_INJ_SEQ_NUM_4,              /*!< ADC Injected Sequence Number 4   */
    ADC_INJ_SEQ_NUMS,               /*!< ADC Injected Sequence Numbers    */
} ADC_INJ_SeqNumETypeDef;

/**
  * @brief ADC AWDG Number Definition
  */
typedef enum {
    ADC_AWDG_NUM_0 = 0,             /*!< ADC AWDG Number 0  */
    ADC_AWDG_NUM_1,                 /*!< ADC AWDG Number 1  */
    ADC_AWDG_NUM_2,                 /*!< ADC AWDG Number 2  */
    ADC_AWDG_NUMS,                  /*!< ADC AWDG Numbers   */
} ADC_AWDG_NumETypeDef;

/**
  * @brief ADC Channel Calibration Coefficient Group Definition
  */
typedef enum {
    ADC_CAL_COEF_GRP_0 = 0,         /*!< ADC Channel Calibration Coefficient Group 0    */
    ADC_CAL_COEF_GRP_1,             /*!< ADC Channel Calibration Coefficient Group 1    */
    ADC_CAL_COEF_GRP_2,             /*!< ADC Channel Calibration Coefficient Group 2    */
    ADC_CAL_COEF_GRP_3,             /*!< ADC Channel Calibration Coefficient Group 3    */
    ADC_CAL_COEF_GRP_NUMS,          /*!< ADC Channel Calibration Coefficient Group Nums */
} ADC_CalCoefGrpETypeDef;


/**
  * @brief Regular Discontinuous Conversion Numbers Definition
  */
typedef enum {
    ADC_REG_DISCONT_CONV_NUM_1 = 0, /*!< Regular Discontinuous Conversion Numbers 1 */
    ADC_REG_DISCONT_CONV_NUM_2,     /*!< Regular Discontinuous Conversion Numbers 2 */
    ADC_REG_DISCONT_CONV_NUM_3,     /*!< Regular Discontinuous Conversion Numbers 3 */
    ADC_REG_DISCONT_CONV_NUM_4,     /*!< Regular Discontinuous Conversion Numbers 4 */
    ADC_REG_DISCONT_CONV_NUM_5,     /*!< Regular Discontinuous Conversion Numbers 5 */
    ADC_REG_DISCONT_CONV_NUM_6,     /*!< Regular Discontinuous Conversion Numbers 6 */
    ADC_REG_DISCONT_CONV_NUM_7,     /*!< Regular Discontinuous Conversion Numbers 7 */
    ADC_REG_DISCONT_CONV_NUM_8,     /*!< Regular Discontinuous Conversion Numbers 8 */
} ADC_REG_DisContConvNumETypeDef;

/**
  * @brief ADC Regular Sequence Length Definition
  */
typedef enum {
    ADC_REG_SEQ_LEN_1 = 0,          /*!< ADC Regular Sequence Length 1  */
    ADC_REG_SEQ_LEN_2,              /*!< ADC Regular Sequence Length 2  */
    ADC_REG_SEQ_LEN_3,              /*!< ADC Regular Sequence Length 3  */
    ADC_REG_SEQ_LEN_4,              /*!< ADC Regular Sequence Length 4  */
    ADC_REG_SEQ_LEN_5,              /*!< ADC Regular Sequence Length 5  */
    ADC_REG_SEQ_LEN_6,              /*!< ADC Regular Sequence Length 6  */
    ADC_REG_SEQ_LEN_7,              /*!< ADC Regular Sequence Length 7  */
    ADC_REG_SEQ_LEN_8,              /*!< ADC Regular Sequence Length 8  */
    ADC_REG_SEQ_LEN_9,              /*!< ADC Regular Sequence Length 9  */
    ADC_REG_SEQ_LEN_10,             /*!< ADC Regular Sequence Length 10 */
    ADC_REG_SEQ_LEN_11,             /*!< ADC Regular Sequence Length 11 */
    ADC_REG_SEQ_LEN_12,             /*!< ADC Regular Sequence Length 12 */
    ADC_REG_SEQ_LEN_13,             /*!< ADC Regular Sequence Length 13 */
    ADC_REG_SEQ_LEN_14,             /*!< ADC Regular Sequence Length 14 */
    ADC_REG_SEQ_LEN_15,             /*!< ADC Regular Sequence Length 15 */
    ADC_REG_SEQ_LEN_16,             /*!< ADC Regular Sequence Length 16 */
} ADC_REG_SeqLenETypeDef;

/**
  * @brief Regular Conversion Mode Definition
  */
typedef enum {
    ADC_REG_CONV_SINGLE = 0,        /*!< Regular Conversion Mode Single     */
    ADC_REG_CONV_CONTINUOUS,        /*!< Regular Conversion Mode Continuous */
} ADC_REG_ConvModeETypeDef;

/**
  * @brief ADC Channel Input Mode Definition
  */
typedef enum {
    ADC_INPUT_MODE_SINGLE_END = 0,  /*!< ADC Channel Input Mode Single-End      */
    ADC_INPUT_MODE_DIFF,            /*!< ADC Channel Input Mode Differential    */
} ADC_InputModeETypeDef;

/**
  * @brief ADC Channel Sample Time Definition
  */
typedef enum {
    ADC_SAMP_TIME_2_CYCLES = 0,     /*!< ADC Channel Sample Time 2 Cycles   */
    ADC_SAMP_TIME_6_CYCLES,         /*!< ADC Channel Sample Time 6 Cycles   */
    ADC_SAMP_TIME_14_CYCLES,        /*!< ADC Channel Sample Time 14 Cycles  */
    ADC_SAMP_TIME_30_CYCLES,        /*!< ADC Channel Sample Time 30 Cycles  */
    ADC_SAMP_TIME_62_CYCLES,        /*!< ADC Channel Sample Time 62 Cycles  */
    ADC_SAMP_TIME_126_CYCLES,       /*!< ADC Channel Sample Time 126 Cycles */
    ADC_SAMP_TIME_254_CYCLES,       /*!< ADC Channel Sample Time 254 Cycles */
    ADC_SAMP_TIME_510_CYCLES,       /*!< ADC Channel Sample Time 510 Cycles */
} ADC_SampTimeETypeDef;

/**
  * @brief ADC Injected Sequence Length Definition
  */
typedef enum {
    ADN_INJ_SEQ_LEN_1 = 0,          /*!< ADC Injected Sequence Length 1 */
    ADN_INJ_SEQ_LEN_2,              /*!< ADC Injected Sequence Length 2 */
    ADN_INJ_SEQ_LEN_3,              /*!< ADC Injected Sequence Length 3 */
    ADN_INJ_SEQ_LEN_4,              /*!< ADC Injected Sequence Length 4 */
} ADC_INJ_SeqLenETypeDef;


/**
  * @brief Normal Channel Oversample Mode Definition
  */
typedef enum {
    ADC_NORM_OVER_SAMP_CONTINUE = 0,/*!< Normal Channel Oversample Mode Continue    */
    ADC_NORM_OVER_SAMP_RESUME,      /*!< Normal Channel Oversample Mode Resume      */
} ADC_NormOverSampModeETypeDef;

/**
  * @brief Overrun Mode Definition
  */
typedef enum {
    ADC_OVERRUN_DATA_PRESERVED = 0, /*!< Overrun Mode Preserved     */
    ADC_OVERRUN_DATA_OVERWRITTEN,   /*!< Overrun Mode Overwriten    */
} ADC_OverRunModeETypeDef;

/**
  * @brief Over Sample Data Shift Definition
  */
typedef enum {
    ADC_OVER_SAMP_SHIFT_NONE = 0,   /*!< Over Sample Data Shift None    */
    ADC_OVER_SAMP_SHIFT_RIGHT_1,    /*!< Over Sample Data Shift Right 1 */
    ADC_OVER_SAMP_SHIFT_RIGHT_2,    /*!< Over Sample Data Shift Right 2 */
    ADC_OVER_SAMP_SHIFT_RIGHT_3,    /*!< Over Sample Data Shift Right 3 */
    ADC_OVER_SAMP_SHIFT_RIGHT_4,    /*!< Over Sample Data Shift Right 4 */
    ADC_OVER_SAMP_SHIFT_RIGHT_5,    /*!< Over Sample Data Shift Right 5 */
    ADC_OVER_SAMP_SHIFT_RIGHT_6,    /*!< Over Sample Data Shift Right 6 */
    ADC_OVER_SAMP_SHIFT_RIGHT_7,    /*!< Over Sample Data Shift Right 7 */
    ADC_OVER_SAMP_SHIFT_RIGHT_8,    /*!< Over Sample Data Shift Right 8 */
} ADC_OverSampShiftETypeDef;

/**
  * @brief Over Sample Ratio Definition
  */
typedef enum {
    ADC_OVER_SAMP_RATIO_2 = 0,      /*!< Over Sample Ratio 2    */
    ADC_OVER_SAMP_RATIO_4,          /*!< Over Sample Ratio 4    */
    ADC_OVER_SAMP_RATIO_8,          /*!< Over Sample Ratio 8    */
    ADC_OVER_SAMP_RATIO_16,         /*!< Over Sample Ratio 16   */
    ADC_OVER_SAMP_RATIO_32,         /*!< Over Sample Ratio 32   */
    ADC_OVER_SAMP_RATIO_64,         /*!< Over Sample Ratio 64   */
    ADC_OVER_SAMP_RATIO_128,        /*!< Over Sample Ratio 128  */
    ADC_OVER_SAMP_RATIO_256,        /*!< Over Sample Ratio 256  */
} ADC_OverSampRatioETypeDef;


/**
  * @brief ADC Bias Current Definition
  */
typedef enum {
    ADC_BIAS_CUR_10uA = 0,          /*!< ADC Bias Current 10uA  */
    ADC_BIAS_CUR_12uA,              /*!< ADC Bias Current 12uA  */
    ADC_BIAS_CUR_14uA,              /*!< ADC Bias Current 14uA  */
    ADC_BIAS_CUR_8uA,               /*!< ADC Bias Current 8uA   */
} ADC_BiasCurETypeDef;

/**
  * @brief ADC Daul Mode Definition
  * @note  Dual mode Only Master ADC Valid
  *        Quad mode Only Master ADC0/2 Valid
  */
typedef enum {
    ADC_DUAL_MODE_INDEPEND = 0,     /*!< ADC Daul Mode Independent                          */
    ADC_DUAL_MODE_REG_INJ_SYNC,     /*!< ADC Daul Mode Regular and Injected Sync            */
    ADC_DUAL_MODE_REG_SYNC_INJ_TRIG,/*!< ADC Daul Mode Regular Sync and Injected Trigger    */
    ADC_DUAL_MODE_REG_TRIG_INJ_SYNC,/*!< ADC Daul Mode Regular Trigger and Injected Sync    */
    ADC_DUAL_MODE_INJ_SYNC,         /*!< ADC Daul Mode Injected Sync                        */
    ADC_DUAL_MODE_REG_SYNC,         /*!< ADC Daul Mode Regular Sync                         */
    ADC_DUAL_MODE_REG_INTERLEAVED,  /*!< ADC Daul Mode Regular InterleaveD                  */
    ADC_DUAL_MODE_INJ_TRIG,         /*!< ADC Daul Mode Injected Trigger                     */

    ADC_QUAD_MODE_INJ_SYNC = 12,    /*!< ADC Quad Mode Injected Sync                        */
    ADC_QUAD_MODE_REG_SYNC,         /*!< ADC Quad Mode Regular Sync                         */
} ADC_DualModeETypeDef;


/**
  * @brief ADC Sequence Trigger Polarity Definition
  */
typedef enum {
    ADC_SEQ_TRIG_POL_SW = 0,        /*!< ADC Sequence Trigger Polarity Software             */
    ADC_SEQ_TRIG_POL_HW_RISING,     /*!< ADC Sequence Trigger Polarity Hardware Rising      */
    ADC_SEQ_TRIG_POL_HW_FALLING,    /*!< ADC Sequence Trigger Polarity Hardware Falling     */
    ADC_SEQ_TRIG_POL_HW_BOTH_EDGE,  /*!< ADC Sequence Trigger Polarity Hardware Both Edge   */
} ADC_SeqTrigPolETypeDef;

/**
  * @brief ADC Sequence Trigger Event Definition
  */
typedef enum {
    ADC_SEQ_TRIG_EVT_TMR7_TRGO = 0, /*!< ADC Sequence Trigger Event TMR7_TRGO       */
    ADC_SEQ_TRIG_EVT_TMR8_TRGO,     /*!< ADC Sequence Trigger Event TMR8_TRGO       */
    ADC_SEQ_TRIG_EVT_TMR0_CC0,      /*!< ADC Sequence Trigger Event TMR0_CC0        */
    ADC_SEQ_TRIG_EVT_TMR1_CC0,      /*!< ADC Sequence Trigger Event TMR1_CC0        */
    ADC_SEQ_TRIG_EVT_TMR2_CC0,      /*!< ADC Sequence Trigger Event TMR2_CC0        */
    ADC_SEQ_TRIG_EVT_TMR0_TRGO,     /*!< ADC Sequence Trigger Event TMR0_TRGO       */
    ADC_SEQ_TRIG_EVT_TMR1_TRGO,     /*!< ADC Sequence Trigger Event TMR1_TRGO       */
    ADC_SEQ_TRIG_EVT_TMR2_TRGO,     /*!< ADC Sequence Trigger Event TMR2_TRGO       */
    ADC_SEQ_TRIG_EVT_TMR3_CC0,      /*!< ADC Sequence Trigger Event TMR3_CC0        */
    ADC_SEQ_TRIG_EVT_TMR3_CC1,      /*!< ADC Sequence Trigger Event TMR3_CC1        */
    ADC_SEQ_TRIG_EVT_TMR3_TRGO,     /*!< ADC Sequence Trigger Event TMR3_TRGO       */
    ADC_SEQ_TRIG_EVT_TMR4_CC0,      /*!< ADC Sequence Trigger Event TMR4_CC0        */
    ADC_SEQ_TRIG_EVT_TMR4_CC1,      /*!< ADC Sequence Trigger Event TMR4_CC1        */
    ADC_SEQ_TRIG_EVT_TMR4_TRGO,     /*!< ADC Sequence Trigger Event TMR4_TRGO       */
    ADC_SEQ_TRIG_EVT_TMR9_CC0,      /*!< ADC Sequence Trigger Event TMR9_CC0        */
    ADC_SEQ_TRIG_EVT_TMR9_CC1,      /*!< ADC Sequence Trigger Event TMR9_CC1        */
    ADC_SEQ_TRIG_EVT_TMR9_TRGO,     /*!< ADC Sequence Trigger Event TMR9_TRGO       */
    ADC_SEQ_TRIG_EVT_TMR10_CC0,     /*!< ADC Sequence Trigger Event TMR10_CC0       */
    ADC_SEQ_TRIG_EVT_TMR10_CC1,     /*!< ADC Sequence Trigger Event TMR10_CC1       */
    ADC_SEQ_TRIG_EVT_TMR10_CC2,     /*!< ADC Sequence Trigger Event TMR10_CC2       */
    ADC_SEQ_TRIG_EVT_TMR10_TRGO,    /*!< ADC Sequence Trigger Event TMR10_TRGO      */
    ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG0, /*!< ADC Sequence Trigger Event HRPWM_ADCTRG0   */
    ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG1, /*!< ADC Sequence Trigger Event HRPWM_ADCTRG1   */
    ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG2, /*!< ADC Sequence Trigger Event HRPWM_ADCTRG2   */
    ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG3, /*!< ADC Sequence Trigger Event HRPWM_ADCTRG3   */
    ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG4, /*!< ADC Sequence Trigger Event HRPWM_ADCTRG4   */
    ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG5, /*!< ADC Sequence Trigger Event HRPWM_ADCTRG5   */
    ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG6, /*!< ADC Sequence Trigger Event HRPWM_ADCTRG6   */
    ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG7, /*!< ADC Sequence Trigger Event HRPWM_ADCTRG7   */
    ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG8, /*!< ADC Sequence Trigger Event HRPWM_ADCTRG8   */
    ADC_SEQ_TRIG_EVT_HRPWM_ADCTRG9, /*!< ADC Sequence Trigger Event HRPWM_ADCTRG9   */
    ADC_SEQ_TRIG_EVT_EXT_PIN_PA_8_9,/*!< ADC Sequence Trigger Event Ext Pin PA8/PA9 */
} ADC_SeqTrigEvtETypeDef;


/**
  * @brief ADC Calibration Mode Definition
  */
typedef enum {
    ADC_CAL_MODE_SINGLE_END = 0,  /*!< ADC Calibration Mode Single-End      */
    ADC_CAL_MODE_DIFF,            /*!< ADC Calibration Mode Differential    */
} ADC_CalModeETypeDef;


/**
  * @brief ADC LL Config Definition
  */
typedef struct __ADC_LLCfgTypeDef {
    ADC_BiasCurETypeDef bias_cur;                   /*!< ADC Bias Current           */
    bool sys_dma_req_en;                            /*!< System DMA Request Enable  */
} ADC_LLCfgTypeDef;

/**
  * @brief ADC Oversample Config Definition
  */
typedef struct __ADC_OverSamp_CfgTypeDef {
    bool trig_en;                                   /*!< Trigger Oversample Enable      */
    ADC_OverSampShiftETypeDef shift;                /*!< Oversample Right Shift         */
    ADC_OverSampRatioETypeDef ratio;                /*!< Oversample Ratio               */
    ADC_NormOverSampModeETypeDef norm_mode;         /*!< Normal Channel Oversample Mode */

    bool reg_en;                                    /*!< Regular Oversample Enable      */
    bool inj_en;                                    /*!< Injected Oversample Enable     */
} ADC_OverSamp_CfgTypeDef;


/**
  * @brief ADC Initialization Structure Definition
  */
typedef struct __ADC_InitTypeDef {
    uint16_t                dual_phase_dly;         /*!< ADC Dual Sample Phase Delay    */
    ADC_DualModeETypeDef    dual_mode;              /*!< ADC Dual Mode                  */
    ADC_OverRunModeETypeDef overrun_mode;           /*!< ADC Overrun Mode               */

    ADC_OverSamp_CfgTypeDef over_samp_cfg;          /*!< Oversample Config              */
    ADC_LLCfgTypeDef       *ll_cfg;                 /*!< Optional LL Config Pointer     */
} ADC_InitTypeDef;


/**
  * @brief ADC Regular Common Config Definition
  */
typedef struct __ADC_REG_ComCfgTypeDef {
    bool                           dis_cont_en;     /*!< Discontinuous Enable           */
    ADC_REG_ConvModeETypeDef       conv_mode;       /*!< Conversion Mode                */
    ADC_REG_DisContConvNumETypeDef dis_cont_nums;   /*!< Discontinuous Sample Numbers   */

    ADC_REG_SeqLenETypeDef seq_len;                 /*!< Regular Sequence Length        */
    ADC_SeqTrigPolETypeDef trig_pol;                /*!< Regular Trigger Polarity       */
    ADC_SeqTrigEvtETypeDef trig_evt;                /*!< Regular Trigger Event          */
} ADC_REG_ComCfgTypeDef;

/**
  * @brief ADC Regular Channel Config Definition
  */
typedef struct __ADC_REG_ChCfgTypeDef {
    ADC_REG_SeqNumETypeDef seq_num;                 /*!< Sequence Number            */
    ADC_ChETypeDef         ch;                      /*!< ADC Channel                */

    bool                  done_int_en;              /*!< Conv Done Interrupt Enable */
    ADC_InputModeETypeDef input_mode;               /*!< Input Mode                 */
    ADC_SampTimeETypeDef  samp_time;                /*!< Sample Time                */
} ADC_REG_ChCfgTypeDef;

/**
  * @brief ADC Injected Common Config Definition
  */
typedef struct __ADC_INJ_ComCfgTypeDef {
    bool auto_conv_en;                              /*!< Auto Conversion Enable     */
    bool dis_cont_en;                               /*!< Discontinuous Enable       */

    ADC_INJ_SeqLenETypeDef seq_len;                 /*!< Injected Sequence Length   */
    ADC_SeqTrigPolETypeDef trig_pol;                /*!< Injected Trigger Polarity  */
    ADC_SeqTrigEvtETypeDef trig_evt;                /*!< Injected Trigger Event     */
} ADC_INJ_ComCfgTypeDef;

/**
  * @brief ADC Injected Channel Config Definition
  */
typedef struct __ADC_INJ_ChCfgTypeDef {
    ADC_INJ_SeqNumETypeDef seq_num;                 /*!< Sequence Number    */
    ADC_ChETypeDef         ch;                      /*!< ADC Channel        */

    ADC_InputModeETypeDef  input_mode;              /*!< Input Mode         */
    ADC_SampTimeETypeDef   samp_time;               /*!< Sample Time        */
} ADC_INJ_ChCfgTypeDef;

/**
  * @brief ADC AWDG Common Config Definition
  */
typedef struct __ADC_AWDG_ComCfgTypeDef {
    ADC_AWDG_NumETypeDef awdg_num;                  /*!< AWDG Number                    */

    bool reg_mon_en;                                /*!< AWDG Minitor Regular Sequence  */
    bool inj_mon_en;                                /*!< AWDG Minitor Injected Sequence */

    uint8_t filter;                                 /*!< Filter                         */
    int16_t thres_high;                             /*!< Threshold High                 */
    int16_t thres_low;                              /*!< Threshold Low                  */
} ADC_AWDG_ComCfgTypeDef;

/**
  * @brief ADC AWDG Channel Config Definition
  */
typedef struct __ADC_AWDG_ChCfgTypeDef {
    bool                 ch_mon_en;                 /*!< Channel Monitor Enable */
    ADC_AWDG_NumETypeDef awdg_num;                  /*!< AWDG Number            */
    ADC_ChETypeDef       ch;                        /*!< ADC Channel            */
} ADC_AWDG_ChCfgTypeDef;

/**
  * @brief ADC DMA Config Definition
  */
typedef struct __ADC_DMA_CfgTypeDef {
    ADC_ChETypeDef ch;                              /*!< ADC Channel                    */

    bool circ_en;                                   /*!< Circulation Mode Enable        */
    bool fix_addr_en;                               /*!< Fix Address Enable             */
    bool half_int_en;                               /*!< Half Complete Interrupt Enable */
    bool cplt_int_en;                               /*!< Complete Interrupt Enable      */

    uint32_t addr;                                  /*!< DMA Transfer Address           */
    uint16_t len;                                   /*!< DMA Transfer Length            */
} ADC_DMA_CfgTypeDef;

/**
  * @brief ADC Calibration Config Definition
  */
typedef struct __ADC_Cal_CfgTypeDef {
    ADC_ChETypeDef         ch;                      /*!< ADC Channel                    */
    ADC_CalCoefGrpETypeDef coef_grp;                /*!< Calibration Coefficient Group  */

    bool     sat_dis;                               /*!< Saturation Disable             */
    int16_t  offset;                                /*!< Offset Calibration Coefficient */
    uint16_t gain;                                  /*!< Gain Calibration Coefficient   */
} ADC_Cal_CfgTypeDef;

/**
  * @brief ADC all software Calibration Config Definition
  */
typedef struct _self_cali {
    int16_t offset;
    uint16_t gain;
} ADC_CALI_TYPE;

typedef struct _cali {
    ADC_CALI_TYPE ADC0_SIG;
    ADC_CALI_TYPE ADC0_DIF;
    ADC_CALI_TYPE ADC1_SIG;
    ADC_CALI_TYPE ADC1_DIF;
    ADC_CALI_TYPE ADC2_SIG;
    ADC_CALI_TYPE ADC2_DIF;
    ADC_CALI_TYPE ADC3_SIG;
    ADC_CALI_TYPE ADC3_DIF;
} ADC_CALI_ALL_TYPE;

/**
  * @brief ADC Auto-calibration Config Definition
  */
typedef struct __ADC_AutoCal_CfgTypeDef {
    ADC_ChETypeDef            ch;                       /*!< ADC Channel            */
    ADC_CalModeETypeDef       mode;                     /*!< Auto-calibration Mode  */
    ADC_OverSampRatioETypeDef auto_cal_ratio;           /*!< Auto-calibration Ratio */
} ADC_AutoCal_CfgTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup ADC_LL_Exported_Functions
  * @{
  */

/** @addtogroup ADC_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_ADC_Init(ADC_TypeDef *Instance, ADC_InitTypeDef *init);
LL_StatusETypeDef LL_ADC_DeInit(ADC_TypeDef *Instance);
void LL_ADC_MspInit(ADC_TypeDef *Instance);
void LL_ADC_MspDeInit(ADC_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup ADC_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_ADC_OverSamp_Cfg(ADC_TypeDef *Instance, ADC_OverSamp_CfgTypeDef *cfg);
LL_StatusETypeDef LL_ADC_REG_ComCfg(ADC_TypeDef *Instance, ADC_REG_ComCfgTypeDef *cfg);
LL_StatusETypeDef LL_ADC_REG_ChCfg(ADC_TypeDef *Instance, ADC_REG_ChCfgTypeDef *cfg);
LL_StatusETypeDef LL_ADC_INJ_ComCfg(ADC_TypeDef *Instance, ADC_INJ_ComCfgTypeDef *cfg);
LL_StatusETypeDef LL_ADC_INJ_ChCfg(ADC_TypeDef *Instance, ADC_INJ_ChCfgTypeDef *cfg);
LL_StatusETypeDef LL_ADC_AWDG_ComCfg(ADC_TypeDef *Instance, ADC_AWDG_ComCfgTypeDef *cfg);
LL_StatusETypeDef LL_ADC_AWDG_ChCfg(ADC_TypeDef *Instance, ADC_AWDG_ChCfgTypeDef *cfg);
LL_StatusETypeDef LL_ADC_DMA_Cfg(ADC_TypeDef *Instance, ADC_DMA_CfgTypeDef *cfg);
LL_StatusETypeDef LL_ADC_Cal_Cfg(ADC_TypeDef *Instance, ADC_Cal_CfgTypeDef *cfg);
LL_StatusETypeDef LL_ADC_AutoCal_Cfg(ADC_TypeDef *Instance, ADC_AutoCal_CfgTypeDef *cfg);

LL_StatusETypeDef LL_ADC_Single_Calibration(ADC_TypeDef *Instance);
LL_StatusETypeDef LL_ADC_Differ_Calibration(ADC_TypeDef *Instance);


/**
  * @}
  */


/** @addtogroup ADC_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_ADC_Norm_IRQHandler(ADC_TypeDef *Instance);
void LL_ADC_Norm_SampEndCallback(ADC_TypeDef *Instance);
void LL_ADC_Norm_ReadyCallback(ADC_TypeDef *Instance);
void LL_ADC_Norm_AWDG2Callback(ADC_TypeDef *Instance);
void LL_ADC_Norm_AWDG1Callback(ADC_TypeDef *Instance);
void LL_ADC_Norm_AWDG0Callback(ADC_TypeDef *Instance);
void LL_ADC_Norm_OverflowCallback(ADC_TypeDef *Instance);
void LL_ADC_Norm_INJ_SeqEndCallback(ADC_TypeDef *Instance);
void LL_ADC_Norm_INJ_ConvEndCallback(ADC_TypeDef *Instance);
void LL_ADC_Norm_REG_SeqEndCallback(ADC_TypeDef *Instance);
void LL_ADC_Norm_REG_ConvEndCallback(ADC_TypeDef *Instance);

void LL_ADC_Samp_ChIRQHandler(ADC_TypeDef *Instance, ADC_ChETypeDef ch);
void LL_ADC_Samp_ChConvDoneCallback(ADC_TypeDef *Instance, ADC_ChETypeDef ch);

void LL_ADC_DMA_ChHalfCpltIRQHandler(ADC_TypeDef *Instance, ADC_ChETypeDef ch);
void LL_ADC_DMA_ChHalfCpltCallback(ADC_TypeDef *Instance, ADC_ChETypeDef ch);

void LL_ADC_DMA_ChCpltIRQHandler(ADC_TypeDef *Instance, ADC_ChETypeDef ch);
void LL_ADC_DMA_ChCpltCallback(ADC_TypeDef *Instance, ADC_ChETypeDef ch);


void LL_ADC_Samp_IRQHandler(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch0ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch1ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch2ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch3ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch4ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch5ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch6ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch7ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch8ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch9ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch10ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch11ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch12ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch13ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch14ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch15ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch16ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch17ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch18ConvDoneCallback(ADC_TypeDef *Instance);
void LL_ADC_Samp_Ch19ConvDoneCallback(ADC_TypeDef *Instance);

void LL_ADC_DMA_HalfCpltIRQHandler(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch0HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch1HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch2HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch3HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch4HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch5HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch6HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch7HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch8HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch9HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch10HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch11HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch12HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch13HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch14HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch15HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch16HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch17HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch18HalfCpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch19HalfCpltCallback(ADC_TypeDef *Instance);

void LL_ADC_DMA_CpltIRQHandler(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch0CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch1CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch2CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch3CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch4CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch5CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch6CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch7CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch8CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch9CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch10CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch11CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch12CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch13CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch14CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch15CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch16CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch17CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch18CpltCallback(ADC_TypeDef *Instance);
void LL_ADC_DMA_Ch19CpltCallback(ADC_TypeDef *Instance);
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

#endif /* _TAE32G58XX_LL_ADC_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

