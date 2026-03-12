/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_core"
#include "usb_log.h"

struct usbh_class_info *usbh_class_info_table_begin = NULL;
struct usbh_class_info *usbh_class_info_table_end = NULL;

usb_slist_t g_bus_head = USB_SLIST_OBJECT_INIT(g_bus_head);

struct setup_align_buffer {
    uint8_t buffer[USB_ALIGN_UP(8, CONFIG_USB_ALIGN_SIZE)];
};

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t ep0_request_buffer[CONFIG_USBHOST_MAX_BUS][USB_ALIGN_UP(CONFIG_USBHOST_REQUEST_BUFFER_LEN, CONFIG_USB_ALIGN_SIZE)];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX struct setup_align_buffer g_setup_buffer[CONFIG_USBHOST_MAX_BUS][CONFIG_USBHOST_MAX_EXTHUBS + 1][CONFIG_USBHOST_MAX_EHPORTS];

struct usbh_bus g_usbhost_bus[CONFIG_USBHOST_MAX_BUS];

/* general descriptor field offsets */
#define DESC_bLength         0 /** Length offset */
#define DESC_bDescriptorType 1 /** Descriptor type offset */

#define USB_DEV_ADDR_MAX         0x7f
#define USB_DEV_ADDR_MARK_OFFSET 5
#define USB_DEV_ADDR_MARK_MASK   0x1f

static void dummy_event_handler(uint8_t busid, uint8_t hub_index, uint8_t hub_port, uint8_t intf, uint8_t event)
{
    (void)busid;
    (void)hub_index;
    (void)hub_port;
    (void)intf;
    (void)event;
}

static int usbh_allocate_devaddr(struct usbh_devaddr_map *devgen)
{
    uint8_t lastaddr = devgen->last;
    uint8_t devaddr = lastaddr;
    int index;
    int bitno;

    for (;;) {
        devaddr++;
        if (devaddr > 0x7f) {
            devaddr = 2;
        }
        if (devaddr == lastaddr) {
            return -USB_ERR_NOMEM;
        }

        index = devaddr >> 5;
        bitno = devaddr & 0x1f;
        if ((devgen->alloctab[index] & (1ul << bitno)) == 0) {
            devgen->alloctab[index] |= (1ul << bitno);
            devgen->last = devaddr;
            return (int)devaddr;
        }
    }
}

static int __usbh_free_devaddr(struct usbh_devaddr_map *devgen, uint8_t devaddr)
{
    int index;
    int bitno;

    if ((devaddr > 0) && (devaddr < USB_DEV_ADDR_MAX)) {
        index = devaddr >> USB_DEV_ADDR_MARK_OFFSET;
        bitno = devaddr & USB_DEV_ADDR_MARK_MASK;

        /* Free the address  */
        if ((devgen->alloctab[index] & (1ul << bitno)) != 0) {
            devgen->alloctab[index] &= ~(1ul << bitno);
        } else {
            return -1;
        }
    }

    return 0;
}

static int usbh_free_devaddr(struct usbh_hubport *hport)
{
    if (hport->dev_addr > 0) {
        __usbh_free_devaddr(&hport->bus->devgen, hport->dev_addr);
    }
    return 0;
}

static const struct usbh_class_driver *usbh_find_class_driver(uint8_t class, uint8_t subclass, uint8_t protocol, uint8_t intf,
                                                              uint16_t vid, uint16_t pid)
{
    struct usbh_class_info *index = NULL;

    for (index = usbh_class_info_table_begin; index < usbh_class_info_table_end; index++) {
        if ((index->match_flags & USB_CLASS_MATCH_INTF_CLASS) && !(index->bInterfaceClass == class)) {
            continue;
        }
        if ((index->match_flags & USB_CLASS_MATCH_INTF_SUBCLASS) && !(index->bInterfaceSubClass == subclass)) {
            continue;
        }
        if ((index->match_flags & USB_CLASS_MATCH_INTF_PROTOCOL) && !(index->bInterfaceProtocol == protocol)) {
            continue;
        }
        if ((index->match_flags & USB_CLASS_MATCH_INTF_NUM) && !(index->bInterfaceNumber == intf)) {
            continue;
        }
        if (index->match_flags & USB_CLASS_MATCH_VID_PID && index->id_table) {
            /* scan id table */
            uint32_t i;
            for (i = 0; index->id_table[i][0]; i++) {
                if (index->id_table[i][0] == vid && index->id_table[i][1] == pid) {
                    break;
                }
            }
            /* do not match, continue next */
            if (!index->id_table[i][0]) {
                continue;
            }
        }
        return index->class_driver;
    }
    return NULL;
}

static int parse_device_descriptor(struct usbh_hubport *hport, struct usb_device_descriptor *desc, uint16_t length)
{
    if (desc->bLength != USB_SIZEOF_DEVICE_DESC) {
        USB_LOG_ERR("invalid device bLength 0x%02x\r\n", desc->bLength);
        return -USB_ERR_INVAL;
    } else if (desc->bDescriptorType != USB_DESCRIPTOR_TYPE_DEVICE) {
        USB_LOG_ERR("unexpected device descriptor 0x%02x\r\n", desc->bDescriptorType);
        return -USB_ERR_INVAL;
    } else {
        if (length <= 8) {
            return 0;
        }
#if 0
        USB_LOG_DBG("Device Descriptor:\r\n");
        USB_LOG_DBG("bLength: 0x%02x           \r\n", desc->bLength);
        USB_LOG_DBG("bDescriptorType: 0x%02x   \r\n", desc->bDescriptorType);
        USB_LOG_DBG("bcdUSB: 0x%04x            \r\n", desc->bcdUSB);
        USB_LOG_DBG("bDeviceClass: 0x%02x      \r\n", desc->bDeviceClass);
        USB_LOG_DBG("bDeviceSubClass: 0x%02x   \r\n", desc->bDeviceSubClass);
        USB_LOG_DBG("bDeviceProtocol: 0x%02x   \r\n", desc->bDeviceProtocol);
        USB_LOG_DBG("bMaxPacketSize0: 0x%02x   \r\n", desc->bMaxPacketSize0);
        USB_LOG_DBG("idVendor: 0x%04x          \r\n", desc->idVendor);
        USB_LOG_DBG("idProduct: 0x%04x         \r\n", desc->idProduct);
        USB_LOG_DBG("bcdDevice: 0x%04x         \r\n", desc->bcdDevice);
        USB_LOG_DBG("iManufacturer: 0x%02x     \r\n", desc->iManufacturer);
        USB_LOG_DBG("iProduct: 0x%02x          \r\n", desc->iProduct);
        USB_LOG_DBG("iSerialNumber: 0x%02x     \r\n", desc->iSerialNumber);
        USB_LOG_DBG("bNumConfigurations: 0x%02x\r\n", desc->bNumConfigurations);
#endif
        hport->device_desc.bLength = desc->bLength;
        hport->device_desc.bDescriptorType = desc->bDescriptorType;
        hport->device_desc.bcdUSB = desc->bcdUSB;
        hport->device_desc.bDeviceClass = desc->bDeviceClass;
        hport->device_desc.bDeviceSubClass = desc->bDeviceSubClass;
        hport->device_desc.bDeviceProtocol = desc->bDeviceProtocol;
        hport->device_desc.bMaxPacketSize0 = desc->bMaxPacketSize0;
        hport->device_desc.idVendor = desc->idVendor;
        hport->device_desc.idProduct = desc->idProduct;
        hport->device_desc.bcdDevice = desc->bcdDevice;
        hport->device_desc.iManufacturer = desc->iManufacturer;
        hport->device_desc.iProduct = desc->iProduct;
        hport->device_desc.iSerialNumber = desc->iSerialNumber;
        hport->device_desc.bNumConfigurations = desc->bNumConfigurations;
    }
    return 0;
}

