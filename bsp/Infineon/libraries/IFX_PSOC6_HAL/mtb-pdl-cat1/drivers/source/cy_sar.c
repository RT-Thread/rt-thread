/***************************************************************************//**
* \file cy_sar.c
* \version 2.10
*
* Provides the public functions for the API for the SAR driver.
*
********************************************************************************
* \copyright
* Copyright 2017-2021 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/
#include "cy_sar.h"

#ifdef CY_IP_MXS40PASS_SAR

#if defined(__cplusplus)
extern "C" {
#endif

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 81, \
'SAR_Type will typecast to either SAR_V1_Type or SAR_V2_Type but not both on PDL initialization based on the target device at compile time.');

#define CHAN_NUM(chan)           ((chan) < CY_SAR_NUM_CHANNELS)
#define IS_RIGHT_ALIGN           (!_FLD2BOOL(SAR_SAMPLE_CTRL_LEFT_ALIGN, SAR_SAMPLE_CTRL(base)))

#define CY_SAR_MASK                 (CY_SAR_SAR0 | \
                                     CY_SAR_SAR1 | \
                                     CY_SAR_SAR2 | \
                                     CY_SAR_SAR3)

#define IS_SAR_MASK_VALID(sarMask)  (0UL == ((sarMask) & ((uint32_t) ~CY_SAR_MASK)))
#define SCAN_CNT_MIN (1UL)
#define SCAN_CNT_MAX (256UL)
#define IS_SCAN_CNT_VALID(scanCnt) ((SCAN_CNT_MIN <= (scanCnt)) && ((scanCnt) <= SCAN_CNT_MAX))

#define CY_SAR_TR_IN_0          (0UL)
#define CY_SAR_TR_IN_1          (1UL)
#define CY_SAR_TR_IN_2          (2UL)
#define CY_SAR_TR_IN_3          (3UL)

static cy_stc_sar_state_backup_t enabledBeforeSleep[CY_SAR_INSTANCES] =
{
    {0UL,0UL},{0UL,0UL}
};

/* This array is used to calibrate the offset for each channel.
* At initialization, channels that are single-ended, signed, and with Vneg = Vref
* have an offset of -(2^12)/2 = -2048. All other channels have an offset of 0.
* The offset can be overridden using Cy_SAR_SetChannelOffset.
* The channel offsets are used by the Cy_SAR_CountsTo_Volts, Cy_SAR_CountsTo_mVolts, and
* Cy_SAR_CountsTo_uVolts functions to convert counts to voltage.
*/
volatile int16_t Cy_SAR_offset[CY_SAR_NUM_CHANNELS][CY_SAR_INSTANCES];

/* This array is used to calibrate the gain for each channel.
* It is set at initialization and the value depends on the SARADC resolution
* and voltage reference, 10*(2^12)/(2*Vref).
* The gain can be overridden using Cy_SAR_SetChannelGain.
* The channel gains are used by the Cy_SAR_CountsTo_Volts, Cy_SAR_CountsTo_mVolts and
* Cy_SAR_CountsTo_uVolts functions to convert counts to voltage.
*/
volatile int32_t Cy_SAR_countsPer10Volt[CY_SAR_NUM_CHANNELS][CY_SAR_INSTANCES];

/* Global variable to save internal states
 * bit 0 - fifo enable for SAR0 instance
 * bit 1 - fifo enable for SAR1 instance
 * */
static uint32_t Cy_SAR_flags = 0UL;


/*******************************************************************************
* Function Name: Cy_SAR_CommonInit
****************************************************************************//**
*
* Initialize common SAR configuration registers.
*
* \param base
* Pointer to structure describing PASS registers.
*
* \param trigConfig
* Pointer to structure containing configuration data.
* See \ref cy_stc_sar_common_config_t.
*
* \return
* - \ref CY_SAR_SUCCESS : initialization complete
* - \ref CY_SAR_BAD_PARAM : input pointers are null, initialization incomplete
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_COMMON_INIT
*
*******************************************************************************/
cy_en_sar_status_t Cy_SAR_CommonInit(PASS_Type * base, const cy_stc_sar_common_config_t  * trigConfig)
{
    cy_en_sar_status_t result = CY_SAR_SUCCESS;

    if((!CY_PASS_V1) && (NULL != base) && (NULL != trigConfig))
    {
        uint32_t simultTrigSourceVal = CY_SAR_TR_IN_0;
        bool simultTrigTimer = false;
        uint32_t interruptState;

        CY_ASSERT_L3(IS_SAR_MASK_VALID(trigConfig->simultControl));
        CY_ASSERT_L3(IS_SCAN_CNT_VALID(trigConfig->scanCount));

        /* Convert and check simultTrigSource value */
        switch(trigConfig->simultTrigSource)
        {
        case CY_SAR_SAR0:
            simultTrigSourceVal = CY_SAR_TR_IN_0;
            break;

        case CY_SAR_SAR1:
            simultTrigSourceVal = CY_SAR_TR_IN_1;
            break;

        case CY_SAR_SAR2:
            simultTrigSourceVal = CY_SAR_TR_IN_2;
            break;

        case CY_SAR_SAR3:
            simultTrigSourceVal = CY_SAR_TR_IN_3;
            break;

        case CY_SAR_TIMER:
            simultTrigTimer = true;
            break;

        default:
            /* Incorrect trigger source */
            result = CY_SAR_BAD_PARAM;
            break;
        }

        if(CY_SAR_SUCCESS == result)
        {
            PASS_SAR_SIMULT_CTRL(base) = _VAL2FLD(PASS_V2_SAR_SIMULT_CTRL_SIMULT_HW_TR_EN, trigConfig->simultControl)                              |
                                         _VAL2FLD(PASS_V2_SAR_SIMULT_CTRL_SIMULT_HW_TR_SRC, simultTrigSourceVal)                                   |
                                        _BOOL2FLD(PASS_V2_SAR_SIMULT_CTRL_SIMULT_HW_TR_TIMER_SEL, simultTrigTimer)                                 |
                                         _VAL2FLD(PASS_V2_SAR_SIMULT_CTRL_SIMULT_HW_TR_LEVEL, (uint32_t)(trigConfig->simultTrigEvent))             |
                                         _VAL2FLD(PASS_V2_SAR_SIMULT_CTRL_SIMULT_HW_SYNC_TR, (uint32_t)(trigConfig->simultTrigSync))               |
                                         _VAL2FLD(PASS_V2_SAR_SIMULT_CTRL_SIMULT_TR_SCAN_CNT_SEL, (uint32_t)(trigConfig->simultSamplesPerTrigger)) |
                                         _VAL2FLD(PASS_V2_SAR_SIMULT_CTRL_SIMULT_EOS_INTR_SCAN_CNT_SEL, (uint32_t)(trigConfig->simultEOSIntrSelect));
            PASS_SAR_TR_SCAN_CNT(base) = _VAL2FLD(PASS_V2_SAR_TR_SCAN_CNT_SCAN_CNT, trigConfig->scanCount - 1UL);

            interruptState = Cy_SysLib_EnterCriticalSection();
            CY_REG32_CLR_SET(PASS_ANA_PWR_CFG(base), PASS_V2_ANA_PWR_CFG_PWR_UP_DELAY, trigConfig->pwrUpDelay);
            Cy_SysLib_ExitCriticalSection(interruptState);
        }
    }
    else
    {
        result = CY_SAR_BAD_PARAM;
    }

    return result;
}

