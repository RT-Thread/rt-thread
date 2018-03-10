/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/emac/gd_eth_emac.c
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
#include "gd_int.h"
#include "gd_ethernet.h"
#include "gd_eth_priv.h"
#include "gd_eth_emac.h"
#include "gd_eth_phy.h"
#include "gd_timer.h"

//#define DEBUG_PRINT

//*****************************************************************************
//*****************************************************************************
//** Local Defines
//*****************************************************************************
//*****************************************************************************
#define EMAC_CR    0x0    //  60-100MHz      84clk, 1.68us
//#define EMAC_CR    0x1    // 100-150MHz     124clk, 2.48us
//#define EMAC_CR    0x2    //  20- 35MHz      32clk, 0.6401us
//#define EMAC_CR    0x3    //  35~ 60MHz
//#define EMAC_CR    0x4    //  150-250 MHz
//#define EMAC_CR    0x5    //  250-300 MHz
//MDC read:
//000        60-100 MHz clk_csr_i/42    clk_csr_i=25MHz
//001        100-150 MHz clk_csr_i/62
//010        20-35 MHz clk_csr_i/16
//011        35-60 MHz clk_csr_i/26
//100        150-250 MHz clk_csr_i/102
//101        250-300 MHz clk_csr_i/122
//110,111  Reserved


/* Error count MAX value */
#define GD_ETH_LC_MAX             (50)
#define GD_ETH_TJT_MAX            (50)
#define GD_ETH_RWT_MAX            (50)
#define GD_ETH_UNF_MAX            (50)
#define GD_ETH_OVF_MAX            (50)


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



//*****************************************************************************
//*****************************************************************************
//** Local Functions Declaration
//*****************************************************************************
//*****************************************************************************
void ethStopDevice(GD_HANDLE handle, GD_ETH_RWE rw);
void ETH_MAC_RxDataProcess(GD_HANDLE handle);
void ethDelay(void);
#if USE_FLOWCTL
void ethSendPause(void);
#endif



//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************
/*!
*****************************************************************************
** \brief Interrupt service routine of the Ethernet driver.
**
** This function calls user callback function, which is registered by
** GD_ETH_Open, when receiving Ethernet frames.
**
** \note This function implements GD_SYS_DriverT::isrFunc.
**
** \return 0, as no further background processing is used.
**
** \sa GD_ETH_Open()
*****************************************************************************
*/
/*lint -e(961, 537, 451) */
GISR1 GD_ETH_Isr(void)
{
    U32 sr;

    GD_HANDLE handle = gd_eth_get_handle();

    // read & clear interrupt status
    sr = GH_ETH_get_SR();
    GH_ETH_set_SR(sr);

#ifdef DEBUG_PRINT
    GM_Printf("sr = 0x%08x\n", sr);
    //GM_Printf("cursr = 0x%08x\n", GH_ETH_get_SR());
#endif

    //GH_ARC_set_IRQClear(0x200);
    //GH_ARC_set_IRQClear(GD_INT_ETH_IRQ);

    // Fatal Bus Error
    if ( (sr & ETH_REG_SR_FBE) == ETH_REG_SR_FBE )
    {
#ifdef DEBUG_PRINT
        GM_Printf("ETH_REG_SR_FBE! SR = 0x%08x\n",sr);
#endif
        ethFBEInt( handle, sr );
    }

    if((sr & (ETH_REG_SR_OVF)) == ETH_REG_SR_OVF)
    {
        //This bit indicates overflow
#ifdef DEBUG_PRINT
        GM_Printf("The rx descriptor is overflow! SR = 0x%08x\n",sr);
#endif
    }

    if((sr & (ETH_REG_SR_ERI)) == ETH_REG_SR_ERI)
    {   //This bit indicates that the MDC had filled the first data buffer of the packe.
        //SR(bit6)RI automatically clears this bit
        //U8 i = 0;

#ifdef DEBUG_PRINT
        GM_Printf("ETH_REG_SR_ERI! SR = 0x%08x\n",sr);
#endif
    }

    //This bit indicates that the next descriptor in the receive list is owned by the host.
    if ( (sr & ETH_REG_SR_RU) == ETH_REG_SR_RU)
    {
#ifdef DEBUG_PRINT
        GM_Printf("ETH_REG_SR_RU! SR = 0x%08x\n",sr);
#endif
        ethRUInt( handle );
        GH_ETH_set_RPDR(1);
    }

    if ( (sr & ETH_REG_SR_RI) == ETH_REG_SR_RI )//frame receive finish
    {
#ifdef DEBUG_PRINT
        GM_Printf("ETH_REG_SR_RI! SR = 0x%08x\n",sr);
#endif
        ETH_MAC_RxDataProcess(handle);
    }

    // Transfer Descriptor Update , point to next descriptor
    if ((sr & (ETH_REG_SR_ETI | ETH_REG_SR_UNF | ETH_REG_SR_TPS | ETH_REG_SR_TU | ETH_REG_SR_TI | ETH_REG_SR_TJT)) != 0 )
    {
#ifdef DEBUG_PRINT
        GM_Printf("ETH TX! SR = 0x%08x\n",sr);
#endif
        ethHandleIntTx( handle);
    }

    if((sr & (ETH_REG_SR_RPS)) == ETH_REG_SR_RPS)
    {   //This bit asserted when Receive Process enters the stopped state.
#ifdef DEBUG_PRINT
        GM_Printf("ETH_REG_SR_RPS! SR = 0x%08x\n",sr);
#endif
    }

    if((sr & (ETH_REG_SR_RWT)) == ETH_REG_SR_RWT)
    {   //This bit is assert when a frame with a length greater than 2048 bytes is received
#ifdef DEBUG_PRINT
        GM_Printf("ETH_REG_SR_RWT! SR = 0x%08x\n",sr);
#endif
    }

    if ((sr & ETH_REG_SR_TU) == ETH_REG_SR_TU)
    {
#ifdef DEBUG_PRINT
        GM_Printf("ETH_REG_SR_TU! SR = 0x%08x\n",sr);
#endif
        ethTUInt( handle );
    }
}

