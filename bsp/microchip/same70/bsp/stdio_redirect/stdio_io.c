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

#include <stdio.h>
#include <stdio_io.h>

/** IO descriptor for STDIO access. */
static struct io_descriptor *stdio_io = NULL;

void stdio_io_init(struct io_descriptor *io)
{
#if defined(__GNUC__)
	/* Specify that stdout and stdin should not be buffered. */
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	/* Note: Already the case in IAR's Normal DLIB default configuration
	 * and AVR GCC library:
	 * - printf() emits one character at a time.
	 * - getchar() requests only 1 byte to exit.
	 */
#endif
	stdio_io = io;
}

void stdio_io_set_io(struct io_descriptor *io)
{
	stdio_io = io;
}

int32_t stdio_io_read(uint8_t *buf, const int32_t len)
{
	if (stdio_io == NULL) {
		return 0;
	}
	return io_read(stdio_io, buf, len);
}

int32_t stdio_io_write(const uint8_t *buf, const int32_t len)
{
	if (stdio_io == NULL) {
		return 0;
	}
	return io_write(stdio_io, buf, len);
}
