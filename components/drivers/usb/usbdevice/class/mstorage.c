/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-10-01     Yi Qiu       first version
 * 2012-11-25     Heyuanjie87  reduce the memory consumption
 * 2012-12-09     Heyuanjie87  change function and endpoint handler
 * 2013-07-25     Yi Qiu       update for USB CV test
 */

#include <rtthread.h>
#include "drivers/usb_device.h"
#include "mstorage.h"

#ifdef RT_USING_DFS_MNTTABLE
#include "dfs_fs.h"
#endif
#ifdef RT_USB_DEVICE_MSTORAGE
#define MSTRORAGE_INTF_STR_INDEX 11

enum STAT
{
    STAT_CBW,
    STAT_CMD,
    STAT_CSW,
    STAT_RECEIVE,
    STAT_SEND,
};

typedef enum
{
    FIXED,
    COUNT,
    BLOCK_COUNT,
}CB_SIZE_TYPE;

typedef enum
{
    DIR_IN,
    DIR_OUT,
    DIR_NONE,
}CB_DIR;

typedef rt_ssize_t (*cbw_handler)(ufunction_t func, ustorage_cbw_t cbw);

struct scsi_cmd
{
    rt_uint16_t cmd;
    cbw_handler handler;
    rt_size_t cmd_len;
    CB_SIZE_TYPE type;
    rt_size_t data_size;
    CB_DIR dir;
};

struct mstorage
{
    struct ustorage_csw csw_response;
    uep_t ep_in;
    uep_t ep_out;
    int status;
    rt_uint32_t cb_data_size;
    rt_device_t disk;
    rt_uint32_t block;
    rt_int32_t count;
    rt_int32_t size;
    struct scsi_cmd* processing;
    struct rt_device_blk_geometry geometry;
};

