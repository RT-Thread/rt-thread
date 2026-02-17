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
 * @file usbh_msc_scsi.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
/* Includes ------------------------------------------------------------------*/
#include "usbh_msc_core.h"
#include "usbh_msc_scsi.h"
#include "usbh_msc_bot.h"
#include "usbh_ioreq.h"
#include "usbh_def.h"

MassStorageParameter_TypeDef USBH_MSC_Param; 

#ifdef USB_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN uint8_t USBH_DataInBuffer[512] __ALIGN_END ;

#ifdef USB_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN uint8_t USBH_DataOutBuffer[512] __ALIGN_END ;

/**
*\*\name    USBH_MSC_TestUnitReady.
*\*\fun     Issues 'Test unit ready' command to the device. Once the response received, it updates the status to upper layer.
*\*\param   pdev: selected device.
*\*\return  status.
*\*\
**/
uint8_t USBH_MSC_TestUnitReady (USB_CORE_MODULE *pdev)
{
    uint8_t index;
    USBH_MSC_Status_TypeDef status = USBH_MSC_BUSY;

    if(HOST_IsDeviceConnected(pdev))
    {  
        switch(USBH_MSC_BOTXferParam.CmdStateMachine)
        {
            case CMD_SEND_STATE:  
                /*Prepare the CBW and relevent field*/
                USBH_MSC_CBWData.field.CBWTransferLength = 0;       /* No Data Transfer */
                USBH_MSC_CBWData.field.CBWFlags = USB_EP_DIR_OUT;
                USBH_MSC_CBWData.field.CBWLength = CBW_LENGTH_TEST_UNIT_READY;
                USBH_MSC_BOTXferParam.pRxTxBuff = USBH_MSC_CSWData.CSWArray;
                USBH_MSC_BOTXferParam.DataLength = USBH_MSC_CSW_MAX_LENGTH;
                USBH_MSC_BOTXferParam.MSCStateCurrent = USBH_MSC_TEST_UNIT_READY;

                for(index = CBW_CB_LENGTH - 1; index != 0; index--)
                {
                    USBH_MSC_CBWData.field.CBWCB[index] = 0x00;
                }

                USBH_MSC_CBWData.field.CBWCB[0]  = OPCODE_TEST_UNIT_READY; 
                USBH_MSC_BOTXferParam.BOTState = USBH_MSC_SEND_CBW;
                /* Start the transfer, then let the state 
                machine magage the other transactions */
                USBH_MSC_BOTXferParam.MSCState = USBH_MSC_BOT_USB_TRANSFERS;
                USBH_MSC_BOTXferParam.BOTXferStatus = USBH_MSC_BUSY;
                USBH_MSC_BOTXferParam.CmdStateMachine = CMD_WAIT_STATUS;

                status = USBH_MSC_BUSY; 
                break;
              
            case CMD_WAIT_STATUS: 
                if(USBH_MSC_BOTXferParam.BOTXferStatus == USBH_MSC_OK)
                { 
                    /* Commands successfully sent and Response Received  */       
                    USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
                    status = USBH_MSC_OK;      
                }
                else if ( USBH_MSC_BOTXferParam.BOTXferStatus == USBH_MSC_FAIL )
                {
                    /* Failure Mode */
                    USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
                    status = USBH_MSC_FAIL;
                }
                else if ( USBH_MSC_BOTXferParam.BOTXferStatus == USBH_MSC_PHASE_ERROR )
                {
                    /* Failure Mode */
                    USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
                    status = USBH_MSC_PHASE_ERROR;    
                }  
                break;
              
            default:
              break;
        }
    }
    return status;
}



