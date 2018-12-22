/**************************************************************************//**
 * @file     adc.h
 * @version  V3.0
 * $Revision: 10 $
 * $Date: 14/02/10 2:27p $
 * @brief    M051 series ADC driver header file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup M051_Device_Driver M051 Device Driver
  @{
*/

/** @addtogroup M051_ADC_Driver ADC Driver
  @{
*/

/** @addtogroup M051_ADC_EXPORTED_CONSTANTS ADC Exported Constants
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/*  ADCR Constant Definitions                                                                              */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_ADCR_ADEN_CONVERTER_DISABLE   (0UL<<ADC_ADCR_ADEN_Pos)     /*!< ADC converter disable          */
#define ADC_ADCR_ADEN_CONVERTER_ENABLE    (1UL<<ADC_ADCR_ADEN_Pos)     /*!< ADC converter enable           */

#define ADC_ADCR_ADMD_SINGLE            (0UL<<ADC_ADCR_ADMD_Pos)     /*!< Single mode                */
#define ADC_ADCR_ADMD_BURST             (1UL<<ADC_ADCR_ADMD_Pos)     /*!< Burst mode                 */
#define ADC_ADCR_ADMD_SINGLE_CYCLE      (2UL<<ADC_ADCR_ADMD_Pos)     /*!< Single cycle scan mode     */
#define ADC_ADCR_ADMD_CONTINUOUS        (3UL<<ADC_ADCR_ADMD_Pos)     /*!< Continuous scan mode       */

#define ADC_ADCR_DIFFEN_SINGLE_END      (0UL<<ADC_ADCR_DIFFEN_Pos)   /*!< Single end input mode      */
#define ADC_ADCR_DIFFEN_DIFFERENTIAL    (1UL<<ADC_ADCR_DIFFEN_Pos)   /*!< Differential input type    */

#define ADC_ADCR_DMOF_UNSIGNED_OUTPUT   (0UL<<ADC_ADCR_DMOF_Pos)     /*!< Select the straight binary format as the output format of the conversion result   */
#define ADC_ADCR_DMOF_TWOS_COMPLEMENT   (1UL<<ADC_ADCR_DMOF_Pos)     /*!< Select the 2's complement format as the output format of the conversion result    */

#define ADC_ADCR_TRGEN_DISABLE          (0UL<<ADC_ADCR_TRGEN_Pos)    /*!< Disable triggering of A/D conversion by external STADC pin or PWM   */
#define ADC_ADCR_TRGEN_ENABLE           (1UL<<ADC_ADCR_TRGEN_Pos)    /*!< Enable triggering of A/D conversion by external STADC pin or PWM  */

#define ADC_ADCR_TRGS_STADC             (0UL<<ADC_ADCR_TRGS_Pos)     /*!< A/D conversion is started by external STADC pin */
#define ADC_ADCR_TRGS_PWM               (3UL<<ADC_ADCR_TRGS_Pos)     /*!< A/D conversion is started by PWM */

#define ADC_ADCR_TRGCOND_LOW_LEVEL      (0UL<<ADC_ADCR_TRGCOND_Pos)  /*!< STADC Low level active     */
#define ADC_ADCR_TRGCOND_HIGH_LEVEL     (1UL<<ADC_ADCR_TRGCOND_Pos)  /*!< STADC High level active    */
#define ADC_ADCR_TRGCOND_FALLING_EDGE   (2UL<<ADC_ADCR_TRGCOND_Pos)  /*!< STADC Falling edge active  */
#define ADC_ADCR_TRGCOND_RISING_EDGE    (3UL<<ADC_ADCR_TRGCOND_Pos)  /*!< STADC Rising edge active   */

