/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(QDEC)
#include <stdint.h>
#include <stddef.h>

#include "nrf.h"
#include "nrf_gpio.h"
#include "nrf_error.h"
#include "nrf_assert.h"
#include "nrf_drv_common.h"
#include "nrf_drv_qdec.h"
#include "app_util_platform.h"
#include "nrf_assert.h"

#define NRF_LOG_MODULE_NAME "QDEC"

#if QDEC_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       QDEC_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  QDEC_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR QDEC_CONFIG_DEBUG_COLOR
#define EVT_TO_STR(event)   (event == NRF_QDEC_EVENT_SAMPLERDY ? "NRF_QDEC_EVENT_SAMPLERDY" :        \
                            (event == NRF_QDEC_EVENT_REPORTRDY ? "NRF_QDEC_EVENT_REPORTRDY" :        \
                            (event == NRF_QDEC_EVENT_ACCOF ? "NRF_QDEC_EVENT_ACCOF" : "UNKNOWN EVENT")))
#else //QDEC_CONFIG_LOG_ENABLED
#define EVT_TO_STR(event)   ""
#define NRF_LOG_LEVEL       0
#endif //QDEC_CONFIG_LOG_ENABLED
#include "nrf_log.h"
#include "nrf_log_ctrl.h"


static qdec_event_handler_t m_qdec_event_handler = NULL;
static const nrf_drv_qdec_config_t m_default_config = NRF_DRV_QDEC_DEFAULT_CONFIG;
static nrf_drv_state_t m_state = NRF_DRV_STATE_UNINITIALIZED;

void QDEC_IRQHandler(void)
{
    nrf_drv_qdec_event_t event;
    if ( nrf_qdec_event_check(NRF_QDEC_EVENT_SAMPLERDY) &&
         nrf_qdec_int_enable_check(NRF_QDEC_INT_SAMPLERDY_MASK) )
    {
        nrf_qdec_event_clear(NRF_QDEC_EVENT_SAMPLERDY);
        NRF_LOG_DEBUG("Event: %s.\r\n", (uint32_t)EVT_TO_STR(NRF_QDEC_EVENT_SAMPLERDY));

        event.type = NRF_QDEC_EVENT_SAMPLERDY;
        event.data.sample.value = (int8_t)nrf_qdec_sample_get();
        m_qdec_event_handler(event);
    }

    if ( nrf_qdec_event_check(NRF_QDEC_EVENT_REPORTRDY) &&
         nrf_qdec_int_enable_check(NRF_QDEC_INT_REPORTRDY_MASK) )
    {
        nrf_qdec_event_clear(NRF_QDEC_EVENT_REPORTRDY);
        NRF_LOG_DEBUG("Event: %s.\r\n", (uint32_t)EVT_TO_STR(NRF_QDEC_INT_REPORTRDY_MASK));

        event.type = NRF_QDEC_EVENT_REPORTRDY;

        event.data.report.acc    = (int16_t)nrf_qdec_accread_get();
        event.data.report.accdbl = (uint16_t)nrf_qdec_accdblread_get();
        m_qdec_event_handler(event);
    }

    if ( nrf_qdec_event_check(NRF_QDEC_EVENT_ACCOF) &&
         nrf_qdec_int_enable_check(NRF_QDEC_INT_ACCOF_MASK) )
    {
        nrf_qdec_event_clear(NRF_QDEC_EVENT_ACCOF);
        NRF_LOG_DEBUG("Event: %s.\r\n", (uint32_t)EVT_TO_STR(NRF_QDEC_EVENT_ACCOF));

        event.type = NRF_QDEC_EVENT_ACCOF;
        m_qdec_event_handler(event);
    }
}


