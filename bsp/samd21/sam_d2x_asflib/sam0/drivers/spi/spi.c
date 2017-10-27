/**
 * \file
 *
 * \brief Serial Peripheral Interface Driver for SAMB11
 *
 * Copyright (C) 2015-2016 Atmel Corporation. All rights reserved.
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
#include "spi.h"

/**
 * \brief Determines if the SPI module is currently synchronizing to the bus.
 *
 * This function will check if the underlying hardware peripheral module is
 * currently synchronizing across multiple clock domains to the hardware bus.
 * This function can be used to delay further operations on the module until it
 * is ready.
 *
 * \param[in]  module  SPI hardware module
 *
 * \return Synchronization status of the underlying hardware module
 * \retval true   Module synchronization is ongoing
 * \retval false  Module synchronization is not ongoing
 *
 */
static bool _spi_is_active(Spi *const spi_module)
{
	Assert(spi_module);

	return spi_module->SPI_BUS_STATUS.bit.SPI_ACTIVE;
}

/**
 * \internal Enable SPI clock.
 *
 * This function will enable SPI clock.
 *
 * \param[in]  module  Pointer to the software instance struct
 */
static void _spi_clock_enable(struct spi_module *const module)
{
	Assert(module);

	Spi *const spi_module = (module->hw);

	if (spi_module == (void *)SPI0) {
		system_clock_peripheral_enable(PERIPHERAL_SPI0_SCK_CLK);
		system_clock_peripheral_enable(PERIPHERAL_SPI0_SCK_PHASE);
		system_clock_peripheral_enable(PERIPHERAL_SPI0_IF);
		system_clock_peripheral_enable(PERIPHERAL_SPI0_CORE);
	} else if (spi_module == (void *)SPI1) {
		system_clock_peripheral_enable(PERIPHERAL_SPI1_SCK_CLK);
		system_clock_peripheral_enable(PERIPHERAL_SPI1_SCK_PHASE);
		system_clock_peripheral_enable(PERIPHERAL_SPI1_IF);
		system_clock_peripheral_enable(PERIPHERAL_SPI1_CORE);
	}
}

/**
 * \internal Disable SPI clock.
 *
 * This function will disable SPI clock.
 *
 * \param[in]  module  Pointer to the software instance struct
 */
static void _spi_clock_disable(struct spi_module *const module)
{
	Assert(module);

	Spi *const spi_module = (module->hw);

	if (spi_module == (void *)SPI0) {
		system_clock_peripheral_disable(PERIPHERAL_SPI0_SCK_CLK);
		system_clock_peripheral_disable(PERIPHERAL_SPI0_SCK_PHASE);
		system_clock_peripheral_disable(PERIPHERAL_SPI0_IF);
		system_clock_peripheral_disable(PERIPHERAL_SPI0_CORE);
	} else if (spi_module == (void *)SPI1) {
		system_clock_peripheral_disable(PERIPHERAL_SPI1_SCK_CLK);
		system_clock_peripheral_disable(PERIPHERAL_SPI1_SCK_PHASE);
		system_clock_peripheral_disable(PERIPHERAL_SPI1_IF);
		system_clock_peripheral_disable(PERIPHERAL_SPI1_CORE);
	}
}

/**
 * \internal Writes an SPI configuration to the hardware module.
 *
 * This function will write out a given configuration to the hardware module.
 * Can only be done when the module is disabled.
 *
 * \param[in]  module  Pointer to the software instance struct
 * \param[in]  config  Pointer to the configuration struct
 *
 * \return The status of the configuration
 * \retval STATUS_ERR_INVALID_ARG  If invalid argument(s) were provided
 * \retval STATUS_OK               If the configuration was written
 */
