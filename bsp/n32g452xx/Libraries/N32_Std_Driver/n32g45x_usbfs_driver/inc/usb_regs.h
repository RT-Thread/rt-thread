/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
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
 * @file usb_regs.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __USB_REGS_H__
#define __USB_REGS_H__

#include "n32g45x.h"

/**
 * @addtogroup N32G45X_USB_Driver
 * @{
 */

typedef enum _EP_DBUF_DIR
{
    /* double buffered endpoint direction */
    EP_DBUF_ERR,
    EP_DBUF_OUT,
    EP_DBUF_IN
} EP_DBUF_DIR;

/* endpoint buffer number */
enum EP_BUF_NUM
{
    EP_NOBUF,
    EP_BUF0,
    EP_BUF1
};

#define RegBase (0x40005C00L) /* USB_IP Peripheral Registers base address */
#define PMAAddr (0x40006000L) /* USB_IP Packet Memory Area base address   */

/******************************************************************************/
/*                         Special registers                                  */
/******************************************************************************/
/* Pull up controller register */
#define DP_CTRL ((__IO unsigned*)(0x40001820))

#define _EnPortPullup() (*DP_CTRL = (*DP_CTRL) | 0x10000000);
#define _DisPortPullup() (*DP_CTRL = (*DP_CTRL) & 0xEFFFFFFF);

/******************************************************************************/
/*                         General registers                                  */
/******************************************************************************/

/* Control register */
#define USB_CTRL ((__IO unsigned*)(RegBase + 0x40))
/* Interrupt status register */
#define USB_STS ((__IO unsigned*)(RegBase + 0x44))
/* Frame number register */
#define USB_FN ((__IO unsigned*)(RegBase + 0x48))
/* Device address register */
#define USB_ADDR ((__IO unsigned*)(RegBase + 0x4C))
/* Buffer Table address register */
#define USB_BUFTAB ((__IO unsigned*)(RegBase + 0x50))
/******************************************************************************/
/*                         Endpoint registers                                 */
/******************************************************************************/
#define EP0REG ((__IO unsigned*)(RegBase)) /* endpoint 0 register address */

/* Endpoint Addresses (w/direction) */
#define EP0_OUT ((uint8_t)0x00)
#define EP0_IN  ((uint8_t)0x80)
#define EP1_OUT ((uint8_t)0x01)
#define EP1_IN  ((uint8_t)0x81)
#define EP2_OUT ((uint8_t)0x02)
#define EP2_IN  ((uint8_t)0x82)
#define EP3_OUT ((uint8_t)0x03)
#define EP3_IN  ((uint8_t)0x83)
#define EP4_OUT ((uint8_t)0x04)
#define EP4_IN  ((uint8_t)0x84)
#define EP5_OUT ((uint8_t)0x05)
#define EP5_IN  ((uint8_t)0x85)
#define EP6_OUT ((uint8_t)0x06)
#define EP6_IN  ((uint8_t)0x86)
#define EP7_OUT ((uint8_t)0x07)
#define EP7_IN  ((uint8_t)0x87)

/* endpoints enumeration */
#define ENDP0 ((uint8_t)0)
#define ENDP1 ((uint8_t)1)
#define ENDP2 ((uint8_t)2)
#define ENDP3 ((uint8_t)3)
#define ENDP4 ((uint8_t)4)
#define ENDP5 ((uint8_t)5)
#define ENDP6 ((uint8_t)6)
#define ENDP7 ((uint8_t)7)

/******************************************************************************/
/*                       USB_STS interrupt events                                */
/******************************************************************************/
#define STS_CTRS  (0x8000) /* Correct TRansfer (clear-only bit) */
#define STS_DOVR  (0x4000) /* DMA OVeR/underrun (clear-only bit) */
#define STS_ERROR (0x2000) /* ERRor (clear-only bit) */
#define STS_WKUP  (0x1000) /* WaKe UP (clear-only bit) */
#define STS_SUSPD (0x0800) /* SUSPend (clear-only bit) */
#define STS_RST   (0x0400) /* RESET (clear-only bit) */
#define STS_SOF   (0x0200) /* Start Of Frame (clear-only bit) */
#define STS_ESOF  (0x0100) /* Expected Start Of Frame (clear-only bit) */

#define STS_DIR   (0x0010) /* DIRection of transaction (read-only bit)  */
#define STS_EP_ID (0x000F) /* EndPoint IDentifier (read-only bit)  */

