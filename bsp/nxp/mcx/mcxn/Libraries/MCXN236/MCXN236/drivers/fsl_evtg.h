/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_EVTG_H_
#define FSL_EVTG_H_

#include "fsl_common.h"

/*!
 * @addtogroup evtg
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief EVTG driver version. */
#define FSL_EVTG_DRIVER_VERSION (MAKE_VERSION(2, 0, 1)) /*!< Version 2.0.1. */
/*@}*/

/*! @brief EVTG instance index. */
typedef enum _evtg_index
{
    kEVTG_Index0 = 0x0U, /*!< EVTG instance index 0. */
    kEVTG_Index1,        /*!< EVTG instance index 1. */
    kEVTG_Index2,        /*!< EVTG instance index 2. */
    kEVTG_Index3,        /*!< EVTG instance index 3. */
} evtg_index_t;

/*! @brief EVTG input index. */
typedef enum _evtg_input_index
{
    kEVTG_InputA = 0x0U, /*!< EVTG input A. */
    kEVTG_InputB,        /*!< EVTG input B. */
    kEVTG_InputC,        /*!< EVTG input C. */
    kEVTG_InputD,        /*!< EVTG input D. */
} evtg_input_index_t;

/*! @brief EVTG AOI index. */
typedef enum _evtg_aoi_index
{
    kEVTG_AOI0 = 0x0U, /*!< EVTG AOI index 0. */
    kEVTG_AOI1 = 0x1U, /*!< EVTG AOI index 1. */
} evtg_aoi_index_t;

/*! @brief EVTG AOI product term index. */
typedef enum _evtg_aoi_product_term
{
    kEVTG_ProductTerm0 = 0x0U, /*!< EVTG AOI product term index 0. */
    kEVTG_ProductTerm1,        /*!< EVTG AOI product term index 1. */
    kEVTG_ProductTerm2,        /*!< EVTG AOI product term index 2. */
    kEVTG_ProductTerm3,        /*!< EVTG AOI product term index 3. */
} evtg_aoi_product_term_t;

/*! @brief EVTG input configuration. */
typedef enum _evtg_aoi_input_config
{
    kEVTG_InputLogicZero = 0x0U, /*!< Force input in product term to a logical zero. */
    kEVTG_InputDirectPass,       /*!< Pass input in product term. */
    kEVTG_InputComplement,       /*!< Complement input in product term. */
    kEVTG_InputLogicOne,         /*!< Force input in product term to a logical one. */
} evtg_aoi_input_config_t;

/*! @brief EVTG AOI Output Filter Sample Count. */
typedef enum _evtg_aoi_outfilter_count
{
    kEVTG_AOIOutFilterSampleCount3 = 0x0U, /*!< EVTG AOI output filter sample count is 3. */
    kEVTG_AOIOutFilterSampleCount4,        /*!< EVTG AOI output filter sample count is 4. */
    kEVTG_AOIOutFilterSampleCount5,        /*!< EVTG AOI output filter sample count is 5. */
    kEVTG_AOIOutFilterSampleCount6,        /*!< EVTG AOI output filter sample count is 6. */
    kEVTG_AOIOutFilterSampleCount7,        /*!< EVTG AOI output filter sample count is 7. */
    kEVTG_AOIOutFilterSampleCount8,        /*!< EVTG AOI output filter sample count is 8. */
    kEVTG_AOIOutFilterSampleCount9,        /*!< EVTG AOI output filter sample count is 9. */
    kEVTG_AOIOutFilterSampleCount10,       /*!< EVTG AOI output filter sample count is 10. */
} evtg_aoi_outfilter_count_t;

/*!
 * @brief EVTG output feedback override control mode. When FF is configured as JK-FF mode,
 *        need EVTG_OUTA feedback to EVTG input and replace one of the four inputs.
 */
typedef enum _evtg_outfdbk_override_input
{
    kEVTG_OutputOverrideInputA = 0x0U, /*!< Replace input A. */
    kEVTG_OutputOverrideInputB,        /*!< Replace input B. */
    kEVTG_OutputOverrideInputC,        /*!< Replace input C. */
    kEVTG_OutputOverrideInputD,        /*!< Replace input D. */
} evtg_outfdbk_override_input_t;

