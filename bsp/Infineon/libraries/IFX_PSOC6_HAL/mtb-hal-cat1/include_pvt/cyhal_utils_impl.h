/***************************************************************************//**
* \file cyhal_utils_impl.h
*
* \brief
* Provides utility functions for working with the CAT1/CAT2 HAL implementation.
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

/** \cond INTERNAL */
/**
* \addtogroup group_hal_impl
* \{
* Common utility macros & functions used by multiple HAL drivers.
*/

#pragma once

#include "cy_result.h"
#include "cyhal_hw_types.h"
#include "cy_utils.h"
#include "cyhal_utils.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(COMPONENT_CAT1D)
#define _CYHAL_UTILS_PACK_INSTANCE_GROUP(instance, group)   (((instance) << 4) | (group))
#define _CYHAL_UTILS_UNPACK_INSTANCE(value)                 (((value) >> 4) & 0x3)
#define _CYHAL_UTILS_UNPACK_GROUP(value)                    ((value) & 0xF)
#endif /* defined(COMPONENT_CAT1D) */

/**
* \addtogroup group_hal_impl_pin_package
* \{
*/

/** Converts the provided gpio pin to a resource instance object
 *
 * @param[in] pin  The pin to get a resource object for
 * @return The equivalent resource instance object for the provided pin.
 */
static inline cyhal_resource_inst_t _cyhal_utils_get_gpio_resource(cyhal_gpio_t pin)
{
    cyhal_resource_inst_t rsc = { CYHAL_RSC_GPIO, CYHAL_GET_PORT(pin), CYHAL_GET_PIN(pin) };
    return rsc;
}

/** Attempts to reserve the specified pin and then initialize it to connect to the item defined by the provided mapping object.
 * @param[in] mapping    The pin/hardware block connection mapping information
 * @param[in] drive_mode The drive mode for the pin
 * @return CY_RSLT_SUCCESS if everything was ok, else an error.
 */
cy_rslt_t _cyhal_utils_reserve_and_connect(const cyhal_resource_pin_mapping_t *mapping, uint8_t drive_mode);

/** Disconnects any routing for the pin from the interconnect driver and then free's the pin from the hwmgr.
 *
 * @param[in] pin       The pin to disconnect and free
 */
void _cyhal_utils_disconnect_and_free(cyhal_gpio_t pin);

/** \} group_hal_impl_pin_package */

#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)

/** Gets the HF clock for the specified peripheral clock group.
 * @param[in] peri_group    The peripheral clock divider group to get the associated HF clock for
 * @return The HF clock that drives the specified peripheral group
 */
uint8_t _cyhal_utils_get_hfclk_for_peri_group(uint8_t peri_group);

/** Gets the peripheral clock group that drives the specified item.
 * @param[in] clocked_item  The item to get the source clock information for
 * @return The peripheral group that feeds the clock tree for the item
 */
uint8_t _cyhal_utils_get_peri_group(const cyhal_resource_inst_t *clocked_item);
#endif

/** Gets the number of clock instances in a particular block
  *
  * @param block The block block for which to get the instance count
  * @return The number of clocks of the specified type
  */
uint32_t _cyhal_utils_get_clock_count(cyhal_clock_block_t block);

/** Gets the peripheral clock frequency that is feeding the clock tree for the specified
 * resource.
 *
 * @param[in] clocked_item  The resource to get the frequency for
 * @return The peripheral clock frequency for the provided resource type
 */
static inline uint32_t _cyhal_utils_get_peripheral_clock_frequency(const cyhal_resource_inst_t *clocked_item)
{
    #if defined(COMPONENT_CAT1A)
    CY_UNUSED_PARAMETER(clocked_item);
    return Cy_SysClk_ClkPeriGetFrequency();
    #elif defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
    CY_ASSERT(NULL != clocked_item);
    uint8_t peri_group = _cyhal_utils_get_peri_group(clocked_item);
    uint8_t hfclk = _cyhal_utils_get_hfclk_for_peri_group(peri_group);
    return Cy_SysClk_ClkHfGetFrequency(hfclk);
    #elif defined(COMPONENT_CAT2)
    CY_UNUSED_PARAMETER(clocked_item);
    return Cy_SysClk_ClkSysGetFrequency();
    #endif
}

