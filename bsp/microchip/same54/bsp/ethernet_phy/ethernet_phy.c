/**
 * \file
 *
 * \brief Ethernet PHY functionality implementation.
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

#include <ethernet_phy.h>
#include <utils_assert.h>
/**
 * \brief Perform a HW initialization to the PHY
 */
int32_t ethernet_phy_init(struct ethernet_phy_descriptor *const descr, struct mac_async_descriptor *const mac,
                          uint16_t addr)
{
	ASSERT(descr && mac && (addr <= 0x1F));

	descr->mac  = mac;
	descr->addr = addr;
	return ERR_NONE;
}

/**
 * \brief Set PHY address
 */
int32_t ethernet_phy_set_address(struct ethernet_phy_descriptor *const descr, uint16_t addr)
{
	ASSERT(descr && (addr <= 0x1F));

	descr->addr = addr;
	return ERR_NONE;
}

/**
 * \brief Read PHY Register value.
 */
int32_t ethernet_phy_read_reg(struct ethernet_phy_descriptor *const descr, uint16_t reg, uint16_t *val)
{
	ASSERT(descr && descr->mac && (reg <= 0x1F) && val);

	return mac_async_read_phy_reg(descr->mac, descr->addr, reg, val);
}

/**
 * \brief Write PHY Register value.
 */
int32_t ethernet_phy_write_reg(struct ethernet_phy_descriptor *const descr, uint16_t reg, uint16_t val)
{
	ASSERT(descr && descr->mac && (reg <= 0x1F));
	return mac_async_write_phy_reg(descr->mac, descr->addr, reg, val);
}

/**
 * \brief Setting bit for a PHY Register
 */
int32_t ethernet_phy_set_reg_bit(struct ethernet_phy_descriptor *const descr, uint16_t reg, uint16_t ofst)
{
	int32_t  rst;
	uint16_t val;

	ASSERT(descr && descr->mac && (reg <= 0x1F));

	rst = mac_async_read_phy_reg(descr->mac, descr->addr, reg, &val);
	if (rst == ERR_NONE) {
		val |= ofst;
		rst = mac_async_write_phy_reg(descr->mac, descr->addr, reg, val);
	}
	return rst;
}
/**
 * \brief Clear bit for a PHY Register
 */
int32_t ethernet_phy_clear_reg_bit(struct ethernet_phy_descriptor *const descr, uint16_t reg, uint16_t ofst)
{
	int32_t  rst;
	uint16_t val;

	ASSERT(descr && (reg <= 0x1F));

	rst = mac_async_read_phy_reg(descr->mac, descr->addr, reg, &val);
	if (rst == ERR_NONE) {
		val &= ~ofst;
		rst = mac_async_write_phy_reg(descr->mac, descr->addr, reg, val);
	}
	return rst;
}
/**
 * \brief Set PHY low-power consumption state.
 */
int32_t ethernet_phy_set_powerdown(struct ethernet_phy_descriptor *const descr, bool state)
{
	ASSERT(descr);
	if (state) {
		return ethernet_phy_set_reg_bit(descr, MDIO_REG0_BMCR, MDIO_REG0_BIT_POWER_DOWN);
	} else {
		return ethernet_phy_clear_reg_bit(descr, MDIO_REG0_BMCR, MDIO_REG0_BIT_POWER_DOWN);
	}
}

/**
 * \brief Set PHY electrically isolate state.
 */
int32_t ethernet_phy_set_isolate(struct ethernet_phy_descriptor *const descr, bool state)
{
	ASSERT(descr);
	if (state) {
		return ethernet_phy_set_reg_bit(descr, MDIO_REG0_BMCR, MDIO_REG0_BIT_ISOLATE);
	} else {
		return ethernet_phy_clear_reg_bit(descr, MDIO_REG0_BMCR, MDIO_REG0_BIT_ISOLATE);
	}
}

/**
 * \brief Restart an auto negotiation of the PHY.
 */
int32_t ethernet_phy_restart_autoneg(struct ethernet_phy_descriptor *const descr)
{
	ASSERT(descr);
	return ethernet_phy_set_reg_bit(descr, MDIO_REG0_BMCR, MDIO_REG0_BIT_RESTART_AUTONEG);
}

/**
 * \brief Set PHY placed in a loopback mode of operation.
 */
int32_t ethernet_phy_set_loopback(struct ethernet_phy_descriptor *const descr, bool state)
{
	ASSERT(descr);
	if (state) {
		return ethernet_phy_set_reg_bit(descr, MDIO_REG0_BMCR, MDIO_REG0_BIT_LOOPBACK);
	} else {
		return ethernet_phy_clear_reg_bit(descr, MDIO_REG0_BMCR, MDIO_REG0_BIT_LOOPBACK);
	}
}

/**
 * \brief Get PHY link status
 */
int32_t ethernet_phy_get_link_status(struct ethernet_phy_descriptor *const descr, bool *status)
{
	int32_t  rst;
	uint16_t val;

	ASSERT(descr && descr->mac && status);
	rst = mac_async_read_phy_reg(descr->mac, descr->addr, MDIO_REG1_BMSR, &val);
	if (rst == ERR_NONE) {
		*status = (val & MDIO_REG1_BIT_LINK_STATUS) ? true : false;
	}
	return rst;
}

/**
 * \brief Reset PHY.
 */
int32_t ethernet_phy_reset(struct ethernet_phy_descriptor *const descr)
{
	ASSERT(descr);
	return ethernet_phy_set_reg_bit(descr, MDIO_REG0_BMCR, MDIO_REG0_BIT_RESET);
}
