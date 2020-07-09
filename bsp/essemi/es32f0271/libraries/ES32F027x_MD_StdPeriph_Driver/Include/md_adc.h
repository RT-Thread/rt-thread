/**
  ******************************************************************************
  * @file    md_ADC.h
  * @brief   ES32F0271 ADC Header File.
  *
  * @version V1.00.01
  * @date    04/12/2018
  * @author  Eastsoft AE Team
  * @note
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MD_ADC_H__
#define __MD_ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/
#include "es32f0271.h"
#include "reg_adc.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined ADC

/** @defgroup ADC ADC
  * @brief ADC micro driver
  * @{
  */

/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/
/* Public types ---------------------------------------------------------------*/
/* Public constants -----------------------------------------------------------*/
/* Public functions -----------------------------------------------------------*/

/** @defgroup MD_ADC_Public_Constants ADC Public Constants
  * @{
  */
  
/**
  * @brief   ADC Init structure.
  */  
typedef struct
{
  uint8_t VRLS;
  uint8_t SSx;
  uint32_t Sel;
  uint32_t Type;
  uint32_t Cntini;
  uint32_t Cnt;  
  uint8_t End;
  uint8_t Ckdiv;
} md_adc_inittypedef;  
/** @defgroup MD_ADC_CFG ADC_CFG Register
  * @{
  */
#define MD_ADC_CFG_TESTEN                (0xEDU)                           /** @brief data ADC Test Enable */

#define MD_ADC_CFG_MODE_NORMAL           (0x00000000U<<ADC_CFG_MODE_POS)   /** @brief data ADC Normal mode */
#define MD_ADC_CFG_MODE_DIFFERENTIAL     (0x00000001U<<ADC_CFG_MODE_POS)   /** @brief data ADC Differential mode */
/**
  * @} MD_ADC_CFG ADC_CFG Register
  */

/** @defgroup MD_ADC_SRATE ADC_SRATE Register
  * @{
  */
#define MD_ADC_SRATE_CLKDIV1             (0x00000000U<<ADC_SRATE_CKDIV_POSS)   /** @brief data ADC clock divide 1  */
#define MD_ADC_SRATE_CLKDIV2             (0x00000001U<<ADC_SRATE_CKDIV_POSS)   /** @brief data ADC clock divide 2  */
#define MD_ADC_SRATE_CLKDIV4             (0x00000002U<<ADC_SRATE_CKDIV_POSS)   /** @brief data ADC clock divide 4  */
#define MD_ADC_SRATE_CLKDIV6             (0x00000003U<<ADC_SRATE_CKDIV_POSS)   /** @brief data ADC clock divide 6  */
#define MD_ADC_SRATE_CLKDIV8             (0x00000004U<<ADC_SRATE_CKDIV_POSS)   /** @brief data ADC clock divide 8  */
#define MD_ADC_SRATE_CLKDIV10            (0x00000005U<<ADC_SRATE_CKDIV_POSS)   /** @brief data ADC clock divide 10 */
#define MD_ADC_SRATE_CLKDIV12            (0x00000006U<<ADC_SRATE_CKDIV_POSS)   /** @brief data ADC clock divide 12 */
#define MD_ADC_SRATE_CLKDIV14            (0x00000007U<<ADC_SRATE_CKDIV_POSS)   /** @brief data ADC clock divide 14 */
#define MD_ADC_SRATE_CLKDIV16            (0x00000008U<<ADC_SRATE_CKDIV_POSS)   /** @brief data ADC clock divide 16 */
#define MD_ADC_SRATE_CLKDIV18            (0x00000009U<<ADC_SRATE_CKDIV_POSS)   /** @brief data ADC clock divide 18 */
#define MD_ADC_SRATE_CLKDIV20            (0x0000000AU<<ADC_SRATE_CKDIV_POSS)   /** @brief data ADC clock divide 20 */
#define MD_ADC_SRATE_CLKDIV22            (0x0000000BU<<ADC_SRATE_CKDIV_POSS)   /** @brief data ADC clock divide 22 */
#define MD_ADC_SRATE_CLKDIV24            (0x0000000CU<<ADC_SRATE_CKDIV_POSS)   /** @brief data ADC clock divide 24 */
#define MD_ADC_SRATE_CLKDIV26            (0x0000000DU<<ADC_SRATE_CKDIV_POSS)   /** @brief data ADC clock divide 26 */
#define MD_ADC_SRATE_CLKDIV28            (0x0000000EU<<ADC_SRATE_CKDIV_POSS)   /** @brief data ADC clock divide 28 */
#define MD_ADC_SRATE_CLKDIV30            (0x0000000FU<<ADC_SRATE_CKDIV_POSS)   /** @brief data ADC clock divide 30 */

/**
  * @} MD_ADC_SRATE ADC_SRATE Register
  */

/** @defgroup MD_ADC_GAIN ADC_GAIN Definitation
  * @{
  */
#define MD_ADC_GAIN_CHPGA_X1              (0x00000000U)                      /** @brief data X1 gain */
#define MD_ADC_GAIN_CHPGA_X2              (0x00000001U)                      /** @brief data X2 gain */
#define MD_ADC_GAIN_CHPGA_X3              (0x00000002U)                      /** @brief data X3 gain */
#define MD_ADC_GAIN_CHPGA_X4              (0x00000003U)                      /** @brief data X4 gain */
#define MD_ADC_GAIN_CHPGA_X5              (0x00000004U)                      /** @brief data X5 gain */
#define MD_ADC_GAIN_CHPGA_X6              (0x00000005U)                      /** @brief data X6 gain */
#define MD_ADC_GAIN_CHPGA_X7              (0x00000006U)                      /** @brief data X7 gain */
#define MD_ADC_GAIN_CHPGA_X8              (0x00000007U)                      /** @brief data X8 gain */
/**
  * @} MD_ADC_GAIN ADC_GAIN Definitation
  */

/** @defgroup MD_ADC_SS_CON ADC_SS_CON_SEL Definitation
  * @{
  */
#define MD_ADC_SS_CON_SEL_SW              (0x00000000U<<ADC_SS0_CON_SEL_POSS)   /** @brief data SS Trigger Select SW       */
#define MD_ADC_SS_CON_SEL_BS16T1          (0x00000001U<<ADC_SS0_CON_SEL_POSS)   /** @brief data SS Trigger Select BS16T1   */
#define MD_ADC_SS_CON_SEL_ALWAYS          (0x00000002U<<ADC_SS0_CON_SEL_POSS)   /** @brief data SS Trigger Select ALWAYS   */
#define MD_ADC_SS_CON_SEL_GP32C4T1        (0x00000003U<<ADC_SS0_CON_SEL_POSS)   /** @brief data SS Trigger Select GP32C4T1 */
#define MD_ADC_SS_CON_SEL_GP16C4T1        (0x00000004U<<ADC_SS0_CON_SEL_POSS)   /** @brief data SS Trigger Select GP16C4T1 */
#define MD_ADC_SS_CON_SEL_GP16C4T2        (0x00000005U<<ADC_SS0_CON_SEL_POSS)   /** @brief data SS Trigger Select GP16C4T2 */
#define MD_ADC_SS_CON_SEL_GP16C4T3        (0x00000006U<<ADC_SS0_CON_SEL_POSS)   /** @brief data SS Trigger Select GP16C4T3 */
#define MD_ADC_SS_CON_SEL_GP16C2T1        (0x00000007U<<ADC_SS0_CON_SEL_POSS)   /** @brief data SS Trigger Select GP16C2T1 */
#define MD_ADC_SS_CON_SEL_GP16C2T2        (0x00000008U<<ADC_SS0_CON_SEL_POSS)   /** @brief data SS Trigger Select GP16C2T2 */
#define MD_ADC_SS_CON_SEL_GP16C2T3        (0x00000009U<<ADC_SS0_CON_SEL_POSS)   /** @brief data SS Trigger Select GP16C2T3 */
#define MD_ADC_SS_CON_SEL_GP16C2T4        (0x0000000AU<<ADC_SS0_CON_SEL_POSS)   /** @brief data SS Trigger Select GP16C2T4 */
#define MD_ADC_SS_CON_SEL_AD16C4T1        (0x0000000BU<<ADC_SS0_CON_SEL_POSS)   /** @brief data SS Trigger Select AD16C4T1 */
#define MD_ADC_SS_CON_SEL_GPIO            (0x0000000CU<<ADC_SS0_CON_SEL_POSS)   /** @brief data SS Trigger Select GPIO     */
#define MD_ADC_SS_CON_SEL_RTC             (0x0000000DU<<ADC_SS0_CON_SEL_POSS)   /** @brief data SS Trigger Select RTC      */
#define MD_ADC_SS_CON_SEL_CMP0            (0x0000000EU<<ADC_SS0_CON_SEL_POSS)   /** @brief data SS Trigger Select CMP0     */
#define MD_ADC_SS_CON_SEL_CMP1            (0x0000000FU<<ADC_SS0_CON_SEL_POSS)   /** @brief data SS Trigger Select CMP1     */
#define MD_ADC_SS_CON_SEL_CMP2            (0x00000010U<<ADC_SS0_CON_SEL_POSS)   /** @brief data SS Trigger Select CMP2     */
#define MD_ADC_SS_CON_SEL_CMP3            (0x00000011U<<ADC_SS0_CON_SEL_POSS)   /** @brief data SS Trigger Select CMP3     */

#define MD_ADC_SS_CON_TYPE_EDGE           (0<<ADC_SS0_CON_TYP_POS)             /** @brief data ADC Sample Sequencer (SS) Trigger Type Edge */
#define MD_ADC_SS_CON_TYPE_LEVEL          (1<<ADC_SS0_CON_TYP_POS)             /** @brief data ADC Sample Sequencer (SS) Trigger Type LEVEL */

#define MD_ADC_SS_CONPRI_HIGHEST         (0<<ADC_SS0_CON_PRI_POSS)            /** @brief data ADC SS priority highest */
#define MD_ADC_SS_CON_PRI_SECOND         (1<<ADC_SS0_CON_PRI_POSS)            /** @brief data ADC SS priority second  */
#define MD_ADC_SS_CON_PRI_THIRD          (2<<ADC_SS0_CON_PRI_POSS)            /** @brief data ADC SS priority third   */
#define MD_ADC_SS_CON_PRI_LOWEST         (3<<ADC_SS0_CON_PRI_POSS)            /** @brief data ADC SS priority lowest  */

#define MD_ADC_SS_CCON_ONE               (1<<ADC_SS0_CON_ONE_POS)             /** @brief data ADC SS One Shot Trigger Mode */
/**
  * @} MD_ADC_SS_CON ADC_SS_CON_SEL Definitation
  */

/** @defgroup MD_ADIN ADIN Pin Defination
  * @{
  */
#define MD_ADC_SS_MUX_ADIN15                    (0x0000000FU)                       /** @brief data ADC ADIN PIN15 Defination */
#define MD_ADC_SS_MUX_ADIN14                    (0x0000000EU)                       /** @brief data ADC ADIN PIN14 Defination */
#define MD_ADC_SS_MUX_ADIN13                    (0x0000000DU)                       /** @brief data ADC ADIN PIN13 Defination */
#define MD_ADC_SS_MUX_ADIN12                    (0x0000000CU)                       /** @brief data ADC ADIN PIN12 Defination */
#define MD_ADC_SS_MUX_ADIN11                    (0x0000000BU)                       /** @brief data ADC ADIN PIN11 Defination */
#define MD_ADC_SS_MUX_ADIN10                    (0x0000000AU)                       /** @brief data ADC ADIN PIN10 Defination */
#define MD_ADC_SS_MUX_ADIN9                     (0x00000009U)                       /** @brief data ADC ADIN PIN9 Defination  */
#define MD_ADC_SS_MUX_ADIN8                     (0x00000008U)                       /** @brief data ADC ADIN PIN8 Defination  */
#define MD_ADC_SS_MUX_ADIN7                     (0x00000007U)                       /** @brief data ADC ADIN PIN7 Defination  */
#define MD_ADC_SS_MUX_ADIN6                     (0x00000006U)                       /** @brief data ADC ADIN PIN6 Defination  */
#define MD_ADC_SS_MUX_ADIN5                     (0x00000005U)                       /** @brief data ADC ADIN PIN5 Defination  */
#define MD_ADC_SS_MUX_ADIN4                     (0x00000004U)                       /** @brief data ADC ADIN PIN5 Defination  */
#define MD_ADC_SS_MUX_ADIN3                     (0x00000003U)                       /** @brief data ADC ADIN PIN3 Defination  */
#define MD_ADC_SS_MUX_ADIN2                     (0x00000002U)                       /** @brief data ADC ADIN PIN2 Defination  */
#define MD_ADC_SS_MUX_ADIN1                     (0x00000001U)                       /** @brief data ADC ADIN PIN1 Defination  */
#define MD_ADC_SS_MUX_ADIN0                     (0x00000000U)                       /** @brief data ADC ADIN PIN0 Defination  */
/**
  * @} MD_ADIN ADIN Pin Defination
  */

/**
  * @} MD_ADC_Public_Constants
  */

/* Public macro ---------------------------------------------------------------*/
/** @defgroup MD_ADC_Public_Macros ADC Public Macros
  * @{
  */

/** @defgroup MD_ADC_PM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Set ADC Macro Test Mode.
  * @note   Enable Macro Test Mode.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_set_cfg_testen(ADC_TypeDef *ADCx)
{
  MODIFY_REG(ADCx->CFG, ADC_CFG_TESTEN_MSK, MD_ADC_CFG_TESTEN<<ADC_CFG_TESTEN_POSS);
}

/**
  * @brief  Set ADC Mode.
  * @param  ADCx ADC Instance
  * @param  Mode
  *         @arg @ref MD_ADC_CFG_MODE_NORMAL
  *         @arg @ref MD_ADC_CFG_MODE_DIFFERENTIAL
  * @retval None
  */
__STATIC_INLINE void md_adc_set_cfg_mode(ADC_TypeDef *ADCx, uint32_t Mode)
{
  MODIFY_REG(ADCx->CFG, ADC_CFG_MODE_MSK, Mode<<ADC_CFG_MODE_POS);
}

/**
  * @brief  Read ADC Mode.
  * @param  ADCx ADC Instance
  * @retval None
  *         @arg @ref MD_ADC_CFG_MODE_NORMAL
  *         @arg @ref MD_ADC_CFG_MODE_DIFFERENTIAL
  */
__STATIC_INLINE uint32_t md_adc_get_cfg_mode(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->CFG, ADC_CFG_MODE_MSK))>>ADC_CFG_MODE_POS);
}

/**
  * @brief  Set ADC Wait Counter Value.
  * @note   Set the wait cycle between each ADC sample.
  * @param  ADCx ADC Instance
  * @param  CNT Value between Min_Value=0x00 and Max_Value=0xFF
  * @retval None
  */
__STATIC_INLINE void md_adc_set_srate_cnt(ADC_TypeDef *ADCx, uint32_t cnt)
{
  MODIFY_REG(ADCx->SRATE, ADC_SRATE_CNT_MSK, cnt<<ADC_SRATE_CNT_POSS);
}

/**
  * @brief  Get ADC Wait Counter Value.
  * @note   Get the wait cycle between each ADC sample.
  * @param  ADCx ADC Instance
  * @retval CNT
  *         @arg @ref CNT Value between Min_Value=0x00 and Max_Value=0xFF
  */
__STATIC_INLINE uint32_t md_adc_get_srate_cnt(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->SRATE, ADC_SRATE_CNT_MSK))>>ADC_SRATE_CNT_POSS);
}

/**
  * @brief  Set ADC Wait Counter Initial Value.
  * @note   Set the Initial Value of ADC wait counter.
  * @param  ADCx ADC Instance
  * @param  CNTINI
  *         @arg @ref CNTINI Value between Min_Value=0x00 and Max_Value=0xFF
  * @retval None
  */
__STATIC_INLINE void md_adc_set_srate_cntini(ADC_TypeDef *adcx, uint32_t cntini)
{
  MODIFY_REG(adcx->SRATE, ADC_SRATE_CNTINI_MSK, cntini<<ADC_SRATE_CNTINI_POSS);
}

/**
  * @brief  Get ADC Wait Counter Initial Value.
  * @note   Get the Initial Value of ADC wait counter.
  * @param  ADCx ADC Instance
  * @retval CNTINI 
  *         @arg @ref CNTINI Value between Min_Value=0x00 and Max_Value=0xFF
  */
__STATIC_INLINE uint32_t md_adc_get_srate_cntini(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->SRATE, ADC_SRATE_CNTINI_MSK))>>ADC_SRATE_CNTINI_POSS);
}

