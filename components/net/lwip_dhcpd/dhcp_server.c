/*
 * File      : dhcp_server.c
 *             A simple DHCP server implementation
 *
 * COPYRIGHT (C) 2011-2018, Shanghai Real-Thread Technology Co., Ltd
 * http://www.rt-thread.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-01-30     aozima       the first version
 * 2013-08-08     aozima       support different network segments.
 * 2015-01-30     bernard      release to RT-Thread RTOS.
 * 2017-12-27     aozima       add [mac-ip] table support.
 */

#include <stdio.h>
#include <stdint.h>
#include <rtthread.h>

#include <lwip/opt.h>
#include <lwip/sockets.h>
#include <lwip/inet_chksum.h>
#include <netif/etharp.h>
#include <netif/ethernetif.h>
#include <lwip/ip.h>
#include <lwip/init.h>

#if (LWIP_VERSION) >= 0x02000000U
    #include <lwip/prot/dhcp.h>
#endif

/* DHCP server option */

/* allocated client ip range */
#ifndef DHCPD_CLIENT_IP_MIN
    #define DHCPD_CLIENT_IP_MIN     2
#endif
#ifndef DHCPD_CLIENT_IP_MAX
    #define DHCPD_CLIENT_IP_MAX     254
#endif

/* the DHCP server address */
#ifndef DHCPD_SERVER_IP
    #define DHCPD_SERVER_IP "192.168.169.1"
#endif

//#define DHCP_DEBUG_PRINTF

#ifdef  DHCP_DEBUG_PRINTF
    #define DEBUG_PRINTF        rt_kprintf("[DHCP] "); rt_kprintf
#else
    #define DEBUG_PRINTF(...)
#endif /* DHCP_DEBUG_PRINTF */

/* we need some routines in the DHCP of lwIP */
#undef  LWIP_DHCP
#define LWIP_DHCP   1
#include <lwip/dhcp.h>

#ifndef DHCP_CLIENT_PORT
#define DHCP_CLIENT_PORT  68
#endif

#ifndef DHCP_SERVER_PORT
#define DHCP_SERVER_PORT  67
#endif

#ifndef ETHADDR32_COPY
#define ETHADDR32_COPY(dst, src)  SMEMCPY(dst, src, ETH_HWADDR_LEN)
#endif

#ifndef ETHADDR16_COPY
#define ETHADDR16_COPY(dst, src)  SMEMCPY(dst, src, ETH_HWADDR_LEN)
#endif

/* buffer size for receive DHCP packet */
#define BUFSZ               1024

#ifndef MAC_ADDR_LEN
    #define MAC_ADDR_LEN     6
#endif

#ifndef MAC_TABLE_LEN
    #define MAC_TABLE_LEN     4
#endif

struct mac_addr_t
{
    uint8_t add[MAC_ADDR_LEN];
};

struct mac_ip_item_t
{
    struct mac_addr_t mac_addr;
    uint8_t ip_addr_3;
};

