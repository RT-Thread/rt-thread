#ifndef _USB_GEN_DEV_MOD_H_
#define _USB_GEN_DEV_MOD_H_

#include "usb_host_common.h"

struct usb_gen_dev_mod
{
    struct usb_gen_dev_mod *parent;
    void *driver_data;      //驱动用来临时积存私有数据的。
};

struct usb_interface *usb_mod_to_usb_interface(struct usb_host_virt_sub_dev *sub_dev);
struct usb_host_virt_sub_dev *usb_mod_interface_to_virt_sub_dev(struct usb_interface *intf);
struct usb_host_func_drv *usb_mod_interface_to_func_drv(struct usb_interface *intf);
struct usb_host_virt_dev *usb_mod_interface_to_usbdev(struct usb_interface *intf);
void *usb_mod_usb_get_intf_priv_data(struct usb_interface *intf);
void  usb_mod_usb_set_intf_priv_data(struct usb_interface *intf, void *data);

#endif

