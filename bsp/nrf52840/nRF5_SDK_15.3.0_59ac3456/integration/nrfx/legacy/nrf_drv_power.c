/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(POWER)
#include "nrf_drv_power.h"
#include <nrf_drv_clock.h>
#ifdef SOFTDEVICE_PRESENT
#include "nrf_sdh.h"
#include "nrf_sdh_soc.h"
#endif

#include <app_util.h>

// The structure with default configuration data.
static const nrfx_power_config_t m_drv_power_config_default =
{
    .dcdcen = NRFX_POWER_CONFIG_DEFAULT_DCDCEN,
#if NRF_POWER_HAS_VDDH
    .dcdcenhv = NRFX_POWER_CONFIG_DEFAULT_DCDCENHV,
#endif
};

static bool m_initialized;

bool nrf_drv_power_init_check(void)
{
    return m_initialized;
}

ret_code_t nrf_drv_power_init(nrf_drv_power_config_t const * p_config)
{
    if (m_initialized)
    {
        return NRF_ERROR_MODULE_ALREADY_INITIALIZED;
    }

#ifdef SOFTDEVICE_PRESENT
    if (nrf_sdh_is_enabled())
    {
        return NRF_ERROR_INVALID_STATE;
    }
#endif
    if (p_config == NULL)
    {
        p_config = &m_drv_power_config_default;
    }

    ret_code_t err_code = nrfx_power_init(p_config);
    if (err_code == NRFX_SUCCESS)
    {
        m_initialized = true;
    }
    return err_code;
}

void nrf_drv_power_uninit()
{
    nrfx_power_uninit();
    nrf_drv_power_pof_uninit();
#if NRF_POWER_HAS_SLEEPEVT
    nrf_drv_power_sleepevt_uninit();
#endif
#if NRF_POWER_HAS_USBREG
    nrf_drv_power_usbevt_uninit();
#endif
    m_initialized = false;
}

ret_code_t nrf_drv_power_pof_init(nrf_drv_power_pofwarn_config_t const * p_config)
{
    ret_code_t err_code = NRF_SUCCESS;
    nrfx_power_pof_init(p_config);
#ifdef SOFTDEVICE_PRESENT
    if (nrf_sdh_is_enabled())
    {
        /* Currently when SD is enabled - the configuration can be changed
         * in very limited range.
         * It is the SoftDevice limitation.
         */
#if NRF_POWER_HAS_VDDH
        if (p_config->thrvddh != nrf_power_pofcon_vddh_get())
        {
            /* Cannot change THRVDDH with current SD API */
            return NRF_ERROR_INVALID_STATE;
        }
#endif
        if (p_config->thr != nrf_power_pofcon_get(NULL))
        {
            /* Only limited number of THR values are supported and
             * the values taken by SD is different than the one in hardware
             */
            uint8_t thr;
            switch(p_config->thr)
            {
                case NRF_POWER_POFTHR_V21:
                    thr = NRF_POWER_THRESHOLD_V21;
                    break;
                case NRF_POWER_POFTHR_V23:
                    thr = NRF_POWER_THRESHOLD_V23;
                    break;
                case NRF_POWER_POFTHR_V25:
                    thr = NRF_POWER_THRESHOLD_V25;
                    break;
                case NRF_POWER_POFTHR_V27:
                    thr = NRF_POWER_THRESHOLD_V27;
                    break;
                default:
                    /* Cannot configure */
                    nrfx_power_pof_uninit();
                    return NRF_ERROR_INVALID_STATE;
            }
            err_code = sd_power_pof_threshold_set(thr);
            if (err_code != NRF_SUCCESS)
            {
                return err_code;
            }
        }
        err_code = sd_power_pof_enable(true);
    }
    else
#endif /* SOFTDEVICE_PRESENT */
    {
        nrfx_power_pof_enable(p_config);
    }
    return err_code;
}

