/*******************************************************************************
* \file cyhal_dac.c
*
* \brief
* Provides a high level interface for interacting with the Infineon Digital/Analog converter.
* This interface abstracts out the chip specific details. If any chip specific
* functionality is necessary, or performance is critical the low level functions
* can be used directly.
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

#include <limits.h>
#include <math.h>
#include <string.h> // For memset

#include "cyhal_analog_common.h"
#include "cyhal_dac.h"
#include "cyhal_gpio.h"
#include "cyhal_hwmgr.h"
#include "cyhal_utils.h"
#include "cyhal_syspm.h"
#include "cy_pdl.h"

/**
* \addtogroup group_hal_impl_dac DAC (Digital to Analog Converter)
* \ingroup group_hal_impl
*
* \section group_hal_impl_dac_power Power Level Mapping
* The following table shows how the HAL-defined power levels map to the hardware-specific power levels
* when cyhal_dac uses output pin buffered mode (with opamp). Unbuffered mode only supports ON and OFF.
* | HAL Power Level                | Opamp Power Level   |
* | ------------------------------ | ------------------- |
* | @ref CYHAL_POWER_LEVEL_HIGH    | CY_CTB_POWER_HIGH   |
* | @ref CYHAL_POWER_LEVEL_MEDIUM  | CY_CTB_POWER_MEDIUM |
* | @ref CYHAL_POWER_LEVEL_LOW     | CY_CTB_POWER_LOW    |
* | @ref CYHAL_POWER_LEVEL_DEFAULT | CY_CTB_POWER_MEDIUM |
*
* cyhal_dac automatically choose between buffered and unbuffered mode by selecting pin.
* Unbuffered mode - dac pin, buffered - opamp pin.
* Buffered mode take care of reserving and configuring the opamp (OA0).
* If AREF voltage reference source is selected cyhal_dac takes care of reserving and configuring the opamp (OA1).
* By default cyhal_dac use VDDA voltage reference source. Use @ref cyhal_dac_set_reference() to change
* between @ref CYHAL_DAC_REF_VDDA and @ref CYHAL_DAC_REF_VREF voltage reference sources.
*
* \note When initializing the DAC via @ref cyhal_dac_init_cfg, if opamps are required (either for buffered output
* or for buffering the AREF output when @ref CYHAL_DAC_REF_VREF is used) then they must be separately configured
* via @ref cyhal_opamp_init_cfg before the DAC is initialized. However, once the DAC is initialized, the
* @ref cyhal_dac_set_power function will update the power mode for the opamp(s) in the same manner that it
* does for DAC instances initialized via @ref cyhal_dac_init.
* \note When the DAC has been initialized via @ref cyhal_dac_init_cfg, the @ref cyhal_dac_set_reference function
* is not supported and will return @ref CYHAL_DAC_RSLT_INVALID_CONFIGURATOR. This is because the @ref
* cyhal_dac_set_reference function needs to manipulate the configuration and routing for OA1, and in this scenario
* that configuration and routing is owned by the configurator.
*/


#if (CYHAL_DRIVER_AVAILABLE_DAC)

