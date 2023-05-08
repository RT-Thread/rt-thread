/*******************************************************************************
* File Name: cyhal_quaddec.c
*
* Description:
* Provides a high level interface for interacting with the Quadrature Decoder.
* This is a wrapper around the lower level PDL API.
*
********************************************************************************
* \copyright
* Copyright 2020-2022 Cypress Semiconductor Corporation (an Infineon company) or
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
 * \addtogroup group_hal_impl_quaddec QuadDec (Quadrature Decoder)
 * \ingroup group_hal_impl
 * \{
 * \section section_hal_impl_quaddec_pins Selecting Pins for Quadrature Decoding
 * To identify the pins that are available to use with the Quadrature Decoder, open the PSoC
 * device datasheet and navigate to the 'Multiple Alternate Functions' table.  Any pin that has
 * the peri.tr_io_input function can be used.
 *
 * \} group_hal_impl_quaddec
 */

#if defined(COMPONENT_CAT2)
/**
 * \addtogroup group_hal_impl_quaddec QuadDec (Quadrature Decoder)
 * \ingroup group_hal_impl
 * \{
 * \note The cyhal_quaddec_connect_digital() and cyhal_quaddec_disconnect_digital() functions are
 * not supported with this device and will return a CYHAL_QUADDEC_RSLT_ERR_NOT_SUPPORTED error if
 * it is called.  This device does not have the internal circuitry routing that this function is
 * used to configure.
 *
 * \} group_hal_impl_quaddec
 */
#endif

#include "cy_tcpwm.h"
#include "cy_tcpwm_quaddec.h"
#include "cyhal_clock.h"
#include "cyhal_gpio.h"
#include "cyhal_hwmgr.h"
#include "cyhal_interconnect.h"
#include "cyhal_quaddec.h"
#include "cyhal_syspm.h"
#include "cyhal_tcpwm_common.h"
#include "cyhal_utils.h"
#include "cyhal_hwmgr_impl.h"

#include <string.h>

#if (CYHAL_DRIVER_AVAILABLE_QUADDEC)

