/***************************************************************************//**
* \file cyhal_timer.c
*
* \brief
* Provides a high level interface for interacting with the Infineon Timer/Counter.
* This interface abstracts out the chip specific details. If any chip specific
* functionality is necessary, or performance is critical the low level functions
* can be used directly.
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
#include <string.h>
#if !defined(COMPONENT_CAT5)
#include "cy_device_headers.h"
#endif
#include "cyhal_timer_impl.h"
#include "cyhal_hwmgr.h"
#include "cyhal_gpio.h"
#include "cyhal_interconnect.h"
#include "cyhal_syspm.h"
#include "cyhal_clock.h"
#if defined(COMPONENT_CAT5)
#include "cyhal_irq_impl.h"
#endif

#if (CYHAL_DRIVER_AVAILABLE_TIMER)

#if defined(__cplusplus)
extern "C" {
#endif

static const cy_stc_tcpwm_counter_config_t _cyhal_timer_default_config =
{
    .period = 32768,
    .clockPrescaler = CY_TCPWM_COUNTER_PRESCALER_DIVBY_1,
    .runMode = CY_TCPWM_COUNTER_CONTINUOUS,
    .countDirection = CY_TCPWM_COUNTER_COUNT_UP,
    .compareOrCapture = CY_TCPWM_COUNTER_MODE_CAPTURE,
    .compare0 = 16384,
    .compare1 = 16384,
    .enableCompareSwap = false,
    .interruptSources = CY_TCPWM_INT_NONE,
    .captureInputMode = 0x3U,
    .captureInput = CY_TCPWM_INPUT_0,
    .reloadInputMode = 0x3U,
    .reloadInput = CY_TCPWM_INPUT_0,
    .startInputMode = 0x3U,
    .startInput = CY_TCPWM_INPUT_0,
    .stopInputMode = 0x3U,
    .stopInput = CY_TCPWM_INPUT_0,
    .countInputMode = 0x3U,
    .countInput = CY_TCPWM_INPUT_1,
#if (CY_IP_MXTCPWM_VERSION >= 2U)
    .capture1InputMode = 0x3U,
    .capture1Input = CY_TCPWM_INPUT_0,
    .enableCompare1Swap = false,
    .compare2 = 16384,
    .compare3 = 16384,
    .trigger0Event = CY_TCPWM_CNT_TRIGGER_ON_DISABLED,
    .trigger1Event = CY_TCPWM_CNT_TRIGGER_ON_DISABLED,
#endif
};

/** Convert timer direction from the HAL enum to the corresponding PDL constant
  *
  * @param[in] direction The direction, as a HAL enum value
  * @return The direction, as a PDL constant
  */
static inline uint32_t _cyhal_timer_convert_direction(cyhal_timer_direction_t direction)
{
    switch (direction)
    {
        case CYHAL_TIMER_DIR_UP:
            return CY_TCPWM_COUNTER_COUNT_UP;
        case CYHAL_TIMER_DIR_DOWN:
            return CY_TCPWM_COUNTER_COUNT_DOWN;
        case CYHAL_TIMER_DIR_UP_DOWN:
            return CY_TCPWM_COUNTER_COUNT_UP_DOWN_2;
        default:
            CY_ASSERT(false);
            return CY_TCPWM_COUNTER_COUNT_UP;
    }
}

/*******************************************************************************
*       Timer HAL Functions
*******************************************************************************/

