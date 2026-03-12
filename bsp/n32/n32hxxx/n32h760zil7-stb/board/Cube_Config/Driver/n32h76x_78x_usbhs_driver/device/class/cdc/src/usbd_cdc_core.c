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
 * @file usbd_cdc_core.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "usbd_cdc_core.h"
#include "usbd_desc.h"
#include "usbd_req.h"
#include "usbhs_bsp.h"

#define USB_CDC_IDLE         0
#define USB_CDC_BUSY         1
#define USB_CDC_ZLP          2

/* CDC Device library callbacks */
uint8_t  USBD_CDC_Init        (void  *pdev, uint8_t cfgidx);
uint8_t  USBD_CDC_DeInit      (void  *pdev, uint8_t cfgidx);
uint8_t  USBD_CDC_Setup       (void  *pdev, USB_SETUP_REQ *req);
uint8_t  USBD_CDC_EP0_RxReady (void *pdev);
uint8_t  USBD_CDC_DataIn      (void *pdev, uint8_t epnum);
uint8_t  USBD_CDC_DataOut     (void *pdev, uint8_t epnum);
uint8_t  USBD_CDC_SOF         (void *pdev);

/* CDC specific management functions */
static void Handle_USBAsynchXfer  (void *pdev);
static uint8_t *USBD_CDC_GetCfgDesc (uint8_t speed, uint16_t *length);
static uint8_t *USBD_CDC_GetOtherCfgDesc (uint8_t speed, uint16_t *length);


extern CDC_IF_Prop_TypeDef  APP_FOPS;
extern uint8_t USBD_DeviceDesc   [USB_SIZ_DEVICE_DESC];

#ifdef USB_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN uint8_t USBD_CDC_CfgDesc  [USB_CDC_CONFIG_DESC_SIZ] __ALIGN_END ;

#ifdef USB_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN uint8_t USBD_CDC_OtherCfgDesc  [USB_CDC_CONFIG_DESC_SIZ] __ALIGN_END ;

#ifdef USB_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN static __IO uint32_t  USBD_CDC_AltSet  __ALIGN_END = 0;

#ifdef USB_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN uint8_t USB_Rx_Buffer   [CDC_DATA_MAX_PACKET_SIZE] __ALIGN_END ;

#ifdef USB_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN uint8_t APP_Rx_Buffer   [APP_RX_DATA_SIZE] __ALIGN_END ; 


#ifdef USB_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN uint8_t CmdBuff[CDC_CMD_PACKET_SIZE] __ALIGN_END ;

uint32_t APP_Rx_ptr_in  = 0;
uint32_t APP_Rx_ptr_out = 0;
uint32_t APP_Rx_length  = 0;

uint8_t  USB_Tx_State = USB_CDC_IDLE;

static uint32_t cdcCmd = 0xFF;
static uint32_t cdcLen = 0;

/* CDC interface class callbacks structure */
USBD_Class_cb_TypeDef  USBD_CDC_cb = 
{
    USBD_CDC_Init,
    USBD_CDC_DeInit,
    USBD_CDC_Setup,
    NULL,                 /* EP0_TxSent, */
    USBD_CDC_EP0_RxReady,
    USBD_CDC_DataIn,
    USBD_CDC_DataOut,
    USBD_CDC_SOF,
    NULL,
    NULL,     
    USBD_CDC_GetCfgDesc,
    USBD_CDC_GetOtherCfgDesc, /* use same cobfig as per FS */
};

