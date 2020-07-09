/**
 * \file
 *
 * \brief SAM USART in SPI mode driver functions.
 *
 * Copyright (c) 2011-2016 Atmel Corporation. All rights reserved.
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

#include "usart_spi.h"
#include "sysclk.h"
#if SAMG55
#include "flexcom.h"
#include "conf_board.h"
#endif

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/*! \brief Enable the USART system clock in SPI master mode.
 *
 * \param p_usart Pointer to Base address of the USART instance.
 *
 */
void usart_spi_init(Usart *p_usart)
{
#if (!SAMG55)

	uint8_t uc_id;

#ifdef USART0
	if (p_usart == USART0) {
		uc_id = ID_USART0;
	}
#endif

#ifdef USART1
	else if(p_usart == USART1) {
		uc_id = ID_USART1;
	}
#endif

#ifdef USART2
	else if(p_usart == USART2) {
		uc_id = ID_USART2;
	}
#endif

#ifdef USART3
	else if(p_usart == USART3) {
		uc_id = ID_USART3;
	}
#endif

#endif

#if SAM4L
	sysclk_enable_peripheral_clock(p_usart);
#elif SAMG55
	flexcom_enable(BOARD_FLEXCOM_USART);
	flexcom_set_opmode(BOARD_FLEXCOM_USART, FLEXCOM_USART);
#else
	sysclk_enable_peripheral_clock(uc_id);
#endif
}

/**
 * \brief Set up a USART in SPI master mode device.
 *
 * The returned device descriptor structure must be passed to the driver
 * whenever that device should be used as current slave device.
 *
 * \param p_usart   Base address of the USART instance.
 * \param device    Pointer to usart device struct that should be initialized.
 * \param flags     USART configuration flags. Common flags for all
 *                  implementations are the usart modes, which should be SPI_MODE_0,
 *                  SPI_MODE_1, SPI_MODE_2, SPI_MODE_3.
 * \param baud_rate Baud rate for communication with slave device in Hz.
 * \param sel_id    Board specific select id.
 */
void usart_spi_setup_device(Usart *p_usart, struct usart_spi_device *device, 
     spi_flags_t flags, unsigned long baud_rate,
     board_spi_select_id_t sel_id)
{
	usart_spi_opt_t opt;

	/* avoid Cppcheck Warning */
	UNUSED(device);
	UNUSED(sel_id);

	/* Basic usart SPI configuration. */
	opt.baudrate = baud_rate;
	opt.char_length = US_MR_CHRL_8_BIT;
	opt.spi_mode = flags;
	opt.channel_mode = US_MR_CHMODE_NORMAL;
	
	/* Initialize the USART module as SPI master. */
#if (SAM4L)
	usart_init_spi_master(p_usart, &opt, sysclk_get_pba_hz());
#else
	usart_init_spi_master(p_usart, &opt, sysclk_get_peripheral_hz());
#endif

	usart_enable_rx(p_usart);
	usart_enable_tx(p_usart);
}

/*! \brief Write one byte to an SPI device using USART in SPI mode.
 *
 * \param p_usart Base address of the USART instance.
 * \param data    The data to be sent out. 
 *
 */
void usart_spi_write_single(Usart *p_usart, uint8_t data)
{
	usart_putchar(p_usart, data);
}

/**
 * \brief Send a sequence of bytes to an SPI device using USART in SPI mode.
 *
 * Received bytes on the USART in SPI mode are discarded.
 *
 * \param p_usart Base address of the USART instance.
 * \param data    Data buffer to write.
 * \param len     Length of data.
 *
 * \return 0 if the USART in SPI master mode sends packet successfully.
 *
 * \pre USART device must be selected with usart_spi_select_device() first.
 */
uint32_t usart_spi_write_packet(Usart *p_usart, const uint8_t *data, size_t len)
{
	uint32_t dummy_data;
	size_t i=0;
	while(len) {
		usart_putchar(p_usart, *(data+i));
		usart_getchar(p_usart, &dummy_data);
		len--;
		i++;
	}
	return 0;
}

/*! \brief Receive one byte from an SPI device using USART in SPI mode.
 *
 * \param p_usart Base address of the USART instance.
 * \param data    Pointer to the data byte where to store the received data.
 *
 * \pre USART device must be selected with usart_spi_select_device() first.
 */