cy_rslt_t _cyhal_timer_init_hw(cyhal_timer_t *obj, const cy_stc_tcpwm_counter_config_t *config, const cyhal_clock_t *clk)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;

    cyhal_resource_inst_t *timer = &obj->tcpwm.resource;
    obj->tcpwm.base = _CYHAL_TCPWM_DATA[_CYHAL_TCPWM_ADJUST_BLOCK_INDEX(timer->block_num)].base;

    en_clk_dst_t pclk = (en_clk_dst_t)(_CYHAL_TCPWM_DATA[_CYHAL_TCPWM_ADJUST_BLOCK_INDEX(timer->block_num)].clock_dst + timer->channel_num);

    if (NULL != clk)
    {
        obj->tcpwm.clock = *clk;
        obj->tcpwm.clock_hz = cyhal_clock_get_frequency(&obj->tcpwm.clock);
        if (CY_SYSCLK_SUCCESS != _cyhal_utils_peri_pclk_assign_divider(pclk, &(obj->tcpwm.clock)))
        {
            result = CYHAL_TIMER_RSLT_ERR_CLOCK_INIT;
        }
    }
    else if (CY_RSLT_SUCCESS == (result = _cyhal_utils_allocate_clock(&(obj->tcpwm.clock), timer, CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT, true)))
    {
        obj->tcpwm.dedicated_clock = true;
        #if defined(COMPONENT_CAT5)
        // CAT5 lacks hardware required to divide from 96MHz to 1MHz
        result = cyhal_timer_set_frequency(obj, CYHAL_TIMER_DEFAULT_FREQ * 3);
        #else
        result = cyhal_timer_set_frequency(obj, CYHAL_TIMER_DEFAULT_FREQ);
        #endif
        if (CY_RSLT_SUCCESS == result)
        {
            if (CY_SYSCLK_SUCCESS != _cyhal_utils_peri_pclk_assign_divider(pclk, &(obj->tcpwm.clock)))
            {
                result = CYHAL_TIMER_RSLT_ERR_CLOCK_INIT;
            }
        }
    }

    if (CY_RSLT_SUCCESS == result)
    {
        result = Cy_TCPWM_Counter_Init(obj->tcpwm.base, _CYHAL_TCPWM_CNT_NUMBER(obj->tcpwm.resource), config);
    }

    if (result == CY_RSLT_SUCCESS)
    {
        _cyhal_tcpwm_init_data(&obj->tcpwm);
        Cy_TCPWM_Counter_Enable(obj->tcpwm.base, _CYHAL_TCPWM_CNT_NUMBER(obj->tcpwm.resource));
    }

    return result;
}

cy_rslt_t cyhal_timer_init(cyhal_timer_t *obj, cyhal_gpio_t pin, const cyhal_clock_t *clk)
{
    CY_ASSERT(NULL != obj);

    // No support currently for pin connections on this device
    if (CYHAL_NC_PIN_VALUE != pin)
        return CYHAL_TIMER_RSLT_ERR_BAD_ARGUMENT;

    memset(obj, 0, sizeof(cyhal_timer_t));
    cy_rslt_t result = CY_RSLT_SUCCESS;

    #if defined(COMPONENT_CAT5)
    // T2Timer requested
    if((uint32_t)clk == (uint32_t)(CYHAL_CLOCK_T2TIMER))
    {
        result = cyhal_hwmgr_allocate(CYHAL_RSC_T2TIMER, &obj->t2timer.resource);
        if (CY_RSLT_SUCCESS == result)
        {
            obj->t2timer.which_timer = obj->t2timer.resource.block_num;
            result = _cyhal_t2timer_init(&obj->t2timer, NULL);
            if(result == CY_RSLT_SUCCESS)
            {
                obj->is_t2timer = true;
            }
        }
    }
    else
    {
        // T2Timer not specifically requested, use either TCPWM or T2Timer
    #endif
        obj->tcpwm.resource.type = CYHAL_RSC_INVALID;
        result = cyhal_hwmgr_allocate(CYHAL_RSC_TCPWM, &obj->tcpwm.resource);
        if (CY_RSLT_SUCCESS == result)
        {
            result = _cyhal_timer_init_hw(obj, &_cyhal_timer_default_config, clk);
    #if defined(COMPONENT_CAT5)
            obj->is_t2timer = false;
        }
        else
        {
            result = cyhal_hwmgr_allocate(CYHAL_RSC_T2TIMER, &obj->t2timer.resource);
            if (CY_RSLT_SUCCESS == result)
            {
                obj->t2timer.which_timer = obj->t2timer.resource.block_num;
                result = _cyhal_t2timer_init(&obj->t2timer, NULL);
                if(result == CY_RSLT_SUCCESS)
                {
                    obj->is_t2timer = true;
                }
            }
        }
    #endif
    }

    if (CY_RSLT_SUCCESS != result)
    {
        cyhal_timer_free(obj);
    }

    return result;
}

cy_rslt_t cyhal_timer_init_cfg(cyhal_timer_t *obj, const cyhal_timer_configurator_t *cfg)
{
    memset(obj, 0, sizeof(cyhal_timer_t));
    obj->tcpwm.resource = *cfg->resource;
    obj->tcpwm.owned_by_configurator = true;
    cy_rslt_t result = _cyhal_timer_init_hw(obj, cfg->config, cfg->clock);
    #if defined(COMPONENT_CAT5)
    // Device configurator doesn't currently support T2Timer
    obj->is_t2timer = false;
    #endif

    if(CY_RSLT_SUCCESS != result)
    {
        cyhal_timer_free(obj);
    }
    return result;
}

