/*!
*******************************************************************************
**
** \file        gd_eth_priv.h
**
** \version     2.0
**
** \date        June 09, 2013
**
** \author      Steven Yu
**
** \brief       GMAC3H Ethernet Driver.
**
** This application allows testing of the ethernet function.
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS.
**
** (C) Copyright 2002 - 2013 by Goke Microelectronics Shanghai WSC
**
*******************************************************************************
*/
#ifndef _GD_ETH_PRIV_H_
#define _GD_ETH_PRIV_H_
#include "gtypes.h"
#include "gd_ethernet.h"



//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************

//*****************************************************************************
//*****************************************************************************
//** Enumerated types
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Data Structures
//*****************************************************************************
//*****************************************************************************
typedef struct
{
    U32 lcCnt;
    U32 RUErrorCnt;
    U32 TUErrorCnt;
    U32 OvfErrorCnt;
    U32 UnfErrorCnt;
    U32 RWTErrorCnt;
    U32 TjtErrorCnt;
    U32 FbeRxErrorCnt;
    U32 FbeTxErrorCnt;
} GD_ETH_PHY_ErrorT;

typedef struct
{
    GD_ETH_PHY_AddrE    addr;
    GBOOL               supJumbo;
    GD_ETH_StatParamsT  workstat;
    GD_ETH_Work_ModeT   workmode;
    GD_ETH_PHY_ErrorT   error;
    GD_ETH_MacT         macaddr;
    GD_ETH_IpT          ipaddr;
    GD_HANDLE           phyreset;
    GD_HANDLE           phyhandle;
	U8                  phyType;

    U32 TxDesStartAddr;
    U32 RxDesStartAddr;

    U8 RxbufferNum;
    U8 TxbufferNum;
    U8 CurRxDesSite;    //the current rx description site(number)
    U8 CurTxDesSite;    //the current tx description site(number)
    U8 CurReadDesSite;
    U8 CurWriteDesSite;

    U8* Txbufferstart;
    U8* Rxbufferstart;
    U8* NetReceiveBuffer;//copy buffer

    GD_ETH_StatE StopFlag;
    U32 SizePerRxBuffer;
    U32 SizePerTxBuffer;
    void (*eth_rcve)(volatile U8* recbuf,U16 len);
} GD_ETH_HandleT;


//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************



#ifdef __cplusplus
extern "C" {
#endif

GD_HANDLE gd_eth_get_handle(void);

#ifdef __cplusplus
}
#endif



#endif /* _GD_ETH_PRIV_H_ */

