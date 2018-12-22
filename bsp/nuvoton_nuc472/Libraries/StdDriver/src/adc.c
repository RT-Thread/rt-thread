/**************************************************************************//**
 * @file     adc.c
 * @version  V1.00
 * $Revision: 13 $
 * $Date: 14/05/29 1:13p $
 * @brief    NUC472/NUC442 ADC driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NUC472_442.h"

/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_ADC_Driver ADC Driver
  @{
*/


/** @addtogroup NUC472_442_ADC_EXPORTED_FUNCTIONS ADC Exported Functions
  @{
*/

/**
  * @brief This API configures ADC module to be ready for convert the input from selected channel
  * @param[in] adc Base address of ADC module
  * @param[in] u32InputMode Input mode (single-end/differential). Valid values are:
  *                 - \ref ADC_INPUT_MODE_SINGLE_END
  *                 - \ref ADC_INPUT_MODE_DIFFERENTIAL
  * @param[in] u32OpMode Operation mode (single/single cycle/continuous). Valid values are:
  *                 - \ref ADC_OPERATION_MODE_SINGLE
  *                 - \ref ADC_OPERATION_MODE_SINGLE_CYCLE
  *                 - \ref ADC_OPERATION_MODE_CONTINUOUS
  * @param[in] u32ChMask Channel enable bit. Valid values are:
  *                 - \ref ADC_CH_0_MASK
  *                 - \ref ADC_CH_1_MASK
  *                 - \ref ADC_CH_2_MASK
  *                 - \ref ADC_CH_3_MASK
  *                 - \ref ADC_CH_4_MASK
  *                 - \ref ADC_CH_5_MASK
  *                 - \ref ADC_CH_6_MASK
  *                 - \ref ADC_CH_7_MASK
  *                 - \ref ADC_CH_8_MASK
  *                 - \ref ADC_CH_9_MASK
  *                 - \ref ADC_CH_10_MASK
  *                 - \ref ADC_CH_11_MASK
  *                 - \ref ADC_CH_TS_MASK
  *                 - \ref ADC_CH_BG_MASK
  * @return  None
  * @note This API does not turn on ADC power nor does trigger ADC conversion
  */
void ADC_Open(ADC_T *adc,
              uint32_t u32InputMode,
              uint32_t u32OpMode,
              uint32_t u32ChMask)
{

    ADC->CTL |= u32InputMode;
    ADC->CTL |= u32OpMode;
    ADC->CHEN  = (ADC->CHEN & ~(ADC_CHEN_CHEN_Msk | ADC_CHEN_ADBGEN_Msk | ADC_CHEN_ADTSEN_Msk)) | u32ChMask;
    return;
}

/**
  * @brief Disable ADC module
  * @param[in] adc Base address of ADC module
  * @return None
  */
void ADC_Close(ADC_T *adc)
{
    SYS->IPRST1 |= SYS_IPRST1_ADCRST_Msk;
    SYS->IPRST1 &= ~SYS_IPRST1_ADCRST_Msk;
    return;

}

/**
  * @brief Configure the hardware trigger condition and enable hardware trigger
  * @param[in] adc Base address of ADC module
  * @param[in] u32Source Decides the hardware trigger source. Valid values are:
  *                 - \ref ADC_TRIGGER_BY_EXT_PIN
  *                 - \ref ADC_TRIGGER_BY_PWM
  * @param[in] u32Param While ADC trigger by PWM, this parameter is used to set the delay between PWM
  *                     trigger and ADC conversion. Valid values are from 0 ~ 0xFF, and actual delay
  *                     time is (4 * u32Param * HCLK). While ADC trigger by external pin, this parameter
  *                     is used to set trigger condition. Valid values are:
  *                 - \ref ADC_LOW_LEVEL_TRIGGER
  *                 - \ref ADC_HIGH_LEVEL_TRIGGER
  *                 - \ref ADC_FALLING_EDGE_TRIGGER
  *                 - \ref ADC_RISING_EDGE_TRIGGER
  * @return None
  */
void ADC_EnableHWTrigger(ADC_T *adc,
                         uint32_t u32Source,
                         uint32_t u32Param)
{
    ADC->CTL &= ~(ADC_TRIGGER_BY_PWM | ADC_RISING_EDGE_TRIGGER | ADC_CTL_HWTRGEN_Msk);
    if(u32Source == ADC_TRIGGER_BY_EXT_PIN) {
        ADC->CTL &= ~(ADC_CTL_HWTRGSEL_Msk | ADC_CTL_HWTRGCOND_Msk);
        ADC->CTL |= u32Source | u32Param | ADC_CTL_HWTRGEN_Msk;
    } else {
        ADC->CTL &= ~(ADC_CTL_HWTRGSEL_Msk | ADC_CTL_PWMTRGDLY_Msk);
        ADC->CTL |= u32Source | (u32Param << ADC_CTL_PWMTRGDLY_Pos) | ADC_CTL_HWTRGEN_Msk;
    }

    return;
}

/**
  * @brief Disable hardware trigger ADC function.
  * @param[in] adc Base address of ADC module
  * @return None
  */
void ADC_DisableHWTrigger(ADC_T *adc)
{
    ADC->CTL &= ~(ADC_TRIGGER_BY_PWM | ADC_RISING_EDGE_TRIGGER | ADC_CTL_HWTRGEN_Msk);
    return;
}

/**
  * @brief Enable the interrupt(s) selected by u32Mask parameter.
  * @param[in] adc Base address of ADC module
  * @param[in] u32Mask  The combination of interrupt status bits listed below. Each bit
  *                     corresponds to a interrupt status. This parameter decides which
  *                     interrupts will be enabled.
  *                     - \ref ADC_ADF_INT
  *                     - \ref ADC_CMP0_INT
  *                     - \ref ADC_CMP1_INT
  * @return None
  */
void ADC_EnableInt(ADC_T *adc, uint32_t u32Mask)
{
    if(u32Mask & ADC_ADF_INT)
        ADC->CTL |= ADC_CTL_ADCIEN_Msk;
    if(u32Mask & ADC_CMP0_INT)
        ADC->CMP[0] |= ADC_CMP0_ADCMPIE_Msk;
    if(u32Mask & ADC_CMP1_INT)
        ADC->CMP[1] |= ADC_CMP1_ADCMPIE_Msk;

    return;
}

/**
  * @brief Disable the interrupt(s) selected by u32Mask parameter.
  * @param[in] adc Base address of ADC module
  * @param[in] u32Mask  The combination of interrupt status bits listed below. Each bit
  *                     corresponds to a interrupt status. This parameter decides which
  *                     interrupts will be disabled.
  *                     - \ref ADC_ADF_INT
  *                     - \ref ADC_CMP0_INT
  *                     - \ref ADC_CMP1_INT
  * @return None
  */
void ADC_DisableInt(ADC_T *adc, uint32_t u32Mask)
{
    if(u32Mask & ADC_ADF_INT)
        ADC->CTL &= ~ADC_CTL_ADCIEN_Msk;
    if(u32Mask & ADC_CMP0_INT)
        ADC->CMP[0] &= ~ADC_CMP0_ADCMPIE_Msk;
    if(u32Mask & ADC_CMP1_INT)
        ADC->CMP[1] &= ~ADC_CMP1_ADCMPIE_Msk;

    return;
}



/*@}*/ /* end of group NUC472_442_ADC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_ADC_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