/**
  * @brief  Set ADC Converter Clock Division.
  * @note   Get the division ratio of ADC converter clock. 0 to 15 division ratio 
  *         where 0 indicates no division is implemented. To modify CLKDIV, user 
  *         should first set CLKEN to 0 and re-enable this bit after modification 
  *         on CLKDIV.
  * @param  ADCx ADC Instance
  * @param  ADC Converter Clock Division
  *         @arg @ref MD_ADC_SRATE_CKDIV1
  *         @arg @ref MD_ADC_SRATE_CKDIV2
  *         @arg @ref MD_ADC_SRATE_CKDIV4
  *         @arg @ref MD_ADC_SRATE_CKDIV6
  *         @arg @ref MD_ADC_SRATE_CKDIV8
  *         @arg @ref MD_ADC_SRATE_CKDIV10
  *         @arg @ref MD_ADC_SRATE_CKDIV12
  *         @arg @ref MD_ADC_SRATE_CKDIV14
  *         @arg @ref MD_ADC_SRATE_CKDIV16
  *         @arg @ref MD_ADC_SRATE_CKDIV18
  *         @arg @ref MD_ADC_SRATE_CKDIV20
  *         @arg @ref MD_ADC_SRATE_CKDIV22
  *         @arg @ref MD_ADC_SRATE_CKDIV24
  *         @arg @ref MD_ADC_SRATE_CKDIV26
  *         @arg @ref MD_ADC_SRATE_CKDIV28
  *         @arg @ref MD_ADC_SRATE_CKDIV30
  * @retval None
  */
__STATIC_INLINE void md_adc_set_srate_clkdiv(ADC_TypeDef *ADCx, uint32_t clkdiv)
{
  MODIFY_REG(ADCx->SRATE, ADC_SRATE_CKDIV_MSK, clkdiv<<ADC_SRATE_CKDIV_POSS);
}


/**
  * @brief  Get ADC Converter Clock Division.
  * @note   Get the division ratio of ADC converter clock. 0 to 15 division ratio 
  *         where 0 indicates no division is implemented. 
  * @param  ADCx ADC Instance
  * @retval ADC Converter Clock Division
  *         @arg @ref MD_ADC_SRATE_CKDIV1
  *         @arg @ref MD_ADC_SRATE_CKDIV2
  *         @arg @ref MD_ADC_SRATE_CKDIV4
  *         @arg @ref MD_ADC_SRATE_CKDIV6
  *         @arg @ref MD_ADC_SRATE_CKDIV8
  *         @arg @ref MD_ADC_SRATE_CKDIV10
  *         @arg @ref MD_ADC_SRATE_CKDIV12
  *         @arg @ref MD_ADC_SRATE_CKDIV14
  *         @arg @ref MD_ADC_SRATE_CKDIV16
  *         @arg @ref MD_ADC_SRATE_CKDIV18
  *         @arg @ref MD_ADC_SRATE_CKDIV20
  *         @arg @ref MD_ADC_SRATE_CKDIV22
  *         @arg @ref MD_ADC_SRATE_CKDIV24
  *         @arg @ref MD_ADC_SRATE_CKDIV26
  *         @arg @ref MD_ADC_SRATE_CKDIV28
  *         @arg @ref MD_ADC_SRATE_CKDIV30
  */
__STATIC_INLINE uint32_t md_adc_get_srate_clkdiv(ADC_TypeDef *ADCx)
{
  return ((READ_BIT(ADCx->SRATE, ADC_SRATE_CKDIV_MSK))>>ADC_SRATE_CKDIV_POSS);
}

/**
  * @brief  ADC clock enable.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_srate_clken(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SRATE, ADC_SRATE_CKEN_MSK);
}

/**
  * @brief  ADC clock sisable.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_srate_clken(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SRATE, ADC_SRATE_CKEN_MSK);
}

/**
  * @brief  Check if ADC clock is enabled.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_srate_clken(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SRATE, ADC_SRATE_CKEN_MSK) == (ADC_SRATE_CKEN_MSK));
}

/**
  * @brief  Channel 15 Invert Control enable.
  * @note   This is used to invert the data of channel 15.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_srate_ch15inv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SRATE, ADC_CHINV_CH15INV_MSK);
}

/**
  * @brief  Channel 15 Invert Control disable.
  * @note   This is used to invert the data of channel 15.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_srate_ch15inv(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SRATE, ADC_CHINV_CH15INV_MSK);
}

/**
  * @brief  Check if Channel 15 Invert Control is enabled.
  * @note   This is used to invert the data of channel 15.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_srate_ch15inv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SRATE, ADC_CHINV_CH15INV_MSK) == (ADC_CHINV_CH15INV_MSK));
}

/**
  * @brief  Channel 14 Invert Control enable.
  * @note   This is used to invert the data of channel 14.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_srate_ch14inv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SRATE, ADC_CHINV_CH14INV_MSK);
}

/**
  * @brief  Channel 14 Invert Control disable.
  * @note   This is used to invert the data of channel 14.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_srate_ch14inv(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SRATE, ADC_CHINV_CH14INV_MSK);
}

/**
  * @brief  Check if Channel 14 Invert Control is enabled.
  * @note   This is used to invert the data of channel 14.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_srate_ch14inv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SRATE, ADC_CHINV_CH14INV_MSK) == (ADC_CHINV_CH14INV_MSK));
}

/**
  * @brief  Channel 13 Invert Control enable.
  * @note   This is used to invert the data of channel 13.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_srate_ch13inv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SRATE, ADC_CHINV_CH13INV_MSK);
}

/**
  * @brief  Channel 13 Invert Control disable.
  * @note   This is used to invert the data of channel 13.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_srate_ch13inv(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SRATE, ADC_CHINV_CH13INV_MSK);
}

/**
  * @brief  Check if Channel 13 Invert Control is enabled.
  * @note   This is used to invert the data of channel 13.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_srate_ch13inv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SRATE, ADC_CHINV_CH13INV_MSK) == (ADC_CHINV_CH13INV_MSK));
}

/**
  * @brief  Channel 12 Invert Control enable.
  * @note   This is used to invert the data of channel 12.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_srate_ch12inv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SRATE, ADC_CHINV_CH12INV_MSK);
}

/**
  * @brief  Channel 12 Invert Control disable.
  * @note   This is used to invert the data of channel 12.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_srate_ch12inv(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SRATE, ADC_CHINV_CH12INV_MSK);
}

/**
  * @brief  Check if Channel 12 Invert Control is enabled.
  * @note   This is used to invert the data of channel 12.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_srate_ch12inv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SRATE, ADC_CHINV_CH12INV_MSK) == (ADC_CHINV_CH12INV_MSK));
}

/**
  * @brief  Channel 11 Invert Control enable.
  * @note   This is used to invert the data of channel 11.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_srate_ch11inv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SRATE, ADC_CHINV_CH15INV_MSK);
}

/**
  * @brief  Channel 11 Invert Control disable.
  * @note   This is used to invert the data of channel 11.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_srate_ch11inv(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SRATE, ADC_CHINV_CH11INV_MSK);
}

/**
  * @brief  Check if Channel 11 Invert Control is enabled.
  * @note   This is used to invert the data of channel 11.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_srate_ch11inv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SRATE, ADC_CHINV_CH11INV_MSK) == (ADC_CHINV_CH11INV_MSK));
}

/**
  * @brief  Channel 10 Invert Control enable.
  * @note   This is used to invert the data of channel 10.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_srate_ch10inv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SRATE, ADC_CHINV_CH10INV_MSK);
}

/**
  * @brief  Channel 10 Invert Control disable.
  * @note   This is used to invert the data of channel 10.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_srate_ch10inv(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SRATE, ADC_CHINV_CH10INV_MSK);
}

/**
  * @brief  Check if Channel 10 Invert Control is enabled.
  * @note   This is used to invert the data of channel 10.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_srate_ch10inv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SRATE, ADC_CHINV_CH10INV_MSK) == (ADC_CHINV_CH10INV_MSK));
}

/**
  * @brief  Channel 9 Invert Control enable.
  * @note   This is used to invert the data of channel 9.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_srate_ch9inv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SRATE, ADC_CHINV_CH9INV_MSK);
}

/**
  * @brief  Channel 9 Invert Control disable.
  * @note   This is used to invert the data of channel 9.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_srate_ch9inv(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SRATE, ADC_CHINV_CH9INV_MSK);
}

/**
  * @brief  Check if Channel 9 Invert Control is enabled.
  * @note   This is used to invert the data of channel 9.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_srate_ch9inv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SRATE, ADC_CHINV_CH9INV_MSK) == (ADC_CHINV_CH9INV_MSK));
}

/**
  * @brief  Channel 8 Invert Control enable.
  * @note   This is used to invert the data of channel 8.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_srate_ch8inv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SRATE, ADC_CHINV_CH8INV_MSK);
}

/**
  * @brief  Channel 8 Invert Control disable.
  * @note   This is used to invert the data of channel 8.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_srate_ch8inv(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SRATE, ADC_CHINV_CH8INV_MSK);
}

/**
  * @brief  Check if Channel 8 Invert Control is enabled.
  * @note   This is used to invert the data of channel 8.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_srate_ch8inv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SRATE, ADC_CHINV_CH8INV_MSK) == (ADC_CHINV_CH8INV_MSK));
}

/**
  * @brief  Channel 7 Invert Control enable.
  * @note   This is used to invert the data of channel 7.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_srate_ch7inv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SRATE, ADC_CHINV_CH7INV_MSK);
}

/**
  * @brief  Channel 7 Invert Control disable.
  * @note   Disable invert data channel 7.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_srate_ch7inv(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SRATE, ADC_CHINV_CH7INV_MSK);
}

/**
  * @brief  Check if Channel 7 Invert Control is enabled.
  * @note   Check invert state of data channel 7.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_srate_ch7inv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SRATE, ADC_CHINV_CH7INV_MSK) == (ADC_CHINV_CH7INV_MSK));
}

/**
  * @brief  Channel 6 Invert Control enable.
  * @note   This is used to invert the data of channel 6.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_srate_ch6inv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SRATE, ADC_CHINV_CH6INV_MSK);
}

/**
  * @brief  Channel 6 Invert Control disable.
  * @note   Disable invert data channel 6.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_srate_ch6inv(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SRATE, ADC_CHINV_CH6INV_MSK);
}

/**
  * @brief  Check if Channel 6 Invert Control is enabled.
  * @note   Check invert state of data channel 6.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_srate_ch6inv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SRATE, ADC_CHINV_CH6INV_MSK) == (ADC_CHINV_CH6INV_MSK));
}

/**
  * @brief  Channel 5 Invert Control enable.
  * @note   This is used to invert the data of channel 5.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_srate_ch5inv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SRATE, ADC_CHINV_CH5INV_MSK);
}

/**
  * @brief  Channel 5 Invert Control disable.
  * @note   Disable invert data channel 5.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_srate_ch5inv(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SRATE, ADC_CHINV_CH5INV_MSK);
}

/**
  * @brief  Check if Channel 5 Invert Control is enabled.
  * @note   Check invert state of data channel 5.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_srate_ch5inv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SRATE, ADC_CHINV_CH5INV_MSK) == (ADC_CHINV_CH5INV_MSK));
}

/**
  * @brief  Channel 4 Invert Control enable.
  * @note   This is used to invert the data of channel 4.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_srate_ch4inv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SRATE, ADC_CHINV_CH4INV_MSK);
}

/**
  * @brief  Channel 4 Invert Control disable.
  * @note   Disable invert data channel 4.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_srate_ch4inv(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SRATE, ADC_CHINV_CH4INV_MSK);
}

/**
  * @brief  Check if Channel 4 Invert Control is enabled.
  * @note   Check invert state of data channel 4.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_srate_ch4inv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SRATE, ADC_CHINV_CH4INV_MSK) == (ADC_CHINV_CH4INV_MSK));
}

/**
  * @brief  Channel 3 Invert Control enable.
  * @note   This is used to invert the data of channel 3.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_srate_ch3inv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SRATE, ADC_CHINV_CH3INV_MSK);
}

/**
  * @brief  Channel 3 Invert Control disable.
  * @note   Disable invert data channel 3.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_srate_ch3inv(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SRATE, ADC_CHINV_CH3INV_MSK);
}

/**
  * @brief  Check if Channel 3 Invert Control is enabled.
  * @note   Check invert state of data of channel 3.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_srate_ch3inv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SRATE, ADC_CHINV_CH3INV_MSK) == (ADC_CHINV_CH3INV_MSK));
}

/**
  * @brief  Channel 2 Invert Control enable.
  * @note   This is used to invert the data of channel 2.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_srate_ch2inv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SRATE, ADC_CHINV_CH2INV_MSK);
}

/**
  * @brief  Channel 2 Invert Control disable.
  * @note   Disable invert data channel 2.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_srate_ch2inv(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SRATE, ADC_CHINV_CH2INV_MSK);
}

/**
  * @brief  Check if Channel 2 Invert Control is enabled.
  * @note   Check invert state of data of channel 2.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_srate_ch2inv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SRATE, ADC_CHINV_CH2INV_MSK) == (ADC_CHINV_CH2INV_MSK));
}

/**
  * @brief  Channel 1 Invert Control enable.
  * @note   This is used to invert the data of channel 1.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_srate_ch1inv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SRATE, ADC_CHINV_CH1INV_MSK);
}

/**
  * @brief  Channel 1 Invert Control disable.
  * @note   Disable invert data channel 1.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_srate_ch1inv(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SRATE, ADC_CHINV_CH1INV_MSK);
}

/**
  * @brief  Check if Channel 1 Invert Control is enabled.
  * @note   Check invert of data of channel 1.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_srate_ch1inv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SRATE, ADC_CHINV_CH1INV_MSK) == (ADC_CHINV_CH1INV_MSK));
}

/**
  * @brief  Channel 0 Invert Control enable.
  * @note   This is used to invert the data of channel 0.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_srate_ch0inv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SRATE, ADC_CHINV_CH0INV_MSK);
}

/**
  * @brief  Channel 0 Invert Control disable.
  * @note   Disable invert data channel 0.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_srate_ch0inv(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SRATE, ADC_CHINV_CH0INV_MSK);
}

/**
  * @brief  Check if Channel 0 Invert Control is enabled.
  * @note   Check invert state of data of channel 0.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_srate_ch0inv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SRATE, ADC_CHINV_CH0INV_MSK) == (ADC_CHINV_CH0INV_MSK));
}

/**
  * @brief  Set ADC SRATE register.
  * @note   This is used to set SRATE register.
  * @param  ADCx ADC Instance
  * @param  SRATE
  * @retval NONE.
  */
__STATIC_INLINE void md_adc_set_srate(ADC_TypeDef *adcx, uint32_t srate)
{
  WRITE_REG(adcx->SRATE, srate);
}

/**
  * @brief  Get ADC SRATE register.
  * @note   This is used to read SRATE register.
  * @param  ADCx ADC Instance
  * @param  SRATE
  * @retval SRATE Register Value.
  */
__STATIC_INLINE uint32_t md_adc_get_srate(ADC_TypeDef *adcx)
{
  return READ_REG(adcx->SRATE);
}

/**
  * @brief  Set ADC Channel 7 PGA Gain.
  * @note   This is used to select channel 7 PGA gain.
  * @param  ADCx ADC Instance
  * @param  ADC PGA Gain
  * @param  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gainl_ch7pga(ADC_TypeDef *ADCx, uint32_t Gain)
{
  MODIFY_REG(ADCx->GAINL, ADC_GAINL_CH7PGA_MSK, Gain<<ADC_GAINL_CH7PGA_POSS);
}

/**
  * @brief  Get ADC Channel 7 PGA Gain.
  * @note   This is used to read channel 7 PGA gain.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  */
__STATIC_INLINE uint32_t md_adc_get_gainl_ch7pga(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->GAINL, ADC_GAINL_CH7PGA_MSK)>>ADC_GAINL_CH7PGA_POSS);
}

/**
  * @brief  Set ADC Channel 6 PGA Gain.
  * @note   This is used to select channel 6 PGA gain.
  * @param  ADCx ADC Instance
  * @param  ADC PGA Gain
  * @param  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gainl_ch6pga(ADC_TypeDef *ADCx, uint32_t Gain)
{
  MODIFY_REG(ADCx->GAINL, ADC_GAINL_CH6PGA_MSK, Gain<<ADC_GAINL_CH6PGA_POSS);
}

/**
  * @brief  Get ADC Channel 6 PGA Gain.
  * @note   This is used to read channel 6 PGA gain.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  */
__STATIC_INLINE uint32_t md_adc_get_gainl_ch6pga(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->GAINL, ADC_GAINL_CH6PGA_MSK)>>ADC_GAINL_CH6PGA_POSS);
}

/**
  * @brief  Set ADC Channel 5 PGA Gain.
  * @note   This is used to select channel 5 PGA gain.
  * @param  ADCx ADC Instance
  * @param  ADC PGA Gain
  * @param  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gainl_ch5pga(ADC_TypeDef *ADCx, uint32_t Gain)
{
  MODIFY_REG(ADCx->GAINL, ADC_GAINL_CH5PGA_MSK, Gain<<ADC_GAINL_CH5PGA_POSS);
}

/**
  * @brief  Get ADC Channel 5 PGA Gain.
  * @note   This is used to read channel 5 PGA gain.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  */
__STATIC_INLINE uint32_t md_adc_get_gainl_ch5pga(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->GAINL, ADC_GAINL_CH5PGA_MSK)>>ADC_GAINL_CH5PGA_POSS);
}

/**
  * @brief  Set ADC Channel 4 PGA Gain.
  * @note   This is used to select channel 4 PGA gain.
  * @param  ADCx ADC Instance
  * @param  ADC PGA Gain
  * @param  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gainl_ch4pga(ADC_TypeDef *ADCx, uint32_t Gain)
{
  MODIFY_REG(ADCx->GAINL, ADC_GAINL_CH4PGA_MSK, Gain<<ADC_GAINL_CH4PGA_POSS);
}

/**
  * @brief  Get ADC Channel 4 PGA Gain.
  * @note   This is used to read channel 4 PGA gain.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  */
