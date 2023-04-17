/*******************************************************************************
* File Name: cyhal_pdmpcm.c
*
* Description:
* Provides a high level interface for interacting with the Infineon I2C. This is
* a wrapper around the lower level PDL API.
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

#include <math.h>
#include <stdlib.h>
#include <string.h> // For memset
#include "cyhal_clock.h"
#include "cyhal_dma.h"
#include "cyhal_gpio.h"
#include "cyhal_hwmgr.h"
#include "cyhal_pdmpcm.h"
#include "cyhal_syspm_impl.h"
#include "cyhal_system.h"
#include "cyhal_utils.h"
#include "cyhal_irq_impl.h"
#include "cy_device.h"
#include "cy_device_headers.h"
#include "cy_utils.h"
#if defined(CY_IP_MXAUDIOSS)
#include "cy_pdm_pcm.h"
#elif defined(CY_IP_MXPDM)
#include "cy_pdm_pcm_v2.h"
#endif

/**
* \addtogroup group_hal_impl_pdmpcm PDM/PCM (Pulse Density Modulation to Pulse Code Modulation Converter)
* \ingroup group_hal_impl
* \{
* The CAT1A PDM/PCM Supports the following conversion parameters:<ul>
* <li>Mode: Mono Left, Mono Right, Stereo
* <li>Word Length: 16/18/20/24 bits</li>
* <li>Sampling Rate: up to 48kHz</li>
* <li>Left/Right Gain Amplifier: -12dB to +10.5dB in 1.5dB steps.</li>
* </ul>
*
* \note If the PDM/PCM block is initialized using the \ref cyhal_pdm_pcm_init function and
* the "channel recording swap" option is selected, the @ref CYHAL_PDM_PCM_MODE_LEFT and
* @ref CYHAL_PDM_PCM_MODE_RIGHT enum members refer to the origin left and right channels
* before the swap is applied.
*
* The CAT1B PDM/PCM Supports the following conversion parameters:<ul>
* <li>Mode: Mono Left, Mono Right, Stereo
* <li>Word Length: 8/10/12/14/16/18/20/24/32 bits</li>
* <li>Sampling Rate: up to 48kHz</li>
* <li>Decimation rates: 32, 64, 96 or 128
* <li>Left/Right Gain Amplifier: Supported gain values are given by the formula
*     `dB = 20 * log10(13921 / 2^x)` where `x` is an integer between 0 and 31 inclusive.
*     This provides a range of +82.5 to -103.5 dB, in approximately 5 dB steps.
*     The requested gain will rounded to the nearest supported value.
* </ul>
* \note On CAT1B devices, if stereo mode is selected, the length of all read operations
* should be a multiple of two so that the left and right channels are read together.
*
* \note On CAT1B devices, when multiple channels are configured in a configurator, each channel
* should be initialized via a separate call to \ref cyhal_pdm_pcm_init_cfg.
* \} group_hal_impl_pdmpcm
*/

#if (CYHAL_DRIVER_AVAILABLE_PDMPCM)

#if defined(CY_IP_MXAUDIOSS_INSTANCES)
#define _CYHAL_PDM_INSTANCES (CY_IP_MXAUDIOSS_INSTANCES)
#if (CY_IP_MXAUDIOSS_INSTANCES >= 1)
#if (defined(AUDIOSS_PDM) && AUDIOSS_PDM) || (defined(AUDIOSS0_PDM) && AUDIOSS0_PDM) || (defined(AUDIOSS0_PDM_PDM) && AUDIOSS0_PDM_PDM)
#define _CYHAL_PDM_INST0 (1u)
#define _CYHAL_PDM_CHANNELS0 (1u)
#else
#define _CYHAL_PDM_INST0 (0u)
#endif
#endif
#if (CY_IP_MXAUDIOSS_INSTANCES >= 2)
#if (defined(AUDIOSS1_PDM) && AUDIOSS1_PDM) || (defined(AUDIOSS1_PDM_PDM) && AUDIOSS1_PDM_PDM)
#define _CYHAL_PDM_INST1 (1u)
#define _CYHAL_PDM_CHANNELS1 (1u)
#else
#define _CYHAL_PDM_INST1 (0u)
#endif
#endif

#define _CYHAL_PDM_PCM_HALF_FIFO (0x80U)
#elif defined(CY_IP_MXPDM) /* defined(CY_IP_MXAUDIOSS_INSTANCES) */
#define _CYHAL_PDM_INSTANCES (CY_IP_MXPDM_INSTANCES)
#define _CYHAL_PDM_INST0 (_CYHAL_PDM_INSTANCES >= 1)
#define _CYHAL_PDM_INST1 (_CYHAL_PDM_INSTANCES >= 2)
#define _CYHAL_PDM_CHANNEL_PAIRING

// TODO Remove this when DRIVERS-5627 is resolved
#define PDM0_NR (2u)
#if (_CYHAL_PDM_INST0)
#define _CYHAL_PDM_CHANNELS0 (PDM0_NR)
#endif
#if (_CYHAL_PDM_INST1)
#define _CYHAL_PDM_CHANNELS1 (PDM1_NR)
#endif

#define _CYHAL_PDM_PCM_HALF_FIFO (0x20U)
#define _CYHAL_PDM_PCM_MAX_FIR1_SCALE (31)

#else
#error "Unsupported PDM IP"
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

#define _CYHAL_PDM_PCM_UNPAIRED (-1)

 // 35-45 PCM samples it takes for PCM to stabilize. Round to even so that same number of left and right samples are removed
#define _CYHAL_PDM_PCM_STABILIZATION_FS 46
#define _CYHAL_PDM_PCM_EVENT_NONE ((cyhal_pdm_pcm_event_t) 0x0)
#define _CYHAL_PDM_PCM_HFCLK (1)

static PDM_Type *const _cyhal_pdm_pcm_base[] =
{
#if (_CYHAL_PDM_INST0)
#if (CY_IP_MXAUDIOSS_INSTANCES == 1)
    PDM, /* Only MXAUDIOSS leaves off the trailing 0 for 1 instance. MXPDM keeps it. */
#else
    PDM0,
#endif
#endif
#if (_CYHAL_PDM_INST1)
    PDM1,
#endif

#if (_CYHAL_PDM_INSTANCES > 2)
    #warning Unhandled audioss instance count
#endif
};

/* Note: We don't track channels in HWMGR because they are not completely independent. Instead we
 * keep a pointer to the obj struct for each channel */
static bool _cyhal_pdm_pcm_arrays_initialized = false;
#if (_CYHAL_PDM_INST0)
CY_NOINIT static cyhal_pdm_pcm_t* _cyhal_pdm_pcm_config_structs_inst0[_CYHAL_PDM_CHANNELS0];
#endif
#if (_CYHAL_PDM_INST1)
CY_NOINIT static cyhal_pdm_pcm_t* _cyhal_pdm_pcm_config_structs_inst1[_CYHAL_PDM_CHANNELS1];
#endif

static uint8_t _cyhal_pdm_num_channels[] =
{
#if (_CYHAL_PDM_INST0)
    _CYHAL_PDM_CHANNELS0,
#endif
#if (_CYHAL_PDM_INST1)
    _CYHAL_PDM_CHANNELS1,
#endif
};

static cyhal_pdm_pcm_t** _cyhal_pdm_pcm_config_structs[_CYHAL_PDM_INSTANCES] =
{
#if (_CYHAL_PDM_INST0)
    _cyhal_pdm_pcm_config_structs_inst0,
#endif
#if (_CYHAL_PDM_INST1)
    _cyhal_pdm_pcm_config_structs_inst1,
#endif
};

#if (_CYHAL_PDM_INST0)
static _cyhal_system_irq_t _cyhal_pdm_pcm_irq_n0[] =
{
#if (CY_IP_MXAUDIOSS_INSTANCES == 1)
    audioss_interrupt_pdm_IRQn, /* Only MXAUDIOSS leaves off the trailing 0 for 1 instance. MXPDM keeps it. */
#elif defined(CY_IP_MXAUDIOSS)
    audioss_0_interrupt_pdm_IRQn,
#elif defined(CY_IP_MXPDM)
    pdm_0_interrupts_0_IRQn,
    pdm_0_interrupts_1_IRQn,
#endif
};
#endif

#if (_CYHAL_PDM_INST1)
static _cyhal_system_irq_t _cyhal_pdm_pcm_irq_n1[] =
{
#if defined(CY_IP_MXAUDIOSS)
    audioss_1_interrupt_pdm_IRQn,
#endif
};
#endif

static const _cyhal_system_irq_t* _cyhal_pdm_pcm_irq_n[] =
{
#if (_CYHAL_PDM_INST0)
    _cyhal_pdm_pcm_irq_n0,
#endif
#if (_CYHAL_PDM_INST1)
    _cyhal_pdm_pcm_irq_n1,
#endif
#if (_CYHAL_PDM_INSTANCES > 2)
    #warning Unhandled audioss instance count
#endif
};

static void _cyhal_pdm_pcm_get_block_from_irqn(_cyhal_system_irq_t irqn, uint8_t* block, uint8_t* channel)
{
    switch (irqn)
    {
#if (_CYHAL_PDM_INST0)
#if (CY_IP_MXAUDIOSS_INSTANCES == 1)
    case audioss_interrupt_pdm_IRQn: /* Only MXAUDIOSS leaves off the trailing 0 for 1 instance. MXPDM keeps it. */
#elif defined(CY_IP_MXAUDIOSS)
    case audioss_0_interrupt_pdm_IRQn:
#elif defined(CY_IP_MXPDM)
    case pdm_0_interrupts_1_IRQn:
        *channel = 1;
        *block = 0;
        break;
    case pdm_0_interrupts_0_IRQn:
#endif
        *channel = 0;
        *block = 0;
        break;
#endif /* (_CYHAL_PDM_INST0) */
#if (_CYHAL_PDM_INST1 == 1)
    case audioss_1_interrupt_pdm_IRQn:
        *channel = 0;
        *block = 1;
        break;
#endif
#if (_CYHAL_PDM_INSTANCES > 2)
    #warning Unhandled audioss instance count
#endif
    default:
        CY_ASSERT(false); // Should never be called with a non-PDM IRQn
        *block = *channel = 0;
        break;
    }
}

