/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-11-19     ZYH               first version
 * 2019-06-10     ZYH               fix hotplug
 */

#include <rtdevice.h>
#ifdef RT_USB_DEVICE_ECM
#include "cdc.h"

#define DBG_LEVEL           DBG_WARNING
#define DBG_SECTION_NAME    "ECM"
#include <rtdbg.h>

/* RT-Thread LWIP ethernet interface */
#include <netif/ethernetif.h>

#ifndef USB_ETH_MTU
#define USB_ETH_MTU     1514
#endif
#define MAX_ADDR_LEN    6
#define ECM_INTF_STR_INDEX 10

struct rt_ecm_eth
{
    /* inherit from ethernet device */
    struct eth_device       parent;
    struct ufunction *      func;
    struct cdc_eps          eps;
    /* interface address info */
    rt_uint8_t              host_addr[MAX_ADDR_LEN];
    rt_uint8_t              dev_addr[MAX_ADDR_LEN];

    ALIGN(4)
    rt_uint8_t              rx_pool[512];
    ALIGN(4)
    rt_size_t               rx_size;
    ALIGN(4)
    rt_size_t               rx_offset;
    ALIGN(4)
    char                    rx_buffer[USB_ETH_MTU];
    char                    tx_buffer[USB_ETH_MTU];

    struct rt_semaphore     tx_buffer_free;

};
typedef struct rt_ecm_eth * rt_ecm_eth_t;

ALIGN(4)
static struct udevice_descriptor _dev_desc =
{
    USB_DESC_LENGTH_DEVICE,     /* bLength */
    USB_DESC_TYPE_DEVICE,       /* type */
    USB_BCD_VERSION,            /* bcdUSB */
    USB_CLASS_CDC,              /* bDeviceClass */
    USB_CDC_SUBCLASS_ETH,       /* bDeviceSubClass */
    USB_CDC_PROTOCOL_NONE,      /* bDeviceProtocol */
    0x40,                       /* bMaxPacketSize0 */
    _VENDOR_ID,                 /* idVendor */
    _PRODUCT_ID,                /* idProduct */
    USB_BCD_DEVICE,             /* bcdDevice */
    USB_STRING_MANU_INDEX,      /* iManufacturer */
    USB_STRING_PRODUCT_INDEX,   /* iProduct */
    USB_STRING_SERIAL_INDEX,    /* iSerialNumber */
    USB_DYNAMIC                 /* bNumConfigurations */
};

/* communcation interface descriptor */
ALIGN(4)
const static struct ucdc_eth_descriptor _comm_desc =
{
#ifdef RT_USB_DEVICE_COMPOSITE
    /* Interface Association Descriptor */
    {
        USB_DESC_LENGTH_IAD,
        USB_DESC_TYPE_IAD,
        USB_DYNAMIC,
        0x02,
        USB_CDC_CLASS_COMM,
        USB_CDC_SUBCLASS_ETH,
        USB_CDC_PROTOCOL_NONE,
        0x00,
    },
#endif
    /* Interface Descriptor */
    {
        USB_DESC_LENGTH_INTERFACE,
        USB_DESC_TYPE_INTERFACE,
        USB_DYNAMIC,
        0x00,
        0x01,
        USB_CDC_CLASS_COMM,
        USB_CDC_SUBCLASS_ETH,
        USB_CDC_PROTOCOL_NONE,
#ifdef RT_USB_DEVICE_COMPOSITE
        ECM_INTF_STR_INDEX,
#else
        0x00,
#endif
    },
    /* Header Functional Descriptor */
    {
        sizeof(struct ucdc_header_descriptor),
        USB_CDC_CS_INTERFACE,
        USB_CDC_SCS_HEADER,
        0x0110,
    },
    /* Union Functional Descriptor */
    {
        sizeof(struct ucdc_union_descriptor),
        USB_CDC_CS_INTERFACE,
        USB_CDC_SCS_UNION,
        USB_DYNAMIC,
        USB_DYNAMIC,
    },
    /* Abstract Control Management Functional Descriptor */
    {
        sizeof(struct ucdc_enet_descriptor),
        USB_CDC_CS_INTERFACE,
        USB_CDC_SCS_ETH,
        USB_STRING_SERIAL_INDEX,
        {0,0,0,0},
        USB_ETH_MTU,
        0x00,
        0x00,
    },
    /* Endpoint Descriptor */
    {
        USB_DESC_LENGTH_ENDPOINT,
        USB_DESC_TYPE_ENDPOINT,
        USB_DIR_IN | USB_DYNAMIC,
        USB_EP_ATTR_INT,
        0x08,
        0xFF,
    },
};