/*******************************************************************************
* Function Name: Cy_SAR_Init
****************************************************************************//**
*
* Initialize all SAR configuration registers.
* If routing is to be configured, all switches will be cleared before
* being initialized.
*
* \note If interleaved averaging mode is used, the Differential Result Format
*       should be the same as the Single-Ended Result Format. Otherwise, this
*       function will return CY_SAR_BAD_PARAM.
*
* \param base
* Pointer to structure describing SAR instance registers
*
* \param config
* Pointer to structure containing configuration data. See \ref cy_stc_sar_config_t
* and guidance in the \ref group_sar_initialization section.
*
* \return
* - \ref CY_SAR_SUCCESS : initialization complete successfully
* - \ref CY_SAR_BAD_PARAM : input pointers are null or some configuration
                            setting is invalid, initialization incomplete.
*
* \funcusage \snippet sar/snippet/main.c SNIPPET_SAR_INIT_CUSTOM
*
*******************************************************************************/
cy_en_sar_status_t Cy_SAR_Init(SAR_Type * base, const cy_stc_sar_config_t * config)
{
    cy_en_sar_status_t result = CY_SAR_BAD_PARAM;

    CY_ASSERT_L1(NULL != base);
    CY_ASSERT_L1(NULL != config);

    if ((NULL != base) && (NULL != config))
    {
        /* If interleaved averaging mode is used, the Differential Result Format should be the same as the Single-Ended Result Format. */
        if (((0UL != (config->sampleCtrl & SAR_V2_SAMPLE_CTRL_AVG_MODE_Msk)) ?
           !((0UL != (config->sampleCtrl & SAR_V2_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_Msk)) !=
             (0UL != (config->sampleCtrl & SAR_V2_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_Msk))) : true) &&
        /* The FIFO is supported by PASS_ver2 only */
            ((NULL != config->fifoCfgPtr) ? !CY_PASS_V1 : true) &&
        /* The Clock selection CY_SAR_CLK_DEEPSLEEP is allowed for PASS_V2 only */
            ((CY_SAR_CLK_DEEPSLEEP == config->clock) ? !CY_PASS_V1 : true))
        {
            uint32_t interruptState;
            uint8_t chan;
            bool vrefNegSelect;
            bool singleEndedSigned;
            bool chanSingleEnded;
            int32_t defaultGain;

            CY_ASSERT_L2(CY_SAR_CTRL(config->ctrl));
            CY_ASSERT_L2(CY_SAR_SAMPLE_CTRL(config->sampleCtrl));
            CY_ASSERT_L2(CY_SAR_SAMPLE_TIME(config->sampleTime01));
            CY_ASSERT_L2(CY_SAR_SAMPLE_TIME(config->sampleTime23));
            CY_ASSERT_L3(CY_SAR_RANGECOND(config->rangeCond));
            CY_ASSERT_L2(CY_SAR_INJMASK(config->chanEn));
            CY_ASSERT_L2(CY_SAR_INTRMASK(config->intrMask));
            CY_ASSERT_L2(CY_SAR_CHANMASK(config->satIntrMask));
            CY_ASSERT_L2(CY_SAR_CHANMASK(config->rangeIntrMask));

            /* Set the REFBUF_EN bit as this is required for proper operation. */
            SAR_CTRL(base) = (config->ctrl | SAR_CTRL_REFBUF_EN_Msk) & ~SAR_CTRL_ENABLED_Msk;
            SAR_SAMPLE_CTRL(base) = config->sampleCtrl | SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_Msk; /* Set the EOS_DSI_OUT_EN bit so the EOS signal can be routed */
            SAR_SAMPLE_TIME01(base) = config->sampleTime01;
            SAR_SAMPLE_TIME23(base) = config->sampleTime23;
            SAR_RANGE_THRES(base) = config->rangeThres;
            SAR_RANGE_COND(base) = (uint32_t)config->rangeCond << SAR_RANGE_COND_RANGE_COND_Pos;
            SAR_CHAN_EN(base) = _VAL2FLD(SAR_CHAN_EN_CHAN_EN, config->chanEn);

            /* Check whether NEG_SEL is set for VREF */
            vrefNegSelect = ((uint32_t)CY_SAR_NEG_SEL_VREF == (config->ctrl & SAR_CTRL_NEG_SEL_Msk))? true : false;
            /* Check whether single ended channels are set to signed */
            singleEndedSigned = (SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_Msk == (config->sampleCtrl & SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_Msk)) ? true : false;
            /* Calculate the default gain for all the channels in counts per 10 volts with rounding */
            defaultGain = (int32_t)(uint16_t)CY_SYSLIB_DIV_ROUND((uint32_t)CY_SAR_WRK_MAX_12BIT * (uint32_t)CY_SAR_10MV_COUNTS, config->vrefMvValue * 2UL);

            for (chan = 0u; chan < CY_SAR_SEQ_NUM_CHANNELS; chan++)
            {
                CY_ASSERT_L2(CY_SAR_CHAN_CONFIG(config->chanConfig[chan]));

                SAR_CHAN_CONFIG(base, chan) = config->chanConfig[chan];

                /* For signed single ended channels with NEG_SEL set to VREF,
                 * set the offset to minus half scale to convert results to unsigned format */
                chanSingleEnded = (0UL == (config->chanConfig[chan] & (SAR_CHAN_CONFIG_DIFFERENTIAL_EN_Msk | SAR_CHAN_CONFIG_NEG_ADDR_EN_Msk))) ? true : false;
                if (chanSingleEnded && vrefNegSelect && singleEndedSigned)
                {
                    Cy_SAR_offset[chan][CY_SAR_INSTANCE(base)] = (int16_t) (CY_SAR_WRK_MAX_12BIT / -2);
                }
                else
                {
                    Cy_SAR_offset[chan][CY_SAR_INSTANCE(base)] = 0;
                }

                Cy_SAR_countsPer10Volt[chan][CY_SAR_INSTANCE(base)] = defaultGain;
            }

            SAR_INTR_MASK(base) = config->intrMask;
            SAR_INTR(base) = config->intrMask;
            SAR_SATURATE_INTR_MASK(base) = config->satIntrMask;
            SAR_SATURATE_INTR(base) = config->satIntrMask;
            SAR_RANGE_INTR_MASK(base) = config->rangeIntrMask;
            SAR_RANGE_INTR(base) = config->rangeIntrMask;

            /* Set routing related registers if enabled */
            if (true == config->configRouting)
            {
                CY_ASSERT_L2(CY_SAR_SWITCHMASK(config->muxSwitch));
                CY_ASSERT_L2(CY_SAR_SQMASK(config->muxSwitchSqCtrl));

                /* Clear out all the switches so that only the desired switches in the config structure are set. */
                SAR_MUX_SWITCH_CLEAR0(base) = CY_SAR_CLEAR_ALL_SWITCHES;

                SAR_MUX_SWITCH0(base) = config->muxSwitch;
                SAR_MUX_SWITCH_SQ_CTRL(base) = config->muxSwitchSqCtrl;
            }

            /* Set the Cap trim if it was trimmed out of range from sflash */
            if ((CY_SAR_CAP_TRIM_MAX == SAR_ANA_TRIM0(base)) || (CY_SAR_CAP_TRIM_MIN == SAR_ANA_TRIM0(base)))
            {
                SAR_ANA_TRIM0(base) = CY_SAR_CAP_TRIM;
            }

            if (0UL != (CY_SAR_INJ_CHAN_MASK & config->chanEn))
            {
                SAR_INJ_CHAN_CONFIG(base) = config->chanConfig[CY_SAR_INJ_CHANNEL];
                Cy_SAR_countsPer10Volt[CY_SAR_INJ_CHANNEL][CY_SAR_INSTANCE(base)] = defaultGain;
            }

            if (NULL != config->fifoCfgPtr)
            {
                uint32_t locLevel = config->fifoCfgPtr->level - 1UL; /* Convert the user value into the machine value */

                Cy_SAR_flags |= CY_SAR_INSTANCE_MASK(base);

                PASS_FIFO_CONFIG(base) = _BOOL2FLD(PASS_FIFO_V2_CONFIG_CHAN_ID_EN,        config->fifoCfgPtr->chanId) |
                                         _BOOL2FLD(PASS_FIFO_V2_CONFIG_CHAIN_TO_NXT,      config->fifoCfgPtr->chainToNext) |
                                         _BOOL2FLD(PASS_FIFO_V2_CONFIG_TR_INTR_CLR_RD_EN, config->fifoCfgPtr->clrTrIntrOnRead);

                CY_ASSERT_L2(CY_SAR_IS_FIFO_LEVEL_VALID(locLevel));
                PASS_FIFO_LEVEL(base) = _VAL2FLD(PASS_FIFO_V2_LEVEL_LEVEL, locLevel);

                interruptState = Cy_SysLib_EnterCriticalSection();

                if (config->fifoCfgPtr->trOut)
                {
                    PASS_SAR_TR_OUT_CTRL(CY_PASS_V2_ADDR) |= CY_SAR_INSTANCE_MASK(base);
                }
                else
                {
                    PASS_SAR_TR_OUT_CTRL(CY_PASS_V2_ADDR) &= ~CY_SAR_INSTANCE_MASK(base);
                }

                Cy_SysLib_ExitCriticalSection(interruptState);
            }
            else
            {
                Cy_SAR_flags &= ~CY_SAR_INSTANCE_MASK(base);
            }

            if (!CY_PASS_V1)
            {
                uint32_t locReg;
                uint32_t locAndMask = ~(CY_SAR_INSTANCE_MASK(base) |
                                       (CY_SAR_INSTANCE_MASK(base) << PASS_V2_SAR_OVR_CTRL_TR_SCAN_CNT_SEL_Pos) |
                                       (CY_SAR_INSTANCE_MASK(base) << PASS_V2_SAR_OVR_CTRL_EOS_INTR_SCAN_CNT_SEL_Pos));
                uint32_t locOrMask = (config->trTimer ? CY_SAR_INSTANCE_MASK(base) : 0UL) |
                                     (config->scanCnt ? (CY_SAR_INSTANCE_MASK(base) << PASS_V2_SAR_OVR_CTRL_TR_SCAN_CNT_SEL_Pos) : 0UL) |
                                     (config->scanCntIntr ? (CY_SAR_INSTANCE_MASK(base) << PASS_V2_SAR_OVR_CTRL_EOS_INTR_SCAN_CNT_SEL_Pos) : 0UL);

                interruptState = Cy_SysLib_EnterCriticalSection();

                locReg = PASS_SAR_OVR_CTRL(CY_PASS_V2_ADDR);
                locReg &= locAndMask;
                locReg |= locOrMask;
                PASS_SAR_OVR_CTRL(CY_PASS_V2_ADDR) = locReg;

                Cy_SysLib_ExitCriticalSection(interruptState);

                CY_ASSERT_L3(CY_SAR_IS_CLK_VALID(config->clock));
                PASS_SAR_CLOCK_SEL(base) = _VAL2FLD(PASS_V2_SAR_CLOCK_SEL_CLOCK_SEL, config->clock);
                PASS_SAR_DPSLP_CTRL(base) = _BOOL2FLD(PASS_V2_SAR_DPSLP_CTRL_ENABLED, (CY_SAR_CLK_DEEPSLEEP == config->clock));
            }

            result = CY_SAR_SUCCESS;
        }
    }

    return result;
}


