/***************************************************************************/ /**
* \file cyhal_adc_sar.c
*
* \brief
* Provides a high level interface for interacting with the Cypress Analog/Digital
* converter. This interface abstracts out the chip specific details. If any chip
* specific functionality is necessary, or performance is critical the low level
* functions can be used directly.
*
********************************************************************************
* \copyright
* Copyright 2018-2022 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
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

/**
 * \addtogroup group_hal_impl_adc ADC (Analog Digital Converter)
 * \ingroup group_hal_impl
 * \{
 * \section cyhal_adc_impl_features Features
 * The CAT1A/CAT2 (PMG/PSoC™ 4/PSoC™ 6/XMC7™) ADC supports the following features:
 * * Resolution: 12 bit
 * * Only @ref CYHAL_POWER_LEVEL_DEFAULT and CYHAL_POWER_LEVEL_OFF are defined. The default power
 *   level will automatically adjust based on smple rate.
 * * Average counts: 2, 4, 8, 16, 32, 64, 128, 256
 *
 * CAT1A supports DMA-based transfer when using @ref cyhal_adc_read_async. When using @ref
 * cyhal_adc_read_async_uv, only interrupt-driven software copy is supported.
 *
 * CAT1A/CAT2 support the following features:
 * * Up to four unique acquisition times
 *
 * CAT1C supports the following features:
 * * Unique acquisition time per channel
 * * Single-ended channels only, referenced to VREF
 * * Internal VREF only
 * * No external bypass
 *
 * After initializing the ADC or changing the reference or bypass selection, it may be necessary to wait up to
 * 210 us for the reference buffer to settle. See the architecture TRM (Analog Subsystem -> SAR ADC ->
 * Architecture -> SARREF) for device specific guidance.
 *
 * \note On CAT1C devices, the \ref cyhal_source_t object populated by \ref cyhal_adc_enable_output is only valid
 * as long as the last channel initialized is not disabled, and no new channels are added. If it necessary to
 * make any of these changes, disable the output using \ref cyhal_adc_disable_output, then re-enable
 * \} group_hal_impl_adc
 */

#include <cmsis_compiler.h>

#include "cyhal_adc.h"
#include "cyhal_analog_common.h"
#include "cyhal_clock.h"
#include "cyhal_dma.h"
#include "cyhal_gpio.h"
#include "cyhal_hwmgr.h"
#include "cyhal_utils.h"
#include "cyhal_irq_impl.h"
#include "cyhal_interconnect.h"
#include "cyhal_syspm.h"
#include "cyhal_system.h"
#include <string.h>

#if (_CYHAL_DRIVER_AVAILABLE_ADC_SAR)

#if defined(CY_IP_MXS40PASS_SAR_INSTANCES)
#define _CYHAL_ADC_SAR_INSTANCES CY_IP_MXS40PASS_SAR_INSTANCES
#elif defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
#define _CYHAL_ADC_SAR_INSTANCES CY_IP_MXS40EPASS_ESAR_INSTANCES
#elif defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
#define _CYHAL_ADC_SAR_INSTANCES CY_IP_M0S8PASS4A_SAR_INSTANCES
#endif

/* ESAR only sign extends to 16 bits, but we return 32-bit signed values. This means that
 * while we can technically read the ADC results using DMA, doing so doesn't bring any
 * real value because still have to post-process the results using the CPU to achieve
 * proper sign extension. We do this on existing CAT1A and CAT2 devices because we had
 * already released DMA support before the issue was realized and we can't remove it
 * without breaking BWC, but extending this behavior to new devices would just be misleading */
#if (CYHAL_DRIVER_AVAILABLE_DMA && !defined(CY_IP_MXS40EPASS_ESAR_INSTANCES))
    #define _CYHAL_ADC_DMA_SUPPORTED (1u)
#else
    #define _CYHAL_ADC_DMA_SUPPORTED (0u)
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

// The PDL for M0S8 PASS doesn't take the register as an argument; it always writes to MUX_SWITCH0
#if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
    #define CY_SAR_MAX_NUM_CHANNELS CY_SAR_SEQ_NUM_CHANNELS
    #define _CYHAL_ADC_SARSEQ_STATE(state) (state)
    #define _CYHAL_ADC_SWITCH_STATE(state) (state)
    #define _CYHAL_ADC_SET_SWITCH(base, mask, state) Cy_SAR_SetAnalogSwitch((base), (mask), (state))
#else
    #define _CYHAL_ADC_SWITCH_STATE(state) ((state) ? CY_SAR_SWITCH_CLOSE : CY_SAR_SWITCH_OPEN)
    #define _CYHAL_ADC_SARSEQ_STATE(state) ((state) ? CY_SAR_SWITCH_SEQ_CTRL_ENABLE : CY_SAR_SWITCH_SEQ_CTRL_DISABLE)
    #define _CYHAL_ADC_SET_SWITCH(base, mask, state) Cy_SAR_SetAnalogSwitch((base), CY_SAR_MUX_SWITCH0, (mask), _CYHAL_ADC_SWITCH_STATE((state)))
#endif

#if defined(CY_IP_MXS40EPASS_ESAR)
    const uint32_t _CYHAL_ADC_MIN_ACQUISITION_TIME_NS = 300u;
#else
    const uint32_t _CYHAL_ADC_MIN_ACQUISITION_TIME_NS = 167;
#endif

#if (CY_IP_MXS40PASS_SAR_INSTANCES == 1) && !defined(CY_DEVICE_PSOC6A256K)
    #define _CYHAL_ADC_SINGLE_UNSUFFIXED
#endif

#if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
static PASS_SAR_Type *const _cyhal_adc_base[] =
#else
static SAR_Type *const _cyhal_adc_base[] =
#endif
{
#if defined(_CYHAL_ADC_SINGLE_UNSUFFIXED)
    SAR,
#else
#if (_CYHAL_ADC_SAR_INSTANCES >= 1)
#if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
    PASS0_SAR0,
#else
    SAR0,
#endif
#endif
#if (_CYHAL_ADC_SAR_INSTANCES >= 2)
#if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
    PASS0_SAR1,
#else
    SAR1,
#endif
#endif
#if (_CYHAL_ADC_SAR_INSTANCES >= 3)
#if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
    PASS0_SAR2,
#else
    SAR2,
#endif
#endif
#if (_CYHAL_ADC_SAR_INSTANCES >= 4)
    #warning Unhandled SAR instance count
#endif
#endif
};

static const en_clk_dst_t _cyhal_adc_clock[] =
{
#if defined(_CYHAL_ADC_SINGLE_UNSUFFIXED)
    PCLK_PASS_CLOCK_SAR,
#elif (CY_IP_M0S8PASS4A_SAR_INSTANCES == 1)
    PCLK_PASS0_CLOCK_SAR,
#elif (CY_IP_M0S8PASS4A_SAR_INSTANCES == 2)
    PCLK_PASS0_CLOCK_SAR,
    PCLK_PASS1_CLOCK_SAR,
#else
    #if (_CYHAL_ADC_SAR_INSTANCES >= 1)
        #if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
        PCLK_PASS0_CLOCK_SAR0,
        #else
        PCLK_PASS_CLOCK_SAR0,
        #endif
    #endif /* (_CYHAL_ADC_SAR_INSTANCES >= 1) */
    #if (_CYHAL_ADC_SAR_INSTANCES >= 2)
        #if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
        PCLK_PASS0_CLOCK_SAR1,
        #else
        PCLK_PASS_CLOCK_SAR1,
        #endif
    #endif /* (_CYHAL_ADC_SAR_INSTANCES >= 2) */
    #if (_CYHAL_ADC_SAR_INSTANCES >= 3)
        #if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
        PCLK_PASS0_CLOCK_SAR2,
        #else
        PCLK_PASS_CLOCK_SAR2,
        #endif
    #endif /* (_CYHAL_ADC_SAR_INSTANCES >= 3) */
    #if (_CYHAL_ADC_SAR_INSTANCES >= 4)
    #warning Unhandled SAR instance count
    #endif
#endif
};

static const cyhal_source_t _cyhal_adc_tr_out[] =
{
#if defined(_CYHAL_ADC_SINGLE_UNSUFFIXED)
    CYHAL_TRIGGER_PASS_TR_SAR_OUT,
#elif (CY_IP_M0S8PASS4A_SAR_INSTANCES == 1)
    CYHAL_TRIGGER_PASS0_TR_SAR_OUT,
#elif (CY_IP_MXS40PASS_SAR_INSTANCES == 1)
    CYHAL_TRIGGER_PASS_TR_SAR_OUT0,
#elif (CY_IP_MXS40PASS_SAR_INSTANCES == 2)
    CYHAL_TRIGGER_PASS_TR_SAR_OUT0,
    CYHAL_TRIGGER_PASS_TR_SAR_OUT1,
#elif (CY_IP_M0S8PASS4A_SAR_INSTANCES == 2)
    CYHAL_TRIGGER_PASS0_TR_SAR_OUT,
    CYHAL_TRIGGER_PASS1_TR_SAR_OUT,
#elif defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
    /* There are two "tr_gen" outputs per SAR, but we only expose one type of trigger
     * so we simplify and only use the first trigger per SAR */
    #if (CY_IP_MXS40EPASS_ESAR_INSTANCES > 0)
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT0_EDGE,
    #endif
    #if (CY_IP_MXS40EPASS_ESAR_INSTANCES > 1)
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT2_EDGE,
    #endif
    #if (CY_IP_MXS40EPASS_ESAR_INSTANCES > 2)
    CYHAL_TRIGGER_PASS0_TR_SAR_GEN_OUT4_EDGE,
    #endif
    #if (CY_IP_MXS40EPASS_ESAR_INSTANCES > 3)
    #error "Unhandled EPASS_ESAR count"
    #endif
#else
    #warning Unhandled SAR instance count
#endif
};

#if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
static uint8_t _cyhal_adc_last_enabled(const cyhal_adc_t* obj); /* Or last channel, if no channel is enabled */
#endif

static const cyhal_dest_t _cyhal_adc_tr_in[] =
{
#if defined(_CYHAL_ADC_SINGLE_UNSUFFIXED)
    CYHAL_TRIGGER_PASS_TR_SAR_IN,
#elif (CY_IP_M0S8PASS4A_SAR_INSTANCES == 1)
    CYHAL_TRIGGER_PASS0_TR_SAR_IN,
#elif (CY_IP_MXS40PASS_SAR_INSTANCES == 1)
    CYHAL_TRIGGER_PASS_TR_SAR_IN0,
#elif (CY_IP_MXS40PASS_SAR_INSTANCES == 2)
    CYHAL_TRIGGER_PASS_TR_SAR_IN0,
    CYHAL_TRIGGER_PASS_TR_SAR_IN1,
#elif (CY_IP_M0S8PASS4A_SAR_INSTANCES == 2)
    CYHAL_TRIGGER_PASS0_TR_SAR_IN,
    CYHAL_TRIGGER_PASS1_TR_SAR_IN,
#elif defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
    /* We don't use groups, so we always trigger the SAR starting from channel 0 */
    #if (CY_IP_MXS40EPASS_ESAR_INSTANCES > 0)
    CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN0,
    #endif
    #if (CY_IP_MXS40EPASS_ESAR_INSTANCES > 1)
    (cyhal_dest_t)(CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN0 + PASS_SAR_SLICE_NR0_SAR_SAR_CHAN_NR),
    #endif
    #if (CY_IP_MXS40EPASS_ESAR_INSTANCES > 2)
    (cyhal_dest_t)(CYHAL_TRIGGER_PASS0_TR_SAR_CH_IN0
                    + PASS_SAR_SLICE_NR0_SAR_SAR_CHAN_NR + PASS_SAR_SLICE_NR1_SAR_SAR_CHAN_NR),
    #endif
    #if (CY_IP_MXS40EPASS_ESAR_INSTANCES > 3)
    #error "Unhandled EPASS_ESAR count"
    #endif
#else
    #warning Unhandled SAR instance count
#endif
};

static cyhal_adc_t* _cyhal_adc_config_structs[_CYHAL_ADC_SAR_INSTANCES];

#if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
static _cyhal_system_irq_t _cyhal_adc_calc_channel_irq(uint8_t adc_num, uint8_t channel_num)
{
    _cyhal_system_irq_t base = pass_0_interrupts_sar_0_IRQn;
    #if (CY_IP_MXS40EPASS_ESAR_INSTANCES > 1)
    if(adc_num > 0u)
    {
        base = (_cyhal_system_irq_t)(base + PASS_SAR_SLICE_NR0_SAR_SAR_CHAN_NR);
    }
    #endif
    #if (CY_IP_MXS40EPASS_ESAR_INSTANCES > 2)
    if(adc_num > 1u)
    {
        base = (_cyhal_system_irq_t)(base + PASS_SAR_SLICE_NR1_SAR_SAR_CHAN_NR);
    }
    #endif
    #if (CY_IP_MXS40EPASS_ESAR_INSTANCES > 3)
    #error "Unhandled ADC instance count"
    #endif

    _cyhal_system_irq_t irq = (_cyhal_system_irq_t)(base + channel_num);
    return irq;
}
#else
static const _cyhal_system_irq_t _cyhal_adc_irq_n[] =
{
#if defined(_CYHAL_ADC_SINGLE_UNSUFFIXED)
    pass_interrupt_sar_IRQn,
#elif (CY_IP_M0S8PASS4A_SAR_INSTANCES == 1)
    pass_0_interrupt_sar_IRQn,
#elif (CY_IP_MXS40PASS_SAR_INSTANCES == 1)
    pass_interrupt_sar_0_IRQn,
#elif (CY_IP_MXS40PASS_SAR_INSTANCES == 2)
    pass_interrupt_sar_0_IRQn,
    pass_interrupt_sar_1_IRQn,
#elif (CY_IP_M0S8PASS4A_SAR_INSTANCES == 2)
    pass_0_interrupt_sar_IRQn,
    pass_0_interrupt_sar_IRQn,
#else
    #warning Unhandled SAR instance count
#endif
};
#endif

#if defined(CY_IP_MXS40EPASS_ESAR)
// Expected to be lowest value possible
#define _CYHAL_ADC_VBG_CHANNEL_IDX  (0)
static cyhal_adc_channel_t _cyhal_adc_vbg_channels[CY_IP_MXS40EPASS_ESAR_INSTANCES];
#endif /* defined(CY_IP_MXS40EPASS_ESAR) */

