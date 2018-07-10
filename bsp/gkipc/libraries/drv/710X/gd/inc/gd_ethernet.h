/*!
*****************************************************************************
** \file        gd_lib/GK7101/inc/gd_ethernet.h
**
** \version     2.0
**
** \date        Sept 09, 2014
**
** \author      Steven Yu
**
** \brief       Ethernet Driver.
**
** This application allows testing of the ethernet function.
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS.
**
** (C) Copyright 2002 - 2014 by Goke Microelectronics Shanghai WSC
**
*******************************************************************************
*/
//#define PRINT_ETH_LOG

#ifndef _GD_ETHERNET_H_
#define _GD_ETHERNET_H_
#include "gtypes.h"
#include <gmodids.h>
#include "gd_gpio.h"



//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************
/* Length of Ethernet Mac address in bytes (Do NOT change) */
#define GD_ETH_MAC_ADDR_NUM        (6)
typedef U8 GD_ETH_MacT[GD_ETH_MAC_ADDR_NUM];
#define GD_ETH_IP_ADDR_NUM        (4)
typedef U8 GD_ETH_IpT[GD_ETH_IP_ADDR_NUM];

#define GD_ETH_ERR_BASE   (GD_ETH_MODULE_ID << 16)



//*****************************************************************************
//*****************************************************************************
//** Enumerated types
//*****************************************************************************
//*****************************************************************************
enum
{
    GD_ERR_ETH_NOT_SUPPORTED = GD_ETH_ERR_BASE, //!< Device not supported.
    GD_ERR_ETH_NOT_OPEN,
    GD_ERR_ETH_PHY_NOT_EXIST,
    GD_ERR_ETH_PHY_RW,
    GD_ERR_ETH_PHY_OTHER,
    GD_ERR_ETH_MAC_NOT_OK,
    GD_ERR_ETH_LINK_DOWN,
    GD_ERR_ETH_TB_OVER,
    GD_ERR_ETH_NO_TD,
};

/*!
*************************************************************************
** \brief Version of Ethernet driver.
**
** This number consists of a \b major version number stored in bits
** 16 to 31 (upper word) and a \b minor version number stored in bits
** 0 to 15 (lower word).
** - The \b major number has to be increased when a parameter change
**   occurs for the existing driver's API after its first release.
** - The \b minor number has to be increased when functions are added to
**   the existing driver's API after its first release.
**
** \note This value has to be assigned to the \b version field of the
**       GD_ETH_OpenParamsT structure.
*************************************************************************
*/
typedef enum
{
    GD_ETH_VERSION = 0x00020000 //!< The current driver version
}GD_ETH_VersionE;

/*!
*************************************************************************
** \brief internal Or external PHY for Ethernet driver.
**
** Indicate speed setting.
** Used on GD_ETH_Open() and GD_ETH_GetStat()
*************************************************************************
*/
typedef enum
{
    GD_ETH_PHY_INTERNAL = 0,    //!<Enet MAC use internal PHY
    GD_ETH_PHY_EXTERNAL_1,      //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_2,      //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_3,      //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_4,      //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_5,      //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_6,      //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_7,      //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_8,      //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_9,      //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_10,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_11,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_12,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_13,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_14,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_15,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_16,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_17,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_18,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_19,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_20,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_21,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_22,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_23,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_24,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_25,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_26,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_27,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_28,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_29,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_30,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_31,     //!<Enet MAC use external PHY
    GD_ETH_PHY_EXTERNAL_AUTO,   //!<Enet MAC use external PHY
}GD_ETH_PHY_AddrE;

/*!
*************************************************************************
** \brief speed parameter for Ethernet driver.
**
** Indicate speed setting.
** Used on GD_ETH_Open() and GD_ETH_GetStat()
*************************************************************************
*/
typedef enum
{
    GD_ETH_SPEED_AUTO  =   0,   //!< Auto-negotiation
    GD_ETH_SPEED_10M   =  10,   //!< 10Mbps
    GD_ETH_SPEED_100M  = 100,   //!< 100Mbps
    GD_ETH_SPEED_1000M = 1000,  //!< 1000Mbps
}GD_ETH_SpeedE;

/*!
*************************************************************************
** \brief duplex mode parameter for Ethernet driver.
**
** Indicate duplex mode setting.
** Used on GD_ETH_Open() and GD_ETH_GetStat()
*************************************************************************
*/
typedef enum
{
    GD_ETH_HALF_DUPLEX  = 0,//!< half-duplex mode
    GD_ETH_FULL_DUPLEX  = 1 //!< full-duplex mode
}GD_ETH_DuplexE;

