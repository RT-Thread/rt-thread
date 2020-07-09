/******************************************************************************
 * @file     ps2.c
 * @version  V1.00
 * $Revision: 5 $
 * $Date: 14/10/03 11:59a $
 * @brief    NUC472/NUC442 PS2 driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include "NUC472_442.h"

/*---------------------------------------------------------------------------------------------------------*/
/* Includes of local headers                                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#include "ps2.h"


/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_PS2_Driver PS2 Driver
  @{
*/


/** @addtogroup NUC472_442_PS2_EXPORTED_FUNCTIONS PS2 Exported Functions
  @{
*/


/**
 *  @brief    The function is used to enable PS2 specified interrupt.
 *
 *  @param[in]    u32Mask    The specified interrupt of PS2 module:
 *                               - \ref PS2_CTL_TXIEN_Msk : PS2 Tx interrupt
 *                               - \ref PS2_CTL_RXIEN_Msk : PS2 Rx interrupt
 *
 *  @return   None
 */
void PS2_EnableInt(uint32_t u32Mask)
{
    PS2->CTL |= u32Mask;
}

/**
 *  @brief    The function is used to disable PS2 specified interrupt.
 *
 *  @param[in]    u32Mask    The specified interrupt of PS2 module:
 *                               - \ref PS2_CTL_TXIEN_Msk : PS2 Tx interrupt
 *                               - \ref PS2_CTL_RXIEN_Msk : PS2 Rx interrupt
 *
 *  @return   None
 */
void PS2_DisableInt(uint32_t u32Mask)
{
    PS2->CTL &= ~u32Mask;
}

/**
 *  @brief    This function use to enable PS2 function and set one byte per trnasfer.
 *
 *  @param    None
 *
 *  @return   None
 */
void PS2_Open(void)
{
    /* Reset PS2 device */
    SYS->IPRST1 |=  SYS_IPRST1_PS2RST_Msk;
    SYS->IPRST1 &= ~SYS_IPRST1_PS2RST_Msk;

    /* Enable PS2 module */
    PS2->CTL |= PS2_CTL_PS2EN_Msk;

    /* Set One byte per trnasfer */
    PS2->CTL &= ~PS2_CTL_TXFDEPTH_Msk;

    /* Clear Tx FIFO */
    PS2->CTL |= PS2_CTL_CLRFIFO_Msk;
    PS2->CTL &= (~PS2_CTL_CLRFIFO_Msk);
}

/**
 *  @brief    This function use to disable PS2 function.
 *
 *  @param    None
 *
 *  @return   None
 */
void PS2_Close(void)
{
    /* Enable PS2 module */
    PS2->CTL &= ~PS2_CTL_PS2EN_Msk;
}

/**
 *  @brief    This function use to read PS2 Rx data.
 *
 *  @param    None
 *
 *  @return   Rx data
 */
uint8_t PS2_Read(void)
{
    return (uint8_t)(PS2->RXDAT & PS2_RXDAT_DAT_Msk);
}

/**
 *  @brief   This function use to transmit PS2 data.
 *
 *  @param[in]   pu32Buf        The buffer to send the data to PS2 transmission FIFO.
 *  @param[in]   u32ByteCount   The byte number of data.
 *
 *  @return  FALSE: transmit data time-out
 *           TRUE:  transmit data successful
 */
int32_t PS2_Write(uint32_t *pu32Buf, uint32_t u32ByteCount)
{
    uint32_t u32TxFIFO_Depth = 16;
    uint32_t u32delayno, txcnt, remainder;
    uint8_t i=0;

    txcnt = u32ByteCount / u32TxFIFO_Depth;

    remainder = u32ByteCount % u32TxFIFO_Depth;
    if(remainder) txcnt++;

    u32delayno = 0;
    while (!(PS2->STATUS & PS2_STATUS_TXEMPTY_Msk)) {
        u32delayno++;
        if (u32delayno >= 0xF0000000)
            return FALSE; // Time Out
    }

    if(u32ByteCount >= u32TxFIFO_Depth)//Tx fifo is 16 bytes
        PS2_SET_TX_BYTE_CNT(u32TxFIFO_Depth);

    do {
        u32delayno = 0;
        while (!(PS2->STATUS & PS2_STATUS_TXEMPTY_Msk)) {
            u32delayno++;
            if(u32delayno >= 0xF0000000)
                return FALSE; // Time Out
        }

        if((txcnt == 1) && (remainder != 0))
            PS2_SET_TX_BYTE_CNT(u32ByteCount);

        PS2->TXDAT0 = pu32Buf[i];
        PS2->TXDAT1 = pu32Buf[i+1];
        PS2->TXDAT2 = pu32Buf[i+2];
        PS2->TXDAT3 = pu32Buf[i+3];

        i = i + 4;

    } while(--txcnt);

    u32delayno = 0;
    while(!(PS2->STATUS & PS2_STATUS_TXEMPTY_Msk)) {
        u32delayno++;
        if(u32delayno >= 0xF0000000)
            return FALSE; // Time Out
    }

    return TRUE;

}


/*@}*/ /* end of group NUC472_442_PS2_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_PS2_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/



