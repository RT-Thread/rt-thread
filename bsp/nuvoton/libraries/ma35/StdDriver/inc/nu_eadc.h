/**************************************************************************//**
 * @file     nu_eadc.h
 * @brief    EADC driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_EADC_H__
#define __NU_EADC_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup EADC_Driver EADC Driver
  @{
*/

/** @addtogroup EADC_EXPORTED_CONSTANTS EADC Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/*  EADC_CTL Constant Definitions                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define EADC_CTL_DIFFEN_SINGLE_END          (0UL<<EADC_CTL_DIFFEN_Pos)   /*!< Single-end input mode      \hideinitializer */
#define EADC_CTL_DIFFEN_DIFFERENTIAL        (1UL<<EADC_CTL_DIFFEN_Pos)   /*!< Differential input mode    \hideinitializer */

#define EADC_CTL_DMOF_STRAIGHT_BINARY       (0UL<<EADC_CTL_DMOF_Pos)     /*!< Select the straight binary format as the output format of the conversion result   \hideinitializer */
#define EADC_CTL_DMOF_TWOS_COMPLEMENT       (1UL<<EADC_CTL_DMOF_Pos)     /*!< Select the 2's complement format as the output format of the conversion result    \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* EADC_SCTL Constant Definitions                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define EADC_SCTL_CHSEL(x)                  ((x) << EADC_SCTL_CHSEL_Pos)       /*!< A/D sample module channel selection \hideinitializer */
#define EADC_SCTL_TRGDLYDIV(x)              ((x) << EADC_SCTL_TRGDLYDIV_Pos)   /*!< A/D sample module start of conversion trigger delay clock divider selection \hideinitializer */
#define EADC_SCTL_TRGDLYCNT(x)              ((x) << EADC_SCTL_TRGDLYCNT_Pos)   /*!< A/D sample module start of conversion trigger delay time \hideinitializer */

