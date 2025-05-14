 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
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
 */

/******************************************************************************
 * @file       drv/iso7816.h
 * @brief      Header File for ISO7816 Driver
 * @version    V1.0
 * @date       9. Oct 2020
 * @model      iso7816
 ******************************************************************************/

#ifndef _DRV_ISO7816_H_
#define _DRV_ISO7816_H_

#include <stdint.h>
#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    A_5V,
    B_3_3V,
    C_1_8V,
} dcd_vclass_t;

typedef enum {
    T0,
    T1,
} iso7816_tprotocol_t;

typedef enum {
    ISO7816_EVENT_CARD_DETECTED,
    ISO7816_EVENT_READ_COMPLETE,
    ISO7816_EVENT_WRITE_COMPLETE,
    ISO7816_EVENT_READ_ERROR,
    ISO7816_EVENT_WRITE_ERROR,
    ISO7816_EVENT_ACTIVATE_SUCCESS,
    ISO7816_EVENT_ACTIVATE_FAILED,
    ISO7816_EVENT_CARD_ERROR_DEACTIVATE,
    ISO7816_EVENT_CARD_SESSION_CLOSED,
    ISO7816_EVENT_RX_FULL,
    ISO7816_EVENT_CWT_TIME_OUT,
    ISO7816_EVENT_RX_OVER,
    ISO7816_EVENT_CRC_ERR,
    ISO7816_EVENT_PARITY_ERR,
    ISO7816_EVENT_SLAVE_ATR_DETECTED,
    ISO7816_EVENT_SLAVE_ATR_DONE,
} iso7816_event_t;

typedef void (*iso7816_event_cb_t)(iso7816_event_t event, void *arg);

typedef enum {
    ISO7816_SLAVE,
    ISO7816_MASTER,
} iso7816_mode_t;

typedef struct {
    uint8_t           clk_div;
    dcd_vclass_t      vclass;
    iso7816_mode_t    mode;
    int32_t           card_detected_en;
} iso7816_config_t;

typedef enum {
    ISO7816_A_ONLY = 1U,
    ISO7816_B_ONLY,
    ISO7816_C_ONLY,
    ISO7816_AB,
    ISO7816_AC,
    ISO7816_BC,
    ISO7816_ABC,
} iso7816_voltage_class_t;

typedef struct {
    iso7816_voltage_class_t    support_voltage_class;
    int32_t                    proto_t;
    int32_t                    clk_stop_is_support;
    int32_t                    history_byte_num;
    uint8_t                    history_data[15];
} iso7816_atr_info_t;

typedef enum {
    EVEN_PARITY,
    ODD_PARITY,
} iso7816_parity_type_t;

typedef enum {
    ISO7816_DRIECT,
    ISO7816_INVERSE,
} iso7816_convention_t;

typedef enum {
    INVCTIVE,
    ACTIVATEING,
    PSS_TRF,
    PSS_RECV,
    ACTIVATE,
} iso7816_card_sta_t;

/**
  \brief       Initialize ISO7816 master interface
  \param[in]   idx         Master index
  \param[in]   cb_event    Pointer to \ref iso7816_event_cb_t
  \param[in]   cb_arg      Event callback arg
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_master_init(int idx, iso7816_event_cb_t cb_event, void *cb_arg);

/**
  \brief       Uninit ISO7816 master interface
  \param[in]   idx    Master index
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_master_uninit(int idx);

/**
  \brief       Config ISO7816 master attributes
  \param[in]   idx       Master index
  \param[in]   config    master config \ref iso7816_config_t
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_master_config(int idx, iso7816_config_t *config);

/**
  \brief       Receiving data from ISO7816 master receiver, used polling mode
  \param[in]   idx         Master index
  \param[in]   buf         Pointer to buffer for data to receive from i2s receiver
  \param[in]   len         Size of receiver data
  \param[in]   time_out    Receive time out value
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_master_receive(int idx, uint8_t *buf, uint32_t len, uint32_t time_out);

/**
  \brief       Receiving data from ISO7816 master receiver, used interrupt mode
  \param[in]   idx    Master index
  \param[in]   buf    Pointer to buffer for data to receive from i2s receiver
  \param[in]   len    Size of receiver data
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_master_receive_it(int idx, uint8_t *buf, uint32_t len);

/**
  \brief       Sending data to ISO7816 master transmitter, used polling mode
  \param[in]   idx         Master index
  \param[in]   buf         Pointer to buffer for data to send
  \param[in]   len         Size of tranmitter data
  \param[in]   time_out    Send time out value
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_master_send(int idx, uint8_t *buf, uint32_t len, uint32_t time_out);

/**
  \brief       Sending data to ISO7816 master transmitter, used interrupt mode
  \param[in]   idx    Master index
  \param[in]   buf    Pointer to buffer for data to send
  \param[in]   len    Size of tranmitter data
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_master_send_it(int idx, uint8_t *buf, uint32_t len);

/**
  \brief       ISO7816 master performs the activation smart card process, this process
               is non-blocking,should monitor callback event or read card status to check card is activate
  \param[in]   idx    Master index
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_master_card_activate(int idx);

/**
  \brief       ISO7816 master performs the deactivation smart card process, this process
               is non-blocking,should monitor callback event or read card status to check card is activate
  \param[in]   idx    Master index
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_master_card_deactivate(int idx);

/**
  \brief       The smard card session status
  \param[in]   idx    Master index
  \return      smart card status.
*/
iso7816_card_sta_t csi_iso7816_master_card_status(int idx);

