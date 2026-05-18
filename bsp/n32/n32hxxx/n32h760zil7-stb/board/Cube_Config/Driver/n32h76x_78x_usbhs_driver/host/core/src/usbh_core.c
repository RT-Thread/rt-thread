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
 * @file usbh_core.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "usbh_ioreq.h"
#include "usbhs_bsp.h"
#include "usbh_hcs.h"
#include "usbh_stdreq.h"
#include "usbh_core.h"
#include "usbhs_hcd_int.h"
#include "usbhs_hcd.h"
#include "n32h76x_78x_gpio.h"
#include "n32h76x_78x_pwr.h"
#include "n32h76x_78x_dbg.h"

uint8_t USBH_Disconnected (USB_CORE_MODULE *USBx); 
uint8_t USBH_Connected (USB_CORE_MODULE *USBx); 
uint8_t USBH_SOF (USB_CORE_MODULE *USBx); 
uint8_t USBH_PortEnabled (USB_CORE_MODULE *USBx); 
uint8_t USBH_PortDisabled (USB_CORE_MODULE *USBx); 

USBHOST_INT_cb_TypeDef USBHOST_INT_cb = 
{
    USBH_SOF,
    USBH_Connected, 
    USBH_Disconnected,
    USBH_PortEnabled,
    USBH_PortDisabled
};

USBHOST_INT_cb_TypeDef  *USBHOST_INT_fops = &USBHOST_INT_cb;

__IO uint32_t suspend_flag = 0;

static USBH_Status USBH_HandleEnum(USB_CORE_MODULE *USBx, USBH_HOST *host);
USBH_Status USBH_HandleControl(USB_CORE_MODULE *USBx, USBH_HOST *host);

void USB_BSP_Resume(USB_CORE_MODULE *USBx);                                                                 
void USB_BSP_Suspend(USB_CORE_MODULE *USBx);

/**
*\*\name    USBH_Connected.
*\*\fun     USB Connect callback function from the Interrupt. 
*\*\param   USBx: selected device.
*\*\return  Status.
*\*\
**/
uint8_t USBH_Connected(USB_CORE_MODULE *USBx)
{
    USBx->host.ConnSts = 1;
    return 0;
}

/**
*\*\name    USBH_Connected.
*\*\fun     USB Port Enable function. 
*\*\param   USBx: selected device.
*\*\return  Status.
*\*\
**/
uint8_t USBH_PortEnabled(USB_CORE_MODULE *USBx)
{
    USBx->host.PortEnabled = 1;
    return 0;
}

/**
*\*\name    USBH_PortDisabled.
*\*\fun     USB Port Disable function.
*\*\param   USBx: selected device.
*\*\return  Status.
*\*\
**/
uint8_t USBH_PortDisabled(USB_CORE_MODULE *USBx)
{
    USBx->host.PortEnabled = 0;
    return 0;
}

/**
*\*\name    USBH_Disconnected.
*\*\fun     USB Disconnect callback function from the Interrupt.
*\*\param   USBx: selected device.
*\*\return  Status.
*\*\
**/
uint8_t USBH_Disconnected (USB_CORE_MODULE *USBx)
{
    USB_BSP_DriveVBUS(USBx,0);
    /* Disable all interrupts. */
    USB_WRITE_REG32(&USBx->regs.GCSR->GINTEN, 0);

    /* Clear any pending interrupts. */
    USB_WRITE_REG32(&USBx->regs.GCSR->GINTSTS, 0xFFFFFFFF);
    USB_EnableGlobalInt(USBx, DISABLE);
    USBx->host.ConnSts = 0;
    return 0;  
}

/**
*\*\name    USBH_SOF.
*\*\fun     USB SOF callback function from the Interrupt. 
*\*\param   USBx: selected device.
*\*\return  Status.
*\*\
**/
uint8_t USBH_SOF (USB_CORE_MODULE *USBx)
{
    /* This callback could be used to implement a scheduler process */
    return 0;  
}

