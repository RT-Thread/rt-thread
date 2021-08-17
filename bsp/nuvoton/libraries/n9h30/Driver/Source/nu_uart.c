/**************************************************************************//**
* @file     uart.c
* @version  V1.00
* @brief    N9H30 UART driver source file
*
* SPDX-License-Identifier: Apache-2.0
* @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "N9H30.h"
#include "nu_sys.h"
#include "nu_uart.h"

/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_UART_Driver UART Driver
  @{
*/

/** @addtogroup N9H30_UART_EXPORTED_CONSTANTS UART Exported Constants
  @{
*/

/*@}*/ /* end of group N9H30_UART_EXPORTED_CONSTANTS */

/// @cond HIDDEN_SYMBOLS

/*-----------------------------------------*/
/* marco, type and constant definitions    */
/*-----------------------------------------*/
/*
    Define debug level
*/
//#define UART_DEBUG
//#define UART_FLOWCONTROL_DEBUG
//#define UART1_DEBUG
//#define UART2_DEBUG

#ifdef UART_DEBUG
    #define UDEBUG          sysprintf
#else
    #define UDEBUG(...)
#endif  /* UART_DEBUG */

#ifdef UART_FLOWCONTROL_DEBUG
    #define FDEBUG          sysprintf
#else
    #define FDEBUG(...)
#endif  /* UART_FLOWCONTROL_DEBUG */

#ifdef UART1_DEBUG
    #define U1DEBUG         sysprintf
#else
    #define U1DEBUG(...)
#endif  /* UART1_DEBUG */

#ifdef UART2_DEBUG
    #define U2DEBUG         sysprintf
#else
    #define U2DEBUG(...)
#endif  /* UART1_DEBUG */

/*-----------------------------------------*/
/* global file scope (static) variables    */
/*-----------------------------------------*/
static UART_BUFFER_T UART_DEV[UART_NUM];

static UINT32 UARTTXBUFSIZE[UART_NUM] = {500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500};  /* UART0~10 Tx buffer size */
static UINT32 UARTRXBUFSIZE[UART_NUM] = {500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500};    /* UART0~10 Rx buffer size */


/*
    UART flag declarations.
*/
static volatile CHAR _uart_cDSRState0 = 0;   /* set 1, state change                         */
static volatile CHAR _uart_cDSRState1 = 0;   /* set 1, state change                         */
static volatile CHAR _uart_cDSRState2 = 0;   /* set 1, state change                         */
static volatile CHAR _uart_cDSRState3 = 0;   /* set 1, state change                         */
static volatile CHAR _uart_cDSRState4 = 0;   /* set 1, state change                         */
static volatile CHAR _uart_cDSRState5 = 0;   /* set 1, state change                         */
static volatile CHAR _uart_cDSRState6 = 0;   /* set 1, state change                         */
static volatile CHAR _uart_cDSRState7 = 0;   /* set 1, state change                         */
static volatile CHAR _uart_cDSRState8 = 0;   /* set 1, state change                         */
static volatile CHAR _uart_cDSRState9 = 0;   /* set 1, state change                         */
static volatile CHAR _uart_cDSRState10 = 0;   /* set 1, state change                         */
static volatile CHAR _uart_cBIIState_0 = 0;  /* set 1, UART channel 0 break interrupt occur */
static volatile CHAR _uart_cBIIState_1 = 0;  /* set 1, UART channel 1 break interrupt occur */
static volatile CHAR _uart_cBIIState_2 = 0;  /* set 1, UART channel 2 break interrupt occur */
static volatile CHAR _uart_cBIIState_3 = 0;  /* set 1, UART channel 3 break interrupt occur */
static volatile CHAR _uart_cBIIState_4 = 0;  /* set 1, UART channel 4 break interrupt occur */
static volatile CHAR _uart_cBIIState_5 = 0;  /* set 1, UART channel 0 break interrupt occur */
static volatile CHAR _uart_cBIIState_6 = 0;  /* set 1, UART channel 1 break interrupt occur */
static volatile CHAR _uart_cBIIState_7 = 0;  /* set 1, UART channel 2 break interrupt occur */
static volatile CHAR _uart_cBIIState_8 = 0;  /* set 1, UART channel 3 break interrupt occur */
static volatile CHAR _uart_cBIIState_9 = 0;  /* set 1, UART channel 4 break interrupt occur */
static volatile CHAR _uart_cBIIState_10 = 0;  /* set 1, UART channel 4 break interrupt occur */
static volatile CHAR _uart_cCTSState0 = 0;    /* set 1, state change                         */
static volatile CHAR _uart_cCTSState1 = 0;    /* set 1, state change                         */
static volatile CHAR _uart_cCTSState2 = 0;    /* set 1, state change                         */
static volatile CHAR _uart_cCTSState3 = 0;    /* set 1, state change                         */
static volatile CHAR _uart_cCTSState4 = 0;    /* set 1, state change                         */
static volatile CHAR _uart_cCTSState5 = 0;    /* set 1, state change                         */
static volatile CHAR _uart_cCTSState6 = 0;    /* set 1, state change                         */
static volatile CHAR _uart_cCTSState7 = 0;    /* set 1, state change                         */
static volatile CHAR _uart_cCTSState8 = 0;    /* set 1, state change                         */
static volatile CHAR _uart_cCTSState9 = 0;    /* set 1, state change                         */
static volatile CHAR _uart_cCTSState10 = 0;    /* set 1, state change                         */

/*
    Define flow control flags & parameters.
*/
#define HWFLOWCONTROL   1
#define SWFLOWCONTROL   2
static volatile CHAR _uart_cFlowControlMode = 0;  /* default no flow control */
static volatile CHAR _uart_cHWTXStopped = 0;      /* Use for H/W flow control. Set 1, stop TX. Set 0, start TX.   */
static volatile CHAR _uart_cHWRXStopped = 0;      /* Use for H/W flow control. Set 1, stop RX. Set 0, start RX.   */
static volatile CHAR _uart_cSWTXStopped = 0;      /* Use for S/W flow control. Set 1, rec Xoff. Set 0, rec Xon.   */
static volatile CHAR _uart_cSWRXStopped = 0;      /* Use for S/W flow control. Set 1, send Xoff. Set 0, send Xon. */
//static INT _uart_nMaxRxBuf = 0;                   /* used in uartReceiveChars() */
//static INT _uart_nMinRxBuf = 0;                   /* used in uartReadRxBuf()    */


/*-----------------------------------------*/
/* prototypes of static functions          */
/*-----------------------------------------*/
static UINT32 _uartTxBufGetNextOne(INT nNum, UINT32 uPointer);
static UINT32 _uartRxBufGetNextOne(INT nNum, UINT32 uPointer);
static void _uartEnableInterrupt(INT nNum, UINT32 uVal);
static void _uartDisableInterrupt(INT nNum, UINT32 uVal);
static void _uartReceiveChars(INT nNum);
static void _uartTransmitChars(INT nNum);
static void _uartCheckModemStatus(INT nNum);
static INT _uartSetBaudRate(INT nNum, UART_T *val);
static void _uartInstallISR(UINT8 ucNum);
static BOOL _uartBUFSpaceAlloc(INT nNum);
static BOOL _uartCheckTxBufSpace(INT nNum, UINT32 uHead, UINT32 uTail, UINT32 uLen);
static INT32 _uartReadRxBuf(INT nNum, PUINT8 pucBuf, UINT32 uLen);
static void _uartWriteTxBuf(INT nNum, PUINT8 pucBuf, UINT32 uLen);
static INT _uartConfigureUART(PVOID pvParam);
static INT _uartPerformIrDA(INT nNum, UINT32 uCmd, UINT32 uCmd1);
static INT _uartGetRegisterValue(INT nNum, PVOID pvReg);


void RS485_HANDLE(INT nNum)
{
    UINT32 volatile uRegISR, uRegFSR, uRegALT_CSR;

    uRegISR = inpw(REG_UART0_ISR + (nNum * UARTOFFSET));
    uRegFSR = inpw(REG_UART0_FSR + (nNum * UARTOFFSET));

    if ((uRegISR & UART_ISR_RLS_IF_Msk) && (uRegISR & UART_ISR_RDA_IF_Msk)) /* RLS INT & RDA INT */ //For RS485 Detect Address
    {
        if (uRegFSR & UART_FSR_RS485_ADD_DETF_Msk)  /* ADD_IF, RS485 mode */
        {
            _uartReceiveChars(nNum);
            outpw((REG_UART0_FSR + (nNum * UARTOFFSET)), UART_FSR_RS485_ADD_DETF_Msk); /* clear ADD_IF flag */
        }
    }
    else if (uRegISR & (UART_ISR_RDA_IF_Msk | UART_ISR_TOUT_IF_Msk))     /* Rx Ready or Time-out INT*/
    {
        /* Handle received data */
        _uartReceiveChars(nNum);
    }

    if (uRegISR & UART_ISR_RLS_IF_Msk)
    {
        uRegFSR = inpw(REG_UART0_FSR + (nNum * UARTOFFSET));
        if (uRegFSR & UART_FSR_BIF_Msk)
            _uart_cBIIState_0 = 1;
    }
}

void uart0ISR(void)
{
    UINT32 volatile uRegISR, uRegFSR;

    uRegISR = inpw(REG_UART0_ISR) & 0xff;

    if (uRegISR & UART_ISR_THRE_IF_Msk) /* TX empty interrupt, check LSR 4 kinds of error further */
        _uartTransmitChars(UART0);

    if (uRegISR & (UART_ISR_RDA_IF_Msk | UART_ISR_TOUT_IF_Msk)) /* Received Data Available interrupt */
        _uartReceiveChars(UART0);

    if (uRegISR & UART_ISR_RLS_IF_Msk)
    {
        uRegFSR = inpw(REG_UART0_FSR);
        if (uRegFSR & UART_FSR_BIF_Msk)
            _uart_cBIIState_0 = 1;
    }

}