/*******************************************************************************
* Function Name: Cy_SAR_DeInit
****************************************************************************//**
*
* Reset SAR registers back to power on reset defaults.
*
* \if Cy_SAR_offset and Cy_SAR_countsPer10Volt arrays are NOT reset. \endif
*
* \param base
* Pointer to structure describing registers
*
* \param deInitRouting
* If true, all SARMUX switches are opened and switch control registers are reset
* to zero. If false, switch registers are untouched.
*
* \return
* - \ref CY_SAR_SUCCESS : de-initialization complete
* - \ref CY_SAR_BAD_PARAM : input pointers are null, de-initialization incomplete
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_DEINIT
*
*******************************************************************************/
cy_en_sar_status_t Cy_SAR_DeInit(SAR_Type * base, bool deInitRouting)
{
    cy_en_sar_status_t result = CY_SAR_BAD_PARAM;

    CY_ASSERT_L1(NULL != base);

    if (NULL != base)
    {
        uint8_t chan;

        SAR_CTRL(base) = CY_SAR_DEINIT;
        SAR_SAMPLE_CTRL(base) = CY_SAR_DEINIT;
        SAR_SAMPLE_TIME01(base) = CY_SAR_SAMPLE_TIME_DEINIT;
        SAR_SAMPLE_TIME23(base) = CY_SAR_SAMPLE_TIME_DEINIT;
        SAR_RANGE_THRES(base) = CY_SAR_DEINIT;
        SAR_RANGE_COND(base) = CY_SAR_DEINIT;
        SAR_CHAN_EN(base) = CY_SAR_DEINIT;
        for (chan = 0u; chan < CY_SAR_SEQ_NUM_CHANNELS; chan++)
        {
            SAR_CHAN_CONFIG(base, chan) = CY_SAR_DEINIT;
        }
        SAR_INJ_CHAN_CONFIG(base) = CY_SAR_DEINIT;
        SAR_INTR_MASK(base) = CY_SAR_DEINIT;
        SAR_SATURATE_INTR_MASK(base) = CY_SAR_DEINIT;
        SAR_RANGE_INTR_MASK(base) = CY_SAR_DEINIT;
        if (true == deInitRouting)
        {
            SAR_MUX_SWITCH_CLEAR0(base) = CY_SAR_CLEAR_ALL_SWITCHES;
            SAR_MUX_SWITCH_DS_CTRL(base) = CY_SAR_DEINIT;
            SAR_MUX_SWITCH_SQ_CTRL(base) = CY_SAR_DEINIT;
        }

        if (!CY_PASS_V1)
        {
            uint32_t locAndMask = ~(CY_SAR_INSTANCE_MASK(base) |
                                    (CY_SAR_INSTANCE_MASK(base) << PASS_V2_SAR_OVR_CTRL_TR_SCAN_CNT_SEL_Pos) |
                                    (CY_SAR_INSTANCE_MASK(base) << PASS_V2_SAR_OVR_CTRL_EOS_INTR_SCAN_CNT_SEL_Pos));

            uint32_t interruptState = Cy_SysLib_EnterCriticalSection();

            PASS_SAR_OVR_CTRL(CY_PASS_V2_ADDR) &= locAndMask;
            PASS_SAR_TR_OUT_CTRL(CY_PASS_V2_ADDR) &= ~CY_SAR_INSTANCE_MASK(base);

            Cy_SysLib_ExitCriticalSection(interruptState);

            if (0UL != (Cy_SAR_flags & CY_SAR_INSTANCE_MASK(base)))
            {
                PASS_FIFO_CTRL(base) = CY_SAR_DEINIT; /* Disable first */
                PASS_FIFO_CONFIG(base) = CY_SAR_DEINIT;
                PASS_FIFO_LEVEL(base) = CY_SAR_DEINIT;
                Cy_SAR_flags &= ~CY_SAR_INSTANCE_MASK(base);
            }

            PASS_SAR_DPSLP_CTRL(base) = CY_SAR_DEINIT;
            PASS_SAR_CLOCK_SEL(base) = CY_SAR_DEINIT;
        }

        result = CY_SAR_SUCCESS;
    }

    return result;
}


/*******************************************************************************
* Function Name: Cy_SAR_Enable
****************************************************************************//**
*
* Power up the SAR ADC subsystem block. The hardware is ready to use
* after 2 us, which is included in this function.
*
* \param base
* Pointer to structure describing registers
*
* \return None
*
*******************************************************************************/
void Cy_SAR_Enable(SAR_Type *base)
{
    if (!_FLD2BOOL(SAR_CTRL_ENABLED, SAR_CTRL(base)))
    {
        SAR_CTRL(base) |= SAR_CTRL_ENABLED_Msk;

        /* The block is ready to use 2 us after the enable signal is set high. */
        Cy_SysLib_DelayUs(CY_SAR_2US_DELAY);

        if ((!CY_PASS_V1) && (0UL != (Cy_SAR_flags & CY_SAR_INSTANCE_MASK(base))))
        {
            PASS_FIFO_CTRL(base) = PASS_FIFO_V2_CTRL_ENABLED_Msk;
        }
    }
}


