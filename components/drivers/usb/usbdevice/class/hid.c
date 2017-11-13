/*
 * File      : hid.c
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017Äê3ÔÂ13ÈÕ     Urey         the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtservice.h>
#include <rtdevice.h>

#include "drivers/usb_common.h"
#include "drivers/usb_device.h"

#include "hid.h"

#ifdef RT_USB_DEVICE_HID

struct hid_s
{
    uep_t ep_in;
    uep_t ep_out;
    int status;

    rt_uint16_t protocol;

    rt_uint8_t  report_buf[MAX_REPORT_SIZE];
};

/* CustomHID_ConfigDescriptor */
const rt_uint8_t _report_desc[] __attribute__ ((packed))=
{
    0x06, 0xFF, 0x00,      /* USAGE_PAGE (Vendor Page: 0xFF00) */
    0x09, 0x01,            /* USAGE (Demo Kit)               */
    0xa1, 0x01,            /* COLLECTION (Application)       */
    /* 6 */

    /* Led 1 */
    0x85, 0x01,            /*     REPORT_ID (1)          */
    0x09, 0x01,            /*     USAGE (LED 1)              */
    0x15, 0x00,            /*     LOGICAL_MINIMUM (0)        */
    0x25, 0x01,            /*     LOGICAL_MAXIMUM (1)        */
    0x75, 0x08,            /*     REPORT_SIZE (8)            */
    0x95, 0x01,            /*     REPORT_COUNT (1)           */
    0xB1, 0x82,             /*    FEATURE (Data,Var,Abs,Vol) */

    0x85, 0x01,            /*     REPORT_ID (1)              */
    0x09, 0x01,            /*     USAGE (LED 1)              */
    0x91, 0x82,            /*     OUTPUT (Data,Var,Abs,Vol)  */
    /* 26 */

    /* Led 2 */
    0x85, 0x02,            /*     REPORT_ID 2            */
    0x09, 0x02,            /*     USAGE (LED 2)              */
    0x15, 0x00,            /*     LOGICAL_MINIMUM (0)        */
    0x25, 0x01,            /*     LOGICAL_MAXIMUM (1)        */
    0x75, 0x08,            /*     REPORT_SIZE (8)            */
    0x95, 0x01,            /*     REPORT_COUNT (1)           */
    0xB1, 0x82,             /*    FEATURE (Data,Var,Abs,Vol) */

    0x85, 0x02,            /*     REPORT_ID (2)              */
    0x09, 0x02,            /*     USAGE (LED 2)              */
    0x91, 0x82,            /*     OUTPUT (Data,Var,Abs,Vol)  */
    /* 46 */

    /* Led 3 */
    0x85, 0x03,            /*     REPORT_ID (3)          */
    0x09, 0x03,            /*     USAGE (LED 3)              */
    0x15, 0x00,            /*     LOGICAL_MINIMUM (0)        */
    0x25, 0x01,            /*     LOGICAL_MAXIMUM (1)        */
    0x75, 0x08,            /*     REPORT_SIZE (8)            */
    0x95, 0x01,            /*     REPORT_COUNT (1)           */
    0xB1, 0x82,             /*    FEATURE (Data,Var,Abs,Vol) */

    0x85, 0x03,            /*     REPORT_ID (3)              */
    0x09, 0x03,            /*     USAGE (LED 3)              */
    0x91, 0x82,            /*     OUTPUT (Data,Var,Abs,Vol)  */
    /* 66 */

    /* Led 4 */
    0x85, 0x04,            /*     REPORT_ID 4)           */
    0x09, 0x04,            /*     USAGE (LED 4)              */
    0x15, 0x00,            /*     LOGICAL_MINIMUM (0)        */
    0x25, 0x01,            /*     LOGICAL_MAXIMUM (1)        */
    0x75, 0x08,            /*     REPORT_SIZE (8)            */
    0x95, 0x01,            /*     REPORT_COUNT (1)           */
    0xB1, 0x82,            /*     FEATURE (Data,Var,Abs,Vol) */

    0x85, 0x04,            /*     REPORT_ID (4)              */
    0x09, 0x04,            /*     USAGE (LED 4)              */
    0x91, 0x82,            /*     OUTPUT (Data,Var,Abs,Vol)  */
    /* 86 */

    /* key Push Button */
    0x85, 0x05,            /*     REPORT_ID (5)              */
    0x09, 0x05,            /*     USAGE (Push Button)        */
    0x15, 0x00,            /*     LOGICAL_MINIMUM (0)        */
    0x25, 0x01,            /*     LOGICAL_MAXIMUM (1)        */
    0x75, 0x01,            /*     REPORT_SIZE (1)            */
    0x81, 0x82,            /*     INPUT (Data,Var,Abs,Vol)   */

    0x09, 0x05,            /*     USAGE (Push Button)        */
    0x75, 0x01,            /*     REPORT_SIZE (1)            */
    0xb1, 0x82,            /*     FEATURE (Data,Var,Abs,Vol) */

    0x75, 0x07,            /*     REPORT_SIZE (7)            */
    0x81, 0x83,            /*     INPUT (Cnst,Var,Abs,Vol)   */
    0x85, 0x05,            /*     REPORT_ID (2)              */

    0x75, 0x07,            /*     REPORT_SIZE (7)            */
    0xb1, 0x83,            /*     FEATURE (Cnst,Var,Abs,Vol) */
    /* 114 */

    /* Tamper Push Button */
    0x85, 0x06,            /*     REPORT_ID (6)              */
    0x09, 0x06,            /*     USAGE (Tamper Push Button) */
    0x15, 0x00,            /*     LOGICAL_MINIMUM (0)        */
    0x25, 0x01,            /*     LOGICAL_MAXIMUM (1)        */
    0x75, 0x01,            /*     REPORT_SIZE (1)            */
    0x81, 0x82,            /*     INPUT (Data,Var,Abs,Vol)   */

    0x09, 0x06,            /*     USAGE (Tamper Push Button) */
    0x75, 0x01,            /*     REPORT_SIZE (1)            */
    0xb1, 0x82,            /*     FEATURE (Data,Var,Abs,Vol) */

    0x75, 0x07,            /*     REPORT_SIZE (7)            */
    0x81, 0x83,            /*     INPUT (Cnst,Var,Abs,Vol)   */
    0x85, 0x06,            /*     REPORT_ID (6)              */

    0x75, 0x07,            /*     REPORT_SIZE (7)            */
    0xb1, 0x83,            /*     FEATURE (Cnst,Var,Abs,Vol) */
    /* 142 */

    /* ADC IN */
    0x85, 0x07,            /*     REPORT_ID (7)              */
    0x09, 0x07,            /*     USAGE (ADC IN)             */
    0x15, 0x00,            /*     LOGICAL_MINIMUM (0)        */
    0x26, 0xff, 0x00,      /*     LOGICAL_MAXIMUM (255)      */
    0x75, 0x08,            /*     REPORT_SIZE (8)            */
    0x81, 0x82,            /*     INPUT (Data,Var,Abs,Vol)   */
    0x85, 0x07,            /*     REPORT_ID (7)              */
    0x09, 0x07,            /*     USAGE (ADC in)             */
    0xb1, 0x82,            /*     FEATURE (Data,Var,Abs,Vol) */
    /* 161 */

    0xc0                    /*     END_COLLECTION              */
}; /* CustomHID_ReportDescriptor */

