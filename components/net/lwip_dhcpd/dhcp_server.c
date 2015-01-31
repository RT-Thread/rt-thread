/*
 * File      : dhcp_server.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-01-30     aozima       the first version
 * 2013-07-10     aozima       add _low_level_dhcp_send.
 * 2013-08-08     aozima       support different network segments.
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

//#define DHCP_DEBUG_PRINTF

#ifdef  DHCP_DEBUG_PRINTF
#define DEBUG_PRINTF        rt_kprintf("[DHCPD] "); rt_kprintf
#else
#define DEBUG_PRINTF(...)
#endif /* DHCP_DEBUG_PRINTF */

#undef  LWIP_DHCP
#define LWIP_DHCP   1
#include <lwip/dhcp.h>

#define SERVER_IPADDR0      192UL
#define SERVER_IPADDR1      168UL
#define SERVER_IPADDR2      169UL
#define SERVER_IPADDR3      1UL

#define DHCP_ETH_NAME       "w00"

#define BUFSZ               1024

#define CLIENT_IP_MIN       2
#define CLIENT_IP_MAX       254
static uint8_t next_client_ip = CLIENT_IP_MIN;
static rt_err_t _low_level_dhcp_send(struct netif * netif,
                                     const void * buffer,
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

    if(p == RT_NULL)
        return -RT_ENOMEM;

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

    return netif->linkoutput(netif, p);
}

