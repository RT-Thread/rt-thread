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
 * @file usb_int.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "usb_lib.h"

__IO uint16_t SaveRState;
__IO uint16_t SaveTState;

extern void (*pEpInt_IN[7])(void);  /*  Handles IN  interrupts   */
extern void (*pEpInt_OUT[7])(void); /*  Handles OUT interrupts   */

/**
 * @brief Low priority Endpoint Correct Transfer interrupt's service routine.
 */
void USB_CorrectTransferLp(void)
{
    __IO uint16_t wEPVal = 0;
    /* stay in loop while pending interrupts */
    while (((wIstr = _GetISTR()) & STS_CTRS) != 0)
    {
        /* extract highest priority endpoint number */
        EPindex = (uint8_t)(wIstr & STS_EP_ID);
        if (EPindex == 0)
        {
            /* Decode and service control endpoint interrupt */
            /* calling related service routine */
            /* (USB_ProcessSetup0, USB_ProcessIn0, USB_ProcessOut0) */

            /* save RX & TX status */
            /* and set both to NAK */

            SaveRState = _GetENDPOINT(ENDP0);
            SaveTState = SaveRState & EPTX_STS;
            SaveRState &= EPRX_STS;
            _SetEPRxTxStatus(ENDP0, EP_RX_NAK, EP_TX_NAK);

            /* DIR bit = origin of the interrupt */

            if ((wIstr & STS_DIR) == 0)
            {
                /* DIR = 0 */

                /* DIR = 0      => IN  int */
                /* DIR = 0 implies that (EP_CTRS_TX = 1) always  */

                _ClearEP_CTR_TX(ENDP0);
                USB_ProcessIn0();

                /* before terminate set Tx & Rx status */

                _SetEPRxTxStatus(ENDP0, SaveRState, SaveTState);
                return;
            }
            else
            {
                /* DIR = 1 */

                /* DIR = 1 & CTR_RX       => SETUP or OUT int */
                /* DIR = 1 & (CTR_TX | CTR_RX) => 2 int pending */

                wEPVal = _GetENDPOINT(ENDP0);

                if ((wEPVal & EP_SETUP) != 0)
                {
                    _ClearEP_CTR_RX(ENDP0); /* SETUP bit kept frozen while CTR_RX = 1 */
                    USB_ProcessSetup0();
                    /* before terminate set Tx & Rx status */

                    _SetEPRxTxStatus(ENDP0, SaveRState, SaveTState);
                    return;
                }

                else if ((wEPVal & EP_CTRS_RX) != 0)
                {
                    _ClearEP_CTR_RX(ENDP0);
                    USB_ProcessOut0();
                    /* before terminate set Tx & Rx status */

                    _SetEPRxTxStatus(ENDP0, SaveRState, SaveTState);
                    return;
                }
            }
        } /* if (EPindex == 0) */
        else
        {
            /* Decode and service non control endpoints interrupt  */

            /* process related endpoint register */
            wEPVal = _GetENDPOINT(EPindex);
            if ((wEPVal & EP_CTRS_RX) != 0)
            {
                /* clear int flag */
                _ClearEP_CTR_RX(EPindex);

                /* call OUT service function */
                (*pEpInt_OUT[EPindex - 1])();

            } /* if ((wEPVal & EP_CTRS_RX) */

            if ((wEPVal & EP_CTRS_TX) != 0)
            {
                /* clear int flag */
                _ClearEP_CTR_TX(EPindex);

                /* call IN service function */
                (*pEpInt_IN[EPindex - 1])();
            } /* if ((wEPVal & EP_CTRS_TX) != 0) */

        } /* if (EPindex == 0) else */

    } /* while (...) */
}

/**
 * @brief High Priority Endpoint Correct Transfer interrupt's service routine.
 */
void USB_CorrectTransferHp(void)
{
    uint32_t wEPVal = 0;

    while (((wIstr = _GetISTR()) & STS_CTRS) != 0)
    {
        _SetISTR((uint16_t)CLR_CTRS); /* clear CTR flag */
        /* extract highest priority endpoint number */
        EPindex = (uint8_t)(wIstr & STS_EP_ID);
        /* process related endpoint register */
        wEPVal = _GetENDPOINT(EPindex);
        if ((wEPVal & EP_CTRS_RX) != 0)
        {
            /* clear int flag */
            _ClearEP_CTR_RX(EPindex);

            /* call OUT service function */
            (*pEpInt_OUT[EPindex - 1])();

        } /* if ((wEPVal & EP_CTRS_RX) */
        else if ((wEPVal & EP_CTRS_TX) != 0)
        {
            /* clear int flag */
            _ClearEP_CTR_TX(EPindex);

            /* call IN service function */
            (*pEpInt_IN[EPindex - 1])();

        } /* if ((wEPVal & EP_CTRS_TX) != 0) */

    } /* while (...) */
}
