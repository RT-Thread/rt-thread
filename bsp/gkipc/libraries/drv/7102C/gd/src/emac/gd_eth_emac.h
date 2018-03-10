/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/emac/gd_eth_emac.h
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
#ifndef _GD_ETH_EMAC_H_
#define _GD_ETH_EMAC_H_
#include "gtypes.h"



//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************
#define GD_ETH_PHY_MAX_REG_NUM  32
//-----------GAR---------------------MDC GMII address register
#define ETH_REG_GAR_SHIFT_PA            (11)        //Physical layer address
#define ETH_REG_GAR_SHIFT_GR            (6)         //GMII/MII register
#define ETH_REG_GAR_SHIFT_CR            (2)         //Application clock range
#define ETH_REG_GAR_GW                  (1<<1)      //GMII/MII write
#define ETH_REG_GAR_GB                  (1<<0)      //GMII/MII busy

//-----------BMR---------------------MDC bus mode reg
#define ETH_REG_BMR_SWRST               (1<<0)
#define ETH_REG_BMR_PBL1                (1<<8)
#define ETH_REG_BMR_PBL2                (2<<8)
#define ETH_REG_BMR_PBL4                (4<<8)
#define ETH_REG_BMR_PBL8                (8<<8)
#define ETH_REG_BMR_PBL16               (16<<8)
#define ETH_REG_BMR_PBL32               (32<<8)     //if set, all internal regs of F_MAC3H is reset

//-----------IER---------------------MDC INT enable
#define ETH_REG_IER_TI                   (1<<0)     //transmit int
#define ETH_REG_IER_TS                   (1<<1)     //transmit process stopped
#define ETH_REG_IER_TU                   (1<<2)     //transmit buf unavailable
#define ETH_REG_IER_TJ                   (1<<3)     //transmit jabber timeout
#define ETH_REG_IER_OVF                  (1<<4)     //
#define ETH_REG_IER_UN                   (1<<5)     //transmit underflow
#define ETH_REG_IER_RI                   (1<<6)     //receive int
#define ETH_REG_IER_RU                   (1<<7)     //reveive buf unavailable
#define ETH_REG_IER_RS                   (1<<8)     //reveive process stopped
#define ETH_REG_IER_RW                   (1<<9)     //reveive watchdog timeout
#define ETH_REG_IER_ETE                  (1<<10)    //early transmit int
#define ETH_REG_IER_FBE                  (1<<13)    //fatal bus error
#define ETH_REG_IER_ERE                  (1<<14)    //early reveive int
#define ETH_REG_IER_AI                   (1<<15)    //abnormal int
#define ETH_REG_IER_NI                   (1<<16)    //normal int

//---------------MCR----------------------MAC configuration reg
#define ETH_REG_MCR_RE                   (1<<2)     //reveive enable
#define ETH_REG_MCR_TE                   (1<<3)     //transmit enable
#define ETH_REG_MCR_DC                   (1<<4)     //deferral check
#define ETH_REG_MCR_BL                   (3<<5)     //back-off limit
#define ETH_REG_MCR_ACS                  (1<<7)     //automatic crc stripping
#define ETH_REG_MCR_APS                  (1<<8)     //automatic pad stripping
#define ETH_REG_MCR_DR                   (1<<9)     //disable retry
#define ETH_REG_MCR_DM                   (1<<11)    //duplex mode
#define ETH_REG_MCR_LM                   (1<<12)    //loop_back mode
#define ETH_REG_MCR_DO                   (1<<13)    //disable receive own
#define ETH_REG_MCR_EM                   (1<<14)    //Endian mode
#define ETH_REG_MCR_PS                   (1<<15)    //port select(0-GMII / 1-MII)
#define ETH_REG_MCR_JE                   (1<<20)    //Jumbo frame enable
#define ETH_REG_MCR_BE                   (1<<21)    //frame burst enable
#define ETH_REG_MCR_JD                   (1<<22)    //jabber disable
#define ETH_REG_MCR_WD                   (1<<23)    //watchdog disable