/** Calculate a peripheral clock divider value that needs to be set to reach the frequency closest
 * to the one requested.
 * \note The caller may need to subtract one from the value returned in order to align with the
 * API/register requirements. This is necessary if the API/register expects a value of 0 to mean
 * divide by 1.
 *
 * @param[in] clocked_item  The resource to get the frequency for
 * @param[in] frequency     The desired frequency
 * @param[in] frac_bits     The number of fractional bits that the divider has
 * @return The calculated divider value
 */
static inline uint32_t _cyhal_utils_divider_value(const cyhal_resource_inst_t *clocked_item, uint32_t frequency, uint32_t frac_bits)
{
    return ((_cyhal_utils_get_peripheral_clock_frequency(clocked_item) * (1 << frac_bits)) + (frequency / 2)) / frequency;
}

/** Converts a hal pm mode to a pdl mode
 *
 * @param[in] mode          hal power management callback mode.
 * @return Equivalent pdl syspm mode.
 */
cy_en_syspm_callback_mode_t _cyhal_utils_convert_haltopdl_pm_mode(cyhal_syspm_callback_mode_t mode);

/** Converts a pdl pm mode to a hal mode
 *
 * @param[in] mode          pdl syspm power management callback mode.
 * @return Equivalent hal pm callback mode.
 */
cyhal_syspm_callback_mode_t _cyhal_utils_convert_pdltohal_pm_mode(cy_en_syspm_callback_mode_t mode);

/**
 * Calculates clock tolerance in the specified units given a desired and actual frequency
 *
 * @param[in] type                  tolerance type
 * @param[in] desired_hz            desired clock frequency in hertz
 * @param[in] actual_hz             actual clock frequency in hertz
 * @return the computed tolerance
 */
int32_t _cyhal_utils_calculate_tolerance(cyhal_clock_tolerance_unit_t type, uint32_t desired_hz, uint32_t actual_hz);

/**
 * Allocates a clock that can drive the specified instance.
 *
 * @param[out]  clock               The clock object to initialize
 * @param[in]   clocked_item        The destination that the allocated clock must be able to drive
 * @param[in]   div                 The divider width that is required. This is ignored if the block is hard-wired to
 *                                  an HFCLK output
 * @param[in]   accept_larger       If no dividers of the specified width are available, can a wider divider be
 *                                  substituted.
 */
cy_rslt_t _cyhal_utils_allocate_clock(cyhal_clock_t *clock, const cyhal_resource_inst_t *clocked_item,
                        cyhal_clock_block_t div, bool accept_larger);

/**
 * Attempts to set the clock to the specified frequency. This is similar to cyhal_clock_set_frequency,
 * but it will also make an attempt to set the frequency for HFCLK outputs, which are not supported by the public
 * API due to their limited range of supported dividers (1, 2, 4, 8)
 *
 * @param[in] clock                 The clock instance to set the frequency for.
 * @param[in] hz                    The frequency, in hertz, to set the clock to.
 * @param[in] tolerance             The allowed tolerance from the desired hz that is acceptable, use NULL if no
 *                                  tolerance check is required.
 */
cy_rslt_t _cyhal_utils_set_clock_frequency(cyhal_clock_t* clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance);

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
/**
 * Finds best divider for HF clock according to source and desired frequency data
 *
 * @param[in] hz_src                clock source frequency in hertz
 * @param[in] desired_hz            desired clock frequency in hertz
 * @param[in] tolerance             desired clock tolerance to achieve. If NULL provided, all possible dividers will
 *                                  be checked and selected most suitable.
 * @param[in] only_below_desired    resulting clock frequencies, that are above desired_hz will be skipped
 * @param[out] div                  resulting divider
 * @return CYHAL_CLOCK_RSLT_ERR_FREQ if divider is not found, CY_RSLT_SUCCESS in other situations
 */
cy_rslt_t _cyhal_utils_find_hf_clk_div(uint32_t hz_src, uint32_t desired_hz, const cyhal_clock_tolerance_t *tolerance,
                        bool only_below_desired, uint32_t *div);

