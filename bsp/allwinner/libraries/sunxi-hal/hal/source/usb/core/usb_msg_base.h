#ifndef _USB_MSG_BASE_H_
#define _USB_MSG_BASE_H_

int _usb_internal_ctrll_msg(struct usb_host_virt_dev *usb_dev,
                            u32 pipe,  struct usb_ctrlrequest *cmd,
                            void *data, s32 len, s32 timeout);

int _usb_internal_bulk_msg(struct usb_host_virt_dev *usb_dev, unsigned int pipe,
                           void *data, int len, int *actual_length, int timeout);

int usb_get_string(struct usb_host_virt_dev  *dev, u16 langid,
                   u8  index, void *buf, s32 size);
int _usb_string_sub(struct usb_host_virt_dev  *dev,  u32 langid, u32 index, u8 *buf);

#endif