static rt_err_t _low_level_dhcp_send(struct netif *netif,
                                     const void *buffer,
                                     rt_size_t size)
{
    struct pbuf *p;
    struct eth_hdr *ethhdr;
    struct ip_hdr *iphdr;
    struct udp_hdr *udphdr;

    p = pbuf_alloc(PBUF_LINK,
                   SIZEOF_ETH_HDR + sizeof(struct ip_hdr)
                   + sizeof(struct udp_hdr) + size,
                   PBUF_RAM);
    if (p == RT_NULL) return -RT_ENOMEM;

    ethhdr = (struct eth_hdr *)p->payload;
    iphdr  = (struct ip_hdr *)((char *)ethhdr + SIZEOF_ETH_HDR);
    udphdr = (struct udp_hdr *)((char *)iphdr + sizeof(struct ip_hdr));

    ETHADDR32_COPY(&ethhdr->dest, (struct eth_addr *)&ethbroadcast);
    ETHADDR16_COPY(&ethhdr->src, netif->hwaddr);
    ethhdr->type = PP_HTONS(ETHTYPE_IP);

    iphdr->src.addr  = 0x00000000; /* src: 0.0.0.0 */
    iphdr->dest.addr = 0xFFFFFFFF; /* src: 255.255.255.255 */

    IPH_VHL_SET(iphdr, 4, IP_HLEN / 4);
    IPH_TOS_SET(iphdr, 0x00);
    IPH_LEN_SET(iphdr, htons(IP_HLEN + sizeof(struct udp_hdr) + size));
    IPH_ID_SET(iphdr, htons(2));
    IPH_OFFSET_SET(iphdr, 0);
    IPH_TTL_SET(iphdr, 255);
    IPH_PROTO_SET(iphdr, IP_PROTO_UDP);
    IPH_CHKSUM_SET(iphdr, 0);
    IPH_CHKSUM_SET(iphdr, inet_chksum(iphdr, IP_HLEN));

    udphdr->src = htons(DHCP_SERVER_PORT);
    udphdr->dest = htons(DHCP_CLIENT_PORT);
    udphdr->len = htons(sizeof(struct udp_hdr) + size);
    udphdr->chksum = 0;

    memcpy((char *)udphdr + sizeof(struct udp_hdr),
           buffer, size);

    netif->linkoutput(netif, p);
    pbuf_free(p);

    return RT_EOK;
}

static uint8_t get_ip(struct mac_addr_t *p_mac_addr)
{
    static uint8_t next_client_ip = DHCPD_CLIENT_IP_MIN;
    static struct mac_ip_item_t mac_table[MAC_TABLE_LEN];
    static int offset = 0;

    struct mac_addr_t bad_mac;
    int i;
    uint8_t ip_addr_3;

    rt_memset(&bad_mac, 0, sizeof(bad_mac));
    if (!rt_memcmp(&bad_mac, p_mac_addr, sizeof(bad_mac)))
    {
        DEBUG_PRINTF("mac address all zero");
        ip_addr_3 = DHCPD_CLIENT_IP_MAX;
        goto _return;
    }

    rt_memset(&bad_mac, 0xFF, sizeof(bad_mac));
    if (!rt_memcmp(&bad_mac, p_mac_addr, sizeof(bad_mac)))
    {
        DEBUG_PRINTF("mac address all one");
        ip_addr_3 = DHCPD_CLIENT_IP_MAX;
        goto _return;
    }

    for (i = 0; i < MAC_TABLE_LEN; i++)
    {
        if (!rt_memcmp(&mac_table[i].mac_addr, p_mac_addr, sizeof(bad_mac)))
        {
            //use old ip
            ip_addr_3 = mac_table[i].ip_addr_3;
            DEBUG_PRINTF("return old ip: %d\n", (int)ip_addr_3);
            goto _return;
        }
    }

    /* add new ip */
    mac_table[offset].mac_addr = *p_mac_addr;
    mac_table[offset].ip_addr_3  = next_client_ip;
    ip_addr_3 = mac_table[offset].ip_addr_3 ;

    offset++;
    if (offset >= MAC_TABLE_LEN)
        offset = 0;

    next_client_ip++;
    if (next_client_ip > DHCPD_CLIENT_IP_MAX)
        next_client_ip = DHCPD_CLIENT_IP_MIN;

    DEBUG_PRINTF("create new ip: %d\n", (int)ip_addr_3);
    DEBUG_PRINTF("next_client_ip %d\n", next_client_ip);

_return:
    return ip_addr_3;
}

