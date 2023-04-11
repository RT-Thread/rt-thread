/***************************************************************************/ /**
* \file cyhal_adc_mic.c
*
* \brief
* Provides a high level interface for interacting with the Infineon Analog/Digital
* convert. This interface abstracts out the chip specific details. If any chip
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
 * \addtogroup group_hal_impl_adcmic ADC (Analog Digital Converter)
 * \ingroup group_hal_impl
 * \{
 * \section cyhal_adcmic_impl_features Features
 * The CAT1B ADC supports the following features:
 * * Resolution: 16 bit
 * * Sample rate: Fixed 480 ksps
 * * Minimum acquisition time: Up to 2084 ns
 * * SW-based async transfer only (DMA is not supported)
 * * VREF: @ref CYHAL_ADC_REF_INTERNAL (1.8V) only
 * * Only @ref CYHAL_POWER_LEVEL_DEFAULT and @ref CYHAL_POWER_LEVEL_OFF are defined.
 * * Single ended vneg: @ref CYHAL_ADC_VNEG_VSSA
 *
 * The following functions are not supported:
 * * Differential channels
 * * Continuous scanning
 * * @ref CYHAL_ADC_EOS event (this is only applicable when continuously scanning)
 * * Averaging. In @ref cyhal_adc_config_t, average count must be 1 and average_mode_flags must be 0.
 *   In @ref cyhal_adc_channel_config_t, enable_averaging must be false.
 * * External vref and bypass pins
 * *
 * \} group_hal_impl_adcmic
 */

#include "cyhal_adc.h"
#include "cyhal_clock.h"
#include "cyhal_gpio.h"
#include "cyhal_hwmgr.h"
#include "cyhal_utils.h"
#include "cyhal_irq_impl.h"
#include "cyhal_system.h"
#include <string.h>

#if (_CYHAL_DRIVER_AVAILABLE_ADC_MIC)
#include "cy_adcmic.h"

