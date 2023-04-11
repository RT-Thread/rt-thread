/***************************************************************************//**
* \file cyhal_spi.c
*
* \brief
* Provides a high level interface for interacting with the Infineon SPI. This is
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

/**
 * \addtogroup group_hal_impl_spi SPI (Serial Peripheral Interface)
 * \ingroup group_hal_impl
 * \{
 * \section section_hal_impl_spi_init_cfg Configurator-generated features limitations
 * List of SPI personality items, which are currently not supported in SPI HAL driver on CAT1/CAT2 devices:
 *  - Modes: TI (Start Coincides), TI (Start Precedes), National Semiconductor (Microwire)
 *  - Low-level RX Interrupt sources
 *  - Low-level TX Interrupt sources
 *  - SPI Done Master interrupt source
 *  - Different data width for RX and TX
 *
 * \section section_hal_impl_spi_data_width Supported transfer data width options
 * Next transfer data width options are supported by next devices:
 *  - CAT1 devices with MXSCB block version 2 and further (value of CY_IP_MXSCB_VERSION) support next data width range: 4 - 32 (included) with step 1
 *  - CAT1 devices with MXSCB block version 1 (value of CY_IP_MXSCB_VERSION) support next data width range: 4 - 16 (included) with step 1
 *  - CAT2 devices support next data width range : 4-16 (included) with step 1
 *
 * \} group_hal_impl_spi
 */

#include <stdlib.h>
#include <string.h>
#include "cyhal_spi.h"
#include "cyhal_scb_common.h"
#include "cyhal_gpio.h"
#include "cyhal_system_impl.h"
#include "cyhal_hwmgr.h"
#include "cyhal_system.h"
#include "cyhal_syspm.h"
#include "cyhal_clock.h"
#include "cyhal_irq_impl.h"

#if (CYHAL_DRIVER_AVAILABLE_SPI)

