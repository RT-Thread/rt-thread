/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-13     tyx          the first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <wlan_mgnt.h>
#include <wlan_cfg.h>
#include <wlan_prot.h>

#define DBG_TAG "WLAN.cmd"
#ifdef RT_WLAN_MGNT_DEBUG
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_INFO
#endif /* RT_WLAN_MGNT_DEBUG */
#include <rtdbg.h>

static struct rt_wlan_scan_result scan_result;
static struct rt_wlan_info *scan_filter = RT_NULL;

#if defined(RT_WLAN_MANAGE_ENABLE) && defined(RT_WLAN_MSH_CMD_ENABLE)

struct wifi_cmd_des
{
    const char *cmd;
    int (*fun)(int argc, char *argv[]);
};

static int wifi_help(int argc, char *argv[]);
static int wifi_scan(int argc, char *argv[]);
static int wifi_status(int argc, char *argv[]);
static int wifi_join(int argc, char *argv[]);
static int wifi_ap(int argc, char *argv[]);
static int wifi_list_sta(int argc, char *argv[]);
static int wifi_disconnect(int argc, char *argv[]);
static int wifi_ap_stop(int argc, char *argv[]);

#ifdef RT_WLAN_CMD_DEBUG
/* just for debug  */
static int wifi_debug(int argc, char *argv[]);
static int wifi_debug_save_cfg(int argc, char *argv[]);
static int wifi_debug_dump_cfg(int argc, char *argv[]);
static int wifi_debug_clear_cfg(int argc, char *argv[]);
static int wifi_debug_dump_prot(int argc, char *argv[]);
static int wifi_debug_set_mode(int argc, char *argv[]);
static int wifi_debug_set_prot(int argc, char *argv[]);
static int wifi_debug_set_autoconnect(int argc, char *argv[]);
#endif

/* cmd table */
static const struct wifi_cmd_des cmd_tab[] =
{
    {"scan", wifi_scan},
    {"help", wifi_help},
    {"status", wifi_status},
    {"join", wifi_join},
    {"ap", wifi_ap},
    {"list_sta", wifi_list_sta},
    {"disc", wifi_disconnect},
    {"ap_stop", wifi_ap_stop},
    {"smartconfig", RT_NULL},
#ifdef RT_WLAN_CMD_DEBUG
    {"-d", wifi_debug},
#endif
};

#ifdef RT_WLAN_CMD_DEBUG
/* debug cmd table */
static const struct wifi_cmd_des debug_tab[] =
{
    {"save_cfg", wifi_debug_save_cfg},
    {"dump_cfg", wifi_debug_dump_cfg},
    {"clear_cfg", wifi_debug_clear_cfg},
    {"dump_prot", wifi_debug_dump_prot},
    {"mode", wifi_debug_set_mode},
    {"prot", wifi_debug_set_prot},
    {"auto", wifi_debug_set_autoconnect},
};
#endif

static int wifi_help(int argc, char *argv[])
{
    rt_kprintf("wifi\n");
    rt_kprintf("wifi help\n");
    rt_kprintf("wifi scan [SSID]\n");
    rt_kprintf("wifi join [SSID] [PASSWORD]\n");
    rt_kprintf("wifi ap SSID [PASSWORD]\n");
    rt_kprintf("wifi disc\n");
    rt_kprintf("wifi ap_stop\n");
    rt_kprintf("wifi status\n");
    rt_kprintf("wifi smartconfig\n");
#ifdef RT_WLAN_CMD_DEBUG
    rt_kprintf("wifi -d debug command\n");
#endif
    return 0;
}

static int wifi_status(int argc, char *argv[])
{
    int rssi;
    struct rt_wlan_info info;

    if (argc > 2)
        return -1;

    if (rt_wlan_is_connected() == 1)
    {
        rssi = rt_wlan_get_rssi();
        rt_wlan_get_info(&info);
        rt_kprintf("Wi-Fi STA Info\n");
        rt_kprintf("SSID : %-.32s\n", &info.ssid.val[0]);
        rt_kprintf("MAC Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", info.bssid[0],
                   info.bssid[1],
                   info.bssid[2],
                   info.bssid[3],
                   info.bssid[4],
                   info.bssid[5]);
        rt_kprintf("Channel: %d\n", info.channel);
        rt_kprintf("DataRate: %dMbps\n", info.datarate / 1000000);
        rt_kprintf("RSSI: %d\n", rssi);
    }
    else
    {
        rt_kprintf("wifi disconnected!\n");
    }

    if (rt_wlan_ap_is_active() == 1)
    {
        rt_wlan_ap_get_info(&info);
        rt_kprintf("Wi-Fi AP Info\n");
        rt_kprintf("SSID : %-.32s\n", &info.ssid.val[0]);
        rt_kprintf("MAC Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", info.bssid[0],
                   info.bssid[1],
                   info.bssid[2],
                   info.bssid[3],
                   info.bssid[4],
                   info.bssid[5]);
        rt_kprintf("Channel: %d\n", info.channel);
        rt_kprintf("DataRate: %dMbps\n", info.datarate / 1000000);
        rt_kprintf("hidden: %s\n", info.hidden ? "Enable" : "Disable");
    }
    else
    {
        rt_kprintf("wifi ap not start!\n");
    }
    rt_kprintf("Auto Connect status:%s!\n", (rt_wlan_get_autoreconnect_mode() ? "Enable" : "Disable"));
    return 0;
}