void uart1ISR(void)
{
    UINT32 volatile uRegISR, uRegFSR, uRegMSR, uRegFUN_SEL;

    uRegISR = inpw(REG_UART1_ISR) & 0xff;
    uRegFUN_SEL = inpw(REG_UART1_FUN_SEL);

    if (uRegISR & UART_ISR_THRE_IF_Msk) /* TX empty interrupt, check LSR 4 kinds of error further */
        _uartTransmitChars(UART1);

    if (uRegFUN_SEL == 0x3)
    {
        RS485_HANDLE(UART1);
    }
    else
    {
        if (uRegISR & (UART_ISR_RDA_IF_Msk | UART_ISR_TOUT_IF_Msk)) /* Received Data Available interrupt */
            _uartReceiveChars(UART1);

        if (uRegISR & UART_ISR_MODEM_IF_Msk)
        {
            if (_uart_cFlowControlMode == 0)
            {
                uRegMSR = inpw(REG_UART1_MSR);

                if (uRegMSR & 0x01)
                    _uart_cCTSState1 = 1;
            }
            else
                _uartCheckModemStatus(UART1);  /* H/W flow control */
        }

        if (uRegISR & UART_ISR_RLS_IF_Msk)
        {
            uRegFSR = inpw(REG_UART1_FSR);
            U1DEBUG("U1 Irpt_RLS [0x%x]!\n", uRegFSR);

            if (uRegFSR & UART_FSR_BIF_Msk)
                _uart_cBIIState_1 = 1;

            if (uRegFSR & UART_FSR_RX_OVER_IF_Msk)
                U1DEBUG("U1 OEI!\n");
        }
    }
}

void uart2ISR(void)
{
    UINT32 volatile uRegISR, uRegFSR, uRegMSR, uRegFUN_SEL;

    uRegISR = inpw(REG_UART2_ISR) & 0xff;
    uRegFUN_SEL = inpw(REG_UART2_FUN_SEL);

    if (uRegISR & UART_ISR_THRE_IF_Msk) /* TX empty interrupt, check LSR 4 kinds of error further */
        _uartTransmitChars(UART2);

    if (uRegFUN_SEL == 0x3)
    {
        RS485_HANDLE(UART2);
    }
    else
    {
        if (uRegISR & (UART_ISR_RDA_IF_Msk | UART_ISR_TOUT_IF_Msk)) /* Received Data Available interrupt */
            _uartReceiveChars(UART2);

        if (uRegISR & UART_ISR_RLS_IF_Msk)
        {
            uRegFSR = inpw(REG_UART2_FSR);
            if (uRegFSR & UART_FSR_BIF_Msk)
                _uart_cBIIState_2 = 1;
        }

        if (uRegISR & UART_ISR_MODEM_IF_Msk)
        {
            if (_uart_cFlowControlMode == 0)
            {
                uRegMSR = inpw(REG_UART2_MSR);

                if (uRegMSR & 0x01)
                    _uart_cCTSState2 = 1;
            }
            else
                _uartCheckModemStatus(UART2);  /* H/W flow control */
        }

        if (uRegISR & UART_ISR_RLS_IF_Msk)
        {
            uRegFSR = inpw(REG_UART2_FSR);
            U1DEBUG("U2 Irpt_RLS [0x%x]!\n", uRegFSR);

            if (uRegFSR & UART_FSR_BIF_Msk)
                _uart_cBIIState_2 = 1;

            if (uRegFSR & UART_FSR_RX_OVER_IF_Msk)
                U1DEBUG("U2 OEI!\n");
        }
    }
}

void uart3ISR(void)
{
    UINT32 volatile uRegISR, uRegFSR, uRegMSR, uRegFUN_SEL;

    uRegISR = inpw(REG_UART3_ISR) & 0xff;
    uRegFUN_SEL = inpw(REG_UART3_FUN_SEL);

    if (uRegISR & UART_ISR_THRE_IF_Msk) /* TX empty interrupt, check LSR 4 kinds of error further */
        _uartTransmitChars(UART3);

    if (uRegFUN_SEL == 0x3)
    {
        RS485_HANDLE(UART3);
    }
    else
    {
        if (uRegISR & (UART_ISR_RDA_IF_Msk | UART_ISR_TOUT_IF_Msk))
            _uartReceiveChars(UART3);

        if (uRegISR & UART_ISR_MODEM_IF_Msk)
        {
            if (_uart_cFlowControlMode == 0)
            {
                uRegMSR = inpw(REG_UART3_MSR);

                if (uRegMSR & 0x01)
                    _uart_cCTSState3 = 1;
            }
            else
                _uartCheckModemStatus(UART3);  /* H/W flow control */
        }

        if (uRegISR & UART_ISR_RLS_IF_Msk)
        {
            uRegFSR = inpw(REG_UART3_FSR);
            U1DEBUG("U3 Irpt_RLS [0x%x]!\n", uRegFSR);

            if (uRegFSR & UART_FSR_BIF_Msk)
                _uart_cBIIState_3 = 1;

            if (uRegFSR & UART_FSR_RX_OVER_IF_Msk)
                U1DEBUG("U3 OEI!\n");
        }
    }

}

void uart4ISR(void)
{
    UINT32 volatile uRegISR, uRegFSR, uRegMSR, uRegFUN_SEL;

    uRegISR = inpw(REG_UART4_ISR) & 0xff;
    uRegFUN_SEL = inpw(REG_UART4_FUN_SEL);

    if (uRegISR & UART_ISR_THRE_IF_Msk) /* TX empty interrupt, check LSR 4 kinds of error further */
        _uartTransmitChars(UART4);

    if (uRegFUN_SEL == 0x3)
    {
        RS485_HANDLE(UART4);
    }
    else
    {
        if (uRegISR & (UART_ISR_RDA_IF_Msk | UART_ISR_TOUT_IF_Msk)) /* Received Data Available interrupt */
            _uartReceiveChars(UART4);

        if (uRegISR & UART_ISR_MODEM_IF_Msk)
        {
            if (_uart_cFlowControlMode == 0)
            {
                uRegMSR = inpw(REG_UART4_MSR);

                if (uRegMSR & 0x01)
                    _uart_cCTSState4 = 1;
            }
            else
                _uartCheckModemStatus(UART4);  /* H/W flow control */
        }

        if (uRegISR & UART_ISR_RLS_IF_Msk)
        {
            uRegFSR = inpw(REG_UART4_FSR);
            U1DEBUG("U4 Irpt_RLS [0x%x]!\n", uRegFSR);

            if (uRegFSR & UART_FSR_BIF_Msk)
                _uart_cBIIState_4 = 1;

            if (uRegFSR & UART_FSR_RX_OVER_IF_Msk)
                U1DEBUG("U4 OEI!\n");
        }
    }

}

void uart5ISR(void)
{
    UINT32 volatile uRegISR, uRegFSR, uRegMSR, uRegFUN_SEL;

    uRegISR = inpw(REG_UART5_ISR) & 0xff;
    uRegFUN_SEL = inpw(REG_UART5_FUN_SEL);

    if (uRegISR & UART_ISR_THRE_IF_Msk) /* TX empty interrupt, check LSR 4 kinds of error further */
        _uartTransmitChars(UART5);

    if (uRegFUN_SEL == 0x3)
    {
        RS485_HANDLE(UART5);
    }
    else
    {
        if (uRegISR & (UART_ISR_RDA_IF_Msk | UART_ISR_TOUT_IF_Msk)) /* Received Data Available interrupt */
            _uartReceiveChars(UART5);

        if (uRegISR & UART_ISR_MODEM_IF_Msk)
        {
            if (_uart_cFlowControlMode == 0)
            {
                uRegMSR = inpw(REG_UART5_MSR);

                if (uRegMSR & 0x01)
                    _uart_cCTSState5 = 1;
            }
            else
                _uartCheckModemStatus(UART5);  /* H/W flow control */
        }

        if (uRegISR & UART_ISR_RLS_IF_Msk)
        {
            uRegFSR = inpw(REG_UART5_FSR);
            U1DEBUG("U5 Irpt_RLS [0x%x]!\n", uRegFSR);

            if (uRegFSR & UART_FSR_BIF_Msk)
                _uart_cBIIState_5 = 1;

            if (uRegFSR & UART_FSR_RX_OVER_IF_Msk)
                U1DEBUG("U5 OEI!\n");
        }
    }

}

void uart6ISR(void)
{
    UINT32 volatile uRegISR, uRegFSR, uRegMSR, uRegFUN_SEL;

    uRegISR = inpw(REG_UART6_ISR) & 0xff;
    uRegFUN_SEL = inpw(REG_UART6_FUN_SEL);

    if (uRegISR & UART_ISR_THRE_IF_Msk) /* TX empty interrupt, check LSR 4 kinds of error further */
        _uartTransmitChars(UART6);

    if (uRegFUN_SEL == 0x3)
    {
        RS485_HANDLE(UART6);
    }
    else
    {
        if (uRegISR & (UART_ISR_RDA_IF_Msk | UART_ISR_TOUT_IF_Msk)) /* Received Data Available interrupt */
            _uartReceiveChars(UART6);

        if (uRegISR & UART_ISR_MODEM_IF_Msk)
        {
            if (_uart_cFlowControlMode == 0)
            {
                uRegMSR = inpw(REG_UART6_MSR);

                if (uRegMSR & 0x01)
                    _uart_cCTSState6 = 1;
            }
            else
                _uartCheckModemStatus(UART6);  /* H/W flow control */
        }

        if (uRegISR & UART_ISR_RLS_IF_Msk)
        {
            uRegFSR = inpw(REG_UART6_FSR);
            U1DEBUG("U6 Irpt_RLS [0x%x]!\n", uRegFSR);

            if (uRegFSR & UART_FSR_BIF_Msk)
                _uart_cBIIState_6 = 1;

            if (uRegFSR & UART_FSR_RX_OVER_IF_Msk)
                U1DEBUG("U6 OEI!\n");
        }
    }

}

void uart7ISR(void)
{
    UINT32 volatile uRegISR, uRegFSR, uRegMSR, uRegFUN_SEL;

    uRegISR = inpw(REG_UART7_ISR) & 0xff;
    uRegFUN_SEL = inpw(REG_UART7_FUN_SEL);

    if (uRegISR & UART_ISR_THRE_IF_Msk) /* TX empty interrupt, check LSR 4 kinds of error further */
        _uartTransmitChars(UART7);

    if (uRegFUN_SEL == 0x3)
    {
        RS485_HANDLE(UART7);
    }
    else
    {
        if (uRegISR & (UART_ISR_RDA_IF_Msk | UART_ISR_TOUT_IF_Msk)) /* Received Data Available interrupt */
            _uartReceiveChars(UART7);

        if (uRegISR & UART_ISR_MODEM_IF_Msk)
        {
            if (_uart_cFlowControlMode == 0)
            {
                uRegMSR = inpw(REG_UART7_MSR);

                if (uRegMSR & 0x01)
                    _uart_cCTSState7 = 1;
            }
            else
                _uartCheckModemStatus(UART7);  /* H/W flow control */
        }

        if (uRegISR & UART_ISR_RLS_IF_Msk)
        {
            uRegFSR = inpw(REG_UART7_FSR);
            U1DEBUG("U7 Irpt_RLS [0x%x]!\n", uRegFSR);

            if (uRegFSR & UART_FSR_BIF_Msk)
                _uart_cBIIState_7 = 1;

            if (uRegFSR & UART_FSR_RX_OVER_IF_Msk)
                U1DEBUG("U7 OEI!\n");
        }
    }

}