/*! @brief EVTG flip flop mode configuration. */
typedef enum _evtg_flipflop_mode
{
    kEVTG_FFModeBypass = 0x0U, /*!< Bypass mode (default).In this mode, user can choose to enable
                                   or disable input sync logic and filter function. */
    kEVTG_FFModeRSTrigger,     /*!< RS trigger mode. In this mode, user can choose to enable
                                   or disable input sync logic and filter function. */
    kEVTG_FFModeTFF,           /*!< T-FF mode. In this mode, input sync or filter has to be enabled
                                   to remove the possible glitch.*/
    kEVTG_FFModeDFF,           /*!< D-FF mode. In this mode, input sync or filter has to be enabled
                                   to remove the possible glitch.*/
    kEVTG_FFModeJKFF,          /*!< JK-FF mode. In this mode, input sync or filter has to be enabled
                                   to remove the possible glitch.*/
    kEVTG_FFModeLatch,         /*!< Latch mode. In this mode, input sync or filter has to be enabled
                                   to remove the possible glitch.*/
} evtg_flipflop_mode_t;

/*! @brief EVTG flip-flop initial value. */
typedef enum _evtg_flipflop_init_output
{
    kEVTG_FFInitOut0 = 0x0U, /*!< Configure the positive output of flip-flop as 0. */
    kEVTG_FFInitOut1 = 0x1U, /*!< Configure the positive output of flip-flop as 1. */
} evtg_flipflop_init_output_t;

/*! @brief The structure for configuring an AOI output filter sample.
 *
 * AOI output filter sample count represent the number of consecutive samples that must agree prior to the AOI output
 * filter accepting an transition.
 * AOI output filter sample period represent the sampling period (in IP bus clock cycles) of the AOI output signals.
 * Each AOI output is sampled multiple times at the rate specified by this period.
 *
 * For the modes with Filter function enabled, filter delay is "(FILT_CNT + 3) x FILT_PER + 2".
 *
 */
typedef struct _evtg_aoi_outfilter_config
{
    evtg_aoi_outfilter_count_t sampleCount; /*!< EVTG AOI output filter sample count.
                                                refer to @ref evtg_aoi_outfilter_count_t. */
    uint8_t samplePeriod;                   /*!< EVTG AOI output filter sample period, within 0~255. If sample period
                                                 value is 0x00 (default), then the input filter is bypassed. */
} evtg_aoi_outfilter_config_t;

/*! @brief The structure for configuring an AOI product term. */
typedef struct _evtg_aoi_product_term_config
{
    evtg_aoi_input_config_t aInput; /*!< Input A configuration. */
    evtg_aoi_input_config_t bInput; /*!< Input B configuration. */
    evtg_aoi_input_config_t cInput; /*!< Input C configuration. */
    evtg_aoi_input_config_t dInput; /*!< Input D configuration. */
} evtg_aoi_product_term_config_t;

/*! @brief EVTG AOI configuration structure. */
typedef struct _evtg_aoi_config
{
    /* AOI Output Filter configuration. */
    evtg_aoi_outfilter_config_t aoiOutFilterConfig; /*!< EVTG AOI output filter sample
                                                        configuration structure. */

    /* Product term configuration. */
    evtg_aoi_product_term_config_t productTerm0; /*!< Configure AOI product term0. */
    evtg_aoi_product_term_config_t productTerm1; /*!< Configure AOI product term1. */
    evtg_aoi_product_term_config_t productTerm2; /*!< Configure AOI product term2. */
    evtg_aoi_product_term_config_t productTerm3; /*!< Configure AOI product term3. */
} evtg_aoi_config_t;

