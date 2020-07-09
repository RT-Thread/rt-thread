/**
 * \file
 *
 * \brief SPI master common service for SAM.
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

#include "spi_master.h"
#if SAMG55
#include "flexcom.h"
#include "conf_board.h"
#endif

/**
 * \brief Max number when the chip selects are connected to a 4- to 16-bit decoder.
 */
#define MAX_NUM_WITH_DECODER 0x10

/**
 * \brief Max number when the chip selects are directly connected to peripheral device.
 */
#define MAX_NUM_WITHOUT_DECODER 0x04

/**
 * \brief Max number when the chip selects are directly connected to peripheral device.
 */
#define NONE_CHIP_SELECT_ID 0x0f

/**
 * \brief The default chip select id.
 */
#define DEFAULT_CHIP_ID 0

/** \brief Initialize the SPI in master mode.
 *
 * \param p_spi  Base address of the SPI instance.
 *
 */
void spi_master_init(Spi *p_spi)
{
#if SAMG55
	flexcom_enable(BOARD_FLEXCOM_SPI);
	flexcom_set_opmode(BOARD_FLEXCOM_SPI, FLEXCOM_SPI);
#else
	spi_enable_clock(p_spi);
#endif
	spi_reset(p_spi);
	spi_set_master_mode(p_spi);
	spi_disable_mode_fault_detect(p_spi);
	spi_disable_loopback(p_spi);
	spi_set_peripheral_chip_select_value(p_spi, DEFAULT_CHIP_ID);
	spi_set_fixed_peripheral_select(p_spi);
	spi_disable_peripheral_select_decode(p_spi);
	spi_set_delay_between_chip_select(p_spi, CONFIG_SPI_MASTER_DELAY_BCS);
}

/**
 * \brief Set up an SPI device.
 *
 * The returned device descriptor structure must be passed to the driver
 * whenever that device should be used as current slave device.
 *
 * \param p_spi     Base address of the SPI instance.
 * \param device    Pointer to SPI device struct that should be initialized.
 * \param flags     SPI configuration flags. Common flags for all
 *                  implementations are the SPI modes SPI_MODE_0 ...
 *                  SPI_MODE_3.
 * \param baud_rate Baud rate for communication with slave device in Hz.
 * \param sel_id    Board specific select id.
 */
void spi_master_setup_device(Spi *p_spi, struct spi_device *device,
		spi_flags_t flags, uint32_t baud_rate, board_spi_select_id_t sel_id)
{
#if (SAM4L)
    int16_t baud_div = spi_calc_baudrate_div(baud_rate, sysclk_get_pba_hz());
#else
	int16_t baud_div = spi_calc_baudrate_div(baud_rate, sysclk_get_peripheral_hz());
#endif
	/* avoid Cppcheck Warning */
	UNUSED(sel_id);
	if (-1 == baud_div) {
		Assert(0 == "Failed to find baudrate divider");
	}
	spi_set_transfer_delay(p_spi, device->id, CONFIG_SPI_MASTER_DELAY_BS,
			CONFIG_SPI_MASTER_DELAY_BCT);
	spi_set_bits_per_transfer(p_spi, device->id,
			CONFIG_SPI_MASTER_BITS_PER_TRANSFER);
	spi_set_baudrate_div(p_spi, device->id, baud_div);
	spi_configure_cs_behavior(p_spi, device->id, SPI_CS_KEEP_LOW);
	spi_set_clock_polarity(p_spi, device->id, flags >> 1);
	spi_set_clock_phase(p_spi, device->id, ((flags & 0x1) ^ 0x1));
}

/**
 * \brief Select the given device on the SPI bus.
 *
 * Set device specific setting and call board chip select.
 *
 * \param p_spi   Base address of the SPI instance.
 * \param device  SPI device.
 *
 */
void spi_select_device(Spi *p_spi, struct spi_device *device)
{
	if (spi_get_peripheral_select_decode_setting(p_spi)) {
		if (device->id < MAX_NUM_WITH_DECODER) {
			spi_set_peripheral_chip_select_value(p_spi, device->id);
		}
	} else {
		if (device->id < MAX_NUM_WITHOUT_DECODER) {
			spi_set_peripheral_chip_select_value(p_spi, (~(1 << device->id)));
		}
	}
}

