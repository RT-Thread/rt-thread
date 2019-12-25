/**
 * Copyright (c) 2013 - 2019, Nordic Semiconductor ASA
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
#include "ble_gattc_evt_app.h"
#include <string.h>
#include "ble_serialization.h"
#include "ble_gattc_struct_serialization.h"
#include "app_util.h"

uint32_t ble_gattc_evt_attr_info_disc_rsp_dec(uint8_t const * const p_buf,
                                              uint32_t              packet_len,
                                              ble_evt_t * const     p_event,
                                              uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GATTC_EVT_ATTR_INFO_DISC_RSP, gattc, attr_info_disc_rsp);

    SER_PULL_uint16(&p_event->evt.gattc_evt.conn_handle);
    SER_PULL_uint16(&p_event->evt.gattc_evt.gatt_status);
    SER_PULL_uint16(&p_event->evt.gattc_evt.error_handle);
    SER_PULL_FIELD_EXTENDED(&p_event->evt.gattc_evt.params.attr_info_disc_rsp,
                            ble_gattc_evt_attr_info_disc_rsp_t_dec);

    SER_EVT_DEC_END;
}

uint32_t ble_gattc_evt_char_disc_rsp_dec(uint8_t const * const p_buf,
                                         uint32_t              packet_len,
                                         ble_evt_t * const     p_event,
                                         uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GATTC_EVT_CHAR_DISC_RSP, gattc, char_disc_rsp);

    SER_PULL_uint16(&p_event->evt.gattc_evt.conn_handle);
    SER_PULL_uint16(&p_event->evt.gattc_evt.gatt_status);
    SER_PULL_uint16(&p_event->evt.gattc_evt.error_handle);
    SER_PULL_FIELD_EXTENDED(&p_event->evt.gattc_evt.params.char_disc_rsp,
                            ble_gattc_evt_char_disc_rsp_t_dec);

    SER_EVT_DEC_END;
}



uint32_t ble_gattc_evt_char_val_by_uuid_read_rsp_dec(uint8_t const * const p_buf,
                                                     uint32_t              packet_len,
                                                     ble_evt_t * const     p_event,
                                                     uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GATTC_EVT_CHAR_VAL_BY_UUID_READ_RSP, gattc, char_val_by_uuid_read_rsp);

    SER_PULL_uint16(&p_event->evt.gattc_evt.conn_handle);
    SER_PULL_uint16(&p_event->evt.gattc_evt.gatt_status);
    SER_PULL_uint16(&p_event->evt.gattc_evt.error_handle);
    SER_PULL_FIELD_EXTENDED(&p_event->evt.gattc_evt.params.char_val_by_uuid_read_rsp,
                            ble_gattc_evt_char_val_by_uuid_read_rsp_t_dec);

    SER_EVT_DEC_END;
}


uint32_t ble_gattc_evt_char_vals_read_rsp_dec(uint8_t const * const p_buf,
                                              uint32_t              packet_len,
                                              ble_evt_t * const     p_event,
                                              uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GATTC_EVT_CHAR_VALS_READ_RSP, gattc, char_vals_read_rsp);

    SER_PULL_uint16(&p_event->evt.gattc_evt.conn_handle);
    SER_PULL_uint16(&p_event->evt.gattc_evt.gatt_status);
    SER_PULL_uint16(&p_event->evt.gattc_evt.error_handle);
    SER_PULL_FIELD_EXTENDED(&p_event->evt.gattc_evt.params.char_vals_read_rsp,
                            ble_gattc_evt_char_vals_read_rsp_t_dec);

    SER_EVT_DEC_END;
}


uint32_t ble_gattc_evt_desc_disc_rsp_dec(uint8_t const * const p_buf,
                                         uint32_t              packet_len,
                                         ble_evt_t * const     p_event,
                                         uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GATTC_EVT_DESC_DISC_RSP, gattc, desc_disc_rsp);

    SER_PULL_uint16(&p_event->evt.gattc_evt.conn_handle);
    SER_PULL_uint16(&p_event->evt.gattc_evt.gatt_status);
    SER_PULL_uint16(&p_event->evt.gattc_evt.error_handle);
    SER_PULL_FIELD_EXTENDED(&p_event->evt.gattc_evt.params.desc_disc_rsp,
                            ble_gattc_evt_desc_disc_rsp_t_dec);

    SER_EVT_DEC_END;
}

uint32_t ble_gattc_evt_hvx_dec(uint8_t const * const p_buf,
                               uint32_t              packet_len,
                               ble_evt_t * const     p_event,
                               uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GATTC_EVT_HVX, gattc, hvx);

    SER_PULL_uint16(&p_event->evt.gattc_evt.conn_handle);
    SER_PULL_uint16(&p_event->evt.gattc_evt.gatt_status);
    SER_PULL_uint16(&p_event->evt.gattc_evt.error_handle);
    SER_PULL_FIELD_EXTENDED(&p_event->evt.gattc_evt.params.hvx,
                            ble_gattc_evt_hvx_t_dec);

    SER_EVT_DEC_END;
}


uint32_t ble_gattc_evt_prim_srvc_disc_rsp_dec(uint8_t const * const p_buf,
                                              uint32_t              packet_len,
                                              ble_evt_t * const     p_event,
                                              uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GATTC_EVT_PRIM_SRVC_DISC_RSP, gattc, prim_srvc_disc_rsp);

    SER_PULL_uint16(&p_event->evt.gattc_evt.conn_handle);
    SER_PULL_uint16(&p_event->evt.gattc_evt.gatt_status);
    SER_PULL_uint16(&p_event->evt.gattc_evt.error_handle);
    SER_PULL_FIELD_EXTENDED(&p_event->evt.gattc_evt.params.prim_srvc_disc_rsp,
                            ble_gattc_evt_prim_srvc_disc_rsp_t_dec);

    SER_EVT_DEC_END;
}

uint32_t ble_gattc_evt_read_rsp_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    ble_evt_t * const     p_event,
                                    uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GATTC_EVT_READ_RSP, gattc, read_rsp);

    SER_PULL_uint16(&p_event->evt.gattc_evt.conn_handle);
    SER_PULL_uint16(&p_event->evt.gattc_evt.gatt_status);
    SER_PULL_uint16(&p_event->evt.gattc_evt.error_handle);
    SER_PULL_FIELD_EXTENDED(&p_event->evt.gattc_evt.params.read_rsp,
                            ble_gattc_evt_read_rsp_t_dec);

    SER_EVT_DEC_END;
}


#define BLE_GATTC_EVT_REL_DISC_RSP_COUNT_POSITION 6


uint32_t ble_gattc_evt_rel_disc_rsp_dec(uint8_t const * const p_buf,
                                        uint32_t              packet_len,
                                        ble_evt_t * const     p_event,
                                        uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GATTC_EVT_READ_RSP, gattc, rel_disc_rsp);

    SER_PULL_uint16(&p_event->evt.gattc_evt.conn_handle);
    SER_PULL_uint16(&p_event->evt.gattc_evt.gatt_status);
    SER_PULL_uint16(&p_event->evt.gattc_evt.error_handle);
    SER_PULL_FIELD_EXTENDED(&p_event->evt.gattc_evt.params.rel_disc_rsp,
                            ble_gattc_evt_rel_disc_rsp_t_dec);

    SER_EVT_DEC_END;
}


uint32_t ble_gattc_evt_timeout_dec(uint8_t const * const p_buf,
                                   uint32_t              packet_len,
                                   ble_evt_t * const     p_event,
                                   uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GATTC_EVT_TIMEOUT, gattc, timeout);

    SER_PULL_uint16(&p_event->evt.gattc_evt.conn_handle);
    SER_PULL_uint16(&p_event->evt.gattc_evt.gatt_status);
    SER_PULL_uint16(&p_event->evt.gattc_evt.error_handle);
    SER_PULL_FIELD(&p_event->evt.gattc_evt.params.timeout,
                   ble_gattc_evt_timeout_t_dec);

    SER_EVT_DEC_END;
}

uint32_t ble_gattc_evt_write_rsp_dec(uint8_t const * const p_buf,
                                     uint32_t              packet_len,
                                     ble_evt_t * const     p_event,
                                     uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GATTC_EVT_WRITE_RSP, gattc, write_rsp);

    SER_PULL_uint16(&p_event->evt.gattc_evt.conn_handle);
    SER_PULL_uint16(&p_event->evt.gattc_evt.gatt_status);
    SER_PULL_uint16(&p_event->evt.gattc_evt.error_handle);
    SER_PULL_FIELD_EXTENDED(&p_event->evt.gattc_evt.params.write_rsp,
                            ble_gattc_evt_write_rsp_t_dec);

    SER_EVT_DEC_END;
}

uint32_t ble_gattc_evt_exchange_mtu_rsp_dec(uint8_t const * const p_buf,
                                            uint32_t              packet_len,
                                            ble_evt_t * const     p_event,
                                            uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GATTC_EVT_EXCHANGE_MTU_RSP, gattc, exchange_mtu_rsp);

    SER_PULL_uint16(&p_event->evt.gattc_evt.conn_handle);
    SER_PULL_uint16(&p_event->evt.gattc_evt.gatt_status);
    SER_PULL_uint16(&p_event->evt.gattc_evt.error_handle);
    SER_PULL_FIELD(&p_event->evt.gattc_evt.params.exchange_mtu_rsp,
                            ble_gattc_evt_exchange_mtu_rsp_t_dec);

    SER_EVT_DEC_END;
}

#if NRF_SD_BLE_API_VERSION >= 4
uint32_t ble_gattc_evt_write_cmd_tx_complete_dec(uint8_t const * const p_buf,
                                                 uint32_t              packet_len,
                                                 ble_evt_t * const     p_event,
                                                 uint32_t * const      p_event_len)
{
    SER_EVT_DEC_BEGIN(BLE_GATTC_EVT_WRITE_CMD_TX_COMPLETE, gattc, write_cmd_tx_complete);
    SER_PULL_uint16(&p_event->evt.gattc_evt.conn_handle);
    SER_PULL_uint16(&p_event->evt.gattc_evt.gatt_status);
    SER_PULL_uint16(&p_event->evt.gattc_evt.error_handle);
    SER_PULL_uint8(&p_event->evt.gattc_evt.params.write_cmd_tx_complete.count);

    SER_EVT_DEC_END;
}
#endif
