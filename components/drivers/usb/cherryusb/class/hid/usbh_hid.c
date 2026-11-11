/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_hid.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_hid"
#include "usb_log.h"

#define DEV_FORMAT "/dev/input%d"

/* general descriptor field offsets */
#define DESC_bLength         0 /** Length offset */
#define DESC_bDescriptorType 1 /** Descriptor type offset */

/* interface descriptor field offsets */
#define INTF_DESC_bInterfaceNumber  2 /** Interface number offset */
#define INTF_DESC_bAlternateSetting 3 /** Alternate setting offset */

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_hid_buf[CONFIG_USBHOST_MAX_HID_CLASS][USB_ALIGN_UP(32, CONFIG_USB_ALIGN_SIZE)];

static struct usbh_hid g_hid_class[CONFIG_USBHOST_MAX_HID_CLASS];
static uint32_t g_devinuse = 0;

static struct usbh_hid *usbh_hid_class_alloc(void)
{
    uint8_t devno;

    for (devno = 0; devno < CONFIG_USBHOST_MAX_HID_CLASS; devno++) {
        if ((g_devinuse & (1U << devno)) == 0) {
            g_devinuse |= (1U << devno);
            memset(&g_hid_class[devno], 0, sizeof(struct usbh_hid));
            g_hid_class[devno].minor = devno;
            return &g_hid_class[devno];
        }
    }
    return NULL;
}

static void usbh_hid_class_free(struct usbh_hid *hid_class)
{
    uint8_t devno = hid_class->minor;

    if (devno < 32) {
        g_devinuse &= ~(1U << devno);
    }
    memset(hid_class, 0, sizeof(struct usbh_hid));
}