void uart8ISR(void)
{
    UINT32 volatile uRegISR, uRegFSR, uRegMSR, uRegFUN_SEL;

    uRegISR = inpw(REG_UART8_ISR) & 0xff;
    uRegFUN_SEL = inpw(REG_UART8_FUN_SEL);

    if (uRegISR & UART_ISR_THRE_IF_Msk) /* TX empty interrupt, check LSR 4 kinds of error further */
        _uartTransmitChars(UART8);

    if (uRegFUN_SEL == 0x3)
    {
        RS485_HANDLE(UART8);
    }
    else
    {
        if (uRegISR & (UART_ISR_RDA_IF_Msk | UART_ISR_TOUT_IF_Msk)) /* Received Data Available interrupt */
            _uartReceiveChars(UART8);

        if (uRegISR & UART_ISR_MODEM_IF_Msk)
        {
            if (_uart_cFlowControlMode == 0)
            {
                uRegMSR = inpw(REG_UART8_MSR);

                if (uRegMSR & 0x01)
                    _uart_cCTSState8 = 1;
            }
            else
                _uartCheckModemStatus(UART8);  /* H/W flow control */
        }

        if (uRegISR & UART_ISR_RLS_IF_Msk)
        {
            uRegFSR = inpw(REG_UART8_FSR);
            U1DEBUG("U8 Irpt_RLS [0x%x]!\n", uRegFSR);

            if (uRegFSR & UART_FSR_BIF_Msk)
                _uart_cBIIState_8 = 1;

            if (uRegFSR & UART_FSR_RX_OVER_IF_Msk)
                U1DEBUG("U8 OEI!\n");
        }
    }

}

void uart9ISR(void)
{
    UINT32 volatile uRegISR, uRegFSR, uRegMSR, uRegFUN_SEL;

    uRegISR = inpw(REG_UART9_ISR) & 0xff;
    uRegFUN_SEL = inpw(REG_UART9_FUN_SEL);

    if (uRegISR & UART_ISR_THRE_IF_Msk) /* TX empty interrupt, check LSR 4 kinds of error further */
        _uartTransmitChars(UART9);

    if (uRegFUN_SEL == 0x3)
    {
        RS485_HANDLE(UART9);
    }
    else
    {
        if (uRegISR & (UART_ISR_RDA_IF_Msk | UART_ISR_TOUT_IF_Msk))  /* Received Data Available interrupt */
            _uartReceiveChars(UART9);

        if (uRegISR & UART_ISR_MODEM_IF_Msk)
        {
            if (_uart_cFlowControlMode == 0)
            {
                uRegMSR = inpw(REG_UART9_MSR);

                if (uRegMSR & 0x01)
                    _uart_cCTSState9 = 1;
            }
            else
                _uartCheckModemStatus(UART9);  /* H/W flow control */
        }

        if (uRegISR & UART_ISR_RLS_IF_Msk)
        {
            uRegFSR = inpw(REG_UART9_FSR);
            U1DEBUG("U9 Irpt_RLS [0x%x]!\n", uRegFSR);

            if (uRegFSR & UART_FSR_BIF_Msk)
                _uart_cBIIState_9 = 1;

            if (uRegFSR & UART_FSR_RX_OVER_IF_Msk)
                U1DEBUG("U9 OEI!\n");
        }
    }

}

void uart10ISR(void)
{
    UINT32 volatile uRegISR, uRegFSR, uRegMSR, uRegFUN_SEL;

    uRegISR = inpw(REG_UARTA_ISR) & 0xff;
    uRegFUN_SEL = inpw(REG_UARTA_FUN_SEL);

    if (uRegISR & UART_ISR_THRE_IF_Msk) /* TX empty interrupt, check LSR 4 kinds of error further */
        _uartTransmitChars(UARTA);

    if (uRegFUN_SEL == 0x3)
    {
        RS485_HANDLE(UARTA);
    }
    else
    {
        if (uRegISR & (UART_ISR_RDA_IF_Msk | UART_ISR_TOUT_IF_Msk)) /* Received Data Available interrupt */
            _uartReceiveChars(UARTA);

        if (uRegISR & UART_ISR_MODEM_IF_Msk)
        {
            if (_uart_cFlowControlMode == 0)
            {
                uRegMSR = inpw(REG_UARTA_MSR);

                if (uRegMSR & 0x01)
                    _uart_cCTSState10 = 1;
            }
            else
                _uartCheckModemStatus(UARTA);  /* H/W flow control */
        }

        if (uRegISR & UART_ISR_RLS_IF_Msk)
        {
            uRegFSR = inpw(REG_UARTA_FSR);
            U1DEBUG("U10 Irpt_RLS [0x%x]!\n", uRegFSR);

            if (uRegFSR & UART_FSR_BIF_Msk)
                _uart_cBIIState_10 = 1;

            if (uRegFSR & UART_FSR_RX_OVER_IF_Msk)
                U1DEBUG("U10 OEI!\n");
        }
    }

}

static UINT32 _uartTxBufGetNextOne(INT nNum, UINT32 uPointer)
{
    if ((uPointer + 1) == UARTTXBUFSIZE[nNum])
        return (UINT32)NULL;
    else
        return (uPointer + 1);
}

static UINT32 _uartRxBufGetNextOne(INT nNum, UINT32 uPointer)
{
    if ((uPointer + 1) == UARTRXBUFSIZE[nNum])
        return (UINT32)NULL;
    else
        return (uPointer + 1);
}

static void _uartEnableInterrupt(INT nNum, UINT32 uVal)
{
    UINT32 uReg = 0;

    uReg = inpw(REG_UART0_IER + (nNum * UARTOFFSET));
    uReg |= uVal;
    outpw(REG_UART0_IER + (nNum * UARTOFFSET), uReg);
}

static void _uartDisableInterrupt(INT nNum, UINT32 uVal)
{
    UINT32 uReg = 0;

    if (uVal == DISABLEALLIER)
        outpw(REG_UART0_IER + (nNum * UARTOFFSET), 0);
    else
    {
        uReg = inpw(REG_UART0_IER + (nNum * UARTOFFSET));
        uReg &= ~uVal;
        outpw(REG_UART0_IER + (nNum * UARTOFFSET), uReg);
    }
}

static void _uartReceiveChars(INT nNum)
{
    //UINT32 volatile uRegLSR, uBuf = 0;
    UINT32 volatile uRegFSR, uRegALT_CSR, uRegFUN_SEL, uRegFCR, uRegLINSR, uRegISR;
    UINT32 volatile uBuf = 0;
    UINT32 volatile uOffset = nNum * UARTOFFSET;
    INT nMaxCount = 256;
    UCHAR ucChar;

    UART_BUFFER_T *dev;

    dev = (UART_BUFFER_T *) &UART_DEV[nNum];

    //uRegFSR = inpw(REG_UART0_FSR+(nNum * UARTOFFSET));
    uRegFUN_SEL = inpw(REG_UART0_FUN_SEL + uOffset);

    do
    {
        uRegFSR = inpw(REG_UART0_FSR + uOffset);
        uRegLINSR = inpw(REG_UART0_LIN_SR + uOffset);
        uRegISR = inpw(REG_UART0_ISR + uOffset);
        ucChar = inpb(REG_UART0_RBR + uOffset);

        if ((uRegFSR & UART_FSR_RS485_ADD_DETF_Msk) && (uRegFUN_SEL == 0x3))
        {
            uRegALT_CSR = inpw(REG_UART0_ALT_CSR + (nNum * UARTOFFSET));
            uRegFCR = inpw(REG_UART0_FCR + (nNum * UARTOFFSET));
            if (uRegALT_CSR & UART_ALT_CSR_RS485_NMM_Msk)
            {
                if (ucChar == (uRegALT_CSR >> UART_ALT_CSR_ADDR_MATCH_Pos))
                {
                    uRegFCR &= ~UART_FCR_RX_DIS_Msk;  /* Enable RS485 RX */
                    outpw((REG_UART0_FCR + (nNum * UARTOFFSET)), uRegFCR);
                }
                else
                {
                    uRegFCR |= UART_FCR_RX_DIS_Msk;  /* Disable RS485 RX */
                    uRegFCR |= UART_FCR_RFR_Msk;  /* Clear data from RX FIFO */
                    outpw((REG_UART0_FCR + (nNum * UARTOFFSET)), uRegFCR);
                    break;
                }
            }
        }


        uBuf = _uartRxBufGetNextOne(nNum, dev->uUartRxTail);
        if (uBuf == dev->uUartRxHead)  /* Rx buffer full */
        {
            //ucChar = inpb(REG_UART0_RBR+(nNum * UARTOFFSET));

            if (_uart_cHWRXStopped)
                U1DEBUG("[%d] buf full!\n", nNum);

            break;
        }

        //ucChar = inpb(REG_UART0_RBR+(nNum * UARTOFFSET));

        dev->pucUartRxBuf[dev->uUartRxTail] = ucChar;

        /* Check LSR for BII, FEI, PEI, OEI */
        dev->pucUARTFlag[dev->uUartRxTail] = 0;

        if (uRegFSR & UART_FSR_BIF_Msk)
        {
            dev->pucUARTFlag[dev->uUartRxTail] = UART_FSR_BIF_Msk;
            U1DEBUG("BIF!\n");
        }
        else if (uRegFSR & UART_FSR_FEF_Msk)
        {
            dev->pucUARTFlag[dev->uUartRxTail] = UART_FSR_FEF_Msk;
            U1DEBUG("FEF!\n");
        }
        else if (uRegFSR & UART_FSR_PEF_Msk)
        {
            dev->pucUARTFlag[dev->uUartRxTail] = UART_FSR_PEF_Msk;
            U1DEBUG("PEF!\n");
        }
        else if (uRegFSR & UART_FSR_RX_OVER_IF_Msk)
        {
            dev->pucUARTFlag[dev->uUartRxTail] = UART_FSR_RX_OVER_IF_Msk;
            U1DEBUG("OVER_IF!\n");
        }
        else if (uRegFSR & UART_FSR_RS485_ADD_DETF_Msk)
        {
            dev->pucUARTFlag[dev->uUartRxTail] = UART_FSR_RS485_ADD_DETF_Msk;
            U1DEBUG("RS485_ADD_DET_IF!\n");
        }

        if (uRegFUN_SEL == 0x1)
        {
            if (uRegISR & UART_ISR_LIN_RX_BREAK_IF_Msk)
            {
                dev->pucLINFlag[dev->uUartRxTail] = uRegLINSR;

                // Clear ISR and LIN Status
                outpw(REG_UART0_ISR, UART_ISR_LIN_RX_BREAK_IF_Msk);
                outpw(REG_UART0_LIN_SR, 0x30F);
            }
        }

        dev->uUartRxTail = _uartRxBufGetNextOne(nNum, dev->uUartRxTail);

        /* overrun error is special case, H/W ignore the character */
        if (uRegFSR & UART_FSR_RX_OVER_IF_Msk)
        {
            dev->pucUARTFlag[dev->uUartRxTail] = UART_FSR_RX_OVER_IF_Msk;
            dev->uUartRxTail = _uartRxBufGetNextOne(nNum, dev->uUartRxTail);
        }

        uRegFSR = inpw(REG_UART0_FSR + (nNum * UARTOFFSET));
    }
    while ((!(uRegFSR & UART_FSR_RX_EMPTY_Msk)) && (nMaxCount-- > 0));

}