void nrf_drv_power_pof_uninit()
{
#ifdef SOFTDEVICE_PRESENT
    if (nrf_sdh_is_enabled())
    {
        ret_code_t err_code = sd_power_pof_enable(false);
        ASSERT(err_code == NRF_SUCCESS);
        UNUSED_VARIABLE(err_code); //handle no-debug case
    }
    else
#endif
    {
        nrfx_power_pof_disable();
    }
    nrfx_power_pof_uninit();
}

#if NRF_POWER_HAS_SLEEPEVT
ret_code_t nrf_drv_power_sleepevt_init(nrf_drv_power_sleepevt_config_t const * p_config)
{
    if (p_config->handler != NULL)
    {
#ifdef SOFTDEVICE_PRESENT
        if (nrf_sdh_is_enabled())
        {
            if ((p_config->en_enter) || (p_config->en_exit))
            {
                return NRF_ERROR_INVALID_STATE;
            }
        }
        else
#endif
        {
            nrfx_power_sleepevt_enable(p_config);
        }
    }
        return NRF_SUCCESS;
}

void nrf_drv_power_sleepevt_uninit(void)
{
#ifdef SOFTDEVICE_PRESENT
    if (nrf_sdh_is_enabled())
    {
        /* Nothing to do */
    }
    else
#endif
    {
        nrfx_power_sleepevt_disable();
    }
    nrfx_power_sleepevt_uninit();
}
#endif /* NRF_POWER_HAS_SLEEPEVT */

#if NRF_POWER_HAS_USBREG

#ifdef SOFTDEVICE_PRESENT
static ret_code_t nrf_drv_power_sd_usbevt_enable(bool enable)
{
    ret_code_t err_code;
    err_code = sd_power_usbdetected_enable(enable);
    ASSERT(err_code == NRF_SUCCESS);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = sd_power_usbpwrrdy_enable(enable);
    ASSERT(err_code == NRF_SUCCESS);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = sd_power_usbremoved_enable(enable);
    ASSERT(err_code == NRF_SUCCESS);
    return err_code;
}
#endif // SOFTDEVICE_PRESENT

ret_code_t nrf_drv_power_usbevt_init(nrf_drv_power_usbevt_config_t const * p_config)
{
    nrf_drv_power_usbevt_uninit();
    nrfx_power_usbevt_init(p_config);
#ifdef SOFTDEVICE_PRESENT
    if (nrf_sdh_is_enabled())
    {
        ret_code_t err_code = nrf_drv_power_sd_usbevt_enable(true);
        ASSERT(err_code == NRF_SUCCESS);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }

        uint32_t regstatus;
        err_code = sd_power_usbregstatus_get(&regstatus);
        ASSERT(err_code == NRF_SUCCESS);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }

        if (regstatus & POWER_USBREGSTATUS_VBUSDETECT_Msk)
        {
            nrfx_power_usb_event_handler_t usbevt_handler = nrfx_power_usb_handler_get();
            ASSERT(usbevt_handler != NULL);
            usbevt_handler(NRFX_POWER_USB_EVT_DETECTED);
        }
    }
    else
#endif
    {
        nrfx_power_usbevt_enable();
    }
    return NRF_SUCCESS;
}

void nrf_drv_power_usbevt_uninit(void)
{
#ifdef SOFTDEVICE_PRESENT
    CRITICAL_REGION_ENTER();
    if (nrf_sdh_is_enabled())
    {
        ret_code_t err_code = nrf_drv_power_sd_usbevt_enable(false);
        ASSERT(err_code == NRF_SUCCESS);
        UNUSED_VARIABLE(err_code);
    }
    else
#endif
    {
        nrfx_power_usbevt_disable();
    }
#ifdef SOFTDEVICE_PRESENT
    CRITICAL_REGION_EXIT();
#endif
    nrfx_power_usbevt_uninit();
}
#endif /* NRF_POWER_HAS_USBREG */

#ifdef SOFTDEVICE_PRESENT
static void nrf_drv_power_sdh_soc_evt_handler(uint32_t evt_id, void * p_context);
static void nrf_drv_power_sdh_state_evt_handler(nrf_sdh_state_evt_t state, void * p_context);

