/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-25     tyx          add w600
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "oneshot.h"

#define NET_READY_TIME_OUT       (rt_tick_from_millisecond(30 * 1000))

struct join_info
{
    char ssid[64];
    char passwd[64];
};

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

static void join_wifi_thread(void *param)
{
    struct join_info *info = param;

    rt_kprintf("connect wifi:%s\n", info->ssid);
    if (rt_strlen(info->passwd) > 0)
    {
        rt_wlan_device_connetct(info->ssid, info->passwd);
    }
    else
    {
        rt_wlan_device_connetct(info->ssid, RT_NULL);
    }
    rt_free(info);
}

static void wm_oneshot_result_cb(int state, unsigned char *ssid, unsigned char *passwd)
{
    rt_thread_t tid;
    struct join_info *info;

    if (state != 0)
    {
        rt_kprintf("Receive wifi info timeout(%d). exit!\n", state);
        return;
    }
    if (ssid == RT_NULL)
    {
        rt_kprintf("SSID is NULL. exit!\n");
        return;
    }
    rt_kprintf("Receive ssid:%s passwd:%s\n", ssid == RT_NULL ? "" : ssid, passwd == RT_NULL ? "" : passwd);
    info = rt_malloc(sizeof(struct join_info));
    if (info == RT_NULL)
    {
        return;
    }
    rt_memset(info, 0, sizeof(struct join_info));
    rt_strncpy(info->ssid, ssid, sizeof(info->ssid));
    if (passwd)
    {
        rt_strncpy(info->passwd, passwd, sizeof(info->passwd));
    }
    tid = rt_thread_create("join", join_wifi_thread, info, 2048, 22, 20);
    if (tid == RT_NULL)
    {
        rt_free(info);
        return;
    }
    rt_thread_startup(tid);
}

void oneshot_demo(int argc, char *argv[])
{
    WM_ONESHOT_MODE mode = WM_UDP;

    if (argc > 2)
    {
        rt_kprintf("use: %s [web]", __FUNCTION__);
        return;
    }
    if (argc == 2)
    {
        if (rt_strcmp("web", argv[1]) == 0)
        {
            mode = WM_APWEB;
        }
        else if(rt_strcmp("udp", argv[1]) == 0)
        {
            mode = WM_UDP;
        }
        else
        {
            rt_kprintf("use: %s [web]", __FUNCTION__);
            return;
        }
    }
    if (wm_oneshot_start(mode, wm_oneshot_result_cb) == 0)
    {
        rt_kprintf("oneshot start...\n");
    }
    else
    {
        rt_kprintf("oneshot start failed\n");
    }
}

#ifdef RT_USING_FINSH
#include "finsh.h"
MSH_CMD_EXPORT(oneshot_demo, oneshot demo);
#endif