static void _uartTransmitChars(INT nNum)
{
    UINT32 volatile i;

    UART_BUFFER_T *dev;

    dev = (UART_BUFFER_T *) &UART_DEV[nNum];

    if (dev->uUartTxHead != dev->uUartTxTail)  /* buffer is not empty */
    {
        for (i = 0; i < 8; i++)
        {
            outpw(REG_UART0_THR + (nNum * UARTOFFSET), dev->pucUartTxBuf[dev->uUartTxHead]);
            dev->uUartTxHead = _uartTxBufGetNextOne(nNum, dev->uUartTxHead);

            if (dev->uUartTxHead == dev->uUartTxTail)  /* buffer empty */
            {
                _uartDisableInterrupt(nNum, UART_IER_THRE_IEN_Msk);
                break;
            }
        }
    }
}

/*
    Call by uart1ISR().
*/
static void _uartCheckModemStatus(INT nNum)
{
    UINT32 volatile uRegMSR;
    UINT32 uOffset = nNum * UARTOFFSET;

    UART_BUFFER_T *dev;

    dev = (UART_BUFFER_T *) &UART_DEV[nNum];

    FDEBUG("\n Modem INT\n");
    uRegMSR = inpw(REG_UART0_MSR + uOffset);
    if (_uart_cHWTXStopped)
    {
        if (!(uRegMSR & 0x10))  /* CTS high, external signal is low */
        {
            _uart_cHWTXStopped = 0;
            FDEBUG("H/W flow control ...\n");

            /* 2007.11.12 modify, PT23 HHWu */
            if (dev->uUartTxHead != dev->uUartTxTail)   /* buffer is not empty */
            {
                _uartEnableInterrupt(nNum, UART_IER_THRE_IEN_Msk);  /* enable TX empty interrupt */
                FDEBUG("buf not empty, TX continued\n");
            }
        }
    }
    else
    {
        if (!(uRegMSR & 0x10))    /* CTS low, external signal is high */
        {
            _uart_cHWTXStopped = 1;
            _uartDisableInterrupt(nNum, UART_IER_THRE_IEN_Msk);  /* disable TX empty interrupt */
            FDEBUG("H/W flow control, TX stopped\n");
        }
    }
}

static INT _uartSetBaudRate(INT nNum, UART_T *val)
{
    UINT32 u32Reg;
    UINT32 uOffset = nNum * UARTOFFSET;
    UINT32 u32Baud_Div;
    UINT32 u32Clk = val->uFreq;
    UINT32 u32baudrate = val->uBaudRate;

    //if (val->uFreq > 200000000)  /* Max frequency 200MHz */
    //  return -1;

    u32Baud_Div = UART_BAUD_MODE2_DIVIDER(u32Clk, u32baudrate);

    if (u32Baud_Div > 0xFFFF)
        u32Reg = (UART_BAUD_MODE0 | UART_BAUD_MODE0_DIVIDER(u32Clk, u32baudrate));
    else
        u32Reg = (UART_BAUD_MODE2 | u32Baud_Div);

    outpw(REG_UART0_BAUD + uOffset, u32Reg);

    return 0;
}

static void _uartInstallISR(UINT8 ucNum)
{
    UART_BUFFER_T *dev;

    IRQn_Type IRQ;

    dev = (UART_BUFFER_T *) &UART_DEV[ucNum];

    if (ucNum == UART0)
    {
        IRQ = UART0_IRQn;
        dev->pvUartVector = sysInstallISR((IRQ_LEVEL_1 | HIGH_LEVEL_SENSITIVE), IRQ, (PVOID)uart0ISR);
    }
    else if (ucNum == UART1)
    {
        IRQ = UART1_IRQn;
        dev->pvUartVector = sysInstallISR((IRQ_LEVEL_1 | HIGH_LEVEL_SENSITIVE), IRQ, (PVOID)uart1ISR);
    }
    else if (ucNum == UART2)
    {
        IRQ = UART2_IRQn;
        dev->pvUartVector = sysInstallISR((IRQ_LEVEL_1 | HIGH_LEVEL_SENSITIVE), IRQ, (PVOID)uart2ISR);
    }
    else if (ucNum == UART3)
    {
        IRQ = UART3_IRQn;
        dev->pvUartVector = sysInstallISR((IRQ_LEVEL_1 | HIGH_LEVEL_SENSITIVE), IRQ, (PVOID)uart3ISR);
    }
    else if (ucNum == UART4)
    {
        IRQ = UART4_IRQn;
        dev->pvUartVector = sysInstallISR((IRQ_LEVEL_1 | HIGH_LEVEL_SENSITIVE), IRQ, (PVOID)uart4ISR);
    }
    else if (ucNum == UART5)
    {
        IRQ = UART5_IRQn;
        dev->pvUartVector = sysInstallISR((IRQ_LEVEL_1 | HIGH_LEVEL_SENSITIVE), IRQ, (PVOID)uart5ISR);
    }
    else if (ucNum == UART6)
    {
        IRQ = UART6_IRQn;
        dev->pvUartVector = sysInstallISR((IRQ_LEVEL_1 | HIGH_LEVEL_SENSITIVE), IRQ, (PVOID)uart6ISR);
    }
    else if (ucNum == UART7)
    {
        IRQ = UART7_IRQn;
        dev->pvUartVector = sysInstallISR((IRQ_LEVEL_1 | HIGH_LEVEL_SENSITIVE), IRQ, (PVOID)uart7ISR);
    }
    else if (ucNum == UART8)
    {
        IRQ = UART8_IRQn;
        dev->pvUartVector = sysInstallISR((IRQ_LEVEL_1 | HIGH_LEVEL_SENSITIVE), IRQ, (PVOID)uart8ISR);
    }
    else if (ucNum == UART9)
    {
        IRQ = UART9_IRQn;
        dev->pvUartVector = sysInstallISR((IRQ_LEVEL_1 | HIGH_LEVEL_SENSITIVE), IRQ, (PVOID)uart9ISR);
    }
    else if (ucNum == UARTA)
    {
        IRQ = UART10_IRQn;
        dev->pvUartVector = sysInstallISR((IRQ_LEVEL_1 | HIGH_LEVEL_SENSITIVE), IRQ, (PVOID)uart10ISR);
    }
    else
    {
        return;
    }

    //dev->pvUartVector = sysInstallISR((IRQ_LEVEL_1 | HIGH_LEVEL_SENSITIVE), IRQ, (PVOID)pvNewISR);
    sysSetLocalInterrupt(ENABLE_IRQ);                            /* enable CPSR I bit */
    sysEnableInterrupt(IRQ);
    //DrvUART_EnableInt(TEST_PORT,(DRVUART_RLSINT|DRVUART_THREINT|DRVUART_RDAINT));


}

static BOOL _uartBUFSpaceAlloc(INT nNum)
{
    UART_BUFFER_T *dev;

    dev = (UART_BUFFER_T *) &UART_DEV[nNum];

    /* Memory allocate Tx buffer */
    dev->pucUartTxBuf = (PUINT8) malloc(UARTTXBUFSIZE[nNum] * sizeof(UINT8));
    if (dev->pucUartTxBuf == NULL)
        return FALSE;

    /* Memory allocate Rx buffer */
    dev->pucUartRxBuf = (PUINT8) malloc(UARTRXBUFSIZE[nNum] * sizeof(UINT8));
    if (dev->pucUartRxBuf == NULL)
    {
        free(dev->pucUartTxBuf);
        return FALSE;
    }

    /* Memory allocate Rx character flag */
    dev->pucUARTFlag = (PINT) malloc(UARTRXBUFSIZE[nNum] * sizeof(INT));
    if (dev->pucUARTFlag == NULL)
    {
        free(dev->pucUartTxBuf);
        free(dev->pucUartRxBuf);
        return FALSE;
    }

    /* initial memory */
    memset(dev->pucUartTxBuf, 0, UARTTXBUFSIZE[nNum] * sizeof(UINT8));
    memset(dev->pucUartRxBuf, 0, UARTRXBUFSIZE[nNum] * sizeof(UINT8));
    memset(dev->pucUARTFlag, 0, UARTRXBUFSIZE[nNum] * sizeof(INT));

    /* inital struct UART_BUFFER_STRUCT, uUartTxHead, uUartTxTail, uUartRxHead, uUartRxTail */
    dev->uUartTxHead = dev->uUartTxTail = (UINT32)NULL;
    dev->uUartRxHead = dev->uUartRxTail = (UINT32)NULL;

    return TRUE;
}

static BOOL _uartCheckTxBufSpace(INT nNum, UINT32 uHead, UINT32 uTail, UINT32 uLen)
{
    UINT32 uBuf;

    uBuf = _uartTxBufGetNextOne(nNum, uTail);
    if (uBuf == uHead)  /* Tx buffer full */
        return FALSE;

    if (uHead == uTail) /* Tx buffer empty */
        return TRUE;

    if (uTail > uHead)
    {
        if (uLen >= (UARTTXBUFSIZE[nNum] - (uTail - uHead))) /* 2007.10.29 fix pointer bug, PT23 HHWu */
            return FALSE;  /* Tx buffer space isn't enough */
        else
            return TRUE;
    }
    else
    {
        /* case: uTail < uHead */
        if (uLen >= (uHead - uTail)) /* 2007.10.29 fix pointer bug, PT23 HHWu */
            return FALSE;  /* Tx buffer space isn't enough */
        else
            return TRUE;
    }

    //return TRUE;
}

