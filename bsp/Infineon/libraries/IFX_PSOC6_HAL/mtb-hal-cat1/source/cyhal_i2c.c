/*******************************************************************************
* File Name: cyhal_i2c.c
*
* Description:
* Provides a high level interface for interacting with the Infineon I2C. This is
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

#include <stdlib.h>
#include <string.h>
#include "cyhal_i2c.h"
#include "cyhal_scb_common.h"
#include "cyhal_gpio.h"
#include "cyhal_hwmgr.h"
#include "cyhal_system.h"
#include "cyhal_syspm.h"
#include "cyhal_utils.h"
#include "cyhal_irq_impl.h"
#include "cyhal_clock.h"

#if (CYHAL_DRIVER_AVAILABLE_I2C)

#if defined(__cplusplus)
extern "C"
{
#endif

#define _CYHAL_I2C_PENDING_NONE              0
#define _CYHAL_I2C_PENDING_RX                1
#define _CYHAL_I2C_PENDING_TX                2
#define _CYHAL_I2C_PENDING_TX_RX             3

#define _CYHAL_I2C_MASTER_DEFAULT_FREQ       100000


static const _cyhal_buffer_info_t _cyhal_i2c_buff_info_default = {
    .addr = {NULL},
    .size = 0,
};

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

static cyhal_i2c_addr_event_t _cyhal_i2c_convert_addr_interrupt_cause(uint32_t pdl_cause)
{
    static const uint32_t status_map1[] =
    {
        (uint32_t)CYHAL_I2C_ADDR_EVENT_NONE,            // Default no event
        (uint32_t)CYHAL_I2C_GENERAL_CALL_EVENT,         // CY_SCB_I2C_READ_EVENT
        (uint32_t)CYHAL_I2C_ADDR_MATCH_EVENT,           // CY_SCB_I2C_ADDR_IN_FIFO_EVENT
    };
    uint32_t set1 = _cyhal_utils_convert_flags(status_map1, sizeof(status_map1) / sizeof(uint32_t), pdl_cause & 0xFF);

    return (cyhal_i2c_addr_event_t)(set1);
}

#if defined (COMPONENT_CAT5)
static void _cyhal_i2c_irq_handler(_cyhal_system_irq_t irqn)
#else
static void _cyhal_i2c_irq_handler(void)
#endif
{
    /* Save the old value and store it aftewards in case we get into a nested IRQ situation */
    /* Safe to cast away volatile because we don't expect this pointer to be changed while we're in here, they
     * just might change where the original pointer points */
    cyhal_i2c_t* old_irq_obj = (cyhal_i2c_t*)_cyhal_i2c_irq_obj;
#if defined (COMPONENT_CAT5)
    _cyhal_i2c_irq_obj = (cyhal_i2c_t*) _cyhal_scb_get_irq_obj(irqn);
#else
    _cyhal_i2c_irq_obj = (cyhal_i2c_t*) _cyhal_scb_get_irq_obj();
#endif
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

#if defined (COMPONENT_CAT5)
static void _cyhal_i2c0_irq_handler(void)
{
    _cyhal_i2c_irq_handler(scb_0_interrupt_IRQn);
}

static void _cyhal_i2c1_irq_handler(void)
{
    _cyhal_i2c_irq_handler(scb_1_interrupt_IRQn);
}

static void _cyhal_i2c2_irq_handler(void)
{
    _cyhal_i2c_irq_handler(scb_2_interrupt_IRQn);
}

static CY_SCB_IRQ_THREAD_CB_t _cyhal_irq_cb[3] = {_cyhal_i2c0_irq_handler, _cyhal_i2c1_irq_handler, _cyhal_i2c2_irq_handler};
#endif

static void _cyhal_i2c_cb_wrapper(uint32_t event)
{
    /* Safe to cast away volatile because we don't expect this pointer to be changed while we're in here, they
     * just might change where the original pointer points */
    cyhal_i2c_t *obj = (cyhal_i2c_t*)_cyhal_i2c_irq_obj;
    cyhal_i2c_event_t anded_events = (cyhal_i2c_event_t)(obj->irq_cause & (uint32_t)_cyhal_i2c_convert_interrupt_cause(event));
    if (anded_events)
    {
        /* Indicates read/write operations will be in a callback */
        obj->op_in_callback = true;
        cyhal_i2c_event_callback_t callback = (cyhal_i2c_event_callback_t) obj->callback_data.callback;
        callback(obj->callback_data.callback_arg, anded_events);
        obj->op_in_callback = false;
    }
}