static struct udevice_descriptor _dev_desc =
{
    USB_DESC_LENGTH_DEVICE,     //bLength;
    USB_DESC_TYPE_DEVICE,       //type;
    USB_BCD_VERSION,            //bcdUSB;
    USB_CLASS_HID,              //bDeviceClass;
    0x00,                       //bDeviceSubClass;
    0x00,                       //bDeviceProtocol;
    64,                         //bMaxPacketSize0;
    _VENDOR_ID,                 //idVendor;
    _PRODUCT_ID,                //idProduct;
    USB_BCD_DEVICE,             //bcdDevice;
    USB_STRING_MANU_INDEX,      //iManufacturer;
    USB_STRING_PRODUCT_INDEX,   //iProduct;
    USB_STRING_SERIAL_INDEX,    //iSerialNumber;
    USB_DYNAMIC,                //bNumConfigurations;
};

static struct usb_qualifier_descriptor _dev_qualifier =
{
    sizeof(_dev_qualifier),
    USB_DESC_TYPE_DEVICEQUALIFIER,
    0x0200,
    USB_CLASS_HID,
    0x00,
    64,
    0x01,
    0,
};

/* hid interface descriptor */
const static struct uhid_comm_descriptor _hid_comm_desc =
{
#ifdef RT_USB_DEVICE_COMPOSITE
    /* Interface Association Descriptor */
    USB_DESC_LENGTH_IAD,
    USB_DESC_TYPE_IAD,
    USB_DYNAMIC,
    0x02,
    0x03,                       /* bInterfaceClass: HID */
    USB_HID_SUBCLASS_NOBOOT,    /* bInterfaceSubClass : 1=BOOT, 0=no boot */
    USB_HID_PROTOCOL_NONE,      /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0x00,
#endif

    /* Interface Descriptor */
    USB_DESC_LENGTH_INTERFACE,
    USB_DESC_TYPE_INTERFACE,
    USB_DYNAMIC,                /* bInterfaceNumber: Number of Interface */
    0x00,                       /* bAlternateSetting: Alternate setting */
    0x02,                       /* bNumEndpoints */
    0x03,                       /* bInterfaceClass: HID */
    USB_HID_SUBCLASS_NOBOOT,    /* bInterfaceSubClass : 1=BOOT, 0=no boot */
    USB_HID_PROTOCOL_NONE,      /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0,                          /* iInterface: Index of string descriptor */

    /* HID Descriptor */
    HID_DESCRIPTOR_SIZE,        /* bLength: HID Descriptor size */
    HID_DESCRIPTOR_TYPE,        /* bDescriptorType: HID */
    0x0110,                     /* bcdHID: HID Class Spec release number */
    0x00,                       /* bCountryCode: Hardware target country */
    0x01,                       /* bNumDescriptors: Number of HID class descriptors to follow */
    0x22,                       /* bDescriptorType */
    sizeof(_report_desc),       /* wItemLength: Total length of Report descriptor */

    /* Endpoint Descriptor IN */
    USB_DESC_LENGTH_ENDPOINT,
    USB_DESC_TYPE_ENDPOINT,
    USB_DYNAMIC | USB_DIR_IN,
    USB_EP_ATTR_INT,
    0x08,
    0x20,

    /* Endpoint Descriptor OUT */
    USB_DESC_LENGTH_ENDPOINT,
    USB_DESC_TYPE_ENDPOINT,
    USB_DYNAMIC | USB_DIR_OUT,
    USB_EP_ATTR_INT,
    0x08,
    0x20,
};


