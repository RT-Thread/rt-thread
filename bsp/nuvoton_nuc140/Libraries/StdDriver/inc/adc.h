/**************************************************************************//**
 * @file     adc.h
 * @version  V3.00
 * $Revision: 6 $
 * $Date: 15/05/06 4:49p $
 * @brief    ADC Driver Header File
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __ADC_H__
#define __ADC_H__


#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup ADC_Driver ADC Driver
  @{
*/

/** @addtogroup ADC_EXPORTED_CONSTANTS ADC Exported Constants
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/*  ADCR Constant Definitions                                                                              */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_ADCR_ADEN_CONVERTER_DISABLE   (0UL<<ADC_ADCR_ADEN_Pos)   /*!< ADC converter disable          */
#define ADC_ADCR_ADEN_CONVERTER_ENABLE    (1UL<<ADC_ADCR_ADEN_Pos)   /*!< ADC converter enable           */

#define ADC_ADCR_ADMD_SINGLE            (0UL<<ADC_ADCR_ADMD_Pos)     /*!< Single mode                */
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


/*@}*/ /* end of group ADC_EXPORTED_CONSTANTS */

/** @addtogroup ADC_EXPORTED_FUNCTIONS ADC Exported Functions
  @{
*/

/**
  * @brief Configure the analog input source of channel 7.
  * @param[in] adc The pointer of the specified ADC module.
  * @param[in] u32Source Decides the analog input source of channel 7. Valid values are:
  *                       - \ref ADC_ADCHER_PRESEL_EXT_INPUT_SIGNAL        : External analog input.
  *                       - \ref ADC_ADCHER_PRESEL_INT_BANDGAP             : Internal bandgap voltage.
  *                       - \ref ADC_ADCHER_PRESEL_INT_TEMPERATURE_SENSOR  : Output of internal temperature sensor.
  * @return None
  * @details Channel 7 supports 3 input sources: External analog voltage, internal Band-gap voltage, and internal temperature sensor output.
  * @note While using VBG as channel 7 source, ADC module clock must /b not exceed 300kHz.
  */
#define ADC_CONFIG_CH7(adc, u32Source) ((adc)->ADCHER = ((adc)->ADCHER & ~ADC_ADCHER_PRESEL_Msk) | (u32Source))

/**
  * @brief Enable PDMA transfer.
  * @param[in] adc The pointer of the specified ADC module
  * @return None
  * @details Enable PDMA to transfer the conversion data.
  * @note While enable PDMA transfer, software must set ADIE = 0 to disable interrupt.
  */
#define ADC_ENABLE_PDMA(adc) ((adc)->ADCR |= ADC_ADCR_PTEN_Msk)

/**
  * @brief Disable PDMA transfer.
  * @param[in] adc The pointer of the specified ADC module
  * @return None
  * @details Disable PDMA to transfer the conversion data.
  */
#define ADC_DISABLE_PDMA(adc) ((adc)->ADCR &= ~ADC_ADCR_PTEN_Msk)

/**
  * @brief Get conversion data of specified channel.
  * @param[in] adc The pointer of the specified ADC module.
  * @param[in] u32ChNum  ADC Channel, valid value are from 0 to 7.
  * @return 16-bit data.
  * @details Read RSLT bit field to get conversion data.
  */
#define ADC_GET_CONVERSION_DATA(adc, u32ChNum) ((adc)->ADDR[(u32ChNum)] & ADC_ADDR_RSLT_Msk)

/**
  * @brief Return the user-specified interrupt flags.
  * @param[in] adc The pointer of the specified ADC module.
  * @param[in] u32Mask The combination of following interrupt status bits. Each bit corresponds to a interrupt status.
  *                    Valid values are:
  *                     - \ref ADC_ADF_INT          :Convert complete interrupt flag.
  *                     - \ref ADC_CMP0_INT         :Comparator 0 interrupt flag.
  *                     - \ref ADC_CMP1_INT         :Comparator 1 interrupt flag.
  * @return User specified interrupt flags.
  * @details Get the status of the ADC interrupt flag.
  */
#define ADC_GET_INT_FLAG(adc, u32Mask) ((adc)->ADSR & (u32Mask))

/**
  * @brief This macro clear the selected interrupt status bits.
  * @param[in] adc The pointer of the specified ADC module.
  * @param[in] u32Mask The combination of following interrupt status bits. Each bit corresponds to a interrupt status.
  *                    Valid values are:
  *                     - \ref ADC_ADF_INT          :Convert complete interrupt flag.
  *                     - \ref ADC_CMP0_INT         :Comparator 0 interrupt flag.
  *                     - \ref ADC_CMP1_INT         :Comparator 1 interrupt flag.
  * @return None
  * @details ADF (ADSR[0])/CMPF0 (ADSR[1])/CMPF0 (ADSR[2]) can be cleared by writing 1 to itself.
  */