int usbh_hid_get_report_descriptor(struct usbh_hid *hid_class, uint8_t *buffer, uint32_t buflen)
{
    struct usb_setup_packet *setup;

    if (!hid_class || !hid_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = hid_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_STANDARD | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = USB_REQUEST_GET_DESCRIPTOR;
    setup->wValue = HID_DESCRIPTOR_TYPE_HID_REPORT << 8;
    setup->wIndex = hid_class->intf;
    setup->wLength = buflen;

    return usbh_control_transfer(hid_class->hport, setup, buffer);
}

int usbh_hid_set_idle(struct usbh_hid *hid_class, uint8_t report_id, uint8_t duration)
{
    struct usb_setup_packet *setup;

    if (!hid_class || !hid_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = hid_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = HID_REQUEST_SET_IDLE;
    setup->wValue = (duration << 8) | report_id;
    setup->wIndex = hid_class->intf;
    setup->wLength = 0;

    return usbh_control_transfer(hid_class->hport, setup, NULL);
}

int usbh_hid_get_idle(struct usbh_hid *hid_class, uint8_t *buffer)
{
    struct usb_setup_packet *setup;
    int ret;

    if (!hid_class || !hid_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = hid_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = HID_REQUEST_GET_IDLE;
    setup->wValue = 0;
    setup->wIndex = hid_class->intf;
    setup->wLength = 1;

    ret = usbh_control_transfer(hid_class->hport, setup, g_hid_buf[hid_class->minor]);
    if (ret < 8) {
        return ret;
    }
    memcpy(buffer, g_hid_buf[hid_class->minor], MIN((uint32_t)ret - 8, 1));
    return ret;
}

int usbh_hid_set_protocol(struct usbh_hid *hid_class, uint8_t protocol)
{
    struct usb_setup_packet *setup;

    if (!hid_class || !hid_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = hid_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = HID_REQUEST_SET_PROTOCOL;
    setup->wValue = protocol;
    setup->wIndex = 0;
    setup->wLength = 0;

    return usbh_control_transfer(hid_class->hport, setup, NULL);
}

int usbh_hid_get_protocol(struct usbh_hid *hid_class, uint8_t *protocol)
{
    struct usb_setup_packet *setup;
    int ret;

    if (!hid_class || !hid_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = hid_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = HID_REQUEST_GET_PROTOCOL;
    setup->wValue = 0;
    setup->wIndex = hid_class->intf;
    setup->wLength = 1;

    ret = usbh_control_transfer(hid_class->hport, setup, g_hid_buf[hid_class->minor]);
    if (ret < 8) {
        return ret;
    }
    memcpy(protocol, g_hid_buf[hid_class->minor], MIN((uint32_t)ret - 8, 1));
    return ret;
}

int usbh_hid_set_report(struct usbh_hid *hid_class, uint8_t report_type, uint8_t report_id, uint8_t *buffer, uint32_t buflen)
{
    struct usb_setup_packet *setup;

    if (!hid_class || !hid_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = hid_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_OUT | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = HID_REQUEST_SET_REPORT;
    setup->wValue = (uint16_t)(((uint32_t)report_type << 8U) | (uint32_t)report_id);
    setup->wIndex = 0;
    setup->wLength = buflen;

    return usbh_control_transfer(hid_class->hport, setup, buffer);
}

int usbh_hid_get_report(struct usbh_hid *hid_class, uint8_t report_type, uint8_t report_id, uint8_t *buffer, uint32_t buflen)
{
    struct usb_setup_packet *setup;

    if (!hid_class || !hid_class->hport) {
        return -USB_ERR_INVAL;
    }
    setup = hid_class->hport->setup;

    setup->bmRequestType = USB_REQUEST_DIR_IN | USB_REQUEST_CLASS | USB_REQUEST_RECIPIENT_INTERFACE;
    setup->bRequest = HID_REQUEST_GET_REPORT;
    setup->wValue = (uint16_t)(((uint32_t)report_type << 8U) | (uint32_t)report_id);
    setup->wIndex = 0;
    setup->wLength = buflen;

    return usbh_control_transfer(hid_class->hport, setup, buffer);
}

int usbh_hid_connect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usb_endpoint_descriptor *ep_desc;
    uint8_t cur_iface = 0xff;
    uint8_t *p;
    bool found = false;

    struct usbh_hid *hid_class = usbh_hid_class_alloc();
    if (hid_class == NULL) {
        USB_LOG_ERR("Fail to alloc hid_class\r\n");
        return -USB_ERR_NOMEM;
    }

    hid_class->hport = hport;
    hid_class->intf = intf;

    hport->config.intf[intf].priv = hid_class;

    p = hport->raw_config_desc;
    while (p[DESC_bLength]) {
        switch (p[DESC_bDescriptorType]) {
            case USB_DESCRIPTOR_TYPE_INTERFACE:
                cur_iface = p[INTF_DESC_bInterfaceNumber];
                if (cur_iface == intf) {
                    hid_class->protocol = p[7];
                    struct usb_hid_descriptor *desc = (struct usb_hid_descriptor *)(p + 9);

                    if (desc->bDescriptorType != HID_DESCRIPTOR_TYPE_HID) {
                        USB_LOG_ERR("HID descriptor not found\r\n");
                        return -USB_ERR_INVAL;
                    }

                    if (desc->subdesc[0].bDescriptorType != HID_DESCRIPTOR_TYPE_HID_REPORT) {
                        USB_LOG_ERR("HID report descriptor not found\r\n");
                        return -USB_ERR_INVAL;
                    }

                    hid_class->report_size = desc->subdesc[0].wDescriptorLength;
                    found = true;
                    goto found;
                }
                break;
            default:
                break;
        }
        /* skip to next descriptor */
        p += p[DESC_bLength];
    }

    if (found == false) {
        USB_LOG_ERR("HID interface not found\r\n");
        return -USB_ERR_INVAL;
    }
found:
    for (uint8_t i = 0; i < hport->config.intf[intf].altsetting[0].intf_desc.bNumEndpoints; i++) {
        ep_desc = &hport->config.intf[intf].altsetting[0].ep[i].ep_desc;
        if (ep_desc->bEndpointAddress & 0x80) {
            USBH_EP_INIT(hid_class->intin, ep_desc);
        } else {
            USBH_EP_INIT(hid_class->intout, ep_desc);
        }
    }

    snprintf(hport->config.intf[intf].devname, CONFIG_USBHOST_DEV_NAMELEN, DEV_FORMAT, hid_class->minor);

    USB_LOG_INFO("Register HID Class:%s\r\n", hport->config.intf[intf].devname);

    usbh_hid_run(hid_class);
    return 0;
}

int usbh_hid_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    int ret = 0;

    struct usbh_hid *hid_class = (struct usbh_hid *)hport->config.intf[intf].priv;

    if (hid_class) {
        if (hid_class->intin) {
            usbh_kill_urb(&hid_class->intin_urb);
        }

        if (hid_class->intout) {
            usbh_kill_urb(&hid_class->intout_urb);
        }

        if (hport->config.intf[intf].devname[0] != '\0') {
            usb_osal_thread_schedule_other();
            USB_LOG_INFO("Unregister HID Class:%s\r\n", hport->config.intf[intf].devname);
            usbh_hid_stop(hid_class);
        }

        usbh_hid_class_free(hid_class);
    }

    return ret;
}

static uint32_t hid_get_itemval(const uint8_t *data, unsigned int idx, unsigned int size)
{
    uint32_t value = 0;

    for (unsigned int i = 1; i <= size; i++)
        value |= data[idx + i] << (8 * (i - 1));

    return value;
}

int usbh_hid_parse_report_descriptor(const uint8_t *report_data, uint32_t report_size, struct usbh_hid_report_info *report_info)
{
    struct usbh_hid_report_item_attribute current_item_attr = { 0 };
    struct usbh_hid_report_item *current_item = NULL;
    uint32_t itemtag, itemtype, itemsize, itemval;
    uint16_t temp_usage;
    uint32_t total_report_size[3] = { 0 }; /* input, output, feature */
    uint32_t i = 0;

    memset(report_info, 0, sizeof(struct usbh_hid_report_info));
    memset(&current_item_attr, 0, sizeof(struct usbh_hid_report_item_attribute));
    current_item_attr.usage_min = 0xffff;
    current_item_attr.usage_max = 0;

    while (i < report_size) {
        itemtag = report_data[i] & HID_TAG_MASK;
        itemtype = report_data[i] & HID_TYPE_MASK;
        itemsize = report_data[i] & HID_SIZE_MASK;

        if (itemsize == 3) /* HID spec: 6.2.2.2 - Short Items */
            itemsize = 4;

        itemval = hid_get_itemval(report_data, i, itemsize);

        USB_LOG_DBG("itemtype 0x%02x, itemtag 0x%02x, itemsize %d, itemval 0x%08x\r\n",
                    itemtype, itemtag, itemsize, itemval);

        switch (itemtype) {
            case HID_ITEMTYPE_MAIN:
                switch (itemtag) {
                    case HID_MAINITEM_TAG_INPUT:
                    case HID_MAINITEM_TAG_OUTPUT:
                    case HID_MAINITEM_TAG_FEATURE:
                        if (report_info->report_item_count == CONFIG_USB_HID_MAX_REPORT_ITEMS) {
                            goto err;
                        }

                        current_item = &report_info->report_items[report_info->report_item_count];
                        current_item->report_flags = itemval;

                        if (itemtag == HID_MAINITEM_TAG_INPUT) {
                            current_item->report_type = HID_REPORT_INPUT;
                        } else if (itemtag == HID_MAINITEM_TAG_OUTPUT) {
                            current_item->report_type = HID_REPORT_OUTPUT;
                        } else {
                            current_item->report_type = HID_REPORT_FEATURE;
                        }

                        current_item->report_bit_offset = total_report_size[current_item->report_type - 1];
                        total_report_size[current_item->report_type - 1] += current_item_attr.report_size * current_item_attr.report_count;

                        memcpy(&current_item->attribute, &current_item_attr, sizeof(struct usbh_hid_report_item_attribute));
                        report_info->report_item_count++;

                        // reset for next item
                        current_item_attr.usage_min = 0xffff;
                        current_item_attr.usage_max = 0;
                        break;
                    case HID_MAINITEM_TAG_COLLECTION:
                        // reset for next item
                        current_item_attr.usage_min = 0xffff;
                        current_item_attr.usage_max = 0;
                        break;
                    case HID_MAINITEM_TAG_ENDCOLLECTION:
                        break;
                    default:
                        goto err;
                }
                break;
            case HID_ITEMTYPE_GLOBAL:
                switch (itemtag) {
                    case HID_GLOBALITEM_TAG_USAGE_PAGE:
                        current_item_attr.usage_page = (uint16_t)itemval;
                        break;
                    case HID_GLOBALITEM_TAG_LOGICAL_MIN:
                        current_item_attr.logical_min = itemval;
                        break;
                    case HID_GLOBALITEM_TAG_LOGICAL_MAX:
                        current_item_attr.logical_max = itemval;
                        break;
                    case HID_GLOBALITEM_TAG_PHYSICAL_MIN:
                        current_item_attr.physical_min = itemval;
                        break;
                    case HID_GLOBALITEM_TAG_PHYSICAL_MAX:
                        current_item_attr.physical_max = itemval;
                        break;
                    case HID_GLOBALITEM_TAG_UNIT_EXP:
                        current_item_attr.unit_exponent = itemval;
                        break;
                    case HID_GLOBALITEM_TAG_UNIT:
                        current_item_attr.unit = itemval;
                        break;
                    case HID_GLOBALITEM_TAG_REPORT_SIZE:
                        current_item_attr.report_size = itemval;
                        break;
                    case HID_GLOBALITEM_TAG_REPORT_COUNT:
                        current_item_attr.report_count = itemval;
                        break;
                    case HID_GLOBALITEM_TAG_REPORT_ID:
                        current_item_attr.report_id = itemval;
                        break;
                    default:
                        goto err;
                }
                break;
            case HID_ITEMTYPE_LOCAL:
                switch (itemtag) {
                    case HID_LOCALITEM_TAG_USAGE:
                        if (itemsize == 4) {
                            temp_usage = (uint16_t)(itemval >> 16);
                        } else {
                            temp_usage = (uint16_t)itemval;
                        }
                        current_item_attr.usage_min = MIN(current_item_attr.usage_min, temp_usage);
                        current_item_attr.usage_max = MAX(current_item_attr.usage_max, temp_usage);

                        break;
                    case HID_LOCALITEM_TAG_USAGE_MIN:
                        current_item_attr.usage_min = (uint16_t)itemval;
                        break;
                    case HID_LOCALITEM_TAG_USAGE_MAX:
                        current_item_attr.usage_max = (uint16_t)itemval;
                        break;
                    default:
                        goto err;
                }
                break;
            default:
                goto err;
        }

        i += (1 + itemsize);
    }

    return 0;
err:
    return -1;
}

int usbh_hid_report_convert(struct usbh_hid_report_item *item, const uint8_t *report_buf, uint32_t *output1, uint8_t **output2, uint32_t *output_len)
{
    const uint8_t *src;
    uint32_t bits_len = item->attribute.report_size * item->attribute.report_count;

    if(bits_len == 0) {
        return -1;
    }

    if (item->report_flags & HID_MAINITEM_CONSTANT) {
        return -1;
    }

    if (item->attribute.report_id > 0) {
        if (report_buf[0] != item->attribute.report_id) {
            return -2; /* report id mismatch */
        }

        src = report_buf + 1; /* skip report id */
    } else {
        src = report_buf;
    }

    if ((bits_len < 32) && (bits_len % 8 != 0)) {
        *output1 = 0;

        for (uint32_t i = 0; i < bits_len; i++) {
            *output1 |= ((src[item->report_bit_offset / 8] >> ((item->report_bit_offset % 8) + i)) & 0x01) << i;
        }

        *output2 = NULL;
        *output_len = (bits_len + 7) / 8;
        return 0;
    } else if (bits_len % 8 == 0) {
        if (item->report_bit_offset % 8 != 0) {
            /* currently do not support item that is not byte aligned */
            return -3;
        }

        uint32_t byte_len = bits_len / 8;
        *output2 = (uint8_t *)src + item->report_bit_offset / 8;
        *output_len = byte_len;
        return 0;
    }
    return -4;
}

static void usbh_hid_item_info_print(struct usbh_hid_report_item *item)
{
    USB_LOG_RAW("Item Type: %s\r\n", (unsigned int)item->report_type == HID_REPORT_INPUT  ? "Input" :
                                     (unsigned int)item->report_type == HID_REPORT_OUTPUT ? "Output" :
                                                                                            "Feature");
    USB_LOG_RAW("Usage Page: 0x%04x\r\n", (unsigned int)item->attribute.usage_page);
    USB_LOG_RAW("Report ID: 0x%04x\r\n", (unsigned int)item->attribute.report_id);
    USB_LOG_RAW("Report Size: %ubit\r\n", (unsigned int)item->attribute.report_size);
    USB_LOG_RAW("Report Count: %u\r\n", (unsigned int)item->attribute.report_count);
    USB_LOG_RAW("Usages(0x%04x ~ 0x%04x)\r\n", (unsigned int)item->attribute.usage_min, (unsigned int)item->attribute.usage_max);
    USB_LOG_RAW("Logical Min: %d\r\n", item->attribute.logical_min);
    USB_LOG_RAW("Logical Max: %d\r\n", item->attribute.logical_max);
    USB_LOG_RAW("Properties: 0x%04x\r\n", (unsigned int)item->report_flags);
    USB_LOG_RAW("Bit Offset: 0x%04x\r\n", (unsigned int)item->report_bit_offset);
    USB_LOG_RAW("\r\n");
}

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_hid_report_desc_buf[2048];

int lshid(int argc, char **argv)
{
    struct usbh_hid *hid_class;
    int ret;
    struct usbh_hid_report_info report_info = { 0 };

    if (argc < 2) {
        USB_LOG_ERR("please input correct command: lshid path\r\n");
        return -1;
    }

    hid_class = usbh_find_class_instance(argv[1]);
    if (!hid_class) {
        USB_LOG_ERR("cannot find hid device\r\n");
        return -1;
    }

    if (hid_class->report_size > sizeof(g_hid_report_desc_buf)) {
        USB_LOG_ERR("hid report buffer is too small\r\n");
        return -1;
    }

    ret = usbh_hid_get_report_descriptor(hid_class, g_hid_report_desc_buf, hid_class->report_size);
    if (ret < 0) {
        USB_LOG_ERR("get hid report descriptor failed, errcode: %d\r\n", ret);
        return -1;
    }

    ret = usbh_hid_parse_report_descriptor(g_hid_report_desc_buf, hid_class->report_size, &report_info);
    if (ret < 0) {
        USB_LOG_ERR("parse hid report descriptor failed\r\n");
        return -1;
    }

    USB_LOG_INFO("HID report item count: %u\r\n", report_info.report_item_count);
    for (uint32_t i = 0; i < report_info.report_item_count; i++) {
        usbh_hid_item_info_print(&report_info.report_items[i]);
    }

    return 0;
}

__WEAK void usbh_hid_run(struct usbh_hid *hid_class)
{
    (void)hid_class;
}

__WEAK void usbh_hid_stop(struct usbh_hid *hid_class)
{
    (void)hid_class;
}

const struct usbh_class_driver hid_class_driver = {
    .driver_name = "hid",
    .connect = usbh_hid_connect,
    .disconnect = usbh_hid_disconnect
};

CLASS_INFO_DEFINE const struct usbh_class_info hid_custom_class_info = {
    .match_flags = USB_CLASS_MATCH_INTF_CLASS,
    .bInterfaceClass = USB_DEVICE_CLASS_HID,
    .bInterfaceSubClass = 0x00,
    .bInterfaceProtocol = 0x00,
    .id_table = NULL,
    .class_driver = &hid_class_driver
};