#if defined(__cplusplus)
extern "C"
{
#endif

#define _CYHAL_DAC_VALUE_SCALING_FACTOR (UINT16_MAX / CY_CTDAC_UNSIGNED_MAX_CODE_VALUE)

static CTDAC_Type *const _cyhal_dac_base[] = {
#if (CY_IP_MXS40PASS_CTDAC_INSTANCES > 0)
    CTDAC0,
#endif
#if (CY_IP_MXS40PASS_CTDAC_INSTANCES > 1)
    CTDAC1,
#endif
#if (CY_IP_MXS40PASS_CTDAC_INSTANCES > 2)
#warning Unhandled CTDAC instance count
#endif
};

static const cy_stc_ctdac_config_t _CYHAL_DAC_DEFAULT_CONFIG =
{
    .refSource = CY_CTDAC_REFSOURCE_VDDA,
    .formatMode = CY_CTDAC_FORMAT_UNSIGNED,
    .updateMode = CY_CTDAC_UPDATE_DIRECT_WRITE,
    .deglitchMode = CY_CTDAC_DEGLITCHMODE_UNBUFFERED,
    .outputMode = CY_CTDAC_OUTPUT_VALUE,
    //.outputBuffer is configured automatically depending on pin choice
    .deepSleep = CY_CTDAC_DEEPSLEEP_ENABLE,
    .deglitchCycles = 0,
    .value = 0,
    .nextValue = 0,
    .enableInterrupt = true,
    .configClock = false,
    // The following values are simply placeholders because configClock is false
    .dividerType = CY_SYSCLK_DIV_8_BIT,
    .dividerNum = 0,
    .dividerIntValue = 0,
    .dividerFracValue = 0,
};

#if defined(CY_IP_MXS40PASS_CTB)
static const cy_stc_ctb_opamp_config_t cyhal_opamp_default_config =
{
    .deepSleep    = CY_CTB_DEEPSLEEP_ENABLE,
    .oaPower      = CY_CTB_POWER_MEDIUM,
    .oaMode       = CY_CTB_MODE_OPAMP1X,
    .oaPump       = CY_CTB_PUMP_ENABLE,
    .oaCompEdge   = CY_CTB_COMP_EDGE_DISABLE,
    .oaCompLevel  = CY_CTB_COMP_DSI_TRIGGER_OUT_LEVEL,
    .oaCompBypass = CY_CTB_COMP_BYPASS_SYNC,
    .oaCompHyst   = CY_CTB_COMP_HYST_DISABLE,
    .oaCompIntrEn = true,
};

/* We can safely assume these indices even if we're owned by a configurator, because
 * the hardware does not support any other connections to the vout and ref in terminals */
static const uint8_t OPAMP_IDX_OUTPUT = 0;
static const uint8_t OPAMP_IDX_REF    = 1;
#endif

#if defined(CY_IP_MXS40PASS_CTB)
static bool _cyhal_dac_is_output_buffered(const cyhal_dac_t *obj)
{
    /* C06 enables the voutsw terminal on the CTDAC block, which is hard-wired to a pin */
    return (0u == (obj->base_dac->CTDAC_SW & CTDAC_CTDAC_SW_CTDO_CO6_Msk));
}
#endif /* defined(CY_IP_MXS40PASS_CTB) */

static bool _cyhal_dac_is_external_reference(const cyhal_dac_t *obj)
{
    /* CVD connects the DAC reference input to VDDA. It will be opened if the DAC is driven
     * by an external reference (buffered through OA1) instead */
    return (0u == (obj->base_dac->CTDAC_SW & CTDAC_CTDAC_SW_CTDD_CVD_Msk));
}

static uint32_t _cyhal_dac_convert_reference(cyhal_dac_ref_t ref)
{
    switch(ref)
        {
            case CYHAL_DAC_REF_VDDA:
                return CY_CTDAC_REFSOURCE_VDDA;
            case CYHAL_DAC_REF_VREF:
                return CY_CTDAC_REFSOURCE_EXTERNAL;
            default:
                CY_ASSERT(false);
                return CY_CTDAC_REFSOURCE_VDDA;
        }
}

#if defined(CY_IP_MXS40PASS_CTB)
static cy_rslt_t _cyhal_dac_configure_oa0(cyhal_dac_t *obj, bool init)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    CY_ASSERT(false == obj->owned_by_configurator);
    if (init && (CYHAL_RSC_INVALID != obj->resource_opamp.type))
    {
        /* Configure OA0 for buffered output */
        /* OA0 require non defaut CY_CTB_MODE_OPAMP10X */
        cy_stc_ctb_opamp_config_t config = cyhal_opamp_default_config;
        config.oaMode = CY_CTB_MODE_OPAMP10X;
        result = Cy_CTB_OpampInit(obj->base_opamp, CY_CTB_OPAMP_0, &config);
        Cy_CTB_SetAnalogSwitch(obj->base_opamp, CY_CTB_SWITCH_OA0_SW, CY_CTB_SW_OA0_NEG_OUT_MASK | CY_CTB_SW_OA0_OUT_SHORT_1X_10X_MASK, CY_CTB_SWITCH_CLOSE);
        Cy_CTB_SetAnalogSwitch(obj->base_opamp, CY_CTB_SWITCH_CTD_SW, CY_CTB_SW_CTD_OUT_CHOLD_MASK | CY_CTB_SW_CTD_CHOLD_OA0_POS_MASK, CY_CTB_SWITCH_CLOSE);
        cyhal_analog_ctb_init(obj->base_opamp);
    }
    else
    {
        /* Open switches OA0 if used */
        Cy_CTB_SetAnalogSwitch(obj->base_opamp, CY_CTB_SWITCH_OA0_SW, CY_CTB_SW_OA0_NEG_OUT_MASK | CY_CTB_SW_OA0_OUT_SHORT_1X_10X_MASK, CY_CTB_SWITCH_OPEN);
        Cy_CTB_SetAnalogSwitch(obj->base_opamp, CY_CTB_SWITCH_CTD_SW, CY_CTB_SW_CTD_OUT_CHOLD_MASK | CY_CTB_SW_CTD_CHOLD_OA0_POS_MASK, CY_CTB_SWITCH_OPEN);
        cyhal_analog_ctb_free(obj->base_opamp);
    }
    return result;
}