GBOOL GD_ETH_CheckPhyBusy(void)
{
    U32 i=0, value;
    while ( i < 2000 )//how to ensure the numbers of the cycle??
    {
        value = GH_ETH_get_GAR();
        if((value & 0x1) == 0) //if MII not busy
            return GFALSE;
        i++;
    }
    return GTRUE;//busy
}

GBOOL GD_ETH_ReadPhy(U8 phyAddr, U8 phyReg, U32* phyRegValue)
{
    GBOOL   retval;

    /* parameter checkout */
    if( (phyAddr > GD_ETH_PHY_EXTERNAL_AUTO)
       ||(phyReg >= GD_ETH_PHY_MAX_REG_NUM)
       ||(phyRegValue == NULL))
    {
        return GFALSE;
    }

    /* check if the PHY is busy? Busy:True, Idle:False */
    retval = GD_ETH_CheckPhyBusy();
    if(retval != GFALSE)
        return GFALSE;

    /* set GDR: */
    //busy and read ,CR=0(MDC:1.42-2.38MHz)
    GH_ETH_set_GAR((phyAddr << ETH_REG_GAR_SHIFT_PA)
                   |(phyReg << ETH_REG_GAR_SHIFT_GR)
                   | ETH_REG_GAR_GB
                   | (EMAC_CR << ETH_REG_GAR_SHIFT_CR));

    /* check if the PHY is busy? Busy:True, Idle:False */
    retval = GD_ETH_CheckPhyBusy();
    if ( retval != GFALSE )
        return GFALSE;

    /* read data: */
    *phyRegValue = (U32)GH_ETH_get_GDR_GD();

    return GTRUE;

}

//MDC write:
GBOOL GD_ETH_WritePhy(U8 phyAddr, U8 phyReg, U32 phyRegVal)
{
    U32  i;
    GBOOL retval;

    /* parameter checkout */
    if((phyAddr > GD_ETH_PHY_EXTERNAL_AUTO)||(phyReg >= GD_ETH_PHY_MAX_REG_NUM))// out of range:5 bit
        return GFALSE;

    /* check if the PHY is busy? Busy:True, Idle:False */
    retval = GD_ETH_CheckPhyBusy();
    if ( retval != GFALSE )
        return GFALSE;

    /* set GDR: */
    i=(GH_ETH_get_GDR()& 0xffff0000);
    GH_ETH_set_GDR(i + (phyRegVal & 0xffff));

    /* check if the PHY is busy? Busy:True, Idle:False */
    retval = GD_ETH_CheckPhyBusy();
    if ( retval != GFALSE )
        return GFALSE;

    /* set DAR: */
    //busy and write ,CR=0(MDC:1.42-2.38MHz)
    GH_ETH_set_GAR((phyAddr << ETH_REG_GAR_SHIFT_PA)
                   |(phyReg << ETH_REG_GAR_SHIFT_GR )
                   | ETH_REG_GAR_GW
                   | ETH_REG_GAR_GB
                   | (EMAC_CR << ETH_REG_GAR_SHIFT_CR));//status is busy, next action will be write

    return GTRUE;

}

