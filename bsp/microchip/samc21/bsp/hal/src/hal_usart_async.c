/**
 * \file
 *
 * \brief I/O USART related functionality implementation.
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

#include "hal_usart_async.h"
#include <utils_assert.h>
#include <hal_atomic.h>
#include <utils.h>

/**
 * \brief Driver version
 */
#define DRIVER_VERSION 0x00000001u

static int32_t usart_async_write(struct io_descriptor *const io_descr, const uint8_t *const buf, const uint16_t length);
static int32_t usart_async_read(struct io_descriptor *const io_descr, uint8_t *const buf, const uint16_t length);
static void    usart_process_byte_sent(struct _usart_async_device *device);
static void    usart_transmission_complete(struct _usart_async_device *device);
static void    usart_error(struct _usart_async_device *device);
static void    usart_fill_rx_buffer(struct _usart_async_device *device, uint8_t data);

/**
 * \brief Initialize usart interface
 */
int32_t usart_async_init(struct usart_async_descriptor *const descr, void *const hw, uint8_t *rx_buffer,
                         uint16_t rx_buffer_length, void *const func)
{
	int32_t init_status;
	ASSERT(descr && hw && rx_buffer && rx_buffer_length);

	if (ERR_NONE != ringbuffer_init(&descr->rx, rx_buffer, rx_buffer_length)) {
		return ERR_INVALID_ARG;
	}
	init_status = _usart_async_init(&descr->device, hw);
	if (init_status) {
		return init_status;
	}

	descr->io.read  = usart_async_read;
	descr->io.write = usart_async_write;

	descr->device.usart_cb.tx_byte_sent = usart_process_byte_sent;
	descr->device.usart_cb.rx_done_cb   = usart_fill_rx_buffer;
	descr->device.usart_cb.tx_done_cb   = usart_transmission_complete;
	descr->device.usart_cb.error_cb     = usart_error;

	return ERR_NONE;
}

/**
 * \brief Deinitialize usart interface
 */
int32_t usart_async_deinit(struct usart_async_descriptor *const descr)
{
	ASSERT(descr);
	_usart_async_deinit(&descr->device);
	descr->io.read  = NULL;
	descr->io.write = NULL;

	return ERR_NONE;
}

/**
 * \brief Enable usart interface
 */
int32_t usart_async_enable(struct usart_async_descriptor *const descr)
{
	ASSERT(descr);
	_usart_async_enable(&descr->device);

	return ERR_NONE;
}

/**
 * \brief Disable usart interface
 */
int32_t usart_async_disable(struct usart_async_descriptor *const descr)
{
	ASSERT(descr);
	_usart_async_disable(&descr->device);

	return ERR_NONE;
}

/**
 * \brief Retrieve I/O descriptor
 */
int32_t usart_async_get_io_descriptor(struct usart_async_descriptor *const descr, struct io_descriptor **io)
{
	ASSERT(descr && io);

	*io = &descr->io;
	return ERR_NONE;
}

/**
 * \brief Register usart callback
 */
int32_t usart_async_register_callback(struct usart_async_descriptor *const descr,
                                      const enum usart_async_callback_type type, usart_cb_t cb)
{
	ASSERT(descr);

	switch (type) {
	case USART_ASYNC_RXC_CB:
		descr->usart_cb.rx_done = cb;
		_usart_async_set_irq_state(&descr->device, USART_ASYNC_RX_DONE, NULL != cb);
		break;
	case USART_ASYNC_TXC_CB:
		descr->usart_cb.tx_done = cb;
		_usart_async_set_irq_state(&descr->device, USART_ASYNC_TX_DONE, NULL != cb);
		break;
	case USART_ASYNC_ERROR_CB:
		descr->usart_cb.error = cb;
		_usart_async_set_irq_state(&descr->device, USART_ASYNC_ERROR, NULL != cb);
		break;
	default:
		return ERR_INVALID_ARG;
	}

	return ERR_NONE;
}

/**
 * \brief Specify action for flow control pins
 */
int32_t usart_async_set_flow_control(struct usart_async_descriptor *const descr,
                                     const union usart_flow_control_state state)
{
	ASSERT(descr);
	_usart_async_set_flow_control_state(&descr->device, state);

	return ERR_NONE;
}

/**
 * \brief Set usart baud rate
 */
int32_t usart_async_set_baud_rate(struct usart_async_descriptor *const descr, const uint32_t baud_rate)
{
	ASSERT(descr);
	_usart_async_set_baud_rate(&descr->device, baud_rate);

	return ERR_NONE;
}

/**
 * \brief Set usart data order
 */
int32_t usart_async_set_data_order(struct usart_async_descriptor *const descr, const enum usart_data_order data_order)
{
	ASSERT(descr);
	_usart_async_set_data_order(&descr->device, data_order);

	return ERR_NONE;
}

/**
 * \brief Set usart mode
 */
int32_t usart_async_set_mode(struct usart_async_descriptor *const descr, const enum usart_mode mode)
{
	ASSERT(descr);
	_usart_async_set_mode(&descr->device, mode);

	return ERR_NONE;
}

/**
 * \brief Set usart parity
 */
int32_t usart_async_set_parity(struct usart_async_descriptor *const descr, const enum usart_parity parity)
{
	ASSERT(descr);
	_usart_async_set_parity(&descr->device, parity);

	return ERR_NONE;
}

/**
 * \brief Set usart stop bits
 */
int32_t usart_async_set_stopbits(struct usart_async_descriptor *const descr, const enum usart_stop_bits stop_bits)
{
	ASSERT(descr);
	_usart_async_set_stop_bits(&descr->device, stop_bits);

	return ERR_NONE;
}

/**
 * \brief Set usart character size
 */
