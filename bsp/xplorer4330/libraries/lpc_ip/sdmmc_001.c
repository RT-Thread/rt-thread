/*
 * @brief	SD/SDIO (MCI) registers and control functions
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

#include "sdmmc_001.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initializes the MCI card controller */
void IP_SDMMC_Init(IP_SDMMC_001_Type *pSDMMC)
{
	/* Software reset */
	pSDMMC->BMOD = MCI_BMOD_SWR;

	/* reset all blocks */
	pSDMMC->CTRL = MCI_CTRL_RESET | MCI_CTRL_FIFO_RESET | MCI_CTRL_DMA_RESET;
	while (pSDMMC->CTRL & (MCI_CTRL_RESET | MCI_CTRL_FIFO_RESET | MCI_CTRL_DMA_RESET)) {}

	/* Internal DMA setup for control register */
	pSDMMC->CTRL = MCI_CTRL_USE_INT_DMAC | MCI_CTRL_INT_ENABLE;
	pSDMMC->INTMASK = 0;

	/* Clear the interrupts for the host controller */
	pSDMMC->RINTSTS = 0xFFFFFFFF;

	/* Put in max timeout */
	pSDMMC->TMOUT = 0xFFFFFFFF;

	/* FIFO threshold settings for DMA, DMA burst of 4,   FIFO watermark at 16 */
	pSDMMC->FIFOTH = MCI_FIFOTH_DMA_MTS_4 | MCI_FIFOTH_RX_WM((SD_FIFO_SZ / 2) - 1) | MCI_FIFOTH_TX_WM(SD_FIFO_SZ / 2);

	/* Enable internal DMA, burst size of 4, fixed burst */
	pSDMMC->BMOD = MCI_BMOD_DE | MCI_BMOD_PBL4 | MCI_BMOD_DSL(4);

	/* disable clock to CIU (needs latch) */
	pSDMMC->CLKENA = 0;
	pSDMMC->CLKSRC = 0;
}

/* Close the MCI */
void IP_SDMMC_DeInit(IP_SDMMC_001_Type *pSDMMC)
{}

/* Set block size for transfer */
void IP_SDMMC_SetBlkSize(IP_SDMMC_001_Type *pSDMMC, uint32_t bytes)
{
	pSDMMC->BLKSIZ = bytes;
}

/* Reset card in slot */
void IP_SDMMC_Reset(IP_SDMMC_001_Type *pSDMMC, int32_t reset)
{
	if (reset) {
		pSDMMC->RST_N = 1;
	}
	else {
		pSDMMC->RST_N = 0;
	}
}

/* Enable or disable slot power */
void IP_SDMMC_PowerOnOff(IP_SDMMC_001_Type *pSDMMC, int32_t enable)
{
	if (enable) {
		pSDMMC->PWREN = 1;
	}
	else {
		pSDMMC->PWREN = 0;
	}
}

/* Detect if write protect is enabled */
int32_t IP_SDMMC_CardWpOn(IP_SDMMC_001_Type *pSDMMC)
{
	if (pSDMMC->WRTPRT & 1) {
		return 1;
	}
	return 0;
}

/* Detect if an SD card is inserted */
int32_t IP_SDMMC_CardNDetect(IP_SDMMC_001_Type *pSDMMC)
{
	/* No card = high state in regsiter */
	if (pSDMMC->CDETECT & 1) {
		return 0;
	}

	return 1;
}

/* Function to send command to Card interface unit (CIU) */
int32_t IP_SDMMC_SendCmd(IP_SDMMC_001_Type *pSDMMC, uint32_t cmd, uint32_t arg)
{
	volatile int32_t tmo = 50;
	volatile int delay;

	/* set command arg reg*/
	pSDMMC->CMDARG = arg;
	pSDMMC->CMD = MCI_CMD_START | cmd;

	/* poll untill command is accepted by the CIU */
	while (--tmo && (pSDMMC->CMD & MCI_CMD_START)) {
		if (tmo & 1) {
			delay = 50;
		}
		else {
			delay = 18000;
		}

		while (--delay > 1) {}
	}

	return (tmo < 1) ? 1 : 0;
}

/* Read the response from the last command */
void IP_SDMMC_GetResponse(IP_SDMMC_001_Type *pSDMMC, uint32_t *resp)
{
	/* on this chip response is not a fifo so read all 4 regs */
	resp[0] = pSDMMC->RESP0;
	resp[1] = pSDMMC->RESP1;
	resp[2] = pSDMMC->RESP2;
	resp[3] = pSDMMC->RESP3;
}

