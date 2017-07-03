/*
 * File      : dhcp_server.c
 *             A simple DHCP server implementation
 *
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013-2015, Shanghai Real-Thread Technology Co., Ltd
 * http://www.rt-thread.com
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-01-30     aozima       the first version
 * 2013-08-08     aozima       support different network segments.
 * 2015-01-30     bernard      release to RT-Thread RTOS.
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

#ifndef DHCPD_ADDR_CACHE_MAX
#define DHCPD_ADDR_CACHE_MAX       5
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

/* buffer size for receive DHCP packet */
#define BUFSZ               1024

/* unique 6-byte MAC address */
typedef struct mac_addr
{
    uint8_t octet[6];
}mac_addr_t;

static mac_addr_t cached_mac_addr[DHCPD_ADDR_CACHE_MAX];
static ip_addr_t  cached_ip_addr [DHCPD_ADDR_CACHE_MAX];

static rt_err_t get_client_addr_form_cache(const mac_addr_t *mac_addr, 
                                            ip_addr_t *ip_addr)
{
    rt_uint32_t i;

    /* Check whether device is already cached */
    for (i = 0; i < DHCPD_ADDR_CACHE_MAX; i ++)
    {
        if (memcmp(&cached_mac_addr[i], mac_addr, sizeof(*mac_addr)) == 0)
        {
            *ip_addr = cached_ip_addr[i];
            return RT_EOK;
        }
    }

    return -RT_EEMPTY;
}

static rt_err_t add_client_addr_to_cache(const mac_addr_t *mac_addr, 
                                            const ip_addr_t *ip_addr)
{
    rt_uint32_t i;
    rt_uint32_t first_empty_slot = DHCPD_ADDR_CACHE_MAX;
    rt_uint32_t cached_slot = DHCPD_ADDR_CACHE_MAX;

    static const mac_addr_t zero_mac_addr = {0};

    /* Search for empty slot in cache */
    for (i = 0; i < DHCPD_ADDR_CACHE_MAX; i ++)
    {
        /* Check for matching MAC address */
        if (memcmp(&cached_mac_addr[i], mac_addr, sizeof(*mac_addr)) == 0)
        {
            /* Cached device found */
            cached_slot = i;
            break;
        }
        else if (first_empty_slot == DHCPD_ADDR_CACHE_MAX && 
                !memcmp(&cached_mac_addr[i], &zero_mac_addr, 6))
        {
            /* Device not found in cache. Return the first empty slot */
            first_empty_slot = i;
        }
    }

    if (cached_slot != DHCPD_ADDR_CACHE_MAX)
    {
        /* Update IP address of cached device */
        cached_ip_addr[cached_slot] = *ip_addr;
    }
    else if (first_empty_slot != DHCPD_ADDR_CACHE_MAX)
    {
        /* Add device to the first empty slot */
        cached_mac_addr[first_empty_slot] = *mac_addr;
        cached_ip_addr [first_empty_slot] = *ip_addr;
    }
    else
    {
        /* Cache is full. Add device to slot 0 */
        cached_mac_addr[0] = *mac_addr;
        cached_ip_addr [0] = *ip_addr;
    }

    return RT_EOK;
}

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