static enum status_code _spi_set_config(
		struct spi_module *const module,
		const struct spi_config *const config)
{
	Assert(module);
	Assert(config);

	Spi *const spi_module = (module->hw);

	module->mode  = config->mode;

#if CONF_SPI_MASTER_ENABLE == true
	/* Find baud value and write it */
	if (config->mode == SPI_MODE_MASTER) {
		spi_module->SPI_CLK_DIVIDER.reg = config->clock_divider;
	}
#endif

	/* Set data order */
	if (config->data_order == SPI_DATA_ORDER_LSB) {
		spi_module->SPI_CONFIGURATION.bit.LSB_FIRST_ENABLE = 0x1;
	} else {
		spi_module->SPI_CONFIGURATION.bit.LSB_FIRST_ENABLE = 0x0;
	}

	/* Set clock polarity and clock phase */
	switch(config->transfer_mode)
	{
		case SPI_TRANSFER_MODE_0:
			spi_module->SPI_CONFIGURATION.bit.SCK_PHASE = 0x0;
			spi_module->SPI_CONFIGURATION.bit.SCK_POLARITY = 0x0;
			break;
		case SPI_TRANSFER_MODE_1:
			spi_module->SPI_CONFIGURATION.bit.SCK_PHASE = 0x1;
			spi_module->SPI_CONFIGURATION.bit.SCK_POLARITY = 0x0;
			break;
		case SPI_TRANSFER_MODE_2:
			spi_module->SPI_CONFIGURATION.bit.SCK_PHASE = 0x0;
			spi_module->SPI_CONFIGURATION.bit.SCK_POLARITY = 0x1;
			break;
		case SPI_TRANSFER_MODE_3:
			spi_module->SPI_CONFIGURATION.bit.SCK_PHASE = 0x1;
			spi_module->SPI_CONFIGURATION.bit.SCK_POLARITY = 0x1;
			break;
		default:
			break;
	}

	return STATUS_OK;
}

/**
 * \brief Checks if the SPI in master mode has shifted out last data, or if the
 * master has ended the transfer in slave mode.
 *
 * This function will check if the SPI master module has shifted out last data,
 * or if the slave select pin has been drawn high by the master for the SPI
 * slave module.
 *
 * \param[in]  module  Pointer to the software instance struct
 *
 * \return Indication of whether any writes are ongoing
 * \retval true   If the SPI master module has shifted out data, or slave select
 *                has been drawn high for SPI slave
 * \retval false  If the SPI master module has not shifted out data
 */
static inline bool _spi_is_write_complete(
		Spi *const spi_module)
{
	Assert(spi_module);

	/* Check interrupt flag */
	return (spi_module->TRANSMIT_STATUS.bit.TX_FIFO_EMPTY);
}


 /**
 * \brief Checks if the SPI module is ready to write data
 *
 * This function will check if the SPI module is ready to write data.
 *
 * \param[in]  module  Pointer to the software instance struct
 *
 * \return Indication of whether the module is ready to read data or not
 * \retval true   If the SPI module is ready to write data
 * \retval false  If the SPI module is not ready to write data
 */
static inline bool _spi_is_ready_to_write(
		Spi *const spi_module)
{
	Assert(spi_module);

	/* Check interrupt flag */
	return (spi_module->TRANSMIT_STATUS.bit.TX_FIFO_NOT_FULL);
}

/**
 * \brief Checks if the SPI module is ready to read data
 *
 * This function will check if the SPI module is ready to read data.
 *
 * \param[in]  module Pointer to the software instance struct
 *
 * \return Indication of whether the module is ready to read data or not
 * \retval true   If the SPI module is ready to read data
 * \retval false  If the SPI module is not ready to read data
 */
static inline bool _spi_is_ready_to_read(
		Spi *const spi_module)
{
	Assert(spi_module);

	/* Check interrupt flag */
	return (spi_module->RECEIVE_STATUS.bit.RX_FIFO_NOT_EMPTY);
}

/**
 * \brief Initializes an SPI peripheral slave device configuration structure to default values
 *
 * This function will initialize a given SPI slave device configuration
 * structure to a set of known default values. This function should be called
 * on any new instance of the configuration structures before being modified by
 * the user application.
 *
 * The default configuration is as follows:
 *  \li Slave Select on GPIO pin 12
 *  \li Addressing not enabled
 *
 * \param[out] config  Configuration structure to initialize to default values
 */