#if defined(__cplusplus)
extern "C"
{
#endif

#define _CYHAL_SPI_DEFAULT_SPEED            100000

#define _CYHAL_SPI_WAIT_OP_RD_BUSY          1
#define _CYHAL_SPI_WAIT_OP_RD_NOT_BUSY      2
#define _CYHAL_SPI_WAIT_OP_WR               3
#define _CYHAL_SPI_WAIT_OP_VALID(op)        ((op) > 0 && (op) <= _CYHAL_SPI_WAIT_OP_WR)

#define _CYHAL_SPI_OVERSAMPLE_MIN           4
#define _CYHAL_SPI_OVERSAMPLE_MAX           16
#define _CYHAL_SPI_SSEL_NUM                 4

#define _CYHAL_SPI_PENDING_NONE             0
#define _CYHAL_SPI_PENDING_RX               1
#define _CYHAL_SPI_PENDING_TX               2
#define _CYHAL_SPI_PENDING_TX_RX            3

#define _CYHAL_SPI_SSEL_ACTIVATE            true
#define _CYHAL_SPI_SSEL_DEACTIVATE          false


/* Default SPI configuration */
static const cy_stc_scb_spi_config_t _cyhal_spi_default_config =
{
    .spiMode                  = CY_SCB_SPI_MASTER,
    .subMode                  = CY_SCB_SPI_MOTOROLA,
    .sclkMode                 = CY_SCB_SPI_CPHA0_CPOL0,
#if defined (COMPONENT_CAT2) || (CY_IP_MXSCB_VERSION >= 3) || (CY_IP_MXS22SCB_VERSION >= 1)
    .parity                   = CY_SCB_SPI_PARITY_NONE,
    .dropOnParityError        = false,
#endif /* defined (COMPONENT_CAT2) || (CY_IP_MXSCB_VERSION >= 3) */
    .oversample               = _CYHAL_SPI_OVERSAMPLE_MIN,
    .rxDataWidth              = 8,
    .txDataWidth              = 8,
    .enableMsbFirst           = true,
    .enableFreeRunSclk        = false,
    .enableInputFilter        = false,
#if (CY_IP_MXSCB_VERSION >= 3) || (CY_IP_MXS22SCB_VERSION >= 1)
    /* Setting this to true leads to incorrect slave communication */
    .enableMisoLateSample     = false,
#else
    .enableMisoLateSample     = true,
#endif
    .enableTransferSeperation = false,
    .enableWakeFromSleep      = false,
    .ssPolarity               = CY_SCB_SPI_ACTIVE_LOW,
#if defined (COMPONENT_CAT2) || (CY_IP_MXSCB_VERSION >= 3) || (CY_IP_MXS22SCB_VERSION >= 1)
    .ssSetupDelay             = false,
    .ssHoldDelay              = false,
#endif /* defined (COMPONENT_CAT2) || (CY_IP_MXSCB_VERSION >= 3) || (CY_IP_MXS22SCB_VERSION >= 1) */
#if defined (COMPONENT_CAT1) && ((CY_IP_MXSCB_VERSION >= 3) || (CY_IP_MXS22SCB_VERSION >= 1))
    .ssInterFrameDelay        = false,
#elif defined (COMPONENT_CAT2)
    .ssInterDataframeDelay    = false,
#endif /* defined (COMPONENT_CAT1) && ((CY_IP_MXSCB_VERSION >= 3) || (CY_IP_MXS22SCB_VERSION >= 1)) or defined (COMPONENT_CAT2) */
    .rxFifoTriggerLevel       = 0,
    .rxFifoIntEnableMask      = 0,
    .txFifoTriggerLevel       = 0,
    .txFifoIntEnableMask      = 0,
    .masterSlaveIntEnableMask = 0
};

/* The PDL clears the IRQ status during Cy_SCB_SPI_Interrupt which prevents _cyhal_scb_get_irq_obj()
 * from working properly in _cyhal_spi_cb_wrapper on devices with muxed IRQs, because they can't tell
 * at that point which system IRQ caused the CPU IRQ. So we need to save this value at the beginning of the
 * IRQ handler when we are able to determine what it is */
static volatile cyhal_spi_t* _cyhal_spi_irq_obj = NULL;

static void _cyhal_ssel_switch_state(cyhal_spi_t *obj, uint8_t ssel_idx, bool ssel_activate);

static cy_rslt_t _cyhal_spi_int_frequency(cyhal_spi_t *obj, uint32_t hz, uint8_t *over_sample_val)
{
    CY_ASSERT(NULL != obj);
    cy_rslt_t result = CY_RSLT_SUCCESS;
    uint8_t oversample_value;
    uint32_t divider_value;
    uint32_t last_diff = 0xFFFFFFFFU;
    uint8_t last_ovrsmpl_val = 0;
    uint32_t last_dvdr_val = 0;
    uint32_t oversampled_freq = 0;
    uint32_t divided_freq = 0;
    uint32_t diff = 0;

    _cyhal_utils_peri_pclk_disable_divider(_cyhal_scb_get_clock_index(obj->resource.block_num), &(obj->clock));

    uint32_t peri_freq = _cyhal_utils_get_peripheral_clock_frequency(&(obj->resource));
    if (!obj->is_slave)
    {
        for (oversample_value = _CYHAL_SPI_OVERSAMPLE_MIN; oversample_value <= _CYHAL_SPI_OVERSAMPLE_MAX; oversample_value++)
        {
            oversampled_freq = hz * oversample_value;
            if ((hz * oversample_value > peri_freq) && (_CYHAL_SPI_OVERSAMPLE_MIN == oversample_value))
            {
                return CYHAL_SPI_RSLT_CLOCK_ERROR;
            }
            else if (hz * oversample_value > peri_freq)
            {
                continue;
            }

            divider_value = _cyhal_utils_divider_value(&(obj->resource), hz * oversample_value, 0);
            divided_freq = peri_freq / divider_value;
            diff = (oversampled_freq > divided_freq)
                ? oversampled_freq - divided_freq
                : divided_freq - oversampled_freq;

            if (diff < last_diff)
            {
                last_diff = diff;
                last_ovrsmpl_val = oversample_value;
                last_dvdr_val = divider_value;
                if (0 == diff)
                {
                    break;
                }
            }
        }
        *over_sample_val = last_ovrsmpl_val;
    }
    else
    {
        /* Slave requires such frequency: required_frequency = N / ((0.5 * desired_period) â€“ 20 nsec - tDSI,
        *   N is 3 when "Enable Input Glitch Filter" is false and 4 when true.
        *   tDSI Is external master delay which is assumed to be 16.66 nsec */

        /* Divided by 2 desired period to avoid dividing in required_frequency formula */
        float desired_period_us_divided = 5e5f * (1 / (float)hz);
        uint32_t required_frequency = (uint32_t)(3e6f / (desired_period_us_divided - 36.66f / 1e3f));

        if (required_frequency > peri_freq)
        {
            return CYHAL_SPI_RSLT_CLOCK_ERROR;
        }

        /* Use maximum available clock for slave to make it able to work with any master environment */
        last_dvdr_val = 1;
        last_ovrsmpl_val = 1;
    }

#if defined (COMPONENT_CAT5)
    CY_UNUSED_PARAMETER(last_dvdr_val);
    result = _cyhal_utils_peri_pclk_set_freq(_cyhal_scb_get_clock_index(obj->resource.block_num), &(obj->clock), hz, last_ovrsmpl_val);
#else
    result = _cyhal_utils_peri_pclk_set_divider(_cyhal_scb_get_clock_index(obj->resource.block_num), &(obj->clock), last_dvdr_val - 1);
#endif
    if (CY_RSLT_SUCCESS == result)
    {
        _cyhal_utils_peri_pclk_enable_divider(_cyhal_scb_get_clock_index(obj->resource.block_num), &(obj->clock));
    }

    return result;
}

static inline cyhal_spi_event_t _cyhal_spi_convert_interrupt_cause(uint32_t pdl_cause)
{
    static const uint32_t status_map[] =
    {
        (uint32_t)CYHAL_SPI_IRQ_ERROR,         // Default error if unknown value is set
        (uint32_t)CYHAL_SPI_IRQ_DATA_IN_FIFO,  // CY_SCB_SPI_TRANSFER_IN_FIFO_EVENT
        (uint32_t)CYHAL_SPI_IRQ_DONE,          // CY_SCB_SPI_TRANSFER_CMPLT_EVENT
        (uint32_t)CYHAL_SPI_IRQ_ERROR,         // CY_SCB_SPI_TRANSFER_ERR_EVENT
    };
    return (cyhal_spi_event_t)_cyhal_utils_convert_flags(status_map, sizeof(status_map) / sizeof(uint32_t), pdl_cause);
}

#if defined (COMPONENT_CAT5)
static void _cyhal_spi_irq_handler(_cyhal_system_irq_t irqn)
#else
static void _cyhal_spi_irq_handler(void)
#endif
{
    /* Save the old value and store it aftewards in case we get into a nested IRQ situation */
    /* Safe to cast away volatile because we don't expect this pointer to be changed while we're in here, they
     * just might change where the original pointer points */
    cyhal_spi_t* old_irq_obj = (cyhal_spi_t*)_cyhal_spi_irq_obj;
#if defined (COMPONENT_CAT5)
    _cyhal_spi_irq_obj = (cyhal_spi_t*) _cyhal_scb_get_irq_obj(irqn);
#else
    _cyhal_spi_irq_obj = (cyhal_spi_t*) _cyhal_scb_get_irq_obj();
#endif
    cyhal_spi_t* obj = (cyhal_spi_t*)_cyhal_spi_irq_obj;

    if (NULL == obj)
    {
        return;
    }

    Cy_SCB_SPI_Interrupt(obj->base, &(obj->context));

    if (!obj->is_async)
    {
        return;
    }

    if (0 == (Cy_SCB_SPI_GetTransferStatus(obj->base, &obj->context) & CY_SCB_SPI_TRANSFER_ACTIVE))
    {
        if (NULL != obj->tx_buffer)
        {
            /* Start TX Transfer */
            obj->pending = _CYHAL_SPI_PENDING_TX;
            const uint8_t *buf = obj->tx_buffer;
            obj->tx_buffer = NULL;

            Cy_SCB_SPI_Transfer(obj->base, (uint8_t *)buf, NULL, obj->tx_buffer_size, &obj->context);
        }
        else if (NULL != obj->rx_buffer)
        {
            /* Start RX Transfer */
            obj->pending = _CYHAL_SPI_PENDING_RX;
            uint8_t *rx_buf = obj->rx_buffer;
            uint8_t *tx_buf;
            size_t trx_size = obj->rx_buffer_size;

            if (obj->rx_buffer_size > 1)
            {
                 /* In this case we don't have a transmit buffer; we only have a receive buffer. While the PDL
                 * is fine with passing NULL for transmit, we don't get to control what data it is sending in
                 * that case, which we allowed the user to set. To honor the user's request, we reuse the rx
                 * buffer as the tx buffer too. We set all bytes beyond the one we will start filling in with
                 * the user provided 'write_fill'. This means the tx buffer is 1 element smaller than the rx
                 * buffer. As a result, we must therefore transfer 1 less element then we really want to in
                 * this transfer. When this transfer is complete, it will call into this again to receive the
                 * final element.
                 */
                trx_size -= 1; // Transfer everything left except for the last byte

                uint8_t **rx_buffer_p = (uint8_t **) &obj->rx_buffer;

                tx_buf = *rx_buffer_p + 1; // Start at second byte to avoid trying to transmit and receive the same byte
                memset(tx_buf, obj->write_fill, trx_size);

                *rx_buffer_p += trx_size; // Move to 1 byte before end
                obj->rx_buffer_size = 1; // Transfer the last byte on the next interrupt
            }
            else
            {
                tx_buf = &obj->write_fill;

                obj->rx_buffer = NULL;
            }

            Cy_SCB_SPI_Transfer(obj->base, tx_buf, rx_buf, trx_size, &obj->context);
        }
        else
        {
            /* Finish Async Transfer */
            obj->pending = _CYHAL_SPI_PENDING_NONE;
            obj->is_async = false;
            _cyhal_ssel_switch_state(obj, obj->active_ssel, _CYHAL_SPI_SSEL_DEACTIVATE);
        }
    }

    _cyhal_spi_irq_obj = old_irq_obj;
}

#if defined (COMPONENT_CAT5)
static void _cyhal_spi0_irq_handler(void)
{
    _cyhal_spi_irq_handler(scb_0_interrupt_IRQn);
}

static void _cyhal_spi1_irq_handler(void)
{
    _cyhal_spi_irq_handler(scb_1_interrupt_IRQn);
}

static void _cyhal_spi2_irq_handler(void)
{
    _cyhal_spi_irq_handler(scb_2_interrupt_IRQn);
}

static CY_SCB_IRQ_THREAD_CB_t _cyhal_irq_cb[3] = {_cyhal_spi0_irq_handler, _cyhal_spi1_irq_handler, _cyhal_spi2_irq_handler};
#endif

static void _cyhal_spi_cb_wrapper(uint32_t event)
{
    /* Safe to cast away volatile because we don't expect this pointer to be changed while we're in here, they
     * just might change where the original pointer points */
    cyhal_spi_t *obj = (cyhal_spi_t*)_cyhal_spi_irq_obj;
    cyhal_spi_event_t anded_events = (cyhal_spi_event_t) (obj->irq_cause & (uint32_t) _cyhal_spi_convert_interrupt_cause(event));

    // Don't call the callback until the final transfer has put everything in the FIFO/completed
    if ((anded_events & (CYHAL_SPI_IRQ_DATA_IN_FIFO | CYHAL_SPI_IRQ_DONE)) && !(obj->rx_buffer == NULL && obj->tx_buffer == NULL))
    {
        return;
    }

    if (anded_events)
    {
        /* Indicates read/write operations will be in a callback */
        obj->op_in_callback = true;
        cyhal_spi_event_callback_t callback = (cyhal_spi_event_callback_t) obj->callback_data.callback;
        callback(obj->callback_data.callback_arg, anded_events);
        obj->op_in_callback = false;
    }
}

static cy_en_scb_spi_sclk_mode_t _cyhal_convert_mode_sclk(cyhal_spi_mode_t mode)
{
    uint8_t sclk_mode = (mode & (CYHAL_SPI_MODE_FLAG_CPOL | CYHAL_SPI_MODE_FLAG_CPHA));

    switch (sclk_mode)
    {
        case CYHAL_SPI_MODE_FLAG_CPOL | CYHAL_SPI_MODE_FLAG_CPHA:
            return (CY_SCB_SPI_CPHA1_CPOL1);
        case CYHAL_SPI_MODE_FLAG_CPOL:
            return (CY_SCB_SPI_CPHA0_CPOL1);
        case CYHAL_SPI_MODE_FLAG_CPHA:
            return (CY_SCB_SPI_CPHA1_CPOL0);
        default:
            return (CY_SCB_SPI_CPHA0_CPOL0);
    }
}

static inline bool _is_cyhal_mode_msb(cyhal_spi_mode_t mode)
{
    return ((mode & CYHAL_SPI_MODE_FLAG_LSB) != CYHAL_SPI_MODE_FLAG_LSB);
}

static cyhal_spi_mode_t _cyhal_spi_mode_pdl_to_hal(const cy_stc_scb_spi_config_t *pdl_cfg)
{
    cy_en_scb_spi_sclk_mode_t clk_mode = pdl_cfg->sclkMode;
    return (cyhal_spi_mode_t)(CYHAL_SPI_MODE(
        ((uint8_t)((clk_mode == CY_SCB_SPI_CPHA0_CPOL1) || (clk_mode == CY_SCB_SPI_CPHA1_CPOL1))),
        ((uint8_t)((clk_mode == CY_SCB_SPI_CPHA1_CPOL0) || (clk_mode == CY_SCB_SPI_CPHA1_CPOL1))),
        ((uint8_t) !pdl_cfg->enableMsbFirst)));
}

static bool _cyhal_spi_pm_callback_instance(void *obj_ptr, cyhal_syspm_callback_state_t state, cy_en_syspm_callback_mode_t pdl_mode)
{
    cyhal_spi_t *obj = (cyhal_spi_t *)obj_ptr;
    bool allow = true;
    cy_stc_syspm_callback_params_t spi_callback_params = {
        .base = (void *) (obj->base),
        .context = (void *) &(obj->context)
    };

    if (CYHAL_SYSPM_CB_CPU_DEEPSLEEP == state)
        allow = (CY_SYSPM_SUCCESS == Cy_SCB_SPI_DeepSleepCallback(&spi_callback_params, pdl_mode));
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D)
    else if (CYHAL_SYSPM_CB_SYSTEM_HIBERNATE == state)
        allow = (CY_SYSPM_SUCCESS == Cy_SCB_SPI_HibernateCallback(&spi_callback_params, pdl_mode));
#endif

    return allow;
}