/**
*\*\name    USBH_MSC_ReadCapacity10.
*\*\fun     Issue the read capacity command to the device. Once the response received, it updates the status to upper layer.
*\*\param   pdev: selected device.
*\*\return  status.
*\*\
**/
uint8_t USBH_MSC_ReadCapacity10(USB_CORE_MODULE *pdev)
{
    uint8_t index;
    USBH_MSC_Status_TypeDef status = USBH_MSC_BUSY;

    if(HOST_IsDeviceConnected(pdev))
    {  
        switch(USBH_MSC_BOTXferParam.CmdStateMachine)
        {
            case CMD_SEND_STATE:
                /*Prepare the CBW and relevent field*/
                USBH_MSC_CBWData.field.CBWTransferLength = XFER_LEN_READ_CAPACITY10;
                USBH_MSC_CBWData.field.CBWFlags = USB_EP_DIR_IN;
                USBH_MSC_CBWData.field.CBWLength = CBW_LENGTH;

                USBH_MSC_BOTXferParam.pRxTxBuff = USBH_DataInBuffer;
                USBH_MSC_BOTXferParam.MSCStateCurrent = USBH_MSC_READ_CAPACITY10;

                for(index = CBW_CB_LENGTH -1; index != 0; index--)
                {
                    USBH_MSC_CBWData.field.CBWCB[index] = 0x00;
                }    

                USBH_MSC_CBWData.field.CBWCB[0]  = OPCODE_READ_CAPACITY10; 
                USBH_MSC_BOTXferParam.BOTState = USBH_MSC_SEND_CBW;

                /* Start the transfer, then let the state machine manage the other 
                                                                    transactions */
                USBH_MSC_BOTXferParam.MSCState = USBH_MSC_BOT_USB_TRANSFERS;
                USBH_MSC_BOTXferParam.BOTXferStatus = USBH_MSC_BUSY;
                USBH_MSC_BOTXferParam.CmdStateMachine = CMD_WAIT_STATUS;

                status = USBH_MSC_BUSY;
                break;

            case CMD_WAIT_STATUS:
                if(USBH_MSC_BOTXferParam.BOTXferStatus == USBH_MSC_OK)
                {
                    /*assign the capacity*/
                    (((uint8_t*)&USBH_MSC_Param.MSCapacity )[3]) = USBH_DataInBuffer[0];
                    (((uint8_t*)&USBH_MSC_Param.MSCapacity )[2]) = USBH_DataInBuffer[1];
                    (((uint8_t*)&USBH_MSC_Param.MSCapacity )[1]) = USBH_DataInBuffer[2];
                    (((uint8_t*)&USBH_MSC_Param.MSCapacity )[0]) = USBH_DataInBuffer[3];

                    /*assign the page length*/
                    (((uint8_t*)&USBH_MSC_Param.MSPageLength )[1]) = USBH_DataInBuffer[6];
                    (((uint8_t*)&USBH_MSC_Param.MSPageLength )[0]) = USBH_DataInBuffer[7];

                    /* Commands successfully sent and Response Received  */       
                    USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
                    status = USBH_MSC_OK;      
                }
                else if ( USBH_MSC_BOTXferParam.BOTXferStatus == USBH_MSC_FAIL )
                {
                    /* Failure Mode */
                    USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
                    status = USBH_MSC_FAIL;
                }  
                else if ( USBH_MSC_BOTXferParam.BOTXferStatus == USBH_MSC_PHASE_ERROR )
                {
                    /* Failure Mode */
                    USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
                    status = USBH_MSC_PHASE_ERROR;    
                } 
                else
                {
                    /* Wait for the Commands to get Completed */
                    /* NO Change in state Machine */
                }
            break;

            default:
            break;
        }
    }
    return status;
}



