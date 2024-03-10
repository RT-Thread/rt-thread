/**********************************************************************
* $Id$         lpc_mci.c            2011-06-02
*//**
* @file        lpc_mci.c
* @brief       Contains all functions support for MCI firmware library
*              on LPC
* @version     2.0
* @date        29. June. 2011
* @author      NXP MCU SW Application Team
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
#ifdef _MCI

#include "LPC407x_8x_177x_8x.h"
#include "lpc_types.h"
#include "lpc_mci.h"
#include "lpc_gpdma.h"
#include "lpc_clkpwr.h"
#include "lpc_pinsel.h"

#define DMA_MCI_SIZE                     BLOCK_LENGTH

#define MCI_DMA_WRITE_CHANNEL            (0)
#define MCI_DMA_READ_CHANNEL             (1)

#define _SHIFT(x)                        (1 << x)
#define _XSHIFT(x, y)                    (x << y)

#define SHIFT_(x)                        (1 >> x)
#define XSHIFT_(x, y)                    (x >> y)

#define MCI_ACMD41_HCS_POS                     (30)

#define MCI_PWRCTRL_BMASK                      (0xC3)

#define MCI_PWRCTRL_OPENDRAIN_POS              (6)
#define MCI_PWRCTRL_OPENDRAIN_NUMBIT           (1)
#define MCI_PWRCTRL_OPENDRAIN_BMASK            (0x01)


volatile uint32_t Mci_Data_Xfer_End = 0;

volatile uint32_t Mci_Data_Xfer_ERR = 0;

volatile uint8_t fifo_plane = 0;

volatile uint32_t CardRCA;

volatile uint8_t CCS;

volatile en_Mci_CardType MCI_CardType;

// Terminal Counter flag, Error Counter flag for Channel 0
uint32_t dmaWrCh_TermianalCnt, dmaWrCh_ErrorCnt;
uint32_t dmaRdCh_TermianalCnt, dmaRdCh_ErrorCnt;


uint32_t MCI_SettingDma(uint8_t* memBuf, uint32_t ChannelNum, uint32_t DMAMode );

int32_t MCI_ReadFifo(uint32_t * dest);
int32_t MCI_WriteFifo(uint32_t * src);

void MCI_TXEnable( void );
void MCI_RXEnable( void );
void MCI_TXDisable( void );
void MCI_RXDisable( void );

void MCI_CmdProcess( void );
void MCI_DataErrorProcess( void );
void MCI_DataErrorProcess( void );
void MCI_DATA_END_InterruptService( void );
void MCI_FIFOInterruptService( void );

int32_t MCI_CheckStatus(uint8_t expect_status);



volatile uint8_t* dataSrcBlock = (uint8_t *) MCI_DMA_SRC_ADDR;
volatile uint8_t* dataDestBlock = (uint8_t *) MCI_DMA_DST_ADDR;

volatile uint32_t txBlockCnt=0, rxBlockCnt=0;

/** @addtogroup MCI_Private_Functions MCI Private Function
 * @ingroup MCI
 * @{
 */

#if MCI_DMA_ENABLED
/*********************************************************************//**
 * @brief        Do setting GPDMA for MCI working
 *
 * @param[in]    DMAMode set for the Type of DMA Transfer. It may be memory
 *                        to peripheral (M2P) or peripheral to memory (P2M)
 *                        in MCI working
 *
 * @param[in]    ChannelNum    which channel is used for current transfer with 
 *                        DMA compent
 *
 * @param[in]    memBuf    point to a UINT8 buffer. In 2 cases of DMAMode
 *                        seperated:
 *                        - M2P: it is the source address that hold the
 *                        expected buffer to transfer
 *                        - P2M: it is the destination address that will store
 *                         data that retrieved from the peripheral (the Card in slot)
 *
 * @return       None
 *
 * @note        This is only required if DMA support is enabled
 **********************************************************************/
uint32_t MCI_SettingDma(uint8_t* memBuf, uint32_t ChannelNum, uint32_t DMAMode )
{
    GPDMA_Channel_CFG_Type GPDMACfg;

    // Transfer size
    GPDMACfg.TransferSize = DMA_MCI_SIZE;
    // Transfer width
    GPDMACfg.TransferWidth = GPDMA_WIDTH_WORD;
    // Transfer type
    GPDMACfg.TransferType = DMAMode;
    // Linker List Item - unused
    GPDMACfg.DMALLI = 0;
    
    /* USB RAM is used for test.
    Please note, Ethernet has its own SRAM, but GPDMA can't access
    that. GPDMA can access USB SRAM and IRAM. Ethernet DMA controller can 
    access both IRAM and Ethernet SRAM. */
    GPDMACfg.ChannelNum = ChannelNum;
    
    if ( DMAMode == GPDMA_TRANSFERTYPE_M2P_DEST_CTRL )
    {
        /* Ch0 set for M2P transfer from mempry to MCI FIFO. */
        // Source memory
        GPDMACfg.SrcMemAddr = (uint32_t)memBuf;
        // Destination memory
        GPDMACfg.DstMemAddr = (uint32_t)LPC_MCI->FIFO;

        // Source connection 
        GPDMACfg.SrcConn = 0;
        // Destination connection 
        GPDMACfg.DstConn = GPDMA_CONN_MCI;
            
    }
    else if ( DMAMode == GPDMA_TRANSFERTYPE_P2M_SRC_CTRL )
    {
        /* Ch0 set for P2M transfer from MCI FIFO to memory. */
        // Source memory
        GPDMACfg.SrcMemAddr = (uint32_t)LPC_MCI->FIFO;
        // Destination memory
        GPDMACfg.DstMemAddr = (uint32_t)memBuf;

        // Source connection 
        GPDMACfg.SrcConn = GPDMA_CONN_MCI;
        // Destination connection
        GPDMACfg.DstConn = 0;
    }
    else
    {
        return ( FALSE );
    }

    // Setup channel with given parameter
    GPDMA_Setup(&GPDMACfg);

    // Enable GPDMA channel 
    GPDMA_ChannelCmd(ChannelNum, ENABLE);

    /* Enable GPDMA interrupt */
    NVIC_EnableIRQ(DMA_IRQn);
    
    return (TRUE);
}


/*********************************************************************//**
 * @brief        GPDMA interrupt handler sub-routine
 *
 * @param        None
 *
 * @return       None
 *
 * @note         This is only executed if DMA support is enabled
 **********************************************************************/
void MCI_DMA_IRQHandler (void)
{
    // check GPDMA interrupt on channel 0
    if (GPDMA_IntGetStatus(GPDMA_STAT_INT, MCI_DMA_WRITE_CHANNEL))
    {
        //check interrupt status on channel 0
        // Check counter terminal status
        if(GPDMA_IntGetStatus(GPDMA_STAT_INTTC, MCI_DMA_WRITE_CHANNEL))
        {
            // Clear terminate counter Interrupt pending
            GPDMA_ClearIntPending (GPDMA_STATCLR_INTTC, MCI_DMA_WRITE_CHANNEL);

            dmaWrCh_TermianalCnt++;
        }
        if (GPDMA_IntGetStatus(GPDMA_STAT_INTERR, MCI_DMA_WRITE_CHANNEL))
        {
            // Clear error counter Interrupt pending
            GPDMA_ClearIntPending (GPDMA_STATCLR_INTERR, MCI_DMA_WRITE_CHANNEL);

            dmaWrCh_ErrorCnt++;
        }
    }
    else if (GPDMA_IntGetStatus(GPDMA_STAT_INT, MCI_DMA_READ_CHANNEL))
    {
        //check interrupt status on channel 0
        // Check counter terminal status
        if(GPDMA_IntGetStatus(GPDMA_STAT_INTTC, MCI_DMA_READ_CHANNEL))
        {
            // Clear terminate counter Interrupt pending
            GPDMA_ClearIntPending (GPDMA_STATCLR_INTTC, MCI_DMA_READ_CHANNEL);

            dmaRdCh_TermianalCnt++;
        }
        if (GPDMA_IntGetStatus(GPDMA_STAT_INTERR, MCI_DMA_READ_CHANNEL))
        {
            // Clear error counter Interrupt pending
            GPDMA_ClearIntPending (GPDMA_STATCLR_INTERR, MCI_DMA_READ_CHANNEL);

            dmaRdCh_ErrorCnt++;
        }
    }
}
#endif


/*********************************************************************//**
 * @brief        Read data from FIFO (after a transmission with card) to
 *                a destination buffer
 *
 * @param[in]    *dest The buffer to store the data that read from card
 *
 * @return       MCI_FUNC_OK
 *************************************************************************/
int32_t MCI_ReadFifo(uint32_t * dest) 
{
    uint8_t i;
    uint8_t start, end;

    if(fifo_plane == 0)
    {
        start = 0;
        end = 7;
    }
    else
    {
        start = 8;
        end = 15;
    }
    fifo_plane = (fifo_plane) ? 0:1;

    for (i = start; i <= end; i++) 
    {
        *dest = LPC_MCI->FIFO[i];
        
        dest++;
    }
    
    return MCI_FUNC_OK;
}


/*********************************************************************//**
 * @brief        Write data from a source buffer to FIFO for transmission
 *
 * @param[in]    *src The buffer hold the data need to write to card
 *
 * @return       MCI_FUNC_OK
 *************************************************************************/
int32_t MCI_WriteFifo(uint32_t * src)
{
    uint8_t i;
    uint8_t start, end;

    if(fifo_plane == 0)
    {
        start = 0;
        end = 7;
    }
    else
    {
        start = 8;
        end = 15;
    }
    fifo_plane = (fifo_plane) ? 0:1;

    for (i = start; i <= end; i++) 
    {
        LPC_MCI->FIFO[i] = *src;
        
        src++;
    }
    
    return MCI_FUNC_OK;
}


/*********************************************************************//**
 * @brief        Enable Transmit data interrupt
 *
 * @param        None
 *
 * @return       None
 *************************************************************************/
void MCI_TXEnable( void )
{
#if MCI_DMA_ENABLED
    LPC_MCI->MASK0 |= ((DATA_END_INT_MASK)|(ERR_TX_INT_MASK));    /* Enable TX interrupts only */
#else
    LPC_MCI->MASK0 |= ((FIFO_TX_INT_MASK)|(DATA_END_INT_MASK)|(ERR_TX_INT_MASK));    /* FIFO TX interrupts only */
#endif

    return;
}


/*********************************************************************//**
 * @brief        Disable Transmit data interrupt
 *
 * @param        None
 *
 * @return       None
 *************************************************************************/