static cy_rslt_t _cyhal_spi_get_ssel_map_idx(cyhal_gpio_t ssel, const cyhal_resource_pin_mapping_t **ssel_map,
                    uint8_t *idx, const cyhal_resource_inst_t *target_blk)
{
    static const cyhal_resource_pin_mapping_t *ssel_s_pin_maps[] = {
    #if defined(CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT0)
        cyhal_pin_map_scb_spi_s_select0,
    #endif
    #if defined(CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT1)
        cyhal_pin_map_scb_spi_s_select1,
    #endif
    #if defined(CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT2)
        cyhal_pin_map_scb_spi_s_select2,
    #endif
    #if defined(CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT3)
        cyhal_pin_map_scb_spi_s_select3
    #endif
    };
    static const size_t ssel_s_pin_maps_sizes_bytes[] = {
    #if defined(CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT0)
        sizeof(cyhal_pin_map_scb_spi_s_select0),
    #endif
    #if defined(CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT1)
        sizeof(cyhal_pin_map_scb_spi_s_select1),
    #endif
    #if defined(CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT2)
        sizeof(cyhal_pin_map_scb_spi_s_select2),
    #endif
    #if defined(CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT3)
        sizeof(cyhal_pin_map_scb_spi_s_select3)
    #endif
    };

    for (uint8_t i = 0; i < sizeof(ssel_s_pin_maps) / sizeof(ssel_s_pin_maps[0]); i++)
    {
        *ssel_map = _cyhal_scb_find_map(ssel, ssel_s_pin_maps[i],
                        ssel_s_pin_maps_sizes_bytes[i] / sizeof(cyhal_resource_pin_mapping_t), target_blk);
        if (NULL != *ssel_map)
        {
            *idx = i;
            return CY_RSLT_SUCCESS;
        }
    }
    return CYHAL_SPI_RSLT_ERR_CANNOT_CONFIG_SSEL;
}

static inline cy_en_scb_spi_polarity_t _cyhal_spi_pol_from_hal_to_pdl(cyhal_spi_ssel_polarity_t hal_polarity)
{
    return (hal_polarity == CYHAL_SPI_SSEL_ACTIVE_HIGH) ? CY_SCB_SPI_ACTIVE_HIGH : CY_SCB_SPI_ACTIVE_LOW;
}

static cy_rslt_t _cyhal_spi_ssel_config(cyhal_spi_t *obj, cyhal_gpio_t ssel,
                                        cyhal_spi_ssel_polarity_t polarity, bool reserve_n_connect)
{
    cy_rslt_t result = CYHAL_SPI_RSLT_ERR_CANNOT_CONFIG_SSEL;
    uint8_t found_idx = 0;
    bool configuring_existing = false;
    if ((NC != ssel) && (_CYHAL_SPI_PENDING_NONE == obj->pending))
    {
        for (uint8_t i = 0; i < _CYHAL_SPI_SSEL_NUM; i++)
        {
            if ((configuring_existing = (ssel == obj->pin_ssel[i])))
            {
                result = CY_RSLT_SUCCESS;
                found_idx = i;
                break;
            }
            if (!obj->is_slave)
            {
                /* Looking for first available ssel slot */
                if ((NC == obj->pin_ssel[i]))
                {
                    result = reserve_n_connect ? cyhal_gpio_init(ssel, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG,
                                (polarity == CYHAL_SPI_SSEL_ACTIVE_LOW) ? true : false) : CY_RSLT_SUCCESS;
                    found_idx = i;
                    break;
                }
            }
        }
        if (!configuring_existing && (obj->is_slave))
        {
            const cyhal_resource_pin_mapping_t *ssel_map = NULL;
            if (CY_RSLT_SUCCESS == _cyhal_spi_get_ssel_map_idx(ssel, &ssel_map, &found_idx, &(obj->resource)))
            {
                /* Either mosi or miso should present. Will take one of them as instance SCB instance index source */
                const cyhal_resource_pin_mapping_t *data_pin_map = (NC != obj->pin_mosi)
                    ? _CYHAL_SCB_FIND_MAP_BLOCK(obj->pin_mosi, cyhal_pin_map_scb_spi_s_mosi, &(obj->resource))
                    : _CYHAL_SCB_FIND_MAP_BLOCK(obj->pin_miso, cyhal_pin_map_scb_spi_s_miso, &(obj->resource));

                if ((NULL != ssel_map) && (NC == obj->pin_ssel[found_idx]) &&
                    _cyhal_utils_map_resources_equal(data_pin_map, ssel_map))
                {
                    result = reserve_n_connect
                        ? _cyhal_utils_reserve_and_connect(ssel_map, (uint8_t)CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT0)
                        : CY_RSLT_SUCCESS;
                }
            }
        }
        if (CY_RSLT_SUCCESS == result)
        {
            if (!configuring_existing)
                obj->pin_ssel[found_idx] = ssel;
            obj->ssel_pol[found_idx] = _cyhal_spi_pol_from_hal_to_pdl(polarity);

            /* Immediately apply updated slave select polarity */
            Cy_SCB_SPI_SetActiveSlaveSelectPolarity(obj->base, (cy_en_scb_spi_slave_select_t)found_idx, obj->ssel_pol[found_idx]);
            if (!obj->is_slave)
            {
                _cyhal_ssel_switch_state(obj, found_idx, _CYHAL_SPI_SSEL_DEACTIVATE);
            }
        }
    }
    return result;
}