rt_align(4)
static struct udevice_descriptor dev_desc =
{
    USB_DESC_LENGTH_DEVICE,     //bLength;
    USB_DESC_TYPE_DEVICE,       //type;
    USB_BCD_VERSION,            //bcdUSB;
    USB_CLASS_MASS_STORAGE,     //bDeviceClass;
    0x06,                       //bDeviceSubClass;
    0x50,                       //bDeviceProtocol;
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
rt_align(4)
static struct usb_qualifier_descriptor dev_qualifier =
{
    sizeof(dev_qualifier),          //bLength
    USB_DESC_TYPE_DEVICEQUALIFIER,  //bDescriptorType
    0x0200,                         //bcdUSB
    USB_CLASS_MASS_STORAGE,         //bDeviceClass
    0x06,                           //bDeviceSubClass
    0x50,                           //bDeviceProtocol
    64,                             //bMaxPacketSize0
    0x01,                           //bNumConfigurations
    0,
};


rt_align(4)
const static struct umass_descriptor _mass_desc =
{
#ifdef RT_USB_DEVICE_COMPOSITE
    /* Interface Association Descriptor */
    {
        USB_DESC_LENGTH_IAD,
        USB_DESC_TYPE_IAD,
        USB_DYNAMIC,
        0x01,
        USB_CLASS_MASS_STORAGE,
        0x06,
        0x50,
        0x00,
    },
#endif
    {
        USB_DESC_LENGTH_INTERFACE,  //bLength;
        USB_DESC_TYPE_INTERFACE,    //type;
        USB_DYNAMIC,                //bInterfaceNumber;
        0x00,                       //bAlternateSetting;
        0x02,                       //bNumEndpoints
        USB_CLASS_MASS_STORAGE,     //bInterfaceClass;
        0x06,                       //bInterfaceSubClass;
        0x50,                       //bInterfaceProtocol;
#ifdef RT_USB_DEVICE_COMPOSITE
        MSTRORAGE_INTF_STR_INDEX,
#else
        0x00,                       //iInterface;
#endif
    },

    {
        USB_DESC_LENGTH_ENDPOINT,   //bLength;
        USB_DESC_TYPE_ENDPOINT,     //type;
        USB_DYNAMIC | USB_DIR_OUT,  //bEndpointAddress;
        USB_EP_ATTR_BULK,           //bmAttributes;
        USB_DYNAMIC,                //wMaxPacketSize;
        0x00,                       //bInterval;
    },

    {
        USB_DESC_LENGTH_ENDPOINT,   //bLength;
        USB_DESC_TYPE_ENDPOINT,     //type;
        USB_DYNAMIC | USB_DIR_IN,   //bEndpointAddress;
        USB_EP_ATTR_BULK,           //bmAttributes;
        USB_DYNAMIC,                //wMaxPacketSize;
        0x00,                       //bInterval;
    },
};

rt_align(4)
const static char* _ustring[] =
{
    "Language",
    "RT-Thread Team.",
    "RTT Mass Storage",
    "320219198301",
    "Configuration",
    "Interface",
};

static rt_ssize_t _test_unit_ready(ufunction_t func, ustorage_cbw_t cbw);
static rt_ssize_t _request_sense(ufunction_t func, ustorage_cbw_t cbw);
static rt_ssize_t _inquiry_cmd(ufunction_t func, ustorage_cbw_t cbw);
static rt_ssize_t _allow_removal(ufunction_t func, ustorage_cbw_t cbw);
static rt_ssize_t _start_stop(ufunction_t func, ustorage_cbw_t cbw);
static rt_ssize_t _mode_sense_6(ufunction_t func, ustorage_cbw_t cbw);
static rt_ssize_t _read_capacities(ufunction_t func, ustorage_cbw_t cbw);
static rt_ssize_t _read_capacity(ufunction_t func, ustorage_cbw_t cbw);
static rt_ssize_t _read_10(ufunction_t func, ustorage_cbw_t cbw);
static rt_ssize_t _write_10(ufunction_t func, ustorage_cbw_t cbw);
static rt_ssize_t _verify_10(ufunction_t func, ustorage_cbw_t cbw);

rt_align(4)
static struct scsi_cmd cmd_data[] =
{
    {SCSI_TEST_UNIT_READY, _test_unit_ready, 6,  FIXED,       0, DIR_NONE},
    {SCSI_REQUEST_SENSE,   _request_sense,   6,  COUNT,       0, DIR_IN},
    {SCSI_INQUIRY_CMD,     _inquiry_cmd,     6,  COUNT,       0, DIR_IN},
    {SCSI_ALLOW_REMOVAL,   _allow_removal,   6,  FIXED,       0, DIR_NONE},
    {SCSI_MODE_SENSE_6,    _mode_sense_6,    6,  COUNT,       0, DIR_IN},
    {SCSI_START_STOP,      _start_stop,      6,  FIXED,       0, DIR_NONE},
    {SCSI_READ_CAPACITIES, _read_capacities, 10, COUNT,       0, DIR_NONE},
    {SCSI_READ_CAPACITY,   _read_capacity,   10, FIXED,       8, DIR_IN},
    {SCSI_READ_10,         _read_10,         10, BLOCK_COUNT, 0, DIR_IN},
    {SCSI_WRITE_10,        _write_10,        10, BLOCK_COUNT, 0, DIR_OUT},
    {SCSI_VERIFY_10,       _verify_10,       10, FIXED,       0, DIR_NONE},
};

static void _send_status(ufunction_t func)
{
    struct mstorage *data;

    RT_ASSERT(func != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_send_status\n"));

    data = (struct mstorage*)func->user_data;
    data->ep_in->request.buffer = (rt_uint8_t*)&data->csw_response;
    data->ep_in->request.size = SIZEOF_CSW;
    data->ep_in->request.req_type = UIO_REQUEST_WRITE;
    rt_usbd_io_request(func->device, data->ep_in, &data->ep_in->request);
    data->status = STAT_CSW;
}

static rt_ssize_t _test_unit_ready(ufunction_t func, ustorage_cbw_t cbw)
{
    struct mstorage *data;

    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_test_unit_ready\n"));

    data = (struct mstorage*)func->user_data;
    data->csw_response.status = 0;

    return 0;
}

static rt_ssize_t _allow_removal(ufunction_t func, ustorage_cbw_t cbw)
{
    struct mstorage *data;

    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_allow_removal\n"));

    data = (struct mstorage*)func->user_data;
    data->csw_response.status = 0;

    return 0;
}

/**
 * This function will handle inquiry command request.
 *
 * @param func the usb function object.
 * @param cbw the command block wrapper.
 *
 * @return RT_EOK on successful.
 */

static rt_ssize_t _inquiry_cmd(ufunction_t func, ustorage_cbw_t cbw)
{
    struct mstorage *data;
    rt_uint8_t *buf;

    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);
    RT_ASSERT(cbw != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_inquiry_cmd\n"));

    data = (struct mstorage*)func->user_data;
    buf = data->ep_in->buffer;

    *(rt_uint32_t*)&buf[0] = 0x0 | (0x80 << 8);
    *(rt_uint32_t*)&buf[4] = 31;

    rt_memset(&buf[8], 0x20, 28);
    rt_memcpy(&buf[8], "RTT", 3);
    rt_memcpy(&buf[16], "USB Disk", 8);

    data->cb_data_size = MIN(data->cb_data_size, SIZEOF_INQUIRY_CMD);
    data->ep_in->request.buffer = buf;
    data->ep_in->request.size = data->cb_data_size;
    data->ep_in->request.req_type = UIO_REQUEST_WRITE;
    rt_usbd_io_request(func->device, data->ep_in, &data->ep_in->request);
    data->status = STAT_CMD;

    return data->cb_data_size;
}

/**
 * This function will handle sense request.
 *
 * @param func the usb function object.
 * @param cbw the command block wrapper.
 *
 * @return RT_EOK on successful.
 */
static rt_ssize_t _request_sense(ufunction_t func, ustorage_cbw_t cbw)
{
    struct mstorage *data;
    struct request_sense_data *buf;

    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);
    RT_ASSERT(cbw != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_request_sense\n"));

    data = (struct mstorage*)func->user_data;
    buf = (struct request_sense_data *)data->ep_in->buffer;

    buf->ErrorCode = 0x70;
    buf->Valid = 0;
    buf->SenseKey = 2;
    buf->Information[0] = 0;
    buf->Information[1] = 0;
    buf->Information[2] = 0;
    buf->Information[3] = 0;
    buf->AdditionalSenseLength = 0x0a;
    buf->AdditionalSenseCode   = 0x3a;
    buf->AdditionalSenseCodeQualifier = 0;

    data->cb_data_size = MIN(data->cb_data_size, SIZEOF_REQUEST_SENSE);
    data->ep_in->request.buffer = (rt_uint8_t*)data->ep_in->buffer;
    data->ep_in->request.size = data->cb_data_size;
    data->ep_in->request.req_type = UIO_REQUEST_WRITE;
    rt_usbd_io_request(func->device, data->ep_in, &data->ep_in->request);
    data->status = STAT_CMD;

    return data->cb_data_size;
}

/**
 * This function will handle mode_sense_6 request.
 *
 * @param func the usb function object.
 * @param cbw the command block wrapper.
 *
 * @return RT_EOK on successful.
 */
static rt_ssize_t _mode_sense_6(ufunction_t func, ustorage_cbw_t cbw)
{
    struct mstorage *data;
    rt_uint8_t *buf;

    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);
    RT_ASSERT(cbw != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_mode_sense_6\n"));

    data = (struct mstorage*)func->user_data;
    buf = data->ep_in->buffer;
    buf[0] = 3;
    buf[1] = 0;
    buf[2] = 0;
    buf[3] = 0;

    data->cb_data_size = MIN(data->cb_data_size, SIZEOF_MODE_SENSE_6);
    data->ep_in->request.buffer = buf;
    data->ep_in->request.size = data->cb_data_size;
    data->ep_in->request.req_type = UIO_REQUEST_WRITE;
    rt_usbd_io_request(func->device, data->ep_in, &data->ep_in->request);
    data->status = STAT_CMD;

    return data->cb_data_size;
}

/**
 * This function will handle read_capacities request.
 *
 * @param func the usb function object.
 * @param cbw the command block wrapper.
 *
 * @return RT_EOK on successful.
 */
static rt_ssize_t _read_capacities(ufunction_t func, ustorage_cbw_t cbw)
{
    struct mstorage *data;
    rt_uint8_t *buf;
    rt_uint32_t sector_count, sector_size;

    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);
    RT_ASSERT(cbw != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_read_capacities\n"));

    data = (struct mstorage*)func->user_data;
    buf = data->ep_in->buffer;
    sector_count = data->geometry.sector_count;
    sector_size = data->geometry.bytes_per_sector;

    *(rt_uint32_t*)&buf[0] = 0x08000000;
    buf[4] = sector_count >> 24;
    buf[5] = 0xff & (sector_count >> 16);
    buf[6] = 0xff & (sector_count >> 8);
    buf[7] = 0xff & (sector_count);
    buf[8] = 0x02;
    buf[9] = 0xff & (sector_size >> 16);
    buf[10] = 0xff & (sector_size >> 8);
    buf[11] = 0xff & sector_size;

    data->cb_data_size = MIN(data->cb_data_size, SIZEOF_READ_CAPACITIES);
    data->ep_in->request.buffer = buf;
    data->ep_in->request.size = data->cb_data_size;
    data->ep_in->request.req_type = UIO_REQUEST_WRITE;
    rt_usbd_io_request(func->device, data->ep_in, &data->ep_in->request);
    data->status = STAT_CMD;

    return data->cb_data_size;
}

/**
 * This function will handle read_capacity request.
 *
 * @param func the usb function object.
 * @param cbw the command block wapper.
 *
 * @return RT_EOK on successful.
 */
static rt_ssize_t _read_capacity(ufunction_t func, ustorage_cbw_t cbw)
{
    struct mstorage *data;

    rt_uint8_t *buf;
    rt_uint32_t sector_count, sector_size;

    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);
    RT_ASSERT(cbw != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_read_capacity\n"));

    data = (struct mstorage*)func->user_data;
    buf = data->ep_in->buffer;
    sector_count = data->geometry.sector_count - 1; /* Last Logical Block Address */
    sector_size = data->geometry.bytes_per_sector;

    buf[0] = sector_count >> 24;
    buf[1] = 0xff & (sector_count >> 16);
    buf[2] = 0xff & (sector_count >> 8);
    buf[3] = 0xff & (sector_count);
    buf[4] = 0x0;
    buf[5] = 0xff & (sector_size >> 16);
    buf[6] = 0xff & (sector_size >> 8);
    buf[7] = 0xff & sector_size;

    data->cb_data_size = MIN(data->cb_data_size, SIZEOF_READ_CAPACITY);
    data->ep_in->request.buffer = buf;
    data->ep_in->request.size = data->cb_data_size;
    data->ep_in->request.req_type = UIO_REQUEST_WRITE;
    rt_usbd_io_request(func->device, data->ep_in, &data->ep_in->request);
    data->status = STAT_CMD;

    return data->cb_data_size;
}

/**
 * This function will handle read_10 request.
 *
 * @param func the usb function object.
 * @param cbw the command block wrapper.
 *
 * @return RT_EOK on successful.
 */
static rt_ssize_t _read_10(ufunction_t func, ustorage_cbw_t cbw)
{
    struct mstorage *data;
    rt_size_t size;

    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);
    RT_ASSERT(cbw != RT_NULL);

    data = (struct mstorage*)func->user_data;
    data->block = cbw->cb[2]<<24 | cbw->cb[3]<<16 | cbw->cb[4]<<8  |
             cbw->cb[5]<<0;
    data->count = cbw->cb[7]<<8 | cbw->cb[8]<<0;

    RT_ASSERT(data->count < data->geometry.sector_count);

    data->csw_response.data_reside = data->cb_data_size;
    size = rt_device_read(data->disk, data->block, data->ep_in->buffer, 1);
    if(size == 0)
    {
        rt_kprintf("read data error\n");
    }

    data->ep_in->request.buffer = data->ep_in->buffer;
    data->ep_in->request.size = data->geometry.bytes_per_sector;
    data->ep_in->request.req_type = UIO_REQUEST_WRITE;
    rt_usbd_io_request(func->device, data->ep_in, &data->ep_in->request);
    data->status = STAT_SEND;

    return data->geometry.bytes_per_sector;
}

/**
 * This function will handle write_10 request.
 *
 * @param func the usb function object.
 * @param cbw the command block wrapper.
 *
 * @return RT_EOK on successful.
 */
static rt_ssize_t _write_10(ufunction_t func, ustorage_cbw_t cbw)
{
    struct mstorage *data;

    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);
    RT_ASSERT(cbw != RT_NULL);

