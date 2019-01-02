/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/emac/gd_ethernet.c
**
** \version     $Id$
**
** \brief
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2012-2013 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************
*/
#include <stdio.h>
#include <string.h>
#include "gtypes.h"
#include "gh_eth.h"
#include "gh_ephy.h"
#include "gd_int.h"
#include "gd_ethernet.h"
#include "gd_eth_priv.h"
#include "gd_eth_emac.h"
#include "gd_eth_phy.h"
#include "gd_timer.h"

//*****************************************************************************
//*****************************************************************************
//** Local Defines
//*****************************************************************************
//*****************************************************************************
#define MAX_RX_BUFFER_NUM               (100)
#define MAX_TX_BUFFER_NUM               (100)
// 2048+sizeof(GD_ETH_MAC_DesT)    (totaol size of per descriptor and buffer)
#define MAX_SIZE_PER_DESANDBUFFER       (2064)
#define ALIGN                           32

#define WRREG(addr,value)      *(volatile unsigned long*)(addr)=(value)
#define RDREG(addr)            *(volatile unsigned long*)(addr)



//*****************************************************************************
//*****************************************************************************
//** Local structures
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Local Data
//*****************************************************************************
//*****************************************************************************
static GD_HANDLE            ethIntHandle __attribute__ ((section(".nocache_buffer"))) = 0;
static GD_HANDLE            ethHandle __attribute__ ((section(".nocache_buffer"))) = 0;
/* driver handle array */
static GD_ETH_HandleT   ethdevice __attribute__ ((section(".nocache_buffer")))  =
{
    GD_ETH_PHY_EXTERNAL_AUTO,   /*addr*/
    GFALSE,                     /*supJumbo*/
    {
        GD_ETH_SPEED_AUTO,      /*workstat.speed*/
        GD_ETH_FULL_DUPLEX,     /*workstat.duplex*/
        GD_ETH_LOOP_OFF,        /*workstat.loopback*/
        GD_ETH_PHY_IF_MODE_MII, /*workstat.mode*/
        GD_ETH_LINKDOWN,        /*workstat.linkup*/
        GD_ETH_ERR_NONE         /*workstat.error*/
    },
    {
        GTRUE,                  /*workmode.bEnAutoNeg*/
        GD_ETH_SPEED_AUTO,      /*workmode.speed*/
        GD_ETH_FULL_DUPLEX,     /*workmode.duplex*/
        GD_ETH_LOOP_OFF,        /*workmode.loopback*/
        GD_ETH_PHY_IF_MODE_MII, /*workmode.mode*/
    },
    { 0x00 },                   /*error*/
    { 0x3C, 0x97, 0x0E, 0x22, 0xE1, 0x14 }, /*mac addr*/
    { 192, 168, 1, 20 },                    /*ip addr*/
    0,                       /*phyreset*/
    0,                       /*phyhandle*/
    0x00000000,                 /*TxDesStartAddr*/
    0x00000000,                 /*RxDesStartAddr*/
    0x00000000,                 /*RxbufferNum*/
    0x00000000,                 /*TxbufferNum*/
    0x00000000,                 /*CurRxDesSite*/
    0x00000000,                 /*CurTxDesSite*/
    0x00000000,                 /*CurReadDesSite*/
    0x00000000,                 /*CurWriteDesSite*/
    NULL,                       /*Txbufferstart*/
    NULL,                       /*Rxbufferstart*/
    NULL,                       /*NetReceiveBuffer*/
    GD_ETH_UNINITIALIZE,        /*StopFlag*/
    0x00000000,                 /*SizePerRxBuffer*/
    0x00000000,                 /*SizePerTxBuffer*/
    NULL,                       /*eth_rcve*/
};

static U32 ethReceiveBuffer[MAX_SIZE_PER_DESANDBUFFER*MAX_RX_BUFFER_NUM/4 + 8] __attribute__ ((section(".nocache_buffer")));
static U32 ethTranslateBuffer[MAX_SIZE_PER_DESANDBUFFER*MAX_TX_BUFFER_NUM/4 + 8] __attribute__ ((section(".nocache_buffer")));
//static U32 ethReceiveBuffer[MAX_SIZE_PER_DESANDBUFFER*MAX_RX_BUFFER_NUM/4 + 8];
//static U32 ethTranslateBuffer[MAX_SIZE_PER_DESANDBUFFER*MAX_TX_BUFFER_NUM/4 + 8];

static U32 ethReceiveBuf[1600] __attribute__ ((section(".nocache_buffer")));

//static U32* ethReceiveBuffer   = 0xCF000000;
//static U32* ethTranslateBuffer = 0xCF800000;

//*****************************************************************************
//*****************************************************************************
//** Local Functions Declaration
//*****************************************************************************
//*****************************************************************************
static void gd_ethClearErrorCount(void);
static void gd_eth_mac_InitRxTxBufDesc(GBOOL txtrue, GBOOL rxtrue);
static GERR gd_eth_mac_InitRxTxBuffer(void);
static void gd_eth_SetNetReceiveBuffer(U8* revbuf);


