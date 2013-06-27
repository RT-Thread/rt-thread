/*
 * File      : mstorage.c
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
 * 2012-10-01     Yi Qiu       first version
 * 2012-11-25     Heyuanjie87  reduce the memory consumption
 * 2012-12-09     Heyuanjie87  change class and endpoint handler
 */

#include <rtthread.h>
#include <rtservice.h>
#include <rtdevice.h>
#include "mstorage.h"

#ifdef RT_USB_DEVICE_MSTORAGE

#define STATUS_CBW              0x00
#define STATUS_CSW              0x01
#define STATUS_RECEIVE          0x02
#define STATUS_SEND             0x03

static int status = STATUS_CBW;
ALIGN(RT_ALIGN_SIZE)
static struct ustorage_csw csw;
static rt_device_t disk;
static rt_uint32_t _block;
static rt_uint32_t _count, _size;
static struct rt_device_blk_geometry geometry;
static rt_uint32_t _removed = 0;

static struct udevice_descriptor dev_desc =
{
    USB_DESC_LENGTH_DEVICE,     //bLength;
    USB_DESC_TYPE_DEVICE,       //type;
    USB_BCD_VERSION,            //bcdUSB;
    USB_CLASS_MASS_STORAGE,     //bDeviceClass;
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

const static struct umass_descriptor _mass_desc =
{
    USB_DESC_LENGTH_INTERFACE,  //bLength;
    USB_DESC_TYPE_INTERFACE,    //type;
    USB_DYNAMIC,                //bInterfaceNumber;
    0x00,                       //bAlternateSetting;
    0x02,                       //bNumEndpoints
    USB_CLASS_MASS_STORAGE,     //bInterfaceClass;
    0x06,                       //bInterfaceSubClass;
    0x50,                       //bInterfaceProtocol;
    0x00,                       //iInterface;

    USB_DESC_LENGTH_ENDPOINT,   //bLength;
    USB_DESC_TYPE_ENDPOINT,     //type;
    USB_DYNAMIC | USB_DIR_OUT,  //bEndpointAddress;
    USB_EP_ATTR_BULK,           //bmAttributes;
    0x40,                       //wMaxPacketSize;
    0x00,                       //bInterval;

    USB_DESC_LENGTH_ENDPOINT,   //bLength;
    USB_DESC_TYPE_ENDPOINT,     //type;
    USB_DYNAMIC | USB_DIR_IN,   //bEndpointAddress;
    USB_EP_ATTR_BULK,           //bmAttributes;
    0x40,                       //wMaxPacketSize;
    0x00,                       //bInterval;
};

const static char* _ustring[] =
{
    "Language",
    "RT-Thread Team.",
    "RTT Mass Storage",
    "1.1.0",
    "Configuration",
    "Interface",
};

/**
 * This function will allocate an usb device instance from system.
 *
 * @param parent the hub instance to which the new allocated device attached.
 * @param port the hub port.
 *
 * @return the allocate instance on successful, or RT_NULL on failure.
 */
static rt_err_t _inquiry_cmd(udevice_t device, uep_t ep_in)
{
    rt_uint8_t data[36];

    *(rt_uint32_t*)&data[0] = 0x0 | (0x80 << 8);
    *(rt_uint32_t*)&data[4] = 31;

    rt_memset(&data[8], 0x20, 28);
    rt_memcpy(&data[8], "RTT", 3);
    rt_memcpy(&data[16], "USB Disk", 8);

    dcd_ep_write(device->dcd, ep_in, (rt_uint8_t*)&data, 36);

    return RT_EOK;
}

/**
 * This function will handle sense request.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _request_sense(udevice_t device, uep_t ep_in)
{
    struct request_sense_data data;

    data.ErrorCode = 0x70;
    data.Valid     = 0;
    data.SenseKey  = 2; //TODO
    data.Information[0] = 0;
    data.Information[1] = 0;
    data.Information[2] = 0;
    data.Information[3] = 0;
    data.AdditionalSenseLength = 0x0a;
    data.AdditionalSenseCode   = 0x3a; //TODO
    data.AdditionalSenseCodeQualifier =0;

    dcd_ep_write(device->dcd, ep_in, (rt_uint8_t*)&data, sizeof(struct request_sense_data));

    return RT_EOK;
}

/**
 * This function will handle mode_sense_6 request.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _mode_sense_6(udevice_t device, uep_t ep_in)
{
    rt_uint8_t data[4];

    data[0]=3;
    data[1]=0;
    data[2]=0;
    data[3]=0;

    dcd_ep_write(device->dcd, ep_in, (rt_uint8_t*)&data, 4);

    return RT_EOK;
}

/**
 * This function will handle read_capacities request.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _read_capacities(udevice_t device, uep_t ep_in)
{
    rt_uint8_t data[12];
    rt_uint32_t sector_count, sector_size;

    RT_ASSERT(device != RT_NULL);

    sector_count = geometry.sector_count;
    sector_size = geometry.bytes_per_sector;

    *(rt_uint32_t*)&data[0] = 0x08000000;
    data[4] = sector_count >> 24;
    data[5] = 0xff & (sector_count >> 16);
    data[6] = 0xff & (sector_count >> 8);
    data[7] = 0xff & (sector_count);
    data[8] = 0x02;
    data[9] = 0xff & (sector_size >> 16);
    data[10] = 0xff & (sector_size >> 8);
    data[11] = 0xff & sector_size;

    dcd_ep_write(device->dcd, ep_in, (rt_uint8_t*)&data, 12);

    return RT_EOK;
}

/**
 * This function will handle read_capacity request.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _read_capacity(udevice_t device, uep_t ep_in)
{
    rt_uint8_t data[8];
    rt_uint32_t sector_count, sector_size;

    RT_ASSERT(device != RT_NULL);

    sector_count = geometry.sector_count;
    sector_size = geometry.bytes_per_sector;

    data[0] = sector_count >> 24;
    data[1] = 0xff & (sector_count >> 16);
    data[2] = 0xff & (sector_count >> 8);
    data[3] = 0xff & (sector_count);
    data[4] = 0x0;
    data[5] = 0xff & (sector_size >> 16);
    data[6] = 0xff & (sector_size >> 8);
    data[7] = 0xff & sector_size;

    dcd_ep_write(device->dcd, ep_in, (rt_uint8_t*)&data, 8);

    return RT_EOK;
}

/**
 * This function will handle read_10 request.
 *
 * @param device the usb device object.
 * @param cbw the command block wrapper.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _read_10(udevice_t device, ustorage_cbw_t cbw, uep_t ep_in)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(cbw != RT_NULL);

    _block = cbw->cb[2]<<24 | cbw->cb[3]<<16 | cbw->cb[4]<<8  |
             cbw->cb[5]<<0  ;

    _count = cbw->cb[7]<<8 | cbw->cb[8]<<0 ;

    RT_ASSERT(_count < geometry.sector_count);

    rt_device_read(disk, _block, ep_in->buffer, 1);
    dcd_ep_write(device->dcd, ep_in, ep_in->buffer, geometry.bytes_per_sector);
    _count --;
    if (_count)
    {
        _block ++;
        status = STATUS_SEND;
    }
    else
    {
        status = STATUS_CSW;
    }

    return RT_EOK;
}

/**
 * This function will handle write_10 request.
 *
 * @param device the usb device object.
 * @param cbw the command block wrapper.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _write_10(udevice_t device, ustorage_cbw_t cbw, uep_t ep_out)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(cbw != RT_NULL);

    _block = cbw->cb[2]<<24 | cbw->cb[3]<<16 | cbw->cb[4]<<8  |
             cbw->cb[5]<<0  ;
    _count = cbw->cb[7]<<8 | cbw->cb[8]<<0;
    csw.data_reside = cbw->xfer_len;
    _size = _count * geometry.bytes_per_sector;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_write_10 count 0x%x 0x%x\n",
                                _count, geometry.sector_count));

    dcd_ep_read(device->dcd, ep_out, ep_out->buffer, geometry.bytes_per_sector);

    return RT_EOK;
}

/**
 * This function will handle verify_10 request.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _verify_10(udevice_t device)
{
    return RT_EOK;
}

static void _send_status(udevice_t device, mass_eps_t eps, ustorage_csw_t csw)
{
    dcd_ep_write(device->dcd, eps->ep_in, (rt_uint8_t*)csw, SIZEOF_CSW);
    dcd_ep_read(device->dcd, eps->ep_out, eps->ep_out->buffer, SIZEOF_CBW);
    status = STATUS_CBW;   
}

static void _start_stop(ustorage_cbw_t cbw)
{
    //TODO
    _removed = 1;
}

/**
 * This function will handle mass storage bulk in endpoint request.
 *
 * @param device the usb device object.
 * @param size request size.
 *
 * @return RT_EOK.
 */
static rt_err_t _ep_in_handler(udevice_t device, uclass_t cls, rt_size_t size)
{
    mass_eps_t eps;
    RT_ASSERT(device != RT_NULL);

    eps = cls->eps;
    if (status == STATUS_CSW)
    {
        _send_status(device, eps, &csw);
    }
    else if (status == STATUS_SEND)
    {
        rt_device_read(disk, _block, eps->ep_in->buffer, 1);
        dcd_ep_write(device->dcd, eps->ep_in, eps->ep_in->buffer,
                     geometry.bytes_per_sector);
        _count --;
        if (_count)
        {
            _block ++;
            status = STATUS_SEND;
        }
        else
        {
            status = STATUS_CSW;
        }
    }

    return RT_EOK;
}

#ifdef  MASS_CBW_DUMP
static void cbw_dump(struct ustorage_cbw* cbw)
{
    RT_ASSERT(cbw != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("signature 0x%x\n", cbw->signature));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("tag 0x%x\n", cbw->tag));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("xfer_len 0x%x\n", cbw->xfer_len));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("dflags 0x%x\n", cbw->dflags));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("lun 0x%x\n", cbw->lun));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("cb_len 0x%x\n", cbw->cb_len));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("cb[0] 0x%x\n", cbw->cb[0]));
}
#endif

