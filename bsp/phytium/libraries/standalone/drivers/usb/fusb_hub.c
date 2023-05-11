/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fusb_hub.c
 * Date: 2022-02-11 13:33:07
 * LastEditTime: 2022-02-17 17:48:52
 * Description:  This files is for implmentation of USB hub function
 *  you may refer to chapter 11 Hub specification for details
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#include "fkernel.h"
#include "fdebug.h"
#include "fassert.h"

#include "fusb_private.h"
#include "fusb_generic_hub.h"

#define FUSB_DEBUG_TAG "FUSB_HUB"
#define FUSB_ERROR(format, ...) FT_DEBUG_PRINT_E(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_WARN(format, ...) FT_DEBUG_PRINT_W(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_INFO(format, ...) FT_DEBUG_PRINT_I(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_DEBUG(format, ...) FT_DEBUG_PRINT_D(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)

/* assume that FUSB_REQ_HOST_TO_DEVICE is overwritten if necessary */
#define DR_PORT FUsbGenerateReqType(FUSB_REQ_HOST_TO_DEVICE, FUSB_REQ_TYPE_CLASS, FUSB_REQ_RECP_OTHER) /* 10100011B */
#define DR_HUB FUsbGenerateReqType(FUSB_REQ_HOST_TO_DEVICE, FUSB_REQ_TYPE_CLASS, FUSB_REQ_RECP_DEV) /* 10100000B */

#define FUSB_HUB_PORT_STATUS        0
#define FUSB_HUB_PORT_CHANGE        1

#define FUSB_HUB_PORT_BUF_LEN       2

/* status (and status change) bits, refer to Table 10-10, Port Status Field in USB spec */
#define FUSB_HUB_STATUS_PORT_CONNECTION BIT(0) /* reflects if device is currently connected to this port */
#define FUSB_HUB_STATUS_PORT_ENABLE     BIT(1) /* reflects if this port is enabled */
#define FUSB_HUB_STATUS_PORT_SUSPEND    BIT(2) /* reflects if this port is suspend, only for USB2 */
#define FUSB_HUB_STATUS_PORT_OVER_CURRENT BIT(3) /* reports over-current conditions in this port */
#define FUSB_HUB_STATUS_PORT_RESET      BIT(4) /* reset signaling asserted */
#define FUSB_HUB_STATUS_BH_PORT_RESET   BIT(5) /* warm reset completed */
#define FUSB_HUB_STATUS_PORT_LINK_STATE BIT(6) /* link state changed */
#define FUSB_HUB_STATUS_PORT_PORT_CONFIG_ERROR BIT(7) /* port fails to config */

/* feature selectors (for setting / clearing features), refer to USB spec. Table 10-17. Hub Class Feature Selectors for details */
#define FUSB_HUB_SEL_PORT_RESET         4
#define FUSB_HUB_SEL_PORT_POWER         8
#define FUSB_HUB_SEL_C_PORT_CONNECTION  16
#define FUSB_HUB_SEL_C_PORT_ENABLE      17  /* USB2 only */
#define FUSB_HUB_SEL_C_PORT_SUSPEND     18  /* USB2 only */
#define FUSB_HUB_SEL_C_PORT_OVER_CURRENT 19
#define FUSB_HUB_SEL_C_PORT_RESET       20
#define FUSB_HUB_SEL_C_PORT_LINK_STATE  25
#define FUSB_HUB_SEL_C_PORT_CONFIG_ERROR 26
#define FUSB_HUB_SEL_C_BH_PORT_RESET     27

/* request type (USB 3.0 hubs only) */
#define SET_HUB_DEPTH 12

/**
 * @name: FUsbHubIntrEp
 * @msg: 获取USB Hub的中断端点
 * @return {FUsbEndpoint *} 中断类型的功能端点
 * @param {FUsbDev} *dev, Hub实例
 */
static FUsbEndpoint *FUsbHubIntrEp(FUsbDev *const dev)
{
    FASSERT(dev);
    int i;

    for (i = 0; i < dev->num_endp; ++i)
    {
        if (dev->endpoints[i].type == FUSB_INTERRUPT_EP &&
            dev->endpoints[i].direction == FUSB_IN)
        {
            return &dev->endpoints[i];
        }
    }

    return NULL;
}

