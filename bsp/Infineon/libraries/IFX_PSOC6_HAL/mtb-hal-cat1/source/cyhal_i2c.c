/*******************************************************************************
* File Name: cyhal_i2c.c
*
* Description:
* Provides a high level interface for interacting with the Infineon I2C. This is
* a wrapper around the lower level PDL API.
*
********************************************************************************
* \copyright
* Copyright 2018-2021 Cypress Semiconductor Corporation (an Infineon company) or
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

#include <stdlib.h>
#include <string.h>
#include "cyhal_i2c.h"
#include "cyhal_scb_common.h"
#include "cyhal_gpio.h"
#include "cyhal_hwmgr.h"
#include "cyhal_system.h"
#include "cyhal_syspm.h"
#include "cyhal_utils.h"
#include "cyhal_irq_psoc.h"
#include "cyhal_clock.h"

#if (CYHAL_DRIVER_AVAILABLE_I2C)

#if defined(__cplusplus)
extern "C"
{
#endif

#define _CYHAL_I2C_PENDING_NONE                    0
#define _CYHAL_I2C_PENDING_RX                      1
#define _CYHAL_I2C_PENDING_TX                      2
#define _CYHAL_I2C_PENDING_TX_RX                   3

#define _CYHAL_I2C_MASTER_DEFAULT_FREQ             100000

static const cy_stc_scb_i2c_config_t _cyhal_i2c_default_config = {
        .i2cMode   = CY_SCB_I2C_MASTER,
        .useRxFifo = false,
        .useTxFifo = true,
        .slaveAddress     = 0U,
        .slaveAddressMask = 0U,
        .acceptAddrInFifo = false,
        .ackGeneralAddr   = false,
        .enableWakeFromSleep = false,
        .enableDigitalFilter = false,
        .lowPhaseDutyCycle = 8U,
        .highPhaseDutyCycle = 8U,
};

/* The PDL clears the IRQ status during Cy_SCB_I2C_Interrupt which prevents _cyhal_scb_get_irq_obj()
 * from working properly in _cyhal_i2c_cb_wrapper on devices with muxed IRQs, because they can't tell
 * at that point which system IRQ caused the CPU IRQ. So we need to save this value at the beginning of the
 * IRQ handler when we are able to determine what it is */
static volatile cyhal_i2c_t* _cyhal_i2c_irq_obj = NULL;

static cyhal_i2c_event_t _cyhal_i2c_convert_interrupt_cause(uint32_t pdl_cause)
{
    static const uint32_t status_map1[] =
    {
        (uint32_t)CYHAL_I2C_EVENT_NONE,                 // Default no event
        (uint32_t)CYHAL_I2C_SLAVE_READ_EVENT,           // CY_SCB_I2C_SLAVE_READ_EVENT
        (uint32_t)CYHAL_I2C_SLAVE_WRITE_EVENT,          // CY_SCB_I2C_SLAVE_WRITE_EVENT
        (uint32_t)CYHAL_I2C_SLAVE_RD_IN_FIFO_EVENT,     // CY_SCB_I2C_SLAVE_RD_IN_FIFO_EVENT
        (uint32_t)CYHAL_I2C_SLAVE_RD_BUF_EMPTY_EVENT,   // CY_SCB_I2C_SLAVE_RD_BUF_EMPTY_EVENT
        (uint32_t)CYHAL_I2C_SLAVE_RD_CMPLT_EVENT,       // CY_SCB_I2C_SLAVE_RD_CMPLT_EVENT
        (uint32_t)CYHAL_I2C_SLAVE_WR_CMPLT_EVENT,       // CY_SCB_I2C_SLAVE_WR_CMPLT_EVENT
        (uint32_t)CYHAL_I2C_SLAVE_ERR_EVENT,            // CY_SCB_I2C_SLAVE_ERR_EVENT
    };
    uint32_t set1 = _cyhal_utils_convert_flags(status_map1, sizeof(status_map1) / sizeof(uint32_t), pdl_cause & 0xFF);

    static const uint32_t status_map2[] =
    {
        (uint32_t)CYHAL_I2C_EVENT_NONE,                 // Default no event
        (uint32_t)CYHAL_I2C_MASTER_WR_IN_FIFO_EVENT,    // CY_SCB_I2C_MASTER_WR_IN_FIFO_EVENT
        (uint32_t)CYHAL_I2C_MASTER_WR_CMPLT_EVENT,      // CY_SCB_I2C_MASTER_WR_CMPLT_EVENT
        (uint32_t)CYHAL_I2C_MASTER_RD_CMPLT_EVENT,      // CY_SCB_I2C_MASTER_RD_CMPLT_EVENT
        (uint32_t)CYHAL_I2C_MASTER_ERR_EVENT,           // CY_SCB_I2C_MASTER_ERR_EVENT
    };
    uint32_t set2 = _cyhal_utils_convert_flags(status_map2, sizeof(status_map2) / sizeof(uint32_t), pdl_cause >> 16);

    return (cyhal_i2c_event_t)(set1 | set2);
}

