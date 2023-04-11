/***************************************************************************//**
* \file cyhal_flash.c
*
* Description:
* Provides a high level interface for interacting with the Infineon Flash. This
* is wrapper around the lower level PDL API.
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

#include "cyhal_hwmgr.h"
#include "cyhal_hw_types.h"
#include "cyhal_flash.h"
#include "cy_utils.h"
#include "cyhal_syspm.h"
#include "cyhal_utils_impl.h"
#include "cyhal_irq_impl.h"
#include <string.h>

#if (CYHAL_DRIVER_AVAILABLE_FLASH)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

typedef cy_en_flashdrv_status_t (*_cyhal_flash_operation)(uint32_t rowAddr, const uint32_t* data);

static bool _cyhal_flash_pm_callback(cyhal_syspm_callback_state_t state, cyhal_syspm_callback_mode_t mode, void* callback_arg);

#if defined(CY_IP_M7CPUSS)
#define _CYHAL_INTERNAL_MEMORY_BLOCKS (4u)
#elif (CY_EM_EEPROM_SIZE > 0)
#define _CYHAL_INTERNAL_MEMORY_BLOCKS (2u)
#else
#define _CYHAL_INTERNAL_MEMORY_BLOCKS (1u)
#endif

static const cyhal_flash_block_info_t _CYHAL_FLASH_BLOCKS[_CYHAL_INTERNAL_MEMORY_BLOCKS] =
{
#if defined(CY_IP_M7CPUSS)
    /* Each flash area is divided into two regions: A "large" region with 2KB sectors and a
     * "small" region with 128b sectors. The flash can be configured in either single- or
     * double-bank mode. In double-bank mode, the flash is divided into two sub-regions such
     * that it is possible to read from one region while writing to another region. Because
     * dual-bank mode is highly device specific, for simplicity we stick to single-bank mode
     * in the portable HAL driver */
    // Large main flash region, 32KB sectors
    {
        .start_address = CY_FLASH_LG_SBM_BASE,
        .size = CY_FLASH_LG_SBM_SIZE,
        .sector_size = 32768u,
        .page_size = 8u,
        .erase_value = 0xFFU,
    },
    // Small main flash region, 8KB sectors
    {
        .start_address = CY_FLASH_SM_SBM_BASE,
        .size = CY_FLASH_SM_SBM_SIZE,
        .sector_size = 8192u,
        .page_size = 8u,
        .erase_value = 0xFFU,
    },
    // Large wflash region, 32KB sectors
    {
        .start_address = CY_WFLASH_LG_SBM_BASE,
        .size = CY_WFLASH_LG_SBM_SIZE,
        .sector_size = 2048u, /* Hard-coded in the IP */
        .page_size = 4u,
        .erase_value = 0xFFU,
    },
    // Small wflash region, 128B sectors
    {
        .start_address = CY_WFLASH_SM_SBM_BASE,
        .size = CY_WFLASH_SM_SBM_SIZE,
        .sector_size = 128u,
        .page_size = 4u,
        .erase_value = 0xFFU,
    },
#else
    // Main Flash
    {
        .start_address = CY_FLASH_BASE,
        .size = CY_FLASH_SIZE,
        .sector_size = CY_FLASH_SIZEOF_ROW,
        .page_size = CY_FLASH_SIZEOF_ROW,
        .erase_value = 0x00U,
    },
    // Working Flash
#if (CY_EM_EEPROM_SIZE > 0)
    {
        .start_address = CY_EM_EEPROM_BASE,
        .size = CY_EM_EEPROM_SIZE,
        .sector_size = CY_FLASH_SIZEOF_ROW,
        .page_size = CY_FLASH_SIZEOF_ROW,
        .erase_value = 0x00U,
    },
#endif
#endif /* CY_IP_M7CPUSS or other */
};

static bool _cyhal_flash_pending_pm_change = false;

