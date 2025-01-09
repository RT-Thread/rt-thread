/*!
    \file    usb_iap_core.c
    \brief   IAP driver

    \version 2024-07-31, V1.1.0, firmware for GD32F5xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "usb_iap_core.h"
#include "flash_operation.h"
#include <string.h>

#define USBD_VID                     0x28E9U
#define USBD_PID                     0x3228U

/* Note:it should use the C99 standard when compiling the below codes */
/* USB standard device descriptor */
__ALIGN_BEGIN const usb_desc_dev iap_dev_desc __ALIGN_END = {
    .header =
    {
        .bLength          = USB_DEV_DESC_LEN,
        .bDescriptorType  = USB_DESCTYPE_DEV
    },
    .bcdUSB                = 0x0200U,
    .bDeviceClass          = 0x00U,
    .bDeviceSubClass       = 0x00U,
    .bDeviceProtocol       = 0x00U,
    .bMaxPacketSize0       = USB_FS_EP0_MAX_LEN,
    .idVendor              = USBD_VID,
    .idProduct             = USBD_PID,
    .bcdDevice             = 0x0100U,
    .iManufacturer         = STR_IDX_MFC,
    .iProduct              = STR_IDX_PRODUCT,
    .iSerialNumber         = STR_IDX_SERIAL,
    .bNumberConfigurations = USBD_CFG_MAX_NUM
};

__ALIGN_BEGIN const usb_hid_desc_config_set iap_config_desc __ALIGN_END = {
    .config =
    {
        .header =
        {
            .bLength         = sizeof(usb_desc_config),
            .bDescriptorType = USB_DESCTYPE_CONFIG
        },
        .wTotalLength         = USB_DESC_LEN_IAP_CONFIG_SET,
        .bNumInterfaces       = 0x01U,
        .bConfigurationValue  = 0x01U,
        .iConfiguration       = 0x00U,
        .bmAttributes         = 0x80U,
        .bMaxPower            = 0x32U
    },

    .hid_itf =
    {
        .header =
        {
            .bLength         = sizeof(usb_desc_itf),
            .bDescriptorType = USB_DESCTYPE_ITF
        },
        .bInterfaceNumber     = 0x00U,
        .bAlternateSetting    = 0x00U,
        .bNumEndpoints        = 0x02U,
        .bInterfaceClass      = USB_HID_CLASS,
        .bInterfaceSubClass   = 0x00U,
        .bInterfaceProtocol   = 0x00U,
        .iInterface           = 0x00U
    },

    .hid_vendor =
    {
        .header =
        {
            .bLength         = sizeof(usb_desc_hid),
            .bDescriptorType = USB_DESCTYPE_HID
        },
        .bcdHID               = 0x0111U,
        .bCountryCode         = 0x00U,
        .bNumDescriptors      = 0x01U,
        .bDescriptorType      = USB_DESCTYPE_REPORT,
        .wDescriptorLength    = USB_DESC_LEN_IAP_REPORT
    },

    .hid_epin =
    {
        .header =
        {
            .bLength         = sizeof(usb_desc_ep),
            .bDescriptorType = USB_DESCTYPE_EP
        },
        .bEndpointAddress     = IAP_IN_EP,
        .bmAttributes         = USB_EP_ATTR_INT,
        .wMaxPacketSize       = IAP_IN_PACKET,
        .bInterval            = 0x01U
    },

    .hid_epout =
    {
        .header =
        {
            .bLength         = sizeof(usb_desc_ep),
            .bDescriptorType = USB_DESCTYPE_EP
        },
        .bEndpointAddress     = IAP_OUT_EP,
        .bmAttributes         = USB_EP_ATTR_INT,
        .wMaxPacketSize       = IAP_OUT_PACKET,
        .bInterval            = 0x01U
    }
};

/* USB language ID Descriptor */
static __ALIGN_BEGIN const usb_desc_LANGID usbd_language_id_desc __ALIGN_END = {
    .header =
    {
        .bLength         = sizeof(usb_desc_LANGID),
        .bDescriptorType = USB_DESCTYPE_STR
    },
    .wLANGID              = ENG_LANGID
};

