/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file usbd_keyboard_core.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "usbd_keyboard_core.h"
#include "usbd_desc.h"
#include "usbd_req.h"
#include "n32h76x_78x_gpio.h"
#include "usbhs_bsp.h"

static uint8_t USBD_Keyboard_Init(void *pdev, uint8_t cfgidx);
static uint8_t USBD_Keyboard_Deinit(void *pdev, uint8_t cfgidx);
static uint8_t USBD_Keyboard_Setup(void *pdev, USB_SETUP_REQ *req);
static uint8_t *USBD_Keyboard_Getcfgdesc(uint8_t speed,uint16_t *length);
static uint8_t USBD_Keyboard_Datain(void *pdev, uint8_t epnum);
static uint8_t USBD_Keyboard_Dataout(void *pdev, uint8_t epnum);

USBD_Class_cb_TypeDef  USBD_HID_Keyboard_cb=
{
    USBD_Keyboard_Init,
    USBD_Keyboard_Deinit,
    USBD_Keyboard_Setup,
    NULL, /*EP0_TxSent*/ 
    NULL,
    USBD_Keyboard_Datain,
    USBD_Keyboard_Dataout,
    NULL,
    NULL,
    NULL,
    USBD_Keyboard_Getcfgdesc,
    USBD_Keyboard_Getcfgdesc,
};

__ALIGN_BEGIN static uint32_t  USBD_Keyboard_AltSet  __ALIGN_END = 0u;
__ALIGN_BEGIN static uint32_t  USBD_Keyboard_Protocol  __ALIGN_END = 0u;
__ALIGN_BEGIN static uint32_t  USBD_Keyboard_IdleState __ALIGN_END = 0u;

/* USB HID device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_Keyboard_CfgDesc[KEYBOARD_CFGDESC_SIZE] __ALIGN_END =
{
    0x09,                             /* bLength: Configuration Descriptor size */
    USB_CONFIGURATION_DESCRIPTOR_TYPE,/* bDescriptorType: Configuration */
    KEYBOARD_CFGDESC_SIZE,               /* wTotalLength: Bytes returned */
    0x00,
    0x01,                             /*bNumInterfaces: 1 interface*/
    0x01,                             /*bConfigurationValue: Configuration value*/
    0x00,                             /*iConfiguration: Index of string descriptor describing the configuration*/
    0x80,                             /*bmAttributes: bus powered and Support Remote Wake-up */
    0x32,                             /*MaxPower 100 mA: this current is used for detecting Vbus*/
    /************** Descriptor of Joystick Mouse interface ****************/
    /* 09 */
    0x09,                             /*bLength: Interface Descriptor size*/
    USB_INTERFACE_DESCRIPTOR_TYPE,    /*bDescriptorType: Interface descriptor type*/
    0x00,                             /*bInterfaceNumber: Number of Interface*/
    0x00,                             /*bAlternateSetting: Alternate setting*/
    0x02,                             /*bNumEndpoints*/
    0x03,                             /*bInterfaceClass: HID*/
    0x01,                             /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
    0x01,                             /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0x00,                             /*iInterface: Index of string descriptor*/
    /******************** Descriptor of Joystick Mouse HID ********************/
    /* 18 */
    0x09,                             /*bLength: HID Descriptor size*/
    KEYBOARD_DESCRIPTOR_TYPE,         /*bDescriptorType: HID*/
    0x10,                             /*bcdHID: HID Class Spec release number*/
    0x01,
    0x21,                             /*bCountryCode: Hardware target country*/
    0x01,                             /*bNumDescriptors: Number of HID class descriptors to follow*/
    0x22,                             /*bDescriptorType*/
    KEYBOARD_REPORT_DESC_SIZE,           /*wItemLength: Total length of Report descriptor*/
    0x00,
    /******************** Descriptor of Mouse endpoint ********************/
    /* 27 */
    0x07,                             /*bLength: Endpoint Descriptor size*/
    USB_ENDPOINT_DESCRIPTOR_TYPE,     /*bDescriptorType:*/
    HID_IN_EP,                        /*bEndpointAddress: Endpoint Address (IN)*/
    0x03,                             /*bmAttributes: Interrupt endpoint*/
    0x08,                             /*wMaxPacketSize: 4 Byte max */
    0x00,
    0x0A,                             /*bInterval: Polling Interval (10 ms)*/
    /* 34 */
    0x07,                             /*bLength: Endpoint Descriptor size*/
    USB_ENDPOINT_DESCRIPTOR_TYPE,     /*bDescriptorType:*/
    HID_OUT_EP,                       /*bEndpointAddress: Endpoint Address (IN)*/
    0x03,                             /*bmAttributes: Interrupt endpoint*/
    HID_OUT_PACKET,                   /*wMaxPacketSize: 4 Byte max */
    0x00,
    0x0A,                             /*bInterval: Polling Interval (10 ms)*/
    /* 41 */
} ;