static uint8_t _cyhal_adc_get_block_from_irqn(_cyhal_system_irq_t irqn)
{
#if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
    uint8_t channel_offset = (uint8_t)(irqn - pass_0_interrupts_sar_0_IRQn);
    #if (CY_IP_MXS40EPASS_ESAR_INSTANCES > 3u)
    #error "Unhandled ADC instance count"
    #endif
    #if (CY_IP_MXS40EPASS_ESAR_INSTANCES > 2u)
    if(channel_offset >= PASS_SAR_SLICE_NR1_SAR_SAR_CHAN_NR + PASS_SAR_SLICE_NR0_SAR_SAR_CHAN_NR)
    {
        return 2u;
    }
    #endif
    #if (CY_IP_MXS40EPASS_ESAR_INSTANCES > 1u)
    if(channel_offset >= PASS_SAR_SLICE_NR0_SAR_SAR_CHAN_NR)
    {
        return 1u;
    }
    #endif
    return 0u;
#else
    switch (irqn)
    {
#if defined(_CYHAL_ADC_SINGLE_UNSUFFIXED)
    case pass_interrupt_sar_IRQn:
        return 0;
#elif (CY_IP_M0S8PASS4A_SAR_INSTANCES == 1)
    case pass_0_interrupt_sar_IRQn:
        return 0;
#elif (CY_IP_MXS40PASS_SAR_INSTANCES == 1)
    case pass_interrupt_sar_0_IRQn:
        return 0;
#elif (CY_IP_MXS40PASS_SAR_INSTANCES == 2)
    case pass_interrupt_sar_0_IRQn:
        return 0;
    case pass_interrupt_sar_1_IRQn:
        return 1;
#elif (CY_IP_M0S8PASS4A_SAR_INSTANCES == 2)
    case pass_0_interrupt_sar_IRQn:
        return 0;
    case pass_1_interrupt_sar_IRQn:
        return 1;
#else
    #warning Unhandled SAR instance count
#endif
    default:
        CY_ASSERT(false); // Should never be called with a non-SAR IRQn
        return 0;
    }
#endif
}

#if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
static const cy_stc_sar2_config_t _CYHAL_ADC_DEFAULT_PDL_CONFIG =
{
    .preconditionTime = 1u,
    .powerupTime = 0u,
    .enableIdlePowerDown = 0u,
    .msbStretchMode = CY_SAR2_MSB_STRETCH_MODE_1CYCLE, /* Give similar behavior to MXS40PASS */
    .enableHalfLsbConv = true,
    .sarMuxEnable = true,
    .adcEnable = true,
    .sarIpEnable = true,
    .channelConfig = { NULL } /* Channels will be individually configured */
};

static const cy_stc_sar2_channel_config_t _CYHAL_ADC_DEFAULT_PDL_CHAN_CONFIG =
{
    /* channelHwEnable will be populated from the user's configuration */
    /* triggerSelection will be populated based on continous scanning configuration */
    .preenptionType = CY_SAR2_PREEMPTION_FINISH_RESUME,
    /* isGroupEnd is populated from the position relative to other enabled channels */
    .doneLevel = CY_SAR2_DONE_LEVEL_PULSE,
    .portAddress = CY_SAR2_PORT_ADDRESS_SARMUX0, /* Despite what the name implies, this means use our own SarMux */
    /* pinAddress will be populated based on user's configuration */
    .extMuxSelect = 0u, /* We don't support the external mux features in the HAL */
    .extMuxEnable = false,
    .preconditionMode = CY_SAR2_PRECONDITION_MODE_OFF, /* Consistent with MXS40PASS */
    .overlapDiagMode = CY_SAR2_OVERLAP_DIAG_MODE_OFF, /* Other settings are for debugging */
    /* sampleTime will be computed based on channel configuration */
    .calibrationValueSelect = CY_SAR2_CALIBRATION_VALUE_REGULAR,
    /* postProcessingMode will be populated based on whether averaging is enabled */
    .resultAlignment = CY_SAR2_RESULT_ALIGNMENT_RIGHT,
    .signExtention = CY_SAR2_SIGN_EXTENTION_UNSIGNED,
    /* averageCount is populated based on global adc configuration. rightShift is populated based on average vs. accumulate */
    .rangeDetectionMode = CY_SAR2_RANGE_DETECTION_MODE_BELOW_LO, /* Placeholder value, range detection is not exposed */
    .rangeDetectionLoThreshold = 0u,
    .rangeDetectionHiThreshold = 0u,
    .interruptMask = 0u, /* interruptMask will be updated if this is the last channel */
};

#elif defined(CY_IP_MXS40PASS_SAR_INSTANCES)
/* OR in the following user-configurable values: vref, bypass, vneg, */
#define _CYHAL_ADC_DEFAULT_CTRL ((uint32_t)CY_SAR_VREF_PWR_100 | (uint32_t)CY_SAR_VREF_SEL_BGR \
                                | (uint32_t)CY_SAR_BYPASS_CAP_DISABLE | (uint32_t)CY_SAR_CTRL_NEGVREF_HW \
                                | (uint32_t)CY_SAR_CTRL_COMP_DLY_12   | (uint32_t)CY_SAR_COMP_PWR_100 \
                                | (uint32_t)CY_SAR_DEEPSLEEP_SARMUX_OFF | (uint32_t)CY_SAR_SARSEQ_SWITCH_ENABLE)

/* Default configuration. OR in the average count, and average mode */
#define _CYHAL_ADC_DEFAULT_SAMPLE ((uint32_t)CY_SAR_RIGHT_ALIGN | (uint32_t)CY_SAR_TRIGGER_MODE_FW_ONLY \
                                 | (uint32_t)CY_SAR_SINGLE_ENDED_SIGNED | (uint32_t)CY_SAR_DIFFERENTIAL_SIGNED \
                                 | (uint32_t)CY_SAR_TRIGGER_MODE_FW_ONLY)

static const cy_stc_sar_config_t _CYHAL_ADC_DEFAULT_PDL_CONFIG =
{
    /* .ctrl is populated from _CYHAL_ADC_DEFAULT_CTRL plus the user's configuration */
    /* .sampleCtrl is puopulated from _CYHAL_ADC_DEFAULT_SAMPLE plus the user's configuration */
    .sampleTime01 = (10UL << SAR_SAMPLE_TIME01_SAMPLE_TIME0_Pos), // Sample times 1, 2, and 3 are not used
    .sampleTime23 = 0UL,
    .rangeThres = (0UL << CY_SAR_RANGE_HIGH_SHIFT) | (0UL << CY_SAR_RANGE_LOW_SHIFT),
    .rangeCond = CY_SAR_RANGE_COND_BELOW,
    .chanEn = 0UL,
    .chanConfig = { 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL},
    .intrMask = (uint32_t) CY_SAR_INTR_EOS,
    .satIntrMask = 0UL,
    .rangeIntrMask = 0UL,
    .muxSwitch = 0UL,
    .muxSwitchSqCtrl = 0UL,
    .configRouting = true,
    /* .vrefMvValue is populated from the user's configuration */
};

#endif

#define _CYHAL_ADC_RESOLUTION 12u
#define _CYHAL_ADC_INTERNAL_VREF_MV 1200UL
#define _CYHAL_ADC_CONVERSION_CYCLES (_CYHAL_ADC_RESOLUTION + 2)

static const cyhal_adc_config_t _CYHAL_ADC_DEFAULT_CONFIG =
{
    .resolution          = _CYHAL_ADC_RESOLUTION,
    .average_count       = 1,
    .average_mode_flags  = CYHAL_ADC_AVG_MODE_AVERAGE,
    .continuous_scanning = true,
#if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
    .vneg                = CYHAL_ADC_VNEG_VSSA,
#else
    .vneg                = CYHAL_ADC_VNEG_VREF,
#endif
    .vref                = CYHAL_ADC_REF_INTERNAL,
    .ext_vref            = NC,
    .ext_vref_mv         = 0u,
    .is_bypassed         = false,
    .bypass_pin          = NC,
};

/*******************************************************************************
*       Internal helper functions
*******************************************************************************/
#if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES) /* Not specific to this IP, but no other IP needs these */
static uint8_t _cyhal_adc_first_enabled(const cyhal_adc_t* obj) /* Or first channel, if no channel is enabled */
{
    uint8_t first_enabled = 0u;
    for(uint8_t i = 0; i < CY_SAR_MAX_NUM_CHANNELS; ++i)
    {
        if(NULL != obj->channel_config[i] && obj->base->CH[i].ENABLE)
        {
            first_enabled = i;
            break;
        }
    }

    return first_enabled;
}

static uint8_t _cyhal_adc_last_enabled(const cyhal_adc_t* obj) /* Or last channel, if no channel is enabled */
{
    uint8_t last_enabled = CY_SAR_MAX_NUM_CHANNELS - 1u;
    /* NOT uint, or the loop will never terminate */
    for(int i = CY_SAR_MAX_NUM_CHANNELS - 1; i >= 0; --i)
    {
        if(NULL != obj->channel_config[i] && obj->base->CH[i].ENABLE)
        {
            last_enabled = i;
            break;
        }
    }

    return last_enabled;
}

static int32_t _cyhal_adc_counts_to_uvolts(cyhal_adc_t* obj, uint8_t channel, uint32_t counts)
{
    CY_UNUSED_PARAMETER(obj); /* We're always single-ended with vneg set to vssa */
    CY_UNUSED_PARAMETER(channel); /* We're always single-ended with vneg set to vssa */

    /* 900000 uV (0.9V) is value from SAR2 ADC PDL driver documentation and stands for voltage on VBG diode.
    *  It always remains stable and it is recommended to be used as reference in ADC counts to Voltage calculations */
    return (int32_t)((counts * 900000.0f) / obj->vbg_last_value);
}

static void _cyhal_adc_extract_channel_conf(cyhal_adc_t* adc, cy_stc_sar2_channel_config_t* channel_configs)
{
    for(uint8_t i = 0; i < CY_SAR_MAX_NUM_CHANNELS; ++i)
    {
        /* The ADC channel configuration structs do not come up with determistic values, so force to 0 any channel
           which we have not explicitly configured */
        if(NULL == adc->channel_config[i])
        {
            memset(&channel_configs[i], 0u, sizeof(cy_stc_sar2_channel_config_t));;
        }
        else
        {
            channel_configs[i].triggerSelection = (cy_en_sar2_trigger_selection_t)_FLD2VAL(PASS_SAR_CH_TR_CTL_SEL, adc->base->CH[i].TR_CTL);
            channel_configs[i].channelPriority  = (uint8_t)_FLD2VAL(PASS_SAR_CH_TR_CTL_PRIO, adc->base->CH[i].TR_CTL);
            channel_configs[i].preenptionType   = (cy_en_sar2_preemption_type_t)_FLD2VAL(PASS_SAR_CH_TR_CTL_PREEMPT_TYPE, adc->base->CH[i].TR_CTL);
            channel_configs[i].isGroupEnd       = (bool)_FLD2BOOL(PASS_SAR_CH_TR_CTL_GROUP_END, adc->base->CH[i].TR_CTL);
            channel_configs[i].doneLevel        = (cy_en_sar2_done_level_t)_FLD2BOOL(PASS_SAR_CH_TR_CTL_DONE_LEVEL, adc->base->CH[i].TR_CTL);

            channel_configs[i].pinAddress             = (cy_en_sar2_pin_address_t)_FLD2VAL(PASS_SAR_CH_SAMPLE_CTL_PIN_ADDR, adc->base->CH[i].SAMPLE_CTL);
            channel_configs[i].portAddress            = (cy_en_sar2_port_address_t)_FLD2VAL(PASS_SAR_CH_SAMPLE_CTL_PORT_ADDR, adc->base->CH[i].SAMPLE_CTL);
            channel_configs[i].extMuxSelect           = (uint8_t)_FLD2VAL(PASS_SAR_CH_SAMPLE_CTL_EXT_MUX_SEL, adc->base->CH[i].SAMPLE_CTL);
            channel_configs[i].extMuxEnable           = (bool)_FLD2BOOL(PASS_SAR_CH_SAMPLE_CTL_EXT_MUX_EN, adc->base->CH[i].SAMPLE_CTL);
            channel_configs[i].preconditionMode       = (cy_en_sar2_precondition_mode_t)_FLD2VAL(PASS_SAR_CH_SAMPLE_CTL_PRECOND_MODE, adc->base->CH[i].SAMPLE_CTL);
            channel_configs[i].overlapDiagMode        = (cy_en_sar2_overlap_diag_mode_t)_FLD2VAL(PASS_SAR_CH_SAMPLE_CTL_OVERLAP_DIAG, adc->base->CH[i].SAMPLE_CTL);
            channel_configs[i].sampleTime             = (uint16_t)_FLD2VAL(PASS_SAR_CH_SAMPLE_CTL_SAMPLE_TIME, adc->base->CH[i].SAMPLE_CTL);
            channel_configs[i].calibrationValueSelect = (cy_en_sar2_calibration_value_select_t)_FLD2VAL(PASS_SAR_CH_SAMPLE_CTL_ALT_CAL, adc->base->CH[i].SAMPLE_CTL);

            channel_configs[i].postProcessingMode = (cy_en_sar2_post_processing_mode_t)_FLD2VAL(PASS_SAR_CH_POST_CTL_POST_PROC, adc->base->CH[i].POST_CTL);
            channel_configs[i].resultAlignment    = (cy_en_sar2_result_alignment_t)_FLD2VAL(PASS_SAR_CH_POST_CTL_LEFT_ALIGN, adc->base->CH[i].POST_CTL);
            channel_configs[i].signExtention      = (cy_en_sar2_sign_extention_t)_FLD2VAL(PASS_SAR_CH_POST_CTL_SIGN_EXT, adc->base->CH[i].POST_CTL);
            channel_configs[i].averageCount       = (uint8_t)_FLD2VAL(PASS_SAR_CH_POST_CTL_AVG_CNT, adc->base->CH[i].POST_CTL);
            channel_configs[i].rightShift         = (uint8_t)_FLD2VAL(PASS_SAR_CH_POST_CTL_SHIFT_R, adc->base->CH[i].POST_CTL);
            channel_configs[i].rangeDetectionMode = (cy_en_sar2_range_detection_mode_t)_FLD2VAL(PASS_SAR_CH_POST_CTL_RANGE_MODE, adc->base->CH[i].POST_CTL);

            channel_configs[i].rangeDetectionLoThreshold = (uint16_t)_FLD2VAL(PASS_SAR_CH_RANGE_CTL_RANGE_LO, adc->base->CH[i].RANGE_CTL);
            channel_configs[i].rangeDetectionHiThreshold = (uint16_t)_FLD2VAL(PASS_SAR_CH_RANGE_CTL_RANGE_HI, adc->base->CH[i].RANGE_CTL);

            channel_configs[i].channelHwEnable = (bool)(adc->base->CH[i].ENABLE);
            channel_configs[i].interruptMask = Cy_SAR2_Channel_GetInterruptMask(adc->base, i);
        }
    }
}
#endif

static void _cyhal_adc_update_intr_mask(const cyhal_adc_t* obj)
{
    bool needs_eos = (obj->async_scans_remaining > 0) /* Async transfer in progress */
                    || (false == obj->conversion_complete) /* ISR needs to flag that a conversion finished */
   #if !defined(CY_IP_MXS40EPASS_ESAR)
                    || obj->stop_after_scan /* ISR needs to stop the conversion after the scan finishes */
   #endif
                    || (0u != (CYHAL_ADC_EOS & obj->user_enabled_events)); /* User requested EOS event */

    #if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
    uint8_t last_channel = _cyhal_adc_last_enabled(obj);
    uint32_t current_mask = Cy_SAR2_Channel_GetInterruptMask(obj->base, last_channel);
    uint32_t new_mask;
    if(needs_eos)
    {
        new_mask = current_mask | CY_SAR2_INT_GRP_DONE;
    }
    else
    {
        new_mask = current_mask & ~CY_SAR2_INT_GRP_DONE;
    }

    Cy_SAR2_Channel_ClearInterrupt(obj->base, last_channel, new_mask & (~current_mask));
    Cy_SAR2_Channel_SetInterruptMask(obj->base, last_channel, new_mask);
    #else
    uint32_t current_mask = Cy_SAR_GetInterruptMask(obj->base);
    uint32_t new_mask;
    if(needs_eos)
    {
        new_mask = current_mask | CY_SAR_INTR_EOS;
    }
    else
    {
        new_mask = current_mask & ~CY_SAR_INTR_EOS;
    }

    Cy_SAR_ClearInterrupt(obj->base, new_mask & (~current_mask));
    Cy_SAR_SetInterruptMask(obj->base, new_mask);
    #endif
}

