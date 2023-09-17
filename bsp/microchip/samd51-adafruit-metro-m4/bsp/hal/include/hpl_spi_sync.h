/**
 * \file
 *
 * \brief Common SPI related functionality declaration.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _HPL_SPI_SYNC_H_INCLUDED
#define _HPL_SPI_SYNC_H_INCLUDED

#include <compiler.h>
#include <utils.h>

#include <hpl_spi.h>

/**
 * \addtogroup hpl_spi HPL SPI
 *
 * \section hpl_spi_rev Revision History
 * - v1.0.0 Initial Release
 *
 *@{
 */

#ifdef __cplusplus
extern "C" {
#endif

/** SPI driver to support sync HAL */
struct _spi_sync_dev {
	/** Pointer to the hardware base or private data for special device. */
	void *prvt;
	/** Data size, number of bytes for each character */
	uint8_t char_size;
	/** Dummy byte used in master mode when reading the slave */
	uint16_t dummy_byte;
};

#ifdef __cplusplus
}
#endif

/**@}*/
#endif /* ifndef _HPL_SPI_SYNC_H_INCLUDED */