static int parse_config_descriptor(struct usbh_hubport *hport, struct usb_configuration_descriptor *desc, uint16_t length)
{
    struct usb_interface_descriptor *intf_desc;
    struct usb_endpoint_descriptor *ep_desc;
    uint8_t cur_alt_setting = 0xff;
    uint8_t cur_iface = 0xff;
    uint8_t cur_ep = 0xff;
    uint8_t cur_ep_num = 0xff;
    uint32_t desc_len = 0;
    uint8_t *p;

    if (desc->bLength != USB_SIZEOF_CONFIG_DESC) {
        USB_LOG_ERR("invalid config bLength 0x%02x\r\n", desc->bLength);
        return -USB_ERR_INVAL;
    } else if (desc->bDescriptorType != USB_DESCRIPTOR_TYPE_CONFIGURATION) {
        USB_LOG_ERR("unexpected config descriptor 0x%02x\r\n", desc->bDescriptorType);
        return -USB_ERR_INVAL;
    } else {
        if (length <= USB_SIZEOF_CONFIG_DESC) {
            return 0;
        }
#if 0
        USB_LOG_DBG("Config Descriptor:\r\n");
        USB_LOG_DBG("bLength: 0x%02x             \r\n", desc->bLength);
        USB_LOG_DBG("bDescriptorType: 0x%02x     \r\n", desc->bDescriptorType);
        USB_LOG_DBG("wTotalLength: 0x%04x        \r\n", desc->wTotalLength);
        USB_LOG_DBG("bNumInterfaces: 0x%02x      \r\n", desc->bNumInterfaces);
        USB_LOG_DBG("bConfigurationValue: 0x%02x \r\n", desc->bConfigurationValue);
        USB_LOG_DBG("iConfiguration: 0x%02x      \r\n", desc->iConfiguration);
        USB_LOG_DBG("bmAttributes: 0x%02x        \r\n", desc->bmAttributes);
        USB_LOG_DBG("bMaxPower: 0x%02x           \r\n", desc->bMaxPower);
#endif
        hport->config.config_desc.bLength = desc->bLength;
        hport->config.config_desc.bDescriptorType = desc->bDescriptorType;
        hport->config.config_desc.wTotalLength = desc->wTotalLength;
        hport->config.config_desc.bNumInterfaces = desc->bNumInterfaces;
        hport->config.config_desc.bConfigurationValue = desc->bConfigurationValue;
        hport->config.config_desc.iConfiguration = desc->iConfiguration;
        hport->config.config_desc.iConfiguration = desc->iConfiguration;
        hport->config.config_desc.bmAttributes = desc->bmAttributes;
        hport->config.config_desc.bMaxPower = desc->bMaxPower;

        p = (uint8_t *)desc;
        p += USB_SIZEOF_CONFIG_DESC;
        desc_len = USB_SIZEOF_CONFIG_DESC;

        memset(hport->config.intf, 0, sizeof(struct usbh_interface) * CONFIG_USBHOST_MAX_INTERFACES);

        while (p[DESC_bLength] && (desc_len <= length)) {
            switch (p[DESC_bDescriptorType]) {
                case USB_DESCRIPTOR_TYPE_INTERFACE:
                    intf_desc = (struct usb_interface_descriptor *)p;
                    cur_iface = intf_desc->bInterfaceNumber;
                    cur_alt_setting = intf_desc->bAlternateSetting;
                    cur_ep_num = intf_desc->bNumEndpoints;
                    cur_ep = 0;

                    if (cur_iface >= CONFIG_USBHOST_MAX_INTERFACES) {
                        USB_LOG_ERR("Interface num %d overflow\r\n", cur_iface);
                        return -USB_ERR_NOMEM;
                    }

                    if (cur_ep_num >= CONFIG_USBHOST_MAX_ENDPOINTS) {
                        USB_LOG_ERR("Endpoint num %d overflow\r\n", cur_ep_num);
                        return -USB_ERR_NOMEM;
                    }

                    if (cur_alt_setting >= CONFIG_USBHOST_MAX_INTF_ALTSETTINGS) {
                        USB_LOG_ERR("Interface altsetting num %d overflow\r\n", cur_alt_setting);
                        return -USB_ERR_NOMEM;
                    }

#if 0
                    USB_LOG_DBG("Interface Descriptor:\r\n");
                    USB_LOG_DBG("bLength: 0x%02x            \r\n", intf_desc->bLength);
                    USB_LOG_DBG("bDescriptorType: 0x%02x    \r\n", intf_desc->bDescriptorType);
                    USB_LOG_DBG("bInterfaceNumber: 0x%02x   \r\n", intf_desc->bInterfaceNumber);
                    USB_LOG_DBG("bAlternateSetting: 0x%02x  \r\n", intf_desc->bAlternateSetting);
                    USB_LOG_DBG("bNumEndpoints: 0x%02x      \r\n", intf_desc->bNumEndpoints);
                    USB_LOG_DBG("bInterfaceClass: 0x%02x    \r\n", intf_desc->bInterfaceClass);
                    USB_LOG_DBG("bInterfaceSubClass: 0x%02x \r\n", intf_desc->bInterfaceSubClass);
                    USB_LOG_DBG("bInterfaceProtocol: 0x%02x \r\n", intf_desc->bInterfaceProtocol);
                    USB_LOG_DBG("iInterface: 0x%02x         \r\n", intf_desc->iInterface);
#endif
                    memcpy(&hport->config.intf[cur_iface].altsetting[cur_alt_setting].intf_desc, intf_desc, 9);
                    hport->config.intf[cur_iface].altsetting_num = cur_alt_setting + 1;
                    break;
                case USB_DESCRIPTOR_TYPE_ENDPOINT:
                    ep_desc = (struct usb_endpoint_descriptor *)p;
                    memcpy(&hport->config.intf[cur_iface].altsetting[cur_alt_setting].ep[cur_ep].ep_desc, ep_desc, 7);
                    cur_ep++;
                    break;

                default:
                    break;
            }
            /* skip to next descriptor */
            p += p[DESC_bLength];
            desc_len += p[DESC_bLength];
        }
    }
    return 0;
}

