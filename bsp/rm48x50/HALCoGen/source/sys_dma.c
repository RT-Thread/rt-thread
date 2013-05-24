/** @file dma.c 
*   @brief DMA Driver Inmplmentation File
*   @date 23.May.2013
*   @version 03.05.01
*
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */


#include "sys_dma.h"


/** @fn void dmaEnable(void)
*   @brief enables DMA module
*
*   This function brings DMA out of reset
*/
void dmaEnable(void)
{
  dmaREG->GCTRL  = 0x00000001U; /* reset dma       */
  dmaREG->GCTRL |= 0x00010000U; /* enable dma      */
  dmaREG->GCTRL |= 0x00000300U; /* stop at suspend */   
}

/** @fn void dmaDisable(void)
*   @brief disables DMA module
*
*   This function disables DMA module
*/
void dmaDisable(void)
{
    /* Wait until DMA's external bus has completed data transfer */
	while((dmaREG->GCTRL & DMA_GCTRL_BUSBUSY) != 0U)
    { 
	} /* Wait */
    /* Disable DMA module */
	dmaREG->GCTRL = 0U;
}


/** @fn void dmaReqAssign(uint32 channel,uint32 reqline)
*   @brief Initializes the DMA Driver
*   @param[in] channel DMA channel
*   @param[in] reqline DMA request line
*
*   This function assigns dma request lines to channels
*/
void dmaReqAssign(uint32 channel,uint32 reqline)
{
    register uint32 i=0U,j=0U;

    i = channel >> 2U;              /* Find the register to configure */
    j = channel -(i<<2U);           /* Find the offset of the type    */
    j = 3U-j;                       /* reverse the byte order         */
    j = j<<3U;                      /* find the bit location          */

    /* mapping channel 'i' to request line 'j' */
    dmaREG->DREQASI[i] &= ~(0xffU<<j);   
    dmaREG->DREQASI[i] |= (reqline<<j);
}


/** @fn uint32 dmaGetReq(uint32 channel)
*   @brief Gets the request line number mapped to the selected channel
*   @param[in] channel DMA channel
*
*   This function returns the request line number mapped to the selected channel
*/
uint32 dmaGetReq(uint32 channel)
{
	register uint32 i=0U,j=0U;

    i = channel >> 2U;              /* Find the register to configure */
    j = channel -(i<<2U);           /* Find the offset of the type    */
    j = 3U-j;                       /* reverse the byte order         */
    j = j<<3U;                      /* find the bit location          */
    return ((dmaREG->DREQASI[i] >> j) &0xffU);
}


/** @fn void dmaSetCtrlPacket(uint32 channel)
*   @brief Initializes the DMA Driver
*
*   This function sets control packet
*/
void dmaSetCtrlPacket(uint32 channel, g_dmaCTRL g_dmaCTRLPKT)
{
    register uint32 i=0U,j=0U;
    
    dmaRAMREG->PCP[channel].ISADDR  =  g_dmaCTRLPKT.SADD;
    
    dmaRAMREG->PCP[channel].IDADDR  =  g_dmaCTRLPKT.DADD;
    
    dmaRAMREG->PCP[channel].ITCOUNT = (g_dmaCTRLPKT.FRCNT << 16U) | g_dmaCTRLPKT.ELCNT;
  
    dmaRAMREG->PCP[channel].CHCTRL  = (g_dmaCTRLPKT.RDSIZE    << 14U) | (g_dmaCTRLPKT.WRSIZE    << 12U) | (g_dmaCTRLPKT.TTYPE << 8U)| \
                                      (g_dmaCTRLPKT.ADDMODERD << 3U ) | (g_dmaCTRLPKT.ADDMODEWR << 1U ) | (g_dmaCTRLPKT.AUTOINIT);

    dmaRAMREG->PCP[channel].CHCTRL |= (g_dmaCTRLPKT.CHCTRL << 16U);

    dmaRAMREG->PCP[channel].EIOFF   = (g_dmaCTRLPKT.ELDOFFSET << 16U) | (g_dmaCTRLPKT.ELSOFFSET);
  
    dmaRAMREG->PCP[channel].FIOFF   = (g_dmaCTRLPKT.FRDOFFSET << 16U) | (g_dmaCTRLPKT.FRSOFFSET);

    i = channel >> 3U;                /* Find the register to write                    */
    j = channel -(i << 3U);           /* Find the offset of the 4th bit                */
    j = 7U -j;                        /* Reverse the order of the 4th bit offset       */
    j = j<<2U;                        /* Find the bit location of the 4th bit to write */

    dmaREG->PAR[i] &= ~(0xfU<<j);
    dmaREG->PAR[i] |= (g_dmaCTRLPKT.PORTASGN<<j);
}



/** @fn void dmaSetChEnable(uint32 channel,uint32 type)
*   @brief Enable channel
*   @param[in] channel DMA channel
*   @param[in] type Type of triggering
*                    - DMA_HW: Enables the selected DMA channel for hardware triggering
*                    - DMA_SW: Enables the selected DMA channel for software triggering
*
*   This function enables the DMA channel for hardware or software triggering
*/
void dmaSetChEnable(uint32 channel,uint32 type)
{
    if(type == DMA_HW)
    {
     dmaREG->HWCHENAS = (1U << channel);
    }
    else if(type == DMA_SW)
    {
     dmaREG->SWCHENAS = (1U << channel);
    }
	else
	{
    /** Empty  */
	}	
}



