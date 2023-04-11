/***************************************************************************//**
* \file cyhal_utils_impl.c
*
* \brief
* Provides utility functions for working with the CAT1/CAT2 HAL implementation.
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
#include <stdarg.h>
#include "cyhal_utils.h"
#include "cyhal_utils_impl.h"
#include "cyhal_hwmgr.h"
#include "cyhal_interconnect.h"
#include "cyhal_clock.h"

#if defined(__cplusplus)
extern "C"
{
#endif

#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
#define _CYHAL_MXSPERI_PCLK_DIV_CNT(gr) \
    case CYHAL_CLOCK_BLOCK_PERIPHERAL##gr##_8BIT: return PERI_PERI_PCLK_PCLK_GROUP_NR##gr##_GR_DIV_8_VECT; \
    case CYHAL_CLOCK_BLOCK_PERIPHERAL##gr##_16BIT: return PERI_PERI_PCLK_PCLK_GROUP_NR##gr##_GR_DIV_16_VECT; \
    case CYHAL_CLOCK_BLOCK_PERIPHERAL##gr##_16_5BIT: return PERI_PERI_PCLK_PCLK_GROUP_NR##gr##_GR_DIV_16_5_VECT; \
    case CYHAL_CLOCK_BLOCK_PERIPHERAL##gr##_24_5BIT: return PERI_PERI_PCLK_PCLK_GROUP_NR##gr##_GR_DIV_24_5_VECT;
#elif defined(COMPONENT_CAT1D)
#define _CYHAL_MXSPERI_PCLK_DIV_CNT(instance, gr) \
    case CYHAL_CLOCK_BLOCK##instance##_PERIPHERAL##gr##_8BIT: return PERI##instance##_PERI_PCLK_PCLK_GROUP_NR##gr##_GR_DIV_8_VECT; \
    case CYHAL_CLOCK_BLOCK##instance##_PERIPHERAL##gr##_16BIT: return PERI##instance##_PERI_PCLK_PCLK_GROUP_NR##gr##_GR_DIV_16_VECT; \
    case CYHAL_CLOCK_BLOCK##instance##_PERIPHERAL##gr##_16_5BIT: return PERI##instance##_PERI_PCLK_PCLK_GROUP_NR##gr##_GR_DIV_16_5_VECT; \
    case CYHAL_CLOCK_BLOCK##instance##_PERIPHERAL##gr##_24_5BIT: return PERI##instance##_PERI_PCLK_PCLK_GROUP_NR##gr##_GR_DIV_24_5_VECT;
#endif

cy_rslt_t _cyhal_utils_reserve_and_connect(const cyhal_resource_pin_mapping_t *mapping, uint8_t drive_mode)
{
    cyhal_resource_inst_t pinRsc = _cyhal_utils_get_gpio_resource(mapping->pin);
    cy_rslt_t status = cyhal_hwmgr_reserve(&pinRsc);
    if (CY_RSLT_SUCCESS == status)
    {
        status = cyhal_connect_pin(mapping, drive_mode);
        if (CY_RSLT_SUCCESS != status)
        {
            cyhal_hwmgr_free(&pinRsc);
        }
    }
    return status;
}

void _cyhal_utils_disconnect_and_free(cyhal_gpio_t pin)
{
    cy_rslt_t rslt = cyhal_disconnect_pin(pin);
    CY_UNUSED_PARAMETER(rslt); /* CY_ASSERT only processes in DEBUG, ignores for others */
    CY_ASSERT(CY_RSLT_SUCCESS == rslt);
    cyhal_resource_inst_t rsc = _cyhal_utils_get_gpio_resource(pin);
    cyhal_hwmgr_free(&rsc);
}

cy_en_syspm_callback_mode_t _cyhal_utils_convert_haltopdl_pm_mode(cyhal_syspm_callback_mode_t mode)
{
    switch (mode)
    {
        case CYHAL_SYSPM_CHECK_READY:
            return CY_SYSPM_CHECK_READY;
        case CYHAL_SYSPM_CHECK_FAIL:
            return CY_SYSPM_CHECK_FAIL;
        case CYHAL_SYSPM_BEFORE_TRANSITION:
            return CY_SYSPM_BEFORE_TRANSITION;
        case CYHAL_SYSPM_AFTER_TRANSITION:
            return CY_SYSPM_AFTER_TRANSITION;
#if defined(COMPONENT_CAT1B)
        case CYHAL_SYSPM_AFTER_DS_WFI_TRANSITION:
            return CY_SYSPM_AFTER_DS_WFI_TRANSITION;
#endif
        default:
            /* Should not get here */
            CY_ASSERT(false);
            return CY_SYSPM_CHECK_READY;
    }
}