static void usbh_print_setup(struct usb_setup_packet *setup)
{
    (void)setup;

    USB_LOG_DBG("Setup: "
                "bmRequestType 0x%02x, bRequest 0x%02x, wValue 0x%04x, wIndex 0x%04x, wLength 0x%04x\r\n",
                setup->bmRequestType,
                setup->bRequest,
                setup->wValue,
                setup->wIndex,
                setup->wLength);
}

static int usbh_get_default_mps(int speed)
{
    switch (speed) {
        case USB_SPEED_LOW: /* For low speed, we use 8 bytes */
            return 8;
        case USB_SPEED_FULL: /* For full or high speed, we use 64 bytes */
        case USB_SPEED_HIGH:
            return 64;
        case USB_SPEED_SUPER: /* For super speed , we must use 512 bytes */
        case USB_SPEED_SUPER_PLUS:
            return 512;
        default:
            return 64;
    }
}

int usbh_enumerate(struct usbh_hubport *hport)
{
    struct usb_interface_descriptor *intf_desc;
    struct usb_setup_packet *setup;
    struct usb_device_descriptor *dev_desc;
    struct usb_endpoint_descriptor *ep;
    int dev_addr;
    uint16_t ep_mps;
    uint8_t config_value;
    uint8_t config_index;
    int ret;

    hport->setup = (struct usb_setup_packet *)&g_setup_buffer[hport->bus->busid][hport->parent->index - 1][hport->port - 1];
    setup = hport->setup;
    ep = &hport->ep0;

    /* Config EP0 mps from speed */
    ep->bEndpointAddress = 0x00;
    ep->bDescriptorType = USB_DESCRIPTOR_TYPE_ENDPOINT;
    ep->bmAttributes = USB_ENDPOINT_TYPE_CONTROL;
    ep->wMaxPacketSize = usbh_get_default_mps(hport->speed);
    ep->bInterval = 0;
    ep->bLength = 7;

    /* Configure EP0 with zero address */
    hport->dev_addr = 0;

    /* Read the first 8 bytes of the device descriptor */
    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_STANDARD | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = USB_REQUEST_GET_DESCRIPTOR;
    setup->wValue = (uint16_t)((USB_DESCRIPTOR_TYPE_DEVICE << 8) | 0);
    setup->wIndex = 0;
    setup->wLength = 8;

    ret = usbh_control_transfer(hport, setup, ep0_request_buffer[hport->bus->busid]);
    if (ret < 0) {
        USB_LOG_ERR("Failed to get device descriptor,errorcode:%d\r\n", ret);
        goto errout;
    }

    ret = parse_device_descriptor(hport, (struct usb_device_descriptor *)ep0_request_buffer[hport->bus->busid], 8);
    if (ret < 0) {
        USB_LOG_ERR("Parse device descriptor fail\r\n");
        goto errout;
    }

    /* Extract the correct max packetsize from the device descriptor */
    dev_desc = (struct usb_device_descriptor *)ep0_request_buffer[hport->bus->busid];
    if (dev_desc->bcdUSB >= USB_3_0) {
        ep_mps = 1 << dev_desc->bMaxPacketSize0;
    } else {
        ep_mps = dev_desc->bMaxPacketSize0;
    }

    USB_LOG_DBG("Device rev=%04x cls=%02x sub=%02x proto=%02x size=%d\r\n",
                dev_desc->bcdUSB, dev_desc->bDeviceClass, dev_desc->bDeviceSubClass,
                dev_desc->bDeviceProtocol, ep_mps);

    /* Reconfigure EP0 with the correct maximum packet size */
    ep->wMaxPacketSize = ep_mps;

    /* Assign a function address to the device connected to this port */
    dev_addr = usbh_allocate_devaddr(&hport->bus->devgen);
    if (dev_addr < 0) {
        USB_LOG_ERR("Failed to allocate devaddr,errorcode:%d\r\n", ret);
        goto errout;
    }

    /* Set the USB device address */
    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_STANDARD | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = USB_REQUEST_SET_ADDRESS;
    setup->wValue = dev_addr;
    setup->wIndex = 0;
    setup->wLength = 0;

    ret = usbh_control_transfer(hport, setup, NULL);
    if (ret < 0) {
        USB_LOG_ERR("Failed to set devaddr,errorcode:%d\r\n", ret);
        goto errout;
    }

    /* Wait device set address completely */
    usb_osal_msleep(10);

    /*Reconfigure EP0 with the correct address */
    hport->dev_addr = dev_addr;

    /* Read the full device descriptor */
    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_STANDARD | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = USB_REQUEST_GET_DESCRIPTOR;
    setup->wValue = (uint16_t)((USB_DESCRIPTOR_TYPE_DEVICE << 8) | 0);
    setup->wIndex = 0;
    setup->wLength = USB_SIZEOF_DEVICE_DESC;

    ret = usbh_control_transfer(hport, setup, ep0_request_buffer[hport->bus->busid]);
    if (ret < 0) {
        USB_LOG_ERR("Failed to get full device descriptor,errorcode:%d\r\n", ret);
        goto errout;
    }

    parse_device_descriptor(hport, (struct usb_device_descriptor *)ep0_request_buffer[hport->bus->busid], USB_SIZEOF_DEVICE_DESC);
    USB_LOG_INFO("New device found,idVendor:%04x,idProduct:%04x,bcdDevice:%04x\r\n",
                 ((struct usb_device_descriptor *)ep0_request_buffer[hport->bus->busid])->idVendor,
                 ((struct usb_device_descriptor *)ep0_request_buffer[hport->bus->busid])->idProduct,
                 ((struct usb_device_descriptor *)ep0_request_buffer[hport->bus->busid])->bcdDevice);

    USB_LOG_INFO("The device has %d bNumConfigurations\r\n", ((struct usb_device_descriptor *)ep0_request_buffer[hport->bus->busid])->bNumConfigurations);

    config_index = usbh_get_hport_active_config_index(hport);
    USB_LOG_DBG("The device selects config %d\r\n", config_index);

    /* Read the first 9 bytes of the config descriptor */
    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_STANDARD | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = USB_REQUEST_GET_DESCRIPTOR;
    setup->wValue = (uint16_t)((USB_DESCRIPTOR_TYPE_CONFIGURATION << 8) | config_index);
    setup->wIndex = 0;
    setup->wLength = USB_SIZEOF_CONFIG_DESC;

    ret = usbh_control_transfer(hport, setup, ep0_request_buffer[hport->bus->busid]);
    if (ret < 0) {
        USB_LOG_ERR("Failed to get config descriptor,errorcode:%d\r\n", ret);
        goto errout;
    }

    ret = parse_config_descriptor(hport, (struct usb_configuration_descriptor *)ep0_request_buffer[hport->bus->busid], USB_SIZEOF_CONFIG_DESC);
    if (ret < 0) {
        USB_LOG_ERR("Parse config descriptor fail\r\n");
        goto errout;
    }

    /* Read the full size of the configuration data */
    uint16_t wTotalLength = ((struct usb_configuration_descriptor *)ep0_request_buffer[hport->bus->busid])->wTotalLength;

    if (wTotalLength > CONFIG_USBHOST_REQUEST_BUFFER_LEN) {
        ret = -USB_ERR_NOMEM;
        USB_LOG_ERR("wTotalLength %d is overflow, default is %d\r\n", wTotalLength, (unsigned int)CONFIG_USBHOST_REQUEST_BUFFER_LEN);
        goto errout;
    }

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_STANDARD | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = USB_REQUEST_GET_DESCRIPTOR;
    setup->wValue = (uint16_t)((USB_DESCRIPTOR_TYPE_CONFIGURATION << 8) | config_index);
    setup->wIndex = 0;
    setup->wLength = wTotalLength;

    ret = usbh_control_transfer(hport, setup, ep0_request_buffer[hport->bus->busid]);
    if (ret < 0) {
        USB_LOG_ERR("Failed to get full config descriptor,errorcode:%d\r\n", ret);
        goto errout;
    }

    ret = parse_config_descriptor(hport, (struct usb_configuration_descriptor *)ep0_request_buffer[hport->bus->busid], wTotalLength);
    if (ret < 0) {
        USB_LOG_ERR("Parse config descriptor fail\r\n");
        goto errout;
    }

    USB_LOG_INFO("The device has %d interfaces\r\n", ((struct usb_configuration_descriptor *)ep0_request_buffer[hport->bus->busid])->bNumInterfaces);
    hport->raw_config_desc = usb_osal_malloc(wTotalLength + 1);
    if (hport->raw_config_desc == NULL) {
        ret = -USB_ERR_NOMEM;
        USB_LOG_ERR("No memory to alloc for raw_config_desc\r\n");
        goto errout;
    }

    config_value = ((struct usb_configuration_descriptor *)ep0_request_buffer[hport->bus->busid])->bConfigurationValue;
    memcpy(hport->raw_config_desc, ep0_request_buffer[hport->bus->busid], wTotalLength);
    hport->raw_config_desc[wTotalLength] = '\0';

#ifdef CONFIG_USBHOST_GET_STRING_DESC
    uint8_t string_buffer[128];

    if (hport->device_desc.iManufacturer > 0) {
        /* Get Manufacturer string */
        memset(string_buffer, 0, 128);
        ret = usbh_get_string_desc(hport, USB_STRING_MFC_INDEX, string_buffer, 128);
        if (ret < 0) {
            USB_LOG_ERR("Failed to get Manufacturer string,errorcode:%d\r\n", ret);
            goto errout;
        }

        USB_LOG_INFO("Manufacturer: %s\r\n", string_buffer);
    } else {
        USB_LOG_WRN("Do not support Manufacturer string\r\n");
    }

    if (hport->device_desc.iProduct > 0) {
        /* Get Product string */
        memset(string_buffer, 0, 128);
        ret = usbh_get_string_desc(hport, USB_STRING_PRODUCT_INDEX, string_buffer, 128);
        if (ret < 0) {
            USB_LOG_ERR("Failed to get Product string,errorcode:%d\r\n", ret);
            goto errout;
        }

        USB_LOG_INFO("Product: %s\r\n", string_buffer);
    } else {
        USB_LOG_WRN("Do not support Product string\r\n");
    }

    if (hport->device_desc.iSerialNumber > 0) {
        /* Get SerialNumber string */
        memset(string_buffer, 0, 128);
        ret = usbh_get_string_desc(hport, USB_STRING_SERIAL_INDEX, string_buffer, 128);
        if (ret < 0) {
            USB_LOG_ERR("Failed to get SerialNumber string,errorcode:%d\r\n", ret);
            goto errout;
        }

        USB_LOG_INFO("SerialNumber: %s\r\n", string_buffer);
    } else {
        USB_LOG_WRN("Do not support SerialNumber string\r\n");
    }
#endif
    /* Select device configuration 1 */
    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_STANDARD | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = USB_REQUEST_SET_CONFIGURATION;
    setup->wValue = config_value;
    setup->wIndex = 0;
    setup->wLength = 0;

    ret = usbh_control_transfer(hport, setup, NULL);
    if (ret < 0) {
        USB_LOG_ERR("Failed to set configuration,errorcode:%d\r\n", ret);
        goto errout;
    }

#ifdef CONFIG_USBHOST_MSOS_ENABLE
    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_VENDOR | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = CONFIG_USBHOST_MSOS_VENDOR_CODE;
    setup->wValue = 0;
    setup->wIndex = 0x0004;
    setup->wLength = 16;

    ret = usbh_control_transfer(hport, setup, ep0_request_buffer[hport->bus->busid]);
    if (ret < 0 && (ret != -USB_ERR_STALL)) {
        USB_LOG_ERR("Failed to get msosv1 compat id,errorcode:%d\r\n", ret);
        goto errout;
    }
#endif
    USB_LOG_INFO("Enumeration success, start loading class driver\r\n");
    hport->bus->event_handler(hport->bus->busid, hport->parent->index, hport->port, USB_INTERFACE_ANY, USBH_EVENT_DEVICE_CONFIGURED);
    /*search supported class driver*/
    for (uint8_t i = 0; i < hport->config.config_desc.bNumInterfaces; i++) {
        intf_desc = &hport->config.intf[i].altsetting[0].intf_desc;

        USB_ASSERT_MSG(intf_desc->bInterfaceNumber == i, "Interface number mismatch, do not support non-standard device\r\n");

        struct usbh_class_driver *class_driver = (struct usbh_class_driver *)usbh_find_class_driver(intf_desc->bInterfaceClass,
                                                                                                    intf_desc->bInterfaceSubClass,
                                                                                                    intf_desc->bInterfaceProtocol,
                                                                                                    intf_desc->bInterfaceNumber,
                                                                                                    hport->device_desc.idVendor,
                                                                                                    hport->device_desc.idProduct);

        if (class_driver == NULL) {
            USB_LOG_ERR("Do not support Class:0x%02x, Subclass:0x%02x, Protocl:0x%02x on interface %u\r\n",
                        intf_desc->bInterfaceClass,
                        intf_desc->bInterfaceSubClass,
                        intf_desc->bInterfaceProtocol,
                        i);
            hport->bus->event_handler(hport->bus->busid, hport->parent->index, hport->port, i, USBH_EVENT_INTERFACE_UNSUPPORTED);
            continue;
        }
        hport->config.intf[i].class_driver = class_driver;
        USB_LOG_INFO("Loading %s class driver on interface %u\r\n", class_driver->driver_name, i);
        ret = CLASS_CONNECT(hport, i);
        if (ret >= 0) {
            hport->bus->event_handler(hport->bus->busid, hport->parent->index, hport->port, i, USBH_EVENT_INTERFACE_START);
        }
    }

errout:
    if (hport->raw_config_desc) {
        usb_osal_free(hport->raw_config_desc);
        hport->raw_config_desc = NULL;
    }
    return ret;
}