static rt_bool_t wifi_info_isequ(struct rt_wlan_info *info1, struct rt_wlan_info *info2)
{
    rt_bool_t is_equ = 1;
    rt_uint8_t bssid_zero[RT_WLAN_BSSID_MAX_LENGTH] = { 0 };

    if (is_equ && (info1->security != SECURITY_UNKNOWN) && (info2->security != SECURITY_UNKNOWN))
    {
        is_equ &= info2->security == info1->security;
    }
    if (is_equ && ((info1->ssid.len > 0) && (info2->ssid.len > 0)))
    {
        is_equ &= info1->ssid.len == info2->ssid.len;
        is_equ &= rt_memcmp(&info2->ssid.val[0], &info1->ssid.val[0], info1->ssid.len) == 0;
    }
    if (is_equ && (rt_memcmp(&info1->bssid[0], bssid_zero, RT_WLAN_BSSID_MAX_LENGTH)) &&
       (rt_memcmp(&info2->bssid[0], bssid_zero, RT_WLAN_BSSID_MAX_LENGTH)))
    {
        is_equ &= rt_memcmp(&info1->bssid[0], &info2->bssid[0], RT_WLAN_BSSID_MAX_LENGTH) == 0;
    }
    if (is_equ && info1->datarate && info2->datarate)
    {
        is_equ &= info1->datarate == info2->datarate;
    }
    if (is_equ && (info1->channel >= 0) && (info2->channel >= 0))
    {
        is_equ &= info1->channel == info2->channel;
    }
    if (is_equ && (info1->rssi < 0) && (info2->rssi < 0))
    {
        is_equ &= info1->rssi == info2->rssi;
    }
    return is_equ;
}

static rt_err_t wifi_scan_result_cache(struct rt_wlan_info *info)
{
    struct rt_wlan_info *ptable;
    rt_err_t err = RT_EOK;
    int i, insert = -1;
    rt_base_t level;

    if ((info == RT_NULL) || (info->ssid.len == 0)) return -RT_EINVAL;

    LOG_D("ssid:%s len:%d mac:%02x:%02x:%02x:%02x:%02x:%02x", info->ssid.val, info->ssid.len,
                  info->bssid[0], info->bssid[1], info->bssid[2], info->bssid[3], info->bssid[4], info->bssid[5]);

    /* scanning result filtering */
    level = rt_hw_interrupt_disable();
    if (scan_filter)
    {
        struct rt_wlan_info _tmp_info = *scan_filter;
        rt_hw_interrupt_enable(level);
        if (wifi_info_isequ(&_tmp_info, info) != RT_TRUE)
        {
            return RT_EOK;
        }
    }
    else
    {
        rt_hw_interrupt_enable(level);
    }

    /* de-duplicatio */
    for (i = 0; i < scan_result.num; i++)
    {
        if ((info->ssid.len == scan_result.info[i].ssid.len) &&
                (rt_memcmp(&info->bssid[0], &scan_result.info[i].bssid[0], RT_WLAN_BSSID_MAX_LENGTH) == 0))
        {
            return RT_EOK;
        }
#ifdef RT_WLAN_SCAN_SORT
        if (insert >= 0)
        {
            continue;
        }
        /* Signal intensity comparison */
        if ((info->rssi < 0) && (scan_result.info[i].rssi < 0))
        {
            if (info->rssi > scan_result.info[i].rssi)
            {
                insert = i;
                continue;
            }
            else if (info->rssi < scan_result.info[i].rssi)
            {
                continue;
            }
        }

        /* Channel comparison */
        if (info->channel < scan_result.info[i].channel)
        {
            insert = i;
            continue;
        }
        else if (info->channel > scan_result.info[i].channel)
        {
            continue;
        }

        /* data rate comparison */
        if ((info->datarate > scan_result.info[i].datarate))
        {
            insert = i;
            continue;
        }
        else if (info->datarate < scan_result.info[i].datarate)
        {
            continue;
        }
#endif
    }

    /* Insert the end */
    if (insert == -1)
        insert = scan_result.num;

    if (scan_result.num >= RT_WLAN_SCAN_CACHE_NUM)
        return RT_EOK;

    /* malloc memory */
    ptable = rt_malloc(sizeof(struct rt_wlan_info) * (scan_result.num + 1));
    if (ptable == RT_NULL)
    {
        LOG_E("wlan info malloc failed!");
        return -RT_ENOMEM;
    }
    scan_result.num ++;

    /* copy info */
    for (i = 0; i < scan_result.num; i++)
    {
        if (i < insert)
        {
            ptable[i] = scan_result.info[i];
        }
        else if (i > insert)
        {
            ptable[i] = scan_result.info[i - 1];
        }
        else if (i == insert)
        {
            ptable[i] = *info;
        }
    }
    rt_free(scan_result.info);
    scan_result.info = ptable;
    return err;
}



