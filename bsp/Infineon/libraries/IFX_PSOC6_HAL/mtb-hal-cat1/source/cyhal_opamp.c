/***************************************************************************/ /**
* \file cyhal_opamp.c
*
* \brief
* Provides a high level interface for interacting with the Infineon Continuous
* Time Block. This interface abstracts out the chip specific details. If any chip
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

#include <string.h>
#include "cyhal_opamp.h"
#include "cyhal_gpio.h"
#include "cyhal_analog_common.h"
#include "cyhal_hwmgr.h"
#include "cy_ctb.h"

/**
* \addtogroup group_hal_impl_opamp Opamp (Operational Amplifier)
* \ingroup group_hal_impl
*
* \section group_hal_impl_opamp_power Power Level Mapping
* The following table shows how the HAL-defined power levels map to the hardware-specific power levels
* | HAL Power Level                | Opamp Power Level   |
* | ------------------------------ | ------------------- |
* | @ref CYHAL_POWER_LEVEL_HIGH    | CY_CTB_POWER_HIGH   |
* | @ref CYHAL_POWER_LEVEL_MEDIUM  | CY_CTB_POWER_MEDIUM |
* | @ref CYHAL_POWER_LEVEL_LOW     | CY_CTB_POWER_LOW    |
* | @ref CYHAL_POWER_LEVEL_DEFAULT | CY_CTB_POWER_MEDIUM |
*
*/

#if (CYHAL_DRIVER_AVAILABLE_OPAMP)

static const cy_stc_ctb_opamp_config_t _cyhal_opamp_default_config =
{
#if defined(CY_IP_MXS40PASS_CTB_INSTANCES)
    .deepSleep    = CY_CTB_DEEPSLEEP_ENABLE,
    .oaPower      = CY_CTB_POWER_OFF,
    .oaMode       = CY_CTB_MODE_OPAMP10X,
    .oaPump       = _CYHAL_CTB_PUMP_ENABLE,
    .oaCompEdge   = CY_CTB_COMP_EDGE_DISABLE,
    .oaCompLevel  = CY_CTB_COMP_DSI_TRIGGER_OUT_LEVEL,
    .oaCompBypass = CY_CTB_COMP_BYPASS_SYNC,
    .oaCompHyst   = CY_CTB_COMP_HYST_DISABLE,
    .oaCompIntrEn = true,
#else
    .power      = CY_CTB_POWER_OFF,
    .outputMode = CY_CTB_MODE_OPAMP_EXTERNAL,
    .pump       = _CYHAL_CTB_PUMP_ENABLE,
    .compEdge   = CY_CTB_COMP_EDGE_DISABLE,
    .compLevel  = CY_CTB_COMP_TRIGGER_OUT_LEVEL,
    .compBypass = false,
    .compHyst   = false,
    .compIntrEn = true,
#endif
};

