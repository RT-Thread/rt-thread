/*
*******************************************************************************
*                                              usb host module
*
*                             Copyright(C), 2006-2008, SoftWinners Co., Ltd.
*                                                  All Rights Reserved
*
* File Name :
*
* Author : GLHuang(HoLiGun)
*
* Version : 1.0
*
* Date : 2008.07.xx
*
* Description :
*
* History :
*******************************************************************************
*/
//#include "usb_host_config.h"

//#include "usb_os_platform.h"
#include <usb_host_common.h>

//#include "usb_host_base_types.h"
//#include "usb_list.h"
#include <usb_host_hub.h>
#include <usb_utils_find_zero_bit.h>
#include "usb_core_base.h"
#include "usb_msg.h"

#include "usb_virt_bus.h"
#include <usb_gen_dev_mod.h>

#include "usb_gen_hub_base.h"
#include "urb.h"




/*
 * USB 2.0 spec Section 11.24.2.7
 */

/*
********************************************************************************
*                     get_port_status
* Description:
*     获得hub端口的状态
* Arguments:
*     hdev  : input.  hub
*     port1 : input.  端口号
*     data  : output. 用来记录端口状态
* Return value:
*     void
* note:
*     void
*********************************************************************************
*/
static int get_port_status(struct usb_host_virt_dev *hdev, int port1,
                           struct usb_port_status *data)
{
    int i, status = -ETIMEDOUT;

    for (i = 0; i < USB_STS_RETRIES && status == -ETIMEDOUT; i++)
    {
        status = usb_control_msg(hdev,
                                 usb_rcvctrlpipe(hdev, 0),
                                 USB_REQ_GET_STATUS,
                                 USB_DIR_IN | USB_RT_PORT,
                                 0,
                                 port1,
                                 (void *)data,
                                 sizeof(*data),
                                 USB_STS_TIMEOUT);
    }

    return status;
}

/*
********************************************************************************
*                     get_port_status
* Description:
*     获得hub端口的状态
* Arguments:
*     hdev    : input.  hub
*     port1   : input.  端口号
*     status  : output. 用来记录端口状态
*     change  : output. 用来记录端口的变化
* Return value:
*     void
* note:
*     void
*********************************************************************************
*/
s32 hub_port_status(struct usb_hub *hub, s32 port1, u16 *status, u16 *change)
{
    int ret;

    ret = get_port_status(hub->hdev, port1, &hub->status->port);

    if (ret < 0)
    {
        hal_log_err("hub_port_status() : failed (err = %d)\n",  ret);
    }
    else
    {
        *status = le16_to_cpu(hub->status->port.wPortStatus);
        *change = le16_to_cpu(hub->status->port.wPortChange);
        ret = 0;
    }

    return ret;
}





#ifdef  CONFIG_USB_SUSPEND

/*
 * Selective port suspend reduces power; most suspended devices draw
 * less than 500 uA.  It's also used in OTG, along with remote wakeup.
 * All devices below the suspended port are also suspended.
 *
 * Devices leave suspend state when the host wakes them up.  Some devices
 * also support "remote wakeup", where the device can activate the USB
 * tree above them to deliver data, such as a keypress or packet.  In
 * some cases, this wakes the USB host.
 */
