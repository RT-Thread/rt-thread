/***************************************************************************/ /**
* \file cyhal_comp.c
*
* \brief
* Provides a high level interface for interacting with the Infineon analog
* comparator. This interface abstracts out the chip specific details. If any chip
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
#include "cyhal_comp.h"
#include "cyhal_comp_ctb.h"
#include "cyhal_comp_lp.h"
#include "cyhal_gpio.h"
#include "cyhal_system.h"

#include <string.h> // For memset

/**
* \addtogroup group_hal_impl_comp COMP (Analog Comparator)
* \ingroup group_hal_impl
* \{
* On CAT1 & CAT2, the comparator driver can use either of two underlying hardware blocks:
* - Opamp (configured as analog comparator)
* - LPComp (Low Power Comparator)
*
* Generally, a set of pins can only connect to either an Opamp or an LPComp but not both. In the event
* that both connections are possible, the LPComp will be preferred.
*
* \section group_hal_impl_comp_power Power Level Mapping
* The following table shows how the HAL-defined power levels map to the hardware-specific power levels.
* For the LPComp, some levels are named differently between CAT1 & CAT2. In this case, the differences
* are in brackets, with the first item being for CAT1 and the second for CAT2.
* | HAL Power Level                | Opamp Power Level   | LPComp Power Level           |
* | ------------------------------ | ------------------- | ---------------------------- |
* | @ref CYHAL_POWER_LEVEL_HIGH    | CY_CTB_POWER_HIGH   | CY_LPCOMP_MODE_[NORMAL/FAST] |
* | @ref CYHAL_POWER_LEVEL_MEDIUM  | CY_CTB_POWER_MEDIUM | CY_LPCOMP_MODE_[LP/SLOW]     |
* | @ref CYHAL_POWER_LEVEL_LOW     | CY_CTB_POWER_LOW    | CY_LPCOMP_MODE_ULP           |
* | @ref CYHAL_POWER_LEVEL_DEFAULT | CY_CTB_POWER_MEDIUM | CY_LPCOMP_MODE_[LP/SLOW]     |
*
* \} group_hal_impl_comp
*/

/* This file is the top-level wrapper. Comp can be implemented on top of either LPComp or the CTB Opamps */
#if (CYHAL_DRIVER_AVAILABLE_COMP)