#define EADC_SOFTWARE_TRIGGER               (0UL<<EADC_SCTL_TRGSEL_Pos)      /*!< Software trigger \hideinitializer */
#define EADC_FALLING_EDGE_TRIGGER           (EADC_SCTL_EXTFEN_Msk | (1UL<<EADC_SCTL_TRGSEL_Pos))       /*!< STADC pin falling edge trigger \hideinitializer */
#define EADC_RISING_EDGE_TRIGGER            (EADC_SCTL_EXTREN_Msk | (1UL<<EADC_SCTL_TRGSEL_Pos))       /*!< STADC pin rising edge trigger \hideinitializer */
#define EADC_FALLING_RISING_EDGE_TRIGGER    (EADC_SCTL_EXTFEN_Msk | EADC_SCTL_EXTREN_Msk | (1UL<<EADC_SCTL_TRGSEL_Pos)) /*!< STADC pin both falling and rising edge trigger \hideinitializer */
#define EADC_ADINT0_TRIGGER                 (2UL<<EADC_SCTL_TRGSEL_Pos)      /*!< ADC ADINT0 interrupt EOC pulse trigger \hideinitializer */
#define EADC_ADINT1_TRIGGER                 (3UL<<EADC_SCTL_TRGSEL_Pos)      /*!< ADC ADINT1 interrupt EOC pulse trigger \hideinitializer */
#define EADC_TIMER0_TRIGGER                 (4UL<<EADC_SCTL_TRGSEL_Pos)      /*!< Timer0 overflow pulse trigger \hideinitializer */
#define EADC_TIMER1_TRIGGER                 (5UL<<EADC_SCTL_TRGSEL_Pos)      /*!< Timer1 overflow pulse trigger \hideinitializer */
#define EADC_TIMER2_TRIGGER                 (6UL<<EADC_SCTL_TRGSEL_Pos)      /*!< Timer2 overflow pulse trigger \hideinitializer */
#define EADC_TIMER3_TRIGGER                 (7UL<<EADC_SCTL_TRGSEL_Pos)      /*!< Timer3 overflow pulse trigger \hideinitializer */
#define EADC_TIMER4_TRIGGER                 (8UL<<EADC_SCTL_TRGSEL_Pos)      /*!< Timer4 overflow pulse trigger \hideinitializer */
#define EADC_TIMER5_TRIGGER                 (9UL<<EADC_SCTL_TRGSEL_Pos)      /*!< Timer5 overflow pulse trigger \hideinitializer */
#define EADC_TIMER6_TRIGGER                 (0xAUL<<EADC_SCTL_TRGSEL_Pos)    /*!< Timer6 overflow pulse trigger \hideinitializer */
#define EADC_TIMER7_TRIGGER                 (0xBUL<<EADC_SCTL_TRGSEL_Pos)    /*!< Timer7 overflow pulse trigger \hideinitializer */
#define EADC_TIMER8_TRIGGER                 (0xCUL<<EADC_SCTL_TRGSEL_Pos)    /*!< Timer8 overflow pulse trigger \hideinitializer */
#define EADC_TIMER9_TRIGGER                 (0xDUL<<EADC_SCTL_TRGSEL_Pos)    /*!< Timer9 overflow pulse trigger \hideinitializer */
#define EADC_TIMER10_TRIGGER                (0xEUL<<EADC_SCTL_TRGSEL_Pos)    /*!< Timer10 overflow pulse trigger \hideinitializer */
#define EADC_TIMER11_TRIGGER                (0xFUL<<EADC_SCTL_TRGSEL_Pos)    /*!< Timer11 overflow pulse trigger \hideinitializer */
#define EADC_EPWM0TG0_TRIGGER               (0x10UL<<EADC_SCTL_TRGSEL_Pos)   /*!< EPWM0TG0 trigger \hideinitializer */
#define EADC_EPWM0TG1_TRIGGER               (0x11UL<<EADC_SCTL_TRGSEL_Pos)   /*!< EPWM0TG1 trigger \hideinitializer */
#define EADC_EPWM0TG2_TRIGGER               (0x12UL<<EADC_SCTL_TRGSEL_Pos)   /*!< EPWM0TG2 trigger \hideinitializer */
#define EADC_EPWM0TG3_TRIGGER               (0x13UL<<EADC_SCTL_TRGSEL_Pos)   /*!< EPWM0TG3 trigger \hideinitializer */
#define EADC_EPWM0TG4_TRIGGER               (0x14UL<<EADC_SCTL_TRGSEL_Pos)   /*!< EPWM0TG4 trigger \hideinitializer */
#define EADC_EPWM0TG5_TRIGGER               (0x15UL<<EADC_SCTL_TRGSEL_Pos)   /*!< EPWM0TG5 trigger \hideinitializer */
#define EADC_EPWM1TG0_TRIGGER               (0x16UL<<EADC_SCTL_TRGSEL_Pos)   /*!< EPWM1TG0 trigger \hideinitializer */
#define EADC_EPWM1TG1_TRIGGER               (0x17UL<<EADC_SCTL_TRGSEL_Pos)   /*!< EPWM1TG1 trigger \hideinitializer */
#define EADC_EPWM1TG2_TRIGGER               (0x18UL<<EADC_SCTL_TRGSEL_Pos)   /*!< EPWM1TG2 trigger \hideinitializer */
#define EADC_EPWM1TG3_TRIGGER               (0x19UL<<EADC_SCTL_TRGSEL_Pos)   /*!< EPWM1TG3 trigger \hideinitializer */
#define EADC_EPWM1TG4_TRIGGER               (0x1AUL<<EADC_SCTL_TRGSEL_Pos)   /*!< EPWM1TG4 trigger \hideinitializer */
#define EADC_EPWM1TG5_TRIGGER               (0x1BUL<<EADC_SCTL_TRGSEL_Pos)   /*!< EPWM1TG5 trigger \hideinitializer */
#define EADC_EPWM2TG0_TRIGGER               (0x1CUL<<EADC_SCTL_TRGSEL_Pos)   /*!< EPWM2TG0 trigger \hideinitializer */
#define EADC_EPWM2TG1_TRIGGER               (0x1DUL<<EADC_SCTL_TRGSEL_Pos)   /*!< EPWM2TG1 trigger \hideinitializer */
#define EADC_EPWM2TG2_TRIGGER               (0x1EUL<<EADC_SCTL_TRGSEL_Pos)   /*!< EPWM2TG2 trigger \hideinitializer */
#define EADC_EPWM2TG3_TRIGGER               (0x1FUL<<EADC_SCTL_TRGSEL_Pos)   /*!< EPWM2TG3 trigger \hideinitializer */
#define EADC_EPWM2TG4_TRIGGER               (0x20UL<<EADC_SCTL_TRGSEL_Pos)   /*!< EPWM2TG4 trigger \hideinitializer */
#define EADC_EPWM2TG5_TRIGGER               (0x21UL<<EADC_SCTL_TRGSEL_Pos)   /*!< EPWM2TG5 trigger \hideinitializer */

#define EADC_SCTL_TRGDLYDIV_DIVIDER_1       (0<<EADC_SCTL_TRGDLYDIV_Pos)           /*!< Trigger delay clock frequency is ADC_CLK/1 \hideinitializer */
#define EADC_SCTL_TRGDLYDIV_DIVIDER_2       (0x1UL<<EADC_SCTL_TRGDLYDIV_Pos)       /*!< Trigger delay clock frequency is ADC_CLK/2 \hideinitializer */
#define EADC_SCTL_TRGDLYDIV_DIVIDER_4       (0x2UL<<EADC_SCTL_TRGDLYDIV_Pos)       /*!< Trigger delay clock frequency is ADC_CLK/4 \hideinitializer */
#define EADC_SCTL_TRGDLYDIV_DIVIDER_16      (0x3UL<<EADC_SCTL_TRGDLYDIV_Pos)       /*!< Trigger delay clock frequency is ADC_CLK/16 \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/* EADC_CMP Constant Definitions                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define EADC_CMP_CMPCOND_LESS_THAN          (0UL<<EADC_CMP_CMPCOND_Pos)   /*!< The compare condition is "less than" \hideinitializer */
#define EADC_CMP_CMPCOND_GREATER_OR_EQUAL   (1UL<<EADC_CMP_CMPCOND_Pos)   /*!< The compare condition is "greater than or equal to" \hideinitializer */
#define EADC_CMP_CMPWEN_ENABLE              (EADC_CMP_CMPWEN_Msk)    /*!< Compare window mode enable \hideinitializer */
#define EADC_CMP_CMPWEN_DISABLE             (~EADC_CMP_CMPWEN_Msk)   /*!< Compare window mode disable \hideinitializer */
#define EADC_CMP_ADCMPIE_ENABLE             (EADC_CMP_ADCMPIE_Msk)   /*!< A/D result compare interrupt enable \hideinitializer */
#define EADC_CMP_ADCMPIE_DISABLE            (~EADC_CMP_ADCMPIE_Msk)  /*!< A/D result compare interrupt disable \hideinitializer */

