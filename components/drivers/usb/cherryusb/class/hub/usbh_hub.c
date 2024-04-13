/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_hub.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_hub"
#include "usb_log.h"

#define DEV_FORMAT "/dev/hub%d"

#define HUB_DEBOUNCE_TIMEOUT   1500
#define HUB_DEBOUNCE_STEP      25
#define HUB_DEBOUNCE_STABLE    100
#define DELAY_TIME_AFTER_RESET 200

#define EXTHUB_FIRST_INDEX 2

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_hub_buf[CONFIG_USBHOST_MAX_BUS][USB_ALIGN_UP(32, CONFIG_USB_ALIGN_SIZE)];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_hub_intbuf[CONFIG_USBHOST_MAX_BUS][CONFIG_USBHOST_MAX_EXTHUBS + 1][USB_ALIGN_UP(1, CONFIG_USB_ALIGN_SIZE)];

extern int usbh_enumerate(struct usbh_hubport *hport);
extern void usbh_hubport_release(struct usbh_hubport *hport);

static const char *speed_table[] = { "error-speed", "low-speed", "full-speed", "high-speed", "wireless-speed", "super-speed", "superplus-speed" };

#ifdef CONFIG_USBHOST_XHCI
struct usbh_hubport *usbh_get_roothub_port(unsigned int port)
{
    return &roothub.child[port - 1];
}
#endif

#if CONFIG_USBHOST_MAX_EXTHUBS > 0
static struct usbh_hub g_hub_class[CONFIG_USBHOST_MAX_EXTHUBS];
static uint32_t g_devinuse = 0;

static struct usbh_hub *usbh_hub_class_alloc(void)
{
    int devno;

    for (devno = 0; devno < CONFIG_USBHOST_MAX_EXTHUBS; devno++) {
        if ((g_devinuse & (1 << devno)) == 0) {
            g_devinuse |= (1 << devno);
            memset(&g_hub_class[devno], 0, sizeof(struct usbh_hub));
            g_hub_class[devno].index = EXTHUB_FIRST_INDEX + devno;
            return &g_hub_class[devno];
        }
    }
    return NULL;
}

static void usbh_hub_class_free(struct usbh_hub *hub_class)
{
    int devno = hub_class->index - EXTHUB_FIRST_INDEX;

    if (devno >= 0 && devno < 32) {
        g_devinuse &= ~(1 << devno);
    }
    memset(hub_class, 0, sizeof(struct usbh_hub));
}
#endif

#if CONFIG_USBHOST_MAX_EXTHUBS > 0
static int _usbh_hub_get_hub_descriptor(struct usbh_hub *hub, uint8_t *buffer)
{
    struct usb_setup_packet *setup;
    int ret;

    setup = hub->parent->setup;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = USB_REQUEST_GET_DESCRIPTOR;

    /* TODO: hub descriptor has some difference between USB 2.0 and USB 3.x,
       and we havn't handle the difference here */
    if ((hub->parent->speed == USB_SPEED_SUPER) ||
        (hub->parent->speed == USB_SPEED_SUPER_PLUS)) {
        setup->wValue = HUB_DESCRIPTOR_TYPE_HUB3 << 8;
    } else {
        setup->wValue = HUB_DESCRIPTOR_TYPE_HUB << 8;
    }

    setup->wIndex = 0;
    setup->wLength = USB_SIZEOF_HUB_DESC;

    ret = usbh_control_transfer(hub->parent, setup, g_hub_buf[hub->bus->busid]);
    if (ret < 0) {
        return ret;
    }
    memcpy(buffer, g_hub_buf[hub->bus->busid], USB_SIZEOF_HUB_DESC);
    return ret;
}
#if 0
static int _usbh_hub_get_status(struct usbh_hub *hub, uint8_t *buffer)
{
    struct usb_setup_packet *setup;
    int ret;

    setup = hub->parent->setup;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = HUB_REQUEST_GET_STATUS;
    setup->wValue = 0;
    setup->wIndex = 0;
    setup->wLength = 2;

    ret = usbh_control_transfer(hub->parent, setup, g_hub_buf[hub->bus->busid]);
    if (ret < 0) {
        return ret;
    }
    memcpy(buffer, g_hub_buf[hub->bus->busid], 2);
    return ret;
}
#endif
#endif

