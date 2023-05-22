/***************************************************************************//**
* \file cyhal_interconnect.h
*
* \brief
* Provides a high level interface for interacting with the internal digital
* routing on the chip. This interface abstracts out the chip specific details.
* If any chip specific functionality is necessary, or performance is critical
* the low level functions can be used directly.
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
* \addtogroup group_hal_interconnect Interconnect (Internal Digital Routing)
* \ingroup group_hal
* \{
* High level interface to the Infineon digital routing.
*
* \section subsection_interconnect_features Features
* Facilities for runtime manipulation of the on chip routing.
* The following types of connections are supported:
* * Connection from a peripheral to a pin. (A dedicated connection must exist
    between the pin and the peripheral; see the device datasheet for more details)
* * Connecting two peripherals in hardware using the on-chip trigger signaling
*
* \section subsection_interconnect_quickstart Quick Start
* * \ref cyhal_connect_pin can be used to connect a pin to a peripheral.(A dedicated connection must exist
*    between the pin and the peripheral; see the device datasheet for more details)
* * \ref cyhal_disconnect_pin can be used to disconnect a pin from a peripheral.
* The drive mode will be reset to High-Z after disconnecting
*
* \section section_interconnect_snippets Code Snippets
*
* \subsection subsection_interconnect_snippet1 Snippet 1: Connecting a pin to TCPWM block
* The following code snippet demonstrates connecting a GPIO pin to an active TCPWM block on a device
* using the \ref cyhal_connect_pin. It is assumed that the TCPWM is already configured and active.<br>
* \snippet hal_interconnect.c snippet_cyhal_interconnect_connect_pin
*
* \subsection subsection_interconnect_snippet2 Snippet 2: Connecting a Timer output signal to a DMA input signal
* The following code snippet demonstrates configuring and connecting a Timer
* which will overflow every 2 seconds and, in doing so, trigger a DMA channel
* start.
* \snippet hal_interconnect.c snippet_cyhal_interconnect_timer_to_dma
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_interconnect Interconnect HAL Results
 *  Interconnect specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** The source and destination are already connected */
#define CYHAL_INTERCONNECT_RSLT_ALREADY_CONNECTED            \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_INTERCONNECT, 0))
/** Connection is invalid */
#define CYHAL_INTERCONNECT_RSLT_INVALID_CONNECTION           \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_INTERCONNECT, 1))
/** Cannot disconnect. Either no connection in the first place or a bad argument */
#define CYHAL_INTERCONNECT_RSLT_CANNOT_DISCONNECT            \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_INTERCONNECT, 2))

/**
 * \}
 */

/** Connect a pin to a peripheral terminal. This will route a direct connection from the pin to the peripheral.
 * Any previous direct connection from the pin will be overriden.<br>
 * See \ref subsection_interconnect_snippet1
 * @param[in] pin_connection  The pin and target peripheral terminal to be connected
 * @param[in] drive_mode      The drive mode to use for the pin
 * @return The status of the connect request
 */
cy_rslt_t cyhal_connect_pin(const cyhal_resource_pin_mapping_t *pin_connection, uint8_t drive_mode);

/** Disconnect a peripheral from a pin. This will also reset the pin's drive mode to High-Z.
 * @param[in] pin The pin to be disconnected
 * @return The status of the disconnect request
 */
cy_rslt_t cyhal_disconnect_pin(cyhal_gpio_t pin);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_INTERCONNECT_IMPL_HEADER
#include CYHAL_INTERCONNECT_IMPL_HEADER
#endif /* CYHAL_INTERCONNECT_IMPL_HEADER */

/** \} group_hal_interconnect */