static uint8_t _cyhal_adc_max_configured_channel(const cyhal_adc_t* obj)
{
    uint8_t max = 0;
    for(uint8_t i = 0; i < CY_SAR_MAX_NUM_CHANNELS; ++i)
    {
        if(NULL != obj->channel_config[i])
        {
            max = i;
        }
    }
    return max;
}

static cyhal_source_t _cyhal_adc_calculate_source(cyhal_adc_t *obj)
{
    CY_ASSERT(obj->resource.block_num < _CYHAL_ADC_SAR_INSTANCES);
    return _cyhal_adc_tr_out[obj->resource.block_num];
}

#if !defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
static uint32_t _cyhal_adc_get_mux_switch_control(cyhal_gpio_t gpio)
{
    static const uint32_t mux_lookup[] =
    {
#if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
        SAR_MUX_SWITCH_HW_CTRL_MUX_HW_CTRL_P0_Msk,
        SAR_MUX_SWITCH_HW_CTRL_MUX_HW_CTRL_P1_Msk,
        SAR_MUX_SWITCH_HW_CTRL_MUX_HW_CTRL_P2_Msk,
        SAR_MUX_SWITCH_HW_CTRL_MUX_HW_CTRL_P3_Msk,
        SAR_MUX_SWITCH_HW_CTRL_MUX_HW_CTRL_P4_Msk,
        SAR_MUX_SWITCH_HW_CTRL_MUX_HW_CTRL_P5_Msk,
        SAR_MUX_SWITCH_HW_CTRL_MUX_HW_CTRL_P6_Msk,
        SAR_MUX_SWITCH_HW_CTRL_MUX_HW_CTRL_P7_Msk,
#else
        (uint32_t)CY_SAR_MUX_SQ_CTRL_P0,
        (uint32_t)CY_SAR_MUX_SQ_CTRL_P1,
        (uint32_t)CY_SAR_MUX_SQ_CTRL_P2,
        (uint32_t)CY_SAR_MUX_SQ_CTRL_P3,
        (uint32_t)CY_SAR_MUX_SQ_CTRL_P4,
        (uint32_t)CY_SAR_MUX_SQ_CTRL_P5,
        (uint32_t)CY_SAR_MUX_SQ_CTRL_P6,
        (uint32_t)CY_SAR_MUX_SQ_CTRL_P7
#endif
    };
    uint8_t pin = CYHAL_GET_PIN(gpio);
    CY_ASSERT(pin < sizeof(mux_lookup)/sizeof(mux_lookup[0]));
    return mux_lookup[pin];
}

static uint32_t _cyhal_adc_get_fw_switch_control(cyhal_gpio_t gpio, bool is_vplus)
{
    static const uint32_t vplus_lookup[] =
    {
        (uint32_t)CY_SAR_MUX_FW_P0_VPLUS,
        (uint32_t)CY_SAR_MUX_FW_P1_VPLUS,
        (uint32_t)CY_SAR_MUX_FW_P2_VPLUS,
        (uint32_t)CY_SAR_MUX_FW_P3_VPLUS,
        (uint32_t)CY_SAR_MUX_FW_P4_VPLUS,
        (uint32_t)CY_SAR_MUX_FW_P5_VPLUS,
        (uint32_t)CY_SAR_MUX_FW_P6_VPLUS,
        (uint32_t)CY_SAR_MUX_FW_P7_VPLUS
    };

    static const uint32_t vminus_lookup[] =
    {
        (uint32_t)CY_SAR_MUX_FW_P0_VMINUS,
        (uint32_t)CY_SAR_MUX_FW_P1_VMINUS,
        (uint32_t)CY_SAR_MUX_FW_P2_VMINUS,
        (uint32_t)CY_SAR_MUX_FW_P3_VMINUS,
        (uint32_t)CY_SAR_MUX_FW_P4_VMINUS,
        (uint32_t)CY_SAR_MUX_FW_P5_VMINUS,
        (uint32_t)CY_SAR_MUX_FW_P6_VMINUS,
        (uint32_t)CY_SAR_MUX_FW_P7_VMINUS
    };

    uint8_t pin = CYHAL_GET_PIN(gpio);
    CY_ASSERT(pin < sizeof(vplus_lookup)/sizeof(vplus_lookup[0]));
    return (uint32_t)(is_vplus ? vplus_lookup[pin] : vminus_lookup[pin]);
}

#if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
static uint32_t _cyhal_adc_get_pin_addr(cyhal_gpio_t gpio)
{
    // On this version of the PASS, there is no explicit vminus address; it is implied by vplus
    static const cy_en_sar_chan_config_port_pin_addr_t vplus_lookup[] =
    {
        CY_SAR_ADDR_SARMUX_0,
        CY_SAR_ADDR_SARMUX_1,
        CY_SAR_ADDR_SARMUX_2,
        CY_SAR_ADDR_SARMUX_3,
        CY_SAR_ADDR_SARMUX_4,
        CY_SAR_ADDR_SARMUX_5,
        CY_SAR_ADDR_SARMUX_6,
        CY_SAR_ADDR_SARMUX_7
    };
    uint8_t pin = CYHAL_GET_PIN(gpio);
    CY_ASSERT(pin < sizeof(vplus_lookup)/sizeof(vplus_lookup[0]));
    return (uint32_t)vplus_lookup[pin];
}
#else
static uint32_t _cyhal_adc_get_pin_addr(cyhal_gpio_t gpio, bool is_vplus)
{
    static const cy_en_sar_chan_config_pos_pin_addr_t vplus_lookup[] =
    {
        CY_SAR_CHAN_POS_PIN_ADDR_0,
        CY_SAR_CHAN_POS_PIN_ADDR_1,
        CY_SAR_CHAN_POS_PIN_ADDR_2,
        CY_SAR_CHAN_POS_PIN_ADDR_3,
        CY_SAR_CHAN_POS_PIN_ADDR_4,
        CY_SAR_CHAN_POS_PIN_ADDR_5,
        CY_SAR_CHAN_POS_PIN_ADDR_6,
        CY_SAR_CHAN_POS_PIN_ADDR_7
    };

    static const cy_en_sar_chan_config_neg_pin_addr_t vminus_lookup[] =
    {
        CY_SAR_CHAN_NEG_PIN_ADDR_0,
        CY_SAR_CHAN_NEG_PIN_ADDR_1,
        CY_SAR_CHAN_NEG_PIN_ADDR_2,
        CY_SAR_CHAN_NEG_PIN_ADDR_3,
        CY_SAR_CHAN_NEG_PIN_ADDR_4,
        CY_SAR_CHAN_NEG_PIN_ADDR_5,
        CY_SAR_CHAN_NEG_PIN_ADDR_6,
        CY_SAR_CHAN_NEG_PIN_ADDR_7
    };
    uint8_t pin = CYHAL_GET_PIN(gpio);
    CY_ASSERT(pin < sizeof(vplus_lookup)/sizeof(vplus_lookup[0]));
    uint32_t pin_addr = is_vplus ? (uint32_t)vplus_lookup[pin] : (uint32_t)vminus_lookup[pin];
    return is_vplus ? (pin_addr | CY_SAR_POS_PORT_ADDR_SARMUX) : (pin_addr | CY_SAR_NEG_PORT_ADDR_SARMUX);
}
#endif

static cy_en_sar_ctrl_vref_sel_t _cyhal_adc_convert_vref(cyhal_adc_vref_t vref)
{
    switch(vref)
    {
        case CYHAL_ADC_REF_INTERNAL:
            return CY_SAR_VREF_SEL_BGR;
        case CYHAL_ADC_REF_EXTERNAL:
            return CY_SAR_VREF_SEL_EXT;
        case CYHAL_ADC_REF_VDDA:
            return CY_SAR_VREF_SEL_VDDA;
        case CYHAL_ADC_REF_VDDA_DIV_2:
            return CY_SAR_VREF_SEL_VDDA_DIV_2;
        default:
            CY_ASSERT(false);
            return CY_SAR_VREF_SEL_BGR;
    }
}

static cy_rslt_t _cyhal_adc_convert_average_count(uint32_t hal_count, cy_en_sar_sample_ctrl_avg_cnt_t* pdl_count)
{
    switch(hal_count)
    {
        case 1: /* Average count of 1 is achieved by disabling averaging for all channels */
        case 2:
            *pdl_count = CY_SAR_AVG_CNT_2;
            return CY_RSLT_SUCCESS;
        case 4:
            *pdl_count = CY_SAR_AVG_CNT_4;
            return CY_RSLT_SUCCESS;
        case 8:
            *pdl_count = CY_SAR_AVG_CNT_8;
            return CY_RSLT_SUCCESS;
        case 16:
            *pdl_count = CY_SAR_AVG_CNT_16;
            return CY_RSLT_SUCCESS;
        case 32:
            *pdl_count = CY_SAR_AVG_CNT_32;
            return CY_RSLT_SUCCESS;
        case 64:
            *pdl_count = CY_SAR_AVG_CNT_64;
            return CY_RSLT_SUCCESS;
        case 128:
            *pdl_count = CY_SAR_AVG_CNT_128;
            return CY_RSLT_SUCCESS;
        case 256:
            *pdl_count = CY_SAR_AVG_CNT_256;
            return CY_RSLT_SUCCESS;
        default:
            return CYHAL_ADC_RSLT_BAD_ARGUMENT;
    }
}

static uint32_t _cyhal_adc_get_vref_mv(const cyhal_adc_config_t* hal_config)
{
    switch(hal_config->vref)
    {
        case CYHAL_ADC_REF_INTERNAL:
            return _CYHAL_ADC_INTERNAL_VREF_MV;
        case CYHAL_ADC_REF_EXTERNAL:
            CY_ASSERT(hal_config->ext_vref_mv > 0); // Should have been error checked already
            return hal_config->ext_vref_mv;
        case CYHAL_ADC_REF_VDDA_DIV_2:
            return cyhal_syspm_get_supply_voltage(CYHAL_VOLTAGE_SUPPLY_VDDA) / 2;
        default:
            CY_ASSERT(CYHAL_ADC_REF_VDDA == hal_config->vref);
            return cyhal_syspm_get_supply_voltage(CYHAL_VOLTAGE_SUPPLY_VDDA);
    }
}

#if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
static cy_rslt_t _cyhal_adc_convert_resolution(uint8_t hal_resolution, cy_en_sar_sample_ctrl_sub_resolution_t *pdl_resolution)
{
    switch(hal_resolution)
    {
        case 10:
            *pdl_resolution = CY_SAR_SUB_RESOLUTION_10B;
            break;
        case 8:
            *pdl_resolution = CY_SAR_SUB_RESOLUTION_8B;
            break;
        default:
            return CYHAL_ADC_RSLT_BAD_ARGUMENT;
    }

    return CY_RSLT_SUCCESS;
}

static void _cyhal_adc_extract_channel_conf(cyhal_adc_t* adc, cy_stc_sar_channel_config_t* channel_configs)
{
    for(uint8_t i = 0; i < CY_SAR_SEQ_NUM_CHANNELS; ++i)
    {
        channel_configs[i].addr  = (cy_en_sar_chan_config_port_pin_addr_t)_FLD2VAL(SAR_CHAN_CONFIG_PIN_ADDR, adc->base->CHAN_CONFIG[i]);
        channel_configs[i].addr |= (cy_en_sar_chan_config_port_pin_addr_t)_FLD2VAL(SAR_CHAN_CONFIG_PORT_ADDR, adc->base->CHAN_CONFIG[i]);

        channel_configs[i].avgEn         = _FLD2BOOL(SAR_CHAN_CONFIG_AVG_EN, adc->base->CHAN_CONFIG[i]);
        channel_configs[i].sampleTimeSel = (cy_en_sar_channel_sampletime_t)_FLD2VAL(SAR_CHAN_CONFIG_SAMPLE_TIME_SEL, adc->base->CHAN_CONFIG[i]);
        channel_configs[i].differential  = _FLD2BOOL(SAR_CHAN_CONFIG_DIFFERENTIAL_EN, adc->base->CHAN_CONFIG[i]);
        channel_configs[i].resolution    = (cy_en_sar_channel_ctrl_resolution_t)_FLD2VAL(SAR_CHAN_CONFIG_RESOLUTION, adc->base->CHAN_CONFIG[i]);
        // Range and Saturate interrupt masks have an enable bit per channel
        channel_configs[i].rangeIntrEn   = (0u != (Cy_SAR_GetRangeInterruptMask(adc->base) & 1uL << i));
        channel_configs[i].satIntrEn     = (0u != (Cy_SAR_GetSatInterruptMask(adc->base) & 1uL << i));
    }
}

static cy_rslt_t _cyhal_adc_populate_pdl_config(const cyhal_adc_config_t* hal_config, cy_stc_sar_config_t* pdl_config,
                                                cy_stc_sar_channel_config_t* channel_configs /* Array, length CY_SAR_SEQ_NUM_CHANNELS */)
{
    memset(pdl_config, 0, sizeof(cy_stc_sar_config_t));

    cy_rslt_t result = CY_RSLT_SUCCESS;
    pdl_config->vrefSel = _cyhal_adc_convert_vref(hal_config->vref);
    pdl_config->vrefBypCapEn = hal_config->is_bypassed;
    pdl_config->negSel = (hal_config->vneg == CYHAL_ADC_VNEG_VSSA) ? CY_SAR_NEG_SEL_VSSA_KELVIN : CY_SAR_NEG_SEL_VREF;
    pdl_config->negVref = CY_SAR_NEGVREF_HW;
    pdl_config->boostPump = true;
    pdl_config->power = CY_SAR_NORMAL_PWR;
    pdl_config->sarMuxDsEn = false; // This only enables the routing in deepsleep, not the SAR. And we only use the routing with the SAR
    pdl_config->switchDisable = false; // We are using the SARSEQ
    if(hal_config->resolution != _CYHAL_ADC_RESOLUTION)
    {
        result = _cyhal_adc_convert_resolution(hal_config->resolution, &pdl_config->subResolution);
    }
    if(CY_RSLT_SUCCESS == result)
    {
        pdl_config->leftAlign = false;
        pdl_config->singleEndedSigned = true;
        pdl_config->differentialSigned = true;
        pdl_config->avgShift = true;
        result = _cyhal_adc_convert_average_count(hal_config->average_count, &pdl_config->avgCnt);
    }
    if(CY_RSLT_SUCCESS == result)
    {
        pdl_config->trigMode = CY_SAR_TRIGGER_MODE_FW_ONLY;
        pdl_config->eosEn = false;
        // Will be updated after configuration when we populate sample times after adding channels
        pdl_config->sampleTime0 = pdl_config->sampleTime1 = pdl_config->sampleTime2 = pdl_config->sampleTime3 = 10u;
        // Skipping range thresholds because we don't expose the range detect feature.
        // We always need to populate channel configuration structs here because otherwise the PDL will not
        // initialize the default gain value that the channels will need when and if we add them later.
        for(uint8_t i = 0; i < CY_SAR_SEQ_NUM_CHANNELS; ++i)
        {
            pdl_config->channelConfig[i] = &channel_configs[i];
        }
        // Routing will be configured and channels will be enabled as channels are added
        pdl_config->vrefMvValue = _cyhal_adc_get_vref_mv(hal_config);
    }
    return result;
}

