/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "netif/etharp.h"
#include "lwip/netif.h"
#include "lwip/pbuf.h"
#include "lwip/tcpip.h"
#if LWIP_DHCP
#include "lwip/dhcp.h"
#include "lwip/prot/dhcp.h"
#endif

#include <rtthread.h>
#include <rtdevice.h>
#include <netif/ethernetif.h>

#include "usbh_core.h"

#include "lwip/opt.h"

#ifndef RT_USING_LWIP212
#error must enable RT_USING_LWIP212
#endif

#ifndef LWIP_NO_RX_THREAD
#error must enable LWIP_NO_RX_THREAD, we do not use rtthread eth rx thread
#endif

#ifndef LWIP_NO_TX_THREAD
#warning suggest you to enable LWIP_NO_TX_THREAD, we do not use rtthread eth tx thread
#endif

#if LWIP_TCPIP_CORE_LOCKING_INPUT != 1
#warning suggest you to set LWIP_TCPIP_CORE_LOCKING_INPUT to 1, usb handles eth input with own thread
#endif

#if LWIP_TCPIP_CORE_LOCKING != 1
#error must set LWIP_TCPIP_CORE_LOCKING to 1
#endif

#if PBUF_POOL_BUFSIZE < 1600
#error PBUF_POOL_BUFSIZE must be larger than 1600
#endif

#if RT_LWIP_TCPTHREAD_STACKSIZE < 2048
#error RT_LWIP_TCPTHREAD_STACKSIZE must be >= 2048
#endif

// #define CONFIG_USBHOST_PLATFORM_CDC_ECM
// #define CONFIG_USBHOST_PLATFORM_CDC_RNDIS
// #define CONFIG_USBHOST_PLATFORM_CDC_NCM
// #define CONFIG_USBHOST_PLATFORM_ASIX
// #define CONFIG_USBHOST_PLATFORM_RTL8152

void usbh_lwip_eth_output_common(struct pbuf *p, uint8_t *buf)
{
    struct pbuf *q;
    uint8_t *buffer;

    buffer = buf;
    for (q = p; q != NULL; q = q->next) {
        usb_memcpy(buffer, q->payload, q->len);
        buffer += q->len;
    }
}

void usbh_lwip_eth_input_common(struct netif *netif, uint8_t *buf, uint32_t len)
{
#if LWIP_TCPIP_CORE_LOCKING_INPUT
    pbuf_type type = PBUF_REF;
#else
    pbuf_type type = PBUF_POOL;
#endif
    err_t err;
    struct pbuf *p;

    p = pbuf_alloc(PBUF_RAW, len, type);
    if (p != NULL) {
#if LWIP_TCPIP_CORE_LOCKING_INPUT
        p->payload = buf;
#else
        usb_memcpy(p->payload, buf, len);
#endif
        err = netif->input(p, netif);
        if (err != ERR_OK) {
            pbuf_free(p);
        }
    } else {
        USB_LOG_ERR("No memory to alloc pbuf\r\n");
    }
}

#ifdef CONFIG_USBHOST_PLATFORM_CDC_ECM
#include "usbh_cdc_ecm.h"

static struct eth_device g_cdc_ecm_dev;

static rt_err_t rt_usbh_cdc_ecm_control(rt_device_t dev, int cmd, void *args)
{
    struct usbh_cdc_ecm *cdc_ecm_class = (struct usbh_cdc_ecm *)dev->user_data;

    switch (cmd) {
        case NIOCTL_GADDR:

            /* get mac address */
            if (args)
                rt_memcpy(args, cdc_ecm_class->mac, 6);
            else
                return -RT_ERROR;

            break;

        default:
            break;
    }

    return RT_EOK;
}

static rt_err_t rt_usbh_cdc_ecm_eth_tx(rt_device_t dev, struct pbuf *p)
{
    int ret;
    (void)dev;

    usbh_lwip_eth_output_common(p, usbh_cdc_ecm_get_eth_txbuf());
    ret = usbh_cdc_ecm_eth_output(p->tot_len);
    if (ret < 0) {
        return -RT_ERROR;
    } else {
        return RT_EOK;
    }
}

void usbh_cdc_ecm_eth_input(uint8_t *buf, uint32_t buflen)
{
    usbh_lwip_eth_input_common(g_cdc_ecm_dev.netif, buf, buflen);
}

void usbh_cdc_ecm_run(struct usbh_cdc_ecm *cdc_ecm_class)
{
    memset(&g_cdc_ecm_dev, 0, sizeof(struct eth_device));

    g_cdc_ecm_dev.parent.control = rt_usbh_cdc_ecm_control;
    g_cdc_ecm_dev.eth_rx = NULL;
    g_cdc_ecm_dev.eth_tx = rt_usbh_cdc_ecm_eth_tx;
    g_cdc_ecm_dev.parent.user_data = cdc_ecm_class;

    eth_device_init(&g_cdc_ecm_dev, "u0");
    eth_device_linkchange(&g_cdc_ecm_dev, RT_TRUE);

    usb_osal_thread_create("usbh_cdc_ecm_rx", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_cdc_ecm_rx_thread, NULL);
}