//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************
/*!
*****************************************************************************
** \brief Initialize the Ethernet driver.
**
** This function initializes Ethernet driver.
** It allocates and initializes driver handle structures as well as
** internal buffers for succeeding GD_ETH_Open(). Currently buffers are
** statically allocated. Setting up hardware is not part of GD_ETH_Init(),
** but is executed in GD_ETH_Open().
**
** \note This function is the implementation of
**       GD_SYS_DriverT::initDriverFunc.
**
** \return
**        - #GD_OK                      On success
**        - #GD_ERR_ALREADY_INITIALIZED Driver is already initialized
**        - #GD_ERR_INVALID_HANDLE      Invalid handle is specified
**        - #GD_ERR_SEMAPHORE_CREATE    Semaphore can not be created
**        - #GD_ERR_OUT_OF_MEMORY       Memory allocation failed
**                                        Not Implemented yet
**
** \sa GD_ETH_Exit()
*****************************************************************************
*/
GERR GD_ETH_Init(GD_ETH_InitParamsT* pInitParams)
{
    S32 retval;
    GD_INT_OPEN_PARAMS_S intOpenParams;
    if(ethIntHandle)
    {
        return GD_ERR_ALREADY_INITIALIZED;
    }
    if(pInitParams == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }
    intOpenParams.type           = GD_INT_ETH_IRQ;
    intOpenParams.sensitivity    = GD_INT_LEVEL_HIGH;
    intOpenParams.priority       = GD_INT_MID_PRIORITY;
    intOpenParams.active         = GD_INT_INVERT_IRQ;
    intOpenParams.isrFct.lowPrio = GD_ETH_Isr;
    retval =  GD_INT_Open(&intOpenParams, &ethIntHandle);
    if (retval != GD_OK)
    {
        return retval;
    }

    if (pInitParams->phyreset != GD_GPIO_0)
    {
        GD_GPIO_Open(pInitParams->phyreset, GD_GPIO_TYPE_OUTPUT_1, NULL, &ethdevice.phyreset);
    }

    if (pInitParams->bHWReset)
    {
        GD_ETH_PHY_HWReset((GD_HANDLE)&ethdevice);
    }
	
	if(pInitParams->phyType != 0)
	{
		ethDelay(); //100ms delay 
		ethdevice.workmode.mode = GD_ETH_PHY_IF_MODE_RMII;
	}
	else
	{
		ethdevice.workmode.mode = GD_ETH_PHY_IF_MODE_MII;
	}
	
#if 0
    if (pInitParams->phyreset != GD_GPIO_0) {
        GD_GPIO_Close(&ethdevice.phyreset);
        ethdevice.phyreset = NULL;
    }
#endif

    GD_ETH_PHY_Init(pInitParams->phyType);
    return retval;
}

/*!
*****************************************************************************
** \brief Exit the Ethernet driver.
**
** This function terminates Ethernet driver and deallocates internal buffers.
**
** \note This function is the implementation of
**       GD_SYS_DriverT::exitDriverFunc.
**
** \sa GD_ETH_Init()
*****************************************************************************
*/
GERR GD_ETH_Exit(void)
{
    if(ethIntHandle == 0)
    {
        return GD_ERR_NOT_INITIALIZED;
    }
    GD_INT_Enable(&ethIntHandle, 0);
    GD_INT_Close(&ethIntHandle);
    ethIntHandle = 0;
    if(ethdevice.phyreset)
    {
        GD_GPIO_Close(&ethdevice.phyreset);
        ethdevice.phyreset = 0;
    }
    return GD_OK;
}