const static char* _ustring[] =
{
    "Language",
    "RT-Thread Team.",
    "RTT HID-Device",
    "32021919830108",
    "Configuration",
    "Interface",
};

#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
static void dump_hex(const rt_uint8_t *ptr, rt_size_t buflen)
{
    unsigned char *buf = (unsigned char*)ptr;
    int i, j;
    for (i=0; i<buflen; i+=16)
    {
        rt_kprintf("%06x: ", i);
        for (j=0; j<16; j++)
            if (i+j < buflen)
                rt_kprintf("%02x ", buf[i+j]);
            else
                rt_kprintf("   ");
        rt_kprintf(" ");
        for (j=0; j<16; j++)
            if (i+j < buflen)
                rt_kprintf("%c", __is_print(buf[i+j]) ? buf[i+j] : '.');
        rt_kprintf("\n");
    }
}

static rt_err_t _ep_out_handler(ufunction_t func, rt_size_t size)
{
    struct hid_s *data;
    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);

    rt_kprintf("%s size = %d\n",__func__,size);
    data = (struct hid_s *) func->user_data;

    if(size != 0)
    {
        dump_hex(data->ep_out->buffer,size);
    }

    data->ep_out->request.buffer = data->ep_out->buffer;
    data->ep_out->request.size = EP_MAXPACKET(data->ep_out);
    data->ep_out->request.req_type = UIO_REQUEST_READ_BEST;
    rt_usbd_io_request(func->device, data->ep_out, &data->ep_out->request);
    return RT_EOK;
}