/**
*\*\name    USBH_MSC_ModeSense6.
*\*\fun     Issue the Mode Sense6 Command to the device. This function is used for reading the WriteProtect Status of the Mass-Storage device.
*\*\param   pdev: selected device.
*\*\return  status.
*\*\
**/
uint8_t USBH_MSC_ModeSense6(USB_CORE_MODULE *pdev)
{
    uint8_t index;
    USBH_MSC_Status_TypeDef status = USBH_MSC_BUSY;

    if(HOST_IsDeviceConnected(pdev))
    {  
        switch(USBH_MSC_BOTXferParam.CmdStateMachine)
        {
            case CMD_SEND_STATE:
                /*Prepare the CBW and relevent field*/
                USBH_MSC_CBWData.field.CBWTransferLength = XFER_LEN_MODE_SENSE6;
                USBH_MSC_CBWData.field.CBWFlags = USB_EP_DIR_IN;
                USBH_MSC_CBWData.field.CBWLength = CBW_LENGTH;

                USBH_MSC_BOTXferParam.pRxTxBuff = USBH_DataInBuffer;
                USBH_MSC_BOTXferParam.MSCStateCurrent = USBH_MSC_MODE_SENSE6;

                for(index = CBW_CB_LENGTH - 1; index != 0; index--)
                {
                    USBH_MSC_CBWData.field.CBWCB[index] = 0x00;
                }    

                USBH_MSC_CBWData.field.CBWCB[0]  = OPCODE_MODE_SENSE6; 
                USBH_MSC_CBWData.field.CBWCB[2]  = MODE_SENSE_PAGE_CONTROL_FIELD | MODE_SENSE_PAGE_CODE;
                                           
                USBH_MSC_CBWData.field.CBWCB[4]  = XFER_LEN_MODE_SENSE6;
                                                                                      
                USBH_MSC_BOTXferParam.BOTState = USBH_MSC_SEND_CBW;

                /* Start the transfer, then let the state machine manage the other transactions */
                USBH_MSC_BOTXferParam.MSCState = USBH_MSC_BOT_USB_TRANSFERS;
                USBH_MSC_BOTXferParam.BOTXferStatus = USBH_MSC_BUSY;
                USBH_MSC_BOTXferParam.CmdStateMachine = CMD_WAIT_STATUS;

                status = USBH_MSC_BUSY;
                break;

            case CMD_WAIT_STATUS:
                if(USBH_MSC_BOTXferParam.BOTXferStatus == USBH_MSC_OK)
                {
                    /* Assign the Write Protect status */
                    /* If WriteProtect = 0, Writing is allowed 
                    If WriteProtect != 0, Disk is Write Protected */
                    if ( USBH_DataInBuffer[2] & MASK_MODE_SENSE_WRITE_PROTECT)
                    {
                        USBH_MSC_Param.MSWriteProtect   = DISK_WRITE_PROTECTED;
                    }
                    else
                    {
                        USBH_MSC_Param.MSWriteProtect   = 0;
                    }

                    /* Commands successfully sent and Response Received  */       
                    USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
                    status = USBH_MSC_OK;      
                }
                else if ( USBH_MSC_BOTXferParam.BOTXferStatus == USBH_MSC_FAIL )
                {
                    /* Failure Mode */
                    USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
                    status = USBH_MSC_FAIL;
                }
                else if ( USBH_MSC_BOTXferParam.BOTXferStatus == USBH_MSC_PHASE_ERROR )
                {
                    /* Failure Mode */
                    USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
                    status = USBH_MSC_PHASE_ERROR;    
                }
                else
                {
                    /* Wait for the Commands to get Completed */
                    /* NO Change in state Machine */
                }
                break;

            default:
                break;
        }
    }
    return status;
}

/**
*\*\name    USBH_MSC_RequestSense.
*\*\fun     Issues the Request Sense command to the device. Once the response received, it updates the status to upper layer.
*\*\param   pdev: selected device.
*\*\return  status.
*\*\
**/
uint8_t USBH_MSC_RequestSense(USB_CORE_MODULE *pdev)
{
    USBH_MSC_Status_TypeDef status = USBH_MSC_BUSY;

    uint8_t index;


    if(HOST_IsDeviceConnected(pdev))
    {  
        switch(USBH_MSC_BOTXferParam.CmdStateMachine)
        {
            case CMD_SEND_STATE:
                /*Prepare the CBW and relevant field*/
                USBH_MSC_CBWData.field.CBWTransferLength = \
                                                    ALLOCATION_LENGTH_REQUEST_SENSE;
                USBH_MSC_CBWData.field.CBWFlags = USB_EP_DIR_IN;
                USBH_MSC_CBWData.field.CBWLength = CBW_LENGTH;
                USBH_MSC_BOTXferParam.pRxTxBuff = USBH_DataInBuffer;
                USBH_MSC_BOTXferParam.MSCStateBkp = USBH_MSC_BOTXferParam.MSCStateCurrent;
                USBH_MSC_BOTXferParam.MSCStateCurrent = USBH_MSC_REQUEST_SENSE;
            
                for(index = CBW_CB_LENGTH - 1; index != 0; index--)
                {
                    USBH_MSC_CBWData.field.CBWCB[index] = 0x00;
                }    

                USBH_MSC_CBWData.field.CBWCB[0]  = OPCODE_REQUEST_SENSE; 
                USBH_MSC_CBWData.field.CBWCB[1]  = DESC_REQUEST_SENSE;
                USBH_MSC_CBWData.field.CBWCB[4]  = ALLOCATION_LENGTH_REQUEST_SENSE;

                USBH_MSC_BOTXferParam.BOTState = USBH_MSC_SEND_CBW;
                /* Start the transfer, then let the state machine manage 
                the other transactions */
                USBH_MSC_BOTXferParam.MSCState = USBH_MSC_BOT_USB_TRANSFERS;
                USBH_MSC_BOTXferParam.BOTXferStatus = USBH_MSC_BUSY;
                USBH_MSC_BOTXferParam.CmdStateMachine = CMD_WAIT_STATUS;

                status = USBH_MSC_BUSY;

                break;

            case CMD_WAIT_STATUS:
                if(USBH_MSC_BOTXferParam.BOTXferStatus == USBH_MSC_OK)
                {
                    /* Get Sense data*/
                    (((uint8_t*)&USBH_MSC_Param.MSSenseKey )[3]) = USBH_DataInBuffer[0];
                    (((uint8_t*)&USBH_MSC_Param.MSSenseKey )[2]) = USBH_DataInBuffer[1];
                    (((uint8_t*)&USBH_MSC_Param.MSSenseKey )[1]) = USBH_DataInBuffer[2];
                    (((uint8_t*)&USBH_MSC_Param.MSSenseKey )[0]) = USBH_DataInBuffer[3];

                    /* Commands successfully sent and Response Received  */       
                    USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
                    status = USBH_MSC_OK;      
                }
                else if ( USBH_MSC_BOTXferParam.BOTXferStatus == USBH_MSC_FAIL )
                {
                    /* Failure Mode */
                    USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
                    status = USBH_MSC_FAIL;
                }

                else if ( USBH_MSC_BOTXferParam.BOTXferStatus == USBH_MSC_PHASE_ERROR )
                {
                    /* Failure Mode */
                    USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
                    status = USBH_MSC_PHASE_ERROR;    
                }

                else
                {
                    /* Wait for the Commands to get Completed */
                    /* NO Change in state Machine */
                }
                break;

            default:
                break;
        }
    }
    return status;
}