/**
*\*\name    USBH_Init.
*\*\fun     Host hardware and stack initializations .
*\*\param   USBx: selected device.
*\*\param   class_cb: Class callback structure address.
*\*\param   user_cb: User callback structure address.
*\*\return  none.
*\*\
**/
void USBH_Init(USB_CORE_MODULE *USBx, USB_CORE_ID_TypeDef coreID, USBH_HOST *host, USBH_Class_cb_TypeDef *class_cb, USBH_User_cb_TypeDef *user_cb)
{
    /* Hardware Init */
    USB_BSP_Init();  

    /* Host de-initializations */
    USBH_DeInit(USBx, host);

    /*Register class and user callbacks */
    host->class_cb = class_cb;
    host->usr_cb = user_cb;  

    /* Start the USB core */
    USBHOST_CoreInit(USBx, coreID);

    /* Upon Init call usr call back */
    host->usr_cb->Init();

    /* Enable Interrupts */
    USB_BSP_EnableInterrupt(USBx, coreID);
}

/**
*\*\name    USBH_DeInit.
*\*\fun     Re-Initialize Host. 
*\*\param   USBx: selected device.
*\*\param   host: host state set.
*\*\return  status: USBH_Status.
*\*\
**/
USBH_Status USBH_DeInit(USB_CORE_MODULE *USBx, USBH_HOST *host)
{
    /* Software Init */
    host->gState = HOST_IDLE;
    host->gStateBkp = HOST_IDLE; 
    host->EnumState = ENUM_IDLE;
    host->RequestState = CMD_SEND;  

    host->Control.state = CTRL_SETUP;
    host->Control.ep0size = USB_MAX_EP0_SIZE;  

    host->device_prop.address = USBH_DEVICE_ADDRESS_DEFAULT;
    host->device_prop.speed = HPCS_PRTSPD_FULL_SPEED;

    USBH_Free_Channel(USBx, host->Control.hch_num_in);
    USBH_Free_Channel(USBx, host->Control.hch_num_out);  
    return USBH_OK;
}

