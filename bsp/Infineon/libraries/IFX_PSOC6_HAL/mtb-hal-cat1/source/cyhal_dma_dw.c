/***************************************************************************//**
* \file cyhal_dma_dw.c
*
* \brief
* Implements a high level interface for interacting with the Infineon Datawire DMA.
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

#include "cyhal_dma.h"
#include "cyhal_dma_dw.h"
#include "cyhal_dma_impl.h"
#include "cyhal_hwmgr_impl.h"
#include "cyhal_interconnect.h"
#include "cyhal_syspm.h"
#include "cyhal_irq_impl.h"
#include "cyhal_triggers.h"

#if (_CYHAL_DRIVER_AVAILABLE_DMA_DW)

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_DW0_PRESENT==1) && (CPUSS_DW1_PRESENT==1)
#define _CYHAL_DMA_DW_NUM_CHANNELS (CPUSS_DW0_CH_NR + CPUSS_DW1_CH_NR)
#elif (CPUSS_DW0_PRESENT==1)
#define _CYHAL_DMA_DW_NUM_CHANNELS (CPUSS_DW0_CH_NR)
#endif

// These devices do not have interrupts for all channels. Channels 29 and greater are absent.
#if defined(CY_DEVICE_PSOC6A256K) || defined(CY_DEVICE_PSOC6A512K)
#define CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ   29
#define CYHAL_DMA_DW1_MAX_CONTIGUOUS_IRQ   29
#else
#define CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ   CPUSS_DW0_CH_NR
#define CYHAL_DMA_DW1_MAX_CONTIGUOUS_IRQ   CPUSS_DW1_CH_NR
#endif

#define _CYHAL_DMA_GET_CPUSS_IRQN_IMPL(block, channel)   cpuss_interrupts_dw##block##_##channel##_IRQn
#define _CYHAL_DMA_GET_CPUSS_IRQN(block, channel)        _CYHAL_DMA_GET_CPUSS_IRQN_IMPL(block, channel)

static cyhal_dma_t* _cyhal_dma_dw_config_structs[_CYHAL_DMA_DW_NUM_CHANNELS];

/** Default dw descriptor config */
static const cy_stc_dma_descriptor_config_t _cyhal_dma_dw_default_descriptor_config =
{
    .retrigger = CY_DMA_RETRIG_IM,
    .interruptType = CY_DMA_DESCR,                  // Overridden by cyhal_dma_cfg_t.action
    .triggerOutType = CY_DMA_DESCR_CHAIN,           // Overridden by [en/dis]able_output()
    .channelState = CY_DMA_CHANNEL_ENABLED,         // Overridden by cyhal_dma_cfg_t.action
    .triggerInType = CY_DMA_DESCR,                  // Overridden by cyhal_dma_cfg_t.action & [dis]connect_digital()
    .dataSize = CY_DMA_WORD,                        // Overridden by cyhal_dma_cfg_t.transfer_width
    .srcTransferSize = CY_DMA_TRANSFER_SIZE_DATA,   // Overriden by direction
    .dstTransferSize = CY_DMA_TRANSFER_SIZE_DATA,   // Overriden by direction
    .descriptorType = CY_DMA_1D_TRANSFER,           // Overriden by cyhal_dma_cfg_t.burst_size
    .srcAddress = 0,                                // Overriden by cyhal_dma_cfg_t.src_addr
    .dstAddress = 0,                                // Overriden by cyhal_dma_cfg_t.dst_addr
    .srcXincrement = 1U,                            // Overriden by cyhal_dma_cfg_t.src_increment
    .dstXincrement = 1U,                            // Overriden by cyhal_dma_cfg_t.dst_increment
    .xCount = 1UL,                                  // Overriden by cyhal_dma_cfg_t.length/burst_size
    .srcYincrement = 0U,                            // Overriden by cyhal_dma_cfg_t.burst_size
    .dstYincrement = 0U,                            // Overriden by cyhal_dma_cfg_t.burst_size
    .yCount = 1UL,                                  // Overriden by cyhal_dma_cfg_t.length
    .nextDescriptor = 0,
};

/** Default dw channel config */
static const cy_stc_dma_channel_config_t _cyhal_dma_dw_default_channel_config =
{
    .descriptor = 0,        // Overriden by config()
    .preemptable = false,
    .priority = 1,          // Overriden by config().priority
    .enable = false,
    .bufferable = false,
};

static bool _cyhal_dma_dw_pm_callback(cyhal_syspm_callback_state_t state, cyhal_syspm_callback_mode_t mode, void* callback_arg);

static cyhal_syspm_callback_data_t cyhal_dma_dw_pm_callback_args = {
    .callback = &_cyhal_dma_dw_pm_callback,
    .states = (cyhal_syspm_callback_state_t)(CYHAL_SYSPM_CB_CPU_DEEPSLEEP | CYHAL_SYSPM_CB_SYSTEM_HIBERNATE),
    .next = NULL,
    .args = NULL,
    .ignore_modes = (cyhal_syspm_callback_mode_t)(CYHAL_SYSPM_BEFORE_TRANSITION | CYHAL_SYSPM_AFTER_DS_WFI_TRANSITION),
};
static bool _cyhal_dma_dw_pm_transition_pending = false;
static bool _cyhal_dma_dw_has_enabled(void)
{
    for (uint8_t i = 0; i < _CYHAL_DMA_DW_NUM_CHANNELS; i++)
        if (NULL != _cyhal_dma_dw_config_structs[i])
            return true;
    return false;
}

