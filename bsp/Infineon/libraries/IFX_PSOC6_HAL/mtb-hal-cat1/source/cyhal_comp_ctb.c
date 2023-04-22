/***************************************************************************/ /**
* \file cyhal_comp_ctb.c
*
* \brief
* Provides an implementation of the comp HAL on top of the CTB opamps.
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
#include "cyhal_comp_ctb.h"
#include "cyhal_gpio.h"
#include "cyhal_analog_common.h"
#include "cyhal_hwmgr.h"
#include "cyhal_irq_impl.h"

#if (_CYHAL_DRIVER_AVAILABLE_COMP_CTB)

#if defined(__cplusplus)
extern "C"
{
#endif

#define _CYHAL_OPAMP_PER_CTB (2u)

static const cy_stc_ctb_opamp_config_t _cyhal_comp_ctb_default_config =
{
    /* oaPower is specified in init */
#if defined(CY_IP_MXS40PASS_CTB_INSTANCES)
    .deepSleep    = CY_CTB_DEEPSLEEP_ENABLE,
    .oaMode       = CY_CTB_MODE_COMP,
    .oaPump       = _CYHAL_CTB_PUMP_ENABLE,
    .oaCompEdge   = CY_CTB_COMP_EDGE_DISABLE,
    .oaCompLevel  = CY_CTB_COMP_DSI_TRIGGER_OUT_LEVEL,
    .oaCompBypass = _CYHAL_COMP_CTB_DEFAULT_BYPASS,
    /* oaCompHyst is specified in init */
    .oaCompIntrEn = true,
#else
    .outputMode = CY_CTB_MODE_COMP,
    .pump       = _CYHAL_CTB_PUMP_ENABLE,
    .compEdge   = CY_CTB_COMP_EDGE_DISABLE,
    .compLevel  = CY_CTB_COMP_TRIGGER_OUT_LEVEL,
    .compBypass = _CYHAL_COMP_CTB_DEFAULT_BYPASS,
    /* compHyst is specified in init */
    .compIntrEn = true,
#endif
};

static bool _cyhal_comp_ctb_arrays_initialized = false;
CY_NOINIT static cyhal_comp_t* _cyhal_comp_ctb_config_structs[_CYHAL_CTB_INSTANCES * _CYHAL_OPAMP_PER_CTB];

static const _cyhal_system_irq_t _cyhal_ctb_irq_n[] =
{
#if (CY_IP_MXS40PASS_CTB_INSTANCES == 1)
    pass_interrupt_ctbs_IRQn,
#elif (CY_IP_M0S8PASS4A_CTB_INSTANCES == 1)
    pass_0_interrupt_ctbs_IRQn,
#elif (_CYHAL_CTB_INSTANCES == 2)
    pass_0_interrupt_ctbs_IRQn,
    pass_1_interrupt_ctbs_IRQn,
#else
    #error Unhandled CTB instance count
#endif
};

/** Get the comp config struct for the opamp that caused the current interrupt */
static cyhal_comp_t* _cyhal_ctb_get_interrupt_source(void)
{
    uint32_t ctb_num = 0;
#if (_CYHAL_CTB_INSTANCES > 1)
    _cyhal_system_irq_t irqn = _cyhal_irq_get_active();
    for (uint32_t i = 0; i < sizeof(_cyhal_ctb_irq_n) / sizeof(_cyhal_system_irq_t); i++)
    {
        if (_cyhal_ctb_irq_n[i] == irqn)
        {
            ctb_num = i;
        }
    }
#endif

    CTBM_Type *ctbm = _cyhal_ctb_base[ctb_num];
    for(uint8_t oa_num = 0; oa_num < _CYHAL_OPAMP_PER_CTB; ++oa_num)
    {
        if(Cy_CTB_GetInterruptStatusMasked(ctbm, _cyhal_opamp_convert_sel(oa_num)))
        {
            cyhal_comp_t* inst = _cyhal_comp_ctb_config_structs[(ctb_num * _CYHAL_OPAMP_PER_CTB) + oa_num];
            if (NULL != inst)
            {
                return inst;
            }
        }
    }

    return NULL;
}

