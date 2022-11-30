/*
 * Copyright 2018-2021, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FSL_ANACTRL_H__
#define __FSL_ANACTRL_H__

#include "fsl_common.h"

/*!
 * @addtogroup anactrl
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief ANACTRL driver version. */
#define FSL_ANACTRL_DRIVER_VERSION (MAKE_VERSION(2, 3, 0)) /*!< Version 2.3.0. */`

/*!
 * @brief ANACTRL interrupt flags
 */
enum _anactrl_interrupt_flags
{
#if (defined(FSL_FEATURE_ANACTRL_CONTROL_VDD_MAIN) && FSL_FEATURE_ANACTRL_CONTROL_VDD_MAIN)
    kANACTRL_BodVDDMainFlag = ANACTRL_BOD_DCDC_INT_STATUS_BODVDDMAIN_STATUS_MASK, /*!< BOD VDDMAIN Interrupt status
                                                                               before Interrupt Enable. */
    kANACTRL_BodVDDMainInterruptFlag =
        ANACTRL_BOD_DCDC_INT_STATUS_BODVDDMAIN_INT_STATUS_MASK,                     /*!< BOD VDDMAIN Interrupt status
                                                                                 after Interrupt Enable. */
    kANACTRL_BodVDDMainPowerFlag = ANACTRL_BOD_DCDC_INT_STATUS_BODVDDMAIN_VAL_MASK, /*!< Current value of BOD VDDMAIN
                                                                                   power status output. */
#else
    kANACTRL_BodVbatFlag = ANACTRL_BOD_DCDC_INT_STATUS_BODVBAT_STATUS_MASK, /*!< BOD VBAT Interrupt status before
                                                                                Interrupt Enable. */
    kANACTRL_BodVbatInterruptFlag = ANACTRL_BOD_DCDC_INT_STATUS_BODVBAT_INT_STATUS_MASK, /*!< BOD VBAT Interrupt status
                                                                                            after Interrupt Enable. */
    kANACTRL_BodVbatPowerFlag = ANACTRL_BOD_DCDC_INT_STATUS_BODVBAT_VAL_MASK, /*!< Current value of BOD VBAT power
                                                                                    status output. */
#endif /* defined(FSL_FEATURE_ANACTRL_CONTROL_VDD_MAIN) && FSL_FEATURE_ANACTRL_CONTROL_VDD_MAIN */
    kANACTRL_BodCoreFlag = ANACTRL_BOD_DCDC_INT_STATUS_BODCORE_STATUS_MASK, /*!< BOD CORE Interrupt status before
                                                                                Interrupt Enable. */
    kANACTRL_BodCoreInterruptFlag = ANACTRL_BOD_DCDC_INT_STATUS_BODCORE_INT_STATUS_MASK, /*!< BOD CORE Interrupt status
                                                                                            after Interrupt Enable. */
    kANACTRL_BodCorePowerFlag = ANACTRL_BOD_DCDC_INT_STATUS_BODCORE_VAL_MASK,      /*!< Current value of BOD CORE power
                                                                                         status output. */
    kANACTRL_DcdcFlag = ANACTRL_BOD_DCDC_INT_STATUS_DCDC_STATUS_MASK,              /*!< DCDC Interrupt status before
                                                                                         Interrupt Enable. */
    kANACTRL_DcdcInterruptFlag = ANACTRL_BOD_DCDC_INT_STATUS_DCDC_INT_STATUS_MASK, /*!< DCDC Interrupt status after
                                                                                        Interrupt Enable. */
    kANACTRL_DcdcPowerFlag = ANACTRL_BOD_DCDC_INT_STATUS_DCDC_VAL_MASK,            /*!< Current value of DCDC power
                                                                                       status output. */
};

/*!
 * @brief ANACTRL interrupt control
 */