#else /* defined(CY_IP_M0S8PASS4A_SAR_INSTANCES) */

static uint32_t _cyhal_adc_convert_average_mode(uint32_t average_mode_flags)
{
    uint32_t result = 0;
    if(0u != (average_mode_flags & CYHAL_ADC_AVG_MODE_ACCUMULATE))
    {
        result |= CY_SAR_AVG_MODE_SEQUENTIAL_ACCUM;
    }
    else if(0u != (average_mode_flags & CYHAL_ADC_AVG_MODE_INTERLEAVED))
    {
        /* INTERLEAVED on its own does not divide the result back down */
        result |= (CY_SAR_AVG_MODE_INTERLEAVED | SAR_SAMPLE_CTRL_AVG_SHIFT_Msk);
    }
    else
    {
        result |= CY_SAR_AVG_MODE_SEQUENTIAL_FIXED;
    }
    return result;
}

/* Populates the PDL config struct with settings from the ADC config struct */
static cy_rslt_t _cyhal_adc_populate_pdl_config(const cyhal_adc_config_t* hal_config, cy_stc_sar_config_t* pdl_config)
{
    memset(pdl_config, 0, sizeof(cy_stc_sar_config_t));
    if(hal_config->resolution != _CYHAL_ADC_RESOLUTION) /* SAR does not support configurable resolution */
    {
        return CYHAL_ADC_RSLT_BAD_ARGUMENT;
    }

    if (((hal_config->average_mode_flags & CYHAL_ADC_AVG_MODE_ACCUMULATE) > 0) &&
        ((hal_config->average_mode_flags & CYHAL_ADC_AVG_MODE_INTERLEAVED) > 0))
    {
        /* Accumulate mode is not compatible with interleaved averaging */
        return CYHAL_ADC_RSLT_BAD_ARGUMENT;
    }

    *pdl_config = _CYHAL_ADC_DEFAULT_PDL_CONFIG;
    uint32_t ctrl = _CYHAL_ADC_DEFAULT_CTRL;
    ctrl |= (uint32_t)_cyhal_adc_convert_vref(hal_config->vref);
    ctrl |= (hal_config->is_bypassed) ? CY_SAR_BYPASS_CAP_ENABLE : CY_SAR_BYPASS_CAP_DISABLE;
    ctrl |= (hal_config->vneg == CYHAL_ADC_VNEG_VSSA) ? CY_SAR_NEG_SEL_VSSA_KELVIN : CY_SAR_NEG_SEL_VREF;

    uint32_t sample_ctrl = _CYHAL_ADC_DEFAULT_SAMPLE;
    cy_en_sar_sample_ctrl_avg_cnt_t pdl_avg;
    cy_rslt_t result = _cyhal_adc_convert_average_count(hal_config->average_count, &pdl_avg);
    if(CY_RSLT_SUCCESS == result)
    {
        sample_ctrl |= (uint32_t)pdl_avg;
        sample_ctrl |= _cyhal_adc_convert_average_mode(hal_config->average_mode_flags);

        pdl_config->ctrl = ctrl;
        pdl_config->sampleCtrl = sample_ctrl;
        pdl_config->vrefMvValue = _cyhal_adc_get_vref_mv(hal_config);
    }
    return result;
}
#endif /* defined(CY_IP_M0S8PASS4A_SAR_INSTANCES) */
static int32_t _cyhal_adc_counts_to_uvolts(cyhal_adc_t* obj, uint8_t channel, int32_t counts)
{
    return Cy_SAR_CountsTo_uVolts(obj->base, channel, counts);
}
#endif /* defined(CY_IP_MXS40EPASS_ESAR_INSTANCES) */

static void _cyhal_adc_start_convert(cyhal_adc_t* obj)
{
    #if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
    /* Continuous vs. single-shot is handled via the trigger configuration */
    Cy_SAR2_Channel_SoftwareTrigger(obj->base, _cyhal_adc_first_enabled(obj));
    #else
    Cy_SAR_StartConvert(obj->base, obj->continuous_scanning ? CY_SAR_START_CONVERT_CONTINUOUS : CY_SAR_START_CONVERT_SINGLE_SHOT);
    #endif
}
static void _cyhal_adc_irq_handler(void)
{
    /* The only enabled event is scan finished */
    cyhal_adc_event_t hal_event = CYHAL_ADC_EOS;

    _cyhal_system_irq_t irqn = _cyhal_irq_get_active();
    uint8_t block = _cyhal_adc_get_block_from_irqn(irqn);
    cyhal_adc_t* obj = _cyhal_adc_config_structs[block];
    #if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
    uint8_t channel_idx = _cyhal_adc_last_enabled(obj);
    Cy_SAR2_Channel_ClearInterrupt(obj->base, channel_idx, CY_SAR2_INT_GRP_DONE);
    #else
    Cy_SAR_ClearInterrupt(obj->base, CY_SAR_INTR_EOS);
    #endif
    obj->conversion_complete = true;
    #if !defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
    if(obj->stop_after_scan)
    {
        Cy_SAR_StopConvert(obj->base);
    }
    #endif

    if(obj->async_scans_remaining > 0)
    {
        uint8_t num_channels = _cyhal_adc_max_configured_channel(obj) + 1;
        /* Can't read millivolts out via DMA */
        if(CYHAL_ASYNC_SW == obj->async_mode || obj->async_transfer_in_uv)
        {
            for(uint8_t i = 0; i < num_channels; ++i)
            {
                int32_t counts = 0;
                #if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
                if (_CYHAL_ADC_VBG_CHANNEL_IDX == i)
                {
                    obj->vbg_last_value = Cy_SAR2_Channel_GetResult(obj->base, _CYHAL_ADC_VBG_CHANNEL_IDX, NULL);
                    continue;
                }
                else
                {
                    counts = Cy_SAR2_Channel_GetResult(obj->base, i, NULL);
                }
                #else
                counts = Cy_SAR_GetResult32(obj->base, i);
                #endif
                *obj->async_buff_next = obj->async_transfer_in_uv ? _cyhal_adc_counts_to_uvolts(obj, i, counts) : counts;
                ++obj->async_buff_next;
            }
            --(obj->async_scans_remaining);
            if(0 == obj->async_scans_remaining)
            {
                obj->async_buff_next = obj->async_buff_orig = NULL;
                hal_event |= CYHAL_ADC_ASYNC_READ_COMPLETE;
            }
            else if(false == obj->continuous_scanning)
            {
                _cyhal_adc_start_convert(obj);
            }
            /* If we're continously scanning, another scan will be kicked off automatically
             * so we don't need to do anything */
        }
        else
        {
            CY_ASSERT(CYHAL_ASYNC_DMA == obj->async_mode);

#if _CYHAL_ADC_DMA_SUPPORTED
            cyhal_dma_cfg_t dma_config =
            {
                .src_addr = (uint32_t)obj->base->CHAN_RESULT,
                .src_increment = 1u,
                .dst_addr = (uint32_t)obj->async_buff_next,
                .dst_increment = 1u,
                .transfer_width = 32u,
                .length = num_channels,
                .burst_size = 0u,
                .action = CYHAL_DMA_TRANSFER_FULL
            };

            // Configure needs to happen after we've manipulated the descriptor config
            cy_rslt_t result = cyhal_dma_configure(&(obj->dma), &dma_config);
            if(CY_RSLT_SUCCESS == result)
            {
                result = cyhal_dma_enable(&(obj->dma));
            }
            if(CY_RSLT_SUCCESS == result)
            {
                result = cyhal_dma_start_transfer(&(obj->dma));
            }
            CY_ASSERT(CY_RSLT_SUCCESS == result);

            /* Don't increment the buffer here - do that when the DMA completes */
            if(false == obj->continuous_scanning)
            {
                _cyhal_adc_start_convert(obj);
            }
#else
            CY_ASSERT(false); // DMA not supported on the current device
#endif //_CYHAL_ADC_DMA_SUPPORTED
        }
    }

    _cyhal_adc_update_intr_mask(obj);

    if(0 != (hal_event & ((cyhal_adc_event_t)obj->user_enabled_events)))
    {
        cyhal_adc_event_callback_t callback = (cyhal_adc_event_callback_t)obj->callback_data.callback;
        if(NULL != callback)
        {
            callback(obj->callback_data.callback_arg, (cyhal_adc_event_t)(hal_event & obj->user_enabled_events));
        }
    }

}

#if _CYHAL_ADC_DMA_SUPPORTED
static void _cyhal_adc_dma_handler(void* arg, cyhal_dma_event_t event)
{
    CY_ASSERT(CYHAL_DMA_TRANSFER_COMPLETE == event);
    CY_UNUSED_PARAMETER(event);
    cyhal_adc_t* obj = (cyhal_adc_t*)arg;
    CY_ASSERT(CYHAL_ASYNC_DMA == obj->async_mode);

    uint8_t num_channels = _cyhal_adc_max_configured_channel(obj) + 1;
    CY_ASSERT(false == obj->async_transfer_in_uv);
    obj->async_buff_next += num_channels;
    --(obj->async_scans_remaining);
    _cyhal_adc_update_intr_mask(obj);

    if(0 == obj->async_scans_remaining)
    {
        // DMA doesn't sign extend when we copy from 16 to 32 bits, so do the sign extension
        // ourselves once all channel scans are complete.
        while(obj->async_buff_orig != obj->async_buff_next)
        {
            // Mask off the upper two bytes because those contain mirrored status bits which
            // are not part of the ADC counts
            int16_t sar_result = (int16_t)(0xFFFF & *(obj->async_buff_orig));
            *(obj->async_buff_orig) = sar_result;
            ++(obj->async_buff_orig);
        }
        obj->async_buff_next = obj->async_buff_orig = NULL;
        if(0 != (CYHAL_ADC_ASYNC_READ_COMPLETE & ((cyhal_adc_event_t)obj->user_enabled_events)))
        {
            cyhal_adc_event_callback_t callback = (cyhal_adc_event_callback_t)obj->callback_data.callback;
            if(NULL != callback)
            {
                callback(obj->callback_data.callback_arg, CYHAL_ADC_ASYNC_READ_COMPLETE);
            }
        }
    }
}
#endif

/*******************************************************************************
*       ADC HAL Functions
*******************************************************************************/

cy_rslt_t _cyhal_adc_config_hw(cyhal_adc_t *obj, const cyhal_adc_configurator_t* cfg, cyhal_gpio_t pin, bool owned_by_configurator)
{
    const uint32_t DESIRED_DIVIDER = 8000000u; // 8 MHz. Required range is 1.7 - 18

    CY_ASSERT(NULL != obj);

    cy_rslt_t result = CY_RSLT_SUCCESS;

    memset(obj, 0, sizeof(cyhal_adc_t));
    obj->clock.reserved = false;
    obj->resource.type = CYHAL_RSC_INVALID;
    obj->async_mode = CYHAL_ASYNC_SW;
    obj->source = CYHAL_TRIGGER_CPUSS_ZERO;
#if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
    obj->resolution = _CYHAL_ADC_RESOLUTION;
    obj->ext_vref = NC;
    obj->bypass_pin = NC;
#endif

    obj->owned_by_configurator = owned_by_configurator;

    if(NULL == cfg->resource && (NC != pin))
    {
        const cyhal_resource_pin_mapping_t* map = _CYHAL_UTILS_TRY_ALLOC(pin, CYHAL_RSC_ADC, cyhal_pin_map_pass_sarmux_pads);

        if (NULL == map)
        {
            result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
        }
        else
        {
            /* No need to reserve - try_alloc did so for us already */
            obj->resource.type = CYHAL_RSC_ADC;
            obj->resource.block_num = map->block_num;
            obj->resource.channel_num = 0; // Force channel to 0, since we don't use channels and the sarmux_pads overload that item
        }
    }
    else if(NULL != cfg->resource)
    {
        obj->resource = *cfg->resource;
    }
    else
    {
        result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
    }

    en_clk_dst_t pclk = (en_clk_dst_t)0;
    if (CY_RSLT_SUCCESS == result)
    {
        obj->base = _cyhal_adc_base[obj->resource.block_num];
        pclk = _cyhal_adc_clock[obj->resource.block_num];
        if (NULL != cfg->clock)
        {
            obj->clock = *cfg->clock;
            obj->dedicated_clock = false;
        }
        else if (CY_RSLT_SUCCESS ==
            (result = _cyhal_utils_allocate_clock(&(obj->clock), &(obj->resource), CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT, true)))
        {
            obj->dedicated_clock = true;
        }
    }

    if (CY_RSLT_SUCCESS == result)
    {
        if (CY_SYSCLK_SUCCESS != _cyhal_utils_peri_pclk_assign_divider(pclk, &(obj->clock)))
            result = CYHAL_ADC_RSLT_FAILED_CLOCK;
    }

    if (CY_RSLT_SUCCESS == result)
    {
        if(obj->dedicated_clock)
        {
            uint32_t source_hz = _cyhal_utils_get_peripheral_clock_frequency(&(obj->resource));
            uint32_t div = source_hz / DESIRED_DIVIDER;
            if (0 == div ||
                (CY_SYSCLK_SUCCESS != _cyhal_utils_peri_pclk_set_divider(pclk, &(obj->clock), div - 1)) ||
                (CY_SYSCLK_SUCCESS != _cyhal_utils_peri_pclk_enable_divider(pclk, &(obj->clock))))
            {
                result = CYHAL_ADC_RSLT_FAILED_CLOCK;
            }
        }
    }

    if (result == CY_RSLT_SUCCESS)
    {
#if defined(CY_IP_MXS40EPASS_ESAR)
        result = (cy_rslt_t)Cy_SAR2_Init(obj->base, cfg->config);
        Cy_SAR2_SetReferenceBufferMode(PASS0_EPASS_MMIO, CY_SAR2_REF_BUF_MODE_ON);
#else
        result = (cy_rslt_t)Cy_SAR_Init(obj->base, cfg->config);
#endif
    }

    if (result == CY_RSLT_SUCCESS)
    {
#if !defined(CY_IP_MXS40EPASS_ESAR)
        Cy_SAR_SetVssaSarSeqCtrl(obj->base, _CYHAL_ADC_SARSEQ_STATE(true));
        Cy_SAR_SetVssaVminusSwitch(obj->base, _CYHAL_ADC_SWITCH_STATE(true));
#endif

        _cyhal_analog_init();

        _cyhal_adc_update_intr_mask(obj);
        _cyhal_adc_config_structs[obj->resource.block_num] = obj;
#if defined(CY_IP_MXS40EPASS_ESAR)
        /* Register every channel to the same handler; only the current last one in the group will fire
         * but this avoids us having to unregister and reregister interrupts every time we enable/disable a channel */
        for(uint8_t i = 0; i < CY_SAR_MAX_NUM_CHANNELS; ++i)
        {
            _cyhal_irq_register(_cyhal_adc_calc_channel_irq(obj->resource.block_num, i),
                                CYHAL_ISR_PRIORITY_DEFAULT, _cyhal_adc_irq_handler);
            _cyhal_irq_enable(_cyhal_adc_calc_channel_irq(obj->resource.block_num, i));
        }

        Cy_SAR2_Enable(obj->base);
#else
        _cyhal_irq_register(_cyhal_adc_irq_n[obj->resource.block_num], CYHAL_ISR_PRIORITY_DEFAULT, _cyhal_adc_irq_handler);
        _cyhal_irq_enable(_cyhal_adc_irq_n[obj->resource.block_num]);
        Cy_SAR_Enable(obj->base);
#endif
    }
    else
    {
        cyhal_adc_free(obj);
    }
    return result;
}

