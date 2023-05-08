/***************************************************************************//**
* \file cyhal_tcpwm_common.c
*
* \brief
* Code shared between the Cypress Timer/Counter and PWM.
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
#include "cyhal_utils.h"
#include "cyhal_irq_impl.h"
#include "cyhal_syspm.h"
#include "cyhal_system.h"
#include "cyhal_tcpwm_common.h"
#include "cyhal_clock.h"

#if (_CYHAL_DRIVER_AVAILABLE_TCPWM)

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(COMPONENT_CAT1B) || (COMPONENT_CAT1D)
#define TCPWM_CLOCK(block, channel)     (PCLK_TCPWM##block##_CLOCK_COUNTER_EN##channel)
#elif defined(COMPONENT_CAT5)
/* Note: PCLK is not used on this device */
#define TCPWM_CLOCK(block, channel)     (0)
#else
#define TCPWM_CLOCK(block, channel)     (PCLK_TCPWM##block##_CLOCKS##channel)
#endif

#if defined(COMPONENT_CAT5)
/* Used to calculate which TCPWM_INTR_MASK_t to use when enabling interrupts */
#define _GET_TCPWM_INTR_MASK(group, counter) (1 << (((group) * 2) + counter))
#endif

#if defined(CY_IP_MXTCPWM_INSTANCES)
#if (CY_IP_MXTCPWM_VERSION == 1)
    #if (CY_IP_MXTCPWM_INSTANCES == 0)
        #define _CYHAL_TCPWM_CHANNELS (0u)
    #elif (CY_IP_MXTCPWM_INSTANCES == 1)
        #define _CYHAL_TCPWM_CHANNELS (TCPWM0_CNT_NR)
    #elif (CY_IP_MXTCPWM_INSTANCES == 2)
        #define _CYHAL_TCPWM_CHANNELS (TCPWM0_CNT_NR + TCPWM1_CNT_NR)
    #else
        #warning Unhandled TCPWM instance count
    #endif
#else // (CY_IP_MXTCPWM_VERSION >= 2)
    #if (CY_IP_MXTCPWM_INSTANCES == 1)
        #if (TCPWM_GRP_NR == 0)
            #define _CYHAL_TCPWM_CHANNELS (0U)
        #elif (TCPWM_GRP_NR == 1)
            #define _CYHAL_TCPWM_CHANNELS (TCPWM_GRP_NR0_GRP_GRP_CNT_NR)
        #elif (TCPWM_GRP_NR == 2)
            #define _CYHAL_TCPWM_CHANNELS (TCPWM_GRP_NR0_GRP_GRP_CNT_NR + TCPWM_GRP_NR1_GRP_GRP_CNT_NR)
        #elif (TCPWM_GRP_NR == 3)
            #define _CYHAL_TCPWM_CHANNELS (TCPWM_GRP_NR0_GRP_GRP_CNT_NR + TCPWM_GRP_NR1_GRP_GRP_CNT_NR + TCPWM_GRP_NR2_GRP_GRP_CNT_NR)
        #elif (TCPWM_GRP_NR == 4)
            #define _CYHAL_TCPWM_CHANNELS (TCPWM_GRP_NR0_GRP_GRP_CNT_NR + TCPWM_GRP_NR1_GRP_GRP_CNT_NR + TCPWM_GRP_NR2_GRP_GRP_CNT_NR + TCPWM_GRP_NR3_GRP_GRP_CNT_NR)
        #endif
    #elif (CY_IP_MXTCPWM_INSTANCES == 2)
        #if (TCPWM0_GRP_NR == 0)
            #define _CYHAL_TCPWM0_CHANNELS (0U)
        #elif (TCPWM0_GRP_NR == 1)
            #define _CYHAL_TCPWM0_CHANNELS (TCPWM0_GRP_NR0_GRP_GRP_CNT_NR)
        #elif (TCPWM0_GRP_NR == 2)
            #define _CYHAL_TCPWM0_CHANNELS (TCPWM0_GRP_NR0_GRP_GRP_CNT_NR + TCPWM0_GRP_NR1_GRP_GRP_CNT_NR)
        #elif (TCPWM0_GRP_NR == 3)
            #define _CYHAL_TCPWM0_CHANNELS (TCPWM0_GRP_NR0_GRP_GRP_CNT_NR + TCPWM0_GRP_NR1_GRP_GRP_CNT_NR + TCPWM0_GRP_NR2_GRP_GRP_CNT_NR)
        #elif (TCPWM0_GRP_NR == 4)
            #define _CYHAL_TCPWM0_CHANNELS (TCPWM0_GRP_NR0_GRP_GRP_CNT_NR + TCPWM0_GRP_NR1_GRP_GRP_CNT_NR + TCPWM0_GRP_NR2_GRP_GRP_CNT_NR + TCPWM0_GRP_NR3_GRP_GRP_CNT_NR)
        #endif
        #ifndef _CYHAL_TCPWM0_CHANNELS
            #error "Unhandled TCPWM0_GRP_NR count"
        #endif
        #if (TCPWM1_GRP_NR == 0)
            #define _CYHAL_TCPWM1_CHANNELS (0U)
        #elif (TCPWM1_GRP_NR == 1)
            #define _CYHAL_TCPWM1_CHANNELS (TCPWM1_GRP_NR0_GRP_GRP_CNT_NR)
        #elif (TCPWM1_GRP_NR == 2)
            #define _CYHAL_TCPWM1_CHANNELS (TCPWM1_GRP_NR0_GRP_GRP_CNT_NR + TCPWM1_GRP_NR1_GRP_GRP_CNT_NR)
        #elif (TCPWM1_GRP_NR == 3)
            #define _CYHAL_TCPWM1_CHANNELS (TCPWM1_GRP_NR0_GRP_GRP_CNT_NR + TCPWM1_GRP_NR1_GRP_GRP_CNT_NR + TCPWM1_GRP_NR2_GRP_GRP_CNT_NR)
        #elif (TCPWM1_GRP_NR == 4)
            #define _CYHAL_TCPWM1_CHANNELS (TCPWM1_GRP_NR0_GRP_GRP_CNT_NR + TCPWM1_GRP_NR1_GRP_GRP_CNT_NR + TCPWM1_GRP_NR2_GRP_GRP_CNT_NR + TCPWM1_GRP_NR3_GRP_GRP_CNT_NR)
        #endif
        #ifndef _CYHAL_TCPWM1_CHANNELS
            #error "Unhandled TCPWM1_GRP_NR count"
        #endif

        #define _CYHAL_TCPWM_CHANNELS (_CYHAL_TCPWM0_CHANNELS + _CYHAL_TCPWM1_CHANNELS)
    #else
        #warning Unhandled TCPWM instance count
    #endif
#endif
#elif defined(CY_IP_M0S8TCPWM_INSTANCES)
    #if (CY_IP_M0S8TCPWM_INSTANCES == 1)
        #define _CYHAL_TCPWM_CHANNELS (TCPWM_CNT_NR)
    #else
        #warning Unhandled TCPWM instance count
    #endif
#endif