/* USB manufacture string */
static __ALIGN_BEGIN const usb_desc_str manufacturer_string __ALIGN_END = {
    .header =
    {
        .bLength         = USB_STRING_LEN(10U),
        .bDescriptorType = USB_DESCTYPE_STR
    },
    .unicode_string = {'G', 'i', 'g', 'a', 'D', 'e', 'v', 'i', 'c', 'e'}
};

/* USB product string */
static __ALIGN_BEGIN const usb_desc_str product_string __ALIGN_END = {
    .header =
    {
        .bLength         = USB_STRING_LEN(12U),
        .bDescriptorType = USB_DESCTYPE_STR
    },
    .unicode_string = {'G', 'D', '3', '2', '-', 'U', 'S', 'B', '_', 'I', 'A', 'P'}
};

/* USB serial string */
static __ALIGN_BEGIN usb_desc_str serial_string __ALIGN_END = {
    .header =
    {
        .bLength         = USB_STRING_LEN(2U),
        .bDescriptorType = USB_DESCTYPE_STR
    }
};

void *const usbd_iap_strings[] = {
    [STR_IDX_LANGID]  = (uint8_t *) &usbd_language_id_desc,
    [STR_IDX_MFC]     = (uint8_t *) &manufacturer_string,
    [STR_IDX_PRODUCT] = (uint8_t *) &product_string,
    [STR_IDX_SERIAL]  = (uint8_t *) &serial_string
};

usb_desc iap_desc = {
    .dev_desc    = (uint8_t *) &iap_dev_desc,
    .config_desc = (uint8_t *) &iap_config_desc,
    .strings     = usbd_iap_strings
};

/* local function prototypes ('static') */
static uint8_t iap_init(usb_dev *udev, uint8_t config_index);
static uint8_t iap_deinit(usb_dev *udev, uint8_t config_index);
static uint8_t iap_req_handler(usb_dev *udev, usb_req *req);
static uint8_t iap_data_out(usb_dev *udev, uint8_t ep_num);

/* IAP requests management functions */
static void iap_req_erase(usb_dev *udev);
static void iap_req_download(usb_dev *udev);
static void iap_req_read_optionbyte(usb_dev *udev);
static void iap_req_write_optionbyte(usb_dev *udev);
static void iap_req_leave(usb_dev *udev);
static void iap_address_send(usb_dev *udev);
static void iap_req_upload(usb_dev *udev);
static void iap_check_rdp(usb_dev *udev);

usb_class_core iap_class = {
    .init            = iap_init,
    .deinit          = iap_deinit,
    .req_proc        = iap_req_handler,
    .data_out        = iap_data_out
};

/* USB custom HID device report descriptor */
__ALIGN_BEGIN const uint8_t iap_report_desc[USB_DESC_LEN_IAP_REPORT] __ALIGN_END = {
    0x05U, 0x01U,     /* USAGE_PAGE (Generic Desktop) */
    0x09U, 0x00U,     /* USAGE (Custom Device)        */
    0xa1U, 0x01U,     /* COLLECTION (Application)     */

    /* IAP command and data */
    0x85U, 0x01U,     /* REPORT_ID (0x01)          */
    0x09U, 0x01U,     /* USAGE (IAP command)       */
    0x15U, 0x00U,     /* LOGICAL_MINIMUM (0)       */
    0x25U, 0xffU,     /* LOGICAL_MAXIMUM (255)     */
    0x75U, 0x08U,     /* REPORT_SIZE (8)           */
#ifdef USE_USB_FS
    0x95U, REPORT_OUT_COUNT,
#else
#ifdef USE_ULPI_PHY
    0x96U, BYTE_LOW(REPORT_OUT_COUNT), BYTE_HIGH(REPORT_OUT_COUNT),
#elif defined(USE_EMBEDDED_PHY)
    0x95U, REPORT_OUT_COUNT,
#endif
#endif
    0x91U, 0x82U,     /* OUTPUT (Data,Var,Abs,Vol) */

    /* device status and option byte */
    0x85U, 0x02U,     /* REPORT_ID (0x02)               */
    0x09U, 0x02U,     /* USAGE (Status and option byte) */
    0x15U, 0x00U,     /* LOGICAL_MINIMUM (0)            */
    0x25U, 0xffU,     /* LOGICAL_MAXIMUM (255)          */
    0x75U, 0x08U,     /* REPORT_SIZE (8)                */

#ifdef USE_USB_FS
    0x95U, REPORT_IN_COUNT,
#else
#ifdef USE_ULPI_PHY
    0x96U, BYTE_LOW(REPORT_IN_COUNT), BYTE_HIGH(REPORT_IN_COUNT),
#elif defined(USE_EMBEDDED_PHY)
    0x95U, REPORT_IN_COUNT,
#endif
#endif
    0x81U, 0x82U,     /* INPUT (Data,Var,Abs,Vol)       */

    0xc0U             /* END_COLLECTION            */
};