static int _usbh_hub_get_portstatus(struct usbh_hub *hub, uint8_t port, struct hub_port_status *port_status)
{
    struct usb_setup_packet *setup;
    int ret;

    setup = hub->parent->setup;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_OTHER;
    setup->bRequest = HUB_REQUEST_GET_STATUS;
    setup->wValue = 0;
    setup->wIndex = port;
    setup->wLength = 4;

    ret = usbh_control_transfer(hub->parent, setup, g_hub_buf[hub->bus->busid]);
    if (ret < 0) {
        return ret;
    }
    memcpy(port_status, g_hub_buf[hub->bus->busid], 4);
    return ret;
}

static int _usbh_hub_set_feature(struct usbh_hub *hub, uint8_t port, uint8_t feature)
{
    struct usb_setup_packet *setup;

    setup = hub->parent->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_OTHER;
    setup->bRequest = HUB_REQUEST_SET_FEATURE;
    setup->wValue = feature;
    setup->wIndex = port;
    setup->wLength = 0;

    return usbh_control_transfer(hub->parent, setup, NULL);
}

static int _usbh_hub_clear_feature(struct usbh_hub *hub, uint8_t port, uint8_t feature)
{
    struct usb_setup_packet *setup;

    setup = hub->parent->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_OTHER;
    setup->bRequest = HUB_REQUEST_CLEAR_FEATURE;
    setup->wValue = feature;
    setup->wIndex = port;
    setup->wLength = 0;

    return usbh_control_transfer(hub->parent, setup, NULL);
}

static int _usbh_hub_set_depth(struct usbh_hub *hub, uint16_t depth)
{
    struct usb_setup_packet *setup;

    setup = hub->parent->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = HUB_REQUEST_SET_HUB_DEPTH;
    setup->wValue = depth;
    setup->wIndex = 0;
    setup->wLength = 0;

    return usbh_control_transfer(hub->parent, setup, NULL);
}

#if CONFIG_USBHOST_MAX_EXTHUBS > 0
static int parse_hub_descriptor(struct usb_hub_descriptor *desc, uint16_t length)
{
    if (desc->bLength != USB_SIZEOF_HUB_DESC) {
        USB_LOG_ERR("invalid device bLength 0x%02x\r\n", desc->bLength);
        return -1;
    } else if (desc->bDescriptorType != HUB_DESCRIPTOR_TYPE_HUB) {
        USB_LOG_ERR("unexpected descriptor 0x%02x\r\n", desc->bDescriptorType);
        return -2;
    } else {
        USB_LOG_RAW("Hub Descriptor:\r\n");
        USB_LOG_RAW("bLength: 0x%02x             \r\n", desc->bLength);
        USB_LOG_RAW("bDescriptorType: 0x%02x     \r\n", desc->bDescriptorType);
        USB_LOG_RAW("bNbrPorts: 0x%02x           \r\n", desc->bNbrPorts);
        USB_LOG_RAW("wHubCharacteristics: 0x%04x \r\n", desc->wHubCharacteristics);
        USB_LOG_RAW("bPwrOn2PwrGood: 0x%02x      \r\n", desc->bPwrOn2PwrGood);
        USB_LOG_RAW("bHubContrCurrent: 0x%02x    \r\n", desc->bHubContrCurrent);
        USB_LOG_RAW("DeviceRemovable: 0x%02x     \r\n", desc->DeviceRemovable);
        USB_LOG_RAW("PortPwrCtrlMask: 0x%02x     \r\n", desc->PortPwrCtrlMask);
    }
    return 0;
}
#endif

static int usbh_hub_get_portstatus(struct usbh_hub *hub, uint8_t port, struct hub_port_status *port_status)
{
    struct usb_setup_packet roothub_setup;
    struct usb_setup_packet *setup;

    if (hub->is_roothub) {
        setup = &roothub_setup;
        setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_OTHER;
        setup->bRequest = HUB_REQUEST_GET_STATUS;
        setup->wValue = 0;
        setup->wIndex = port;
        setup->wLength = 4;
        return usbh_roothub_control(hub->bus, &roothub_setup, (uint8_t *)port_status);
    } else {
        return _usbh_hub_get_portstatus(hub, port, port_status);
    }
}