/* Wait untill SPI is busy for some time (timeout > 0) or no wait (timeout == 0). */
static cy_rslt_t _cyhal_spi_wait_for_op(cyhal_spi_t *obj, uint8_t op, uint32_t* timeout)
{
    CY_ASSERT(_CYHAL_SPI_WAIT_OP_VALID(op));

    cy_rslt_t result = CY_RSLT_SUCCESS;
    uint32_t timeout_us = _CYHAL_UTILS_US_PER_MS;
    bool op_condition = true;

    if (!(obj->op_in_callback) && *timeout > 0)
    {
        while (op_condition && *timeout > 0)
        {
            switch (op)
            {
                case _CYHAL_SPI_WAIT_OP_RD_BUSY:
                    op_condition = (cyhal_spi_readable(obj) == 0 && !cyhal_spi_is_busy(obj));
                    break;
                case _CYHAL_SPI_WAIT_OP_RD_NOT_BUSY:
                    op_condition = (cyhal_spi_readable(obj) == 0 || cyhal_spi_is_busy(obj));
                    break;
                case _CYHAL_SPI_WAIT_OP_WR:
                    op_condition = ((cyhal_spi_writable(obj) < Cy_SCB_GetFifoSize(obj->base)) || cyhal_spi_is_busy(obj));
                    break;
                default:
                    op_condition = false;
                    break;
            }

            if (timeout_us > 0)
            {
                cyhal_system_delay_us(_CYHAL_UTILS_ONE_TIME_UNIT);
                --timeout_us;
            }
            else
            {
                timeout_us = _CYHAL_UTILS_US_PER_MS;
                (*timeout)--;
            }
        }
        result = (*timeout > 0) ? CY_RSLT_SUCCESS : CYHAL_SPI_RSLT_WARN_TIMEOUT;
    }
    return result;
}