/*!
    \brief      send IAP report
    \param[in]  udev: pointer to USB device instance
    \param[in]  report: pointer to HID report
    \param[in]  len: data length
    \param[out] none
    \retval     USB device operation status
*/
uint8_t iap_report_send(usb_dev *udev, uint8_t *report, uint32_t len)
{
    usbd_ep_send(udev, IAP_IN_EP, report, len);

    return USBD_OK;
}

/*!
    \brief      initialize the IAP device
    \param[in]  udev: pointer to usb device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t iap_init(usb_dev *udev, uint8_t config_index)
{
    static __ALIGN_BEGIN usbd_iap_handler iap_handler __ALIGN_END;

    /* initialize Tx endpoint */
    usbd_ep_setup(udev, &(iap_config_desc.hid_epin));

    /* initialize Rx endpoint */
    usbd_ep_setup(udev, &(iap_config_desc.hid_epout));

    memset((void *)&iap_handler, 0U, sizeof(usbd_iap_handler));

    /* prepare receive data */
    usbd_ep_recev(udev, IAP_OUT_EP, iap_handler.report_buf, IAP_OUT_PACKET);

    iap_handler.base_address = APP_LOADED_ADDR;

    udev->dev.class_data[USBD_IAP_INTERFACE] = (void *)&iap_handler;

    return USBD_OK;
}

/*!
    \brief      deinitialize the IAP device
    \param[in]  udev: pointer to usb device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t iap_deinit(usb_dev *udev, uint8_t config_index)
{
    /* deinitialize IAP endpoints */
    usbd_ep_clear(udev, IAP_IN_EP);
    usbd_ep_clear(udev, IAP_OUT_EP);

    return USBD_OK;
}

/*!
    \brief      handle the IAP class-specific requests
    \param[in]  udev: pointer to usb device instance
    \param[in]  req: device class-specific request
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t iap_req_handler(usb_dev *udev, usb_req *req)
{
    usb_transc *transc = &udev->dev.transc_in[0];
    usbd_iap_handler *iap = (usbd_iap_handler *)udev->dev.class_data[USBD_IAP_INTERFACE];

    switch(req->bRequest) {
    case GET_REPORT:
        /* no use for this driver */
        break;

    case GET_IDLE:
        transc->xfer_buf = (uint8_t *)&iap->idlestate;
        transc->remain_len = 1U;
        break;

    case GET_PROTOCOL:
        transc->xfer_buf = (uint8_t *)&iap->protocol;
        transc->remain_len = 1U;
        break;

    case SET_REPORT:
        iap->reportID = (uint8_t)(req->wValue);
        break;

    case SET_IDLE:
        iap->idlestate = (uint8_t)(req->wValue >> 8U);
        break;

    case SET_PROTOCOL:
        iap->protocol = (uint8_t)(req->wValue);
        break;

    case USB_GET_DESCRIPTOR:
        if(USB_DESCTYPE_REPORT == (req->wValue >> 8U)) {
            transc->remain_len = USB_MIN(USB_DESC_LEN_IAP_REPORT, req->wLength);
            transc->xfer_buf = (uint8_t *)iap_report_desc;
        }
        break;

    default:
        return USBD_FAIL;
    }

    return USBD_OK;
}