int usbh_hub_set_feature(struct usbh_hub *hub, uint8_t port, uint8_t feature)
{
    struct usb_setup_packet roothub_setup;
    struct usb_setup_packet *setup;

    if (hub->is_roothub) {
        setup = &roothub_setup;
        setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_OTHER;
        setup->bRequest = HUB_REQUEST_SET_FEATURE;
        setup->wValue = feature;
        setup->wIndex = port;
        setup->wLength = 0;
        return usbh_roothub_control(hub->bus, setup, NULL);
    } else {
        return _usbh_hub_set_feature(hub, port, feature);
    }
}

int usbh_hub_clear_feature(struct usbh_hub *hub, uint8_t port, uint8_t feature)
{
    struct usb_setup_packet roothub_setup;
    struct usb_setup_packet *setup;

    if (hub->is_roothub) {
        setup = &roothub_setup;
        setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_OTHER;
        setup->bRequest = HUB_REQUEST_CLEAR_FEATURE;
        setup->wValue = feature;
        setup->wIndex = port;
        setup->wLength = 0;
        return usbh_roothub_control(hub->bus, setup, NULL);
    } else {
        return _usbh_hub_clear_feature(hub, port, feature);
    }
}

static int usbh_hub_set_depth(struct usbh_hub *hub, uint16_t depth)
{
    struct usb_setup_packet roothub_setup;
    struct usb_setup_packet *setup;

    if (hub->is_roothub) {
        setup = &roothub_setup;
        setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_DEVICE;
        setup->bRequest = HUB_REQUEST_SET_HUB_DEPTH;
        setup->wValue = depth;
        setup->wIndex = 0;
        setup->wLength = 0;
        return usbh_roothub_control(hub->bus, setup, NULL);
    } else {
        return _usbh_hub_set_depth(hub, depth);
    }
}

#if CONFIG_USBHOST_MAX_EXTHUBS > 0
static void hub_int_complete_callback(void *arg, int nbytes)
{
    struct usbh_hub *hub = (struct usbh_hub *)arg;

    if (nbytes > 0) {
        usbh_hub_thread_wakeup(hub);
    } else if (nbytes == -USB_ERR_NAK) {
        /* Restart timer to submit urb again */
        USB_LOG_DBG("Restart timer\r\n");
        usb_osal_timer_start(hub->int_timer);
    } else {
    }
}

static void hub_int_timeout(void *arg)
{
    struct usbh_hub *hub = (struct usbh_hub *)arg;

    usbh_int_urb_fill(&hub->intin_urb, hub->parent, hub->intin, hub->int_buffer, 1, 0, hub_int_complete_callback, hub);
    usbh_submit_urb(&hub->intin_urb);
}

static int usbh_hub_connect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usb_endpoint_descriptor *ep_desc;
    struct hub_port_status port_status;
    int ret;

    struct usbh_hub *hub = usbh_hub_class_alloc();
    if (hub == NULL) {
        USB_LOG_ERR("Fail to alloc hub_class\r\n");
        return -USB_ERR_NOMEM;
    }

    hub->hub_addr = hport->dev_addr;
    hub->parent = hport;
    hub->bus = hport->bus;

    hport->config.intf[intf].priv = hub;

    ret = _usbh_hub_get_hub_descriptor(hub, (uint8_t *)&hub->hub_desc);
    if (ret < 0) {
        return ret;
    }

    parse_hub_descriptor(&hub->hub_desc, USB_SIZEOF_HUB_DESC);

    for (uint8_t port = 0; port < hub->hub_desc.bNbrPorts; port++) {
        hub->child[port].port = port + 1;
        hub->child[port].parent = hub;
        hub->child[port].bus = hport->bus;
    }

    ep_desc = &hport->config.intf[intf].altsetting[0].ep[0].ep_desc;
    if (ep_desc->bEndpointAddress & 0x80) {
        USBH_EP_INIT(hub->intin, ep_desc);
    } else {
        return -1;
    }

    if (hport->speed == USB_SPEED_SUPER) {
        uint16_t depth = 0;
        struct usbh_hubport *parent = hport->parent->parent;
        while (parent) {
            depth++;
            parent = parent->parent->parent;
        }

        ret = usbh_hub_set_depth(hub, depth);
        if (ret < 0) {
            return ret;
        }
    }

    for (uint8_t port = 0; port < hub->hub_desc.bNbrPorts; port++) {
        ret = usbh_hub_set_feature(hub, port + 1, HUB_PORT_FEATURE_POWER);
        if (ret < 0) {
            return ret;
        }
    }

    for (uint8_t port = 0; port < hub->hub_desc.bNbrPorts; port++) {
        ret = usbh_hub_get_portstatus(hub, port + 1, &port_status);
        USB_LOG_INFO("port %u, status:0x%02x, change:0x%02x\r\n", port + 1, port_status.wPortStatus, port_status.wPortChange);
        if (ret < 0) {
            return ret;
        }
    }

    hub->connected = true;
    snprintf(hport->config.intf[intf].devname, CONFIG_USBHOST_DEV_NAMELEN, DEV_FORMAT, hub->index);

    usb_slist_add_tail(&hub->bus->hub_list, &hub->list);

    USB_LOG_INFO("Register HUB Class:%s\r\n", hport->config.intf[intf].devname);

    hub->int_buffer = g_hub_intbuf[hub->bus->busid][hub->index - 1];

    hub->int_timer = usb_osal_timer_create("hubint_tim", USBH_GET_URB_INTERVAL(hub->intin->bInterval, hport->speed), hub_int_timeout, hub, 0);
    if (hub->int_timer == NULL) {
        USB_LOG_ERR("No memory to alloc int_timer\r\n");
        return -USB_ERR_NOMEM;
    }
    usb_osal_timer_start(hub->int_timer);
    return 0;
}