/**
  \brief       ISO7816 master performs the warm reset smart card process
  \param[in]   idx    Master index
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_master_card_warm_reset(int idx);

/**
  \brief       ISO7816 master performs clock stop
  \param[in]   idx    Master index
  \param[in]   en     The clk last state when power down
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_master_card_clk_stop_enable(int idx, int en);

/**
  \brief       ISO7816 master performs pwoer down
  \param[in]   idx    Master index
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_master_power_down(int idx);

/**
  \brief       Get atr analytical results
  \param[in]   idx     Master index
  \param[out]  info    The result of atr information
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_master_atr_info(int idx, iso7816_atr_info_t *info);

/**
  \brief       Initialize ISO7816 slave interface
  \param[in]   idx       Slave index
  \param[in]   cb        Pointer to \ref iso7816_event_cb_t
  \param[in]   cb_arg    Event callback arg
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_init(int idx, iso7816_event_cb_t cb, void *cb_arg);

/**
  \brief       Uninit ISO7816 slave interface
  \param[in]   idx    Slave index
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_uninit(int idx);

/**
  \brief       Enable ISO7816 slave interface
  \param[in]   idx    Slave index
  \param[in]   en     Slave enable
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_enable(int idx, int en);

/**
  \brief       Enable ISO7816 slave receive parity
  \param[in]   idx    Slave index
  \param[in]   en     Enable receive parity
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_receive_parity_enable(int idx, int en);

/**
  \brief       Set ISO7816 slave receive parity attributes
  \param[in]   idx    Slave index
  \param[in]   type    Set receiver parity type
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_set_receive_parity(int idx, iso7816_parity_type_t type);

/**
  \brief       Enable ISO7816 slave send parity
  \param[in]   idx    Slave index
  \param[in]   en     Enable send parity
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_send_parity_enable(int idx, int en);

/**
  \brief       Set ISO7816 slave send parity attributes
  \param[in]   idx     Slave index
  \param[in]   type    Set send parity attributes
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_set_send_parity(int idx, iso7816_parity_type_t type);

/**
  \brief       Set the number of ISO7816 slave receive retry
  \param[in]   idx    Slave index
  \param[in]   val    Set the number retry
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_set_receive_retry(int idx, uint8_t val);

/**
  \brief       Set the number of ISO7816 send send retry
  \param[in]   idx    Slave index
  \param[in]   val    Set the number retry
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_set_send_retry(int idx, uint8_t val);

/**
  \brief       Set the ISO7816 slave GT
  \param[in]   idx    Slave index
  \param[in]   val    Set the slave GT
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_set_gt(int idx, uint8_t val);

/**
  \brief       Set the ISO7816 slave WT
  \param[in]   idx    Slave index
  \param[in]   val    Set the slave WT
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_set_wt(int idx, uint16_t val);

/**
  \brief       Set the ISO7816 slave baud, baud = F/D
  \param[in]   idx    Slave index
  \param[in]   val    Set the slave baud
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_set_baud(int idx, uint16_t val);

/**
  \brief       Set the ISO7816 slave convention
  \param[in]   idx           Slave index
  \param[in]   convention    Set the slave convention \ref iso7816_convention_t
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_set_convention(int idx, iso7816_convention_t convention);

/**
  \brief       Set the ISO7816 slave art response time, val range is 400~40000
  \param[in]   idx    Slave index
  \param[in]   val    Set the slave art response time
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_set_atr_ack_time(int idx, int val);

/**
  \brief       Set the ISO7816 slave send atr data
  \param[in]   idx    Slave index
  \param[in]   buf    Pointer to buffer for data to send
  \param[in]   len    Size of tranmitter data
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_send_atr(int idx, uint8_t *buf, int len);

/**
  \brief       Receiving data from ISO7816 slave receiver, used polling mode
  \param[in]   idx    Master index
  \param[in]   buf    Pointer to buffer for data to receive from i2s receiver
  \param[in]   len    Size of receiver data
  \param[in]   timer_out  receive time out value
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_receive(int idx, uint8_t *buf, uint32_t len, uint32_t time_out);

/**
  \brief       Flushed the ISO7816 slave receive fifo
  \param[in]   idx    Master index
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_flushed_receive_fifo(int idx);

/**
  \brief       Receiving data from ISO7816 slave receiver, used interrupt mode
  \param[in]   idx    Master index
  \param[in]   buf    Pointer to buffer for data to receive from i2s receiver
  \param[in]   len    Size of receiver data
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_receive_it(int idx, uint8_t *buf, uint32_t len);

/**
  \brief       Sending data to ISO7816 slave transmitter, used polling mode
  \param[in]   idx          Slave index
  \param[in]   buf          Pointer to buffer for data to send
  \param[in]   len          Size of tranmitter data
  \param[in]   timer_out    Send time out value
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_send(int idx, uint8_t *buf, uint32_t len, uint32_t time_out);

/**
  \brief       Flushed the ISO7816 slave send fifo.
  \param[in]   idx    Master index
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_flushed_send_fifo(int idx);

/**
  \brief       Sending data to ISO7816 slave transmitter, used interrupt mode
  \param[in]   idx    Slave index
  \param[in]   buf    Pointer to buffer for data to send
  \param[in]   len    Size of tranmitter data
  \return      0 for success, negative for error code
*/
int32_t csi_iso7816_slave_send_it(int idx, uint8_t *buf, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_ISO7816_H_ */