/*!
*****************************************************************************
** \brief Open the Ethernet driver.
**
** This function opens the Ethernet driver. It initializes an internal
** handle structure depending on 'paramsPtr', and then set up underlying
** hardware. If succeed, the ethdevice has already got running.
**
** Auto-negotiation will be activated if #GD_ETH_SPEED_AUTO is specified
** in 'paramsPtr->speed'.
** Normally, 'paramsPtr->recvCallback' should be pointed to upper-layer protocol's
** input function. Specify NULL if it is not necessary.
**
** \param paramsPtr Pointer to #GD_ETH_OpenParamsT parameters.
**                  - version:     Driver version
**                  - devIndex:    Device index to identify Ethernet ethdevice (obsolete)
**                  - speed:       Speed setting
**                  - duplex:      Duplex mode setting
**                  - loop:        Loopback mode setting. It is only for
**                                 debugging purpose. General applications
**                                 should specify #GD_ETH_LOOP_OFF.
**                  - recvCallback:Callback function. It is called from
**                                 GD_ETH_Isr() at receiving-data event.
** \param errorCodePtr Pointer where error code should be stored or NULL if unused.
**
** \return
**        - (!NULL) Valid driver handle (obsolete) on success
**        - (NULL)  The driver can not be opened
**
** \sa GD_ETH_Close()
** \sa GD_ETH_Isr()
*****************************************************************************
*/
GERR GD_ETH_Open(GD_ETH_OpenParamsT* pOpenParams, GD_HANDLE* pHandle)
{
    U32 i;
    GERR     gerr;
    if(ethIntHandle == 0)
    {
        return GD_ERR_NOT_INITIALIZED;
    }
    if(pOpenParams == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }
    if(pHandle == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }
    if ((pOpenParams->addr > GD_ETH_PHY_EXTERNAL_AUTO) ||

        ((pOpenParams->workmode.bEnAutoNeg != GTRUE) &&
        ((pOpenParams->workmode.speed != GD_ETH_SPEED_AUTO) &&
        (pOpenParams->workmode.speed != GD_ETH_SPEED_10M) &&
        (pOpenParams->workmode.speed != GD_ETH_SPEED_100M) &&
        (pOpenParams->workmode.speed != GD_ETH_SPEED_1000M) ||
        (pOpenParams->workmode.duplex != GD_ETH_HALF_DUPLEX) &&
        (pOpenParams->workmode.duplex != GD_ETH_FULL_DUPLEX) ||
        (pOpenParams->workmode.loopback != GD_ETH_LOOP_OFF) &&
        (pOpenParams->workmode.loopback != GD_ETH_LOOP_ON_MAC) &&
        (pOpenParams->workmode.loopback != GD_ETH_LOOP_ON_PHY))) ||

        (pOpenParams->workmode.mode >= GD_ETH_PHY_IF_MODE_NONE))
    {
        return GD_ERR_BAD_PARAMETER;
    }
    if(ethHandle != 0)
    {
        return GD_ERR_ALREADY_OPEN;
    }
    ethdevice.addr                  = pOpenParams->addr;
    ethdevice.workmode.bEnAutoNeg   = pOpenParams->workmode.bEnAutoNeg;
    ethdevice.workmode.speed        = pOpenParams->workmode.speed;
    ethdevice.workmode.duplex       = pOpenParams->workmode.duplex;
    ethdevice.workmode.loopback     = pOpenParams->workmode.loopback;
   //ethdevice.workmode.mode         = pOpenParams->workmode.mode;

    // move to here for RMII mode, must config phy clk output first,
    // otherwise, the EMAC can not work.
    if(ethdevice.workmode.mode == GD_ETH_PHY_IF_MODE_RMII)
    	GD_TIMER_Delay(500); 
	
    gerr = GD_ETH_PHY_Open(&ethdevice.addr, &ethdevice.phyhandle);
    if(gerr!=GD_OK)
    {
        return gerr;
    }
    gerr = GD_ETH_PHY_SWReset(ethdevice.phyhandle);
    if(gerr!=GD_OK)
    {
        return gerr;
    }
    gerr = GD_ETH_PHY_SetWorkMode(ethdevice.phyhandle, ethdevice.workmode);
    if(gerr!=GD_OK)
    {
        return gerr;
    }

    switch(ethdevice.workmode.mode)
    {
    case GD_ETH_PHY_IF_MODE_SGMII:
    case GD_ETH_PHY_IF_MODE_GMII:
    case GD_ETH_PHY_IF_MODE_TBI:
    case GD_ETH_PHY_IF_MODE_RGMII:
    case GD_ETH_PHY_IF_MODE_RGMII_ID:
    case GD_ETH_PHY_IF_MODE_RGMII_RXID:
    case GD_ETH_PHY_IF_MODE_RGMII_TXID:
    case GD_ETH_PHY_IF_MODE_RTBI:
    case GD_ETH_PHY_IF_MODE_XGMII:
    case GD_ETH_PHY_IF_MODE_NONE:
        return GD_ERR_BAD_PARAMETER;
        //break;
    case GD_ETH_PHY_IF_MODE_MII:
        GH_EPHY_set_MII_RMII_rmii(0x0);
        break;
    case GD_ETH_PHY_IF_MODE_RMII:
    default:
        GH_EPHY_set_MII_RMII_rmii(0x1);
        break;
    }

    /* reset emac */
    GH_ETH_set_BMR(ETH_REG_BMR_SWRST);//reset emac all reg
    for ( i = 0; i < 1000; i++ )
    {
        GD_TIMER_Delay(1);
        if((GH_ETH_get_BMR() & ETH_REG_BMR_SWRST)!= ETH_REG_BMR_SWRST)
           break;
    }
    if ( i >=1000 )
    {
        return GD_ERR_ETH_MAC_NOT_OK;
    }

    gd_ethClearErrorCount();

    ethdevice.StopFlag = GD_ETH_UNINITIALIZE;

    /*Initialise the recevie and transmit buffer, and the descriptors*/
    gd_eth_mac_InitRxTxBuffer();

    gd_eth_SetNetReceiveBuffer((U8*)((U32)&ethReceiveBuf[0]+2));

#if FIX_TX_OWN
    //small endian,one bytes dma, skip length=0, swr=0
    //GH_ETH_set_BMR(ETH_REG_BMR_PBL1);
    GH_ETH_set_BMR_PBL(1);
#else
   //small endian,32 bytes dma, skip length=0, swr=0
    //GH_ETH_set_BMR(ETH_REG_BMR_PBL32);
    GH_ETH_set_BMR_PBL(32);
#endif /* FIX_TX_OWN */
    GH_ETH_set_BMR_FB(1);

    /* set MCR (Configuration resister) must be after phy initial */
    GH_ETH_set_MCR(ethSetupMCR((GD_HANDLE)&ethdevice));
    /* set RDLAR (Receive Descriptor base address) */
    GH_ETH_set_RDLAR((U32)(ethdevice.RxDesStartAddr));
    /* set TDLAR(descriptor base) current desc */
    GH_ETH_set_TDLAR((U32)(ethdevice.TxDesStartAddr));
    /* set MFFR (Address Filtering)*/
    GH_ETH_set_MFFR((U32)ETH_REG_MFFR_RA);//disable broadcast frame
    /* set MHTRH (Address Filtering)*/
    GH_ETH_set_MHTRH((U32)0xFFFFFFFF);
    /* set MHTRL (Address Filtering)*/
    GH_ETH_set_MHTRL((U32)0xFFFFFFFF);
    /* set MAR0H (MAC Address)*/
    GH_ETH_set_MAR0H(0x80000000+(pOpenParams->macaddr[5]<<8)+pOpenParams->macaddr[4]);
    /* set MAR0L (MAC Address)*/
    GH_ETH_set_MAR0L((pOpenParams->macaddr[3]<<24)+(pOpenParams->macaddr[2]<<16)+
                     (pOpenParams->macaddr[1]<<8)+(pOpenParams->macaddr[0]<<0));
    /* Setup Flow Control Register */
    GH_ETH_set_FCR(ETH_REG_FCR_TFE| ETH_REG_FCR_RFE);


#ifdef PRINT_ETH_LOG
    printf("TDLAR: 0x%08x\n", ethdevice.TxDesStartAddr);
    printf("RDLAR: 0x%08x\n", ethdevice.RxDesStartAddr);
#endif

//#if FIX_TX_OWN
    GH_ETH_set_OMR(GH_ETH_get_OMR()|ETH_REG_OMR_SF);
//#endif /* FIX_TX_OWN */

    GD_ETH_SetEMACSpeed((GD_HANDLE)&ethdevice, pOpenParams->workmode.speed);

    //set IER (Interrupt settings)
    GH_ETH_set_IER(ETH_REG_IER_NI | ETH_REG_IER_AI | ETH_REG_IER_FBE | ETH_REG_IER_RW
                    | ETH_REG_IER_RS | ETH_REG_IER_RU | ETH_REG_IER_RI | ETH_REG_IER_UN
                    | ETH_REG_IER_OVF | ETH_REG_IER_TJ | ETH_REG_IER_TU | ETH_REG_IER_TS | ETH_REG_IER_TI);

    /* added by waite wu */
    /* create thread */

    ethdevice.StopFlag   = GD_ETH_RX_STOP;
    ethdevice.StopFlag  |= GD_ETH_TX_STOP;

    GD_INT_Enable(&ethIntHandle, 1);

    GD_ETH_StartDevice((GD_HANDLE)&ethdevice, GD_ETH_R);//make it in rx/tx state
    //GD_ETH_StartDevice(&ethdevice, GD_ETH_W);//make it in tx state

    if(gerr != GD_OK)
    {
#ifdef PRINT_ETH_LOG
        printf("[%s_%d]Ethernet Initialization Failure!\n",__FUNCTION__, __LINE__);
#endif
        return GD_ERR_ETH_LINK_DOWN;
    }
#ifdef PRINT_ETH_LOG
    printf("[%s_%d]Ethernet Initialization Succeed!\n",__FUNCTION__, __LINE__);
#endif
    ethHandle = (GD_HANDLE)&ethdevice;
    *pHandle  = (GD_HANDLE)&ethdevice;
    return GD_OK;
}