void MCI_TXDisable( void )
{
#if MCI_DMA_ENABLED
    LPC_MCI->MASK0 &= ~((DATA_END_INT_MASK)|(ERR_TX_INT_MASK));    /* Enable TX interrupts only */
#else
    LPC_MCI->MASK0 &= ~((FIFO_TX_INT_MASK)|(DATA_END_INT_MASK)|(ERR_TX_INT_MASK));    /* FIFO TX interrupts only */
#endif

    return;
}


/*********************************************************************//**
 * @brief        Enable Receive data interrupt
 *
 * @param        None
 *
 * @return       None
 *************************************************************************/
void MCI_RXEnable( void )
{
#if MCI_DMA_ENABLED
    LPC_MCI->MASK0 |= ((DATA_END_INT_MASK)|(ERR_RX_INT_MASK));    /* Enable RX interrupts only */
#else
    LPC_MCI->MASK0 |= ((FIFO_RX_INT_MASK)|(DATA_END_INT_MASK)|(ERR_RX_INT_MASK));    /* FIFO RX interrupts only */
#endif

    return;
}


/*********************************************************************//**
 * @brief        Disable Receive data interrupt
 *
 * @param        None
 *
 * @return       None
 *************************************************************************/
void MCI_RXDisable( void )
{
#if MCI_DMA_ENABLED
    LPC_MCI->MASK0 &= ~((DATA_END_INT_MASK)|(ERR_RX_INT_MASK));    /* Enable TX interrupts only */
#else
    LPC_MCI->MASK0 &= ~((FIFO_RX_INT_MASK)|(DATA_END_INT_MASK)|(ERR_RX_INT_MASK));    /* FIFO TX interrupts only */
#endif

    return;
}

/*********************************************************************//**
 * @brief      Check if the card is in the given state.
 *@param       expect_status    expected status
 * @details    Continuously get the card status until the card is ready. if its status matches 
 *             with the given state, return with success. Else, return MCI_FUNC_ERR_STATE.
 *             If the card is still not ready, return MCI_FUNC_NOT_READY.
 *
 * @param      None
 *
 * @return     MCI_FUNC_OK if all success
 *************************************************************************/
int32_t MCI_CheckStatus(uint8_t expect_status)
{
    int32_t respValue, retval = MCI_FUNC_FAILED;
    uint32_t retryCnt = 0xFFFF, i;
    while (retryCnt > 0)
    {
        if (MCI_GetCardStatus(&respValue) != MCI_FUNC_OK)
        {
            break;
        }
        else
        {
            /* The only valid state is TRANS per MMC and SD state diagram.
            RCV state may be seen, but, it happens only when TX_ACTIVE or
            RX_ACTIVE occurs before the WRITE_BLOCK and READ_BLOCK cmds are
            being sent, which is not a valid sequence. */
            if(!(respValue & CARD_STATUS_READY_FOR_DATA ))
            {
                retval = MCI_FUNC_NOT_READY;
            }
            else if(CARDSTATEOF(respValue) != expect_status)
            {
              // If card is in prg state, wait until it changes to trans state
              // when "operation complete"
              if(CARDSTATEOF(respValue) != CARD_STATE_PRG)
              {
                return MCI_FUNC_ERR_STATE;
              }    
            }
            else
            {
                return MCI_FUNC_OK;
            }
        }
        retryCnt--;
        for(i = 0; i < 0x20; i++);
        
    }

    return retval;
}


/*********************************************************************//**
 * @brief        Called by MCI interrupt handler to simplify the command
 *                process.
 *
 * @param        None
 *
 * @return       None
 *
 * @note         In card initialization, the commnad interrupts are disabled
 *************************************************************************/
void MCI_CmdProcess( void )
{
    uint32_t MCIStatus;

    MCIStatus = LPC_MCI->STATUS;

    if ( MCIStatus &  MCI_CMD_CRC_FAIL )
    {
        LPC_MCI->CLEAR =  MCI_CMD_CRC_FAIL;
    }

    if ( MCIStatus &  MCI_CMD_TIMEOUT )
    {
        LPC_MCI->CLEAR =  MCI_CMD_TIMEOUT;
    }

    /* Cmd Resp End or Cmd Sent */
    if ( MCIStatus &  MCI_CMD_RESP_END )
    {
        LPC_MCI->CLEAR =  MCI_CMD_RESP_END;
    }

    if ( MCIStatus &  MCI_CMD_SENT )
    {
        LPC_MCI->CLEAR =  MCI_CMD_SENT;
    }

    if ( MCIStatus &  MCI_CMD_ACTIVE )
    {
        LPC_MCI->CLEAR =  MCI_CMD_ACTIVE;
    }

    return;
}


/*********************************************************************//**
 * @brief        Called by MCI interrupt handler to manage error on the bus
 *
 * @param        None
 *
 * @return       None
 *************************************************************************/
void MCI_DataErrorProcess( void )
{
    uint32_t MCIStatus;

    MCIStatus = LPC_MCI->STATUS;

    if ( MCIStatus &  MCI_DATA_CRC_FAIL )
    {
        LPC_MCI->CLEAR = MCI_DATA_CRC_FAIL;
    }

    if ( MCIStatus &  MCI_DATA_TIMEOUT )
    {
        LPC_MCI->CLEAR =  MCI_DATA_TIMEOUT;
    }

    /* Underrun or overrun */
    if ( MCIStatus &  MCI_TX_UNDERRUN )
    {
        LPC_MCI->CLEAR = MCI_TX_UNDERRUN;
    }

    if ( MCIStatus &  MCI_RX_OVERRUN )
    {
        LPC_MCI->CLEAR =  MCI_RX_OVERRUN;
    }

    /* Start bit error on data signal */
    if ( MCIStatus &  MCI_START_BIT_ERR )
    {
        LPC_MCI->CLEAR =  MCI_START_BIT_ERR;
    }

    Mci_Data_Xfer_End = 0;
    Mci_Data_Xfer_ERR = MCIStatus;
    return;
}


/*********************************************************************//**
 * @brief         Called by MCI interrupt handler. This is the last interrupt
 *                manipulates the process of the data-block write and read 
 *                to/with card
 *
 * @details       This service is also used with/without DMA support. It simply
 *                clears the flag messages the in-process data-block transfer 
 *                has been done/ended
 *
 * @param         None
 *
 * @return        None
 *************************************************************************/
void MCI_DATA_END_InterruptService( void )
{
    uint32_t MCIStatus;

    MCIStatus = LPC_MCI->STATUS;
    if ( MCIStatus &  MCI_DATA_END )        /* Data end, and Data block end  */
    {
        LPC_MCI->CLEAR = MCI_DATA_END;

        Mci_Data_Xfer_End = 0;

        Mci_Data_Xfer_ERR = 0;

        MCI_TXDisable();
        
        MCI_RXDisable();

        return;
    }

    if ( MCIStatus &  MCI_DATA_BLK_END )
    {
        LPC_MCI->CLEAR =  MCI_DATA_BLK_END;

        //MCI_TXDisable();

        return;
    }

    /* Tx active  */
    if ( MCIStatus & MCI_TX_ACTIVE )
    {

    }

    /* Rx active  */
    if ( MCIStatus & MCI_RX_ACTIVE )
    {

    }

    return;
}


/*********************************************************************//**
 * @brief        Called by MCI interrupt handler if requiring to using FIFO
 *                for data transferring. It copy data to/from FIFO register
 *                from/to a data buffer.
 *
 * @param        None
 *
 * @return       None
 *
 * @note         This function is done without DMA transfer support
 **********************************************************************/
void MCI_FIFOInterruptService( void )
{
#if !MCI_DMA_ENABLED
    uint32_t MCIStatus;

    MCIStatus = LPC_MCI->STATUS;

    if ( MCIStatus & (FIFO_TX_INT_MASK ) )
    {
        /* empty is multiple of 512 block size */
        if ( MCIStatus & MCI_TX_HALF_EMPTY )
        {
            //There's no data, return
            if(dataSrcBlock == NULL)
                return;

            /* write 8 words to fifo */
            MCI_WriteFifo((uint32_t *)&dataSrcBlock[txBlockCnt]);

            txBlockCnt += 32;
        }

        if (txBlockCnt == BLOCK_LENGTH)    /* block complete */
        {
            dataSrcBlock += BLOCK_LENGTH;

            txBlockCnt = 0;

            /* disable FIFO int until next block write */
            //LPC_MCI->MASK0 &= ~(FIFO_TX_INT_MASK);

            /* wait for SD card to complete sending data i.e MCI_DATA_BLK_END interrupt */
        }
    }
    else if ( MCIStatus & (FIFO_RX_INT_MASK) )
    {
        /* if using RX_HALF_FULL remove one ReadFIFO below */
        if ( MCIStatus & MCI_RX_HALF_FULL )
        {
            //There's no store data, return
            if(dataDestBlock == NULL)
                return;

            /* read 8 words from fifo */
            MCI_ReadFifo((uint32_t *)&dataDestBlock[rxBlockCnt]);

            rxBlockCnt += 32;
        }

        /* block complete */
        if (rxBlockCnt == BLOCK_LENGTH)
        {
            dataDestBlock += BLOCK_LENGTH;

            rxBlockCnt = 0;
        }
    }
#endif

    return;
}

/*********************************************************************//**
 * @brief        MCI_IRQHandler is to manage the reasons that cause the 
 *               interrupt.
 *
 * @details      It controls the data-block writing and reading by access 
 *               the FIFO register.
 *               It handle the state changes on the MCI bus...
 *
 * @param        None
 *
 * @return       None
 **********************************************************************/
void MCI_IRQHandler (void)
{
    uint32_t MCI_Status;

    MCI_Status = LPC_MCI->STATUS;

    /* handle MCI_STATUS interrupt */
    if ( MCI_Status & DATA_ERR_INT_MASK )
    {
        MCI_DataErrorProcess();

        return;
    }

    if ( MCI_Status & DATA_END_INT_MASK )
    {
        MCI_DATA_END_InterruptService();

        return;
    }
    else if ( MCI_Status & FIFO_INT_MASK )
    {
        MCI_FIFOInterruptService();

        return;
    }
    else if ( MCI_Status & CMD_INT_MASK )
    {
        MCI_CmdProcess();

        return;
    }
}


/**
 * @}
 */



/** @addtogroup MCI_Public_Functions
 * @{
 */