cy_rslt_t cyhal_adc_init_cfg(cyhal_adc_t *adc, cyhal_adc_channel_t** channels, uint8_t* num_channels,
                                const cyhal_adc_configurator_t *cfg)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    if(*num_channels < cfg->num_channels)
    {
        result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
    }

    if(CY_RSLT_SUCCESS == result)
    {
        *num_channels = cfg->num_channels;
        result = _cyhal_adc_config_hw(adc, cfg, NC, true);
    }

    if(CY_RSLT_SUCCESS == result)
    {
        /* config_hw will have initialized the channels in the ADC HW and the configurator will
         * have set up the routing, but we need to initialize the channel structs */
        for(int i = 0; i < *num_channels; ++i)
        {
            cyhal_adc_channel_t* channel = channels[i];
            memset(channel, 0, sizeof(cyhal_adc_channel_t));
            channel->adc = adc;
            channel->channel_idx = i;
            /* Nothing in this flow needs to know what the pins are - and the inputs aren't even
             * necesssarily pins. The configurator takes care of resource reservation and routing for us */
            channel->vplus = NC;
#if !defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
            channel->vminus = NC;
#endif
            /* The configurator takes care of initial solving, but store this so that we behave properly
             * if the user changes any of the configuration at runtime */
            channel->minimum_acquisition_ns = cfg->achieved_acquisition_time[i];
        }
    }
    return result;
}

cy_rslt_t cyhal_adc_init(cyhal_adc_t *obj, cyhal_gpio_t pin, const cyhal_clock_t *clk)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
#if !defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
    /* On EPASS, there are no non-default values that we need to set on the ADC-wide PDL config */
    cy_stc_sar_config_t pdl_config;

#if defined(CY_IP_M0S8PASS4A_INSTANCES)
    cy_stc_sar_channel_config_t chan_configs[CY_SAR_SEQ_NUM_CHANNELS];
    memset(chan_configs, 0, sizeof(chan_configs));
    // No channels have actually been configured yet, so an empty set of config structs is fine here
    result =  _cyhal_adc_populate_pdl_config(&_CYHAL_ADC_DEFAULT_CONFIG, &pdl_config, chan_configs);
#else
    result = _cyhal_adc_populate_pdl_config(&_CYHAL_ADC_DEFAULT_CONFIG, &pdl_config);
#endif
#endif

    if (CY_RSLT_SUCCESS == result)
    {
        cyhal_adc_configurator_t config;
        config.resource = NULL;
#if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
        config.config = &_CYHAL_ADC_DEFAULT_PDL_CONFIG;
#else
        config.config = &pdl_config;
#endif
        config.clock = clk;
        config.num_channels = 0u;

        result = _cyhal_adc_config_hw(obj, &config, pin, false);
    }
#if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
    /* Some of the default configuration options are per-channel in the hardware and therefore
     * need to be stored on the hal object, call into configure() to take care of that */
    if(CY_RSLT_SUCCESS == result)
    {
        result = cyhal_adc_configure(obj, &_CYHAL_ADC_DEFAULT_CONFIG);
    }
    if (CY_RSLT_SUCCESS == result)
    {
        obj->vbg_chan_inited = false;
    }
#endif
    return result;
}

void cyhal_adc_free(cyhal_adc_t *obj)
{
    if (NULL != obj && NULL != obj->base)
    {
#if defined(CY_IP_MXS40EPASS_ESAR)
        for(uint8_t i = 0; i < CY_SAR_MAX_NUM_CHANNELS; ++i)
        {
            _cyhal_irq_free(_cyhal_adc_calc_channel_irq(obj->resource.block_num, i));
        }
#else
        _cyhal_system_irq_t irqn = _cyhal_adc_irq_n[obj->resource.block_num];
        _cyhal_irq_free(irqn);
#endif
        _cyhal_adc_config_structs[obj->resource.block_num] = NULL;

        cy_rslt_t rslt;
        rslt = cyhal_adc_disable_output(obj, CYHAL_ADC_OUTPUT_SCAN_COMPLETE);
        CY_ASSERT(CY_RSLT_SUCCESS == rslt);
        if (CYHAL_TRIGGER_CPUSS_ZERO != obj->source)
        {
            rslt = cyhal_adc_disconnect_digital(obj, obj->source, CYHAL_ADC_INPUT_START_SCAN);
            CY_ASSERT(CY_RSLT_SUCCESS == rslt);
        }
        (void)rslt; // Disable compiler warning in release build

#if !defined(CY_IP_MXS40EPASS_ESAR)
        Cy_SAR_SetVssaSarSeqCtrl(obj->base, _CYHAL_ADC_SARSEQ_STATE(false));
        Cy_SAR_SetVssaVminusSwitch(obj->base, _CYHAL_ADC_SWITCH_STATE(false));

        Cy_SAR_StopConvert(obj->base);
#endif

        if(false == obj->owned_by_configurator)
        {
#if !defined(CY_IP_MXS40EPASS_ESAR)
            Cy_SAR_Disable(obj->base);
#else
            Cy_SAR2_Disable(obj->base);
#endif

            if(obj->dedicated_clock)
            {
                _cyhal_utils_peri_pclk_disable_divider(_cyhal_adc_clock[obj->resource.block_num], &(obj->clock));
                cyhal_clock_free(&obj->clock);
            }

            _cyhal_analog_free();
#if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
            _cyhal_utils_release_if_used(&(obj->ext_vref));
            _cyhal_utils_release_if_used(&(obj->bypass_pin));
#endif
            cyhal_hwmgr_free(&obj->resource);
        }
        obj->base = NULL;
    }
}

#if defined(CY_IP_MXS40EPASS_ESAR)
cy_rslt_t _cyhal_adc_populate_acquisition_timers(cyhal_adc_t* obj)
{
    /* EPASS has dedicated acquisition timer per channel. To avoid
     * having to ifdef the numerous callsiteas, implement this as a no-op */
    CY_UNUSED_PARAMETER(obj);
    return CY_RSLT_SUCCESS;
}

cy_rslt_t _cyhal_adc_apply_channel_configs(cyhal_adc_t* obj, cy_stc_sar2_channel_config_t* channel_configs)
{
    uint32_t clock_frequency_hz = cyhal_clock_get_frequency(&(obj->clock));
    uint32_t clock_period_ns = (clock_frequency_hz > 0u)
        ? (_CYHAL_UTILS_NS_PER_SECOND / clock_frequency_hz)
        : 0u;
    CY_ASSERT(0u != clock_period_ns);

    bool found_enabled = false;
    uint8_t last_enabled = 0u;
    for(size_t i = 0; i < CY_SAR_MAX_NUM_CHANNELS; ++i)
    {
        Cy_SAR2_Channel_DeInit(obj->base, i);
        if (channel_configs[i].channelHwEnable)
        {
            last_enabled = i;
            if(false == found_enabled) /* Set trigger on the start of the group */
            {
                found_enabled = true;
                channel_configs[i].triggerSelection = obj->continuous_scanning ?
                    CY_SAR2_TRIGGER_CONTINUOUS : CY_SAR2_TRIGGER_GENERIC0;
            }

            if(obj->channel_config[i]->avg_enabled)
            {
                /* Value stored is 1 less than the desired count, but decrement is done by Cy_SAR2_Channel_Init */
                channel_configs[i].averageCount = obj->average_count;
                /* postProcessingMode=AVG triggers the repeated acquisition of samples.
                 * The difference between accumulate and average is whether we do a right shift afterwards
                 */
                uint8_t rightShift;
                channel_configs[i].postProcessingMode = CY_SAR2_POST_PROCESSING_MODE_AVG;
                if(obj->average_is_accumulate)
                {
                    rightShift = 0u;
                }
                else
                {
                    for(rightShift = 31u; (0u == (obj->average_count & 1u << rightShift)); --rightShift) { }
                }
                channel_configs[i].rightShift = rightShift;
            }
            else
            {
                channel_configs[i].averageCount = 0u;
                channel_configs[i].postProcessingMode = CY_SAR2_POST_PROCESSING_MODE_NONE;
                channel_configs[i].rightShift = 0u;
            }

            uint16_t sample_clock_cycles =
                (uint16_t)((obj->channel_config[i]->minimum_acquisition_ns + (clock_period_ns - 1)) / clock_period_ns);
            channel_configs[i].sampleTime = sample_clock_cycles;
        }
        channel_configs[i].isGroupEnd = false;
        channel_configs[i].interruptMask = 0u;
    }

    channel_configs[last_enabled].isGroupEnd = true;
    channel_configs[last_enabled].interruptMask = CY_SAR2_INT_GRP_DONE;

    /* We need to do a 2 pass because we don't know what channel is at the end until
     * we've gone past it */
    cy_rslt_t result = CY_RSLT_SUCCESS;
    for(size_t i = 0; i < CY_SAR_MAX_NUM_CHANNELS; ++i)
    {
        cy_rslt_t result2 = Cy_SAR2_Channel_Init(obj->base, i, &channel_configs[i]);
        if(CY_RSLT_SUCCESS == result)
        {
            result = result2;
        }
    }

    if(CY_RSLT_SUCCESS == result)
    {
        /* We only support one trigger output per ADC instance, so by convention we always drive trigger 0 */
        result = Cy_SAR2_SetGenericTriggerOutput(PASS0_EPASS_MMIO, obj->resource.block_num, 0u, last_enabled);
    }
    return result;
}

void _cyhal_adc_channel_update_config(cyhal_adc_channel_t* obj, cy_stc_sar2_channel_config_t *pdl_cfg, const cyhal_adc_channel_config_t *cfg)
{
    /* We're just applying the HAL configuration provided. The PDL config could already have values that
     * aren't derived from cyhal_adc_channel_config_t, especially if we're updating an existing channel,
     * so omit the customary memset to 0 step */
    pdl_cfg->channelHwEnable = cfg->enabled;
    /* There's no hardware field to explicitly enable/disable averaging for a channel, you just set an average count
     * of 1 if you don't want to average a channel. Because the HAL also allows the average count to be globally
     * set to 1 to disable averaging on all channels, we need to separately keep track of whether this particular
     * channel is supposed to be subject to averaging when it is enabled in general. */
    obj->avg_enabled = cfg->enable_averaging;
    /* Here we only update "primary" data sources that aren't derived from anything other than the
     * cyhal_adc_channel_config_t. We don't set anything that can be derived from the channel pdl config
     * combined with the ADC config; that is taken care of in _cyhal_adc_apply_channel_configs */
}

#else
cy_rslt_t _cyhal_adc_populate_acquisition_timers(cyhal_adc_t* obj)
{
    const uint32_t ACQUISITION_CLOCKS_MIN = 2;
    const uint32_t ACQUISITION_CLOCKS_MAX = 1023;

    cy_rslt_t result = CY_RSLT_SUCCESS;

    uint32_t clock_frequency_hz = cyhal_clock_get_frequency(&(obj->clock));
    uint32_t clock_period_ns = (clock_frequency_hz > 0)
        ? (_CYHAL_UTILS_NS_PER_SECOND / clock_frequency_hz)
        : 0;
    uint16_t sample_timer_ns[] = { 0u, 0u, 0u, 0u };
    uint8_t assigned_timer[CY_SAR_SEQ_NUM_CHANNELS];
    if (clock_period_ns == 0)
    {
        result = CYHAL_ADC_RSLT_FAILED_CLOCK;
    }
    if (result == CY_RSLT_SUCCESS)
    {
        for(uint8_t channel = 0; channel < CY_SAR_SEQ_NUM_CHANNELS; ++channel)
        {
            cyhal_adc_channel_t* chan_config = obj->channel_config[channel];
            assigned_timer[channel] = 0u;
            /* If the channel isn't in use, what we select doesn't matter */
            if(NULL != chan_config)
            {
                bool found = false;
                for(uint8_t timer = 0; !found && timer < sizeof(sample_timer_ns) / sizeof(sample_timer_ns[0]); ++timer)
                {
                    if(chan_config->minimum_acquisition_ns == sample_timer_ns[timer])
                    {
                        /* Matched a pre-existing timer; use that */
                        assigned_timer[channel] = timer;
                        found = true;
                    }
                    else if(0 == sample_timer_ns[timer])
                    {
                        /* Found a free timer - allocate and use that */
                        sample_timer_ns[timer] = chan_config->minimum_acquisition_ns;
                        assigned_timer[channel] = timer;
                        found = true;
                    }
                }

                if(false == found)
                {
                    /* Ran out of acquisition timers */
                    result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
                }
            }
        }
    }

    if(CY_RSLT_SUCCESS == result)
    {
        uint16_t sample_timer_clocks[sizeof(sample_timer_ns) / sizeof(sample_timer_ns[0])];
        for(uint8_t i = 0; i < sizeof(sample_timer_clocks) / sizeof(sample_timer_clocks[0]); ++i)
        {
            /* Convert from nanoseconds to clock cycles, rounding up */
            uint32_t clock_cycles = (sample_timer_ns[i] + (clock_period_ns - 1)) / clock_period_ns;
            if(clock_cycles < ACQUISITION_CLOCKS_MIN)
            {
                clock_cycles = ACQUISITION_CLOCKS_MIN;
            }
            else if(clock_cycles > ACQUISITION_CLOCKS_MAX)
            {
                clock_cycles = ACQUISITION_CLOCKS_MAX;
            }
            /* Per the register map, this should be one greater than the actual desired sampling cycle count */
            sample_timer_clocks[i] = clock_cycles + 1;
        }

        obj->base->SAMPLE_TIME01 = (uint32_t) (((uint32_t)sample_timer_clocks[0] << SAR_SAMPLE_TIME01_SAMPLE_TIME0_Pos)
                                 | ((uint32_t)sample_timer_clocks[1] << SAR_SAMPLE_TIME01_SAMPLE_TIME1_Pos));
        obj->base->SAMPLE_TIME23 = (uint32_t) (((uint32_t)sample_timer_clocks[2] << SAR_SAMPLE_TIME23_SAMPLE_TIME2_Pos)
                                 | ((uint32_t)sample_timer_clocks[3] << SAR_SAMPLE_TIME23_SAMPLE_TIME3_Pos));

        for(uint8_t i = 0; i < CY_SAR_SEQ_NUM_CHANNELS; ++i)
        {
            obj->base->CHAN_CONFIG[i] &= ~SAR_CHAN_CONFIG_SAMPLE_TIME_SEL_Msk;
            obj->base->CHAN_CONFIG[i] |= (uint32_t)assigned_timer[i] << SAR_CHAN_CONFIG_SAMPLE_TIME_SEL_Pos;
        }
    }

    return result;
}
#endif

