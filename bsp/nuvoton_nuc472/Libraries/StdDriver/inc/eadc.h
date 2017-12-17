/**************************************************************************//**
 * @file     eadc.h
 * @version  V1.00
 * $Revision: 17 $
 * $Date: 15/12/01 10:13a $
 * @brief    NUC472/NUC442 EADC driver header file
 *
 * @note
 * Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __EADC_H__
#define __EADC_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_EADC_Driver EADC Driver
  @{
*/

/** @addtogroup NUC472_442_EADC_EXPORTED_CONSTANTS EADC Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/* EADC SAMPLE module number Definitions                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
#define EADC0_SAMPLE_MODULE0    0     /*!< EADC0 SAMPLE module 0  \hideinitializer */
#define EADC0_SAMPLE_MODULE1    1     /*!< EADC0 SAMPLE module 1  \hideinitializer */
#define EADC0_SAMPLE_MODULE2    2     /*!< EADC0 SAMPLE module 2  \hideinitializer */
#define EADC0_SAMPLE_MODULE3    3     /*!< EADC0 SAMPLE module 3  \hideinitializer */
#define EADC0_SAMPLE_MODULE4    4     /*!< EADC0 SAMPLE module 4  \hideinitializer */
#define EADC0_SAMPLE_MODULE5    5     /*!< EADC0 SAMPLE module 5  \hideinitializer */
#define EADC0_SAMPLE_MODULE6    6     /*!< EADC0 SAMPLE module 6  \hideinitializer */
#define EADC0_SAMPLE_MODULE7    7     /*!< EADC0 SAMPLE module 7  \hideinitializer */
#define EADC1_SAMPLE_MODULE0    8     /*!< EADC1 SAMPLE module 0  \hideinitializer */
#define EADC1_SAMPLE_MODULE1    9     /*!< EADC1 SAMPLE module 1  \hideinitializer */
#define EADC1_SAMPLE_MODULE2   10     /*!< EADC1 SAMPLE module 2  \hideinitializer */
#define EADC1_SAMPLE_MODULE3   11     /*!< EADC1 SAMPLE module 3  \hideinitializer */
#define EADC1_SAMPLE_MODULE4   12     /*!< EADC1 SAMPLE module 4  \hideinitializer */
#define EADC1_SAMPLE_MODULE5   13     /*!< EADC1 SAMPLE module 5  \hideinitializer */
#define EADC1_SAMPLE_MODULE6   14     /*!< EADC1 SAMPLE module 6  \hideinitializer */
#define EADC1_SAMPLE_MODULE7   15     /*!< EADC1 SAMPLE module 7  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* EADC Compare SAMPLE module number Definitions                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
#define CMP_EADC0_SAMPLE_MODULE0  0   /*!< Compare EADC0 SAMPLE module 0  \hideinitializer */
#define CMP_EADC0_SAMPLE_MODULE1  1   /*!< Compare EADC0 SAMPLE module 1  \hideinitializer */
#define CMP_EADC0_SAMPLE_MODULE2  2   /*!< Compare EADC0 SAMPLE module 2  \hideinitializer */
#define CMP_EADC0_SAMPLE_MODULE3  3   /*!< Compare EADC0 SAMPLE module 3  \hideinitializer */
#define CMP_EADC1_SAMPLE_MODULE0  4   /*!< Compare EADC1 SAMPLE module 0  \hideinitializer */
#define CMP_EADC1_SAMPLE_MODULE1  5   /*!< Compare EADC1 SAMPLE module 1  \hideinitializer */
#define CMP_EADC1_SAMPLE_MODULE2  6   /*!< Compare EADC1 SAMPLE module 2  \hideinitializer */
#define CMP_EADC1_SAMPLE_MODULE3  7   /*!< Compare EADC1 SAMPLE module 3  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* EADC_ADnSPCTLx Constant Definitions                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
#define EADC_SCTL_CHSEL(x)     ((x) << EADC_AD0SPCTL0_CHSEL_Pos)       /*!< A/D sample module channel selection  \hideinitializer */
#define EADC_SCTL_TRGDLYDIV(x) ((x) << EADC_AD0SPCTL0_TRGDLYDIV_Pos)   /*!< A/D sample module start of conversion trigger delay clock divider selection  \hideinitializer */
#define EADC_SCTL_TRGDLYCNT(x) ((x) << EADC_AD0SPCTL0_TRGDLYCNT_Pos)   /*!< A/D sample module start of conversion trigger delay time  \hideinitializer */

