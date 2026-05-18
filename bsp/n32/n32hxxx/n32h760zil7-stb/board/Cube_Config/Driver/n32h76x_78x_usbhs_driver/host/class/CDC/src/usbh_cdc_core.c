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
 * @file usbh_cdc_core.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "usbh_cdc_core.h"

#define CDC_BUFFER_SIZE                 1024

#ifdef USB_INTERNAL_DMA_ENABLED
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma data_alignment=4   
#endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN CDC_Machine_TypeDef   CDC_Machine __ALIGN_END ;

CDC_Requests                        CDC_ReqState;
CDC_Xfer_TypeDef                    CDC_TxParam;
CDC_Xfer_TypeDef                    CDC_RxParam;

#ifdef USB_INTERNAL_DMA_ENABLED
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma data_alignment=4   
#endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN uint8_t               TxBuf [CDC_BUFFER_SIZE] __ALIGN_END ;

#ifdef USB_INTERNAL_DMA_ENABLED
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma data_alignment=4   
#endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN uint8_t               RxBuf [CDC_BUFFER_SIZE] __ALIGN_END ;

CDC_Usercb_TypeDef UserCb;
uint8_t RX_Enabled = 0;

static void CDC_InitTxRxParam(void);

static void CDC_ReceiveData(CDC_Xfer_TypeDef *cdc_Data);

static void CDC_ProcessTransmission(USB_CORE_MODULE *pdev, USBH_HOST  *phost);

static void CDC_ProcessReception(USB_CORE_MODULE *pdev, USBH_HOST *phost);

static USBH_Status CDC_InterfaceInit(USB_CORE_MODULE *pdev , void *phost);

void CDC_InterfaceDeInit(USB_CORE_MODULE *pdev , void *phost);

static USBH_Status CDC_Handle(USB_CORE_MODULE *pdev , void *phost);

static USBH_Status CDC_ClassRequest(USB_CORE_MODULE *pdev , void *phost);


USBH_Class_cb_TypeDef  USBH_CDC_cb = 
{
    CDC_InterfaceInit,
    CDC_InterfaceDeInit,
    CDC_ClassRequest,
    CDC_Handle
};

