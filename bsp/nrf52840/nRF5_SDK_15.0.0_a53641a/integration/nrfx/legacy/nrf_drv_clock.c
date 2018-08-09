/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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

#include <nordic_common.h>
#include "nrf_drv_clock.h"

#if NRF_MODULE_ENABLED(CLOCK)

#ifdef SOFTDEVICE_PRESENT
#include "nrf_sdh.h"
#include "nrf_sdh_soc.h"
#endif

#define NRF_LOG_MODULE_NAME clock
#if CLOCK_CONFIG_LOG_ENABLED
    #define NRF_LOG_LEVEL       CLOCK_CONFIG_LOG_LEVEL
    #define NRF_LOG_INFO_COLOR  CLOCK_CONFIG_INFO_COLOR
    #define NRF_LOG_DEBUG_COLOR CLOCK_CONFIG_DEBUG_COLOR
#else //CLOCK_CONFIG_LOG_ENABLED
    #define NRF_LOG_LEVEL       0
#endif //CLOCK_CONFIG_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define EVT_TO_STR(event)                                                     \
    (event == NRF_CLOCK_EVENT_HFCLKSTARTED ? "NRF_CLOCK_EVENT_HFCLKSTARTED" : \
    (event == NRF_CLOCK_EVENT_LFCLKSTARTED ? "NRF_CLOCK_EVENT_LFCLKSTARTED" : \
    (event == NRF_CLOCK_EVENT_DONE         ? "NRF_CLOCK_EVENT_DONE"         : \
    (event == NRF_CLOCK_EVENT_CTTO         ? "NRF_CLOCK_EVENT_CTTO"         : \
                                             "UNKNOWN EVENT"))))


/*lint -save -e652 */
#define NRF_CLOCK_LFCLK_RC    CLOCK_LFCLKSRC_SRC_RC
#define NRF_CLOCK_LFCLK_Xtal  CLOCK_LFCLKSRC_SRC_Xtal
#define NRF_CLOCK_LFCLK_Synth CLOCK_LFCLKSRC_SRC_Synth
/*lint -restore */

#if (CLOCK_CONFIG_LF_SRC == NRF_CLOCK_LFCLK_RC) && !defined(SOFTDEVICE_PRESENT)
#define CALIBRATION_SUPPORT 1
#else
#define CALIBRATION_SUPPORT 0
#endif
typedef enum
{
    CAL_STATE_IDLE,
    CAL_STATE_CT,
    CAL_STATE_HFCLK_REQ,
    CAL_STATE_CAL,
    CAL_STATE_ABORT,
} nrf_drv_clock_cal_state_t;

/**@brief CLOCK control block. */
typedef struct
{
    bool                                    module_initialized; /*< Indicate the state of module */
    volatile bool                           hfclk_on;           /*< High-frequency clock state. */
    volatile bool                           lfclk_on;           /*< Low-frequency clock state. */
    volatile uint32_t                       hfclk_requests;     /*< High-frequency clock request counter. */
    volatile nrf_drv_clock_handler_item_t * p_hf_head;
    volatile uint32_t                       lfclk_requests;     /*< Low-frequency clock request counter. */
    volatile nrf_drv_clock_handler_item_t * p_lf_head;
#if CALIBRATION_SUPPORT
    nrf_drv_clock_handler_item_t            cal_hfclk_started_handler_item;
    nrf_drv_clock_event_handler_t           cal_done_handler;
    volatile nrf_drv_clock_cal_state_t      cal_state;
#endif // CALIBRATION_SUPPORT
} nrf_drv_clock_cb_t;

static nrf_drv_clock_cb_t m_clock_cb;

static void clock_irq_handler(nrfx_clock_evt_type_t evt);

