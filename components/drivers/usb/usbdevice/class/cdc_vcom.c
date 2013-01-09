/*
 * File      : cdc_vcom.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-10-02     Yi Qiu       first version
 * 2012-12-12     heyuanjie87  change endpoints and class handler
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include "cdc.h"

#ifdef RT_USB_DEVICE_CDC

#define CDC_RX_BUFSIZE          64
#define CDC_TX_BUFSIZE          2048
static rt_uint8_t rx_pool[CDC_RX_BUFSIZE];
static rt_uint8_t tx_pool[CDC_TX_BUFSIZE];
static struct rt_ringbuffer rx_ringbuffer;
static struct rt_ringbuffer tx_ringbuffer;
static struct rt_serial_device vcom_serial;
static struct serial_ringbuffer vcom_int_rx;
static rt_bool_t vcom_connected = RT_FALSE;

static struct udevice_descriptor dev_desc =
{
    USB_DESC_LENGTH_DEVICE,     //bLength;
    USB_DESC_TYPE_DEVICE,       //type;
    USB_BCD_VERSION,            //bcdUSB;
    USB_CLASS_CDC,              //bDeviceClass;
    0x00,                       //bDeviceSubClass;
    0x00,                       //bDeviceProtocol;
    0x40,                       //bMaxPacketSize0;
    USB_VENDOR_ID,              //idVendor;
    USB_CDC_PRODUCT_ID,         //idProduct;
    USB_BCD_DEVICE,             //bcdDevice;
    USB_STRING_MANU_INDEX,      //iManufacturer;
    USB_STRING_PRODUCT_INDEX,   //iProduct;
    USB_STRING_SERIAL_INDEX,    //iSerialNumber;
    USB_DYNAMIC,                //bNumConfigurations;    
};

/* communcation interface descriptor */
const static struct ucdc_comm_descriptor _comm_desc =
{
#ifdef RT_USB_DEVICE_COMPOSITE
    /* Interface Association Descriptor */
    USB_DESC_LENGTH_IAD,
    USB_DESC_TYPE_IAD,
    USB_DYNAMIC,
    0x02,
    USB_CDC_CLASS_COMM,
    USB_CDC_SUBCLASS_ACM,
    USB_CDC_PROTOCOL_V25TER,
    0x00,
#endif
    /* Interface Descriptor */
    USB_DESC_LENGTH_INTERFACE,
    USB_DESC_TYPE_INTERFACE,
    USB_DYNAMIC,
    0x00,   
    0x01,
    USB_CDC_CLASS_COMM,
    USB_CDC_SUBCLASS_ACM,
    USB_CDC_PROTOCOL_V25TER,
    0x00,
    /* Header Functional Descriptor */   
    0x05,                              
    USB_CDC_CS_INTERFACE,
    USB_CDC_SCS_HEADER,
    0x0110,
    /* Call Management Functional Descriptor */   
    0x05,            
    USB_CDC_CS_INTERFACE,
    USB_CDC_SCS_CALL_MGMT,
    0x00,
    USB_DYNAMIC,
    /* Abstract Control Management Functional Descriptor */
    0x04,
    USB_CDC_CS_INTERFACE,
    USB_CDC_SCS_ACM,
    0x02,
    /* Union Functional Descriptor */   
    0x05,
    USB_CDC_CS_INTERFACE,
    USB_CDC_SCS_UNION,
    USB_DYNAMIC,
    USB_DYNAMIC,
    /* Endpoint Descriptor */    
    USB_DESC_LENGTH_ENDPOINT,
    USB_DESC_TYPE_ENDPOINT,
    USB_DYNAMIC | USB_DIR_IN,
    USB_EP_ATTR_INT,
    0x08,
    0xFF,
};

/* data interface descriptor */
const static struct ucdc_data_descriptor _data_desc =
{
    /* interface descriptor */
    USB_DESC_LENGTH_INTERFACE,
    USB_DESC_TYPE_INTERFACE,
    USB_DYNAMIC,
    0x00,
    0x02,         
    USB_CDC_CLASS_DATA,
    0x00,                             
    0x00,                             
    0x00,              
    /* endpoint, bulk out */
    USB_DESC_LENGTH_ENDPOINT,     
    USB_DESC_TYPE_ENDPOINT,
    USB_DYNAMIC | USB_DIR_OUT,
    USB_EP_ATTR_BULK,      
    USB_CDC_BUFSIZE,
    0x00,          
    /* endpoint, bulk in */
    USB_DESC_LENGTH_ENDPOINT,
    USB_DESC_TYPE_ENDPOINT,
    USB_DYNAMIC | USB_DIR_IN,
    USB_EP_ATTR_BULK,      
    USB_CDC_BUFSIZE,
    0x00,
};

