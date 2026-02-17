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
 * @file usbd_msc_core.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "usbd_msc_mem.h"
#include "usbd_msc_core.h"
#include "usbd_msc_bot.h"
#include "usbd_req.h"


uint8_t  USBD_MSC_Init (void  *pdev, uint8_t cfgidx);

uint8_t  USBD_MSC_DeInit (void  *pdev, uint8_t cfgidx);

uint8_t  USBD_MSC_Setup (void  *pdev, USB_SETUP_REQ *req);

uint8_t  USBD_MSC_DataIn (void  *pdev, uint8_t epnum);

uint8_t  USBD_MSC_DataOut (void  *pdev, uint8_t epnum);

uint8_t  *USBD_MSC_GetCfgDesc (uint8_t speed, uint16_t *length);

uint8_t  *USBD_MSC_GetOtherCfgDesc (uint8_t speed, uint16_t *length);


uint8_t USBD_MSC_CfgDesc[USB_MSC_CONFIG_DESC_SIZ];


USBD_Class_cb_TypeDef  USBD_MSC_cb = 
{
    USBD_MSC_Init,
    USBD_MSC_DeInit,
    USBD_MSC_Setup,
    NULL, /*EP0_TxSent*/
    NULL, /*EP0_RxReady*/
    USBD_MSC_DataIn,
    USBD_MSC_DataOut,
    NULL, /*SOF */ 
    NULL,
    NULL,
    USBD_MSC_GetCfgDesc,
    USBD_MSC_GetOtherCfgDesc,
};

#ifdef USB_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_INTERNAL_DMA_ENABLED */
/* USB Mass storage device Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
__ALIGN_BEGIN uint8_t USBD_MSC_CfgDesc[USB_MSC_CONFIG_DESC_SIZ] __ALIGN_END =
{
    0x09,   /* bLength: Configuation Descriptor size */
    USB_DESC_TYPE_CONFIGURATION,   /* bDescriptorType: Configuration */
    USB_MSC_CONFIG_DESC_SIZ,
    0x00,
    0x01,   /* bNumInterfaces: 1 interface */
    0x01,   /* bConfigurationValue: */
    0x04,   /* iConfiguration: */
    0xC0,   /* bmAttributes: */
    0x32,   /* MaxPower 100 mA */

    /********************  Mass Storage interface ********************/
    0x09,   /* bLength: Interface Descriptor size */
    0x04,   /* bDescriptorType: */
    0x00,   /* bInterfaceNumber: Number of Interface */
    0x00,   /* bAlternateSetting: Alternate setting */
    0x02,   /* bNumEndpoints*/
    0x08,   /* bInterfaceClass: MSC Class */
    0x06,   /* bInterfaceSubClass : SCSI transparent*/
    0x50,   /* nInterfaceProtocol */
    0x05,   /* iInterface: */
    /********************  Mass Storage Endpoints ********************/
    0x07,   /*Endpoint descriptor length = 7*/
    0x05,   /*Endpoint descriptor type */
    MSC_IN_EP,   /*Endpoint address (IN, address 1) */
    0x02,   /*Bulk endpoint type */
    LOBYTE(MSC_MAX_PACKET),
    HIBYTE(MSC_MAX_PACKET),
    0x00,   /*Polling interval in milliseconds */

    0x07,   /*Endpoint descriptor length = 7 */
    0x05,   /*Endpoint descriptor type */
    MSC_OUT_EP,   /*Endpoint address (OUT, address 1) */
    0x02,   /*Bulk endpoint type */
    LOBYTE(MSC_MAX_PACKET),
    HIBYTE(MSC_MAX_PACKET),
    0x00    /*Polling interval in milliseconds*/
};

 #ifdef USB_INTERNAL_DMA_ENABLED
   #if defined ( __ICCARM__ ) /*!< IAR Compiler */
     #pragma data_alignment=4   
   #endif
 #endif /* USB_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN uint8_t USBD_MSC_OtherCfgDesc[USB_MSC_CONFIG_DESC_SIZ] __ALIGN_END =
{
    0x09,   /* bLength: Configuation Descriptor size */
    USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION,   
    USB_MSC_CONFIG_DESC_SIZ,

    0x00,
    0x01,   /* bNumInterfaces: 1 interface */
    0x01,   /* bConfigurationValue: */
    0x04,   /* iConfiguration: */
    0xC0,   /* bmAttributes: */
    0x32,   /* MaxPower 100 mA */

    /********************  Mass Storage interface ********************/
    0x09,   /* bLength: Interface Descriptor size */
    0x04,   /* bDescriptorType: */
    0x00,   /* bInterfaceNumber: Number of Interface */
    0x00,   /* bAlternateSetting: Alternate setting */
    0x02,   /* bNumEndpoints*/
    0x08,   /* bInterfaceClass: MSC Class */
    0x06,   /* bInterfaceSubClass : SCSI transparent command set*/
    0x50,   /* nInterfaceProtocol */
    0x05,          /* iInterface: */
    /********************  Mass Storage Endpoints ********************/
    0x07,   /*Endpoint descriptor length = 7*/
    0x05,   /*Endpoint descriptor type */
    MSC_IN_EP,   /*Endpoint address (IN, address 1) */
    0x02,   /*Bulk endpoint type */
    0x40,
    0x00,
    0x00,   /*Polling interval in milliseconds */

    0x07,   /*Endpoint descriptor length = 7 */
    0x05,   /*Endpoint descriptor type */
    MSC_OUT_EP,   /*Endpoint address (OUT, address 1) */
    0x02,   /*Bulk endpoint type */
    0x40,
    0x00,
    0x00     /*Polling interval in milliseconds*/
};