#if defined(CY_IP_MXPDM)
#define _CYHAL_PDM_USES_PCLK
static const en_clk_dst_t _cyhal_pdm_clock[] =
{
#if (CY_IP_MXPDM_INSTANCES >= 1)
    PCLK_PDM0_CLK_IF_SRSS
#else
    #warning Unhandled tdm instance count
#endif
};
#endif

#if defined(CY_IP_MXAUDIOSS)
static const cy_stc_pdm_pcm_config_t _cyhal_pdm_pcm_default_config =
{
    .clkDiv = CY_PDM_PCM_CLK_DIV_BYPASS, // Configured by cyhal_pdm_pcm_init
    .mclkDiv = CY_PDM_PCM_CLK_DIV_BYPASS, // Configured by cyhal_pdm_pcm_init
    .ckoDiv = 3U, // Configured by cyhal_pdm_pcm_init
    .ckoDelay = 0U,
    .sincDecRate = 32U, // Configured by cyhal_pdm_pcm_init
    .chanSelect = CY_PDM_PCM_OUT_STEREO, // Configured by cyhal_pdm_pcm_init
    .chanSwapEnable = false,
    .highPassFilterGain = 8U,
    .highPassDisable = false,
    .softMuteCycles = CY_PDM_PCM_SOFT_MUTE_CYCLES_96,
    .softMuteFineGain = 1UL,
    .softMuteEnable = false,
    .wordLen = CY_PDM_PCM_WLEN_16_BIT, // Configured by cyhal_pdm_pcm_init
    .signExtension = true,
    .gainLeft = CY_PDM_PCM_BYPASS, // Configured by cyhal_pdm_pcm_init and cyhal_pdm_pcm_set_gain
    .gainRight = CY_PDM_PCM_BYPASS, // Configured by cyhal_pdm_pcm_init and cyhal_pdm_pcm_set_gain
    .rxFifoTriggerLevel = _CYHAL_PDM_PCM_HALF_FIFO - 1,
    .dmaTriggerEnable = false,
    .interruptMask = 0UL,
};
#elif defined(CY_IP_MXPDM)
static const cy_stc_pdm_pcm_config_v2_t _cyhal_pdm_pcm_default_config =
{
    /* clkDiv configured by pdm_pcm_init */
    .clksel = CY_PDM_PCM_SEL_SRSS_CLOCK,
    .halverate = CY_PDM_PCM_RATE_FULL,
    .route = 0u, /* Will be updated as channels are enabled */
    .fir0_coeff_user_value = 0u, /* Use default filter */
    .fir1_coeff_user_value = 0u, /* Use default filter */

};

static const cy_stc_pdm_pcm_channel_config_t _cyhal_pdm_pcm_default_channel_config =
{
    /* sampleDelay configured by init */
    /* Word size configured by init */
    .signExtension = true,
    .rxFifoTriggerLevel = _CYHAL_PDM_PCM_HALF_FIFO - 1,
    .fir0_enable = false, /* Default behavior is fir0 off and fir1 on */
    .cic_decim_code = CY_PDM_PCM_CHAN_CIC_DECIM_32,
    .fir0_decim_code = CY_PDM_PCM_CHAN_FIR0_DECIM_1, /* Ignored, FIR0 is disabled */
    .fir0_scale = 0u, /* Ignored, FIR0 is disabled */
    /* fir1 code and scale configured by init */
    .dc_block_disable = false, /* DC disable is only for testing */
    .dc_block_code = CY_PDM_PCM_CHAN_DCBLOCK_CODE_16
};

#endif

/* If check_used is set, return -1 if the paired channel is not used by this obj */
static inline int16_t _cyhal_pdm_pcm_get_paired_channel(cyhal_pdm_pcm_t* obj, bool check_used)
{
#if defined(_CYHAL_PDM_CHANNEL_PAIRING)
    /* The first index of a pair is always even. So clear the lowest bit if we're odd, set if if we're even */
    uint8_t channel_idx = obj->resource.channel_num;
    int16_t paired_channel = channel_idx ^ 1;
    if(paired_channel < _cyhal_pdm_num_channels[obj->resource.block_num])
    {
       if((false == check_used) || (obj == _cyhal_pdm_pcm_config_structs[obj->resource.block_num][paired_channel]))
       {
           return paired_channel;
       }
    }
#else
    CY_UNUSED_PARAMETER(obj);
    CY_UNUSED_PARAMETER(check_used);
#endif
    return _CYHAL_PDM_PCM_UNPAIRED;
}

static cyhal_pdm_pcm_t* _cyhal_pdm_pcm_find_existing_obj(uint8_t block_num)
{
    cyhal_pdm_pcm_t* existing_obj = NULL;
    /* Reserve this instance if there are no existing channels */
    for(int i = 0; NULL == existing_obj && i < _cyhal_pdm_num_channels[block_num]; ++i)
    {
        existing_obj = _cyhal_pdm_pcm_config_structs[block_num][i];
    }
    return existing_obj;
}

static inline uint32_t _cyhal_pdm_pcm_get_pdl_event_mask(cyhal_pdm_pcm_event_t event)
{
    static const uint32_t status_map[] =
    {
        0u,                                     // Default, no value
        (uint32_t)CY_PDM_PCM_INTR_RX_TRIGGER,   // CYHAL_PDM_PCM_RX_HALF_FULL
#if defined(CY_IP_MXAUDIOSS)
        (uint32_t)CY_PDM_PCM_INTR_RX_NOT_EMPTY, // CYHAL_PDM_PCM_RX_NOT_EMPTY
#elif defined(CY_IP_MXPDM)
        0u,
#endif
        (uint32_t)CY_PDM_PCM_INTR_RX_OVERFLOW,  // CYHAL_PDM_PCM_RX_OVERFLOW
        (uint32_t)CY_PDM_PCM_INTR_RX_UNDERFLOW, // CYHAL_PDM_PCM_RX_UNDERFLOW
    };
    return _cyhal_utils_convert_flags(status_map, sizeof(status_map) / sizeof(uint32_t), (uint32_t)event);
}

static inline cyhal_pdm_pcm_event_t _cyhal_pdm_pcm_get_hal_event(uint32_t pdl_event)
{
    cyhal_pdm_pcm_event_t hal_event = (cyhal_pdm_pcm_event_t)0u;
    if(0u != (pdl_event & CY_PDM_PCM_INTR_RX_TRIGGER))
    {
        hal_event |= CYHAL_PDM_PCM_RX_HALF_FULL;
    }
#if defined(CY_IP_MXAUDIOSS)
    if(0u != (pdl_event & CY_PDM_PCM_INTR_RX_NOT_EMPTY))
    {
        hal_event |= CYHAL_PDM_PCM_RX_NOT_EMPTY;
    }
#endif
    if(0u != (pdl_event & CY_PDM_PCM_INTR_RX_OVERFLOW))
    {
        hal_event |= CYHAL_PDM_PCM_RX_OVERFLOW;
    }
    if(0u != (pdl_event & CY_PDM_PCM_INTR_RX_UNDERFLOW))
    {
        hal_event |= CYHAL_PDM_PCM_RX_UNDERFLOW;
    }
    return hal_event;
}


static inline void _cyhal_pdm_pcm_clear_interrupt(cyhal_pdm_pcm_t* obj, uint32_t interrupt)
{
#if defined(CY_IP_MXAUDIOSS)
    Cy_PDM_PCM_ClearInterrupt(obj->base, interrupt);
#elif defined(CY_IP_MXPDM)
    Cy_PDM_PCM_Channel_ClearInterrupt(obj->base, obj->resource.channel_num, interrupt);
#endif
}

static inline uint32_t _cyhal_pdm_pcm_get_interrupt_mask(cyhal_pdm_pcm_t* obj)
{
#if defined(CY_IP_MXAUDIOSS)
    return Cy_PDM_PCM_GetInterruptMask(obj->base);
#elif defined(CY_IP_MXPDM)
    return Cy_PDM_PCM_Channel_GetInterruptMask(obj->base, obj->resource.channel_num);
#endif
}

static inline void _cyhal_pdm_pcm_set_interrupt_mask(cyhal_pdm_pcm_t* obj, uint32_t mask)
{
#if defined(CY_IP_MXAUDIOSS)
    Cy_PDM_PCM_SetInterruptMask(obj->base, mask);
#elif defined(CY_IP_MXPDM)
    Cy_PDM_PCM_Channel_SetInterruptMask(obj->base, obj->resource.channel_num, mask);
#endif
}

static inline void _cyhal_pdm_pcm_set_rx_fifo_level(cyhal_pdm_pcm_t *obj, uint8_t fifo_level)
{
#if defined(CY_IP_MXAUDIOSS)
    PDM_PCM_RX_FIFO_CTL(obj->base) = _VAL2FLD(PDM_RX_FIFO_CTL_TRIGGER_LEVEL, fifo_level - 1);
#elif defined(CY_IP_MXPDM)
    PDM_PCM_RX_FIFO_CTL(obj->base, obj->resource.channel_num) = _VAL2FLD(PDM_CH_RX_FIFO_CTL_TRIGGER_LEVEL, fifo_level - 1);
    int16_t paired_channel = _cyhal_pdm_pcm_get_paired_channel(obj, true);
    if(paired_channel >= 0)
    {
        PDM_PCM_RX_FIFO_CTL(obj->base, obj->resource.channel_num) = _VAL2FLD(PDM_CH_RX_FIFO_CTL_TRIGGER_LEVEL, fifo_level - 1);
    }
#endif
    _cyhal_pdm_pcm_clear_interrupt(obj, CY_PDM_PCM_INTR_RX_TRIGGER);
}

static bool _cyhal_pdm_pcm_pm_callback(cyhal_syspm_callback_state_t state, cyhal_syspm_callback_mode_t mode, void* callback_arg)
{
    CY_UNUSED_PARAMETER(state);
    cyhal_pdm_pcm_t *obj = (cyhal_pdm_pcm_t *)callback_arg;

    switch (mode)
    {
        case CYHAL_SYSPM_CHECK_READY:
        {
            bool enabled = cyhal_pdm_pcm_is_enabled(obj);
            obj->pm_transition_ready = !(enabled || cyhal_pdm_pcm_is_pending(obj));
            break;
        }
        case CYHAL_SYSPM_CHECK_FAIL:
        case CYHAL_SYSPM_AFTER_TRANSITION:
            obj->pm_transition_ready = false;
            break;
        default:
            CY_ASSERT(false);
            break;
    }
    return obj->pm_transition_ready;
}

