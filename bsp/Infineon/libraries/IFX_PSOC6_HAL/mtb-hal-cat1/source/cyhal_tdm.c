/*******************************************************************************
* File Name: cyhal_tdm.c
*
* Description:
* Provides a high level interface for interacting with the Infineon TDM. This is
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

#include "cyhal_tdm.h"
#include "cyhal_audio_common.h"
#include "cyhal_system.h"

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
/**
* \addtogroup group_hal_impl_tdm TDM (Time Division Multiplexing)
* \ingroup group_hal_impl
* \{
* The CAT1 (PSoC™ 6) TDM Supports the following values for word lengths:
* - 8 bits
* - 10 bits (CAT1B only)
* - 12 bits (CAT1B only)
* - 14 bits (CAT1B only)
* - 16 bits
* - 18 bits
* - 20 bits
* - 24 bits
* - 32 bits
*
* On CAT1A devices, the only supported channel length is 32 bits. On CAT1B devices, the channel
* length may be any value greater than or equal to the word length and less than or equal to 32 bits.
*
* On CAT1A devices, up to 8 channels are supported.
* On CAT1B devices, the number of supported channels is specified by the `TDM_NR<n>_CH_NR` macros.
* Disabling channels (so that they are included in the sequencing but ignored) is only supported
* on CAT1B devices.
*
* The sclk signal is formed by integer division of the input clock source (either internally
* provided or from the mclk pin). The CAT1A TDM supports sclk divider values from 1 to 64. On
* CAT1B devices, the TDM supports sclk divider values from 2 to 256.
* On CAT1A devices, if both RX and TX are used, the same GPIO must be specified for
* mclk in both directions. See the device datasheet for more details on valid pin selections.
*
* The following events are not supported on CAT1B:
* - \ref CYHAL_TDM_TX_EMPTY
* - \ref CYHAL_TDM_TX_NOT_FULL
* - \ref CYHAL_TDM_RX_FULL
* - \ref CYHAL_TDM_RX_NOT_EMPTY
*
* \note If the TDM hardware is initialized with a configurator-generated configuration via the
* @ref cyhal_tdm_init_cfg function, the @ref CYHAL_TDM_TX_HALF_EMPTY and @ref CYHAL_TDM_RX_HALF_FULL
* events will be raised at the configurator defined TX and RX FIFO trigger levels, respectively,
* instead of their usual trigger level of half the FIFO depth.
*
* \} group_hal_impl_tdm
*/
#elif defined(COMPONENT_CAT2)
/**
* \addtogroup group_hal_impl_tdm TDM (Time Division Multiplexing)
* \ingroup group_hal_impl
* \{
*
* The CAT2 (PSoC™ 4) TDM only supports TX in master mode.
*
* There are no trigger connections available from the TDM peripheral to other peripherals on
* the CAT2 platform. Hence, the \ref cyhal_tdm_enable_output and \ref cyhal_tdm_disable_output
* are not supported on this platform.
*
* It supports the following values for word lengths:
* - 8 bits
* - 16 bits
* - 18 bits
* - 20 bits
* - 24 bits
* - 32 bits
*
* The channel length must be greater than or equal to the word length. On CAT2 devices, the
* set of supported channel lengths is the same as the set of supported word lengths.
*
* The sclk signal is formed by integer division of the input clock source (either internally
* provided or from the mclk pin). The CAT2 TDM supports sclk divider values from 1 to 64.

* \note If the TDM hardware is initialized with a configurator-generated configuration via the
* @ref cyhal_tdm_init_cfg function, the @ref CYHAL_TDM_TX_HALF_EMPTY event will be raised at the
* configurator defined TX FIFO trigger level instead of the usual trigger level of half the FIFO depth.
*
* \} group_hal_impl_tdm
*/
#endif

#if (CYHAL_DRIVER_AVAILABLE_TDM)