static void lfclk_stop(void)
{
#if CALIBRATION_SUPPORT
    nrfx_clock_calibration_timer_stop();
#endif

#ifdef SOFTDEVICE_PRESENT
    // If LFCLK is requested to stop while SD is still enabled,
    // it indicates an error in the application.
    // Enabling SD should increment the LFCLK request.
    ASSERT(!nrf_sdh_is_enabled());
#endif // SOFTDEVICE_PRESENT

    nrfx_clock_lfclk_stop();
    m_clock_cb.lfclk_on = false;
}

static void hfclk_start(void)
{
#ifdef SOFTDEVICE_PRESENT
    if (nrf_sdh_is_enabled())
    {
        (void)sd_clock_hfclk_request();
        return;
    }
#endif // SOFTDEVICE_PRESENT

    nrfx_clock_hfclk_start();
}

static void hfclk_stop(void)
{
#ifdef SOFTDEVICE_PRESENT
    if (nrf_sdh_is_enabled())
    {
        (void)sd_clock_hfclk_release();
        m_clock_cb.hfclk_on = false;
        return;
    }
#endif // SOFTDEVICE_PRESENT

    nrfx_clock_hfclk_stop();
    m_clock_cb.hfclk_on = false;
}

bool nrf_drv_clock_init_check(void)
{
    return m_clock_cb.module_initialized;
}