    data = (struct mstorage*)func->user_data;

    data->block = cbw->cb[2]<<24 | cbw->cb[3]<<16 | cbw->cb[4]<<8  |
             cbw->cb[5]<<0;
    data->count = cbw->cb[7]<<8 | cbw->cb[8];
    data->csw_response.data_reside = cbw->xfer_len;
    data->size = data->count * data->geometry.bytes_per_sector;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_write_10 count 0x%x block 0x%x 0x%x\n",
                                data->count, data->block, data->geometry.sector_count));

    data->csw_response.data_reside = data->cb_data_size;

    data->ep_out->request.buffer = data->ep_out->buffer;
    data->ep_out->request.size = data->geometry.bytes_per_sector;
    data->ep_out->request.req_type = UIO_REQUEST_READ_FULL;
    rt_usbd_io_request(func->device, data->ep_out, &data->ep_out->request);
    data->status = STAT_RECEIVE;

    return data->geometry.bytes_per_sector;
}

/**
 * This function will handle verify_10 request.
 *
 * @param func the usb function object.
 *
 * @return RT_EOK on successful.
 */
static rt_ssize_t _verify_10(ufunction_t func, ustorage_cbw_t cbw)
{
    struct mstorage *data;

    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_verify_10\n"));

    data = (struct mstorage*)func->user_data;
    data->csw_response.status = 0;

    return 0;
}

