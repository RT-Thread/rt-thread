/*******************************************************************************
* File Name: cyhal_audio_common.c
*
* Description:
* Provides common functionality for the I2S and TDM audio drivers.
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
#include "cyhal_gpio.h"
#include "cyhal_hw_resources.h"
#include "cyhal_hwmgr.h"
#include "cyhal_utils.h"
#include "cyhal_irq_impl.h"
#include "cyhal_dma.h"
#include "cyhal_syspm.h"
#include "cy_device.h"
#include "cyhal_audio_common.h"
#include "cyhal_system.h"

#if (CYHAL_DRIVER_AVAILABLE_I2S || CYHAL_DRIVER_AVAILABLE_TDM)

#if defined(__cplusplus)
extern "C"
{
#endif

#if defined(COMPONENT_CAT2)
/* PDL register naming varies slightly between CAT1 and CAT2 */
#define REG_I2S_CTL(base)         I2S_CTL(base)
#define REG_I2S_CLOCK_CTL(base)   I2S_CLOCK_CTL(base)
#define REG_I2S_TX_CTL(base)      I2S_TX_CTL(base)
#define REG_I2S_TX_FIFO_CTL(base) I2S_TX_FIFO_CTL(base)
#else
#define _CYHAL_AUDIOSS_TX_SLAVE_AVAILABLE
#define _CYHAL_AUDIOSS_TX_WATCHDOG_AVAILABLE
/* Some devices have an extra layer of hierarchy in their parameters */
#if defined(AUDIOSS0_I2S_I2S)
#define AUDIOSS0_I2S (AUDIOSS0_I2S_I2S)
#endif
#if defined(AUDIOSS1_I2S_I2S)
#define AUDIOSS1_I2S (AUDIOSS1_I2S_I2S)
#endif
#if defined(AUDIOSS2_I2S_I2S)
#define AUDIOSS2_I2S (AUDIOSS2_I2S_I2S)
#endif
#endif

#define _CYHAL_AUDIOSS_MAX_CHANNEL_LENGTH (32u)

#if defined(CY_IP_MXAUDIOSS)
static cy_rslt_t _cyhal_audioss_length_to_pdl(uint8_t user_length, cy_en_i2s_len_t *pdl_length, const _cyhal_audioss_t *obj);
static uint8_t _cyhal_audioss_length_from_pdl(cy_en_i2s_len_t pdl_length);
#define _CYHAL_AUDIOSS_FIFO_DEPTH (256)

#define _CYHAL_AUDIOSS_TX_SCK_MAP cyhal_pin_map_audioss_tx_sck
#define _CYHAL_AUDIOSS_TX_WS_MAP  cyhal_pin_map_audioss_tx_ws
#define _CYHAL_AUDIOSS_TX_SDO_MAP cyhal_pin_map_audioss_tx_sdo

#define _CYHAL_AUDIOSS_DRIVE_MODE_TX_SCK    CYHAL_PIN_MAP_DRIVE_MODE_AUDIOSS_TX_SCK
#define _CYHAL_AUDIOSS_DRIVE_MODE_TX_WS     CYHAL_PIN_MAP_DRIVE_MODE_AUDIOSS_TX_WS
#define _CYHAL_AUDIOSS_DRIVE_MODE_TX_SDO    CYHAL_PIN_MAP_DRIVE_MODE_AUDIOSS_TX_SDO

#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
#define _CYHAL_AUDIOSS_RX_SCK_MAP cyhal_pin_map_audioss_rx_sck
#define _CYHAL_AUDIOSS_RX_WS_MAP  cyhal_pin_map_audioss_rx_ws
#define _CYHAL_AUDIOSS_RX_SDI_MAP cyhal_pin_map_audioss_rx_sdi

#define _CYHAL_AUDIOSS_DRIVE_MODE_RX_SCK    CYHAL_PIN_MAP_DRIVE_MODE_AUDIOSS_RX_SCK
#define _CYHAL_AUDIOSS_DRIVE_MODE_RX_WS     CYHAL_PIN_MAP_DRIVE_MODE_AUDIOSS_RX_WS
#define _CYHAL_AUDIOSS_DRIVE_MODE_RX_SDI    CYHAL_PIN_MAP_DRIVE_MODE_AUDIOSS_RX_SDI
#endif


static I2S_Type *const _cyhal_audioss_base[] =
{
#if (CY_IP_MXAUDIOSS_INSTANCES == 1 && defined(AUDIOSS_I2S) && AUDIOSS_I2S)
    I2S,
#elif (CY_IP_MXAUDIOSS_INSTANCES >= 1 && ((defined(AUDIOSS_I2S_I2S) && AUDIOSS_I2S_I2S) || (defined(AUDIOSS0_I2S) && AUDIOSS0_I2S) || (defined(AUDIOSS0_I2S_I2S) && AUDIOSS0_I2S_I2S)))
    I2S0,
#endif
#if (CY_IP_MXAUDIOSS_INSTANCES >= 2 && ((defined(AUDIOSS1_I2S) && AUDIOSS1_I2S) || (defined(AUDIOSS1_I2S_I2S) && AUDIOSS1_I2S_I2S)))
    I2S1,
#endif
#if (CY_IP_MXAUDIOSS_INSTANCES >= 3 && ((defined(AUDIOSS2_I2S) && AUDIOSS2_I2S) || (defined(AUDIOSS2_I2S_I2S) && AUDIOSS2_I2S_I2S)))
    I2S2,
#endif

#if (CY_IP_MXS40AUDIOSS_INSTANCES > 2)
    #warning Unhandled audioss instance count
#endif
};

#if (!defined(COMPONENT_CAT2))
#define _CYHAL_AUDIOSS_TRIGGERS_AVAILABLE
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
static const cyhal_source_t _cyhal_audioss_rx_trigger[] =
{
#if (CY_IP_MXAUDIOSS_INSTANCES == 1 && defined(AUDIOSS_I2S) && AUDIOSS_I2S)
    CYHAL_TRIGGER_AUDIOSS_TR_I2S_RX_REQ,
#elif (CY_IP_MXAUDIOSS_INSTANCES >= 1 && defined(AUDIOSS0_I2S) && AUDIOSS0_I2S)
    CYHAL_TRIGGER_AUDIOSS0_TR_I2S_RX_REQ,
#endif
#if (CY_IP_MXAUDIOSS_INSTANCES >= 2 && defined(AUDIOSS1_I2S) && AUDIOSS1_I2S)
    CYHAL_TRIGGER_AUDIOSS1_TR_I2S_RX_REQ,
#endif
#if (CY_IP_MXAUDIOSS_INSTANCES >= 2 && defined(AUDIOSS2_I2S) && AUDIOSS2_I2S)
    CYHAL_TRIGGER_AUDIOSS2_TR_I2S_RX_REQ,
#endif

#if (CY_IP_MXS40AUDIOSS_INSTANCES > 3)
    #warning Unhandled audioss instance count
#endif
};
#endif

static const cyhal_source_t _cyhal_audioss_tx_trigger[] =
{
#if (CY_IP_MXAUDIOSS_INSTANCES == 1 && defined(AUDIOSS_I2S) && AUDIOSS_I2S)
    CYHAL_TRIGGER_AUDIOSS_TR_I2S_TX_REQ,
#elif (CY_IP_MXAUDIOSS_INSTANCES >= 1 && defined(AUDIOSS0_I2S) && AUDIOSS0_I2S)
    CYHAL_TRIGGER_AUDIOSS0_TR_I2S_TX_REQ,
#endif
#if (CY_IP_MXAUDIOSS_INSTANCES >= 2 && defined(AUDIOSS1_I2S) && AUDIOSS1_I2S)
    CYHAL_TRIGGER_AUDIOSS1_TR_I2S_TX_REQ,
#endif
#if (CY_IP_MXAUDIOSS_INSTANCES >= 3 && defined(AUDIOSS2_I2S) && AUDIOSS2_I2S)
    CYHAL_TRIGGER_AUDIOSS2_TR_I2S_TX_REQ,
#endif

#if (CY_IP_MXS40AUDIOSS_INSTANCES > 3)
    #warning Unhandled audioss instance count
#endif
};
#endif

static _cyhal_audioss_t* _cyhal_audioss_config_structs[CY_IP_MXAUDIOSS_INSTANCES];

static const _cyhal_system_irq_t _cyhal_audioss_irq_n[] =
{
#if (CY_IP_MXAUDIOSS_INSTANCES == 1 && (defined(AUDIOSS_I2S) && AUDIOSS_I2S || defined(AUDIOSS_I2S_I2S) && AUDIOSS_I2S_I2S)) // Without index suffix
    audioss_interrupt_i2s_IRQn,
#elif (CY_IP_MXAUDIOSS_INSTANCES >= 1 && defined(AUDIOSS0_I2S) && AUDIOSS0_I2S)
    audioss_0_interrupt_i2s_IRQn,
#endif
#if (CY_IP_MXAUDIOSS_INSTANCES >= 2 && defined(AUDIOSS1_I2S) && AUDIOSS1_I2S)
    audioss_1_interrupt_i2s_IRQn,
#endif
#if (CY_IP_MXAUDIOSS_INSTANCES >= 3 && defined(AUDIOSS2_I2S) && AUDIOSS2_I2S)
    audioss_2_interrupt_i2s_IRQn,
#endif

#if (CY_IP_MXS40AUDIOSS_INSTANCES > 3)
    #warning Unhandled audioss instance count
#endif
};

static uint8_t _cyhal_audioss_get_block_from_irqn(_cyhal_system_irq_t irqn)
{
    switch (irqn)
    {
#if !defined(CY_CPU_CORTEX_M4) || (CY_CPU_CORTEX_M4) || defined(COMPONENT_CAT1C)
#if (CY_IP_MXAUDIOSS_INSTANCES == 1 && (defined(AUDIOSS_I2S) && AUDIOSS_I2S || defined(AUDIOSS_I2S_I2S) && AUDIOSS_I2S_I2S)) // Without index suffix
        case audioss_interrupt_i2s_IRQn:
            return 0;
#elif (CY_IP_MXAUDIOSS_INSTANCES >= 1 && defined(AUDIOSS0_I2S) && AUDIOSS0_I2S)
        case audioss_0_interrupt_i2s_IRQn:
            return 0;
#endif
#if (CY_IP_MXAUDIOSS_INSTANCES >= 2 && defined(AUDIOSS1_I2S) && AUDIOSS1_I2S)
        case audioss_1_interrupt_i2s_IRQn:
            return 1;
#endif
#if (CY_IP_MXAUDIOSS_INSTANCES >= 3 && defined(AUDIOSS2_I2S) && AUDIOSS2_I2S)
        case audioss_2_interrupt_i2s_IRQn:
            return 2;
#endif
#if (CY_IP_MXS40AUDIOSS_INSTANCES > 3)
    #warning Unhandled audioss instance count
#endif
#endif /* (CY_CPU_CORTEX_M4) */
        default:
            CY_ASSERT(false); // Should never be called with a non-I2S IRQn
            return 0;
    }
}

#if defined(COMPONENT_CAT2) /* PSoCâ„¢ 4 uses a PCLK */
#define _CYHAL_AUDIOSS_USES_PCLK
static const en_clk_dst_t _cyhal_audioss_clock[] =
{
#if (CY_IP_MXAUDIOSS_INSTANCES == 1)
    PCLK_AUDIOSS_CLOCK_POS_I2S_EN,
#else
    #warning Unhandled audioss instance count
#endif
};
#endif

static void _cyhal_audioss_irq_handler(void);
typedef cy_stc_i2s_config_t _cyhal_audioss_pdl_config_t;

#elif defined(CY_IP_MXTDM) && (CY_IP_MXTDM_INSTANCES > 0)
#define _CYHAL_AUDIOSS_FIFO_DEPTH (128)

#define _CYHAL_AUDIOSS_TX_SCK_MAP cyhal_pin_map_tdm_tdm_tx_sck
#define _CYHAL_AUDIOSS_TX_WS_MAP  cyhal_pin_map_tdm_tdm_tx_fsync
#define _CYHAL_AUDIOSS_TX_SDO_MAP cyhal_pin_map_tdm_tdm_tx_sd
#define _CYHAL_AUDIOSS_TX_MCK_MAP cyhal_pin_map_tdm_tdm_tx_mck
#define _CYHAL_AUDIOSS_RX_SCK_MAP cyhal_pin_map_tdm_tdm_rx_sck
#define _CYHAL_AUDIOSS_RX_WS_MAP  cyhal_pin_map_tdm_tdm_rx_fsync
#define _CYHAL_AUDIOSS_RX_SDI_MAP cyhal_pin_map_tdm_tdm_rx_sd
#define _CYHAL_AUDIOSS_RX_MCK_MAP cyhal_pin_map_tdm_tdm_rx_mck

#define _CYHAL_AUDIOSS_DRIVE_MODE_TX_SCK    CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_TX_SCK
#define _CYHAL_AUDIOSS_DRIVE_MODE_TX_WS     CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_TX_FSYNC
#define _CYHAL_AUDIOSS_DRIVE_MODE_TX_SDO    CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_TX_SD
#define _CYHAL_AUDIOSS_DRIVE_MODE_RX_SCK    CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_RX_SCK
#define _CYHAL_AUDIOSS_DRIVE_MODE_RX_WS     CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_RX_FSYNC
#define _CYHAL_AUDIOSS_DRIVE_MODE_RX_SDI    CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_RX_SD

/* Per cy_en_tdm_clock_sel_t, only TX mclk_in is selectable for both.
 * This is probably a bug in the PDL, will be updated as necessary
 * following the resolution of DRIVERS-5376
 */
#define Cy_I2S_Init           Cy_AudioTDM_Init
#define Cy_I2S_DeInit         Cy_AudioTDM_DeInit

static cy_rslt_t _cyhal_audioss_length_to_pdl(uint8_t user_length, cy_en_tdm_ws_t *pdl_length, const _cyhal_audioss_t *obj);
static uint8_t _cyhal_audioss_length_from_pdl(cy_en_tdm_ws_t pdl_length);

static TDM_Type *const _cyhal_audioss_base[] =
{
#if defined (TDM0)
    TDM0,
#endif
#if defined (TDM1)
    TDM1,
#endif
};

static const uint8_t _cyhal_audioss_max_channels[] =
{
#if (CY_IP_MXTDM_INSTANCES == 1)
    #if (TDM_NR == 1)
        TDM_NR_CH_NR,
    #elif (TDM_NR == 2)
        TDM_NR0_CH_NR,
        TDM_NR1_CH_NR,
    #else
        #warning Unhandled TDM struct count
    #endif
#elif (CY_IP_MXTDM_INSTANCES == 2)
    #if (TDM_NR == 2)
        TDM_NR_CH_NR,
    #else
        #warning Unhandled TDM struct count
    #endif
#else
    #warning Unhandled tdm instance count
#endif
};

#if !defined (COMPONENT_CAT5)
#define _CYHAL_AUDIOSS_USES_PCLK
static const en_clk_dst_t _cyhal_audioss_clock[] =
{
#if (CY_IP_MXTDM_INSTANCES == 1)
    PCLK_TDM0_CLK_IF_SRSS0,
#else
    #warning Unhandled tdm instance count
#endif
};

#define _CYHAL_AUDIOSS_TRIGGERS_AVAILABLE
static const cyhal_source_t _cyhal_audioss_rx_trigger[] =
{
#if (CY_IP_MXTDM_INSTANCES == 1)
    CYHAL_TRIGGER_TDM_TR_RX_REQ0,
#else
    #warning Unhandled tdm instance count
#endif
};

static const cyhal_source_t _cyhal_audioss_tx_trigger[] =
{
#if (CY_IP_MXTDM_INSTANCES == 1)
    CYHAL_TRIGGER_TDM_TR_TX_REQ0,
#else
    #warning Unhandled tdm instance count
#endif
};
#endif /* !defined (COMPONENT_CAT5) */

static _cyhal_audioss_t* _cyhal_audioss_config_structs[CY_IP_MXTDM_INSTANCES];