static cy_rslt_t _cyhal_dac_configure_oa1(cyhal_dac_t *obj, bool init)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    CY_ASSERT(false == obj->owned_by_configurator);

    if (init && (CYHAL_RSC_INVALID != obj->resource_aref_opamp.type))
    {
        /* Configure OA1 for buffered (AREF) voltage reference source */
        result = Cy_CTB_OpampInit(obj->base_opamp, CY_CTB_OPAMP_1, &cyhal_opamp_default_config);
        Cy_CTB_SetAnalogSwitch(obj->base_opamp, CY_CTB_SWITCH_OA1_SW, CY_CTB_SW_OA1_NEG_OUT_MASK | CY_CTB_SW_OA1_POS_AREF_MASK, CY_CTB_SWITCH_CLOSE);
        Cy_CTB_SetAnalogSwitch(obj->base_opamp, CY_CTB_SWITCH_CTD_SW, CY_CTB_SW_CTD_REF_OA1_OUT_MASK, CY_CTB_SWITCH_CLOSE);
        cyhal_analog_ctb_init(obj->base_opamp);
    }
    else
    {
        /* Open switches OA1 if used */
        Cy_CTB_SetAnalogSwitch(obj->base_opamp, CY_CTB_SWITCH_OA1_SW, CY_CTB_SW_OA1_NEG_OUT_MASK | CY_CTB_SW_OA1_POS_AREF_MASK, CY_CTB_SWITCH_OPEN);
        Cy_CTB_SetAnalogSwitch(obj->base_opamp, CY_CTB_SWITCH_CTD_SW, CY_CTB_SW_CTD_REF_OA1_OUT_MASK, CY_CTB_SWITCH_OPEN);
        cyhal_analog_ctb_free(obj->base_opamp);
    }
    return result;
}
#endif

/*******************************************************************************
*       DAC HAL Functions
*******************************************************************************/
cy_rslt_t _cyhal_dac_init_hw(cyhal_dac_t *obj, const cy_stc_ctdac_config_t *config)
{
    obj->base_dac = _cyhal_dac_base[obj->resource_dac.block_num];
    #if (_CYHAL_DRIVER_AVAILABLE_COMP_CTB)
    obj->base_opamp = _cyhal_ctb_base[obj->resource_dac.block_num];
    #endif // _CYHAL_DRIVER_AVAILABLE_COMP_CTB
    cy_rslt_t result = (cy_rslt_t)Cy_CTDAC_Init(obj->base_dac, config);

    /* We deliberately don't initialize the opamp(s), if any, here. In the configurator
     * flow, these are initialized by the application via separate calls to
     * cyhal_opamp_init_cfg */

    if (CY_RSLT_SUCCESS == result)
    {
        _cyhal_analog_init();
        Cy_CTDAC_Enable(obj->base_dac);
    }

    return result;
}

