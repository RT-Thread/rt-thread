/*******************************************************************************
* File Name: cyhal_ezi2c.c
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
#include "cyhal_ezi2c.h"
#include "cyhal_scb_common.h"
#include "cyhal_gpio.h"
#include "cyhal_system_impl.h"
#include "cyhal_hwmgr.h"
#include "cyhal_utils.h"
#include "cyhal_irq_impl.h"
#include "cyhal_clock.h"

#if (CYHAL_DRIVER_AVAILABLE_EZI2C)

#if defined(__cplusplus)
extern "C"
{
#endif

static inline cyhal_ezi2c_status_t _cyhal_ezi2c_convert_activity_status(uint32_t pdl_status)
{
    /* Structure to map EZI2C (PDL) status on HAL EZI2C status */
    static const uint32_t status_map[] =
    {
        0U,                                  // Default value
        (uint32_t)CYHAL_EZI2C_STATUS_READ1,  // CY_SCB_EZI2C_STATUS_READ1
        (uint32_t)CYHAL_EZI2C_STATUS_WRITE1, // CY_SCB_EZI2C_STATUS_WRITE1
        (uint32_t)CYHAL_EZI2C_STATUS_READ2,  // CY_SCB_EZI2C_STATUS_READ2
        (uint32_t)CYHAL_EZI2C_STATUS_WRITE2, // CY_SCB_EZI2C_STATUS_WRITE2
        (uint32_t)CYHAL_EZI2C_STATUS_BUSY,   // CY_SCB_EZI2C_STATUS_BUSY
        (uint32_t)CYHAL_EZI2C_STATUS_ERR,    // CY_SCB_EZI2C_STATUS_ERR
    };

    cyhal_ezi2c_status_t hal_status = (cyhal_ezi2c_status_t)_cyhal_utils_convert_flags(
        status_map, sizeof(status_map) / sizeof(uint32_t), pdl_status);
    if ((hal_status & (CYHAL_EZI2C_STATUS_BUSY | CYHAL_EZI2C_STATUS_ERR)) == 0)
    {
        hal_status |= CYHAL_EZI2C_STATUS_OK;
    }
    return hal_status;
}

#if defined (COMPONENT_CAT5)
static void _cyhal_ezi2c_irq_handler(_cyhal_system_irq_t irqn)
#else
static void _cyhal_ezi2c_irq_handler(void)
#endif
{
#if defined (COMPONENT_CAT5)
    cyhal_ezi2c_t *obj = (cyhal_ezi2c_t*) _cyhal_scb_get_irq_obj(irqn);
#else
    cyhal_ezi2c_t *obj = (cyhal_ezi2c_t*) _cyhal_scb_get_irq_obj();
#endif
    Cy_SCB_EZI2C_Interrupt(obj->base, &(obj->context));

    /* Check if callback is registered */
    cyhal_ezi2c_event_callback_t callback = (cyhal_ezi2c_event_callback_t) obj->callback_data.callback;
    if (callback != NULL)
    {
        /* Check status of EZI2C and verify which events are enabled */
        cyhal_ezi2c_status_t status = cyhal_ezi2c_get_activity_status(obj);
        if(status & obj->irq_cause)
        {
            (void) (callback) (obj->callback_data.callback_arg, (cyhal_ezi2c_status_t)(status & obj->irq_cause));
        }
    }
}

#if defined (COMPONENT_CAT5)
static void _cyhal_ezi2c0_irq_handler(void)
{
    _cyhal_ezi2c_irq_handler(scb_0_interrupt_IRQn);
}

static void _cyhal_ezi2c1_irq_handler(void)
{
    _cyhal_ezi2c_irq_handler(scb_1_interrupt_IRQn);
}

static void _cyhal_ezi2c2_irq_handler(void)
{
    _cyhal_ezi2c_irq_handler(scb_2_interrupt_IRQn);
}

static CY_SCB_IRQ_THREAD_CB_t _cyhal_irq_cb[3] = {_cyhal_ezi2c0_irq_handler, _cyhal_ezi2c1_irq_handler, _cyhal_ezi2c2_irq_handler};
#endif

static bool _cyhal_ezi2c_pm_callback_instance(void *obj_ptr, cyhal_syspm_callback_state_t state, cy_en_syspm_callback_mode_t pdl_mode)
{
    cyhal_ezi2c_t *obj = (cyhal_ezi2c_t*)(obj_ptr);

    cy_stc_syspm_callback_params_t ezi2c_callback_params = {
        .base = (void *) (obj->base),
        .context = (void *) &(obj->context)
    };

    bool allow = true;
    switch(state)
    {
        case CYHAL_SYSPM_CB_CPU_DEEPSLEEP:
            allow = (CY_SYSPM_SUCCESS == Cy_SCB_EZI2C_DeepSleepCallback(&ezi2c_callback_params, pdl_mode));
            break;
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
        case CYHAL_SYSPM_CB_SYSTEM_HIBERNATE:
            allow = (CY_SYSPM_SUCCESS == Cy_SCB_EZI2C_HibernateCallback(&ezi2c_callback_params, pdl_mode));
            break;
#endif
        default:
            CY_ASSERT(false);
            break;
    }
    return allow;
}

