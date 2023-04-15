/***************************************************************************//**
* \file cyhal_dma_dmac.c
*
* \brief
* Implements a high level interface for interacting with the Infineon DMAC.
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
#include "cyhal_dma_dmac.h"
#include "cyhal_dma_impl.h"
#include "cyhal_hwmgr_impl.h"
#include "cyhal_interconnect.h"
#include "cyhal_syspm.h"
#include "cyhal_utils.h"
#include "cyhal_irq_impl.h"
#include "cyhal_triggers.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if (_CYHAL_DRIVER_AVAILABLE_DMA_DMAC)

#if defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC)
#define DMAC0_IRQn                  (cpuss_interrupts_dmac_0_IRQn)
#define GET_RESOURCE_DATA(x)        (x.dmac)
typedef DMAC_Type                   cyhal_dmac_hw_type;
#elif defined(CY_IP_M0S8CPUSSV3_DMAC)
#define DMAC0_IRQn                  (cpuss_interrupt_dma_IRQn)
#define GET_RESOURCE_DATA(x)        (x)
#define CY_TRIGGER_TWO_CYCLES       (2)
typedef DMAC_Type                   cyhal_dmac_hw_type;
#elif defined(CY_IP_MXAHBDMAC)
#define DMAC0_IRQn                  (cpuss_interrupts_dmac0_0_IRQn)
#define DMAC1_IRQn                  (cpuss_interrupts_dmac1_0_IRQn)
#define GET_RESOURCE_DATA(x)        (x.dmac)
typedef MXAHBDMAC_Type              cyhal_dmac_hw_type;
#elif defined(CY_IP_MXSAXIDMAC)
#define DMAC0_IRQn                  (m55appcpuss_interrupts_axidmac_0_IRQn)
typedef SAXI_DMAC_Type              cyhal_dmac_hw_type;
#define GET_RESOURCE_DATA(x)        (x.dmac)
#endif

#if defined (AXI_DMAC_CH_NR)
#if APPCPUSS_AXIDMAC1_PRESENT
#define NUM_DMAC0_CHANNELS          (APPCPUSS_AXIDMAC0_CH_NR)
#define NUM_DMAC_CHANNELS           (APPCPUSS_AXIDMAC0_CH_NR + APPCPUSS_AXIDMAC1_CH_NR)
#else
#define NUM_DMAC0_CHANNELS          (APPCPUSS_AXIDMAC0_CH_NR)
#define NUM_DMAC_CHANNELS           (APPCPUSS_AXIDMAC0_CH_NR)
#endif
#elif defined(CPUSS_DMAC0_CH_NR) && defined(CPUSS_DMAC1_CH_NR) && (CPUSS_DMAC0_PRESENT > 0) && (CPUSS_DMAC1_PRESENT > 0)
#define NUM_DMAC_CHANNELS           (CPUSS_DMAC0_CH_NR + CPUSS_DMAC1_CH_NR)
#define NUM_DMAC0_CHANNELS          (CPUSS_DMAC0_CH_NR)
#elif defined(CPUSS_DMAC_CH_NR)
#define NUM_DMAC_CHANNELS           (CPUSS_DMAC_CH_NR)
#define CPUSS_DMAC0_CH_NR           (CPUSS_DMAC_CH_NR)
#define NUM_DMAC0_CHANNELS          (CPUSS_DMAC_CH_NR)
#define CYHAL_TRIGGER_CPUSS_DMAC0_TR_IN0   (CYHAL_TRIGGER_CPUSS_DMAC_TR_IN0)
#define _CYHAL_TRIGGER_CPUSS_DMAC0_TR_OUT0 (_CYHAL_TRIGGER_CPUSS_DMAC_TR_OUT0)
#endif

//Wrappers for PDL functions and Macros for AXI DMAC differences
#if defined(CY_IP_MXSAXIDMAC)
#define _cyhal_dmac_channel_enable(base, channel)   Cy_AXIDMAC_Channel_Enable(base, channel)
#define _cyhal_dmac_channel_disable(base, channel)  Cy_AXIDMAC_Channel_Disable(base, channel)
#define _cyhal_dmac_get_active_channel(base)        Cy_AXIDMAC_GetActiveChannel(base)
#define _cyhal_dmac_channel_get_interrupt_status_masked(base, channel) Cy_AXIDMAC_Channel_GetInterruptStatusMasked(base, channel)
#define _CYHAL_DMAC_CHANNEL_ENABLED        (CY_AXIDMAC_CHANNEL_ENABLED)
#define _CYHAL_DMAC_CHANNEL_DISABLED       (CY_AXIDMAC_CHANNEL_DISABLED)
#define _CYHAL_DMAC_DESCR            (CY_AXIDMAC_DESCR)
#define _CYHAL_DMAC_X_LOOP           (CY_AXIDMAC_X_LOOP)
#define _CYHAL_DMAC_CH_DESCR_CTL_TR_IN_TYPE_Msk   (SAXI_DMAC_CH_DESCR_CTL_TR_IN_TYPE_Msk)
#define _CYHAL_DMAC_CH_DESCR_CTL_TR_OUT_TYPE_Msk   (SAXI_DMAC_CH_DESCR_CTL_TR_OUT_TYPE_Msk)
#define _CYHAL_DMAC_CH_DESCR_CTL_TR_IN_TYPE        (SAXI_DMAC_CH_DESCR_CTL_TR_IN_TYPE)
#define _CYHAL_DMAC_CH_DESCR_CTL_TR_OUT_TYPE       (SAXI_DMAC_CH_DESCR_CTL_TR_OUT_TYPE)
#define _CYHAL_DMAC_CH_DESCR_CTL_TR_IN_TYPE_Pos    (SAXI_DMAC_CH_DESCR_CTL_TR_IN_TYPE_Pos)
#define _CYHAL_DMAC_CH_DESCR_CTL_TR_OUT_TYPE_Pos    (SAXI_DMAC_CH_DESCR_CTL_TR_OUT_TYPE_Pos)
#define _CYHAL_TRIGGER_CPUSS_ZERO                  (CYHAL_TRIGGER_M33SYSCPUSS_ZERO)
#elif defined(CY_IP_MXAHBDMAC) || defined(CY_IP_M0S8CPUSSV3_DMAC) || defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC)
#define _cyhal_dmac_channel_enable(base, channel)   Cy_DMAC_Channel_Enable(base, channel)
#define _cyhal_dmac_channel_disable(base, channel)  Cy_DMAC_Channel_Disable(base, channel)
#define _cyhal_dmac_get_active_channel(base)        Cy_DMAC_GetActiveChannel(base)
#define _cyhal_dmac_channel_get_interrupt_status_masked(base, channel) Cy_DMAC_Channel_GetInterruptStatusMasked(base, channel)
#define _CYHAL_DMAC_CHANNEL_ENABLED        (CY_DMAC_CHANNEL_ENABLED)
#define _CYHAL_DMAC_CHANNEL_DISABLED       (CY_DMAC_CHANNEL_DISABLED)
#define _CYHAL_DMAC_DESCR            (CY_DMAC_DESCR)
#define _CYHAL_DMAC_X_LOOP           (CY_DMAC_X_LOOP)
#define _CYHAL_DMAC_CH_DESCR_CTL_TR_IN_TYPE_Msk    (DMAC_CH_V2_DESCR_CTL_TR_IN_TYPE_Msk)
#define _CYHAL_DMAC_CH_DESCR_CTL_TR_OUT_TYPE_Msk   (DMAC_CH_V2_DESCR_CTL_TR_OUT_TYPE_Msk)
#define _CYHAL_DMAC_CH_DESCR_CTL_TR_IN_TYPE        (DMAC_CH_V2_DESCR_CTL_TR_IN_TYPE)
#define _CYHAL_DMAC_CH_DESCR_CTL_TR_OUT_TYPE       (DMAC_CH_V2_DESCR_CTL_TR_OUT_TYPE)
#define _CYHAL_DMAC_CH_DESCR_CTL_TR_IN_TYPE_Pos    (DMAC_CH_V2_DESCR_CTL_TR_IN_TYPE_Pos)
#define _CYHAL_DMAC_CH_DESCR_CTL_TR_OUT_TYPE_Pos   (DMAC_CH_V2_DESCR_CTL_TR_OUT_TYPE_Pos)
#define _CYHAL_TRIGGER_CPUSS_ZERO                  (CYHAL_TRIGGER_CPUSS_ZERO)
#endif


static cyhal_dma_t* _cyhal_dma_dmac_config_structs[NUM_DMAC_CHANNELS];

/** Default dmac descriptor config */
#if defined(CY_IP_MXSAXIDMAC)
static const cy_stc_axidmac_descriptor_config_t _cyhal_dma_dmac_default_descriptor_config =
#else
static const cy_stc_dmac_descriptor_config_t _cyhal_dma_dmac_default_descriptor_config =
#endif
{
    .srcAddress = 0,                                // Overriden by cyhal_dma_cfg_t.src_addr
    .dstAddress = 0,                                // Overriden by cyhal_dma_cfg_t.dst_addr
#if defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_MXAHBDMAC)
    .dataSize = CY_DMAC_WORD,                       // Overridden by cyhal_dma_cfg_t.transfer_width
    .dstTransferSize = CY_DMAC_TRANSFER_SIZE_DATA,  // Overriden by direction
    .srcTransferSize = CY_DMAC_TRANSFER_SIZE_DATA,  // Overriden by direction
    .retrigger = CY_DMAC_RETRIG_IM,
    .interruptType = CY_DMAC_DESCR,                 // Overridden by cyhal_dma_cfg_t.action
    .triggerOutType = CY_DMAC_DESCR_CHAIN,          // Overridden by [en/dis]able_output()
    .channelState = CY_DMAC_CHANNEL_ENABLED,
    .triggerInType = CY_DMAC_DESCR,                 // Overridden by cyhal_dma_cfg_t.action & [dis]connect_digital()
    .dataPrefetch = false,
    .descriptorType = CY_DMAC_1D_TRANSFER,          // Overriden by cyhal_dma_cfg_t.burst_size
    .srcXincrement = 1U,                            // Overriden by cyhal_dma_cfg_t.src_increment
    .dstXincrement = 1U,                            // Overriden by cyhal_dma_cfg_t.dst_increment
    .xCount = 1UL,                                  // Overriden by cyhal_dma_cfg_t.length/burst_size
    .srcYincrement = 0U,                            // Overriden by cyhal_dma_cfg_t.burst_size
    .dstYincrement = 0U,                            // Overriden by cyhal_dma_cfg_t.burst_size
    .yCount = 1UL,                                  // Overriden by cyhal_dma_cfg_t.length
    .nextDescriptor = 0,
#elif defined(CY_IP_M0S8CPUSSV3_DMAC)
    .dataSize = CY_DMAC_WORD,                       // Overridden by cyhal_dma_cfg_t.transfer_width
    .dstTransferSize = CY_DMAC_TRANSFER_SIZE_DATA,  // Overriden by direction
    .srcTransferSize = CY_DMAC_TRANSFER_SIZE_DATA,  // Overriden by direction
    .retrigger = CY_DMAC_RETRIG_IM,
    .triggerType = CY_DMAC_SINGLE_DESCR,
    .dataCount = 1,                                 // Overriden by cyhal_dma_cfg_t.length
    .dstAddrIncrement = true,                       // Overriden by cyhal_dma_cfg_t.dst_increment
    .srcAddrIncrement = true,                       // Overriden by cyhal_dma_cfg_t.src_increment
    .interrupt = true,
    .preemptable = true,
    .flipping = false,
#elif defined(CY_IP_MXSAXIDMAC)
    .interruptType = CY_AXIDMAC_DESCR,              // Overridden by cyhal_dma_cfg_t.action
    .triggerOutType = CY_AXIDMAC_DESCR_CHAIN,       // Overridden by [en/dis]able_output()
    .channelState = CY_AXIDMAC_CHANNEL_ENABLED,
    .triggerInType = CY_AXIDMAC_DESCR,              // Overridden by cyhal_dma_cfg_t.action & [dis]connect_digital()
    .dataPrefetch = false,
    .descriptorType = CY_AXIDMAC_1D_MEMCOPY_COPY,   // Overriden by cyhal_dma_cfg_t.burst_size
    .srcXincrement = 1U,                            // Overriden by cyhal_dma_cfg_t.src_increment
    .dstXincrement = 1U,                            // Overriden by cyhal_dma_cfg_t.dst_increment
    .xCount = 1UL,                                  // Overriden by cyhal_dma_cfg_t.length/burst_size
    .srcYincrement = 0U,                            // Overriden by cyhal_dma_cfg_t.burst_size
    .dstYincrement = 0U,                            // Overriden by cyhal_dma_cfg_t.burst_size
    .yCount = 1UL,                                  // Overriden by cyhal_dma_cfg_t.length
    .nextDescriptor = 0,
#endif
};

