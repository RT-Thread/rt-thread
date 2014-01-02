/**********************************************************************
* $Id$      lpc_emac.c          2011-06-02
*//**
* @file     lpc_emac.c
* @brief    Contains all functions support for Ethernet MAC firmware
*           library on LPC
* @version  1.0
* @date     02. June. 2011
* @author   NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/
#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc_libcfg.h"
#else
#include "lpc_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */
#ifdef _EMAC

#include "lpc_emac.h"
#include "lpc_clkpwr.h"
#include "lpc_pinsel.h"

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup EMAC
 * @{
 */
 
/************************** PRIVATE VARIABLES *************************/


/* MII Mgmt Configuration register - Clock divider setting */
const uint8_t EMAC_clkdiv[] = { 4, 6, 8, 10, 14, 20, 28, 36, 40, 44, 48, 52, 56, 60, 64 };

/* EMAC Config data */
static EMAC_CFG_Type EMAC_Configs;


/* EMAC local DMA Descriptors */


#ifdef __IAR_SYSTEMS_ICC__
/* Global Tx Buffer data */
#pragma data_alignment=4
static uint16_t saFrameBuffers[EMAC_MAX_FRAME_NUM][EMAC_MAX_FRAME_SIZE];
#else
/* Global Rx Buffer data */
static uint16_t __attribute__ ((aligned (4))) saFrameBuffers[EMAC_MAX_FRAME_NUM][EMAC_MAX_FRAME_SIZE];
#endif
static uint32_t sulCurrFrameSz = 0;
static uint8_t  sbCurrFrameID = 0;

/***************************** PRIVATE FUNCTION *****************************/
static void EMAC_UpdateRxConsumeIndex(void);
static void EMAC_UpdateTxProduceIndex(void);
static uint32_t EMAC_AllocTxBuff(uint16_t nFrameSize, uint8_t bLastFrame);
static uint32_t EMAC_GetRxFrameSize(void);


/*********************************************************************//**
 * @brief
 * @param[in]
 * @return
 **********************************************************************/
void rx_descr_init (void)
{
    unsigned int i;

    for (i = 0; i < EMAC_NUM_RX_FRAG; i++)
    {
        RX_DESC_PACKET(i)  = RX_BUF(i);
        RX_DESC_CTRL(i)    = EMAC_RCTRL_INT | (EMAC_ETH_MAX_FLEN-1);
        RX_STAT_INFO(i)    = 0;
        RX_STAT_HASHCRC(i) = 0;
    }

    /* Set EMAC Receive Descriptor Registers. */
    LPC_EMAC->RxDescriptor    = RX_DESC_BASE;
    LPC_EMAC->RxStatus        = RX_STAT_BASE;
    LPC_EMAC->RxDescriptorNumber = EMAC_NUM_RX_FRAG-1;

    /* Rx Descriptors Point to 0 */
    LPC_EMAC->RxConsumeIndex  = 0;
}

/*********************************************************************//**
 * @brief
 * @param[in]
 * @return
 **********************************************************************/
void tx_descr_init (void)
{
    unsigned int i;

    for (i = 0; i < EMAC_NUM_TX_FRAG; i++)
    {
        TX_DESC_PACKET(i) = TX_BUF(i);
        TX_DESC_CTRL(i)   = 0;
        TX_STAT_INFO(i)   = 0;
    }

    /* Set EMAC Transmit Descriptor Registers. */
    LPC_EMAC->TxDescriptor    = TX_DESC_BASE;
    LPC_EMAC->TxStatus        = TX_STAT_BASE;
    LPC_EMAC->TxDescriptorNumber = EMAC_NUM_TX_FRAG-1;

    /* Tx Descriptors Point to 0 */
    LPC_EMAC->TxProduceIndex  = 0;
}

/*********************************************************************//**
 * @brief       Set Station MAC address for EMAC module
 * @param[in]   abStationAddr Pointer to Station address that contains 6-bytes
 *              of MAC address.
 * @return      None
 **********************************************************************/
void setEmacAddr(uint8_t abStationAddr[])
{
    /* Set the Ethernet MAC Address registers */
    LPC_EMAC->SA0 = ((uint32_t)abStationAddr[5] << 8) | (uint32_t)abStationAddr[4];
    LPC_EMAC->SA1 = ((uint32_t)abStationAddr[3] << 8) | (uint32_t)abStationAddr[2];
    LPC_EMAC->SA2 = ((uint32_t)abStationAddr[1] << 8) | (uint32_t)abStationAddr[0];
}


/************************** GLOBAL/PUBLIC FUNCTIONS *************************/

/** @defgroup EMAC_Public_Functions
 * @{
 */

/*********************************************************************//**
 * @brief          Write data to PHY
 * @param[in]  PhyReg    PHY register address
 * @param[in]  Value       Register Value
 * @return        None
 **********************************************************************/
void EMAC_Write_PHY (uint8_t PhyReg, uint16_t Value)
{
    unsigned int tout;

    LPC_EMAC->MADR = ((EMAC_Configs.bPhyAddr & 0x1F) << 8 )| (PhyReg & 0x1F);
    LPC_EMAC->MWTD = Value;

    /* Wait utill operation completed */
    tout = 0;

    for (tout = 0; tout < EMAC_MII_WR_TOUT; tout++)
    {
        if ((LPC_EMAC->MIND & EMAC_MIND_BUSY) == 0)
        {
            break;
        }
    }
}

/*********************************************************************//**
 * @brief          Read data from PHY register
 * @param[in]  PhyReg    PHY register address
 * @return        Register value
 **********************************************************************/
uint16_t EMAC_Read_PHY (uint8_t PhyReg)
{
    unsigned int tout;

    LPC_EMAC->MADR = ((EMAC_Configs.bPhyAddr & 0x1F) << 8 )| (PhyReg & 0x1F);
    LPC_EMAC->MCMD = EMAC_MCMD_READ;

    /* Wait until operation completed */
    tout = 0;
    for (tout = 0; tout < EMAC_MII_RD_TOUT; tout++)
    {
        if ((LPC_EMAC->MIND & EMAC_MIND_BUSY) == 0)
        {
            break;
        }
    }

    LPC_EMAC->MCMD = 0;
    return (LPC_EMAC->MRDD);
}

/*********************************************************************//**
 * @brief         Set Full/Half Duplex Mode
 * @param[in]  full_duplex    0: Half-duplex, 1: Full-duplex
 * @return        None
 **********************************************************************/
void EMAC_SetFullDuplexMode(uint8_t full_duplex)
{
  if(full_duplex)
  {
        LPC_EMAC->MAC2    |= EMAC_MAC2_FULL_DUP;
    LPC_EMAC->Command |= EMAC_CR_FULL_DUP;
    LPC_EMAC->IPGT     = EMAC_IPGT_FULL_DUP;
  }
  else
  {
        LPC_EMAC->IPGT = EMAC_IPGT_HALF_DUP;
  }
}
/*********************************************************************//**
 * @brief         Set PHY Speed
 * @param[in]  mode_100Mbps    0: 10Mbps, 1: 100Mbps
 * @return        None
 **********************************************************************/
void EMAC_SetPHYSpeed(uint8_t mode_100Mbps)
{
  if(mode_100Mbps)
  {
     LPC_EMAC->SUPP = EMAC_SUPP_SPEED;
  }
  else
  {
     LPC_EMAC->SUPP = 0;
  }
}


/*********************************************************************//**
 * @brief       Initializes the EMAC peripheral according to the specified
*               parameters in the EMAC_ConfigStruct.
 * @param[in]   EMAC_ConfigStruct Pointer to a EMAC_CFG_Type structure
*                    that contains the configuration information for the
*                    specified EMAC peripheral.
 * @return      None
 *
 * Note: This function will initialize EMAC module according to procedure below:
 *  - Remove the soft reset condition from the MAC
 *  - Configure the PHY via the MIIM interface of the MAC
 *  - Select RMII mode
 *  - Configure the transmit and receive DMA engines, including the descriptor arrays
 *  - Configure the host registers (MAC1,MAC2 etc.) in the MAC
 *  - Enable the receive and transmit data paths
 *  In default state after initializing,  Rx Done and Tx Done interrupt are enabled,
 *  nad all  interrupts are also enabled
 *  (Ref. from LPC17xx UM)
 **********************************************************************/
int32_t EMAC_Init(EMAC_CFG_Type *EMAC_ConfigStruct)
{
    /* Initialize the EMAC Ethernet controller. */
    volatile int32_t tout, tmp;

    EMAC_Configs = *EMAC_ConfigStruct;

    /* Set up power for Ethernet module */
    CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCENET, ENABLE);

    /* Enable P1 Ethernet Pins. */

    /* Reset all EMAC internal modules */
    LPC_EMAC->MAC1    = EMAC_MAC1_RES_TX | EMAC_MAC1_RES_MCS_TX | EMAC_MAC1_RES_RX |
                    EMAC_MAC1_RES_MCS_RX | EMAC_MAC1_SIM_RES | EMAC_MAC1_SOFT_RES;

    LPC_EMAC->Command = EMAC_CR_REG_RES | EMAC_CR_TX_RES | EMAC_CR_RX_RES | EMAC_CR_PASS_RUNT_FRM;

    /* A short delay after reset. */
    for (tout = 100; tout; tout--);

    /* Initialize MAC control registers. */
    LPC_EMAC->MAC1 = EMAC_MAC1_PASS_ALL;
    LPC_EMAC->MAC2 = EMAC_MAC2_CRC_EN | EMAC_MAC2_PAD_EN;
    LPC_EMAC->MAXF = EMAC_ETH_MAX_FLEN;
    /*
     * Find the clock that close to desired target clock
     */
    tmp = CLKPWR_GetCLK(CLKPWR_CLKTYPE_CPU)/ EMAC_MCFG_MII_MAXCLK;
    for (tout = 0; tout < sizeof (EMAC_clkdiv); tout++)
    {
        if (EMAC_clkdiv[tout] >= tmp)
            break;
    }

        if(tout >= sizeof (EMAC_clkdiv))
        return ERROR;
    tout++;

    // Set Frame size
    LPC_EMAC->MAXF = EMAC_ConfigStruct->nMaxFrameSize;

    // Write to MAC configuration register and reset
    LPC_EMAC->MCFG = EMAC_MCFG_CLK_SEL(tout) | EMAC_MCFG_RES_MII;

    // release reset
    LPC_EMAC->MCFG &= ~(EMAC_MCFG_RES_MII);
    LPC_EMAC->CLRT = EMAC_CLRT_DEF;
    LPC_EMAC->IPGR = EMAC_IPGR_P2_DEF;

    /* Enable Reduced MII interface. */
    LPC_EMAC->Command = EMAC_CR_RMII | EMAC_CR_PASS_RUNT_FRM;


    // Initilialize PHY
    if(EMAC_ConfigStruct->pfnPHYInit != NULL)
    {
        if(EMAC_ConfigStruct->pfnPHYInit(&EMAC_ConfigStruct->PhyCfg) != SUCCESS)
        {
        return ERROR;
        }
    }

    // Set EMAC address
    setEmacAddr(EMAC_ConfigStruct->pbEMAC_Addr);

    /* Initialize Tx and Rx DMA Descriptors */
    rx_descr_init ();
    tx_descr_init ();

    // Set Receive Filter register: enable broadcast and multicast
    LPC_EMAC->RxFilterCtrl = EMAC_RFC_MCAST_EN | EMAC_RFC_BCAST_EN | EMAC_RFC_PERFECT_EN;

    /* Enable Rx Done and Tx Done interrupt for EMAC */
    EMAC_IntCmd((EMAC_INT_RX_OVERRUN | EMAC_INT_RX_ERR | EMAC_INT_RX_FIN \
            | EMAC_INT_RX_DONE | EMAC_INT_TX_UNDERRUN | EMAC_INT_TX_ERR \
            | EMAC_INT_TX_FIN | EMAC_INT_TX_DONE), ENABLE);

    /* Reset all interrupts */
    LPC_EMAC->IntClear  = 0xFFFF;

    /* Enable receive and transmit mode of MAC Ethernet core */
    EMAC_TxEnable();
    EMAC_RxEnable();

    NVIC_EnableIRQ(ENET_IRQn);

    return SUCCESS;
}


