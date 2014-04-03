/*
 * File      : cdc_vcom.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
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
 * 2012-10-02     Yi Qiu       first version
 * 2012-12-12     heyuanjie87  change endpoints and class handler
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include "cdc.h"

#ifdef RT_USB_DEVICE_CDC

#define CDC_RX_BUFSIZE          2048
#define CDC_TX_BUFSIZE          2048
static rt_uint8_t rx_rbp[CDC_RX_BUFSIZE];
static rt_uint8_t tx_rbp[CDC_TX_BUFSIZE];
static struct rt_ringbuffer rx_ringbuffer;
static struct rt_ringbuffer tx_ringbuffer;
static struct serial_ringbuffer vcom_int_rx;

static struct rt_serial_device vcom_serial;

#define CDC_MaxPacketSize 64
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t rx_buf[CDC_RX_BUFSIZE];
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t tx_buf[CDC_TX_BUFSIZE];

volatile static rt_bool_t vcom_connected = RT_FALSE;
volatile static rt_bool_t vcom_in_sending = RT_FALSE;

static struct udevice_descriptor dev_desc =
{
    USB_DESC_LENGTH_DEVICE,     //bLength;
    USB_DESC_TYPE_DEVICE,       //type;
    USB_BCD_VERSION,            //bcdUSB;
    USB_CLASS_CDC,              //bDeviceClass;
    0x00,                       //bDeviceSubClass;
    0x00,                       //bDeviceProtocol;
    CDC_MaxPacketSize,          //bMaxPacketSize0;
    _VENDOR_ID,                 //idVendor;
    _PRODUCT_ID,                //idProduct;
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

const static char* _ustring[] =
{
    "Language",
    "RT-Thread Team.",
    "RTT Virtual Serial",
    "1.1.0",
    "Configuration",
    "Interface",
};

static void _vcom_reset_state(void)
{
    int lvl = rt_hw_interrupt_disable();
    tx_ringbuffer.read_mirror  = tx_ringbuffer.read_index = 0;
    tx_ringbuffer.write_mirror = tx_ringbuffer.write_index = 0;
    vcom_connected = RT_FALSE;
    vcom_in_sending = RT_FALSE;
    /*rt_kprintf("reset USB serial\n", cnt);*/
    rt_hw_interrupt_enable(lvl);
}

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
    rt_uint32_t remain;
    cdc_eps_t eps;

    eps = (cdc_eps_t)cls->eps;
    level = rt_hw_interrupt_disable();
    remain = rt_ringbuffer_data_len(&tx_ringbuffer);
    if (remain != 0)
    {
        /* although vcom_in_sending is set in SOF handler in the very
         * beginning, we have to guarantee the state is right when start
         * sending. There is at least one extreme case where we have finished the
         * last IN transaction but the vcom_in_sending is RT_FALSE.
         *
         * Ok, what the extreme case is: pour data into vcom in loop. Open
         * terminal on the PC, you will see the data. Then close it. So the
         * data will be sent to the PC in the back. When the buffer of the PC
         * driver is full. It will not send IN packet to the board and you will
         * have no chance to clear vcom_in_sending in this function. The data
         * will fill into the ringbuffer until it is full, and we will reset
         * the state machine and clear vcom_in_sending. When you open the
         * terminal on the PC again. The IN packet will appear on the line and
         * we will, eventually, reach here with vcom_in_sending is clear.
         */
        vcom_in_sending = RT_TRUE;
        rt_ringbuffer_get(&tx_ringbuffer, eps->ep_in->buffer, remain);
        rt_hw_interrupt_enable(level);

        /* send data to host */
        dcd_ep_write(device->dcd, eps->ep_in, eps->ep_in->buffer, remain);

        return RT_EOK;
    }

    if (size != 0 &&
        (size % CDC_MaxPacketSize) == 0)
    {
        /* don't have data right now. Send a zero-length-packet to
         * terminate the transaction.
         *
         * FIXME: actually, this might not be the right place to send zlp.
         * Only the rt_device_write could know how much data is sending. */
        vcom_in_sending = RT_TRUE;
        rt_hw_interrupt_enable(level);
        dcd_ep_write(device->dcd, eps->ep_in, RT_NULL, 0);
        return RT_EOK;
    }
    else
    {
        vcom_in_sending = RT_FALSE;
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
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
        dcd_send_status(device->dcd);
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

    eps->ep_in->buffer = tx_buf;
    eps->ep_out->buffer = rx_buf;

    _vcom_reset_state();

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

    _vcom_reset_state();

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
    cdc_eps_t eps;

    if (vcom_connected != RT_TRUE)
        return -RT_ERROR;

    if (vcom_in_sending)
    {
        return RT_EOK;
    }

    eps = (cdc_eps_t)cls->eps;

    size = rt_ringbuffer_data_len(&tx_ringbuffer);
    if (size == 0)
        return -RT_EFULL;

    level = rt_hw_interrupt_disable();
    rt_ringbuffer_get(&tx_ringbuffer, eps->ep_in->buffer, size);
    rt_hw_interrupt_enable(level);

    /* send data to host */
    vcom_in_sending = RT_TRUE;
    dcd_ep_write(device->dcd, eps->ep_in, eps->ep_in->buffer, size);

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

    /* set usb device string description */
    rt_usbd_device_set_string(device, _ustring);
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
    int cnt;

    if (vcom_connected != RT_TRUE)
    {
        return 0;
    }

    /* if the buffer is full, there is a chance that the host would pull some
     * data out soon. But we cannot rely on that and if we wait to long, just
     * return. */
    for (cnt = 500;
         rt_ringbuffer_space_len(&tx_ringbuffer) == 0 && cnt;
         cnt--)
    {
        /*rt_kprintf("wait for %d\n", cnt);*/
        if (vcom_connected != RT_TRUE)
            return 0;
    }
    if (cnt == 0)
    {
        /* OK, we believe that the connection is lost. So don't send any more
         * data and act as the USB cable is not plugged in. Reset the VCOM
         * state machine */
        _vcom_reset_state();
        return 0;
    }

    level = rt_hw_interrupt_disable();
    if (rt_ringbuffer_space_len(&tx_ringbuffer))
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
    if (rt_ringbuffer_data_len(&rx_ringbuffer))
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
    rt_ringbuffer_init(&rx_ringbuffer, rx_rbp, CDC_RX_BUFSIZE);
    rt_ringbuffer_init(&tx_ringbuffer, tx_rbp, CDC_TX_BUFSIZE);

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
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          RT_NULL);
}

#endif