const _cyhal_tcpwm_data_t _CYHAL_TCPWM_DATA[] =
{
#if defined(CY_IP_MXTCPWM_INSTANCES)
    #if (CY_IP_MXTCPWM_VERSION == 1)
        #if (CY_IP_MXTCPWM_INSTANCES > 0)
            {TCPWM0, TCPWM_CLOCK(0, 0), TCPWM0_CNT_CNT_WIDTH, TCPWM0_CNT_NR, 0, tcpwm_0_interrupts_0_IRQn },
        #endif
        #if (CY_IP_MXTCPWM_INSTANCES > 1)
            {TCPWM1, TCPWM_CLOCK(1, 0), TCPWM1_CNT_CNT_WIDTH, TCPWM1_CNT_NR, TCPWM0_CNT_NR, tcpwm_1_interrupts_0_IRQn },
        #endif
        #if (CY_IP_MXTCPWM_INSTANCES > 2)
            #warning Unhandled TCPWM instance count
        #endif
    #else // (CY_IP_MXTCPWM_VERSION >= 2)
        #if (CY_IP_MXTCPWM_INSTANCES == 1)
            #if (TCPWM_GRP_NR > 0)
                {TCPWM0, TCPWM_CLOCK(0, 0), TCPWM_GRP_NR0_CNT_GRP_CNT_WIDTH, TCPWM_GRP_NR0_GRP_GRP_CNT_NR, 0, tcpwm_0_interrupts_0_IRQn },
            #endif
            #if (TCPWM_GRP_NR > 1)
                {TCPWM0, TCPWM_CLOCK(0, 256), TCPWM_GRP_NR1_CNT_GRP_CNT_WIDTH, TCPWM_GRP_NR1_GRP_GRP_CNT_NR, TCPWM_GRP_NR0_GRP_GRP_CNT_NR, tcpwm_0_interrupts_256_IRQn },
            #endif
            #if (TCPWM_GRP_NR > 2)
                {TCPWM0, TCPWM_CLOCK(0, 512), TCPWM_GRP_NR2_CNT_GRP_CNT_WIDTH, TCPWM_GRP_NR2_GRP_GRP_CNT_NR, TCPWM_GRP_NR0_GRP_GRP_CNT_NR + TCPWM_GRP_NR1_GRP_GRP_CNT_NR, tcpwm_0_interrupts_512_IRQn },
            #endif
            #if (TCPWM_GRP_NR > 3)
                {TCPWM0, TCPWM_CLOCK(0, 768), TCPWM_GRP_NR3_CNT_GRP_CNT_WIDTH, TCPWM_GRP_NR3_GRP_GRP_CNT_NR, TCPWM_GRP_NR0_GRP_GRP_CNT_NR + TCPWM_GRP_NR1_GRP_GRP_CNT_NR + TCPWM_GRP_NR2_GRP_GRP_CNT_NR, tcpwm_0_interrupts_768_IRQn },
            #endif
        #endif
        #if (CY_IP_MXTCPWM_INSTANCES == 2)
            #if (TCPWM0_GRP_NR > 0)
                {TCPWM0, TCPWM_CLOCK(0, 0), TCPWM0_GRP_NR0_CNT_GRP_CNT_WIDTH, TCPWM0_GRP_NR0_GRP_GRP_CNT_NR, 0, tcpwm_0_interrupts_0_IRQn },
            #endif
            #if (TCPWM0_GRP_NR > 1)
                {TCPWM0, TCPWM_CLOCK(0, 256), TCPWM0_GRP_NR1_CNT_GRP_CNT_WIDTH, TCPWM0_GRP_NR1_GRP_GRP_CNT_NR, TCPWM0_GRP_NR0_GRP_GRP_CNT_NR, tcpwm_0_interrupts_256_IRQn },
            #endif
            #if (TCPWM0_GRP_NR > 2)
                {TCPWM0, TCPWM_CLOCK(0, 512), TCPWM0_GRP_NR2_CNT_GRP_CNT_WIDTH, TCPWM0_GRP_NR2_GRP_GRP_CNT_NR, TCPWM0_GRP_NR0_GRP_GRP_CNT_NR + TCPWM0_GRP_NR1_GRP_GRP_CNT_NR, tcpwm_0_interrupts_512_IRQn },
            #endif
            #if (TCPWM0_GRP_NR > 3)
                {TCPWM0, TCPWM_CLOCK(0, 768), TCPWM0_GRP_NR3_CNT_GRP_CNT_WIDTH, TCPWM0_GRP_NR3_GRP_GRP_CNT_NR, TCPWM0_GRP_NR0_GRP_GRP_CNT_NR + TCPWM0_GRP_NR1_GRP_GRP_CNT_NR + TCPWM0_GRP_NR2_GRP_GRP_CNT_NR, tcpwm_0_interrupts_768_IRQn },
            #endif
            #if (TCPWM0_GRP_NR > 4)
                #error "Unhandled TCPWM0_GRP_NR count"
            #endif
            #if (TCPWM1_GRP_NR > 0)
                {TCPWM1, TCPWM_CLOCK(1, 0), TCPWM1_GRP_NR0_CNT_GRP_CNT_WIDTH, TCPWM1_GRP_NR0_GRP_GRP_CNT_NR, _CYHAL_TCPWM0_CHANNELS, tcpwm_1_interrupts_0_IRQn },
            #endif
            #if (TCPWM1_GRP_NR > 1)
                {TCPWM1, TCPWM_CLOCK(1, 256), TCPWM1_GRP_NR1_CNT_GRP_CNT_WIDTH, TCPWM1_GRP_NR1_GRP_GRP_CNT_NR, _CYHAL_TCPWM0_CHANNELS + TCPWM1_GRP_NR0_GRP_GRP_CNT_NR, tcpwm_1_interrupts_256_IRQn },
            #endif
            #if (TCPWM1_GRP_NR > 2)
                {TCPWM1, TCPWM_CLOCK(1, 512), TCPWM1_GRP_NR2_CNT_GRP_CNT_WIDTH, TCPWM1_GRP_NR2_GRP_GRP_CNT_NR, _CYHAL_TCPWM0_CHANNELS + TCPWM1_GRP_NR0_GRP_GRP_CNT_NR + TCPWM1_GRP_NR1_GRP_GRP_CNT_NR, tcpwm_1_interrupts_512_IRQn },
            #endif
            #if (TCPWM1_GRP_NR > 3)
                {TCPWM1, TCPWM_CLOCK(1, 768), TCPWM1_GRP_NR3_CNT_GRP_CNT_WIDTH, TCPWM1_GRP_NR3_GRP_GRP_CNT_NR, _CYHAL_TCPWM0_CHANNELS + TCPWM1_GRP_NR0_GRP_GRP_CNT_NR + TCPWM1_GRP_NR1_GRP_GRP_CNT_NR + TCPWM1_GRP_NR2_GRP_GRP_CNT_NR, tcpwm_1_interrupts_768_IRQn },
            #endif
            #if (TCPWM1_GRP_NR > 4)
                #error "Unhandled TCPWM1_GRP_NR count"
            #endif
        #endif
        #if (CY_IP_MXTCPWM_INSTANCES > 2)
            #warning Unhandled TCPWM instance count
        #endif
    #endif
#elif defined(CY_IP_M0S8TCPWM_INSTANCES)
    #if (CY_IP_M0S8TCPWM_INSTANCES == 1)
        {TCPWM, PCLK_TCPWM_CLOCKS0, 16, TCPWM_CNT_NR, 0, tcpwm_interrupts_0_IRQn },
    #endif
    #if (CY_IP_M0S8TCPWM_INSTANCES > 1)
        #warning Unhandled TCPWM instance count
    #endif
#endif
};


// There are some number of input trigger indices (starting at 0) that are
// reserved for various purposes. Here we are dealing with inputs from the
// trigmux which start after the reserved inputs so we must always offset the
// trigger index after reservation. For all devices, indices 0 and 1 are
// reserved for constant signals 0 and 1 respectively (so offset by 2 to
// start). Depending on device, further offsetting may be needed as well. The
// number of trigmux tcpwm inputs (but not the total number of tcpwm trigger
// inputs) per tcpwm block is also defined here.
#if (CY_IP_MXTCPWM_VERSION == 1U)
    const uint16_t _CYHAL_TCPWM_TRIGGER_INPUTS_IDX_OFFSET[1] = {2};
    const uint16_t _CYHAL_TCPWM_TRIGGER_INPUTS_PER_BLOCK[1] = {(16 - 2)}; // = {(16 - _CYHAL_TCPWM_TRIGGER_INPUTS_IDX_OFFSET[0])};
#elif (CY_IP_MXTCPWM_VERSION == 2U)
    // Note: These devices also have support for up to 256 trigger lines total,
    // but only 28 input triggers (on top of the 2 + TCPWM_TR_ONE_CNT_NR) are
    // currently available, so we only support that to save RAM.
    #if (CY_IP_MXTCPWM_INSTANCES == 1)
    const uint16_t _CYHAL_TCPWM_TRIGGER_INPUTS_IDX_OFFSET[1] = {(2 + TCPWM_TR_ONE_CNT_NR)};
    const uint16_t  _CYHAL_TCPWM_TRIGGER_INPUTS_PER_BLOCK[1] = {(TCPWM_TR_ALL_CNT_NR)};
    #elif (CY_IP_MXTCPWM_INSTANCES == 2)
    const uint16_t _CYHAL_TCPWM_TRIGGER_INPUTS_IDX_OFFSET[2] = {(2 + TCPWM0_TR_ONE_CNT_NR), (2 + TCPWM1_TR_ONE_CNT_NR)};
    const uint16_t _CYHAL_TCPWM_TRIGGER_INPUTS_PER_BLOCK[2] = {(TCPWM0_TR_ALL_CNT_NR), (TCPWM1_TR_ALL_CNT_NR)};
    #else
    #warning Unhandled TCPWM instance count
    #endif
#else // (CY_IP_M0S8TCPWM_VERSION == 2)
    #if defined(CY_DEVICE_PSOC4AS1)
        const uint16_t _CYHAL_TCPWM_TRIGGER_INPUTS_IDX_OFFSET[1] = {(2 + 12)};
        const uint16_t _CYHAL_TCPWM_TRIGGER_INPUTS_PER_BLOCK[1] = {(16 - 2 - 12)}; // = {(16 - _CYHAL_TCPWM_TRIGGER_INPUTS_IDX_OFFSET[0])};
    #else
        const uint16_t _CYHAL_TCPWM_TRIGGER_INPUTS_IDX_OFFSET[1] = {(2 + 7)};
        const uint16_t _CYHAL_TCPWM_TRIGGER_INPUTS_PER_BLOCK[1] = {(16 - 2 - 7)}; // = {(16 - _CYHAL_TCPWM_TRIGGER_INPUTS_IDX_OFFSET[0])};
    #endif
#endif

// Get the the channel relative to the start of the first TCPWM IP block
#define _CYHAL_TCPWM_GET_ARRAY_INDEX(block, channel)  ((_CYHAL_TCPWM_DATA[(_CYHAL_TCPWM_ADJUST_BLOCK_INDEX(block))].channel_offset) + (channel))

