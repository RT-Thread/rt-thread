/***************************************************************************//**
* \file cyhal_keyscan.c
*
* \brief
* Provides a high level interface for interacting with the Infineon KeyScan.
* This is a wrapper around the lower level PDL API.
*
********************************************************************************
* \copyright
* Copyright 2021-2022 Cypress Semiconductor Corporation (an Infineon company) or
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
 * \addtogroup group_hal_impl_keyscan KeyScan
 * \ingroup group_hal_impl
 * \{
 * On CAT1 devices, the KeyScan peripheral is clocked from the shared source CLK_MF.
 * If `NULL` is passed for the `clk` argument to \ref cyhal_keyscan_init, the KeyScan
 * HAL will automatically reserve and enable CLK_MF. If the KeyScan driver needs to be
 * used in combination with another driver that also requires CLK_MF, use the Clock
 * driver to initialize CLK_MF, then pass the resulting \ref cyhal_clock_t value
 * to \ref cyhal_keyscan_init and any other HAL driver that needs to share this clock.
 * \} group_hal_impl_keyscan
 */
#include <stdlib.h>
#include <string.h>
#include "cyhal_keyscan.h"
#include "cyhal_gpio.h"
#include "cyhal_hwmgr.h"
#include "cyhal_system.h"
#include "cyhal_syspm.h"
#include "cyhal_utils.h"
#include "cyhal_irq_impl.h"
#include "cyhal_clock.h"

#if (CYHAL_DRIVER_AVAILABLE_KEYSCAN)