GERR GD_ETH_PHY_HWReset(GD_HANDLE handle)
{
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device && device->phyreset)
    {
        GD_GPIO_Write(device->phyreset, 1);
        ethDelay(); //100ms delay
        GD_GPIO_Write(device->phyreset, 0);
        //gd_eth_TimerDelay(50);//100ms
        ethDelay(); //100ms delay
        GD_GPIO_Write(device->phyreset, 1);
        //ethDelay(); //100ms delay
    }
    return GD_OK;
}

void GD_ETH_StartDevice(GD_HANDLE handle, GD_ETH_RWE IsRx)
{
    U32 omr;
    U32 old_omr;
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device == NULL)   return;

    /* Get the information of OMR(MDC Operation Mode Register) */
    omr = GH_ETH_get_OMR();
#ifdef DEBUG_PRINT
    GM_Printf("oldOMR = 0x%08x\n",omr);
#endif
    old_omr = omr;
    if ( IsRx & GD_ETH_R)
    {
        if((device->StopFlag & GD_ETH_RX_STOP)||
           (device->StopFlag & GD_ETH_RX_STOP_HWERR))
        {
            device->StopFlag &= ~GD_ETH_RX_STOP;
            device->StopFlag &= ~GD_ETH_RX_STOP_HWERR;
            device->StopFlag |= GD_ETH_RX_RUN;
            omr |= ETH_REG_OMR_SR;
        }
        else if((device->StopFlag & GD_ETH_RX_SUSP_NOBUF)||
                (device->StopFlag & GD_ETH_RX_SUSP_HWERR))
        {
            device->StopFlag &= ~GD_ETH_RX_SUSP_NOBUF;
            device->StopFlag &= ~GD_ETH_RX_SUSP_HWERR;
            device->StopFlag |= GD_ETH_RX_RUN;

            GH_ETH_set_RPDR(1);//set any value, then F_MAC3H will check receive descriptor
        }
    }

    if(IsRx & GD_ETH_W)
    {
        if((device->StopFlag & GD_ETH_TX_STOP)||
           (device->StopFlag & GD_ETH_TX_STOP_HWERR))
        {
            device->StopFlag &= ~GD_ETH_TX_STOP;
            device->StopFlag &= ~GD_ETH_TX_STOP_HWERR;
            device->StopFlag |= GD_ETH_TX_RUN;

            omr |= ETH_REG_OMR_ST;
        }
        else if((device->StopFlag & GD_ETH_TX_SUSP_NODAT)||
                (device->StopFlag & GD_ETH_TX_SUSP_HWERR))
        {
            device->StopFlag &= ~GD_ETH_TX_SUSP_NODAT;
            device->StopFlag &= ~GD_ETH_TX_SUSP_HWERR;
            device->StopFlag |= GD_ETH_TX_RUN;

            GH_ETH_set_TPDR(1);//set any value, then F_MAC3H will check for frame to be transmit.s
        }
    }

#ifdef DEBUG_PRINT
    GM_Printf("newOMR = 0x%08x\n",omr);
#endif

    if ( omr != old_omr )
    {
        /* Update the OMR */
        GH_ETH_set_OMR(omr);
    }
}

//*****************************************************************************
//*****************************************************************************
//** Local Functions
//*****************************************************************************
//*****************************************************************************

/*
*****************************************************************************
** \brief software bug assert
**
** This function asserts a software bug to stop receive/transmit process later
** and also generates some messages.
**
** \param func    Pointer to a name of function
** \param message Pointer to a message
**
*****************************************************************************
*/
/*lint -e{715} */
void gmcSWError(GD_HANDLE handle)
{
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device==NULL)
        return;
    device->error.RWTErrorCnt++;
    if(device->error.RWTErrorCnt>GD_ETH_RWT_MAX)
    {
        device->StopFlag |= GD_ETH_FATAL_ERROR;
        ethStopDevice(handle, GD_ETH_RW );
        device->StopFlag = GD_ETH_FATAL_ERROR;
    }
    else
    {
        device->StopFlag |= GD_ETH_RX_RUN;
    }
}