/*!
*************************************************************************
** \brief local ethWorkMode.loop mode parameter for Ethernet driver.
**
** Indicate local ethWorkMode.loop mode setting.
** Used on GD_ETH_Open()
**
** \note local ethWorkMode.loop mode is for debug purpose. general applications
**       should specify #GD_ETH_LOOP_OFF only.
*************************************************************************
*/
typedef enum
{
    GD_ETH_LOOP_OFF     = 0,//!< ethWorkMode.loop off
    GD_ETH_LOOP_ON_MAC  = 1,//!< ethWorkMode.loop on LAN(MAC) device
    GD_ETH_LOOP_ON_PHY  = 2 //!< ethWorkMode.loop on PHY device
}GD_ETH_LoopE;

/*!
*************************************************************************
** \brief link status parameter for Ethernet driver.
**
** Indicate link status.
** Used on GD_ETH_GetStat()
*************************************************************************
*/
typedef enum
{
    GD_ETH_LINKDOWN    = 0, //!< link is down
    GD_ETH_LINKUP      = 1, //!< link is up
    GD_ETH_LINKUNKNOWN = 2  //!< link status is unknown
}GD_ETH_LinkE;

/*!
*************************************************************************
** \brief detailed error status for Ethernet driver.
**
** Indicate detailed error status.
** Used on GD_ETH_GetStat()
**
** \note It depends on ethernet hardware. So other values may
**       be added in future version.
*************************************************************************
*/
typedef enum
{
    GD_ETH_ERR_NONE      = 0x00000000,//!< No error, normal running
    GD_ETH_ERR_SW        = 0x00000001,//!< Fatal error by software(bug)
    GD_ETH_ERR_FATAL     = 0x00000001,//!< Fatal error by software(bug)
    GD_ETH_ERR_RX_BUS    = 0x00000002,//!< Bus error in receiving
    GD_ETH_ERR_RWT_MAX   = 0x00000008,//!< Excessive Watchdog timeout error
    GD_ETH_ERR_RX_BAND   = 0x00000020,//!< Overflow error in receiving
    GD_ETH_ERR_RX_CONFIG = 0x00000080,//!< Feature not supported (Jumbo frames)

    GD_ETH_ERR_TX_BUS    = 0x00000004,//!< Bus error in transmitting
    GD_ETH_ERR_TJT_MAX   = 0x00000010,//!< Excessive Jabber timeout error
    GD_ETH_ERR_TX_BAND   = 0x00000040,//!< Underflow error in transmitting
    GD_ETH_ERR_TX_CONFIG = 0x00000100,//!< Feature not supported (Jumbo frames)
    GD_ETH_ERR_LATE_COL  = 0x00000200,//!< Excessive late collision error

}GD_ETH_ErrorE;


typedef enum
{
    GD_ETH_UNINITIALIZE  = 0x00000000,
    GD_ETH_FATAL_ERROR   = 0x00000001,
    GD_ETH_UNKNOWN       = 0x00000002,
    GD_ETH_RX_RUN        = 0x00000004,
    GD_ETH_RX_SUSP_NOBUF = 0x00000008,
    GD_ETH_RX_SUSP_HWERR = 0x00000010,
    GD_ETH_RX_STOP       = 0x00000020,
    GD_ETH_RX_STOP_HWERR = 0x00000040,
    GD_ETH_TX_RUN        = 0x00000080,
    GD_ETH_TX_SUSP_NODAT = 0x00000100,
    GD_ETH_TX_SUSP_HWERR = 0x00000200,
    GD_ETH_TX_STOP       = 0x00000400,
    GD_ETH_TX_STOP_HWERR = 0x00000800,
} GD_ETH_StatE;

typedef enum
{
    GD_ETH_R  = 0x00000001,
    GD_ETH_W  = 0x00000002,
    GD_ETH_RW = 0x00000003
} GD_ETH_RWE;

/*!
*************************************************************************
** \brief Frame end flag for Ethernet driver.
**
** Indicate whether frame reaches to end or not. It is passed as an argument of
** read/write to indicate a boundary of ethernet frame.
** Used on GD_ETH_Write() and GD_ETH_Read().
*************************************************************************
*/
typedef enum
{
    GD_ETH_FRAME_NOTEND   =  0x00000000,//!< frame does not end.
    GD_ETH_FRAME_END      =  0x00000001,//!< frame ends.
    GD_ETH_FRAME_TERM     =  0x00000002 //!< frame ends on error
} GD_ETH_FrameEndE;