static uint16_t _cyhal_flash_init_count = 0;
static cyhal_syspm_callback_data_t _cyhal_flash_internal_pm_cb = {
    .callback = _cyhal_flash_pm_callback,
    .states = (cyhal_syspm_callback_state_t)(CYHAL_SYSPM_CB_CPU_SLEEP | CYHAL_SYSPM_CB_CPU_DEEPSLEEP | CYHAL_SYSPM_CB_SYSTEM_HIBERNATE | CYHAL_SYSPM_CB_SYSTEM_LOW),
    .next = NULL,
    .args = NULL,
    .ignore_modes = (cyhal_syspm_callback_mode_t)(CYHAL_SYSPM_BEFORE_TRANSITION | CYHAL_SYSPM_AFTER_DS_WFI_TRANSITION),
};

static inline cy_rslt_t _cyhal_flash_convert_status(uint32_t pdl_status)
{
    return (pdl_status == CY_FLASH_DRV_OPERATION_STARTED) ? CY_RSLT_SUCCESS : pdl_status;
}

#if defined(CY_IP_S8SRSSLT) && CY_FLASH_NON_BLOCKING_SUPPORTED
static void _cyhal_flash_irq_handler(void)
{
    (void) Cy_Flash_ResumeWrite();
}
#endif

static bool _cyhal_flash_pm_callback(cyhal_syspm_callback_state_t state, cyhal_syspm_callback_mode_t mode, void* callback_arg)
{
    CY_UNUSED_PARAMETER(state);
    CY_UNUSED_PARAMETER(callback_arg);
    bool allow = true;

    switch (mode)
    {
        case CYHAL_SYSPM_CHECK_READY:
            _cyhal_flash_pending_pm_change = true;
            #if defined(CY_IP_MXS40SRSS) || defined(CY_IP_M7CPUSS) || CY_FLASH_NON_BLOCKING_SUPPORTED
            if (CY_RSLT_SUCCESS != Cy_Flash_IsOperationComplete())
            {
                _cyhal_flash_pending_pm_change = false;
                allow = false;
            }
            #endif
            break;
        case CYHAL_SYSPM_AFTER_TRANSITION:
        case CYHAL_SYSPM_CHECK_FAIL:
            _cyhal_flash_pending_pm_change = false;
            break;
        default:
            /* Don't care */
            break;
    }

    return allow;
}

static inline bool _cyhal_flash_is_flash_address(uint32_t address)
{
    /* We don't use a for loop because the comparison values are all compile-time constants
     * so this should collapse to a maximum of 8 compare operations - 2 or 4 on most devices */
    return
#if ((_CYHAL_INTERNAL_MEMORY_BLOCKS) > 3)
    (_CYHAL_FLASH_BLOCKS[3].start_address <= address
        && address < (_CYHAL_FLASH_BLOCKS[3].start_address + _CYHAL_FLASH_BLOCKS[3].size)) ||
#endif
#if ((_CYHAL_INTERNAL_MEMORY_BLOCKS) > 2)
    (_CYHAL_FLASH_BLOCKS[2].start_address <= address
        && address < (_CYHAL_FLASH_BLOCKS[2].start_address + _CYHAL_FLASH_BLOCKS[2].size)) ||
#endif
#if ((_CYHAL_INTERNAL_MEMORY_BLOCKS) > 1)
    (_CYHAL_FLASH_BLOCKS[1].start_address <= address
        && address < (_CYHAL_FLASH_BLOCKS[1].start_address + _CYHAL_FLASH_BLOCKS[1].size)) ||
#endif
    (_CYHAL_FLASH_BLOCKS[0].start_address <= address
        && address < (_CYHAL_FLASH_BLOCKS[0].start_address + _CYHAL_FLASH_BLOCKS[0].size));
}
static inline bool _cyhal_flash_is_sram_address(uint32_t address)
{
    return ((CY_SRAM_BASE <= address) && (address < (CY_SRAM_BASE + CY_SRAM_SIZE)));
}

static cy_rslt_t _cyhal_flash_run_operation(
    _cyhal_flash_operation operation, uint32_t address, const uint32_t* data, bool clearCache)
{
    cy_rslt_t status;
    if (_cyhal_flash_pending_pm_change)
        status = CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    else
    {
        status = (_cyhal_flash_is_sram_address((uint32_t)data))
            ? (cy_rslt_t)_cyhal_flash_convert_status((cy_rslt_t)operation(address, data))
            : CYHAL_FLASH_RSLT_ERR_ADDRESS;
#if defined(CY_IP_M7CPUSS) /* PDL automatically clears cache when necessary */
        CY_UNUSED_PARAMETER(clearCache);
#else
        if (clearCache)
        {
            Cy_SysLib_ClearFlashCacheAndBuffer();
        }
#endif
    }

    return status;
}

