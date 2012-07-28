/*
 * File      : usb_host.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
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

#define RT_DEBUG_USB                    0x01

#define USB_MAX_DEVICE                    0x20
#define USB_MAX_INTERFACE                0x08
#define USB_HUB_PORT_NUM                0x04
#define SIZEOF_USB_REQUEST                0x08

#define UINST_STATUS_IDLE                0x00
#define UINST_STATUS_BUSY                0x01
#define UINST_STATUS_ERROR                0x02

#define UPIPE_STATUS_OK                    0x00
#define UPIPE_STATUS_STALL                0x01
#define UPIPE_STATUS_ERROR                0x02

#define USB_CLASS_DEVICE                  0x00
#define USB_CLASS_AUDIO                    0x01
#define USB_CLASS_CDC                      0x02
#define USB_CLASS_HID                      0x03
#define USB_CLASS_PHYSICAL                0x05
#define USB_CLASS_IMAGE                    0x06
#define USB_CLASS_PRINTER                 0x07
#define USB_CLASS_MASS_STORAGE          0x08
#define USB_CLASS_HUB                      0x09
#define USB_CLASS_CDC_DATA                0x0a
#define USB_CLASS_SMART_CARD             0x0b
#define USB_CLASS_SECURITY                0x0d
#define USB_CLASS_VIDEO                    0x0e
#define USB_CLASS_HEALTHCARE             0x0f
#define USB_CLASS_DIAG_DEVICE            0xdc
#define USB_CLASS_WIRELESS                0xe0
#define USB_CLASS_MISC                     0xef
#define USB_CLASS_APP_SPECIFIC          0xfe
#define USB_CLASS_VEND_SPECIFIC         0xff

#define USB_DESC_TYPE_DEVICE            0x01
#define USB_DESC_TYPE_CONFIGURATION        0x02
#define USB_DESC_TYPE_STRING            0x03
#define USB_DESC_TYPE_INTERFACE            0x04
#define USB_DESC_TYPE_ENDPOINT            0x05
#define USB_DESC_TYPE_DEVICEQUALIFIER    0x06
#define USB_DESC_TYPE_OTHERSPEED        0x07
#define USB_DESC_TYPE_HID                 0x21
#define USB_DESC_TYPE_REPORT             0x22
#define USB_DESC_TYPE_PHYSICAL          0x23
#define USB_DESC_TYPE_HUB                  0x29

#define USB_REQ_TYPE_STANDARD            0x00
#define USB_REQ_TYPE_CLASS                0x20
#define USB_REQ_TYPE_VENDOR              0x40
#define USB_REQ_TYPE_TYPE_MASK            0x60

#define USB_REQ_TYPE_DIR_OUT            0x00
#define USB_REQ_TYPE_DIR_IN                0x80

#define USB_REQ_TYPE_DEVICE              0x00
#define USB_REQ_TYPE_INTERFACE          0x01
#define USB_REQ_TYPE_ENDPOINT            0x02
#define USB_REQ_TYPE_OTHER                0x03
#define USB_REQ_TYPE_RECIPIENT_MASK        0x1f

#define USB_FEATURE_ENDPOINT_HALT        0x00
#define USB_FEATURE_DEV_REMOTE_WAKEUP    0x01
#define USB_FEATURE_TEST_MODE            0x02

#define USB_REQ_GET_STATUS                0x00
#define USB_REQ_CLEAR_FEATURE            0x01
#define USB_REQ_SET_FEATURE                0x03
#define USB_REQ_SET_ADDRESS                0x05
#define USB_REQ_GET_DESCRIPTOR            0x06
#define USB_REQ_SET_DESCRIPTOR            0x07
#define USB_REQ_GET_CONFIGURATION        0x08
#define USB_REQ_SET_CONFIGURATION        0x09
#define USB_REQ_GET_INTERFACE            0x0A
#define USB_REQ_SET_INTERFACE            0x0B
#define USB_REQ_SYNCH_FRAME                0x0C
#define USB_REQ_SET_ENCRYPTION            0x0D
#define USB_REQ_GET_ENCRYPTION            0x0E
#define USB_REQ_RPIPE_ABORT                0x0E
#define USB_REQ_SET_HANDSHAKE            0x0F
#define USB_REQ_RPIPE_RESET                0x0F
#define USB_REQ_GET_HANDSHAKE            0x10
#define USB_REQ_SET_CONNECTION            0x11
#define USB_REQ_SET_SECURITY_DATA        0x12
#define USB_REQ_GET_SECURITY_DATA        0x13
#define USB_REQ_SET_WUSB_DATA            0x14
#define USB_REQ_LOOPBACK_DATA_WRITE        0x15
#define USB_REQ_LOOPBACK_DATA_READ        0x16
#define USB_REQ_SET_INTERFACE_DS        0x17

#define USB_PID_OUT                      0x01
#define USB_PID_ACK                      0x02
#define USB_PID_DATA0                    0x03
#define USB_PID_SOF                      0x05
#define USB_PID_IN                        0x09
#define USB_PID_NACK                     0x0A
#define USB_PID_DATA1                    0x0B
#define USB_PID_PRE                      0x0C
#define USB_PID_SETUP                    0x0D
#define USB_PID_STALL                    0x0E

#define USB_EP_DESC_OUT                    0x00
#define USB_EP_DESC_IN                    0x80
#define USB_EP_DESC_NUM_MASK            0x0f

#define USB_EP_ATTR_CONTROL                0x00
#define USB_EP_ATTR_ISOC                0x01
#define USB_EP_ATTR_BULK                0x02
#define USB_EP_ATTR_INT                    0x03
#define USB_EP_ATTR_TYPE_MASK            0x03

#define USB_EPNO_MASK                     0x7f
#define USB_DIR_OUT                     0x00
#define USB_DIR_IN                         0x80
#define USB_DIR_MASK                      0x80

#define RH_GET_PORT_STATUS                0
#define RH_SET_PORT_STATUS                1
#define RH_CLEAR_PORT_FEATURE            2
#define RH_SET_PORT_FEATURE                3

/*
 * Port feature numbers
 */