/** Default dmac channel config */
#if defined(CY_IP_MXSAXIDMAC)
static const cy_stc_axidmac_channel_config_t _cyhal_dma_dmac_default_channel_config =
#else
static const cy_stc_dmac_channel_config_t _cyhal_dma_dmac_default_channel_config =
#endif
{
    .priority = 1,                          // Overriden by config().priority
    .enable = false,
#if defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_MXAHBDMAC)
    .bufferable = false,
    .descriptor = 0,                        // Overriden by config()
#elif defined(CY_IP_M0S8CPUSSV3_DMAC)
    .descriptor = CY_DMAC_DESCRIPTOR_PING,  // Overriden by config()
#elif defined(CY_IP_MXSAXIDMAC)
    .bufferable = false,
#endif
};

static bool _cyhal_dma_dmac_pm_callback(cyhal_syspm_callback_state_t state, cyhal_syspm_callback_mode_t mode, void* callback_arg);

static cyhal_syspm_callback_data_t _cyhal_dma_dmac_pm_callback_args = {
    .callback = &_cyhal_dma_dmac_pm_callback,
    .states = (cyhal_syspm_callback_state_t)(CYHAL_SYSPM_CB_CPU_DEEPSLEEP | CYHAL_SYSPM_CB_SYSTEM_HIBERNATE),
    .next = NULL,
    .args = NULL,
    .ignore_modes = (cyhal_syspm_callback_mode_t)(CYHAL_SYSPM_BEFORE_TRANSITION | CYHAL_SYSPM_AFTER_DS_WFI_TRANSITION),
};
static bool _cyhal_dma_dmac_pm_transition_pending = false;
static bool _cyhal_dma_dmac_has_enabled(void)
{
    for (uint8_t i = 0; i < NUM_DMAC_CHANNELS; i++)
        if (NULL != _cyhal_dma_dmac_config_structs[i])
            return true;
    return false;
}