cy_rslt_t cyhal_flash_init(cyhal_flash_t *obj)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);

#if defined(CY_IP_S8SRSSLT) && CY_FLASH_NON_BLOCKING_SUPPORTED
    /* Configure Flash interrupt */
    _cyhal_irq_register(cpuss_interrupt_spcif_IRQn, 0u, &_cyhal_flash_irq_handler);
    _cyhal_irq_enable(cpuss_interrupt_spcif_IRQn);
#endif
    if(_cyhal_flash_init_count == 0)
    {
        _cyhal_syspm_register_peripheral_callback(&_cyhal_flash_internal_pm_cb);
#if defined(CY_IP_M7CPUSS)
        Cy_Flash_Init();
        Cy_Flashc_WorkWriteEnable();
#endif
    }
    _cyhal_flash_init_count++;
    return CY_RSLT_SUCCESS;
}

void cyhal_flash_free(cyhal_flash_t *obj)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);
#if defined(CY_IP_S8SRSSLT) && CY_FLASH_NON_BLOCKING_SUPPORTED
    _cyhal_irq_free(cpuss_interrupt_spcif_IRQn);
#endif
    CY_ASSERT(_cyhal_flash_init_count > 0);
    _cyhal_flash_init_count--;
    if(_cyhal_flash_init_count == 0)
    {
        _cyhal_syspm_unregister_peripheral_callback(&_cyhal_flash_internal_pm_cb);
#if defined(CY_IP_M7CPUSS)
        Cy_Flashc_WorkWriteDisable();
#endif
    }
}

void cyhal_flash_get_info(const cyhal_flash_t *obj, cyhal_flash_info_t *info)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);

    info->block_count = _CYHAL_INTERNAL_MEMORY_BLOCKS;
    info->blocks = &_CYHAL_FLASH_BLOCKS[0];
}

cy_rslt_t cyhal_flash_read(cyhal_flash_t *obj, uint32_t address, uint8_t *data, size_t size)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);

    if (!_cyhal_flash_is_flash_address(address) || !_cyhal_flash_is_flash_address(address + size - 1))
    {
        return CYHAL_FLASH_RSLT_ERR_ADDRESS;
    }
    memcpy((void *)data, (void *)address, size);
    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_flash_erase(cyhal_flash_t *obj, uint32_t address)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);
#if defined(CY_IP_MXS40SRSS) || defined(CY_IP_M7CPUSS)
    cy_rslt_t status = CYHAL_FLASH_RSLT_ERR_ADDRESS;

    if (_cyhal_flash_pending_pm_change)
        status = CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    else if (_cyhal_flash_is_flash_address(address))
    {
#if defined(CY_IP_M7CPUSS)
        /* This IP does not support row-at-a-time erase */
        status = (cy_rslt_t)_cyhal_flash_convert_status(Cy_Flash_EraseSector(address));
        /* PDL automatically clears cache when necessary */
#else
        status = (cy_rslt_t)_cyhal_flash_convert_status(Cy_Flash_EraseRow(address));
        Cy_SysLib_ClearFlashCacheAndBuffer();
#endif
    }
    return status;
#else
    CY_UNUSED_PARAMETER(address);
    return CYHAL_FLASH_RSLT_ERR_NOT_SUPPORTED;
#endif
}

cy_rslt_t cyhal_flash_write(cyhal_flash_t *obj, uint32_t address, const uint32_t* data)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);

#if defined(CY_IP_M7CPUSS)
    /* This IP does not support a bundled write (erase + program) operation. Instead,
      * it is necessary to perform an erase operation followed by a program operation.
      */
    CY_UNUSED_PARAMETER(address);
    CY_UNUSED_PARAMETER(data);
    return CYHAL_FLASH_RSLT_ERR_NOT_SUPPORTED;