static bool _cyhal_dma_dw_pm_callback(cyhal_syspm_callback_state_t state, cyhal_syspm_callback_mode_t mode, void* callback_arg)
{
    CY_UNUSED_PARAMETER(state);
    CY_UNUSED_PARAMETER(callback_arg);
    bool block_transition = false;
    switch(mode)
    {
        case CYHAL_SYSPM_CHECK_READY:
            for (uint8_t i = 0; i < _CYHAL_DMA_DW_NUM_CHANNELS && !block_transition; i++)
            {
                block_transition |= (_cyhal_dma_dw_config_structs[i] != NULL) && _cyhal_dma_dw_is_busy(_cyhal_dma_dw_config_structs[i]);
            }

            _cyhal_dma_dw_pm_transition_pending = !block_transition;
            break;

        case CYHAL_SYSPM_CHECK_FAIL:
        case CYHAL_SYSPM_AFTER_TRANSITION:
            _cyhal_dma_dw_pm_transition_pending = false;
            break;
        default:
            CY_ASSERT(false);
            break;
    }
    return _cyhal_dma_dw_pm_transition_pending;
}

/** Sets the dw configuration struct */
static inline void _cyhal_dma_dw_set_obj(cyhal_dma_t *obj)
{
    _cyhal_dma_dw_config_structs[obj->resource.block_num * CPUSS_DW0_CH_NR + obj->resource.channel_num] = obj;
}

/** Zeros the dw configuration struct */
static inline void _cyhal_dma_dw_free_obj(cyhal_dma_t *obj)
{
    _cyhal_dma_dw_config_structs[obj->resource.block_num * CPUSS_DW0_CH_NR + obj->resource.channel_num] = NULL;
}

/** Gets the dw configuration struct from block and channel */
static inline cyhal_dma_t* _cyhal_dma_dw_get_obj(uint8_t block, uint8_t channel)
{
    return _cyhal_dma_dw_config_structs[block * CPUSS_DW0_CH_NR + channel];
}

/** Gets the dw block number from irq number */
/** This should never be called from a non-dma IRQn */
static inline uint8_t _cyhal_dma_dw_get_block_from_irqn(_cyhal_system_irq_t irqn)
{
#if (CPUSS_DW0_PRESENT==1)
#if defined(COMPONENT_CAT1D)
    if (irqn >= m33syscpuss_interrupts_dw0_0_IRQn && irqn < m33syscpuss_interrupts_dw0_0_IRQn + (_cyhal_system_irq_t)CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ)
#else
    if (irqn >= cpuss_interrupts_dw0_0_IRQn && irqn < cpuss_interrupts_dw0_0_IRQn + (_cyhal_system_irq_t)CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ)
#endif
        return 0;
#if (CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ != CPUSS_DW0_CH_NR)
    if ((irqn >= _CYHAL_DMA_GET_CPUSS_IRQN(0, CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ)) &&
        (irqn < (_cyhal_system_irq_t)(_CYHAL_DMA_GET_CPUSS_IRQN(0, CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ) + CPUSS_DW0_CH_NR - CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ)))
        return 0;
#endif
#endif
#if (CPUSS_DW1_PRESENT==1)
    if (irqn >= cpuss_interrupts_dw1_0_IRQn && irqn < cpuss_interrupts_dw1_0_IRQn + (_cyhal_system_irq_t)CYHAL_DMA_DW1_MAX_CONTIGUOUS_IRQ)
        return 1;
#if (CYHAL_DMA_DW1_MAX_CONTIGUOUS_IRQ != CPUSS_DW1_CH_NR)
    if ((irqn >= _CYHAL_DMA_GET_CPUSS_IRQN(1, CYHAL_DMA_DW1_MAX_CONTIGUOUS_IRQ)) &&
        (irqn < (_cyhal_system_irq_t)(_CYHAL_DMA_GET_CPUSS_IRQN(1, CYHAL_DMA_DW1_MAX_CONTIGUOUS_IRQ) + CPUSS_DW1_CH_NR - CYHAL_DMA_DW1_MAX_CONTIGUOUS_IRQ)))
        return 1;
#endif
#endif
    CY_ASSERT(false);
    return 0xFF;
}