/* data interface descriptor */
ALIGN(4)
const static struct ucdc_data_descriptor _data_desc =
{
    /* interface descriptor */
    {
        USB_DESC_LENGTH_INTERFACE,
        USB_DESC_TYPE_INTERFACE,
        USB_DYNAMIC,
        0x00,
        0x02,
        USB_CDC_CLASS_DATA,
        USB_CDC_SUBCLASS_ETH,
        0x00,
        0x00,
    },
    /* endpoint, bulk out */
    {
        USB_DESC_LENGTH_ENDPOINT,
        USB_DESC_TYPE_ENDPOINT,
        USB_DIR_OUT | USB_DYNAMIC,
        USB_EP_ATTR_BULK,
        USB_DYNAMIC,
        0x00,
    },
    /* endpoint, bulk in */
    {
        USB_DESC_LENGTH_ENDPOINT,
        USB_DESC_TYPE_ENDPOINT,
        USB_DYNAMIC | USB_DIR_IN,
        USB_EP_ATTR_BULK,
        USB_DYNAMIC,
        0x00,
    },
};

ALIGN(4)
const static char* _ustring[] =
{
    "Language",                 /* LANGID */
    "RT-Thread Team.",          /* MANU */
    "RT-Thread ECM device",     /* PRODUCT */
    "3497F694ECAB",             /* SERIAL (MAC)*/
    "Configuration",            /* CONFIG */
    "Interface",                /* INTERFACE */
};

ALIGN(4)
//FS and HS needed
static struct usb_qualifier_descriptor dev_qualifier =
{
    sizeof(dev_qualifier),          //bLength
    USB_DESC_TYPE_DEVICEQUALIFIER,  //bDescriptorType
    0x0200,                         //bcdUSB
    USB_CLASS_CDC,                  //bDeviceClass
    USB_CDC_SUBCLASS_ETH,           //bDeviceSubClass
    USB_CDC_PROTOCOL_NONE,          //bDeviceProtocol
    64,                             //bMaxPacketSize0
    0x01,                           //bNumConfigurations
    0,
};

static rt_err_t _cdc_send_notifi(ufunction_t func,ucdc_notification_code_t notifi,rt_uint16_t wValue,rt_uint16_t wLength)
{
    static struct ucdc_management_element_notifications _notifi;
    cdc_eps_t eps;
    RT_ASSERT(func!=RT_NULL)
    eps = &((rt_ecm_eth_t)func->user_data)->eps;
    _notifi.bmRequestType = 0xA1;
    _notifi.bNotificatinCode = notifi;
    _notifi.wValue = wValue;
    _notifi.wLength = wLength;

    eps->ep_cmd->request.buffer = (void *)&_notifi;
    eps->ep_cmd->request.size = 8;
    eps->ep_cmd->request.req_type = UIO_REQUEST_WRITE;
    rt_usbd_io_request(func->device, eps->ep_cmd, &eps->ep_cmd->request);
    return RT_EOK;
}