cy_rslt_t cyhal_timer_configure(cyhal_timer_t *obj, const cyhal_timer_cfg_t *cfg)
{
    cy_rslt_t rslt;
    #if defined(COMPONENT_CAT5)
    if(obj->is_t2timer)
    {
        if((cfg->direction != CYHAL_TIMER_DIR_DOWN) || (cfg->is_compare != true) || (cfg->value != 0x0))
        {
            // T2Timer can only count down, it has no capture mode, and doesn't support starting values
            return CYHAL_TIMER_RSLT_ERR_UNSUPPORTED;
        }
        cyhal_t2timer_cfg_t t2t_cfg = {
            .mode = T2_ARM_TIMER_MODE_FREERUNNING,
            .counter_mode = T2_ARM_TIMER_COUNTER_MODE_ONESHOT,
            .duration = cfg->compare_value,
        };
        if(cfg->is_continuous)
        {
            t2t_cfg.counter_mode = T2_ARM_TIMER_COUNTER_MODE_WRAPPING;
        }
        rslt = _cyhal_t2timer_configure(&obj->t2timer, &t2t_cfg);
    }
    else
    #endif
    {
        obj->default_value = cfg->value;
        cy_stc_tcpwm_counter_config_t config = _cyhal_timer_default_config;
        config.period = cfg->period;
        config.compare0 = cfg->compare_value;
        config.runMode = cfg->is_continuous ? CY_TCPWM_COUNTER_CONTINUOUS : CY_TCPWM_COUNTER_ONESHOT;
        config.compareOrCapture = cfg->is_compare ? CY_TCPWM_COUNTER_MODE_COMPARE : CY_TCPWM_COUNTER_MODE_CAPTURE;
        config.countDirection = _cyhal_timer_convert_direction(cfg->direction);
        // DeInit will clear the interrupt mask; save it now and restore after we re-nit
        uint32_t old_mask = Cy_TCPWM_GetInterruptMask(obj->tcpwm.base, _CYHAL_TCPWM_CNT_NUMBER(obj->tcpwm.resource));
        Cy_TCPWM_Counter_DeInit(obj->tcpwm.base, _CYHAL_TCPWM_CNT_NUMBER(obj->tcpwm.resource), &config);
        rslt = (cy_rslt_t)Cy_TCPWM_Counter_Init(obj->tcpwm.base, _CYHAL_TCPWM_CNT_NUMBER(obj->tcpwm.resource), &config);
        Cy_TCPWM_Counter_Enable(obj->tcpwm.base, _CYHAL_TCPWM_CNT_NUMBER(obj->tcpwm.resource));
        Cy_TCPWM_SetInterruptMask(obj->tcpwm.base, _CYHAL_TCPWM_CNT_NUMBER(obj->tcpwm.resource), old_mask);

        // This must be called after Cy_TCPWM_Counter_Init
        cyhal_timer_reset(obj);
    }

    return rslt;
}

cy_rslt_t cyhal_timer_set_frequency(cyhal_timer_t *obj, uint32_t hz)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;

    #if defined(COMPONENT_CAT5)
    if(obj->is_t2timer)
    {
        result = _cyhal_t2timer_set_frequency(&obj->t2timer, hz);
    }
    else
    #endif
    {
        if(!obj->tcpwm.dedicated_clock)
        {
            result = CYHAL_TIMER_RSLT_ERR_SHARED_CLOCK;
        }
        #if !defined(COMPONENT_CAT5)
        const cyhal_clock_tolerance_t tolerance = {
            .type = CYHAL_TOLERANCE_PERCENT,
            .value = 2,
        };
        #endif
        if(CY_RSLT_SUCCESS == result)
        {
            #if defined(COMPONENT_CAT5)
            uint32_t current_freq = _cyhal_utils_get_peripheral_clock_frequency(&(obj->tcpwm.resource));
            uint32_t divider = ((current_freq + hz - 1) / hz);
            // _set_divider doesn't use this with CAT5, but to avoid warnings here is what it would use
            en_clk_dst_t clk_dst = (en_clk_dst_t)(_CYHAL_TCPWM_DATA[_CYHAL_TCPWM_ADJUST_BLOCK_INDEX(obj->tcpwm.resource.block_num)].clock_dst + obj->tcpwm.resource.channel_num);
            if(CY_RSLT_SUCCESS == _cyhal_utils_peri_pclk_set_divider(clk_dst, &obj->tcpwm.clock, (divider - 1)))
            #else
            if((CY_RSLT_SUCCESS == cyhal_clock_set_enabled(&obj->tcpwm.clock, false, false)) &&
            (CY_RSLT_SUCCESS == cyhal_clock_set_frequency(&obj->tcpwm.clock, hz, &tolerance)) &&
            (CY_RSLT_SUCCESS == cyhal_clock_set_enabled(&obj->tcpwm.clock, true, false)))
            #endif
            {
                obj->tcpwm.clock_hz = cyhal_clock_get_frequency(&obj->tcpwm.clock);
            }
            else
            {
                result = CYHAL_TIMER_RSLT_ERR_CLOCK_INIT;
            }
        }
    }

    return result;
}