/*********************************************************************//**
 * @brief        Set MCI clock rate, during initialization phase < 400K
 *                during data phase < 20Mhz
 *
 * @param[in]    ClockRate Clock rate to be set (in Hz)
 *
 * @return       None
 **********************************************************************/
void MCI_Set_MCIClock( uint32_t ClockRate )
{
    volatile uint32_t i;
    uint32_t ClkValue = 0;
    uint32_t pclk;
    
    pclk = CLKPWR_GetCLK(CLKPWR_CLKTYPE_PER);

    ClkValue = (pclk + 2*ClockRate - 1) /(2*ClockRate); 
    if(ClkValue)
        ClkValue -= 1;

    LPC_MCI->CLOCK = (LPC_MCI->CLOCK & ~(0xFF)) | (1 << 8)  | ClkValue;

    for ( i = 0; i < 0x10; i++ );    /* delay 3MCLK + 2PCLK before next write */

    return;
}


/**********************************************************************//**
 * @brief        Set the Width to 1-bit Bus or 4-bit Bus
 *
 * @param[in]    width buswidth expected to set
 *
 * @return       MCI_FUNC_OK in case of success
 *************************************************************************/
int32_t MCI_SetBusWidth( uint32_t width )
{
    volatile uint32_t i;
    uint8_t bus_width = BUS_WIDTH_1BIT;

    if ( width == SD_1_BIT )
    {
        LPC_MCI->CLOCK &=  ~(1 << 11);    /* 1 bit bus */
    }
    else if ( width == SD_4_BIT )
    {
        LPC_MCI->CLOCK |=  (1 << 11);/* 4 bit bus */
        bus_width = BUS_WIDTH_4BITS;
    }

    for ( i = 0; i < 0x10; i++ );    /* delay 3MCLK + 2PCLK  */
    
    if ((MCI_CardType == MCI_SDSC_V1_CARD) ||
        (MCI_CardType == MCI_SDSC_V2_CARD) ||
        (MCI_CardType == MCI_SDHC_SDXC_CARD)) 
    {
        if ( MCI_Acmd_SendBusWidth( bus_width ) != MCI_FUNC_OK )
        {
            return(MCI_FUNC_FAILED);
        }
    }
    return MCI_FUNC_OK;
}


/************************************************************************//**
 * @brief        Do initialization the MCI block as set its clock, registers,
 *                setup NVIC for interrupts, configure the pins used for MCI 
 *                function, do initialize the card in slot...
 *
 * @param[in]    powerActiveLevel the power level to activate the card in slot
 *
 * @return       MCI_FUNC_OK in case of success
 ***************************************************************************/
int32_t MCI_Init(uint8_t powerActiveLevel )
{
    volatile uint32_t i;

    MCI_CardType = MCI_CARD_UNKNOWN;

    // Following block of code added to ensure card VCC drops to zero
    // before card is initialized
  
    // Force all MCI control pins to basic I/O mode
    LPC_IOCON->P1_2  &= ~0x1F; /* SD_CLK @ P1.2 */
    LPC_IOCON->P1_3  &= ~0x1F; /* SD_CMD @ P1.3 */
    LPC_IOCON->P1_5  &= ~0x1F; /* SD_PWR @ P1.5 */
    LPC_IOCON->P1_6  &= ~0x1F; /* SD_DAT_0 @ P1.6 */
    LPC_IOCON->P1_7  &= ~0x1F; /* SD_DAT_1 @ P1.7 */
    LPC_IOCON->P1_11 &= ~0x1F; /* SD_DAT_2 @ P1.11 */
    LPC_IOCON->P1_12 &= 0x1F; /* SD_DAT_3 @ P1.12 */

    // Set all MCI pins to outputs
    LPC_GPIO1->DIR |= 0x18EC;
  
    // Force all pins low (except power control pin)
    LPC_GPIO1->CLR = 0x1000;
    LPC_GPIO1->CLR = 0x0800;
    LPC_GPIO1->CLR = 0x0080;
    LPC_GPIO1->CLR = 0x0040;
  
    LPC_GPIO1->SET = 0x0020;
  
    LPC_GPIO1->CLR = 0x0008;
    LPC_GPIO1->CLR = 0x0004;

    // Crude delay of 50ms at 120MHz
    for ( i = 0; i < 0x100000; i++ );

    LPC_SC->PCONP |= ( 1 << 28 );            /* Enable clock to the MCI block */

    if ( LPC_MCI->CLOCK & (1 << 8) )
    {
       LPC_MCI->CLOCK &= ~(1 << 8);
       for ( i = 0; i < 0x10; i++ );    /* delay 3MCLK + 2PCLK  */
    }

    if ( LPC_MCI->POWER & 0x02 )
    {
       LPC_MCI->POWER = 0x00;
       for ( i = 0; i < 0x10; i++ );    /* delay 3MCLK + 2PCLK  */
    }

    /* Disable all interrupts for now */
    LPC_MCI->MASK0 = 0;

    //SD_CLK
    PINSEL_ConfigPin(1, 2, 2);

    //SD_CMD
    PINSEL_ConfigPin(1, 3, 2);

    //SD_PWR
    PINSEL_ConfigPin(1, 5, 2);

    //SD_DAT_0
    PINSEL_ConfigPin(1, 6, 2);

    //SD_DAT_1
    PINSEL_ConfigPin(1, 7, 2);

    //SD_DAT_2
    PINSEL_ConfigPin(1, 11, 2);

    //SD_DAT_3
    PINSEL_ConfigPin(1, 12, 2);

    // SD_PWR is active high (follows the output of the SD Card interface block).
    if(powerActiveLevel == LOW_LVL)
    {
        LPC_SC->SCS &= ~ 0x08;//Becase on EA board SD_PWR is active low
    }
    else
    {
        LPC_SC->SCS |= 0x08;
    }

    //Setting for timeout problem
    LPC_MCI->DATATMR = 0x1FFFFFFF;

    /*set up clocking default mode, clear any registers as needed */
    LPC_MCI->COMMAND = 0;
    for ( i = 0; i < 0x10; i++ );    /* delay 3MCLK + 2PCLK  */
    LPC_MCI->DATACTRL = 0;
    for ( i = 0; i < 0x10; i++ );    /* delay 3MCLK + 2PCLK  */
    LPC_MCI->CLEAR = 0x7FF;        /* clear all pending interrupts */

    LPC_MCI->POWER = 0x02;        /* power up */
    for ( i = 0; i < 0x10; i++ );    /* delay 3MCLK + 2PCLK  */

    
    /* delays for the supply output is stable*/
    for ( i = 0; i < 0x80000; i++ );
    
    /* During identification phase, the clock should be less than
    400Khz. Once we pass this phase, the normal clock can be set up
    to 25Mhz on SD card and 20Mhz on MMC card. */
    MCI_Set_MCIClock(MCI_SLOW_RATE );

    LPC_MCI->POWER |= 0x01;        /* bit 1 is set already, from power up to power on */
    for ( i = 0; i < 0x10; i++ );    /* delay 3MCLK + 2PCLK  */

    NVIC_EnableIRQ(MCI_IRQn);

    MCI_CardInit();

    /* During the initialization phase, to simplify the process, the CMD related
    interrupts are disabled. The DATA related interrupts are enabled when
    the FIFOs are used and just before WRITE_BLOCK READ_BLOCK cmds are issues, and
    disabled after the data block has been written and read. Please also note,
    before WRITE_BLOCK only TX related data interrupts are enabled, and before
    READ_BLOCK only RX related data interrupts are enabled. */
    return MCI_FUNC_OK;
}


/************************************************************************//**
 * @brief         Set output in open drain mode or pushpull mode
 *
 * @param[in]    mode the mode going to set
 *
 * @return         None
 ***************************************************************************/
void MCI_SetOutputMode(uint32_t mode)
{
    uint32_t i = 0;
    if(mode == MCI_OUTPUT_MODE_OPENDRAIN)
    {
        /* Set Open Drain output control for MMC */
        LPC_MCI->POWER |= (1 << MCI_PWRCTRL_OPENDRAIN_POS) & MCI_PWRCTRL_BMASK;
    }
    else
    {
        /* Clear Open Drain output control for SD */
        LPC_MCI->POWER &= (~(1 << MCI_PWRCTRL_OPENDRAIN_POS) & MCI_PWRCTRL_BMASK);
    }
    for ( i = 0; i < 0x10; i++ );    /* delay 3MCLK + 2PCLK  */
}


/************************************************************************//**
 * @brief        The routine is used to send a CMD to the card
 *
 * @param[in]    CmdIndex the command to be sent to cards
 *
 * @param[in]    Argument the argument follows the command
 *
 * @param[in]    ExpectResp the response type for the command. They may be:
 *                - EXPECT_NO_RESP: means no response required
 *                - EXPECT_SHORT_RESP: means a response in a word needed
 *                - EXPECT_LONG_RESP: means a response in 4 words needed
 *
 * @param[in]    AllowTimeout allow timeout the command or not
 *
 * @return       None
 ***************************************************************************/
void MCI_SendCmd(st_Mci_CmdInfo* pCmdIf)
{
    volatile uint32_t i;
    uint32_t CmdData = 0;
    uint32_t CmdStatus;

    uint32_t CmdIndex = pCmdIf->CmdIndex;
    uint32_t Argument = pCmdIf->Argument;
    uint32_t ExpectResp = pCmdIf->ExpectResp;
    uint32_t AllowTimeout = pCmdIf->AllowTimeout;
    
    /* the command engine must be disabled when we modify the argument
    or the peripheral resends */
    while ( (CmdStatus = LPC_MCI->STATUS) & MCI_CMD_ACTIVE )    /* Command in progress. */
    {
        LPC_MCI->COMMAND = 0;
        for ( i = 0; i < 0x10; i++ );    /* delay 3MCLK + 2PCLK  */
        LPC_MCI->CLEAR = CmdStatus | MCI_CMD_ACTIVE;
    }


    /*set the command details, the CmdIndex should 0 through 0x3F only */
    CmdData |= (CmdIndex & 0x3F);    /* bit 0 through 5 only */

    if ( ExpectResp == EXPECT_NO_RESP )            /* no response */
    {
        CmdData &= ~((1 << 6) | (1 << 7));        /* Clear long response bit as well */
    }
    else if ( ExpectResp == EXPECT_SHORT_RESP )    /* expect short response */
    {
        CmdData |= (1 << 6);
    }
    else if ( ExpectResp == EXPECT_LONG_RESP )    /* expect long response */
    {
        CmdData |= (1 << 6) | (1 << 7);
    }

    if ( AllowTimeout == ALLOW_CMD_TIMER )            /* allow timeout or not */
    {
        CmdData &= ~ MCI_DISABLE_CMD_TIMER;
    }
    else
    {
        CmdData |= MCI_DISABLE_CMD_TIMER;
    }

    /*send the command*/
    CmdData |= (1 << 10);        /* This bit needs to be set last. */

    // clear status register
    LPC_MCI->CLEAR = 0x7FF;

    LPC_MCI->ARGUMENT = Argument;    /* Set the argument first, finally command */

    LPC_MCI->COMMAND = CmdData;

    for ( i = 0; i < 0x10; i++ );    /* delay 3MCLK + 2PCLK  */

    // Wait until command is processed
    while(!LPC_MCI->STATUS);
    
    // Wait until command sent
    while(LPC_MCI->STATUS & MCI_CMD_ACTIVE);
    
    return;
}


