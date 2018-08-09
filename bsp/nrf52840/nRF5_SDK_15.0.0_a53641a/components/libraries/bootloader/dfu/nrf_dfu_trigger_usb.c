/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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
#include "nrf_dfu_trigger_usb.h"
#include "app_usbd_string_config.h"
#include "app_usbd.h"
#include "app_usbd_nrf_dfu_trigger.h"
#include "nrf_drv_clock.h"
#include "nrf_log_ctrl.h"
#include "nrf_gpio.h"
#include "boards.h"
#include "app_util.h"
#include "app_usbd_serial_num.h"
#define NRF_LOG_MODULE_NAME nrf_dfu_trigger_usb
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#ifndef BSP_SELF_PINRESET_PIN
#error "This module is intended to be used with boards that have the GP pin shortened with the RESET pin."
#endif

/**
 * @brief Enable power USB detection.
 *
 * Configure if the example supports USB port connection.
 */
#ifndef USBD_POWER_DETECTION
#define USBD_POWER_DETECTION true
#endif

#define DFU_FLASH_PAGE_SIZE  (NRF_FICR->CODEPAGESIZE)
#define DFU_FLASH_PAGE_COUNT (NRF_FICR->CODESIZE)

// Semantic versioning string.
#define VERSION_STRING STRINGIFY(APP_VERSION_MAJOR) "." STRINGIFY(APP_VERSION_MINOR) "." STRINGIFY(APP_VERSION_PATCH) APP_VERSION_PRERELEASE APP_VERSION_METADATA

static uint8_t                                m_version_string[] = APP_NAME " " VERSION_STRING; ///< Human-readable version string.
static app_usbd_nrf_dfu_trigger_nordic_info_t m_dfu_info;                                       ///< Struct with various information about the current firmware.

static void dfu_trigger_evt_handler(app_usbd_class_inst_t        const *  p_inst,
                                    app_usbd_nrf_dfu_trigger_user_event_t event)
{
    UNUSED_PARAMETER(p_inst);

    switch (event)
    {
        case APP_USBD_NRF_DFU_TRIGGER_USER_EVT_DETACH:
            NRF_LOG_INFO("DFU Detach request received. Triggering a pin reset.");
            NRF_LOG_FINAL_FLUSH();
            nrf_gpio_cfg_output(BSP_SELF_PINRESET_PIN);
            nrf_gpio_pin_clear(BSP_SELF_PINRESET_PIN);
            break;
        default:
            break;
    }
}


APP_USBD_NRF_DFU_TRIGGER_GLOBAL_DEF(m_app_dfu,
                                    NRF_DFU_TRIGGER_USB_INTERFACE_NUM,
                                    &m_dfu_info,
                                    m_version_string,
                                    dfu_trigger_evt_handler);


static void usbd_user_evt_handler(app_usbd_event_type_t event)
{
    switch (event)
    {
        case APP_USBD_EVT_DRV_SUSPEND:
            break;
        case APP_USBD_EVT_DRV_RESUME:
            break;
        case APP_USBD_EVT_STARTED:
            break;
        case APP_USBD_EVT_STOPPED:
            app_usbd_disable();
            break;
        case APP_USBD_EVT_POWER_DETECTED:
            NRF_LOG_INFO("USB power detected");

            if (!nrf_drv_usbd_is_enabled())
            {
                app_usbd_enable();
            }
            break;
        case APP_USBD_EVT_POWER_REMOVED:
            NRF_LOG_INFO("USB power removed");
            app_usbd_stop();
            break;
        case APP_USBD_EVT_POWER_READY:
            NRF_LOG_INFO("USB ready");
            app_usbd_start();
            break;
        default:
            break;
    }
}


static void serial_number_strings_create(void)
{
    // Remove characters that are not supported in semantic versioning strings.
    for (size_t i = strlen(APP_NAME) + 1; i < strlen((char*)m_version_string); i++)
    {
        if (((m_version_string[i] >= 'a') && (m_version_string[i] <= 'z'))
         || ((m_version_string[i] >= 'A') && (m_version_string[i] <= 'Z'))
         || ((m_version_string[i] >= '0') && (m_version_string[i] <= '9'))
         ||  (m_version_string[i] == '+')
         ||  (m_version_string[i] == '.')
         ||  (m_version_string[i] == '-'))
        {
            // Valid semantic versioning character.
        }
        else
        {
            m_version_string[i] = '-';
        }
    }

#if !NRF_DFU_TRIGGER_USB_USB_SHARED
    app_usbd_serial_num_generate();
#endif
}

#if !(APP_USBD_CONFIG_EVENT_QUEUE_ENABLE)
static void usbd_evt_handler(app_usbd_internal_evt_t const * const p_event)
{
    app_usbd_event_execute(p_event);
}
#endif

ret_code_t nrf_dfu_trigger_usb_init(void)
{
    ret_code_t  ret;
    static bool initialized = false;

    if (initialized)
    {
        return NRF_SUCCESS;
    }

    m_dfu_info.wAddress       = CODE_START;
    m_dfu_info.wFirmwareSize  = CODE_SIZE;
    m_dfu_info.wVersionMajor  = APP_VERSION_MAJOR;
    m_dfu_info.wVersionMinor  = APP_VERSION_MINOR;
    m_dfu_info.wFirmwareID    = APP_ID;
    m_dfu_info.wFlashPageSize = DFU_FLASH_PAGE_SIZE;
    m_dfu_info.wFlashSize     = m_dfu_info.wFlashPageSize * DFU_FLASH_PAGE_COUNT;

    serial_number_strings_create();

    if (!NRF_DFU_TRIGGER_USB_USB_SHARED)
    {
        static const app_usbd_config_t usbd_config = {

#if !(APP_USBD_CONFIG_EVENT_QUEUE_ENABLE)
            .ev_handler = usbd_evt_handler,
#endif
            .ev_state_proc = usbd_user_evt_handler
        };

        ret = nrf_drv_clock_init();
        if ((ret != NRF_SUCCESS) && (ret != NRF_ERROR_MODULE_ALREADY_INITIALIZED))
        {
            return ret;
        }

        ret = app_usbd_init(&usbd_config);
        if (ret != NRF_SUCCESS)
        {
            return ret;
        }
    }

    app_usbd_class_inst_t const * class_dfu = app_usbd_nrf_dfu_trigger_class_inst_get(&m_app_dfu);
    ret = app_usbd_class_append(class_dfu);

    if (!NRF_DFU_TRIGGER_USB_USB_SHARED)
    {
        if (USBD_POWER_DETECTION)
        {
            ret = app_usbd_power_events_enable();
            APP_ERROR_CHECK(ret);
        }
        else
        {
            NRF_LOG_INFO("No USB power detection enabled\r\nStarting USB now");

            app_usbd_enable();
            app_usbd_start();
        }
    }

    if (ret == NRF_SUCCESS)
    {
        initialized = true;
    }

    return ret;
}
