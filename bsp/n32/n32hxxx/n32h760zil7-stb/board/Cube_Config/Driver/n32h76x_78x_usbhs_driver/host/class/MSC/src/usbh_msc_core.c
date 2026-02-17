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
 * @file usbh_msc_core.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
/* Includes ------------------------------------------------------------------*/

#include "usbh_msc_core.h"
#include "usbh_msc_scsi.h"
#include "usbh_msc_bot.h"
#include "usbh_core.h"
#include "log.h"


#define USBH_MSC_ERROR_RETRY_LIMIT 10

#ifdef USB_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN MSC_Machine_TypeDef         MSC_Machine __ALIGN_END ;

#ifdef USB_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN USB_Setup_TypeDef           MSC_Setup __ALIGN_END ;
uint8_t MSCErrorCount = 0;

static USBH_Status USBH_MSC_InterfaceInit(USB_CORE_MODULE *pdev , void *phost);

static void USBH_MSC_InterfaceDeInit(USB_CORE_MODULE *pdev , void *phost);

static USBH_Status USBH_MSC_Handle(USB_CORE_MODULE *pdev , void *phost);

static USBH_Status USBH_MSC_ClassRequest(USB_CORE_MODULE *pdev , void *phost);

static USBH_Status USBH_MSC_GETMaxLUN(USB_CORE_MODULE *pdev, USBH_HOST *phost);

USBH_Class_cb_TypeDef  USBH_MSC_cb = 
{
    USBH_MSC_InterfaceInit,
    USBH_MSC_InterfaceDeInit,
    USBH_MSC_ClassRequest,
    USBH_MSC_Handle,
};

void USBH_MSC_ErrorHandle(uint8_t status);

/**
*\*\name    USBH_MSC_InterfaceInit.
*\*\fun     Interface initialization for MSC class.
*\*\param   pdev: selected device.
*\*\param   phost: Selected device property.
*\*\return  Status of class request handled.
*\*\
**/
static USBH_Status USBH_MSC_InterfaceInit (USB_CORE_MODULE *pdev, void *phost)
{
    USBH_HOST *pphost = phost;

    if((pphost->device_prop.Itf_Desc[0].bInterfaceClass == MSC_CLASS) && \
     (pphost->device_prop.Itf_Desc[0].bInterfaceProtocol == MSC_PROTOCOL))
    {
        if(pphost->device_prop.Ep_Desc[0][0].bEndpointAddress & 0x80)
        {
            MSC_Machine.MSBulkInEp = (pphost->device_prop.Ep_Desc[0][0].bEndpointAddress);
            MSC_Machine.MSBulkInEpSize  = pphost->device_prop.Ep_Desc[0][0].wMaxPacketSize;
        }
        else
        {
            MSC_Machine.MSBulkOutEp = (pphost->device_prop.Ep_Desc[0][0].bEndpointAddress);
            MSC_Machine.MSBulkOutEpSize  = pphost->device_prop.Ep_Desc[0] [0].wMaxPacketSize;      
        }

        if(pphost->device_prop.Ep_Desc[0][1].bEndpointAddress & 0x80)
        {
            MSC_Machine.MSBulkInEp = (pphost->device_prop.Ep_Desc[0][1].bEndpointAddress);
            MSC_Machine.MSBulkInEpSize  = pphost->device_prop.Ep_Desc[0][1].wMaxPacketSize;      
        }
        else
        {
            MSC_Machine.MSBulkOutEp = (pphost->device_prop.Ep_Desc[0][1].bEndpointAddress);
            MSC_Machine.MSBulkOutEpSize  = pphost->device_prop.Ep_Desc[0][1].wMaxPacketSize;      
        }

        MSC_Machine.hc_num_out = USBH_Alloc_Channel(pdev, MSC_Machine.MSBulkOutEp);
        MSC_Machine.hc_num_in = USBH_Alloc_Channel(pdev, MSC_Machine.MSBulkInEp);  

        /* Open the new channels */
        USBH_Open_Channel  (pdev,
                            MSC_Machine.hc_num_out,
                            pphost->device_prop.address,
                            pphost->device_prop.speed,
                            EP_TYPE_BULK,
                            MSC_Machine.MSBulkOutEpSize);  

        USBH_Open_Channel  (pdev,
                            MSC_Machine.hc_num_in,
                            pphost->device_prop.address,
                            pphost->device_prop.speed,
                            EP_TYPE_BULK,
                            MSC_Machine.MSBulkInEpSize);    
    }

    else
    {
        if (pphost->device_prop.Itf_Desc[0].bInterfaceClass == USB_HUB)
        {
            printf("Hub is not supported.\n");
        }
        else if (pphost->device_prop.Itf_Desc[0].bInterfaceClass == USB_CDCC)
        {
            printf("Communications and CDC Control device is not supported.\n");
        }
        else if (pphost->device_prop.Itf_Desc[0].bInterfaceClass == USB_HID)
        {
            printf("HID device is not supported.\n");
        }
        else if (pphost->device_prop.Itf_Desc[0].bInterfaceClass == USB_PRINTER)
        {
            printf("Printer device is not supported.\n");
        }
        else if (pphost->device_prop.Itf_Desc[0].bInterfaceClass == USB_SMARTCARD)
        {
            printf("Smart Card device is not supported.\n");
        }
        else if (pphost->device_prop.Itf_Desc[0].bInterfaceClass == USB_VIDEO)
        {
            printf("Video device  is not supported.\n");
        }
        else if (pphost->device_prop.Itf_Desc[0].bInterfaceClass == USB_AVD)
        {
            printf("Audio/Video Devices is not supported.\n");
        }
        else
        {
            printf ("The attached device is not supported. \n");
        }

        pphost->usr_cb->DeviceNotSupported();
    }

    return USBH_OK ;
 
}