// These structures will most probably be cleaned up a bit once we have more details
// on TDM interrupts for Hatchet1. Seems like there are no separate lines for tx and
// rx interrupts but it will be confirmed once we have a working patch.
static const _cyhal_system_irq_t _cyhal_audioss_tx_irq_n[] =
{
#if defined (TDM0)
    #if defined(COMPONENT_CAT5)
        tdm_0_interrupts_IRQn,
    #else
        tdm_0_interrupts_tx_0_IRQn,
    #endif
#endif
#if defined (TDM1)
    #if defined(COMPONENT_CAT5)
        tdm_1_interrupts_IRQn,
    #else
        tdm_1_interrupts_tx_0_IRQn,
    #endif
#endif
};

static const _cyhal_system_irq_t _cyhal_audioss_rx_irq_n[] =
{
#if defined (TDM0)
    #if defined(COMPONENT_CAT5)
        tdm_0_interrupts_IRQn,
    #else
        tdm_0_interrupts_rx_0_IRQn,
    #endif
#endif
#if defined (TDM1)
    #if defined(COMPONENT_CAT5)
        tdm_1_interrupts_IRQn,
    #else
        tdm_1_interrupts_rx_0_IRQn,
    #endif
#endif
};

static uint8_t _cyhal_audioss_get_block_from_irqn(_cyhal_system_irq_t irqn)
{
#if defined (TDM0)
    #if defined (COMPONENT_CAT5)
        if (irqn == tdm_0_interrupts_IRQn)
    #else
        if ((irqn == tdm_0_interrupts_tx_0_IRQn) || (irqn == tdm_0_interrupts_rx_0_IRQn))
    #endif
            return 0;
#endif
#if defined (TDM1)
    #if defined (COMPONENT_CAT5)
        if (irqn == tdm_1_interrupts_IRQn)
    #else
        if ((irqn == tdm_1_interrupts_tx_0_IRQn) || (irqn == tdm_1_interrupts_rx_0_IRQn))
    #endif
            return 1;
#endif
    CY_ASSERT(false); // Should never be called with a non-TDM IRQn
    return 0;
}

#if defined (COMPONENT_CAT5)
static void _cyhal_audioss_irq_handler(UINT8 instance, BOOL8 rx_int);
static void _cyhal_audioss_irq_handler_rx(_cyhal_system_irq_t irqn);
static void _cyhal_audioss_irq_handler_tx(_cyhal_system_irq_t irqn);
#else
static void _cyhal_audioss_irq_handler_rx(void);
static void _cyhal_audioss_irq_handler_tx(void);
#endif
typedef cy_stc_tdm_config_t _cyhal_audioss_pdl_config_t;

#else
#error "Unrecognized audio IP"
#endif

static void _cyhal_audioss_update_enabled_events(_cyhal_audioss_t* obj);
static void _cyhal_audioss_process_event(_cyhal_audioss_t *obj, uint32_t event);
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
static void _cyhal_audioss_update_rx_trigger_level(_cyhal_audioss_t* obj);
static uint32_t _cyhal_audioss_read_fifo(_cyhal_audioss_t *obj);
#if (CYHAL_DRIVER_AVAILABLE_DMA)
static cy_rslt_t _cyhal_audioss_dma_perform_rx(_cyhal_audioss_t *obj);
static void _cyhal_audioss_dma_handler_rx(void *callback_arg, cyhal_dma_event_t event);
#endif /* (CYHAL_DRIVER_AVAILABLE_DMA) */
#endif /* defined(_CYHAL_AUDIOSS_RX_ENABLED) */
static uint32_t _cyhal_audioss_disable_events(_cyhal_audioss_t *obj, bool tx);
static void _cyhal_audioss_restore_events(_cyhal_audioss_t *obj, bool tx, uint32_t old_events);
#if (CYHAL_DRIVER_AVAILABLE_DMA)
static cy_rslt_t _cyhal_audioss_dma_perform_tx(_cyhal_audioss_t *obj);
static void _cyhal_audioss_dma_handler_tx(void *callback_arg, cyhal_dma_event_t event);
static uint8_t _cyhal_audioss_rounded_word_length(_cyhal_audioss_t *obj, bool is_tx);
#endif /* (CYHAL_DRIVER_AVAILABLE_DMA) */
static bool _cyhal_audioss_pm_callback(cyhal_syspm_callback_state_t state, cyhal_syspm_callback_mode_t mode, void* callback_arg);
static cy_rslt_t _cyhal_audioss_populate_pdl_config(_cyhal_audioss_t *obj, _cyhal_audioss_pdl_config_t* pdl_config,
                                                    const _cyhal_audioss_config_t* hal_cfg,
                                                    uint16_t sclk_div_rx, uint16_t sclk_div_tx,
                                                    bool rx_en, bool tx_en, bool mclk_rx, bool mclk_tx);
static void _cyhal_audioss_reconstruct_pdl_config(_cyhal_audioss_t *obj, _cyhal_audioss_pdl_config_t* pdl_config);
static cy_rslt_t _cyhal_audioss_compute_sclk_div(_cyhal_audioss_t *obj, uint32_t sample_rate_hz, uint32_t mclk_hz, uint8_t channel_length, uint8_t num_channels, uint16_t *sclk_div);
static uint32_t _cyhal_audioss_get_num_in_fifo(_cyhal_audioss_t *obj, bool is_tx);
static void _cyhal_audioss_write_fifo(_cyhal_audioss_t *obj, uint32_t value);

cy_rslt_t _cyhal_audioss_init_clock(_cyhal_audioss_t *obj, const cyhal_clock_t* clk, bool all_mclk)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    if (clk != NULL)
    {
        obj->clock = *clk;
    }
    else if (false == all_mclk) // No need to reserve a clock if we're using the mclk pin
    {
        // The hardware is generally going to be hardwired to an hfclk (or equivalent dedicated clock),
        // which has very limited divider options. In the event that we're hooked up a PERI divider,
        // we don't have any particular expectations about its width - so just ask for 16-bit or larger
        result = _cyhal_utils_allocate_clock(&(obj->clock), &(obj->resource), CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT, true);
        if(CY_RSLT_SUCCESS == result)
        {
            obj->is_clock_owned = true;
            result = cyhal_clock_set_enabled(&(obj->clock), true, true);
        }
    }

#if defined(_CYHAL_AUDIOSS_USES_PCLK)
    // If we're not using MCLK, and we're using a peri divider, hook it up to ourself
    bool any_mclk = (0u != obj->mclk_hz_tx);
    #if defined(_CYHAL_AUDIOSS_RX_ENABLED)
        any_mclk = any_mclk || (0u != obj->mclk_hz_rx);
    #endif
    if (CY_RSLT_SUCCESS == result && false == any_mclk && obj->clock.block != CYHAL_CLOCK_BLOCK_HF)
    {
        en_clk_dst_t pclk = _cyhal_audioss_clock[obj->resource.block_num];
        if (CY_SYSCLK_SUCCESS != _cyhal_utils_peri_pclk_assign_divider(pclk, &(obj->clock)))
            result = obj->interface->err_clock;
    }
#endif

    return result;
}

cy_rslt_t _cyhal_audioss_init_pdl(_cyhal_audioss_t *obj, const _cyhal_audioss_pdl_config_t* pdl_config)
{
    cy_rslt_t result = (cy_rslt_t)Cy_I2S_Init(obj->base, pdl_config);

#if defined(CY_IP_MXTDM)
    if(CY_RSLT_SUCCESS == result)
    {
        // PDL init doesn't automatically enable the RX-TX sub-blocks
        if(pdl_config->tx_config->enable)
        {
            Cy_AudioTDM_EnableTx(&obj->base->TDM_TX_STRUCT);
        }
        if(pdl_config->rx_config->enable)
        {
            Cy_AudioTDM_EnableRx(&obj->base->TDM_RX_STRUCT);
        }
    }
#endif
    return result;
}

cy_rslt_t _cyhal_audioss_init_hw(_cyhal_audioss_t *obj, const _cyhal_audioss_pdl_config_t* pdl_config)
{
#if defined(CY_IP_MXAUDIOSS)
    obj->base = _cyhal_audioss_base[obj->resource.block_num];
#elif defined(CY_IP_MXTDM)
    obj->base = &(_cyhal_audioss_base[obj->resource.block_num]->TDM_STRUCT[obj->resource.channel_num]);
#endif

    cy_rslt_t result = _cyhal_audioss_init_pdl(obj, pdl_config);

    if (CY_RSLT_SUCCESS == result)
    {
#if defined(CY_IP_MXAUDIOSS) && defined(_CYHAL_AUDIOSS_RX_ENABLED)
        obj->user_fifo_level_rx = pdl_config->rxFifoTriggerLevel;
#elif defined(CY_IP_MXTDM)
        obj->user_fifo_level_rx = pdl_config->rx_config->fifoTriggerLevel;
#endif
        /* No way to explicitly clear the FIFO on the TDM IP, but
         * it is cleared as a side effect of the FIFO being disabled
         * which it should be both at startup and after a free/init cycle
         */
#if defined(CY_IP_MXAUDIOSS)
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
        if(pdl_config->txEnabled)
        {
            Cy_I2S_ClearTxFifo(obj->base);
        }
        if(pdl_config->rxEnabled)
        {
            Cy_I2S_ClearRxFifo(obj->base);
        }
#else
        Cy_I2S_ClearTxFifo(obj->base);
#endif
#endif

        obj->pm_callback.states = (cyhal_syspm_callback_state_t)(CYHAL_SYSPM_CB_CPU_DEEPSLEEP | CYHAL_SYSPM_CB_SYSTEM_HIBERNATE);
        obj->pm_callback.callback = &_cyhal_audioss_pm_callback;
        obj->pm_callback.next = NULL;
        obj->pm_callback.args = (void*)obj;
        obj->pm_callback.ignore_modes = (cyhal_syspm_callback_mode_t)(CYHAL_SYSPM_BEFORE_TRANSITION | CYHAL_SYSPM_AFTER_DS_WFI_TRANSITION);
        obj->pm_transition_ready = false;
#if (CYHAL_DRIVER_AVAILABLE_SYSPM)
        _cyhal_syspm_register_peripheral_callback(&(obj->pm_callback));
#endif /*  (CYHAL_DRIVER_AVAILABLE_SYSPM) */
        _cyhal_audioss_config_structs[obj->resource.block_num] = obj;
#if defined(CY_IP_MXAUDIOSS)
        _cyhal_irq_register(_cyhal_audioss_irq_n[obj->resource.block_num], CYHAL_ISR_PRIORITY_DEFAULT, _cyhal_audioss_irq_handler);
        _cyhal_irq_enable(_cyhal_audioss_irq_n[obj->resource.block_num]);
#elif defined(CY_IP_MXTDM)
    #if defined (COMPONENT_CAT5)
        Cy_AudioTDM_RegisterInterruptCallback(obj->base,  _cyhal_audioss_irq_handler);
        Cy_AudioTDM_EnableInterrupt(obj->base); // Enables both TX and RX
    #endif

        _cyhal_irq_register(_cyhal_audioss_rx_irq_n[obj->resource.block_num], CYHAL_ISR_PRIORITY_DEFAULT, (cy_israddress)_cyhal_audioss_irq_handler_rx);
        _cyhal_irq_enable(_cyhal_audioss_rx_irq_n[obj->resource.block_num]);

        _cyhal_irq_register(_cyhal_audioss_tx_irq_n[obj->resource.block_num], CYHAL_ISR_PRIORITY_DEFAULT, (cy_israddress)_cyhal_audioss_irq_handler_tx );
        _cyhal_irq_enable(_cyhal_audioss_tx_irq_n[obj->resource.block_num]);
#else
#error "Unrecognized audio IP"
#endif
    }

    return result;
}