__STATIC_INLINE uint32_t md_adc_get_gainl_ch4pga(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->GAINL, ADC_GAINL_CH4PGA_MSK)>>ADC_GAINL_CH4PGA_POSS);
}

/**
  * @brief  Set ADC Channel 3 PGA Gain.
  * @note   This is used to select channel 3 PGA gain.
  * @param  ADCx ADC Instance
  * @param  ADC PGA Gain
  * @param  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gainl_ch3pga(ADC_TypeDef *ADCx, uint32_t Gain)
{
  MODIFY_REG(ADCx->GAINL, ADC_GAINL_CH3PGA_MSK, Gain<<ADC_GAINL_CH3PGA_POSS);
}

/**
  * @brief  Get ADC Channel 3 PGA Gain.
  * @note   This is used to read channel 3 PGA gain.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  */
__STATIC_INLINE uint32_t md_adc_get_gainl_ch3pga(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->GAINL, ADC_GAINL_CH3PGA_MSK)>>ADC_GAINL_CH3PGA_POSS);
}

/**
  * @brief  Set ADC Channel 2 PGA Gain.
  * @note   This is used to select channel 2 PGA gain.
  * @param  ADCx ADC Instance
  * @param  ADC PGA Gain
  * @param  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gainl_ch2pga(ADC_TypeDef *ADCx, uint32_t Gain)
{
  MODIFY_REG(ADCx->GAINL, ADC_GAINL_CH2PGA_MSK, Gain<<ADC_GAINL_CH2PGA_POSS);
}

/**
  * @brief  Get ADC Channel 2 PGA Gain.
  * @note   This is used to read channel 2 PGA gain.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  */
__STATIC_INLINE uint32_t md_adc_get_gainl_ch2pga(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->GAINL, ADC_GAINL_CH2PGA_MSK)>>ADC_GAINL_CH2PGA_POSS);
}

/**
  * @brief  Set ADC Channel 1 PGA Gain.
  * @note   This is used to select channel 1 PGA gain.
  * @param  ADCx ADC Instance
  * @param  ADC PGA Gain
  * @param  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gainl_ch1pga(ADC_TypeDef *ADCx, uint32_t Gain)
{
  MODIFY_REG(ADCx->GAINL, ADC_GAINL_CH1PGA_MSK, Gain<<ADC_GAINL_CH1PGA_POSS);
}

/**
  * @brief  Get ADC Channel 1 PGA Gain.
  * @note   This is used to read channel 1 PGA gain.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  */
__STATIC_INLINE uint32_t md_adc_get_gainl_ch1pga(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->GAINL, ADC_GAINL_CH1PGA_MSK)>>ADC_GAINL_CH1PGA_POSS);
}

/**
  * @brief  Set ADC Channel 0 PGA Gain.
  * @note   This is used to select channel 0 PGA gain.
  * @param  ADCx ADC Instance
  * @param  ADC PGA Gain
  * @param  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gainl_ch0pga(ADC_TypeDef *ADCx, uint32_t Gain)
{
  MODIFY_REG(ADCx->GAINL, ADC_GAINL_CH0PGA_MSK, Gain<<ADC_GAINL_CH0PGA_POSS);
}

/**
  * @brief  Get ADC Channel 0 PGA Gain.
  * @note   This is used to read channel 0 PGA gain.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  */
__STATIC_INLINE uint32_t md_adc_get_gainl_ch0pga(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->GAINL, ADC_GAINL_CH0PGA_MSK)>>ADC_GAINL_CH0PGA_POSS);
}

/**
  * @brief  Set ADC Channels 0~7 PGA Gain.
  * @note   This is used to select channels 0-7 PGA gain.
  * @param  ADCx ADC Instance
  * @param  GainL Register Values for CH0~CH7.
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gainl(ADC_TypeDef *ADCx, uint32_t GainL)
{
  WRITE_REG(ADCx->GAINL, GainL);
}

/**
  * @brief  Get ADC Channels 0~7 PGA Gain.
  * @note   This is used to read channels 0-7 PGA gain.
  * @param  ADCx ADC Instance
  * @retval GainL Register Values for CH0~CH7.
  */
__STATIC_INLINE uint32_t md_adc_get_gainl(ADC_TypeDef *ADCx)
{
  return READ_REG(ADCx->GAINL);
}

/**
  * @brief  Set ADC Channel 15 PGA Gain.
  * @note   This is used to select channel 15 PGA gain.
  * @param  ADCx ADC Instance
  * @param  ADC PGA Gain
  * @param  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gainh_ch15pga(ADC_TypeDef *ADCx, uint32_t Gain)
{
  MODIFY_REG(ADCx->GAINH, ADC_GAINH_CH15PGA_MSK, Gain<<ADC_GAINH_CH15PGA_POSS);
}

/**
  * @brief  Get ADC Channel 15 PGA Gain.
  * @note   This is used to read channel 15 PGA gain.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  */
__STATIC_INLINE uint32_t md_adc_get_gainh_ch15pga(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->GAINH, ADC_GAINH_CH15PGA_MSK)>>ADC_GAINH_CH15PGA_POSS);
}

/**
  * @brief  Set ADC Channel 14 PGA Gain.
  * @note   This is used to select channel 14 PGA gain.
  * @param  ADCx ADC Instance
  * @param  ADC PGA Gain
  * @param  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gainh_ch14pga(ADC_TypeDef *ADCx, uint32_t Gain)
{
  MODIFY_REG(ADCx->GAINH, ADC_GAINH_CH14PGA_MSK, Gain<<ADC_GAINH_CH14PGA_POSS);
}

/**
  * @brief  Get ADC Channel 14 PGA Gain.
  * @note   This is used to read channel 14 PGA gain.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  */
__STATIC_INLINE uint32_t md_adc_get_gainh_ch14pga(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->GAINH, ADC_GAINH_CH14PGA_MSK)>>ADC_GAINH_CH14PGA_POSS);
}

/**
  * @brief  Set ADC Channel 13 PGA Gain.
  * @note   This is used to select channel 13 PGA gain.
  * @param  ADCx ADC Instance
  * @param  ADC PGA Gain
  * @param  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gainh_ch13pga(ADC_TypeDef *ADCx, uint32_t Gain)
{
  MODIFY_REG(ADCx->GAINH, ADC_GAINH_CH13PGA_MSK, Gain<<ADC_GAINH_CH13PGA_POSS);
}

/**
  * @brief  Get ADC Channel 13 PGA Gain.
  * @note   This is used to read channel 13 PGA gain.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  */
__STATIC_INLINE uint32_t md_adc_get_gainh_ch13pga(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->GAINH, ADC_GAINH_CH13PGA_MSK)>>ADC_GAINH_CH13PGA_POSS);
}

/**
  * @brief  Set ADC Channel 12 PGA Gain.
  * @note   This is used to select channel 12 PGA gain.
  * @param  ADCx ADC Instance
  * @param  ADC PGA Gain
  * @param  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gainh_ch12pga(ADC_TypeDef *ADCx, uint32_t Gain)
{
  MODIFY_REG(ADCx->GAINH, ADC_GAINH_CH12PGA_MSK, Gain<<ADC_GAINH_CH12PGA_POSS);
}

/**
  * @brief  Get ADC Channel 12 PGA Gain.
  * @note   This is used to read channel 12 PGA gain.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  */
__STATIC_INLINE uint32_t md_adc_get_gainh_ch12pga(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->GAINH, ADC_GAINH_CH12PGA_MSK)>>ADC_GAINH_CH12PGA_POSS);
}

/**
  * @brief  Set ADC Channel 11 PGA Gain.
  * @note   This is used to select channel 11 PGA gain.
  * @param  ADCx ADC Instance
  * @param  ADC PGA Gain
  * @param  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gainh_ch11pga(ADC_TypeDef *ADCx, uint32_t Gain)
{
  MODIFY_REG(ADCx->GAINH, ADC_GAINH_CH11PGA_MSK, Gain<<ADC_GAINH_CH11PGA_POSS);
}

/**
  * @brief  Get ADC Channel 11 PGA Gain.
  * @note   This is used to read channel 11 PGA gain.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  */
__STATIC_INLINE uint32_t md_adc_get_gainh_ch3pga(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->GAINH, ADC_GAINH_CH11PGA_MSK)>>ADC_GAINH_CH11PGA_POSS);
}

/**
  * @brief  Set ADC Channel 10 PGA Gain.
  * @note   This is used to select channel 10 PGA gain.
  * @param  ADCx ADC Instance
  * @param  ADC PGA Gain
  * @param  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gainh_ch10pga(ADC_TypeDef *ADCx, uint32_t Gain)
{
  MODIFY_REG(ADCx->GAINH, ADC_GAINH_CH10PGA_MSK, Gain<<ADC_GAINH_CH10PGA_POSS);
}

/**
  * @brief  Get ADC Channel 10 PGA Gain.
  * @note   This is used to read channel 10 PGA gain.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  */
__STATIC_INLINE uint32_t md_adc_get_gainh_ch10pga(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->GAINH, ADC_GAINH_CH10PGA_MSK)>>ADC_GAINH_CH10PGA_POSS);
}

/**
  * @brief  Set ADC Channel 9 PGA Gain.
  * @note   This is used to select channel 9 PGA gain.
  * @param  ADCx ADC Instance
  * @param  ADC PGA Gain
  * @param  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gainh_ch9pga(ADC_TypeDef *ADCx, uint32_t Gain)
{
  MODIFY_REG(ADCx->GAINH, ADC_GAINH_CH9PGA_MSK, Gain<<ADC_GAINH_CH9PGA_POSS);
}

/**
  * @brief  Get ADC Channel 9 PGA Gain.
  * @note   This is used to read channel 9 PGA gain.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  */
__STATIC_INLINE uint32_t md_adc_get_gainh_ch9pga(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->GAINH, ADC_GAINH_CH9PGA_MSK)>>ADC_GAINH_CH9PGA_POSS);
}

/**
  * @brief  Set ADC Channel 8 PGA Gain.
  * @note   This is used to select channel 8 PGA gain.
  * @param  ADCx ADC Instance
  * @param  ADC PGA Gain
  * @param  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gainh_ch8pga(ADC_TypeDef *ADCx, uint32_t Gain)
{
  MODIFY_REG(ADCx->GAINH, ADC_GAINH_CH8PGA_MSK, Gain<<ADC_GAINH_CH8PGA_POSS);
}

/**
  * @brief  Get ADC Channel 8 PGA Gain.
  * @note   This is used to read channel 8 PGA gain.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_PGA_GAIN_X1
  *         @arg @ref MD_ADC_PGA_GAIN_X2
  *         @arg @ref MD_ADC_PGA_GAIN_X3
  *         @arg @ref MD_ADC_PGA_GAIN_X4
  *         @arg @ref MD_ADC_PGA_GAIN_X5
  *         @arg @ref MD_ADC_PGA_GAIN_X6
  *         @arg @ref MD_ADC_PGA_GAIN_X7
  *         @arg @ref MD_ADC_PGA_GAIN_X8
  */
__STATIC_INLINE uint32_t md_adc_get_gainh_ch8pga(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->GAINH, ADC_GAINH_CH8PGA_MSK)>>ADC_GAINH_CH8PGA_POSS);
}

/**
  * @brief  Set ADC Channels 8~15 PGA Gain.
  * @note   This register is used to select channels 8-15 PGA gain.
  * @param  GainH Register Values for CH8~CH15.
  * @retval None
  */
__STATIC_INLINE void md_adc_set_gainh(ADC_TypeDef *ADCx, uint32_t GainH)
{
  WRITE_REG(ADCx->GAINH, GainH);
}

/**
  * @brief  Get ADC Channels 8~15 PGA Gain.
  * @note   This register is used to read channels 8-15 PGA gain.
  * @param  ADCx ADC Instance
  * @retval GainH Register Values for CH8~CH15.
  */
__STATIC_INLINE uint32_t md_adc_get_gainh(ADC_TypeDef *ADCx)
{
  return READ_REG(ADCx->GAINH);
}

/**
  * @brief  Refresh ADC FIFOs SS0~SS3.
  * @note   This register allowed users to reset ADC FIFO when starting a 
  *         new Sample Sequencer.
  * @param  ADCx ADC Instance
  * @param  Value if bit (1 or 0)
  * @retval None
  */
__STATIC_INLINE void md_adc_set_frf_ffrst(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->FRF, ADC_FRF_FFRST_MSK);
}

/**
  * @brief  Get ADC FIFO Refresh Status.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_frf_ffrst(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->FRF, ADC_FRF_FFRST_MSK)>>ADC_FRF_FFRST_POS);
}

/**
  * @brief  Refresh ADC SS3 FIFO.
  * @note   This register is used to refresh the FIFO of sequencer 3 at any
  *         time. This bit will cleared by itself.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_set_frf_ss3rf(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->FRF, ADC_FRF_SS3RF_MSK);
}

/**
  * @brief  Refresh ADC SS32 FIFO.
  * @note   This register is used to refresh the FIFO of sequencer 2 at any
  *         time. This bit will cleared by itself.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_set_frf_ss2rf(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->FRF, ADC_FRF_SS2RF_MSK);
}

/**
  * @brief  Refresh ADC SS1 FIFO.
  * @note   This register is used to refresh the FIFO of sequencer 1 at any
  *         time. This bit will cleared by itself.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_set_frf_ss1rf(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->FRF, ADC_FRF_SS1RF_MSK);
}

/**
  * @brief  Refresh ADC SS0 FIFO.
  * @note   This register is used to refresh the FIFO of sequencer 0 at any
  *         time. This bit will cleared by itself.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_set_frf_ss0rf(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->FRF, ADC_FRF_SS0RF_MSK);
}

/**
  * @brief  Refresh ADC FIFO Register.
  * @note   This is used to set RFR register.
  * @param  ADCx ADC Instance
  * @param  Register Value
  * @retval None
  */
__STATIC_INLINE void md_adc_set_frf(ADC_TypeDef *ADCx, uint32_t Value)
{
  WRITE_REG(ADCx->FRF, Value);
}

/**
  * @brief  Get ADC FIFO Refresh Register.
  * @note   This is used to get RFR register.
  * @param  ADCx ADC Instance
  * @retval Register Value
  */
__STATIC_INLINE uint32_t md_adc_get_frf(ADC_TypeDef *ADCx)
{
  return READ_REG(ADCx->FRF);
}