/*@}*/ /* end of group EADC_EXPORTED_CONSTANTS */

/** @addtogroup EADC_EXPORTED_FUNCTIONS EADC Exported Functions
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/*  EADC Macro Definitions                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/

/**
  * @brief A/D Converter Control Circuits Reset.
  * @param[in] eadc The pointer of the specified EADC module.
  * @return None
  * @details ADCRST bit (EADC_CT[1]) remains 1 during ADC reset, when ADC reset end, the ADCRST bit is automatically cleared to 0.
  * \hideinitializer
  */
#define EADC_CONV_RESET(eadc) ((eadc)->CTL |= EADC_CTL_ADCRST_Msk)

/**
  * @brief Enable PDMA transfer.
  * @param[in] eadc The pointer of the specified EADC module.
  * @return None
  * @details When A/D conversion is completed, the converted data is loaded into EADC_DATn (n: 0 ~ 18) register,
  *         user can enable this bit to generate a PDMA data transfer request.
  * @note When set PDMAEN bit (EADC_CTL[11]), user must set ADINTENn (EADC_CTL[5:2], n=0~3) = 0 to disable interrupt.
  * \hideinitializer
  */
#define EADC_ENABLE_PDMA(eadc) ((eadc)->CTL |= EADC_CTL_PDMAEN_Msk)

/**
  * @brief Disable PDMA transfer.
  * @param[in] eadc The pointer of the specified EADC module.
  * @return None
  * @details This macro is used to disable PDMA transfer.
  * \hideinitializer
  */
#define EADC_DISABLE_PDMA(eadc) ((eadc)->CTL &= (~EADC_CTL_PDMAEN_Msk))

/**
  * @brief Enable Sample Module PDMA transfer.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleMask the combination of sample module interrupt status bits. Each bit corresponds to a sample module interrupt status.
  *                          This parameter decides which sample module interrupts will be disabled, valid range are between 1~0x7FFFF.
  * @return None
  * @details When A/D conversion is completed, the converted data is loaded into EADC_DATn (n: 0 ~ 18) register,
  *         user can enable this bit to generate a PDMA data transfer request.
  * \hideinitializer
  */
#define EADC_ENABLE_SAMPLE_MODULE_PDMA(eadc, u32ModuleMask) ((eadc)->PDMACTL |= u32ModuleMask)

/**
  * @brief Disable Sample Module PDMA transfer.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleMask the combination of sample module interrupt status bits. Each bit corresponds to a sample module interrupt status.
  *                          This parameter decides which sample module interrupts will be disabled, valid range are between 1~0x7FFFF.
  * @return None
  * @details This macro is used to disable sample module PDMA transfer.
  * \hideinitializer
  */
#define EADC_DISABLE_SAMPLE_MODULE_PDMA(eadc, u32ModuleMask) ((eadc)->PDMACTL &= (~u32ModuleMask))

/**
  * @brief Enable double buffer mode.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleNum Decides the sample module number, valid value are from 0 to 3.
  * @return None
  * @details The ADC controller supports a double buffer mode in sample module 0~3.
  *         If user enable DBMEN (EADC_SCTLn[23], n=0~3), the double buffer mode will enable.
  * \hideinitializer
  */
#define EADC_ENABLE_DOUBLE_BUFFER(eadc, u32ModuleNum) ((eadc)->SCTL[(u32ModuleNum)] |= EADC_SCTL_DBMEN_Msk)

/**
  * @brief Disable double buffer mode.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleNum Decides the sample module number, valid value are from 0 to 3.
  * @return None
  * @details Sample has one sample result register.
  * \hideinitializer
  */
#define EADC_DISABLE_DOUBLE_BUFFER(eadc, u32ModuleNum) ((eadc)->SCTL[(u32ModuleNum)] &= ~EADC_SCTL_DBMEN_Msk)

/**
  * @brief Set ADIFn at A/D end of conversion.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleNum Decides the sample module number, valid value are from 0 to 15.
  * @return None
  * @details The A/D converter generates ADIFn (EADC_STATUS2[3:0], n=0~3) at the start of conversion.
  * \hideinitializer
  */
#define EADC_ENABLE_INT_POSITION(eadc, u32ModuleNum) ((eadc)->SCTL[(u32ModuleNum)] |= EADC_SCTL_INTPOS_Msk)

