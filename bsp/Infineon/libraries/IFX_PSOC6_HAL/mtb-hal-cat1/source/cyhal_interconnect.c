/***************************************************************************//**
* \file cyhal_interconnect.c
*
* \brief
* Provides a high level interface for interacting with the internal digital
* routing on the chip. This is a wrapper around the lower level PDL API.
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

#include "cyhal_interconnect.h"
#include "cyhal_gpio_impl.h"

#if defined(__cplusplus)
extern "C"
{
#endif

#if (CYHAL_DRIVER_AVAILABLE_INTERCONNECT)

typedef enum
{
    CYHAL_CONNECT_TYPE_VALIDATE,
    CYHAL_CONNECT_TYPE_CONNECT,
    CYHAL_CONNECT_TYPE_DISCONNECT,
} cyhal_connect_type_t;

// Only define if there are actual trigger signals
#if defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI)
//Need to take peri #
#ifdef CY_IP_M0S8PERI_INSTANCES
#define _CYHAL_PERI_INSTANCES (CY_IP_M0S8PERI_INSTANCES)
#elif defined(CY_IP_MXSPERI_INSTANCES)
#define _CYHAL_PERI_INSTANCES (CY_IP_MXSPERI_INSTANCES)
#elif defined(CY_IP_MXPERI_TR_INSTANCES)
#define _CYHAL_PERI_INSTANCES (CY_IP_MXPERI_TR_INSTANCES)
#endif
#ifdef _CYHAL_PERI_INSTANCES
static uint8_t _CYHAL_INTERCONNECT_BASE_IDX[_CYHAL_PERI_INSTANCES] = {
    0,
#if (_CYHAL_PERI_INSTANCES == 2)
    PERI0_TR_GROUP_NR,
#elif (_CYHAL_PERI_INSTANCES > 2)
#error "Max amount of PERI instances is 2"
//For current devices there is a maximum of 2 PERI instances possible
#endif
};

static uint32_t get_peri_block_from_trigger(uint8_t mux_group)
{
    uint32_t blk_idx = 0;
    for(uint8_t i = 0; i < _CYHAL_PERI_INSTANCES;i++)
    {
        if(mux_group > _CYHAL_INTERCONNECT_BASE_IDX[i])
        {
            blk_idx=i;
        }
    }
    return blk_idx;
}

static uint32_t get_local_peri_group_num_from_trigger(uint8_t mux_group)
{
    return ((uint32_t)(mux_group - _CYHAL_INTERCONNECT_BASE_IDX[get_peri_block_from_trigger(mux_group)]));
}
// Helpers for creating Cy_TrigMux_* inputs                                //helper for local peri based group
#define CY_TRIGMUX_INPUT_LINE(mux_group, source_idx) (uint32_t)(((get_local_peri_group_num_from_trigger(mux_group))) << 8 | (source_idx) | (get_peri_block_from_trigger(mux_group) << 16u))
#define CY_TRIGMUX_OUTPUT_LINE(mux_group, dest_idx) (uint32_t)(0x40000000 |  ((get_local_peri_group_num_from_trigger(mux_group))) << 8 | (dest_idx) | (get_peri_block_from_trigger(mux_group) << 16u))
#define CY_SELECT_OUTPUT_LINE(mux_group, dest_idx) (uint32_t)(0x40001000 | ((get_local_peri_group_num_from_trigger(mux_group))) << 8 | (dest_idx) | (get_peri_block_from_trigger(mux_group) << 16u))
#else
#error "No PERI Instances"
#endif
#if (CY_IP_MXPERI_VERSION >= 2u) || (CY_IP_M0S8PERI_VERSION >= 1u) || (CY_IP_MXSPERI >= 1u)
static int8_t _cyhal_get_first_1to1_mux_idx(void)
{
    for(uint8_t idx = 0; idx < (sizeof(cyhal_is_mux_1to1)/sizeof(cyhal_is_mux_1to1[0])); idx++)
    {
        if(cyhal_is_mux_1to1[idx])
            return idx;
    }

    return -1;
}
#endif

// Reads peri trigmux register and returns the selected input line (0 is
// default if no line has been selected)
static uint8_t _cyhal_read_mux_input_idx(uint8_t mux_group, uint8_t mux_output_idx)
{
#if (CY_IP_MXPERI_VERSION >= 2u) || (CY_IP_M0S8PERI_VERSION >= 1u) || (CY_IP_MXSPERI >= 1u)
    const int8_t MUX_GROUP_1TO1_OFFSET = _cyhal_get_first_1to1_mux_idx();
    const uint8_t FIRST_1TO1_MUX_GROUP_IDX = 16;
#endif

    uint32_t mux_reg = 0;
#if (CY_IP_MXPERI_VERSION >= 2u) || (CY_IP_M0S8PERI_VERSION == 1u) || (CY_IP_MXSPERI >= 1u)
    // M0S8 has no 1to1 muxes but the table is still valid
    if(cyhal_is_mux_1to1[mux_group])
    {
        // There are up to 16 regular mux groups and up to 16 1to1 mux groups
        // (in PSoC™ 6).  PERI_TR_GR_TR_CTL starts at the first regular mux so
        // offset by 16 if reading a 1to1 mux.
        mux_reg = PERI_TR_GR_TR_CTL(mux_group - MUX_GROUP_1TO1_OFFSET + FIRST_1TO1_MUX_GROUP_IDX, mux_output_idx);
    }
    else
    {
        mux_reg = PERI_TR_GR_TR_CTL(mux_group, mux_output_idx);
    }
#else // CY_IP_MXPERI_VERSION == 1
    mux_reg = PERI_TR_GR_TR_CTL(mux_group, mux_output_idx);
#endif


#if (CY_IP_MXPERI_VERSION >= 1u) || (CY_IP_MXSPERI >= 1u)
    return _FLD2VAL(PERI_TR_GR_TR_OUT_CTL_TR_SEL, mux_reg);
#elif CY_IP_M0S8PERI_VERSION == 1u
    return _FLD2VAL(PERI_TR_CTL_TR_SEL, mux_reg);
#endif
}

#if (CY_IP_MXPERI_VERSION >= 2u) || (CY_IP_M0S8PERI_VERSION == 1u) || (CY_IP_MXSPERI >= 1u)
static cy_rslt_t _cyhal_interconnect_change_connection_direct(
    uint8_t mux_group, uint8_t mux_group_1to1_offset, uint8_t source_idx, uint8_t dest_idx, cyhal_signal_type_t type, bool connect)
{
#if CY_IP_M0S8PERI_VERSION == 1u
    CY_UNUSED_PARAMETER(type);
    CY_UNUSED_PARAMETER(mux_group_1to1_offset);
#endif

    if(cyhal_is_mux_1to1[mux_group])
    {
#if (CY_IP_MXPERI_VERSION >= 2u) || (CY_IP_MXSPERI >= 1u)
        // Cy_TrigMux_Select assumes the mux_group idx param starts from the
        // first 1to1 mux (so first 1to1 mux is 0)
        uint32_t out_trig = CY_SELECT_OUTPUT_LINE(mux_group - mux_group_1to1_offset, dest_idx);

        if(connect)
            return Cy_TrigMux_Select(out_trig, false, (en_trig_type_t)type);
        else
            return Cy_TrigMux_Deselect(out_trig);
#else
        return (connect)
            ? CYHAL_INTERCONNECT_RSLT_INVALID_CONNECTION
            : CYHAL_INTERCONNECT_RSLT_CANNOT_DISCONNECT;
#endif
    }
    else
    {
        uint32_t in_trig = CY_TRIGMUX_INPUT_LINE(mux_group, source_idx);
        uint32_t out_trig = CY_TRIGMUX_OUTPUT_LINE(mux_group, dest_idx);

        if(connect)
        {
#if (CY_IP_MXPERI_VERSION >= 2u) || (CY_IP_MXSPERI >= 1u)
            return Cy_TrigMux_Connect(in_trig, out_trig, false, (en_trig_type_t)type);
#else
            return Cy_TrigMux_Connect(in_trig, out_trig);
#endif
        }
        else
        {
            // No Cy_TrigMux_Disconnect so just clear register of found
            // mux input line.
            PERI_TR_GR_TR_CTL(mux_group, dest_idx) = 0;
            return CY_RSLT_SUCCESS;
        }
    }
}
#elif CY_IP_MXPERI_VERSION == 1u
/* Change a HAL trigger connection where a mux is involved */
static cy_rslt_t _cyhal_interconnect_change_connection_direct(uint8_t mux, uint8_t input_idx, uint8_t output_idx, cyhal_signal_type_t type, bool connect)
{
    if (connect)
    {
        uint32_t in_trig = CY_TRIGMUX_INPUT_LINE(mux, input_idx);
        uint32_t out_trig = CY_TRIGMUX_OUTPUT_LINE(mux, output_idx);

        return Cy_TrigMux_Connect(in_trig, out_trig, false, (en_trig_type_t)type);
    }
    else
    {
        PERI_TR_GR_TR_CTL(mux, output_idx) = 0;
        return CY_RSLT_SUCCESS;
    }
}

