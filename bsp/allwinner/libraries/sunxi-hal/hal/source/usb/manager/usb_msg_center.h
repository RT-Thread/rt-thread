#ifndef __USB_MSG_CENTER_H__
#define __USB_MSG_CENTER_H__
#include <typedef.h>
#include "usb_msg_center.h"
#include "sunxi_usb_board.h"

typedef enum usb_role
{
    USB_ROLE_NULL = 0,
    USB_ROLE_HOST,
    USB_ROLE_DEVICE,
} usb_role_t;

typedef struct usb_msg
{
    u8  hw_insmod_host;
    u8  hw_rmmod_host;
    u8  hw_insmod_device;
    u8  hw_rmmod_device;
} usb_msg_t;

typedef struct usb_msg_center_info
{
    struct usb_cfg *cfg;

    struct usb_msg msg;
    enum usb_role role;

    u32 skip;           /* if skip, not enter msg process */
    /* mainly to omit invalid msg */
} usb_msg_center_info_t;
enum usb_role get_usb_role(void);
int usb_msg_center_init(void);
int usb_msg_center_exit(void);
void usb_msg_center(usb_cfg_t *cfg);
void hw_insmod_usb_host(void);
void hw_insmod_usb_device(void);
void hw_rmmod_usb_host(void);
void hw_rmmod_usb_device(void);
#endif