#define CLR_CTRS  (~STS_CTRS)  /* clear Correct TRansfer bit */
#define CLR_DOVR  (~STS_DOVR)  /* clear DMA OVeR/underrun bit*/
#define CLR_ERROR (~STS_ERROR) /* clear ERRor bit */
#define CLR_WKUP  (~STS_WKUP)  /* clear WaKe UP bit     */
#define CLR_SUSPD (~STS_SUSPD) /* clear SUSPend bit     */
#define CLR_RST   (~STS_RST)   /* clear RESET bit      */
#define CLR_SOF   (~STS_SOF)   /* clear Start Of Frame bit   */
#define CLR_ESOF  (~STS_ESOF)  /* clear Expected Start Of Frame bit */

/******************************************************************************/
/*             USB_CTRL control register bits definitions                         */
/******************************************************************************/
#define CTRL_CTRSM  (0x8000) /* Correct TRansfer Mask */
#define CTRL_DOVRM  (0x4000) /* DMA OVeR/underrun Mask */
#define CTRL_ERRORM (0x2000) /* ERRor Mask */
#define CTRL_WKUPM  (0x1000) /* WaKe UP Mask */
#define CTRL_SUSPDM (0x0800) /* SUSPend Mask */
#define CTRL_RSTM   (0x0400) /* RESET Mask   */
#define CTRL_SOFM   (0x0200) /* Start Of Frame Mask */
#define CTRL_ESOFM  (0x0100) /* Expected Start Of Frame Mask */

#define CTRL_RESUM   (0x0010) /* RESUME request */
#define CTRL_FSUSPD  (0x0008) /* Force SUSPend */
#define CTRL_LP_MODE (0x0004) /* Low-power MODE */
#define CTRL_PD      (0x0002) /* Power DoWN */
#define CTRL_FRST    (0x0001) /* Force USB RESet */

/******************************************************************************/
/*                USB_FN Frame Number Register bit definitions                   */
/******************************************************************************/
#define FN_RXDP (0x8000) /* status of D+ data line */
#define FN_RXDM (0x4000) /* status of D- data line */
#define FN_LCK  (0x2000) /* LoCKed */
#define FN_LSOF (0x1800) /* Lost SOF */
#define FN_FNUM (0x07FF) /* Frame Number */
/******************************************************************************/
/*               USB_ADDR Device ADDRess bit definitions                         */
/******************************************************************************/
#define ADDR_EFUC (0x80)
#define ADDR_ADDR (0x7F)
/******************************************************************************/
/*                            Endpoint register                               */
/******************************************************************************/
/* bit positions */
#define EP_CTRS_RX   (0x8000) /* EndPoint Correct TRansfer RX */
#define EP_DATTOG_RX (0x4000) /* EndPoint Data TOGGLE RX */
#define EPRX_STS     (0x3000) /* EndPoint RX STATus bit field */
#define EP_SETUP     (0x0800) /* EndPoint SETUP */
#define EP_T_FIELD   (0x0600) /* EndPoint TYPE */
#define EP_KIND      (0x0100) /* EndPoint KIND */
#define EP_CTRS_TX   (0x0080) /* EndPoint Correct TRansfer TX */
#define EP_DATTOG_TX (0x0040) /* EndPoint Data TOGGLE TX */
#define EPTX_STS     (0x0030) /* EndPoint TX STATus bit field */
#define EPADDR_FIELD (0x000F) /* EndPoint ADDRess FIELD */

/* EndPoint REGister INTEN (no toggle fields) */
#define EPREG_MASK (EP_CTRS_RX | EP_SETUP | EP_T_FIELD | EP_KIND | EP_CTRS_TX | EPADDR_FIELD)

/* EP_TYPE[1:0] EndPoint TYPE */
#define EP_TYPE_MASK   (0x0600) /* EndPoint TYPE Mask */
#define EP_BULK        (0x0000) /* EndPoint BULK */
#define EP_CONTROL     (0x0200) /* EndPoint CONTROL */
#define EP_ISOCHRONOUS (0x0400) /* EndPoint ISOCHRONOUS */
#define EP_INTERRUPT   (0x0600) /* EndPoint INTERRUPT */
#define EP_T_MASK      (~EP_T_FIELD & EPREG_MASK)

/* EP_KIND EndPoint KIND */
#define EPKIND_MASK (~EP_KIND & EPREG_MASK)

/* STAT_TX[1:0] STATus for TX transfer */
#define EP_TX_DIS       (0x0000) /* EndPoint TX DISabled */
#define EP_TX_STALL     (0x0010) /* EndPoint TX STALLed */
#define EP_TX_NAK       (0x0020) /* EndPoint TX NAKed */
#define EP_TX_VALID     (0x0030) /* EndPoint TX VALID */
#define EPTX_DATTOG1    (0x0010) /* EndPoint TX Data TOGgle bit1 */
#define EPTX_DATTOG2    (0x0020) /* EndPoint TX Data TOGgle bit2 */
#define EPTX_DATTOGMASK (EPTX_STS | EPREG_MASK)

