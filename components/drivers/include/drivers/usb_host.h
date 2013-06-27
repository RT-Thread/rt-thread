/*
 * File      : usb_host.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2011, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-3-12     Yi Qiu      first version
 */

#ifndef __RT_USB_HOST_H__
#define __RT_USB_HOST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rtthread.h>
#include "usb_common.h"

#define USB_MAX_DEVICE                  0x20
#define USB_MAX_INTERFACE               0x08
#define USB_HUB_PORT_NUM                0x04
#define SIZEOF_USB_REQUEST              0x08

#define UINST_STATUS_IDLE               0x00
#define UINST_STATUS_BUSY               0x01
#define UINST_STATUS_ERROR              0x02

#define UPIPE_STATUS_OK                 0x00
#define UPIPE_STATUS_STALL              0x01
#define UPIPE_STATUS_ERROR              0x02

struct uhcd;
struct uifinst;
struct uhubinst;

struct uclass_driver
{
    rt_list_t list;
    int class_code;
    int subclass_code;
    
    rt_err_t (*run)(void* arg);
    rt_err_t (*stop)(void* arg);
    
    void* user_data;
};
typedef struct uclass_driver* ucd_t;

struct uprotocal
{
    rt_list_t list;
    int pro_id;
    
    rt_err_t (*init)(void* arg);
    rt_err_t (*callback)(void* arg);    
};
typedef struct uprotocal* uprotocal_t;

struct uinstance
{
    struct udevice_descriptor dev_desc;
    ucfg_desc_t cfg_desc;
    struct uhcd *hcd;

    rt_uint8_t status;
    rt_uint8_t type;
    rt_uint8_t index;
    rt_uint8_t address;    
    rt_uint8_t speed;
    rt_uint8_t max_packet_size;    
    rt_uint8_t port;

    struct uhubinst* parent;
    struct uifinst* ifinst[USB_MAX_INTERFACE];        
};
typedef struct uinstance* uinst_t;

struct uifinst
{
    uinst_t uinst;
    uintf_desc_t intf_desc;

    ucd_t drv;
    void *user_data;
};
typedef struct uifinst* uifinst_t;

struct upipe
{
    rt_uint32_t status;
    struct uendpoint_descriptor ep;
    uifinst_t ifinst;
    func_callback callback;
    void* user_data;
};
typedef struct upipe* upipe_t;

struct uhubinst
{
    struct uhub_descriptor hub_desc;
    rt_uint8_t num_ports;
    rt_uint32_t port_status[USB_HUB_PORT_NUM];
    struct uinstance* child[USB_HUB_PORT_NUM];        

    rt_bool_t is_roothub;
    upipe_t pipe_in;
    rt_uint8_t buffer[8];    
    struct uinstance* self;
    struct uhcd *hcd;    
};    
typedef struct uhubinst* uhubinst_t;

struct uhcd_ops
{
    int (*ctl_xfer)(uinst_t inst, ureq_t setup, void* buffer, int nbytes, 
        int timeout);
    int (*bulk_xfer)(upipe_t pipe, void* buffer, int nbytes, int timeout);
    int (*int_xfer)(upipe_t pipe, void* buffer, int nbytes, int timeout);
    int (*iso_xfer)(upipe_t pipe, void* buffer, int nbytes, int timeout);
    
    rt_err_t (*alloc_pipe)(struct upipe** pipe, uifinst_t ifinst, uep_desc_t ep, 
        func_callback callback);
    rt_err_t (*free_pipe)(upipe_t pipe);    
    rt_err_t (*hub_ctrl)(rt_uint16_t port, rt_uint8_t cmd, void *args);    
};

struct uhcd
{
    struct rt_device parent;
    struct uhcd_ops* ops;
};
typedef struct uhcd* uhcd_t;

enum uhost_msg_type
{
    USB_MSG_CONNECT_CHANGE,
    USB_MSG_CALLBACK,
};
typedef enum uhost_msg_type uhost_msg_type;

struct uhost_msg
{
    uhost_msg_type type; 
    union
    {
        struct uhubinst* uhub;
        struct 
        {
            func_callback function;
            void *context;
        }cb;
    }content;
};
typedef struct uhost_msg* uhost_msg_t;

/* usb host system interface */
void rt_usb_host_init(void);
void rt_usb_hub_thread(void);

/* usb host core interface */
uinst_t rt_usb_alloc_instance(void);
rt_err_t rt_usb_attatch_instance(uinst_t uinst);
rt_err_t rt_usb_detach_instance(uinst_t uinst);
rt_err_t rt_usb_get_descriptor(uinst_t    uinst,
                               rt_uint8_t type,
                               void      *buffer, 
                               int        nbytes);
rt_err_t rt_usb_set_configure(uinst_t uinst, int config);
rt_err_t rt_usb_set_address(uinst_t uinst);
rt_err_t rt_usb_set_interface(uinst_t uinst, int intf);
rt_err_t rt_usb_clear_feature(uinst_t uinst, int endpoint, int feature);
rt_err_t rt_usb_get_interface_descriptor(ucfg_desc_t   cfg_desc,
                                         int           num,
                                         uintf_desc_t *intf_desc);