static INT32 _uartReadRxBuf(INT nNum, PUINT8 pucBuf, UINT32 uLen)
{
    UINT32 i;
    UINT32 uOffset = nNum * UARTOFFSET;
    UART_BUFFER_T *dev;

    dev = (UART_BUFFER_T *) &UART_DEV[nNum];

    if (dev->bIsUseUARTRxInt == TRUE)
    {

        // disable Rx interrupt ...

        if (dev->uUartRxHead == dev->uUartRxTail)
            return 0;

        for (i = uLen ; i > 0 ; i--)
        {
            *pucBuf++ = dev->pucUartRxBuf[dev->uUartRxHead];
            dev->uUartRxHead = _uartRxBufGetNextOne(nNum, dev->uUartRxHead);

            if (dev->uUartRxHead == dev->uUartRxTail)
                break;
        }

        uLen = uLen - i + 1;
    }
    else     /* pooling mode */
    {
        for (i = 0 ; i < uLen; i++)
        {
            while (!(inpw(REG_UART0_FSR + uOffset) & UART_FSR_RX_EMPTY_Msk));
            *pucBuf++ = inpb(REG_UART0_RBR + uOffset);
        }
    }

    return (uLen);
}

static void _uartWriteTxBuf(INT nNum, PUINT8 pucBuf, UINT32 uLen)
{
    UINT32 i;
    UINT32 uOffset = nNum * UARTOFFSET;
    UART_BUFFER_T *dev;

    dev = (UART_BUFFER_T *) &UART_DEV[nNum];

    /* Check interrupt or polling mode first */
    if (dev->bIsUseUARTTxInt == TRUE)
    {
        while (uLen--)
        {
            dev->pucUartTxBuf[dev->uUartTxTail] = *pucBuf++;
            dev->uUartTxTail = _uartTxBufGetNextOne(nNum, dev->uUartTxTail);
        }

        if (!(inpw(REG_UART0_IER + uOffset) & UART_IER_THRE_IEN_Msk)) /* Enable Tx empty interrupt */
            _uartEnableInterrupt(nNum, UART_IER_THRE_IEN_Msk);
    }
    else     /* pooling mode */
    {
        for (i = 0 ; i < uLen ; i++)
        {
            /* Wait until the transmitter buffer is empty */
            while (!(inpw(REG_UART0_FSR + uOffset) & UART_FSR_TE_FLAG_Msk));
            outpw(REG_UART0_THR + uOffset, *pucBuf++);
        }
    }
}

static INT _uartConfigureUART(PVOID pvParam)
{
    INT retval;
    BOOL bIsMemoryAllocOk;
    UINT32 u32Reg;
    UINT32 uOffset;
    UINT32 uNum = 0;

    UART_T *param = (UART_T *) pvParam;

    uOffset = param->ucUartNo * UARTOFFSET;
    uNum = param->ucUartNo;

    /* Check UART channel */
    if (uNum > UARTA)
        return UART_ERR_CHANNEL_INVALID;

    /* Check the supplied parity */
    if ((param->ucParity != NU_PARITY_NONE) &&
            (param->ucParity != NU_PARITY_EVEN) &&
            (param->ucParity != NU_PARITY_ODD)  &&
            (param->ucParity != (NU_PARITY_ODD | NU_PARITY_STICK)) &&
            (param->ucParity != (NU_PARITY_EVEN | NU_PARITY_STICK)))
        return UART_ERR_PARITY_INVALID;

    /* Check the supplied number of data bits */
    if ((param->ucDataBits != NU_DATA_BITS_5) &&
            (param->ucDataBits != NU_DATA_BITS_6) &&
            (param->ucDataBits != NU_DATA_BITS_7) &&
            (param->ucDataBits != NU_DATA_BITS_8))
        return UART_ERR_DATA_BITS_INVALID;

    /* Check the supplied number of stop bits */
    if ((param->ucStopBits != NU_STOP_BITS_1) &&
            (param->ucStopBits != NU_STOP_BITS_2))
        return UART_ERR_STOP_BITS_INVALID;

    /* Check the supplied number of trigger level bytes */
    if ((param -> ucUartNo == UART1) || (param -> ucUartNo == UART2) || (param -> ucUartNo == UART4) ||
            (param -> ucUartNo == UART6) || (param -> ucUartNo == UART8) || (param -> ucUartNo == UARTA))
    {
        /* UART1,2,4,6,8,A */
        if ((param->ucRxTriggerLevel != UART_FCR_RFITL_1BYTE)   &&
                (param->ucRxTriggerLevel != UART_FCR_RFITL_4BYTES)  &&
                (param->ucRxTriggerLevel != UART_FCR_RFITL_8BYTES)  &&
                (param->ucRxTriggerLevel != UART_FCR_RFITL_14BYTES) &&
                (param->ucRxTriggerLevel != UART_FCR_RFITL_30BYTES) &&
                (param->ucRxTriggerLevel != UART_FCR_RFITL_46BYTES) &&
                (param->ucRxTriggerLevel != UART_FCR_RFITL_62BYTES))
            return UART_ERR_TRIGGERLEVEL_INVALID;
    }
    else
    {
        /* UART0,3,5,7,9 */
        if ((param->ucRxTriggerLevel != UART_FCR_RFITL_1BYTE)  &&
                (param->ucRxTriggerLevel != UART_FCR_RFITL_4BYTES) &&
                (param->ucRxTriggerLevel != UART_FCR_RFITL_8BYTES) &&
                (param->ucRxTriggerLevel != UART_FCR_RFITL_30BYTES))
            return UART_ERR_TRIGGERLEVEL_INVALID;
    }

    /* Enable UART clock */
    if (param->ucUartNo < ALLCHANNEL)
    {
        outpw(REG_CLK_PCLKEN0, inpw(REG_CLK_PCLKEN0) | (1 << (16 + param->ucUartNo)));
    }

    /* Reset TX/RX FIFOs */
    u32Reg = inpw(REG_UART0_FCR + uOffset);
    outpw(REG_UART0_FCR + uOffset, (u32Reg | (0x03 << 1)));

    /* Setup baud rate */
    retval = _uartSetBaudRate(param->ucUartNo, param);
    if (retval < 0)
        return UART_ERR_SET_BAUDRATE_FAIL;

    /* Setup parity, data bits, and stop bits */
    outpw(REG_UART0_LCR + uOffset, (param->ucParity | param->ucDataBits | param->ucStopBits));

    /* Setup Rx time out value */
    outpw(REG_UART0_TOR + uOffset, 0x80 + 0x20);

    /* Setup FIFO trigger level */
    outpw(REG_UART0_FCR + uOffset, param->ucRxTriggerLevel);

    /* only exec once unless call uartClose() */
    if (UART_DEV[param->ucUartNo].bIsUARTInitial == FALSE)
    {
        /* Configure GPIO function */
        //_uartConfigureGPIO(param->ucUartNo);

        /* Allocate Tx, Rx buffer */
        bIsMemoryAllocOk = _uartBUFSpaceAlloc(param->ucUartNo);
        if (bIsMemoryAllocOk == FALSE)
            return UART_ERR_ALLOC_MEMORY_FAIL;

        /* Hook UART interrupt service routine */
        _uartInstallISR(param->ucUartNo);

        /* Enable Rx interrupt */
        if (UART_DEV[param->ucUartNo].bIsUseUARTRxInt == TRUE)
            _uartEnableInterrupt(param->ucUartNo, UART_IER_RDA_IEN_Msk);

    }

    UART_DEV[param->ucUartNo].bIsUARTInitial = TRUE;  /* it's important to set TRUE */
    return 0;
}

static INT _uartPerformIrDA(INT nNum, UINT32 uCmd, UINT32 uCmd1)  /* UART2 only */
{
    UINT32 uOffset = nNum * UARTOFFSET;
    UINT32 baud;

    switch (uCmd)
    {
    case ENABLEIrDA:
        //_uart_bIsPerformIrDA = TRUE;

        baud = inpw(REG_UART0_BAUD + uOffset);
        baud = baud & (0x0000ffff);
        baud = baud + 2;
        baud = baud / 16;
        baud = baud - 2;

        outpw(REG_UART0_BAUD + uOffset, baud);

        if (uCmd1 == IrDA_TX)
            outpw(REG_UART0_IRCR + uOffset, UART_IRCR_TX_SELECT_Msk);
        else if (uCmd1 == IrDA_RX)
            outpw(REG_UART0_IRCR + uOffset, 0x0);
        else
            return UART_ERR_IrDA_COMMAND_INVALID;

        outpw(REG_UART0_FUN_SEL + uOffset, 0x2); // Select IrDA mode

        break;

    case DISABLEIrDA:
        //_uart_bIsPerformIrDA = FALSE;
        outpw(REG_UART0_IRCR + uOffset, 0x40); /* Set default value, INV_TX set 0, INV_RX set 1 */
        outpw(REG_UART0_FUN_SEL + uOffset, 0x0); // Select UART mode
        break;

    default:
        return UART_ERR_IrDA_COMMAND_INVALID;
    }

    return 0;
}