void spi_slave_inst_get_config_defaults(
		struct spi_slave_inst_config *const config)
{
	Assert(config);

	config->ss_pin          = PIN_LP_GPIO_12;
	config->address_enabled = false;
	config->address         = 0;
}

/**
 * \brief Initializes an SPI configuration structure to default values
 *
 * This function will initialize a given SPI configuration structure to a set
 * of known default values. This function should be called on any new
 * instance of the configuration structures before being modified by the
 * user application.
 *
 * The default configuration is as follows:
 *  \li Master mode enabled
 *  \li MSB of the data is transmitted first
 *  \li Transfer mode 0
 *  \li MUX Setting 0
 *  \li Character size 8 bit
 *  \li Not enabled in sleep mode
 *  \li Receiver enabled
 *  \li Baudrate 50000
 *  \li Default pinmux settings for all pads
 *  \li Clock source 0 (26MHz)
 *  \li	Clock divider  (Formula: baud_rate = ((clock input freq/clock_divider+1)/2))
 *                                  (For Example: if clock source is CLOCK_INPUT_0 then
 *                                  ((26000000/(129+1))/2) = 100000 bps)
 *
 * \param[in,out] config  Configuration structure to initialize to default values
 */
void spi_get_config_defaults(
		struct spi_config *const config)
{
	Assert(config);

	config->mode             = SPI_MODE_MASTER;
	config->data_order       = SPI_DATA_ORDER_MSB;
	config->transfer_mode    = SPI_TRANSFER_MODE_0;
	config->clock_source     = SPI_CLK_INPUT_0;
	config->clock_divider    = 129;

	config->pin_number_pad[0] = PIN_LP_GPIO_10;
	config->pin_number_pad[1] = PIN_LP_GPIO_11;
	config->pin_number_pad[2] = PIN_LP_GPIO_12;
	config->pin_number_pad[3] = PIN_LP_GPIO_13;

	config->pinmux_sel_pad[0] = MUX_LP_GPIO_10_SPI0_SCK;
	config->pinmux_sel_pad[1] = MUX_LP_GPIO_11_SPI0_MOSI;
	config->pinmux_sel_pad[2] = MUX_LP_GPIO_12_SPI0_SSN;
	config->pinmux_sel_pad[3] = MUX_LP_GPIO_13_SPI0_MISO;
};

/**
 * \brief Attaches an SPI peripheral slave
 *
 * This function will initialize the software SPI peripheral slave, based on
 * the values of the config struct. The slave can then be selected and
 * optionally addressed by the \ref spi_select_slave function.
 *
 * \param[out] slave   Pointer to the software slave instance struct
 * \param[in]  config  Pointer to the config struct
 *
 */
void spi_attach_slave(
		struct spi_slave_inst *const slave,
		struct spi_slave_inst_config *const config)
{
	Assert(slave);
	Assert(config);

	slave->ss_pin          = config->ss_pin;
	slave->address_enabled = config->address_enabled;
	slave->address         = config->address;

	struct gpio_config config_gpio;
	gpio_get_config_defaults(&config_gpio);
	config_gpio.direction = GPIO_PIN_DIR_OUTPUT;
	gpio_pin_set_config(slave->ss_pin, &config_gpio);

	gpio_pin_set_output_level(slave->ss_pin, true);
}

/**
 * \brief Resets the SPI module
 *
 * This function will reset the SPI module to its power on default values and
 * disable it.
 *
 * \param[in,out] module Pointer to the software instance struct
 */
void spi_reset(struct spi_module *const module)
{
	/* Sanity check arguments */
	Spi *const spi_module = (module->hw);

	/* Disable the module */
	spi_disable(module);

	/* Software reset the module */
	if(spi_module == (void *)SPI0) {
		system_peripheral_reset(PERIPHERAL_SPI0_CORE);
		system_peripheral_reset(PERIPHERAL_SPI0_IF);
	} else if (spi_module == (void *)SPI1) {
		system_peripheral_reset(PERIPHERAL_SPI1_CORE);
		system_peripheral_reset(PERIPHERAL_SPI1_IF);
	}
}

