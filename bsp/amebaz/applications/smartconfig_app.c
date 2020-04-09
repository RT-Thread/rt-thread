/*
 * File      : smartconfig_demo.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
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
 * 2018-09-13     Bernard      the first version
 */
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_SMARTCONFIG_LIB

#include <sys/socket.h>
#include "smartconfig.h"

#define NET_READY_TIME_OUT       (rt_tick_from_millisecond(30 * 1000))

static int rt_wlan_device_connetct(char *ssid, char *passwd)
{
    int result = RT_EOK;
    rt_uint8_t time_cnt = 0;

    result = rt_wlan_connect(ssid, passwd);
    if (result != RT_EOK)
    {
        rt_kprintf("\nconnect ssid %s error:%d!\n", ssid, result);
        return result;
    };

    do
    {
        rt_thread_mdelay(1000);
        time_cnt ++;
        if (rt_wlan_is_ready())
        {
            break;
        }
    }
    while (time_cnt <= (NET_READY_TIME_OUT / 1000));

    if (time_cnt <= (NET_READY_TIME_OUT / 1000))
    {
        rt_kprintf("networking ready!\n");
    }
    else
    {
        rt_kprintf("wait ip got timeout!\n");
        result = -RT_ETIMEOUT;
    }

    return result;
}

static void airkiss_send_notification(uint8_t random)
{
    int i;
    int sock = -1;
    int udpbufsize = 2;
    struct sockaddr_in UDPBCAddr, UDPBCServerAddr;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        rt_kprintf("notify create socket error!\n");
        goto _exit;
    }

    UDPBCAddr.sin_family = AF_INET;
    UDPBCAddr.sin_port = htons(10000);
    UDPBCAddr.sin_addr.s_addr = htonl(0xffffffff);
    rt_memset(&(UDPBCAddr.sin_zero), 0, sizeof(UDPBCAddr.sin_zero));

    UDPBCServerAddr.sin_family = AF_INET;
    UDPBCServerAddr.sin_port = htons(10000);
    UDPBCServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    rt_memset(&(UDPBCServerAddr.sin_zero), 0, sizeof(UDPBCServerAddr.sin_zero));

    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &udpbufsize, sizeof(int)) != 0)
    {
        rt_kprintf("notify socket setsockopt error\n");
        goto _exit;
    }

    if (bind(sock, (struct sockaddr *)&UDPBCServerAddr, sizeof(UDPBCServerAddr)) != 0)
    {
        rt_kprintf("notify socket bind error\n");
        goto _exit;
    }

    for (i = 0; i <= 20; i++)
    {
        int ret = sendto(sock, (char *)&random, 1, 0, (struct sockaddr *)&UDPBCAddr, sizeof(UDPBCAddr));
        rt_thread_delay(10);
    }

    rt_kprintf("airkiss notification thread exit!\n");

_exit:
    if (sock >= 0)
    {
        closesocket(sock);
    }
}

static int smartconfig_result(rt_smartconfig_type result_type, char *ssid, char *passwd, void *userdata, rt_uint8_t userdata_len)
{
    rt_uint8_t random = *(rt_uint8_t *)userdata;

    rt_kprintf("type:%d\n", result_type);
    rt_kprintf("ssid:%s\n", ssid);
    rt_kprintf("passwd:%s\n", passwd);
    rt_kprintf("user_data:0x%02x\n", random);
    if (rt_wlan_device_connetct(ssid, passwd) == RT_EOK)
    {
        airkiss_send_notification(random);
    }

    return 0;
}

void smartconfig_demo(void)
{
    rt_smartconfig_start(SMARTCONFIG_TYPE_AIRKISS, SMARTCONFIG_ENCRYPT_NONE, RT_NULL, smartconfig_result);
}

#ifdef RT_USING_FINSH
#include "finsh.h"
MSH_CMD_EXPORT(smartconfig_demo, smartconfig demo);
#endif

#endif