static cyhal_comp_event_t _cyhal_comp_ctb_get_enabled_events(cyhal_comp_t * obj)
{
    uint32_t edge_config_val = (0u == obj->resource.channel_num)
        ? (CTBM_OA_RES0_CTRL(obj->base_ctb) & CTBM_OA_RES0_CTRL_OA0_COMPINT_Msk)
        : (CTBM_OA_RES1_CTRL(obj->base_ctb) & CTBM_OA_RES1_CTRL_OA1_COMPINT_Msk);

    switch(edge_config_val)
    {
        case CY_CTB_COMP_EDGE_DISABLE:
            return (cyhal_comp_event_t)0u;
        case CY_CTB_COMP_EDGE_RISING:
            return CYHAL_COMP_RISING_EDGE;
        case CY_CTB_COMP_EDGE_FALLING:
            return CYHAL_COMP_FALLING_EDGE;
        case CY_CTB_COMP_EDGE_BOTH:
            return (cyhal_comp_event_t)(CYHAL_COMP_RISING_EDGE | CYHAL_COMP_FALLING_EDGE);
        default:
            CY_ASSERT(false);
            return (cyhal_comp_event_t)0u;
    }
}

static cy_en_ctb_comp_edge_t _cyhal_comp_ctb_convert_hal_event(cyhal_comp_event_t event)
{
    switch((uint8_t)event)
    {
        case 0u:
            return CY_CTB_COMP_EDGE_DISABLE;
        case (uint8_t)CYHAL_COMP_RISING_EDGE:
            return CY_CTB_COMP_EDGE_RISING;
        case (uint8_t)CYHAL_COMP_FALLING_EDGE:
            return CY_CTB_COMP_EDGE_FALLING;
        case (uint8_t)(CYHAL_COMP_RISING_EDGE | CYHAL_COMP_FALLING_EDGE):
            return CY_CTB_COMP_EDGE_BOTH;
        default:
            CY_ASSERT(false);
            return CY_CTB_COMP_EDGE_DISABLE;
    }
}

static void _cyhal_comp_ctb_irq_handler(void)
{
    cyhal_comp_t* obj = _cyhal_ctb_get_interrupt_source();
    Cy_CTB_ClearInterrupt(obj->base_ctb, _cyhal_opamp_convert_sel(obj->resource.channel_num));
    cyhal_comp_event_callback_t callback = (cyhal_comp_event_callback_t)obj->callback_data.callback;
    if(NULL != callback)
    {
        // The CTB hardware doesn't directly capture the event, so just pass on the converted mask
        cyhal_comp_event_t event = _cyhal_comp_ctb_get_enabled_events(obj);
        callback(obj->callback_data.callback_arg, event);
    }
}

static void _cyhal_comp_ctb_cfg_init(void)
{
    if (!_cyhal_comp_ctb_arrays_initialized)
    {
        for (uint8_t i = 0; i < _CYHAL_CTB_INSTANCES * _CYHAL_OPAMP_PER_CTB; i++)
        {
            _cyhal_comp_ctb_config_structs[i] = NULL;
        }
        _cyhal_comp_ctb_arrays_initialized = true;
    }
}

cy_rslt_t _cyhal_comp_ctb_init_hw(cyhal_comp_t *obj, const cy_stc_ctb_opamp_config_t* cfg)
{
    obj->base_ctb = _cyhal_ctb_base[obj->resource.block_num];
    cy_rslt_t result = Cy_CTB_OpampInit(obj->base_ctb, _cyhal_opamp_convert_sel(obj->resource.channel_num), cfg);
    if(CY_RSLT_SUCCESS == result)
    {
        /* Initialize the programmable analog */
        cyhal_analog_ctb_init(obj->base_ctb);

        _cyhal_irq_register(_cyhal_ctb_irq_n[obj->resource.block_num], CYHAL_ISR_PRIORITY_DEFAULT, _cyhal_comp_ctb_irq_handler);
        _cyhal_irq_enable(_cyhal_ctb_irq_n[obj->resource.block_num]);
        _cyhal_comp_ctb_config_structs[(obj->resource.block_num * _CYHAL_OPAMP_PER_CTB) + obj->resource.channel_num] = obj;
    }
    else
    {
        obj->base_ctb = NULL;
    }

    return result;
}

