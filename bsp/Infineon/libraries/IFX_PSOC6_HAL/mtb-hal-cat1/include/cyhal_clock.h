/*******************************************************************************
* File Name: cyhal_clock.h
*
* Description:
* Provides a high level interface for interacting with the Clocks on the device.
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
* \addtogroup group_hal_clock Clock
* \ingroup group_hal
* \{
* Interface for getting and changing clock configuration.
*
* The clock driver is a single API designed to allow reading and configuring
* any clock in the system. The driver works the same to configure System clocks
* as it does for Peripheral clocks. It supports both a readonly mode where any
* number of items can get information about the clock. Alternatively, each
* clock can have a single owner that is able to adjust the configuration of the
* clock.
*
* This driver supports source clocks, clock dividers, and clock signal muxes.
* All clock objects support the get() functions. Only some clocks support
* setting specific attributes. Use the \ref cyhal_clock_get_features() function
* to determine which features are settable for a specific clock. Calling a set()
* function on a clock that does not support it will return an error.
*
* This driver makes no assumptions about how the device is currently configured.
* It can be used from a completely unconfigured system (eg: device just booted)
* to a fully pre-configured (eg: setup by the Device Configurator). The drivers
* query and modify the actual state of the hardware, there is no caching or
* remembering of state. To maximize portability of code, it is often convenient
* to place all system clock configuration into a Board Support Package (BSP) so
* the main application code is flexible and can port between devices.
*
* All System Clock instances are available as constant variables in the
* implementation specific header. These clocks can be used directly to call
* any get() function. Similarly, \ref cyhal_clock_get allows for getting
* access to a specific clock object given a resource instance. Like the
* constant variables, this clock reference can be used to call any of the
* get() functions at any time. If a clock needs to be modified, either
* \ref cyhal_clock_allocate or \ref cyhal_clock_reserve must be called to
* obtain a lock on the clock object and to ensure that nothing else in the
* application is currently using it or assuming its configuration is stable.
* If exclusive control of a clock is no longer needed \ref cyhal_clock_free
* can be called to release it. This will remove the lock allowing something
* else in the system to potentially modify its state.
*
* \ref cyhal_clock_reserve and \ref cyhal_clock_allocate are very similar. They
* both reserve a clock object that can then be modified. The difference between
* them is the argument that is passed in. \ref cyhal_clock_reserve takes a
* specific instance that it will attempt to reserve. \ref cyhal_clock_allocate
* takes in a type of clock that it will attempt to find a free instance for and
* reserve that.
*
* \note After calling \ref cyhal_clock_free the clock object can still be used
* to call any of the get() functions just as is possible from the instance
* returned by \ref cyhal_clock_get or using any of the constant clock variables.
*
* \note A clock only needs to be allocated ( \ref cyhal_clock_allocate ) or
* reserved ( \ref cyhal_clock_reserve ) if its configuration needs to be changed
* by calling one of the set() functions.
*
* \note While the API is generic, the specific clock resource instances
* (\ref cyhal_resource_inst_t) are device specific. See the implementation
* specific sections for more details on what clocks and hardware resources are
* available.
*
* \section section_clock_features Features
* * Queryable clock features
* * Configurable clock enablement
* * Configurable clock frequency/divider
* * Configurable clock sources
* * Reserve or share clock objects
*
* \section section_clock_quickstart Quick Start
*
* See \ref subsection_clock_snippet_1 for a code snippet that shows how to reserve
* and configure a clock object.
*
* \section section_clock_snippets Code snippets
* \note Error handling code has been intentionally left out of snippets to highlight API usage.
*
* \subsection subsection_clock_snippet_1 Snippet 1: Simple clock read only access
* The following snippet shows how get details about a clock if there is no need to adjust any of its
* settings (e.g. read only access). This does not require initializing a clock object.
* \snippet hal_clock.c snippet_cyhal_clock_simple_access
*
* \subsection subsection_clock_snippet_2 Snippet 2: Simple clock reservation and configuration
* The following snippet initializes a clock object, updates its frequency then enables it.
* \snippet hal_clock.c snippet_cyhal_clock_simple_init
*
* \subsection subsection_clock_snippet_3 Snippet 3: Clock allocation and reuse
* The following snippet shows how a clock can be allocated and reused for multiple peripheral instances.
* \snippet hal_clock.c snippet_cyhal_clock_simple_allocate
*
* \subsection subsection_clock_snippet_4 Snippet 4: Change clock source
* The following snippet shows how a to change the source of a clock.
* \snippet hal_clock.c snippet_cyhal_clock_change_source
*
* \subsection subsection_clock_snippet_5 Snippet 5: System initialization
* \note This example is device specific. See \ref subsection_clock_snippet_5_impl for specific implementation.
*
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/** \addtogroup group_hal_results_clock Clock HAL Results
 *  Clock specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */


/** Error configuring clock frequency, divider, or multiplier. */
#define CYHAL_CLOCK_RSLT_ERR_FREQ               \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_CLOCK, 0))
/** Invalid source clock. */
#define CYHAL_CLOCK_RSLT_ERR_SOURCE             \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_CLOCK, 1))
/** Specified operation is not supported by the current clock. */
#define CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED      \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_CLOCK, 2))
/** The specified resource is not valid. */
#define CYHAL_CLOCK_RSLT_ERR_RESOURCE           \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_CLOCK, 3))
/** The clock did not lock after being enabled. */
#define CYHAL_CLOCK_RSLT_ERR_LOCK               \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_CLOCK, 4))

/**
 * \}
 */

/** \addtogroup group_hal_tolerance
 *  \{ *//**
 *  \{ @name Clock Tolerance
 */

/** Clock tolerance 0 percent */
extern const cyhal_clock_tolerance_t CYHAL_CLOCK_TOLERANCE_0_P;
/** Clock tolerance 1 percent */
extern const cyhal_clock_tolerance_t CYHAL_CLOCK_TOLERANCE_1_P;
/** Clock tolerance 5 percent */
extern const cyhal_clock_tolerance_t CYHAL_CLOCK_TOLERANCE_5_P;

/**
 * \} \}
 */

/** Enum defining the different features each clock can support of clocks. These are bit masks.
 * These can be used to determine which set() APIs are legal for a particular clock. */
typedef enum
{
    CYHAL_CLOCK_FEATURE_NONE =       (0),       //!< No features of the clock are configurable.
    CYHAL_CLOCK_FEATURE_ENABLE =     (1 << 0),  //!< The clock can be enabled & disabled \ref cyhal_clock_set_enabled.
    CYHAL_CLOCK_FEATURE_FREQUENCY =  (1 << 1),  //!< The clock frequency can be adjusted \ref cyhal_clock_set_frequency.
    CYHAL_CLOCK_FEATURE_DIVIDER =    (1 << 2),  //!< The clock divider can be adjusted \ref cyhal_clock_set_divider.
    // Not available on any supported device yet.
//  CYHAL_CLOCK_FEATURE_MULTIPLIER = (1 << 3),  //!< The clock multiplier can be adjusted \ref  cyhal_clock_set_multiplier.
    CYHAL_CLOCK_FEATURE_SOURCE =     (1 << 4),  //!< The clock source can be adjusted \ref cyhal_clock_set_source.
} cyhal_clock_feature_t;


/** Get a Clock instance for readonly use. This clock object can be used to call
 * any of the get() functions. To call any of the set() functions, \ref
 * cyhal_clock_reserve must be called to get exclusive access to the clock object
 * to allow it to be modified.
 *
 * @param[out] clock    The clock object to store the initialized data into. The
 * caller must allocate the memory for this object but the init function will
 * initialize its contents.
 * @param[in]  resource The clock resource instance to initialize.
 * @return The status of the get request. This will only return an error if the provided
 * resource instance is not a valid clock object.
 */