static void _cyhal_i2c_irq_handler(void)
{
    /* Save the old value and store it aftewards in case we get into a nested IRQ situation */
    /* Safe to cast away volatile because we don't expect this pointer to be changed while we're in here, they
     * just might change where the original pointer points */
    cyhal_i2c_t* old_irq_obj = (cyhal_i2c_t*)_cyhal_i2c_irq_obj;
    _cyhal_i2c_irq_obj = (cyhal_i2c_t*) _cyhal_scb_get_irq_obj();
    cyhal_i2c_t* obj = (cyhal_i2c_t*)_cyhal_i2c_irq_obj;

    Cy_SCB_I2C_Interrupt(obj->base, &(obj->context));

    if (obj->pending)
    {
        /* This code is part of cyhal_i2c_master_transfer_async() API functionality */
        /* cyhal_i2c_master_transfer_async() API uses this interrupt handler for RX transfer */
        if (0 == (Cy_SCB_I2C_MasterGetStatus(obj->base,  &obj->context) & CY_SCB_I2C_MASTER_BUSY))
        {
            /* Check if TX is completed and run RX in case when TX and RX are enabled */
            if (obj->pending == _CYHAL_I2C_PENDING_TX_RX)
            {
                /* Start RX transfer */
                obj->pending = _CYHAL_I2C_PENDING_RX;
                Cy_SCB_I2C_MasterRead(obj->base, &obj->rx_config, &obj->context);
            }
            else
            {
                /* Finish async TX or RX separate transfer */
                obj->pending = _CYHAL_I2C_PENDING_NONE;
            }
        }
    }

    _cyhal_i2c_irq_obj = old_irq_obj;
}

static void _cyhal_i2c_cb_wrapper(uint32_t event)
{
    /* Safe to cast away volatile because we don't expect this pointer to be changed while we're in here, they
     * just might change where the original pointer points */
    cyhal_i2c_t *obj = (cyhal_i2c_t*)_cyhal_i2c_irq_obj;
    cyhal_i2c_event_t anded_events = (cyhal_i2c_event_t)(obj->irq_cause & (uint32_t)_cyhal_i2c_convert_interrupt_cause(event));
    if (anded_events)
    {
        cyhal_i2c_event_callback_t callback = (cyhal_i2c_event_callback_t) obj->callback_data.callback;
        callback(obj->callback_data.callback_arg, anded_events);
    }
}