#if defined(__cplusplus)
extern "C"
{
#endif

#if defined(CY_IP_MXAUDIOSS)
static uint32_t _cyhal_tdm_convert_interrupt_cause(uint32_t pdl_cause);
static uint32_t _cyhal_tdm_convert_event(uint32_t event);
#elif defined(CY_IP_MXTDM)
static uint32_t _cyhal_tdm_convert_interrupt_cause(uint32_t pdl_cause, bool is_tx);
static uint32_t _cyhal_tdm_convert_event(uint32_t event, bool is_tx);
#endif

static void _cyhal_tdm_invoke_callback(_cyhal_audioss_t* obj, uint32_t event);

static const _cyhal_audioss_interface_t _cyhal_tdm_interface =
{
    .convert_interrupt_cause = _cyhal_tdm_convert_interrupt_cause,
    .convert_to_pdl = _cyhal_tdm_convert_event,
    .invoke_user_callback = _cyhal_tdm_invoke_callback,
    .event_mask_empty = CYHAL_TDM_TX_EMPTY,
    .event_mask_half_empty = CYHAL_TDM_TX_HALF_EMPTY,
#if (CYHAL_DRIVER_AVAILABLE_TDM_RX)
    .event_mask_full = CYHAL_TDM_RX_FULL,
    .event_mask_half_full = CYHAL_TDM_RX_HALF_FULL,
    .event_rx_complete = CYHAL_TDM_ASYNC_RX_COMPLETE,
#endif
    .event_tx_complete = CYHAL_TDM_ASYNC_TX_COMPLETE,
    .err_invalid_pin = CYHAL_TDM_RSLT_ERR_INVALID_PIN,
    .err_invalid_arg = CYHAL_TDM_RSLT_ERR_INVALID_ARG,
    .err_clock = CYHAL_TDM_RSLT_ERR_CLOCK,
    .err_not_supported = CYHAL_TDM_RSLT_NOT_SUPPORTED,
};

cy_rslt_t cyhal_tdm_init(cyhal_tdm_t *obj, const cyhal_tdm_pins_t* tx_pins, const cyhal_tdm_pins_t* rx_pins,
                         const cyhal_tdm_config_t* config, cyhal_clock_t* clk)
{
    _cyhal_audioss_pins_t rx_converted, tx_converted;
    _cyhal_audioss_pins_t* rx_pin_ptr = NULL;
    _cyhal_audioss_pins_t* tx_pin_ptr = NULL;
    if(NULL != rx_pins)
    {
        rx_converted.sck = rx_pins->sck;
        rx_converted.ws = rx_pins->ws;
        rx_converted.data = rx_pins->data;
        rx_converted.mclk = rx_pins->mclk;
        rx_pin_ptr = &rx_converted;
    }

    if(NULL != tx_pins)
    {
        tx_converted.sck = tx_pins->sck;
        tx_converted.ws = tx_pins->ws;
        tx_converted.data = tx_pins->data;
        tx_converted.mclk = tx_pins->mclk;
        tx_pin_ptr = &tx_converted;
    }

    _cyhal_audioss_config_t converted_config =
    {
        .is_tx_slave    = config->is_tx_slave,
        .is_rx_slave    = config->is_rx_slave,
        .mclk_hz        = config->mclk_hz,
        .channel_length = config->channel_length,
        .word_length    = config->word_length,
        .sample_rate_hz = config->sample_rate_hz,
        .num_channels   = config->num_channels,
        .channel_mask   = config->channel_mask,
        .tx_ws_full     = (config->tx_ws_width == CYHAL_TDM_WS_FULL),
#if (CYHAL_DRIVER_AVAILABLE_TDM_RX)
        .rx_ws_full     = (config->rx_ws_width == CYHAL_TDM_WS_FULL),
#endif
        .is_i2s         = false
    };

    return _cyhal_audioss_init((_cyhal_audioss_t *)obj, tx_pin_ptr, rx_pin_ptr, &converted_config, clk, &_cyhal_tdm_interface);
}

cy_rslt_t cyhal_tdm_init_cfg(cyhal_tdm_t *obj, const cyhal_tdm_configurator_t *cfg)
{
    return _cyhal_audioss_init_cfg((_cyhal_audioss_t *)obj, cfg, &_cyhal_tdm_interface);
}

void cyhal_tdm_register_callback(cyhal_tdm_t *obj, cyhal_tdm_event_callback_t callback, void *callback_arg)
{
    CY_ASSERT(NULL != obj);

    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    obj->callback_data.callback = (cy_israddress) callback;
    obj->callback_data.callback_arg = callback_arg;
    cyhal_system_critical_section_exit(savedIntrStatus);
}

#if defined(CY_IP_MXAUDIOSS)
static uint32_t _cyhal_tdm_convert_interrupt_cause(uint32_t pdl_cause)
{
    cyhal_tdm_event_t result = (cyhal_tdm_event_t)0u;
    if(0 != (pdl_cause & CY_I2S_INTR_TX_NOT_FULL))
    {
        result |= CYHAL_TDM_TX_NOT_FULL;
    }
    if(0 != (pdl_cause & CY_I2S_INTR_TX_TRIGGER))
    {
        result |= CYHAL_TDM_TX_HALF_EMPTY;
    }
    if(0 != (pdl_cause & CY_I2S_INTR_TX_EMPTY))
    {
        result |= CYHAL_TDM_TX_EMPTY;
    }
    if(0 != (pdl_cause & CY_I2S_INTR_TX_OVERFLOW))
    {
        result |= CYHAL_TDM_TX_OVERFLOW;
    }
    if(0 != (pdl_cause & CY_I2S_INTR_TX_UNDERFLOW))
    {
        result |= CYHAL_TDM_TX_UNDERFLOW ;
    }
#if (CYHAL_DRIVER_AVAILABLE_TDM_RX)
    if(0 != (pdl_cause & CY_I2S_INTR_RX_NOT_EMPTY))
    {
        result |= CYHAL_TDM_RX_NOT_EMPTY;
    }
    if(0 != (pdl_cause & CY_I2S_INTR_RX_TRIGGER))
    {
        result |= CYHAL_TDM_RX_HALF_FULL;
    }
    if(0 != (pdl_cause & CY_I2S_INTR_RX_FULL))
    {
        result |= CYHAL_TDM_RX_FULL;
    }
    if(0 != (pdl_cause & CY_I2S_INTR_RX_OVERFLOW))
    {
        result |= CYHAL_TDM_RX_OVERFLOW;
    }
    if(0 != (pdl_cause & CY_I2S_INTR_RX_UNDERFLOW))
    {
        result |= CYHAL_TDM_RX_UNDERFLOW;
    }
#endif

    return (uint32_t)result;
}

static uint32_t _cyhal_tdm_convert_event(uint32_t event)
{
    cyhal_tdm_event_t hal_event = (cyhal_tdm_event_t)event;
    uint32_t pdl_event = 0u;
    if(0 != (hal_event & CYHAL_TDM_TX_NOT_FULL))
    {
        pdl_event |= CY_I2S_INTR_TX_NOT_FULL;
    }
    if(0 != (hal_event & CYHAL_TDM_TX_HALF_EMPTY))
    {
        pdl_event |= CY_I2S_INTR_TX_TRIGGER;
    }
    if(0 != (hal_event & CYHAL_TDM_TX_EMPTY))
    {
        pdl_event |= CY_I2S_INTR_TX_EMPTY;
    }
    if(0 != (hal_event & CYHAL_TDM_TX_OVERFLOW))
    {
        pdl_event |= CY_I2S_INTR_TX_OVERFLOW;
    }
    if(0 != (hal_event & CYHAL_TDM_TX_UNDERFLOW ))
    {
        pdl_event |= CY_I2S_INTR_TX_UNDERFLOW;
    }
#if (CYHAL_DRIVER_AVAILABLE_TDM_RX)
    if(0 != (hal_event & CYHAL_TDM_RX_NOT_EMPTY))
    {
        pdl_event |= CY_I2S_INTR_RX_NOT_EMPTY;
    }
    if(0 != (hal_event & CYHAL_TDM_RX_HALF_FULL))
    {
        pdl_event |= CY_I2S_INTR_RX_TRIGGER;
    }
    if(0 != (hal_event & CYHAL_TDM_RX_FULL))
    {
        pdl_event |= CY_I2S_INTR_RX_FULL;
    }
    if(0 != (hal_event & CYHAL_TDM_RX_OVERFLOW))
    {
        pdl_event |= CY_I2S_INTR_RX_OVERFLOW;
    }
    if(0 != (hal_event & CYHAL_TDM_RX_UNDERFLOW))
    {
        pdl_event |= CY_I2S_INTR_RX_UNDERFLOW;
    }
#endif
    return pdl_event;
}
#elif defined(CY_IP_MXTDM)
static uint32_t _cyhal_tdm_convert_event(uint32_t event, bool is_tx)
{
    cyhal_tdm_event_t hal_event = (cyhal_tdm_event_t)event;
    uint32_t pdl_event = 0u;
    if(is_tx)
    {
        /* Full/empty related interrupts not supported by this IP:
         * * CYHAL_TDM_TX_NOT_FULL
         * * CYHAL_TDM_TX_EMPTY
         */
        if(0 != (hal_event & CYHAL_TDM_TX_HALF_EMPTY))
        {
            pdl_event |= CY_TDM_INTR_TX_FIFO_TRIGGER;
        }
        if(0 != (hal_event & CYHAL_TDM_TX_OVERFLOW))
        {
            pdl_event |= CY_TDM_INTR_TX_FIFO_OVERFLOW;
        }
        if(0 != (hal_event & CYHAL_TDM_TX_UNDERFLOW ))
        {
            pdl_event |= CY_TDM_INTR_TX_FIFO_UNDERFLOW;
        }
    }
    else
    {
        /* Full/empty related interrupts not supported by this IP:
         * * CYHAL_TDM_RX_NOT_FULL
         * * CYHAL_TDM_RX_EMPTY
         */
        if(0 != (hal_event & CYHAL_TDM_RX_HALF_FULL))
        {
            pdl_event |= CY_TDM_INTR_RX_FIFO_TRIGGER;
        }
        if(0 != (hal_event & CYHAL_TDM_RX_OVERFLOW))
        {
            pdl_event |= CY_TDM_INTR_RX_FIFO_OVERFLOW;
        }
        if(0 != (hal_event & CYHAL_TDM_RX_UNDERFLOW ))
        {
            pdl_event |= CY_TDM_INTR_RX_FIFO_UNDERFLOW;
        }
    }

    return pdl_event;
}

static uint32_t _cyhal_tdm_convert_interrupt_cause(uint32_t pdl_cause, bool is_tx)
{
    cyhal_tdm_event_t result = (cyhal_tdm_event_t)0u;
    if(is_tx)
    {
        /* Full/empty related interrupts not supported by this IP:
         * * CYHAL_TDM_TX_NOT_FULL
         * * CYHAL_TDM_TX_EMPTY
         */
        if(0 != (pdl_cause & CY_TDM_INTR_TX_FIFO_TRIGGER))
        {
            result |= CYHAL_TDM_TX_HALF_EMPTY;
        }
        if(0 != (pdl_cause & CY_TDM_INTR_TX_FIFO_OVERFLOW))
        {
            result |= CYHAL_TDM_TX_OVERFLOW;
        }
        if(0 != (pdl_cause & CY_TDM_INTR_TX_FIFO_UNDERFLOW))
        {
            result |= CYHAL_TDM_TX_UNDERFLOW;
        }
    }
    else
    {
        /* Full/empty related interrupts not supported by this IP:
         * * CYHAL_TDM_RX_NOT_FULL
         * * CYHAL_TDM_RX_EMPTY
         */
        if(0 != (pdl_cause & CY_TDM_INTR_RX_FIFO_TRIGGER))
        {
            result |= CYHAL_TDM_RX_HALF_FULL;
        }
        if(0 != (pdl_cause & CY_TDM_INTR_RX_FIFO_OVERFLOW))
        {
            result |= CYHAL_TDM_RX_OVERFLOW;
        }
        if(0 != (pdl_cause & CY_TDM_INTR_RX_FIFO_UNDERFLOW))
        {
            result |= CYHAL_TDM_RX_UNDERFLOW;
        }
    }

    return result;
}
#endif

static void _cyhal_tdm_invoke_callback(_cyhal_audioss_t* obj, uint32_t event)
{
    cyhal_tdm_event_callback_t callback = (cyhal_tdm_event_callback_t)obj->callback_data.callback;
    if(NULL != callback)
    {
        callback(obj->callback_data.callback_arg, (cyhal_tdm_event_t)event);
    }
}

cy_rslt_t cyhal_tdm_enable_output(cyhal_tdm_t *obj, cyhal_tdm_output_t output, cyhal_source_t *source)
{
    CY_ASSERT(CYHAL_TDM_TRIGGER_RX_HALF_FULL == output || CYHAL_TDM_TRIGGER_TX_HALF_EMPTY == output);
    bool is_rx = CYHAL_TDM_TRIGGER_RX_HALF_FULL == output;
    return _cyhal_audioss_enable_output(obj, is_rx, source);
}

cy_rslt_t cyhal_tdm_disable_output(cyhal_tdm_t *obj, cyhal_tdm_output_t output)
{
    CY_ASSERT(CYHAL_TDM_TRIGGER_RX_HALF_FULL == output || CYHAL_TDM_TRIGGER_TX_HALF_EMPTY == output);
    bool is_rx = CYHAL_TDM_TRIGGER_RX_HALF_FULL == output;
    return _cyhal_audioss_disable_output(obj, is_rx);
}

#if defined(__cplusplus)
}
#endif

#endif /* CYHAL_DRIVER_AVAILABLE_TDM */