#define EADC_SOFTWARE_TRIGGER (0UL << EADC_AD0SPCTL0_TRGSEL_Pos)      /*!< Software trigger  \hideinitializer */
#define EADC_STADC_TRIGGER    (1UL << EADC_AD0SPCTL0_TRGSEL_Pos)      /*!< External pin STADC trigger  \hideinitializer */
#define EADC_ADINT0_TRIGGER   (2UL << EADC_AD0SPCTL0_TRGSEL_Pos)      /*!< EADC ADINT0 interrupt EOC pulse trigger  \hideinitializer */
#define EADC_ADINT1_TRIGGER   (3UL << EADC_AD0SPCTL0_TRGSEL_Pos)      /*!< EADC ADINT1 interrupt EOC pulse trigger  \hideinitializer */
#define EADC_TIMER0_TRIGGER   (4UL << EADC_AD0SPCTL0_TRGSEL_Pos)      /*!< Timer0 overflow pulse trigger  \hideinitializer */
#define EADC_TIMER1_TRIGGER   (5UL << EADC_AD0SPCTL0_TRGSEL_Pos)      /*!< Timer1 overflow pulse trigger  \hideinitializer */
#define EADC_TIMER2_TRIGGER   (6UL << EADC_AD0SPCTL0_TRGSEL_Pos)      /*!< Timer2 overflow pulse trigger  \hideinitializer */
#define EADC_TIMER3_TRIGGER   (7UL << EADC_AD0SPCTL0_TRGSEL_Pos)      /*!< Timer3 overflow pulse trigger  \hideinitializer */
#define EADC_EPWM0CH0_TRIGGER  (8UL << EADC_AD0SPCTL0_TRGSEL_Pos)      /*!< EPWM0CH0 trigger  \hideinitializer */
#define EADC_EPWM0CH2_TRIGGER  (9UL << EADC_AD0SPCTL0_TRGSEL_Pos)      /*!< EPWM0CH2 trigger  \hideinitializer */
#define EADC_EPWM0CH4_TRIGGER  (0xAUL << EADC_AD0SPCTL0_TRGSEL_Pos)    /*!< EPWM0CH4 trigger  \hideinitializer */
#define EADC_EPWM1CH0_TRIGGER  (0xBUL << EADC_AD0SPCTL0_TRGSEL_Pos)    /*!< EPWM1CH0 trigger  \hideinitializer */
#define EADC_EPWM1CH2_TRIGGER  (0xCUL << EADC_AD0SPCTL0_TRGSEL_Pos)    /*!< EPWM1CH2 trigger  \hideinitializer */
#define EADC_EPWM1CH4_TRIGGER  (0xDUL << EADC_AD0SPCTL0_TRGSEL_Pos)    /*!< EPWM1CH4 trigger  \hideinitializer */
#define EADC_PWM0CH0_TRIGGER  (0xEUL << EADC_AD0SPCTL0_TRGSEL_Pos)    /*!< PWM0CH0 trigger  \hideinitializer */
#define EADC_PWM0CH1_TRIGGER  (0xFUL << EADC_AD0SPCTL0_TRGSEL_Pos)    /*!< PWM0CH1 trigger  \hideinitializer */