#if (CY_IP_MXTCPWM_VERSION == 2)
    #if (CY_IP_MXTCPWM_INSTANCES == 1)
        uint8_t _CYHAL_OUTPUT_TRIGGERS_USED [_CYHAL_TCPWM_CHANNELS];
    #elif (CY_IP_MXTCPWM_INSTANCES == 2)
        uint8_t _CYHAL_OUTPUT_TRIGGERS_USED [_CYHAL_TCPWM0_CHANNELS + _CYHAL_TCPWM1_CHANNELS];
    #else
        #warning Unhandled TCPWM instance count
    #endif // (CY_IP_MXTCPWM_INSTANCES == 1 or 2)
#endif // (CY_IP_MXTCPWM_VERSION == 2)

/** Callback array for TCPWM interrupts */
static cyhal_tcpwm_t *_cyhal_tcpwm_data_structs[_CYHAL_TCPWM_CHANNELS];

#if (CYHAL_DRIVER_AVAILABLE_SYSPM)
static bool _cyhal_tcpwm_pm_has_enabled(void)
{
    for (uint8_t i = 0; i < _CYHAL_TCPWM_CHANNELS; i++)
    {
        if (NULL != _cyhal_tcpwm_data_structs[i])
        {
            return true;
        }
    }
    return false;
}

static bool _cyhal_tcpwm_pm_transition_pending_value = false;

bool _cyhal_tcpwm_pm_transition_pending(void)
{
    return _cyhal_tcpwm_pm_transition_pending_value;
}