void usbh_cdc_ecm_stop(struct usbh_cdc_ecm *cdc_ecm_class)
{
    (void)cdc_ecm_class;

    eth_device_deinit(&g_cdc_ecm_dev);
}
#endif

#ifdef CONFIG_USBHOST_PLATFORM_CDC_RNDIS
#include "usbh_rndis.h"

static struct eth_device g_rndis_dev;

static rt_timer_t keep_timer = RT_NULL;

static void rndis_dev_keepalive_timeout(void *parameter)
{
    struct usbh_rndis *rndis_class = (struct usbh_rndis *)parameter;
    usbh_rndis_keepalive(rndis_class);
}

static void timer_init(struct usbh_rndis *rndis_class)
{
    keep_timer = rt_timer_create("keep",
                                 rndis_dev_keepalive_timeout,
                                 rndis_class,
                                 5000,
                                 RT_TIMER_FLAG_PERIODIC |
                                     RT_TIMER_FLAG_SOFT_TIMER);

    rt_timer_start(keep_timer);
}

static rt_err_t rt_usbh_rndis_control(rt_device_t dev, int cmd, void *args)
{
    struct usbh_rndis *rndis_class = (struct usbh_rndis *)dev->user_data;

    switch (cmd) {
        case NIOCTL_GADDR:

            /* get mac address */
            if (args)
                rt_memcpy(args, rndis_class->mac, 6);
            else
                return -RT_ERROR;

            break;

        default:
            break;
    }

    return RT_EOK;
}

static rt_err_t rt_usbh_rndis_eth_tx(rt_device_t dev, struct pbuf *p)
{
    int ret;
    (void)dev;

    usbh_lwip_eth_output_common(p, usbh_rndis_get_eth_txbuf());
    ret = usbh_rndis_eth_output(p->tot_len);
    if (ret < 0) {
        return -RT_ERROR;
    } else {
        return RT_EOK;
    }
}

void usbh_rndis_eth_input(uint8_t *buf, uint32_t buflen)
{
    usbh_lwip_eth_input_common(g_rndis_dev.netif, buf, buflen);
}

void usbh_rndis_run(struct usbh_rndis *rndis_class)
{
    memset(&g_rndis_dev, 0, sizeof(struct eth_device));

    g_rndis_dev.parent.control = rt_usbh_rndis_control;
    g_rndis_dev.eth_rx = NULL;
    g_rndis_dev.eth_tx = rt_usbh_rndis_eth_tx;
    g_rndis_dev.parent.user_data = rndis_class;

    eth_device_init(&g_rndis_dev, "u2");
    eth_device_linkchange(&g_rndis_dev, RT_TRUE);

    usb_osal_thread_create("usbh_rndis_rx", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_rndis_rx_thread, NULL);
    //timer_init(rndis_class);
}

void usbh_rndis_stop(struct usbh_rndis *rndis_class)
{
    (void)rndis_class;

    eth_device_deinit(&g_rndis_dev);
    // rt_timer_stop(keep_timer);
    // rt_timer_delete(keep_timer);
}
#endif

#ifdef CONFIG_USBHOST_PLATFORM_CDC_NCM
#include "usbh_cdc_ncm.h"

static struct eth_device g_cdc_ncm_dev;

static rt_err_t rt_usbh_cdc_ncm_control(rt_device_t dev, int cmd, void *args)
{
    struct usbh_cdc_ncm *cdc_ncm_class = (struct usbh_cdc_ncm *)dev->user_data;

    switch (cmd) {
        case NIOCTL_GADDR:

            /* get mac address */
            if (args)
                rt_memcpy(args, cdc_ncm_class->mac, 6);
            else
                return -RT_ERROR;

            break;

        default:
            break;
    }

    return RT_EOK;
}

static rt_err_t rt_usbh_cdc_ncm_eth_tx(rt_device_t dev, struct pbuf *p)
{
    int ret;
    (void)dev;

    usbh_lwip_eth_output_common(p, usbh_cdc_ncm_get_eth_txbuf());
    ret = usbh_cdc_ncm_eth_output(p->tot_len);
    if (ret < 0) {
        return -RT_ERROR;
    } else {
        return RT_EOK;
    }
}

void usbh_cdc_ncm_eth_input(uint8_t *buf, uint32_t buflen)
{
    usbh_lwip_eth_input_common(g_cdc_ncm_dev.netif, buf, buflen);
}