void usart_spi_read_single(Usart *p_usart, uint8_t *data)
{
	uint32_t temp_data = 0;
	/* Dummy write one data to slave in order to read data. */
	usart_putchar(p_usart, CONFIG_USART_SPI_DUMMY);

	usart_getchar(p_usart, &temp_data);
	*data = (uint8_t)temp_data;
}

/**
 * \brief Receive a sequence of bytes from a USART in SPI mode device.
 *
 * All bytes sent out on usart bus are sent as value 0.
 *
 * \param p_usart Base address of the usart instance.
 * \param data    Data buffer to put read data.
 * \param len     Length of data.
 *
 * \return 0 if the USART in SPI master mode reads packet successfully.
 *
 * \pre USART device must be selected with usart_spi_select_device() first.
 */
uint32_t usart_spi_read_packet(Usart *p_usart, uint8_t *data, size_t len)
{
	uint32_t val;
	uint32_t i = 0;

	while(len) {
		/* Dummy write one data to slave in order to read data. */
		usart_putchar(p_usart, CONFIG_USART_SPI_DUMMY);
		usart_getchar(p_usart, &val);

		data[i] = (uint8_t)(val & 0xFF);
		i++;
		len--;
	}
	
	return 0;
}

/**
 * \brief Select the given device on the SPI bus.
 *
 * \param p_usart  Base address of the USART instance.
 * \param device   SPI device.
 *
 */
void usart_spi_select_device(Usart *p_usart, struct usart_spi_device *device)
{
	/* avoid Cppcheck Warning */
	UNUSED(device);
	
	usart_spi_force_chip_select(p_usart);
}

/**
 * \brief De-select the given device on the SPI bus.
 *
 * \param p_usart Base address of the USART instance.
 * \param device  SPI device.
 */
void usart_spi_deselect_device(Usart *p_usart, struct usart_spi_device *device)
{
	/* avoid Cppcheck Warning */
	UNUSED(device);
	
	usart_spi_release_chip_select(p_usart);
}

/*! \brief Check whether there are data in Transmit Holding Register or
 *         Transmit Shift Register in SPI master mode.
 *
 * \param p_usart Base address of the USART instance.
 *
 * \retval 1      The two registers are empty.
 * \retval 0      One of the two registers contains data.
 */
uint32_t usart_spi_is_tx_empty(Usart *p_usart)
{
	return usart_is_tx_empty(p_usart);
}

/*! \brief Check whether the USART in SPI master mode contains a received character.
 *
 * \param p_usart Base address of the USART instance.
 *
 * \retval 1      Some data have been received.
 * \retval 0      No data has been received.
 */
uint32_t usart_spi_is_rx_ready(Usart *p_usart)
{
	return usart_is_rx_ready(p_usart);
}

/*! \brief Check if the USART Transmit Holding Register is empty or not in SPI mode.
 *
 * \param p_usart Base address of the USART instance.
 *
 * \retval 1      There is no data in the Transmit Holding Register.
 * \retval 0      There are data in the Transmit Holding Register.
 */
uint32_t usart_spi_is_tx_ready(Usart *p_usart)
{
	return usart_is_tx_ready(p_usart);
}

/*! \brief Check if both receive buffers are full.
 *
 * \param p_usart Base address of the USART instance.
 *
 * \retval 1      Receive buffers are full.
 * \retval 0      Receive buffers are not full.
 */
uint32_t usart_spi_is_rx_full(Usart *p_usart)
{
#if (!SAMV71 && !SAMV70 && !SAME70 && !SAMS70)
	return usart_is_rx_buf_full(p_usart);
#endif
}

/*! \brief Enable the USART for the specified USART in SPI mode.
 *
 * \param p_usart Base address of the USART instance.
 */
void usart_spi_enable(Usart *p_usart)
{
	usart_enable_tx(p_usart);
	usart_enable_rx(p_usart);
}

/*! \brief Disable the USART for the specified USART in SPI mode.
 *
 * Ensure that nothing is transferred while setting up buffers.
 *
 * \param p_usart Base address of the USART instance.
 *
 */
void usart_spi_disable(Usart *p_usart)
{
	usart_disable_tx(p_usart);
	usart_disable_rx(p_usart);
}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
