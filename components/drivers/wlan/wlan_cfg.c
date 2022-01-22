/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-06     tyx          the first version
 */

#include <rtthread.h>
#include <wlan_cfg.h>

#define DBG_TAG "WLAN.cfg"
#ifdef RT_WLAN_CFG_DEBUG
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_INFO
#endif /* RT_WLAN_CFG_DEBUG */
#include <rtdbg.h>

#ifdef RT_WLAN_CFG_ENABLE

#define WLAN_CFG_LOCK()      (rt_mutex_take(&cfg_mutex, RT_WAITING_FOREVER))
#define WLAN_CFG_UNLOCK()    (rt_mutex_release(&cfg_mutex))

#if RT_WLAN_CFG_INFO_MAX < 1
#error "The minimum configuration is 1"
#endif

struct cfg_save_info_head
{
    rt_uint32_t magic;
    rt_uint32_t len;
    rt_uint32_t num;
    rt_uint32_t crc;
};

struct rt_wlan_cfg_des
{
    rt_uint32_t num;
    struct rt_wlan_cfg_info *cfg_info;
};

static struct rt_wlan_cfg_des *cfg_cache;
static const struct rt_wlan_cfg_ops *cfg_ops;
static struct rt_mutex cfg_mutex;

/*
 * CRC16_CCITT
 */
static rt_uint16_t rt_wlan_cal_crc(rt_uint8_t *buff, int len)
{
    rt_uint16_t wCRCin = 0x0000;
    rt_uint16_t wCPoly = 0x1021;
    rt_uint8_t  wChar = 0;

    while (len--)
    {
        int i;

        wChar = *(buff++);
        wCRCin ^= (wChar << 8);

        for (i = 0; i < 8; i++)
        {
            if (wCRCin & 0x8000)
                wCRCin = (wCRCin << 1) ^ wCPoly;
            else
                wCRCin = wCRCin << 1;
        }
    }
    return wCRCin;
}

void rt_wlan_cfg_init(void)
{
    /* init cache memory */
    if (cfg_cache == RT_NULL)
    {
        cfg_cache = rt_malloc(sizeof(struct rt_wlan_cfg_des));
        if (cfg_cache != RT_NULL)
        {
            rt_memset(cfg_cache, 0, sizeof(struct rt_wlan_cfg_des));
        }
        /* init mutex lock */
        rt_mutex_init(&cfg_mutex, "wlan_cfg", RT_IPC_FLAG_PRIO);
    }
}

void rt_wlan_cfg_set_ops(const struct rt_wlan_cfg_ops *ops)
{
    rt_wlan_cfg_init();

    WLAN_CFG_LOCK();
    /* save ops pointer */
    cfg_ops = ops;
    WLAN_CFG_UNLOCK();
}

/* save config data */
rt_err_t rt_wlan_cfg_cache_save(void)
{
    rt_err_t err = RT_EOK;
    struct cfg_save_info_head *info_pkg;
    int len = 0;

    if ((cfg_ops == RT_NULL) || (cfg_ops->write_cfg == RT_NULL))
        return RT_EOK;

    WLAN_CFG_LOCK();
    len = sizeof(struct cfg_save_info_head) + sizeof(struct rt_wlan_cfg_info) * cfg_cache->num;
    info_pkg = rt_malloc(len);
    if (info_pkg == RT_NULL)
    {
        WLAN_CFG_UNLOCK();
        return -RT_ENOMEM;
    }
    info_pkg->magic = RT_WLAN_CFG_MAGIC;
    info_pkg->len = len;
    info_pkg->num = cfg_cache->num;
    /* CRC */
    info_pkg->crc = rt_wlan_cal_crc((rt_uint8_t *)cfg_cache->cfg_info, sizeof(struct rt_wlan_cfg_info) * cfg_cache->num);
    rt_memcpy(((rt_uint8_t *)info_pkg) + sizeof(struct cfg_save_info_head),
              cfg_cache->cfg_info, sizeof(struct rt_wlan_cfg_info) * cfg_cache->num);
    if (cfg_ops->write_cfg(info_pkg, len) != len)
        err =  -RT_ERROR;
    rt_free(info_pkg);
    WLAN_CFG_UNLOCK();
    return err;
}