/*! @brief EVTG configuration covering all configurable fields. */
typedef struct _evtg_config
{
    /* Input configuration. */
    bool enableInputASync;                             /*!< Enable/Disable EVTG A input synchronous with bus clk. */
    bool enableInputBSync;                             /*!< Enable/Disable EVTG B input synchronous with bus clk. */
    bool enableInputCSync;                             /*!< Enable/Disable EVTG C input synchronous with bus clk. */
    bool enableInputDSync;                             /*!< Enable/Disable EVTG D input synchronous with bus clk. */
    evtg_outfdbk_override_input_t outfdbkOverideinput; /*!< EVTG output feedback to EVTG input
                                                               and replace one of the four inputs. */

    /* Flip-flop configuration. */
    evtg_flipflop_mode_t flipflopMode; /*!< Flip-Flop can be configured as one of Bypass mode, RS trigger mode,
                                               T-FF mode, D-FF mode, JK-FF mode, Latch mode. */
    bool enableFlipflopInitOutput;     /*!< Flip-flop initial output value enable/disable. */
    evtg_flipflop_init_output_t flipflopInitOutputValue; /*!< Flip-flop initial output value configuration. */

#if defined(FSL_FEATURE_EVTG_HAS_FORCE_BYPASS_FLIPFLOP) && FSL_FEATURE_EVTG_HAS_FORCE_BYPASS_FLIPFLOP
    bool enableForceBypassFlipFlopAOI0; /*!< Enable/Disable force bypass Flip-Flop and route the AOI_0(Filter_0)
                                                value directly to EVTG_OUTA */
    bool enableForceBypassFlipFlopAOI1; /*!< Enable/Disable force bypass Flip-Flop and route the AOI_1(Filter_1)
                                                value directly to EVTG_OUTB */
#endif

    /* AOI configuration. */
    evtg_aoi_config_t aoi0Config; /*!< Configure EVTG AOI0. */
    evtg_aoi_config_t aoi1Config; /*!< Configure EVTG AOI1. */
} evtg_config_t;