/*---------------------------------------------------------------------------------------------------------*/
/* ADCHER Constant Definitions                                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_ADCHER_PRESEL_EXT_INPUT_SIGNAL         (0UL<<ADC_ADCHER_PRESEL_Pos)    /*!< The input source of channel 7 is the external analog input                   */
#define ADC_ADCHER_PRESEL_INT_BANDGAP              (1UL<<ADC_ADCHER_PRESEL_Pos)    /*!< The input source of channel 7 is the internal bandgap voltage                */
#define ADC_ADCHER_PRESEL_INT_TEMPERATURE_SENSOR   (2UL<<ADC_ADCHER_PRESEL_Pos)    /*!< The input source of channel 7 is the output of internal temperature sensor   */

/*---------------------------------------------------------------------------------------------------------*/
/* ADCMPR Constant Definitions                                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_ADCMPR_CMPD(x)                    ((x) << ADC_ADCMPR_CMPD_Pos)          /*!< Compare value for compare function            */
#define ADC_ADCMPR_CMPMATCNT(x)               (((x)-1) << ADC_ADCMPR_CMPMATCNT_Pos) /*!< Match count for compare function              */
#define ADC_ADCMPR_CMPCH(x)                   ((x) << ADC_ADCMPR_CMPCH_Pos)         /*!< Compare channel for compare function          */
#define ADC_ADCMPR_CMPCOND_LESS_THAN          (0<<ADC_ADCMPR_CMPCOND_Pos)           /*!< The compare condition is "less than"          */
#define ADC_ADCMPR_CMPCOND_GREATER_OR_EQUAL   (1<<ADC_ADCMPR_CMPCOND_Pos)           /*!< The compare condition is "greater than or equal to" */
#define ADC_ADCMPR_CMPIE_INTERRUPT_ENABLE     (ADC_ADCMPR_CMPIE_Msk)                /*!< The compare function interrupt enable */

/*---------------------------------------------------------------------------------------------------------*/
/* ADC Interrupt Constant Definitions                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_ADF_INT         (ADC_ADSR_ADF_Msk)          /*!< ADC convert complete interrupt */
#define ADC_CMP0_INT        (ADC_ADSR_CMPF0_Msk)        /*!< ADC comparator 0 interrupt */
#define ADC_CMP1_INT        (ADC_ADSR_CMPF1_Msk)        /*!< ADC comparator 1 interrupt */

/*---------------------------------------------------------------------------------------------------------*/
/* ADC Operation Mode Constant Definitions                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_SINGLE_MODE         0   /*!< ADC single mode            */
#define ADC_BURST_MODE          1   /*!< ADC burst mode             */
#define ADC_SINGLE_CYCLE_MODE   2   /*!< ADC single-cycle scan mode */
#define ADC_CONTINUOUS_MODE     3   /*!< ADC continuous scan mode   */

/*---------------------------------------------------------------------------------------------------------*/
/* ADC Trigger Condition Constant Definitions                                                              */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_LOW_LEVEL      0   /*!< ADC external trigger condition is low level trigger    */
#define ADC_HIGH_LEVEL     1   /*!< ADC external trigger condition is high level trigger   */
#define ADC_FALLING_EDGE   2   /*!< ADC external trigger condition is falling edge trigger */
#define ADC_RISING_EDGE    3   /*!< ADC external trigger condition is rising edge trigger  */

/*---------------------------------------------------------------------------------------------------------*/
/* ADC Compare Condition Constant Definitions                                                              */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_LESS_THAN          0   /*!< ADC compare condition is "less than the compare value"                */
#define ADC_GREATER_OR_EQUAL   1   /*!< ADC compare condition is "greater than or equal to the compare value" */

/*---------------------------------------------------------------------------------------------------------*/
/* Constant Definitions of ADC Channel 7 Input Source                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_CH7_EXT_INPUT_SIGNAL         0   /*!< External input signal       */
#define ADC_CH7_INT_BANDGAP              1   /*!< Internal band-gap voltage   */
#define ADC_CH7_INT_TEMPERATURE_SENSOR   2   /*!< Internal temperature sensor */


/*@}*/ /* end of group M051_ADC_EXPORTED_CONSTANTS */