/** Gets the dw channel number from irq number */
/** This should never be called from a non-dma IRQn */
static inline uint8_t _cyhal_dma_dw_get_channel_from_irqn(_cyhal_system_irq_t irqn)
{
#if (CPUSS_DW0_PRESENT==1)
#if defined(COMPONENT_CAT1D)
    if (irqn >= m33syscpuss_interrupts_dw0_0_IRQn && irqn < m33syscpuss_interrupts_dw0_0_IRQn + (_cyhal_system_irq_t)CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ)
        return (uint8_t)(irqn - m33syscpuss_interrupts_dw0_0_IRQn);
#else
    if (irqn >= cpuss_interrupts_dw0_0_IRQn && irqn < cpuss_interrupts_dw0_0_IRQn + (_cyhal_system_irq_t)CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ)
        return (uint8_t)(irqn - cpuss_interrupts_dw0_0_IRQn);
#endif
#if (CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ != CPUSS_DW0_CH_NR)
    if ((irqn >= _CYHAL_DMA_GET_CPUSS_IRQN(0, CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ)) &&
        (irqn < (_cyhal_system_irq_t)(_CYHAL_DMA_GET_CPUSS_IRQN(0, CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ) + CPUSS_DW0_CH_NR - CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ)))
        return CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ + irqn - _CYHAL_DMA_GET_CPUSS_IRQN(0, CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ);
#endif
#endif
#if (CPUSS_DW1_PRESENT==1)
    if (irqn >= cpuss_interrupts_dw1_0_IRQn && irqn < cpuss_interrupts_dw1_0_IRQn + (_cyhal_system_irq_t)CYHAL_DMA_DW1_MAX_CONTIGUOUS_IRQ)
        return (uint8_t)(irqn - cpuss_interrupts_dw1_0_IRQn);
#if (CYHAL_DMA_DW1_MAX_CONTIGUOUS_IRQ != CPUSS_DW1_CH_NR)
    if ((irqn >= _CYHAL_DMA_GET_CPUSS_IRQN(1, CYHAL_DMA_DW1_MAX_CONTIGUOUS_IRQ)) &&
        (irqn < (_cyhal_system_irq_t)(_CYHAL_DMA_GET_CPUSS_IRQN(1, CYHAL_DMA_DW1_MAX_CONTIGUOUS_IRQ) + CPUSS_DW1_CH_NR - CYHAL_DMA_DW1_MAX_CONTIGUOUS_IRQ)))
        return CYHAL_DMA_DW1_MAX_CONTIGUOUS_IRQ + irqn - _CYHAL_DMA_GET_CPUSS_IRQN(1, CYHAL_DMA_DW1_MAX_CONTIGUOUS_IRQ);
#endif
#endif
    CY_ASSERT(false);
    return 0xFF;
}

/** Gets the irqn corresponding to a particular cyhal_dma_t config struct */
static inline _cyhal_system_irq_t _cyhal_dma_dw_get_irqn(cyhal_dma_t *obj)
{
    // Some devices do not have contigious interrupts for all channels.
#if (CPUSS_DW0_PRESENT==1)
    if (obj->resource.block_num == 0 && obj->resource.channel_num < CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ)
    {
#if defined(COMPONENT_CAT1D)
        return (_cyhal_system_irq_t)((uint8_t)m33syscpuss_interrupts_dw0_0_IRQn + obj->resource.channel_num);
#else
        return (_cyhal_system_irq_t)((uint8_t)cpuss_interrupts_dw0_0_IRQn + obj->resource.channel_num);
#endif
    }
    #if (CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ != CPUSS_DW0_CH_NR)
    else if ((obj->resource.block_num == 0 && obj->resource.channel_num < CPUSS_DW0_CH_NR))
    {
        return (_cyhal_system_irq_t)((uint8_t)_CYHAL_DMA_GET_CPUSS_IRQN(0, CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ) + (obj->resource.channel_num - CYHAL_DMA_DW0_MAX_CONTIGUOUS_IRQ));
    }
    #endif
#endif
#if (CPUSS_DW1_PRESENT==1)
    if (obj->resource.block_num == 1 && obj->resource.channel_num < CYHAL_DMA_DW1_MAX_CONTIGUOUS_IRQ)
    {
        return (_cyhal_system_irq_t)((uint16_t)cpuss_interrupts_dw1_0_IRQn + obj->resource.channel_num);
    }
    #if (CYHAL_DMA_DW1_MAX_CONTIGUOUS_IRQ != CPUSS_DW1_CH_NR)
    else if (obj->resource.block_num == 1 && obj->resource.channel_num < CPUSS_DW1_CH_NR)
    {
        return (_cyhal_system_irq_t)((uint8_t)_CYHAL_DMA_GET_CPUSS_IRQN(1, CYHAL_DMA_DW1_MAX_CONTIGUOUS_IRQ) + (obj->resource.channel_num - CYHAL_DMA_DW1_MAX_CONTIGUOUS_IRQ));
    }
    #endif
#endif

    CY_ASSERT(false);
#if (_CYHAL_IRQ_MUXING)
    return disconnected_IRQn;
#else
    return unconnected_IRQn;
#endif
}

/** Gets the dw base pointer from block number */
static inline DW_Type* _cyhal_dma_dw_get_base(uint8_t block_num)
{
#if (CPUSS_DW1_PRESENT==1)
    return block_num == 0 ? DW0 : DW1;
#else
    CY_UNUSED_PARAMETER(block_num);
    return DW0;
#endif
}

/** Uses tables provided as part of the hal interconnect driver to determine mux
 * trigger group and mux trigger index and then construct the trigger line
 * input parameter to Cy_TrigMux_SwTrigger. */
