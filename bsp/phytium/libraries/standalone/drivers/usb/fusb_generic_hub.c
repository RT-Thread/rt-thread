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
 * FilePath: fusb_generic_hub.c
 * Date: 2022-02-11 13:33:11
 * LastEditTime: 2022-02-18 09:19:27
 * Description:  This files is for implmentation of generic hub function
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#include "fsleep.h"
#include "fdebug.h"
#include "fusb.h"
#include "fusb_generic_hub.h"

#define FUSB_DEBUG_TAG "FUSB_HUB"
#define FUSB_ERROR(format, ...) FT_DEBUG_PRINT_E(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_WARN(format, ...) FT_DEBUG_PRINT_W(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_INFO(format, ...) FT_DEBUG_PRINT_I(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_DEBUG(format, ...) FT_DEBUG_PRINT_D(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)

void FUsbGenericHubDestory(FUsbDev *const dev)
{
    FUsbGenericHub *const hub = FUSB_GEN_HUB_GET(dev);
    FUsb *instace = dev->controller->usb;
    if (!hub)
    {
        return;
    }

    /* First, detach all devices behind this hub */
    int port;
    for (port = 1; port <= hub->num_ports; ++port)
    {
        if (hub->ports[port] >= 0)
        {
            FUSB_INFO("Generic hub: Detachment at port %d ", port);
            FUsbDetachDev(dev->controller, hub->ports[port]);
            hub->ports[port] = FUSB_NO_DEV_ADDR;
        }
    }

    /* Disable all ports */
    if (hub->ops->disable_port)
    {
        for (port = 1; port <= hub->num_ports; ++port)
        {
            hub->ops->disable_port(dev, port);
        }
    }

    FUSB_FREE(instace, hub->ports); // free(hub->ports);
    FUSB_FREE(instace, hub);           // free(hub);
}

static int FUsbGenericHubDebounce(FUsbDev *const dev, const int port)
{
    FUsbGenericHub *const hub = FUSB_GEN_HUB_GET(dev);

    const int step_ms = 1;       /* linux uses 25ms, we're busy anyway */
    const int at_least_ms = 100; /* 100ms as in usb20 spec 9.1.2 */
    const int timeout_ms = 1500; /* linux uses this value */

    int total_ms = 0;
    int stable_ms = 0;
    while (stable_ms < at_least_ms && total_ms < timeout_ms)
    {
        fsleep_millisec(step_ms);

        const int changed = hub->ops->port_status_changed(dev, port);
        const int connected = hub->ops->port_connected(dev, port);
        if (changed < 0 || connected < 0)
        {
            return -1;
        }

        if (!changed && connected)
        {
            stable_ms += step_ms;
        }
        else
        {
            FUSB_INFO("Generic hub: Unstable connection at %d ",
                      port);
            stable_ms = 0;
        }
        total_ms += step_ms;
    }
    if (total_ms >= timeout_ms)
    {
        FUSB_INFO("Generic hub: Debouncing timed out at %d ", port);
    }
    return 0; /* ignore timeouts, try to always go on */
}

int FUsbGenericHubWaitForPort(FUsbDev *const dev, const int port,
                              const int wait_for,
                              int (*const port_op)(FUsbDev *, int),
                              int timeout_steps, const int step_us)
{
    int state;
    do
    {
        state = port_op(dev, port);
        if (state < 0)
        {
            return -1;
        }
        else if (!!state == wait_for)
        {
            return timeout_steps;
        }
        fsleep_microsec(step_us);
        --timeout_steps;
    }
    while (timeout_steps);

    return 0;
}

int FUsbGenericHubResetPort(FUsbDev *const dev, const int port)
{
    FUsbGenericHub *const hub = FUSB_GEN_HUB_GET(dev);

    if (hub->ops->start_port_reset(dev, port) < 0)
    {
        return -1;
    }

    /* wait for 10ms (usb20 spec 11.5.1.5: reset should take 10 to 20ms) */
    fsleep_millisec(10);

    /* now wait 12ms for the hub to finish the reset */
    const int ret = FUsbGenericHubWaitForPort(
                        /* time out after 120 * 100us = 12ms */
                        dev, port, 0, hub->ops->port_in_reset, 120, 100);
    if (ret < 0)
    {
        return -1;
    }
    else if (!ret)
    {
        FUSB_INFO("Generic hub: Reset timed out at port %d ", port);
    }

    return 0; /* ignore timeouts, try to always go on */
}

static int FUsbGenericHubDetachDev(FUsbDev *const dev, const int port)
{
    FUsbGenericHub *const hub = FUSB_GEN_HUB_GET(dev);

    FUsbDetachDev(dev->controller, hub->ports[port]);
    hub->ports[port] = FUSB_NO_DEV_ADDR;

    return 0;
}