/*
*****************************************************************************
** \brief LC error handler
**
** This function handles LC(Loss of Carrier) error.
**
** \param rw      Read/write direction
**
*****************************************************************************
*/
void ethLCErr(GD_HANDLE handle, GBOOL IsRx)
{
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device==NULL)
        return;

    device->error.lcCnt++;
    if(device->error.lcCnt>GD_ETH_LC_MAX)
    {
        device->StopFlag |=GD_ETH_FATAL_ERROR;
        ethStopDevice(handle, GD_ETH_RW );
        device->StopFlag = GD_ETH_FATAL_ERROR;
    }
    else
    {
        if(IsRx)
        {
            device->StopFlag |=GD_ETH_RX_RUN;
        }
        else
        {
            device->StopFlag |=GD_ETH_TX_RUN;
        }
    }
}
/*
*****************************************************************************
** \brief RU error handler
**
** This function handles RU(Receive Buffer Unavailable) error.
**
*****************************************************************************
*/
void ethRUInt(GD_HANDLE handle)
{
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device == NULL)
    {
        return;
    }

#if USE_FLOWCTL
    ethSendPause();
#endif

    device->error.RUErrorCnt++;
    //device->StopFlag |= GD_ETH_RX_SUSP_NOBUF;
    //device->StopFlag &= (~GD_ETH_RX_RUN);

    /*stop the receiving*/
    ethStopDevice(handle,GD_ETH_R);

    /*disable ru interrupt*/
    GH_ETH_set_IER_RU(0);

    /*process received packets*/
    ETH_MAC_RxDataProcess(handle);

    /*reset the receicve descriptors*/
    //ETH_MAC_InitRxTxBufDesc(GFALSE, GTRUE);

    GH_ETH_set_RDLAR((U32)(device->RxDesStartAddr));
    device->CurRxDesSite = 0;

    /*enable RU interrupt*/
    GH_ETH_set_IER_RU(1);

    /*restart the receiving*/
    GD_ETH_StartDevice(handle, GD_ETH_R);//make it in rx state

}

/*
*****************************************************************************
** \brief OVF error handler
**
** This function handles OVF(Receive Overflow) error.
**
*****************************************************************************
*/
void ethOVFInt(GD_HANDLE handle)
{
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device==NULL)
        return;
    device->error.OvfErrorCnt++;
    if(device->error.OvfErrorCnt>GD_ETH_OVF_MAX)
    {
        device->StopFlag |=GD_ETH_FATAL_ERROR;
        ethStopDevice(handle, GD_ETH_RW );
        device->StopFlag = GD_ETH_FATAL_ERROR;
    }
    else
    {
        device->StopFlag |=GD_ETH_RX_RUN;
    }
}

/*
*****************************************************************************
** \brief RWT error handler
**
** This function handles RWT(Receive Watchdog Timeout) error.
**
** \param    Fmac3h device Id
**
*****************************************************************************
*/
void ethRWTInt(GD_HANDLE handle)
{
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device==NULL)
    {
        return;
    }
    device->error.RWTErrorCnt++;
    if(device->error.RWTErrorCnt>GD_ETH_RWT_MAX)
    {
        device->StopFlag |= GD_ETH_FATAL_ERROR;
        ethStopDevice(handle, GD_ETH_RW );
        device->StopFlag = GD_ETH_FATAL_ERROR;
    }
    else
    {
        device->StopFlag |= GD_ETH_RX_RUN;
    }
}

/*
*****************************************************************************
** \brief TU error handler
**
** This function handles TU(Transmit Buffer Unavailable) error.
**
*****************************************************************************
*/
void ethTUInt(GD_HANDLE handle)
{
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device == NULL)
        return;
    device->error.TUErrorCnt++;
    device->StopFlag |= GD_ETH_TX_SUSP_NODAT;
    //device->StopFlag &= (~GD_ETH_TX_RUN);
}

/*
*****************************************************************************
** \brief UNF error handler
**
** This function handles UNF(Transmit Underflow) error.
**
*****************************************************************************
*/
void ethUNFInt(GD_HANDLE handle)
{
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device==NULL)
        return;
    device->error.UnfErrorCnt++;

    if(device->error.UnfErrorCnt>GD_ETH_UNF_MAX)
    {
        device->StopFlag |=GD_ETH_FATAL_ERROR;
        ethStopDevice(handle, GD_ETH_RW );
        device->StopFlag = GD_ETH_FATAL_ERROR;
    }
    else
    {
        device->StopFlag |=GD_ETH_TX_SUSP_HWERR;
        GD_ETH_StartDevice(handle, GD_ETH_W );
    }
}