/**
*\*\name    CDC_InterfaceInit.
*\*\fun     The function init the CDC class.
*\*\param   pdev: Selected device
*\*\param   phost: Selected device property
*\*\return  USBH_Status :Response for USB CDC driver intialization.
*\*\
**/
static USBH_Status CDC_InterfaceInit ( USB_CORE_MODULE *pdev, void *phost)
{
    USBH_HOST *pphost = phost;
    USBH_Status status = USBH_OK ;

    /* Communication Interface */
    if((pphost->device_prop.Itf_Desc[0].bInterfaceClass == COMMUNICATION_DEVICE_CLASS_CODE)&& \
     (pphost->device_prop.Itf_Desc[0].bInterfaceSubClass == ABSTRACT_CONTROL_MODEL) && \
     (pphost->device_prop.Itf_Desc[0].bInterfaceProtocol == COMMON_AT_COMMAND))
    {
        /*Collect the notification endpoint address and length*/
        CDC_Machine.CDC_CommItf.ep_addr = pphost->device_prop.Ep_Desc[0][0].bEndpointAddress;
        CDC_Machine.CDC_CommItf.length  = pphost->device_prop.Ep_Desc[0][0].wMaxPacketSize;

        if(pphost->device_prop.Ep_Desc[0][0].bEndpointAddress & 0x80)
        {
            CDC_Machine.CDC_CommItf.notificationEp = (pphost->device_prop.Ep_Desc[0][0].bEndpointAddress);
        }
        /*Allocate the length for host channel number in*/
        CDC_Machine.CDC_CommItf.hc_num_in = USBH_Alloc_Channel(pdev, CDC_Machine.CDC_CommItf.notificationEp );
        /* Open channel for IN endpoint */
        USBH_Open_Channel (pdev, CDC_Machine.CDC_CommItf.hc_num_in,pphost->device_prop.address, pphost->device_prop.speed, EP_TYPE_INTR, CDC_Machine.CDC_CommItf.length); 
    }
    else
    {
        pphost->usr_cb->DeviceNotSupported();
    }


    /* Data Interface */
    if((pphost->device_prop.Itf_Desc[1].bInterfaceClass  == DATA_INTERFACE_CLASS_CODE)&& \
       (pphost->device_prop.Itf_Desc[1].bInterfaceSubClass  == RESERVED) && \
       (pphost->device_prop.Itf_Desc[1].bInterfaceProtocol == NO_CLASS_SPECIFIC_PROTOCOL_CODE))
    {
        /*Collect the class specific endpoint address and length*/
        CDC_Machine.CDC_DataItf.ep_addr = pphost->device_prop.Ep_Desc[1][0].bEndpointAddress;
        CDC_Machine.CDC_DataItf.length  = pphost->device_prop.Ep_Desc[1][0].wMaxPacketSize;

        if(pphost->device_prop.Ep_Desc[1][0].bEndpointAddress & 0x80)
        {      
            CDC_Machine.CDC_DataItf.cdcInEp = (pphost->device_prop.Ep_Desc[1][0].bEndpointAddress);
        }
        else
        {
            CDC_Machine.CDC_DataItf.cdcOutEp = (pphost->device_prop.Ep_Desc[1][0].bEndpointAddress);
        }

        if(pphost->device_prop.Ep_Desc[1][1].bEndpointAddress & 0x80)
        {
            CDC_Machine.CDC_DataItf.cdcInEp = (pphost->device_prop.Ep_Desc[1][1].bEndpointAddress);
        }
        else
        {
            CDC_Machine.CDC_DataItf.cdcOutEp = (pphost->device_prop.Ep_Desc[1][1].bEndpointAddress);
        }

        /*Allocate the length for host channel number out*/
        CDC_Machine.CDC_DataItf.hc_num_out = USBH_Alloc_Channel(pdev, CDC_Machine.CDC_DataItf.cdcOutEp);
        /*Allocate the length for host channel number in*/
        CDC_Machine.CDC_DataItf.hc_num_in = USBH_Alloc_Channel(pdev, CDC_Machine.CDC_DataItf.cdcInEp);  

        /* Open channel for OUT endpoint */
        USBH_Open_Channel(pdev, CDC_Machine.CDC_DataItf.hc_num_out, pphost->device_prop.address, pphost->device_prop.speed, EP_TYPE_BULK, CDC_Machine.CDC_DataItf.length);  
        /* Open channel for IN endpoint */
        USBH_Open_Channel(pdev, CDC_Machine.CDC_DataItf.hc_num_in, pphost->device_prop.address, pphost->device_prop.speed, EP_TYPE_BULK, CDC_Machine.CDC_DataItf.length);

        /*Initilise the Tx/Rx Params*/
        CDC_InitTxRxParam();

        /*Initialize the class specific request with "GET_LINE_CODING"*/
        CDC_ReqState = CDC_GET_LINE_CODING_RQUEST ;
    }
    else
    {
        pphost->usr_cb->DeviceNotSupported();   
    }  
    return status;

}