#define EADC_SPCTL_TRGDLYDIV_DIVIDER_1    (0 << EADC_AD0SPCTL0_TRGDLYDIV_Pos)           /*!< Trigger delay clock frequency is ADC_CLK/1  \hideinitializer */
#define EADC_SPCTL_TRGDLYDIV_DIVIDER_2    (0x1UL << EADC_AD0SPCTL0_TRGDLYDIV_Pos)       /*!< Trigger delay clock frequency is ADC_CLK/2  \hideinitializer */
#define EADC_SPCTL_TRGDLYDIV_DIVIDER_4    (0x2UL << EADC_AD0SPCTL0_TRGDLYDIV_Pos)       /*!< Trigger delay clock frequency is ADC_CLK/4  \hideinitializer */
#define EADC_SPCTL_TRGDLYDIV_DIVIDER_16   (0x3UL << EADC_AD0SPCTL0_TRGDLYDIV_Pos)       /*!< Trigger delay clock frequency is ADC_CLK/16  \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/* EADC_CMP Constant Definitions                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define EADC_CMP_CMPCOND_LESS_THAN          (0UL << EADC_CMP0_CMPCOND_Pos)   /*!< The compare condition is "less than"  \hideinitializer */
#define EADC_CMP_CMPCOND_GREATER_OR_EQUAL   (1UL << EADC_CMP0_CMPCOND_Pos)   /*!< The compare condition is "greater than or equal to"  \hideinitializer */
#define EADC_CMP_ADCMPIE_ENABLE             (EADC_CMP0_ADCMPIE_Msk)          /*!< A/D result compare interrupt enable  \hideinitializer */
#define EADC_CMP_ADCMPIE_DISABLE            (~EADC_CMP0_ADCMPIE_Msk)         /*!< A/D result compare interrupt disable  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* EADC PWM Trigger Condition Definitions                                                                  */
/*---------------------------------------------------------------------------------------------------------*/
#define EADC0_TRIGGEREN0    0     /*!< A/D trigger condition for SAMPLE00  \hideinitializer */
#define EADC0_TRIGGEREN1    1     /*!< A/D trigger condition for SAMPLE01  \hideinitializer */
#define EADC0_TRIGGEREN2    2     /*!< A/D trigger condition for SAMPLE02  \hideinitializer */
#define EADC0_TRIGGEREN3    3     /*!< A/D trigger condition for SAMPLE03  \hideinitializer */
#define EADC1_TRIGGEREN0    4     /*!< A/D trigger condition for SAMPLE10  \hideinitializer */
#define EADC1_TRIGGEREN1    5     /*!< A/D trigger condition for SAMPLE11  \hideinitializer */
#define EADC1_TRIGGEREN2    6     /*!< A/D trigger condition for SAMPLE12  \hideinitializer */
#define EADC1_TRIGGEREN3    7     /*!< A/D trigger condition for SAMPLE13  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* EADC Channel selection Definitions                                                                  */
/*---------------------------------------------------------------------------------------------------------*/
#define EADC0_CH0    0     /*!< Select EADC0 channel 0 for EADC0 SAMPLE Module \hideinitializer */
#define EADC0_CH1    1     /*!< Select EADC0 channel 1 for EADC0 SAMPLE Module \hideinitializer */
#define EADC0_CH2    2     /*!< Select EADC0 channel 2 for EADC0 SAMPLE Module \hideinitializer */
#define EADC0_CH3    3     /*!< Select EADC0 channel 3 for EADC0 SAMPLE Module \hideinitializer */
#define EADC0_CH4    4     /*!< Select EADC0 channel 4 for EADC0 SAMPLE Module \hideinitializer */
#define EADC0_CH5    5     /*!< Select EADC0 channel 5 for EADC0 SAMPLE Module \hideinitializer */
#define EADC0_CH6    6     /*!< Select EADC0 channel 6 for EADC0 SAMPLE Module \hideinitializer */
#define EADC0_CH7    7     /*!< Select EADC0 channel 7 for EADC0 SAMPLE Module \hideinitializer */
#define EADC0_VBG    8     /*!< Select EADC0 VBG for EADC0 SAMPLE Module \hideinitializer */
#define EADC0_VTEMP  9     /*!< Select EADC0 VTEMP for EADC0 SAMPLE Module \hideinitializer */
#define EADC0_AVSS  10     /*!< Select EADC0 AVSS for EADC0 SAMPLE Module \hideinitializer */
#define EADC0_OP0   11     /*!< Select EADC0 OP0 for EADC0 SAMPLE Module \hideinitializer */
#define EADC1_CH0    0     /*!< Select EADC1 channel 0 for EADC1 SAMPLE Module \hideinitializer */
#define EADC1_CH1    1     /*!< Select EADC1 channel 1 for EADC1 SAMPLE Module \hideinitializer */
#define EADC1_CH2    2     /*!< Select EADC1 channel 2 for EADC1 SAMPLE Module \hideinitializer */
#define EADC1_CH3    3     /*!< Select EADC1 channel 3 for EADC1 SAMPLE Module \hideinitializer */
#define EADC1_CH4    4     /*!< Select EADC1 channel 4 for EADC1 SAMPLE Module \hideinitializer */
#define EADC1_CH5    5     /*!< Select EADC1 channel 5 for EADC1 SAMPLE Module \hideinitializer */
#define EADC1_CH6    6     /*!< Select EADC1 channel 6 for EADC1 SAMPLE Module \hideinitializer */
#define EADC1_CH7    7     /*!< Select EADC1 channel 7 for EADC1 SAMPLE Module \hideinitializer */
#define EADC1_OP1    8     /*!< Select EADC1 OP1 for EADC1 SAMPLE Module \hideinitializer */

/*@}*/ /* end of group NUC472_442_EADC_EXPORTED_CONSTANTS */

/** @addtogroup NUC472_442_EADC_EXPORTED_FUNCTIONS EADC Exported Functions
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/*  EADC Macro Definitions                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/

/**
  * @brief Power down EADC module
  * @param[in] eadc Base address of EADC module
  * @return None
  * \hideinitializer
  */
#define EADC_POWER_DOWN(eadc) (EADC->CTL &= ~EADC_CTL_ADCEN_Msk)

/**
  * @brief Power on EADC module
  * @param[in] eadc Base address of EADC module
  * @return None
  * \hideinitializer
  */
#define EADC_POWER_ON(eadc) (EADC->CTL |= EADC_CTL_ADCEN_Msk)

/**
  * @brief A/D Converter Control Circuits Reset.
  * @param[in] eadc Base address of EADC module.
  * @return None
  * @details ADCRST bit (EADC_CT[1]) remains 1 during EADC reset, when EADC reset end, the ADCRST bit is automatically cleared to 0.
  * \hideinitializer
  */
#define EADC_CONV_RESET(eadc) ((eadc)->CTL |= EADC_CTL_ADCRST_Msk)

/**
  * @brief Enable double buffer mode.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32ModuleNum Decides the sample module number, valid values are:
  *                            - \ref EADC0_SAMPLE_MODULE0      : EADC0 SAMPLE module 0
  *                            - \ref EADC0_SAMPLE_MODULE1      : EADC0 SAMPLE module 1
  *                            - \ref EADC0_SAMPLE_MODULE2      : EADC0 SAMPLE module 2
  *                            - \ref EADC0_SAMPLE_MODULE3      : EADC0 SAMPLE module 3
  *                            - \ref EADC1_SAMPLE_MODULE0      : EADC1 SAMPLE module 0
  *                            - \ref EADC1_SAMPLE_MODULE1      : EADC1 SAMPLE module 1
  *                            - \ref EADC1_SAMPLE_MODULE2      : EADC1 SAMPLE module 2
  *                            - \ref EADC1_SAMPLE_MODULE3      : EADC1 SAMPLE module 3
  * @return None
  * @details The EADC controller supports a double buffer mode in eadc0/1 sample module 0~3.
  * \hideinitializer
  */