/**
  * @brief Set ADIFn at A/D start of conversion.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleNum Decides the sample module number, valid value are from 0 to 15.
  * @return None
  * @details The A/D converter generates ADIFn (EADC_STATUS2[3:0], n=0~3) at the end of conversion.
  * \hideinitializer
  */
#define EADC_DISABLE_INT_POSITION(eadc, u32ModuleNum) ((eadc)->SCTL[(u32ModuleNum)] &= ~EADC_SCTL_INTPOS_Msk)

/**
  * @brief Enable the interrupt.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32Mask Decides the combination of interrupt status bits. Each bit corresponds to a interrupt status.
  *                    This parameter decides which interrupts will be enabled. Bit 0 is ADCIEN0, bit 1 is ADCIEN1..., bit 3 is ADCIEN3.
  * @return None
  * @details The A/D converter generates a conversion end ADIFn (EADC_STATUS2[n]) upon the end of specific sample module A/D conversion.
  *         If ADCIENn bit (EADC_CTL[n+2]) is set then conversion end interrupt request ADINTn is generated (n=0~3).
  * \hideinitializer
  */
#define EADC_ENABLE_INT(eadc, u32Mask) ((eadc)->CTL |= ((u32Mask) << EADC_CTL_ADCIEN0_Pos))

/**
  * @brief Disable the interrupt.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32Mask Decides the combination of interrupt status bits. Each bit corresponds to a interrupt status.
  *                    This parameter decides which interrupts will be disabled. Bit 0 is ADCIEN0, bit 1 is ADCIEN1..., bit 3 is ADCIEN3.
  * @return None
  * @details Specific sample module A/D ADINT0 interrupt function Disabled.
  * \hideinitializer
  */
#define EADC_DISABLE_INT(eadc, u32Mask) ((eadc)->CTL &= ~((u32Mask) << EADC_CTL_ADCIEN0_Pos))

/**
  * @brief Enable the sample module interrupt.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32IntSel Decides which interrupt source will be used, valid value are from 0 to 3.
  * @param[in] u32ModuleMask the combination of sample module interrupt status bits. Each bit corresponds to a sample module interrupt status.
  *                          This parameter decides which sample module interrupts will be enabled, valid range are between 1~0x7FFFF.
  * @return None
  * @details There are 4 ADC interrupts ADINT0~3, and each of these interrupts has its own interrupt vector address.
  * \hideinitializer
  */
#define EADC_ENABLE_SAMPLE_MODULE_INT(eadc, u32IntSel, u32ModuleMask) ((eadc)->INTSRC[(u32IntSel)] |= (u32ModuleMask))

/**
  * @brief Disable the sample module interrupt.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32IntSel Decides which interrupt source will be used, valid value are from 0 to 3.
  * @param[in] u32ModuleMask the combination of sample module interrupt status bits. Each bit corresponds to a sample module interrupt status.
  *                          This parameter decides which sample module interrupts will be disabled, valid range are between 1~0x7FFFF.
  * @return None
  * @details There are 4 ADC interrupts ADINT0~3, and each of these interrupts has its own interrupt vector address.
  * \hideinitializer
  */
#define EADC_DISABLE_SAMPLE_MODULE_INT(eadc, u32IntSel, u32ModuleMask) ((eadc)->INTSRC[(u32IntSel)] &= ~(u32ModuleMask))

/**
  * @brief Set the input mode output format.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32Format Decides the output format. Valid values are:
  *                       - EADC_CTL_DMOF_STRAIGHT_BINARY      :Select the straight binary format as the output format of the conversion result.
  *                       - EADC_CTL_DMOF_TWOS_COMPLEMENT      :Select the 2's complement format as the output format of the conversion result.
  * @return None
  * @details The macro is used to set A/D input mode output format.
  * \hideinitializer
  */
#define EADC_SET_DMOF(eadc, u32Format) ((eadc)->CTL = ((eadc)->CTL & ~EADC_CTL_DMOF_Msk) | (u32Format))

/**
  * @brief Start the A/D conversion.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleMask The combination of sample module. Each bit corresponds to a sample module.
  *                         This parameter decides which sample module will be conversion, valid range are between 1~0x7FFFF.
  *                         Bit 0 is sample module 0, bit 1 is sample module 1..., bit 18 is sample module 18.
  * @return None
  * @details After write EADC_SWTRG register to start ADC conversion, the EADC_PENDSTS register will show which SAMPLE will conversion.
  * \hideinitializer
  */
#define EADC_START_CONV(eadc, u32ModuleMask) ((eadc)->SWTRG = (u32ModuleMask))

/**
  * @brief Cancel the conversion for sample module.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleMask The combination of sample module. Each bit corresponds to a sample module.
  *                         This parameter decides which sample module will stop the conversion, valid range are between 1~0x7FFFF.
  *                         Bit 0 is sample module 0, bit 1 is sample module 1..., bit 18 is sample module18.
  * @return None
  * @details If user want to disable the conversion of the sample module, user can write EADC_PENDSTS register to clear it.
  * \hideinitializer
  */
#define EADC_STOP_CONV(eadc, u32ModuleMask) ((eadc)->PENDSTS = (u32ModuleMask))

