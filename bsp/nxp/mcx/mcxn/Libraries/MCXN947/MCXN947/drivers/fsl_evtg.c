/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_evtg.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.evtg"
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Initialize EVTG with a user configuration structure.
 *
 * param base      EVTG base address.
 * param evtgIndex EVTG instance index.
 * param psConfig  EVTG initial configuration structure pointer.
 */
void EVTG_Init(EVTG_Type *base, evtg_index_t evtgIndex, evtg_config_t *psConfig)
{
    /* Configure Flip-Flop as expected mode. */
    base->EVTG_INST[(uint8_t)evtgIndex].EVTG_CTRL = EVTG_EVTG_INST_EVTG_CTRL_MODE_SEL((uint16_t)psConfig->flipflopMode);

    if (kEVTG_FFModeJKFF == psConfig->flipflopMode)
    {
        /* When FF Mode is configured as JK-FF mode, need EVTG_OUTA feedback to EVTG input and replace one of the four
         * inputs.*/
        base->EVTG_INST[(uint8_t)evtgIndex].EVTG_CTRL |=
            EVTG_EVTG_INST_EVTG_CTRL_FB_OVRD((uint16_t)psConfig->outfdbkOverideinput);
    }

    if (psConfig->enableFlipflopInitOutput == true)
    {
        EVTG_ForceFlipflopInitOutput(base, evtgIndex, psConfig->flipflopInitOutputValue);
    }

#if defined(FSL_FEATURE_EVTG_HAS_FORCE_BYPASS_FLIPFLOP) && FSL_FEATURE_EVTG_HAS_FORCE_BYPASS_FLIPFLOP
    base->EVTG_INST[(uint8_t)evtgIndex].EVTG_CTRL |= EVTG_EVTG_INST_EVTG_CTRL_FORCE_BYPASS(
        ((uint16_t)psConfig->enableForceBypassFlipFlopAOI1 << 1U) | (uint16_t)psConfig->enableForceBypassFlipFlopAOI0);
#endif

    /* Configure EVTG input sync. */
    base->EVTG_INST[(uint8_t)evtgIndex].EVTG_CTRL |= EVTG_EVTG_INST_EVTG_CTRL_SYNC_CTRL(
        (((uint16_t)psConfig->enableInputDSync << 3U) | ((uint16_t)psConfig->enableInputCSync << 2U) |
         ((uint16_t)psConfig->enableInputBSync << 1U) | ((uint16_t)psConfig->enableInputASync)));

    /* Configure AOI0. */
    base->EVTG_INST[(uint8_t)evtgIndex].EVTG_AOI0_BFT01 =
        (EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT0_AC((uint8_t)psConfig->aoi0Config.productTerm0.aInput) |
         EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT0_BC((uint8_t)psConfig->aoi0Config.productTerm0.bInput) |
         EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT0_CC((uint8_t)psConfig->aoi0Config.productTerm0.cInput) |
         EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT0_DC((uint8_t)psConfig->aoi0Config.productTerm0.dInput) |
         EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT1_AC((uint8_t)psConfig->aoi0Config.productTerm1.aInput) |
         EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT1_BC((uint8_t)psConfig->aoi0Config.productTerm1.bInput) |
         EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT1_CC((uint8_t)psConfig->aoi0Config.productTerm1.cInput) |
         EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT1_DC((uint8_t)psConfig->aoi0Config.productTerm1.dInput));

    base->EVTG_INST[(uint8_t)evtgIndex].EVTG_AOI0_BFT23 =
        (EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT2_AC((uint8_t)psConfig->aoi0Config.productTerm2.aInput) |
         EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT2_BC((uint8_t)psConfig->aoi0Config.productTerm2.bInput) |
         EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT2_CC((uint8_t)psConfig->aoi0Config.productTerm2.cInput) |
         EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT2_DC((uint8_t)psConfig->aoi0Config.productTerm2.dInput) |
         EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT3_AC((uint8_t)psConfig->aoi0Config.productTerm3.aInput) |
         EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT3_BC((uint8_t)psConfig->aoi0Config.productTerm3.bInput) |
         EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT3_CC((uint8_t)psConfig->aoi0Config.productTerm3.cInput) |
         EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT3_DC((uint8_t)psConfig->aoi0Config.productTerm3.dInput));

    base->EVTG_INST[(uint8_t)evtgIndex].EVTG_AOI0_FILT |=
        (EVTG_EVTG_INST_EVTG_AOI0_FILT_FILT_CNT((uint16_t)psConfig->aoi0Config.aoiOutFilterConfig.sampleCount) |
         EVTG_EVTG_INST_EVTG_AOI0_FILT_FILT_PER(psConfig->aoi0Config.aoiOutFilterConfig.samplePeriod));

    /* Configure AOI1. */
    base->EVTG_INST[(uint8_t)evtgIndex].EVTG_AOI1_BFT01 =
        (EVTG_EVTG_INST_EVTG_AOI1_BFT01_PT0_AC((uint8_t)psConfig->aoi1Config.productTerm0.aInput) |
         EVTG_EVTG_INST_EVTG_AOI1_BFT01_PT0_BC((uint8_t)psConfig->aoi1Config.productTerm0.bInput) |
         EVTG_EVTG_INST_EVTG_AOI1_BFT01_PT0_CC((uint8_t)psConfig->aoi1Config.productTerm0.cInput) |
         EVTG_EVTG_INST_EVTG_AOI1_BFT01_PT0_DC((uint8_t)psConfig->aoi1Config.productTerm0.dInput) |
         EVTG_EVTG_INST_EVTG_AOI1_BFT01_PT1_AC((uint8_t)psConfig->aoi1Config.productTerm1.aInput) |
         EVTG_EVTG_INST_EVTG_AOI1_BFT01_PT1_BC((uint8_t)psConfig->aoi1Config.productTerm1.bInput) |
         EVTG_EVTG_INST_EVTG_AOI1_BFT01_PT1_CC((uint8_t)psConfig->aoi1Config.productTerm1.cInput) |
         EVTG_EVTG_INST_EVTG_AOI1_BFT01_PT1_DC((uint8_t)psConfig->aoi1Config.productTerm1.dInput));

    base->EVTG_INST[(uint8_t)evtgIndex].EVTG_AOI1_BFT23 =
        (EVTG_EVTG_INST_EVTG_AOI1_BFT23_PT2_AC((uint8_t)psConfig->aoi1Config.productTerm2.aInput) |
         EVTG_EVTG_INST_EVTG_AOI1_BFT23_PT2_BC((uint8_t)psConfig->aoi1Config.productTerm2.bInput) |
         EVTG_EVTG_INST_EVTG_AOI1_BFT23_PT2_CC((uint8_t)psConfig->aoi1Config.productTerm2.cInput) |
         EVTG_EVTG_INST_EVTG_AOI1_BFT23_PT2_DC((uint8_t)psConfig->aoi1Config.productTerm2.dInput) |
         EVTG_EVTG_INST_EVTG_AOI1_BFT23_PT3_AC((uint8_t)psConfig->aoi1Config.productTerm3.aInput) |
         EVTG_EVTG_INST_EVTG_AOI1_BFT23_PT3_BC((uint8_t)psConfig->aoi1Config.productTerm3.bInput) |
         EVTG_EVTG_INST_EVTG_AOI1_BFT23_PT3_CC((uint8_t)psConfig->aoi1Config.productTerm3.cInput) |
         EVTG_EVTG_INST_EVTG_AOI1_BFT23_PT3_DC((uint8_t)psConfig->aoi1Config.productTerm3.dInput));

    base->EVTG_INST[(uint8_t)evtgIndex].EVTG_AOI1_FILT |=
        (EVTG_EVTG_INST_EVTG_AOI1_FILT_FILT_CNT((uint16_t)psConfig->aoi1Config.aoiOutFilterConfig.sampleCount) |
         EVTG_EVTG_INST_EVTG_AOI1_FILT_FILT_PER(psConfig->aoi1Config.aoiOutFilterConfig.samplePeriod));
}

