/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-14     tyx          the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <wlan_dev.h>
#include <wlan_prot.h>

#define DBG_TAG "WLAN.prot"
#ifdef RT_WLAN_PROT_DEBUG
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_INFO
#endif /* RT_WLAN_PROT_DEBUG */
#include <rtdbg.h>

#ifdef RT_WLAN_PROT_ENABLE

#if RT_WLAN_PROT_NAME_LEN < 4
#error "The name is too short"
#endif

struct rt_wlan_prot_event_des
{
    rt_wlan_prot_event_handler handler;
    struct rt_wlan_prot *prot;
};

static struct rt_wlan_prot *_prot[RT_WLAN_PROT_MAX];

static struct rt_wlan_prot_event_des prot_event_tab[RT_WLAN_PROT_EVT_MAX][RT_WLAN_PROT_MAX];

static void rt_wlan_prot_event_handle(struct rt_wlan_device *wlan, rt_wlan_dev_event_t event, struct rt_wlan_buff *buff, void *parameter)
{
    int i;
    struct rt_wlan_prot *wlan_prot;
    struct rt_wlan_prot *prot;
    rt_wlan_prot_event_handler handler;
    rt_wlan_prot_event_t prot_event;

    LOG_D("F:%s L:%d event:%d", __FUNCTION__, __LINE__, event);

    wlan_prot = wlan->prot;
    handler = RT_NULL;
    prot = RT_NULL;
    switch (event)
    {
    case RT_WLAN_DEV_EVT_INIT_DONE:
    {
        LOG_D("L%d event: INIT_DONE", __LINE__);
        prot_event = RT_WLAN_PROT_EVT_INIT_DONE;
        break;
    }
    case RT_WLAN_DEV_EVT_CONNECT:
    {
        LOG_D("L%d event: CONNECT", __LINE__);
        prot_event = RT_WLAN_PROT_EVT_CONNECT;
        break;
    }
    case RT_WLAN_DEV_EVT_DISCONNECT:
    {
        LOG_D("L%d event: DISCONNECT", __LINE__);
        prot_event = RT_WLAN_PROT_EVT_DISCONNECT;
        break;
    }
    case RT_WLAN_DEV_EVT_AP_START:
    {
        LOG_D("L%d event: AP_START", __LINE__);
        prot_event = RT_WLAN_PROT_EVT_AP_START;
        break;
    }
    case RT_WLAN_DEV_EVT_AP_STOP:
    {
        LOG_D("L%d event: AP_STOP", __LINE__);
        prot_event = RT_WLAN_PROT_EVT_AP_STOP;
        break;
    }
    case RT_WLAN_DEV_EVT_AP_ASSOCIATED:
    {
        LOG_D("L%d event: AP_ASSOCIATED", __LINE__);
        prot_event = RT_WLAN_PROT_EVT_AP_ASSOCIATED;
        break;
    }
    case RT_WLAN_DEV_EVT_AP_DISASSOCIATED:
    {
        LOG_D("L%d event: AP_DISASSOCIATED", __LINE__);
        prot_event = RT_WLAN_PROT_EVT_AP_DISASSOCIATED;
        break;
    }
    default:
    {
        return;
    }
    }
    for (i = 0; i < RT_WLAN_PROT_MAX; i++)
    {
        if ((prot_event_tab[prot_event][i].handler != RT_NULL) &&
                (prot_event_tab[prot_event][i].prot->id == wlan_prot->id))
        {
            handler = prot_event_tab[prot_event][i].handler;
            prot = prot_event_tab[prot_event][i].prot;
            break;
        }
    }

    if (handler != RT_NULL)
    {
        handler(prot, wlan, prot_event);
    }
}

static struct rt_wlan_device *rt_wlan_prot_find_by_name(const char *name)
{
    rt_device_t device;

