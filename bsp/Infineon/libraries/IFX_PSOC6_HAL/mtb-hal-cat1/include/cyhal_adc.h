/***************************************************************************//**
* \file cyhal_adc.h
*
* \brief
* Provides a high level interface for interacting with the Infineon Analog to
* Digital Converter. This interface abstracts out the chip specific details.
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
* \addtogroup group_hal_adc ADC (Analog to Digital Converter)
* \ingroup group_hal
* \{
* High level interface for interacting with the analog to digital converter (ADC).
*
* \section cyhal_adc_features Features
* Each ADC instance supports one or more selectable channels, each
* of which can perform conversions on a different pin.
* See the device datasheet for details about which pins support ADC conversion.
*
* Both single-ended and differential channels are supported. The values returned
* by the read API are relative to the ADC's voltage range, which is device specific.
* See the BSP documentation for details.
*
* \section cyhal_adc_quickstart Quickstart
* Call \ref cyhal_adc_init to initialize an ADC instance by providing the ADC
* object (<b>obj</b>), input pin (<b>pin</b>) and clock (<b>clk</b>).<br> The input
* pin argument is just to signify which ADC instance to initialize. It does not
* actually reserve the pin or create an ADC channel for it. The clock parameter can
* be left NULL to use an available clock resource with a default frequency.<br>
* Use \ref cyhal_adc_channel_init_diff to initialize one or more channels associated
* with that instance.<br>
* Use \ref cyhal_adc_read for reading the results.<br>
* See \ref subsection_adc_snippet_1.
*
* \note \ref cyhal_adc_read_u16 always returns a 16 bit value in the range
* 0x0000-0xFFFF. If the underlying hardware does not support 16 bit resolution the
* value is scaled linearly to cover the full 16 bits.
*
* \section subsection_adc_snippets Code snippets
* \note Error checking is omitted for clarity
* \subsection subsection_adc_snippet_1 Snippet 1: Simple ADC initialization and reading conversion result
* The following snippet initializes an ADC and one channel.
* One ADC conversion result is returned corresponding to the input at the specified
* pin.
* \snippet hal_adc.c snippet_cyhal_adc_simple_init
*
* \subsection subsection_adc_snippet_2 Snippet 2: Multi-channel ADC initialization and reading conversion result
* The following snippet initializes an ADC with one single-ended channel and one differential channel
* \snippet hal_adc.c snippet_cyhal_adc_multi_init
*
* \subsection subsection_adc_snippet_3 Snippet 3: Asynchronously read multiple channels
*  The following snippet illustrates how to asynchronously read multiple scans of multiple channels.
* \snippet hal_adc.c snippet_cyhal_adc_async_read
*
* \subsection subsection_adc_snippet_4 Snippet 4: Continuous scanning
*  This snippet shows how to run the ADC in continuous mode and process results as each scan completes.
* \snippet hal_adc.c snippet_cyhal_adc_continuous_read
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"
#include "cyhal_gpio.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_hal_results_adc ADC HAL Results
 *  ADC specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** Bad argument */
#define CYHAL_ADC_RSLT_BAD_ARGUMENT                     \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_ADC, 0))
/** Failed to initialize ADC clock */
#define CYHAL_ADC_RSLT_FAILED_CLOCK                     \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_ADC, 1))
/** Failed to initialize ADC */
#define CYHAL_ADC_RSLT_FAILED_INIT                      \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_ADC, 2))
/** No channels available */
#define CYHAL_ADC_RSLT_NO_CHANNELS                      \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_ADC, 3))

/**
 * \}
 */

/** Number of bits populated with meaningful data by each ADC sample */
#define CYHAL_ADC_BITS 16
/** Maximum value that the ADC can return */
#define CYHAL_ADC_MAX_VALUE ((1 << CYHAL_ADC_BITS) - 1)

/** Possible selections for ADC reference */
typedef enum
{
    CYHAL_ADC_REF_INTERNAL,     //!< Internal reference. See the BSP documentation for the value of this reference. (Default)
    CYHAL_ADC_REF_EXTERNAL,     //!< Reference from external pin.
    CYHAL_ADC_REF_VDDA,         //!< Reference from VDDA (analog supply)
    CYHAL_ADC_REF_VDDA_DIV_2,   //!< Reference from VDDA (analog supply) divided by 2
} cyhal_adc_vref_t;

