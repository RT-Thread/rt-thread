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
 * @file usbd_audio_core.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "usbd_audio_core.h"
#include "usbd_audio_out_if.h"

/*********************************************
   AUDIO Device library callbacks
 *********************************************/
static uint8_t  USBD_AUDIO_Init       (void  *pdev, uint8_t cfgidx);
static uint8_t  USBD_AUDIO_DeInit     (void  *pdev, uint8_t cfgidx);
static uint8_t  USBD_AUDIO_Setup      (void  *pdev, USB_SETUP_REQ *req);
static uint8_t  USBD_AUDIO_EP0_RxReady(void *pdev);
static uint8_t  USBD_AUDIO_DataIn     (void *pdev, uint8_t epnum);
static uint8_t  USBD_AUDIO_DataOut    (void *pdev, uint8_t epnum);
static uint8_t  USBD_AUDIO_SOF        (void *pdev);
static uint8_t  USBD_AUDIO_OUT_Incplt (void  *pdev);

static void AUDIO_Req_GetCurrent(void *pdev, USB_SETUP_REQ *req);
static void AUDIO_Req_SetCurrent(void *pdev, USB_SETUP_REQ *req);
static uint8_t  *USBD_AUDIO_GetCfgDesc (uint8_t speed, uint16_t *length);

/* Main Buffer for Audio Data Out transfers and its relative pointers */
uint8_t  IsocOutBuff [TOTAL_OUT_BUF_SIZE * 2];
uint8_t* IsocOutWrPtr = IsocOutBuff;
uint8_t* IsocOutRdPtr = IsocOutBuff;

/* Main Buffer for Audio Control Requests transfers and its relative variables */
uint8_t  AudioCtrl[64];
uint8_t  AudioCtrlCmd = 0;
uint32_t AudioCtrlLen = 0;
uint8_t  AudioCtrlUnit = 0;

static uint32_t PlayFlag = 0;

static __IO uint32_t  USBD_AUDIO_AltSet = 0;
static uint8_t USBD_AUDIO_CfgDesc[AUDIO_CONFIG_DESC_SIZE];

/* AUDIO interface class callbacks structure */
USBD_Class_cb_TypeDef  USBD_AUDIO_cb = 
{
    USBD_AUDIO_Init,
    USBD_AUDIO_DeInit,
    USBD_AUDIO_Setup,
    NULL, /* EP0_TxSent */
    USBD_AUDIO_EP0_RxReady,
    USBD_AUDIO_DataIn,
    USBD_AUDIO_DataOut,
    USBD_AUDIO_SOF,
    NULL,
    USBD_AUDIO_OUT_Incplt,
    USBD_AUDIO_GetCfgDesc,
    USBD_AUDIO_GetCfgDesc,
};