/*!
*****************************************************************************
** \brief Close the Ethernet driver.
**
** This function closes the Ethernet driver. After this function, the ethdevice
** is stopped and its configurations are unset.
** If stop process failed, the handle is not closed.
**
** \param handle Ethernet driver handle (obsolete)
**
** \return
**        - #GD_ERR_NOT_INITIALIZED Ethernet driver is not initialized
**        - #GD_ERR_INVALID_HANDLE  Invalid handle is specified
**        - #GD_ETH_ERR_LOCK_FAIL   Handle lock failed. Try Again later.
**                                    This should not happen as all other
**                                    calls to this driver should be finished
**                                    when closing it.
**
** \sa GD_ETH_Open()
*****************************************************************************
*/
/*lint -e{715} */
GERR GD_ETH_Close(GD_HANDLE* pHandle)
{
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)(*pHandle);
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    GD_INT_Enable(pHandle, 0);
    ethHandle = 0;
    GD_ETH_PHY_Close(&device->phyhandle);
    return GD_OK;
}

/*!
*****************************************************************************
** \brief Read data over network.
**
** This function retrieves Ethernet frame data from the Ethernet ethdevice,
** and store them into a buffer, pointed to by 'bufPtr'.
** If 'size' is smaller than the one of actual frame, the left data can be
** read by succeeding GD_ETH_Read().
** Only if all the frame data are received successfully, #GD_ETH_FRAME_END
** is set in 'frame'.
**
** \param handle Ethernet driver handle (obsolete)
** \param bufPtr Pointer to read buffer
** \param size   Read size
** \param frame  Pointer to frame flag. If read process detect the end of an
**               Ethernet frame, #GD_ETH_FRAME_END is set then return. If it
**               is #GD_ETH_FRAME_NOTEND, read data does not contain frame
**               end. If it is #GD_ETH_FRAME_TERM, current Ethernet frame
**               was aborted by hardware errors. So application should discard
**               the read data.
**
** \return
**        - (>0) read data size.
**        - #GD_ERR_NOT_INITIALIZED Ethernet driver is not initialized
**        - #GD_ERR_INVALID_HANDLE  Invalid handle is specified
**        - #GD_ETH_ERR_NULL_PTR    bufPtr or frame is NULL
**        - #GD_ETH_ERR_LOCK_FAIL   Handle lock failed. Try Again later.
**                                    The handle may be locked by GD_ETH_Write
**                                    used in another tasks. A task switch
**                                    should be performed to allow the other
**                                    task to free the lock.
**        - #GD_ETH_ERR_DATACCESS   Unknown error on data copy
**        - #GD_ETH_ERR_RXSTOP      Read process failed because of its
**                                    fatal hardware errors . Application
**                                    should reset(close and re-open)
**                                    driver. GD_ETH_GetStat() can get
**                                    detailed information about the error.
** \sa GD_ETH_GetStat()
** \sa GD_ETH_Write()
*****************************************************************************
*/
/* ******************************************* */
/* Enable profiling for the following function */
/* ******************************************* */
/*lint -e(961) */
/* ******************************************* */
/*lint -e{715} */
S32 GD_ETH_Read(GD_HANDLE handle, char *bufPtr, S32 size, GD_ETH_FrameEndE *pframe)
{
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    return 0;
}