/**
  * @brief  Check if all ADC Sequencer is idle.
  * @note   Check if SS0~SS3 is idle.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_idle(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SSEN, ADC_SSEN_IDLE_MSK) == (ADC_SSEN_IDLE_MSK));
}

/**
  * @brief  ADC Sample Sequencer 3 (SS3) Enable.
  * @note   User can set this bit to enable sample sequencer 3 (SS3). 
  *         This bit will cleared by itself.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ssen_ss3en(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SSEN, ADC_SSEN_SS3EN_MSK);
}

/**
  * @brief  ADC Sample Sequencer 3 (SS3) Disable.
  * @note   Disable sample sequencer 3 (SS3).
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ssen_ss3en(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SSEN, ADC_SSEN_SS3EN_MSK);
}

/**
  * @brief  Check if ADC Sample Sequencer 3 (SS3) is enabled.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ssen_ss3en(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SSEN, ADC_SSEN_SS3EN_MSK) == (ADC_SSEN_SS3EN_MSK));
}

/**
  * @brief  ADC Sample Sequencer 2 (SS2) Enable.
  * @note   User can set this bit to enable sample sequencer 2 (SS2). 
  *         This bit will cleared by itself.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ssen_ss2en(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SSEN, ADC_SSEN_SS2EN_MSK);
}

/**
  * @brief  ADC Sample Sequencer 2 (SS2) Disable.
  * @note   Disable sample sequencer 2 (SS2).
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ssen_ss2en(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SSEN, ADC_SSEN_SS2EN_MSK);
}

/**
  * @brief  Check if ADC Sample Sequencer 2 (SS2) is enabled.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ssen_ss2en(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SSEN, ADC_SSEN_SS2EN_MSK) == (ADC_SSEN_SS2EN_MSK));
}

/**
  * @brief  ADC Sample Sequencer 1 (SS1) Enable.
  * @note   User can set this bit to enable sample sequencer 1 (SS1). 
  *         This bit will cleared by itself.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ssen_ss1en(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SSEN, ADC_SSEN_SS1EN_MSK);
}

/**
  * @brief  ADC Sample Sequencer 1 (SS1) Disable.
  * @note   Disable sample sequencer 1 (SS1).
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ssen_ss1en(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SSEN, ADC_SSEN_SS1EN_MSK);
}

/**
  * @brief  Check if ADC Sample Sequencer 1 (SS1) is enabled.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ssen_ss1en(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SSEN, ADC_SSEN_SS1EN_MSK) == (ADC_SSEN_SS1EN_MSK));
}

/**
  * @brief  ADC Sample Sequencer 0 (SS0) Enable.
  * @note   User can set this bit to enable sequencer 0 (SS0). 
  *         This bit will cleared by itself.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ssen_ss0en(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SSEN, ADC_SSEN_SS0EN_MSK);
}

/**
  * @brief  AADC Sample Sequencer 0 (SS0) Disable.
  * @note   Disable sample sequencer 0 (SS0).
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ssen_ss0en(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SSEN, ADC_SSEN_SS0EN_MSK);
}

/**
  * @brief  Check if ADC Sample Sequencer 0 (SS0) is enabled.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ssen_ss0en(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SSEN, ADC_SSEN_SS0EN_MSK) == (ADC_SSEN_SS0EN_MSK));
}

/**
  * @brief  ADC Sample Sequencer 3 (SS3) Initiate.
  * @note   Triggers smapling on SS3 if the sequencer is enabled in the ADC_SSEN_SS3EN. 
  *         This bit will cleared by itself.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_set_swtri_ss3(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SWTRI, ADC_SWTRI_SS3_MSK);
}

/**
  * @brief  ADC Sample Sequencer 2 (SS2) Initiate.
  * @note   Triggers smapling on SS2 if the sequencer is enabled in the ADC_SSEN_SS2EN. 
  *         This bit will cleared by itself.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_set_swtri_ss2(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SWTRI, ADC_SWTRI_SS2_MSK);
}

/**
  * @brief  ADC Sample Sequencer 1 (SS1) Initiate.
  * @note   Triggers smapling on SS1 if the sequencer is enabled in the ADC_SSEN_SS1EN. 
  *         This bit will cleared by itself.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_set_swtri_ss1(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SWTRI, ADC_SWTRI_SS1_MSK);
}

/**
  * @brief  ADC Sample Sequencer 0 (SS0) Initiate.
  * @note   Triggers smapling on SS0 if the sequencer is enabled in the ADC_SSEN_SS0EN. 
  *         This bit will cleared by itself.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_set_swtri_ss0(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SWTRI, ADC_SWTRI_SS0_MSK);
}

/**
  * @brief  ADC Timeout Interrupt Enable.
  * @note   User can set this bit to enable timeout Interrupt function.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ier_toie(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, ADC_IER_TOIE_MSK);
}

/**
  * @brief  ADC Sample Sequencer 3 (SS3) Interrupt Enable.
  * @note   User can set this bit to enable sequencer 3 Interrupt function.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ier_ss3ie(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, ADC_IER_SS3IE_MSK);
}

/**
  * @brief  ADC Sample Sequencer 2 (SS2) Interrupt Enable.
  * @note   User can set this bit to enable sequencer 2 Interrupt function.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ier_ss2ie(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, ADC_IER_SS2IE_MSK);
}

/**
  * @brief  ADC Sample Sequencer 1 (SS1) Interrupt Enable.
  * @note   User can set this bit to enable sequencer 1 Interrupt function.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ier_ss1ie(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, ADC_IER_SS1IE_MSK);
}

/**
  * @brief  ADC Sample Sequencer 0 (SS0) Interrupt Enable.
  * @note   User can set this bit to enable sequencer 0 Interrupt function.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ier_ss0ie(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IER, ADC_IER_SS0IE_MSK);
}

/**
  * @brief  ADC Timeout Interrupt Disable.
  * @note   User can set this bit to disable timeout Interrupt function.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_idr_toid(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IDR, ADC_IDR_TOID_MSK);
}

/**
  * @brief  ADC Sample Sequencer 3 (SS3) Interrupt Disable.
  * @note   User can set this bit to disable sequencer 3 Interrupt function.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_idr_ss3id(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IDR, ADC_IDR_SS3ID_MSK);
}

/**
  * @brief  ADC Sample Sequencer 2 (SS2) Interrupt Disable.
  * @note   User can set this bit to disable sequencer 2 Interrupt function.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_idr_ss2id(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IDR, ADC_IDR_SS2ID_MSK);
}

/**
  * @brief  ADC Sample Sequencer 1 (SS1) Interrupt Disable.
  * @note   User can set this bit to disable sequencer 1 Interrupt function.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_idr_ss1id(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IDR, ADC_IDR_SS1ID_MSK);
}

/**
  * @brief  ADC Sample Sequencer 0 (SS0) Interrupt Disable.
  * @note   User can set this bit to disable sequencer 0 Interrupt function.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_idr_ss0id(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->IDR, ADC_IDR_SS0ID_MSK);
}

/**
  * @brief  Check if ADC Timeout Interrupt is Enabled.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ivs_toivs(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IVS, ADC_IVS_TOIVS_MSK) == (ADC_IVS_TOIVS_MSK));
}

/**
  * @brief  Check if ADC Sample Sequencer 3 (SS3) Interrupt is Enabled.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ivs_ss3ivs(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IVS, ADC_IVS_SS3IVS_MSK) == (ADC_IVS_SS3IVS_MSK));
}

/**
  * @brief  Check if ADC Sample Sequencer 2 (SS2) Interrupt is Enabled.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ivs_ss2ivs(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IVS, ADC_IVS_SS2IVS_MSK) == (ADC_IVS_SS2IVS_MSK));
}

/**
  * @brief  Check if ADC Sample Sequencer 1 (SS1) Interrupt is Enabled.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ivs_ss1ivs(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IVS, ADC_IVS_SS1IVS_MSK) == (ADC_IVS_SS1IVS_MSK));
}

/**
  * @brief  Check if ADC Sample Sequencer 0 (SS0) Interrupt is Enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ivs_ss0ivs(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IVS, ADC_IVS_SS0IVS_MSK) == (ADC_IVS_SS0IVS_MSK));
}

/**
  * @brief  Check Timeout Raw Interrupt Flag Status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_rif_torif(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->RIF, ADC_RIF_TORIF_MSK) == (ADC_RIF_TORIF_MSK));
}

/**
  * @brief  Check ADC Sample Sequencer 3 (SS3) Raw Interrupt Flag Status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_rif_ss3rif(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->RIF, ADC_RIF_SS3RIF_MSK) == (ADC_RIF_SS3RIF_MSK));
}

/**
  * @brief  Check ADC Sample Sequencer 2 (SS2) Raw Interrupt Flag Status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_rif_ss2rif(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->RIF, ADC_RIF_SS2RIF_MSK) == (ADC_RIF_SS2RIF_MSK));
}

/**
  * @brief  Check ADC Sample Sequencer 1 (SS1) Raw Interrupt Flag Status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_rif_ss1rif(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->RIF, ADC_RIF_SS1RIF_MSK) == (ADC_RIF_SS1RIF_MSK));
}

/**
  * @brief  Check ADC Sample Sequencer 0 (SS0) Raw Interrupt Flag Status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_rif_ss0rif(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->RIF, ADC_RIF_SS0RIF_MSK) == (ADC_RIF_SS0RIF_MSK));
}

/**
  * @brief  Check Timeout Interrupt Flag Masked Status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ifm_torif(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IFM, ADC_IFM_TOIFM_MSK) == (ADC_IFM_TOIFM_MSK));
}

/**
  * @brief  Check ADC Sample Sequencer 3 (SS3) Interrupt Flag Masked Status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ifm_ss3rif(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IFM, ADC_IFM_SS3IFM_MSK) == (ADC_IFM_SS3IFM_MSK));
}

/**
  * @brief  Check ADC Sample Sequencer 2 (SS2) Interrupt Flag Masked Status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ifm_ss2rif(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IFM, ADC_IFM_SS2IFM_MSK) == (ADC_IFM_SS2IFM_MSK));
}

/**
  * @brief  Check ADC Sample Sequencer 1 (SS1) Interrupt Flag Masked Status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ifm_ss1rif(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IFM, ADC_IFM_SS1IFM_MSK) == (ADC_IFM_SS1IFM_MSK));
}

/**
  * @brief  Check ADC Sample Sequencer 0 (SS0) Interrupt Flag Masked Status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ifm_ss0rif(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->IFM, ADC_IFM_SS0IFM_MSK) == (ADC_IFM_SS0IFM_MSK));
}

/**
  * @brief  ADC Timeout Interrupt Clear.
  * @note   User can set this bit to clear timeout interrupt status.
  * @param  ADCx ADC Instance
  * @retval None.
  */
__STATIC_INLINE void md_uart_clear_flag_icr_toicr(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->ICR, ADC_ICR_TOICR_MSK);
}