/** @addtogroup M051_ADC_EXPORTED_FUNCTIONS ADC Exported Functions
  @{
*/

/**
  * @brief Configure the analog input source of channel 7.
  * @param[in] adc Base address of ADC module.
  * @param[in] u32Source Decides the analog input source of channel 7. Valid values are:
  *                       - \ref ADC_ADCHER_PRESEL_EXT_INPUT_SIGNAL        : External analog input.
  *                       - \ref ADC_ADCHER_PRESEL_INT_BANDGAP             : Internal bandgap voltage.
  *                       - \ref ADC_ADCHER_PRESEL_INT_TEMPERATURE_SENSOR  : Output of internal temperature sensor.
  * @return None
  * @note While using VBG as channel 7 source, ADC module clock must /b not exceed 300kHz.
  */
#define ADC_CONFIG_CH7(adc, u32Source) (ADC->ADCHER = (ADC->ADCHER & ~ADC_ADCHER_PRESEL_Msk) | (u32Source))

/**
  * @brief Get conversion data of specified channel.
  * @param[in] adc Base address of ADC module.
  * @param[in] u32ChNum ADC Channel, valid value are from 0 to 7.
  * @return  Read RSLT bit field to get conversion data.
  */
#define ADC_GET_CONVERSION_DATA(adc, u32ChNum) ((ADC->ADDR[(u32ChNum)] & ADC_ADDR_RSLT_Msk)>>ADC_ADDR_RSLT_Pos)

/**
  * @brief Return the user-specified interrupt flags.
  * @param[in] adc Base address of ADC module.
  * @param[in] u32Mask The combination of following interrupt status bits. Each bit corresponds to a interrupt status.
  *                    Valid values are:
  *                     - \ref ADC_ADF_INT          :Convert complete interrupt flag.
  *                     - \ref ADC_CMP0_INT         :Comparator 0 interrupt flag.
  *                     - \ref ADC_CMP1_INT         :Comparator 1 interrupt flag.
  * @return  User specified interrupt flags.
  */
#define ADC_GET_INT_FLAG(adc, u32Mask) (ADC->ADSR & (u32Mask))

/**
  * @brief This macro clear the selected interrupt status bits.
  * @param[in] adc Base address of ADC module.
  * @param[in] u32Mask The combination of following interrupt status bits. Each bit corresponds to a interrupt status.
  *                    Valid values are:
  *                     - \ref ADC_ADF_INT          :Convert complete interrupt flag
  *                     - \ref ADC_CMP0_INT         :Comparator 0 interrupt flag
  *                     - \ref ADC_CMP1_INT         :Comparator 1 interrupt flag
  * @return  None
  */
#define ADC_CLR_INT_FLAG(adc, u32Mask) (ADC->ADSR = u32Mask)

/**
  * @brief Get the busy state of ADC.
  * @param[in] adc Base address of ADC module.
  * @return busy state of ADC.
  * @retval 0 ADC is not busy.
  * @retval 1 ADC is busy.
  */
#define ADC_IS_BUSY(adc) (ADC->ADSR & ADC_ADSR_BUSY_Msk ? 1 : 0)

/**
  * @brief Check if the ADC conversion data is over written or not.
  * @param[in] adc Base address of ADC module.
  * @param[in] u32ChNum ADC Channel, valid value are from 0 to 7.
  * @return Over run state of ADC data.
  * @retval 0 ADC data is not overrun.
  * @retval 1 ADC data us overrun.
  */
#define ADC_IS_DATA_OVERRUN(adc, u32ChNum) (ADC->ADSR & (u32ChNum<<ADC_ADSR_OVERRUN_Pos) ? 1 : 0)

/**
  * @brief Check if the ADC conversion data is valid or not.
  * @param[in] adc Base address of ADC module.
  * @param[in] u32ChNum ADC Channel, valid value are from 0 to 7.
  * @return Valid state of ADC data.
  * @retval 0 ADC data is not valid.
  * @retval 1 ADC data us valid.
  */
