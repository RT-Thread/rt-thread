/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2025-05-28  huangjin     first commit
 */
#ifndef __DRV_XMAC_MSG_H__
#define __DRV_XMAC_MSG_H__
#include <rtthread.h>
#include <rtdevice.h>

#ifdef BSP_USING_ETH_MSG

#include <netif/ethernetif.h>

#include "fxmac_msg.h"
#include "fkernel.h"
#include "ferror_code.h"
#include "fassert.h"
#include "fxmac_msg_bdring.h"
#include "eth_ieee_reg.h"
#include "fcpu_info.h"
#include "fxmac_msg_phy.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RTTHREAD_XMAC_MSG_INIT_ERROR        FT_CODE_ERR(ErrModPort, 0, 0x1)
#define RTTHREAD_XMAC_MSG_PARAM_ERROR       FT_CODE_ERR(ErrModPort, 0, 0x2)
#define RTTHREAD_XMAC_MSG_NO_VALID_SPACE    FT_CODE_ERR(ErrModPort, 0, 0x3)

#define FXMAC_MSG_RX_BDSPACE_LENGTH    0x20000 /* default set 128KB*/
#define FXMAC_MSG_TX_BDSPACE_LENGTH    0x20000 /* default set 128KB*/

#define FXMAC_MSG_RX_PBUFS_LENGTH       64
#define FXMAC_MSG_TX_PBUFS_LENGTH       64

#define FXMAC_MSG_MAX_HARDWARE_ADDRESS_LENGTH 6

#define XMAC_MSG_PHY_RESET_ENABLE 1
#define XMAC_MSG_PHY_RESET_DISABLE 0

/* configuration */
#define FXMAC_MSG_OS_CONFIG_JUMBO  BIT(0)
#define FXMAC_MSG_OS_CONFIG_MULTICAST_ADDRESS_FILITER  BIT(1) /* Allow multicast address filtering  */
#define FXMAC_MSG_OS_CONFIG_COPY_ALL_FRAMES BIT(2) /* enable copy all frames */
#define FXMAC_MSG_OS_CONFIG_CLOSE_FCS_CHECK BIT(3) /* close fcs check */
#define FXMAC_MSG_OS_CONFIG_RX_POLL_RECV BIT(4)  /* select poll mode */
#define FXMAC_MSG_OS_CONFIG_UNICAST_ADDRESS_FILITER BIT(5) /* Allow unicast address filtering  */
/* Phy */
#define FXMAC_MSG_PHY_SPEED_10M    10
#define FXMAC_MSG_PHY_SPEED_100M    100
#define FXMAC_MSG_PHY_SPEED_1000M    1000

#define FXMAC_MSG_PHY_HALF_DUPLEX   0
#define FXMAC_MSG_PHY_FULL_DUPLEX   1

#define MAX_FRAME_SIZE_JUMBO (FXMAC_MSG_MTU_JUMBO + FXMAC_MSG_HDR_SIZE + FXMAC_MSG_TRL_SIZE)

/* Byte alignment of BDs */
#define BD_ALIGNMENT (FXMAC_MSG_DMABD_MINIMUM_ALIGNMENT*2)

/*  frame queue */
#define PQ_QUEUE_SIZE 4096

#define LINK_THREAD_STACK_LENGTH 0x20400


typedef struct
{
    uintptr data[PQ_QUEUE_SIZE];
    int head, tail, len;
} PqQueue;

typedef enum
{
    FXMAC_MSG_OS_INTERFACE_SGMII = 0,
    FXMAC_MSG_OS_INTERFACE_RMII,
    FXMAC_MSG_OS_INTERFACE_RGMII,
    FXMAC_MSG_OS_INTERFACE_LENGTH
} FXmacMsgRtThreadInterface;


typedef struct
{
    u8 rx_bdspace[FXMAC_MSG_RX_BDSPACE_LENGTH] __attribute__((aligned(128))); /* 接收bd 缓冲区 */
    u8 tx_bdspace[FXMAC_MSG_RX_BDSPACE_LENGTH] __attribute__((aligned(128))); /* 发送bd 缓冲区 */

    uintptr rx_pbufs_storage[FXMAC_MSG_RX_PBUFS_LENGTH];
    uintptr tx_pbufs_storage[FXMAC_MSG_TX_PBUFS_LENGTH];

} FXmacMsgNetifBuffer;

typedef struct
{
    u32 instance_id;
    FXmacMsgRtThreadInterface interface;
    u32 autonegotiation; /* 1 is autonegotiation ,0 is manually set */
    u32 phy_speed;  /* FXMAC_PHY_SPEED_XXX */
    u32 phy_duplex; /* FXMAC_PHY_XXX_DUPLEX */
} FXmacMsgOsControl;


typedef struct
{
    struct eth_device parent; /* inherit from ethernet device */

    FXmacMsgCtrl instance; /* Xmac controller */
    FXmacMsgOsControl mac_config;

    FXmacMsgNetifBuffer buffer; /* DMA buffer */

    /* queue to store overflow packets */
    PqQueue recv_q;
    PqQueue send_q;

    /* configuration */
    u32 config;
    u32 is_link_up;
    rt_uint8_t hwaddr[FXMAC_MSG_MAX_HARDWARE_ADDRESS_LENGTH]; /* MAC address */

    struct rt_thread _link_thread; /* link detect thread */
    rt_uint8_t _link_thread_stack[LINK_THREAD_STACK_LENGTH];/* link detect thread stack*/
} FXmacMsgOs;

enum lwip_port_link_status
{
    ETH_LINK_UNDEFINED = 0,
    ETH_LINK_UP,
    ETH_LINK_DOWN,
    ETH_LINK_NEGOTIATING
};



#ifdef __cplusplus
}
#endif

#endif // !

#endif