/**
 * @name: FUsbHubPortStatusChange
 * @msg: Usb Hub的Port状态变化回调函数
 * @return {FUsbTransCode} USB请求返回值
 * @param {FUsbDev} *dev, Hub实例
 * @param {int} port, Port号
 */
static FUsbTransCode FUsbHubPortStatusChange(FUsbDev *const dev, const int port)
{
    FASSERT(dev);
    unsigned short buf[FUSB_HUB_PORT_BUF_LEN]; /* Hub Status and Change Status */
    FUsbTransCode ret = FUsbGetStatus(dev, port, DR_PORT, sizeof(buf), buf);

    if (ret >= FUSB_CC_ZERO_BYTES)
    {
        ret = buf[FUSB_HUB_PORT_CHANGE] & FUSB_HUB_STATUS_PORT_CONNECTION;
        if (ret)
        {
            ret = FUsbClearFeature(dev, port, FUSB_HUB_SEL_C_PORT_CONNECTION, DR_PORT);
        }
    }

    return ret;
}

/**
 * @name: FUsbHubPortConnected
 * @msg: Usb Hub的Port连接回调函数
 * @return {FUsbTransCode} USB请求返回值
 * @param {FUsbDev} *dev, Hub实例
 * @param {int} port, Port号
 */
static FUsbTransCode FUsbHubPortConnected(FUsbDev *const dev, const int port)
{
    FASSERT(dev);
    unsigned short buf[FUSB_HUB_PORT_BUF_LEN]; /* Hub Status and Change Status */
    FUsbTransCode ret = FUsbGetStatus(dev, port, DR_PORT, sizeof(buf), buf);

    if (ret >= FUSB_CC_ZERO_BYTES)
    {
        ret = buf[FUSB_HUB_PORT_STATUS] & FUSB_HUB_STATUS_PORT_CONNECTION;
    }

    return ret;
}

/**
 * @name: FUsbHubPortInReset
 * @msg: 检查Hub port是否处于Reset状态
 * @return {FUsbTransCode} USB请求返回值
 * @param {FUsbDev} *dev, Hub实例
 * @param {int} port, Port号
 */
static FUsbTransCode FUsbHubPortInReset(FUsbDev *const dev, const int port)
{
    FASSERT(dev);
    unsigned short buf[FUSB_HUB_PORT_BUF_LEN]; /* Hub Status and Change Status */
    FUsbTransCode ret = FUsbGetStatus(dev, port, DR_PORT, sizeof(buf), buf);

    if (ret >= FUSB_CC_ZERO_BYTES)
    {
        ret = buf[FUSB_HUB_PORT_STATUS] & FUSB_HUB_STATUS_PORT_RESET;
    }

    return ret;
}

/**
 * @name: FUsbHubPortEnabled
 * @msg: 检查Hub port是否已使能
 * @return {FUsbTransCode} USB请求返回值
 * @param {FUsbDev} *dev, Hub实例
 * @param {int} port, Port号
 */
static FUsbTransCode FUsbHubPortEnabled(FUsbDev *const dev, const int port)
{
    FASSERT(dev);
    unsigned short buf[FUSB_HUB_PORT_BUF_LEN]; /* Hub Status and Change Status */
    FUsbTransCode ret = FUsbGetStatus(dev, port, DR_PORT, sizeof(buf), buf);

    if (ret >= FUSB_CC_ZERO_BYTES)
    {
        ret = buf[FUSB_HUB_PORT_STATUS] & FUSB_HUB_STATUS_PORT_ENABLE;
    }

    return ret;
}

/**
 * @name: FUsbHubPortSpeed
 * @msg: 获取Hub port的速度类型
 * @return {FUsbSpeed} Port的速度类型，支持SuperSpeed和HighSpeed
 * @param {FUsbDev} *dev, Hub实例
 * @param {int} port, Port号
 */
