/*
 * @brief Mational DP83848 simple PHY driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "chip.h"
#include "lpc_phy.h"

/** @defgroup DP83848_PHY	BOARD: PHY status and control driver for the DP83848
 * @ingroup BOARD_PHY
 * Various functions for controlling and monitoring the status of the
 * DP83848 PHY.
 * @{
 */

/** @brief  DP83848 PHY register offsets */
#define DP8_BMCR_REG        0x0	/*!< Basic Mode Control Register */
#define DP8_BMSR_REG        0x1	/*!< Basic Mode Status Reg */
#define DP8_ANADV_REG       0x4	/*!< Auto_Neg Advt Reg  */
#define DP8_ANLPA_REG       0x5	/*!< Auto_neg Link Partner Ability Reg */
#define DP8_ANEEXP_REG      0x6	/*!< Auto-neg Expansion Reg  */
#define DP8_PHY_STAT_REG    0x10/*!< PHY Status Register  */
#define DP8_PHY_INT_CTL_REG 0x11/*!< PHY Interrupt Control Register */
#define DP8_PHY_RBR_REG     0x17/*!< PHY RMII and Bypass Register  */
#define DP8_PHY_STS_REG     0x19/*!< PHY Status Register  */

/* DP83848 Control register definitions */
#define DP8_RESET          (1 << 15)	/*!< 1= S/W Reset */
#define DP8_LOOPBACK       (1 << 14)	/*!< 1=loopback Enabled */
#define DP8_SPEED_SELECT   (1 << 13)	/*!< 1=Select 100MBps */
#define DP8_AUTONEG        (1 << 12)	/*!< 1=Enable auto-negotiation */
#define DP8_POWER_DOWN     (1 << 11)	/*!< 1=Power down PHY */
#define DP8_ISOLATE        (1 << 10)	/*!< 1=Isolate PHY */
#define DP8_RESTART_AUTONEG (1 << 9)	/*!< 1=Restart auto-negoatiation */
#define DP8_DUPLEX_MODE    (1 << 8)		/*!< 1=Full duplex mode */
#define DP8_COLLISION_TEST (1 << 7)		/*!< 1=Perform collsion test */

/* DP83848 Status register definitions */
#define DP8_100BASE_T4     (1 << 15)	/*!< T4 mode */
#define DP8_100BASE_TX_FD  (1 << 14)	/*!< 100MBps full duplex */
#define DP8_100BASE_TX_HD  (1 << 13)	/*!< 100MBps half duplex */
#define DP8_10BASE_T_FD    (1 << 12)	/*!< 100Bps full duplex */
#define DP8_10BASE_T_HD    (1 << 11)	/*!< 10MBps half duplex */
#define DP8_MF_PREAMB_SUPPR (1 << 6)	/*!< Preamble suppress */
#define DP8_AUTONEG_COMP   (1 << 5)		/*!< Auto-negotation complete */
#define DP8_RMT_FAULT      (1 << 4)		/*!< Fault */
#define DP8_AUTONEG_ABILITY (1 << 3)	/*!< Auto-negotation supported */
#define DP8_LINK_STATUS    (1 << 2)		/*!< 1=Link active */
#define DP8_JABBER_DETECT  (1 << 1)		/*!< Jabber detect */
#define DP8_EXTEND_CAPAB   (1 << 0)		/*!< Supports extended capabilities */

/* DP83848 PHY RBR MII dode definitions */
#define DP8_RBR_RMII_MODE  (1 << 5)		/*!< Use RMII mode */

/* DP83848 PHY status definitions */
#define DP8_REMOTEFAULT    (1 << 6)		/*!< Remote fault */
#define DP8_FULLDUPLEX     (1 << 2)		/*!< 1=full duplex */
#define DP8_SPEED10MBPS    (1 << 1)		/*!< 1=10MBps speed */
#define DP8_VALID_LINK     (1 << 0)		/*!< 1=Link active */

/* DP83848 PHY ID register definitions */
#define DP8_PHYID1_OUI     0x2000		/*!< Expected PHY ID1 */
#define DP8_PHYID2_OUI     0x5c90		/*!< Expected PHY ID2 */

/* DP83848 PHY update flags */
static uint32_t physts, olddphysts;

/* PHY update counter for state machine */
static int32_t phyustate;

/* Pointer to delay function used for this driver */
static p_msDelay_func_t pDelayMs;

/* Write to the PHY. Will block for delays based on the pDelayMs function. Returns
   true on success, or false on failure */
