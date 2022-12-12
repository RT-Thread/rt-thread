/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file or main.c
 * to avoid loosing it when reconfiguring.
 */

#include <atmel_start.h>
#include <ieee8023_mii_standard_config.h>
#include <ethernet_phy_main.h>

struct ethernet_phy_descriptor MACIF_PHY_desc;

void MACIF_PHY_init(void)
{
	mac_async_enable(&MACIF);
	ethernet_phy_init(&MACIF_PHY_desc, &MACIF, CONF_MACIF_PHY_IEEE8023_MII_PHY_ADDRESS);
#if CONF_MACIF_PHY_IEEE8023_MII_CONTROL_REG0_SETTING == 1
	ethernet_phy_write_reg(&MACIF_PHY_desc, MDIO_REG0_BMCR, CONF_MACIF_PHY_IEEE8023_MII_CONTROL_REG0);
#endif /* CONF_MACIF_PHY_IEEE8023_MII_CONTROL_REG0_SETTING */
}

void MACIF_PHY_example(void)
{
	bool    link_state;
	int32_t rst;
	/* Restart an auto-negotiation */
	rst = ethernet_phy_restart_autoneg(&MACIF_PHY_desc);
	while (rst != ERR_NONE) {
	}

	/* Wait for PHY link up */
	do {
		rst = ethernet_phy_get_link_status(&MACIF_PHY_desc, &link_state);
	} while (rst == ERR_NONE && link_state == true);
}

void ethernet_phys_init(void)
{

	MACIF_PHY_init();
}