enum _anactrl_interrupt
{
#if (defined(FSL_FEATURE_ANACTRL_CONTROL_VDD_MAIN) && FSL_FEATURE_ANACTRL_CONTROL_VDD_MAIN)
    kANACTRL_BodVDDMainInterruptEnable = ANACTRL_BOD_DCDC_INT_CTRL_BODVDDMAIN_INT_ENABLE_MASK, /*!< BOD VDDMAIN
                                                                                            interrupt control. */
#else
    kANACTRL_BodVbatInterruptEnable = ANACTRL_BOD_DCDC_INT_CTRL_BODVBAT_INT_ENABLE_MASK, /*!< BOD VBAT interrupt
                                                                                            control. */
#endif /* defined(FSL_FEATURE_ANACTRL_CONTROL_VDD_MAIN) && FSL_FEATURE_ANACTRL_CONTROL_VDD_MAIN */
    kANACTRL_BodCoreInterruptEnable = ANACTRL_BOD_DCDC_INT_CTRL_BODCORE_INT_ENABLE_MASK, /*!< BOD CORE interrupt
                                                                                            control. */
    kANACTRL_DcdcInterruptEnable = ANACTRL_BOD_DCDC_INT_CTRL_DCDC_INT_ENABLE_MASK,       /*!< DCDC interrupt control. */
};

/*!
 * @brief ANACTRL status flags
 */
enum _anactrl_flags
{
    kANACTRL_FlashPowerDownFlag = ANACTRL_ANALOG_CTRL_STATUS_FLASH_PWRDWN_MASK,     /*!< Flash power-down status. */
    kANACTRL_FlashInitErrorFlag = ANACTRL_ANALOG_CTRL_STATUS_FLASH_INIT_ERROR_MASK, /*!< Flash initialization
                                                                                          error status. */
};

/*!
 * @brief ANACTRL FRO192M and XO32M status flags
 */
enum _anactrl_osc_flags
{
    kANACTRL_OutputClkValidFlag      = ANACTRL_FRO192M_STATUS_CLK_VALID_MASK,  /*!< Output clock valid signal. */
    kANACTRL_CCOThresholdVoltageFlag = ANACTRL_FRO192M_STATUS_ATB_VCTRL_MASK,  /*!< CCO threshold voltage detector
                                                                                     output (signal vcco_ok). */
    kANACTRL_XO32MOutputReadyFlag = ANACTRL_XO32M_STATUS_XO_READY_MASK << 16U, /*!< Indicates XO out
                                                                                    frequency statibilty. */
};

/*!
 * @brief Configuration for FRO192M
 *
 * This structure holds the configuration settings for the on-chip high-speed Free Running Oscillator. To initialize
 * this structure to reasonable defaults, call the ANACTRL_GetDefaultFro192MConfig() function and pass a
 * pointer to your config structure instance.
 */
typedef struct _anactrl_fro192M_config
{
    bool enable12MHzClk; /*!< Enable 12MHz clock. */
    bool enable96MHzClk; /*!< Enable 96MHz clock. */
} anactrl_fro192M_config_t;

/*!
 * @brief Configuration for XO32M
 *
 * This structure holds the configuration settings for the 32 MHz crystal oscillator. To initialize this
 * structure to reasonable defaults, call the ANACTRL_GetDefaultXo32MConfig() function and pass a
 * pointer to your config structure instance.
 */
typedef struct _anactrl_xo32M_config
{
    bool enableACBufferBypass; /*!< Enable XO AC buffer bypass in pll and top level. */
#if !(defined(FSL_FEATURE_ANACTRL_HAS_NO_ENABLE_PLL_USB_OUT_BIT_FIELD) && \
      FSL_FEATURE_ANACTRL_HAS_NO_ENABLE_PLL_USB_OUT_BIT_FIELD)
    bool enablePllUsbOutput; /*!< Enable XO 32 MHz output to USB HS PLL. */
#endif                       /* FSL_FEATURE_ANACTRL_HAS_NO_ENABLE_PLL_USB_OUT_BIT_FIELD */
    bool enableSysCLkOutput; /*!< Enable XO 32 MHz output to CPU system, SCT, and CLKOUT */
#if (defined(FSL_FEATURE_ANACTRL_HAS_XO32M_ADC_CLK_MODE_BIF_FIELD) && \
     FSL_FEATURE_ANACTRL_HAS_XO32M_ADC_CLK_MODE_BIF_FIELD)
    bool enableADCOutput; /*!< Enable High speed crystal oscillator output to ADC. */
#endif                    /* FSL_FEATURE_ANACTRL_HAS_XO32M_ADC_CLK_MODE_BIF_FIELD */
} anactrl_xo32M_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initializes the ANACTRL mode, the module's clock will be enabled by invoking this function.
 *
 * @param base ANACTRL peripheral base address.
 */