rt_err_t rt_usb_get_endpoint_descriptor(uintf_desc_t intf_desc,
                                        int          num, 
                                        uep_desc_t  *ep_desc);

/* usb class driver interface */
rt_err_t rt_usb_class_driver_init(void);
rt_err_t rt_usb_class_driver_register(ucd_t drv);
rt_err_t rt_usb_class_driver_unregister(ucd_t drv);
rt_err_t rt_usb_class_driver_run(ucd_t drv, void *args);
rt_err_t rt_usb_class_driver_stop(ucd_t drv, void *args);
ucd_t rt_usb_class_driver_find(int class_code, int subclass_code);

/* usb class driver implement */
ucd_t rt_usb_class_driver_hid(void);
ucd_t rt_usb_class_driver_hub(void);
ucd_t rt_usb_class_driver_storage(void);
ucd_t rt_usb_class_driver_adk(void);

/* usb hid protocal implement */
uprotocal_t rt_usb_hid_protocal_kbd(void);
uprotocal_t rt_usb_hid_protocal_mouse(void);

/* usb adk class driver interface */
rt_err_t rt_usb_adk_set_string(const char *manufacturer,
                               const char *model,
                               const char *description,
                               const char *version,
                               const char *uri, 
                               const char *serial);

/* usb hub interface */
rt_err_t rt_usb_hub_get_descriptor(uinst_t     uinst,
                                   rt_uint8_t *buffer, 
                                   rt_size_t   size);
rt_err_t rt_usb_hub_get_status(uinst_t uinst, rt_uint8_t *buffer);
rt_err_t rt_usb_hub_get_port_status(uhubinst_t  uhub,
                                    rt_uint16_t port, 
                                    rt_uint8_t *buffer);
rt_err_t rt_usb_hub_clear_port_feature(uhubinst_t  uhub,
                                       rt_uint16_t port, 
                                       rt_uint16_t feature);
rt_err_t rt_usb_hub_set_port_feature(uhubinst_t  uhub,
                                     rt_uint16_t port, 
                                     rt_uint16_t feature);
rt_err_t rt_usb_hub_reset_port(uhubinst_t uhub, rt_uint16_t port);
rt_err_t rt_usb_post_event(struct uhost_msg* msg, rt_size_t size);

/* usb host controller driver interface */
rt_inline rt_err_t rt_usb_hcd_alloc_pipe(uhcd_t        hcd,
                                         upipe_t      *pipe, 
                                         uifinst_t     ifinst,
                                         uep_desc_t    ep,
                                         func_callback callback)
{
    if (ifinst == RT_NULL)
        return -RT_EIO;

    return hcd->ops->alloc_pipe(pipe, ifinst, ep, callback);
}

rt_inline rt_err_t rt_usb_hcd_free_pipe(uhcd_t hcd, upipe_t pipe)
{
    RT_ASSERT(pipe != RT_NULL);
    
    return hcd->ops->free_pipe(pipe);
}

rt_inline int rt_usb_hcd_bulk_xfer(uhcd_t  hcd,
                                   upipe_t pipe,
                                   void   *buffer, 
                                   int     nbytes,
                                   int     timeout)
{
    if (pipe == RT_NULL)
        return -1;
    if (pipe->ifinst == RT_NULL)
        return -1;
    if (pipe->ifinst->uinst == RT_NULL)
        return -1;    
    if (pipe->ifinst->uinst->status == UINST_STATUS_IDLE) 
        return -1;

    return hcd->ops->bulk_xfer(pipe, buffer, nbytes, timeout);
}

rt_inline int rt_usb_hcd_control_xfer(uhcd_t  hcd,
                                      uinst_t uinst,
                                      ureq_t  setup, 
                                      void   *buffer,
                                      int     nbytes,
                                      int     timeout)
{
    if (uinst->status == UINST_STATUS_IDLE)
        return -1;

    return hcd->ops->ctl_xfer(uinst, setup, buffer, nbytes, timeout);
}

rt_inline int rt_usb_hcd_int_xfer(uhcd_t  hcd,
                                  upipe_t pipe,
                                  void   *buffer, 
                                  int     nbytes,
                                  int     timeout)
{    
    if (pipe == RT_NULL)
        return -1;
    if (pipe->ifinst == RT_NULL)
        return -1;
    if (pipe->ifinst->uinst == RT_NULL)
        return -1;    
    if (pipe->ifinst->uinst->status == UINST_STATUS_IDLE) 
        return -1;

    return hcd->ops->int_xfer(pipe, buffer, nbytes, timeout);
}

rt_inline rt_err_t rt_usb_hcd_hub_control(uhcd_t      hcd,
                                          rt_uint16_t port, 
                                          rt_uint8_t  cmd,
                                          void       *args)
{    
    return hcd->ops->hub_ctrl(port, cmd, args);
}

#ifdef __cplusplus
}
#endif

#endif