/**
 * \brief Initializes the SPI module
 *
 * This function will initialize the SPI module, based on the values
 * of the config struct.
 *
 * \param[out]  module  Pointer to the software instance struct
 * \param[in]   hw      Pointer to hardware instance
 * \param[in]   config  Pointer to the config struct
 *
 * \return Status of the initialization
 * \retval STATUS_OK               Module initiated correctly
 * \retval STATUS_ERR_DENIED       If module is enabled
 * \retval STATUS_BUSY             If module is busy resetting
 * \retval STATUS_ERR_INVALID_ARG  If invalid argument(s) were provided
 */
enum status_code spi_init(
		struct spi_module *const module,
		Spi *const hw,
		const struct spi_config *const config)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(hw);
	Assert(config);

	uint8_t idx;

	/* Initialize device instance */
	module->hw = hw;

	Spi *const spi_module = (module->hw);

	/* Check if module is enabled. */
	if (spi_module->SPI_MODULE_ENABLE.reg & SPI_MODULE_ENABLE_MASK) {
		spi_module->SPI_MODULE_ENABLE.reg = (0x0ul << SPI_MODULE_ENABLE_ENABLE_Pos);
	}

	spi_reset(module);
	_spi_clock_enable(module);

#if SPI_CALLBACK_MODE == true
	if (module->hw == SPI0) {
		_spi_instances[0] = module;
		system_register_isr(RAM_ISR_TABLE_SPIRX0_INDEX, (uint32_t)spi_rx0_isr_handler);
		system_register_isr(RAM_ISR_TABLE_SPITX0_INDEX, (uint32_t)spi_tx0_isr_handler);
	} else if (module->hw == SPI1) {
		_spi_instances[1] = module;
		system_register_isr(RAM_ISR_TABLE_SPIRX1_INDEX, (uint32_t)spi_rx1_isr_handler);
		system_register_isr(RAM_ISR_TABLE_SPITX1_INDEX, (uint32_t)spi_tx1_isr_handler);
	}
#endif

	//Program the pinmux.
	struct gpio_config config_gpio;
	gpio_get_config_defaults(&config_gpio);

	/* Set the pinmux for this spi module. */
	for(idx = 0; idx < 4; idx++) {
		if (config->pin_number_pad[idx] != PINMUX_UNUSED) {
			if (config->mode == SPI_MODE_MASTER) {
				config_gpio.direction = GPIO_PIN_DIR_OUTPUT;
			} else if (config->mode == SPI_MODE_SLAVE) {
				config_gpio.direction = GPIO_PIN_DIR_INPUT;
			}
			gpio_pin_set_config(config->pin_number_pad[idx], &config_gpio);
			gpio_pinmux_cofiguration(config->pin_number_pad[idx], \
						(uint16_t)(config->pinmux_sel_pad[idx]));
		}
	}

	/* Set up the input clock for the module */
	spi_module->CLOCK_SOURCE_SELECT.reg = config->clock_source;

#  if CONF_SPI_MASTER_ENABLE == true
	if (config->mode == SPI_MODE_MASTER) {
		/* Set the mode in SPI master mode */
		spi_module->SPI_MASTER_MODE.reg = SPI_MODE_MASTER;
	}
#  endif

#  if CONF_SPI_SLAVE_ENABLE == true
	if (config->mode == SPI_MODE_SLAVE) {
		/* Set the mode in SPI slave mode */
		spi_module->SPI_MASTER_MODE.reg = SPI_MODE_SLAVE;
	}
#  endif

#if SPI_CALLBACK_MODE == true
	/* Temporary variables */
	uint8_t i;

	/* Initialize parameters */
	for (i = 0; i < SPI_CALLBACK_N; i++) {
		module->callback[i]        = NULL;
	}
	module->tx_buffer_ptr              = NULL;
	module->rx_buffer_ptr              = NULL;
	module->remaining_tx_buffer_length = 0x0000;
	module->remaining_rx_buffer_length = 0x0000;
	module->registered_callback        = 0x00;
	module->enabled_callback           = 0x00;
	module->status                     = STATUS_OK;
	module->dir                        = SPI_DIRECTION_IDLE;
	module->locked                     = 0;