static FUsbSpeed FUsbHubPortSpeed(FUsbDev *const dev, const int port)
{
    FASSERT(dev);
    unsigned short buf[FUSB_HUB_PORT_BUF_LEN]; /* Hub Status and Change Status */
    FUsbTransCode ret = FUsbGetStatus(dev, port, DR_PORT, sizeof(buf), buf);
    int speed;

    if (ret >= FUSB_CC_ZERO_BYTES && (buf[FUSB_HUB_PORT_STATUS] & FUSB_HUB_STATUS_PORT_ENABLE))
    {
        /* SuperSpeed hubs can only have SuperSpeed devices. */
        if (FUsbIsSuperSpeed(dev->speed))
        {
            return dev->speed;
        }

        /*[bit] 10  9  (USB 2.0 port status word)
         *      0   0  full speed
         *      0   1  low speed
         *      1   0  high speed
         *      1   1  invalid
         */
        speed = (buf[FUSB_HUB_PORT_STATUS] >> 9) & 0x3;
        if (speed != 0x3) /* high-speed device */
        {
            return speed;
        }
    }

    return FUSB_UNKNOWN_SPEED;
}

/**
 * @name: FUsbHubEnablePort
 * @msg: 使能Hub port
 * @return {FUsbTransCode} USB请求返回值
 * @param {FUsbDev} *dev, Hub实例
 * @param {int} port, port号
 */
static FUsbTransCode FUsbHubEnablePort(FUsbDev *const dev, const int port)
{
    FASSERT(dev);
    return FUsbSetFeature(dev, port, FUSB_HUB_SEL_PORT_POWER, DR_PORT);
}

/**
 * @name: FUsbHubStartPortReset
 * @msg: 开始Reset Hub port
 * @return {FUsbTransCode} USB请求返回值
 * @param {FUsbDev} *dev, Hub实例
 * @param {int} port, port号
 */
static FUsbTransCode FUsbHubStartPortReset(FUsbDev *const dev, const int port)
{
    FASSERT(dev);
    return FUsbSetFeature(dev, port, FUSB_HUB_SEL_PORT_RESET, DR_PORT);
}

static void FUsbHubSetHubDepth(FUsbDev *const dev)
{
    FASSERT(dev);
    FUsbDevReq dr =
    {
        .bmRequestType = FUsbGenerateReqType(FUSB_REQ_HOST_TO_DEVICE,
                                             FUSB_REQ_TYPE_CLASS, FUSB_REQ_RECP_DEV),
        .bRequest = SET_HUB_DEPTH,
        .wValue = 0,
        .wIndex = 0,
        .wLength = 0,
    };
    FUsbDev *parent = dev;

    FASSERT(dev->controller);
    while (parent->hub > 0)
    {
        FASSERT(dev->controller->devices[parent->hub]);
        parent = dev->controller->devices[parent->hub];
        dr.wValue++;
    }

    FUsbTransCode ret = dev->controller->control(dev, FUSB_OUT, sizeof(dr), &dr, 0, NULL);
    if (ret < FUSB_CC_ZERO_BYTES)
    {
        FUSB_ERROR("Failed SET_HUB_DEPTH(%d) on hub %d: %d ",
                   dr.wValue, dev->address, ret);
    }

    return;
}

static const FUsbGenericHubOps FUSB_HUB_OPS =
{
    .hub_status_changed = NULL,
    .port_status_changed = FUsbHubPortStatusChange,
    .port_connected = FUsbHubPortConnected,
    .port_in_reset = FUsbHubPortInReset,
    .port_enabled = FUsbHubPortEnabled,
    .port_speed = FUsbHubPortSpeed,
    .enable_port = FUsbHubEnablePort,
    .disable_port = NULL,
    .start_port_reset = FUsbHubStartPortReset,
    .reset_port = FUsbGenericHubResetPort,
};

/* Clear CSC if set and enumerate port if it's connected regardless of change
   bits. Some broken hubs don't set CSC if already connected during reset. */
