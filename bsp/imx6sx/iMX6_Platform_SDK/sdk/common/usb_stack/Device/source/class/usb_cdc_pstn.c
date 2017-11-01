/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
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
 * @file usb_cdc_pstn.c
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009
 *
 * @brief The file contains USB CDC_PSTN Sub Class implementation.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
 #include "usb_cdc_pstn.h"  /* USB CDC PSTN Sub Class Header File */

 /*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/

/*****************************************************************************
 * Global Functions Prototypes
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

/*****************************************************************************
 * Local Variables
 *****************************************************************************/
/* PSTN subclass callback pointer */
static USB_CLASS_CALLBACK g_pstn_callback = NULL;
/* data terminal equipment present or not */
static boolean g_dte_present = FALSE;
static uint_8 g_dte_status = 0; /* Status of DATA TERMINAL EQUIPMENT */
static uint_16 g_break_duration = 0; /* Length of time in milliseconds of the
                                                              break signal */
static uint_8 g_current_interface = 0;
static UART_BITMAP g_uart_bitmap;

#if CIC_NOTIF_ELEM_SUPPORT
static uint_8 g_serial_state_buf[NOTIF_PACKET_SIZE+UART_BITMAP_SIZE] =
{
    NOTIF_REQUEST_TYPE,SERIAL_STATE_NOTIF,
    0x00,0x00,/*wValue*/
    0x00,0x00,/*interface - modifies*/
    UART_BITMAP_SIZE,0x00,/* wlength*/
    0x00,0x00 /*data initialized - modifies*/
};/*uart bitmap*/
#endif
 /*****************************************************************************
 * Local Functions
 *****************************************************************************/

/*****************************************************************************
 * Global Functions
 *****************************************************************************/

/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_Pstn_Init
 *
 * @brief The function initializes the PSTN Module
 *
 * @param controller_ID     : Controller ID
 * @param callback          : PSTN Callback
 *
 * @return error
 *         USB_OK           : Always
 ******************************************************************************
 * PSTN Sub Class Initialization routine
 *****************************************************************************/
uint_8 USB_Class_CDC_Pstn_Init (
    uint_8    controller_ID,        /* [IN] Controller ID */
    USB_CLASS_CALLBACK callback     /* [IN] PSTN Callback */
)
{
    uint_8 error = USB_OK;
    UNUSED (controller_ID)
    
    /* save input parameters */
    g_pstn_callback = callback;
    return error;
}
/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_PSTN_Get_Line_Coding
 *
 * @brief  This function is called in response to GetLineCoding request
 *
 * @param controller_ID   : Controller ID
 * @param setup_packet    : Pointer to setup packet
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return status:
 *          USB_OK : When Successfull
 *          USBERR_INVALID_REQ_TYPE: When  request for
 *                                   invalid Interface is presented
 ******************************************************************************
 * Calls application to receive Line Coding Information
 *****************************************************************************/