/* STAT_RX[1:0] STATus for RX transfer */
#define EP_RX_DIS       (0x0000) /* EndPoint RX DISabled */
#define EP_RX_STALL     (0x1000) /* EndPoint RX STALLed */
#define EP_RX_NAK       (0x2000) /* EndPoint RX NAKed */
#define EP_RX_VALID     (0x3000) /* EndPoint RX VALID */
#define EPRX_DATTOG1    (0x1000) /* EndPoint RX Data TOGgle bit1 */
#define EPRX_DATTOG2    (0x2000) /* EndPoint RX Data TOGgle bit1 */
#define EPRX_DATTOGMASK (EPRX_STS | EPREG_MASK)

/* USB_SetCtrl */
#define _SetCNTR(wRegValue) (*USB_CTRL = (uint16_t)wRegValue)

/* USB_SetSts */
#define _SetISTR(wRegValue) (*USB_STS = (uint16_t)wRegValue)

/* USB_SetAddr */
#define _SetDADDR(wRegValue) (*USB_ADDR = (uint16_t)wRegValue)

/* USB_SetBuftab */
#define _SetBTABLE(wRegValue) (*USB_BUFTAB = (uint16_t)(wRegValue & 0xFFF8))

/* USB_GetCtrl */
#define _GetCNTR() ((uint16_t)*USB_CTRL)

/* USB_GetSts */
#define _GetISTR() ((uint16_t)*USB_STS)

/* USB_GetFn */
#define _GetFNR() ((uint16_t)*USB_FN)

/* USB_GetAddr */
#define _GetDADDR() ((uint16_t)*USB_ADDR)

/* USB_GetBTABLE */
#define _GetBTABLE() ((uint16_t)*USB_BUFTAB)

/* USB_SetEndPoint */
#define _SetENDPOINT(bEpNum, wRegValue) (*(EP0REG + bEpNum) = (uint16_t)wRegValue)

/* USB_GetEndPoint */
#define _GetENDPOINT(bEpNum) ((uint16_t)(*(EP0REG + bEpNum)))

/*******************************************************************************
 * Macro Name     : USB_SetEpType
 * Description    : sets the type in the endpoint register(bits EP_TYPE[1:0])
 * Input          : bEpNum: Endpoint Number.
 *                  wType
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _SetEPType(bEpNum, wType) (_SetENDPOINT(bEpNum, ((_GetENDPOINT(bEpNum) & EP_T_MASK) | wType)))

/*******************************************************************************
 * Macro Name     : USB_GetEpType
 * Description    : gets the type in the endpoint register(bits EP_TYPE[1:0])
 * Input          : bEpNum: Endpoint Number.
 * Output         : None.
 * Return         : Endpoint Type
 *******************************************************************************/
#define _GetEPType(bEpNum) (_GetENDPOINT(bEpNum) & EP_T_FIELD)

/*******************************************************************************
 * Macro Name     : SetEPTxStatus
 * Description    : sets the status for tx transfer (bits STAT_TX[1:0]).
 * Input          : bEpNum: Endpoint Number.
 *                  wState: new state
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _SetEPTxStatus(bEpNum, wState)                                                                                 \
    {                                                                                                                  \
        register uint16_t _wRegVal;                                                                                    \
        _wRegVal = _GetENDPOINT(bEpNum) & EPTX_DATTOGMASK;                                                             \
        /* toggle first bit ? */                                                                                       \
        if ((EPTX_DATTOG1 & wState) != 0)                                                                              \
            _wRegVal ^= EPTX_DATTOG1;                                                                                  \
        /* toggle second bit ?  */                                                                                     \
        if ((EPTX_DATTOG2 & wState) != 0)                                                                              \
            _wRegVal ^= EPTX_DATTOG2;                                                                                  \
        _SetENDPOINT(bEpNum, (_wRegVal | EP_CTRS_RX | EP_CTRS_TX));                                                    \
    } /* _SetEPTxStatus */