static bool _cyhal_tcpwm_pm_callback(cyhal_syspm_callback_state_t state, cyhal_syspm_callback_mode_t mode, void* callback_arg)
{
    CY_UNUSED_PARAMETER(state);
    CY_UNUSED_PARAMETER(callback_arg);
    switch(mode)
    {
        case CYHAL_SYSPM_CHECK_FAIL:
        {
            _cyhal_tcpwm_pm_transition_pending_value = false;
            break;
        }
        case CYHAL_SYSPM_BEFORE_TRANSITION:
        {
            for (uint8_t i = 0; i < _CYHAL_TCPWM_INSTANCES; i++)
            {
                TCPWM_Type* base = _CYHAL_TCPWM_DATA[i].base;
                for (uint8_t j = 0; j < _CYHAL_TCPWM_DATA[i].num_channels; j++)
                {
                    // Not using _CYHAL_TCPWM_GET_ARRAY_INDEX macro since we've already compressed the indexing (skipping empty groups),
                    // and the macro would compress it again
                    if (NULL != _cyhal_tcpwm_data_structs[_CYHAL_TCPWM_DATA[i].channel_offset + j])
                    {
                        #if defined(CY_IP_M0S8TCPWM) || (CY_IP_MXTCPWM_VERSION == 1)
                        uint32_t mask = ((uint32_t)1u << j);
                        if((((TCPWM_Type *)(base))->CTRL) & mask)
                        {
                            _cyhal_tcpwm_data_structs[_CYHAL_TCPWM_DATA[i].channel_offset + j]->presleep_state = true;
                        }
                        else
                        {
                            _cyhal_tcpwm_data_structs[_CYHAL_TCPWM_DATA[i].channel_offset + j]->presleep_state = false;
                        }
                        #else
                        if(_FLD2BOOL(TCPWM_GRP_CNT_V2_CTRL_ENABLED, TCPWM_GRP_CNT_CTRL(base, TCPWM_GRP_CNT_GET_GRP(j), j)))
                        {
                            _cyhal_tcpwm_data_structs[_CYHAL_TCPWM_DATA[i].channel_offset + j]->presleep_state = true;
                        }
                        else
                        {
                            _cyhal_tcpwm_data_structs[_CYHAL_TCPWM_DATA[i].channel_offset + j]->presleep_state = false;
                        }
                        #endif
                    }
                }
            }
            break;
        }
        case CYHAL_SYSPM_AFTER_TRANSITION:
        {
            for (uint8_t i = 0; i < _CYHAL_TCPWM_INSTANCES; i++)
            {
                #if defined(CY_IP_M0S8TCPWM) || (CY_IP_MXTCPWM_VERSION == 1)
                uint32_t enable_flag = 0;
                #endif
                TCPWM_Type* base = _CYHAL_TCPWM_DATA[i].base;
                for (uint8_t j = 0; j < _CYHAL_TCPWM_DATA[i].num_channels; j++)
                {
                    // Not using _CYHAL_TCPWM_GET_ARRAY_INDEX macro since we've already compressed the indexing (skipping empty groups),
                    // and the macro would compress it again
                    if (NULL != _cyhal_tcpwm_data_structs[_CYHAL_TCPWM_DATA[i].channel_offset + j])
                    {

                        if(_cyhal_tcpwm_data_structs[_CYHAL_TCPWM_DATA[i].channel_offset + j]->presleep_state)
                        {
                            #if defined(CY_IP_M0S8TCPWM) || (CY_IP_MXTCPWM_VERSION == 1)
                            enable_flag |= 1u << j;
                            #else
                            Cy_TCPWM_Enable_Single(base, j);
                            #endif
                        }
                    }
                }
                #if defined(CY_IP_M0S8TCPWM) || (CY_IP_MXTCPWM_VERSION == 1)
                if (0 != enable_flag)
                {
                    // This only enables the counter. This does not start the timer/counter or the pwm.
                    Cy_TCPWM_Enable_Multiple(base, enable_flag);
                }
                #endif
            }
            _cyhal_tcpwm_pm_transition_pending_value = false;
            break;
        }
        case CYHAL_SYSPM_CHECK_READY:
        {
            for (uint8_t i = 0; i < _CYHAL_TCPWM_INSTANCES; i++)
            {
                for (uint8_t j = 0; j < _CYHAL_TCPWM_DATA[i].num_channels; j++)
                {
                    // Not using _CYHAL_TCPWM_GET_ARRAY_INDEX macro since we've already compressed the indexing (skipping empty groups),
                    // and the macro would compress it again
                    cyhal_tcpwm_t* obj = _cyhal_tcpwm_data_structs[_CYHAL_TCPWM_DATA[i].channel_offset + j];
                    if ((NULL != obj) && (CY_TCPWM_PWM_STATUS_COUNTER_RUNNING & Cy_TCPWM_PWM_GetStatus(obj->base, _CYHAL_TCPWM_CNT_NUMBER(obj->resource))))
                    {
                        return false;
                    }
                }
            }
            _cyhal_tcpwm_pm_transition_pending_value = true;
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

static cyhal_syspm_callback_data_t _cyhal_tcpwm_syspm_callback_data =
{
    .callback = &_cyhal_tcpwm_pm_callback,
    .states = (cyhal_syspm_callback_state_t)(CYHAL_SYSPM_CB_CPU_DEEPSLEEP | CYHAL_SYSPM_CB_SYSTEM_HIBERNATE),
    .next = NULL,
    .args = NULL,
    .ignore_modes = (cyhal_syspm_callback_mode_t)(CYHAL_SYSPM_AFTER_DS_WFI_TRANSITION),
};

#else   /* !(CYHAL_DRIVER_AVAILABLE_SYSPM) */
/* If SysPm driver is not available redefine function for TCPWM to return a bad value */
bool _cyhal_tcpwm_pm_transition_pending(void)
{
    return false;
}
#endif /* (CYHAL_DRIVER_AVAILABLE_SYSPM) */

void _cyhal_tcpwm_init_data(cyhal_tcpwm_t *tcpwm)
{
#if defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI)
    for (uint8_t i = 0; i < _CYHAL_TCPWM_INPUTS; i++)
    {
        tcpwm->inputs[i] = CYHAL_TRIGGER_CPUSS_ZERO;
    }
#endif
    #if (CYHAL_DRIVER_AVAILABLE_SYSPM)
    if (!_cyhal_tcpwm_pm_has_enabled())
    {
        _cyhal_syspm_register_peripheral_callback(&_cyhal_tcpwm_syspm_callback_data);
    }
    #endif
    _cyhal_tcpwm_data_structs[_CYHAL_TCPWM_GET_ARRAY_INDEX(tcpwm->resource.block_num, tcpwm->resource.channel_num)] = tcpwm;
}

#if defined (COMPONENT_CAT5)
static void _cyhal_tcpwm_irq_handler(UINT8 group_id, UINT8 counter_id)
{
    uint8_t block = group_id;
    uint8_t channel = counter_id;
#else
static void _cyhal_tcpwm_irq_handler(void)
{
    _cyhal_system_irq_t irqn = _cyhal_irq_get_active();
    uint8_t block, channel = 0;
    // Determine TCPWM block and channel from IRQn
    for (block = 0; block < _CYHAL_TCPWM_INSTANCES; block++)
    {
        if ((irqn >= _CYHAL_TCPWM_DATA[_CYHAL_TCPWM_ADJUST_BLOCK_INDEX(block)].isr_offset) && (irqn < _CYHAL_TCPWM_DATA[_CYHAL_TCPWM_ADJUST_BLOCK_INDEX(block)].isr_offset + _CYHAL_TCPWM_DATA[_CYHAL_TCPWM_ADJUST_BLOCK_INDEX(block)].num_channels))
        {
            channel = (uint8_t)(irqn - _CYHAL_TCPWM_DATA[_CYHAL_TCPWM_ADJUST_BLOCK_INDEX(block)].isr_offset);
            break;
        }
    }
#endif

    if (block < _CYHAL_TCPWM_INSTANCES)
    {
        TCPWM_Type *blockAddr = _CYHAL_TCPWM_DATA[_CYHAL_TCPWM_ADJUST_BLOCK_INDEX(block)].base;
        cyhal_tcpwm_t *tcpwm = _cyhal_tcpwm_data_structs[_CYHAL_TCPWM_GET_ARRAY_INDEX(block, channel)];
        #if (_CYHAL_IRQ_MUXING)
        /* Disable any interrupts that couldn't be disabled from enable_event */
        uint32_t saved_intr_status = cyhal_system_critical_section_enter();
        if(0u != tcpwm->clear_intr_mask)
        {
            uint32_t cnt_num = _CYHAL_TCPWM_CNT_NUMBER(tcpwm->resource);
            uint32_t old_mask = Cy_TCPWM_GetInterruptMask(blockAddr, cnt_num);
            Cy_TCPWM_SetInterruptMask(blockAddr, cnt_num, (old_mask & ~(tcpwm->clear_intr_mask)));
            tcpwm->clear_intr_mask = 0u;
        }
        cyhal_system_critical_section_exit(saved_intr_status);
        #endif
        uint32_t intrCause = Cy_TCPWM_GetInterruptStatusMasked(blockAddr, _CYHAL_TCPWM_CNT_NUMBER(tcpwm->resource));
        /* The masked status can be 0 if we updated the mask above */
        if (0u != intrCause && tcpwm->callback_data.callback != NULL)
        {
            _cyhal_tcpwm_event_callback_t callback = (_cyhal_tcpwm_event_callback_t) tcpwm->callback_data.callback;
            /* Call registered callbacks here */
            (void) (callback) (tcpwm->callback_data.callback_arg, intrCause);
        }

        Cy_TCPWM_ClearInterrupt(blockAddr, _CYHAL_TCPWM_CNT_NUMBER(tcpwm->resource), intrCause);

        #if defined(COMPONENT_CAT5)
        // CAT5 interrupt disables itself after firing, re-enable it
        Cy_TCPWM_EnableInterrupt(_GET_TCPWM_INTR_MASK(group_id, counter_id));
        #endif
    }
    else
    {
        CY_HALT(); // Could not determine the block/channel for IRQn
    }
}

/*******************************************************************************
*       TCPWM Shared HAL Functions
*******************************************************************************/

void _cyhal_tcpwm_free(cyhal_tcpwm_t *obj)
{
    CY_ASSERT(NULL != obj);

    _cyhal_system_irq_t irqn = (_cyhal_system_irq_t)(_CYHAL_TCPWM_DATA[_CYHAL_TCPWM_ADJUST_BLOCK_INDEX(obj->resource.block_num)].isr_offset + obj->resource.channel_num);
    _cyhal_irq_free(irqn);

    if (NULL != obj->base)
    {
        _cyhal_tcpwm_data_structs[_CYHAL_TCPWM_GET_ARRAY_INDEX(obj->resource.block_num, obj->resource.channel_num)] = NULL;
        #if (CYHAL_DRIVER_AVAILABLE_SYSPM)
        if (!_cyhal_tcpwm_pm_has_enabled())
        {
            _cyhal_syspm_unregister_peripheral_callback(&_cyhal_tcpwm_syspm_callback_data);
        }
        #endif

#if defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI)
        for (uint8_t i = 0; i < _CYHAL_TCPWM_OUTPUTS; i++)
        {
            _cyhal_tcpwm_disable_output(obj, (cyhal_tcpwm_output_t)i);
        }
        for (uint8_t i = 0; i < _CYHAL_TCPWM_INPUTS; i++)
        {
            if (CYHAL_TRIGGER_CPUSS_ZERO != obj->inputs[i])
            {
                _cyhal_tcpwm_disconnect_digital(obj, obj->inputs[i], (cyhal_tcpwm_input_t)i);
            }
        }
#endif

        #if defined(CY_IP_MXTCPWM) && (CY_IP_MXTCPWM_VERSION >= 2)
        Cy_TCPWM_Disable_Single(obj->base, _CYHAL_TCPWM_CNT_NUMBER(obj->resource));
        #else
        Cy_TCPWM_PWM_Disable(obj->base, _CYHAL_TCPWM_CNT_NUMBER(obj->resource));
        #endif

        if(false == obj->owned_by_configurator)
        {
            cyhal_hwmgr_free(&(obj->resource));
        }

        obj->base = NULL;
        obj->resource.type = CYHAL_RSC_INVALID;
    }

    if (obj->dedicated_clock)
    {
        en_clk_dst_t pclk = (en_clk_dst_t)(_CYHAL_TCPWM_DATA[_CYHAL_TCPWM_ADJUST_BLOCK_INDEX(obj->resource.block_num)].clock_dst + obj->resource.channel_num);
        cy_rslt_t rslt = _cyhal_utils_peri_pclk_disable_divider(pclk, &(obj->clock));
        CY_UNUSED_PARAMETER(rslt); /* CY_ASSERT only processes in DEBUG, ignores for others */
        CY_ASSERT(CY_RSLT_SUCCESS == rslt);
        cyhal_clock_free(&(obj->clock));
        obj->dedicated_clock = false;
    }
}

void _cyhal_tcpwm_register_callback(cyhal_resource_inst_t *resource, cy_israddress callback, void *callback_arg)
{
    uint8_t index = _CYHAL_TCPWM_GET_ARRAY_INDEX(resource->block_num, resource->channel_num);
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    _cyhal_tcpwm_data_structs[index]->callback_data.callback = callback;
    _cyhal_tcpwm_data_structs[index]->callback_data.callback_arg = callback_arg;
    cyhal_system_critical_section_exit(savedIntrStatus);

    _cyhal_system_irq_t irqn = (_cyhal_system_irq_t)(_CYHAL_TCPWM_DATA[_CYHAL_TCPWM_ADJUST_BLOCK_INDEX(resource->block_num)].isr_offset + resource->channel_num);
    /* Only enable if it's not already enabled */
    if (false == _cyhal_irq_is_enabled(irqn))
    {
        #if defined (COMPONENT_CAT5)
            Cy_TCPWM_RegisterInterruptCallback(_cyhal_tcpwm_irq_handler);
            Cy_TCPWM_EnableInterrupt(_GET_TCPWM_INTR_MASK(resource->block_num, resource->channel_num));
        #endif

        _cyhal_irq_register(irqn, CYHAL_ISR_PRIORITY_DEFAULT, (cy_israddress)_cyhal_tcpwm_irq_handler);
        _cyhal_irq_enable(irqn);
    }
}

void _cyhal_tcpwm_enable_event(cyhal_tcpwm_t *tcpwm, cyhal_resource_inst_t *resource, uint32_t event, uint8_t intr_priority, bool enable)
{
    uint32_t old_mask = Cy_TCPWM_GetInterruptMask(tcpwm->base, _CYHAL_TCPWM_CNT_NUMBER(*resource));
    if (enable)
    {
        // Clear any newly enabled events so that old IRQs don't trigger ISRs
        Cy_TCPWM_ClearInterrupt(tcpwm->base, _CYHAL_TCPWM_CNT_NUMBER(*resource), ~old_mask & event);
    }
#if (_CYHAL_IRQ_MUXING)
    /* We may be in a critical section. Only clear the interrupt status if there isn't a pending interrupt */
    if (Cy_TCPWM_GetInterruptStatus(tcpwm->base, _CYHAL_TCPWM_CNT_NUMBER(*resource)) == 0 || enable)
#endif
    {
        Cy_TCPWM_SetInterruptMask(tcpwm->base, _CYHAL_TCPWM_CNT_NUMBER(*resource), enable ? (old_mask | event) : (old_mask & ~event));
    }
#if (_CYHAL_IRQ_MUXING)
    else
    {
        /* Note that this interrupt cause should be cleared the next time an interrupt is triggered */
        uint32_t saved_intr_status = cyhal_system_critical_section_enter();
        tcpwm->clear_intr_mask |= event;
        cyhal_system_critical_section_exit(saved_intr_status);
    }
#endif

    _cyhal_system_irq_t irqn = (_cyhal_system_irq_t) (_CYHAL_TCPWM_DATA[_CYHAL_TCPWM_ADJUST_BLOCK_INDEX(resource->block_num)].isr_offset + resource->channel_num);
    _cyhal_irq_set_priority(irqn, intr_priority);
}

#if (CY_IP_MXTCPWM_VERSION == 2U)
static uint8_t _cyhal_tcpwm_convert_output_t(cyhal_tcpwm_output_t signal)
{
    switch(signal)
    {
        case CYHAL_TCPWM_OUTPUT_OVERFLOW:
            return CY_TCPWM_CNT_TRIGGER_ON_OVERFLOW;
        case CYHAL_TCPWM_OUTPUT_UNDERFLOW:
            return CY_TCPWM_CNT_TRIGGER_ON_UNDEFLOW;
        case CYHAL_TCPWM_OUTPUT_TERMINAL_COUNT:
            return CY_TCPWM_CNT_TRIGGER_ON_TC;
        case CYHAL_TCPWM_OUTPUT_COMPARE_MATCH:
            return CY_TCPWM_CNT_TRIGGER_ON_CC0_MATCH;
        case CYHAL_TCPWM_OUTPUT_LINE_OUT:
            return CY_TCPWM_CNT_TRIGGER_ON_LINE_OUT;
        default:
            CY_ASSERT(false);
            return 0;
    }
}
#endif

#if defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI)
#if (CY_IP_MXTCPWM_VERSION == 1U) ||(CY_IP_MXTCPWM_VERSION == 2U) || (CY_IP_M0S8TCPWM_VERSION == 2)
// Assumes trig_index is not offset by _CYHAL_TCPWM_TRIGGER_INPUTS_IDX_OFFSET
// (that is, it is 0 indexed).
cyhal_dest_t _cyhal_tpwm_calculate_dest(uint8_t block, uint8_t trig_index)
{
#if (CY_IP_MXTCPWM_VERSION == 1U)
    if(block == 0)
    {
        return (cyhal_dest_t)(CYHAL_TRIGGER_TCPWM0_TR_IN0 + trig_index);
    }
    else
    {
        CY_ASSERT(block == 1);
        return (cyhal_dest_t)(CYHAL_TRIGGER_TCPWM1_TR_IN0 + trig_index);
    }
#elif (CY_IP_MXTCPWM_VERSION == 2U)
    #if (CY_IP_MXTCPWM_INSTANCES == 2)
    return (cyhal_dest_t)(_CYHAL_TCPWM_GET_IP_BLOCK(block) == 0 ? (CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN0 + \
            trig_index) : (CYHAL_TRIGGER_TCPWM1_TR_ALL_CNT_IN0 + trig_index));
    #else
    CY_UNUSED_PARAMETER(block);
    return (cyhal_dest_t)(CYHAL_TRIGGER_TCPWM0_TR_ALL_CNT_IN0 + trig_index);
    #endif
#elif (CY_IP_M0S8TCPWM_VERSION == 2)
    CY_UNUSED_PARAMETER(block);
#if defined(CY_DEVICE_PSOC4AS1)
    CY_ASSERT(block == 0);
    return (cyhal_dest_t)(CYHAL_TRIGGER_TCPWM_TR_IN12 + trig_index);
#elif defined(CY_DEVICE_PMG1S3) || defined(CY_DEVICE_CCG7S)
    CY_ASSERT(block == 0);
    return (cyhal_dest_t)(CYHAL_TRIGGER_TCPWM_TR_IN8 + trig_index);
#else
    CY_ASSERT(block == 0);
    return (cyhal_dest_t)(CYHAL_TRIGGER_TCPWM_TR_IN7 + trig_index);
#endif
#endif
}
#endif

#if (CY_IP_MXTCPWM_VERSION == 1U) || (CY_IP_M0S8TCPWM_VERSION == 2)
static cyhal_source_t _cyhal_tcpwm_calculate_source(uint8_t block, uint8_t chnl, cyhal_tcpwm_output_t signal)
{
#if (CY_IP_MXTCPWM_VERSION == 1U)
    switch(signal)
    {
        case CYHAL_TCPWM_OUTPUT_OVERFLOW:
            return block == 0
                ? (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OVERFLOW0 + chnl, CYHAL_SIGNAL_TYPE_EDGE)
                : (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM1_TR_OVERFLOW0 + chnl, CYHAL_SIGNAL_TYPE_EDGE);
        case CYHAL_TCPWM_OUTPUT_UNDERFLOW:
            return block == 0
                ? (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_UNDERFLOW0 + chnl, CYHAL_SIGNAL_TYPE_EDGE)
                : (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM1_TR_UNDERFLOW0 + chnl, CYHAL_SIGNAL_TYPE_EDGE);
        case CYHAL_TCPWM_OUTPUT_COMPARE_MATCH:
            #if defined(COMPONENT_CAT1B)
            return block == 0
                ? (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_CC_MATCH0 + chnl, CYHAL_SIGNAL_TYPE_EDGE)
                : (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM1_TR_CC_MATCH0 + chnl, CYHAL_SIGNAL_TYPE_EDGE);
            #else
            return block == 0
                ? (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_COMPARE_MATCH0 + chnl, CYHAL_SIGNAL_TYPE_EDGE)
                : (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM1_TR_COMPARE_MATCH0 + chnl, CYHAL_SIGNAL_TYPE_EDGE);
            #endif
       default:
            // Should never reach here
            CY_ASSERT(false);
            return CYHAL_TRIGGER_CPUSS_ZERO;
    }
#elif (CY_IP_M0S8TCPWM_VERSION == 2)
    CY_UNUSED_PARAMETER(block);
    switch(signal)
    {
        case CYHAL_TCPWM_OUTPUT_OVERFLOW:
            return (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_OVERFLOW0 + chnl, CYHAL_SIGNAL_TYPE_EDGE);
        case CYHAL_TCPWM_OUTPUT_UNDERFLOW:
            return (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_UNDERFLOW0 + chnl, CYHAL_SIGNAL_TYPE_EDGE);
        case CYHAL_TCPWM_OUTPUT_COMPARE_MATCH:
            return (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM_TR_COMPARE_MATCH0 + chnl, CYHAL_SIGNAL_TYPE_EDGE);
       default:
            // Should never reach here
            CY_ASSERT(false);
            return CYHAL_TRIGGER_CPUSS_ZERO;
    }
#endif
}
#elif (CY_IP_MXTCPWM_VERSION == 2U)
static cyhal_source_t _cyhal_tcpwm_calculate_source(uint8_t out_trig_idx, uint8_t free_trig)
{
    // Triggers are ordered by output trig idx, then block, then channel.
    // Offsetting by out_trig_idx is sufficient to get the correct trigger.
    if(free_trig == 0)
    {
        return (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT00 + out_trig_idx, CYHAL_SIGNAL_TYPE_EDGE);
    }
    else if(free_trig == 1)
    {
        return (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_TCPWM0_TR_OUT10 + out_trig_idx, CYHAL_SIGNAL_TYPE_EDGE);
    }
    else
    {
        // Should never reach here
        CY_ASSERT(false);
        return CYHAL_TRIGGER_CPUSS_ZERO;
    }
}
#endif
#endif /* defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI) */

cy_rslt_t _cyhal_tcpwm_connect_digital(cyhal_tcpwm_t *obj, cyhal_source_t source, cyhal_tcpwm_input_t signal, cyhal_edge_type_t type)
{
#if defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI)
    cy_rslt_t rslt = CY_RSLT_SUCCESS;
    cyhal_signal_type_t signal_type = _CYHAL_TRIGGER_GET_SOURCE_TYPE(source);
    if((CYHAL_SIGNAL_TYPE_LEVEL == signal_type) != (CYHAL_EDGE_TYPE_LEVEL == type))
    {
        rslt = CYHAL_TCPWM_RSLT_ERR_BAD_ARGUMENT;
    }

    const uint8_t block = obj->resource.block_num;
    uint8_t trig_index = 0;

    if(CY_RSLT_SUCCESS == rslt)
    {
        #if defined (COMPONENT_CAT5)
            // Note: Only applicable for Quaddec on this device. Triggers are hardcoded.
            switch(signal)
            {
                case CYHAL_TCPWM_INPUT_COUNT: /* phiA */
                    trig_index = 0;
                    break;
                case CYHAL_TCPWM_INPUT_START: /* phiB */
                    trig_index = 1;
                    break;
                case CYHAL_TCPWM_INPUT_RELOAD: /* index */
                    trig_index = 2;
                    break;
                default:
                    rslt = CYHAL_TCPWM_RSLT_ERR_BAD_ARGUMENT;
                    break;
            }
        #else
            // Find free input trigger index
            uint32_t saved_intr_status = cyhal_system_critical_section_enter();
            for(trig_index = 0; trig_index < (_CYHAL_TCPWM_TRIGGER_INPUTS_PER_BLOCK[_CYHAL_TCPWM_GET_IP_BLOCK(block)]) ; trig_index++)
            {
                cyhal_dest_t dest = _cyhal_tpwm_calculate_dest(block, trig_index);

                /* On some devices, not all triggers connect uniformly to all sources, so make sure the trigger
                * we're trying to use can actually connect to the source we want to use */
                rslt = _cyhal_connect_signal(source, dest);
                if (rslt == CY_RSLT_SUCCESS)
                {
                    break;
                }
            }
            cyhal_system_critical_section_exit(saved_intr_status);

            if(trig_index == (_CYHAL_TCPWM_TRIGGER_INPUTS_PER_BLOCK[_CYHAL_TCPWM_GET_IP_BLOCK(block)]))
            {
                rslt = CYHAL_TCPWM_RSLT_ERR_NO_FREE_INPUT_SIGNALS;
            }
        #endif
    }

    if(CY_RSLT_SUCCESS == rslt)
    {
        uint16_t trigger_sig = trig_index + _CYHAL_TCPWM_TRIGGER_INPUTS_IDX_OFFSET[_CYHAL_TCPWM_GET_IP_BLOCK(block)];
#if (CY_IP_MXTCPWM_VERSION == 1U) || (CY_IP_M0S8TCPWM_VERSION == 2)
        const uint8_t chnl = obj->resource.channel_num;
        // Clear appropriate trigger reg field and set input index and edge trigger type
        // Note: Input trigger indices 0 and 1 are reserved for constant signals 0
        // and 1 respectively. The first actual trigger input has index 2.
        switch(signal)
        {
            case CYHAL_TCPWM_INPUT_START:
                TCPWM_CNT_TR_CTRL0(obj->base, chnl) &= ~TCPWM_CNT_TR_CTRL0_START_SEL_Msk;
                TCPWM_CNT_TR_CTRL0(obj->base, chnl) |= _VAL2FLD(TCPWM_CNT_TR_CTRL0_START_SEL, trigger_sig);
                TCPWM_CNT_TR_CTRL1(obj->base, chnl) &= ~TCPWM_CNT_TR_CTRL1_START_EDGE_Msk;
                TCPWM_CNT_TR_CTRL1(obj->base, chnl) |= _VAL2FLD(TCPWM_CNT_TR_CTRL1_START_EDGE, type);
                break;
            case CYHAL_TCPWM_INPUT_STOP:
                TCPWM_CNT_TR_CTRL0(obj->base, chnl) &= ~TCPWM_CNT_TR_CTRL0_STOP_SEL_Msk;
                TCPWM_CNT_TR_CTRL0(obj->base, chnl) |= _VAL2FLD(TCPWM_CNT_TR_CTRL0_STOP_SEL, trigger_sig);
                TCPWM_CNT_TR_CTRL1(obj->base, chnl) &= ~TCPWM_CNT_TR_CTRL1_STOP_EDGE_Msk;
                TCPWM_CNT_TR_CTRL1(obj->base, chnl) |= _VAL2FLD(TCPWM_CNT_TR_CTRL1_STOP_EDGE, type);
                break;
            case CYHAL_TCPWM_INPUT_RELOAD:
                TCPWM_CNT_TR_CTRL0(obj->base, chnl) &= ~TCPWM_CNT_TR_CTRL0_RELOAD_SEL_Msk;
                TCPWM_CNT_TR_CTRL0(obj->base, chnl) |= _VAL2FLD(TCPWM_CNT_TR_CTRL0_RELOAD_SEL, trigger_sig);
                TCPWM_CNT_TR_CTRL1(obj->base, chnl) &= ~TCPWM_CNT_TR_CTRL1_RELOAD_EDGE_Msk;
                TCPWM_CNT_TR_CTRL1(obj->base, chnl) |= _VAL2FLD(TCPWM_CNT_TR_CTRL1_RELOAD_EDGE, type);
                break;
            case CYHAL_TCPWM_INPUT_COUNT:
                TCPWM_CNT_TR_CTRL0(obj->base, chnl) &= ~TCPWM_CNT_TR_CTRL0_COUNT_SEL_Msk;
                TCPWM_CNT_TR_CTRL0(obj->base, chnl) |= _VAL2FLD(TCPWM_CNT_TR_CTRL0_COUNT_SEL, trigger_sig);
                TCPWM_CNT_TR_CTRL1(obj->base, chnl) &= ~TCPWM_CNT_TR_CTRL1_COUNT_EDGE_Msk;
                TCPWM_CNT_TR_CTRL1(obj->base, chnl) |= _VAL2FLD(TCPWM_CNT_TR_CTRL1_COUNT_EDGE, type);
                break;
            case CYHAL_TCPWM_INPUT_CAPTURE:
                TCPWM_CNT_TR_CTRL0(obj->base, chnl) &= ~TCPWM_CNT_TR_CTRL0_CAPTURE_SEL_Msk;
                TCPWM_CNT_TR_CTRL0(obj->base, chnl) |= _VAL2FLD(TCPWM_CNT_TR_CTRL0_CAPTURE_SEL, trigger_sig);
                TCPWM_CNT_TR_CTRL1(obj->base, chnl) &= ~TCPWM_CNT_TR_CTRL1_CAPTURE_EDGE_Msk;
                TCPWM_CNT_TR_CTRL1(obj->base, chnl) |= _VAL2FLD(TCPWM_CNT_TR_CTRL1_CAPTURE_EDGE, type);
                break;
           default:
                rslt = CYHAL_TCPWM_RSLT_ERR_BAD_ARGUMENT;
        }

#elif (CY_IP_MXTCPWM_VERSION == 2U)
        // Clear appropriate trigger reg fields and set input index and edge trigger type.
        // Note: Cy_TCPWM_InputTriggerSetup assumes channel indices for block 0 are
        // 0-255 and block 1 are 256-511.
        uint8_t group = _CYHAL_TCPWM_GET_GRP(block);
        uint32_t counter = _CYHAL_TCPWM_CNT_NUMBER(obj->resource);
        switch(signal)
        {
            case CYHAL_TCPWM_INPUT_START:
                TCPWM_GRP_CNT_TR_IN_SEL1(obj->base, group, counter) &= ~TCPWM_GRP_CNT_V2_TR_IN_SEL1_START_SEL_Msk;
                TCPWM_GRP_CNT_TR_IN_EDGE_SEL(obj->base, group, counter) &= ~TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_START_EDGE_Msk;
                Cy_TCPWM_InputTriggerSetup(obj->base, counter, CY_TCPWM_INPUT_TR_START, type, trigger_sig);
                break;
            case CYHAL_TCPWM_INPUT_STOP:
                TCPWM_GRP_CNT_TR_IN_SEL0(obj->base, group, counter) &= ~TCPWM_GRP_CNT_V2_TR_IN_SEL0_STOP_SEL_Msk;
                TCPWM_GRP_CNT_TR_IN_EDGE_SEL(obj->base, group, counter) &= ~TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_STOP_EDGE_Msk;
                Cy_TCPWM_InputTriggerSetup(obj->base, counter, CY_TCPWM_INPUT_TR_STOP_OR_KILL, type, trigger_sig);
                break;
            case CYHAL_TCPWM_INPUT_RELOAD:
                TCPWM_GRP_CNT_TR_IN_SEL0(obj->base, group, counter) &= ~TCPWM_GRP_CNT_V2_TR_IN_SEL0_RELOAD_SEL_Msk;
                TCPWM_GRP_CNT_TR_IN_EDGE_SEL(obj->base, group, counter) &= ~TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_RELOAD_EDGE_Msk;
                Cy_TCPWM_InputTriggerSetup(obj->base, counter, CY_TCPWM_INPUT_TR_RELOAD_OR_INDEX, type, trigger_sig);
                break;
            case CYHAL_TCPWM_INPUT_COUNT:
                TCPWM_GRP_CNT_TR_IN_SEL0(obj->base, group, counter) &= ~TCPWM_GRP_CNT_V2_TR_IN_SEL0_COUNT_SEL_Msk;
                TCPWM_GRP_CNT_TR_IN_EDGE_SEL(obj->base, group, counter) &= ~TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_COUNT_EDGE_Msk;
                Cy_TCPWM_InputTriggerSetup(obj->base, counter, CY_TCPWM_INPUT_TR_COUNT, type, trigger_sig);
                break;
            case CYHAL_TCPWM_INPUT_CAPTURE:
                TCPWM_GRP_CNT_TR_IN_SEL0(obj->base, group, counter) &= ~TCPWM_GRP_CNT_V2_TR_IN_SEL0_CAPTURE0_SEL_Msk;
                TCPWM_GRP_CNT_TR_IN_EDGE_SEL(obj->base, group, counter) &= ~TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_CAPTURE0_EDGE_Msk;
                Cy_TCPWM_InputTriggerSetup(obj->base, counter, CY_TCPWM_INPUT_TR_CAPTURE0, type, trigger_sig);
                break;
           default:
                rslt = CYHAL_TCPWM_RSLT_ERR_BAD_ARGUMENT;
        }
#else
#error Unrecognized TCPWM version
#endif
    }

    if(CY_RSLT_SUCCESS == rslt)
    {
        obj->inputs[(uint32_t)signal] = source;
    }
    else if((_CYHAL_TCPWM_TRIGGER_INPUTS_PER_BLOCK[_CYHAL_TCPWM_GET_IP_BLOCK(block)]) != trig_index)
    {
        /* If we made a connection before erroring out later, undo the connection */
        cyhal_dest_t dest = _cyhal_tpwm_calculate_dest(block, trig_index);
        cy_rslt_t disconnect_rslt = _cyhal_disconnect_signal(source, dest);
        /* Deliberately not impacting the return value, because we're already in an error state. A successful
         * disconnect won't change that. An unsuccessful disconnect should in theory never happen because if
         * we got here we made a successful connection above. */
        CY_ASSERT(CY_RSLT_SUCCESS == disconnect_rslt);
        CY_UNUSED_PARAMETER(disconnect_rslt); /* Avoid unused variable warning in release builds */
    }

    return rslt;
#else
    CY_UNUSED_PARAMETER(obj);
    CY_UNUSED_PARAMETER(source);
    CY_UNUSED_PARAMETER(signal);
    CY_UNUSED_PARAMETER(type);

    return CYHAL_TCPWM_RSLT_ERR_BAD_ARGUMENT;
#endif /* defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI) */
}

cy_rslt_t _cyhal_tcpwm_enable_output(cyhal_tcpwm_t *obj, cyhal_tcpwm_output_t signal, cyhal_source_t *source)
{
#if defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI)
    const uint8_t block = obj->resource.block_num;
    const uint8_t chnl = obj->resource.channel_num;

// Note that triggers are always generated for TCPWMv1 so this just returns the proper source signal
#if (CY_IP_MXTCPWM_VERSION == 1U) || (CY_IP_M0S8TCPWM_VERSION == 2)
    CY_ASSERT(block < 2);

    *source = _cyhal_tcpwm_calculate_source(block, chnl, signal);

    return CY_RSLT_SUCCESS;
#elif (CY_IP_MXTCPWM_VERSION == 2U)
    uint8_t event_type = _cyhal_tcpwm_convert_output_t(signal);

    // All channels in _CYHAL_OUTPUT_TRIGGERS_USED are just ordered
    // sequentially, not ordered by blocks.
    uint8_t out_trig_idx = _CYHAL_TCPWM_GET_ARRAY_INDEX(block, chnl);

    // Find free trigger, if any
    int8_t free_trig = -1;
    uint32_t saved_intr_status = cyhal_system_critical_section_enter();
    if(!(_CYHAL_OUTPUT_TRIGGERS_USED[out_trig_idx] & 1))
    {
        // Output trigger idx 0 is free
        free_trig = 0;
        _CYHAL_OUTPUT_TRIGGERS_USED[out_trig_idx] |= 1;
    }
    else if(!(_CYHAL_OUTPUT_TRIGGERS_USED[out_trig_idx] & 2))
    {
        // Output trigger idx 1 is free
        free_trig = 1;
        _CYHAL_OUTPUT_TRIGGERS_USED[out_trig_idx] |= 2;
    }
    cyhal_system_critical_section_exit(saved_intr_status);

    // Configure trigger out registers
    if(free_trig == 0)
    {
        TCPWM_GRP_CNT_TR_OUT_SEL(obj->base, _CYHAL_TCPWM_GET_GRP(block), _CYHAL_TCPWM_CNT_NUMBER(obj->resource)) \
                                 &= ~TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT0_Msk;
        TCPWM_GRP_CNT_TR_OUT_SEL(obj->base, _CYHAL_TCPWM_GET_GRP(block), _CYHAL_TCPWM_CNT_NUMBER(obj->resource)) \
                                 |= _VAL2FLD(TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT0, event_type);
    }
    else if(free_trig == 1)
    {
        TCPWM_GRP_CNT_TR_OUT_SEL(obj->base, _CYHAL_TCPWM_GET_GRP(block), _CYHAL_TCPWM_CNT_NUMBER(obj->resource)) \
                                 &= ~TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT1_Msk;
        TCPWM_GRP_CNT_TR_OUT_SEL(obj->base, _CYHAL_TCPWM_GET_GRP(block), _CYHAL_TCPWM_CNT_NUMBER(obj->resource)) \
                                 |= _VAL2FLD(TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT1, event_type);
    }
    else
        return CYHAL_TCPWM_RSLT_ERR_NO_FREE_OUTPUT_SIGNALS;

    *source = _cyhal_tcpwm_calculate_source(out_trig_idx, free_trig);

    return CY_RSLT_SUCCESS;
#else
#error Unrecognized TCPWM version
#endif
#else
    CY_UNUSED_PARAMETER(obj);
    CY_UNUSED_PARAMETER(signal);
    CY_UNUSED_PARAMETER(source);
    return CYHAL_TCPWM_RSLT_ERR_NO_FREE_OUTPUT_SIGNALS;
#endif /* defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI) */
}

cy_rslt_t _cyhal_tcpwm_disconnect_digital(cyhal_tcpwm_t *obj, cyhal_source_t source, cyhal_tcpwm_input_t signal)
{
#if defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI)
    const uint8_t block = obj->resource.block_num;
    uint8_t trig_index;

#if (CY_IP_MXTCPWM_VERSION == 1U) || (CY_IP_M0S8TCPWM_VERSION == 2)
    const uint8_t chnl = obj->resource.channel_num;
    switch (signal)
    {
        // Grab trig_index then clear/reset to default (CY_TCPWM_INPUT_LEVEL is
        // default) appropriate ctrl reg fields
        case CYHAL_TCPWM_INPUT_START:
            trig_index = _FLD2VAL(TCPWM_CNT_TR_CTRL0_START_SEL, TCPWM_CNT_TR_CTRL0(obj->base, chnl));
            TCPWM_CNT_TR_CTRL0(obj->base, chnl) &= ~TCPWM_CNT_TR_CTRL0_START_SEL_Msk;
            TCPWM_CNT_TR_CTRL1(obj->base, chnl) |= _VAL2FLD(TCPWM_CNT_TR_CTRL1_START_EDGE, CY_TCPWM_INPUT_LEVEL);
            break;
        case CYHAL_TCPWM_INPUT_STOP:
            trig_index = _FLD2VAL(TCPWM_CNT_TR_CTRL0_STOP_SEL, TCPWM_CNT_TR_CTRL0(obj->base, chnl));
            TCPWM_CNT_TR_CTRL0(obj->base, chnl) &= ~TCPWM_CNT_TR_CTRL0_STOP_SEL_Msk;
            TCPWM_CNT_TR_CTRL1(obj->base, chnl) |= _VAL2FLD(TCPWM_CNT_TR_CTRL1_STOP_EDGE, CY_TCPWM_INPUT_LEVEL);
            break;
        case CYHAL_TCPWM_INPUT_RELOAD:
            trig_index = _FLD2VAL(TCPWM_CNT_TR_CTRL0_RELOAD_SEL, TCPWM_CNT_TR_CTRL0(obj->base, chnl));
            TCPWM_CNT_TR_CTRL0(obj->base, chnl) &= ~TCPWM_CNT_TR_CTRL0_RELOAD_SEL_Msk;
            TCPWM_CNT_TR_CTRL1(obj->base, chnl) |= _VAL2FLD(TCPWM_CNT_TR_CTRL1_RELOAD_EDGE, CY_TCPWM_INPUT_LEVEL);
            break;
        case CYHAL_TCPWM_INPUT_COUNT:
            trig_index = _FLD2VAL(TCPWM_CNT_TR_CTRL0_COUNT_SEL, TCPWM_CNT_TR_CTRL0(obj->base, chnl));
            TCPWM_CNT_TR_CTRL0(obj->base, chnl) &= ~TCPWM_CNT_TR_CTRL0_COUNT_SEL_Msk;
            TCPWM_CNT_TR_CTRL1(obj->base, chnl) |= _VAL2FLD(TCPWM_CNT_TR_CTRL1_COUNT_EDGE, CY_TCPWM_INPUT_LEVEL);
            break;
        case CYHAL_TCPWM_INPUT_CAPTURE:
            trig_index = _FLD2VAL(TCPWM_CNT_TR_CTRL0_CAPTURE_SEL, TCPWM_CNT_TR_CTRL0(obj->base, chnl));
            TCPWM_CNT_TR_CTRL0(obj->base, chnl) &= ~TCPWM_CNT_TR_CTRL0_CAPTURE_SEL_Msk;
            TCPWM_CNT_TR_CTRL1(obj->base, chnl) |= _VAL2FLD(TCPWM_CNT_TR_CTRL1_CAPTURE_EDGE, CY_TCPWM_INPUT_LEVEL);
            break;
       default:
            return CYHAL_TCPWM_RSLT_ERR_BAD_ARGUMENT;
    }
#elif (CY_IP_MXTCPWM_VERSION == 2U)
    switch(signal)
    {
        case CYHAL_TCPWM_INPUT_START:
            trig_index = _FLD2VAL(TCPWM_GRP_CNT_V2_TR_IN_SEL1_START_SEL, TCPWM_GRP_CNT_TR_IN_SEL1(obj->base, _CYHAL_TCPWM_GET_GRP(block), \
                                  _CYHAL_TCPWM_CNT_NUMBER(obj->resource)));
            TCPWM_GRP_CNT_TR_IN_SEL1(obj->base, _CYHAL_TCPWM_GET_GRP(block), _CYHAL_TCPWM_CNT_NUMBER(obj->resource)) &= ~TCPWM_GRP_CNT_V2_TR_IN_SEL1_START_SEL_Msk;
            TCPWM_GRP_CNT_TR_IN_EDGE_SEL(obj->base, _CYHAL_TCPWM_GET_GRP(block), _CYHAL_TCPWM_CNT_NUMBER(obj->resource)) &= ~TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_START_EDGE_Msk;
            break;
        case CYHAL_TCPWM_INPUT_STOP:
            trig_index = _FLD2VAL(TCPWM_GRP_CNT_V2_TR_IN_SEL0_STOP_SEL, TCPWM_GRP_CNT_TR_IN_SEL0(obj->base, _CYHAL_TCPWM_GET_GRP(block), \
                                  _CYHAL_TCPWM_CNT_NUMBER(obj->resource)));
            TCPWM_GRP_CNT_TR_IN_SEL0(obj->base, _CYHAL_TCPWM_GET_GRP(block), _CYHAL_TCPWM_CNT_NUMBER(obj->resource)) &= ~TCPWM_GRP_CNT_V2_TR_IN_SEL0_STOP_SEL_Msk;
            TCPWM_GRP_CNT_TR_IN_EDGE_SEL(obj->base, _CYHAL_TCPWM_GET_GRP(block), _CYHAL_TCPWM_CNT_NUMBER(obj->resource)) &= ~TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_STOP_EDGE_Msk;
            break;
        case CYHAL_TCPWM_INPUT_RELOAD:
            trig_index = _FLD2VAL(TCPWM_GRP_CNT_V2_TR_IN_SEL0_RELOAD_SEL, TCPWM_GRP_CNT_TR_IN_SEL0(obj->base, _CYHAL_TCPWM_GET_GRP(block), \
                                  _CYHAL_TCPWM_CNT_NUMBER(obj->resource)));
            TCPWM_GRP_CNT_TR_IN_SEL0(obj->base, _CYHAL_TCPWM_GET_GRP(block), _CYHAL_TCPWM_CNT_NUMBER(obj->resource)) &= ~TCPWM_GRP_CNT_V2_TR_IN_SEL0_RELOAD_SEL_Msk;
            TCPWM_GRP_CNT_TR_IN_EDGE_SEL(obj->base, _CYHAL_TCPWM_GET_GRP(block), _CYHAL_TCPWM_CNT_NUMBER(obj->resource)) &= ~TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_RELOAD_EDGE_Msk;
            break;
        case CYHAL_TCPWM_INPUT_COUNT:
            trig_index = _FLD2VAL(TCPWM_GRP_CNT_V2_TR_IN_SEL0_COUNT_SEL, TCPWM_GRP_CNT_TR_IN_SEL0(obj->base, _CYHAL_TCPWM_GET_GRP(block), \
                                  _CYHAL_TCPWM_CNT_NUMBER(obj->resource)));
            TCPWM_GRP_CNT_TR_IN_SEL0(obj->base, _CYHAL_TCPWM_GET_GRP(block), _CYHAL_TCPWM_CNT_NUMBER(obj->resource)) &= ~TCPWM_GRP_CNT_V2_TR_IN_SEL0_COUNT_SEL_Msk;
            TCPWM_GRP_CNT_TR_IN_EDGE_SEL(obj->base, _CYHAL_TCPWM_GET_GRP(block), _CYHAL_TCPWM_CNT_NUMBER(obj->resource)) &= ~TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_COUNT_EDGE_Msk;
            break;
        case CYHAL_TCPWM_INPUT_CAPTURE:
            trig_index = _FLD2VAL(TCPWM_GRP_CNT_V2_TR_IN_SEL0_CAPTURE0_SEL, TCPWM_GRP_CNT_TR_IN_SEL0(obj->base, _CYHAL_TCPWM_GET_GRP(block), \
                                  _CYHAL_TCPWM_CNT_NUMBER(obj->resource)));
            TCPWM_GRP_CNT_TR_IN_SEL0(obj->base, _CYHAL_TCPWM_GET_GRP(block), _CYHAL_TCPWM_CNT_NUMBER(obj->resource)) &= ~TCPWM_GRP_CNT_V2_TR_IN_SEL0_CAPTURE0_SEL_Msk;
            TCPWM_GRP_CNT_TR_IN_EDGE_SEL(obj->base, _CYHAL_TCPWM_GET_GRP(block), _CYHAL_TCPWM_CNT_NUMBER(obj->resource)) &= ~TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_CAPTURE0_EDGE_Msk;
            break;
       default:
            return CYHAL_TCPWM_RSLT_ERR_BAD_ARGUMENT;
    }
#else
#error Unrecognized TCPWM version
#endif

    trig_index -= (_CYHAL_TCPWM_TRIGGER_INPUTS_IDX_OFFSET[_CYHAL_TCPWM_GET_IP_BLOCK(block)]);

    cyhal_dest_t dest = _cyhal_tpwm_calculate_dest(block, trig_index);

    cy_rslt_t rslt = _cyhal_disconnect_signal(source, dest);
    if (CY_RSLT_SUCCESS == rslt)
    {
        obj->inputs[(uint32_t)signal] = CYHAL_TRIGGER_CPUSS_ZERO;
    }
    return rslt;
#else
    CY_UNUSED_PARAMETER(obj);
    CY_UNUSED_PARAMETER(signal);
    CY_UNUSED_PARAMETER(source);
    return CYHAL_TCPWM_RSLT_ERR_BAD_ARGUMENT;
#endif /* defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI) */
}

cy_rslt_t _cyhal_tcpwm_disable_output(cyhal_tcpwm_t *obj, cyhal_tcpwm_output_t signal)
{
#if defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI)
// Triggers are always generated for TCPWMv1 so this is a noop.
#if (CY_IP_MXTCPWM_VERSION == 1U) || (CY_IP_M0S8TCPWM_VERSION == 2)
    CY_UNUSED_PARAMETER(obj);
    CY_UNUSED_PARAMETER(signal);

    return CY_RSLT_SUCCESS;
#elif (CY_IP_MXTCPWM_VERSION == 2U)
    const uint8_t block = obj->resource.block_num;
    const uint8_t chnl = obj->resource.channel_num;

    uint8_t event_type = _cyhal_tcpwm_convert_output_t(signal);

    // All channels in _CYHAL_OUTPUT_TRIGGERS_USED are just ordered
    // sequentially, not ordered by blocks.
    uint8_t trig_index = _CYHAL_TCPWM_GET_ARRAY_INDEX(block, chnl);

    if(_FLD2VAL(TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT0, TCPWM_GRP_CNT_TR_OUT_SEL(obj->base, _CYHAL_TCPWM_GET_GRP(block), \
                _CYHAL_TCPWM_CNT_NUMBER(obj->resource))) == event_type)
    {
        // Disable output trigger idx 0
        TCPWM_GRP_CNT_TR_OUT_SEL(obj->base, _CYHAL_TCPWM_GET_GRP(block), _CYHAL_TCPWM_CNT_NUMBER(obj->resource)) \
                                 &= ~TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT0_Msk;
        TCPWM_GRP_CNT_TR_OUT_SEL(obj->base, _CYHAL_TCPWM_GET_GRP(block), _CYHAL_TCPWM_CNT_NUMBER(obj->resource)) \
                                 |= _VAL2FLD(TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT0, CY_TCPWM_CNT_TRIGGER_ON_DISABLED);
        _CYHAL_OUTPUT_TRIGGERS_USED[trig_index] &= ~1;
    }
    else if(_FLD2VAL(TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT1, TCPWM_GRP_CNT_TR_OUT_SEL(obj->base, _CYHAL_TCPWM_GET_GRP(block), \
                     _CYHAL_TCPWM_CNT_NUMBER(obj->resource))) == event_type)
    {
        // Disable output trigger idx 1
        TCPWM_GRP_CNT_TR_OUT_SEL(obj->base, _CYHAL_TCPWM_GET_GRP(block), _CYHAL_TCPWM_CNT_NUMBER(obj->resource)) \
                                 &= ~TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT1_Msk;
        TCPWM_GRP_CNT_TR_OUT_SEL(obj->base, _CYHAL_TCPWM_GET_GRP(block), _CYHAL_TCPWM_CNT_NUMBER(obj->resource)) \
                                 |= _VAL2FLD(TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT1, CY_TCPWM_CNT_TRIGGER_ON_DISABLED);
        _CYHAL_OUTPUT_TRIGGERS_USED[trig_index] &= ~2;
    }
    else
        return CYHAL_TCPWM_RSLT_ERR_BAD_ARGUMENT;

    return CY_RSLT_SUCCESS;
#else
#error Unrecognized TCPWM version
#endif
#else
    CY_UNUSED_PARAMETER(obj);
    CY_UNUSED_PARAMETER(signal);

    return CYHAL_TCPWM_RSLT_ERR_BAD_ARGUMENT;
#endif /* defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI) */
}

#if defined(__cplusplus)
}
#endif

#endif /* _CYHAL_DRIVER_AVAILABLE_TCPWM */