/*******************************************************************************
* Function Name: Cy_SAR_Disable
****************************************************************************//**
*
* Turn off the hardware block.
*
* \param base
* Pointer to structure describing registers
*
* \return None
*
*******************************************************************************/
void Cy_SAR_Disable(SAR_Type *base)
{
    if (_FLD2BOOL(SAR_CTRL_ENABLED, SAR_CTRL(base)))
    {
        while (_FLD2BOOL(SAR_STATUS_BUSY, SAR_STATUS(base)))
        {
            /* Wait for SAR to go idle */
        }

        SAR_CTRL(base) &= ~SAR_CTRL_ENABLED_Msk;

        if ((!CY_PASS_V1) && (0UL != (Cy_SAR_flags & CY_SAR_INSTANCE_MASK(base))))
        {
            PASS_FIFO_CTRL(base) = 0UL;
        }
    }
}


/*******************************************************************************
* Function Name: Cy_SAR_DeepSleep
****************************************************************************//**
*
* This is the preferred routine to prepare the hardware for Deep Sleep.
*
* It will call \ref Cy_SAR_StopConvert to disable continuous conversions
* and wait for SAR conversions to stop before entering Deep Sleep.
* If the SARMUX is not configured for Deep Sleep operation, the entire SAR hardware
* block will be turned off.
*
* \param base
* Pointer to structure describing registers
*
* \return None
*
* \funcusage
*
* This function is used in the \ref Cy_SAR_DeepSleepCallback. There is no
* need to call this function directly.
*
*******************************************************************************/
void Cy_SAR_DeepSleep(SAR_Type *base)
{
    uint32_t ctrlReg = SAR_CTRL(base);

    enabledBeforeSleep[CY_SAR_INSTANCE(base)].hwEnabled = ctrlReg & SAR_CTRL_ENABLED_Msk;

    /* Turn off the reference buffer */
    ctrlReg &= ~SAR_CTRL_REFBUF_EN_Msk;

    if (SAR_CTRL_ENABLED_Msk == enabledBeforeSleep[CY_SAR_INSTANCE(base)].hwEnabled)
    {

        /* Save state of CONTINUOUS bit so that conversions can be re-started upon wake-up */
        enabledBeforeSleep[CY_SAR_INSTANCE(base)].continuous = SAR_SAMPLE_CTRL(base) & SAR_SAMPLE_CTRL_CONTINUOUS_Msk;

        Cy_SAR_StopConvert(base);

        while (_FLD2BOOL(SAR_STATUS_BUSY, SAR_STATUS(base)))
        {
            /* Wait for SAR to stop conversions before entering low power */
        }

        /* Turn off the entire hardware block only if the SARMUX is not
         * enabled for Deep Sleep operation. */
        if (SAR_CTRL_DEEPSLEEP_ON_Msk != (ctrlReg & SAR_CTRL_DEEPSLEEP_ON_Msk))
        {
            SAR_CTRL(base) &= ~SAR_CTRL_ENABLED_Msk;
        }
    }

    SAR_CTRL(base) = ctrlReg;
}


/*******************************************************************************
* Function Name: Cy_SAR_Wakeup
****************************************************************************//**
*
* This is the preferred routine to restore the hardware to the state after calling
* \ref Cy_SAR_DeepSleep. Restoring the hardware involves re-enabling the hardware,
* the reference buffer, and continuous scanning if it was previously
* enabled before entering sleep.
*
* \param base
* Pointer to structure describing registers
*
* \sideeffect
* Calling this function without previously calling \ref Cy_SAR_DeepSleep can lead to
* unpredictable results.
*
* \return None
*
* \funcusage
*
* This function is used in the \ref Cy_SAR_DeepSleepCallback. There is no
* need to call this function directly.
*
*******************************************************************************/
void Cy_SAR_Wakeup(SAR_Type *base)
{
    /* Turn on the reference buffer */
    SAR_CTRL(base) |= SAR_CTRL_REFBUF_EN_Msk;

    if (SAR_CTRL_ENABLED_Msk == enabledBeforeSleep[CY_SAR_INSTANCE(base)].hwEnabled)
    {
        Cy_SAR_Enable(base);

        if (SAR_SAMPLE_CTRL_CONTINUOUS_Msk == enabledBeforeSleep[CY_SAR_INSTANCE(base)].continuous)
        {
            Cy_SAR_StartConvert(base, CY_SAR_START_CONVERT_CONTINUOUS);
        }
    }
}


/*******************************************************************************
* Function Name: Cy_SAR_StartConvert
****************************************************************************//**
*
* Start a single scan (one shot) of all enabled channels or start scanning
* continuously. When in continuous mode, all firmware and hardware triggers
* are ignored. To stop continuous scanning, call \ref Cy_SAR_StopConvert.
*
* \param base
* Pointer to structure describing registers
*
* \param startSelect
* A value of the enum \ref cy_en_sar_start_convert_sel_t
*
* \return None
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_START_CONVERT
*
*******************************************************************************/
void Cy_SAR_StartConvert(SAR_Type *base, cy_en_sar_start_convert_sel_t startSelect)
{
    CY_ASSERT_L3(CY_SAR_STARTCONVERT(startSelect));

    switch(startSelect)
    {
    case CY_SAR_START_CONVERT_CONTINUOUS:
        SAR_SAMPLE_CTRL(base) |= SAR_SAMPLE_CTRL_CONTINUOUS_Msk;
        break;
    case CY_SAR_START_CONVERT_SINGLE_SHOT:
    default:
        SAR_START_CTRL(base) = SAR_START_CTRL_FW_TRIGGER_Msk;
        break;
    }
}


/*******************************************************************************
* Function Name: Cy_SAR_StopConvert
****************************************************************************//**
*
* Stop continuous scanning of enabled channels.
* If a conversion is currently executing, that conversion will complete,
* but no further conversions will occur until the next call to
* \ref Cy_SAR_StartConvert or the next hardware trigger, if enabled.
*
* \param base
* Pointer to structure describing registers
*
* \return None
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_STOP_CONVERT
*
*******************************************************************************/
void Cy_SAR_StopConvert(SAR_Type *base)
{
    if (SAR_SAMPLE_CTRL_CONTINUOUS_Msk == (SAR_SAMPLE_CTRL(base) & SAR_SAMPLE_CTRL_CONTINUOUS_Msk))
    {
        SAR_SAMPLE_CTRL(base) &= ~SAR_SAMPLE_CTRL_CONTINUOUS_Msk;
    }
}


/*******************************************************************************
* Function Name: Cy_SAR_SetConvertMode
****************************************************************************//**
*
* Set the mode in which conversions are triggered. This function does
* not start any conversions; it only configures the mode for subsequent conversions.
*
* There are three modes:
*   - firmware only; hardware triggering is disabled
*   - firmware and edge sensitive hardware triggering
*   - firmware and level sensitive hardware triggering
*
* Note that firmware triggering is always enabled.
*
* \param base
* Pointer to structure describing registers
*
* \param mode
* A value of the enum \ref cy_en_sar_sample_ctrl_trigger_mode_t
*
* \return None
*
* \funcusage
*
* \snippet sar/snippet/main.c SAR_SNIPPET_SET_CONVERT_MODE
*
*******************************************************************************/
void Cy_SAR_SetConvertMode(SAR_Type *base, cy_en_sar_sample_ctrl_trigger_mode_t mode)
{
    CY_ASSERT_L3(CY_SAR_TRIGGER(mode));

    /* Clear the TRIGGER_EN and TRIGGER_LEVEL bits */
    uint32_t sampleCtrlReg = SAR_SAMPLE_CTRL(base) & ~(SAR_SAMPLE_CTRL_DSI_TRIGGER_EN_Msk | SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk);

    SAR_SAMPLE_CTRL(base) = sampleCtrlReg | (uint32_t)mode;
}