static cy_en_scb_i2c_command_t _cyhal_i2c_cb_addr_wrapper(uint32_t event)
{
    /* Safe to cast away volatile because we don't expect this pointer to be changed while we're in here, they
     * just might change where the original pointer points */
    cyhal_i2c_t *obj = (cyhal_i2c_t*)_cyhal_i2c_irq_obj;
    cyhal_i2c_addr_event_t addr_events = (cyhal_i2c_addr_event_t)(obj->addr_irq_cause & (uint32_t)_cyhal_i2c_convert_addr_interrupt_cause(event));
    uint8_t device_address = 0;
    /* The default command is the ACK address. It can be overridden in an address callback */
    cyhal_i2c_command_rsp_t cmd = CYHAL_I2C_CMD_ACK;
    if (addr_events)
    {
        /* If ADDR_IN_FIFO_EVENT received, HAL need to read the device address using Cy_SCB_ReadRxFifo API as per I2C PDL documentation */
        if (0L != (CYHAL_I2C_ADDR_MATCH_EVENT & addr_events))
        {
            /* Slave address stored in PDL is shifted left by 1, so to get correct slave address need to do LSR by 1 */
            device_address = (Cy_SCB_ReadRxFifo(obj->base)) >> 1;
        }
        /* Indicates read/write operations will be in a callback */
        obj->op_in_callback = true;
        cyhal_i2c_address_callback_t callback = (cyhal_i2c_address_callback_t) obj->addr_callback_data.callback;
        cmd = callback(obj->addr_callback_data.callback_arg, addr_events, device_address);
        obj->op_in_callback = false;
    }
    return (cy_en_scb_i2c_command_t)cmd;
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

    // pins_blocks will contain bit representation of blocks, that are connected to specified pin
    // 1 block - 1 bit, so, for example, pin_blocks = 0x00000006 means that certain pin
    // can belong to next non-reserved blocks SCB2 and SCB1
    uint32_t pins_blocks = _CYHAL_SCB_AVAILABLE_BLOCKS_MASK;
    if (NC != sda)
    {
        pins_blocks &= _CYHAL_SCB_CHECK_AFFILIATION(sda, cyhal_pin_map_scb_i2c_sda);
    }
    if (NC != scl)
    {
        pins_blocks &= _CYHAL_SCB_CHECK_AFFILIATION(scl, cyhal_pin_map_scb_i2c_scl);
    }

    // One (or more) pin does not belong to any SCB instance or all corresponding SCB instances
    // are reserved
    if (0 == pins_blocks)
    {
        return CYHAL_I2C_RSLT_ERR_INVALID_PIN;
    }

    uint8_t found_block_idx = 0;
    while(((pins_blocks >> found_block_idx) & 0x1) == 0)
    {
        found_block_idx++;
    }

    cyhal_resource_inst_t i2c_rsc = { CYHAL_RSC_SCB, found_block_idx, 0 };

    /* Reserve the I2C */
    const cyhal_resource_pin_mapping_t *sda_map = _CYHAL_SCB_FIND_MAP_BLOCK(sda, cyhal_pin_map_scb_i2c_sda, &i2c_rsc);
    const cyhal_resource_pin_mapping_t *scl_map = _CYHAL_SCB_FIND_MAP_BLOCK(scl, cyhal_pin_map_scb_i2c_scl, &i2c_rsc);
    uint8_t scb_arr_index = 0;

    if ((NULL == sda_map) || (NULL == scl_map) || !_cyhal_utils_map_resources_equal(sda_map, scl_map))
    {
        return CYHAL_I2C_RSLT_ERR_INVALID_PIN;
    }

    cy_rslt_t result = cyhal_hwmgr_reserve(&i2c_rsc);

    if (result == CY_RSLT_SUCCESS)
    {
        scb_arr_index = _cyhal_scb_get_block_index(i2c_rsc.block_num);
        obj->base = _CYHAL_SCB_BASE_ADDRESSES[scb_arr_index];
        obj->resource = i2c_rsc;

        result = _cyhal_utils_reserve_and_connect(sda_map, (uint8_t)CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SDA);
        if (result == CY_RSLT_SUCCESS)
            obj->pin_sda = sda;
    }

    if (result == CY_RSLT_SUCCESS)
    {
        result = _cyhal_utils_reserve_and_connect(scl_map, (uint8_t)CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SCL);
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
    /* Initial value for read/write operations in callback */
    obj->op_in_callback = false;

    obj->rx_slave_buff = _cyhal_i2c_buff_info_default;
    obj->tx_slave_buff = _cyhal_i2c_buff_info_default;

    /* Configure I2C to operate */
    cy_rslt_t result = (cy_rslt_t)Cy_SCB_I2C_Init(obj->base, pdl_cfg, &(obj->context));
    uint8_t scb_arr_index = _cyhal_scb_get_block_index(obj->resource.block_num);

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
        obj->addr_callback_data.callback = NULL;
        obj->addr_callback_data.callback_arg = NULL;
        obj->irq_cause = CYHAL_I2C_EVENT_NONE;
        obj->addr_irq_cause = CYHAL_I2C_ADDR_EVENT_NONE;

        #if defined (COMPONENT_CAT5)
            Cy_SCB_RegisterInterruptCallback(obj->base, _cyhal_irq_cb[_CYHAL_SCB_IRQ_N[scb_arr_index]]);
            Cy_SCB_EnableInterrupt(obj->base);
        #endif

        _cyhal_irq_register(_CYHAL_SCB_IRQ_N[scb_arr_index], CYHAL_ISR_PRIORITY_DEFAULT, (cy_israddress)_cyhal_i2c_irq_handler);
        _cyhal_irq_enable(_CYHAL_SCB_IRQ_N[scb_arr_index]);
    }

    return result;
}

