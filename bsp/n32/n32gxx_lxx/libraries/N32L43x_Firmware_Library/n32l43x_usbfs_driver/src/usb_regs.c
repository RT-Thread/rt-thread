/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file usb_regs.c
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "usb_lib.h"

/**
 * @brief Set the CTRL register value.
 * @param wRegValue new register value.
 */
void USB_SetCtrl(uint16_t wRegValue)
{
    _SetCNTR(wRegValue);
}

/**
 * @brief returns the CTRL register value.
 * @return CTRL register Value.
 */
uint16_t USB_GetCtrl(void)
{
    return (_GetCNTR());
}

/**
 * @brief Set the STS register value.
 * @param wRegValue new register value.
 */
void USB_SetSts(uint16_t wRegValue)
{
    _SetISTR(wRegValue);
}

/**
 * @brief Returns the STS register value.
 * @return STS register Value
 */
uint16_t USB_GetSts(void)
{
    return (_GetISTR());
}

/**
 * @brief Returns the FN register value.
 * @return FN register Value
 */
uint16_t USB_GetFn(void)
{
    return (_GetFNR());
}

/**
 * @brief Set the ADDR register value.
 * @param wRegValue new register value.
 */
void USB_SetAddr(uint16_t wRegValue)
{
    _SetDADDR(wRegValue);
}

/**
 * @brief Returns the ADDR register value.
 * @return ADDR register Value
 */
uint16_t USB_GetAddr(void)
{
    return (_GetDADDR());
}

/**
 * @brief Set the BUFTAB.
 * @param wRegValue New register value.
 */
void USB_SetBuftab(uint16_t wRegValue)
{
    _SetBTABLE(wRegValue);
}

/**
 * @brief Returns the BUFTAB register value.
 * @return BUFTAB address.
 */
uint16_t USB_GetBTABLE(void)
{
    return (_GetBTABLE());
}

/**
 * @brief Set the Endpoint register value.
 * @param bEpNum Endpoint Number.
 * @param wRegValue New register value.
 */
void USB_SetEndPoint(uint8_t bEpNum, uint16_t wRegValue)
{
    _SetENDPOINT(bEpNum, wRegValue);
}

/**
 * @brief Return the Endpoint register value.
 * @param bEpNum Endpoint Number.
 * @return Endpoint register value.
 */
uint16_t USB_GetEndPoint(uint8_t bEpNum)
{
    return (_GetENDPOINT(bEpNum));
}

/**
 * @brief sets the type in the endpoint register.
 * @param bEpNum Endpoint Number.
 * @param wType type definition.
 */
void USB_SetEpType(uint8_t bEpNum, uint16_t wType)
{
    _SetEPType(bEpNum, wType);
}

/**
 * @brief Returns the endpoint type.
 * @param bEpNum Endpoint Number.
 * @return Endpoint Type
 */
uint16_t USB_GetEpType(uint8_t bEpNum)
{
    return (_GetEPType(bEpNum));
}

/**
 * @brief Set the status of Tx endpoint.
 * @param bEpNum Endpoint Number.
 * @param wState new state.
 */
void SetEPTxStatus(uint8_t bEpNum, uint16_t wState)
{
    _SetEPTxStatus(bEpNum, wState);
}

/**
 * @brief Set the status of Rx endpoint.
 * @param bEpNum Endpoint Number.
 * @param wState new state.
 */
void SetEPRxStatus(uint8_t bEpNum, uint16_t wState)
{
    _SetEPRxStatus(bEpNum, wState);
}

/**
 * @brief sets the status for Double Buffer Endpoint to STALL
 * @param bEpNum Endpoint Number.
 * @param bDir Endpoint direction.
 */
void USB_SetDouBleBuferEpStall(uint8_t bEpNum, uint8_t bDir)
{
    uint16_t Endpoint_DTOG_Status;
    Endpoint_DTOG_Status = USB_GetEndPoint(bEpNum);
    if (bDir == EP_DBUF_OUT)
    { /* OUT double buffered endpoint */
        _SetENDPOINT(bEpNum, Endpoint_DTOG_Status & ~EPRX_DATTOG1);
    }
    else if (bDir == EP_DBUF_IN)
    { /* IN double buffered endpoint */
        _SetENDPOINT(bEpNum, Endpoint_DTOG_Status & ~EPTX_DATTOG1);
    }
}