/*******************************************************************************
* Function Name: Cy_SAR_IsEndConversion
****************************************************************************//**
*
* Immediately return the status of the conversion or does not return (blocking)
* until the conversion completes, depending on the retMode parameter.
* In blocking mode, there is a time out of about 10 seconds for a CPU speed of
* 100 MHz.
*
* \param base
* Pointer to structure describing registers
*
* \param retMode
* A value of the enum \ref cy_en_sar_return_mode_t
*
* \return
* - \ref CY_SAR_SUCCESS : the last conversion is complete
* - \ref CY_SAR_CONVERSION_NOT_COMPLETE : the conversion has not completed
* - \ref CY_SAR_TIMEOUT : the watchdog timer has expired in blocking mode
*
* \sideeffect
* This function reads the end of conversion status and clears it after.
*
* \note
* \ref CY_SAR_WAIT_FOR_RESULT and \ref CY_SAR_WAIT_FOR_RESULT_INJ return modes are not recommended
* for use in RTOS environment.
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_IS_END_CONVERSION
*
*******************************************************************************/
cy_en_sar_status_t Cy_SAR_IsEndConversion(SAR_Type *base, cy_en_sar_return_mode_t retMode)
{
    CY_ASSERT_L3(CY_SAR_RETURN(retMode));

    cy_en_sar_status_t result;

    uint32_t wdt = 0x1555555UL; /* Watchdog timer for blocking while loop */
    uint32_t mask = ((CY_SAR_RETURN_STATUS_INJ == retMode) || (CY_SAR_WAIT_FOR_RESULT_INJ == retMode)) ? CY_SAR_INTR_INJ_EOC : CY_SAR_INTR_EOS;
    uint32_t intr = mask & Cy_SAR_GetInterruptStatus(base);

    if ((CY_SAR_WAIT_FOR_RESULT == retMode) || (CY_SAR_WAIT_FOR_RESULT_INJ == retMode))
    {
        while ((0UL == intr) && (0UL != wdt))
        {
            intr = mask & Cy_SAR_GetInterruptStatus(base);
            wdt--;
        }
    }

    /* Clear the EOS bit */
    if (mask == intr)
    {
        result = CY_SAR_SUCCESS;
        Cy_SAR_ClearInterrupt(base, mask);
    }
    else if (0UL == wdt)
    {
        result = CY_SAR_TIMEOUT;
    }
    else
    {
        result = CY_SAR_CONVERSION_NOT_COMPLETE;
    }

    return result;
}


/*******************************************************************************
* Function Name: Cy_SAR_IsChannelSigned
****************************************************************************//**
*
* Return true if channel result is configured for signed format, else false.
* The formats for single-ended and differential channels are independent.
* This function will first check whether the channel is single-ended or differential.
*
* \param base
* Pointer to structure describing registers
*
* \param chan
* The channel to check, between 0 and \ref CY_SAR_INJ_CHANNEL
*
* \return
* If channel number is invalid, false is returned
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_IS_CHANNEL_SIGNED
*
*******************************************************************************/
bool Cy_SAR_IsChannelSigned(const SAR_Type *base, uint32_t chan)
{
    CY_ASSERT_L2(CHAN_NUM(chan));

    bool isSigned = false;

    if (chan < CY_SAR_NUM_CHANNELS)
    {
        /* Sign bits are stored separately for differential and single ended channels. */
        if (true == Cy_SAR_IsChannelDifferential(base, chan))
        { /* Differential channel */
            if (SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_Msk == (SAR_SAMPLE_CTRL(base) & SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_Msk))
            {
                isSigned = true;
            }
        }
        else
        { /* Single ended channel */
            if (SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_Msk == (SAR_SAMPLE_CTRL(base) & SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_Msk))
            {
                isSigned = true;
            }
        }
    }

    return isSigned;
}


/*******************************************************************************
* Function Name: Cy_SAR_IsChannelSingleEnded
****************************************************************************//**
*
* Return true if channel is single ended, else false
*
* \param base
* Pointer to structure describing registers
*
* \param chan
* The channel to check, between 0 and \ref CY_SAR_INJ_CHANNEL
*
* \return
* If channel number is invalid, false is returned
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_IS_CHANNEL_SE
*
*******************************************************************************/
bool Cy_SAR_IsChannelSingleEnded(const SAR_Type *base, uint32_t chan)
{
    CY_ASSERT_L2(CHAN_NUM(chan));

    bool isSingleEnded = false;

    if (chan < CY_SAR_SEQ_NUM_CHANNELS)
    {
        if (0UL == (SAR_CHAN_CONFIG(base, chan) & (SAR_CHAN_CONFIG_DIFFERENTIAL_EN_Msk | SAR_CHAN_CONFIG_NEG_ADDR_EN_Msk)))
        {
            isSingleEnded = true;
        }
    }
    else if (CY_SAR_INJ_CHANNEL == chan)
    {
        isSingleEnded = !_FLD2BOOL(SAR_INJ_CHAN_CONFIG_INJ_DIFFERENTIAL_EN, SAR_INJ_CHAN_CONFIG(base));
    }
    else
    {
        /* Return false */
    }

    return isSingleEnded;
}


/*******************************************************************************
* Function Name: Cy_SAR_GetResult16
****************************************************************************//**
*
* Return the data available in the channel result data register as a signed
* 16-bit integer.
*
* \param base
* Pointer to structure describing registers
*
* \param chan
* The channel to read the result from, between 0 and \ref CY_SAR_INJ_CHANNEL
*
* \return
* Data is returned as a signed 16-bit integer.
* If channel number is invalid, 0 is returned.
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_GET_RESULT16
*
*******************************************************************************/
int16_t Cy_SAR_GetResult16(const SAR_Type *base, uint32_t chan)
{
    CY_ASSERT_L2(CHAN_NUM(chan));

    uint32_t adcResult = 0UL;

    if (chan < CY_SAR_SEQ_NUM_CHANNELS)
    {
        adcResult = _FLD2VAL(SAR_CHAN_RESULT_RESULT, SAR_CHAN_RESULT(base, chan));
    }
    else if (CY_SAR_INJ_CHANNEL == chan)
    {
        adcResult = _FLD2VAL(SAR_INJ_RESULT_INJ_RESULT, SAR_INJ_RESULT(base));
    }
    else
    {
        /* Return zero */
    }

    return (int16_t) adcResult;
}


/*******************************************************************************
* Function Name: Cy_SAR_GetResult32
****************************************************************************//**
*
* Return the data available in the channel result data register as a signed
* 32-bit integer.
*
* \param base
* Pointer to structure describing registers
*
* \param chan
* The channel to read the result from, between 0 and \ref CY_SAR_INJ_CHANNEL
*
* \return
* Data is returned as a signed 32-bit integer.
* If channel number is invalid, 0 is returned.
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_GET_RESULT32
*
*******************************************************************************/
int32_t Cy_SAR_GetResult32(const SAR_Type *base, uint32_t chan)
{
    return ((int32_t)Cy_SAR_GetResult16(base, chan));
}


/*******************************************************************************
* Function Name: Cy_SAR_SetLowLimit
****************************************************************************//**
*
* Set the low threshold for range detection. The values are interpreted
* as signed or unsigned according to the channel configuration. Range
* detection is done on the value stored in the result register. That is, after
* averaging, shifting sign extension, and left/right alignment.
*
* \param base
* Pointer to structure describing registers
*
* \param lowLimit
* The low threshold for range detection
*
* \return None
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_SET_LOWHIGH_LIMIT
*
*******************************************************************************/
void Cy_SAR_SetLowLimit(SAR_Type *base, uint32_t lowLimit)
{
    CY_ASSERT_L2(CY_SAR_RANGE_LIMIT(lowLimit));

    CY_REG32_CLR_SET(SAR_RANGE_THRES(base), SAR_RANGE_THRES_RANGE_LOW, lowLimit);
}