#endif

	/* Write configuration to module and return status code */
	return _spi_set_config(module, config);
}

/**
 * \name Enable/Disable
 * @{
 */

/**
 * \brief Enables the SPI module
 *
 * This function will enable the SPI module.
 *
 * \param[in,out] module  Pointer to the software instance struct
 */
void spi_enable(struct spi_module *const module)
{
	Spi *const spi_module = (module->hw);

#if SPI_CALLBACK_MODE == true
	if(spi_module == SPI0) {
		NVIC_EnableIRQ(SPI0_RX_IRQn);
		NVIC_EnableIRQ(SPI0_TX_IRQn);
	} else if(spi_module == SPI1) {
		NVIC_EnableIRQ(SPI1_RX_IRQn);
		NVIC_EnableIRQ(SPI1_TX_IRQn);
	}
#endif

	/* Enable SPI */
	spi_module->SPI_MODULE_ENABLE.reg = SPI_MODULE_ENABLE_ENABLE;
}

/**
 * \brief Disables the SPI module
 *
 * This function will disable the SPI module.
 *
 * \param[in,out] module  Pointer to the software instance struct
 */
void spi_disable(struct spi_module *const module)
{
	Spi *const spi_module = (module->hw);

#  if SPI_CALLBACK_MODE == true
	if(spi_module == SPI0) {
		NVIC_DisableIRQ(SPI0_RX_IRQn);
		NVIC_DisableIRQ(SPI0_TX_IRQn);
	} else if(spi_module == SPI1) {
		NVIC_DisableIRQ(SPI1_RX_IRQn);
		NVIC_DisableIRQ(SPI1_TX_IRQn);
	}
#  endif

	/* Disable SPI */
	spi_module->SPI_MODULE_ENABLE.reg = (0x0ul << SPI_MODULE_ENABLE_ENABLE_Pos);
	_spi_clock_disable(module);
}

/**
 * \brief Attempt to get lock on driver instance
 *
 * This function checks the instance's lock, which indicates whether or not it
 * is currently in use, and sets the lock if it was not already set.
 *
 * The purpose of this is to enable exclusive access to driver instances, so
 * that, e.g., transactions by different services will not interfere with each
 * other.
 *
 * \param[in,out] module Pointer to the driver instance to lock
 *
 * \retval STATUS_OK   If the module was locked
 * \retval STATUS_BUSY If the module was already locked
 */
enum status_code spi_lock(struct spi_module *const module)
{
	enum status_code status;

	if (module->locked) {
		status = STATUS_BUSY;
	} else {
		module->locked = true;
		status = STATUS_OK;
	}

	return status;
}

/**
 * \brief Unlock driver instance
 *
 * This function clears the instance lock, indicating that it is available for
 * use.
 *
 * \param[in,out] module Pointer to the driver instance to lock.
 *
 * \retval STATUS_OK   If the module was locked
 * \retval STATUS_BUSY If the module was already locked
 */
void spi_unlock(struct spi_module *const module)
{
	module->locked = false;
}

/**
 * \brief Transfers a single SPI character
 *
 * This function will send a single SPI character via SPI and ignore any data
 * shifted in by the connected device. To both send and receive data, use the
 * \ref spi_transceive_wait function or use the \ref spi_read function after
 * writing a character.
 *
 * Note that this function does not handle the SS (Slave Select)
 * pin(s) in master mode; this must be handled from the user application.
 *
 * \note In slave mode, the data will not be transferred before a master
 *       initiates a transaction.
 *
 * \param[in] module   Pointer to the software instance struct
 * \param[in] tx_data  Data to transmit
 *
 * \return Status of the procedure
 * \retval STATUS_OK    If the data was written
 * \retval STATUS_BUSY  If the last write was not completed
 */