/**
 * This function will handle cdc bulk in endpoint request.
 *
 * @param device the usb device object.
 * @param size request size.
 *
 * @return RT_EOK.
 */
static rt_err_t _ep_in_handler(udevice_t device, uclass_t cls, rt_size_t size)
{
    rt_uint32_t level;
    rt_size_t length;
    cdc_eps_t eps;
    rt_size_t mps;

    eps = (cdc_eps_t)cls->eps;
    mps = eps->ep_in->ep_desc->wMaxPacketSize;
    size = RT_RINGBUFFER_SIZE(&tx_ringbuffer);
    if(size == 0) return RT_EOK;
    
    length = size > mps ? mps : size;

    level = rt_hw_interrupt_disable();
    rt_ringbuffer_get(&tx_ringbuffer, eps->ep_in->buffer, length);
    rt_hw_interrupt_enable(level);

    /* send data to host */
    dcd_ep_write(device->dcd, eps->ep_in, eps->ep_in->buffer, length);

    return RT_EOK;
}

/**
 * This function will handle cdc bulk out endpoint request.
 *
 * @param device the usb device object.
 * @param size request size.
 *
 * @return RT_EOK.
 */
static rt_err_t _ep_out_handler(udevice_t device, uclass_t cls, rt_size_t size)
{
    rt_uint32_t level;
    cdc_eps_t eps;

    RT_ASSERT(device != RT_NULL);
    
    eps = (cdc_eps_t)cls->eps;
    /* receive data from USB VCOM */
    level = rt_hw_interrupt_disable();
    rt_ringbuffer_put(&rx_ringbuffer, eps->ep_out->buffer, size);
    rt_hw_interrupt_enable(level);

    /* notify receive data */
    rt_hw_serial_isr(&vcom_serial);

    dcd_ep_read(device->dcd, eps->ep_out, eps->ep_out->buffer, 
        eps->ep_out->ep_desc->wMaxPacketSize);    

    return RT_EOK;
}

/**
 * This function will handle cdc interrupt in endpoint request.
 *
 * @param device the usb device object.
 * @param size request size.
 *
 * @return RT_EOK.
 */