cyhal_syspm_callback_mode_t _cyhal_utils_convert_pdltohal_pm_mode(cy_en_syspm_callback_mode_t mode)
{
    switch (mode)
    {
        case CY_SYSPM_CHECK_READY:
            return CYHAL_SYSPM_CHECK_READY;
        case CY_SYSPM_CHECK_FAIL:
            return CYHAL_SYSPM_CHECK_FAIL;
        case CY_SYSPM_BEFORE_TRANSITION:
            return CYHAL_SYSPM_BEFORE_TRANSITION;
        case CY_SYSPM_AFTER_TRANSITION:
            return CYHAL_SYSPM_AFTER_TRANSITION;
#if defined(COMPONENT_CAT1B)
        case CY_SYSPM_AFTER_DS_WFI_TRANSITION:
            return CYHAL_SYSPM_AFTER_DS_WFI_TRANSITION;
#endif
        default:
            /* Should not get here */
            CY_ASSERT(false);
            return CYHAL_SYSPM_CHECK_READY;
    }
}

int32_t _cyhal_utils_calculate_tolerance(cyhal_clock_tolerance_unit_t type, uint32_t desired_hz, uint32_t actual_hz)
{
    switch (type)
    {
        case CYHAL_TOLERANCE_HZ:
            return (int32_t)(desired_hz - actual_hz);
        case CYHAL_TOLERANCE_PPM:
            return (int32_t)(((int64_t)(desired_hz - actual_hz)) * 1000000) / ((int32_t)desired_hz);
        case CYHAL_TOLERANCE_PERCENT:
            return (int32_t)((((int64_t)desired_hz - actual_hz) * 100) / desired_hz);
        default:
            CY_ASSERT(false);
            return 0;
    }
}

static inline cy_rslt_t _cyhal_utils_allocate_peri(cyhal_clock_t *clock, uint8_t peri_group, cyhal_clock_block_t div, bool accept_larger)
{
    static const cyhal_clock_block_t PERI_DIVIDERS[] =
    {
        CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT,
        CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT,
        CYHAL_CLOCK_BLOCK_PERIPHERAL_16_5BIT,
        CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT
    };

    cy_rslt_t result = CYHAL_HWMGR_RSLT_ERR_NONE_FREE;
    bool found_minimum = false;

#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
    bool dividers_exist = false;
#endif
    for(size_t i = 0; i < sizeof(PERI_DIVIDERS) / sizeof(PERI_DIVIDERS[0]); ++i)
    {
        if(PERI_DIVIDERS[i] == div)
        {
            found_minimum = true;
        }

        if(found_minimum)
        {
#if defined(COMPONENT_CAT1A)
            CY_UNUSED_PARAMETER(peri_group);
            result = _cyhal_clock_allocate_peri(clock, PERI_DIVIDERS[i]);
#elif defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
#if !defined(COMPONENT_CAT1D)
            cyhal_clock_block_t adjusted_div = (cyhal_clock_block_t)_CYHAL_PERIPHERAL_GROUP_ADJUST(peri_group, PERI_DIVIDERS[i]);
#else /* !defined(COMPONENT_CAT1D) */
            uint8_t instance = _CYHAL_UTILS_UNPACK_INSTANCE(peri_group);
            uint8_t group = _CYHAL_UTILS_UNPACK_GROUP(peri_group);
            cyhal_clock_block_t adjusted_div = (cyhal_clock_block_t)_CYHAL_PERIPHERAL_GROUP_ADJUST(instance, group, PERI_DIVIDERS[i]);
#endif /* !defined(COMPONENT_CAT1D) or other */
            dividers_exist |= (_cyhal_utils_get_clock_count(adjusted_div) > 0);
            result = _cyhal_clock_allocate_peri(clock, adjusted_div);
#elif defined(COMPONENT_CAT2)
            CY_UNUSED_PARAMETER(peri_group);
            result = cyhal_clock_allocate(clock, PERI_DIVIDERS[i]);
#endif

            if(CY_RSLT_SUCCESS == result || !accept_larger)
            {
                break;
            }
        }
    }

#if defined(COMPONENT_CAT1B)
    // If no dividers exist, try to reserve the hfclk that drives the peri group
    if(CY_RSLT_SUCCESS != result && false == dividers_exist)
    {
        uint8_t hfclk_idx = _cyhal_utils_get_hfclk_for_peri_group(peri_group);
        result = cyhal_clock_reserve(clock, &CYHAL_CLOCK_HF[hfclk_idx]);
    }
#endif
    return result;
}