/**
  * @brief Get the conversion pending flag.
  * @param[in] eadc The pointer of the specified EADC module.
  * @return Return the conversion pending sample module.
  * @details This STPFn(EADC_PENDSTS[18:0]) bit remains 1 during pending state, when the respective ADC conversion is end,
  *         the STPFn (n=0~18) bit is automatically cleared to 0.
  * \hideinitializer
  */
#define EADC_GET_PENDING_CONV(eadc) ((eadc)->PENDSTS)

/**
  * @brief Get the conversion data of the user-specified sample module.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleNum Decides the sample module number, valid value are from 0 to 18.
  * @return Return the conversion data of the user-specified sample module.
  * @details This macro is used to read RESULT bit (EADC_DATn[15:0], n=0~18) field to get conversion data.
  * \hideinitializer
  */
#define EADC_GET_CONV_DATA(eadc, u32ModuleNum) ((eadc)->DAT[(u32ModuleNum)] & EADC_DAT_RESULT_Msk)

/**
  * @brief Get the data overrun flag of the user-specified sample module.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleMask The combination of data overrun status bits. Each bit corresponds to a data overrun status, valid range are between 1~0x7FFFF.
  * @return Return the data overrun flag of the user-specified sample module.
  * @details This macro is used to read OV bit (EADC_STATUS0[31:16], EADC_STATUS1[18:16]) field to get data overrun status.
  * \hideinitializer
  */
#define EADC_GET_DATA_OVERRUN_FLAG(eadc, u32ModuleMask) ((((eadc)->STATUS0 >> EADC_STATUS0_OV_Pos) | ((eadc)->STATUS1 & EADC_STATUS1_OV_Msk)) & (u32ModuleMask))

/**
  * @brief Get the data valid flag of the user-specified sample module.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleMask The combination of data valid status bits. Each bit corresponds to a data valid status, valid range are between 1~0x7FFFF.
  * @return Return the data valid flag of the user-specified sample module.
  * @details This macro is used to read VALID bit (EADC_STATUS0[15:0], EADC_STATUS1[2:0]) field to get data valid status.
  * \hideinitializer
  */
#define EADC_GET_DATA_VALID_FLAG(eadc, u32ModuleMask) ((((eadc)->STATUS0 & EADC_STATUS0_VALID_Msk) | (((eadc)->STATUS1 & EADC_STATUS1_VALID_Msk) << 16)) & (u32ModuleMask))

/**
  * @brief Get the double data of the user-specified sample module.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleNum Decides the sample module number, valid value are from 0 to 18.
  * @return Return the double data of the user-specified sample module.
  * @details This macro is used to read RESULT bit (EADC_DDATn[15:0], n=0~3) field to get conversion data.
  * \hideinitializer
  */
#define EADC_GET_DOUBLE_DATA(eadc, u32ModuleNum) ((eadc)->DDAT[(u32ModuleNum)] & EADC_DDAT0_RESULT_Msk)

/**
  * @brief Get the user-specified interrupt flags.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32Mask The combination of interrupt status bits. Each bit corresponds to a interrupt status.
  *                    Bit 0 is ADIF0, bit 1 is ADIF1..., bit 3 is ADIF3.
  *                    Bit 4 is ADCMPF0, bit 5 is ADCMPF1..., bit 7 is ADCMPF3.
  * @return Return the user-specified interrupt flags.
  * @details This macro is used to get the user-specified interrupt flags.
  * \hideinitializer
  */
#define EADC_GET_INT_FLAG(eadc, u32Mask) ((eadc)->STATUS2 & (u32Mask))

/**
  * @brief Get the user-specified sample module overrun flags.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleMask The combination of sample module overrun status bits. Each bit corresponds to a sample module overrun status, valid range are between 1~0x7FFFF.
  * @return Return the user-specified sample module overrun flags.
  * @details This macro is used to get the user-specified sample module overrun flags.
  * \hideinitializer
  */
#define EADC_GET_SAMPLE_MODULE_OV_FLAG(eadc, u32ModuleMask) ((eadc)->OVSTS & (u32ModuleMask))

/**
  * @brief Clear the selected interrupt status bits.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32Mask The combination of compare interrupt status bits. Each bit corresponds to a compare interrupt status.
  *                    Bit 0 is ADIF0, bit 1 is ADIF1..., bit 3 is ADIF3.
  *                    Bit 4 is ADCMPF0, bit 5 is ADCMPF1..., bit 7 is ADCMPF3.
  * @return None
  * @details This macro is used to clear clear the selected interrupt status bits.
  * \hideinitializer
  */
#define EADC_CLR_INT_FLAG(eadc, u32Mask) ((eadc)->STATUS2 = (u32Mask))

/**
  * @brief Clear the selected sample module overrun status bits.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleMask The combination of sample module overrun status bits. Each bit corresponds to a sample module overrun status.
  *                      Bit 0 is SPOVF0, bit 1 is SPOVF1..., bit 18 is SPOVF18.
  * @return None
  * @details This macro is used to clear the selected sample module overrun status bits.
  * \hideinitializer
  */
