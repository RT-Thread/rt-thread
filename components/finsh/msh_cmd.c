/*
 *  internal commands for RT-Thread module shell
 *
 * COPYRIGHT (C) 2013-2015, Shanghai Real-Thread Technology Co., Ltd
 *
 *  This file is part of RT-Thread (http://www.rt-thread.org)
 *  Maintainer: bernard.xiong <bernard.xiong at gmail.com>
 *
 *  All rights reserved.
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
 * 2013-03-30     Bernard      the first verion for FinSH
 * 2015-08-28     Bernard      Add mkfs command.
 */

#include <rtthread.h>
#include <finsh.h>

#include "msh.h"

#ifdef FINSH_USING_MSH
#ifdef RT_USING_LWIP
int cmd_ifconfig(int argc, char **argv)
{
    extern void list_if(void);
    extern void set_if(char *netif_name, char *ip_addr, char *gw_addr, char *nm_addr);


    if (argc == 1)
    {
        list_if();
    }
    else if (argc == 5)
    {
        rt_kprintf("config : %s\n", argv[1]);
        rt_kprintf("IP addr: %s\n", argv[2]);
        rt_kprintf("Gateway: %s\n", argv[3]);
        rt_kprintf("netmask: %s\n", argv[4]);
        set_if(argv[1], argv[2], argv[3], argv[4]);
    }
    else
    {
        rt_kprintf("bad parameter! e.g: ifconfig e0 192.168.1.30 192.168.1.1 255.255.255.0\n");
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_ifconfig, __cmd_ifconfig, list the information of network interfaces);

#ifdef RT_LWIP_DNS
#include <lwip/api.h>
#include <lwip/dns.h>
#include <lwip/ip_addr.h>
#include <lwip/init.h>

int cmd_dns(int argc, char **argv)
{
    extern void set_dns(char* dns_server);

    if (argc == 1)
    {
        int index;

#if (LWIP_VERSION) < 0x02000000U
        ip_addr_t ip_addr;
        for(index=0; index<DNS_MAX_SERVERS; index++)
        {
            ip_addr = dns_getserver(index);
            rt_kprintf("dns server #%d: %s\n", index, ipaddr_ntoa(&ip_addr));
        }
#else
        const ip_addr_t *ip_addr;
        for(index=0; index<DNS_MAX_SERVERS; index++)
        {
            ip_addr = dns_getserver(index);
            rt_kprintf("dns server #%d: %s\n", index, ipaddr_ntoa(ip_addr));
        }
#endif
    }
    else if (argc == 2)
    {
        rt_kprintf("dns : %s\n", argv[1]);
        set_dns(argv[1]);
    }
    else
    {
        rt_kprintf("bad parameter! e.g: dns 114.114.114.114\n");
    }
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_dns, __cmd_dns, list the information of dns);
#endif

#ifdef RT_LWIP_TCP
int cmd_netstat(int argc, char **argv)
{
    extern void list_tcps(void);

    list_tcps();
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_netstat, __cmd_netstat, list the information of TCP / IP);
#endif
#endif /* RT_USING_LWIP */

int cmd_ps(int argc, char **argv)
{
    extern long list_thread(void);
    extern int list_module(void);

#ifdef RT_USING_MODULE
    if ((argc == 2) && (strcmp(argv[1], "-m") == 0))
        list_module();
    else
#endif
        list_thread();
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_ps, __cmd_ps, List threads in the system.);

int cmd_time(int argc, char **argv)
{
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_time, __cmd_time, Execute command with time.);

#ifdef RT_USING_HEAP
int cmd_free(int argc, char **argv)
{
    extern void list_mem(void);
    extern void list_memheap(void);

#ifdef RT_USING_MEMHEAP_AS_HEAP
    list_memheap();
#else
    list_mem();
#endif
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_free, __cmd_free, Show the memory usage in the system.);
#endif

#endif