#ifdef USB_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_INTERNAL_DMA_ENABLED */
/* USB CDC device Configuration Descriptor */
__ALIGN_BEGIN uint8_t USBD_CDC_CfgDesc[USB_CDC_CONFIG_DESC_SIZ]  __ALIGN_END =
{
    /* Configuration Descriptor */
    0x09,                                       /* bLength: Configuration Descriptor size */
    USB_DESC_TYPE_CONFIGURATION,                /* bDescriptorType: Configuration */
    USB_CDC_CONFIG_DESC_SIZ,                    /* wTotalLength */
    0x00,
    0x02,                                       /* bNumInterfaces: 2 interfaces */
    0x01,                                       /* bConfigurationValue: Configuration value */
    0x00,                                       /* iConfiguration: Index of string descriptor */
    0xC0,                                       /* bmAttributes: self powered */
    0x32,                                       /* MaxPower 100 mA */

    /* Interface Descriptor */
    0x09,                                       /* bLength: Interface Descriptor size */
    USB_DESC_TYPE_INTERFACE,                    /* bDescriptorType: Interface */
    /* Interface descriptor type */
    0x00,                                       /* bInterfaceNumber: Number of Interface */
    0x00,                                       /* bAlternateSetting: Alternate setting */
    0x01,                                       /* bNumEndpoints: One endpoint used */
    0x02,                                       /* bInterfaceClass: Communication Interface Class */
    0x02,                                       /* bInterfaceSubClass: Abstract Control Model */
    0x01,                                       /* bInterfaceProtocol: Common AT commands */
    0x00,                                       /* iInterface */

    /* Header Functional Descriptor */
    0x05,                                       /* bLength: Endpoint Descriptor size */
    0x24,                                       /* bDescriptorType: CS_INTERFACE */
    0x00,                                       /* bDescriptorSubtype: Header Func Desc */
    0x10,                                       /* bcdCDC: spec release number */
    0x01,

    /* Call Management Functional Descriptor */
    0x05,                                       /* bFunctionLength */
    0x24,                                       /* bDescriptorType: CS_INTERFACE */
    0x01,                                       /* bDescriptorSubtype: Call Management Func Desc */
    0x00,                                       /* bmCapabilities: D0+D1 */
    0x01,                                       /* bDataInterface */

    /* ACM Functional Descriptor */
    0x04,                                       /* bFunctionLength */
    0x24,                                       /* bDescriptorType: CS_INTERFACE */
    0x02,                                       /* bDescriptorSubtype: Abstract Control Management desc */
    0x02,                                       /* bmCapabilities */

    /* Union Functional Descriptor */
    0x05,                                       /* bFunctionLength */
    0x24,                                       /* bDescriptorType: CS_INTERFACE */
    0x06,                                       /* bDescriptorSubtype: Union func desc */
    0x00,                                       /* bMasterInterface: Communication class interface */
    0x01,                                       /* bSlaveInterface0: Data Class Interface */

    /* Endpoint 2 Descriptor */
    0x07,                                       /* bLength: Endpoint Descriptor size */
    USB_DESC_TYPE_ENDPOINT,                     /* bDescriptorType: Endpoint */
    CDC_CMD_EP,                                 /* bEndpointAddress */
    0x03,                                       /* bmAttributes: Interrupt */
    LOBYTE(CDC_CMD_PACKET_SIZE),                /* wMaxPacketSize */
    HIBYTE(CDC_CMD_PACKET_SIZE),
    0x10,                                       /* bInterval */
    /*---------------------------------------------------------------------------*/

    /* Data class interface descriptor */
    0x09,                                       /* bLength: Endpoint Descriptor size */
    USB_DESC_TYPE_INTERFACE,                    /* bDescriptorType: */
    0x01,                                       /* bInterfaceNumber: Number of Interface */
    0x00,                                       /* bAlternateSetting: Alternate setting */
    0x02,                                       /* bNumEndpoints: Two endpoints used */
    0x0A,                                       /* bInterfaceClass: CDC */
    0x00,                                       /* bInterfaceSubClass */
    0x00,                                       /* bInterfaceProtocol */
    0x00,                                       /* iInterface */

    /* Endpoint OUT Descriptor */
    0x07,                                       /* bLength: Endpoint Descriptor size */
    USB_DESC_TYPE_ENDPOINT,                     /* bDescriptorType: Endpoint */
    CDC_OUT_EP,                                 /* bEndpointAddress */
    0x02,                                       /* bmAttributes: Bulk */
    LOBYTE(CDC_DATA_MAX_PACKET_SIZE),           /* wMaxPacketSize: */
    HIBYTE(CDC_DATA_MAX_PACKET_SIZE),
    0x00,                                       /* bInterval */

    /* Endpoint IN Descriptor */
    0x07,                                       /* bLength: Endpoint Descriptor size */
    USB_DESC_TYPE_ENDPOINT,                     /* bDescriptorType: Endpoint */
    CDC_IN_EP,                                  /* bEndpointAddress */
    0x02,                                       /* bmAttributes: Bulk */
    LOBYTE(CDC_DATA_MAX_PACKET_SIZE),        /* wMaxPacketSize: */
    HIBYTE(CDC_DATA_MAX_PACKET_SIZE),
    0x00                                        /* bInterval */
};