/* USB AUDIO device Configuration Descriptor */
static uint8_t USBD_AUDIO_CfgDesc[AUDIO_CONFIG_DESC_SIZE] =
{
    /* Configuration 1 */
    0x09,                                 /* bLength */
    USB_CONFIGURATION_DESCRIPTOR_TYPE,    /* bDescriptorType */
    LOBYTE(AUDIO_CONFIG_DESC_SIZE),       /* wTotalLength  109 bytes*/
    HIBYTE(AUDIO_CONFIG_DESC_SIZE),      
    0x02,                                 /* bNumInterfaces */
    0x01,                                 /* bConfigurationValue */
    0x00,                                 /* iConfiguration */
    0xC0,                                 /* bmAttributes  BUS Powred*/
    0x32,                                 /* bMaxPower = 100 mA*/
    /* 09 byte*/

    /* USB Speaker Standard interface descriptor */
    AUDIO_INTERFACE_DESC_SIZE,            /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,        /* bDescriptorType */
    0x00,                                 /* bInterfaceNumber */
    0x00,                                 /* bAlternateSetting */
    0x00,                                 /* bNumEndpoints */
    USB_DEVICE_CLASS_AUDIO,               /* bInterfaceClass */
    AUDIO_SUBCLASS_AUDIOCONTROL,          /* bInterfaceSubClass */
    AUDIO_PROTOCOL_UNDEFINED,             /* bInterfaceProtocol */
    0x00,                                 /* iInterface */
    /* 09 byte*/

    /* USB Speaker Class-specific AC Interface Descriptor */
    AUDIO_INTERFACE_DESC_SIZE,            /* bLength */
    AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
    AUDIO_CONTROL_HEADER,                 /* bDescriptorSubtype */
    0x00,          /* 1.00 */             /* bcdADC */
    0x01,
    0x27,                                 /* wTotalLength = 39*/
    0x00,
    0x01,                                 /* bInCollection */
    0x01,                                 /* baInterfaceNr */
    /* 09 byte*/

    /* USB Speaker Input Terminal Descriptor */
    AUDIO_INPUT_TERMINAL_DESC_SIZE,       /* bLength */
    AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
    AUDIO_CONTROL_INPUT_TERMINAL,         /* bDescriptorSubtype */
    0x01,                                 /* bTerminalID */
    0x01,                                 /* wTerminalType AUDIO_TERMINAL_USB_STREAMING   0x0101 */
    0x01,
    0x00,                                 /* bAssocTerminal */
    0x01,                                 /* bNrChannels */
    0x00,                                 /* wChannelConfig 0x0000  Mono */
    0x00,
    0x00,                                 /* iChannelNames */
    0x00,                                 /* iTerminal */
    /* 12 byte*/

    /* USB Speaker Audio Feature Unit Descriptor */
    0x09,                                 /* bLength */
    AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
    AUDIO_CONTROL_FEATURE_UNIT,           /* bDescriptorSubtype */
    AUDIO_OUT_STREAMING_CTRL,             /* bUnitID */
    0x01,                                 /* bSourceID */
    0x01,                                 /* bControlSize */
    AUDIO_CONTROL_MUTE,                   /* bmaControls(0) */
    0x00,                                 /* bmaControls(1) */
    0x00,                                 /* iTerminal */
    /* 09 byte*/

    /*USB Speaker Output Terminal Descriptor */
    0x09,      /* bLength */
    AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
    AUDIO_CONTROL_OUTPUT_TERMINAL,        /* bDescriptorSubtype */
    0x03,                                 /* bTerminalID */
    0x01,                                 /* wTerminalType  0x0301*/
    0x03,
    0x00,                                 /* bAssocTerminal */
    0x02,                                 /* bSourceID */
    0x00,                                 /* iTerminal */
    /* 09 byte*/

    /* USB Speaker Standard AS Interface Descriptor - Audio Streaming Zero Bandwith */
    /* Interface 1, Alternate Setting 0                                             */
    AUDIO_INTERFACE_DESC_SIZE,  /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,        /* bDescriptorType */
    0x01,                                 /* bInterfaceNumber */
    0x00,                                 /* bAlternateSetting */
    0x00,                                 /* bNumEndpoints */
    USB_DEVICE_CLASS_AUDIO,               /* bInterfaceClass */
    AUDIO_SUBCLASS_AUDIOSTREAMING,        /* bInterfaceSubClass */
    AUDIO_PROTOCOL_UNDEFINED,             /* bInterfaceProtocol */
    0x00,                                 /* iInterface */
    /* 09 byte*/

    /* USB Speaker Standard AS Interface Descriptor - Audio Streaming Operational */
    /* Interface 1, Alternate Setting 1                                           */
    AUDIO_INTERFACE_DESC_SIZE,  /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,        /* bDescriptorType */
    0x01,                                 /* bInterfaceNumber */
    0x01,                                 /* bAlternateSetting */
    0x01,                                 /* bNumEndpoints */
    USB_DEVICE_CLASS_AUDIO,               /* bInterfaceClass */
    AUDIO_SUBCLASS_AUDIOSTREAMING,        /* bInterfaceSubClass */
    AUDIO_PROTOCOL_UNDEFINED,             /* bInterfaceProtocol */
    0x00,                                 /* iInterface */
    /* 09 byte*/

    /* USB Speaker Audio Streaming Interface Descriptor */
    AUDIO_STREAMING_INTERFACE_DESC_SIZE,  /* bLength */
    AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
    AUDIO_STREAMING_GENERAL,              /* bDescriptorSubtype */
    0x01,                                 /* bTerminalLink */
    0x01,                                 /* bDelay */
    0x01,                                 /* wFormatTag AUDIO_FORMAT_PCM  0x0001*/
    0x00,
    /* 07 byte*/

    /* USB Speaker Audio Type III Format Interface Descriptor */
    0x0B,                                 /* bLength */
    AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
    AUDIO_STREAMING_FORMAT_TYPE,          /* bDescriptorSubtype */
    AUDIO_FORMAT_TYPE_III,                /* bFormatType */ 
    0x02,                                 /* bNrChannels */
    0x02,                                 /* bSubFrameSize :  2 Bytes per frame (16bits) */
    16,                                   /* bBitResolution (16-bits per sample) */ 
    0x01,                                 /* bSamFreqType only one frequency supported */ 
    SAMPLE_FREQ(USBD_AUDIO_FREQ),         /* Audio sampling frequency coded on 3 bytes */
    /* 11 byte*/

    /* Endpoint 9 - Standard Descriptor */
    AUDIO_STANDARD_ENDPOINT_DESC_SIZE,    /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */
    AUDIO_OUT_EP,                         /* bEndpointAddress 9 out endpoint*/
    USB_ENDPOINT_TYPE_ISOCHRONOUS,        /* bmAttributes */
    AUDIO_PACKET_SZE(USBD_AUDIO_FREQ),    /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
    0x01,                                 /* bInterval */
    0x00,                                 /* bRefresh */
    0x00,                                 /* bSynchAddress */
    /* 09 byte*/

    /* Endpoint - Audio Streaming Descriptor*/
    AUDIO_STREAMING_ENDPOINT_DESC_SIZE,   /* bLength */
    AUDIO_ENDPOINT_DESCRIPTOR_TYPE,       /* bDescriptorType */
    AUDIO_ENDPOINT_GENERAL,               /* bDescriptor */
    0x00,                                 /* bmAttributes */
    0x00,                                 /* bLockDelayUnits */
    0x00,                                 /* wLockDelay */
    0x00,
    /* 07 byte*/
} ;

