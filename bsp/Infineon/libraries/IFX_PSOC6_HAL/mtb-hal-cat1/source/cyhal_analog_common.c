/***************************************************************************//**
* \file cyhal_analog_common.c
*
* \brief
* Provides common functionality that needs to be shared among all drivers that
* interact with the Programmable Analog Subsystem.
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

#include "cy_pdl.h"
#include "cyhal_hw_types.h"
#include "cyhal_hwmgr.h"
#include "cyhal_pin_package.h"
#include "cyhal_gpio.h"
#include "cyhal_system_impl.h"
#include "cyhal_analog_common.h"

#if (_CYHAL_DRIVER_AVAILABLE_PASS)

#if defined(__cplusplus)
extern "C"
{
#endif

#if defined(CY_IP_MXS40PASS_INSTANCES)
static uint16_t cyhal_analog_ref_count = 0;
#endif

#if (_CYHAL_DRIVER_AVAILABLE_COMP_CTB)
static uint16_t cyhal_analog_ctb_ref_count = 0;

CTBM_Type *const _cyhal_ctb_base[] =
{
/* All current CAT1/CAT2 devices have only one CTB block per PASS */
#if ((PASS_NR_CTBS == 1) || (PASS0_NR_CTBS == 1))
    CTBM0,
#else
    #error "Unhandled CTB instance count"
#endif
#if (PASS1_NR_CTBS == 1)
    CTBM1,
#elif (PASS1_NR_CTBS > 1)
    #error "Unhandled CTB instance count"
#endif
};


#endif

void _cyhal_analog_init(void)
{
#if defined(CY_IP_MXS40PASS_INSTANCES)
    uint32_t saved_intr = cyhal_system_critical_section_enter();
    if(cyhal_analog_ref_count == 0)
    {
        Cy_SysAnalog_Init(&Cy_SysAnalog_Fast_Local);
        Cy_SysAnalog_Enable();
    }

    ++cyhal_analog_ref_count;
    cyhal_system_critical_section_exit(saved_intr);
#endif
}

void _cyhal_analog_free(void)
{
#if defined(CY_IP_MXS40PASS_INSTANCES)
    uint32_t saved_intr = cyhal_system_critical_section_enter();
    CY_ASSERT(cyhal_analog_ref_count > 0);
    --cyhal_analog_ref_count;
    if(cyhal_analog_ref_count == 0)
    {
        Cy_SysAnalog_Disable();
        Cy_SysAnalog_DeInit();
    }
    cyhal_system_critical_section_exit(saved_intr);
#endif
}

#if (_CYHAL_DRIVER_AVAILABLE_COMP_CTB)
void cyhal_analog_ctb_init(CTBM_Type *base)
{
    uint32_t saved_intr = cyhal_system_critical_section_enter();
    _cyhal_analog_init();
    if(cyhal_analog_ctb_ref_count == 0)
    {
        Cy_CTB_Enable(base);
    }
    ++cyhal_analog_ctb_ref_count;
    cyhal_system_critical_section_exit(saved_intr);
}

void cyhal_analog_ctb_free(CTBM_Type *base)
{
    uint32_t saved_intr = cyhal_system_critical_section_enter();
    CY_ASSERT(cyhal_analog_ctb_ref_count > 0);
    --cyhal_analog_ctb_ref_count;
    if(cyhal_analog_ctb_ref_count == 0)
    {
        Cy_CTB_Disable(base);
        Cy_CTB_DeInit(base, true);
    }
    _cyhal_analog_free();
    cyhal_system_critical_section_exit(saved_intr);
}