/* Change a HAL trigger connection where 2 muxes are involved */
static cy_rslt_t _cyhal_interconnect_change_connection_indirect(uint8_t source_mux_group, uint8_t source_mux_input_idx, uint8_t source_mux_output_idx,
    uint8_t dest_mux_group, uint8_t dest_mux_input_idx, uint8_t dest_mux_output_idx, cyhal_signal_type_t type, bool connect)
{
    if(connect)
    {
        // Construct Cy_TrigMux_Connect trigger inputs for both source and dest muxes
        uint32_t source_mux_in_trig = CY_TRIGMUX_INPUT_LINE(source_mux_group, source_mux_input_idx);
        uint32_t source_mux_out_trig = CY_TRIGMUX_OUTPUT_LINE(source_mux_group, source_mux_output_idx);

        uint32_t dest_mux_in_trig = CY_TRIGMUX_INPUT_LINE(dest_mux_group, dest_mux_input_idx);
        uint32_t dest_mux_out_trig = CY_TRIGMUX_OUTPUT_LINE(dest_mux_group, dest_mux_output_idx);

        if(_cyhal_read_mux_input_idx(dest_mux_group, dest_mux_output_idx) != 0)
        {
            return CYHAL_INTERCONNECT_RSLT_ALREADY_CONNECTED;
        }

        cy_rslt_t result = Cy_TrigMux_Connect(source_mux_in_trig, source_mux_out_trig, false, (en_trig_type_t)type);
        if (CY_RSLT_SUCCESS == result)
            result = Cy_TrigMux_Connect(dest_mux_in_trig, dest_mux_out_trig, false, (en_trig_type_t)type);
        return result;
    }
    else
    {
        // No Cy_TrigMux_Disconnect so just clear registers of found muxes
        PERI_TR_GR_TR_CTL(source_mux_group, source_mux_output_idx) = 0;
        PERI_TR_GR_TR_CTL(dest_mux_group, dest_mux_output_idx) = 0;
        return CY_RSLT_SUCCESS;
    }
}
#endif /* #if CY_IP_MXPERI_VERSION >= 2u || CY_IP_M0S8PERI_VERSION == 1u */