/*******************************************************************************
 * Macro Name     : SetEPRxStatus
 * Description    : sets the status for rx transfer (bits STAT_TX[1:0])
 * Input          : bEpNum: Endpoint Number.
 *                  wState: new state.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _SetEPRxStatus(bEpNum, wState)                                                                                 \
    {                                                                                                                  \
        register uint16_t _wRegVal;                                                                                    \
                                                                                                                       \
        _wRegVal = _GetENDPOINT(bEpNum) & EPRX_DATTOGMASK;                                                             \
        /* toggle first bit ? */                                                                                       \
        if ((EPRX_DATTOG1 & wState) != 0)                                                                              \
            _wRegVal ^= EPRX_DATTOG1;                                                                                  \
        /* toggle second bit ? */                                                                                      \
        if ((EPRX_DATTOG2 & wState) != 0)                                                                              \
            _wRegVal ^= EPRX_DATTOG2;                                                                                  \
        _SetENDPOINT(bEpNum, (_wRegVal | EP_CTRS_RX | EP_CTRS_TX));                                                    \
    } /* _SetEPRxStatus */

/*******************************************************************************
 * Macro Name     : SetEPRxTxStatus
 * Description    : sets the status for rx & tx (bits STAT_TX[1:0] & STAT_RX[1:0])
 * Input          : bEpNum: Endpoint Number.
 *                  wStaterx: new state.
 *                  wStatetx: new state.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _SetEPRxTxStatus(bEpNum, wStaterx, wStatetx)                                                                   \
    {                                                                                                                  \
        register uint32_t _wRegVal;                                                                                    \
                                                                                                                       \
        _wRegVal = _GetENDPOINT(bEpNum) & (EPRX_DATTOGMASK | EPTX_STS);                                                \
        /* toggle first bit ? */                                                                                       \
        if ((EPRX_DATTOG1 & wStaterx) != 0)                                                                            \
            _wRegVal ^= EPRX_DATTOG1;                                                                                  \
        /* toggle second bit ? */                                                                                      \
        if ((EPRX_DATTOG2 & wStaterx) != 0)                                                                            \
            _wRegVal ^= EPRX_DATTOG2;                                                                                  \
        /* toggle first bit ? */                                                                                       \
        if ((EPTX_DATTOG1 & wStatetx) != 0)                                                                            \
            _wRegVal ^= EPTX_DATTOG1;                                                                                  \
        /* toggle second bit ?  */                                                                                     \
        if ((EPTX_DATTOG2 & wStatetx) != 0)                                                                            \
            _wRegVal ^= EPTX_DATTOG2;                                                                                  \
        _SetENDPOINT(bEpNum, _wRegVal | EP_CTRS_RX | EP_CTRS_TX);                                                      \
    } /* _SetEPRxTxStatus */
/*******************************************************************************
 * Macro Name     : USB_GetEpTxSts / USB_GetEpRxSts
 * Description    : gets the status for tx/rx transfer (bits STAT_TX[1:0]
 *                  /STAT_RX[1:0])
 * Input          : bEpNum: Endpoint Number.
 * Output         : None.
 * Return         : status .
 *******************************************************************************/
#define _GetEPTxStatus(bEpNum) ((uint16_t)_GetENDPOINT(bEpNum) & EPTX_STS)

#define _GetEPRxStatus(bEpNum) ((uint16_t)_GetENDPOINT(bEpNum) & EPRX_STS)

/*******************************************************************************
 * Macro Name     : USB_SetEpTxValid / USB_SetEpRxValid
 * Description    : sets directly the VALID tx/rx-status into the enpoint register
 * Input          : bEpNum: Endpoint Number.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _SetEPTxValid(bEpNum) (_SetEPTxStatus(bEpNum, EP_TX_VALID))

#define _SetEPRxValid(bEpNum) (_SetEPRxStatus(bEpNum, EP_RX_VALID))

/*******************************************************************************
 * Macro Name     : USB_GetTxStallSts / USB_GetRxStallSts.
 * Description    : checks stall condition in an endpoint.
 * Input          : bEpNum: Endpoint Number.
 * Output         : None.
 * Return         : TRUE = endpoint in stall condition.
 *******************************************************************************/
#define _GetTxStallStatus(bEpNum) (_GetEPTxStatus(bEpNum) == EP_TX_STALL)
#define _GetRxStallStatus(bEpNum) (_GetEPRxStatus(bEpNum) == EP_RX_STALL)

