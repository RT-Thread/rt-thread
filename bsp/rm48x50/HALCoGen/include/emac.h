/**
 *  \file   emac.h
 *
 *  \brief  EMAC APIs and macros.
 *
 *   This file contains the driver API prototypes and macro definitions.
 */

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __EMAC_H__
#define __EMAC_H__

#include "sys_common.h"
#include "hw_emac.h"
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/*
** Macros which can be used as speed parameter to the API EMACRMIISpeedSet
*/
#define EMAC_RMIISPEED_10MBPS                 (0x00000000U)
#define EMAC_RMIISPEED_100MBPS                (0x00008000U)

/*
** Macros which can be used as duplexMode parameter to the API 
** EMACDuplexSet
*/
#define EMAC_DUPLEX_FULL                      (0x00000001U)
#define EMAC_DUPLEX_HALF                      (0x00000000U)

/*
** Macros which can be used as matchFilt  parameters to the API 
** EMACMACAddrSet
*/
/* Address not used to match/filter incoming packets */
#define EMAC_MACADDR_NO_MATCH_NO_FILTER       (0x00000000U)

/* Address will be used to filter incoming packets */
#define EMAC_MACADDR_FILTER                   (0x00100000U)

/* Address will be used to match incoming packets */
#define EMAC_MACADDR_MATCH                    (0x00180000U)

/*
** Macros which can be passed as eoiFlag to EMACRxIntAckToClear API
*/
#define EMAC_INT_CORE0_RX                     (0x1U)
#define EMAC_INT_CORE1_RX                     (0x5U)
#define EMAC_INT_CORE2_RX                     (0x9U)

/*
** Macros which can be passed as eoiFlag to EMACTxIntAckToClear API
*/
#define EMAC_INT_CORE0_TX                     (0x2U)
#define EMAC_INT_CORE1_TX                     (0x6U)
#define EMAC_INT_CORE2_TX                     (0xAU)

/*****************************************************************************/
/** 
 *  @defgroup EMACMDIO EMAC/MDIO
 *  @brief Ethernet Media Access Controller/Management Data Input/Output.
 *  
 *  The EMAC controls the flow of packet data from the system to the PHY. The MDIO module controls PHY
 *  configuration and status monitoring.
 *
 *  Both the EMAC and the MDIO modules interface to the system core through a custom interface that
 *  allows efficient data transmission and reception. This custom interface is referred to as the EMAC control
 *  module and is considered integral to the EMAC/MDIO peripheral
 *
 *	Related Files
 *   - emac.h
 *   - emac.c
 *   - hw_emac.h
 *   - hw_emac_ctrl.h
 *   - hw_mdio.h
 *   - hw_reg_access.h	
 *   - mdio.h
 *   - mdio.c
 *  @addtogroup EMACMDIO
 *  @{
 */
/*
** Prototypes for the APIs
*/
extern void EMACTxIntPulseEnable(uint32 emacBase, uint32 emacCtrlBase,
                                 uint32 ctrlCore, uint32 channel);
extern void EMACTxIntPulseDisable(uint32 emacBase, uint32 emacCtrlBase,
                                  uint32 ctrlCore, uint32 channel);
extern void EMACRxIntPulseEnable(uint32 emacBase, uint32 emacCtrlBase,
                                 uint32 ctrlCore, uint32 channel);
extern void EMACRxIntPulseDisable(uint32 emacBase, uint32 emacCtrlBase,
                                   uint32 ctrlCore, uint32 channel);
extern void EMACRMIISpeedSet(uint32 emacBase, uint32 speed);
extern void EMACDuplexSet(uint32 emacBase, uint32 duplexMode);
extern void EMACTxEnable(uint32 emacBase);
extern void EMACRxEnable(uint32 emacBase);
extern void EMACTxHdrDescPtrWrite(uint32 emacBase, uint32 descHdr,
                                  uint32 channel);
extern void EMACRxHdrDescPtrWrite(uint32 emacBase, uint32 descHdr,
                                  uint32 channel);
extern void EMACInit(uint32 emacCtrlBase, uint32 emacBase);
extern void EMACMACSrcAddrSet(uint32 emacBase, uint8 * macAddr);
extern void EMACMACAddrSet(uint32 emacBase, uint32 channel,
                           uint8 * macAddr, uint32 matchFilt);
extern void EMACMIIEnable(uint32 emacBase);
extern void EMACRxUnicastSet(uint32 emacBase, uint32 channel);
extern void EMACCoreIntAck(uint32 emacBase, uint32 eoiFlag);
extern void EMACTxCPWrite(uint32 emacBase, uint32 channel,
                          uint32 comPtr);
extern void EMACRxCPWrite(uint32 emacBase, uint32 channel,
                          uint32 comPtr);
extern void EMACRxBroadCastEnable(uint32 emacBase, uint32 channel);
extern void EMACNumFreeBufSet(uint32 emacBase, uint32 channel,
                              uint32 nBuf);
extern uint32 EMACIntVectorGet(uint32 emacBase);

#ifdef __cplusplus
}
#endif

/**@}*/
#endif /* __EMAC_H__ */