static inline void _cyhal_pdm_pcm_increment_async_buffer(cyhal_pdm_pcm_t *obj, size_t increment)
{
    CY_ASSERT(obj->async_read_remaining >= increment);
    uint32_t saved_intr = cyhal_system_critical_section_enter();
    obj->async_read_remaining -= increment;
    obj->async_buffer = (obj->async_read_remaining == 0)
        ? NULL
        : (void*)(((uint8_t*) obj->async_buffer) + increment * obj->word_size);
    cyhal_system_critical_section_exit(saved_intr);
}

static inline void _cyhal_pdm_pcm_try_read_async(cyhal_pdm_pcm_t *obj)
{
    size_t read_remaining = obj->async_read_remaining;
    cyhal_pdm_pcm_read(obj, obj->async_buffer, &read_remaining);
    _cyhal_pdm_pcm_increment_async_buffer(obj, read_remaining);
}

static inline cy_rslt_t _cyhal_pdm_pcm_dma_start(cyhal_pdm_pcm_t *obj)
{
    cy_rslt_t rslt;
    size_t transfer_size = obj->user_trigger_level;
    if (obj->async_read_remaining <= obj->user_trigger_level)
    {
        transfer_size = obj->async_read_remaining;
        // Only want the user callback to be called on the last dma transfer.
        cyhal_dma_enable_event(&(obj->dma), CYHAL_DMA_TRANSFER_COMPLETE, CYHAL_ISR_PRIORITY_DEFAULT, true);
    }

    int16_t paired_channel = _cyhal_pdm_pcm_get_paired_channel(obj, true);

    cyhal_dma_cfg_t dma_cfg =
    {
#if defined(CY_IP_MXAUDIOSS)
        .src_addr = (uint32_t)(&(obj->base->RX_FIFO_RD)),
#elif defined(CY_IP_MXPDM)
        .src_addr = (uint32_t)(&(obj->base->CH[obj->resource.channel_num].RX_FIFO_RD)),
#endif
        .src_increment = 0,
        .dst_addr = (uint32_t)obj->async_buffer,
        .dst_increment = (paired_channel < 0) ? 1 : 2,
        .transfer_width = 8 * obj->word_size,
        .length = (paired_channel < 0) ? transfer_size : transfer_size / 2,
        .burst_size = 0,
        .action = CYHAL_DMA_TRANSFER_BURST,
    };

    rslt = cyhal_dma_configure(&(obj->dma), &dma_cfg);

    if (CY_RSLT_SUCCESS == rslt)
    {
        rslt = cyhal_dma_enable(&(obj->dma));
    }

#if defined(CY_IP_MXPDM)
    if(paired_channel >= 0 && CY_RSLT_SUCCESS == rslt)
    {
        /* The first DMA was for the left samples. The second DMA will be for the right ones
         * Start the transfer at the first element of async_buffer */
        void* dst_addr = (((uint8_t*) obj->async_buffer) + obj->word_size);
        cyhal_dma_cfg_t dma_cfg_paired =
        {
            .src_addr = (uint32_t)(&(obj->base->CH[paired_channel].RX_FIFO_RD)),
            .src_increment = 0,
            .dst_addr = (uint32_t)dst_addr,
            .dst_increment = 2,
            .transfer_width = 8 * obj->word_size,
            .length = transfer_size / 2,
            .burst_size = 0,
            .action = CYHAL_DMA_TRANSFER_BURST,
        };

        rslt = cyhal_dma_configure(&(obj->dma_paired), &dma_cfg_paired);

        if (CY_RSLT_SUCCESS == rslt)
        {
            rslt = cyhal_dma_enable(&(obj->dma_paired));
        }
    }
#endif

    if (CY_RSLT_SUCCESS == rslt)
    {
        _cyhal_pdm_pcm_increment_async_buffer(obj, transfer_size);
        rslt = cyhal_dma_start_transfer(&(obj->dma));
    }
#if defined(CY_IP_MXPDM)
    if (paired_channel >= 0 && CY_RSLT_SUCCESS == rslt)
    {
        rslt = cyhal_dma_start_transfer(&(obj->dma_paired));
    }
#endif
    return rslt;
}

static void _cyhal_pdm_pcm_hw_irq_handler(void)
{
    _cyhal_system_irq_t irqn = _cyhal_irq_get_active();
    uint8_t block, channel;
    _cyhal_pdm_pcm_get_block_from_irqn(irqn, &block, &channel);
    cyhal_pdm_pcm_t *obj = _cyhal_pdm_pcm_config_structs[block][channel];

    if (obj != NULL)
    {
#if defined(CY_IP_MXAUDIOSS)
        uint32_t irq_status = Cy_PDM_PCM_GetInterruptStatus(obj->base);
#elif defined(CY_IP_MXPDM)
        uint32_t irq_status = Cy_PDM_PCM_Channel_GetInterruptStatus(obj->base, obj->resource.channel_num);
#endif
        _cyhal_pdm_pcm_clear_interrupt(obj, irq_status);
        cyhal_pdm_pcm_event_t event = _cyhal_pdm_pcm_get_hal_event(irq_status);

        if((CYHAL_PDM_PCM_RX_HALF_FULL & event) || (CYHAL_PDM_PCM_RX_OVERFLOW & event))
        {
            if (obj->stabilized)
            {
                if (NULL != obj->async_buffer)
                {
                    if (obj->dma.resource.type == CYHAL_RSC_INVALID)
                    {
                        if (obj->async_read_remaining > 0)
                        {
                            _cyhal_pdm_pcm_try_read_async(obj);
                        }
                        if (obj->async_read_remaining == 0)
                        {
                            event |= CYHAL_PDM_PCM_ASYNC_COMPLETE;
                        }
                    }
                    else
                    {
                        if (obj->async_read_remaining > 0 && !cyhal_dma_is_busy(&(obj->dma)))
                        {
                            cy_rslt_t rslt = _cyhal_pdm_pcm_dma_start(obj);
                            CY_UNUSED_PARAMETER(rslt);
                            CY_ASSERT(CY_RSLT_SUCCESS == rslt);
                        }
                    }

                    if (obj->async_read_remaining == 0)
                    {
                        obj->async_buffer = NULL;
                        if (!(obj->irq_cause & CYHAL_PDM_PCM_RX_HALF_FULL))
                        {
                            // Only disable the interrupt mask if the user did not explicitly enable the mask
                            _cyhal_pdm_pcm_set_interrupt_mask(obj, _cyhal_pdm_pcm_get_interrupt_mask(obj) & ~CY_PDM_PCM_INTR_RX_TRIGGER);
                        }
                    }
                }
            }
            else
            {
                /* Filter out the events that aren't applicable until we've stabilized */
                event &= ~(CYHAL_PDM_PCM_RX_HALF_FULL | CYHAL_PDM_PCM_RX_OVERFLOW);
                // The PDM/PCM block alternates between left and right in stereo.
                // To preserve oddness and eveness of left and right, removes an even number of elements.
                for (int i = 0; i < _CYHAL_PDM_PCM_STABILIZATION_FS; i++)
                {
#if defined(CY_IP_MXAUDIOSS)
                    (void)Cy_PDM_PCM_ReadFifo(obj->base);
#elif defined(CY_IP_MXPDM)
                    Cy_PDM_PCM_Channel_ReadFifo(obj->base, obj->resource.channel_num);
                    int16_t paired_channel = _cyhal_pdm_pcm_get_paired_channel(obj, true);
                    if(paired_channel >= 0)
                    {
                        (void)Cy_PDM_PCM_Channel_ReadFifo(obj->base, paired_channel);
                    }
#endif
                }
                _cyhal_pdm_pcm_set_rx_fifo_level(obj, obj->user_trigger_level);
                if (!cyhal_pdm_pcm_is_pending(obj) && !(CYHAL_PDM_PCM_RX_HALF_FULL & obj->irq_cause))
                {
                    _cyhal_pdm_pcm_set_interrupt_mask(obj, _cyhal_pdm_pcm_get_interrupt_mask(obj) & ~CY_PDM_PCM_INTR_RX_TRIGGER);
                }
                obj->stabilized = true;
            }
        }

        event &= obj->irq_cause;

        if (event != _CYHAL_PDM_PCM_EVENT_NONE)
        {
            cyhal_pdm_pcm_event_callback_t callback = (cyhal_pdm_pcm_event_callback_t) obj->callback_data.callback;
            if (callback != NULL)
            {
                callback(obj->callback_data.callback_arg, event);
            }
        }
    }
}

#if defined(CY_IP_MXAUDIOSS)
static inline bool _cyhal_pdm_pcm_invalid_gain_range(int16_t gain_value)
{
    return gain_value < CYHAL_PDM_PCM_MIN_GAIN || gain_value > CYHAL_PDM_PCM_MAX_GAIN;
}

static inline cy_en_pdm_pcm_gain_t _cyhal_pdm_pcm_scale_gain_value(int8_t gain_value)
{
    // The hardware use gain rate of 1.5 dB per register increment,
    // ranging from -12dB (register value 0x0) to 10.5dB (register value 0xF).
    // Need to scale dB range [-24, 21] to register range [0x0, 0xF]
    return (cy_en_pdm_pcm_gain_t) ((gain_value + 25) / 3);
}

static inline uint8_t _cyhal_pdm_pcm_word_length_from_pdl(cy_en_pdm_pcm_word_len_t pdl_length)
{
    switch(pdl_length)
    {
        case CY_PDM_PCM_WLEN_16_BIT:
            return 16u;
        case CY_PDM_PCM_WLEN_18_BIT:
            return 18u;
        case CY_PDM_PCM_WLEN_20_BIT:
            return 20u;
        case CY_PDM_PCM_WLEN_24_BIT:
            return 24u;
        default:
            CY_ASSERT(false);
            return 24u;
    }
}

#elif defined(CY_IP_MXPDM)

