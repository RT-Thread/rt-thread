/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_BLUETOOTH_H
#define USBH_BLUETOOTH_H

#define USB_BLUETOOTH_HCI_NONE 0x00
#define USB_BLUETOOTH_HCI_CMD  0x01
#define USB_BLUETOOTH_HCI_ACL  0x02
#define USB_BLUETOOTH_HCI_SCO  0x03
#define USB_BLUETOOTH_HCI_EVT  0x04
#define USB_BLUETOOTH_HCI_ISO  0x05

struct usbh_bluetooth {
    struct usbh_hubport *hport;
    uint8_t intf;
    struct usb_endpoint_descriptor *bulkin;  /* Bulk IN endpoint */
    struct usb_endpoint_descriptor *bulkout; /* Bulk OUT endpoint */
    struct usbh_urb bulkin_urb;              /* Bulk IN urb */
    struct usbh_urb bulkout_urb;             /* Bulk OUT urb */
#ifndef CONFIG_USBHOST_BLUETOOTH_HCI_H4
    struct usb_endpoint_descriptor *intin;  /* INTR endpoint */
    struct usb_endpoint_descriptor *isoin;  /* Bulk IN endpoint */
    struct usb_endpoint_descriptor *isoout; /* Bulk OUT endpoint */
    struct usbh_urb intin_urb;              /* INTR IN urb */
    struct usbh_urb *isoin_urb;             /* Bulk IN urb */
    struct usbh_urb *isoout_urb;            /* Bulk OUT urb */
    uint8_t num_of_intf_altsettings;
#endif

    void *user_data;
};

#ifdef __cplusplus
extern "C" {
#endif

int usbh_bluetooth_hci_write(uint8_t hci_type, uint8_t *buffer, uint32_t buflen);
void usbh_bluetooth_hci_read_callback(uint8_t *data, uint32_t len);
#ifdef CONFIG_USBHOST_BLUETOOTH_HCI_H4
void usbh_bluetooth_hci_rx_thread(void *argument);
#else
void usbh_bluetooth_hci_evt_rx_thread(void *argument);
void usbh_bluetooth_hci_acl_rx_thread(void *argument);
#endif

void usbh_bluetooth_run(struct usbh_bluetooth *bluetooth_class);
void usbh_bluetooth_stop(struct usbh_bluetooth *bluetooth_class);

#ifdef __cplusplus
}
#endif

#endif /* USBH_BLUETOOTH_H */