/*******************************************************************************
* Function Name: Cy_SAR_SetHighLimit
****************************************************************************//**
*
* Set the high threshold for range detection. The values are interpreted
* as signed or unsigned according to the channel configuration. Range
* detection is done on the value stored in the result register. That is, after
* averaging, shifting sign extension, and left/right alignment.
*
* \param base
* Pointer to structure describing registers
*
* \param highLimit
* The high threshold for range detection
*
* \return None
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_SET_LOWHIGH_LIMIT
*
*******************************************************************************/
void Cy_SAR_SetHighLimit(SAR_Type *base, uint32_t highLimit)
{
    CY_ASSERT_L2(CY_SAR_RANGE_LIMIT(highLimit));

    CY_REG32_CLR_SET(SAR_RANGE_THRES(base), SAR_RANGE_THRES_RANGE_HIGH, highLimit);
}


/*******************************************************************************
* Function Name: Cy_SAR_SetChannelOffset
****************************************************************************//**
*
* Store the channel offset for the voltage conversion functions.
*
* Offset is applied to counts before unit scaling and gain.
* See \ref Cy_SAR_CountsTo_Volts for more about this formula.
*
* To change channel 0's offset based on a known V_offset_mV, use:
*
*     Cy_SAR_SetOffset(0UL, -1 * V_offset_mV * (1UL << Resolution) / (2 * V_ref_mV));
*
* \param base
* Pointer to structure describing registers
*
* \param chan
* The channel number, between 0 and \ref CY_SAR_INJ_CHANNEL.
*
* \param offset
* The count value measured when the inputs are shorted or
* connected to the same input voltage.
*
* \return
* - \ref CY_SAR_SUCCESS : offset was set successfully
* - \ref CY_SAR_BAD_PARAM : channel number is equal to or greater than \ref CY_SAR_NUM_CHANNELS
*
*******************************************************************************/
cy_en_sar_status_t Cy_SAR_SetChannelOffset(const SAR_Type *base, uint32_t chan, int16_t offset)
{
    CY_ASSERT_L2(CHAN_NUM(chan));

    cy_en_sar_status_t result = CY_SAR_BAD_PARAM;

    if (chan < CY_SAR_NUM_CHANNELS)
    {
        Cy_SAR_offset[chan][CY_SAR_INSTANCE(base)] = offset;
        result = CY_SAR_SUCCESS;
    }

    return result;
}


/*******************************************************************************
* Function Name: Cy_SAR_SetChannelGain
****************************************************************************//**
*
* Store the gain value for the voltage conversion functions.
* The gain is configured at initialization in \ref Cy_SAR_Init
* based on the SARADC resolution and voltage reference.
*
* Gain is applied after offset and unit scaling.
* See \ref Cy_SAR_CountsTo_Volts for more about this formula.
*
* To change channel 0's gain based on a known V_ref_mV, use:
*
*     Cy_SAR_SetGain(0UL, 10000 * (1UL << Resolution) / (2 * V_ref_mV));
*
* \param base
* Pointer to structure describing registers
*
* \param chan
* The channel number, between 0 and \ref CY_SAR_INJ_CHANNEL.
*
* \param adcGain
* The gain in counts per 10 volt.
*
* \return
* - \ref CY_SAR_SUCCESS : gain was set successfully
* - \ref CY_SAR_BAD_PARAM : channel number is equal to or greater than \ref CY_SAR_NUM_CHANNELS
*
*******************************************************************************/
cy_en_sar_status_t Cy_SAR_SetChannelGain(const SAR_Type *base, uint32_t chan, int32_t adcGain)
{
    CY_ASSERT_L2(CHAN_NUM(chan));

    cy_en_sar_status_t result = CY_SAR_BAD_PARAM;

    if (chan < CY_SAR_NUM_CHANNELS)
    {
        Cy_SAR_countsPer10Volt[chan][CY_SAR_INSTANCE(base)] = adcGain;
        result = CY_SAR_SUCCESS;
    }

    return result;
}


/*******************************************************************************
* Function Name: Cy_SAR_RawCounts2Counts
****************************************************************************//**
*
* Convert the channel result to a consistent result after accounting for
* averaging and subtracting the offset.
* The equation used is:
*
*     Counts = (RawCounts/AvgDivider - Offset)
*
* where,
* - RawCounts: Raw counts from SAR 16-bit CHAN_RESULT register
* - AvgDivider: divider based on averaging mode (\ref cy_en_sar_sample_ctrl_avg_mode_t) and number of samples averaged
*   (\ref cy_en_sar_sample_ctrl_avg_cnt_t)
*   - \ref CY_SAR_AVG_MODE_SEQUENTIAL_ACCUM : AvgDivider is the number of samples averaged or 16, whichever is smaller
*   - \ref CY_SAR_AVG_MODE_SEQUENTIAL_FIXED : AvgDivider is 1
*   - \ref CY_SAR_AVG_MODE_INTERLEAVED : AvgDivider is the number of samples averaged
* - Offset: Value stored by the \ref Cy_SAR_SetChannelOffset function.
*
* \param base
* Pointer to structure describing registers
*
* \param chan
* The channel number, between 0 and \ref CY_SAR_INJ_CHANNEL
*
* \param adcCounts
* Conversion result from \ref Cy_SAR_GetResult16
*
* \return
* adcCounts after averaging and offset adjustments.
* If channel number is invalid, adcCounts is returned unmodified.
*
* \funcusage
*
* This function is used by \ref Cy_SAR_CountsTo_Volts, \ref Cy_SAR_CountsTo_mVolts,
* and \ref Cy_SAR_CountsTo_uVolts. Calling this function directly is usually
* not needed.
*
*******************************************************************************/
int16_t Cy_SAR_RawCounts2Counts(const SAR_Type *base, uint32_t chan, int16_t adcCounts)
{
    int16_t retVal = adcCounts;

    CY_ASSERT_L2(CHAN_NUM(chan));

    if (chan < CY_SAR_NUM_CHANNELS)
    {
        /* Divide the adcCount when accumulate averaging mode selected */
        if (!_FLD2BOOL(SAR_SAMPLE_CTRL_AVG_SHIFT, SAR_SAMPLE_CTRL(base)))
        { /* If Average mode != fixed */
            if (((chan < CY_SAR_SEQ_NUM_CHANNELS) && _FLD2BOOL(SAR_CHAN_CONFIG_AVG_EN,         SAR_CHAN_CONFIG(base, chan))) ||
                ((chan == CY_SAR_INJ_CHANNEL)     && _FLD2BOOL(SAR_INJ_CHAN_CONFIG_INJ_AVG_EN, SAR_INJ_CHAN_CONFIG(base))))
            { /* If channel uses averaging */
                uint32_t averageAdcSamplesDiv;

                /* Divide by 2^(AVG_CNT + 1) */
                averageAdcSamplesDiv = (SAR_SAMPLE_CTRL(base) & SAR_SAMPLE_CTRL_AVG_CNT_Msk) >> SAR_SAMPLE_CTRL_AVG_CNT_Pos;
                averageAdcSamplesDiv = (1UL << (averageAdcSamplesDiv + 1UL));

                /* If averaging mode is ACCUNDUMP (channel will be sampled back to back and averaged)
                * divider limit is 16 */
                if (SAR_SAMPLE_CTRL_AVG_MODE_Msk != (SAR_SAMPLE_CTRL(base) & SAR_SAMPLE_CTRL_AVG_MODE_Msk))
                {
                    if (averageAdcSamplesDiv > 16UL)
                    {
                        averageAdcSamplesDiv = 16UL;
                    }
                }

                /* If unsigned format, prevent sign extension */
                if (false == Cy_SAR_IsChannelSigned(base, chan))
                {
                    retVal = (int16_t)(uint32_t)((uint16_t) retVal / averageAdcSamplesDiv);
                }
                else
                {
                    retVal /= (int16_t) averageAdcSamplesDiv;
                }
            }
        }

        /* Subtract ADC offset */
        retVal -= Cy_SAR_offset[chan][CY_SAR_INSTANCE(base)];
    }

    return (retVal);
}