static inline uint8_t _cyhal_pdm_pcm_word_length_from_pdl(cy_en_pdm_pcm_word_size_t pdl_length)
{
    switch(pdl_length)
    {
        case CY_PDM_PCM_WSIZE_8_BIT:
            return 8u;
        case CY_PDM_PCM_WSIZE_10_BIT:
            return 10u;
        case CY_PDM_PCM_WSIZE_12_BIT:
            return 12u;
        case CY_PDM_PCM_WSIZE_14_BIT:
            return 14u;
        case CY_PDM_PCM_WSIZE_16_BIT:
            return 16u;
        case CY_PDM_PCM_WSIZE_18_BIT:
            return 18u;
        case CY_PDM_PCM_WSIZE_20_BIT:
            return 20u;
        case CY_PDM_PCM_WSIZE_24_BIT:
            return 24u;
        case CY_PDM_PCM_WSIZE_32_BIT:
            return 32u;
        default:
            CY_ASSERT(false);
            return 32u;
    }

}
static inline cy_rslt_t _cyhal_pdm_pcm_word_length_to_pdl(uint8_t word_length, cy_en_pdm_pcm_word_size_t *pdl_length)
{
    switch(word_length)
    {
        case 8:
            *pdl_length = CY_PDM_PCM_WSIZE_8_BIT;
            break;
        case 10:
            *pdl_length = CY_PDM_PCM_WSIZE_10_BIT;
            break;
        case 12:
            *pdl_length = CY_PDM_PCM_WSIZE_12_BIT;
            break;
        case 14:
            *pdl_length = CY_PDM_PCM_WSIZE_14_BIT;
            break;
        case 16:
            *pdl_length = CY_PDM_PCM_WSIZE_16_BIT;
            break;
        case 18:
            *pdl_length = CY_PDM_PCM_WSIZE_18_BIT;
            break;
        case 20:
            *pdl_length = CY_PDM_PCM_WSIZE_20_BIT;
            break;
        case 24:
            *pdl_length = CY_PDM_PCM_WSIZE_24_BIT;
            break;
        case 32:
            *pdl_length = CY_PDM_PCM_WSIZE_32_BIT;
            break;
        default:
            return CYHAL_PDM_PCM_RSLT_ERR_INVALID_CONFIG_PARAM;
    }

    return CY_RSLT_SUCCESS;
}

static inline cy_rslt_t _cyhal_pdm_pcm_convert_decim_rate(uint8_t decim_rate, cy_en_pdm_pcm_ch_fir1_decimcode_t* pdl_code)
{
    switch(decim_rate)
    {
        case 32:
            *pdl_code = CY_PDM_PCM_CHAN_FIR1_DECIM_1;
            break;
        case 64:
            *pdl_code = CY_PDM_PCM_CHAN_FIR1_DECIM_2;
            break;
        case 96:
            *pdl_code = CY_PDM_PCM_CHAN_FIR1_DECIM_3;
            break;
        case 128:
            *pdl_code = CY_PDM_PCM_CHAN_FIR1_DECIM_4;
            break;
        default:
            return CYHAL_PDM_PCM_RSLT_ERR_INVALID_CONFIG_PARAM;
    }

    return CY_RSLT_SUCCESS;
}

static inline int _cyhal_pdm_pcm_gain_to_scale(int16_t gain_val)
{
    /* This IP version doesn't support directly configuring the gain, but we can manipulate the FIR scale
     * The formula for gain in db is db = 20 * log_10(FIR1_GAIN / 2^scale), where FIR1_GAIN = 13921
     * Solving for scale, we get: scale = log_2(FIR1_GAIN / 10^(db / 20))
     */

     /* Cmath only provides ln and log10, need to compute log_2 in terms of those */
     const int FIR1_GAIN = 13921;
     /* Gain is specified in 0.5 db steps in the interface */
     float desired_gain = ((float)gain_val) * 0.5f;
     float inner_value = FIR1_GAIN / (powf(10, (desired_gain / 20)));
     float scale = logf(inner_value) / logf(2);
     int scale_rounded = (uint8_t)(scale + 0.5f);
     return scale_rounded;
}

#endif
#if defined(CY_IP_MXAUDIOSS)
static inline cy_rslt_t _cyhal_pdm_pcm_set_pdl_config_struct(cyhal_pdm_pcm_t* obj, const cyhal_pdm_pcm_cfg_t *cfg, cy_stc_pdm_pcm_config_t *pdl_config)
{
    // PDM_CKO = sample_rate * decimation_rate
    if (cfg->sample_rate > CYHAL_PDM_PCM_MAX_SAMPLE_RATE)
    {
        return CYHAL_PDM_PCM_RSLT_ERR_INVALID_CONFIG_PARAM;
    }
    uint32_t pdm_cko = cfg->sample_rate * cfg->decimation_rate;
    uint32_t hf1_freq = cyhal_clock_get_frequency(&obj->clock);
    // need to use 3 clock dividers to divied hf1_freq to pdm_cko
    // divider 0 and 1 have values 1 to 4, divider 2 has values 2 to 16
    uint8_t best_div0 = 1, best_div1 = 1, best_div2 = 2;
    uint32_t min_error = UINT32_MAX;
    for (uint8_t div1 = 1; div1 <= 4; div1++)
    {
        // start divider 0 at divider 1 's current value
        // (div0, div1) = (2,3) is equivalent to (3,2)
        for (uint8_t div0 = div1; div0 <= 4; div0++)
        {
            uint32_t div01_freq = div0 * div1 * pdm_cko;
            for (uint8_t div2 = 2; div2 <= 16; div2++)
            {
                uint32_t computed_hfclk1_freq = div01_freq * div2;
                uint32_t error = computed_hfclk1_freq < hf1_freq ? hf1_freq - computed_hfclk1_freq : computed_hfclk1_freq - hf1_freq;
                if (error < min_error)
                {
                    best_div0 = div0;
                    best_div1 = div1;
                    best_div2 = div2;
                    min_error = error;
                }
            }
        }
    }
    pdl_config->clkDiv = (cy_en_pdm_pcm_clk_div_t)(best_div0 - 1);
    pdl_config->mclkDiv = (cy_en_pdm_pcm_clk_div_t)(best_div1 - 1);
    pdl_config->ckoDiv = best_div2 - 1;

    // sinc_rate = decimation_rate / 2
    // decimation rate is always valid. The max value for sync rate is 0x7F
    pdl_config->sincDecRate = (cfg->decimation_rate) / 2;

    switch(cfg->mode)
    {
        case CYHAL_PDM_PCM_MODE_LEFT:
            pdl_config->chanSelect = CY_PDM_PCM_OUT_CHAN_LEFT;
            break;
        case CYHAL_PDM_PCM_MODE_RIGHT:
            pdl_config->chanSelect = CY_PDM_PCM_OUT_CHAN_RIGHT;
            break;
        case CYHAL_PDM_PCM_MODE_STEREO:
            pdl_config->chanSelect = CY_PDM_PCM_OUT_STEREO;
            break;
        default:
            return CYHAL_PDM_PCM_RSLT_ERR_INVALID_CONFIG_PARAM;
    }

    switch(cfg->word_length)
    {
        case 16:
            pdl_config->wordLen = CY_PDM_PCM_WLEN_16_BIT;
            break;
        case 18:
            pdl_config->wordLen = CY_PDM_PCM_WLEN_18_BIT;
            break;
        case 20:
            pdl_config->wordLen = CY_PDM_PCM_WLEN_20_BIT;
            break;
        case 24:
            pdl_config->wordLen = CY_PDM_PCM_WLEN_24_BIT;
            break;
        default:
            return CYHAL_PDM_PCM_RSLT_ERR_INVALID_CONFIG_PARAM;
    }

    if (_cyhal_pdm_pcm_invalid_gain_range(cfg->left_gain) || _cyhal_pdm_pcm_invalid_gain_range(cfg->right_gain))
    {
        return CYHAL_PDM_PCM_RSLT_ERR_INVALID_CONFIG_PARAM;
    }
    pdl_config->gainLeft = _cyhal_pdm_pcm_scale_gain_value(cfg->left_gain);
    pdl_config->gainRight = _cyhal_pdm_pcm_scale_gain_value(cfg->right_gain);

    return CY_RSLT_SUCCESS;
}

#elif defined(CY_IP_MXPDM)