#define EADC_ENABLE_DOUBLE_BUFFER(eadc, u32ModuleNum) ((eadc)->DBMEN |= (1 << u32ModuleNum))

/**
  * @brief Disable double buffer mode.
  * @param[in] eadc Base address of EADC module..
  * @param[in] u32ModuleNum Decides the sample module number, valid values are:
  *                            - \ref EADC0_SAMPLE_MODULE0      : EADC0 SAMPLE module 0
  *                            - \ref EADC0_SAMPLE_MODULE1      : EADC0 SAMPLE module 1
  *                            - \ref EADC0_SAMPLE_MODULE2      : EADC0 SAMPLE module 2
  *                            - \ref EADC0_SAMPLE_MODULE3      : EADC0 SAMPLE module 3
  *                            - \ref EADC1_SAMPLE_MODULE0      : EADC1 SAMPLE module 0
  *                            - \ref EADC1_SAMPLE_MODULE1      : EADC1 SAMPLE module 1
  *                            - \ref EADC1_SAMPLE_MODULE2      : EADC1 SAMPLE module 2
  *                            - \ref EADC1_SAMPLE_MODULE3      : EADC1 SAMPLE module 3
  * @return None
  * @details Sample has one sample result register.
  * \hideinitializer
  */
#define EADC_DISABLE_DOUBLE_BUFFER(eadc, u32ModuleNum) ((eadc)->DBMEN &= ~(1 << u32ModuleNum))

/**
  * @brief Enable the interrupt.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32Mask Decides the combination of interrupt enable bits. Each bit corresponds to a interrupt enable.
  *                    This parameter decides which interrupts will be enabled. Bit 0 is ADCIEN0, bit 1 is ADCIEN1..., bit 3 is ADCIEN3.
  * @return None
  * @details The A/D converter generates a conversion end ADIFn (EADC_STATUS1[n]) upon the end of specific sample module A/D conversion.
  *         If ADCIENn bit (EADC_CTL[n+2]) is set then conversion end interrupt request ADINTn is generated (n=0~3).
  * \hideinitializer
  */
#define EADC_ENABLE_INT(eadc, u32Mask) ((eadc)->CTL |= ((u32Mask) << EADC_CTL_ADCIEN0_Pos))

/**
  * @brief Disable the interrupt.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32Mask Decides the combination of interrupt enable bits. Each bit corresponds to a interrupt enable.
  *                    This parameter decides which interrupts will be disabled. Bit 0 is ADCIEN0, bit 1 is ADCIEN1..., bit 3 is ADCIEN3.
  * @return None
  * @details Specific sample module A/D ADINT0 interrupt function Disabled.
  * \hideinitializer
  */
#define EADC_DISABLE_INT(eadc, u32Mask) ((eadc)->CTL &= ~((u32Mask) << EADC_CTL_ADCIEN0_Pos))

/**
  * @brief Enable the sample module interrupt.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32IntSel Decides which interrupt source will be used, valid value are from 0 to 3.
  * @param[in] u32ModuleMask the combination of sample module interrupt enable bits. Each bit corresponds to a sample module interrupt enable.
  *                          This parameter decides which sample module interrupts will be enabled, valid range are between 1~0xFFFF.
  * @return None
  * @details There are 4 EADC interrupts ADINT0~3, and each of these interrupts has its own interrupt vector address.
  * \hideinitializer
  */
#define EADC_ENABLE_SAMPLE_MODULE_INT(eadc, u32IntSel, u32ModuleMask) ((eadc)->INTSRC[(u32IntSel)] |= (u32ModuleMask))

/**
  * @brief Disable the sample module interrupt.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32IntSel Decides which interrupt source will be used, valid value are from 0 to 3.
  * @param[in] u32ModuleMask the combination of sample module interrupt enable bits. Each bit corresponds to a sample module interrupt enable.
  *                          This parameter decides which sample module interrupts will be disabled, valid range are between 1~0xFFFF.
  * @return None
  * @details There are 4 EADC interrupts ADINT0~3, and each of these interrupts has its own interrupt vector address.
  * \hideinitializer
  */
#define EADC_DISABLE_SAMPLE_MODULE_INT(eadc, u32IntSel, u32ModuleMask) ((eadc)->INTSRC[(u32IntSel)] &= ~(u32ModuleMask))

/**
  * @brief Start the A/D conversion.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32ModuleMask The combination of sample module. Each bit corresponds to a sample module.
  *                         This parameter decides which sample module will be conversion, valid range are between 1~0xFFFF.
  *                         Bit 0 is sample module 0, bit 1 is sample module 1..., bit 15 is sample module 15.
  * @return None
  * @details After write EADC_SWTRG register to start EADC conversion, the EADC_PENDSTS register will show which SAMPLE will conversion.
  * \hideinitializer
  */
