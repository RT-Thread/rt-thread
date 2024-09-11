/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-06     tyx          the first version
 */

#ifndef __DEV_WLAN_CFG_H__
#define __DEV_WLAN_CFG_H__

#include <dev_wlan.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef RT_WLAN_CFG_INFO_MAX
#define RT_WLAN_CFG_INFO_MAX    (3) /* min is 1 */
#endif

#define RT_WLAN_CFG_MAGIC       (0x426f6d62)

struct rt_wlan_cfg_info
{
    struct rt_wlan_info info;
    struct rt_wlan_key key;
};

typedef int (*rt_wlan_wr)(void *buff, int len);

struct rt_wlan_cfg_ops
{
    int (*read_cfg)(void *buff, int len);
    int (*get_len)(void);
    int (*write_cfg)(void *buff, int len);
};

void rt_wlan_cfg_init(void);

void rt_wlan_cfg_set_ops(const struct rt_wlan_cfg_ops *ops);

int rt_wlan_cfg_get_num(void);

int rt_wlan_cfg_read(struct rt_wlan_cfg_info *cfg_info, int num);

int rt_wlan_cfg_read_index(struct rt_wlan_cfg_info *cfg_info, int index);

rt_err_t rt_wlan_cfg_save(struct rt_wlan_cfg_info *cfg_info);

rt_err_t rt_wlan_cfg_cache_refresh(void);

rt_err_t rt_wlan_cfg_cache_save(void);

int rt_wlan_cfg_delete_index(int index);

void rt_wlan_cfg_delete_all(void);

void rt_wlan_cfg_dump(void);

#ifdef __cplusplus
}
#endif

#endif