rt_err_t rt_wlan_cfg_cache_refresh(void)
{
    int len = 0, i, j;
    struct cfg_save_info_head *head;
    void *data;
    struct rt_wlan_cfg_info *t_info, *cfg_info;
    rt_uint32_t crc;
    rt_bool_t equal_flag;

    /* cache is full! exit */
    if (cfg_cache == RT_NULL || cfg_cache->num >= RT_WLAN_CFG_INFO_MAX)
        return -RT_ERROR;

    /* check callback */
    if ((cfg_ops == RT_NULL) ||
            (cfg_ops->get_len == RT_NULL) ||
            (cfg_ops->read_cfg == RT_NULL))
        return -RT_ERROR;

    WLAN_CFG_LOCK();
    /* get data len */
    if ((len = cfg_ops->get_len()) <= 0)
    {
        WLAN_CFG_UNLOCK();
        return -RT_ERROR;
    }

    head = rt_malloc(len);
    if (head == RT_NULL)
    {
        WLAN_CFG_UNLOCK();
        return -RT_ERROR;
    }
    /* get data */
    if (cfg_ops->read_cfg(head, len) != len)
    {
        rt_free(head);
        WLAN_CFG_UNLOCK();
        return -RT_ERROR;
    }
    /* get config */
    data = ((rt_uint8_t *)head) + sizeof(struct cfg_save_info_head);
    crc = rt_wlan_cal_crc((rt_uint8_t *)data, len - sizeof(struct cfg_save_info_head));
    LOG_D("head->magic:0x%08x  RT_WLAN_CFG_MAGIC:0x%08x", head->magic, RT_WLAN_CFG_MAGIC);
    LOG_D("head->len:%d len:%d", head->len, len);
    LOG_D("head->num:%d num:%d", head->num, (len - sizeof(struct cfg_save_info_head)) / sizeof(struct rt_wlan_cfg_info));
    LOG_D("hred->crc:0x%04x crc:0x%04x", head->crc, crc);
    /* check */
    if ((head->magic != RT_WLAN_CFG_MAGIC) ||
            (head->len != len) ||
            (head->num != (len - sizeof(struct cfg_save_info_head)) / sizeof(struct rt_wlan_cfg_info)) ||
            (head->crc != crc))
    {
        rt_free(head);
        WLAN_CFG_UNLOCK();
        return -RT_ERROR;
    }

    /* remove duplicate config */
    cfg_info = (struct rt_wlan_cfg_info *)data;
    for (i = 0; i < head->num; i++)
    {
        equal_flag = RT_FALSE;
        for (j = 0; j < cfg_cache->num; j++)
        {
            if ((cfg_cache->cfg_info[j].info.ssid.len == cfg_info[i].info.ssid.len) &&
                    (rt_memcmp(&cfg_cache->cfg_info[j].info.ssid.val[0], &cfg_info[i].info.ssid.val[0],
                               cfg_cache->cfg_info[j].info.ssid.len) == 0) &&
                    (rt_memcmp(&cfg_cache->cfg_info[j].info.bssid[0], &cfg_info[i].info.bssid[0], RT_WLAN_BSSID_MAX_LENGTH) == 0))
            {
                equal_flag = RT_TRUE;
                break;
            }
        }

        if (cfg_cache->num >= RT_WLAN_CFG_INFO_MAX)
        {
            break;
        }

        if (equal_flag == RT_FALSE)
        {
            t_info = rt_realloc(cfg_cache->cfg_info, sizeof(struct rt_wlan_cfg_info) * (cfg_cache->num + 1));
            if (t_info == RT_NULL)
            {
                rt_free(head);
                WLAN_CFG_UNLOCK();
                return -RT_ERROR;
            }
            cfg_cache->cfg_info = t_info;
            cfg_cache->cfg_info[cfg_cache->num] = cfg_info[i];
            cfg_cache->num ++;
        }
    }

    rt_free(head);
    WLAN_CFG_UNLOCK();
    return RT_EOK;
}

int rt_wlan_cfg_get_num(void)
{
    rt_wlan_cfg_init();

    return cfg_cache->num;
}

int rt_wlan_cfg_read(struct rt_wlan_cfg_info *cfg_info, int num)
{
    rt_wlan_cfg_init();

    if ((cfg_info == RT_NULL) || (num <= 0))
        return 0;
    /* copy data */
    WLAN_CFG_LOCK();
    num = cfg_cache->num > num ? num : cfg_cache->num;
    rt_memcpy(&cfg_cache->cfg_info[0], cfg_info, sizeof(struct rt_wlan_cfg_info) * num);
    WLAN_CFG_UNLOCK();

    return num;
}

