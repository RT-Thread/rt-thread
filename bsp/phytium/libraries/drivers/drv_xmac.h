/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2022-07-07  liuzhihong   first commit
 * 2023-07-14  liuzhihong   support RT-Smart
 */
#ifndef __DRV_XMAC_H__
#define __DRV_XMAC_H__
#include <rtthread.h>
#include <rtdevice.h>

#include <netif/ethernetif.h>

#include "fxmac.h"
#include "fkernel.h"
#include "ferror_code.h"
#include "fassert.h"
#include "fcache.h"
#include "fxmac_bdring.h"
#include "eth_ieee_reg.h"
#include "fcpu_info.h"
#include "fdebug.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FREERTOS_XMAC_INIT_ERROR FT_CODE_ERR(ErrModPort, 0, 0x1)
#define FREERTOS_XMAC_PARAM_ERROR FT_CODE_ERR(ErrModPort, 0, 0x2)
#define FREERTOS_XMAC_NO_VALID_SPACE FT_CODE_ERR(ErrModPort, 0, 0x3)

#define FXMAX_RX_BDSPACE_LENGTH    0x20000 /* default set 128KB*/
#define FXMAX_TX_BDSPACE_LENGTH    0x20000 /* default set 128KB*/

#define FXMAX_RX_PBUFS_LENGTH       16
#define FXMAX_TX_PBUFS_LENGTH       16

#define FXMAX_MAX_HARDWARE_ADDRESS_LENGTH 6

/* configuration */
#define FXMAC_OS_CONFIG_JUMBO  BIT(0)
#define FXMAC_OS_CONFIG_MULTICAST_ADDRESS_FILITER  BIT(1) /* Allow multicast address filtering  */
#define FXMAC_OS_CONFIG_COPY_ALL_FRAMES BIT(2) /* enable copy all frames */
#define FXMAC_OS_CONFIG_CLOSE_FCS_CHECK BIT(3) /* close fcs check */
#define FXMAC_OS_CONFIG_RX_POLL_RECV BIT(4)  /* select poll mode */
/* Phy */
#define FXMAC_PHY_SPEED_10M    10
#define FXMAC_PHY_SPEED_100M    100
#define FXMAC_PHY_SPEED_1000M    1000

#define FXMAC_PHY_HALF_DUPLEX   0
#define FXMAC_PHY_FULL_DUPLEX   1

#define MAX_FRAME_SIZE_JUMBO (FXMAC_MTU_JUMBO + FXMAC_HDR_SIZE + FXMAC_TRL_SIZE)

/* Byte alignment of BDs */
#define BD_ALIGNMENT (FXMAC_DMABD_MINIMUM_ALIGNMENT*2)

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
    FXMAC_OS_INTERFACE_SGMII = 0,
    FXMAC_OS_INTERFACE_RMII,
    FXMAC_OS_INTERFACE_RGMII,
    FXMAC_OS_INTERFACE_LENGTH
} FXmacRtThreadInterface;


typedef struct
{
    u8 rx_bdspace[FXMAX_RX_BDSPACE_LENGTH] __attribute__((aligned(128))); /* 接收bd 缓冲区 */
    u8 tx_bdspace[FXMAX_RX_BDSPACE_LENGTH] __attribute__((aligned(128))); /* 发送bd 缓冲区 */

    uintptr rx_pbufs_storage[FXMAX_RX_PBUFS_LENGTH];
    uintptr tx_pbufs_storage[FXMAX_TX_PBUFS_LENGTH];

} FXmacNetifBuffer;

typedef struct
{
    u32 instance_id;
    FXmacRtThreadInterface interface;
    u32 autonegotiation; /* 1 is autonegotiation ,0 is manually set */
    u32 phy_speed;  /* FXMAC_PHY_SPEED_XXX */
    u32 phy_duplex; /* FXMAC_PHY_XXX_DUPLEX */
} FXmacOsControl;


typedef struct
{
    struct eth_device parent; /* inherit from ethernet device */

    FXmac instance; /* Xmac controller */
    FXmacOsControl mac_config;

    FXmacNetifBuffer buffer; /* DMA buffer */

    /* queue to store overflow packets */
    PqQueue recv_q;
    PqQueue send_q;

    /* configuration */
    u32 config;

    rt_uint8_t hwaddr[FXMAX_MAX_HARDWARE_ADDRESS_LENGTH]; /* MAC address */

    struct rt_thread _link_thread; /* link detect thread */
    rt_uint8_t _link_thread_stack[LINK_THREAD_STACK_LENGTH];/* link detect thread stack*/
} FXmacOs;

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