static void wifi_scan_result_clean(void)
{

    /* If there is data */
    if (scan_result.num)
    {
        scan_result.num = 0;
        rt_free(scan_result.info);
        scan_result.info = RT_NULL;
    }
}

static void print_ap_info(struct rt_wlan_info *info,int index)
{
        char *security;

        if(index == 0)
        {
            rt_kprintf("             SSID                      MAC            security    rssi chn Mbps\n");
            rt_kprintf("------------------------------- -----------------  -------------- ---- --- ----\n");
        }

        {
            rt_kprintf("%-32.32s", &(info->ssid.val[0]));
            rt_kprintf("%02x:%02x:%02x:%02x:%02x:%02x  ",
                       info->bssid[0],
                       info->bssid[1],
                       info->bssid[2],
                       info->bssid[3],
                       info->bssid[4],
                       info->bssid[5]
                      );
            switch (info->security)
            {
            case SECURITY_OPEN:
                security = "OPEN";
                break;
            case SECURITY_WEP_PSK:
                security = "WEP_PSK";
                break;
            case SECURITY_WEP_SHARED:
                security = "WEP_SHARED";
                break;
            case SECURITY_WPA_TKIP_PSK:
                security = "WPA_TKIP_PSK";
                break;
            case SECURITY_WPA_AES_PSK:
                security = "WPA_AES_PSK";
                break;
            case SECURITY_WPA2_AES_PSK:
                security = "WPA2_AES_PSK";
                break;
            case SECURITY_WPA2_TKIP_PSK:
                security = "WPA2_TKIP_PSK";
                break;
            case SECURITY_WPA2_MIXED_PSK:
                security = "WPA2_MIXED_PSK";
                break;
            case SECURITY_WPS_OPEN:
                security = "WPS_OPEN";
                break;
            case SECURITY_WPS_SECURE:
                security = "WPS_SECURE";
                break;
            default:
                security = "UNKNOWN";
                break;
            }
            rt_kprintf("%-14.14s ", security);
            rt_kprintf("%-4d ", info->rssi);
            rt_kprintf("%3d ", info->channel);
            rt_kprintf("%4d\n", info->datarate / 1000000);
        }

}

static void user_ap_info_callback(int event, struct rt_wlan_buff *buff, void *parameter)
{
    struct rt_wlan_info *info = RT_NULL;
    int index = 0;
    int ret = RT_EOK;

    RT_ASSERT(event == RT_WLAN_EVT_SCAN_REPORT);
    RT_ASSERT(buff != RT_NULL);
    RT_ASSERT(parameter != RT_NULL);

    info = (struct rt_wlan_info *)buff->data;
    index = *((int *)(parameter));

    ret = wifi_scan_result_cache(info);
    if(ret == RT_EOK)
    {
        if(scan_filter == RT_NULL ||
                (scan_filter != RT_NULL &&
                 scan_filter->ssid.len == info->ssid.len &&
                 rt_memcmp(&scan_filter->ssid.val[0], &info->ssid.val[0], scan_filter->ssid.len) == 0))
        {
            /*Print the info*/
            print_ap_info(info,index);

            index++;
            *((int *)(parameter)) = index;
        }
    }

}
static int wifi_scan(int argc, char *argv[])
{
    struct rt_wlan_info *info = RT_NULL;
    struct rt_wlan_info filter;
    int ret = 0;
    int i = 0;

    if (argc > 3)
        return -1;

    if (argc == 3)
    {
        INVALID_INFO(&filter);
        SSID_SET(&filter, argv[2]);
        info = &filter;
    }

    ret = rt_wlan_register_event_handler(RT_WLAN_EVT_SCAN_REPORT,user_ap_info_callback,&i);
    if(ret != RT_EOK)
    {
        LOG_E("Scan register user callback error:%d!\n",ret);
        return 0;
    }

    if(info)
    {
        scan_filter = info;
    }


    /*Todo: what can i do for it return val */
    ret = rt_wlan_scan_with_info(info);
    if(ret != RT_EOK)
    {
        LOG_E("Scan with info error:%d!\n",ret);
    }

    /* clean scan result */
    wifi_scan_result_clean();
    if(info)
    {
        scan_filter = RT_NULL;
    }
    return 0;
}

