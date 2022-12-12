/**
 *******************************************************************************
 * @file  usb_dev_cdc_class.c
 * @brief The CDC VCP core functions.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_dev_cdc_class.h"
#include "usb_dev_driver.h"
#include "usb_dev_ctrleptrans.h"
#include "usb_dev_stdreq.h"
#include "usb_dev_desc.h"
#include "cdc_data_process.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_SINGLE_CDC USB Device CDC
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
uint8_t *usb_dev_cdc_getcfgdesc(uint16_t *length);
void process_asynchdata_uart2usb(void *pdev);

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
usb_dev_class_func  class_cdc_cbk = {
    &usb_dev_cdc_init,
    &usb_dev_cdc_deinit,
    &usb_dev_cdc_setup,
    NULL,
    &usb_dev_cdc_ctrlep_rxready,
    &usb_dev_cdc_getcfgdesc,
    &usb_dev_cdc_sof,
    &usb_dev_cdc_datain,
    &usb_dev_cdc_dataout,
    NULL,
    NULL,
};

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
__USB_ALIGN_BEGIN static uint32_t  alternate_setting  = 0UL;
__USB_ALIGN_BEGIN static uint8_t usb_rx_buffer[MAX_CDC_PACKET_SIZE];
uint8_t uart_rx_buffer[APP_RX_DATA_SIZE];  /* used as a buffer for receiving data from uart port */
__USB_ALIGN_BEGIN static uint8_t CmdBuff[CDC_CMD_PACKET_SIZE];
uint32_t APP_Rx_ptr_in  = 0UL;
uint32_t APP_Rx_ptr_out = 0UL;
static uint32_t APP_Rx_length  = 0UL;
static uint8_t  USB_Tx_State   = 0U;
static uint32_t cdcCmd  = 0xFFUL;
static uint32_t cdcLen  = 0UL;
static uint32_t LastPackLen = 0UL;

__USB_ALIGN_BEGIN static uint8_t usb_dev_cdc_cfgdesc[USB_CDC_CONFIG_DESC_SIZ]  = {
    0x09,
    USB_CFG_DESCRIPTOR_TYPE,
    USB_CDC_CONFIG_DESC_SIZ,
    0x00,
    0x02,
    0x01,
    0x00,
    0xC0,
    0x32,

    0x08,
    0x0B,
    0x00,
    0x02,
    0x02,
    0x02,
    0x01,
    0x04,

    0x09,
    USB_INTERFACE_DESCRIPTOR_TYPE,
    0x00,
    0x00,
    0x01,
    0x02,
    0x02,
    0x01,
    0x00,

    0x05,
    0x24,
    0x00,
    0x10,
    0x01,

    0x05,
    0x24,
    0x01,
    0x00,
    0x01,

    0x04,
    0x24,
    0x02,
    0x02,

    0x05,
    0x24,
    0x06,
    0x00,
    0x01,

    0x07,
    USB_ENDPOINT_DESCRIPTOR_TYPE,
    CDC_CMD_EP,
    0x03,
    LOBYTE(CDC_CMD_PACKET_SIZE),
    HIBYTE(CDC_CMD_PACKET_SIZE),
    0xFF,

    0x09,
    USB_INTERFACE_DESCRIPTOR_TYPE,
    0x01,
    0x00,
    0x02,
    0x0A,
    0x00,
    0x00,
    0x00,

    0x07,
    USB_ENDPOINT_DESCRIPTOR_TYPE,
    CDC_OUT_EP,
    0x02,
    LOBYTE(MAX_CDC_PACKET_SIZE),
    HIBYTE(MAX_CDC_PACKET_SIZE),
    0x00,

    0x07,
    USB_ENDPOINT_DESCRIPTOR_TYPE,
    CDC_IN_EP,
    0x02,
    LOBYTE(MAX_CDC_PACKET_SIZE),
    HIBYTE(MAX_CDC_PACKET_SIZE),
    0x00
} ;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Initilaize the CDC application
 * @param  [in] pdev        Device instance
 * @retval None
 */
