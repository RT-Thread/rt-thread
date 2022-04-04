/**
 * \file
 *
 * \brief STDIO redirection terminal
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

#ifndef _STDIO_IO_H_INCLUDED
#define _STDIO_IO_H_INCLUDED

#include <hal_io.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 *  \brief Initialize STDIO access
 *  \param[in] io Pointer to IO descriptor,
 *                NULL to discard R/W without any error.
 */
void stdio_io_init(struct io_descriptor *io);

/**
 *  \brief Change IO descriptor for terminal to R/W data
 *  \param[in] io Pointer to IO descriptor,
 *                NULL to discard R/W without any error.
 */
void stdio_io_set_io(struct io_descriptor *io);

/**
 *  \brief Read through specified terminal
 *  \param[out] buf Pointer to buffer to place read data
 *  \param[in] len Data length in number of bytes
 *  \return status
 *  \retval >=0 number of bytes read
 *  \retval <0 error
 */
int32_t stdio_io_read(uint8_t *buf, const int32_t len);

/**
 *  \brief Write through specified terminal
 *  \param[in] buf Pointer to buffer to place data to write
 *  \param[in] len Data length in number of bytes
 *  \return status
 *  \retval >=0 number of bytes read
 *  \retval <0 error
 */
int32_t stdio_io_write(const uint8_t *buf, const int32_t len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _STDIO_IO_H_INCLUDED */