cy_rslt_t cyhal_adc_configure(cyhal_adc_t *obj, const cyhal_adc_config_t *config)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    obj->continuous_scanning = config->continuous_scanning;

#if defined(CY_IP_MXS40EPASS_ESAR)
    /* No external bypass or external vref option available */
    if (config->is_bypassed
        || CYHAL_ADC_REF_INTERNAL != config->vref
        || CYHAL_ADC_VNEG_VSSA != config->vneg
        || config->average_count < 1u
        || config->average_count > (UINT8_MAX + 1)) /* 8-bit field stores (desired_count - 1) */
    {
        /* No need to check here that the other vref/bypass related parameters are consistent with these
         * selections, there are already checks further down that do that */
        result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
    }

    /* Even though average count can technically be any value between 1 and 256, when we're operating in "true"
     * average mode (i.e. not accumulate) we're limited to powers of 2 because those are the only division
     * ratios that can be achieved through the "shiftRight" functionality.
     */

     obj->average_is_accumulate = (0u != (config->average_mode_flags & CYHAL_ADC_AVG_MODE_ACCUMULATE));
     if(false == obj->average_is_accumulate)
     {
         bool saw_one = false;
         for(uint8_t i = 0; i < 16u; ++i)
         {
             if(0u != (config->average_count & (1u << i)))
             {
                 if(saw_one) /* Two bits set, not a power of 2 */
                 {
                    result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
                    break;
                 }
                 saw_one = true;
             }
         }
     }
#endif
#if defined(CYHAL_PIN_MAP_DRIVE_MODE_PASS_SAR_EXT_VREF0)
    if(NC != config->ext_vref)
    {
        // If this pin wasn't used in the previous config for either vref or bypass, reserve it
        if((NC == obj->ext_vref) && (config->ext_vref != obj->bypass_pin))
        {
            const cyhal_resource_pin_mapping_t* ext_vref_map =
                _cyhal_utils_get_resource(config->ext_vref, cyhal_pin_map_pass_sar_ext_vref0,
                    sizeof(cyhal_pin_map_pass_sar_ext_vref0)/sizeof(cyhal_pin_map_pass_sar_ext_vref0[0]), &(obj->resource),
                    false);

            if (NULL == ext_vref_map)
            {
                result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
            }
            else
            {
                result = _cyhal_utils_reserve_and_connect(ext_vref_map, CYHAL_PIN_MAP_DRIVE_MODE_PASS_SAR_EXT_VREF0);
            }

            if(CY_RSLT_SUCCESS == result)
            {
                obj->ext_vref = config->ext_vref;
            }
        }
    }
    else
    {
        if(NC != obj->ext_vref) // We used to have an external vref pin - free it
        {
            // If the same pin was used as bypass, mark it freed now too
            if(obj->ext_vref == obj->bypass_pin)
            {
                obj->bypass_pin = NC;
            }
            // It is okay to do this without checking if the pin is still used for bypass,
            // because in that case we will just re-reserve the pin below
            cyhal_gpio_free(obj->ext_vref);
            obj->ext_vref = NC;
        }

        // If external vref exists as a GPIO, it's an error to set vref to external without passing in the pin
        if(CYHAL_ADC_REF_EXTERNAL == config->vref)
        {
            result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
        }
    }

    if(NC != config->bypass_pin)
    {
        if(CY_RSLT_SUCCESS == result)
        {
            // Bypass and ext_vref share the same hard-wired IO connection
            const cyhal_resource_pin_mapping_t* bypass_map =
                _cyhal_utils_get_resource(config->bypass_pin, cyhal_pin_map_pass_sar_ext_vref0,
                    sizeof(cyhal_pin_map_pass_sar_ext_vref0)/sizeof(cyhal_pin_map_pass_sar_ext_vref0[0]), &(obj->resource),
                    false);

            if (NULL == bypass_map)
            {
                result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
            }
            else if(config->bypass_pin != config->ext_vref) // It's valid to use the same pin for both ext_vref and bypass
            {
                result = _cyhal_utils_reserve_and_connect(bypass_map, CYHAL_PIN_MAP_DRIVE_MODE_PASS_SAR_EXT_VREF0);
            }
        }

        if(CY_RSLT_SUCCESS == result)
        {
            obj->bypass_pin = config->bypass_pin;
        }
    }
    else
    {
        // We used to have an external vref pin - free it, unless it's still used for ext_vref
        if((NC != obj->bypass_pin) && (obj->ext_vref != obj->bypass_pin))
        {
            cyhal_gpio_free(obj->bypass_pin);
            obj->bypass_pin = NC;
        }

        // If bypass exists as a GPIO, it's an error to enable bypass without passing in the pin
        if(config->is_bypassed)
        {
            result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
        }
    }
#else
    /* No GPIO pins for VREF - it must be using a dedicated pad */
    if(config->bypass_pin != NC || config->ext_vref != NC)
    {
        result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
    }
#endif

    if(false == ((CYHAL_ADC_REF_EXTERNAL == config->vref) ^ (0u == config->ext_vref_mv)))
    {
        /* Must have exactly one of: ext vref selected, ext vref voltage unspecified */
        result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
    }

#if !defined(CY_IP_MXS40EPASS_ESAR)
    cy_stc_sar_config_t pdl_config;
#if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
    if(CY_RSLT_SUCCESS == result)
    {
        obj->resolution = config->resolution;
        cy_stc_sar_channel_config_t chan_configs[CY_SAR_SEQ_NUM_CHANNELS];
        _cyhal_adc_extract_channel_conf(obj, chan_configs);
        result = _cyhal_adc_populate_pdl_config(config, &pdl_config, chan_configs);
    }
#else
    if(CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_adc_populate_pdl_config(config, &pdl_config);
    }
#endif

    if(CY_RSLT_SUCCESS == result)
    {
        /* Save and restore channel configs */
        pdl_config.chanEn = obj->base->CHAN_EN;

        /* Don't deinit routing or change the channel config - we're going
         * to turn the SAR back on in a minute */
#if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
        pdl_config.routingConfig = NULL;
#else
        pdl_config.configRouting = false;
        /* On M0S8 we already extracted the channel configuration as part
         * of assembling the PDL config struct. On MxS40 we need to do it here */
        for(uint8_t i = 0; i < CY_SAR_SEQ_NUM_CHANNELS; ++i)
        {
            pdl_config.chanConfig[i] = obj->base->CHAN_CONFIG[i];
        }
#endif
        Cy_SAR_Disable(obj->base);
        Cy_SAR_DeInit(obj->base, false);
        result = (cy_rslt_t)Cy_SAR_Init(obj->base, &pdl_config);
        _cyhal_adc_populate_acquisition_timers(obj);
        Cy_SAR_SetInterruptMask(obj->base, CY_SAR_INTR_EOS);
        Cy_SAR_Enable(obj->base);
    }
#else
    if(CY_RSLT_SUCCESS == result)
    {
        /* On EPASS, there is no global configuration to update, but we need to repopulate the channel configuration */
        obj->average_count = config->average_count;
        obj->average_is_accumulate = (0u != (config->average_mode_flags & CYHAL_ADC_AVG_MODE_ACCUMULATE));
        cy_stc_sar2_channel_config_t channel_configs[CY_SAR_MAX_NUM_CHANNELS];

        _cyhal_adc_extract_channel_conf(obj, channel_configs);
        result = _cyhal_adc_apply_channel_configs(obj, channel_configs);
    }
#endif

    if(obj->continuous_scanning)
    {
        obj->conversion_complete = false;
        _cyhal_adc_update_intr_mask(obj);
        _cyhal_adc_start_convert(obj);
    }
    return result;
}

cy_rslt_t cyhal_adc_set_power(cyhal_adc_t *obj, cyhal_power_level_t power)
{
    // The SAR doesn't have selectable power levels in the same way that the opamps do.
    if(CYHAL_POWER_LEVEL_OFF == power)
    {
#if !defined(CY_IP_MXS40EPASS_ESAR)
        Cy_SAR_Disable(obj->base);
#else
        Cy_SAR2_Disable(obj->base);
#endif
    }
    else
    {
#if !defined(CY_IP_MXS40EPASS_ESAR)
        Cy_SAR_Enable(obj->base);
#else
        Cy_SAR2_Enable(obj->base);
#endif
    }
    return CY_RSLT_SUCCESS;
}

static uint16_t _cyhal_adc_get_average_count(cyhal_adc_t* obj, int channel_idx)
{
#if defined(CY_IP_MXS40EPASS_ESAR)
    return _FLD2VAL(PASS_SAR_CH_POST_CTL_AVG_CNT, obj->base->CH[channel_idx].POST_CTL);
#else
    uint32_t average_count = 1;
    /* If averaging is in interleaved mode, it does not impact the sample time */
#if defined(CY_IP_MXS40PASS_SAR_INSTANCES)
    bool is_interleaved = CY_SAR_AVG_MODE_INTERLEAVED == (SAR_SAMPLE_CTRL(obj->base) & SAR_SAMPLE_CTRL_AVG_MODE_Msk);
#else
    bool is_interleaved = false;
#endif

    if(false == is_interleaved)
    {
        average_count = (SAR_SAMPLE_CTRL(obj->base) & SAR_SAMPLE_CTRL_AVG_CNT_Msk) >> SAR_SAMPLE_CTRL_AVG_CNT_Pos;
        average_count = (1uL << (average_count + 1uL));
    }

    return (obj->base->CHAN_CONFIG[channel_idx] & SAR_CHAN_CONFIG_AVG_EN_Msk) ? average_count : 1;
#endif
}

/* Gets acquisition times and conversion clocks for all enabled channels, factoring in averaging */
static void _cyhal_adc_get_sample_times(cyhal_adc_t* obj, uint32_t* min_acquisition_ns, uint32_t* conversion_clock_cycles)
{
    *min_acquisition_ns = *conversion_clock_cycles = 0;
    for(uint8_t i = 0; i < CY_SAR_MAX_NUM_CHANNELS; ++i)
    {
        cyhal_adc_channel_t* chan_config = obj->channel_config[i];
#if defined(CY_IP_MXS40EPASS_ESAR)
        if((NULL != chan_config) && (0u != (obj->base->CH[i].ENABLE)))
#else
        if((NULL != chan_config) && (0u != (obj->base->CHAN_EN & ((uint32_t)1U << i))))
#endif
        {
            uint32_t min_time = chan_config->minimum_acquisition_ns;
            uint8_t clock_cycles = _CYHAL_ADC_CONVERSION_CYCLES;
            uint16_t average_count = _cyhal_adc_get_average_count(obj, i);
            min_time *= average_count;
            clock_cycles *= average_count;

            *min_acquisition_ns += min_time;
            *conversion_clock_cycles += clock_cycles;
        }
    }
}

uint32_t _cyhal_adc_calc_optimal_clock_rate(cyhal_adc_t* obj, uint32_t target_sample_hz)
{
    /* From the architecture TRM */
    const uint32_t ADC_CLOCK_MAX_HZ = 60000000;
    const uint32_t ADC_CLOCK_MIN_HZ = 1000000;

    uint32_t sample_period_ns = _CYHAL_UTILS_NS_PER_SECOND / target_sample_hz;
    uint32_t total_acquisition_ns, conversion_clock_cycles;
    _cyhal_adc_get_sample_times(obj, &total_acquisition_ns, &conversion_clock_cycles);

    uint32_t conversion_budget_ns;
    if(sample_period_ns < total_acquisition_ns)
    {
        // Requested sampling rate is impossible - go as fast as we can.
        conversion_budget_ns = 1;
    }
    else
    {
        conversion_budget_ns = sample_period_ns - total_acquisition_ns;
    }

    uint32_t target_period_ns = conversion_budget_ns / conversion_clock_cycles;
    uint32_t target_clock_hz = _CYHAL_UTILS_NS_PER_SECOND / target_period_ns;
    if(target_clock_hz > ADC_CLOCK_MAX_HZ)
    {
        target_clock_hz = ADC_CLOCK_MAX_HZ;
    }
    else if(target_clock_hz < ADC_CLOCK_MIN_HZ)
    {
        target_clock_hz = ADC_CLOCK_MIN_HZ;
    }

    return target_clock_hz;
}

uint32_t _cyhal_adc_compute_actual_sample_rate(cyhal_adc_t* obj)
{
    /* Assumes that the acquisition timers and clock frequency are already set */
    uint32_t clock_frequency_hz = cyhal_clock_get_frequency(&obj->clock);
    uint32_t clock_period_ns = (clock_frequency_hz > 0)
        ? (_CYHAL_UTILS_NS_PER_SECOND / clock_frequency_hz)
        : 0;
    CY_ASSERT(clock_period_ns > 0);

    uint32_t total_sample_time_ns = 0;
#if defined(CY_IP_MXS40EPASS_ESAR)
    for(uint8_t i = 0; i < CY_SAR_MAX_NUM_CHANNELS; ++i)
    {
        uint32_t sample_count = _FLD2VAL(PASS_SAR_CH_SAMPLE_CTL_SAMPLE_TIME, obj->base->CH[i].SAMPLE_CTL);
        total_sample_time_ns +=  sample_count * clock_period_ns;
    }
#else
    uint16_t sample_timer[] =
    {
        (obj->base->SAMPLE_TIME01 & SAR_SAMPLE_TIME01_SAMPLE_TIME0_Msk) >> SAR_SAMPLE_TIME01_SAMPLE_TIME0_Pos,
        (obj->base->SAMPLE_TIME01 & SAR_SAMPLE_TIME01_SAMPLE_TIME1_Msk) >> SAR_SAMPLE_TIME01_SAMPLE_TIME1_Pos,
        (obj->base->SAMPLE_TIME23 & SAR_SAMPLE_TIME23_SAMPLE_TIME2_Msk) >> SAR_SAMPLE_TIME23_SAMPLE_TIME2_Pos,
        (obj->base->SAMPLE_TIME23 & SAR_SAMPLE_TIME23_SAMPLE_TIME3_Msk) >> SAR_SAMPLE_TIME23_SAMPLE_TIME3_Pos,
    };

    for(uint8_t i = 0; i < CY_SAR_SEQ_NUM_CHANNELS; ++i)
    {
        if(0u == (obj->base->CHAN_EN & ((uint32_t)1u << i)))
        {
            continue;
        }
        uint8_t sample_time_idx =
            (obj->base->CHAN_CONFIG[i] & SAR_CHAN_CONFIG_SAMPLE_TIME_SEL_Msk) >> SAR_CHAN_CONFIG_SAMPLE_TIME_SEL_Pos;
        /* Per the register map, the register value is one more than the actual cycle number. */
        uint32_t sample_cycles = sample_timer[sample_time_idx] - 1;
        uint32_t total_cycles = sample_cycles + _CYHAL_ADC_CONVERSION_CYCLES;
        uint32_t sample_time_ns = total_cycles * clock_period_ns;
        sample_time_ns *= _cyhal_adc_get_average_count(obj, i);
        total_sample_time_ns += sample_time_ns;
    }
#endif
    uint32_t sample_frequency_hz = (total_sample_time_ns > 0)
        ? (_CYHAL_UTILS_NS_PER_SECOND / total_sample_time_ns)
        : 0;
    return sample_frequency_hz;
}