/**
*\*\name    USBH_MSC_InterfaceDeInit.
*\*\fun     De-Initialize interface by freeing host channels allocated to interface.
*\*\param   pdev: selected device.
*\*\param   phost: Selected device property.
*\*\return  none.
*\*\
**/
void USBH_MSC_InterfaceDeInit ( USB_CORE_MODULE *pdev, void *phost)
{
    if ( MSC_Machine.hc_num_out)
    {
        USB_HCH_Halt(pdev, MSC_Machine.hc_num_out);
        USBH_Free_Channel  (pdev, MSC_Machine.hc_num_out);
        MSC_Machine.hc_num_out = 0;     /* Reset the Channel as Free */
    }

    if ( MSC_Machine.hc_num_in)
    {
        USB_HCH_Halt(pdev, MSC_Machine.hc_num_in);
        USBH_Free_Channel  (pdev, MSC_Machine.hc_num_in);
        MSC_Machine.hc_num_in = 0;     /* Reset the Channel as Free */
    } 
}


/**
*\*\name    USBH_MSC_ClassRequest.
*\*\fun     This function will only initialize the MSC state machine.
*\*\param   pdev: selected device.
*\*\param   phost: Selected device property.
*\*\return  Status of class request handled.
*\*\
**/
static USBH_Status USBH_MSC_ClassRequest(USB_CORE_MODULE *pdev , void *phost)
{
    USBH_Status status = USBH_OK ;
    USBH_MSC_BOTXferParam.MSCState = USBH_MSC_BOT_INIT_STATE;

    return status; 
}