/**
 * \brief Deselect the given device on the SPI bus.
 *
 * Call board chip deselect.
 *
 * \param p_spi   Base address of the SPI instance.
 * \param device  SPI device.
 *
 * \pre SPI device must be selected with spi_select_device() first.
 */
void spi_deselect_device(Spi *p_spi, struct spi_device *device)
{
	/* avoid Cppcheck Warning */
	UNUSED(device);
	while (!spi_is_tx_empty(p_spi)) {
	}

	// Assert all lines; no peripheral is selected.
	spi_set_peripheral_chip_select_value(p_spi, NONE_CHIP_SELECT_ID);

	// Last transfer, so de-assert the current NPCS if CSAAT is set.
	spi_set_lastxfer(p_spi);

}

/**
 * \brief Send a sequence of bytes to an SPI device.
 *
 * Received bytes on the SPI bus are discarded.
 *
 * \param p_spi     Base address of the SPI instance.
 * \param data      Data buffer to write.
 * \param len       Length of data to be written.
 *
 * \pre SPI device must be selected with spi_select_device() first.
 */
status_code_t spi_write_packet(Spi *p_spi, const uint8_t *data,
		size_t len)
{
	uint32_t timeout = SPI_TIMEOUT;
	uint32_t i = 0;
	uint8_t val;

	while (len) {
		timeout = SPI_TIMEOUT;
		while (!spi_is_tx_ready(p_spi)) {
			if (!timeout--) {
				return ERR_TIMEOUT;
			}
		}
		val = data[i];
		spi_write_single(p_spi, val);
		i++;
		len--;
	}

	return STATUS_OK;
}

/**
 * \brief Receive a sequence of bytes from an SPI device.
 *
 * All bytes sent out on SPI bus are sent as value 0.
 *
 * \param p_spi     Base address of the SPI instance.
 * \param data      Data buffer to read.
 * \param len       Length of data to be read.
 *
 * \pre SPI device must be selected with spi_select_device() first.
 */
status_code_t spi_read_packet(Spi *p_spi, uint8_t *data, size_t len)
{
	uint32_t timeout = SPI_TIMEOUT;
	uint8_t val;
	uint32_t i = 0;

	while (len) {
		timeout = SPI_TIMEOUT;
		while (!spi_is_tx_ready(p_spi)) {
			if (!timeout--) {
				return ERR_TIMEOUT;
			}
		}
		spi_write_single(p_spi, CONFIG_SPI_MASTER_DUMMY);

		timeout = SPI_TIMEOUT;
		while (!spi_is_rx_ready(p_spi)) {
			if (!timeout--) {
				return ERR_TIMEOUT;
			}
		}
		spi_read_single(p_spi, &val);

		data[i] = val;
		i++;
		len--;
	}

	return STATUS_OK;
}

/**
 * \brief Send and receive a sequence of bytes from an SPI device.
 *
 * \param p_spi     Base address of the SPI instance.
 * \param tx_data   Data buffer to send.
 * \param rx_data   Data buffer to read.
 * \param len       Length of data to be read.
 *
 * \pre SPI device must be selected with spi_select_device() first.
 */
status_code_t spi_transceive_packet(Spi *p_spi, uint8_t *tx_data, uint8_t *rx_data, size_t len)
{
	uint32_t timeout = SPI_TIMEOUT;
	uint8_t val;
	uint32_t i = 0;

	while (len) {
		timeout = SPI_TIMEOUT;
		while (!spi_is_tx_ready(p_spi)) {
			if (!timeout--) {
				return ERR_TIMEOUT;
			}
		}
		spi_write_single(p_spi, tx_data[i]);

		timeout = SPI_TIMEOUT;
		while (!spi_is_rx_ready(p_spi)) {
			if (!timeout--) {
				return ERR_TIMEOUT;
			}
		}
		spi_read_single(p_spi, &val);

		rx_data[i] = val;
		i++;
		len--;
	}

	return STATUS_OK;
}
//! @}