void usbh_hubport_release(struct usbh_hubport *hport)
{
    if (hport->connected) {
        hport->connected = false;
        usbh_kill_urb(&hport->ep0_urb);
        usbh_free_devaddr(hport);
        for (uint8_t i = 0; i < hport->config.config_desc.bNumInterfaces; i++) {
            if (hport->config.intf[i].class_driver && hport->config.intf[i].class_driver->disconnect) {
                CLASS_DISCONNECT(hport, i);
            }
            hport->bus->event_handler(hport->bus->busid, hport->parent->index, hport->port, i, USBH_EVENT_INTERFACE_STOP);
        }
        hport->config.config_desc.bNumInterfaces = 0;
        if (hport->mutex) {
            usb_osal_mutex_delete(hport->mutex);
        }
        USB_LOG_INFO("Device on Bus %u, Hub %u, Port %u disconnected\r\n", hport->bus->busid, hport->parent->index, hport->port);
        hport->bus->event_handler(hport->bus->busid, hport->parent->index, hport->port, USB_INTERFACE_ANY, USBH_EVENT_DEVICE_DISCONNECTED);
    }
}

static void usbh_bus_init(struct usbh_bus *bus, uint8_t busid, uintptr_t reg_base)
{
    memset(bus, 0, sizeof(struct usbh_bus));
    bus->busid = busid;
    bus->hcd.hcd_id = busid;
    bus->hcd.reg_base = reg_base;

    /* devaddr 1 is for roothub */
    bus->devgen.last = 0x7f;

    usb_slist_add_tail(&g_bus_head, &bus->list);
}