static void dhcpd_thread_entry(void *parameter)
{
    struct netif *netif = RT_NULL;
    int sock;
    int bytes_read;
    char *recv_data;
    rt_uint32_t addr_len;
    struct sockaddr_in server_addr, client_addr;
    struct dhcp_msg *msg;
    int optval = 1;
    struct mac_addr_t mac_addr;
    uint8_t DHCPD_SERVER_IPADDR0, DHCPD_SERVER_IPADDR1, DHCPD_SERVER_IPADDR2, DHCPD_SERVER_IPADDR3;

    /* get ethernet interface. */
    netif = (struct netif *) parameter;
    RT_ASSERT(netif != RT_NULL);

    /* our DHCP server information */
    {
#if (LWIP_VERSION) >= 0x02000000U
        ip4_addr_t addr;
        ip4addr_aton(DHCPD_SERVER_IP, &addr);
#else
        struct ip_addr addr;
        ipaddr_aton(DHCPD_SERVER_IP, &addr);
#endif /* LWIP_VERSION */

        DHCPD_SERVER_IPADDR0 = (ntohl(addr.addr) >> 24) & 0xFF;
        DHCPD_SERVER_IPADDR1 = (ntohl(addr.addr) >> 16) & 0xFF;
        DHCPD_SERVER_IPADDR2 = (ntohl(addr.addr) >>  8) & 0xFF;
        DHCPD_SERVER_IPADDR3 = (ntohl(addr.addr) >>  0) & 0xFF;
    }
    DEBUG_PRINTF("DHCP server IP: %d.%d.%d.%d  client IP: %d.%d.%d.%d-%d\n",
                 DHCPD_SERVER_IPADDR0, DHCPD_SERVER_IPADDR1,
                 DHCPD_SERVER_IPADDR2, DHCPD_SERVER_IPADDR3,
                 DHCPD_SERVER_IPADDR0, DHCPD_SERVER_IPADDR1,
                 DHCPD_SERVER_IPADDR2, DHCPD_CLIENT_IP_MIN, DHCPD_CLIENT_IP_MAX);

    /* allocate buffer for receive */
    recv_data = rt_malloc(BUFSZ);
    if (recv_data == RT_NULL)
    {
        /* No memory */
        DEBUG_PRINTF("Out of memory\n");
        return;
    }

    /* create a socket with UDP */
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        DEBUG_PRINTF("create socket failed, errno = %d\n", errno);
        rt_free(recv_data);
        return;
    }

    /* set to receive broadcast packet */
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));

    /* initialize server address */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(DHCP_SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    rt_memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    /* bind socket to the server address */
    if (bind(sock, (struct sockaddr *)&server_addr,
             sizeof(struct sockaddr)) == -1)
    {
        /* bind failed. */
        DEBUG_PRINTF("bind server address failed, errno=%d\n", errno);
        closesocket(sock);
        rt_free(recv_data);
        return;
    }

    addr_len = sizeof(struct sockaddr);
    DEBUG_PRINTF("DHCP server listen on port %d...\n", DHCP_SERVER_PORT);

    while (1)
    {
        bytes_read = recvfrom(sock, recv_data, BUFSZ - 1, 0,
                              (struct sockaddr *)&client_addr, &addr_len);
        if (bytes_read <= 0)
        {
            closesocket(sock);
            rt_free(recv_data);
            return;
        }
        else if (bytes_read < DHCP_MSG_LEN)
        {
            DEBUG_PRINTF("packet too short, wait for next!\n");
            continue;
        }

        msg = (struct dhcp_msg *)recv_data;
        /* check message type to make sure we can handle it */
        if ((msg->op != DHCP_BOOTREQUEST) || (msg->cookie != PP_HTONL(DHCP_MAGIC_COOKIE)))
        {
            continue;
        }

        memcpy(mac_addr.add, msg->chaddr, MAC_ADDR_LEN);

        /* handler. */
        {
            uint8_t *dhcp_opt;
            uint8_t option;
            uint8_t length;

            uint8_t message_type = 0;
            uint8_t finished = 0;
            uint32_t request_ip  = 0;

            uint8_t client_ip_3;

            client_ip_3 = get_ip(&mac_addr);

            dhcp_opt = (uint8_t *)msg + DHCP_OPTIONS_OFS;
            while (finished == 0)
            {
                option = *dhcp_opt;
                length = *(dhcp_opt + 1);

                switch (option)
                {
                case DHCP_OPTION_REQUESTED_IP:
                    request_ip = *(dhcp_opt + 2) << 24 | *(dhcp_opt + 3) << 16
                                 | *(dhcp_opt + 4) << 8 | *(dhcp_opt + 5);
                    break;

                case DHCP_OPTION_END:
                    finished = 1;
                    break;

                case DHCP_OPTION_MESSAGE_TYPE:
                    message_type = *(dhcp_opt + 2);
                    break;

                default:
                    break;
                } /* switch(option) */

                dhcp_opt += (2 + length);
            }

            /* reply. */
            dhcp_opt = (uint8_t *)msg + DHCP_OPTIONS_OFS;

            /* check. */
            if (request_ip)
            {
                uint32_t client_ip = DHCPD_SERVER_IPADDR0 << 24 | DHCPD_SERVER_IPADDR1 << 16
                                     | DHCPD_SERVER_IPADDR2 << 8 | client_ip_3;

                DEBUG_PRINTF("message_type: %d, request_ip: %08X, client_ip: %08X.\n", message_type, request_ip, client_ip);

                if (request_ip != client_ip)
                {
                    *dhcp_opt++ = DHCP_OPTION_MESSAGE_TYPE;
                    *dhcp_opt++ = DHCP_OPTION_MESSAGE_TYPE_LEN;
                    *dhcp_opt++ = DHCP_NAK;
                    *dhcp_opt++ = DHCP_OPTION_END;

                    DEBUG_PRINTF("requested IP invalid, reply DHCP_NAK\n");

                    if (netif != RT_NULL)
                    {
                        int send_byte = (dhcp_opt - (uint8_t *)msg);
                        _low_level_dhcp_send(netif, msg, send_byte);
                        DEBUG_PRINTF("DHCP server send %d byte\n", send_byte);
                    }

                    continue;
                }
            }

            if (message_type == DHCP_DISCOVER)
            {
                DEBUG_PRINTF("request DHCP_DISCOVER\n");
                DEBUG_PRINTF("reply   DHCP_OFFER\n");

                // DHCP_OPTION_MESSAGE_TYPE
                *dhcp_opt++ = DHCP_OPTION_MESSAGE_TYPE;
                *dhcp_opt++ = DHCP_OPTION_MESSAGE_TYPE_LEN;
                *dhcp_opt++ = DHCP_OFFER;

                // DHCP_OPTION_SERVER_ID
                *dhcp_opt++ = DHCP_OPTION_SERVER_ID;
                *dhcp_opt++ = 4;
                *dhcp_opt++ = DHCPD_SERVER_IPADDR0;
                *dhcp_opt++ = DHCPD_SERVER_IPADDR1;
                *dhcp_opt++ = DHCPD_SERVER_IPADDR2;
                *dhcp_opt++ = DHCPD_SERVER_IPADDR3;

                // DHCP_OPTION_LEASE_TIME
                *dhcp_opt++ = DHCP_OPTION_LEASE_TIME;
                *dhcp_opt++ = 4;
                *dhcp_opt++ = 0x00;
                *dhcp_opt++ = 0x01;
                *dhcp_opt++ = 0x51;
                *dhcp_opt++ = 0x80;
            }
            else if (message_type == DHCP_REQUEST)
            {
                DEBUG_PRINTF("request DHCP_REQUEST\n");
                DEBUG_PRINTF("reply   DHCP_ACK\n");

                // DHCP_OPTION_MESSAGE_TYPE
                *dhcp_opt++ = DHCP_OPTION_MESSAGE_TYPE;
                *dhcp_opt++ = DHCP_OPTION_MESSAGE_TYPE_LEN;
                *dhcp_opt++ = DHCP_ACK;

                // DHCP_OPTION_SERVER_ID
                *dhcp_opt++ = DHCP_OPTION_SERVER_ID;
                *dhcp_opt++ = 4;
                *dhcp_opt++ = DHCPD_SERVER_IPADDR0;
                *dhcp_opt++ = DHCPD_SERVER_IPADDR1;
                *dhcp_opt++ = DHCPD_SERVER_IPADDR2;
                *dhcp_opt++ = DHCPD_SERVER_IPADDR3;

                // DHCP_OPTION_SUBNET_MASK
                *dhcp_opt++ = DHCP_OPTION_SUBNET_MASK;
                *dhcp_opt++ = 4;
                *dhcp_opt++ = 0xFF;
                *dhcp_opt++ = 0xFF;
                *dhcp_opt++ = 0xFF;
                *dhcp_opt++ = 0x00;

#ifdef DHCPD_USING_ROUTER
                // DHCP_OPTION_ROUTER
                *dhcp_opt++ = DHCP_OPTION_ROUTER;
                *dhcp_opt++ = 4;
                *dhcp_opt++ = DHCPD_SERVER_IPADDR0;
                *dhcp_opt++ = DHCPD_SERVER_IPADDR1;
                *dhcp_opt++ = DHCPD_SERVER_IPADDR2;
                *dhcp_opt++ = 1;
#endif

                // DHCP_OPTION_DNS_SERVER, use the default DNS server address in lwIP
                *dhcp_opt++ = DHCP_OPTION_DNS_SERVER;
                *dhcp_opt++ = 4;

#ifndef DHCP_DNS_SERVER_IP
                *dhcp_opt++ = DHCPD_SERVER_IPADDR0;
                *dhcp_opt++ = DHCPD_SERVER_IPADDR1;
                *dhcp_opt++ = DHCPD_SERVER_IPADDR2;
                *dhcp_opt++ = 1;
#else
                {
#if (LWIP_VERSION) >= 0x02000000U
                    ip4_addr_t dns_addr;
#else
                    struct ip_addr dns_addr;
#endif /* LWIP_VERSION */
                    ip4addr_aton(DHCP_DNS_SERVER_IP, &dns_addr);

                    *dhcp_opt++ = (ntohl(dns_addr.addr) >> 24) & 0xFF;
                    *dhcp_opt++ = (ntohl(dns_addr.addr) >> 16) & 0xFF;
                    *dhcp_opt++ = (ntohl(dns_addr.addr) >>  8) & 0xFF;
                    *dhcp_opt++ = (ntohl(dns_addr.addr) >>  0) & 0xFF;
                }
#endif

                // DHCP_OPTION_LEASE_TIME
                *dhcp_opt++ = DHCP_OPTION_LEASE_TIME;
                *dhcp_opt++ = 4;
                *dhcp_opt++ = 0x00;
                *dhcp_opt++ = 0x01;
                *dhcp_opt++ = 0x51;
                *dhcp_opt++ = 0x80;
            }
            else
            {
                DEBUG_PRINTF("un handle message:%d\n", message_type);
            }

            // append DHCP_OPTION_END
            *dhcp_opt++ = DHCP_OPTION_END;

            /* send reply. */
            if ((message_type == DHCP_DISCOVER) || (message_type == DHCP_REQUEST))
            {
                msg->op = DHCP_BOOTREPLY;
                IP4_ADDR(&msg->yiaddr,
                         DHCPD_SERVER_IPADDR0, DHCPD_SERVER_IPADDR1,
                         DHCPD_SERVER_IPADDR2, client_ip_3);

                client_addr.sin_addr.s_addr = INADDR_BROADCAST;

                if (netif != RT_NULL)
                {
                    int send_byte = (dhcp_opt - (uint8_t *)msg);
                    _low_level_dhcp_send(netif, msg, send_byte);
                    DEBUG_PRINTF("DHCP server send %d byte\n", send_byte);
                }
            }
        } /* handler. */
    }
}

void dhcpd_start(const char *netif_name)
{
    rt_thread_t thread;
    struct netif *netif = netif_list;

    if (strlen(netif_name) > sizeof(netif->name))
    {
        rt_kprintf("network interface name too long!\r\n");
        return;
    }
    while (netif != RT_NULL)
    {
        if (strncmp(netif_name, netif->name, sizeof(netif->name)) == 0)
            break;

        netif = netif->next;
        if (netif == RT_NULL)
        {
            rt_kprintf("network interface: %s not found!\r\n", netif_name);
            return;
        }
    }

    if (1)
    {
        extern void set_if(const char *netif_name, const char *ip_addr, const char *gw_addr, const char *nm_addr);

        dhcp_stop(netif);

        set_if(netif_name, DHCPD_SERVER_IP, "0.0.0.0", "255.255.255.0");

        netif_set_up(netif);
    }

    thread = rt_thread_create("dhcpd",
                              dhcpd_thread_entry, netif,
                              1024,
                              RT_THREAD_PRIORITY_MAX - 3,
                              2);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
}