static rt_err_t _ecm_set_eth_packet_filter(ufunction_t func, ureq_t setup)
{
    rt_ecm_eth_t _ecm_eth = (rt_ecm_eth_t)func->user_data;
    dcd_ep0_send_status(func->device->dcd);

    /* send link up. */
    eth_device_linkchange(&_ecm_eth->parent, RT_TRUE);
    _cdc_send_notifi(func, UCDC_NOTIFI_NETWORK_CONNECTION, 1, 0);

#ifdef LWIP_USING_DHCPD
    extern void dhcpd_start(const char *netif_name);
    dhcpd_start("u0");
#endif

    return RT_EOK;
}
/**
 * This function will handle rndis interface request.
 *
 * @param device the usb device object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _interface_handler(ufunction_t func, ureq_t setup)
{
    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    switch(setup->bRequest)
    {
    case CDC_SET_ETH_PACKET_FILTER:
        LOG_D("CDC_SET_ETH_PACKET_FILTER");
        _ecm_set_eth_packet_filter(func, setup);
        break;
    default:
        LOG_E("Unknow setup->bRequest: 0x%02X", setup->bRequest);
        break;
    }
    return RT_EOK;
}

/**
 * This function will handle rndis bulk in endpoint request.
 *
 * @param device the usb device object.
 * @param size request size.
 *
 * @return RT_EOK.
 */

static rt_err_t _ep_in_handler(ufunction_t func, rt_size_t size)
{
    rt_ecm_eth_t ecm_device = (rt_ecm_eth_t)func->user_data;
    rt_sem_release(&ecm_device->tx_buffer_free);
    return RT_EOK;
}

/**
 * This function will handle RNDIS bulk out endpoint request.
 *
 * @param device the usb device object.
 * @param size request size.
 *
 * @return RT_EOK.
 */
