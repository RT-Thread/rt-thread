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
#if NRF_MODULE_ENABLED(PDM)
#include "nrf_drv_pdm.h"
#include "nrf_assert.h"
#include "nrf_drv_common.h"
#include "nrf_gpio.h"

#define NRF_LOG_MODULE_NAME "PDM"

#if PDM_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       PDM_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  PDM_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR PDM_CONFIG_DEBUG_COLOR
#define EVT_TO_STR(event)   (event == NRF_PDM_EVENT_STARTED ? "NRF_PDM_EVENT_STARTED" :                \
                            (event == NRF_PDM_EVENT_STOPPED ? "NRF_COMP_EVENT_DOWN" :                  \
                            (event == NRF_PDM_EVENT_END ? "NRF_COMP_EVENT_CROSS" : "UNKNOWN EVENT")))
#else //PDM_CONFIG_LOG_ENABLED
#define EVT_TO_STR(event)   ""
#define NRF_LOG_LEVEL       0
#endif //PDM_CONFIG_LOG_ENABLED
#include "nrf_log.h"
#include "nrf_log_ctrl.h"


/** @brief PDM interface status. */
typedef enum
{
    NRF_PDM_STATE_IDLE,
    NRF_PDM_STATE_RUNNING,
    NRF_PDM_STATE_TRANSITION
} nrf_drv_pdm_state_t;


/** @brief PDM interface control block.*/
typedef struct
{
    nrf_drv_state_t             drv_state;        ///< Driver state.
    nrf_drv_pdm_state_t         status;           ///< Sampling state.
    nrf_drv_pdm_event_handler_t event_handler;    ///< Event handler function pointer.
    uint16_t                    buffer_length;    ///< Length of a single buffer in 16-bit words.
    uint32_t *                  buffers[2];       ///< Sample buffers.
} nrf_drv_pdm_cb_t;

static nrf_drv_pdm_cb_t m_cb;


void PDM_IRQHandler(void)
{
    if (nrf_pdm_event_check(NRF_PDM_EVENT_END))
    {
        nrf_pdm_event_clear(NRF_PDM_EVENT_END);
        NRF_LOG_DEBUG("Event: %s.\r\n", (uint32_t)EVT_TO_STR(NRF_PDM_EVENT_END));

        //Buffer is ready to process.
        if (nrf_pdm_buffer_get() == m_cb.buffers[0])
        {
            NRF_LOG_DEBUG("PDM data:\r\n");
            NRF_LOG_HEXDUMP_DEBUG((uint8_t *)m_cb.buffers[1], m_cb.buffer_length * sizeof(m_cb.buffers[1]));
            m_cb.event_handler(m_cb.buffers[1], m_cb.buffer_length);
        }
        else
        {
            NRF_LOG_DEBUG("PDM data:\r\n");
            NRF_LOG_HEXDUMP_DEBUG((uint8_t *)m_cb.buffers[0], m_cb.buffer_length * sizeof(m_cb.buffers[0]));
            m_cb.event_handler(m_cb.buffers[0], m_cb.buffer_length);
        }
    }
    else if (nrf_pdm_event_check(NRF_PDM_EVENT_STARTED))
    {
        nrf_pdm_event_clear(NRF_PDM_EVENT_STARTED);
        NRF_LOG_DEBUG("Event: %s.\r\n", (uint32_t)EVT_TO_STR(NRF_PDM_EVENT_STARTED));
        m_cb.status = NRF_PDM_STATE_RUNNING;

        //Swap buffer.
        if (nrf_pdm_buffer_get() == m_cb.buffers[0])
        {
            nrf_pdm_buffer_set(m_cb.buffers[1],m_cb.buffer_length);
        }
        else
        {
            nrf_pdm_buffer_set(m_cb.buffers[0],m_cb.buffer_length);
        }
    }
    else if (nrf_pdm_event_check(NRF_PDM_EVENT_STOPPED))
    {
        nrf_pdm_event_clear(NRF_PDM_EVENT_STOPPED);
        NRF_LOG_DEBUG("Event: %s.\r\n", (uint32_t)EVT_TO_STR(NRF_PDM_EVENT_STOPPED));
        nrf_pdm_disable();
        m_cb.status = NRF_PDM_STATE_IDLE;
    }
}