/*********************************************************************//**
 * @brief       De-initializes the EMAC peripheral registers to their
*                  default reset values.
 * @param[in]   None
 * @return      None
 **********************************************************************/
void EMAC_DeInit(void)
{
    // Disable all interrupt
    LPC_EMAC->IntEnable = 0x00;

    // Clear all pending interrupt
    LPC_EMAC->IntClear = (0xFF) | (EMAC_INT_SOFT_INT | EMAC_INT_WAKEUP);

    LPC_EMAC->Command = 0;

    /* TurnOff power for Ethernet module */
    CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCENET, DISABLE);
}

/*********************************************************************//**
 * @brief       EMAC TX API modules
 * @param[in]   None
 * @return      None
 **********************************************************************/
void EMAC_TxEnable( void )
{
    LPC_EMAC->Command |= EMAC_CR_TX_EN;
    return;
}


/*********************************************************************//**
 * @brief       EMAC RX API modules
 * @param[in]   None
 * @return      None
 **********************************************************************/
void EMAC_TxDisable( void )
{
    LPC_EMAC->Command &= ~EMAC_CR_TX_EN;
    return;
}

/*********************************************************************//**
 * @brief       EMAC RX API modules
 * @param[in]   None
 * @return      None
 **********************************************************************/
void EMAC_RxEnable( void )
{
    LPC_EMAC->Command |= EMAC_CR_RX_EN;
    LPC_EMAC->MAC1 |= EMAC_MAC1_REC_EN;
    return;
}