static rt_ssize_t _start_stop(ufunction_t func,
    ustorage_cbw_t cbw)
{
    struct mstorage *data;

    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_start_stop\n"));

    data = (struct mstorage*)func->user_data;
    data->csw_response.status = 0;

    return 0;
}

static rt_err_t _ep_in_handler(ufunction_t func, rt_size_t size)
{
    struct mstorage *data;

    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_ep_in_handler\n"));

    data = (struct mstorage*)func->user_data;

    switch(data->status)
    {
    case STAT_CSW:
        if(data->ep_in->request.size != SIZEOF_CSW)
        {
            rt_kprintf("Size of csw command error\n");
            rt_usbd_ep_set_stall(func->device, data->ep_in);
        }
        else
        {
            RT_DEBUG_LOG(RT_DEBUG_USB, ("return to cbw status\n"));
            data->ep_out->request.buffer = data->ep_out->buffer;
            data->ep_out->request.size = SIZEOF_CBW;
            data->ep_out->request.req_type = UIO_REQUEST_READ_FULL;
            rt_usbd_io_request(func->device, data->ep_out, &data->ep_out->request);
            data->status = STAT_CBW;
        }
        break;
     case STAT_CMD:
        if(data->csw_response.data_reside == 0xFF)
        {
            data->csw_response.data_reside = 0;
        }
        else
        {
            data->csw_response.data_reside -= data->ep_in->request.size;
            if(data->csw_response.data_reside != 0)
            {
                RT_DEBUG_LOG(RT_DEBUG_USB, ("data_reside %d, request %d\n",
                    data->csw_response.data_reside, data->ep_in->request.size));
                if(data->processing->dir == DIR_OUT)
                {
                    rt_usbd_ep_set_stall(func->device, data->ep_out);
                }
                else
                {
                    //rt_kprintf("warning:in stall path but not stall\n");

                    /* FIXME: Disable the operation or the disk cannot work. */
                    //rt_usbd_ep_set_stall(func->device, data->ep_in);
                }
                data->csw_response.data_reside = 0;
            }
            }
        _send_status(func);
        break;
     case STAT_SEND:
        data->csw_response.data_reside -= data->ep_in->request.size;
        data->count--;
        data->block++;
        if(data->count > 0 && data->csw_response.data_reside > 0)
        {
            if(rt_device_read(data->disk, data->block, data->ep_in->buffer, 1) == 0)
            {
                rt_kprintf("disk read error\n");
                rt_usbd_ep_set_stall(func->device, data->ep_in);
                return -RT_ERROR;
            }

            data->ep_in->request.buffer = data->ep_in->buffer;
            data->ep_in->request.size = data->geometry.bytes_per_sector;
            data->ep_in->request.req_type = UIO_REQUEST_WRITE;
            rt_usbd_io_request(func->device, data->ep_in, &data->ep_in->request);
        }
        else
        {
            _send_status(func);
        }
        break;
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

static struct scsi_cmd* _find_cbw_command(rt_uint16_t cmd)
{
    int i;

    for(i=0; i<sizeof(cmd_data)/sizeof(struct scsi_cmd); i++)
    {
        if(cmd_data[i].cmd == cmd)
            return &cmd_data[i];
    }

    return RT_NULL;
}

static void _cb_len_calc(ufunction_t func, struct scsi_cmd* cmd,
    ustorage_cbw_t cbw)
{
    struct mstorage *data;

    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(cmd != RT_NULL);
    RT_ASSERT(cbw != RT_NULL);

    data = (struct mstorage*)func->user_data;
    if(cmd->cmd_len == 6)
    {
        switch(cmd->type)
        {
        case COUNT:
            data->cb_data_size = cbw->cb[4];
            break;
        case BLOCK_COUNT:
            data->cb_data_size = cbw->cb[4] * data->geometry.bytes_per_sector;
            break;
        case FIXED:
            data->cb_data_size = cmd->data_size;
            break;
        default:
            break;
        }
    }
    else if(cmd->cmd_len == 10)
    {
        switch(cmd->type)
        {
        case COUNT:
            data->cb_data_size = cbw->cb[7]<<8 | cbw->cb[8];
            break;
        case BLOCK_COUNT:
            data->cb_data_size = (cbw->cb[7]<<8 | cbw->cb[8]) *
                data->geometry.bytes_per_sector;
            break;
        case FIXED:
            data->cb_data_size = cmd->data_size;
            break;
        default:
            break;
        }
    }

    //workaround: for stability in full-speed mode
    else if(cmd->cmd_len == 12)
    {
        switch(cmd->type)
        {
        case COUNT:
            data->cb_data_size = cbw->cb[4];
            break;
        default:
            break;
        }
    }
    else
    {
        rt_kprintf("cmd_len error %d\n", cmd->cmd_len);
    }
}

static rt_bool_t _cbw_verify(ufunction_t func, struct scsi_cmd* cmd,
    ustorage_cbw_t cbw)
{
    struct mstorage *data;

    RT_ASSERT(cmd != RT_NULL);
    RT_ASSERT(cbw != RT_NULL);
    RT_ASSERT(func != RT_NULL);

    data = (struct mstorage*)func->user_data;
    if(cmd->cmd_len != cbw->cb_len)
    {
        rt_kprintf("cb_len error\n");
        cmd->cmd_len = cbw->cb_len;
    }

    if(cbw->xfer_len > 0 && data->cb_data_size == 0)
    {
        rt_kprintf("xfer_len > 0 && data_size == 0\n");
        return RT_FALSE;
    }

    if(cbw->xfer_len == 0 && data->cb_data_size > 0)
    {
        rt_kprintf("xfer_len == 0 && data_size > 0");
        return RT_FALSE;
    }

    if(((cbw->dflags & USB_DIR_IN) && (cmd->dir == DIR_OUT)) ||
        (!(cbw->dflags & USB_DIR_IN) && (cmd->dir == DIR_IN)))
    {
        rt_kprintf("dir error\n");
        return RT_FALSE;
    }

    if(cbw->xfer_len > data->cb_data_size)
    {
        rt_kprintf("xfer_len > data_size\n");
        return RT_FALSE;
    }

    if(cbw->xfer_len < data->cb_data_size)
    {
        rt_kprintf("xfer_len < data_size\n");
        data->cb_data_size = cbw->xfer_len;
        data->csw_response.status = 1;
    }

    return RT_TRUE;
}

static rt_ssize_t _cbw_handler(ufunction_t func, struct scsi_cmd* cmd,
    ustorage_cbw_t cbw)
{
    struct mstorage *data;

    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(cbw != RT_NULL);
    RT_ASSERT(cmd->handler != RT_NULL);

    data = (struct mstorage*)func->user_data;
    data->processing = cmd;
    return cmd->handler(func, cbw);
}

/**
 * This function will handle mass storage bulk out endpoint request.
 *
 * @param func the usb function object.
 * @param size request size.
 *
 * @return RT_EOK.
 */
static rt_err_t _ep_out_handler(ufunction_t func, rt_size_t size)
{
    struct mstorage *data;
    struct scsi_cmd* cmd;
    rt_size_t len;
    struct ustorage_cbw* cbw;

    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_ep_out_handler %d\n", size));

    data = (struct mstorage*)func->user_data;
    cbw = (struct ustorage_cbw*)data->ep_out->buffer;
    if(data->status == STAT_CBW)
    {
        /* dump cbw information */
        if(cbw->signature != CBW_SIGNATURE || size != SIZEOF_CBW)
        {
            goto exit;
        }

        data->csw_response.signature = CSW_SIGNATURE;
        data->csw_response.tag = cbw->tag;
        data->csw_response.data_reside = cbw->xfer_len;
        data->csw_response.status = 0;

        RT_DEBUG_LOG(RT_DEBUG_USB, ("ep_out reside %d\n", data->csw_response.data_reside));

        cmd = _find_cbw_command(cbw->cb[0]);
        if(cmd == RT_NULL)
        {
            rt_kprintf("can't find cbw command\n");
            goto exit;
        }

        _cb_len_calc(func, cmd, cbw);
        if(!_cbw_verify(func, cmd, cbw))
        {
            goto exit;
        }

        len = _cbw_handler(func, cmd, cbw);
        if(len == 0)
        {
            _send_status(func);
        }

        return RT_EOK;
    }
    else if(data->status == STAT_RECEIVE)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("\nwrite size %d block 0x%x oount 0x%x\n",
                                    size, data->block, data->size));

        data->size -= size;
        data->csw_response.data_reside -= size;

        rt_device_write(data->disk, data->block, data->ep_out->buffer, 1);

        if(data->csw_response.data_reside != 0)
        {
            data->ep_out->request.buffer = data->ep_out->buffer;
            data->ep_out->request.size = data->geometry.bytes_per_sector;
            data->ep_out->request.req_type = UIO_REQUEST_READ_FULL;
            rt_usbd_io_request(func->device, data->ep_out, &data->ep_out->request);
            data->block ++;
        }
        else
        {
            _send_status(func);
        }

        return RT_EOK;
    }

exit:
    if(data->csw_response.data_reside)
    {
        if(cbw->dflags & USB_DIR_IN)
        {
            rt_usbd_ep_set_stall(func->device, data->ep_in);
        }
        else
        {
            rt_usbd_ep_set_stall(func->device, data->ep_in);
            rt_usbd_ep_set_stall(func->device, data->ep_out);
        }
    }
    data->csw_response.status = 1;
    _send_status(func);

    return -RT_ERROR;
}