#if defined(__cplusplus)
extern "C"
{
#endif

cy_rslt_t cyhal_comp_init(cyhal_comp_t *obj, cyhal_gpio_t vin_p, cyhal_gpio_t vin_m, cyhal_gpio_t output, cyhal_comp_config_t *cfg)
{
    cy_rslt_t result;
#if (_CYHAL_DRIVER_AVAILABLE_COMP_LP)
    result = _cyhal_comp_lp_init(obj, vin_p, vin_m, output, cfg);
#endif
#if (_CYHAL_DRIVER_AVAILABLE_COMP_CTB)
    #if (_CYHAL_DRIVER_AVAILABLE_COMP_LP)
    if (CY_RSLT_SUCCESS != result)
    #endif
    {
        result = _cyhal_comp_ctb_init(obj, vin_p, vin_m, output, cfg);
    }
#endif
    return result;
}

cy_rslt_t cyhal_comp_init_cfg(cyhal_comp_t *obj, const cyhal_comp_configurator_t *cfg)
{
    cy_rslt_t result = CYHAL_COMP_RSLT_ERR_BAD_ARGUMENT;
    memset(obj, 0, sizeof(cyhal_comp_t));
    obj->owned_by_configurator = true;
    obj->resource = *cfg->resource;
    obj->pin_vin_p = NC;
    obj->pin_vin_m = NC;
    obj->pin_out  = NC;

#if (_CYHAL_DRIVER_AVAILABLE_COMP_LP)
    if (CYHAL_RSC_LPCOMP == cfg->resource->type)
    {
        result = _cyhal_comp_lp_init_cfg(obj, cfg);
    }
#endif

#if (_CYHAL_DRIVER_AVAILABLE_COMP_CTB)
    if (CYHAL_RSC_OPAMP == cfg->resource->type)
    {
        result = _cyhal_comp_ctb_init_cfg(obj, cfg);
    }
#endif

    return result;
}

void cyhal_comp_free(cyhal_comp_t *obj)
{
#if (_CYHAL_DRIVER_AVAILABLE_COMP_CTB)
    #if (_CYHAL_DRIVER_AVAILABLE_COMP_LP)
    if(obj->resource.type == CYHAL_RSC_OPAMP)
    #endif
    {
        _cyhal_comp_ctb_free(obj);
    }
#endif
    {
#if (_CYHAL_DRIVER_AVAILABLE_COMP_LP)
    #if (_CYHAL_DRIVER_AVAILABLE_COMP_CTB)
    if(obj->resource.type == CYHAL_RSC_LPCOMP)
    #endif
    {
        _cyhal_comp_lp_free(obj);
    }
#endif
    }
}

cy_rslt_t cyhal_comp_set_power(cyhal_comp_t *obj, cyhal_power_level_t power)
{
#if (_CYHAL_DRIVER_AVAILABLE_COMP_CTB)
    #if (_CYHAL_DRIVER_AVAILABLE_COMP_LP)
    if(obj->resource.type == CYHAL_RSC_OPAMP)
    #endif
    {
        return _cyhal_comp_ctb_set_power(obj, power);
    }
#endif
#if (_CYHAL_DRIVER_AVAILABLE_COMP_LP)
    CY_ASSERT(obj->resource.type == CYHAL_RSC_LPCOMP);
    return _cyhal_comp_lp_set_power(obj, power);
#endif
}

cy_rslt_t cyhal_comp_configure(cyhal_comp_t *obj, cyhal_comp_config_t *cfg)
{
#if (_CYHAL_DRIVER_AVAILABLE_COMP_CTB)
    #if (_CYHAL_DRIVER_AVAILABLE_COMP_LP)
    if(obj->resource.type == CYHAL_RSC_OPAMP)
    #endif
    {
        return _cyhal_comp_ctb_configure(obj, cfg);
    }
#endif
#if (_CYHAL_DRIVER_AVAILABLE_COMP_LP)
    CY_ASSERT(obj->resource.type == CYHAL_RSC_LPCOMP);
    return _cyhal_comp_lp_configure(obj, cfg);
#endif
}

bool cyhal_comp_read(cyhal_comp_t *obj)
{
#if (_CYHAL_DRIVER_AVAILABLE_COMP_CTB)
    #if (_CYHAL_DRIVER_AVAILABLE_COMP_LP)
    if(obj->resource.type == CYHAL_RSC_OPAMP)
    #endif
    {
        return _cyhal_comp_ctb_read(obj);
    }
#endif
#if (_CYHAL_DRIVER_AVAILABLE_COMP_LP)
    CY_ASSERT(obj->resource.type == CYHAL_RSC_LPCOMP);
    return _cyhal_comp_lp_read(obj);
#endif
}

void cyhal_comp_register_callback(cyhal_comp_t *obj, cyhal_comp_event_callback_t callback, void *callback_arg)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);

    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    obj->callback_data.callback = (cy_israddress) callback;
    obj->callback_data.callback_arg = callback_arg;
    cyhal_system_critical_section_exit(savedIntrStatus);
}

void cyhal_comp_enable_event(cyhal_comp_t *obj, cyhal_comp_event_t event, uint8_t intr_priority, bool enable)
{
#if (_CYHAL_DRIVER_AVAILABLE_COMP_CTB)
    #if (_CYHAL_DRIVER_AVAILABLE_COMP_LP)
    if(obj->resource.type == CYHAL_RSC_OPAMP)
    #endif
    {
        _cyhal_comp_ctb_enable_event(obj, event, intr_priority, enable);
        return;
    }
#endif
#if (_CYHAL_DRIVER_AVAILABLE_COMP_LP)
    CY_ASSERT(obj->resource.type == CYHAL_RSC_LPCOMP);
    _cyhal_comp_lp_enable_event(obj, event, intr_priority, enable);
#endif
}

#if defined(__cplusplus)
}
#endif

#endif /* CYHAL_DRIVER_AVAILABLE_COMP */