/**
*\*\name    USBH_Main_Process.
*\*\fun     USB Host core main state machine process 
*\*\param   USBx: selected device.
*\*\param   host: host state set.
*\*\return  none.
*\*\
**/
void USBH_Main_Process(USB_CORE_MODULE *USBx, USB_CORE_ID_TypeDef coreID, USBH_HOST *host)
{
    volatile USBH_Status status = USBH_FAIL;

    /* check for Host port events */
    if(((HOST_IsDeviceConnected(USBx) == 0) || (HOST_IsPortEnabled(USBx) == 0)) && (host->gState != HOST_IDLE)) 
    {
        if(host->gState != HOST_DEV_DISCONNECTED) 
        {
            host->gState = HOST_DEV_DISCONNECTED;
        }
    }

    switch (host->gState)
    {
        case HOST_IDLE:
            if (HOST_IsDeviceConnected(USBx))  
            {
                host->gState = HOST_WAIT_PRT_ENABLED; 

                /*wait denounce delay */
                USB_BSP_mDelay(100);

                /* Apply a port RESET */
                HOST_ResetPort(USBx);

                /* User RESET callback*/
                host->usr_cb->ResetDevice();
            }
        break;

        case HOST_WAIT_PRT_ENABLED:
            if (USBx->host.PortEnabled == 1)
            { 
                host->gState = HOST_DEV_ATTACHED; 
                USB_BSP_mDelay(50);
            }
        break;
          
        case HOST_DEV_ATTACHED :
            host->usr_cb->DeviceAttached();
            host->Control.hch_num_out = USBH_Alloc_Channel(USBx, 0x00);
            host->Control.hch_num_in = USBH_Alloc_Channel(USBx, 0x80);

            /* Reset USB Device */
            if ( HOST_ResetPort(USBx) == 0)
            {
                host->usr_cb->ResetDevice();

                /* Host is Now ready to start the Enumeration */
                host->device_prop.speed = HOST_GetCurrentSpeed(USBx);

                host->gState = HOST_ENUMERATION;
                host->usr_cb->DeviceSpeedDetected(host->device_prop.speed);

                /* Open Control pipes */
                USBH_Open_Channel (USBx,
                                 host->Control.hch_num_in,
                                 host->device_prop.address,
                                 host->device_prop.speed,
                                 EP_TYPE_CTRL,
                                 host->Control.ep0size); 

                /* Open Control pipes */
                USBH_Open_Channel (USBx,
                                 host->Control.hch_num_out,
                                 host->device_prop.address,
                                 host->device_prop.speed,
                                 EP_TYPE_CTRL,
                                 host->Control.ep0size);
            }
        break;

        case HOST_ENUMERATION:     
            /* Check for enumeration status */  
            if (USBH_HandleEnum(USBx , host) == USBH_OK)
            { 
                  /* The function shall return USBH_OK when full enumeration is complete */
                  
                  /* user callback for end of device basic enumeration */
                  host->usr_cb->EnumerationDone();
                  host->gState  = HOST_USR_INPUT;
            }
        break;

        case HOST_USR_INPUT:
            /*The function should return user response true to move to class state */
            if ( host->usr_cb->UserInput() == USBH_USER_RESP_OK)
            {
                if((host->class_cb->Init(USBx, host)) == USBH_OK)
                {
                    host->gState  = HOST_CLASS_REQUEST;
                }
            }   
        break;

        case HOST_CLASS_REQUEST:  
            /* process class standard control requests state machine */ 
            status = host->class_cb->Requests(USBx, host);

            if(status == USBH_OK)
            {
                host->gState  = HOST_CLASS;
            }  
            else
            {
                USBH_ErrorHandle(host, status);
            }
        break;
        case HOST_CLASS:   
            /* process class state machine */
            status = host->class_cb->Machine(USBx, host);
            USBH_ErrorHandle(host, status);
        break;

        case HOST_CTRL_XFER:
            /* process control transfer state machine */
            USBH_HandleControl(USBx, host);    
        break;
        case HOST_ERROR_STATE:
            /* Re-Initialize Host for new Enumeration */
            USBH_DeInit(USBx, host);
            host->usr_cb->DeInit();
            host->class_cb->DeInit(USBx, &host->device_prop);
        break;

        case HOST_DEV_DISCONNECTED :
            /* Manage User disconnect operations*/
            host->usr_cb->DeviceDisconnected();

            /* Re-Initialize Host for new Enumeration */
            USBH_DeInit(USBx, host);
            host->usr_cb->DeInit();
            host->class_cb->DeInit(USBx, &host->device_prop); 
            USBH_DeAllocate_AllChannel(USBx);  
            host->gState = HOST_IDLE;

            /* Re-Initialize Host for new Enumeration */
            USBHOST_CoreInit(USBx, coreID);
        break;

        default :
        break;
    }

}

/**
*\*\name    USBH_ErrorHandle.
*\*\fun     This function handles the Error on Host side.
*\*\param   host: host state set.
*\*\param   errType : Type of Error or Busy/OK state
*\*\return  none.
*\*\
**/
void USBH_ErrorHandle(USBH_HOST *host, USBH_Status errType)
{
    /* Error unrecovered or not supported device speed */
    if ( (errType == USBH_ERROR_SPEED_UNKNOWN) || (errType == USBH_UNRECOVERED_ERROR) )
    {
        host->usr_cb->UnrecoveredError(); 
        host->gState = HOST_ERROR_STATE;   
    }  
    /* USB host restart requested from application layer */
    else if(errType == USBH_APPLY_DEINIT)
    {
        host->gState = HOST_ERROR_STATE;  
        /* user callback for initialization */
        host->usr_cb->Init();
    } 
}