// Since both connect and disconnect need to derive mux group(s) and trigger
// indices, use this func to avoid duplicate code.
static cy_rslt_t _cyhal_interconnect_check_connection(cyhal_source_t source, cyhal_dest_t dest, cyhal_connect_type_t connect)
{
    cyhal_internal_source_t internal_src = _CYHAL_TRIGGER_GET_SOURCE_SIGNAL(source);
    cyhal_signal_type_t type = _CYHAL_TRIGGER_GET_SOURCE_TYPE(source);
#if CY_IP_MXPERI_VERSION >= 2u || CY_IP_M0S8PERI_VERSION >= 1u || CY_IP_MXSPERI >= 1u
    const int8_t mux_group_1to1_offset = _cyhal_get_first_1to1_mux_idx();

    // cyhal_dest_to_mux stores 1to1 triggers with bit 8 set and the lower 7
    // bits as the offset into the 1to1 triggers (so 128 is 1to1 mux index 0)
    // but here we need the actual group offset for all the triggers.
    uint8_t mux_group = cyhal_dest_to_mux[dest];
    if(mux_group & 0x80)
        mux_group = mux_group_1to1_offset + (mux_group & ~0x80);

    uint8_t dest_idx = cyhal_mux_dest_index[dest];

    // Search through table of mux input trigger lines
    for (uint16_t source_idx = 0; source_idx < cyhal_sources_per_mux[mux_group]; source_idx++)
    {
        if(cyhal_mux_to_sources[mux_group][source_idx] == internal_src)
        {
            // 1to1 triggers muxes source and dest indices must match
            if(cyhal_is_mux_1to1[mux_group] && (source_idx != dest_idx))
            {
                return CYHAL_INTERCONNECT_RSLT_INVALID_CONNECTION;
            }

            // Check if the mux is already configured (possibly from a
            // different source)
            if(CYHAL_CONNECT_TYPE_DISCONNECT != connect
                && _cyhal_read_mux_input_idx(mux_group, dest_idx) != 0)
            {
                return CYHAL_INTERCONNECT_RSLT_ALREADY_CONNECTED;
            }

            return (connect == CYHAL_CONNECT_TYPE_VALIDATE)
                ? CY_RSLT_SUCCESS
                : _cyhal_interconnect_change_connection_direct(mux_group, mux_group_1to1_offset, source_idx, dest_idx, type, connect == CYHAL_CONNECT_TYPE_CONNECT);
        }
    }
    return CYHAL_INTERCONNECT_RSLT_INVALID_CONNECTION;
#elif CY_IP_MXPERI_VERSION == 1u
    uint8_t dest_mux_group = cyhal_dest_to_mux[dest];
    uint8_t dest_mux_output_idx = cyhal_mux_dest_index[dest];

    // Special case 1: DW sources connect to USB_DMA_BURSTEND destinations directly
    // through mux 9 so handle here.
    if(dest_mux_group == 9)
    {
        if((internal_src < _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT0) || (internal_src > _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT15))
            return CYHAL_INTERCONNECT_RSLT_INVALID_CONNECTION;

        if((dest < CYHAL_TRIGGER_USB_DMA_BURSTEND0) || (dest > CYHAL_TRIGGER_USB_DMA_BURSTEND7))
            return CYHAL_INTERCONNECT_RSLT_INVALID_CONNECTION;

        uint16_t mux9_input_idx = (uint16_t)(internal_src - _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT0) + 1;
        uint16_t mux9_output_idx = (uint16_t)(dest - CYHAL_TRIGGER_USB_DMA_BURSTEND0);

        uint8_t set_input_idx = _cyhal_read_mux_input_idx(9, mux9_output_idx);
        if ((CYHAL_CONNECT_TYPE_DISCONNECT != connect) && (set_input_idx != 0))
            return CYHAL_INTERCONNECT_RSLT_ALREADY_CONNECTED;
        else if ((CYHAL_CONNECT_TYPE_DISCONNECT == connect) && (set_input_idx == 0))
            return CYHAL_INTERCONNECT_RSLT_CANNOT_DISCONNECT;
        else
        {
            return (connect == CYHAL_CONNECT_TYPE_VALIDATE)
                ? CY_RSLT_SUCCESS
                : _cyhal_interconnect_change_connection_direct(9, mux9_input_idx, mux9_output_idx, type, connect == CYHAL_CONNECT_TYPE_CONNECT);
        }
    }

    // Special case 2: UDB_TR_DW_ACK destinations have no destinations side mux
    // and are instead only connected through mux 10. Handle those connections
    // here (while handling all other connections through mux 10 later).
    if((dest_mux_group == 10) && (dest >= CYHAL_TRIGGER_UDB_TR_DW_ACK0) && (dest <= CYHAL_TRIGGER_UDB_TR_DW_ACK7))
    {
        if((internal_src < _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT0) || (internal_src > _CYHAL_TRIGGER_CPUSS_DW1_TR_OUT15))
            return CYHAL_INTERCONNECT_RSLT_INVALID_CONNECTION;

        uint16_t mux10_input_idx = (uint16_t)(internal_src - _CYHAL_TRIGGER_CPUSS_DW0_TR_OUT0) + 1;
        uint16_t mux10_output_idx = (uint16_t)(dest - CYHAL_TRIGGER_UDB_TR_DW_ACK0);

        uint8_t set_input_idx = _cyhal_read_mux_input_idx(10, mux10_output_idx);
        if ((CYHAL_CONNECT_TYPE_DISCONNECT != connect) && (set_input_idx != 0))
            return CYHAL_INTERCONNECT_RSLT_ALREADY_CONNECTED;
        else if ((CYHAL_CONNECT_TYPE_DISCONNECT == connect) && (set_input_idx == 0))
            return CYHAL_INTERCONNECT_RSLT_CANNOT_DISCONNECT;
        else
        {
            return (connect == CYHAL_CONNECT_TYPE_VALIDATE)
                ? CY_RSLT_SUCCESS
                : _cyhal_interconnect_change_connection_direct(10, mux10_input_idx, mux10_output_idx, type, connect == CYHAL_CONNECT_TYPE_CONNECT);
        }
    }

    // Since PSoC™ 6 BLE devices w/ trigmux vers1 have a 1to1 relationship
    // between peripheral sources and reduction trigger muxes (besides DW which
    // connects to trig mux 9 and 10, handled above) it is possible to search
    // through source mux tables to find the idx required.
    uint16_t source_mux_group = 0;
    uint16_t source_mux_input_idx = 0;
    bool found_source_mux_info = false;
    for(source_mux_group = 10; source_mux_group < 15; source_mux_group++)
    {
        for(source_mux_input_idx = 0; source_mux_input_idx < cyhal_sources_per_mux[source_mux_group]; source_mux_input_idx++)
        {
            if(cyhal_mux_to_sources[source_mux_group][source_mux_input_idx] == internal_src)
            {
                found_source_mux_info = true;
                break;
            }
        }
        if(found_source_mux_info)
            break;
    }

    if(!found_source_mux_info)
        return CYHAL_INTERCONNECT_RSLT_INVALID_CONNECTION;

    // Construct the cyhal_internal_source_t range that contains all possible inputs
    // from the source mux to the dest mux. Not every cyhal_internal_source_t in this
    // range will go to the dest mux but dest_mux_input_line_low and
    // dest_mux_input_line_high will be used in the next step to find which inputs can.
    cyhal_internal_source_t dest_mux_input_line_low;
    cyhal_internal_source_t dest_mux_input_line_high;
    switch (source_mux_group)
    {
        case 10:
            dest_mux_input_line_low = _CYHAL_TRIGGER_TR_GROUP10_OUTPUT0;
            dest_mux_input_line_high = _CYHAL_TRIGGER_TR_GROUP10_OUTPUT7;
            break;
        case 11:
            dest_mux_input_line_low = _CYHAL_TRIGGER_TR_GROUP11_OUTPUT0;
            dest_mux_input_line_high = _CYHAL_TRIGGER_TR_GROUP11_OUTPUT15;
            break;
        case 12:
            dest_mux_input_line_low = _CYHAL_TRIGGER_TR_GROUP12_OUTPUT0;
            dest_mux_input_line_high = _CYHAL_TRIGGER_TR_GROUP12_OUTPUT9;
            break;
        case 13:
            dest_mux_input_line_low = _CYHAL_TRIGGER_TR_GROUP13_OUTPUT0;
            dest_mux_input_line_high = _CYHAL_TRIGGER_TR_GROUP13_OUTPUT17;
            break;
        case 14:
            dest_mux_input_line_low = _CYHAL_TRIGGER_TR_GROUP14_OUTPUT0;
            dest_mux_input_line_high = _CYHAL_TRIGGER_TR_GROUP14_OUTPUT15;
            break;
        default:
            return CYHAL_INTERCONNECT_RSLT_INVALID_CONNECTION;
    }

    // Search through the dest mux source table to find the low and high
    // indices of the valid inputs from the source mux to the dest mux. These
    // indices will correspond to, and be between, dest_mux_input_line_low and
    // dest_mux_input_line_high (but not necessarily the whole range). If e.g
    // only source mux output lines 8-9 go to the dest mux this will be
    // reflected by setting source_mux_start_idx to 8
    uint16_t dest_mux_input_line_low_idx = 10000;
    uint16_t dest_mux_input_line_high_idx = 0;
    uint16_t source_mux_start_idx = 0;
    for(uint16_t i = 0; i < cyhal_sources_per_mux[dest_mux_group]; i++)
    {
        if((cyhal_mux_to_sources[dest_mux_group][i] >= dest_mux_input_line_low) &&
                (cyhal_mux_to_sources[dest_mux_group][i] <= dest_mux_input_line_high))
        {
            if(dest_mux_input_line_low_idx > i)
            {
                dest_mux_input_line_low_idx = i;
                source_mux_start_idx = (uint16_t)(cyhal_mux_to_sources[dest_mux_group][i] - dest_mux_input_line_low);
            }

            if(dest_mux_input_line_high_idx < i)
                dest_mux_input_line_high_idx = i;
        }
    }

    // Construct possible output trigger lines from the source mux starting at
    // the first input line found in the previous step. Since source mux output
    // lines can be arbitrarily selected and may already be in use, read the
    // source mux register to check if an output is free.
    uint8_t source_mux_output_idx = 0;
    uint8_t dest_mux_input_idx = 0;
    bool found_connection = false;
    for(source_mux_output_idx = source_mux_start_idx; source_mux_output_idx < (source_mux_start_idx + (dest_mux_input_line_high_idx - dest_mux_input_line_low_idx + 1)); source_mux_output_idx++)
    {
        // If connecting: Check if possible output trigger is free.
        if((connect != CYHAL_CONNECT_TYPE_DISCONNECT) && _cyhal_read_mux_input_idx(source_mux_group, source_mux_output_idx) == 0)
        {
            dest_mux_input_idx = dest_mux_input_line_low_idx + source_mux_output_idx - source_mux_start_idx;

            found_connection = true;
            break;
        }
        // If disconnecting: We have already used this source mux output line
        // and it matches the inputted source. Since disconnecting only
        // requires output idx info (for both muxes) nothing needs to be
        // calculated here.
        else if((connect == CYHAL_CONNECT_TYPE_DISCONNECT) && _cyhal_read_mux_input_idx(source_mux_group, source_mux_output_idx) == source_mux_input_idx)
        {
            found_connection = true;
            break;
        }
    }

    if(!found_connection)
    {
        return (connect == CYHAL_CONNECT_TYPE_DISCONNECT)
            ? CYHAL_INTERCONNECT_RSLT_CANNOT_DISCONNECT
            : CYHAL_INTERCONNECT_RSLT_INVALID_CONNECTION;
    }

    return (connect == CYHAL_CONNECT_TYPE_VALIDATE)
        ? CY_RSLT_SUCCESS
        : _cyhal_interconnect_change_connection_indirect(source_mux_group, source_mux_input_idx, source_mux_output_idx,
            dest_mux_group, dest_mux_input_idx, dest_mux_output_idx, type, connect == CYHAL_CONNECT_TYPE_CONNECT);
#else
#error Unrecognized PERI version
#endif
}

