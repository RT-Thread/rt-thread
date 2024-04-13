#ifndef _USBH_XXX_H
#define _USBH_XXX_H

#include "usb_xxx.h"

struct usbh_xxx {
    struct usbh_hubport *hport;
    struct usb_endpoint_descriptor *xxxin;
    struct usb_endpoint_descriptor *xxxout;
    struct usbh_urb xxxin_urb;
    struct usbh_urb xxxout_urb;

    uint8_t intf; /* interface number */
    uint8_t minor;

    void *user_data;
};

void usbh_xxx_run(struct usbh_xxx *xxx_class);
void usbh_xxx_stop(struct usbh_xxx *xxx_class);

#endif