//---------------MFFR----------------------MAC frame filter reg
#define ETH_REG_MFFR_PR                   (1<<0)    //promiscuous mode
#define ETH_REG_MFFR_HP                   (1<<1)    //hash/perfect filtering mode
#define ETH_REG_MFFR_HO                   (1<<2)    //hash only filtering mode
#define ETH_REG_MFFR_IF                   (1<<3)    //inverse filtering
#define ETH_REG_MFFR_PM                   (1<<4)    //pass all multicast
#define ETH_REG_MFFR_DB                   (1<<5)    //disable broadcast frame
#define ETH_REG_MFFR_PCF                  (1<<7)    //pass control frames
#define ETH_REG_MFFR_RA                   0x80000000   //(1<<31)   //revceive all

//---------------FCR----------------------flow control reg
#define ETH_REG_FCR_FCB                   (1<<0)    //flow control busy
#define ETH_REG_FCR_TFE                   (1<<1)    //
#define ETH_REG_FCR_RFE                   (1<<2)    //receive flow control enable
#define ETH_REG_FCR_UP                    (1<<3)    //unicast pause frame detect
#define ETH_REG_FCR_PT                    (0xffff<<16)  //pause time

//---------------OMR----------------------MDC operation mode reg
#define ETH_REG_OMR_SR                    (1<<1)    //start/stop receive
#define ETH_REG_OMR_OSF                   (1<<2)    //operate on second frame
#define ETH_REG_OMR_ST                    (1<<13)   //start/stop transmit
#define ETH_REG_OMR_TTC                   (7<<14)   //transmit threshold control
#define ETH_REG_OMR_SF                    (1<<21)   //store and forward

//---------------SR------------------------MDC status reg
#define ETH_REG_SR_TI                   (1<<0)      //transmit int(frame complete)
#define ETH_REG_SR_TPS                  (1<<1)      //transmit process stopped
#define ETH_REG_SR_TU                   (1<<2)      //transmit buf unavailable
#define ETH_REG_SR_TJT                  (1<<3)      //transmit jabber timeout
#define ETH_REG_SR_OVF                  (1<<4)      //
#define ETH_REG_SR_UNF                  (1<<5)      //transmit underflow
#define ETH_REG_SR_RI                   (1<<6)      //receive int(frame complete)
#define ETH_REG_SR_RU                   (1<<7)      //reveive buf unavailable
#define ETH_REG_SR_RPS                  (1<<8)      //receive process stopped
#define ETH_REG_SR_RWT                  (1<<9)      //reveive watchdog timeout
#define ETH_REG_SR_ETI                  (1<<10)     //early transmit int
#define ETH_REG_SR_FBE                  (1<<13)     //fatal bus error
#define ETH_REG_SR_ERI                  (1<<14)     //early receive int
#define ETH_REG_SR_AIS                  (1<<15)     //abnormal int summary
#define ETH_REG_SR_NIS                  (1<<16)     //normal int summary
#define ETH_REG_SR_RS                   (7<<17)     //(not int)receive process state
#define ETH_REG_SR_TS                   (7<<20)     //(not int)transmit process state
#define ETH_REG_SR_EB                   (7<<23)     //(not int)error bits(1-host abort during transmit / 2-host abort during receive)

#define ETH_REG_SR_TXEB                 (1<<23)     //
#define ETH_REG_SR_RXEB                 (2<<23)     //

//---------------RDES0------------------------
#define ETH_DES_R0_RMA                 (1<<0)       //RX MAC Address
#define ETH_DES_R0_CE                  (1<<1)       //crc error
#define ETH_DES_R0_DL                  (1<<2)       //Dribble Bit Error
#define ETH_DES_R0_RE                  (1<<3)       //receive error
#define ETH_DES_R0_RWT                 (1<<4)       //receive watchdog timeout
#define ETH_DES_R0_FT                  (1<<5)       //frame type
#define ETH_DES_R0_LC                  (1<<6)       //late conllision
#define ETH_DES_R0_GF                  (1<<7)       //giant frame
#define ETH_DES_R0_LS                  (1<<8)       //last descriptor
#define ETH_DES_R0_FS                  (1<<9)       //first descriptor
#define ETH_DES_R0_VLAN                (1<<10)      //vlan frame is received
#define ETH_DES_R0_OE                  (1<<11)      //overflow error
#define ETH_DES_R0_LE                  (1<<12)      //length error
#define ETH_DES_R0_SAF                 (1<<13)      //Source Address Filter Fail
#define ETH_DES_R0_DE                  (1<<14)      //descriptor length
#define ETH_DES_R0_ES                  (1<<15)      //error summary
#define ETH_DES_R0_FL                  (0x3fff<<16) //frame length
#define ETH_DES_R0_AFM                 (1<<30)      //Destination Address Filter Fail
#define ETH_DES_R0_OWN                 0x80000000   //(1<<31)      //OWN bit