cy_rslt_t _cyhal_audioss_init(_cyhal_audioss_t *obj, const _cyhal_audioss_pins_t* tx_pins, const _cyhal_audioss_pins_t* rx_pins, const _cyhal_audioss_config_t* config, cyhal_clock_t* clk, const _cyhal_audioss_interface_t* interface)
{
    CY_ASSERT(NULL != obj);

    memset(obj, 0, sizeof(_cyhal_audioss_t));
    /* Explicitly marked not allocated resources as invalid to prevent freeing them. */
    obj->resource.type = CYHAL_RSC_INVALID;
    obj->pin_tx_sck    = CYHAL_NC_PIN_VALUE;
    obj->pin_tx_ws     = CYHAL_NC_PIN_VALUE;
    obj->pin_tx_sdo    = CYHAL_NC_PIN_VALUE;
    obj->pin_tx_mclk   = CYHAL_NC_PIN_VALUE;
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    obj->pin_rx_sck    = CYHAL_NC_PIN_VALUE;
    obj->pin_rx_ws     = CYHAL_NC_PIN_VALUE;
    obj->pin_rx_sdi    = CYHAL_NC_PIN_VALUE;
    obj->pin_rx_mclk   = CYHAL_NC_PIN_VALUE;
#endif

    obj->interface         = interface;
    obj->channel_length_tx = config->channel_length;
    obj->word_length_tx    = config->word_length;
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    obj->channel_length_rx = config->channel_length;
    obj->word_length_rx    = config->word_length;
#endif

    /*
     * We will update this to owned later if appropriate - for now set to false
     * so we don't try to free if we fail before allocating a clock
     */
    obj->is_clock_owned = false;

    obj->user_enabled_events = 0u;

    obj->callback_data.callback = NULL;
    obj->callback_data.callback_arg = NULL;
    obj->async_mode = CYHAL_ASYNC_SW;
    obj->async_tx_buff = NULL;
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    obj->async_rx_buff = NULL;
#endif
    obj->tx_dma.resource.type = CYHAL_RSC_INVALID;
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    obj->rx_dma.resource.type = CYHAL_RSC_INVALID;
#endif

    cy_rslt_t result = CY_RSLT_SUCCESS;

    /* Determine which I2S instance to use */
    const cyhal_resource_pin_mapping_t *tx_sck_map = (NULL != tx_pins) ? _CYHAL_UTILS_GET_RESOURCE(tx_pins->sck, _CYHAL_AUDIOSS_TX_SCK_MAP) : NULL;
    const cyhal_resource_pin_mapping_t *tx_ws_map  = (NULL != tx_pins) ? _CYHAL_UTILS_GET_RESOURCE(tx_pins->ws, _CYHAL_AUDIOSS_TX_WS_MAP) : NULL;
    const cyhal_resource_pin_mapping_t *tx_sdo_map = (NULL != tx_pins) ? _CYHAL_UTILS_GET_RESOURCE(tx_pins->data, _CYHAL_AUDIOSS_TX_SDO_MAP) : NULL;

#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    const cyhal_resource_pin_mapping_t *rx_sck_map = (NULL != rx_pins) ? _CYHAL_UTILS_GET_RESOURCE(rx_pins->sck, _CYHAL_AUDIOSS_RX_SCK_MAP) : NULL;
    const cyhal_resource_pin_mapping_t *rx_ws_map  = (NULL != rx_pins) ? _CYHAL_UTILS_GET_RESOURCE(rx_pins->ws, _CYHAL_AUDIOSS_RX_WS_MAP) : NULL;
    const cyhal_resource_pin_mapping_t *rx_sdi_map = (NULL != rx_pins) ? _CYHAL_UTILS_GET_RESOURCE(rx_pins->data, _CYHAL_AUDIOSS_RX_SDI_MAP) : NULL;
#endif

    const cyhal_resource_pin_mapping_t *mclk_map_rx = NULL;
    const cyhal_resource_pin_mapping_t *mclk_map_tx = NULL;

#if !defined(_CYHAL_AUDIOSS_RX_ENABLED)
    if(rx_pins != NULL)
    {
        result = interface->err_not_supported;
    }
#endif
#if !defined(_CYHAL_AUDIOSS_TX_SLAVE_AVAILABLE)
    if(config->is_tx_slave)
    {
        result = interface->err_not_supported;
    }
#endif
#if defined(CY_IP_MXAUDIOSS)
    if(NULL != tx_pins && NULL != rx_pins && tx_pins->mclk != rx_pins->mclk)
    {
        /* RX and TX must share the same MCLK pin (or lack thereof) on this IP */
        result = obj->interface->err_invalid_pin;
    }

    mclk_map_rx = (NULL != rx_pins) ? _CYHAL_UTILS_GET_RESOURCE(rx_pins->mclk, cyhal_pin_map_audioss_clk_i2s_if) : NULL;
    mclk_map_tx = (NULL != tx_pins) /* If non-null, we know the mclk pins must be the same, so can reuse the rx value */
              ? ((NULL != mclk_map_rx) ? mclk_map_rx : _CYHAL_UTILS_GET_RESOURCE(tx_pins->mclk, cyhal_pin_map_audioss_clk_i2s_if))
          : NULL;

    uint8_t mclk_tx_dm = CYHAL_PIN_MAP_DRIVE_MODE_AUDIOSS_CLK_I2S_IF;
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    uint8_t mclk_rx_dm = CYHAL_PIN_MAP_DRIVE_MODE_AUDIOSS_CLK_I2S_IF;
#endif
#elif defined(CY_IP_MXTDM)
    mclk_map_rx = (NULL != rx_pins) ? _CYHAL_UTILS_GET_RESOURCE(rx_pins->mclk, _CYHAL_AUDIOSS_RX_MCK_MAP) : NULL;
    mclk_map_tx = (NULL != tx_pins) ? _CYHAL_UTILS_GET_RESOURCE(tx_pins->mclk, _CYHAL_AUDIOSS_TX_MCK_MAP) : NULL;
    uint8_t mclk_tx_dm = (uint8_t)CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_TX_MCK;
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    uint8_t mclk_rx_dm = (uint8_t)CYHAL_PIN_MAP_DRIVE_MODE_TDM_TDM_RX_MCK;
#endif
#endif

#if defined(CY_IP_MXAUDIOSS)
    cyhal_resource_t rsc_type = CYHAL_RSC_I2S;
#elif defined(CY_IP_MXTDM)
    cyhal_resource_t rsc_type = CYHAL_RSC_TDM;
#endif

    if(CY_RSLT_SUCCESS == result && NULL != tx_pins) /* It is valid to leave either tx or rx empty */
    {
        if(NULL != tx_sck_map && NULL != tx_ws_map && NULL != tx_sdo_map
            && _cyhal_utils_map_resources_equal_all(3, tx_sck_map, tx_ws_map, tx_sdo_map))
        {
            _CYHAL_UTILS_ASSIGN_RESOURCE(obj->resource, rsc_type, tx_sck_map);
        }
        else
        {
            result = obj->interface->err_invalid_pin;
        }
    }

#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    if(CY_RSLT_SUCCESS == result && NULL != rx_pins)
    {
        if(NULL == rx_sck_map || NULL == rx_ws_map || NULL == rx_sdi_map ||
            (false == _cyhal_utils_map_resources_equal_all(3, rx_sck_map, rx_ws_map, rx_sdi_map)))
        {
            result = obj->interface->err_invalid_pin;
        }
        else
        {
            if((obj->resource.type != CYHAL_RSC_INVALID)
                && (false == _cyhal_utils_map_resource_equal(&(obj->resource), rx_sck_map, false)))
            {
                /* TX pins and RX pins don't map to the same instance */
                result = obj->interface->err_invalid_pin;
            }
            _CYHAL_UTILS_ASSIGN_RESOURCE(obj->resource, rsc_type, rx_sck_map);
        }
    }
#endif

    if(CYHAL_RSC_INVALID == obj->resource.type) /* If this happens it means neither rx nor tx was specified */
    {
        result = obj->interface->err_invalid_pin;
    }

    if(CY_RSLT_SUCCESS == result && NULL != rx_pins && CYHAL_NC_PIN_VALUE != rx_pins->mclk )
    {
        if(NULL == mclk_map_rx || (false == _cyhal_utils_map_resource_equal(&(obj->resource), mclk_map_rx, false)))
        {
            result = obj->interface->err_invalid_pin;
        }
    }

    if(CY_RSLT_SUCCESS == result && NULL != tx_pins && CYHAL_NC_PIN_VALUE != tx_pins->mclk )
    {
        if(NULL == mclk_map_tx || (false == _cyhal_utils_map_resource_equal(&(obj->resource), mclk_map_tx, false)))
        {
            result = obj->interface->err_invalid_pin;
        }
    }

#if defined(CY_IP_MXAUDIOSS)
    const uint8_t MAX_CHANNELS = 8u; /* I2S will already have limited to a lower count */
#elif defined(CY_IP_MXTDM)
    const uint8_t MAX_CHANNELS = _cyhal_audioss_max_channels[obj->resource.block_num];
#endif
    if(CY_RSLT_SUCCESS == result && config->num_channels > MAX_CHANNELS)
    {
        result = obj->interface->err_invalid_arg;
    }

#if defined(CY_IP_MXAUDIOSS)
    // This IP doesn't support disabling individual channels, just reducing the overall count
    for(size_t i = 0; i < sizeof(config->channel_mask) * 8 /* bits per byte */; ++i)
    {
        bool chan_enabled = (0u != (config->channel_mask & ((uint32_t)1u << i)));
        bool is_selected_channel = (i < config->num_channels);
        if(is_selected_channel != chan_enabled)
        {
            result = obj->interface->err_invalid_arg;
            break;
        }
    }
#endif

    if(CY_RSLT_SUCCESS == result)
    {
        result = cyhal_hwmgr_reserve(&(obj->resource));
    }

    if(CY_RSLT_SUCCESS != result)
    {
        // If we aren't successful by here, we didn't manage to reserve the hardware resource,
        // so mark it as invalid to ensure it isn't incorrectly freed.
        obj->resource.type = CYHAL_RSC_INVALID;
    }

    uint8_t dm_tx_sck, dm_tx_ws;
#if defined (COMPONENT_CAT5)
    dm_tx_sck = (config->is_tx_slave) ? CYHAL_PIN_MAP_DRIVE_MODE_TDM_SLAVE : _CYHAL_AUDIOSS_DRIVE_MODE_TX_SCK;
    dm_tx_ws = (config->is_tx_slave) ? CYHAL_PIN_MAP_DRIVE_MODE_TDM_SLAVE : _CYHAL_AUDIOSS_DRIVE_MODE_TX_WS;
#else
    dm_tx_sck = _CYHAL_AUDIOSS_DRIVE_MODE_TX_SCK;
    dm_tx_ws = _CYHAL_AUDIOSS_DRIVE_MODE_TX_WS;
#endif

    /* Reserve the pins */
    if(CY_RSLT_SUCCESS == result && NULL != tx_pins)
    {
        result = _cyhal_utils_reserve_and_connect(tx_sck_map, dm_tx_sck);
        if(CY_RSLT_SUCCESS == result)
        {
            obj->pin_tx_sck = tx_pins->sck;
            result = _cyhal_utils_reserve_and_connect(tx_ws_map, dm_tx_ws);
        }
        if(CY_RSLT_SUCCESS == result)
        {
            obj->pin_tx_ws = tx_pins->ws;
            result = _cyhal_utils_reserve_and_connect(tx_sdo_map, (uint8_t)_CYHAL_AUDIOSS_DRIVE_MODE_TX_SDO);
        }
        if(CY_RSLT_SUCCESS == result)
        {
            obj->pin_tx_sdo = tx_pins->data;
        }
#if defined(_CYHAL_AUDIOSS_TX_SLAVE_AVAILABLE) && !defined (COMPONENT_CAT5)
        // In slave mode, the clock and word select pins are inputs
        if(CY_RSLT_SUCCESS == result && config->is_tx_slave)
        {
            result = cyhal_gpio_configure(obj->pin_tx_sck, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE);
            if(CY_RSLT_SUCCESS == result)
            {
                result = cyhal_gpio_configure(obj->pin_tx_ws, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE);
            }
        }
#endif

    }

#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    if(CY_RSLT_SUCCESS == result && NULL != rx_pins)
    {
        result = _cyhal_utils_reserve_and_connect(rx_sdi_map, (uint8_t)_CYHAL_AUDIOSS_DRIVE_MODE_RX_SDI);

#if defined (COMPONENT_CAT5)
        if(CY_RSLT_SUCCESS == result)
        {
            obj->pin_rx_sdi = rx_pins->data;
            obj->pin_rx_sck = rx_pins->sck; // The SCK and WS are tied to the TX on this device
            obj->pin_rx_ws = rx_pins->ws;
        }
#else
        if(CY_RSLT_SUCCESS == result)
        {
            obj->pin_rx_sdi = rx_pins->data;
            result = _cyhal_utils_reserve_and_connect(rx_sck_map, (uint8_t)_CYHAL_AUDIOSS_DRIVE_MODE_RX_SCK);
        }
        if(CY_RSLT_SUCCESS == result)
        {
            obj->pin_rx_sck = rx_pins->sck;
            result = _cyhal_utils_reserve_and_connect(rx_ws_map, (uint8_t)_CYHAL_AUDIOSS_DRIVE_MODE_RX_WS);
        }
        if(CY_RSLT_SUCCESS == result)
        {
            obj->pin_rx_ws = rx_pins->ws;
        }

        // In slave mode, the clock and word select pins are inputs
        if(CY_RSLT_SUCCESS == result && config->is_rx_slave)
        {
            result = cyhal_gpio_configure(obj->pin_rx_sck, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE);
            if(CY_RSLT_SUCCESS == result)
            {
                result = cyhal_gpio_configure(obj->pin_rx_ws, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE);
            }
        }
#endif

    }
#endif

    bool has_mclk = NULL != mclk_map_rx || NULL != mclk_map_tx;
    if(CY_RSLT_SUCCESS == result && has_mclk)
    {
        if(config->mclk_hz == 0)
        {
            // Must specify mclk frequency when using mclk
            result = obj->interface->err_invalid_arg;
        }
        else
        {
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
            if(NULL != mclk_map_rx)
            {
                result = _cyhal_utils_reserve_and_connect(mclk_map_rx, mclk_rx_dm);
                if(CY_RSLT_SUCCESS == result)
                {
                    obj->pin_rx_mclk = mclk_map_rx->pin;
                    obj->mclk_hz_rx = config->mclk_hz;
                }
            }
#endif
            if(CY_RSLT_SUCCESS == result && NULL != mclk_map_tx)
            {
                /* Don't try to reserve twice if rx and tx mclk are the same pin */
                if(NULL == mclk_map_rx || mclk_map_tx->pin != mclk_map_rx->pin)
                {
                    result = _cyhal_utils_reserve_and_connect(mclk_map_tx, mclk_tx_dm);
                }
                if(CY_RSLT_SUCCESS == result)
                {
                    obj->pin_tx_mclk = mclk_map_tx->pin;
                    obj->mclk_hz_tx = config->mclk_hz;
                }
            }
        }
    }

    if(CY_RSLT_SUCCESS == result && false == has_mclk)
    {
        // Must not specify mclk frequency when mclk pin is not in use
        if(config->mclk_hz != 0)
        {
            result = obj->interface->err_invalid_arg;
        }
    }

    /* In this init flow rx and tx have the same lengths so we just need to check tx */
    if(CY_RSLT_SUCCESS == result && obj->word_length_tx > obj->channel_length_tx)
    {
        // Word length must be less than or equal to channel length
        result = obj->interface->err_invalid_arg;
    }

    if(CY_RSLT_SUCCESS == result && obj->channel_length_tx > _CYHAL_AUDIOSS_MAX_CHANNEL_LENGTH)
    {
        // Channel length on MXAUDIOSS is more restricted than this, but that is
        // checked in populate_pdl_config. There is also a lower bound of 4
        // on MXTDM but that is taken care of by the check above because
        // 8 bits is the smallest word length we support.
        result = obj->interface->err_invalid_arg;
    }

    if (CY_RSLT_SUCCESS == result)
    {
        bool all_mclk = (NULL == rx_pins || CYHAL_NC_PIN_VALUE != rx_pins->mclk)
                     && (NULL == tx_pins || CYHAL_NC_PIN_VALUE != tx_pins->mclk);

        result = _cyhal_audioss_init_clock(obj, clk, all_mclk);
    }

    uint16_t sclk_div_tx = 0;
    uint16_t sclk_div_rx = 0;
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    if(CY_RSLT_SUCCESS == result && NULL != rx_pins)
    {
        result = _cyhal_audioss_compute_sclk_div(obj, config->sample_rate_hz, obj->mclk_hz_rx, obj->channel_length_rx, config->num_channels, &sclk_div_rx);
    }
    #endif
    if(CY_RSLT_SUCCESS == result && NULL != tx_pins)
    {
        result = _cyhal_audioss_compute_sclk_div(obj, config->sample_rate_hz, obj->mclk_hz_tx, obj->channel_length_tx, config->num_channels, &sclk_div_tx);
    }

    _cyhal_audioss_pdl_config_t pdl_config;
    memset(&pdl_config, 0, sizeof(pdl_config));
#if defined(CY_IP_MXTDM)
    cy_stc_tdm_config_tx_t tx_config = {0};
    cy_stc_tdm_config_rx_t rx_config = {0};
    pdl_config.tx_config = &tx_config;
    pdl_config.rx_config = &rx_config;
#endif
    if (CY_RSLT_SUCCESS == result)
    {
        bool tx_en = (CYHAL_NC_PIN_VALUE != obj->pin_tx_sdo);
        bool tx_mclk = (CYHAL_NC_PIN_VALUE != obj->pin_tx_mclk);
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
        bool rx_en = (CYHAL_NC_PIN_VALUE != obj->pin_rx_sdi);
        bool rx_mclk = (CYHAL_NC_PIN_VALUE != obj->pin_rx_mclk);
#else
        bool rx_en = false;
        bool rx_mclk = false;
#endif
        result = _cyhal_audioss_populate_pdl_config(obj, &pdl_config, config, sclk_div_rx, sclk_div_tx, rx_en, tx_en, rx_mclk, tx_mclk);
    }

    if (CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_audioss_init_hw(obj, &pdl_config);
    }

    if (CY_RSLT_SUCCESS != result)
    {
        _cyhal_audioss_free(obj);
    }
    return result;
}

cy_rslt_t _cyhal_audioss_init_cfg(_cyhal_audioss_t *obj, const _cyhal_audioss_configurator_t *cfg, const _cyhal_audioss_interface_t* interface)
{
    CY_ASSERT(NULL != obj);

    memset(obj, 0, sizeof(_cyhal_audioss_t));
    obj->owned_by_configurator = true;
    obj->resource = *cfg->resource;
    obj->mclk_hz_tx = cfg->mclk_hz_tx;
    obj->interface = interface;

    obj->async_mode        = CYHAL_ASYNC_SW;
    obj->tx_dma.resource.type = CYHAL_RSC_INVALID;
#if defined(CY_IP_MXAUDIOSS)
    obj->channel_length_tx = _cyhal_audioss_length_from_pdl(cfg->config->txChannelLength);
    obj->word_length_tx    = _cyhal_audioss_length_from_pdl(cfg->config->txWordLength);
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    obj->channel_length_rx = _cyhal_audioss_length_from_pdl(cfg->config->rxChannelLength);
    obj->word_length_rx    = _cyhal_audioss_length_from_pdl(cfg->config->rxWordLength);
#endif
#elif defined(CY_IP_MXTDM)
    obj->channel_length_tx = cfg->config->tx_config->channelSize;
    obj->word_length_tx    = _cyhal_audioss_length_from_pdl(cfg->config->tx_config->wordSize);
    obj->channel_length_rx = cfg->config->rx_config->channelSize;
    obj->word_length_rx    = _cyhal_audioss_length_from_pdl(cfg->config->rx_config->wordSize);
#endif
    obj->pin_tx_sck        = CYHAL_NC_PIN_VALUE;
    obj->pin_tx_ws         = CYHAL_NC_PIN_VALUE;
    obj->pin_tx_sdo        = CYHAL_NC_PIN_VALUE;
    obj->pin_tx_mclk       = CYHAL_NC_PIN_VALUE;
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    obj->rx_dma.resource.type = CYHAL_RSC_INVALID;
    obj->pin_rx_sck        = CYHAL_NC_PIN_VALUE;
    obj->pin_rx_ws         = CYHAL_NC_PIN_VALUE;
    obj->pin_rx_sdi        = CYHAL_NC_PIN_VALUE;
    obj->pin_rx_mclk       = CYHAL_NC_PIN_VALUE;
#endif

#if defined(CY_IP_MXAUDIOSS)
    bool all_mclk = (0u != obj->mclk_hz_tx); /* No separate rx/tx clock selection */
#elif defined(CY_IP_MXTDM)
    bool all_mclk = ((false == cfg->config->rx_config->enable) || (CY_TDM_SEL_MCLK_IN == cfg->config->rx_config->clkSel))
                 && ((false == cfg->config->tx_config->enable) || (CY_TDM_SEL_MCLK_IN == cfg->config->tx_config->clkSel));
#endif
    cy_rslt_t result = _cyhal_audioss_init_clock(obj, cfg->clock, all_mclk);

    if(CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_audioss_init_hw(obj, cfg->config);
    }

    if(CY_RSLT_SUCCESS != result)
    {
        _cyhal_audioss_free(obj);
    }
    return result;
}