#ifdef USB_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_INTERNAL_DMA_ENABLED */ 
__ALIGN_BEGIN uint8_t USBD_CDC_OtherCfgDesc[USB_CDC_CONFIG_DESC_SIZ]  __ALIGN_END =
{ 
    0x09,   /* bLength: Configuration Descriptor size */
    USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION,   
    USB_CDC_CONFIG_DESC_SIZ,
    0x00,
    0x02,   /* bNumInterfaces: 2 interfaces */
    0x01,   /* bConfigurationValue: */
    0x04,   /* iConfiguration: */
    0xC0,   /* bmAttributes: */
    0x32,   /* MaxPower 100 mA */  

    /*Interface Descriptor */
    0x09,   /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE,  /* bDescriptorType: Interface */
    /* Interface descriptor type */
    0x00,   /* bInterfaceNumber: Number of Interface */
    0x00,   /* bAlternateSetting: Alternate setting */
    0x01,   /* bNumEndpoints: One endpoints used */
    0x02,   /* bInterfaceClass: Communication Interface Class */
    0x02,   /* bInterfaceSubClass: Abstract Control Model */
    0x01,   /* bInterfaceProtocol: Common AT commands */
    0x00,   /* iInterface: */

    /*Header Functional Descriptor*/
    0x05,   /* bLength: Endpoint Descriptor size */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x00,   /* bDescriptorSubtype: Header Func Desc */
    0x10,   /* bcdCDC: spec release number */
    0x01,

    /*Call Management Functional Descriptor*/
    0x05,   /* bFunctionLength */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x01,   /* bDescriptorSubtype: Call Management Func Desc */
    0x00,   /* bmCapabilities: D0+D1 */
    0x01,   /* bDataInterface: 1 */

    /*ACM Functional Descriptor*/
    0x04,   /* bFunctionLength */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x02,   /* bDescriptorSubtype: Abstract Control Management desc */
    0x02,   /* bmCapabilities */

    /*Union Functional Descriptor*/
    0x05,   /* bFunctionLength */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x06,   /* bDescriptorSubtype: Union func desc */
    0x00,   /* bMasterInterface: Communication class interface */
    0x01,   /* bSlaveInterface0: Data Class Interface */

    /*Endpoint 2 Descriptor*/
    0x07,                           /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */
    CDC_CMD_EP,                     /* bEndpointAddress */
    0x03,                           /* bmAttributes: Interrupt */
    LOBYTE(CDC_CMD_PACKET_SIZE),    /* wMaxPacketSize: */
    HIBYTE(CDC_CMD_PACKET_SIZE),
    0xFF,                           /* bInterval: */

    /*---------------------------------------------------------------------------*/

    /*Data class interface descriptor*/
    0x09,   /* bLength: Endpoint Descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE,  /* bDescriptorType: */
    0x01,   /* bInterfaceNumber: Number of Interface */
    0x00,   /* bAlternateSetting: Alternate setting */
    0x02,   /* bNumEndpoints: Two endpoints used */
    0x0A,   /* bInterfaceClass: CDC */
    0x00,   /* bInterfaceSubClass: */
    0x00,   /* bInterfaceProtocol: */
    0x00,   /* iInterface: */

    /*Endpoint OUT Descriptor*/
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType: Endpoint */
    CDC_OUT_EP,                        /* bEndpointAddress */
    0x02,                              /* bmAttributes: Bulk */
    0x40,                              /* wMaxPacketSize: */
    0x00,
    0x00,                              /* bInterval: ignore for Bulk transfer */

    /*Endpoint IN Descriptor*/
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,     /* bDescriptorType: Endpoint */
    CDC_IN_EP,                        /* bEndpointAddress */
    0x02,                             /* bmAttributes: Bulk */
    0x40,                             /* wMaxPacketSize: */
    0x00,
    0x00                              /* bInterval */
};