/*!
*****************************************************************************
** \brief Write data over network.
**
** This function writes Ethernet frame data, pointed to by 'bufPtr',
** into a buffer and hand it over to the Ethernet ethdevice.
** Only if #GD_ETH_FRAME_END is specified in 'frame', the data will be actually
** sent over network. Until then, all the data are kept in buffers.
**
** \param handle Ethernet driver handle (obsolete)
** \param bufPtr Pointer to write data
** \param size   Write size
** \param frame  Frame flag. It should be #GD_ETH_FRAME_NOTEND or
**               #GD_ETH_FRAME_END. If #GD_ETH_FRAME_NOTEND, the written
**               data is stored in driver. If #GD_ETH_FRAME_END, the data
**               stored in driver is transferred as an Ethernet frame.
**
** \return
**        - (>0)                      Written data size
**        - #GD_ERR_NOT_INITIALIZED Ethernet driver is not initialized
**        - #GD_ERR_INVALID_HANDLE  Invalid handle is specified
**        - #GD_ETH_ERR_NULL_PTR    bufPtr is NULL
**        - #GD_ETH_ERR_LOCK_FAIL   Handle lock failed. Try Again later.
**                                    The handle may be locked by GD_ETH_Read
**                                    used in another tasks. A task switch
**                                    should be performed to allow the other
**                                    task to free the lock.
**        - #GD_ETH_ERR_DATACCESS   Unknown error on data copy
**        - #GD_ETH_ERR_TXSTOP      Write process failed because of its
**                                    fatal hardware errors . Application
**                                    should  reset(close and re-open) driver.
**                                    GD_ETH_GetStat() can get detailed
**                                    information about the error.
**        - #GD_ETH_ERR_AGAIN       Write process failed on some non-fatal
**                                    errors. Try Again later.
**
** \sa GD_ETH_GetStat()
** \sa GD_ETH_Read()
*****************************************************************************
*/
/*lint -e{715} */
S32 GD_ETH_Write(GD_HANDLE handle, const char* buffer, S32 len, GD_ETH_FrameEndE frame)
{
    U32 i;
    U16 dlen;
    volatile GD_ETH_MAC_DesT* p;
    volatile U8* des;
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    if(len > device->SizePerTxBuffer)
    {
        printf("Len too big: %d, TxBufSize: %d\n", len, device->SizePerTxBuffer);
        return GFALSE;
    }

    /*Find a valid descriptor*/
#if 0
    for(i=0;i<device->TxbufferNum;i++)
    {
        p=(volatile GD_ETH_MAC_DesT*)((device->TxDesStartAddr) + device->CurWriteDesSite*sizeof(GD_ETH_MAC_DesT));
        if(((p->des0)&ETH_DES_T0_OWN) == 0 )
        {
            break;
        }
        /*update the CurWriteDesSite index*/
        if(device->CurWriteDesSite == device->TxbufferNum - 1)
        {
            device->CurWriteDesSite = 0;
        }
        else
        {
            device->CurWriteDesSite++;
        }
    }
    if(i == device->TxbufferNum)
    {
        printf("No valid descriptor!\n");
        return GFALSE;
    }
#else
    p=(volatile GD_ETH_MAC_DesT*)((device->TxDesStartAddr) + device->CurWriteDesSite*sizeof(GD_ETH_MAC_DesT));
    //GM_Printf("descriptor:0x%08x-0x%08x\n", (U32)p, GH_ETH_get_CHTDR());
    //GM_Printf("descriptor buffer:0x%08x-0x%08x\n", (U32)(p->des2), GH_ETH_get_CHTBAR());
    //GM_Printf("descriptor:0x%08x\n", (U32)p);
    //GM_Printf("descriptor buffer:0x%08x\n", (U32)(p->des2));
    //p=(volatile GD_ETH_MAC_DesT*)GH_ETH_get_CHTDR();
    if(((p->des0)&ETH_DES_T0_OWN) != 0 )
    {
        //GM_Printf("No valid descriptor!\n");
        return GFALSE;
    }
    /*update the CurWriteDesSite index*/
    if(device->CurWriteDesSite == device->TxbufferNum - 1)
    {
        device->CurWriteDesSite = 0;
    }
    else
    {
        device->CurWriteDesSite++;
    }

#endif

    p->des0=0;//ETH_DES_T0_OWN;
    p->des1 = (p->des1)&ETH_DES_T1_TER; //(ETH_DES_T1_TBS1 & 0x0);
    p->des3 =0;

    //copy data :
    des=(volatile U8*)(p->des2);////point to data buffer

    for(i=0;i<len;i++)
    {
        des[i]=buffer[i];
    }
    i = len;
    //add CRC check sum:
    des[i++]=0;
    des[i++]=0;
    des[i++]=0;
    des[i++]=0;
    //dlen=len+4;
    dlen=len;
    //set data length:
    /*if(dlen<64)
    {
        //printf("dlen = %d\n", dlen);
        for(i=0;i<(U8)(64-len);i++)//fix the error for data len < 64, (heyong).
            des[len+i]=i;
        p->des1 =(p->des1)|(ETH_DES_T1_TBS1 & 64); //first data buffer size
    }
    else*/
        p->des1 =(p->des1)|(ETH_DES_T1_TBS1 & len);
    p->des1 |= ETH_DES_T1_FS |ETH_DES_T1_LS| ETH_DES_T1_IC; //| ETH_DES_T1_TCH;//| ETH_DES_T1_TER; //first segment, last segment

    p->des3=0;//(U32)((device->TxDesStartAddr)+1*sizeof(GD_ETH_MAC_DesT));
    p->des0=ETH_DES_T0_OWN; //start to send

    GD_ETH_StartDevice(handle, GD_ETH_W);//make it in tx state
    return 0;
}