static int usbh_hub_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usbh_hubport *child;
    int ret = 0;

    struct usbh_hub *hub = (struct usbh_hub *)hport->config.intf[intf].priv;

    if (hub) {
        if (hub->intin) {
            usbh_kill_urb(&hub->intin_urb);
        }

        if (hub->int_timer) {
            usb_osal_timer_delete(hub->int_timer);
        }

        for (uint8_t port = 0; port < hub->hub_desc.bNbrPorts; port++) {
            child = &hub->child[port];
            usbh_hubport_release(child);
            child->parent = NULL;
        }

        if (hport->config.intf[intf].devname[0] != '\0') {
            USB_LOG_INFO("Unregister HUB Class:%s\r\n", hport->config.intf[intf].devname);
            usb_slist_remove(&hub->bus->hub_list, &hub->list);
        }

        usbh_hub_class_free(hub);
    }
    return ret;
}
#endif

static void usbh_hubport_enumerate_thread(void *argument)
{
    struct usbh_hubport *child = (struct usbh_hubport *)argument;

    if (usbh_enumerate(child) < 0) {
        /** release child sources */
        usbh_hubport_release(child);
        USB_LOG_ERR("Port %u enumerate fail\r\n", child->port);
    }
    usb_osal_thread_delete(NULL);
}