#define ADC_CLR_INT_FLAG(adc, u32Mask) ((adc)->ADSR = (u32Mask))

/**
  * @brief Get the busy state of ADC.
  * @param[in] adc The pointer of the specified ADC module.
  * @retval 0 ADC is not busy.
  * @retval 1 ADC is busy.
  * @details BUSY(ADSR[3])is mirror of as ADST bit (ADCR[11]).
  */
#define ADC_IS_BUSY(adc) ((adc)->ADSR & ADC_ADSR_BUSY_Msk ? 1 : 0)

/**
  * @brief Check if the ADC conversion data is over written or not.
  * @param[in] adc The pointer of the specified ADC module.
  * @param[in] u32ChNum ADC Channel, valid value are from 0 to 7.
  * @retval 0 ADC data is not overrun.
  * @retval 1 ADC data is overrun.
  * @details OVERRUN (ADSR[23:16]) is a mirror to OVERRUN (ADDR0~7[16]).
  */
#define ADC_IS_DATA_OVERRUN(adc, u32ChNum) ((adc)->ADSR & (0x1 << (ADC_ADSR_OVERRUN_Pos + (u32ChNum))) ? 1 : 0)

/**
  * @brief Check if the ADC conversion data is valid or not.
  * @param[in] adc The pointer of the specified ADC module.
  * @param[in] u32ChNum ADC Channel, valid value are from 0 to 7.
  * @retval 0 ADC data is not valid.
  * @retval 1 ADC data is valid.
  * @details VALID (ADDR0~7[17]) is set to 1 when corresponding channel analog input conversion is completed and cleared by hardware after ADDR register is read.
  */
#define ADC_IS_DATA_VALID(adc, u32ChNum) ((adc)->ADSR & (0x1<<(ADC_ADSR_VALID_Pos+(u32ChNum))) ? 1 : 0)

/**
  * @brief Power down ADC module.
  * @param[in] adc The pointer of the specified ADC module.
  * @return None
  * @details Disable A/D converter analog circuit for saving power consumption.
  * @note None
  */
#define ADC_POWER_DOWN(adc) ((adc)->ADCR &= ~ADC_ADCR_ADEN_Msk)

/**
  * @brief Power on ADC module.
  * @param[in] adc The pointer of the specified ADC module.
  * @return None
  * @details Before starting A/D conversion function, ADEN bit (ADCR[0]) should be set to 1.
  */
#define ADC_POWER_ON(adc) ((adc)->ADCR |= ADC_ADCR_ADEN_Msk)

/**
  * @brief Configure the comparator 0 and enable it.
  * @param[in] adc The pointer of the specified ADC module.
  * @param[in] u32ChNum  Specifies the source channel, valid value are from 0 to 7.
  * @param[in] u32Condition Specifies the compare condition. Valid values are:
  *                          - \ref ADC_ADCMPR_CMPCOND_LESS_THAN            :The compare condition is "less than the compare value".
  *                          - \ref ADC_ADCMPR_CMPCOND_GREATER_OR_EQUAL     :The compare condition is "greater than or equal to the compare value.
  * @param[in] u32Data Specifies the compare value, valid value are between 0 ~ 0xFFF.
  * @param[in] u32MatchCount Specifies the match count setting, valid values are between 1~16.
  * @return None
  * @details For example, ADC_ENABLE_CMP0(ADC, 5, ADC_ADCMPR_CMPCOND_GREATER_OR_EQUAL, 0x800, 10);
  *          Means ADC will assert comparator 0 flag if channel 5 conversion result is greater or
  *          equal to 0x800 for 10 times continuously.
  * \hideinitializer
  */
#define ADC_ENABLE_CMP0(adc, \
                        u32ChNum, \
                        u32Condition, \
                        u32Data, \
                        u32MatchCount) ((adc)->ADCMPR[0] = ((u32ChNum) << ADC_ADCMPR_CMPCH_Pos) | \
                                                          (u32Condition) | \
                                                         ((u32Data) << ADC_ADCMPR_CMPD_Pos) | \
                                                         (((u32MatchCount) - 1) << ADC_ADCMPR_CMPMATCNT_Pos) |\
                                                          ADC_ADCMPR_CMPEN_Msk)

/**
  * @brief Disable comparator 0.
  * @param[in] adc The pointer of the specified ADC module.
  * @return None
  * @details Set CMPEN (ADCMPR0[0]) to 0 to disable ADC controller to compare CMPD (ADCMPR0[27:16]).
  */