#define USE_TWO_BUFFER  1
GERR GD_ETH_Write_HD(GD_HANDLE handle, const char* HbufPtr, S32 Hsize, const char* DbufPtr, S32 Dsize, GD_ETH_FrameEndE frame)
{
    U32 i;
#ifndef USE_TWO_BUFFER
    U16 dlen;
#endif
    volatile GD_ETH_MAC_DesT* p;
    volatile U8* des;
    S32 len;
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    len = Hsize + Dsize;
    if(len > device->SizePerTxBuffer)
    {
        printf("Len too big: %d, TxBufSize: %d\n", len, device->SizePerTxBuffer);
        return GD_ERR_ETH_TB_OVER;
    }
    p=(volatile GD_ETH_MAC_DesT*)((device->TxDesStartAddr) + device->CurWriteDesSite*sizeof(GD_ETH_MAC_DesT));
    if(((p->des0)&ETH_DES_T0_OWN) != 0 )
    {
        //GM_Printf("No valid descriptor!\n");
        return GD_ERR_ETH_NO_TD;
    }
    /*update the CurWriteDesSite index*/
    if(device->CurWriteDesSite == device->TxbufferNum - 1)
    {
        device->CurWriteDesSite = 0;
    }
    else
    {
        device->CurWriteDesSite++;
    }

    p->des0=0;//ETH_DES_T0_OWN;
    p->des1 = (p->des1)&ETH_DES_T1_TER; //(ETH_DES_T1_TBS1 & 0x0);
#ifdef USE_TWO_BUFFER
    p->des3 = (U32)DbufPtr;
#else
    p->des3 = 0;
#endif

    //copy data :
    des=(volatile U8*)(p->des2);////point to data buffer

    for(i=0;i<Hsize;i++)
    {
        *des++=*HbufPtr++;
    }
#ifdef USE_TWO_BUFFER
#else
    for(i=0;i<Dsize;i++)
    {
        *des++=*DbufPtr++;
    }
#endif
    des=(volatile U8*)(p->des2);////point to data buffer
    i = len;
    //add CRC check sum:
    des[i++]=0;
    des[i++]=0;
    des[i++]=0;
    des[i++]=0;
    //set data length:
#ifdef USE_TWO_BUFFER
    p->des1 = (p->des1)|(ETH_DES_T1_TBS1 & Hsize) + (ETH_DES_T1_TBS2 & (Dsize<<11));
    p->des3 = (U32)DbufPtr;//(U32)((device->TxDesStartAddr)+1*sizeof(GD_ETH_MAC_DesT));
#else
    //dlen=len+4;
    dlen=len;
    if(dlen<64)
    {
        for(i=0;i<(U8)(60-len);i++)
            des[len+i]=i;
        p->des1 =(p->des1)|(ETH_DES_T1_TBS1 & 60); //first data buffer size
    }
    else
        p->des1 =(p->des1)|(ETH_DES_T1_TBS1 & len);
    p->des3 = 0;//(U32)((device->TxDesStartAddr)+1*sizeof(GD_ETH_MAC_DesT));
#endif
    p->des1 |= ETH_DES_T1_FS |ETH_DES_T1_LS| ETH_DES_T1_IC; //| ETH_DES_T1_TCH;//| ETH_DES_T1_TER; //first segment, last segment

    p->des0 = (U32)ETH_DES_T0_OWN; //start to send

    GD_ETH_StartDevice(handle, GD_ETH_W);//make it in tx state
    return GD_OK;
}

GERR GD_ETH_SetEMACSpeed(GD_HANDLE handle, GD_ETH_SpeedE speed)
{
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device->workmode.speed = speed;
    if(device->workmode.bEnAutoNeg)
    {
        printf("Set MAC work in AUTO mode\n");
    }
    else
    {
        switch(speed)
        {
        case GD_ETH_SPEED_AUTO:
            printf("Set MAC work in AUTO mode\n");
            break;
        case GD_ETH_SPEED_10M:
            printf("Set MAC work in 10M mode\n");
            break;
        case GD_ETH_SPEED_100M:
            printf("Set MAC work in 100M mode\n");
            break;
        case GD_ETH_SPEED_1000M:
            printf("Set MAC work in 1000M mode\n");
            break;
        }
    }
    return GD_ETH_PHY_SetWorkMode(device->phyhandle, device->workmode);
}

/*!
*****************************************************************************
** \brief Set Ethernet MAC address.
**
** This function returns Ethernet MAC address of the ethdevice in 'macAddress'.
** It can be called at any time after GD_ETH_Init().
**
** \param index      Device index to identify Ethernet ethdevice (obsolete)
** \param macAddress Ethernet MAC address, represented as byte buffer.
**
** \return
**        - #GD_OK                  On success
**        - #GD_ERR_NOT_INITIALIZED Ethernet driver is not initialized
**        - #GD_ETH_ERR_NULL_PTR    macAddress is NULL
**        - #GD_ETH_ERR_LOCK_FAIL   Handle lock failed. Try Again later.
**                                    The handle may be locked by another tasks.
**                                    A task switch should be performed to allow
**                                    the other task to free the lock.
**
*****************************************************************************
*/
/*lint -e{715} */
GERR GD_ETH_SetMacAddress(GD_HANDLE handle, GD_ETH_MacT macAddress)
{
    U32 i;
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    /* set MAR0H (MAC Address)*/
    GH_ETH_set_MAR0H(0x80000000+(macAddress[5]<<8)+macAddress[4]);
    /* set MAR0L (MAC Address)*/
    GH_ETH_set_MAR0L((macAddress[3]<<24)+(macAddress[2]<<16)+
                     (macAddress[1]<<8)+(macAddress[0]<<0));
    for(i=0; i<GD_ETH_MAC_ADDR_NUM; i++)
    {
        device->macaddr[i] = macAddress[i];
    }
    return GD_OK;
}

