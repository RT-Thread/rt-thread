/**
 * \file
 *
 * \brief MAC functionality declaration.
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

#ifndef HPL_MAC_ASYNC_H_INCLUDED
#define HPL_MAC_ASYNC_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>
#include <utils.h>
#include <hpl_irq.h>
/**
 * \addtogroup hpl__mac__async__group MAC HPL APIs
 *
 *@{
 */

/**
 * \brief MAC device descriptor Forward declaration
 */
struct _mac_async_device;

/**
 * \brief MAC callback type
 *
 * \param[in] dev An MAC device descriptor
 */
typedef void (*_mac_async_cb_t)(struct _mac_async_device *const dev);

/**
 * \brief MAC callbacks
 */
struct _mac_async_callbacks {
	_mac_async_cb_t transmited; /*!< Frame received */
	_mac_async_cb_t received;   /*!< Frame transmited */
};

/**
 * \brief MAC device descriptor
 */
struct _mac_async_device {
	void *                      hw;  /*!< Hardware module instance handler */
	struct _mac_async_callbacks cb;  /*!< Callback handler */
	struct _irq_descriptor      irq; /*!< IRQ handler */
};

/**
 * \brief MAC callback types
 */
enum mac_async_cb_type {
	MAC_ASYNC_RECEIVE_CB, /*!< One or more frame been received */
	MAC_ASYNC_TRANSMIT_CB /*!< One or more frame been transmited */
};

struct mac_async_filter {
	uint8_t mac[6];     /*!< Destination address */
	uint8_t tid[2];     /*!< Type ID, 0x0600 IP package */
	bool    tid_enable; /*!< Enable TID matching */
};
/**
 * \brief Initialize the MAC driver
 *
 * Initialize the MAC driver
 *
 * \param[in] dev A MAC device descriptor to deinit
 * \param[in] hw  Hardware module instance
 *
 * \return Operation status.
 * \retval ERR_NONE Success.

 */
int32_t _mac_async_init(struct _mac_async_device *const dev, void *const hw);

/**
 * \brief Deinitialize the MAC driver
 *
 * Deinitialize the MAC driver
 *
 * \param[in] descr A MAC device descriptor to deinit
 *
 * \return Operation status.
 * \retval ERR_NONE Success.
 */
int32_t _mac_async_deinit(struct _mac_async_device *const dev);

/** \brief Enable the MAC
 *
 * Enable the MAC
 *
 * \param[in] dev Pointer to the HPL MAC device descriptor
 *
 * \return Operation status.
 * \retval ERR_NONE Success.
 */
int32_t _mac_async_enable(struct _mac_async_device *const dev);

/**
 * \brief Disable the MAC
 *
 * Disable the MAC
 *
 * \param[in] dev Pointer to the HPL MAC device descriptor
 *
 * \return Operation status.
 * \retval ERR_NONE Success.
 */
int32_t _mac_async_disable(struct _mac_async_device *const dev);

/**
 * \brief Write raw data to MAC
 *
 * Write raw data to MAC that will be transmitted.
 *
 * \param[in] dev Pointer to the HPL MAC device descriptor
 * \param[in] buffer Pointer to the data buffer
 * \param[in] length Length of the data buffer
 *
 * \return Operation status.
 * \retval ERR_NONE Success.
 */
int32_t _mac_async_write(struct _mac_async_device *const dev, uint8_t *buf, uint32_t len);

/**
 * \brief Read received raw data from MAC
 *
 * Read received raw data from MAC
 *
 * \param[in] dev    Pointer to the HPL MAC device descriptor
 * \param[in] buffer Pointer to the data buffer. if pointer is null, then the
 *                   frame will be discard.
 * \param[in] length Max Length of the data buffer to be read. if len is zero,
 *                   then the frame will be discard
 *
 * \return Number of bytes that have been received
 */
uint32_t _mac_async_read(struct _mac_async_device *const dev, uint8_t *buf, uint32_t len);

/**
 * \brief Get next valid package length
 *
 * Get next valid package length from MAC. Application can use this function
 * to fetch the length of the next package, malloc the a buffer whit this
 * length, and then invoke mac_async_read to read out the package data.
 *
 * \param[in] dev Pointer to the HPL MAC device descriptor.
 *
 * \return Number of bytes that next package can be read.
 */
uint32_t _mac_async_read_len(struct _mac_async_device *const dev);

/**
 * \brief Enable the MAC IRQ
 *
 * Enable the MAC IRQ
 *
 * \param[in] dev Pointer to the HPL MAC device descriptor
 */
void _mac_async_enable_irq(struct _mac_async_device *const dev);

/**
 * \brief Disable the MAC IRQ
 *
 * Disable the MAC IRQ
 *
 * \param[in] dev Pointer to the HPL MAC device descriptor
 */
void _mac_async_disable_irq(struct _mac_async_device *const dev);

/**
 * \brief Register the MAC callback
 *
 * Register the MAC callback
 *
 * \param[in] dev  Pointer to the HPL MAC device descriptor
 * \param[in] type Callback function type.
 * \param[in] func A callback function, passing NULL will de-register
 *
 * \return Operation status.
 * \retval ERR_NONE Success.
 */
int32_t _mac_async_register_callback(struct _mac_async_device *const dev, const enum mac_async_cb_type type,
                                     const FUNC_PTR func);

/**
 * \brief Set MAC filter
 *
 * Set MAC filter, ethernet frames which match the filter will be received.
 *
 * \param[in] dev    Pointer to the HPL MAC device descriptor
 * \param[in] index  Mac filter index, start from 0, max value depends on
 *                   hardware specificaions.
 * \param[in] filter Pointer to the filter descriptor.
 *
 * \return Operation status.
 * \retval ERR_NONE Success.
 */
int32_t _mac_async_set_filter(struct _mac_async_device *const dev, uint8_t index, struct mac_async_filter *filter);

/**
 * \brief Set MAC filter (expaneded)
 *
 * Set MAC filter, ethernet frames which match the filter will be received.
 *
 * \param[in] dev Pointer to the HPL MAC device descriptor
 * \param[in] mac Mac address
 *
 * \return Operation status.
 * \retval ERR_NONE Success.
 */
int32_t _mac_async_set_filter_ex(struct _mac_async_device *const dev, uint8_t mac[6]);

/**
 * \brief Write PHY register
 *
 * Write PHY register
 *
 * \param[in] dev Pointer to the HPL MAC device descriptor
 * \param[in] addr  PHY address.
 * \param[in] reg   Register address.
 * \param[in] data  Register value.
 *
 * \return Operation status.
 * \retval ERR_NONE Success.
 */
int32_t _mac_async_write_phy_reg(struct _mac_async_device *const dev, uint16_t addr, uint16_t reg, uint16_t data);

/**
 * \brief Read PHY register
 *
 * Read PHY register
 *
 * \param[in] dev Pointer to the HPL MAC device descriptor
 * \param[in] addr  PHY address.
 * \param[in] reg   Register address.
 * \param[in] data  Register value.
 *
 * \return Operation status.
 * \retval ERR_NONE Success.
 */
int32_t _mac_async_read_phy_reg(struct _mac_async_device *const dev, uint16_t addr, uint16_t reg, uint16_t *val);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* HPL_MAC_ASYNC_H_INCLUDED */