static inline cy_rslt_t _cyhal_pdm_pcm_set_pdl_config_struct(cyhal_pdm_pcm_t* obj, const cyhal_pdm_pcm_cfg_t *cfg,
                                                             bool found_existing,
                                                             cy_stc_pdm_pcm_config_v2_t  *pdl_config,
                                                             cy_stc_pdm_pcm_channel_config_t* pdl_chan_config,
                                                             cy_stc_pdm_pcm_channel_config_t* pdl_chan_config_paired)
{
    const uint8_t MIN_CLK_DIV = 4u; /* PDM.CLOCK_CTL.CLOCK_DIV defines 0-2 (corresponding to divide by 1-3) as illegal */
    const uint16_t MAX_CLK_DIV = 256;
    const uint16_t CLK_STEP = 2u; /* Use even divide divides to ensure a 50/50 duty cycle */
    const cyhal_clock_tolerance_t CLK_TOLERANCE = { .type = CYHAL_TOLERANCE_PERCENT, .value = 1 };

    cy_rslt_t result = CY_RSLT_SUCCESS;
    if (cfg->sample_rate > CYHAL_PDM_PCM_MAX_SAMPLE_RATE)
    {
        result = CYHAL_PDM_PCM_RSLT_ERR_INVALID_CONFIG_PARAM;
    }
    int fir1_scale = _cyhal_pdm_pcm_gain_to_scale(cfg->left_gain);
    if(CY_RSLT_SUCCESS == result && (fir1_scale < 0 || fir1_scale > _CYHAL_PDM_PCM_MAX_FIR1_SCALE))
    {
        result = CYHAL_PDM_PCM_RSLT_ERR_INVALID_CONFIG_PARAM;
    }

    uint8_t clkDiv = 0u; /* Per hw definition, this should be 1 less than the actual desired divide */
    if(CY_RSLT_SUCCESS == result)
    {
        uint32_t target_freq = cfg->sample_rate * cfg->decimation_rate;

        if(obj->is_clock_owned && false == found_existing)
        {
            /* For power consumption purposes we want the input clock divided down as far as it will
             * go. So start out at our smallest supported divider and increase until we find something that
             * will get us within our tolerance. */
             for(uint16_t i = MIN_CLK_DIV; i <= MAX_CLK_DIV; i += CLK_STEP)
             {
                 uint32_t desired_source_freq = target_freq * i;
                 cy_rslt_t freq_result = _cyhal_utils_set_clock_frequency(&(obj->clock), desired_source_freq, &CLK_TOLERANCE);
                 if(CY_RSLT_SUCCESS == freq_result)
                 {
                     clkDiv = i - 1;
                     break;
                 }
             }
        }
        else // User-provided clock or clock already initialized by another channel, all we can do is adjust/check our internal divider
        {
            uint32_t actual_source_freq = cyhal_clock_get_frequency(&obj->clock);
            uint32_t best_divider = (actual_source_freq + (target_freq / 2)) / target_freq; // Round to nearest divider
            uint32_t desired_source_freq = target_freq * best_divider;
            uint32_t diff = (uint32_t)abs(_cyhal_utils_calculate_tolerance(CLK_TOLERANCE.type, desired_source_freq, actual_source_freq));
            if(diff <= CLK_TOLERANCE.value && best_divider <= MAX_CLK_DIV)
            {
                clkDiv = (uint8_t)(best_divider - 1);
            }
        }

        if(0u == clkDiv)
        {
            result = CYHAL_PDM_PCM_RSLT_ERR_INVALID_CONFIG_PARAM;
        }

        if(found_existing) /* Check that the required clock divider is the same as what is already there */
        {
            uint8_t existingDiv = _FLD2VAL(PDM_CLOCK_CTL_CLOCK_DIV, PDM_PCM_CLOCK_CTL(obj->base));
            if(existingDiv != clkDiv)
            {
                result = CYHAL_PDM_PCM_RSLT_ERR_INVALID_CONFIG_PARAM;
            }
        }
    }

    if(CY_RSLT_SUCCESS == result)
    {
        pdl_config->clkDiv = clkDiv;
        /* Left samples on rising edge, right samples on falling edge. Per PDL documentation, rising edge corresponds to
         * a sampledelay of clockDiv, and falling edge corresponds to sampledelay of clockDiv / 2.
         * When we're in stereo, we sample left on the "primary" channel and right on the paired one */
        pdl_chan_config->sampledelay = (CYHAL_PDM_PCM_MODE_RIGHT == cfg->mode) ? clkDiv / 2 : clkDiv;
        pdl_chan_config->fir1_scale = fir1_scale;
        result = _cyhal_pdm_pcm_word_length_to_pdl(cfg->word_length, &pdl_chan_config->wordSize);
    }

    if(CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_pdm_pcm_convert_decim_rate(cfg->decimation_rate, &pdl_chan_config->fir1_decim_code);
    }

    if(CY_RSLT_SUCCESS == result && NULL != pdl_chan_config_paired)
    {
        int fir1_scale_paired = _cyhal_pdm_pcm_gain_to_scale(cfg->right_gain);
        if(CY_RSLT_SUCCESS == result && (fir1_scale_paired < 0 || fir1_scale_paired > _CYHAL_PDM_PCM_MAX_FIR1_SCALE))
        {
            result = CYHAL_PDM_PCM_RSLT_ERR_INVALID_CONFIG_PARAM;
        }

        if(CY_RSLT_SUCCESS == result)
        {
            *pdl_chan_config_paired = *pdl_chan_config;
            pdl_chan_config_paired->sampledelay = clkDiv / 2;
            pdl_chan_config_paired->fir1_scale = fir1_scale_paired;
        }
    }

    return result;
}

#endif

// - Update clocking confguration
// - Handle word length

static void _cyhal_pdm_pcm_dma_callback(void *callback_arg, cyhal_dma_event_t event)
{
    CY_UNUSED_PARAMETER(event);
    cyhal_pdm_pcm_t *obj = (cyhal_pdm_pcm_t *)callback_arg;
    if (obj != NULL)
    {
#if defined(CY_IP_MXPDM)
        bool has_pair = CYHAL_RSC_INVALID != obj->dma_paired.resource.type;
        if(has_pair && ((cyhal_dma_is_busy(&obj->dma) || cyhal_dma_is_busy(&obj->dma_paired))))
        {
            return; /* This callback was for the first DMA. Wait for the second one */
        }
#endif
        // DMA finished trigger callback
        cyhal_pdm_pcm_event_callback_t callback = (cyhal_pdm_pcm_event_callback_t) obj->callback_data.callback;
        if (callback != NULL)
        {
            callback(obj->callback_data.callback_arg, CYHAL_PDM_PCM_ASYNC_COMPLETE);
        }
    }
}


static cy_rslt_t _cyhal_pdm_pcm_init_clock(cyhal_pdm_pcm_t *obj, const cyhal_clock_t* clk_source, cyhal_pdm_pcm_t* existing_obj)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    if(NULL != existing_obj)
    {
        /* Either both use auto-allocated clock source or they both use the same manually specified source */
        if((true == existing_obj->is_clock_owned) != (clk_source == NULL))
        {
            result = CYHAL_PDM_PCM_RSLT_ERR_INVALID_CONFIG_PARAM;
        }
        else
        {
            /* Copy over the existing clock settings */
            obj->clock = existing_obj->clock;
            obj->is_clock_owned = existing_obj->is_clock_owned;
            if(false == existing_obj->is_clock_owned)
            {
                /* Custom clocks must be the same */
                if((clk_source->block != existing_obj->clock.block) ||
                   (clk_source->channel != existing_obj->clock.channel))
               {
                    result = CYHAL_PDM_PCM_RSLT_ERR_INVALID_CONFIG_PARAM;
               }
            }
        }
    }
    else if (clk_source != NULL)
    {
        obj->clock = *clk_source;
    }
    else
    {
        // On CAT1A, we're hard-wired to an HFCLK so the divider type doesn't apply. On all current CAT1B hardware,
        // we happen to be wired to a PERI group with a 16.5 bit divider, but we're not terribly picky so just ask
        // for a 16-bit divider.
        result = _cyhal_utils_allocate_clock(&(obj->clock), &(obj->resource), CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT, true);
        if(CY_RSLT_SUCCESS == result)
        {
            obj->is_clock_owned = true;
            result = cyhal_clock_set_enabled(&(obj->clock), true, true);
        }
    }

#if defined(_CYHAL_PDM_USES_PCLK)
    // If we're using a peri divider, hook it up to ourself
    if (CY_RSLT_SUCCESS == result && obj->clock.block != CYHAL_CLOCK_BLOCK_HF && false == obj->owned_by_configurator)
    {
        en_clk_dst_t pclk = _cyhal_pdm_clock[obj->resource.block_num];
        result = _cyhal_utils_peri_pclk_assign_divider(pclk, &(obj->clock));
    }
#endif

    return result;
}

static void _cyhal_pdm_pcm_arrays_init( void )
{
    if (!_cyhal_pdm_pcm_arrays_initialized)
    {
#if (_CYHAL_PDM_INST0)
        for (uint8_t i = 0; i < _CYHAL_PDM_CHANNELS0; i++)
        {
            _cyhal_pdm_pcm_config_structs_inst0[i] = NULL;
        }
#endif
#if (_CYHAL_PDM_INST1)
        for (uint8_t i = 0; i < _CYHAL_PDM_CHANNELS1; i++)
        {
            _cyhal_pdm_pcm_config_structs_inst1[i] = NULL;
        }
#endif
        _cyhal_pdm_pcm_arrays_initialized = true;
    }

}

static cy_rslt_t _cyhal_pdm_pcm_init_hw(cyhal_pdm_pcm_t *obj, int paired_channel, cyhal_pdm_pcm_t* existing_obj,
#if defined(CY_IP_MXAUDIOSS_INSTANCES)
                                        const cy_stc_pdm_pcm_config_t* pdl_struct
#elif defined(CY_IP_MXTDM_INSTANCES)
                                        const cy_stc_pdm_pcm_config_v2_t* pdl_struct,
                                        const cy_stc_pdm_pcm_channel_config_t* pdl_chan_struct,
                                        const cy_stc_pdm_pcm_channel_config_t* pdl_chan_struct_paired
#endif 
)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    obj->base = _cyhal_pdm_pcm_base[obj->resource.block_num];
    if(NULL == existing_obj)
    {
        result = (cy_rslt_t)Cy_PDM_PCM_Init(obj->base, pdl_struct);
    }

#if defined(CY_IP_MXPDM)
    if (CY_RSLT_SUCCESS == result)
    {
        result = (cy_rslt_t)Cy_PDM_PCM_Channel_Init(obj->base, pdl_chan_struct, obj->resource.channel_num);
    }
    if(CY_RSLT_SUCCESS == result && paired_channel >= 0)
    {
        result = (cy_rslt_t)Cy_PDM_PCM_Channel_Init(obj->base, pdl_chan_struct_paired, paired_channel);
    }
    if (CY_RSLT_SUCCESS == result)
    {
        Cy_PDM_PCM_Channel_Enable(obj->base, obj->resource.channel_num);
        if(paired_channel >= 0)
        {
            Cy_PDM_PCM_Channel_Enable(obj->base, paired_channel);
        }
    }
#elif defined(CY_IP_MXAUDIOSS)
    CY_UNUSED_PARAMETER(paired_channel);
