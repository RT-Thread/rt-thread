/**
 * \file
 *
 * \brief SPI related functionality declaration.
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

#ifndef _HPL_SPI_S_SYNC_H_INCLUDED
#define _HPL_SPI_S_SYNC_H_INCLUDED

#include <hpl_spi_sync.h>

/**
 * \addtogroup hpl_spi HPL SPI
 *
 *@{
 */

#ifdef __cplusplus
extern "C" {
#endif

/** Uses common SPI sync device driver. */
#define _spi_s_sync_dev _spi_sync_dev

/**
 * \name HPL functions
 */
//@{
/**
 *  \brief Initialize SPI for access without interrupts
 *  It will load default hardware configuration and software struct.
 *  \param[in, out] dev Pointer to the SPI device instance.
 *  \param[in] hw Pointer to the hardware base.
 *  \return Operation status.
 *  \retval ERR_INVALID_ARG Input parameter problem.
 *  \retval ERR_BUSY SPI hardware not ready (resetting).
 *  \retval ERR_DENIED SPI has been enabled.
 *  \retval 0 Operation done successfully.
 */
int32_t _spi_s_sync_init(struct _spi_s_sync_dev *dev, void *const hw);

/**
 *  \brief Initialize SPI for access with interrupts
 *  Disable, reset the hardware and the software struct.
 *  \param[in, out] dev Pointer to the SPI device instance.
 *  \return Operation status.
 *  \retval 0 Operation done successfully.
 */
int32_t _spi_s_sync_deinit(struct _spi_s_sync_dev *dev);

/**
 *  \brief Enable SPI for access without interrupts
 *  \param[in, out] dev Pointer to the SPI device instance.
 *  \return Operation status.
 *  \retval ERR_BUSY SPI hardware not ready (resetting).
 *  \retval 0 Operation done successfully.
 */
int32_t _spi_s_sync_enable(struct _spi_s_sync_dev *dev);

/**
 *  \brief Disable SPI for access without interrupts
 *  Disable SPI. Deactivate all CS pins if works as master.
 *  \param[in, out] dev Pointer to the SPI device instance.
 *  \return Operation status.
 *  \retval 0 Operation done successfully.
 */
int32_t _spi_s_sync_disable(struct _spi_s_sync_dev *dev);

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
int32_t _spi_s_sync_set_mode(struct _spi_s_sync_dev *dev, const enum spi_transfer_mode mode);

/**
 *  \brief Set SPI baudrate
 *  \param[in, out] dev Pointer to the SPI device instance.
 *  \param[in] char_size The character size, see \ref spi_char_size.
 *  \return Operation status.
 *  \retval ERR_INVALID_ARG The character size is not supported.
 *  \retval ERR_BUSY SPI is not ready to accept new setting.
 *  \retval 0 Operation done successfully.
 */
int32_t _spi_s_sync_set_char_size(struct _spi_s_sync_dev *dev, const enum spi_char_size char_size);

/**
 *  \brief Set SPI data order
 *  \param[in, out] dev Pointer to the SPI device instance.
 *  \param[in] dord SPI data order (LSB/MSB first).
 *  \return Operation status.
 *  \retval ERR_INVALID_ARG The character size is not supported.
 *  \retval ERR_BUSY SPI is not ready to accept new setting.
 *  \retval 0 Operation done successfully.
 */
int32_t _spi_s_sync_set_data_order(struct _spi_s_sync_dev *dev, const enum spi_data_order dord);

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
int32_t _spi_s_sync_enable_tx(struct _spi_s_sync_dev *dev, bool state);

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
 * \retval 0 OK Status
 */
int32_t _spi_s_sync_enable_rx(struct _spi_s_sync_dev *dev, bool state);

/**
 *  \brief Read one character to SPI device instance
 *  \param[in, out] dev Pointer to the SPI device instance.
 *
 *  \return Character read from SPI module
 */
uint16_t _spi_s_sync_read_one(struct _spi_s_sync_dev *dev);

/**
 *  \brief Write one character to assigned buffer
 *  \param[in, out] dev Pointer to the SPI device instance.
 *  \param[in] data
 *
 *  \return Status code of write operation
 *  \retval 0 Write operation OK
 */
int32_t _spi_s_sync_write_one(struct _spi_s_sync_dev *dev, uint16_t data);

/**
 * \brief Check if TX ready
 *
 * \param[in] dev  Pointer to the SPI device instance
 *
 * \return TX ready state
 * \retval true TX ready
 * \retval false TX not ready
 */
bool _spi_s_sync_is_tx_ready(struct _spi_s_sync_dev *dev);

/**
 * \brief Check if RX character ready
 *
 * \param[in] dev  Pointer to the SPI device instance
 *
 * \return RX character ready state
 * \retval true RX character ready
 * \retval false RX character not ready
 */
bool _spi_s_sync_is_rx_ready(struct _spi_s_sync_dev *dev);

/**
 * \brief Check if SS deactiviation detected
 *
 * \param[in] dev  Pointer to the SPI device instance
 *
 * \return SS deactiviation state
 * \retval true SS deactiviation detected
 * \retval false SS deactiviation not detected
 */
bool _spi_s_sync_is_ss_deactivated(struct _spi_s_sync_dev *dev);

/**
 * \brief Check if error is detected
 *
 * \param[in] dev  Pointer to the SPI device instance
 *
 * \return Error detection state
 * \retval true Error detected
 * \retval false Error not detected
 */
bool _spi_s_sync_is_error(struct _spi_s_sync_dev *dev);
//@}

#ifdef __cplusplus
}
#endif

/**@}*/
#endif /* ifndef _HPL_SPI_S_SYNC_H_INCLUDED */
