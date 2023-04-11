/***************************************************************************//**
* \file cyhal_scb_common.c
*
* \brief
* Provides a struct definitions for configuration resources in the SCB (UART, I2C, SPI).
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

#include "cyhal_scb_common.h"
#include "cyhal_hwmgr.h"
#include "cyhal_syspm.h"
#include "cyhal_clock.h"
#include "cyhal_interconnect.h"
#include "cyhal_peri_common.h"

#if (_CYHAL_DRIVER_AVAILABLE_SCB)

#if defined(__cplusplus)
extern "C"
{
#endif

const uint32_t _CYHAL_SCB_AVAILABLE_BLOCKS_MASK =
{
#ifdef SCB0
    1 << 0u
#endif
#ifdef SCB1
    | 1 << 1u
#endif
#ifdef SCB2
    | 1 << 2u
#endif
#ifdef SCB3
    | 1 << 3u
#endif
#ifdef SCB4
    | 1 << 4u
#endif
#ifdef SCB5
    | 1 << 5u
#endif
#ifdef SCB6
    | 1 << 6u
#endif
#ifdef SCB7
    | 1 << 7u
#endif
#ifdef SCB8
    | 1 << 8u
#endif
#ifdef SCB9
    | 1 << 9u
#endif
#ifdef SCB10
    | 1 << 10u
#endif
#ifdef SCB11
    | 1 << 11u
#endif
#ifdef SCB12
    | 1 << 12u
#endif
#ifdef SCB13
    | 1 << 13u
#endif
#ifdef SCB14
    | 1 << 14u
#endif
#ifdef SCB15
    | 1 << 15u
#endif
};

const uint8_t _CYHAL_SCB_BASE_ADDRESS_INDEX[_SCB_ARRAY_SIZE] =
{
#ifdef SCB0
    0u,
#endif
#ifdef SCB1
    1u,
#endif
#ifdef SCB2
    2u,
#endif
#ifdef SCB3
    3u,
#endif
#ifdef SCB4
    4u,
#endif
#ifdef SCB5
    5u,
#endif
#ifdef SCB6
    6u,
#endif
#ifdef SCB7
    7u,
#endif
#ifdef SCB8
    8u,
#endif
#ifdef SCB9
    9u,
#endif
#ifdef SCB10
    10u,
#endif
#ifdef SCB11
    11u,
#endif
#ifdef SCB12
    12u,
#endif
#ifdef SCB13
    13u,
#endif
#ifdef SCB14
    14u,
#endif
#ifdef SCB15
    15u,
#endif
};

CySCB_Type* const _CYHAL_SCB_BASE_ADDRESSES[_SCB_ARRAY_SIZE] =
{
#ifdef SCB0
    SCB0,
#endif
#ifdef SCB1
    SCB1,
#endif
#ifdef SCB2
    SCB2,
#endif
#ifdef SCB3
    SCB3,
#endif
#ifdef SCB4
    SCB4,
#endif
#ifdef SCB5
    SCB5,
#endif
#ifdef SCB6
    SCB6,
#endif
#ifdef SCB7
    SCB7,
#endif
#ifdef SCB8
    SCB8,
#endif
#ifdef SCB9
    SCB9,
#endif
#ifdef SCB10
    SCB10,
#endif
#ifdef SCB11
    SCB11,
#endif
#ifdef SCB12
    SCB12,
#endif
#ifdef SCB13
    SCB13,
#endif
#ifdef SCB14
    SCB14,
#endif
#ifdef SCB15
    SCB15,
#endif
};

const _cyhal_system_irq_t _CYHAL_SCB_IRQ_N[_SCB_ARRAY_SIZE] =
{
#ifdef SCB0
    scb_0_interrupt_IRQn,
#endif
#ifdef SCB1
    scb_1_interrupt_IRQn,
#endif
#ifdef SCB2
    scb_2_interrupt_IRQn,
#endif
#ifdef SCB3
    scb_3_interrupt_IRQn,
#endif
#ifdef SCB4
    scb_4_interrupt_IRQn,
#endif
#ifdef SCB5
    scb_5_interrupt_IRQn,
#endif
#ifdef SCB6
    scb_6_interrupt_IRQn,
#endif
#ifdef SCB7
    scb_7_interrupt_IRQn,
#endif
#ifdef SCB8
    scb_8_interrupt_IRQn,
#endif
#ifdef SCB9
    scb_9_interrupt_IRQn,
#endif
#ifdef SCB10
    scb_10_interrupt_IRQn,
#endif
#ifdef SCB11
    scb_11_interrupt_IRQn,
#endif
#ifdef SCB12
    scb_12_interrupt_IRQn,
#endif
#ifdef SCB13
    scb_13_interrupt_IRQn,
#endif
#ifdef SCB14
    scb_14_interrupt_IRQn,
#endif
#ifdef SCB15
    scb_15_interrupt_IRQn,
#endif
};

/** The configuration structs for the resource in use on each SCB block */
static void *_cyhal_scb_config_structs[_SCB_ARRAY_SIZE];
/** The callback to use for each scb instance */
static bool (*_cyhal_scb_config_pm_callback[_SCB_ARRAY_SIZE]) (void *obj_ptr, cyhal_syspm_callback_state_t state, cy_en_syspm_callback_mode_t pdl_mode);