NRF_SDH_SOC_OBSERVER(m_soc_observer, POWER_CONFIG_SOC_OBSERVER_PRIO,
                     nrf_drv_power_sdh_soc_evt_handler, NULL);

NRF_SDH_STATE_OBSERVER(m_sd_observer, POWER_CONFIG_STATE_OBSERVER_PRIO) =
{
    .handler   = nrf_drv_power_sdh_state_evt_handler,
    .p_context = NULL
};

static void nrf_drv_power_sdh_soc_evt_handler(uint32_t evt_id, void * p_context)
{
    if (evt_id == NRF_EVT_POWER_FAILURE_WARNING)
    {
        nrfx_power_pofwarn_event_handler_t pofwarn_handler = nrfx_power_pof_handler_get();
        /* Cannot be null if event is enabled */
        ASSERT(pofwarn_handler != NULL);
        pofwarn_handler();
    }

#if NRF_POWER_HAS_USBREG
    nrfx_power_usb_event_handler_t usbevt_handler = nrfx_power_usb_handler_get();
    if (usbevt_handler != NULL)
    {
        switch (evt_id)
        {
            case NRF_EVT_POWER_USB_POWER_READY:
                usbevt_handler(NRFX_POWER_USB_EVT_READY);
                break;

            case NRF_EVT_POWER_USB_DETECTED:
                usbevt_handler(NRFX_POWER_USB_EVT_DETECTED);
                break;

            case NRF_EVT_POWER_USB_REMOVED:
                usbevt_handler(NRFX_POWER_USB_EVT_REMOVED);
                break;

            default:
                break;

        }
    }
#endif
}

static void nrf_drv_power_on_sd_enable(void)
{
    ASSERT(m_initialized); /* This module has to be enabled first */
    CRITICAL_REGION_ENTER();
    if (nrfx_power_pof_handler_get() != NULL)
    {
        ret_code_t err_code = sd_power_pof_enable(true);
        ASSERT(err_code == NRF_SUCCESS);
        UNUSED_VARIABLE(err_code); //handle no-debug case
    }
    CRITICAL_REGION_EXIT();

#if NRF_POWER_HAS_USBREG
    if (nrfx_power_usb_handler_get() != NULL)
    {
        ret_code_t err_code = nrf_drv_power_sd_usbevt_enable(true);
        ASSERT(err_code == NRF_SUCCESS);
        UNUSED_VARIABLE(err_code); //handle no-debug case
    }
#endif
}

static void nrf_drv_power_on_sd_disable(void)
{
    /* Reinit interrupts */
    ASSERT(m_initialized);
    NRFX_IRQ_PRIORITY_SET(POWER_CLOCK_IRQn, CLOCK_CONFIG_IRQ_PRIORITY);
    NRFX_IRQ_ENABLE(POWER_CLOCK_IRQn);
    if (nrfx_power_pof_handler_get() != NULL)
    {
        nrf_power_int_enable(NRF_POWER_INT_POFWARN_MASK);
    }

#if NRF_POWER_HAS_USBREG
    if (nrfx_power_usb_handler_get() != NULL)
    {
       nrf_power_int_enable(
           NRF_POWER_INT_USBDETECTED_MASK |
           NRF_POWER_INT_USBREMOVED_MASK  |
           NRF_POWER_INT_USBPWRRDY_MASK);
    }
#endif
}

static void nrf_drv_power_sdh_state_evt_handler(nrf_sdh_state_evt_t state, void * p_context)
{
    switch (state)
    {
        case NRF_SDH_EVT_STATE_ENABLED:
            nrf_drv_power_on_sd_enable();
            break;

        case NRF_SDH_EVT_STATE_DISABLED:
            nrf_drv_power_on_sd_disable();
            break;

        default:
            break;
    }
}

#endif // SOFTDEVICE_PRESENT
#endif //POWER_ENABLED
