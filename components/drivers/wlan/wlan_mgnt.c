/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-06     tyx          the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <wlan_dev.h>
#include <wlan_cfg.h>
#include <wlan_mgnt.h>
#include <wlan_prot.h>
#include <wlan_workqueue.h>

#define DBG_TAG "WLAN.mgnt"
#ifdef RT_WLAN_MGNT_DEBUG
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_INFO
#endif /* RT_WLAN_MGNT_DEBUG */
#include <rtdbg.h>

#ifdef RT_WLAN_MANAGE_ENABLE

#ifndef RT_WLAN_DEVICE
#define RT_WLAN_DEVICE(__device) ((struct rt_wlan_device *)__device)
#endif

#define RT_WLAN_LOG_D(_fmt, ...) LOG_D("L:%d "_fmt"", __LINE__, ##__VA_ARGS__)
#define RT_WLAN_LOG_I(...) LOG_I(__VA_ARGS__)
#define RT_WLAN_LOG_W(_fmt, ...) LOG_W("F:%s L:%d "_fmt"", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define RT_WLAN_LOG_E(_fmt, ...) LOG_E("F:%s L:%d "_fmt"", __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define STA_DEVICE()  (_sta_mgnt.device)
#define AP_DEVICE()  (_ap_mgnt.device)

#define SRESULT_LOCK()    (rt_mutex_take(&scan_result_mutex, RT_WAITING_FOREVER))
#define SRESULT_UNLOCK()  (rt_mutex_release(&scan_result_mutex))

#define STAINFO_LOCK()    (rt_mutex_take(&sta_info_mutex, RT_WAITING_FOREVER))
#define STAINFO_UNLOCK()  (rt_mutex_release(&sta_info_mutex))

#define MGNT_LOCK()       (rt_mutex_take(&mgnt_mutex, RT_WAITING_FOREVER))
#define MGNT_UNLOCK()     (rt_mutex_release(&mgnt_mutex))

#define COMPLETE_LOCK()       (rt_mutex_take(&complete_mutex, RT_WAITING_FOREVER))
#define COMPLETE_UNLOCK()     (rt_mutex_release(&complete_mutex))

#ifdef RT_WLAN_AUTO_CONNECT_ENABLE
#define TIME_STOP()    (rt_timer_stop(&reconnect_time))
#define TIME_START()   (rt_timer_start(&reconnect_time))
#else
#define TIME_STOP()
#define TIME_START()
#endif

#if RT_WLAN_EBOX_NUM < 1
#error "event box num Too few"
#endif

struct rt_wlan_mgnt_des
{
    struct rt_wlan_device *device;
    struct rt_wlan_info info;
    struct rt_wlan_key key;
    rt_uint8_t state;
    rt_uint8_t flags;
};

struct rt_wlan_event_desc
{
    rt_wlan_event_handler handler;
    void *parameter;
};

struct rt_wlan_sta_list
{
    struct rt_wlan_sta_list *next;
    struct rt_wlan_info info;
};

struct rt_wlan_sta_des
{
    int num;
    struct rt_wlan_sta_list *node;
};

struct rt_wlan_msg
{
    rt_int32_t event;
    rt_int32_t len;
    void *buff;
};

struct rt_wlan_complete_des
{
    struct rt_event complete;
    rt_uint32_t event_flag;
    int index;
};

static struct rt_mutex mgnt_mutex;

static struct rt_wlan_mgnt_des _sta_mgnt;
static struct rt_wlan_mgnt_des _ap_mgnt;

static struct rt_wlan_scan_result scan_result;
static struct rt_mutex scan_result_mutex;

static struct rt_wlan_sta_des sta_info;
static struct rt_mutex sta_info_mutex;

static struct rt_wlan_event_desc event_tab[RT_WLAN_EVT_MAX];

static struct rt_wlan_complete_des *complete_tab[5];
static struct rt_mutex complete_mutex;
static struct rt_wlan_info *scan_filter;

#ifdef RT_WLAN_AUTO_CONNECT_ENABLE
static struct rt_timer reconnect_time;
#endif

rt_inline int _sta_is_null(void)
{
    if (_sta_mgnt.device == RT_NULL)
    {
        return 1;
    }
    return 0;
}

rt_inline int _ap_is_null(void)
{
    if (_ap_mgnt.device == RT_NULL)
    {
        return 1;
    }
    return 0;
}

rt_inline rt_bool_t _is_do_connect(void)
{
    if ((rt_wlan_get_autoreconnect_mode() == RT_FALSE) ||
            (rt_wlan_is_connected() == RT_TRUE) ||
            (_sta_mgnt.state & RT_WLAN_STATE_CONNECTING))
    {
        return RT_FALSE;
    }
    return RT_TRUE;
}

#ifdef RT_WLAN_WORK_THREAD_ENABLE

static rt_bool_t rt_wlan_info_isequ(struct rt_wlan_info *info1, struct rt_wlan_info *info2)
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

static void rt_wlan_mgnt_work(void *parameter)
{
    struct rt_wlan_msg *msg = parameter;
    void *user_parameter;
    rt_wlan_event_handler handler = RT_NULL;
    struct rt_wlan_buff user_buff = { 0 };
    rt_base_t level;

    /* Get user callback */
    if (msg->event < RT_WLAN_EVT_MAX)
    {
        level = rt_hw_interrupt_disable();
        handler = event_tab[msg->event].handler;
        user_parameter = event_tab[msg->event].parameter;
        rt_hw_interrupt_enable(level);
    }

    /* run user callback fun */
    if (handler)
    {
        user_buff.data = msg->buff;
        user_buff.len = msg->len;
        RT_WLAN_LOG_D("wlan work thread run user callback, event:%d", msg->event);
        handler(msg->event, &user_buff, user_parameter);
    }

    switch (msg->event)
    {
    case RT_WLAN_EVT_STA_CONNECTED:
    {
        struct rt_wlan_cfg_info cfg_info;

        rt_memset(&cfg_info, 0, sizeof(cfg_info));
        /* save config */
        if (rt_wlan_is_connected() == RT_TRUE)
        {
            rt_enter_critical();
            cfg_info.info = _sta_mgnt.info;
            cfg_info.key = _sta_mgnt.key;
            rt_exit_critical();
            RT_WLAN_LOG_D("run save config! ssid:%s len%d", _sta_mgnt.info.ssid.val, _sta_mgnt.info.ssid.len);
#ifdef RT_WLAN_CFG_ENABLE
            rt_wlan_cfg_save(&cfg_info);
#endif
        }
        break;
    }
    default :
        break;
    }

    rt_free(msg);
}

static rt_err_t rt_wlan_send_to_thread(rt_wlan_event_t event, void *buff, int len)
{
    struct rt_wlan_msg *msg;

    RT_WLAN_LOG_D("F:%s is run event:%d", __FUNCTION__, event);

    /* Event packing */
    msg = rt_malloc(sizeof(struct rt_wlan_msg) + len);
    if (msg == RT_NULL)
    {
        RT_WLAN_LOG_E("wlan mgnt send msg err! No memory");
        return -RT_ENOMEM;
    }
    rt_memset(msg, 0, sizeof(struct rt_wlan_msg) + len);
    msg->event = event;
    if (len != 0)
    {
        msg->buff = (void *)&msg[1];
        rt_memcpy(msg->buff, buff, len);
        msg->len = len;
    }

    /* send event to wlan thread */
    if (rt_wlan_workqueue_dowork(rt_wlan_mgnt_work, msg) != RT_EOK)
    {
        rt_free(msg);
        RT_WLAN_LOG_E("wlan mgnt do work fail");
        return -RT_ERROR;
    }
    return RT_EOK;
}
#endif