#define EADC_START_CONV(eadc, u32ModuleMask) ((eadc)->SWTRG = (u32ModuleMask))

/**
  * @brief Get the conversion pending flag.
  * @param[in] eadc Base address of EADC module.
  * @return Return the conversion pending sample module.
  * @return None
  * @details This STPFn(EADC_PENDSTS[15:0]) bit remains 1 during pending state, when the respective EADC conversion is end,
  *         the STPFn (n=0~15) bit is automatically cleared to 0.
  * \hideinitializer
  */
#define EADC_GET_PENDING_CONV(eadc) ((eadc)->PENDSTS)

/**
  * @brief Get the conversion data of the user-specified sample module.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32ModuleNum Decides the sample module number, valid values are:
  *                            - \ref EADC0_SAMPLE_MODULE0      : EADC0 SAMPLE module 0
  *                            - \ref EADC0_SAMPLE_MODULE1      : EADC0 SAMPLE module 1
  *                            - \ref EADC0_SAMPLE_MODULE2      : EADC0 SAMPLE module 2
  *                            - \ref EADC0_SAMPLE_MODULE3      : EADC0 SAMPLE module 3
  *                            - \ref EADC0_SAMPLE_MODULE4      : EADC0 SAMPLE module 4
  *                            - \ref EADC0_SAMPLE_MODULE5      : EADC0 SAMPLE module 5
  *                            - \ref EADC0_SAMPLE_MODULE6      : EADC0 SAMPLE module 6
  *                            - \ref EADC0_SAMPLE_MODULE7      : EADC0 SAMPLE module 7
  *                            - \ref EADC1_SAMPLE_MODULE0      : EADC1 SAMPLE module 0
  *                            - \ref EADC1_SAMPLE_MODULE1      : EADC1 SAMPLE module 1
  *                            - \ref EADC1_SAMPLE_MODULE2      : EADC1 SAMPLE module 2
  *                            - \ref EADC1_SAMPLE_MODULE3      : EADC1 SAMPLE module 3
  *                            - \ref EADC1_SAMPLE_MODULE4      : EADC1 SAMPLE module 4
  *                            - \ref EADC1_SAMPLE_MODULE5      : EADC1 SAMPLE module 5
  *                            - \ref EADC1_SAMPLE_MODULE6      : EADC1 SAMPLE module 6
  *                            - \ref EADC1_SAMPLE_MODULE7      : EADC1 SAMPLE module 7
  * @return Return the conversion data of the user-specified sample module.
  * @details This macro is used to read RESULT bit (EADC_ADxDATn[11:0], x=0~1, n=0~7) field to get conversion data.
  * \hideinitializer
  */
#define EADC_GET_CONV_DATA(eadc, u32ModuleNum) (*(__IO uint32_t *)(&((eadc)->AD0DAT0) + (u32ModuleNum)) & EADC_AD0DAT0_RESULT_Msk)

/**
  * @brief Get the data overrun flag of the user-specified sample module.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32ModuleMask The combination of data overrun status bits. Each bit corresponds to a data overrun status, valid range are between 1~0x7FFFF.
  * @return Return the data overrun flag of the user-specified sample module.
  * @details This macro is used to read OV bit (EADC_STATUS0[31:16]) field to get data overrun status.
  * \hideinitializer
  */
#define EADC_GET_DATA_OVERRUN_FLAG(eadc, u32ModuleMask) (((eadc)->STATUS0 >> EADC_STATUS0_OV_Pos) & (u32ModuleMask))

/**
  * @brief Get the data valid flag of the user-specified sample module.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32ModuleMask The combination of data valid status bits. Each bit corresponds to a data valid status, valid range are between 1~0x7FFFF.
  * @return Return the data valid flag of the user-specified sample module.
  * @details This macro is used to read VALID bit of EADC_STATUS0[15:0] to get data valid status.
  * \hideinitializer
  */
#define EADC_GET_DATA_VALID_FLAG(eadc, u32ModuleMask) (((eadc)->STATUS0 & EADC_STATUS0_VALID_Msk) & (u32ModuleMask))

/**
  * @brief Get the double data of the user-specified sample module.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32ModuleNum Decides the sample module number, valid values are:
  *                            - \ref EADC0_SAMPLE_MODULE0      : EADC0 SAMPLE module 0
  *                            - \ref EADC0_SAMPLE_MODULE1      : EADC0 SAMPLE module 1
  *                            - \ref EADC0_SAMPLE_MODULE2      : EADC0 SAMPLE module 2
  *                            - \ref EADC0_SAMPLE_MODULE3      : EADC0 SAMPLE module 3
  *                            - \ref EADC1_SAMPLE_MODULE0      : EADC1 SAMPLE module 0
  *                            - \ref EADC1_SAMPLE_MODULE1      : EADC1 SAMPLE module 1
  *                            - \ref EADC1_SAMPLE_MODULE2      : EADC1 SAMPLE module 2
  *                            - \ref EADC1_SAMPLE_MODULE3      : EADC1 SAMPLE module 3
  * @return Return the double data of the user-specified sample module.
  * @details This macro is used to read RESULT bit (EADC_ADxDDATn[11:0], x=0~1, n=0~3) field to get conversion data.
  * \hideinitializer
  */
