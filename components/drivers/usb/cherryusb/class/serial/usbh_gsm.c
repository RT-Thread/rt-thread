/*
 * Copyright (c) 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_serial.h"

#undef USB_DBG_TAG
#define USB_DBG_TAG "usbh_gsm"
#include "usb_log.h"

struct usbh_gsm {
    struct usb_endpoint_descriptor *intin;
    struct usbh_urb intin_urb;
    struct usb_osal_timer *modem_timer;
    uint16_t modem_status;
};

static int usbh_gsm_attach(struct usbh_serial *serial)
{
    struct usb_endpoint_descriptor *ep_desc;

    struct usbh_gsm *gsm_class = usb_osal_malloc(sizeof(struct usbh_gsm));
    if (!gsm_class) {
        USB_LOG_ERR("No memory for gsm_class\r\n");
        return -USB_ERR_NOMEM;
    }
    memset(gsm_class, 0, sizeof(struct usbh_gsm));
    serial->priv = gsm_class;

    for (uint8_t i = 0; i < serial->hport->config.intf[serial->intf].altsetting[0].intf_desc.bNumEndpoints; i++) {
        ep_desc = &serial->hport->config.intf[serial->intf].altsetting[0].ep[i].ep_desc;

        if (USB_GET_ENDPOINT_TYPE(ep_desc->bmAttributes) == USB_ENDPOINT_TYPE_INTERRUPT) {
            if (ep_desc->bEndpointAddress & 0x80) {
                USBH_EP_INIT(gsm_class->intin, ep_desc);
                break;
            } else {
            }
        }
    }

    if (!gsm_class->intin) {
        USB_LOG_WRN("Do not find interrupt endpoint, so disable modem status monitor\r\n");
    }
    return 0;
}

static void usbh_gsm_detach(struct usbh_serial *serial)
{
    struct usbh_gsm *gsm_class;

    if (!serial || !serial->priv) {
        return;
    }

    gsm_class = (struct usbh_gsm *)serial->priv;
    if (gsm_class->intin) {
        usbh_kill_urb(&gsm_class->intin_urb);
    }
    serial->priv = NULL;
    usb_osal_free(gsm_class);
}

static int usbh_gsm_set_line_coding(struct usbh_serial *serial, struct cdc_line_coding *line_coding)
{
    return 0;
}

static int usbh_gsm_set_line_state(struct usbh_serial *serial, bool dtr, bool rts)
{
    return 0;
}

static const struct usbh_serial_driver gsm_driver = {
    .driver_name = "gsm",

    .ignore_rx_header = 0,
    .ignore_tx_header = 0,

    .attach = usbh_gsm_attach,
    .detach = usbh_gsm_detach,
    .set_flow_control = NULL,
    .set_line_coding = usbh_gsm_set_line_coding,
    .get_line_coding = NULL,
    .set_line_state = usbh_gsm_set_line_state,
    .get_modem_status = NULL,
};

static int usbh_gsm_connect(struct usbh_hubport *hport, uint8_t intf)
{
    return usbh_serial_probe(hport, intf, &gsm_driver) ? 0 : -USB_ERR_NOMEM;
}

static int usbh_gsm_disconnect(struct usbh_hubport *hport, uint8_t intf)
{
    struct usbh_serial *serial = (struct usbh_serial *)hport->config.intf[intf].priv;

    if (serial) {
        usbh_serial_remove(serial);
    }
    return 0;
}

const struct usbh_class_driver gsm_class_driver = {
    .driver_name = "gsm",
    .connect = usbh_gsm_connect,
    .disconnect = usbh_gsm_disconnect
};

static const uint16_t gsm_id_table[][2] = {
    { 0x2C7C, 0x0120 }, /* Quectel EC20 */
    { 0x2C7C, 0x0121 }, /* Quectel EC21 */
    { 0x2C7C, 0x0125 }, /* Quectel EC25 */
    { 0x2C7C, 0x0191 }, /* Quectel EG91 */
    { 0x2C7C, 0x0195 }, /* Quectel EG95 */
    { 0x2C7C, 0x6002 }, /* Quectel EC200/EC600/EC800/EG91x */
    { 0x1E0E, 0x9001 }, /* SIMCOM SIM7600 */
    { 0x2ECC, 0x3012 }, /* Chinamobile ML307R */
    { 0, 0 },
};

CLASS_INFO_DEFINE const struct usbh_class_info gsm_class_info = {
    .match_flags = USB_CLASS_MATCH_VID_PID | USB_CLASS_MATCH_INTF_CLASS | USB_CLASS_MATCH_INTF_SUBCLASS | USB_CLASS_MATCH_INTF_PROTOCOL,
    .bInterfaceClass = 0xff,
    .bInterfaceSubClass = 0x00,
    .bInterfaceProtocol = 0x00,
    .id_table = gsm_id_table,
    .class_driver = &gsm_class_driver
};
