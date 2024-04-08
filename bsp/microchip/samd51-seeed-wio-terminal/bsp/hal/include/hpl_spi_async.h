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

#ifndef _HPL_SPI_ASYNC_H_INCLUDED
#define _HPL_SPI_ASYNC_H_INCLUDED

#include <hpl_spi.h>
#include <hpl_irq.h>

/**
 * \addtogroup hpl_spi HPL SPI
 *
 *@{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief Callbacks the SPI driver must offer in async mode
 */
//@{
/** The callback types */
enum _spi_async_dev_cb_type {
	/** Callback type for transmit, see \ref _spi_async_dev_cb_xfer_t. */
	SPI_DEV_CB_TX,
	/** Callback type for receive, see \ref _spi_async_dev_cb_xfer_t. */
	SPI_DEV_CB_RX,
	/** Callback type for \ref _spi_async_dev_cb_complete_t. */
	SPI_DEV_CB_COMPLETE,
	/** Callback type for error */
	SPI_DEV_CB_ERROR,
	/** Number of callbacks. */
	SPI_DEV_CB_N
};

struct _spi_async_dev;

/** \brief The prototype for callback on SPI transfer error.
 *  If status code is zero, it indicates the normal completion, that is,
 *  SS deactivation.
 *  If status code belows zero, it indicates complete.
 */
typedef void (*_spi_async_dev_cb_error_t)(struct _spi_async_dev *dev, int32_t status);

/** \brief The prototype for callback on SPI transmit/receive event
 *  For TX, the callback is invoked when transmit is done or ready to start
 *  transmit.
 *  For RX, the callback is invoked when receive is done or ready to read data,
 *  see \ref _spi_async_dev_read_one_t on data reading.
 *  Without DMA enabled, the callback is invoked on each character event.
 *  With DMA enabled, the callback is invoked on DMA buffer done.
 */
typedef void (*_spi_async_dev_cb_xfer_t)(struct _spi_async_dev *dev);

/**
 *  \brief The callbacks offered by SPI driver
 */
struct _spi_async_dev_callbacks {
	/** TX callback, see \ref _spi_async_dev_cb_xfer_t. */
	_spi_async_dev_cb_xfer_t tx;
	/** RX callback, see \ref _spi_async_dev_cb_xfer_t. */
	_spi_async_dev_cb_xfer_t rx;
	/** Complete or complete callback, see \ref _spi_async_dev_cb_complete_t. */
	_spi_async_dev_cb_xfer_t complete;
	/** Error callback, see \ref */
	_spi_async_dev_cb_error_t err;
};
//@}

/**
 *  \brief SPI async driver
 */
//@{

/** SPI driver to support async HAL */
struct _spi_async_dev {
	/** Pointer to the hardware base or private data for special device. */
	void *prvt;
	/** Data size, number of bytes for each character */
	uint8_t char_size;
	/** Dummy byte used in master mode when reading the slave */
	uint16_t dummy_byte;

	/** \brief Pointer to callback functions, ignored for polling mode
	 *  Pointer to the callback functions so that initialize the driver to
	 *  handle interrupts.
	 */
	struct _spi_async_dev_callbacks callbacks;
	/** IRQ instance for SPI device. */
	struct _irq_descriptor irq;
};
//@}

#ifdef __cplusplus
}
#endif

/**@}*/
#endif /* ifndef _HPL_SPI_ASYNC_H_INCLUDED */
