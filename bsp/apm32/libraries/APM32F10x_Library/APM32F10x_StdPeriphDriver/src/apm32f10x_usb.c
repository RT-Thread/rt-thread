/*!
 * @file        apm32f10x_usb.c
 *
 * @brief       This file contains all the functions for the USBD peripheral
 *
 * @version     V1.0.1
 *
 * @date        2021-03-23
 *
 */

#include "apm32f10x_usb.h"

/*!
 * @brief       Set Endpoint type
 *
 * @param       ep: Endpoint number
 *
 * @param       type: Endpoint type
 *
 * @retval      None
 */
void USBD_SetEPType(USBD_EP_T ep, USBD_EP_TYPE_T type)
{
    __IOM uint32_t reg;

    reg = USBD->EP[ep].EP;

    reg &= (uint32_t)(USBD_EP_MASK_DEFAULT);
    reg &= ~USBD_EP_BIT_TYPE;
    reg |= type << 9;

    USBD->EP[ep].EP = reg;
}

/*!
 * @brief       Set EP kind
 *
 * @param       ep: Endpoint number
 *
 * @retval      None
 */
void USBD_SetEPKind(USBD_EP_T ep)
{
    __IOM uint32_t reg;

    reg = USBD->EP[ep].EP;

    reg &= (uint32_t)(USBD_EP_MASK_DEFAULT);
    reg |= USBD_EP_BIT_KIND;

    USBD->EP[ep].EP = reg;
}

/*!
 * @brief       Reset EP kind
 *
 * @param       ep: Endpoint number
 *
 * @retval      None
 */
void USBD_ResetEPKind(USBD_EP_T ep)
{
    __IOM uint32_t reg;

    reg = USBD->EP[ep].EP;

    reg &= (uint32_t)(USBD_EP_MASK_DEFAULT);
    reg &= ~USBD_EP_BIT_KIND;

    USBD->EP[ep].EP = reg;
}


/*!
 * @brief       Reset EP CTFR bit
 *
 * @param       ep: Endpoint number
 *
 * @retval      None
 */
void USBD_ResetEPRxFlag(USBD_EP_T ep)
{
    __IOM uint32_t reg;

    reg = USBD->EP[ep].EP;

    reg &= (uint32_t)(USBD_EP_MASK_DEFAULT);
    reg &= ~USBD_EP_BIT_CTFR;

    USBD->EP[ep].EP = reg;
}

/*!
 * @brief       Reset EP CTFT bit
 *
 * @param       ep: Endpoint number
 *
 * @retval      None
 */
void USBD_ResetEPTxFlag(USBD_EP_T ep)
{
    __IOM uint32_t reg;

    reg = USBD->EP[ep].EP;

    reg &= (uint32_t)(USBD_EP_MASK_DEFAULT);
    reg &= ~USBD_EP_BIT_CTFT;

    USBD->EP[ep].EP = reg;
}

/*!
 * @brief       Toggle Tx DTOG
 *
 * @param       ep: Endpoint number
 *
 * @retval      None
 */
void USBD_ToggleTx(USBD_EP_T ep)
{
    __IOM uint32_t reg;

    reg = USBD->EP[ep].EP;

    reg &= (uint32_t)(USBD_EP_MASK_DEFAULT);
    reg |= USBD_EP_BIT_TXDTOG;

    USBD->EP[ep].EP = reg;
}

/*!
 * @brief       Toggle Rx DTOG
 *
 * @param       ep: Endpoint number
 *
 * @retval      None
 */
void USBD_ToggleRx(USBD_EP_T ep)
{
    __IOM uint32_t reg;

    reg = USBD->EP[ep].EP;

    reg &= (uint32_t)(USBD_EP_MASK_DEFAULT);
    reg |= USBD_EP_BIT_RXDTOG;

    USBD->EP[ep].EP = reg;
}

/*!
 * @brief       Reset Toggle Tx DTOG
 *
 * @param       ep: Endpoint number
 *
 * @retval      None
 */
void USBD_ResetTxToggle(USBD_EP_T ep)
{
    if(USBD->EP[ep].EP_B.TXDTOG)
    {
        USBD_ToggleTx(ep);
    }
}

/*!
 * @brief       Reset Toggle Rx DTOG
 *
 * @param       ep: Endpoint number
 *
 * @retval      None
 */
void USBD_ResetRxToggle(USBD_EP_T ep)
{
    if(USBD->EP[ep].EP_B.RXDTOG)
    {
        USBD_ToggleRx(ep);
    }
}

/*!
 * @brief       Set EP address
 *
 * @param       ep: Endpoint number
 *
 * @param       addr: Address
 *
 * @retval      None
 */
void USBD_SetEpAddr(USBD_EP_T ep, uint8_t addr)
{
    __IOM uint32_t reg;

    reg = USBD->EP[ep].EP;

    reg &= (uint32_t)(USBD_EP_MASK_DEFAULT);
    reg &= ~USBD_EP_BIT_ADDR;
    reg |= addr;

    USBD->EP[ep].EP = reg;
}