cy_rslt_t cyhal_clock_get(cyhal_clock_t *clock, const cyhal_resource_inst_t *resource);

/** Reserves the specified Clock instance.
 * Once the clock has been reserved the get() and set() functions can be used. If
 * at any time the clock is no longer needed, it can be released by calling
 * \ref cyhal_clock_free.
 * \note This does not change the clock configuration or connections.
 *
 * @param[out] clock        The clock object to initialize. The caller must allocate
 * the memory for this object but the init function will initialize its contents.
 * @param[in]  clock_       The constant clock object to reserve
 * @return The status of the reserve request.
 */
cy_rslt_t cyhal_clock_reserve(cyhal_clock_t *clock, const cyhal_clock_t *clock_);

/** Allocates and Reserves a Clock instance, of the provided block type, for use.
 * This should be used when needing a specific type of clock but the exact instance
 * does not matter. This does everything that is done by \ref cyhal_clock_reserve.
 * Once the clock has been allocated the get() and set() functions can be used. If
 * at any time the clock is no longer needed, it can be released by calling
 * \ref cyhal_clock_free.
 * \note This does not change the clock configuration or connections.
 * \note This is generally only supported for clock blocks that have multiple instances
 *
 * @param[out] clock        The clock object to initialize. The caller must allocate
 * the memory for this object but the init function will initialize its contents.
 * @param[in]  block        The specific type of clock to allocate
 * @return The status of the allocate request.
 */
cy_rslt_t cyhal_clock_allocate(cyhal_clock_t *clock, cyhal_clock_block_t block);

/** Gets the features supported by the specified clock. This can be used to determine which
 * set() APIs are legal to be called for this clock.
 *
 * @param[in] clock The clock object to get features for.
 * @return The feature set that can be configured by this clock. Features are bit mask values.
 */
cyhal_clock_feature_t cyhal_clock_get_features(const cyhal_clock_t *clock);

/** Gets whether the specified clock is currently enabled and locked, if appropriate. While
 * most clocks simply have an enabled state, Crystals, PLL, and a few others may also check
 * to make sure the clock has locked and is stable before returning true.
 *
 * \note External clocks which cannot be enabled/disabled directly will return true
 * if a frequency has been set for them, and false otherwise
 *
 * @param[in] clock The clock object to check if it is enabled.
 * @return Whether the specified clock is enabled or not.
 */
bool cyhal_clock_is_enabled(const cyhal_clock_t *clock);

/** Attempts to update the enablement of the specified clock. This is only legal to call
 * if the \ref cyhal_clock_get_features API indicates support for \ref CYHAL_CLOCK_FEATURE_ENABLE.
 *
 * \note \ref cyhal_clock_allocate or \ref cyhal_clock_reserve must be called on the <b>clock</b>
 * instance before using this function.
 *
 * \note If disabled, any clocks or peripherals that are using this will stop working. Make sure
 * to switch the clock source (\ref cyhal_clock_set_source) of any downstream clocks if necessary
 * to keep them running prior to disabling their source.
 *
 * @param[in] clock         The clock object to update the enablement of.
 * @param[in] enabled       Whether the clock should be enabled (true) or disabled (false).
 * @param[in] wait_for_lock Whether to wait for the clock to enable & lock (true), or just send
 *                          the request and return (false). Most clocks behave the same either
 *                          way, however Crystals, PLLs, and similar require time to lock. If
 *                          false, \ref cyhal_clock_is_enabled needs to be used to check that
 *                          it is running before using the clock.
 * @return The status of the requested to change the clocks enablement.
 */
cy_rslt_t cyhal_clock_set_enabled(cyhal_clock_t *clock, bool enabled, bool wait_for_lock);

/** Gets the frequency (in Hz) the clock is currently operating at.
 *
 * @param[in] clock    The clock object to get the frequency of.
 * @return The frequency the clock is currently running at. 0 if the clock is disabled.
 */
uint32_t cyhal_clock_get_frequency(const cyhal_clock_t *clock);