cy_rslt_t cyhal_dac_init(cyhal_dac_t *obj, cyhal_gpio_t pin)
{
    CY_ASSERT(NULL != obj);

    /* Initial values */
    cy_rslt_t result = CY_RSLT_SUCCESS;
    memset(obj, 0, sizeof(cyhal_dac_t));
    obj->resource_dac.type = CYHAL_RSC_INVALID;
    obj->resource_opamp.type = CYHAL_RSC_INVALID;
    obj->pin = CYHAL_NC_PIN_VALUE;
    obj->resource_aref_opamp.type = CYHAL_RSC_INVALID;

    const cyhal_resource_pin_mapping_t *opamp_map = NULL;

    #ifdef CYHAL_PIN_MAP_DRIVE_MODE_DAC_CTDAC_VOUTSW
    const cyhal_resource_pin_mapping_t *dac_map = _CYHAL_UTILS_GET_RESOURCE(pin, cyhal_pin_map_dac_ctdac_voutsw);
    #else
    const cyhal_resource_pin_mapping_t *dac_map = NULL;
    #endif
    if (NULL == dac_map)
    {
        /* Try to get buffered output pin if unbuffered is not specified.  */
        #ifdef CYHAL_PIN_MAP_DRIVE_MODE_OPAMP_OUT_10X
        opamp_map = _CYHAL_UTILS_GET_RESOURCE(pin, cyhal_pin_map_opamp_out_10x);
        #endif
    }

    /* Check if mapping is successful */
    if ((NULL == dac_map) && (NULL == opamp_map))
    {
        result = CYHAL_DAC_RSLT_BAD_ARGUMENT;
    }

#if defined(CY_IP_MXS40PASS_CTB)
    /* Verify if opamp instance 0 is selected, buffered output can be connected to OA0 */
    if ((NULL != opamp_map) && (OPAMP_IDX_OUTPUT != (opamp_map->channel_num)))
    {
        result = CYHAL_DAC_RSLT_BAD_ARGUMENT;
    }
#endif

    cyhal_resource_inst_t opamp_instance;
    cyhal_resource_inst_t dac_instance;

#if defined(CY_IP_MXS40PASS_CTB)
    if (NULL != opamp_map)
    {
        dac_instance.type = CYHAL_RSC_DAC;
        dac_instance.block_num = opamp_map->block_num;
        dac_instance.channel_num = 0;
    }
    else if (CY_RSLT_SUCCESS == result)
    {
#endif
        _CYHAL_UTILS_ASSIGN_RESOURCE(dac_instance, CYHAL_RSC_DAC, dac_map);
#if defined(CY_IP_MXS40PASS_CTB)
    }
#endif

    if (CY_RSLT_SUCCESS == result)
    {
        result = cyhal_hwmgr_reserve(&dac_instance);
    }

    if (CY_RSLT_SUCCESS == result)
    {
        obj->resource_dac = dac_instance;
    }

    if ((NULL != opamp_map) && (CY_RSLT_SUCCESS == result))
    {
        _CYHAL_UTILS_ASSIGN_RESOURCE(opamp_instance, CYHAL_RSC_OPAMP, opamp_map);
        result = cyhal_hwmgr_reserve(&opamp_instance);
        if (CY_RSLT_SUCCESS == result)
        {
            obj->resource_opamp = opamp_instance;
        }
    }

    if (CY_RSLT_SUCCESS == result)
    {
#if defined(CYHAL_PIN_MAP_DRIVE_MODE_DAC_CTDAC_VOUTSW)
        if (NULL != dac_map)
        {
            result = _cyhal_utils_reserve_and_connect(dac_map, CYHAL_PIN_MAP_DRIVE_MODE_DAC_CTDAC_VOUTSW);
        }
#endif
#if defined(CYHAL_PIN_MAP_DRIVE_MODE_OPAMP_OUT_10X)
        if (NULL != opamp_map)
        {
            result = _cyhal_utils_reserve_and_connect(opamp_map, CYHAL_PIN_MAP_DRIVE_MODE_OPAMP_OUT_10X);
        }
#endif

        if (CY_RSLT_SUCCESS == result)
        {
            obj->pin = pin;
        }
    }

    if (CY_RSLT_SUCCESS == result)
    {
        /* Verify is output buffered or not */
        cy_stc_ctdac_config_t config = _CYHAL_DAC_DEFAULT_CONFIG;
        config.outputBuffer = (obj->resource_opamp.type != CYHAL_RSC_INVALID) ? CY_CTDAC_OUTPUT_BUFFERED : CY_CTDAC_OUTPUT_UNBUFFERED;
        result = _cyhal_dac_init_hw(obj, &config);
    }

#if defined(CY_IP_MXS40PASS_CTB)
    if ((CY_RSLT_SUCCESS == result) && (obj->resource_opamp.type != CYHAL_RSC_INVALID))
    {
        /* Init OA0 for buffered output, don't touch OA1 it may be used by opamp or comp */
        result = _cyhal_dac_configure_oa0(obj, true);
    }
#endif

    if(CY_RSLT_SUCCESS != result)
    {
        /* Freeup resources in case of failure */
        cyhal_dac_free(obj);
    }
    return result;
}

 cy_rslt_t cyhal_dac_init_cfg(cyhal_dac_t *obj, const cyhal_dac_configurator_t *cfg)
 {
    memset(obj, 0, sizeof(cyhal_dac_t));
    obj->owned_by_configurator = true;
    obj->resource_dac = *cfg->resource;
    obj->resource_opamp.type = CYHAL_RSC_INVALID;
    obj->resource_aref_opamp.type = CYHAL_RSC_INVALID;
    obj->pin = CYHAL_NC_PIN_VALUE;
    cy_rslt_t result = _cyhal_dac_init_hw(obj, cfg->config);

    if(CY_RSLT_SUCCESS != result)
    {
        cyhal_dac_free(obj);
    }
    return result;
}