#define PORT_FEAT_CONNECTION            0
#define PORT_FEAT_ENABLE                1
#define PORT_FEAT_SUSPEND                2
#define PORT_FEAT_OVER_CURRENT            3
#define PORT_FEAT_RESET                    4
#define PORT_FEAT_POWER                    8
#define PORT_FEAT_LOWSPEED                9
#define PORT_FEAT_HIGHSPEED                10
#define PORT_FEAT_C_CONNECTION            16
#define PORT_FEAT_C_ENABLE                17
#define PORT_FEAT_C_SUSPEND                18
#define PORT_FEAT_C_OVER_CURRENT        19
#define PORT_FEAT_C_RESET                20

/*
    The HcRhPortStatus[1:NDP] register is used to control and report port events on a per-port
    basis. NumberDownstreamPorts represents the number of HcRhPortStatus registers that are
    implemented in hardware.  The lower word is used to reflect the port status, whereas the upper
    word reflects the status change bits.  Some status bits are implemented with special write behavior
    (see below).  If a transaction (token through handshake) is in progress when a write to change
    port status occurs, the resulting port status change must be postponed until the transaction
    completes.  Reserved bits should always be written '0'.
*/
#define PORT_CCS                        0x00000001UL    /* R:CurrentConnectStatus - W:ClearPortEnable    */
#define PORT_PES                        0x00000002UL    /* R:PortEnableStatus - W:SetPortEnable             */
#define PORT_PSS                           0x00000004UL    /* R:PortSuspendStatus - W:SetPortSuspend        */
#define PORT_POCI                       0x00000008UL    /* R:PortOverCurrentIndicator - W:ClearSuspendStatus    */
#define PORT_PRS                         0x00000010UL    /* R:PortResetStatus - W: SetPortReset            */
#define PORT_PPS                         0x00000100UL    /* R:PortPowerStatus - W: SetPortPower            */
#define PORT_LSDA                         0x00000200UL    /* R:LowSpeedDeviceAttached - W:ClearPortPower    */
#define PORT_CCSC                        0x00010000UL
#define PORT_PESC                        0x00020000UL
#define PORT_PSSC                        0x00040000UL
#define PORT_POCIC                        0x00080000UL
#define PORT_PRSC                        0x00100000UL

/*
 *Hub Status & Hub Change bit masks
 */
#define HUB_STATUS_LOCAL_POWER            0x0001
#define HUB_STATUS_OVERCURRENT            0x0002

#define HUB_CHANGE_LOCAL_POWER            0x0001
#define HUB_CHANGE_OVERCURRENT            0x0002

#define USB_EP_ATTR(attr)                 (attr & USB_EP_ATTR_TYPE_MASK)
#define USB_EP_DESC_NUM(addr)            (addr & USB_EP_DESC_NUM_MASK)

#define uswap_32(x) \
    ((((x) & 0xff000000) >> 24) | \
     (((x) & 0x00ff0000) >>  8) | \
     (((x) & 0x0000ff00) <<  8) | \
     (((x) & 0x000000ff) << 24))

typedef void (*func_callback)(void *context);

struct uhcd;
struct uifinst;
struct uhubinst;

enum umsg_type
{
    USB_MSG_CONNECT_CHANGE,
    USB_MSG_CALLBACK,
};
typedef enum umsg_type umsg_type;

struct usb_descriptor
{
    rt_uint8_t bLength;
    rt_uint8_t type;
};
typedef struct usb_descriptor* udesc_t;