/*
*****************************************************************************
** \brief TJT error handler
**
** This function handles TJT(Transmit Jabber Timeout) error.
**
*****************************************************************************
*/
void ethTJTInt(GD_HANDLE handle)
{
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device==NULL)
        return;
    device->error.TjtErrorCnt++;
    if(device->error.TjtErrorCnt>GD_ETH_TJT_MAX)
    {
        device->StopFlag |=GD_ETH_FATAL_ERROR;
        ethStopDevice(handle, GD_ETH_RW );
        device->StopFlag = GD_ETH_FATAL_ERROR;
    }
    else
    {
        device->StopFlag |=GD_ETH_TX_STOP_HWERR;
        GD_ETH_StartDevice(handle, GD_ETH_W );
    }
}

/*
*****************************************************************************
** \brief FBE error handler
**
** This function handles FBE(Fatal Bus Error) error.
**
** \param sr      SR register value
**
*****************************************************************************
*/
void ethFBEInt(GD_HANDLE handle, U32 sr)
{
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device==NULL)
        return;

    device->StopFlag |=GD_ETH_FATAL_ERROR;
    if((sr & ETH_REG_SR_EB) == ETH_REG_SR_TXEB)//host abort received in transmition
    {
        device->error.FbeTxErrorCnt++;
    }
    else
    {
        device->error.FbeRxErrorCnt++;
    }
    ethStopDevice(handle, GD_ETH_RW);
    device->StopFlag = GD_ETH_FATAL_ERROR;
}

/*
*****************************************************************************
** \brief handler for receive interrupt
**
** This function handles receive interrupt(RI). It searches for completed descriptors
** by checking descriptor status (Own bit) and make descPtrRx updated.
**
** \return
**        -#GTRUE    Readable data was detected
**        -#GFALSE   Readable data was not detected
*****************************************************************************
*/
void ethHandleIntRx(GD_HANDLE handle)
{
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    GD_ETH_MAC_DesT* p;
    GBOOL bHandling = GTRUE;
    /*   Before        Descriptors         After interrupt
     *                +---------------+
     *                |1              |
     *                |---------------|
     *                |1              |
     *  descPtrRead-->|---------------|
     *                |0              |
     *                |---------------|
     *                |0              |
     *  descPtrRx  -->|---------------|
     *                |1=>0           |    Own bit is 1 => 0, and
     *                |---------------|<---new descPtrRx should be here.
     *                |1              |
     *                +---------------+
     */

    if(device==NULL)
        return;

    while (bHandling)
    {
        p=(GD_ETH_MAC_DesT*)((device->RxDesStartAddr)+device->CurRxDesSite*sizeof(GD_ETH_MAC_DesT));
        if((p->des0 & 0x80000000) == 0x80000000)
            break;
        if(device->CurRxDesSite==device->RxbufferNum-1)
           device->CurRxDesSite=0;
        else
           device->CurRxDesSite++;
        if ( device->CurRxDesSite == device->CurReadDesSite)
            break;
    }
}

/*
*****************************************************************************
** \brief handler for transfer interrupt
**
** This function handles transfer interrupt(TI). It searches for completed
** descriptors by checking descriptor status(Own bit), and make descPtrTx updated.
** It also reclaims used transmit buffers.
**
*****************************************************************************
*/
void ethHandleIntTx(GD_HANDLE handle)
{
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    GD_ETH_MAC_DesT* p;
    GBOOL bHandling = GTRUE;

    /*   Before        Descriptors         After interrupt
     *                +---------------+
     *                |1              |
     *                |---------------|
     *                |1              |
     * descPtrTx   -->|---------------|
     *                |1=>0           |    Own bit is 1 => 0, and
     *                |---------------|<---new descPtrTx should be here.
     *                |0              |
     *                |---------------|
     *                |0              |
     * descPtrWrite-->|---------------|
     *                |1              |
     *                +---------------+
     */

    if(device==NULL)
        return;

    if(device->CurTxDesSite == device->CurWriteDesSite)
    {
        return;
    }

    while(bHandling)
    {
        //GM_Printf("+");
        p=(GD_ETH_MAC_DesT*)((device->TxDesStartAddr)+device->CurTxDesSite*sizeof(GD_ETH_MAC_DesT));

#ifdef DEBUG_PRINT
        GM_Printf("Des0 = 0x%08x\n",p->des0);
        GM_Printf("Des1 = 0x%08x\n",p->des1);
        GM_Printf("Des2 = 0x%08x\n",p->des2);
        GM_Printf("Des3 = 0x%08x\n",p->des3);
#endif

        if( (p->des0 & 0x80000000) == 0x80000000)
        {
            break;
        }
        if(p->des0 & ETH_DES_T0_ES)//happen any error
        {
            if(p->des0 & ETH_DES_T0_JT)
                ethTJTInt(handle);
            if(p->des0 & ETH_DES_T0_UF)
                ethUNFInt(handle);
            if(p->des0 & ETH_DES_T0_LCO)
                ethLCErr(handle, GFALSE);
            if((p->des0 & ETH_DES_T0_EC )||(p->des0 & ETH_DES_T0_ED))
            {
                ;
            }
            if((p->des1 & ETH_DES_T1_LS)==0)
            {
                break;
            }
        }
        if(device->CurTxDesSite==device->TxbufferNum-1)
        {
            device->CurTxDesSite=0;
        }
        else
        {
            device->CurTxDesSite++;
        }
        if ( device->CurTxDesSite == device->CurWriteDesSite)
        {
            break;
        }
    }
}

