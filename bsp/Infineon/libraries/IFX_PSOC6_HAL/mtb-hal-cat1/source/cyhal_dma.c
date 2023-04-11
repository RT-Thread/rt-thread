/***************************************************************************//**
* \file cyhal_dma.c
*
* \brief
* Implements a high level interface for interacting with the Infineon DMA.
* This implementation abstracts out the chip specific details. If any chip specific
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

/**
 * \addtogroup group_hal_impl_dma DMA (Direct Memory Access)
 * \ingroup group_hal_impl
 * \{
 * \section section_hal_impl_dma_data_arr_requirement User-provided data arrays requirements
 * CM7 cores in CAT1C devices support Data Cache. Data Cache line is 32 bytes. User needs to make sure that
 * the source and destination buffer pointers points to 32 byte aligned data. User can use CY_ALIGN(32) macro for
 * 32 byte alignment.
 *
 * \} group_hal_impl_dma
 */

#include "cyhal_dma.h"
#include "cyhal_system.h"
#include "cyhal_hwmgr.h"

#if (CYHAL_DRIVER_AVAILABLE_DMA)

#if (_CYHAL_DRIVER_AVAILABLE_DMA_DMAC)
#include "cyhal_dma_dmac.h"
#endif
#if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
#include "cyhal_dma_dw.h"
#endif

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */


cy_rslt_t cyhal_dma_init_adv(
    cyhal_dma_t *obj, cyhal_dma_src_t *src, cyhal_dma_dest_t *dest, cyhal_source_t *dest_source, uint8_t priority, cyhal_dma_direction_t direction)
{
    CY_ASSERT(NULL != obj);

    obj->direction = direction;
    obj->callback_data.callback = NULL;
    obj->callback_data.callback_arg = NULL;
    obj->irq_cause = 0;
    obj->source = CYHAL_TRIGGER_CPUSS_ZERO;
    obj->owned_by_configurator = false;

    cy_rslt_t rslt;
    cyhal_source_t *src_trigger = (NULL == src) ? NULL : &src->source;
    cyhal_dest_t *dest_trigger = (NULL == dest) ? NULL : &dest->dest;

#if (_CYHAL_DRIVER_AVAILABLE_DMA_DW && !_CYHAL_DRIVER_AVAILABLE_DMA_DMAC)
    /* Only DW available. */
    rslt = _cyhal_dma_dw_init(obj, src_trigger, dest_trigger, priority);
#elif (_CYHAL_DRIVER_AVAILABLE_DMA_DMAC && !_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    /* Only DMAC available. */
    rslt = _cyhal_dma_dmac_init(obj, src_trigger, dest_trigger, priority);
#else
    /* DMAC is designed with high memory bandwidth for memory to memory
     * transfers so prefer it when direction is MEM2MEM. Otherwise prefer
     * Datawire as it is designed for low latency memory to peripheral or
     * peripheral to memory transfers. Note: Both DMA types can handle any
     * direction value so using a non-ideal DMA type is ok.*/
    if(direction == CYHAL_DMA_DIRECTION_MEM2MEM)
    {
        rslt = _cyhal_dma_dmac_init(obj, src_trigger, dest_trigger, priority);
        /* If no DMAC channels are available fall back on DW. */
        if(CYHAL_HWMGR_RSLT_ERR_NONE_FREE == rslt)
            rslt = _cyhal_dma_dw_init(obj, src_trigger, dest_trigger, priority);
    }
    else
    {
        rslt = _cyhal_dma_dw_init(obj, src_trigger, dest_trigger, priority);
        /* If no DW channels are available fall back on DMAC. */
        if(CYHAL_HWMGR_RSLT_ERR_NONE_FREE == rslt)
            rslt = _cyhal_dma_dmac_init(obj, src_trigger, dest_trigger, priority);
    }
#endif

    if (CY_RSLT_SUCCESS == rslt)
    {
        if (NULL != src)
        {
            rslt = cyhal_dma_connect_digital(obj, src->source, src->input);
            obj->source = src->source;
        }

        if ((CY_RSLT_SUCCESS == rslt) && (NULL != dest))
        {
            rslt = cyhal_dma_enable_output(obj, dest->output, dest_source);
        }

        // If connection setup failed, free the resources.
        if (CY_RSLT_SUCCESS != rslt)
        {
            cyhal_dma_free(obj);
        }
    }

    return rslt;
}