#ifdef USB_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN static uint8_t  USBD_MSC_MaxLun  __ALIGN_END = 0;

#ifdef USB_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN static uint8_t  USBD_MSC_AltSet  __ALIGN_END = 0;


/**
*\*\name   USBD_MSC_Init.
*\*\fun    Initialize  the mass storage configuration.
*\*\param  pdev : USB device
*\*\param  cfgidx: configuration index
*\*\return status
**/
uint8_t  USBD_MSC_Init (void  *pdev, uint8_t cfgidx)
{
    USBD_MSC_DeInit(pdev , cfgidx );

    /* Open EP IN */
    USBDEV_EP_Open(pdev, MSC_IN_EP, MSC_EPIN_SIZE, USB_EP_BULK);

    /* Open EP OUT */
    USBDEV_EP_Open(pdev, MSC_OUT_EP, MSC_EPOUT_SIZE, USB_EP_BULK);

    /* Init the BOT  layer */
    MSC_BOT_Init(pdev); 

    return USBD_OK;
}

/**
*\*\name   USBD_MSC_DeInit.
*\*\fun    DeInitilaize  the mass storage configuration.
*\*\param  pdev : USB device
*\*\param  cfgidx: configuration index
*\*\return status
**/
uint8_t  USBD_MSC_DeInit (void  *pdev, uint8_t cfgidx)
{
  /* Close MSC EPs */
  USBDEV_EP_Close (pdev , MSC_IN_EP);
  USBDEV_EP_Close (pdev , MSC_OUT_EP);
  
  /* Un Init the BOT layer */
  MSC_BOT_DeInit(pdev);
  return USBD_OK;
}