/**
 * @brief Returns the endpoint Tx status.
 * @param bEpNum Endpoint Number.
 * @return Endpoint TX Status
 */
uint16_t USB_GetEpTxSts(uint8_t bEpNum)
{
    return (_GetEPTxStatus(bEpNum));
}

/**
 * @brief Returns the endpoint Rx status.
 * @param bEpNum Endpoint Number.
 * @return Endpoint RX Status
 */
uint16_t USB_GetEpRxSts(uint8_t bEpNum)
{
    return (_GetEPRxStatus(bEpNum));
}

/**
 * @brief Valid the endpoint Tx Status.
 * @param bEpNum Endpoint Number.
 */
void USB_SetEpTxValid(uint8_t bEpNum)
{
    _SetEPTxStatus(bEpNum, EP_TX_VALID);
}

/**
 * @brief Valid the endpoint Rx Status.
 * @param bEpNum Endpoint Number.
 */
void USB_SetEpRxValid(uint8_t bEpNum)
{
    _SetEPRxStatus(bEpNum, EP_RX_VALID);
}

/**
 * @brief Clear the EP_KIND bit.
 * @param bEpNum Endpoint Number.
 */
void USB_SetEpKind(uint8_t bEpNum)
{
    _SetEP_KIND(bEpNum);
}

/**
 * @brief set the  EP_KIND bit.
 * @param bEpNum Endpoint Number.
 */
void USB_ClrEpKind(uint8_t bEpNum)
{
    _ClearEP_KIND(bEpNum);
}
/**
 * @brief Clear the Status Out of the related Endpoint
 * @param bEpNum Endpoint Number.
 */
void USB_ClrStsOut(uint8_t bEpNum)
{
    _ClearEP_KIND(bEpNum);
}
/**
 * @brief Set the Status Out of the related Endpoint
 * @param bEpNum Endpoint Number.
 */
void USB_SetStsOut(uint8_t bEpNum)
{
    _SetEP_KIND(bEpNum);
}
/**
 * @brief Enable the double buffer feature for the endpoint.
 * @param bEpNum Endpoint Number.
 */
void USB_SetEpDoubleBufer(uint8_t bEpNum)
{
    _SetEP_KIND(bEpNum);
}
/**
 * @brief Disable the double buffer feature for the endpoint.
 * @param bEpNum Endpoint Number.
 */
void USB_ClrEpDoubleBufer(uint8_t bEpNum)
{
    _ClearEP_KIND(bEpNum);
}
/**
 * @brief Returns the Stall status of the Tx endpoint.
 * @param bEpNum Endpoint Number.
 * @return Tx Stall status.
 */
uint16_t USB_GetTxStallSts(uint8_t bEpNum)
{
    return (_GetTxStallStatus(bEpNum));
}
/**
 * @brief Returns the Stall status of the Rx endpoint.
 * @param bEpNum Endpoint Number.
 * @return Rx Stall status.
 */
uint16_t USB_GetRxStallSts(uint8_t bEpNum)
{
    return (_GetRxStallStatus(bEpNum));
}
/**
 * @brief Clear the CTR_RX bit.
 * @param bEpNum Endpoint Number.
 */
void USB_ClrEpCtrsRx(uint8_t bEpNum)
{
    _ClearEP_CTR_RX(bEpNum);
}
/**
 * @brief Clear the CTR_TX bit.
 * @param bEpNum Endpoint Number.
 */
void USB_ClrEpCtrsTx(uint8_t bEpNum)
{
    _ClearEP_CTR_TX(bEpNum);
}
/**
 * @brief Toggle the DTOG_RX bit.
 * @param bEpNum Endpoint Number.
 */
void USB_DattogRx(uint8_t bEpNum)
{
    _ToggleDTOG_RX(bEpNum);
}
/**
 * @brief Toggle the DTOG_TX bit.
 * @param bEpNum Endpoint Number.
 */
void USB_DattogTx(uint8_t bEpNum)
{
    _ToggleDTOG_TX(bEpNum);
}
/**
 * @brief Clear the DTOG_RX bit.
 * @param bEpNum Endpoint Number.
 */
void USB_ClrDattogRx(uint8_t bEpNum)
{
    _ClearDTOG_RX(bEpNum);
}
/**
 * @brief Clear the DTOG_TX bit.
 * @param bEpNum Endpoint Number.
 */