ret_code_t nrf_drv_pdm_init(nrf_drv_pdm_config_t const * p_config,
                              nrf_drv_pdm_event_handler_t event_handler)
{
    ret_code_t err_code;

    if (m_cb.drv_state != NRF_DRV_STATE_UNINITIALIZED)
    {
        err_code = NRF_ERROR_INVALID_STATE;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
    if ((p_config == NULL)
        || (event_handler == NULL))
    {
        err_code = NRF_ERROR_INVALID_PARAM;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
    if (p_config->gain_l > NRF_PDM_GAIN_MAXIMUM
        || p_config->gain_r > NRF_PDM_GAIN_MAXIMUM
        || p_config->buffer_length > NRF_PDM_MAX_BUFFER_SIZE)
    {
        err_code = NRF_ERROR_INVALID_PARAM;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    m_cb.buffers[0] = (uint32_t*)p_config->buffer_a;
    m_cb.buffers[1] = (uint32_t*)p_config->buffer_b;
    m_cb.buffer_length = p_config->buffer_length;
    m_cb.event_handler = event_handler;
    m_cb.status = NRF_PDM_STATE_IDLE;

    nrf_pdm_buffer_set(m_cb.buffers[0],m_cb.buffer_length);
    nrf_pdm_clock_set(p_config->clock_freq);
    nrf_pdm_mode_set(p_config->mode, p_config->edge);
    nrf_pdm_gain_set(p_config->gain_l, p_config->gain_r);

    nrf_gpio_cfg_output(p_config->pin_clk);
    nrf_gpio_pin_clear(p_config->pin_clk);
    nrf_gpio_cfg_input(p_config->pin_din, NRF_GPIO_PIN_NOPULL);
    nrf_pdm_psel_connect(p_config->pin_clk, p_config->pin_din);

    m_cb.drv_state = NRF_DRV_STATE_INITIALIZED;
    nrf_pdm_int_enable(NRF_PDM_INT_STARTED | NRF_PDM_INT_END | NRF_PDM_INT_STOPPED);
    nrf_drv_common_irq_enable(PDM_IRQn, p_config->interrupt_priority);

    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}


void nrf_drv_pdm_uninit(void)
{
    nrf_pdm_disable();
    nrf_pdm_psel_disconnect();
    m_cb.drv_state = NRF_DRV_STATE_UNINITIALIZED;
    NRF_LOG_INFO("Uninitialized.\r\n");
}


ret_code_t nrf_drv_pdm_start(void)
{
    ASSERT(m_cb.drv_state != NRF_DRV_STATE_UNINITIALIZED);
    ret_code_t err_code;

    if (m_cb.status != NRF_PDM_STATE_IDLE)
    {
        if (m_cb.status == NRF_PDM_STATE_RUNNING)
        {
            err_code = NRF_SUCCESS;
            NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
            return err_code;
        }
        err_code = NRF_ERROR_BUSY;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
    m_cb.status = NRF_PDM_STATE_TRANSITION;
    m_cb.drv_state = NRF_DRV_STATE_POWERED_ON;
    nrf_pdm_enable();
    nrf_pdm_event_clear(NRF_PDM_EVENT_STARTED);
    nrf_pdm_task_trigger(NRF_PDM_TASK_START);
    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}


ret_code_t nrf_drv_pdm_stop(void)
{
    ASSERT(m_cb.drv_state != NRF_DRV_STATE_UNINITIALIZED);
    ret_code_t err_code;

    if (m_cb.status != NRF_PDM_STATE_RUNNING)
    {
        if (m_cb.status == NRF_PDM_STATE_IDLE)
        {
            nrf_pdm_disable();
            err_code = NRF_SUCCESS;
            NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
            return err_code;
        }
        err_code = NRF_ERROR_BUSY;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
    m_cb.status = NRF_PDM_STATE_TRANSITION;
    m_cb.drv_state = NRF_DRV_STATE_INITIALIZED;
    nrf_pdm_task_trigger(NRF_PDM_TASK_STOP);
    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}
#endif //NRF_MODULE_ENABLED(PDM)