#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
uint8_t _cyhal_utils_get_hfclk_for_peri_group(uint8_t peri_group)
{
    switch (peri_group)
    {
        /* Peripheral groups are device specific. */
#if defined(CY_DEVICE_CYW20829)
        case 0:
        case 2:
            return 0;
        case 1:
        case 3:
        case 6:
            return 1;
        case 4:
            return 2;
        case 5:
            return 3;
#elif defined(CY_DEVICE_TVIIBH8M) || defined(CY_DEVICE_TVIIBH4M)
        case 0:
            return 0;
        case 1:
            return 2;
#else
#warning "Unsupported device"
#endif /* defined(CY_DEVICE_CYW20829) */
        default:
            CY_ASSERT(false); /* Use APIs provided by the clock driver */
            break;
    }
    return 0;
}
#endif /* defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) */

#if defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
uint8_t _cyhal_utils_get_peri_group(const cyhal_resource_inst_t *clocked_item)
{
    switch (clocked_item->type)
    {
        /* Peripheral groups are device specific. */
#if defined(CY_DEVICE_CYW20829)
        case CYHAL_RSC_CAN:
        case CYHAL_RSC_LIN:
        case CYHAL_RSC_SCB:
        case CYHAL_RSC_TCPWM:
            return 1;
        case CYHAL_RSC_CRYPTO:
            return 2;
        case CYHAL_RSC_I2S:
        case CYHAL_RSC_TDM:
        case CYHAL_RSC_PDM:
            return 3;
        case CYHAL_RSC_BLESS:
            return 4;
        case CYHAL_RSC_ADCMIC:
            return 5;
        case CYHAL_RSC_SMIF:
            return 6;
#elif defined(CY_DEVICE_TVIIBH8M) || defined(CY_DEVICE_TVIIBH4M)
        #if defined(CY_DEVICE_TVIIBH8M)
        case CYHAL_RSC_TCPWM:
            // 4 is the same as _CYHAL_TCPWM_MAX_GRPS_PER_IP_BLOCK
            if (clocked_item->block_num < 4)
            {
                return 0;
            }
            return 1;
        #else
        case CYHAL_RSC_TCPWM:
        #endif
        case CYHAL_RSC_ADC:
        case CYHAL_RSC_SCB:
        case CYHAL_RSC_CAN:
        case CYHAL_RSC_LIN:
            return 1;
#else
#warning "Unsupported device"
#endif
        default:
            CY_ASSERT(false); /* Use APIs provided by the clock driver */
            break;
    }
    return 0;
}
#endif