static rt_err_t _ep_cmd_handler(udevice_t device, uclass_t cls, rt_size_t size)
{
    RT_ASSERT(device != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_ep_cmd_handler\n"));

    return RT_EOK;
}

/**
 * This function will handle cdc_get_line_coding request.
 *
 * @param device the usb device object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _cdc_get_line_coding(udevice_t device, ureq_t setup)
{
    struct ucdc_line_coding data;
    rt_uint16_t size;
    
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);
    
    data.dwDTERate = 115200;
    data.bCharFormat = 0;
    data.bDataBits = 8;
    data.bParityType = 0;
    size = setup->length > 7 ? 7 : setup->length;
    
    dcd_ep_write(device->dcd, 0, (void*)&data, size);
    
    return RT_EOK;
}

/**
 * This function will handle cdc_set_line_coding request.
 *
 * @param device the usb device object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _cdc_set_line_coding(udevice_t device, ureq_t setup)
{
    struct ucdc_line_coding data;   
    rt_err_t ret;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    rt_completion_init(&device->dcd->completion);
 
    dcd_ep_read(device->dcd, 0, (void*)&data, setup->length);

    ret = rt_completion_wait(&device->dcd->completion, 100);
    if(ret != RT_EOK)
    {
        rt_kprintf("_cdc_set_line_coding timeout\n");
    }
     
    return RT_EOK;
}

/**
 * This function will handle cdc interface request.
 *
 * @param device the usb device object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _interface_handler(udevice_t device, uclass_t cls, ureq_t setup)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);
        
    switch(setup->request)
    {
    case CDC_SEND_ENCAPSULATED_COMMAND:
        break;
    case CDC_GET_ENCAPSULATED_RESPONSE:
        break;
    case CDC_SET_COMM_FEATURE:
        break;
    case CDC_GET_COMM_FEATURE:
        break;
    case CDC_CLEAR_COMM_FEATURE:
        break;
    case CDC_SET_LINE_CODING:
        _cdc_set_line_coding(device, setup);
        vcom_connected = RT_TRUE;        
        break;
    case CDC_GET_LINE_CODING:
        _cdc_get_line_coding(device, setup);  
        break;
    case CDC_SET_CONTROL_LINE_STATE:
        rt_device_control((rt_device_t)device->dcd, CONTROL_SEND_STATUS, RT_NULL);        
        break;
    case CDC_SEND_BREAK:
        break;
    default:
        rt_kprintf("unknown cdc request\n",setup->request_type);
        return -RT_ERROR;
    }

    return RT_EOK;
}

/**
 * This function will run cdc class, it will be called on handle set configuration request.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _class_run(udevice_t device, uclass_t cls)
{
    cdc_eps_t eps;
    RT_ASSERT(device != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("cdc class run\n"));
    eps = (cdc_eps_t)cls->eps;

    eps->ep_in->buffer=tx_pool;
    eps->ep_out->buffer=rx_pool;

    dcd_ep_read(device->dcd, eps->ep_out, eps->ep_out->buffer, 
        eps->ep_out->ep_desc->wMaxPacketSize);
    
    return RT_EOK;
}

/**
 * This function will stop cdc class, it will be called on handle set configuration request.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _class_stop(udevice_t device, uclass_t cls)
{
    RT_ASSERT(device != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("cdc class stop\n"));

    return RT_EOK;
}

/**
 * This function will handle system sof event.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _class_sof_handler(udevice_t device, uclass_t cls)
{
    rt_uint32_t level;
    rt_size_t size;
    static rt_uint32_t frame_count = 0;
    cdc_eps_t eps;

    if(vcom_connected != RT_TRUE) return -RT_ERROR;
    
    eps = (cdc_eps_t)cls->eps;
    if (frame_count ++ == 5)
    {
        rt_size_t mps = eps->ep_in->ep_desc->wMaxPacketSize;

        /* reset the frame counter */
        frame_count = 0;

        size = RT_RINGBUFFER_SIZE(&tx_ringbuffer);
        if(size == 0) return -RT_EFULL;

        size = size > mps ? mps : size;
        
        level = rt_hw_interrupt_disable();
        rt_ringbuffer_get(&tx_ringbuffer, eps->ep_in->buffer, size);
        rt_hw_interrupt_enable(level);                     
        
        /* send data to host */
        dcd_ep_write(device->dcd, eps->ep_in, eps->ep_in->buffer, size);
    }

    return RT_EOK;
}

static struct uclass_ops ops =
{
    _class_run,
    _class_stop,
    _class_sof_handler,
};

/**
 * This function will configure cdc descriptor.
 *
 * @param comm the communication interface number.
 * @param data the data interface number.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _cdc_descriptor_config(ucdc_comm_desc_t comm, rt_uint8_t cintf_nr, ucdc_data_desc_t data, rt_uint8_t dintf_nr)
{
    comm->call_mgmt_desc.data_interface = dintf_nr;
    comm->union_desc.master_interface = cintf_nr;
    comm->union_desc.slave_interface0 = dintf_nr;
#ifdef RT_USB_DEVICE_COMPOSITE    
    comm->iad_desc.bFirstInterface = cintf_nr;
#endif

    return RT_EOK;
}

/**
 * This function will create a cdc class instance.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK on successful.
 */