static cy_rslt_t _cyhal_spi_setup_resources(cyhal_spi_t *obj, const cyhal_spi_configurator_t *cfg)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;

    cyhal_gpio_t ssel = NC;
    cyhal_gpio_t sclk = cfg->gpios.sclk;
    cyhal_gpio_t mosi = cfg->gpios.mosi;
    cyhal_gpio_t miso = cfg->gpios.miso;

    for (size_t ssel_idx = 0; ssel_idx < sizeof(cfg->gpios.ssel) / sizeof(cfg->gpios.ssel[0]); ++ssel_idx)
    {
        if (NC != cfg->gpios.ssel[ssel_idx])
        {
            ssel = cfg->gpios.ssel[ssel_idx];
            obj->active_ssel = ssel_idx;
            break;
        }
    }

    /* Validate pins configuration. Mandatory pins:*/
    /* Master mode: MOSI pin used, MISO unused:     SCLK, SSEL are optional */
    /* Master mode: MISO pin used, MOSI unused:     SCLK is mandatory, MOSI, SSEL are optional */
    /* Slave  mode: MOSI or MISO are used:          SCLK and SSEL are mandatory */

    /* Slave */
    if (obj->is_slave)
    {
        if ((NC == sclk) || (NC == ssel) || ((NC == mosi) && (NC == miso)))
        {
            return CYHAL_SPI_RSLT_PIN_CONFIG_NOT_SUPPORTED;
        }
    }
    /* Master */
    else
    {
        if ((NC != miso && NC == sclk) || (NC == mosi && NC == miso))
        {
            return CYHAL_SPI_RSLT_PIN_CONFIG_NOT_SUPPORTED;
        }
    }

    uint32_t saved_intr_status = cyhal_system_critical_section_enter();

    // pins_blocks will contain bit representation of blocks, that are connected to specified pin
    // 1 block - 1 bit, so, for example, pin_blocks = 0x00000006 means that certain pin
    // can belong to next non-reserved blocks SCB2 and SCB1
    uint32_t pins_blocks = _CYHAL_SCB_AVAILABLE_BLOCKS_MASK;
    uint8_t found_block_idx = 0;
    if (false == obj->dc_configured)
    {
        if (obj->is_slave)
        {
            if (NC != sclk)
            {
                pins_blocks &= _CYHAL_SCB_CHECK_AFFILIATION(sclk, cyhal_pin_map_scb_spi_s_clk);
            }
            if (NC != miso)
            {
                pins_blocks &= _CYHAL_SCB_CHECK_AFFILIATION(miso, cyhal_pin_map_scb_spi_s_miso);
            }
            if (NC != mosi)
            {
                pins_blocks &= _CYHAL_SCB_CHECK_AFFILIATION(mosi, cyhal_pin_map_scb_spi_s_mosi);
            }
            if (NC != ssel)
            {
                uint32_t ss_pins_blocks = 0;

            #ifdef CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT0
                ss_pins_blocks |= _CYHAL_SCB_CHECK_AFFILIATION(ssel, cyhal_pin_map_scb_spi_s_select0);
            #endif /* (CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT0) */

            #ifdef CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT1
                ss_pins_blocks |= _CYHAL_SCB_CHECK_AFFILIATION(ssel, cyhal_pin_map_scb_spi_s_select1);
            #endif /* (CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT1) */

            #ifdef CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT2
                ss_pins_blocks |= _CYHAL_SCB_CHECK_AFFILIATION(ssel, cyhal_pin_map_scb_spi_s_select2);
            #endif /* (CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT2) */

            #ifdef CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT3
                ss_pins_blocks |= _CYHAL_SCB_CHECK_AFFILIATION(ssel, cyhal_pin_map_scb_spi_s_select3);
            #endif /* (CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_SELECT3) */

                pins_blocks &= ss_pins_blocks;
            }
        }
        else
        {
            if (NC != sclk)
            {
                pins_blocks &= _CYHAL_SCB_CHECK_AFFILIATION(sclk, cyhal_pin_map_scb_spi_m_clk);
            }
            if (NC != miso)
            {
                pins_blocks &= _CYHAL_SCB_CHECK_AFFILIATION(miso, cyhal_pin_map_scb_spi_m_miso);
            }
            if (NC != mosi)
            {
                pins_blocks &= _CYHAL_SCB_CHECK_AFFILIATION(mosi, cyhal_pin_map_scb_spi_m_mosi);
            }
            /* No need to check SSEL for SPI master as the SS pin can be any */
        }

        if (0 == pins_blocks)
        {
            // One (or more) pin does not belong to any SCB instance or all corresponding SCB instances
            // are reserved
            result = CYHAL_SPI_RSLT_ERR_INVALID_PIN;
        }
        else
        {
            while(((pins_blocks >> found_block_idx) & 0x1) == 0)
            {
                found_block_idx++;
            }
        }
    }

    /* Get pin configurations */
    const cyhal_resource_pin_mapping_t *mosi_map = NULL;
    const cyhal_resource_pin_mapping_t *miso_map = NULL;
    const cyhal_resource_pin_mapping_t *sclk_map = NULL;
    const cyhal_resource_pin_mapping_t *ssel_map = NULL;
    uint8_t mosi_dm = 0, miso_dm = 0, sclk_dm = 0;

    const cyhal_resource_inst_t default_spi_inst = { CYHAL_RSC_SCB, found_block_idx, 0 };
    const cyhal_resource_inst_t* spi_inst_p = (obj->dc_configured)
        ? cfg->resource
        : &default_spi_inst;

    if (CY_RSLT_SUCCESS == result)
    {
        if (obj->is_slave)
        {
            mosi_map = _CYHAL_SCB_FIND_MAP_BLOCK(mosi, cyhal_pin_map_scb_spi_s_mosi, spi_inst_p);
            miso_map = _CYHAL_SCB_FIND_MAP_BLOCK(miso, cyhal_pin_map_scb_spi_s_miso, spi_inst_p);
            sclk_map = _CYHAL_SCB_FIND_MAP_BLOCK(sclk, cyhal_pin_map_scb_spi_s_clk, spi_inst_p);
            mosi_dm = (uint8_t)CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_MOSI;
            miso_dm = (uint8_t)CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_MISO;
            sclk_dm = (uint8_t)CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_S_CLK;
            result = _cyhal_spi_get_ssel_map_idx(ssel, &ssel_map, &obj->active_ssel, spi_inst_p);
        }
        else
        {
            mosi_map = _CYHAL_SCB_FIND_MAP_BLOCK(mosi, cyhal_pin_map_scb_spi_m_mosi, spi_inst_p);
            miso_map = _CYHAL_SCB_FIND_MAP_BLOCK(miso, cyhal_pin_map_scb_spi_m_miso, spi_inst_p);
            sclk_map = _CYHAL_SCB_FIND_MAP_BLOCK(sclk, cyhal_pin_map_scb_spi_m_clk, spi_inst_p);
            mosi_dm = (uint8_t)CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_MOSI;
            miso_dm = (uint8_t)CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_MISO;
            sclk_dm = (uint8_t)CYHAL_PIN_MAP_DRIVE_MODE_SCB_SPI_M_CLK;
            /* No need to find maps for ssel pins, as GPIO used */
        }

        const cyhal_resource_pin_mapping_t *base_map = (NC != mosi)
            ? (mosi_map != NULL ? mosi_map : NULL)
            : (miso_map != NULL ? miso_map : NULL);

        /* Validate pins mapping */
        if (NULL == base_map ||
            ((NC != mosi) && ((NULL == mosi_map) || !_cyhal_utils_map_resources_equal(base_map, mosi_map))) ||
            ((NC != miso) && ((NULL == miso_map) || !_cyhal_utils_map_resources_equal(base_map, miso_map))) ||
            ((NC != sclk) && ((NULL == sclk_map) || !_cyhal_utils_map_resources_equal(base_map, sclk_map))) ||
            ((obj->is_slave) && ((NC != ssel) && ((NULL == ssel_map) || !_cyhal_utils_map_resources_equal(base_map, ssel_map)))))
        {
            result = CYHAL_SPI_RSLT_ERR_INVALID_PIN;
        }
    }

    if (CY_RSLT_SUCCESS == result)
    {
        if (false == obj->dc_configured)
        {
            result = cyhal_hwmgr_reserve(spi_inst_p);
        }
    }

    cyhal_system_critical_section_exit(saved_intr_status);

    if (CY_RSLT_SUCCESS == result)
    {
        obj->resource = *spi_inst_p;
        uint8_t scb_arr_index = _cyhal_scb_get_block_index(obj->resource.block_num);
        obj->base = _CYHAL_SCB_BASE_ADDRESSES[scb_arr_index];
    }

    // reserve the MOSI pin
    if ((result == CY_RSLT_SUCCESS) && (NC != mosi))
    {
        if (false == obj->dc_configured)
        {
            result = _cyhal_utils_reserve_and_connect(mosi_map, mosi_dm);
        }
        if (result == CY_RSLT_SUCCESS)
        {
            obj->pin_mosi = mosi;
        }
    }

    // reserve the MISO pin
    if ((result == CY_RSLT_SUCCESS) && (NC != miso))
    {
        if (false == obj->dc_configured)
        {
            result = _cyhal_utils_reserve_and_connect(miso_map, miso_dm);
        }
        if (result == CY_RSLT_SUCCESS)
        {
            obj->pin_miso = miso;
        }
    }

    // reserve the SCLK pin
    if (result == CY_RSLT_SUCCESS && (NC != sclk))
    {
        if (false == obj->dc_configured)
        {
            result = _cyhal_utils_reserve_and_connect(sclk_map, sclk_dm);
        }
        if (result == CY_RSLT_SUCCESS)
        {
            obj->pin_sclk = sclk;
        }
    }

    // reserve and configure the SSEL pin
    if ((result == CY_RSLT_SUCCESS) && (NC != ssel))
    {
        result = _cyhal_spi_ssel_config(obj, ssel,
                    (cyhal_spi_ssel_polarity_t)((cfg->config->ssPolarity >> obj->active_ssel) & 0x1), !obj->dc_configured);
    }

    if (result == CY_RSLT_SUCCESS)
    {
        if (cfg->clock == NULL)
        {
            result = _cyhal_utils_allocate_clock(&(obj->clock), &(obj->resource), CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT, true);
            obj->alloc_clock = true;
        }
        else
        {
            obj->clock = *cfg->clock;
            obj->alloc_clock = false;

            /* Per CDT 315848 and 002-20730 Rev. *E:
             * For SPI, an integer clock divider must be used for both master and slave. */
            if ((obj->clock.block == CYHAL_CLOCK_BLOCK_PERIPHERAL_16_5BIT) || (obj->clock.block == CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT))
            {
                result = CYHAL_SPI_RSLT_CLOCK_NOT_SUPPORTED;
            }
        }
    }
    if (result == CY_RSLT_SUCCESS)
    {
        result = _cyhal_utils_peri_pclk_assign_divider(_cyhal_scb_get_clock_index(obj->resource.block_num), &(obj->clock));

        if ((result == CY_RSLT_SUCCESS) && obj->alloc_clock)
        {
            result = _cyhal_spi_int_frequency(obj, _CYHAL_SPI_DEFAULT_SPEED, &obj->oversample_value);
        }
    }

    return result;
}

cy_rslt_t cyhal_spi_init(cyhal_spi_t *obj, cyhal_gpio_t mosi, cyhal_gpio_t miso, cyhal_gpio_t sclk, cyhal_gpio_t ssel,
                         const cyhal_clock_t *clk, uint8_t bits, cyhal_spi_mode_t mode, bool is_slave)
{
    CY_ASSERT(NULL != obj);

    cy_stc_scb_spi_config_t driver_config = _cyhal_spi_default_config;
    driver_config.spiMode = is_slave == 0
        ? CY_SCB_SPI_MASTER
        : CY_SCB_SPI_SLAVE;
    driver_config.enableMsbFirst = _is_cyhal_mode_msb(mode);
    driver_config.sclkMode = _cyhal_convert_mode_sclk(mode);
    driver_config.rxDataWidth = bits;
    driver_config.txDataWidth = bits;
    driver_config.ssPolarity = ((CY_SCB_SPI_ACTIVE_LOW << CY_SCB_SPI_SLAVE_SELECT0) | \
                                (CY_SCB_SPI_ACTIVE_LOW << CY_SCB_SPI_SLAVE_SELECT1) | \
                                (CY_SCB_SPI_ACTIVE_LOW << CY_SCB_SPI_SLAVE_SELECT2) | \
                                (CY_SCB_SPI_ACTIVE_LOW << CY_SCB_SPI_SLAVE_SELECT3));
    cyhal_spi_configurator_t cfg = {
        .resource = NULL,
        .config = &driver_config,
        .clock = clk,
        .gpios = { sclk, { ssel, NC, NC, NC }, mosi, miso }
    };

    return cyhal_spi_init_cfg(obj, &cfg);
}