void usb_dev_cdc_init(void *pdev)
{
    usb_opendevep(pdev, CDC_IN_EP, MAX_CDC_IN_PACKET_SIZE, EP_TYPE_BULK);
    usb_opendevep(pdev, CDC_OUT_EP, MAX_CDC_OUT_PACKET_SIZE, EP_TYPE_BULK);
    usb_opendevep(pdev, CDC_CMD_EP, CDC_CMD_PACKET_SIZE, EP_TYPE_INTR);
    vcp_init();
    usb_readytorx(pdev, CDC_OUT_EP, (uint8_t *)(usb_rx_buffer), MAX_CDC_OUT_PACKET_SIZE);
}

/**
 * @brief  Deinitialize the CDC application
 * @param  [in] pdev        Device instance
 * @retval None
 */
void usb_dev_cdc_deinit(void *pdev)
{
    usb_shutdevep(pdev, CDC_IN_EP);
    usb_shutdevep(pdev, CDC_OUT_EP);
    usb_shutdevep(pdev, CDC_CMD_EP);
    vcp_deinit();
}

/**
 * @brief  Handle the setup requests
 * @param  [in] pdev        Device instance
 * @param  [in] req         usb requests
 * @retval status
 */
uint8_t usb_dev_cdc_setup(void *pdev, USB_SETUP_REQ *req)
{
    uint16_t len = USB_CDC_DESC_SIZ;
    uint8_t  *pbuf = usb_dev_cdc_cfgdesc + 9;
    uint8_t  u8Res = USB_DEV_OK;

    switch (req->bmRequest & USB_REQ_TYPE_MASK) {
        case USB_REQ_TYPE_CLASS :
            if (req->wLength != 0U) {
                if ((req->bmRequest & 0x80U) != 0U) {
                    vcp_ctrlpare(req->bRequest, CmdBuff, req->wLength);
                    usb_ctrldatatx(pdev, CmdBuff, req->wLength);
                } else {
                    cdcCmd = req->bRequest;
                    cdcLen = req->wLength;
                    usb_ctrldatarx(pdev, CmdBuff, req->wLength);
                }
            } else {
                vcp_ctrlpare(req->bRequest, NULL, 0UL);
            }
            break;
        case USB_REQ_TYPE_STANDARD:
            switch (req->bRequest) {
                case USB_REQ_GET_DESCRIPTOR:
                    if ((req->wValue >> 8) == CDC_DESCRIPTOR_TYPE) {
                        pbuf = usb_dev_cdc_cfgdesc + 9U + (9U * USBD_ITF_MAX_NUM);
                        len  = LL_MIN(USB_CDC_DESC_SIZ, req->wLength);
                    }
                    usb_ctrldatatx(pdev, pbuf, len);
                    break;

                case USB_REQ_GET_INTERFACE :
                    usb_ctrldatatx(pdev, (uint8_t *)&alternate_setting, 1U);
                    break;

                case USB_REQ_SET_INTERFACE :
                    if ((uint8_t)(req->wValue) < USBD_ITF_MAX_NUM) {
                        alternate_setting = (uint8_t)(req->wValue);
                    } else {
                        usb_ctrlerr(pdev);
                    }
                    break;
                default:
                    break;
            }
            break;

        default:
            usb_ctrlerr(pdev);
            u8Res = USB_DEV_FAIL;
            break;
    }
    return u8Res;
}

/**
 * @brief  Data received on control endpoint
 * @param  [in] pdev        device device instance
 * @retval None
 */
void usb_dev_cdc_ctrlep_rxready(void *pdev)
{
    if (cdcCmd != NO_CMD) {
        vcp_ctrlpare(cdcCmd, CmdBuff, cdcLen);
        cdcCmd = NO_CMD;
    }
}

/**
 * @brief  Data sent on non-control IN endpoint
 * @param  [in] pdev        Device instance
 * @param  [in] epnum       endpoint index
 * @retval None
 */