/**
 * This function will handle mass storage interface request.
 *
 * @param func the usb function object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _interface_handler(ufunction_t func, ureq_t setup)
{
    rt_uint8_t lun = 0;

    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(func->device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("mstorage_interface_handler\n"));

    switch(setup->bRequest)
    {
    case USBREQ_GET_MAX_LUN:

        RT_DEBUG_LOG(RT_DEBUG_USB, ("USBREQ_GET_MAX_LUN\n"));

        if(setup->wValue || setup->wLength != 1)
        {
            rt_usbd_ep0_set_stall(func->device);
        }
        else
        {
            rt_usbd_ep0_write(func->device, &lun, setup->wLength);
        }
        break;
    case USBREQ_MASS_STORAGE_RESET:

        RT_DEBUG_LOG(RT_DEBUG_USB, ("USBREQ_MASS_STORAGE_RESET\n"));

        if(setup->wValue || setup->wLength != 0)
        {
            rt_usbd_ep0_set_stall(func->device);
        }
        else
        {
            dcd_ep0_send_status(func->device->dcd);
        }
        break;
    default:
        rt_kprintf("unknown interface request\n");
        break;
    }

    return RT_EOK;
}

/**
 * This function will run mass storage function, it will be called on handle set configuration request.
 *
 * @param func the usb function object.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _function_enable(ufunction_t func)
{
    struct mstorage *data;
    RT_ASSERT(func != RT_NULL);
    RT_DEBUG_LOG(RT_DEBUG_USB, ("Mass storage function enabled\n"));
    data = (struct mstorage*)func->user_data;

    data->disk = rt_device_find(RT_USB_MSTORAGE_DISK_NAME);
    if(data->disk == RT_NULL)
    {
        rt_kprintf("no data->disk named %s\n", RT_USB_MSTORAGE_DISK_NAME);
        return -RT_ERROR;
    }

#ifdef RT_USING_DFS_MNTTABLE
    dfs_unmount_device(data->disk);
#endif

    if(rt_device_open(data->disk, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("disk open error\n");
        return -RT_ERROR;
    }

    if(rt_device_control(data->disk, RT_DEVICE_CTRL_BLK_GETGEOME,
        (void*)&data->geometry) != RT_EOK)
    {
        rt_kprintf("get disk info error\n");
        return -RT_ERROR;
    }

    data->ep_in->buffer = (rt_uint8_t*)rt_malloc(data->geometry.bytes_per_sector);
    if(data->ep_in->buffer == RT_NULL)
    {
        rt_kprintf("no memory\n");
        return -RT_ENOMEM;
    }
    data->ep_out->buffer = (rt_uint8_t*)rt_malloc(data->geometry.bytes_per_sector);
    if(data->ep_out->buffer == RT_NULL)
    {
        rt_free(data->ep_in->buffer);
        rt_kprintf("no memory\n");
        return -RT_ENOMEM;
    }

    /* prepare to read CBW request */
    data->ep_out->request.buffer = data->ep_out->buffer;
    data->ep_out->request.size = SIZEOF_CBW;
    data->ep_out->request.req_type = UIO_REQUEST_READ_FULL;
    rt_usbd_io_request(func->device, data->ep_out, &data->ep_out->request);

    return RT_EOK;
}