/************************************************************************//**
 * @brief        The routine is to get the reponse from card after commands.
 *               This function is always used in pair of MCI_SendCmd() func
 *
 * @param[in]    ExpectCmdData specify the command of which the data will be
 *                retrieved. This field should be the same with CmdIndex of
 *                MCI_SendCmd() function.
 *
 * @param[in]    ExpectResp the response type for the command. They may be:
 *                - EXPECT_NO_RESP: means no response required
 *                - EXPECT_SHORT_RESP: means a response in a word needed
 *                - EXPECT_LONG_RESP: means a response in 4 words needed
 *
 * @param[out]   CmdResp the buffer stored the data replied from cards
 *
 * @return       MCI_FUNC_OK in case of success
 ***************************************************************************/
int32_t MCI_GetCmdResp(uint32_t ExpectCmdData, uint32_t ExpectResp, uint32_t *CmdResp)
{
    uint32_t CmdRespStatus = 0;
    uint32_t LastCmdIndex;
    uint32_t i = 0;

    if ( ExpectResp == EXPECT_NO_RESP )
    {
        return MCI_FUNC_OK;
    }

    while (1)
    {
        // Get the status of the component
        CmdRespStatus = LPC_MCI->STATUS;

        if ( CmdRespStatus & (MCI_CMD_TIMEOUT) )
        {
            LPC_MCI->CLEAR = CmdRespStatus | MCI_CMD_TIMEOUT;

            LPC_MCI->COMMAND = 0;
            LPC_MCI->ARGUMENT = 0xFFFFFFFF;

            for ( i = 0; i < 0x10; i++ );    /* delay 3MCLK + 2PCLK  */
            
            return (CmdRespStatus);
        }

        if (  CmdRespStatus & MCI_CMD_CRC_FAIL )
        {
            LPC_MCI->CLEAR = CmdRespStatus | MCI_CMD_CRC_FAIL;
            LastCmdIndex = LPC_MCI->COMMAND & 0x003F;

            if ( (LastCmdIndex == CMD1_SEND_OP_COND) || (LastCmdIndex == ACMD41_SEND_APP_OP_COND)
                                                    || (LastCmdIndex == CMD12_STOP_TRANSMISSION) )
            {
                LPC_MCI->COMMAND = 0;
                LPC_MCI->ARGUMENT = 0xFFFFFFFF;
                for ( i = 0; i < 0x10; i++ );    /* delay 3MCLK + 2PCLK  */
                break;            /* ignore CRC error if it's a resp for SEND_OP_COND
                                or STOP_TRANSMISSION. */
            }
            else
            {
                return (CmdRespStatus);
            }
        }
        else if (CmdRespStatus & MCI_CMD_RESP_END)
        {
            LPC_MCI->CLEAR = CmdRespStatus | MCI_CMD_RESP_END;
            break;    /* cmd response is received, expecting response */
        }
        
    }

    if ((LPC_MCI->RESP_CMD & 0x3F) != ExpectCmdData)
    {
        /* If the response is not R1, in the response field, the Expected Cmd data
        won't be the same as the CMD data in SendCmd(). Below four cmds have
        R2 or R3 response. We don't need to check if MCI_RESP_CMD is the same
        as the Expected or not. */
        if ((ExpectCmdData != CMD1_SEND_OP_COND) && (ExpectCmdData != ACMD41_SEND_APP_OP_COND)
                    && (ExpectCmdData != CMD2_ALL_SEND_CID) && (ExpectCmdData != CMD9_SEND_CSD))
        {
            CmdRespStatus = INVALID_RESPONSE;    /* Reuse error status */
            return (INVALID_RESPONSE);
        }
    }

    /* Read MCI_RESP0 register assuming it's not long response. */
    if (CmdResp != NULL)
    {
        if (ExpectResp == EXPECT_SHORT_RESP)
        {
            *(CmdResp + 0) = LPC_MCI->RESP0;
        }
        else if (ExpectResp == EXPECT_LONG_RESP)
        {
            *(CmdResp + 0) = LPC_MCI->RESP0;
            *(CmdResp + 1) = LPC_MCI->RESP1;
            *(CmdResp + 2) = LPC_MCI->RESP2;
            *(CmdResp + 3) = LPC_MCI->RESP3;
        }
        }

    return MCI_FUNC_OK;
}


/************************************************************************//**
 * @brief        The routine is to send command to cards then get back the 
 *               reponses (if required).
 *
 * @param[in]    CmdIndex the command to be sent to cards
 *
 * @param[in]    Argument the argument follows the command
 *
 * @param[in]    ExpectResp the response type for the command. They may be:
 *                - EXPECT_NO_RESP: means no response required
 *                - EXPECT_SHORT_RESP: means a response in a word needed
 *                - EXPECT_LONG_RESP: means a response in 4 words needed
 *
 * @param[out]    CmdResp the buffer stored the data replied from cards
 *
 * @param[in]    AllowTimeout allow timeout the command or not
 *
 * @return       MCI_FUNC_OK in case of success
 ***************************************************************************/
int32_t MCI_CmdResp(st_Mci_CmdInfo* pCmdIf)
{
    int32_t respStatus;
    uint32_t CmdIndex = pCmdIf->CmdIndex;
    uint32_t ExpectResp = pCmdIf->ExpectResp;
    uint32_t *CmdResp = pCmdIf->CmdResp;
    

    MCI_SendCmd(pCmdIf);

    if((CmdResp != NULL) || (ExpectResp != EXPECT_NO_RESP))
    {
        respStatus = MCI_GetCmdResp(CmdIndex, ExpectResp, CmdResp);
    }
    else
    {
        respStatus = MCI_FUNC_BAD_PARAMETERS;
    }

    return respStatus;
}


/************************************************************************//**
 * @brief        To reset the card, the CMD0 is sent and then the card is put
 *               in idle state. This is the very first command to be sent to
 *               initialize either MMC or SD card.
 *
 * @param        None
 *
 * @return       Always MCI_FUNC_OK
 ***************************************************************************/
int32_t MCI_CardReset(void)
{
    st_Mci_CmdInfo cmdIf;
    /* Because CMD0 command to put the device to idle state does not need response 
    since, it's only sending commad */
    cmdIf.CmdIndex = CMD0_GO_IDLE_STATE;
    cmdIf.Argument = 0x00000000;
    cmdIf.ExpectResp = EXPECT_NO_RESP;
    cmdIf.AllowTimeout = 0;
    cmdIf.CmdResp = 0;
    MCI_SendCmd(&cmdIf);

    return MCI_FUNC_OK;
}


/************************************************************************//**
 * @brief        Send CMD1 (SEND_OP_COND) to card.
 *
 * @param        None
 *
 * @return       MCI_FUNC_OK if all success
 ****************************************************************************/
int32_t MCI_Cmd_SendOpCond( void )
{
    volatile uint32_t i;
    uint32_t retryCount;
    uint32_t respStatus;
    uint32_t respValue[4];
    st_Mci_CmdInfo cmdIf;
    int32_t retval = MCI_FUNC_FAILED;

    retryCount = 0x200;            /* reset retry counter */

    cmdIf.CmdIndex = CMD1_SEND_OP_COND;
    cmdIf.Argument = OCR_INDEX;
    cmdIf.ExpectResp = EXPECT_SHORT_RESP;
    cmdIf.AllowTimeout = ALLOW_CMD_TIMER;
    cmdIf.CmdResp = (uint32_t *)&respValue[0];
    /* continuously sends until the busy bit is cleared */
    while ( retryCount > 0 ) 
    {
        respStatus = MCI_CmdResp(&cmdIf);

        if(respStatus & MCI_CMD_TIMEOUT)
        {
            retval = MCI_FUNC_TIMEOUT;
        }
        else if ((respValue[0] & 0x80000000) == 0)
        {
            //The card has not finished the power up routine
            retval = MCI_FUNC_BUS_NOT_IDLE;
        }
        else
        {
            retval = MCI_FUNC_OK;
            break;
        }

        for ( i = 0; i < 0x20; i++ );

        retryCount--;
    }

    return(retval);
}


/************************************************************************//**
 * @brief        Send CMD8 (SEND_IF_COND) for interface condition to card.
 *
 * @param        None
 *
 * @return       MCI_FUNC_OK if all success
 ****************************************************************************/
int32_t MCI_Cmd_SendIfCond(void)
{
    volatile uint32_t i;
    uint32_t retryCount;
    uint32_t CmdArgument;
    uint32_t respStatus;
    uint32_t respValue[4];

    int32_t retval = MCI_FUNC_FAILED;

    uint8_t voltageSupplied = MCI_CMD8_VOLATAGESUPPLIED_27_36;//in range 2.7-3.6V
    uint8_t checkPattern = 0xAA;
    st_Mci_CmdInfo cmdIf;
   
    CmdArgument = (voltageSupplied << MCI_CMD8_VOLTAGESUPPLIED_POS) | (checkPattern << MCI_CMD8_CHECKPATTERN_POS);

    retryCount = 20;

    cmdIf.CmdIndex = CMD8_SEND_IF_COND;
    cmdIf.Argument = CmdArgument;
    cmdIf.ExpectResp = EXPECT_SHORT_RESP;
    cmdIf.AllowTimeout = ALLOW_CMD_TIMER;
    cmdIf.CmdResp = (uint32_t *)&respValue[0];
    while ( retryCount > 0 )
    {
        respStatus = MCI_CmdResp(&cmdIf);

        if(respStatus & MCI_CMD_TIMEOUT)
        {
            //Consider as no response
            retval = MCI_FUNC_TIMEOUT;
        }
        else if (((respValue[0]>>MCI_CMD8_CHECKPATTERN_POS) & MCI_CMD8_CHECKPATTERN_BMASK) != checkPattern)
        {
            return MCI_FUNC_BAD_PARAMETERS;
        }
        else if (((respValue[0] >> MCI_CMD8_VOLTAGESUPPLIED_POS) & MCI_CMD8_VOLTAGESUPPLIED_BMASK)
                        != voltageSupplied)
        {
            return MCI_FUNC_BAD_PARAMETERS;
        }
        else
        {
            return MCI_FUNC_OK;
        }

        for ( i = 0; i < 0x20; i++ );

        retryCount--;
    }

    return retval;
}