void ANACTRL_Init(ANACTRL_Type *base);

/*!
 * @brief De-initializes ANACTRL module, the module's clock will be disabled by invoking this function.
 *
 * @param base ANACTRL peripheral base address.
 */
void ANACTRL_Deinit(ANACTRL_Type *base);
/* @} */

/*!
 * @name Set oscillators
 * @{
 */

/*!
 * @brief Configs the on-chip high-speed Free Running Oscillator(FRO192M), such as enabling/disabling 12 MHZ clock
 * output and enable/disable 96MHZ clock output.
 *
 * @param base ANACTRL peripheral base address.
 * @param config Pointer to FRO192M configuration structure. Refer to @ref anactrl_fro192M_config_t structure.
 */
void ANACTRL_SetFro192M(ANACTRL_Type *base, const anactrl_fro192M_config_t *config);

/*!
 * @brief Gets the default configuration of FRO192M.
 * The default values are:
 * @code
    config->enable12MHzClk = true;
    config->enable96MHzClk = false;
    @endcode
 * @param config Pointer to FRO192M configuration structure. Refer to @ref anactrl_fro192M_config_t structure.
 */
void ANACTRL_GetDefaultFro192MConfig(anactrl_fro192M_config_t *config);

/*!
 * @brief Configs the 32 MHz Crystal oscillator(High-speed crystal oscillator), such as enable/disable output to CPU
 * system, and so on.
 *
 * @param base ANACTRL peripheral base address.
 * @param config Pointer to XO32M configuration structure. Refer to @ref anactrl_xo32M_config_t structure.
 */
void ANACTRL_SetXo32M(ANACTRL_Type *base, const anactrl_xo32M_config_t *config);

/*!
 * @brief Gets the default configuration of XO32M.
 * The default values are:
 * @code
    config->enableSysCLkOutput = false;
    config->enableACBufferBypass = false;
    @endcode
 * @param config Pointer to XO32M configuration structure. Refer to @ref anactrl_xo32M_config_t structure.
 */
void ANACTRL_GetDefaultXo32MConfig(anactrl_xo32M_config_t *config);

/* @} */

#if !(defined(FSL_FEATURE_ANACTRL_HAS_NO_FREQ_ME_CTRL) && FSL_FEATURE_ANACTRL_HAS_NO_FREQ_ME_CTRL)
/*!
 * @name Measure Frequency
 * @{
 */

/*!
 * @brief Measures the frequency of the target clock source.
 *
 * This function measures target frequency according to a accurate reference frequency.The formula is:
 * Ftarget = (CAPVAL * Freference) / ((1<<SCALE)-1)
 *
 * @note Both tartget and reference clocks are selectable by programming the target clock select FREQMEAS_TARGET
 * register in INPUTMUX and reference clock select FREQMEAS_REF register in INPUTMUX.
 *
 * @param base ANACTRL peripheral base address.
 * @param scale Define the power of 2 count that ref counter counts to during measurement, ranges from 2 to 31.
 * @param refClkFreq frequency of the reference clock.
 *
 * @return frequency of the target clock.
 */
uint32_t ANACTRL_MeasureFrequency(ANACTRL_Type *base, uint8_t scale, uint32_t refClkFreq);
/* @} */
#endif /* FSL_FEATURE_ANACTRL_HAS_NO_FREQ_ME_CTRL */

/*!
 * @name Interrupt Interface
 * @{
 */

/*!
 * @brief Enables the ANACTRL interrupts.
 *
 * @param base ANACTRL peripheral base address.
 * @param mask The interrupt mask. Refer to "_anactrl_interrupt" enumeration.
 */
static inline void ANACTRL_EnableInterrupts(ANACTRL_Type *base, uint32_t mask)
{
    base->BOD_DCDC_INT_CTRL |= (0x15U & mask);
}

/*!
 * @brief Disables the ANACTRL interrupts.
 *
 * @param base ANACTRL peripheral base address.
 * @param mask The interrupt mask. Refer to "_anactrl_interrupt" enumeration.
 */
static inline void ANACTRL_DisableInterrupts(ANACTRL_Type *base, uint32_t mask)
{
    base->BOD_DCDC_INT_CTRL &= ~(0x15U & mask);
}

/*!
 * @brief Clears the ANACTRL interrupts.
 *
 * @param base ANACTRL peripheral base address.
 * @param mask The interrupt mask. Refer to "_anactrl_interrupt" enumeration.
 */