uint32_t _cyhal_utils_get_clock_count(cyhal_clock_block_t block)
{
    //NOTE: This could potentially reuse the cyhal_hwmgr.c cyhal_block_offsets_clock array
    switch (block)
    {
        #if defined(COMPONENT_CAT1)
        #if defined(COMPONENT_CAT1A)
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT:
            return PERI_DIV_8_NR;
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT:
            return PERI_DIV_16_NR;
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16_5BIT:
            return PERI_DIV_16_5_NR;
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT:
            return PERI_DIV_24_5_NR;
        case CYHAL_CLOCK_BLOCK_PLL:
            return SRSS_NUM_PLL;
        #elif defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
        #if (PERI_PERI_PCLK_PCLK_GROUP_NR > 0)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(0);
        #endif
        #if (PERI_PERI_PCLK_PCLK_GROUP_NR > 1)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(1);
        #endif
        #if (PERI_PERI_PCLK_PCLK_GROUP_NR > 2)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(2);
        #endif
        #if (PERI_PERI_PCLK_PCLK_GROUP_NR > 3)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(3);
        #endif
        #if (PERI_PERI_PCLK_PCLK_GROUP_NR > 4)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(4);
        #endif
        #if (PERI_PERI_PCLK_PCLK_GROUP_NR > 5)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(5);
        #endif
        #if (PERI_PERI_PCLK_PCLK_GROUP_NR > 6)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(6);
        #endif
        #if (PERI_PERI_PCLK_PCLK_GROUP_NR > 7)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(7);
        #endif
        #if (PERI_PERI_PCLK_PCLK_GROUP_NR > 8)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(8);
        #endif
        #if (PERI_PERI_PCLK_PCLK_GROUP_NR > 9)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(9);
        #endif
        #if (PERI_PERI_PCLK_PCLK_GROUP_NR > 10)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(10);
        #endif
        #if (PERI_PERI_PCLK_PCLK_GROUP_NR > 11)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(11);
        #endif
        #if (PERI_PERI_PCLK_PCLK_GROUP_NR > 12)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(12);
        #endif
        #if (PERI_PERI_PCLK_PCLK_GROUP_NR > 13)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(13);
        #endif
        #if (PERI_PERI_PCLK_PCLK_GROUP_NR > 14)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(14);
        #endif
        #if (PERI_PERI_PCLK_PCLK_GROUP_NR > 15)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(15);
        #endif
        case CYHAL_CLOCK_BLOCK_PERI:
            return PERI_PCLK_GROUP_NR;
        case CYHAL_CLOCK_BLOCK_PLL200:
            return SRSS_NUM_PLL200M;
        case CYHAL_CLOCK_BLOCK_PLL400:
            return SRSS_NUM_PLL400M;
        #elif defined (COMPOANENT_CAT1D)
        #if (PERI0_PERI_PCLK_PCLK_GROUP_NR > 0)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(0, 0);
        #endif
        #if (PERI0_PERI_PCLK_PCLK_GROUP_NR > 1)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(0, 1);
        #endif
        #if (PERI0_PERI_PCLK_PCLK_GROUP_NR > 2)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(0, 2);
        #endif
        #if (PERI0_PERI_PCLK_PCLK_GROUP_NR > 3)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(0, 3);
        #endif
        #if (PERI0_PERI_PCLK_PCLK_GROUP_NR > 4)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(0, 4);
        #endif
        #if (PERI0_PERI_PCLK_PCLK_GROUP_NR > 5)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(0, 5);
        #endif
        #if (PERI0_PERI_PCLK_PCLK_GROUP_NR > 6)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(0, 6);
        #endif
        #if (PERI0_PERI_PCLK_PCLK_GROUP_NR > 7)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(0, 7);
        #endif
        #if (PERI0_PERI_PCLK_PCLK_GROUP_NR > 8)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(0, 8);
        #endif
        #if (PERI0_PERI_PCLK_PCLK_GROUP_NR > 9)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(0, 9);
        #endif
        #if (PERI0_PERI_PCLK_PCLK_GROUP_NR > 10)
        #warning "Unhandled number of PCLK for PERI0"
        #endif
        #if (PERI1_PERI_PCLK_PCLK_GROUP_NR > 0)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(1, 0);
        #endif
        #if (PERI1_PERI_PCLK_PCLK_GROUP_NR > 1)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(1, 1);
        #endif
        #if (PERI1_PERI_PCLK_PCLK_GROUP_NR > 2)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(1, 2);
        #endif
        #if (PERI1_PERI_PCLK_PCLK_GROUP_NR > 3)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(1, 3);
        #endif
        #if (PERI1_PERI_PCLK_PCLK_GROUP_NR > 4)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(1, 4);
        #endif
        #if (PERI1_PERI_PCLK_PCLK_GROUP_NR > 5)
        _CYHAL_MXSPERI_PCLK_DIV_CNT(1, 5);
        #endif
        #if (PERI_PERI_PCLK_PCLK_GROUP_NR > 6)
        #warning "Unhandled number of PCLK for PERI1"
        #endif
        case CYHAL_CLOCK_BLOCK_PERI:
            return PERI_PCLK_GROUP_NR;
        case CYHAL_CLOCK_BLOCK_DPLL_LP:
            return SRSS_NUM_DPLL_LP;
        case CYHAL_CLOCK_BLOCK_DPLL_HP:
            return SRSS_NUM_DPLL_HP;
        #endif /* defined(COMPONENT_CAT1B) */

        case CYHAL_CLOCK_BLOCK_PATHMUX:
            return SRSS_NUM_CLKPATH;
        case CYHAL_CLOCK_BLOCK_HF:
            return SRSS_NUM_HFROOT;
        #elif defined(COMPONENT_CAT2) /* defined(COMPONENT_CAT1) */
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT:
            return PERI_PCLK_DIV_8_NR;
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT:
            return PERI_PCLK_DIV_16_NR;
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_16_5BIT:
            return PERI_PCLK_DIV_16_5_NR;
        case CYHAL_CLOCK_BLOCK_PERIPHERAL_24_5BIT:
            return PERI_PCLK_DIV_24_5_NR;
        #endif /* defined(COMPONENT_CAT2) */
        default:
            return 1;
    }
}