#endif

    if (CY_RSLT_SUCCESS == result)
    {
        _cyhal_pdm_pcm_config_structs[obj->resource.block_num][obj->resource.channel_num] = obj;
#if defined(CY_IP_MXAUDIOSS)
        uint8_t word_length = _cyhal_pdm_pcm_word_length_from_pdl(pdl_struct->wordLen);
#elif defined(CY_IP_MXPDM)
        if(paired_channel >= 0)
        {
            _cyhal_pdm_pcm_config_structs[obj->resource.block_num][paired_channel] = obj;
        }
        uint8_t word_length = _cyhal_pdm_pcm_word_length_from_pdl(pdl_chan_struct->wordSize);
#endif
        if(word_length <= 8)
        {
            obj->word_size = 1;
        }
        else if(word_length <= 16)
        {
            obj->word_size = 2;
        }
        else
        {
            obj->word_size = 4;
        }
        obj->callback_data.callback = NULL;
        obj->callback_data.callback_arg = NULL;
#if defined(CY_IP_MXAUDIOSS)
        /* No irq mask in the config struct for MXTDM */
        obj->irq_cause = (uint32_t)_cyhal_pdm_pcm_get_hal_event(pdl_struct->interruptMask);
        obj->stabilized = false;
#elif defined(CY_IP_MXTDM)
        obj->stabilized = true;
        _cyhal_pdm_pcm_set_rx_fifo_level(obj, obj->user_trigger_level);
#endif
        obj->pm_transition_ready = false;

        obj->pm_callback.callback = &_cyhal_pdm_pcm_pm_callback;
        obj->pm_callback.states = (cyhal_syspm_callback_state_t)(CYHAL_SYSPM_CB_CPU_DEEPSLEEP | CYHAL_SYSPM_CB_SYSTEM_HIBERNATE);
        obj->pm_callback.next = NULL;
        obj->pm_callback.args = (void*)obj;
        obj->pm_callback.ignore_modes = (cyhal_syspm_callback_mode_t)(CYHAL_SYSPM_BEFORE_TRANSITION | CYHAL_SYSPM_AFTER_DS_WFI_TRANSITION);

        _cyhal_syspm_register_peripheral_callback(&(obj->pm_callback));

        /* If we're using two channels in a stereo pair, both will generate interrupts in sync with each other, so
         * only listen on the primary channel (i.e. the one corresponding to the pins that were passed in) */
        _cyhal_system_irq_t irqn = _cyhal_pdm_pcm_irq_n[obj->resource.block_num][obj->resource.channel_num];
        _cyhal_irq_register(irqn, CYHAL_ISR_PRIORITY_DEFAULT, _cyhal_pdm_pcm_hw_irq_handler);
        _cyhal_irq_enable(irqn);
        cyhal_pdm_pcm_clear(obj);
    }

    return result;
}

cy_rslt_t cyhal_pdm_pcm_init(cyhal_pdm_pcm_t *obj, cyhal_gpio_t pin_data, cyhal_gpio_t pin_clk,
                const cyhal_clock_t *clk_source, const cyhal_pdm_pcm_cfg_t *cfg)
{
    CY_ASSERT(NULL != obj);
    memset(obj, 0, sizeof(cyhal_pdm_pcm_t));
    cy_rslt_t result = CY_RSLT_SUCCESS;

    _cyhal_pdm_pcm_arrays_init();

    /* Explicitly marked not allocated resources as invalid to prevent freeing them. */
    obj->resource.type = CYHAL_RSC_INVALID;
    obj->pin_data = CYHAL_NC_PIN_VALUE;
    obj->pin_clk = CYHAL_NC_PIN_VALUE;
    obj->dma.resource.type = CYHAL_RSC_INVALID;
#if defined(CY_IP_MXPDM)
    obj->dma_paired.resource.type = CYHAL_RSC_INVALID;
#endif

    obj->user_trigger_level = _CYHAL_PDM_PCM_HALF_FIFO;

    /* Reserve the PDM-PCM */
#if defined(CY_IP_MXAUDIOSS)
    const cyhal_resource_pin_mapping_t *data_map = _CYHAL_UTILS_GET_RESOURCE(pin_data, cyhal_pin_map_audioss_pdm_data);
    const cyhal_resource_pin_mapping_t *clk_map = _CYHAL_UTILS_GET_RESOURCE(pin_clk, cyhal_pin_map_audioss_pdm_clk);
    uint8_t data_dm = CYHAL_PIN_MAP_DRIVE_MODE_AUDIOSS_PDM_DATA;
    uint8_t clk_dm = CYHAL_PIN_MAP_DRIVE_MODE_AUDIOSS_PDM_CLK;
#elif defined(CY_IP_MXTDM)
    const cyhal_resource_pin_mapping_t *data_map = _CYHAL_UTILS_GET_RESOURCE(pin_data, cyhal_pin_map_pdm_pdm_data);
    const cyhal_resource_pin_mapping_t *clk_map = _CYHAL_UTILS_GET_RESOURCE(pin_clk, cyhal_pin_map_pdm_pdm_clk);
    uint8_t data_dm = CYHAL_PIN_MAP_DRIVE_MODE_PDM_PDM_DATA;
    uint8_t clk_dm = CYHAL_PIN_MAP_DRIVE_MODE_PDM_PDM_CLK;
#endif

    if ((NULL == data_map) || (NULL == clk_map) || !_cyhal_utils_map_resources_equal(data_map, clk_map))
    {
        result = CYHAL_PDM_PCM_RSLT_ERR_INVALID_PIN;
    }

    cyhal_pdm_pcm_t* existing_obj = NULL;
    int paired_channel = _CYHAL_PDM_PCM_UNPAIRED;
    if(CY_RSLT_SUCCESS == result)
    {
        _CYHAL_UTILS_ASSIGN_RESOURCE(obj->resource, CYHAL_RSC_PDM, data_map);
        obj->base = _cyhal_pdm_pcm_base[obj->resource.block_num];
        if(CYHAL_PDM_PCM_MODE_STEREO == cfg->mode)
        {
            /* Need to also reserve the adjacent receiver */
            paired_channel = _cyhal_pdm_pcm_get_paired_channel(obj, false);
        }

        if((NULL != _cyhal_pdm_pcm_config_structs[obj->resource.block_num][obj->resource.channel_num]) ||
           (paired_channel >= 0 && (NULL != _cyhal_pdm_pcm_config_structs[obj->resource.block_num][paired_channel])))
        {
            /* This channel is already consumed */
            result = CYHAL_HWMGR_RSLT_ERR_INUSE;
        }
        else
        {
            existing_obj = _cyhal_pdm_pcm_find_existing_obj(obj->resource.block_num);
            if(NULL == existing_obj)
            {
                result = cyhal_hwmgr_reserve(&(obj->resource));
            }
        }
    }

    /* Reserve the pdm in pin */
    if (CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_utils_reserve_and_connect(data_map, data_dm);
        if (CY_RSLT_SUCCESS == result)
            obj->pin_data = pin_data;
    }

    /* Reserve the clk pin */
    if (CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_utils_reserve_and_connect(clk_map, clk_dm);
        if (CY_RSLT_SUCCESS == result)
            obj->pin_clk = pin_clk;
    }

    /* Clock init needs to happen before we perform the PDL config so that we know our source frequency */
    if (CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_pdm_pcm_init_clock(obj, clk_source, existing_obj);
    }

    if (CY_RSLT_SUCCESS == result)
    {
#if defined(CY_IP_MXAUDIOSS)
        cy_stc_pdm_pcm_config_t pdl_struct = _cyhal_pdm_pcm_default_config;
        result = _cyhal_pdm_pcm_set_pdl_config_struct(obj, cfg, &pdl_struct);
#elif defined(CY_IP_MXPDM)
        cy_stc_pdm_pcm_config_v2_t pdl_struct = _cyhal_pdm_pcm_default_config;
        cy_stc_pdm_pcm_channel_config_t pdl_chan_struct = _cyhal_pdm_pcm_default_channel_config;
        cy_stc_pdm_pcm_channel_config_t pdl_chan_struct_paired = _cyhal_pdm_pcm_default_channel_config;
        result = _cyhal_pdm_pcm_set_pdl_config_struct(obj, cfg, (NULL != existing_obj), &pdl_struct,
                    &pdl_chan_struct, paired_channel >= 0 ? &pdl_chan_struct_paired : NULL);
#endif
        if (CY_RSLT_SUCCESS == result)
        {
#if defined(CY_IP_MXAUDIOSS)
            result = _cyhal_pdm_pcm_init_hw(obj, paired_channel, existing_obj, &pdl_struct);
#elif defined(CY_IP_MXTDM)
            result = _cyhal_pdm_pcm_init_hw(obj, paired_channel, existing_obj, &pdl_struct,
                        &pdl_chan_struct, &pdl_chan_struct_paired);

        if(NULL != existing_obj && paired_channel >= 0)
        {
            /* Update the route register to point the paired channel to the primary channel's pins */

            PDM_PCM_ROUTE_CTL(obj->base) |= (1 << paired_channel);
        }
#endif
        }
    }

    if (CY_RSLT_SUCCESS != result)
    {
        cyhal_pdm_pcm_free(obj);
    }
    return result;
}

cy_rslt_t cyhal_pdm_pcm_init_cfg(cyhal_pdm_pcm_t *obj, const cyhal_pdm_pcm_configurator_t* cfg)
{
    CY_ASSERT(NULL != obj);
    memset(obj, 0, sizeof(cyhal_pdm_pcm_t));
    obj->resource = *cfg->resource;
    obj->pin_data = CYHAL_NC_PIN_VALUE;
    obj->pin_clk = CYHAL_NC_PIN_VALUE;
    obj->dma.resource.type = CYHAL_RSC_INVALID;
#if defined(CY_IP_MXPDM)
    obj->dma_paired.resource.type = CYHAL_RSC_INVALID;
#endif
    obj->owned_by_configurator = true;

    /* Trigger fires when the FIFO has one more entry than the configured level */
#if defined(CY_IP_MXAUDIOSS)
    obj->user_trigger_level = cfg->config->rxFifoTriggerLevel + 1;
#elif defined(CY_IP_MXTDM)
    obj->user_trigger_level = cfg->chan_config->rxFifoTriggerLevel + 1;
#endif

    _cyhal_pdm_pcm_arrays_init();

    cyhal_pdm_pcm_t* existing_obj = _cyhal_pdm_pcm_find_existing_obj(obj->resource.block_num);
    cy_rslt_t result = _cyhal_pdm_pcm_init_clock(obj, cfg->clock, existing_obj);

    if(CY_RSLT_SUCCESS == result)
    {
        /* When initializing from configurator, separate channels are always configured independently */
#if defined(CY_IP_MXAUDIOSS)
        result = _cyhal_pdm_pcm_init_hw(obj, _CYHAL_PDM_PCM_UNPAIRED, existing_obj, cfg->config);
#elif defined(CY_IP_MXTDM)
        result = _cyhal_pdm_pcm_init_hw(obj, _CYHAL_PDM_PCM_UNPAIRED, existing_obj, cfg->config, cfg->chan_config, NULL);
#endif
    }

    if(CY_RSLT_SUCCESS != result)
    {
        cyhal_pdm_pcm_free(obj);
    }

    return result;
}