static cy_rslt_t _cyhal_ezi2c_setup_resources(cyhal_ezi2c_t *obj, cyhal_gpio_t sda, cyhal_gpio_t scl, const cyhal_clock_t *clk)
{
    /* Explicitly marked not allocated resources as invalid to prevent freeing them. */
    obj->resource.type = CYHAL_RSC_INVALID;
    obj->pin_scl = CYHAL_NC_PIN_VALUE;
    obj->pin_sda = CYHAL_NC_PIN_VALUE;
    obj->is_clock_owned = false;
    obj->two_addresses = false;

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
        return CYHAL_EZI2C_RSLT_ERR_INVALID_PIN;
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
    if ((NULL == sda_map) || (NULL == scl_map) || !_cyhal_utils_map_resources_equal(sda_map, scl_map))
    {
        return CYHAL_EZI2C_RSLT_ERR_INVALID_PIN;
    }

    cy_rslt_t result = cyhal_hwmgr_reserve(&i2c_rsc);

    /* Reserve the SDA pin */
    if (result == CY_RSLT_SUCCESS)
    {
        obj->resource = i2c_rsc;

        result = _cyhal_utils_reserve_and_connect(sda_map, (uint8_t)CYHAL_PIN_MAP_DRIVE_MODE_SCB_I2C_SDA);
        if (result == CY_RSLT_SUCCESS)
            obj->pin_sda = sda;
    }

    /* Reserve the SCL pin */
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
            result = _cyhal_utils_allocate_clock(&(obj->clock), &i2c_rsc, CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT, true);
            obj->is_clock_owned = (CY_RSLT_SUCCESS == result);
        }
        else
        {
            obj->clock = *clk;
        }
    }

    return result;
}

static cy_rslt_t _cyhal_ezi2c_init_hw(cyhal_ezi2c_t *obj, const cy_stc_scb_ezi2c_config_t* pdl_cfg)
{
    uint8_t scb_arr_index = _cyhal_scb_get_block_index(obj->resource.block_num);
    obj->base = _CYHAL_SCB_BASE_ADDRESSES[scb_arr_index];
    obj->two_addresses = (pdl_cfg->numberOfAddresses == CY_SCB_EZI2C_TWO_ADDRESSES);

    /* Configure I2C to operate */
    cy_rslt_t result = Cy_SCB_EZI2C_Init(obj->base, pdl_cfg, &(obj->context));

    if (CY_RSLT_SUCCESS == result)
    {
        _cyhal_scb_update_instance_data(obj->resource.block_num, (void*)obj, &_cyhal_ezi2c_pm_callback_instance);
        obj->callback_data.callback = NULL;
        obj->callback_data.callback_arg = NULL;
        obj->irq_cause = 0;

        #if defined (COMPONENT_CAT5)
            Cy_SCB_RegisterInterruptCallback(obj->base, _cyhal_irq_cb[_CYHAL_SCB_IRQ_N[scb_arr_index]]);
        #endif

        _cyhal_irq_register(_CYHAL_SCB_IRQ_N[scb_arr_index], CYHAL_ISR_PRIORITY_DEFAULT, (cy_israddress)_cyhal_ezi2c_irq_handler);
    }

    return result;
}

static void _cyhal_ezi2c_setup_and_enable(cyhal_ezi2c_t *obj, const cyhal_ezi2c_slave_cfg_t *slave1_cfg, const cyhal_ezi2c_slave_cfg_t *slave2_cfg)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != slave1_cfg);

    uint8_t scb_arr_index = _cyhal_scb_get_block_index(obj->resource.block_num);

    /* Configure buffer for communication with master */
    Cy_SCB_EZI2C_SetBuffer1(obj->base, slave1_cfg->buf, slave1_cfg->buf_size, slave1_cfg->buf_rw_boundary, &(obj->context));
    /* Check if user set one or two addresses */
    if (obj->two_addresses && (NULL != slave2_cfg))
    {
        Cy_SCB_EZI2C_SetBuffer2(obj->base, slave2_cfg->buf, slave2_cfg->buf_size, slave2_cfg->buf_rw_boundary, &(obj->context));
    }

    #if defined (COMPONENT_CAT5)
        Cy_SCB_EnableInterrupt(obj->base);
    #endif

    _cyhal_irq_enable(_CYHAL_SCB_IRQ_N[scb_arr_index]);
    /* Enable EZI2C to operate */
    Cy_SCB_EZI2C_Enable(obj->base);
}