static rt_err_t _ep_in_handler(ufunction_t func, rt_size_t size)
{
    struct hid_s *data;
    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);

    data = (struct hid_s *) func->user_data;

    return RT_EOK;
}

static rt_err_t _hid_set_report_callback(udevice_t device, rt_size_t size)
{
    RT_DEBUG_LOG(RT_DEBUG_USB, ("_hid_set_report_callback\n"));

    if(size != 0)
    {
        rt_kprintf("HID set report callback:\n");
        dump_hex(device->dcd->ep0.request.buffer - size,size);
    }

    dcd_ep0_send_status(device->dcd);

    return RT_EOK;
}

/**
 * This function will handle hid interface bRequest.
 *
 * @param device the usb device object.
 * @param setup the setup bRequest.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _interface_handler(ufunction_t func, ureq_t setup)
{
    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    struct hid_s *data = (struct hid_s *) func->user_data;

    if(setup->wIndex != 0)
        return -RT_EIO;

    switch (setup->bRequest)
    {
    case USB_REQ_GET_DESCRIPTOR:
        if((setup->wValue >> 8) == USB_DESC_TYPE_REPORT)
        {
            rt_kprintf("HID get report descriptor\n");
            rt_kprintf("sizeof _report_desc = %d bytes\n",sizeof(_report_desc));
            rt_usbd_ep0_write(func->device, (void *)(&_report_desc[0]), sizeof(_report_desc));
        }
        else if((setup->wValue >> 8) == USB_DESC_TYPE_HID)
        {
            rt_kprintf("HID get hid descriptor\n");

            rt_usbd_ep0_write(func->device, (void *)(&_hid_comm_desc.hid_desc), sizeof(struct uhid_descriptor));
        }
        break;
    case USB_HID_REQ_GET_REPORT:
        rt_kprintf("HID get report \n");
        rt_kprintf("wLength = %d\n",setup->wLength);
        if(setup->wLength == 0)
        {
            rt_usbd_ep0_set_stall(func->device);
            break;
        }
        if((setup->wLength == 0) || (setup->wLength > MAX_REPORT_SIZE))
            setup->wLength = MAX_REPORT_SIZE;
        rt_usbd_ep0_write(func->device, data->report_buf,setup->wLength);
        break;
    case USB_HID_REQ_GET_IDLE:
        rt_kprintf("HID get idle \n");

        dcd_ep0_send_status(func->device->dcd);
        break;
    case USB_HID_REQ_GET_PROTOCOL:
        rt_kprintf("HID get protocol \n");
        rt_usbd_ep0_write(func->device, &data->protocol,2);
        break;
    case USB_HID_REQ_SET_REPORT:
        rt_kprintf("HID set report \n");
        rt_kprintf("set report size = %d\n",setup->wLength);

        if((setup->wLength == 0) || (setup->wLength > MAX_REPORT_SIZE))
            rt_usbd_ep0_set_stall(func->device);

        rt_usbd_ep0_read(func->device, data->report_buf, setup->wLength, _hid_set_report_callback);
        break;
    case USB_HID_REQ_SET_IDLE:
    {
        int duration = (setup->wValue >> 8);
        int report_id = (setup->wValue & 0xFF);
        rt_kprintf("HID set idle \n");
        rt_kprintf("duration = %d,report_id = %d\n",duration,report_id);

        dcd_ep0_send_status(func->device->dcd);
    }
        break;
    case USB_HID_REQ_SET_PROTOCOL:
        rt_kprintf("HID set protocol \n");
        data->protocol = setup->wValue;

        dcd_ep0_send_status(func->device->dcd);
        break;
    }

    return RT_EOK;
}


/**
 * This function will run cdc function, it will be called on handle set configuration bRequest.
 *
 * @param func the usb function object.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _function_enable(ufunction_t func)
{
    struct hid_s *data;

    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);
    data = (struct hid_s *) func->user_data;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("hid function enable\n"));
//
//    _vcom_reset_state(func);
//
    data->ep_out->buffer = rt_malloc(HID_RX_BUFSIZE);
    data->ep_out->request.buffer    = data->ep_out->buffer;
    data->ep_out->request.size      = EP_MAXPACKET(data->ep_out);
    data->ep_out->request.req_type  = UIO_REQUEST_READ_BEST;

    rt_usbd_io_request(func->device, data->ep_out, &data->ep_out->request);

    return RT_EOK;
}

/**
 * This function will stop cdc function, it will be called on handle set configuration bRequest.
 *
 * @param func the usb function object.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _function_disable(ufunction_t func)
{
    struct hid_s *data;

    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);
    data = (struct hid_s *) func->user_data;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("hid function disable\n"));

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




/**
 * This function will configure hid descriptor.
 *
 * @param comm the communication interface number.
 * @param data the data interface number.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _hid_descriptor_config(uhid_comm_desc_t hid, rt_uint8_t cintf_nr)
{
#ifdef RT_USB_DEVICE_COMPOSITE
    hid->iad_desc.bFirstInterface = cintf_nr;
#endif

    return RT_EOK;
}

static void rt_usb_hid_init(struct ufunction *func)
{

}


/**
 * This function will create a hid function instance.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK on successful.
 */