/**
 * This function will stop mass storage function, it will be called on handle set configuration request.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _function_disable(ufunction_t func)
{
    struct mstorage *data;
    RT_ASSERT(func != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("Mass storage function disabled\n"));

    data = (struct mstorage*)func->user_data;
    if(data->ep_in->buffer != RT_NULL)
    {
        rt_free(data->ep_in->buffer);
        data->ep_in->buffer = RT_NULL;
    }

    if(data->ep_out->buffer != RT_NULL)
    {
        rt_free(data->ep_out->buffer);
        data->ep_out->buffer = RT_NULL;
    }
    if(data->disk != RT_NULL)
    {
        rt_device_close(data->disk);
#ifdef RT_USING_DFS_MNTTABLE
        dfs_mount_device(data->disk);
#endif
        data->disk = RT_NULL;
    }

    data->status = STAT_CBW;

    return RT_EOK;
}

static struct ufunction_ops ops =
{
    _function_enable,
    _function_disable,
    RT_NULL,
};
static rt_err_t _mstorage_descriptor_config(umass_desc_t desc, rt_uint8_t cintf_nr, rt_uint8_t device_is_hs)
{
#ifdef RT_USB_DEVICE_COMPOSITE
    desc->iad_desc.bFirstInterface = cintf_nr;
#endif
    desc->ep_out_desc.wMaxPacketSize = device_is_hs ? 512 : 64;
    desc->ep_in_desc.wMaxPacketSize = device_is_hs ? 512 : 64;
    return RT_EOK;
}
/**
 * This function will create a mass storage function instance.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK on successful.
 */