static bool _cyhal_dma_dmac_pm_callback(cyhal_syspm_callback_state_t state, cyhal_syspm_callback_mode_t mode, void* callback_arg)
{
    CY_UNUSED_PARAMETER(state);
    CY_UNUSED_PARAMETER(callback_arg);
    bool block_transition = false;
    switch(mode)
    {
        case CYHAL_SYSPM_CHECK_READY:
            for (uint8_t i = 0; (i < NUM_DMAC_CHANNELS) && !block_transition; i++)
            {
                block_transition |= (_cyhal_dma_dmac_config_structs[i] != NULL) && _cyhal_dma_dmac_is_busy(_cyhal_dma_dmac_config_structs[i]);
            }
            _cyhal_dma_dmac_pm_transition_pending = !block_transition;
            break;
        case CYHAL_SYSPM_CHECK_FAIL:
        case CYHAL_SYSPM_AFTER_TRANSITION:
            _cyhal_dma_dmac_pm_transition_pending = false;
            break;
        default:
            CY_ASSERT(false);
            break;
    }
    return _cyhal_dma_dmac_pm_transition_pending;
}

/** Gets the dmac configuration struct offset */
static inline uint8_t _cyhal_dma_dmac_get_cfg_offset(const cyhal_dma_t* obj)
{
    return (obj->resource.block_num * NUM_DMAC0_CHANNELS) + obj->resource.channel_num;
}

/** Sets the dmac configuration struct */
static inline void _cyhal_dma_dmac_set_obj(cyhal_dma_t *obj)
{
    _cyhal_dma_dmac_config_structs[_cyhal_dma_dmac_get_cfg_offset(obj)] = obj;
}

/** Zeros the dmac configuration struct */
static inline void _cyhal_dma_dmac_free_obj(cyhal_dma_t *obj)
{
    _cyhal_dma_dmac_config_structs[_cyhal_dma_dmac_get_cfg_offset(obj)] = NULL;
}

/** Gets the dmac configuration struct from block and channel */
static inline cyhal_dma_t* _cyhal_dma_dmac_get_obj(uint8_t block, uint8_t channel)
{
#if defined(CY_IP_MXSAXIDMAC)
    return _cyhal_dma_dmac_config_structs[(block * APPCPUSS_AXIDMAC0_CH_NR) + channel];
#else
    return _cyhal_dma_dmac_config_structs[(block * CPUSS_DMAC0_CH_NR) + channel];
#endif
}

/** Gets the dmac block number from irq number */
/** This should never be called from a non-dma IRQn */
static inline uint8_t _cyhal_dma_dmac_get_block_from_irqn(_cyhal_system_irq_t irqn)
{
    uint8_t diff = irqn - DMAC0_IRQn;
    CY_ASSERT(diff < NUM_DMAC_CHANNELS);
    if (diff < NUM_DMAC0_CHANNELS)
        return 0;
#if (NUM_DMAC0_CHANNELS < NUM_DMAC_CHANNELS)
    if (diff < NUM_DMAC_CHANNELS)
        return 1;
#endif
    else
    {
        // Should never reach here. Just silencing compiler warnings.
        CY_ASSERT(false);
        return 0xFF;
    }
}

#if defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_MXAHBDMAC) || defined(CY_IP_MXSAXIDMAC)
/** Gets the dmac channel number from irq number */
/** This should never be called from a non-dma IRQn */
static inline uint8_t _cyhal_dma_dmac_get_channel_from_irqn(_cyhal_system_irq_t irqn)
{
    uint8_t diff = irqn - DMAC0_IRQn;
    CY_ASSERT(diff < NUM_DMAC_CHANNELS);
    if (diff < NUM_DMAC0_CHANNELS)
        return diff;
#if (NUM_DMAC0_CHANNELS < NUM_DMAC_CHANNELS)
    else
        return diff - NUM_DMAC0_CHANNELS;
#endif
    // Should never reach here. Just silencing compiler warnings.
    CY_ASSERT(false);
    return 0xFF;
}
#endif

/** Gets the irqn corresponding to a particular cyhal_dma_t config struct */
static inline _cyhal_system_irq_t _cyhal_dma_dmac_get_irqn(cyhal_dma_t *obj)
{
    #if defined(CY_IP_M0S8CPUSSV3_DMAC)
        CY_UNUSED_PARAMETER(obj);
        /* This IP has a single ganged IRQ for all DMA channels */
        return DMAC0_IRQn;
    #else
        return (_cyhal_system_irq_t)((uint8_t)DMAC0_IRQn + _cyhal_dma_dmac_get_cfg_offset(obj));
    #endif
}

/** Gets the dmac base pointer from block number */
static inline cyhal_dmac_hw_type* _cyhal_dma_dmac_get_base(uint8_t block_num)
{
#if defined(CY_IP_MXSAXIDMAC)
    CY_UNUSED_PARAMETER(block_num);
    return SAXI_DMAC;
#elif defined(CPUSS_DMAC0_CH_NR) && !defined(CPUSS_DMAC1_CH_NR)
    CY_UNUSED_PARAMETER(block_num);
    return DMAC;
#elif defined(CPUSS_DMAC0_CH_NR) && defined(CPUSS_DMAC1_CH_NR)
    return (block_num == 0) ? MXAHBDMAC0 : MXAHBDMAC1;
#else
    //Should never get here
    #error "Error: No corresponding base type"
#endif
}

/** Uses tables provided as part of the hal interconnect driver to determine mux
 * trigger group and mux trigger index and then construct the trigger line
 * input parameter to Cy_TrigMux_SwTrigger. */
static inline uint32_t _cyhal_dma_dmac_get_trigger_line(uint8_t block_num, uint8_t channel_num)
{
    /* cyhal_dest_t triggers are guaranteed to be sorted by trigger type, block
     * num, then channel num, therefore, we can just directly find the proper
     * trigger by calculating an offset. */
#if defined(CY_IP_MXSAXIDMAC)
    cyhal_dest_t trigger = (cyhal_dest_t)(CYHAL_TRIGGER_M55APPCPUSS_AXIDMAC_TR_IN0 + (block_num * APPCPUSS_AXIDMAC0_CH_NR) + channel_num);
#else
    cyhal_dest_t trigger = (cyhal_dest_t)(CYHAL_TRIGGER_CPUSS_DMAC0_TR_IN0 + (block_num * CPUSS_DMAC0_CH_NR) + channel_num);
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
#if defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_MXAHBDMAC) || defined(CY_IP_MXSAXIDMAC)
    return PERI_TR_CMD_OUT_SEL_Msk | ((uint32_t)trig_group << 8) | cyhal_mux_dest_index[trigger];
#elif defined(CY_IP_M0S8CPUSSV3_DMAC)
    return PERI_TR_CTL_TR_OUT_Msk | ((uint32_t)trig_group << 8) | cyhal_mux_dest_index[trigger];
#endif
}