#define EADC_CLR_SAMPLE_MODULE_OV_FLAG(eadc, u32ModuleMask) ((eadc)->OVSTS = (u32ModuleMask))

/**
  * @brief Check all sample module A/D result data register overrun flags.
  * @param[in] eadc The pointer of the specified EADC module.
  * @retval 0 None of sample module data register overrun flag is set to 1.
  * @retval 1 Any one of sample module data register overrun flag is set to 1.
  * @details The AOV bit (EADC_STATUS2[27]) will keep 1 when any one of sample module data register overrun flag OVn (EADC_DATn[16]) is set to 1.
  * \hideinitializer
  */
#define EADC_IS_DATA_OV(eadc) (((eadc)->STATUS2 & EADC_STATUS2_AOV_Msk) >> EADC_STATUS2_AOV_Pos)

/**
  * @brief Check all sample module A/D result data register valid flags.
  * @param[in] eadc The pointer of the specified EADC module.
  * @retval 0 None of sample module data register valid flag is set to 1.
  * @retval 1 Any one of sample module data register valid flag is set to 1.
  * @details The AVALID bit (EADC_STATUS2[26]) will keep 1 when any one of sample module data register valid flag VALIDn (EADC_DATn[17]) is set to 1.
  * \hideinitializer
  */
#define EADC_IS_DATA_VALID(eadc) (((eadc)->STATUS2 & EADC_STATUS2_AVALID_Msk) >> EADC_STATUS2_AVALID_Pos)

/**
  * @brief Check all A/D sample module start of conversion overrun flags.
  * @param[in] eadc The pointer of the specified EADC module.
  * @retval 0 None of sample module event overrun flag is set to 1.
  * @retval 1 Any one of sample module event overrun flag is set to 1.
  * @details The STOVF bit (EADC_STATUS2[25]) will keep 1 when any one of sample module event overrun flag SPOVFn (EADC_OVSTS[n]) is set to 1.
  * \hideinitializer
  */
#define EADC_IS_SAMPLE_MODULE_OV(eadc) (((eadc)->STATUS2 & EADC_STATUS2_STOVF_Msk) >> EADC_STATUS2_STOVF_Pos)

/**
  * @brief Check all A/D interrupt flag overrun bits.
  * @param[in] eadc The pointer of the specified EADC module.
  * @retval 0 None of ADINT interrupt flag is overwritten to 1.
  * @retval 1 Any one of ADINT interrupt flag is overwritten to 1.
  * @details The ADOVIF bit (EADC_STATUS2[24]) will keep 1 when any one of ADINT interrupt flag ADOVIFn (EADC_STATUS2[11:8]) is overwritten to 1.
  * \hideinitializer
  */
#define EADC_IS_INT_FLAG_OV(eadc) (((eadc)->STATUS2 & EADC_STATUS2_ADOVIF_Msk) >> EADC_STATUS2_ADOVIF_Pos)

/**
  * @brief Get the busy state of EADC.
  * @param[in] eadc The pointer of the specified EADC module.
  * @retval 0 Idle state.
  * @retval 1 Busy state.
  * @details This macro is used to read BUSY bit (EADC_STATUS2[23]) to get busy state.
  * \hideinitializer
  */
#define EADC_IS_BUSY(eadc) (((eadc)->STATUS2 & EADC_STATUS2_BUSY_Msk) >> EADC_STATUS2_BUSY_Pos)

/**
  * @brief Configure the comparator 0 and enable it.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleNum specifies the compare sample module, valid value are from 0 to 18.
  * @param[in] u32Condition specifies the compare condition. Valid values are:
  *                        - \ref EADC_CMP_CMPCOND_LESS_THAN            :The compare condition is "less than the compare value"
  *                        - \ref EADC_CMP_CMPCOND_GREATER_OR_EQUAL     :The compare condition is "greater than or equal to the compare value
  * @param[in] u16CMPData specifies the compare value, valid range are between 0~0xFFF.
  * @param[in] u32MatchCount specifies the match count setting, valid range are between 0~0xF.
  * @return None
  * @details For example, ADC_ENABLE_CMP0(EADC, 5, ADC_ADCMPR_CMPCOND_GREATER_OR_EQUAL, 0x800, 10, EADC_CMP_CMPWEN_DISABLE, EADC_CMP_ADCMPIE_ENABLE);
  *         Means EADC will assert comparator 0 flag if sample module 5 conversion result is greater or
  *         equal to 0x800 for 10 times continuously, and a compare interrupt request is generated.
  * \hideinitializer
  */
#define EADC_ENABLE_CMP0(eadc,\
                         u32ModuleNum,\
                         u32Condition,\
                         u16CMPData,\
                         u32MatchCount) ((eadc)->CMP[0] = (((eadc)->CMP[0] & ~(EADC_CMP_CMPSPL_Msk|EADC_CMP_CMPCOND_Msk|EADC_CMP_CMPDAT_Msk|EADC_CMP_CMPMCNT_Msk))|\
                                                            (((u32ModuleNum) << EADC_CMP_CMPSPL_Pos)|\
                                                            (u32Condition) |\
                                                            ((u16CMPData) << EADC_CMP_CMPDAT_Pos)| \
                                                            (((u32MatchCount) - 1) << EADC_CMP_CMPMCNT_Pos)|\
                                                            EADC_CMP_ADCMPEN_Msk)))

