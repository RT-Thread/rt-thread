#ifndef __USB_GADGET_DEMO_MSG_H__
#define __USB_GADGET_DEMO_MSG_H__

struct usb_msg_dev {
    uint8_t max_lun;
    uint8_t cbw[32];
};

extern struct usb_msg_dev g_msg_dev;

udc_errno_t usb_msg_callback(uint8_t ep_addr, udc_callback_event_t event,
            void *data, uint32_t len);
void usb_msg_desc_init(void);

#endif /* __USB_GADGET_DEMO_MSG_H__ */
