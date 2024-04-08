/*
 * @brief LPC82x DMA chip driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
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

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/* DMA SRAM table - this can be optionally used with the Chip_DMA_SetSRAMBase()
   function if a DMA SRAM table is needed. This table is correctly aligned for
     the DMA controller. */
#ifdef __ICCARM__
#define ASTR(str)  #str
#define ALIGN(x) _Pragma(ASTR(data_alignment=##x))
#else
#define ALIGN(x) __attribute__((aligned(x)))
#endif

/* Alignment of 512 bytes */
#define DMA_ALIGN ALIGN(512)
DMA_ALIGN DMA_CHDESC_T Chip_DMA_Table[MAX_DMA_CHANNEL];

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

void ChipEz_DMA_Init(uint32_t isEnableIRQ)
{
	Chip_DMA_Init(LPC_DMA);
	Chip_DMA_Enable(LPC_DMA);
	Chip_DMA_SetSRAMBase(LPC_DMA, DMA_ADDR(Chip_DMA_Table));
	if (isEnableIRQ)
    	NVIC_EnableIRQ(DMA_IRQn);

}

 /**
  * Initialize DMA parameters specific to a channel 
  * 
  * @param channel
  * @param src_address
  * @param dst_address
  * @param xfr_width
  * @param length_bytes
  */
 void ChipEz_DMA_InitChannel( DMA_CHID_T channel, uint32_t src_address, uint32_t src_increment,
		 uint32_t dst_address, uint32_t dst_increment, uint32_t xfr_width, uint32_t length_bytes, uint32_t priority) 
 {
   Chip_DMA_EnableChannel(LPC_DMA, channel);
   Chip_DMA_EnableIntChannel(LPC_DMA, channel);
 
   Chip_DMA_SetupChannelConfig(LPC_DMA, channel, DMA_CFG_PERIPHREQEN |
		   DMA_CFG_CHPRIORITY(priority));
 
   if (src_increment != DMA_XFERCFG_SRCINC_0) {
	 Chip_DMA_Table[channel].source = DMA_ADDR((src_address + length_bytes)
			 - (1UL << xfr_width));
   } else {
	 Chip_DMA_Table[channel].source = DMA_ADDR(src_address);
   }
 
   if (dst_increment != DMA_XFERCFG_DSTINC_0) {
	 Chip_DMA_Table[channel].dest = DMA_ADDR((dst_address + length_bytes)
			 - (1UL << xfr_width));
   } else {
	 Chip_DMA_Table[channel].dest = DMA_ADDR(dst_address);
   }
   Chip_DMA_Table[channel].next = DMA_ADDR(0);
 
 }
 
 /**
  * Start the DMA transfer 
  * 
  * @param channel
  * @param src_increment
  * @param dst_increment
  * @param xfr_width
  * @param length_bytes
  */
 void ChipEz_DMA_StartTransfer(DMA_CHID_T channel, uint32_t src_increment, uint32_t dst_increment, uint32_t xfr_width, uint32_t length_bytes) 
 {
   uint32_t xfer_count;
 
   /* Calculate transfer_count ( length in terms of transfers) */
   xfer_count = (xfr_width == DMA_XFERCFG_WIDTH_8) ? length_bytes :
		   (xfr_width == DMA_XFERCFG_WIDTH_16) ? (length_bytes >> 1) :
		   (length_bytes >> 2);
 
   Chip_DMA_SetupChannelTransfer(LPC_DMA, channel,
		   (DMA_XFERCFG_CFGVALID | DMA_XFERCFG_SETINTA | DMA_XFERCFG_SWTRIG |
		   xfr_width | src_increment | dst_increment |
		   DMA_XFERCFG_XFERCOUNT(xfer_count)));
 }

bool ChipEzr_DMA_Transfer( DMA_CHID_T channel, uint32_t src_address, uint32_t src_increment,
		uint32_t dst_address, uint32_t dst_increment, uint32_t xfr_width, uint32_t length_bytes, uint32_t priority) 
{
	if ((Chip_DMA_GetBusyChannels(LPC_DMA) & (1 << channel)) != 0)
		return FALSE;
	ChipEz_DMA_InitChannel(channel, src_address, src_increment, dst_address, dst_increment, xfr_width, length_bytes, priority);
	ChipEz_DMA_StartTransfer(channel, src_increment, dst_increment, xfr_width, length_bytes);
	return TRUE;
}

void ChipEz_DMA_AbortChannel(DMA_CHID_T ch) {
	 Chip_DMA_DisableChannel(LPC_DMA, ch);
	 while ((Chip_DMA_GetBusyChannels(LPC_DMA) & (1 << ch)) != 0) {}
	 Chip_DMA_AbortChannel(LPC_DMA, ch);
	 Chip_DMA_ClearErrorIntChannel(LPC_DMA, ch);
}