cy_rslt_t cyhal_ezi2c_init(cyhal_ezi2c_t *obj, cyhal_gpio_t sda, cyhal_gpio_t scl, const cyhal_clock_t *clk, const cyhal_ezi2c_cfg_t *cfg)
{
    CY_ASSERT(NULL != obj);
    memset(obj, 0, sizeof(cyhal_ezi2c_t));

    /* Validate input configuration structure */
    if ((0 == cfg->slave1_cfg.slave_address) || ((cfg->two_addresses) && (0 == cfg->slave2_cfg.slave_address)))
    {
        return CYHAL_EZI2C_RSLT_ERR_CHECK_USER_CONFIG;
    }

    obj->dc_configured = false;
    /* Populate configuration structure */
    const cy_stc_scb_ezi2c_config_t pdl_config =
    {
        .numberOfAddresses   = cfg->two_addresses ? CY_SCB_EZI2C_TWO_ADDRESSES : CY_SCB_EZI2C_ONE_ADDRESS,
        .slaveAddress1       = cfg->slave1_cfg.slave_address,
        .slaveAddress2       = cfg->two_addresses ? cfg->slave2_cfg.slave_address : 0,
        .subAddressSize      = (cy_en_scb_ezi2c_sub_addr_size_t)cfg->sub_address_size,
        .enableWakeFromSleep = cfg->enable_wake_from_sleep,
    };

    cy_rslt_t result = _cyhal_ezi2c_setup_resources(obj, sda, scl, clk);

    if (CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_ezi2c_init_hw(obj, &pdl_config);
    }

    if (CY_RSLT_SUCCESS == result)
    {
        uint32_t dataRate = _cyhal_i2c_set_peri_divider((void *)obj, false, (uint32_t)cfg->data_rate, true);
        if (dataRate == 0)
        {
            /* Can not reach desired data rate */
            return CYHAL_EZI2C_RSLT_ERR_CAN_NOT_REACH_DR;
        }
    }

    if (result == CY_RSLT_SUCCESS)
    {
        _cyhal_ezi2c_setup_and_enable(obj, &cfg->slave1_cfg, &cfg->slave2_cfg);
    }

    if (result != CY_RSLT_SUCCESS)
    {
        cyhal_ezi2c_free(obj);
    }
    return result;
}

void cyhal_ezi2c_free(cyhal_ezi2c_t *obj)
{
    CY_ASSERT(NULL != obj);

    if (NULL != obj->base)
    {
        Cy_SCB_EZI2C_Disable(obj->base, &obj->context);
        Cy_SCB_EZI2C_DeInit(obj->base);
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

cyhal_ezi2c_status_t cyhal_ezi2c_get_activity_status(cyhal_ezi2c_t *obj)
{
    return _cyhal_ezi2c_convert_activity_status(Cy_SCB_EZI2C_GetActivity(obj->base, &(obj->context)));
}

void cyhal_ezi2c_register_callback(cyhal_ezi2c_t *obj, cyhal_ezi2c_event_callback_t callback, void *callback_arg)
{
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    obj->callback_data.callback = (cy_israddress) callback;
    obj->callback_data.callback_arg = callback_arg;
    cyhal_system_critical_section_exit(savedIntrStatus);
}

void cyhal_ezi2c_enable_event(cyhal_ezi2c_t *obj, cyhal_ezi2c_status_t event, uint8_t intr_priority, bool enable)
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

cy_rslt_t cyhal_ezi2c_init_cfg(cyhal_ezi2c_t *obj, const cyhal_ezi2c_configurator_t *cfg,
                               const cyhal_ezi2c_slave_cfg_t *slave1_cfg, const cyhal_ezi2c_slave_cfg_t *slave2_cfg)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != cfg);
    CY_ASSERT(NULL != cfg->config);

    obj->resource = *cfg->resource;
    obj->clock = *cfg->clock;
    obj->is_clock_owned = false;
    obj->two_addresses = false;
    obj->dc_configured = true;

    cy_rslt_t result = _cyhal_ezi2c_init_hw(obj, cfg->config);

    if (CY_RSLT_SUCCESS == result)
    {
        _cyhal_ezi2c_setup_and_enable(obj, slave1_cfg, slave2_cfg);
    }

    return result;
}

#if defined(__cplusplus)
}
#endif

#endif /* CYHAL_DRIVER_AVAILABLE_EZI2C */