#define EADC_GET_DOUBLE_DATA(eadc, u32ModuleNum) (*(__IO uint32_t *)(&((eadc)->AD0DDAT0) + (u32ModuleNum)) & EADC_AD0DDAT0_RESULT_Msk)

/**
  * @brief Get the user-specified interrupt flags.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32Mask The combination of interrupt status bits. Each bit corresponds to a interrupt status.
  *                    Bit 0 is ADIF0, bit 1 is ADIF1..., bit 3 is ADIF3.
  *                    Bit 4 is ADCMPO0, bit 5 is ADCMPO1, bit 6 is ADCMPF0, bit 7 is ADCMPF1.
  * @return Return the user-specified interrupt flags.
  * @details This macro is used to get the user-specified interrupt flags.
  * \hideinitializer
  */
#define EADC_GET_INT_FLAG(eadc, u32Mask) ((eadc)->STATUS1 & (u32Mask))

/**
  * @brief Get the user-specified sample module overrun flags.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32ModuleMask The combination of sample module overrun status bits. Each bit corresponds to a sample module overrun status, valid range are between 1~0xFFFF.
  * @return Return the user-specified sample module overrun flags.
  * @details This macro is used to get the user-specified sample module overrun flags.
  * \hideinitializer
  */
#define EADC_GET_SAMPLE_MODULE_OV_FLAG(eadc, u32ModuleMask) (((eadc)->STATUS0 >> EADC_STATUS0_OV_Pos) & u32ModuleMask)

/**
  * @brief Clear the selected interrupt status bits.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32Mask The combination of compare interrupt status bits. Each bit corresponds to a compare interrupt status.
  *                    Bit 0 is ADIF0, bit 1 is ADIF1..., bit 3 is ADIF3.
  *                    Bit 4 is ADCMPO0, bit 5 is ADCMPO1, bit 6 is ADCMPF0, bit 7 is ADCMPF1.
  * @return None
  * @details This macro is used to clear clear the selected interrupt status bits.
  * \hideinitializer
  */
#define EADC_CLR_INT_FLAG(eadc, u32Mask) ((eadc)->STATUS1 = (u32Mask))

/**
  * @brief Check all sample module A/D result data register overrun flags.
  * @param[in] eadc Base address of EADC module.
  * @retval 0 None of sample module data register overrun flag is set to 1.
  * @retval 1 Any one of sample module data register overrun flag is set to 1.
  * @details The AOV bit (EADC_STATUS1[27]) will keep 1 when any one of sample module data register overrun flag OVn (EADC_ADxDATn[16]) is set to 1.
  * \hideinitializer
  */
#define EADC_IS_DATA_OV(eadc) (((eadc)->STATUS1 & EADC_STATUS1_AOV_Msk) >> EADC_STATUS1_AOV_Pos)

/**
  * @brief Check all sample module A/D result data register valid flags.
  * @param[in] eadc Base address of EADC module.
  * @retval 0 None of sample module data register valid flag is set to 1.
  * @retval 1 Any one of sample module data register valid flag is set to 1.
  * @details The AVALID bit (EADC_STATUS1[26]) will keep 1 when any one of sample module data register valid flag VALIDn (EADC_ADxDATn[17]) is set to 1.
  * \hideinitializer
  */
#define EADC_IS_DATA_VALID(eadc) (((eadc)->STATUS1 & EADC_STATUS1_AVALID_Msk) >> EADC_STATUS1_AVALID_Pos)

/**
  * @brief Check all A/D sample module start of conversion overrun flags.
  * @param[in] eadc Base address of EADC module.
  * @retval 0 None of sample module event overrun flag is set to 1.
  * @retval 1 Any one of sample module event overrun flag is set to 1.
  * @details The STOVF bit (EADC_STATUS1[25]) will keep 1 when any one of sample module event overrun flag SPOVFn (EADC_OVSTS[n]) is set to 1.
  * \hideinitializer
  */
#define EADC_IS_SAMPLE_MODULE_OV(eadc) (((eadc)->STATUS1 & EADC_STATUS1_STOVF_Msk) >> EADC_STATUS1_STOVF_Pos)

/**
  * @brief Check all A/D interrupt flag overrun bits.
  * @param[in] eadc Base address of EADC module.
  * @retval 0 None of ADINT interrupt flag is overwritten to 1.
  * @retval 1 Any one of ADINT interrupt flag is overwritten to 1.
  * @details The ADOVIF bit (EADC_STATUS1[24]) will keep 1 when any one of ADINT interrupt flag ADFOVn (EADC_ADIFOV[3:0]) is overwritten to 1.
  * \hideinitializer
  */
#define EADC_IS_INT_FLAG_OV(eadc) (((eadc)->STATUS1 & EADC_STATUS1_ADOVIF_Msk) >> EADC_STATUS1_ADOVIF_Pos)

/**
  * @brief Get the busy state of EADC.
  * @param[in] eadc Base address of EADC module.
  * @param[in] converter Which converter, it should be 0 or 1.
  * @retval 0 Idle state.
  * @retval 1 Busy state.
  * @details This macro is used to read BUSY0(EADC_STATUS1[8]) or BUSY1(EADC_STATUS1[16]) to get busy state.
  * \hideinitializer
  */
