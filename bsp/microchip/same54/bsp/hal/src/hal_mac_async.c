/**
 * \file
 *
 * \brief MAC functionality implementation.
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
#include <hal_mac_async.h>
#include <utils_assert.h>
/**
 * \brief Driver version
 */
#define DRIVER_VERSION 0x00000001u

/* Private function */
static void mac_read_cb(struct _mac_async_device *dev);
static void mac_write_cb(struct _mac_async_device *dev);

/**
 * \brief Initialize the MAC driver
 */
int32_t mac_async_init(struct mac_async_descriptor *const descr, void *const hw)
{
	ASSERT(descr && hw);

	return _mac_async_init(&descr->dev, hw);
}

/**
 * \brief Deinitialize the MAC driver
 */
int32_t mac_async_deinit(struct mac_async_descriptor *const descr)
{
	ASSERT(descr);

	return _mac_async_deinit(&descr->dev);
}

/**
 * \brief Enable the MAC
 */
int32_t mac_async_enable(struct mac_async_descriptor *const descr)
{
	ASSERT(descr);

	return _mac_async_enable(&descr->dev);
}
/**
 * \brief Disable the MAC
 */
int32_t mac_async_disable(struct mac_async_descriptor *const descr)
{
	ASSERT(descr);

	return _mac_async_disable(&descr->dev);
}
/**
 * \brief Write raw data to MAC
 */
int32_t mac_async_write(struct mac_async_descriptor *const descr, uint8_t *buf, uint32_t len)
{
	ASSERT(descr && buf && len);

	return _mac_async_write(&descr->dev, buf, len);
}

/**
 * \brief Read raw data from MAC
 */
uint32_t mac_async_read(struct mac_async_descriptor *const descr, uint8_t *buf, uint32_t len)
{
	ASSERT(descr);

	return _mac_async_read(&descr->dev, buf, len);
}

/**
 * \brief Get next valid package length
 */
uint32_t mac_async_read_len(struct mac_async_descriptor *const descr)
{
	ASSERT(descr);

	return _mac_async_read_len(&descr->dev);
}
/**
 * \brief Enable the MAC IRQ
 */
void mac_async_enable_irq(struct mac_async_descriptor *const descr)
{
	ASSERT(descr);

	_mac_async_enable_irq(&descr->dev);
}

/**
 * \brief Disable the MAC IRQ
 */
void mac_async_disable_irq(struct mac_async_descriptor *const descr)
{
	ASSERT(descr);

	_mac_async_disable_irq(&descr->dev);
}

/**
 * \brief Register the MAC callback function
 */
int32_t mac_async_register_callback(struct mac_async_descriptor *const descr, const enum mac_async_cb_type type,
                                    const FUNC_PTR func)
{
	ASSERT(descr);

	switch (type) {
	case MAC_ASYNC_RECEIVE_CB:
		descr->cb.receive = (mac_async_cb_t)func;
		return _mac_async_register_callback(&descr->dev, type, (func == NULL) ? NULL : (FUNC_PTR)mac_read_cb);
	case MAC_ASYNC_TRANSMIT_CB:
		descr->cb.transmit = (mac_async_cb_t)func;
		return _mac_async_register_callback(&descr->dev, type, (func == NULL) ? NULL : (FUNC_PTR)mac_write_cb);
	default:
		return ERR_INVALID_ARG;
	}
}
/**
 * \brief Set MAC filter
 */
int32_t mac_async_set_filter(struct mac_async_descriptor *const descr, uint8_t index, struct mac_async_filter *filter)
{
	ASSERT(descr && filter);

	return _mac_async_set_filter(&descr->dev, index, filter);
}

/**
 * \brief Set MAC filter (expaneded)
 */
int32_t mac_async_set_filter_ex(struct mac_async_descriptor *const descr, uint8_t mac[6])
{
	ASSERT(descr && mac);

	return _mac_async_set_filter_ex(&descr->dev, mac);
}

/**
 * \brief Write PHY register
 */
int32_t mac_async_write_phy_reg(struct mac_async_descriptor *const descr, uint16_t addr, uint16_t reg, uint16_t val)
{
	ASSERT(descr);

	return _mac_async_write_phy_reg(&descr->dev, addr, reg, val);
}
/**
 * \brief Read PHY register
 */
int32_t mac_async_read_phy_reg(struct mac_async_descriptor *const descr, uint16_t addr, uint16_t reg, uint16_t *val)
{
	ASSERT(descr && val);

	return _mac_async_read_phy_reg(&descr->dev, addr, reg, val);
}
/**
 * \brief Get MAC driver version
 */
uint32_t mac_async_get_version(void)
{
	return DRIVER_VERSION;
}

/**
 * \internal data receivced handler
 *
 * \param[in] dev The pointer to MAC device structure
 */
static void mac_read_cb(struct _mac_async_device *dev)
{
	struct mac_async_descriptor *const descr = CONTAINER_OF(dev, struct mac_async_descriptor, dev);

	if (descr->cb.receive) {
		descr->cb.receive(descr);
	}
}

/**
 * \internal data transmit handler
 *
 * \param[in] dev The pointer to MAC device structure
 */
static void mac_write_cb(struct _mac_async_device *dev)
{
	struct mac_async_descriptor *const descr = CONTAINER_OF(dev, struct mac_async_descriptor, dev);

	if (descr->cb.transmit) {
		descr->cb.transmit(descr);
	}
}