/*******************************************************************************
 * Macro Name     : USB_SetEpKind / USB_ClrEpKind.
 * Description    : set & clear EP_KIND bit.
 * Input          : bEpNum: Endpoint Number.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _SetEP_KIND(bEpNum)                                                                                            \
    (_SetENDPOINT(bEpNum, (EP_CTRS_RX | EP_CTRS_TX | ((_GetENDPOINT(bEpNum) | EP_KIND) & EPREG_MASK))))
#define _ClearEP_KIND(bEpNum) (_SetENDPOINT(bEpNum, (EP_CTRS_RX | EP_CTRS_TX | (_GetENDPOINT(bEpNum) & EPKIND_MASK))))

/*******************************************************************************
 * Macro Name     : USB_SetStsOut / USB_ClrStsOut.
 * Description    : Sets/clears directly STATUS_OUT bit in the endpoint register.
 * Input          : bEpNum: Endpoint Number.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _Set_Status_Out(bEpNum)   _SetEP_KIND(bEpNum)
#define _Clear_Status_Out(bEpNum) _ClearEP_KIND(bEpNum)

/*******************************************************************************
 * Macro Name     : USB_SetEpDoubleBufer / USB_ClrEpDoubleBufer.
 * Description    : Sets/clears directly EP_KIND bit in the endpoint register.
 * Input          : bEpNum: Endpoint Number.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _SetEPDoubleBuff(bEpNum)   _SetEP_KIND(bEpNum)
#define _ClearEPDoubleBuff(bEpNum) _ClearEP_KIND(bEpNum)

/*******************************************************************************
 * Macro Name     : USB_ClrEpCtrsRx / USB_ClrEpCtrsTx.
 * Description    : Clears bit CTR_RX / CTR_TX in the endpoint register.
 * Input          : bEpNum: Endpoint Number.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _ClearEP_CTR_RX(bEpNum) (_SetENDPOINT(bEpNum, _GetENDPOINT(bEpNum) & 0x7FFF & EPREG_MASK))
#define _ClearEP_CTR_TX(bEpNum) (_SetENDPOINT(bEpNum, _GetENDPOINT(bEpNum) & 0xFF7F & EPREG_MASK))

/*******************************************************************************
 * Macro Name     : USB_DattogRx / USB_DattogTx .
 * Description    : Toggles DTOG_RX / DTOG_TX bit in the endpoint register.
 * Input          : bEpNum: Endpoint Number.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _ToggleDTOG_RX(bEpNum)                                                                                         \
    (_SetENDPOINT(bEpNum, EP_CTRS_RX | EP_CTRS_TX | EP_DATTOG_RX | (_GetENDPOINT(bEpNum) & EPREG_MASK)))
#define _ToggleDTOG_TX(bEpNum)                                                                                         \
    (_SetENDPOINT(bEpNum, EP_CTRS_RX | EP_CTRS_TX | EP_DATTOG_TX | (_GetENDPOINT(bEpNum) & EPREG_MASK)))

/*******************************************************************************
 * Macro Name     : USB_ClrDattogRx / USB_ClrDattogTx.
 * Description    : Clears DTOG_RX / DTOG_TX bit in the endpoint register.
 * Input          : bEpNum: Endpoint Number.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _ClearDTOG_RX(bEpNum)                                                                                          \
    if ((_GetENDPOINT(bEpNum) & EP_DATTOG_RX) != 0)                                                                    \
    _ToggleDTOG_RX(bEpNum)
#define _ClearDTOG_TX(bEpNum)                                                                                          \
    if ((_GetENDPOINT(bEpNum) & EP_DATTOG_TX) != 0)                                                                    \
    _ToggleDTOG_TX(bEpNum)
/*******************************************************************************
 * Macro Name     : USB_SetEpAddress.
 * Description    : Sets address in an endpoint register.
 * Input          : bEpNum: Endpoint Number.
 *                  bAddr: Address.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _SetEPAddress(bEpNum, bAddr)                                                                                   \
    _SetENDPOINT(bEpNum, EP_CTRS_RX | EP_CTRS_TX | (_GetENDPOINT(bEpNum) & EPREG_MASK) | bAddr)

/*******************************************************************************
 * Macro Name     : USB_GetEpAddress.
 * Description    : Gets address in an endpoint register.
 * Input          : bEpNum: Endpoint Number.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _GetEPAddress(bEpNum) ((uint8_t)(_GetENDPOINT(bEpNum) & EPADDR_FIELD))

#define _pEPTxAddr(bEpNum)  ((uint32_t*)((_GetBTABLE() + bEpNum * 8) * 2 + PMAAddr))
#define _pEPTxCount(bEpNum) ((uint32_t*)((_GetBTABLE() + bEpNum * 8 + 2) * 2 + PMAAddr))
#define _pEPRxAddr(bEpNum)  ((uint32_t*)((_GetBTABLE() + bEpNum * 8 + 4) * 2 + PMAAddr))
#define _pEPRxCount(bEpNum) ((uint32_t*)((_GetBTABLE() + bEpNum * 8 + 6) * 2 + PMAAddr))

/*******************************************************************************
 * Macro Name     : USB_SetEpTxAddr / USB_SetEpRxAddr.
 * Description    : sets address of the tx/rx buffer.
 * Input          : bEpNum: Endpoint Number.
 *                  wAddr: address to be set (must be word aligned).
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _SetEPTxAddr(bEpNum, wAddr) (*_pEPTxAddr(bEpNum) = ((wAddr >> 1) << 1))
#define _SetEPRxAddr(bEpNum, wAddr) (*_pEPRxAddr(bEpNum) = ((wAddr >> 1) << 1))

/*******************************************************************************
 * Macro Name     : USB_GetEpTxAddr / USB_GetEpRxAddr.
 * Description    : Gets address of the tx/rx buffer.
 * Input          : bEpNum: Endpoint Number.
 * Output         : None.
 * Return         : address of the buffer.
 *******************************************************************************/