__STATIC_INLINE uint32_t _cyhal_i2c_slave_status(cyhal_i2c_t *obj)
{
    return Cy_SCB_I2C_SlaveGetStatus(obj->base, &obj->context);
}

__STATIC_INLINE void _cyhal_i2c_slave_clear_write_status(cyhal_i2c_t *obj)
{
    (void)Cy_SCB_I2C_SlaveClearWriteStatus(obj->base, &obj->context);
}

__STATIC_INLINE void _cyhal_i2c_slave_clear_read_status(cyhal_i2c_t *obj)
{
    (void)Cy_SCB_I2C_SlaveClearReadStatus(obj->base, &obj->context);
}

/* Wait for I2C slave status for some time (timeout > 0) or no wait (timeout == 0).
* The function returns CYHAL_I2C_RSLT_WARN_TIMEOUT in case timeout reached, otherwise - CY_RSLT_SUCCESS
* NOTE: When the read/write operation was called in a I2C callback function timeout is ignored
*/
static cy_rslt_t _cyhal_i2c_slave_wait_for_status(cyhal_i2c_t *obj, uint32_t i2c_status, uint32_t timeout)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    uint32_t timeout_us = _CYHAL_UTILS_US_PER_MS;

    if (!(obj->op_in_callback) && timeout > 0)
    {
        while (0U == (_cyhal_i2c_slave_status(obj) & i2c_status) && timeout > 0)
        {
            if (timeout_us > 0)
            {
                cyhal_system_delay_us(_CYHAL_UTILS_ONE_TIME_UNIT);
                --timeout_us;
            }
            else
            {
                timeout_us = _CYHAL_UTILS_US_PER_MS;
                --timeout;
            }
        }
        result = (timeout > 0) ? CY_RSLT_SUCCESS : CYHAL_I2C_RSLT_WARN_TIMEOUT;
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

    uint8_t scb_arr_index = _cyhal_scb_get_block_index(obj->resource.block_num);
    obj->base = _CYHAL_SCB_BASE_ADDRESSES[scb_arr_index];

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
        uint8_t scb_arr_index = _cyhal_scb_get_block_index(obj->resource.block_num);
        _cyhal_scb_update_instance_data(obj->resource.block_num, NULL, NULL);
        _cyhal_system_irq_t irqn = _CYHAL_SCB_IRQ_N[scb_arr_index];
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

    /* Prepare advanced configuration structure */
    cyhal_i2c_adv_cfg_t adv_cfg = {
        .basic_cfg = *cfg,
        /* Fill advanced parameters by default values */
        .address_mask = CYHAL_I2C_DEFAULT_ADDR_MASK,
        .enable_address_callback = false,
    };

    return cyhal_i2c_configure_adv(obj, &adv_cfg);
}