enum status_code spi_write(struct spi_module *module, uint8_t tx_data)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(module->hw);

	Spi *const spi_module = (module->hw);

	/* Check if the data register has been copied to the shift register */
	if (!_spi_is_ready_to_write(spi_module)) {
		/* Data register has not been copied to the shift register, return */
		return STATUS_BUSY;
	}

	/* Write the character to the DATA register */
	spi_module->TRANSMIT_DATA.reg = tx_data & SPI_TRANSMIT_DATA_MASK;

	return STATUS_OK;
}

/**
 * \brief Reads last received SPI character
 *
 * This function will return the last SPI character shifted into the receive
 * register by the \ref spi_write function
 *
 * \note Receiver must be enabled in the configuration
 *
 * \param[in] module    Pointer to the software instance struct
 * \param[out] rx_data  Pointer to store the received data
 *
 * \returns Status of the read operation.
 * \retval STATUS_OK            If data was read
 * \retval STATUS_ERR_IO        If no data is available
 * \retval STATUS_ERR_OVERFLOW  If the data is overflown
 */
enum status_code spi_read(
		struct spi_module *const module,
		uint8_t *rx_data)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(module->hw);

	Spi *const spi_module = (module->hw);

	/* Check if data is ready to be read */
	if (!_spi_is_ready_to_read(spi_module)) {
		/* No data has been received, return */
		return STATUS_ERR_IO;
	}

	/* Return value */
	enum status_code retval = STATUS_OK;

	/* Check if data is overflown */
	if (spi_module->RECEIVE_STATUS.bit.FIFO_OVERRUN) {
		retval = STATUS_ERR_OVERFLOW;
	}

	/* Read the character from the DATA register */
	*rx_data = ((uint8_t)spi_module->RECEIVE_DATA.reg & SPI_RECEIVE_DATA_MASK);

	return retval;
}

/**
 * \brief Transceive requested amount of data to and from the SPI.
 *
 * This function will return after sending and receiving requested amount of data
 *
 * \note Receiver must be enabled in the configuration
 * \note The \ref spi_select_slave function should be called before calling
 *       this function.
 *
 * \param[in] module    Pointer to the software instance struct
 * \param[in] tx_data   Pointer containing the data to be transmitted
 * \param[in] length    Length of data to be read
 * \param[out] rx_data  Pointer to store the received data
 *
 * \returns Status of the read operation.
 * \retval STATUS_OK            If data was read
 * \retval STATUS_ERR_IO        If no data is available
 * \retval STATUS_ERR_OVERFLOW  If the data is overflown
 */
enum status_code spi_transceive_buffer_wait(
		struct spi_module *const module,
		uint8_t *tx_data,
		uint8_t *rx_data,
		uint16_t length)
{
	Spi *spi_module = module->hw;
	uint8_t dummy = 0;
	uint8_t skip_mosi = 0;
	uint8_t skip_miso = 0;
	uint8_t status;
	uint16_t transfer_len = 0;

	if(spi_module == 0) {
		return STATUS_ERR_NOT_INITIALIZED;
	}
	if(!tx_data) {
		tx_data = &dummy;
		*tx_data = module->tx_dummy_byte;
		skip_mosi = 1;
	} else if(!rx_data) {
		rx_data = &dummy;
		skip_miso = 1;
	} else if(length == 0) {
		return STATUS_ERR_INVALID_ARG;
	}

	/* Check for Idle */
	do {
		status = _spi_is_active(spi_module);
	}while(status);

	/* Clear all status registers */
	spi_module->RECEIVE_STATUS.reg;
	spi_module->TRANSMIT_STATUS.reg;

	/* Start transfer */
	while(transfer_len < length) {
		/* Write data to MOSI */
		while(!_spi_is_ready_to_write(spi_module));
		spi_module->TRANSMIT_DATA.reg = *tx_data;
		/* Read data shifted from MISO */
		while(!_spi_is_ready_to_read(spi_module));
		*rx_data = spi_module->RECEIVE_DATA.reg;
		transfer_len++;
		if (!skip_mosi) {
			tx_data++;
		}
		if (!skip_miso) {
			rx_data++;
		}
	}
	/* check TXFIFO is empty */
	do {
		status = _spi_is_write_complete(spi_module);
	}while(!status);

	return STATUS_OK;

}