/**
*\*\name    USBH_MSC_Write10.
*\*\fun     Issue the write command to the device. Once the response received, it updates the status to upper layer.
*\*\param   pdev: selected device.
*\*\param   dataBuffer : DataBuffer contains the data to write.
*\*\param   address : Address to which the data will be written.
*\*\param   nbOfbytes : NbOfbytes to be written.
*\*\return  status.
*\*\
**/
uint8_t USBH_MSC_Write10(USB_CORE_MODULE *pdev, uint8_t *dataBuffer, uint32_t address, uint32_t nbOfbytes)
{
    uint8_t index;
    USBH_MSC_Status_TypeDef status = USBH_MSC_BUSY;
    uint16_t nbOfPages;

    if(HOST_IsDeviceConnected(pdev))
    {  
        switch(USBH_MSC_BOTXferParam.CmdStateMachine)
        {
            case CMD_SEND_STATE:   
                USBH_MSC_CBWData.field.CBWTransferLength = nbOfbytes;
                USBH_MSC_CBWData.field.CBWFlags = USB_EP_DIR_OUT;
                USBH_MSC_CBWData.field.CBWLength = CBW_LENGTH;
                USBH_MSC_BOTXferParam.pRxTxBuff = dataBuffer;


                for(index = CBW_CB_LENGTH - 1; index != 0; index--)  
                {
                    USBH_MSC_CBWData.field.CBWCB[index] = 0x00;
                }

                USBH_MSC_CBWData.field.CBWCB[0]  = OPCODE_WRITE10; 

                /*logical block address*/
                USBH_MSC_CBWData.field.CBWCB[2]  = (((uint8_t*)&address)[3]) ;
                USBH_MSC_CBWData.field.CBWCB[3]  = (((uint8_t*)&address)[2]);
                USBH_MSC_CBWData.field.CBWCB[4]  = (((uint8_t*)&address)[1]);
                USBH_MSC_CBWData.field.CBWCB[5]  = (((uint8_t*)&address)[0]);

                /*USBH_MSC_PAGE_LENGTH = 512*/
                nbOfPages = nbOfbytes/ USBH_MSC_PAGE_LENGTH; 

                /*Transfer length */
                USBH_MSC_CBWData.field.CBWCB[7]  = (((uint8_t *)&nbOfPages)[1]) ; 
                USBH_MSC_CBWData.field.CBWCB[8]  = (((uint8_t *)&nbOfPages)[0]) ; 

                USBH_MSC_BOTXferParam.BOTState = USBH_MSC_SEND_CBW;
                /* Start the transfer, then let the state machine 
                manage the other transactions */
                USBH_MSC_BOTXferParam.MSCState = USBH_MSC_BOT_USB_TRANSFERS;
                USBH_MSC_BOTXferParam.BOTXferStatus = USBH_MSC_BUSY;
                USBH_MSC_BOTXferParam.CmdStateMachine = CMD_WAIT_STATUS;

                status = USBH_MSC_BUSY;

            break;

            case CMD_WAIT_STATUS:
                if(USBH_MSC_BOTXferParam.BOTXferStatus == USBH_MSC_OK)
                { 
                    /* Commands successfully sent and Response Received  */       
                    USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
                    status = USBH_MSC_OK;      
                }
                else if ( USBH_MSC_BOTXferParam.BOTXferStatus == USBH_MSC_FAIL )
                {
                    /* Failure Mode */
                    USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
                }
                else if ( USBH_MSC_BOTXferParam.BOTXferStatus == USBH_MSC_PHASE_ERROR )
                {
                    /* Failure Mode */
                    USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
                    status = USBH_MSC_PHASE_ERROR;    
                }
                break;

            default:
                break;
        }
    }
    return status;
}