static uint8_t _cyhal_scb_get_block_from_irqn(_cyhal_system_irq_t irqn)
{
    uint8_t scb_block_num = 0;
    switch (irqn)
    {
    #ifdef SCB0
        case scb_0_interrupt_IRQn:
            scb_block_num = 0;
            break;
    #endif
    #ifdef SCB1
        case scb_1_interrupt_IRQn:
            scb_block_num = 1;
            break;
    #endif
    #ifdef SCB2
        case scb_2_interrupt_IRQn:
            scb_block_num = 2;
            break;
    #endif
    #ifdef SCB3
        case scb_3_interrupt_IRQn:
            scb_block_num = 3;
            break;
    #endif
    #ifdef SCB4
        case scb_4_interrupt_IRQn:
            scb_block_num = 4;
            break;
    #endif
    #ifdef SCB5
        case scb_5_interrupt_IRQn:
            scb_block_num = 5;
            break;
    #endif
    #ifdef SCB6
        case scb_6_interrupt_IRQn:
            scb_block_num = 6;
            break;
    #endif
    #ifdef SCB7
        case scb_7_interrupt_IRQn:
            scb_block_num = 7;
            break;
    #endif
    #ifdef SCB8
        case scb_8_interrupt_IRQn:
            scb_block_num = 8;
            break;
    #endif
    #ifdef SCB9
        case scb_9_interrupt_IRQn:
            scb_block_num = 9;
            break;
    #endif
    #ifdef SCB10
        case scb_10_interrupt_IRQn:
            scb_block_num = 10;
            break;
    #endif
    #ifdef SCB11
        case scb_11_interrupt_IRQn:
            scb_block_num = 11;
            break;
    #endif
    #ifdef SCB12
        case scb_12_interrupt_IRQn:
            scb_block_num = 12;
            break;
    #endif
    #ifdef SCB13
        case scb_13_interrupt_IRQn:
            scb_block_num = 13;
            break;
    #endif
    #ifdef SCB14
        case scb_14_interrupt_IRQn:
            scb_block_num = 14;
            break;
    #endif
    #ifdef SCB15
        case scb_15_interrupt_IRQn:
            scb_block_num = 15;
            break;
    #endif
    #if (_SCB_ARRAY_SIZE > 16)
    #error "Unhandled scb count"
    #endif
        default:
            CY_ASSERT(false); // Should never be called with a non-SCB IRQn
            scb_block_num = _CYHAL_SCB_BLOCK_ID_INVALID;
    }

    return _cyhal_scb_get_block_index(scb_block_num);
}