#if defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_MXAHBDMAC) || defined(CY_IP_MXSAXIDMAC)
/** Convert PDL interrupt cause to hal dma event */
static inline cyhal_dma_event_t _cyhal_dma_dmac_convert_interrupt_cause(cyhal_dma_t *obj, uint32_t cause)
{
    static const cyhal_dma_event_t hal[] =
    {
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
    for (uint8_t i = 0; cause > 0 && i < sizeof(hal)/sizeof(cyhal_dma_event_t); i++)
    {
        if ((cause & (1 << i)) > 0)
        hal_rslt |= hal[i];
    }

    if ((uint32_t)(hal_rslt & CYHAL_DMA_TRANSFER_COMPLETE) > 0 && obj->expected_bursts > 0)
    {
        obj->expected_bursts--;
        if (0 == obj->expected_bursts)
        {
            hal_rslt |= CYHAL_DMA_DESCRIPTOR_COMPLETE;
#if defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_MXAHBDMAC) || defined(CY_IP_MXSAXIDMAC)
            obj->expected_bursts = (GET_RESOURCE_DATA(obj->descriptor_config).interruptType == _CYHAL_DMAC_X_LOOP)
                ? GET_RESOURCE_DATA(obj->descriptor_config).yCount
                : 1;
#else
            obj->expected_bursts = 1;
#endif
        }
    }

    return hal_rslt;
}
#endif

/** DMAC irq handler */
static void _cyhal_dma_dmac_irq_handler(void)
{
    /* Use irqn to get appropriate config structure */
    _cyhal_system_irq_t irqn = _cyhal_irq_get_active();
    uint8_t block = _cyhal_dma_dmac_get_block_from_irqn(irqn);
#if defined(CY_IP_MXSAXIDMAC)
    SAXI_DMAC_Type* base = _cyhal_dma_dmac_get_base(block);
#else
    DMAC_Type* base = _cyhal_dma_dmac_get_base(block);
#endif
#if defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_MXAHBDMAC) || defined(CY_IP_MXSAXIDMAC)
    uint8_t channel = _cyhal_dma_dmac_get_channel_from_irqn(irqn);
    cyhal_dma_t *obj = _cyhal_dma_dmac_get_obj(block, channel);

    /* Get interrupt type and call users event callback if they have enabled that event */
    uint32_t cause = _cyhal_dmac_channel_get_interrupt_status_masked(base, channel);
    cyhal_dma_event_t event_type = _cyhal_dma_dmac_convert_interrupt_cause(obj, cause);
    uint32_t events_to_callback = event_type & obj->irq_cause;
    if(obj->callback_data.callback != NULL && events_to_callback)
    {
        ((cyhal_dma_event_callback_t)obj->callback_data.callback)(obj->callback_data.callback_arg, (cyhal_dma_event_t)events_to_callback);
    }

    /* Clear all interrupts */
#if defined(CY_IP_MXSAXIDMAC)
    Cy_AXIDMAC_Channel_ClearInterrupt(base, channel, CY_AXIDMAC_INTR_MASK);
#else
    Cy_DMAC_Channel_ClearInterrupt(base, channel, CY_DMAC_INTR_MASK);
#endif
#elif defined(CY_IP_M0S8CPUSSV3_DMAC)
    uint32_t channels = Cy_DMAC_GetInterruptStatusMasked(base);
    for(int i = 0 ; ((uint32_t)(1 << i)) <= channels ; i++)
    {
        cyhal_dma_t *obj = _cyhal_dma_dmac_get_obj(block, i);
        if (obj != NULL)
        {
            if (((channels & (1 << i)) != 0) && (obj->callback_data.callback != NULL))
            {
                ((cyhal_dma_event_callback_t)obj->callback_data.callback)(obj->callback_data.callback_arg, CYHAL_DMA_TRANSFER_COMPLETE);
            }
        }
    }
    Cy_DMAC_ClearInterrupt(_cyhal_dma_dmac_get_base(block), channels);
#endif
}

static cyhal_source_t _cyhal_dma_dmac_get_src(uint8_t block_num, uint8_t channel_num)
{
#if defined(CY_IP_MXSAXIDMAC)
    return (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE((_CYHAL_TRIGGER_M55APPCPUSS_AXIDMAC_TR_OUT0 + (block_num * APPCPUSS_AXIDMAC0_CH_NR) + channel_num), CYHAL_SIGNAL_TYPE_EDGE);
#else
    return (cyhal_source_t)_CYHAL_TRIGGER_CREATE_SOURCE((_CYHAL_TRIGGER_CPUSS_DMAC0_TR_OUT0 + (block_num * CPUSS_DMAC0_CH_NR) + channel_num), CYHAL_SIGNAL_TYPE_EDGE);
#endif
}

static cyhal_dest_t _cyhal_dma_dmac_get_dest(uint8_t block_num, uint8_t channel_num)
{
#if defined(CY_IP_MXSAXIDMAC)
    return (cyhal_dest_t)(CYHAL_TRIGGER_M55APPCPUSS_AXIDMAC_TR_IN0 + (block_num * APPCPUSS_AXIDMAC0_CH_NR) + channel_num);
#else
    return (cyhal_dest_t)(CYHAL_TRIGGER_CPUSS_DMAC0_TR_IN0 + (block_num * CPUSS_DMAC0_CH_NR) + channel_num);
#endif
}

static cy_rslt_t _cyhal_dma_dmac_stage(cyhal_dma_t *obj)
{
    cyhal_dmac_hw_type* base = _cyhal_dma_dmac_get_base(obj->resource.block_num);
#if defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_MXAHBDMAC) || defined(CY_IP_MXSAXIDMAC)
    #if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    SCB_CleanDCache_by_Addr((void *)&(obj->descriptor), sizeof(obj->descriptor));
    #endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
#if defined(CY_IP_MXSAXIDMAC)
    cy_rslt_t rslt = Cy_AXIDMAC_Descriptor_Init(GET_RESOURCE_DATA(&obj->descriptor), GET_RESOURCE_DATA(&obj->descriptor_config));
#else
    cy_rslt_t rslt = Cy_DMAC_Descriptor_Init(GET_RESOURCE_DATA(&obj->descriptor), GET_RESOURCE_DATA(&obj->descriptor_config));
#endif
#elif defined(CY_IP_M0S8CPUSSV3_DMAC)
    cy_rslt_t rslt = Cy_DMAC_Descriptor_Init(base, obj->resource.channel_num, obj->descriptor, GET_RESOURCE_DATA(&obj->descriptor_config));
#endif
#if defined(CY_IP_MXSAXIDMAC)
    if(CY_AXIDMAC_SUCCESS != rslt)
#else
    if(CY_DMAC_SUCCESS != rslt)
#endif
        return CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER;

    /* Setup channel and enable */
    #if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    SCB_CleanDCache_by_Addr((void *)&(obj->channel_config), sizeof(obj->channel_config));
    #endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
#if defined(CY_IP_MXSAXIDMAC)
    if(CY_AXIDMAC_SUCCESS != Cy_AXIDMAC_Channel_Init(base, obj->resource.channel_num, GET_RESOURCE_DATA(&obj->channel_config)))
#else
    if(CY_DMAC_SUCCESS != Cy_DMAC_Channel_Init(base, obj->resource.channel_num, GET_RESOURCE_DATA(&obj->channel_config)))
#endif
        return CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER;

#if defined(CY_IP_MXSAXIDMAC)
    Cy_AXIDMAC_Channel_SetInterruptMask(base, obj->resource.channel_num, CY_AXIDMAC_INTR_MASK);
#elif defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_MXAHBDMAC)
    Cy_DMAC_Channel_SetInterruptMask(base, obj->resource.channel_num, CY_DMAC_INTR_MASK);
#endif
#if defined(CY_IP_MXSAXIDMAC)
    Cy_AXIDMAC_Enable(base);
#else
    Cy_DMAC_Enable(base);
#endif

#if defined(CY_IP_MXSAXIDMAC)
    /* src_misal and dst_misal interrupts are triggered immediately on enable
     * so return those errors here */
    uint32_t status = Cy_AXIDMAC_Channel_GetInterruptStatus(base, obj->resource.channel_num);
    if((status & CY_AXIDMAC_INTR_INVALID_DESCR_TYPE))
    {
        /* Clear all interrupts and return error */
        Cy_AXIDMAC_Channel_ClearInterrupt(base, obj->resource.channel_num, CY_AXIDMAC_INTR_MASK);
        return CYHAL_DMA_RSLT_ERR_INVALID_ALIGNMENT;
    }
#elif defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_MXAHBDMAC)
    /* src_misal and dst_misal interrupts are triggered immediately on enable
     * so return those errors here */
    uint32_t status = Cy_DMAC_Channel_GetInterruptStatus(base, obj->resource.channel_num);
    if((status & CY_DMAC_INTR_SRC_MISAL) ||
       (status & CY_DMAC_INTR_DST_MISAL))
    {
        /* Clear all interrupts and return error */
        Cy_DMAC_Channel_ClearInterrupt(base, obj->resource.channel_num, CY_DMAC_INTR_MASK);
        return CYHAL_DMA_RSLT_ERR_INVALID_ALIGNMENT;
    }
#endif

    /* Enable interrupt for this channel; preserve user priority if they enabled an interrupt */
    _cyhal_system_irq_t irqn = _cyhal_dma_dmac_get_irqn(obj);
    uint32_t priority = (CYHAL_DMA_NO_INTR == obj->irq_cause)
        ? CYHAL_ISR_PRIORITY_DEFAULT
        : _cyhal_irq_get_priority(irqn);

    if(CY_RSLT_SUCCESS != _cyhal_irq_register(irqn, priority, _cyhal_dma_dmac_irq_handler))
        return CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER;
    _cyhal_irq_enable(irqn);

    return CY_RSLT_SUCCESS;
}

cy_rslt_t _cyhal_dma_dmac_init(cyhal_dma_t *obj, cyhal_source_t *src, cyhal_dest_t *dest, uint8_t priority)
{
#if defined(CY_IP_MXSAXIDMAC)
    if(!CY_AXIDMAC_IS_PRIORITY_VALID(priority))
#else
    if(!CY_DMAC_IS_PRIORITY_VALID(priority))
#endif
        return CYHAL_DMA_RSLT_ERR_INVALID_PRIORITY;

    if (_cyhal_dma_dmac_pm_transition_pending)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }

    cy_rslt_t rslt = _cyhal_hwmgr_allocate_with_connection(
        CYHAL_RSC_DMA, src, dest, _cyhal_dma_dmac_get_src, _cyhal_dma_dmac_get_dest, &obj->resource);
    if(rslt != CY_RSLT_SUCCESS)
        return rslt;

    obj->callback_data.callback = NULL;

    /* Setup descriptor and channel configs */
    GET_RESOURCE_DATA(obj->descriptor_config) = _cyhal_dma_dmac_default_descriptor_config;
    GET_RESOURCE_DATA(obj->channel_config) = _cyhal_dma_dmac_default_channel_config;
#if defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_MXAHBDMAC) || defined(CY_IP_MXSAXIDMAC)
    GET_RESOURCE_DATA(obj->channel_config).descriptor = GET_RESOURCE_DATA(&obj->descriptor);
#elif defined(CY_IP_M0S8CPUSSV3_DMAC)
    obj->descriptor = obj->channel_config.descriptor;
#endif
    GET_RESOURCE_DATA(obj->channel_config).priority = priority;

#if CYHAL_DRIVER_AVAILABLE_SYSPM
    if (!_cyhal_dma_dmac_has_enabled())
    {
        _cyhal_syspm_register_peripheral_callback(&_cyhal_dma_dmac_pm_callback_args);
    }
#endif

    _cyhal_dma_dmac_set_obj(obj);

    return CY_RSLT_SUCCESS;
}

cy_rslt_t _cyhal_dma_dmac_init_cfg(cyhal_dma_t *obj, const cyhal_dma_configurator_t *cfg)
{
    if (_cyhal_dma_dmac_pm_transition_pending)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }

    obj->resource = *(cfg->resource);
    obj->callback_data.callback = NULL;

    /* Setup descriptor and channel configs */
#if defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_MXAHBDMAC) || defined(CY_IP_MXSAXIDMAC)
    obj->descriptor_config.dmac = *(cfg->dmac_descriptor_config);
    obj->channel_config.dmac = *(cfg->dmac_channel_config);
    GET_RESOURCE_DATA(obj->channel_config).descriptor = GET_RESOURCE_DATA(&obj->descriptor);
    obj->expected_bursts = cfg->dmac_descriptor_config->yCount;
#elif defined(CY_IP_M0S8CPUSSV3_DMAC)
    obj->descriptor_config = *(cfg->descriptor_config);
    obj->channel_config = *(cfg->channel_config);
    obj->descriptor = obj->channel_config.descriptor;
    obj->expected_bursts = 1;
#endif

#if CYHAL_DRIVER_AVAILABLE_SYSPM
    if (!_cyhal_dma_dmac_has_enabled())
    {
        _cyhal_syspm_register_peripheral_callback(&_cyhal_dma_dmac_pm_callback_args);
    }
#endif

    _cyhal_dma_dmac_set_obj(obj);

    return _cyhal_dma_dmac_stage(obj);
}

