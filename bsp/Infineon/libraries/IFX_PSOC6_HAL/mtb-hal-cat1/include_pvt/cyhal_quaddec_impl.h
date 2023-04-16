/***************************************************************************//**
* \file cyhal_quaddec_impl.h
*
* Description:
* Provides a high level interface for interacting with the Infineon PWM.
*
********************************************************************************
* \copyright
* Copyright 2019-2021 Cypress Semiconductor Corporation (an Infineon company) or
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

#pragma once

#include "cyhal_tcpwm_common.h"

#if defined(CY_IP_MXTCPWM_INSTANCES) || defined(CY_IP_M0S8TCPWM_INSTANCES)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/** \addtogroup group_hal_impl_quaddec Quadrature Decoder
 * \ingroup group_hal_impl
 * \{
 * \section group_hal_impl_quaddec_interconnect Interconnect
 * In PSoCâ„¢ Quadrature Decoder channels can configure multiple input and output
 * triggers simultaneously. 1 or more input triggers can be configured to
 * initiate different PWM actions (e.g start, stop, reload, etc) with
 * configurable edge detection on that incoming signal. Output triggers are
 * based on certain events (e.g overflow, cc_match, etc).
 */

__STATIC_INLINE uint32_t _cyhal_quaddec_convert_event(cyhal_quaddec_event_t event)
{
    uint32_t pdl_event = 0U;
    if (event & CYHAL_QUADDEC_IRQ_TERMINAL_COUNT)
    {
        pdl_event |= CY_TCPWM_INT_ON_TC;
    }
    if (event & CYHAL_QUADDEC_IRQ_CAPTURE)
    {
        pdl_event |= CY_TCPWM_INT_ON_CC;
    }
    return pdl_event;
}

__STATIC_INLINE void _cyhal_quaddec_register_callback(cyhal_quaddec_t *obj,
                                                      cyhal_quaddec_event_callback_t callback,
                                                      void *callback_arg)
{
    _cyhal_tcpwm_register_callback(&obj->tcpwm.resource, (cy_israddress) callback, callback_arg);
}

#define cyhal_quaddec_register_callback(obj, callback, callback_arg) \
        _cyhal_quaddec_register_callback(obj, callback, callback_arg)

__STATIC_INLINE void _cyhal_quaddec_enable_event(cyhal_quaddec_t *obj,
                                                 cyhal_quaddec_event_t event,
                                                 uint8_t intr_priority,
                                                 bool enable)
{
    uint32_t converted = _cyhal_quaddec_convert_event(event);
    _cyhal_tcpwm_enable_event(&obj->tcpwm, &obj->tcpwm.resource, converted, intr_priority,
                              enable);
}

#define cyhal_quaddec_enable_event(obj, event, intr_priority, enable) \
        _cyhal_quaddec_enable_event(obj, event, intr_priority, enable)

/** \} group_hal_impl_quaddec */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* defined(CY_IP_MXTCPWM_INSTANCES) */
