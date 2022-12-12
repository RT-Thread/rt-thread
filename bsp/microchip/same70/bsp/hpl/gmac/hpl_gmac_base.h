/**
 * \file
 *
 * \brief functionality declaration.
 *
 * Copyright (c) 2017-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 */

#ifndef HPL_GMAC_BASE_H_
#define HPL_GMAC_BASE_H_

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Transmit buffer descriptor
 **/
typedef struct _mac_txbuf_descriptor {
	uint32_t address;
	union gmac_tx_status {
		uint32_t val;
		struct _gmac_tx_status_bm {
			uint32_t len : 14,                   /**< Length of buffer */
			    reserved : 1, last_buf : 1,      /**< Last buffer (in the current frame) */
			    no_crc : 1,                      /**< No CRC */
			    reserved1 : 3, checksum_err : 3, /**< Transmit checksum generation offload error */
			    reserved2 : 3, lco : 1,          /**< Late collision, transmit error detected */
			    exhausted : 1,                   /**< Buffer exhausted in mid frame */
			    reserved3 : 1, error : 1,        /**< Retry limit exceeded, error detected */
			    wrap : 1,                        /**< Marks last descriptor in TD list */
			    used : 1;                        /**< User clear, GMAC sets this to 1 once a frame
			                                          has been successfully transmitted */
		} bm;
	} status;
} _mac_txbuf_descr;

/**
 * @brief Receive buffer descriptor
 **/
typedef struct _mac_rxbuf_descriptor {
	union _gmac_rx_addr {
		uint32_t val;
		struct rx_addr_bm {
			uint32_t ownership : 1, /**< clear before buffer can be used again */
			    wrap : 1,           /**< Marks last entry in array */
			    addr : 30;          /**< Address in number of DW */
		} bm;
	} address;
	union gmac_rx_status {
		uint32_t val;
		struct _gmac_rx_status_bm {
			uint32_t len : 13,                    /**< Length of frame including FCS */
			    fcs : 1,                          /**< Frame has bad FCS */
			    sof : 1,                          /**< Start of frame */
			    eof : 1,                          /**< End of frame */
			    cfi : 1,                          /**< Concatenation Format Indicator */
			    vlan_priority : 3,                /**< VLAN priority (if VLAN detected) */
			    priority_detected : 1,            /**< Priority tag detected */
			    vlan_detected : 1,                /**< VLAN tag detected */
			    type_id_match : 2,                /**< Type ID match */
			    checksumoffload : 1,              /**< Checksum offload specific function */
			    addrmatch : 2,                    /**< Address register match */
			    ext_addr_match : 1,               /**< External address match found */
			    reserved : 1, uni_hash_match : 1, /**< Unicast hash match */
			    multi_hash_match : 1,             /**< Multicast hash match */
			    boardcast_detect : 1;             /**< Global broadcast address detected */
		} bm;
	} status;
} _mac_rxbuf_descr;

#ifdef __cplusplus
}
#endif

#endif /* HPL_GMAC_BASE_H_ */