void cyhal_pdm_pcm_free(cyhal_pdm_pcm_t *obj)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(_cyhal_pdm_pcm_arrays_initialized); /* Should not be freeing if we never initialized anything */

    if (CYHAL_RSC_INVALID != obj->resource.type)
    {
#if defined(CY_IP_MXPDM)
        int16_t paired_channel = _cyhal_pdm_pcm_get_paired_channel(obj, true);
#endif
        bool last_remaining = true;
        for(int i = 0; last_remaining && i < _cyhal_pdm_num_channels[obj->resource.block_num]; ++i)
        {
            cyhal_pdm_pcm_t* existing = _cyhal_pdm_pcm_config_structs[obj->resource.block_num][i];
            last_remaining &= (NULL == existing || obj == existing);
        }
        _cyhal_syspm_unregister_peripheral_callback(&(obj->pm_callback));
        if(NULL != obj->base)
        {
#if defined(CY_IP_MXPDM)
            Cy_PDM_PCM_Channel_Disable(obj->base, obj->resource.channel_num);
            Cy_PDM_PCM_Channel_DeInit(obj->base, obj->resource.channel_num);
            if(paired_channel >= 0)
            {
                Cy_PDM_PCM_Channel_Disable(obj->base, paired_channel);
                Cy_PDM_PCM_Channel_DeInit(obj->base, paired_channel);

                /* Update the route register to point the paired channel to the primary channel's pins. */
                PDM_PCM_ROUTE_CTL(obj->base) &= ~(1 << paired_channel);
            }
#endif
            if(last_remaining)
            {
                Cy_PDM_PCM_DeInit(obj->base);
            }

            _cyhal_irq_free(_cyhal_pdm_pcm_irq_n[obj->resource.block_num][obj->resource.channel_num]);
        }

        if(obj == _cyhal_pdm_pcm_config_structs[obj->resource.block_num][obj->resource.channel_num])
        {
            _cyhal_pdm_pcm_config_structs[obj->resource.block_num][obj->resource.channel_num] = NULL;
        }
#if defined(CY_IP_MXPDM)
        if(paired_channel >= 0)
        {
            /* Clear out the paired channel if stereo */
            _cyhal_pdm_pcm_config_structs[obj->resource.block_num][paired_channel] = NULL;
        }
#endif

        if(last_remaining && false == obj->owned_by_configurator)
        {
            cyhal_hwmgr_free(&(obj->resource));
        }
        obj->base = NULL;
        obj->resource.type = CYHAL_RSC_INVALID;

        if(false == obj->owned_by_configurator)
        {
            _cyhal_utils_release_if_used(&(obj->pin_data));
            _cyhal_utils_release_if_used(&(obj->pin_clk));
        }

        if(last_remaining && obj->is_clock_owned)
        {
            cyhal_clock_free(&(obj->clock));
        }

        if (CYHAL_RSC_INVALID != obj->dma.resource.type)
        {
            cyhal_dma_free(&(obj->dma));
        }

#if defined(CY_IP_MXPDM)
        if (CYHAL_RSC_INVALID != obj->dma_paired.resource.type)
        {
            cyhal_dma_free(&(obj->dma_paired));
        }
#endif
    }
}

cy_rslt_t cyhal_pdm_pcm_start(cyhal_pdm_pcm_t *obj)
{
    CY_ASSERT(NULL != obj);
    if (obj->pm_transition_ready)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }
#if defined(CY_IP_MXAUDIOSS) /* MXPDM clears the FIFO whenever it is disabled */
    obj->stabilized = false;
    // Remove any element currently in the FIFO. This ensure the correct stabilization time delay.
    Cy_PDM_PCM_ClearFifo(obj->base);
    Cy_PDM_PCM_Enable(obj->base);
    // After Enable is asserted, there is a transition period of about 35-45 sample cycles on MXAUDIOSS
    _cyhal_pdm_pcm_set_rx_fifo_level(obj, _CYHAL_PDM_PCM_STABILIZATION_FS);
    _cyhal_pdm_pcm_set_interrupt_mask(obj, _cyhal_pdm_pcm_get_interrupt_mask(obj) | CY_PDM_PCM_INTR_RX_TRIGGER);
#elif defined(CY_IP_MXPDM)
    /* Enable/disable is more aggressive than we want, e.g. it will clear the FIFOs. Just activate/deactivate */
    Cy_PDM_PCM_Activate_Channel(obj->base, obj->resource.channel_num);
    int16_t paired_channel = _cyhal_pdm_pcm_get_paired_channel(obj, true);
    if(paired_channel >= 0)
    {
        Cy_PDM_PCM_Activate_Channel(obj->base, paired_channel);
    }
#endif
    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_pdm_pcm_stop(cyhal_pdm_pcm_t *obj)
{
    CY_ASSERT(NULL != obj);
#if defined(CY_IP_MXAUDIOSS)
    Cy_PDM_PCM_Disable(obj->base);
#elif defined(CY_IP_MXPDM)
    /* Enable/disable is more aggressive than we want, e.g. it will clear the FIFOs. Just activate/deactivate */
    Cy_PDM_PCM_DeActivate_Channel(obj->base, obj->resource.channel_num);
    int16_t paired_channel = _cyhal_pdm_pcm_get_paired_channel(obj, true);
    if(paired_channel >= 0)
    {
        Cy_PDM_PCM_DeActivate_Channel(obj->base, paired_channel);
    }
#endif
    return CY_RSLT_SUCCESS;
}

bool cyhal_pdm_pcm_is_enabled(cyhal_pdm_pcm_t *obj)
{
    CY_ASSERT(NULL != obj);
#if defined(CY_IP_MXAUDIOSS)
    return (0 != Cy_PDM_PCM_GetCurrentState(obj->base));
#elif defined(CY_IP_MXPDM)
    return (0 != Cy_PDM_PCM_Channel_GetCurrentState(obj->base, obj->resource.channel_num));
#endif
}

cy_rslt_t cyhal_pdm_pcm_set_gain(cyhal_pdm_pcm_t *obj, int16_t gain_left, int16_t gain_right)
{
    CY_ASSERT(NULL != obj);
    cy_rslt_t result = CY_RSLT_SUCCESS;

#if defined(CY_IP_MXAUDIOSS)
    if (_cyhal_pdm_pcm_invalid_gain_range(gain_left) || _cyhal_pdm_pcm_invalid_gain_range(gain_right))
    {
        result = CYHAL_PDM_PCM_RSLT_ERR_INVALID_CONFIG_PARAM;
    }
    Cy_PDM_PCM_SetGain(obj->base, CY_PDM_PCM_CHAN_LEFT, _cyhal_pdm_pcm_scale_gain_value(gain_left));
    Cy_PDM_PCM_SetGain(obj->base, CY_PDM_PCM_CHAN_RIGHT, _cyhal_pdm_pcm_scale_gain_value(gain_right));
#elif defined(CY_IP_MXPDM)
    int16_t paired_channel = _cyhal_pdm_pcm_get_paired_channel(obj, true);

    int fir1_scale_left = _cyhal_pdm_pcm_gain_to_scale(gain_left);
    if(CY_RSLT_SUCCESS == result && (fir1_scale_left < 0 || fir1_scale_left > _CYHAL_PDM_PCM_MAX_FIR1_SCALE))
    {
        result = CYHAL_PDM_PCM_RSLT_ERR_INVALID_CONFIG_PARAM;
    }

    int fir1_scale_right = _cyhal_pdm_pcm_gain_to_scale(gain_right);
    if(CY_RSLT_SUCCESS == result && (fir1_scale_right < 0 || fir1_scale_right > _CYHAL_PDM_PCM_MAX_FIR1_SCALE))
    {
        result = CYHAL_PDM_PCM_RSLT_ERR_INVALID_CONFIG_PARAM;
    }

    bool mono_and_right = false;
    if(paired_channel < 0) /* Unpaired, figure out if we were set up for left or right. */
    {
        /* Left = rising edge = (sampleDelay == clockDiv). Right = falling edge = (sampleDelay == clockDiv / 2) */
        uint8_t clkDiv = _FLD2VAL(PDM_CLOCK_CTL_CLOCK_DIV, PDM_PCM_CLOCK_CTL(obj->base));
        uint8_t sampleDelay = _FLD2VAL(PDM_CH_IF_CTL_SAMPLE_DELAY, PDM_PCM_CH_IF_CTL(obj->base, obj->resource.channel_num));
        mono_and_right = (sampleDelay != clkDiv);
    }

    if(CY_RSLT_SUCCESS == result)
    {
        /* The primary channel index is left, and the paired one is right */
        cy_en_pdm_pcm_ch_fir1_decimcode_t decim_code = (cy_en_pdm_pcm_ch_fir1_decimcode_t)
                                                        _FLD2VAL(PDM_CH_FIR1_CTL_DECIM2, PDM_PCM_CH_FIR1_CTL(obj->base, 0u));
        Cy_PDM_PCM_Channel_Set_Fir1(obj->base, obj->resource.channel_num, decim_code, mono_and_right ? fir1_scale_right : fir1_scale_left);

        if(paired_channel >= 0)
        {
            /* Decim code is the same between left and right because we set them up from the same user selection */
            Cy_PDM_PCM_Channel_Set_Fir1(obj->base, paired_channel, decim_code, fir1_scale_right);
        }

    }
#endif
    return result;
}