static void usbh_hub_events(struct usbh_hub *hub)
{
    struct usbh_hubport *child;
    struct hub_port_status port_status;
    uint8_t portchange_index;
    uint16_t portstatus;
    uint16_t portchange;
    uint16_t mask;
    uint16_t feat;
    uint8_t speed;
    int ret;

    if (!hub->connected) {
        return;
    }

    portchange_index = hub->int_buffer[0];
    hub->int_buffer[0] &= ~portchange_index;

    for (uint8_t port = 0; port < hub->hub_desc.bNbrPorts; port++) {
        USB_LOG_DBG("Port change:0x%02x\r\n", portchange_index);

        if (!(portchange_index & (1 << (port + 1)))) {
            continue;
        }
        portchange_index &= ~(1 << (port + 1));
        USB_LOG_DBG("Port %d change\r\n", port + 1);

        /* Read hub port status */
        ret = usbh_hub_get_portstatus(hub, port + 1, &port_status);
        if (ret < 0) {
            USB_LOG_ERR("Failed to read port %u status, errorcode: %d\r\n", port + 1, ret);
            continue;
        }

        portstatus = port_status.wPortStatus;
        portchange = port_status.wPortChange;

        USB_LOG_DBG("port %u, status:0x%02x, change:0x%02x\r\n", port + 1, portstatus, portchange);

        /* First, clear all change bits */
        mask = 1;
        feat = HUB_PORT_FEATURE_C_CONNECTION;
        while (portchange) {
            if (portchange & mask) {
                ret = usbh_hub_clear_feature(hub, port + 1, feat);
                if (ret < 0) {
                    USB_LOG_ERR("Failed to clear port %u, change mask:%04x, errorcode:%d\r\n", port + 1, mask, ret);
                    continue;
                }
                portchange &= (~mask);
            }
            mask <<= 1;
            feat++;
        }

        portchange = port_status.wPortChange;

        /* Second, if port changes, debounces first */
        if (portchange & HUB_PORT_STATUS_C_CONNECTION) {
            uint16_t connection = 0;
            uint16_t debouncestable = 0;
            for (uint32_t debouncetime = 0; debouncetime < HUB_DEBOUNCE_TIMEOUT; debouncetime += HUB_DEBOUNCE_STEP) {
                /* Read hub port status */
                ret = usbh_hub_get_portstatus(hub, port + 1, &port_status);
                if (ret < 0) {
                    USB_LOG_ERR("Failed to read port %u status, errorcode: %d\r\n", port + 1, ret);
                    continue;
                }

                portstatus = port_status.wPortStatus;
                portchange = port_status.wPortChange;

                USB_LOG_DBG("Port %u, status:0x%02x, change:0x%02x\r\n", port + 1, portstatus, portchange);

                if (!(portchange & HUB_PORT_STATUS_C_CONNECTION) &&
                    ((portstatus & HUB_PORT_STATUS_CONNECTION) == connection)) {
                    debouncestable += HUB_DEBOUNCE_STEP;
                    if (debouncestable >= HUB_DEBOUNCE_STABLE) {
                        break;
                    }
                } else {
                    debouncestable = 0;
                    connection = portstatus & HUB_PORT_STATUS_CONNECTION;
                }

                if (portchange & HUB_PORT_STATUS_C_CONNECTION) {
                    usbh_hub_clear_feature(hub, port + 1, HUB_PORT_FEATURE_C_CONNECTION);
                }

                usb_osal_msleep(HUB_DEBOUNCE_STEP);
            }

            /** check if debounce ok */
            if (debouncestable < HUB_DEBOUNCE_STABLE) {
                USB_LOG_ERR("Failed to debounce port %u\r\n", port + 1);
                break;
            }

            /* Last, check connect status */
            if (portstatus & HUB_PORT_STATUS_CONNECTION) {
                ret = usbh_hub_set_feature(hub, port + 1, HUB_PORT_FEATURE_RESET);
                if (ret < 0) {
                    USB_LOG_ERR("Failed to reset port %u,errorcode:%d\r\n", port, ret);
                    continue;
                }

                usb_osal_msleep(DELAY_TIME_AFTER_RESET);
                /* Read hub port status */
                ret = usbh_hub_get_portstatus(hub, port + 1, &port_status);
                if (ret < 0) {
                    USB_LOG_ERR("Failed to read port %u status, errorcode: %d\r\n", port + 1, ret);
                    continue;
                }

                portstatus = port_status.wPortStatus;
                portchange = port_status.wPortChange;
                if (!(portstatus & HUB_PORT_STATUS_RESET) && (portstatus & HUB_PORT_STATUS_ENABLE)) {
                    if (portchange & HUB_PORT_STATUS_C_RESET) {
                        ret = usbh_hub_clear_feature(hub, port + 1, HUB_PORT_FEATURE_C_RESET);
                        if (ret < 0) {
                            USB_LOG_ERR("Failed to clear port %u reset change, errorcode: %d\r\n", port, ret);
                        }
                    }

                    if (portstatus & HUB_PORT_STATUS_HIGH_SPEED) {
                        speed = USB_SPEED_HIGH;
                    } else if (portstatus & HUB_PORT_STATUS_LOW_SPEED) {
                        speed = USB_SPEED_LOW;
                    }
#ifdef CONFIG_USBHOST_XHCI
                    else {
                        extern uint8_t usbh_get_port_speed(struct usbh_hub * hub, const uint8_t port);

                        /* USB3.0 speed cannot get from portstatus, checkout port speed instead */
                        uint8_t super_speed = usbh_get_port_speed(hub, port + 1);
                        if (super_speed > USB_SPEED_HIGH) {
                            /* assert that when using USB 3.0 ports, attached device must also be USB 3.0 speed */
                            speed = super_speed;
                        } else {
                            speed = USB_SPEED_FULL;
                        }
                    }
#else
                    else {
                        speed = USB_SPEED_FULL;
                    }
#endif

                    child = &hub->child[port];
                    /** release child sources first */
                    usbh_hubport_release(child);

                    memset(child, 0, sizeof(struct usbh_hubport));
                    child->parent = hub;
                    child->connected = true;
                    child->port = port + 1;
                    child->speed = speed;
                    child->bus = hub->bus;
                    child->mutex = usb_osal_mutex_create();

                    USB_LOG_INFO("New %s device on Bus %u, Hub %u, Port %u connected\r\n", speed_table[speed], hub->bus->busid, hub->index, port + 1);

                    /* create disposable thread to enumerate device on current hport, do not block hub thread */
                    usb_osal_thread_create("usbh_enum", CONFIG_USBHOST_PSC_STACKSIZE, CONFIG_USBHOST_PSC_PRIO + 1, usbh_hubport_enumerate_thread, (void *)child);
                } else {
                    child = &hub->child[port];
                    /** release child sources */
                    usbh_hubport_release(child);

                    /** some USB 3.0 ip may failed to enable USB 2.0 port for USB 3.0 device */
                    USB_LOG_WRN("Failed to enable port %u\r\n", port + 1);

                    continue;
                }
            } else {
                child = &hub->child[port];
                /** release child sources */
                usbh_hubport_release(child);
                USB_LOG_INFO("Device on Bus %u, Hub %u, Port %u disconnected\r\n", hub->bus->busid, hub->index, port + 1);
            }
        }
    }

    /* Start next hub int transfer */
    if (!hub->is_roothub && hub->connected) {
        usb_osal_timer_start(hub->int_timer);
    }
}

