/**
 * \file
 *
 * \brief Ethernet PHY functionality declaration.
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

#ifndef ETHERNET_PHY_H_INCLUDED
#define ETHERNET_PHY_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "compiler.h"
#include "hal_mac_async.h"
#include "ieee8023_mii_standard_register.h"

struct ethernet_phy_descriptor {
	struct mac_async_descriptor *mac;  /* MAC descriptor handler */
	uint16_t                     addr; /* PHY address, defined by IEEE802.3
	                                      section 22.2.4.5.5 */
};

/**
 * \brief Perform a HW initialization to the PHY
 *
 * This should be called only once to initialize the PHY pre-settings.
 *
 * \param[in] descr Ethernet PHY descriptor.
 * \param[in] mac   MAC descriptor, the descriptor should be initialized.
 * \param[in] addr  Ethernet PHY 5 bits address.
 *
 * \return Operation result
 * \retval ERR_NONE initializing successful.
 */
int32_t ethernet_phy_init(struct ethernet_phy_descriptor *const descr, struct mac_async_descriptor *const mac,
                          uint16_t addr);

/**
 * \brief Set PHY address
 *
 * Set PHY management PHY address which defined by IEEE802.3 section 22.2.4.5.5
 *
 * \param[in] descr Ethernet PHY descriptor.
 * \param[in] addr  PHY address
 *
 * \return Operation result
 * \retval ERR_NONE Set address successful.
 */
int32_t ethernet_phy_set_address(struct ethernet_phy_descriptor *const descr, uint16_t addr);

/**
 * \brief Read PHY Register value.
 *
 * Read PHY Register value from PHY.
 *
 * \note For conformance with the 802.3 specification, MDC must not exceed
 *       2.5 MHz (MDC is only active during MDIO read and write operations).
 *       The function execution time depend on MDC frequency.
 *
 * \param[in]  descr Ethernet PHY descriptor.
 * \param[in]  reg   Register address
 * \param[out] val   Register value
 *
 * \return Operation result.
 * \retval ERR_NONE Read register successful.
 */
int32_t ethernet_phy_read_reg(struct ethernet_phy_descriptor *const descr, uint16_t reg, uint16_t *val);

/**
 * \brief Write PHY Register value.
 *
 * Read PHY Register value from PHY.
 *
 * \note For conformance with the 802.3 specification, MDC must not exceed
 *       2.5 MHz (MDC is only active during MDIO read and write operations).
 *       The function execution time depend on MDC frequency.
 *
 * \param[in]  descr Ethernet PHY descriptor.
 * \param[in]  reg   Register address
 * \param[out] val   Register value
 *
 * \return Operation result.
 * \retval ERR_NONE Write register successful.
 */
int32_t ethernet_phy_write_reg(struct ethernet_phy_descriptor *const descr, uint16_t reg, uint16_t val);

/**
 * \brief Setting bit for a PHY Register
 *
 * Bit setting for a PHY Register.
 *
 * \param[in] descr Ethernet PHY descriptor.
 * \param[in] reg   Register address.
 * \param[in] ofst  Register bit mask.
 *
 * \return Operation result.
 * \retval ERR_NONE Set register bit successful.
 */
int32_t ethernet_phy_set_reg_bit(struct ethernet_phy_descriptor *const descr, uint16_t reg, uint16_t ofst);

/**
 * \brief Clear bit for a PHY Register
 *
 * Clear bit for a PHY Register.
 *
 * \param[in] descr Ethernet PHY descriptor.
 * \param[in] reg   Register address.
 * \param[in] ofst  Register bit mask.
 *
 * \return Operation result.
 * \retval ERR_NONE Clear register bit successful.
 */
int32_t ethernet_phy_clear_reg_bit(struct ethernet_phy_descriptor *const descr, uint16_t reg, uint16_t ofst);

/**
 * \brief Set PHY low-power consumption state.
 *
 * The specific behavior of a PHY in the power-down state is implementation
 * specific. While in the power-down state, the PHY shall respond to management
 * transactions. During the transition to the power-down state and while in the
 * power-down state, the PHY shall not generate spurious signals on the MII or
 * GMII.
 *
 * \param[in] descr Ethernet PHY descriptor.
 * \param[in] state The state of the power-down mode.
 *
 * \return Operation result.
 * \retval ERR_NONE Power-Down has been config successful.
 */
int32_t ethernet_phy_set_powerdown(struct ethernet_phy_descriptor *const descr, bool state);

/**
 * \brief Set PHY electrically isolate state.
 *
 * When the PHY is isolated from the MII or RMII it shall not respond to the
 * data bundle.
 *
 * \param[in] descr Ethernet PHY descriptor.
 * \param[in] state The state of the isolate mode.
 *
 * \return Operation result.
 * \retval ERR_NONE Isolate has been config successful.
 */
int32_t ethernet_phy_set_isolate(struct ethernet_phy_descriptor *const descr, bool state);

/**
 * \brief Restart an auto negotiation of the PHY.
 *
 * Restart Auto_Negotantion process
 *
 * \param[in] descr Ethernet PHY descriptor.
 *
 * \return Operation result
 * \retval ERR_NONE Auto-Negotiation has been initiated.
 */
int32_t ethernet_phy_restart_autoneg(struct ethernet_phy_descriptor *const descr);

/**
 * \brief Set PHY placed in a loopback mode of operation.
 *
 * When in loopback mode, the PHY shall accept data from the MII/RMII transmit
 * data path and return it to the MII/RMII receive data path.
 *
 * \param[in] descr Ethernet PHY descriptor.
 * \param[in] state State of the loopback mode.
 *
 * \return Operation result
 * \retval ERR_NONE Loopback has been set successful.
 */
int32_t ethernet_phy_set_loopback(struct ethernet_phy_descriptor *const descr, bool state);

/**
 * \brief Get PHY link status
 *
 * Get PHY link status
 *
 * \param[in]  descr  Ethernet PHY descriptor.
 * \param[out] status Pointer to the Link Status.
 *
 * \return ERR_NONE if successfully
 */
int32_t ethernet_phy_get_link_status(struct ethernet_phy_descriptor *const descr, bool *status);

/**
 * \brief Reset PHY.
 *
 * Resetting PHY, this action set all the status and control register to their
 * default states. As a consequence this action may change the internal state
 * of the PHY and the state of the physical link associated with the PHY. The
 * reset process shall be completed within 0.5 second.
 *
 * \param[in] descr Ethernet PHY descriptor.
 *
 * \return ERR_NONE if successfully
 */
int32_t ethernet_phy_reset(struct ethernet_phy_descriptor *const descr);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ETHERNET_PHY_H_INCLUDED */