#define ADC_DISABLE_CMP0(adc) ((adc)->ADCMPR[0] = 0)

/**
  * @brief Configure the comparator 1 and enable it.
  * @param[in] adc The pointer of the specified ADC module.
  * @param[in] u32ChNum  Specifies the source channel, valid value are from 0 to 7.
  * @param[in] u32Condition Specifies the compare condition. Valid values are:
  *                          - \ref ADC_ADCMPR_CMPCOND_LESS_THAN            :The compare condition is "less than the compare value".
  *                          - \ref ADC_ADCMPR_CMPCOND_GREATER_OR_EQUAL     :The compare condition is "greater than or equal to the compare value.
  * @param[in] u32Data Specifies the compare value, valid value are between 0 ~ 0xFFF.
  * @param[in] u32MatchCount Specifies the match count setting, valid values are between 1~16.
  * @return None
  * @details For example, ADC_ENABLE_CMP1(ADC, 5, ADC_ADCMPR_CMPCOND_GREATER_OR_EQUAL, 0x800, 10);
  *          Means ADC will assert comparator 1 flag if channel 5 conversion result is greater or
  *          equal to 0x800 for 10 times continuously.
  * \hideinitializer
  */
#define ADC_ENABLE_CMP1(adc, \
                        u32ChNum, \
                        u32Condition, \
                        u32Data, \
                        u32MatchCount) ((adc)->ADCMPR[1] = ((u32ChNum) << ADC_ADCMPR_CMPCH_Pos) | \
                                                          (u32Condition) | \
                                                         ((u32Data) << ADC_ADCMPR_CMPD_Pos) | \
                                                         (((u32MatchCount) - 1) << ADC_ADCMPR_CMPMATCNT_Pos) |\
                                                          ADC_ADCMPR_CMPEN_Msk)

/**
  * @brief Disable comparator 1.
  * @param[in] adc The pointer of the specified ADC module.
  * @return None
  * @details Set CMPEN (ADCMPR1[0]) to 0 to disable ADC controller to compare CMPD (ADCMPR1[27:16]).
  */
#define ADC_DISABLE_CMP1(adc) ((adc)->ADCMPR[1] = 0)

/**
  * @brief Set ADC input channel.
  * @param[in] adc The pointer of the specified ADC module.
  * @param[in] u32Mask  Channel enable bit. Each bit corresponds to a input channel. Bit 0 is channel 0, bit 1 is channel 1..., bit 7 is channel 7.
  * @return None
  * @details Enabled channel will be converted while ADC starts.
  * @note NUC100 series MCU ADC can only convert 1 channel at a time. If more than 1 channels are enabled, only channel
  *       with smallest number will be convert.
  */
#define ADC_SET_INPUT_CHANNEL(adc, u32Mask) ((adc)->ADCHER = ((adc)->ADCHER & ~ADC_ADCHER_CHEN_Msk) | (u32Mask))

/**
  * @brief Set the output format mode.
  * @param[in] adc The pointer of the specified ADC module.
  * @param[in] u32Format Decides the output format. Valid values are:
  *                       - \ref ADC_ADCR_DMOF_UNSIGNED_OUTPUT      :Select the straight binary format as the output format of the conversion result.
  *                       - \ref ADC_ADCR_DMOF_TWOS_COMPLEMENT      :Select the 2's complement format as the output format of the conversion result.
  * @return None
  * @details  The macro is used to set A/D differential input mode output format.
  */
#define ADC_SET_DMOF(adc, u32Format) ((adc)->ADCR = ((adc)->ADCR & ~ADC_ADCR_DMOF_Msk) | (u32Format))

/**
  * @brief Start the A/D conversion.
  * @param[in] adc The pointer of the specified ADC module.
  * @return None
  * @details ADST (ADCR[11]) can be set to 1 from three sources: software, PWM Center-aligned trigger and external pin STADC.
  */
#define ADC_START_CONV(adc) ((adc)->ADCR |= ADC_ADCR_ADST_Msk)

/**
  * @brief Stop the A/D conversion.
  * @param[in] adc The pointer of the specified ADC module.
  * @return None
  * @details ADST (ADCR[11]) will be cleared to 0 by hardware automatically at the ends of single mode and single-cycle scan mode.
  *          In continuous scan mode, A/D conversion is continuously performed until software writes 0 to this bit or chip reset.
  */
#define ADC_STOP_CONV(adc) ((adc)->ADCR &= ~ADC_ADCR_ADST_Msk)

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



/*@}*/ /* end of group ADC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group ADC_Driver */

/*@}*/ /* end of group Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__ADC_H__

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