void USB_ClrDattogTx(uint8_t bEpNum)
{
    _ClearDTOG_TX(bEpNum);
}
/**
 * @brief Set the endpoint address.
 * @param bEpNum Endpoint Number.
 * @param bAddr New endpoint address.
 */
void USB_SetEpAddress(uint8_t bEpNum, uint8_t bAddr)
{
    _SetEPAddress(bEpNum, bAddr);
}
/**
 * @brief Get the endpoint address.
 * @param bEpNum Endpoint Number.
 * @return Endpoint address.
 */
uint8_t USB_GetEpAddress(uint8_t bEpNum)
{
    return (_GetEPAddress(bEpNum));
}
/**
 * @brief Set the endpoint Tx buffer address.
 * @param bEpNum Endpoint Number.
 * @param wAddr new address.
 */
void USB_SetEpTxAddr(uint8_t bEpNum, uint16_t wAddr)
{
    _SetEPTxAddr(bEpNum, wAddr);
}
/**
 * @brief Set the endpoint Rx buffer address.
 * @param bEpNum Endpoint Number.
 * @param wAddr new address.
 */
void USB_SetEpRxAddr(uint8_t bEpNum, uint16_t wAddr)
{
    _SetEPRxAddr(bEpNum, wAddr);
}
/**
 * @brief Returns the endpoint Tx buffer address.
 * @param bEpNum Endpoint Number.
 * @return Rx buffer address.
 */
uint16_t USB_GetEpTxAddr(uint8_t bEpNum)
{
    return (_GetEPTxAddr(bEpNum));
}
/**
 * @brief Returns the endpoint Rx buffer address.
 * @param bEpNum Endpoint Number.
 * @return Rx buffer address.
 */
uint16_t USB_GetEpRxAddr(uint8_t bEpNum)
{
    return (_GetEPRxAddr(bEpNum));
}
/**
 * @brief Set the Tx count.
 * @param bEpNum Endpoint Number.
 * @param wCount new count value.
 */
void USB_SetEpTxCnt(uint8_t bEpNum, uint16_t wCount)
{
    _SetEPTxCount(bEpNum, wCount);
}
/**
 * @brief Set the Count Rx Register value.
 * @param pdwReg point to the register.
 * @param wCount the new register value.
 */
void USB_SetEpCntRxReg(uint32_t* pdwReg, uint16_t wCount)
{
    _SetEPCountRxReg(dwReg, wCount);
}
/**
 * @brief Set the Rx count.
 * @param bEpNum Endpoint Number.
 * @param wCount the new count value.
 */
void USB_SetEpRxCnt(uint8_t bEpNum, uint16_t wCount)
{
    _SetEPRxCount(bEpNum, wCount);
}
/**
 * @brief Get the Tx count.
 * @param bEpNum Endpoint Number.
 * @return Tx count value.
 */
uint16_t USB_GetEpTxCnt(uint8_t bEpNum)
{
    return (_GetEPTxCount(bEpNum));
}
/**
 * @brief Get the Rx count.
 * @param bEpNum Endpoint Number.
 * @return Rx count value.
 */
uint16_t USB_GetEpRxCnt(uint8_t bEpNum)
{
    return (_GetEPRxCount(bEpNum));
}
/**
 * @brief Set the addresses of the buffer 0 and 1.
 * @param bEpNum Endpoint Number.
 * @param wBuf0Addr new address of buffer 0.
 * @param wBuf1Addr new address of buffer 1.
 */
void USB_SetEpDblBuferAddr(uint8_t bEpNum, uint16_t wBuf0Addr, uint16_t wBuf1Addr)
{
    _SetEPDblBuffAddr(bEpNum, wBuf0Addr, wBuf1Addr);
}
/**
 * @brief Set the Buffer 1 address.
 * @param bEpNum Endpoint Number
 * @param wBuf0Addr new address.
 */
void USB_SetEpDblBuf0Addr(uint8_t bEpNum, uint16_t wBuf0Addr)
{
    _SetEPDblBuf0Addr(bEpNum, wBuf0Addr);
}
/**
 * @brief Set the Buffer 1 address.
 * @param bEpNum Endpoint Number
 * @param wBuf1Addr new address.
 */
void USB_SetEpDblBuf1Addr(uint8_t bEpNum, uint16_t wBuf1Addr)
{
    _SetEPDblBuf1Addr(bEpNum, wBuf1Addr);
}
/**
 * @brief Returns the address of the Buffer 0.
 * @param bEpNum Endpoint Number.
 */