/**
*\*\name    CDC_InterfaceDeInit.
*\*\fun     The function DeInit the Host Channels used for the CDC class.
*\*\param   pdev: Selected device
*\*\param   phost: Selected device property
*\*\return  none.
*\*\
**/
void CDC_InterfaceDeInit ( USB_CORE_MODULE *pdev, void *phost)
{
    if (CDC_Machine.CDC_CommItf.hc_num_in)
    {
        USB_HCH_Halt(pdev, CDC_Machine.CDC_CommItf.hc_num_in);
        USBH_Free_Channel(pdev,CDC_Machine.CDC_CommItf.hc_num_in);
        CDC_Machine.CDC_CommItf.hc_num_in = 0;     /* Reset the Channel as Free */
    }

    if (CDC_Machine.CDC_DataItf.hc_num_out)
    {
        USB_HCH_Halt(pdev, CDC_Machine.CDC_DataItf.hc_num_out);
        USBH_Free_Channel(pdev,CDC_Machine.CDC_DataItf.hc_num_out);
        CDC_Machine.CDC_DataItf.hc_num_out = 0;     /* Reset the Channel as Free */
    }

    if (CDC_Machine.CDC_DataItf.hc_num_in)
    {
        USB_HCH_Halt(pdev, CDC_Machine.CDC_DataItf.hc_num_in);
        USBH_Free_Channel  (pdev,CDC_Machine.CDC_DataItf.hc_num_in);
        CDC_Machine.CDC_DataItf.hc_num_in = 0;     /* Reset the Channel as Free */
    } 
}

/**
*\*\name    CDC_ClassRequest.
*\*\fun     The function is responsible for handling CDC Class requests for CDC class.
*\*\param   pdev: Selected device
*\*\param   phost: Selected device property
*\*\return  USBH_Status :Response for USB Set Protocol request.
*\*\
**/
static USBH_Status CDC_ClassRequest(USB_CORE_MODULE *pdev , void *phost)
{   
    USBH_HOST *pphost = phost;

    USBH_Status status         = USBH_BUSY;
    USBH_Status ClassReqStatus = USBH_BUSY;

    switch(CDC_ReqState) 
    {

        case CDC_GET_LINE_CODING_RQUEST: 
            /*Issue the get line coding request*/
            ClassReqStatus = CDC_GETLineCoding(pdev, phost);
            if( ClassReqStatus == USBH_OK )
            {          /*Change the state */
                CDC_ReqState = CDC_SET_CONTROL_LINE_STATE_REQUEST;
            }
            break;

        case CDC_SET_LINE_CODING_RQUEST: 
            /*Issue the set line coding request*/
            ClassReqStatus = CDC_SETLineCoding(pdev, phost);
            if(ClassReqStatus == USBH_OK )
            {
                /*Change the state */
                CDC_ReqState = CDC_GET_LINE_CODING_RQUEST ;
            }
            if(ClassReqStatus == USBH_NOT_SUPPORTED )
            {
                /* a Clear Feature should be issued here */
                CDC_ReqState = CDC_ERROR_STATE;
            }
            break;

        case CDC_SET_CONTROL_LINE_STATE_REQUEST:
        /*Issue the set control line coding */
            ClassReqStatus = CDC_SETControlLineState(pdev, phost);
            if( ClassReqStatus == USBH_OK )
            {
                /*Change the state */
                CDC_ReqState = CDC_SET_CONTROL_LINE_STATE_REQUEST;
                /*Also set the state of receive CDCRxParam to IDLE*/
                CDC_RxParam.CDCState = CDC_IDLE; 
                status = USBH_OK; /*This return from class specific routinues request*/
            }
            break;

        case CDC_ERROR_STATE:

            ClassReqStatus = USBH_ClrFeature(pdev, phost, 0x00, pphost->Control.hch_num_out);

            if(ClassReqStatus == USBH_OK )
            {        
                /*Change the state to waiting*/
                CDC_ReqState = CDC_GET_LINE_CODING_RQUEST ;
            }
            break;
    }

    return status; 
}



/**
*\*\name    CDC_Handle.
*\*\fun     The function is for managing state machine for CDC data transfers.
*\*\param   pdev: Selected device
*\*\param   phost: Selected device property
*\*\return  status.
*\*\
**/
static USBH_Status CDC_Handle(USB_CORE_MODULE *pdev , void *phost)
{
    USBH_Status status = USBH_OK;
    USBH_HOST *pphost = phost;

    /* Call Application process */
    pphost->usr_cb->UserApplication();  

    /*Handle the transmission */
    CDC_ProcessTransmission(pdev, pphost);

    /*Always send in packet to device*/    
    CDC_ProcessReception(pdev, pphost);

    return status;
}