/*********************************************************************//**
 * @brief       EMAC RX API modules
 * @param[in]   None
 * @return      None
 **********************************************************************/
void EMAC_RxDisable( void )
{
    LPC_EMAC->Command &= ~EMAC_CR_RX_EN;
    LPC_EMAC->MAC1 &= ~EMAC_MAC1_REC_EN;
    return;
}

/*********************************************************************//**
 * @brief       Get the status of  given buffer.
 * @param[in]    idx   Buffer index
 * @return   EMAC_BUFF_AVAILABLE/EMAC_BUFF_FULL/EMAC_BUFF_PARTIAL_FULL
 *
 **********************************************************************/
EMAC_BUFF_STATUS EMAC_GetBufferSts(EMAC_BUFF_IDX idx)
{
    uint32_t consume_idx, produce_idx;
    uint32_t max_frag_num;

    // Get the consume index, produce index and the buffer size
    if(idx == EMAC_TX_BUFF)
    {
        consume_idx = LPC_EMAC->TxConsumeIndex;
        produce_idx = LPC_EMAC->TxProduceIndex;
        max_frag_num = LPC_EMAC->TxDescriptorNumber + 1;
    }
    else
    {
        consume_idx = LPC_EMAC->RxConsumeIndex;
        produce_idx = LPC_EMAC->RxProduceIndex;
        max_frag_num = LPC_EMAC->RxDescriptorNumber + 1;
    }

    // empty
    if(consume_idx == produce_idx)
        return EMAC_BUFF_EMPTY;

    // Full
    if(consume_idx == 0 &&
        produce_idx == max_frag_num - 1)
        return EMAC_BUFF_FULL;
    
    // Wrap-around
    if(consume_idx == produce_idx + 1)
        return EMAC_BUFF_FULL;  

    return EMAC_BUFF_PARTIAL_FULL;
}