uint8_t _cyhal_scb_get_block_index(uint8_t scb_block_num)
{
    uint8_t arr_index = _CYHAL_SCB_BLOCK_ID_INVALID;
    for (uint8_t instance_idx = 0; instance_idx < _SCB_ARRAY_SIZE; instance_idx++)
    {
        if (_CYHAL_SCB_BASE_ADDRESS_INDEX[instance_idx] == scb_block_num)
        {
            arr_index = instance_idx;
            break;
        }
    }
    return arr_index;
}

#if defined (COMPONENT_CAT5)
void *_cyhal_scb_get_irq_obj(_cyhal_system_irq_t irqn)
{
    uint8_t block = _cyhal_scb_get_block_from_irqn(irqn);
    return _cyhal_scb_config_structs[block];
}
#else
void *_cyhal_scb_get_irq_obj(void)
{
    _cyhal_system_irq_t irqn = _cyhal_irq_get_active();
    if ((_cyhal_system_irq_t)unconnected_IRQn == irqn)
    {
        return NULL;
    }
    else
    {
        uint8_t block = _cyhal_scb_get_block_from_irqn(irqn);
        return _cyhal_scb_config_structs[block];
    }
}
#endif

/* Peripheral clock values for different I2C speeds according PDL API Reference Guide */

/* Must be between 1.55 MHz and 12.8 MHz for running i2c master at 100KHz   */
#define _CYHAL_SCB_PERI_CLOCK_SLAVE_STD      8000000
/* Must be between 7.82 MHz and 15.38 MHz for running i2c master at 400KHz  */
#define _CYHAL_SCB_PERI_CLOCK_SLAVE_FST      12500000

/* Must be between 15.84 MHz and 89.0 MHz for running i2c master at 1MHz */
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
#define _CYHAL_SCB_PERI_CLOCK_SLAVE_FSTP     50000000
#elif defined(COMPONENT_CAT2)
#define _CYHAL_SCB_PERI_CLOCK_SLAVE_FSTP     24000000
#elif defined(COMPONENT_CAT5)
#define _CYHAL_SCB_PERI_CLOCK_SLAVE_FSTP     96000000
#endif

/* Must be between 1.55 MHz and 3.2 MHz for running i2c slave at 100KHz     */
#define _CYHAL_SCB_PERI_CLOCK_MASTER_STD     2000000
/* Must be between 7.82 MHz and 10 MHz for running i2c slave at 400KHz      */
#define _CYHAL_SCB_PERI_CLOCK_MASTER_FST     8500000
/* Must be between 14.32 MHz and 25.8 MHz for running i2c slave at 1MHz  */
#define _CYHAL_SCB_PERI_CLOCK_MASTER_FSTP    20000000