#if defined(__cplusplus)
extern "C"
{
#endif

/* Internal defines */
#define _CYHAL_KEYSCAN_MAX_COLS         MXKEYSCAN_NUM_COLS_OUT
#define _CYHAL_KEYSCAN_MAX_ROWS         MXKEYSCAN_NUM_ROWS_IN

/* Internal prototypes */
static void _cyhal_keyscan_irq_handler(void);
static void _cyhal_keyscan_cb_wrapper(void);
static bool _cyhal_keyscan_pm_callback(cyhal_syspm_callback_state_t state, cyhal_syspm_callback_mode_t mode, void* callback_arg);
static cy_rslt_t _cyhal_keyscan_init_resources(cyhal_keyscan_t *obj, uint8_t num_columns, const cyhal_gpio_t *columns,
                                               uint8_t num_rows, const cyhal_gpio_t *rows, const cyhal_clock_t *clock);
static cy_rslt_t _cyhal_keyscan_init_hw(cyhal_keyscan_t *obj, cy_stc_ks_config_t *cfg);

/* Default KeyScan configuration */
static const cy_stc_ks_config_t _cyhal_keyscan_default_config = {
    .macroDownDebCnt            = 3,
    .macroUpDebCnt              = 3,
    .microDebCnt                = 3,
    .noofRows                   = 0,
    .noofColumns                = 0,
    .ghostEnable                = true,
    .cpuWakeupEnable            = true,
    .clkStayOn                  = true
};

/* LPM transition callback data */
static cyhal_syspm_callback_data_t _cyhal_keyscan_syspm_callback_data =
{
    .callback = &_cyhal_keyscan_pm_callback,
    .states = (cyhal_syspm_callback_state_t)(CYHAL_SYSPM_CB_CPU_DEEPSLEEP | CYHAL_SYSPM_CB_SYSTEM_HIBERNATE),
    .next = NULL,
    .args = NULL,
    .ignore_modes = (cyhal_syspm_callback_mode_t)(CYHAL_SYSPM_CHECK_READY | CYHAL_SYSPM_AFTER_DS_WFI_TRANSITION),
};

/* Base addresses */
static MXKEYSCAN_Type *const _cyhal_keyscan_base[] =
{
#if (CY_IP_MXKEYSCAN_INSTANCES == 1)
    MXKEYSCAN,
#else
    #error "Unhandled keyscan instance count"
#endif
};

/* Record of init structs */
static cyhal_keyscan_t *_cyhal_keyscan_config_structs[1];

static void _cyhal_keyscan_irq_handler(void)
{
    cyhal_keyscan_t *obj = _cyhal_keyscan_config_structs[0];
    uint32_t int_status;
    cy_rslt_t result = Cy_Keyscan_GetInterruptMaskedStatus(MXKEYSCAN, &int_status);
    CY_ASSERT(CY_RSLT_SUCCESS == result);
    CY_UNUSED_PARAMETER(result);
    if(0u != (MXKEYSCAN_INTR_FIFO_THRESH_DONE & int_status))
    {
        Cy_Keyscan_Interrupt_Handler(obj->base, &(obj->context));
    }

    if(0u != (MXKEYSCAN_INTR_KEY_EDGE_DONE & int_status))
    {
        /* KEY_EDGE_DONE is just to wake the CPU from sleep, we should ignore it */
        Cy_Keyscan_ClearInterrupt(MXKEYSCAN, MXKEYSCAN_INTR_KEY_EDGE_DONE);
    }
}

static void _cyhal_keyscan_cb_wrapper(void)
{
    cyhal_keyscan_t *obj = _cyhal_keyscan_config_structs[0];
    uint32_t hal_event = CYHAL_KEYSCAN_EVENT_ACTION_DETECTED |
                        ((obj->context.curNumElements == obj->context.maxNumElements) ? CYHAL_KEYSCAN_EVENT_BUFFER_FULL : 0);
    cyhal_keyscan_event_t anded_events = (cyhal_keyscan_event_t)(obj->irq_cause & hal_event);
    if (anded_events)
    {
        cyhal_keyscan_event_callback_t callback = (cyhal_keyscan_event_callback_t) obj->callback_data.callback;
        callback(obj->callback_data.callback_arg, anded_events);
    }
}

static bool _cyhal_keyscan_pm_callback(cyhal_syspm_callback_state_t state, cyhal_syspm_callback_mode_t mode, void* callback_arg)
{
    CY_UNUSED_PARAMETER(state);
    CY_UNUSED_PARAMETER(callback_arg);

    uint32_t readMask;
    cyhal_keyscan_t *obj = _cyhal_keyscan_config_structs[0];
    Cy_Keyscan_GetInterruptMask(obj->base, &readMask);

    switch(mode)
    {
        case CYHAL_SYSPM_AFTER_TRANSITION:
        {
            Cy_Keyscan_EnableClockStayOn(obj->base);
            Cy_Keyscan_SetInterruptMask(obj->base, readMask & ~MXKEYSCAN_INTR_KEY_EDGE_DONE);
            break;
        }
        case CYHAL_SYSPM_BEFORE_TRANSITION:
        {
            Cy_Keyscan_DisableClockStayOn(obj->base);
            Cy_Keyscan_SetInterruptMask(obj->base, readMask | MXKEYSCAN_INTR_KEY_EDGE_DONE);
            break;
        }
        default:
        {
            CY_ASSERT(false);
            break;
        }
    }
    return true;
}

static cy_rslt_t _cyhal_keyscan_init_resources(cyhal_keyscan_t *obj, uint8_t num_columns, const cyhal_gpio_t *columns,
                                uint8_t num_rows, const cyhal_gpio_t *rows, const cyhal_clock_t *clock)
{
    // Explicitly marked not allocated resources as invalid to prevent freeing them.
    obj->resource.type = CYHAL_RSC_INVALID;
    obj->irq_cause = CYHAL_KEYSCAN_EVENT_NONE;
    for (uint8_t idx=0; idx < _CYHAL_KEYSCAN_MAX_COLS; idx++) obj->columns[idx] = NC;
    for (uint8_t idx=0; idx < _CYHAL_KEYSCAN_MAX_ROWS; idx++) obj->rows[idx] = NC;

    cy_rslt_t result = CY_RSLT_SUCCESS;

    if ((num_columns > _CYHAL_KEYSCAN_MAX_COLS) || (num_rows > _CYHAL_KEYSCAN_MAX_ROWS ))
        result = CYHAL_KEYSCAN_RSLT_ERR_INVALID_ARG;

    // Reserve the column pins
    for (uint8_t idx=0; idx < num_columns; idx++)
    {
        if (result == CY_RSLT_SUCCESS)
        {
            const cyhal_resource_pin_mapping_t* column_map = _CYHAL_UTILS_GET_RESOURCE(columns[idx], cyhal_pin_map_keyscan_ks_col);
            result = (column_map == NULL) ? CYHAL_KEYSCAN_RSLT_ERR_INVALID_PIN : CY_RSLT_SUCCESS;
            if (result == CY_RSLT_SUCCESS)
            {
                if(CYHAL_RSC_INVALID == obj->resource.type)
                {
                    obj->resource.type = CYHAL_RSC_KEYSCAN;
                    obj->resource.block_num = column_map->block_num;
                    obj->resource.channel_num = 0;
                    result = cyhal_hwmgr_reserve(&(obj->resource));
                }
                /* Directly, instead of using _cyhal_utils_map_resource, checking whether pin belong to used block
                 * (and not checking channel_num) as cyhal_pin_map_keyscan_ks_row / cyhal_pin_map_keyscan_ks_col maps
                 * each column as separate channel */
                else if (obj->resource.block_num != column_map->block_num)
                {
                    result = CYHAL_KEYSCAN_RSLT_ERR_INVALID_PIN;
                }
            }
            if (result == CY_RSLT_SUCCESS)
            {
                /* For this block, we reuse the channel_num field to store the bit index on the keyscan.
                 * Pull off and check that value */
                uint8_t bit_index = column_map->channel_num;
                if (bit_index != idx) /* PDL only support contiguous indices that start from 0 */
                {
                    result = CYHAL_KEYSCAN_RSLT_ERR_INVALID_PIN;
                }
            }
            if (result == CY_RSLT_SUCCESS)
            {
                result = _cyhal_utils_reserve_and_connect(column_map, CYHAL_PIN_MAP_DRIVE_MODE_KEYSCAN_KS_COL);
            }
            if (result == CY_RSLT_SUCCESS)
            {
                obj->columns[idx] = columns[idx];
            }
        }
    }

    // Reserve the row pins
    for (uint8_t idx=0; idx < num_rows; idx++)
    {
        if (result == CY_RSLT_SUCCESS)
        {
            const cyhal_resource_pin_mapping_t* row_map = _CYHAL_UTILS_GET_RESOURCE(rows[idx], cyhal_pin_map_keyscan_ks_row);
            result = (row_map == NULL) ? CYHAL_KEYSCAN_RSLT_ERR_INVALID_PIN : CY_RSLT_SUCCESS;
            /* We must have at least one column, so we know that obj->resource will be set if we reach
             * here in a non-error state. */
            /* Directly, instead of using _cyhal_utils_map_resource, checking whether pin belong to used block
                 * (and not checking channel_num) as cyhal_pin_map_keyscan_ks_row / cyhal_pin_map_keyscan_ks_col maps
                 * each column as separate channel */
            if (result == CY_RSLT_SUCCESS && (obj->resource.block_num != row_map->block_num))
            {
                result = CYHAL_KEYSCAN_RSLT_ERR_INVALID_PIN;
            }
            if (result == CY_RSLT_SUCCESS)
            {
                /* For this block, we reuse the channel num field to store the bit index on the keyscan.
                 * Pull off and check that value
                 */
                uint8_t bit_index = row_map->channel_num;
                if (bit_index != idx) /* PDL only support contiguous indices that start from 0 */
                {
                    result = CYHAL_KEYSCAN_RSLT_ERR_INVALID_PIN;
                }
            }
            if (result == CY_RSLT_SUCCESS)
            {
                result = _cyhal_utils_reserve_and_connect(row_map, CYHAL_PIN_MAP_DRIVE_MODE_KEYSCAN_KS_ROW);
            }
            if (result == CY_RSLT_SUCCESS)
            {
                obj->rows[idx] = rows[idx];
            }
        }
    }

    // Clock allocation
    if (result == CY_RSLT_SUCCESS)
    {
        if (clock == NULL)
        {
            cyhal_clock_t clock_keyscan;
            result = cyhal_clock_reserve(&clock_keyscan, &CYHAL_CLOCK_MF);
            if (CY_RSLT_SUCCESS == result)
            {
                obj->is_clock_owned = true;
                obj->clock = clock_keyscan;
                result = cyhal_clock_set_enabled(&clock_keyscan, true, true);
            }
        }
        else if(clock->block == CYHAL_CLOCK_BLOCK_MF)
        {
            obj->clock = *clock;
        }
        else /* CLK_MF is the only valid clock source */
        {
            result = CYHAL_KEYSCAN_RSLT_ERR_INVALID_ARG;
        }
    }

    return result;
}

static cy_rslt_t _cyhal_keyscan_init_hw(cyhal_keyscan_t *obj, cy_stc_ks_config_t *cfg)
{
    obj->base = _cyhal_keyscan_base[obj->resource.block_num];

    cy_rslt_t result = Cy_Keyscan_Init(obj->base, cfg, &(obj->context));
    if (result == CY_RSLT_SUCCESS)
    {
        _cyhal_keyscan_config_structs[0] = obj;
        _cyhal_syspm_register_peripheral_callback(&_cyhal_keyscan_syspm_callback_data);

        obj->callback_data.callback = NULL;
        obj->callback_data.callback_arg = NULL;
        obj->irq_cause = CYHAL_KEYSCAN_EVENT_NONE;

        /* The PDL driver relies on being notified whenever FIFO_THRESH_DONE happens,
         * so enable this and leave it enabled. The HAL-level event enable/disable
         * just determines whether the application callback is invoked.
         */
        Cy_Keyscan_SetInterruptMask(obj->base, MXKEYSCAN_INTR_FIFO_THRESH_DONE);

        result = Cy_Keyscan_Register_Callback(_cyhal_keyscan_cb_wrapper, &(obj->context));
    }

    if (result == CY_RSLT_SUCCESS)
    {
        _cyhal_irq_register(keyscan_interrupt_IRQn, CYHAL_ISR_PRIORITY_DEFAULT, _cyhal_keyscan_irq_handler);
        _cyhal_irq_enable(keyscan_interrupt_IRQn);

        result = Cy_Keyscan_FlushEvents(obj->base, &(obj->context));
    }

    if (result == CY_RSLT_SUCCESS)
    {
        result = Cy_Keyscan_Enable(obj->base, &(obj->context));
    }

    return result;
}

cy_rslt_t cyhal_keyscan_init(cyhal_keyscan_t *obj, uint8_t num_columns, const cyhal_gpio_t *columns,
                                uint8_t num_rows, const cyhal_gpio_t *rows, const cyhal_clock_t *clock)
{
    CY_ASSERT(NULL != obj);
    memset(obj, 0, sizeof(cyhal_keyscan_t));

    obj->dc_configured = false;

    cy_rslt_t result = _cyhal_keyscan_init_resources(obj, num_columns, columns, num_rows, rows, clock);

    if (result == CY_RSLT_SUCCESS)
    {
        cy_stc_ks_config_t config = _cyhal_keyscan_default_config;
        config.noofRows = num_rows;
        config.noofColumns = num_columns;
        result = _cyhal_keyscan_init_hw(obj, &config);
    }

    if (result != CY_RSLT_SUCCESS)
    {
        cyhal_keyscan_free(obj);
    }

    return result;
}

cy_rslt_t cyhal_keyscan_init_cfg(cyhal_keyscan_t *obj, const cyhal_keyscan_configurator_t *cfg)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != cfg);
    CY_ASSERT(NULL != cfg->config);
    memset(obj, 0, sizeof(cyhal_keyscan_t));

    obj->resource = *cfg->resource;
    obj->clock = *cfg->clock;
    obj->is_clock_owned = false;
    obj->dc_configured = true;

    for (uint8_t idx=0; idx < _CYHAL_KEYSCAN_MAX_COLS; idx++) obj->columns[idx] = NC;
    for (uint8_t idx=0; idx < _CYHAL_KEYSCAN_MAX_ROWS; idx++) obj->rows[idx] = NC;

    cy_rslt_t result = _cyhal_keyscan_init_hw(obj, cfg->config);

    if (result != CY_RSLT_SUCCESS)
    {
        cyhal_keyscan_free(obj);
    }

    return result;
}