/** Vminus selection for single-ended channels */
typedef enum
{
    CYHAL_ADC_VNEG_VSSA, //!< Connect vminus to ground.
    CYHAL_ADC_VNEG_VREF, //!< Connect vminus to the selected vref (see @ref cyhal_adc_vref_t)
} cyhal_adc_vneg_t;

/** ADC events */
typedef enum
{
    CYHAL_ADC_EOS = 1u,                  //!< End of scan: a scan of all channels has completed. Only applicable when continuously scanning
    CYHAL_ADC_ASYNC_READ_COMPLETE = 2u,  //!< An asynchronous read operation has completed.
} cyhal_adc_event_t;

/** Selections for ADC input signals  */
typedef enum
{
    CYHAL_ADC_INPUT_START_SCAN, // !< Start a scan when a signal is received
}
cyhal_adc_input_t;

/** Selections for ADC output signals  */
typedef enum
{
    CYHAL_ADC_OUTPUT_SCAN_COMPLETE, // !< An output signal should be triggered when a scan is complete
}
cyhal_adc_output_t;

/** Perform standard averaging. Divide the accumulated value by the number of samples.
  * @note This is not supported in combination with @ref CYHAL_ADC_AVG_MODE_ACCUMULATE */
#define CYHAL_ADC_AVG_MODE_AVERAGE    (1u << 0)
/** Accumulate samples as in @ref CYHAL_ADC_AVG_MODE_AVERAGE, but do not divide by the number of samples */
#define CYHAL_ADC_AVG_MODE_ACCUMULATE (1u << 1)
/** Average mode flag position indices shifted by greater than this are implementation specific. The value
  * of this macro is subject to change between HAL versions. */
#define CYHAL_ADC_AVG_MODE_MAX_SHIFT (1u)

/** Selects the default connection for the inverting input to achieve a single-ended channel. This connection
  * is controlled by the `vneg` member of @ref cyhal_adc_config_t.
  */
#define CYHAL_ADC_VNEG CYHAL_NC_PIN_VALUE

/** ADC Configuration */
typedef struct
{
    /** Whether the ADC samples continuously (true) or only on demand (false).
      *
      * When configured to true, the ADC will immediately begin scanning all configured channels.
      * When configured to false, the ADC will stop continuous scanning at the completion of the current scan
      */
    bool                continuous_scanning;
    /** ADC resolution. See the implementation specific documentation for supported values */
    uint8_t             resolution;
    /** The number of samples that should be averaged together to obtain a result. A value of 1 disables averaging. */
    uint16_t            average_count;
    /** Flags to control the behavior of the averaging functionality when @ref average_count is greater than 1.
      * This field contains zero or more flags that are OR'd together. All implementations define
      * @ref CYHAL_ADC_AVG_MODE_AVERAGE and @ref CYHAL_ADC_AVG_MODE_ACCUMULATE (though some may not support both modes).
      * Some implementations may define other flags to control additional aspects of the averaging functionality; see
      * the implementation-specific documentation for details.
      */
    uint32_t            average_mode_flags;
    /** The external voltage reference value, in millivolts.
      * If vref is set to @ref CYHAL_ADC_REF_EXTERNAL, this must be nonzero.
      * If vref is set to anything other than @ref CYHAL_ADC_REF_EXTERNAL, this must be zero.
      */
    uint32_t            ext_vref_mv;
    /** Vminus selection for single-ended channels */
    cyhal_adc_vneg_t    vneg;
    /** ADC voltage reference */
    cyhal_adc_vref_t    vref;
    /** The GPIO that should be used for the external reference. If @ref CYHAL_ADC_REF_EXTERNAL
      * is selected and the current target uses a GPIO for ADC ext_vref (see the BSP documentation),
      * this must not be @ref NC. If the current target uses a dedicated pin (not a GPIO) for ADC ext_vref,
      * or if any other reference is selected, this must be @ref NC.
      */
    cyhal_gpio_t        ext_vref;
    /** Whether an external bypass capacitor should be used. Depending on the platform this may be required
      * to reduce noise at sufficiently high sample rates. See the implementation specific documentation
      * for details.
      */
    bool                is_bypassed;
    /** The GPIO pin that should be used for the bypass capacitor. If `is_bypassed` is true and the current target
      * uses a GPIO for the bypass capacitor connection, this must not be @ref NC. Otherwise, this must be @ref NC.
      * Depending on the device, this may be the same GPIO as `ext_vref`. See the BSP documentation for details.
      */
    cyhal_gpio_t        bypass_pin;
} cyhal_adc_config_t;