cy_rslt_t cyhal_adc_set_sample_rate(cyhal_adc_t* obj, uint32_t desired_sample_rate_hz, uint32_t* achieved_sample_rate_hz)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    /* If we don't own the clock, the caller needs to adjust it and/or the acquisition times to achive the desired rate */
    if(obj->dedicated_clock)
    {
        uint32_t desired_hz = _cyhal_adc_calc_optimal_clock_rate(obj, desired_sample_rate_hz);
        result = cyhal_clock_set_frequency(&(obj->clock), desired_hz, NULL);
    }

    if(CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_adc_populate_acquisition_timers(obj);
    }

    if(CY_RSLT_SUCCESS == result)
    {
        *achieved_sample_rate_hz = _cyhal_adc_compute_actual_sample_rate(obj);
    }
    else
    {
        *achieved_sample_rate_hz = 0u;
    }
    return result;
}

/*******************************************************************************
*       ADC Channel HAL Functions
*******************************************************************************/

#if !defined(CY_IP_MXS40EPASS_ESAR)
/* Updates the channel with the new config while preserving configuration parameters that
 * cyhal_adc_channel_config_t doesn't impact like pin selection */
void _cyhal_adc_channel_update_config(cyhal_adc_channel_t* obj, const cyhal_adc_channel_config_t* config)
{
    uint32_t existing_config = obj->adc->base->CHAN_CONFIG[obj->channel_idx];
    const uint32_t PRESERVE_MASK = SAR_CHAN_CONFIG_DIFFERENTIAL_EN_Msk
#if defined(CY_IP_M0S8PASS4A_INSTANCES)
                                    | SAR_CHAN_CONFIG_PIN_ADDR_Msk | SAR_CHAN_CONFIG_PORT_ADDR_Msk;
#else
                                    | SAR_CHAN_CONFIG_POS_PIN_ADDR_Msk | SAR_CHAN_CONFIG_POS_PORT_ADDR_Msk
                                    | SAR_CHAN_CONFIG_NEG_PIN_ADDR_Msk | SAR_CHAN_CONFIG_NEG_PORT_ADDR_Msk
                                    | SAR_CHAN_CONFIG_NEG_ADDR_EN_Msk;
#endif
    uint32_t result = existing_config & PRESERVE_MASK;
    result |=
          _BOOL2FLD(SAR_CHAN_CONFIG_AVG_EN, config->enable_averaging)
        | _VAL2FLD(SAR_CHAN_CONFIG_SAMPLE_TIME_SEL, 0u); /* Placeholder, will be updated by populate_acquisition_timers */
#if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
    bool resolution_override = (obj->adc->resolution != _CYHAL_ADC_RESOLUTION);
    result |= _VAL2FLD(SAR_CHAN_CONFIG_RESOLUTION, (resolution_override ? CY_SAR_SUB_RES : CY_SAR_MAX_RES));
#endif

    obj->adc->base->CHAN_CONFIG[obj->channel_idx] = result;
}

void _cyhal_adc_channel_set_pin_config(cyhal_adc_channel_t* obj, cyhal_gpio_t vplus, cyhal_gpio_t vminus)
{
        uint32_t result = 0u;
#if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
        CY_UNUSED_PARAMETER(vminus); // On M0S8, vminus is implied by vplus
        result |= _cyhal_adc_get_pin_addr(vplus);
        result |= _BOOL2FLD(SAR_CHAN_CONFIG_DIFFERENTIAL_EN, NC != vminus);
#else
        result |= _cyhal_adc_get_pin_addr(vplus, true);
        if(vminus == NC)
        {
            /* Single-ended channel */
            result |= (uint32_t)CY_SAR_CHAN_SINGLE_ENDED;
        }
        else
        {
            /* Differential */
            result |= _cyhal_adc_get_pin_addr(vminus, false);
            result |= (uint32_t)CY_SAR_CHAN_DIFFERENTIAL_UNPAIRED;
        }
#endif

    obj->adc->base->CHAN_CONFIG[obj->channel_idx] = result;
}

static void _cyhal_adc_update_chan_offset(cyhal_adc_channel_t* obj)
{
    /* Normally, the PDL sets the offset in the ADC init. But we change the channel config after we initialize
     * the ADC itself, so we need to set the offset appropriately here. Otherwise the _uv functions will not
     * work correctly.
     * The conditions in the PDL are: singleEnded && vrefNegSelect && singleEndedSigned. We always operate
     * in signed mode so we only need to check the first two.
    */
    bool single_ended = Cy_SAR_IsChannelSingleEnded(obj->adc->base, obj->channel_idx);
    uint32_t neg_sel_vref_val = (uint32_t)CY_SAR_NEG_SEL_VREF;
#if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
    // The NEG_SEL values in the M0S8 pdl are not pre-shifted
    neg_sel_vref_val = neg_sel_vref_val << SAR_CTRL_NEG_SEL_Pos;
#endif
    bool neg_sel_vref = (neg_sel_vref_val == (obj->adc->base->CTRL & SAR_CTRL_NEG_SEL_Msk));
    int16_t offset = (single_ended && neg_sel_vref) ? (-1 * ((int16_t) (CY_SAR_WRK_MAX_12BIT / 2))) : 0;

#if defined(CY_IP_MXS40PASS_SAR_INSTANCES) && (CY_IP_MXS40PASS_SAR_INSTANCES < 2)
    Cy_SAR_SetOffset(obj->channel_idx, offset);
#else
    Cy_SAR_SetChannelOffset(obj->adc->base, obj->channel_idx, offset);
#endif
}
#endif

cy_rslt_t cyhal_adc_channel_init_diff(cyhal_adc_channel_t *obj, cyhal_adc_t* adc, cyhal_gpio_t vplus, cyhal_gpio_t vminus, const cyhal_adc_channel_config_t* cfg)
{
    CY_ASSERT(obj != NULL);
    CY_ASSERT(adc != NULL);

    cy_rslt_t result = CY_RSLT_SUCCESS;

    memset(obj, 0, sizeof(cyhal_adc_channel_t));
    obj->vplus = NC;
#if !defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
    obj->vminus = NC;
    const cyhal_resource_pin_mapping_t *vminus_map = NULL;
#endif

    // Check for invalid pin or pin belonging to a different SAR
    const cyhal_resource_pin_mapping_t *vplus_map = _cyhal_utils_get_resource(vplus, cyhal_pin_map_pass_sarmux_pads,
        sizeof(cyhal_pin_map_pass_sarmux_pads)/sizeof(cyhal_pin_map_pass_sarmux_pads[0]), NULL, false);

    if(NULL == vplus_map || adc->resource.block_num != vplus_map->block_num)
    {
        result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
    }

    uint8_t chosen_channel = 0;

    if (CY_RSLT_SUCCESS == result)
    {
        // Find the first available channel
        #if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
        for(chosen_channel = _CYHAL_ADC_VBG_CHANNEL_IDX + 1; chosen_channel < CY_SAR_MAX_NUM_CHANNELS; ++chosen_channel)
        #else
        for(chosen_channel = 0; chosen_channel < CY_SAR_MAX_NUM_CHANNELS; ++chosen_channel)
        #endif /* defined(CY_IP_MXS40EPASS_ESAR_INSTANCES) or other */
        {
            if(NULL == adc->channel_config[chosen_channel])
            {
                break;
            }
        }
        if (chosen_channel >= CY_SAR_MAX_NUM_CHANNELS) // No channels available
            result = CYHAL_ADC_RSLT_NO_CHANNELS;
    }

    if(CY_RSLT_SUCCESS == result)
    {
        // Don't set the ADC until here so that free knows whether we have allocated
        // the channel on the parent ADC instance (and therefore doesn't try to free it if
        // something fails further up)
        obj->adc = adc;
        obj->channel_idx = chosen_channel;
        obj->adc->channel_config[chosen_channel] = obj;
        obj->minimum_acquisition_ns = (cfg->min_acquisition_ns > _CYHAL_ADC_MIN_ACQUISITION_TIME_NS)
                                       ? cfg->min_acquisition_ns : _CYHAL_ADC_MIN_ACQUISITION_TIME_NS;
    }

    if((CY_RSLT_SUCCESS == result) && (CYHAL_ADC_VNEG != vminus))
    {
        #if defined(CY_IP_MXS40EPASS_ESAR)
        /* We don't support differential channels */
        result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
        #else
        vminus_map = _cyhal_utils_get_resource(vminus, cyhal_pin_map_pass_sarmux_pads,
            sizeof(cyhal_pin_map_pass_sarmux_pads)/sizeof(cyhal_pin_map_pass_sarmux_pads[0]), NULL, false);
        if (NULL == vminus_map || adc->resource.block_num != vminus_map->block_num)
        {
            result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
        }
        #if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
        // For PSoC™ 4A devices, vplus must be an even number pin, and vminus the following odd numbered pin
        else if (((vplus & 1) != 0) || ((vplus + 1) != vminus))
        {
            result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
        }
        #endif
        #endif
    }

    if(CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_utils_reserve_and_connect(vplus_map, CYHAL_PIN_MAP_DRIVE_MODE_PASS_SARMUX_PADS);
    }

    if(CY_RSLT_SUCCESS == result)
    {
        obj->vplus = vplus;
#if !defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
        if(CYHAL_ADC_VNEG != vminus)
        {
            result = _cyhal_utils_reserve_and_connect(vminus_map, CYHAL_PIN_MAP_DRIVE_MODE_PASS_SARMUX_PADS);
        }
    }

    if(CY_RSLT_SUCCESS == result)
    {
        obj->vminus = vminus;
#endif
        result = _cyhal_adc_populate_acquisition_timers(obj->adc);
    }

    if(CY_RSLT_SUCCESS == result)
    {
#if defined(CY_IP_MXS40EPASS_ESAR)
        cy_stc_sar2_channel_config_t channel_configs[CY_SAR_MAX_NUM_CHANNELS];
        _cyhal_adc_extract_channel_conf(obj->adc, channel_configs);
        channel_configs[obj->channel_idx] = _CYHAL_ADC_DEFAULT_PDL_CHAN_CONFIG;
        channel_configs[obj->channel_idx].pinAddress =
            (cy_en_sar2_pin_address_t)(CY_SAR2_PIN_ADDRESS_AN0 + vplus_map->channel_num);

        #if defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
        if (false == adc->vbg_chan_inited)
        {
            uint8_t block_idx = adc->resource.block_num;

            _cyhal_adc_vbg_channels[block_idx].adc = adc;
            _cyhal_adc_vbg_channels[block_idx].channel_idx = _CYHAL_ADC_VBG_CHANNEL_IDX;
            _cyhal_adc_vbg_channels[block_idx].adc->channel_config[_CYHAL_ADC_VBG_CHANNEL_IDX] = &_cyhal_adc_vbg_channels[block_idx];
            _cyhal_adc_vbg_channels[block_idx].minimum_acquisition_ns = obj->minimum_acquisition_ns;

            channel_configs[_CYHAL_ADC_VBG_CHANNEL_IDX] = _CYHAL_ADC_DEFAULT_PDL_CHAN_CONFIG;
            channel_configs[_CYHAL_ADC_VBG_CHANNEL_IDX].pinAddress = CY_SAR2_PIN_ADDRESS_VBG;

            _cyhal_adc_channel_update_config(obj, &channel_configs[_CYHAL_ADC_VBG_CHANNEL_IDX], cfg);

            adc->vbg_chan_inited = true;
        }
        #endif /* defined(CY_IP_MXS40EPASS_ESAR_INSTANCES) */

        _cyhal_adc_channel_update_config(obj, &channel_configs[obj->channel_idx], cfg);
        result = _cyhal_adc_apply_channel_configs(obj->adc, channel_configs);
#else
        uint32_t fw_ctrl_plus = _cyhal_adc_get_fw_switch_control(vplus, true);
        uint32_t mux_ctrl_plus = _cyhal_adc_get_mux_switch_control(vplus);

        _CYHAL_ADC_SET_SWITCH(obj->adc->base, fw_ctrl_plus, true);
        Cy_SAR_SetSwitchSarSeqCtrl(obj->adc->base, mux_ctrl_plus, _CYHAL_ADC_SARSEQ_STATE(true));

        if(CYHAL_ADC_VNEG != vminus)
        {
            uint32_t fw_ctrl_minus = _cyhal_adc_get_fw_switch_control(vminus, false);
            uint32_t mux_ctrl_minus = _cyhal_adc_get_mux_switch_control(vminus);

            _CYHAL_ADC_SET_SWITCH(obj->adc->base, fw_ctrl_minus, true);
            Cy_SAR_SetSwitchSarSeqCtrl(obj->adc->base, mux_ctrl_minus, _CYHAL_ADC_SARSEQ_STATE(true));
        }

        _cyhal_adc_channel_set_pin_config(obj, obj->vplus, obj->vminus);
        result = cyhal_adc_channel_configure(obj, cfg);
#endif
    }

    if(CY_RSLT_SUCCESS != result)
    {
        cyhal_adc_channel_free(obj);
    }

    return result;
}

cy_rslt_t cyhal_adc_channel_configure(cyhal_adc_channel_t *obj, const cyhal_adc_channel_config_t *config)
{
    CY_ASSERT(NULL != obj);

    obj->minimum_acquisition_ns = (config->min_acquisition_ns > _CYHAL_ADC_MIN_ACQUISITION_TIME_NS)
                                   ? config->min_acquisition_ns : _CYHAL_ADC_MIN_ACQUISITION_TIME_NS;

#if defined(CY_IP_MXS40EPASS_ESAR)
    cy_stc_sar2_channel_config_t channel_configs[CY_SAR_MAX_NUM_CHANNELS];
    _cyhal_adc_extract_channel_conf(obj->adc, channel_configs);
    _cyhal_adc_channel_update_config(obj, &channel_configs[obj->channel_idx], config);
    return _cyhal_adc_apply_channel_configs(obj->adc, channel_configs);
#else
    _cyhal_adc_channel_update_config(obj, config);
    if(config->enabled)
    {
        obj->adc->base->CHAN_EN |= 1u << obj->channel_idx;
    }
    else
    {
        obj->adc->base->CHAN_EN &= ~(1u << obj->channel_idx);
    }
    _cyhal_adc_update_chan_offset(obj);
    return _cyhal_adc_populate_acquisition_timers(obj->adc);
#endif
}

