/*
 * File      : winusb.c
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-16     ZYH          first version
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtservice.h>
#include <rtdevice.h>
#include <drivers/usb_device.h>
#include "winusb.h"
struct winusb_device
{
    uep_t ep_out;
    uep_t ep_in;
};

typedef struct winusb_device * winusb_device_t;

static struct udevice_descriptor dev_desc =
{
    USB_DESC_LENGTH_DEVICE,     //bLength;
    USB_DESC_TYPE_DEVICE,       //type;
    USB_BCD_VERSION,            //bcdUSB;
    0x00,                       //bDeviceClass;
    0x00,                       //bDeviceSubClass;
    0x00,                       //bDeviceProtocol;
    0x40,                       //bMaxPacketSize0;
    _VENDOR_ID,                 //idVendor;
    _PRODUCT_ID,                //idProduct;
    USB_BCD_DEVICE,             //bcdDevice;
    USB_STRING_MANU_INDEX,      //iManufacturer;
    USB_STRING_PRODUCT_INDEX,   //iProduct;
    USB_STRING_SERIAL_INDEX,    //iSerialNumber;
    USB_DYNAMIC,                //bNumConfigurations;
};
//FS and HS needed
static struct usb_qualifier_descriptor dev_qualifier =
{
    sizeof(dev_qualifier),
    USB_DESC_TYPE_DEVICEQUALIFIER,
    0x0200,
    0x00,
    0x00,
    64,
    0x01,
    0,
};

struct winusb_descriptor _winusb_desc = 
{
#ifdef RT_USB_DEVICE_COMPOSITE
    /* Interface Association Descriptor */
    USB_DESC_LENGTH_IAD,
    USB_DESC_TYPE_IAD,
    USB_DYNAMIC,
    0x01,
    0xFF,
    0x00,
    0x00,
    0x00,
#endif
    /*interface descriptor*/
    USB_DESC_LENGTH_INTERFACE,  //bLength;
    USB_DESC_TYPE_INTERFACE,    //type;
    USB_DYNAMIC,                //bInterfaceNumber;
    0x00,                       //bAlternateSetting;
    0x02,                       //bNumEndpoints
    0xFF,                       //bInterfaceClass;
    0x00,                       //bInterfaceSubClass;
    0x00,                       //bInterfaceProtocol;
    0x00,                       //iInterface;
    /*endpoint descriptor*/
    USB_DESC_LENGTH_ENDPOINT,
    USB_DESC_TYPE_ENDPOINT,
    USB_DYNAMIC | USB_DIR_OUT,
    USB_EP_ATTR_BULK,
    0x40,
    0x00,
    /*endpoint descriptor*/
    USB_DESC_LENGTH_ENDPOINT,
    USB_DESC_TYPE_ENDPOINT,
    USB_DYNAMIC | USB_DIR_IN,
    USB_EP_ATTR_BULK,
    0x40,
    0x00,
};


const static char* _ustring[] =
{
    "Language",
    "RT-Thread Team.",
    "RTT Win USB",
    "32021919830108",
    "Configuration",
    "Interface",
    USB_STRING_OS//must be
};
struct usb_os_proerty winusb_proerty[] = 
{
    USB_OS_PROERTY_DESC(USB_OS_PROERTY_TYPE_REG_SZ,"DeviceInterfaceGUID","{6860DC3C-C05F-4807-8807-1CA861CC1D66}"),
};

