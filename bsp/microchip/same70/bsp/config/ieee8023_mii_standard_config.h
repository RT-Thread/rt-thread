/* Auto-generated config file ieee8023_mii_standard_config.h */
#ifndef IEEE8023_MII_STANDARD_CONFIG_H
#define IEEE8023_MII_STANDARD_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Basic configuration

// <o> PHY Address <0-31>
// <i> The PHY Address is five bits, allowing 32 unique PHY addresses. A PHY
// <i> that is connected to the station management entity via the mechanical
// <i> interface defined in IEEE 802.3 22.6 shall always respond to
// <i> transactions addressed to PHY Address zero b00000. A station management
// <i> entity that is attached to multiple PHYs must have prior knowledge of
// <i> the appropriate PHY Address for each PHY.
// <id> ieee8023_mii_phy_address
#ifndef CONF_MACIF_PHY_IEEE8023_MII_PHY_ADDRESS
#define CONF_MACIF_PHY_IEEE8023_MII_PHY_ADDRESS 0
#endif

// </h>

// <e> Control Register (Register 0) Settings
// <i> The MII Management Interface Control Register (Register 0) Setting.
// <i> Full details about the can be found in Clause 22.2.4 of the IEEE 802.3
// <i> Specification.
// <id> ieee8023_mii_control_reg0_setting
#ifndef CONF_MACIF_PHY_IEEE8023_MII_CONTROL_REG0_SETTING
#define CONF_MACIF_PHY_IEEE8023_MII_CONTROL_REG0_SETTING 1
#endif

// <q> Loopback Enable
// <i> Set PHY be placed in a loopback mode of operation.
// <id> ieee8023_mii_control_loopback_en
#ifndef CONF_MACIF_PHY_IEEE8023_MII_CONTROL_LOOPBACK_EN
#define CONF_MACIF_PHY_IEEE8023_MII_CONTROL_LOOPBACK_EN 0
#endif

// <o> Speed Selection
// <i> These bits select the PHY speed.
// <0x0=> 10 Mb/s
// <0x1=> 100 Mb/s
// <0x2=> 1000 Mb/s
// <id> ieee8023_mii_control_speed_lsb
#ifndef CONF_MACIF_PHY_IEEE8023_MII_CONTROL_SPEED
#define CONF_MACIF_PHY_IEEE8023_MII_CONTROL_SPEED 1
#endif

// <q> Auto-Negotiation Enable
// <i> Indicates whether the Auto-Negotiation enable or not
// <id> ieee8023_mii_control_autoneg_en
#ifndef CONF_MACIF_PHY_IEEE8023_MII_CONTROL_AUTONEG_EN
#define CONF_MACIF_PHY_IEEE8023_MII_CONTROL_AUTONEG_EN 1
#endif

// <q> Power Down Enable
// <i> Set PHY in a low-power consumption state, The specific behavior of a
// <i> PHY in the power-down state is implementation specific. While in the
// <i> power-down state, the PHY shall respond to management transactions.
// <i> During the transition to the power-down state and while in the
// <i> power-down state, the PHY shall not generate spurious signals on the
// <i> MII or GMII.
// <id> ieee8023_mii_control_powerdown_en
#ifndef CONF_MACIF_PHY_IEEE8023_MII_CONTROL_POWER_DOWN_EN
#define CONF_MACIF_PHY_IEEE8023_MII_CONTROL_POWER_DOWN_EN 0
#endif

// <q> Isolate Enable
// <i> Set PHY forced to electrically isolate its data paths from the MII or
// <i> GMII. When the PHY is isolated from the MII or GMII it shall not
// <i> respond to the TXD data bundle, TX_EN, TX_ER and GTX_CLK inputs, and it
// <i> shall present a high impedance on its TX_CLK, RX_CLK, RX_DV, RX_ER, RXD
// <i> data bundle, COL, and CRS outputs. When the PHY is isolated from the
// <i> MII or GMII it shall respond to management transactions.
// <id> ieee8023_mii_control_isolate_en
#ifndef CONF_MACIF_PHY_IEEE8023_MII_CONTROL_ISOLATE_EN
#define CONF_MACIF_PHY_IEEE8023_MII_CONTROL_ISOLATE_EN 0
#endif

// <o> Duplex Mode Selection
// <i> The duplex mode can be selected via either the Auto-Negotiation enable,
// <i> or manual duplex selection. Manual duplex selection is allowed when
// <i> Auto-Negotiation is disabled. When Auto-Negotiation is enabled, this
// <i> setting has no effect on the link configuration.
// <0x0=> half duplex
// <0x1=> full duplex
// <id> ieee8023_mii_control_duplex_mode
#ifndef CONF_MACIF_PHY_IEEE8023_MII_CONTROL_DUPLEX_MODE
#define CONF_MACIF_PHY_IEEE8023_MII_CONTROL_DUPLEX_MODE 1
#endif

#ifndef CONF_MACIF_PHY_IEEE8023_MII_CONTROL_REG0
#define CONF_MACIF_PHY_IEEE8023_MII_CONTROL_REG0                                                                       \
	(CONF_MACIF_PHY_IEEE8023_MII_CONTROL_LOOPBACK_EN ? MDIO_REG0_BIT_RESET : 0)                                        \
	    | ((CONF_MACIF_PHY_IEEE8023_MII_CONTROL_SPEED & 0x1) ? MDIO_REG0_BIT_SPEED_SELECT_LSB : 0)                     \
	    | ((CONF_MACIF_PHY_IEEE8023_MII_CONTROL_SPEED & 0x2) ? MDIO_REG0_BIT_SPEED_SELECT_MSB : 0)                     \
	    | (CONF_MACIF_PHY_IEEE8023_MII_CONTROL_AUTONEG_EN ? MDIO_REG0_BIT_AUTONEG : 0)                                 \
	    | (CONF_MACIF_PHY_IEEE8023_MII_CONTROL_POWER_DOWN_EN ? MDIO_REG0_BIT_POWER_DOWN : 0)                           \
	    | (CONF_MACIF_PHY_IEEE8023_MII_CONTROL_ISOLATE_EN ? MDIO_REG0_BIT_ISOLATE : 0)                                 \
	    | (CONF_MACIF_PHY_IEEE8023_MII_CONTROL_DUPLEX_MODE ? MDIO_REG0_BIT_DUPLEX_MODE : 0)
#endif
// </e>

// <<< end of configuration section >>>

#endif // IEEE8023_MII_STANDARD_CONFIG_H