/**
*\*\name    USBH_MSC_Read10.
*\*\fun     Issue the read command to the device. Once the response received, it updates the status to upper layer.
*\*\param   pdev: selected device.
*\*\param   dataBuffer : DataBuffer contains the data to read.
*\*\param   address : Address to which the data will be read.
*\*\param   nbOfbytes : NbOfbytes to be read.
*\*\return  status.
*\*\
**/
uint8_t USBH_MSC_Read10(USB_CORE_MODULE *pdev, uint8_t *dataBuffer, uint32_t address, uint32_t nbOfbytes)
{
    uint8_t index;
    static USBH_MSC_Status_TypeDef status = USBH_MSC_BUSY;
    uint16_t nbOfPages;
    status = USBH_MSC_BUSY;

    if(HOST_IsDeviceConnected(pdev))
    {
        switch(USBH_MSC_BOTXferParam.CmdStateMachine)
        {
            case CMD_SEND_STATE:
                /*Prepare the CBW and relevant field*/
                USBH_MSC_CBWData.field.CBWTransferLength = nbOfbytes;
                USBH_MSC_CBWData.field.CBWFlags = USB_EP_DIR_IN;
                USBH_MSC_CBWData.field.CBWLength = CBW_LENGTH;

                USBH_MSC_BOTXferParam.pRxTxBuff = dataBuffer;

                for(index = CBW_CB_LENGTH - 1; index != 0; index--)
                {
                    USBH_MSC_CBWData.field.CBWCB[index] = 0x00;
                }

                USBH_MSC_CBWData.field.CBWCB[0]  = OPCODE_READ10; 

                /*logical block address*/

                USBH_MSC_CBWData.field.CBWCB[2]  = (((uint8_t*)&address)[3]);
                USBH_MSC_CBWData.field.CBWCB[3]  = (((uint8_t*)&address)[2]);
                USBH_MSC_CBWData.field.CBWCB[4]  = (((uint8_t*)&address)[1]);
                USBH_MSC_CBWData.field.CBWCB[5]  = (((uint8_t*)&address)[0]);

                /*USBH_MSC_PAGE_LENGTH = 512*/
                nbOfPages = nbOfbytes/ USBH_MSC_PAGE_LENGTH;  

                /*Transfer length */
                USBH_MSC_CBWData.field.CBWCB[7]  = (((uint8_t *)&nbOfPages)[1]) ; 
                USBH_MSC_CBWData.field.CBWCB[8]  = (((uint8_t *)&nbOfPages)[0]) ; 


                USBH_MSC_BOTXferParam.BOTState = USBH_MSC_SEND_CBW;
                /* Start the transfer, then let the state machine 
                manage the other transactions */
                USBH_MSC_BOTXferParam.MSCState = USBH_MSC_BOT_USB_TRANSFERS;
                USBH_MSC_BOTXferParam.BOTXferStatus = USBH_MSC_BUSY;
                USBH_MSC_BOTXferParam.CmdStateMachine = CMD_WAIT_STATUS;

                status = USBH_MSC_BUSY;

                break;

            case CMD_WAIT_STATUS:
                if((USBH_MSC_BOTXferParam.BOTXferStatus == USBH_MSC_OK) && (HOST_IsDeviceConnected(pdev)))
                { 
                    /* Commands successfully sent and Response Received  */       
                    USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
                    status = USBH_MSC_OK;      
                }
                else if ((USBH_MSC_BOTXferParam.BOTXferStatus == USBH_MSC_FAIL ) && (HOST_IsDeviceConnected(pdev)))
                {
                    /* Failure Mode */
                    USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
                }
                else if ( USBH_MSC_BOTXferParam.BOTXferStatus == USBH_MSC_PHASE_ERROR )
                {
                    /* Failure Mode */
                    USBH_MSC_BOTXferParam.CmdStateMachine = CMD_SEND_STATE;
                    status = USBH_MSC_PHASE_ERROR;    
                }
                else
                {
                    /* Wait for the Commands to get Completed */
                    /* NO Change in state Machine */
                }
                break;

            default:
                break;
        }
    }
    return status;
}