static rt_err_t _ep_out_handler(ufunction_t func, rt_size_t size)
{
    rt_ecm_eth_t ecm_device = (rt_ecm_eth_t)func->user_data;
    rt_memcpy((void *)(ecm_device->rx_buffer + ecm_device->rx_offset),ecm_device->rx_pool,size);
    ecm_device->rx_offset += size;
    if(size < EP_MAXPACKET(ecm_device->eps.ep_out))
    {
        ecm_device->rx_size = ecm_device->rx_offset;
        ecm_device->rx_offset = 0;
        eth_device_ready(&ecm_device->parent);

    }else
    {
        ecm_device->eps.ep_out->request.buffer = ecm_device->eps.ep_out->buffer;
        ecm_device->eps.ep_out->request.size = EP_MAXPACKET(ecm_device->eps.ep_out);
        ecm_device->eps.ep_out->request.req_type = UIO_REQUEST_READ_BEST;
        rt_usbd_io_request(ecm_device->func->device, ecm_device->eps.ep_out, &ecm_device->eps.ep_out->request);
    }


    return RT_EOK;
}
static rt_err_t rt_ecm_eth_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_ecm_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_ecm_eth_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t rt_ecm_eth_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_size_t rt_ecm_eth_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}
static rt_err_t rt_ecm_eth_control(rt_device_t dev, int cmd, void *args)
{
    rt_ecm_eth_t ecm_eth_dev = (rt_ecm_eth_t)dev;
    switch(cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if(args) rt_memcpy(args, ecm_eth_dev->dev_addr, MAX_ADDR_LEN);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops ecm_device_ops =
{
    rt_ecm_eth_init,
    rt_ecm_eth_open,
    rt_ecm_eth_close,
    rt_ecm_eth_read,
    rt_ecm_eth_write,
    rt_ecm_eth_control
};
#endif

struct pbuf *rt_ecm_eth_rx(rt_device_t dev)
{
    struct pbuf* p = RT_NULL;
    rt_uint32_t offset = 0;
    rt_ecm_eth_t ecm_eth_dev = (rt_ecm_eth_t)dev;
    if(ecm_eth_dev->rx_size != 0)
    {
        /* allocate buffer */
        p = pbuf_alloc(PBUF_RAW, ecm_eth_dev->rx_size, PBUF_RAM);
        if (p != RT_NULL)
        {
            struct pbuf* q;

            for (q = p; q != RT_NULL; q= q->next)
            {
                /* Copy the received frame into buffer from memory pointed by the current ETHERNET DMA Rx descriptor */
                rt_memcpy(q->payload,
                        (rt_uint8_t *)((ecm_eth_dev->rx_buffer) + offset),
                        q->len);
                offset += q->len;
            }
        }
    }

    {
        if(ecm_eth_dev->func->device->state == USB_STATE_CONFIGURED)
        {
            ecm_eth_dev->rx_size = 0;
            ecm_eth_dev->rx_offset = 0;
            ecm_eth_dev->eps.ep_out->request.buffer = ecm_eth_dev->eps.ep_out->buffer;
            ecm_eth_dev->eps.ep_out->request.size = EP_MAXPACKET(ecm_eth_dev->eps.ep_out);
            ecm_eth_dev->eps.ep_out->request.req_type = UIO_REQUEST_READ_BEST;
            rt_usbd_io_request(ecm_eth_dev->func->device, ecm_eth_dev->eps.ep_out, &ecm_eth_dev->eps.ep_out->request);
        }
    }

    return p;
}

rt_err_t rt_ecm_eth_tx(rt_device_t dev, struct pbuf* p)
{
    struct pbuf* q;
    char * pbuffer;
    rt_err_t result = RT_EOK;
    rt_ecm_eth_t ecm_eth_dev = (rt_ecm_eth_t)dev;

    if(!ecm_eth_dev->parent.link_status)
    {
        LOG_D("linkdown, drop pkg");
        return RT_EOK;
    }

    if(p->tot_len > USB_ETH_MTU)
    {
        LOG_W("ECM MTU is:%d, but the send packet size is %d",
                     USB_ETH_MTU, p->tot_len);
        p->tot_len = USB_ETH_MTU;
    }

    result = rt_sem_take(&ecm_eth_dev->tx_buffer_free, rt_tick_from_millisecond(1000));
    if(result != RT_EOK)
    {
        LOG_W("wait for buffer free timeout");
        /* if cost 1s to wait send done it said that connection is close . drop it */
        rt_sem_release(&ecm_eth_dev->tx_buffer_free);
        return result;
    }

    pbuffer = (char *)&ecm_eth_dev->tx_buffer;
    for (q = p; q != NULL; q = q->next)
    {
        rt_memcpy(pbuffer, q->payload, q->len);
        pbuffer += q->len;
    }

    {
        if(ecm_eth_dev->func->device->state == USB_STATE_CONFIGURED)
        {
            ecm_eth_dev->eps.ep_in->request.buffer = (void *)&ecm_eth_dev->tx_buffer;
            ecm_eth_dev->eps.ep_in->request.size = p->tot_len;
            ecm_eth_dev->eps.ep_in->request.req_type = UIO_REQUEST_WRITE;
            rt_usbd_io_request(ecm_eth_dev->func->device, ecm_eth_dev->eps.ep_in, &ecm_eth_dev->eps.ep_in->request);
        }
    }

    return result;
}
/**
 * This function will handle RNDIS interrupt in endpoint request.
 *
 * @param device the usb device object.
 * @param size request size.
 *
 * @return RT_EOK.
 */
static rt_err_t _ep_cmd_handler(ufunction_t func, rt_size_t size)
{
    return RT_EOK;
}

/**
 * This function will run cdc class, it will be called on handle set configuration request.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _function_enable(ufunction_t func)
{
    cdc_eps_t eps;
    rt_ecm_eth_t ecm_device = (rt_ecm_eth_t)func->user_data;

    LOG_D("plugged in");

    eps = (cdc_eps_t)&ecm_device->eps;
    eps->ep_out->buffer = ecm_device->rx_pool;

    /* reset eth rx tx */
    ecm_device->rx_size = 0;
    ecm_device->rx_offset = 0;

    eps->ep_out->request.buffer = (void *)eps->ep_out->buffer;
    eps->ep_out->request.size = EP_MAXPACKET(eps->ep_out);
    eps->ep_out->request.req_type = UIO_REQUEST_READ_BEST;
    rt_usbd_io_request(func->device, eps->ep_out, &eps->ep_out->request);
    return RT_EOK;
}

/**
 * This function will stop cdc class, it will be called on handle set configuration request.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _function_disable(ufunction_t func)
{
    LOG_D("plugged out");

    eth_device_linkchange(&((rt_ecm_eth_t)func->user_data)->parent, RT_FALSE);

    /* reset eth rx tx */
    ((rt_ecm_eth_t)func->user_data)->rx_size = 0;
    ((rt_ecm_eth_t)func->user_data)->rx_offset = 0;

    return RT_EOK;
}


