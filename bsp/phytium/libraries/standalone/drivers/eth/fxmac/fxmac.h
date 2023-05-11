/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fxmac.h
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file is for gmac driver .Functions in this file are the minimum required functions
 * for this driver.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/06/16    first release
 */

#ifndef FXMAC_H
#define FXMAC_H

#include "ftypes.h"
#include "fassert.h"
#include "ferror_code.h"
#include "fxmac_hw.h"
#include "fxmac_bdring.h"
#include "fparameters.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define FXMAC_ERR_INVALID_PARAM FT_MAKE_ERRCODE(ErrModBsp, ErrBspEth, 0x1u)
#define FXMAC_ERR_SG_LIST FT_MAKE_ERRCODE(ErrModBsp, ErrBspEth, 0x2u)
#define FXMAC_ERR_GENERAL FT_MAKE_ERRCODE(ErrModBsp, ErrBspEth, 0x4u)
#define FXMAC_ERR_SG_NO_LIST FT_MAKE_ERRCODE(ErrModBsp, ErrBspEth, 0x5u)
#define FXMAC_ERR_PHY_BUSY FT_MAKE_ERRCODE(ErrModBsp, ErrBspEth, 0x6u)
#define FXMAC_PHY_IS_NOT_FOUND FT_MAKE_ERRCODE(ErrModBsp, ErrBspEth, 0x7u)
#define FXMAC_PHY_AUTO_AUTONEGOTIATION_FAILED FT_MAKE_ERRCODE(ErrModBsp, ErrBspEth, 0x8u)
#define FXMAC_ERR_MAC_IS_PROCESSING FT_MAKE_ERRCODE(ErrModBsp, ErrBspEth, 0x9u)

/** @name Configuration options
 *
 * Device configuration options. See the FXMAC_SetOptions(),
 * FXMACClearOptions() and FXMAC_GetOptions() for information on how to
 * use options.
 *
 * The default state of the options are noted and are what the device and
 * driver will be set to after calling FXMAC_Reset() or
 * FXMAC_Initialize().
 *
 * @{
 */

#define FXMAC_PROMISC_OPTION 0x00000001U
/* Accept all incoming packets.
 *   This option defaults to disabled (cleared) */

#define FXMAC_FRAME1536_OPTION 0x00000002U
/* Frame larger than 1516 support for Tx & Rx.x
 *   This option defaults to disabled (cleared) */

#define FXMAC_VLAN_OPTION 0x00000004U
/* VLAN Rx & Tx frame support.
 *   This option defaults to disabled (cleared) */

#define FXMAC_FLOW_CONTROL_OPTION 0x00000010U
/* Enable recognition of flow control frames on Rx
 *   This option defaults to enabled (set) */

#define FXMAC_FCS_STRIP_OPTION 0x00000020U
/* Strip FCS and PAD from incoming frames. Note: PAD from VLAN frames is not
 *   stripped.
 *   This option defaults to enabled (set) */

#define FXMAC_FCS_INSERT_OPTION 0x00000040U
/* Generate FCS field and add PAD automatically for outgoing frames.
 *   This option defaults to disabled (cleared) */

#define FXMAC_LENTYPE_ERR_OPTION 0x00000080U
/* Enable Length/Type error checking for incoming frames. When this option is
 *   set, the MAC will filter frames that have a mismatched type/length field
 *   and if FXMAC_REPORT_RXERR_OPTION is set, the user is notified when these
 *   types of frames are encountered. When this option is cleared, the MAC will
 *   allow these types of frames to be received.
 *
 *   This option defaults to disabled (cleared) */

#define FXMAC_TRANSMITTER_ENABLE_OPTION 0x00000100U
/* Enable the transmitter.
 *   This option defaults to enabled (set) */

#define FXMAC_RECEIVER_ENABLE_OPTION 0x00000200U
/* Enable the receiver
 *   This option defaults to enabled (set) */

#define FXMAC_BROADCAST_OPTION 0x00000400U
/* Allow reception of the broadcast address
 *   This option defaults to enabled (set) */

#define FXMAC_MULTICAST_OPTION 0x00000800U
/* Allows reception of multicast addresses programmed into hash
 *   This option defaults to disabled (clear) */

#define FXMAC_RX_CHKSUM_ENABLE_OPTION 0x00001000U
/* Enable the RX checksum offload
 *   This option defaults to enabled (set) */

#define FXMAC_TX_CHKSUM_ENABLE_OPTION 0x00002000U
/* Enable the TX checksum offload
 *   This option defaults to enabled (set) */

#define FXMAC_JUMBO_ENABLE_OPTION 0x00004000U
#define FXMAC_SGMII_ENABLE_OPTION 0x00008000U

#define FXMAC_LOOPBACK_NO_MII_OPTION 0x00010000U
#define FXMAC_LOOPBACK_USXGMII_OPTION 0x00020000U