/*
    Remark:
    1. LCR & LSR aren't support yet.
*/
static INT _uartGetRegisterValue(INT nNum, PVOID pvReg)
{
    INT nCnt = 0;
    UINT32 uOffset = nNum * UARTOFFSET;

    UART_REGISTER_T *reg = (UART_REGISTER_T *) pvReg;

    memset(reg, 0, sizeof(UART_REGISTER_T));

    /* Read IER */
    reg->uUartReg[nCnt][0] = REG_UART0_IER + uOffset;
    reg->uUartReg[nCnt++][1] = inpw(REG_UART0_IER + uOffset);

    /* Read FCR */
    reg->uUartReg[nCnt][0] = REG_UART0_FCR + uOffset;
    reg->uUartReg[nCnt++][1] = inpw(REG_UART0_FCR + uOffset);

    /* Read LCR */
    reg->uUartReg[nCnt][0] = REG_UART0_LCR + uOffset;
    reg->uUartReg[nCnt++][1] = inpw(REG_UART0_LCR + uOffset);

    /* Read MCR, MSR */
    reg->uUartReg[nCnt][0] = REG_UART0_MCR + uOffset;
    reg->uUartReg[nCnt++][1] = inpw(REG_UART0_MCR + uOffset);
    reg->uUartReg[nCnt][0] = REG_UART0_MSR + uOffset;
    reg->uUartReg[nCnt++][1] = inpw(REG_UART0_MSR + uOffset);

    /* Read FSR */
    reg->uUartReg[nCnt][0] = REG_UART0_FSR + uOffset;
    reg->uUartReg[nCnt++][1] = inpw(REG_UART0_FSR + uOffset);

    /* Read ISR */
    reg->uUartReg[nCnt][0] = REG_UART0_ISR + uOffset;
    reg->uUartReg[nCnt++][1] = inpw(REG_UART0_ISR + uOffset);

    /* Read TOR */
    reg->uUartReg[nCnt][0] = REG_UART0_TOR + uOffset;
    reg->uUartReg[nCnt++][1] = inpw(REG_UART0_TOR + uOffset);

    /* Read BAUD */
    reg->uUartReg[nCnt][0] = REG_UART0_BAUD + uOffset;
    reg->uUartReg[nCnt++][1] = inpw(REG_UART0_BAUD + uOffset);

    /* Read IRCR */
    reg->uUartReg[nCnt][0] = REG_UART0_IRCR + uOffset;
    reg->uUartReg[nCnt++][1] = inpw(REG_UART0_IRCR + uOffset);

    /* Read ALT_CSR */
    reg->uUartReg[nCnt][0] = REG_UART0_ALT_CSR + uOffset;
    reg->uUartReg[nCnt++][1] = inpw(REG_UART0_ALT_CSR + uOffset);

    /* Read FUN_SEL */
    reg->uUartReg[nCnt][0] = REG_UART0_FUN_SEL + uOffset;
    reg->uUartReg[nCnt++][1] = inpw(REG_UART0_FUN_SEL + uOffset);

    /* Read LIN_CTL */
    reg->uUartReg[nCnt][0] = REG_UART0_LIN_CTL + uOffset;
    reg->uUartReg[nCnt++][1] = inpw(REG_UART0_LIN_CTL + uOffset);

    /* Read LIN_SR */
    reg->uUartReg[nCnt][0] = REG_UART0_LIN_SR + uOffset;
    reg->uUartReg[nCnt++][1] = inpw(REG_UART0_LIN_SR + uOffset);

    return (nCnt);
}

/// @endcond HIDDEN_SYMBOLS

/** @addtogroup N9H30_UART_EXPORTED_FUNCTIONS UART Exported Functions
  @{
*/

/**
  * @brief    The function is used to initial device struct parameters.
  *
  * @return   0
  */
INT uartInit(void)
{
    INT i;

    /* Initial UART_BUFFER_T struct */
    for (i = 0; i < UART_NUM ; i++)
        UART_DEV[i].bIsUARTInitial = FALSE;

    for (i = 0; i < UART_NUM ; i++)
        UART_DEV[i].bIsUseUARTTxInt = TRUE;

    for (i = 0; i < UART_NUM ; i++)
        UART_DEV[i].bIsUseUARTRxInt = TRUE;

    return 0;
}

/**
  * @brief    The function is used to config UART channel.
  *
  * @param[in]    uart: UART Port. ( UART0 / UART1 / UART2 / UART3 / UART 4 /UART 5 /
  *                                 UART6 / UART7 / UART8 / UART9 / UARTA )
  *
  * @return   UART_EIO: UART config Fail
  *           Successful: UART config success
  */
INT uartOpen(PVOID uart)
{
    INT nValue = 0;
    UART_T *dev = (UART_T *) uart;

    if ((nValue = _uartConfigureUART(uart)) < 0)
    {
        if (nValue != UART_ERR_CHANNEL_INVALID)
            UART_DEV[dev->ucUartNo].nErrno = nValue;

        return UART_EIO;
    }
    else
        UART_DEV[dev->ucUartNo].nErrno = 0;

    return Successful;
}

/**
  * @brief    The function is used to read RX FIFO returned data or RX driver buffer.
  *
  * @param[in]    nNum: UART Port. ( UART0 / UART1 / UART2 / UART3 / UART 4 /UART 5 /
  *                                 UART6 / UART7 / UART8 / UART9 / UARTA )
  * @param[out]   pucBuf: The buffer to receive.
  *
  * @param[in]    uLen: The the read bytes number of data.
  *
  * @return   UART_EIO: UART read Fail
  *           DataLength: Receive byte count
  */
INT32 uartRead(INT nNum, PUINT8 pucBuf, UINT32 uLen)
{
    UART_BUFFER_T *dev;
    INT32 DataLength;

    //if((nNum < UART0) || (nNum > UART4))
    //  return UART_ENODEV;

    dev = (UART_BUFFER_T *) &UART_DEV[nNum];

    /* Check UART initial status */
    if (dev->bIsUARTInitial == FALSE)
        return UART_EIO;

    /* Check uLen value */
    if ((uLen > UARTRXBUFSIZE[nNum]) || (uLen == 0))
        return UART_EIO;

    DataLength = _uartReadRxBuf(nNum, pucBuf, uLen);

    return (DataLength);

}


/**
  * @brief    The function is used to write data to TX FIFO directly or TX driver buffer.
  *
  * @param[in]    nNum: UART channel. ( UART0 / UART1 / UART2 / UART3 / UART 4 /UART 5 /
  *                                     UART6 / UART7 / UART8 / UART9 / UARTA )
  * @param[out]   pucBuf: Transmit buffer pointer.
  *
  * @param[in]    uLen: Transmit buffer length.
  *
  * @return   UART_EIO: UART transmit Fail
  *           uLen: write length on success
  */
INT32 uartWrite(INT nNum, PUINT8 pucBuf, UINT32 uLen)
{
    BOOL bIsTxBufEnough;

    UART_BUFFER_T *dev;

    //if((nNum < UART0) || (nNum > UART4))
    //  return UART_ENODEV;

    dev = (UART_BUFFER_T *) &UART_DEV[nNum];
    dev->nErrno = 0;

    /* Check UART initial status */
    if (dev->bIsUARTInitial == FALSE)
        return UART_EIO;

    /* Check uLen value */
    if ((uLen > UARTWRITESIZE) || (uLen == 0))
        return UART_EIO;

    /* Check UART Tx buffer */
    if (dev->bIsUseUARTTxInt == TRUE)
    {
        bIsTxBufEnough = _uartCheckTxBufSpace(nNum, dev->uUartTxHead, dev->uUartTxTail, uLen);
        if (bIsTxBufEnough == FALSE)
        {
            //sysprintf("Tx buf not enough\n");
            dev->nErrno = UART_ERR_TX_BUF_NOT_ENOUGH;
            return UART_EIO;
        }
    }

    /* Move data to UART Tx buffer then transmit */
    _uartWriteTxBuf(nNum, pucBuf, uLen);

    return (uLen);
}

/**
  * @brief    Support some UART driver commands for application.
  *
  * @param[in]    nNum: UART channel. ( UART0 / UART1 / UART2 / UART3 / UART 4 /UART 5 /
  *                                     UART6 / UART7 / UART8 / UART9 / UARTA )
  *
  * @param[in]    uCmd: Command.
  *
  * @param[in]    uArg0: Arguments for the command.
  *
  * @param[in]    uArg1: Arguments for the command.
  *
  * @return   UART_ENODEV: UART channel out of range
  *           UART_EIO: No activated or argument error or configure UART fail
  *           Successful: Success
  */