/*********************************************************************//**
 * @brief       Allocate a descriptor for sending frame and get the coressponding buffer address
 * @param[in]   FrameSize       The size of frame you want to send
 * @return  Address of the TX_DESC_PACKET buffer
 **********************************************************************/
 uint32_t EMAC_AllocTxBuff(uint16_t nFrameSize, uint8_t bLastFrame)
{
    uint32_t idx;
    uint32_t  dp;
    volatile uint32_t i;

    idx = LPC_EMAC->TxProduceIndex;

    while(EMAC_GetBufferSts(EMAC_TX_BUFF) == EMAC_BUFF_FULL)
    {
      for(i = 0; i < 1000000; i++) ; 
    }

    dp = TX_DESC_PACKET(idx);

    if(bLastFrame)
      TX_DESC_CTRL(idx) = ((nFrameSize-1) & EMAC_TCTRL_SIZE) | (EMAC_TCTRL_INT | EMAC_TCTRL_LAST);
    else
      TX_DESC_CTRL(idx) = ((nFrameSize-1) & EMAC_TCTRL_SIZE) | (EMAC_TCTRL_INT);

    return dp;
}

/*********************************************************************//**
 * @brief   Increase the TxProduceIndex (after writting to the Transmit buffer
 *      to enable the Transmit buffer) and wrap-around the index if
 *          it reaches the maximum Transmit Number
 * @param[in]   None
 * @return      None
 **********************************************************************/
void EMAC_UpdateTxProduceIndex(void)
{
    // Get current Tx produce index
    uint32_t idx = LPC_EMAC->TxProduceIndex;

    /* Start frame transmission */
    if (++idx == LPC_EMAC->TxDescriptorNumber + 1) idx = 0;
    LPC_EMAC->TxProduceIndex = idx;
}

/*********************************************************************//**
 * @brief   Get current status value of receive data (due to TxProduceIndex)
 * @param[in]   None    
 * @return  Current value of receive data (due to TxProduceIndex)
 **********************************************************************/
uint32_t EMAC_GetTxFrameStatus(void)
{
    uint32_t idx;

    idx = LPC_EMAC->TxProduceIndex;
    return (TX_STAT_INFO(idx));
}

/*********************************************************************//**
 * @brief   Write data to Tx packet data buffer at current index due to
 *              TxProduceIndex
 * @param[in]   pDataStruct store the address and the size of buffer that saves data.
 * @return      None
 **********************************************************************/
void EMAC_WritePacketBuffer(EMAC_PACKETBUF_Type *pDataStruct)
{
   uint16_t* pDest;
   uint16_t* pSource = (uint16_t*)pDataStruct->pbDataBuf;
   uint32_t  size = pDataStruct->ulDataLen;
   int32_t  frame_num;
   uint32_t tmp;
   uint32_t max_frame_size = LPC_EMAC->MAXF;
   
   size = (size + 1) & 0xFFFE;    // round Size up to next even number
   frame_num = size/max_frame_size;

   if(size == 0)
    return;

   while(frame_num >= 0)
   {
     tmp = (frame_num > 0)? max_frame_size:size;

     if(tmp == 0)
        break;
     
     // Setup descriptors and data
     if(frame_num == 0)
       pDest = (uint16_t*)EMAC_AllocTxBuff(tmp, 1);  // last frame
     else
       pDest = (uint16_t*)EMAC_AllocTxBuff(tmp, 0);
     
     // Copy data
     while (tmp > 0)
     {
       *pDest++ = *pSource++;
       tmp -= 2;
     }
     frame_num--;
     size -= tmp;

     // Update produce index
     EMAC_UpdateTxProduceIndex();
   } 
}