/*
********************************************************************************
*                     hub_port_suspend
* Description:
*     获得hub端口的状态
* Arguments:
*     hdev    : input.  hub
*     port1   : input.  端口号
*     status  : output. 用来记录端口状态
*     change  : output. 用来记录端口的变化
* Return value:
*     void
* note:
*     void
*********************************************************************************
*/
static int hub_port_suspend(struct usb_hub *hub, int port1, struct usb_device *udev)
{
    int status;

    // dev_dbg(hub->intfdev, "suspend port %d\n", port1);

    /* enable remote wakeup when appropriate; this lets the device
     * wake up the upstream hub (including maybe the root hub).
     *
     * NOTE:  OTG devices may issue remote wakeup (or SRP) even when
     * we don't explicitly enable it here.
     */
    if (udev->actconfig
        // && FIXME (remote wakeup enabled on this bus)
        // ... currently assuming it's always appropriate
        && (udev->actconfig->desc.bmAttributes
            & USB_CONFIG_ATT_WAKEUP) != 0)
    {
        status = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
                                 USB_REQ_SET_FEATURE, USB_RECIP_DEVICE,
                                 USB_DEVICE_REMOTE_WAKEUP, 0,
                                 NULL, 0,
                                 USB_CTRL_SET_TIMEOUT);

        if (status)
            dev_dbg(&udev->dev,
                    "won't remote wakeup, status %d\n",
                    status);
    }

    /* see 7.1.7.6 */
    status = set_port_feature(hub->hdev, port1, USB_PORT_FEAT_SUSPEND);

    if (status)
    {
        dev_dbg(hub->intfdev,
                "can't suspend port %d, status %d\n",
                port1, status);
        /* paranoia:  "should not happen" */
        (void) usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
                               USB_REQ_CLEAR_FEATURE, USB_RECIP_DEVICE,
                               USB_DEVICE_REMOTE_WAKEUP, 0,
                               NULL, 0,
                               USB_CTRL_SET_TIMEOUT);
    }
    else
    {
        /* device has up to 10 msec to fully suspend */
        dev_dbg(&udev->dev, "usb suspend\n");
        usb_set_device_state(udev, USB_STATE_SUSPENDED);
        msleep(10);
    }

    return status;
}

/*
 * Devices on USB hub ports have only one "suspend" state, corresponding
 * to ACPI D2, "may cause the device to lose some context".
 * State transitions include:
 *
 *   - suspend, resume ... when the VBUS power link stays live
 *   - suspend, disconnect ... VBUS lost
 *
 * Once VBUS drop breaks the circuit, the port it's using has to go through
 * normal re-enumeration procedures, starting with enabling VBUS power.
 * Other than re-initializing the hub (plug/unplug, except for root hubs),
 * Linux (2.6) currently has NO mechanisms to initiate that:  no khubd
 * timer, no SRP, no requests through sysfs.
 */
static int __usb_suspend_device(struct usb_device *udev, int port1,
                                pm_message_t state)
{
    int status;

    /* caller owns the udev device lock */
    if (port1 < 0)
    {
        return port1;
    }

    if (udev->state == USB_STATE_SUSPENDED
        || udev->state == USB_STATE_NOTATTACHED)
    {
        return 0;
    }

    /* suspend interface drivers; if this is a hub, it
     * suspends the child devices
     */
    if (udev->actconfig)
    {
        int i;

        for (i = 0; i < udev->actconfig->desc.bNumInterfaces; i++)
        {
            struct usb_interface    *intf;
            struct usb_driver   *driver;
            intf = udev->actconfig->interface[i];

            if (state <= intf->dev.power.power_state)
            {
                continue;
            }

            if (!intf->dev.driver)
            {
                continue;
            }

            driver = to_usb_driver(intf->dev.driver);

            if (driver->suspend)
            {
                status = driver->suspend(intf, state);

                if (intf->dev.power.power_state != state
                    || status)
                    dev_err(&intf->dev,
                            "suspend %d fail, code %d\n",
                            state, status);
            }

            /* only drivers with suspend() can ever resume();
             * and after power loss, even they won't.
             * bus_rescan_devices() can rebind drivers later.
             *
             * FIXME the PM core self-deadlocks when unbinding
             * drivers during suspend/resume ... everything grabs
             * dpm_sem (not a spinlock, ugh).  we want to unbind,
             * since we know every driver's probe/disconnect works
             * even for drivers that can't suspend.
             */
            if (!driver->suspend || state > PM_SUSPEND_MEM)
            {
#if 1
                dev_warn(&intf->dev, "resume is unsafe!\n");
#else
                down_write(&usb_bus_type.rwsem);
                device_release_driver(&intf->dev);
                up_write(&usb_bus_type.rwsem);
#endif
            }
        }
    }

    /*
     * FIXME this needs port power off call paths too, to help force
     * USB into the "generic" PM model.  At least for devices on
     * ports that aren't using ganged switching (usually root hubs).
     *
     * NOTE: SRP-capable links should adopt more aggressive poweroff
     * policies (when HNP doesn't apply) once we have mechanisms to
     * turn power back on!  (Likely not before 2.7...)
     */
    if (state > PM_SUSPEND_MEM)
    {
        dev_warn(&udev->dev, "no poweroff yet, suspending instead\n");
    }

    /* "global suspend" of the HC-to-USB interface (root hub), or
     * "selective suspend" of just one hub-device link.
     */
    if (!udev->parent)
    {
        struct usb_bus  *bus = udev->bus;

        if (bus && bus->op->hub_suspend)
        {
            status = bus->op->hub_suspend(bus);

            if (status == 0)
            {
                dev_dbg(&udev->dev, "usb suspend\n");
                usb_set_device_state(udev,
                                     USB_STATE_SUSPENDED);
            }
        }
        else
        {
            status = -EOPNOTSUPP;
        }
    }
    else
        status = hub_port_suspend(hdev_to_hub(udev->parent), port1,
                                  udev);

    if (status == 0)
    {
        udev->dev.power.power_state = state;
    }

    return status;
}