static void dhcpd_thread_entry(void *parameter)
{
    uint32_t dhcpd_ip_addr;
    uint32_t dhcpd_netmask;
    uint32_t subnet;
    uint32_t ip_mask;
    uint32_t first_ip_addr;
    uint32_t final_ip_addr;
    uint32_t next_ip_addr;

    struct netif *netif = RT_NULL;
    int sock;
    int bytes_read;
    char *recv_data;
    rt_uint32_t addr_len;
    struct sockaddr_in server_addr, client_addr;
    struct dhcp_msg *msg;
    int optval = 1;

    /* get ethernet interface. */
    netif = (struct netif*) parameter;
    RT_ASSERT(netif != RT_NULL);
    
    memset(cached_ip_addr, 0, sizeof(cached_ip_addr));
    memset(cached_mac_addr, 0, sizeof(cached_mac_addr));

    /* save local IP address and netmask to be sent in DHCP packets */
    dhcpd_ip_addr = ip4_addr_get_u32(&netif->ip_addr);
    dhcpd_netmask = ip4_addr_get_u32(&netif->netmask);

    /* calculate the first available IP address which will be served */
    subnet = dhcpd_ip_addr & dhcpd_netmask;
    ip_mask = ~dhcpd_netmask;
    first_ip_addr = subnet | ((dhcpd_ip_addr + htonl(1UL)) & ip_mask);
    final_ip_addr = subnet | (ip_mask - htonl(1UL));
    next_ip_addr = first_ip_addr;

    /* our DHCP server information */
    DEBUG_PRINTF("DHCP server IP: %d.%d.%d.%d\n",
                ((uint8_t *)&dhcpd_ip_addr)[0], ((uint8_t *)&dhcpd_ip_addr)[1],
                ((uint8_t *)&dhcpd_ip_addr)[2], ((uint8_t *)&dhcpd_ip_addr)[3]);
    DEBUG_PRINTF("DHCP client IP: %d.%d.%d.%d - %d.%d.%d.%d\n",
                ((uint8_t *)&first_ip_addr)[0], ((uint8_t *)&first_ip_addr)[1],
                ((uint8_t *)&first_ip_addr)[2], ((uint8_t *)&first_ip_addr)[3],
                ((uint8_t *)&final_ip_addr)[0], ((uint8_t *)&final_ip_addr)[1],
                ((uint8_t *)&final_ip_addr)[2], ((uint8_t *)&final_ip_addr)[3]);
    
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
    
    /* set receive timeout value: 1s */
    optval = 1000;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &optval, sizeof(optval));

    /* initialize server address */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(DHCP_SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    /* bind socket to the server address */
    if (bind(sock, (struct sockaddr *)&server_addr,
             sizeof(struct sockaddr)) == -1)
    {
        /* bind failed. */
        DEBUG_PRINTF("bind server address failed, errno=%d\n", errno);
        rt_free(recv_data);
        return;
    }

    addr_len = sizeof(struct sockaddr);
    DEBUG_PRINTF("DHCP server listen on port %d...\n", DHCP_SERVER_PORT);

    while (rt_thread_self()->user_data == RT_TRUE)
    {
        bytes_read = recvfrom(sock, recv_data, BUFSZ - 1, 0,
                              (struct sockaddr *)&client_addr, &addr_len);
        if (bytes_read < DHCP_MSG_LEN)
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

        /* handler. */
        {
            uint8_t *dhcp_opt;
            uint8_t option;
            uint8_t length;

            uint8_t message_type = 0;
            uint8_t finished = 0;

            ip_addr_t request_ip_addr;
            ip_addr_t given_ip_addr;
            ip_addr_t reply_ip_addr;
            
            /* record client MAC address */
            mac_addr_t client_mac_addr = *(mac_addr_t *)msg->chaddr;
            
            dhcp_opt = msg->options;
            while (finished == 0)
            {
                option = *dhcp_opt;
                length = *(dhcp_opt + 1);

                switch (option)
                {
                case DHCP_OPTION_REQUESTED_IP:
                    /* keep requested IP address */
                    request_ip_addr = *(ip_addr_t *)(dhcp_opt + 2);
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
            dhcp_opt = msg->options;
            if (message_type == DHCP_DISCOVER)
            {
                DEBUG_PRINTF("request DHCP_DISCOVER\n");
                DEBUG_PRINTF("reply   DHCP_OFFER\n");
                
                /* check whether device is already cached */
                if (get_client_addr_form_cache(&client_mac_addr, 
                                                &reply_ip_addr) != RT_EOK)
                {
                    /* address not found and use next available IP address */
                    reply_ip_addr = *(ip_addr_t *)&next_ip_addr;
                }

                /* create the IP address for the offer */
                memcpy(&msg->yiaddr, &reply_ip_addr, sizeof(ip_addr_t));
                
                // DHCP_OPTION_MESSAGE_TYPE
                *dhcp_opt++ = DHCP_OPTION_MESSAGE_TYPE;
                *dhcp_opt++ = DHCP_OPTION_MESSAGE_TYPE_LEN;
                *dhcp_opt++ = DHCP_OFFER;

                // DHCP_OPTION_SERVER_ID
                *dhcp_opt++ = DHCP_OPTION_SERVER_ID;
                *dhcp_opt++ = 4;
                *dhcp_opt++ = ((uint8_t *)&dhcpd_ip_addr)[0];
                *dhcp_opt++ = ((uint8_t *)&dhcpd_ip_addr)[1];
                *dhcp_opt++ = ((uint8_t *)&dhcpd_ip_addr)[2];
                *dhcp_opt++ = ((uint8_t *)&dhcpd_ip_addr)[3];

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
                rt_bool_t next_ip_addr_used = RT_FALSE;

                DEBUG_PRINTF("request DHCP_REQUEST\n");
                DEBUG_PRINTF("reply   DHCP_ACK\n");

                /* check if device is cached, if so, give the previous IP address */
                if (get_client_addr_form_cache(&client_mac_addr, 
                                                &given_ip_addr) != RT_EOK)
                {
                    /* address not found and use next available IP address */
                    given_ip_addr = *(ip_addr_t *)&next_ip_addr;
                    next_ip_addr_used = RT_TRUE;
                }
                
                /* check if the requested IP address matches one we have assigned */
                if (!memcmp(&request_ip_addr, &given_ip_addr, sizeof(ip_addr_t)))
                {
                    /* Request is for next available IP */
                    /* create the IP address for the offer */
                    memcpy(&msg->yiaddr, &given_ip_addr, sizeof(ip_addr_t));

                    if (next_ip_addr_used == RT_TRUE)
                    {
                        /* increment next available IP address only if not found in cache */
                        do {
                            next_ip_addr = subnet | ((next_ip_addr + htonl(1UL)) & ip_mask);
                        }while(ntohl(final_ip_addr) < ntohl(next_ip_addr) && 
                                ntohl(first_ip_addr) > ntohl(next_ip_addr));
                    }

                    /* cache client */
                    add_client_addr_to_cache(&client_mac_addr, &given_ip_addr);
                }
                else
                {
                    /* Request is not for the assigned IP */
                    /* clear IP address */
                    memset(&msg->yiaddr, 0, sizeof(msg->yiaddr));

                    // DHCP_OPTION_SERVER_ID
                    *dhcp_opt++ = DHCP_OPTION_SERVER_ID;
                    *dhcp_opt++ = 4;
                    *dhcp_opt++ = ((uint8_t *)&dhcpd_ip_addr)[0];
                    *dhcp_opt++ = ((uint8_t *)&dhcpd_ip_addr)[1];
                    *dhcp_opt++ = ((uint8_t *)&dhcpd_ip_addr)[2];
                    *dhcp_opt++ = ((uint8_t *)&dhcpd_ip_addr)[3];

                    // DHCP_OPTION_MESSAGE_TYPE
                    *dhcp_opt++ = DHCP_OPTION_MESSAGE_TYPE;
                    *dhcp_opt++ = DHCP_OPTION_MESSAGE_TYPE_LEN;
                    *dhcp_opt++ = DHCP_NAK;
                    *dhcp_opt++ = DHCP_OPTION_END;
                    
                    /* force client to take next available IP by sending NAK */
                    DEBUG_PRINTF("requested IP invalid, reply DHCP_NAK\n");
                    if (netif != RT_NULL)
                    {
                        int send_byte = (dhcp_opt - (rt_uint8_t *)msg);
                        _low_level_dhcp_send(netif, msg, send_byte);
                        DEBUG_PRINTF("DHCP server send %d byte\n", send_byte);
                    }
                    continue;
                }

                // DHCP_OPTION_MESSAGE_TYPE
                *dhcp_opt++ = DHCP_OPTION_MESSAGE_TYPE;
                *dhcp_opt++ = DHCP_OPTION_MESSAGE_TYPE_LEN;
                *dhcp_opt++ = DHCP_ACK;

                // DHCP_OPTION_SERVER_ID
                *dhcp_opt++ = DHCP_OPTION_SERVER_ID;
                *dhcp_opt++ = 4;
                *dhcp_opt++ = ((uint8_t *)&dhcpd_ip_addr)[0];
                *dhcp_opt++ = ((uint8_t *)&dhcpd_ip_addr)[1];
                *dhcp_opt++ = ((uint8_t *)&dhcpd_ip_addr)[2];
                *dhcp_opt++ = ((uint8_t *)&dhcpd_ip_addr)[3];

                // DHCP_OPTION_SUBNET_MASK
                *dhcp_opt++ = DHCP_OPTION_SUBNET_MASK;
                *dhcp_opt++ = 4;
                *dhcp_opt++ = ((uint8_t *)&dhcpd_netmask)[0];
                *dhcp_opt++ = ((uint8_t *)&dhcpd_netmask)[1];
                *dhcp_opt++ = ((uint8_t *)&dhcpd_netmask)[2];
                *dhcp_opt++ = ((uint8_t *)&dhcpd_netmask)[3];

#ifdef DHCPD_USING_ROUTER
                // DHCP_OPTION_ROUTER
                *dhcp_opt++ = DHCP_OPTION_ROUTER;
                *dhcp_opt++ = 4;
                *dhcp_opt++ = ((uint8_t *)&dhcpd_ip_addr)[0];
                *dhcp_opt++ = ((uint8_t *)&dhcpd_ip_addr)[1];
                *dhcp_opt++ = ((uint8_t *)&dhcpd_ip_addr)[2];
                *dhcp_opt++ = 1;
#endif

                // DHCP_OPTION_DNS_SERVER, use the default DNS server address in lwIP
                *dhcp_opt++ = DHCP_OPTION_DNS_SERVER;
                *dhcp_opt++ = 4;
                *dhcp_opt++ = 208;
                *dhcp_opt++ = 67;
                *dhcp_opt++ = 222;
                *dhcp_opt++ = 222;

                // DHCP_OPTION_LEASE_TIME
                *dhcp_opt++ = DHCP_OPTION_LEASE_TIME;
                *dhcp_opt++ = 4;
                *dhcp_opt++ = 0x00;
                *dhcp_opt++ = 0x01;
                *dhcp_opt++ = 0x51;
                *dhcp_opt++ = 0x80;

                // DHCP_OPTION_MTU
                *dhcp_opt++ = DHCP_OPTION_MTU;
                *dhcp_opt++ = 2;
                *dhcp_opt++ = ETHERNET_MTU >> 8;
                *dhcp_opt++ = ETHERNET_MTU & 0xff;
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
    
    /* clean up */
    {
        closesocket(sock);
        rt_free(recv_data);
        DEBUG_PRINTF("DHCP server closed\n");
    }
}

void dhcpd_start(char* netif_name)
{
    rt_thread_t thread;
    struct netif *netif = netif_list;
    
//    if(strlen(netif_name) > sizeof(netif->name))
//    {
//        rt_kprintf("network interface name too long!\r\n");
//        return;
//    }
    while(netif != RT_NULL)
    {
        if(strncmp(netif_name, netif->name, sizeof(netif->name)) == 0)
            break;

        netif = netif->next;
        if( netif == RT_NULL )
        {
            rt_kprintf("network interface: %s not found!\r\n", netif_name);
            return;
        }
    }

    thread = rt_thread_create("dhcpd",
                              dhcpd_thread_entry, netif,
                              1024,
                              RT_THREAD_PRIORITY_MAX - 3,
                              2);
    if (thread != RT_NULL)
    {
        thread->user_data = RT_TRUE;
        rt_thread_startup(thread);
    }
}

void dhcpd_stop(void)
{
    rt_thread_t thread;
    
    thread = rt_thread_find("dhcpd");
    if (thread != RT_NULL)
    {
        thread->user_data = RT_FALSE;
    }
}