void _cyhal_dma_dmac_free(cyhal_dma_t *obj)
{
    cyhal_dmac_hw_type* base = _cyhal_dma_dmac_get_base(obj->resource.block_num);
#if defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_MXAHBDMAC)
    Cy_DMAC_Descriptor_DeInit(GET_RESOURCE_DATA(&obj->descriptor));
    Cy_DMAC_Channel_DeInit(base, obj->resource.channel_num);
#elif defined(CY_IP_M0S8CPUSSV3_DMAC)
    Cy_DMAC_Descriptor_DeInit(base, obj->resource.channel_num, obj->descriptor);
    Cy_DMAC_Channel_DeInit(base, obj->resource.channel_num);
#elif defined(CY_IP_MXSAXIDMAC)
    Cy_AXIDMAC_Descriptor_DeInit(GET_RESOURCE_DATA(&obj->descriptor));
    Cy_AXIDMAC_Channel_DeInit(base, obj->resource.channel_num);
#endif

    _cyhal_irq_free(_cyhal_dma_dmac_get_irqn(obj));

    _cyhal_dma_dmac_free_obj(obj);

#if CYHAL_DRIVER_AVAILABLE_SYSPM
    if (!_cyhal_dma_dmac_has_enabled())
    {
        _cyhal_syspm_unregister_peripheral_callback(&_cyhal_dma_dmac_pm_callback_args);
        _cyhal_dma_dmac_pm_transition_pending = false;
    }
#endif
}

/* Initialize descriptor, initialize channel, enable channel, enable channel
 * interrupt, and enable DMAC controller */