/**
 * usb_suspend_device - suspend a usb device
 * @udev: device that's no longer in active use
 * @state: PMSG_SUSPEND to suspend
 * Context: must be able to sleep; device not locked
 *
 * Suspends a USB device that isn't in active use, conserving power.
 * Devices may wake out of a suspend, if anything important happens,
 * using the remote wakeup mechanism.  They may also be taken out of
 * suspend by the host, using usb_resume_device().  It's also routine
 * to disconnect devices while they are suspended.
 *
 * Suspending OTG devices may trigger HNP, if that's been enabled
 * between a pair of dual-role devices.  That will change roles, such
 * as from A-Host to A-Peripheral or from B-Host back to B-Peripheral.
 *
 * Returns 0 on success, else negative errno.
 */
int usb_suspend_device(struct usb_device *udev, pm_message_t state)
{
    int port1, status;
    port1 = locktree(udev);

    if (port1 < 0)
    {
        return port1;
    }

    status = __usb_suspend_device(udev, port1, state);
    // usb_unlock_device(udev);
    return status;
}

/*
 * hardware resume signaling is finished, either because of selective
 * resume (by host) or remote wakeup (by device) ... now see what changed
 * in the tree that's rooted at this device.
 */
static int finish_port_resume(struct usb_device *udev)
{
    int status;
    u16 devstatus;
    /* caller owns the udev device lock */
    dev_dbg(&udev->dev, "usb resume\n");
    /* usb ch9 identifies four variants of SUSPENDED, based on what
     * state the device resumes to.  Linux currently won't see the
     * first two on the host side; they'd be inside hub_port_init()
     * during many timeouts, but khubd can't suspend until later.
     */
    usb_set_device_state(udev, udev->actconfig
                         ? USB_STATE_CONFIGURED
                         : USB_STATE_ADDRESS);
    udev->dev.power.power_state = PMSG_ON;
    /* 10.5.4.5 says be sure devices in the tree are still there.
     * For now let's assume the device didn't go crazy on resume,
     * and device drivers will know about any resume quirks.
     */
    status = usb_get_status(udev, USB_RECIP_DEVICE, 0, &devstatus);

    if (status < 0)
        dev_dbg(&udev->dev,
                "gone after usb resume? status %d\n",
                status);
    else if (udev->actconfig)
    {
        unsigned    i;
        le16_to_cpus(&devstatus);

        if (devstatus & (1 << USB_DEVICE_REMOTE_WAKEUP))
        {
            status = usb_control_msg(udev,
                                     usb_sndctrlpipe(udev, 0),
                                     USB_REQ_CLEAR_FEATURE,
                                     USB_RECIP_DEVICE,
                                     USB_DEVICE_REMOTE_WAKEUP, 0,
                                     NULL, 0,
                                     USB_CTRL_SET_TIMEOUT);

            if (status)
            {
                dev_dbg(&udev->dev, "disable remote "
                        "wakeup, status %d\n", status);
                status = 0;
            }
        }

        /* resume interface drivers; if this is a hub, it
         * resumes the child devices
         */
        for (i = 0; i < udev->actconfig->desc.bNumInterfaces; i++)
        {
            struct usb_interface    *intf;
            struct usb_driver   *driver;
            intf = udev->actconfig->interface[i];

            if (intf->dev.power.power_state == PMSG_ON)
            {
                continue;
            }

            if (!intf->dev.driver)
            {
                /* FIXME maybe force to alt 0 */
                continue;
            }

            driver = to_usb_driver(intf->dev.driver);

            /* bus_rescan_devices() may rebind drivers */
            if (!driver->resume)
            {
                continue;
            }

            /* can we do better than just logging errors? */
            status = driver->resume(intf);

            if (intf->dev.power.power_state != PMSG_ON
                || status)
                dev_dbg(&intf->dev,
                        "resume fail, state %d code %d\n",
                        intf->dev.power.power_state, status);
        }

        status = 0;
    }
    else if (udev->devnum <= 0)
    {
        dev_dbg(&udev->dev, "bogus resume!\n");
        status = -EINVAL;
    }

    return status;
}