ufunction_t rt_usbd_function_mstorage_create(udevice_t device)
{
    uintf_t intf;
    struct mstorage *data;
    ufunction_t func;
    ualtsetting_t setting;
    umass_desc_t mass_desc;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);

    /* set usb device string description */
#ifdef RT_USB_DEVICE_COMPOSITE
    rt_usbd_device_set_interface_string(device, MSTRORAGE_INTF_STR_INDEX, _ustring[2]);
#else
    rt_usbd_device_set_string(device, _ustring);
#endif

    /* create a mass storage function */
    func = rt_usbd_function_new(device, &dev_desc, &ops);
    device->dev_qualifier = &dev_qualifier;

    /* allocate memory for mass storage function data */
    data = (struct mstorage*)rt_malloc(sizeof(struct mstorage));
    rt_memset(data, 0, sizeof(struct mstorage));
    func->user_data = (void*)data;

    /* create an interface object */
    intf = rt_usbd_interface_new(device, _interface_handler);

    /* create an alternate setting object */
    setting = rt_usbd_altsetting_new(sizeof(struct umass_descriptor));

    /* config desc in alternate setting */
    rt_usbd_altsetting_config_descriptor(setting, &_mass_desc, (rt_off_t)&((umass_desc_t)0)->intf_desc);

    /* configure the msc interface descriptor */
    _mstorage_descriptor_config(setting->desc, intf->intf_num, device->dcd->device_is_hs);

    /* create a bulk out and a bulk in endpoint */
    mass_desc = (umass_desc_t)setting->desc;
    data->ep_in = rt_usbd_endpoint_new(&mass_desc->ep_in_desc, _ep_in_handler);
    data->ep_out = rt_usbd_endpoint_new(&mass_desc->ep_out_desc, _ep_out_handler);

    /* add the bulk out and bulk in endpoint to the alternate setting */
    rt_usbd_altsetting_add_endpoint(setting, data->ep_out);
    rt_usbd_altsetting_add_endpoint(setting, data->ep_in);

    /* add the alternate setting to the interface, then set default setting */
    rt_usbd_interface_add_altsetting(intf, setting);
    rt_usbd_set_altsetting(intf, 0);

    /* add the interface to the mass storage function */
    rt_usbd_function_add_interface(func, intf);

    return func;
}
struct udclass msc_class =
{
    .rt_usbd_function_create = rt_usbd_function_mstorage_create
};

int rt_usbd_msc_class_register(void)
{
    rt_usbd_class_register(&msc_class);
    return 0;
}
INIT_PREV_EXPORT(rt_usbd_msc_class_register);

#endif
