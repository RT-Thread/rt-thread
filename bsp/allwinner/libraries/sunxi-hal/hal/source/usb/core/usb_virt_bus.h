#ifndef _USB_VIRT_BUS_H_
#define _USB_VIRT_BUS_H_

s32 usb_virt_bus_drv_reg(struct usb_host_func_drv *drv);
s32 usb_virt_bus_drv_unreg(struct usb_host_func_drv *drv);
s32 usb_virt_bus_dev_add(struct usb_host_virt_sub_dev *dev);
s32 usb_virt_bus_dev_del(struct usb_host_virt_sub_dev *dev);

s32 usb_virt_bus_init(void);
s32 usb_virt_bus_exit(void);

#endif



