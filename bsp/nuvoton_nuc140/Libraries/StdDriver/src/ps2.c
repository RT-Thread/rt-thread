/**************************************************************************//**
 * @file     ps2.c
 * @version  V3.00
 * $Revision: 2 $
 * $Date: 15/05/04 3:27p $
 * @brief    PS/2 driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include "NUC100Series.h"

/*---------------------------------------------------------------------------------------------------------*/
/* Includes of local headers                                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#include "ps2.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup PS2_Driver PS2 Driver
  @{
*/


/** @addtogroup PS2_EXPORTED_FUNCTIONS PS2 Exported Functions
  @{
*/


/**
 *  @brief     Enable PS/2 Interrupt
 *
 *  @param[in] u32Mask    The specified interrupt of PS/2 module:
 *                               - PS2D_PS2CON_TXINTEN_Msk: PS/2 Tx interrupt
 *                               - PS2D_PS2CON_RXINTEN_Msk: PS/2 Rx interrupt
 *
 *  @return    None
 *
 *  @details   The function is used to enable PS/2 specified Tx or Rx interrupt.
 */
void PS2_EnableInt(uint32_t u32Mask)
{
    PS2->PS2CON |= u32Mask;
}

/**
 *  @brief      Disable PS/2 Interrupt.
 *
 *  @param[in]  u32Mask    The specified interrupt of PS2 module:
 *                               - PS2D_PS2CON_TXINTEN_Msk: PS2 Tx interrupt
 *                               - PS2D_PS2CON_RXINTEN_Msk: PS2 Rx interrupt
 *
 *  @return     None
 *
 *  @details    The function is used to disable PS/2 specified Tx or Rx interrupt.
 */
void PS2_DisableInt(uint32_t u32Mask)
{
    PS2->PS2CON &= ~u32Mask;
}

/**
 *  @brief    Enable PS/2 function and Set Parameter
 *
 *  @param    None
 *
 *  @return   None
 *
 *  @details  This function is used to enable PS/2 function and set one byte per transfer.
 */
void PS2_Open(void)
{
    /* Reset PS2 device */
    SYS->IPRSTC2 |=  SYS_IPRSTC2_PS2_RST_Msk;
    SYS->IPRSTC2 &= ~SYS_IPRSTC2_PS2_RST_Msk;

    /* Enable PS2 module */
    PS2->PS2CON |= PS2_PS2CON_PS2EN_Msk;

    /* Set One byte per transfer */
    PS2->PS2CON &= ~PS2_PS2CON_TXFIFO_DEPTH_Msk;

    /* Clear Tx FIFO */
    PS2->PS2CON |= PS2_PS2CON_CLRFIFO_Msk;
    PS2->PS2CON &= (~PS2_PS2CON_CLRFIFO_Msk);
}

/**
 *  @brief    Disable PS/2 function
 *
 *  @param    None
 *
 *  @return   None
 *
 *  @details  This function use to disable PS/2 function.
 */
void PS2_Close(void)
{
    /* Enable PS2 module */
    PS2->PS2CON &= ~PS2_PS2CON_PS2EN_Msk;
}

/**
 *  @brief    This function use to read PS/2 Rx data.
 *
 *  @param    None
 *
 *  @return   Rx data
 *
 *  @details  To get PS/2 receive 8 bits data from PS2RXDATA register.
 */
uint8_t PS2_Read(void)
{
    return (uint8_t)(PS2->PS2RXDATA & PS2_PS2RXDATA_RXDATA_Msk);
}

/**
 *  @brief        This function use to transmit PS/2 data.
 *
 *  @param[in]    pu32Buf        The buffer to send the data to PS/2 transmission FIFO.
 *  @param[in]    u32ByteCount   The byte number of data.
 *
 *  @retval       0 transmit data time-out
 *  @retval       1 transmit data successful
 *
 *  @details      Write data to PS/2 transmit FIFO and set the depth of Tx transmit bytes, then check every data transmission success or time-out.
 */
int32_t PS2_Write(uint32_t *pu32Buf, uint32_t u32ByteCount)
{
    uint32_t u32TxFIFO_Depth = 16;
    uint32_t u32delayno, txcnt, remainder;
    uint8_t i = 0;

    txcnt = u32ByteCount / u32TxFIFO_Depth;

    remainder = u32ByteCount % u32TxFIFO_Depth;
    if(remainder) txcnt++;

    u32delayno = 0;
    while(!(PS2->PS2STATUS & PS2_PS2STATUS_TXEMPTY_Msk))
    {
        u32delayno++;
        if(u32delayno >= 0xF00000)
            return FALSE; // Time Out
    }

    if(u32ByteCount >= u32TxFIFO_Depth)//Tx FIFO is 16 bytes
        PS2_SET_TX_BYTE_CNT(u32TxFIFO_Depth);

    do
    {
        u32delayno = 0;
        while(!(PS2->PS2STATUS & PS2_PS2STATUS_TXEMPTY_Msk))
        {
            u32delayno++;
            if(u32delayno >= 0xF00000)
                return FALSE; // Time Out
        }

        if((txcnt == 1) && (remainder != 0))
            PS2_SET_TX_BYTE_CNT(u32ByteCount);

        PS2->PS2TXDATA0 = pu32Buf[i];
        PS2->PS2TXDATA1 = pu32Buf[i + 1];
        PS2->PS2TXDATA2 = pu32Buf[i + 2];
        PS2->PS2TXDATA3 = pu32Buf[i + 3];

        i = i + 4;

    }
    while(--txcnt);

    u32delayno = 0;
    while(!(PS2->PS2STATUS & PS2_PS2STATUS_TXEMPTY_Msk))
    {
        u32delayno++;
        if(u32delayno >= 0xF00000)
            return FALSE; // Time Out
    }

    return TRUE;

}


/*@}*/ /* end of group PS2_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group PS2_Driver */

/*@}*/ /* end of group Device_Driver */

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/