ufunction_t rt_usbd_function_hid_create(udevice_t device)
{
    ufunction_t     func;
    struct hid_s   *data;

    uintf_t         hid_intf;
    ualtsetting_t   hid_setting;
    uhid_comm_desc_t hid_desc;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);

    /* set usb device string description */
    rt_usbd_device_set_string(device, _ustring);

    /* create a cdc function */
    func = rt_usbd_function_new(device, &_dev_desc, &ops);
    rt_usbd_device_set_qualifier(device, &_dev_qualifier);

    /* allocate memory for cdc vcom data */
    data = (struct hid_s*)rt_malloc(sizeof(struct hid_s));
    rt_memset(data, 0, sizeof(struct hid_s));
    func->user_data = (void*)data;

    /* initilize hid */
    rt_usb_hid_init(func);

    /* create an interface object */
    hid_intf = rt_usbd_interface_new(device, _interface_handler);

    /* create an alternate setting object */
    hid_setting = rt_usbd_altsetting_new(sizeof(struct uhid_comm_descriptor));

    /* config desc in alternate setting */
    rt_usbd_altsetting_config_descriptor(hid_setting, &_hid_comm_desc, (rt_off_t)&((uhid_comm_desc_t)0)->intf_desc);

    /* configure the hid interface descriptor */
    _hid_descriptor_config(hid_setting->desc, hid_intf->intf_num);

    /* create endpoint */
    hid_desc = (uhid_comm_desc_t)hid_setting->desc;
    data->ep_out = rt_usbd_endpoint_new(&hid_desc->ep_out_desc, _ep_out_handler);
    data->ep_in  = rt_usbd_endpoint_new(&hid_desc->ep_in_desc, _ep_in_handler);

    /* add the int out and int in endpoint to the alternate setting */
    rt_usbd_altsetting_add_endpoint(hid_setting, data->ep_out);
    rt_usbd_altsetting_add_endpoint(hid_setting, data->ep_in);

    /* add the alternate setting to the interface, then set default setting */
    rt_usbd_interface_add_altsetting(hid_intf, hid_setting);
    rt_usbd_set_altsetting(hid_intf, 0);

    /* add the interface to the mass storage function */
    rt_usbd_function_add_interface(func, hid_intf);
    return func;
}

#endif /* RT_USB_DEVICE_HID */
