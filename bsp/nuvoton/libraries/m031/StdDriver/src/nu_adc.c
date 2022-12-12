/**************************************************************************//**
 * @file     adc.c
 * @version  V3.00
 * $Revision: 7 $
 * $Date: 18/07/24 2:17p $
 * @brief    M031 Series ADC Driver Source File
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "M031Series.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup ADC_Driver ADC Driver
  @{
*/

/** @addtogroup ADC_EXPORTED_FUNCTIONS ADC Exported Functions
  @{
*/

/**
  * @brief This API configures ADC module to be ready for convert the input from selected channel
  * @param[in] adc The pointer of the specified ADC module
  * @param[in] u32InputMode Decides the ADC analog input mode. Valid values are:
  *                          - \ref ADC_ADCR_DIFFEN_SINGLE_END      :Single-end input mode
  *                          - \ref ADC_ADCR_DIFFEN_DIFFERENTIAL    :Differential input mode
  * @param[in] u32OpMode Decides the ADC operation mode. Valid values are:
  *                       - \ref ADC_ADCR_ADMD_SINGLE               :Single mode.
  *                       - \ref ADC_ADCR_ADMD_BURST                :Burst mode.
  *                       - \ref ADC_ADCR_ADMD_SINGLE_CYCLE         :Single cycle scan mode.
  *                       - \ref ADC_ADCR_ADMD_CONTINUOUS           :Continuous scan mode.
  * @param[in] u32ChMask Channel enable bit. Each bit corresponds to a input channel. Bit 0 is channel 0, bit 1 is channel 1..., bit 15 is channel 15.
  * @return  None
  * @note M031 series MCU ADC can only convert 1 channel at a time. If more than 1 channels are enabled, only channel
  *       with smallest number will be convert.
  * @note This API does not turn on ADC power nor does trigger ADC conversion.
  * @note This API will reset and calibrate ADC if ADC never be calibrated after chip power on.
  */
void ADC_Open(ADC_T *adc,
              uint32_t u32InputMode,
              uint32_t u32OpMode,
              uint32_t u32ChMask)
{
    /* Do calibration for ADC to decrease the effect of electrical random noise. */
    if ((adc->ADCALSTSR & ADC_ADCALSTSR_CALIF_Msk) == 0)
    {
        /* Must reset ADC before ADC calibration */
        adc->ADCR |= ADC_ADCR_RESET_Msk;
        while((adc->ADCR & ADC_ADCR_RESET_Msk) == ADC_ADCR_RESET_Msk);

        adc->ADCALSTSR |= ADC_ADCALSTSR_CALIF_Msk;  /* Clear Calibration Finish Interrupt Flag */
        adc->ADCALR |= ADC_ADCALR_CALEN_Msk;        /* Enable Calibration function */
        ADC_START_CONV(adc);                        /* Start to calibration */
        while((adc->ADCALSTSR & ADC_ADCALSTSR_CALIF_Msk) != ADC_ADCALSTSR_CALIF_Msk);   /* Wait calibration finish */
    }

    adc->ADCR = (adc->ADCR & (~(ADC_ADCR_DIFFEN_Msk | ADC_ADCR_ADMD_Msk))) | \
                (u32InputMode) | \
                (u32OpMode);

    adc->ADCHER = (adc->ADCHER & ~ADC_ADCHER_CHEN_Msk) | (u32ChMask);

    return;
}

/**
  * @brief Disable ADC module
  * @param[in] adc The pointer of the specified ADC module
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
  * @param[in] adc The pointer of the specified ADC module
  * @param[in] u32Source Decides the hardware trigger source. Valid values are:
  *                       - \ref ADC_ADCR_TRGS_STADC            :A/D conversion is started by external STADC pin.
  *                       - \ref ADC_ADCR_TRGS_TIMER            :A/D conversion is started by Timer.
  *                       - \ref ADC_ADCR_TRGS_PWM              :A/D conversion is started by PWM.
  * @param[in] u32Param While ADC trigger by PWM or Timer, this parameter is unused.
  *                     While ADC trigger by external pin, this parameter is used to set trigger condition.
  *                     Valid values are:
  *                      - \ref ADC_ADCR_TRGCOND_LOW_LEVEL     :STADC Low level active
  *                      - \ref ADC_ADCR_TRGCOND_HIGH_LEVEL    :STADC High level active
  *                      - \ref ADC_ADCR_TRGCOND_FALLING_EDGE  :STADC Falling edge active
  *                      - \ref ADC_ADCR_TRGCOND_RISING_EDGE   :STADC Rising edge active
  * @return None
  * @note Software should disable TRGEN (ADCR[8]) and ADST (ADCR[11]) before change TRGS(ADCR[5:4]).
  */