/**
  * @brief Configure the comparator 1 and enable it.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleNum specifies the compare sample module, valid value are from 0 to 18.
  * @param[in] u32Condition specifies the compare condition. Valid values are:
  *                        - \ref EADC_CMP_CMPCOND_LESS_THAN            :The compare condition is "less than the compare value"
  *                        - \ref EADC_CMP_CMPCOND_GREATER_OR_EQUAL     :The compare condition is "greater than or equal to the compare value
  * @param[in] u16CMPData specifies the compare value, valid range are between 0~0xFFF.
  * @param[in] u32MatchCount specifies the match count setting, valid range are between 0~0xF.
  * @return None
  * @details For example, ADC_ENABLE_CMP1(EADC, 5, ADC_ADCMPR_CMPCOND_GREATER_OR_EQUAL, 0x800, 10, EADC_CMP_ADCMPIE_ENABLE);
  *         Means EADC will assert comparator 1 flag if sample module 5 conversion result is greater or
  *         equal to 0x800 for 10 times continuously, and a compare interrupt request is generated.
  * \hideinitializer
  */
#define EADC_ENABLE_CMP1(eadc,\
                         u32ModuleNum,\
                         u32Condition,\
                         u16CMPData,\
                         u32MatchCount) ((eadc)->CMP[1] = (((eadc)->CMP[1] & ~(EADC_CMP_CMPSPL_Msk|EADC_CMP_CMPCOND_Msk|EADC_CMP_CMPDAT_Msk|EADC_CMP_CMPMCNT_Msk))|\
                                                            (((u32ModuleNum) << EADC_CMP_CMPSPL_Pos)|\
                                                            (u32Condition) |\
                                                            ((u16CMPData) << EADC_CMP_CMPDAT_Pos)| \
                                                            (((u32MatchCount) - 1) << EADC_CMP_CMPMCNT_Pos)|\
                                                            EADC_CMP_ADCMPEN_Msk)))

/**
  * @brief Configure the comparator 2 and enable it.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleNum specifies the compare sample module, valid value are from 0 to 18.
  * @param[in] u32Condition specifies the compare condition. Valid values are:
  *                        - \ref EADC_CMP_CMPCOND_LESS_THAN            :The compare condition is "less than the compare value"
  *                        - \ref EADC_CMP_CMPCOND_GREATER_OR_EQUAL     :The compare condition is "greater than or equal to the compare value
  * @param[in] u16CMPData specifies the compare value, valid range are between 0~0xFFF.
  * @param[in] u32MatchCount specifies the match count setting, valid range are between 0~0xF.
  * @return None
  * @details For example, ADC_ENABLE_CMP2(EADC, 5, ADC_ADCMPR_CMPCOND_GREATER_OR_EQUAL, 0x800, 10, EADC_CMP_CMPWEN_DISABLE, EADC_CMP_ADCMPIE_ENABLE);
  *         Means EADC will assert comparator 2 flag if sample module 5 conversion result is greater or
  *         equal to 0x800 for 10 times continuously, and a compare interrupt request is generated.
  * \hideinitializer
  */
#define EADC_ENABLE_CMP2(eadc,\
                         u32ModuleNum,\
                         u32Condition,\
                         u16CMPData,\
                         u32MatchCount) ((eadc)->CMP[2] = (((eadc)->CMP[2] & ~(EADC_CMP_CMPSPL_Msk|EADC_CMP_CMPCOND_Msk|EADC_CMP_CMPDAT_Msk|EADC_CMP_CMPMCNT_Msk))|\
                                                            (((u32ModuleNum) << EADC_CMP_CMPSPL_Pos)|\
                                                            (u32Condition) |\
                                                            ((u16CMPData) << EADC_CMP_CMPDAT_Pos)| \
                                                            (((u32MatchCount) - 1) << EADC_CMP_CMPMCNT_Pos)|\
                                                            EADC_CMP_ADCMPEN_Msk)))

/**
  * @brief Configure the comparator 3 and enable it.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32ModuleNum specifies the compare sample module, valid value are from 0 to 18.
  * @param[in] u32Condition specifies the compare condition. Valid values are:
  *                        - \ref EADC_CMP_CMPCOND_LESS_THAN            :The compare condition is "less than the compare value"
  *                        - \ref EADC_CMP_CMPCOND_GREATER_OR_EQUAL     :The compare condition is "greater than or equal to the compare value
  * @param[in] u16CMPData specifies the compare value, valid range are between 0~0xFFF.
  * @param[in] u32MatchCount specifies the match count setting, valid range are between 1~0xF.
  * @return None
  * @details For example, ADC_ENABLE_CMP3(EADC, 5, ADC_ADCMPR_CMPCOND_GREATER_OR_EQUAL, 0x800, 10, EADC_CMP_ADCMPIE_ENABLE);
  *         Means EADC will assert comparator 3 flag if sample module 5 conversion result is greater or
  *         equal to 0x800 for 10 times continuously, and a compare interrupt request is generated.
  * \hideinitializer
  */