static inline uint32_t _cyhal_dma_dw_get_trigger_line(uint8_t block_num, uint8_t channel_num)
{
    /* cyhal_dest_t triggers are guaranteed to be sorted by trigger type, block
     * num, then channel num, therefore, we can just directly find the proper
     * trigger by calculating an offset. */
#if defined(COMPONENT_CAT1D)
    cyhal_dest_t trigger = (cyhal_dest_t)(CYHAL_TRIGGER_M33SYSCPUSS_DW0_TR_IN0 + (block_num * CPUSS_DW0_CH_NR) + channel_num);
#else
    cyhal_dest_t trigger = (cyhal_dest_t)(CYHAL_TRIGGER_CPUSS_DW0_TR_IN0 + (block_num * CPUSS_DW0_CH_NR) + channel_num);
#endif

    /* One to one triggers have bit 8 set in cyhal_dest_to_mux but
     * Cy_TrigMux_SwTrigger wants the trigger group field to have bit 5 set to
     * denote one to one triggers. */
    uint8_t trig_group = cyhal_dest_to_mux[trigger];
    /* If hal one to one triggers bit is set: mask it out and set pdl one to
     * one bit */
    if(trig_group & _CYHAL_DMA_TRIGGERS_1TO1_MASK)
        trig_group = (trig_group & ~_CYHAL_DMA_TRIGGERS_1TO1_MASK) | _CYHAL_DMA_PDL_TRIGGERS_1TO1_MASK;

    /* Construct trigger line which consists of three fields packed into a
     * uint32_t:
     * Bits   30: Input/output bit. Set to 1 for output.
     * Bits 12-8: Trigger group selection.
     * Bits  7-0: Select the output trigger number in the trigger group. */
    return PERI_TR_CMD_OUT_SEL_Msk | (uint32_t)((uint32_t)trig_group << 8) | cyhal_mux_dest_index[trigger];
}

/** Convert PDL interrupt cause to hal dma event */
static inline cyhal_dma_event_t _cyhal_dma_dw_convert_interrupt_cause(cyhal_dma_t *obj, cy_en_dma_intr_cause_t cause)
{
    static const cyhal_dma_event_t hal[] =
    {
        CYHAL_DMA_NO_INTR,
        CYHAL_DMA_TRANSFER_COMPLETE,
        CYHAL_DMA_SRC_BUS_ERROR,
        CYHAL_DMA_DST_BUS_ERROR,
        CYHAL_DMA_SRC_MISAL,
        CYHAL_DMA_DST_MISAL,
        CYHAL_DMA_CURR_PTR_NULL,
        CYHAL_DMA_ACTIVE_CH_DISABLED,
        CYHAL_DMA_DESCR_BUS_ERROR
    };

    cyhal_dma_event_t hal_rslt = CYHAL_DMA_NO_INTR;
    CY_ASSERT(cause < sizeof(hal)/sizeof(cyhal_dma_event_t));
    if (cause < sizeof(hal)/sizeof(cyhal_dma_event_t))
        hal_rslt = hal[cause];

    if ((uint32_t)(hal_rslt & CYHAL_DMA_TRANSFER_COMPLETE) > 0 && obj->expected_bursts > 0)
    {
        obj->expected_bursts--;
        if (0 == obj->expected_bursts)
        {
            hal_rslt |= CYHAL_DMA_DESCRIPTOR_COMPLETE;
            obj->expected_bursts = (obj->descriptor_config.dw.interruptType == CY_DMA_X_LOOP)
                ? obj->descriptor_config.dw.yCount
                : 1;
        }
    }

    return hal_rslt;
}

/** DW irq handler */
static void _cyhal_dma_dw_irq_handler(void)
{
    /* Use irqn to get appropriate config structure */
    _cyhal_system_irq_t active_irq = _cyhal_irq_get_active();
    uint8_t block = _cyhal_dma_dw_get_block_from_irqn(active_irq);
    uint8_t channel = _cyhal_dma_dw_get_channel_from_irqn(active_irq);
    cyhal_dma_t *obj = _cyhal_dma_dw_get_obj(block, channel);

    /* Get interrupt type and call users event callback if they have enabled that event */
    cy_en_dma_intr_cause_t cause = Cy_DMA_Channel_GetStatus(_cyhal_dma_dw_get_base(block), channel);
    cyhal_dma_event_t event_type = _cyhal_dma_dw_convert_interrupt_cause(obj, cause);
    uint32_t events_to_callback = event_type & obj->irq_cause;
    if(obj->callback_data.callback != NULL && events_to_callback)
    {
        ((cyhal_dma_event_callback_t)obj->callback_data.callback)(obj->callback_data.callback_arg, (cyhal_dma_event_t)events_to_callback);
    }

    /* Clear all interrupts */
    Cy_DMA_Channel_ClearInterrupt(_cyhal_dma_dw_get_base(block), channel);
}