/** ADC Channel Configuration */
typedef struct
{
    /** Whether this channel should be sampled when the ADC performs a scan */
    bool enabled;
    /** Enable or disable averaging for this channel.
      * All other aspects of the averging functionality are configured in @ref cyhal_adc_config_t
      */
    bool enable_averaging;
    /** Minimum time that this channel should be sampled, in nanoseconds. The actual time may be greater
      * than this depending on hardware limitations, the sample rate, and the configuration of other channels.
      * @note While this value is specified in ns, the underlying hardware generally does not support
      * acquisition time with a granularity of 1 ns. See the implementation specific documentation for details.
      */
    uint32_t min_acquisition_ns;
} cyhal_adc_channel_config_t;

/** Handler for ADC event callbacks */
typedef void (*cyhal_adc_event_callback_t)(void *callback_arg, cyhal_adc_event_t event);

/** Initialize ADC peripheral
 *
 * The ADC will be initialized with the following default configuration:
 * - Sample rate: See implementation-specific documentation
 * - Average count: 1 (averaging disabled).
 * - Continuous scanning: false
 * - Single ended vneg: @ref CYHAL_ADC_VNEG_VREF
 * - Vref: @ref CYHAL_ADC_REF_INTERNAL
 * - External vref: @ref NC
 * - Bypassed: false
 * - Bypass pin: @ref NC
 * - Power level: @ref CYHAL_POWER_LEVEL_DEFAULT
 *
 * To change the configuration, see @ref cyhal_adc_configure
 *
 * @param[out] obj  Pointer to an ADC object. The caller must allocate the memory
 *  for this object but the init function will initialize its contents.
 * @param[in]  pin A pin corresponding to the ADC block to initialize
 *  Note: This pin is not reserved, it is just used to identify which ADC block to allocate.
 *  If multiple channels will be allocated for a single ADC instance, only one pin should be
 *  passed here; it does not matter which one. After calling this function once, call
 *  @ref cyhal_adc_channel_init_diff once for each pin whose value should be measured.
 * @param[in]  clk The clock to use can be shared, if not provided a new clock will be allocated
 * @return The status of the init request. \ref CY_RSLT_SUCCESS is returned on success.
 * On failure, a problem specific error code will be returned.
 * This error could be from the HAL or lower level driver.<br>
 * For all other return codes, please refer to device driver documentation available in the BSP landing page
 */
cy_rslt_t cyhal_adc_init(cyhal_adc_t *obj, cyhal_gpio_t pin, const cyhal_clock_t *clk);

/** Initialize the ADC peripheral and its channels using a configurator generated configuration struct
  *
 * @param[out] adc              Pointer to an adc object. The caller must allocate the memory
 *                              for this object but the init function will initialize its contents.
 * @param[out] channels         Array of pointers to ADC channel objects. This array must contain
 *                              a minimum of one (non-null) entry per channel that is enabled by the configurator
 * @param[in,out] num_channels  Length of the `channels` array. If this value is too small for all of the channels
 *                              enabled by the configurator an error will be returned. Will be updated with the
 *                              number of channels that were enabled by the configurator.
 * @param[in] cfg               Configuration structure generated by the configurator.
 * @return The status of the init request
 */
 cy_rslt_t cyhal_adc_init_cfg(cyhal_adc_t *adc, cyhal_adc_channel_t** channels, uint8_t* num_channels,
                                const cyhal_adc_configurator_t *cfg);

/** Uninitialize the ADC peripheral and cyhal_adc_t object
 *
 * @param[in,out] obj The ADC object
 */
void cyhal_adc_free(cyhal_adc_t *obj);

/** Update the ADC configuration.
  *
  * @note If a scan is in progress, this may cause it to be interrupted.
  *
  * @param[in] obj      The ADC object
  * @param[in] config   The configuration to apply
  * @return The status of the configuration request
  * On failure, a problem specific error code will be returned.
  * This error could be from the HAL or lower level driver.<br>
  * For all other return codes, please refer to device driver documentation available in the BSP landing page
  */
cy_rslt_t cyhal_adc_configure(cyhal_adc_t *obj, const cyhal_adc_config_t *config);

/** Changes the current operating power level of the ADC.
 *
 * If the power level is set to @ref CYHAL_POWER_LEVEL_OFF, the ADC will be powered-off
 * but it will retain its configuration, so it is not necessary to reconfigure it when changing
 * the power level from @ref CYHAL_POWER_LEVEL_OFF to any other value.
 *
 * @param[in] obj   ADC object
 * @param[in] power The power level to set
 * @return The status of the set power request
 * On failure, a problem specific error code will be returned.
 * This error could be from the HAL or lower level driver.<br>
 * For all other return codes, please refer to device driver documentation available in the BSP landing page
 */