/**
*\*\name    USBD_AUDIO_Init.
*\*\fun     Initializes the AUDIO interface.
*\*\param   pdev: device instance.
*\*\param   cfgidx: Configuration index
*\*\return  status.
**/
static uint8_t USBD_AUDIO_Init (void  *pdev, uint8_t cfgidx)
{  
    /* Open EP OUT */
    USBDEV_EP_Open(pdev, AUDIO_OUT_EP, AUDIO_OUT_PACKET, USB_EP_ISOC);

    /* Initialize the Audio output Hardware layer */
    if (AUDIO_OUT_fops.Init(USBD_AUDIO_FREQ, DEFAULT_VOLUME, 0) != USBD_OK)
    {
        return USBD_FAIL;
    }

    /* Prepare Out endpoint to receive audio data */
    USBDEV_EP_PrepareRx(pdev, AUDIO_OUT_EP, (uint8_t*)IsocOutBuff, AUDIO_OUT_PACKET);  
  
    return USBD_OK;
}

/**
*\*\name    USBD_AUDIO_DeInit.
*\*\fun     DeInitializes the AUDIO layer.
*\*\param   pdev: device instance.
*\*\param   cfgidx: Configuration index
*\*\return  status.
**/
static uint8_t USBD_AUDIO_DeInit (void  *pdev, uint8_t cfgidx)
{
    USBDEV_EP_Close(pdev , AUDIO_OUT_EP);

    /* DeInitialize the Audio output Hardware layer */
    if (AUDIO_OUT_fops.DeInit(0) != USBD_OK)
    {
        return USBD_FAIL;
    }

    return USBD_OK;
}