#else
    cy_rslt_t status = _cyhal_flash_is_flash_address(address)
        ? _cyhal_flash_run_operation(Cy_Flash_WriteRow, address, data, true)
        : CYHAL_FLASH_RSLT_ERR_ADDRESS;
    return (status);
#endif
}

cy_rslt_t cyhal_flash_program(cyhal_flash_t *obj, uint32_t address, const uint32_t *data)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);

#if defined(CY_IP_MXS40SRSS) || defined(CY_IP_M7CPUSS)
    return _cyhal_flash_is_flash_address(address)
        ? _cyhal_flash_run_operation(Cy_Flash_ProgramRow, address, data, true)
        : CYHAL_FLASH_RSLT_ERR_ADDRESS;
#else
    CY_UNUSED_PARAMETER(address);
    CY_UNUSED_PARAMETER(data);
    return CYHAL_FLASH_RSLT_ERR_NOT_SUPPORTED;
#endif
}

cy_rslt_t cyhal_flash_start_erase(cyhal_flash_t *obj, uint32_t address)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);

#if defined(CY_IP_MXS40SRSS)
    cy_rslt_t status;
    if (_cyhal_flash_pending_pm_change)
    {
        status = CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }
    else
    {
        status = (cy_rslt_t)_cyhal_flash_convert_status(_cyhal_flash_is_flash_address(address)
#if defined(CY_IP_M7CPUSS)
            ? Cy_Flash_StartEraseSector(address)
#else
            ? Cy_Flash_StartEraseRow(address)
#endif
            : CYHAL_FLASH_RSLT_ERR_ADDRESS);
    }
    return status;
#else
    CY_UNUSED_PARAMETER(address);
    return CYHAL_FLASH_RSLT_ERR_NOT_SUPPORTED;
#endif
}

cy_rslt_t cyhal_flash_start_write(cyhal_flash_t *obj, uint32_t address, const uint32_t* data)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);

    /* M7CPUSS does not support write, only erase + program */
#if (defined(CY_IP_MXS40SRSS) && !defined(CY_IP_M7CPUSS)) || CY_FLASH_NON_BLOCKING_SUPPORTED
    return _cyhal_flash_is_flash_address(address)
        ? _cyhal_flash_run_operation(Cy_Flash_StartWrite, address, data, false)
        : CYHAL_FLASH_RSLT_ERR_ADDRESS;
#else
    CY_UNUSED_PARAMETER(address);
    CY_UNUSED_PARAMETER(data);
    return CYHAL_FLASH_RSLT_ERR_NOT_SUPPORTED;
#endif
}

cy_rslt_t cyhal_flash_start_program(cyhal_flash_t *obj, uint32_t address, const uint32_t* data)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);

#if defined(CY_IP_MXS40SRSS)
    return _cyhal_flash_is_flash_address(address)
#if defined(CY_IP_M7CPUSS) /* StartWrite on this device behaves the same as StartProgram on others */
        ? _cyhal_flash_run_operation(Cy_Flash_StartWrite, address, data, false)
#else
        ? _cyhal_flash_run_operation(Cy_Flash_StartProgram, address, data, false)
#endif
        : CYHAL_FLASH_RSLT_ERR_ADDRESS;
#else
    CY_UNUSED_PARAMETER(address);
    CY_UNUSED_PARAMETER(data);
    return CYHAL_FLASH_RSLT_ERR_NOT_SUPPORTED;
#endif
}

bool cyhal_flash_is_operation_complete(cyhal_flash_t *obj)
{
    CY_UNUSED_PARAMETER(obj);
    CY_ASSERT(NULL != obj);
#if defined(CY_IP_MXS40SRSS) || defined(CY_IP_M7CPUSS) || CY_FLASH_NON_BLOCKING_SUPPORTED
    bool complete = (CY_FLASH_DRV_SUCCESS == Cy_Flash_IsOperationComplete());
#if !defined(CY_IP_M7CPUSS) /* PDL automatically clears cache when necessary */
    if (complete)
        Cy_SysLib_ClearFlashCacheAndBuffer();
#endif
    return complete;
#else
    return true;
#endif
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* (CYHAL_DRIVER_AVAILABLE_FLASH) */