/*******************************************************************************
* Function Name: Cy_SAR_CountsTo_Volts
****************************************************************************//**
*
* Convert the ADC output to Volts as a float32. For example, if the ADC
* measured 0.534 volts, the return value would be 0.534.
* The calculation of voltage depends on the channel offset, gain and other parameters.
* The equation used is:
*
*     V = (RawCounts/AvgDivider - Offset)*TEN_VOLT/Gain
*
* where,
* - RawCounts: Raw counts from SAR 16-bit CHAN_RESULT register
* - AvgDivider: divider based on averaging mode (\ref cy_en_sar_sample_ctrl_avg_mode_t) and number of samples averaged
*   (\ref cy_en_sar_sample_ctrl_avg_cnt_t)
*   - \ref CY_SAR_AVG_MODE_SEQUENTIAL_ACCUM : AvgDivider is the number of samples averaged or 16, whichever is smaller
*   - \ref CY_SAR_AVG_MODE_SEQUENTIAL_FIXED : AvgDivider is 1
*   - \ref CY_SAR_AVG_MODE_INTERLEAVED : AvgDivider is the number of samples averaged
* - Offset: Value stored by the \ref Cy_SAR_SetChannelOffset function.
* - TEN_VOLT: 10 V constant since the gain is in counts per 10 volts.
* - Gain: Value stored by the \ref Cy_SAR_SetChannelGain function.
*
* \note
* This function is only valid when result alignment is right aligned.
*
* \param base
* Pointer to structure describing registers
*
* \param chan
* The channel number, between 0 and \ref CY_SAR_INJ_CHANNEL
*
* \param adcCounts
* Conversion result from \ref Cy_SAR_GetResult16
*
* \return
* Result in Volts.
* - If channel number is invalid, 0 is returned.
* - If channel is left aligned, 0 is returned.
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_COUNTSTO_VOLTS
*
*******************************************************************************/
float32_t Cy_SAR_CountsTo_Volts(const SAR_Type *base, uint32_t chan, int16_t adcCounts)
{
    CY_ASSERT_L2(CHAN_NUM(chan));

    float32_t result_Volts = 0.0f;

    if (chan < CY_SAR_NUM_CHANNELS)
    {
        if (IS_RIGHT_ALIGN)
        {
            result_Volts = (float32_t)Cy_SAR_RawCounts2Counts(base, chan, adcCounts) * CY_SAR_10V_COUNTS;
            result_Volts /= (float32_t)Cy_SAR_countsPer10Volt[chan][CY_SAR_INSTANCE(base)];
        }
    }

    return result_Volts;
}


/*******************************************************************************
* Function Name: Cy_SAR_CountsTo_mVolts
****************************************************************************//**
*
* Convert the ADC output to millivolts as an int16. For example, if the ADC
* measured 0.534 volts, the return value would be 534.
* The calculation of voltage depends on the channel offset, gain and other parameters.
* The equation used is:
*
*     V = (RawCounts/AvgDivider - Offset)*TEN_VOLT/Gain
*     mV = V * 1000
*
* where,
* - RawCounts: Raw counts from SAR 16-bit CHAN_RESULT register
* - AvgDivider: divider based on averaging mode (\ref cy_en_sar_sample_ctrl_avg_mode_t) and number of samples averaged
*   (\ref cy_en_sar_sample_ctrl_avg_cnt_t)
*   - \ref CY_SAR_AVG_MODE_SEQUENTIAL_ACCUM : AvgDivider is the number of samples averaged or 16, whichever is smaller
*   - \ref CY_SAR_AVG_MODE_SEQUENTIAL_FIXED : AvgDivider is 1
*   - \ref CY_SAR_AVG_MODE_INTERLEAVED : AvgDivider is the number of samples averaged
* - Offset: Value stored by the \ref Cy_SAR_SetChannelOffset function.
* - TEN_VOLT: 10 V constant since the gain is in counts per 10 volts.
* - Gain: Value stored by the \ref Cy_SAR_SetChannelGain function.
*
* \note
* This function is only valid when result alignment is right aligned.
*
* \param base
* Pointer to structure describing registers
*
* \param chan
* The channel number, between 0 and \ref CY_SAR_INJ_CHANNEL
*
* \param adcCounts
* Conversion result from \ref Cy_SAR_GetResult16
*
* \return
* Result in millivolts.
* - If channel number is invalid, 0 is returned.
* - If channel is left aligned, 0 is returned.
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_COUNTSTO_MVOLTS
*
*******************************************************************************/
int16_t Cy_SAR_CountsTo_mVolts(const SAR_Type *base, uint32_t chan, int16_t adcCounts)
{
    CY_ASSERT_L2(CHAN_NUM(chan));

    int32_t result_mVolts = 0;

    if (chan < CY_SAR_NUM_CHANNELS)
    {
        if (IS_RIGHT_ALIGN)
        {
            int16_t locCounts = Cy_SAR_RawCounts2Counts(base, chan, adcCounts);

            result_mVolts = ((int32_t)locCounts * CY_SAR_10MV_COUNTS);
            if (locCounts > 0)
            {
                result_mVolts += Cy_SAR_countsPer10Volt[chan][CY_SAR_INSTANCE(base)] / 2;
            }
            else
            {
                result_mVolts -= Cy_SAR_countsPer10Volt[chan][CY_SAR_INSTANCE(base)] / 2;
            }
            result_mVolts /= Cy_SAR_countsPer10Volt[chan][CY_SAR_INSTANCE(base)];
        }
    }

    return (int16_t) result_mVolts;
}


/*******************************************************************************
* Function Name: Cy_SAR_CountsTo_uVolts
****************************************************************************//**
*
* Convert the ADC output to microvolts as a int32. For example, if the ADC
* measured 0.534 volts, the return value would be 534000.
* The calculation of voltage depends on the channel offset, gain and other parameters.
* The equation used is:
*
*     V = (RawCounts/AvgDivider - Offset)*TEN_VOLT/Gain
*     uV = V * 1000000
*
* where,
* - RawCounts: Raw counts from SAR 16-bit CHAN_RESULT register
* - AvgDivider: divider based on averaging mode (\ref cy_en_sar_sample_ctrl_avg_mode_t) and number of samples averaged
*   (\ref cy_en_sar_sample_ctrl_avg_cnt_t)
*   - \ref CY_SAR_AVG_MODE_SEQUENTIAL_ACCUM : AvgDivider is the number of samples averaged or 16, whichever is smaller
*   - \ref CY_SAR_AVG_MODE_SEQUENTIAL_FIXED : AvgDivider is 1
*   - \ref CY_SAR_AVG_MODE_INTERLEAVED : AvgDivider is the number of samples averaged
* - Offset: Value stored by the \ref Cy_SAR_SetChannelOffset function.
* - TEN_VOLT: 10 V constant since the gain is in counts per 10 volts.
* - Gain: Value stored by the \ref Cy_SAR_SetChannelGain function.
*
* \note
* This function is only valid when result alignment is right aligned.
*
* \param base
* Pointer to structure describing registers
*
* \param chan
* The channel number, between 0 and \ref CY_SAR_INJ_CHANNEL
*
* \param adcCounts
* Conversion result from \ref Cy_SAR_GetResult16
*
* \return
* Result in microvolts.
* - If channel number is valid, 0 is returned.
* - If channel is left aligned, 0 is returned.
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_COUNTSTO_UVOLTS
*
*******************************************************************************/
int32_t Cy_SAR_CountsTo_uVolts(const SAR_Type *base, uint32_t chan, int16_t adcCounts)
{
    CY_ASSERT_L2(CHAN_NUM(chan));

    int64_t result_uVolts = 0;

    if (chan < CY_SAR_NUM_CHANNELS)
    {
        if (IS_RIGHT_ALIGN)
        {
            result_uVolts = (int64_t)Cy_SAR_RawCounts2Counts(base, chan, adcCounts) * CY_SAR_10UV_COUNTS;
            result_uVolts /= Cy_SAR_countsPer10Volt[chan][CY_SAR_INSTANCE(base)];
        }
    }

    return ((int32_t)result_uVolts);
}