uint32_t _cyhal_i2c_set_peri_divider(void *obj, bool is_i2c, uint32_t freq, bool is_slave)
{
    CySCB_Type *base = is_i2c ? ((cyhal_i2c_t *)obj)->base : ((cyhal_ezi2c_t *)obj)->base;
    uint32_t block_num = is_i2c ? ((cyhal_i2c_t *)obj)->resource.block_num : ((cyhal_ezi2c_t *)obj)->resource.block_num;
    cyhal_clock_t *clock = is_i2c ? &(((cyhal_i2c_t *)obj)->clock) : &(((cyhal_ezi2c_t *)obj)->clock);
    bool is_clock_owned = is_i2c ? ((cyhal_i2c_t *)obj)->is_clock_owned : ((cyhal_ezi2c_t *)obj)->is_clock_owned;

    /* Return the actual data rate on success, 0 otherwise */
    uint32_t data_rate = 0;
    if (freq != 0)
    {
        uint32_t peri_freq = 0;
        if (freq <= CY_SCB_I2C_STD_DATA_RATE)
        {
            peri_freq = is_slave ? _CYHAL_SCB_PERI_CLOCK_SLAVE_STD : _CYHAL_SCB_PERI_CLOCK_MASTER_STD;
        }
        else if (freq <= CY_SCB_I2C_FST_DATA_RATE)
        {
            peri_freq = is_slave ? _CYHAL_SCB_PERI_CLOCK_SLAVE_FST : _CYHAL_SCB_PERI_CLOCK_MASTER_FST;
        }
        else if (freq <= CY_SCB_I2C_FSTP_DATA_RATE)
        {
            peri_freq = is_slave ? _CYHAL_SCB_PERI_CLOCK_SLAVE_FSTP : _CYHAL_SCB_PERI_CLOCK_MASTER_FSTP;
        }

        if (peri_freq > 0 && _cyhal_utils_peri_pclk_assign_divider(
            _cyhal_scb_get_clock_index(block_num), clock) == CY_SYSCLK_SUCCESS)
        {
            cy_rslt_t status = CY_RSLT_SUCCESS;

            if (is_clock_owned)
            {
                status = cyhal_clock_set_enabled(clock, false, false);
                if (status == CY_RSLT_SUCCESS)
                {
                    status = cyhal_clock_set_frequency(clock, peri_freq, NULL);
                }
                if (status == CY_RSLT_SUCCESS)
                {
                    status = cyhal_clock_set_enabled(clock, true, false);
                }
            }

            if(status == CY_RSLT_SUCCESS)
            {
                data_rate = (is_slave)
                    ? Cy_SCB_I2C_GetDataRate(base, cyhal_clock_get_frequency(clock))
                    : Cy_SCB_I2C_SetDataRate(base, freq, cyhal_clock_get_frequency(clock));
            }
        }
    }
    return data_rate;
}

const cyhal_resource_pin_mapping_t* _cyhal_scb_find_map(cyhal_gpio_t pin, const cyhal_resource_pin_mapping_t *pin_map,
        size_t count, const cyhal_resource_inst_t *block_res)
{
    for (size_t i = 0; i < count; i++)
    {
        if (pin == pin_map[i].pin)
        {
            /* Block is already found, check if certain pin can work for provided block  */
            if ((NULL != block_res) && (CYHAL_RSC_SCB == block_res->type))
            {
                if (_cyhal_utils_map_resource_equal(block_res, &(pin_map[i]), false))
                {
                    return &pin_map[i];
                }
            }
            /* No block provided */
            else
            {
                cyhal_resource_inst_t rsc = { CYHAL_RSC_SCB, pin_map[i].block_num, pin_map[i].channel_num };
                if (CY_RSLT_SUCCESS == cyhal_hwmgr_reserve(&rsc))
                {
                    cyhal_hwmgr_free(&rsc);
                    return &pin_map[i];
                }
            }
        }
    }
    return NULL;
}

uint32_t _cyhal_scb_check_pin_affiliation(cyhal_gpio_t pin, const cyhal_resource_pin_mapping_t *pin_map,
        size_t count)
{
    uint32_t bitband_blocks = 0;
    for (size_t i = 0; i < count; i++)
    {
        if (pin == pin_map[i].pin)
        {
            cyhal_resource_inst_t rsc = { CYHAL_RSC_SCB, pin_map[i].block_num, pin_map[i].channel_num };
            if (CY_RSLT_SUCCESS == cyhal_hwmgr_reserve(&rsc))
            {
                cyhal_hwmgr_free(&rsc);
                bitband_blocks |= 1 << pin_map[i].block_num;
            }
        }
    }
    return bitband_blocks;
}

