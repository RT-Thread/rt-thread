/*
 * @brief Ethernet control functions
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

#include "enet_001.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* Saved address for PHY and clock divider */
STATIC uint32_t phyCfg;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Resets ethernet interface */
void IP_ENET_Reset(IP_ENET_001_Type *LPC_ENET)
{
	/* This should be called prior to IP_ENET_Init. The MAC controller may
	   not be ready for a call to init right away so a small delay should
	   occur after this call. */
	LPC_ENET->DMA_BUS_MODE |= DMA_BM_SWR;
}

/* Sets the address of the interface */
void IP_ENET_SetADDR(IP_ENET_001_Type *LPC_ENET, const uint8_t *macAddr)
{
	/* Save MAC address */
	LPC_ENET->MAC_ADDR0_LOW = ((uint32_t) macAddr[3] << 24) |
							  ((uint32_t) macAddr[2] << 16) | ((uint32_t) macAddr[1] << 8) |
							  ((uint32_t) macAddr[0]);
	LPC_ENET->MAC_ADDR0_HIGH = ((uint32_t) macAddr[5] << 8) |
							   ((uint32_t) macAddr[4]);
}

/* Initialize ethernet interface */
void IP_ENET_Init(IP_ENET_001_Type *LPC_ENET)
{
	/* Enhanced descriptors, burst length = 1 */
	LPC_ENET->DMA_BUS_MODE = DMA_BM_ATDS | DMA_BM_PBL(1) | DMA_BM_RPBL(1);

	/* Initial MAC configuration for checksum offload, full duplex,
	   100Mbps, disable receive own in half duplex, inter-frame gap
	   of 64-bits */
	LPC_ENET->MAC_CONFIG = MAC_CFG_BL(0) | MAC_CFG_IPC | MAC_CFG_DM |
						   MAC_CFG_DO | MAC_CFG_FES | MAC_CFG_PS | MAC_CFG_IFG(3);

	/* Setup default filter */
	LPC_ENET->MAC_FRAME_FILTER = MAC_FF_PR | MAC_FF_RA;

	/* Flush transmit FIFO */
	LPC_ENET->DMA_OP_MODE = DMA_OM_FTF;

	/* Setup DMA to flush receive FIFOs at 32 bytes, service TX FIFOs at
	   64 bytes */
	LPC_ENET->DMA_OP_MODE |= DMA_OM_RTC(1) | DMA_OM_TTC(0);

	/* Clear all MAC interrupts */
	LPC_ENET->DMA_STAT = DMA_ST_ALL;

	/* Enable MAC interrupts */
	LPC_ENET->DMA_INT_EN = 0;
}

/* Sets up the PHY link clock divider and PHY address */
void IP_ENET_SetupMII(IP_ENET_001_Type *LPC_ENET, uint32_t div, uint8_t addr)
{
	/* Save clock divider and PHY address in MII address register */
	phyCfg = MAC_MIIA_PA(addr) | MAC_MIIA_CR(div);
}

/*De-initialize the ethernet interface */
void IP_ENET_DeInit(IP_ENET_001_Type *LPC_ENET)
{
	/* Disable packet reception */
	LPC_ENET->MAC_CONFIG = 0;

	/* Flush transmit FIFO */
	LPC_ENET->DMA_OP_MODE = DMA_OM_FTF;

	/* Disable receive and transmit DMA processes */
	LPC_ENET->DMA_OP_MODE = 0;
}

/* Starts a PHY write via the MII */
void IP_ENET_StartMIIWrite(IP_ENET_001_Type *LPC_ENET, uint8_t reg, uint16_t data)
{
	/* Write value at PHY address and register */
	LPC_ENET->MAC_MII_ADDR = phyCfg | MAC_MIIA_GR(reg) | MAC_MIIA_W;
	LPC_ENET->MAC_MII_DATA = (uint32_t) data;
	LPC_ENET->MAC_MII_ADDR |= MAC_MIIA_GB;
}

/*Starts a PHY read via the MII */
void IP_ENET_StartMIIRead(IP_ENET_001_Type *LPC_ENET, uint8_t reg)
{
	/* Read value at PHY address and register */
	LPC_ENET->MAC_MII_ADDR = phyCfg | MAC_MIIA_GR(reg);
	LPC_ENET->MAC_MII_ADDR |= MAC_MIIA_GB;
}

/* Returns MII link (PHY) busy status */
bool IP_ENET_IsMIIBusy(IP_ENET_001_Type *LPC_ENET)
{
	if (LPC_ENET->MAC_MII_ADDR & MAC_MIIA_GB) {
		return true;
	}

	return false;
}

/* Enables or disables ethernet transmit */
void IP_ENET_TXEnable(IP_ENET_001_Type *LPC_ENET, bool Enable)
{
	if (Enable) {
		/* Descriptor list head pointers must be setup prior to enable */
		LPC_ENET->MAC_CONFIG |= MAC_CFG_TE;
		LPC_ENET->DMA_OP_MODE |= DMA_OM_ST;
	}
	else {
		LPC_ENET->MAC_CONFIG &= ~MAC_CFG_TE;
	}
}

/* Enables or disables ethernet packet reception */
void IP_ENET_RXEnable(IP_ENET_001_Type *LPC_ENET, bool Enable)
{
	if (Enable) {
		/* Descriptor list head pointers must be setup prior to enable */
		LPC_ENET->MAC_CONFIG |= MAC_CFG_RE;
		LPC_ENET->DMA_OP_MODE |= DMA_OM_SR;
	}
	else {
		LPC_ENET->MAC_CONFIG &= ~MAC_CFG_RE;
	}
}

/* Sets full or half duplex for the interface */
void IP_ENET_SetDuplex(IP_ENET_001_Type *LPC_ENET, bool full)
{
	if (full) {
		LPC_ENET->MAC_CONFIG |= MAC_CFG_DM;
	}
	else {
		LPC_ENET->MAC_CONFIG &= ~MAC_CFG_DM;
	}
}

/* Sets speed for the interface */
void IP_ENET_SetSpeed(IP_ENET_001_Type *LPC_ENET, bool speed100)
{
	if (speed100) {
		LPC_ENET->MAC_CONFIG |= MAC_CFG_FES;
	}
	else {
		LPC_ENET->MAC_CONFIG &= ~MAC_CFG_FES;
	}
}

/* Configures the initial ethernet descriptors */
void IP_ENET_InitDescriptors(IP_ENET_001_Type *LPC_ENET,
							 IP_ENET_001_ENHTXDESC_Type *pTXDescs, IP_ENET_001_ENHRXDESC_Type *pRXDescs)
{
	/* Setup descriptor list base addresses */
	LPC_ENET->DMA_TRANS_DES_ADDR = (uint32_t) pTXDescs;
	LPC_ENET->DMA_REC_DES_ADDR = (uint32_t) pRXDescs;
}
