#ifndef _USB_CORE_INTERFACE_H_
#define _USB_CORE_INTERFACE_H_
s32 usb_host_func_drv_reg(struct usb_host_func_drv *drv);
s32 usb_host_func_drv_unreg(struct usb_host_func_drv *drv);
void *usb_buffer_alloc(struct usb_host_virt_dev *dev, u32 size, u32 mem_flags, void *dma);
void usb_buffer_free(struct usb_host_virt_dev *dev, u32 size, void *addr, void *dma);
#endif