#define EADC_IS_BUSY(eadc, converter) (((((eadc)->STATUS1 >> (EADC_STATUS1_BUSY0_Pos + (8 * converter)))) & EADC_STATUS1_BUSY0_Msk) )

/**
  * @brief Configure the comparator 0 and enable it.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32ModuleNum specifies the compare sample module, valid values are:
  *                            - \ref CMP_EADC0_SAMPLE_MODULE0  : EADC0 SAMPLE module 0
  *                            - \ref CMP_EADC0_SAMPLE_MODULE1  : EADC0 SAMPLE module 1
  *                            - \ref CMP_EADC0_SAMPLE_MODULE2  : EADC0 SAMPLE module 2
  *                            - \ref CMP_EADC0_SAMPLE_MODULE3  : EADC0 SAMPLE module 3
  *                            - \ref CMP_EADC1_SAMPLE_MODULE0  : EADC1 SAMPLE module 0
  *                            - \ref CMP_EADC1_SAMPLE_MODULE1  : EADC1 SAMPLE module 1
  *                            - \ref CMP_EADC1_SAMPLE_MODULE2  : EADC1 SAMPLE module 2
  *                            - \ref CMP_EADC1_SAMPLE_MODULE3  : EADC1 SAMPLE module 3
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
                         u32MatchCount) ((eadc)->CMP[0] |=(((u32ModuleNum) << EADC_CMP0_CMPSPL_Pos)|\
                                                            (u32Condition) |\
                                                            ((u16CMPData) << EADC_CMP0_CMPDAT_Pos)| \
                                                            (((u32MatchCount) - 1) << EADC_CMP0_CMPMCNT_Pos)|\
                                                            EADC_CMP0_ADCMPEN_Msk))

/**
  * @brief Configure the comparator 1 and enable it.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32ModuleNum specifies the compare sample module, valid values are:
  *                            - \ref CMP_EADC0_SAMPLE_MODULE0  : EADC0 SAMPLE module 0
  *                            - \ref CMP_EADC0_SAMPLE_MODULE1  : EADC0 SAMPLE module 1
  *                            - \ref CMP_EADC0_SAMPLE_MODULE2  : EADC0 SAMPLE module 2
  *                            - \ref CMP_EADC0_SAMPLE_MODULE3  : EADC0 SAMPLE module 3
  *                            - \ref CMP_EADC1_SAMPLE_MODULE0  : EADC1 SAMPLE module 0
  *                            - \ref CMP_EADC1_SAMPLE_MODULE1  : EADC1 SAMPLE module 1
  *                            - \ref CMP_EADC1_SAMPLE_MODULE2  : EADC1 SAMPLE module 2
  *                            - \ref CMP_EADC1_SAMPLE_MODULE3  : EADC1 SAMPLE module 3
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
                         u32MatchCount) ((eadc)->CMP[1] |=(((u32ModuleNum) << EADC_CMP1_CMPSPL_Pos)|\
                                                            (u32Condition) |\
                                                            ((u16CMPData) << EADC_CMP1_CMPDAT_Pos)| \
                                                            (((u32MatchCount) - 1) << EADC_CMP1_CMPMCNT_Pos)|\
                                                            EADC_CMP1_ADCMPEN_Msk))

/**
  * @brief Enable the compare interrupt.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32CMP Specifies the compare register, valid value are 0 and 1.
  * @return None
  * @details If the compare function is enabled and the compare condition matches the setting of CMPCOND (EADC_CMPn[2], n=0~1)
  *         and CMPMCNT (EADC_CMPn[11:8], n=0~1), ADCMPFn (EADC_STATUS1[7:6], n=0~1) will be asserted, in the meanwhile,
  *         if ADCMPIE is set to 1, a compare interrupt request is generated.
  * \hideinitializer
  */
#define EADC_ENABLE_CMP_INT(eadc, u32CMP) ((eadc)->CMP[(u32CMP)] |= EADC_CMP0_ADCMPIE_Msk)

/**
  * @brief Disable the compare interrupt.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32CMP Specifies the compare register, valid value are 0 and 1.
  * @return None
  * @details This macro is used to disable the compare interrupt.
  * \hideinitializer
  */
#define EADC_DISABLE_CMP_INT(eadc, u32CMP) ((eadc)->CMP[(u32CMP)] &= ~EADC_CMP0_ADCMPIE_Msk)

/**
  * @brief Disable comparator 0.
  * @param[in] eadc Base address of EADC module.
  * @return None
  * @details This macro is used to disable comparator 0.
  * \hideinitializer
  */
#define EADC_DISABLE_CMP0(eadc) ((eadc)->CMP[0] = 0)

/**
  * @brief Disable comparator 1.
  * @param[in] eadc Base address of EADC module.
  * @return None
  * @details This macro is used to disable comparator 1.
  * \hideinitializer
  */
#define EADC_DISABLE_CMP1(eadc) ((eadc)->CMP[1] = 0)