#define FXMAC_GET_TXRING(instance) (instance.tx_bd_queue.bdring)
#define FXMAC_GET_RXRING(instance) (instance.rx_bd_queue.bdring)

#define FXMAC_DEFAULT_OPTIONS               \
    ((u32)FXMAC_FLOW_CONTROL_OPTION |       \
     (u32)FXMAC_FCS_INSERT_OPTION |         \
     (u32)FXMAC_FCS_STRIP_OPTION |          \
     (u32)FXMAC_BROADCAST_OPTION |          \
     (u32)FXMAC_LENTYPE_ERR_OPTION |        \
     (u32)FXMAC_TRANSMITTER_ENABLE_OPTION | \
     (u32)FXMAC_RECEIVER_ENABLE_OPTION |    \
     (u32)FXMAC_RX_CHKSUM_ENABLE_OPTION |   \
     (u32)FXMAC_TX_CHKSUM_ENABLE_OPTION)

typedef enum
{
    FXMAC_LINKDOWN = 0,
    FXMAC_LINKUP = 1,
    FXMAC_NEGOTIATING = 2
} FXmacLinkStatus;

/* The next few constants help upper layers determine the size of memory
 * pools used for Ethernet buffers and descriptor lists.
 */
#define FXMAC_MAC_ADDR_SIZE 6U /* size of Ethernet header */

#define FXMAC_MTU 1500U         /* max MTU size of Ethernet frame */
#define FXMAC_MTU_JUMBO 10240U  /* max MTU size of jumbo frame */
#define FXMAC_HDR_SIZE 14U      /* size of Ethernet header  , DA + SA + TYPE*/
#define FXMAC_HDR_VLAN_SIZE 18U /* size of Ethernet header with VLAN */
#define FXMAC_TRL_SIZE 4U       /* size of Ethernet trailer (FCS) */
#define FXMAC_MAX_FRAME_SIZE (FXMAC_MTU + FXMAC_HDR_SIZE + \
                              FXMAC_TRL_SIZE)
#define FXMAC_MAX_VLAN_FRAME_SIZE (FXMAC_MTU + FXMAC_HDR_SIZE + \
                                   FXMAC_HDR_VLAN_SIZE + FXMAC_TRL_SIZE)
#define FXMAC_MAX_VLAN_FRAME_SIZE_JUMBO (FXMAC_MTU_JUMBO + FXMAC_HDR_SIZE + \
        FXMAC_HDR_VLAN_SIZE + FXMAC_TRL_SIZE)

#define FXMAC_MAX_FRAME_SIZE_JUMBO (FXMAC_MTU_JUMBO + FXMAC_HDR_SIZE + FXMAC_TRL_SIZE)

/** @name Callback identifiers
 *
 * These constants are used as parameters to FXMAC_SetHandler()
 * @{
 */
#define FXMAC_HANDLER_DMASEND 1U        /* 发送中断 */
#define FXMAC_HANDLER_DMARECV 2U        /* 接收中断 */
#define FXMAC_HANDLER_ERROR 3U          /* 异常中断 */
#define FXMAC_HANDLER_LINKCHANGE 4U     /* 连接状态 */
#define FXMAC_HANDLER_RESTART 5U        /* 发送描述符队列发生异常 */
/*@}*/

#define FXMAC_DMA_SG_IS_STARTED 0
#define FXMAC_DMA_SG_IS_STOPED 1

#define FXMAC_SPEED_10 10U
#define FXMAC_SPEED_100 100U
#define FXMAC_SPEED_1000 1000U
#define FXMAC_SPEED_2500 2500U
#define FXMAC_SPEED_5000 5000U
#define FXMAC_SPEED_10000 10000U
#define FXMAC_SPEED_25000 25000U

/*  Capability mask bits */
#define FXMAC_CAPS_ISR_CLEAR_ON_WRITE   0x00000001 /* irq status parameters need to be written to clear after they have been read */


/** @name Direction identifiers
 *
 *  These are used by several functions and callbacks that need
 *  to specify whether an operation specifies a send or receive channel.
 * @{
 */
#define FXMAC_SEND 1U /* send direction */
#define FXMAC_RECV 2U /* receive direction */

/****************************************************************************/
/**
 *
 * This macro triggers trasmit circuit to send data currently in TX buffer(s).
 *
 * @param instance_p is a pointer to the FXmac instance to be worked on.
 *
 * @return
 *
 * @note
 *
 * Signature: void FXmacTransmit(FXmac *instance_p)
 *
 *****************************************************************************/
#define FXmacTransmit(instance_p)                                        \
    FXMAC_WRITEREG32((instance_p)->config.base_address,                  \
                     FXMAC_NWCTRL_OFFSET,                                \
                     (FXMAC_READREG32((instance_p)->config.base_address, \
                                      FXMAC_NWCTRL_OFFSET) |             \
                      FXMAC_NWCTRL_STARTTX_MASK))

