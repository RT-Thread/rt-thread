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

struct hid_report *usbh_hid_report_parse(const uint8_t *data, uint32_t report_len, uint32_t max_usages)
{
    uint32_t i = 0;
    uint32_t itemtag, itemtype, itemsize;
    uint32_t itemval;
    struct hid_report_field field;
    uint32_t usage_page = 0, usage = 0, usage_min = 0, usage_max = 0, flags = 0;
    uint32_t *usages;
    struct hid_report *hid_report;

    hid_report = usb_osal_malloc(sizeof(struct hid_report));
    if (!hid_report) {
        USB_LOG_ERR("hid report malloc failed\r\n");
        return NULL;
    }

    usages = usb_osal_malloc(sizeof(uint32_t) * max_usages);
    if (!usages) {
        USB_LOG_ERR("hid usages malloc failed\r\n");
        goto err;
    }

    memset(hid_report, 0, sizeof(struct hid_report));
    memset(&field, 0, sizeof(struct hid_report_field));

    while (i < report_len) {
        itemtag = data[i] & HID_TAG_MASK;
        itemtype = data[i] & HID_TYPE_MASK;
        itemsize = data[i] & HID_SIZE_MASK;

        if (itemsize == 3) /* HID spec: 6.2.2.2 - Short Items */
            itemsize = 4;

        itemval = hid_get_itemval(data, i, itemsize);

        USB_LOG_DBG("itemtype 0x%02x, itemtag 0x%02x, itemsize %d, itemval 0x%08x\r\n",
                    itemtype, itemtag, itemsize, itemval);

        switch (itemtype) {
            case HID_ITEMTYPE_MAIN:
                switch (itemtag) {
                    case HID_MAINITEM_TAG_INPUT:
                        if ((flags & HID_REPORT_FLAG_REQUIRED_MASK) != HID_REPORT_FLAG_REQUIRED_MASK)
                            goto err;

                        if (hid_report->input_count >= CONFIG_USBHOST_HID_MAX_INPUT) {
                            USB_LOG_ERR("hid input fields exceed max limit\r\n");
                            goto err;
                        }

                        field.flags = flags;
                        field.properties = itemval;
                        field.usage_page = usage_page;
                        memcpy(&hid_report->input_fields[hid_report->input_count], &field, sizeof(struct hid_report_field));
                        if (field.usage_count > 0) {
                            hid_report->input_fields[hid_report->input_count].usages = usb_osal_malloc(sizeof(uint32_t) * field.usage_count);
                            if (!hid_report->input_fields[hid_report->input_count].usages) {
                                USB_LOG_ERR("hid input usages malloc failed\r\n");
                                goto err;
                            }
                            memcpy(hid_report->input_fields[hid_report->input_count].usages, usages, sizeof(uint32_t) * field.usage_count);
                        }

                        hid_report->input_count++;

                        /* only keep the global items */
                        flags &= HID_REPORT_FLAG_GLOBAL_MASK;
                        memset(&field, 0, sizeof(struct hid_report_field));
                        break;
                    case HID_MAINITEM_TAG_OUTPUT:
                        if ((flags & HID_REPORT_FLAG_REQUIRED_MASK) != HID_REPORT_FLAG_REQUIRED_MASK)
                            goto err;

                        if (hid_report->output_count >= CONFIG_USBHOST_HID_MAX_OUTPUT) {
                            USB_LOG_ERR("hid output fields exceed max limit\r\n");
                            goto err;
                        }

                        field.flags = flags;
                        field.properties = itemval;
                        field.usage_page = usage_page;
                        memcpy(&hid_report->output_fields[hid_report->output_count], &field, sizeof(struct hid_report_field));
                        if (field.usage_count > 0) {
                            hid_report->output_fields[hid_report->output_count].usages = usb_osal_malloc(sizeof(uint32_t) * field.usage_count);
                            if (!hid_report->output_fields[hid_report->output_count].usages) {
                                USB_LOG_ERR("hid output usages malloc failed\r\n");
                                goto err;
                            }
                            memcpy(hid_report->output_fields[hid_report->output_count].usages, usages, sizeof(uint32_t) * field.usage_count);
                        }

                        hid_report->output_count++;

                        /* only keep the global items */
                        flags &= HID_REPORT_FLAG_GLOBAL_MASK;
                        memset(&field, 0, sizeof(struct hid_report_field));
                        break;
                    case HID_MAINITEM_TAG_COLLECTION:
                        memset(&field, 0, sizeof(struct hid_report_field));
                        break;
                    case HID_MAINITEM_TAG_FEATURE:

                        if (hid_report->feature_count >= CONFIG_USBHOST_HID_MAX_FEATURE) {
                            USB_LOG_ERR("hid feature fields exceed max limit\r\n");
                            goto err;
                        }

                        field.flags = flags;
                        field.properties = itemval;
                        field.usage_page = usage_page;
                        memcpy(&hid_report->feature_fields[hid_report->feature_count], &field, sizeof(struct hid_report_field));
                        if (field.usage_count > 0) {
                            hid_report->feature_fields[hid_report->feature_count].usages = usb_osal_malloc(sizeof(uint32_t) * field.usage_count);
                            if (!hid_report->feature_fields[hid_report->feature_count].usages) {
                                USB_LOG_ERR("hid feature usages malloc failed\r\n");
                                goto err;
                            }
                            memcpy(hid_report->feature_fields[hid_report->feature_count].usages, usages, sizeof(uint32_t) * field.usage_count);
                        }

                        hid_report->feature_count++;

                        memset(&field, 0, sizeof(struct hid_report_field));

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
                        usage_page = itemval;

                        if (usage_page > UINT16_MAX)
                            goto err;

                        flags |= HID_REPORT_FLAG_USAGE_PAGE;
                        break;
                    case HID_GLOBALITEM_TAG_LOGICAL_MIN:
                        field.logical_min = (int32_t)itemval;
                        flags |= HID_REPORT_FLAG_LOGICAL_MIN;
                        break;
                    case HID_GLOBALITEM_TAG_LOGICAL_MAX:
                        field.logical_max = (int32_t)itemval;
                        flags |= HID_REPORT_FLAG_LOGICAL_MAX;
                        break;
                    case HID_GLOBALITEM_TAG_REPORT_SIZE:
                        field.report_size = itemval;
                        flags |= HID_REPORT_FLAG_REPORT_SIZE;
                        break;
                    case HID_GLOBALITEM_TAG_REPORT_COUNT:
                        field.report_count = itemval;
                        flags |= HID_REPORT_FLAG_REPORT_COUNT;
                        break;
                    case HID_GLOBALITEM_TAG_REPORT_ID:
                        hid_report->uses_report_id = true;
                        field.report_id = itemval;
                        flags |= HID_REPORT_FLAG_REPORT_ID;
                        break;
                    default:
                        goto err;
                }
                break;
            case HID_ITEMTYPE_LOCAL:
                switch (itemtag) {
                    case HID_LOCALITEM_TAG_USAGE:
                        usage = itemval;
                        /* Extended usage (size 4) combines both usage page and id */
                        if (itemsize != 4) {
                            if (!(flags & HID_REPORT_FLAG_USAGE_PAGE))
                                goto err;
                            usage |= usage_page << 16;
                        }

                        usages[field.usage_count++] = usage;

                        break;
                    case HID_LOCALITEM_TAG_USAGE_MIN:
                        usage_min = itemval;
                        if (itemsize == 4) {
                            /* Usage max must be extended as well */
                            flags |= HID_REPORT_FLAG_EXTENDED_USAGE;
                        } else {
                            if (!(flags & HID_REPORT_FLAG_USAGE_PAGE))
                                goto err;
                            usage_min |= usage_page << 16;
                        }
                        field.usage_min = usage_min;
                        flags |= HID_REPORT_FLAG_USAGE_MIN;
                        break;
                    case HID_LOCALITEM_TAG_USAGE_MAX:
                        if (!(flags & HID_REPORT_FLAG_USAGE_MIN))
                            goto err;

                        usage_max = itemval;
                        if (flags & HID_REPORT_FLAG_EXTENDED_USAGE) {
                            /* Fail if max is not extended usage (HID spec 6.2.2.8) */
                            if (itemsize != 4)
                                goto err;
                        } else if (itemsize == 4) {
                            /* Fail because min wasn't extended, but max is */
                            goto err;
                        } else {
                            if (!(flags & HID_REPORT_FLAG_USAGE_PAGE))
                                goto err;
                            usage_max |= usage_page << 16;
                        }

                        /* Usage min and max must be on the same page */
                        if (USAGE_PAGE(usage_min) != USAGE_PAGE(usage_max)) {
                            goto err;
                        }

                        if (usage_min > usage_max) {
                            goto err;
                        }

                        for (uint32_t j = usage_min; j <= usage_max; j++) {
                            usages[field.usage_count++] = j;
                        }

                        field.usage_max = usage_max;
                        flags |= HID_REPORT_FLAG_USAGE_MAX;
                        flags &= ~(HID_REPORT_FLAG_USAGE_MIN | HID_REPORT_FLAG_EXTENDED_USAGE);
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
    usb_osal_free(usages);
    return hid_report;
err:
    if (hid_report) {
        usb_osal_free(hid_report);

        for (uint32_t j = 0; j < hid_report->input_count; j++)
            usb_osal_free(hid_report->input_fields[j].usages);

        for (uint32_t j = 0; j < hid_report->output_count; j++)
            usb_osal_free(hid_report->output_fields[j].usages);

        for (uint32_t j = 0; j < hid_report->feature_count; j++)
            usb_osal_free(hid_report->feature_fields[j].usages);
    }

    if (usages)
        usb_osal_free(usages);
    return NULL;
}

void usbh_hid_report_free(struct hid_report *hid_report)
{
    if (hid_report) {
        for (uint32_t j = 0; j < hid_report->input_count; j++)
            usb_osal_free(hid_report->input_fields[j].usages);

        for (uint32_t j = 0; j < hid_report->output_count; j++)
            usb_osal_free(hid_report->output_fields[j].usages);

        for (uint32_t j = 0; j < hid_report->feature_count; j++)
            usb_osal_free(hid_report->feature_fields[j].usages);

        usb_osal_free(hid_report);
    }
}

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t g_hid_report_buf[2048];

static const char *hid_property_string(uint32_t value)
{
    uint32_t off = 0;
    static char buffer[160];

    memset(buffer, 0, sizeof(buffer));

    if (value & HID_MAINITEM_CONSTANT)
        off += snprintf(buffer + off, sizeof(buffer) - off, "Constant, ");
    else
        off += snprintf(buffer + off, sizeof(buffer) - off, "Data, ");

    if (value & HID_MAINITEM_VARIABLE)
        off += snprintf(buffer + off, sizeof(buffer) - off, "Variable, ");
    else
        off += snprintf(buffer + off, sizeof(buffer) - off, "Array, ");

    if (value & HID_MAINITEM_RELATIVE)
        off += snprintf(buffer + off, sizeof(buffer) - off, "Relative, ");
    else
        off += snprintf(buffer + off, sizeof(buffer) - off, "Absolute, ");

    if (value & HID_MAINITEM_WRAP)
        off += snprintf(buffer + off, sizeof(buffer) - off, "Wrap, ");
    else
        off += snprintf(buffer + off, sizeof(buffer) - off, "NoWrap, ");

    if (value & HID_MAINITEM_NONLINEAR)
        off += snprintf(buffer + off, sizeof(buffer) - off, "NonLinear, ");
    else
        off += snprintf(buffer + off, sizeof(buffer) - off, "Linear, ");

    if (value & HID_MAINITEM_NOPREFERRED)
        off += snprintf(buffer + off, sizeof(buffer) - off, "NoPreferred, ");
    else
        off += snprintf(buffer + off, sizeof(buffer) - off, "Preferred, ");

    if (value & HID_MAINITEM_NULLSTATE)
        off += snprintf(buffer + off, sizeof(buffer) - off, "NullState, ");
    else
        off += snprintf(buffer + off, sizeof(buffer) - off, "NoNullState, ");

    if (value & HID_MAINITEM_VOLATILE)
        off += snprintf(buffer + off, sizeof(buffer) - off, "Volatile, ");
    else
        off += snprintf(buffer + off, sizeof(buffer) - off, "NonVolatile, ");

    if (value & HID_MAINITEM_BUFFEREDBYTES)
        off += snprintf(buffer + off, sizeof(buffer) - off, "BufferedBytes");
    else
        off += snprintf(buffer + off, sizeof(buffer) - off, "BitField");

    return buffer;

}

static void usbh_hid_field_info_print(uint32_t idx, struct hid_report_field *field)
{
    USB_LOG_RAW("  Field %u:\r\n", idx);
    USB_LOG_RAW("    Usage Page: 0x%04x\r\n", (unsigned int)field->usage_page);
    USB_LOG_RAW("    Report ID: %u\r\n", (unsigned int)field->report_id);
    USB_LOG_RAW("    Report Size: %ubit\r\n", (unsigned int)field->report_size);
    USB_LOG_RAW("    Report Count: %u\r\n", (unsigned int)field->report_count);
    USB_LOG_RAW("    Logical Min: %d\r\n", field->logical_min);
    USB_LOG_RAW("    Logical Max: %d\r\n", field->logical_max);
    USB_LOG_RAW("    Usage Count: %u\r\n", (unsigned int)field->usage_count);
    if (field->usage_count > 0) {
        if (field->usage_count == 1) {
            USB_LOG_RAW("    Usage: 0x%04x\r\n", USAGE_ID(field->usages[0]));
        } else {
            USB_LOG_RAW("    Usages(0x%04x ~ 0x%04x)\r\n", USAGE_ID(field->usage_min), USAGE_ID(field->usage_max));
        }
    }
    USB_LOG_RAW("    Flags: 0x%04x\r\n", (unsigned int)field->flags);
    USB_LOG_RAW("    Properties: 0x%04x(%s)\r\n", (unsigned int)field->properties, hid_property_string(field->properties));
}

int lshid(int argc, char **argv)
{
    struct usbh_hid *hid_class;
    struct hid_report *hid_report;
    int ret;

    if (argc < 2) {
        USB_LOG_ERR("please input correct command: lshid path\r\n");
        return -1;
    }

    hid_class = usbh_find_class_instance(argv[1]);
    if (!hid_class) {
        USB_LOG_ERR("cannot find hid device\r\n");
        return -1;
    }

    if (hid_class->report_size > sizeof(g_hid_report_buf)) {
        USB_LOG_ERR("hid report buffer is too small\r\n");
        return -1;
    }

    ret = usbh_hid_get_report_descriptor(hid_class, g_hid_report_buf, hid_class->report_size);
    if (ret < 0) {
        USB_LOG_ERR("get hid report descriptor failed, errcode: %d\r\n", ret);
        return -1;
    }

    hid_report = usbh_hid_report_parse(g_hid_report_buf, hid_class->report_size, 1024);
    if (hid_report) {
        USB_LOG_RAW("HID report parsed successfully\r\n");

        USB_LOG_RAW("Input fields: %u\r\n", (unsigned int)hid_report->input_count);
        for (uint32_t i = 0; i < hid_report->input_count; i++) {
            struct hid_report_field *field = &hid_report->input_fields[i];
            usbh_hid_field_info_print(i, field);
        }

        USB_LOG_RAW("Output fields: %u\r\n", (unsigned int)hid_report->output_count);
        for (uint32_t i = 0; i < hid_report->output_count; i++) {
            struct hid_report_field *field = &hid_report->output_fields[i];
            usbh_hid_field_info_print(i, field);
        }

        USB_LOG_RAW("Feature fields: %u\r\n", (unsigned int)hid_report->feature_count);
        for (uint32_t i = 0; i < hid_report->feature_count; i++) {
            struct hid_report_field *field = &hid_report->feature_fields[i];
            usbh_hid_field_info_print(i, field);
        }

        usbh_hid_report_free(hid_report);
    } else {
        USB_LOG_ERR("HID report parsed failed\r\n");
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
