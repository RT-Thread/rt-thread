/**
 * \file
 *
 * \brief USART in SPI mode driver functions.
 *
 * Copyright (c) 2010-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#ifndef USART_SPI_H_INCLUDED
#define USART_SPI_H_INCLUDED

#include <parts.h>

#if XMEGA
# include "xmega_usart_spi/usart_spi.h"
#elif MEGA_RF
# include "megarf_usart_spi/usart_spi.h"
#elif UC3
# include "uc3_usart_spi/usart_spi.h"
#elif SAM
# include "sam_usart_spi/usart_spi.h"
#else
# error Unsupported chip type
#endif

/**
 *
 * \defgroup usart_spi_group USART in SPI (Serial Peripheral Interface) mode
 *
 * This is the common API for USART in SPI mode. Additional features are available
 * in the documentation of the specific modules.
 *
 * \section spi_group_platform Platform Dependencies
 *
 * The spi API is partially chip- or platform-specific. While all
 * platforms provide mostly the same functionality, there are some
 * variations around how different bus types and clock tree structures
 * are handled.
 *
 * The following functions are available on all platforms, but there may
 * be variations in the function signature (i.e. parameters) and
 * behaviour. These functions are typically called by platform-specific
 * parts of drivers, and applications that aren't intended to be
 * portable:
 *   - usart_spi_init()
 *   - usart_spi_setup_device()
 *   - usart_spi_select_device()
 *   - usart_spi_deselect_device()
 *   - usart_spi_write_single()
 *   - usart_spi_write_packet()
 *   - usart_spi_read_single()
 *   - usart_spi_read_packet()
 *   - usart_spi_is_tx_empty()
 *   - usart_spi_is_tx_ready()
 *   - usart_spi_is_rx_full()
 *   - usart_spi_is_rx_ready()
 *   - usart_spi_enable()
 *   - usart_spi_disable()
 *   - usart_spi_is_enabled()
 *
 *
 * @{
 */

//! @}

#endif /* USART_SPI_H_INCLUDED */