struct udevice_descriptor 
{
    rt_uint8_t bLength;
    rt_uint8_t type;
    rt_uint16_t bcdUSB;
    rt_uint8_t bDeviceClass;
    rt_uint8_t bDeviceSubClass;
    rt_uint8_t bDeviceProtocol;
    rt_uint8_t bMaxPacketSize0;
    rt_uint16_t idVendor;
    rt_uint16_t idProduct;
    rt_uint16_t bcdDevice;
    rt_uint8_t iManufacturer;
    rt_uint8_t iProduct;
    rt_uint8_t iSerialNumber;
    rt_uint8_t bNumConfigurations;
};
typedef struct udevice_descriptor* udev_desc_t;

struct uconfig_descriptor 
{
    rt_uint8_t bLength;
    rt_uint8_t type;
    rt_uint16_t wTotalLength;
    rt_uint8_t bNumInterfaces;
    rt_uint8_t bConfigurationValue;
    rt_uint8_t iConfiguration;
    rt_uint8_t bmAttributes;
    rt_uint8_t MaxPower;
};
typedef struct uconfig_descriptor* ucfg_desc_t;

struct uinterface_descriptor 
{
    rt_uint8_t bLength;
    rt_uint8_t type;
    rt_uint8_t bInterfaceNumber;
    rt_uint8_t bAlternateSetting;
    rt_uint8_t bNumEndpoints;
    rt_uint8_t bInterfaceClass;
    rt_uint8_t bInterfaceSubClass;
    rt_uint8_t bInterfaceProtocol;
    rt_uint8_t iInterface;
};
typedef struct uinterface_descriptor* uintf_desc_t;

struct uendpoint_descriptor 
{
    rt_uint8_t bLength;
    rt_uint8_t type;
    rt_uint8_t bEndpointAddress;
    rt_uint8_t bmAttributes;
    rt_uint16_t wMaxPacketSize;
    rt_uint8_t bInterval;
};
typedef struct uendpoint_descriptor* uep_desc_t;

struct ustring_descriptor 
{
    rt_uint8_t bLength;
    rt_uint8_t type;
    rt_uint8_t* String;
};
typedef struct ustring_descriptor* ustr_desc_t;

struct uhub_descriptor 
{
    rt_uint8_t length;
    rt_uint8_t type;
    rt_uint8_t num_ports;
    rt_uint16_t characteristics;    
    rt_uint8_t pwron_to_good;        /* power on to power good */
    rt_uint8_t current;    
    rt_uint8_t removable[8];
    rt_uint8_t pwr_ctl[8];
};
typedef struct uhub_descriptor* uhub_desc_t;

struct ureqest
{
    rt_uint8_t request_type;
    rt_uint8_t request;
    rt_uint16_t value;
    rt_uint16_t index;    
    rt_uint16_t length;
};
typedef struct ureqest* ureq_t;

struct uclass_driver
{
    rt_list_t list;
    int class_code;
    int subclass_code;
    
    rt_err_t (*run)(void* arg);
    rt_err_t (*stop)(void* arg);