struct usb_os_function_comp_id_descriptor winusb_func_comp_id_desc = 
{
    .bFirstInterfaceNumber = USB_DYNAMIC,
    .reserved1          = 0x01,
    .compatibleID       = {'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00},
    .subCompatibleID    = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    .reserved2          = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

static rt_err_t _ep_out_handler(ufunction_t func, rt_size_t size)
{
    struct winusb_device* data = (struct winusb_device*)func->user_data;
    rt_kprintf("recev:%s",data->ep_out->buffer);
    data->ep_in->request.buffer = data->ep_out->buffer;
    data->ep_in->request.size = EP_MAXPACKET(data->ep_out);
    
    data->ep_in->request.req_type = UIO_REQUEST_WRITE;    
    rt_usbd_io_request(func->device, data->ep_in, &data->ep_in->request);
    return RT_EOK;
}

static rt_err_t _ep_in_handler(ufunction_t func, rt_size_t size)
{
    return RT_EOK;
}
static rt_err_t _interface_handler(ufunction_t func, ureq_t setup)
{
    switch(setup->bRequest)
    {
    case 'A':
        switch(setup->wIndex)
        {
        case 0x05:
            usbd_os_proerty_descriptor_send(func,setup,winusb_proerty,sizeof(winusb_proerty)/sizeof(winusb_proerty[0]));
            break;
        }
        break;
    }
    
    return RT_EOK;
}
static rt_err_t _function_enable(ufunction_t func)
{
    RT_ASSERT(func != RT_NULL);
    struct winusb_device* data = (struct winusb_device*)func->user_data;
    data->ep_out->buffer = rt_malloc(0x40);

    data->ep_out->request.buffer = data->ep_out->buffer;
    data->ep_out->request.size = EP_MAXPACKET(data->ep_out);
    
    data->ep_out->request.req_type = UIO_REQUEST_READ_BEST;    
    rt_usbd_io_request(func->device, data->ep_out, &data->ep_out->request);
    return RT_EOK;
}
static rt_err_t _function_disable(ufunction_t func)
{
    RT_ASSERT(func != RT_NULL);
    struct winusb_device* data = (struct winusb_device*)func->user_data;
    if(data->ep_out->buffer != RT_NULL)
    {
        rt_free(data->ep_out->buffer);
        data->ep_out->buffer = RT_NULL;        
    }
    return RT_EOK;
}

static struct ufunction_ops ops =
{
    _function_enable,
    _function_disable,
    RT_NULL,
};

static rt_err_t _winusb_descriptor_config(winusb_desc_t winusb, rt_uint8_t cintf_nr)
{
#ifdef RT_USB_DEVICE_COMPOSITE
    winusb->iad_desc.bFirstInterface = cintf_nr;
#endif
    winusb_func_comp_id_desc.bFirstInterfaceNumber = cintf_nr;
    return RT_EOK;
}
static rt_err_t rt_usb_winusb_init(ufunction_t func)
{
    return RT_EOK;
}

ufunction_t rt_usbd_function_winusb_create(udevice_t device)
{
    ufunction_t         func;
    winusb_device_t     winusb_device;

    uintf_t             winusb_intf;
    ualtsetting_t       winusb_setting;
    winusb_desc_t       winusb_desc;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);

    /* set usb device string description */
    rt_usbd_device_set_string(device, _ustring);

    /* create a cdc function */
    func = rt_usbd_function_new(device, &dev_desc, &ops);
    rt_usbd_device_set_qualifier(device, &dev_qualifier);

    /* allocate memory for cdc vcom data */
    winusb_device = (winusb_device_t)rt_malloc(sizeof(struct winusb_device));
    rt_memset((void *)winusb_device, 0, sizeof(struct winusb_device));
    func->user_data = (void*)winusb_device;

    /* create an interface object */
    winusb_intf = rt_usbd_interface_new(device, _interface_handler);

    /* create an alternate setting object */
    winusb_setting = rt_usbd_altsetting_new(sizeof(struct winusb_descriptor));

    /* config desc in alternate setting */
    rt_usbd_altsetting_config_descriptor(winusb_setting, &_winusb_desc, (rt_off_t)&((winusb_desc_t)0)->intf_desc);

    /* configure the hid interface descriptor */
    _winusb_descriptor_config(winusb_setting->desc, winusb_intf->intf_num);

    /* create endpoint */
    winusb_desc = (winusb_desc_t)winusb_setting->desc;
    winusb_device->ep_out = rt_usbd_endpoint_new(&winusb_desc->ep_out_desc, _ep_out_handler);
    winusb_device->ep_in  = rt_usbd_endpoint_new(&winusb_desc->ep_in_desc, _ep_in_handler);

    /* add the int out and int in endpoint to the alternate setting */
    rt_usbd_altsetting_add_endpoint(winusb_setting, winusb_device->ep_out);
    rt_usbd_altsetting_add_endpoint(winusb_setting, winusb_device->ep_in);

    /* add the alternate setting to the interface, then set default setting */
    rt_usbd_interface_add_altsetting(winusb_intf, winusb_setting);
    rt_usbd_set_altsetting(winusb_intf, 0);

    /* add the interface to the mass storage function */
    rt_usbd_function_add_interface(func, winusb_intf);

    rt_usbd_os_comp_id_desc_add_os_func_comp_id_desc(device->os_comp_id_desc, &winusb_func_comp_id_desc);
    /* initilize hid */
    rt_usb_winusb_init(func);
    return func;
}