cy_rslt_t cyhal_i2c_configure_adv(cyhal_i2c_t *obj, const cyhal_i2c_adv_cfg_t *cfg)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != cfg);
    CY_ASSERT(NULL != &cfg->basic_cfg);

    (void) Cy_SCB_I2C_Disable(obj->base, &obj->context);

    cy_stc_scb_i2c_config_t _config_structure = _cyhal_i2c_default_config;

    _config_structure.i2cMode = (cfg->basic_cfg.is_slave)
        ? CY_SCB_I2C_SLAVE
        : CY_SCB_I2C_MASTER;

    _config_structure.slaveAddress  = (uint8_t)cfg->basic_cfg.address;

    if (cfg->basic_cfg.is_slave)
    {
        _config_structure.acceptAddrInFifo = cfg->enable_address_callback;
        _config_structure.ackGeneralAddr   = cfg->enable_address_callback;
        _config_structure.slaveAddressMask = cfg->address_mask;
    }

    cy_rslt_t result = (cy_rslt_t)Cy_SCB_I2C_Init(obj->base, &_config_structure, &(obj->context));
    if (CY_RSLT_SUCCESS == result)
    {
        /* Set data rate */
        uint32_t dataRate = _cyhal_i2c_set_peri_divider((void *)obj, true,
                                cfg->basic_cfg.frequencyhal_hz, cfg->basic_cfg.is_slave);
        if (dataRate == 0)
        {
            /* Deinit SCB block */
            Cy_SCB_I2C_DeInit(obj->base);
            /* Can not reach desired data rate */
            return CYHAL_I2C_RSLT_ERR_CAN_NOT_REACH_DR;
        }

    #if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
        (void) Cy_SCB_I2C_Enable(obj->base);
    #elif defined(COMPONENT_CAT2)
        (void) Cy_SCB_I2C_Enable(obj->base, &(obj->context));
    #endif
    }
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

cy_rslt_t cyhal_i2c_slave_abort_read(cyhal_i2c_t *obj)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;

    if (obj->context.state == CY_SCB_I2C_IDLE)
    {
        Cy_SCB_I2C_SlaveAbortRead(obj->base, &obj->context);
    }
    else
    {
        result = CYHAL_I2C_RSLT_WARN_DEVICE_BUSY;
    }
    return result;
}

cy_rslt_t cyhal_i2c_slave_config_write_buffer(cyhal_i2c_t *obj, const uint8_t *data, uint16_t size)
{
    cy_rslt_t result = CYHAL_I2C_RSLT_ERR_BAD_ARGUMENT;
    if (size > 0 && data != NULL)
    {
        if (obj->context.state == CY_SCB_I2C_IDLE)
        {
            Cy_SCB_I2C_SlaveConfigWriteBuf(obj->base, (uint8_t *)data, size, &obj->context);
            obj->rx_slave_buff.addr.u8 = (uint8_t *)data;
            obj->rx_slave_buff.size = size;
            result = CY_RSLT_SUCCESS;
        }
        else
        {
            result = CYHAL_I2C_RSLT_WARN_DEVICE_BUSY;
        }
    }
    return result;
}