cy_rslt_t cyhal_timer_start(cyhal_timer_t *obj)
{
    CY_ASSERT(NULL != obj);
    cy_rslt_t result = CY_RSLT_SUCCESS;
    #if (CYHAL_DRIVER_AVAILABLE_SYSPM)
    #if defined(COMPONENT_CAT5)
    if (_cyhal_tcpwm_pm_transition_pending() || (obj->is_t2timer && obj->running))
    #else
    if (_cyhal_tcpwm_pm_transition_pending())
    #endif
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }
    #endif

    #if defined(COMPONENT_CAT5)
    if(obj->is_t2timer)
    {
        result = _cyhal_t2timer_start(&obj->t2timer);
        if(result == CY_RSLT_SUCCESS)
        {
            obj->running = true;
        }
    }
    else
    #endif
    {
        Cy_TCPWM_Counter_Enable(obj->tcpwm.base, _CYHAL_TCPWM_CNT_NUMBER(obj->tcpwm.resource));
        #if defined(CY_IP_MXTCPWM) && (CY_IP_MXTCPWM_VERSION >= 2)
        Cy_TCPWM_TriggerStart_Single(obj->tcpwm.base, _CYHAL_TCPWM_CNT_NUMBER(obj->tcpwm.resource));
        #else
        Cy_TCPWM_TriggerStart(obj->tcpwm.base, (1 << _CYHAL_TCPWM_CNT_NUMBER(obj->tcpwm.resource)));
        #endif
    }
    return result;
}

cy_rslt_t cyhal_timer_stop(cyhal_timer_t *obj)
{
    CY_ASSERT(NULL != obj);
    cy_rslt_t result = CY_RSLT_SUCCESS;

    #if defined(COMPONENT_CAT5)
    if(obj->is_t2timer)
    {
        result = _cyhal_t2timer_stop(&obj->t2timer);
        if(result == CY_RSLT_SUCCESS)
        {
            obj->running = false;
        }
    }
    else
    #endif
    {
        Cy_TCPWM_Counter_Disable(obj->tcpwm.base, _CYHAL_TCPWM_CNT_NUMBER(obj->tcpwm.resource));
    }

    return result;
}

cy_rslt_t cyhal_timer_reset(cyhal_timer_t *obj)
{
    CY_ASSERT(NULL != obj);
    cy_rslt_t result = CY_RSLT_SUCCESS;

    #if defined(COMPONENT_CAT5)
    if(obj->is_t2timer)
    {
        result = _cyhal_t2timer_reset(&obj->t2timer);
        if(result == CY_RSLT_SUCCESS)
        {
            obj->running = true;
        }
    }
    else
    #endif
    {
        Cy_TCPWM_Counter_SetCounter(obj->tcpwm.base, _CYHAL_TCPWM_CNT_NUMBER(obj->tcpwm.resource), obj->default_value);
    }

    return result;
}

uint32_t cyhal_timer_read(const cyhal_timer_t *obj)
{
    CY_ASSERT(NULL != obj);
    uint32_t read_value = 0;
    #if defined(COMPONENT_CAT5)
    if(obj->is_t2timer)
    {
        read_value = _cyhal_t2timer_read(&obj->t2timer);
    }
    else
    #endif
    {
        read_value = Cy_TCPWM_Counter_GetCounter(obj->tcpwm.base, _CYHAL_TCPWM_CNT_NUMBER(obj->tcpwm.resource));
    }
    return read_value;
}

static cyhal_tcpwm_input_t _cyhal_timer_translate_input_signal(cyhal_timer_input_t event)
{
    switch(event)
    {
        case CYHAL_TIMER_INPUT_START:
            return CYHAL_TCPWM_INPUT_START;
        case CYHAL_TIMER_INPUT_STOP:
            return CYHAL_TCPWM_INPUT_STOP;
        case CYHAL_TIMER_INPUT_RELOAD:
            return CYHAL_TCPWM_INPUT_RELOAD;
        case CYHAL_TIMER_INPUT_COUNT:
            return CYHAL_TCPWM_INPUT_COUNT;
        case CYHAL_TIMER_INPUT_CAPTURE:
            return CYHAL_TCPWM_INPUT_CAPTURE;
        default:
            CY_ASSERT(false);
            return (cyhal_tcpwm_input_t)0;
    }
}