/**
*\*\name    USBD_AUDIO_Setup.
*\*\fun     Handles the Audio control request parsing.
*\*\param   pdev: device instance.
*\*\param   req: usb requests
*\*\return  status.
**/
static uint8_t USBD_AUDIO_Setup (void  *pdev, USB_SETUP_REQ *req)
{
    uint16_t len=USB_AUDIO_DESC_SIZ;
    uint8_t  *pbuf=USBD_AUDIO_CfgDesc + 18;

    switch (req->bmRequest & USB_REQ_TYPE_MASK)
    {
        /* AUDIO Class Requests */
        case USB_REQ_TYPE_CLASS :    
            switch (req->bRequest)
            {
                case AUDIO_REQ_GET_CUR:
                    AUDIO_Req_GetCurrent(pdev, req);
                    break;
                  
                case AUDIO_REQ_SET_CUR:
                    AUDIO_Req_SetCurrent(pdev, req);   
                    break;

                default:
                    USBD_CtrlError (pdev, req);
                    return USBD_FAIL;
            }
            break;

        /* Standard Requests */
        case USB_REQ_TYPE_STANDARD:
            switch (req->bRequest)
            {
                case USB_REQ_GET_DESCRIPTOR: 
                    if( (req->wValue >> 8) == AUDIO_DESCRIPTOR_TYPE)
                    {
                        pbuf = USBD_AUDIO_CfgDesc + 18;
                        len = MIN(USB_AUDIO_DESC_SIZ , req->wLength);
                    }
                    USBD_CtrlSendData (pdev, pbuf, len);
                    break;

                case USB_REQ_GET_INTERFACE :
                    USBD_CtrlSendData (pdev, (uint8_t *)&USBD_AUDIO_AltSet, 1);
                    break;

                case USB_REQ_SET_INTERFACE :
                    if ((uint8_t)(req->wValue) < AUDIO_TOTAL_IF_NUM)
                    {
                        USBD_AUDIO_AltSet = (uint8_t)(req->wValue);
                    }
                    else
                    {
                        /* Call the error management function (command will be nacked */
                        USBD_CtrlError (pdev, req);
                    }
                    break;
            }
    }
    return USBD_OK;
}

/**
*\*\name    USBD_AUDIO_EP0_RxReady.
*\*\fun     Handles audio control requests data.
*\*\param   pdev: device instance.
*\*\return  status.
**/
static uint8_t  USBD_AUDIO_EP0_RxReady (void  *pdev)
{ 
    /* Check if an AudioControl request has been issued */
    if (AudioCtrlCmd == AUDIO_REQ_SET_CUR)
    {/* In this driver, to simplify code, only SET_CUR request is managed */
        /* Check for which addressed unit the AudioControl request has been issued */
        if (AudioCtrlUnit == AUDIO_OUT_STREAMING_CTRL)
        {/* In this driver, to simplify code, only one unit is manage */
            /* Call the audio interface mute function */
            AUDIO_OUT_fops.MuteCtrl(AudioCtrl[0]);

            /* Reset the AudioCtrlCmd variable to prevent re-entering this function */
            AudioCtrlCmd = 0;
            AudioCtrlLen = 0;
        }
    } 

    return USBD_OK;
}

/**
*\*\name    USBD_AUDIO_DataIn.
*\*\fun     Handles the audio IN data stage.
*\*\param   pdev: device instance.
*\*\param   epnum: endpoint number
*\*\return  status.
**/
static uint8_t  USBD_AUDIO_DataIn (void *pdev, uint8_t epnum)
{
    return USBD_OK;
}

__IO uint32_t DataOutCounter = 0;
/**
*\*\name    USBD_AUDIO_DataOut.
*\*\fun     Handles the Audio Out data stage.
*\*\param   pdev: device instance.
*\*\param   epnum: endpoint number
*\*\return  status.
**/
static uint8_t  USBD_AUDIO_DataOut (void *pdev, uint8_t epnum)
{     
    DataOutCounter++;
    if (epnum == AUDIO_OUT_EP)
    {
        /* Increment the Buffer pointer or roll it back when all buffers are full */
        if (IsocOutWrPtr >= (IsocOutBuff + (AUDIO_OUT_PACKET * OUT_PACKET_NUM)))
        {/* All buffers are full: roll back */
            IsocOutWrPtr = IsocOutBuff;
        }
        else
        {/* Increment the buffer pointer */
            IsocOutWrPtr += AUDIO_OUT_PACKET;
        }

        /* Toggle the frame index */  
        ((USB_CORE_MODULE*)pdev)->dev.out_ep[epnum].even_odd_frame = 
        (((USB_CORE_MODULE*)pdev)->dev.out_ep[epnum].even_odd_frame)? 0:1;

        /* Prepare Out endpoint to receive next audio packet */
        USBDEV_EP_PrepareRx(pdev, AUDIO_OUT_EP, (uint8_t*)(IsocOutWrPtr), AUDIO_OUT_PACKET);

        /* Trigger the start of streaming only when half buffer is full */
        if ((PlayFlag == 0) && (IsocOutWrPtr >= (IsocOutBuff + ((AUDIO_OUT_PACKET * OUT_PACKET_NUM) / 2))))
        {
            /* Enable start of Streaming */
            PlayFlag = 1;
        }
    }

    return USBD_OK;
}