static int hub_port_resume(struct usb_hub *hub, int port1, struct usb_device *udev)
{
    int status;
    // dev_dbg(hub->intfdev, "resume port %d\n", port1);
    /* see 7.1.7.7; affects power usage, but not budgeting */
    status = clear_port_feature(hub->hdev,
                                port1, USB_PORT_FEAT_SUSPEND);

    if (status)
    {
        dev_dbg(hub->intfdev,
                "can't resume port %d, status %d\n",
                port1, status);
    }
    else
    {
        u16     devstatus;
        u16     portchange;

        /* drive resume for at least 20 msec */
        if (udev)
        {
            dev_dbg(&udev->dev, "RESUME\n");
        }

        msleep(25);
#define LIVE_FLAGS  ( USB_PORT_STAT_POWER \
                      | USB_PORT_STAT_ENABLE \
                      | USB_PORT_STAT_CONNECTION)
        /* Virtual root hubs can trigger on GET_PORT_STATUS to
         * stop resume signaling.  Then finish the resume
         * sequence.
         */
        devstatus = portchange = 0;
        status = hub_port_status(hub, port1,
                                 &devstatus, &portchange);

        if (status < 0
            || (devstatus & LIVE_FLAGS) != LIVE_FLAGS
            || (devstatus & USB_PORT_STAT_SUSPEND) != 0
           )
        {
            dev_dbg(hub->intfdev,
                    "port %d status %04x.%04x after resume, %d\n",
                    port1, portchange, devstatus, status);
        }
        else
        {
            /* TRSMRCY = 10 msec */
            msleep(10);

            if (udev)
            {
                status = finish_port_resume(udev);
            }
        }
    }

    if (status < 0)
    {
        hub_port_logical_disconnect(hub, port1);
    }

    return status;
}

static int hub_resume(struct usb_interface *intf);

/**
 * usb_resume_device - re-activate a suspended usb device
 * @udev: device to re-activate
 * Context: must be able to sleep; device not locked
 *
 * This will re-activate the suspended device, increasing power usage
 * while letting drivers communicate again with its endpoints.
 * USB resume explicitly guarantees that the power session between
 * the host and the device is the same as it was when the device
 * suspended.
 *
 * Returns 0 on success, else negative errno.
 */
