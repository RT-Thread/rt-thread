/**
 * \file
 *
 * \brief Control Area Network(CAN) functionality implementation.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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
#include <hal_can_async.h>
#include <utils_assert.h>

#define DRIVER_VERSION 0x00000001u

/**
 * \internal Callback of CAN Message Write finished
 *
 * \param[in] dev The pointer to CAN device structure
 */
static void can_tx_done(struct _can_async_device *dev);
/**
 * \internal Callback of CAN Message Read finished
 *
 * \param[in] dev The pointer to CAN device structure
 */
static void can_rx_done(struct _can_async_device *dev);
/**
 * \internal Callback of CAN Interrupt
 *
 * \param[in] dev  The pointer to CAN device structure
 * \param[in] type Interrupt source type
 */
static void can_irq_handler(struct _can_async_device *dev, enum can_async_interrupt_type type);

/**
 * \brief Initialize CAN.
 */
int32_t can_async_init(struct can_async_descriptor *const descr, void *const hw)
{
	int32_t rc;

	ASSERT(descr && hw);

	rc = _can_async_init(&descr->dev, hw);
	if (rc) {
		return rc;
	}
	descr->dev.cb.tx_done     = can_tx_done;
	descr->dev.cb.rx_done     = can_rx_done;
	descr->dev.cb.irq_handler = can_irq_handler;

	return ERR_NONE;
}

/**
 * \brief Deinitialize CAN.
 */
int32_t can_async_deinit(struct can_async_descriptor *const descr)
{
	ASSERT(descr);
	return _can_async_deinit(&descr->dev);
}

/**
 * \brief Enable CAN
 */
int32_t can_async_enable(struct can_async_descriptor *const descr)
{
	ASSERT(descr);
	return _can_async_enable(&descr->dev);
}

/**
 * \brief Disable CAN
 */
int32_t can_async_disable(struct can_async_descriptor *const descr)
{
	ASSERT(descr);
	return _can_async_disable(&descr->dev);
}

/**
 * \brief Read a CAN message
 */
int32_t can_async_read(struct can_async_descriptor *const descr, struct can_message *msg)
{
	ASSERT(descr && msg);
	return _can_async_read(&descr->dev, msg);
}

/**
 * \brief Write a CAN message
 */
int32_t can_async_write(struct can_async_descriptor *const descr, struct can_message *msg)
{
	ASSERT(descr && msg);
	return _can_async_write(&descr->dev, msg);
}

/**
 * \brief Register CAN callback function to interrupt
 */
int32_t can_async_register_callback(struct can_async_descriptor *const descr, enum can_async_callback_type type,
                                    FUNC_PTR cb)
{
	ASSERT(descr);

	switch (type) {
	case CAN_ASYNC_RX_CB:
		descr->cb.rx_done = (cb != NULL) ? (can_cb_t)cb : NULL;
		break;
	case CAN_ASYNC_TX_CB:
		descr->cb.tx_done = (cb != NULL) ? (can_cb_t)cb : NULL;
		break;
	case CAN_ASYNC_IRQ_CB:
		descr->cb.irq_handler
		    = (cb != NULL) ? (void (*)(struct can_async_descriptor *const, enum can_async_interrupt_type))cb : NULL;
		break;
	default:
		return ERR_INVALID_ARG;
	}

	_can_async_set_irq_state(&descr->dev, type, NULL != cb);

	return ERR_NONE;
}

/**
 * \brief Return number of read errors
 */
uint8_t can_async_get_rxerr(struct can_async_descriptor *const descr)
{
	ASSERT(descr);
	return _can_async_get_rxerr(&descr->dev);
}

/**
 * \brief Return number of write errors
 */
uint8_t can_async_get_txerr(struct can_async_descriptor *const descr)
{
	ASSERT(descr);
	return _can_async_get_txerr(&descr->dev);
}

/**
 * \brief Set CAN to the specified mode
 */
int32_t can_async_set_mode(struct can_async_descriptor *const descr, enum can_mode mode)
{
	ASSERT(descr);
	return _can_async_set_mode(&descr->dev, mode);
}

/**
 * \brief Set CAN filter
 */
int32_t can_async_set_filter(struct can_async_descriptor *const descr, uint8_t index, enum can_format fmt,
                             struct can_filter *filter)
{
	ASSERT(descr);
	return _can_async_set_filter(&descr->dev, index, fmt, filter);
}

/**
 * \brief Retrieve the current driver version
 */
uint32_t can_async_get_version(void)
{
	return DRIVER_VERSION;
}

/**
 * \internal Callback of CAN Message Write finished
 */
static void can_tx_done(struct _can_async_device *dev)
{
	struct can_async_descriptor *const descr = CONTAINER_OF(dev, struct can_async_descriptor, dev);

	if (descr->cb.tx_done) {
		descr->cb.tx_done(descr);
	}
}

/**
 * \internal Callback of CAN Message Read finished
 */
static void can_rx_done(struct _can_async_device *dev)
{
	struct can_async_descriptor *const descr = CONTAINER_OF(dev, struct can_async_descriptor, dev);

	if (descr->cb.rx_done) {
		descr->cb.rx_done(descr);
	}
}

/**
 * \internal Callback of CAN Interrupt
 */
static void can_irq_handler(struct _can_async_device *dev, enum can_async_interrupt_type type)
{
	struct can_async_descriptor *const descr = CONTAINER_OF(dev, struct can_async_descriptor, dev);

	if (descr->cb.irq_handler) {
		descr->cb.irq_handler(descr, type);
	}
}