cy_rslt_t _cyhal_dma_dmac_configure(cyhal_dma_t *obj, const cyhal_dma_cfg_t *cfg)
{
    /* Do not reconfigure if transfer is pending/active already */
    if(_cyhal_dma_dmac_is_busy(obj))
        return CYHAL_DMA_RSLT_ERR_CHANNEL_BUSY;

    // DMAC only supports <=65536 byte burst and <=65536 bytes per burst
    if ((cfg->burst_size > 65536) ||
        ((cfg->burst_size <= 1) && (cfg->length > 65536)) ||
        ((cfg->burst_size > 0) && (cfg->length > (cfg->burst_size * 65536))))
        return CYHAL_DMA_RSLT_ERR_INVALID_TRANSFER_SIZE;

#if defined(CY_IP_M0S8CPUSSV3_DMAC)
    // PSoCâ„¢ 4 devices do not support automatically disabling the channel on completion
    if ((cfg->action == CYHAL_DMA_TRANSFER_BURST_DISABLE) ||
        (cfg->action == CYHAL_DMA_TRANSFER_FULL_DISABLE))
    {
        return CYHAL_DMA_RSLT_FATAL_UNSUPPORTED_HARDWARE;
    }
#endif

    #if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    SCB_CleanDCache_by_Addr((void *)cfg->src_addr, cfg->length * (cfg->transfer_width / 8));
    SCB_CleanDCache_by_Addr((void *)cfg->dst_addr, cfg->length * (cfg->transfer_width / 8));
    #endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
    GET_RESOURCE_DATA(obj->descriptor_config).srcAddress = (void*)cfg->src_addr;
    GET_RESOURCE_DATA(obj->descriptor_config).dstAddress = (void*)cfg->dst_addr;

#if !defined(CY_IP_MXSAXIDMAC)
    if(cfg->transfer_width == 8)
        GET_RESOURCE_DATA(obj->descriptor_config).dataSize = CY_DMAC_BYTE;
    else if(cfg->transfer_width == 16)
        GET_RESOURCE_DATA(obj->descriptor_config).dataSize = CY_DMAC_HALFWORD;
    else if(cfg->transfer_width == 32)
        GET_RESOURCE_DATA(obj->descriptor_config).dataSize = CY_DMAC_WORD;
    else
        return CYHAL_DMA_RSLT_ERR_INVALID_TRANSFER_WIDTH;

    /* By default, transfer what the user set for dataSize. However, if transfering between memory
     * and a peripheral, make sure the peripheral access is using words. */
    GET_RESOURCE_DATA(obj->descriptor_config).srcTransferSize =
        GET_RESOURCE_DATA(obj->descriptor_config).dstTransferSize = CY_DMAC_TRANSFER_SIZE_DATA;
    if (obj->direction == CYHAL_DMA_DIRECTION_PERIPH2MEM)
        GET_RESOURCE_DATA(obj->descriptor_config).srcTransferSize = CY_DMAC_TRANSFER_SIZE_WORD;
    else if (obj->direction == CYHAL_DMA_DIRECTION_MEM2PERIPH)
        GET_RESOURCE_DATA(obj->descriptor_config).dstTransferSize = CY_DMAC_TRANSFER_SIZE_WORD;
#endif
#if defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_MXAHBDMAC) || defined(CY_IP_MXSAXIDMAC)
    GET_RESOURCE_DATA(obj->descriptor_config).nextDescriptor = GET_RESOURCE_DATA(&obj->descriptor);
    if ((cfg->action == CYHAL_DMA_TRANSFER_BURST) || (cfg->action == CYHAL_DMA_TRANSFER_FULL))
    {
        GET_RESOURCE_DATA(obj->descriptor_config).channelState = _CYHAL_DMAC_CHANNEL_ENABLED;
    }
    else
    {
        GET_RESOURCE_DATA(obj->descriptor_config).channelState = _CYHAL_DMAC_CHANNEL_DISABLED;
    }

    GET_RESOURCE_DATA(obj->descriptor_config).srcXincrement = cfg->src_increment;
    GET_RESOURCE_DATA(obj->descriptor_config).dstXincrement = cfg->dst_increment;

    /* Setup 2D transfer if burst_size is being used otherwise set up 1D
     * transfer */
    if(cfg->burst_size != 0)
    {
        /* Length must be a multiple of burst_size */
        if(cfg->length % cfg->burst_size != 0)
            return CYHAL_DMA_RSLT_ERR_INVALID_BURST_SIZE;

#if defined(CY_IP_MXSAXIDMAC)
        GET_RESOURCE_DATA(obj->descriptor_config).descriptorType = CY_AXIDMAC_2D_MEMCOPY_COPY;
#else
        GET_RESOURCE_DATA(obj->descriptor_config).descriptorType = CY_DMAC_2D_TRANSFER;
#endif
        GET_RESOURCE_DATA(obj->descriptor_config).xCount = cfg->burst_size;
        GET_RESOURCE_DATA(obj->descriptor_config).yCount = cfg->length / cfg->burst_size;
        GET_RESOURCE_DATA(obj->descriptor_config).srcYincrement = cfg->src_increment * cfg->burst_size;
        GET_RESOURCE_DATA(obj->descriptor_config).dstYincrement = cfg->dst_increment * cfg->burst_size;
    }
    else
    {
#if defined(CY_IP_MXSAXIDMAC)
        GET_RESOURCE_DATA(obj->descriptor_config).descriptorType = CY_AXIDMAC_1D_MEMCOPY_COPY;
#else
        GET_RESOURCE_DATA(obj->descriptor_config).descriptorType = CY_DMAC_1D_TRANSFER;
#endif
        GET_RESOURCE_DATA(obj->descriptor_config).xCount = cfg->length;
    }

    /* If burst action, configure trigger and interrupt actions */
    if (cfg->burst_size != 0 &&
        (cfg->action == CYHAL_DMA_TRANSFER_BURST || cfg->action == CYHAL_DMA_TRANSFER_BURST_DISABLE))
    {
        obj->expected_bursts = GET_RESOURCE_DATA(obj->descriptor_config).yCount;
        GET_RESOURCE_DATA(obj->descriptor_config).interruptType = _CYHAL_DMAC_X_LOOP;
        if (obj->source == _CYHAL_TRIGGER_CPUSS_ZERO) // If not overridden by connect_digital()
            GET_RESOURCE_DATA(obj->descriptor_config).triggerInType = _CYHAL_DMAC_X_LOOP;
    }
    else
    {
        obj->expected_bursts = 1;
        GET_RESOURCE_DATA(obj->descriptor_config).interruptType = _CYHAL_DMAC_DESCR;
        if (obj->source == _CYHAL_TRIGGER_CPUSS_ZERO) // If not overridden by connect_digital()
            GET_RESOURCE_DATA(obj->descriptor_config).triggerInType = _CYHAL_DMAC_DESCR;
     }
#elif defined(CY_IP_M0S8CPUSSV3_DMAC)
    if(cfg->burst_size != 0)
    {
        return CYHAL_DMA_RSLT_ERR_INVALID_BURST_SIZE;
    }
    else
    {
        GET_RESOURCE_DATA(obj->descriptor_config).dataCount = cfg->length;
        GET_RESOURCE_DATA(obj->descriptor_config).srcAddrIncrement = cfg->src_increment;
        GET_RESOURCE_DATA(obj->descriptor_config).dstAddrIncrement = cfg->dst_increment;
        obj->expected_bursts = 1;
    }
#endif

    return _cyhal_dma_dmac_stage(obj);
}