    if (name == RT_NULL)
    {
        LOG_E("F:%s L:%d Parameter Wrongful", __FUNCTION__, __LINE__);
        return RT_NULL;
    }
    device = rt_device_find(name);
    if (device == RT_NULL)
    {
        LOG_E("F:%s L:%d not find wlan dev!! name:%s", __FUNCTION__, __LINE__, name);
        return RT_NULL;
    }
    return (struct rt_wlan_device *)device;
}

rt_err_t rt_wlan_prot_attach(const char *dev_name, const char *prot_name)
{
    struct rt_wlan_device *wlan;

    wlan = rt_wlan_prot_find_by_name(dev_name);
    if (wlan == RT_NULL)
    {
        return -RT_ERROR;
    }
    return rt_wlan_prot_attach_dev(wlan, prot_name);
}

rt_err_t rt_wlan_prot_detach(const char *name)
{
    struct rt_wlan_device *wlan;

    wlan = rt_wlan_prot_find_by_name(name);
    if (wlan == RT_NULL)
    {
        return -RT_ERROR;
    }
    return rt_wlan_prot_detach_dev(wlan);
}

rt_err_t rt_wlan_prot_attach_dev(struct rt_wlan_device *wlan, const char *prot_name)
{
    int i = 0;
    struct rt_wlan_prot *prot = wlan->prot;
    rt_wlan_dev_event_handler handler = rt_wlan_prot_event_handle;

    if (wlan == RT_NULL)
    {
        LOG_E("F:%s L:%d wlan is null", __FUNCTION__, __LINE__);
        return -RT_ERROR;
    }

    if (prot != RT_NULL &&
            (rt_strcmp(prot->name, prot_name) == 0))
    {
        LOG_D("prot is register");
        return RT_EOK;
    }

    /* if prot not NULL */
    if (prot != RT_NULL)
        rt_wlan_prot_detach_dev(wlan);

#ifdef RT_WLAN_PROT_LWIP_PBUF_FORCE
    if (rt_strcmp(RT_WLAN_PROT_LWIP_NAME, prot_name) != 0)
    {
        return -RT_ERROR;
    }
#endif
    /* find prot */
    for (i = 0; i < RT_WLAN_PROT_MAX; i++)
    {
        if ((_prot[i] != RT_NULL) && (rt_strcmp(_prot[i]->name, prot_name) == 0))
        {
            /* attach prot */
            wlan->prot = _prot[i]->ops->dev_reg_callback(_prot[i], wlan);
            break;
        }
    }

    if (i >= RT_WLAN_PROT_MAX)
    {
        LOG_E("F:%s L:%d not find wlan protocol", __FUNCTION__, __LINE__);
        return -RT_ERROR;
    }

    rt_wlan_dev_register_event_handler(wlan, RT_WLAN_DEV_EVT_CONNECT, handler, RT_NULL);
    rt_wlan_dev_register_event_handler(wlan, RT_WLAN_DEV_EVT_DISCONNECT, handler, RT_NULL);
    rt_wlan_dev_register_event_handler(wlan, RT_WLAN_DEV_EVT_AP_START, handler, RT_NULL);
    rt_wlan_dev_register_event_handler(wlan, RT_WLAN_DEV_EVT_AP_STOP, handler, RT_NULL);
    rt_wlan_dev_register_event_handler(wlan, RT_WLAN_DEV_EVT_AP_ASSOCIATED, handler, RT_NULL);
    rt_wlan_dev_register_event_handler(wlan, RT_WLAN_DEV_EVT_AP_DISASSOCIATED, handler, RT_NULL);

    return RT_EOK;
}

rt_err_t rt_wlan_prot_detach_dev(struct rt_wlan_device *wlan)
{
    struct rt_wlan_prot *prot = wlan->prot;
    rt_wlan_dev_event_t event;

    if (prot == RT_NULL)
        return RT_EOK;

    for (event = RT_WLAN_DEV_EVT_INIT_DONE; event < RT_WLAN_DEV_EVT_MAX; event ++)
    {
        rt_wlan_dev_unregister_event_handler(wlan, event, rt_wlan_prot_event_handle);
    }

    /* detach prot */
    prot->ops->dev_unreg_callback(prot, wlan);
    wlan->prot = RT_NULL;

    return RT_EOK;
}