static cyhal_source_t _cyhal_dma_dw_get_src(uint8_t block_num, uint8_t channel_num)
{
#if defined(COMPONENT_CAT1D)
    return (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_M33SYSCPUSS_DW0_TR_OUT0 + (block_num * CPUSS_DW0_CH_NR) + channel_num, CYHAL_SIGNAL_TYPE_EDGE);
#else
    return (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE(_CYHAL_TRIGGER_CPUSS_DW0_TR_OUT0 + (block_num * CPUSS_DW0_CH_NR) + channel_num, CYHAL_SIGNAL_TYPE_EDGE);
#endif
}

static cyhal_dest_t _cyhal_dma_dw_get_dest(uint8_t block_num, uint8_t channel_num)
{
#if defined(COMPONENT_CAT1D)
    return (cyhal_dest_t)(CYHAL_TRIGGER_M33SYSCPUSS_DW0_TR_IN0 + (block_num * CPUSS_DW0_CH_NR) + channel_num);
#else
    return (cyhal_dest_t)(CYHAL_TRIGGER_CPUSS_DW0_TR_IN0 + (block_num * CPUSS_DW0_CH_NR) + channel_num);
#endif
}

cy_rslt_t _cyhal_dma_dw_stage(cyhal_dma_t *obj)
{
    #if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    SCB_CleanDCache_by_Addr((void *)&(obj->descriptor), sizeof(obj->descriptor));
    SCB_CleanDCache_by_Addr((void *)&(obj->descriptor_config), sizeof(obj->descriptor_config));
    #endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
    if(CY_DMA_SUCCESS != Cy_DMA_Descriptor_Init(&obj->descriptor.dw, &obj->descriptor_config.dw))
        return CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER;

    /* Setup channel and enable */
    #if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    SCB_CleanDCache_by_Addr((void *)&(obj->channel_config), sizeof(obj->channel_config));
    #endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
    DW_Type* base = _cyhal_dma_dw_get_base(obj->resource.block_num);
    if(CY_DMA_SUCCESS != Cy_DMA_Channel_Init(base, obj->resource.channel_num, &obj->channel_config.dw))
        return CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER;

    Cy_DMA_Channel_SetInterruptMask (base, obj->resource.channel_num, CY_DMA_INTR_MASK);

    Cy_DMA_Enable(base);

    /* src_misal and dst_misal interrupts are triggered immediately on enable
     * so return those errors here */
    uint32_t status = Cy_DMA_Channel_GetInterruptStatus(base, obj->resource.channel_num);
    if((status == CY_DMA_INTR_CAUSE_SRC_MISAL) ||
       (status == CY_DMA_INTR_CAUSE_DST_MISAL))
    {
        Cy_DMA_Channel_ClearInterrupt(base, obj->resource.channel_num);
        return CYHAL_DMA_RSLT_ERR_INVALID_ALIGNMENT;
    }

    /* Enable interrupt for this channel; preserve user priority if they enabled an interrupt */
    _cyhal_system_irq_t irqn = _cyhal_dma_dw_get_irqn(obj);
    uint32_t priority = (CYHAL_DMA_NO_INTR == obj->irq_cause)
        ? CYHAL_ISR_PRIORITY_DEFAULT
        : _cyhal_irq_get_priority(irqn);

    if(CY_RSLT_SUCCESS != _cyhal_irq_register(irqn, priority, _cyhal_dma_dw_irq_handler))
        return CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER;
    _cyhal_irq_enable(irqn);

    return CY_RSLT_SUCCESS;
}

cy_rslt_t _cyhal_dma_dw_init(cyhal_dma_t *obj, cyhal_source_t *src, cyhal_dest_t *dest, uint8_t priority)
{
    if(!CY_DMA_IS_PRIORITY_VALID(priority))
        return CYHAL_DMA_RSLT_ERR_INVALID_PRIORITY;

    cy_rslt_t rslt = _cyhal_hwmgr_allocate_with_connection(
        CYHAL_RSC_DW, src, dest, _cyhal_dma_dw_get_src, _cyhal_dma_dw_get_dest, &obj->resource);
    if(rslt != CY_RSLT_SUCCESS)
        return rslt;

    /* Setup descriptor and channel configs */
    obj->descriptor_config.dw = _cyhal_dma_dw_default_descriptor_config;
    obj->channel_config.dw = _cyhal_dma_dw_default_channel_config;
    obj->channel_config.dw.descriptor = &obj->descriptor.dw;
    obj->channel_config.dw.priority = priority;
#if CYHAL_DRIVER_AVAILABLE_SYSPM
    if (!_cyhal_dma_dw_has_enabled())
    {
        _cyhal_syspm_register_peripheral_callback(&cyhal_dma_dw_pm_callback_args);
    }
#endif
    _cyhal_dma_dw_set_obj(obj);

    return CY_RSLT_SUCCESS;
}

cy_rslt_t _cyhal_dma_dw_init_cfg(cyhal_dma_t *obj, const cyhal_dma_configurator_t *cfg)
{
    if (_cyhal_dma_dw_pm_transition_pending)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }

    obj->resource = *(cfg->resource);
    obj->callback_data.callback = NULL;

    /* Setup descriptor and channel configs */
    obj->descriptor_config.dw = *(cfg->dw_descriptor_config);
    obj->channel_config.dw = *(cfg->dw_channel_config);
    obj->channel_config.dw.descriptor = &obj->descriptor.dw;
    obj->expected_bursts = cfg->dw_descriptor_config->yCount;

#if CYHAL_DRIVER_AVAILABLE_SYSPM
    if (!_cyhal_dma_dw_has_enabled())
    {
        _cyhal_syspm_register_peripheral_callback(&cyhal_dma_dw_pm_callback_args);
    }
#endif

    _cyhal_dma_dw_set_obj(obj);

    return _cyhal_dma_dw_stage(obj);
}

