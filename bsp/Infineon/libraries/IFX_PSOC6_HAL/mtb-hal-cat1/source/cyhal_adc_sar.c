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
* Copyright 2018-2021 Cypress Semiconductor Corporation (an Infineon company) or
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
 * The CAT1A/CAT2 (PMG/PSoC™ 4/PSoC™ 6) ADC supports the following features:
 * * Resolution: 12 bit
 * * Only @ref CYHAL_POWER_LEVEL_DEFAULT and CYHAL_POWER_LEVEL_OFF are defined. The default power
 *   level will automatically adjust based on smple rate.
 * * Average counts: 2, 4, 8, 16, 32, 64, 128, 256
 * * Up to four unique acquisition times.
 * * DMA-based transfer when using @ref cyhal_adc_read_async. When using @ref cyhal_adc_read_async_uv,
 *   only interrupt-driven software copy is supported.
 *
 * After initializing the ADC or changing the reference or bypass selection, it may be necessary to wait up to
 * 210 us for the reference buffer to settle. See the architecture TRM (Analog Subsystem -> SAR ADC ->
 * Architecture -> SARREF) for device specific guidance.
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
#include "cyhal_irq_psoc.h"
#include "cyhal_interconnect.h"
#include "cyhal_syspm.h"
#include "cyhal_system.h"
#include <string.h>

#if (_CYHAL_DRIVER_AVAILABLE_ADC_SAR)

#if defined(CY_IP_MXS40PASS_SAR_INSTANCES)
#define _CYHAL_ADC_SAR_INSTANCES CY_IP_MXS40PASS_SAR_INSTANCES
#elif defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
#define _CYHAL_ADC_SAR_INSTANCES CY_IP_M0S8PASS4A_SAR_INSTANCES
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

// The PDL for M0S8 PASS doesn't take the register as an argument; it always writes to MUX_SWITCH0
#if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
    #define _CYHAL_ADC_SARSEQ_STATE(state) (state)
    #define _CYHAL_ADC_SWITCH_STATE(state) (state)
    #define _CYHAL_ADC_SET_SWITCH(base, mask, state) Cy_SAR_SetAnalogSwitch((base), (mask), (state))
#else
    #define _CYHAL_ADC_SWITCH_STATE(state) ((state) ? CY_SAR_SWITCH_CLOSE : CY_SAR_SWITCH_OPEN)
    #define _CYHAL_ADC_SARSEQ_STATE(state) ((state) ? CY_SAR_SWITCH_SEQ_CTRL_ENABLE : CY_SAR_SWITCH_SEQ_CTRL_DISABLE)
    #define _CYHAL_ADC_SET_SWITCH(base, mask, state) Cy_SAR_SetAnalogSwitch((base), CY_SAR_MUX_SWITCH0, (mask), _CYHAL_ADC_SWITCH_STATE((state)))
#endif

#if (CY_IP_MXS40PASS_SAR_INSTANCES == 1) && !defined(CY_DEVICE_PSOC6A256K)
    #define _CYHAL_ADC_SINGLE_UNSUFFIXED
#endif

static SAR_Type *const _cyhal_adc_base[] =
{
#if defined(_CYHAL_ADC_SINGLE_UNSUFFIXED)
    SAR,
#else
#if (_CYHAL_ADC_SAR_INSTANCES >= 1)
    SAR0,
#endif
#if (_CYHAL_ADC_SAR_INSTANCES >= 2)
    SAR1,
#endif
#if (_CYHAL_ADC_SAR_INSTANCES >= 3)
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
#elif (CY_IP_MXS40PASS_SAR_INSTANCES == 1)
    PCLK_PASS_CLOCK_SAR0,
#elif (CY_IP_MXS40PASS_SAR_INSTANCES == 2)
    PCLK_PASS_CLOCK_SAR0,
    PCLK_PASS_CLOCK_SAR1,
#elif (CY_IP_M0S8PASS4A_SAR_INSTANCES == 2)
    PCLK_PASS0_CLOCK_SAR,
    PCLK_PASS1_CLOCK_SAR,
#else
    #warning Unhandled SAR instance count
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
#else
    #warning Unhandled SAR instance count
#endif
};

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
#else
    #warning Unhandled SAR instance count
#endif
};

static cyhal_adc_t* _cyhal_adc_config_structs[_CYHAL_ADC_SAR_INSTANCES];

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

