/***************************************************************************//**
* \file cyhal_hwmgr.c
*
* \brief
* Provides a high level interface for managing hardware resources. This is
* used to track what hardware blocks are already being used so they are not over
* allocated.
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

#include "cy_utils.h"
#include "cyhal_hwmgr.h"
#include "cyhal_system.h"

#if defined(__cplusplus)
extern "C"
{
#endif

#define CY_BYTE_NUM_SHIFT (3)
#define CY_BIT_NUM_MASK (0x07)

// Get device specific resources and offsets
// This must declare:
//    _CYHAL_RESOURCES
//    typedef _cyhal_hwmgr_offset_t
//    static uint8_t cyhal_used[<appropriate size>] = {0};
//    static inline uint16_t _cyhal_uses_channels(cyhal_resource_t type);
//    static inline uint16_t _cyhal_get_resource_offset(cyhal_resource_t type);
//    static inline const _cyhal_hwmgr_offset_t* _cyhal_get_block_offsets(cyhal_resource_t type);
//    static inline uint8_t _cyhal_get_block_offset_length(cyhal_resource_t type);
#include "cyhal_hwmgr_impl_part.h"

/*
 * This function is designed to verify that the number of valid resources in the cyhal_resource_t
 * enum and the number entries in the _CYHAL_RESOURCES array are identical. Any mismatch
 * between the two will lead to runtime failures. This will produce a divide by 0 error if they
 * get of of sync.
 * NOTE: This function should never be called, it is only for a compile time error check
 * NOTE: The suppress is to temporarily disable the IAR warning about an uncalled function
 */
static inline void _check_array_size(void) __attribute__ ((deprecated));
#if __ICCARM__
#pragma diag_suppress=Pe177
#elif __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
#endif
static inline void _check_array_size(void)
{
    uint32_t dummy = 1 / (_CYHAL_RESOURCES == CYHAL_RSC_INVALID);
    (void)dummy;
}
#if __ICCARM__
#pragma diag_default=Pe177
#elif __clang__
#pragma clang diagnostic pop
#endif

/*******************************************************************************
*       Utility helper functions
*******************************************************************************/

static cy_rslt_t _cyhal_get_bit_position(cyhal_resource_t type, uint8_t block, uint8_t channel, uint16_t* bitPosition)
{
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
    /* For backwards compatability. */
    if (type == CYHAL_RSC_CLKPATH)
    {
        channel = block;
        block = CYHAL_CLOCK_BLOCK_PATHMUX;
        type = CYHAL_RSC_CLOCK;
    }
#endif
    uint16_t offsetRsc = _cyhal_get_resource_offset(type);
    // Offset that is one past the beginning of the next resource (or one past the end of the array).
    // Our offset must be strictly less than that
    uint16_t offsetEndOfRsc = ((1u + type) < _CYHAL_RESOURCES)
        ? _cyhal_get_resource_offset((cyhal_resource_t)(type + 1))
        : CY_TOTAL_ALLOCATABLE_ITEMS;

    if (_cyhal_uses_channels(type))
    {
        const _cyhal_hwmgr_offset_t* blockOffsets = _cyhal_get_block_offsets(type);
        *bitPosition = offsetEndOfRsc;
        if (blockOffsets != NULL)
        {
            // Offset (from the beginning of the section for this block type) that is one past the end of
            // the requested block index. The channel number must be strictly less than that.
            uint16_t blocks = _cyhal_get_block_offset_length(type);
            if (block < blocks)
            {
                *bitPosition = offsetRsc + blockOffsets[block] + channel;
                if ((block + 1) < blocks)
                {
                    offsetEndOfRsc = offsetRsc + blockOffsets[block + 1];
                }
            }
        }
    }
    else
    {
        *bitPosition = offsetRsc + block;
    }

    return (*bitPosition < offsetEndOfRsc)
        ? CY_RSLT_SUCCESS
        : CYHAL_HWMGR_RSLT_ERR_INVALID;
}

static inline cy_rslt_t _cyhal_is_set(const uint8_t* used, cyhal_resource_t type, uint8_t block, uint8_t channel, bool* isSet)
{
    uint16_t bitPosition;
    cy_rslt_t status = _cyhal_get_bit_position(type, block, channel, &bitPosition);
    if (status == CY_RSLT_SUCCESS)
    {
        uint8_t byte = (uint8_t)(bitPosition >> CY_BYTE_NUM_SHIFT);
        uint8_t bit = bitPosition & CY_BIT_NUM_MASK;
        *isSet = (used[byte] & (1 << bit));
    }
    return status;
}

static inline cy_rslt_t _cyhal_set_bit(uint8_t* used, cyhal_resource_t type, uint8_t block, uint8_t channel)
{
    uint16_t bitPosition;
    cy_rslt_t status = _cyhal_get_bit_position(type, block, channel, &bitPosition);
    if (status == CY_RSLT_SUCCESS)
    {
        uint8_t byte = (uint8_t)(bitPosition >> CY_BYTE_NUM_SHIFT);
        uint8_t bit = bitPosition & CY_BIT_NUM_MASK;
        used[byte] |= (1 << bit);
    }
    return status;
}