void _cyhal_audioss_free(_cyhal_audioss_t *obj)
{
    CY_ASSERT(NULL != obj);

    if(CYHAL_RSC_INVALID != obj->resource.type)
    {
#if defined(CY_IP_MXAUDIOSS)
        _cyhal_system_irq_t irqn = _cyhal_audioss_irq_n[obj->resource.block_num];
        _cyhal_irq_free(irqn);
#elif defined(CY_IP_MXTDM)
        _cyhal_system_irq_t irqn = _cyhal_audioss_rx_irq_n[obj->resource.block_num];
        _cyhal_irq_free(irqn);
        irqn = _cyhal_audioss_tx_irq_n[obj->resource.block_num];
        _cyhal_irq_free(irqn);
#endif

#if (CYHAL_DRIVER_AVAILABLE_SYSPM)
        _cyhal_syspm_unregister_peripheral_callback(&(obj->pm_callback));
#endif /*  (CYHAL_DRIVER_AVAILABLE_SYSPM) */

        if(NULL != obj->base)
        {
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
            _cyhal_audioss_stop_rx(obj);
#endif
            _cyhal_audioss_stop_tx(obj);

#if defined(CY_IP_MXTDM)
            Cy_AudioTDM_DisableTx(&obj->base->TDM_TX_STRUCT);
            Cy_AudioTDM_DisableRx(&obj->base->TDM_RX_STRUCT);
#endif
        }
        if(false == obj->owned_by_configurator)
        {
            cyhal_hwmgr_free(&(obj->resource));
        }

        obj->base = NULL;
        obj->resource.type = CYHAL_RSC_INVALID;
    }

    /* Need to check this before we start releasing because release_if_used
     * sets the pin to NC once it is done */
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    bool different_mclk = (obj->pin_rx_mclk != obj->pin_tx_mclk);
#endif
    _cyhal_utils_release_if_used(&(obj->pin_tx_sck));
    _cyhal_utils_release_if_used(&(obj->pin_tx_ws));
    _cyhal_utils_release_if_used(&(obj->pin_tx_sdo));
    _cyhal_utils_release_if_used(&(obj->pin_tx_mclk));
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    _cyhal_utils_release_if_used(&(obj->pin_rx_sck));
    _cyhal_utils_release_if_used(&(obj->pin_rx_ws));
    _cyhal_utils_release_if_used(&(obj->pin_rx_sdi));
    if(different_mclk)
    {
        _cyhal_utils_release_if_used(&(obj->pin_rx_mclk));
    }
#endif
    if(obj->is_clock_owned)
    {
        cyhal_clock_free(&(obj->clock));
    }

#if (CYHAL_DRIVER_AVAILABLE_DMA)
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    if(CYHAL_RSC_INVALID != obj->rx_dma.resource.type)
    {
        cyhal_dma_free(&obj->rx_dma);
    }
#endif /* defined(_CYHAL_AUDIOSS_RX_ENABLED) */

    if(CYHAL_RSC_INVALID != obj->tx_dma.resource.type)
    {
        cyhal_dma_free(&obj->tx_dma);
    }
#endif /* (CYHAL_DRIVER_AVAILABLE_DMA) */
}

static uint8_t _cyhal_audioss_fifo_trigger_level(_cyhal_audioss_t* obj, bool is_tx)
{
#if defined(CY_IP_MXAUDIOSS)
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    return is_tx
        ? (uint8_t)_FLD2VAL(I2S_TX_FIFO_CTL_TRIGGER_LEVEL, REG_I2S_TX_FIFO_CTL(obj->base))
        : (uint8_t)_FLD2VAL(I2S_RX_FIFO_CTL_TRIGGER_LEVEL, REG_I2S_RX_FIFO_CTL(obj->base));
#else
    CY_UNUSED_PARAMETER(is_tx);
    return (uint8_t)_FLD2VAL(I2S_TX_FIFO_CTL_TRIGGER_LEVEL, REG_I2S_TX_FIFO_CTL(obj->base));
#endif
#elif defined(CY_IP_MXTDM)
    return is_tx
        ? (uint8_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_TRIGGER_LEVEL, TDM_STRUCT_TX_FIFO_CTL(&obj->base->TDM_TX_STRUCT))
        : (uint8_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_FIFO_CTL_TRIGGER_LEVEL, TDM_STRUCT_RX_FIFO_CTL(&obj->base->TDM_RX_STRUCT));
#endif
}

static bool _cyhal_audioss_is_direction_enabled(_cyhal_audioss_t *obj, bool is_tx)
{
#if defined(CY_IP_MXAUDIOSS)
    return is_tx
        ? (0u != (REG_I2S_CTL(obj->base) & I2S_CTL_TX_ENABLED_Msk))
        : (0u != (REG_I2S_CTL(obj->base) & I2S_CTL_RX_ENABLED_Msk));
#elif defined(CY_IP_MXTDM)
    return is_tx
        ? (0u != (TDM_STRUCT_TX_CTL(&obj->base->TDM_TX_STRUCT) & TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_CTL_ENABLED_Msk))
        : (0u != (TDM_STRUCT_RX_CTL(&obj->base->TDM_RX_STRUCT) & TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_CTL_ENABLED_Msk));
#endif
}

/* Note: This function is called prior to PDL init, and again from set_sample_rate. This means that
 * it cannot safely query either register values (which may not be initialized), nor pin values (which
 * are not populated in the configurator init flow) */
static cy_rslt_t _cyhal_audioss_compute_sclk_div(_cyhal_audioss_t *obj, uint32_t sample_rate_hz, uint32_t mclk_hz, uint8_t channel_length, uint8_t num_channels, uint16_t *sclk_div)
{
#if defined(CY_IP_MXAUDIOSS)
    const uint8_t SCLK_INCREMENT = 1;
    const uint8_t MIN_SCLK_DIVIDER = 1;
    const uint8_t MAX_SCLK_DIVIDER = 64; // Divider value internal to the I2S block
#elif defined(CY_IP_MXTDM)
    const uint8_t MIN_SCLK_DIVIDER = 2;
    const uint8_t SCLK_INCREMENT = 2; // Per PDL, should be set to an even value to ensure 50/50 duty cycle
    const uint16_t MAX_SCLK_DIVIDER = 256; // Divider value internal to the I2S block
#endif

    const cyhal_clock_tolerance_t SCLK_TOLERANCE = { .type = CYHAL_TOLERANCE_PERCENT, .value = 1 };
    uint32_t sclk_target = sample_rate_hz * channel_length * num_channels;
    *sclk_div = 0;

    if(obj->is_clock_owned)
    {
        // Try each of the divider values that we support internally, and see whether any of them gets us
        // within our tolerance of a frequency that our source clock can provide.
        for(uint16_t i = MIN_SCLK_DIVIDER; i <= MAX_SCLK_DIVIDER; i += SCLK_INCREMENT)
        {
#if defined(CY_IP_MXAUDIOSS)
            // This IP has a hard-wired 8x divider
            uint32_t desired_source_freq = sclk_target * i * 8;
#elif defined(CY_IP_MXTDM)
            uint32_t desired_source_freq = sclk_target * i;
#endif
            cy_rslt_t freq_result = _cyhal_utils_set_clock_frequency(&(obj->clock), desired_source_freq, &SCLK_TOLERANCE);
            if(CY_RSLT_SUCCESS == freq_result)
            {
                *sclk_div = i;
                break;
            }
        }
    }
    else // Using user-provided clock, or using the mclk pin
    {
        // We can't change the clock, so just check if it's within tolerance
#if defined(CY_IP_MXAUDIOSS)
        uint32_t desired_divided_freq = sclk_target * 8; // I2S hw has a hard-wired 8x divider
#elif defined(CY_IP_MXTDM)
        uint32_t desired_divided_freq = sclk_target;
#endif
        uint32_t actual_source_freq = (0u != mclk_hz) ? mclk_hz : cyhal_clock_get_frequency(&obj->clock);
        uint32_t best_divider = (actual_source_freq + (desired_divided_freq / 2)) / desired_divided_freq; // Round to nearest divider
#if !defined (COMPONENT_CAT5)
        uint32_t desired_source_freq = desired_divided_freq * best_divider;
        uint32_t diff = (uint32_t)abs(_cyhal_utils_calculate_tolerance(SCLK_TOLERANCE.type, desired_source_freq, actual_source_freq));
        if(diff <= SCLK_TOLERANCE.value && best_divider <= MAX_SCLK_DIVIDER)
        {
            *sclk_div = (uint16_t)best_divider;
        }
#else
        // Tolerance check cannot be reliably done on this device. Therefore skip it.
        *sclk_div = best_divider;
#endif
    }

    return (0 == *sclk_div) ? obj->interface->err_clock : CY_RSLT_SUCCESS;
}

cy_rslt_t _cyhal_audioss_set_sample_rate(_cyhal_audioss_t *obj, uint32_t sample_rate_hz)
{
    uint16_t sclk_div_tx = 0;
    _cyhal_audioss_pdl_config_t pdl_config;
    memset(&pdl_config, 0, sizeof(pdl_config));
#if defined(CY_IP_MXTDM)
    cy_stc_tdm_config_tx_t tx_config;
    cy_stc_tdm_config_rx_t rx_config;
    pdl_config.tx_config = &tx_config;
    pdl_config.rx_config = &rx_config;
#endif
    _cyhal_audioss_reconstruct_pdl_config(obj, &pdl_config);
#if defined(CY_IP_MXAUDIOSS)
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    uint8_t rx_channels = pdl_config.rxChannels;
#endif
    uint8_t tx_channels = pdl_config.txChannels;
#elif defined(CY_IP_MXTDM)
     uint8_t rx_channels = pdl_config.rx_config->channelNum;
     uint8_t tx_channels = pdl_config.tx_config->channelNum;
#endif /* _CYHAL_AUDIOSS_RX_ENABLED */
    cy_rslt_t result = _cyhal_audioss_compute_sclk_div(obj, sample_rate_hz, obj->mclk_hz_tx, obj->channel_length_tx, tx_channels, &sclk_div_tx);
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    uint16_t sclk_div_rx = 0;
    if(CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_audioss_compute_sclk_div(obj, sample_rate_hz, obj->mclk_hz_rx, obj->channel_length_rx, rx_channels, &sclk_div_rx);
    }
#endif /* _CYHAL_AUDIOSS_RX_ENABLED */
    if(CY_RSLT_SUCCESS == result)
    {
#if defined(CY_IP_MXAUDIOSS)
        pdl_config.clkDiv = (uint8_t)(sclk_div_tx);
#elif defined(CY_IP_MXTDM)
        pdl_config.tx_config->clkDiv = sclk_div_tx;
        pdl_config.rx_config->clkDiv = sclk_div_rx;
#endif
        Cy_I2S_DeInit(obj->base);

        result = _cyhal_audioss_init_pdl(obj, &pdl_config);
    }

    return result;
}

void _cyhal_audioss_enable_event(_cyhal_audioss_t *obj, uint32_t event, uint8_t intr_priority, bool enable)
{
    CY_ASSERT(NULL != obj);

    if (enable)
    {
        obj->user_enabled_events |= event;
    }
    else
    {
        obj->user_enabled_events &= ~event;
    }

    _cyhal_audioss_update_enabled_events(obj);
#if defined(CY_IP_MXAUDIOSS)
    _cyhal_system_irq_t irqn = _cyhal_audioss_irq_n[obj->resource.block_num];
    _cyhal_irq_set_priority(irqn, intr_priority);
#elif defined(CY_IP_MXTDM)
    _cyhal_system_irq_t irqn = _cyhal_audioss_tx_irq_n[obj->resource.block_num];
    _cyhal_irq_set_priority(irqn, intr_priority);
    irqn = _cyhal_audioss_rx_irq_n[obj->resource.block_num];
    _cyhal_irq_set_priority(irqn, intr_priority);
#endif
}

cy_rslt_t _cyhal_audioss_start_tx(_cyhal_audioss_t *obj)
{
    if (obj->pm_transition_ready)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }
#if defined(CY_IP_MXAUDIOSS)
    Cy_I2S_EnableTx(obj->base);
#elif defined(CY_IP_MXTDM)
    Cy_AudioTDM_ActivateTx(&obj->base->TDM_TX_STRUCT);
#endif
    return CY_RSLT_SUCCESS;
}

cy_rslt_t _cyhal_audioss_stop_tx(_cyhal_audioss_t *obj)
{
#if defined(CY_IP_MXAUDIOSS)
    Cy_I2S_DisableTx(obj->base);
#elif defined(CY_IP_MXTDM)
    // Not disable - that is more aggressive than we want
    Cy_AudioTDM_DeActivateTx(&obj->base->TDM_TX_STRUCT);
#endif
    return CY_RSLT_SUCCESS;
}

cy_rslt_t _cyhal_audioss_clear_tx(_cyhal_audioss_t *obj)
{
#if defined(CY_IP_MXAUDIOSS)
    Cy_I2S_ClearTxFifo(obj->base);
#elif defined(CY_IP_MXTDM)
    /* No way to explicitly clear the FIFO, so disable and re-enable
     * which will clear the FIFO as a side effect, while retaining
     * all other configuration */
     bool was_active = _cyhal_audioss_is_tx_enabled(obj);
     Cy_AudioTDM_DisableTx(&obj->base->TDM_TX_STRUCT);
     Cy_AudioTDM_EnableTx(&obj->base->TDM_TX_STRUCT);
     if(was_active)
     {
         Cy_AudioTDM_ActivateTx(&obj->base->TDM_TX_STRUCT);
     }
#endif
    return CY_RSLT_SUCCESS;
}

cy_rslt_t _cyhal_audioss_start_rx(_cyhal_audioss_t *obj)
{
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    if (obj->pm_transition_ready)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }
#if defined(CY_IP_MXAUDIOSS)
    Cy_I2S_EnableRx(obj->base);
#elif defined(CY_IP_MXTDM)
    Cy_AudioTDM_ActivateRx(&obj->base->TDM_RX_STRUCT);
#endif
    return CY_RSLT_SUCCESS;
#else
    return obj->interface->err_not_supported;
#endif
}

cy_rslt_t _cyhal_audioss_stop_rx(_cyhal_audioss_t *obj)
{
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
#if defined(CY_IP_MXAUDIOSS)
    Cy_I2S_DisableRx(obj->base);
#elif defined(CY_IP_MXTDM)
    // Not disable - that is more aggressive than we want
    Cy_AudioTDM_DeActivateRx(&obj->base->TDM_RX_STRUCT);
#endif
    return CY_RSLT_SUCCESS;
#else
    return obj->interface->err_not_supported;
#endif
}

cy_rslt_t _cyhal_audioss_clear_rx(_cyhal_audioss_t *obj)
{
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
#if defined(CY_IP_MXAUDIOSS)
    Cy_I2S_ClearRxFifo(obj->base);
#elif defined(CY_IP_MXTDM)
    /* No way to explicitly clear the FIFO, so disable and re-enable
     * which will clear the FIFO as a side effect, while retaining
     * all other configuration */
     bool was_active = _cyhal_audioss_is_rx_enabled(obj);
     Cy_AudioTDM_DisableRx(&obj->base->TDM_RX_STRUCT);
     Cy_AudioTDM_EnableRx(&obj->base->TDM_RX_STRUCT);
     if(was_active)
     {
         Cy_AudioTDM_ActivateRx(&obj->base->TDM_RX_STRUCT);
     }
#endif
    return CY_RSLT_SUCCESS;
#else
    return obj->interface->err_not_supported;
#endif
}