#if defined(COMPONENT_CAT1A)
cy_rslt_t _cyhal_utils_allocate_clock(cyhal_clock_t *clock, const cyhal_resource_inst_t *clocked_item, cyhal_clock_block_t div, bool accept_larger)
{
    CY_ASSERT(NULL != clocked_item);

    cyhal_clock_t clock_rsc;
    switch (clocked_item->type)
    {
        /* High frequency clock assignments are device specific. */
#if defined(CY_DEVICE_PSOC6ABLE2) || defined(CY_DEVICE_PSOC6A2M)
        case CYHAL_RSC_I2S:
        case CYHAL_RSC_PDM:
            clock_rsc = CYHAL_CLOCK_HF[1];
            break;
#endif
#if defined(CY_DEVICE_PSOC6ABLE2) || defined(CY_DEVICE_PSOC6A2M) || defined(CY_DEVICE_PSOC6A512K) || defined(CY_DEVICE_PSOC6A256K)
        case CYHAL_RSC_SMIF:
            clock_rsc = CYHAL_CLOCK_HF[2];
            break;
        case CYHAL_RSC_USB:
            clock_rsc = CYHAL_CLOCK_HF[3];
            break;
#endif
#if defined(CY_DEVICE_PSOC6A2M)
        case CYHAL_RSC_SDHC:
            clock_rsc = (clocked_item->block_num == 0)
                ? CYHAL_CLOCK_HF[4]
                : CYHAL_CLOCK_HF[2];
            break;
#elif defined(CY_DEVICE_PSOC6A512K)
        case CYHAL_RSC_SDHC:
            clock_rsc = CYHAL_CLOCK_HF[4];
            break;
#endif
        case CYHAL_RSC_CLOCK:
            CY_ASSERT(false); /* Use APIs provided by the clock driver */
            return CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED;
        default:
            return _cyhal_utils_allocate_peri(clock, 0, div, accept_larger);
    }
    return cyhal_clock_reserve(clock, &clock_rsc);
}
#elif defined(COMPONENT_CAT1C)
cy_rslt_t _cyhal_utils_allocate_clock(cyhal_clock_t *clock, const cyhal_resource_inst_t *clocked_item, cyhal_clock_block_t div, bool accept_larger)
{
    CY_ASSERT(NULL != clocked_item);

    cyhal_clock_t clock_rsc;
    uint8_t peri_group;
    switch (clocked_item->type)
    {
        /* High frequency clock assignments are device specific. */
#if defined(CY_DEVICE_TVIIBH8M) || defined(CY_DEVICE_TVIIBH4M)
        case CYHAL_RSC_I2S:
            clock_rsc = CYHAL_CLOCK_HF[5];
            break;
        case CYHAL_RSC_SMIF:
        case CYHAL_RSC_SDHC:
            clock_rsc = CYHAL_CLOCK_HF[6];
            break;
#endif
        case CYHAL_RSC_CLOCK:
            CY_ASSERT(false); /* Use APIs provided by the clock driver */
            return CYHAL_CLOCK_RSLT_ERR_NOT_SUPPORTED;
        default:
            peri_group = _cyhal_utils_get_peri_group(clocked_item);
            return _cyhal_utils_allocate_peri(clock, peri_group, div, accept_larger);
    }
    return cyhal_clock_reserve(clock, &clock_rsc);
}