uint_8 USB_Class_CDC_PSTN_Get_Line_Coding (
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data to be send */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
    uint_8 status;
    UNUSED (size)
    g_current_interface = (uint_8)setup_packet->index ;
    status = USB_Desc_Get_Line_Coding(controller_ID, g_current_interface, 
        data);

    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_PSTN_Set_Line_Coding
 *
 * @brief  This function is called in response to SetLineCoding request
 *
 * @param controller_ID   : Controller ID
 * @param setup_packet    : Pointer to setup packet
 * @param data            : Pointer to Data
 * @param size            : Pointer to Size of Data
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Calls Applciation to update Line Coding Information
 *****************************************************************************/
uint_8 USB_Class_CDC_PSTN_Set_Line_Coding (
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
    uint_8 status;
    UNUSED(data)
    
    *size = 0;

    g_current_interface = (uint_8)setup_packet->index ;
    status = USB_Desc_Set_Line_Coding(controller_ID, g_current_interface,
        (uint_8_ptr *)&setup_packet);

    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_PSTN_Set_Ctrl_Line_State
 *
 * @brief  This function is called in response to Set Control Line State
 *
 * @param controller_ID   : Controller ID
 * @param setup_packet    : Pointer to setup packet
 * @param data            : Pointer to Data
 * @param size            : Pointer to Size of Data
 *
 * @return status:
 *                        USB_OK : Always
 ******************************************************************************
 * Updates Control Line State
 *****************************************************************************/
uint_8 USB_Class_CDC_PSTN_Set_Ctrl_Line_State (
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data  */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
    UNUSED(data)
    *size = 0;

    g_dte_status = (uint_8)setup_packet->value ;
    g_uart_bitmap._byte = 0x00; /* initialize */
    /* activate/deactivate Tx carrier */
    g_uart_bitmap.Bitmap_Uart.bTxCarrier = (g_dte_status &
        CARRIER_ACTIVATION_CHECK) ? 1 : 0 ;
     /* activate carrier and DTE */
    g_uart_bitmap.Bitmap_Uart.bRxCarrier = (g_dte_status &
        CARRIER_ACTIVATION_CHECK) ? 1 : 0 ;

    /* Indicates to DCE if DTE is present or not */
    g_dte_present = (boolean)((g_dte_status & DTE_PRESENCE_CHECK) ?
        TRUE : FALSE);
    UNUSED(g_dte_present);
#if CIC_NOTIF_ELEM_SUPPORT
    /* Send Notification to Host - Parameter on Device side has changed */
    USB_Class_CDC_PSTN_Send_Serial_State(controller_ID);
#endif
    if(g_pstn_callback != NULL)
    {
        if(g_dte_status & CARRIER_ACTIVATION_CHECK)
        {
            g_pstn_callback(controller_ID, USB_APP_CDC_CARRIER_ACTIVATED, 
                NULL);
        }
        else
        {
            g_pstn_callback(controller_ID, USB_APP_CDC_CARRIER_DEACTIVATED,
                NULL);
        }
    }
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_PSTN_Send_Break
 *
 * @brief  This function is called in response to Set Config request
 *
 * @param controller_ID   : Controller ID
 * @param setup_packet    : Pointer to setup packet
 * @param data            : Pointer to Data
 * @param size            : Pointer to Size of Data
 *
 * @return status:
 *                        USB_OK : Always
 ******************************************************************************
 * Updates Break Duration Information from Host
 *****************************************************************************/
uint_8 USB_Class_CDC_PSTN_Send_Break (
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data  */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
    UNUSED (controller_ID)
    UNUSED (data)
    *size = 0;

    g_break_duration = setup_packet->value;
    UNUSED(g_break_duration);

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_PSTN_Get_Comm_Feature
 *
 * @brief  This function is called in response to GetCommFeature request
 *
 * @param controller_ID   : Controller ID
 * @param setup_packet    : Pointer to setup packet
 * @param data            : Pointer to Data to be send
 * @param size            : Pointer to Size of Data
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Returns the status of the get comm feature request
 *****************************************************************************/
uint_8 USB_Class_CDC_PSTN_Get_Comm_Feature (
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data to send */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{   uint_8 status;

    status = USB_OK;
    *size = COMM_FEATURE_DATA_SIZE;
    g_current_interface = (uint_8)setup_packet->index ;
    if(setup_packet->value == ABSTRACT_STATE_FEATURE)
    {
        status = USB_Desc_Get_Abstract_State(controller_ID, 
            g_current_interface, data);
    }
    else if(setup_packet->value == COUNTRY_SETTING_FEATURE)
    {
        status = USB_Desc_Get_Country_Setting(controller_ID,
            g_current_interface, data);
    }
    else
    {
        *size = 0; /* for Reserved/Invalid Feature Selector Value */
    }
    return status;
}

/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_PSTN_Set_Comm_Feature
 *
 * @brief  This function is called in response to SetCommFeature request
 *
 * @param controller_ID   : Controller ID
 * @param setup_packet    : Pointer to setup packet
 * @param data            : Pointer to Data
 * @param size            : Pointer to Size of Data
 *
 * @return status:
 *      USB_OK                  : When Successfull
 *      USBERR_INVALID_REQ_TYPE : When  request for invalid
 *                                Interface is presented
 ******************************************************************************
 * Sets the comm feature specified by Host
 *****************************************************************************/
uint_8 USB_Class_CDC_PSTN_Set_Comm_Feature (
    uint_8 controller_ID,               /* [IN] Controller ID */
    USB_SETUP_STRUCT * setup_packet,    /* [IN] Pointer to setup packet */
    uint_8_ptr *data,                   /* [OUT] Pointer to Data */
    USB_PACKET_SIZE *size               /* [OUT] Pointer to Size of Data */
)
{
    uint_8 status;
    status = USB_OK;
    *size = COMM_FEATURE_DATA_SIZE;
    g_current_interface = (uint_8)setup_packet->index ;
    if(setup_packet->value == ABSTRACT_STATE_FEATURE)
    {
        status = USB_Desc_Set_Abstract_State(controller_ID,
            g_current_interface, data);
    }
    else if(setup_packet->value == COUNTRY_SETTING_FEATURE)
    {
        status = USB_Desc_Set_Country_Setting(controller_ID,
            g_current_interface, data);
    }
    else
    {
        *size = 0; /* for Reserved/Invalid Feature Selector Value */
    }
    return status;
}

#if CIC_NOTIF_ELEM_SUPPORT
/**************************************************************************//*!
 *
 * @name  USB_Class_CDC_PSTN_Send_Serial_State
 *
 * @brief  This function is called to send serial state notification
 *
 * @param controller_ID : Controller ID
 *
 * @return NONE
 ******************************************************************************
 * Returns the Serial State
 *****************************************************************************/
void USB_Class_CDC_PSTN_Send_Serial_State (
    uint_8 controller_ID               /* [IN] Controller ID */
)
{
    /* update array for current interface */
    g_serial_state_buf[4] = g_current_interface;
    /* Lower byte of UART BITMAP */
    g_serial_state_buf[NOTIF_PACKET_SIZE+UART_BITMAP_SIZE-2] =
        g_uart_bitmap._byte;
    (void)USB_Class_CDC_Interface_CIC_Send_Data(controller_ID,
        g_serial_state_buf, (NOTIF_PACKET_SIZE + UART_BITMAP_SIZE));
}
#endif

