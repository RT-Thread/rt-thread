#ifndef _USB_MSG_H_
#define _USB_MSG_H_

int usb_string(struct usb_host_virt_dev *dev, int index, char *buf, u32 size);
int usb_control_msg(struct usb_host_virt_dev *dev, u32 pipe, u8 request, u8 requesttype,
                    u16 value, u16 index, void *data, u16 size, s32 timeout);
s32 usb_set_configuration(struct usb_host_virt_dev *dev, s32 configuration);
s32 usb_get_descriptor(struct usb_host_virt_dev *dev, u8 type, u8 index, void *buf, s32 size);
s32 usb_get_device_descriptor(struct usb_host_virt_dev *dev, u32 size);

int __usb_get_extra_descriptor(unsigned char *buffer,
                               unsigned size,
                               unsigned char type,
                               void **ptr);
#define usb_get_extra_descriptor(ifpoint,type,ptr)\
    __usb_get_extra_descriptor((ifpoint)->extra,(ifpoint)->extralen,\
                               type,(void**)ptr)

int usb_get_status(struct usb_host_virt_dev *dev, s32 type, s32 target, void *data);
int usb_clear_halt(struct usb_host_virt_dev *dev, int pipe);

int usb_set_interface(struct usb_host_virt_dev  *dev, int interface, int alternate);
void usb_disable_interface(struct usb_host_virt_dev *dev, struct usb_interface *intf);

int usb_bulk_msg(struct usb_host_virt_dev *usb_dev, unsigned int pipe, void *data, int len, int *actual_length, int timeout);
#endif
