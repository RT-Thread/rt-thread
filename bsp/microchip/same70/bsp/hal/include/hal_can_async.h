/**
 * \file
 *
 * \brief Control Area Network(CAN) functionality declaration.
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

#ifndef HAL_CAN_ASYNC_H_INCLUDED
#define HAL_CAN_ASYNC_H_INCLUDED

#include <hpl_can.h>
#include <hpl_can_async.h>
#include <utils_assert.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * \addtogroup doc_driver_hal_can_async
 *
 *@{
 */

/**
 * \brief CAN Asynchronous descriptor
 *
 * The CAN descriptor forward declaration.
 */
struct can_async_descriptor;

/**
 * Callback for CAN interrupt
 */
typedef void (*can_cb_t)(struct can_async_descriptor *const descr);

/**
 * \brief CAN callbacks
 */
struct can_callbacks {
	can_cb_t tx_done;
	can_cb_t rx_done;
	void (*irq_handler)(struct can_async_descriptor *const descr, enum can_async_interrupt_type type);
};

/**
 * \brief CAN descriptor
 */
struct can_async_descriptor {
	struct _can_async_device dev; /*!< CAN HPL device descriptor */
	struct can_callbacks     cb;  /*!< CAN Interrupt Callbacks handler */
};

/**
 * \brief Initialize CAN.
 *
 * This function initializes the given CAN descriptor.
 *
 * \param[in, out] descr A CAN descriptor to initialize.
 * \param[in]      hw    The pointer to hardware instance.
 *
 * \return Initialization status.
 */
int32_t can_async_init(struct can_async_descriptor *const descr, void *const hw);

/**
 * \brief Deinitialize CAN.
 *
 * This function deinitializes the given CAN descriptor.
 *
 * \param[in, out] descr The CAN descriptor to deinitialize.
 *
 * \return De-initialization status.
 */
int32_t can_async_deinit(struct can_async_descriptor *const descr);

/**
 * \brief Enable CAN
 *
 * This function enables CAN by the given can descriptor.
 *
 * \param[in] descr The CAN descriptor to enable.
 *
 * \return Enabling status.
 */
int32_t can_async_enable(struct can_async_descriptor *const descr);

/**
 * \brief Disable CAN
 *
 * This function disables CAN by the given can descriptor.
 *
 * \param[in] descr The CAN descriptor to disable.
 *
 * \return Disabling status.
 */
int32_t can_async_disable(struct can_async_descriptor *const descr);

/**
 * \brief Read a CAN message
 *
 * \param[in] descr The CAN descriptor to read message.
 * \param[in] msg   The CAN message to read to.
 *
 * \return The status of read message.
 */
int32_t can_async_read(struct can_async_descriptor *const descr, struct can_message *msg);

/**
 * \brief Write a CAN message
 *
 * \param[in] descr The CAN descriptor to write message.
 * \param[in] msg   The CAN message to write.
 *
 * \return The status of write message.
 */
int32_t can_async_write(struct can_async_descriptor *const descr, struct can_message *msg);

/**
 * \brief Register CAN callback function to interrupt
 *
 * \param[in] descr The CAN descriptor
 * \param[in] type  Callback type
 * \param[in] cb    A callback function, passing NULL will de-register any
 *                  registered callback
 *
 * \return The status of callback assignment.
 */
int32_t can_async_register_callback(struct can_async_descriptor *const descr, enum can_async_callback_type type,
                                    FUNC_PTR cb);

/**
 * \brief Return number of read errors
 *
 * This function returns the number of read errors.
 *
 * \param[in] descr The CAN descriptor pointer
 *
 * \return The number of read errors.
 */
uint8_t can_async_get_rxerr(struct can_async_descriptor *const descr);

/**
 * \brief Return number of write errors
 *
 * This function returns the number of write errors.
 *
 * \param[in] descr The CAN descriptor pointer
 *
 * \return The number of write errors.
 */
uint8_t can_async_get_txerr(struct can_async_descriptor *const descr);

/**
 * \brief Set CAN to the specified mode
 *
 * This function sets CAN to a specified mode.
 *
 * \param[in] descr The CAN descriptor pointer
 * \param[in] mode  The CAN operation mode
 *
 * \return Status of the operation.
 */
int32_t can_async_set_mode(struct can_async_descriptor *const descr, enum can_mode mode);

/**
 * \brief Set CAN Filter
 *
 * This function sets CAN to a specified mode.
 *
 * \param[in] descr The CAN descriptor pointer
 * \param[in] index   Index of Filter list
 * \param[in] fmt     CAN Indentify Type
 * \param[in] filter  CAN Filter struct, NULL for clear filter
 *
 * \return Status of the operation.
 */
int32_t can_async_set_filter(struct can_async_descriptor *const descr, uint8_t index, enum can_format fmt,
                             struct can_filter *filter);

/**
 * \brief Retrieve the current driver version
 *
 * \return The current driver version.
 */
uint32_t can_async_get_version(void);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* HAL_CAN_ASYNC_H_INCLUDED */