static Status lpc_mii_write(uint8_t reg, uint16_t data)
{
	Status sts = ERROR;
	int32_t mst = 250;

	/* Write value for register */
	Chip_ENET_Start_MII_Write(reg, data);

	/* Wait for unbusy status */
	while (mst > 0) {
		if (Chip_ENET_Is_MII_Busy()) {
			mst--;
			pDelayMs(1);
		}
		else {
			mst = 0;
			sts = SUCCESS;
		}
	}

	return sts;
}

/* Read from the PHY. Will block for delays based on the pDelayMs function. Returns
   true on success, or false on failure */
static Status lpc_mii_read(uint8_t reg, uint16_t *data)
{
	Status sts = ERROR;
	int32_t mst = 250;

	/* Start register read */
	Chip_ENET_Start_MII_Read(reg);

	/* Wait for unbusy status */
	while (mst > 0) {
		if (!Chip_ENET_Is_MII_Busy()) {
			mst = 0;
			*data = Chip_ENET_Read_MII_Data();
			sts = SUCCESS;
		}
		else {
			mst--;
			pDelayMs(1);
		}
	}

	return sts;
}

/* Update PHY status from passed value */
static void lpc_update_phy_sts(uint16_t linksts)
{
	/* Update link active status */
	if (linksts & DP8_VALID_LINK) {
		physts |= PHY_LINK_CONNECTED;
	}
	else {
		physts &= ~PHY_LINK_CONNECTED;
	}

	/* Full or half duplex */
	if (linksts & DP8_FULLDUPLEX) {
		physts |= PHY_LINK_FULLDUPLX;
	}
	else {
		physts &= ~PHY_LINK_FULLDUPLX;
	}

	/* Configure 100MBit/10MBit mode. */
	if (linksts & DP8_SPEED10MBPS) {
		physts &= ~PHY_LINK_SPEED100;
	}
	else {
		physts |= PHY_LINK_SPEED100;
	}

	/* If the status has changed, indicate via change flag */
	if ((physts & (PHY_LINK_SPEED100 | PHY_LINK_FULLDUPLX | PHY_LINK_CONNECTED)) !=
		(olddphysts & (PHY_LINK_SPEED100 | PHY_LINK_FULLDUPLX | PHY_LINK_CONNECTED))) {
		olddphysts = physts;
		physts |= PHY_LINK_CHANGED;
	}
}

/* Initialize the DP83848 PHY */
uint32_t lpc_phy_init(bool rmii, p_msDelay_func_t pDelayMsFunc)
{
	uint16_t tmp;
	int32_t i;

	pDelayMs = pDelayMsFunc;

	/* Initial states for PHY status and state machine */
	olddphysts = physts = phyustate = 0;

	/* Only first read and write are checked for failure */
	/* Put the DP83848C in reset mode and wait for completion */
	if (lpc_mii_write(DP8_BMCR_REG, DP8_RESET) != SUCCESS) {
		return ERROR;
	}
	i = 400;
	while (i > 0) {
		pDelayMs(1);
		if (lpc_mii_read(DP8_BMCR_REG, &tmp) != SUCCESS) {
			return ERROR;
		}

		if (!(tmp & (DP8_RESET | DP8_POWER_DOWN))) {
			i = -1;
		}
		else {
			i--;
		}
	}
	/* Timeout? */
	if (i == 0) {
		return ERROR;
	}

#if 0
	/* Setup link based on configuration options */
#if PHY_USE_AUTONEG == 1
	tmp = DP8_AUTONEG;
#else
	tmp = 0;
#endif
#if PHY_USE_100MBS == 1
	tmp |= DP8_SPEED_SELECT;
#endif
#if PHY_USE_FULL_DUPLEX == 1
	tmp |= DP8_DUPLEX_MODE;
#endif

#else
	tmp = DP8_AUTONEG;
#endif

	lpc_mii_write(DP8_BMCR_REG, tmp);

	/* Enable RMII mode for PHY */
	if (rmii) {
		lpc_mii_write(DP8_PHY_RBR_REG, DP8_RBR_RMII_MODE);
	}

	/* The link is not set active at this point, but will be detected
	   later */

	return SUCCESS;
}

/* Phy status update state machine */
uint32_t lpcPHYStsPoll(void)
{
	switch (phyustate) {
	default:
	case 0:
		/* Read BMSR to clear faults */
		Chip_ENET_Start_MII_Read(DP8_PHY_STAT_REG);
		physts &= ~PHY_LINK_CHANGED;
		physts = physts | PHY_LINK_BUSY;
		phyustate = 1;
		break;

	case 1:
		/* Wait for read status state */
		if (!Chip_ENET_Is_MII_Busy()) {
			/* Update PHY status */
			physts &= ~PHY_LINK_BUSY;
			lpc_update_phy_sts(Chip_ENET_Read_MII_Data());
			phyustate = 0;
		}
		break;
	}

	return physts;
}

/**
 * @}
 */