/**
  * @brief  ADC Sample Sequencer 3 (SS3) Interrupt Clear.
  * @note   User can set this bit to clear SS3 interrupt status.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_clear_flag_icr_ss3icr(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->ICR, ADC_ICR_SS3ICR_MSK);
}

/**
  * @brief  ADC Sample Sequencer 2 (SS2) Interrupt Clear.
  * @note   User can set this bit to clear SS2 interrupt status.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_clear_flag_icr_ss2icr(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->ICR, ADC_ICR_SS2ICR_MSK);
}

/**
  * @brief  ADC Sample Sequencer 1 (SS1) Interrupt Clear.
  * @note   User can set this bit to clear SS1 interrupt status.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_clear_flag_icr_ss1icr(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->ICR, ADC_ICR_SS1ICR_MSK);
}

/**
  * @brief  ADC Sample Sequencer 0 (SS0) Interrupt Clear.
  * @note   User can set this bit to clear SS0 interrupt status.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_uart_clear_flag_icr_ss0icr(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->ICR, ADC_ICR_SS0ICR_MSK);
}

/**
  * @brief  ADC SS3 DMA Function Enable.
  * @note   User can set this register to enable DMA function. 
  *         For S3, if set when FIFO is not empty, DMA Single REQ will rise.
  * @param  UARTx UART Instance
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_dma_ss3dmaen(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->DMA, ADC_DMA_SS3_DMAEN_MSK);
}

/**
  * @brief  ADC SS3 DMA Function Disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_dma_ss3dmaen(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->DMA, ADC_DMA_SS3_DMAEN_MSK);
}

/**
  * @brief  Check if ADC SS3 DMA is enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_dma_ss3dmaen(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DMA, ADC_DMA_SS3_DMAEN_MSK) == (ADC_DMA_SS3_DMAEN_MSK));
}

/**
  * @brief  ADC SS2 DMA Function Enable.
  * @note   User can set this register to enable DMA function. 
  *         For S2, if set when FIFO is not empty, DMA Single REQ will rise.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_dma_ss2dmaen(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->DMA, ADC_DMA_SS2_DMAEN_MSK);
}

/**
  * @brief  ADC SS2 DMA Function Disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_dma_ss2dmaen(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->DMA, ADC_DMA_SS2_DMAEN_MSK);
}

/**
  * @brief  Check if ADC SS2 DMA is enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_dma_ss2dmaen(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DMA, ADC_DMA_SS2_DMAEN_MSK) == (ADC_DMA_SS2_DMAEN_MSK));
}

/**
  * @brief  ADC SS1 DMA Function Enable.
  * @note   User can set this register to enable DMA function. 
  *         For S1, if set when FIFO is not empty, DMA Single REQ will rise.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_dma_ss1dmaen(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->DMA, ADC_DMA_SS1_DMAEN_MSK);
}

/**
  * @brief  ADC SS1 DMA Function Disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_dma_ss1dmaen(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->DMA, ADC_DMA_SS1_DMAEN_MSK);
}

/**
  * @brief  Check if ADC SS1 DMA is enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_dma_ss1dmaen(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DMA, ADC_DMA_SS1_DMAEN_MSK) == (ADC_DMA_SS1_DMAEN_MSK));
}

/**
  * @brief  ADC SS0 DMA Function Enable.
  * @note   User can set this register to enable DMA function. 
  *         For S0, if set when FIFO is not empty, DMA Single REQ will rise.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_dma_ss0dmaen(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->DMA, ADC_DMA_SS0_DMAEN_MSK);
}

/**
  * @brief  ADC SS0 DMA Function Disable.
  * @param  UARTx UART Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_dma_ss0dmaen(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->DMA, ADC_DMA_SS0_DMAEN_MSK);
}

/**
  * @brief  Check if ADC SS3 DMA is enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_dma_ss0dmaen(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->DMA, ADC_DMA_SS0_DMAEN_MSK) == (ADC_DMA_SS0_DMAEN_MSK));
}

/**
  * @brief  Set SS0 Trigger Select.
  * @note   This field selects the trigger source for Sample Sequencer 0.
  * @param  ADCx ADC Instance.
  * @param  Sample sequencer trigger sources.
  * @param  This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_CON_SEL_SW
  *         @arg @ref MD_ADC_SS_CON_SEL_BS16T1
  *         @arg @ref MD_ADC_SS_CON_SEL_ALWAYS
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T2
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T3
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T2
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T3
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T4
  *         @arg @ref MD_ADC_SS_CON_SEL_AD16C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GPIO
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP0
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP1
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP2
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP3
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss0_con_sel(ADC_TypeDef *ADCx, uint32_t TrigSource)
{
  MODIFY_REG(ADCx->SS0_CON, ADC_SS0_CON_SEL_MSK, TrigSource<<ADC_SS0_CON_SEL_POSS);
}

/**
  * @brief  Get SS0 Trigger Source Select.
  * @param  ADCx ADC Instance.
  * @retval This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_CON_SEL_SW
  *         @arg @ref MD_ADC_SS_CON_SEL_BS16T1
  *         @arg @ref MD_ADC_SS_CON_SEL_ALWAYS
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T2
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T3
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T2
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T3
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T4
  *         @arg @ref MD_ADC_SS_CON_SEL_AD16C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GPIO
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP0
  *         @arg @ref MD_ADC_SS_CCON_SEL_CMP1
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP2
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP3
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_con_sel(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_CON, ADC_SS0_CON_SEL_MSK)>>ADC_SS0_CON_SEL_POSS);
}

/**
  * @brief  Set ADC Sample Sequencer 0 (SS0) Trigger Type select.
  * @note   User can set this bit to select the type of trigger.
  * @param  Sample sequencer trigger types.
  * @param  This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_CON_TYP_EDGE
  *         @arg @ref MD_ADC_SS_COM_TYP_LEVEL
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss0_con_type(ADC_TypeDef *ADCx, uint32_t TrigType)
{
  MODIFY_REG(ADCx->SS0_CON, ADC_SS0_CON_TYP_MSK, TrigType<<ADC_SS0_CON_TYP_POS);
}

/**
  * @brief  Get ADC Sample Sequencer 0 (SS0) Trigger Type select.
  * @param  ADCx ADC Instance.
  * @retval  This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_CON_TYP_EDGE
  *         @arg @ref MD_ADC_SS_COM_TYP_LEVEL
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_con_type(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_CON, ADC_SS0_CON_TYP_MSK)>>ADC_SS0_CON_TYP_POS);
}

/**
  * @brief  Set ADC Sample Sequencer 0 (SS0) Priority.
  * @note   This field contains a binary-encoded value specifying the
  *         priority encoding of SS0. The prioriteies assigned to the
  *         sequencers must be uniquely mapped.
  * @param  ADCx ADC Instance.
  * @param  Sample sequencer trigger priorities.
  * @param  This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS0_CON_PRI_HIGHEST
  *         @arg @ref MD_ADC_SS0_CON_PRI_SECOND
  *         @arg @ref MD_ADC_SS0_CON_PRI_THIRD
  *         @arg @ref MD_ADC_SS0_CON_PRI_LOWEST
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss0_con_pri(ADC_TypeDef *ADCx, uint32_t priority)
{
  MODIFY_REG(ADCx->SS0_CON, ADC_SS0_CON_PRI_MSK, priority<<ADC_SS0_CON_PRI_POSS);
}

/**
  * @brief  Get ADC Sample Sequencer 0 (SS0) Priority.
  * @param  ADCx ADC Instance.
  * @retval  This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS0_CON_PRI_HIGHEST
  *         @arg @ref MD_ADC_SS0_CON_PRI_SECOND
  *         @arg @ref MD_ADC_SS0_CON_PRI_THIRD
  *         @arg @ref MD_ADC_SS0_CON_PRI_LOWEST
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_con_pri(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_CON, ADC_SS0_CON_PRI_MSK)>>ADC_SS0_CON_PRI_POSS);
}

/**
  * @brief  Enable One Shot Trigger Mode.
  * @note   When set HIGH, each trigger will only sample once and use one slot in FIFO.
  * @param  ADCx ADC Instance.
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_ss0_con_one(ADC_TypeDef *adcx)
{
  SET_BIT(adcx->SS0_CON, ADC_SS0_CON_ONE_MSK);
}

/**
  * @brief  Disable One Shot Trigger Mode.
  * @param  ADCx ADC Instance.
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_ss0_con_one(ADC_TypeDef *adcx)
{
  CLEAR_BIT(adcx->SS0_CON, ADC_SS0_CON_ONE_MSK);
}

/**
  * @brief  Set 8th Sample Input Select.
  * @note   User can set this register to select which channel will be
  *         sampled. For example, a value of n indicates the input is
  *         channel n.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss0_mux0_mux7(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS0_MUX0, ADC_SS0_MUX0_MUX7_MSK, AdinPin<<ADC_SS0_MUX0_MUX7_POSS);
}

/**
  * @brief  Get 8th Sample Input Select.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_mux0_mux7(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_MUX0, ADC_SS0_MUX0_MUX7_MSK)>>ADC_SS0_MUX0_MUX7_POSS);
}

/**
  * @brief  Set 7th Sample Input Select.
  * @note   User can set this register to select which channel will be
  *         sampled. For example, a value of n indicates the input is
  *         channel n.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss0_mux0_mux6(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS0_MUX0, ADC_SS0_MUX0_MUX6_MSK, AdinPin<<ADC_SS0_MUX0_MUX6_POSS);
}

/**
  * @brief  Get 7th Sample Input Select.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_mux0_mux6(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_MUX0, ADC_SS0_MUX0_MUX6_MSK)>>ADC_SS0_MUX0_MUX6_POSS);
}

/**
  * @brief  Set 6th Sample Input Select.
  * @note   User can set this register to select which channel will be
  *         sampled. For example, a value of n indicates the input is
  *         channel n.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss0_mux0_mux5(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS0_MUX0, ADC_SS0_MUX0_MUX5_MSK, AdinPin<<ADC_SS0_MUX0_MUX5_POSS);
}

/**
  * @brief  Get 6th Sample Input Select..
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_mux0_mux5(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_MUX0, ADC_SS0_MUX0_MUX5_MSK)>>ADC_SS0_MUX0_MUX5_POSS);
}

/**
  * @brief  Set 5th Sample Input Select.
  * @note   User can set this register to select which channel will be
  *         sampled. For example, a value of n indicates the input is
  *         channel n.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss0_mux0_mux4(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS0_MUX0, ADC_SS0_MUX0_MUX4_MSK, AdinPin<<ADC_SS0_MUX0_MUX4_POSS);
}

/**
  * @brief  Get 5th Sample Input Select.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_mux0_mux4(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_MUX0, ADC_SS0_MUX0_MUX4_MSK)>>ADC_SS0_MUX0_MUX4_POSS);
}

/**
  * @brief  Set 4th Sample Input Select.
  * @note   User can set this register to select which channel will be
  *         sampled. For example, a value of n indicates the input is
  *         channel n.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss0_mux0_mux3(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS0_MUX0, ADC_SS0_MUX0_MUX3_MSK, AdinPin<<ADC_SS0_MUX0_MUX3_POSS);
}

/**
  * @brief  Get 4th Sample Input Select.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_mux0_mux3(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_MUX0, ADC_SS0_MUX0_MUX3_MSK)>>ADC_SS0_MUX0_MUX3_POSS);
}

/**
  * @brief  Set 3rd Sample Input Select.
  * @note   User can set this register to select which channel will be
  *         sampled. For example, a value of n indicates the input is
  *         channel n.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss0_mux0_mux2(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS0_MUX0, ADC_SS0_MUX0_MUX2_MSK, AdinPin<<ADC_SS0_MUX0_MUX2_POSS);
}

/**
  * @brief  Get 3rd Sample Input Select.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_mux0_mux2(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_MUX0, ADC_SS0_MUX0_MUX2_MSK)>>ADC_SS0_MUX0_MUX2_POSS);
}

/**
  * @brief  Set 2nd Sample Input Select.
  * @note   User can set this register to select which channel will be
  *         sampled. For example, a value of n indicates the input is
  *         channel n.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss0_mux0_mux1(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS0_MUX0, ADC_SS0_MUX0_MUX1_MSK, AdinPin<<ADC_SS0_MUX0_MUX1_POSS);
}

/**
  * @brief  Get 2nd Sample Input Select.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_mux0_mux1(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_MUX0, ADC_SS0_MUX0_MUX1_MSK)>>ADC_SS0_MUX0_MUX1_POSS);
}

/**
  * @brief  Set 1st Sample Input Select.
  * @note   User can set this register to select which channel will be
  *         sampled. For example, a value of n indicates the input is
  *         channel n.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss0_mux0_mux0(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS0_MUX0, ADC_SS0_MUX0_MUX0_MSK, AdinPin<<ADC_SS0_MUX0_MUX0_POSS);
}

/**
  * @brief  Get 1st Sample Input Select.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_mux0_mux0(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_MUX0, ADC_SS0_MUX0_MUX0_MSK)>>ADC_SS0_MUX0_MUX0_POSS);
}

/**
  * @brief  Set ADC channels MUX 0~7.
  * @note   Set ADC SS0_MUX0 register.
  * @note   Mapping ADINx to ADC channels 0~7.

  * @param  ADC Channel
  * @param  MUX Register
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss0_mux0(ADC_TypeDef *ADCx, uint32_t RegValue)
{
  WRITE_REG(ADCx->SS0_MUX0, RegValue);
}

/**
  * @brief  Get ADC channels MUX 0~7.
  * @note   Get ADC SS0_MUX0 register.
  * @param  ADCx ADC Instance
  * @retval SS0_MUX0 Register Value
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_mux0(ADC_TypeDef *ADCx)
{
  return READ_REG(ADCx->SS0_MUX0);
}

/**
  * @brief  Set 16th Sample Input Select.
  * @note   User can set this register to select which channel will be
  *         sampled. For example, a value of n indicates the input is
  *         channel n.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss0_mux1_mux15(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS0_MUX1, ADC_SS0_MUX1_MUX15_MSK, AdinPin<<ADC_SS0_MUX1_MUX15_POSS);
}

/**
  * @brief  Get 16th Sample Input Select.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_mux1_mux15(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_MUX0, ADC_SS0_MUX1_MUX15_MSK)>>ADC_SS0_MUX1_MUX15_POSS);
}

/**
  * @brief  Set 15th Sample Input Select.
  * @note   User can set this register to select which channel will be
  *         sampled. For example, a value of n indicates the input is
  *         channel n.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss0_mux1_mux14(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS0_MUX1, ADC_SS0_MUX1_MUX14_MSK, AdinPin<<ADC_SS0_MUX1_MUX14_POSS);
}

/**
  * @brief  Get 15th Sample Input Select.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_mux1_mux14(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_MUX0, ADC_SS0_MUX1_MUX14_MSK)>>ADC_SS0_MUX1_MUX14_POSS);
}

/**
  * @brief  Set 14th Sample Input Select.
  * @note   User can set this register to select which channel will be
  *         sampled. For example, a value of n indicates the input is
  *         channel n.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss0_mux1_mux13(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS0_MUX1, ADC_SS0_MUX1_MUX13_MSK, AdinPin<<ADC_SS0_MUX1_MUX13_POSS);
}

/**
  * @brief  Get 14th Sample Input Select.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_mux1_mux13(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_MUX0, ADC_SS0_MUX1_MUX13_MSK)>>ADC_SS0_MUX1_MUX13_POSS);
}

/**
  * @brief  Set 13th Sample Input Select.
  * @note   User can set this register to select which channel will be
  *         sampled. For example, a value of n indicates the input is
  *         channel n.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss0_mux1_mux12(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS0_MUX1, ADC_SS0_MUX1_MUX12_MSK, AdinPin<<ADC_SS0_MUX1_MUX12_POSS);
}

/**
  * @brief  Get 13th Sample Input Select.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_mux1_mux12(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_MUX0, ADC_SS0_MUX1_MUX12_MSK)>>ADC_SS0_MUX1_MUX12_POSS);
}

/**
  * @brief  Set 12th Sample Input Select.
  * @note   User can set this register to select which channel will be
  *         sampled. For example, a value of n indicates the input is
  *         channel n.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss0_mux1_mux11(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS0_MUX1, ADC_SS0_MUX1_MUX11_MSK, AdinPin<<ADC_SS0_MUX1_MUX11_POSS);
}

/**
  * @brief  Get 12th Sample Input Select.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_mux1_mux11(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_MUX0, ADC_SS0_MUX1_MUX11_MSK)>>ADC_SS0_MUX1_MUX11_POSS);
}

/**
  * @brief  Set 11th Sample Input Select.
  * @note   User can set this register to select which channel will be
  *         sampled. For example, a value of n indicates the input is
  *         channel n.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss0_mux1_mux10(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS0_MUX1, ADC_SS0_MUX1_MUX10_MSK, AdinPin<<ADC_SS0_MUX1_MUX10_POSS);
}

/**
  * @brief  Get 11th Sample Input Select.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_mux1_mux10(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_MUX0, ADC_SS0_MUX1_MUX10_MSK)>>ADC_SS0_MUX1_MUX10_POSS);
}

/**
  * @brief  Set 10th Sample Input Select.
  * @note   User can set this register to select which channel will be
  *         sampled. For example, a value of n indicates the input is
  *         channel n.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss0_mux1_mux9(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS0_MUX1, ADC_SS0_MUX1_MUX9_MSK, AdinPin<<ADC_SS0_MUX1_MUX9_POSS);
}

/**
  * @brief  Get 10th Sample Input Select.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_mux1_mux9(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_MUX0, ADC_SS0_MUX1_MUX9_MSK)>>ADC_SS0_MUX1_MUX9_POSS);
}

/**
  * @brief  Set 9th Sample Input Select.
  * @note   User can set this register to select which channel will be
  *         sampled. For example, a value of n indicates the input is
  *         channel n.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss0_mux1_mux8(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS0_MUX1, ADC_SS0_MUX1_MUX8_MSK, AdinPin<<ADC_SS0_MUX1_MUX8_POSS);
}

/**
  * @brief  Get 9th Sample Input Select.
  * @param  ADCx ADC Instance
  * @retval  Gain parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_mux1_mux8(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_MUX0, ADC_SS0_MUX1_MUX8_MSK)>>ADC_SS0_MUX1_MUX8_POSS);
}

/**
  * @brief  Set ADC channels MUX 8~15.
  * @note   Set SS0_MUX1 register for channels 8~15.
  * @param  ADCx ADC Instance.
  * @param  SS0 MUX1 Register.
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss0_mux1(ADC_TypeDef *ADCx, uint32_t RegValue)
{
  WRITE_REG(ADCx->SS0_MUX1, RegValue);
}

/**
  * @brief  Get ADC channels MUX 8~15.
  * @note   Get SS0_MUX1 register for channels 8~15.
  * @param  ADCx ADC Instance.
  * @retval SS0 MUX1 Register.
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_mux1(ADC_TypeDef *ADCx)
{
  return READ_REG(ADCx->SS0_MUX1);
}

/**
  * @brief  16th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss0_end_ie15(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS0_END, ADC_SS0_END_IE15_MSK);
}

/**
  * @brief  16th Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss0_end_ie15(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS0_END, ADC_SS0_END_IE15_MSK);
}

/**
  * @brief  Check if 16th Sample Interrupt is Enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss0_end_ie15(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_END, ADC_SS0_END_IE15_MSK) == (ADC_SS0_END_IE15_MSK));
}

/**
  * @brief  15th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss0_end_ie14(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS0_END, ADC_SS0_END_IE14_MSK);
}

/**
  * @brief  15th Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss0_end_ie14(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS0_END, ADC_SS0_END_IE14_MSK);
}

/**
  * @brief  Check if 15th Sample Interrupt is Enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss0_end_ie14(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_END, ADC_SS0_END_IE14_MSK) == (ADC_SS0_END_IE14_MSK));
}

/**
  * @brief  14th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss0_end_ie13(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS0_END, ADC_SS0_END_IE13_MSK);
}

/**
  * @brief  14th Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss0_end_ie13(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS0_END, ADC_SS0_END_IE13_MSK);
}

/**
  * @brief  Check if 14th Sample Interrupt is Enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss0_end_ie13(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_END, ADC_SS0_END_IE13_MSK) == (ADC_SS0_END_IE13_MSK));
}

/**
  * @brief  13th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss0_end_ie12(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS0_END, ADC_SS0_END_IE12_MSK);
}

/**
  * @brief  13th Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss0_end_ie12(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS0_END, ADC_SS0_END_IE12_MSK);
}

/**
  * @brief  Check if 13th Sample Interrupt is Enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss0_end_ie12(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_END, ADC_SS0_END_IE12_MSK) == (ADC_SS0_END_IE12_MSK));
}

/**
  * @brief  12th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss0_end_ie11(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS0_END, ADC_SS0_END_IE11_MSK);
}

/**
  * @brief  12th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss0_end_ie11(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS0_END, ADC_SS0_END_IE11_MSK);
}

/**
  * @brief  Check 12th Sample Interrupt is Enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss0_end_ie11(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_END, ADC_SS0_END_IE11_MSK) == (ADC_SS0_END_IE11_MSK));
}

/**
  * @brief  11th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss0_end_ie10(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS0_END, ADC_SS0_END_IE10_MSK);
}

/**
  * @brief  11th Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss0_end_ie10(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS0_END, ADC_SS0_END_IE10_MSK);
}

/**
  * @brief  Check if 11th Sample Interrupt is Enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss0_end_ie10(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_END, ADC_SS0_END_IE10_MSK) == (ADC_SS0_END_IE10_MSK));
}

/**
  * @brief  10th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss0_end_ie9(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS0_END, ADC_SS0_END_IE9_MSK);
}

/**
  * @brief  10th Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss0_end_ie9(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS0_END, ADC_SS0_END_IE9_MSK);
}

/**
  * @brief  Check if 10th Sample Interrupt is Enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss0_end_ie9(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_END, ADC_SS0_END_IE9_MSK) == (ADC_SS0_END_IE9_MSK));
}

/**
  * @brief  9th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss0_end_ie8(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS0_END, ADC_SS0_END_IE8_MSK);
}

/**
  * @brief  9th Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss0_end_ie8(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS0_END, ADC_SS0_END_IE8_MSK);
}

/**
  * @brief  Check if 9th Sample Interrupt is Enable.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss0_end_ie8(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_END, ADC_SS0_END_IE8_MSK) == (ADC_SS0_END_IE8_MSK));
}

/**
  * @brief  8th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss0_end_ie7(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS0_END, ADC_SS0_END_IE7_MSK);
}

/**
  * @brief  8th Sample Interrupt Disable
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss0_end_ie7(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS0_END, ADC_SS0_END_IE7_MSK);
}

/**
  * @brief  Check if 8th Sample Interrupt is Enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss0_end_ie7(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_END, ADC_SS0_END_IE7_MSK) == (ADC_SS0_END_IE7_MSK));
}

/**
  * @brief  7th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss0_end_ie6(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS0_END, ADC_SS0_END_IE6_MSK);
}

/**
  * @brief  7th Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss0_end_ie6(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS0_END, ADC_SS0_END_IE6_MSK);
}

/**
  * @brief  Check if 7th Sample Interrupt is Enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss0_end_ie6(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_END, ADC_SS0_END_IE6_MSK) == (ADC_SS0_END_IE6_MSK));
}


/**
  * @brief  6th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss0_end_ie5(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS0_END, ADC_SS0_END_IE5_MSK);
}

/**
  * @brief  6th Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss0_end_ie5(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS0_END, ADC_SS0_END_IE5_MSK);
}

/**
  * @brief  Check if 6th Sample Interrupt is Enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss0_end_ie5(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_END, ADC_SS0_END_IE5_MSK) == (ADC_SS0_END_IE5_MSK));
}

/**
  * @brief  5th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss0_end_ie4(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS0_END, ADC_SS0_END_IE4_MSK);
}

/**
  * @brief  5th Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss0_end_ie4(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS0_END, ADC_SS0_END_IE4_MSK);
}

/**
  * @brief  Check if 5th Sample Interrupt is Enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss0_end_ie4(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_END, ADC_SS0_END_IE4_MSK) == (ADC_SS0_END_IE4_MSK));
}

/**
  * @brief  4th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss0_end_ie3(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS0_END, ADC_SS0_END_IE3_MSK);
}

/**
  * @brief  4th Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss0_end_ie3(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS0_END, ADC_SS0_END_IE3_MSK);
}

/**
  * @brief  Check if 4th Sample Interrupt is Enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss0_end_ie3(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_END, ADC_SS0_END_IE3_MSK) == (ADC_SS0_END_IE3_MSK));
}

/**
  * @brief  3rd Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss0_end_ie2(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS0_END, ADC_SS0_END_IE2_MSK);
}

/**
  * @brief  3rd Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss0_end_ie2(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS0_END, ADC_SS0_END_IE2_MSK);
}

/**
  * @brief  Check if 3rd Sample Interrupt is Enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss0_end_ie2(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_END, ADC_SS0_END_IE2_MSK) == (ADC_SS0_END_IE2_MSK));
}

/**
  * @brief  2nd Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss0_end_ie1(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS0_END, ADC_SS0_END_IE1_MSK);
}

/**
  * @brief  2nd Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss0_end_ie1(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS0_END, ADC_SS0_END_IE1_MSK);
}

/**
  * @brief  Check if 2nd Sample Interrupt is Enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss0_end_ie1(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_END, ADC_SS0_END_IE1_MSK) == (ADC_SS0_END_IE1_MSK));
}

/**
  * @brief  1st Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss0_end_ie0(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS0_END, ADC_SS0_END_IE0_MSK);
}

/**
  * @brief  1st Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss0_end_ie0(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS0_END, ADC_SS0_END_IE0_MSK);
}

/**
  * @brief  Check if 1st Sample Interrupt is Enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss0_end_ie0(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_END, ADC_SS0_END_IE0_MSK) == (ADC_SS0_END_IE0_MSK));
}

/**
  * @brief  Set ADC SS0 sample counts.
  * @note   User can set this register to select how many times will ADC samples data.
  * @param  ADCx ADC Instance.
  * @param  End Value Min_Value=0x00 Max_Value=0x0F.
  * @retval None.
  */
__STATIC_INLINE void md_adc_set_ss0_end_end(ADC_TypeDef *ADCx, uint32_t EndValue)
{
  MODIFY_REG(ADCx->SS0_END, ADC_SS0_END_END_MSK, EndValue<<ADC_SS0_END_END_POSS);
}