static bool _cyhal_i2c_pm_callback_instance(void *obj_ptr, cyhal_syspm_callback_state_t state, cy_en_syspm_callback_mode_t pdl_mode)
{
    cyhal_i2c_t *obj = (cyhal_i2c_t*)obj_ptr;
    cy_stc_syspm_callback_params_t i2c_callback_params = {
        .base = (void *) (obj->base),
        .context = (void *) &(obj->context)
    };
    bool allow = true;

    if (CYHAL_SYSPM_CB_CPU_DEEPSLEEP == state)
        allow = (CY_SYSPM_SUCCESS == Cy_SCB_I2C_DeepSleepCallback(&i2c_callback_params, pdl_mode));
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
    else if (CYHAL_SYSPM_CB_SYSTEM_HIBERNATE == state)
        allow = (CY_SYSPM_SUCCESS == Cy_SCB_I2C_HibernateCallback(&i2c_callback_params, pdl_mode));
#endif

    return allow;
}

static cy_rslt_t _cyhal_i2c_init_resources(cyhal_i2c_t *obj, cyhal_gpio_t sda, cyhal_gpio_t scl, const cyhal_clock_t *clk)
{
    /* Explicitly marked not allocated resources as invalid to prevent freeing them. */
    obj->resource.type = CYHAL_RSC_INVALID;
    obj->pin_scl = CYHAL_NC_PIN_VALUE;
    obj->pin_sda = CYHAL_NC_PIN_VALUE;
    obj->is_clock_owned = false;

    /* Reserve the I2C */
    const cyhal_resource_pin_mapping_t *sda_map = _CYHAL_SCB_FIND_MAP(sda, cyhal_pin_map_scb_i2c_sda);
    const cyhal_resource_pin_mapping_t *scl_map = _CYHAL_SCB_FIND_MAP(scl, cyhal_pin_map_scb_i2c_scl);

    if ((NULL == sda_map) || (NULL == scl_map) || !_cyhal_utils_map_resources_equal(sda_map, scl_map))
    {
        return CYHAL_I2C_RSLT_ERR_INVALID_PIN;
    }

    cyhal_resource_inst_t rsc = { CYHAL_RSC_SCB, scl_map->block_num, scl_map->channel_num };
    cy_rslt_t result = cyhal_hwmgr_reserve(&rsc);

    if (result == CY_RSLT_SUCCESS)
    {
        obj->base = _CYHAL_SCB_BASE_ADDRESSES[rsc.block_num];
        obj->resource = rsc;

        result = _cyhal_utils_reserve_and_connect(sda_map, CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SDA);
        if (result == CY_RSLT_SUCCESS)
            obj->pin_sda = sda;
    }

    if (result == CY_RSLT_SUCCESS)
    {
        result = _cyhal_utils_reserve_and_connect(scl_map, CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SCL);
        if (result == CY_RSLT_SUCCESS)
            obj->pin_scl = scl;
    }

    if (result == CY_RSLT_SUCCESS)
    {
        if (clk == NULL)
        {
            result = _cyhal_utils_allocate_clock(&(obj->clock), &(obj->resource), CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT, true);
            obj->is_clock_owned = (result == CY_RSLT_SUCCESS);
        }
        else
        {
            obj->clock = *clk;
        }
    }

    if (result == CY_RSLT_SUCCESS)
    {
        uint32_t dataRate = _cyhal_i2c_set_peri_divider((void *)obj, true, _CYHAL_I2C_MASTER_DEFAULT_FREQ, false);
        if (dataRate == 0)
        {
            /* Can not reach desired data rate */
            result = CYHAL_I2C_RSLT_ERR_CAN_NOT_REACH_DR;
        }
    }

    return result;
}