cy_rslt_t cyhal_dma_init_cfg(cyhal_dma_t *obj, const cyhal_dma_configurator_t *cfg)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != cfg);

    obj->owned_by_configurator = true;

#if (_CYHAL_DRIVER_AVAILABLE_DMA_DMAC)
    #if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    if (cfg->resource->type == CYHAL_RSC_DMA)
    #endif
    {
        return _cyhal_dma_dmac_init_cfg(obj, cfg);
    }
#endif
#if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    CY_ASSERT(cfg->resource->type == CYHAL_RSC_DW);
    return _cyhal_dma_dw_init_cfg(obj, cfg);
#endif
}

void cyhal_dma_free(cyhal_dma_t *obj)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(!cyhal_dma_is_busy(obj));

    cy_rslt_t rslt;
    // DMA signal enum values don't matter since they are actually the same connection
    rslt = cyhal_dma_disable_output(obj, CYHAL_DMA_OUTPUT_TRIGGER_ALL_ELEMENTS);
    CY_ASSERT(CY_RSLT_SUCCESS == rslt);
    if (CYHAL_TRIGGER_CPUSS_ZERO != obj->source)
    {
        rslt = cyhal_dma_disconnect_digital(obj, obj->source, CYHAL_DMA_INPUT_TRIGGER_ALL_ELEMENTS);
        CY_ASSERT(CY_RSLT_SUCCESS == rslt);
    }
    (void)rslt; // Disable compiler warning in release build

#if (_CYHAL_DRIVER_AVAILABLE_DMA_DMAC)
    #if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    if(obj->resource.type == CYHAL_RSC_DMA)
    #endif
    {
        _cyhal_dma_dmac_free(obj);
    }
#endif
#if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    #if (_CYHAL_DRIVER_AVAILABLE_DMA_DMAC)
    if(obj->resource.type == CYHAL_RSC_DW)
    #endif
    {
        _cyhal_dma_dw_free(obj);
    }
#endif

    if (!obj->owned_by_configurator)
    {
        cyhal_hwmgr_free(&obj->resource);
    }
}

cy_rslt_t cyhal_dma_configure(cyhal_dma_t *obj, const cyhal_dma_cfg_t *cfg)
{
    CY_ASSERT(NULL != obj);

#if (_CYHAL_DRIVER_AVAILABLE_DMA_DMAC)
    #if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    if(obj->resource.type == CYHAL_RSC_DMA)
    #endif
    {
        return _cyhal_dma_dmac_configure(obj, cfg);
    }
#endif
#if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    CY_ASSERT(obj->resource.type == CYHAL_RSC_DW);
    return _cyhal_dma_dw_configure(obj, cfg);
#endif
}

cy_rslt_t cyhal_dma_start_transfer(cyhal_dma_t *obj)
{
    CY_ASSERT(NULL != obj);

#if (_CYHAL_DRIVER_AVAILABLE_DMA_DMAC)
    #if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    if(obj->resource.type == CYHAL_RSC_DMA)
    #endif
    {
        return _cyhal_dma_dmac_start_transfer(obj);
    }
#endif
#if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    CY_ASSERT(obj->resource.type == CYHAL_RSC_DW);
    return _cyhal_dma_dw_start_transfer(obj);
#endif
}

cy_rslt_t cyhal_dma_enable(cyhal_dma_t *obj)
{
    CY_ASSERT(NULL != obj);

#if (_CYHAL_DRIVER_AVAILABLE_DMA_DMAC)
    #if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    if(obj->resource.type == CYHAL_RSC_DMA)
    #endif
    {
        return _cyhal_dma_dmac_enable(obj);
    }
#endif
#if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    CY_ASSERT(obj->resource.type == CYHAL_RSC_DW);
    return _cyhal_dma_dw_enable(obj);
#endif
}

cy_rslt_t cyhal_dma_disable(cyhal_dma_t *obj)
{
    CY_ASSERT(NULL != obj);

#if (_CYHAL_DRIVER_AVAILABLE_DMA_DMAC)
    #if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    if(obj->resource.type == CYHAL_RSC_DMA)
    #endif
    {
        return _cyhal_dma_dmac_disable(obj);
    }
#endif
#if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    CY_ASSERT(obj->resource.type == CYHAL_RSC_DW);
    return _cyhal_dma_dw_disable(obj);
#endif
}