void usb_dev_cdc_datain(void *pdev, uint8_t epnum)
{
    uint16_t tx2usb_ptr;
    uint16_t tx2usb_length;

    if (USB_Tx_State == 1U) {
        if (APP_Rx_length == 0U) {
            if (LastPackLen == MAX_CDC_IN_PACKET_SIZE) {
                usb_deveptx(pdev, CDC_IN_EP, NULL, 0UL);
                LastPackLen = 0UL;
            } else {
                USB_Tx_State = 0U;
            }
        } else {
            if (APP_Rx_length >= MAX_CDC_IN_PACKET_SIZE) {
                tx2usb_ptr      = (uint16_t)APP_Rx_ptr_out;
                tx2usb_length   = (uint16_t)MAX_CDC_IN_PACKET_SIZE - 1U;
                APP_Rx_ptr_out += MAX_CDC_IN_PACKET_SIZE - 1U;
                APP_Rx_length  -= MAX_CDC_IN_PACKET_SIZE - 1U;
            } else {
                tx2usb_ptr      = (uint16_t)APP_Rx_ptr_out;
                tx2usb_length   = (uint16_t)APP_Rx_length;
                APP_Rx_ptr_out += APP_Rx_length;
                APP_Rx_length   = 0U;
            }
            usb_deveptx(pdev,
                        CDC_IN_EP,
                        (uint8_t *)&uart_rx_buffer[tx2usb_ptr],
                        (uint32_t)tx2usb_length);
            LastPackLen = (uint32_t)tx2usb_length;
        }
    }
}

/**
 * @brief  Data received on non-control Out endpoint
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint index
 * @retval None
 */
void usb_dev_cdc_dataout(void *pdev, uint8_t epnum)
{
    uint16_t usb_rx_cnt;

    usb_rx_cnt = (uint16_t)((usb_core_instance *)pdev)->dev.out_ep[epnum].xfer_count;
    vcp_rxdata(usb_rx_buffer, usb_rx_cnt);
    usb_readytorx(pdev, CDC_OUT_EP, (uint8_t *)(usb_rx_buffer), MAX_CDC_OUT_PACKET_SIZE);
}

/**
 * @brief  Start Of Frame event management
 * @param  [in] pdev        Device instance
 * @retval status
 */
uint8_t usb_dev_cdc_sof(void *pdev)
{
    static uint32_t FrameCount = 0UL;

    if (FrameCount++ == CDC_IN_FRAME_INTERVAL) {
        FrameCount = 0UL;
        process_asynchdata_uart2usb(pdev);
    }
    return USB_DEV_OK;
}

/**
 * @brief  process the data received from usart and send through USB to host
 * @param  [in] pdev        device instance
 * @retval None
 */
void process_asynchdata_uart2usb(void *pdev)
{
    uint16_t tx2usb_ptr;     /* the location of the pointer in buffer that would be sent to USB */
    uint16_t tx2usb_length;  /* the length in bytes that would be sent to USB */

    if (USB_Tx_State != 1U) {
        if (APP_Rx_ptr_out == APP_RX_DATA_SIZE) {
            APP_Rx_ptr_out = 0UL;
        }
        if (APP_Rx_ptr_out == APP_Rx_ptr_in) {
            USB_Tx_State = 0U;
        } else {
            if (APP_Rx_ptr_out > APP_Rx_ptr_in) {
                APP_Rx_length = APP_RX_DATA_SIZE - APP_Rx_ptr_out;
            } else {
                APP_Rx_length = APP_Rx_ptr_in - APP_Rx_ptr_out;
            }

            if (APP_Rx_length >= MAX_CDC_IN_PACKET_SIZE) {
                tx2usb_ptr = (uint16_t)APP_Rx_ptr_out;
                tx2usb_length = MAX_CDC_IN_PACKET_SIZE - 1U;

                APP_Rx_ptr_out += MAX_CDC_IN_PACKET_SIZE - 1UL;
                APP_Rx_length -= MAX_CDC_IN_PACKET_SIZE - 1UL;
            } else {
                tx2usb_ptr = (uint16_t)APP_Rx_ptr_out;
                tx2usb_length = (uint16_t)APP_Rx_length;

                APP_Rx_ptr_out += APP_Rx_length;
                APP_Rx_length = 0UL;
            }
            USB_Tx_State = 1U;

            usb_deveptx(pdev,
                        CDC_IN_EP,
                        (uint8_t *)&uart_rx_buffer[tx2usb_ptr],
                        (uint32_t)tx2usb_length);
            LastPackLen = (uint32_t)tx2usb_length;
        }
    }
}

/**
 * @brief  get the configuration descriptor
 * @param  [in] length          length of configuration descriptor in bytes
 * @retval the pointer to configuration descriptor buffer
 */
uint8_t *usb_dev_cdc_getcfgdesc(uint16_t *length)
{
    *length = (uint16_t)sizeof(usb_dev_cdc_cfgdesc);
    return usb_dev_cdc_cfgdesc;
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
