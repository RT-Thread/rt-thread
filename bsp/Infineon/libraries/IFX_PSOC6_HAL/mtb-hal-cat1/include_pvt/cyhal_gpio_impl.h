/***************************************************************************//**
* \file cyhal_gpio_impl.h
*
* Description:
* Provides a high level interface for interacting with the Infineon GPIO. This is
* a wrapper around the lower level PDL API.
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

#pragma once

#include "cy_gpio.h"
#include "cyhal_gpio.h"
#include "cyhal_utils.h"
#include "cy_utils.h"

#if defined(CY_IP_MXS40IOSS) || defined(CY_IP_M0S8IOSS) || defined(CY_IP_MXS40SIOSS) || defined(CY_IP_MXS22IOSS)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B)
/** \addtogroup group_hal_impl_gpio GPIO
 * \ingroup group_hal_impl
 * \{
 * \section group_hal_impl_gpio_interrupt Interrupt Priorities
 * In CAT1 & CAT2 (PSoC™ 6/4), each GPIO port has a single IRQ line. Hence, there can only be a
 * single interrupt handler and priority set at the hardware level. The HAL tracks any interrupt
 * handler that is registered through \ref cyhal_gpio_register_callback separately so it can run
 * the appropriate pin specific callback anyway. However, the HAL will take over the interrupt
 * for the port. Additionally, it cannot do anything about the priority and all pins on the port
 * will share the last priority set via \ref cyhal_gpio_enable_event. for a specific pin on a port
 * will apply to the all the pins in that pin's port. If multiple pins on the same port are set at
 * different priorities, the priority that the last pin is set to will be applied to all pins used
 * on that port.
 *
 * \section group_hal_impl_gpio_interconnect Interconnect
 * In CAT1 & CAT2 (PSoC™ 6/4) only a subset of pins available on a board are connected to input
 * triggers. Another subset is connected to output triggers. Check the appropriate file for your
 * board in pin_packages/ to determine what pins can be used. A particular pin can have 0 or 1
 * input triggers and 0 or 1 output triggers. Input triggers to a pin are used to clear/set the
 * GPIO pins output. An output trigger on a pin is activated when the pins GPIO input is set.
 *
 * \} group_hal_impl_gpio
 */
#elif defined(COMPONENT_CAT2)
/** \addtogroup group_hal_impl_gpio GPIO
 * \ingroup group_hal_impl
 * \{
 * \section group_hal_impl_gpio_interrupt Interrupt Priorities
 * In CAT2 (PMG/PSoC™ 4), ports 0 through 3 have dedicated IRQ lines (ioss_interrupts_gpio_0_IRQn - ioss_interrupts_gpio_3_IRQn)
 * and other ports are required to use the All-Port IRQ line (ioss_interrupt_gpio_IRQn).
 * If multiple pins on the same port are set at different priorities, the priority that the
 * last pin is set to will be applied to all pins used on that port. When using the pin that does
 * not have a dedicated IRQ line (port 4 and higher) following are the implications,
 * 1. The priority set through \ref cyhal_gpio_enable_event for the specific pin will
 *    apply to all pins on port 4 and higher.
 * 2. The interrupts will not be proccessed in the same order as they were received
 *    because the same All-Port IRQ line will be used for all GPIOs.
 *
 ** \section group_hal_impl_gpio_interconnect Interconnect
 * PSoC™ 4 does not have GPIO triggers.
 * \} group_hal_impl_gpio
 */
#endif

/*******************************************************************************
*       Defines
*******************************************************************************/
#define CYHAL_GET_PORTADDR(pin)    (Cy_GPIO_PortToAddr(CYHAL_GET_PORT(pin)))  /**< Macro to get the port address from pin */

/*******************************************************************************
*       Functions
*******************************************************************************/

__STATIC_INLINE void cyhal_gpio_write_internal(cyhal_gpio_t pin, bool value)
{
    Cy_GPIO_Write(CYHAL_GET_PORTADDR(pin), CYHAL_GET_PIN(pin), value);
}

#define cyhal_gpio_write(pin, value) cyhal_gpio_write_internal(pin, value)

__STATIC_INLINE bool cyhal_gpio_read_internal(cyhal_gpio_t pin)
{
    return 0 != Cy_GPIO_Read(CYHAL_GET_PORTADDR(pin), CYHAL_GET_PIN(pin));
}

#define cyhal_gpio_read(pin) cyhal_gpio_read_internal(pin)

__STATIC_INLINE void cyhal_gpio_toggle_internal(cyhal_gpio_t pin)
{
    Cy_GPIO_Inv(CYHAL_GET_PORTADDR(pin), CYHAL_GET_PIN(pin));
}

#define cyhal_gpio_toggle(pin) cyhal_gpio_toggle_internal(pin)

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* defined(CY_IP_MXS40IOSS) || defined(CY_IP_M0S8IOSS) || defined(CY_IP_MXS40SIOSS) */