/************************************************************************//**
 * @brief        Send CMD55 (APP_CMD) to indicate to the card that the next
 *               command is an application specific command rather than a 
 *               standard command. Before an ACMD, call this routine first
 *
 * @param        None
 *
 * @return       MCI_FUNC_OK if all success
 ****************************************************************************/
int32_t MCI_Cmd_SendACMD( void )
{
    volatile uint32_t i;
    uint32_t retryCount;
    uint32_t CmdArgument;
    uint32_t respStatus;
    uint32_t respValue[4];
    st_Mci_CmdInfo cmdIf;
    int32_t retval = MCI_FUNC_FAILED;

    if ((MCI_CardType == MCI_SDSC_V1_CARD) ||
        (MCI_CardType == MCI_SDSC_V2_CARD) ||
        (MCI_CardType == MCI_SDHC_SDXC_CARD)) 
    {
        CmdArgument = CardRCA;    /* Use the address from SET_RELATIVE_ADDR cmd */
    }
    else            /* if MMC or unknown card type, use 0x0. */
    {
        CmdArgument = 0x00000000;
    }

    retryCount = 20;

    cmdIf.CmdIndex = CMD55_APP_CMD;
    cmdIf.Argument = CmdArgument;
    cmdIf.ExpectResp = EXPECT_SHORT_RESP;
    cmdIf.AllowTimeout = ALLOW_CMD_TIMER;
    cmdIf.CmdResp = (uint32_t *)&respValue[0];
    while ( retryCount > 0 )
    {
        respStatus = MCI_CmdResp(&cmdIf);

        if(respStatus != 0)
        {
            retval = MCI_FUNC_FAILED;
        }
        else if (respValue[0] & CARD_STATUS_ACMD_ENABLE)
        {
            retval = MCI_FUNC_OK;
            break;
        }
        else
        {
            retval = MCI_FUNC_NOT_READY;
        }

        for ( i = 0; i < 0x20; i++ );

        retryCount--;
    }

    return retval;
}


/************************************************************************//**
 * @brief        Send ACMD41 (SEND_APP_OP_COND) to Host Capacity Support (HCS)
 *               information and asks the accessed card to send its operating
 *               condition (OCR).
 *
 * @param[in]    hcsVal input the Host Capacity Support
 *
 * @return       MCI_FUNC_OK if all success
 *
 * @note         If SEND_APP_OP_COND is timeout, the card in the slot is not MMC
 *                type, try this combination to see if we can communicate with
 *                a SD type.
 ****************************************************************************/
int32_t MCI_Acmd_SendOpCond(uint8_t hcsVal)
{
    volatile uint32_t i;
    uint32_t retryCount;
    uint32_t respStatus, argument;
    uint32_t respValue[4];
    st_Mci_CmdInfo cmdIf;

    int32_t retval = MCI_FUNC_FAILED;

    argument = OCR_INDEX | (hcsVal << MCI_ACMD41_HCS_POS);

    /* timeout on SEND_OP_COND command on MMC, now, try SEND_APP_OP_COND
    command to SD */
    retryCount = 0x2000;            /* reset retry counter */
    
    cmdIf.CmdIndex = ACMD41_SEND_APP_OP_COND;
    cmdIf.Argument = argument;
    cmdIf.ExpectResp = EXPECT_SHORT_RESP;
    cmdIf.AllowTimeout = ALLOW_CMD_TIMER;
    cmdIf.CmdResp = (uint32_t *)&respValue[0];

    /* Clear Open Drain output control for SD */
    MCI_SetOutputMode(MCI_OUTPUT_MODE_PUSHPULL);

    /* The host repeatedly issues ACMD41 for at least 1 second or */
    /* until the busy bit are set to 1 */
    while ( retryCount > 0 )
    {
        if ((retval = MCI_Cmd_SendACMD()) == MCI_FUNC_OK)
        {   
            respStatus = MCI_CmdResp(&cmdIf);

            if(respStatus & MCI_CMD_TIMEOUT)
            {
                retval = MCI_FUNC_TIMEOUT;
            }
            else if (!(respValue[0] & 0x80000000))
            {
                retval = MCI_FUNC_BUS_NOT_IDLE;
            }
            else
            {
                CCS = (respValue[0]&(1<<30)) ? 1:0;
                retval = MCI_FUNC_OK;
                break;
            }
        }
        else    /* The command isn't accepted by the card.*/
        {
            return retval;
        }

        for ( i = 0; i < 0x20; i++ );

        retryCount--;
    }

    return retval;
}

/************************************************************************//**
 * @brief         Do initialization for the card in the slot
 *
 * @details        Try CMD1 first for MMC, if it's timeout, try CMD55
 *                and CMD41 for SD, if both failed, initialization faliure,
 *                bailout with unknown card type. Otherwise, return the
 *                card type, either MMC or SD. <<<KHOA_110708: checking>>>
 *
 *                This is followed Figure 4-2: Card Initialization and
 *                Identification Flow (SD mode) in Physical Layer Simplified
 *                Specification Version 2.00 document        
 *
 * @param         None
 *
 * @return        MCI_FUNC_OK if success
 ****************************************************************************/
int32_t MCI_CardInit( void )
{
    volatile uint32_t i;
    int32_t retval = MCI_FUNC_FAILED;

    MCI_CardType = MCI_CARD_UNKNOWN;

    if (MCI_CardReset() != MCI_FUNC_OK)
    {
        return MCI_FUNC_FAILED;
    }

    /* Clear Open Drain output control for SD */
    MCI_SetOutputMode(MCI_OUTPUT_MODE_PUSHPULL);

    for ( i = 0; i < 0x3000; i++ );

    retval = MCI_Cmd_SendIfCond();

    if(retval == MCI_FUNC_BAD_PARAMETERS)
    {
        //Unknow card is unusable
        return retval;
    }

    if(retval == MCI_FUNC_OK) /* Ver2.00 or later*/
    {
        //Check in case of High Capacity Supporting Host
        if ((retval = MCI_Acmd_SendOpCond(1)) == MCI_FUNC_OK)
        {
            MCI_CardType = MCI_SDSC_V2_CARD;//SDSC
            
            if(CCS )
            {
                MCI_CardType = MCI_SDHC_SDXC_CARD;//SDHC or SDXC 
            }

            return MCI_FUNC_OK;    /* Found the card, it's a hD */
        }
    }

    if(retval != MCI_FUNC_OK) /* voltage mismatch (ver2.00)or ver1.X SD Card or not SD Card*/
    {
        
        //Check in case of Standard Capacity Supporting Host
        if ((retval = MCI_Acmd_SendOpCond(0)) == MCI_FUNC_OK)
        {
            MCI_CardType = MCI_SDSC_V1_CARD;//Support Standard Capacity only

            return MCI_FUNC_OK;    /* Found the card, it's a SD */
        }
    }

    if(retval != MCI_FUNC_OK)
    {
        /* Set Open Drain output control for MMC */
        MCI_SetOutputMode(MCI_OUTPUT_MODE_OPENDRAIN);

        for ( i = 0; i < 0x3000; i++ );

        /* Try CMD1 first for MMC, if it's timeout, try CMD55 and CMD41 for SD,
        if both failed, initialization faIlure, bailout. */
        if (MCI_Cmd_SendOpCond() == MCI_FUNC_OK)
        {
            MCI_CardType = MCI_MMC_CARD;

            return MCI_FUNC_OK;    /* Found the card, it's a MMC */
        }
    }

    /* tried both MMC and SD card, give up */
    return MCI_FUNC_OK;
}


/************************************************************************//**
 * @brief         Get the type of card that is currently used in the slot
 *
 * @param         None
 *
 * @return        Card Type: MMC Card or SD card
 ****************************************************************************/
en_Mci_CardType MCI_GetCardType(void)
{
    return MCI_CardType;
}


/************************************************************************//**
 * @brief         Get the all the Identifier (CID) of the card by sending the 
 *                CMD2 (ALL_SEND_CID) command. Then parse 4-byte data obtained
 *                from the card by the CID meaning.    
 *
 * @param[out]    cidValue the CID Result after parsing the data from the card
 *
 * @return        MCI_FUNC_OK if all success
 ****************************************************************************/