/**
*\*\name    USBD_AUDIO_SOF.
*\*\fun     Handles the SOF event (data buffer update and synchronization).
*\*\param   pdev: device instance.
*\*\return  status.
**/
static uint8_t  USBD_AUDIO_SOF (void *pdev)
{     
    /* Check if there are available data in stream buffer.
    In this function, a single variable (PlayFlag) is used to avoid software delays.
    The play operation must be executed as soon as possible after the SOF detection. */
    if (PlayFlag)
    {      
        /* Start playing received packet */
        AUDIO_OUT_fops.AudioCmd((uint8_t*)(IsocOutRdPtr),  /* Samples buffer pointer */
                                AUDIO_OUT_PACKET,          /* Number of samples in Bytes */
                                AUDIO_CMD_PLAY);           /* Command to be processed */

        /* Increment the Buffer pointer or roll it back when all buffers all full */  
        if (IsocOutRdPtr >= (IsocOutBuff + (AUDIO_OUT_PACKET * OUT_PACKET_NUM)))
        {/* Roll back to the start of buffer */
            IsocOutRdPtr = IsocOutBuff;
        }
        else
        {/* Increment to the next sub-buffer */
            IsocOutRdPtr += AUDIO_OUT_PACKET;
        }

        /* If all available buffers have been consumed, stop playing */
        if (IsocOutRdPtr == IsocOutWrPtr)
        {
            /* Pause the audio stream */
            AUDIO_OUT_fops.AudioCmd((uint8_t*)(IsocOutBuff),   /* Samples buffer pointer */
                                    AUDIO_OUT_PACKET,          /* Number of samples in Bytes */
                                    AUDIO_CMD_PAUSE);          /* Command to be processed */

            /* Stop entering play loop */
            PlayFlag = 0;

            /* Reset buffer pointers */
            IsocOutRdPtr = IsocOutBuff;
            IsocOutWrPtr = IsocOutBuff;
        }
    }

    return USBD_OK;
}

/**
*\*\name    USBD_AUDIO_OUT_Incplt.
*\*\fun     Handles the iso out incomplete event.
*\*\param   pdev: device instance.
*\*\return  status.
**/
static uint8_t  USBD_AUDIO_OUT_Incplt (void  *pdev)
{
    return USBD_OK;
}

/**
*\*\name    AUDIO_Req_GetCurrent.
*\*\fun     Handles the GET_CUR Audio control request.
*\*\param   pdev: device instance.
*\*\param   req: setup class request
*\*\return  status.
**/
static void AUDIO_Req_GetCurrent(void *pdev, USB_SETUP_REQ *req)
{  
    /* Send the current mute state */
    USBD_CtrlSendData (pdev, AudioCtrl, req->wLength);
}

/**
*\*\name    AUDIO_Req_SetCurrent.
*\*\fun     Handles the SET_CUR Audio control request.
*\*\param   pdev: device instance.
*\*\param   req: setup class request
*\*\return  status.
**/
static void AUDIO_Req_SetCurrent(void *pdev, USB_SETUP_REQ *req)
{ 
    if (req->wLength)
    {
        /* Prepare the reception of the buffer over EP0 */
        USBD_CtrlPrepareRx (pdev, AudioCtrl, req->wLength);

        /* Set the global variables indicating current request and its length 
        to the function USBD_AUDIO_EP0_RxReady() which will process the request */
        AudioCtrlCmd = AUDIO_REQ_SET_CUR;     /* Set the request value */
        AudioCtrlLen = req->wLength;          /* Set the request data length */
        AudioCtrlUnit = HIBYTE(req->wIndex);  /* Set the request target unit */
    }
}

/**
*\*\name    USBD_AUDIO_GetCfgDesc.
*\*\fun     Returns configuration descriptor.
*\*\param   speed : current device speed
*\*\param   length : pointer data length
*\*\return  pointer to descriptor buffer.
**/
static uint8_t  *USBD_AUDIO_GetCfgDesc (uint8_t speed, uint16_t *length)
{
    *length = sizeof (USBD_AUDIO_CfgDesc);
    return USBD_AUDIO_CfgDesc;
}