/**
*\*\name   USBD_MSC_Setup.
*\*\fun    Handle the MSC specific requests.
*\*\param  pdev : USB device
*\*\param  req: USB request
*\*\return status
**/
uint8_t  USBD_MSC_Setup (void  *pdev, USB_SETUP_REQ *req)
{
    switch (req->bmRequest & USB_REQ_TYPE_MASK)
    {

        /* Class request */
        case USB_REQ_TYPE_CLASS :
            switch (req->bRequest)
            {
                case BOT_GET_MAX_LUN :
                    if((req->wValue  == 0) && (req->wLength == 1) && ((req->bmRequest & 0x80) == 0x80))
                    {
                        USBD_MSC_MaxLun = USBD_STORAGE_fops->GetMaxLun();
                        if(USBD_MSC_MaxLun > 0)
                        {
                            USBD_CtrlSendData (pdev, &USBD_MSC_MaxLun, 1);
                        }
                        else
                        {
                            USBD_CtrlError(pdev , req);
                            return USBD_FAIL; 
                        }
                    }
                    else
                    {
                        USBD_CtrlError(pdev , req);
                        return USBD_FAIL; 
                    }
                    break;

                case BOT_RESET :
                    if((req->wValue  == 0) && (req->wLength == 0) && ((req->bmRequest & 0x80) != 0x80))
                    {
                        MSC_BOT_Reset(pdev);
                    }
                    else
                    {
                        USBD_CtrlError(pdev , req);
                        return USBD_FAIL; 
                    }
                    break;

                default:
                    USBD_CtrlError(pdev , req);
                    return USBD_FAIL; 
            }
            break;
            
        /* Interface & Endpoint request */
        case USB_REQ_TYPE_STANDARD:
            switch (req->bRequest)
            {
                case USB_REQ_GET_INTERFACE :
                    USBD_CtrlSendData (pdev, &USBD_MSC_AltSet, 1);
                    break;

                case USB_REQ_SET_INTERFACE :
                    USBD_MSC_AltSet = (uint8_t)(req->wValue);
                    break;

                case USB_REQ_CLEAR_FEATURE:  

                    /* Flush the FIFO and Clear the stall status */    
                    USBDEV_EP_Flush(pdev, (uint8_t)req->wIndex);

                    /* Re-activate the EP */      
                    USBDEV_EP_Close (pdev , (uint8_t)req->wIndex);
                    if((((uint8_t)req->wIndex) & 0x80) == 0x80)
                    {
                        USBDEV_EP_Open(pdev, ((uint8_t)req->wIndex), MSC_EPIN_SIZE, USB_EP_BULK);
                    }
                    else
                    {
                        USBDEV_EP_Open(pdev, ((uint8_t)req->wIndex), MSC_EPOUT_SIZE, USB_EP_BULK);
                    }
                    /* Handle BOT error */
                    MSC_BOT_CplClrFeature(pdev, (uint8_t)req->wIndex);
                    break;

                }  
                break;

        default:
            break;
    }
    return USBD_OK;
}

/**
*\*\name   USBD_MSC_DataIn.
*\*\fun    Handle data IN Stage.
*\*\param  pdev : USB device
*\*\param  epnum: endpoint index
*\*\return status
**/
uint8_t  USBD_MSC_DataIn (void  *pdev, uint8_t epnum)
{
    MSC_BOT_DataIn(pdev , epnum);
    return USBD_OK;
}

/**
*\*\name   USBD_MSC_DataOut.
*\*\fun    Handle data OUT Stage.
*\*\param  pdev : USB device
*\*\param  epnum: endpoint index
*\*\return status
**/
uint8_t  USBD_MSC_DataOut (void  *pdev, uint8_t epnum)
{
    MSC_BOT_DataOut(pdev , epnum);
    return USBD_OK;
}

/**
*\*\name   USBD_MSC_GetCfgDesc.
*\*\fun    return configuration descriptor.
*\*\param  speed: current device speed
*\*\param  length: pointer data length
*\*\return pointer to descriptor buffer
**/
uint8_t  *USBD_MSC_GetCfgDesc (uint8_t speed, uint16_t *length)
{
    *length = sizeof (USBD_MSC_CfgDesc);
    return USBD_MSC_CfgDesc;
}

/**
*\*\name   USBD_MSC_GetOtherCfgDesc.
*\*\fun    return configuration descriptor.
*\*\param  speed: current device speed
*\*\param  length: pointer data length
*\*\return pointer to descriptor buffer
**/
uint8_t  *USBD_MSC_GetOtherCfgDesc (uint8_t speed, uint16_t *length)
{
    *length = sizeof (USBD_MSC_OtherCfgDesc);
    return USBD_MSC_OtherCfgDesc;
}