static cy_rslt_t _cyhal_i2c_init_hw(cyhal_i2c_t *obj, const cy_stc_scb_i2c_config_t *pdl_cfg)
{
    CY_ASSERT(NULL != obj->base);

    /* Initial value for async operations */
    obj->pending = _CYHAL_I2C_PENDING_NONE;

    /* Configure I2C to operate */
    cy_rslt_t result = (cy_rslt_t)Cy_SCB_I2C_Init(obj->base, pdl_cfg, &(obj->context));

    if (result == CY_RSLT_SUCCESS)
    {
        _cyhal_scb_update_instance_data(obj->resource.block_num, (void*)obj, &_cyhal_i2c_pm_callback_instance);
        /* Enable I2C to operate */
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
        Cy_SCB_I2C_Enable(obj->base);
#elif defined(COMPONENT_CAT2)
        Cy_SCB_I2C_Enable(obj->base, &(obj->context));
#endif
        obj->callback_data.callback = NULL;
        obj->callback_data.callback_arg = NULL;
        obj->irq_cause = CYHAL_I2C_EVENT_NONE;

        _cyhal_irq_register(_CYHAL_SCB_IRQ_N[obj->resource.block_num], CYHAL_ISR_PRIORITY_DEFAULT, _cyhal_i2c_irq_handler);
        _cyhal_irq_enable(_CYHAL_SCB_IRQ_N[obj->resource.block_num]);
    }

    return result;
}

/* Start API implementing */
cy_rslt_t cyhal_i2c_init(cyhal_i2c_t *obj, cyhal_gpio_t sda, cyhal_gpio_t scl, const cyhal_clock_t *clk)
{
    CY_ASSERT(NULL != obj);
    obj->dc_configured = false;
    memset(obj, 0, sizeof(cyhal_i2c_t));

    cy_rslt_t result = _cyhal_i2c_init_resources(obj, sda, scl, clk);
    if (CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_i2c_init_hw(obj, &_cyhal_i2c_default_config);
    }
    if (CY_RSLT_SUCCESS != result)
    {
        cyhal_i2c_free(obj);
    }
    return result;
}

cy_rslt_t cyhal_i2c_init_cfg(cyhal_i2c_t *obj, const cyhal_i2c_configurator_t *cfg)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != cfg);
    CY_ASSERT(NULL != cfg->config);

    memset(obj, 0, sizeof(cyhal_i2c_t));

    obj->dc_configured = true;
    obj->resource = *cfg->resource;
    obj->clock = *cfg->clock;
    obj->is_clock_owned = false;
    obj->base = _CYHAL_SCB_BASE_ADDRESSES[obj->resource.block_num];

    return _cyhal_i2c_init_hw(obj, cfg->config);
}

void cyhal_i2c_free(cyhal_i2c_t *obj)
{
    CY_ASSERT(NULL != obj);

    if (NULL != obj->base)
    {
        Cy_SCB_I2C_Disable(obj->base, &obj->context);
        Cy_SCB_I2C_DeInit(obj->base);
        obj->base = NULL;
    }

    if (CYHAL_RSC_INVALID != obj->resource.type)
    {
        _cyhal_scb_update_instance_data(obj->resource.block_num, NULL, NULL);
        _cyhal_system_irq_t irqn = _CYHAL_SCB_IRQ_N[obj->resource.block_num];
        _cyhal_irq_free(irqn);

        if (!obj->dc_configured)
        {
            cyhal_hwmgr_free(&(obj->resource));
        }

        obj->resource.type = CYHAL_RSC_INVALID;
    }

    if (!obj->dc_configured)
    {
        _cyhal_utils_release_if_used(&(obj->pin_sda));
        _cyhal_utils_release_if_used(&(obj->pin_scl));

        if (obj->is_clock_owned)
        {
            cyhal_clock_free(&(obj->clock));
        }
    }
}