/** Function for finding most suitable divider for provided clock */
typedef cy_rslt_t (*_cyhal_utils_clk_div_func_t)(uint32_t hz_src, uint32_t desired_hz,
                        const cyhal_clock_tolerance_t *tolerance, bool only_below_desired, uint32_t *div);

/**
 * Finds for provided HF clock most suitable source to achieve target clock frequency and returns it with
 * corresponding divider value. No clock configuration changed in this function.
 *
 * @param[in] clock                 The HFCLK clock instance that needs clock configuration.
 * @param[in] hz                    The maximum frequency, in hertz, that needs to be achieved. The clock will not exceed
 *                                  this value.
 * @param[in] tolerance             The allowed tolerance below the desired hz that is acceptable, use NULL if no
 *                                  tolerance check is required.
 * @param[in] div_find_func         Pointer to _cyhal_utils_clk_div_func_t - type function, that will find most suitable
 *                                  divider for provided clock.
 * @param[out] hf_source            Resulting HF source clock, switching to which, in combination with resulting divider,
 *                                  will provide frequency closest to desired.
 * @param[out] div                  Resulting divider for resulting HF source clock.
 */
cy_rslt_t _cyhal_utils_find_hf_source_n_divider(cyhal_clock_t *clock, uint32_t hz,
                        const cyhal_clock_tolerance_t *tolerance, _cyhal_utils_clk_div_func_t div_find_func,
                        cyhal_clock_t *hf_source, uint32_t *div);

/**
 * Attempts to set the clock to the specified frequency. This is similar to cyhal_clock_set_frequency, but it will also
 * make an attempt to set the frequency for HFCLK outputs. This is an enhancement beyond _cyhal_utils_set_clock_frequency
 * as this will also attemt to adjust the source clock as well as change the divider.
 *
 * @param[in] clock                 The HFCLK clock instance to set the frequency for.
 * @param[in] hz                    The maximum frequency, in hertz, to set the clock to. The clock will not exceed this
 *                                  value.
 * @param[in] tolerance             The allowed tolerance below the desired hz that is acceptable, use NULL if no
 *                                  tolerance check is required.
 */
cy_rslt_t _cyhal_utils_set_clock_frequency2(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance);

/* Compatibility macros until other environments are updated to not use this anymore. */
#define CY_UTILS_GET_RESOURCE(pin, mappings)            _CYHAL_UTILS_GET_RESOURCE((pin), (mappings))
#define cyhal_utils_get_resource(pin, mappings, count)  _cyhal_utils_get_resource((pin), (mappings), (count), NULL)
#define cyhal_utils_get_gpio_resource(pin)              _cyhal_utils_get_gpio_resource((pin))
#define CYHAL_SCB_BASE_ADDRESSES                        _CYHAL_SCB_BASE_ADDRESSES
#define CYHAL_TCPWM_DATA                                _CYHAL_TCPWM_DATA

#endif /* defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)*/