/**
*\*\name    CDC_ProcessTransmission.
*\*\fun     The function is responsible for sending data to the device.
*\*\param   pdev: Selected device
*\*\param   phost: Selected device property
*\*\return  none.
*\*\
**/
void CDC_ProcessTransmission(USB_CORE_MODULE *pdev, USBH_HOST *phost)
{
    static uint32_t len ;
    URB_STATE URB_StatusTx = URB_IDLE;

    URB_StatusTx = HOST_GetURB_State(pdev , CDC_Machine.CDC_DataItf.hc_num_out);

    switch(CDC_TxParam.CDCState)
    {
        case CDC_IDLE:
            break;

        case CDC_SEND_DATA:
            if(( URB_StatusTx == URB_DONE ) || (URB_StatusTx == URB_IDLE))
            {
                /*Check the data length is more then the CDC_Machine.CDC_DataItf.CDC_DataItf.length */
                if(CDC_TxParam.DataLength > CDC_Machine.CDC_DataItf.length)
                {
                
                    len = CDC_Machine.CDC_DataItf.length ;
                    /*Send the data */
                    USBH_BulkSendData (pdev, CDC_TxParam.pRxTxBuff, len , CDC_Machine.CDC_DataItf.hc_num_out);
                }
                else
                {
                    len = CDC_TxParam.DataLength ;
                    /*Send the remaining data */
                    USBH_BulkSendData (pdev, CDC_TxParam.pRxTxBuff, len, CDC_Machine.CDC_DataItf.hc_num_out);
                }
                CDC_TxParam.CDCState = CDC_DATA_SENT;
            }
            break;

        case CDC_DATA_SENT:
            /*Check the status done for transmssion*/
            if(URB_StatusTx == URB_DONE )
            {         
                /*Point to next chunc of data*/
                CDC_TxParam.pRxTxBuff += len ;

                /*decrease the data length*/
                CDC_TxParam.DataLength -= len;    

                if(CDC_TxParam.DataLength == 0)
                {
                    CDC_TxParam.CDCState = CDC_IDLE;
                }
                else
                {
                    CDC_TxParam.CDCState = CDC_SEND_DATA; 
                }
            }
            else if( URB_StatusTx == URB_NOTREADY )
            {
                /*Send the same data */
                USBH_BulkSendData (pdev, (CDC_TxParam.pRxTxBuff), len, CDC_Machine.CDC_DataItf.hc_num_out);
            }
            break;

        case CDC_READ_DATA:
            break;

        case CDC_BUSY:
            break;

        case CDC_GET_DATA:
            break;

        case CDC_POLL:
            break;

        case CDC_CTRL_STATE:
            break;
    }
}

/**
*\*\name    CDC_ProcessReception.
*\*\fun     This function responsible for reception of data from the device.
*\*\param   pdev: Selected device
*\*\param   phost: Selected device property
*\*\return  none.
*\*\
**/
static void CDC_ProcessReception(USB_CORE_MODULE *pdev, USBH_HOST *phost)
{
    if(RX_Enabled == 1)
    {
        URB_STATE URB_StatusRx =   HOST_GetURB_State(pdev , CDC_Machine.CDC_DataItf.hc_num_in);  

        switch(CDC_RxParam.CDCState)
        {
            case CDC_IDLE:
                /*check the received length lesser then the remaining space available in the 
                buffer */
                if(CDC_RxParam.DataLength < (CDC_RxParam.BufferLen - CDC_Machine.CDC_DataItf.length))
                {
                    /*Receive the data */
                    USBH_BulkReceiveData(pdev, CDC_RxParam.pFillBuff, CDC_Machine.CDC_DataItf.length, CDC_Machine.CDC_DataItf.hc_num_in);

                    /*change the cdc state to USBH_CDC_GET_DATA*/
                    CDC_RxParam.CDCState = CDC_GET_DATA;
                }
                break;

            case CDC_GET_DATA:
                /*Check the last state of the device is URB_DONE */
                if(URB_StatusRx == URB_DONE)
                {
                    /* Move the pointer as well as datalength */
                    CDC_RxParam.DataLength += pdev->host.XferCnt[CDC_Machine.CDC_DataItf.hc_num_in];
                    CDC_RxParam.pFillBuff  += pdev->host.XferCnt[CDC_Machine.CDC_DataItf.hc_num_in];


                    /* Process the recived data */
                    CDC_ReceiveData(&CDC_RxParam);

                    /*change the state od the CDC state*/
                    CDC_RxParam.CDCState = CDC_IDLE;
                }
                break;

            case CDC_READ_DATA:
                break;

            case CDC_BUSY:
                break;

            case CDC_SEND_DATA:
                break;

            case CDC_DATA_SENT:
                break;

            case CDC_POLL:
                break;

            case CDC_CTRL_STATE:
                break;
        }
    }
}