/*!
 * @brief       Set EP Tx status
 *
 * @param       ep: Endpoint number
 *
 * @param       status: status
 *
 * @retval      None
 */
void USBD_SetEPTxStatus(USBD_EP_T ep, USBD_EP_STATUS_T status)
{
    __IOM uint32_t reg;

    status <<= 4;

    reg = USBD->EP[ep].EP;

    reg &= (uint32_t)(USBD_EP_MASK_DEFAULT | USBD_EP_BIT_TXSTS);
    reg ^= (status & USBD_EP_BIT_TXSTS);

    USBD->EP[ep].EP = reg;
}

/*!
 * @brief       Set EP Rx status
 *
 * @param       ep: Endpoint number
 *
 * @param       status: status
 *
 * @retval      None
 */
void USBD_SetEPRxStatus(USBD_EP_T ep, USBD_EP_STATUS_T status)
{
    __IOM uint32_t reg;
    uint32_t tmp;

    tmp = status << 12;

    reg = USBD->EP[ep].EP;

    reg &= (uint32_t)(USBD_EP_MASK_DEFAULT | USBD_EP_BIT_RXSTS);
    reg ^= (tmp & USBD_EP_BIT_RXSTS);

    USBD->EP[ep].EP = reg;
}


/*!
 * @brief       Set EP Rx and Txstatus
 *
 * @param       ep: Endpoint number
 *
 * @param       status: status
 *
 * @retval      None
 */
void USBD_SetEPRxTxStatus(USBD_EP_T ep, USBD_EP_STATUS_T txStatus, USBD_EP_STATUS_T rxStatus)
{
    __IOM uint32_t reg;
    uint32_t tmp;

    reg = USBD->EP[ep].EP;

    reg &= (uint32_t)(USBD_EP_MASK_DEFAULT | USBD_EP_BIT_RXSTS | USBD_EP_BIT_TXSTS);

    tmp = rxStatus << 12;
    reg ^= (tmp & USBD_EP_BIT_RXSTS);

    tmp = txStatus << 4;
    reg ^= (tmp & USBD_EP_BIT_TXSTS);

    USBD->EP[ep].EP = reg;
}

/*!
 * @brief       Set EP Rx Count
 *
 * @param       ep: Endpoint number
 *
 * @param       cnt: Rx count
 *
 * @retval      None
 */
void USBD_SetEPRxCnt(USBD_EP_T ep, uint32_t cnt)
{
    __IOM uint32_t *p;
    __IOM uint32_t block = 0;

    p = USBD_ReadEPRxCntPointer(ep);

    if(cnt > 62)
    {
        block = cnt >> 5;

        if(!(cnt & 0x1f))
        {
            block -= 1;
        }

        *p = (block << 10) | 0x8000;
    }
    else
    {
        block = cnt >> 1;

        if(cnt & 0x01)
        {
            block += 1;
        }

        *p = (block << 10);
    }
}

/*!
 * @brief       Write a buffer of data to a selected endpoint
 *
 * @param       ep:   Endpoint number
 *
 * @retval      wBuf: The pointer to the buffer of data to be written to the endpoint
 *
 * @param       wLen: Number of data to be written (in bytes)
 *
 * @retval      None
 */
void USBD_WriteDataToEP(USBD_EP_T ep, uint8_t *wBuf, uint32_t wLen)
{
    uint32_t i;
    uint32_t *addrEP;
    uint32_t tmp;

    wLen = (wLen + 1) >> 1;

    addrEP = (uint32_t *)USBD_ReadEPTxAddr(ep);
    addrEP = (uint32_t *)(((uint32_t)addrEP << 1) + USBD_PMA_ADDR);

    for(i = 0; i < wLen; i++)
    {
        tmp = *wBuf++;
        tmp = ((*wBuf++) << 8) | tmp;

        *addrEP++ = tmp;
    }
}

/*!
 * @brief       Read a buffer of data to a selected endpoint
 *
 * @param       ep:   Endpoint number
 *
 * @retval      wBuf: The pointer to the buffer of data to be read to the endpoint
 *
 * @param       wLen: Number of data to be read (in bytes)
 *
 * @retval      None
 */
void USBD_ReadDataFromEP(USBD_EP_T ep, uint8_t *rBuf, uint32_t rLen)
{
    uint32_t i;
    uint32_t *addrEP;
    uint32_t tmp;

    rLen = (rLen + 1) >> 1;

    addrEP = (uint32_t *)USBD_ReadEPRxAddr(ep);
    addrEP = (uint32_t *)(((uint32_t)addrEP << 1) + USBD_PMA_ADDR);

    for(i = 0; i < rLen; i++)
    {
        tmp = *addrEP++;
        *rBuf++ = tmp & 0XFF;
        *rBuf++ = (tmp >> 8) & 0xff;
    }
}

