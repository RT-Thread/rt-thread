/*
*******************************************************************************
*                                              usb host module
*
*                             Copyright(C), 2006-2008, SoftWinners Co., Ltd.
*                                                  All Rights Reserved
*
* File Name :
*
* Author : GLHuang(HoLiGun)
*
* Version : 1.0
*
* Date : 2008.07.07
*
* Description :
*           usb的通用设备模型，临时版本，
* History :
*
********************************************************************************************************************
*/
#include "usb_os_platform.h"
#include "usb_host_common.h"

#include "usb_list.h"

//to_usb_interface
//从sub_devf转换到interface
struct usb_interface *usb_mod_to_usb_interface(struct usb_host_virt_sub_dev *sub_dev)
{
    if (!sub_dev)
    {
        hal_log_err("PANIC : usb_dev_mod :: from virt_sub_dev to usb_interface input == NULL\n");
        return NULL;
    }

    return sub_dev->sub_dev_interface;
}

//从intf转换到virt_sub_dev
struct usb_host_virt_sub_dev *usb_mod_interface_to_virt_sub_dev(struct usb_interface *intf)
{
    if (!intf)
    {
        hal_log_err("PANIC : usb_dev_mod :: from usb_interface to virt_sub_dev input == NULL\n");
        return NULL;
    }

    return intf->virt_sub_dev;
}

//从intf转换到func_drv
struct usb_host_func_drv *usb_mod_interface_to_func_drv(struct usb_interface *intf)
{
    if (!intf)
    {
        hal_log_err("PANIC : usb_dev_mod :: from usb_interface to virt_sub_dev input == NULL\n");
        return NULL;
    }

    if (intf->virt_sub_dev)
    {
        return intf->virt_sub_dev->func_drv;
    }
    else
    {
        hal_log_err("PANIC : usb_dev_mod :: from usb_interface to func_drv :  intf->virt_sub_dev == NULL\n");
        return NULL;
    }
}

//interface_to_usbdev
//从intf转换到virt_dev
struct usb_host_virt_dev *usb_mod_interface_to_usbdev(struct usb_interface *intf)
{
    struct usb_host_virt_sub_dev *virt_sub_dev = NULL;

    //struct usb_host_virt_dev * virt_dev = NULL;
    if (!intf)
    {
        hal_log_err("PANIC : usb_mod_interface_to_usbdev () inft == NULL\n");
        return NULL;
    }

    virt_sub_dev = usb_mod_interface_to_virt_sub_dev(intf);

    if (!virt_sub_dev)
    {
        hal_log_err("PANIC : usb_mod_interface_to_usbdev()  virt_sub_dev == NULL\n");
        return NULL;
    }

    return virt_sub_dev->father_dev;
}

//=========================================================
//usb_get_intfdata
void *usb_mod_usb_get_intf_priv_data(struct usb_interface *intf)
{
    if (!intf)
    {
        hal_log_err("PANIC : usb_mod_usb_get_intf_priv_data () inft == NULL\n");
        return NULL;
    }

    if (intf->virt_sub_dev && intf->virt_sub_dev->drv_pirv_data)
    {
        return  intf->virt_sub_dev->drv_pirv_data;
    }
    else
    {
        hal_log_err("PANIC : usb_mod_usb_get_intf_priv_data () intf->virt_sub_dev->drv_pirv_data == NULL\n");
        return NULL;
    }
}

//usb_set_intfdata
void  usb_mod_usb_set_intf_priv_data(struct usb_interface *intf, void *data)
{
    if (!intf)
    {
        hal_log_err("PANIC : usb_mod_usb_set_intf_priv_data () inft == NULL\n");
        return ;
    }

    //  if(intf->virt_sub_dev && intf->virt_sub_dev->drv_pirv_data){
    if (intf->virt_sub_dev)
    {
        intf->virt_sub_dev->drv_pirv_data = data;
    }
    else
    {
        hal_log_err("PANIC : usb_mod_usb_set_intf_priv_data () intf->virt_sub_dev->drv_pirv_data == NULL\n");
    }
}