int usbh_initialize(uint8_t busid, uintptr_t reg_base, usbh_event_handler_t event_handler)
{
    struct usbh_bus *bus;

    USB_ASSERT_MSG(busid < CONFIG_USBHOST_MAX_BUS, "bus overflow\r\n");

    bus = &g_usbhost_bus[busid];

    usbh_bus_init(bus, busid, reg_base);

    if (event_handler) {
        bus->event_handler = event_handler;
    } else {
        bus->event_handler = dummy_event_handler;
    }

#ifdef __ARMCC_VERSION /* ARM C Compiler */
    extern const int usbh_class_info$$Base;
    extern const int usbh_class_info$$Limit;
    usbh_class_info_table_begin = (struct usbh_class_info *)&usbh_class_info$$Base;
    usbh_class_info_table_end = (struct usbh_class_info *)&usbh_class_info$$Limit;
#elif defined(__GNUC__)
    extern uint32_t __usbh_class_info_start__;
    extern uint32_t __usbh_class_info_end__;
    usbh_class_info_table_begin = (struct usbh_class_info *)&__usbh_class_info_start__;
    usbh_class_info_table_end = (struct usbh_class_info *)&__usbh_class_info_end__;
#elif defined(__ICCARM__) || defined(__ICCRX__) || defined(__ICCRISCV__)
    usbh_class_info_table_begin = (struct usbh_class_info *)__section_begin(".usbh_class_info");
    usbh_class_info_table_end = (struct usbh_class_info *)__section_end(".usbh_class_info");
#endif
    usbh_hub_initialize(bus);
    return 0;
}

int usbh_deinitialize(uint8_t busid)
{
    struct usbh_bus *bus;

    USB_ASSERT_MSG(busid < CONFIG_USBHOST_MAX_BUS, "bus overflow\r\n");

    bus = &g_usbhost_bus[busid];

    bus->event_handler(bus->busid, USB_HUB_INDEX_ANY, USB_HUB_PORT_ANY, USB_INTERFACE_ANY, USBH_EVENT_DEINIT);

    usbh_hub_deinitialize(bus);

    usb_slist_remove(&g_bus_head, &bus->list);

    return 0;
}

int usbh_control_transfer(struct usbh_hubport *hport, struct usb_setup_packet *setup, uint8_t *buffer)
{
    struct usbh_urb *urb;
    volatile uint8_t retry = 3;
    int ret;

    if (!hport || !setup) {
        return -USB_ERR_INVAL;
    }

    urb = &hport->ep0_urb;

    usb_osal_mutex_take(hport->mutex);

    usbh_print_setup(setup);

resubmit:
    usbh_control_urb_fill(urb, hport, setup, buffer, setup->wLength, CONFIG_USBHOST_CONTROL_TRANSFER_TIMEOUT, NULL, NULL);
    ret = usbh_submit_urb(urb);
    if (ret == 0) {
        ret = urb->actual_length;
    }

    if (ret < 0 && (ret != -USB_ERR_TIMEOUT)) {
        retry--;
        if (retry > 0) {
            USB_LOG_WRN("Control transfer failed, errorcode %d, retrying...\r\n", ret);
            goto resubmit;
        }
    }

    usb_osal_mutex_give(hport->mutex);
    return ret;
}