/**
*\*\name    USBD_CDC_Init.
*\*\fun     Initialize the CDC interface.
*\*\param   pdev: device instance.
*\*\param   cfgidx: Configuration index
*\*\return  USBD_OK.
*\*\
**/
uint8_t USBD_CDC_Init (void  *pdev, uint8_t cfgidx)
{
    /* Open EP IN */
    USBDEV_EP_Open(pdev, CDC_IN_EP, CDC_DATA_IN_PACKET_SIZE, USB_EP_BULK);

    /* Open EP OUT */
    USBDEV_EP_Open(pdev, CDC_OUT_EP, CDC_DATA_OUT_PACKET_SIZE, USB_EP_BULK);

    /* Open Command IN EP */
    USBDEV_EP_Open(pdev, CDC_CMD_EP, CDC_CMD_PACKET_SIZE, USB_EP_INT);

    /* Initialize the Interface physical components */
    APP_FOPS.pIf_Init();

    /* Prepare Out endpoint to receive next packet */
    USBDEV_EP_PrepareRx(pdev, CDC_OUT_EP, (uint8_t*)(USB_Rx_Buffer), CDC_DATA_OUT_PACKET_SIZE);
  
    return USBD_OK;
}

/**
*\*\name    USBD_CDC_DeInit.
*\*\fun     DeInitialize the CDC layer.
*\*\param   pdev: device instance.
*\*\param   cfgidx: Configuration index
*\*\return  USBD_OK.
*\*\
**/
uint8_t  USBD_CDC_DeInit (void  *pdev, uint8_t cfgidx)
{
    /* Open EP IN */
    USBDEV_EP_Close(pdev, CDC_IN_EP);

    /* Open EP OUT */
    USBDEV_EP_Close(pdev, CDC_OUT_EP);

    /* Open Command IN EP */
    USBDEV_EP_Close(pdev, CDC_CMD_EP);

    /* Restore default state of the Interface physical components */
    APP_FOPS.pIf_DeInit();

    return USBD_OK;
}