#define ADC_IS_DATA_VALID(adc, u32ChNum) (ADC->ADSR & (0x1<<(ADC_ADSR_VALID_Pos+u32ChNum)) ? 1 : 0)

/**
  * @brief Power down ADC module.
  * @param[in] adc Base address of ADC module.
  * @return None
  */
#define ADC_POWER_DOWN(adc) (ADC->ADCR &= ~ADC_ADCR_ADEN_Msk)

/**
  * @brief Power on ADC module.
  * @param[in] adc Base address of ADC module.
  * @return None
  */
#define ADC_POWER_ON(adc) (ADC->ADCR |= ADC_ADCR_ADEN_Msk)

/**
  * @brief Configure the comparator 0 and enable it.
  * @param[in] adc Base address of ADC module.
  * @param[in] u32ChNum  Specifies the source channel, valid value are from 0 to 7.
  * @param[in] u32Condition Specifies the compare condition. Valid values are:
  *                          - \ref ADC_ADCMPR_CMPCOND_LESS_THAN            :The compare condition is "less than the compare value"
  *                          - \ref ADC_ADCMPR_CMPCOND_GREATER_OR_EQUAL     :The compare condition is "greater than or equal to the compare value
  * @param[in] u32Data Specifies the compare value, valid value are between 0 ~ 0xFFF.
  * @param[in] u32MatchCount Specifies the match count setting, valid values are between 1~16.
  * @return None
  * @details For example, ADC_ENABLE_CMP0(ADC, 5, ADC_ADCMPR_CMPCOND_GREATER_OR_EQUAL, 0x800, 10);
  *          Means ADC will assert comparator 0 flag if channel 5 conversion result is greater or
  *          equal to 0x800 for 10 times continuously.
  * @note When DIFFEN bit is set to 1, ADC comparator compares CMPD with conversion result with unsigned
  *       format (M05xxBN only). u32Data should be filled in unsigned format (straight binary format).
  */
#define ADC_ENABLE_CMP0(adc, \
                        u32ChNum, \
                        u32Condition, \
                        u32Data, \
                        u32MatchCount) (ADC->ADCMPR[0] = ((u32ChNum) << ADC_ADCMPR_CMPCH_Pos) | \
                                                          u32Condition | \
                                                         ((u32Data) << ADC_ADCMPR_CMPD_Pos) | \
                                                         (((u32MatchCount) - 1) << ADC_ADCMPR_CMPMATCNT_Pos) |\
                                                          ADC_ADCMPR_CMPEN_Msk)

/**
  * @brief Disable comparator 0
  * @param[in] adc Base address of ADC module
  */
#define ADC_DISABLE_CMP0(adc) (ADC->ADCMPR[0] = 0)

/**
  * @brief Configure the comparator 1 and enable it.
  * @param[in] adc Base address of ADC module.
  * @param[in] u32ChNum  Specifies the source channel, valid value are from 0 to 7.
  * @param[in] u32Condition Specifies the compare condition. Valid values are:
  *                          - \ref ADC_ADCMPR_CMPCOND_LESS_THAN            :The compare condition is "less than the compare value"
  *                          - \ref ADC_ADCMPR_CMPCOND_GREATER_OR_EQUAL     :The compare condition is "greater than or equal to the compare value
  * @param[in] u32Data Specifies the compare value, valid value are between 0 ~ 0xFFF.
  * @param[in] u32MatchCount Specifies the match count setting, valid values are between 1~16.
  * @return None
  * @details For example, ADC_ENABLE_CMP1(ADC, 5, ADC_ADCMPR_CMPCOND_GREATER_OR_EQUAL, 0x800, 10);
  *          Means ADC will assert comparator 1 flag if channel 5 conversion result is greater or
  *          equal to 0x800 for 10 times continuously.
  */