/**
*\*\name    USBH_HandleEnum.
*\*\fun     This function includes the complete enumeration process.
*\*\param   USBx: selected device.
*\*\param   host: host state set.
*\*\return  status: USBH_Status.
*\*\
**/
static USBH_Status USBH_HandleEnum(USB_CORE_MODULE *USBx, USBH_HOST *host)
{
    USBH_Status Status = USBH_BUSY;  
    uint8_t Local_Buffer[64];

    switch (host->EnumState)
    {
        case ENUM_IDLE:  
            /* Get Device Desc for only 1st 8 bytes : To get EP0 MaxPacketSize */
            if( USBH_Get_DevDesc(USBx , host, 8) == USBH_OK)
            {
                host->Control.ep0size = host->device_prop.Dev_Desc.bMaxPacketSize;

                host->EnumState = ENUM_GET_FULL_DEV_DESC;

                /* modify control channels configuration for MaxPacket size */
                USBH_Modify_Channel (USBx, host->Control.hch_num_out, 0, 0, 0, host->Control.ep0size);
                USBH_Modify_Channel (USBx, host->Control.hch_num_in, 0, 0, 0, host->Control.ep0size);
            }
        break;

        case ENUM_GET_FULL_DEV_DESC:  
            /* Get FULL Device Desc  */
            if( USBH_Get_DevDesc(USBx, host, USB_DEVICE_DESC_SIZE) == USBH_OK)
            {
                /* user callback for device descriptor available */
                host->usr_cb->DeviceDescAvailable(&host->device_prop.Dev_Desc);      
                host->EnumState = ENUM_SET_ADDR;
            }
        break;

        case ENUM_SET_ADDR: 
            /* set address */
            if( USBH_SetAddress(USBx, host, USBH_DEVICE_ADDRESS) == USBH_OK)
            {
                USB_BSP_mDelay(2);
                host->device_prop.address = USBH_DEVICE_ADDRESS;

                /* user callback for device address assigned */
                host->usr_cb->DeviceAddressAssigned();
                host->EnumState = ENUM_GET_CFG_DESC;

                /* modify control channels to update device address */
                USBH_Modify_Channel (USBx, host->Control.hch_num_in, host->device_prop.address, 0, 0, 0);
                USBH_Modify_Channel (USBx, host->Control.hch_num_out, host->device_prop.address, 0, 0, 0);
            }
        break;

        case ENUM_GET_CFG_DESC:  
            /* get standard configuration descriptor */
            if( USBH_Get_CfgDesc(USBx, host, USB_CONFIGURATION_DESC_SIZE) == USBH_OK)
            {
                /* before getting full config descriptor, check if it does not exceed 
                buffer size allocated to config descriptor USBH_MAX_DATA_BUFFER
                in the usbh_conf.h*/
                if (host->device_prop.Cfg_Desc.wTotalLength <= USBH_MAX_DATA_BUFFER)
                {
                    host->EnumState = ENUM_GET_FULL_CFG_DESC;
                }
            }
        break;

        case ENUM_GET_FULL_CFG_DESC:  
            /* get FULL config descriptor (config, interface, endpoints) */
            if(USBH_Get_CfgDesc(USBx, host, host->device_prop.Cfg_Desc.wTotalLength) == USBH_OK)
            {
                /* User callback for configuration descriptors available */
                host->usr_cb->ConfigurationDescAvailable(&host->device_prop.Cfg_Desc, host->device_prop.Itf_Desc, host->device_prop.Ep_Desc[0]);
              
                host->EnumState = ENUM_GET_MFC_STRING_DESC;
            }
        break;

        case ENUM_GET_MFC_STRING_DESC:  
            if(host->device_prop.Dev_Desc.iManufacturer != 0)
            { /* Check that Manufacturer String is available */
              
                if ( USBH_Get_StringDesc(USBx, host, host->device_prop.Dev_Desc.iManufacturer, Local_Buffer, 0xff) == USBH_OK)
                {
                    /* User callback for Manufacturing string */
                    host->usr_cb->ManufacturerString(Local_Buffer);
                    host->EnumState = ENUM_GET_PRODUCT_STRING_DESC;
                }
            }
            else
            {
                host->usr_cb->ManufacturerString("N/A");
                host->EnumState = ENUM_GET_PRODUCT_STRING_DESC;
            }
        break;

        case ENUM_GET_PRODUCT_STRING_DESC:   
            if(host->device_prop.Dev_Desc.iProduct != 0)
            { /* Check that Product string is available */
                if(USBH_Get_StringDesc(USBx, host, host->device_prop.Dev_Desc.iProduct, Local_Buffer, 0xff) == USBH_OK)
                {
                    /* User callback for Product string */
                    host->usr_cb->ProductString(Local_Buffer);
                    host->EnumState = ENUM_GET_SERIALNUM_STRING_DESC;
                }
            }
        else
        {
            host->usr_cb->ProductString("N/A");
            host->EnumState = ENUM_GET_SERIALNUM_STRING_DESC;
        } 
        break;

        case ENUM_GET_SERIALNUM_STRING_DESC:   
            if(host->device_prop.Dev_Desc.iSerialNumber != 0)
            { /* Check that Serial number string is available */    
                if(USBH_Get_StringDesc(USBx, host, host->device_prop.Dev_Desc.iSerialNumber, Local_Buffer, 0xff) == USBH_OK)
                {
                    /* User callback for Serial number string */
                    host->usr_cb->SerialNumString(Local_Buffer);
                    host->EnumState = ENUM_SET_CONFIGURATION;
                }
            }
            else
            {
                host->usr_cb->SerialNumString("N/A");
                host->EnumState = ENUM_SET_CONFIGURATION;
            }  
        break;
          
        case ENUM_SET_CONFIGURATION:
            /* set configuration  (default config) */
            if(USBH_SetCfg(USBx, host, host->device_prop.Cfg_Desc.bConfigurationValue) == USBH_OK)
            {
                host->EnumState = ENUM_DEV_CONFIGURED;
            }
        break;


        case ENUM_DEV_CONFIGURED:
            /* user callback for enumeration done */
            Status = USBH_OK;
        break;

        default:
        break;
    }  
    return Status;
}

