/**
 * \file
 *
 * \brief I2C Slave Hardware Proxy Layer(HPL) declaration.
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
#ifndef _HPL_I2C_S_ASYNC_H_INCLUDED
#define _HPL_I2C_S_ASYNC_H_INCLUDED

#include "hpl_i2c_s_sync.h"
#include "hpl_irq.h"
#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief i2c callback types
 */
enum _i2c_s_async_callback_type { I2C_S_DEVICE_ERROR, I2C_S_DEVICE_TX, I2C_S_DEVICE_RX_COMPLETE };

/**
 * \brief Forward declaration of I2C Slave device
 */
struct _i2c_s_async_device;

/**
 * \brief i2c slave callback function type
 */
typedef void (*_i2c_s_async_cb_t)(struct _i2c_s_async_device *device);

/**
 * \brief i2c slave callback pointers structure
 */
struct _i2c_s_async_callback {
	void (*error)(struct _i2c_s_async_device *const device);
	void (*tx)(struct _i2c_s_async_device *const device);
	void (*rx_done)(struct _i2c_s_async_device *const device, const uint8_t data);
};

/**
 * \brief i2c slave device structure
 */
struct _i2c_s_async_device {
	void *                       hw;
	struct _i2c_s_async_callback cb;
	struct _irq_descriptor       irq;
};

/**
 * \name HPL functions
 */

/**
 * \brief Initialize asynchronous I2C slave
 *
 * This function does low level I2C configuration.
 *
 * \param[in] device The pointer to i2c interrupt device structure
 *
 * \return Return 0 for success and negative value for error
 */
int32_t _i2c_s_async_init(struct _i2c_s_async_device *const device, void *const hw);

/**
 * \brief Deinitialize asynchronous I2C in interrupt mode
 *
 * \param[in] device The pointer to i2c device structure
 *
 * \return Return 0 for success and negative value for error
 */
int32_t _i2c_s_async_deinit(struct _i2c_s_async_device *const device);

/**
 * \brief Enable I2C module
 *
 * This function does low level I2C enable.
 *
 * \param[in] device The pointer to i2c slave device structure
 *
 * \return Return 0 for success and negative value for error
 */
int32_t _i2c_s_async_enable(struct _i2c_s_async_device *const device);

/**
 * \brief Disable I2C module
 *
 * This function does low level I2C disable.
 *
 * \param[in] device The pointer to i2c slave device structure
 *
 * \return Return 0 for success and negative value for error
 */
int32_t _i2c_s_async_disable(struct _i2c_s_async_device *const device);

/**
 * \brief Check if 10-bit addressing mode is on
 *
 * \param[in] device The pointer to i2c slave device structure
 *
 * \return Cheking status
 * \retval 1 10-bit addressing mode is on
 * \retval 0 10-bit addressing mode is off
 */
int32_t _i2c_s_async_is_10bit_addressing_on(const struct _i2c_s_async_device *const device);

/**
 * \brief Set I2C slave address
 *
 * \param[in] device The pointer to i2c slave device structure
 * \param[in] address Address to set
 *
 * \return Return 0 for success and negative value for error
 */
int32_t _i2c_s_async_set_address(struct _i2c_s_async_device *const device, const uint16_t address);

/**
 * \brief Write a byte to the given I2C instance
 *
 * \param[in] device The pointer to i2c slave device structure
 * \param[in] data Data to write
 */
void _i2c_s_async_write_byte(struct _i2c_s_async_device *const device, const uint8_t data);

/**
 * \brief Retrieve I2C slave status
 *
 * \param[in] device The pointer to i2c slave device structure
 *
 *\return I2C slave status
 */
i2c_s_status_t _i2c_s_async_get_status(const struct _i2c_s_async_device *const device);

/**
 * \brief Abort data transmission
 *
 * \param[in] device The pointer to i2c device structure
 *
 * \return Return 0 for success and negative value for error
 */
int32_t _i2c_s_async_abort_transmission(const struct _i2c_s_async_device *const device);

/**
 * \brief Enable/disable I2C slave interrupt
 *
 * param[in] device The pointer to I2C slave device instance
 * param[in] type The type of interrupt to disable/enable if applicable
 * param[in] disable Enable or disable
 */
int32_t _i2c_s_async_set_irq_state(struct _i2c_s_async_device *const device, const enum _i2c_s_async_callback_type type,
                                   const bool disable);

#ifdef __cplusplus
}
#endif

#endif /* _HPL_I2C_S_ASYNC_H_INCLUDED */