void cyhal_dac_free(cyhal_dac_t *obj)
{
    if (NULL != obj->base_dac)
    {
#if defined(CY_IP_MXS40PASS_CTB)
        /* Power off OA1 if used */
        if (_cyhal_dac_is_external_reference(obj))
        {
            Cy_CTB_SetPower(obj->base_opamp, _cyhal_opamp_convert_sel(OPAMP_IDX_REF), (cy_en_ctb_power_t)_cyhal_opamp_convert_power(CYHAL_POWER_LEVEL_OFF), CY_CTB_PUMP_ENABLE);
            if(false == obj->owned_by_configurator)
            {
                (void)_cyhal_dac_configure_oa1(obj, false);
            }
        }

        /* Power off OA0 if used */
        if (_cyhal_dac_is_output_buffered(obj))
        {
            Cy_CTB_SetPower(obj->base_opamp, _cyhal_opamp_convert_sel(OPAMP_IDX_OUTPUT), (cy_en_ctb_power_t)_cyhal_opamp_convert_power(CYHAL_POWER_LEVEL_OFF), CY_CTB_PUMP_ENABLE);
            if(false == obj->owned_by_configurator)
            {
                (void)_cyhal_dac_configure_oa0(obj, false);
            }
        }
#endif

        _cyhal_analog_free();

        Cy_CTDAC_Disable(obj->base_dac);

        if(false == obj->owned_by_configurator)
        {
            cyhal_hwmgr_free(&obj->resource_dac);
            if(CYHAL_RSC_INVALID != obj->resource_opamp.type)
            {
                cyhal_hwmgr_free(&obj->resource_opamp);
            }
            if(CYHAL_RSC_INVALID != obj->resource_aref_opamp.type)
            {
                cyhal_hwmgr_free(&obj->resource_aref_opamp);
            }

            _cyhal_utils_release_if_used(&(obj->pin));
        }

        obj->base_dac = NULL;
        obj->base_opamp = NULL;
    }
}

void cyhal_dac_write(const cyhal_dac_t *obj, uint16_t value)
{
    uint16_t scaled_value = value / _CYHAL_DAC_VALUE_SCALING_FACTOR;
    Cy_CTDAC_SetValue(obj->base_dac, scaled_value);
}

cy_rslt_t cyhal_dac_write_mv(const cyhal_dac_t *obj, uint16_t value)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    uint32_t reference_voltage_mv = 0;

    if (_cyhal_dac_is_external_reference(obj))
    {
        reference_voltage_mv = cyhal_syspm_get_supply_voltage(CYHAL_VOLTAGE_SUPPLY_VDDA);

        if (0 == reference_voltage_mv)
        {
            result = CYHAL_DAC_RSLT_BAD_REF_VOLTAGE;
        }
    }
    else
    {
        /* AREF voltage in millivolts */
        reference_voltage_mv = 1200;
    }

    if (result == CY_RSLT_SUCCESS)
    {
        uint32_t count =  (value << 12) / reference_voltage_mv;
        Cy_CTDAC_SetValue(obj->base_dac, count);
    }

    return result;
}

uint16_t cyhal_dac_read(cyhal_dac_t *obj)
{
    uint16_t value = (uint16_t)obj->base_dac->CTDAC_VAL;
    uint16_t scaled_value = value * _CYHAL_DAC_VALUE_SCALING_FACTOR;
    return scaled_value;
}