INT uartIoctl(INT nNum, UINT32 uCmd, UINT32 uArg0, UINT32 uArg1)
{
    INT32 retval;
    UINT32 uReg;
    UINT32 uOffset = nNum * UARTOFFSET;

    UART_BUFFER_T *dev;

    if ((nNum < UART0) || (nNum > UARTA))
        return UART_ENODEV;

    dev = (UART_BUFFER_T *) &UART_DEV[nNum];

    /* Check UART initial status */
    if (dev->bIsUARTInitial == FALSE)
    {
        if ((uCmd != UART_IOC_GETERRNO) &&
                (uCmd != UART_IOC_GETUARTREGISTERVALUE))
            return UART_EIO;
    }

    switch (uCmd)
    {
    case UART_IOC_SETTXMODE:
        if (uArg0 == UARTINTMODE)
            dev->bIsUseUARTTxInt = TRUE;
        else if (uArg0 == UARTPOLLMODE)
            dev->bIsUseUARTTxInt = FALSE;
        else
        {
            dev->nErrno = UART_ERR_OPERATE_MODE_INVALID;
            return UART_EIO;
        }

        break;

    case UART_IOC_SETRXMODE:
        if (uArg0 == UARTINTMODE)
        {
            dev->bIsUseUARTRxInt = TRUE;
            _uartEnableInterrupt(nNum, UART_IER_RDA_IEN_Msk);
        }
        else if (uArg0 == UARTPOLLMODE)
        {
            dev->bIsUseUARTRxInt = FALSE;
            _uartDisableInterrupt(nNum, UART_IER_RDA_IEN_Msk);
        }
        else
        {
            dev->nErrno = UART_ERR_OPERATE_MODE_INVALID;
            return UART_EIO;
        }

        break;

    case UART_IOC_GETRECCHARINFO:  // ..... not test yet
        memcpy((PVOID) uArg0, (PVOID) dev, sizeof(struct UART_BUFFER_STRUCT));
        break;

    case UART_IOC_SETUARTPARAMETER:  // ..... not test yet
        if ((retval = _uartConfigureUART((PVOID) uArg0)) < 0)
        {
            dev->nErrno = retval;
            return UART_EIO;
        }

        break;

    case UART_IOC_PERFORMIrDA:

        if ((retval = _uartPerformIrDA(nNum, uArg0, uArg1)) < 0)
        {
            dev->nErrno = retval;
            return UART_EIO;
        }

        break;

    case UART_IOC_GETUARTREGISTERVALUE:
        return (_uartGetRegisterValue(nNum, (PVOID) uArg0));
    //break;

    case UART_IOC_GETERRNO:
        *(PUINT32)uArg0 = dev->nErrno;
        break;

    case UART_IOC_SETMODEMINTERRUPT:

        if (uArg0 == UART_ENABLE_MODEM_INT)
            _uartEnableInterrupt(nNum, UART_IER_MODEM_IEN_Msk);
        else if (uArg0 == UART_DISABLE_MODEM_INT)
            _uartDisableInterrupt(nNum, UART_IER_MODEM_IEN_Msk);
        else
            return UART_EIO;

        break;

    case UART_IOC_GETCTSSTATE:

        if (nNum == UART1)
        {
            *(PUINT32)uArg0 = _uart_cCTSState1;                        /* CTS state */
            _uart_cCTSState1 = 0;
        }
        else if (nNum == UART2)
        {
            *(PUINT32)uArg0 = _uart_cCTSState2;                        /* CTS state */
            _uart_cCTSState2 = 0;
        }
        else if (nNum == UART3)
        {
            *(PUINT32)uArg0 = _uart_cCTSState3;                        /* CTS state */
            _uart_cCTSState3 = 0;
        }
        else if (nNum == UART4)
        {
            *(PUINT32)uArg0 = _uart_cCTSState4;                        /* CTS state */
            _uart_cCTSState4 = 0;
        }
        else if (nNum == UART5)
        {
            *(PUINT32)uArg0 = _uart_cCTSState5;                        /* CTS state */
            _uart_cCTSState5 = 0;
        }
        else if (nNum == UART6)
        {
            *(PUINT32)uArg0 = _uart_cCTSState6;                        /* CTS state */
            _uart_cCTSState6 = 0;
        }
        else if (nNum == UART7)
        {
            *(PUINT32)uArg0 = _uart_cCTSState7;                        /* CTS state */
            _uart_cCTSState7 = 0;
        }
        else if (nNum == UART8)
        {
            *(PUINT32)uArg0 = _uart_cCTSState8;                        /* CTS state */
            _uart_cCTSState8 = 0;
        }
        else if (nNum == UART9)
        {
            *(PUINT32)uArg0 = _uart_cCTSState9;                        /* CTS state */
            _uart_cCTSState9 = 0;
        }
        else if (nNum == UARTA)
        {
            *(PUINT32)uArg0 = _uart_cCTSState10;                        /* CTS state */
            _uart_cCTSState10 = 0;
        }

        *(PUINT32)uArg1 = (inpw(REG_UART0_MSR + uOffset) & (1 << 4)) >> 4; /* get CTS# value */

        break;

    case UART_IOC_SETRTSSIGNAL:

        if (uArg0 == UART_RTS_HIGH)     /* set RTS signal high */
            outpw(REG_UART0_MCR + uOffset, inpw(REG_UART0_MCR + uOffset) & ~0x02);
        else if (uArg0 == UART_RTS_LOW) /* set RTS signal low  */
            outpw(REG_UART0_MCR + uOffset, inpw(REG_UART0_MCR + uOffset) | 0x02);
        else
            return UART_EIO;

        break;

    case UART_IOC_SETINTERRUPT:
        if (uArg0 == 1)      /* enable interrupt  */
            _uartEnableInterrupt(nNum, uArg1);
        else if (uArg0 == 0) /* disable interrupt */
            _uartDisableInterrupt(nNum, uArg1);
        else
            return UART_EIO;

        break;

    case UART_IOC_SETBREAKCONTROL:
        uReg = inpw(REG_UART0_LCR + uOffset);
        if (uArg0 == 1)      /* set break contorl bit  */
        {
            uReg |= UART_LCR_BCB_Msk;
            outpw(REG_UART0_LCR + uOffset, uReg);
        }
        else if (uArg0 == 0)    /* clear break contorl bit */
        {
            uReg &= ~UART_LCR_BCB_Msk;
            outpw(REG_UART0_LCR + uOffset, uReg);
        }
        else
            return UART_EIO;

        break;

    case UART_IOC_GETBIISTATE:
        switch (nNum)
        {
        case UART0:
            *(PUINT32)uArg0 = _uart_cBIIState_0;
            break;
        case UART1:
            *(PUINT32)uArg0 = _uart_cBIIState_1;
            break;
        case UART2:
            *(PUINT32)uArg0 = _uart_cBIIState_2;
            break;
        case UART3:
            *(PUINT32)uArg0 = _uart_cBIIState_3;
            break;
        case UART4:
            *(PUINT32)uArg0 = _uart_cBIIState_4;
            break;
        case UART5:
            *(PUINT32)uArg0 = _uart_cBIIState_5;
            break;
        case UART6:
            *(PUINT32)uArg0 = _uart_cBIIState_6;
            break;
        case UART7:
            *(PUINT32)uArg0 = _uart_cBIIState_7;
            break;
        case UART8:
            *(PUINT32)uArg0 = _uart_cBIIState_8;
            break;
        case UART9:
            *(PUINT32)uArg0 = _uart_cBIIState_9;
            break;
        case UARTA:
            *(PUINT32)uArg0 = _uart_cBIIState_10;
            break;

        default:
            break;
        }
        break;

    /* H/W S/W flow control function */
    case UART_IOC_ENABLEHWFLOWCONTROL:

        /* H/W & S/W are alternative */
        if (_uart_cFlowControlMode == SWFLOWCONTROL)
            return UART_EIO;

        _uart_cFlowControlMode = HWFLOWCONTROL;

        /* Implement H/W flow control on TX & RX interrupt mode. */
        //dev->bIsUseUARTTxInt = TRUE;
        //dev->bIsUseUARTRxInt = TRUE;
        _uartEnableInterrupt(nNum, UART_IER_RDA_IEN_Msk);

        /*
            Set up RTS mechanism.
            In uartReceiveChars(), if uRecCnt >= _uart_nMaxRxBuf then set RTS high to stop RX.
            In uartReadRxBuf(), if uRecCnt <= _uart_nMinRxBuf then set RTS low to re-start RX.
        */
        //_uart_nMaxRxBuf = (UARTRXBUFSIZE[nNum] * 3) / 4;
        //_uart_nMinRxBuf = UARTRXBUFSIZE[nNum] / 2;
        //FDEBUG("max[%d] min[%d]\n", _uart_nMaxRxBuf, _uart_nMinRxBuf);

        /* Set RTS high level trigger */
        outpw(REG_UART0_MCR + uOffset, (inpw(REG_UART0_MCR + uOffset) | UART_RTS_IS_HIGH_LEV_TRG));
        /* Set RTS high level trigger */
        outpw(REG_UART0_MSR + uOffset, (inpw(REG_UART0_MSR + uOffset) | UART_CTS_IS_HIGH_LEV_TRG));

        /* Set Auto CTS/RTS */
        outpw(REG_UART0_IER + uOffset, inpw(REG_UART0_IER + uOffset) | (0x3 << 12));

        /* Enable MODEM status interrupt */
        //_uartEnableInterrupt(nNum, UART_IER_MODEM_IEN_Msk);

        /*
            Maintain H/W flow control flag by read Modem Status Register.
            If CTS high, stop TX.
            If CTS low, start TX.
        */
        //if( inpw(REG_UART0_MSR+uOffset) & 0x10 )  /* CTS external signal is low  */
        //  _uart_cHWTXStopped = 0;       /* TX started                  */
        //else                              /* CTS external signal is high */
        //  _uart_cHWTXStopped = 1;       /* TX stopped                  */

        /* Set RTS as logic 0, RX re-start */
        //outpb(REG_UART0_MCR+uOffset, inpb(REG_UART0_MCR+uOffset) | 0x02);  /* set RTS signal low  */
        //_uart_cHWRXStopped = 0;  // RX started
        break;

    case UART_IOC_DISABLEHWFLOWCONTROL:

        /* Disable MODEM status interrupt */
        _uartDisableInterrupt(nNum, UART_IER_MODEM_IEN_Msk);
        _uart_cFlowControlMode = 0;
        _uart_cHWTXStopped = 0;
        _uart_cHWRXStopped = 0;
        break;

    case UART_IOC_FLUSH_TX_BUFFER:
        dev->uUartTxTail = 0;
        dev->uUartTxHead = 0;
        break;

    case UART_IOC_FLUSH_RX_BUFFER:
        dev->uUartRxTail = 0;
        dev->uUartRxHead = 0;
        break;

    case UART_IOC_SET_RS485_MODE:
        outpw((REG_UART0_FUN_SEL + uOffset), 0x3);
        outpw((REG_UART0_MCR + uOffset), 0x0);
        outpw((REG_UART0_LCR + uOffset), (UART_LCR_SPE_Msk | UART_LCR_EPE_Msk | UART_LCR_PBE_Msk | (0x3 << UART_LCR_WLS_Pos)));
        outpw((REG_UART0_ALT_CSR + uOffset), uArg0 | (uArg1 << UART_ALT_CSR_ADDR_MATCH_Pos));
        break;

    case UART_IOC_SEND_RS485_ADDRESS:

        while (!((inpw(REG_UART0_FSR + uOffset)) & UART_FSR_TE_FLAG_Msk));
        uReg = inpw(REG_UART0_LCR + uOffset);
        outpw((REG_UART0_LCR + uOffset), (UART_LCR_SPE_Msk | UART_LCR_PBE_Msk | (0x3 << UART_LCR_WLS_Pos)));
        outpw((REG_UART0_THR + uOffset), uArg0);
        while (!((inpw(REG_UART0_FSR + uOffset)) & UART_FSR_TE_FLAG_Msk));

        outpw((REG_UART0_LCR + uOffset), uReg);

        break;

    case UART_IOC_SET_RS485_RXOFF:
        uReg = inpw(REG_UART0_FCR + uOffset);
        if (uArg0 == 1)
            uReg |= UART_FCR_RX_DIS_Msk;
        else
            uReg &= ~UART_FCR_RX_DIS_Msk;

        outpw((REG_UART0_FCR + uOffset), uReg);

        break;

    case UART_IOC_SET_ALTCTL_REG:

        outpw((REG_UART0_ALT_CSR + uOffset), uArg0);

        break;

    case UART_IOC_GET_ALTCTL_REG:

        *(PUINT32)uArg0 = inpw(REG_UART0_ALT_CSR + uOffset);

        break;

    case UART_IOC_SET_LIN_MODE:

        outpw((REG_UART0_FUN_SEL + uOffset), 0x1); // Select LIN function

        /* Select LIN function setting : Tx enable, Rx enable and break field length */
        uReg = inpw(REG_UART0_ALT_CSR + uOffset);
        uReg &= ~(UART_ALT_CSR_LIN_TX_EN_Msk | UART_ALT_CSR_LIN_RX_EN_Msk | UART_ALT_CSR_UA_LIN_BKFL_Msk);
        uReg |= (uArg0 | (uArg1 << UART_ALT_CSR_UA_LIN_BKFL_Pos));
        outpw((REG_UART0_ALT_CSR + uOffset), uReg);

        break;

    default:
        return UART_ENOTTY;
    }

    return Successful;
}