int32_t MCI_GetCID(st_Mci_CardId* cidValue)
{
    volatile uint32_t i;
    uint32_t retryCount;
    uint32_t respStatus;
    uint32_t respValue[4];
    st_Mci_CmdInfo cmdIf;
    
    /* This command is normally after CMD1(MMC) or ACMD41(SD). */
    retryCount = 0x200;// 0x20;            /* reset retry counter */
    
    cmdIf.CmdIndex = CMD2_ALL_SEND_CID;
    cmdIf.Argument = 0;
    cmdIf.ExpectResp = EXPECT_LONG_RESP;
    cmdIf.AllowTimeout = ALLOW_CMD_TIMER;
    cmdIf.CmdResp = (uint32_t *)&respValue[0];
    while ( retryCount > 0 )
    {
        respStatus = MCI_CmdResp(&cmdIf);

        /* bit 0 and bit 2 must be zero, or it's timeout or CRC error */
        //if ((!(respStatus & MCI_CMD_TIMEOUT)) && (!(respStatus & MCI_CMD_CRC_FAIL)))
        if (!(respStatus & MCI_CMD_TIMEOUT))
        {
            // Parsing the data retrieved
            if(cidValue != NULL)
            {
                cidValue->MID = (respValue[0] >> MCI_CID_MANUFACTURER_ID_WPOS) & MCI_CID_MANUFACTURER_ID_WBMASK;

                cidValue->OID = (respValue[0] >> MCI_CID_OEMAPPLICATION_ID_WPOS) & MCI_CID_OEMAPPLICATION_ID_WBMASK;

                cidValue->PNM_H = (respValue[0] >> MCI_CID_PRODUCTNAME_ID_H_WPOS) & MCI_CID_PRODUCTNAME_ID_H_WBMASK;

                cidValue->PNM_L = (respValue[1] >> MCI_CID_PRODUCTNAME_ID_L_WPOS) & MCI_CID_PRODUCTNAME_ID_L_WBMASK;

                cidValue->PRV = (respValue[2] >> MCI_CID_PRODUCTREVISION_ID_WPOS) & MCI_CID_PRODUCTREVISION_ID_WBMASK;

                cidValue->PSN = (((respValue[2] >> MCI_CID_PRODUCTSERIALNUM_ID_H_WPOS) & MCI_CID_PRODUCTSERIALNUM_ID_H_WBMASK) << 8)
                                            | ((respValue[3] >> MCI_CID_PRODUCTSERIALNUM_ID_L_WPOS) & MCI_CID_PRODUCTSERIALNUM_ID_L_WBMASK);

                cidValue->reserved = (respValue[3] >> MCI_CID_RESERVED_ID_WPOS) & MCI_CID_RESERVED_ID_WBMASK;

                cidValue->MDT = (respValue[3] >> MCI_CID_MANUFACTURINGDATE_ID_WPOS) & MCI_CID_MANUFACTURINGDATE_ID_WBMASK;

                cidValue->CRC = (respValue[3] >> MCI_CID_CHECKSUM_ID_WPOS) & MCI_CID_CHECKSUM_ID_WBMASK;

                cidValue->unused = (respValue[3] >> MCI_CID_UNUSED_ID_WPOS) & MCI_CID_UNUSED_ID_WBMASK;

            }

            return  MCI_FUNC_OK;    /* response is back and correct. */
        }


        for ( i = 0; i < 0x20; i++ );

        retryCount--;
    }

    return MCI_FUNC_TIMEOUT;
}


/************************************************************************//**
 * @brief        Set the address for the card in the slot by sending CMD3 
 *                (SET_RELATIVE_ADDR) command. To get the address of the card
 *                currently in used, needs to call MCI_GetCardAddress()
 *
 * @param        None
 *
 * @return       MCI_FUNC_OK if all success
 ****************************************************************************/
int32_t MCI_SetCardAddress( void )
{
    volatile uint32_t i;
    uint32_t retryCount;
    uint32_t respStatus;
    uint32_t respValue;
    uint32_t CmdArgument;
    st_Mci_CmdInfo cmdIf;
    int32_t retval = MCI_FUNC_FAILED;
    
    /* If it's a SD card, SET_RELATIVE_ADDR is to get the address
    from the card and use this value in RCA, if it's a MMC, set default
    RCA addr. 0x00010000. */
    if ((MCI_CardType == MCI_SDSC_V1_CARD) ||
        (MCI_CardType == MCI_SDSC_V2_CARD) ||
        (MCI_CardType == MCI_SDHC_SDXC_CARD))
    {
        CmdArgument = 0;
    }
    else            /* If it's unknown or MMC_CARD, fix the RCA address */
    {
        CmdArgument = 0x00010000;
    }

    retryCount = 0x20;            /* reset retry counter */
    cmdIf.CmdIndex = CMD3_SET_RELATIVE_ADDR;
    cmdIf.Argument = CmdArgument;
    cmdIf.ExpectResp = EXPECT_SHORT_RESP;
    cmdIf.AllowTimeout = ALLOW_CMD_TIMER;
    cmdIf.CmdResp = &respValue;
    while ( retryCount > 0 )
    {
        /* Send CMD3 command repeatedly until the response is back correctly */
        respStatus = MCI_CmdResp(&cmdIf);

        if(respStatus & MCI_CMD_TIMEOUT)
        {
            retval = MCI_FUNC_TIMEOUT;
        }
        else if(!((respValue >> RCA_RES_CARD_STATUS_POS)& CARD_STATUS_READY_FOR_DATA))
        {
            retval = MCI_FUNC_NOT_READY;
        }
        else if((CARDSTATEOF(respValue) != MCI_CARDSTATE_IDENDTIFIED))
        {
            retval = MCI_FUNC_ERR_STATE;
        }
        else
        {
            CardRCA = (respValue >> RCA_RES_NEW_PUBLISHED_RCA_POS) & RCA_RES_NEW_PUBLISHED_RCA_MASK;    /* Save the RCA value from SD card */

            CardRCA <<= RCA_ARGUMENT_POS;

            MCI_SetOutputMode(MCI_OUTPUT_MODE_PUSHPULL);
            
            return (MCI_FUNC_OK);    /* response is back and correct. */
        }

        for ( i = 0; i < 0x20; i++ );

        retryCount--;
    }

    return retval;
}


/************************************************************************//**
 * @brief        Get the address for the card in the slot
 *
 * @param        None
 *
 * @return       MCI_FUNC_OK if all success
 *
 * @note        This function must be called after MCI_SetCardAddress() executing
 ****************************************************************************/
uint32_t MCI_GetCardAddress(void)
{
    return CardRCA;
}


/************************************************************************//**
 * @brief       Get the Card-Specific Data of in-slot card by sending CMD9
 *                (SEND_CSD) command
 *
 * @param[out]  csdVal a buffer stored the value of CSD obtained from the card
 *
 * @return      MCI_FUNC_OK if all success
 *
 * @note        CMD9 (SEND_CSD) command should be sent only at standby state 
 *                (STBY) after CMD3
 ****************************************************************************/
int32_t MCI_GetCSD(uint32_t* csdVal)
{
    volatile uint32_t i;
    uint32_t retryCount;
    uint32_t respStatus;
    uint32_t respValue[4];
    uint32_t CmdArgument;
    st_Mci_CmdInfo cmdIf;

    if ((MCI_CardType == MCI_SDSC_V1_CARD) ||
        (MCI_CardType == MCI_SDSC_V2_CARD) ||
        (MCI_CardType == MCI_SDHC_SDXC_CARD))
    {
        CmdArgument = CardRCA;
    }
    else            /* if MMC or unknown card type, use default RCA addr. */
    {
        CmdArgument = 0x00010000;
    }

    retryCount = 0x20;
    cmdIf.CmdIndex = CMD9_SEND_CSD;
    cmdIf.Argument = CmdArgument;
    cmdIf.ExpectResp = EXPECT_LONG_RESP;
    cmdIf.AllowTimeout = ALLOW_CMD_TIMER;
    cmdIf.CmdResp = (uint32_t *)&respValue[0];
    while ( retryCount > 0 )
    {
         /* Check current status */
       if(((MCI_CheckStatus(CARD_STATE_STBY) != MCI_FUNC_OK)))
            return MCI_FUNC_ERR_STATE;

        respStatus = MCI_CmdResp(&cmdIf);

        if ( !respStatus )
        {
            if(csdVal != NULL)
            {
                csdVal[0] = respValue[0];
                csdVal[1] = respValue[1];
                csdVal[2] = respValue[2];
                csdVal[3] = respValue[3];
            }

            return (MCI_FUNC_OK);
        }

        for ( i = 0; i < 0x20; i++ );

        retryCount--;
    }

    return (MCI_FUNC_FAILED);
}


/************************************************************************//**
 * @brief       Select the card by the specified address. This is done by sending
 *              out the CMD7 with the address argument to needed card
 *
 * @param       None
 *
 * @return      MCI_FUNC_OK if all success
 *
 * @note        CMD7 (SELECT_CARD) command should be sent after CMD9 ((SEND_CSD).
 *                The state will be inter-changed between STBY to TRANS by this 
 *                CMD7 command
 ****************************************************************************/
int32_t MCI_Cmd_SelectCard( void )
{
    volatile uint32_t i;
    uint32_t retryCount;
    uint32_t respStatus;
    uint32_t respValue[4];
    uint32_t CmdArgument;
    st_Mci_CmdInfo cmdIf;
    int32_t retval = MCI_FUNC_FAILED;

    if ((MCI_CardType == MCI_SDSC_V1_CARD) ||
            (MCI_CardType == MCI_SDSC_V2_CARD) ||
            (MCI_CardType == MCI_SDHC_SDXC_CARD)) 
    {
        CmdArgument = CardRCA;
    }
    else            /* if MMC or unknown card type, use default RCA addr. */
    {
        CmdArgument = 0x00010000;
    }

    retryCount = 0x20;
    cmdIf.CmdIndex = CMD7_SELECT_CARD;
    cmdIf.Argument = CmdArgument;
    cmdIf.ExpectResp = EXPECT_SHORT_RESP;
    cmdIf.AllowTimeout = ALLOW_CMD_TIMER;
    cmdIf.CmdResp =  (uint32_t *)&respValue[0];
    while ( retryCount > 0 )
    {
         /* Check current status */
       if(((MCI_CheckStatus(CARD_STATE_STBY) != MCI_FUNC_OK)) &&
            (MCI_CheckStatus(CARD_STATE_TRAN) != MCI_FUNC_OK) &&
            (MCI_CheckStatus(CARD_STATE_DATA) != MCI_FUNC_OK) &&
            (MCI_CheckStatus(CARD_STATE_PRG) != MCI_FUNC_OK) &&
            (MCI_CheckStatus(CARD_STATE_DIS) != MCI_FUNC_OK))
            return MCI_FUNC_ERR_STATE;

        respStatus = MCI_CmdResp(&cmdIf);

        if(respStatus)
        {
            retval = MCI_FUNC_FAILED;
        }
        else if (respValue[0] & CARD_STATUS_ERR_MASK)
        {
            return MCI_FUNC_BAD_PARAMETERS;
        }
        else
        {
            if(((MCI_CheckStatus(CARD_STATE_STBY) != MCI_FUNC_OK)) &&
                (MCI_CheckStatus(CARD_STATE_TRAN) != MCI_FUNC_OK) &&
                (MCI_CheckStatus(CARD_STATE_PRG) != MCI_FUNC_OK) &&
                (MCI_CheckStatus(CARD_STATE_DIS) != MCI_FUNC_OK))
                return MCI_FUNC_ERR_STATE;
            return MCI_FUNC_OK;
        }

        for ( i = 0; i < 0x20; i++ );

        retryCount--;
    }

    return retval;
}


/************************************************************************//**
 * @brief         Get the status of the card. The return is from the card.
 *                By sending CMD13 (SEND_STATUS), the status of the card
 *                will be responded from card addressed
 *
 * @param[out]    cardStatus the status returned from the card
 *
 * @return        MCI_FUNC_OK if all success
 ****************************************************************************/