#if defined(__cplusplus)
extern "C"
{
#endif

cy_rslt_t _cyhal_opamp_init_hw(cyhal_opamp_t *obj, const cy_stc_ctb_opamp_config_t* cfg)
{
    obj->base = _cyhal_ctb_base[obj->resource.block_num];
    cy_rslt_t result = Cy_CTB_OpampInit(obj->base, _cyhal_opamp_convert_sel(obj->resource.channel_num), cfg);
    if(CY_RSLT_SUCCESS == result)
    {
        obj->is_init_success = true;
        /* Initialize the programmable analog */
        cyhal_analog_ctb_init(obj->base);
    }
    return result;
}

cy_rslt_t cyhal_opamp_init(cyhal_opamp_t *obj, cyhal_gpio_t vin_p, cyhal_gpio_t vin_m, cyhal_gpio_t vout)
{
    /* Check if obj is free */
    CY_ASSERT(NULL != obj);

    /* Initial values */
    cy_rslt_t result = CY_RSLT_SUCCESS;
    memset(obj, 0, sizeof(cyhal_opamp_t));
    obj->base = NULL;
    obj->resource.type = CYHAL_RSC_INVALID;
    obj->is_init_success = false;

    /* Validate input pins. vin_p and vout are mandatory pins, vin_m is optional. */
    if ((NC == vin_p) || (NC == vout))
    {
        result = CYHAL_OPAMP_RSLT_ERR_INVALID_PIN;
    }

    /* Allocate resources */
    if(CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_opamp_init_common(&(obj->resource), CYHAL_OPAMP_RSLT_BAD_ARGUMENT, vin_p, vin_m, vout, NC /* comp_out unused by opamp */);
    }


    /* Configure the opamp */
    if (result == CY_RSLT_SUCCESS)
    {
        obj->pin_vin_p = vin_p;
        obj->pin_vin_m = vin_m;
        obj->pin_vout = vout;

        result = _cyhal_opamp_init_hw(obj, &_cyhal_opamp_default_config);
    }

    if (result == CY_RSLT_SUCCESS)
    {
        /* OPAMP Routing. Close input switches for OA0 or OA1. */
        Cy_CTB_SetAnalogSwitch(obj->base, _cyhal_opamp_convert_switch(obj->resource.channel_num), _cyhal_opamp_pin_to_mask(obj->resource.channel_num, vin_p, vin_m, vout), _CYHAL_CTB_SW_CLOSE);
        _cyhal_opamp_set_isolation_switch(obj->resource.channel_num, obj->base, true);
    }

    /* Free OPAMP in case of failure */
    if (result != CY_RSLT_SUCCESS)
    {
        cyhal_opamp_free(obj);
    }
    return result;
}

cy_rslt_t cyhal_opamp_init_cfg(cyhal_opamp_t *obj, const cyhal_opamp_configurator_t *cfg)
{
    memset(obj, 0, sizeof(cyhal_opamp_t));
    obj->owned_by_configurator = true;
    obj->resource = *cfg->resource;
    obj->is_init_success = false;
    obj->pin_vin_p = NC;
    obj->pin_vin_m = NC;
    obj->pin_vout  = NC;
    cy_rslt_t result = _cyhal_opamp_init_hw(obj, cfg->config);
    if(CY_RSLT_SUCCESS != result)
    {
        cyhal_opamp_free(obj);
    }

    return result;
}

cy_rslt_t cyhal_opamp_set_power(cyhal_opamp_t *obj, cyhal_power_level_t power)
{
    /* Safe convert power level from HAL (cyhal_power_level_t) to PDL (cy_en_ctb_power_t) */
    cy_en_ctb_power_t power_level = (cy_en_ctb_power_t)_cyhal_opamp_convert_power(power);

    Cy_CTB_SetPower(obj->base, _cyhal_opamp_convert_sel(obj->resource.channel_num), power_level, _CYHAL_CTB_PUMP_ENABLE);

    return CY_RSLT_SUCCESS;
}

void cyhal_opamp_free(cyhal_opamp_t *obj)
{
    if (NULL != obj && NULL != obj->base)
    {
        if (obj->is_init_success)
        {
            cyhal_opamp_set_power(obj, CYHAL_POWER_LEVEL_OFF);
            if(false == obj->owned_by_configurator)
            {
                Cy_CTB_SetAnalogSwitch(obj->base, _cyhal_opamp_convert_switch(obj->resource.channel_num), _cyhal_opamp_pin_to_mask(obj->resource.channel_num, obj->pin_vin_p, obj->pin_vin_m, obj->pin_vout), _CYHAL_CTB_SW_OPEN);
                _cyhal_opamp_set_isolation_switch(obj->resource.channel_num, obj->base, false);
            }
            cyhal_analog_ctb_free(obj->base);
        }
    }

    if((NULL != obj) && (CYHAL_RSC_INVALID != obj->resource.type))
    {
        if(false == obj->owned_by_configurator)
        {
            cyhal_hwmgr_free(&obj->resource);
        }
        obj->base = NULL;
        obj->resource.type = CYHAL_RSC_INVALID;
    }

    if(NULL != obj)
    {
        _cyhal_utils_release_if_used(&(obj->pin_vin_p));
        _cyhal_utils_release_if_used(&(obj->pin_vout));
        _cyhal_utils_release_if_used(&(obj->pin_vin_m));
    }
}

#if defined(__cplusplus)
}
#endif

#endif /* CYHAL_DRIVER_AVAILABLE_OPAMP */