static uint8_t _cyhal_adc_get_block_from_irqn(_cyhal_system_irq_t irqn)
{
    switch (irqn)
    {
#if (CY_CPU_CORTEX_M4 || CY_IP_M0S8PASS4A_SAR_INSTANCES) // M0S8 only has one processor, a CM0 variant
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
#endif /* (CY_CPU_CORTEX_M4 || CY_IP_M0S8PASS4A_SAR_INSTANCES) */
    default:
        CY_ASSERT(false); // Should never be called with a non-SAR IRQn
        return 0;
    }
}

#if defined(CY_IP_MXS40PASS_SAR_INSTANCES)
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
    .vneg                = CYHAL_ADC_VNEG_VREF,
    .vref                = CYHAL_ADC_REF_INTERNAL,
    .ext_vref            = NC,
    .ext_vref_mv         = 0u,
    .is_bypassed         = false,
    .bypass_pin          = NC,
};

/*******************************************************************************
*       Internal helper functions
*******************************************************************************/
static void _cyhal_adc_update_intr_mask(const cyhal_adc_t* obj)
{
    bool needs_eos = (obj->async_scans_remaining > 0) /* Async transfer in progress */
                    || (false == obj->conversion_complete) /* ISR needs to flag that a conversion finished */
                    || obj->stop_after_scan /* ISR needs to stop the conversion after the scan finishes */
                    || (0u != (CYHAL_ADC_EOS & obj->user_enabled_events)); /* User requested EOS event */

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
}

static uint8_t _cyhal_adc_max_configured_channel(const cyhal_adc_t* obj)
{
    uint8_t max = 0;
    for(uint8_t i = 0; i < CY_SAR_SEQ_NUM_CHANNELS; ++i)
    {
        if(NULL != obj->channel_config[i])
        {
            max = i;
        }
    }
    return max;
}

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
        channel_configs[i].rangeIntrEn   = (0u != (Cy_SAR_GetRangeInterruptMask(adc->base) & 1u << i));
        channel_configs[i].satIntrEn     = (0u != (Cy_SAR_GetSatInterruptMask(adc->base) & 1u << i));
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
#else
static uint32_t _cyhal_adc_convert_average_mode(uint32_t average_mode_flags)
{
    uint32 result = 0;
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
#endif

static void _cyhal_adc_irq_handler(void)
{
    /* The only enabled event is scan finished */
    cyhal_adc_event_t hal_event = CYHAL_ADC_EOS;

    _cyhal_system_irq_t irqn = _cyhal_irq_get_active();
    uint8_t block = _cyhal_adc_get_block_from_irqn(irqn);
    cyhal_adc_t* obj = _cyhal_adc_config_structs[block];
    Cy_SAR_ClearInterrupt(obj->base, CY_SAR_INTR_EOS);
    obj->conversion_complete = true;
    if(obj->stop_after_scan)
    {
        Cy_SAR_StopConvert(obj->base);
    }

    if(obj->async_scans_remaining > 0)
    {
        uint8_t num_channels = _cyhal_adc_max_configured_channel(obj) + 1;
        /* Can't read millivolts out via DMA */
        if(CYHAL_ASYNC_SW == obj->async_mode || obj->async_transfer_in_uv)
        {
            for(uint8_t i = 0; i < num_channels; ++i)
            {
                int32_t counts = Cy_SAR_GetResult32(obj->base, i);
                *obj->async_buff_next = obj->async_transfer_in_uv ? Cy_SAR_CountsTo_uVolts(obj->base, i, counts) : counts;
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
                Cy_SAR_StartConvert(obj->base, CY_SAR_START_CONVERT_SINGLE_SHOT);
            }
            /* If we're continously scanning, another scan will be kicked off automatically
             * so we don't need to do anything */
        }
        else
        {
            CY_ASSERT(CYHAL_ASYNC_DMA == obj->async_mode);

#if defined(CY_IP_M0S8CPUSSV3_DMAC) || defined(CY_IP_M4CPUSS_DMA) || defined(CY_IP_M4CPUSS_DMAC)
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
                Cy_SAR_StartConvert(obj->base, CY_SAR_START_CONVERT_SINGLE_SHOT);
            }
#else
            CY_ASSERT(false); // DMA not supported on the current device
#endif //defined(CY_IP_M0S8CPUSSV3_DMAC) || defined(CY_IP_M4CPUSS_DMA) || defined(CY_IP_M4CPUSS_DMAC)
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

#if defined(CY_IP_M0S8CPUSSV3_DMAC) || defined(CY_IP_M4CPUSS_DMA) || defined(CY_IP_M4CPUSS_DMAC)
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
        result = (cy_rslt_t)Cy_SAR_Init(obj->base, cfg->config);
    }

    if (result == CY_RSLT_SUCCESS)
    {
        Cy_SAR_SetVssaSarSeqCtrl(obj->base, _CYHAL_ADC_SARSEQ_STATE(true));
        Cy_SAR_SetVssaVminusSwitch(obj->base, _CYHAL_ADC_SWITCH_STATE(true));

        _cyhal_analog_init();

        _cyhal_adc_config_structs[obj->resource.block_num] = obj;
        _cyhal_irq_register(_cyhal_adc_irq_n[obj->resource.block_num], CYHAL_ISR_PRIORITY_DEFAULT, _cyhal_adc_irq_handler);
        _cyhal_irq_enable(_cyhal_adc_irq_n[obj->resource.block_num]);

        _cyhal_adc_update_intr_mask(obj);
        Cy_SAR_Enable(obj->base);
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
            channel->vminus = NC;
            /* The configurator takes care of initial solving, but store this so that we behave properly
             * if the user changes any of the configuration at runtime */
            channel->minimum_acquisition_ns = cfg->achieved_acquisition_time[i];
        }
    }
    return result;
}

