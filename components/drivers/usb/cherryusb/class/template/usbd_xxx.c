#include "usbd_core.h"
#include "usbd_xxx.h"

static int xxx_class_interface_request_handler(uint8_t busid, struct usb_setup_packet *setup, uint8_t **data, uint32_t *len)
{
    USB_LOG_WRN("XXX Class request: "
                 "bRequest 0x%02x\r\n",
                 setup->bRequest);

    switch (setup->bRequest) {
        default:
            USB_LOG_WRN("Unhandled XXX Class bRequest 0x%02x\r\n", setup->bRequest);
            return -1;
    }

    return 0;
}

static void xxx_notify_handler(uint8_t busid, uint8_t event, void *arg)
{
    switch (event) {
        case USBD_EVENT_RESET:

            break;

        default:
            break;
    }
}

struct usbd_interface *usbd_xxx_init_intf(uint8_t busid, struct usbd_interface *intf)
{
    intf->class_interface_handler = xxx_class_interface_request_handler;
    intf->class_endpoint_handler = NULL;
    intf->vendor_handler = NULL;
    intf->notify_handler = xxx_notify_handler;

    return intf;
}