#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
// Reads until empty, then updates the length and buffer address to their new locations
static void _cyhal_audioss_read_until_empty(_cyhal_audioss_t *obj, void** buffer, size_t* length)
{
    // The buffer is the smallest type that will hold the word length
    // The structure of this function deliberately accepts duplication of the outer loop
    // structure in order to avoid having to recheck the word length every time around,
    // because this function is in a performance sensitive code path.
    if(obj->word_length_rx <= 8)
    {
        uint8_t *cast_buffer = (uint8_t*)(*buffer);

        while(*length > 0 && _cyhal_audioss_get_num_in_fifo(obj, false) > 0)
        {
            *cast_buffer = (uint8_t)_cyhal_audioss_read_fifo(obj);
            ++cast_buffer;
            --(*length);
        }
        *buffer = (void*)cast_buffer;
    }
    else if(obj->word_length_rx <= 16)
    {
        uint16_t *cast_buffer = (uint16_t*)(*buffer);

        while(*length > 0 && _cyhal_audioss_get_num_in_fifo(obj, false) > 0)
        {
            *cast_buffer = (uint16_t)_cyhal_audioss_read_fifo(obj);
            ++cast_buffer;
            --(*length);
        }
        *buffer = (void*)cast_buffer;
    }
    else
    {
        CY_ASSERT(obj->word_length_rx <= 32);
        uint32_t *cast_buffer = (uint32_t*)(*buffer);

        while(*length > 0 && _cyhal_audioss_get_num_in_fifo(obj, false) > 0)
        {
            *cast_buffer = _cyhal_audioss_read_fifo(obj);
            ++cast_buffer;
            --(*length);
        }
        *buffer = (void*)cast_buffer;
    }
}
#endif

cy_rslt_t _cyhal_audioss_read(_cyhal_audioss_t *obj, void *data, size_t* length)
{
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    CY_ASSERT(NULL != obj);
    if (obj->pm_transition_ready)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }

    size_t remaining = *length;
    _cyhal_audioss_read_until_empty(obj, &data, &remaining);
    *length -= remaining;
    return CY_RSLT_SUCCESS;
#else
    CY_UNUSED_PARAMETER(data);
    CY_UNUSED_PARAMETER(length);
    return obj->interface->err_not_supported;
#endif
}

static void _cyhal_audioss_write_until_full(_cyhal_audioss_t *obj, const void** buffer, size_t *length)
{
    // The buffer is the smallest type that will hold the word length
    // The structure of this function deliberately accepts duplication of the outer loop
    // structure in order to avoid having to recheck the word length every time around,
    // because this function is in a performance sensitive code path.
    if(obj->word_length_tx <= 8)
    {
        const uint8_t *cast_buffer = (const uint8_t*)(*buffer);

        while(*length > 0 && _cyhal_audioss_get_num_in_fifo(obj, true) < _CYHAL_AUDIOSS_FIFO_DEPTH)
        {
            _cyhal_audioss_write_fifo(obj, *cast_buffer);
            ++cast_buffer;
            --(*length);
        }
        *buffer = (void*)cast_buffer;
    }
    else if(obj->word_length_tx <= 16)
    {
        const uint16_t *cast_buffer = (const uint16_t*)(*buffer);

        while(*length > 0 && _cyhal_audioss_get_num_in_fifo(obj, true) < _CYHAL_AUDIOSS_FIFO_DEPTH)
        {
            _cyhal_audioss_write_fifo(obj, *cast_buffer);
            ++cast_buffer;
            --(*length);
        }
        *buffer = (void*)cast_buffer;
    }
    else
    {
        CY_ASSERT(obj->word_length_tx <= 32);
        const uint32_t *cast_buffer = (const uint32_t*)(*buffer);

        while(*length > 0 && _cyhal_audioss_get_num_in_fifo(obj, true) < _CYHAL_AUDIOSS_FIFO_DEPTH)
        {
            _cyhal_audioss_write_fifo(obj, *cast_buffer);
            ++cast_buffer;
            --(*length);
        }
        *buffer = (void*)cast_buffer;
    }
}

cy_rslt_t _cyhal_audioss_write(_cyhal_audioss_t *obj, const void *data, size_t *length)
{
    CY_ASSERT(NULL != obj);
    if (obj->pm_transition_ready)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }

    size_t remaining = *length;
    _cyhal_audioss_write_until_full(obj, &data, &remaining);
    *length -= remaining;
    return CY_RSLT_SUCCESS;
}

bool _cyhal_audioss_is_tx_enabled(_cyhal_audioss_t *obj)
{
    CY_ASSERT(NULL != obj);

#if defined(CY_IP_MXAUDIOSS)
    return (0 != (CY_I2S_TX_START & Cy_I2S_GetCurrentState(obj->base)));
#elif(defined(CY_IP_MXTDM))
    return (0u != (TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_ACTIVE_Msk & obj->base->TDM_TX_STRUCT.TX_FIFO_CTL));
#endif
}

bool _cyhal_audioss_is_tx_busy(_cyhal_audioss_t *obj)
{
    CY_ASSERT(NULL != obj);

    return (0 != _cyhal_audioss_get_num_in_fifo(obj, true)) || _cyhal_audioss_is_write_pending(obj);
}

bool _cyhal_audioss_is_rx_enabled(_cyhal_audioss_t *obj)
{
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    CY_ASSERT(NULL != obj);
#if defined(CY_IP_MXAUDIOSS)
    return (0 != (CY_I2S_RX_START & Cy_I2S_GetCurrentState(obj->base)));
#elif(defined(CY_IP_MXTDM))
    return (0u != (TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_FIFO_CTL_ACTIVE_Msk & obj->base->TDM_RX_STRUCT.RX_FIFO_CTL));
#endif
#else
    CY_UNUSED_PARAMETER(obj);
    return false;
#endif
}

bool _cyhal_audioss_is_rx_busy(_cyhal_audioss_t *obj)
{
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    CY_ASSERT(NULL != obj);
    return (0 != _cyhal_audioss_get_num_in_fifo(obj, false)) || _cyhal_audioss_is_read_pending(obj);
#else
    CY_UNUSED_PARAMETER(obj);
    return false;
#endif
}

cy_rslt_t _cyhal_audioss_read_async(_cyhal_audioss_t *obj, void *rx, size_t rx_length)
{
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    CY_ASSERT(NULL != obj);
    if (obj->pm_transition_ready)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }

    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    obj->async_rx_buff = rx;
    obj->async_rx_length = rx_length;
    cyhal_system_critical_section_exit(savedIntrStatus);
    switch(obj->async_mode)
    {
        case CYHAL_ASYNC_SW:
        {
            /* Read as much as we can now, then set up an interrupt to do the rest
             * This is a potentially long operation but we don't want other I2S operations to
             * interleave with it. So do a "mini critical section" and disable the interrupts for this block only.
             */
            uint32_t old_events = _cyhal_audioss_disable_events(obj, false);
            // Safe to cast away volatile here because we're calling read_until_empty from within
            // a critical section, so it should not change out from under us during this call
            _cyhal_audioss_read_until_empty(obj, (void**)(&obj->async_rx_buff), (size_t*)(&obj->async_rx_length));
            _cyhal_audioss_update_rx_trigger_level(obj);
            _cyhal_audioss_restore_events(obj, false, old_events);
            if(obj->async_rx_length > 0)
            {
                _cyhal_audioss_update_enabled_events(obj);
            }
            else
            {
                _cyhal_audioss_process_event(obj, obj->interface->event_rx_complete);
            }
           break;
        }
        case CYHAL_ASYNC_DMA:
        {
            // Don't directly kick off the DMA here - it will be triggered
            // from the interrupt handler when the FIFO rised above the threshold
            // (which may have already happened by the time we get here if the
            // application already had the full or half-full event enabled)
            _cyhal_audioss_update_rx_trigger_level(obj);
            _cyhal_audioss_update_enabled_events(obj);
            break;
        }
        default:
           CY_ASSERT(0); /* Unrecognized async mode */
    }

    return CY_RSLT_SUCCESS;
#else
    CY_UNUSED_PARAMETER(rx);
    CY_UNUSED_PARAMETER(rx_length);
    return obj->interface->err_not_supported;
#endif
}

static void _cyhal_audioss_reconstruct_pdl_config(_cyhal_audioss_t *obj, _cyhal_audioss_pdl_config_t* pdl_config)
{
#if defined(CY_IP_MXAUDIOSS)
    I2S_Type* base = obj->base;
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    pdl_config->txEnabled = _FLD2BOOL(I2S_CTL_TX_ENABLED, REG_I2S_CTL(base));
    pdl_config->rxEnabled = _FLD2BOOL(I2S_CTL_RX_ENABLED, REG_I2S_CTL(base));

    uint32_t rx_ctl_val = REG_I2S_RX_CTL(base);
    pdl_config->rxMasterMode = _FLD2BOOL(I2S_RX_CTL_MS, rx_ctl_val);
    pdl_config->rxAlignment  = (cy_en_i2s_alignment_t)_FLD2VAL(I2S_RX_CTL_I2S_MODE, rx_ctl_val);
    pdl_config->rxWsPulseWidth = (cy_en_i2s_ws_pw_t)_FLD2VAL(I2S_RX_CTL_WS_PULSE, rx_ctl_val);
    pdl_config->rxWatchdogEnable = _FLD2BOOL(I2S_RX_CTL_WD_EN, rx_ctl_val);
    pdl_config->rxWatchdogValue = REG_I2S_RX_WATCHDOG(base);
    pdl_config->rxSdiLatchingTime = _FLD2BOOL(I2S_RX_CTL_B_CLOCK_INV, rx_ctl_val);
    pdl_config->rxSckoInversion = _FLD2BOOL(I2S_RX_CTL_SCKO_POL, rx_ctl_val);
    pdl_config->rxSckiInversion = _FLD2BOOL(I2S_RX_CTL_SCKI_POL, rx_ctl_val);
    /* Register is one less than desired value */
    pdl_config->rxChannels = ((uint8_t)_FLD2VAL(I2S_RX_CTL_CH_NR, rx_ctl_val)) + 1;
    pdl_config->rxChannelLength = (cy_en_i2s_len_t)_FLD2VAL(I2S_RX_CTL_CH_LEN, rx_ctl_val);
    pdl_config->rxWordLength = (cy_en_i2s_len_t)_FLD2VAL(I2S_RX_CTL_WORD_LEN, rx_ctl_val);
    pdl_config->rxSignExtension = _FLD2BOOL(I2S_RX_CTL_SCKI_POL, rx_ctl_val);
    pdl_config->rxFifoTriggerLevel = _cyhal_audioss_fifo_trigger_level(obj, false);
#endif /* _CYHAL_AUDIOSS_RX_ENABLED */

#if defined(_CYHAL_AUDIOSS_TX_WATCHDOG_AVAILABLE)
        pdl_config->txWatchdogEnable = _FLD2BOOL(I2S_TX_CTL_WD_EN, rx_ctl_val);;
        pdl_config->txWatchdogValue = REG_I2S_TX_WATCHDOG(base);
#endif

#if defined(_CYHAL_AUDIOSS_TRIGGERS_AVAILABLE)
        pdl_config->txDmaTrigger = _FLD2BOOL(I2S_TR_CTL_TX_REQ_EN, REG_I2S_TR_CTL(base));
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
        pdl_config->rxDmaTrigger = _FLD2BOOL(I2S_TR_CTL_RX_REQ_EN, REG_I2S_TR_CTL(base));;
#endif
#endif /* _CYHAL_AUDIOSS_RX_ENABLED */

    uint32_t tx_ctl_val = REG_I2S_TX_CTL(base);
#if defined(_CYHAL_AUDIOSS_TX_SLAVE_AVAILABLE)
        pdl_config->txMasterMode = _FLD2BOOL(I2S_TX_CTL_MS, tx_ctl_val);
        pdl_config->txSckiInversion = _FLD2BOOL(I2S_TX_CTL_SCKI_POL, tx_ctl_val);
        pdl_config->txSdoLatchingTime = _FLD2BOOL(I2S_TX_CTL_B_CLOCK_INV, tx_ctl_val);;
#endif
    /* Register value is 1 less than the desired divider */
    pdl_config->clkDiv = ((uint8_t)_FLD2VAL(I2S_CLOCK_CTL_CLOCK_DIV, REG_I2S_CLOCK_CTL(base))) + 1;
    pdl_config->extClk = _FLD2BOOL(I2S_CLOCK_CTL_CLOCK_SEL, REG_I2S_CLOCK_CTL(base));

    /* TDM mode A == channel data starts on rising edge of WS */
    pdl_config->txAlignment = (cy_en_i2s_alignment_t)_FLD2VAL(I2S_TX_CTL_I2S_MODE, tx_ctl_val);
    pdl_config->txWsPulseWidth = (cy_en_i2s_ws_pw_t)_FLD2VAL(I2S_TX_CTL_WS_PULSE, tx_ctl_val);

    pdl_config->txSckoInversion = _FLD2BOOL(I2S_TX_CTL_SCKO_POL, tx_ctl_val);

    /* Register is one less than desired value */
    pdl_config->txChannels = ((uint8_t)_FLD2VAL(I2S_TX_CTL_CH_NR, tx_ctl_val)) + 1;
    pdl_config->txChannelLength = (cy_en_i2s_len_t)_FLD2VAL(I2S_TX_CTL_CH_LEN, tx_ctl_val);
    pdl_config->txWordLength = (cy_en_i2s_len_t)_FLD2VAL(I2S_TX_CTL_WORD_LEN, tx_ctl_val);
    pdl_config->txOverheadValue = (cy_en_i2s_overhead_t)_FLD2VAL(I2S_TX_CTL_OVHDATA, tx_ctl_val);
    pdl_config->txFifoTriggerLevel = _cyhal_audioss_fifo_trigger_level(obj, true);
#elif defined(CY_IP_MXTDM)
    TDM_TX_STRUCT_Type* base_tx = &obj->base->TDM_TX_STRUCT;
    TDM_RX_STRUCT_Type* base_rx = &obj->base->TDM_RX_STRUCT;

    /* Configure TX */
    pdl_config->tx_config->enable = _cyhal_audioss_is_direction_enabled(obj, true);
    pdl_config->tx_config->masterMode = (cy_en_tdm_device_cfg_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_CTL_MS, TDM_STRUCT_TX_CTL(base_tx));
    pdl_config->tx_config->wordSize = (cy_en_tdm_ws_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_CTL_WORD_SIZE, TDM_STRUCT_TX_CTL(base_tx));
    pdl_config->tx_config->format = (cy_en_tdm_format_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_CTL_FORMAT, TDM_STRUCT_TX_CTL(base_tx));

    uint32_t tx_if_ctl = TDM_STRUCT_TX_IF_CTL(base_tx);
    /* Divider in the config register is a less than the desired value */
    pdl_config->tx_config->clkDiv = (uint16_t)(_FLD2VAL(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_CLOCK_DIV, tx_if_ctl) + 1);
    pdl_config->tx_config->clkSel = (cy_en_tdm_clock_sel_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_CLOCK_SEL, tx_if_ctl);
    pdl_config->tx_config->sckPolarity = (cy_en_tdm_sckpolarity_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_SCK_POLARITY, tx_if_ctl);;
    pdl_config->tx_config->fsyncPolarity = (cy_en_tdm_fsyncpolarity_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_FSYNC_POLARITY, tx_if_ctl);;
    pdl_config->tx_config->fsyncFormat = (cy_en_tdm_fsyncformat_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_FSYNC_FORMAT, tx_if_ctl);
    /* Channel size and count in the register are one less than the desired value */
    pdl_config->tx_config->channelNum = (uint8_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_CH_NR, tx_if_ctl) + 1;
    pdl_config->tx_config->channelSize = (uint8_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_CH_SIZE, tx_if_ctl) + 1;
    pdl_config->tx_config->fifoTriggerLevel = _cyhal_audioss_fifo_trigger_level(obj, true);
    pdl_config->tx_config->chEn = TDM_STRUCT_TX_CH_CTL(base_tx);
    pdl_config->tx_config->signalInput = _FLD2VAL(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_ROUTE_CTL_MODE, TDM_STRUCT_TX_ROUTE_CTL(base_tx));
    pdl_config->tx_config->i2sMode = _FLD2BOOL(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_I2S_MODE, tx_if_ctl);

    /* Configure RX */
    pdl_config->rx_config->enable = _cyhal_audioss_is_direction_enabled(obj, false);
    pdl_config->rx_config->masterMode = (cy_en_tdm_device_cfg_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_CTL_MS, TDM_STRUCT_RX_CTL(base_rx));
    pdl_config->rx_config->wordSize = (cy_en_tdm_ws_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_CTL_WORD_SIZE, TDM_STRUCT_RX_CTL(base_rx));
    pdl_config->rx_config->format = (cy_en_tdm_format_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_CTL_FORMAT, TDM_STRUCT_RX_CTL(base_rx));

    uint32_t rx_if_ctl = TDM_STRUCT_RX_IF_CTL(base_rx);
    /* Divider in the config register is a less than the desired value */
    pdl_config->rx_config->clkDiv = (uint16_t)(_FLD2VAL(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_CLOCK_DIV, rx_if_ctl) + 1);
    pdl_config->rx_config->clkSel = (cy_en_tdm_clock_sel_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_CLOCK_SEL, rx_if_ctl);
    pdl_config->rx_config->sckPolarity = (cy_en_tdm_sckpolarity_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_SCK_POLARITY, rx_if_ctl);
    pdl_config->rx_config->fsyncPolarity = (cy_en_tdm_fsyncpolarity_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_FSYNC_POLARITY, rx_if_ctl);;
    pdl_config->rx_config->fsyncFormat = (cy_en_tdm_fsyncformat_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_FSYNC_FORMAT, rx_if_ctl);
    /* Channel size and count in the register are one less than the desired value */
    pdl_config->rx_config->channelNum = (uint8_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_CH_NR, rx_if_ctl) + 1;
    pdl_config->rx_config->channelSize = (uint8_t)_FLD2VAL(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_CH_SIZE, rx_if_ctl) + 1;
    pdl_config->rx_config->fifoTriggerLevel = _cyhal_audioss_fifo_trigger_level(obj, false);
    pdl_config->rx_config->chEn = TDM_STRUCT_RX_CH_CTL(base_rx);
    pdl_config->rx_config->signalInput = _FLD2VAL(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_ROUTE_CTL_MODE, TDM_STRUCT_RX_ROUTE_CTL(base_rx));
    pdl_config->rx_config->i2sMode = _FLD2BOOL(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_I2S_MODE, rx_if_ctl);
#else
#error "Unrecognized audio IP"
#endif
}