/*!
    \brief      handle data out stage
    \param[in]  udev: pointer to usb device instance
    \param[in]  ep_num: endpoint identifier
    \param[out] none
    \retval     none
*/
static uint8_t iap_data_out(usb_dev *udev, uint8_t ep_num)
{
    usbd_iap_handler *iap = (usbd_iap_handler *)udev->dev.class_data[USBD_IAP_INTERFACE];

    if(IAP_HOST_ID == iap->report_buf[0]) {
        switch(iap->report_buf[1]) {
        case IAP_DOWNLOAD:
            iap_req_download(udev);
            break;

        case IAP_ERASE:
            iap_req_erase(udev);
            break;

        case IAP_READ_OPTION_BYTE:
            iap_req_read_optionbyte(udev);
            break;

        case IAP_LEAVE:
            iap_req_leave(udev);
            break;

        case IAP_GETBIN_ADDRESS:
            iap_address_send(udev);
            break;

        case IAP_WRITE_OPTION_BYTE:
            iap_req_write_optionbyte(udev);
            break;

        case IAP_UPLOAD:
            iap_req_upload(udev);
            break;

        case IAP_CHECK_RDP:
            iap_check_rdp(udev);
            break;

        default:
            break;
        }
    }

    usbd_ep_recev(udev, IAP_OUT_EP, iap->report_buf, IAP_OUT_PACKET);

    return USBD_OK;
}

/*!
    \brief      handle the IAP_DOWNLOAD request
    \param[in]  udev: pointer to usb device instance
    \param[out] none
    \retval     none
*/
static void iap_req_download(usb_dev *udev)
{
    usbd_iap_handler *iap = (usbd_iap_handler *)udev->dev.class_data[USBD_IAP_INTERFACE];

    iap->dev_status[0] = IAP_DEVICE_ID;

    /* get the target address to download */
    iap->base_address  = iap->report_buf[2];
    iap->base_address |= (uint32_t)iap->report_buf[3] << 8U;
    iap->base_address |= (uint32_t)iap->report_buf[4] << 16U;
    iap->base_address |= (uint32_t)iap->report_buf[5] << 24U;

    /* program the target address */
    if(FMC_READY == iap_data_write(&iap->report_buf[6], iap->base_address, TRANSFER_SIZE)) {
        iap->dev_status[1] = OPERATION_SUCCESS;
    } else {
        iap->dev_status[1] = OPERATION_FAIL;
    }

    iap_report_send(udev, iap->dev_status, IAP_IN_PACKET);
}

/*!
    \brief      handle the IAP_WRITE_OPTION_BYTE request
    \param[in]  udev: pointer to usb device instance
    \param[out] none
    \retval     none
*/
static void iap_req_write_optionbyte(usb_dev *udev)
{
    uint32_t option_byte_addr = 0U;
    uint16_t option_byte_size = 0U;
    usbd_iap_handler *iap = (usbd_iap_handler *)udev->dev.class_data[USBD_IAP_INTERFACE];

    /* get option byte address address */
    option_byte_addr  = iap->report_buf[2];
    option_byte_addr |= (uint32_t)iap->report_buf[3] << 8U;
    option_byte_addr |= (uint32_t)iap->report_buf[4] << 16U;
    option_byte_addr |= (uint32_t)iap->report_buf[5] << 24U;

    /* get option byte address size */
    if(OPT_BYTE_ADDR1 == option_byte_addr) {
        option_byte_size = OPT_BYTE_SIZE1;
    } else if(OPT_BYTE_ADDR2 == option_byte_addr) {
        option_byte_size = OPT_BYTE_SIZE2;
    } else if(EFUSE_BYTE_ADDR == option_byte_addr) {
        option_byte_size = EFUSE_BYTE_SIZE;
    }

    iap->dev_status[0] = IAP_DEVICE_ID;
    /* write option byte address data */
    if(FMC_READY == option_byte_write(option_byte_addr, &iap->report_buf[6], option_byte_size)) {
        iap->dev_status[1] = OB_WRITE_SUCCESS;
    } else {
        iap->dev_status[1] = OPERATION_FAIL;
    }

    iap_report_send(udev, iap->dev_status, IAP_IN_PACKET);
}