cy_rslt_t cyhal_i2c_configure(cyhal_i2c_t *obj, const cyhal_i2c_cfg_t *cfg)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != cfg);

    (void) Cy_SCB_I2C_Disable(obj->base, &obj->context);

    cy_stc_scb_i2c_config_t config_structure = _cyhal_i2c_default_config;
    config_structure.i2cMode = (cfg->is_slave)
        ? CY_SCB_I2C_SLAVE
        : CY_SCB_I2C_MASTER;

    config_structure.slaveAddress  = (uint8_t)cfg->address;

    /* Set slave address mask if I2C is operate in slave mode */
    if (cfg->is_slave)
    {
        config_structure.slaveAddressMask = 0xFEU;
    }

    /* Set data rate */
    uint32_t dataRate = _cyhal_i2c_set_peri_divider((void *)obj, true, cfg->frequencyhal_hz, cfg->is_slave);
    if (dataRate == 0)
    {
        /* Can not reach desired data rate */
        return CYHAL_I2C_RSLT_ERR_CAN_NOT_REACH_DR;
    }

    cy_rslt_t result = (cy_rslt_t)Cy_SCB_I2C_Init(obj->base, &config_structure, &(obj->context));
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
    (void) Cy_SCB_I2C_Enable(obj->base);
#elif defined(COMPONENT_CAT2)
    (void) Cy_SCB_I2C_Enable(obj->base, &(obj->context));
#endif

    return result;
}

cy_rslt_t cyhal_i2c_master_write(cyhal_i2c_t *obj, uint16_t dev_addr, const uint8_t *data, uint16_t size, uint32_t timeout, bool send_stop)
{
    if (_cyhal_scb_pm_transition_pending())
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;

    cy_en_scb_i2c_status_t status = (obj->context.state == CY_SCB_I2C_IDLE)
        ? Cy_SCB_I2C_MasterSendStart(obj->base, dev_addr, CY_SCB_I2C_WRITE_XFER, timeout, &obj->context)
        : Cy_SCB_I2C_MasterSendReStart(obj->base, dev_addr, CY_SCB_I2C_WRITE_XFER, timeout, &obj->context);

    if (status == CY_SCB_I2C_SUCCESS)
    {
        while (size > 0)
        {
            status = Cy_SCB_I2C_MasterWriteByte(obj->base, *data, timeout, &obj->context);
            if (status != CY_SCB_I2C_SUCCESS)
            {
                break;
            }
            --size;
            ++data;
        }
    }

    if (send_stop)
    {
        /* SCB in I2C mode is very time sensitive. In practice we have to request STOP after */
        /* each block, otherwise it may break the transmission */
        Cy_SCB_I2C_MasterSendStop(obj->base, timeout, &obj->context);
    }

    return status;
}

cy_rslt_t cyhal_i2c_master_read(cyhal_i2c_t *obj, uint16_t dev_addr, uint8_t *data, uint16_t size, uint32_t timeout, bool send_stop)
{
    if (_cyhal_scb_pm_transition_pending())
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;

    cy_en_scb_i2c_command_t ack = CY_SCB_I2C_ACK;

    /* Start transaction, send dev_addr */
    cy_en_scb_i2c_status_t status = obj->context.state == CY_SCB_I2C_IDLE
        ? Cy_SCB_I2C_MasterSendStart(obj->base, dev_addr, CY_SCB_I2C_READ_XFER, timeout, &obj->context)
        : Cy_SCB_I2C_MasterSendReStart(obj->base, dev_addr, CY_SCB_I2C_READ_XFER, timeout, &obj->context);

    if (status == CY_SCB_I2C_SUCCESS)
    {
        while (size > 0) {
            if (size == 1)
            {
                ack = CY_SCB_I2C_NAK;
            }
            status = Cy_SCB_I2C_MasterReadByte(obj->base, ack, (uint8_t *)data, timeout, &obj->context);
            if (status != CY_SCB_I2C_SUCCESS)
            {
                break;
            }
            --size;
            ++data;
        }
    }

    if (send_stop)
    {
        /* SCB in I2C mode is very time sensitive. In practice we have to request STOP after */
        /* each block, otherwise it may break the transmission */
        Cy_SCB_I2C_MasterSendStop(obj->base, timeout, &obj->context);
    }
    return status;
}