cy_rslt_t cyhal_spi_init_cfg(cyhal_spi_t *obj, const cyhal_spi_configurator_t *cfg)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != cfg);
    CY_ASSERT(NULL != cfg->config);

    memset(obj, 0, sizeof(cyhal_spi_t));

    obj->dc_configured = (NULL != cfg->resource);
    cy_stc_scb_spi_config_t cfg_local = *cfg->config;

    if (obj->dc_configured &&
       ((cfg_local.subMode != CY_SCB_SPI_MOTOROLA) ||
        (cfg_local.rxFifoIntEnableMask != 0) ||
        (cfg_local.txFifoIntEnableMask != 0) ||
        (cfg_local.masterSlaveIntEnableMask != 0) ||
        (cfg_local.rxDataWidth != cfg_local.txDataWidth)))
    {
        /* Next SPI personality (device configurator) items are NOT supported by SPI HAL:
        - Modes: TI (Start Coincides), TI (Start Precedes), National Semiconductor (Microwire)
        - Low-level RX Interrupt sources
        - Low-level TX Interrupt sources
        - SPI Done Master interrupt source
        - Different data width for RX and TX
        */
        return CYHAL_SPI_RSLT_ERR_CFG_NOT_SUPPORTED;
    }

    cy_rslt_t result = CY_RSLT_SUCCESS;
    bool is_slave = (cfg_local.spiMode == CY_SCB_SPI_SLAVE);

    // Explicitly marked not allocated resources as invalid to prevent freeing them.
    for (uint8_t i = 0; i < _CYHAL_SPI_SSEL_NUM; i++)
    {
        obj->pin_ssel[i] = NC;
        obj->ssel_pol[i] = CY_SCB_SPI_ACTIVE_LOW;
    }
    obj->resource.type = CYHAL_RSC_INVALID;
    obj->pin_miso = NC;
    obj->pin_mosi = NC;
    obj->pin_sclk = NC;

    obj->pending = _CYHAL_SPI_PENDING_NONE;
    obj->write_fill = (uint8_t) CY_SCB_SPI_DEFAULT_TX;
    obj->active_ssel = 0;
    obj->is_slave = is_slave;
    obj->oversample_value = _CYHAL_SPI_OVERSAMPLE_MIN;

    result = _cyhal_spi_setup_resources(obj, cfg);

    if (result == CY_RSLT_SUCCESS)
    {
        _cyhal_scb_update_instance_data(obj->resource.block_num, (void*)obj, &_cyhal_spi_pm_callback_instance);
        if ((false == obj->dc_configured) && obj->alloc_clock)
        {
            cfg_local.oversample = obj->oversample_value;
        }
        obj->oversample_value = cfg_local.oversample;
        obj->data_bits = cfg_local.txDataWidth;
        obj->msb_first = cfg_local.enableMsbFirst;
        obj->clk_mode = cfg_local.sclkMode;
        obj->mode = (uint8_t) _cyhal_spi_mode_pdl_to_hal(&cfg_local);

        result = (cy_rslt_t)Cy_SCB_SPI_Init(obj->base, &cfg_local, &(obj->context));
    }

    if (result == CY_RSLT_SUCCESS)
    {
        /* Activating specified by user ssel after init */
        if (NC != obj->pin_ssel[obj->active_ssel])
        {
            result = cyhal_spi_select_active_ssel(obj, obj->pin_ssel[obj->active_ssel]);

            /* Configuring rest of provided ssel signals */
            size_t ssel_idx = obj->active_ssel;
            while ((result == CY_RSLT_SUCCESS) && ((ssel_idx + 1) < sizeof(cfg->gpios.ssel) / sizeof(cfg->gpios.ssel[0])))
            {
                ++ssel_idx;
                if (NC != cfg->gpios.ssel[ssel_idx])
                {
                    result = _cyhal_spi_ssel_config(obj, cfg->gpios.ssel[ssel_idx],
                                        (cyhal_spi_ssel_polarity_t)((cfg->config->ssPolarity >> ssel_idx) & 0x1),
                                        !obj->dc_configured);
                }
            }
        }
    }

    if (result == CY_RSLT_SUCCESS)
    {
        uint8_t scb_arr_index = _cyhal_scb_get_block_index(obj->resource.block_num);

        obj->callback_data.callback = NULL;
        obj->callback_data.callback_arg = NULL;
        obj->irq_cause = 0;

        #if defined (COMPONENT_CAT5)
            Cy_SCB_RegisterInterruptCallback(obj->base, _cyhal_irq_cb[obj->resource.block_num]);
            Cy_SCB_EnableInterrupt(obj->base);
        #endif

        _cyhal_irq_register(_CYHAL_SCB_IRQ_N[scb_arr_index], CYHAL_ISR_PRIORITY_DEFAULT, (cy_israddress)_cyhal_spi_irq_handler );
        _cyhal_irq_enable(_CYHAL_SCB_IRQ_N[scb_arr_index]);
        Cy_SCB_SPI_Enable(obj->base);
    }
    else
    {
        cyhal_spi_free(obj);
    }
    return result;
}

void cyhal_spi_free(cyhal_spi_t *obj)
{
    if (NULL != obj->base)
    {
        _cyhal_scb_update_instance_data(obj->resource.block_num, NULL, NULL);
        Cy_SCB_SPI_Disable(obj->base, NULL);
        Cy_SCB_SPI_DeInit(obj->base);
        obj->base = NULL;
    }

    if (obj->resource.type != CYHAL_RSC_INVALID)
    {
        uint8_t scb_arr_index = _cyhal_scb_get_block_index(obj->resource.block_num);
        _cyhal_system_irq_t irqn = _CYHAL_SCB_IRQ_N[scb_arr_index];
        _cyhal_irq_free(irqn);

        if (false == obj->dc_configured)
        {
            cyhal_hwmgr_free(&(obj->resource));
        }
        obj->resource.type = CYHAL_RSC_INVALID;
    }

    if (false == obj->dc_configured)
    {
        _cyhal_utils_release_if_used(&(obj->pin_miso));
        _cyhal_utils_release_if_used(&(obj->pin_mosi));
        _cyhal_utils_release_if_used(&(obj->pin_sclk));
        for (uint8_t i = 0; i < _CYHAL_SPI_SSEL_NUM; i++)
        {
            #if defined(COMPONENT_CAT5)
            if(obj->is_slave == false)
            {
                // In master mode, we have reserved this via cyhal_gpio_init which logs it as reserved
                // in cyhal_gpio.c static arrays.  Need to free it similarly to mark it unreserved

                // Potential side effects: gpio free also unregisters any callback and disconnects the pin.
                // If this becomes problematic, add new gpio free_btss function to unset those arrays
                cyhal_gpio_free((obj->pin_ssel[i]));
            }
            else
            #endif
            {
                _cyhal_utils_release_if_used(&(obj->pin_ssel[i]));
            }
        }
    }

    if (obj->alloc_clock)
    {
       cyhal_clock_free(&(obj->clock));
       obj->alloc_clock = false;
    }
}

static void _cyhal_ssel_switch_state(cyhal_spi_t *obj, uint8_t ssel_idx, bool ssel_activate)
{
    if ((!obj->is_slave) && (CYHAL_NC_PIN_VALUE != obj->pin_ssel[ssel_idx]))
    {
        /* Situations described:
        *   ssel_activate = true (need to set SSEL into active state)
        *       CY_SCB_SPI_ACTIVE_LOW - writing 0 to ssel pin
        *       CY_SCB_SPI_ACTIVE_HIGH - writing 1 to ssel pin
        *   ssel_activate = false (need to set SSEL into inactive state)
        *       CY_SCB_SPI_ACTIVE_LOW - writing 1 to ssel pin
        *       CY_SCB_SPI_ACTIVE_HIGH - writing 0 to ssel pin */
        bool ssel_state = (CY_SCB_SPI_ACTIVE_LOW == obj->ssel_pol[ssel_idx]) ? !ssel_activate : ssel_activate;
        cyhal_gpio_write(obj->pin_ssel[ssel_idx], ssel_state);
    }
}