/**
*\*\name    USBD_CDC_Setup
*\*\fun     Handle the CDC specific requests.
*\*\param   pdev: device instance.
*\*\param   req: usb requests
*\*\return  USBD_OK.
**/
uint8_t USBD_CDC_Setup (void  *pdev, USB_SETUP_REQ *req)
{
    switch (req->bmRequest & USB_REQ_TYPE_MASK)
    {
        /* CDC Class Requests -------------------------------*/
        case USB_REQ_TYPE_CLASS :
            /* Check if the request is a data setup packet */
            if (req->wLength)
            {
                /* Check if the request is Device-to-Host */
                if (req->bmRequest & 0x80)
                {
                    /* Get the data to be sent to Host from interface layer */
                    APP_FOPS.pIf_Ctrl(req->bRequest, CmdBuff, req->wLength);
                  
                    /* Send the data to the host */
                    USBD_CtrlSendData(pdev, CmdBuff, req->wLength);
                }
                else /* Host-to-Device request */
                {
                    /* Set the value of the current command to be processed */
                    cdcCmd = req->bRequest;
                    cdcLen = req->wLength;
                  
                    /* Prepare the reception of the buffer over EP0
                    Next step: the received data will be managed in usbd_cdc_EP0_TxSent() 
                    function. */
                    USBD_CtrlPrepareRx (pdev, CmdBuff, req->wLength);
                }
            }
            else /* No Data request */
            {
                /* Transfer the command to the interface layer */
                APP_FOPS.pIf_Ctrl(req->bRequest, NULL, 0);
            }
            break;

        /* Standard Requests -------------------------------*/
        case USB_REQ_TYPE_STANDARD:
            switch (req->bRequest)
            {
                case USB_REQ_GET_DESCRIPTOR: 
                    USBD_CtrlError (pdev, req);
                    return USBD_FAIL;

                case USB_REQ_GET_INTERFACE :
                    USBD_CtrlSendData (pdev, (uint8_t *)&USBD_CDC_AltSet, 1);
                    break;

                case USB_REQ_SET_INTERFACE :
                    if ((uint8_t)(req->wValue) < USBD_ITF_MAX_NUM)
                    {
                        USBD_CDC_AltSet = (uint8_t)(req->wValue);
                    }
                    else
                    {
                        /* Call the error management function (command will be nacked */
                        USBD_CtrlError (pdev, req);
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            USBD_CtrlError (pdev, req);
            return USBD_FAIL;
    }
    return USBD_OK;
}

/**
*\*\name    USBD_CDC_EP0_RxReady
*\*\fun     Data received on control endpoint.
*\*\param   pdev: device instance.
*\*\return  USBD_OK.
**/
uint8_t  USBD_CDC_EP0_RxReady (void  *pdev)
{ 
    if (cdcCmd != NO_CMD)
    {
        /* Process the data */
        APP_FOPS.pIf_Ctrl(cdcCmd, CmdBuff, cdcLen);
        /* Reset the command variable to default value */
        cdcCmd = NO_CMD;
    }

    return USBD_OK;
}


/**
*\*\name    USBD_CDC_DataIn.
*\*\fun     handle data IN Stage.
*\*\param   pdev: device instance.
*\*\param   epnum: endpoint index.
*\*\return  USBD_OK.
*\*\
**/
uint8_t  USBD_CDC_DataIn (void *pdev, uint8_t epnum)
{
    uint16_t USB_Tx_ptr;
    uint16_t USB_Tx_length;

    if (USB_Tx_State == USB_CDC_BUSY)
    {
        if (APP_Rx_length == 0) 
        {
            USB_Tx_State = USB_CDC_IDLE;
        }
        else 
        {
            if (APP_Rx_length > CDC_DATA_IN_PACKET_SIZE)
            {
                USB_Tx_ptr = APP_Rx_ptr_out;
                USB_Tx_length = CDC_DATA_IN_PACKET_SIZE;
            
                APP_Rx_ptr_out += CDC_DATA_IN_PACKET_SIZE;
                APP_Rx_length -= CDC_DATA_IN_PACKET_SIZE;
            }
            else 
            {
                USB_Tx_ptr = APP_Rx_ptr_out;
                USB_Tx_length = APP_Rx_length;
                
                APP_Rx_ptr_out += APP_Rx_length;
                APP_Rx_length = 0;
                if(USB_Tx_length == CDC_DATA_IN_PACKET_SIZE)
                {
                    USB_Tx_State = USB_CDC_ZLP;
                }
            }
            
            /* Prepare the available data buffer to be sent on IN endpoint */
            USBDEV_EP_Tx (pdev, CDC_IN_EP, (uint8_t*)&APP_Rx_Buffer[USB_Tx_ptr], USB_Tx_length);
            return USBD_OK;
        }
    }

    /* Avoid any asynchronous transfer during ZLP */
    if (USB_Tx_State == USB_CDC_ZLP)
    {
        /*Send ZLP to indicate the end of the current transfer */
        USBDEV_EP_Tx (pdev, CDC_IN_EP, NULL, 0);

        USB_Tx_State = USB_CDC_IDLE;
    }
    return USBD_OK;
}

/**
*\*\name    USBD_CDC_DataOut.
*\*\fun     handle data OUT Stage.
*\*\param   pdev: device instance.
*\*\param   epnum: endpoint index.
*\*\return  USBD_OK.
*\*\
**/
uint8_t  USBD_CDC_DataOut (void *pdev, uint8_t epnum)
{      
    uint16_t USB_Rx_Cnt;

    /* Get the received data buffer and update the counter */
    USB_Rx_Cnt = ((USB_CORE_MODULE*)pdev)->dev.out_ep[epnum].xfer_count;

    /* USB data will be immediately processed, this allow next USB traffic being 
    NAKed till the end of the application Xfer */
    APP_FOPS.pIf_DataRx(USB_Rx_Buffer, USB_Rx_Cnt);

    /* Prepare Out endpoint to receive next packet */
    USBDEV_EP_PrepareRx(pdev, CDC_OUT_EP, (uint8_t*)(USB_Rx_Buffer), CDC_DATA_OUT_PACKET_SIZE);

    return USBD_OK;
}

/**
*\*\name    USBD_CDC_SOF.
*\*\fun     Start Of Frame event management.
*\*\param   pdev: device instance.
*\*\return  USBD_OK.
*\*\
**/
uint8_t  USBD_CDC_SOF (void *pdev)
{      
    static uint32_t FrameCount = 0;

    if (FrameCount++ == CDC_IN_FRAME_INTERVAL)
    {
        /* Reset the frame counter */
        FrameCount = 0;

        /* Check the data to be sent through IN pipe */
        Handle_USBAsynchXfer(pdev);
    }

    return USBD_OK;
}

/**
*\*\name    Handle_USBAsynchXfer.
*\*\fun     process the data received from usart and send through USB to host.
*\*\param   pdev: device instance.
*\*\return  USBD_OK.
*\*\
**/
static void Handle_USBAsynchXfer (void *pdev)
{
    uint16_t USB_Tx_ptr;
    uint16_t USB_Tx_length;

    if(USB_Tx_State == USB_CDC_IDLE)
    {
        if (APP_Rx_ptr_out == APP_RX_DATA_SIZE)
        {
            APP_Rx_ptr_out = 0;
        }

        if(APP_Rx_ptr_out == APP_Rx_ptr_in) 
        {
            USB_Tx_State = USB_CDC_IDLE; 
            return;
        }

        if(APP_Rx_ptr_out > APP_Rx_ptr_in) /* rollback */
        { 
            APP_Rx_length = APP_RX_DATA_SIZE - APP_Rx_ptr_out;
        }
        else 
        {
            APP_Rx_length = APP_Rx_ptr_in - APP_Rx_ptr_out;
        }
  
        if (APP_Rx_length > CDC_DATA_IN_PACKET_SIZE)
        {
            USB_Tx_ptr = APP_Rx_ptr_out;
            USB_Tx_length = CDC_DATA_IN_PACKET_SIZE;
          
            APP_Rx_ptr_out += CDC_DATA_IN_PACKET_SIZE;
            APP_Rx_length -= CDC_DATA_IN_PACKET_SIZE;
            USB_Tx_State = USB_CDC_BUSY;
        }
        else
        {
            USB_Tx_ptr = APP_Rx_ptr_out;
            USB_Tx_length = APP_Rx_length;
          
            APP_Rx_ptr_out += APP_Rx_length;
            APP_Rx_length = 0;
            if(USB_Tx_length == CDC_DATA_IN_PACKET_SIZE)
            {
                USB_Tx_State = USB_CDC_ZLP;
            }
            else
            {
                USB_Tx_State = USB_CDC_BUSY;
            }
        }
        USBDEV_EP_Tx (pdev, CDC_IN_EP, (uint8_t*)&APP_Rx_Buffer[USB_Tx_ptr], USB_Tx_length);
    }
}

/**
*\*\name    USBD_CDC_GetCfgDesc.
*\*\fun     Return configuration descriptor.
*\*\param   speed : current device speed
*\*\param   length : pointer data length
*\*\return  pointer to descriptor buffer.
*\*\
**/
static uint8_t *USBD_CDC_GetCfgDesc (uint8_t speed, uint16_t *length)
{
    *length = sizeof (USBD_CDC_CfgDesc);
    return USBD_CDC_CfgDesc;
}

/**
*\*\name    USBD_CDC_GetOtherCfgDesc.
*\*\fun     Return configuration descriptor.
*\*\param   speed : current device speed
*\*\param   length : pointer data length
*\*\return  pointer to descriptor buffer.
*\*\
**/
static uint8_t *USBD_CDC_GetOtherCfgDesc (uint8_t speed, uint16_t *length)
{
  *length = sizeof (USBD_CDC_OtherCfgDesc);
  return USBD_CDC_OtherCfgDesc;
}