uint32_t _cyhal_opamp_pin_to_mask(uint8_t opamp_num, cyhal_gpio_t vin_p, cyhal_gpio_t vin_m, cyhal_gpio_t vout)
{
    /* Follower mode require close switch from vin_p to OAP+, from OAP- to OPAMP_OUT, from OPAMP_OUT to vout */
    /* Non follower mode require close switch from vin_p to OAP+, from vin_m to OAP- */

    const cyhal_resource_pin_mapping_t *vin_p0_map = _CYHAL_UTILS_GET_RESOURCE(vin_p, cyhal_pin_map_opamp_vin_p0);
    // If we have a valid vplus pin, it must be in either vin_p0 or vin_p1
#ifdef CYHAL_PIN_MAP_DRIVE_MODE_OPAMP_VIN_P1
    CY_ASSERT((NULL != vin_p0_map) || (NULL != _CYHAL_UTILS_GET_RESOURCE(vin_p, cyhal_pin_map_opamp_vin_p1)));
#else
    CY_ASSERT(NULL != vin_p0_map);
#endif
    uint32_t switch_mask = (0u == opamp_num)
                            ? ((NULL != vin_p0_map) ? CTBM_OA0_SW_OA0P_A20_Msk /* OA0_POS_PIN0 */ : CTBM_OA0_SW_OA0P_A30_Msk /* OA0_POS_PIN6 */)
                            : ((NULL != vin_p0_map) ? CTBM_OA1_SW_OA1P_A13_Msk /* OA1_POS_PIN5 */ : CTBM_OA1_SW_OA1P_A43_Msk /* OA1_POS_PIN7 */);

    if (NC == vin_m)
    {
        if(NC != vout)
        {
            // Set switches for internal feedback
            switch_mask |= (0u == opamp_num) ? CTBM_OA0_SW_OA0O_D81_Msk /* OA0_OUT_SHORT_1X_10X */ : CTBM_OA1_SW_OA1O_D82_Msk /* OA1_OUT_SHORT_1X_10X */;
            switch_mask |= (0u == opamp_num) ? CTBM_OA0_SW_OA0M_A81_Msk : CTBM_OA1_SW_OA1M_A82_Msk;
        }
    }
    else
    {
        switch_mask |= (0u == opamp_num) ? CTBM_OA0_SW_OA0M_A11_Msk /* OA0_NEG_PIN1 */ :  CTBM_OA1_SW_OA1M_A22_Msk /* OA1_NEG_PIN4 */;
    }

    return switch_mask;
}

cy_rslt_t _cyhal_opamp_init_common(cyhal_resource_inst_t* rsc, cy_rslt_t bad_arg_error, cyhal_gpio_t vin_p, cyhal_gpio_t vin_m, cyhal_gpio_t vout, cyhal_gpio_t comp_out)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    rsc->type = CYHAL_RSC_INVALID;
    cyhal_gpio_t reserved_vin_p = NC;
    cyhal_gpio_t reserved_vin_m = NC;
    cyhal_gpio_t reserved_vout = NC;
    cyhal_gpio_t reserved_comp_out = NC;

    const cyhal_resource_pin_mapping_t *vin_p_map = _CYHAL_UTILS_GET_RESOURCE(vin_p, cyhal_pin_map_opamp_vin_p0);
#ifdef CYHAL_PIN_MAP_DRIVE_MODE_OPAMP_VIN_P1
    if(NULL == vin_p_map)
    {
        vin_p_map = _CYHAL_UTILS_GET_RESOURCE(vin_p, cyhal_pin_map_opamp_vin_p1);
    }