int32_t MCI_GetCardStatus(int32_t* cardStatus)
{
    volatile uint32_t i;
    uint32_t retryCount;
    uint32_t respStatus;
    uint32_t respValue[4];
    uint32_t CmdArgument;
    st_Mci_CmdInfo cmdIf;
    int32_t retval = MCI_FUNC_FAILED;

    if(cardStatus == NULL)
        return MCI_FUNC_OK;
    
    if ((MCI_CardType == MCI_SDSC_V1_CARD) ||
        (MCI_CardType == MCI_SDSC_V2_CARD) ||
        (MCI_CardType == MCI_SDHC_SDXC_CARD)) 
    {
        CmdArgument = CardRCA;
    }
    else            /* if MMC or unknown card type, use default RCA addr. */
    {
        CmdArgument = 0x00010000;
    }

    retryCount = 0x20;
    cmdIf.CmdIndex = CMD13_SEND_STATUS;
    cmdIf.Argument = CmdArgument;
    cmdIf.ExpectResp = EXPECT_SHORT_RESP;
    cmdIf.AllowTimeout = ALLOW_CMD_TIMER;
    cmdIf.CmdResp =  (uint32_t *)&respValue[0];
    while ( retryCount > 0 )
    {
        respStatus = MCI_CmdResp(&cmdIf);

        if(respStatus)  /* only retry if sending command failed */
        {
            retval = MCI_FUNC_FAILED;
        }
        else
        {
            *cardStatus = respValue[0];

            return MCI_FUNC_OK;
        }

        retryCount--;
        for ( i = 0; i < 0x10; i++ );
    }

    return retval;
}

/************************************************************************//**
 * @brief        Set the length for the blocks in the next action on data 
 *                manipulation (as read, write, erase). This function is to
 *                send CMD16 (SET_BLOCK_LEN) to cards.
 *
 * @param[in]    blockLength the value for the length of block will be handled
 *
 * @return         MCI_FUNC_OK if all success
 *
 * @note         CMD16 command should be sent after the card is selected by CMD7 
 *                (SELECT_CARD).
 *  In the case of SDHC and SDXC Cards, block length set by CMD16 command doen't 
 *  affect memory read and write commands. Always 512 Bytes fixed block length is 
 *  used. This command is effective for LOCK_UNLOCK command..
 ****************************************************************************/
int32_t MCI_SetBlockLen(uint32_t blockLength)
{
    volatile uint32_t i;
    uint32_t retryCount;
    uint32_t respStatus;
    uint32_t respValue[4];
    st_Mci_CmdInfo cmdIf;
    int32_t retval = MCI_FUNC_FAILED;

    retryCount = 0x20;
    cmdIf.CmdIndex = CMD16_SET_BLOCK_LEN;
    cmdIf.Argument = blockLength;
    cmdIf.ExpectResp = EXPECT_SHORT_RESP;
    cmdIf.AllowTimeout = ALLOW_CMD_TIMER;
    cmdIf.CmdResp =  (uint32_t *)&respValue[0];
    while ( retryCount > 0 )
    {
         /* Check current status */
       if((MCI_CheckStatus(CARD_STATE_TRAN) != MCI_FUNC_OK) )
            return MCI_FUNC_ERR_STATE;

        respStatus = MCI_CmdResp(&cmdIf);

        if(respStatus)
        {
            retval = MCI_FUNC_FAILED;
        }
        else if (respValue[0] & CARD_STATUS_ERR_MASK)
        {
            return MCI_FUNC_BAD_PARAMETERS;
        }
        else
        {
            return MCI_CheckStatus(CARD_STATE_TRAN);
        }
        

        for ( i = 0; i < 0x20; i++ );

        retryCount--;
    }

    return retval;
}


/************************************************************************//**
 * @brief         Set bus-width (1 bit or 4 bit) to work with the card by command
 *                CMD6 (SET_ACMD_BUS_WIDTH).
 *
 * @param[in]    buswidth The value represented for bus-width
 *                - 0b00: 1-bit bus-width
 *                - 0b10: 4-bit bus-width
 *
 * @return         MCI_FUNC_OK if all success
 *
 * @note        
 *                - If SD card is currently in used, it's possible to enable 4-bit
 *                bus-width instead of 1-bit to speed up.
 *                - This command can only be transferred during TRANS state.
 *                - Since, it's a ACMD, CMD55 (APP_CMD) needs to be sent out first
 ****************************************************************************/
int32_t MCI_Acmd_SendBusWidth( uint32_t buswidth )
{
    volatile uint32_t i;
    uint32_t retryCount;
    uint32_t respStatus;
    uint32_t respValue[4];
    st_Mci_CmdInfo cmdIf;
    int32_t retval = MCI_FUNC_FAILED;

    retryCount = 0x20;            /* reset retry counter */
    cmdIf.CmdIndex = ACMD6_SET_BUS_WIDTH;
    cmdIf.Argument = buswidth;
    cmdIf.ExpectResp = EXPECT_SHORT_RESP;
    cmdIf.AllowTimeout = ALLOW_CMD_TIMER;
    cmdIf.CmdResp =  (uint32_t *)&respValue[0];
    while ( retryCount > 0 )
    {
         /* The card must be in tran state in order to change the bus width */
        retval = MCI_CheckStatus(CARD_STATE_TRAN);
        if(retval!= MCI_FUNC_OK)
            return retval;
    
        if (MCI_Cmd_SendACMD() == MCI_FUNC_OK)
        {
            respStatus = MCI_CmdResp(&cmdIf);

            if(respStatus)
            {
                retval = MCI_FUNC_FAILED;
            }
            else if (respValue[0] & CARD_STATUS_ERR_MASK)
            {
                return MCI_FUNC_BAD_PARAMETERS;
            }
            else
            {
                return MCI_CheckStatus(CARD_STATE_TRAN);
            }
        }

        for ( i = 0; i < 0x20; i++ );

        retryCount--;
    }

    return retval;
}


/************************************************************************//**
 * @brief        Get the state of  data transfer to see if it is ended or not
 *
 * @param        None
 *
 * @return       Transfer state (stored by Mci_Data_Xfer_End variable)
 ****************************************************************************/
uint32_t MCI_GetDataXferEndState(void)
{
    return Mci_Data_Xfer_End;
}
/************************************************************************//**
 * @brief        Get the error state of  the lastest data transfer
 *
 * @param        None
 *
 * @return       Error state (stored by Mci_Data_Xfer_ERR variable)
 ****************************************************************************/
uint32_t MCI_GetXferErrState(void)
{
    return Mci_Data_Xfer_ERR;
}

/************************************************************************//**
 * @brief        Stop the current transmission on the bus by sending command CMD12
 *                (STOP_TRANSMISSION). In this case, the card may be in a unknown
 *                state. So that it need a warm reset for normal operation.
 *
 * @param[in]    None
 *
 * @return       MCI_FUNC_OK if all success
 ****************************************************************************/
int32_t MCI_Cmd_StopTransmission( void )
{
    volatile uint32_t i;
    uint32_t retryCount;
    uint32_t respStatus;
    uint32_t respValue[4];
    st_Mci_CmdInfo cmdIf;
    int32_t retval = MCI_FUNC_FAILED;

    /* do nothing when the card is in tran state */
    if(MCI_CheckStatus(CARD_STATE_TRAN) == MCI_FUNC_OK) 
    {
        return MCI_FUNC_OK;
    }
    
    retryCount = 0x20;
    cmdIf.CmdIndex = CMD12_STOP_TRANSMISSION;
    cmdIf.Argument = 0x00000000;
    cmdIf.ExpectResp = EXPECT_SHORT_RESP;
    cmdIf.AllowTimeout = ALLOW_CMD_TIMER;
    cmdIf.CmdResp =  (uint32_t *)&respValue[0];
    while ( retryCount > 0 )
    {
        /* Check current status */
         if((MCI_CheckStatus(CARD_STATE_DATA) != MCI_FUNC_OK) &&
              (MCI_CheckStatus(CARD_STATE_RCV) != MCI_FUNC_OK))
              return MCI_FUNC_ERR_STATE;
         
        respStatus = MCI_CmdResp(&cmdIf);

        if(respStatus)
        {
            retval = MCI_FUNC_FAILED;
        }
        else if (respValue[0] & CARD_STATUS_ERR_MASK)
        {
            return MCI_FUNC_BAD_PARAMETERS;
        }
        else
        {
            if((MCI_CheckStatus(CARD_STATE_PRG) != MCI_FUNC_OK) &&
              (MCI_CheckStatus(CARD_STATE_TRAN) != MCI_FUNC_OK))
              return MCI_FUNC_ERR_STATE;
            return MCI_FUNC_OK;
        }

        for ( i = 0; i < 0x20; i++ );

        retryCount--;
    }

    return retval;
}


/************************************************************************//**
 * @brief        Write blocks to card by sending command CMD24 (WRITE_BLOCK) or
 *                command CMD25 (WRITE_MULTIPLE_BLOCK) followed by the blocks of
 *                data to be written.
 *
 * @param[in]    blockNum The block number to start writting
 *
 * @param[in]    numOfBlock Determine how many blocks will be written (from the
 *                starting block)
 *
 * @return       MCI_FUNC_OK if all success
 *
 * @note        These commands should be sent in TRANS state.
 ****************************************************************************/
int32_t MCI_Cmd_WriteBlock(uint32_t blockNum, uint32_t numOfBlock)
{
    volatile uint32_t i;
    uint32_t retryCount;
    uint32_t respStatus;
    uint32_t respValue[4];
    st_Mci_CmdInfo cmdIf;
    uint32_t commandID;

    int32_t retval = MCI_FUNC_FAILED;

    if (numOfBlock > 1)
    {
        commandID = CMD25_WRITE_MULTIPLE_BLOCK;
    }
    else
    {
        commandID = CMD24_WRITE_BLOCK;
    }
    
    retryCount = 0x20;
    cmdIf.CmdIndex = commandID;
    if (MCI_CardType == MCI_SDHC_SDXC_CARD)
    {
        cmdIf.Argument = blockNum;                      /* Block Address */
    }
    else            
    {
        cmdIf.Argument = blockNum * BLOCK_LENGTH;       /* Byte Address */
    }     
    cmdIf.ExpectResp = EXPECT_SHORT_RESP;
    cmdIf.AllowTimeout = ALLOW_CMD_TIMER;
    cmdIf.CmdResp =  (uint32_t *)&respValue[0];
    
    while ( retryCount > 0 )
    {
         /* Check current status */
        if((MCI_CheckStatus(CARD_STATE_TRAN) != MCI_FUNC_OK))
            return MCI_FUNC_ERR_STATE;
   
        respStatus = MCI_CmdResp(&cmdIf);

        if(respStatus)
        {
            retval = MCI_FUNC_FAILED;
        }
        else if (respValue[0] & CARD_STATUS_ERR_MASK)
        {
            return MCI_FUNC_BAD_PARAMETERS;
        }
        else 
        {
            if((MCI_CheckStatus(CARD_STATE_RCV) != MCI_FUNC_OK) &&
              (MCI_CheckStatus(CARD_STATE_TRAN) != MCI_FUNC_OK))
              return MCI_FUNC_ERR_STATE;
            return MCI_FUNC_OK;
        }
        

        for ( i = 0; i < 0x20; i++ );

        retryCount--;

    }

    return retval;                /* Fatal error */
}