/**
  * @brief    Release memory resource, disable interrupt.
  *
  * @param[in]    nNum: UART channel. ( UART0 / UART1 / UART2 / UART3 / UART 4 /UART 5 /
  *                                     UART6 / UART7 / UART8 / UART9 / UARTA )
  *
  * @return   UART_ENODEV: UART channel out of range
  *           UART_EIO: No activated
  *           Successful: Success
  */
INT32 uartRelease(INT nNum)
{
    UART_BUFFER_T *dev;

    if ((nNum < UART0) || (nNum > UARTA))
        return UART_ENODEV;

    dev = (UART_BUFFER_T *) &UART_DEV[nNum];

    /* Check UART initial status */
    if (dev->bIsUARTInitial == FALSE)
        return UART_EIO;

    /* Disable all interrupt of the specific UART */
    _uartDisableInterrupt(nNum, DISABLEALLIER);

    /* Free memory */
    free(dev->pucUartTxBuf);
    free(dev->pucUartRxBuf);
    free(dev->pucUARTFlag);

    /* Initial parameter */
    dev->bIsUARTInitial = FALSE;  /* it's important */

    return Successful;
}

/*@}*/ /* end of group N9H30_UART_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_UART_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */
#else
#include "N9H30.h"
#include "nu_sys.h"
#include "nu_uart.h"

/**
 *    @brief        Open and set UART function
 *
 *    @param[in]    uart            The pointer of the specified UART module.
 *    @param[in]    u32baudrate     The baudrate of UART module.
 *
 *    @return       None
 *
 *    @details      This function use to enable UART function and set baud-rate.
 */
void UART_Open(UART_T *uart, uint32_t u32baudrate)
{
    uint32_t u32UartClkSrcSel = 0ul, u32UartClkDivNum = 0ul;
    //uint32_t u32ClkTbl[4] = {XIN, LXT, ACLK, UCLK};
    uint32_t u32ClkTbl[4] = {12000000, 0, 75000000, 150000000};
    uint32_t u32Baud_Div = 0ul;

    if ((uint32_t)uart == UART0_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL4) & (0x3ul << 3)) >> 3;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL4) & (0x7ul << 5)) >> 5;
    }
    else if ((uint32_t)uart == UART1_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL4) & (0x3ul << 11)) >> 11;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL4) & (0x7ul << 13)) >> 13;
    }
    else if ((uint32_t)uart == UART2_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL4) & (0x3ul << 19)) >> 19;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL4) & (0x7ul << 21)) >> 21;
    }
    else if ((uint32_t)uart == UART3_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL4) & (0x3ul << 27)) >> 27;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL4) & (0x7ul << 29)) >> 29;
    }
    else if ((uint32_t)uart == UART4_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL5) & (0x3ul << 3)) >> 3;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL5) & (0x7ul << 5)) >> 5;
    }
    else if ((uint32_t)uart == UART5_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL5) & (0x3ul << 11)) >> 11;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL5) & (0x7ul << 13)) >> 13;
    }
    else if ((uint32_t)uart == UART6_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL5) & (0x3ul << 19)) >> 19;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL5) & (0x7ul << 21)) >> 21;
    }
    else if ((uint32_t)uart == UART7_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL5) & (0x3ul << 27)) >> 27;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL5) & (0x7ul << 29)) >> 29;
    }
    else if ((uint32_t)uart == UART8_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL6) & (0x3ul << 3)) >> 3;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL6) & (0x7ul << 5)) >> 5;
    }
    else if ((uint32_t)uart == UART9_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL6) & (0x3ul << 11)) >> 11;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL6) & (0x7ul << 13)) >> 13;
    }
    else if ((uint32_t)uart == UARTA_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL6) & (0x3ul << 19)) >> 19;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL6) & (0x7ul << 21)) >> 21;
    }

    /* Select UART function */
    uart->FUNCSEL = UART_FUNCSEL_UART;

    /* Set UART line configuration */
    uart->LINE = UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1;

    /* Set UART Rx and RTS trigger level */
    uart->FIFO &= ~(UART_FIFO_RFITL_Msk | UART_FIFO_RTSTRGLV_Msk);

    /* Get PLL clock frequency if UART clock source selection is PLL */
    if (u32UartClkSrcSel == 2ul)  // ACLK
    {
        //u32ClkTbl[u32UartClkSrcSel] = CLK_GetPLLClockFreq();
    }

    if (u32UartClkSrcSel == 3ul)  // PCLK
    {
        //u32ClkTbl[u32UartClkSrcSel] = CLK_GetPLLClockFreq();
    }

    /* Set UART baud rate */
    if (u32baudrate != 0ul)
    {
        u32Baud_Div = UART_BAUD_MODE2_DIVIDER((u32ClkTbl[u32UartClkSrcSel]) / (u32UartClkDivNum + 1ul), u32baudrate);

        if (u32Baud_Div > 0xFFFFul)
        {
            uart->BAUD = (UART_BAUD_MODE0 | UART_BAUD_MODE0_DIVIDER((u32ClkTbl[u32UartClkSrcSel]) / (u32UartClkDivNum + 1ul), u32baudrate));
        }
        else
        {
            uart->BAUD = (UART_BAUD_MODE2 | u32Baud_Div);
        }
    }
}

void UART_Close(UART_T *uart)
{
    uart->INTEN = 0ul;
}

/**
 *    @brief        Set UART line configuration
 *
 *    @param[in]    uart            The pointer of the specified UART module.
 *    @param[in]    u32baudrate     The register value of baudrate of UART module.
 *                                  If u32baudrate = 0, UART baudrate will not change.
 *    @param[in]    u32data_width   The data length of UART module.
 *                                  - \ref UART_WORD_LEN_5
 *                                  - \ref UART_WORD_LEN_6
 *                                  - \ref UART_WORD_LEN_7
 *                                  - \ref UART_WORD_LEN_8
 *    @param[in]    u32parity       The parity setting (none/odd/even/mark/space) of UART module.
 *                                  - \ref UART_PARITY_NONE
 *                                  - \ref UART_PARITY_ODD
 *                                  - \ref UART_PARITY_EVEN
 *                                  - \ref UART_PARITY_MARK
 *                                  - \ref UART_PARITY_SPACE
 *    @param[in]    u32stop_bits    The stop bit length (1/1.5/2 bit) of UART module.
 *                                  - \ref UART_STOP_BIT_1
 *                                  - \ref UART_STOP_BIT_1_5
 *                                  - \ref UART_STOP_BIT_2
 *
 *    @return       None
 *
 *    @details      This function use to config UART line setting.
 */
void UART_SetLineConfig(UART_T *uart, uint32_t u32baudrate, uint32_t u32data_width, uint32_t u32parity, uint32_t  u32stop_bits)
{
    uint32_t u32UartClkSrcSel = 0ul, u32UartClkDivNum = 0ul;
    //uint32_t u32ClkTbl[4] = {XIN, LXT, ACLK, UCLK};
    uint32_t u32ClkTbl[4] = {12000000, 32768, 75000000, 150000000};
    uint32_t u32Baud_Div = 0ul;


    if ((uint32_t)uart == UART0_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL4) & (0x3ul << 3)) >> 3;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL4) & (0x7ul << 5)) >> 5;
    }
    else if ((uint32_t)uart == UART1_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL4) & (0x3ul << 11)) >> 11;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL4) & (0x7ul << 13)) >> 13;
    }
    else if ((uint32_t)uart == UART2_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL4) & (0x3ul << 19)) >> 19;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL4) & (0x7ul << 21)) >> 21;
    }
    else if ((uint32_t)uart == UART3_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL4) & (0x3ul << 27)) >> 27;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL4) & (0x7ul << 29)) >> 29;
    }
    else if ((uint32_t)uart == UART4_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL5) & (0x3ul << 3)) >> 3;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL5) & (0x7ul << 5)) >> 5;
    }
    else if ((uint32_t)uart == UART5_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL5) & (0x3ul << 11)) >> 11;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL5) & (0x7ul << 13)) >> 13;
    }
    else if ((uint32_t)uart == UART6_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL5) & (0x3ul << 19)) >> 19;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL5) & (0x7ul << 21)) >> 21;
    }
    else if ((uint32_t)uart == UART7_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL5) & (0x3ul << 27)) >> 27;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL5) & (0x7ul << 29)) >> 29;
    }
    else if ((uint32_t)uart == UART8_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL6) & (0x3ul << 3)) >> 3;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL6) & (0x7ul << 5)) >> 5;
    }
    else if ((uint32_t)uart == UART9_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL6) & (0x3ul << 11)) >> 11;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL6) & (0x7ul << 13)) >> 13;
    }
    else if ((uint32_t)uart == UARTA_BA)
    {
        /* Get UART clock source selection */
        u32UartClkSrcSel = (inp32(REG_CLK_DIVCTL6) & (0x3ul << 19)) >> 19;
        /* Get UART clock divider number */
        u32UartClkDivNum = (inp32(REG_CLK_DIVCTL6) & (0x7ul << 21)) >> 21;
    }

    /* Get PLL clock frequency if UART clock source selection is PLL */
    if (u32UartClkSrcSel == 2ul)  // ACLK
    {
        //u32ClkTbl[u32UartClkSrcSel] = CLK_GetPLLClockFreq();
    }

    if (u32UartClkSrcSel == 3ul)  // PCLK
    {
        //u32ClkTbl[u32UartClkSrcSel] = CLK_GetPLLClockFreq();
    }

    /* Set UART baud rate */
    if (u32baudrate != 0ul)
    {
        u32Baud_Div = UART_BAUD_MODE2_DIVIDER((u32ClkTbl[u32UartClkSrcSel]) / (u32UartClkDivNum + 1ul), u32baudrate);

        if (u32Baud_Div > 0xFFFFul)
        {
            uart->BAUD = (UART_BAUD_MODE0 | UART_BAUD_MODE0_DIVIDER((u32ClkTbl[u32UartClkSrcSel]) / (u32UartClkDivNum + 1ul), u32baudrate));
        }
        else
        {
            uart->BAUD = (UART_BAUD_MODE2 | u32Baud_Div);
        }
    }

    /* Set UART line configuration */
    uart->LINE = u32data_width | u32parity | u32stop_bits;
}
#endif