void _cyhal_dma_dw_free(cyhal_dma_t *obj)
{
    Cy_DMA_Descriptor_DeInit(&obj->descriptor.dw);
    Cy_DMA_Channel_DeInit(_cyhal_dma_dw_get_base(obj->resource.block_num), obj->resource.channel_num);

    _cyhal_irq_free(_cyhal_dma_dw_get_irqn(obj));

    _cyhal_dma_dw_free_obj(obj);
#if CYHAL_DRIVER_AVAILABLE_SYSPM
    if (!_cyhal_dma_dw_has_enabled())
    {
        _cyhal_syspm_unregister_peripheral_callback(&cyhal_dma_dw_pm_callback_args);
        _cyhal_dma_dw_pm_transition_pending = false;
    }
#endif
}

/* Initialize descriptor, initialize channel, enable channel, enable channel
 * interrupt, and enable DW controller */
cy_rslt_t _cyhal_dma_dw_configure(cyhal_dma_t *obj, const cyhal_dma_cfg_t *cfg)
{
    /* Do not reconfigure if transfer is pending/active already */
    if(_cyhal_dma_dw_is_busy(obj))
        return CYHAL_DMA_RSLT_ERR_CHANNEL_BUSY;

    // DataWire only supports <=256 byte burst and <=256 bytes per burst
    if ((cfg->burst_size > 256) ||
        (cfg->burst_size <= 1 && cfg->length > 256) ||
        (cfg->burst_size > 0 && cfg->length > (cfg->burst_size * 256)))
        return CYHAL_DMA_RSLT_ERR_INVALID_TRANSFER_SIZE;

    #if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    SCB_CleanDCache_by_Addr((void *)cfg->src_addr, cfg->length * (cfg->transfer_width / 8));
    SCB_CleanDCache_by_Addr((void *)cfg->dst_addr, cfg->length * (cfg->transfer_width / 8));
    #endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
    obj->descriptor_config.dw.srcAddress = (void*)cfg->src_addr;
    obj->descriptor_config.dw.dstAddress = (void*)cfg->dst_addr;
    obj->descriptor_config.dw.nextDescriptor = &obj->descriptor.dw;
    if (cfg->action == CYHAL_DMA_TRANSFER_BURST || cfg->action == CYHAL_DMA_TRANSFER_FULL)
    {
        obj->descriptor_config.dw.channelState = CY_DMA_CHANNEL_ENABLED;
    }
    else
    {
        obj->descriptor_config.dw.channelState = CY_DMA_CHANNEL_DISABLED;
    }

    if(cfg->transfer_width == 8)
        obj->descriptor_config.dw.dataSize = CY_DMA_BYTE;
    else if(cfg->transfer_width == 16)
        obj->descriptor_config.dw.dataSize = CY_DMA_HALFWORD;
    else if(cfg->transfer_width == 32)
        obj->descriptor_config.dw.dataSize = CY_DMA_WORD;
    else
        return CYHAL_DMA_RSLT_ERR_INVALID_TRANSFER_WIDTH;

    /* By default, transfer what the user set for dataSize. However, if transfering between memory
     * and a peripheral, make sure the peripheral access is using words. */
    obj->descriptor_config.dw.srcTransferSize =
        obj->descriptor_config.dw.dstTransferSize = CY_DMA_TRANSFER_SIZE_DATA;
    if (obj->direction == CYHAL_DMA_DIRECTION_PERIPH2MEM)
        obj->descriptor_config.dw.srcTransferSize = CY_DMA_TRANSFER_SIZE_WORD;
    else if (obj->direction == CYHAL_DMA_DIRECTION_MEM2PERIPH)
        obj->descriptor_config.dw.dstTransferSize = CY_DMA_TRANSFER_SIZE_WORD;

    /* Length must be a multiple of burst_size */
    if(cfg->burst_size != 0 && cfg->length % cfg->burst_size != 0)
        return CYHAL_DMA_RSLT_ERR_INVALID_BURST_SIZE;

    /* Setup 2D transfer if burst_size is being used otherwise set up 1D transfer */
    obj->descriptor_config.dw.srcXincrement = cfg->src_increment;
    obj->descriptor_config.dw.dstXincrement = cfg->dst_increment;

    if(cfg->burst_size != 0)
    {
        obj->descriptor_config.dw.descriptorType = CY_DMA_2D_TRANSFER;
        obj->descriptor_config.dw.xCount = cfg->burst_size;
        obj->descriptor_config.dw.yCount = cfg->length / cfg->burst_size;
        obj->descriptor_config.dw.srcYincrement = cfg->src_increment * (int32_t)cfg->burst_size;
        obj->descriptor_config.dw.dstYincrement = cfg->dst_increment * (int32_t)cfg->burst_size;
    }
    else
    {
        obj->descriptor_config.dw.descriptorType = CY_DMA_1D_TRANSFER;
        obj->descriptor_config.dw.xCount = cfg->length;
        obj->descriptor_config.dw.yCount = 1;
        obj->descriptor_config.dw.srcYincrement = 0;
        obj->descriptor_config.dw.dstYincrement = 0;
    }

    /* If burst action, configure trigger and interrupt actions */
    if (cfg->burst_size != 0 &&
        (cfg->action == CYHAL_DMA_TRANSFER_BURST || cfg->action == CYHAL_DMA_TRANSFER_BURST_DISABLE))
    {
        obj->expected_bursts = obj->descriptor_config.dw.yCount;
        obj->descriptor_config.dw.interruptType = CY_DMA_X_LOOP;
        if (obj->source == CYHAL_TRIGGER_CPUSS_ZERO) // If not overridden by connect_digital()
            obj->descriptor_config.dw.triggerInType = CY_DMA_X_LOOP;
    }
    else
    {
        obj->expected_bursts = 1;
        obj->descriptor_config.dw.interruptType = CY_DMA_DESCR;
        if (obj->source == CYHAL_TRIGGER_CPUSS_ZERO) // If not overridden by connect_digital()
            obj->descriptor_config.dw.triggerInType = CY_DMA_DESCR;
    }

    return _cyhal_dma_dw_stage(obj);
}