#if defined(__cplusplus)
extern "C" {
#endif

#define _CYHAL_CNT_NUM _CYHAL_TCPWM_CNT_NUMBER(obj->tcpwm.resource)

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || \
    defined(COMPONENT_CAT1D) || defined(COMPONENT_CAT5)
static cyhal_tcpwm_input_t _cyhal_quaddec_translate_input_signal(cyhal_quaddec_input_t signal);
#endif

static inline cy_rslt_t _cyhal_quaddec_configure_clock(cyhal_tcpwm_t *tcpwm, en_clk_dst_t pclk, uint32_t frequency)
{
    cy_rslt_t rslt;

    #if !defined(COMPONENT_CAT5)
    const cyhal_clock_tolerance_t tolerance = {
        .type = CYHAL_TOLERANCE_PERCENT,
        .value = 2,
    };
    #endif

    #if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
        rslt = _cyhal_utils_allocate_clock(&tcpwm->clock, &tcpwm->resource, CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT, true);
    #elif defined(COMPONENT_CAT2)
        rslt = cyhal_clock_allocate(&tcpwm->clock, CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT);
    #elif defined(COMPONENT_CAT5)
        rslt = CY_RSLT_SUCCESS; // No need to allocate the TCPWM clock as it is a shared resource
    #else
        #warning "No clock allocated for QuadDec"
        rslt = CYHAL_QUADDEC_RSLT_ERR_CLOCK_INIT;
    #endif

    if (rslt == CY_RSLT_SUCCESS)
    {
        tcpwm->dedicated_clock = true;

        #if defined(COMPONENT_CAT5)
            uint32_t current_freq = _cyhal_utils_get_peripheral_clock_frequency(&(tcpwm->resource));
            if (frequency <= current_freq)
            {
                uint32_t divider = ((current_freq + frequency - 1) / frequency);
                // _set_divider doesn't use this with CAT5, but to avoid warnings here is what it would use
                en_clk_dst_t clk_dst = (en_clk_dst_t)(_CYHAL_TCPWM_DATA[_CYHAL_TCPWM_ADJUST_BLOCK_INDEX(tcpwm->resource.block_num)].clock_dst + tcpwm->resource.channel_num);

                if (_cyhal_utils_peri_pclk_set_divider(clk_dst, &tcpwm->clock, (divider - 1)) == CY_RSLT_SUCCESS)
                {
                    return CY_RSLT_SUCCESS;
                }
            }
        #else
            if (cyhal_clock_set_frequency(&tcpwm->clock, frequency, &tolerance) == CY_RSLT_SUCCESS)
            {
                if (_cyhal_utils_peri_pclk_assign_divider(pclk, &(tcpwm->clock)) == CY_SYSCLK_SUCCESS)
                {
                    cyhal_clock_set_enabled(&tcpwm->clock, true, false);
                    return CY_RSLT_SUCCESS;
                }
            }
        #endif
    }

    return CYHAL_QUADDEC_RSLT_ERR_CLOCK_INIT;
}

#if defined(COMPONENT_CAT2)
//--------------------------------------------------------------------------------------------------
// _cyhal_quaddec_connect_pin
//
// NOTE: This function should be called after the pin has been initialized with cyhal_gpio_init().
//--------------------------------------------------------------------------------------------------
cy_rslt_t _cyhal_quaddec_connect_pin(cyhal_quaddec_input_t signal, cyhal_gpio_t pin,
                                     TCPWM_Type* base, uint8_t channel_num)
{
#if defined(CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_TR_IN)
    bool found = false;
    uint8_t index;
    uint8_t array_size = sizeof(cyhal_pin_map_tcpwm_tr_in) / sizeof(cyhal_resource_pin_mapping_t);
    cyhal_resource_pin_mapping_t mapping;

    // Search through cyhal_pin_map_tcpwm_tr_in to determine if pin can be
    // used to drive a trigger line.
    for (index = 0; index < array_size; index++)
    {
        mapping = cyhal_pin_map_tcpwm_tr_in[index];

        if (mapping.pin == pin)
        {
            found = true;
            Cy_GPIO_SetHSIOM(CYHAL_GET_PORTADDR(pin), CYHAL_GET_PIN(pin), mapping.hsiom);
            break;
        }
    }

    if (!found)
    {
        return CYHAL_GPIO_RSLT_ERR_NO_OUTPUT_SIGNAL;
    }

    switch (signal)
    {
        case CYHAL_QUADDEC_INPUT_PHI_A:
            TCPWM_CNT_TR_CTRL0(base, channel_num) &= ~TCPWM_CNT_TR_CTRL0_COUNT_SEL_Msk;
            TCPWM_CNT_TR_CTRL0(base, channel_num) |= _VAL2FLD(TCPWM_CNT_TR_CTRL0_COUNT_SEL,
                                                              (uint32_t)(mapping.channel_num) + 2);
            TCPWM_CNT_TR_CTRL1(base, channel_num) &= ~TCPWM_CNT_TR_CTRL1_COUNT_EDGE_Msk;
            TCPWM_CNT_TR_CTRL1(base, channel_num) |= _VAL2FLD(TCPWM_CNT_TR_CTRL1_COUNT_EDGE,
                                                              CYHAL_EDGE_TYPE_RISING_EDGE);
            break;

        case CYHAL_QUADDEC_INPUT_PHI_B:
            TCPWM_CNT_TR_CTRL0(base, channel_num) &= ~TCPWM_CNT_TR_CTRL0_START_SEL_Msk;
            TCPWM_CNT_TR_CTRL0(base, channel_num) |= _VAL2FLD(TCPWM_CNT_TR_CTRL0_START_SEL,
                                                              (uint32_t)(mapping.channel_num) + 2);
            TCPWM_CNT_TR_CTRL1(base, channel_num) &= ~TCPWM_CNT_TR_CTRL1_START_EDGE_Msk;
            TCPWM_CNT_TR_CTRL1(base, channel_num) |= _VAL2FLD(TCPWM_CNT_TR_CTRL1_START_EDGE,
                                                              CYHAL_EDGE_TYPE_RISING_EDGE);
            break;

        case CYHAL_QUADDEC_INPUT_INDEX:
            TCPWM_CNT_TR_CTRL0(base, channel_num) &= ~TCPWM_CNT_TR_CTRL0_RELOAD_SEL_Msk;
            TCPWM_CNT_TR_CTRL0(base, channel_num) |= _VAL2FLD(TCPWM_CNT_TR_CTRL0_RELOAD_SEL,
                                                              (uint32_t)(mapping.channel_num) + 2);
            TCPWM_CNT_TR_CTRL1(base, channel_num) &= ~TCPWM_CNT_TR_CTRL1_RELOAD_EDGE_Msk;
            TCPWM_CNT_TR_CTRL1(base, channel_num) |= _VAL2FLD(TCPWM_CNT_TR_CTRL1_RELOAD_EDGE,
                                                              CYHAL_EDGE_TYPE_RISING_EDGE);
            break;

        default:
            return CYHAL_GPIO_RSLT_ERR_NO_OUTPUT_SIGNAL;
    }

    return CY_RSLT_SUCCESS;
#else
    CY_UNUSED_PARAMETER(signal);
    CY_UNUSED_PARAMETER(pin);
    CY_UNUSED_PARAMETER(base);
    CY_UNUSED_PARAMETER(channel_num);

    return CYHAL_GPIO_RSLT_ERR_NO_OUTPUT_SIGNAL;
#endif /* defined(CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_TR_IN) */
}
#endif

static cy_rslt_t _cyhal_quaddec_pin_init(cyhal_quaddec_t *obj, cyhal_gpio_t pin, cyhal_gpio_t *obj_pin, cyhal_signal_type_t signal_type, cyhal_quaddec_input_t input)
{
    if (NC == pin)
    {
        return CYHAL_QUADDEC_RSLT_ERR_BAD_ARGUMENT;
    }

    #if defined (COMPONENT_CAT5)
        cy_rslt_t rslt = CYHAL_QUADDEC_RSLT_ERR_BAD_ARGUMENT;
        const cyhal_resource_pin_mapping_t* pinMap = _CYHAL_UTILS_GET_RESOURCE(pin, cyhal_pin_map_tcpwm_tr_all_cnt_in);

        if (pinMap != NULL)
            rslt = _cyhal_utils_reserve_and_connect(pinMap, CYHAL_PIN_MAP_DRIVE_MODE_TCPWM_TR_IN);
        else
            rslt = CYHAL_HWMGR_RSLT_ERR_INVALID; // Note: Intentional to match PSoC behavior
    #else
        cy_rslt_t rslt = cyhal_gpio_init(pin, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, false);
    #endif

    if (rslt == CY_RSLT_SUCCESS)
    {
        *obj_pin = pin;
        #if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || \
            defined(COMPONENT_CAT1D) || defined(COMPONENT_CAT5)
        uint8_t idx = (uint8_t)_cyhal_quaddec_translate_input_signal(input);

        #if !defined(COMPONENT_CAT5)
            // Already taken care of in cyhal_connect_pin() for CAT5
            rslt = cyhal_gpio_enable_output(pin, signal_type, &(obj->tcpwm.inputs[idx]));
        #endif

        if (rslt == CY_RSLT_SUCCESS)
        {
            rslt = cyhal_quaddec_connect_digital(obj, obj->tcpwm.inputs[idx], input);
            if (rslt != CY_RSLT_SUCCESS)
            {
                obj->tcpwm.inputs[idx] = CYHAL_TRIGGER_CPUSS_ZERO;
            }
        }
        #elif defined(COMPONENT_CAT2)
        CY_UNUSED_PARAMETER(signal_type);
        rslt = _cyhal_quaddec_connect_pin(input, pin, obj->tcpwm.base,
                                          obj->tcpwm.resource.channel_num);
        #else
        #warning "_cyhal_quaddec_pin_init encountered unsupported architecture"
        #endif
    }
    return rslt;
}

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
static uint8_t _cyhal_quaddec_get_phy_a_input_dest_trig_idx;
static cyhal_dest_t _cyhal_quaddec_get_phy_a_input_dest(uint8_t block_num, uint8_t channel_num)
{
    CY_UNUSED_PARAMETER(channel_num);
    uint8_t trig_idx = _cyhal_quaddec_get_phy_a_input_dest_trig_idx;
    if (trig_idx >= _CYHAL_TCPWM_TRIGGER_INPUTS_PER_BLOCK[_CYHAL_TCPWM_GET_IP_BLOCK(block_num)])
    {
        /* We cannot use unexisting for current block number index, so this is rather incorrect param situation.
        There is no possibility to return warning/error code, setting trig index to default 0. */
        trig_idx = 0;
    }
    return _cyhal_tpwm_calculate_dest(block_num, trig_idx);
}
#endif

cy_rslt_t _cyhal_quaddec_init_hw(cyhal_quaddec_t *obj, const cy_stc_tcpwm_quaddec_config_t *config, const cyhal_clock_t *clk,
                                 uint32_t frequency /* Only required if clk == NULL */)
{
    obj->last_counter_value = 1 << (_CYHAL_TCPWM_DATA[_CYHAL_TCPWM_ADJUST_BLOCK_INDEX(obj->tcpwm.resource.block_num)].max_count - 1);

    obj->tcpwm.base = _CYHAL_TCPWM_DATA[_CYHAL_TCPWM_ADJUST_BLOCK_INDEX(obj->tcpwm.resource.block_num)].base;
    _cyhal_tcpwm_init_data(&obj->tcpwm);

    cy_rslt_t rslt = Cy_TCPWM_QuadDec_Init(obj->tcpwm.base, _CYHAL_CNT_NUM, config);

    // Clock configuration
    if (CY_RSLT_SUCCESS == rslt)
    {
        en_clk_dst_t pclk =(en_clk_dst_t)(_CYHAL_TCPWM_DATA[
            _CYHAL_TCPWM_ADJUST_BLOCK_INDEX(obj->tcpwm.resource.block_num)].clock_dst + obj->tcpwm.resource.channel_num);

        if (clk != NULL)
        {
            if (frequency != 0)
            {
                rslt = CYHAL_QUADDEC_RSLT_ERR_BAD_ARGUMENT;
            }
            else
            {
                obj->tcpwm.clock = *clk;

                if (_cyhal_utils_peri_pclk_assign_divider(pclk, &(obj->tcpwm.clock)) != CY_SYSCLK_SUCCESS)
                {
                    rslt = CYHAL_QUADDEC_RSLT_ERR_CLOCK_INIT;
                }
            }
        }
        else
        {
            rslt = _cyhal_quaddec_configure_clock(&obj->tcpwm, pclk, frequency);
        }

        if (rslt == CY_RSLT_SUCCESS)
        {
            obj->tcpwm.clock_hz = cyhal_clock_get_frequency(&obj->tcpwm.clock);
        }
    }
    return rslt;
}

cy_rslt_t cyhal_quaddec_init(cyhal_quaddec_t *obj, cyhal_gpio_t phi_a, cyhal_gpio_t phi_b,
                             cyhal_gpio_t index, cyhal_quaddec_resolution_t resolution,
                             const cyhal_clock_t *clk, uint32_t frequency)
{
    CY_ASSERT(obj != NULL);
    cy_rslt_t rslt = CY_RSLT_SUCCESS;

    // Initialize the quadrature object
    // Explicitly marked not allocated resources as invalid to prevent freeing them.
    memset(obj, 0, sizeof(cyhal_quaddec_t));
    obj->phi_a = NC;
    obj->phi_b = NC;
    obj->index = NC;
    obj->tcpwm.resource.type = CYHAL_RSC_INVALID;

    // Allocate TCPWM resource
    #if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)  || \
        defined(COMPONENT_CAT1D)
    if (NC == phi_a)
    {
        return CYHAL_QUADDEC_RSLT_ERR_BAD_ARGUMENT;
    }

    cyhal_source_t phy_a_src;
    uint8_t phy_a_idx = (uint8_t)_cyhal_quaddec_translate_input_signal(CYHAL_QUADDEC_INPUT_PHI_A);
    rslt = cyhal_gpio_init(phi_a, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, false);

    if (rslt == CY_RSLT_SUCCESS)
    {
        obj->phi_a = phi_a;
        rslt = cyhal_gpio_enable_output(phi_a, CYHAL_SIGNAL_TYPE_LEVEL, &phy_a_src);

        uint16_t max_trig_cnt = 0;
        for (size_t idx = 0; idx < (sizeof(_CYHAL_TCPWM_TRIGGER_INPUTS_PER_BLOCK) / sizeof(_CYHAL_TCPWM_TRIGGER_INPUTS_PER_BLOCK[0])); ++idx)
        {
            if (max_trig_cnt < _CYHAL_TCPWM_TRIGGER_INPUTS_PER_BLOCK[idx])
            {
                max_trig_cnt = _CYHAL_TCPWM_TRIGGER_INPUTS_PER_BLOCK[idx];
            }
        }

        if (rslt == CY_RSLT_SUCCESS)
        {
            _cyhal_quaddec_get_phy_a_input_dest_trig_idx = 0;
            do
            {
                rslt = _cyhal_hwmgr_allocate_with_connection(CYHAL_RSC_TCPWM, &phy_a_src,
                    NULL, NULL, _cyhal_quaddec_get_phy_a_input_dest, &obj->tcpwm.resource);
                _cyhal_quaddec_get_phy_a_input_dest_trig_idx++;
            } while (CY_RSLT_SUCCESS != rslt && _cyhal_quaddec_get_phy_a_input_dest_trig_idx < max_trig_cnt);
        }
    }
    #else
        rslt = cyhal_hwmgr_allocate(CYHAL_RSC_TCPWM, &obj->tcpwm.resource);
    #endif

    // Basic configuration of TCPWM for quadrature functionality
    if (rslt == CY_RSLT_SUCCESS)
    {
        cy_stc_tcpwm_quaddec_config_t config;

        memset(&config, 0, sizeof(cy_stc_tcpwm_quaddec_config_t));

        config.resolution = resolution;

        #if (CY_IP_MXTCPWM_VERSION >= 2U)
        config.phiAInputMode  = CY_TCPWM_INPUT_LEVEL;                // Pass thorugh (no edge detection)
        config.phiBInputMode  = CY_TCPWM_INPUT_LEVEL;                // Pass thorugh (no edge detection)
        config.trigger0Event  = CY_TCPWM_CNT_TRIGGER_ON_DISABLED;    // Disable output trigger0 event generation
        config.trigger1Event  = CY_TCPWM_CNT_TRIGGER_ON_DISABLED;    // Disable output trigger1 event generation
        #endif

        // This function is only used to set the resolution and configure the TCPWM for quadrature mode.
        // It also configures the inputs, but that will be overwritten by cyhal_quaddec_connect_digital().
        // So, this must be called before that function is called.
        rslt = _cyhal_quaddec_init_hw(obj, &config, clk, frequency);
    }

    // Pin configuration
    if (rslt == CY_RSLT_SUCCESS)
    {
        // See note above about CAT5 triggers
        #if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || \
            defined(COMPONENT_CAT1D) // already initialized above
            obj->tcpwm.inputs[phy_a_idx] = phy_a_src;;
            rslt = cyhal_quaddec_connect_digital(obj, obj->tcpwm.inputs[phy_a_idx], CYHAL_QUADDEC_INPUT_PHI_A);
        #else
            rslt = _cyhal_quaddec_pin_init(obj, phi_a, &(obj->phi_a), CYHAL_SIGNAL_TYPE_LEVEL, CYHAL_QUADDEC_INPUT_PHI_A);
        #endif

        if (rslt == CY_RSLT_SUCCESS)
        {
            rslt = _cyhal_quaddec_pin_init(obj, phi_b, &(obj->phi_b), CYHAL_SIGNAL_TYPE_LEVEL, CYHAL_QUADDEC_INPUT_PHI_B);
        }

        if (index != NC)
        {
            if (rslt == CY_RSLT_SUCCESS)
            {
                rslt = _cyhal_quaddec_pin_init(obj, index, &(obj->index), CYHAL_SIGNAL_TYPE_EDGE, CYHAL_QUADDEC_INPUT_INDEX);
            }
        }
        // See note above about CAT5 triggers
        #if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || \
            defined(COMPONENT_CAT1D)
        else
        {
            uint8_t idx = (uint8_t)_cyhal_quaddec_translate_input_signal(CYHAL_QUADDEC_INPUT_INDEX);
            obj->tcpwm.inputs[idx] = CYHAL_TRIGGER_CPUSS_ZERO;
        }
        #endif
    }

    // Enable the quadrature function
    if (rslt == CY_RSLT_SUCCESS)
    {
        Cy_TCPWM_QuadDec_Enable(obj->tcpwm.base, _CYHAL_CNT_NUM);
    }
    else
    {
        cyhal_quaddec_free(obj);
    }

    return rslt;
}

cy_rslt_t cyhal_quaddec_init_cfg(cyhal_quaddec_t *obj, const cyhal_quaddec_configurator_t *cfg)
{
    memset(obj, 0, sizeof(cyhal_quaddec_t));
    /* These pins are probably actually connected, but that is handled by the configurator */
    obj->phi_a = NC;
    obj->phi_b = NC;
    obj->index = NC;
    obj->tcpwm.resource = *cfg->resource;
    obj->tcpwm.owned_by_configurator = true;
    cy_rslt_t result = _cyhal_quaddec_init_hw(obj, cfg->config, cfg->clock, 0u /* Ignored because configurator provides a clock */);

    /* No need to populate obj->tcpwm.inputs because that is only used to interact with the interconnect
     * driver, and all of our routing here was configured by the configurator */

    if (CY_RSLT_SUCCESS == result)
    {
        Cy_TCPWM_QuadDec_Enable(obj->tcpwm.base, _CYHAL_CNT_NUM);
    }
    else
    {
        cyhal_quaddec_free(obj);
    }
    return result;
}

void cyhal_quaddec_free(cyhal_quaddec_t *obj)
{
    CY_ASSERT(obj != NULL);
    #if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || \
        defined(COMPONENT_CAT1D) || defined(COMPONENT_CAT5)
    uint8_t idx_phi_a = (uint8_t)_cyhal_quaddec_translate_input_signal(CYHAL_QUADDEC_INPUT_PHI_A);
    if ((obj->phi_a != NC) && (obj->tcpwm.inputs[idx_phi_a] != CYHAL_TRIGGER_CPUSS_ZERO))
    {
        cyhal_quaddec_disconnect_digital(obj, obj->tcpwm.inputs[idx_phi_a], CYHAL_QUADDEC_INPUT_PHI_A);
    }
    uint8_t idx_phi_b = (uint8_t)_cyhal_quaddec_translate_input_signal(CYHAL_QUADDEC_INPUT_PHI_B);
    if ((obj->phi_b != NC) && (obj->tcpwm.inputs[idx_phi_b] != CYHAL_TRIGGER_CPUSS_ZERO))
    {
        cyhal_quaddec_disconnect_digital(obj, obj->tcpwm.inputs[idx_phi_b], CYHAL_QUADDEC_INPUT_PHI_B);
    }
    uint8_t idx_index = (uint8_t)_cyhal_quaddec_translate_input_signal(CYHAL_QUADDEC_INPUT_INDEX);
    if ((obj->index != NC) && (obj->tcpwm.inputs[idx_index] != CYHAL_TRIGGER_CPUSS_ZERO))
    {
        cyhal_quaddec_disconnect_digital(obj, obj->tcpwm.inputs[idx_index], CYHAL_QUADDEC_INPUT_INDEX);
    }
    #endif
    _cyhal_utils_release_if_used(&obj->phi_a);
    _cyhal_utils_release_if_used(&obj->phi_b);
    _cyhal_utils_release_if_used(&obj->index);
    if (obj->tcpwm.resource.type != CYHAL_RSC_INVALID)
    {
        _cyhal_tcpwm_free(&obj->tcpwm);
    }
}

cy_rslt_t cyhal_quaddec_start(cyhal_quaddec_t *obj)
{
    CY_ASSERT(obj != NULL);
    if (_cyhal_tcpwm_pm_transition_pending())
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }
    Cy_TCPWM_QuadDec_Enable(obj->tcpwm.base, _CYHAL_CNT_NUM);

    // Trigger reload/index the QuadDec.
    // From the TRM, "A reload trigger must be provided through firmware to start the counter if
    // the hardware reload signal is not enabled."
    #if defined(CY_IP_MXTCPWM) && (CY_IP_MXTCPWM_VERSION >= 2)
    Cy_TCPWM_TriggerReloadOrIndex_Single(obj->tcpwm.base, _CYHAL_CNT_NUM);
    #else
    Cy_TCPWM_TriggerReloadOrIndex(obj->tcpwm.base, 1 << _CYHAL_CNT_NUM);
    #endif

    obj->last_counter_value = 1 << (_CYHAL_TCPWM_DATA[_CYHAL_TCPWM_ADJUST_BLOCK_INDEX(obj->tcpwm.resource.block_num)].max_count - 1);

    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_quaddec_stop(cyhal_quaddec_t *obj)
{
    CY_ASSERT(obj != NULL);
    Cy_TCPWM_QuadDec_Disable(obj->tcpwm.base, _CYHAL_CNT_NUM);
    return CY_RSLT_SUCCESS;
}

int32_t cyhal_quaddec_get_delta(cyhal_quaddec_t *obj)
{
    CY_ASSERT(obj != NULL);

    uint32_t midpoint = 1 << (_CYHAL_TCPWM_DATA[_CYHAL_TCPWM_ADJUST_BLOCK_INDEX(obj->tcpwm.resource.block_num)].max_count - 1);
    uint32_t max_delta = midpoint >> 1;
    uint32_t max_counter_value = (midpoint == 0x8000U) ? 0xFFFFU : 0xFFFFFFFFU;
    uint32_t current_counter_value = Cy_TCPWM_QuadDec_GetCounter(obj->tcpwm.base, _CYHAL_CNT_NUM);
    int32_t  delta = current_counter_value - obj->last_counter_value;

    // Overflow has occurred
    if (delta < (int32_t)(-max_delta))
    {
        delta = max_counter_value - obj->last_counter_value;
        delta += current_counter_value - midpoint;
    }
    // Underflow has occurred
    else if (delta > (int32_t)max_delta)
    {
        delta = (int32_t)(-obj->last_counter_value);
        delta += current_counter_value - midpoint;
    }

    obj->last_counter_value = current_counter_value;

    return delta;
}

uint32_t cyhal_quaddec_read_counter(const cyhal_quaddec_t *obj)
{
    CY_ASSERT(obj != NULL);
    return Cy_TCPWM_QuadDec_GetCounter(obj->tcpwm.base, _CYHAL_CNT_NUM);
}

uint32_t cyhal_quaddec_read_capture(const cyhal_quaddec_t *obj)
{
    CY_ASSERT(obj != NULL);
    #if defined(CY_IP_MXTCPWM) && (CY_IP_MXTCPWM_VERSION >= 2)
    return Cy_TCPWM_QuadDec_GetCapture0Val(obj->tcpwm.base, _CYHAL_CNT_NUM);
    #else
    return Cy_TCPWM_QuadDec_GetCapture(obj->tcpwm.base, _CYHAL_CNT_NUM);
    #endif
}

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || \
    defined(COMPONENT_CAT1D) || defined(COMPONENT_CAT5)

static cyhal_tcpwm_input_t _cyhal_quaddec_translate_input_signal(cyhal_quaddec_input_t signal)
{
    switch (signal)
    {
        case CYHAL_QUADDEC_INPUT_PHI_A:
            return CYHAL_TCPWM_INPUT_COUNT;
        case CYHAL_QUADDEC_INPUT_PHI_B:
            return CYHAL_TCPWM_INPUT_START;
        case CYHAL_QUADDEC_INPUT_STOP:
            return CYHAL_TCPWM_INPUT_STOP;
        case CYHAL_QUADDEC_INPUT_INDEX:
            return CYHAL_TCPWM_INPUT_RELOAD;
        default:
            CY_ASSERT(false);
            return (cyhal_tcpwm_input_t)0;
    }
}

cy_rslt_t cyhal_quaddec_connect_digital2(cyhal_quaddec_t *obj, cyhal_source_t source, cyhal_quaddec_input_t signal, cyhal_edge_type_t edge_type)
{
    cyhal_tcpwm_input_t tcpwm_signal = _cyhal_quaddec_translate_input_signal(signal);
    return _cyhal_tcpwm_connect_digital(&(obj->tcpwm), source, tcpwm_signal, edge_type);
}

cy_rslt_t cyhal_quaddec_connect_digital(cyhal_quaddec_t *obj, cyhal_source_t source, cyhal_quaddec_input_t signal)
{
#if defined(CY_IP_M0S8PERI_TR) || defined(CY_IP_MXPERI_TR) || defined(CY_IP_MXSPERI)
    /* Signal type just tells us edge vs. level, but TCPWM lets you customize which edge you want. So default
     * to rising edge. If the application cares about the edge type, it can use connect_digital2 */
    cyhal_signal_type_t signal_type = _CYHAL_TRIGGER_GET_SOURCE_TYPE(source);
    cyhal_edge_type_t edge_type = (signal_type == CYHAL_SIGNAL_TYPE_LEVEL) ? CYHAL_EDGE_TYPE_LEVEL : CYHAL_EDGE_TYPE_RISING_EDGE;
    return cyhal_quaddec_connect_digital2(obj, source, signal, edge_type);
#else
    CY_UNUSED_PARAMETER(obj);
    CY_UNUSED_PARAMETER(source);
    CY_UNUSED_PARAMETER(signal);
    return CYHAL_QUADDEC_RSLT_ERR_BAD_ARGUMENT;
#endif
}

cy_rslt_t cyhal_quaddec_disconnect_digital(cyhal_quaddec_t *obj, cyhal_source_t source, cyhal_quaddec_input_t signal)
{
    return _cyhal_tcpwm_disconnect_digital(&(obj->tcpwm), source,
                                           _cyhal_quaddec_translate_input_signal(signal));
}

#elif defined(COMPONENT_CAT2)

cy_rslt_t cyhal_quaddec_connect_digital(cyhal_quaddec_t *obj, cyhal_source_t source, cyhal_quaddec_input_t signal)
{
    CY_UNUSED_PARAMETER(obj);
    CY_UNUSED_PARAMETER(source);
    CY_UNUSED_PARAMETER(signal);
    return CYHAL_QUADDEC_RSLT_ERR_NOT_SUPPORTED;
}

cy_rslt_t cyhal_quaddec_disconnect_digital(cyhal_quaddec_t *obj, cyhal_source_t source, cyhal_quaddec_input_t signal)
{
    CY_UNUSED_PARAMETER(obj);
    CY_UNUSED_PARAMETER(source);
    CY_UNUSED_PARAMETER(signal);
    return CYHAL_QUADDEC_RSLT_ERR_NOT_SUPPORTED;
}

#endif

static cyhal_tcpwm_output_t _cyhal_quaddec_translate_output_signal(cyhal_quaddec_output_t signal)
{
    switch (signal)
    {
        case CYHAL_QUADDEC_OUTPUT_COMPARE_MATCH:
            return CYHAL_TCPWM_OUTPUT_COMPARE_MATCH;
        default:
            CY_ASSERT(false);
            return (cyhal_tcpwm_output_t)0;
    }
}

cy_rslt_t cyhal_quaddec_enable_output(cyhal_quaddec_t *obj, cyhal_quaddec_output_t signal, cyhal_source_t *source)
{
    if (signal != CYHAL_QUADDEC_OUTPUT_COMPARE_MATCH)
    {
        return CYHAL_QUADDEC_RSLT_ERR_BAD_ARGUMENT;
    }

    return _cyhal_tcpwm_enable_output(&(obj->tcpwm), _cyhal_quaddec_translate_output_signal(signal), source);
}

cy_rslt_t cyhal_quaddec_disable_output(cyhal_quaddec_t *obj, cyhal_quaddec_output_t signal)
{
    if (signal != CYHAL_QUADDEC_OUTPUT_COMPARE_MATCH)
        return CYHAL_QUADDEC_RSLT_ERR_BAD_ARGUMENT;

    return _cyhal_tcpwm_disable_output(&(obj->tcpwm), _cyhal_quaddec_translate_output_signal(signal));
}

#if defined(__cplusplus)
}
#endif

#endif // CYHAL_DRIVER_AVAILABLE_QUADDEC