/*********************************************************************//**
 * @brief       Get current status value of receive data (due to RxConsumeIndex)
 * @param[in]   None    
 * @return  Current value of receive data (due to RxConsumeIndex)
 **********************************************************************/
uint32_t EMAC_GetRxFrameStatus(void)
{
    uint32_t idx;

    idx = LPC_EMAC->RxConsumeIndex;
    return (RX_STAT_INFO(idx));
}


/*********************************************************************//**
 * @brief       Get size of current Received data in received buffer (due to
 *              RxConsumeIndex)
 * @param[in]   None
 * @return      Size of received data
 **********************************************************************/
uint32_t EMAC_GetRxFrameSize(void)
{
    uint32_t idx;

    idx = LPC_EMAC->RxConsumeIndex;

    return (((RX_STAT_INFO(idx)) & EMAC_RINFO_SIZE)+1);
}


/*********************************************************************//**
 * @brief       Get the address of TX_DESC_PACKET buffer so that user can access from application
 * @param[in] None
 * @return  Address of the TX_DESC_PACKET buffer
 **********************************************************************/

uint32_t EMAC_GetRxBuffer(void)
{
    uint32_t idx;

    idx = LPC_EMAC->RxConsumeIndex;

    return RX_DESC_PACKET(idx);
 }


/*********************************************************************//**
 * @brief       Increase the RxConsumeIndex (after reading the Receive buffer
 *              to release the Receive buffer) and wrap-around the index if
 *              it reaches the maximum Receive Number
 * @param[in]   None
 * @return      None
 **********************************************************************/
void EMAC_UpdateRxConsumeIndex(void)
{
    // Get current Rx consume index
    uint32_t idx = LPC_EMAC->RxConsumeIndex;

    /* Release frame from EMAC buffer */
    if (++idx == EMAC_NUM_RX_FRAG) idx = 0;

    LPC_EMAC->RxConsumeIndex = idx;
}

/*********************************************************************//**
 * @brief       Standard EMAC IRQ Handler. This sub-routine will check
 *              these following interrupt and call the call-back function
 *              if they're already installed:
 *              - Overrun Error interrupt in RX Queue
 *              - Receive Error interrupt: AlignmentError, RangeError,
 *              LengthError, SymbolError, CRCError or NoDescriptor or Overrun
 *              - RX Finished Process Descriptors interrupt (ProduceIndex == ConsumeIndex)
 *              - Receive Done interrupt: Read received frame to the internal buffer
 *              - Transmit Under-run interrupt
 *              - Transmit errors interrupt : LateCollision, ExcessiveCollision
 *              and ExcessiveDefer, NoDescriptor or Under-run
 *              - TX Finished Process Descriptors interrupt (ProduceIndex == ConsumeIndex)
 *              - Transmit Done interrupt
 *              - Interrupt triggered by software
 *              - Interrupt triggered by a Wakeup event detected by the receive filter
 * @param[in]   None
 * @return      None
 **********************************************************************/
