/**
 * \file
 *
 * \brief I/O related functionality declaration.
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

#ifndef _HAL_IO_INCLUDED
#define _HAL_IO_INCLUDED

/**
 * \addtogroup doc_driver_hal_helper_io I/O Driver
 *
 *@{
 */

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief I/O descriptor
 *
 * The I/O descriptor forward declaration.
 */
struct io_descriptor;

/**
 * \brief I/O write function pointer type
 */
typedef int32_t (*io_write_t)(struct io_descriptor *const io_descr, const uint8_t *const buf, const uint16_t length);

/**
 * \brief I/O read function pointer type
 */
typedef int32_t (*io_read_t)(struct io_descriptor *const io_descr, uint8_t *const buf, const uint16_t length);

/**
 * \brief I/O descriptor
 */
struct io_descriptor {
	io_write_t write; /*! The write function pointer. */
	io_read_t  read;  /*! The read function pointer. */
};

/**
 * \brief I/O write interface
 *
 * This function writes up to \p length of bytes to a given I/O descriptor.
 * It returns the number of bytes actually write.
 *
 * \param[in] descr  An I/O descriptor to write
 * \param[in] buf    The buffer pointer to story the write data
 * \param[in] length The number of bytes to write
 *
 * \return The number of bytes written
 */
int32_t io_write(struct io_descriptor *const io_descr, const uint8_t *const buf, const uint16_t length);

/**
 * \brief I/O read interface
 *
 * This function reads up to \p length bytes from a given I/O descriptor, and
 * stores it in the buffer pointed to by \p buf. It returns the number of bytes
 * actually read.
 *
 * \param[in] descr  An I/O descriptor to read
 * \param[in] buf    The buffer pointer to story the read data
 * \param[in] length The number of bytes to read
 *
 * \return The number of bytes actually read. This number can be less than the
 *         requested length. E.g., in a driver that uses ring buffer for
 *         reception, it may depend on the availability of data in the
 *         ring buffer.
 */
int32_t io_read(struct io_descriptor *const io_descr, uint8_t *const buf, const uint16_t length);

#ifdef __cplusplus
}
#endif
/**@}*/
#endif /* _HAL_IO_INCLUDED */