cy_rslt_t cyhal_adc_set_power(cyhal_adc_t *obj, cyhal_power_level_t power);

/** Configure the number of samples per second.
  *
  * This is the number of times each enabled channel is sampled per second. The total number of samples performed
  *  by the ADC hardware per second is equal to `sample_rate_hz / num_channels_enabled`.
  * Depending on the system clock configuration or limitations of the underlying hardware, it may not be possible
  *  to achieve precisely the desired sample rate. The `achived_sample_rate_hz` parameter will be updated to indicate
  *  the sample rate that was achived.
  * @note The `achieved_sample_rate_hz` value is only valid while the configuration of the ADC and its channels remains
  *  umodified. If @ref cyhal_adc_configure, @ref cyhal_adc_channel_init_diff, @ref cyhal_adc_channel_configure,
  *  or @ref cyhal_adc_channel_free is called, it is necessary to call this function again in order to update the sample rate.
  *  Therefore, it is recommended to call this function after the ADC and all channels have been configured.
  *
  * @param[in]  obj                      The ADC object to configure
  * @param[in]  desired_sample_rate_hz   The desired sample rate, in hertz
  * @param[out] achieved_sample_rate_hz  The achieved sample rate, in hertz
  *
  * @return The status of the sample rate request. Note that inability to exactly match the requested sample
  *  rate is not considered an error. It is the application's responsibility to determine whether the achived rate
  *  is within the tolerance that it requires.
  * \ref CY_RSLT_SUCCESS is returned on success.<br>
  * On failure, a problem specific error code will be returned. This error could be from the HAL or lower level driver.<br>
  * For all other return codes, please refer to device driver documentation available in the BSP landing page
  */
cy_rslt_t cyhal_adc_set_sample_rate(cyhal_adc_t* obj, uint32_t desired_sample_rate_hz, uint32_t* achieved_sample_rate_hz);

/** Initialize a differential ADC channel.
 * @note: Some platforms may restrict which pins can be used as part of a differential pair. See the
 * implementation-specific documentation for details.
 *
 * Configures the pin used by ADC.
 * @param[out] obj      The ADC channel object to initialize
 * @param[in]  adc      The ADC for which the channel should be initialized
 * @param[in]  vplus    Non-inverting input
 * @param[in]  vminus   Inverting input. For a single ended channel, use @ref CYHAL_ADC_VNEG.
 * @param[in]  cfg      The ADC channel configuration
 * @return The status of the init request.
 * On failure, a problem specific error code will be returned.
 * This error could be from the HAL or lower level driver.<br>
 * For all other return codes, please refer to device driver documentation available in the BSP landing page
 */
cy_rslt_t cyhal_adc_channel_init_diff(cyhal_adc_channel_t *obj, cyhal_adc_t* adc, cyhal_gpio_t vplus, cyhal_gpio_t vminus, const cyhal_adc_channel_config_t* cfg);

/** Update the ADC channel configuration.
  *
  * @note If a scan is in progress, this may cause it to be interrupted. It is not valid to change the enabled state
  *  of a channel while an asynchronous read operation is in progress.
  *
  * @param[in] obj      The ADC channel object
  * @param[in] config   The configuration to apply
  * @return The status of the configuration request
  * On failure, a problem specific error code will be returned.
  * This error could be from the HAL or lower level driver.<br>
  * For all other return codes, please refer to device driver documentation available in the BSP landing page
  */
cy_rslt_t cyhal_adc_channel_configure(cyhal_adc_channel_t *obj, const cyhal_adc_channel_config_t *config);

/** Uninitialize the ADC channel and cyhal_adc_channel_t object
 *
 * @param[in,out] obj The ADC channel object
 */
void cyhal_adc_channel_free(cyhal_adc_channel_t *obj);

/** Read the value from the ADC pin, represented as an unsigned 16bit value
 *  where 0x0000 represents the minimum value in the ADC's range, and 0xFFFF
 *  represents the maximum value in the ADC's range.
 * If continous scanning is disabled, this will block while a conversion is
 *   performed on the selected channel, then return the result. Depending on the
 *   ADC speed this function may block for some time.
 * If continuous scanning is enabled, this will return the value from the most
 *   recent conversion of the specified channel (if called shortly after enabling
 *   continuous scanning it may block until at least one conversion has been performed
 *   on this channel).
 *
 * @param[in] obj The ADC object
 * @return An unsigned 16bit value representing the current input voltage
 */