/*******************************************************************************
* Function Name: Cy_SAR_SetAnalogSwitch
****************************************************************************//**
*
* Provide firmware control of the SARMUX switches for firmware sequencing.
* Each call to this function can open or close a set of switches.
* Previously configured switches are untouched.
*
* If the SARSEQ is enabled, there is no need to use this function.
*
* \param base
* Pointer to structure describing registers
*
* \param switchSelect
* The switch register that contains the desired switches. Select a value
* from \ref cy_en_sar_switch_register_sel_t.
*
* \param switchMask
* The mask of the switches to either open or close.
* Select one or more values from the \ref cy_en_sar_mux_switch_fw_ctrl_t enum
* and "OR" them together.
*
* \param state
* Open or close the desired switches. Select a value from \ref cy_en_sar_switch_state_t.
*
* \return None
*
* \funcusage
*
* \snippet sar/snippet/main.c SAR_SNIPPET_SET_ANALOG_SWITCH
*
*******************************************************************************/
void Cy_SAR_SetAnalogSwitch(SAR_Type *base, cy_en_sar_switch_register_sel_t switchSelect, uint32_t switchMask, cy_en_sar_switch_state_t state)
{
    CY_ASSERT_L3(CY_SAR_SWITCHSELECT(switchSelect));
    CY_ASSERT_L2(CY_SAR_SWITCHMASK(switchMask));
    CY_ASSERT_L3(CY_SAR_SWITCHSTATE(state));
    (void)switchSelect; /* Suppress warning */

    __IOM uint32_t *switchReg;
    __IOM uint32_t *switchClearReg;

    switchReg = &SAR_MUX_SWITCH0(base);
    switchClearReg = &SAR_MUX_SWITCH_CLEAR0(base);

    switch(state)
    {
    case CY_SAR_SWITCH_CLOSE:
        *switchReg |= switchMask;
        break;
    case CY_SAR_SWITCH_OPEN:
    default:

        /* Unlike the close case, we are not OR'ing the register. Set 1 to clear.*/
        *switchClearReg = switchMask;
        break;
    }
}


/*******************************************************************************
* Function Name: Cy_SAR_GetAnalogSwitch
****************************************************************************//**
*
* Return the state (open or close) of SARMUX switches.
*
* \param base
* Pointer to structure describing registers
*
* \param switchSelect
* The switch register that contains the desired switches. Select a value
* from \ref cy_en_sar_switch_register_sel_t.
*
* \return
* Each bit corresponds to a single switch, where a bit value of 0 is open
* and 1 is closed.
* Compare this value to the switch masks in \ref cy_en_sar_mux_switch_fw_ctrl_t.
*
*******************************************************************************/
uint32_t Cy_SAR_GetAnalogSwitch(const SAR_Type *base, cy_en_sar_switch_register_sel_t switchSelect)
{
    CY_ASSERT_L3(CY_SAR_SWITCHSELECT(switchSelect));
    (void)switchSelect; /* Suppress warning */
    return SAR_MUX_SWITCH0(base);
}


/*******************************************************************************
* Function Name: Cy_SAR_SetSwitchSarSeqCtrl
****************************************************************************//**
*
* Enable or disable SARSEQ control of one or more switches.
* Previously configured switches are untouched.
*
* \param base
* Pointer to structure describing registers
*
* \param switchMask
* The mask of the switches.
* Select one or more values from the \ref cy_en_sar_mux_switch_sq_ctrl_t enum
* and "OR" them together.
*
* \param ctrl
* Enable or disable SARSEQ control. Select a value from \ref cy_en_sar_switch_sar_seq_ctrl_t.
*
* \return None
*
* \funcusage
*
* \snippet sar/snippet/main.c SAR_SNIPPET_SET_SWITCH_SAR_SEQ_CTRL
*
*******************************************************************************/
void Cy_SAR_SetSwitchSarSeqCtrl(SAR_Type *base, uint32_t switchMask, cy_en_sar_switch_sar_seq_ctrl_t ctrl)
{
    CY_ASSERT_L2(CY_SAR_SQMASK(switchMask));
    CY_ASSERT_L3(CY_SAR_SQCTRL(ctrl));

    switch(ctrl)
    {
    case CY_SAR_SWITCH_SEQ_CTRL_ENABLE:
        SAR_MUX_SWITCH_SQ_CTRL(base) |= switchMask;
        break;
    case CY_SAR_SWITCH_SEQ_CTRL_DISABLE:
    default:
        SAR_MUX_SWITCH_SQ_CTRL(base) &= ~switchMask;
        break;
    }
}


/*******************************************************************************
* Function Name: Cy_SAR_DeepSleepCallback
****************************************************************************//**
*
* Callback to prepare the SAR before entering Deep Sleep
* and to re-enable the SAR after exiting Deep Sleep.
*
* \param callbackParams
* Pointer to structure of type \ref cy_stc_syspm_callback_params_t
*
* \param mode
* Callback mode, see \ref cy_en_syspm_callback_mode_t
*
* \return
* See \ref cy_en_syspm_status_t
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_DEEPSLEEP_CALLBACK
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SAR_DeepSleepCallback(const cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode)
{
    cy_en_syspm_status_t returnValue = CY_SYSPM_SUCCESS;

    if (CY_PASS_V1)
    {
        if (CY_SYSPM_BEFORE_TRANSITION == mode)
        { /* Actions that should be done before entering the Deep Sleep mode */
            Cy_SAR_DeepSleep((SAR_Type *)callbackParams->base);
        }
        else if (CY_SYSPM_AFTER_TRANSITION == mode)
        { /* Actions that should be done after exiting the Deep Sleep mode */
            Cy_SAR_Wakeup((SAR_Type *)callbackParams->base);
        }
        else
        { /* Does nothing in other modes */
        }
    }

    return returnValue;
}


/*******************************************************************************
* Function Name: Cy_SAR_ScanCountEnable
****************************************************************************//**
*
* Enables the Scanning Counter.
* Suitable for PASS_V2.
*
* \param base
* Pointer to the structure of SAR instance registers.
*
* \return The status:
* - CY_SAR_BAD_PARAM - either the feature is not supported by this IP version or
*                      the injection channel is triggered and not tailgating.
* - CY_SAR_SUCCESS - the SAR Scanning Counter feature is successfully enabled.
*
* \funcusage \snippet sar/snippet/main.c SNIPPET_SAR_DS
*
*******************************************************************************/
cy_en_sar_status_t Cy_SAR_ScanCountEnable(const SAR_Type * base)
{
    cy_en_sar_status_t retVal = CY_SAR_BAD_PARAM;

    if (!CY_PASS_V1)
    {
        uint32_t interruptState = Cy_SysLib_EnterCriticalSection();
        uint32_t locInjChanCfg = SAR_INJ_CHAN_CONFIG(base);
        /* If the injection channel is triggered the Scan Counter could be enabled only if the injection channel configured as tailgating  */
        if ((0UL != (locInjChanCfg & SAR_V2_INJ_CHAN_CONFIG_INJ_START_EN_Msk)) ? (0UL == (locInjChanCfg & SAR_V2_INJ_CHAN_CONFIG_INJ_TAILGATING_Msk)) : true)
        {
            PASS_SAR_OVR_CTRL(CY_PASS_V2_ADDR) |= CY_SAR_INSTANCE_MASK(base) << PASS_V2_SAR_OVR_CTRL_TR_SCAN_CNT_SEL_Pos;
            Cy_SysLib_ExitCriticalSection(interruptState);
            retVal = CY_SAR_SUCCESS;
        }
    }

    return (retVal);
}
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');


#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXS40PASS_SAR */

/* [] END OF FILE */