/**
  * @brief  Get ADC SS0 sample counts.
  * @param  ADCx ADC Instance.
  * @retval End Value Min_Value=0x00 Max_Value=0x0F.
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_end_end(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_END, ADC_SS0_END_END_MSK)>>ADC_SS0_END_END_POSS);
}

/**
  * @brief  Set ADC Sample Sequence 0 End Control Register.
  * @note   Set ADC_SS0_END register
  * @param  ADCx ADC Instance
  * @param  ADC_SS0_END Register Value
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss0_end(ADC_TypeDef *ADCx, uint32_t RegValue)
{
  MODIFY_REG(ADCx->SS0_END, ADC_SS0_END_END_MSK, RegValue);
}

/**
  * @brief  Get ADC Sample Sequence 0 End Control Register.
  * @param  ADCx ADC Instance
  * @retval ADC_SS0_END Register Value
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_end(ADC_TypeDef *ADCx)
{
  return READ_REG(ADCx->SS0_END);
}

/**
  * @brief  Set ADC Sample Sequencer 0 (SS0) FIFO Overflow status
  * @note   When the FIFO is full and a write was requested. 
  *         When an overflow is detected, the most recent write is dropped.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss0_fstat_ov(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS0_END, ADC_SS0_FSTAT_OV_MSK);
}

/**
  * @brief  Get ADC Sample Sequencer 0 (SS0) FIFO Overflow status
  * @param  ADCx ADC Instance
  * @retval 1 or 0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_fstat_ov(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_FSTAT, ADC_SS0_FSTAT_OV_MSK)>>ADC_SS0_FSTAT_OV_POS);
}

/**
  * @brief  Check if ADC SS0 FSTAT OV is actived.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ss0_fstat_ov(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_FSTAT, ADC_SS0_FSTAT_OV_MSK) == (ADC_SS0_FSTAT_OV_MSK));
}

/**
  * @brief  Get ADC SS0 FSTAT FULL
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_fstat_full(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_FSTAT, ADC_SS0_FSTAT_FULL_MSK)>>ADC_SS0_FSTAT_FULL_POS);
}

/**
  * @brief  Check if ADC SS0 FSTAT FULL is actived.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ss0_fstat_full(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_FSTAT, ADC_SS0_FSTAT_FULL_MSK) == (ADC_SS0_FSTAT_FULL_MSK));
}

/**
  * @brief  Set ADC SS0 FSTAT UV.
  * @note   When the FIFO is empty and a read was requested. 
  *         The problematic read does not move the FIFO pointers, and 0s are returned.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_set_ss0_fstat_uv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS0_END, ADC_SS0_FSTAT_UV_MSK);
}

/**
  * @brief  Get ADC SS0 FSTAT UV
  * @param  ADCx ADC Instance
  * @retval 1 or 0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_fstat_uv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_FSTAT, ADC_SS0_FSTAT_UV_MSK)>>ADC_SS0_FSTAT_UV_POS);
}

/**
  * @brief  Check if ADC SS0 FSTAT UV is actived.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ss0_fstat_uv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_FSTAT, ADC_SS0_FSTAT_UV_MSK) == (ADC_SS0_FSTAT_UV_MSK));
}

/**
  * @brief  Get ADC SS0 FSTAT EMPTY
  * @param  ADCx ADC Instance
  * @retval 1 or 0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_fstat_empty(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_FSTAT, ADC_SS0_FSTAT_EMPTY_MSK)>>ADC_SS0_FSTAT_EMPTY_POS);
}

/**
  * @brief  Check if ADC SS0 FSTAT EMPTY is actived.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ss0_fstat_empty(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_FSTAT, ADC_SS0_FSTAT_EMPTY_MSK) == (ADC_SS0_FSTAT_EMPTY_MSK));
}

/**
  * @brief  Get ADC SS0 FSTAT HPTR
  * @note   The field contains the current “head” pointer index, which is the
  *         next entry to be written to FIFO.
  * @param  ADCx ADC Instance
  * @retval 1 or 0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_fstat_hptr(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_FSTAT, ADC_SS0_FSTAT_HPTR_MSK)>>ADC_SS0_FSTAT_HPTR_POSS);
}

/**
  * @brief  Get ADC SS0 FSTAT TPTR
  * @note   The field contains the current tail pointer index, which is the
  *         next entry to be read from FIFO.
  * @param  ADCx ADC Instance
  * @retval 1 or 0
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_fstat_tptr(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS0_FSTAT, ADC_SS0_FSTAT_TPTR_MSK)>>ADC_SS0_FSTAT_TPTR_POSS);
}

/**
  * @brief  Get ADC sample sequencer 0(SS0) result FIFO data.
  * @note   User can read conversion result data by reading this register.
  * @param  ADCx ADC Instance
  * @retval ADC Sampled Data
  */
__STATIC_INLINE uint32_t md_adc_get_ss0_data(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_REG(ADC->SS0_DATA));
}

/**
  * @brief  Set SS1 Trigger Select.
  * @note   This field selects the trigger source for Sample Sequencer 1.
  * @param  ADCx ADC Instance
  * @param  Sample sequencer trigger sources.
  *         This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_CON_SEL_SW
  *         @arg @ref MD_ADC_SS_CON_SEL_BS16T1
  *         @arg @ref MD_ADC_SS_CON_SEL_ALWAYS
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T2
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T3
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T2
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T3
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T4
  *         @arg @ref MD_ADC_SS_CON_SEL_AD16C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GPIO
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP0
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP1
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP2
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP3
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss1_con_sel(ADC_TypeDef *ADCx, uint32_t TrigSource)
{
  MODIFY_REG(ADCx->SS1_CON, ADC_SS1_CON_SEL_MSK, TrigSource<<ADC_SS1_CON_SEL_POSS);
}

/**
  * @brief  Get SS1 Trigger Select.
  * @param  ADCx ADC Instance.
  * @retval This return value can be one of the following values:
  *         @arg @ref MD_ADC_SS_CON_SEL_SW
  *         @arg @ref MD_ADC_SS_CON_SEL_BS16T1
  *         @arg @ref MD_ADC_SS_CON_SEL_ALWAYS
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T2
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T3
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T2
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T3
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T4
  *         @arg @ref MD_ADC_SS_CON_SEL_AD16C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GPIO
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP0
  *         @arg @ref MD_ADC_SS_CCON_SEL_CMP1
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP2
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP3
  * @retval None
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_con_sel(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_CON, ADC_SS1_CON_SEL_MSK)>>ADC_SS1_CON_SEL_POSS);
}

/**
  * @brief  ADC Sample Sequencer 1 (SS1) Trigger Type select.
  * @note   User can set this bit to select the type of trigger.
  * @param  ADCx ADC Instance.
  * @param  This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_CON_TYP_EDGE
  *         @arg @ref MD_ADC_SS_COM_TYP_LEVEL
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss1_con_type(ADC_TypeDef *ADCx, uint32_t TrigType)
{
  MODIFY_REG(ADCx->SS1_CON, ADC_SS1_CON_TYP_MSK, TrigType<<ADC_SS1_CON_TYP_POS);
}

/**
  * @brief  Get ADC Sample Sequencer 1 (SS1) Trigger Type.
  * @param  ADCx ADC Instance.
  * @retval  This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_CON_TYP_EDGE
  *         @arg @ref MD_ADC_SS_COM_TYP_LEVEL
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_con_type(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_CON, ADC_SS1_CON_TYP_MSK)>>ADC_SS1_CON_TYP_POS);
}

/**
  * @brief  Set ADC Sample Sequencer 1 (SS1) Priority.
  * @note   This field contains a binary-encoded value specifying the
  *         priority encoding of SS1. The prioriteies assigned to the
  *         sequencers must be uniquely mapped.
  * @param  ADCx ADC Instance.
  * @param  This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS0_CON_PRI_HIGHEST
  *         @arg @ref MD_ADC_SS0_CON_PRI_SECOND
  *         @arg @ref MD_ADC_SS0_CON_PRI_THIRD
  *         @arg @ref MD_ADC_SS0_CON_PRI_LOWEST
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss1_con_pri(ADC_TypeDef *adcx, uint32_t priority)
{
  MODIFY_REG(adcx->SS1_CON, ADC_SS1_CON_PRI_MSK, priority<<ADC_SS1_CON_PRI_POSS);
}

/**
  * @brief  Get ADC Sample Sequencer 1 (SS1) Priority.
  * @param  ADCx ADC Instance.
  * @retval This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS0_CON_PRI_HIGHEST
  *         @arg @ref MD_ADC_SS0_CON_PRI_SECOND
  *         @arg @ref MD_ADC_SS0_CON_PRI_THIRD
  *         @arg @ref MD_ADC_SS0_CON_PRI_LOWEST
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_con_pri(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_CON, ADC_SS1_CON_PRI_MSK)>>ADC_SS1_CON_PRI_POSS);
}

/**
  * @brief  One Shot Trigger Mode enable.
  * @note   When set HIGH, each trigger will only sample once and use one
  *         slot in FIFO.
  * @param  ADCx ADC Instance.
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_ss1_con_one(ADC_TypeDef *adcx)
{
  SET_BIT(adcx->SS1_CON, ADC_SS1_CON_ONE_MSK);
}

/**
  * @brief  One Shot Trigger Mode disable.
  * @param  ADCx ADC Instance.
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_ss1_con_one(ADC_TypeDef *adcx)
{
  CLEAR_BIT(adcx->SS1_CON, ADC_SS1_CON_ONE_MSK);
}

/**
  * @brief  Set ADC SS1 MUX7 ADINx Input Pin.
  * @note   8th Sample Input Select.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss1_mux0_mux7(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS1_MUX0, ADC_SS1_MUX0_MUX7_MSK, AdinPin<<ADC_SS1_MUX0_MUX7_POSS);
}

/**
  * @brief  Get ADC SS1 MUX7 Input ADIN Pin.
  * @param  ADCx ADC Instance
  * @retval Return value can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_mux0_mux7(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_MUX0, ADC_SS1_MUX0_MUX7_MSK)>>ADC_SS1_MUX0_MUX7_POSS);
}

/**
  * @brief  Set ADC SS1 MUX6 Input ADIN Pin.
  * @note   7th Sample Input Select.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss1_mux0_mux6(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS1_MUX0, ADC_SS1_MUX0_MUX6_MSK, AdinPin<<ADC_SS1_MUX0_MUX6_POSS);
}

/**
  * @brief  Get ADC SS1 MUX6 Input ADIN Pin.
  * @param  ADCx ADC Instance
  * @retval Return value can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_mux0_mux6(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_MUX0, ADC_SS1_MUX0_MUX6_MSK)>>ADC_SS1_MUX0_MUX6_POSS);
}

/**
  * @brief  Set ADC SS1 MUX0 MUX5 Input ADIN Pin.
  * @note   6th Sample Input Select.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss1_mux0_mux5(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS1_MUX0, ADC_SS1_MUX0_MUX5_MSK, AdinPin<<ADC_SS1_MUX0_MUX5_POSS);
}

/**
  * @brief  Get ADC SS1 MUX0 MUX5 Input ADIN Pin.
  * @param  ADCx ADC Instance
  * @retval Return value can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_mux0_mux5(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_MUX0, ADC_SS1_MUX0_MUX5_MSK)>>ADC_SS1_MUX0_MUX5_POSS);
}

/**
  * @brief  Set ADC SS1 MUX0 MUX4 Input ADIN Pin.
  * @note   5th Sample Input Select.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss1_mux0_mux4(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS1_MUX0, ADC_SS1_MUX0_MUX4_MSK, AdinPin<<ADC_SS1_MUX0_MUX4_POSS);
}

/**
  * @brief  Get ADC SS1 MUX0 MUX4 Input ADIN Pin.
  * @param  ADCx ADC Instance
  * @retval Return value can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_mux0_mux4(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_MUX0, ADC_SS1_MUX0_MUX4_MSK)>>ADC_SS1_MUX0_MUX4_POSS);
}

/**
  * @brief  Set ADC SS1 MUX0 MUX3 Input ADIN Pin.
  * @note   4th Sample Input Select.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss1_mux0_mux3(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS1_MUX0, ADC_SS1_MUX0_MUX3_MSK, AdinPin<<ADC_SS1_MUX0_MUX3_POSS);
}

/**
  * @brief  Get ADC SS1 MUX0 MUX3 Input ADIN Pin.
  * @param  ADCx ADC Instance
  * @retval Return value can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_mux0_mux3(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_MUX0, ADC_SS1_MUX0_MUX3_MSK)>>ADC_SS1_MUX0_MUX3_POSS);
}

/**
  * @brief  Set ADC SS1 MUX0 MUX2 Input ADIN Pin.
  * @note   3rd Sample Input Select.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss1_mux0_mux2(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS1_MUX0, ADC_SS1_MUX0_MUX2_MSK, AdinPin<<ADC_SS1_MUX0_MUX2_POSS);
}

/**
  * @brief  Get ADC SS1 MUX0 MUX2 Input ADIN Pin.
  * @param  ADCx ADC Instance
  * @retval Return value can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_mux0_mux2(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_MUX0, ADC_SS1_MUX0_MUX2_MSK)>>ADC_SS1_MUX0_MUX2_POSS);
}

/**
  * @brief  Set ADC SS1 MUX0 MUX1 Input ADIN Pin.
  * @note   2nd Sample Input Select.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss1_mux0_mux1(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS1_MUX0, ADC_SS1_MUX0_MUX1_MSK, AdinPin<<ADC_SS1_MUX0_MUX1_POSS);
}

/**
  * @brief  Get ADC SS1 MUX0 MUX1 Input ADIN Pin.
  * @param  ADCx ADC Instance
  * @retval Return value can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_mux0_mux1(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_MUX0, ADC_SS1_MUX0_MUX1_MSK)>>ADC_SS1_MUX0_MUX1_POSS);
}

/**
  * @brief  Set ADC SS1 MUX0 MUX0 Input ADIN Pin.
  * @note   1st Sample Input Select.
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss1_mux0_mux0(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS1_MUX0, ADC_SS1_MUX0_MUX0_MSK, AdinPin<<ADC_SS1_MUX0_MUX0_POSS);
}

/**
  * @brief  Get ADC SS1 MUX0 Input ADIN Pin.
  * @param  ADCx ADC Instance.
  * @retval Return value can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_mux0_mux0(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_MUX0, ADC_SS1_MUX0_MUX0_MSK)>>ADC_SS1_MUX0_MUX0_POSS);
}

/**
  * @brief  Set ADC_SS1_MUX0 register.
  * @note   Set ADC_SS1_MUX0 channels 0~7.
  * @param  ADCx ADC Instance.
  * @param  ADC_SS1_MUX0 register value.
  * @retval None.
  */
__STATIC_INLINE void md_adc_set_ss1_mux0(ADC_TypeDef *ADCx, uint32_t RegValue)
{
  WRITE_REG(ADCx->SS1_MUX0, RegValue);
}

/**
  * @brief  Get ADC_SS1_MUX0 register.
  * @param  ADCx ADC Instance.
  * @retval ADC_SS1_MUX0 register value.
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_mux0(ADC_TypeDef *ADCx)
{
  return READ_REG(ADCx->SS1_MUX0);
}

/**
  * @brief  8th Sample Interrupt Enable.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_enable_ss1_end_ie7(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS1_END, ADC_SS1_END_IE7_MSK);
}

/**
  * @brief  8th Sample Interrupt Disable.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_ss1_end_ie7(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS1_END, ADC_SS1_END_IE7_MSK);
}

/**
  * @brief  Check if 8th Sample Interrupt is enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss1_end_ie7(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_END, ADC_SS1_END_IE7_MSK) == (ADC_SS1_END_IE7_MSK));
}

/**
  * @brief  7th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss1_end_ie6(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS1_END, ADC_SS1_END_IE6_MSK);
}

/**
  * @brief  7th Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss1_end_ie6(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS1_END, ADC_SS1_END_IE6_MSK);
}

/**
  * @brief  Check if 7th Sample Interrupt is enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss1_end_ie6(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_END, ADC_SS1_END_IE6_MSK) == (ADC_SS1_END_IE6_MSK));
}


/**
  * @brief  6th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss10_end_ie5(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS1_END, ADC_SS1_END_IE5_MSK);
}

/**
  * @brief  8th Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss1_end_ie5(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS1_END, ADC_SS1_END_IE5_MSK);
}

/**
  * @brief  Check if 6th Sample Interrupt is enabled.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss1_end_ie5(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_END, ADC_SS1_END_IE5_MSK) == (ADC_SS1_END_IE5_MSK));
}

/**
  * @brief  5th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss1_end_ie4(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS1_END, ADC_SS1_END_IE4_MSK);
}

/**
  * @brief  5th Sample Interrupt Disable.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_disable_ss1_end_ie4(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS1_END, ADC_SS1_END_IE4_MSK);
}

/**
  * @brief  Check if 5th Sample Interrupt is enabled.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss1_end_ie4(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_END, ADC_SS1_END_IE4_MSK) == (ADC_SS1_END_IE4_MSK));
}

/**
  * @brief  4th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss1_end_ie3(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS1_END, ADC_SS1_END_IE3_MSK);
}

/**
  * @brief  8th Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss1_end_ie3(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS1_END, ADC_SS1_END_IE3_MSK);
}

/**
  * @brief  Check if 4th Sample Interrupt is enabled.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss1_end_ie3(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_END, ADC_SS1_END_IE3_MSK) == (ADC_SS1_END_IE3_MSK));
}

/**
  * @brief  3rd Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss1_end_ie2(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS1_END, ADC_SS1_END_IE2_MSK);
}

/**
  * @brief  3rd Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss1_end_ie2(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS1_END, ADC_SS1_END_IE2_MSK);
}

/**
  * @brief  Check if 3rd Sample Interrupt is enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss1_end_ie2(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_END, ADC_SS1_END_IE2_MSK) == (ADC_SS1_END_IE2_MSK));
}

/**
  * @brief  2nd Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss1_end_ie1(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS1_END, ADC_SS1_END_IE1_MSK);
}

/**
  * @brief  2nd Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss1_end_ie1(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS1_END, ADC_SS1_END_IE1_MSK);
}

/**
  * @brief  Check if 2nd Sample Interrupt is enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss1_end_ie1(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_END, ADC_SS1_END_IE1_MSK) == (ADC_SS1_END_IE1_MSK));
}

/**
  * @brief  1st Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss1_end_ie0(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS1_END, ADC_SS1_END_IE0_MSK);
}

/**
  * @brief  1st Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss1_end_ie0(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS1_END, ADC_SS1_END_IE0_MSK);
}

/**
  * @brief  Check if 1st Sample Interrupt is enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss1_end_ie0(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_END, ADC_SS1_END_IE0_MSK) == (ADC_SS1_END_IE0_MSK));
}

/**
  * @brief  Set end sample counts.
  * @note   User can set this register to select how many times will ADC
  *         samples data.
  * @param  ADCx ADC Instance.
  * @param  End Value Min_Value=0x00 Max_Value=0x07.
  * @retval None.
  */