#elif defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1D)
cy_rslt_t _cyhal_utils_allocate_clock(cyhal_clock_t *clock, const cyhal_resource_inst_t *clocked_item, cyhal_clock_block_t div, bool accept_larger)
{
    CY_ASSERT(NULL != clocked_item);
    uint8_t peri_group = _cyhal_utils_get_peri_group(clocked_item);
    return _cyhal_utils_allocate_peri(clock, peri_group, div, accept_larger);
}
#elif defined(COMPONENT_CAT2)
cy_rslt_t _cyhal_utils_allocate_clock(cyhal_clock_t *clock, const cyhal_resource_inst_t *clocked_item, cyhal_clock_block_t div, bool accept_larger)
{
    CY_ASSERT(NULL != clocked_item);
    CY_UNUSED_PARAMETER(clocked_item);
    return _cyhal_utils_allocate_peri(clock, 0, div, accept_larger);
}
#endif

cy_rslt_t _cyhal_utils_set_clock_frequency(cyhal_clock_t* clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
    if(clock->block == CYHAL_CLOCK_BLOCK_HF)
    {
        uint32_t divider;
        cy_en_clkhf_in_sources_t source = Cy_SysClk_ClkHfGetSource(clock->channel);
        uint32_t source_hz = Cy_SysClk_ClkPathGetFrequency((uint32_t)source);
        if (CY_RSLT_SUCCESS == _cyhal_utils_find_hf_clk_div(source_hz, hz, tolerance, false, &divider))
        {
            return cyhal_clock_set_divider(clock, divider);
        }
        return CYHAL_CLOCK_RSLT_ERR_FREQ;
    }
    else
    {
#endif
        // Defer to the clock driver
        return cyhal_clock_set_frequency(clock, hz, tolerance);
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
    }
#endif
}

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
cy_rslt_t _cyhal_utils_find_hf_clk_div(uint32_t hz_src, uint32_t desired_hz, const cyhal_clock_tolerance_t *tolerance,
                        bool only_below_desired, uint32_t *div)
{
    const uint8_t HFCLK_DIVIDERS[] = { 1, 2, 4, 8};
    cy_rslt_t retval = CYHAL_CLOCK_RSLT_ERR_FREQ;
    uint32_t tolerance_check_value = (NULL != tolerance) ? tolerance->value : 0xFFFFFFFFU;
    cyhal_clock_tolerance_unit_t tolerance_type = (NULL != tolerance) ? tolerance->type : CYHAL_TOLERANCE_HZ;

    for(uint8_t i = 0; i < sizeof(HFCLK_DIVIDERS) / sizeof(HFCLK_DIVIDERS[0]); ++i)
    {
        const uint32_t divider = HFCLK_DIVIDERS[i];
        uint32_t actual_freq = hz_src / divider;
        if ((actual_freq > desired_hz) && only_below_desired)
            continue;
        uint32_t achieved_tolerance = abs(_cyhal_utils_calculate_tolerance(tolerance_type, desired_hz, actual_freq));
        if (achieved_tolerance < tolerance_check_value)
        {
            *div = divider;
            retval = CY_RSLT_SUCCESS;
            if ((NULL != tolerance) || (achieved_tolerance == 0))
                break;
            tolerance_check_value = achieved_tolerance;
        }
        else if (only_below_desired)
        {
            /* We are going from smallest divider, to highest. If we've not achieved better tolerance in
            *   this iteration, we will no achieve it in futher for sure. */
            break;
        }
    }
    return retval;
}