#endif /* defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI) */

cy_rslt_t _cyhal_connect_signal(cyhal_source_t source, cyhal_dest_t dest)
{
#if defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI)
    return _cyhal_interconnect_check_connection(source, dest, CYHAL_CONNECT_TYPE_CONNECT);
#else
    CY_UNUSED_PARAMETER(source);
    CY_UNUSED_PARAMETER(dest);
    return CYHAL_INTERCONNECT_RSLT_INVALID_CONNECTION;
#endif /* defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI) */
}

cy_rslt_t _cyhal_disconnect_signal(cyhal_source_t source, cyhal_dest_t dest)
{
#if defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI)
    return _cyhal_interconnect_check_connection(source, dest, CYHAL_CONNECT_TYPE_DISCONNECT);
#else
    CY_UNUSED_PARAMETER(source);
    CY_UNUSED_PARAMETER(dest);
    return CYHAL_INTERCONNECT_RSLT_INVALID_CONNECTION;
#endif /* defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI) */
}

bool _cyhal_can_connect_signal(cyhal_source_t source, cyhal_dest_t dest)
{
#if defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI)
    return (CY_RSLT_SUCCESS == _cyhal_interconnect_check_connection(source, dest, CYHAL_CONNECT_TYPE_VALIDATE));
#else
    CY_UNUSED_PARAMETER(source);
    CY_UNUSED_PARAMETER(dest);
    return false;
#endif /* defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI) */
}