/**
 * This function will handle mass storage bulk out endpoint request.
 *
 * @param device the usb device object.
 * @param size request size.
 *
 * @return RT_EOK.
 */
static rt_err_t _ep_out_handler(udevice_t device, uclass_t cls, rt_size_t size)
{
    mass_eps_t eps;
    RT_ASSERT(device != RT_NULL);

    eps = (mass_eps_t)cls->eps;
    if(status == STATUS_CBW)
    {
        struct ustorage_cbw* cbw;

        /* dump cbw information */
        cbw = (struct ustorage_cbw*)eps->ep_out->buffer;

        if(cbw->signature == CBW_SIGNATURE)
        {
            csw.signature = CSW_SIGNATURE;
            csw.tag = cbw->tag;
            csw.data_reside = 0;
            csw.status = 0;
        }
        else
            return -RT_ERROR;

        switch(cbw->cb[0])
        {
        case SCSI_TEST_UNIT_READY:
            csw.status = _removed;
            _send_status(device, eps, &csw);
            break;
        case SCSI_REQUEST_SENSE:
            _request_sense(device, eps->ep_in);
            status = STATUS_CSW;
            break;
        case SCSI_INQUIRY_CMD:
            _inquiry_cmd(device, eps->ep_in);
            status = STATUS_CSW;
            break;
        case SCSI_MODE_SENSE_6:
            _mode_sense_6(device, eps->ep_in);
            status = STATUS_CSW;
            break;
        case SCSI_ALLOW_MEDIUM_REMOVAL:
            _send_status(device, eps, &csw);
            break;
        case SCSI_READ_CAPACITIES:
            _read_capacities(device, eps->ep_in);
            status = STATUS_CSW;
            break;
        case SCSI_READ_CAPACITY:
            _read_capacity(device, eps->ep_in);
            status = STATUS_CSW;
            break;
        case SCSI_READ_10:
            _read_10(device, cbw, eps->ep_in);
            break;
        case SCSI_WRITE_10:
            _write_10(device, cbw, eps->ep_out);
            status = STATUS_RECEIVE;
            break;
        case SCSI_VERIFY_10:
            _verify_10(device);
            break;
        case SCSI_START_STOP:
            _start_stop(cbw);
            _send_status(device, eps, &csw);
            break;
        }
    }
    else if(status == STATUS_RECEIVE)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("write size 0x%x block 0x%x oount 0x%x\n",
                                    size, _block, _size));

        _size -= size;
        csw.data_reside -= size;

        rt_device_write(disk, _block, eps->ep_in->buffer, 1);
        _block ++;
        if(_size == 0)
        {
            _send_status(device, eps, &csw);
        }
        else
        {
            dcd_ep_read(device->dcd, eps->ep_out, eps->ep_out->buffer,
                        geometry.bytes_per_sector);
        }
    }
    else
    {
        rt_kprintf("none cbw status\n");
    }

    return RT_EOK;
}