void ENET_IRQHandler(void)
{
    /* EMAC Ethernet Controller Interrupt function. */
    uint32_t int_stat;
    int32_t RxLen;
    
    // Get EMAC interrupt status
    while ((int_stat = (LPC_EMAC->IntStatus & LPC_EMAC->IntEnable)) != 0)
    {
        // Clear interrupt status
        LPC_EMAC->IntClear = int_stat;
     
        if(int_stat & (EMAC_INT_RX_OVERRUN |EMAC_INT_RX_ERR ))
        {
           uint32_t ulFrameSts = EMAC_GetRxFrameStatus();
           uint32_t ulErrCode = 0;

           ulErrCode |= (ulFrameSts & EMAC_RINFO_CRC_ERR) ? EMAC_CRC_ERR:0;
           ulErrCode |= (ulFrameSts & EMAC_RINFO_SYM_ERR) ? EMAC_SYMBOL_ERR:0;
           ulErrCode |= (ulFrameSts & EMAC_RINFO_LEN_ERR) ? EMAC_LENGTH_ERR:0;
           ulErrCode |= (ulFrameSts & EMAC_RINFO_ALIGN_ERR) ? EMAC_ALIGN_ERR:0;
           ulErrCode |= (ulFrameSts & EMAC_RINFO_OVERRUN) ? EMAC_OVERRUN_ERR:0;
           ulErrCode |= (ulFrameSts & EMAC_RINFO_NO_DESCR) ? EMAC_RX_NO_DESC_ERR:0;
           ulErrCode |= (ulFrameSts & EMAC_RINFO_FAIL_FILT) ? EMAC_FILTER_FAILED_ERR:0;
           
           if(ulErrCode == 0)
           {
              /* Note:
                  * The EMAC doesn't distinguish the frame type and frame length,
                  * so, e.g. when the IP(0x8000) or ARP(0x0806) packets are received,
                  * it compares the frame type with the max length and gives the
                  * "Range" error. In fact, this bit is not an error indication,
                  * but simply a statement by the chip regarding the status of
                  * the received frame
                  */
              int_stat &= ~EMAC_INT_RX_ERR;
           }
           else
           {
             if(EMAC_Configs.pfnErrorReceive != NULL)
               EMAC_Configs.pfnErrorReceive(ulErrCode);
            }
        }

        if(int_stat & (EMAC_INT_TX_UNDERRUN|EMAC_INT_TX_ERR ))
        {
           uint32_t ulFrameSts = EMAC_GetTxFrameStatus();
           uint32_t ulErrCode = 0;

           ulErrCode |= (ulFrameSts & EMAC_TINFO_EXCESS_DEF) ? EMAC_EXCESSIVE_DEFER_ERR:0;
           ulErrCode |= (ulFrameSts & EMAC_TINFO_EXCESS_COL) ? EMAC_EXCESSIVE_COLLISION_ERR:0;
           ulErrCode |= (ulFrameSts & EMAC_TINFO_LATE_COL) ? EMAC_LATE_COLLISION_ERR:0;
           ulErrCode |= (ulFrameSts & EMAC_TINFO_UNDERRUN) ? EMAC_UNDERRUN_ERR:0;
           ulErrCode |= (ulFrameSts & EMAC_TINFO_NO_DESCR) ? EMAC_TX_NO_DESC_ERR:0;
           if(EMAC_Configs.pfnErrorReceive != NULL)
              EMAC_Configs.pfnErrorReceive(ulErrCode);
        }
   
        if(int_stat & EMAC_INT_RX_DONE)
        {

          /* Packet received. */
          if(EMAC_GetBufferSts(EMAC_RX_BUFF) != EMAC_BUFF_EMPTY)
          {
             // Get data size
         RxLen = EMAC_GetRxFrameSize();
         if(RxLen > 0)
         {
            // trip out 4-bytes CRC field, note that length in (-1) style format
            RxLen -= 3;
              
            if((EMAC_GetRxFrameStatus() & EMAC_RINFO_ERR_MASK )== 0)
                    {
            uint16_t *pDest = (uint16_t*) &saFrameBuffers[sbCurrFrameID][sulCurrFrameSz];
            uint16_t *pSource = (uint16_t*)EMAC_GetRxBuffer();
                        sulCurrFrameSz += RxLen;
                 
            if(sulCurrFrameSz >= EMAC_MAX_FRAME_SIZE)
            {
              sulCurrFrameSz = 0;
              if(EMAC_Configs.pfnErrorReceive != NULL)
                     EMAC_Configs.pfnErrorReceive(EMAC_LENGTH_ERR);
            }
            else
            {
                // Copy data
               while (RxLen > 0)
                {
                            *pDest++ = *pSource++;
                            RxLen -= 2;
                            } 
                if(EMAC_GetRxFrameStatus() & EMAC_RINFO_LAST_FLAG)
                {
                  
                    if(EMAC_Configs.pfnFrameReceive != NULL)
                    {
                  EMAC_Configs.pfnFrameReceive((uint16_t*)saFrameBuffers[sbCurrFrameID], sulCurrFrameSz);
                    }
                    sulCurrFrameSz = 0;
                    sbCurrFrameID ++;
                    if(sbCurrFrameID >= EMAC_MAX_FRAME_NUM)
                    sbCurrFrameID = 0;
                }   
                /* Release frame from EMAC buffer */
                EMAC_UpdateRxConsumeIndex();
            }
            }
        }            
        }
        
    }
        
        if(int_stat & EMAC_INT_TX_FIN && (EMAC_Configs.pfnTransmitFinish != NULL))
        {
             EMAC_Configs.pfnTransmitFinish();
        }

        if(int_stat & EMAC_INT_SOFT_INT && (EMAC_Configs.pfnSoftInt!= NULL))
        {
             EMAC_Configs.pfnSoftInt();
        }

        if(int_stat & EMAC_INT_WAKEUP && (EMAC_Configs.pfnWakeup!= NULL))
        {
             EMAC_Configs.pfnWakeup();
        }
     
    }
}