#define ADC_ENABLE_CMP1(adc, \
                        u32ChNum, \
                        u32Condition, \
                        u32Data, \
                        u32MatchCount) (ADC->ADCMPR[1] = ((u32ChNum) << ADC_ADCMPR_CMPCH_Pos) | \
                                                          u32Condition | \
                                                         ((u32Data) << ADC_ADCMPR_CMPD_Pos) | \
                                                         (((u32MatchCount) - 1) << ADC_ADCMPR_CMPMATCNT_Pos) |\
                                                          ADC_ADCMPR_CMPEN_Msk)

/**
  * @brief Disable comparator 1.
  * @param[in] adc Base address of ADC module.
  */
#define ADC_DISABLE_CMP1(adc) (ADC->ADCMPR[1] = 0)

/**
  * @brief Set ADC input channel. Enabled channel will be converted while ADC starts.
  * @param[in] adc Base address of ADC module.
  * @param[in] u32Mask  Channel enable bit. Each bit corresponds to a input channel. Bit 0 is channel 0, bit 1 is channel 1..., bit 7 is channel 7.
  * @return None
  * @note M051 series MCU ADC can only convert 1 channel at a time. If more than 1 channels are enabled, only channel
  *       with smallest number will be convert.
  */
#define ADC_SET_INPUT_CHANNEL(adc, u32Mask) (ADC->ADCHER = (ADC->ADCHER & ~ADC_ADCHER_CHEN_Msk) | (u32Mask))

/**
  * @brief Set the output format mode.
  * @param[in] adc Base address of ADC module.
  * @param[in] u32Format Decides the output format. Valid values are:
  *                      - \ref ADC_ADCR_DMOF_UNSIGNED_OUTPUT      :Select the straight binary format as the output format of the conversion result.
  *                      - \ref ADC_ADCR_DMOF_TWOS_COMPLEMENT      :Select the 2's complement format as the output format of the conversion result.
  * @return None
  * @note Burst mode and ADC compare function can not support 2's complement output format,
  *       this u32Format must be 0 (M05xxBN only).
  */
#define ADC_SET_DMOF(adc, u32Format) (ADC->ADCR = (ADC->ADCR & ~ADC_ADCR_DMOF_Msk) | (u32Format))

/**
  * @brief Start the A/D conversion.
  * @param[in] adc Base address of ADC module.
  * @return None
  */
#define ADC_START_CONV(adc) (ADC->ADCR |= ADC_ADCR_ADST_Msk)

/**
  * @brief Stop the A/D conversion.
  * @param[in] adc Base address of ADC module.
  * @return None
  * @note When hardware clears the ADST bit, the ADST bit must be kept at 0 at least one ADC peripheral clock
  *       period before setting it to 1 again, otherwise the A/D converter may not work (M05xxBN only). If ADST
  *       bit is cleared to 0 when ADC is in converting, the BUSY bit will be cleared to 0 immediately, ADC will
  *       finish the current conversion and save the result to the ADDRx register of the enabled channel (M05xxBN only).
  *       But, ADC can not finish the current conversion and A/D converter enters idle state directly (M05xxDN only).
  */
#define ADC_STOP_CONV(adc) (ADC->ADCR &= ~ADC_ADCR_ADST_Msk)

void ADC_Open(ADC_T *adc,
              uint32_t u32InputMode,
              uint32_t u32OpMode,
              uint32_t u32ChMask);
void ADC_Close(ADC_T *adc);
void ADC_EnableHWTrigger(ADC_T *adc,
                         uint32_t u32Source,
                         uint32_t u32Param);
void ADC_DisableHWTrigger(ADC_T *adc);
void ADC_EnableInt(ADC_T *adc, uint32_t u32Mask);
void ADC_DisableInt(ADC_T *adc, uint32_t u32Mask);



/*@}*/ /* end of group M051_ADC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M051_ADC_Driver */

/*@}*/ /* end of group M051_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__ADC_H__

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