#define _GetEPTxAddr(bEpNum) ((uint16_t)*_pEPTxAddr(bEpNum))
#define _GetEPRxAddr(bEpNum) ((uint16_t)*_pEPRxAddr(bEpNum))

/*******************************************************************************
 * Macro Name     : USB_SetEpCntRxReg.
 * Description    : Sets counter of rx buffer with no. of blocks.
 * Input          : pdwReg: pointer to counter.
 *                  wCount: Counter.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _BlocksOf32(dwReg, wCount, wNBlocks)                                                                           \
    {                                                                                                                  \
        wNBlocks = wCount >> 5;                                                                                        \
        if ((wCount & 0x1f) == 0)                                                                                      \
            wNBlocks--;                                                                                                \
        *pdwReg = (uint32_t)((wNBlocks << 11) | 0x8000);                                                               \
    } /* _BlocksOf32 */

#define _BlocksOf2(dwReg, wCount, wNBlocks)                                                                            \
    {                                                                                                                  \
        wNBlocks = wCount >> 1;                                                                                        \
        if ((wCount & 0x1) != 0)                                                                                       \
            wNBlocks++;                                                                                                \
        *pdwReg = (uint32_t)(wNBlocks << 10);                                                                          \
    } /* _BlocksOf2 */

#define _SetEPCountRxReg(dwReg, wCount)                                                                                \
    {                                                                                                                  \
        uint16_t wNBlocks;                                                                                             \
        if (wCount > 62)                                                                                               \
        {                                                                                                              \
            _BlocksOf32(dwReg, wCount, wNBlocks);                                                                      \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            _BlocksOf2(dwReg, wCount, wNBlocks);                                                                       \
        }                                                                                                              \
    } /* _SetEPCountRxReg */

#define _SetEPRxDblBuf0Count(bEpNum, wCount)                                                                           \
    {                                                                                                                  \
        uint32_t* pdwReg = _pEPTxCount(bEpNum);                                                                        \
        _SetEPCountRxReg(pdwReg, wCount);                                                                              \
    }
/*******************************************************************************
 * Macro Name     : USB_SetEpTxCnt / USB_SetEpRxCnt.
 * Description    : sets counter for the tx/rx buffer.
 * Input          : bEpNum: endpoint number.
 *                  wCount: Counter value.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _SetEPTxCount(bEpNum, wCount) (*_pEPTxCount(bEpNum) = wCount)
#define _SetEPRxCount(bEpNum, wCount)                                                                                  \
    {                                                                                                                  \
        uint32_t* pdwReg = _pEPRxCount(bEpNum);                                                                        \
        _SetEPCountRxReg(pdwReg, wCount);                                                                              \
    }
/*******************************************************************************
 * Macro Name     : USB_GetEpTxCnt / USB_GetEpRxCnt.
 * Description    : gets counter of the tx buffer.
 * Input          : bEpNum: endpoint number.
 * Output         : None.
 * Return         : Counter value.
 *******************************************************************************/
#define _GetEPTxCount(bEpNum) ((uint16_t)(*_pEPTxCount(bEpNum)) & 0x3ff)
#define _GetEPRxCount(bEpNum) ((uint16_t)(*_pEPRxCount(bEpNum)) & 0x3ff)