uint16_t cyhal_adc_read_u16(const cyhal_adc_channel_t *obj);

/** Read the value from ADC pin, represented as a 32-bit signed, right-aligned value.
 *
 * This is a 'resolution'-bit value, sign-extended to 32 bits. If the vplus signal is
 *  below the vminus signal, the result will be negative. If the vplus signal is above
 *  the vminus signal, the result will be positive.
 * If continous scanning is disabled, this will block while a conversion is
 *   performed on the selected channel, then return the result. Depending on the
 *   ADC speed this function may block for some time.
 * If continuous scanning is enabled, this will return the value from the most
 *   recent conversion of the specified channel (if called shortly after enabling
 *   continuous scanning it may block until at least one conversion has been performed
 *   on this channel).
 *
 * @param[in] obj The ADC object
 * @return A signed 32 bit value representing the current input voltage
 */
int32_t cyhal_adc_read(const cyhal_adc_channel_t *obj);

/** Read the value from ADC pin, in microvolts.
 *
 * If continous scanning is disabled, this will block while a conversion is
 *   performed on the selected channel, then return the result. Depending on the
 *   ADC speed this function may block for some time.
 * If continuous scanning is enabled, this will return the value from the most
 *   recent conversion of the specified channel (if called shortly after enabling
 *   continuous scanning it may block until at least one conversion has been performed
 *   on this channel).
 *
 * @param[in] obj The ADC object
 * @return An unsigned 32 bit value representing the current input in microvolts
 */
int32_t cyhal_adc_read_uv(const cyhal_adc_channel_t *obj);

/** Scan the specified ADC channels in the background and copy the results
  * into the array pointed to by `result_list`.
  *
  * Results are represented as 32-bit signed, right-aligned values. That is, they are
  *  'resolution'-bit values, sign-extended to 32 bits. If the vplus signal is
  *  below the vminus signal, the result will be negative. If the vplus signal is above
  *  the vminus signal, the result will be positive.
  *
  * If continuous scanning is disabled, this will trigger num_scan new scans and copy the results
  *  into `result_list` once the scan is completed.
  *
  * If continuous scanning is enabled, this will copy the results of num_scan scans into the result_list as
  *  they complete, beginning with the most recently completed scan (if one exists).
  *
  * Scan results are placed sequentially into result_list. That is, result_list will contain all of the results from the
  * first scan, followed by all of the results from the second scan, etc.  If channels exist that are initialized but not
  * enabled, they will consume locations in result_list, but these values are undefined.
  *
  * When the requested number of scans have been completed, the @ref CYHAL_ADC_ASYNC_READ_COMPLETE event will be raised.
  *
  * @ref cyhal_adc_set_async_mode can be used to control whether this uses DMA or a SW (CPU-driven) transfer.
  *
  * @param[in] obj          ADC to read from
  * @param[in] num_scan     The number of scans of each channel that should be read
  * @param[in] result_list  The array where results should be. This must be of length num_scan * initialized_channels,
  *                         where initialized_channels is the number of channels that have been initialized for this ADC
  *                         (and not later freed) via @ref cyhal_adc_channel_init_diff
  * @return The status of the read async request
  * On failure, a problem specific error code will be returned.
  * This error could be from the HAL or lower level driver.<br>
  * For all other return codes, please refer to device driver documentation available in the BSP landing page
  */
cy_rslt_t cyhal_adc_read_async(cyhal_adc_t* obj, size_t num_scan, int32_t* result_list);

/** Scan the specified ADC channels in the background and copy the conversion results in microvolts
  * into the array pointed to by `result_list`.
  *
  * If continuous scanning is disabled, this will trigger num_scan new scans and copy the results
  *  into `result_list` once the scan is completed.
  *
  * If continuous scanning is enabled, this will copy the results of num_scan scans into the result_list as
  *  they complete, beginning with the most recently completed scan (if one exists).
  *
  * Scan results are placed sequentially into result_list. That is, result_list will contain all of the results from the
  * first scan, followed by all of the results from the second scan, etc.  If channels exist that are initialized but not
  * enabled, they will consume locations in result_list, but these values are undefined.
  *
  * When the requested number of scans have been completed, the @ref CYHAL_ADC_ASYNC_READ_COMPLETE event will be raised.
  *
  * @ref cyhal_adc_set_async_mode can be used to control whether this uses DMA or a SW (CPU-driven) transfer.
  *
  * @param[in] obj          ADC to read from
  * @param[in] num_scan     The number of scans of each channel that should be read
  * @param[in] result_list  The array where results should be. This must be of length num_scan * initialized_channels,
  *                         where initialized_channels is the number of channels that have been initialized for this ADC
  *                         (and not later freed) via @ref cyhal_adc_channel_init_diff
  * @return The status of the read async request
  * On failure, a problem specific error code will be returned.
  * This error could be from the HAL or lower level driver.<br>
  * For all other return codes, please refer to device driver documentation available in the BSP landing page
  */