GBOOL ethGetRxDescriptorDataSize(volatile GD_ETH_MAC_DesT* p, U16* datalen)
{
    if((p == NULL)||(datalen == NULL))
        return GFALSE;

    if(p->des0 & ETH_DES_R0_LS)//last buffers of the frame
        *datalen=(p->des0 & ETH_DES_R0_FL) >> 16;//frame lenth
    else
        *datalen=(p->des1 & ETH_DES_R1_RBS1);

    return GTRUE;
}

void ETH_MAC_RxDataProcess(GD_HANDLE handle)
{
    GD_ETH_MAC_DesT* p_RxDesTmp;
    volatile GD_ETH_MAC_DesT* p;
    volatile GD_ETH_MAC_DesT* p_FrameStart;
    GBOOL  b_FrameStart=GFALSE; 
    volatile U8* revbuf;
    volatile U8* p_RxCopyBuf;    
    volatile U8* p_RxSrcBuf;    
    U16 m_RxDesLoopBackNum=0;
    U16 n_RxFrameLen=0;
    //U8* des;
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    U16 len,i;
    len = 0;

    p = (volatile GD_ETH_MAC_DesT*)((device->RxDesStartAddr) + device->CurRxDesSite * sizeof(GD_ETH_MAC_DesT));
    while((p->des0 & ETH_DES_R0_OWN) != ETH_DES_R0_OWN)
    {
#ifdef DEBUG_PRINT
        GM_Printf("@\n");
#endif

        if((p->des0 & (ETH_DES_R0_ES|ETH_DES_R0_LE|ETH_DES_R0_OE|ETH_DES_R0_GF|  \
            ETH_DES_R0_LC|ETH_DES_R0_RWT|ETH_DES_R0_RE|ETH_DES_R0_DL|ETH_DES_R0_CE)) != 0)
        {
#ifdef DEBUG_PRINT
            GM_Printf("RxDES0=0x%x\n",p->des0);
#endif
        }
        //else
        if((p->des0 & ETH_DES_R0_FT) != ETH_DES_R0_FT)
        {
#ifdef DEBUG_PRINT
            GM_Printf("other type frame\n",p->des0);
#endif
        }
        //else
        if((p->des0 & ETH_DES_R0_VLAN) == ETH_DES_R0_VLAN)
        {
#ifdef DEBUG_PRINT
            GM_Printf("Vlan frame\n",p->des0);
#endif
        }
        //else

        if(((p->des0) & ETH_DES_R0_FS) == ETH_DES_R0_FS)
        {
            revbuf=(volatile U8*)(p->des2);//buffer is adjacent. Be careful the last buffrer->the first buffer
            p_FrameStart=p;
            b_FrameStart=GTRUE;
            m_RxDesLoopBackNum=0;
            n_RxFrameLen=0;
            
            p_RxDesTmp=(volatile GD_ETH_MAC_DesT*)((device->RxDesStartAddr) + (device->RxbufferNum-1) * sizeof(GD_ETH_MAC_DesT));
            p_RxCopyBuf=(volatile U8 *)(p_RxDesTmp->des2+device->SizePerRxBuffer);

        }
        else if(b_FrameStart==GTRUE)//not only one buffer
        {  
            if(p==(volatile GD_ETH_MAC_DesT*)device->RxDesStartAddr)//(device->CurRxDesSite == 0)//loopback
            {
                m_RxDesLoopBackNum++;
            }
            else if(m_RxDesLoopBackNum != 0)
            {
                m_RxDesLoopBackNum++;
            }
        }

        if(((p->des0) & ETH_DES_R0_LS) == ETH_DES_R0_LS)
        {
            if(ethGetRxDescriptorDataSize(p,&len) == GFALSE)
            {
#ifdef DEBUG_PRINT
                GM_Printf("Get Rx data size fail, please check\n!");
#endif
                continue;
            }
#if !STRIP_CRC
            len -= 4;                       //strip the crc field
#endif

            if(m_RxDesLoopBackNum!=0)//copy buffer
            {
#ifdef DEBUG_PRINT
                GM_Printf("memcpy:SRC_ADDR=0x%08x\tDST_ADDR=0x%08x\tLEN=%d\n!",p_RxCopyBuf,p->des2,len-n_RxFrameLen);
#endif            
                p_RxSrcBuf=(U8 *)(p->des2);
                for(i=0;i<len-n_RxFrameLen;i++)
                {
                    *p_RxCopyBuf++=*p_RxSrcBuf++;
                }

/*                memcpy((void *)p_RxCopyBuf,(const void *)p_RxSrcBuf,len-n_RxFrameLen);               
                p_RxCopyBuf=p_RxCopyBuf+(len-n_RxFrameLen);    */ 

            }

            //for(j=0;j<len;j++)
            //des[j]=revbuf[j];
            if(device->eth_rcve)
            {
                device->eth_rcve(revbuf,len);
            }
           
            while(p_FrameStart!=p) //Host release all the Rx descriptors to FMAC3
            {

                p_FrameStart->des1 = ((p_FrameStart->des1) & ETH_DES_R1_RER) | device->SizePerRxBuffer;//device->SizePerRxBuffer <2048
                p_FrameStart->des2 = (U32)device->Rxbufferstart + device->CurRxDesSite * device->SizePerRxBuffer;
                p_FrameStart->des3 = 0x0;
                p_FrameStart->des0 = ETH_DES_R0_OWN;//owned by mac
				
                device->CurRxDesSite++;
                p_FrameStart++;
                if(device->CurRxDesSite == device->RxbufferNum)
                {
                    device->CurRxDesSite = 0;
                    p_FrameStart =(GD_ETH_MAC_DesT*) (device->RxDesStartAddr);
                }
                
            }


            p->des1 = ((p->des1) & ETH_DES_R1_RER) | device->SizePerRxBuffer;//device->SizePerRxBuffer <2048
            p->des2 = (U32)device->Rxbufferstart + device->CurRxDesSite * device->SizePerRxBuffer;
            p->des3 = 0x0;
            p->des0 = ETH_DES_R0_OWN;//owned by mac
			            
            device->CurRxDesSite++;
            if(device->CurRxDesSite == device->RxbufferNum)
            {
                device->CurRxDesSite = 0;
            }
            
            p = (volatile GD_ETH_MAC_DesT*)((device->RxDesStartAddr) + device->CurRxDesSite * sizeof(GD_ETH_MAC_DesT));
            
            b_FrameStart=GFALSE;
            m_RxDesLoopBackNum=0;
            n_RxFrameLen=0;          
        }
        else if(b_FrameStart==GTRUE)//not last buffer, the frame has two buffer at least
        {
            ethGetRxDescriptorDataSize(p,&len);//len==device->SizePerRxBuffer ,except for last buffer               
            n_RxFrameLen=n_RxFrameLen+len;
            if(m_RxDesLoopBackNum!=0)//copy buffer
            {
#ifdef DEBUG_PRINT
                GM_Printf("memcpy:SRC_ADDR=0x%08x\tDST_ADDR=0x%08x\tLEN=%d\n!",p_RxCopyBuf,p->des2,len);
#endif
                p_RxSrcBuf=(U8 *)(p->des2);
                for(i=0;i<len;i++)
                {
                    *p_RxCopyBuf++=*p_RxSrcBuf++;
                }
 
/*                memcpy((void *)p_RxCopyBuf,(const void *)p_RxSrcBuf,len);               
                p_RxCopyBuf=p_RxCopyBuf+len; */               
            }     

            if(p==p_RxDesTmp)
            {
                p=(volatile GD_ETH_MAC_DesT*)device->RxDesStartAddr;
            }
            else
            {
                p++;
            }
            //continue;    
        }
        else//error
        {
            //Host release the Rx descriptor to FMAC3
            p->des1 = ((p->des1) & ETH_DES_R1_RER) | device->SizePerRxBuffer;//device->SizePerRxBuffer <2048
            p->des2 = (U32)device->Rxbufferstart + device->CurRxDesSite * device->SizePerRxBuffer;
            p->des3 = 0x0;
            p->des0 = ETH_DES_R0_OWN;//owned by mac


            device->CurRxDesSite++;
            if(device->CurRxDesSite == device->RxbufferNum)
            {
                device->CurRxDesSite = 0;
            }
            p = (volatile GD_ETH_MAC_DesT*)((device->RxDesStartAddr) + device->CurRxDesSite * sizeof(GD_ETH_MAC_DesT));
            
            b_FrameStart=GFALSE;
            m_RxDesLoopBackNum=0;
            n_RxFrameLen=0;    
        }
    }
}