/**
*\*\name    USBH_MSC_Handle.
*\*\fun     MSC state machine handler.
*\*\param   pdev: selected device.
*\*\param   phost: Selected device property.
*\*\return  status.
*\*\
**/
static USBH_Status USBH_MSC_Handle(USB_CORE_MODULE *pdev , void *phost)
{
    USBH_HOST *pphost = phost;

    USBH_Status status = USBH_BUSY;
    uint8_t mscStatus = USBH_MSC_BUSY;
    uint8_t appliStatus = 0;


    static uint8_t maxLunExceed = FALSE;

    if(HOST_IsDeviceConnected(pdev))
    {   
        switch(USBH_MSC_BOTXferParam.MSCState)
        {
            case USBH_MSC_BOT_INIT_STATE:
                USBH_MSC_Init(pdev);
                USBH_MSC_BOTXferParam.MSCState = USBH_MSC_GET_MAX_LUN;  
                break;
            case USBH_MSC_GET_MAX_LUN:
                /* Issue GetMaxLUN request */
                status = USBH_MSC_GETMaxLUN(pdev, phost);
              
                if(status == USBH_OK )
                {
                    MSC_Machine.maxLun = *(MSC_Machine.buff) ;
                    
                    /* If device has more that one logical unit then it is not supported */
                    if((MSC_Machine.maxLun > 0) && (maxLunExceed == FALSE))
                    {
                        maxLunExceed = TRUE;
                        pphost->usr_cb->DeviceNotSupported();
                      
                        break;
                    }
                
                    USBH_MSC_BOTXferParam.MSCState = USBH_MSC_TEST_UNIT_READY;
                }
                if(status == USBH_NOT_SUPPORTED )
                {
                    /* If the Command has failed, then we need to move to Next State, after
                    STALL condition is cleared by Control-Transfer */
                    USBH_MSC_BOTXferParam.MSCStateBkp = USBH_MSC_TEST_UNIT_READY;        
                    /* a Clear Feature should be issued here */
                    USBH_MSC_BOTXferParam.MSCState = USBH_MSC_CTRL_ERROR_STATE;
                }
                break;
              
            case USBH_MSC_CTRL_ERROR_STATE:
                /* Issue Clearfeature request */
                status = USBH_ClrFeature(pdev,
                                         phost,
                                         0x00,
                                         pphost->Control.hch_num_out);
                if(status == USBH_OK )
                {
                    /* If GetMaxLun Request not support, assume Single LUN configuration */
                    MSC_Machine.maxLun = 0;  
                
                    USBH_MSC_BOTXferParam.MSCState = USBH_MSC_BOTXferParam.MSCStateBkp;     
                }
                break;  
              
            case USBH_MSC_TEST_UNIT_READY:
                /* Issue SCSI command TestUnitReady */ 
                mscStatus = USBH_MSC_TestUnitReady(pdev);

                if(mscStatus == USBH_MSC_OK )
                {
                    USBH_MSC_BOTXferParam.MSCState = USBH_MSC_READ_CAPACITY10;
                    MSCErrorCount = 0;
                    status = USBH_OK;
                }
                else
                {
                    USBH_MSC_ErrorHandle(mscStatus);
                } 
                break;
              
            case USBH_MSC_READ_CAPACITY10:
                /* Issue READ_CAPACITY10 SCSI command */
                mscStatus = USBH_MSC_ReadCapacity10(pdev);
                if(mscStatus == USBH_MSC_OK )
                {
                    USBH_MSC_BOTXferParam.MSCState = USBH_MSC_MODE_SENSE6;
                    MSCErrorCount = 0;
                    status = USBH_OK;
                }
                else
                {
                    USBH_MSC_ErrorHandle(mscStatus);
                }
                break;

            case USBH_MSC_MODE_SENSE6:
                /* Issue ModeSense6 SCSI command for detecting if device is write-protected */
                mscStatus = USBH_MSC_ModeSense6(pdev);
                if(mscStatus == USBH_MSC_OK )
                {
                    USBH_MSC_BOTXferParam.MSCState = USBH_MSC_DEFAULT_APPLI_STATE;
                    MSCErrorCount = 0;
                    status = USBH_OK;
                }
                else
                {
                    USBH_MSC_ErrorHandle(mscStatus);
                }
                break;
               
            case USBH_MSC_BOT_USB_TRANSFERS:
                /* Process the BOT state machine */
                USBH_MSC_HandleBOTXfer(pdev,phost);
                break;

            case USBH_MSC_DEFAULT_APPLI_STATE:
                /* Process Application callback for MSC */
                appliStatus = pphost->usr_cb->UserApplication();
                if(appliStatus == 0)
                {
                    USBH_MSC_BOTXferParam.MSCState = USBH_MSC_DEFAULT_APPLI_STATE;
                }
                else if (appliStatus == 1) 
                {
                    /* De-init requested from application layer */
                    status =  USBH_APPLY_DEINIT;
                }
                break;
              
            case USBH_MSC_UNRECOVERED_STATE:
                status = USBH_UNRECOVERED_ERROR;
                break;

            case USBH_MSC_REQUEST_SENSE:
                /* Issue RequestSense SCSI command for retrieving error code */
                mscStatus = USBH_MSC_RequestSense(pdev);
                if(mscStatus == USBH_MSC_OK )
                {
                    USBH_MSC_BOTXferParam.MSCState = USBH_MSC_BOTXferParam.MSCStateBkp;
                    status = USBH_OK;
                }
                else
                {
                    USBH_MSC_ErrorHandle(mscStatus);
                }  
                break;
            default:
                break; 
        }
    }
    return status;
}



/**
*\*\name    USBH_MSC_GETMaxLUN.
*\*\fun     This request is used to reset the mass storage device and its associated interface. This class-specific request shall ready the device for the next CBW from the host.
*\*\param   pdev: selected device.
*\*\param   phost: Selected device property.
*\*\return  status: USB ctrl xfer status.
*\*\
**/
static USBH_Status USBH_MSC_GETMaxLUN(USB_CORE_MODULE *pdev , USBH_HOST *phost)
{
    phost->Control.setup.b.bmRequestType = USB_D2H | USB_REQ_TYPE_CLASS | USB_REQ_RECIPIENT_INTERFACE;

    phost->Control.setup.b.bRequest = USB_REQ_GET_MAX_LUN;
    phost->Control.setup.b.wValue.w = 0;
    phost->Control.setup.b.wIndex.w = 0;
    phost->Control.setup.b.wLength.w = 1;           

    return USBH_CtrlReq(pdev, phost, MSC_Machine.buff , 1 ); 
}

/**
*\*\name    USBH_MSC_ErrorHandle.
*\*\fun     The function is for handling errors occurring during the MSC state machine.
*\*\param   status: selected device.
*\*\return  none: USB ctrl xfer status.
*\*\
**/
void USBH_MSC_ErrorHandle(uint8_t status)
{  
    if(status == USBH_MSC_FAIL)
    { 
        MSCErrorCount++;
        if(MSCErrorCount < USBH_MSC_ERROR_RETRY_LIMIT)
        { /* Try MSC level error recovery, Issue the request Sense to get 
            Drive error reason  */
            USBH_MSC_BOTXferParam.MSCState = USBH_MSC_REQUEST_SENSE;
            USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
        }
        else
        {
            /* Error trials exceeded the limit, go to unrecovered state */
            USBH_MSC_BOTXferParam.MSCState = USBH_MSC_UNRECOVERED_STATE;
        }
    } 
    else if(status == USBH_MSC_PHASE_ERROR)
    {
        /* Phase error, Go to Unrecovered state */
        USBH_MSC_BOTXferParam.MSCState = USBH_MSC_UNRECOVERED_STATE;
    }
    else if(status == USBH_MSC_BUSY)
    {
        /*No change in state*/
    }
}