cy_rslt_t _cyhal_comp_ctb_init(cyhal_comp_t *obj, cyhal_gpio_t vin_p, cyhal_gpio_t vin_m, cyhal_gpio_t output, cyhal_comp_config_t *cfg)
{
    CY_ASSERT(NULL != obj);

    /* Initial values */
    cy_rslt_t result = CY_RSLT_SUCCESS;
    memset(obj, 0, sizeof(cyhal_comp_t));
    obj->resource.type = CYHAL_RSC_INVALID;

    /* CTB configuration objects initialization */
    _cyhal_comp_ctb_cfg_init();

    /* Validate pins. vin_p and vin_m are mandatory pins, vout is optional. */
    if ((NC == vin_p) || (NC == vin_m))
    {
        result = CYHAL_COMP_RSLT_ERR_INVALID_PIN;
    }

    /* Allocate resources */
    if(CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_opamp_init_common(&(obj->resource), CYHAL_COMP_RSLT_ERR_INVALID_PIN, vin_p, vin_m, NC /* vout unused by comparator */, output);
    }

    /* Configure the opamp */
    if (result == CY_RSLT_SUCCESS)
    {
        obj->pin_vin_p = vin_p;
        obj->pin_vin_m = vin_m;
        obj->pin_out = output;
        cy_stc_ctb_opamp_config_t config = _cyhal_comp_ctb_default_config;
#if defined(CY_IP_MXS40PASS_CTB_INSTANCES)
        config.oaPower = (cy_en_ctb_power_t)_cyhal_opamp_convert_power(cfg->power);
        config.oaCompHyst = _CYHAL_COMP_CTB_HIST(cfg->hysteresis);
#else
        config.power = (cy_en_ctb_power_t)_cyhal_opamp_convert_power(cfg->power);
        config.compHyst = _CYHAL_COMP_CTB_HIST(cfg->hysteresis);
#endif

        result = _cyhal_comp_ctb_init_hw(obj, &config);
    }

    if (result == CY_RSLT_SUCCESS)
    {
        /* OPAMP Routing. Close input switches for OA0 or OA1. */
        Cy_CTB_SetAnalogSwitch(obj->base_ctb, _cyhal_opamp_convert_switch(obj->resource.channel_num), _cyhal_opamp_pin_to_mask(obj->resource.channel_num, vin_p, vin_m, NC), _CYHAL_CTB_SW_CLOSE);
        _cyhal_opamp_set_isolation_switch(obj->resource.channel_num, obj->base_ctb, true);
    }

    /* Free OPAMP in case of failure */
    if (result != CY_RSLT_SUCCESS)
    {
        _cyhal_comp_ctb_free(obj);
    }
    return result;
}

cy_rslt_t _cyhal_comp_ctb_init_cfg(cyhal_comp_t *obj, const cyhal_comp_configurator_t *cfg)
{
    /* CTB configuration objects initialization */
    _cyhal_comp_ctb_cfg_init();

    cy_rslt_t result = _cyhal_comp_ctb_init_hw(obj, cfg->opamp);
    if(CY_RSLT_SUCCESS != result)
    {
        _cyhal_comp_ctb_free(obj);
    }

    return result;
}

