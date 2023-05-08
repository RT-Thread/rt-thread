/*******************************************************************************
* File Name: cyhal_audio_common.h
*
* Description:
* Provides common functionality for the I2S and TDM audio drivers.
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

#include <stdbool.h>
#include <stdint.h>
#include "cyhal_gpio.h"
#include "cyhal_hw_resources.h"

#if (CYHAL_DRIVER_AVAILABLE_I2S || CYHAL_DRIVER_AVAILABLE_TDM)

#if defined(__cplusplus)
extern "C"
{
#endif

/** \cond INTERNAL */

#if (CYHAL_DRIVER_AVAILABLE_TDM_RX || CYHAL_DRIVER_AVAILABLE_I2S_RX)
#define _CYHAL_AUDIOSS_RX_ENABLED
#endif

/* Pins to use for one direction of an audio interface */
typedef struct {
    cyhal_gpio_t sck;   // Clock pin
    cyhal_gpio_t ws;    // Word select
    cyhal_gpio_t data;  // Data pin (sdo or sdi)
    cyhal_gpio_t mclk;  // mclk input (may be NC if unused)
} _cyhal_audioss_pins_t;

/* AUDIOSS Configuration */
typedef struct {
    /* Configure TX to operate a slave (true) or master (false) */
    bool is_tx_slave;
    /* Configure RX to operate a slave (true) or master (false) **/
    bool is_rx_slave;
    /* Frequency, in hertz, of the master clock if it is provided by an external pin.
     * If the mclk pin is not NC, this must be nonzero.
     * If the mclk pin is NC, this must be zero.
     */
    uint32_t mclk_hz;
    /* Number of bits in each channel. See the implementation specific documentation for supported values. **/
    uint8_t channel_length;
    /* Number of bits in each word. Must be less than or equal to channel_length.
     * If word_length < channel_length, the excess bits will be padded with 0's.
     */
    uint8_t word_length;
    /* Sample rate in Hz */
    uint32_t sample_rate_hz;
    /* Number of channels */
    uint8_t num_channels;
    /* Channel enable mask. 1=enabled, 0=disabled */
    uint32_t channel_mask;
    /* false = TX WS pulse is a single SCK cycle. true = TX WS pulse spans a full channel */
    bool tx_ws_full;
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    /* false = RX WS pulse is a single SCK cycle. true = RX WS pulse spans a full channel */
    bool rx_ws_full;
#endif
    /* Is this block being used as I2S. */
    bool is_i2s;
} _cyhal_audioss_config_t;

cy_rslt_t _cyhal_audioss_init(_cyhal_audioss_t *obj, const _cyhal_audioss_pins_t* tx_pins, const _cyhal_audioss_pins_t* rx_pins, const _cyhal_audioss_config_t* config, cyhal_clock_t* clk, const _cyhal_audioss_interface_t* interface);

cy_rslt_t _cyhal_audioss_init_cfg(_cyhal_audioss_t *obj, const _cyhal_audioss_configurator_t *cfg, const _cyhal_audioss_interface_t* interface);

void _cyhal_audioss_free(_cyhal_audioss_t *obj);

cy_rslt_t _cyhal_audioss_set_sample_rate(_cyhal_audioss_t *obj, uint32_t sample_rate_hz);

void _cyhal_audioss_enable_event(_cyhal_audioss_t *obj, uint32_t event, uint8_t intr_priority, bool enable);

cy_rslt_t _cyhal_audioss_start_tx(_cyhal_audioss_t *obj);

cy_rslt_t _cyhal_audioss_stop_tx(_cyhal_audioss_t *obj);

cy_rslt_t _cyhal_audioss_clear_tx(_cyhal_audioss_t *obj);

cy_rslt_t _cyhal_audioss_start_rx(_cyhal_audioss_t *obj);

cy_rslt_t _cyhal_audioss_stop_rx(_cyhal_audioss_t *obj);

cy_rslt_t _cyhal_audioss_clear_rx(_cyhal_audioss_t *obj);

cy_rslt_t _cyhal_audioss_read(_cyhal_audioss_t *obj, void *data, size_t* length);

cy_rslt_t _cyhal_audioss_write(_cyhal_audioss_t *obj, const void *data, size_t *length);

bool _cyhal_audioss_is_tx_enabled(_cyhal_audioss_t *obj);

bool _cyhal_audioss_is_tx_busy(_cyhal_audioss_t *obj);

bool _cyhal_audioss_is_rx_enabled(_cyhal_audioss_t *obj);

bool _cyhal_audioss_is_rx_busy(_cyhal_audioss_t *obj);

cy_rslt_t _cyhal_audioss_read_async(_cyhal_audioss_t *obj, void *rx, size_t rx_length);

cy_rslt_t _cyhal_audioss_write_async(_cyhal_audioss_t *obj, const void *tx, size_t tx_length);

cy_rslt_t _cyhal_audioss_set_async_mode(_cyhal_audioss_t *obj, cyhal_async_mode_t mode, uint8_t dma_priority);

bool _cyhal_audioss_is_read_pending(_cyhal_audioss_t *obj);

bool _cyhal_audioss_is_write_pending(_cyhal_audioss_t *obj);

cy_rslt_t _cyhal_audioss_abort_read_async(_cyhal_audioss_t *obj);

cy_rslt_t _cyhal_audioss_abort_write_async(_cyhal_audioss_t *obj);

cy_rslt_t _cyhal_audioss_enable_output(_cyhal_audioss_t *obj, bool is_rx, cyhal_source_t *source);

cy_rslt_t _cyhal_audioss_disable_output(_cyhal_audioss_t *obj, bool is_rx);

/** \endcond */

#if defined(__cplusplus)
}
#endif

#endif /* CYHAL_DRIVER_AVAILABLE_I2S */
