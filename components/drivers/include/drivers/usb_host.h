/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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

#define DEV_STATUS_IDLE                 0x00
#define DEV_STATUS_BUSY                 0x01
#define DEV_STATUS_ERROR                0x02

#define UPIPE_STATUS_OK                 0x00
#define UPIPE_STATUS_STALL              0x01
#define UPIPE_STATUS_ERROR              0x02

#define USBH_PID_SETUP                  0x00
#define USBH_PID_DATA                   0x01

struct uhcd;
struct uhintf;
struct uhub;
struct upipe;

struct uclass_driver
{
    rt_list_t list;
    int class_code;
    int subclass_code;
    
    rt_err_t (*enable)(void* arg);
    rt_err_t (*disable)(void* arg);
    
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
    struct rt_device parent;

    struct udevice_descriptor dev_desc;
    ucfg_desc_t cfg_desc;
    struct uhcd *hcd;

    struct upipe * pipe_ep0_out;
    struct upipe * pipe_ep0_in;
    rt_list_t pipe;

    rt_uint8_t status;
    rt_uint8_t type;
    rt_uint8_t index;
    rt_uint8_t address;    
    rt_uint8_t speed;
    rt_uint8_t max_packet_size;    
    rt_uint8_t port;

    struct uhub* parent_hub;
    struct uhintf* intf[USB_MAX_INTERFACE];        
};
typedef struct uinstance* uinst_t;

struct uhintf
{
    struct uinstance* device;
    uintf_desc_t intf_desc;

    ucd_t drv;
    void *user_data;
};

struct upipe
{
    rt_list_t list;
    rt_uint8_t pipe_index;
    rt_uint32_t status;
    struct uendpoint_descriptor ep;
    uinst_t inst;
    func_callback callback;
    void* user_data;
};
typedef struct upipe* upipe_t;

struct uhub
{
    struct uhub_descriptor hub_desc;
    rt_uint8_t num_ports;
    rt_uint32_t port_status[USB_HUB_PORT_NUM];
    struct uinstance* child[USB_HUB_PORT_NUM];        

    rt_bool_t is_roothub;

    rt_uint8_t buffer[8];    
    struct uinstance* self;
    struct uhcd *hcd;
};    
typedef struct uhub* uhub_t;

struct uhcd_ops
{
    rt_err_t    (*reset_port)   (rt_uint8_t port);
    int         (*pipe_xfer)    (upipe_t pipe, rt_uint8_t token, void* buffer, int nbytes, int timeout);
    rt_err_t    (*open_pipe)    (upipe_t pipe);
    rt_err_t    (*close_pipe)   (upipe_t pipe);  
};
typedef struct uhcd_ops* uhcd_ops_t;
struct uhcd
{
    struct rt_device parent;
    uhcd_ops_t ops;
    rt_uint8_t num_ports;
    uhub_t roothub; 
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
        struct uhub* hub;
        struct 
        {
            func_callback function;
            void *context;
        }cb;
    }content;
};
typedef struct uhost_msg* uhost_msg_t;

/* usb host system interface */
rt_err_t rt_usb_host_init(void);
void rt_usbh_hub_init(struct uhcd *hcd);

/* usb host core interface */
struct uinstance* rt_usbh_alloc_instance(uhcd_t uhcd);
rt_err_t rt_usbh_attatch_instance(struct uinstance* device);
rt_err_t rt_usbh_detach_instance(struct uinstance* device);
rt_err_t rt_usbh_get_descriptor(struct uinstance* device, rt_uint8_t type, void* buffer, int nbytes);
rt_err_t rt_usbh_set_configure(struct uinstance* device, int config);
rt_err_t rt_usbh_set_address(struct uinstance* device);
rt_err_t rt_usbh_set_interface(struct uinstance* device, int intf);
rt_err_t rt_usbh_clear_feature(struct uinstance* device, int endpoint, int feature);
rt_err_t rt_usbh_get_interface_descriptor(ucfg_desc_t cfg_desc, int num, uintf_desc_t* intf_desc);
rt_err_t rt_usbh_get_endpoint_descriptor(uintf_desc_t intf_desc, int num, uep_desc_t* ep_desc);