/**
*\*\name    USBH_HandleControl.
*\*\fun     Handles the USB control transfer state machine.
*\*\param   USBx: selected device.
*\*\param   host: host state set.
*\*\return  status: USBH_Status.
*\*\
**/
USBH_Status USBH_HandleControl(USB_CORE_MODULE *USBx, USBH_HOST *host)
{
    uint8_t direction;  
    static uint16_t timeout = 0;
    USBH_Status status = USBH_OK;
    URB_STATE URB_Status = URB_IDLE;

    host->Control.status = CTRL_START;

    switch(host->Control.state)
    {
        case CTRL_SETUP:
            /* send a SETUP packet */
            USBH_CtrlSendSetup(USBx, host->Control.setup.d8, host->Control.hch_num_out);  
            host->Control.state = CTRL_SETUP_WAIT;  
        break; 

        case CTRL_SETUP_WAIT:

            URB_Status = HOST_GetURB_State(USBx, host->Control.hch_num_out); 
            /* case SETUP packet sent successfully */
            if(URB_Status == URB_DONE)
            { 
                direction = (host->Control.setup.b.bmRequestType & USB_REQ_DIR_MASK);

                /* check if there is a data stage */
                if(host->Control.setup.b.wLength.w != 0 )
                {        
                    timeout = DATA_STAGE_TIMEOUT;
                    if(direction == USB_D2H)
                    {
                        /* Data Direction is IN */
                        host->Control.state = CTRL_DATA_IN;
                    }
                    else
                    {
                        /* Data Direction is OUT */
                        host->Control.state = CTRL_DATA_OUT;
                    } 
                }
                /* No DATA stage */
                else
                {
                    timeout = NODATA_STAGE_TIMEOUT;
                    /* If there is No Data Transfer Stage */
                    if (direction == USB_D2H)
                    {
                        /* Data Direction is IN */
                        host->Control.state = CTRL_STATUS_OUT;
                    }
                    else
                    {
                        /* Data Direction is OUT */
                        host->Control.state = CTRL_STATUS_IN;
                    } 
                }          
                /* Set the delay timer to enable timeout for data stage completion */
                host->Control.timer = HOST_GetCurrentFrame(USBx);
            }
            else if(URB_Status == URB_ERROR)
            {
                host->Control.state = CTRL_ERROR;
                host->Control.status = CTRL_XACTERR;
            }    
        break;

        case CTRL_DATA_IN:  
            /* Issue an IN token */ 
            USBH_CtrlReceiveData(USBx, host->Control.buff, host->Control.length, host->Control.hch_num_in);

            host->Control.state = CTRL_DATA_IN_WAIT;
        break;    

        case CTRL_DATA_IN_WAIT:

            URB_Status = HOST_GetURB_State(USBx , host->Control.hch_num_in); 

            /* check is DATA packet transferred successfully */
            if (URB_Status == URB_DONE)
            { 
                host->Control.state = CTRL_STATUS_OUT;
            }

            /* manage error cases*/
            if (URB_Status == URB_STALL) 
            { 
                /* In stall case, return to previous machine state*/
                host->gState =   host->gStateBkp;
                host->Control.state = CTRL_STALLED;  
            }   
            else if (URB_Status == URB_ERROR)
            {
                /* Device error */
                host->Control.state = CTRL_ERROR;    
            }
            else if ((HOST_GetCurrentFrame(USBx)- host->Control.timer) > timeout)
            {
                /* timeout for IN transfer */
                host->Control.state = CTRL_ERROR; 
            }   
        break;

        case CTRL_DATA_OUT:
            /* Start DATA out transfer (only one DATA packet)*/
            USBx->host.hch[host->Control.hch_num_out].toggle_out = 1; 
                
            USBH_CtrlSendData (USBx, host->Control.buff, host->Control.length, host->Control.hch_num_out);

            host->Control.state = CTRL_DATA_OUT_WAIT;
        break;

        case CTRL_DATA_OUT_WAIT:

            URB_Status = HOST_GetURB_State(USBx , host->Control.hch_num_out);     
            if(URB_Status == URB_DONE)
            { /* If the Setup Pkt is sent successful, then change the state */
                host->Control.state = CTRL_STATUS_IN;
            }
            /* handle error cases */
            else if(URB_Status == URB_STALL) 
            { 
                /* In stall case, return to previous machine state*/
                host->gState =   host->gStateBkp;
                host->Control.state = CTRL_STALLED;  
            } 
            else if(URB_Status == URB_NOTREADY)
            { 
                /* Nack received from device */
                host->Control.state = CTRL_DATA_OUT;
            }    
            else if(URB_Status == URB_ERROR)
            {
                /* device error */
                host->Control.state = CTRL_ERROR;      
            } 
        break;


        case CTRL_STATUS_IN:
            /* Send 0 bytes out packet */
            USBH_CtrlReceiveData(USBx, 0, 0,host->Control.hch_num_in);
            host->Control.state = CTRL_STATUS_IN_WAIT;
        break;

        case CTRL_STATUS_IN_WAIT:
            URB_Status = HOST_GetURB_State(USBx , host->Control.hch_num_in); 
            if(URB_Status == URB_DONE)
            {   /* Control transfers completed, Exit the State Machine */
                host->gState =   host->gStateBkp;
                host->Control.state = CTRL_COMPLETE;
            }
            else if(URB_Status == URB_ERROR)
            {
                host->Control.state = CTRL_ERROR;  
            }
            else if((HOST_GetCurrentFrame(USBx) - host->Control.timer) > timeout)
            {
                host->Control.state = CTRL_ERROR; 
            }
            else if(URB_Status == URB_STALL)
            {
                /* Control transfers completed, Exit the State Machine */
                host->gState =   host->gStateBkp;
                host->Control.state = CTRL_STALLED;
                status = USBH_NOT_SUPPORTED;
            }
        break;

        case CTRL_STATUS_OUT:
            USBx->host.hch[host->Control.hch_num_out].toggle_out ^= 1; 
            USBH_CtrlSendData(USBx, 0, 0, host->Control.hch_num_out);

            host->Control.state = CTRL_STATUS_OUT_WAIT;
        break;

        case CTRL_STATUS_OUT_WAIT: 

            URB_Status = HOST_GetURB_State(USBx , host->Control.hch_num_out);  
            if(URB_Status == URB_DONE)
            { 
                host->gState =   host->gStateBkp; 
                host->Control.state = CTRL_COMPLETE; 
            }
            else if(URB_Status == URB_NOTREADY)
            { 
                host->Control.state = CTRL_STATUS_OUT;
            }      
            else if(URB_Status == URB_ERROR)
            {
                host->Control.state = CTRL_ERROR;      
            }
        break;

        case CTRL_ERROR:
        /* 
        After a halt condition is encountered or an error is detected by the 
        host, a control endpoint is allowed to recover by accepting the next Setup 
        PID; i.e., recovery actions via some other pipe are not required for control
        endpoints. For the Default Control Pipe, a device reset will ultimately be 
        required to clear the halt or error condition if the next Setup PID is not 
        accepted.
        */
        if(++host->Control.errorcount <= USBH_MAX_ERROR_COUNT)
        {
            /* Do the transmission again, starting from SETUP Packet */
            host->Control.state = CTRL_SETUP; 
        }
        else
        {
            host->Control.status = CTRL_FAIL;
            host->gState =   host->gStateBkp;
          
            status = USBH_FAIL;
        }
        break;

        default:
        break;
    }
    return status;
}