static void FUsbHubPortInit(FUsbDev *const dev, const int port)
{
    FASSERT(dev);
    unsigned short buf[FUSB_HUB_PORT_BUF_LEN]; /* Hub Status and Change Status */
    FUsbTransCode ret = FUsbGetStatus(dev, port, DR_PORT, sizeof(buf), buf);

    if (ret < FUSB_CC_ZERO_BYTES)
    {
        return;
    }

    if (buf[FUSB_HUB_PORT_CHANGE] & FUSB_HUB_STATUS_PORT_CONNECTION)
    {
        FUsbClearFeature(dev, port, FUSB_HUB_SEL_C_PORT_CONNECTION, DR_PORT);
    }

    if (buf[FUSB_HUB_PORT_STATUS] & FUSB_HUB_STATUS_PORT_CONNECTION)
    {
        FUSB_INFO("Usb hub: Port coldplug at %d ", port);
        FUsbGenericHubScanPort(dev, port);
    }

    return;
}

/**
 * @name: FUsbHubHandlePortChange
 * @msg: Hub端口状态变化的处理回调函数
 * @return {*}
 * @param {FUsbDev} *dev
 * @param {int} port
 */
static FUsbTransCode FUsbHubHandlePortChange(FUsbDev *const dev, const int port)
{
    FASSERT(dev);
    static const struct
    {
        unsigned short change_bit;
        unsigned short clear_sel;
    } change_bits[] =
    {
        {FUSB_HUB_STATUS_PORT_CONNECTION, FUSB_HUB_SEL_C_PORT_CONNECTION},
        {FUSB_HUB_STATUS_PORT_ENABLE, FUSB_HUB_SEL_C_PORT_ENABLE},
        {FUSB_HUB_STATUS_PORT_SUSPEND, FUSB_HUB_SEL_C_PORT_SUSPEND},
        {FUSB_HUB_STATUS_PORT_OVER_CURRENT, FUSB_HUB_SEL_C_PORT_OVER_CURRENT},
        {FUSB_HUB_STATUS_PORT_RESET, FUSB_HUB_SEL_C_PORT_RESET},
        {FUSB_HUB_STATUS_BH_PORT_RESET, FUSB_HUB_SEL_C_BH_PORT_RESET},
        {FUSB_HUB_STATUS_PORT_LINK_STATE, FUSB_HUB_SEL_C_PORT_LINK_STATE},
        {FUSB_HUB_STATUS_PORT_PORT_CONFIG_ERROR, FUSB_HUB_SEL_C_PORT_CONFIG_ERROR},
    };

    FUsbTransCode ret = 0;
    unsigned int i;
    unsigned short checked_bits = 0;
    unsigned short buf[FUSB_HUB_PORT_BUF_LEN] = {0, 0}; /* Hub Status and Change Status */

    ret = FUsbGetStatus(dev, port, DR_PORT, sizeof(buf), buf);
    if (ret < FUSB_CC_ZERO_BYTES)
    {
        return ret;
    }

    /*
     * Second word holds the change bits. The interrupt transfer shows
     * a logical or of these bits, so we have to clear them all.
     */
    for (i = 0; i < ARRAY_SIZE(change_bits); ++i)
    {
        if (buf[FUSB_HUB_PORT_CHANGE] & change_bits[i].change_bit)
        {
            /* clear feature if specific change bit = 1 */
            FUsbClearFeature(dev, port, change_bits[i].clear_sel, DR_PORT);
        }

        checked_bits |= change_bits[i].change_bit;
    }

    if (buf[FUSB_HUB_PORT_CHANGE] & ~checked_bits)
    {
        FUSB_DEBUG("Spurious change bit at port %d ", port);
    }

    /* Now, handle connection changes. */
    if (buf[FUSB_HUB_PORT_CHANGE] & FUSB_HUB_STATUS_PORT_CONNECTION)
    {
        FUSB_DEBUG("Port change at %d ", port);
        ret = FUsbGenericHubScanPort(dev, port);
    }

    return ret;
}

/**
 * @name: FUsbHubPoll
 * @msg: 轮询Hub的所有端口，检查端口状态变化
 * @return {*}
 * @param {FUsbDev} *dev, Hub设备实例
 */