void _cyhal_comp_ctb_free(cyhal_comp_t *obj)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(_cyhal_comp_ctb_arrays_initialized); /* Should not be freeing if we never initialized anything */

    if(CYHAL_RSC_INVALID != obj->resource.type)
    {
        if(false == obj->owned_by_configurator)
        {
            Cy_CTB_SetAnalogSwitch(obj->base_ctb, _cyhal_opamp_convert_switch(obj->resource.channel_num), _cyhal_opamp_pin_to_mask(obj->resource.channel_num, obj->pin_vin_p, obj->pin_vin_m, NC), _CYHAL_CTB_SW_OPEN);
            _cyhal_opamp_set_isolation_switch(obj->resource.channel_num, obj->base_ctb, false);
        }
        cyhal_analog_ctb_free(obj->base_ctb);

        _cyhal_comp_ctb_config_structs[(obj->resource.block_num * _CYHAL_OPAMP_PER_CTB) + obj->resource.channel_num] = NULL;

        uint8_t ctb_num = obj->resource.block_num;
        /* If neither opamp in this ctb is in use, disable the ISR */
        if((NULL == _cyhal_comp_ctb_config_structs[ctb_num * _CYHAL_OPAMP_PER_CTB])
            && (NULL == _cyhal_comp_ctb_config_structs[(ctb_num * _CYHAL_OPAMP_PER_CTB) + 1]))
        {
            _cyhal_irq_free(_cyhal_ctb_irq_n[obj->resource.block_num]);
        }

        if(false == obj->owned_by_configurator)
        {
            cyhal_hwmgr_free(&(obj->resource));
        }
        obj->base_ctb = NULL;
        obj->resource.type = CYHAL_RSC_INVALID;
    }

    _cyhal_utils_release_if_used(&(obj->pin_vin_p));
    _cyhal_utils_release_if_used(&(obj->pin_vin_m));
    _cyhal_utils_release_if_used(&(obj->pin_out));
}

cy_rslt_t _cyhal_comp_ctb_set_power(cyhal_comp_t *obj, cyhal_power_level_t power)
{
    CY_ASSERT(NULL != obj);

    cy_en_ctb_power_t power_level = (cy_en_ctb_power_t)_cyhal_opamp_convert_power(power);
    Cy_CTB_SetPower(obj->base_ctb, _cyhal_opamp_convert_sel(obj->resource.channel_num), power_level, _CYHAL_CTB_PUMP_ENABLE);
    return CY_RSLT_SUCCESS;
}

cy_rslt_t _cyhal_comp_ctb_configure(cyhal_comp_t *obj, cyhal_comp_config_t *cfg)
{
    CY_ASSERT(NULL != obj);

#if defined(CY_IP_MXS40PASS_CTB_INSTANCES)
    cy_rslt_t result = _cyhal_comp_ctb_set_power(obj, cfg->power);
    if(CY_RSLT_SUCCESS == result)
    {
        Cy_CTB_CompSetConfig(obj->base_ctb, _cyhal_opamp_convert_sel(obj->resource.channel_num),
            CY_CTB_COMP_DSI_TRIGGER_OUT_LEVEL, _CYHAL_COMP_CTB_DEFAULT_BYPASS, _CYHAL_COMP_CTB_HIST(cfg->hysteresis));
    }
#else
    cy_stc_ctb_opamp_config_t config = _cyhal_comp_ctb_default_config;
    config.power = (cy_en_ctb_power_t)_cyhal_opamp_convert_power(cfg->power);
    config.compHyst = _CYHAL_COMP_CTB_HIST(cfg->hysteresis);
    cy_rslt_t result = Cy_CTB_OpampInit(obj->base_ctb, _cyhal_opamp_convert_sel(obj->resource.channel_num), &config);
#endif

    return result;
}

bool _cyhal_comp_ctb_read(cyhal_comp_t *obj)
{
    CY_ASSERT(NULL != obj);

    return (1UL == Cy_CTB_CompGetStatus(obj->base_ctb, _cyhal_opamp_convert_sel(obj->resource.channel_num)));
}

void _cyhal_comp_ctb_enable_event(cyhal_comp_t *obj, cyhal_comp_event_t event, uint8_t intr_priority, bool enable)
{
    CY_UNUSED_PARAMETER(intr_priority);
    cyhal_comp_event_t enabled_events = _cyhal_comp_ctb_get_enabled_events(obj);
    if(enable)
    {
        enabled_events |= event;
    }
    else
    {
        enabled_events &= (~event);
    }

    _cyhal_system_irq_t irqn = _cyhal_ctb_irq_n[obj->resource.block_num];
    _cyhal_irq_set_priority(irqn, intr_priority);

    cy_en_ctb_comp_edge_t pdl_event = _cyhal_comp_ctb_convert_hal_event(enabled_events);
    Cy_CTB_CompSetInterruptEdgeType(obj->base_ctb, _cyhal_opamp_convert_sel(obj->resource.channel_num), pdl_event);
}

#if defined(__cplusplus)
}
#endif

#endif /* _CYHAL_DRIVER_AVAILABLE_COMP_CTB */