int usbh_get_string_desc(struct usbh_hubport *hport, uint8_t index, uint8_t *output, uint16_t output_len)
{
    struct usb_setup_packet *setup = hport->setup;
    int ret;
    uint8_t *src;
    uint8_t *dst;
    uint16_t len;
    uint16_t i = 2;
    uint16_t j = 0;

    /* Get Manufacturer string */
    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_STANDARD | USB_REQUEST_RECIPIENT_DEVICE;
    setup->bRequest = USB_REQUEST_GET_DESCRIPTOR;
    setup->wValue = (uint16_t)((USB_DESCRIPTOR_TYPE_STRING << 8) | index);
    setup->wIndex = 0x0409;
    setup->wLength = 255;

    ret = usbh_control_transfer(hport, setup, ep0_request_buffer[hport->bus->busid]);
    if (ret < 0) {
        return ret;
    }

    src = ep0_request_buffer[hport->bus->busid];
    dst = output;
    len = src[0];

    if (((len - 2) / 2) > output_len) {
        return -USB_ERR_NOMEM;
    }

    while (i < len) {
        dst[j] = src[i];
        i += 2;
        j++;
    }

    return 0;
}

int usbh_set_interface(struct usbh_hubport *hport, uint8_t intf, uint8_t altsetting)
{
    struct usb_setup_packet *setup = hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_STANDARD | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = USB_REQUEST_SET_INTERFACE;
    setup->wValue = altsetting;
    setup->wIndex = intf;
    setup->wLength = 0;

    return usbh_control_transfer(hport, setup, NULL);
}

