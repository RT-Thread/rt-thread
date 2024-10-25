/*!
    \file    usb_iap_core.c
    \brief   IAP driver

    \version 2023-12-31, V1.4.0, firmware for GD32E50x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

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

#include "usb_iap_libusb.h"
#include "flash_operation.h"

#define USBD_VID                     0x28E9U
#define USBD_PID                     0x1007U

uint8_t report_buf[IAP_OUT_PACKET + 1U];
uint8_t option_byte[IAP_IN_PACKET] = {0U};

/* state machine variables */
uint8_t device_status[IAP_IN_PACKET];
uint8_t bin_address[IAP_IN_PACKET];

uint8_t flag = 0U;

static uint16_t transfer_times = 0U;
static uint32_t file_length = 0U;
static uint32_t base_address = APP_LOADED_ADDR;

/* Note:it should use the C99 standard when compiling the below codes */
/* USB standard device descriptor */
const usb_desc_dev iap_dev_desc =
{
    .header =
     {
         .bLength          = USB_DEV_DESC_LEN,
         .bDescriptorType  = USB_DESCTYPE_DEV
     },
    .bcdUSB                = 0x0200U,
    .bDeviceClass          = 0xFFU,
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

const usb_iap_libusb_desc_config_set iap_config_desc =
{
    .config =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_config),
             .bDescriptorType = USB_DESCTYPE_CONFIG
         },
        .wTotalLength         = sizeof(usb_iap_libusb_desc_config_set),
        .bNumInterfaces       = 0x01U,
        .bConfigurationValue  = 0x01U,
        .iConfiguration       = 0x00U,
        .bmAttributes         = 0x80U,
        .bMaxPower            = 0x32U
    },

    .itf =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_itf),
             .bDescriptorType = USB_DESCTYPE_ITF
         },
        .bInterfaceNumber     = 0x00U,
        .bAlternateSetting    = 0x00U,
        .bNumEndpoints        = 0x02U,
        .bInterfaceClass      = 0x00U,
        .bInterfaceSubClass   = 0x00U,
        .bInterfaceProtocol   = 0x00U,
        .iInterface           = 0x00U
    },

    .epin =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_ep),
             .bDescriptorType = USB_DESCTYPE_EP
         },
        .bEndpointAddress     = IAP_IN_EP,
        .bmAttributes         = USB_EP_ATTR_BULK,
        .wMaxPacketSize       = IAP_IN_PACKET,
        .bInterval            = 0x00U
    },

    .epout =
    {
        .header =
         {
             .bLength         = sizeof(usb_desc_ep),
             .bDescriptorType = USB_DESCTYPE_EP
         },
        .bEndpointAddress     = IAP_OUT_EP,
        .bmAttributes         = USB_EP_ATTR_BULK,
        .wMaxPacketSize       = IAP_OUT_PACKET,
        .bInterval            = 0x00U
    }
};

/* USB language ID Descriptor */
const usb_desc_LANGID usbd_language_id_desc =
{
    .header =
     {
         .bLength         = sizeof(usb_desc_LANGID),
         .bDescriptorType = USB_DESCTYPE_STR
     },
    .wLANGID              = ENG_LANGID
};

/* USB serial string */
uint8_t usbd_serial_string[USB_SERIAL_STRING_SIZE] =
{
    USB_SERIAL_STRING_SIZE,    /* bLength */
    USB_DESCTYPE_STR,          /* bDescriptorType */
};

void *const usbd_iap_strings[] =
{
    [STR_IDX_LANGID] = (uint8_t *)&usbd_language_id_desc,
    [STR_IDX_MFC] = USBD_STRING_DESC("GigaDevice"),
    [STR_IDX_PRODUCT] = USBD_STRING_DESC("GD32 USB Libusb IAP in FS Mode"),
    [STR_IDX_SERIAL] = usbd_serial_string
};

/* local function prototypes ('static') */
static uint8_t iap_init (usb_dev *udev, uint8_t config_index);
static uint8_t iap_deinit (usb_dev *udev, uint8_t config_index);
static uint8_t iap_req_handler (usb_dev *udev, usb_req *req);
static uint8_t iap_data_out (usb_dev *udev, uint8_t ep_num);

usb_class_core iap_libusb_class = {
    .init            = iap_init,
    .deinit          = iap_deinit,
    .req_proc        = iap_req_handler,
    .data_out        = iap_data_out
};

/* IAP requests management functions */
static void iap_req_erase     (usb_dev *udev);
static void iap_req_dnload    (usb_dev *udev);
static void iap_req_optionbyte(usb_dev *udev, uint8_t option_num);
static void iap_req_leave     (usb_dev *udev);
static void iap_address_send  (usb_dev *udev);

/*!
    \brief      send IAP report
    \param[in]  udev: pointer to USB device instance
    \param[in]  report: pointer to HID report
    \param[in]  len: data length
    \param[out] none
    \retval     USB device operation status
*/
uint8_t iap_data_send (usb_dev *udev, uint8_t *report, uint16_t len)
{
    usbd_ep_send (udev, IAP_IN_EP, report, len);

    return USBD_OK;
}

/*!
    \brief      initialize the IAP device
    \param[in]  udev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t iap_init (usb_dev *udev, uint8_t config_index)
{
    /* initialize TX endpoint */
    usbd_ep_setup(udev, &(iap_config_desc.epin));

    /* initialize RX endpoint */
    usbd_ep_setup(udev, &(iap_config_desc.epout));

    /* unlock the internal flash */
    fmc_unlock();

    /* prepare receive Data */
    usbd_ep_recev(udev, IAP_OUT_EP, report_buf, IAP_OUT_PACKET);

    return USBD_OK;
}