/*!
    \brief      handle the IAP_ERASE request
    \param[in]  udev: pointer to usb device instance
    \param[out] none
    \retval     none
*/
static void iap_req_erase(usb_dev *udev)
{
    uint32_t addr = 0U;
    usbd_iap_handler *iap = (usbd_iap_handler *)udev->dev.class_data[USBD_IAP_INTERFACE];

    /* get base address to erase */
    iap->base_address  = iap->report_buf[2];
    iap->base_address |= (uint32_t)iap->report_buf[3] << 8U;
    iap->base_address |= (uint32_t)iap->report_buf[4] << 16U;
    iap->base_address |= (uint32_t)iap->report_buf[5] << 24U;

    /* get file length */
    iap->file_length = iap->report_buf[6];
    iap->file_length |= (uint32_t)iap->report_buf[7] << 8U;
    iap->file_length |= (uint32_t)iap->report_buf[8] << 16U;
    iap->file_length |= (uint32_t)iap->report_buf[9] << 24U;

    /* check if the address is in protected area */
    if(IS_PROTECTED_AREA(iap->base_address)) {
        return;
    }

    addr = iap->base_address;
    iap->dev_status[0] = IAP_DEVICE_ID;

    if(FMC_READY == flash_erase(addr, iap->file_length)) {
        iap->dev_status[1] = OPERATION_SUCCESS;
    } else {
        iap->dev_status[1] = OPERATION_FAIL;
    }

    usbd_ep_send(udev, IAP_IN_EP, iap->dev_status, IAP_IN_PACKET);
}

/*!
    \brief      handle the IAP_READ_OPTION_BYTE request
    \param[in]  udev: pointer to usb device instance
    \param[out] none
    \retval     none
*/
static void iap_req_read_optionbyte(usb_dev *udev)
{
    uint8_t i = 0U;
    uint32_t option_size = 0U, temp = 0U, option_address = 0U;
    usbd_iap_handler *iap = (usbd_iap_handler *)udev->dev.class_data[USBD_IAP_INTERFACE];

    /* read option address address */
    option_address = iap->report_buf[2] + (iap->report_buf[3] << 8U) + (iap->report_buf[4] << 16U) + (iap->report_buf[5] << 24U);

    iap->option_byte[0] = IAP_DEVICE_ID;
    if(OPT_BYTE_ADDR1 == option_address) {
        option_size = OPT_BYTE_SIZE1;
    } else if(OPT_BYTE_ADDR2 == option_address) {
        option_size = OPT_BYTE_SIZE2;
    } else if(EFUSE_BYTE_ADDR == option_address) {
        option_size = EFUSE_BYTE_SIZE;
    }

    /* read option address content */
    for(i = 0U; i < (option_size / 4U); i++) {
        temp =  *(uint32_t *)option_address;
        iap->option_byte[4 * i + 5] = temp >> 24U;
        iap->option_byte[4 * i + 4] = temp >> 16U;
        iap->option_byte[4 * i + 3] = temp >> 8U;
        iap->option_byte[4 * i + 2] = temp;
        option_address = option_address + 4U;
    }
    iap->option_byte[1] = OPERATION_SUCCESS;

    iap_report_send(udev, iap->option_byte, IAP_IN_PACKET);
}