cy_rslt_t cyhal_i2c_slave_config_write_buffer(cyhal_i2c_t *obj, const uint8_t *data, uint16_t size)
{
    if (obj->context.state == CY_SCB_I2C_IDLE)
    {
        Cy_SCB_I2C_SlaveConfigWriteBuf(obj->base, (uint8_t *)data, size, &obj->context);
    }
    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_i2c_slave_config_read_buffer(cyhal_i2c_t *obj, uint8_t *data, uint16_t size)
{
    if (obj->context.state == CY_SCB_I2C_IDLE)
    {
        Cy_SCB_I2C_SlaveConfigReadBuf(obj->base, (uint8_t *)data, size, &obj->context);
    }
    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_i2c_master_mem_write(cyhal_i2c_t *obj, uint16_t address, uint16_t mem_addr, uint16_t mem_addr_size, const uint8_t *data, uint16_t size, uint32_t timeout)
{
    if (_cyhal_scb_pm_transition_pending())
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;

    uint8_t mem_addr_buf[2];
    if (mem_addr_size == 1)
    {
        mem_addr_buf[0] = (uint8_t)mem_addr;
    }
    else if (mem_addr_size == 2)
    {
        mem_addr_buf[0] = (uint8_t)(mem_addr >> 8);
        mem_addr_buf[1] = (uint8_t)mem_addr;
    }
    else
    {
        return CYHAL_I2C_RSLT_ERR_INVALID_ADDRESS_SIZE;
    }

    cy_rslt_t status = cyhal_i2c_master_write(obj, address, mem_addr_buf, mem_addr_size, timeout, false);

    if (status == CY_RSLT_SUCCESS)
    {
        while (size > 0)
        {
            status = Cy_SCB_I2C_MasterWriteByte(obj->base, *data, timeout, &obj->context);
            if (status != CY_SCB_I2C_SUCCESS)
            {
                break;
            }
            --size;
            ++data;
        }
        /* SCB in I2C mode is very time sensitive. In practice we have to request STOP after */
        /* each block, otherwise it may break the transmission */
        Cy_SCB_I2C_MasterSendStop(obj->base, timeout, &obj->context);
    }
    return status;
}

cy_rslt_t cyhal_i2c_master_mem_read(cyhal_i2c_t *obj, uint16_t address, uint16_t mem_addr, uint16_t mem_addr_size, uint8_t *data, uint16_t size, uint32_t timeout)
{
    if (_cyhal_scb_pm_transition_pending())
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;

    uint8_t mem_addr_buf[2];
    if (mem_addr_size == 1)
    {
        mem_addr_buf[0] = (uint8_t)mem_addr;
    }
    else if (mem_addr_size == 2)
    {
        mem_addr_buf[0] = (uint8_t)(mem_addr >> 8);
        mem_addr_buf[1] = (uint8_t)mem_addr;
    }
    else
    {
        return CYHAL_I2C_RSLT_ERR_INVALID_ADDRESS_SIZE;
    }

    cy_rslt_t status = cyhal_i2c_master_write(obj, address, mem_addr_buf, mem_addr_size, timeout, false);
    if (status == CY_RSLT_SUCCESS)
    {
        status = cyhal_i2c_master_read(obj, address, data, size, timeout, true);
    }
    return status;
}

cy_rslt_t cyhal_i2c_master_transfer_async(cyhal_i2c_t *obj, uint16_t address, const void *tx, size_t tx_size, void *rx, size_t rx_size)
{
    if (_cyhal_scb_pm_transition_pending())
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;

    obj->rx_config.slaveAddress = (uint8_t)address;
    obj->tx_config.slaveAddress = (uint8_t)address;

    obj->rx_config.buffer = rx;
    obj->rx_config.bufferSize = rx_size;

    obj->tx_config.buffer = (void *)tx;
    obj->tx_config.bufferSize = tx_size;

    if (!obj->pending)
    {
        /* Validate input data and do appropriate action */
        if (tx_size)
        {
            obj->pending = (rx_size)
                ? _CYHAL_I2C_PENDING_TX_RX
                : _CYHAL_I2C_PENDING_TX;
            Cy_SCB_I2C_MasterWrite(obj->base, &obj->tx_config, &obj->context);
            /* Receive covered by interrupt handler - _cyhal_i2c_irq_handler() */
        }
        else if (rx_size)
        {
            obj->pending = _CYHAL_I2C_PENDING_RX;
            Cy_SCB_I2C_MasterRead(obj->base, &obj->rx_config, &obj->context);
        }
        else
        {
            return CYHAL_I2C_RSLT_ERR_TX_RX_BUFFERS_ARE_EMPTY;
        }
    }
    else
    {
        return CYHAL_I2C_RSLT_ERR_PREVIOUS_ASYNCH_PENDING;
    }
    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_i2c_abort_async(cyhal_i2c_t *obj)
{
    uint16_t timeout_us = 10000;
    if (obj->pending != _CYHAL_I2C_PENDING_NONE)
    {
        if (obj->pending == _CYHAL_I2C_PENDING_RX)
        {
            Cy_SCB_I2C_MasterAbortRead(obj->base, &obj->context);
        }
        else
        {
            Cy_SCB_I2C_MasterAbortWrite(obj->base, &obj->context);
        }
        /* After abort, next I2C operation can be initiated only after CY_SCB_I2C_MASTER_BUSY is cleared,
        *   so waiting for that event to occur. */
        while ((CY_SCB_I2C_MASTER_BUSY & obj->context.masterStatus) && (timeout_us != 0))
        {
            cyhal_system_delay_us(1);
            timeout_us--;
        }
        if (0 == timeout_us)
        {
            return CYHAL_I2C_RSLT_ERR_ABORT_ASYNC_TIMEOUT;
        }
        obj->pending = _CYHAL_I2C_PENDING_NONE;
    }
    return CY_RSLT_SUCCESS;
}

void cyhal_i2c_register_callback(cyhal_i2c_t *obj, cyhal_i2c_event_callback_t callback, void *callback_arg)
{
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    obj->callback_data.callback = (cy_israddress) callback;
    obj->callback_data.callback_arg = callback_arg;
    cyhal_system_critical_section_exit(savedIntrStatus);
    Cy_SCB_I2C_RegisterEventCallback(obj->base, _cyhal_i2c_cb_wrapper, &(obj->context));

    obj->irq_cause = CYHAL_I2C_EVENT_NONE;
}

void cyhal_i2c_enable_event(cyhal_i2c_t *obj, cyhal_i2c_event_t event, uint8_t intr_priority, bool enable)
{
    if (enable)
    {
        obj->irq_cause |= event;
    }
    else
    {
        obj->irq_cause &= ~event;
    }

    _cyhal_system_irq_t irqn = _CYHAL_SCB_IRQ_N[obj->resource.block_num];
    _cyhal_irq_set_priority(irqn, intr_priority);
}

cy_rslt_t cyhal_i2c_set_fifo_level(cyhal_i2c_t *obj, cyhal_i2c_fifo_type_t type, uint16_t level)
{
    return _cyhal_scb_set_fifo_level(obj->base, (cyhal_scb_fifo_type_t)type, level);
}

cy_rslt_t cyhal_i2c_enable_output(cyhal_i2c_t *obj, cyhal_i2c_output_t output, cyhal_source_t *source)
{
    return _cyhal_scb_enable_output(obj->resource, (cyhal_scb_output_t)output, source);
}

cy_rslt_t cyhal_i2c_disable_output(cyhal_i2c_t *obj, cyhal_i2c_output_t output)
{
    CY_UNUSED_PARAMETER(obj);
    return _cyhal_scb_disable_output((cyhal_scb_output_t)output);
}

#if defined(__cplusplus)
}
#endif

#endif /* CYHAL_DRIVER_AVAILABLE_I2C */