/************************************************************************//**
 * @brief        Read blocks to card by sending CMD17 (READ_SINGLE_BLOCK) or
 *                CMD18 (READ_MULTIPLE_BLOCK) commands followed by the blocks of
 *                data to be read.
 *
 * @param[in]    blockNum The block number to start reading
 *
 * @param[in]    numOfBlock Determine how many blocks will be read (from the
 *                starting block)
 *
 * @return       MCI_FUNC_OK if all success
 *
 * @note        These commands should be sent in TRANS state.
 ****************************************************************************/
int32_t MCI_Cmd_ReadBlock(uint32_t blockNum, uint32_t numOfBlock)
{
    volatile uint32_t i;
    uint32_t retryCount;
    uint32_t respStatus;
    uint32_t respValue[4];
    uint32_t commandID;
    st_Mci_CmdInfo cmdIf;
    int32_t retval = MCI_FUNC_FAILED;
  
    // To Do: Read Multi-Block
    if (numOfBlock > 1)
        commandID = CMD18_READ_MULTIPLE_BLOCK;
    else
        commandID = CMD17_READ_SINGLE_BLOCK;

    retryCount = 0x20;
    cmdIf.CmdIndex = commandID;
    if (MCI_CardType == MCI_SDHC_SDXC_CARD)
    {
        cmdIf.Argument = blockNum;                      /* Block Address */
    }
    else            
    {
        cmdIf.Argument = blockNum * BLOCK_LENGTH;       /* Byte Address */
    }    
    cmdIf.ExpectResp = EXPECT_SHORT_RESP;
    cmdIf.AllowTimeout = ALLOW_CMD_TIMER;
    cmdIf.CmdResp =  (uint32_t *)&respValue[0];
    while ( retryCount > 0 )
    {
         /* Check current status */
        if((MCI_CheckStatus(CARD_STATE_TRAN) != MCI_FUNC_OK))
            return MCI_FUNC_ERR_STATE;
        
        respStatus = MCI_CmdResp(&cmdIf);

        if(respStatus)
        {
            retval = MCI_FUNC_FAILED;
        }
        else if (respValue[0] & CARD_STATUS_ERR_MASK)
        {
            return MCI_FUNC_BAD_PARAMETERS;
        }
        else
        {
            if((MCI_CheckStatus(CARD_STATE_DATA) != MCI_FUNC_OK) &&
              (MCI_CheckStatus(CARD_STATE_TRAN) != MCI_FUNC_OK))
              return MCI_FUNC_ERR_STATE;
            return MCI_FUNC_OK;
        }
       

        for ( i = 0; i < 0x20; i++ );

        retryCount--;
         
    }

    return retval;
}


/************************************************************************//**
 * @brief         Write data at a specific address to starting block with number
 *                of blocks will be written from first block
 * @details        
 *                - At preparation
 *                    - Set MCI data control register, data length and data timeout
 *                    - Send CMD24 (WRITE_BLOCK) or CMD25 (WRITE_MULTIPLE_BLOCK)
 *                    commands to card
 *                    - Enable interupt for MCI component
 *                - At completion
 *                    - TX_ACTIVE interrupt is occured
 *                    - Write data to FIFO register continuously until the data block
 *                    length is reached
 *
 * @param[in]    *memblock The pointer to location stored required data to be
 *                written to card
 *
 * @param[in]    blockNum The block number to start writting
 *
 * @param[in]    numOfBlock Determine how many blocks will be written (from the
 *                starting block)
 *
 * @return         MCI_FUNC_OK if all success
 ****************************************************************************/
int32_t MCI_WriteBlock(volatile uint8_t* memblock, uint32_t blockNum, uint32_t numOfBlock)
{
    volatile uint32_t i;
    uint32_t DataCtrl = 0;

    if(BLOCK_LENGTH*numOfBlock > DATA_RW_MAX_LEN)
        return MCI_FUNC_BAD_PARAMETERS;
    
    dataSrcBlock = memblock;

    LPC_MCI->CLEAR = 0x7FF;

    LPC_MCI->DATACTRL = 0;

    for ( i = 0; i < 0x10; i++ );

    /* Wait the SD Card enters to TRANS state. */
    if (MCI_CheckStatus(CARD_STATE_TRAN) != MCI_FUNC_OK)
        return MCI_FUNC_ERR_STATE;
    
    LPC_MCI->DATATMR = DATA_TIMER_VALUE_W;

    LPC_MCI->DATALEN = BLOCK_LENGTH*numOfBlock;

    Mci_Data_Xfer_End = 1;
    Mci_Data_Xfer_ERR = 0;
    fifo_plane = 0;

    txBlockCnt = 0;

    MCI_TXEnable();

    if (MCI_Cmd_WriteBlock(blockNum, numOfBlock) != MCI_FUNC_OK)
    {
        return ( MCI_FUNC_FAILED );
    }

    //for(blockCnt = 0; blockCnt < numOfBlock; blockCnt++)
    {
#if MCI_DMA_ENABLED
        MCI_SettingDma((uint8_t*) dataSrcBlock, MCI_DMA_WRITE_CHANNEL, GPDMA_TRANSFERTYPE_M2P_DEST_CTRL);
        
        /* Write, block transfer, DMA, and data length */
        DataCtrl |= MCI_DATACTRL_ENABLE | MCI_DATACTRL_DIR_TO_CARD 
                        | MCI_DATACTRL_DMA_ENABLE | MCI_DTATCTRL_BLOCKSIZE(DATA_BLOCK_LEN);
#else
        /* Write, block transfer, and data length */
        DataCtrl |= MCI_DATACTRL_ENABLE  | MCI_DATACTRL_DIR_TO_CARD  | MCI_DTATCTRL_BLOCKSIZE(DATA_BLOCK_LEN);
#endif
    }

    LPC_MCI->DATACTRL = DataCtrl;

    for ( i = 0; i < 0x10; i++ );

    return MCI_FUNC_OK;
}


/************************************************************************//**
 * @brief         Read data at a specific address to starting block with number
 *                of blocks will be read from first block
 *
 * @details        
 *                - At preparation
 *                    - Set MCI data control register, data length and data timeout
 *                    - Send CMD17 (READ_SINGLE_BLOCK) or CMD18 (READ_MULTIPLE_BLOCK)
 *                    commands to card
 *                    - Enable interupt for MCI component
 *                - At completion
 *                    - RX_ACTIVE interrupt is occured
 *                    - Read data from FIFO register continuously until the data block
 *                    length is reached to retrieve needed data
 *
 * @param[in]    *destBlock The pointer to location will captured data read
 *                from card
 *
 * @param[in]    blockNum The block number to start reading
 *
 * @param[in]    numOfBlock Determine how many blocks will be read (from the
 *                starting block)
 *
 * @return         MCI_FUNC_OK if all success
 ****************************************************************************/
int32_t MCI_ReadBlock(volatile uint8_t* destBlock, uint32_t blockNum, uint32_t numOfBlock)
{
    volatile uint32_t i;
    uint32_t DataCtrl = 0;

    if(BLOCK_LENGTH*numOfBlock > DATA_RW_MAX_LEN)
        return MCI_FUNC_BAD_PARAMETERS;
    
    dataDestBlock = destBlock;

    LPC_MCI->CLEAR = 0x7FF;

    LPC_MCI->DATACTRL = 0;

    for ( i = 0; i < 0x10; i++ );

    /* Wait the SD Card enters to TRANS state. */
    if (MCI_CheckStatus(CARD_STATE_TRAN) != MCI_FUNC_OK)
        return MCI_FUNC_ERR_STATE;
    
    MCI_RXEnable();

    LPC_MCI->DATATMR = DATA_TIMER_VALUE_R;

    LPC_MCI->DATALEN = BLOCK_LENGTH*numOfBlock;

    Mci_Data_Xfer_End = 1;
    Mci_Data_Xfer_ERR = 0;
    rxBlockCnt = 0;
    fifo_plane = 0;


    // Start data engine on READ before command to avoid overflow of the FIFO.
    {        
#if MCI_DMA_ENABLED
        MCI_SettingDma((uint8_t*) dataDestBlock, MCI_DMA_READ_CHANNEL, GPDMA_TRANSFERTYPE_P2M_SRC_CTRL);

        /* Write, block transfer, DMA, and data length */
        DataCtrl |= MCI_DATACTRL_ENABLE | MCI_DATACTRL_DIR_FROM_CARD
                        | MCI_DATACTRL_DMA_ENABLE | MCI_DTATCTRL_BLOCKSIZE(DATA_BLOCK_LEN);
#else
        //Retrieving the result after reading the card is done by the FIFO handling for interrupt
        
        /* Read, enable, block transfer, and data length */
        DataCtrl |= MCI_DATACTRL_ENABLE | MCI_DATACTRL_DIR_FROM_CARD | MCI_DTATCTRL_BLOCKSIZE(DATA_BLOCK_LEN);

#endif
    }
    
    LPC_MCI->DATACTRL = DataCtrl;

    for ( i = 0; i < 0x10; i++ );

    if ( MCI_Cmd_ReadBlock(blockNum, numOfBlock) != MCI_FUNC_OK )
    {
        return MCI_FUNC_FAILED;
    }

    return MCI_FUNC_OK;
}


/************************************************************************//**
 * @brief        Turn off the MCI power by disabling the Power Register for MCI
 *
 * @param        None
 *
 * @return       None
 ****************************************************************************/
void MCI_PowerOff(void) 
{
    volatile uint32_t i;

    LPC_MCI->POWER = 0;
    
    for (i = 0; i < 0x100; i++);
    
    return;
}


/**
 * @}
 */

#endif /*_MCI*/

/*****************************************************************************
**                            End Of File
******************************************************************************/
