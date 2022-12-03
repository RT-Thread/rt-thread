#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include <usb/sunxi_hal_udc.h>
#include <usb/ch9.h>
#include <usb/storage.h>

#include <hal_log.h>

#include "usb_msg.h"

static struct usb_device_descriptor demo_device_desc = {
    .bLength = USB_DT_DEVICE_SIZE,
    .bDescriptorType = USB_DT_DEVICE,
    .bcdUSB = 0x0200,
    .bDeviceClass = 0,
    .bDeviceSubClass = 0,
    .bDeviceProtocol = 0,
    .bMaxPacketSize0 = 64,
    .idVendor = 0x18d1,
    .idProduct = 0x0001,
    .bcdDevice = 0x0001,
    .iManufacturer = 0x01,
    .iProduct = 0x02,
    .iSerialNumber = 0x03,
    .bNumConfigurations = 1
};

static struct usb_config_descriptor demo_config_desc = {
    .bLength = USB_DT_CONFIG_SIZE,
    .bDescriptorType = USB_DT_CONFIG,
    .wTotalLength = 32, /* FIXME */
    .bNumInterfaces = 1,
    .bConfigurationValue = 1,
    .iConfiguration = 0,
    .bmAttributes = 0x80,
    .bMaxPower = 0x64 /* 200mA */
};

static struct usb_interface_descriptor demo_intf_desc = {
    .bLength = USB_DT_INTERFACE_SIZE,
    .bDescriptorType = USB_DT_INTERFACE,
    .bInterfaceNumber = 0x0,
    .bAlternateSetting = 0x0,
    .bNumEndpoints = 2,
    .bInterfaceClass = 0x08, /* Mass Storage class */
    .bInterfaceSubClass = 0x06, /* SCSI Transparent Subclass */
    .bInterfaceProtocol = 0x50, /* Bulk-Only Protocol */
    .iInterface = 0
};

static struct usb_endpoint_descriptor demo_ep_bulk_out = {
    .bLength = USB_DT_ENDPOINT_SIZE,
    .bDescriptorType = USB_DT_ENDPOINT,
    .bEndpointAddress = 0x1 | USB_DIR_OUT,
    .bmAttributes = USB_ENDPOINT_XFER_BULK,
    .wMaxPacketSize = 0x0200, /* 512 Bytes */
    .bInterval = 0
};

static struct usb_endpoint_descriptor demo_ep_bulk_in = {
    .bLength = USB_DT_ENDPOINT_SIZE,
    .bDescriptorType = USB_DT_ENDPOINT,
    .bEndpointAddress = 0x1 | USB_DIR_IN,
    .bmAttributes = USB_ENDPOINT_XFER_BULK,
    .wMaxPacketSize = 0x0200, /* 512 Bytes */
    .bInterval = 0
};

/*
 * String descriptors
 */
static const uint16_t g_str_lang_id[] = {
    0x0304, 0x0409
};

static const uint16_t g_str_manufacturer[] = {
    0x030e, 'G', 'o', 'o', 'g', 'l', 'e'
};

static const uint16_t g_str_product[] = {
    0x0308, 'M', 's', 'g'
};

static const uint16_t g_str_serialnumber[] = {
    0x0314, '2', '0', '0', '8', '0', '4', '1', '1'
};

struct usb_msg_dev g_msg_dev = {
    .max_lun = 0,
};

static void *g_config_desc = NULL;

void usb_msg_desc_init(void)
{
    uint32_t config_desc_len;
    void *buf;

    config_desc_len = demo_config_desc.bLength + demo_intf_desc.bLength
            + demo_ep_bulk_out.bLength + demo_ep_bulk_in.bLength;

    g_config_desc = malloc(config_desc_len);

    /* compose configuation, interface and endpoint descriptors */
    buf = g_config_desc;
    memcpy(buf, &demo_config_desc, demo_config_desc.bLength);
    buf += demo_config_desc.bLength;
    memcpy(buf, &demo_intf_desc, demo_intf_desc.bLength);
    buf += demo_intf_desc.bLength;
    memcpy(buf, &demo_ep_bulk_out, demo_ep_bulk_out.bLength);
    buf += demo_ep_bulk_out.bLength;
    memcpy(buf, &demo_ep_bulk_in, demo_ep_bulk_in.bLength);

    hal_udc_device_desc_init(&demo_device_desc);
    hal_udc_config_desc_init(g_config_desc, config_desc_len);
    /* FIXME: string descriptors must be initialized in the following order now */
    hal_udc_string_desc_init(g_str_lang_id);
    hal_udc_string_desc_init(g_str_manufacturer);
    hal_udc_string_desc_init(g_str_product);
    hal_udc_string_desc_init(g_str_serialnumber);
}