/*********************************************************************//**
 * @brief       Enable/Disable hash filter functionality for specified destination
 *              MAC address in EMAC module
 * @param[in]   dstMAC_addr    Pointer to the first MAC destination address, should
 *                  be 6-bytes length, in order LSB to the MSB
 * @param[in]   NewState        New State of this command, should be:
 *                  - ENABLE.
 *                  - DISABLE.
 * @return      None
 *
 * Note:
 * The standard Ethernet cyclic redundancy check (CRC) function is calculated from
 * the 6 byte destination address in the Ethernet frame (this CRC is calculated
 * anyway as part of calculating the CRC of the whole frame), then bits [28:23] out of
 * the 32 bits CRC result are taken to form the hash. The 6 bit hash is used to access
 * the hash table: it is used as an index in the 64 bit HashFilter register that has been
 * programmed with accept values. If the selected accept value is 1, the frame is
 * accepted.
 **********************************************************************/
void EMAC_SetHashFilter(uint8_t dstMAC_addr[], FunctionalState NewState)
{
    uint32_t *pReg;
    uint32_t tmp;
    int32_t crc;

    // Calculate the CRC from the destination MAC address
    crc = EMAC_CRCCalc(dstMAC_addr, 6);
    // Extract the value from CRC to get index value for hash filter table
    crc = (crc >> 23) & 0x3F;

    pReg = (crc > 31) ? ((uint32_t *)&LPC_EMAC->HashFilterH) \
                        : ((uint32_t *)&LPC_EMAC->HashFilterL);
    tmp = (crc > 31) ? (crc - 32) : crc;
    if (NewState == ENABLE)
    {
        (*pReg) |= (1UL << tmp);
    }
    else
    {
        (*pReg) &= ~(1UL << tmp);
    }
    
}


/*********************************************************************//**
 * @brief       Calculates CRC code for number of bytes in the frame
 * @param[in]   frame_no_fcs    Pointer to the first byte of the frame
 * @param[in]   frame_len       length of the frame without the FCS
 * @return      the CRC as a 32 bit integer
 **********************************************************************/
int32_t EMAC_CRCCalc(uint8_t frame_no_fcs[], int32_t frame_len)
{
    int i;      // iterator
    int j;      // another iterator
    char byte;  // current byte
    int crc;    // CRC result
    int q0, q1, q2, q3; // temporary variables

    crc = 0xFFFFFFFF;

    for (i = 0; i < frame_len; i++)
    {
        byte = *frame_no_fcs++;
        for (j = 0; j < 2; j++)
        {
            if (((crc >> 28) ^ (byte >> 3)) & 0x00000001)
            {
                q3 = 0x04C11DB7;
            }
            else
            {
                q3 = 0x00000000;
            }

            if (((crc >> 29) ^ (byte >> 2)) & 0x00000001)
            {
                q2 = 0x09823B6E;
            }
            else
            {
                q2 = 0x00000000;
            }

            if (((crc >> 30) ^ (byte >> 1)) & 0x00000001)
            {
                q1 = 0x130476DC;
            }
            else
            {
                q1 = 0x00000000;
            }

            if (((crc >> 31) ^ (byte >> 0)) & 0x00000001)
            {
                q0 = 0x2608EDB8;
            }
            else
            {
                q0 = 0x00000000;
            }

            crc = (crc << 4) ^ q3 ^ q2 ^ q1 ^ q0;

            byte >>= 4;
        }
    }

    return crc;
}

/*********************************************************************//**
 * @brief       Enable/Disable Filter mode for each specified type EMAC peripheral
 * @param[in]   ulFilterMode    Filter mode, should be:
 *                              - EMAC_RFC_UCAST_EN: all frames of unicast types
 *                              will be accepted
 *                              - EMAC_RFC_BCAST_EN: broadcast frame will be
 *                              accepted
 *                              - EMAC_RFC_MCAST_EN: all frames of multicast
 *                              types will be accepted
 *                              - EMAC_RFC_UCAST_HASH_EN: The imperfect hash
 *                              filter will be applied to unicast addresses
 *                              - EMAC_RFC_MCAST_HASH_EN: The imperfect hash
 *                              filter will be applied to multicast addresses
 *                              - EMAC_RFC_PERFECT_EN: the destination address
 *                              will be compared with the 6 byte station address
 *                              programmed in the station address by the filter
 *                              - EMAC_RFC_MAGP_WOL_EN: the result of the magic
 *                              packet filter will generate a WoL interrupt when
 *                              there is a match
 *                              - EMAC_RFC_PFILT_WOL_EN: the result of the perfect address
 *                              matching filter and the imperfect hash filter will
 *                              generate a WoL interrupt when there is a match
 * @param[in]   NewState    New State of this command, should be:
 *                              - ENABLE
 *                              - DISABLE
 * @return      None
 **********************************************************************/