ret_code_t nrf_drv_qdec_init(const nrf_drv_qdec_config_t * p_config,
                             qdec_event_handler_t event_handler)
{
    ret_code_t err_code;

    if (m_state != NRF_DRV_STATE_UNINITIALIZED)
    {
        err_code = NRF_ERROR_INVALID_STATE;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    if (p_config == NULL)
    {
        p_config = &m_default_config;
    }

    if (event_handler)
    {
        m_qdec_event_handler = event_handler;
    }
    else
    {
        err_code = NRF_ERROR_INVALID_PARAM;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    nrf_qdec_sampleper_set(p_config->sampleper);
    nrf_gpio_cfg_input(p_config->pselled, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(p_config->psela, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(p_config->pselb, NRF_GPIO_PIN_NOPULL);
    nrf_qdec_pio_assign( p_config->psela, p_config->pselb, p_config->pselled);
    nrf_qdec_ledpre_set(p_config->ledpre);
    nrf_qdec_ledpol_set(p_config->ledpol);
    nrf_qdec_shorts_enable(NRF_QDEC_SHORT_REPORTRDY_READCLRACC_MASK);

    if (p_config->dbfen)
    {
        nrf_qdec_dbfen_enable();
    }
    else
    {
        nrf_qdec_dbfen_disable();
    }

    uint32_t int_mask = NRF_QDEC_INT_ACCOF_MASK;

    if (p_config->reportper != NRF_QDEC_REPORTPER_DISABLED)
    {
        nrf_qdec_reportper_set(p_config->reportper);
        int_mask |= NRF_QDEC_INT_REPORTRDY_MASK;
    }

    if (p_config->sample_inten)
    {
        int_mask |= NRF_QDEC_INT_SAMPLERDY_MASK;
    }

    nrf_qdec_int_enable(int_mask);
    nrf_drv_common_irq_enable(QDEC_IRQn, p_config->interrupt_priority);

    m_state = NRF_DRV_STATE_INITIALIZED;

    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}

void nrf_drv_qdec_uninit(void)
{
    ASSERT(m_state != NRF_DRV_STATE_UNINITIALIZED);
    nrf_drv_qdec_disable();
    nrf_drv_common_irq_disable(QDEC_IRQn);
    m_state = NRF_DRV_STATE_UNINITIALIZED;
    NRF_LOG_INFO("Uninitialized.\r\n");
}

void nrf_drv_qdec_enable(void)
{
    ASSERT(m_state == NRF_DRV_STATE_INITIALIZED);
    nrf_qdec_enable();
    nrf_qdec_task_trigger(NRF_QDEC_TASK_START);
    m_state = NRF_DRV_STATE_POWERED_ON;
    NRF_LOG_INFO("Enabled.\r\n");
}

void nrf_drv_qdec_disable(void)
{
    ASSERT(m_state == NRF_DRV_STATE_POWERED_ON);
    nrf_qdec_task_trigger(NRF_QDEC_TASK_STOP);
    nrf_qdec_disable();
    m_state = NRF_DRV_STATE_INITIALIZED;
    NRF_LOG_INFO("Disabled.\r\n");
}

void nrf_drv_qdec_accumulators_read(int16_t * p_acc, int16_t * p_accdbl)
{
    ASSERT(m_state == NRF_DRV_STATE_POWERED_ON);
    nrf_qdec_task_trigger(NRF_QDEC_TASK_READCLRACC);

    *p_acc    = (int16_t)nrf_qdec_accread_get();
    *p_accdbl = (int16_t)nrf_qdec_accdblread_get();

    NRF_LOG_DEBUG("Accumulators data, ACC register:\r\n");
    NRF_LOG_HEXDUMP_DEBUG((uint8_t *)p_acc, sizeof(p_acc));
    NRF_LOG_DEBUG("Accumulators data, ACCDBL register:\r\n");
    NRF_LOG_HEXDUMP_DEBUG((uint8_t *)p_accdbl, sizeof(p_accdbl));
}

void nrf_drv_qdec_task_address_get(nrf_qdec_task_t task, uint32_t * p_task)
{
    *p_task = (uint32_t)nrf_qdec_task_address_get(task);
}

void nrf_drv_qdec_event_address_get(nrf_qdec_event_t event, uint32_t * p_event)
{
    *p_event = (uint32_t)nrf_qdec_event_address_get(event);
}

#endif //NRF_MODULE_ENABLED(QDEC)