static cy_rslt_t _cyhal_audioss_populate_pdl_config(_cyhal_audioss_t *obj, _cyhal_audioss_pdl_config_t* pdl_config,
                                                    const _cyhal_audioss_config_t* hal_cfg,
                                                    uint16_t sclk_div_rx, uint16_t sclk_div_tx,
                                                    bool rx_en, bool tx_en, bool mclk_rx, bool mclk_tx)
{
#if defined(CY_IP_MXAUDIOSS)
    cy_en_i2s_len_t pdl_word_length_tx, pdl_channel_length_tx;
    cy_rslt_t result = _cyhal_audioss_length_to_pdl(obj->channel_length_tx, &pdl_channel_length_tx, obj);
    if (CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_audioss_length_to_pdl(obj->word_length_tx, &pdl_word_length_tx, obj);
    }
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    cy_en_i2s_len_t pdl_word_length_rx, pdl_channel_length_rx;
    if (CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_audioss_length_to_pdl(obj->channel_length_rx, &pdl_channel_length_rx, obj);
    }
    if (CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_audioss_length_to_pdl(obj->word_length_rx, &pdl_word_length_rx, obj);
    }
#endif

    if(CY_RSLT_SUCCESS == result)
    {
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
        pdl_config->txEnabled = tx_en;
        pdl_config->rxEnabled = rx_en;

        pdl_config->rxMasterMode = !hal_cfg->is_rx_slave;
        pdl_config->rxAlignment = hal_cfg->is_i2s ? CY_I2S_I2S_MODE : CY_I2S_TDM_MODE_A;
        pdl_config->rxWsPulseWidth = hal_cfg->rx_ws_full
                                ? CY_I2S_WS_ONE_CHANNEL_LENGTH : CY_I2S_WS_ONE_SCK_CYCLE;
        pdl_config->rxWatchdogEnable = false;
        pdl_config->rxWatchdogValue = 0u;
        pdl_config->rxSdiLatchingTime = false;
        pdl_config->rxSckoInversion = false;
        pdl_config->rxSckiInversion = false;
        pdl_config->rxChannels = hal_cfg->num_channels;
        pdl_config->rxChannelLength = pdl_channel_length_rx;
        pdl_config->rxWordLength = pdl_word_length_rx;
        pdl_config->rxSignExtension = false; /* All MSB are filled by zeros, per HAL API specification */
        pdl_config->rxFifoTriggerLevel = _CYHAL_AUDIOSS_FIFO_DEPTH / 2 - 1; // Trigger at half full
#else
        CY_UNUSED_PARAMETER(rx_en);
        CY_UNUSED_PARAMETER(tx_en);
#endif

#if defined(_CYHAL_AUDIOSS_TX_WATCHDOG_AVAILABLE)
        pdl_config->txWatchdogEnable = false;
        pdl_config->txWatchdogValue = 0u;
#endif

#if defined(_CYHAL_AUDIOSS_TRIGGERS_AVAILABLE)
        pdl_config->txDmaTrigger = false;
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
        pdl_config->rxDmaTrigger = false;
#endif
#endif

#if defined(_CYHAL_AUDIOSS_TX_SLAVE_AVAILABLE)
        pdl_config->txMasterMode = !hal_cfg->is_tx_slave;
        pdl_config->txSckiInversion = false;
        pdl_config->txSdoLatchingTime = false;
#endif
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
        /* Should be the same because RX and TX mclk must be the same if they are both enabled */
        CY_ASSERT(sclk_div_rx == sclk_div_tx || false == pdl_config->txEnabled || false == pdl_config->rxEnabled);
        pdl_config->clkDiv = (uint8_t)(pdl_config->txEnabled ? sclk_div_tx : sclk_div_rx);
#else
        CY_UNUSED_PARAMETER(sclk_div_rx);
        pdl_config->clkDiv = (uint8_t)(sclk_div_tx);
#endif
        pdl_config->extClk = mclk_tx; /* No separate rx/tx mclk selection on this IP */
        CY_UNUSED_PARAMETER(mclk_rx);
        /* TDM mode A == channel data starts on rising edge of WS */
        pdl_config->txAlignment = hal_cfg->is_i2s ? CY_I2S_I2S_MODE : CY_I2S_TDM_MODE_A;
        pdl_config->txWsPulseWidth = hal_cfg->tx_ws_full
                                ? CY_I2S_WS_ONE_CHANNEL_LENGTH : CY_I2S_WS_ONE_SCK_CYCLE;

        pdl_config->txSckoInversion = false;

        pdl_config->txChannels = hal_cfg->num_channels;
        pdl_config->txChannelLength = pdl_channel_length_tx;
        pdl_config->txWordLength = pdl_word_length_tx;
        pdl_config->txOverheadValue = CY_I2S_OVHDATA_ZERO; /* Per HAL API specification */
        pdl_config->txFifoTriggerLevel = _CYHAL_AUDIOSS_FIFO_DEPTH / 2 + 1; /* Trigger at half empty */
    }
#elif defined(CY_IP_MXTDM)
    cy_en_tdm_ws_t pdl_word_length_rx, pdl_word_length_tx;
    cy_rslt_t result = _cyhal_audioss_length_to_pdl(obj->word_length_tx, &pdl_word_length_tx, obj);
    if(CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_audioss_length_to_pdl(obj->word_length_rx, &pdl_word_length_rx, obj);
    }
    if(CY_RSLT_SUCCESS == result)
    {
        /* Configure TX */
        pdl_config->tx_config->enable = tx_en;
        pdl_config->tx_config->masterMode = hal_cfg->is_tx_slave ? CY_TDM_DEVICE_SLAVE : CY_TDM_DEVICE_MASTER;
        pdl_config->tx_config->wordSize = pdl_word_length_tx;
        pdl_config->tx_config->format = hal_cfg->is_i2s ? CY_TDM_LEFT_DELAYED : CY_TDM_LEFT;
        pdl_config->tx_config->clkDiv = sclk_div_tx;
        /* Only clock 0 from the srss hooked up on current hardware */
        pdl_config->tx_config->clkSel = mclk_tx ? CY_TDM_SEL_MCLK_IN : CY_TDM_SEL_SRSS_CLK0;
        pdl_config->tx_config->sckPolarity = CY_TDM_CLK;
        /* For I2S, frame sync aka word select starts out low */
        pdl_config->tx_config->fsyncPolarity = hal_cfg->is_i2s ? CY_TDM_SIGN_INVERTED : CY_TDM_SIGN;
        pdl_config->tx_config->fsyncFormat = hal_cfg->tx_ws_full ? CY_TDM_CH_PERIOD : CY_TDM_BIT_PERIOD;
        pdl_config->tx_config->channelNum = hal_cfg->num_channels;
        pdl_config->tx_config->channelSize = obj->channel_length_tx;
        pdl_config->tx_config->fifoTriggerLevel = _CYHAL_AUDIOSS_FIFO_DEPTH / 2 + 1; /* Trigger at half empty */
        pdl_config->tx_config->chEn = hal_cfg->channel_mask;
        pdl_config->tx_config->signalInput = 0; /* TX and RX signaling independent */
        pdl_config->tx_config->i2sMode = hal_cfg->is_i2s;

        /* Configure RX */
        pdl_config->rx_config->enable = rx_en;
        pdl_config->rx_config->masterMode = hal_cfg->is_rx_slave ? CY_TDM_DEVICE_SLAVE : CY_TDM_DEVICE_MASTER;
        pdl_config->rx_config->wordSize = pdl_word_length_rx;
        pdl_config->rx_config->format = hal_cfg->is_i2s ? CY_TDM_LEFT_DELAYED : CY_TDM_LEFT;
        pdl_config->rx_config->clkDiv = sclk_div_rx;
        /* Only clock 0 from the srss hooked up on current hardware */
        pdl_config->rx_config->clkSel = mclk_rx ? CY_TDM_SEL_MCLK_IN : CY_TDM_SEL_SRSS_CLK0;
        pdl_config->rx_config->sckPolarity = CY_TDM_CLK;
        /* For I2S, frame sync aka word select starts out low */
        pdl_config->rx_config->fsyncPolarity = hal_cfg->is_i2s ? CY_TDM_SIGN_INVERTED : CY_TDM_SIGN;
        pdl_config->rx_config->fsyncFormat = hal_cfg->rx_ws_full ? CY_TDM_CH_PERIOD : CY_TDM_BIT_PERIOD;
        pdl_config->rx_config->channelNum = hal_cfg->num_channels;
        pdl_config->rx_config->channelSize = obj->channel_length_rx;
        pdl_config->rx_config->fifoTriggerLevel = _CYHAL_AUDIOSS_FIFO_DEPTH / 2 + 1; /* Trigger at half empty */
        pdl_config->rx_config->chEn = hal_cfg->channel_mask;
        pdl_config->rx_config->signalInput = 0; /* TX and RX signaling independent */
        pdl_config->rx_config->i2sMode = hal_cfg->is_i2s;
        pdl_config->rx_config->signExtend = CY_ZERO_EXTEND;
        pdl_config->rx_config->lateSample = false;
    }
#else
#error "Unrecognized audio IP"
#endif
    return result;
}

#if (CYHAL_DRIVER_AVAILABLE_DMA)
/* Round up the word length to the next power of 2
*  NOTE: This method used only in I2S HAL function related to DMA.
*   To avoid compilation warning declare this function only when DMA is available
*/
static uint8_t _cyhal_audioss_rounded_word_length(_cyhal_audioss_t *obj, bool is_tx)
{
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    uint8_t word_length = is_tx ? obj->word_length_tx : obj->word_length_rx;
#else
    CY_UNUSED_PARAMETER(is_tx);
    uint8_t word_length = obj->word_length_tx;
#endif
    CY_ASSERT(word_length <= 32);
    if(word_length <= 8)
    {
        return 8u;
    }
    else if(word_length <= 16)
    {
        return 16u;
    }

    return 32u;
}
#endif /* (CYHAL_DRIVER_AVAILABLE_DMA) */

cy_rslt_t _cyhal_audioss_write_async(_cyhal_audioss_t *obj, const void *tx, size_t tx_length)
{
    CY_ASSERT(NULL != obj);
    if (obj->pm_transition_ready)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }

    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    obj->async_tx_buff = tx;
    obj->async_tx_length = tx_length;
    cyhal_system_critical_section_exit(savedIntrStatus);
    switch(obj->async_mode)
    {
        case CYHAL_ASYNC_SW:
        {
            /* Write as much as we can now, then set up an interrupt to do the rest
            * This is a potentially long operation but we don't want other I2S operations to
            * interleave with it. So do a "mini critical section" and disable the interrupts for this block only.
            */
            uint32_t old_events = _cyhal_audioss_disable_events(obj, true);
            // Safe to cast away volatile here because we're calling write_until_full from within
            // a critical section, so it should not change out from under us during this call
            _cyhal_audioss_write_until_full(obj, (const void**)(&obj->async_tx_buff), (size_t *)(&obj->async_tx_length));
            _cyhal_audioss_restore_events(obj, true, old_events);
            if(obj->async_tx_length > 0)
            {
                _cyhal_audioss_update_enabled_events(obj);
            }
            else
            {
                _cyhal_audioss_process_event(obj, obj->interface->event_tx_complete);
            }
            break;
        }
        case CYHAL_ASYNC_DMA:
        {
            // Don't directly kick off the DMA here - it will be triggered
            // from the interrupt handler when the FIFO drops below the threshold
            // (which may have already happened by the time we get here if the
            // application already had the half-empty or empty event enabled)
            _cyhal_audioss_update_enabled_events(obj);
            break;
        }
        default:
            CY_ASSERT(0); /* Unrecognized async mode */
            break;
    }

    return CY_RSLT_SUCCESS;
}

cy_rslt_t _cyhal_audioss_set_async_mode(_cyhal_audioss_t *obj, cyhal_async_mode_t mode, uint8_t dma_priority)
{
    CY_ASSERT(NULL != obj);

// We don't support swapping the async mode out from under a pending transfer.
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    CY_ASSERT(false == _cyhal_audioss_is_read_pending(obj));
#endif
    CY_ASSERT(false == _cyhal_audioss_is_write_pending(obj));

    cy_rslt_t result = CY_RSLT_SUCCESS;


    if(mode == CYHAL_ASYNC_DMA)
    {
    #if (CYHAL_DRIVER_AVAILABLE_DMA)
        // Reserve a DMA channel for each direction that is enabled
        if(_cyhal_audioss_is_direction_enabled(obj, true) && CYHAL_RSC_INVALID == obj->tx_dma.resource.type)
        {
            /* Reserve a DMA channel for async transmit if tx is enabled */
            result = cyhal_dma_init(&obj->tx_dma, CYHAL_DMA_PRIORITY_DEFAULT, CYHAL_DMA_DIRECTION_MEM2PERIPH);
            cyhal_dma_register_callback(&obj->tx_dma, &_cyhal_audioss_dma_handler_tx, obj);
        }
        #if defined(_CYHAL_AUDIOSS_RX_ENABLED)
        if(_cyhal_audioss_is_direction_enabled(obj, false) && CYHAL_RSC_INVALID == obj->rx_dma.resource.type)
        {
            /* Reserve a DMA channel for async receive if rx is enabled */
            result = cyhal_dma_init(&obj->rx_dma, CYHAL_DMA_PRIORITY_DEFAULT, CYHAL_DMA_DIRECTION_PERIPH2MEM);
            cyhal_dma_register_callback(&obj->rx_dma, &_cyhal_audioss_dma_handler_rx, obj);
        }
        #endif /* defined(_CYHAL_AUDIOSS_RX_ENABLED) */
    #else
        CY_ASSERT(0); /* DMA driver is not available */
    #endif /* (CYHAL_DRIVER_AVAILABLE_DMA) */
    }
    else
    {
        /* Free the DMA instances if we reserved them but don't need them anymore */
        if(CYHAL_RSC_INVALID != obj->tx_dma.resource.type)
        {
        #if (CYHAL_DRIVER_AVAILABLE_DMA)
            cyhal_dma_free(&obj->tx_dma);
        #endif /* (CYHAL_DRIVER_AVAILABLE_DMA) */
            obj->tx_dma.resource.type = CYHAL_RSC_INVALID;
        }
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
        if(CYHAL_RSC_INVALID != obj->rx_dma.resource.type)
        {
        #if (CYHAL_DRIVER_AVAILABLE_DMA)
            cyhal_dma_free(&obj->rx_dma);
        #endif /* (CYHAL_DRIVER_AVAILABLE_DMA) */
            obj->rx_dma.resource.type = CYHAL_RSC_INVALID;
        }
#endif /* defined(_CYHAL_AUDIOSS_RX_ENABLED) */
    }

    if(CY_RSLT_SUCCESS == result)
    {
        obj->async_mode = mode;
        obj->async_dma_priority = dma_priority;
    }
    return result;
}