#endif /* CYHAL_DRIVER_AVAILABLE_INTERCONNECT */

cy_rslt_t cyhal_connect_pin(const cyhal_resource_pin_mapping_t *pin_connection, uint8_t drive_mode)
{
    cyhal_gpio_t pin = pin_connection->pin;
    GPIO_PRT_Type *port = Cy_GPIO_PortToAddr(CYHAL_GET_PORT(pin));
    en_hsiom_sel_t hsiom = pin_connection->hsiom;

    Cy_GPIO_Pin_FastInit(port, CYHAL_GET_PIN(pin), drive_mode, 1, hsiom);
    // Force output to enable pulls.
    switch (drive_mode)
    {
        case CY_GPIO_DM_PULLUP:
            Cy_GPIO_Write(port, CYHAL_GET_PIN(pin), 1);
            break;
        case CY_GPIO_DM_PULLDOWN:
            Cy_GPIO_Write(port, CYHAL_GET_PIN(pin), 0);
            break;
        default:
            /* do nothing */
            break;
    }

    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_disconnect_pin(cyhal_gpio_t pin)
{
    GPIO_PRT_Type *port = Cy_GPIO_PortToAddr(CYHAL_GET_PORT(pin));

    Cy_GPIO_Pin_FastInit(port, CYHAL_GET_PIN(pin), CY_GPIO_DM_HIGHZ, 1, HSIOM_SEL_GPIO);

    return CY_RSLT_SUCCESS;
}

#if defined(__cplusplus)
}
#endif