rt_err_t rt_wlan_cfg_save(struct rt_wlan_cfg_info *cfg_info)
{
    rt_err_t err = RT_EOK;
    struct rt_wlan_cfg_info *t_info;
    int idx = -1, i = 0;

    rt_wlan_cfg_init();

    /* parameter check */
    if ((cfg_info == RT_NULL) || (cfg_info->info.ssid.len == 0))
    {
        return -RT_EINVAL;
    }
    /* if (iteam == cache) exit */
    WLAN_CFG_LOCK();
    for (i = 0; i < cfg_cache->num; i++)
    {
        if ((cfg_cache->cfg_info[i].info.ssid.len == cfg_info->info.ssid.len) &&
                (rt_memcmp(&cfg_cache->cfg_info[i].info.ssid.val[0], &cfg_info->info.ssid.val[0],
                           cfg_cache->cfg_info[i].info.ssid.len) == 0) &&
                (rt_memcmp(&cfg_cache->cfg_info[i].info.bssid[0], &cfg_info->info.bssid[0], RT_WLAN_BSSID_MAX_LENGTH) == 0))
        {
            idx = i;
            break;
        }
    }

    if ((idx == 0) && (cfg_cache->cfg_info[i].key.len == cfg_info->key.len) &&
            (rt_memcmp(&cfg_cache->cfg_info[i].key.val[0], &cfg_info->key.val[0], cfg_info->key.len) == 0))
    {
        WLAN_CFG_UNLOCK();
        return RT_EOK;
    }

    /* not find iteam with cache, Add iteam to the head   */
    if ((idx == -1) && (cfg_cache->num < RT_WLAN_CFG_INFO_MAX))
    {
        t_info = rt_realloc(cfg_cache->cfg_info, sizeof(struct rt_wlan_cfg_info) * (cfg_cache->num + 1));
        if (t_info == RT_NULL)
        {
            WLAN_CFG_UNLOCK();
            return -RT_ENOMEM;
        }
        cfg_cache->cfg_info = t_info;
        cfg_cache->num ++;
    }

    /* move cache info */
    i = (i >= RT_WLAN_CFG_INFO_MAX ? RT_WLAN_CFG_INFO_MAX - 1 : i);
    for (; i; i--)
    {
        cfg_cache->cfg_info[i] = cfg_cache->cfg_info[i - 1];
    }
    /* add iteam to head */
    cfg_cache->cfg_info[i] = *cfg_info;
    WLAN_CFG_UNLOCK();

    /* save info to flash */
    err = rt_wlan_cfg_cache_save();

    return err;
}

int rt_wlan_cfg_read_index(struct rt_wlan_cfg_info *cfg_info, int index)
{
    rt_wlan_cfg_init();

    if ((cfg_info == RT_NULL) || (index < 0))
        return 0;

    WLAN_CFG_LOCK();
    if (index >= cfg_cache->num)
    {
        WLAN_CFG_UNLOCK();
        return 0;
    }
    /* copy data */
    *cfg_info = cfg_cache->cfg_info[index];
    WLAN_CFG_UNLOCK();
    return 1;
}

int rt_wlan_cfg_delete_index(int index)
{
    struct rt_wlan_cfg_info *cfg_info;
    int i;

    rt_wlan_cfg_init();

    if (index < 0)
        return -1;

    WLAN_CFG_LOCK();
    if (index >= cfg_cache->num)
    {
        WLAN_CFG_UNLOCK();
        return -1;
    }

    /* malloc new mem */
    cfg_info = rt_malloc(sizeof(struct rt_wlan_cfg_info) * (cfg_cache->num - 1));
    if (cfg_info == RT_NULL)
    {
        WLAN_CFG_UNLOCK();
        return -1;
    }
    /* copy data to new mem */
    for (i = 0; i < cfg_cache->num; i++)
    {
        if (i < index)
        {
            cfg_info[i] = cfg_cache->cfg_info[i];
        }
        else if (i > index)
        {
            cfg_info[i - 1] = cfg_cache->cfg_info[i];
        }
    }
    rt_free(cfg_cache->cfg_info);
    cfg_cache->cfg_info = cfg_info;
    cfg_cache->num --;
    WLAN_CFG_UNLOCK();

    return 0;
}

void rt_wlan_cfg_delete_all(void)
{
    rt_wlan_cfg_init();

    /* delete all iteam */
    WLAN_CFG_LOCK();
    cfg_cache->num = 0;
    rt_free(cfg_cache->cfg_info);
    cfg_cache->cfg_info = RT_NULL;
    WLAN_CFG_UNLOCK();
}

void rt_wlan_cfg_dump(void)
{
    int index = 0;
    struct rt_wlan_info *info;
    struct rt_wlan_key *key;
    char *security;

    rt_wlan_cfg_init();

    rt_kprintf("             SSID                           PASSWORD                   MAC            security     chn\n");
    rt_kprintf("------------------------------- ------------------------------- -----------------  --------------  ---\n");
    for (index = 0; index < cfg_cache->num; index ++)
    {
        info = &cfg_cache->cfg_info[index].info;
        key = &cfg_cache->cfg_info[index].key;

        if (info->ssid.len)
            rt_kprintf("%-32.32s", &info->ssid.val[0]);
        else
            rt_kprintf("%-32.32s", " ");

        if (key->len)
            rt_kprintf("%-32.32s", &key->val[0]);
        else
            rt_kprintf("%-32.32s", " ");

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
        rt_kprintf("%-14.14s  ", security);
        rt_kprintf("%3d    \n", info->channel);
    }
}

#endif
