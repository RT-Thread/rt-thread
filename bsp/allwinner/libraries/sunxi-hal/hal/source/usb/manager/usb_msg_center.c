#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <rtthread.h>
#include <init.h>
#include <typedef.h>
#include <kapi.h>
#include <log.h>
#include <usb/sunxi_hal_udc.h>
#include <usb/hal_hci.h>
#include "usb_msg_center.h"
#include "usb_manager_common.h"

static struct usb_msg_center_info g_center_info;
enum usb_role get_usb_role(void)
{
    return g_center_info.role;
}
static void set_usb_role(struct usb_msg_center_info *center_info, enum usb_role role)
{
    Usb_Manager_INFO("role:%d \n", role);
    center_info->role = role;
}

static void insmod_host_driver(struct usb_msg_center_info *center_info)
{
    Usb_Manager_INFO("\n");
    set_usb_role(center_info, USB_ROLE_HOST);
    hal_usb_hcd_init(0);
}

static void rmmod_host_driver(struct usb_msg_center_info *center_info)
{
    Usb_Manager_INFO("\n");
    set_usb_role(center_info, USB_ROLE_NULL);
    /*TODO*/
    hal_usb_hcd_deinit(0);
}

static void insmod_device_driver(struct usb_msg_center_info *center_info)
{
#ifdef CONFIG_COMPONENT_ADBD
    extern int adbd_main(void);
#endif
    Usb_Manager_Err(" adbd_main\n");
    set_usb_role(center_info, USB_ROLE_DEVICE);
#ifdef CONFIG_COMPONENT_ADBD
    adbd_main();
#endif
}

static void rmmod_device_driver(struct usb_msg_center_info *center_info)
{
#ifdef CONFIG_COMPONENT_ADBD
    extern int adbd_exit(void);
#endif
    Usb_Manager_Err("\n");
    set_usb_role(center_info, USB_ROLE_NULL);
#ifdef CONFIG_COMPONENT_ADBD
    adbd_exit();
#endif
    Usb_Manager_Err("\n");
}

static void do_usb_role_null(struct usb_msg_center_info *center_info)
{
    if (center_info->msg.hw_insmod_host)
    {
        insmod_host_driver(center_info);
        center_info->msg.hw_insmod_host = 0;

        goto end;
    }

    if (center_info->msg.hw_insmod_device)
    {
        insmod_device_driver(center_info);
        center_info->msg.hw_insmod_device = 0;

        goto end;
    }

end:
    memset(&center_info->msg, 0, sizeof(struct usb_msg));
}

static void do_usb_role_host(struct usb_msg_center_info *center_info)
{
    if (center_info->msg.hw_rmmod_host)
    {
        rmmod_host_driver(center_info);
        center_info->msg.hw_rmmod_host = 0;
        goto end;
    }

end:
    memset(&center_info->msg, 0, sizeof(struct usb_msg));
}

static void do_usb_role_device(struct usb_msg_center_info *center_info)
{
    if (center_info->msg.hw_rmmod_device)
    {
        rmmod_device_driver(center_info);
        center_info->msg.hw_rmmod_device = 0;
        goto end;
    }

end:
    memset(&center_info->msg, 0, sizeof(struct usb_msg));
}
static void modify_msg(struct usb_msg *msg)
{
    if (msg->hw_insmod_host && msg->hw_rmmod_host)
    {
        msg->hw_insmod_host = 0;
        msg->hw_rmmod_host  = 0;
    }

    if (msg->hw_insmod_device && msg->hw_rmmod_device)
    {
        msg->hw_insmod_device = 0;
        msg->hw_rmmod_device  = 0;
    }
}
void usb_msg_center(usb_cfg_t *cfg)
{
    enum usb_role role = USB_ROLE_NULL;
    struct usb_msg_center_info *center_info = &g_center_info;

    center_info->cfg = cfg;

    /* receive massage */
    modify_msg(&center_info->msg);
    /* execute cmd */
    role = get_usb_role();
    Usb_Manager_Debug("role=%d\n", get_usb_role());
    switch (role)
    {
        case USB_ROLE_NULL:
            do_usb_role_null(center_info);
            break;

        case USB_ROLE_HOST:
            do_usb_role_host(center_info);
            break;

        case USB_ROLE_DEVICE:
            do_usb_role_device(center_info);
            break;

        default:
            Usb_Manager_Err("ERR: unknown role(%x)\n", role);
    }
}

int usb_msg_center_init(void)
{
    struct usb_msg_center_info *center_info = &g_center_info;

    memset(center_info, 0, sizeof(struct usb_msg_center_info));
    return 0;
}

int usb_msg_center_exit(void)
{
    struct usb_msg_center_info *center_info = &g_center_info;

    memset(center_info, 0, sizeof(struct usb_msg_center_info));
    return 0;
}

void hw_insmod_usb_host(void)
{
    g_center_info.msg.hw_insmod_host = 1;
}

void hw_rmmod_usb_host(void)
{
    g_center_info.msg.hw_rmmod_host = 1;
}

void hw_insmod_usb_device(void)
{
    g_center_info.msg.hw_insmod_device = 1;
}

void hw_rmmod_usb_device(void)
{
    g_center_info.msg.hw_rmmod_device = 1;
}
