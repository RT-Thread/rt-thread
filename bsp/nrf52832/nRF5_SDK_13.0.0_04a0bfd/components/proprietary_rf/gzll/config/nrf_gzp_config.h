/**
 * Copyright (c) 2008 - 2017, Nordic Semiconductor ASA
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
#ifndef __GZP_CONFIG_H
#define __GZP_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Definition of "secret key" used during "Host ID exchange".
 */

#define GZP_SECRET_KEY {1, 23, 45, 57, 26, 68, 12, 64, 13, 73, 13, 62, 26, 45, 12, 77}

//-----------------------------------------------------------------------------

/**
  Definition of the first static selected pairing channel. Should be located in
  the lower Nth of the channel range, where N is the size if the channel subset
  selected by the application.
*/
#define GZP_CHANNEL_LOW 2

/**
  Definition of the second static selected pairing channel. Should be located in
  the upper Nth of the channel range, where N is the size if the channel subset
  selected by the application.
*/
#define GZP_CHANNEL_HIGH 79

/**
  Definition of the static "global" pairing address.
*/
#define GZP_ADDRESS 4, 6, 8, 10

/**
  Reduced TX power for use during close proximity pairing.
 */
#define GZP_POWER NRF_GZLL_TX_POWER_N16_DBM

/**
  Definition of pairing request timeout.
*/
#define GZP_REQ_TX_TIMEOUT 200

/**
  Definition of the maximimum number of "backoff" packets (step 0) to be transmitted.
*/
#define GZP_MAX_BACKOFF_PACKETS 100

/**
  Definition of the period a device shall wait before attempting to send the packet for
  fetching the pairing response (step 1).
*/
#define GZP_TX_ACK_WAIT_TIMEOUT (GZP_CLOSE_PROXIMITY_BACKOFF_RX_TIMEOUT + 50)

/**
  Definition of the period a device in close proximity shall back off on the pairing
  address after a backoff packet has been received.
*/
#define GZP_CLOSE_PROXIMITY_BACKOFF_RX_TIMEOUT ((GZP_REQ_TX_TIMEOUT / 2) + 50)

/**
  Definition of the period a device NOT in close proximity shall back off on the pairing
  address after a backoff packet has been received.
*/
#define GZP_NOT_PROXIMITY_BACKOFF_RX_TIMEOUT (GZP_CLOSE_PROXIMITY_BACKOFF_RX_TIMEOUT + GZP_STEP1_RX_TIMEOUT)

/**
  Definition of the time the host waits for a device to complete
  transmission of the pairing request step 1 packet.
*/
#define GZP_STEP1_RX_TIMEOUT (((GZP_REQ_TX_TIMEOUT / 2) + GZP_TX_ACK_WAIT_TIMEOUT) + 50)

/**
  Definition of the lowest boundary for the channel range to be used.
*/
#define GZP_CHANNEL_MIN 2

/**
  Definition of the upper boundary for the channel range to be used.
*/
#define GZP_CHANNEL_MAX 80

/**
  Definition of the minimum channel spacing for the channel subset generated
  during pairing.
*/
#define GZP_CHANNEL_SPACING_MIN 5

/**
  Non volatile memory (Flash or OTP) storage address. A device will
  require GZP_DEVICE_PARAMS_STORAGE_SIZE bytes of memory, and
  Host 11 bytes. When using flash memory, storage address should
  be a multiple of chip page size.
*/
#define GZP_PARAMS_STORAGE_ADR 0x00001000

/**
  Number of bytes available for parameter storage in Device.
  It is equal to flash page size on nRF5x chips.
*/
#if defined (NRF51)
    #define GZP_DEVICE_PARAMS_STORAGE_SIZE 1024
#elif defined (NRF52)
    #define GZP_DEVICE_PARAMS_STORAGE_SIZE 4096
#endif

/**
  Maximum Device TX payload length [bytes].
 */
#define GZP_MAX_FW_PAYLOAD_LENGTH 17

/**
  Maximum Host ACK payload length [bytes].
 */
#define GZP_MAX_ACK_PAYLOAD_LENGTH 10



#ifdef __cplusplus
}
#endif

#endif