static void FUsbHubPoll(FUsbDev *const dev)
{
    FASSERT(dev);
    int port, i;
    u8 buf[32] = {0};
    const u8 *ibuf;

    /* First, gather all change bits from finished interrupt transfers. */
    const size_t port_bytes = min(ARRAY_SIZE(buf),
                                  (size_t)DIV_ROUND_UP(FUSB_GEN_HUB_GET(dev)->num_ports + 1, 8));

    while (NULL != (ibuf = dev->controller->poll_intr_queue(FUSB_GEN_HUB_GET(dev)->data)))
    {
        for (i = 0; (size_t)i < port_bytes; ++i)
        {
            buf[i] |= ibuf[i];
        }
    }

    for (port = 1; port <= FUSB_GEN_HUB_GET(dev)->num_ports; ++port)
    {
        /* ports start at bit1; bit0 is hub status change */
        if (buf[port / 8] & (1 << (port % 8)))
        {
            if (FUsbHubHandlePortChange(dev, port) < 0)
            {
                return;
            }
        }
    }

    return;
}

/**
 * @name: FUsbHubDestory
 * @msg: USB Hub的去初始化函数
 * @return {*}
 * @param {FUsbDev} *dev, Hub设备实例
 */
static void FUsbHubDestory(FUsbDev *const dev)
{
    FASSERT(dev);
    FUsbEndpoint *const intr_ep = FUsbHubIntrEp(dev);
    FASSERT(intr_ep); /* interrupt ep must exists */
    dev->controller->destroy_intr_queue(intr_ep, FUSB_GEN_HUB_GET(dev)->data);
    FUsbGenericHubDestory(dev);
}

/**
 * @name: FUsbHubInit
 * @msg: USB Hub的初始化函数，由应用程序注册到FUSB框架中
 * @return {*}
 * @param {FUsbDev} *dev, Hub设备实例
 */
void FUsbHubInit(FUsbDev *dev)
{
    FASSERT(dev);
    FUsbEndpoint *const intr_ep = FUsbHubIntrEp(dev); /* get the first intrrupt ep found */
    if (NULL == intr_ep)
    {
        FUSB_ERROR("No interrupt-in endpoint found ");
        return;
    }

    FASSERT(dev->controller);

    /* Get number of ports from hub descriptor */
    int type = FUsbIsSuperSpeed(dev->speed) ? FUSB_DESC_TYPE_SUPER_SPEED_HUB : FUSB_DESC_TYPE_HUB; /* similar enough */
    FUsbHubDescriptor desc;                                /* won't fit the whole thing, we don't care */
    if (FUsbGetDescriptor(dev, FUsbGenerateReqType(FUSB_REQ_DEVICE_TO_HOST, FUSB_REQ_TYPE_CLASS, FUSB_REQ_RECP_DEV), type, 0, &desc, sizeof(desc)) != sizeof(desc))
    {
        FUSB_ERROR("FUsbGetDescriptor(HUB) failed ");
        FUsbDetachDev(dev->controller, dev->address);
        return;
    }

    if (FUsbIsSuperSpeed(dev->speed))
    {
        FUsbHubSetHubDepth(dev);
    }

    /*
     * Register interrupt transfer:
     *   one bit per port + one bit for the hub,
     *   20 transfers in the queue, like our HID driver,
     *   one transfer per 256ms
     */
    void *const intrq = dev->controller->create_intr_queue(
                            intr_ep, intr_ep->maxpacketsize, 20, 256);
    if (NULL == intrq)
    {
        FUsbDetachDev(dev->controller, dev->address);
        return;
    }

    /*
     * Limit the number of ports by the max packet size of
     * the interrupt endpoint. This shouldn't be necessary
     * but prevents a potential overflow in FUsbHubPoll().
     */
    const unsigned int num_ports =
        min((int)desc.bNbrPorts, intr_ep->maxpacketsize * 8 - 1);
    if (FUsbGenericHubInit(dev, num_ports, &FUSB_HUB_OPS))
    {
        dev->controller->destroy_intr_queue(intr_ep, intrq);
        FUsbDetachDev(dev->controller, dev->address);
        return;
    }

    unsigned int port;
    for (port = 1; port <= num_ports; ++port)
    {
        FUsbHubPortInit(dev, port);
    }

    FUSB_GEN_HUB_GET(dev)->data = intrq;
    dev->poll = FUsbHubPoll;
    dev->destroy = FUsbHubDestory;

    return;
}