cy_rslt_t cyhal_adc_read_async_uv(cyhal_adc_t* obj, size_t num_scan, int32_t* result_list);

/** Set the mechanism that is used to perform ADC asynchronous transfers. The default is SW.
 *  @warning The effect of calling this function while an async transfer is pending is undefined.
 *
 * @param[in]     obj          The ADC object
 * @param[in]     mode         The transfer mode
 * @param[in]     dma_priority The priority, if DMA is used. Valid values are the same as for @ref cyhal_dma_init.
 *                             If DMA is not selected, the only valid value is CYHAL_DMA_PRIORITY_DEFAULT, and no
                               guarantees are made about prioritization.
 * @return The status of the set mode request
 * On failure, a problem specific error code will be returned.
 * This error could be from the HAL or lower level driver.<br>
 * For all other return codes, please refer to device driver documentation available in the BSP landing page
 */
cy_rslt_t cyhal_adc_set_async_mode(cyhal_adc_t *obj, cyhal_async_mode_t mode, uint8_t dma_priority);

/** Register an ADC callback handler
 *
 * This function will be called when one of the events enabled by \ref cyhal_adc_enable_event occurs.
 *
 * @param[in] obj          The ADC object
 * @param[in] callback     The callback handler which will be invoked when the interrupt fires
 * @param[in] callback_arg Generic argument that will be provided to the callback when called
 */
void cyhal_adc_register_callback(cyhal_adc_t *obj, cyhal_adc_event_callback_t callback, void *callback_arg);

/** Configure ADC events.
 *
 * When an enabled event occurs, the function specified by \ref cyhal_adc_register_callback will be called.
 *
 * @param[in] obj            The ADC object
 * @param[in] event          The ADC event type
 * @param[in] intr_priority  The priority for NVIC interrupt events
 * @param[in] enable         True to turn on specified events, False to turn off
 */
void cyhal_adc_enable_event(cyhal_adc_t *obj, cyhal_adc_event_t event, uint8_t intr_priority, bool enable);

/** Connects a source signal and enables the specified input
 *
 * @param[in] obj          The ADC object
 * @param[in] source       Source signal obtained from another driver's cyhal_<PERIPH>_enable_output
 * @param[in] input        Which input signal to connect to
  * @return The status of the connection
 */
cy_rslt_t cyhal_adc_connect_digital(cyhal_adc_t *obj, cyhal_source_t source, cyhal_adc_input_t input);

/** Enables the specified output signal
 *
 * @param[in]  obj          The ADC object
 * @param[in]  output       Which output signal to enable
 * @param[out] source       Pointer to user-allocated source signal object
 * which will be initialized by enable_output. \p source should be passed to
 * (dis)connect_digital functions to (dis)connect the associated endpoints.
  * @return The status of the output enable
 */
cy_rslt_t cyhal_adc_enable_output(cyhal_adc_t *obj, cyhal_adc_output_t output, cyhal_source_t *source);

/** Disconnect a source signal and disable ADC input
 *
 * @param[in] obj          The ADC object
 * @param[in] source       Source signal from cyhal_<PERIPH>_enable_output to disable
 * @param[in] input        Which input signal to disconnect
  * @return The status of the disconnect
 */
cy_rslt_t cyhal_adc_disconnect_digital(cyhal_adc_t *obj, cyhal_source_t source, cyhal_adc_input_t input);

/** Disables specified output signal from ADC.
 *
 * @param[in]  obj          The ADC object
 * @param[in]  output       Which output signal to disable
  * @return The status of the disablement
 */
cy_rslt_t cyhal_adc_disable_output(cyhal_adc_t *obj, cyhal_adc_output_t output);

#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_ADC_IMPL_HEADER
#include CYHAL_ADC_IMPL_HEADER
#endif /* CYHAL_ADC_IMPL_HEADER */

/** \} group_hal_adc */
