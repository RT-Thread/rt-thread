#ifndef _USB_GEN_HUB_H_
#define _USB_GEN_HUB_H_


#include "usb_gen_hub_base.h"
#define usb_endpoint_out(ep_dir)    (!((ep_dir) & USB_DIR_IN))

void usb_set_device_state(struct usb_host_virt_dev *udev, enum usb_device_state new_state);
void usb_disable_endpoint(struct usb_host_virt_dev *dev, unsigned int epaddr);

void usb_disconnect(struct usb_host_virt_dev **pdev);

void usb_disable_device(struct usb_host_virt_dev *dev, int skip_ep0);
int usb_reset_device(struct usb_host_virt_dev *udev);

int usb_new_device(struct usb_host_virt_dev *udev);

__u32 hub_GetHubNo(struct usb_host_virt_dev *udev);
__u32 hub_GetHubSeries(struct usb_host_virt_dev *udev);

void kick_khubd(struct usb_hub *hub);
void hub_activate(struct usb_hub *hub);

s32 usb_gen_hub_init(void);
s32 usb_gen_hub_exit(void);

#endif