static struct ufunction_ops ops =
{
    _function_enable,
    _function_disable,
    RT_NULL,
};

/**
 * This function will configure cdc descriptor.
 *
 * @param comm the communication interface number.
 * @param data the data interface number.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _cdc_descriptor_config(ucdc_comm_desc_t comm, rt_uint8_t cintf_nr, ucdc_data_desc_t data, rt_uint8_t dintf_nr, rt_uint8_t device_is_hs)
{
    comm->call_mgmt_desc.data_interface = dintf_nr;
    comm->union_desc.master_interface = cintf_nr;
    comm->union_desc.slave_interface0 = dintf_nr;
#ifdef RT_USB_DEVICE_COMPOSITE
    comm->iad_desc.bFirstInterface = cintf_nr;
#endif
    data->ep_out_desc.wMaxPacketSize = device_is_hs ? 512 : 64;
    data->ep_in_desc.wMaxPacketSize = device_is_hs ? 512 : 64;
    return RT_EOK;
}



/**
 * This function will create a cdc ecm class instance.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK on successful.
 */
ufunction_t rt_usbd_function_ecm_create(udevice_t device)
{
    ufunction_t cdc;
    rt_ecm_eth_t _ecm_eth;
    cdc_eps_t eps;
    uintf_t intf_comm, intf_data;
    ualtsetting_t comm_setting, data_setting;
    ucdc_data_desc_t data_desc;
    ucdc_eth_desc_t comm_desc;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);

    /* set usb device string description */
#ifdef RT_USB_DEVICE_COMPOSITE
    rt_usbd_device_set_interface_string(device, ECM_INTF_STR_INDEX, _ustring[2]);
#else
    rt_usbd_device_set_string(device, _ustring);