#define EADC_ENABLE_CMP3(eadc,\
                         u32ModuleNum,\
                         u32Condition,\
                         u16CMPData,\
                         u32MatchCount) ((eadc)->CMP[3] = (((eadc)->CMP[3] & ~(EADC_CMP_CMPSPL_Msk|EADC_CMP_CMPCOND_Msk|EADC_CMP_CMPDAT_Msk|EADC_CMP_CMPMCNT_Msk))|\
                                                            (((u32ModuleNum) << EADC_CMP_CMPSPL_Pos)|\
                                                            (u32Condition) |\
                                                            ((u16CMPData) << EADC_CMP_CMPDAT_Pos)| \
                                                            (((u32MatchCount) - 1) << EADC_CMP_CMPMCNT_Pos)|\
                                                            EADC_CMP_ADCMPEN_Msk)))

/**
  * @brief Enable the compare window mode.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32CMP Specifies the compare register, valid value are 0 and 2.
  * @return None
  * @details ADCMPF0 (EADC_STATUS2[4]) will be set when both EADC_CMP0 and EADC_CMP1 compared condition matched.
  * \hideinitializer
  */
#define EADC_ENABLE_CMP_WINDOW_MODE(eadc, u32CMP) ((eadc)->CMP[(u32CMP)] |= EADC_CMP_CMPWEN_Msk)

/**
  * @brief Disable the compare window mode.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32CMP Specifies the compare register, valid value are 0 and 2.
  * @return None
  * @details ADCMPF2 (EADC_STATUS2[6]) will be set when both EADC_CMP2 and EADC_CMP3 compared condition matched.
  * \hideinitializer
  */
#define EADC_DISABLE_CMP_WINDOW_MODE(eadc, u32CMP) ((eadc)->CMP[(u32CMP)] &= ~EADC_CMP_CMPWEN_Msk)

/**
  * @brief Enable the compare interrupt.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32CMP Specifies the compare register, valid value are from 0 to 3.
  * @return None
  * @details If the compare function is enabled and the compare condition matches the setting of CMPCOND (EADC_CMPn[2], n=0~3)
  *         and CMPMCNT (EADC_CMPn[11:8], n=0~3), ADCMPFn (EADC_STATUS2[7:4], n=0~3) will be asserted, in the meanwhile,
  *         if ADCMPIE is set to 1, a compare interrupt request is generated.
  * \hideinitializer
  */
#define EADC_ENABLE_CMP_INT(eadc, u32CMP) ((eadc)->CMP[(u32CMP)] |= EADC_CMP_ADCMPIE_Msk)

/**
  * @brief Disable the compare interrupt.
  * @param[in] eadc The pointer of the specified EADC module.
  * @param[in] u32CMP Specifies the compare register, valid value are from 0 to 3.
  * @return None
  * @details This macro is used to disable the compare interrupt.
  * \hideinitializer
  */
#define EADC_DISABLE_CMP_INT(eadc, u32CMP) ((eadc)->CMP[(u32CMP)] &= ~EADC_CMP_ADCMPIE_Msk)

/**
  * @brief Disable comparator 0.
  * @param[in] eadc The pointer of the specified EADC module.
  * @return None
  * @details This macro is used to disable comparator 0.
  * \hideinitializer
  */
#define EADC_DISABLE_CMP0(eadc) ((eadc)->CMP[0] = 0)

/**
  * @brief Disable comparator 1.
  * @param[in] eadc The pointer of the specified EADC module.
  * @return None
  * @details This macro is used to disable comparator 1.
  * \hideinitializer
  */
#define EADC_DISABLE_CMP1(eadc) ((eadc)->CMP[1] = 0)

/**
  * @brief Disable comparator 2.
  * @param[in] eadc The pointer of the specified EADC module.
  * @return None
  * @details This macro is used to disable comparator 2.
  * \hideinitializer
  */
#define EADC_DISABLE_CMP2(eadc) ((eadc)->CMP[2] = 0)

/**
  * @brief Disable comparator 3.
  * @param[in] eadc The pointer of the specified EADC module.
  * @return None
  * @details This macro is used to disable comparator 3.
  * \hideinitializer
  */
#define EADC_DISABLE_CMP3(eadc) ((eadc)->CMP[3] = 0)

/*---------------------------------------------------------------------------------------------------------*/
/* Define EADC functions prototype                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
void EADC_Open(EADC_T *eadc, uint32_t u32InputMode);
void EADC_Close(EADC_T *eadc);
void EADC_ConfigSampleModule(EADC_T *eadc, uint32_t u32ModuleNum, uint32_t u32TriggerSrc, uint32_t u32Channel);
void EADC_SetTriggerDelayTime(EADC_T *eadc, uint32_t u32ModuleNum, uint32_t u32TriggerDelayTime, uint32_t u32DelayClockDivider);
void EADC_SetExtendSampleTime(EADC_T *eadc, uint32_t u32ModuleNum, uint32_t u32ExtendSampleTime);

/*@}*/ /* end of group EADC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group EADC_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_EADC_H__ */