__STATIC_INLINE void md_adc_set_ss1_end_end(ADC_TypeDef *ADCx, uint32_t EndValue)
{
  MODIFY_REG(ADCx->SS1_END, ADC_SS1_END_END_MSK, EndValue<<ADC_SS1_END_END_POSS);
}

/**
  * @brief  Get end sample counts.
  * @param  ADCx ADC Instance
  * @retval End Value Min_Value=0x00 Max_Value=0x07.
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_end_end(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_END, ADC_SS1_END_END_MSK)>>ADC_SS1_END_END_POSS);
}

/**
  * @brief  Set ADC_SS1_END Control Register
  * @param  ADCx ADC Instance.
  * @param  ADC_SS1_END register value.
  * @retval None.
  */
__STATIC_INLINE void md_adc_set_ss1_end(ADC_TypeDef *ADCx, uint32_t RegValue)
{
  MODIFY_REG(ADCx->SS1_END, ADC_SS1_END_END_MSK, RegValue);
}

/**
  * @brief  Get ADC_SS1_End Control Register
  * @param  ADCx ADC Instance.
  * @retval ADC_SS1_END register value.
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_end(ADC_TypeDef *ADCx)
{
  return READ_REG(ADCx->SS1_END);
}

/**
  * @brief  Set ADC Sample Sequencer 1 (SS1) FIFO Overflow status.
  * @note   When the FIFO is full and a write was requested, the
  *         most recent write is dropped.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_set_ss1_fstat_ov(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS1_END, ADC_SS1_FSTAT_OV_MSK);
}

/**
  * @brief  Get ADC Sample Sequencer 1 (SS1) FIFO Overflow status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_fstat_ov(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_FSTAT, ADC_SS1_FSTAT_OV_MSK)>>ADC_SS1_FSTAT_OV_POS);
}

/**
  * @brief  Check if ADC Sample Sequencer 1 (SS1) FIFO Overflow is actived.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ss1_fstat_ov(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_FSTAT, ADC_SS1_FSTAT_OV_MSK) == (ADC_SS1_FSTAT_OV_MSK));
}

/**
  * @brief  Get ADC SS1 FIFO Full status
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_fstat_full(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_FSTAT, ADC_SS1_FSTAT_FULL_MSK)>>ADC_SS1_FSTAT_FULL_POS);
}

/**
  * @brief  Check if ADC SS1 FIFO Full is actived.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ss1_fstat_full(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_FSTAT, ADC_SS1_FSTAT_FULL_MSK) == (ADC_SS1_FSTAT_FULL_MSK));
}

/**
  * @brief  Set ADC Sample Sequencer 1 (SS1) FIFO Underflow status.
  * @note   When the FIFO is empty and a read was requested. 
  *         The problematic read does not move the FIFO pointers, and 0s are returned.
  * @param  ADCx ADC Instance
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss1_fstat_uv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS1_END, ADC_SS1_FSTAT_UV_MSK);
}

/**
  * @brief  Get ADC Sample Sequencer 1 (SS1) FIFO Underflow status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_fstat_uv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_FSTAT, ADC_SS1_FSTAT_UV_MSK)>>ADC_SS1_FSTAT_UV_POS);
}

/**
  * @brief  Check if ADC Sample Sequencer 1 (SS1) FIFO Underflow status is actived.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ss1_fstat_uv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_FSTAT, ADC_SS1_FSTAT_UV_MSK) == (ADC_SS1_FSTAT_UV_MSK));
}

/**
  * @brief  Get ADC SS1 FIFO Empty status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_fstat_empty(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_FSTAT, ADC_SS1_FSTAT_EMPTY_MSK)>>ADC_SS1_FSTAT_EMPTY_POS);
}

/**
  * @brief  Check if ADC SS1 FIFO Empty is actived.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ss1_fstat_empty(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_FSTAT, ADC_SS1_FSTAT_EMPTY_MSK) == (ADC_SS1_FSTAT_EMPTY_MSK));
}

/**
  * @brief  Get ADC SS1 FIFO Head Pointer.
  * @note   The field contains the current head pointer index, which is the
  *         next entry to be written to FIFO.
  * @param  ADCx ADC Instance.
  * @retval Value between Min_Data=0x00 and Max_Data=0x0F
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_fstat_hptr(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_FSTAT, ADC_SS1_FSTAT_HPTR_MSK)>>ADC_SS1_FSTAT_HPTR_POSS);
}

/**
  * @brief  Get ADC SS1 FIFO Tail Pointer.
  * @note   The field contains the current tail pointer index, which is the
  *         next entry to be read from FIFO.
  * @param  ADCx ADC Instance.
  * @retval Value between Min_Data=0x00 and Max_Data=0x0F
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_fstat_tptr(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_FSTAT, ADC_SS1_FSTAT_TPTR_MSK)>>ADC_SS1_FSTAT_TPTR_POSS);
}

/**
  * @brief  Get ADC sample sequencer 1(SS1) Conversion Result Data.
  * @note   User can read conversion result data by reading this register.
  * @param  ADCx ADC Instance.
  * @retval ADC Sampled Data.
  */
__STATIC_INLINE uint32_t md_adc_get_ss1_data(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_REG(ADC->SS1_DATA));
}

/**
  * @brief  Set ADC SS2 Trigger Select.
  * @note   This field selects the trigger source for Sample Sequencer 1.
  * @param  ADCx ADC Instance.
  * @param  This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_CON_SEL_SW
  *         @arg @ref MD_ADC_SS_CON_SEL_BS16T1
  *         @arg @ref MD_ADC_SS_CON_SEL_ALWAYS
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T2
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T3
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T2
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T3
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T4
  *         @arg @ref MD_ADC_SS_CON_SEL_AD16C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GPIO
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP0
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP1
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP2
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP3
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss2_con_sel(ADC_TypeDef *ADCx, uint32_t TrigSource)
{
  MODIFY_REG(ADCx->SS2_CON, ADC_SS2_CON_SEL_MSK, TrigSource<<ADC_SS2_CON_SEL_POSS);
}

/**
  * @brief  Get ADC SS2 Trigger Select.
  * @param  Sample sequencer trigger sources.
  * @param  ADCx ADC Instance.
  * @retval Retrun value can be one of the following values:
  *         @arg @ref MD_ADC_SS_CON_SEL_SW
  *         @arg @ref MD_ADC_SS_CON_SEL_BS16T1
  *         @arg @ref MD_ADC_SS_CON_SEL_ALWAYS
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T2
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T3
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T2
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T3
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T4
  *         @arg @ref MD_ADC_SS_CON_SEL_AD16C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GPIO
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP0
  *         @arg @ref MD_ADC_SS_CCON_SEL_CMP1
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP2
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP3
  */
__STATIC_INLINE uint32_t md_adc_get_ss2_con_sel(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_CON, ADC_SS2_CON_SEL_MSK)>>ADC_SS2_CON_SEL_POSS);
}

/**
  * @brief  ADC Sample Sequencer 2 (SS2) Trigger Type select.
  * @param  ADCx ADC Instance.
  * @param  This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_CON_TYP_EDGE
  *         @arg @ref MD_ADC_SS_COM_TYP_LEVEL
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss2_con_type(ADC_TypeDef *ADCx, uint32_t TrigType)
{
  MODIFY_REG(ADCx->SS2_CON, ADC_SS2_CON_TYP_MSK, TrigType<<ADC_SS2_CON_TYP_POS);
}

/**
  * @brief  Get ADC Sample Sequencer 2 (SS2) Trigger Type.
  * @param  ADCx ADC Instance.
  * @retval Return value can be one of the following values:
  *         @arg @ref MD_ADC_SS_CON_TYP_EDGE
  *         @arg @ref MD_ADC_SS_COM_TYP_LEVEL
  */
__STATIC_INLINE uint32_t md_adc_get_ss2_con_type(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_CON, ADC_SS2_CON_TYP_MSK)>>ADC_SS2_CON_TYP_POS);
}

/**
  * @brief  Set ADC Sample Sequencer 2(SS2) Priority.
  * @note   This field contains a binary-encoded value specifying the
  *         priority encoding of SS2. The prioriteies assigned to the
  *         sequencers must be uniquely mapped.
  * @param  ADCx ADC Instance.
  * @param  This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_CON_PRI_HIGHEST
  *         @arg @ref MD_ADC_SS_CON_PRI_SECOND
  *         @arg @ref MD_ADC_SS_CON_PRI_THIRD
  *         @arg @ref MD_ADC_SS_CON_PRI_LOWEST
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss2_con_pri(ADC_TypeDef *adcx, uint32_t priority)
{
  MODIFY_REG(adcx->SS2_CON, ADC_SS2_CON_PRI_MSK, priority<<ADC_SS2_CON_PRI_POSS);
}

/**
  * @brief  Get ADC Sample Sequencer 2(SS2) Priority.
  * @param  ADCx ADC Instance.
  * @retval  This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS0_CON_PRI_HIGHEST
  *         @arg @ref MD_ADC_SS0_CON_PRI_SECOND
  *         @arg @ref MD_ADC_SS0_CON_PRI_THIRD
  *         @arg @ref MD_ADC_SS0_CON_PRI_LOWEST
  */
__STATIC_INLINE uint32_t md_adc_get_ss2_con_pri(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_CON, ADC_SS2_CON_PRI_MSK)>>ADC_SS2_CON_PRI_POSS);
}

/**
  * @brief  Enable One Shot Trigger Mode.
  * @note   When set HIGH, each trigger will only sample once and use one
  *         slot in FIFO.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss2_con_one(ADC_TypeDef *adcx)
{
  SET_BIT(adcx->SS2_CON, ADC_SS2_CON_ONE_MSK);
}

/**
  * @brief  Disable One Shot Trigger Mode.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss2_con_one(ADC_TypeDef *adcx)
{
  CLEAR_BIT(adcx->SS2_CON, ADC_SS2_CON_ONE_MSK);
}

/**
  * @brief  4th Sample Input Select..
  * @param  ADCx ADC Instance
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss2_mux0_mux3(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS2_MUX0, ADC_SS2_MUX0_MUX3_MSK, AdinPin<<ADC_SS2_MUX0_MUX3_POSS);
}

/**
  * @brief  Get 4th Sample Input.
  * @param  ADCx ADC Instance
  * @retval Return value can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss2_mux0_mux3(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_MUX0, ADC_SS2_MUX0_MUX3_MSK)>>ADC_SS2_MUX0_MUX3_POSS);
}

/**
  * @brief  3rd Sample Input Select.
  * @param  ADCx ADC Instance.
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss2_mux0_mux2(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS2_MUX0, ADC_SS2_MUX0_MUX2_MSK, AdinPin<<ADC_SS2_MUX0_MUX2_POSS);
}

/**
  * @brief  Get 3rd Sample Input Select.
  * @param  ADCx ADC Instance.
  * @retval Return value can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss2_mux0_mux2(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_MUX0, ADC_SS2_MUX0_MUX2_MSK)>>ADC_SS2_MUX0_MUX2_POSS);
}

/**
  * @brief  2nd Sample Input Select.
  * @param  ADCx ADC Instance.
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss2_mux0_mux1(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS2_MUX0, ADC_SS2_MUX0_MUX1_MSK, AdinPin<<ADC_SS2_MUX0_MUX1_POSS);
}

/**
  * @brief  Get 2nd Sample Input Select.
  * @param  ADCx ADC Instance
  * @retval Return value can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss2_mux0_mux1(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_MUX0, ADC_SS2_MUX0_MUX1_MSK)>>ADC_SS2_MUX0_MUX1_POSS);
}

/**
  * @brief  1st Sample Input Select.
  * @param  ADCx ADC Instance.
  * @param  ADIN Pin:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE void md_adc_set_ss2_mux0_mux0(ADC_TypeDef *ADCx, uint32_t AdinPin)
{
  MODIFY_REG(ADCx->SS2_MUX0, ADC_SS2_MUX0_MUX0_MSK, AdinPin<<ADC_SS2_MUX0_MUX0_POSS);
}

/**
  * @brief  Get 1st Sample Input Select.
  * @param  ADCx ADC Instance.
  * @retval Return value can be one of the following values:
  *         @arg @ref MD_ADC_SS_MUX_ADIN15
  *         @arg @ref MD_ADC_SS_MUX_ADIN14
  *         @arg @ref MD_ADC_SS_MUX_ADIN13
  *         @arg @ref MD_ADC_SS_MUX_ADIN12
  *         @arg @ref MD_ADC_SS_MUX_ADIN11
  *         @arg @ref MD_ADC_SS_MUX_ADIN10
  *         @arg @ref MD_ADC_SS_MUX_ADIN9
  *         @arg @ref MD_ADC_SS_MUX_ADIN8
  *         @arg @ref MD_ADC_SS_MUX_ADIN7
  *         @arg @ref MD_ADC_SS_MUX_ADIN6
  *         @arg @ref MD_ADC_SS_MUX_ADIN5
  *         @arg @ref MD_ADC_SS_MUX_ADIN4
  *         @arg @ref MD_ADC_SS_MUX_ADIN3
  *         @arg @ref MD_ADC_SS_MUX_ADIN2
  *         @arg @ref MD_ADC_SS_MUX_ADIN1
  *         @arg @ref MD_ADC_SS_MUX_ADIN0
  */
__STATIC_INLINE uint32_t md_adc_get_ss2_mux0_mux0(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_MUX0, ADC_SS2_MUX0_MUX0_MSK)>>ADC_SS2_MUX0_MUX0_POSS);
}

/**
  * @brief  Set ADC_SS2_MUX0 register value.
  * @param  ADCx ADC Instance.
  * @param  ADC_SS2_MUX0 Register
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss2_mux0(ADC_TypeDef *ADCx, uint32_t RegValue)
{
  WRITE_REG(ADCx->SS2_MUX0, RegValue);
}

/**
  * @brief  Get ADC_SS2_MUX0 register value.
  * @param  ADCx ADC Instance.
  * @retval ADC_SS2_MUX0 Register
  */
__STATIC_INLINE uint32_t md_adc_get_ss2_mux0(ADC_TypeDef *ADCx)
{
  return READ_REG(ADCx->SS2_MUX0);
}

/**
  * @brief  4th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss2_end_ie3(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS2_END, ADC_SS2_END_IE3_MSK);
}

/**
  * @brief  4th Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss2_end_ie3(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS2_END, ADC_SS2_END_IE3_MSK);
}

/**
  * @brief  Check if 4th Sample Interrupt is enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss2_end_ie3(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_END, ADC_SS2_END_IE3_MSK) == (ADC_SS2_END_IE3_MSK));
}

/**
  * @brief  3rd Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss2_end_ie2(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS2_END, ADC_SS2_END_IE2_MSK);
}

/**
  * @brief  3rd Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss2_end_ie2(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS2_END, ADC_SS2_END_IE2_MSK);
}

/**
  * @brief  Check if 3rd Sample Interrupt is enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss2_end_ie2(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_END, ADC_SS2_END_IE2_MSK) == (ADC_SS2_END_IE2_MSK));
}

/**
  * @brief  2nd Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss2_end_ie1(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS1_END, ADC_SS2_END_IE1_MSK);
}

/**
  * @brief  2nd Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss2_end_ie1(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS2_END, ADC_SS2_END_IE1_MSK);
}

/**
  * @brief  Check if 2nd Sample Interrupt Enable is enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss2_end_ie1(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS1_END, ADC_SS2_END_IE1_MSK) == (ADC_SS2_END_IE1_MSK));
}

/**
  * @brief  1st Sample Interrupt Enable
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss2_end_ie0(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS2_END, ADC_SS2_END_IE0_MSK);
}

/**
  * @brief  4th Sample Interrupt Disable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss2_end_ie0(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS2_END, ADC_SS2_END_IE0_MSK);
}

/**
  * @brief  Check if 1st Sample Interrupt is enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss2_end_ie0(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_END, ADC_SS2_END_IE0_MSK) == (ADC_SS2_END_IE0_MSK));
}

/**
  * @brief  Set ADC SS2 END sample.
  * @param  ADCx ADC Instance.
  * @param  End Value Min_Value=0x00 Max_Value=0x03
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss2_end_end(ADC_TypeDef *ADCx, uint32_t EndValue)
{
  MODIFY_REG(ADCx->SS2_END, ADC_SS2_END_END_MSK, EndValue<<ADC_SS2_END_END_POSS);
}

/**
  * @brief  Get ADC SS2 END sample.
  * @param  ADCx ADC Instance.
  * @retval End Value Min_Value=0x00 Max_Value=0x03
  */