#endif
    /* create a cdc class */
    cdc = rt_usbd_function_new(device, &_dev_desc, &ops);
    rt_usbd_device_set_qualifier(device, &dev_qualifier);
    _ecm_eth= rt_malloc(sizeof(struct rt_ecm_eth));
    RT_ASSERT(_ecm_eth != RT_NULL);
    rt_memset(_ecm_eth, 0, sizeof(struct rt_ecm_eth));
    cdc->user_data = _ecm_eth;

    _ecm_eth->func = cdc;
    /* create a cdc class endpoints collection */
    eps = &_ecm_eth->eps;
    /* create a cdc communication interface and a cdc data interface */
    intf_comm = rt_usbd_interface_new(device, _interface_handler);
    intf_data = rt_usbd_interface_new(device, _interface_handler);

    /* create a communication alternate setting and a data alternate setting */
    comm_setting = rt_usbd_altsetting_new(sizeof(struct ucdc_eth_descriptor));
    data_setting = rt_usbd_altsetting_new(sizeof(struct ucdc_data_descriptor));

    /* config desc in alternate setting */
    rt_usbd_altsetting_config_descriptor(comm_setting, &_comm_desc,
                                         (rt_off_t)&((ucdc_eth_desc_t)0)->intf_desc);
    rt_usbd_altsetting_config_descriptor(data_setting, &_data_desc, 0);
    /* configure the cdc interface descriptor */
    _cdc_descriptor_config(comm_setting->desc, intf_comm->intf_num, data_setting->desc, intf_data->intf_num, device->dcd->device_is_hs);

    /* create a command endpoint */
    comm_desc = (ucdc_eth_desc_t)comm_setting->desc;
    eps->ep_cmd = rt_usbd_endpoint_new(&comm_desc->ep_desc, _ep_cmd_handler);
    /* add the command endpoint to the cdc communication interface */
    rt_usbd_altsetting_add_endpoint(comm_setting, eps->ep_cmd);

    /* add the communication alternate setting to the communication interface,
       then set default setting of the interface */
    rt_usbd_interface_add_altsetting(intf_comm, comm_setting);
    rt_usbd_set_altsetting(intf_comm, 0);
    /* add the communication interface to the cdc class */
    rt_usbd_function_add_interface(cdc, intf_comm);

    /* create a bulk in and a bulk out endpoint */
    data_desc = (ucdc_data_desc_t)data_setting->desc;
    eps->ep_out = rt_usbd_endpoint_new(&data_desc->ep_out_desc, _ep_out_handler);
    eps->ep_in = rt_usbd_endpoint_new(&data_desc->ep_in_desc, _ep_in_handler);

    /* add the bulk out and bulk in endpoints to the data alternate setting */
    rt_usbd_altsetting_add_endpoint(data_setting, eps->ep_in);
    rt_usbd_altsetting_add_endpoint(data_setting, eps->ep_out);

    /* add the data alternate setting to the data interface
            then set default setting of the interface */
    rt_usbd_interface_add_altsetting(intf_data, data_setting);
    rt_usbd_set_altsetting(intf_data, 0);

    /* add the cdc data interface to cdc class */
    rt_usbd_function_add_interface(cdc, intf_data);

    rt_sem_init(&_ecm_eth->tx_buffer_free, "ue_tx", 1, RT_IPC_FLAG_FIFO);
    /* OUI 00-00-00, only for test. */
    _ecm_eth->dev_addr[0] = 0x34;
    _ecm_eth->dev_addr[1] = 0x97;
    _ecm_eth->dev_addr[2] = 0xF6;
    /* generate random MAC. */
    _ecm_eth->dev_addr[3] = 0x94;//*(const rt_uint8_t *)(0x1fff7a10);
    _ecm_eth->dev_addr[4] = 0xEC;//*(const rt_uint8_t *)(0x1fff7a14);
    _ecm_eth->dev_addr[5] = 0xAC;//(const rt_uint8_t *)(0x1fff7a18);
    /* OUI 00-00-00, only for test. */
    _ecm_eth->host_addr[0] = 0x34;
    _ecm_eth->host_addr[1] = 0x97;
    _ecm_eth->host_addr[2] = 0xF6;
    /* generate random MAC. */
    _ecm_eth->host_addr[3] = 0x94;//*(const rt_uint8_t *)(0x1fff7a10);
    _ecm_eth->host_addr[4] = 0xEC;//*(const rt_uint8_t *)(0x1fff7a14);
    _ecm_eth->host_addr[5] = 0xAB;//*(const rt_uint8_t *)(0x1fff7a18);

    _ecm_eth->parent.parent.init       = rt_ecm_eth_init;
    _ecm_eth->parent.parent.open       = rt_ecm_eth_open;
    _ecm_eth->parent.parent.close      = rt_ecm_eth_close;
    _ecm_eth->parent.parent.read       = rt_ecm_eth_read;
    _ecm_eth->parent.parent.write      = rt_ecm_eth_write;
    _ecm_eth->parent.parent.control    = rt_ecm_eth_control;
    _ecm_eth->parent.parent.user_data  = device;

    _ecm_eth->parent.eth_rx     = rt_ecm_eth_rx;
    _ecm_eth->parent.eth_tx     = rt_ecm_eth_tx;
    /* register eth device */
    eth_device_init(&_ecm_eth->parent, "u0");

    /* send link up. */
    eth_device_linkchange(&_ecm_eth->parent, RT_FALSE);

    return cdc;
}

struct udclass ecm_class =
{
    .rt_usbd_function_create = rt_usbd_function_ecm_create
};

int rt_usbd_ecm_class_register(void)
{
    rt_usbd_class_register(&ecm_class);
    return 0;
}
INIT_PREV_EXPORT(rt_usbd_ecm_class_register);

#endif /* RT_USB_DEVICE_ECM */