void cyhal_keyscan_free(cyhal_keyscan_t *obj)
{
    CY_ASSERT(NULL != obj);

    if (obj->resource.type != CYHAL_RSC_INVALID)
    {
        _cyhal_irq_free(keyscan_interrupt_IRQn);
        _cyhal_keyscan_config_structs[0] = NULL;

        if (obj->base != NULL)
        {
            Cy_Keyscan_SetInterruptMask(obj->base, 0);
            Cy_Keyscan_Disable(obj->base, &(obj->context));
            Cy_Keyscan_DeInit(obj->base, &(obj->context));
        }

        if (false == obj->dc_configured)
        {
            cyhal_hwmgr_free(&(obj->resource));
        }
    }

    if (obj->is_clock_owned)
    {
        cyhal_clock_free(&(obj->clock));
    }

    if (false == obj->dc_configured)
    {
        // Free the column pins
        for (uint8_t idx=0; idx < _CYHAL_KEYSCAN_MAX_COLS; idx++)
        {
            _cyhal_utils_release_if_used(&(obj->columns[idx]));
        }
        // Free the row pins
        for (uint8_t idx=0; idx < _CYHAL_KEYSCAN_MAX_ROWS; idx++)
        {
            _cyhal_utils_release_if_used(&(obj->rows[idx]));
        }
    }
}