void EMAC_SetFilterMode(uint32_t ulFilterMode, FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        LPC_EMAC->RxFilterCtrl |= ulFilterMode;

        if((ulFilterMode & EMAC_RFC_MCAST_HASH_EN) &&
            ((ulFilterMode & EMAC_RFC_MCAST_EN) == 0))
        {
          LPC_EMAC->RxFilterCtrl &= ~EMAC_RFC_MCAST_EN;
        }
        if((ulFilterMode & EMAC_RFC_UCAST_HASH_EN) &&
            ((ulFilterMode & EMAC_RFC_UCAST_EN) == 0))
        {
          LPC_EMAC->RxFilterCtrl &= ~EMAC_RFC_UCAST_EN;
        }
    }
    else
    {
        LPC_EMAC->RxFilterCtrl &= ~ulFilterMode;
    }
}

/*********************************************************************//**
 * @brief       Get status of Wake On LAN Filter for each specified
 *              type in EMAC peripheral, clear this status if it is set
 * @param[in]   ulFilterMode    WoL Filter mode, should be:
 *                              - EMAC_WOL_UCAST: unicast frames caused WoL
 *                              - EMAC_WOL_UCAST: broadcast frame caused WoL
 *                              - EMAC_WOL_MCAST: multicast frame caused WoL
 *                              - EMAC_WOL_UCAST_HASH: unicast frame that passes the
 *                              imperfect hash filter caused WoL
 *                              - EMAC_WOL_MCAST_HASH: multicast frame that passes the
 *                              imperfect hash filter caused WoL
 *                              - EMAC_WOL_PERFECT:perfect address matching filter
 *                              caused WoL
 *                              - EMAC_WOL_RX_FILTER: the receive filter caused WoL
 *                              - EMAC_WOL_MAG_PACKET: the magic packet filter caused WoL
 * @return      SET/RESET
 **********************************************************************/
FlagStatus EMAC_GetWoLStatus(uint32_t ulWoLMode)
{
    if (LPC_EMAC->RxFilterWoLStatus & ulWoLMode)
    {
        LPC_EMAC->RxFilterWoLClear = ulWoLMode;

        return SET;
    }
    else
    {
        return RESET;
    }
}






/*********************************************************************//**
 * @brief       Enable/Disable interrupt for each type in EMAC
 * @param[in]   ulIntType   Interrupt Type, should be:
 *                          - EMAC_INT_RX_OVERRUN: Receive Overrun
 *                          - EMAC_INT_RX_ERR: Receive Error
 *                          - EMAC_INT_RX_FIN: Receive Descriptor Finish
 *                          - EMAC_INT_RX_DONE: Receive Done
 *                          - EMAC_INT_TX_UNDERRUN: Transmit Under-run
 *                          - EMAC_INT_TX_ERR: Transmit Error
 *                          - EMAC_INT_TX_FIN: Transmit descriptor finish
 *                          - EMAC_INT_TX_DONE: Transmit Done
 *                          - EMAC_INT_SOFT_INT: Software interrupt
 *                          - EMAC_INT_WAKEUP: Wakeup interrupt
 * @param[in]   NewState    New State of this function, should be:
 *                          - ENABLE.
 *                          - DISABLE.
 * @return      None
 **********************************************************************/
void EMAC_IntCmd(uint32_t ulIntType, FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        LPC_EMAC->IntEnable |= ulIntType;
    }
    else
    {
        LPC_EMAC->IntEnable &= ~(ulIntType);
    }
}

/*********************************************************************//**
 * @brief       Check whether if specified interrupt flag is set or not
 *              for each interrupt type in EMAC and clear interrupt pending
 *              if it is set.
 * @param[in]   ulIntType   Interrupt Type, should be:
 *                          - EMAC_INT_RX_OVERRUN: Receive Overrun
 *                          - EMAC_INT_RX_ERR: Receive Error
 *                          - EMAC_INT_RX_FIN: Receive Descriptor Finish
 *                          - EMAC_INT_RX_DONE: Receive Done
 *                          - EMAC_INT_TX_UNDERRUN: Transmit Under-run
 *                          - EMAC_INT_TX_ERR: Transmit Error
 *                          - EMAC_INT_TX_FIN: Transmit descriptor finish
 *                          - EMAC_INT_TX_DONE: Transmit Done
 *                          - EMAC_INT_SOFT_INT: Software interrupt
 *                          - EMAC_INT_WAKEUP: Wakeup interrupt
 * @return      New state of specified interrupt (SET or RESET)
 **********************************************************************/
IntStatus EMAC_IntGetStatus(uint32_t ulIntType)
{
    if (LPC_EMAC->IntStatus & ulIntType)
    {
        LPC_EMAC->IntClear = ulIntType;
        return SET;
    }
    else
    {
        return RESET;
    }
}



/**
 * @}
 */

/**
 * @}
 */
#endif /*_EMAC*/