void cyhal_adc_channel_free(cyhal_adc_channel_t *obj)
{
    if(obj->adc != NULL)
    {
        // Disable the channel, the unconfigure it
        obj->adc->channel_config[obj->channel_idx] = NULL;

#if !defined(CY_IP_MXS40EPASS_ESAR)
        if(false == obj->adc->owned_by_configurator)
        {
            if(NC != obj->vplus)
            {
                uint32_t fw_ctrl_plus = _cyhal_adc_get_fw_switch_control(obj->vplus, true);
                uint32_t mux_ctrl_plus = _cyhal_adc_get_mux_switch_control(obj->vplus);

                _CYHAL_ADC_SET_SWITCH(obj->adc->base, fw_ctrl_plus, false);
                Cy_SAR_SetSwitchSarSeqCtrl(obj->adc->base, mux_ctrl_plus, _CYHAL_ADC_SARSEQ_STATE(false));
            }

            if(NC != obj->vminus)
            {
                uint32_t mux_ctrl_minus = _cyhal_adc_get_mux_switch_control(obj->vminus);
                uint32_t fw_ctrl_minus = _cyhal_adc_get_fw_switch_control(obj->vminus, false);

                _CYHAL_ADC_SET_SWITCH(obj->adc->base, fw_ctrl_minus, false);
                Cy_SAR_SetSwitchSarSeqCtrl(obj->adc->base, mux_ctrl_minus, _CYHAL_ADC_SARSEQ_STATE(false));
            }
        }
        obj->adc->base->CHAN_CONFIG[obj->channel_idx] = 0;
#else
        Cy_SAR2_Channel_DeInit(obj->adc->base, obj->channel_idx);
#endif

        if(false == obj->adc->owned_by_configurator)
        {
            _cyhal_utils_release_if_used(&(obj->vplus));
#if !defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
            _cyhal_utils_release_if_used(&(obj->vminus));
#endif
        }

        #if defined(CY_IP_MXS40EPASS_ESAR)
        if (obj->adc->vbg_chan_inited)
        {
            // If VBG sampling channel is activated, go through all channels and find how many activated left.
            // If no more active user channels left, DeInit VBG channel too.
            uint8_t active_chan_num = 0;
            for(uint8_t chan_idx = 0; chan_idx < CY_SAR_MAX_NUM_CHANNELS; ++chan_idx)
            {
                if(NULL != obj->adc->channel_config[chan_idx])
                {
                    ++active_chan_num;
                    if (active_chan_num > 1)
                    {
                        // If 2 or more channels are active (VBG + at least one user channel), no reason to continue
                        // as we will definitely not going to DeInit VBG channel
                        break;
                    }
                }
            }
            if (1 == active_chan_num)
            {
                // Only VBG channel left to be active, DeIniting it
                Cy_SAR2_Channel_DeInit(obj->adc->base, _CYHAL_ADC_VBG_CHANNEL_IDX);
                obj->adc->vbg_chan_inited = false;
            }
        }
        #endif /* defined(CY_IP_MXS40EPASS_ESAR) */

        obj->adc = NULL;
    }
}

uint16_t cyhal_adc_read_u16(const cyhal_adc_channel_t *obj)
{
    int32_t signed_result = cyhal_adc_read(obj);

#if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
    const uint8_t RESULT_SCALING_FACTOR = UINT16_MAX / ((1 << obj->adc->resolution) - 1); // 12-bit SAR resolution
#else
    const uint8_t RESULT_SCALING_FACTOR = UINT16_MAX / 0xFFF; // constant 12-bit SAR resolution
#endif

#if defined(CY_IP_MXS40EPASS_ESAR)
    uint16_t unsigned_result = (uint16_t)((uint32_t)(signed_result) & 0xFFFF);
#else
    /* Legacy API for BWC. Convert from signed to unsigned by adding 0x800 to
     * convert the lowest signed 12-bit number to 0x0.
     */
    uint16_t unsigned_result = (uint16_t)(signed_result + 0x800);
#endif

    /* The SAR provides a 12-bit result, but this API is defined to fill a full 16-bit range */
    uint16_t scaled_result = unsigned_result * RESULT_SCALING_FACTOR;
    return scaled_result;
}

int32_t cyhal_adc_read(const cyhal_adc_channel_t *obj)
{
    uint32_t old_en_mask = 0u;

#if defined(CY_IP_MXS40PASS_SAR_INSTANCES)
    bool isInterleaved = (CY_SAR_AVG_MODE_INTERLEAVED == (SAR_SAMPLE_CTRL(obj->adc->base) & SAR_SAMPLE_CTRL_AVG_MODE_Msk));
#elif !defined(CY_IP_MXS40EPASS_ESAR)
    bool isInterleaved = false;
#endif
#if defined(CY_IP_MXS40EPASS_ESAR)
    cy_stc_sar2_channel_config_t channel_configs[CY_SAR_MAX_NUM_CHANNELS];
#endif
    if(!obj->adc->continuous_scanning)
    {
        /* Enable the selected channel only, then perform an on-demand conversion.
         * Save the old enabled channel set to restore after we're done */
#if defined(CY_IP_MXS40EPASS_ESAR)
        _cyhal_adc_extract_channel_conf(obj->adc, channel_configs);
        /* We need to do a full update because the first and last channels in the group must be enabled */
        for(uint8_t i = 0; i < CY_SAR_MAX_NUM_CHANNELS; ++i) /* Fortunately, each ADC supports a max of 32 channels */
        {
            old_en_mask |= channel_configs[i].channelHwEnable << i;
            channel_configs[i].channelHwEnable = (obj->channel_idx == i) || (_CYHAL_ADC_VBG_CHANNEL_IDX == i);
        }
        _cyhal_adc_apply_channel_configs(obj->adc, channel_configs);
#else
        bool isChannelAveraging = (obj->adc->base->CHAN_CONFIG[obj->channel_idx] & SAR_CHAN_CONFIG_AVG_EN_Msk);
        bool isChannelInterleaved = (isInterleaved && isChannelAveraging);
        old_en_mask = SAR_CHAN_EN(obj->adc->base);
        Cy_SAR_SetChanMask(obj->adc->base, (uint32_t) (1U << obj->channel_idx));
#endif

        obj->adc->conversion_complete = false;
        #if !defined(CY_IP_MXS40EPASS_ESAR)
        obj->adc->stop_after_scan = isChannelInterleaved;
        #endif
        _cyhal_adc_update_intr_mask(obj->adc);

        // If interleaved averaging and average is enabled for this channel, set for
        // continuous scanning and then stop the scan once we get a result. This is
        // because the ADC hardware has a special case where it will not raise
        // the EOC interrupt until AVG_COUNT scans have occurred when all enabled
        // channels are using interleaved channels. This means that for the first AVG_COUNT - 1
        // scans there will be no interrupt, therefore conversion_complete will never
        // be set true, and therefore the loop below would be stuck waiting forever,
        // never able to trigger a subsequent scan.
#if defined(CY_IP_MXS40EPASS_ESAR)
        Cy_SAR2_Channel_SoftwareTrigger(obj->adc->base, _cyhal_adc_first_enabled(obj->adc));
#else
        Cy_SAR_StartConvert(obj->adc->base, (isChannelInterleaved) ? CY_SAR_START_CONVERT_CONTINUOUS : CY_SAR_START_CONVERT_SINGLE_SHOT);
#endif
    }

    /* Cy_SAR_IsEndConversion relies on and clears the EOS interrupt status bit.
     * We don't know how this read will be used in combination with interrupts,
     * so implement our own interrupt-driven EOS flag
     */
    while(!obj->adc->conversion_complete) { }

#if defined(CY_IP_MXS40EPASS_ESAR)
    /* Cy_SAR2_Channel_GetResult returns 12-bit unsigned value, which represent ADC count value in range from 0V to 3.3V/5V
    *  (depends on VDDA). Casting it to signed 32 bit int as per cyhal_adc_read return value description.  */
    int32_t result = (int32_t)(Cy_SAR2_Channel_GetResult(obj->adc->base, obj->channel_idx, NULL /* We don't need the status bits */));
    obj->adc->vbg_last_value = Cy_SAR2_Channel_GetResult(obj->adc->base, _CYHAL_ADC_VBG_CHANNEL_IDX, NULL /* We don't need the status bits */);
#else
    int32_t result = Cy_SAR_GetResult32(obj->adc->base, obj->channel_idx);
#endif

    if(!obj->adc->continuous_scanning)
    {
#if defined(CY_IP_MXS40EPASS_ESAR)
        for(uint8_t i = 0; i < CY_SAR_MAX_NUM_CHANNELS; ++i)
        {
            channel_configs[i].channelHwEnable = (0u != (old_en_mask & (1u << i)));
        }
        _cyhal_adc_apply_channel_configs(obj->adc, channel_configs);
#else
        Cy_SAR_SetChanMask(obj->adc->base, old_en_mask);
#endif
    }

    return result;
}

int32_t cyhal_adc_read_uv(const cyhal_adc_channel_t *obj)
{
    CY_ASSERT(NULL != obj);

    int32_t counts = cyhal_adc_read(obj);
    return _cyhal_adc_counts_to_uvolts(obj->adc, obj->channel_idx, counts);
}

void _cyhal_adc_start_async_read(cyhal_adc_t* obj, size_t num_scan, int32_t* result_list)
{
    CY_ASSERT(NULL == obj->async_buff_next); /* Transfer already in progress */
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    obj->async_scans_remaining = num_scan;
    obj->async_buff_next = obj->async_buff_orig = result_list;
    _cyhal_adc_update_intr_mask(obj);

    if(false == obj->continuous_scanning)
    {
        _cyhal_adc_start_convert(obj);
    }
    cyhal_system_critical_section_exit(savedIntrStatus);
}

cy_rslt_t cyhal_adc_read_async(cyhal_adc_t* obj, size_t num_scan, int32_t* result_list)
{
    CY_ASSERT(NULL != obj);
    obj->async_transfer_in_uv = false;
    _cyhal_adc_start_async_read(obj, num_scan, result_list);
    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_adc_read_async_uv(cyhal_adc_t* obj, size_t num_scan, int32_t* result_list)
{
    CY_ASSERT(NULL != obj);
    obj->async_transfer_in_uv = true;
    _cyhal_adc_start_async_read(obj, num_scan, result_list);
    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_adc_set_async_mode(cyhal_adc_t *obj, cyhal_async_mode_t mode, uint8_t dma_priority)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL == obj->async_buff_next); /* Can't swap mode while a transfer is running */

    cy_rslt_t result = CY_RSLT_SUCCESS;

    if(mode == CYHAL_ASYNC_DMA)
    {
#if _CYHAL_ADC_DMA_SUPPORTED
        result = cyhal_dma_init(&(obj->dma), CYHAL_DMA_PRIORITY_DEFAULT, CYHAL_DMA_DIRECTION_PERIPH2MEM);
        if(CY_RSLT_SUCCESS == result)
        {
            cyhal_dma_register_callback(&(obj->dma), &_cyhal_adc_dma_handler, obj);
            cyhal_dma_enable_event(&(obj->dma), CYHAL_DMA_TRANSFER_COMPLETE, dma_priority, true);
        }
#else
        CY_UNUSED_PARAMETER(dma_priority);
        result = CYHAL_ADC_RSLT_BAD_ARGUMENT; // DMA not supported
#endif
    }
    else
    {
#if _CYHAL_ADC_DMA_SUPPORTED
        /* Free the DMA instances if we reserved them but don't need them anymore */
        if(CYHAL_RSC_INVALID != obj->dma.resource.type)
        {
            cyhal_dma_free(&obj->dma);
            obj->dma.resource.type = CYHAL_RSC_INVALID;
        }
#endif
    }

    if(CY_RSLT_SUCCESS == result)
    {
        obj->async_mode = mode;
    }
    return CY_RSLT_SUCCESS;
}

void cyhal_adc_register_callback(cyhal_adc_t *obj, cyhal_adc_event_callback_t callback, void *callback_arg)
{
    CY_ASSERT(NULL != obj);

    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    obj->callback_data.callback = (cy_israddress) callback;
    obj->callback_data.callback_arg = callback_arg;
    cyhal_system_critical_section_exit(savedIntrStatus);
}

void cyhal_adc_enable_event(cyhal_adc_t *obj, cyhal_adc_event_t event, uint8_t intr_priority, bool enable)
{
    if(enable)
    {
        obj->user_enabled_events |= event;
    }
    else
    {
        obj->user_enabled_events &= ~event;
    }

    _cyhal_adc_update_intr_mask(obj);

#if defined(CY_IP_MXS40EPASS_ESAR)
    for(uint8_t i = 0; i < CY_SAR_MAX_NUM_CHANNELS; ++i)
    {
        _cyhal_system_irq_t irqn = _cyhal_adc_calc_channel_irq(obj->resource.block_num, i);
        _cyhal_irq_set_priority(irqn, intr_priority);
    }
#else
    _cyhal_system_irq_t irqn = _cyhal_adc_irq_n[obj->resource.block_num];
    _cyhal_irq_set_priority(irqn, intr_priority);
#endif
}

static cyhal_dest_t _cyhal_adc_calculate_dest(uint8_t block_num)
{
    CY_ASSERT(block_num < _CYHAL_ADC_SAR_INSTANCES);
    return _cyhal_adc_tr_in[block_num];
}

cy_rslt_t cyhal_adc_connect_digital(cyhal_adc_t *obj, cyhal_source_t source, cyhal_adc_input_t input)
{
    if(input == CYHAL_ADC_INPUT_START_SCAN)
    {
#if !defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
        Cy_SAR_SetConvertMode(obj->base, CY_SAR_TRIGGER_MODE_FW_AND_HWEDGE);
#endif
        cyhal_dest_t dest = _cyhal_adc_calculate_dest(obj->resource.block_num);
        return _cyhal_connect_signal(source, dest);
    }

    return CYHAL_ADC_RSLT_BAD_ARGUMENT;
}

cy_rslt_t cyhal_adc_enable_output(cyhal_adc_t *obj, cyhal_adc_output_t output, cyhal_source_t *source)
{
    if(output == CYHAL_ADC_OUTPUT_SCAN_COMPLETE)
    {
#if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
        SAR_SAMPLE_CTRL(obj->base) |= SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_Msk;
#elif !defined(CY_IP_MXS40EPASS_ESAR_INSTANCES) /* Trigger is always enabled for ESAR */
        SAR_SAMPLE_CTRL(obj->base) |= SAR_SAMPLE_CTRL_TRIGGER_OUT_EN_Msk;
#endif
        *source = _cyhal_adc_calculate_source(obj);
        return CY_RSLT_SUCCESS;
    }

    return CYHAL_ADC_RSLT_BAD_ARGUMENT;
}

cy_rslt_t cyhal_adc_disconnect_digital(cyhal_adc_t *obj, cyhal_source_t source,  cyhal_adc_input_t input)
{
    if(input == CYHAL_ADC_INPUT_START_SCAN)
    {
        #if !defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
        /* EPASS is always in hw trigger mode, we can just also force the trigger through SW */
        Cy_SAR_SetConvertMode(obj->base, CY_SAR_TRIGGER_MODE_FW_ONLY);
        #endif
        cyhal_dest_t dest = _cyhal_adc_calculate_dest(obj->resource.block_num);
        return _cyhal_disconnect_signal(source, dest);
    }

    return CYHAL_ADC_RSLT_BAD_ARGUMENT;
}

cy_rslt_t cyhal_adc_disable_output(cyhal_adc_t *obj, cyhal_adc_output_t output)
{
    if(output != CYHAL_ADC_OUTPUT_SCAN_COMPLETE)
    {
        return CYHAL_ADC_RSLT_BAD_ARGUMENT;
    }

#if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
    SAR_SAMPLE_CTRL(obj->base) &= ~SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_Msk;
#elif defined(CY_IP_MXS40EPASS_ESAR_INSTANCES)
    /* Output trigger is always enabled for ESAR */
    CY_UNUSED_PARAMETER(obj);
#else
    SAR_SAMPLE_CTRL(obj->base) &= ~SAR_SAMPLE_CTRL_TRIGGER_OUT_EN_Msk;
#endif

    return CY_RSLT_SUCCESS;
}

#if defined(__cplusplus)
}
#endif

#endif /* (_CYHAL_DRIVER_AVAILABLE_ADC_SAR) */