cy_rslt_t cyhal_adc_init(cyhal_adc_t *obj, cyhal_gpio_t pin, const cyhal_clock_t *clk)
{
    cy_stc_sar_config_t pdl_config;

#if defined(CY_IP_M0S8PASS4A_INSTANCES)
    cy_stc_sar_channel_config_t chan_configs[CY_SAR_SEQ_NUM_CHANNELS];
    memset(chan_configs, 0, sizeof(chan_configs));
    // No channels have actually been configured yet, so an empty set of config structs is fine here
    cy_rslt_t result =  _cyhal_adc_populate_pdl_config(&_CYHAL_ADC_DEFAULT_CONFIG, &pdl_config, chan_configs);
#else
    cy_rslt_t result = _cyhal_adc_populate_pdl_config(&_CYHAL_ADC_DEFAULT_CONFIG, &pdl_config);
#endif

    if (CY_RSLT_SUCCESS == result)
    {
        cyhal_adc_configurator_t config;
        config.resource = NULL;
        config.config = &pdl_config;
        config.clock = clk;
        config.num_channels = 0u;

        result = _cyhal_adc_config_hw(obj, &config, pin, false);
    }
    return result;
}

void cyhal_adc_free(cyhal_adc_t *obj)
{
    if (NULL != obj && NULL != obj->base)
    {
        _cyhal_system_irq_t irqn = _cyhal_adc_irq_n[obj->resource.block_num];
        _cyhal_irq_free(irqn);
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

        Cy_SAR_SetVssaSarSeqCtrl(obj->base, _CYHAL_ADC_SARSEQ_STATE(false));
        Cy_SAR_SetVssaVminusSwitch(obj->base, _CYHAL_ADC_SWITCH_STATE(false));

        Cy_SAR_StopConvert(obj->base);

        if(false == obj->owned_by_configurator)
        {
            Cy_SAR_Disable(obj->base);

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
                for(uint8_t timer = 0; timer < sizeof(sample_timer_ns) / sizeof(sample_timer_ns[0]); ++timer)
                {
                    if(chan_config->minimum_acquisition_ns == sample_timer_ns[timer])
                    {
                        /* Matched a pre-existing timer; use that */
                        assigned_timer[channel] = timer;
                        found = true;
                        break;
                    }
                    else if(0 == sample_timer_ns[timer])
                    {
                        /* Found a free timer - allocate and use that */
                        sample_timer_ns[timer] = chan_config->minimum_acquisition_ns;
                        assigned_timer[channel] = timer;
                        found = true;
                        break;
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


cy_rslt_t cyhal_adc_configure(cyhal_adc_t *obj, const cyhal_adc_config_t *config)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;

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

    obj->continuous_scanning = config->continuous_scanning;
    if(obj->continuous_scanning)
    {
        obj->conversion_complete = false;
        _cyhal_adc_update_intr_mask(obj);
        Cy_SAR_StartConvert(obj->base, CY_SAR_START_CONVERT_CONTINUOUS);
    }
    return result;
}

cy_rslt_t cyhal_adc_set_power(cyhal_adc_t *obj, cyhal_power_level_t power)
{
    // The SAR doesn't have selectable power levels in the same way that the opamps do.
    if(CYHAL_POWER_LEVEL_OFF == power)
    {
        Cy_SAR_Disable(obj->base);
    }
    else
    {
        Cy_SAR_Enable(obj->base);
    }
    return CY_RSLT_SUCCESS;
}

static uint16_t _cyhal_adc_get_average_count(cyhal_adc_t* obj, int channel_idx)
{
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
}

/* Gets acquisition times and conversion clocks for all enabled channels, factoring in averaging */
static void _cyhal_adc_get_sample_times(cyhal_adc_t* obj, uint32_t* min_acquisition_ns, uint32_t* conversion_clock_cycles)
{
    *min_acquisition_ns = *conversion_clock_cycles = 0;
    for(uint8_t i = 0; i < CY_SAR_SEQ_NUM_CHANNELS; ++i)
    {
        cyhal_adc_channel_t* chan_config = obj->channel_config[i];
        if((NULL != chan_config) && (0u != (obj->base->CHAN_EN & ((uint32_t)1U << i))))
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
    uint16_t sample_timer[] =
    {
        (obj->base->SAMPLE_TIME01 & SAR_SAMPLE_TIME01_SAMPLE_TIME0_Msk) >> SAR_SAMPLE_TIME01_SAMPLE_TIME0_Pos,
        (obj->base->SAMPLE_TIME01 & SAR_SAMPLE_TIME01_SAMPLE_TIME1_Msk) >> SAR_SAMPLE_TIME01_SAMPLE_TIME1_Pos,
        (obj->base->SAMPLE_TIME23 & SAR_SAMPLE_TIME23_SAMPLE_TIME2_Msk) >> SAR_SAMPLE_TIME23_SAMPLE_TIME2_Pos,
        (obj->base->SAMPLE_TIME23 & SAR_SAMPLE_TIME23_SAMPLE_TIME3_Msk) >> SAR_SAMPLE_TIME23_SAMPLE_TIME3_Pos,
    };

    uint32_t total_sample_time_ns = 0;

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

cy_rslt_t cyhal_adc_channel_init_diff(cyhal_adc_channel_t *obj, cyhal_adc_t* adc, cyhal_gpio_t vplus, cyhal_gpio_t vminus, const cyhal_adc_channel_config_t* cfg)
{
    CY_ASSERT(obj != NULL);
    CY_ASSERT(adc != NULL);

    const uint32_t CYHAL_ADC_MIN_ACQUISITION_TIME_NS = 167;

    cy_rslt_t result = CY_RSLT_SUCCESS;

    memset(obj, 0, sizeof(cyhal_adc_channel_t));
    obj->vplus = NC;
    obj->vminus = NC;

    // Check for invalid pin or pin belonging to a different SAR
    const cyhal_resource_pin_mapping_t *vplus_map = _cyhal_utils_get_resource(vplus, cyhal_pin_map_pass_sarmux_pads,
        sizeof(cyhal_pin_map_pass_sarmux_pads)/sizeof(cyhal_pin_map_pass_sarmux_pads[0]), NULL, false);
    const cyhal_resource_pin_mapping_t *vminus_map = NULL;

    if(NULL == vplus_map || adc->resource.block_num != vplus_map->block_num)
    {
        result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
    }

    uint8_t chosen_channel = 0;

    if (CY_RSLT_SUCCESS == result)
    {
        // Find the first available channel
        for(chosen_channel = 0; chosen_channel < CY_SAR_SEQ_NUM_CHANNELS; ++chosen_channel)
        {
            if(NULL == adc->channel_config[chosen_channel])
            {
                break;
            }
        }
        if (chosen_channel >= CY_SAR_SEQ_NUM_CHANNELS) // No channels available
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
        obj->minimum_acquisition_ns = (cfg->min_acquisition_ns > CYHAL_ADC_MIN_ACQUISITION_TIME_NS)
                                       ? cfg->min_acquisition_ns : CYHAL_ADC_MIN_ACQUISITION_TIME_NS;
    }

    if((CY_RSLT_SUCCESS == result) && (CYHAL_ADC_VNEG != vminus))
    {
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
    }

    if(CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_utils_reserve_and_connect(vplus_map, CYHAL_PIN_MAP_DRIVE_MODE_PASS_SARMUX_PADS);
    }

    if(CY_RSLT_SUCCESS == result)
    {
        obj->vplus = vplus;
        if(CYHAL_ADC_VNEG != vminus)
        {
            result = _cyhal_utils_reserve_and_connect(vminus_map, CYHAL_PIN_MAP_DRIVE_MODE_PASS_SARMUX_PADS);
        }
    }

    if(CY_RSLT_SUCCESS == result)
    {
        obj->vminus = vminus;

        result = _cyhal_adc_populate_acquisition_timers(obj->adc);
    }

    if(CY_RSLT_SUCCESS == result)
    {
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
}

void cyhal_adc_channel_free(cyhal_adc_channel_t *obj)
{
    if(obj->adc != NULL)
    {
        // Disable the channel, the unconfigure it
        obj->adc->channel_config[obj->channel_idx] = NULL;

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

        if(false == obj->adc->owned_by_configurator)
        {
            _cyhal_utils_release_if_used(&(obj->vplus));
            _cyhal_utils_release_if_used(&(obj->vminus));
        }

        obj->adc->base->CHAN_CONFIG[obj->channel_idx] = 0;
        obj->adc = NULL;
    }
}

uint16_t cyhal_adc_read_u16(const cyhal_adc_channel_t *obj)
{
#if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
    const uint8_t RESULT_SCALING_FACTOR = UINT16_MAX / ((1 << obj->adc->resolution) - 1); // 12-bit SAR resolution
#else
    const uint8_t RESULT_SCALING_FACTOR = UINT16_MAX / 0xFFF; // constant 12-bit SAR resolution
#endif
    int32_t signed_result = cyhal_adc_read(obj);
    /* Legacy API for BWC. Convert from signed to unsigned by adding 0x800 to
     * convert the lowest signed 12-bit number to 0x0.
     */
    uint16_t unsigned_result = (uint16_t)(signed_result + 0x800);
    /* The SAR provides a 12-bit result, but this API is defined to fill a full 16-bit range */
    uint16_t scaled_result = unsigned_result * RESULT_SCALING_FACTOR;
    return scaled_result;
}

int32_t cyhal_adc_read(const cyhal_adc_channel_t *obj)
{
    uint32_t old_en_mask = 0u;

#if defined(CY_IP_MXS40PASS_SAR_INSTANCES)
    bool isInterleaved = (CY_SAR_AVG_MODE_INTERLEAVED == (SAR_SAMPLE_CTRL(obj->adc->base) & SAR_SAMPLE_CTRL_AVG_MODE_Msk));
#else
    bool isInterleaved = false;
#endif
    bool isChannelAveraging = (obj->adc->base->CHAN_CONFIG[obj->channel_idx] & SAR_CHAN_CONFIG_AVG_EN_Msk);
    if(!obj->adc->continuous_scanning)
    {
        /* Enable the selected channel only, then perform an on-demand conversion.
         * Save the old enabled channel set to restore after we're done */
        bool isChannelInterleaved = (isInterleaved && isChannelAveraging);
        old_en_mask = SAR_CHAN_EN(obj->adc->base);
        Cy_SAR_SetChanMask(obj->adc->base, (uint32_t) (1U << obj->channel_idx));
        obj->adc->conversion_complete = false;
        obj->adc->stop_after_scan = isChannelInterleaved;
        _cyhal_adc_update_intr_mask(obj->adc);

        // If interleaved averaging and average is enabled for this channel, set for
        // continuous scanning and then stop the scan once we get a result. This is
        // because the ADC hardware has a special case where it will not raise
        // the EOC interrupt until AVG_COUNT scans have occurred when all enabled
        // channels are using interleaved channels. This means that for the first AVG_COUNT - 1
        // scans there will be no interrupt, therefore conversion_complete will never
        // be set true, and therefore the loop below would be stuck waiting forever,
        // never able to trigger a subsequent scan.
        Cy_SAR_StartConvert(obj->adc->base, (isChannelInterleaved) ? CY_SAR_START_CONVERT_CONTINUOUS : CY_SAR_START_CONVERT_SINGLE_SHOT);
    }

    /* Cy_SAR_IsEndConversion relies on and clears the EOS interrupt status bit.
     * We don't know how this read will be used in combination with interrupts,
     * so implement our own interrupt-driven EOS flag
     */
    while(!obj->adc->conversion_complete) { }

    int32_t result = Cy_SAR_GetResult32(obj->adc->base, obj->channel_idx);

    if(!obj->adc->continuous_scanning)
    {
        Cy_SAR_SetChanMask(obj->adc->base, old_en_mask);
    }

    return result;
}

int32_t cyhal_adc_read_uv(const cyhal_adc_channel_t *obj)
{
    CY_ASSERT(NULL != obj);

    int32_t counts = cyhal_adc_read(obj);
    return Cy_SAR_CountsTo_uVolts(obj->adc->base, obj->channel_idx, counts);
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
        Cy_SAR_StartConvert(obj->base, CY_SAR_START_CONVERT_SINGLE_SHOT);
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
#if defined(CY_IP_M0S8CPUSSV3_DMAC) || defined(CY_IP_M4CPUSS_DMA) || defined(CY_IP_M4CPUSS_DMAC)
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
#if defined(CY_IP_M0S8CPUSSV3_DMAC) || defined(CY_IP_M4CPUSS_DMA) || defined(CY_IP_M4CPUSS_DMAC)
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

    _cyhal_system_irq_t irqn = _cyhal_adc_irq_n[obj->resource.block_num];
    _cyhal_irq_set_priority(irqn, intr_priority);
}

static cyhal_dest_t _cyhal_adc_calculate_dest(uint8_t block_num)
{
    CY_ASSERT(block_num < _CYHAL_ADC_SAR_INSTANCES);
    return _cyhal_adc_tr_in[block_num];
}

static cyhal_source_t _cyhal_adc_calculate_source(uint8_t block_num)
{
    CY_ASSERT(block_num < _CYHAL_ADC_SAR_INSTANCES);
    return _cyhal_adc_tr_out[block_num];
}

cy_rslt_t cyhal_adc_connect_digital(cyhal_adc_t *obj, cyhal_source_t source, cyhal_adc_input_t input)
{
    if(input == CYHAL_ADC_INPUT_START_SCAN)
    {
        Cy_SAR_SetConvertMode(obj->base, CY_SAR_TRIGGER_MODE_FW_AND_HWEDGE);
        cyhal_dest_t dest = _cyhal_adc_calculate_dest(obj->resource.block_num);
#if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
        // On M0S8 the trigger type is not configurable so the type argument to connect_signal is ignored
        // Therefore, we arbitrarily pick EDGE to satisfy the interface
        return _cyhal_connect_signal(source, dest);
#else
        return _cyhal_connect_signal(source, dest);
#endif
    }

    return CYHAL_ADC_RSLT_BAD_ARGUMENT;
}

cy_rslt_t cyhal_adc_enable_output(cyhal_adc_t *obj, cyhal_adc_output_t output, cyhal_source_t *source)
{
    if(output == CYHAL_ADC_OUTPUT_SCAN_COMPLETE)
    {
#if defined(CY_IP_M0S8PASS4A_SAR_INSTANCES)
        SAR_SAMPLE_CTRL(obj->base) |= SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_Msk;
#else
        SAR_SAMPLE_CTRL(obj->base) |= SAR_SAMPLE_CTRL_TRIGGER_OUT_EN_Msk;
#endif
        *source = _cyhal_adc_calculate_source(obj->resource.block_num);
        return CY_RSLT_SUCCESS;
    }

    return CYHAL_ADC_RSLT_BAD_ARGUMENT;
}

cy_rslt_t cyhal_adc_disconnect_digital(cyhal_adc_t *obj, cyhal_source_t source,  cyhal_adc_input_t input)
{
    if(input == CYHAL_ADC_INPUT_START_SCAN)
    {
        Cy_SAR_SetConvertMode(obj->base, CY_SAR_TRIGGER_MODE_FW_ONLY);
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
#else
    SAR_SAMPLE_CTRL(obj->base) &= ~SAR_SAMPLE_CTRL_TRIGGER_OUT_EN_Msk;
#endif

    return CY_RSLT_SUCCESS;
}

#if defined(__cplusplus)
}
#endif

#endif /* (_CYHAL_DRIVER_AVAILABLE_ADC_SAR) */