/**
  * @brief Enable simultaneous mode.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32ModuleMask The combination of sample module. Each bit corresponds to a sample module.
  *                         This parameter decides which sample module will be set to simultaneous mode, valid range are between 1~0xFF.
  *                         Bit 0 is sample module 0, bit 1 is sample module 1..., bit 7 is sample module 7.
  * @return None
  * @details This macro is used to set selected sample modules to be simultaneous mode.
  * \hideinitializer
  */
#define EADC_ENABLE_SIMULTANEOUS(eadc,u32ModuleMask) ((eadc)->SIMUSEL |= (u32ModuleMask))

/**
  * @brief Disable simultaneous mode.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32ModuleMask The combination of sample module. Each bit corresponds to a sample module.
  *                         This parameter decides which sample module will be set to disable simultaneous mode, valid range are between 1~0xFF.
  *                         Bit 0 is sample module 0, bit 1 is sample module 1..., bit 7 is sample module 7.
  * @return None
  * @details This macro is used to set selected sample modules to disable simultaneous mode.
  * \hideinitializer
  */
#define EADC_DISABLE_SIMULTANEOUS(eadc,u32ModuleMask) ((eadc)->SIMUSEL &= ~(u32ModuleMask))

/**
  * @brief Enable PWM and EPWM trigger trigger EADC condition.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32ADTriggerModuleNum Decides the sample module number, valid values are:
  *                            - \ref EADC0_TRIGGEREN0      : AD trigger condition for SAMPLE00
  *                            - \ref EADC0_TRIGGEREN1      : AD trigger condition for SAMPLE01
  *                            - \ref EADC0_TRIGGEREN2      : AD trigger condition for SAMPLE02
  *                            - \ref EADC0_TRIGGEREN3      : AD trigger condition for SAMPLE03
  *                            - \ref EADC1_TRIGGEREN0      : AD trigger condition for SAMPLE10
  *                            - \ref EADC1_TRIGGEREN1      : AD trigger condition for SAMPLE11
  *                            - \ref EADC1_TRIGGEREN2      : AD trigger condition for SAMPLE12
  *                            - \ref EADC1_TRIGGEREN3      : AD trigger condition for SAMPLE13
  * @param[in] u32TriggerMask Decides the PWM and EPWM trigger EADC condition, valid range are between 0~0xFFFFFFFF.
  * @return None
  * @details This macro is used to enable PWM and EPWM trigger EADC condition.
  */
#define EADC_EnablePWMTriggerCondition(eadc,u32ADTriggerModuleNum,u32TriggerMask) (*(__IO uint32_t *)(&(eadc)->AD0TRGEN0 + (u32ADTriggerModuleNum)) |= (u32TriggerMask))

/**
  * @brief Disable PWM and EPWM trigger trigger EADC condition.
  * @param[in] eadc Base address of EADC module.
  * @param[in] u32ADTriggerModuleNum Decides the sample module number, valid values are:
  *                            - \ref EADC0_TRIGGEREN0      : AD trigger condition for SAMPLE00
  *                            - \ref EADC0_TRIGGEREN1      : AD trigger condition for SAMPLE01
  *                            - \ref EADC0_TRIGGEREN2      : AD trigger condition for SAMPLE02
  *                            - \ref EADC0_TRIGGEREN3      : AD trigger condition for SAMPLE03
  *                            - \ref EADC1_TRIGGEREN0      : AD trigger condition for SAMPLE10
  *                            - \ref EADC1_TRIGGEREN1      : AD trigger condition for SAMPLE11
  *                            - \ref EADC1_TRIGGEREN2      : AD trigger condition for SAMPLE12
  *                            - \ref EADC1_TRIGGEREN3      : AD trigger condition for SAMPLE13
  * @param[in] u32TriggerMask Decides the PWM and EPWM trigger EADC condition, valid range are between 0~0xFFFFFFFF.
  * @return None
  * @details This macro is used to disable PWM and EPWM trigger EADC condition.
  */
#define EADC_DisablePWMTriggerCondition(eadc,u32ADTriggerModuleNum,u32TriggerMask) (*(__IO uint32_t *)(&(eadc)->AD0TRGEN0 + (u32ADTriggerModuleNum)) |= (u32TriggerMask))

/*---------------------------------------------------------------------------------------------------------*/
/* Define EADC functions prototype                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
void EADC_Open(EADC_T *eadc, uint32_t u32InputMode);
void EADC_Close(EADC_T *eadc);
void EADC_ConfigSampleModule(EADC_T *eadc, \
                             uint32_t u32ModuleNum, \
                             uint32_t u32TriggerSource, \
                             uint32_t u32Channel);
void EADC_SetTriggerDelayTime(EADC_T *eadc, \
                              uint32_t u32ModuleNum, \
                              uint32_t u32TriggerDelayTime, \
                              uint32_t u32DelayClockDivider);
void EADC_SetExtendSampleTime(EADC_T *eadc, uint32_t u32ModuleNum, uint32_t u32ExtendSampleTime);

/*@}*/ /* end of group NUC472_442_EADC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_EADC_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */


#ifdef __cplusplus
}
#endif

#endif //__EADC_H__

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
