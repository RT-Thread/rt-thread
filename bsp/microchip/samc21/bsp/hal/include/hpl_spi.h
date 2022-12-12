/**
 * \file
 *
 * \brief SPI related functionality declaration.
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

#ifndef _HPL_SPI_H_INCLUDED
#define _HPL_SPI_H_INCLUDED

#include <compiler.h>
#include <utils.h>

/**
 * \addtogroup hpl_spi HPL SPI
 *
 *@{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief SPI Dummy char is used when reading data from the SPI slave
 */
#define SPI_DUMMY_CHAR 0x1ff

/**
 *  \brief SPI message to let driver to process
 */
//@{
struct spi_msg {
	/** Pointer to the output data buffer */
	uint8_t *txbuf;
	/** Pointer to the input data buffer */
	uint8_t *rxbuf;
	/** Size of the message data in SPI characters */
	uint32_t size;
};
//@}

/**
 *  \brief SPI transfer modes
 *  SPI transfer mode controls clock polarity and clock phase.
 *  Mode 0: leading edge is rising edge, data sample on leading edge.
 *  Mode 1: leading edge is rising edge, data sample on trailing edge.
 *  Mode 2: leading edge is falling edge, data sample on leading edge.
 *  Mode 3: leading edge is falling edge, data sample on trailing edge.
 */
enum spi_transfer_mode {
	/** Leading edge is rising edge, data sample on leading edge. */
	SPI_MODE_0,
	/** Leading edge is rising edge, data sample on trailing edge. */
	SPI_MODE_1,
	/** Leading edge is falling edge, data sample on leading edge. */
	SPI_MODE_2,
	/** Leading edge is falling edge, data sample on trailing edge. */
	SPI_MODE_3
};

/**
 *  \brief SPI character sizes
 *  The character size influence the way the data is sent/received.
 *  For char size <= 8 data is stored byte by byte.
 *  For char size between 9 ~ 16 data is stored in 2-byte length.
 *  Note that the default and recommended char size is 8 bit since it's
 *  supported by all system.
 */
enum spi_char_size {
	/** Character size is 8 bit. */
	SPI_CHAR_SIZE_8 = 0,
	/** Character size is 9 bit. */
	SPI_CHAR_SIZE_9 = 1,
	/** Character size is 10 bit. */
	SPI_CHAR_SIZE_10 = 2,
	/** Character size is 11 bit. */
	SPI_CHAR_SIZE_11 = 3,
	/** Character size is 12 bit. */
	SPI_CHAR_SIZE_12 = 4,
	/** Character size is 13 bit. */
	SPI_CHAR_SIZE_13 = 5,
	/** Character size is 14 bit. */
	SPI_CHAR_SIZE_14 = 6,
	/** Character size is 15 bit. */
	SPI_CHAR_SIZE_15 = 7,
	/** Character size is 16 bit. */
	SPI_CHAR_SIZE_16 = 8
};

/**
 *  \brief SPI data order
 */
enum spi_data_order {
	/** MSB goes first. */
	SPI_DATA_ORDER_MSB_1ST = 0,
	/** LSB goes first. */
	SPI_DATA_ORDER_LSB_1ST = 1
};

/** \brief Transfer descriptor for SPI
 *  Transfer descriptor holds TX and RX buffers
 */
struct spi_xfer {
	/** Pointer to data buffer to TX */
	uint8_t *txbuf;
	/** Pointer to data buffer to RX */
	uint8_t *rxbuf;
	/** Size of data characters to TX & RX */
	uint32_t size;
};

/** SPI generic driver. */
struct spi_dev {
	/** Pointer to the hardware base or private data for special device. */
	void *prvt;
	/** Reference start of sync/async variables */
	uint32_t sync_async_misc[1];
};

/**
 *  \brief Calculate the baudrate value for hardware to use to set baudrate
 *  \param[in, out] dev Pointer to the SPI device instance.
 *  \param[in] clk Clock frequency (Hz) for baudrate generation.
 *  \param[in] baud Target baudrate (bps).
 *  \return Error or baudrate value.
 *  \retval >0 Baudrate value.
 *  \retval ERR_INVALID_ARG Calculation fail.
 */
int32_t _spi_calc_baud_val(struct spi_dev *dev, const uint32_t clk, const uint32_t baud);

#ifdef __cplusplus
}
#endif

/**@}*/
#endif /* ifndef _HPL_SPI_H_INCLUDED */
