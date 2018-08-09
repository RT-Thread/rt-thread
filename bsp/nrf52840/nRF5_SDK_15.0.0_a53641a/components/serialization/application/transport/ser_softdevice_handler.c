/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
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
#include <stdlib.h>
#include <string.h>
#include "nrf_queue.h"
#include "app_scheduler.h"
#include "nrf_sdh.h"
#include "nrf_sdm.h"
#include "ser_sd_transport.h"
#include "ser_app_hal.h"
#include "ser_config.h"
#include "nrf_soc.h"
#include "ble_serialization.h"
#if defined(BLE_STACK_SUPPORT_REQD)
#include "ble_app.h"
#include "nrf_sdh_ble.h"
#endif
#if defined(ANT_STACK_SUPPORT_REQD)
#include "ant_event.h"
#endif

#define SD_BLE_EVT_MAILBOX_QUEUE_SIZE 5 /**< Size of mailbox queue. */

/** @brief Structure used to pass packet details through mailbox.
 */
#if defined(BLE_STACK_SUPPORT_REQD)
typedef struct
{
    //lint -save -e666
    uint32_t evt_data[CEIL_DIV(NRF_SDH_BLE_EVT_BUF_SIZE, sizeof (uint32_t))]; /**< Buffer for decoded event */
    //lint -restore
} ser_sd_handler_evt_data_t;
#endif

#if defined(ANT_STACK_SUPPORT_REQD)
typedef struct
{
    uint32_t evt_data[CEIL_DIV(sizeof(ant_evt_t), sizeof (uint32_t))]; /**< Buffer for decoded event */
} ser_ant_sd_handler_evt_data_t;
#endif

/** @brief
 *   Mailbox used for communication between event handler (called from serial stream
 *   interrupt context) and event processing function (called from scheduler or interrupt context).
 */
#if defined(BLE_STACK_SUPPORT_REQD)
NRF_QUEUE_DEF(ser_sd_handler_evt_data_t,
              m_sd_ble_evt_mailbox,
              SD_BLE_EVT_MAILBOX_QUEUE_SIZE,
              NRF_QUEUE_MODE_NO_OVERFLOW);
#endif

#if defined(ANT_STACK_SUPPORT_REQD)
NRF_QUEUE_DEF(ser_ant_sd_handler_evt_data_t,
              m_sd_ant_evt_mailbox,
              SD_BLE_EVT_MAILBOX_QUEUE_SIZE,
              NRF_QUEUE_MODE_NO_OVERFLOW);
#endif

NRF_QUEUE_DEF(uint32_t,
              m_sd_soc_evt_mailbox,
              SD_BLE_EVT_MAILBOX_QUEUE_SIZE,
              NRF_QUEUE_MODE_NO_OVERFLOW);

/**
 * @brief Function to be replaced by user implementation if needed.
 *
 * Weak function - user can add different implementation of this function if application needs it.
 */
__WEAK void os_rsp_set_handler(void)
{

}

static void connectivity_reset_low(void)
{
    //Signal a reset to the connectivity chip by setting the reset pin low.
    ser_app_hal_nrf_reset_pin_clear();
    ser_app_hal_delay(CONN_CHIP_RESET_TIME);

}

static void connectivity_reset_high(void)
{

    //Set the reset level to high again.
    ser_app_hal_nrf_reset_pin_set();

    //Wait for connectivity chip to be ready.
    ser_app_hal_delay(CONN_CHIP_WAKEUP_TIME);
}

#if defined(BLE_STACK_SUPPORT_REQD)
static void ser_softdevice_ble_evt_handler(uint8_t * p_data, uint16_t length)
{
    ser_sd_handler_evt_data_t item;
    uint32_t                  err_code;
    uint32_t                  len32 = sizeof (item.evt_data);

    err_code = ble_event_dec(p_data, length, (ble_evt_t *)item.evt_data, &len32);
    APP_ERROR_CHECK(err_code);

    err_code = ser_sd_transport_rx_free(p_data);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_queue_push(&m_sd_ble_evt_mailbox, &item);
    APP_ERROR_CHECK(err_code);

    ser_app_hal_nrf_evt_pending();
}
#endif

#if defined(ANT_STACK_SUPPORT_REQD)
static void ser_softdevice_ant_evt_handler(uint8_t * p_data, uint16_t length)
{
    ser_ant_sd_handler_evt_data_t item;
    uint32_t                      err_code;
    uint32_t                      len32 = sizeof (item.evt_data);

    err_code = ant_event_dec(p_data, length, (ant_evt_t *)item.evt_data, &len32);
    APP_ERROR_CHECK(err_code);

    err_code = ser_sd_transport_rx_free(p_data);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_queue_push(&m_sd_ant_evt_mailbox, &item);
    APP_ERROR_CHECK(err_code);

    ser_app_hal_nrf_evt_pending();
}
#endif