ret_code_t nrf_drv_clock_init(void)
{
    ret_code_t err_code = NRF_SUCCESS;
    if (m_clock_cb.module_initialized)
    {
        err_code = NRF_ERROR_MODULE_ALREADY_INITIALIZED;
    }
    else
    {
        m_clock_cb.p_hf_head      = NULL;
        m_clock_cb.hfclk_requests = 0;
        m_clock_cb.p_lf_head      = NULL;
        m_clock_cb.lfclk_requests = 0;
        err_code = nrfx_clock_init(clock_irq_handler);
#ifdef SOFTDEVICE_PRESENT
        if (!nrf_sdh_is_enabled())
#endif
        {
            nrfx_clock_enable();
        }

#if CALIBRATION_SUPPORT
        m_clock_cb.cal_state = CAL_STATE_IDLE;
#endif

        m_clock_cb.module_initialized = true;
    }

    NRF_LOG_INFO("Function: %s, error code: %s.",
                 (uint32_t)__func__,
                 (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}

void nrf_drv_clock_uninit(void)
{
    ASSERT(m_clock_cb.module_initialized);
    nrfx_clock_disable();
    nrfx_clock_uninit();
}

static void item_enqueue(nrf_drv_clock_handler_item_t ** p_head,
                         nrf_drv_clock_handler_item_t *  p_item)
{
    nrf_drv_clock_handler_item_t * p_next = *p_head;
    while (p_next)
    {
        if (p_next == p_item)
        {
            return;
        }
        p_next = p_next->p_next;
    }

    p_item->p_next = (*p_head ? *p_head : NULL);
    *p_head = p_item;
}

static nrf_drv_clock_handler_item_t * item_dequeue(nrf_drv_clock_handler_item_t ** p_head)
{
    nrf_drv_clock_handler_item_t * p_item = *p_head;
    if (p_item)
    {
        *p_head = p_item->p_next;
    }
    return p_item;
}

void nrf_drv_clock_lfclk_request(nrf_drv_clock_handler_item_t * p_handler_item)
{
    ASSERT(m_clock_cb.module_initialized);

    if (m_clock_cb.lfclk_on)
    {
        if (p_handler_item)
        {
            p_handler_item->event_handler(NRF_DRV_CLOCK_EVT_LFCLK_STARTED);
        }
        CRITICAL_REGION_ENTER();
        ++(m_clock_cb.lfclk_requests);
        CRITICAL_REGION_EXIT();
    }
    else
    {
        CRITICAL_REGION_ENTER();
        if (p_handler_item)
        {
            item_enqueue((nrf_drv_clock_handler_item_t **)&m_clock_cb.p_lf_head,
                p_handler_item);
        }
        if (m_clock_cb.lfclk_requests == 0)
        {
            nrfx_clock_lfclk_start();
        }
        ++(m_clock_cb.lfclk_requests);
        CRITICAL_REGION_EXIT();
    }

    ASSERT(m_clock_cb.lfclk_requests > 0);
}

void nrf_drv_clock_lfclk_release(void)
{
    ASSERT(m_clock_cb.module_initialized);
    ASSERT(m_clock_cb.lfclk_requests > 0);

    CRITICAL_REGION_ENTER();
    --(m_clock_cb.lfclk_requests);
    if (m_clock_cb.lfclk_requests == 0)
    {
        lfclk_stop();
    }
    CRITICAL_REGION_EXIT();
}

bool nrf_drv_clock_lfclk_is_running(void)
{
    ASSERT(m_clock_cb.module_initialized);

#ifdef SOFTDEVICE_PRESENT
    if (nrf_sdh_is_enabled())
    {
        return true;
    }
#endif // SOFTDEVICE_PRESENT

    return nrfx_clock_lfclk_is_running();
}

void nrf_drv_clock_hfclk_request(nrf_drv_clock_handler_item_t * p_handler_item)
{
    ASSERT(m_clock_cb.module_initialized);

    if (m_clock_cb.hfclk_on)
    {
        if (p_handler_item)
        {
            p_handler_item->event_handler(NRF_DRV_CLOCK_EVT_HFCLK_STARTED);
        }
        CRITICAL_REGION_ENTER();
        ++(m_clock_cb.hfclk_requests);
        CRITICAL_REGION_EXIT();
    }
    else
    {
        CRITICAL_REGION_ENTER();
        if (p_handler_item)
        {
            item_enqueue((nrf_drv_clock_handler_item_t **)&m_clock_cb.p_hf_head,
                p_handler_item);
        }
        if (m_clock_cb.hfclk_requests == 0)
        {
            hfclk_start();
        }
        ++(m_clock_cb.hfclk_requests);
        CRITICAL_REGION_EXIT();
    }

    ASSERT(m_clock_cb.hfclk_requests > 0);
}

void nrf_drv_clock_hfclk_release(void)
{
    ASSERT(m_clock_cb.module_initialized);
    ASSERT(m_clock_cb.hfclk_requests > 0);

    CRITICAL_REGION_ENTER();
    --(m_clock_cb.hfclk_requests);
    if (m_clock_cb.hfclk_requests == 0)
    {
        hfclk_stop();
    }
    CRITICAL_REGION_EXIT();
}

bool nrf_drv_clock_hfclk_is_running(void)
{
    ASSERT(m_clock_cb.module_initialized);

#ifdef SOFTDEVICE_PRESENT
    if (nrf_sdh_is_enabled())
    {
        uint32_t is_running;
        UNUSED_VARIABLE(sd_clock_hfclk_is_running(&is_running));
        return (is_running ? true : false);
    }
#endif // SOFTDEVICE_PRESENT

    return nrfx_clock_hfclk_is_running();
}

#if CALIBRATION_SUPPORT
static void clock_calibration_hf_started(nrf_drv_clock_evt_type_t event)
{
    if (m_clock_cb.cal_state == CAL_STATE_ABORT)
    {
        nrf_drv_clock_hfclk_release();
        m_clock_cb.cal_state = CAL_STATE_IDLE;
        if (m_clock_cb.cal_done_handler)
        {
            m_clock_cb.cal_done_handler(NRF_DRV_CLOCK_EVT_CAL_ABORTED);
        }
    }
    else
    {
        ASSERT(event == NRF_DRV_CLOCK_EVT_HFCLK_STARTED);
        if (nrfx_clock_calibration_start() != NRFX_SUCCESS)
        {
            ASSERT(false);
        }
    }
}
#endif // CALIBRATION_SUPPORT

ret_code_t nrf_drv_clock_calibration_start(uint8_t interval, nrf_drv_clock_event_handler_t handler)
{
    ret_code_t err_code = NRF_SUCCESS;
#if CALIBRATION_SUPPORT
    ASSERT(m_clock_cb.cal_state == CAL_STATE_IDLE);
    if (m_clock_cb.lfclk_on == false)
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }
    else if (m_clock_cb.cal_state == CAL_STATE_IDLE)
    {
        m_clock_cb.cal_done_handler = handler;
        m_clock_cb.cal_hfclk_started_handler_item.event_handler = clock_calibration_hf_started;
        if (interval == 0)
        {
            m_clock_cb.cal_state = CAL_STATE_HFCLK_REQ;
            nrf_drv_clock_hfclk_request(&m_clock_cb.cal_hfclk_started_handler_item);
        }
        else
        {
            m_clock_cb.cal_state = CAL_STATE_CT;
            nrfx_clock_calibration_timer_start(interval);
        }
    }
    else
    {
        err_code = NRF_ERROR_BUSY;
    }
    NRF_LOG_WARNING("Function: %s, error code: %s.",
                    (uint32_t)__func__,
                    (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
#else
    UNUSED_PARAMETER(interval);
    UNUSED_PARAMETER(handler);
    err_code = NRF_ERROR_FORBIDDEN;
    NRF_LOG_WARNING("Function: %s, error code: %s.",
                    (uint32_t)__func__,
                    (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
#endif // CALIBRATION_SUPPORT
}

ret_code_t nrf_drv_clock_calibration_abort(void)
{
    ret_code_t err_code = NRF_SUCCESS;
#if CALIBRATION_SUPPORT
    CRITICAL_REGION_ENTER();
    switch (m_clock_cb.cal_state)
    {
    case CAL_STATE_CT:
        nrfx_clock_calibration_timer_stop();
        m_clock_cb.cal_state = CAL_STATE_IDLE;
        if (m_clock_cb.cal_done_handler)
        {
            m_clock_cb.cal_done_handler(NRF_DRV_CLOCK_EVT_CAL_ABORTED);
        }
        break;
    case CAL_STATE_HFCLK_REQ:
        /* fall through. */
    case CAL_STATE_CAL:
        m_clock_cb.cal_state = CAL_STATE_ABORT;
        break;
    default:
        break;
    }
    CRITICAL_REGION_EXIT();

    NRF_LOG_INFO("Function: %s, error code: %s.",
                  (uint32_t)__func__,
                  (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
#else
    err_code = NRF_ERROR_FORBIDDEN;
    NRF_LOG_WARNING("Function: %s, error code: %s.",
                    (uint32_t)__func__,
                    (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
#endif // CALIBRATION_SUPPORT
}

ret_code_t nrf_drv_clock_is_calibrating(bool * p_is_calibrating)
{
    ret_code_t err_code = NRF_SUCCESS;
#if CALIBRATION_SUPPORT
    ASSERT(m_clock_cb.module_initialized);
    *p_is_calibrating = (m_clock_cb.cal_state != CAL_STATE_IDLE);
    NRF_LOG_INFO("Function: %s, error code: %s.",
                  (uint32_t)__func__,
                  (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
#else
    UNUSED_PARAMETER(p_is_calibrating);
    err_code = NRF_ERROR_FORBIDDEN;
    NRF_LOG_WARNING("Function: %s, error code: %s.",
                    (uint32_t)__func__,
                    (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
#endif // CALIBRATION_SUPPORT
}

__STATIC_INLINE void clock_clk_started_notify(nrf_drv_clock_evt_type_t evt_type)
{
    nrf_drv_clock_handler_item_t **p_head;
    if (evt_type == NRF_DRV_CLOCK_EVT_HFCLK_STARTED)
    {
        p_head = (nrf_drv_clock_handler_item_t **)&m_clock_cb.p_hf_head;
    }
    else
    {
        p_head = (nrf_drv_clock_handler_item_t **)&m_clock_cb.p_lf_head;
    }

    while (1)
    {
        nrf_drv_clock_handler_item_t * p_item = item_dequeue(p_head);
        if (!p_item)
        {
            break;
        }

        p_item->event_handler(evt_type);
    }
}

static void clock_irq_handler(nrfx_clock_evt_type_t evt)
{
    if (evt == NRFX_CLOCK_EVT_HFCLK_STARTED)
    {
        m_clock_cb.hfclk_on = true;
        clock_clk_started_notify(NRF_DRV_CLOCK_EVT_HFCLK_STARTED);
    }
    if (evt == NRFX_CLOCK_EVT_LFCLK_STARTED)
    {
        m_clock_cb.lfclk_on = true;
        clock_clk_started_notify(NRF_DRV_CLOCK_EVT_LFCLK_STARTED);
    }
#if CALIBRATION_SUPPORT
    if (evt == NRFX_CLOCK_EVT_CTTO)
    {
        nrf_drv_clock_hfclk_request(&m_clock_cb.cal_hfclk_started_handler_item);
    }

    if (evt == NRFX_CLOCK_EVT_CAL_DONE)
    {
        nrf_drv_clock_hfclk_release();
        bool aborted = (m_clock_cb.cal_state == CAL_STATE_ABORT);
        m_clock_cb.cal_state = CAL_STATE_IDLE;
        if (m_clock_cb.cal_done_handler)
        {
            m_clock_cb.cal_done_handler(aborted ?
                NRF_DRV_CLOCK_EVT_CAL_ABORTED : NRF_DRV_CLOCK_EVT_CAL_DONE);
        }
    }
#endif // CALIBRATION_SUPPORT
}

#ifdef SOFTDEVICE_PRESENT
/**
 * @brief SoftDevice SoC event handler.
 *
 * @param[in] evt_id    SoC event.
 * @param[in] p_context Context.
 */
static void soc_evt_handler(uint32_t evt_id, void * p_context)
{
    if (evt_id == NRF_EVT_HFCLKSTARTED)
    {
        m_clock_cb.hfclk_on = true;
        clock_clk_started_notify(NRF_DRV_CLOCK_EVT_HFCLK_STARTED);
    }
}
NRF_SDH_SOC_OBSERVER(m_soc_evt_observer, CLOCK_CONFIG_SOC_OBSERVER_PRIO, soc_evt_handler, NULL);

/**
 * @brief SoftDevice enable/disable state handler.
 *
 * @param[in] state     State.
 * @param[in] p_context Context.
 */
static void sd_state_evt_handler(nrf_sdh_state_evt_t state, void * p_context)
{
    switch (state)
    {
        case NRF_SDH_EVT_STATE_ENABLE_PREPARE:
            NVIC_DisableIRQ(POWER_CLOCK_IRQn);
            break;

        case NRF_SDH_EVT_STATE_ENABLED:
            CRITICAL_REGION_ENTER();
            /* Make sure that nrf_drv_clock module is initialized */
            if (!m_clock_cb.module_initialized)
            {
                (void)nrf_drv_clock_init();
            }
            /* SD is one of the LFCLK requesters, but it will enable it by itself. */
            ++(m_clock_cb.lfclk_requests);
            m_clock_cb.lfclk_on = true;
            CRITICAL_REGION_EXIT();
            break;

        case NRF_SDH_EVT_STATE_DISABLED:
            /* Reinit interrupts */
            ASSERT(m_clock_cb.module_initialized);
            nrfx_clock_enable();

            /* SD leaves LFCLK enabled - disable it if it is no longer required. */
            nrf_drv_clock_lfclk_release();
            break;

        default:
            break;
    }
}

NRF_SDH_STATE_OBSERVER(m_sd_state_observer, CLOCK_CONFIG_STATE_OBSERVER_PRIO) =
{
    .handler   = sd_state_evt_handler,
    .p_context = NULL,
};

#endif // SOFTDEVICE_PRESENT

#undef NRF_CLOCK_LFCLK_RC
#undef NRF_CLOCK_LFCLK_Xtal
#undef NRF_CLOCK_LFCLK_Synth

#endif // NRF_MODULE_ENABLED(CLOCK)