static int FUsbGenericHubAttachDev(FUsbDev *const dev, const int port)
{
    FUsbGenericHub *const hub = FUSB_GEN_HUB_GET(dev);

    if (FUsbGenericHubDebounce(dev, port) < 0)
    {
        return -1;
    }

    if (hub->ops->reset_port)
    {
        if (hub->ops->reset_port(dev, port) < 0)
        {
            return -1;
        }

        if (!hub->ops->port_connected(dev, port))
        {
            FUSB_INFO(
                "Generic hub: Port %d disconnected after "
                "reset. Possibly upgraded, rescan required. ",
                port);
            return 0;
        }

        /* after reset the port will be enabled automatically */
        const int ret = FUsbGenericHubWaitForPort(
                            /* time out after 1,000 * 10us = 10ms */
                            dev, port, 1, hub->ops->port_enabled, 1000, 10);
        if (ret < 0)
        {
            return -1;
        }
        else if (!ret)
            FUSB_INFO("Generic hub: Port %d still "
                      "disabled after 10ms ",
                      port);
    }

    const FUsbSpeed speed = hub->ops->port_speed(dev, port);
    if (speed >= 0)
    {
        FUSB_DEBUG("Generic hub: Success at port %d ", port);
        if (hub->ops->reset_port)
        {
            fsleep_millisec(10);
        } /* Reset recovery time
                       (usb20 spec 7.1.7.5) */
        hub->ports[port] = FUsbAttachDev(
                               dev->controller, dev->address, port, speed);
    }
    return 0;
}

int FUsbGenericHubScanPort(FUsbDev *const dev, const int port)
{
    FUsbGenericHub *const hub = FUSB_GEN_HUB_GET(dev);

    if (hub->ports[port] >= 0)
    {
        FUSB_INFO("Generic hub: Detachment at port %d ", port);
        const int ret = FUsbGenericHubDetachDev(dev, port);
        if (ret < 0)
        {
            return ret;
        }
    }

    if (hub->ops->port_connected(dev, port))
    {
        FUSB_INFO("Generic hub: Attachment at port %d ", port);
        return FUsbGenericHubAttachDev(dev, port);
    }

    return 0;
}

static void FUsbGenericHubPoll(FUsbDev *const dev)
{
    FUsbGenericHub *const hub = FUSB_GEN_HUB_GET(dev);
    if (!hub)
    {
        return;
    }

    if (hub->ops->hub_status_changed &&
        hub->ops->hub_status_changed(dev) != FUSB_CC_SUCCESS)
    {
        return;
    }

    int port;
    for (port = 1; port <= hub->num_ports; ++port)
    {
        const FUsbTransCode ret = hub->ops->port_status_changed(dev, port);
        if (ret < 0)
        {
            FUSB_WARN("Transcode %d", ret);
            return;
        }
        else if (ret == FUSB_CC_SUCCESS)
        {
            FUSB_INFO("Generic hub: Port change at %d ", port);
            if (FUsbGenericHubScanPort(dev, port) < 0)
            {
                return;
            }
        }
    }
}

int FUsbGenericHubInit(FUsbDev *const dev, const int num_ports,
                       const FUsbGenericHubOps *const ops)
{
    int port;
    FUsb *instance = dev->controller->usb;

    dev->destroy = FUsbGenericHubDestory;
    dev->poll = FUsbGenericHubPoll;
    FASSERT(NULL == dev->data);
    dev->data = FUSB_ALLOCATE(instance, sizeof(FUsbGenericHub), FUSB_DEFAULT_ALIGN);
    if (NULL == dev->data)
    {
        FUSB_ERROR("Generic hub: Out of memory ");
        return -1;
    }

    FUsbGenericHub *const hub = FUSB_GEN_HUB_GET(dev);
    hub->num_ports = num_ports;
    FASSERT(NULL == hub->ports);
    hub->ports = FUSB_ALLOCATE(instance, sizeof(*hub->ports) * (num_ports + 1), FUSB_DEFAULT_ALIGN);
    hub->ops = ops;
    if (NULL == hub->ports)
    {
        FUSB_ERROR("Generic hub: Out of memory ");
        FUSB_FREE(instance, dev->data);
        dev->data = NULL;
        return -1;
    }

    for (port = 1; port <= num_ports; ++port)
    {
        hub->ports[port] = FUSB_NO_DEV_ADDR;
    }

    /* Enable all ports */
    if (ops->enable_port)
    {
        for (port = 1; port <= num_ports; ++port)
        {
            ops->enable_port(dev, port);
        }

        /* wait once for all ports */
        fsleep_millisec(20);
    }

    return 0;
}