static void *usbh_list_all_interface_name(struct usbh_hub *hub, const char *devname)
{
    struct usbh_hubport *hport;
    struct usbh_hub *hub_next;
    void *priv;

    for (uint8_t port = 0; port < hub->nports; port++) {
        hport = &hub->child[port];
        if (hport->connected) {
            for (uint8_t itf = 0; itf < hport->config.config_desc.bNumInterfaces; itf++) {
                if (hport->config.intf[itf].class_driver && hport->config.intf[itf].class_driver->driver_name) {
                    if ((strncmp(hport->config.intf[itf].devname, devname, CONFIG_USBHOST_DEV_NAMELEN) == 0) && hport->config.intf[itf].priv)
                        return hport->config.intf[itf].priv;

                    if (strcmp(hport->config.intf[itf].class_driver->driver_name, "hub") == 0) {
                        hub_next = hport->config.intf[itf].priv;

                        if (hub_next && hub_next->connected) {
                            priv = usbh_list_all_interface_name(hub_next, devname);
                            if (priv) {
                                return priv;
                            }
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

static struct usbh_hubport *usbh_list_all_hubport(struct usbh_hub *hub, uint8_t hub_index, uint8_t hub_port)
{
    struct usbh_hubport *hport;
    struct usbh_hub *hub_next;

    if (hub->index == hub_index) {
        hport = &hub->child[hub_port - 1];
        if (hport->connected) {
            return hport;
        } else {
            return NULL;
        }
    } else {
        for (uint8_t port = 0; port < hub->nports; port++) {
            hport = &hub->child[port];
            if (hport->connected) {
                for (uint8_t itf = 0; itf < hport->config.config_desc.bNumInterfaces; itf++) {
                    if (hport->config.intf[itf].class_driver && hport->config.intf[itf].class_driver->driver_name) {
                        if (strcmp(hport->config.intf[itf].class_driver->driver_name, "hub") == 0) {
                            hub_next = hport->config.intf[itf].priv;

                            if (hub_next && hub_next->connected) {
                                hport = usbh_list_all_hubport(hub_next, hub_index, hub_port);
                                if (hport) {
                                    return hport;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

void *usbh_find_class_instance(const char *devname)
{
    usb_slist_t *bus_list;
    struct usbh_hub *hub;
    struct usbh_bus *bus;
    void *priv;
    size_t flags;

    flags = usb_osal_enter_critical_section();
    usb_slist_for_each(bus_list, &g_bus_head)
    {
        bus = usb_slist_entry(bus_list, struct usbh_bus, list);
        hub = &bus->hcd.roothub;

        priv = usbh_list_all_interface_name(hub, devname);
        if (priv) {
            usb_osal_leave_critical_section(flags);
            return priv;
        }
    }
    usb_osal_leave_critical_section(flags);
    return NULL;
}

struct usbh_hubport *usbh_find_hubport(uint8_t busid, uint8_t hub_index, uint8_t hub_port)
{
    struct usbh_hub *hub;
    struct usbh_bus *bus;
    struct usbh_hubport *hport;
    size_t flags;

    flags = usb_osal_enter_critical_section();

    bus = &g_usbhost_bus[busid];
    hub = &bus->hcd.roothub;

    hport = usbh_list_all_hubport(hub, hub_index, hub_port);
    usb_osal_leave_critical_section(flags);
    return hport;
}

static void usbh_print_hubport_info(struct usbh_hubport *hport)
{
    USB_LOG_RAW("Device Descriptor:\r\n");
    USB_LOG_RAW("  bLength: 0x%02x           \r\n", hport->device_desc.bLength);
    USB_LOG_RAW("  bDescriptorType: 0x%02x   \r\n", hport->device_desc.bDescriptorType);
    USB_LOG_RAW("  bcdUSB: 0x%04x            \r\n", hport->device_desc.bcdUSB);
    USB_LOG_RAW("  bDeviceClass: 0x%02x      \r\n", hport->device_desc.bDeviceClass);
    USB_LOG_RAW("  bDeviceSubClass: 0x%02x   \r\n", hport->device_desc.bDeviceSubClass);
    USB_LOG_RAW("  bDeviceProtocol: 0x%02x   \r\n", hport->device_desc.bDeviceProtocol);
    USB_LOG_RAW("  bMaxPacketSize0: 0x%02x   \r\n", hport->device_desc.bMaxPacketSize0);
    USB_LOG_RAW("  idVendor: 0x%04x          \r\n", hport->device_desc.idVendor);
    USB_LOG_RAW("  idProduct: 0x%04x         \r\n", hport->device_desc.idProduct);
    USB_LOG_RAW("  bcdDevice: 0x%04x         \r\n", hport->device_desc.bcdDevice);
    USB_LOG_RAW("  iManufacturer: 0x%02x     \r\n", hport->device_desc.iManufacturer);
    USB_LOG_RAW("  iProduct: 0x%02x          \r\n", hport->device_desc.iProduct);
    USB_LOG_RAW("  iSerialNumber: 0x%02x     \r\n", hport->device_desc.iSerialNumber);
    USB_LOG_RAW("  bNumConfigurations: 0x%02x\r\n", hport->device_desc.bNumConfigurations);

    USB_LOG_RAW("  Config Descriptor:\r\n");
    USB_LOG_RAW("    bLength: 0x%02x             \r\n", hport->config.config_desc.bLength);
    USB_LOG_RAW("    bDescriptorType: 0x%02x     \r\n", hport->config.config_desc.bDescriptorType);
    USB_LOG_RAW("    wTotalLength: 0x%04x        \r\n", hport->config.config_desc.wTotalLength);
    USB_LOG_RAW("    bNumInterfaces: 0x%02x      \r\n", hport->config.config_desc.bNumInterfaces);
    USB_LOG_RAW("    bConfigurationValue: 0x%02x \r\n", hport->config.config_desc.bConfigurationValue);
    USB_LOG_RAW("    iConfiguration: 0x%02x      \r\n", hport->config.config_desc.iConfiguration);
    USB_LOG_RAW("    bmAttributes: 0x%02x        \r\n", hport->config.config_desc.bmAttributes);
    USB_LOG_RAW("    bMaxPower: 0x%02x           \r\n", hport->config.config_desc.bMaxPower);

    for (uint8_t i = 0; i < hport->config.config_desc.bNumInterfaces; i++) {
        for (uint8_t j = 0; j < hport->config.intf[i].altsetting_num; j++) {
            USB_LOG_RAW("    Interface Descriptor:\r\n");
            USB_LOG_RAW("      bLength: 0x%02x            \r\n", hport->config.intf[i].altsetting[j].intf_desc.bLength);
            USB_LOG_RAW("      bDescriptorType: 0x%02x    \r\n", hport->config.intf[i].altsetting[j].intf_desc.bDescriptorType);
            USB_LOG_RAW("      bInterfaceNumber: 0x%02x   \r\n", hport->config.intf[i].altsetting[j].intf_desc.bInterfaceNumber);
            USB_LOG_RAW("      bAlternateSetting: 0x%02x  \r\n", hport->config.intf[i].altsetting[j].intf_desc.bAlternateSetting);
            USB_LOG_RAW("      bNumEndpoints: 0x%02x      \r\n", hport->config.intf[i].altsetting[j].intf_desc.bNumEndpoints);
            USB_LOG_RAW("      bInterfaceClass: 0x%02x    \r\n", hport->config.intf[i].altsetting[j].intf_desc.bInterfaceClass);
            USB_LOG_RAW("      bInterfaceSubClass: 0x%02x \r\n", hport->config.intf[i].altsetting[j].intf_desc.bInterfaceSubClass);
            USB_LOG_RAW("      bInterfaceProtocol: 0x%02x \r\n", hport->config.intf[i].altsetting[j].intf_desc.bInterfaceProtocol);
            USB_LOG_RAW("      iInterface: 0x%02x         \r\n", hport->config.intf[i].altsetting[j].intf_desc.iInterface);

            for (uint8_t k = 0; k < hport->config.intf[i].altsetting[j].intf_desc.bNumEndpoints; k++) {
                USB_LOG_RAW("      Endpoint Descriptor:\r\n");
                USB_LOG_RAW("        bLength: 0x%02x          \r\n", hport->config.intf[i].altsetting[j].ep[k].ep_desc.bLength);
                USB_LOG_RAW("        bDescriptorType: 0x%02x  \r\n", hport->config.intf[i].altsetting[j].ep[k].ep_desc.bDescriptorType);
                USB_LOG_RAW("        bEndpointAddress: 0x%02x \r\n", hport->config.intf[i].altsetting[j].ep[k].ep_desc.bEndpointAddress);
                USB_LOG_RAW("        bmAttributes: 0x%02x     \r\n", hport->config.intf[i].altsetting[j].ep[k].ep_desc.bmAttributes);
                USB_LOG_RAW("        wMaxPacketSize: 0x%04x   \r\n", hport->config.intf[i].altsetting[j].ep[k].ep_desc.wMaxPacketSize);
                USB_LOG_RAW("        bInterval: 0x%02x        \r\n", hport->config.intf[i].altsetting[j].ep[k].ep_desc.bInterval);
            }
        }
    }
}

static void usbh_list_device(struct usbh_hub *hub, bool astree, bool verbose, int dev_addr, int vid, int pid)
{
    static const char *speed_table[] = {
        "UNKNOWN",
        "low-speed",
        "full-speed",
        "high-speed",
        "wireless",
        "super-speed",
        "super-speed-plus",
    };

    static const char *root_speed_table[] = {
        "UNKNOWN",
        "1.1",
        "1.1",
        "2.0",
        "2.5",
        "3.0",
        "3.0",
    };

    static const uint16_t speed_baud[] = {
        0,
        12,
        12,
        480,
        480,
        5000,
        10000,
    };

    struct usbh_bus *bus;
    struct usbh_hubport *hport;
    struct usbh_hub *hub_next;

    uint8_t imbuf[64];
    uint8_t ipbuf[64];

    const char *pimstr;
    const char *pipstr;

    bool imvalid = false;
    bool ipvalid = false;

    int ret;

    bus = hub->bus;

    (void)speed_table;

    if (hub->is_roothub) {
        if (astree) {
            USB_LOG_RAW("/:  Bus %02u.Port 1: Dev %u, Class=root_hub, Driver=hcd, %uM\r\n",
                        bus->busid, hub->hub_addr, speed_baud[hub->speed]);

        } else {
            if ((dev_addr < 0) || (hub->hub_addr == dev_addr)) {
                if (((vid < 0) || (vid == 0xffff)) && ((pid < 0) || (pid == 0xffff))) {
                    USB_LOG_RAW("Bus %03u Device %03u: ID %04x:%04x %s %s root hub\r\n",
                                bus->busid, hub->hub_addr, 0xffff, 0xffff,
                                "Cherry-Embedded", root_speed_table[hub->speed]);
                }
            }
        }
    }

    for (uint8_t port = 0; port < hub->nports; port++) {
        hport = &hub->child[port];
        if (hport->connected) {
            ret = 0;
            if (hport->device_desc.iManufacturer) {
                memset(imbuf, 0, sizeof(imbuf));
                ret = usbh_get_string_desc(hport, hport->device_desc.iManufacturer, imbuf, sizeof(imbuf));
                if (ret == 0) {
                    imvalid = true;
                }
            }

            if (hport->device_desc.iProduct) {
                memset(ipbuf, 0, sizeof(ipbuf));
                ret = usbh_get_string_desc(hport, hport->device_desc.iProduct, ipbuf, sizeof(ipbuf));
                if (ret == 0) {
                    ipvalid = true;
                }
            }

            if (imvalid) {
                pimstr = (const char *)imbuf;
            } else {
                pimstr = "Not specified Manufacturer";
            }

            if (ipvalid) {
                pipstr = (const char *)ipbuf;
            } else {
                pipstr = "Not specified Product";
            }

            if (!astree) {
                if ((dev_addr < 0) || (hport->dev_addr == dev_addr)) {
                    if (((vid < 0) || (vid == hport->device_desc.idVendor)) && ((pid < 0) || (pid == hport->device_desc.idProduct))) {
                        USB_LOG_RAW("Bus %03u Device %03u: ID %04x:%04x %s %s\r\n",
                                    bus->busid, hport->dev_addr, hport->device_desc.idVendor, hport->device_desc.idProduct,
                                    pimstr, pipstr);

                        if (verbose) {
                            usbh_print_hubport_info(hport);
                        }
                    }
                }
            }

            for (uint8_t intf = 0; intf < hport->config.config_desc.bNumInterfaces; intf++) {
                if (hport->config.intf[intf].class_driver && hport->config.intf[intf].class_driver->driver_name) {
                    if (astree) {
                        for (uint8_t j = 0; j < hub->index; j++) {
                            USB_LOG_RAW("    ");
                        }

                        USB_LOG_RAW("|__ Port %u: Dev %u, If %u, ClassDriver=%s, %uM\r\n",
                                    hport->port, hport->dev_addr, intf, hport->config.intf[intf].class_driver->driver_name, speed_baud[hport->speed]);
                    }

                    if (!strcmp(hport->config.intf[intf].class_driver->driver_name, "hub")) {
                        hub_next = hport->config.intf[intf].priv;

                        if (hub_next && hub_next->connected) {
                            usbh_list_device(hub_next, astree, verbose, dev_addr, vid, pid);
                        }
                    }
                } else if (astree) {
                    for (uint8_t j = 0; j < hub->index; j++) {
                        USB_LOG_RAW("    ");
                    }

                    USB_LOG_RAW("|__ Port %u: Dev %u, If 0 ClassDriver=none, %uM\r\n",
                                hport->port, hport->dev_addr, speed_baud[hport->speed]);
                }
            }
        }
    }
}

void lsusb_help(void)
{
    USB_LOG_RAW("List USB Devices\r\n"
                "Usage: lsusb [options]...\r\n"
                "\r\n"
                "-v, --verbose\r\n"
                "    - increase verbosity (show descriptors)\r\n"
                "-s [[bus]:][dev_addr]\r\n"
                "    - show only devices with specified device and/or\r\n"
                "      bus numbers (in decimal)\r\n"
                "-d vendor:[product]\r\n"
                "    - show only devices with the specified vendor and\r\n"
                "      product ID numbers (in hexadecimal)\r\n"
                "-t, --tree\r\n"
                "    - dump the physical USB device hierarchy as a tree\r\n"
                "-V, --version\r\n"
                "    - show version of the cherryusb\r\n"
                "-h, --help\r\n"
                "    - show usage and help information\r\n");
}

int lsusb(int argc, char **argv)
{
    usb_slist_t *bus_list;
    struct usbh_bus *bus;

    int busid = -1;
    int dev_addr = -1;
    int vid = -1;
    int pid = -1;
    bool astree = false;
    bool verbose = false;

    if (argc < 2) {
        lsusb_help();
        return 0;
    }

    while (argc > 1) {
        argc--;
        argv++;

        if (!strcmp(*argv, "-V") || !strcmp(*argv, "--version")) {
            USB_LOG_RAW("CherryUSB version %s\r\n", CHERRYUSB_VERSION_STR);
            return 0;
        } else if (!strcmp(*argv, "-h") || !strcmp(*argv, "--help")) {
            lsusb_help();
            return 0;
        } else if (!strcmp(*argv, "-v") || !strcmp(*argv, "--verbose")) {
            verbose = true;
        } else if (!strcmp(*argv, "-t") || !strcmp(*argv, "--tree")) {
            astree = true;
        } else if (!strcmp(*argv, "-s")) {
            if (argc > 1) {
                argc--;
                argv++;

                if (*argv[0] == '-') {
                    continue;
                }

                char *endptr;
                const char *colon = strchr(*argv, ':');
                (void)endptr;

                if (colon != NULL) {
                    const char *str;
                    if (colon > *argv) {
                        busid = strtol(*argv, &endptr, 10);
                    }
                    str = colon + 1;
                    if (*str != '\0') {
                        dev_addr = strtol(str, &endptr, 10);
                        if (dev_addr <= 0 || dev_addr >= 128) {
                            dev_addr = -1;
                        }
                    }
                } else {
                    dev_addr = strtol(*argv, &endptr, 10);
                    if (dev_addr <= 0 || dev_addr >= 128) {
                        dev_addr = -1;
                    }
                }
            }
        } else if (!strcmp(*argv, "-d")) {
            if (argc > 1) {
                argc--;
                argv++;

                if (*argv[0] == '-') {
                    continue;
                }

                char *endptr;
                const char *colon = strchr(*argv, ':');
                (void)endptr;

                if (colon == NULL) {
                    continue;
                }
                const char *str;

                vid = strtol(*argv, &endptr, 16);
                if (vid < 0 || vid > 0xffff) {
                    vid = -1;
                    continue;
                }
                str = colon + 1;
                if (*str != '\0') {
                    pid = strtol(str, &endptr, 16);
                    if (pid < 0 || pid > 0xffff) {
                        pid = -1;
                    }
                }
            }
        }
    }

    if (astree) {
        busid = -1;
        dev_addr = -1;
        vid = -1;
        pid = -1;
        verbose = false;
    }

    usb_slist_for_each(bus_list, &g_bus_head)
    {
        bus = usb_slist_entry(bus_list, struct usbh_bus, list);
        if (busid >= 0) {
            if (bus->busid != busid) {
                continue;
            }
        }

        usbh_list_device(&bus->hcd.roothub, astree, verbose, dev_addr, vid, pid);
    }

    return 0;
}

__WEAK uint8_t usbh_get_hport_active_config_index(struct usbh_hubport *hport)
{
    ARG_UNUSED(hport);

    return 0; // Default to configuration index 0
}