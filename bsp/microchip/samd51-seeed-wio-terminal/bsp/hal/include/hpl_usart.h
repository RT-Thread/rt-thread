/**
 * \file
 *
 * \brief USART related functionality declaration.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _HPL_USART_H_INCLUDED
#define _HPL_USART_H_INCLUDED

/**
 * \addtogroup HPL USART SYNC
 *
 * \section hpl_usart_sync_rev Revision History
 * - v1.0.0 Initial Release
 *
 *@{
 */

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief USART flow control state
 */
union usart_flow_control_state {
	struct {
		uint8_t cts : 1;
		uint8_t rts : 1;
		uint8_t unavailable : 1;
		uint8_t reserved : 5;
	} bit;
	uint8_t value;
};

/**
 * \brief USART baud rate mode
 */
enum usart_baud_rate_mode { USART_BAUDRATE_ASYNCH_ARITHMETIC, USART_BAUDRATE_ASYNCH_FRACTIONAL, USART_BAUDRATE_SYNCH };

/**
 * \brief USART data order
 */
enum usart_data_order { USART_DATA_ORDER_MSB = 0, USART_DATA_ORDER_LSB = 1 };

/**
 * \brief USART mode
 */
enum usart_mode { USART_MODE_ASYNCHRONOUS = 0, USART_MODE_SYNCHRONOUS = 1 };

/**
 * \brief USART parity
 */
enum usart_parity {
	USART_PARITY_EVEN  = 0,
	USART_PARITY_ODD   = 1,
	USART_PARITY_NONE  = 2,
	USART_PARITY_SPACE = 3,
	USART_PARITY_MARK  = 4
};

/**
 * \brief USART stop bits mode
 */
enum usart_stop_bits { USART_STOP_BITS_ONE = 0, USART_STOP_BITS_TWO = 1, USART_STOP_BITS_ONE_P_FIVE = 2 };

/**
 * \brief USART character size
 */
enum usart_character_size {
	USART_CHARACTER_SIZE_8BITS = 0,
	USART_CHARACTER_SIZE_9BITS = 1,
	USART_CHARACTER_SIZE_5BITS = 5,
	USART_CHARACTER_SIZE_6BITS = 6,
	USART_CHARACTER_SIZE_7BITS = 7
};

//@}

#ifdef __cplusplus
}
#endif
/**@}*/
#endif /* _HPL_USART_H_INCLUDED */