cy_rslt_t cyhal_spi_set_frequency(cyhal_spi_t *obj, uint32_t hz)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    uint8_t   ovr_sample_val;

    if (NULL == obj)
    {
        return CYHAL_SPI_RSLT_BAD_ARGUMENT;
    }

    /* HAL is allowed to change clock settings since it owns the clock */
    if (obj->alloc_clock)
    {
        Cy_SCB_SPI_Disable(obj->base, &obj->context);
        result = _cyhal_spi_int_frequency(obj, hz, &ovr_sample_val);

        /* No need to reconfigure slave since oversample value, that was changed in _cyhal_spi_int_frequency, in slave is ignored */
        if ((CY_RSLT_SUCCESS == result) && !obj->is_slave && (obj->oversample_value != ovr_sample_val))
        {
            cy_stc_scb_spi_config_t config_structure = _cyhal_spi_default_config;
            Cy_SCB_SPI_DeInit(obj->base);
            config_structure.spiMode = obj->is_slave == false
                ? CY_SCB_SPI_MASTER
                : CY_SCB_SPI_SLAVE;
            config_structure.enableMsbFirst = obj->msb_first;
            config_structure.sclkMode = obj->clk_mode;
            config_structure.rxDataWidth = obj->data_bits;
            config_structure.txDataWidth = obj->data_bits;
            config_structure.oversample = ovr_sample_val;
            obj->oversample_value = ovr_sample_val;
            result = (cy_rslt_t)Cy_SCB_SPI_Init(obj->base, &config_structure, &(obj->context));
        }

        if (CY_RSLT_SUCCESS == result)
        {
            Cy_SCB_SPI_Enable(obj->base);
        }
    }
    else
    {
        result = CYHAL_SPI_RSLT_CLOCK_ERROR;
    }

    return result;
}

cy_rslt_t cyhal_spi_select_active_ssel(cyhal_spi_t *obj, cyhal_gpio_t ssel)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != obj->base);
    if ((NC != ssel) && (_CYHAL_SPI_PENDING_NONE == obj->pending))
    {
        for (uint8_t i = 0; i < _CYHAL_SPI_SSEL_NUM; i++)
        {
            if(obj->pin_ssel[i] == ssel)
            {
                Cy_SCB_SPI_SetActiveSlaveSelect(obj->base, (cy_en_scb_spi_slave_select_t)i);
                obj->active_ssel = i;
                return CY_RSLT_SUCCESS;
            }
        }
    }
    return CYHAL_SPI_RSLT_ERR_CANNOT_SWITCH_SSEL;
}

cy_rslt_t cyhal_spi_slave_select_config(cyhal_spi_t *obj, cyhal_gpio_t ssel, cyhal_spi_ssel_polarity_t polarity)
{
    CY_ASSERT(NULL != obj);
    return _cyhal_spi_ssel_config(obj, ssel, polarity, true);
}

