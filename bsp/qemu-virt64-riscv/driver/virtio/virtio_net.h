/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 */

#ifndef __VIRTIO_NET_H__
#define __VIRTIO_NET_H__

#ifdef RT_USING_VIRTIO_NET

#include <rtdef.h>
#include <netif/ethernetif.h>

#include <virtio.h>

#define VIRTIO_NET_QUEUE_RX         0
#define VIRTIO_NET_QUEUE_TX         1
#define VIRTIO_NET_RTX_QUEUE_SIZE   16
#define VIRTIO_NET_RTX_BUF_SIZE     2048

#define VIRTIO_NET_F_CSUM                   0   /* Host handles pkts w/ partial csum */
#define VIRTIO_NET_F_GUEST_CSUM             1   /* Guest handles pkts w/ partial csum */
#define VIRTIO_NET_F_CTRL_GUEST_OFFLOADS    2   /* Dynamic offload configuration */
#define VIRTIO_NET_F_MTU                    3   /* Initial MTU advice */
#define VIRTIO_NET_F_MAC                    5   /* Host has given MAC address */
#define VIRTIO_NET_F_GUEST_TSO4             7   /* Guest can handle TSOv4 in */
#define VIRTIO_NET_F_GUEST_TSO6             8   /* Guest can handle TSOv6 in */
#define VIRTIO_NET_F_GUEST_ECN              9   /* Guest can handle TSO[6] w/ ECN in */
#define VIRTIO_NET_F_GUEST_UFO              10  /* Guest can handle UFO in */
#define VIRTIO_NET_F_HOST_TSO4              11  /* Host can handle TSOv4 in */
#define VIRTIO_NET_F_HOST_TSO6              12  /* Host can handle TSOv6 in */
#define VIRTIO_NET_F_HOST_ECN               13  /* Host can handle TSO[6] w/ ECN in */
#define VIRTIO_NET_F_HOST_UFO               14  /* Host can handle UFO in */
#define VIRTIO_NET_F_MRG_RXBUF              15  /* Host can merge receive buffers. */
#define VIRTIO_NET_F_STATUS                 16  /* virtio_net_config.status available */
#define VIRTIO_NET_F_CTRL_VQ                17  /* Control channel available */
#define VIRTIO_NET_F_CTRL_RX                18  /* Control channel RX mode support */
#define VIRTIO_NET_F_CTRL_VLAN              19  /* Control channel VLAN filtering */
#define VIRTIO_NET_F_CTRL_RX_EXTRA          20  /* Extra RX mode control support */
#define VIRTIO_NET_F_GUEST_ANNOUNCE         21  /* Guest can announce device on the network */
#define VIRTIO_NET_F_MQ                     22  /* Device supports Receive Flow Steering */
#define VIRTIO_NET_F_CTRL_MAC_ADDR          23  /* Set MAC address */

#define VIRTIO_NET_F_HASH_REPORT            57  /* Supports hash report */
#define VIRTIO_NET_F_RSS                    60  /* Supports RSS RX steering */
#define VIRTIO_NET_F_RSC_EXT                61  /* Extended coalescing info */
#define VIRTIO_NET_F_STANDBY                62  /* Act as standby for another device with the same MAC */
#define VIRTIO_NET_F_SPEED_DUPLEX           63  /* Device set linkspeed and duplex */

#define VIRTIO_NET_S_LINK_UP        (1 << 0)
#define VIRTIO_NET_S_ANNOUNCE       (1 << 1)

#define VIRTIO_NET_HDR_F_NEEDS_CSUM 1
#define VIRTIO_NET_HDR_F_DATA_VALID 2
#define VIRTIO_NET_HDR_F_RSC_INFO   4

#define VIRTIO_NET_HDR_GSO_NONE     0
#define VIRTIO_NET_HDR_GSO_TCPV4    1
#define VIRTIO_NET_HDR_GSO_UDP      3
#define VIRTIO_NET_HDR_GSO_TCPV6    4
#define VIRTIO_NET_HDR_GSO_ECN      0x80

struct virtio_net_hdr
{
    rt_uint8_t flags;
    rt_uint8_t gso_type;
    rt_uint16_t hdr_len;
    rt_uint16_t gso_size;
    rt_uint16_t csum_start;
    rt_uint16_t csum_offset;
    rt_uint16_t num_buffers;
} __attribute__ ((packed));

#define VIRTIO_NET_MSS              1514
#define VIRTIO_NET_HDR_SIZE         (sizeof(struct virtio_net_hdr))
#define VIRTIO_NET_PAYLOAD_MAX_SIZE (VIRTIO_NET_HDR_SIZE + VIRTIO_NET_MSS)

struct virtio_net_config
{
    rt_uint8_t mac[6];
    rt_uint16_t status;
    rt_uint16_t max_virtqueue_pairs;
    rt_uint16_t mtu;
    rt_uint32_t speed;
    rt_uint8_t duplex;
    rt_uint8_t rss_max_key_size;
    rt_uint16_t rss_max_indirection_table_length;
    rt_uint32_t supported_hash_types;
} __attribute__((packed));

struct virtio_net_device
{
    struct eth_device parent;

    struct virtio_device virtio_dev;

    struct virtio_net_config *config;

    struct
    {
        /* Transmit hdr */
        struct virtio_net_hdr hdr;
        /* Transmit buffer */
        rt_uint8_t tx_buffer[VIRTIO_NET_PAYLOAD_MAX_SIZE];
        /* Receive buffer */
        rt_uint8_t rx_buffer[VIRTIO_NET_PAYLOAD_MAX_SIZE];
    } info[VIRTIO_NET_RTX_QUEUE_SIZE];
};

rt_err_t rt_virtio_net_init(rt_ubase_t *mmio_base, rt_uint32_t irq);

#endif /* RT_USING_VIRTIO_NET */

#endif /* __VIRTIO_NET_H__ */