void ser_softdevice_flash_operation_success_evt(bool success)
{
    uint32_t evt_type = success ? NRF_EVT_FLASH_OPERATION_SUCCESS :
            NRF_EVT_FLASH_OPERATION_ERROR;

    uint32_t err_code = nrf_queue_push(&m_sd_soc_evt_mailbox, &evt_type);
    APP_ERROR_CHECK(err_code);

    ser_app_hal_nrf_evt_pending();
}

/**
 * @brief Function called while waiting for connectivity chip response. It handles incoming events.
 */
static void ser_sd_rsp_wait(void)
{
    do
    {
        (void)sd_app_evt_wait();

        //intern_softdevice_events_execute();
    }
    while (ser_sd_transport_is_busy());
}

uint32_t sd_evt_get(uint32_t * p_evt_id)
{
    return nrf_queue_pop(&m_sd_soc_evt_mailbox, p_evt_id);
}

#if defined(BLE_STACK_SUPPORT_REQD)
uint32_t sd_ble_evt_get(uint8_t * p_data, uint16_t * p_len)
{
    uint32_t err_code = nrf_queue_pop(&m_sd_ble_evt_mailbox, p_data);

    if (err_code == NRF_SUCCESS) //if anything in the mailbox
    {
        if (((ble_evt_t *)p_data)->header.evt_len > *p_len)
        {
            err_code = NRF_ERROR_DATA_SIZE;
        }
        else
        {
            *p_len = ((ble_evt_t *)p_data)->header.evt_len;
        }
    }
    else
    {
        err_code = NRF_ERROR_NOT_FOUND;
    }

    return err_code;
}
#endif

#if defined(ANT_STACK_SUPPORT_REQD)
uint32_t sd_ant_event_get(uint8_t* p_channel, uint8_t* p_event, uint8_t* p_ant_mesg)
{
    SER_ASSERT_NOT_NULL(p_channel);
    SER_ASSERT_NOT_NULL(p_event);
    SER_ASSERT_NOT_NULL(p_ant_mesg);

    uint32_t err_code;

    ser_ant_sd_handler_evt_data_t item;

    err_code = nrf_queue_pop(&m_sd_ant_evt_mailbox, &item);

    if (err_code == NRF_SUCCESS)
    {
        *p_event     = ((ant_evt_t *)item.evt_data) -> event;
        *p_channel   = ((ant_evt_t *)item.evt_data) -> channel;
        memcpy(p_ant_mesg, ((ant_evt_t *)item.evt_data)->message.aucMessage, MESG_BUFFER_SIZE);
    } else {
        err_code = NRF_ERROR_NOT_FOUND;
    }

    return err_code;
}
#endif

#if defined(BLE_STACK_SUPPORT_REQD)
uint32_t sd_ble_evt_mailbox_length_get(uint32_t * p_mailbox_length)
{
    *p_mailbox_length = nrf_queue_utilization_get(&m_sd_ble_evt_mailbox);
    return NRF_SUCCESS;
}
#endif

#if (defined(S332) || defined(S212))
uint32_t sd_softdevice_enable(nrf_clock_lf_cfg_t const * p_clock_lf_cfg,
                              nrf_fault_handler_t fault_handler,
                              const char* p_license_key)
#else
uint32_t sd_softdevice_enable(nrf_clock_lf_cfg_t const * p_clock_lf_cfg,
                              nrf_fault_handler_t assertion_handler)
#endif
{
    uint32_t err_code;

    err_code = ser_app_hal_hw_init(ser_softdevice_flash_operation_success_evt);

    if (err_code == NRF_SUCCESS)
    {
        connectivity_reset_low();

        nrf_queue_reset(&m_sd_soc_evt_mailbox);
        ser_sd_transport_evt_handler_t ble_evt_handler = NULL;
        ser_sd_transport_evt_handler_t ant_evt_handler = NULL;

#ifdef BLE_STACK_SUPPORT_REQD
        ble_evt_handler = ser_softdevice_ble_evt_handler;
        nrf_queue_reset(&m_sd_ble_evt_mailbox);
#endif // BLE_STACK_SUPPORT_REQD

#ifdef ANT_STACK_SUPPORT_REQD
        ant_evt_handler = ser_softdevice_ant_evt_handler;
        nrf_queue_reset(&m_sd_ant_evt_mailbox);
#endif // ANT_STACK_SUPPORT_REQD
        err_code = ser_sd_transport_open(ble_evt_handler,
                                         ant_evt_handler,
                                         ser_sd_rsp_wait,
                                         os_rsp_set_handler,
                                         NULL);

        if (err_code == NRF_SUCCESS)
        {
          connectivity_reset_high();
        }

        ser_app_hal_nrf_evt_irq_priority_set();
    }

    return err_code;
}


uint32_t sd_softdevice_disable(void)
{
    return ser_sd_transport_close();
}

