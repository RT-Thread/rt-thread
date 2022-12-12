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

#ifndef HAL_MAC_ASYNC_H_INCLUDED
#define HAL_MAC_ASYNC_H_INCLUDED

#include <hpl_mac_async.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup doc_driver_hal_mac_async
 *
 *@{
 */

/**
 * \brief MAC descriptor
 *
 * The MAC descriptor forward declaration.
 */
struct mac_async_descriptor;

/**
 * \brief MAC callback type
 *
 * \param[in] descr A MAC descriptor
 */
typedef void (*mac_async_cb_t)(struct mac_async_descriptor *const descr);

/**
 * \brief MAC callbacks
 */
struct mac_async_callbacks {
	mac_async_cb_t receive;
	mac_async_cb_t transmit;
};

/**
 * \brief MAC descriptor
 */
struct mac_async_descriptor {
	struct _mac_async_device   dev; /*!< MAC HPL device descriptor */
	struct mac_async_callbacks cb;  /*!< MAC Callback handlers */
};

/**
 * Callback for MAC interrupt
 */
typedef void (*mac_cb)(struct mac_async_descriptor *const descr);

/**
 * \brief Initialize the MAC driver
 *
 * \param[in] descr A MAC descriptor to init.
 * \param[in] hw    Hardware instance pointer.
 *
 * \return Operation status.
 * \retval ERR_NONE Success.

 */
int32_t mac_async_init(struct mac_async_descriptor *const descr, void *const dev);

/**
 * \brief Deinitialize the MAC driver
 *
 * \param[in] descr A MAC descriptor to deinitialize.
 *
 * \return Operation status.
 * \retval ERR_NONE Success.
 */
int32_t mac_async_deinit(struct mac_async_descriptor *const descr);

/** \brief Enable the MAC
 *
 * \param[in] descr Pointer to the HAL MAC descriptor.
 *
 * \return Operation status.
 * \retval ERR_NONE Success.
 */
int32_t mac_async_enable(struct mac_async_descriptor *const descr);

/**
 * \brief Disable the MAC
 *
 * \param[in] descr Pointer to the HAL MAC descriptor
 *
 * \return Operation status.
 * \retval ERR_NONE Success.
 */
int32_t mac_async_disable(struct mac_async_descriptor *const descr);

/**
 * \brief Write raw data to MAC
 *
 * Write the raw data to the MAC that will be transmitted
 *
 * \param[in] descr Pointer to the HAL MAC descriptor.
 * \param[in] buf   Pointer to the data buffer.
 * \param[in] len   Length of the data buffer.
 *
 * \return Operation status.
 * \retval ERR_NONE Success.
 */
int32_t mac_async_write(struct mac_async_descriptor *const descr, uint8_t *buf, uint32_t len);

/**
 * \brief Read raw data from MAC
 *
 * Read received raw data from MAC
 *
 * \param[in] descr  Pointer to the HAL MAC descriptor.
 * \param[in] buffer Pointer to the data buffer. If the pointer is NULL, then the
 *                   frame will be discarded.
 * \param[in] length The max. length of the data buffer to be read. If the length is zero,
 *                   then the frame will be discard
 *
 * \return Number of bytes that received
 */
uint32_t mac_async_read(struct mac_async_descriptor *const descr, uint8_t *buf, uint32_t len);

/**
 * \brief Get next valid package length
 *
 * Get next valid package length from the MAC. The application can use this function
 * to fetch the length of the next package, malloc a buffer with this
 * length, and then invoke mac_async_read to read out the package data.
 *
 * \param[in] descr Pointer to the HAL MAC descriptor.
 *
 * \return The number of bytes in the next package that can be read.
 */
uint32_t mac_async_read_len(struct mac_async_descriptor *const descr);

/**
 * \brief Enable the MAC IRQ
 *
 * \param[in] descr Pointer to the HAL MAC descriptor
 */
void mac_async_enable_irq(struct mac_async_descriptor *const descr);

/**
 * \brief Disable the MAC IRQ
 *
 * \param[in] descr Pointer to the HAL MAC descriptor
 */
void mac_async_disable_irq(struct mac_async_descriptor *const descr);

/**
 * \brief Register the MAC callback function
 *
 * \param[in] descr Pointer to the HAL MAC descriptor.
 * \param[in] type  Callback function type.
 * \param[in] func  A callback function. Passing NULL will de-register any
 *                  registered callback.
 *
 * \return Operation status.
 * \retval ERR_NONE Success.
 */
int32_t mac_async_register_callback(struct mac_async_descriptor *const descr, const enum mac_async_cb_type type,
                                    const FUNC_PTR func);

/**
 * \brief Set MAC filter
 *
 * Set MAC filter. Ethernet frames matching the filter, will be received.
 *
 * \param[in] descr  Pointer to the HAL MAC descriptor.
 * \param[in] index  MAC filter index. Start from 0. The maximum value depends on
 *            the hardware specifications.
 * \param[in] filter Pointer to the filter descriptor.
 *
 * \return Operation status.
 * \retval ERR_NONE Success.
 */
int32_t mac_async_set_filter(struct mac_async_descriptor *const descr, uint8_t index, struct mac_async_filter *filter);

/**
 * \brief Set MAC filter (expanded).
 *
 * Set MAC filter. The Ethernet frames matching the filter, will be received.
 *
 * \param[in] descr  Pointer to the HAL MAC descriptor
 * \param[in] mac    MAC address
 *
 * \return Operation status.
 * \retval ERR_NONE Success.
 */
int32_t mac_async_set_filter_ex(struct mac_async_descriptor *const descr, uint8_t mac[6]);

/**
 * \brief Write PHY register
 *
 * \param[in] descr Pointer to the HAL MAC descriptor.
 * \param[in] addr  PHY address.
 * \param[in] reg   Register address.
 * \param[in] val   Register value.
 *
 * \return Operation status.
 * \retval ERR_NONE Success.
 */
int32_t mac_async_write_phy_reg(struct mac_async_descriptor *const descr, uint16_t addr, uint16_t reg, uint16_t val);

/**
 * \brief Read PHY register
 *
 * \param[in] descr Pointer to the HAL MAC descriptor.
 * \param[in] addr  PHY address.
 * \param[in] reg   Register address.
 * \param[in] val   Register value.
 *
 * \return Operation status.
 * \retval ERR_NONE Success.
 */
int32_t mac_async_read_phy_reg(struct mac_async_descriptor *const descr, uint16_t addr, uint16_t reg, uint16_t *val);

/**
 * \brief Get the MAC driver version
 */
uint32_t mac_async_get_version(void);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* HAL_MAC_ASYNC_H_INCLUDED */