cy_rslt_t _cyhal_dma_dmac_enable(cyhal_dma_t *obj)
{
    cyhal_dmac_hw_type* base = _cyhal_dma_dmac_get_base(obj->resource.block_num);
    _cyhal_dmac_channel_enable(base, obj->resource.channel_num);
    return CY_RSLT_SUCCESS;
}

cy_rslt_t _cyhal_dma_dmac_disable(cyhal_dma_t *obj)
{
    cyhal_dmac_hw_type* base = _cyhal_dma_dmac_get_base(obj->resource.block_num);
    _cyhal_dmac_channel_disable(base, obj->resource.channel_num);
    return CY_RSLT_SUCCESS;
}

cy_rslt_t _cyhal_dma_dmac_start_transfer(cyhal_dma_t *obj)
{
    /* Return warning if channel is busy */
    if(_cyhal_dma_dmac_is_busy(obj))
        return CYHAL_DMA_RSLT_WARN_TRANSFER_ALREADY_STARTED;

    if (_cyhal_dma_dmac_pm_transition_pending)
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;

    uint32_t trigline = _cyhal_dma_dmac_get_trigger_line(obj->resource.block_num, obj->resource.channel_num);
    cy_en_trigmux_status_t trig_status = Cy_TrigMux_SwTrigger(trigline, CY_TRIGGER_TWO_CYCLES);

    /* Also return warning if SW trigger is already initiated but DMA hardware
     * has not seen it yet */
    if(trig_status == CY_TRIGMUX_INVALID_STATE)
        return CYHAL_DMA_RSLT_WARN_TRANSFER_ALREADY_STARTED;
    else
        return CY_RSLT_SUCCESS;
}

void _cyhal_dma_dmac_enable_event(cyhal_dma_t *obj, cyhal_dma_event_t event, uint8_t intr_priority, bool enable)
{
#if defined (CY_IP_M0S8CPUSSV3_DMAC)
    DMAC_Type *base = _cyhal_dma_dmac_get_base(obj->resource.block_num);
    uint32_t mask = Cy_DMAC_GetInterruptMask(base);
#endif
    if(enable)
    {
#if defined (CY_IP_M0S8CPUSSV3_DMAC)
        Cy_DMAC_SetInterruptMask(base, mask | (1 << obj->resource.channel_num));
#endif
        obj->irq_cause |= event;
    }
    else
    {
#if defined (CY_IP_M0S8CPUSSV3_DMAC)
        Cy_DMAC_SetInterruptMask(base, mask & ~(1 << obj->resource.channel_num));
#endif
        obj->irq_cause &= ~event;
    }

    _cyhal_irq_set_priority(_cyhal_dma_dmac_get_irqn(obj), intr_priority);
}

bool _cyhal_dma_dmac_is_busy(cyhal_dma_t *obj)
{
    /* The value is a bit field of all pending or active channels */
    return _cyhal_dmac_get_active_channel(_cyhal_dma_dmac_get_base(obj->resource.block_num)) & (1 << obj->resource.channel_num);
}
#if defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_MXAHBDMAC) || defined(CY_IP_MXSAXIDMAC)
#if defined(CY_IP_MXSAXIDMAC)
static cy_en_axidmac_trigger_type_t _cyhal_convert_input_t(cyhal_dma_input_t input)
{
    switch(input)
    {
        case CYHAL_DMA_INPUT_TRIGGER_SINGLE_ELEMENT:
            return CY_AXIDMAC_M_LOOP;
        case CYHAL_DMA_INPUT_TRIGGER_SINGLE_BURST:
            return CY_AXIDMAC_X_LOOP;
        case CYHAL_DMA_INPUT_TRIGGER_ALL_ELEMENTS:
            return CY_AXIDMAC_DESCR;
        default:
            // Should never reach here. Just silencing compiler warnings.
            CY_ASSERT(false);
            return CY_AXIDMAC_DESCR;
    }
}
#elif defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_MXAHBDMAC)
static cy_en_dmac_trigger_type_t _cyhal_convert_input_t(cyhal_dma_input_t input)
{
    switch(input)
    {
        case CYHAL_DMA_INPUT_TRIGGER_SINGLE_ELEMENT:
            return CY_DMAC_1ELEMENT;
        case CYHAL_DMA_INPUT_TRIGGER_SINGLE_BURST:
            return CY_DMAC_X_LOOP;
        case CYHAL_DMA_INPUT_TRIGGER_ALL_ELEMENTS:
            return CY_DMAC_DESCR;
        default:
            // Should never reach here. Just silencing compiler warnings.
            CY_ASSERT(false);
            return CY_DMAC_DESCR;
    }
}
#endif

#if defined(CY_IP_MXSAXIDMAC)
static cy_en_axidmac_trigger_type_t _cyhal_convert_output_t(cyhal_dma_output_t output)
{
    switch(output)
    {
        case CYHAL_DMA_OUTPUT_TRIGGER_SINGLE_ELEMENT:
            return CY_AXIDMAC_M_LOOP;
        case CYHAL_DMA_OUTPUT_TRIGGER_SINGLE_BURST:

            return CY_AXIDMAC_X_LOOP;
        case CYHAL_DMA_OUTPUT_TRIGGER_ALL_ELEMENTS:
            return CY_AXIDMAC_DESCR;
        default:
            // Should never reach here. Just silencing compiler warnings.
            CY_ASSERT(false);
            return CY_AXIDMAC_DESCR;
    }
}
#else
static cy_en_dmac_trigger_type_t _cyhal_convert_output_t(cyhal_dma_output_t output)
{
    switch(output)
    {
        case CYHAL_DMA_OUTPUT_TRIGGER_SINGLE_ELEMENT:
            return CY_DMAC_1ELEMENT;
        case CYHAL_DMA_OUTPUT_TRIGGER_SINGLE_BURST:
            return CY_DMAC_X_LOOP;
        case CYHAL_DMA_OUTPUT_TRIGGER_ALL_ELEMENTS:
            return CY_DMAC_DESCR;
        default:
            // Should never reach here. Just silencing compiler warnings.
            CY_ASSERT(false);
            return CY_DMAC_DESCR;
    }
}
#endif

cy_rslt_t _cyhal_dma_dmac_connect_digital(cyhal_dma_t *obj, cyhal_source_t source, cyhal_dma_input_t input)
{
    if(input != CYHAL_DMA_INPUT_TRIGGER_SINGLE_ELEMENT &&
       input != CYHAL_DMA_INPUT_TRIGGER_SINGLE_BURST &&
       input != CYHAL_DMA_INPUT_TRIGGER_ALL_ELEMENTS)
        return CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER;

    obj->descriptor_config.dmac.triggerInType = _cyhal_convert_input_t(input);

    _cyhal_dmac_channel_disable(_cyhal_dma_dmac_get_base(obj->resource.block_num), obj->resource.channel_num);

    obj->descriptor.dmac.ctl &= ~_CYHAL_DMAC_CH_DESCR_CTL_TR_IN_TYPE_Msk;
    obj->descriptor.dmac.ctl |= _VAL2FLD(_CYHAL_DMAC_CH_DESCR_CTL_TR_IN_TYPE, obj->descriptor_config.dmac.triggerInType);

    _cyhal_dmac_channel_enable(_cyhal_dma_dmac_get_base(obj->resource.block_num), obj->resource.channel_num);

    cyhal_dest_t dest = _cyhal_dma_dmac_get_dest(obj->resource.block_num, obj->resource.channel_num);

    return _cyhal_connect_signal(source, dest);
}