/**
*\*\name    CDC_InitTxRxParam.
*\*\fun     Initialize the transmit and receive buffer and its parameter.
*\*\param   none.
*\*\return  none.
*\*\
**/
static void CDC_InitTxRxParam(void)
{
    /*Initialize the Transmit buffer and its parameter*/
    CDC_TxParam.CDCState = CDC_IDLE;
    CDC_TxParam.DataLength = 0;
    CDC_TxParam.pRxTxBuff = TxBuf;

    /*Initialize the Receive buffer and its parameter*/
    CDC_RxParam.CDCState = CDC_IDLE;
    CDC_RxParam.DataLength = 0;
    CDC_RxParam.pFillBuff = RxBuf;  
    CDC_RxParam.pEmptyBuff = RxBuf;
    CDC_RxParam.BufferLen = sizeof(RxBuf);
}

/**
*\*\name    CDC_ReceiveData.
*\*\fun     This is a call back function from cdc core layer to redirect the received data on the user out put system.
*\*\param   cdc_Data: type of USBH_CDCXfer_TypeDef.
*\*\return  none.
*\*\
**/
static void CDC_ReceiveData(CDC_Xfer_TypeDef *cdc_Data)
{
    uint8_t *ptr; 

    if(cdc_Data->pEmptyBuff < cdc_Data->pFillBuff)
    {
        ptr = cdc_Data->pFillBuff;
        *ptr = 0x00;

        /* redirect the received data on the user out put system */
        UserCb.Receive(cdc_Data->pEmptyBuff);

        cdc_Data->pFillBuff  = cdc_Data->pEmptyBuff ; 
        cdc_Data->DataLength = 0;    /*Reset the data length to zero*/
    }
}


/**
*\*\name    CDC_SendData.
*\*\fun     This function send data to the device.
*\*\param   data : the pointer of send data
*\*\param   length : length of data
*\*\return  none.
**/
void CDC_SendData(uint8_t *data, uint16_t length)
{
    if(CDC_TxParam.CDCState == CDC_IDLE)
    {
        CDC_TxParam.pRxTxBuff = data; 
        CDC_TxParam.DataLength = length;
        CDC_TxParam.CDCState = CDC_SEND_DATA;  
    }    
}

/**
*\*\name    CDC_StartReception.
*\*\fun     CDC start reception.
*\*\param   pdev: Selected device
*\*\return  none.
**/
void CDC_StartReception(USB_CORE_MODULE *pdev)
{
    RX_Enabled = 1;
}

/**
*\*\name    CDC_StopReception.
*\*\fun     CDC stop reception.
*\*\param   pdev: Selected device
*\*\return  none.
**/
void CDC_StopReception(USB_CORE_MODULE *pdev)
{
    RX_Enabled = 0; 
    USB_HCH_Halt(pdev, CDC_Machine.CDC_DataItf.hc_num_in);
    USBH_Free_Channel(pdev,CDC_Machine.CDC_DataItf.hc_num_in);
}