__STATIC_INLINE uint32_t md_adc_get_ss2_end_end(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_END, ADC_SS2_END_END_MSK)>>ADC_SS2_END_END_POSS);
}

/**
  * @brief  Set ADC_SS2_End Control Register.
  * @param  ADCx ADC Instance.
  * @param  ADC_SS2_End Register Value.
  * @retval None.
  */
__STATIC_INLINE void md_adc_set_ss2_end(ADC_TypeDef *ADCx, uint32_t RegValue)
{
  MODIFY_REG(ADCx->SS2_END, ADC_SS2_END_END_MSK, RegValue);
}

/**
  * @brief  Get ADC_SS2_End Control Register.
  * @param  ADCx ADC Instance.
  * @retval ADC_SS2_End Register Value.
  */
__STATIC_INLINE uint32_t md_adc_get_ss2_end(ADC_TypeDef *ADCx)
{
  return READ_REG(ADCx->SS2_END);
}

/**
  * @brief  Set ADC Sample Sequencer 2(SS2) FIFO Overflow status.
  * @note   When the FIFO is full and a write was requested, the
  *         most recent write is dropped.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_set_ss2_fstat_ov(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS2_END, ADC_SS2_FSTAT_OV_MSK);
}

/**
  * @brief  Get ADC Sample Sequencer 2(SS2) FIFO Overflow status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_ss2_fstat_ov(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_FSTAT, ADC_SS2_FSTAT_OV_MSK)>>ADC_SS2_FSTAT_OV_POS);
}

/**
  * @brief  Check if ADC Sample Sequencer 2(SS2) FIFO Overflow status is actived.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ss2_fstat_ov(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_FSTAT, ADC_SS2_FSTAT_OV_MSK) == (ADC_SS2_FSTAT_OV_MSK));
}

/**
  * @brief  Get ADC SS2 FIFO Full status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_ss2_fstat_full(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_FSTAT, ADC_SS2_FSTAT_FULL_MSK)>>ADC_SS2_FSTAT_FULL_POS);
}

/**
  * @brief  Check if ADC SS2 FIFO Full is actived.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ss2_fstat_full(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_FSTAT, ADC_SS2_FSTAT_FULL_MSK) == (ADC_SS2_FSTAT_FULL_MSK));
}

/**
  * @brief  Set ADC Sample Sequencer 2(SS2) FIFO Underflow status.
  * @note   When the FIFO is empty and a read was requested. 
  *         The problematic read does not move the FIFO pointers, and 0s are returned.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_set_ss2_fstat_uv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS2_END, ADC_SS2_FSTAT_UV_MSK);
}

/**
  * @brief  Get ADC Sample Sequencer 2(SS2) FIFO Underflow status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_ss2_fstat_uv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_FSTAT, ADC_SS2_FSTAT_UV_MSK)>>ADC_SS2_FSTAT_UV_POS);
}

/**
  * @brief  Check if ADC Sample Sequencer 2(SS2) FIFO Underflow status is actived.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ss2_fstat_uv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_FSTAT, ADC_SS2_FSTAT_UV_MSK) == (ADC_SS2_FSTAT_UV_MSK));
}

/**
  * @brief  Get ADC SS2 FIFO Empty status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_ss2_fstat_empty(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_FSTAT, ADC_SS2_FSTAT_EMPTY_MSK)>>ADC_SS2_FSTAT_EMPTY_POS);
}

/**
  * @brief  Check if ADC SS2 FIFO Empty is actived.
  * @param  ADCx ADC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ss2_fstat_empty(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_FSTAT, ADC_SS2_FSTAT_EMPTY_MSK) == (ADC_SS2_FSTAT_EMPTY_MSK));
}

/**
  * @brief  Get ADC SS2 FIFO Head Pointer.
  * @param  ADCx ADC Instance.
  * @retval Return value between Min_Data=0x00 and Max_Data=0x0F.
  */
__STATIC_INLINE uint32_t md_adc_get_ss2_fstat_hptr(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_FSTAT, ADC_SS2_FSTAT_HPTR_MSK)>>ADC_SS2_FSTAT_HPTR_POSS);
}

/**
  * @brief  Get ADC SS2 FSTAT TPTR
  * @param  ADCx ADC Instance
  * @retval Return value between Min_Data=0x00 and Max_Data=0x0F.
  */
__STATIC_INLINE uint32_t md_adc_get_ss2_fstat_tptr(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS2_FSTAT, ADC_SS2_FSTAT_TPTR_MSK)>>ADC_SS2_FSTAT_TPTR_POSS);
}

/**
  * @brief  Get ADC sample sequencer 2(SS2) Conversion Result Data.
  * @note   User can read conversion result data by reading this register.
  * @param  ADCx ADC Instance.
  * @retval ADC Sampled Data.
  */
__STATIC_INLINE uint32_t md_adc_get_ss2_data(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_REG(ADC->SS2_DATA));
}

/**
  * @brief  Set SS3 Trigger Select.
  * @note   This field selects the trigger source for Sample Sequencer 3.
  * @param  ADCx ADC Instance.
  * @param  This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_CON_SEL_SW
  *         @arg @ref MD_ADC_SS_CON_SEL_BS16T1
  *         @arg @ref MD_ADC_SS_CON_SEL_ALWAYS
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T2
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T3
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T2
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T3
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T4
  *         @arg @ref MD_ADC_SS_CON_SEL_AD16C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GPIO
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP0
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP1
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP2
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP3
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss3_con_sel(ADC_TypeDef *ADCx, uint32_t TrigSource)
{
  MODIFY_REG(ADCx->SS3_CON, ADC_SS3_CON_SEL_MSK, TrigSource<<ADC_SS3_CON_SEL_POSS);
}

/**
  * @brief  Get SS3 Trigger Select.
  * @param  ADCx ADC Instance.
  * @retval This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_CON_SEL_SW
  *         @arg @ref MD_ADC_SS_CON_SEL_BS16T1
  *         @arg @ref MD_ADC_SS_CON_SEL_ALWAYS
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T2
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C4T3
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T2
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T3
  *         @arg @ref MD_ADC_SS_CON_SEL_GP32C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GP16C2T4
  *         @arg @ref MD_ADC_SS_CON_SEL_AD16C4T1
  *         @arg @ref MD_ADC_SS_CON_SEL_GPIO
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP0
  *         @arg @ref MD_ADC_SS_CCON_SEL_CMP1
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP2
  *         @arg @ref MD_ADC_SS_CON_SEL_CMP3
  */
__STATIC_INLINE uint32_t md_adc_get_ss3_con_sel(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS3_CON, ADC_SS3_CON_SEL_MSK)>>ADC_SS3_CON_SEL_POSS);
}

/**
  * @brief  ADC Sample Sequencer 2 (SS2) Trigger Type select.
  * @param  ADCx ADC Instance.
  * @param  This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_CON_TYP_EDGE
  *         @arg @ref MD_ADC_SS_COM_TYP_LEVEL
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss3_con_type(ADC_TypeDef *ADCx, uint32_t TrigType)
{
  MODIFY_REG(ADCx->SS3_CON, ADC_SS3_CON_TYP_MSK, TrigType<<ADC_SS3_CON_TYP_POS);
}

/**
  * @brief  Get ADC Sample Sequencer 2 (SS2) Trigger Type.
  * @param  ADCx ADC Instance.
  * @retval  his parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_CON_TYP_EDGE
  *         @arg @ref MD_ADC_SS_COM_TYP_LEVEL
  */
__STATIC_INLINE uint32_t md_adc_get_ss3_con_type(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS3_CON, ADC_SS3_CON_TYP_MSK)>>ADC_SS3_CON_TYP_POS);
}

/**
  * @brief  Set ADC Sample Sequencer 3(SS3) Priority.
  * @note   This field contains a binary-encoded value specifying the
  *         priority encoding of SS2. The prioriteies assigned to the
  *         sequencers must be uniquely mapped.
  * @param  ADCx ADC Instance.
  * @param  This parameter can be one of the following values:
  *         @arg @ref MD_ADC_SS_CON_PRI_HIGHEST
  *         @arg @ref MD_ADC_SS_CON_PRI_SECOND
  *         @arg @ref MD_ADC_SS_CON_PRI_THIRD
  *         @arg @ref MD_ADC_SS_CON_PRI_LOWEST
  * @retval None
  */
__STATIC_INLINE void md_adc_set_ss3_con_pri(ADC_TypeDef *adcx, uint32_t priority)
{
  MODIFY_REG(adcx->SS3_CON, ADC_SS3_CON_PRI_MSK, priority<<ADC_SS3_CON_PRI_POSS);
}

/**
  * @brief  Get ADC Sample Sequencer 3(SS3) Priority.
  * @param  ADCx ADC Instance.
  * @retval Return value can be one of the following values:
  *         @arg @ref MD_ADC_SS0_CON_PRI_HIGHEST
  *         @arg @ref MD_ADC_SS0_CON_PRI_SECOND
  *         @arg @ref MD_ADC_SS0_CON_PRI_THIRD
  *         @arg @ref MD_ADC_SS0_CON_PRI_LOWEST
  */
__STATIC_INLINE uint32_t md_adc_get_ss3_con_pri(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS3_CON, ADC_SS3_CON_PRI_MSK)>>ADC_SS3_CON_PRI_POSS);
}

/**
  * @brief  Enable ADC sample sequencer 3(SS3) one shot mode.
  * @note   When set HIGH, each trigger will only sample once and use one
  *         slot in FIFO.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss3_con_one(ADC_TypeDef *adcx)
{
  SET_BIT(adcx->SS3_CON, ADC_SS3_CON_ONE_MSK);
}

/**
  * @brief  Disable ADC sample sequencer 3(SS3) one shot mode.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss3_con_one(ADC_TypeDef *adcx)
{
  CLEAR_BIT(adcx->SS3_CON, ADC_SS3_CON_ONE_MSK);
}

/**
  * @brief  Enable ADC SS3 1th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_enable_ss3_end_ie0(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS3_END, ADC_SS3_END_IE0_MSK);
}

/**
  * @brief  Disable ADC SS3 1th Sample Interrupt Enable.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_disable_ss3_end_ie0(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->SS3_END, ADC_SS3_END_IE0_MSK);
}

/**
  * @brief  Check if ADC SS3 1th Sample Interrupt is enabled.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_enabled_ss3_end_ie0(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS3_END, ADC_SS3_END_IE0_MSK) == (ADC_SS3_END_IE0_MSK));
}

/**
  * @brief  Set ADC SS3 END sample.
  * @param  ADCx ADC Instance.
  * @param  End Value Min_Value=0x00 Max_Value=0x01.
  * @retval None.
  */
__STATIC_INLINE void md_adc_set_ss3_end_end(ADC_TypeDef *ADCx, uint32_t EndValue)
{
  MODIFY_REG(ADCx->SS3_END, ADC_SS3_END_END_MSK, EndValue<<ADC_SS3_END_END_POS);
}

/**
  * @brief  Get ADC SS3 END sample.
  * @param  ADCx ADC Instance.
  * @retval End Value Min_Value=0x00 Max_Value=0x01
  */
__STATIC_INLINE uint32_t md_adc_get_ss3_end_end(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS3_END, ADC_SS3_END_END_MSK)>>ADC_SS3_END_END_POS);
}

/**
  * @brief  Set ADC_SS3_End Control Register.
  * @param  ADCx ADC Instance.
  * @param  ADC_SS3_END Register Value.
  * @retval None.
  */
__STATIC_INLINE void md_adc_set_ss3_end(ADC_TypeDef *ADCx, uint32_t RegValue)
{
  MODIFY_REG(ADCx->SS2_END, ADC_SS3_END_END_MSK, RegValue);
}

/**
  * @brief  Get ADC_SS3_End Control Register
  * @param  ADCx ADC Instance.
  * @retval ADC_SS3_End Register Value.
  */
__STATIC_INLINE uint32_t md_adc_get_ss3_end(ADC_TypeDef *ADCx)
{
  return READ_REG(ADCx->SS3_END);
}

/**
  * @brief  Set ADC Sample Sequencer 3 (SS3) FIFO Overflow status.
  * @note   When the FIFO is full and a write was requested, the
  *         most recent write is dropped.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_set_ss3_fstat_ov(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS3_END, ADC_SS3_FSTAT_OV_MSK);
}

/**
  * @brief  Get ADC Sample Sequencer 3 (SS3) FIFO Overflow status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_ss3_fstat_ov(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS3_FSTAT, ADC_SS3_FSTAT_OV_MSK)>>ADC_SS3_FSTAT_OV_POS);
}

/**
  * @brief  Check if ADC Sample Sequencer 3 (SS3) FIFO Overflow status is actived.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ss3_fstat_ov(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS3_FSTAT, ADC_SS3_FSTAT_OV_MSK) == (ADC_SS3_FSTAT_OV_MSK));
}

/**
  * @brief  Get ADC SS3 FIFO Full status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_ss3_fstat_full(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS3_FSTAT, ADC_SS3_FSTAT_FULL_MSK)>>ADC_SS3_FSTAT_FULL_POS);
}

/**
  * @brief  Check if ADC SS3 FIFO Full status is actived.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ss3_fstat_full(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS3_FSTAT, ADC_SS3_FSTAT_FULL_MSK) == (ADC_SS3_FSTAT_FULL_MSK));
}

/**
  * @brief  Set ADC Sample Sequencer 3 (SS3) FIFO Underflow status.
  * @note   When the FIFO is empty and a read was requested. 
  *         The problematic read does not move the FIFO pointers, and 0s are returned.
  * @param  ADCx ADC Instance.
  * @retval None.
  */
__STATIC_INLINE void md_adc_set_ss3_fstat_uv(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->SS3_END, ADC_SS3_FSTAT_UV_MSK);
}

/**
  * @brief  Get ADC Sample Sequencer 3 (SS3) FIFO Underflow status.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_ss3_fstat_uv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS3_FSTAT, ADC_SS3_FSTAT_UV_MSK)>>ADC_SS3_FSTAT_UV_POS);
}

/**
  * @brief  Check if ADC Sample Sequencer 3 (SS3) FIFO Underflow status is actived.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ss3_fstat_uv(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS3_FSTAT, ADC_SS3_FSTAT_UV_MSK) == (ADC_SS3_FSTAT_UV_MSK));
}

/**
  * @brief  Get ADC SS3 FIFO Empty.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_get_ss3_fstat_empty(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS3_FSTAT, ADC_SS3_FSTAT_EMPTY_MSK)>>ADC_SS3_FSTAT_EMPTY_POS);
}

/**
  * @brief  Check if ADC SS3 FIFO Empty is actived.
  * @param  ADCx ADC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t md_adc_is_active_flag_ss3_fstat_empty(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS3_FSTAT, ADC_SS3_FSTAT_EMPTY_MSK) == (ADC_SS3_FSTAT_EMPTY_MSK));
}

/**
  * @brief  Get ADC SS3 FIFO Head Pointer.
  * @param  ADCx ADC Instance.
  * @retval Value between Min_Data=0x00 and Max_Data=0x01.
  */
__STATIC_INLINE uint32_t md_adc_get_ss23_fstat_hptr(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS3_FSTAT, ADC_SS3_FSTAT_HPTR_MSK)>>ADC_SS3_FSTAT_HPTR_POSS);
}

/**
  * @brief  Get ADC SS3 FIFO Tail Pointer.
  * @param  ADCx ADC Instance.
  * @retval Value between Min_Data=0x00 and Max_Data=0x01.
  */
__STATIC_INLINE uint32_t md_adc_get_ss3_fstat_tptr(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->SS3_FSTAT, ADC_SS3_FSTAT_TPTR_MSK)>>ADC_SS3_FSTAT_TPTR_POSS);
}

/**
  * @brief  Get ADC sample sequencer 3(SS3) Conversion Result Data.
  * @note   User can read conversion result data by reading this register.
  * @param  ADCx ADC Instance.
  * @retval ADC Sampled Data.
  */
__STATIC_INLINE uint32_t md_adc_get_ss3_data(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_REG(ADC->SS3_DATA));
}

/** @defgroup MD_ADC_PM_WRITE_READ Common Write and read registers Macros
  * @}
  */
#endif

void md_adc_init(ADC_TypeDef *ADCx, md_adc_inittypedef *ADC_InitStruct,uint8_t *);
void md_adc_calibration_data(double, double ,double * ,double *);
void md_adc_get_data(uint8_t, double, double, uint16_t *);
/**
  * @} MD_ADC_Public_Macros
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