void ethStopDevice(GD_HANDLE handle, GD_ETH_RWE rw)
{
    U32 omr; //    = ETH_REG_OMR;
    U32 old_omr;// = omr;
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device==NULL)
        return;
    omr=GH_ETH_get_OMR();
    old_omr = omr;

    if((rw == GD_ETH_R)||(rw == GD_ETH_RW))
    {
        omr &= ~(ETH_REG_OMR_SR);//end receive
        device->StopFlag &= ~GD_ETH_RX_RUN;
        device->StopFlag &= ~GD_ETH_RX_SUSP_NOBUF;
        device->StopFlag &= ~GD_ETH_RX_SUSP_HWERR;
        device->StopFlag &= ~GD_ETH_RX_STOP_HWERR;

        device->StopFlag |= GD_ETH_RX_STOP;
    }

    if((rw == GD_ETH_W)||(rw == GD_ETH_RW))
    {
        omr &= ~(ETH_REG_OMR_ST);//end send
        device->StopFlag &= ~GD_ETH_TX_RUN;
        device->StopFlag &= ~GD_ETH_TX_SUSP_NODAT;
        device->StopFlag &= ~GD_ETH_TX_SUSP_HWERR;
        device->StopFlag &= ~GD_ETH_TX_STOP_HWERR;

        device->StopFlag |= GD_ETH_TX_STOP;
    }

    if ( omr != old_omr )
        GH_ETH_set_OMR(omr);

}