#endif

    // In at least one use case, everything except for vin_p is optional. Leave it to the calling driver to
    // validate which combinations are allowed in its particular use case.
    const cyhal_resource_pin_mapping_t *vin_m_map = (NC != vin_m)    ? _CYHAL_UTILS_GET_RESOURCE(vin_m, cyhal_pin_map_opamp_vin_m)      : NULL;
    const cyhal_resource_pin_mapping_t *vout_map  = (NC != vout)     ? _CYHAL_UTILS_GET_RESOURCE(vout, cyhal_pin_map_opamp_out_10x)     : NULL;
    const cyhal_resource_pin_mapping_t *comp_map  = (NC != comp_out) ? _CYHAL_UTILS_GET_RESOURCE(comp_out, cyhal_pin_map_opamp_dsi_ctb_cmp) : NULL;


    if((NULL == vin_p_map) || ((NC != vin_m) && (NULL == vin_m_map)) || ((NC != vout) && (NULL == vout_map)) || ((NC != comp_out) && (NULL == comp_map)))
    {
        result = bad_arg_error;
    }

    if((CY_RSLT_SUCCESS == result) && (NULL != vin_p_map) &&
        ((NULL != vin_m_map && (false == _cyhal_utils_map_resources_equal(vin_p_map, vin_m_map)))
        || (NULL != vout_map && (false == _cyhal_utils_map_resources_equal(vin_p_map, vout_map)))
        || (NULL != comp_map && (false == _cyhal_utils_map_resources_equal(vin_p_map, comp_map)))))
    {
        result = bad_arg_error;
    }

    if (NULL != vin_p_map)
    {
        cyhal_resource_inst_t rsc2 = { CYHAL_RSC_OPAMP, vin_p_map->block_num, vin_p_map->channel_num };
        if(CY_RSLT_SUCCESS == result)
        {
            result = cyhal_hwmgr_reserve(&rsc2);
        }

        if(CY_RSLT_SUCCESS == result)
        {
            *rsc = rsc2;

            /* If we fail to reserve any of the pins, clear it out so that free doesn't try to release it */
            result = _cyhal_utils_reserve_and_connect(vin_p_map, CYHAL_PIN_MAP_DRIVE_MODE_OPAMP_VIN_P0);
        }

        if(CY_RSLT_SUCCESS == result)
        {
            reserved_vin_p = vin_p;
            if(NC != vin_m)
            {
                result = _cyhal_utils_reserve_and_connect(vin_m_map, CYHAL_PIN_MAP_DRIVE_MODE_OPAMP_VIN_M);
            }
        }

        if(CY_RSLT_SUCCESS == result)
        {
            reserved_vin_m = vin_m;
            if(NC != vout)
            {
                result = _cyhal_utils_reserve_and_connect(vout_map, CYHAL_PIN_MAP_DRIVE_MODE_OPAMP_OUT_10X);
            }
        }

        if(CY_RSLT_SUCCESS == result)
        {
            reserved_vout = vout;
            if(NC != comp_out)
            {
                result = _cyhal_utils_reserve_and_connect(comp_map, CYHAL_PIN_MAP_DRIVE_MODE_OPAMP_DSI_CTB_CMP);
            }
        }

        if(CY_RSLT_SUCCESS == result)
        {
            reserved_comp_out = comp_out;
        }

        if(CY_RSLT_SUCCESS != result)
        {
            _cyhal_utils_release_if_used(&reserved_vin_p);
            _cyhal_utils_release_if_used(&reserved_vin_m);
            _cyhal_utils_release_if_used(&reserved_vout);
            _cyhal_utils_release_if_used(&reserved_comp_out);

            if(CYHAL_RSC_INVALID != rsc->type)
            {
                cyhal_hwmgr_free(rsc);
            }
        }
    }

    return result;
}

uint32_t _cyhal_opamp_convert_power(cyhal_power_level_t hal_power)
{
    switch(hal_power)
    {
        case CYHAL_POWER_LEVEL_OFF:
            return (uint32_t)CY_CTB_POWER_OFF;
        case CYHAL_POWER_LEVEL_LOW:
            return (uint32_t)CY_CTB_POWER_LOW;
        case CYHAL_POWER_LEVEL_MEDIUM:
            return (uint32_t)CY_CTB_POWER_MEDIUM;
        case CYHAL_POWER_LEVEL_HIGH:
            return (uint32_t)CY_CTB_POWER_HIGH;
        case CYHAL_POWER_LEVEL_DEFAULT:
            return (uint32_t)CY_CTB_POWER_MEDIUM;
        default:
            CY_ASSERT(false);
            return CYHAL_POWER_LEVEL_OFF;
    }
}

#endif // _CYHAL_DRIVER_AVAILABLE_COMP_CTB

#if defined(__cplusplus)
}
#endif

#endif /* (_CYHAL_DRIVER_AVAILABLE_PASS) */
