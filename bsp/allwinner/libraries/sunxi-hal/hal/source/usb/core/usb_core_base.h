#ifndef _USB_CORE_BASE_H_
#define _USB_CORE_BASE_H_

//usb host开启
u8 usb_host_enable(void);
//usb host 禁止
u8 usb_host_disable(void);

//查询usb host是否开启
//return    :   非0为enable
u8 usb_host_is_enabled(void);


//usb_host_virt_dev{}的分配与释放
struct usb_host_virt_dev *usb_host_alloc_virt_dev(struct usb_host_virt_dev *parent, struct usb_virt_bus *bus, u32 port1);
void usb_host_free_virt_dev(struct usb_host_virt_dev *virt_dev);



struct usb_host_virt_interface *usb_altnum_to_altsetting(struct usb_interface *intf, s32 altnum);




void usb_lock_device(struct usb_host_virt_dev *virt_dev);
void usb_unlock_device(struct usb_host_virt_dev *virt_dev);



void *usb_buffer_alloc(struct usb_host_virt_dev *dev, u32 size, u32 mem_flags, void *dma);
void usb_buffer_free(struct usb_host_virt_dev *dev, u32 size, void *addr, void *dma);

struct usb_interface *usb_ifnum_to_if(struct usb_host_virt_dev *dev, u32  ifnum);

s32 _usb_core_func_drv_probe_interface(struct usb_host_virt_sub_dev *sub_dev);
s32 _usb_core_func_drv_disconncet_interface(struct usb_host_virt_sub_dev *dev);


#endif