int usb_resume_device(struct usb_device *udev)
{
    int port1, status;
    port1 = locktree(udev);

    if (port1 < 0)
    {
        return port1;
    }

    /* "global resume" of the HC-to-USB interface (root hub), or
     * selective resume of one hub-to-device port
     */
    if (!udev->parent)
    {
        struct usb_bus  *bus = udev->bus;

        if (bus && bus->op->hub_resume)
        {
            status = bus->op->hub_resume(bus);
        }
        else
        {
            status = -EOPNOTSUPP;
        }

        if (status == 0)
        {
            dev_dbg(&udev->dev, "usb resume\n");
            /* TRSMRCY = 10 msec */
            msleep(10);
            usb_set_device_state(udev, USB_STATE_CONFIGURED);
            udev->dev.power.power_state = PMSG_ON;
            status = hub_resume(udev
                                ->actconfig->interface[0]);
        }
    }
    else if (udev->state == USB_STATE_SUSPENDED)
    {
        // NOTE this fails if parent is also suspended...
        status = hub_port_resume(hdev_to_hub(udev->parent),
                                 port1, udev);
    }
    else
    {
        status = 0;
    }

    if (status < 0)
    {
        dev_dbg(&udev->dev, "can't resume, status %d\n",
                status);
    }

    // usb_unlock_device(udev);

    /* rebind drivers that had no suspend() */
    if (status == 0)
    {
        usb_lock_all_devices();
        bus_rescan_devices(&usb_bus_type);
        usb_unlock_all_devices();
    }

    return status;
}

static int remote_wakeup(struct usb_device *udev)
{
    int status = 0;
    /* don't repeat RESUME sequence if this device
     * was already woken up by some other task
     */
    down(&udev->serialize);

    if (udev->state == USB_STATE_SUSPENDED)
    {
        dev_dbg(&udev->dev, "RESUME (wakeup)\n");
        /* TRSMRCY = 10 msec */
        msleep(10);
        status = finish_port_resume(udev);
    }

    up(&udev->serialize);
    return status;
}

static __s32 hub_suspend(struct usb_interface *intf, pm_message_t state)
{
    struct usb_hub      *hub = usb_mod_usb_get_intf_priv_data(intf);
    struct usb_device   *hdev = hub->hdev;
    unsigned        port1;
    int         status;
    /* stop khubd and related activity */
    hub_quiesce(hub);

    /* then suspend every port */
    for (port1 = 1; port1 <= hdev->maxchild; port1++)
    {
        struct usb_device   *udev;
        udev = hdev->children [port1 - 1];

        if (!udev)
        {
            continue;
        }

        down(&udev->serialize);
        status = __usb_suspend_device(udev, port1, state);
        up(&udev->serialize);

        if (status < 0)
            dev_dbg(&intf->dev, "suspend port %d --> %d\n",
                    port1, status);
    }

    intf->dev.power.power_state = state;
    return 0;
}

static int hub_resume(struct usb_interface *intf)
{
    struct usb_device   *hdev = usb_mod_interface_to_usbdev(intf);
    struct usb_hub      *hub = usb_mod_usb_get_intf_priv_data(intf);
    unsigned        port1;
    int         status;

    if (intf->dev.power.power_state == PM_SUSPEND_ON)
    {
        return 0;
    }

    for (port1 = 1; port1 <= hdev->maxchild; port1++)
    {
        struct usb_device   *udev;
        u16         portstat, portchange;
        udev = hdev->children [port1 - 1];
        status = hub_port_status(hub, port1, &portstat, &portchange);

        if (status == 0)
        {
            if (portchange & USB_PORT_STAT_C_SUSPEND)
            {
                clear_port_feature(hdev, port1,
                                   USB_PORT_FEAT_C_SUSPEND);
                portchange &= ~USB_PORT_STAT_C_SUSPEND;
            }

            /* let khubd handle disconnects etc */
            if (portchange)
            {
                continue;
            }
        }

        if (!udev || status < 0)
        {
            continue;
        }

        down(&udev->serialize);

        if (portstat & USB_PORT_STAT_SUSPEND)
        {
            status = hub_port_resume(hub, port1, udev);
        }
        else
        {
            status = finish_port_resume(udev);

            if (status < 0)
            {
                dev_dbg(&intf->dev, "resume port %d --> %d\n",
                        port1, status);
                hub_port_logical_disconnect(hub, port1);
            }
        }

        up(&udev->serialize);
    }

    intf->dev.power.power_state = PMSG_ON;
    hub->resume_root_hub = 0;
    hub_activate(hub);
    return 0;
}