static inline void ANACTRL_ClearInterrupts(ANACTRL_Type *base, uint32_t mask)
{
    base->BOD_DCDC_INT_CTRL |= (uint32_t)(mask << 1UL);
}
/* @} */

/*!
 * @name Status Interface
 * @{
 */

/*!
 * @brief Gets ANACTRL status flags.
 *
 * This function gets Analog control status flags. The flags are returned as the logical
 * OR value of the enumerators @ref _anactrl_flags. To check for a specific status,
 * compare the return value with enumerators in the @ref _anactrl_flags.
 * For example, to check whether the flash is in power down mode:
 * @code
 *     if (kANACTRL_FlashPowerDownFlag & ANACTRL_ANACTRL_GetStatusFlags(ANACTRL))
 *     {
 *         ...
 *     }
 * @endcode
 *
 * @param base ANACTRL peripheral base address.
 * @return ANACTRL status flags which are given in the enumerators in the @ref _anactrl_flags.
 */
static inline uint32_t ANACTRL_GetStatusFlags(ANACTRL_Type *base)
{
    return base->ANALOG_CTRL_STATUS;
}

/*!
 * @brief Gets ANACTRL oscillators status flags.
 *
 * This function gets Anactrl oscillators status flags. The flags are returned as the logical
 * OR value of the enumerators @ref _anactrl_osc_flags. To check for a specific status,
 * compare the return value with enumerators in the @ref _anactrl_osc_flags.
 * For example, to check whether the FRO192M clock output is valid:
 * @code
 *     if (kANACTRL_OutputClkValidFlag & ANACTRL_ANACTRL_GetOscStatusFlags(ANACTRL))
 *     {
 *         ...
 *     }
 * @endcode
 *
 * @param base ANACTRL peripheral base address.
 * @return ANACTRL oscillators status flags which are given in the enumerators in the @ref _anactrl_osc_flags.
 */
static inline uint32_t ANACTRL_GetOscStatusFlags(ANACTRL_Type *base)
{
    return (base->FRO192M_STATUS & 0xFFU) | ((base->XO32M_STATUS & 0xFFU) << 16U);
}

/*!
 * @brief Gets ANACTRL interrupt status flags.
 *
 * This function gets Anactrl interrupt status flags. The flags are returned as the logical
 * OR value of the enumerators @ref _anactrl_interrupt_flags. To check for a specific status,
 * compare the return value with enumerators in the @ref _anactrl_interrupt_flags.
 * For example, to check whether the VBAT voltage level is above the threshold:
 * @code
 *     if (kANACTRL_BodVbatPowerFlag & ANACTRL_ANACTRL_GetInterruptStatusFlags(ANACTRL))
 *     {
 *         ...
 *     }
 * @endcode
 *
 * @param base ANACTRL peripheral base address.
 * @return ANACTRL oscillators status flags which are given in the enumerators in the @ref _anactrl_osc_flags.
 */
static inline uint32_t ANACTRL_GetInterruptStatusFlags(ANACTRL_Type *base)
{
    return base->BOD_DCDC_INT_STATUS & 0x1FFU;
}
/* @} */

#if (defined(FSL_FEATURE_ANACTRL_HAS_AUX_BIAS_REG) && (FSL_FEATURE_ANACTRL_HAS_AUX_BIAS_REG == 1U))
/*!
 * @brief Aux_Bias Control Interfaces
 * @{
 */

/*!
 * @brief Enables/disabless 1V reference voltage buffer.
 *
 * @param base ANACTRL peripheral base address.
 * @param enable Used to enable or disable 1V reference voltage buffer.
 */
static inline void ANACTRL_EnableVref1V(ANACTRL_Type *base, bool enable)
{
    if (enable)
    {
        base->AUX_BIAS |= ANACTRL_AUX_BIAS_VREF1VENABLE_MASK;
    }
    else
    {
        base->AUX_BIAS &= ~ANACTRL_AUX_BIAS_VREF1VENABLE_MASK;
    }
}

/* @} */
#endif /* defined(FSL_FEATURE_ANACTRL_HAS_AUX_BIAS_REG) */

#if defined(__cplusplus)
}
#endif

/* @}*/

#endif /* __FSL_ANACTRL_H__ */