/**
*\*\name    USB_BSP_Resume.
*\*\fun     Handles the USB Resume from Suspend Mode.
*\*\param   USBx: selected device.
*\*\return  none.
*\*\
**/
void USB_BSP_Resume(USB_CORE_MODULE *USBx)                                                                 
{
    uint32_t hpcs = 0;

    /*  switch-off the clocks */
    USB_CLR_REG32_BIT(USBx->regs.PWRCTRL, USBHS_PWRCTRL_PHYSTP);
    
    hpcs = USB_ReadHPCS(USBx);
    hpcs &= (~USBHS_HPCS_PSUSP); 
    hpcs |= USBHS_HPCS_PRES;
    USB_WRITE_REG32(USBx->regs.HPCS, hpcs);
    USB_BSP_mDelay (20);

    hpcs &= (~USBHS_HPCS_PRES);
    USB_WRITE_REG32(USBx->regs.HPCS, hpcs); 
}

/**
*\*\name    USB_BSP_Suspend.
*\*\fun     Handles the Enter USB to Suspend Mode.
*\*\param   USBx: selected device.
*\*\return  none.
*\*\
**/
void USB_BSP_Suspend(USB_CORE_MODULE *USBx)
{
    uint32_t hpcs;

    hpcs  = USB_ReadHPCS(USBx);
    hpcs |= USBHS_HPCS_PSUSP;
    USB_WRITE_REG32(USBx->regs.HPCS, hpcs);

    /*  switch-off the clocks */
    USB_SET_REG32_BIT(USBx->regs.PWRCTRL, USBHS_PWRCTRL_PHYSTP);
}