/**
 * This function will handle mass storage interface request.
 *
 * @param device the usb device object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _interface_handler(udevice_t device, uclass_t cls, ureq_t setup)
{
    rt_uint8_t lun = 0;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_interface_handler\n"));

    switch(setup->request)
    {
    case USBREQ_GET_MAX_LUN:
        dcd_ep_write(device->dcd, 0, &lun, 1);
        break;
    case USBREQ_MASS_STORAGE_RESET:
        break;
    default:
        rt_kprintf("unknown interface request\n");
        break;
    }

    return RT_EOK;
}

/**
 * This function will run mass storage class, it will be called on handle set configuration request.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _class_run(udevice_t device, uclass_t cls)
{
    mass_eps_t eps;
    rt_uint8_t *buffer;
    RT_ASSERT(device != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("mass storage run\n"));
    eps = (mass_eps_t)cls->eps;

    disk = rt_device_find(RT_USB_MSTORAGE_DISK_NAME);
    if(disk == RT_NULL)
    {
        rt_kprintf("no disk named %s\n", RT_USB_MSTORAGE_DISK_NAME);
        return -RT_ERROR;
    }
    if(rt_device_control(disk, RT_DEVICE_CTRL_BLK_GETGEOME, (void*)&geometry) != RT_EOK)
        return -RT_ERROR;

    buffer = (rt_uint8_t*)rt_malloc(geometry.bytes_per_sector);
    if(buffer == RT_NULL)
        return -RT_ENOMEM;
    eps->ep_out->buffer = buffer;
    eps->ep_in->buffer = buffer;

    dcd_ep_read(device->dcd, eps->ep_out, eps->ep_out->buffer, SIZEOF_CBW);

    return RT_EOK;
}

/**
 * This function will stop mass storage class, it will be called on handle set configuration request.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _class_stop(udevice_t device, uclass_t cls)
{
    mass_eps_t eps;
    RT_ASSERT(device != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("mass storage stop\n"));
    eps = (mass_eps_t)cls->eps;
    rt_free(eps->ep_in->buffer);
    eps->ep_out->buffer = RT_NULL;
    eps->ep_in->buffer = RT_NULL;

    return RT_EOK;
}

static struct uclass_ops ops =
{
    _class_run,
    _class_stop,
    RT_NULL,
};

/**
 * This function will create a mass storage class instance.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK on successful.
 */