bool cyhal_dma_is_busy(cyhal_dma_t *obj)
{
    CY_ASSERT(NULL != obj);

#if (_CYHAL_DRIVER_AVAILABLE_DMA_DMAC)
    #if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    if(obj->resource.type == CYHAL_RSC_DMA)
    #endif
    {
        return _cyhal_dma_dmac_is_busy(obj);
    }
#endif
#if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    CY_ASSERT(obj->resource.type == CYHAL_RSC_DW);
    return _cyhal_dma_dw_is_busy(obj);
#endif
}

void cyhal_dma_register_callback(cyhal_dma_t *obj, cyhal_dma_event_callback_t callback, void *callback_arg)
{
    CY_ASSERT(NULL != obj);

    uint32_t saved_intr_status = cyhal_system_critical_section_enter();
    obj->callback_data.callback = (cy_israddress)callback;
    obj->callback_data.callback_arg = callback_arg;
    cyhal_system_critical_section_exit(saved_intr_status);
}

void cyhal_dma_enable_event(cyhal_dma_t *obj, cyhal_dma_event_t event, uint8_t intr_priority, bool enable)
{
    CY_ASSERT(NULL != obj);

#if (_CYHAL_DRIVER_AVAILABLE_DMA_DMAC)
    #if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    if(obj->resource.type == CYHAL_RSC_DMA)
    #endif
    {
        _cyhal_dma_dmac_enable_event(obj, event, intr_priority, enable);
        return;
    }
#endif
#if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    CY_ASSERT(obj->resource.type == CYHAL_RSC_DW);
    _cyhal_dma_dw_enable_event(obj, event, intr_priority, enable);
#endif
}

cy_rslt_t cyhal_dma_connect_digital(cyhal_dma_t *obj, cyhal_source_t source, cyhal_dma_input_t input)
{
    CY_ASSERT(NULL != obj);

#if (_CYHAL_DRIVER_AVAILABLE_DMA_DMAC)
    #if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    if(obj->resource.type == CYHAL_RSC_DMA)
    #endif
    {
        return _cyhal_dma_dmac_connect_digital(obj, source, input);
    }
#endif
#if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    CY_ASSERT(obj->resource.type == CYHAL_RSC_DW);
    return _cyhal_dma_dw_connect_digital(obj, source, input);
#endif
}

cy_rslt_t cyhal_dma_enable_output(cyhal_dma_t *obj, cyhal_dma_output_t output, cyhal_source_t *source)
{
    CY_ASSERT(NULL != obj);

#if (_CYHAL_DRIVER_AVAILABLE_DMA_DMAC)
    #if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    if(obj->resource.type == CYHAL_RSC_DMA)
    #endif
    {
        return _cyhal_dma_dmac_enable_output(obj, output, source);
    }
#endif
#if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    CY_ASSERT(obj->resource.type == CYHAL_RSC_DW);
    return _cyhal_dma_dw_enable_output(obj, output, source);
#endif
}

cy_rslt_t cyhal_dma_disconnect_digital(cyhal_dma_t *obj, cyhal_source_t source, cyhal_dma_input_t input)
{
    CY_ASSERT(NULL != obj);

#if (_CYHAL_DRIVER_AVAILABLE_DMA_DMAC)
    #if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    if(obj->resource.type == CYHAL_RSC_DMA)
    #endif
    {
        return _cyhal_dma_dmac_disconnect_digital(obj, source, input);
    }
#endif
#if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    CY_ASSERT(obj->resource.type == CYHAL_RSC_DW);
    return _cyhal_dma_dw_disconnect_digital(obj, source, input);
#endif
}

cy_rslt_t cyhal_dma_disable_output(cyhal_dma_t *obj, cyhal_dma_output_t output)
{
    CY_ASSERT(NULL != obj);

#if (_CYHAL_DRIVER_AVAILABLE_DMA_DMAC)
    #if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    if(obj->resource.type == CYHAL_RSC_DMA)
    #endif
    {
        return _cyhal_dma_dmac_disable_output(obj, output);
    }
#endif
#if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)
    CY_ASSERT(obj->resource.type == CYHAL_RSC_DW);
    return _cyhal_dma_dw_disable_output(obj, output);
#endif
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* (CYHAL_DRIVER_AVAILABLE_DMA) */