static int wifi_join(int argc, char *argv[])
{
    const char *ssid = RT_NULL;
    const char *key = RT_NULL;
    struct rt_wlan_cfg_info cfg_info;

    rt_memset(&cfg_info, 0, sizeof(cfg_info));
    if (argc ==  2)
    {
#ifdef RT_WLAN_CFG_ENABLE
        /* get info to connect */
        if (rt_wlan_cfg_read_index(&cfg_info, 0) == 1)
        {
            ssid = (char *)(&cfg_info.info.ssid.val[0]);
            if (cfg_info.key.len)
                key = (char *)(&cfg_info.key.val[0]);
        }
        else
#endif
        {
            rt_kprintf("not find connect info\n");
        }
    }
    else if (argc == 3)
    {
        /* ssid */
        ssid = argv[2];
    }
    else if (argc == 4)
    {
        ssid = argv[2];
        /* password */
        key = argv[3];
    }
    else
    {
        return -1;
    }
    rt_wlan_connect(ssid, key);
    return 0;
}

static int wifi_ap(int argc, char *argv[])
{
    const char *ssid = RT_NULL;
    const char *key = RT_NULL;

    if (argc == 3)
    {
        ssid = argv[2];
    }
    else if (argc == 4)
    {
        ssid = argv[2];
        key = argv[3];
    }
    else
    {
        return -1;
    }

    rt_wlan_start_ap(ssid, key);
    return 0;
}

static int wifi_list_sta(int argc, char *argv[])
{
    struct rt_wlan_info *sta_info;
    int num, i;

    if (argc > 2)
        return -1;
    num = rt_wlan_ap_get_sta_num();
    sta_info = rt_malloc(sizeof(struct rt_wlan_info) * num);
    if (sta_info == RT_NULL)
    {
        rt_kprintf("num:%d\n", num);
        return 0;
    }
    rt_wlan_ap_get_sta_info(sta_info, num);
    rt_kprintf("num:%d\n", num);
    for (i = 0; i < num; i++)
    {
        rt_kprintf("sta mac  %02x:%02x:%02x:%02x:%02x:%02x\n",
                   sta_info[i].bssid[0], sta_info[i].bssid[1], sta_info[i].bssid[2],
                   sta_info[i].bssid[3], sta_info[i].bssid[4], sta_info[i].bssid[5]);
    }
    rt_free(sta_info);
    return 0;
}

static int wifi_disconnect(int argc, char *argv[])
{
    if (argc != 2)
    {
        return -1;
    }

    rt_wlan_disconnect();
    return 0;
}

static int wifi_ap_stop(int argc, char *argv[])
{
    if (argc != 2)
    {
        return -1;
    }

    rt_wlan_ap_stop();
    return 0;
}

#ifdef RT_WLAN_CMD_DEBUG
/* just for debug */
static int wifi_debug_help(int argc, char *argv[])
{
    rt_kprintf("save_cfg ssid [password]\n");
    rt_kprintf("dump_cfg\n");
    rt_kprintf("clear_cfg\n");
    rt_kprintf("dump_prot\n");
    rt_kprintf("mode sta/ap dev_name\n");
    rt_kprintf("prot lwip dev_name\n");
    rt_kprintf("auto enable/disable\n");
    return 0;
}

static int wifi_debug_save_cfg(int argc, char *argv[])
{
    struct rt_wlan_cfg_info cfg_info;
    int len;
    char *ssid = RT_NULL, *password = RT_NULL;

    rt_memset(&cfg_info, 0, sizeof(cfg_info));
    INVALID_INFO(&cfg_info.info);
    if (argc == 2)
    {
        ssid = argv[1];
    }
    else if (argc == 3)
    {
        ssid = argv[1];
        password = argv[2];
    }
    else
    {
        return -1;
    }

    if (ssid != RT_NULL)
    {
        len = rt_strlen(ssid);
        if (len > RT_WLAN_SSID_MAX_LENGTH)
        {
            rt_kprintf("ssid is to long");
            return 0;
        }
        rt_memcpy(&cfg_info.info.ssid.val[0], ssid, len);
        cfg_info.info.ssid.len = len;
    }

    if (password != RT_NULL)
    {
        len = rt_strlen(password);
        if (len > RT_WLAN_PASSWORD_MAX_LENGTH)
        {
            rt_kprintf("password is to long");
            return 0;
        }
        rt_memcpy(&cfg_info.key.val[0], password, len);
        cfg_info.key.len = len;
    }
#ifdef RT_WLAN_CFG_ENABLE
    rt_wlan_cfg_save(&cfg_info);
#endif
    return 0;
}