//---------------RDES1------------------------
#define ETH_DES_R1_RBS1                (0x7ff<<0)   //receive buf1 size
#define ETH_DES_R1_RBS2                (0x7ff<<11)  //receive buf2 size
#define ETH_DES_R1_RCH                 (1<<24)      //second address chained
#define ETH_DES_R1_RER                 (1<<25)      //receive end of ring
#define ETH_DES_R1_DIC                 0x80000000   //(1<<31)      //Disable Interrupt on Completion

//---------------TDES0------------------------
#define ETH_DES_T0_DB                  (1<<0)       //defferal bit
#define ETH_DES_T0_UF                  (1<<1)       //underflow error
#define ETH_DES_T0_ED                  (1<<2)       //excessive defferal
#define ETH_DES_T0_CC                  (0xf<<3)     //collision count
#define ETH_DES_T0_VF                  (1<<7)       //vlan frame
#define ETH_DES_T0_EC                  (1<<8)       //excessive collision
#define ETH_DES_T0_LCO                 (1<<9)       //late collision
#define ETH_DES_T0_NC                  (1<<10)      //no carrier
#define ETH_DES_T0_LC                  (1<<11)      //loss of carrier
#define ETH_DES_T0_FF                  (1<<13)      //Frame Flushed
#define ETH_DES_T0_JT                  (1<<14)      //jabber timeout
#define ETH_DES_T0_ES                  (1<<15)      //error summary
#define ETH_DES_T0_OWN                 0x80000000   //(1<<31)      //OWN bit

//---------------TDES1------------------------
#define ETH_DES_T1_TBS1                (0x7ff<<0)   //transmit buf1 size
#define ETH_DES_T1_TBS2                (0x7ff<<11)  //transmit buf2 size
#define ETH_DES_T1_DP                  (1<<23)      //disable padding
#define ETH_DES_T1_TCH                 (1<<24)      //second address chained
#define ETH_DES_T1_TER                 (1<<25)      //transmit end of ring
#define ETH_DES_T1_DC                  (1<<26)      //disable crc
#define ETH_DES_T1_FS                  (1<<29)      //first segment
#define ETH_DES_T1_LS                  (1<<30)      //last segment
#define ETH_DES_T1_IC                  0x80000000   //(1<<31)        //int on collision



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
    U32    des0;    //record the status information of the rx/tx
    U32    des1;    //rx/tx buffer size
    U32    des2;    //rx/tx buffer address which the current description pointed to
    U32    des3;    //reserved
} GD_ETH_MAC_DesT;



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
void gmcSWError(GD_HANDLE handle);
void ethLCErr(GD_HANDLE handle, GBOOL IsRx);
void ethRUInt(GD_HANDLE handle);
void ethOVFInt(GD_HANDLE handle);
void ethRWTInt(GD_HANDLE handle);
void ethTUInt(GD_HANDLE handle);
void ethUNFInt(GD_HANDLE handle);
void ethTJTInt(GD_HANDLE handle);
void ethFBEInt(GD_HANDLE handle, U32 sr);
void ethHandleIntRx(GD_HANDLE handle);
void ethHandleIntTx(GD_HANDLE handle);
U32 ethSetupMCR(GD_HANDLE handle);

void GD_ETH_StartDevice(GD_HANDLE handle, GD_ETH_RWE IsRx);
GBOOL GD_ETH_CheckPhyBusy(void);
GBOOL GD_ETH_ReadPhy(U8 phyAddr, U8 phyReg, U32* phyRegValue);
GBOOL GD_ETH_WritePhy(U8 phyAddr, U8 phyReg, U32 phyRegVal);
GERR GD_ETH_PHY_HWReset(GD_HANDLE handle);


#ifdef __cplusplus
extern "C" {
#endif

GISR1 GD_ETH_Isr(void);


#ifdef __cplusplus
}
#endif



#endif /* _GD_ETH_EMAC_H_ */