cy_rslt_t _cyhal_dma_dw_enable(cyhal_dma_t *obj)
{
    DW_Type* base = _cyhal_dma_dw_get_base(obj->resource.block_num);
    Cy_DMA_Channel_Enable(base, obj->resource.channel_num);
    return CY_RSLT_SUCCESS;
}

cy_rslt_t _cyhal_dma_dw_disable(cyhal_dma_t *obj)
{
    DW_Type* base = _cyhal_dma_dw_get_base(obj->resource.block_num);
    Cy_DMA_Channel_Disable(base, obj->resource.channel_num);
    return CY_RSLT_SUCCESS;
}

cy_rslt_t _cyhal_dma_dw_start_transfer(cyhal_dma_t *obj)
{
    /* Return warning if channel is busy */
    if(_cyhal_dma_dw_is_busy(obj))
        return CYHAL_DMA_RSLT_WARN_TRANSFER_ALREADY_STARTED;

    if (_cyhal_dma_dw_pm_transition_pending)
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;

    uint32_t trigline = _cyhal_dma_dw_get_trigger_line(obj->resource.block_num, obj->resource.channel_num);
    cy_en_trigmux_status_t trig_status = Cy_TrigMux_SwTrigger(trigline, CY_TRIGGER_TWO_CYCLES);

    /* Also return warning if SW trigger is already initiated but DMA hardware
     * has not seen it yet */
    if(trig_status == CY_TRIGMUX_INVALID_STATE)
        return CYHAL_DMA_RSLT_WARN_TRANSFER_ALREADY_STARTED;
    else
        return CY_RSLT_SUCCESS;
}

void _cyhal_dma_dw_enable_event(cyhal_dma_t *obj, cyhal_dma_event_t event, uint8_t intr_priority, bool enable)
{
    if(enable)
        obj->irq_cause |= event;
    else
        obj->irq_cause &= ~event;

    _cyhal_irq_set_priority(_cyhal_dma_dw_get_irqn(obj), intr_priority);
}

bool _cyhal_dma_dw_is_busy(cyhal_dma_t *obj)
{
#if CY_IP_M4CPUSS_DMA_VERSION == 1
    /* In DW_V1 the pending channel information is stored in the PENDING
     * register of the DW block and is a bit field of all pending or active
     * channels */
    return _cyhal_dma_dw_get_base(obj->resource.block_num)->PENDING & (1 << obj->resource.channel_num);
#elif (CY_IP_M4CPUSS_DMA_VERSION == 2)
    /* In DW_V2 the pending channel information is stored in the STATUS
     * register of the channel itself */
    return DW_CH_STATUS(_cyhal_dma_dw_get_base(obj->resource.block_num), obj->resource.channel_num) & (1UL << DW_CH_STRUCT_V2_CH_STATUS_PENDING_Pos);
#elif defined(CY_IP_M7CPUSS) || defined(CY_IP_MXDW)
    return DW_CH_STATUS(_cyhal_dma_dw_get_base(obj->resource.block_num), obj->resource.channel_num) & (1UL << DW_CH_STRUCT_CH_STATUS_PENDING_Pos);
#else
    // Should never reach here. Just silencing compiler warnings.
    CY_ASSERT(false);
    return false;
#endif
}

static cy_en_dma_trigger_type_t _cyhal_convert_input_t(cyhal_dma_input_t input)
{
    switch(input)
    {
        case CYHAL_DMA_INPUT_TRIGGER_SINGLE_ELEMENT:
            return CY_DMA_1ELEMENT;
        case CYHAL_DMA_INPUT_TRIGGER_SINGLE_BURST:
            return CY_DMA_X_LOOP;
        case CYHAL_DMA_INPUT_TRIGGER_ALL_ELEMENTS:
            return CY_DMA_DESCR;
        default:
            // Should never reach here. Just silencing compiler warnings.
            CY_ASSERT(false);
            return CY_DMA_DESCR;
    }
}