static rt_err_t rt_wlan_scan_result_cache(struct rt_wlan_info *info, int timeout)
{
    struct rt_wlan_info *ptable;
    rt_err_t err = RT_EOK;
    int i, insert = -1;
    rt_base_t level;

    if (_sta_is_null() || (info == RT_NULL) || (info->ssid.len == 0)) return RT_EOK;

    RT_WLAN_LOG_D("ssid:%s len:%d mac:%02x:%02x:%02x:%02x:%02x:%02x", info->ssid.val, info->ssid.len,
                  info->bssid[0], info->bssid[1], info->bssid[2], info->bssid[3], info->bssid[4], info->bssid[5]);

    err = rt_mutex_take(&scan_result_mutex, rt_tick_from_millisecond(timeout));
    if (err != RT_EOK)
        return err;

    /* scanning result filtering */
    level = rt_hw_interrupt_disable();
    if (scan_filter)
    {
        struct rt_wlan_info _tmp_info = *scan_filter;
        rt_hw_interrupt_enable(level);
        if (rt_wlan_info_isequ(&_tmp_info, info) != RT_TRUE)
        {
            rt_mutex_release(&scan_result_mutex);
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
            rt_mutex_release(&scan_result_mutex);
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
        rt_mutex_release(&scan_result_mutex);
        RT_WLAN_LOG_E("wlan info malloc failed!");
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
    rt_mutex_release(&scan_result_mutex);
    return err;
}

static rt_err_t rt_wlan_sta_info_add(struct rt_wlan_info *info, int timeout)
{
    struct rt_wlan_sta_list *sta_list;
    rt_err_t err = RT_EOK;

    if (_ap_is_null() || (info == RT_NULL)) return RT_EOK;

    err = rt_mutex_take(&sta_info_mutex, rt_tick_from_millisecond(timeout));
    if (err == RT_EOK)
    {
        /* malloc memory */
        sta_list = rt_malloc(sizeof(struct rt_wlan_sta_list));
        if (sta_list == RT_NULL)
        {
            rt_mutex_release(&sta_info_mutex);
            RT_WLAN_LOG_E("sta list malloc failed!");
            return -RT_ENOMEM;
        }
        sta_list->next = RT_NULL;
        sta_list->info = *info;

        /* Append sta info */
        sta_list->next = sta_info.node;
        sta_info.node = sta_list;
        /* num++ */
        sta_info.num ++;
        rt_mutex_release(&sta_info_mutex);
        RT_WLAN_LOG_I("sta associated mac:%02x:%02x:%02x:%02x:%02x:%02x",
                      info->bssid[0], info->bssid[1], info->bssid[2],
                      info->bssid[3], info->bssid[4], info->bssid[5]);
    }
    return err;
}

static rt_err_t rt_wlan_sta_info_del(struct rt_wlan_info *info, int timeout)
{
    struct rt_wlan_sta_list *sta_list, *sta_prve;
    rt_err_t err = RT_EOK;

    if (_ap_is_null() || (info == RT_NULL)) return RT_EOK;

    err = rt_mutex_take(&sta_info_mutex, rt_tick_from_millisecond(timeout));
    if (err == RT_EOK)
    {
        /* traversing the list */
        for (sta_list = sta_info.node, sta_prve = RT_NULL; sta_list != RT_NULL;
                sta_prve = sta_list, sta_list = sta_list->next)
        {
            /* find mac addr */
            if (rt_memcmp(&sta_list->info.bssid[0], &info->bssid[0], RT_WLAN_BSSID_MAX_LENGTH) == 0)
            {
                if (sta_prve == RT_NULL)
                {
                    sta_info.node = sta_list->next;
                }
                else
                {
                    sta_prve->next = sta_list->next;
                }
                sta_info.num --;
                rt_free(sta_list);
                break;
            }
        }
        rt_mutex_release(&sta_info_mutex);
        RT_WLAN_LOG_I("sta exit mac:%02x:%02x:%02x:%02x:%02x:%02x",
                      info->bssid[0], info->bssid[1], info->bssid[2],
                      info->bssid[3], info->bssid[4], info->bssid[5]);
    }
    return err;
}

static rt_err_t rt_wlan_sta_info_del_all(int timeout)
{
    struct rt_wlan_sta_list *sta_list, *sta_next;
    rt_err_t err = RT_EOK;

    err = rt_mutex_take(&sta_info_mutex, rt_tick_from_millisecond(timeout));
    if (err == RT_EOK)
    {
        /* traversing the list */
        for (sta_list = sta_info.node; sta_list != RT_NULL; sta_list = sta_next)
        {
            sta_next = sta_list->next;
            sta_info.num --;
            rt_free(sta_list);
        }
        rt_mutex_release(&sta_info_mutex);
    }
    if (sta_info.num != 0)
    {
        RT_WLAN_LOG_W("\n\n!!!Program runing exception!!!\n\n");
    }
    sta_info.num = 0;
    sta_info.node = RT_NULL;
    return err;
}
#ifdef RT_WLAN_AUTO_CONNECT_ENABLE
static void rt_wlan_auto_connect_run(struct rt_work *work, void *parameter)
{
    static rt_uint32_t id = 0;
    struct rt_wlan_cfg_info cfg_info;
    char *password = RT_NULL;
    rt_base_t level;

    RT_WLAN_LOG_D("F:%s is run", __FUNCTION__);

    if (rt_mutex_take(&mgnt_mutex, 0) != RT_EOK)
        goto exit;

    /* auto connect status is disable or wifi is connect or connecting, exit */
    if (_is_do_connect() == RT_FALSE)
    {
        id = 0;
        RT_WLAN_LOG_D("not connection");
        goto exit;
    }

    /* Read the next configuration */
    rt_memset(&cfg_info, 0, sizeof(struct rt_wlan_cfg_info));
    if (rt_wlan_cfg_read_index(&cfg_info, id ++) == 0)
    {
        RT_WLAN_LOG_D("read cfg fail");
        id = 0;
        goto exit;
    }

    if (id >= rt_wlan_cfg_get_num()) id = 0;

    if ((cfg_info.key.len > 0) && (cfg_info.key.len <= RT_WLAN_PASSWORD_MAX_LENGTH))
    {
        cfg_info.key.val[cfg_info.key.len] = '\0';
        password = (char *)(&cfg_info.key.val[0]);
    }
    rt_wlan_connect((char *)cfg_info.info.ssid.val, password);
exit:
    rt_mutex_release(&mgnt_mutex);
    level = rt_hw_interrupt_disable();
    rt_memset(work, 0, sizeof(struct rt_work));
    rt_hw_interrupt_enable(level);
}

static void rt_wlan_cyclic_check(void *parameter)
{
    struct rt_workqueue *workqueue;
    static struct rt_work work;
    rt_base_t level;

    if ((_is_do_connect() == RT_TRUE) && (work.work_func == RT_NULL))
    {
        workqueue = rt_wlan_get_workqueue();
        if (workqueue != RT_NULL)
        {
            level = rt_hw_interrupt_disable();
            rt_work_init(&work, rt_wlan_auto_connect_run, RT_NULL);
            rt_hw_interrupt_enable(level);
            if (rt_workqueue_dowork(workqueue, &work) != RT_EOK)
            {
                level = rt_hw_interrupt_disable();
                rt_memset(&work, 0, sizeof(struct rt_work));
                rt_hw_interrupt_enable(level);
            }
        }
    }
}
#endif

static void rt_wlan_event_dispatch(struct rt_wlan_device *device, rt_wlan_dev_event_t event, struct rt_wlan_buff *buff, void *parameter)
{
    rt_err_t err = RT_NULL;
    rt_wlan_event_t user_event = RT_WLAN_EVT_MAX;
    int i;
    struct rt_wlan_buff user_buff = { 0 };

    if (buff)
    {
        user_buff = *buff;
    }
    /* Event Handle */
    switch (event)
    {
    case RT_WLAN_DEV_EVT_CONNECT:
    {
        RT_WLAN_LOG_D("event: CONNECT");
        _sta_mgnt.state |= RT_WLAN_STATE_CONNECT;
        _sta_mgnt.state &= ~RT_WLAN_STATE_CONNECTING;
        user_event = RT_WLAN_EVT_STA_CONNECTED;
        TIME_STOP();
        user_buff.data = &_sta_mgnt.info;
        user_buff.len = sizeof(struct rt_wlan_info);
        RT_WLAN_LOG_I("wifi connect success ssid:%s", &_sta_mgnt.info.ssid.val[0]);
        break;
    }
    case RT_WLAN_DEV_EVT_CONNECT_FAIL:
    {
        RT_WLAN_LOG_D("event: CONNECT_FAIL");
        _sta_mgnt.state &= ~RT_WLAN_STATE_CONNECT;
        _sta_mgnt.state &= ~RT_WLAN_STATE_CONNECTING;
        _sta_mgnt.state &= ~RT_WLAN_STATE_READY;
        user_event = RT_WLAN_EVT_STA_CONNECTED_FAIL;
        user_buff.data = &_sta_mgnt.info;
        user_buff.len = sizeof(struct rt_wlan_info);
        if (rt_wlan_get_autoreconnect_mode())
        {
            TIME_START();
        }
        break;
    }
    case RT_WLAN_DEV_EVT_DISCONNECT:
    {
        RT_WLAN_LOG_D("event: DISCONNECT");
        _sta_mgnt.state &= ~RT_WLAN_STATE_CONNECT;
        _sta_mgnt.state &= ~RT_WLAN_STATE_READY;
        user_event = RT_WLAN_EVT_STA_DISCONNECTED;
        user_buff.data = &_sta_mgnt.info;
        user_buff.len = sizeof(struct rt_wlan_info);
        if (rt_wlan_get_autoreconnect_mode())
        {
            TIME_START();
        }
        break;
    }
    case RT_WLAN_DEV_EVT_AP_START:
    {
        RT_WLAN_LOG_D("event: AP_START");
        _ap_mgnt.state |= RT_WLAN_STATE_ACTIVE;
        user_event = RT_WLAN_EVT_AP_START;
        user_buff.data = &_ap_mgnt.info;
        user_buff.len = sizeof(struct rt_wlan_info);
        break;
    }
    case RT_WLAN_DEV_EVT_AP_STOP:
    {
        RT_WLAN_LOG_D("event: AP_STOP");
        _ap_mgnt.state &= ~RT_WLAN_STATE_ACTIVE;
        user_event = RT_WLAN_EVT_AP_STOP;
        err = rt_wlan_sta_info_del_all(RT_WAITING_FOREVER);
        if (err != RT_NULL)
        {
            RT_WLAN_LOG_W("AP_STOP event handle fail");
        }
        user_buff.data = &_ap_mgnt.info;
        user_buff.len = sizeof(struct rt_wlan_info);
        break;
    }
    case RT_WLAN_DEV_EVT_AP_ASSOCIATED:
    {
        RT_WLAN_LOG_D("event: ASSOCIATED");
        user_event = RT_WLAN_EVT_AP_ASSOCIATED;
        if (user_buff.len != sizeof(struct rt_wlan_info))
            break;
        err = rt_wlan_sta_info_add(user_buff.data, RT_WAITING_FOREVER);
        if (err != RT_EOK)
        {
            RT_WLAN_LOG_W("AP_ASSOCIATED event handle fail");
        }
        break;
    }
    case RT_WLAN_DEV_EVT_AP_DISASSOCIATED:
    {
        RT_WLAN_LOG_D("event: DISASSOCIATED");
        user_event = RT_WLAN_EVT_AP_DISASSOCIATED;
        if (user_buff.len != sizeof(struct rt_wlan_info))
            break;
        err = rt_wlan_sta_info_del(user_buff.data, RT_WAITING_FOREVER);
        if (err != RT_EOK)
        {
            RT_WLAN_LOG_W("AP_DISASSOCIATED event handle fail");
        }
        break;
    }
    case RT_WLAN_DEV_EVT_AP_ASSOCIATE_FAILED:
    {
        RT_WLAN_LOG_D("event: AP_ASSOCIATE_FAILED");
        break;
    }
    case RT_WLAN_DEV_EVT_SCAN_REPORT:
    {
        RT_WLAN_LOG_D("event: SCAN_REPORT");
        user_event = RT_WLAN_EVT_SCAN_REPORT;
        if (user_buff.len != sizeof(struct rt_wlan_info))
            break;
        rt_wlan_scan_result_cache(user_buff.data, 0);
        break;
    }
    case RT_WLAN_DEV_EVT_SCAN_DONE:
    {
        RT_WLAN_LOG_D("event: SCAN_DONE");
        user_buff.data = &scan_result;
        user_buff.len = sizeof(scan_result);
        user_event = RT_WLAN_EVT_SCAN_DONE;
        break;
    }
    default :
    {
        RT_WLAN_LOG_D("event: UNKNOWN");
        return;
    }
    }

    /* send event */
    COMPLETE_LOCK();
    for (i = 0; i < sizeof(complete_tab) / sizeof(complete_tab[0]); i++)
    {
        if ((complete_tab[i] != RT_NULL))
        {
            complete_tab[i]->event_flag |= 0x1 << event;
            rt_event_send(&complete_tab[i]->complete, 0x1 << event);
            RT_WLAN_LOG_D("&complete_tab[i]->complete:0x%08x", &complete_tab[i]->complete);
        }
    }
    COMPLETE_UNLOCK();
#ifdef RT_WLAN_WORK_THREAD_ENABLE
    rt_wlan_send_to_thread(user_event, user_buff.data, user_buff.len);
#else
    {
        void *user_parameter;
        rt_wlan_event_handler handler = RT_NULL;
        rt_base_t level;
        /* Get user callback */
        if (user_event < RT_WLAN_EVT_MAX)
        {
            level = rt_hw_interrupt_disable();
            handler = event_tab[user_event].handler;
            user_parameter = event_tab[user_event].parameter;
            rt_hw_interrupt_enable(level);
        }

        /* run user callback fun */
        if (handler)
        {
            RT_WLAN_LOG_D("unknown thread run user callback, event:%d", user_event);
            handler(user_event, &user_buff, user_parameter);
        }
    }
#endif
}

static struct rt_wlan_complete_des *rt_wlan_complete_create(const char *name)
{
    struct rt_wlan_complete_des *complete;
    int i;

    complete = rt_malloc(sizeof(struct rt_wlan_complete_des));
    if (complete == RT_NULL)
    {
        RT_WLAN_LOG_E("complete event create failed");
        MGNT_UNLOCK();
        return complete;
    }
    rt_event_init(&complete->complete, name, RT_IPC_FLAG_FIFO);
    complete->event_flag = 0;
    //protect
    COMPLETE_LOCK();
    for (i = 0; i < sizeof(complete_tab) / sizeof(complete_tab[0]); i++)
    {
        if (complete_tab[i] == RT_NULL)
        {
            complete->index = i;
            complete_tab[i] = complete;
            break;
        }
    }
    COMPLETE_UNLOCK();

    if (i >= sizeof(complete_tab) / sizeof(complete_tab[0]))
    {
        rt_event_detach(&complete->complete);
        rt_free(complete);
        complete = RT_NULL;
    }

    return complete;
}

static rt_err_t rt_wlan_complete_wait(struct rt_wlan_complete_des *complete, rt_uint32_t event,
                                      rt_uint32_t timeout, rt_uint32_t *recved)
{
    if (complete == RT_NULL)
    {
        return -RT_ERROR;
    }

    /* Check whether there is a waiting event */
    if (complete->event_flag & event)
    {
        *recved = complete->event_flag;
        return RT_EOK;
    }
    else
    {
        return rt_event_recv(&complete->complete, event, RT_EVENT_FLAG_OR,
                             rt_tick_from_millisecond(timeout), recved);
    }
}

static void rt_wlan_complete_delete(struct rt_wlan_complete_des *complete)
{
    if (complete == RT_NULL)
    {
        return;
    }
    COMPLETE_LOCK();
    complete_tab[complete->index] = RT_NULL;
    COMPLETE_UNLOCK();
    rt_event_detach(&complete->complete);
    rt_free(complete);
}

rt_err_t rt_wlan_set_mode(const char *dev_name, rt_wlan_mode_t mode)
{
    rt_device_t device = RT_NULL;
    rt_err_t err;
    rt_int8_t up_event_flag = 0;
    rt_wlan_dev_event_handler handler = RT_NULL;

    if ((dev_name == RT_NULL) || (mode >= RT_WLAN_MODE_MAX))
    {
        RT_WLAN_LOG_E("Parameter Wrongful name:%s mode:%d", dev_name, mode);
        return -RT_EINVAL;
    }

    RT_WLAN_LOG_D("%s is run dev_name:%s mode:%s%s%s", __FUNCTION__, dev_name,
                  mode == RT_WLAN_NONE ? "NONE" : "",
                  mode == RT_WLAN_STATION ? "STA" : "",
                  mode == RT_WLAN_AP ? "AP" : ""
                 );

    /* find device */
    device = rt_device_find(dev_name);
    if (device == RT_NULL)
    {
        RT_WLAN_LOG_E("not find device, set mode failed! name:%s", dev_name);
        return -RT_EIO;
    }

    MGNT_LOCK();
    if (RT_WLAN_DEVICE(device)->mode == mode)
    {
        RT_WLAN_LOG_D("L:%d this device mode is set");
        MGNT_UNLOCK();
        return RT_EOK;
    }

    if ((mode == RT_WLAN_STATION) &&
            (RT_WLAN_DEVICE(device)->flags & RT_WLAN_FLAG_AP_ONLY))
    {
        RT_WLAN_LOG_I("this device ap mode only");
        MGNT_UNLOCK();
        return -RT_ERROR;
    }
    else if ((mode == RT_WLAN_AP) &&
             (RT_WLAN_DEVICE(device)->flags & RT_WLAN_FLAG_STA_ONLY))
    {
        RT_WLAN_LOG_I("this device sta mode only");
        MGNT_UNLOCK();
        return -RT_ERROR;
    }

    /*
     * device == sta  and change to ap,  should deinit
     * device == ap   and change to sta, should deinit
    */
    if (((mode == RT_WLAN_STATION) && (RT_WLAN_DEVICE(device) == AP_DEVICE())) ||
            ((mode == RT_WLAN_AP) && (RT_WLAN_DEVICE(device) == STA_DEVICE())))
    {
        err = rt_wlan_set_mode(dev_name, RT_WLAN_NONE);
        if (err != RT_EOK)
        {
            RT_WLAN_LOG_E("change mode failed!");
            MGNT_UNLOCK();
            return err;
        }
    }

    /* init device */
    err = rt_wlan_dev_init(RT_WLAN_DEVICE(device), mode);
    if (err != RT_EOK)
    {
        RT_WLAN_LOG_E("F:%s L:%d wlan init failed", __FUNCTION__, __LINE__);
        MGNT_UNLOCK();
        return err;
    }

    /* the mode is none */
    if (mode == RT_WLAN_NONE)
    {
        if (_sta_mgnt.device == RT_WLAN_DEVICE(device))
        {
            _sta_mgnt.device = RT_NULL;
            _sta_mgnt.state = 0;
            up_event_flag = 1;
            handler = RT_NULL;
        }
        else if (_ap_mgnt.device == RT_WLAN_DEVICE(device))
        {
            _ap_mgnt.state = 0;
            _ap_mgnt.device = RT_NULL;
            up_event_flag = 1;
            handler = RT_NULL;
        }
    }
    /* save sta device */
    else if (mode == RT_WLAN_STATION)
    {
        up_event_flag = 1;
        handler = rt_wlan_event_dispatch;
        _sta_mgnt.device = RT_WLAN_DEVICE(device);
    }
    /* save ap device */
    else if (mode == RT_WLAN_AP)
    {
        up_event_flag = 1;
        handler = rt_wlan_event_dispatch;
        _ap_mgnt.device = RT_WLAN_DEVICE(device);
    }

    /* update dev event handle */
    if (up_event_flag == 1)
    {
        if (handler)
        {
            if (mode == RT_WLAN_STATION)
            {
                rt_wlan_dev_register_event_handler(RT_WLAN_DEVICE(device), RT_WLAN_DEV_EVT_CONNECT, handler, RT_NULL);
                rt_wlan_dev_register_event_handler(RT_WLAN_DEVICE(device), RT_WLAN_DEV_EVT_CONNECT_FAIL, handler, RT_NULL);
                rt_wlan_dev_register_event_handler(RT_WLAN_DEVICE(device), RT_WLAN_DEV_EVT_DISCONNECT, handler, RT_NULL);
                rt_wlan_dev_register_event_handler(RT_WLAN_DEVICE(device), RT_WLAN_DEV_EVT_SCAN_REPORT, handler, RT_NULL);
                rt_wlan_dev_register_event_handler(RT_WLAN_DEVICE(device), RT_WLAN_DEV_EVT_SCAN_DONE, handler, RT_NULL);
            }
            else if (mode == RT_WLAN_AP)
            {
                rt_wlan_dev_register_event_handler(RT_WLAN_DEVICE(device), RT_WLAN_DEV_EVT_AP_START, handler, RT_NULL);
                rt_wlan_dev_register_event_handler(RT_WLAN_DEVICE(device), RT_WLAN_DEV_EVT_AP_STOP, handler, RT_NULL);
                rt_wlan_dev_register_event_handler(RT_WLAN_DEVICE(device), RT_WLAN_DEV_EVT_AP_ASSOCIATED, handler, RT_NULL);
                rt_wlan_dev_register_event_handler(RT_WLAN_DEVICE(device), RT_WLAN_DEV_EVT_AP_DISASSOCIATED, handler, RT_NULL);
                rt_wlan_dev_register_event_handler(RT_WLAN_DEVICE(device), RT_WLAN_DEV_EVT_AP_ASSOCIATE_FAILED, handler, RT_NULL);
            }
        }
        else
        {
            rt_wlan_dev_event_t event;
            handler = rt_wlan_event_dispatch;
            for (event = RT_WLAN_DEV_EVT_INIT_DONE; event < RT_WLAN_DEV_EVT_MAX; event++)
            {
                rt_wlan_dev_unregister_event_handler(RT_WLAN_DEVICE(device), event, handler);
            }
        }
    }
    MGNT_UNLOCK();

    /* Mount protocol */
#if defined(RT_WLAN_PROT_ENABLE) && defined(RT_WLAN_DEFAULT_PROT)
    if (err == RT_EOK)
    {
        rt_wlan_prot_attach(dev_name, RT_WLAN_DEFAULT_PROT);
    }
#endif
    return err;
}

rt_wlan_mode_t rt_wlan_get_mode(const char *dev_name)
{
    rt_device_t device = RT_NULL;
    rt_wlan_mode_t mode;

    if (dev_name == RT_NULL)
    {
        RT_WLAN_LOG_E("name is null");
        return RT_WLAN_NONE;
    }

    /* find device */
    device = rt_device_find(dev_name);
    if (device == RT_NULL)
    {
        RT_WLAN_LOG_E("device not find! name:%s", dev_name);
        return RT_WLAN_NONE;
    }

    /* get mode */
    mode = RT_WLAN_DEVICE(device)->mode;
    RT_WLAN_LOG_D("%s is run dev_name:%s mode:%s%s%s", __FUNCTION__, dev_name,
                  mode == RT_WLAN_NONE ? "NONE" : "",
                  mode == RT_WLAN_STATION ? "STA" : "",
                  mode == RT_WLAN_AP ? "AP" : "");

    return mode;
}

rt_bool_t rt_wlan_find_best_by_cache(const char *ssid, struct rt_wlan_info *info)
{
    int i, ssid_len;
    struct rt_wlan_info *info_best;
    struct rt_wlan_scan_result *result;

    ssid_len = rt_strlen(ssid);
    result = &scan_result;
    info_best = RT_NULL;

    SRESULT_LOCK();
    for (i = 0; i < result->num; i++)
    {
        /* SSID is equal. */
        if ((result->info[i].ssid.len == ssid_len) &&
                (rt_memcmp((char *)&result->info[i].ssid.val[0], ssid, ssid_len) == 0))
        {
            if (info_best == RT_NULL)
            {
                info_best = &result->info[i];
                continue;
            }
            /* Signal strength effective */
            if ((result->info[i].rssi < 0) && (info_best->rssi < 0))
            {
                /* Find the strongest signal. */
                if (result->info[i].rssi > info_best->rssi)
                {
                    info_best = &result->info[i];
                    continue;
                }
                else if (result->info[i].rssi < info_best->rssi)
                {
                    continue;
                }
            }

            /* Finding the fastest signal */
            if (result->info[i].datarate > info_best->datarate)
            {
                info_best = &result->info[i];
                continue;
            }
        }
    }
    SRESULT_UNLOCK();

    if (info_best == RT_NULL)
        return RT_FALSE;

    *info = *info_best;
    return RT_TRUE;
}

rt_err_t rt_wlan_connect(const char *ssid, const char *password)
{
    rt_err_t err = RT_EOK;
    int ssid_len = 0;
    struct rt_wlan_info info;
    struct rt_wlan_complete_des *complete;
    rt_uint32_t set = 0, recved = 0;
    rt_uint32_t scan_retry = RT_WLAN_SCAN_RETRY_CNT;

    /* sta dev Can't be NULL */
    if (_sta_is_null())
    {
        return -RT_EIO;
    }
    RT_WLAN_LOG_D("%s is run ssid:%s password:%s", __FUNCTION__, ssid, password);
    if (ssid == RT_NULL)
    {
        RT_WLAN_LOG_E("ssid is null!");
        return -RT_EINVAL;
    }
    ssid_len = rt_strlen(ssid);
    if (ssid_len > RT_WLAN_SSID_MAX_LENGTH)
    {
        RT_WLAN_LOG_E("ssid is to long! ssid:%s len:%d", ssid, ssid_len);
        return -RT_EINVAL;
    }

    if ((rt_wlan_is_connected() == RT_TRUE) &&
            (rt_strcmp((char *)&_sta_mgnt.info.ssid.val[0], ssid) == 0))
    {
        RT_WLAN_LOG_I("wifi is connect ssid:%s", ssid);
        return RT_EOK;
    }
    /* get info from cache */
    INVALID_INFO(&info);
    MGNT_LOCK();
    while (scan_retry-- && rt_wlan_find_best_by_cache(ssid, &info) != RT_TRUE)
    {
        rt_wlan_scan_sync();
    }
    rt_wlan_scan_result_clean();

    if (info.ssid.len <= 0)
    {
        RT_WLAN_LOG_W("not find ap! ssid:%s", ssid);
        MGNT_UNLOCK();
        return -RT_ERROR;
    }

    RT_WLAN_LOG_D("find best info ssid:%s mac: %02x %02x %02x %02x %02x %02x",
                  info.ssid.val, info.bssid[0], info.bssid[1], info.bssid[2], info.bssid[3], info.bssid[4], info.bssid[5]);

    /* create event wait complete */
    complete = rt_wlan_complete_create("join");
    if (complete == RT_NULL)
    {
        MGNT_UNLOCK();
        return -RT_ENOMEM;
    }
    /* run connect adv */
    err = rt_wlan_connect_adv(&info, password);
    if (err != RT_EOK)
    {
        rt_wlan_complete_delete(complete);
        MGNT_UNLOCK();
        return err;
    }

    /* Initializing events that need to wait */
    set |= 0x1 << RT_WLAN_DEV_EVT_CONNECT;
    set |= 0x1 << RT_WLAN_DEV_EVT_CONNECT_FAIL;
    /* Check whether there is a waiting event */
    rt_wlan_complete_wait(complete, set, RT_WLAN_CONNECT_WAIT_MS, &recved);
    rt_wlan_complete_delete(complete);
    /* check event */
    set = 0x1 << RT_WLAN_DEV_EVT_CONNECT;
    if (!(recved & set))
    {
        RT_WLAN_LOG_I("wifi connect failed!");
        MGNT_UNLOCK();
        return -RT_ERROR;
    }
    MGNT_UNLOCK();
    return err;
}

rt_err_t rt_wlan_connect_adv(struct rt_wlan_info *info, const char *password)
{
    int password_len = 0;
    rt_err_t err = RT_EOK;

    if (_sta_is_null())
    {
        return -RT_EIO;
    }
    if (info == RT_NULL)
    {
        RT_WLAN_LOG_E("info is null!");
        return -RT_EINVAL;
    }
    RT_WLAN_LOG_D("%s is run ssid:%s password:%s", __FUNCTION__, info->ssid.val, password);
    /* Parameter checking */
    if (password != RT_NULL)
    {
        password_len = rt_strlen(password);
        if (password_len > RT_WLAN_PASSWORD_MAX_LENGTH)
        {
            RT_WLAN_LOG_E("password is to long! password:%s len:%d", password, password_len);
            return -RT_EINVAL;
        }
    }
    if (info->ssid.len == 0 || info->ssid.len > RT_WLAN_SSID_MAX_LENGTH)
    {
        RT_WLAN_LOG_E("ssid is zero or to long! ssid:%s len:%d", info->ssid.val, info->ssid.len);
        return -RT_EINVAL;
    }
    /* is connect ? */
    MGNT_LOCK();
    if (rt_wlan_is_connected())
    {
        if ((_sta_mgnt.info.ssid.len == info->ssid.len) &&
                (_sta_mgnt.key.len == password_len) &&
                (rt_memcmp(&_sta_mgnt.info.ssid.val[0], &info->ssid.val[0], info->ssid.len) == 0) &&
                (rt_memcmp(&_sta_mgnt.info.bssid[0], &info->bssid[0], RT_WLAN_BSSID_MAX_LENGTH) == 0) &&
                (rt_memcmp(&_sta_mgnt.key.val[0], password, password_len) == 0))
        {
            RT_WLAN_LOG_I("wifi Already Connected");
            MGNT_UNLOCK();
            return RT_EOK;
        }

        err = rt_wlan_disconnect();
        if (err != RT_EOK)
        {
            MGNT_UNLOCK();
            return err;
        }
    }

    /* save info */
    rt_enter_critical();
    _sta_mgnt.info = *info;
    rt_memcpy(&_sta_mgnt.key.val, password, password_len);
    _sta_mgnt.key.len = password_len;
    _sta_mgnt.key.val[password_len] = '\0';
    rt_exit_critical();
    /* run wifi connect */
    _sta_mgnt.state |= RT_WLAN_STATE_CONNECTING;
    err = rt_wlan_dev_connect(_sta_mgnt.device, info, password, password_len);
    if (err != RT_EOK)
    {
        rt_enter_critical();
        rt_memset(&_sta_mgnt.info, 0, sizeof(struct rt_wlan_ssid));
        rt_memset(&_sta_mgnt.key, 0, sizeof(struct rt_wlan_key));
        rt_exit_critical();
        _sta_mgnt.state &= ~RT_WLAN_STATE_CONNECTING;
        MGNT_UNLOCK();
        return err;
    }

    MGNT_UNLOCK();
    return err;
}

rt_err_t rt_wlan_disconnect(void)
{
    rt_err_t err;
    struct rt_wlan_complete_des *complete;
    rt_uint32_t recved = 0, set = 0;

    /* ap dev Can't be empty */
    if (_sta_is_null())
    {
        return -RT_EIO;
    }
    RT_WLAN_LOG_D("%s is run", __FUNCTION__);

    /* run disconnect */
    MGNT_LOCK();
    /* create event wait complete */
    complete = rt_wlan_complete_create("disc");
    if (complete == RT_NULL)
    {
        MGNT_UNLOCK();
        return -RT_ENOMEM;
    }
    err = rt_wlan_dev_disconnect(_sta_mgnt.device);
    if (err != RT_EOK)
    {
        RT_WLAN_LOG_E("wifi disconnect fail");
        rt_wlan_complete_delete(complete);
        MGNT_UNLOCK();
        return err;
    }
    /* Initializing events that need to wait */
    set |= 0x1 << RT_WLAN_DEV_EVT_DISCONNECT;
    /* Check whether there is a waiting event */
    rt_wlan_complete_wait(complete, set, RT_WLAN_CONNECT_WAIT_MS, &recved);
    rt_wlan_complete_delete(complete);
    /* check event */
    set = 0x1 << RT_WLAN_DEV_EVT_DISCONNECT;
    if (!(recved & set))
    {
        RT_WLAN_LOG_E("disconnect failed!");
        MGNT_UNLOCK();
        return -RT_ERROR;
    }
    RT_WLAN_LOG_I("disconnect success!");
    MGNT_UNLOCK();
    return err;
}

rt_bool_t rt_wlan_is_connected(void)
{
    rt_bool_t _connect;

    if (_sta_is_null())
    {
        return RT_FALSE;
    }
    _connect = _sta_mgnt.state & RT_WLAN_STATE_CONNECT ? RT_TRUE : RT_FALSE;
    RT_WLAN_LOG_D("%s is run : %s", __FUNCTION__, _connect ? "connect" : "disconnect");
    return _connect;
}

rt_bool_t rt_wlan_is_ready(void)
{
    rt_bool_t _ready;

    if (_sta_is_null())
    {
        return RT_FALSE;
    }
    _ready = _sta_mgnt.state & RT_WLAN_STATE_READY ? RT_TRUE : RT_FALSE;
    RT_WLAN_LOG_D("%s is run : %s", __FUNCTION__, _ready ? "ready" : "not ready");
    return _ready;
}

rt_err_t rt_wlan_set_mac(rt_uint8_t mac[6])
{
    rt_err_t err = RT_EOK;

    if (_sta_is_null())
    {
        return -RT_EIO;
    }
    RT_WLAN_LOG_D("%s is run mac: %02x:%02x:%02x:%02x:%02x:%02x",
                  __FUNCTION__, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    MGNT_LOCK();
    err = rt_wlan_dev_set_mac(STA_DEVICE(), mac);
    if (err != RT_EOK)
    {
        RT_WLAN_LOG_E("set sta mac addr fail");
        MGNT_UNLOCK();
        return err;
    }
    MGNT_UNLOCK();
    return err;
}

rt_err_t rt_wlan_get_mac(rt_uint8_t mac[6])
{
    rt_err_t err = RT_EOK;

    if (_sta_is_null())
    {
        return -RT_EIO;
    }
    MGNT_LOCK();
    err = rt_wlan_dev_get_mac(STA_DEVICE(), mac);
    if (err != RT_EOK)
    {
        RT_WLAN_LOG_E("get sta mac addr fail");
        MGNT_UNLOCK();
        return err;
    }
    RT_WLAN_LOG_D("%s is run mac: %02x:%02x:%02x:%02x:%02x:%02x",
                  __FUNCTION__, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    MGNT_UNLOCK();
    return err;
}

rt_err_t rt_wlan_get_info(struct rt_wlan_info *info)
{
    if (_sta_is_null())
    {
        return -RT_EIO;
    }
    RT_WLAN_LOG_D("%s is run", __FUNCTION__);

    if (rt_wlan_is_connected() == RT_TRUE)
    {
        *info = _sta_mgnt.info;
        info->rssi = rt_wlan_get_rssi();
        return RT_EOK;
    }
    return -RT_ERROR;
}

int rt_wlan_get_rssi(void)
{
    int rssi = 0;

    if (_sta_is_null())
    {
        return -RT_EIO;
    }

    MGNT_LOCK();
    rssi = rt_wlan_dev_get_rssi(STA_DEVICE());
    RT_WLAN_LOG_D("%s is run rssi:%d", __FUNCTION__, rssi);
    MGNT_UNLOCK();
    return rssi;
}

rt_err_t rt_wlan_start_ap(const char *ssid, const char *password)
{
    rt_err_t err = RT_EOK;
    int ssid_len = 0;
    struct rt_wlan_info info;
    struct rt_wlan_complete_des *complete;
    rt_uint32_t set = 0, recved = 0;

    if (_ap_is_null())
    {
        return -RT_EIO;
    }
    if (ssid == RT_NULL) return -RT_EINVAL;

    rt_memset(&info, 0, sizeof(struct rt_wlan_info));
    RT_WLAN_LOG_D("%s is run ssid:%s password:%s", __FUNCTION__, ssid, password);
    if (password)
    {
        info.security = SECURITY_WPA2_AES_PSK;
    }
    ssid_len = rt_strlen(ssid);
    if (ssid_len > RT_WLAN_SSID_MAX_LENGTH)
    {
        RT_WLAN_LOG_E("ssid is to long! len:%d", ssid_len);
    }

    /* copy info */
    rt_memcpy(&info.ssid.val, ssid, ssid_len);
    info.ssid.len = ssid_len;
    info.channel = 6;
    info.band = RT_802_11_BAND_2_4GHZ;

    /* Initializing events that need to wait */
    MGNT_LOCK();
    /* create event wait complete */
    complete = rt_wlan_complete_create("start_ap");
    if (complete == RT_NULL)
    {
        MGNT_UNLOCK();
        return -RT_ENOMEM;
    }

    /* start ap */
    err = rt_wlan_start_ap_adv(&info, password);
    if (err != RT_EOK)
    {
        rt_wlan_complete_delete(complete);
        RT_WLAN_LOG_I("start ap failed!");
        MGNT_UNLOCK();
        return err;
    }

    /* Initializing events that need to wait */
    set |= 0x1 << RT_WLAN_DEV_EVT_AP_START;
    set |= 0x1 << RT_WLAN_DEV_EVT_AP_STOP;
    /* Check whether there is a waiting event */
    rt_wlan_complete_wait(complete, set, RT_WLAN_START_AP_WAIT_MS, &recved);
    rt_wlan_complete_delete(complete);
    /* check event */
    set = 0x1 << RT_WLAN_DEV_EVT_AP_START;
    if (!(recved & set))
    {
        RT_WLAN_LOG_I("start ap failed!");
        MGNT_UNLOCK();
        return -RT_ERROR;
    }
    RT_WLAN_LOG_I("start ap successs!");
    MGNT_UNLOCK();
    return err;
}

rt_err_t rt_wlan_start_ap_adv(struct rt_wlan_info *info, const char *password)
{
    rt_err_t err = RT_EOK;
    int password_len = 0;

    if (_ap_is_null())
    {
        return -RT_EIO;
    }
    RT_WLAN_LOG_D("%s is run", __FUNCTION__);
    if (password != RT_NULL)
    {
        password_len = rt_strlen(password);
    }
    if (password_len > RT_WLAN_PASSWORD_MAX_LENGTH)
    {
        RT_WLAN_LOG_E("key is to long! len:%d", password_len);
        return -RT_EINVAL;
    }
    /* is start up ? */
    MGNT_LOCK();
    if (rt_wlan_ap_is_active())
    {
        if ((_ap_mgnt.info.ssid.len == info->ssid.len) &&
                (_ap_mgnt.info.security == info->security) &&
                (_ap_mgnt.info.channel == info->channel) &&
                (_ap_mgnt.info.hidden == info->hidden) &&
                (_ap_mgnt.key.len == password_len) &&
                (rt_memcmp(&_ap_mgnt.info.ssid.val[0], &info->ssid.val[0], info->ssid.len) == 0) &&
                (rt_memcmp(&_ap_mgnt.key.val[0], password, password_len)))
        {
            RT_WLAN_LOG_D("wifi Already Start");
            MGNT_UNLOCK();
            return RT_EOK;
        }
    }

    err = rt_wlan_dev_ap_start(AP_DEVICE(), info, password, password_len);
    if (err != RT_EOK)
    {
        MGNT_UNLOCK();
        return err;
    }
    rt_memcpy(&_ap_mgnt.info, info, sizeof(struct rt_wlan_info));
    rt_memcpy(&_ap_mgnt.key.val, password, password_len);
    _ap_mgnt.key.len = password_len;

    MGNT_UNLOCK();
    return err;
}

rt_bool_t rt_wlan_ap_is_active(void)
{
    rt_bool_t _active = RT_FALSE;

    if (_ap_is_null())
    {
        return RT_FALSE;
    }

    _active = _ap_mgnt.state & RT_WLAN_STATE_ACTIVE ? RT_TRUE : RT_FALSE;
    RT_WLAN_LOG_D("%s is run active:%s", __FUNCTION__, _active ? "Active" : "Inactive");
    return _active;
}

rt_err_t rt_wlan_ap_stop(void)
{
    rt_err_t err = RT_EOK;
    struct rt_wlan_complete_des *complete;
    rt_uint32_t set = 0, recved = 0;

    if (_ap_is_null())
    {
        return -RT_EIO;
    }
    RT_WLAN_LOG_D("%s is run", __FUNCTION__);

    MGNT_LOCK();
    /* create event wait complete */
    complete = rt_wlan_complete_create("stop_ap");
    if (complete == RT_NULL)
    {
        MGNT_UNLOCK();
        return -RT_ENOMEM;
    }
    err = rt_wlan_dev_ap_stop(AP_DEVICE());
    if (err != RT_EOK)
    {
        RT_WLAN_LOG_E("ap stop fail");
        rt_wlan_complete_delete(complete);
        MGNT_UNLOCK();
        return err;
    }
    /* Initializing events that need to wait */
    set |= 0x1 << RT_WLAN_DEV_EVT_AP_STOP;
    /* Check whether there is a waiting event */
    rt_wlan_complete_wait(complete, set, RT_WLAN_START_AP_WAIT_MS, &recved);
    rt_wlan_complete_delete(complete);
    /* check event */
    set = 0x1 << RT_WLAN_DEV_EVT_AP_STOP;
    if (!(recved & set))
    {
        RT_WLAN_LOG_I("ap stop failed!");
        MGNT_UNLOCK();
        return -RT_ERROR;
    }
    RT_WLAN_LOG_I("ap stop success!");
    MGNT_UNLOCK();
    return err;
}

rt_err_t rt_wlan_ap_get_info(struct rt_wlan_info *info)
{
    if (_ap_is_null())
    {
        return -RT_EIO;
    }
    RT_WLAN_LOG_D("%s is run", __FUNCTION__);

    if (rt_wlan_ap_is_active() == RT_TRUE)
    {
        *info = _ap_mgnt.info;
        return RT_EOK;
    }
    return -RT_ERROR;
}

/* get sta number  */
int rt_wlan_ap_get_sta_num(void)
{
    int sta_num = 0;

    STAINFO_LOCK();
    sta_num = sta_info.num;
    STAINFO_UNLOCK();
    RT_WLAN_LOG_D("%s is run num:%d", __FUNCTION__, sta_num);
    return sta_num;
}

/* get sta info */
int rt_wlan_ap_get_sta_info(struct rt_wlan_info *info, int num)
{
    int sta_num = 0, i = 0;
    struct rt_wlan_sta_list *sta_list;

    STAINFO_LOCK();
    /* sta_num = min(sta_info.num, num) */
    sta_num = sta_info.num > num ? num : sta_info.num;
    for (sta_list = sta_info.node; sta_list != RT_NULL && i < sta_num; sta_list = sta_list->next)
    {
        info[i] = sta_list->info;
        i ++;
    }
    STAINFO_UNLOCK();
    RT_WLAN_LOG_D("%s is run num:%d", __FUNCTION__, i);
    return i;
}

/* deauth sta */
rt_err_t rt_wlan_ap_deauth_sta(rt_uint8_t *mac)
{
    rt_err_t err = RT_EOK;
    struct rt_wlan_sta_list *sta_list;
    rt_bool_t find_flag = RT_FALSE;

    if (_ap_is_null())
    {
        return -RT_EIO;
    }
    RT_WLAN_LOG_D("%s is run mac: %02x:%02x:%02x:%02x:%02x:%02x:%d",
                  __FUNCTION__, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    if (mac == RT_NULL)
    {
        RT_WLAN_LOG_E("mac addr is null");
        return -RT_EINVAL;
    }

    MGNT_LOCK();
    if (sta_info.node == RT_NULL || sta_info.num == 0)
    {
        RT_WLAN_LOG_E("No AP");
        MGNT_UNLOCK();
        return -RT_ERROR;
    }

    STAINFO_LOCK();
    /* Search for MAC address from sta list */
    for (sta_list = sta_info.node; sta_list != RT_NULL; sta_list = sta_list->next)
    {
        if (rt_memcmp(&sta_list->info.bssid[0], &mac[0], RT_WLAN_BSSID_MAX_LENGTH) == 0)
        {
            find_flag = RT_TRUE;
            break;
        }
    }
    STAINFO_UNLOCK();

    /* No MAC address was found. return */
    if (find_flag != RT_TRUE)
    {
        RT_WLAN_LOG_E("Not find mac addr");
        MGNT_UNLOCK();
        return -RT_ERROR;
    }

    /* Kill STA */
    err = rt_wlan_dev_ap_deauth(AP_DEVICE(), mac);
    if (err != RT_NULL)
    {
        RT_WLAN_LOG_E("deauth sta failed");
        MGNT_UNLOCK();
        return err;
    }

    MGNT_UNLOCK();
    return err;
}

rt_err_t rt_wlan_ap_set_country(rt_country_code_t country_code)
{
    rt_err_t err = RT_EOK;

    if (_ap_is_null())
    {
        return -RT_EIO;
    }
    RT_WLAN_LOG_D("%s is run country:%d", __FUNCTION__, country_code);
    MGNT_LOCK();
    err = rt_wlan_dev_set_country(AP_DEVICE(), country_code);
    MGNT_UNLOCK();
    return err;
}

rt_country_code_t rt_wlan_ap_get_country(void)
{
    rt_country_code_t country_code = RT_COUNTRY_UNKNOWN;

    if (_ap_is_null())
    {
        return country_code;
    }
    MGNT_LOCK();
    country_code = rt_wlan_dev_get_country(AP_DEVICE());
    RT_WLAN_LOG_D("%s is run country:%d", __FUNCTION__, country_code);
    MGNT_UNLOCK();
    return country_code;
}

void rt_wlan_config_autoreconnect(rt_bool_t enable)
{
#ifdef RT_WLAN_AUTO_CONNECT_ENABLE
    RT_WLAN_LOG_D("%s is run enable:%d", __FUNCTION__, enable);

    MGNT_LOCK();
    if (enable)
    {
        TIME_START();
        _sta_mgnt.flags |= RT_WLAN_STATE_AUTOEN;
    }
    else
    {
        TIME_STOP();
        _sta_mgnt.flags &= ~RT_WLAN_STATE_AUTOEN;
    }
    MGNT_UNLOCK();
#endif
}

rt_bool_t rt_wlan_get_autoreconnect_mode(void)
{
#ifdef RT_WLAN_AUTO_CONNECT_ENABLE
    rt_bool_t enable = 0;

    enable = _sta_mgnt.flags & RT_WLAN_STATE_AUTOEN ? 1 : 0;
    RT_WLAN_LOG_D("%s is run enable:%d", __FUNCTION__, enable);
    return enable;
#else
    return RT_FALSE;
#endif
}

/* Call the underlying scan function, which is asynchronous.
The hotspots scanned are returned by callbacks */
rt_err_t rt_wlan_scan(void)
{
    rt_err_t err = RT_EOK;

    if (_sta_is_null())
    {
        return -RT_EIO;
    }
    RT_WLAN_LOG_D("%s is run", __FUNCTION__);

    MGNT_LOCK();
    err = rt_wlan_dev_scan(STA_DEVICE(), RT_NULL);
    MGNT_UNLOCK();
    return err;
}

struct rt_wlan_scan_result *rt_wlan_scan_sync(void)
{
    struct rt_wlan_scan_result *result;

    /* Execute synchronous scan function */
    MGNT_LOCK();
    result = rt_wlan_scan_with_info(RT_NULL);
    MGNT_UNLOCK();
    return result;
}

struct rt_wlan_scan_result *rt_wlan_scan_with_info(struct rt_wlan_info *info)
{
    rt_err_t err = RT_EOK;
    struct rt_wlan_complete_des *complete;
    rt_uint32_t set = 0, recved = 0;
    static struct rt_wlan_info scan_filter_info;
    rt_base_t level;
    struct rt_wlan_scan_result *result;

    if (_sta_is_null())
    {
        return RT_NULL;
    }
    RT_WLAN_LOG_D("%s is run", __FUNCTION__);
    if (info != RT_NULL && info->ssid.len > RT_WLAN_SSID_MAX_LENGTH)
    {
        RT_WLAN_LOG_E("ssid is to long!");
        return RT_NULL;
    }

    /* Create an event that needs to wait. */
    MGNT_LOCK();
    complete = rt_wlan_complete_create("scan");
    if (complete == RT_NULL)
    {
        MGNT_UNLOCK();
        return &scan_result;
    }

    /* add scan info filter */
    if (info)
    {
        scan_filter_info = *info;
        level = rt_hw_interrupt_disable();
        scan_filter = &scan_filter_info;
        rt_hw_interrupt_enable(level);
    }

    /* run scan */
    err = rt_wlan_dev_scan(STA_DEVICE(), info);
    if (err != RT_EOK)
    {
        rt_wlan_complete_delete(complete);
        RT_WLAN_LOG_E("scan sync fail");
        result = RT_NULL;
        goto scan_exit;
    }

    /* Initializing events that need to wait */
    set |= 0x1 << RT_WLAN_DEV_EVT_SCAN_DONE;
    /* Check whether there is a waiting event */
    rt_wlan_complete_wait(complete, set, RT_WLAN_CONNECT_WAIT_MS, &recved);
    rt_wlan_complete_delete(complete);
    /* check event */
    set = 0x1 << RT_WLAN_DEV_EVT_SCAN_DONE;
    if (!(recved & set))
    {
        RT_WLAN_LOG_E("scan wait timeout!");
        result = &scan_result;
        goto scan_exit;
    }

scan_exit:
    MGNT_UNLOCK();
    level = rt_hw_interrupt_disable();
    scan_filter = RT_NULL;
    rt_hw_interrupt_enable(level);
    result = &scan_result;
    return result;
}

int rt_wlan_scan_get_info_num(void)
{
    int num = 0;

    num = scan_result.num;
    RT_WLAN_LOG_D("%s is run num:%d", __FUNCTION__, num);
    return num;
}

int rt_wlan_scan_get_info(struct rt_wlan_info *info, int num)
{
    int _num = 0;

    SRESULT_LOCK();
    if (scan_result.num && num > 0)
    {
        _num = scan_result.num > num ? num : scan_result.num;
        rt_memcpy(info, scan_result.info, _num * sizeof(struct rt_wlan_info));
    }
    SRESULT_UNLOCK();
    return _num;
}

struct rt_wlan_scan_result *rt_wlan_scan_get_result(void)
{
    return &scan_result;
}

void rt_wlan_scan_result_clean(void)
{
    MGNT_LOCK();
    SRESULT_LOCK();

    /* If there is data */
    if (scan_result.num)
    {
        scan_result.num = 0;
        rt_free(scan_result.info);
        scan_result.info = RT_NULL;
    }
    SRESULT_UNLOCK();
    MGNT_UNLOCK();
}

int rt_wlan_scan_find_cache(struct rt_wlan_info *info, struct rt_wlan_info *out_info, int num)
{
    int i = 0, count = 0;
    struct rt_wlan_info *scan_info;
    rt_bool_t is_equ;

    if ((out_info == RT_NULL) || (info == RT_NULL) || (num <= 0))
    {
        return 0;
    }
    SRESULT_LOCK();
    /* Traversing the cache to find a qualified hot spot information */
    for (i = 0; (i < scan_result.num) && (count < num); i++)
    {
        scan_info = &scan_result.info[i];
        is_equ = rt_wlan_info_isequ(scan_info, info);
        /* Determine whether to find */
        if (is_equ)
        {
            rt_memcpy(&out_info[count], scan_info, sizeof(struct rt_wlan_info));
            count ++;
        }
    }
    SRESULT_UNLOCK();

    return count;
}

rt_err_t rt_wlan_set_powersave(int level)
{
    rt_err_t err = RT_EOK;

    if (_sta_is_null())
    {
        return -RT_EIO;
    }
    RT_WLAN_LOG_D("%s is run", __FUNCTION__);
    MGNT_LOCK();
    err = rt_wlan_dev_set_powersave(STA_DEVICE(), level);
    MGNT_UNLOCK();
    return err;
}

int rt_wlan_get_powersave(void)
{
    int level;

    if (_sta_is_null())
    {
        return -1;
    }
    RT_WLAN_LOG_D("%s is run", __FUNCTION__);
    MGNT_LOCK();
    level = rt_wlan_dev_get_powersave(STA_DEVICE());
    MGNT_UNLOCK();
    return level;
}

rt_err_t rt_wlan_register_event_handler(rt_wlan_event_t event, rt_wlan_event_handler handler, void *parameter)
{
    rt_base_t level;

    if (event >= RT_WLAN_EVT_MAX)
    {
        return RT_EINVAL;
    }
    RT_WLAN_LOG_D("%s is run event:%d", __FUNCTION__, event);

    MGNT_LOCK();
    /* Registering Callbacks */
    level = rt_hw_interrupt_disable();
    event_tab[event].handler = handler;
    event_tab[event].parameter = parameter;
    rt_hw_interrupt_enable(level);
    MGNT_UNLOCK();
    return RT_EOK;
}

rt_err_t rt_wlan_unregister_event_handler(rt_wlan_event_t event)
{
    rt_base_t level;

    if (event >= RT_WLAN_EVT_MAX)
    {
        return RT_EINVAL;
    }
    RT_WLAN_LOG_D("%s is run event:%d", __FUNCTION__, event);
    MGNT_LOCK();
    /* unregister*/
    level = rt_hw_interrupt_disable();
    event_tab[event].handler = RT_NULL;
    event_tab[event].parameter = RT_NULL;
    rt_hw_interrupt_enable(level);
    MGNT_UNLOCK();
    return RT_EOK;
}

void rt_wlan_mgnt_lock(void)
{
    MGNT_LOCK();
}

void rt_wlan_mgnt_unlock(void)
{
    MGNT_UNLOCK();
}

int rt_wlan_prot_ready_event(struct rt_wlan_device *wlan, struct rt_wlan_buff *buff)
{
    rt_base_t level;

    if ((wlan == RT_NULL) || (_sta_mgnt.device != wlan) ||
            (!(_sta_mgnt.state & RT_WLAN_STATE_CONNECT)))
    {
        return -1;
    }
    if (_sta_mgnt.state & RT_WLAN_STATE_READY)
    {
        return 0;
    }
    level = rt_hw_interrupt_disable();
    _sta_mgnt.state |= RT_WLAN_STATE_READY;
    rt_hw_interrupt_enable(level);
#ifdef RT_WLAN_WORK_THREAD_ENABLE
    rt_wlan_send_to_thread(RT_WLAN_EVT_READY, buff->data, buff->len);
#else
    {
        void *user_parameter;
        rt_wlan_event_handler handler = RT_NULL;

        level = rt_hw_interrupt_disable();
        handler = event_tab[RT_WLAN_EVT_READY].handler;
        user_parameter = event_tab[RT_WLAN_EVT_READY].parameter;
        rt_hw_interrupt_enable(level);
        if (handler)
        {
            handler(RT_WLAN_EVT_READY, buff, user_parameter);
        }
    }
#endif
    return 0;
}

int rt_wlan_init(void)
{
    static rt_int8_t _init_flag = 0;

    /* Execute only once */
    if (_init_flag == 0)
    {
        rt_memset(&_sta_mgnt, 0, sizeof(struct rt_wlan_mgnt_des));
        rt_memset(&_ap_mgnt, 0, sizeof(struct rt_wlan_mgnt_des));
        rt_memset(&scan_result, 0, sizeof(struct rt_wlan_scan_result));
        rt_memset(&sta_info, 0, sizeof(struct rt_wlan_sta_des));
        rt_mutex_init(&mgnt_mutex, "mgnt", RT_IPC_FLAG_FIFO);
        rt_mutex_init(&scan_result_mutex, "scan", RT_IPC_FLAG_FIFO);
        rt_mutex_init(&sta_info_mutex, "sta", RT_IPC_FLAG_FIFO);
        rt_mutex_init(&complete_mutex, "complete", RT_IPC_FLAG_FIFO);
#ifdef RT_WLAN_AUTO_CONNECT_ENABLE
        rt_timer_init(&reconnect_time, "wifi_tim", rt_wlan_cyclic_check, RT_NULL,
                      rt_tick_from_millisecond(AUTO_CONNECTION_PERIOD_MS),
                      RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);
#endif
        _init_flag = 1;
    }
    return 0;
}
INIT_PREV_EXPORT(rt_wlan_init);

#endif