uclass_t rt_usbd_class_cdc_create(udevice_t device)
{
    uclass_t cdc;
    cdc_eps_t eps;
    uintf_t intf_comm, intf_data;
    ualtsetting_t comm_setting, data_setting;
    ucdc_data_desc_t data_desc;
    ucdc_comm_desc_t comm_desc;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    
    /* create a cdc class */
    cdc = rt_usbd_class_create(device, &dev_desc, &ops);
    /* create a cdc class endpoints collection */
    eps = rt_malloc(sizeof(struct cdc_eps));
    cdc->eps = (void*)eps;

    /* create a cdc communication interface and a cdc data interface */
    intf_comm = rt_usbd_interface_create(device, _interface_handler);
    intf_data = rt_usbd_interface_create(device, _interface_handler);

    /* create a communication alternate setting and a data alternate setting */
    comm_setting = rt_usbd_altsetting_create(sizeof(struct ucdc_comm_descriptor));     
    data_setting = rt_usbd_altsetting_create(sizeof(struct ucdc_data_descriptor)); 
    
    /* config desc in alternate setting */    
    rt_usbd_altsetting_config_descriptor(comm_setting, &_comm_desc,
        (rt_off_t)&((ucdc_comm_desc_t)0)->intf_desc);
    rt_usbd_altsetting_config_descriptor(data_setting, &_data_desc, 0);
    /* configure the cdc interface descriptor */
    _cdc_descriptor_config(comm_setting->desc, intf_comm->intf_num, data_setting->desc, intf_data->intf_num);

    /* create a bulk in and a bulk endpoint */
    data_desc = (ucdc_data_desc_t)data_setting->desc;
    eps->ep_out = rt_usbd_endpoint_create(&data_desc->ep_out_desc, _ep_out_handler);
    eps->ep_in = rt_usbd_endpoint_create(&data_desc->ep_in_desc, _ep_in_handler);

    /* add the bulk out and bulk in endpoints to the data alternate setting */
    rt_usbd_altsetting_add_endpoint(data_setting, eps->ep_in);
    rt_usbd_altsetting_add_endpoint(data_setting, eps->ep_out);
    
    /* add the data alternate setting to the data interface
            then set default setting of the interface */
    rt_usbd_interface_add_altsetting(intf_data, data_setting);
    rt_usbd_set_altsetting(intf_data, 0);

    /* add the cdc data interface to cdc class */
    rt_usbd_class_add_interface(cdc, intf_data);  

    /* create a command endpoint */
    comm_desc = (ucdc_comm_desc_t)comm_setting->desc;
    eps->ep_cmd = rt_usbd_endpoint_create(&comm_desc->ep_desc, _ep_cmd_handler);

    /* add the command endpoint to the cdc communication interface */
    rt_usbd_altsetting_add_endpoint(comm_setting, eps->ep_cmd);
    
    /* add the communication alternate setting to the communication interface,
       then set default setting of the interface */
    rt_usbd_interface_add_altsetting(intf_comm, comm_setting);
    rt_usbd_set_altsetting(intf_comm, 0);

    /* add the communication interface to the cdc class */
    rt_usbd_class_add_interface(cdc, intf_comm);    

    return cdc;
}

/**
* UART device in RT-Thread
*/
static rt_err_t _vcom_configure(struct rt_serial_device *serial, 
    struct serial_configure *cfg)
{
    return RT_EOK;
}

static rt_err_t _vcom_control(struct rt_serial_device *serial, 
    int cmd, void *arg)
{
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        break;
    }

    return RT_EOK;
}

static int _vcom_putc(struct rt_serial_device *serial, char c)
{
    rt_uint32_t level;
    
    if (vcom_connected != RT_TRUE) return 0;
    
    level = rt_hw_interrupt_disable();
    if (RT_RINGBUFFER_EMPTY(&tx_ringbuffer))
    {
        rt_ringbuffer_putchar(&tx_ringbuffer, c);
    }
    rt_hw_interrupt_enable(level);     
    
    return 1;
}

static int _vcom_getc(struct rt_serial_device *serial)
{
    int result;
    rt_uint8_t ch;
    rt_uint32_t level;

    result = -1;

    level = rt_hw_interrupt_disable();
    if (RT_RINGBUFFER_SIZE(&rx_ringbuffer))
    {
        rt_ringbuffer_getchar(&rx_ringbuffer, &ch);
        result = ch;
    }
    rt_hw_interrupt_enable(level);

    return result;
}

static const struct rt_uart_ops usb_vcom_ops =
{
    _vcom_configure,
    _vcom_control,
    _vcom_putc,
    _vcom_getc,
};

void rt_usb_vcom_init(void)
{
    struct serial_configure config;

    /* initialize ring buffer */
    rt_ringbuffer_init(&rx_ringbuffer, rx_pool, CDC_RX_BUFSIZE);
    rt_ringbuffer_init(&tx_ringbuffer, tx_pool, CDC_TX_BUFSIZE);

    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert = NRZ_NORMAL;

    vcom_serial.ops = &usb_vcom_ops;
    vcom_serial.int_rx = &vcom_int_rx;
    vcom_serial.config = config;

    /* register vcom device */
    rt_hw_serial_register(&vcom_serial, "vcom",
    RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
        RT_NULL);
}

#endif