static cy_en_dma_trigger_type_t _cyhal_convert_output_t(cyhal_dma_output_t output)
{
    switch(output)
    {
        case CYHAL_DMA_OUTPUT_TRIGGER_SINGLE_ELEMENT:
            return CY_DMA_1ELEMENT;
        case CYHAL_DMA_OUTPUT_TRIGGER_SINGLE_BURST:
            return CY_DMA_X_LOOP;
        case CYHAL_DMA_OUTPUT_TRIGGER_ALL_ELEMENTS:
            return CY_DMA_DESCR;
        default:
            // Should never reach here. Just silencing compiler warnings.
            CY_ASSERT(false);
            return CY_DMA_DESCR;
    }
}

cy_rslt_t _cyhal_dma_dw_connect_digital(cyhal_dma_t *obj, cyhal_source_t source, cyhal_dma_input_t input)
{
    if(input != CYHAL_DMA_INPUT_TRIGGER_SINGLE_ELEMENT &&
       input != CYHAL_DMA_INPUT_TRIGGER_SINGLE_BURST &&
       input != CYHAL_DMA_INPUT_TRIGGER_ALL_ELEMENTS)
        return CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER;
    // Check that we are not overwriting an existing connection
    CY_ASSERT(obj->source == CYHAL_TRIGGER_CPUSS_ZERO);

    obj->descriptor_config.dw.triggerInType = _cyhal_convert_input_t(input);
    obj->descriptor.dw.ctl &= ~CY_DMA_CTL_TR_IN_TYPE_Msk;
    obj->descriptor.dw.ctl |= _VAL2FLD(CY_DMA_CTL_TR_IN_TYPE, obj->descriptor_config.dw.triggerInType);

    cyhal_dest_t dest = _cyhal_dma_dw_get_dest(obj->resource.block_num, obj->resource.channel_num);

    cy_rslt_t rslt = _cyhal_connect_signal(source, dest);
    if (CY_RSLT_SUCCESS == rslt)
    {
        obj->source = source;
    }

    return rslt;
}

cy_rslt_t _cyhal_dma_dw_enable_output(cyhal_dma_t *obj, cyhal_dma_output_t output, cyhal_source_t *source)
{
    if(output != CYHAL_DMA_OUTPUT_TRIGGER_SINGLE_ELEMENT &&
       output != CYHAL_DMA_OUTPUT_TRIGGER_SINGLE_BURST &&
       output != CYHAL_DMA_OUTPUT_TRIGGER_ALL_ELEMENTS)
        return CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER;

    obj->descriptor.dw.ctl &= ~CY_DMA_CTL_TR_OUT_TYPE_Msk;
    obj->descriptor.dw.ctl |= _VAL2FLD(CY_DMA_CTL_TR_OUT_TYPE, _cyhal_convert_output_t(output));

    *source = _cyhal_dma_dw_get_src(obj->resource.block_num, obj->resource.channel_num);

    return CY_RSLT_SUCCESS;
}

cy_rslt_t _cyhal_dma_dw_disconnect_digital(cyhal_dma_t *obj, cyhal_source_t source, cyhal_dma_input_t input)
{
    if(input != CYHAL_DMA_INPUT_TRIGGER_SINGLE_ELEMENT &&
       input != CYHAL_DMA_INPUT_TRIGGER_SINGLE_BURST &&
       input != CYHAL_DMA_INPUT_TRIGGER_ALL_ELEMENTS)
        return CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER;
    CY_ASSERT(obj->source != CYHAL_TRIGGER_CPUSS_ZERO);

    // There is no option to totally disable. Just reset to default.
    // NOTE: Use .interruptType since it matches the desired .triggerInType from configure(), but
    // is not modified by connect/disconnect functions
    obj->descriptor.dw.ctl &= ~CY_DMA_CTL_TR_IN_TYPE_Msk;
    obj->descriptor.dw.ctl |= _VAL2FLD(CY_DMA_CTL_TR_IN_TYPE, _cyhal_dma_dw_default_descriptor_config.interruptType);


    cyhal_dest_t dest = _cyhal_dma_dw_get_dest(obj->resource.block_num, obj->resource.channel_num);

    cy_rslt_t rslt = _cyhal_disconnect_signal(source, dest);
    if (CY_RSLT_SUCCESS == rslt)
    {
        obj->source = CYHAL_TRIGGER_CPUSS_ZERO;
    }

    return rslt;
}

cy_rslt_t _cyhal_dma_dw_disable_output(cyhal_dma_t *obj, cyhal_dma_output_t output)
{
    if(output != CYHAL_DMA_OUTPUT_TRIGGER_SINGLE_ELEMENT &&
       output != CYHAL_DMA_OUTPUT_TRIGGER_SINGLE_BURST &&
       output != CYHAL_DMA_OUTPUT_TRIGGER_ALL_ELEMENTS)
        return CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER;

    // There is no option to totally disable. Just reset to default.
    obj->descriptor.dw.ctl &= ~CY_DMA_CTL_TR_OUT_TYPE_Msk;
    obj->descriptor.dw.ctl |= _VAL2FLD(CY_DMA_CTL_TR_OUT_TYPE, _cyhal_dma_dw_default_descriptor_config.triggerOutType);

    return CY_RSLT_SUCCESS;
}

#if defined(__cplusplus)
}
#endif

#endif /* _CYHAL_DRIVER_AVAILABLE_DMA_DW */