void usb_resume_root_hub(struct usb_device *hdev)
{
    struct usb_hub *hub = hdev_to_hub(hdev);
    hub->resume_root_hub = 1;
    kick_khubd(hub);
}

#else   /* !CONFIG_USB_SUSPEND */

s32 usb_suspend_device(struct usb_host_virt_dev *virt_dev)
{
    return 0;
}

s32 usb_resume_device(struct usb_host_virt_dev *virt_dev)
{
    return 0;
}



__s32 hub_suspend(struct usb_interface *intf)
{
    return 0;
}

int hub_resume(struct usb_interface *intf)
{
    return 0;
}


int remote_wakeup(struct usb_host_virt_dev *udev)
{
    return 0;
}

#endif  /* CONFIG_USB_SUSPEND */







void hub_quiesce(struct usb_hub *hub)
{
    if (hub == NULL)
    {
        __err("ERR: hub_quiesce: input error\n");
        return;
    }

    /* stop khubd and related activity */
    hub->quiescing = 1;
    usb_kill_urb(hub->urb);
    /*
        if (hub->has_indicators)
            cancel_delayed_work(&hub->leds);
        if (hub->has_indicators || hub->tt.hub)
            flush_scheduled_work();
    */
}

/*
 * USB 2.0 spec Section 11.24.2.6
 */
static int get_hub_status(struct usb_host_virt_dev *hdev,
                          struct usb_hub_status *data)
{
    int i, status = -ETIMEDOUT;

    for (i = 0; i < USB_STS_RETRIES && status == -ETIMEDOUT; i++)
    {
        status = usb_control_msg(hdev, usb_rcvctrlpipe(hdev, 0),
                                 USB_REQ_GET_STATUS, USB_DIR_IN | USB_RT_HUB, 0, 0,
                                 (void *)data, sizeof(*data), USB_STS_TIMEOUT);
    }

    return status;
}

int hub_hub_status(struct usb_hub *hub,
                   u16 *status, u16 *change)
{
    int ret;
    ret = get_hub_status(hub->hdev, &hub->status->hub);

    if (ret < 0)
    {
        __err("PANIC : hub_hub_status()  failed (err = %d)\n", ret);
    }
    else
    {
        *status = le16_to_cpu(hub->status->hub.wHubStatus);
        *change = le16_to_cpu(hub->status->hub.wHubChange);
        ret = 0;
    }

    return ret;
}



//限制: 只能在thread环境中使用,isr中是禁止的
int hub_thread_sleep(struct hub_thread_context *thread_cont)
{
    u8  ret = 0;
    //USB_OS_SEMI_PEND(thread_cont->hub_thread_event, 0, &ret);
    hal_sem_wait(thread_cont->hub_thread_event);

    //if (ret != USB_OS_NO_ERR)
    if (ret != 0)
    {
        __err("PANIC : hub_thread_sleep() : ret = %d\n", ret);
        return -1;
    }

    return (ret ? -EINTR : 0);
}

//可以在thead,isr中使用
void hub_thread_wakeup(struct hub_thread_context *thread_cont)
{
    //USB_OS_SEMI_POST(thread_cont->hub_thread_event);
    hal_sem_post(thread_cont->hub_thread_event);
}


