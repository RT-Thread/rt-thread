/**
 * \file
 *
 * \brief Control Area Network(CAN) functionality declaration.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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
 *
 */

#ifndef HPL_CAN_H_INCLUDED
#define HPL_CAN_H_INCLUDED

#include <utils_assert.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup hpl_can CAN Common declaration
 *
 * \section can_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */

/**
 * \brief CAN Message Format
 */
enum can_format {
	CAN_FMT_STDID, /*!< Standard Format, 11 bits identifier */
	CAN_FMT_EXTID  /*!< Extended Format, 29 bits identifier */
};

/**
 * \brief CAN Message Type
 */
enum can_type {
	CAN_TYPE_DATA,  /*!< A DATA FRAME carries data from a transmitter to the
	                    receivers.*/
	CAN_TYPE_REMOTE /*!< A REMOTE FRAME is transmitted by a bus unit to request
	                     the transmission of the DATA FRAME with the same
	                     IDENTIFIER */
};

/**
 * \brief CAN Bus Mode
 */
enum can_mode {
	/** Normal operation Mode */
	CAN_MODE_NORMAL,
	/** In Bus Monitoring mode (see ISO11898-1, 10.12 Bus monitoring), the CAN
	 * is able to receive valid data frames and valid remote frames, but
	 * cannot start a transmission. In this mode, it sends only recessive bits
	 * on the CAN bus. If the CAN is required to send a dominant bit (ACK bit,
	 * overload flag, active error flag), the bit is rerouted internally so
	 * that the CAN monitors this dominant bit, although the CAN bus may
	 * remain in recessive state.
	 * The Bus Monitoring mode can be used to analyze the traffic on a CAN bus
	 * without affecting it by the transmission of dominant bits.
	 */
	CAN_MODE_MONITORING
};

/**
 * \brief CAN Message
 */
struct can_message {
	uint32_t        id;   /* Message identifier */
	enum can_type   type; /* Message Type */
	uint8_t *       data; /* Pointer to Message Data */
	uint8_t         len;  /* Message Length */
	enum can_format fmt;  /* Identifier format, CAN_STD, CAN_EXT */
};

/**
 * \brief CAN Filter
 */
struct can_filter {
	uint32_t id;   /* Message identifier */
	uint32_t mask; /* The mask applied to the id */
};

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* HPL_CAN_H_INCLUDED */