bool _cyhal_audioss_is_read_pending(_cyhal_audioss_t *obj)
{
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    return (NULL != obj->async_rx_buff);
#else
    CY_UNUSED_PARAMETER(obj);
    return false;
#endif
}

bool _cyhal_audioss_is_write_pending(_cyhal_audioss_t *obj)
{
    return (NULL != obj->async_tx_buff);
}

cy_rslt_t _cyhal_audioss_abort_read_async(_cyhal_audioss_t *obj)
{
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    uint32_t saved_intr = cyhal_system_critical_section_enter();
    obj->async_rx_buff = NULL;
    _cyhal_audioss_update_enabled_events(obj);
    cyhal_system_critical_section_exit(saved_intr);
    return CY_RSLT_SUCCESS;
#else
    return obj->interface->err_not_supported;
#endif
}

cy_rslt_t _cyhal_audioss_abort_write_async(_cyhal_audioss_t *obj)
{
    uint32_t saved_intr = cyhal_system_critical_section_enter();
    obj->async_tx_buff = NULL;
    _cyhal_audioss_update_enabled_events(obj);
    cyhal_system_critical_section_exit(saved_intr);
    return CY_RSLT_SUCCESS;
}

#if defined(CY_IP_MXAUDIOSS)
static uint8_t _cyhal_audioss_length_from_pdl(cy_en_i2s_len_t pdl_length)
{
    switch(pdl_length)
    {
        case CY_I2S_LEN8:
            return 8u;
        case CY_I2S_LEN16:
            return 16u;
        case CY_I2S_LEN18:
            return 18u;
        case CY_I2S_LEN20:
            return 20u;
        case CY_I2S_LEN24:
            return 24u;
        case CY_I2S_LEN32:
            return 32u;
        default:
            CY_ASSERT(false); /* Should never get here */
            return 32u;
    }
}

static cy_rslt_t _cyhal_audioss_length_to_pdl(uint8_t user_length, cy_en_i2s_len_t *pdl_length, const _cyhal_audioss_t *obj)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    switch(user_length)
    {
        case 8u:
            *pdl_length = CY_I2S_LEN8;
            break;
        case 16u:
            *pdl_length = CY_I2S_LEN16;
            break;
        case 18u:
            *pdl_length = CY_I2S_LEN18;
            break;
        case 20u:
            *pdl_length = CY_I2S_LEN20;
            break;
        case 24u:
            *pdl_length = CY_I2S_LEN24;
            break;
        case 32u:
            *pdl_length = CY_I2S_LEN32;
            break;
        default:
            *pdl_length = CY_I2S_LEN32;
            result = obj->interface->err_invalid_arg;
    }
    return result;
}
#elif defined(CY_IP_MXTDM)
static uint8_t _cyhal_audioss_length_from_pdl(cy_en_tdm_ws_t pdl_length)
{
    switch(pdl_length)
    {
        case CY_TDM_SIZE_8:
            return 8u;
        case CY_TDM_SIZE_10:
            return 10u;
        case CY_TDM_SIZE_12:
            return 12u;
        case CY_TDM_SIZE_14:
            return 14u;
        case CY_TDM_SIZE_16:
            return 16u;
        case CY_TDM_SIZE_18:
            return 18u;
        case CY_TDM_SIZE_20:
            return 20u;
        case CY_TDM_SIZE_24:
            return 24u;
        case CY_TDM_SIZE_32:
            return 32u;
        default:
            CY_ASSERT(false); /* Should never get here */
            return 32u;
    }
}

static cy_rslt_t _cyhal_audioss_length_to_pdl(uint8_t user_length, cy_en_tdm_ws_t *pdl_length, const _cyhal_audioss_t *obj)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    switch(user_length)
    {
        case 8u:
            *pdl_length = CY_TDM_SIZE_8;
            break;
        case 10u:
            *pdl_length = CY_TDM_SIZE_10;
            break;
        case 12u:
            *pdl_length = CY_TDM_SIZE_12;
            break;
        case 14u:
            *pdl_length = CY_TDM_SIZE_14;
            break;
        case 16u:
            *pdl_length = CY_TDM_SIZE_16;
            break;
        case 18u:
            *pdl_length = CY_TDM_SIZE_18;
            break;
        case 20u:
            *pdl_length = CY_TDM_SIZE_20;
            break;
        case 24u:
            *pdl_length = CY_TDM_SIZE_24;
            break;
        case 32u:
            *pdl_length = CY_TDM_SIZE_32;
            break;
        default:
            *pdl_length = CY_TDM_SIZE_32;
            result = obj->interface->err_invalid_arg;
    }
    return result;
}
#else
#error "Unrecognized audio IP"
#endif

#if defined(CY_IP_MXAUDIOSS)
static void _cyhal_audioss_irq_handler(void)
{
    _cyhal_system_irq_t irqn = _cyhal_irq_get_active();
    uint8_t block = _cyhal_audioss_get_block_from_irqn(irqn);
    _cyhal_audioss_t* obj = _cyhal_audioss_config_structs[block];

    uint32_t interrupt_status = Cy_I2S_GetInterruptStatusMasked(obj->base);
    Cy_I2S_ClearInterrupt(obj->base, interrupt_status);
    uint32_t event = obj->interface->convert_interrupt_cause(interrupt_status);
    _cyhal_audioss_process_event(obj, event);
}
#elif defined(CY_IP_MXTDM)