cy_rslt_t _cyhal_dma_dmac_enable_output(cyhal_dma_t *obj, cyhal_dma_output_t output, cyhal_source_t *source)
{
    if(output != CYHAL_DMA_OUTPUT_TRIGGER_SINGLE_ELEMENT &&
       output != CYHAL_DMA_OUTPUT_TRIGGER_SINGLE_BURST &&
       output != CYHAL_DMA_OUTPUT_TRIGGER_ALL_ELEMENTS)
        return CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER;

    _cyhal_dmac_channel_disable(_cyhal_dma_dmac_get_base(obj->resource.block_num), obj->resource.channel_num);

    obj->descriptor.dmac.ctl &= ~_CYHAL_DMAC_CH_DESCR_CTL_TR_OUT_TYPE_Msk;
    obj->descriptor.dmac.ctl |= _VAL2FLD(_CYHAL_DMAC_CH_DESCR_CTL_TR_OUT_TYPE, _cyhal_convert_output_t(output));

    _cyhal_dmac_channel_enable(_cyhal_dma_dmac_get_base(obj->resource.block_num), obj->resource.channel_num);
    *source = _cyhal_dma_dmac_get_src(obj->resource.block_num, obj->resource.channel_num);

    return CY_RSLT_SUCCESS;
}

cy_rslt_t _cyhal_dma_dmac_disconnect_digital(cyhal_dma_t *obj, cyhal_source_t source, cyhal_dma_input_t input)
{
    if(input != CYHAL_DMA_INPUT_TRIGGER_SINGLE_ELEMENT &&
       input != CYHAL_DMA_INPUT_TRIGGER_SINGLE_BURST &&
       input != CYHAL_DMA_INPUT_TRIGGER_ALL_ELEMENTS)
        return CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER;


    // There is no option to totally disable. Just reset to default.
    // NOTE: Use .interruptType since it matches the desired .triggerInType from configure(), but
    // is not modified by connect/disconnect functions
    _cyhal_dmac_channel_disable(_cyhal_dma_dmac_get_base(obj->resource.block_num), obj->resource.channel_num);

    obj->descriptor.dmac.ctl &= ~_CYHAL_DMAC_CH_DESCR_CTL_TR_IN_TYPE_Msk;
    obj->descriptor.dmac.ctl |= _VAL2FLD(_CYHAL_DMAC_CH_DESCR_CTL_TR_IN_TYPE, _cyhal_dma_dmac_default_descriptor_config.interruptType);

    _cyhal_dmac_channel_enable(_cyhal_dma_dmac_get_base(obj->resource.block_num), obj->resource.channel_num);

    cyhal_dest_t dest = _cyhal_dma_dmac_get_dest(obj->resource.block_num, obj->resource.channel_num);

    return _cyhal_disconnect_signal(source, dest);
}

cy_rslt_t _cyhal_dma_dmac_disable_output(cyhal_dma_t *obj, cyhal_dma_output_t output)
{
    if(output != CYHAL_DMA_OUTPUT_TRIGGER_SINGLE_ELEMENT &&
       output != CYHAL_DMA_OUTPUT_TRIGGER_SINGLE_BURST &&
       output != CYHAL_DMA_OUTPUT_TRIGGER_ALL_ELEMENTS)
        return CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER;

    // There is no option to totally disable. Just reset to default.
    _cyhal_dmac_channel_disable(_cyhal_dma_dmac_get_base(obj->resource.block_num), obj->resource.channel_num);

    obj->descriptor.dmac.ctl &= ~_CYHAL_DMAC_CH_DESCR_CTL_TR_OUT_TYPE_Msk;
    obj->descriptor.dmac.ctl |= _VAL2FLD(_CYHAL_DMAC_CH_DESCR_CTL_TR_OUT_TYPE, _cyhal_dma_dmac_default_descriptor_config.triggerOutType);

    _cyhal_dmac_channel_enable(_cyhal_dma_dmac_get_base(obj->resource.block_num), obj->resource.channel_num);

    return CY_RSLT_SUCCESS;

}
#elif defined(CY_IP_M0S8CPUSSV3_DMAC)

cy_rslt_t _cyhal_dma_dmac_connect_digital(cyhal_dma_t *obj, cyhal_source_t source, cyhal_dma_input_t input)
{
    if((input != CYHAL_DMA_INPUT_TRIGGER_SINGLE_ELEMENT) &&
       (input != CYHAL_DMA_INPUT_TRIGGER_ALL_ELEMENTS))
        return CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER;

    Cy_DMAC_Channel_SetCurrentDescriptor(_cyhal_dma_dmac_get_base(obj->resource.block_num), obj->resource.channel_num, obj->descriptor);

    cyhal_dest_t dest = (cyhal_dest_t)(CYHAL_TRIGGER_CPUSS_DMAC0_TR_IN0 + obj->resource.channel_num);


    return _cyhal_connect_signal(source, dest);
}

// M0S8 output triggers are always active. This is a noop except to return the source.
cy_rslt_t _cyhal_dma_dmac_enable_output(cyhal_dma_t *obj, cyhal_dma_output_t output, cyhal_source_t *source)
{
    if((output != CYHAL_DMA_OUTPUT_TRIGGER_SINGLE_ELEMENT) &&
       (output != CYHAL_DMA_OUTPUT_TRIGGER_ALL_ELEMENTS))
        return CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER;

    *source = _cyhal_dma_dmac_get_src(obj->resource.block_num, obj->resource.channel_num);

    return CY_RSLT_SUCCESS;
}

cy_rslt_t _cyhal_dma_dmac_disconnect_digital(cyhal_dma_t *obj, cyhal_source_t source, cyhal_dma_input_t input)
{
    if((input != CYHAL_DMA_INPUT_TRIGGER_SINGLE_ELEMENT) &&
       (input != CYHAL_DMA_INPUT_TRIGGER_ALL_ELEMENTS))
        return CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER;

    // Reset to default
    Cy_DMAC_Channel_SetCurrentDescriptor(_cyhal_dma_dmac_get_base(obj->resource.block_num), obj->resource.channel_num, obj->descriptor);

    cyhal_dest_t dest = (cyhal_dest_t)(CYHAL_TRIGGER_CPUSS_DMAC0_TR_IN0 + obj->resource.channel_num);

    return _cyhal_disconnect_signal(source, dest);
}

// M0S8 output triggers are always active. This is a noop.
cy_rslt_t _cyhal_dma_dmac_disable_output(cyhal_dma_t *obj, cyhal_dma_output_t output)
{
    CY_UNUSED_PARAMETER(obj);

    if((output != CYHAL_DMA_OUTPUT_TRIGGER_SINGLE_ELEMENT) &&
       (output != CYHAL_DMA_OUTPUT_TRIGGER_ALL_ELEMENTS))
        return CYHAL_DMA_RSLT_ERR_INVALID_PARAMETER;

    return CY_RSLT_SUCCESS;
}

#endif /* defined(CY_IP_M4CPUSS_DMAC) || defined(CY_IP_M7CPUSS_DMAC) || defined(CY_IP_MXAHBDMAC) */

#endif /* (_CYHAL_DRIVER_AVAILABLE_DMA_DMAC) */

#if defined(__cplusplus)
}
#endif