/*! @} */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @addtogroup evtg_driver
 * @{
 */

/*!
 * @name Initialization Interfaces
 * @{
 */

/*!
 * @brief Initialize EVTG with a user configuration structure.
 *
 * @param base      EVTG base address.
 * @param evtgIndex EVTG instance index.
 * @param psConfig  EVTG initial configuration structure pointer.
 */
void EVTG_Init(EVTG_Type *base, evtg_index_t evtgIndex, evtg_config_t *psConfig);

/*!
 * @brief Loads default values to the EVTG configuration structure.
 *
 *  The purpose of this API is to initialize the configuration structure to default value for @ref EVTG_Init()
 *  to use.
 *  The Flip-Flop can be configured as Bypass mode, RS trigger mode, T-FF mode, D-FF mode, JK-FF mode, Latch mode.
 *  Please check RM INTC chapter for more details.
 *
 * @param psConfig     EVTG initial configuration structure pointer.
 * @param flipflopMode EVTG flip flop mode. see @ ref _evtg_flipflop_mode
 */
void EVTG_GetDefaultConfig(evtg_config_t *psConfig, evtg_flipflop_mode_t flipflopMode);
/*! @} */

/*!
 * @name Force Init Flipflop Interfaces
 * @{
 */

/*!
 * @brief Force Flip-flop initial output value to be presented on flip-flop positive output.
 *
 * @param base                    EVTG base address.
 * @param evtgIndex               EVTG instance index.
 * @param flipflopInitOutputValue EVTG flip-flop initial output control.
 *                                 see @ref evtg_flipflop_init_output_t
 */
static inline void EVTG_ForceFlipflopInitOutput(EVTG_Type *base,
                                                evtg_index_t evtgIndex,
                                                evtg_flipflop_init_output_t flipflopInitOutputValue)
{
    base->EVTG_INST[(uint8_t)evtgIndex].EVTG_CTRL &= (~(uint16_t)EVTG_EVTG_INST_EVTG_CTRL_FF_INIT_MASK);
    base->EVTG_INST[(uint8_t)evtgIndex].EVTG_CTRL |=
        EVTG_EVTG_INST_EVTG_CTRL_FF_INIT((uint16_t)flipflopInitOutputValue);
    /* INIT_EN bit should be set after FF_INIT is set. */
    base->EVTG_INST[(uint8_t)evtgIndex].EVTG_CTRL |= EVTG_EVTG_INST_EVTG_CTRL_INIT_EN_MASK;
}
/*! @} */

/*!
 * @name Input Interfaces
 * @{
 */
/*!
 * @brief Configure each input value of AOI product term. Each selected input term in
 *        each product term can be configured to produce a logical 0 or 1 or pass the
 *        true or complement of the selected event input. Adapt to some simple aoi
 *        expressions.
 *
 * @param base        EVTG base address.
 * @param evtgIndex   EVTG instance index.
 * @param aoiIndex    EVTG AOI index. see enum ref evtg_aoi_index_t
 * @param productTerm EVTG product term index.
 * @param inputIndex  EVTG input index.
 * @param input       EVTG input configuration with enum @ref evtg_aoi_input_config_t.
 */
static inline void EVTG_SetProductTermInput(EVTG_Type *base,
                                            evtg_index_t evtgIndex,
                                            evtg_aoi_index_t aoiIndex,
                                            evtg_aoi_product_term_t productTerm,
                                            evtg_input_index_t inputIndex,
                                            evtg_aoi_input_config_t input)
{
    if (kEVTG_AOI0 == aoiIndex)
    {
        if ((productTerm == kEVTG_ProductTerm0) || (productTerm == kEVTG_ProductTerm1))
        {
            base->EVTG_INST[(uint8_t)evtgIndex].EVTG_AOI0_BFT01 &=
                (uint16_t)(~(3UL << ((3U - ((uint8_t)inputIndex)) * 2U + (((3U - (uint8_t)productTerm) % 2U) * 8U))));
            base->EVTG_INST[(uint8_t)evtgIndex].EVTG_AOI0_BFT01 |=
                ((((uint16_t)(input)) << ((3U - ((uint8_t)inputIndex)) * 2U +
                                          (((3U - (uint8_t)productTerm) % 2U) * 8U))) &
                 (uint16_t)(3UL << ((3U - ((uint8_t)inputIndex)) * 2U + (((3U - (uint8_t)productTerm) % 2U) * 8U))));
        }
        else
        {
            base->EVTG_INST[(uint8_t)evtgIndex].EVTG_AOI0_BFT23 &=
                (uint16_t)(~(3UL << ((3U - ((uint8_t)inputIndex)) * 2U + (((3U - (uint8_t)productTerm) % 2U) * 8U))));
            base->EVTG_INST[(uint8_t)evtgIndex].EVTG_AOI0_BFT23 |=
                ((((uint16_t)(input)) << ((3U - ((uint8_t)inputIndex)) * 2U +
                                          (((3U - (uint8_t)productTerm) % 2U) * 8U))) &
                 (uint16_t)(3UL << ((3U - ((uint8_t)inputIndex)) * 2U + (((3U - (uint8_t)productTerm) % 2U) * 8U))));
        }
    }
    else if (kEVTG_AOI1 == aoiIndex)
    {
        if ((productTerm == kEVTG_ProductTerm0) || (productTerm == kEVTG_ProductTerm1))
        {
            base->EVTG_INST[(uint8_t)evtgIndex].EVTG_AOI1_BFT01 &=
                (uint16_t)(~(3UL << ((3U - ((uint8_t)inputIndex)) * 2U + (((3U - (uint8_t)productTerm) % 2U) * 8U))));
            base->EVTG_INST[(uint8_t)evtgIndex].EVTG_AOI1_BFT01 |=
                ((((uint16_t)(input)) << ((3U - ((uint8_t)inputIndex)) * 2U +
                                          (((3U - (uint8_t)productTerm) % 2U) * 8U))) &
                 (uint16_t)(3UL << ((3U - ((uint8_t)inputIndex)) * 2U + (((3U - (uint8_t)productTerm) % 2U) * 8U))));
        }
        else
        {
            base->EVTG_INST[(uint8_t)evtgIndex].EVTG_AOI1_BFT23 &=
                (uint16_t)(~(3UL << ((3U - ((uint8_t)inputIndex)) * 2U + (((3U - (uint8_t)productTerm) % 2U) * 8U))));
            base->EVTG_INST[(uint8_t)evtgIndex].EVTG_AOI1_BFT23 |=
                ((((uint16_t)(input)) << ((3U - ((uint8_t)inputIndex)) * 2U +
                                          (((3U - (uint8_t)productTerm) % 2U) * 8U))) &
                 (uint16_t)(3UL << ((3U - ((uint8_t)inputIndex)) * 2U + (((3U - (uint8_t)productTerm) % 2U) * 8U))));
        }
    }
    else
    {
        ; /* No action*/
    }
}

/*!
 * @brief Configure AOI product term by initializing the product term
 *        configuration structure.
 *
 * @param base                EVTG base address.
 * @param evtgIndex           EVTG instance index.
 * @param aoiIndex            EVTG AOI index. see enum @ref evtg_aoi_index_t
 * @param productTerm         EVTG AOI product term index.
 * @param psProductTermConfig Pointer to EVTG product term configuration structure.
 *                            see ref _evtg_aoi_product_term_config
 */
void EVTG_ConfigAOIProductTerm(EVTG_Type *base,
                               evtg_index_t evtgIndex,
                               evtg_aoi_index_t aoiIndex,
                               evtg_aoi_product_term_t productTerm,
                               evtg_aoi_product_term_config_t *psProductTermConfig);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_EVTG_H_ */