/*******************************************************************************
 * Macro Name     : USB_SetEpDblBuf0Addr / USB_SetEpDblBuf1Addr.
 * Description    : Sets buffer 0/1 address in a double buffer endpoint.
 * Input          : bEpNum: endpoint number.
 *                : wBuf0Addr: buffer 0 address.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _SetEPDblBuf0Addr(bEpNum, wBuf0Addr)                                                                           \
    {                                                                                                                  \
        _SetEPTxAddr(bEpNum, wBuf0Addr);                                                                               \
    }
#define _SetEPDblBuf1Addr(bEpNum, wBuf1Addr)                                                                           \
    {                                                                                                                  \
        _SetEPRxAddr(bEpNum, wBuf1Addr);                                                                               \
    }

/*******************************************************************************
 * Macro Name     : USB_SetEpDblBuferAddr.
 * Description    : Sets addresses in a double buffer endpoint.
 * Input          : bEpNum: endpoint number.
 *                : wBuf0Addr: buffer 0 address.
 *                : wBuf1Addr = buffer 1 address.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _SetEPDblBuffAddr(bEpNum, wBuf0Addr, wBuf1Addr)                                                                \
    {                                                                                                                  \
        _SetEPDblBuf0Addr(bEpNum, wBuf0Addr);                                                                          \
        _SetEPDblBuf1Addr(bEpNum, wBuf1Addr);                                                                          \
    } /* _SetEPDblBuffAddr */

/*******************************************************************************
 * Macro Name     : USB_GetEpDblBuf0Addr / USB_GetEpDblBuf1Addr.
 * Description    : Gets buffer 0/1 address of a double buffer endpoint.
 * Input          : bEpNum: endpoint number.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _GetEPDblBuf0Addr(bEpNum) (_GetEPTxAddr(bEpNum))
#define _GetEPDblBuf1Addr(bEpNum) (_GetEPRxAddr(bEpNum))

/*******************************************************************************
 * Macro Name     : USB_SetEpDblBuferCnt / USB_SetEpDblBuf0Cnt / USB_SetEpDblBuf1Cnt.
 * Description    : Gets buffer 0/1 address of a double buffer endpoint.
 * Input          : bEpNum: endpoint number.
 *                : bDir: endpoint dir  EP_DBUF_OUT = OUT
 *                                      EP_DBUF_IN  = IN
 *                : wCount: Counter value
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _SetEPDblBuf0Count(bEpNum, bDir, wCount)                                                                       \
    {                                                                                                                  \
        if (bDir == EP_DBUF_OUT)                                                                                       \
        /* OUT endpoint */                                                                                             \
        {                                                                                                              \
            _SetEPRxDblBuf0Count(bEpNum, wCount);                                                                      \
        }                                                                                                              \
        else if (bDir == EP_DBUF_IN)                                                                                   \
            /* IN endpoint */                                                                                          \
            *_pEPTxCount(bEpNum) = (uint32_t)wCount;                                                                   \
    } /* USB_SetEpDblBuf0Cnt*/

#define _SetEPDblBuf1Count(bEpNum, bDir, wCount)                                                                       \
    {                                                                                                                  \
        if (bDir == EP_DBUF_OUT)                                                                                       \
        /* OUT endpoint */                                                                                             \
        {                                                                                                              \
            _SetEPRxCount(bEpNum, wCount);                                                                             \
        }                                                                                                              \
        else if (bDir == EP_DBUF_IN)                                                                                   \
            /* IN endpoint */                                                                                          \
            *_pEPRxCount(bEpNum) = (uint32_t)wCount;                                                                   \
    } /* USB_SetEpDblBuf1Cnt */

#define _SetEPDblBuffCount(bEpNum, bDir, wCount)                                                                       \
    {                                                                                                                  \
        _SetEPDblBuf0Count(bEpNum, bDir, wCount);                                                                      \
        _SetEPDblBuf1Count(bEpNum, bDir, wCount);                                                                      \
    } /* _SetEPDblBuffCount  */

/*******************************************************************************
 * Macro Name     : USB_GetEpDblBuf0Cnt / USB_GetEpDblBuf1Cnt.
 * Description    : Gets buffer 0/1 rx/tx counter for double buffering.
 * Input          : bEpNum: endpoint number.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
#define _GetEPDblBuf0Count(bEpNum) (_GetEPTxCount(bEpNum))
#define _GetEPDblBuf1Count(bEpNum) (_GetEPRxCount(bEpNum))

extern __IO uint16_t wIstr; /* USB_STS register last read value */