/* usb class driver interface */
rt_err_t rt_usbh_class_driver_init(void);
rt_err_t rt_usbh_class_driver_register(ucd_t drv);
rt_err_t rt_usbh_class_driver_unregister(ucd_t drv);
rt_err_t rt_usbh_class_driver_enable(ucd_t drv, void* args);
rt_err_t rt_usbh_class_driver_disable(ucd_t drv, void* args);
ucd_t rt_usbh_class_driver_find(int class_code, int subclass_code);

/* usb class driver implement */
ucd_t rt_usbh_class_driver_hub(void);
ucd_t rt_usbh_class_driver_storage(void);



/* usb hub interface */
rt_err_t rt_usbh_hub_get_descriptor(struct uinstance* device, rt_uint8_t *buffer, 
    rt_size_t size);
rt_err_t rt_usbh_hub_get_status(struct uinstance* device, rt_uint32_t* buffer);
rt_err_t rt_usbh_hub_get_port_status(uhub_t uhub, rt_uint16_t port, 
    rt_uint32_t* buffer);
rt_err_t rt_usbh_hub_clear_port_feature(uhub_t uhub, rt_uint16_t port, 
    rt_uint16_t feature);
rt_err_t rt_usbh_hub_set_port_feature(uhub_t uhub, rt_uint16_t port, 
    rt_uint16_t feature);
rt_err_t rt_usbh_hub_reset_port(uhub_t uhub, rt_uint16_t port);
rt_err_t rt_usbh_event_signal(struct uhost_msg* msg);


void rt_usbh_root_hub_connect_handler(struct uhcd *hcd, rt_uint8_t port, rt_bool_t isHS);
void rt_usbh_root_hub_disconnect_handler(struct uhcd *hcd, rt_uint8_t port);

/* usb host controller driver interface */
rt_inline rt_err_t rt_usb_instance_add_pipe(uinst_t inst, upipe_t pipe)
{
    RT_ASSERT(inst != RT_NULL);
    RT_ASSERT(pipe != RT_NULL);
    rt_list_insert_before(&inst->pipe, &pipe->list);
    return RT_EOK;
}
rt_inline upipe_t rt_usb_instance_find_pipe(uinst_t inst,rt_uint8_t ep_address)
{
    rt_list_t * l;
    for(l = inst->pipe.next;l != &inst->pipe;l = l->next)
    {
        if(rt_list_entry(l,struct upipe,list)->ep.bEndpointAddress == ep_address)
        {
            return rt_list_entry(l,struct upipe,list);
        }
    }
    return RT_NULL;
}
rt_inline rt_err_t rt_usb_hcd_alloc_pipe(uhcd_t hcd, upipe_t* pipe, uinst_t inst, uep_desc_t ep)
{
    *pipe = (upipe_t)rt_malloc(sizeof(struct upipe));
    if(*pipe == RT_NULL)
    {
        return RT_ERROR;
    }
    rt_memset(*pipe,0,sizeof(struct upipe));
    (*pipe)->inst = inst;
    rt_memcpy(&(*pipe)->ep,ep,sizeof(struct uendpoint_descriptor));
    return hcd->ops->open_pipe(*pipe);
}
rt_inline void rt_usb_pipe_add_callback(upipe_t pipe, func_callback callback)
{
    pipe->callback = callback;
}

rt_inline rt_err_t rt_usb_hcd_free_pipe(uhcd_t hcd, upipe_t pipe)
{
    RT_ASSERT(pipe != RT_NULL);
    hcd->ops->close_pipe(pipe);
    rt_free(pipe);
    return RT_EOK;
}

int rt_usb_hcd_pipe_xfer(uhcd_t hcd, upipe_t pipe, void* buffer, int nbytes, int timeout);
rt_inline int rt_usb_hcd_setup_xfer(uhcd_t hcd, upipe_t pipe, ureq_t setup, int timeout)
{
    return hcd->ops->pipe_xfer(pipe, USBH_PID_SETUP, (void *)setup, 8, timeout);
}

#ifdef __cplusplus
}
#endif

#endif