cy_rslt_t cyhal_dac_set_reference(cyhal_dac_t *obj, cyhal_dac_ref_t ref)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;

    if(false == obj->owned_by_configurator)
    {
        if (CYHAL_DAC_REF_VDDA == ref)
        {
#if defined(CY_IP_MXS40PASS_CTB) /* If no opamps we just need to check that ref is VDDA, the only supported value */
            /* Unreserve OA1, not needed for VDDA */
            if (obj->resource_aref_opamp.type != CYHAL_RSC_INVALID)
            {
                cyhal_hwmgr_free(&obj->resource_aref_opamp);
                obj->resource_aref_opamp.type = CYHAL_RSC_INVALID;

                /* Freeup OA1. Not needed when VDDA reference is set  */
                result = _cyhal_dac_configure_oa1(obj, false);
            }
        }
        else if (CYHAL_DAC_REF_VREF == ref)
        {
            if (obj->resource_aref_opamp.type == CYHAL_RSC_INVALID)
            {
                /* Reserve OA1 to be able connect to AREF voltage source */
                obj->resource_aref_opamp.type = CYHAL_RSC_OPAMP;
                obj->resource_aref_opamp.block_num = obj->resource_dac.block_num;
                obj->resource_aref_opamp.channel_num = OPAMP_IDX_REF;

                result = cyhal_hwmgr_reserve(&obj->resource_aref_opamp);
                if (CY_RSLT_SUCCESS != result)
                {
                    obj->resource_aref_opamp.type = CYHAL_RSC_INVALID;
                }
                else
                {
                    /* Init OA1 to be able connect to AREF voltage source. OA0 is untouched */
                    result = _cyhal_dac_configure_oa1(obj, true);
                }
            }
#endif
        }
        else
        {
            result = CYHAL_DAC_RSLT_BAD_REF_VOLTAGE;
        }

        if (result == CY_RSLT_SUCCESS)
        {
            Cy_CTDAC_SetRef(obj->base_dac, (cy_en_ctdac_ref_source_t)_cyhal_dac_convert_reference(ref));
        }
    }
    else
    {
        /* We don't own the configuration and routing of OA1, so we can't init/free it and open/close
         * switches to it, as would be required to change the reference */
        result = CYHAL_DAC_RSLT_INVALID_CONFIGURATOR;
    }

    return result;
}

cy_rslt_t cyhal_dac_set_power(cyhal_dac_t *obj, cyhal_power_level_t power)
{
#if defined(CY_IP_MXS40PASS_CTB)
    if (_cyhal_dac_is_output_buffered(obj) || _cyhal_dac_is_external_reference(obj))
    {
        /* Safe convert power level from HAL (cyhal_power_level_t) to PDL (cy_en_ctb_power_t) */
        cy_en_ctb_power_t power_level = (cy_en_ctb_power_t)_cyhal_opamp_convert_power(power);
        if(_cyhal_dac_is_output_buffered(obj))
        {
            Cy_CTB_SetPower(obj->base_opamp, _cyhal_opamp_convert_sel(OPAMP_IDX_OUTPUT), power_level, CY_CTB_PUMP_ENABLE);
        }
        if(_cyhal_dac_is_external_reference(obj))
        {
            Cy_CTB_SetPower(obj->base_opamp, _cyhal_opamp_convert_sel(OPAMP_IDX_REF), power_level, CY_CTB_PUMP_ENABLE);
        }

        bool full_ctb_owned = _cyhal_dac_is_output_buffered(obj) || _cyhal_dac_is_external_reference(obj);
        if(full_ctb_owned)
        {
            if (CYHAL_POWER_LEVEL_OFF == power)
            {
                Cy_CTB_Disable(obj->base_opamp);
            }
            else
            {
                Cy_CTB_Enable(obj->base_opamp);
            }
        }
    }
#endif
    if (CYHAL_POWER_LEVEL_OFF == power)
    {
        Cy_CTDAC_Disable(obj->base_dac);
    }
    else
    {
        Cy_CTDAC_Enable(obj->base_dac);
    }
    return CY_RSLT_SUCCESS;
}

#if defined(__cplusplus)
}
#endif

#endif /* CYHAL_DRIVER_AVAILABLE_DAC */