rt_err_t rt_wlan_prot_regisetr(struct rt_wlan_prot *prot)
{
    int i;
    rt_uint32_t id;
    static rt_uint8_t num;

    /* Parameter checking */
    if ((prot == RT_NULL) ||
            (prot->ops->prot_recv == RT_NULL) ||
            (prot->ops->dev_reg_callback == RT_NULL))
    {
        LOG_E("F:%s L:%d Parameter Wrongful", __FUNCTION__, __LINE__);
        return -RT_EINVAL;
    }

    /* save prot */
    for (i = 0; i < RT_WLAN_PROT_MAX; i++)
    {
        if (_prot[i] == RT_NULL)
        {
            id = (RT_LWAN_ID_PREFIX << 16) | num;
            prot->id = id;
            _prot[i] = prot;
            num ++;
            break;
        }
        else if (rt_strcmp(_prot[i]->name, prot->name) == 0)
        {
            break;
        }
    }

    /* is full */
    if (i >= RT_WLAN_PROT_MAX)
    {
        LOG_E("F:%s L:%d Space full", __FUNCTION__, __LINE__);
        return -RT_ERROR;
    }

    return RT_EOK;
}

rt_err_t rt_wlan_prot_event_register(struct rt_wlan_prot *prot, rt_wlan_prot_event_t event, rt_wlan_prot_event_handler handler)
{
    int i;

    if ((prot == RT_NULL) || (handler == RT_NULL))
    {
        return -RT_EINVAL;
    }

    for (i = 0; i < RT_WLAN_PROT_MAX; i++)
    {
        if (prot_event_tab[event][i].handler == RT_NULL)
        {
            prot_event_tab[event][i].handler = handler;
            prot_event_tab[event][i].prot = prot;
            return RT_EOK;
        }
    }

    return -RT_ERROR;
}

rt_err_t rt_wlan_prot_event_unregister(struct rt_wlan_prot *prot, rt_wlan_prot_event_t event)
{
    int i;

    if (prot == RT_NULL)
    {
        return -RT_EINVAL;
    }

    for (i = 0; i < RT_WLAN_PROT_MAX; i++)
    {
        if ((prot_event_tab[event][i].handler != RT_NULL) &&
                (prot_event_tab[event][i].prot == prot))
        {
            rt_memset(&prot_event_tab[event][i], 0, sizeof(struct rt_wlan_prot_event_des));
            return RT_EOK;
        }
    }

    return -RT_ERROR;
}

rt_err_t rt_wlan_prot_transfer_dev(struct rt_wlan_device *wlan, void *buff, int len)
{
    if (wlan->ops->wlan_send != RT_NULL)
    {
        return wlan->ops->wlan_send(wlan, buff, len);
    }
    return -RT_ERROR;
}

rt_err_t rt_wlan_dev_transfer_prot(struct rt_wlan_device *wlan, void *buff, int len)
{
    struct rt_wlan_prot *prot = wlan->prot;

    if (prot != RT_NULL)
    {
        return prot->ops->prot_recv(wlan, buff, len);
    }
    return -RT_ERROR;
}

extern int rt_wlan_prot_ready_event(struct rt_wlan_device *wlan, struct rt_wlan_buff *buff);
int rt_wlan_prot_ready(struct rt_wlan_device *wlan, struct rt_wlan_buff *buff)
{
    return rt_wlan_prot_ready_event(wlan, buff);
}

void rt_wlan_prot_dump(void)
{
    int i;

    rt_kprintf("  name       id \n");
    rt_kprintf("--------  --------\n");
    for (i = 0; i < RT_WLAN_PROT_MAX; i++)
    {
        if (_prot[i] != RT_NULL)
        {
            rt_kprintf("%-8.8s  ", _prot[i]->name);
            rt_kprintf("%08x\n", _prot[i]->id);
        }
    }
}
#endif