/*!
    \brief      handle the IAP_LEAVE request
    \param[in]  udev: pointer to usb device instance
    \param[out] none
    \retval     none
*/
static void iap_req_leave(usb_dev *udev)
{
    usbd_iap_handler *iap = (usbd_iap_handler *)udev->dev.class_data[USBD_IAP_INTERFACE];

    /* get base address to jump */
    iap->base_address  = iap->report_buf[2];
    iap->base_address |= (uint32_t)iap->report_buf[3] << 8U;
    iap->base_address |= (uint32_t)iap->report_buf[4] << 16U;
    iap->base_address |= (uint32_t)iap->report_buf[5] << 24U;

    iap->dev_status[0] = IAP_DEVICE_ID;
    iap->dev_status[1] = LEAVE_FINISH;

    usbd_ep_send(udev, IAP_IN_EP, iap->dev_status, IAP_IN_PACKET);
    usbd_disconnect(udev);

    /* reset register */
    register_reset();
    /* jump to target */
    jump_to_execute(iap->base_address);
}

/*!
    \brief      handle the IAP_GETBIN_ADDRESS request
    \param[in]  udev: pointer to usb device instance
    \param[out] none
    \retval     none
*/
static void iap_address_send(usb_dev *udev)
{
    usbd_iap_handler *iap = (usbd_iap_handler *)udev->dev.class_data[USBD_IAP_INTERFACE];

    iap->bin_addr[0] = IAP_DEVICE_ID;
    /* get app boundary address */
    iap->bin_addr[1] = (uint8_t)(APP_LOADED_ADDR);
    iap->bin_addr[2] = (uint8_t)(APP_LOADED_ADDR >> 8U);
    iap->bin_addr[3] = (uint8_t)(APP_LOADED_ADDR >> 16U);
    iap->bin_addr[4] = (uint8_t)(APP_LOADED_ADDR >> 24U);

    iap_report_send(udev, iap->bin_addr, IAP_IN_PACKET);
}

/*!
    \brief      handle the IAP_UPLOAD request
    \param[in]  udev: pointer to usb device instance
    \param[out] none
    \retval     none
*/
static void iap_req_upload(usb_dev *udev)
{
    uint16_t packet_valid_length = 0U, i = 0U;
    uint32_t bin_flash_addr = APP_LOADED_ADDR;
    usbd_iap_handler *iap = (usbd_iap_handler *)udev->dev.class_data[USBD_IAP_INTERFACE];

    iap->bin_addr[0] = IAP_DEVICE_ID;
    /* get target flash address */
    bin_flash_addr  = iap->report_buf[2];
    bin_flash_addr |= (uint32_t)iap->report_buf[3] << 8U;
    bin_flash_addr |= (uint32_t)iap->report_buf[4] << 16U;
    bin_flash_addr |= (uint32_t)iap->report_buf[5] << 24U;
    /* get current packet valid length */
    packet_valid_length = iap->report_buf[6];
    packet_valid_length |= iap->report_buf[7] << 8U;
    /* get target flash address content */
    for(i = 0; i < packet_valid_length; i++) {
        iap->bin_addr[i + 1] = REG8(bin_flash_addr + i);
    }

    iap_report_send(udev, iap->bin_addr, IAP_IN_PACKET);
}

/*!
    \brief      handle the IAP_CHECK_RDP request
    \param[in]  udev: pointer to usb device instance
    \param[out] none
    \retval     none
*/
static void iap_check_rdp(usb_dev *udev)
{
    uint8_t mode = 0U;
    usbd_iap_handler *iap = (usbd_iap_handler *)udev->dev.class_data[USBD_IAP_INTERFACE];

    /* check whether the SPC bit of FMC module is normal state */
    if(0xAAU != (uint8_t)(REG16(OPT_BYTE_ADDR1) >> 8U)) {
        mode = IS_RDP_MODE;
    } else {
        mode = IS_NORMAL_MODE;
    }

    iap->bin_addr[0] = IAP_DEVICE_ID;
    iap->bin_addr[1] = mode;

    iap_report_send(udev, iap->bin_addr, IAP_IN_PACKET);
}