void usbh_cdc_ncm_run(struct usbh_cdc_ncm *cdc_ncm_class)
{
    memset(&g_cdc_ncm_dev, 0, sizeof(struct eth_device));

    g_cdc_ncm_dev.parent.control = rt_usbh_cdc_ncm_control;
    g_cdc_ncm_dev.eth_rx = NULL;
    g_cdc_ncm_dev.eth_tx = rt_usbh_cdc_ncm_eth_tx;
    g_cdc_ncm_dev.parent.user_data = cdc_ncm_class;

    eth_device_init(&g_cdc_ncm_dev, "u1");
    eth_device_linkchange(&g_cdc_ncm_dev, RT_TRUE);

    usb_osal_thread_create("usbh_cdc_ncm_rx", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_cdc_ncm_rx_thread, NULL);
}

void usbh_cdc_ncm_stop(struct usbh_cdc_ncm *cdc_ncm_class)
{
    (void)cdc_ncm_class;

    eth_device_deinit(&g_cdc_ncm_dev);
}
#endif

#ifdef CONFIG_USBHOST_PLATFORM_ASIX
#include "usbh_asix.h"

static struct eth_device g_asix_dev;

static rt_err_t rt_usbh_asix_control(rt_device_t dev, int cmd, void *args)
{
    struct usbh_asix *asix_class = (struct usbh_asix *)dev->user_data;

    switch (cmd) {
        case NIOCTL_GADDR:

            /* get mac address */
            if (args)
                rt_memcpy(args, asix_class->mac, 6);
            else
                return -RT_ERROR;

            break;

        default:
            break;
    }

    return RT_EOK;
}

static rt_err_t rt_usbh_asix_eth_tx(rt_device_t dev, struct pbuf *p)
{
    int ret;
    (void)dev;

    usbh_lwip_eth_output_common(p, usbh_asix_get_eth_txbuf());
    ret = usbh_asix_eth_output(p->tot_len);
    if (ret < 0) {
        return -RT_ERROR;
    } else {
        return RT_EOK;
    }
}

void usbh_asix_eth_input(uint8_t *buf, uint32_t buflen)
{
    usbh_lwip_eth_input_common(g_asix_dev.netif, buf, buflen);
}

void usbh_asix_run(struct usbh_asix *asix_class)
{
    memset(&g_asix_dev, 0, sizeof(struct eth_device));

    g_asix_dev.parent.control = rt_usbh_asix_control;
    g_asix_dev.eth_rx = NULL;
    g_asix_dev.eth_tx = rt_usbh_asix_eth_tx;
    g_asix_dev.parent.user_data = asix_class;

    eth_device_init(&g_asix_dev, "u3");
    eth_device_linkchange(&g_asix_dev, RT_TRUE);

    usb_osal_thread_create("usbh_asix_rx", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_asix_rx_thread, NULL);
}

void usbh_asix_stop(struct usbh_asix *asix_class)
{
    (void)asix_class;

    eth_device_deinit(&g_asix_dev);
}
#endif

#ifdef CONFIG_USBHOST_PLATFORM_RTL8152
#include "usbh_rtl8152.h"

static struct eth_device g_rtl8152_dev;

static rt_err_t rt_usbh_rtl8152_control(rt_device_t dev, int cmd, void *args)
{
    struct usbh_rtl8152 *rtl8152_class = (struct usbh_rtl8152 *)dev->user_data;

    switch (cmd) {
        case NIOCTL_GADDR:

            /* get mac address */
            if (args)
                rt_memcpy(args, rtl8152_class->mac, 6);
            else
                return -RT_ERROR;

            break;

        default:
            break;
    }

    return RT_EOK;
}

static rt_err_t rt_usbh_rtl8152_eth_tx(rt_device_t dev, struct pbuf *p)
{
    int ret;
    (void)dev;

    usbh_lwip_eth_output_common(p, usbh_rtl8152_get_eth_txbuf());
    ret = usbh_rtl8152_eth_output(p->tot_len);
    if (ret < 0) {
        return -RT_ERROR;
    } else {
        return RT_EOK;
    }
}

void usbh_rtl8152_eth_input(uint8_t *buf, uint32_t buflen)
{
    usbh_lwip_eth_input_common(g_rtl8152_dev.netif, buf, buflen);
}

void usbh_rtl8152_run(struct usbh_rtl8152 *rtl8152_class)
{
    memset(&g_rtl8152_dev, 0, sizeof(struct eth_device));

    g_rtl8152_dev.parent.control = rt_usbh_rtl8152_control;
    g_rtl8152_dev.eth_rx = NULL;
    g_rtl8152_dev.eth_tx = rt_usbh_rtl8152_eth_tx;
    g_rtl8152_dev.parent.user_data = rtl8152_class;

    eth_device_init(&g_rtl8152_dev, "u4");
    eth_device_linkchange(&g_rtl8152_dev, RT_TRUE);

    usb_osal_thread_create("usbh_rtl8152_rx", 2048, CONFIG_USBHOST_PSC_PRIO + 1, usbh_rtl8152_rx_thread, NULL);
}

void usbh_rtl8152_stop(struct usbh_rtl8152 *rtl8152_class)
{
    (void)rtl8152_class;

    eth_device_deinit(&g_rtl8152_dev);
}
#endif