/*!
    \brief      de-initialize the IAP device
    \param[in]  udev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t iap_deinit (usb_dev *udev, uint8_t config_index)
{
    /* deinitialize IAP endpoints */
    usbd_ep_clear (udev, IAP_IN_EP);
    usbd_ep_clear (udev, IAP_OUT_EP);

    /* lock the internal flash */
    fmc_lock();

    return USBD_OK;
}

/*!
    \brief      handle the IAP class-specific requests
    \param[in]  udev: pointer to USB device instance
    \param[in]  req: device class-specific request
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t iap_req_handler (usb_dev *udev, usb_req *req)
{
    return USBD_OK;
}

/*!
    \brief      handle data out stage
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: endpoint identifier
    \param[out] none
    \retval     none
*/
static uint8_t iap_data_out (usb_dev *udev ,uint8_t ep_num)
{
    if ((IAP_OUT_EP & 0x7FU) == ep_num)
    {
        if (0x01U == report_buf[0])
        {
            switch(report_buf[1])
            {
            case IAP_DNLOAD:
                iap_req_dnload(udev);
                break;

            case IAP_ERASE:
                iap_req_erase(udev);
                break;

            case IAP_OPTION_BYTE1:
                iap_req_optionbyte(udev, 0x01U);
                break;

            case IAP_LEAVE:
                iap_req_leave(udev);
                break;

            case IAP_GETBIN_ADDRESS:
                iap_address_send(udev);
                break;

            case IAP_OPTION_BYTE2:
                iap_req_optionbyte(udev, 0x02U);
                break;

            default:
                break;
            }
        }

        usbd_ep_recev(udev, IAP_OUT_EP, report_buf, IAP_OUT_PACKET);
    }

    return USBD_OK;
}

/*!
    \brief      handle the IAP_DNLOAD request
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static void iap_req_dnload(usb_dev *udev)
{
    if (0U != transfer_times)
    {
        if (1U == transfer_times)
        {
            iap_data_write(&report_buf[2], base_address, file_length % TRANSFER_SIZE);

            device_status[0] = 0x02U;
            device_status[1] = 0x02U;

            iap_data_send (udev, device_status, 2U);
        } else {
            iap_data_write(&report_buf[2], base_address, TRANSFER_SIZE);

            base_address += TRANSFER_SIZE;
        }

        transfer_times--;
    }
}

/*!
    \brief      handle the IAP_ERASE request
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static void iap_req_erase(usb_dev *udev)
{
    uint32_t addr = 0U;

    /* get base address to erase */
    base_address  = report_buf[2];
    base_address |= report_buf[3] << 8U;
    base_address |= report_buf[4] << 16U;
    base_address |= report_buf[5] << 24U;

    /* get file length */
    file_length = report_buf[7];
    file_length |= report_buf[8] << 8U;
    file_length |= report_buf[9] << 16U;
    file_length |= report_buf[10] << 24U;

    if (0U == (file_length % TRANSFER_SIZE))
    {
        transfer_times = file_length / TRANSFER_SIZE;
    } else {
        transfer_times = file_length / TRANSFER_SIZE + 1U;
    }

    /* check if the address is in protected area */
    if (IS_PROTECTED_AREA(base_address))
    {
        return;
    }

    addr = base_address;

    /* unlock the flash program erase controller */
    fmc_unlock();

    flash_erase(addr, file_length, report_buf);

    fmc_lock();

    device_status[0] = 0x02U;
    device_status[1] = 0x01U;

    usbd_ep_send(udev, IAP_IN_EP, device_status, IAP_IN_PACKET);
}

/*!
    \brief      handle the IAP_OPTION_BYTE request
    \param[in]  udev: pointer to USB device instance
    \param[in]  option_num: number of option byte
    \param[out] none
    \retval     none
*/
static void iap_req_optionbyte(usb_dev *udev, uint8_t option_num)
{
    uint8_t i = 0U;
    uint32_t address = 0U;

    option_byte[0]= 0x02U;

    if (option_num == 0x01U)
    {
        address = OPT_BYTE_ADDR1;
#ifdef OPT_BYTE_ADDR2
    } else if (option_num == 0x02U)
    {
        address = OPT_BYTE_ADDR2;
#endif
    } else {
        return;
    }

    for (i = 1U; i < 17U; i++)
    {
        option_byte[i] = *(uint8_t *)address;
        address++;
    }

    iap_data_send (udev, option_byte, 17U);
}

/*!
    \brief      handle the IAP_LEAVE request
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static void iap_req_leave(usb_dev *udev)
{
    /* lock the internal flash */
    fmc_lock();

    /* generate system reset to allow jumping to the user code */
    NVIC_SystemReset();
}

/*!
    \brief      handle the IAP_SEND_ADDRESS request
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static void iap_address_send(usb_dev *udev)
{
    bin_address[0] = 0x02U;

    bin_address[1] = (uint8_t)(APP_LOADED_ADDR);
    bin_address[2] = (uint8_t)(APP_LOADED_ADDR >> 8U);
    bin_address[3] = (uint8_t)(APP_LOADED_ADDR >> 16U);
    bin_address[4] = (uint8_t)(APP_LOADED_ADDR >> 24U);

    iap_data_send (udev, bin_address, 5U);
}