static inline cy_rslt_t _cyhal_clear_bit(uint8_t* used, cyhal_resource_t type, uint8_t block, uint8_t channel)
{
    uint16_t bitPosition;
    cy_rslt_t status = _cyhal_get_bit_position(type, block, channel, &bitPosition);
    if (status == CY_RSLT_SUCCESS)
    {
        uint8_t byte = (uint8_t)(bitPosition >> CY_BYTE_NUM_SHIFT);
        uint8_t bit = bitPosition & CY_BIT_NUM_MASK;
        used[byte] &= ~(1 << bit);
    }
    return status;
}

/*******************************************************************************
*       Hardware Manager API
*******************************************************************************/

cy_rslt_t cyhal_hwmgr_init(void)
{
    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_hwmgr_reserve(const cyhal_resource_inst_t* obj)
{
    bool isSet;
    uint32_t state = cyhal_system_critical_section_enter();
    cy_rslt_t rslt = _cyhal_is_set(cyhal_used, obj->type, obj->block_num, obj->channel_num, &isSet);
    if (rslt == CY_RSLT_SUCCESS && isSet)
    {
        rslt = CYHAL_HWMGR_RSLT_ERR_INUSE;
    }

    if (rslt == CY_RSLT_SUCCESS)
    {
        rslt = _cyhal_set_bit(cyhal_used, obj->type, obj->block_num, obj->channel_num);
    }
    cyhal_system_critical_section_exit(state);

    return rslt;
}

void cyhal_hwmgr_free(const cyhal_resource_inst_t* obj)
{
    uint32_t state = cyhal_system_critical_section_enter();
    cy_rslt_t rslt = _cyhal_clear_bit(cyhal_used, obj->type, obj->block_num, obj->channel_num);
    CY_UNUSED_PARAMETER(rslt); /* CY_ASSERT only processes in DEBUG, ignores for others */
    CY_ASSERT(CY_RSLT_SUCCESS == rslt);
    cyhal_system_critical_section_exit(state);
}

#if (CYHAL_DRIVER_AVAILABLE_INTERCONNECT)
cy_rslt_t cyhal_hwmgr_allocate(cyhal_resource_t type, cyhal_resource_inst_t* obj)
{
    return _cyhal_hwmgr_allocate_with_connection(type, NULL, NULL, NULL, NULL, obj);
}

cy_rslt_t _cyhal_hwmgr_allocate_with_connection(cyhal_resource_t type, const cyhal_source_t *src, const cyhal_dest_t *dest,
    _cyhal_hwmgr_get_output_source_t get_src, _cyhal_hwmgr_get_input_dest_t get_dest, cyhal_resource_inst_t *obj)
#else
cy_rslt_t cyhal_hwmgr_allocate(cyhal_resource_t type, cyhal_resource_inst_t* obj)
#endif
{
    uint16_t offsetStartOfRsc = _cyhal_get_resource_offset(type);
    uint16_t offsetEndOfRsc = ((1u + type) < _CYHAL_RESOURCES)
        ? _cyhal_get_resource_offset((cyhal_resource_t)(type + 1))
        : CY_TOTAL_ALLOCATABLE_ITEMS;
    bool usesChannels = _cyhal_uses_channels(type);

    uint16_t count = offsetEndOfRsc - offsetStartOfRsc;
    uint8_t block = 0;
    uint8_t channel = 0;
    for (uint16_t i = 0; i < count; i++)
    {
#if (CYHAL_DRIVER_AVAILABLE_INTERCONNECT)
        bool valid = true;
        if (NULL != src)
        {
            cyhal_dest_t destination = get_dest(block, channel);
            valid = _cyhal_can_connect_signal(*src, destination);
        }
        if (valid && NULL != dest)
        {
            cyhal_source_t source = get_src(block, channel);
            valid = _cyhal_can_connect_signal(source, *dest);
        }
        if (valid)
#endif
        {
            cyhal_resource_inst_t rsc = { type, block, channel };
            if (CY_RSLT_SUCCESS == cyhal_hwmgr_reserve(&rsc))
            {
                obj->type = type;
                obj->block_num = block;
                obj->channel_num = channel;
                return CY_RSLT_SUCCESS;
            }
        }

        if (usesChannels)
        {
            const _cyhal_hwmgr_offset_t* blockOffsets = _cyhal_get_block_offsets(type);
            uint16_t blocks = _cyhal_get_block_offset_length(type);
            if ((block + 1) < blocks && blockOffsets[block + 1] <= (i + 1))
            {
                channel = 0;
                do
                {
                    block++;
                }
                while (((block + 1) < blocks) && (blockOffsets[block + 1] == blockOffsets[block])); /* Skip empty blocks */
            }
            else
            {
                channel++;
            }
        }
        else
        {
            block++;
        }
    }

    return CYHAL_HWMGR_RSLT_ERR_NONE_FREE;
}

#if defined(__cplusplus)
}
#endif