__ALIGN_BEGIN static uint8_t HID_KEYBOARD_ReportDesc[KEYBOARD_REPORT_DESC_SIZE] __ALIGN_END =
{
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x05, 0x07,                    // USAGE_PAGE (Keyboard)
    0x19, 0x00,                    // USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x00,                    // USAGE_MAXIMUM (Reserved (no event indicated))
    0x15, 0x00,                    // LOGICAL_MINIMUM (0)
    0x25, 0x01,                    // LOGICAL_MAXIMUM (1)
    0x95, 0x01,                    // REPORT_COUNT (1)
    0x75, 0x08,                    // REPORT_SIZE (8)
    0x81, 0x02,                    // INPUT (Data,Var,Abs)
    0x95, 0x01,                    // REPORT_COUNT (1)
    0x75, 0x08,                    // REPORT_SIZE (8)
    0x81, 0x03,                    // INPUT (Cnst,Var,Abs)
    0x95, 0x06,                    // REPORT_COUNT (6)
    0x75, 0x08,                    // REPORT_SIZE (8)
    0x15, 0x00,                    // LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              // LOGICAL_MAXIMUM (255)
    0x05, 0x07,                    // USAGE_PAGE (Keyboard)
    0x19, 0x00,                    // USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0xe7,                    // USAGE_MAXIMUM (Keyboard Right GUI)
    0x81, 0x00,                    // INPUT (Data,Ary,Abs)
    0x15, 0x01,                    // LOGICAL_MINIMUM (1)
    0x95, 0x05,                    // REPORT_COUNT (5)
    0x75, 0x01,                    // REPORT_SIZE (1)
    0x05, 0x08,                    // USAGE_PAGE (LEDs)
    0x19, 0x01,                    // USAGE_MINIMUM (Num Lock)
    0x29, 0x05,                    // USAGE_MAXIMUM (Kana)
    0x91, 0x02,                    // OUTPUT (Data,Var,Abs)
    0x95, 0x01,                    // REPORT_COUNT (1)
    0x75, 0x03,                    // REPORT_SIZE (3)
    0x91, 0x03,                    // OUTPUT (Cnst,Var,Abs)
    0xc0                           // END_COLLECTION
};

__IO uint8_t Report_buf[64];

/**
*\*\name    USBD_Keyboard_Init.
*\*\fun     Initialize the interface of KEYBOARD HID.
*\*\param   pdev: device instance.
*\*\param   cfgidx: Configuration index
*\*\return  USBD_OK.
*\*\
**/
static uint8_t USBD_Keyboard_Init(void *pdev, uint8_t cfgidx)
{
    USBDEV_EP_Open(pdev, HID_IN_EP, 8, USB_EP_INT);
    USBDEV_EP_Open(pdev, HID_OUT_EP, HID_OUT_PACKET, USB_EP_INT);
    USBDEV_EP_PrepareRx(pdev, HID_OUT_EP, (uint8_t *)Report_buf, 64);
    USBDEV_SetEPStatus(pdev, HID_OUT_EP, USB_EP_RX_VALID);
    
    return USBD_OK;
}

/**
*\*\name    USBD_Keyboard_Deinit.
*\*\fun     DeInitialize the interface of KEYBOARD HID.
*\*\param   pdev: device instance.
*\*\param   cfgidx: Configuration index
*\*\return  USBD_OK.
*\*\
**/
static uint8_t USBD_Keyboard_Deinit(void *pdev, uint8_t cfgidx)
{
    USBDEV_EP_Close(pdev, HID_IN_EP);
    USBDEV_EP_Close(pdev, HID_OUT_EP);
    
    return USBD_OK;
}