/*!
*****************************************************************************
** \brief Get Ethernet MAC address.
**
** This function returns Ethernet MAC address of the ethdevice in 'macAddress'.
** It can be called at any time after GD_ETH_Init().
**
** \param index      Device index to identify Ethernet ethdevice (obsolete)
** \param macAddress Ethernet MAC address, represented as byte buffer.
**
** \return
**        - #GD_OK                  On success
**        - #GD_ERR_NOT_INITIALIZED Ethernet driver is not initialized
**        - #GD_ETH_ERR_NULL_PTR    macAddress is NULL
**        - #GD_ETH_ERR_LOCK_FAIL   Handle lock failed. Try Again later.
**                                    The handle may be locked by another tasks.
**                                    A task switch should be performed to allow
**                                    the other task to free the lock.
**
*****************************************************************************
*/
/*lint -e{715} */
GERR GD_ETH_GetMacAddress(GD_HANDLE handle, GD_ETH_MacT* pmacAddress)
{
    U32 i;
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    if(pmacAddress == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }
    for(i=0; i<GD_ETH_MAC_ADDR_NUM; i++)
    {
       (*pmacAddress)[i] = device->macaddr[i];
    }
    return GD_OK;
}
GERR GD_ETH_SetIPAddress(GD_HANDLE handle, GD_ETH_IpT ipAddress)
{
    U32 i;
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    for(i=0; i<GD_ETH_IP_ADDR_NUM; i++)
    {
        device->ipaddr[i] = ipAddress[i];
    }
    return GD_OK;
}

GERR GD_ETH_GetIPAddress(GD_HANDLE handle, GD_ETH_IpT* pipAddress)
{
    U32 i;
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    if(pipAddress == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }
    for(i=0; i<GD_ETH_IP_ADDR_NUM; i++)
    {
        (*pipAddress)[i] = device->ipaddr[i];
    }
    return GD_OK;
}

GERR GD_ETH_GetPhyAddress(GD_HANDLE handle, U8* phy)
{
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    if(phy == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }
    *phy = device->addr;
    return GD_OK;
}

/*!
*****************************************************************************
** \brief Get Driver/Link status information
**
** This function returns information about the current ethdevice and link status.
** If lastly-called function returned an error, you can check details
** of error status with 'statParamsPtr->error'.
**
** \note Returned values are valid only if this function is called
** after GD_ETH_Open.
**
** \param handle Ethernet driver handle (obsolete)
** \param statParamsPtr Pointer to #GD_ETH_StatParamsT parameters
**                      - speed:       Speed setting
**                      - duplex:      Duplex mode setting
**                      - loop:        Local loopback mode setting
**                      - linkup:      Link is up or down
**                      - error:       Error details
** \return
**        - #GD_OK                  On success
**        - #GD_ERR_NOT_INITIALIZED Ethernet driver is not initialized
**        - #GD_ERR_INVALID_HANDLE  Invalid handle is specified
**        - #GD_ETH_ERR_NULL_PTR    statParamsPtr is NULL
**        - #GD_ETH_ERR_LOCK_FAIL   Handle lock failed. Try Again later.
**                                    The handle may be locked by another tasks.
**                                    A task switch should be performed to allow
**                                    the other task to free the lock.
**        - #GD_ETH_ERR_DATACCESS   Unknown error on data copy
**
** \sa GD_ETH_Read()
** \sa GD_ETH_Write()
*****************************************************************************
*/
/*lint -e{715} */
GERR GD_ETH_GetStat(GD_HANDLE handle, GD_ETH_StatParamsT *statParamsPtr)
{
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    return GD_ETH_PHY_GetWorkStatus(device->phyhandle, statParamsPtr);
}

/*!
*****************************************************************************
** \brief Check and update PHY-link status.
**
** This function checks and try to make the PHY-link up if it's in down-status.
** Is is assumed to be called periodically in order to keep the internal
** status updated.

** \param handle Ethernet driver handle (obsolete)

** \return
**        - #GD_OK                  On success
**        - #GD_ERR_NOT_INITIALIZED Ethernet driver is not initialized
**        - #GD_ERR_INVALID_HANDLE  Invalid handle is specified
**        - #GD_ETH_ERR_LOCK_FAIL   Handle lock failed. Try Again later.
**                                    The handle may be locked by another tasks.
**                                    A task switch should be performed to allow
**                                    the other task to free the lock.
**        - #GD_ETH_ERR_LINKDOWN    Link is still down.
**
** \sa GD_ETH_Open()
*****************************************************************************
*/
/*lint -e{715} */
GERR GD_ETH_CheckLink(GD_HANDLE handle)
{
    GERR retval;
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    retval = GD_ETH_PHY_GetWorkStatus(device->phyhandle, &device->workstat);
    return retval;
}

GERR GD_ETH_SleepTime(U32 ulTime)
{
    GD_TIMER_Delay(ulTime);
    return GD_OK;
}