static void usb_msg_ep_init(void)
{
    hal_log_info("usb demo ep init...\n");

    /* init bulk-in ep */
    hal_udc_ep_enable(demo_ep_bulk_in.bEndpointAddress,
            demo_ep_bulk_in.wMaxPacketSize,
            demo_ep_bulk_in.bmAttributes & USB_ENDPOINT_XFERTYPE_MASK);

    /* initialise bulk-out ep buf in order to get the first CBW */
    hal_udc_ep_set_buf(demo_ep_bulk_out.bEndpointAddress,
            g_msg_dev.cbw,
            sizeof(g_msg_dev.cbw));

    /* init bulk-out ep */
    hal_udc_ep_enable(demo_ep_bulk_out.bEndpointAddress,
            demo_ep_bulk_out.wMaxPacketSize,
            demo_ep_bulk_out.bmAttributes & USB_ENDPOINT_XFERTYPE_MASK);
}

static udc_errno_t usb_msg_class_request_handler(struct usb_ctrlrequest *crq)
{
    udc_errno_t ret = UDC_ERRNO_SUCCESS;

    switch(crq->bRequest) {
    case US_BULK_RESET_REQUEST:
        /* TODO */
        break;
    case US_BULK_GET_MAX_LUN:
        hal_log_info("get MAX_LUN\r\n");

        if (crq->bRequestType !=
                (USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE)) {
            ret = UDC_ERRNO_CMD_INVALID;
            break;
        }
        /* FIXME: a fake response for demo */
        hal_udc_ep_write(0, &g_msg_dev.max_lun, sizeof(g_msg_dev.max_lun));
        break;
    default:
        ret = UDC_ERRNO_CMD_INVALID;
        break;
    }

    return ret;
}

static udc_errno_t usb_msg_standard_request_handler(struct usb_ctrlrequest *crq)
{
    udc_errno_t ret = UDC_ERRNO_SUCCESS;

    switch (crq->bRequest) {
    case USB_REQ_SET_CONFIGURATION:
        /* FIXME: usb msg driver should be independent of demo code */
        usb_msg_ep_init();
        break;
    default:
        ret = UDC_ERRNO_CMD_INVALID;
        break;
    }

    return ret;
}

static udc_errno_t usb_msg_scsi_cmd_handler(struct bulk_cb_wrap *cbw)
{
    udc_errno_t ret = UDC_ERRNO_SUCCESS;
    uint8_t opcode = cbw->CDB[0];
    uint8_t fake_rsp[36] = {0x00, 0x80, 0x02, 0x02, 0x1F, 0x00, 0x00,
            0x00, 0x54, 0x69, 0x6e, 0x61, 0x20, 0x20, 0x20,
            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
            0x20, 0x20, 0x20, 0x20, 0x20};

    hal_log_info("scsi cmd opcode: 0x%x\n", opcode);

    switch (opcode) {
    case 0x12: /* INQUIRY */
        /* FIXME: a fake response for demo */
        hal_udc_ep_write(demo_ep_bulk_in.bEndpointAddress, fake_rsp, sizeof(fake_rsp));
        break;
    default:
        ret = UDC_ERRNO_CMD_INVALID;
        break;
    }

    return ret;
}

udc_errno_t usb_msg_callback(uint8_t ep_addr, udc_callback_event_t event, void *data, uint32_t len)
{
    uint8_t ep_idx;
    uint8_t is_in;
    udc_errno_t ret = UDC_ERRNO_SUCCESS;
    struct usb_ctrlrequest *crq;
    struct bulk_cb_wrap *cbw;

    hal_log_info("usb_msg_callback event: %"PRIu32", len: %"PRIu32"\n", event, len);

    ep_idx = ep_addr & 0x7f;
    is_in = ep_addr & USB_DIR_IN;

    if (ep_idx == 0) { /* handle ep0 */
        crq = (struct usb_ctrlrequest *)data;

        switch (event) {
        case UDC_EVENT_RX_STANDARD_REQUEST:
            ret = usb_msg_standard_request_handler(crq);
            break;
        case UDC_EVENT_RX_CLASS_REQUEST:
            ret = usb_msg_class_request_handler(crq);
            break;
        default:
            ret = UDC_ERRNO_CMD_NOT_SUPPORTED;
            break;
        }
    } else { /* handle ep1~4 */
        if (is_in) {
            /* TODO: maybe useless? */
        } else {
            cbw = (struct bulk_cb_wrap *)data;

            switch (event) {
            case UDC_EVENT_RX_DATA:
                usb_msg_scsi_cmd_handler(cbw);
                break;
            default:
                ret = UDC_ERRNO_CMD_NOT_SUPPORTED;
                break;
            }
        }
    }

    return ret;
}