uint16_t USB_GetEpDblBuf0Addr(uint8_t bEpNum)
{
    return (_GetEPDblBuf0Addr(bEpNum));
}
/**
 * @brief Returns the address of the Buffer 1.
 * @param bEpNum Endpoint Number.
 * @return Address of the Buffer 1.
 */
uint16_t USB_GetEpDblBuf1Addr(uint8_t bEpNum)
{
    return (_GetEPDblBuf1Addr(bEpNum));
}
/**
 * @brief Set the number of bytes for a double Buffer endpoint.
 * @param bEpNum
 * @param bDir
 * @param wCount
 */
void USB_SetEpDblBuferCnt(uint8_t bEpNum, uint8_t bDir, uint16_t wCount)
{
    _SetEPDblBuffCount(bEpNum, bDir, wCount);
}
/**
 * @brief Set the number of bytes in the buffer 0 of a double Buffer endpoint.
 * @param bEpNum
 * @param bDir
 * @param wCount
 */
void USB_SetEpDblBuf0Cnt(uint8_t bEpNum, uint8_t bDir, uint16_t wCount)
{
    _SetEPDblBuf0Count(bEpNum, bDir, wCount);
}
/**
 * @brief Set the number of bytes in the buffer 0 of a double Buffer endpoint.
 * @param bEpNum
 * @param bDir
 * @param wCount
 */
void USB_SetEpDblBuf1Cnt(uint8_t bEpNum, uint8_t bDir, uint16_t wCount)
{
    _SetEPDblBuf1Count(bEpNum, bDir, wCount);
}
/**
 * @brief Returns the number of byte received in the buffer 0 of a double Buffer endpoint.
 * @param bEpNum Endpoint Number.
 * @return Endpoint Buffer 0 count
 */
uint16_t USB_GetEpDblBuf0Cnt(uint8_t bEpNum)
{
    return (_GetEPDblBuf0Count(bEpNum));
}
/**
 * @brief Returns the number of data received in the buffer 1 of a double Buffer endpoint.
 * @param bEpNum Endpoint Number.
 * @return Endpoint Buffer 1 count.
 */
uint16_t USB_GetEpDblBuf1Cnt(uint8_t bEpNum)
{
    return (_GetEPDblBuf1Count(bEpNum));
}
/**
 * @brief gets direction of the double buffered endpoint
 * @param bEpNum Endpoint Number.
 * @return EP_DBUF_OUT, EP_DBUF_IN, EP_DBUF_ERR if the endpoint counter not yet programmed.
 */
EP_DBUF_DIR GetEPDblBufDir(uint8_t bEpNum)
{
    if ((uint16_t)(*_pEPRxCount(bEpNum) & 0xFC00) != 0)
        return (EP_DBUF_OUT);
    else if (((uint16_t)(*_pEPTxCount(bEpNum)) & 0x03FF) != 0)
        return (EP_DBUF_IN);
    else
        return (EP_DBUF_ERR);
}
/**
 * @brief free buffer used from the application realizing it to the line toggles
 * bit SW_BUF in the double buffered endpoint register
 * @param bEpNum
 * @param bDir
 */
void USB_FreeUserBuf(uint8_t bEpNum, uint8_t bDir)
{
    if (bDir == EP_DBUF_OUT)
    { /* OUT double buffered endpoint */
        _ToggleDTOG_TX(bEpNum);
    }
    else if (bDir == EP_DBUF_IN)
    { /* IN double buffered endpoint */
        _ToggleDTOG_RX(bEpNum);
    }
}

/**
 * @brief merge two byte in a word.
 * @param bh byte high
 * @param bl bytes low.
 * @return resulted word.
 */
uint16_t USB_ToWord(uint8_t bh, uint8_t bl)
{
    uint16_t wRet;
    wRet = (uint16_t)bl | ((uint16_t)bh << 8);
    return (wRet);
}
/**
 * @brief Swap two byte in a word.
 * @param wSwW word to Swap.
 * @return resulted word.
 */
uint16_t USB_ByteSwap(uint16_t wSwW)
{
    uint8_t bTemp;
    uint16_t wRet;
    bTemp = (uint8_t)(wSwW & 0xff);
    wRet  = (wSwW >> 8) | ((uint16_t)bTemp << 8);
    return (wRet);
}