cy_rslt_t cyhal_spi_recv(cyhal_spi_t *obj, uint32_t *value)
{
    if (NULL == obj)
        return CYHAL_SPI_RSLT_BAD_ARGUMENT;

    if (_cyhal_scb_pm_transition_pending())
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;

    uint32_t read_value = CY_SCB_SPI_RX_NO_DATA;
    const uint32_t fill_in = 0xffffffffUL; /* PDL Fill in value */
    uint32_t count = 0;

    if ((obj->is_slave) && (CYHAL_NC_PIN_VALUE == obj->pin_mosi))
    {
        return CYHAL_SPI_RSLT_INVALID_PIN_API_NOT_SUPPORTED;
    }

    if ((!obj->is_slave) && (CYHAL_NC_PIN_VALUE == obj->pin_miso))
    {
        return CYHAL_SPI_RSLT_INVALID_PIN_API_NOT_SUPPORTED;
    }

    if (!obj->is_slave)
    {
        _cyhal_ssel_switch_state(obj, obj->active_ssel, _CYHAL_SPI_SSEL_ACTIVATE);

        /* Clear FIFOs */
        Cy_SCB_SPI_ClearTxFifo(obj->base);
        Cy_SCB_SPI_ClearRxFifo(obj->base);

        while (count == 0)
        {
            count = Cy_SCB_SPI_Write(obj->base, fill_in);
        }

        while (Cy_SCB_SPI_IsTxComplete(obj->base) == false) { }
        while (Cy_SCB_SPI_GetNumInRxFifo(obj->base) == 0) { } /* Wait for RX FIFO not empty */
        _cyhal_ssel_switch_state(obj, obj->active_ssel, _CYHAL_SPI_SSEL_DEACTIVATE);
    }

    while (read_value == CY_SCB_SPI_RX_NO_DATA)
    {
        read_value = Cy_SCB_SPI_Read(obj->base);
    }
    *value = read_value;
    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_spi_send(cyhal_spi_t *obj, uint32_t value)
{
    if (NULL == obj)
        return CYHAL_SPI_RSLT_BAD_ARGUMENT;

    if (_cyhal_scb_pm_transition_pending())
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;

    uint32_t count = 0;
    cy_rslt_t result = CY_RSLT_SUCCESS;

    if ((obj->is_slave) && (CYHAL_NC_PIN_VALUE == obj->pin_miso))
    {
        return CYHAL_SPI_RSLT_INVALID_PIN_API_NOT_SUPPORTED;
    }

    if ((!obj->is_slave) && (CYHAL_NC_PIN_VALUE == obj->pin_mosi))
    {
        return CYHAL_SPI_RSLT_INVALID_PIN_API_NOT_SUPPORTED;
    }

    if (!obj->is_slave)
    {
        _cyhal_ssel_switch_state(obj, obj->active_ssel, _CYHAL_SPI_SSEL_ACTIVATE);

        /* Clear FIFOs */
        Cy_SCB_SPI_ClearTxFifo(obj->base);
        Cy_SCB_SPI_ClearRxFifo(obj->base);
    }

    while (count == 0)
    {
        count = Cy_SCB_SPI_Write(obj->base, value);
    }

    if (!obj->is_slave)
    {
        while (Cy_SCB_SPI_IsTxComplete(obj->base) == false) { }
        while (Cy_SCB_SPI_GetNumInRxFifo(obj->base) == 0) { } /* Wait for RX FIFO not empty */
        _cyhal_ssel_switch_state(obj, obj->active_ssel, _CYHAL_SPI_SSEL_DEACTIVATE);
        (void)Cy_SCB_SPI_Read(obj->base);
    }

    return result;
}


cy_rslt_t cyhal_spi_slave_read(cyhal_spi_t *obj, uint8_t *dst_buff, uint16_t *size, uint32_t timeout)
{
    cy_rslt_t status = CYHAL_SPI_RSLT_BAD_ARGUMENT;

    if ((dst_buff != NULL) && (size != NULL))
    {
        /* Wait until the master start writing or any data will be in the slave RX buffer */
        status = _cyhal_spi_wait_for_op(obj, _CYHAL_SPI_WAIT_OP_RD_NOT_BUSY, &timeout);

        if (CY_RSLT_SUCCESS == status)
        {
            /* Wait until the master finish writing */
            status = _cyhal_spi_wait_for_op(obj, _CYHAL_SPI_WAIT_OP_RD_BUSY, &timeout);
        }

        if (CY_RSLT_SUCCESS == status)
        {
            *size = _CYHAL_SCB_BYTES_TO_COPY(cyhal_spi_readable(obj), *size);
            *size = Cy_SCB_SPI_ReadArray(obj->base, (void*)dst_buff, (uint32_t)*size);
        }
    }
    return status;
}

cy_rslt_t cyhal_spi_slave_write(cyhal_spi_t *obj, const uint8_t *src_buff, uint16_t *size, uint32_t timeout)
{
    cy_rslt_t status = CYHAL_SPI_RSLT_BAD_ARGUMENT;

    if ((src_buff != NULL) && (size != NULL))
    {
        status = cyhal_spi_transfer_async(obj, src_buff, (size_t)*size, NULL, 0U);

        if (CY_RSLT_SUCCESS == status)
        {
            /* Wait until the slave finish writing */
            status = _cyhal_spi_wait_for_op(obj, _CYHAL_SPI_WAIT_OP_WR, &timeout);
        }
    }
    return status;
}

cy_rslt_t cyhal_spi_transfer(cyhal_spi_t *obj, const uint8_t *tx, size_t tx_length, uint8_t *rx, size_t rx_length, uint8_t write_fill)
{
    if (NULL == obj)
        return CYHAL_SPI_RSLT_BAD_ARGUMENT;

    if (_cyhal_scb_pm_transition_pending())
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;

    obj->write_fill = write_fill;
    cy_rslt_t rslt = cyhal_spi_transfer_async(obj, tx, tx_length, rx, rx_length);
    if (rslt == CY_RSLT_SUCCESS)
    {
        while (obj->pending != _CYHAL_SPI_PENDING_NONE) { } /* Wait for async transfer to complete */
    }
    obj->write_fill = (uint8_t) CY_SCB_SPI_DEFAULT_TX;
    return rslt;
}

cy_rslt_t cyhal_spi_transfer_async(cyhal_spi_t *obj, const uint8_t *tx, size_t tx_length, uint8_t *rx, size_t rx_length)
{
    if (NULL == obj)
        return CYHAL_SPI_RSLT_BAD_ARGUMENT;

    if (_cyhal_scb_pm_transition_pending())
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;

    cy_en_scb_spi_status_t spi_status;

    /* There is no pin provided for incoming data. Ignoring user's rx array and rx_length. */
    if ((obj->is_slave && (NC == obj->pin_mosi)) || (!obj->is_slave && (NC == obj->pin_miso)))
    {
        rx_length = 0;
    }

    /* There is no pin provided for outgoing data. Ignoring user's tx array and tx_length. */
    if ((obj->is_slave && (NC == obj->pin_miso)) || (!obj->is_slave && (NC == obj->pin_mosi)))
    {
        tx_length = 0;
    }

    _cyhal_ssel_switch_state(obj, obj->active_ssel, _CYHAL_SPI_SSEL_ACTIVATE);
    obj->is_async = true;

    uint8_t arr_size_modifier = 0;
    if (obj->data_bits <= 8)
    {
        arr_size_modifier = 1;
    }
    else if (obj->data_bits <= 16)
    {
        arr_size_modifier = 2;
    }
    else
    {
        arr_size_modifier = 4;
    }


    /* Setup transfer */
    if (tx_length > rx_length)
    {
        if (rx_length > 0)
        {
            /* I) write + read, II) write only */
            obj->pending = _CYHAL_SPI_PENDING_TX_RX;
            obj->rx_buffer = NULL;

            obj->tx_buffer = tx + (rx_length * arr_size_modifier);
            obj->tx_buffer_size = tx_length - rx_length;

            tx_length = rx_length; // Use tx_length to store entire transfer length
        }
        else
        {
            /*  I) write only */
            obj->pending = _CYHAL_SPI_PENDING_TX;
            obj->rx_buffer = NULL;
            obj->tx_buffer = NULL;

            rx = NULL;
        }
    }
    else if (rx_length > tx_length)
    {
        if (tx_length > 0)
        {
            /*  I) write + read, II) read only */
            obj->pending = _CYHAL_SPI_PENDING_TX_RX;
            obj->tx_buffer = NULL;

            obj->rx_buffer = rx + (tx_length * arr_size_modifier);
            obj->rx_buffer_size = rx_length - tx_length;
        }
        else
        {
            /*  I) read only. */
            obj->pending = _CYHAL_SPI_PENDING_RX;
            obj->tx_buffer = NULL;

            obj->rx_buffer = rx_length > 1 ? rx + 1 : NULL;
            obj->rx_buffer_size = rx_length - 1;
            tx = &obj->write_fill;
            tx_length = 1;
        }
    }
    else
    {
        /* RX and TX of the same size: I) write + read. */
        obj->pending = _CYHAL_SPI_PENDING_TX_RX;
        obj->rx_buffer = NULL;
        obj->tx_buffer = NULL;
    }
    spi_status = Cy_SCB_SPI_Transfer(obj->base, (void *)tx, rx, tx_length, &obj->context);
    return spi_status == CY_SCB_SPI_SUCCESS
        ? CY_RSLT_SUCCESS
        : CYHAL_SPI_RSLT_TRANSFER_ERROR;
}

bool cyhal_spi_is_busy(cyhal_spi_t *obj)
{
    return Cy_SCB_SPI_IsBusBusy(obj->base) || (_CYHAL_SPI_PENDING_NONE != obj->pending);
}

cy_rslt_t cyhal_spi_abort_async(cyhal_spi_t *obj)
{
    if (NULL == obj)
    {
        return CYHAL_SPI_RSLT_BAD_ARGUMENT;
    }

    Cy_SCB_SPI_AbortTransfer(obj->base, &(obj->context));
    obj->pending = _CYHAL_SPI_PENDING_NONE;
    return CY_RSLT_SUCCESS;
}

void cyhal_spi_register_callback(cyhal_spi_t *obj, cyhal_spi_event_callback_t callback, void *callback_arg)
{
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    obj->callback_data.callback = (cy_israddress) callback;
    obj->callback_data.callback_arg = callback_arg;
    cyhal_system_critical_section_exit(savedIntrStatus);
    Cy_SCB_SPI_RegisterCallback(obj->base, _cyhal_spi_cb_wrapper, &(obj->context));

    obj->irq_cause = 0;
}

void cyhal_spi_enable_event(cyhal_spi_t *obj, cyhal_spi_event_t event, uint8_t intr_priority, bool enable)
{
    if (enable)
    {
        obj->irq_cause |= event;
    }
    else
    {
        obj->irq_cause &= ~event;
    }

    uint8_t scb_arr_index = _cyhal_scb_get_block_index(obj->resource.block_num);
    _cyhal_system_irq_t irqn = _CYHAL_SCB_IRQ_N[scb_arr_index];
    _cyhal_irq_set_priority(irqn, intr_priority);
}

cy_rslt_t cyhal_spi_set_fifo_level(cyhal_spi_t *obj, cyhal_spi_fifo_type_t type, uint16_t level)
{
    return _cyhal_scb_set_fifo_level(obj->base, (cyhal_scb_fifo_type_t)type, level);
}

cy_rslt_t cyhal_spi_enable_output(cyhal_spi_t *obj, cyhal_spi_output_t output, cyhal_source_t *source)
{
    return _cyhal_scb_enable_output(obj->resource, (cyhal_scb_output_t)output, source);
}

cy_rslt_t cyhal_spi_disable_output(cyhal_spi_t *obj, cyhal_spi_output_t output)
{
    CY_UNUSED_PARAMETER(obj);
    return _cyhal_scb_disable_output((cyhal_scb_output_t)output);
}

uint32_t cyhal_spi_readable(cyhal_spi_t *obj)
{
    return Cy_SCB_SPI_GetNumInRxFifo(obj->base);
}

uint32_t cyhal_spi_writable(cyhal_spi_t *obj)
{
    return Cy_SCB_GetFifoSize(obj->base) - Cy_SCB_SPI_GetNumInTxFifo(obj->base);
}

cy_rslt_t cyhal_spi_clear(cyhal_spi_t *obj)
{
    Cy_SCB_SPI_ClearRxFifo(obj->base);
    Cy_SCB_SPI_ClearTxFifo(obj->base);

    return CY_RSLT_SUCCESS;
}

#if defined(__cplusplus)
}
#endif

#endif /* CYHAL_DRIVER_AVAILABLE_SPI */
