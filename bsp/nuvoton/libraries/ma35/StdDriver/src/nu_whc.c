/**************************************************************************//**
 * @file     whc.c
 * @brief    WHC driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup WHC_Driver WHC Driver
  @{
*/

/** @addtogroup WHC_EXPORTED_FUNCTIONS WHC Exported Functions
  @{
*/

/**
  * @brief      Send message through a wormhole channel
  * @param[in]  whc           The pointer of the specified WHC module.
  * @param[in]  u32Ch         WHC channel, valid channel numbers are 0~3
  * @param[in]  pu32TxBuf     The buffer holds the data to send
  * @retval     0             Success
  * @retval     -1            Failed. Channel is busy, previous message hasn't been read yet.
  */
int WHC_Send(WHC_T *whc, uint32_t u32Ch, uint32_t *pu32TxBuf)
{
    int i;

    if (whc->TXSTS & (1ul << u32Ch))
    {
        for (i = 0; i < WHC_BUFFER_LEN; i++)
            whc->TMDAT[u32Ch][i] = *pu32TxBuf++;
        whc->TXCTL = (1ul << u32Ch);
    }
    else
    {
        return -1;

    }
    return 0;
}

/**
  * @brief      Receive message from a wormhole channel
  * @param[in]  whc           The pointer of the specified WHC module.
  * @param[in]  u32Ch         WHC channel, valid channel numbers are 0~3
  * @param[out] pu32RxBuf     The buffer to hold the receive data
  * @retval     0             Success
  * @retval     -1            Failed. Channel is empty and no message is available for read.
  * @Note       This function send an ACK signal after receive complete
  */
int WHC_Recv(WHC_T *whc, uint32_t u32Ch, uint32_t *pu32RxBuf)
{
    int i;

    if (whc->RXSTS & (1ul << u32Ch))
    {
        for (i = 0; i < WHC_BUFFER_LEN; i++)
            *pu32RxBuf++ = whc->RMDAT[u32Ch][i];
        whc->RXCTL = (1ul << u32Ch);
    }
    else
    {
        return -1;

    }
    return 0;
}

/**
  * @brief      Get counter part status
  * @param[in]  whc           The pointer of the specified WHC module.
  * @param[in]  u32Core       Core number, valid channel numbers are 0~1
  * @retval     \ref WHC_RUN_MODE
  * @retval     \ref WHC_POFF_MODE
  * @retval     \ref WHC_PD_MODE
  */
int WHC_GetCPSts(WHC_T *whc, uint32_t u32Core)
{
    if (u32Core == 0)
    {
        return (whc->CPSTS & WHC_CPSTS_OPMODE0_Msk) >> WHC_CPSTS_OPMODE0_Pos;
    }
    else
    {
        return (whc->CPSTS & WHC_CPSTS_OPMODE1_Msk) >> WHC_CPSTS_OPMODE1_Pos;
    }
}

/*@}*/ /* end of group WHC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group WHC_Driver */

/*@}*/ /* end of group Standard_Driver */