#if USE_FLOWCTL
void ethSendPause(void)
{
    U32 fcr;
    U32 timeout;

    for ( timeout = 0; timeout < 0x100; timeout++ )
    {
        //fcr = ETH_REG_FCR;
        fcr=GH_ETH_get_FCR();
        if ( (fcr & ETH_REG_FCR_FCB) == 0x0 )
            break;
    }
    if ( timeout >= 0x100 )
    {
        return;
    }
    fcr &= ~ETH_REG_FCR_PT;
    fcr |=  (0x1d0 << 16);//pause time
    fcr |= ETH_REG_FCR_FCB;
    //ETH_REG_FCR = fcr;
    GH_ETH_set_FCR(fcr);
}
#endif

/*
*****************************************************************************
** \brief calculate MCR value
**
** This function calculates and returns a value for
** initializing MCR (MAC Configuration Register).
**
** \param devId   Fmac3h device Id
**
** \return
**      MCR value
*****************************************************************************
*/
U32 ethSetupMCR(GD_HANDLE handle)
{
    U32 mcr = (U32)0;
    GD_ETH_HandleT* device = (GD_ETH_HandleT*)handle;
    if(device==NULL)
        return 0;

    if ( device->supJumbo == GTRUE)
    {
        mcr |= ETH_REG_MCR_WD;//disable watch dog
        mcr |= ETH_REG_MCR_JD;//disable jabber
        mcr |= ETH_REG_MCR_JE;//enable jumbo frame
    }
    if ( device->workmode.mode == GD_ETH_PHY_IF_MODE_GMII)
    {
        mcr &= ~ETH_REG_MCR_PS;
    }
    else
    {
        mcr |= ETH_REG_MCR_PS;  //MII
    }


    mcr &= ~ETH_REG_MCR_EM; //little endian


    if ( device->workmode.loopback == GD_ETH_LOOP_ON_MAC )
    {
        mcr |= ETH_REG_MCR_LM;
    }


    if ( device->workmode.duplex == GD_ETH_HALF_DUPLEX )
    {
        mcr &= ~ETH_REG_MCR_DM;
    }
    else
    {
        mcr |= ETH_REG_MCR_DM;  //mac loop back should excute here
    }

    mcr |= ETH_REG_MCR_APS; //auto pad stripping
    mcr |= ETH_REG_MCR_ACS; //auto crc stripping
    mcr |= ETH_REG_MCR_DC;  //deferral check
    mcr |= ETH_REG_MCR_TE;  //tx enable
    mcr |= ETH_REG_MCR_RE;  //rx enable
 //   mcr |= ETH_REG_MCR_DO;//disable receive own
    return mcr;

}

void ethDelay(void)
{
    U32 i = 0, j = 0;

    for(i=0;i<100000/6;i++)
    {
        for(i=0;i<1000000;i++)
        {
            GH_ETH_get_GAR();
        }
    }
}