/*!
 * brief Configure AOI product term by initializing the product term
 *       configuration structure.
 *
 * param base                EVTG base address.
 * param evtgIndex           EVTG instance index.
 * param aoiIndex            EVTG AOI index. see enum ref evtg_aoi_index_t
 * param productTerm         EVTG AOI product term index.
 * param psProductTermConfig Pointer to EVTG product term configuration structure.
 *                           see ref _evtg_product_term_config
 */
void EVTG_ConfigAOIProductTerm(EVTG_Type *base,
                               evtg_index_t evtgIndex,
                               evtg_aoi_index_t aoiIndex,
                               evtg_aoi_product_term_t productTerm,
                               evtg_aoi_product_term_config_t *psProductTermConfig)
{
    volatile uint16_t *pu16AOIPT01Config;
    volatile uint16_t *pu16AOIPT23Config;

    if (kEVTG_AOI0 == aoiIndex)
    {
        pu16AOIPT01Config = &base->EVTG_INST[(uint8_t)evtgIndex].EVTG_AOI0_BFT01;
        pu16AOIPT23Config = &base->EVTG_INST[(uint8_t)evtgIndex].EVTG_AOI0_BFT23;
    }
    else
    {
        pu16AOIPT01Config = &base->EVTG_INST[(uint8_t)evtgIndex].EVTG_AOI1_BFT01;
        pu16AOIPT23Config = &base->EVTG_INST[(uint8_t)evtgIndex].EVTG_AOI1_BFT23;
    }

    if (kEVTG_ProductTerm0 == productTerm)
    {
        *pu16AOIPT01Config &=
            ~(uint16_t)(EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT0_AC_MASK | EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT0_BC_MASK |
                        EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT0_CC_MASK | EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT0_DC_MASK);
        *pu16AOIPT01Config |= (EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT0_AC((uint8_t)psProductTermConfig->aInput) |
                               EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT0_BC((uint8_t)psProductTermConfig->bInput) |
                               EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT0_CC((uint8_t)psProductTermConfig->cInput) |
                               EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT0_DC((uint8_t)psProductTermConfig->dInput));
    }
    else if (kEVTG_ProductTerm1 == productTerm)
    {
        *pu16AOIPT01Config &=
            ~(uint16_t)(EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT1_AC_MASK | EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT1_BC_MASK |
                        EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT1_CC_MASK | EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT1_DC_MASK);
        *pu16AOIPT01Config |= (EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT1_AC((uint8_t)psProductTermConfig->aInput) |
                               EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT1_BC((uint8_t)psProductTermConfig->bInput) |
                               EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT1_CC((uint8_t)psProductTermConfig->cInput) |
                               EVTG_EVTG_INST_EVTG_AOI0_BFT01_PT1_DC((uint8_t)psProductTermConfig->dInput));
    }
    else if (kEVTG_ProductTerm2 == productTerm)
    {
        *pu16AOIPT23Config &=
            ~(uint16_t)(EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT2_AC_MASK | EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT2_BC_MASK |
                        EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT2_CC_MASK | EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT2_DC_MASK);
        *pu16AOIPT23Config |= (EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT2_AC((uint8_t)psProductTermConfig->aInput) |
                               EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT2_BC((uint8_t)psProductTermConfig->bInput) |
                               EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT2_CC((uint8_t)psProductTermConfig->cInput) |
                               EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT2_DC((uint8_t)psProductTermConfig->dInput));
    }
    else
    {
        *pu16AOIPT23Config &=
            ~(uint16_t)(EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT3_AC_MASK | EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT3_BC_MASK |
                        EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT3_CC_MASK | EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT3_DC_MASK);
        *pu16AOIPT23Config |= (EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT3_AC((uint8_t)psProductTermConfig->aInput) |
                               EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT3_BC((uint8_t)psProductTermConfig->bInput) |
                               EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT3_CC((uint8_t)psProductTermConfig->cInput) |
                               EVTG_EVTG_INST_EVTG_AOI0_BFT23_PT3_DC((uint8_t)psProductTermConfig->dInput));
    }
}

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
void EVTG_GetDefaultConfig(evtg_config_t *psConfig, evtg_flipflop_mode_t flipflopMode)
{
    /* Initializes the configure structure to zero. */
    (void)memset(psConfig, 0, sizeof(evtg_config_t));

    switch (flipflopMode)
    {
        case kEVTG_FFModeBypass:

            /*
             * In this mode, filp-flop will be passed, The two AOI expressions "AOI_0" and "AOI_1"
             * will be directly assigned to EVTG outputs(EVTG_OUTA and EVTG_OUTB).
             *
             * In this mode, user can choose to enable or disable input sync logic and filter function.
             * Here disable both input sync logic and filter function.
             */
            psConfig->flipflopMode = kEVTG_FFModeBypass;

            psConfig->enableInputASync = false;
            psConfig->enableInputBSync = false;
            psConfig->enableInputCSync = false;
            psConfig->enableInputDSync = false;

            break;

        case kEVTG_FFModeRSTrigger:

            /*
             * In this mode, AOI_0 expression is Reset port, and AOI_1 is Set port. Both are active
             * high. When "R"(Reset) is high, whatever "S"(Set) is, EVTG_OUTA will be "0". When "R" is
             * low and "S" is high, EVTG_OUTA will be "1". If both "R" and "S" are low, EVTG output
             * will be kept. EVTG_OUTB is always the complement of EVTG_OUTA.
             *
             * In this mode, user can choose to enable or disable input sync logic and filter function.
             * Here disable both input sync logic and filter function.
             */
            psConfig->flipflopMode = kEVTG_FFModeRSTrigger;

            psConfig->enableInputASync = false;
            psConfig->enableInputBSync = false;
            psConfig->enableInputCSync = false;
            psConfig->enableInputDSync = false;

            break;

        case kEVTG_FFModeTFF:

            /*
             * In this mode, AOI_0 expression is T port of T-FF, AOI_1 is CLK port. When T assert,
             * the Q port (EVTG_OUTA) will turnover at the rising edge of "CLK". When T dis-assert,
             * Q(EVTG_OUTA) will be kept. EVTG_OUTB is always the complement of EVTG_OUTA.
             *
             * In this mode, input sync or filter has to be enabled to remove the possible glitch.
             * Here input sync is enabled, filter is disabled. User could override corresponding fields
             * depends on the actual user case to choose to enable or disable input sync logic and filter
             * function.
             */
            psConfig->flipflopMode = kEVTG_FFModeTFF;

            psConfig->enableInputASync = true;
            psConfig->enableInputBSync = true;
            psConfig->enableInputCSync = true;
            psConfig->enableInputDSync = true;

            break;

        case kEVTG_FFModeJKFF:

            /*
             * In general, JK Flip-Flop have four input ports: J, K , Q and CLK(Q is output of Flip-Flop).
             * And the logical expression is J&~Q | ~K&Q;  Here we implement the logic expression by AOI
             * so that we can reuse the D-FF to implement JK-FF. Suppose we set EVTG input "An" as "J" port,
             * "Cn" as "K" port, "Dn" as "CLK" port, and "Q" port of FF feed back and override "Bn".
             * According to the JK logic expression, the AOI_0 expression will be "An&~Bn | Bn&~Cn",
             * AOI_1 expression will be "Dn".
             *
             * In this mode, input sync or filter has to be enabled to remove the possible glitch.
             * Here input sync is enabled, filter is disabled. User could override corresponding fields
             * depends on the actual user case to choose to enable or disable input sync logic and filter
             * function.
             *
             * When FF Mode is configured as JK-FF mode, need EVTG_OUTA feedback to EVTG input and replace
             * one of the four inputs. Here input Bn is replaced, represents which EVTG input(EVTG_OUTA)
             * is replaced by FF output.
             */
            psConfig->flipflopMode        = kEVTG_FFModeJKFF;
            psConfig->outfdbkOverideinput = kEVTG_OutputOverrideInputB;

            psConfig->enableInputASync = true;
            psConfig->enableInputBSync = true;
            psConfig->enableInputCSync = true;
            psConfig->enableInputDSync = true;

            break;

        case kEVTG_FFModeLatch:

            /*
             * In this mode, AOI_0 expression is D port, AOI_1 is CLK port. Different from D-FF
             * mode, in Latch mode, D port will be passed only when CLK is high, and output will be
             * kept when CLK is low. EVTG_OUTB is always the complement of EVTG_OUTA.
             *
             * In this mode, input sync or filter has to be enabled to remove the possible glitch.
             * Here input sync is enabled, filter is disabled. User could override corresponding fields
             * depends on the actual user case to choose to enable or disable input sync logic and filter
             * function.
             */
            psConfig->flipflopMode = kEVTG_FFModeLatch;

            psConfig->enableInputASync = true;
            psConfig->enableInputBSync = true;
            psConfig->enableInputCSync = true;
            psConfig->enableInputDSync = true;

            break;

        default:
            assert(false);
            break;
    }
    /* User could choose to enable or disable Flip-flop initial output value. */
    psConfig->enableFlipflopInitOutput = false;
    psConfig->flipflopInitOutputValue  = kEVTG_FFInitOut0;

    /* User could choose to override this fields to enable filter function. */
    psConfig->aoi0Config.aoiOutFilterConfig.sampleCount  = kEVTG_AOIOutFilterSampleCount3;
    psConfig->aoi0Config.aoiOutFilterConfig.samplePeriod = 0U;

    psConfig->aoi1Config.aoiOutFilterConfig.sampleCount  = kEVTG_AOIOutFilterSampleCount3;
    psConfig->aoi1Config.aoiOutFilterConfig.samplePeriod = 0U;

#if defined(FSL_FEATURE_EVTG_HAS_FORCE_BYPASS_FLIPFLOP) && FSL_FEATURE_EVTG_HAS_FORCE_BYPASS_FLIPFLOP
    psConfig->enableForceBypassFlipFlopAOI0 = false;
    psConfig->enableForceBypassFlipFlopAOI1 = false;
#endif

    /*
     * For JK-FF Mode, Here we implement the logic expression by AOI so that we can reuse the
     * D-FF to implement JK-FF. Suppose we set EVTG input "An" as "J" port, "Cn" as "K" port, "Dn"
     * as "CLK" port, and "Q" port of FF feed back and override "Bn". According to the JK logic
     * expression, the AOI_0 expression will be "An&~Bn | Bn&~Cn", AOI_1 expression will be "Dn".
     *
     * For other FF Mode, the default input here is logical 0. User can configure to produce a logical 0
     * or 1 or pass the true or complement of the selected event input according to their requirement.
     */
    if (kEVTG_FFModeJKFF == flipflopMode)
    {
        psConfig->aoi0Config.productTerm0.aInput = kEVTG_InputDirectPass;
        psConfig->aoi0Config.productTerm0.bInput = kEVTG_InputComplement;
        psConfig->aoi0Config.productTerm0.cInput = kEVTG_InputLogicOne;
        psConfig->aoi0Config.productTerm0.dInput = kEVTG_InputLogicOne;

        psConfig->aoi0Config.productTerm1.aInput = kEVTG_InputLogicOne;
        psConfig->aoi0Config.productTerm1.bInput = kEVTG_InputDirectPass;
        psConfig->aoi0Config.productTerm1.cInput = kEVTG_InputComplement;
        psConfig->aoi0Config.productTerm1.dInput = kEVTG_InputLogicOne;

        psConfig->aoi0Config.productTerm2.aInput = kEVTG_InputLogicZero;
        psConfig->aoi0Config.productTerm2.bInput = kEVTG_InputLogicZero;
        psConfig->aoi0Config.productTerm2.cInput = kEVTG_InputLogicZero;
        psConfig->aoi0Config.productTerm2.dInput = kEVTG_InputLogicZero;

        psConfig->aoi0Config.productTerm3.aInput = kEVTG_InputLogicZero;
        psConfig->aoi0Config.productTerm3.bInput = kEVTG_InputLogicZero;
        psConfig->aoi0Config.productTerm3.cInput = kEVTG_InputLogicZero;
        psConfig->aoi0Config.productTerm3.dInput = kEVTG_InputLogicZero;

        psConfig->aoi1Config.productTerm0.aInput = kEVTG_InputLogicOne;
        psConfig->aoi1Config.productTerm0.bInput = kEVTG_InputLogicOne;
        psConfig->aoi1Config.productTerm0.cInput = kEVTG_InputLogicOne;
        psConfig->aoi1Config.productTerm0.dInput = kEVTG_InputDirectPass;

        psConfig->aoi1Config.productTerm1.aInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm1.bInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm1.cInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm1.dInput = kEVTG_InputLogicZero;

        psConfig->aoi1Config.productTerm2.aInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm2.bInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm2.cInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm2.dInput = kEVTG_InputLogicZero;

        psConfig->aoi1Config.productTerm3.aInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm3.bInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm3.cInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm3.dInput = kEVTG_InputLogicZero;
    }
    else
    {
        psConfig->aoi0Config.productTerm0.aInput = kEVTG_InputLogicZero;
        psConfig->aoi0Config.productTerm0.bInput = kEVTG_InputLogicZero;
        psConfig->aoi0Config.productTerm0.cInput = kEVTG_InputLogicZero;
        psConfig->aoi0Config.productTerm0.dInput = kEVTG_InputLogicZero;

        psConfig->aoi0Config.productTerm1.aInput = kEVTG_InputLogicZero;
        psConfig->aoi0Config.productTerm1.bInput = kEVTG_InputLogicZero;
        psConfig->aoi0Config.productTerm1.cInput = kEVTG_InputLogicZero;
        psConfig->aoi0Config.productTerm1.dInput = kEVTG_InputLogicZero;

        psConfig->aoi0Config.productTerm2.aInput = kEVTG_InputLogicZero;
        psConfig->aoi0Config.productTerm2.bInput = kEVTG_InputLogicZero;
        psConfig->aoi0Config.productTerm2.cInput = kEVTG_InputLogicZero;
        psConfig->aoi0Config.productTerm2.dInput = kEVTG_InputLogicZero;

        psConfig->aoi0Config.productTerm3.aInput = kEVTG_InputLogicZero;
        psConfig->aoi0Config.productTerm3.bInput = kEVTG_InputLogicZero;
        psConfig->aoi0Config.productTerm3.cInput = kEVTG_InputLogicZero;
        psConfig->aoi0Config.productTerm3.dInput = kEVTG_InputLogicZero;

        psConfig->aoi1Config.productTerm0.aInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm0.bInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm0.cInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm0.dInput = kEVTG_InputLogicZero;

        psConfig->aoi1Config.productTerm1.aInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm1.bInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm1.cInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm1.dInput = kEVTG_InputLogicZero;

        psConfig->aoi1Config.productTerm2.aInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm2.bInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm2.cInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm2.dInput = kEVTG_InputLogicZero;

        psConfig->aoi1Config.productTerm3.aInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm3.bInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm3.cInput = kEVTG_InputLogicZero;
        psConfig->aoi1Config.productTerm3.dInput = kEVTG_InputLogicZero;
    }
}