/**
 * \brief Transceive single byte of data to and from the SPI.
 *
 * This function will return after single byte of data transceived.
 *
 * \note Receiver must be enabled in the configuration
 * \note The \ref spi_select_slave function should be called before calling
 *       this function.
 *
 * \param[in] module    Pointer to the software instance struct
 * \param[in] tx_data   Pointer containing the data to be transmitted
 * \param[out] rx_data  Pointer to store the received data
 *
 * \returns Status of the read operation.
 * \retval STATUS_OK            If data was read
 * \retval STATUS_ERR_IO        If no data is available
 * \retval STATUS_ERR_OVERFLOW  If the data is overflown
 */
enum status_code spi_transceive_wait(
		struct spi_module *const module,
		uint8_t *tx_data,
		uint8_t *rx_data)
{
	return spi_transceive_buffer_wait(module, tx_data, rx_data, 1);
}

/**
 * \brief Reads requested amount of data from the SPI.
 *
 * This function will return after reading requested amount of data
 *
 * \note Receiver must be enabled in the configuration
 * \note The \ref spi_select_slave function should be called before calling
 *       this function.
 *
 * \param[in] module    Pointer to the software instance struct
 * \param[in] length    Length of data to be read
 * \param[in] dummy     Dummy byte to be sent on bus when reading data
 * \param[out] rx_data  Pointer to store the received data
 *
 * \returns Status of the read operation.
 * \retval STATUS_OK            If data was read
 * \retval STATUS_ERR_IO        If no data is available
 * \retval STATUS_ERR_OVERFLOW  If the data is overflown
 */
enum status_code spi_read_buffer_wait(
		struct spi_module *const module,
		uint8_t *rx_data,
		uint16_t length,
		uint8_t dummy)
{
	module->tx_dummy_byte = dummy;
	return spi_transceive_buffer_wait(module, NULL, rx_data, length);
}

/**
 * \brief Writes requested amount of data to the SPI.
 *
 * This function will return after writing requested amount of data
 *
 * \note The \ref spi_select_slave function should be called before calling
 *       this function.
 *
 * \param[in] module    Pointer to the software instance struct
 * \param[in] length    length of data to be read
 * \param[out] tx_data  Pointer to buffer to be transmitted
 *
 * \returns Status of the read operation.
 * \retval STATUS_OK            If data was read
 * \retval STATUS_ERR_IO        If no data is available
 * \retval STATUS_ERR_OVERFLOW  If the data is overflown
 */
enum status_code spi_write_buffer_wait(
		struct spi_module *const module,
		uint8_t *tx_data,
		uint16_t length)
{
	return spi_transceive_buffer_wait(module, tx_data, NULL, length);
}

/**
 * \brief Asserting/Deasserting the slave select for the corresponding slave.
 *
 * This function will assert or deassert the SS of the requested slave device.
 *
 * \param[in] module    Pointer to the software instance struct
 * \param[in] slave     Pointer containing slave instance
 * \param[in] select    Bool to select the salve or deselect
 *
 * \returns Status of the slave select operation.
 *
 * \retval STATUS_OK                If SS pin is a valid one and selected/deselected
 * \retval STATUS_ERR_INVALID_ARG   Invalid SS pin
 */
enum status_code spi_select_slave(
		struct spi_module *const module,
		struct spi_slave_inst *const slave,
		bool select)
{
	uint8_t gpio_num = slave->ss_pin;
	if(select) {
		/* ASSERT Slave select pin */
		gpio_pin_set_output_level(gpio_num, false);
	} else {
		/* DEASSERT Slave select pin */
		gpio_pin_set_output_level(gpio_num, true);
	}

	return STATUS_OK;
}