    const char* manufacturer;
    const char* model;
    const char* description;
    const char* version;
    const char* uri;
    const char* serial;
    
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

struct umsg
{
    umsg_type type; 
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
typedef struct umsg* umsg_t;

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

/* usb host system interface */
void rt_usb_host_init(void);
void rt_usb_hub_thread(void);

/* usb host core interface */
uinst_t rt_usb_alloc_instance(void);
rt_err_t rt_usb_attatch_instance(uinst_t uinst);
rt_err_t rt_usb_detach_instance(uinst_t uinst);
rt_err_t rt_usb_get_descriptor(uinst_t uinst, rt_uint8_t type, void* buffer, 
    int nbytes);
rt_err_t rt_usb_set_configure(uinst_t uinst, int config);
rt_err_t rt_usb_set_address(uinst_t uinst);
rt_err_t rt_usb_set_interface(uinst_t uinst, int intf);
rt_err_t rt_usb_clear_feature(uinst_t uinst, int endpoint, int feature);
rt_err_t rt_usb_get_interface_descriptor(ucfg_desc_t cfg_desc, int num, 
    uintf_desc_t* intf_desc);
rt_err_t rt_usb_get_endpoint_descriptor(uintf_desc_t intf_desc, int num, 
    uep_desc_t* ep_desc);

/* usb class driver interface */
rt_err_t rt_usb_class_driver_init(void);
rt_err_t rt_usb_class_driver_register(ucd_t drv);
rt_err_t rt_usb_class_driver_unregister(ucd_t drv);
rt_err_t rt_usb_class_driver_run(ucd_t drv, void* args);
rt_err_t rt_usb_class_driver_stop(ucd_t drv, void* args);
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
rt_err_t rt_usb_adk_set_string(const char* manufacturer, const char* model,
    const char* description, const char* version, const char* uri, 
    const char* serial);

/* usb hub interface */
rt_err_t rt_usb_hub_get_descriptor(uinst_t uinst, rt_uint8_t *buffer, 
    rt_size_t size);
rt_err_t rt_usb_hub_get_status(uinst_t uinst, rt_uint8_t* buffer);
rt_err_t rt_usb_hub_get_port_status(uhubinst_t uhub, rt_uint16_t port, 
    rt_uint8_t* buffer);
rt_err_t rt_usb_hub_clear_port_feature(uhubinst_t uhub, rt_uint16_t port, 
    rt_uint16_t feature);
rt_err_t rt_usb_hub_set_port_feature(uhubinst_t uhub, rt_uint16_t port, 
    rt_uint16_t feature);
rt_err_t rt_usb_hub_reset_port(uhubinst_t uhub, rt_uint16_t port);
rt_err_t rt_usb_post_event(struct umsg* msg, rt_size_t size);

/* usb host controller driver interface */
rt_inline rt_err_t rt_usb_hcd_alloc_pipe(uhcd_t hcd, upipe_t* pipe, 
    uifinst_t ifinst, uep_desc_t ep, func_callback callback)
{
    if(ifinst == RT_NULL) return -RT_EIO;

    /* parameter check */
    RT_ASSERT(hcd != RT_NULL);
    RT_ASSERT(hcd->ops != RT_NULL);    
    RT_ASSERT(hcd->ops->alloc_pipe!= RT_NULL);

    return hcd->ops->alloc_pipe(pipe, ifinst, ep, callback);
}

rt_inline rt_err_t rt_usb_hcd_free_pipe(uhcd_t hcd, upipe_t pipe)
{
    RT_ASSERT(pipe != RT_NULL);
    
    /* parameter check */
    RT_ASSERT(hcd != RT_NULL);
    RT_ASSERT(hcd->ops != RT_NULL);    
    RT_ASSERT(hcd->ops->free_pipe!= RT_NULL);

    return hcd->ops->free_pipe(pipe);
}

rt_inline int rt_usb_hcd_bulk_xfer(uhcd_t hcd, upipe_t pipe, void* buffer, 
    int nbytes, int timeout)
{
    if(pipe == RT_NULL) return -1;
    if(pipe->ifinst == RT_NULL) return -1;
    if(pipe->ifinst->uinst == RT_NULL) return -1;    
    if(pipe->ifinst->uinst->status == UINST_STATUS_IDLE) 
        return -1;

    /* parameter check */
    RT_ASSERT(hcd != RT_NULL);
    RT_ASSERT(hcd->ops != RT_NULL);    
    RT_ASSERT(hcd->ops->bulk_xfer!= RT_NULL);

    return hcd->ops->bulk_xfer(pipe, buffer, nbytes, timeout);
}

rt_inline int rt_usb_hcd_control_xfer(uhcd_t hcd, uinst_t uinst, ureq_t setup, 
    void* buffer, int nbytes, int timeout)
{
    if(uinst->status == UINST_STATUS_IDLE) return -1;

    /* parameter check */
    RT_ASSERT(hcd != RT_NULL);
    RT_ASSERT(hcd->ops != RT_NULL);    
    RT_ASSERT(hcd->ops->ctl_xfer!= RT_NULL);        

    return hcd->ops->ctl_xfer(uinst, setup, buffer, nbytes, timeout);
}

rt_inline int rt_usb_hcd_int_xfer(uhcd_t hcd, upipe_t pipe, void* buffer, 
    int nbytes, int timeout)
{    
    if(pipe == RT_NULL) return -1;
    if(pipe->ifinst == RT_NULL) return -1;
    if(pipe->ifinst->uinst == RT_NULL) return -1;    
    if(pipe->ifinst->uinst->status == UINST_STATUS_IDLE) 
        return -1;

    RT_ASSERT(hcd != RT_NULL);
    RT_ASSERT(hcd->ops != RT_NULL);    
    RT_ASSERT(hcd->ops->int_xfer!= RT_NULL);

    return hcd->ops->int_xfer(pipe, buffer, nbytes, timeout);
}

rt_inline rt_err_t rt_usb_hcd_hub_control(uhcd_t hcd, rt_uint16_t port, 
    rt_uint8_t cmd, void *args)
{    
    RT_ASSERT(hcd != RT_NULL);
    RT_ASSERT(hcd->ops != RT_NULL);
    RT_ASSERT(hcd->ops->hub_ctrl != RT_NULL);

    return hcd->ops->hub_ctrl(port, cmd, args);
}

#ifdef __cplusplus
}
#endif

#endif