int32_t usart_async_set_character_size(struct usart_async_descriptor *const descr, const enum usart_character_size size)
{
	ASSERT(descr);
	_usart_async_set_character_size(&descr->device, size);

	return ERR_NONE;
}

/**
 * \brief Retrieve the state of flow control pins
 */
int32_t usart_async_flow_control_status(const struct usart_async_descriptor *const descr,
                                        union usart_flow_control_state *const      state)
{
	ASSERT(descr && state);
	*state = _usart_async_get_flow_control_state(&descr->device);

	return ERR_NONE;
}

/**
 * \brief Check if the usart transmitter is empty
 */
int32_t usart_async_is_tx_empty(const struct usart_async_descriptor *const descr)
{
	ASSERT(descr);
	return _usart_async_is_byte_sent(&descr->device);
}

/**
 * \brief Check if the usart receiver is not empty
 */
int32_t usart_async_is_rx_not_empty(const struct usart_async_descriptor *const descr)
{
	ASSERT(descr);

	return ringbuffer_num(&descr->rx) > 0;
}

/**
 * \brief Retrieve the current interface status
 */
int32_t usart_async_get_status(struct usart_async_descriptor *const descr, struct usart_async_status *const status)
{
	ASSERT(descr);

	volatile uint32_t *tmp_stat  = &(descr->stat);
	volatile uint16_t *tmp_txcnt = &(descr->tx_por);

	if (status) {
		status->flags = *tmp_stat;
		status->txcnt = *tmp_txcnt;
		status->rxcnt = ringbuffer_num(&descr->rx);
	}
	if (*tmp_stat & USART_ASYNC_STATUS_BUSY) {
		return ERR_BUSY;
	}

	return ERR_NONE;
}

/**
 * \brief flush usart rx ringbuf
 */
int32_t usart_async_flush_rx_buffer(struct usart_async_descriptor *const descr)
{
	ASSERT(descr);

	return ringbuffer_flush(&descr->rx);
}

/**
 * \brief Retrieve the current driver version
 */
uint32_t usart_async_get_version(void)
{
	return DRIVER_VERSION;
}

/*
 * \internal Write the given data to usart interface
 *
 * \param[in] descr The pointer to an io descriptor
 * \param[in] buf Data to write to usart
 * \param[in] length The number of bytes to write
 *
 * \return The number of bytes written.
 */
static int32_t usart_async_write(struct io_descriptor *const io_descr, const uint8_t *const buf, const uint16_t length)
{
	struct usart_async_descriptor *descr = CONTAINER_OF(io_descr, struct usart_async_descriptor, io);

	ASSERT(descr && buf && length);

	if (descr->tx_por != descr->tx_buffer_length) {
		return ERR_NO_RESOURCE;
	}
	descr->tx_buffer        = (uint8_t *)buf;
	descr->tx_buffer_length = length;
	descr->tx_por           = 0;
	descr->stat             = USART_ASYNC_STATUS_BUSY;
	_usart_async_enable_byte_sent_irq(&descr->device);

	return (int32_t)length;
}

/*
 * \internal Read data from usart interface
 *
 * \param[in] descr The pointer to an io descriptor
 * \param[in] buf A buffer to read data to
 * \param[in] length The size of a buffer
 *
 * \return The number of bytes read.
 */
static int32_t usart_async_read(struct io_descriptor *const io_descr, uint8_t *const buf, const uint16_t length)
{
	uint16_t                       was_read = 0;
	uint32_t                       num;
	struct usart_async_descriptor *descr = CONTAINER_OF(io_descr, struct usart_async_descriptor, io);

	ASSERT(descr && buf && length);

	CRITICAL_SECTION_ENTER()
	num = ringbuffer_num(&descr->rx);
	CRITICAL_SECTION_LEAVE()

	while ((was_read < num) && (was_read < length)) {
		ringbuffer_get(&descr->rx, &buf[was_read++]);
	}

	return (int32_t)was_read;
}

/**
 * \brief Process "byte is sent" interrupt
 *
 * \param[in] device The pointer to device structure
 */
static void usart_process_byte_sent(struct _usart_async_device *device)
{
	struct usart_async_descriptor *descr = CONTAINER_OF(device, struct usart_async_descriptor, device);
	if (descr->tx_por != descr->tx_buffer_length) {
		_usart_async_write_byte(&descr->device, descr->tx_buffer[descr->tx_por++]);
		_usart_async_enable_byte_sent_irq(&descr->device);
	} else {
		_usart_async_enable_tx_done_irq(&descr->device);
	}
}

/**
 * \brief Process completion of data sending
 *
 * \param[in] device The pointer to device structure
 */
static void usart_transmission_complete(struct _usart_async_device *device)
{
	struct usart_async_descriptor *descr = CONTAINER_OF(device, struct usart_async_descriptor, device);

	descr->stat = 0;
	if (descr->usart_cb.tx_done) {
		descr->usart_cb.tx_done(descr);
	}
}

/**
 * \brief Process byte reception
 *
 * \param[in] device The pointer to device structure
 * \param[in] data Data read
 */
static void usart_fill_rx_buffer(struct _usart_async_device *device, uint8_t data)
{
	struct usart_async_descriptor *descr = CONTAINER_OF(device, struct usart_async_descriptor, device);

	ringbuffer_put(&descr->rx, data);

	if (descr->usart_cb.rx_done) {
		descr->usart_cb.rx_done(descr);
	}
}

/**
 * \brief Process error interrupt
 *
 * \param[in] device The pointer to device structure
 */
static void usart_error(struct _usart_async_device *device)
{
	struct usart_async_descriptor *descr = CONTAINER_OF(device, struct usart_async_descriptor, device);

	descr->stat = 0;
	if (descr->usart_cb.error) {
		descr->usart_cb.error(descr);
	}
}

//@}