cy_rslt_t _cyhal_utils_find_hf_source_n_divider(cyhal_clock_t *clock, uint32_t hz,
        const cyhal_clock_tolerance_t *tolerance, _cyhal_utils_clk_div_func_t div_find_func, cyhal_clock_t *hf_source,
        uint32_t *div)
{
    CY_ASSERT(NULL != clock);
    CY_ASSERT(hz != 0);

    uint32_t count;
    const cyhal_resource_inst_t ** sources;
    cy_rslt_t retval = cyhal_clock_get_sources(clock, &sources, &count);
    if (CY_RSLT_SUCCESS != retval)
        return retval;

    uint32_t best_tolerance_hz = 0xFFFFFFFFU;
    cyhal_clock_t best_clock;
    uint32_t best_clock_freq = 0;
    uint32_t best_divider = 1;
    /* Go through all possible HFCLK clock sources and check what source fits best */
    for (uint32_t i = 0; i < count; ++i)
    {
        cyhal_clock_t temp_clock;
        if (CY_RSLT_SUCCESS == cyhal_clock_get(&temp_clock, sources[i]))
        {
            uint32_t cur_hf_source_freq = cyhal_clock_get_frequency(&temp_clock);
            /* source frequency is much lower than desired, no reason to continue */
            if ((0 == cur_hf_source_freq) ||
                ((NULL != tolerance) && (_cyhal_utils_calculate_tolerance(tolerance->type, hz, cur_hf_source_freq) > (int32_t)tolerance->value)))
            {
                continue;
            }
            /* Covering situation when PATHMUX has enabled FLL / PLL on its way. In that case FLL / PLL frequency
                is observed on PATHMUX which is covered in other iterations of the sources loop */
            if (CYHAL_CLOCK_BLOCK_PATHMUX == temp_clock.block)
            {
                if (((sources[i]->channel_num == 0) && Cy_SysClk_FllIsEnabled())
                #if (SRSS_NUM_PLL > 0)
                    || ((sources[i]->channel_num > 0) && (sources[i]->channel_num <= SRSS_NUM_PLL) &&
                        Cy_SysClk_PllIsEnabled(sources[i]->channel_num))
                #endif /* SRSS_NUM_PLL > 0 */
                #if !defined(COMPONENT_CAT1D)
                #if (SRSS_NUM_PLL400M > 0)
                    || ((sources[i]->channel_num > SRSS_NUM_PLL) && (sources[i]->channel_num <= SRSS_NUM_PLL + SRSS_NUM_PLL400M) &&
                        Cy_SysClk_PllIsEnabled(sources[i]->channel_num))
                #endif /* SRSS_NUM_PLL400M > 0 */
                #else /* !defined(COMPONENT_CAT1D) */
                #if (SRSS_NUM_DPLL_HP > 0)
                    || ((sources[i]->channel_num > SRSS_NUM_PLL) && (sources[i]->channel_num <= SRSS_NUM_PLL + SRSS_NUM_DPLL_HP) &&
                        Cy_SysClk_PllIsEnabled(sources[i]->channel_num))
                #endif /* SRSS_NUM_DPLL_HP > 0 */
                #endif /* !defined(COMPONENT_CAT1D) or other */
                )
                {
                    continue;
                }
            }

            uint32_t cur_clock_divider;
            if (CY_RSLT_SUCCESS == div_find_func(cur_hf_source_freq, hz, NULL, true, &cur_clock_divider))
            {
                uint32_t cur_divided_freq = cur_hf_source_freq / cur_clock_divider;
                uint32_t cur_clock_tolerance = abs(_cyhal_utils_calculate_tolerance(CYHAL_TOLERANCE_HZ, hz, cur_divided_freq));
                if (cur_clock_tolerance < best_tolerance_hz)
                {
                    best_clock = temp_clock;
                    best_tolerance_hz = cur_clock_tolerance;
                    best_clock_freq = cur_divided_freq;
                    best_divider = cur_clock_divider;
                    if (cur_divided_freq == hz)
                        break;
                }
            }
        }
    }

    if (0 == best_clock_freq)
    {
        retval = CYHAL_CLOCK_RSLT_ERR_SOURCE;
    }
    else if (NULL != tolerance) /* Verify within tolerance if one was provided. */
    {
        uint32_t achieved_tolerance = abs(_cyhal_utils_calculate_tolerance(tolerance->type, hz, best_clock_freq));
        if (achieved_tolerance > tolerance->value)
            retval = CYHAL_CLOCK_RSLT_ERR_FREQ;
    }

    if (CY_RSLT_SUCCESS == retval)
    {
        *hf_source = best_clock;
        *div = best_divider;
    }

    return retval;
}

cy_rslt_t _cyhal_utils_set_clock_frequency2(cyhal_clock_t *clock, uint32_t hz, const cyhal_clock_tolerance_t *tolerance)
{
    CY_ASSERT(NULL != clock);
    CY_ASSERT(hz != 0);

    cyhal_clock_t hf_source;
    uint32_t divider = 0;
    cy_rslt_t retval = _cyhal_utils_find_hf_source_n_divider(clock, hz, tolerance, _cyhal_utils_find_hf_clk_div,
                            &hf_source, &divider);
    if (CY_RSLT_SUCCESS == retval)
    {
        retval = cyhal_clock_set_source(clock, &hf_source);
    }
    if (CY_RSLT_SUCCESS == retval)
    {
        retval = cyhal_clock_set_divider(clock, divider);
    }

    return retval;
}
#endif

#if defined(__cplusplus)
}
#endif
