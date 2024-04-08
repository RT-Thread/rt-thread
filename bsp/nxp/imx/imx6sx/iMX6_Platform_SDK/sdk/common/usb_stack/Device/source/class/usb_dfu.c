/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 ******************************************************************************
 *
 * THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************//*!
 *
 * @file usb_dfu.c
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief The file contains USB stack DFU layer implementation.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_dfu.h"          /* USB DFU Class Header File */
#include "usb_devapi.h"       /* USB device Header File */
#include "RealTimerCounter.h" /* USB RTC Header File */

/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/

/****************************************************************************
 * Global Variables
 ****************************************************************************/

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/


/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
void USB_Class_DFU_Periodic_Task(void);
void USB_Class_DFU_set_bwPoll_TimeOut(uint_32 timeout );
static void USB_Class_DFU_Process_bwPoll_TimeOut(void);
static uint_8 USB_Class_DFU_Getstatus    
(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
static uint_8 USB_Class_DFU_Getstate 
(
    uint_8 controller_ID,               
    uint_8 interface,                   
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
static uint_8 USB_Other_Requests
(
    uint_8 controller_ID,              
    USB_SETUP_STRUCT * setup_packet,   
    uint_8_ptr *data,                  
    USB_PACKET_SIZE *size);            
    
static uint_8 DFU_App_Detach_State
(
    uint_8 controller_ID,               
    USB_SETUP_STRUCT * setup_packet,    
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
static uint_8 DFU_Idle_State
(
    uint_8 controller_ID,              
    USB_SETUP_STRUCT * setup_packet,   
    uint_8_ptr *data,                  
    USB_PACKET_SIZE *size              
);
static uint_8 DFU_Dnload_Sync_State
(
    uint_8 controller_ID,              
    USB_SETUP_STRUCT * setup_packet,   
    uint_8_ptr *data,                  
    USB_PACKET_SIZE *size              
);
static uint_8 DFU_Dnbusy_State
(
    uint_8 controller_ID,              
    USB_SETUP_STRUCT * setup_packet,   
    uint_8_ptr *data,                  
    USB_PACKET_SIZE *size              
);
static uint_8 DFU_Dnload_Idle_State
(
    uint_8 controller_ID,              
    USB_SETUP_STRUCT * setup_packet,   
    uint_8_ptr *data,                  
    USB_PACKET_SIZE *size              
);
static uint_8 DFU_Manifest_Sync_State
(
    uint_8 controller_ID,              
    USB_SETUP_STRUCT * setup_packet,   
    uint_8_ptr *data,                  
    USB_PACKET_SIZE *size              
);
static uint_8 DFU_Manifest_State
(
    uint_8 controller_ID,              
    USB_SETUP_STRUCT * setup_packet,    
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size              
);
static uint_8 DFU_Manifest_Wait_Reset_State
(
    uint_8 controller_ID,               
    USB_SETUP_STRUCT * setup_packet,    
    uint_8_ptr *data,                   
    USB_PACKET_SIZE *size               
);
static uint_8 DFU_Upload_Idle_State
(
    uint_8 controller_ID,              
    USB_SETUP_STRUCT * setup_packet,   
    uint_8_ptr *data,                  
    USB_PACKET_SIZE *size              
);
static uint_8 DFU_Error_State
(
    uint_8 controller_ID,              
    USB_SETUP_STRUCT * setup_packet,   
    uint_8_ptr *data,                  
    USB_PACKET_SIZE *size              
);
/*****************************************************************************
 * Local Variables
 *****************************************************************************/
/* DFU Class Callback Function Pointer */
static USB_CLASS_CALLBACK g_dfu_class_callback=NULL;
/* DFU Class Vendor Callback Function Pointer */
static USB_REQ_FUNC       g_vendor_req_callback=NULL;
/* DFU Class requests Callback Function Pointer */
static USB_CLASS_SPECIFIC_HANDLER_FUNC g_param_callback = NULL;
/* state of DFU device */
static uint_8 g_state;
/* status of DFU device */
static uint_8 g_status[GETSTATUS_DATA_SIZE] = {0x00,POLLTIMEOUT,0x00,0x00,0x00,0x00};
/* length of data */
#if defined(_MC9S08JS16_H)
static uint_8 wlength;
#else
static uint_16 wlength;
#endif
/* Flag to check Poll Timeout occur or not */
static boolean Flag_bwPoll_TimeOut = FALSE;
/* Flag to check download block process complete or not */
static boolean Flag_Block_Complete = FALSE;
/* Flag to check manifest phase complete or not */
static boolean Flag_Manifest_Complete = FALSE;
/* Poll Timeout */
static TIMER_OBJECT bwPoll_TimeOut;
/*****************************************************************************
 * Local Functions
 *****************************************************************************/
/**************************************************************************//*!
 *
 * @name  USB_Class_DFU_Set_bwPoll_TimeOut
 *
 * @brief  To set timeout of block download process and manifest phase
 *
 *
 * @return :  None
 *
 ******************************************************************************
 *
 *****************************************************************************/
void USB_Class_DFU_set_bwPoll_TimeOut(uint_32 app_timeout )
{
      g_status[BWPOLLTIMEOUT] = (uint_8)((app_timeout)&(0xFF));
      g_status[BWPOLLTIMEOUT+1] = (uint_8)((app_timeout>>8)&(0xFF));
      g_status[BWPOLLTIMEOUT+2] = (uint_8)((app_timeout>>24)&(0xFF));
}
/**************************************************************************//*!
 *
 * @name  USB_Class_DFU_Process_bwPoll_TimeOut
 *
 * @brief  To check timeout of block download process and manifest phase
 *
 *
 * @return :  None
 *
 ******************************************************************************
 *
 *****************************************************************************/
static void USB_Class_DFU_Process_bwPoll_TimeOut()
{
    Flag_bwPoll_TimeOut = TRUE;
    if (g_state == USB_DFU_DNBUSY)
        g_state = USB_DFU_DNLOAD_SYNC;
    if (g_state == USB_DFU_MANIFEST)
    {
#if(MANIFESTATION)
        g_state = USB_DFU_MANIFEST_SYNC;
#else
        g_state = USB_DFU_MANIFEST_WAIT_RESET;
#endif
    }
}
/**************************************************************************//*!
 *
 * @name  USB_Class_DFU_App_SetIdle
 *
 * @brief  This function is called to set device state is Idle
 *
 *
 * @return : status
 *                        USB_OK        : When Successfull
 *                        Others        : When Error
 *****************************************************************************/

void USB_Class_DFU_App_SetIdle(void) 
{
  g_state = USB_APP_IDLE;
}
/**************************************************************************//*!
 *
 * @name  USB_Class_DFU_App_SetDetach
 *
 * @brief  This function is called to set device state is Detach
 *
 *
 * @return : status
 *                        USB_OK        : When Successful
 *                        Others        : When Error
 ******************************************************************************/
void USB_Class_DFU_App_SetDetach(void) 
 {
   g_state = USB_APP_DETACH;
 }    
/**************************************************************************//*!
 *
 * @name  USB_Class_DFU_App_Getstate
 *
 * @brief  This function is called by App layer to get state from DFU class
 *
 *
 * @return :  state of device
 *
 *****************************************************************************/
 
uint_8 USB_Class_DFU_App_Getstate(void) 
{
  return g_state;
}
/**************************************************************************//*!
 *
 * @name  USB_Class_DFU_App_Setstate
 *
 * @brief  This function is called when detect USB reset signal
 *
 *
 * @return status:
 *                        USB_OK        : When Successful
 *                        Others        : When Error
 *
 *****************************************************************************/
void USB_Class_DFU_App_Set_Usbreset(void)
{ 
switch(g_state) 
  {
    case USB_APP_DETACH:
      g_state = USB_DFU_IDLE;
      break;
    default:
      if(!Flag_Manifest_Complete) 
      { 
        g_state = USB_DFU_ERROR;
      }
      break;
  }
}
/**************************************************************************//*!
 *
 * @name  USB_Class_DFU_App_Set_Flag_Manifest
 *
 * @brief  This function is called when app layer need set Flag to inform 
 *
 * completed manifest phase
 *
 * @return status:
 *                        USB_OK        : When Successful
 *                        Others        : When Error
 *
 *****************************************************************************/
void USB_Class_DFU_App_Set_Flag_Manifest(void)
{
  Flag_Manifest_Complete = TRUE;
}
/**************************************************************************//*!
 *
 * @name  USB_Class_DFU_App_Reset_Flag_Manifest
 *
 * @brief  This function is called when app layer need set Flag to inform 
 *
 * completed manifest phase
 *
 * @return status:
 *                        USB_OK        : When Successful
 *                        Others        : When Error
 *
 *****************************************************************************/
void USB_Class_DFU_App_Reset_Flag_Manifest(void)
{
  Flag_Manifest_Complete = FALSE;
}
/**************************************************************************//*!
 *
 * @name  USB_Class_DFU_App_Set_Flag_Manifest
 *
 * @brief  This function is called when app layer need set Flag to inform 
 *
 * completed manifest phase
 *
 * @return status:
 *                        USB_OK        : When Successful
 *                        Others        : When Error
 *
 *****************************************************************************/
boolean USB_Class_DFU_App_Get_Flag_Manifest(void)
{
  return Flag_Manifest_Complete;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_DFU_Getstatus
 *
 * @brief   The funtion gets status of device and generate timeout for
 *          transition between phases.
 *
 * @param controller_ID     : Controller ID
 * @param interface         : Interface
 * @param data              : Pointer to data
 * @param size              : Pointer to size of data
 *
 * @return status:
 *                        USB_OK        : When Successful
 *                        USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Return status of device
 *****************************************************************************/
static uint_8 USB_Class_DFU_Getstatus (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
    UNUSED(controller_ID)
    /* if interface valid */
    if (interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* get status data*/
        *size = GETSTATUS_DATA_SIZE;
        *data = g_status;
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_DFU_Getstate
 *
 * @brief   The funtion gets state of device
 *
 * @param controller_ID     : Controller ID
 * @param interface         : Interface
 * @param data              : Pointer to data
 * @param size              : Pointer to size of Data
 *
 * @return status:
 *                        USB_OK        : When Successful
 *                        USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Return state of device.
 *****************************************************************************/
static uint_8 USB_Class_DFU_Getstate (
    uint_8 controller_ID,               /* [IN] Controller ID */
    uint_8 interface,                   /* [IN] Interface */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
    UNUSED(controller_ID)
    /* if interface valid */
    if (interface < USB_MAX_SUPPORTED_INTERFACES)
    {
        /* get state data*/
        *size = GETSTATE_DATA_SIZE;
        *data = &g_state;
        return USB_OK;
    }
    return USBERR_INVALID_REQ_TYPE;
}

/**************************************************************************//*!
 *
 * @name  USB_Other_Requests
 *
 * @brief   The function provides flexibility to add class and vendor specific
 *              requests
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Setup packet received
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *                        USB_OK        : When Successful
 *                        Others        : When Error
 *
 ******************************************************************************
 * Handles DFU Class requests and forwards vendor specific request to the
 * application
 *****************************************************************************/
static uint_8 USB_Other_Requests (
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Setup packet received */
    uint_8_ptr *data,                   /* [OUT] Data to be send back */
    USB_PACKET_SIZE *size               /* [OUT] Size to be returned*/
)
{
    uint_8 status = USBERR_INVALID_REQ_TYPE;
    /* Check size NULL */
    if (size == NULL)
    {
        return USBERR_GET_MEMORY_FAILED;
    }
    *size = 0;
    if ((setup_packet->request_type & USB_REQUEST_CLASS_MASK) ==
            USB_REQUEST_CLASS_CLASS)
    {
    g_status[BSTATE] = g_state;
        switch (g_state)
        {
        /* State1: App_Detach */
        case USB_APP_DETACH:
            status = DFU_App_Detach_State(controller_ID, setup_packet, data, size) ;
            break;
        /* State2: Dfu_Idle */
        case USB_DFU_IDLE:
            status = DFU_Idle_State(controller_ID, setup_packet, data, size) ;
            break;
        /* State3: Dfu_Dnload_Sync */
        case USB_DFU_DNLOAD_SYNC:
            status = DFU_Dnload_Sync_State(controller_ID, setup_packet, data, size);
            break;
        /* State4: Dfu_Dnbusy */             
        case USB_DFU_DNBUSY:
            status = DFU_Dnbusy_State(controller_ID, setup_packet, data, size);
            break;
        /* State5: Dfu_Dnload_Idle*/
        case USB_DFU_DNLOAD_IDLE:
            status = DFU_Dnload_Idle_State(controller_ID, setup_packet, data, size);
            break;
        /* State6: Dfu_Mani_Sync */  
        case USB_DFU_MANIFEST_SYNC:
            status = DFU_Manifest_Sync_State(controller_ID, setup_packet, data, size);
            break;
        /* State7: Dfu_Mani */  
        case USB_DFU_MANIFEST:
            status = DFU_Manifest_State(controller_ID, setup_packet, data, size);
            break;
        /* State8: Dfu_Mani_Wait_Reset */  
        case USB_DFU_MANIFEST_WAIT_RESET:
           status = DFU_Manifest_Wait_Reset_State(controller_ID, setup_packet, data, size);
            break;
        /* State9: Dfu_Upload_Idle */  
        case USB_DFU_UPLOAD_IDLE:
            status = DFU_Upload_Idle_State(controller_ID, setup_packet, data, size);
            break;
        /* State10: Dfu_Error */
        case USB_DFU_ERROR:
            status = DFU_Error_State(controller_ID, setup_packet, data, size);
            break;
        default:
            status = USB_OK;
            break;
        }
    }
    g_status[BSTATUS] = status;
    return status;
}
/**************************************************************************//*!
 *
 * @name  DFU_App_Detach_State
 *
 * @brief   The function processes requests at USB_APP_DETACH  state
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Setup packet received
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *                        USB_OK        : When Successful
 *                        Others        : When Error
 *
 *****************************************************************************/
static uint_8 DFU_App_Detach_State
(
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Setup packet received */
    uint_8_ptr *data,                   /* [OUT] Data to be send back */
    USB_PACKET_SIZE *size               /* [OUT] Size to be returned*/
)
{
    uint_8 status;
    uint_8 interface;

    interface = (uint_8)setup_packet->index;
    switch (setup_packet->request)
    {
    /* DFU_GETSTATUS Request */
    case USB_DFU_GETSTATUS:
        status= USB_Class_DFU_Getstatus(controller_ID,interface,data,size);
        break;
    /* DFU_GETSTATE Request */    
    case USB_DFU_GETSTATE:
        status = USB_Class_DFU_Getstate(controller_ID,interface,data,size);
        break;
    default:
        status = USBERR_INVALID_REQ_TYPE;
        g_state = USB_APP_IDLE;
        break;
    }
    return status;
}

/**************************************************************************//*!
 *
 * @name  DFU_Idle_State
 *
 * @brief   The function processes requests at USB_DFU_IDLE state
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Setup packet received
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *                        USB_OK        : When Successful
 *                        Others        : When Error
 *
 *****************************************************************************/
static uint_8 DFU_Idle_State
(
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Setup packet received */
    uint_8_ptr *data,                   /* [OUT] Data to be send back */
    USB_PACKET_SIZE *size               /* [OUT] Size to be returned*/
)
{
    uint_8 status;
    uint_8 interface,BlockNum,wBlockNum,check_request_type;

    interface = (uint_8)setup_packet->index;
    BlockNum = (uint_8)setup_packet->value;
    wBlockNum = (uint_8)setup_packet->value;
    check_request_type =(uint_8)setup_packet->request_type;
    *data = ((uint_8*)setup_packet)+USB_SETUP_PKT_SIZE;
    switch (setup_packet->request)
    {
    /* DFU_DNLOAD request */
    case USB_DFU_DNLOAD:
        /* check wBlockNum */
        #if defined(_MC9S08JS16_H)
        wlength = (uint_8)setup_packet->length;
        #else
        wlength = setup_packet->length;
        #endif
        if (wlength>0)
        {
            (void)RemoveTimerQ(0);
#if(BITCANDOWNLOAD)
            /* Start check download timeout */
            g_state = USB_DFU_DNLOAD_SYNC;
            Flag_Block_Complete = FALSE;            
            /* Call to application */
            status = USB_Class_DFU_Dnload(controller_ID,wBlockNum,data,&wlength);
            if(USB_OK != status)
            {
            	g_state = USB_DFU_ERROR;
            }
#else
            status = USBERR_INVALID_REQ_TYPE;;
            g_state = USB_DFU_ERROR;
#endif
        }
        /* the last block */
        if (wlength == 0)
        {
            status = USBERR_INVALID_REQ_TYPE;;
            g_state = USB_DFU_ERROR;
        }
        break;
    /* DFU_UPLOAD request */
    case USB_DFU_UPLOAD:
#if(BITCANUPLOAD)
        BlockNum = (uint_8)setup_packet->value;
        /* Call to application */
        status = USB_Class_DFU_Upload(controller_ID,BlockNum,data,size,setup_packet->length);
		if (*size < setup_packet->length) g_state = USB_DFU_IDLE;
        else
        g_state = USB_DFU_UPLOAD_IDLE;
#else
        status = USBERR_INVALID_REQ_TYPE;
        g_state = USB_DFU_ERROR;
#endif
        break;
    /* DFU_ABORT request */
    case USB_DFU_ABORT:
        status = USB_OK;
        break;
    /* DFU_GETSTATUS request */
    case USB_DFU_GETSTATUS:
        status= USB_Class_DFU_Getstatus(controller_ID,interface,data,size);
        break;
    /* DFU_GETSTATE request */
    case USB_DFU_GETSTATE:
        status = USB_Class_DFU_Getstate(controller_ID,interface,data,size);
        break;
    default:
        status = USBERR_INVALID_REQ_TYPE;
        g_state = USB_DFU_ERROR;
        break;
    }
    return status;
}

/**************************************************************************//*!
 *
 * @name  DFU_Dnload_Sync_State
 *
 * @brief   The function processes requests at USB_DFU_DNLOAD_SYNC  state
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Setup packet received
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *                        USB_OK        : When Successful
 *                        Others        : When Error
 *
 *****************************************************************************/
static uint_8 DFU_Dnload_Sync_State
(
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Setup packet received */
    uint_8_ptr *data,                   /* [OUT] Data to be send back */
    USB_PACKET_SIZE *size               /* [OUT] Size to be returned*/
)
{
    uint_8 status;
    uint_8 interface;

    interface = (uint_8)setup_packet->index;
    switch (setup_packet->request)
    {
    /* DFU_GETSTATUS request */
    case USB_DFU_GETSTATUS:
        if (Flag_Block_Complete) 
        	g_state = USB_DFU_DNLOAD_IDLE;
        else
        {
        	/* Set time out for writing to flash*/
        	(void)RemoveTimerQ(0);
        	Flag_bwPoll_TimeOut = FALSE;
            Flag_Block_Complete = FALSE;
            if(g_status[BWPOLLTIMEOUT+2]>0)
            bwPoll_TimeOut.msCount = 0xFFFF; /* Max Poll Time Out */
            else
            bwPoll_TimeOut.msCount = (uint_16)(g_status[BWPOLLTIMEOUT]+(g_status[BWPOLLTIMEOUT+1] <<8));
            bwPoll_TimeOut.pfnTimerCallback = USB_Class_DFU_Process_bwPoll_TimeOut;
            (void)AddTimerQ(&bwPoll_TimeOut);
            
            g_state = USB_DFU_DNBUSY;       
        } 
        g_status[BSTATE] = g_state;
        status= USB_Class_DFU_Getstatus(controller_ID,interface,data,size);
        break;
    /* DFU_GETSTATE request */    
    case USB_DFU_GETSTATE:
        status = USB_Class_DFU_Getstate(controller_ID,interface,data,size);
        break;
    default:
        status = USBERR_INVALID_REQ_TYPE;
        g_state = USB_DFU_ERROR;
        break;
    }
    return status;
}
/**************************************************************************//*!
*
* @name  DFU_Dnbusy_State
*
* @brief   The function processes requests at USB_DFU_DNBUSY  state
*
* @param controller_ID     : Controller ID
* @param setup_packet      : Setup packet received
* @param data              : Data to be send back
* @param size              : Size to be returned
*
* @return status:
*                        USB_OK        : When Successful
*                        Others        : When Error
*
*****************************************************************************/
static uint_8 DFU_Dnbusy_State
(
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Setup packet received */
    uint_8_ptr *data,                   /* [OUT] Data to be send back */
    USB_PACKET_SIZE *size               /* [OUT] Size to be returned*/
)
{
	UNUSED (controller_ID)
	UNUSED (setup_packet)
	UNUSED (data)
	UNUSED (size)
    g_state = USB_DFU_ERROR;
    return USBERR_INVALID_REQ_TYPE;
}
/**************************************************************************//*!
 *
 * @name  DFU_Dnload_Idle_State
 *
 * @brief   The function processes requests at USB_DFU_DNLOAD_IDLE   state
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Setup packet received
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *                        USB_OK        : When Successful
 *                        Others        : When Error
 *
 *****************************************************************************/
static uint_8 DFU_Dnload_Idle_State
(
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Setup packet received */
    uint_8_ptr *data,                   /* [OUT] Data to be send back */
    USB_PACKET_SIZE *size               /* [OUT] Size to be returned*/
)
{
    uint_8 status;
    uint_8 interface,BlockNum,wBlockNum,check_request_type;

    interface = (uint_8)setup_packet->index;
    BlockNum = (uint_8)setup_packet->value;
    wBlockNum = (uint_8)setup_packet->value;
    check_request_type =(uint_8)setup_packet->request_type;
    *data = ((uint_8*)setup_packet)+USB_SETUP_PKT_SIZE;

    switch (setup_packet->request)
    {
    /* DFU_DNLOAD request*/
    case USB_DFU_DNLOAD:
    
	    #if defined(_MC9S08JS16_H)
	    wlength = (uint_8)setup_packet->length;
	    #else
	    wlength = setup_packet->length;
	    #endif
	    
	    /* check wlength */
	    if (wlength>0)
	    {               
	        g_state = USB_DFU_DNLOAD_SYNC;
	        Flag_Block_Complete = FALSE;
	    }
	    if (wlength==0)
	    {           
	        g_state = USB_DFU_MANIFEST_SYNC;    
	        status = USB_OK;
	    }
	    /* Call to application */
	    status = USB_Class_DFU_Dnload(controller_ID,wBlockNum,data,&wlength);      
	        if (USB_OK != status)
	        {
	        	g_state= USB_DFU_ERROR;
	        }
        break;
    /* DFU_ABORT request */
    case USB_DFU_ABORT:
        status = USB_OK;
        g_state = USB_DFU_IDLE;
        break;
    /* DFU_GETSTATUS request */
    case USB_DFU_GETSTATUS:
        status= USB_Class_DFU_Getstatus(controller_ID,interface,data,size);
        break;
    /* DFU_GETSTATE request */
    case USB_DFU_GETSTATE:
        status = USB_Class_DFU_Getstate(controller_ID,interface,data,size);
        break;
    default:
        status = USBERR_INVALID_REQ_TYPE;
        g_state = USB_DFU_ERROR;
        break;
    }
    return status;
}

/**************************************************************************//*!
 *
 * @name  DFU_Manifest_Sync_State
 *
 * @brief   The function processes requests at USB_DFU_MANIFEST_SYNC   state
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Setup packet received
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *                        USB_OK        : When Successful
 *                        Others        : When Error
 *
 ******************************************************************************/
static uint_8 DFU_Manifest_Sync_State
(
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Setup packet received */
    uint_8_ptr *data,                   /* [OUT] Data to be send back */
    USB_PACKET_SIZE *size               /* [OUT] Size to be returned*/
)
{
    uint_8 status;
    uint_8 interface;

    interface = (uint_8)setup_packet->index;
    switch (setup_packet->request)
    {
    /* DFU_GETSTATUS request */
    case USB_DFU_GETSTATUS:
        if (Flag_Manifest_Complete)
        {
#if(MANIFESTATION)
            g_state = USB_DFU_IDLE;
            g_status[BSTATE] = g_state;
            status= USB_Class_DFU_Getstatus(controller_ID,interface,data,size);    
#endif
        }
        else
        {	/* poll time out for manifest process */
        	(void)RemoveTimerQ(0);
            Flag_bwPoll_TimeOut = FALSE;
            if(g_status[BWPOLLTIMEOUT+2]>0)
            bwPoll_TimeOut.msCount = 0xFFFF; /* Max Poll Time Out */
            else
            bwPoll_TimeOut.msCount = (uint_16)(g_status[BWPOLLTIMEOUT]+(g_status[BWPOLLTIMEOUT+1] <<8));
            bwPoll_TimeOut.pfnTimerCallback = USB_Class_DFU_Process_bwPoll_TimeOut;
            (void)AddTimerQ(&bwPoll_TimeOut);
            g_state = USB_DFU_MANIFEST;
            g_status[BSTATE] = g_state;
            status= USB_Class_DFU_Getstatus(controller_ID,interface,data,size);
            
        }
        break;
    /* DFU_GETSTATE request */
    case USB_DFU_GETSTATE:
        status = USB_Class_DFU_Getstate(controller_ID,interface,data,size);
        break;
    default:
        status = USBERR_INVALID_REQ_TYPE;
        g_state = USB_DFU_ERROR;
        break;
    }
    return status;
} 
/**************************************************************************//*!
 *
 * @name  DFU_Manifest_State
 *
 * @brief   The function processes requests at DFU_MANIFEST  state
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Setup packet received
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *                        USB_OK        : When Successful
 *                        Others        : When Error
 *
 *****************************************************************************/
static uint_8 DFU_Manifest_State
(
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Setup packet received */
    uint_8_ptr *data,                   /* [OUT] Data to be send back */
    USB_PACKET_SIZE *size               /* [OUT] Size to be returned*/
)
{
    UNUSED(controller_ID);
    UNUSED(setup_packet);
    UNUSED(data);
    UNUSED(size);    
    g_state = USB_DFU_ERROR;
    return USBERR_INVALID_REQ_TYPE;
}
/**************************************************************************//*!
 *
 * @name  DFU_Manifest_Wait_Reset_State
 *
 * @brief   The function processes requests at USB_DFU_MANIFEST_WAIT_RESET  state
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Setup packet received
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *                        USB_OK        : When Successful
 *                        Others        : When Error
 *
 *****************************************************************************/
static uint_8 DFU_Manifest_Wait_Reset_State
(
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Setup packet received */
    uint_8_ptr *data,                   /* [OUT] Data to be send back */
    USB_PACKET_SIZE *size               /* [OUT] Size to be returned*/
)
{
    UNUSED(controller_ID);
    UNUSED(setup_packet);
    UNUSED(data);
    UNUSED(size);
    
    return USBERR_INVALID_REQ_TYPE;;
}
/**************************************************************************//*!
 *
 * @name  DFU_Upload_Idle_State
 *
 * @brief   The function processes requests at USB_DFU_UPLOAD_IDLE    state
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Setup packet received
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *                        USB_OK        : When Successful
 *                        Others        : When Error
 *
 ******************************************************************************/
static uint_8 DFU_Upload_Idle_State
(
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Setup packet received */
    uint_8_ptr *data,                   /* [OUT] Data to be send back */
    USB_PACKET_SIZE *size               /* [OUT] Size to be returned*/
)
{
    uint_8 status;
    uint_8 interface,BlockNum,wBlockNum,check_request_type;

    interface = (uint_8)setup_packet->index;
    BlockNum = (uint_8)setup_packet->value;
    wBlockNum = (uint_8)setup_packet->value;
    check_request_type =(uint_8)setup_packet->request_type;
    *data = ((uint_8*)setup_packet)+USB_SETUP_PKT_SIZE;

    switch (setup_packet->request)
    {
    /* DFU_UPLOAD Request */
    case USB_DFU_UPLOAD:
        status = USB_Class_DFU_Upload(controller_ID,BlockNum, data, size, setup_packet->length);
        if (*size < setup_packet->length) g_state = USB_DFU_IDLE;
        break;
    /* DFU_ABORT Request */
    case USB_DFU_ABORT:
        status = USB_OK;
        g_state = USB_DFU_IDLE;
        break;
    /* DFU_GETSTATUS Request */
    case USB_DFU_GETSTATUS:
        status= USB_Class_DFU_Getstatus(controller_ID,interface,data,size);
        break;
    /* DFU_GETSTATE Request */
    case USB_DFU_GETSTATE:
        status = USB_Class_DFU_Getstate(controller_ID,interface,data,size);
        break;
    default:
        status = USBERR_INVALID_REQ_TYPE;
        g_state = USB_DFU_ERROR;
        break;
    }
    return status;
}

/**************************************************************************//*!
 *
 * @name  DFU_Error_State
 *
 * @brief   The function processes requests at USB_DFU_ERROR    state
 *
 * @param controller_ID     : Controller ID
 * @param setup_packet      : Setup packet received
 * @param data              : Data to be send back
 * @param size              : Size to be returned
 *
 * @return status:
 *                        USB_OK        : When Successful
 *                        Others        : When Error
 *
 *****************************************************************************/
static uint_8 DFU_Error_State
(
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Setup packet received */
    uint_8_ptr *data,                   /* [OUT] Data to be send back */
    USB_PACKET_SIZE *size               /* [OUT] Size to be returned*/
)
{
    uint_8 status;
    uint_8 interface;

    interface = (uint_8)setup_packet->index;
    switch (setup_packet->request)
    {
    /* DFU_GETSTATUS Request */
    case USB_DFU_GETSTATUS:
        status= USB_Class_DFU_Getstatus(controller_ID,interface,data,size);
        break;
    /* DFU_GETSTATE Request */
    case USB_DFU_GETSTATE:
        status = USB_Class_DFU_Getstate(controller_ID,interface,data,size);
        break;
    /* DFU_CLRSTATUS Request */
    case USB_DFU_CLRSTATUS:
        status = USB_OK;
        g_state = USB_DFU_IDLE;
        break;
    default:
        status = USBERR_INVALID_REQ_TYPE;
        break;
    }

    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_DFU_Event
 *
 * @brief The function initializes DFU endpoint
 *
 * @param controller_ID     : Controller ID
 * @param event             : Event Type
 * @param val               : Pointer to configuration Value
 *
 * @return None
 *
 ******************************************************************************
 * The funtion initializes the DFU endpoints when Enumeration complete event is
 * received
 *****************************************************************************/
static void USB_Class_DFU_Event 
(
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_8 event,           /* [IN] Event Type */
    void* val               /* [IN] Pointer to configuration Value */
)
{
	switch(event)
	{

		case USB_APP_BUS_RESET:
        if (g_dfu_class_callback != NULL)
        {
            /* notify the application of the event */
            g_dfu_class_callback(controller_ID, event, val);
        }
    	break;
    	
		case BUS_POWERED:	
        g_state = USB_APP_DETACH;
		break;
	}	
}

/*****************************************************************************
 * Global Functions
 *****************************************************************************

 *****************************************************************************
 *
 * @name  USB_Class_DFU_Init
 *
 * @brief   The funtion initializes the Device and Controller layer
 *
 * @param   controller_ID               : Controller ID
 * @param   dfu_class_callback          : DFU Class Callback
 * @param   vendor_req_callback         : Vendor Request Callback
 * @param   param_callback              : Class requests Callback
 *
 * @return status:
 *                        USB_OK        : When Successfull
 *                        Others        : When Error
 *
 ******************************************************************************
 *This function initializes the DFU Class layer and layers it is dependent on
 *****************************************************************************/
uint_8 USB_Class_DFU_Init 
(
    uint_8    controller_ID,                /* [IN] Controller ID */
    USB_CLASS_CALLBACK dfu_class_callback,  /* [IN] DFU Class Callback */
    USB_REQ_FUNC       vendor_req_callback, /* [IN] Vendor Request Callback */
    USB_CLASS_SPECIFIC_HANDLER_FUNC param_callback
                                            /* [ IN] DFU Class requests Callback */
)
{
    USB_ENDPOINTS *ep_desc_data = (USB_ENDPOINTS *)
                                  USB_Desc_Get_Endpoints(controller_ID);

    /* Initialize the device layer*/
    uint_8 status = _usb_device_init(controller_ID, NULL,
                                    (uint_8)(ep_desc_data->count+1), TRUE);
    if (status == USB_OK)
    {
        /* Initialize the generic class functions */
        status = USB_Class_Init(controller_ID,USB_Class_DFU_Event,
                                USB_Other_Requests);

        if (status == USB_OK)
        {
            /* save the DFU class callback pointer */
            g_dfu_class_callback = dfu_class_callback;

            /* save the vendor request callback pointer */
            g_vendor_req_callback = vendor_req_callback;

            /* Save the callback to ask application for class specific params*/
            g_param_callback = param_callback;
        }
    }
    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_DFU_DeInit
 *
 * @brief   The function de-initializes the Device and Controller layer
 *
 * @param   controller_ID               : Controller ID
 *
 * @return status:
 *                        USB_OK        : When Successful
 *                        Others        : When Error
 *
 ******************************************************************************
 *This function de-initializes the DFU Class layer
 *****************************************************************************/
uint_8 USB_Class_DFU_DeInit 
(
    uint_8 controller_ID              /* [IN] Controller ID */
) 
{
    uint_8 status;
   
    /* free the HID class callback pointer */
    g_dfu_class_callback = NULL;
    
    /* free the vendor request callback pointer */
    g_vendor_req_callback = NULL;
    
    /* free the callback to ask application for class specific params*/
    g_param_callback = NULL;
    
    /* Call common class deinit function */
    status = USB_Class_DeInit(controller_ID);
    
    if(status == USB_OK)
    /* Call device deinit function */
    	status = _usb_device_deinit();
    	
    return status;
} 

/*****************************************************************************
 *
 * @name  USB_Class_DFU_Periodic_Task
 *
 * @brief   The function implements flashing task
 *
 * @param   none
 *
 * @return status:
 *                        none
 *
 ******************************************************************************
 *
 *****************************************************************************/
void USB_Class_DFU_Periodic_Task(void)
{
	    if ((g_state == USB_DFU_DNBUSY)&&(Flag_Block_Complete == FALSE))
    {
	    /* The state has just changed to USB_DFU_DNBUSY from USB_DFU_DNLOAD_SYNC 
		state after received get_STATUS request */
		/* Erase memory, write the received block to flash memory */
		USB_Class_DFU_Flashing();
		Flag_Block_Complete = TRUE;
    }
		
 	if((g_state == USB_DFU_MANIFEST)&&(Flag_Manifest_Complete  == FALSE))
    {
	    /* The state has just changed to USB_DFU_MANIFEST from USB_DFU_MANIFEST_SYNC 
		state after received get_STATUS request */
		/* Erase memory, write the received block to flash memory */
    	USB_Class_DFU_Manifest();
    	Flag_Manifest_Complete  = TRUE;
    }
}