/* Sets the SD bus clock speed */
void IP_SDMMC_SetClock(IP_SDMMC_001_Type *pSDMMC, uint32_t clk_rate, uint32_t speed)
{
	/* compute SD/MMC clock dividers */
	uint32_t div;

	div = ((clk_rate / speed) + 2) >> 1;

	if ((div == pSDMMC->CLKDIV) && pSDMMC->CLKENA) {
		return;	/* Closest speed is already set */

	}
	/* disable clock */
	pSDMMC->CLKENA = 0;

	/* User divider 0 */
	pSDMMC->CLKSRC = MCI_CLKSRC_CLKDIV0;

	/* inform CIU */
	IP_SDMMC_SendCmd(pSDMMC, MCI_CMD_UPD_CLK | MCI_CMD_PRV_DAT_WAIT, 0);

	/* set divider 0 to desired value */
	pSDMMC->CLKDIV = MCI_CLOCK_DIVIDER(0, div);

	/* inform CIU */
	IP_SDMMC_SendCmd(pSDMMC, MCI_CMD_UPD_CLK | MCI_CMD_PRV_DAT_WAIT, 0);

	/* enable clock */
	pSDMMC->CLKENA = MCI_CLKEN_ENABLE;

	/* inform CIU */
	IP_SDMMC_SendCmd(pSDMMC, MCI_CMD_UPD_CLK | MCI_CMD_PRV_DAT_WAIT, 0);
}

/* Function to set card type */
void IP_SDMMC_SetCardType(IP_SDMMC_001_Type *pSDMMC, uint32_t ctype)
{
	pSDMMC->CTYPE = ctype;
}

/* Function to clear interrupt & FIFOs */
void IP_SDMMC_SetClearIntFifo(IP_SDMMC_001_Type *pSDMMC)
{
	/* reset all blocks */
	pSDMMC->CTRL |= MCI_CTRL_FIFO_RESET;

	/* wait till resets clear */
	while (pSDMMC->CTRL & MCI_CTRL_FIFO_RESET) {}

	/* Clear interrupt status */
	pSDMMC->RINTSTS = 0xFFFFFFFF;
}

/* Returns the raw SD interface interrupt status */
uint32_t IP_SDMMC_GetRawIntStatus(IP_SDMMC_001_Type *pSDMMC)
{
	return pSDMMC->RINTSTS;
}

/* Sets the raw SD interface interrupt status */
void IP_SDMMC_SetRawIntStatus(IP_SDMMC_001_Type *pSDMMC, uint32_t iVal)
{
	pSDMMC->RINTSTS = iVal;
}

/* Sets the SD interface interrupt mask */
void IP_SDMMC_SetIntMask(IP_SDMMC_001_Type *pSDMMC, uint32_t iVal)
{
	pSDMMC->INTMASK = iVal;
}

/* Setup DMA descriptors */
void IP_SDMMC_DmaSetup(IP_SDMMC_001_Type *pSDMMC, sdif_device *psdif_dev, uint32_t addr, uint32_t size)
{
	int i = 0;
	uint32_t ctrl, maxs;

	/* Reset DMA */
	pSDMMC->CTRL |= MCI_CTRL_DMA_RESET | MCI_CTRL_FIFO_RESET;
	while (pSDMMC->CTRL & MCI_CTRL_DMA_RESET) {}

	/* Build a descriptor list using the chained DMA method */
	while (size > 0) {
		/* Limit size of the transfer to maximum buffer size */
		maxs = size;
		if (maxs > MCI_DMADES1_MAXTR) {
			maxs = MCI_DMADES1_MAXTR;
		}
		size -= maxs;

		/* Set buffer size */
		psdif_dev->mci_dma_dd[i].des1 = MCI_DMADES1_BS1(maxs);

		/* Setup buffer address (chained) */
		psdif_dev->mci_dma_dd[i].des2 = addr + (i * MCI_DMADES1_MAXTR);

		/* Setup basic control */
		ctrl = MCI_DMADES0_OWN | MCI_DMADES0_CH;
		if (i == 0) {
			ctrl |= MCI_DMADES0_FS;	/* First DMA buffer */

		}
		/* No more data? Then this is the last descriptor */
		if (!size) {
			ctrl |= MCI_DMADES0_LD;
		}
		else {
			ctrl |= MCI_DMADES0_DIC;
		}

		/* Another descriptor is needed */
		psdif_dev->mci_dma_dd[i].des3 = (uint32_t) &psdif_dev->mci_dma_dd[i + 1];
		psdif_dev->mci_dma_dd[i].des0 = ctrl;

		i++;
	}

	/* Set DMA derscriptor base address */
	pSDMMC->DBADDR = (uint32_t) &psdif_dev->mci_dma_dd[0];
}

/**
 * @brief	Sets the transfer block size
 * @param	pSDMMC		: Pointer to IP_SDMMC_001_Type structure
 * @param	blk_size	: Block Size value
 * @return	None
 */
void IP_SDMMC_SetBlockSize(IP_SDMMC_001_Type *pSDMMC, uint32_t blk_size)
{
	/* set block size and byte count */
	pSDMMC->BLKSIZ = blk_size;
	pSDMMC->BYTCNT = blk_size;
}