static cyhal_tcpwm_output_t _cyhal_timer_translate_output_signal(cyhal_timer_output_t signal)
{
    switch(signal)
    {
        case CYHAL_TIMER_OUTPUT_OVERFLOW:
            return CYHAL_TCPWM_OUTPUT_OVERFLOW;
        case CYHAL_TIMER_OUTPUT_UNDERFLOW:
            return CYHAL_TCPWM_OUTPUT_UNDERFLOW;
        case CYHAL_TIMER_OUTPUT_COMPARE_MATCH:
            return CYHAL_TCPWM_OUTPUT_COMPARE_MATCH;
        case CYHAL_TIMER_OUTPUT_TERMINAL_COUNT:
            return CYHAL_TCPWM_OUTPUT_TERMINAL_COUNT;
        default:
            CY_ASSERT(false);
            return (cyhal_tcpwm_output_t)0;
    }
}

cy_rslt_t cyhal_timer_connect_digital2(cyhal_timer_t *obj, cyhal_source_t source, cyhal_timer_input_t signal, cyhal_edge_type_t edge_type)
{
    #if defined(COMPONENT_CAT5)
    if(obj->is_t2timer)
    {
        return CYHAL_TIMER_RSLT_ERR_UNSUPPORTED;
    }
    #endif
    cyhal_tcpwm_input_t tcpwm_signal = _cyhal_timer_translate_input_signal(signal);
    return _cyhal_tcpwm_connect_digital(&(obj->tcpwm), source, tcpwm_signal, edge_type);
}

cy_rslt_t cyhal_timer_connect_digital(cyhal_timer_t *obj, cyhal_source_t source, cyhal_timer_input_t signal)
{
    #if defined(COMPONENT_CAT5)
    if(obj->is_t2timer)
    {
        return CYHAL_TIMER_RSLT_ERR_UNSUPPORTED;
    }
    #endif
#if defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI)
    /* Signal type just tells us edge vs. level, but TCPWM lets you customize which edge you want. So default
     * to rising edge. If the application cares about the edge type, it can use connect_digital2 */
    cyhal_signal_type_t signal_type = _CYHAL_TRIGGER_GET_SOURCE_TYPE(source);
    cyhal_edge_type_t edge_type = (signal_type == CYHAL_SIGNAL_TYPE_LEVEL) ? CYHAL_EDGE_TYPE_LEVEL : CYHAL_EDGE_TYPE_RISING_EDGE;
    return cyhal_timer_connect_digital2(obj, source, signal, edge_type);
#else
    CY_UNUSED_PARAMETER(obj);
    CY_UNUSED_PARAMETER(source);
    CY_UNUSED_PARAMETER(signal);
    return CYHAL_TIMER_RSLT_ERR_BAD_ARGUMENT;
#endif
}

cy_rslt_t cyhal_timer_enable_output(cyhal_timer_t *obj, cyhal_timer_output_t signal, cyhal_source_t *source)
{
    #if defined(COMPONENT_CAT5)
    if(obj->is_t2timer)
    {
        return CYHAL_TIMER_RSLT_ERR_UNSUPPORTED;
    }
    #endif
    cyhal_tcpwm_output_t tcpwm_signal = _cyhal_timer_translate_output_signal(signal);
    return _cyhal_tcpwm_enable_output(&(obj->tcpwm), tcpwm_signal, source);
}

cy_rslt_t cyhal_timer_disconnect_digital(cyhal_timer_t *obj, cyhal_source_t source, cyhal_timer_input_t signal)
{
    #if defined(COMPONENT_CAT5)
    if(obj->is_t2timer)
    {
        return CYHAL_TIMER_RSLT_ERR_UNSUPPORTED;
    }
    #endif
    return _cyhal_tcpwm_disconnect_digital(&(obj->tcpwm), source, _cyhal_timer_translate_input_signal(signal));
}

cy_rslt_t cyhal_timer_disable_output(cyhal_timer_t *obj, cyhal_timer_output_t signal)
{
    #if defined(COMPONENT_CAT5)
    if(obj->is_t2timer)
    {
        return CYHAL_TIMER_RSLT_ERR_UNSUPPORTED;
    }
    #endif
    return _cyhal_tcpwm_disable_output(&(obj->tcpwm), _cyhal_timer_translate_output_signal(signal));
}

#if defined(__cplusplus)
}
#endif

#endif /* CYHAL_DRIVER_AVAILABLE_TIMER */