void GD_ETH_SetNetReceiveFuc(void (*eth_rcve)(volatile U8* recbuf,U16 len))
{
    ethdevice.eth_rcve = eth_rcve;
}

//*****************************************************************************
//*****************************************************************************
//** Local Functions
//*****************************************************************************
//*****************************************************************************
/*
*****************************************************************************
** \brief clear error count
**
** This function clears error counts.
**
** \param rw      Read/write direction
**
*****************************************************************************
*/
static void gd_ethClearErrorCount(void)
{
    ethdevice.error.lcCnt          = 0;
    ethdevice.error.RUErrorCnt     = 0;
    ethdevice.error.TUErrorCnt     = 0;
    ethdevice.error.OvfErrorCnt    = 0;
    ethdevice.error.UnfErrorCnt    = 0;
    ethdevice.error.RWTErrorCnt    = 0;
    ethdevice.error.TjtErrorCnt    = 0;
    ethdevice.error.FbeRxErrorCnt  = 0;
    ethdevice.error.FbeTxErrorCnt  = 0;
}

static void gd_eth_mac_InitRxTxBufDesc(GBOOL txtrue, GBOOL rxtrue)
{
    volatile GD_ETH_MAC_DesT* p = NULL;
    U32 i;

    if(rxtrue == GTRUE)
    {
        /* Initialize the rx description */
        for(i = 0;i < ethdevice.RxbufferNum; i++)
        {
            p = (volatile GD_ETH_MAC_DesT*)((ethdevice.RxDesStartAddr) + (i * sizeof(GD_ETH_MAC_DesT)));
            p->des0 = (U32)(ETH_DES_R0_OWN);
            p->des1 = ethdevice.SizePerRxBuffer - 1;//rbs1=2047,rbs2=0;
            p->des2 = (U32)ethdevice.Rxbufferstart + (i *ethdevice.SizePerRxBuffer);
            p->des3 = 0x0;
        }

        if(p != NULL)
        {
            /* mark the last buffer */
            p->des1 |= ETH_DES_R1_RER;//RER=1,bit 25,last rxdesc
        }
    }

    if(txtrue == GTRUE)
    {
        /* Initialize the tx description */
        for(i = 0; i < ethdevice.TxbufferNum; i++)
        {
            p = (volatile GD_ETH_MAC_DesT*)((ethdevice.TxDesStartAddr) + (i * sizeof(GD_ETH_MAC_DesT)));
            p->des0 = 0x00000000;
            p->des1 = 0;//ETH_DES_T1_IC|ETH_DES_T1_FS|ETH_DES_T1_TCH;//0xA1000000(set IC(bit31),FS(bit29),CH1(bit24))
            p->des2 = (U32)ethdevice.Txbufferstart + i * ethdevice.SizePerTxBuffer;
            p->des3 = 0x0;
        }

        if(p != NULL)
        {
            /* mark the last buffer */
            p->des1 |= ETH_DES_T1_TER;//TER=1,bit 25,last txdesc
        }
    }

    return;

}

static GERR gd_eth_mac_InitRxTxBuffer(void)
{
    U32 RxAddOffset, TxAddOffset;

    /* memory clear */
    memset((void*)ethReceiveBuffer, 0, (MAX_SIZE_PER_DESANDBUFFER * MAX_RX_BUFFER_NUM + 32));
    memset((void*)ethTranslateBuffer, 0, (MAX_SIZE_PER_DESANDBUFFER * MAX_TX_BUFFER_NUM + 32));

    /* address align(32) */
    RxAddOffset = ALIGN - (((U32)&ethReceiveBuffer[0]) % ALIGN);
    TxAddOffset = ALIGN - (((U32)&ethTranslateBuffer[0]) % ALIGN);

    /* Initialize MAC Host description */
    ethdevice.RxbufferNum        = MAX_RX_BUFFER_NUM;
    ethdevice.TxbufferNum        = MAX_TX_BUFFER_NUM;
    ethdevice.SizePerRxBuffer    = MAX_SIZE_PER_DESANDBUFFER - sizeof(GD_ETH_MAC_DesT);
    ethdevice.SizePerTxBuffer    = MAX_SIZE_PER_DESANDBUFFER - sizeof(GD_ETH_MAC_DesT);
    ethdevice.TxDesStartAddr     = (U32)ethTranslateBuffer + TxAddOffset;
    ethdevice.RxDesStartAddr     = (U32)ethReceiveBuffer + RxAddOffset;
    ethdevice.Txbufferstart      = (U8*)((U32)ethdevice.TxDesStartAddr+(ethdevice.TxbufferNum)*sizeof(GD_ETH_MAC_DesT));
    ethdevice.Rxbufferstart      = (U8*)((U32)ethdevice.RxDesStartAddr+(ethdevice.RxbufferNum)*sizeof(GD_ETH_MAC_DesT));
    ethdevice.CurRxDesSite       = 0;
    ethdevice.CurTxDesSite       = 0;
    ethdevice.CurReadDesSite     = 0;
    ethdevice.CurWriteDesSite    = 0;

    /* Initialize the rx&tx buffer description */
    gd_eth_mac_InitRxTxBufDesc(GTRUE, GTRUE);

    return GD_OK;

}

static void gd_eth_SetNetReceiveBuffer(U8* revbuf)
{
    ethdevice.NetReceiveBuffer=(U8*)revbuf;
}

GD_HANDLE gd_eth_get_handle(void)
{
    return (GD_HANDLE)&ethdevice;
}