typedef void (*FXmacIrqHandler)(void *args);
typedef void (*FXmacErrorIrqHandler)(void *args, u32 direction, u32 error_word);
/* Interface Mode definitions */
typedef enum
{
    FXMAC_PHY_INTERFACE_MODE_SGMII,
    FXMAC_PHY_INTERFACE_MODE_RMII,
    FXMAC_PHY_INTERFACE_MODE_RGMII,
    FXMAC_PHY_INTERFACE_MODE_XGMII,
    FXMAC_PHY_INTERFACE_MODE_USXGMII,
    FXMAC_PHY_INTERFACE_MODE_5GBASER ,
    FXMAC_PHY_INTERFACE_MODE_2500BASEX
} FXmacPhyInterface;

typedef struct
{
    u32 instance_id; /* Id of device*/
    volatile uintptr_t base_address;
    volatile uintptr_t extral_mode_base;
    volatile uintptr_t extral_loopback_base;
    FXmacPhyInterface interface;
    u32 speed;    /* FXMAC_SPEED_XXX */
    u32 duplex;   /* 1 is full-duplex , 0 is half-duplex */
    u32 auto_neg; /* Enable auto-negotiation - when set active high, autonegotiation operation is enabled. */
    u32 pclk_hz;
    u32 max_queue_num; /* Number of Xmac Controller Queues  */
    u32 tx_queue_id;   /* 0 ~ FXMAC_QUEUE_MAX_NUM ,Index queue number */
    u32 rx_queue_id;   /* 0 ~ FXMAC_QUEUE_MAX_NUM ,Index queue number */
    u32 hotplug_irq_num;
    u32 dma_brust_length; /*  burst length */
    u32 network_default_config;
    u32 queue_irq_num[FXMAC_QUEUE_MAX_NUM]; /* mac0 8个 ，其他的 4个 */
    u32 caps; /*  */
} FXmacConfig;

typedef struct
{
    u32 queue_id;
    FXmacBdRing bdring;
} FXmacQueue;

typedef struct
{
    FXmacConfig config;
    u32 is_ready; /* Device is ininitialized and ready*/
    u32 is_started;
    u32 link_status; /* indicates link status ,FXMAC_LINKUP is link up ,FXMAC_LINKDOWN is link down,FXMAC_NEGOTIATING is need to negotiating*/
    u32 options;
    u32 caps;   /*  Capability mask bits */

    FXmacQueue tx_bd_queue; /* Transmit Queue */
    FXmacQueue rx_bd_queue; /* Receive Queue */

    FXmacIrqHandler send_irq_handler;
    void *send_args;

    FXmacIrqHandler recv_irq_handler;
    void *recv_args;

    FXmacErrorIrqHandler error_irq_handler;
    void *error_args;

    FXmacIrqHandler link_change_handler;
    void *link_change_args;

    FXmacIrqHandler restart_handler;
    void *restart_args;

    u32 moudle_id; /* Module identification number */
    u32 max_mtu_size;
    u32 max_frame_size;

    u32 phy_address;   /* phy address */
    u32 rxbuf_mask;    /* 1000,100,10 */

} FXmac;

/* fxmac_sinit.c */
const FXmacConfig *FXmacLookupConfig(u32 instance_id);

/* fgmac.c */
FError FXmacCfgInitialize(FXmac *instance_p, const FXmacConfig *config_p);

void FXmacInitInterface(FXmac *instance_p);

void FXmacGetMacAddress(FXmac *instance_p, u8 *address_ptr, u8 index);
FError FXmacSetMacAddress(FXmac *instance_p, u8 *address_ptr, u8 index);

FError FXmacSetOptions(FXmac *instance_p, u32 options, u32 queue_num);
FError FXmacClearOptions(FXmac *instance_p, u32 options, u32 queue_num);
boolean FXmacUsxLinkStatus(FXmac *instance_p);

void FXmacStart(FXmac *instance_p);
void FXmacStop(FXmac *instance_p);
void FXmacSetQueuePtr(FXmac *instance_p, uintptr QPtr, u8 QueueNum,
                      u32 direction);

/* phy interface */
FError FXmacPhyWrite(FXmac *instance_p, u32 phy_address,
                     u32 register_num, u16 phy_data);

FError FXmacPhyRead(FXmac *instance_p, u32 phy_address,
                    u32 register_num, u16 *phydat_aptr);

FError FXmacPhyInit(FXmac *instance_p, u32 speed, u32 duplex_mode, u32 autonegotiation_en);

void FXmacSelectClk(FXmac *instance_p);

FError FXmacSetHandler(FXmac *instance_p, u32 handler_type, void *func_pointer, void *call_back_ref);
/* interrupt */
void FXmacIntrHandler(s32 vector, void *args);

void FXmacClearHash(FXmac *instance_p);


/* debug */
void FXmacDebugTxPrint(FXmac *instance_p);
void FXmacDebugRxPrint(FXmac *instance_p);
void FXmacDebugUsxPrint(FXmac *instance_p);

#ifdef __cplusplus
}
#endif

#endif // !