void USB_SetCtrl(uint16_t /*wRegValue*/);
void USB_SetSts(uint16_t /*wRegValue*/);
void USB_SetAddr(uint16_t /*wRegValue*/);
void USB_SetBuftab(uint16_t /*wRegValue*/);
void USB_SetBuftab(uint16_t /*wRegValue*/);
uint16_t USB_GetCtrl(void);
uint16_t USB_GetSts(void);
uint16_t USB_GetFn(void);
uint16_t USB_GetAddr(void);
uint16_t USB_GetBTABLE(void);
void USB_SetEndPoint(uint8_t /*bEpNum*/, uint16_t /*wRegValue*/);
uint16_t USB_GetEndPoint(uint8_t /*bEpNum*/);
void USB_SetEpType(uint8_t /*bEpNum*/, uint16_t /*wType*/);
uint16_t USB_GetEpType(uint8_t /*bEpNum*/);
void SetEPTxStatus(uint8_t /*bEpNum*/, uint16_t /*wState*/);
void SetEPRxStatus(uint8_t /*bEpNum*/, uint16_t /*wState*/);
void USB_SetDouBleBuferEpStall(uint8_t /*bEpNum*/, uint8_t bDir);
uint16_t USB_GetEpTxSts(uint8_t /*bEpNum*/);
uint16_t USB_GetEpRxSts(uint8_t /*bEpNum*/);
void USB_SetEpTxValid(uint8_t /*bEpNum*/);
void USB_SetEpRxValid(uint8_t /*bEpNum*/);
uint16_t USB_GetTxStallSts(uint8_t /*bEpNum*/);
uint16_t USB_GetRxStallSts(uint8_t /*bEpNum*/);
void USB_SetEpKind(uint8_t /*bEpNum*/);
void USB_ClrEpKind(uint8_t /*bEpNum*/);
void USB_SetStsOut(uint8_t /*bEpNum*/);
void USB_ClrStsOut(uint8_t /*bEpNum*/);
void USB_SetEpDoubleBufer(uint8_t /*bEpNum*/);
void USB_ClrEpDoubleBufer(uint8_t /*bEpNum*/);
void USB_ClrEpCtrsRx(uint8_t /*bEpNum*/);
void USB_ClrEpCtrsTx(uint8_t /*bEpNum*/);
void USB_DattogRx(uint8_t /*bEpNum*/);
void USB_DattogTx(uint8_t /*bEpNum*/);
void USB_ClrDattogRx(uint8_t /*bEpNum*/);
void USB_ClrDattogTx(uint8_t /*bEpNum*/);
void USB_SetEpAddress(uint8_t /*bEpNum*/, uint8_t /*bAddr*/);
uint8_t USB_GetEpAddress(uint8_t /*bEpNum*/);
void USB_SetEpTxAddr(uint8_t /*bEpNum*/, uint16_t /*wAddr*/);
void USB_SetEpRxAddr(uint8_t /*bEpNum*/, uint16_t /*wAddr*/);
uint16_t USB_GetEpTxAddr(uint8_t /*bEpNum*/);
uint16_t USB_GetEpRxAddr(uint8_t /*bEpNum*/);
void USB_SetEpCntRxReg(uint32_t* /*pdwReg*/, uint16_t /*wCount*/);
void USB_SetEpTxCnt(uint8_t /*bEpNum*/, uint16_t /*wCount*/);
void USB_SetEpRxCnt(uint8_t /*bEpNum*/, uint16_t /*wCount*/);
uint16_t USB_GetEpTxCnt(uint8_t /*bEpNum*/);
uint16_t USB_GetEpRxCnt(uint8_t /*bEpNum*/);
void USB_SetEpDblBuf0Addr(uint8_t /*bEpNum*/, uint16_t /*wBuf0Addr*/);
void USB_SetEpDblBuf1Addr(uint8_t /*bEpNum*/, uint16_t /*wBuf1Addr*/);
void USB_SetEpDblBuferAddr(uint8_t /*bEpNum*/, uint16_t /*wBuf0Addr*/, uint16_t /*wBuf1Addr*/);
uint16_t USB_GetEpDblBuf0Addr(uint8_t /*bEpNum*/);
uint16_t USB_GetEpDblBuf1Addr(uint8_t /*bEpNum*/);
void USB_SetEpDblBuferCnt(uint8_t /*bEpNum*/, uint8_t /*bDir*/, uint16_t /*wCount*/);
void USB_SetEpDblBuf0Cnt(uint8_t /*bEpNum*/, uint8_t /*bDir*/, uint16_t /*wCount*/);
void USB_SetEpDblBuf1Cnt(uint8_t /*bEpNum*/, uint8_t /*bDir*/, uint16_t /*wCount*/);
uint16_t USB_GetEpDblBuf0Cnt(uint8_t /*bEpNum*/);
uint16_t USB_GetEpDblBuf1Cnt(uint8_t /*bEpNum*/);
EP_DBUF_DIR GetEPDblBufDir(uint8_t /*bEpNum*/);
void USB_FreeUserBuf(uint8_t bEpNum /*bEpNum*/, uint8_t bDir);
uint16_t USB_ToWord(uint8_t, uint8_t);
uint16_t USB_ByteSwap(uint16_t);

/**
 * @}
 */

#endif /* __USB_REGS_H__ */
