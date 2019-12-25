/**
 * Copyright (c) 2016 - 2019 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 *
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
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
#ifndef RAL_API_H_INCLUDED
#define RAL_API_H_INCLUDED

#include "ral_api_spec.h"
#include "sys_time.h"
#include "phy_common.h"
#include "phy_pd_data.h"
#include "mac_common.h"
#include "mac_mlme_pib.h"
#include "mac_time.h"
#include <stdint.h>
#include <stdbool.h>

/**@file ral_api.h
 *
 * @defgroup ral_api Radio Abstraction Layer common API
 * @ingroup ral_15_4
 * @{
 *
 * @brief Radio abstraction layer common interface.
 *
 * @details These are requirements for the implementation code:
 *
 *          - no frames must be received between new frame indication and
 *            a call to ral_data_ind_read.
 */

// various constants to use with MAC/PHY header parsing
#define PHR_POS                  0
#define PHR_SIZE                 1
#define CRC_SIZE                 2
#define MAC_FRAME_CTRL_POS       0
#define MAC_FRAME_CTRL_SIZE      2
#define ACK_REQUEST_MASK         0x20
#define SEQ_NUM_POS             (MAC_FRAME_CTRL_POS + MAC_FRAME_CTRL_SIZE)
#define ACK_PD_BIT_MASK          0x0010

#define FRAME_TYPE_MASK          0x0007
#define FRAME_TYPE_BEACON        0x0000
#define FRAME_TYPE_DATA          0x0001
#define FRAME_TYPE_ACK           0x0002
#define FRAME_TYPE_COMMAND       0x0003

#define FRAME_PENDING_MASK       0x0010

/**@brief   RAL atomic section */
typedef volatile uint8_t  ral_atomic_t;

// private RAL data
typedef struct
{
    volatile uint8_t         tx_seq_num;
    volatile bool            ack_needed;
    volatile bool            waiting_for_ack;
    volatile ral_atomic_t    ral_atomic;
    volatile mac_timestamp_t received_frame_timestamp;
    volatile bool            spi_transfer;
    volatile bool            cca_performing;
#if defined(AT86RF231)
    volatile int8_t          ed_value;
    volatile bool            unread_frame;              /** This flag is used to deny transmission if incoming frame
                                                            has not been read from radio buffer.
                                                            todo: remove this deny to accelerate data exchange.
                                                         */
    volatile bool            is_promiscuous_mode;       /**< Set to true if promiscuous mode is enabled.*/
#elif (defined(NRF52_SERIES) || defined(NRF52))
    // pointer to free memory for rx DMA
    volatile uint8_t *       p_buffer;
    volatile sys_time_t      calibr_value;
    volatile uint8_t         bcc_part;
#endif
} ral_mem_t;


/**@brief   Initializes radio abstraction layer.
 */
void ral_init(void);

/**@brief   Resets radio abstraction layer.
 */
void ral_reset(void);

/**@brief   Performs synchronous ED measurement.
 */
uint8_t ral_ed_perform(void);

/**@brief Sends request to change radio state.
 *
 * @param state - New radio state. One of...
 *
 * @return PHY_SUCCESS, if state has been successfully achieved;
 *         current state, if state cannot be reached.*/
phy_enum_t ral_state_set(const phy_enum_t state);

/**@brief Returns current state of radio.
 */
phy_enum_t ral_state_get(void);

/**@brief Puts radio into sleep mode
 */
void ral_sleep(void);

 /**@brief Awakes a radio
  */
void ral_wakeup(void);

/**@brief   Performs synchronous cca.
 */
phy_status_t ral_cca_perform(void);

/**@brief Sends PHY frame.
 *
 * @param[in] pd_data - full data frame to be send.
 *
 * @details RAL automatically adds header and FCS control bytes
 * to \a pd_data. Caller must reserve 1 byte before \a psdu
 * pointer and may leave last two bytes of payload (i.e. FCS
 * control field) uninitialized.
 *
 * RF chip or RAL code is responsible to receive an ACK frame.
 * After ACK is handled, device should be restored to the TX state.*/
void ral_data_req(pd_data_req_t * pd_data);

/**@brief Reads indication frame from radio.
 *
 * @retval  Pointer on the structure of a PHY data indication
 *          with received frame.
 */
pd_data_ind_t * ral_data_ind_read(void);

/**@brief   Enable data flow from radio hardware after it was disabled
 *          by ral_data_flow_disable().
 */
void ral_data_flow_enable(void);


/**@brief   Disable data flow from radio hardware
 */
void ral_data_flow_disable(void);


/**@brief This function is used to set attribute from MAC or PHY layer
 * without checking of its boundaries.
 *
 * @param id - one of #MAC_SHORT_ADDRESS, #MAC_EXTENDED_ADDRESS, #MAC_PAN_ID 
 * and some other values.
 * @param p_value - pointer to new value.
 */
void ral_attribute_set(uint8_t id, const void * p_value);


/**@brief This function is used to get a copy of attribute value stored inside
 * radio module.
 *
 * @param[in] id - one of #PHY_CURRENT_CHANNEL_ID, #PHY_TRANSMIT_POWER_ID or
 * #PHY_CCA_MODE_ID. Other attributes are not supported.
 * @param[out] p_attr_value - pointer to value to get.
 */
void ral_attribute_get(uint8_t id, void * p_attr_value);

/**@brief This function is used to define frame start time by it's size
 * and the timestamp, when RX IRQ has been received.
 *
 * @param irq_time - moment when IRQ has been received.
 * @param frame_size - size of received frame in bytes.
 *
 * @retval MAC timestamp when PHY header has been started to receive.
 */
mac_timestamp_t ral_rx_start_time(mac_timestamp_t irq_time, uint8_t frame_size);

/**@brief This function performs RSSI.
 *
 * @return  RSSI sample value.
 */
uint8_t ral_rssi_get(void);

/**@brief This function calculates the adjusted RSSI value using a temperature
 * correction factor.
 *
 * @param[in] rssi - RSSI sample value (as returned by @ref ral_rssi_get).
 * @param[in] temp - Temperature value in °C.
 *
 * @return  Temperature-corrected RSSI value.
 */
uint8_t ral_rssi_corrected_get(uint8_t rssi, int8_t temp);

/** @} */

#endif /* RAL_API_H_INCLUDED */