typedef enum
{
    GD_ETH_PHY_IF_MODE_MII,
    GD_ETH_PHY_IF_MODE_GMII,
    GD_ETH_PHY_IF_MODE_SGMII,
    GD_ETH_PHY_IF_MODE_TBI,
    GD_ETH_PHY_IF_MODE_RMII,
    GD_ETH_PHY_IF_MODE_RGMII,
    GD_ETH_PHY_IF_MODE_RGMII_ID,
    GD_ETH_PHY_IF_MODE_RGMII_RXID,
    GD_ETH_PHY_IF_MODE_RGMII_TXID,
    GD_ETH_PHY_IF_MODE_RTBI,
    GD_ETH_PHY_IF_MODE_XGMII,
    GD_ETH_PHY_IF_MODE_NONE /* Must be last */
}GD_ETH_PHY_IF_E;   /* Phy Interface */


//*****************************************************************************
//*****************************************************************************
//** Data Structures
//*****************************************************************************
//*****************************************************************************

/*!
*************************************************************************
** \brief Status information about Ethernet driver and link status.
**
** This data structure contains information about the current ethernet
** driver settings and link status.
**
** \sa GD_ETH_GetStat
*************************************************************************
*/
typedef struct
{
    GBOOL           bEnAutoNeg;
    GD_ETH_SpeedE   speed;          //!< speed setting
    GD_ETH_DuplexE  duplex;         //!< duplex mode setting
    GD_ETH_LoopE    loopback;       //!< local loopback mode setting
    GD_ETH_PHY_IF_E mode;           //!<
}GD_ETH_Work_ModeT;

/*!
*************************************************************************
** \brief Status information about Ethernet driver and link status.
**
** This data structure contains information about the current ethernet
** driver settings and link status.
**
** \sa GD_ETH_GetStat
*************************************************************************
*/
typedef struct
{
    GD_ETH_SpeedE   speed;      //!< speed setting
    GD_ETH_DuplexE  duplex;     //!< duplex mode setting
    GD_ETH_LoopE    loopback;   //!< local loopback mode setting
    GD_ETH_PHY_IF_E mode;       //!<
    GD_ETH_LinkE    linkup;     //!< link is up or not
    GD_ETH_ErrorE   error;      //!< error details (if available)
}GD_ETH_StatParamsT;

/*!
 *************************************************************************
 ** \brief Open parameters for Ethernet driver.
 **
 ** This data structure contains all the parameters for GD_ETH_Open().
 **
 ** \sa GD_ETH_Open
 *************************************************************************
 */
typedef struct
{
    GBOOL               bHWReset;
    GD_GPIO_PIN_E       phyreset;
	U8                  phyType;
} GD_ETH_InitParamsT;

/*!
 *************************************************************************
 ** \brief Open parameters for Ethernet driver.
 **
 ** This data structure contains all the parameters for GD_ETH_Open().
 **
 ** \sa GD_ETH_Open
 *************************************************************************
 */
typedef struct
{
    GD_ETH_PHY_AddrE    addr;
    GD_ETH_Work_ModeT   workmode;
    GD_ETH_MacT         macaddr;
    GD_ETH_IpT          ipaddr;
} GD_ETH_OpenParamsT;


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

GERR GD_ETH_Init(GD_ETH_InitParamsT* pInitParams);
GERR GD_ETH_Exit(void);
GERR GD_ETH_Open(GD_ETH_OpenParamsT* pOpenParams, GD_HANDLE* pHandle);
GERR GD_ETH_Close(GD_HANDLE* pHandle);
S32  GD_ETH_Read(GD_HANDLE handle, char *bufPtr, S32 size, GD_ETH_FrameEndE *pframe);
S32  GD_ETH_Write(GD_HANDLE handle, const char* bufPtr, S32 size, GD_ETH_FrameEndE frame);
GERR GD_ETH_Write_HD(GD_HANDLE handle, const char* HbufPtr, S32 Hsize, const char* DbufPtr, S32 Dsize, GD_ETH_FrameEndE frame);
GERR GD_ETH_SetEMACSpeed(GD_HANDLE handle, GD_ETH_SpeedE speed);
GERR GD_ETH_SetMacAddress(GD_HANDLE handle, GD_ETH_MacT macAddress);
GERR GD_ETH_GetMacAddress(GD_HANDLE handle, GD_ETH_MacT* pmacAddress);
GERR GD_ETH_SetIPAddress(GD_HANDLE handle, GD_ETH_IpT ipAddress);
GERR GD_ETH_GetIPAddress(GD_HANDLE handle, GD_ETH_IpT* pipAddress);
GERR GD_ETH_GetPhyAddress(GD_HANDLE handle, U8* phy);
GERR GD_ETH_GetStat(GD_HANDLE handle, GD_ETH_StatParamsT *statParamsPtr);
GERR GD_ETH_CheckLink(GD_HANDLE handle);
GERR GD_ETH_SleepTime(U32 ulTime);
void GD_ETH_SetNetReceiveFuc(void (*eth_rcve)(volatile U8* recbuf,U16 len));


#ifdef __cplusplus
}
#endif

#endif /* _GD_ETHERNET_H_ */