static void usbh_hub_thread(void *argument)
{
    struct usbh_hub *hub;
    int ret = 0;

    struct usbh_bus *bus = (struct usbh_bus *)argument;

    usb_hc_init(bus);
    while (1) {
        ret = usb_osal_mq_recv(bus->hub_mq, (uintptr_t *)&hub, USB_OSAL_WAITING_FOREVER);
        if (ret < 0) {
            continue;
        }
        usbh_hub_events(hub);
    }
}

void usbh_hub_thread_wakeup(struct usbh_hub *hub)
{
    usb_osal_mq_send(hub->bus->hub_mq, (uintptr_t)hub);
}

int usbh_hub_initialize(struct usbh_bus *bus)
{
    char thread_name[32] = { 0 };

    bus->hub_mq = usb_osal_mq_create(7);
    if (bus->hub_mq == NULL) {
        USB_LOG_ERR("Failed to create hub mq\r\n");
        return -1;
    }

    snprintf(thread_name, 32, "usbh_hub%u", bus->busid);
    bus->hub_thread = usb_osal_thread_create(thread_name, CONFIG_USBHOST_PSC_STACKSIZE, CONFIG_USBHOST_PSC_PRIO, usbh_hub_thread, bus);
    if (bus->hub_thread == NULL) {
        USB_LOG_ERR("Failed to create hub thread\r\n");
        return -1;
    }
    return 0;
}

int usbh_hub_deinitialize(struct usbh_bus *bus)
{
    usb_slist_t *hub_list;
    struct usbh_hubport *hport;
    size_t flags;

    flags = usb_osal_enter_critical_section();

    usb_slist_for_each(hub_list, &bus->hub_list)
    {
        struct usbh_hub *hub = usb_slist_entry(hub_list, struct usbh_hub, list);

        for (uint8_t port = 0; port < hub->hub_desc.bNbrPorts; port++) {
            hport = &hub->child[port];

            usbh_hubport_release(hport);
        }
    }

    usb_hc_deinit(bus);

    usb_osal_leave_critical_section(flags);

    usb_osal_mq_delete(bus->hub_mq);
    usb_osal_thread_delete(bus->hub_thread);

    return 0;
}

#if CONFIG_USBHOST_MAX_EXTHUBS > 0
const struct usbh_class_driver hub_class_driver = {
    .driver_name = "hub",
    .connect = usbh_hub_connect,
    .disconnect = usbh_hub_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info hub_class_info = {
    .match_flags = USB_CLASS_MATCH_INTF_CLASS,
    .class = USB_DEVICE_CLASS_HUB,
    .subclass = 0,
    .protocol = 0,
    .id_table = NULL,
    .class_driver = &hub_class_driver
};
#endif