void ADC_EnableHWTrigger(ADC_T *adc,
                         uint32_t u32Source,
                         uint32_t u32Param)
{
    if(u32Source == ADC_ADCR_TRGS_STADC)
    {
        adc->ADCR = (adc->ADCR & ~(ADC_ADCR_TRGS_Msk | ADC_ADCR_TRGCOND_Msk | ADC_ADCR_TRGEN_Msk)) |
                    ((u32Source) | (u32Param) | ADC_ADCR_TRGEN_Msk);
    }
    else if(u32Source == ADC_ADCR_TRGS_TIMER)
    {
        adc->ADCR = (adc->ADCR & ~(ADC_ADCR_TRGS_Msk | ADC_ADCR_TRGCOND_Msk | ADC_ADCR_TRGEN_Msk)) |
                    ((u32Source) | ADC_ADCR_TRGEN_Msk);
    }
    else
    {
        adc->ADCR = (adc->ADCR & ~(ADC_ADCR_TRGS_Msk | ADC_ADCR_TRGCOND_Msk | ADC_ADCR_TRGEN_Msk)) |
                    ((u32Source) | ADC_ADCR_TRGEN_Msk);
    }
    return;
}

/**
  * @brief Disable hardware trigger ADC function.
  * @param[in] adc The pointer of the specified ADC module
  * @return None
  */
void ADC_DisableHWTrigger(ADC_T *adc)
{
    adc->ADCR &= ~(ADC_ADCR_TRGS_Msk | ADC_ADCR_TRGCOND_Msk | ADC_ADCR_TRGEN_Msk);
    return;
}

/**
  * @brief Enable the interrupt(s) selected by u32Mask parameter.
  * @param[in] adc The pointer of the specified ADC module
  * @param[in] u32Mask The combination of interrupt status bits listed below. Each bit
  *                    corresponds to a interrupt status. This parameter decides which
  *                    interrupts will be enabled.
  *                     - \ref ADC_ADF_INT    :ADC convert complete interrupt
  *                     - \ref ADC_CMP0_INT   :ADC comparator 0 interrupt
  *                     - \ref ADC_CMP1_INT   :ADC comparator 1 interrupt
  * @return None
  */
void ADC_EnableInt(ADC_T *adc, uint32_t u32Mask)
{
    if((u32Mask) & ADC_ADF_INT)
        adc->ADCR |= ADC_ADCR_ADIE_Msk;
    if((u32Mask) & ADC_CMP0_INT)
        adc->ADCMPR[0] |= ADC_ADCMPR_CMPIE_Msk;
    if((u32Mask) & ADC_CMP1_INT)
        adc->ADCMPR[1] |= ADC_ADCMPR_CMPIE_Msk;

    return;
}

/**
  * @brief Disable the interrupt(s) selected by u32Mask parameter.
  * @param[in] adc The pointer of the specified ADC module
  * @param[in] u32Mask The combination of interrupt status bits listed below. Each bit
  *                    corresponds to a interrupt status. This parameter decides which
  *                    interrupts will be disabled.
  *                     - \ref ADC_ADF_INT     :ADC convert complete interrupt
  *                     - \ref ADC_CMP0_INT    :ADC comparator 0 interrupt
  *                     - \ref ADC_CMP1_INT    :ADC comparator 1 interrupt
  * @return None
  */
void ADC_DisableInt(ADC_T *adc, uint32_t u32Mask)
{
    if((u32Mask) & ADC_ADF_INT)
        adc->ADCR &= ~ADC_ADCR_ADIE_Msk;
    if((u32Mask) & ADC_CMP0_INT)
        adc->ADCMPR[0] &= ~ADC_ADCMPR_CMPIE_Msk;
    if((u32Mask) & ADC_CMP1_INT)
        adc->ADCMPR[1] &= ~ADC_ADCMPR_CMPIE_Msk;

    return;
}

/**
  * @brief Set ADC extend sample time.
  * @param[in] adc The pointer of the specified ADC module.
  * @param[in] u32ModuleNum Decides the sample module number, valid value are 0.
  * @param[in] u32ExtendSampleTime Decides the extend sampling time, the range is from 0~255 ADC clock. Valid value are from 0 to 0xFF.
  * @return None
  * @details When A/D converting at high conversion rate, the sampling time of analog input voltage may not enough if input channel loading is heavy,
  *         user can extend A/D sampling time after trigger source is coming to get enough sampling time.
  */
void ADC_SetExtendSampleTime(ADC_T *adc, uint32_t u32ModuleNum, uint32_t u32ExtendSampleTime)
{
    adc->ESMPCTL = (adc->ESMPCTL & ~ADC_ESMPCTL_EXTSMPT_Msk) |
                   (u32ExtendSampleTime << ADC_ESMPCTL_EXTSMPT_Pos);
}

/*@}*/ /* end of group ADC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group ADC_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