static int wifi_debug_dump_cfg(int argc, char *argv[])
{
    if (argc == 1)
    {
#ifdef RT_WLAN_CFG_ENABLE
        rt_wlan_cfg_dump();
#endif
    }
    else
    {
        return -1;
    }
    return 0;
}

static int wifi_debug_clear_cfg(int argc, char *argv[])
{
    if (argc == 1)
    {
#ifdef RT_WLAN_CFG_ENABLE
        rt_wlan_cfg_delete_all();
        rt_wlan_cfg_cache_save();
#endif
    }
    else
    {
        return -1;
    }
    return 0;
}

static int wifi_debug_dump_prot(int argc, char *argv[])
{
    if (argc == 1)
    {
        rt_wlan_prot_dump();
    }
    else
    {
        return -1;
    }
    return 0;
}

static int wifi_debug_set_mode(int argc, char *argv[])
{
    rt_wlan_mode_t mode;

    if (argc != 3)
        return -1;

    if (rt_strcmp("sta", argv[1]) == 0)
    {
        mode = RT_WLAN_STATION;
    }
    else if (rt_strcmp("ap", argv[1]) == 0)
    {
        mode = RT_WLAN_AP;
    }
    else if (rt_strcmp("none", argv[1]) == 0)
    {
        mode = RT_WLAN_NONE;
    }
    else
        return -1;

    rt_wlan_set_mode(argv[2], mode);
    return 0;
}

static int wifi_debug_set_prot(int argc, char *argv[])
{
    if (argc != 3)
    {
        return -1;
    }

    rt_wlan_prot_attach(argv[2], argv[1]);
    return 0;
}

static int wifi_debug_set_autoconnect(int argc, char *argv[])
{
    if (argc == 2)
    {
        if (rt_strcmp(argv[1], "enable") == 0)
            rt_wlan_config_autoreconnect(RT_TRUE);
        else if (rt_strcmp(argv[1], "disable") == 0)
            rt_wlan_config_autoreconnect(RT_FALSE);
    }
    else
    {
        return -1;
    }
    return 0;
}

static int wifi_debug(int argc, char *argv[])
{
    int i, result = 0;
    const struct wifi_cmd_des *run_cmd = RT_NULL;

    if (argc < 3)
    {
        wifi_debug_help(0, RT_NULL);
        return 0;
    }

    for (i = 0; i < sizeof(debug_tab) / sizeof(debug_tab[0]); i++)
    {
        if (rt_strcmp(debug_tab[i].cmd, argv[2]) == 0)
        {
            run_cmd = &debug_tab[i];
            break;
        }
    }

    if (run_cmd == RT_NULL)
    {
        wifi_debug_help(0, RT_NULL);
        return 0;
    }

    if (run_cmd->fun != RT_NULL)
    {
        result = run_cmd->fun(argc - 2, &argv[2]);
    }

    if (result)
    {
        wifi_debug_help(argc - 2, &argv[2]);
    }
    return 0;
}
#endif

static int wifi_msh(int argc, char *argv[])
{
    int i, result = 0;
    const struct wifi_cmd_des *run_cmd = RT_NULL;

    if (argc == 1)
    {
        wifi_help(argc, argv);
        return 0;
    }

    /* find fun */
    for (i = 0; i < sizeof(cmd_tab) / sizeof(cmd_tab[0]); i++)
    {
        if (rt_strcmp(cmd_tab[i].cmd, argv[1]) == 0)
        {
            run_cmd = &cmd_tab[i];
            break;
        }
    }

    /* not find fun, print help */
    if (run_cmd == RT_NULL)
    {
        wifi_help(argc, argv);
        return 0;
    }

    /* run fun */
    if (run_cmd->fun != RT_NULL)
    {
        result = run_cmd->fun(argc, argv);
    }

    if (result)
    {
        wifi_help(argc, argv);
    }
    return 0;
}

#if defined(RT_USING_FINSH)
MSH_CMD_EXPORT_ALIAS(wifi_msh, wifi, wifi command);
#endif

#endif