cy_rslt_t cyhal_pdm_pcm_clear(cyhal_pdm_pcm_t *obj)
{
    CY_ASSERT(NULL != obj);
#if defined(CY_IP_MXAUDIOSS)
    // Remove any element currently in the FIFO. This ensure the correct stabilization time delay.
    Cy_PDM_PCM_ClearFifo(obj->base);
#elif defined(CY_IP_MXPDM)
    /* No explicit clear operation in the HW, just read everything in the FIFO. */
    while(Cy_PDM_PCM_Channel_GetNumInFifo(obj->base, obj->resource.channel_num) > 0)
    {
        (void)Cy_PDM_PCM_Channel_ReadFifo(obj->base, obj->resource.channel_num);
    }

    int16_t paired_channel = _cyhal_pdm_pcm_get_paired_channel(obj, true);
    if(paired_channel >= 0)
    {
        while(Cy_PDM_PCM_Channel_GetNumInFifo(obj->base, paired_channel) > 0)
        {
            (void)Cy_PDM_PCM_Channel_ReadFifo(obj->base, paired_channel);
        }
    }
#endif
    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_pdm_pcm_read(cyhal_pdm_pcm_t *obj, void *data, size_t *length)
{
    CY_ASSERT(NULL != obj);
    if (!(obj->stabilized))
    {
        *length = 0;
    }

#if defined(CY_IP_MXAUDIOSS)
    uint8_t fifo_count = Cy_PDM_PCM_GetNumInFifo(obj->base);
#elif defined(CY_IP_MXPDM)
    int16_t paired_channel = _cyhal_pdm_pcm_get_paired_channel(obj, true);
    uint8_t fifo_count = Cy_PDM_PCM_Channel_GetNumInFifo(obj->base, obj->resource.channel_num);
    if(paired_channel >= 0)
    {
        fifo_count += Cy_PDM_PCM_Channel_GetNumInFifo(obj->base, paired_channel);
        /* We'll be reading one entry from each FIFO, so round down if neceessary to get an even number */
        fifo_count &= ~(1u);
    }
#endif

    if (*length > fifo_count)
    {
        *length = fifo_count;
    }
    size_t i;

    if (obj->word_size == 1)
    {
        uint8_t *buffer = (uint8_t *)data;
        for (i = 0; i < *length; i++)
        {
#if defined(CY_IP_MXAUDIOSS)
            buffer[i] = (Cy_PDM_PCM_ReadFifo(obj->base) & 0xFF);
#elif defined(CY_IP_MXPDM)
            buffer[i] = (Cy_PDM_PCM_Channel_ReadFifo(obj->base, obj->resource.channel_num)) & 0xFF;
            if(paired_channel >= 0)
            {
                ++i;
                buffer[i] = (Cy_PDM_PCM_Channel_ReadFifo(obj->base, paired_channel)) & 0xFF;
            }
#endif
        }
    }
    if (obj->word_size == 2)
    {
        uint16_t *buffer = (uint16_t *)data;
        for (i = 0; i < *length; i++)
        {
#if defined(CY_IP_MXAUDIOSS)
            buffer[i] = (Cy_PDM_PCM_ReadFifo(obj->base) & 0xFFFF);
#elif defined(CY_IP_MXPDM)
            buffer[i] = (Cy_PDM_PCM_Channel_ReadFifo(obj->base, obj->resource.channel_num)) & 0xFFFF;
            if(paired_channel >= 0)
            {
                ++i;
                buffer[i] = (Cy_PDM_PCM_Channel_ReadFifo(obj->base, paired_channel)) & 0xFFFF;
            }
#endif
        }
    }
    else
    {
        uint32_t *buffer = (uint32_t *)data;
        for (i = 0; i < *length; i++)
        {
#if defined(CY_IP_MXAUDIOSS)
            buffer[i] = Cy_PDM_PCM_ReadFifo(obj->base);
#elif defined(CY_IP_MXPDM)
            buffer[i] = Cy_PDM_PCM_Channel_ReadFifo(obj->base, obj->resource.channel_num);
            if(paired_channel >= 0)
            {
                ++i;
                buffer[i] = Cy_PDM_PCM_Channel_ReadFifo(obj->base, paired_channel);
            }
#endif
        }
    }
    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_pdm_pcm_read_async(cyhal_pdm_pcm_t *obj, void *data, size_t length)
{
    CY_ASSERT(NULL != obj);
    if (obj->pm_transition_ready)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }
    if (cyhal_pdm_pcm_is_pending(obj))
    {
        return CYHAL_PDM_PCM_RSLT_ERR_ASYNC_IN_PROGRESS;
    }

    // Disable PDM interrupts temporarily.
    _cyhal_irq_disable(_cyhal_pdm_pcm_irq_n[obj->resource.block_num][obj->resource.channel_num]);

    obj->async_buffer = data;
    obj->async_read_remaining = length;

    if (obj->stabilized)
    {
        if (obj->dma.resource.type == CYHAL_RSC_INVALID)
        {
            // read as much as we can, if there are left overs, then set interrupt flags
            _cyhal_pdm_pcm_try_read_async(obj);

            if (0 == obj->async_read_remaining)
            {
                cyhal_pdm_pcm_event_callback_t callback = (cyhal_pdm_pcm_event_callback_t) obj->callback_data.callback;
                if (callback != NULL)
                {
                    obj->async_buffer = NULL;
                    callback(obj->callback_data.callback_arg, CYHAL_PDM_PCM_ASYNC_COMPLETE);
                }
            }
        }
    }
    // Setup interrupt for FIFO half full.
    if (0 != obj->async_read_remaining)
    {
        _cyhal_pdm_pcm_set_interrupt_mask(obj, _cyhal_pdm_pcm_get_interrupt_mask(obj) | CY_PDM_PCM_INTR_RX_TRIGGER);
    }
    _cyhal_irq_enable(_cyhal_pdm_pcm_irq_n[obj->resource.block_num][obj->resource.channel_num]);
    return CY_RSLT_SUCCESS;
}

bool cyhal_pdm_pcm_is_pending(cyhal_pdm_pcm_t *obj)
{
    CY_ASSERT(NULL != obj);
    return obj->async_read_remaining != 0 && obj->async_buffer != NULL;
}

cy_rslt_t cyhal_pdm_pcm_abort_async(cyhal_pdm_pcm_t *obj)
{
    CY_ASSERT(NULL != obj);
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    obj->async_read_remaining = 0;
    obj->async_buffer = NULL;
    // Only disable the interrupt mask if the user did not explicitly enable the mask
    if (!(obj->irq_cause & CYHAL_PDM_PCM_RX_HALF_FULL))
    {
        _cyhal_pdm_pcm_set_interrupt_mask(obj, _cyhal_pdm_pcm_get_interrupt_mask(obj) & ~CY_PDM_PCM_INTR_RX_TRIGGER);
    }
    cyhal_system_critical_section_exit(savedIntrStatus);
    return CY_RSLT_SUCCESS;
}

void cyhal_pdm_pcm_register_callback(cyhal_pdm_pcm_t *obj, cyhal_pdm_pcm_event_callback_t callback, void *callback_arg)
{
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    obj->callback_data.callback = (cy_israddress) callback;
    obj->callback_data.callback_arg = callback_arg;
    cyhal_system_critical_section_exit(savedIntrStatus);
}

void cyhal_pdm_pcm_enable_event(cyhal_pdm_pcm_t *obj, cyhal_pdm_pcm_event_t event, uint8_t intr_priority, bool enable)
{
    uint32_t mask = _cyhal_pdm_pcm_get_pdl_event_mask(event);
    if (enable)
    {
        obj->irq_cause |= event;
        _cyhal_pdm_pcm_clear_interrupt(obj, mask);
        _cyhal_pdm_pcm_set_interrupt_mask(obj, _cyhal_pdm_pcm_get_interrupt_mask(obj) | mask);
    }
    else
    {
        obj->irq_cause &= ~event;
        uint32_t intr_status = cyhal_system_critical_section_enter();
        if (!obj->stabilized && cyhal_pdm_pcm_is_pending(obj))
        {
            // The half full event is used internally by the stabilization code.
            // The start() API clear the FIFO, if we have more data than the half FIFO, then PDM/PCM has stabilized.
            // This half interrupt mask will automatically cleared by the stabilization code.

            // Is an async operation is pending the mask will also be cleared automatically when the async operation finishes
            mask &= ~CY_PDM_PCM_INTR_RX_TRIGGER;
        }
        _cyhal_pdm_pcm_set_interrupt_mask(obj, _cyhal_pdm_pcm_get_interrupt_mask(obj) & ~mask);
        cyhal_system_critical_section_exit(intr_status);
    }

    _cyhal_irq_set_priority(_cyhal_pdm_pcm_irq_n[obj->resource.block_num][obj->resource.channel_num], intr_priority);
}

cy_rslt_t cyhal_pdm_pcm_set_async_mode(cyhal_pdm_pcm_t *obj, cyhal_async_mode_t mode, uint8_t dma_priority)
{
    CY_ASSERT(NULL != obj);
    cy_rslt_t rslt = CY_RSLT_SUCCESS;

    if (CYHAL_ASYNC_SW == mode)
    {
        if (CYHAL_DMA_PRIORITY_DEFAULT != dma_priority)
        {
            rslt = CYHAL_PDM_PCM_RSLT_ERR_INVALID_CONFIG_PARAM;
        }
        else if (CYHAL_RSC_INVALID != obj->dma.resource.type)
        {
            cyhal_dma_free(&(obj->dma));
            obj->dma.resource.type = CYHAL_RSC_INVALID;
#if defined(CY_IP_MXPDM)
            if(CYHAL_RSC_INVALID != obj->dma_paired.resource.type)
            {
                cyhal_dma_free(&(obj->dma_paired));
                obj->dma_paired.resource.type = CYHAL_RSC_INVALID;
            }
#endif
        }
    }
    else if (CYHAL_ASYNC_DMA == mode && CYHAL_RSC_INVALID == obj->dma.resource.type)
    {
        rslt = cyhal_dma_init(&(obj->dma), dma_priority, CYHAL_DMA_DIRECTION_PERIPH2MEM);
#if defined(CY_IP_MXPDM)
        int16_t paired_channel = _cyhal_pdm_pcm_get_paired_channel(obj, true);
        if(paired_channel >= 0)
        {
            rslt = cyhal_dma_init(&(obj->dma_paired), dma_priority, CYHAL_DMA_DIRECTION_PERIPH2MEM);
            if(CY_RSLT_SUCCESS == rslt)
            {
                cyhal_dma_register_callback(&(obj->dma_paired), &_cyhal_pdm_pcm_dma_callback, obj);
            }
        }
#endif
        if(CY_RSLT_SUCCESS == rslt)
        {
            cyhal_dma_register_callback(&(obj->dma), &_cyhal_pdm_pcm_dma_callback, obj);
        }
    }
    return rslt;
}

#if defined(__cplusplus)
}
#endif

#endif /* CYHAL_DRIVER_AVAILABLE_PDMPCM */