cy_rslt_t cyhal_keyscan_read(cyhal_keyscan_t *obj, uint8_t* count, cyhal_keyscan_action_t* keys)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    bool hasPending = true;
    uint8_t eventCount = 0;
    cy_stc_key_event eventNext;

    while ((CY_KEYSCAN_SUCCESS == status) && (hasPending) && (eventCount < *count))
    {
        status = Cy_Keyscan_EventsPending(obj->base, &hasPending, &(obj->context));
        if (CY_KEYSCAN_SUCCESS == status && hasPending)
        {
            status = Cy_Keyscan_GetNextEvent(obj->base, &eventNext, &(obj->context));
            if (CY_KEYSCAN_SUCCESS == status)
            {
                /* There are several special keycode IDs that aren't currently exposed through the HAL;
                 * don't include those in the events we give the user. See cy_en_ks_keycode_t */
                 bool isSpecialKeycode = (KEYSCAN_KEYCODE_GHOST == eventNext.keyCode)
                                      || (KEYSCAN_KEYCODE_NONE == eventNext.keyCode)
                                      || (KEYSCAN_KEYCODE_END_OF_SCAN_CYCLE == eventNext.keyCode)
                                      || (KEYSCAN_KEYCODE_ROLLOVER == eventNext.keyCode);
                if (false == isSpecialKeycode)
                {
                    // Note: Discard eventNext.scanCycleFlag
                    keys[eventCount].keycode = eventNext.keyCode;
                    keys[eventCount].action = (eventNext.upDownFlag == 0)
                        ? CYHAL_KEYSCAN_ACTION_PRESS
                        : CYHAL_KEYSCAN_ACTION_RELEASE;

                    eventCount++;
                }
            }
        }
    }
    *count = eventCount;

    return status;
}

void cyhal_keyscan_register_callback(cyhal_keyscan_t *obj, cyhal_keyscan_event_callback_t callback, void *callback_arg)
{
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    obj->callback_data.callback = (cy_israddress) callback;
    obj->callback_data.callback_arg = callback_arg;
    cyhal_system_critical_section_exit(savedIntrStatus);
}

void cyhal_keyscan_enable_event(cyhal_keyscan_t *obj, cyhal_keyscan_event_t event, uint8_t intr_priority, bool enable)
{
    if (enable)
    {
        obj->irq_cause |= event;
    }
    else
    {
        obj->irq_cause &= ~event;
    }

    _cyhal_irq_set_priority(keyscan_interrupt_IRQn, intr_priority);
}

#if defined(__cplusplus)
}
#endif

#endif /* CYHAL_DRIVER_AVAILABLE_KEYSCAN */
