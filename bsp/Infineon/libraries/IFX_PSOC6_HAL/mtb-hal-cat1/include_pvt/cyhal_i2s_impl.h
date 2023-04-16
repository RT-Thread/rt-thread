/***************************************************************************//**
* \file cyhal_i2s_impl.h
*
* Description:
* Provides a high level interface for interacting with the Infineon I2S. This is
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

#include "cyhal_audio_common.h"

#if (CYHAL_DRIVER_AVAILABLE_I2S)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#define cyhal_i2s_free(obj) (_cyhal_audioss_free((_cyhal_audioss_t *)(obj)))

#define cyhal_i2s_set_sample_rate(obj, sample_rate_hz) \
    _cyhal_audioss_set_sample_rate((_cyhal_audioss_t *)(obj), (sample_rate_hz))

#define cyhal_i2s_enable_event(obj, event, intr_priority, enable) \
    _cyhal_audioss_enable_event((_cyhal_audioss_t *)(obj), (uint32_t)(event), (intr_priority), (enable))

#define cyhal_i2s_start_tx(obj) _cyhal_audioss_start_tx((_cyhal_audioss_t *)(obj))
#define cyhal_i2s_stop_tx(obj) _cyhal_audioss_stop_tx((_cyhal_audioss_t *)(obj))
#define cyhal_i2s_clear_tx(obj) _cyhal_audioss_clear_tx((_cyhal_audioss_t *)(obj))

#define cyhal_i2s_start_rx(obj) _cyhal_audioss_start_rx((_cyhal_audioss_t *)(obj))
#define cyhal_i2s_stop_rx(obj) _cyhal_audioss_stop_rx((_cyhal_audioss_t *)(obj))
#define cyhal_i2s_clear_rx(obj) _cyhal_audioss_clear_rx((_cyhal_audioss_t *)(obj))

#define cyhal_i2s_read(obj, data,  length) \
    _cyhal_audioss_read((_cyhal_audioss_t *)obj, data, length)

#define cyhal_i2s_write(obj, data, length) \
    _cyhal_audioss_write((_cyhal_audioss_t *)obj, data, length)

#define cyhal_i2s_is_tx_enabled(obj) _cyhal_audioss_is_tx_enabled((_cyhal_audioss_t *)(obj))
#define cyhal_i2s_is_tx_busy(obj) _cyhal_audioss_is_tx_busy((_cyhal_audioss_t *)(obj))

#define cyhal_i2s_is_rx_enabled(obj) _cyhal_audioss_is_rx_enabled((_cyhal_audioss_t *)(obj))
#define cyhal_i2s_is_rx_busy(obj) _cyhal_audioss_is_rx_busy((_cyhal_audioss_t *)(obj))

#define cyhal_i2s_read_async(obj, rx, rx_length) \
    _cyhal_audioss_read_async((_cyhal_audioss_t *)(obj), (rx), (rx_length))

#define cyhal_i2s_write_async(obj, tx, tx_length) \
    _cyhal_audioss_write_async((_cyhal_audioss_t *)(obj), (tx), (tx_length))

#define cyhal_i2s_set_async_mode(obj, mode, dma_priority) \
    _cyhal_audioss_set_async_mode((_cyhal_audioss_t *)(obj), (mode), (dma_priority))

#define cyhal_i2s_is_read_pending(obj) _cyhal_audioss_is_read_pending((_cyhal_audioss_t *)(obj))
#define cyhal_i2s_is_write_pending(obj) _cyhal_audioss_is_write_pending((_cyhal_audioss_t *)(obj))

#define cyhal_i2s_abort_read_async(obj) _cyhal_audioss_abort_read_async((_cyhal_audioss_t *)(obj))
#define cyhal_i2s_abort_write_async(obj) _cyhal_audioss_abort_write_async((_cyhal_audioss_t *)(obj))

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* CYHAL_DRIVER_AVAILABLE_I2S */