cy_rslt_t _cyhal_scb_set_fifo_level(CySCB_Type *base, cyhal_scb_fifo_type_t type, uint16_t level)
{
    if(!CY_SCB_IS_TRIGGER_LEVEL_VALID(base, level))
        return CYHAL_SCB_RSLT_ERR_BAD_ARGUMENT;

    if(type == CYHAL_SCB_FIFO_RX)
    {
        SCB_RX_FIFO_CTRL(base) &= ~SCB_RX_FIFO_CTRL_TRIGGER_LEVEL_Msk;
        SCB_RX_FIFO_CTRL(base) |= _VAL2FLD(SCB_RX_FIFO_CTRL_TRIGGER_LEVEL, level);

        return CY_RSLT_SUCCESS;
    }
    else if(type == CYHAL_SCB_FIFO_TX)
    {
        SCB_TX_FIFO_CTRL(base) &= ~SCB_TX_FIFO_CTRL_TRIGGER_LEVEL_Msk;
        SCB_TX_FIFO_CTRL(base) |= _VAL2FLD(SCB_TX_FIFO_CTRL_TRIGGER_LEVEL, level);

        return CY_RSLT_SUCCESS;
    }

    return CYHAL_SCB_RSLT_ERR_BAD_ARGUMENT;
}

cy_rslt_t _cyhal_scb_enable_output(cyhal_resource_inst_t resource, cyhal_scb_output_t output, cyhal_source_t *source)
{
// All PSoC™ 6 devices have scb triggers but not all PSoC™ 4 devices do
#if ((defined(CY_IP_MXSCB) && !defined(COMPONENT_CAT2)) || defined(CY_DEVICE_PSOC4AMC) || defined(CY_DEVICE_PSOC4AS3) || defined(CY_DEVICE_PSOC4AS4))
    // This just returns a proper cyhal_source_t. Use _cyhal_scb_set_fifo_level
    // to actually set level.
    cyhal_internal_source_t src_int;
    uint8_t scb_arr_index = _cyhal_scb_get_block_index(resource.block_num);
    if(output == CYHAL_SCB_OUTPUT_TRIGGER_RX_FIFO_LEVEL_REACHED)
    {
        src_int = (cyhal_internal_source_t)(_CYHAL_TRIGGER_SCB0_TR_RX_REQ + scb_arr_index);
        *source = (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE(src_int, CYHAL_SIGNAL_TYPE_EDGE);
        return CY_RSLT_SUCCESS;
    }
    // This just returns a proper cyhal_source_t. Use _cyhal_scb_set_fifo_level
    // to actually set level.
    else if(output == CYHAL_SCB_OUTPUT_TRIGGER_TX_FIFO_LEVEL_REACHED)
    {
        src_int = (cyhal_internal_source_t)(_CYHAL_TRIGGER_SCB0_TR_TX_REQ + scb_arr_index);
        *source = (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE(src_int, CYHAL_SIGNAL_TYPE_EDGE);
        return CY_RSLT_SUCCESS;
    }

    return CYHAL_SCB_RSLT_ERR_BAD_ARGUMENT;
#else
    CY_UNUSED_PARAMETER(resource);
    CY_UNUSED_PARAMETER(output);
    CY_UNUSED_PARAMETER(source);
    return CYHAL_INTERCONNECT_RSLT_INVALID_CONNECTION;
#endif
}

cy_rslt_t _cyhal_scb_disable_output(cyhal_scb_output_t output)
{
// All PSoC™ 6 devices have scb triggers but not all PSoC™ 4 devices do
#if (defined(CY_IP_MXSCB) || defined(CY_DEVICE_PSOC4AMC) || defined(CY_DEVICE_PSOC4AS3) || defined(CY_DEVICE_PSOC4AS4))
    // Noop: Use _cyhal_scb_set_fifo_level to actually set level
    if (output == CYHAL_SCB_OUTPUT_TRIGGER_RX_FIFO_LEVEL_REACHED ||
        output == CYHAL_SCB_OUTPUT_TRIGGER_TX_FIFO_LEVEL_REACHED)
    {
        return CY_RSLT_SUCCESS;
    }

    return CYHAL_SCB_RSLT_ERR_BAD_ARGUMENT;
#else
    CY_UNUSED_PARAMETER(output);
    return CYHAL_INTERCONNECT_RSLT_INVALID_CONNECTION;
#endif
}

static bool __cyhal_scb_pm_transition_pending_value = false;

bool _cyhal_scb_pm_transition_pending(void)
{
    return __cyhal_scb_pm_transition_pending_value;
}

static bool _cyhal_scb_pm_callback_index(uint8_t index, cyhal_syspm_callback_state_t state, cy_en_syspm_callback_mode_t pdl_mode)
{
    void *obj = _cyhal_scb_config_structs[index];
    cyhal_scb_instance_pm_callback callback = _cyhal_scb_config_pm_callback[index];
    return ((NULL != obj) && (callback != NULL)) ? callback(obj, state, pdl_mode) : true;
}

static bool _cyhal_scb_pm_callback_common(cyhal_syspm_callback_state_t state, cyhal_syspm_callback_mode_t mode, void* callback_arg)
{
    CY_UNUSED_PARAMETER(callback_arg);
    bool allow = true;
    cy_en_syspm_callback_mode_t pdl_mode = _cyhal_utils_convert_haltopdl_pm_mode(mode);
    for (uint8_t instance_idx = 0; instance_idx < _SCB_ARRAY_SIZE; instance_idx++)
    {
        allow = _cyhal_scb_pm_callback_index(instance_idx, state, pdl_mode);

        if (!allow && mode == CYHAL_SYSPM_CHECK_READY)
        {
            for (uint8_t revert_idx = 0; revert_idx < instance_idx; revert_idx++)
            {
                _cyhal_scb_pm_callback_index(revert_idx, state, CY_SYSPM_CHECK_FAIL);
            }
            break;
        }
    }

    if (mode == CYHAL_SYSPM_CHECK_FAIL || mode == CYHAL_SYSPM_AFTER_TRANSITION)
    {
        __cyhal_scb_pm_transition_pending_value = false;
    }
    else if (mode == CYHAL_SYSPM_CHECK_READY && allow)
    {
        __cyhal_scb_pm_transition_pending_value = true;
    }
    return allow;
}

cyhal_syspm_callback_data_t _cyhal_scb_pm_callback_data =
{
    .callback = &_cyhal_scb_pm_callback_common,
    .states = (cyhal_syspm_callback_state_t)(CYHAL_SYSPM_CB_CPU_DEEPSLEEP | CYHAL_SYSPM_CB_SYSTEM_HIBERNATE),
    .args = NULL,
    .next = NULL,
    .ignore_modes = (cyhal_syspm_callback_mode_t)0,
};

void _cyhal_scb_update_instance_data(uint8_t block_num, void *obj, cyhal_scb_instance_pm_callback pm_callback)
{
    uint8_t scb_arr_index = _cyhal_scb_get_block_index(block_num);

    _cyhal_scb_config_structs[scb_arr_index] = obj;
    _cyhal_scb_config_pm_callback[scb_arr_index] = pm_callback;

    int count = 0;
    for (uint8_t i = 0; i < _SCB_ARRAY_SIZE; i++)
    {
        if (NULL != _cyhal_scb_config_structs[i])
        {
            if (count == 1)
            {
                return;
            }
            count++;
        }
    }

    if (count == 0)
    {
        CY_ASSERT(obj == NULL);
        #if (CYHAL_DRIVER_AVAILABLE_SYSPM)
        _cyhal_syspm_unregister_peripheral_callback(&_cyhal_scb_pm_callback_data);
        #endif
    }
    else if (count == 1 && obj != NULL)
    {
        #if (CYHAL_DRIVER_AVAILABLE_SYSPM)
        _cyhal_syspm_register_peripheral_callback(&_cyhal_scb_pm_callback_data);
        #endif
    }
}

#if defined(__cplusplus)
}
#endif

#endif /* _CYHAL_DRIVER_AVAILABLE_SCB */
