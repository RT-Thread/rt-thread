/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-14     tyx          the first version
 */

#ifndef __WLAN_PROT_H__
#define __WLAN_PROT_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef RT_WLAN_PROT_NAME_LEN
#define RT_WLAN_PROT_NAME_LEN  (8)
#endif

#ifndef RT_WLAN_PROT_MAX
#define RT_WLAN_PROT_MAX       (1)
#endif

#define RT_LWAN_ID_PREFIX      (0x5054)

typedef enum
{
    RT_WLAN_PROT_EVT_INIT_DONE = 0,
    RT_WLAN_PROT_EVT_CONNECT,
    RT_WLAN_PROT_EVT_DISCONNECT,
    RT_WLAN_PROT_EVT_AP_START,
    RT_WLAN_PROT_EVT_AP_STOP,
    RT_WLAN_PROT_EVT_AP_ASSOCIATED,
    RT_WLAN_PROT_EVT_AP_DISASSOCIATED,
    RT_WLAN_PROT_EVT_MAX,
} rt_wlan_prot_event_t;

struct rt_wlan_prot;
struct rt_wlan_prot_ops
{
    rt_err_t (*prot_recv)(struct rt_wlan_device *wlan, void *buff, int len);
    struct rt_wlan_prot *(*dev_reg_callback)(struct rt_wlan_prot *prot, struct rt_wlan_device *wlan);
    void (*dev_unreg_callback)(struct rt_wlan_prot *prot, struct rt_wlan_device *wlan);
};

struct rt_wlan_prot
{
    char name[RT_WLAN_PROT_NAME_LEN];
    rt_uint32_t id;
    const struct rt_wlan_prot_ops *ops;
};

typedef void (*rt_wlan_prot_event_handler)(struct rt_wlan_prot *port, struct rt_wlan_device *wlan, int event);

rt_err_t rt_wlan_prot_attach(const char *dev_name, const char *prot_name);

rt_err_t rt_wlan_prot_attach_dev(struct rt_wlan_device *wlan, const char *prot_name);

rt_err_t rt_wlan_prot_detach(const char *dev_name);

rt_err_t rt_wlan_prot_detach_dev(struct rt_wlan_device *wlan);

rt_err_t rt_wlan_prot_regisetr(struct rt_wlan_prot *prot);

rt_err_t rt_wlan_prot_transfer_dev(struct rt_wlan_device *wlan, void *buff, int len);

rt_err_t rt_wlan_dev_transfer_prot(struct rt_wlan_device *wlan, void *buff, int len);

rt_err_t rt_wlan_prot_event_register(struct rt_wlan_prot *prot, rt_wlan_prot_event_t event, rt_wlan_prot_event_handler handler);

rt_err_t rt_wlan_prot_event_unregister(struct rt_wlan_prot *prot, rt_wlan_prot_event_t event);

int rt_wlan_prot_ready(struct rt_wlan_device *wlan, struct rt_wlan_buff *buff);

void rt_wlan_prot_dump(void);

#ifdef __cplusplus
}
#endif

#endif