/** @fn void dmaSetPriority(uint32 channel, dmaPRIORITY_t priority)
*   @brief Assign Priority to the channel
*   @param[in] channel DMA channel
*   @param[in] priority Priority queue to which channel needs to be assigned
*                        - LOWPRIORITY : The selected channel will be assigned to low priority queue
*                        - HIGHPRIORITY: The selected channel will be assigned to high priority queue
*
*   This function assigns the selected priority to the selected channel
*/
void dmaSetPriority(uint32 channel, dmaPRIORITY_t priority)
{
	if (priority == LOWPRIORITY)
	{
		dmaREG->CHPRIOR |= 1U << channel;
	}
	else
	{
		dmaREG->CHPRIOS |= 1U << channel;
	}
}


/** @fn void dmaEnableInterrupt(uint32 channel, dmaInterrupt_t inttype)
*   @brief Enable selected interrupt
*   @param[in] channel DMA channel
*   @param[in] inttype Interrupt to be enabled
*                       - FTC: Frame Transfer Complete Interrupt will be disabled for the selected channel
*                       - LFS: Last Frame Transfer Started Interrupt will be disabled for the selected channel
*                       - HBC: First Half Of Block Complete Interrupt will be disabled for the selected channel
*                       - BTC: Block transfer complete Interrupt will be disabled for the selected channel
*                       - BER: Bus Error Interrupt will be disabled for the selected channel
*
*   This function enables the selected interrupt for the selected channel
*/
void dmaEnableInterrupt(uint32 channel, dmaInterrupt_t inttype)
{
	dmaREG->GCHIENAS = 1 << channel;
	
	switch (inttype)
	{
	case FTC: 	dmaREG->FTCINTENAS |= 1U << channel;
				break;
	case LFS:	dmaREG->LFSINTENAS |= 1U << channel;
				break;
	case HBC:	dmaREG->HBCINTENAS |= 1U << channel;
				break;
	case BTC:	dmaREG->BTCINTENAS |= 1U << channel;
				break;
	default :
	            break;
	}
}



/** @fn void dmaDisableInterrupt(uint32 channel, dmaInterrupt_t inttype)
*   @brief Disable selected interrupt
*   @param[in] channel DMA channel
*   @param[in] inttype Interrupt to be disabled
*                       - FTC: Frame Transfer Complete Interrupt will be disabled for the selected channel
*                       - LFS: Last Frame Transfer Started Interrupt will be disabled for the selected channel
*                       - HBC: First Half Of Block Complete Interrupt will be disabled for the selected channel
*                       - BTC: Block transfer complete Interrupt will be disabled for the selected channel
*                       - BER: Bus Error Interrupt will be disabled for the selected channel
*
*   This function disables the selected interrupt for the selected channel
*/
void dmaDisableInterrupt(uint32 channel, dmaInterrupt_t inttype)
{
	switch (inttype)
	{
	case FTC: 	dmaREG->FTCINTENAR |= 1U << channel;
				break;
	case LFS:	dmaREG->LFSINTENAR |= 1U << channel;
				break;
	case HBC:	dmaREG->HBCINTENAR |= 1U << channel;
				break;
	case BTC:	dmaREG->BTCINTENAR |= 1U << channel;
				break;
	default :
	            break;				
	}
}



/** @fn void dmaDefineRegion(dmaREGION_t region, uint32 start_add, uint32 end_add)
*   @brief Configure start and end address of the region
*   @param[in] region Memory Region
*                     - DMA_REGION0
*                     - DMA_REGION1
*                     - DMA_REGION2
*                     - DMA_REGION3
*   @param[in] start_add Start address of the the region
*   @param[in] end_add End address of the region
*
*   This function configure start and end address of the selected region
*/
void dmaDefineRegion(dmaREGION_t region, uint32 start_add, uint32 end_add)
{
	dmaREG->DMAMPR[region].STARTADD = start_add;
	dmaREG->DMAMPR[region].ENDADD = end_add;
}



/** @fn void dmaEnableRegion(dmaREGION_t region, dmaRegionAccess_t access, boolean intenable)
*   @brief Enable the selected region
*   @param[in] region Memory Region
*                     - DMA_REGION0
*                     - DMA_REGION1
*                     - DMA_REGION2
*                     - DMA_REGION3
*   @param[in] access Access permission of the selected region
*                      - FULLACCESS
*                      - READONLY
*                      - WRITEONLY
*                      - NOACCESS
*   @param[in] intenable Interrupt to be enabled or not
*                         - INTERRUPT_ENABLE : Enable interrupt for the selected region
*                         - INTERRUPT_DISABLE: Disable interrupt for the selected region
*
*   This function enables the selected region with selected access permission with or without interrupt enable
*/
void dmaEnableRegion(dmaREGION_t region, dmaRegionAccess_t access, boolean intenable)
{
    /* Enable the region */
	dmaREG->DMAMPCTRL |= 1U << (region*8U);
    /* Set access permission for the region */
	dmaREG->DMAMPCTRL |= access << ((region*8U) + 1U);
    /* Enable or Disable interrupt */
	dmaREG->DMAMPCTRL |= intenable << ((region*8U) + 3U);
}



/** @fn void dmaDisableRegion(dmaREGION_t region)
*   @brief Disable the selected region
*   @param[in] region Memory Region
*                     - DMA_REGION0
*                     - DMA_REGION1
*                     - DMA_REGION2
*                     - DMA_REGION3
*
*   This function disables the selected region(no address checking done).
*/
void dmaDisableRegion(dmaREGION_t region)
{
	dmaREG->DMAMPCTRL &= ~(1U << (region*8U));
}



/** @fn void dmaEnableParityCheck(void)
*   @brief Enable Parity Check
*
*   This function enables parit check
*/
void dmaEnableParityCheck(void)
{
	dmaREG->DMAPCR = 0x5U;
}



/** @fn void dmaDisableParityCheck(void)
*   @brief Disable Parity Check
*
*   This function disables parity check
*/
void dmaDisableParityCheck(void)
{
	dmaREG->DMAPCR = 0xAU;
}