static void dhcpd_thread_entry(void* parameter)
{
    struct netif * netif = RT_NULL;
    int sock;
    int bytes_read;
    char *recv_data;
    rt_uint32_t addr_len;
    struct sockaddr_in server_addr, client_addr;
    struct dhcp_msg *msg;

    /* find ethernet interface. */
    netif = netif_find(DHCP_ETH_NAME);
    if(netif == RT_NULL)
    {
        DEBUG_PRINTF("can't find the ethernet interface: %s\r\n",
                     DHCP_ETH_NAME);
    }

    recv_data = rt_malloc(BUFSZ);
    if (recv_data == RT_NULL)
    {
        DEBUG_PRINTF("No memory\n");
        return;
    }

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        DEBUG_PRINTF("Socket error\n");

        rt_free(recv_data);
        return;
    }

    {
        int optval;
        int res=5;
        // set SO_REUSEADDR on a socket to true (1):
        optval = 1;

        res = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));
        res = res;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(DHCP_SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    rt_memset(&(server_addr.sin_zero),0, sizeof(server_addr.sin_zero));

    if (bind(sock,(struct sockaddr *)&server_addr,
             sizeof(struct sockaddr)) == -1)
    {
        DEBUG_PRINTF("Bind error\n");

        /* 释放接收用的数据缓冲 */
        rt_free(recv_data);
        return;
    }

    addr_len = sizeof(struct sockaddr);
    DEBUG_PRINTF("DHCP server listen on port %d...\n", DHCP_SERVER_PORT);

    while (1)
    {
        bytes_read = recvfrom(sock, recv_data, BUFSZ - 1, 0,
                              (struct sockaddr *)&client_addr, &addr_len);
        if(bytes_read < DHCP_MSG_LEN)
        {
            DEBUG_PRINTF("too short, wait next!\r\n");
            continue;
        }
        msg = (struct dhcp_msg *)recv_data;
        if( (msg->op != DHCP_BOOTREQUEST) ||
            (msg->cookie != PP_HTONL(DHCP_MAGIC_COOKIE)) )
        {
            continue;
        }

        /* handler. */
        {
            uint8_t * dhcp_opt;
            uint8_t option;
            uint8_t length;

            uint8_t message_type = 0;
            uint8_t fnished = 0;
            uint32_t request_ip  = 0;

            dhcp_opt = (uint8_t *)msg + DHCP_OPTIONS_OFS;
            while(fnished == 0)
            {
                option = *dhcp_opt;
                length = *(dhcp_opt+1);

                switch(option)
                {
                case DHCP_OPTION_REQUESTED_IP:
                    request_ip = *(dhcp_opt+2) << 24 | *(dhcp_opt+3) << 16
                                 | *(dhcp_opt+4) << 8 | *(dhcp_opt+5);
                    break;

                case DHCP_OPTION_END:
                    fnished = 1;
                    break;

                case DHCP_OPTION_MESSAGE_TYPE:
                    message_type = *(dhcp_opt+2);
                    break;

                default:

                    break;
                } /* switch(option) */

                dhcp_opt += (2 + length);
            }

            /* reply. */
            dhcp_opt = (uint8_t *)msg + DHCP_OPTIONS_OFS;

            /* check. */
            if(request_ip)
            {
                uint32_t client_ip = SERVER_IPADDR0 << 24 | SERVER_IPADDR1 << 16
                                     | SERVER_IPADDR2 << 8 | (next_client_ip);
         
                if(request_ip != client_ip)
                {
                    *dhcp_opt++ = DHCP_OPTION_MESSAGE_TYPE;
                    *dhcp_opt++ = DHCP_OPTION_MESSAGE_TYPE_LEN;
                    *dhcp_opt++ = DHCP_NAK;
                    *dhcp_opt++ = DHCP_OPTION_END;

                    DEBUG_PRINTF("requested IP invalid, reply DHCP_NAK\r\n");
                    if(netif != RT_NULL )
                    {
                        int send_byte = (dhcp_opt - (uint8_t *)msg);
                        _low_level_dhcp_send(netif, msg, send_byte);
                        DEBUG_PRINTF("DHCP server send %d byte\r\n\r\n", send_byte);
                    }

                 next_client_ip++;
                 if(next_client_ip > CLIENT_IP_MAX)
                    next_client_ip = CLIENT_IP_MIN;
                    continue;
                }

            }

            if(message_type == DHCP_DISCOVER)
            {
                DEBUG_PRINTF("request DHCP_DISCOVER\r\n");
                DEBUG_PRINTF("reply   DHCP_OFFER\r\n");

                // DHCP_OPTION_MESSAGE_TYPE
                *dhcp_opt++ = DHCP_OPTION_MESSAGE_TYPE;
                *dhcp_opt++ = DHCP_OPTION_MESSAGE_TYPE_LEN;
                *dhcp_opt++ = DHCP_OFFER;

                // DHCP_OPTION_SERVER_ID
                *dhcp_opt++ = DHCP_OPTION_SERVER_ID;
                *dhcp_opt++ = 4;
                *dhcp_opt++ = SERVER_IPADDR0;
                *dhcp_opt++ = SERVER_IPADDR1;
                *dhcp_opt++ = SERVER_IPADDR2;
                *dhcp_opt++ = SERVER_IPADDR3;

                // DHCP_OPTION_LEASE_TIME
                *dhcp_opt++ = DHCP_OPTION_LEASE_TIME;
                *dhcp_opt++ = 4;
                *dhcp_opt++ = 0x00;
                *dhcp_opt++ = 0x01;
                *dhcp_opt++ = 0x51;
                *dhcp_opt++ = 0x80;
            }
            else if(message_type == DHCP_REQUEST)
            {
                DEBUG_PRINTF("request DHCP_REQUEST\r\n");
                DEBUG_PRINTF("reply   DHCP_ACK\r\n");

                // DHCP_OPTION_MESSAGE_TYPE
                *dhcp_opt++ = DHCP_OPTION_MESSAGE_TYPE;
                *dhcp_opt++ = DHCP_OPTION_MESSAGE_TYPE_LEN;
                *dhcp_opt++ = DHCP_ACK;

                // DHCP_OPTION_SERVER_ID
                *dhcp_opt++ = DHCP_OPTION_SERVER_ID;
                *dhcp_opt++ = 4;
                *dhcp_opt++ = SERVER_IPADDR0;
                *dhcp_opt++ = SERVER_IPADDR1;
                *dhcp_opt++ = SERVER_IPADDR2;
                *dhcp_opt++ = SERVER_IPADDR3;

                // DHCP_OPTION_SUBNET_MASK
                *dhcp_opt++ = DHCP_OPTION_SUBNET_MASK;
                *dhcp_opt++ = 4;
                *dhcp_opt++ = 0xFF;
                *dhcp_opt++ = 0xFF;
                *dhcp_opt++ = 0xFF;
                *dhcp_opt++ = 0x00;

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
                DEBUG_PRINTF("un handle message:%d\r\n", message_type);
            }

            // append DHCP_OPTION_END
            *dhcp_opt++ = DHCP_OPTION_END;

            /* send reply. */
            if( (message_type == DHCP_DISCOVER)
                    || (message_type == DHCP_REQUEST) )
            {
                msg->op = DHCP_BOOTREPLY;
                IP4_ADDR(&msg->yiaddr,
                         SERVER_IPADDR0, SERVER_IPADDR1,
                         SERVER_IPADDR2, next_client_ip);
            
                                
                client_addr.sin_addr.s_addr = INADDR_BROADCAST;

                if(netif != RT_NULL )
                {
                    int send_byte = (dhcp_opt - (uint8_t *)msg);
                    _low_level_dhcp_send(netif, msg, send_byte);
                    DEBUG_PRINTF("DHCP server send %d byte\r\n\r\n", send_byte);
                }
            }
        } /* handler. */
    }
}

void dhcpd_start(void)
{
    rt_thread_t thread;
    thread = rt_thread_create("dhcpd",
                              dhcpd_thread_entry,
                              RT_NULL,
                              1024,
                              RT_THREAD_PRIORITY_MAX-3,
                              2);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
}

