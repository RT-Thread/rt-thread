/**
 * \file
 *
 * \brief SPI Slave Async related functionality declaration.
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

#ifndef _HPL_SPI_S_ASYNC_H_INCLUDED
#define _HPL_SPI_S_ASYNC_H_INCLUDED

#include <hpl_spi_async.h>

/**
 * \addtogroup hpl_spi HPL SPI
 *
 *
 *@{
 */

#ifdef __cplusplus
extern "C" {
#endif

/** Uses common SPI async device driver. */
#define _spi_s_async_dev _spi_async_dev

#define _spi_s_async_dev_cb_type _spi_async_dev_cb_type

/** Uses common SPI async device driver complete callback type. */
#define _spi_m_async_dev_cb_error_t _spi_async_dev_cb_error_t

/** Uses common SPI async device driver transfer callback type. */
#define _spi_s_async_dev_cb_xfer_t _spi_async_dev_cb_xfer_t

/**
 * \name HPL functions
 */
//@{
/**
 *  \brief Initialize SPI for access with interrupts
 *  It will load default hardware configuration and software struct.
 *  \param[in, out] dev Pointer to the SPI device instance.
 *  \param[in] hw Pointer to the hardware base.
 *  \return Operation status.
 *  \retval ERR_INVALID_ARG Input parameter problem.
 *  \retval ERR_BUSY SPI hardware not ready (resetting).
 *  \retval ERR_DENIED SPI has been enabled.
 *  \retval 0 Operation done successfully.
 */
int32_t _spi_s_async_init(struct _spi_s_async_dev *dev, void *const hw);

/**
 *  \brief Initialize SPI for access with interrupts
 *  Disable, reset the hardware and the software struct.
 *  \param[in, out] dev Pointer to the SPI device instance.
 *  \return Operation status.
 *  \retval 0 Operation done successfully.
 */
int32_t _spi_s_async_deinit(struct _spi_s_async_dev *dev);

/**
 *  \brief Enable SPI for access with interrupts
 *  Enable the SPI and enable callback generation of receive and error
 *  interrupts.
 *  \param[in, out] dev Pointer to the SPI device instance.
 *  \return Operation status.
 *  \retval ERR_INVALID_ARG Input parameter problem.
 *  \retval ERR_BUSY SPI hardware not ready (resetting).
 *  \retval 0 Operation done successfully.
 */
int32_t _spi_s_async_enable(struct _spi_s_async_dev *dev);

/**
 *  \brief Disable SPI for access without interrupts
 *  Disable SPI and interrupts. Deactivate all CS pins if works as master.
 *  \param[in, out] dev Pointer to the SPI device instance.
 *  \return Operation status.
 *  \retval 0 Operation done successfully.
 */
int32_t _spi_s_async_disable(struct _spi_s_async_dev *dev);

/**
 *  \brief Set SPI transfer mode
 *  Set SPI transfer mode (\ref spi_transfer_mode),
 *  which controls clock polarity and clock phase.
 *  Mode 0: leading edge is rising edge, data sample on leading edge.
 *  Mode 1: leading edge is rising edge, data sample on trailing edge.
 *  Mode 2: leading edge is falling edge, data sample on leading edge.
 *  Mode 3: leading edge is falling edge, data sample on trailing edge.
 *  \param[in, out] dev Pointer to the SPI device instance.
 *  \param[in] mode The SPI transfer mode.
 *  \return Operation status.
 *  \retval ERR_BUSY SPI is not ready to accept new setting.
 *  \retval 0 Operation done successfully.
 */
int32_t _spi_s_async_set_mode(struct _spi_s_async_dev *dev, const enum spi_transfer_mode mode);

/**
 *  \brief Set SPI baudrate
 *  \param[in, out] dev Pointer to the SPI device instance.
 *  \param[in] char_size The character size, see \ref spi_char_size.
 *  \return Operation status.
 *  \retval ERR_INVALID_ARG The character size is not supported.
 *  \retval ERR_BUSY SPI is not ready to accept new setting.
 *  \retval 0 Operation done successfully.
 */
int32_t _spi_s_async_set_char_size(struct _spi_s_async_dev *dev, const enum spi_char_size char_size);

/**
 *  \brief Set SPI data order
 *  \param[in, out] dev Pointer to the SPI device instance.
 *  \param[in] dord SPI data order (LSB/MSB first).
 *  \return Operation status.
 *  \retval ERR_INVALID_ARG The character size is not supported.
 *  \retval ERR_BUSY SPI is not ready to accept new setting.
 *  \retval 0 Operation done successfully.
 */
int32_t _spi_s_async_set_data_order(struct _spi_s_async_dev *dev, const enum spi_data_order dord);

/**
 * \brief Enable interrupt on character output
 *
 * Enable interrupt when a new character can be written
 * to the SPI device.
 *
 * \param[in] dev   Pointer to the SPI device instance
 * \param[in] state true  = enable output interrupt
 *                  false = disable output interrupt
 *
 * \return Status code
 * \retval 0 Ok status
 */
int32_t _spi_s_async_enable_tx(struct _spi_s_async_dev *dev, bool state);

/**
 * \brief Enable interrupt on character input
 *
 * Enable interrupt when a new character is ready to be
 * read from the SPI device.
 *
 * \param[in] dev  Pointer to the SPI device instance
 * \param[in] state true  = enable input interrupts
 *                  false = disable input interrupt
 *
 * \return Status code
 * \retvat 0 OK Status
 */
int32_t _spi_s_async_enable_rx(struct _spi_s_async_dev *dev, bool state);

/**
 * \brief Enable interrupt on Slave Select (SS) rising
 *
 * \param[in] dev  Pointer to the SPI device instance
 * \param[in] state true  = enable input interrupts
 *                  false = disable input interrupt
 *
 * \return Status code
 * \retvat 0 OK Status
 */
int32_t _spi_s_async_enable_ss_detect(struct _spi_s_async_dev *dev, bool state);

/**
 *  \brief Read one character to SPI device instance
 *  \param[in, out] dev Pointer to the SPI device instance.
 *
 *  \return Character read from SPI module
 */
uint16_t _spi_s_async_read_one(struct _spi_s_async_dev *dev);

/**
 *  \brief Write one character to assigned buffer
 *  \param[in, out] dev Pointer to the SPI device instance.
 *  \param[in] data
 *
 *  \return Status code of write operation
 *  \retval 0 Write operation OK
 */
int32_t _spi_s_async_write_one(struct _spi_s_async_dev *dev, uint16_t data);

/**
 *  \brief Register the SPI device callback
 *  \param[in, out] dev Pointer to the SPI device instance.
 *  \param[in] cb_type The callback type.
 *  \param[in] func The callback function to register. NULL to disable callback.
 *  \return Always 0.
 */
int32_t _spi_s_async_register_callback(struct _spi_s_async_dev *dev, const enum _spi_s_async_dev_cb_type cb_type,
                                       const FUNC_PTR func);

/**
 * \brief Enable/disable SPI slave interrupt
 *
 * param[in] device The pointer to SPI slave device instance
 * param[in] type The type of interrupt to disable/enable if applicable
 * param[in] state Enable or disable
 */
void _spi_s_async_set_irq_state(struct _spi_s_async_dev *const device, const enum _spi_async_dev_cb_type type,
                                const bool state);
//@}

#ifdef __cplusplus
}
#endif

/**@}*/
#endif /* ifndef _HPL_SPI_S_ASYNC_H_INCLUDED */