cy_rslt_t cyhal_i2c_slave_config_read_buffer(cyhal_i2c_t *obj, uint8_t *data, uint16_t size)
{
    cy_rslt_t result = CYHAL_I2C_RSLT_ERR_BAD_ARGUMENT;
    if (size > 0 && data != NULL)
    {
        if (obj->context.state == CY_SCB_I2C_IDLE)
        {
            Cy_SCB_I2C_SlaveConfigReadBuf(obj->base, (uint8_t *)data, size, &obj->context);
            obj->tx_slave_buff.addr.u8 = data;
            obj->tx_slave_buff.size = size;
            result = CY_RSLT_SUCCESS;
        }
        else
        {
            result = CYHAL_I2C_RSLT_WARN_DEVICE_BUSY;
        }
    }
    return result;
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

cy_rslt_t cyhal_i2c_slave_read(cyhal_i2c_t *obj, uint8_t *dst_buff, uint16_t *size, uint32_t timeout)
{
    cy_rslt_t status = CYHAL_I2C_RSLT_ERR_BAD_ARGUMENT;

    if (obj->rx_slave_buff.addr.u8 == NULL)
    {
        status = CYHAL_I2C_RSLT_ERR_BUFFERS_NULL_PTR;
    }
    else if ((dst_buff != NULL) && (size != NULL))
    {
        /* Wait until the master completes writing */
        status = _cyhal_i2c_slave_wait_for_status(obj, CY_SCB_I2C_SLAVE_WR_CMPLT, timeout);

        if (CY_RSLT_SUCCESS == status)
        {
            *size = _CYHAL_SCB_BYTES_TO_COPY(cyhal_i2c_slave_readable(obj), *size);
            /* Check if the destination buffer is not a I2C RX buffer. */
            if (obj->rx_slave_buff.addr.u8 != dst_buff)
            {
                /* Copy command into the destination buffer */
                (void) memcpy((void *)dst_buff, (const void *)obj->rx_slave_buff.addr.u8, *size);
            }

            /* Wait for device set the state to IDLE */
            while (obj->context.state != CY_SCB_I2C_IDLE && !(obj->op_in_callback))
            {
                /* I2C PDL driver guarantee the slave will be in IDLE state
                    after the end of a transaction */
            }

            _cyhal_i2c_slave_clear_write_status(obj);
        }
    }
    return status;
}

cy_rslt_t cyhal_i2c_slave_write(cyhal_i2c_t *obj, const uint8_t *src_buff, uint16_t *size, uint32_t timeout)
{
    cy_rslt_t status = CYHAL_I2C_RSLT_ERR_BAD_ARGUMENT;

    if (obj->tx_slave_buff.addr.u8 == NULL)
    {
        status = CYHAL_I2C_RSLT_ERR_BUFFERS_NULL_PTR;
    }
    else if ((src_buff != NULL) && (size != NULL))
    {
        /* Wait for completion of a previous Master read transaction */
        while (obj->context.state != CY_SCB_I2C_IDLE && !(obj->op_in_callback))
        {
            /* I2C PDL driver guarantee the slave will be in IDLE state
                after the end of a previous transaction */
        }

        if (obj->context.state == CY_SCB_I2C_IDLE)
        {
            *size = _CYHAL_SCB_BYTES_TO_COPY(obj->tx_slave_buff.size, *size);
            /* Check if the source buffer is not a I2C TX buffer. */
            if (obj->tx_slave_buff.addr.u8 != src_buff)
            {
                /* Copy command into the TX buffer */
                (void) memcpy((void *)obj->tx_slave_buff.addr.u8, (const void *)src_buff, *size);
            }

            /* Wait until the master completes reading */
            status = _cyhal_i2c_slave_wait_for_status(obj, CY_SCB_I2C_SLAVE_RD_CMPLT, timeout);
            if (CY_RSLT_SUCCESS == status)
            {
                _cyhal_i2c_slave_clear_read_status(obj);
            }
        }
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

void cyhal_i2c_register_address_callback(cyhal_i2c_t *obj, cyhal_i2c_address_callback_t callback, void *callback_arg)
{
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    obj->addr_callback_data.callback = (cy_israddress) callback;
    obj->addr_callback_data.callback_arg = callback_arg;
    cyhal_system_critical_section_exit(savedIntrStatus);
    Cy_SCB_I2C_RegisterAddrCallback(obj->base, _cyhal_i2c_cb_addr_wrapper, &(obj->context));

    obj->addr_irq_cause = CYHAL_I2C_ADDR_EVENT_NONE;
}

void cyhal_i2c_enable_event(cyhal_i2c_t *obj, cyhal_i2c_event_t event, uint8_t intr_priority, bool enable)
{
    uint8_t scb_arr_index = _cyhal_scb_get_block_index(obj->resource.block_num);
    if (enable)
    {
        obj->irq_cause |= event;
    }
    else
    {
        obj->irq_cause &= ~event;
    }

    _cyhal_system_irq_t irqn = _CYHAL_SCB_IRQ_N[scb_arr_index];
    _cyhal_irq_set_priority(irqn, intr_priority);
}

void cyhal_i2c_enable_address_event(cyhal_i2c_t *obj, cyhal_i2c_addr_event_t event, uint8_t intr_priority, bool enable)
{
    uint8_t scb_arr_index = _cyhal_scb_get_block_index(obj->resource.block_num);
    if (enable)
    {
        obj->addr_irq_cause |= event;
    }
    else
    {
        obj->addr_irq_cause &= ~event;
    }

    _cyhal_system_irq_t irqn = _CYHAL_SCB_IRQ_N[scb_arr_index];
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

uint32_t cyhal_i2c_slave_readable(cyhal_i2c_t *obj)
{
    return Cy_SCB_I2C_SlaveGetWriteTransferCount(obj->base, &obj->context);
}

uint32_t cyhal_i2c_slave_writable(cyhal_i2c_t *obj)
{
    return (obj->tx_slave_buff.size - Cy_SCB_I2C_SlaveGetReadTransferCount(obj->base, &obj->context));
}

cy_rslt_t cyhal_i2c_clear(cyhal_i2c_t *obj)
{
    Cy_SCB_ClearRxFifo(obj->base);
    Cy_SCB_ClearTxFifo(obj->base);

    _cyhal_i2c_slave_clear_write_status(obj);
    _cyhal_i2c_slave_clear_read_status(obj);
    return CY_RSLT_SUCCESS;
}

#if defined(__cplusplus)
}
#endif

#endif /* CYHAL_DRIVER_AVAILABLE_I2C */