#if defined(__cplusplus)
extern "C"
{
#endif

#define _CYHAL_ADCMIC_NUM_CHANNELS(obj) (sizeof(obj->channel_config) / sizeof(obj->channel_config[0]))
static const uint8_t  _CYHAL_ADCMIC_RESOLUTION          = 16u;
static const uint32_t _CYHAL_ADCMIC_TARGET_CLOCK_HZ     = 24000000u;
static const uint32_t _CYHAL_ADCMIC_SAMPLE_RATE_HZ      = 480000u; /* Fixed by the HW */
static const uint32_t _CYHAL_ADCMIC_ACQUISITION_TIME_NS = 2084u;   /* 1 / 480 ksps */

static const cy_stc_adcmic_dc_config_t _CYHAL_ADCMIC_DEFAULT_DC_CONFIG =
{
    .range = CY_ADCMIC_DC_RANGE_3_6V,
    .channel = CY_ADCMIC_REFGND, /* Will be updated to match the actual input when a read is triggered */
    .timerPeriod = 10000,
    .timerInput = CY_ADCMIC_TIMER_COUNT_INPUT_CLK_SYS
    /* context will be populated during init */
};

static MXS40ADCMIC_Type *const _cyhal_adcmic_base[] =
{
#if (CY_IP_MXS40ADCMIC_INSTANCES <= 1)
    MXS40ADCMIC0,
#else
    #warning Unhandled ADCMIC instance count
#endif
};

static const en_clk_dst_t _cyhal_adcmic_clock[] =
{
#if (CY_IP_MXS40ADCMIC_INSTANCES <= 1)
    PCLK_ADCMIC_CLK_HF,
#else
    #warning Unhandled ADCMIC instance count
#endif
};

static cyhal_adc_t* _cyhal_adcmic_config_structs[CY_IP_MXS40ADCMIC_INSTANCES];

static const _cyhal_system_irq_t _cyhal_adcmic_irq_n[] =
{
#if (CY_IP_MXS40ADCMIC_INSTANCES <= 1)
    adcmic_interrupt_adcmic_IRQn,
#else
    #warning Unhandled ADCMIC instance count
#endif
};

static uint8_t _cyhal_adcmic_get_block_from_irqn(_cyhal_system_irq_t irqn)
{
    switch (irqn)
    {
    #if (CY_IP_MXS40ADCMIC_INSTANCES <= 1)
        case adcmic_interrupt_adcmic_IRQn:
            return 0;
    #else
        #warning Unhandled ADCMIC instance count
    #endif
        default:
            CY_ASSERT(false); // Should never be called with a non-ADCMIC IRQn
            return 0;
    }
}

/* Find the next enabled channel, starting from current_idx and adjusting the buffer
 * along the way to account for disabled channels */
static void _cyhal_adcmic_find_next_channel(cyhal_adc_t* obj, uint8_t* current_idx, int32_t **buffer)
{
    uint8_t start_idx = *current_idx;
    do
    {
        if(NULL != obj->channel_config[*current_idx])
        {
            if(obj->channel_config[*current_idx]->enabled)
            {
                break;
            }
            else
            {
                ++(*buffer);
            }
            *current_idx = (*current_idx + 1) % _CYHAL_ADCMIC_NUM_CHANNELS(obj);
        }
    } while(*current_idx != start_idx); /* While we haven't wrapped completely around */
}

static uint16_t _cyhal_adc_cnt_to_u16(int16_t raw_cnt)
{
    uint16_t raw_cnt_fixed = (uint16_t)(raw_cnt - CY_ADCMIC_DC_OFFSET);
    // Scaling 0 - CY_ADCMIC_DC_FS_CNT range to 0 - CY_ADCMIC_DC_FS (0xFFFF) range
    // CY_ADCMIC_DC_FS_CNT is multiplied by 10, so division needed
    uint16_t scaled_cnt = (uint16_t)(raw_cnt_fixed * CY_ADCMIC_DC_FS / (CY_ADCMIC_DC_FS_CNT / 10U));
    return scaled_cnt;
}

static void _cyhal_adcmic_irq_handler(void)
{
    /* The only interrupt we enable is DC conversion complete */
    _cyhal_system_irq_t irqn = _cyhal_irq_get_active();
    uint8_t block = _cyhal_adcmic_get_block_from_irqn(irqn);
    cyhal_adc_t* obj = _cyhal_adcmic_config_structs[block];
    Cy_ADCMic_ClearInterrupt(obj->base, CY_ADCMIC_INTR_DC);
    obj->conversion_complete = true;

    if(obj->async_scans_remaining > 0)
    {
        int16_t dc_data = Cy_ADCMic_GetDcResult(obj->base);
        if (obj->async_transfer_in_uv)
        {
            *(obj->async_buff_next) = Cy_ADCMic_CountsTo_uVolts(dc_data, &obj->pdl_context);
        }
        else
        {
            *(obj->async_buff_next) = (int32_t)_cyhal_adc_cnt_to_u16(dc_data);
        }
        obj->async_buff_next++;
        uint8_t old_channel = obj->current_channel_index;
        _cyhal_adcmic_find_next_channel(obj, &(obj->current_channel_index), &(obj->async_buff_next));
        /* we know that at least one channel was enabled, so we don't have to worry about that case,
         * but we do need to check for rollover */
        if(obj->current_channel_index <= old_channel)
        {
            --(obj->async_scans_remaining);
            if(obj->async_scans_remaining == 0)
            {
                /* We're done, notify the user if they asked us to */
                obj->async_buff_next = NULL;
                Cy_ADCMic_DisableInterrupt(obj->base, CY_ADCMIC_INTR_DC);
                Cy_ADCMic_DisableTimer(obj->base);
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
    }
    else
    {
        Cy_ADCMic_DisableTimer(obj->base);
    }
}

static cy_en_adcmic_dc_channel_t _cyhal_adcmic_convert_channel_sel(uint8_t bit_index)
{
    static const cy_en_adcmic_dc_channel_t gpio_channel[] =
    {
        CY_ADCMIC_GPIO0,
        CY_ADCMIC_GPIO1,
        CY_ADCMIC_GPIO2,
        CY_ADCMIC_GPIO3,
        CY_ADCMIC_GPIO4,
        CY_ADCMIC_GPIO5,
        CY_ADCMIC_GPIO6,
        CY_ADCMIC_GPIO7,
    };

    if (bit_index < sizeof(gpio_channel) / sizeof(gpio_channel[0]))
    {
        return gpio_channel[bit_index];
    }
    else
    {
        CY_ASSERT(false); /* We only support GPIO channels and the above defines all of them */
        return CY_ADCMIC_REFGND;
    }
}

/*******************************************************************************
*       ADC HAL Functions
*******************************************************************************/

cy_rslt_t _cyhal_adc_config_hw(cyhal_adc_t *obj, const cyhal_adc_configurator_t* cfg, cyhal_gpio_t pin, bool owned_by_configurator)
{
    CY_ASSERT(NULL != obj);

    cy_rslt_t result = CY_RSLT_SUCCESS;
    memset(obj, 0, sizeof(cyhal_adc_t));
    obj->resource.type = CYHAL_RSC_INVALID;

    obj->owned_by_configurator = owned_by_configurator;

    if(NULL == cfg->resource && NC != pin)
    {
        for (uint32_t i = 0; i < sizeof(cyhal_pin_map_adcmic_gpio_adc_in)/sizeof(cyhal_resource_pin_mapping_t); i++)
        {
            if (pin == cyhal_pin_map_adcmic_gpio_adc_in[i].pin)
            {
                // Force the channel_num to 0 since the ADC_MIC pin_map repurposes that field
                cyhal_resource_inst_t inst = { CYHAL_RSC_ADCMIC, cyhal_pin_map_adcmic_gpio_adc_in[i].block_num, 0 };
                if (CY_RSLT_SUCCESS == cyhal_hwmgr_reserve(&inst))
                {
                    obj->resource = inst;
                    break;
                }
            }
        }

        if (obj->resource.type == CYHAL_RSC_INVALID)
        {
            result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
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
        obj->base = _cyhal_adcmic_base[obj->resource.block_num];
        pclk = _cyhal_adcmic_clock[obj->resource.block_num];
        if (NULL != cfg->clock)
        {
            obj->clock = *cfg->clock;
            obj->dedicated_clock = false;
        }
        else if (CY_RSLT_SUCCESS ==
            (result = _cyhal_utils_allocate_clock(&(obj->clock), &(obj->resource), CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT, true)))
        {
            obj->dedicated_clock = true;
            result = cyhal_clock_set_enabled(&(obj->clock), true /* enabled */, false /* don't wait for lock. Not applicable to dividers */);
        }
    }

    if (CY_RSLT_SUCCESS == result && obj->clock.block != CYHAL_CLOCK_BLOCK_HF)
    {
        if (CY_SYSCLK_SUCCESS != _cyhal_utils_peri_pclk_assign_divider(pclk, &(obj->clock)))
            result = CYHAL_ADC_RSLT_FAILED_CLOCK;
    }

    if (CY_RSLT_SUCCESS == result)
    {
        if(obj->dedicated_clock)
        {
            if(CY_RSLT_SUCCESS != _cyhal_utils_set_clock_frequency(&(obj->clock), _CYHAL_ADCMIC_TARGET_CLOCK_HZ, NULL))
            {
               result = CYHAL_ADC_RSLT_FAILED_CLOCK;
            }
        }
    }

    if (result == CY_RSLT_SUCCESS)
    {
        result = (cy_rslt_t)Cy_ADCMic_Init(obj->base, cfg->config, CY_ADCMIC_DC);
    }

    if (result == CY_RSLT_SUCCESS)
    {
        Cy_ADCMic_Enable(obj->base);
        _cyhal_adcmic_config_structs[obj->resource.block_num] = obj;
        cy_stc_sysint_t irqCfg = { _cyhal_adcmic_irq_n[obj->resource.block_num], CYHAL_ISR_PRIORITY_DEFAULT };
        Cy_SysInt_Init(&irqCfg, _cyhal_adcmic_irq_handler);
        NVIC_EnableIRQ(_cyhal_adcmic_irq_n[obj->resource.block_num]);
        /* No need to explicitly start conversion, that happens automatically when we enable */
    }
    else
    {
        cyhal_adc_free(obj);
    }
    return result;
}

cy_rslt_t cyhal_adc_init(cyhal_adc_t *obj, cyhal_gpio_t pin, const cyhal_clock_t *clk)
{
    cyhal_adc_configurator_t config;
    config.resource = NULL;
    cy_stc_adcmic_dc_config_t dcConfig = _CYHAL_ADCMIC_DEFAULT_DC_CONFIG;
    dcConfig.context = &obj->pdl_context;

    cy_stc_adcmic_config_t pdl_config =
    {
        .micConfig   = NULL,
        .pdmConfig   = NULL,
        .dcConfig    = &dcConfig
    };

    config.config = &pdl_config;
    config.clock = clk;
    config.num_channels = 0u;

    cy_rslt_t result = _cyhal_adc_config_hw(obj, &config, pin, false);
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
            channel->enabled = true;
        }
    }
    return result;
}

void cyhal_adc_free(cyhal_adc_t *obj)
{
    CY_ASSERT(NULL != obj);
    if (CYHAL_RSC_INVALID != obj->resource.type)
    {
        _cyhal_system_irq_t irqn = _cyhal_adcmic_irq_n[obj->resource.block_num];
        _cyhal_irq_free(irqn);
        _cyhal_adcmic_config_structs[obj->resource.block_num] = NULL;

        if(obj->dedicated_clock)
        {
            _cyhal_utils_peri_pclk_disable_divider(_cyhal_adcmic_clock[obj->resource.block_num], &(obj->clock));
            cyhal_clock_free(&obj->clock);
        }

        if (NULL != obj->base)
        {
            Cy_ADCMic_Disable(obj->base);
            obj->base = NULL;
        }

        if(false == obj->owned_by_configurator)
        {
            cyhal_hwmgr_free(&obj->resource);
        }
    }
}

cy_rslt_t cyhal_adc_configure(cyhal_adc_t *obj, const cyhal_adc_config_t *config)
{
    /* The hardware is very limited, so all we can do is check that the config matches what we support */
    CY_UNUSED_PARAMETER(obj);
    if((false != config->continuous_scanning)
        || (_CYHAL_ADCMIC_RESOLUTION != config->resolution)
        || (1u != config->average_count)
        || (0u != config->average_mode_flags)
        || (0u != config->ext_vref_mv)
        || (CYHAL_ADC_VNEG_VSSA != config->vneg)
        || (CYHAL_ADC_REF_INTERNAL != config->vref)
        || (NC != config->ext_vref)
        || (false != config->is_bypassed)
        || (NC != config->bypass_pin))
    {
        return CYHAL_ADC_RSLT_BAD_ARGUMENT;
    }

    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_adc_set_power(cyhal_adc_t *obj, cyhal_power_level_t power)
{
    // The ADC doesn't have selectable power levels in the same way that the opamps do.
    if(CYHAL_POWER_LEVEL_OFF == power)
    {
        Cy_ADCMic_Disable(obj->base);
    }
    else
    {
        Cy_ADCMic_Enable(obj->base);
    }
    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_adc_set_sample_rate(cyhal_adc_t* obj, uint32_t desired_sample_rate_hz, uint32_t* achieved_sample_rate_hz)
{
    /* Only one sample rate supported, so all we can do is validate */
    CY_UNUSED_PARAMETER(obj);
    *achieved_sample_rate_hz = _CYHAL_ADCMIC_SAMPLE_RATE_HZ;
    return (_CYHAL_ADCMIC_SAMPLE_RATE_HZ == desired_sample_rate_hz) ? CY_RSLT_SUCCESS : CYHAL_ADC_RSLT_BAD_ARGUMENT;
}

cy_rslt_t cyhal_adc_channel_init_diff(cyhal_adc_channel_t *obj, cyhal_adc_t* adc, cyhal_gpio_t vplus, cyhal_gpio_t vminus, const cyhal_adc_channel_config_t* cfg)
{
    CY_ASSERT(obj != NULL);
    CY_ASSERT(adc != NULL);

    cy_rslt_t result = CY_RSLT_SUCCESS;

    memset(obj, 0, sizeof(cyhal_adc_channel_t));
    obj->vplus = NC;

    // Check for invalid pin or pin belonging to a different SAR
    const cyhal_resource_pin_mapping_t *vplus_map = _cyhal_utils_get_resource(vplus,
        cyhal_pin_map_adcmic_gpio_adc_in,
        sizeof(cyhal_pin_map_adcmic_gpio_adc_in)/sizeof(cyhal_pin_map_adcmic_gpio_adc_in[0]),
        &(adc->resource), true);

    if(NULL == vplus_map)
    {
        result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
    }

    if(CY_RSLT_SUCCESS == result && CYHAL_ADC_VNEG != vminus)
    {
        result = CYHAL_ADC_RSLT_BAD_ARGUMENT; /* Only single-ended supported on this ADC HW */
    }

    if(CY_RSLT_SUCCESS == result)
    {
        /* For this block, we reuse the drive mode field to store the bit index on the adcmic.
         * Pull off and save that value, but provide the real required drive mode for connecting
         */
        uint8_t bit_index = vplus_map->channel_num;
        obj->channel_sel = _cyhal_adcmic_convert_channel_sel(bit_index);
        result = _cyhal_utils_reserve_and_connect(vplus_map, CYHAL_PIN_MAP_DRIVE_MODE_ADCMIC_GPIO_ADC_IN);
    }

    uint8_t chosen_channel = 0;
    if (CY_RSLT_SUCCESS == result)
    {
        obj->vplus = vplus;
        // Find the first available channel
        for(chosen_channel = 0; chosen_channel < _CYHAL_ADCMIC_NUM_CHANNELS(obj->adc); ++chosen_channel)
        {
            if(NULL == adc->channel_config[chosen_channel])
            {
                break;
            }
        }
        if (chosen_channel >= _CYHAL_ADCMIC_NUM_CHANNELS(obj->adc))
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
    }

    if(CY_RSLT_SUCCESS == result)
    {
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

    cy_rslt_t result = CY_RSLT_SUCCESS;
    if((config->min_acquisition_ns > _CYHAL_ADCMIC_ACQUISITION_TIME_NS) || config->enable_averaging)
    {
        result = CYHAL_ADC_RSLT_BAD_ARGUMENT;
    }
    if(CY_RSLT_SUCCESS == result)
    {
        obj->enabled = config->enabled;
    }

    return result;
}

void cyhal_adc_channel_free(cyhal_adc_channel_t *obj)
{
    CY_ASSERT(NULL != obj);

    // If obj->adc exists, check whether it was configured via configurator (as we are not allowed to free
    //  pins, that were set up via configurator) and if not, release pin. Also, release pin if obj->adc does not exist.
    if(((obj->adc != NULL) && (false == obj->adc->owned_by_configurator)) || (obj->adc == NULL))
    {
        _cyhal_utils_release_if_used(&(obj->vplus));
    }

    if(obj->adc != NULL)
    {
        // Disable the channel. No per-channel configuration was statically set, so nothing to unconfigure
        obj->adc->channel_config[obj->channel_idx] = NULL;
        obj->adc = NULL;
    }
}

static int16_t _cyhal_adc_read_raw(const cyhal_adc_channel_t *obj)
{
    Cy_ADCMic_SelectDcChannel(obj->adc->base, obj->channel_sel);
    /* Cy_ADCMic_IsEndConversion relies on and clears the EOS interrupt status bit.
     * We don't know how this read will be used in combination with interrupts,
     * so implement our own interrupt-driven EOS flag.
     */
    Cy_ADCMic_ClearInterrupt(obj->adc->base, CY_ADCMIC_INTR_DC);
    Cy_ADCMic_EnableInterrupt(obj->adc->base, CY_ADCMIC_INTR_DC);
    obj->adc->conversion_complete = false;
    Cy_ADCMic_EnableTimer(obj->adc->base);
    int retry = 1000;
    while(!obj->adc->conversion_complete && retry > 0)
    {
        cyhal_system_delay_us(1u); /* Conversion should take ~2 us */
        --retry;
    }
    Cy_ADCMic_DisableInterrupt(obj->adc->base, CY_ADCMIC_INTR_DC);
    CY_ASSERT(retry > 0);
    return Cy_ADCMic_GetDcResult(obj->adc->base);
}

uint16_t cyhal_adc_read_u16(const cyhal_adc_channel_t *obj)
{
    CY_ASSERT(NULL != obj);
    return _cyhal_adc_cnt_to_u16(_cyhal_adc_read_raw(obj));
}

int32_t cyhal_adc_read(const cyhal_adc_channel_t *obj)
{
    CY_ASSERT(NULL != obj);
    return (int32_t)(cyhal_adc_read_u16(obj));
}

int32_t cyhal_adc_read_uv(const cyhal_adc_channel_t *obj)
{
    CY_ASSERT(NULL != obj);
    return Cy_ADCMic_CountsTo_uVolts(_cyhal_adc_read_raw(obj), &obj->adc->pdl_context);
}

static void _cyhal_adcmic_start_async_read(cyhal_adc_t* obj, size_t num_scan, int32_t* result_list)
{
    CY_ASSERT(NULL == obj->async_buff_next); /* Transfer already in progress */
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    obj->current_channel_index = 0;
    obj->async_scans_remaining = num_scan;
    obj->async_buff_next = result_list;
    _cyhal_adcmic_find_next_channel(obj, &(obj->current_channel_index), &(obj->async_buff_next));
    if(NULL == obj->channel_config[obj->current_channel_index]
        || (false == obj->channel_config[obj->current_channel_index]->enabled))
    {
        /* No enabled channels found, we're done */
        obj->async_buff_next = NULL;
        obj->async_scans_remaining = 0u;
    }
    else
    {
        Cy_ADCMic_SelectDcChannel(obj->base, obj->channel_config[obj->current_channel_index]->channel_sel);
        Cy_ADCMic_ClearInterrupt(obj->base, CY_ADCMIC_INTR_DC);
        Cy_ADCMic_EnableInterrupt(obj->base, CY_ADCMIC_INTR_DC);
        Cy_ADCMic_EnableTimer(obj->base);
    }
    cyhal_system_critical_section_exit(savedIntrStatus);
}

cy_rslt_t cyhal_adc_read_async(cyhal_adc_t* obj, size_t num_scan, int32_t* result_list)
{
    CY_ASSERT(NULL != obj);
    obj->async_transfer_in_uv = false;
    _cyhal_adcmic_start_async_read(obj, num_scan, result_list);
    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_adc_read_async_uv(cyhal_adc_t* obj, size_t num_scan, int32_t* result_list)
{
    CY_ASSERT(NULL != obj);
    obj->async_transfer_in_uv = true;
    _cyhal_adcmic_start_async_read(obj, num_scan, result_list);
    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_adc_set_async_mode(cyhal_adc_t *obj, cyhal_async_mode_t mode, uint8_t dma_priority)
{
    CY_UNUSED_PARAMETER(obj);
    CY_UNUSED_PARAMETER(dma_priority);
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL == obj->async_buff_next); /* Can't swap mode while a transfer is running */
    if(mode == CYHAL_ASYNC_DMA)
    {
        /* DMA not supported on this HW. CPU intervention is required after every sample anyway,
         * so triggering the DMA would involve more overhead than just CPU copying the 32 bits */
        return CYHAL_ADC_RSLT_BAD_ARGUMENT;
    }
    else
    {
        return CY_RSLT_SUCCESS;
    }
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
    /* Continuous scanning isn't supported (the hardware is converting continuously, but it's not automatically
     * scanning across all enabled channels). We listen for EOC internally at times but that doesn't correspond to
     * the EOS event. So there's no interrupts that we need to enable/disable here. */
    if(enable)
    {
        obj->user_enabled_events |= event;
    }
    else
    {
        obj->user_enabled_events &= ~event;
    }

    _cyhal_system_irq_t irqn = _cyhal_adcmic_irq_n[obj->resource.block_num];
    _cyhal_irq_set_priority(irqn, intr_priority);
}

cy_rslt_t cyhal_adc_connect_digital(cyhal_adc_t *obj, cyhal_source_t source, cyhal_adc_input_t input)
{
    /* No trigger inputs supported on this hardware */
    CY_UNUSED_PARAMETER(obj);
    CY_UNUSED_PARAMETER(source);
    CY_UNUSED_PARAMETER(input);
    return CYHAL_ADC_RSLT_BAD_ARGUMENT;
}

cy_rslt_t cyhal_adc_enable_output(cyhal_adc_t *obj, cyhal_adc_output_t output, cyhal_source_t *source)
{
    /* No trigger outputs supported on this hardware */
    CY_UNUSED_PARAMETER(obj);
    CY_UNUSED_PARAMETER(output);
    CY_UNUSED_PARAMETER(source);
    return CYHAL_ADC_RSLT_BAD_ARGUMENT;
}

cy_rslt_t cyhal_adc_disconnect_digital(cyhal_adc_t *obj, cyhal_source_t source,  cyhal_adc_input_t input)
{
    /* No trigger inputs supported on this hardware */
    CY_UNUSED_PARAMETER(obj);
    CY_UNUSED_PARAMETER(source);
    CY_UNUSED_PARAMETER(input);
    return CYHAL_ADC_RSLT_BAD_ARGUMENT;
}

cy_rslt_t cyhal_adc_disable_output(cyhal_adc_t *obj, cyhal_adc_output_t output)
{
    /* No trigger outputs supported on this hardware */
    CY_UNUSED_PARAMETER(obj);
    CY_UNUSED_PARAMETER(output);
    return CYHAL_ADC_RSLT_BAD_ARGUMENT;
}

#if defined(__cplusplus)
}
#endif

#endif /* _CYHAL_DRIVER_AVAILABLE_ADC_MIC */