#if defined (COMPONENT_CAT5)
static void _cyhal_audioss_irq_handler_rx(_cyhal_system_irq_t irqn)
{
#else
static void _cyhal_audioss_irq_handler_rx()
{
    _cyhal_system_irq_t irqn = _cyhal_irq_get_active();
#endif
    uint8_t block = _cyhal_audioss_get_block_from_irqn(irqn);
    _cyhal_audioss_t* obj = _cyhal_audioss_config_structs[block];

    uint32_t interrupt_status = Cy_AudioTDM_GetRxInterruptStatusMasked(&obj->base->TDM_RX_STRUCT);
    Cy_AudioTDM_ClearRxInterrupt(&obj->base->TDM_RX_STRUCT, interrupt_status);
    uint32_t event = obj->interface->convert_interrupt_cause(interrupt_status, false);
    _cyhal_audioss_process_event(obj, event);
}

#if defined (COMPONENT_CAT5)
static void _cyhal_audioss_irq_handler_tx(_cyhal_system_irq_t irqn)
{
#else
static void _cyhal_audioss_irq_handler_tx()
{
    _cyhal_system_irq_t irqn = _cyhal_irq_get_active();
#endif
    uint8_t block = _cyhal_audioss_get_block_from_irqn(irqn);
    _cyhal_audioss_t* obj = _cyhal_audioss_config_structs[block];

    uint32_t interrupt_status = Cy_AudioTDM_GetTxInterruptStatusMasked(&obj->base->TDM_TX_STRUCT);
    Cy_AudioTDM_ClearTxInterrupt(&obj->base->TDM_TX_STRUCT, interrupt_status);
    uint32_t event = obj->interface->convert_interrupt_cause(interrupt_status, true);
    _cyhal_audioss_process_event(obj, event);
}

#if defined (COMPONENT_CAT5)
static void _cyhal_audioss_irq_handler(UINT8 instance, BOOL8 rx_int)
{
    (rx_int) ? _cyhal_audioss_irq_handler_rx(instance) : _cyhal_audioss_irq_handler_tx(instance);
}
#endif
#endif

static void _cyhal_audioss_update_enabled_events(_cyhal_audioss_t *obj)
{
    uint32_t events = obj->user_enabled_events;
    if(NULL != obj->async_tx_buff && obj->async_tx_length > 0)
    {
        events |= (obj->interface->event_mask_empty | obj->interface->event_mask_half_empty);
    }
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    if(NULL != obj->async_rx_buff && obj->async_rx_length > 0)
    {
        events |= (obj->interface->event_mask_full | obj->interface->event_mask_half_full);
    }
#endif

#if defined(CY_IP_MXAUDIOSS)
    uint32_t mask = obj->interface->convert_to_pdl(events);
    // The register is 24 bits wide but the hardware pads the value out with 1's when read.
    // So mask down to just the bits that we actually care about.
    uint32_t old_mask = Cy_I2S_GetInterruptMask(obj->base) & CY_I2S_INTR_MASK;

    // Clear the interrupts that are about to be enabled to avoid spurious firing
    uint32_t new_interrupts = mask & (~old_mask);
    Cy_I2S_ClearInterrupt(obj->base, new_interrupts);

    Cy_I2S_SetInterruptMask(obj->base, mask);
#elif defined(CY_IP_MXTDM)
    uint32_t tx_mask = obj->interface->convert_to_pdl(events, true);
    uint32_t old_tx_mask = Cy_AudioTDM_GetTxInterruptMask(&obj->base->TDM_TX_STRUCT);

    // Clear the interrupts that are about to be enabled to avoid spurious firing
    uint32_t new_interrupts_tx = tx_mask & (~old_tx_mask);
    Cy_AudioTDM_ClearTxInterrupt(&obj->base->TDM_TX_STRUCT, new_interrupts_tx);
    Cy_AudioTDM_SetTxInterruptMask(&obj->base->TDM_TX_STRUCT, tx_mask);

    uint32_t rx_mask = obj->interface->convert_to_pdl(events, false);
    uint32_t old_rx_mask = Cy_AudioTDM_GetRxInterruptMask(&obj->base->TDM_RX_STRUCT);

    // Clear the interrupts that are about to be enabled to avoid spurious firing
    uint32_t new_interrupts_rx = rx_mask & (~old_rx_mask);
    Cy_AudioTDM_ClearRxInterrupt(&obj->base->TDM_RX_STRUCT, new_interrupts_rx);
    Cy_AudioTDM_SetRxInterruptMask(&obj->base->TDM_RX_STRUCT, rx_mask);
#endif
}

#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
static void _cyhal_audioss_update_rx_trigger_level(_cyhal_audioss_t *obj)
{
    // If we're doing an async read and the amount remaining is less than
    // the standard trigger level, temporarily reduce it so that we get
    // an interrupt as soon as the amount the user requested is ready
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    uint8_t trigger_level = obj->user_fifo_level_rx;
    if(NULL != obj->async_rx_buff
       && obj->async_rx_length < trigger_level
       && obj->async_rx_length > 0)
    {
        trigger_level = obj->async_rx_length;
    }

#if defined(CY_IP_MXAUDIOSS)
    // Safe to do a blind write of this register because the only other bits are
    // CLEAR, which is only set temporarily from clear_tx, and FREEZE, which is
    // never used by this driver (it exists for debugging purposes only)
    obj->base->RX_FIFO_CTL = (uint32_t) (trigger_level << I2S_RX_FIFO_CTL_TRIGGER_LEVEL_Pos);
#elif defined(CY_IP_MXTDM)
    uint32_t value = obj->base->TDM_RX_STRUCT.RX_FIFO_CTL;
    value &= ~TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_TRIGGER_LEVEL_Msk;
    value |= trigger_level << TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_TRIGGER_LEVEL_Pos;
    obj->base->TDM_RX_STRUCT.RX_FIFO_CTL = value;
#endif
    cyhal_system_critical_section_exit(savedIntrStatus);
}
#endif

static uint32_t _cyhal_audioss_disable_events(_cyhal_audioss_t *obj, bool tx)
{
#if defined(CY_IP_MXAUDIOSS)
    CY_UNUSED_PARAMETER(tx);
    uint32_t old_interrupt_mask = Cy_I2S_GetInterruptMask(obj->base);
    Cy_I2S_SetInterruptMask(obj->base, 0u);
    return old_interrupt_mask;
#elif defined(CY_IP_MXTDM)
    uint32_t old_interrupt_mask;
    if(tx)
    {
        old_interrupt_mask = Cy_AudioTDM_GetTxInterruptMask(&obj->base->TDM_TX_STRUCT);
        Cy_AudioTDM_SetTxInterruptMask(&obj->base->TDM_TX_STRUCT, 0u);
    }
    else
    {
        old_interrupt_mask = Cy_AudioTDM_GetRxInterruptMask(&obj->base->TDM_RX_STRUCT);
        Cy_AudioTDM_SetRxInterruptMask(&obj->base->TDM_RX_STRUCT, 0u);
    }
    return old_interrupt_mask;
#endif
}

static void _cyhal_audioss_restore_events(_cyhal_audioss_t *obj, bool tx, uint32_t old_events)
{
#if defined(CY_IP_MXAUDIOSS)
    CY_UNUSED_PARAMETER(tx);
    Cy_I2S_SetInterruptMask(obj->base, old_events);
#elif defined(CY_IP_MXTDM)
    if(tx)
    {
        Cy_AudioTDM_SetTxInterruptMask(&obj->base->TDM_TX_STRUCT, old_events);
    }
    else
    {
        Cy_AudioTDM_SetRxInterruptMask(&obj->base->TDM_RX_STRUCT, old_events);
    }
#endif
}

#if defined(_CYHAL_AUDIOSS_RX_ENABLED) && (CYHAL_DRIVER_AVAILABLE_DMA)
static cy_rslt_t _cyhal_audioss_dma_perform_rx(_cyhal_audioss_t *obj)
{
    // We could have received an event after we started the DMA but before it
    // managed to bring the FIFO below the threshold
    if(cyhal_dma_is_busy(&(obj->rx_dma)))
        return CY_RSLT_SUCCESS;
    /* ISR triggers when we have one more entry in the FIFO than the trigger level */
    size_t transfer_size = _cyhal_audioss_fifo_trigger_level(obj, false) + 1;
    if (transfer_size >= obj->async_rx_length)
    {
        transfer_size = obj->async_rx_length;
        // Only want the user callback to be call on the last dma transfer.
        cyhal_dma_enable_event(&(obj->rx_dma), CYHAL_DMA_TRANSFER_COMPLETE, obj->async_dma_priority, true);
    }

    cyhal_dma_cfg_t dma_cfg =
    {
#if defined(CY_IP_MXAUDIOSS)
        .src_addr = (uint32_t)(&(obj->base->RX_FIFO_RD)),
#elif defined(CY_IP_MXTDM)
        .src_addr = (uint32_t)(&(obj->base->TDM_RX_STRUCT.RX_FIFO_RD)),
#endif
        .src_increment = 0,
        .dst_addr = (uint32_t)obj->async_rx_buff,
        .dst_increment = 1,
        .transfer_width = _cyhal_audioss_rounded_word_length(obj, false),
        .length = transfer_size,
        .burst_size = 0,
        .action = CYHAL_DMA_TRANSFER_FULL,
    };
    cy_rslt_t result = cyhal_dma_configure(&(obj->rx_dma), &dma_cfg);

    if(CY_RSLT_SUCCESS == result)
    {
        result = cyhal_dma_enable(&(obj->rx_dma));
    }

    // Update the buffer first so that it's guaranteed to be correct whenever the DMA completes
    if(CY_RSLT_SUCCESS == result)
    {
        size_t increment_bytes = transfer_size * (_cyhal_audioss_rounded_word_length(obj, false) / 8);
        uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
        obj->async_rx_buff = (void*)(((uint8_t*) obj->async_rx_buff) + increment_bytes);
        obj->async_rx_length -= transfer_size;
        _cyhal_audioss_update_rx_trigger_level(obj);
        _cyhal_audioss_update_enabled_events(obj);
        cyhal_system_critical_section_exit(savedIntrStatus);

        result = cyhal_dma_start_transfer(&(obj->rx_dma));
    }

    return result;
}
#endif /* defined(_CYHAL_AUDIOSS_RX_ENABLED) && (CYHAL_DRIVER_AVAILABLE_DMA) */

#if (CYHAL_DRIVER_AVAILABLE_DMA)
static cy_rslt_t _cyhal_audioss_dma_perform_tx(_cyhal_audioss_t *obj)
{
    // We could have received an event after the DMA brought the FIFO below the
    // threshold but before the DMA is entirely complete
    if(cyhal_dma_is_busy(&(obj->tx_dma)))
        return CY_RSLT_SUCCESS;

    CY_ASSERT(NULL != obj->async_tx_buff);

    /* ISR triggers when the FIFO count less than the trigger level */
    size_t transfer_size = _cyhal_audioss_fifo_trigger_level(obj, true) + 1;
    if (transfer_size >= obj->async_tx_length)
    {
        transfer_size = obj->async_tx_length;
        // Only want the user callback to be call on the last dma transfer.
        cyhal_dma_enable_event(&(obj->tx_dma), CYHAL_DMA_TRANSFER_COMPLETE, obj->async_dma_priority, true);
    }

    cyhal_dma_cfg_t dma_cfg =
    {
        .src_addr = (uint32_t)obj->async_tx_buff,
        .src_increment = 1,
#if defined(CY_IP_MXAUDIOSS)
        .dst_addr = (uint32_t)(&(obj->base->TX_FIFO_WR)),
#elif defined(CY_IP_MXTDM)
        .dst_addr = (uint32_t)(&(obj->base->TDM_TX_STRUCT.TX_FIFO_WR)),
#endif
        .dst_increment = 0,
        .transfer_width = _cyhal_audioss_rounded_word_length(obj, true),
        .length = transfer_size,
        .burst_size = 0,
        .action = CYHAL_DMA_TRANSFER_FULL,
    };
    cy_rslt_t result = cyhal_dma_configure(&(obj->tx_dma), &dma_cfg);

    if(CY_RSLT_SUCCESS == result)
    {
        result = cyhal_dma_enable(&(obj->tx_dma));
    }

    // Update the buffer first so that it's guaranteed to be correct whenever the DMA completes
    if(CY_RSLT_SUCCESS == result)
    {
        size_t increment_bytes = transfer_size * (_cyhal_audioss_rounded_word_length(obj, true) / 8);
        uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
        obj->async_tx_buff = (void*)(((uint8_t*) obj->async_tx_buff) + increment_bytes);
        obj->async_tx_length -= transfer_size;

        // Do this after we've updated async_tx_buff/length because once we have kicked
        // off the final DMA transfer there is no further action we will take on the
        // half-empty/empty events, and we don't want those to wind upstarving the
        // DMA complete event
        _cyhal_audioss_update_enabled_events(obj);
        cyhal_system_critical_section_exit(savedIntrStatus);

        result = cyhal_dma_start_transfer(&(obj->tx_dma));
    }

    return result;
}
#endif /* (CYHAL_DRIVER_AVAILABLE_DMA) */

static uint32_t _cyhal_audioss_get_num_in_fifo(_cyhal_audioss_t *obj, bool is_tx)
{
#if defined(CY_IP_MXAUDIOSS)
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    return is_tx ? Cy_I2S_GetNumInTxFifo(obj->base) : Cy_I2S_GetNumInRxFifo(obj->base);
#else
    CY_UNUSED_PARAMETER(is_tx);
    return Cy_I2S_GetNumInTxFifo(obj->base);
#endif
#elif defined(CY_IP_MXTDM)
    return is_tx ? Cy_AudioTDM_GetNumInTxFifo(&obj->base->TDM_TX_STRUCT)
                 : Cy_AudioTDM_GetNumInRxFifo(&obj->base->TDM_RX_STRUCT);
#endif
}

#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
static uint32_t _cyhal_audioss_read_fifo(_cyhal_audioss_t *obj)
{
#if defined(CY_IP_MXAUDIOSS)
    return Cy_I2S_ReadRxData(obj->base);
#elif defined(CY_IP_MXTDM)
    return Cy_AudioTDM_ReadRxData(&obj->base->TDM_RX_STRUCT);
#endif
}
#endif

static void _cyhal_audioss_write_fifo(_cyhal_audioss_t *obj, uint32_t value)
{
#if defined(CY_IP_MXAUDIOSS)
    Cy_I2S_WriteTxData(obj->base, value);
#elif defined(CY_IP_MXTDM)
    Cy_AudioTDM_WriteTxData(&obj->base->TDM_TX_STRUCT, value);
#endif
}

#if defined(_CYHAL_AUDIOSS_RX_ENABLED) && (CYHAL_DRIVER_AVAILABLE_DMA)
/* Callback argument is the I2S instance */
static void _cyhal_audioss_dma_handler_rx(void *callback_arg, cyhal_dma_event_t event)
{
    CY_UNUSED_PARAMETER(event);
    /* We only hook this handler up when we're doing the final transfer, so send the completed event */
    CY_ASSERT(CYHAL_DMA_TRANSFER_COMPLETE == event);

    _cyhal_audioss_t *obj = (_cyhal_audioss_t*)callback_arg;
    obj->async_rx_buff = NULL;
    cyhal_dma_enable_event(&obj->rx_dma, CYHAL_DMA_TRANSFER_COMPLETE, obj->async_dma_priority, false);
    _cyhal_audioss_process_event(obj, obj->interface->event_rx_complete);
}
#endif /* defined(_CYHAL_AUDIOSS_RX_ENABLED) && (CYHAL_DRIVER_AVAILABLE_DMA) */

#if (CYHAL_DRIVER_AVAILABLE_DMA)
/* Callback argument is the I2S instance */
static void _cyhal_audioss_dma_handler_tx(void *callback_arg, cyhal_dma_event_t event)
{
    CY_UNUSED_PARAMETER(event);
    /* We only hook this handler up when we're doing the final transfer, so send the completed event */
    CY_ASSERT(CYHAL_DMA_TRANSFER_COMPLETE == event);

    _cyhal_audioss_t *obj = (_cyhal_audioss_t*)callback_arg;
    obj->async_tx_buff = NULL;
    cyhal_dma_enable_event(&obj->tx_dma, CYHAL_DMA_TRANSFER_COMPLETE, obj->async_dma_priority, false);
    _cyhal_audioss_process_event(obj, obj->interface->event_tx_complete);
}
#endif /* (CYHAL_DRIVER_AVAILABLE_DMA) */

static void _cyhal_audioss_process_event(_cyhal_audioss_t *obj, uint32_t event)
{
    if(0 != (event & (obj->interface->event_mask_empty | obj->interface->event_mask_half_empty)))
    {
        /* We should normally not get the "empty" interrupt during an async transfer because we
         * should be topping the FIFO back up after each half-empty interrupt. But in case something
         * delays our response and the FIFO gets all the way to empty, listen for that as well
         */
        uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
        if(NULL != obj->async_tx_buff && obj->async_tx_length > 0)
        {
            switch(obj->async_mode)
            {
                case CYHAL_ASYNC_SW:
                {
                    /* Write as much as we can out until the FIFO is full
                     * This is a potentially long operation but we don't want other I2S operations to
                     * interleave with it. So switch to a "mini critical section" and disable the
                     * interrupts for this block only while we're copying
                     */
                    uint32_t old_events = _cyhal_audioss_disable_events(obj, true);
                    cyhal_system_critical_section_exit(savedIntrStatus);
                    // Safe to cast away volatile here because we're calling write_until_full from within
                    // a critical section, so it should not change out from under us during this call
                    _cyhal_audioss_write_until_full(obj, (const void**)(&obj->async_tx_buff), (size_t *)(&obj->async_tx_length));

                    // Re-enter the global critical section so that the exit below behaves correctly
                    savedIntrStatus = cyhal_system_critical_section_enter();
                    _cyhal_audioss_restore_events(obj, true, old_events);
                    if(0 == obj->async_tx_length)
                    {
                        /* We finished the async transfer. */
                        event |= obj->interface->event_tx_complete;
                    }
                    break;
                }
                case CYHAL_ASYNC_DMA:
                {
                #if (CYHAL_DRIVER_AVAILABLE_DMA)
                    cy_rslt_t result = _cyhal_audioss_dma_perform_tx(obj);
                    CY_UNUSED_PARAMETER(result);
                    CY_ASSERT(CY_RSLT_SUCCESS == result);
                #else
                    CY_ASSERT(0); /* DMA driver is not available */
                #endif /* (CYHAL_DRIVER_AVAILABLE_DMA) */
                    break;
                }
                default:
                    CY_ASSERT(0); /* Unrecognized async mode */
                    break;
            }
        }

        cyhal_system_critical_section_exit(savedIntrStatus);
    }

#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    if(0 != (event & (obj->interface->event_mask_full | obj->interface->event_mask_half_full)))
    {
        /* Similar to TX, we don't expect to receive the "full" interrupt, but check for it out of caution */
        uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
        if(NULL != obj->async_rx_buff && obj->async_rx_length > 0)
        {
            switch(obj->async_mode)
            {
                case CYHAL_ASYNC_SW:
                {
                   /* Read as much as we can until the FIFO is empty
                     * This is a potentially long operation but we don't want other I2S operations to
                     * interleave with it. So switch to a "mini critical section" and disable the
                     * interrupts for this block only while we're copying
                    */
                   uint32_t old_events = _cyhal_audioss_disable_events(obj, false);
                   cyhal_system_critical_section_exit(savedIntrStatus);
                   // Safe to cast away volatile here because we're calling read_until_empty from within
                   // a critical section, so it should not change out from under us during this call
                   _cyhal_audioss_read_until_empty(obj, (void**)(&obj->async_rx_buff), (size_t*)(&obj->async_rx_length));
                   // Re-enter the global critical section so that the exit below behaves correctly
                   savedIntrStatus = cyhal_system_critical_section_enter();
                   _cyhal_audioss_restore_events(obj, false, old_events);
                   _cyhal_audioss_update_enabled_events(obj);
                   if(0 == obj->async_rx_length)
                   {
                       /* We finished the async transfer.  */
                       event |= obj->interface->event_rx_complete;
                   }
                   break;
                }
                case CYHAL_ASYNC_DMA:
                #if (CYHAL_DRIVER_AVAILABLE_DMA)
                   _cyhal_audioss_dma_perform_rx(obj);
                #else
                    CY_ASSERT(0); /* DMA driver is not available */
                #endif /* (CYHAL_DRIVER_AVAILABLE_DMA) */
                   break;

                default:
                   CY_ASSERT(0); /* Unrecognized async mode */
            }

            // During async rx transfers, we may temporarily set the trigger level below half-full.
            // So make sure that it's a real "half full" and skip propagating to the user if it isn't
#if defined(CY_IP_MXAUDIOSS)
            uint8_t trigger_level = (obj->base->RX_FIFO_CTL & I2S_RX_FIFO_CTL_TRIGGER_LEVEL_Msk) >> I2S_RX_FIFO_CTL_TRIGGER_LEVEL_Pos;
#elif defined(CY_IP_MXTDM)
            uint8_t trigger_level = (obj->base->TDM_RX_STRUCT.RX_FIFO_CTL & TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_FIFO_CTL_TRIGGER_LEVEL_Msk) >> TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_FIFO_CTL_TRIGGER_LEVEL_Pos;
#endif
            if(trigger_level != obj->user_fifo_level_rx)
            {
                event &= ~(obj->interface->event_mask_half_full);
            }
        }

        cyhal_system_critical_section_exit(savedIntrStatus);
    }
#endif /* defined(_CYHAL_AUDIOSS_RX_ENABLED) */

    /* Mark async transfer as complete if we just finished one. */
    if(0 != (event & obj->interface->event_tx_complete))
    {
        obj->async_tx_buff = NULL;
        _cyhal_audioss_update_enabled_events(obj);
    }

#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    if(0 != (event & obj->interface->event_rx_complete))
    {
        obj->async_rx_buff = NULL;
        _cyhal_audioss_update_enabled_events(obj);
    }
#endif /* defined(_CYHAL_AUDIOSS_RX_ENABLED) */

    if(0 != (event & obj->user_enabled_events))
    {
        obj->interface->invoke_user_callback(obj, event & obj->user_enabled_events);
    }
}

static bool _cyhal_audioss_pm_callback(cyhal_syspm_callback_state_t state, cyhal_syspm_callback_mode_t mode, void* callback_arg)
{
    _cyhal_audioss_t *obj = (_cyhal_audioss_t *)callback_arg;
    CY_UNUSED_PARAMETER(state);

    switch(mode)
    {
        case CYHAL_SYSPM_CHECK_READY:
        {
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
            bool is_active = _cyhal_audioss_is_rx_enabled(obj)
                          || _cyhal_audioss_is_tx_enabled(obj);
            obj->pm_transition_ready = !is_active && !(_cyhal_audioss_is_read_pending(obj) || _cyhal_audioss_is_tx_busy(obj));
#else
            bool is_active = _cyhal_audioss_is_tx_enabled(obj);
            obj->pm_transition_ready = !is_active && !_cyhal_audioss_is_tx_busy(obj);
#endif /* defined(_CYHAL_AUDIOSS_RX_ENABLED) */
            return obj->pm_transition_ready;
        }
        case CYHAL_SYSPM_CHECK_FAIL:
        case CYHAL_SYSPM_AFTER_TRANSITION:
            obj->pm_transition_ready = false;
            return true;
        default:
            return true;
    }
}

#if defined(_CYHAL_AUDIOSS_TRIGGERS_AVAILABLE)
static cyhal_source_t _cyhal_audioss_calculate_source(_cyhal_audioss_t *obj, bool is_rx)
{
#if defined(_CYHAL_AUDIOSS_RX_ENABLED)
    return is_rx ? _cyhal_audioss_rx_trigger[obj->resource.block_num] : _cyhal_audioss_tx_trigger[obj->resource.block_num];
#else
    CY_UNUSED_PARAMETER(is_rx);
    return _cyhal_audioss_tx_trigger[obj->resource.block_num];
#endif /* defined(_CYHAL_AUDIOSS_RX_ENABLED) */
}
#endif

cy_rslt_t _cyhal_audioss_enable_output(_cyhal_audioss_t *obj, bool is_rx, cyhal_source_t *source)
{
#if defined(_CYHAL_AUDIOSS_TRIGGERS_AVAILABLE)
    #if defined(CY_IP_MXAUDIOSS) /* On MXTDM the trigger lines are always enabled */
    if(is_rx)
    {
        REG_I2S_TR_CTL(obj->base) |= I2S_TR_CTL_RX_REQ_EN_Msk;
    }
    else
    {
        REG_I2S_TR_CTL(obj->base) |= I2S_TR_CTL_TX_REQ_EN_Msk;
    }
    #endif /* defined(CY_IP_MXAUDIOSS) */

    *source = _cyhal_audioss_calculate_source(obj, is_rx);
    return CY_RSLT_SUCCESS;
#else
    CY_UNUSED_PARAMETER(is_rx);
    CY_UNUSED_PARAMETER(source);
    return obj->interface->err_not_supported;
#endif /* defined(_CYHAL_AUDIOSS_TRIGGERS_AVAILABLE) */
}

cy_rslt_t _cyhal_audioss_disable_output(_cyhal_audioss_t *obj, bool is_rx)
{
#if defined(_CYHAL_AUDIOSS_TRIGGERS_AVAILABLE)
    #if defined(CY_IP_MXAUDIOSS)
    if(is_rx)
    {
        REG_I2S_TR_CTL(obj->base) &= ~I2S_TR_CTL_RX_REQ_EN_Msk;
    }
    else
    {
        REG_I2S_TR_CTL(obj->base) &= ~I2S_TR_CTL_TX_REQ_EN_Msk;
    }
    #else
    /* On MXTDM the trigger lines are always enabled */
    CY_UNUSED_PARAMETER(obj);
    CY_UNUSED_PARAMETER(is_rx);
    #endif /* defined(CY_IP_MXAUDIOSS) */

    return CY_RSLT_SUCCESS;
#else
    CY_UNUSED_PARAMETER(is_rx);
    return obj->interface->err_not_supported;
#endif /* defined(_CYHAL_AUDIOSS_TRIGGERS_AVAILABLE) */
}


#if defined(__cplusplus)
}
#endif

#endif /* CYHAL_DRIVER_AVAILABLE_I2S */