/** Attempts to update the operating frequency of the clock. This is only legal to call
 * if the \ref cyhal_clock_get_features API indicates support for \ref CYHAL_CLOCK_FEATURE_FREQUENCY.
 *
 * \note \ref cyhal_clock_allocate or \ref cyhal_clock_reserve must be called on the <b>clock</b>
 * instance before using this function.
 *
 * \note Some clocks (eg: FLLs & PLLs) may need to be stopped before their frequency can
 * be changed. This function will take care of disabling & re-enabling as necessary, however,
 * this can cause a temporary glitch on anything that is running off of the clock at the time.
 * If glitch free operation is required, change the source of any downstream clocks the
 * application before changing the clock frequency.
 *
 * @param[in] clock     The clock object to set the frequency for.
 * @param[in] hz        The frequency, in hertz, to set the clock to.
 * @param[in] tolerance The allowed tolerance from the desired hz that is acceptable, use NULL if no
 *                      tolerance check is required.
 * @return The status of the request to set the clock frequency.
 */
cy_rslt_t cyhal_clock_set_frequency(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance);

/** Attempts to update the divider, and by extension the operating frequency, of the clock. This is only
 * legal to call if the \ref cyhal_clock_get_features API indicates support for
 * \ref CYHAL_CLOCK_FEATURE_DIVIDER.
 *
 * \note \ref cyhal_clock_allocate or \ref cyhal_clock_reserve must be called on the <b>clock</b>
 * instance before using this function.
 *
 * @param[in] clock     The clock object to set the divider for.
 * @param[in] divider   The divider value to use.
 * @return The status of the request to set the clock divider.
 */
cy_rslt_t cyhal_clock_set_divider(cyhal_clock_t *clock, uint32_t divider);

/** Gets the clocks that can serve as inputs to the current clock.
 *
 * @param[in]  clock    The clock object to get legal sources for.
 * @param[out] sources  The sources that are legal for the current clock.
 *                      \note the array does not need to be allocated before calling this
 *                      the pointer will be updated to point to an existing const array.
 * @param[out] count    The number of clock sources contained in the <b>sources</b> variable.
 * @return The status of the request to get clock sources.
 */
cy_rslt_t cyhal_clock_get_sources(const cyhal_clock_t *clock, const cyhal_resource_inst_t **sources[], uint32_t *count);

/** Attempts to update the source for the specified clock. This is only legal to call if the
 * \ref cyhal_clock_get_features API indicates support for \ref CYHAL_CLOCK_FEATURE_SOURCE.
 *
 * \note \ref cyhal_clock_allocate or \ref cyhal_clock_reserve must be called on the <b>clock</b>
 * instance before using this function.
 *
 * \note Some clocks (eg: FLLs & PLLs) may need to be stopped before their source can be changed.
 * This function will take care of disabling & re-enabling as necessary, however, this can cause
 * a temporary glitch on anything that is running off of the clock at the time. If glitch free
 * operation is required, change the source for any downstream clocks in the application before
 * changing the source clock.
 *
 * \note No checking is done to verify that the source clock is running. This needs to be done
 * by the caller.
 *
 * @param[in] clock     The clock object to set a new source for.
 * @param[in] source    The source clock to update to.
 * @return The status of the request to set the source of the clock
 */
cy_rslt_t cyhal_clock_set_source(cyhal_clock_t *clock, const cyhal_clock_t *source);

/** Releases the exclusive lock the clock. This instance can no longer be used to with any set()
 * functions. It can still be used for readonly access to Clock APIs just like is possible after
 * calling \ref cyhal_clock_get.
 *
 * \note This does not change the behavior (e.g.: enablement) of the clock.
 *
 * @param[in,out] clock The clock object to free
 */
void cyhal_clock_free(cyhal_clock_t *clock);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_CLOCK_IMPL_HEADER
#include CYHAL_CLOCK_IMPL_HEADER
#endif /* CYHAL_CLOCK_IMPL_HEADER */

/** \} group_hal_clock */