/**
*\*\name    USBD_Keyboard_Setup.
*\*\fun     Handle the KEYBOARD HID SETUP request.
*\*\param   pdev: device instance.
*\*\param   req: usb requests
*\*\return  status.
*\*\
**/
static uint8_t USBD_Keyboard_Setup(void *pdev, USB_SETUP_REQ *req)
{
    uint16_t   len = 0u;
    uint8_t  *pbuf = NULL;
    uint8_t  status = USBD_OK;

    switch (req->bmRequest & USB_REQ_TYPE_MASK)
    {
        case USB_REQ_TYPE_CLASS :
            switch (req->bRequest)
            {
                case KEYBOARD_REQ_SET_PROTOCOL:
                    USBD_Keyboard_Protocol = (uint8_t)(req->wValue);
                    break;
                case KEYBOARD_REQ_GET_PROTOCOL:
                    USBD_CtrlSendData(pdev, (uint8_t *)&USBD_Keyboard_Protocol, 1u);
                    break;
                case KEYBOARD_REQ_SET_IDLE:
                    USBD_Keyboard_IdleState = (uint8_t)(req->wValue >> 8u);
                    break;
                case KEYBOARD_REQ_GET_IDLE:
                    USBD_CtrlSendData(pdev, (uint8_t *)&USBD_Keyboard_IdleState, 1u);
                    break;
                default:
                    USBD_CtrlError(pdev, req);
                    status = USBD_FAIL;
                    break;
            }
            break;
        case USB_REQ_TYPE_STANDARD:
            switch (req->bRequest)
            {
                case USB_REQ_GET_DESCRIPTOR:
                    if((req->wValue >> 8u) == (uint16_t)KEYBOARD_REPORT_DESC)
                    {
                        len  = (uint16_t)MIN(KEYBOARD_REPORT_DESC_SIZE , req->wLength);
                        pbuf = HID_KEYBOARD_ReportDesc;
                    }
                    else if((req->wValue >> 8u) == (uint16_t)KEYBOARD_DESCRIPTOR_TYPE)
                    {
                        pbuf = USBD_Keyboard_CfgDesc + 0x12;
                        len  = (uint16_t)MIN(KEYBOARD_DESC_SIZE , req->wLength);
                    }
                    else
                    {
                        //
                    }
                    USBD_CtrlSendData(pdev, pbuf, len);
                    break;
                case USB_REQ_GET_INTERFACE :
                    USBD_CtrlSendData(pdev, (uint8_t *)&USBD_Keyboard_AltSet, 1u);
                    break;
                case USB_REQ_SET_INTERFACE :
                    USBD_Keyboard_AltSet = (uint8_t)(req->wValue);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return status;
}

/**
*\*\name    USBD_Keyboard_Getcfgdesc.
*\*\fun     return configuration descriptor.
*\*\param   speed : current device speed.
*\*\param   length : pointer data length.
*\*\return  pointer to descriptor buffer.
*\*\
**/
static uint8_t *USBD_Keyboard_Getcfgdesc(uint8_t speed, uint16_t *length)
{
    *length = (uint16_t)sizeof (USBD_Keyboard_CfgDesc);
    return USBD_Keyboard_CfgDesc;
}

/**
*\*\name    USBD_Keyboard_Datain.
*\*\fun     handle data IN Stage.
*\*\param   pdev: device instance.
*\*\param   epnum: endpoint index.
*\*\return  USBD_OK.
*\*\
**/
static uint8_t USBD_Keyboard_Datain(void *pdev, uint8_t epnum)
{
    USBDEV_EP_Flush(pdev, HID_IN_EP);
    
    return USBD_OK;
}

/**
*\*\name    USBD_Keyboard_Dataout.
*\*\fun     handle the OUT data Stage.
*\*\param   pdev: device instance.
*\*\param   epnum: endpoint index.
*\*\return  USBD_OK.
*\*\
**/
static uint8_t USBD_Keyboard_Dataout(void *pdev, uint8_t epnum)
{
    if (epnum == HID_OUT_EP) 
    {
        if(Report_buf[0] & 0x02)
        {
            LED_On(LED1_PORT, LED1_PIN);
        }
        else
        {
            LED_Off(LED1_PORT, LED1_PIN);
        }
        if(Report_buf[0] & 0x01)
        {
            LED_On(LED2_PORT, LED2_PIN);
        }
        else
        {
            LED_Off(LED2_PORT, LED2_PIN);
        }
    }
    
    USBDEV_EP_PrepareRx(pdev, HID_OUT_EP, (uint8_t *)Report_buf, 64);
    USBDEV_SetEPStatus(pdev, HID_OUT_EP, USB_EP_RX_VALID);
    
    return USBD_OK;
}