static inline cy_rslt_t _cyhal_utils_peri_pclk_set_divider(en_clk_dst_t clk_dest, const cyhal_clock_t *clock, uint32_t div)
{
    #if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
    return Cy_SysClk_PeriPclkSetDivider(clk_dest, _CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel, div);
    #else
    CY_UNUSED_PARAMETER(clk_dest);
    return Cy_SysClk_PeriphSetDivider(_CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel, div);
    #endif
}
static inline uint32_t _cyhal_utils_peri_pclk_get_divider(en_clk_dst_t clk_dest, const cyhal_clock_t *clock)
{
    #if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
    return Cy_SysClk_PeriPclkGetDivider(clk_dest, _CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel);
    #else
    CY_UNUSED_PARAMETER(clk_dest);
    return Cy_SysClk_PeriphGetDivider(_CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel);
    #endif
}
static inline cy_rslt_t _cyhal_utils_peri_pclk_set_frac_divider(en_clk_dst_t clk_dest, const cyhal_clock_t *clock, uint32_t div_int, uint32_t div_frac)
{
    #if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
    return Cy_SysClk_PeriPclkSetFracDivider(clk_dest, _CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel, div_int, div_frac);
    #else
    CY_UNUSED_PARAMETER(clk_dest);
    return Cy_SysClk_PeriphSetFracDivider(_CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel, div_int, div_frac);
    #endif
}
static inline void _cyhal_utils_peri_pclk_get_frac_divider(en_clk_dst_t clk_dest, const cyhal_clock_t *clock, uint32_t *div_int, uint32_t *div_frac)
{
    #if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
    Cy_SysClk_PeriPclkGetFracDivider(clk_dest, _CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel, div_int, div_frac);
    #else
    CY_UNUSED_PARAMETER(clk_dest);
    Cy_SysClk_PeriphGetFracDivider(_CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel, div_int, div_frac);
    #endif
}
static inline uint32_t _cyhal_utils_peri_pclk_get_frequency(en_clk_dst_t clk_dest, const cyhal_clock_t *clock)
{
    #if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
    return Cy_SysClk_PeriPclkGetFrequency(clk_dest, _CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel);
    #else
    CY_UNUSED_PARAMETER(clk_dest);
    return Cy_SysClk_PeriphGetFrequency(_CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel);
    #endif
}
static inline cy_rslt_t _cyhal_utils_peri_pclk_assign_divider(en_clk_dst_t clk_dest, const cyhal_clock_t *clock)
{
    #if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
        return Cy_SysClk_PeriPclkAssignDivider(clk_dest, _CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel);
    #else
        return Cy_SysClk_PeriphAssignDivider(clk_dest, _CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel);
    #endif
}
static inline uint32_t _cyhal_utils_peri_pclk_get_assigned_divider(en_clk_dst_t clk_dest)
{
    #if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
        return Cy_SysClk_PeriPclkGetAssignedDivider(clk_dest);
    #else
        return Cy_SysClk_PeriphGetAssignedDivider(clk_dest);
    #endif
}
static inline cy_rslt_t _cyhal_utils_peri_pclk_enable_divider(en_clk_dst_t clk_dest, const cyhal_clock_t *clock)
{
    #if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
    return Cy_SysClk_PeriPclkEnableDivider(clk_dest, _CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel);
    #else
    CY_UNUSED_PARAMETER(clk_dest);
    return Cy_SysClk_PeriphEnableDivider(_CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel);
    #endif
}
static inline cy_rslt_t _cyhal_utils_peri_pclk_disable_divider(en_clk_dst_t clk_dest, const cyhal_clock_t *clock)
{
    #if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
    return Cy_SysClk_PeriPclkDisableDivider(clk_dest, _CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel);
    #else
    CY_UNUSED_PARAMETER(clk_dest);
    return Cy_SysClk_PeriphDisableDivider(_CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel);
    #endif
}
static inline cy_rslt_t _cyhal_utils_peri_pclk_enable_phase_align_divider(en_clk_dst_t clk_dest, const cyhal_clock_t *clock, const cyhal_clock_t *clock2)
{
    #if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
    return Cy_SysClk_PeriPclkEnablePhaseAlignDivider(clk_dest, _CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel,
                                                    _CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock2->block), clock2->channel);
    #else
    CY_UNUSED_PARAMETER(clk_dest);
    return Cy_SysClk_PeriphEnablePhaseAlignDivider(_CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel,
                                                   _CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock2->block), clock2->channel);
    #endif
}
static inline bool _cyhal_utils_peri_pclk_is_divider_enabled(en_clk_dst_t clk_dest, const cyhal_clock_t *clock)
{
    #if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
    return Cy_SysClk_PeriPclkGetDividerEnabled(clk_dest, _CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel);
    #elif defined(COMPONENT_CAT2)
    CY_UNUSED_PARAMETER(clk_dest);
    return Cy_SysClk_PeriphDividerIsEnabled(_CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel);
    #else
    CY_UNUSED_PARAMETER(clk_dest);
    return Cy_SysClk_PeriphGetDividerEnabled(_CYHAL_PERIPHERAL_GROUP_GET_DIVIDER_TYPE(clock->block), clock->channel);
    #endif
}

#if defined(__cplusplus)
}
#endif

/** \} group_hal_impl_utils */
/** \} group_hal_impl */
/** \endcond */