uclass_t rt_usbd_class_mstorage_create(udevice_t device)
{
    uintf_t intf;
    mass_eps_t eps;
    uclass_t mstorage;
    ualtsetting_t setting;
    umass_desc_t mass_desc;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);

    /* set usb device string description */
    rt_usbd_device_set_string(device, _ustring);
    /* create a mass storage class */
    mstorage = rt_usbd_class_create(device, &dev_desc, &ops);
    /* create a mass storage endpoints collection */
    eps = (mass_eps_t)rt_malloc(sizeof(struct mass_eps));
    mstorage->eps = (void*)eps;

    /* create an interface */
    intf = rt_usbd_interface_create(device, _interface_handler);

    /* create an alternate setting */
    setting = rt_usbd_altsetting_create(sizeof(struct umass_descriptor));
    /* config desc in alternate setting */
    rt_usbd_altsetting_config_descriptor(setting, &_mass_desc, 0);

    /* create a bulk out and a bulk in endpoint */
    mass_desc = (umass_desc_t)setting->desc;
    eps->ep_in = rt_usbd_endpoint_create(&mass_desc->ep_in_desc, _ep_in_handler);
    eps->ep_out = rt_usbd_endpoint_create(&mass_desc->ep_out_desc, _ep_out_handler);

    /* add the bulk out and bulk in endpoint to the alternate setting */
    rt_usbd_altsetting_add_endpoint(setting, eps->ep_out);
    rt_usbd_altsetting_add_endpoint(setting, eps->ep_in);

    /* add the alternate setting to the interface, then set default setting */
    rt_usbd_interface_add_altsetting(intf, setting);
    rt_usbd_set_altsetting(intf, 0);

    /* add the interface to the mass storage class */
    rt_usbd_class_add_interface(mstorage, intf);

    return mstorage;
}

#endif
