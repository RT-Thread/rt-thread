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
 * @file phdc_com_model.c
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009

 * @brief This file packetizes the data to be sent according to the IEEE_11073
 *        protocol.
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "hidef.h"                  /* for EnableInterrupts macro */
#include "derivative.h"             /* include peripheral declarations */
#include "types.h"                  /* User Defined Data Types */
#include "phd_com_model.h"          /* IEEE11073 Header File */
#include "phdc_app.h"               /* PHDC Application Header File */
#include "usb_phdc.h"               /* USB PHDC Class Header File */
#include "usb_descriptor.h"         /* PHDC App Descriptor Header File */
#if (defined LITTLE_ENDIAN)
#include "ieee11073_phd_types_kinetis.h"    /* IEEE11073 Data Structures */
#else
#include "ieee11073_phd_types.h"    /* IEEE11073 Data Structures */
#endif
#include "ieee11073_nom_codes.h"    /* IEEE11073 Nomenclature Codes */
#include "RealTimerCounter.h"

/* skip the inclusion in dependency stage */
#ifndef __NO_SETJMP
   #include <stdio.h>
#endif
#include <string.h>			

#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
#include "exceptions.h"
#endif

/*****************************************************************************
 * Global Functions Prototypes
 *****************************************************************************/

/****************************************************************************
 * Global Variables - None
 ****************************************************************************/

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
static void PHD_Assoc_Response_Handler(uint_8 controller_ID, APDU* val);
static void PHD_Unhandled_Request(uint_8 controller_ID, APDU* val);
static void PHD_Disconnect_Handler(uint_8 controller_ID, APDU* val);
static void PHD_Connect_Handler(uint_8 controller_ID, APDU* val);
static void PHD_Config_Event_Report_Handler(uint_8 controller_ID, APDU* val);
static void PHD_ABRT_Request_Handler(uint_8 controller_ID, APDU* val);
static void PHD_Assoc_RelRes_Handler(uint_8 controller_ID, APDU* val);
static void PHD_Assoc_RelReq_Handler(uint_8 controller_ID, APDU* val);
static void PHD_OPN_STATE_PRST_APDU_Handler(uint_8 controller_ID, APDU* val);

static uint_8 PHD_Remove_Timer(uint_8_ptr pindex);
static uint_8 PHD_Add_Timer(PTIMER_OBJECT pTimerObject);

void PHD_Callback(uint_8 controller_ID, uint_8 event_type,  void* val);

#ifndef TIMER_CALLBACK_ARG
static void PHD_Association_Timer_Callback(void);
static void PHD_Configuration_Timer_Callback(void);
static void PHD_Msr_Timer_Callback(void);
static void PHD_Disassociation_Timer_Callback(void);
#else
static void PHD_Association_Timer_Callback(void* arg);
static void PHD_Configuration_Timer_Callback(void* arg);
static void PHD_Msr_Timer_Callback(void* arg);
static void PHD_Disassociation_Timer_Callback(void* arg);
#endif
/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/ 
PHD_STATE_MC_FUNC const phd_state_mc_func[AG_MAX_STATES][AG_MAX_EVENTS] =
{
   /* PHD_AG_STATE_DISCONNECTED */
   PHD_Disconnect_Handler,PHD_Connect_Handler,                 NULL,                      NULL,                    NULL,                    NULL,                    NULL,NULL,
   /* PHD_AG_STATE_CON_UNASSOCIATED */
   PHD_Disconnect_Handler,PHD_Connect_Handler,PHD_Unhandled_Request,                      NULL,                    NULL,                    NULL,PHD_ABRT_Request_Handler,NULL,
   /* PHD_AG_STATE_CON_ASSOCIATING */
   PHD_Disconnect_Handler,PHD_Connect_Handler,PHD_Unhandled_Request,PHD_Assoc_Response_Handler,                    NULL,                    NULL,PHD_ABRT_Request_Handler,PHD_OPN_STATE_PRST_APDU_Handler,
   /* PHD_AG_STATE_CON_ASSOC_CFG_SENDING_CONFIG */
   PHD_Disconnect_Handler,PHD_Connect_Handler,PHD_Unhandled_Request,                      NULL,PHD_Assoc_RelReq_Handler,                    NULL,PHD_ABRT_Request_Handler,PHD_OPN_STATE_PRST_APDU_Handler,
   /* PHD_AG_STATE_CON_ASSOC_CFG_WAITING_APPROVAL */
   PHD_Disconnect_Handler,PHD_Connect_Handler,PHD_Unhandled_Request,                      NULL,PHD_Assoc_RelReq_Handler,                    NULL,PHD_ABRT_Request_Handler,PHD_OPN_STATE_PRST_APDU_Handler,
   /* PHD_AG_STATE_CON_ASSOC_OPERATING */
   PHD_Disconnect_Handler,PHD_Connect_Handler,PHD_Unhandled_Request,                      NULL,PHD_Assoc_RelReq_Handler,                    NULL,PHD_ABRT_Request_Handler,PHD_OPN_STATE_PRST_APDU_Handler,
   /* PHD_AG_STATE_CON_DISASSOCIATING */
   PHD_Disconnect_Handler,PHD_Connect_Handler,PHD_Unhandled_Request,                      NULL,PHD_Assoc_RelReq_Handler,PHD_Assoc_RelRes_Handler,PHD_ABRT_Request_Handler,NULL
};

/*****************************************************************************
 * Local Variables
 *****************************************************************************/
static PHD_CALLBACK g_phd_callback;

#ifdef _MC9S08JS16_H
#pragma DATA_SEG PHD_BUFFER
#endif

static uint_8 phd_buffer[PHD_BUFF_SIZE]; /* buffer used for get
                           attributes response
                           and measurements */

#ifdef _MC9S08JS16_H
#pragma DATA_SEG DEFAULT
#endif


static uint_16 phd_buffer_offset;
/* variables to keep track of the phd_buffer usage */
static boolean g_phd_buffer_being_used = FALSE;
static boolean g_sent_resp_get_attr = FALSE;
/* initialize the device state */
static uint_8 phd_com_state = PHD_AG_STATE_DISCONNECTED;

static uint_8 timer_index = INVALID_TIMER_VALUE;
static uint_8 assoc_retry_count = PHD_ASSOC_RETRY_COUNT;

static uint_8 g_controllerID;
/*****************************************************************************
 * Local Functions
 *****************************************************************************/
#if (defined LITTLE_ENDIAN)
intu16 SWAPBYTE16(intu16 a) 
 {
    return ((a >> (intu16)0x08) | ((a & 0xFF) << (intu16)0x08));
 }

intu32 SWAPBYTE32(intu32 a) 
 {
    return (intu32)((SWAPBYTE16((uint_32)(a) & (uint_32)0xFFFF) << 0x10) |(SWAPBYTE16((uint_32)((a) >> 0x10))));
 }
#else
#define SWAPBYTE16(a) 			(a)
#define SWAPBYTE32(a) 			(a)
#endif
/******************************************************************************
 *
 *    @name        PHD_OPN_STATE_PRST_APDU_Handler
 *
 *    @brief       This function handles the request/data sent by the host when
 *                 the device is in operating state
 *
 *    @param       controller_ID : Controller ID
 *    @param       val           : Pointer to APDU received
 *
 *    @return      None
 *
 *****************************************************************************
 * This function parses the data received and checks whether it is a response
 * to the attributes sent or the response to the measurement data
 *****************************************************************************/
static void PHD_OPN_STATE_PRST_APDU_Handler (
    uint_8 controller_ID,   /* [IN] Controller ID */
    APDU* val               /* [IN] Pointer to APDU received */
)
{
    extern uint_8 const PHD_WSL_DIM_GET_RSP[];
    
    if( (val->choice == PRST_CHOSEN) &&
        (
         (phd_com_state == PHD_AG_STATE_CON_ASSOC_OPERATING) ||
         (phd_com_state == PHD_AG_STATE_CON_ASSOCIATING)     ||
         (phd_com_state == PHD_AG_STATE_CON_ASSOC_CFG_SENDING_CONFIG) ||
         (phd_com_state == PHD_AG_STATE_CON_ASSOC_CFG_WAITING_APPROVAL)
        )         
      ) 
    {
        /* get the APDU received starting from invoke id */
        DATA_apdu *p_data_pdu = (DATA_apdu *)&(val->u.prst.value);

        if(p_data_pdu->choice.choice == ROIV_CMIP_GET_CHOSEN)
        {/* its the Get command */
            if(p_data_pdu->choice.u.roiv_cmipGet.attribute_id_list.count == 0)
            { 
				/* count 0 implies the whole MDS class */
                uint_16 invoke_id = SWAPBYTE16(p_data_pdu->invoke_id);
				
                /* if phd_buffer is already in use, return */
                /* Safe to test without Disable/Enable interrupts, PHD_OPN_STATE_PRST_APDU_Handler
                   is only called from interrupt context
                 */   
                if(g_phd_buffer_being_used == TRUE) 
                {
                    return;   
                }
                g_phd_buffer_being_used = TRUE;

                /* copy the get attribute response into the phd_buffer */
				(void)memcpy(phd_buffer, PHD_WSL_DIM_GET_RSP, DIM_GET_RSP_SIZE);
                /* get the invoke id from the get attribute request sent
                by manager */
#if (defined LITTLE_ENDIAN)
                phd_buffer[6] = (uint_8)((invoke_id >> 8)
                                                          & LOW_BYTE_MASK);
                phd_buffer[7]= (uint_8)((invoke_id) & LOW_BYTE_MASK);
#else
                phd_buffer[6] = (uint_8)((invoke_id >> UPPER_BYTE_SHIFT)
                                                          & LOW_BYTE_MASK);
                phd_buffer[7]= (uint_8)((invoke_id) & LOW_BYTE_MASK);
#endif
                g_sent_resp_get_attr=TRUE;
                /* Send Atributes to Manager */
                (void)USB_Class_PHDC_Send_Data(controller_ID, FALSE, 0,
                	SEND_DATA_QOS, (uint_8_ptr)phd_buffer,
                	(USB_PACKET_SIZE)DIM_GET_RSP_SIZE);
            }
        }
        else if(p_data_pdu->choice.choice == RORS_CMIP_CONFIRMED_EVENT_REPORT_CHOSEN)
        {
          if(phd_com_state == PHD_AG_STATE_CON_ASSOC_CFG_WAITING_APPROVAL) 
          {
            
                      /* confirmed */
            /* configuration accepted */
            ConfigReportRsp *p_rsp = (ConfigReportRsp *)p_data_pdu->choice.
                   u.rors_cmipConfirmedEventReport.event_reply_info.value;
            if((p_rsp->config_report_id == EXTENDED_CONFIG_START) &&
               (p_rsp->config_result == ACCEPTED_CONFIG ))
            {
                (void)PHD_Remove_Timer(&timer_index); 
                /* if configuration accepted, enter operating state */
                phd_com_state = PHD_AG_STATE_CON_ASSOC_OPERATING;
                g_phd_callback(controller_ID,APP_PHD_CONNECTED_TO_HOST);
                g_sent_resp_get_attr=FALSE;
            }
            else
            {
                /* configuration not accepted by the manager */
                phd_com_state = PHD_AG_STATE_CON_ASSOC_CFG_SENDING_CONFIG;
            }
          } 
          else 
          {
            /* confirmed report on completion */
            /* if the received APDU is the response to the measurements sent */
            (void)PHD_Remove_Timer(&timer_index);            
            g_phd_callback(controller_ID,APP_PHD_MEASUREMENT_SENT);
          }
          
        }

    }
}

/******************************************************************************
 *
 *    @name        PHD_Config_Event_Report_Handler
 *
 *    @brief       This function handles the response sent by the host after
 *                 config report is sent to the host for approval
 *
 *    @param       controller_ID : Controller ID
 *    @param       val           : Pointer to APDU received
 *
 *    @return      None
 *
 *****************************************************************************
 * This fucntion parses the response to the configuration event report sent
 * to check whether the configuration was accepted or rejected
 *****************************************************************************/
static void PHD_Config_Event_Report_Handler (
    uint_8 controller_ID,   /* [IN] Controller ID */
    APDU* val               /* [IN] Pointer to APDU received */
)
{
    UNUSED (controller_ID)
    if(( phd_com_state == PHD_AG_STATE_CON_ASSOC_CFG_WAITING_APPROVAL) &&
       ( val->choice ==  PRST_CHOSEN))
    {
        DATA_apdu *p_data_pdu = (DATA_apdu *)&(val->u.prst.value);
        (void)PHD_Remove_Timer(&timer_index);                
        if(p_data_pdu->choice.choice ==
                                  RORS_CMIP_CONFIRMED_EVENT_REPORT_CHOSEN)
        {
            /* confirmed */
            /* configuration accepted */
            ConfigReportRsp *p_rsp = (ConfigReportRsp *)p_data_pdu->choice.
                   u.rors_cmipConfirmedEventReport.event_reply_info.value;
            if((p_rsp->config_report_id == EXTENDED_CONFIG_START) &&
               (p_rsp->config_result == ACCEPTED_CONFIG ))
            {
                /* if configuration accepted, enter operating state */
                phd_com_state = PHD_AG_STATE_CON_ASSOC_OPERATING;
            }
            else
            {
                /* configuration not accepted by the manager */
                phd_com_state = PHD_AG_STATE_CON_ASSOC_CFG_SENDING_CONFIG;
            }
        }
    }
}

/******************************************************************************
 *
 *    @name        PHD_Assoc_Response_Handler
 *
 *    @brief       This function handles the assciation request response sent
 *                 by the host
 *
 *    @param       controller_ID : Controller ID
 *    @param       val           : Pointer to APDU received
 *
 *    @return      None
 *
 *****************************************************************************
 * This function parses the association request response to check whether the
 * configuration was already known to the manager or not. In case the
 * configuartion was not known, configuration event report is sent
 *****************************************************************************/
static void PHD_Assoc_Response_Handler (
    uint_8 controller_ID,   /* [IN] Controller ID */
    APDU* val               /* [IN] Pointer to APDU received */
)
{
    extern uint_8 const PHD_WSL_CNFG_EVT_RPT[];
    if(( phd_com_state == PHD_AG_STATE_CON_ASSOCIATING) &&
        ( val->choice ==  AARE_CHOSEN))
    {
        AARE_apdu *p_assoc_res = &(val->u.aare);
        (void)PHD_Remove_Timer(&timer_index);  
                    
        if( p_assoc_res->result == ACCEPTED_UNKNOWN_CONFIG)
        {
            /* if manager says the configuration is unknown, send configuration
            event report */
            phd_com_state = PHD_AG_STATE_CON_ASSOC_CFG_SENDING_CONFIG;

            /* send the configuration information */
            (void)USB_Class_PHDC_Send_Data(controller_ID, FALSE,0,SEND_DATA_QOS,
        		(uint_8_ptr)PHD_WSL_CNFG_EVT_RPT, 
				(USB_PACKET_SIZE)CNFG_EVT_RPT_SIZE);
        }
        else
        {
            /* if the configuration is already known to the manager, enter
              operating state */
            phd_com_state = PHD_AG_STATE_CON_ASSOC_OPERATING;
            g_phd_callback(controller_ID,APP_PHD_CONNECTED_TO_HOST);
        }
    }
}
/******************************************************************************
 *
 *    @name        PHD_Unhandled_Request
 *
 *    @brief       This function takes care of the unhandled request
 *
 *    @param       controller_ID : Controller ID
 *    @param       val           : Pointer to APDU received
 *
 *    @return      None
 *
 *****************************************************************************
 * This function should take care of any request which is not supported or is
 * illegal
 *****************************************************************************/
static void PHD_Unhandled_Request(
    uint_8 controller_ID,   /* [IN] Controller ID */
    APDU* val               /* [IN] Pointer to APDU received */
)
{
    UNUSED (controller_ID)
    UNUSED (val)
}
/******************************************************************************
 *
 *    @name        PHD_ABRT_Request_Handler
 *
 *    @brief       This function handles abrt req
 *
 *    @param       controller_ID : Controller ID
 *    @param       val           : Pointer to APDU received
 *
 *    @return      None
 *
 *****************************************************************************
 * This handles the abort request sent by the manager
 *****************************************************************************/
static void PHD_ABRT_Request_Handler(
    uint_8 controller_ID,   /* [IN] Controller ID */
    APDU* val               /* [IN] Pointer to APDU received */
)
{
    UNUSED (val)
    phd_com_state = PHD_AG_STATE_CON_UNASSOCIATED;
    assoc_retry_count = PHD_ASSOC_RETRY_COUNT;
    g_phd_callback(controller_ID, APP_PHD_DISCONNECTED_FROM_HOST);
}

/******************************************************************************
 *
 *    @name        PHD_Assoc_RelRes_Handler
 *
 *    @brief       This function handles association release response
 *
 *    @param       controller_ID : Controller ID
 *    @param       val           : Pointer to APDU received
 *
 *    @return      None
 *
 *****************************************************************************
 * This function handles the association release response
 *****************************************************************************/
static void PHD_Assoc_RelRes_Handler(
    uint_8 controller_ID,   /* [IN] Controller ID */
    APDU* val               /* [IN] Pointer to APDU received */
)
{
    UNUSED (val)
    (void)PHD_Remove_Timer(&timer_index);        
    phd_com_state = PHD_AG_STATE_CON_UNASSOCIATED;
    assoc_retry_count = PHD_ASSOC_RETRY_COUNT;
    g_phd_callback(controller_ID, APP_PHD_DISCONNECTED_FROM_HOST);    
}
/******************************************************************************
 *
 *    @name        PHD_Assoc_RelReq_Handler
 *
 *    @brief       This function handles association release request
 *
 *    @param       controller_ID : Controller ID
 *    @param       val           : Pointer to APDU received
 *
 *    @return      None
 *
 *****************************************************************************
 * This function sends a response to the association release request
 *****************************************************************************/
static void PHD_Assoc_RelReq_Handler(
    uint_8 controller_ID,   /* [IN] Controller ID */
    APDU* val               /* [IN] Pointer to APDU received */
)
{
    extern uint_8 const PHD_WSL_REL_RES[];
    UNUSED (val)
    (void)PHD_Remove_Timer(&timer_index);    
    /* send release response */
    (void)USB_Class_PHDC_Send_Data(controller_ID, FALSE, 0, SEND_DATA_QOS,
		(uint_8_ptr)PHD_WSL_REL_RES, REL_RES_SIZE);

    phd_com_state = PHD_AG_STATE_CON_UNASSOCIATED;
    assoc_retry_count = PHD_ASSOC_RETRY_COUNT;
    g_phd_callback(controller_ID, APP_PHD_DISCONNECTED_FROM_HOST);

}
/******************************************************************************
 *
 *    @name        PHD_Disconnect_Handler
 *
 *    @brief       This function handles disconnect request
 *
 *    @param       controller_ID : Controller ID
 *    @param       val           : Pointer to APDU received
 *
 *    @return      None
 *
 *****************************************************************************
 * Sets the PHDC state to disconnected
 *****************************************************************************/
static void PHD_Disconnect_Handler(
    uint_8 controller_ID,   /* [IN] Controller ID */
    APDU* val               /* [IN] Pointer to APDU received */
)
{
    UNUSED (controller_ID)
    UNUSED (val)
    (void)PHD_Remove_Timer(&timer_index);
    phd_com_state = PHD_AG_STATE_DISCONNECTED;
    g_phd_callback(controller_ID, APP_PHD_UNINITIALISED);
}
/******************************************************************************
 *
 *    @name        PHD_Connect_Handler
 *
 *    @brief       This function handles connect request
 *
 *    @param       controller_ID : Controller ID
 *    @param       val           : Pointer to APDU received
 *
 *    @return      None
 *
 *****************************************************************************
 * Sets the PHDC state to unassciated if it was disconnected
 *****************************************************************************/
static void PHD_Connect_Handler(
    uint_8 controller_ID,   /* [IN] Controller ID */
    APDU* val               /* [IN] Pointer to APDU received */
)
{
    UNUSED (val)
    if(phd_com_state == PHD_AG_STATE_DISCONNECTED)
    {
        phd_com_state = PHD_AG_STATE_CON_UNASSOCIATED;
        assoc_retry_count = PHD_ASSOC_RETRY_COUNT;
        g_phd_callback(controller_ID, APP_PHD_INITIALISED);
    }

}
/******************************************************************************
 *
 *    @name        PHD_Callback
 *
 *    @brief       This function handles the callback
 *
 *    @param       controller_ID : Controller ID
 *    @param       event_tyoe    : type of the event
 *    @param       val           : Pointer to Received Buffer
 *
 *    @return      None
 *
 *****************************************************************************
 * This function is called from the class layer and handles the events (reset,
 * enumeration complete, send/recv complete)
 *****************************************************************************/
void PHD_Callback(
    uint_8 controller_ID,  /* [IN] Controller ID */
    uint_8 event_type,     /* [IN] type of the event */
    void* val              /* [IN] Pointer to Received Buffer */
)
{

    uint_8 trans_event = 0xff;

    switch (event_type)
    {
		case USB_APP_BUS_RESET:
		case USB_APP_CONFIG_CHANGED:
			/* on reset, transport is disconnected */
			trans_event = PHD_AG_EVT_TRANSPORT_DISCONNECTED;
			break;		
		case USB_APP_ENUM_COMPLETE:
			/* when enumeration is complete, transport is connected */
			trans_event = PHD_AG_EVT_TRANSPORT_CONNECTED;
			break;
	  case USB_APP_META_DATA_PARAMS_CHANGED:
        case USB_APP_ERROR:
			(void)USB_Class_PHDC_Recv_Data(controller_ID, PHDC_BULK_OUT_QOS, NULL, 0);
			return;
			break;
		case USB_APP_GET_DATA_BUFF:
		{
			/* called by lower layer to get recv buffer */
			PTR_USB_CLASS_PHDC_RX_BUFF rx_buff = 
				(PTR_USB_CLASS_PHDC_RX_BUFF)val;

			/* Copy Received Data*/
			if(phd_buffer_offset == 0)
			{
				(void)memcpy(phd_buffer, rx_buff->in_buff, rx_buff->in_size);
			}
#ifdef _MC9S08JS16_H
		    phd_buffer_offset += rx_buff->in_size;
            (void)USB_Class_PHDC_Recv_Data(controller_ID, PHDC_BULK_OUT_QOS, 
                phd_buffer + phd_buffer_offset, 
                (uint_8)(rx_buff->transfer_size - phd_buffer_offset));
#else            
		    phd_buffer_offset += rx_buff->in_size;
            (void)USB_Class_PHDC_Recv_Data(controller_ID, PHDC_BULK_OUT_QOS, 
                phd_buffer + phd_buffer_offset, 
                (uint_16)(rx_buff->transfer_size - phd_buffer_offset));	
#endif            
			break;
		}
		case USB_APP_GET_TRANSFER_SIZE:
		{
            PTR_USB_CLASS_PHDC_XFER_SIZE xfer_size = 
				(PTR_USB_CLASS_PHDC_XFER_SIZE)val;
#if USB_METADATA_SUPPORTED
			if(xfer_size->meta_data_packet)
			{
				PTR_USB_META_DATA_MSG_PREAMBLE metadata_preamble_ptr =
					(PTR_USB_META_DATA_MSG_PREAMBLE)xfer_size->in_buff;
				xfer_size->transfer_size = (USB_PACKET_SIZE)
					(metadata_preamble_ptr->opaque_data_size + 
					METADATA_HEADER_SIZE);
			}
			else
#endif
			{

		    	APDU *papdu = (APDU*)xfer_size->in_buff;
			    xfer_size->transfer_size = (USB_PACKET_SIZE)
    			    (papdu->length + APDU_HEADER_SIZE);
			}
			if(xfer_size->direction == USB_RECV)
			{
			    phd_buffer_offset = 0;
			}
			break;
		}
		case USB_APP_DATA_RECEIVED:
		{
			PTR_USB_APP_EVENT_DATA_RECEIVED rx_buff = 
				(PTR_USB_APP_EVENT_DATA_RECEIVED )val;
		
			/* Copy Received Data*/
			if(phd_buffer_offset == 0)
			{
				(void)memcpy(phd_buffer, rx_buff->buffer_ptr, rx_buff->size);
			}

			/* receive data complete */
			trans_event = PHD_AG_EVT_TRANSPORT_APDU_RECEIVED;
		    
		}
			break;
		case USB_APP_SEND_COMPLETE:
			/* send data complete */
			g_phd_buffer_being_used = FALSE;/* release the phd_buffer */
			switch (phd_com_state)
			{
				case PHD_AG_STATE_CON_ASSOCIATING:
				{                
					TIMER_OBJECT AssocTimerObject;
					/* 10 sec timer */
					AssocTimerObject.msCount = PHD_ASSOCIATION_TIMEOUT;
					AssocTimerObject.pfnTimerCallback = 
					    PHD_Association_Timer_Callback;
					/* start timer */
					timer_index = PHD_Add_Timer(&AssocTimerObject);
					break;
				}
				case PHD_AG_STATE_CON_ASSOC_CFG_SENDING_CONFIG:
				{                

					TIMER_OBJECT ConfigTimerObject;
					phd_com_state = 
						PHD_AG_STATE_CON_ASSOC_CFG_WAITING_APPROVAL;
					/* 10 sec timer */
					ConfigTimerObject.msCount = PHD_CONFIGURATION_TIMEOUT;
					ConfigTimerObject.pfnTimerCallback = 
						PHD_Configuration_Timer_Callback;
					/* start timer */
					timer_index = PHD_Add_Timer(&ConfigTimerObject);
					break;
				}
				case PHD_AG_STATE_CON_DISASSOCIATING:
				{
					TIMER_OBJECT DissocTimerObject;
					/* 3 sec timer */
					DissocTimerObject.msCount = PHD_ASSOC_RELEASE_TIMEOUT;
					DissocTimerObject.pfnTimerCallback = 
						PHD_Disassociation_Timer_Callback;
					/* start timer */
					timer_index = PHD_Add_Timer(&DissocTimerObject);
					break;
				}
				case PHD_AG_STATE_CON_ASSOC_OPERATING:
				{
					if(g_sent_resp_get_attr==TRUE)
					{
						/* attributes sent, ready to send measurements */
						g_phd_callback(controller_ID,
							APP_PHD_CONNECTED_TO_HOST);
						g_sent_resp_get_attr=FALSE;
					}
					else if(phd_com_state == PHD_AG_STATE_CON_ASSOC_OPERATING)
					{
						TIMER_OBJECT MsrTimerObject;
						/* 3 sec timer */
						MsrTimerObject.msCount = PHD_DEFAULT_RESPONSE_TIMEOUT;
						MsrTimerObject.pfnTimerCallback = 
							PHD_Msr_Timer_Callback;
						/* start timer */
						timer_index = PHD_Add_Timer(&MsrTimerObject);                
					}
					break;
				}
			} /* End switch(phd_com_state) */
			break;

		default:
			break;
	}/* End switch(event_type) */

    if(trans_event != 0xff)
    {
        uint_8 com_state;
        uint_8 transport_event = trans_event;

        /* get the received APDU */
        USB_APP_EVENT_DATA_RECEIVED *p_recv =
			(USB_APP_EVENT_DATA_RECEIVED *)val;

        APDU *p_apdu = (APDU *)(phd_buffer);

        if(trans_event == PHD_AG_EVT_TRANSPORT_APDU_RECEIVED)
        {
			/* apdu received from transport */
            transport_event = (uint_8)((p_apdu->choice >> UPPER_BYTE_SHIFT)
				& LOW_NIBBLE_MASK);
        }

        com_state = (uint_8)(phd_com_state & AG_PHD_STATE_MASK);

        if(phd_state_mc_func[com_state][transport_event] != NULL)
        {   /* incase valid event then call the function */
            (void)phd_state_mc_func[com_state][transport_event]
				(controller_ID, p_apdu);
        }
        else
        {
            /* send error to app layer */
            g_phd_callback(controller_ID,APP_PHD_ERROR);
        }
    }
	/* Start next Receive */
	if(trans_event == PHD_AG_EVT_TRANSPORT_APDU_RECEIVED)
	    (void)USB_Class_PHDC_Recv_Data(controller_ID, PHDC_BULK_OUT_QOS, NULL, 0);
    return;
}

/*****************************************************************************
 * Global Functions
 *****************************************************************************/
/******************************************************************************
 *
 *    @name        PHD_Transport_Init
 *
 *    @brief       This function initializes the PHDC class layer and layers
 *                 below
 *
 *    @param       controller_ID : Controller ID
 *    @param       phd_callback  : Callback function to register
 *
 *    @return      None
 *
 *****************************************************************************
 * Called by the application layer to initialize all the layers below it
 *****************************************************************************/
uint_8 PHD_Transport_Init(
    uint_8 controller_ID,         /* [IN] Controller ID */
    PHD_CALLBACK phd_callback     /* [IN] Callback function to register */
)
{
    g_phd_callback = phd_callback;
	g_controllerID = controller_ID;
    return USB_Class_PHDC_Init(controller_ID, PHD_Callback, NULL);
}
/******************************************************************************
 *
 *    @name        PHD_Connect_to_Manager
 *
 *    @brief       This function sends the association request to the host
 *
 *    @param       controller_ID : Controller ID
 *
 *    @return      None
 *
 *****************************************************************************
 * This function is called by the application when enumeration is complete to
 * send the association request
 *****************************************************************************/
void PHD_Connect_to_Manager(
    uint_8 controller_ID   /* [IN] Controller ID */
)
{
    extern uint_8 const PHD_WSL_ASSOC_REQ[];
    if((phd_com_state == PHD_AG_STATE_CON_UNASSOCIATED) ||
     (phd_com_state == PHD_AG_STATE_CON_ASSOCIATING))
    {
        phd_com_state = PHD_AG_STATE_CON_ASSOCIATING;
        /* Send Assoc request to Manager */
        (void)USB_Class_PHDC_Send_Data(controller_ID, FALSE, 0, SEND_DATA_QOS,
			(uint_8_ptr)PHD_WSL_ASSOC_REQ, ASSOC_REQ_SIZE);

    }

}
/******************************************************************************
 *
 *    @name        PHD_Disconnect_from_Manager
 *
 *    @brief       This function sends the association release request to the
 *                 host
 *
 *    @param       controller_ID : Controller ID
 *
 *    @return      None
 *
 ****************************************************************************
 * Called by the application to send the assciation release request
 *****************************************************************************/
void PHD_Disconnect_from_Manager(
    uint_8 controller_ID   /* [IN] Controller ID */
)
{
    extern uint_8 const PHD_WSL_REL_REQ[];
    switch(phd_com_state)
    {
        case PHD_AG_STATE_CON_ASSOCIATING:
            phd_com_state = PHD_AG_STATE_CON_UNASSOCIATED;
            /* Send abort */
            PHD_Send_Abort_to_Manager(controller_ID, 
				(uint_16)ABORT_REASON_UNDEFINED);
            break;
        case PHD_AG_STATE_CON_DISASSOCIATING:
        case PHD_AG_STATE_CON_UNASSOCIATED:
            /* No State Change in case of Dis-Associating or UnAssociated */
            break;
        default:
			phd_com_state = PHD_AG_STATE_CON_DISASSOCIATING;
			/* Send Association release to Manager */
			(void)USB_Class_PHDC_Send_Data(controller_ID, FALSE, 0, 
				SEND_DATA_QOS, (uint_8_ptr)PHD_WSL_REL_REQ, REL_REQ_SIZE);
        break;
    }
}
/******************************************************************************
 *
 *    @name        PHD_Send_Abort_to_Manager
 *
 *    @brief       This function sends abort request to the host
 *
 *    @param       controller_ID : Controller ID
 *    @param       abort_reason  : Reason for abort
 *
 *    @return      None
 *
 ****************************************************************************
 * Called by the application to send abort apdu
 *****************************************************************************/
void PHD_Send_Abort_to_Manager (
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_16 abort_reason    /* [IN] Reason for abort */
)
{
    extern uint_8 const PHD_WSL_ABRT[];
    phd_com_state = PHD_AG_STATE_CON_UNASSOCIATED;
    assoc_retry_count = PHD_ASSOC_RETRY_COUNT;    
    (void)memcpy(phd_buffer, PHD_WSL_ABRT, ABRT_SIZE);
    
    /* Update the abort reason */
    phd_buffer[4] = (uint_8)((abort_reason >> 8) & 0xFF);
    phd_buffer[5] = (uint_8)(abort_reason & 0xFF);    
    
    /* Send Abort to Manager */
    (void)USB_Class_PHDC_Send_Data(controller_ID, FALSE, 0, SEND_DATA_QOS,
		(uint_8_ptr)&phd_buffer, ABRT_SIZE);
}

/******************************************************************************
 *
 *    @name        PHD_Send_Measurements_to_Manager
 *
 *    @brief       This function sends measurements to the host
 *
 *    @param       controller_ID : Controller ID
 *
 *    @return      None
 *
 *****************************************************************************
 * Called by the application to send the measurement data via event report
 *****************************************************************************/
void PHD_Send_Measurements_to_Manager(
    uint_8 controller_ID      /* [IN] Controller ID */ ,
    uint_8 qos
)
{
    if(phd_com_state == PHD_AG_STATE_CON_ASSOC_OPERATING)
    {
        USB_PACKET_SIZE buff_size = (USB_PACKET_SIZE)PHD_BUFF_SIZE;
        DisableInterrupts;
		#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
		usb_int_dis();
		#endif		
        /* if phd_buffer already in use, return */
        if(g_phd_buffer_being_used == TRUE) 
		{
            EnableInterrupts;
			#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
			usb_int_en();
			#endif					
			return;
		}
        g_phd_buffer_being_used = TRUE;
        EnableInterrupts;
		#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
		usb_int_en();
		#endif				
        
		/* update measurements */
		PHD_Send_WSL_Measurements_to_Manager (controller_ID, &phd_buffer, 
			(void*)&buff_size);
        /* send measurements */
        (void)USB_Class_PHDC_Send_Data(controller_ID, FALSE, 0, qos,
			(uint_8_ptr)phd_buffer, buff_size);
                                                                             
    }
}

/******************************************************************************
 *
 *    @name        PHD_Association_Timer_Callback
 *
 *    @brief       This function is called whenever association timeout occurs
 *
 *    @param       arg : Argument passed by Timer ISR (optional)
 *
 *    @return      None
 *
 *****************************************************************************
 * This function is called whenever association response is not received 
 * within the association timeout time (10 seconds)
 *****************************************************************************/
#ifdef TIMER_CALLBACK_ARG
static void PHD_Association_Timer_Callback(void* arg)
#else
static void PHD_Association_Timer_Callback(void)
#endif
{
#ifdef TIMER_CALLBACK_ARG
    UNUSED(arg)
#endif
    
    /* Decrement association retry count */
    assoc_retry_count--;
    if(assoc_retry_count != 0)
    {                
        /* connect to the manager if max retry count not reached */
        PHD_Connect_to_Manager(g_controllerID);
    }
    else
    {

        /* association failed for max retry count, so trasition to unassociated
        state, and reset the retry count. Now it is upto the application to 
        start the association */
        /* Send abort */
        PHD_Send_Abort_to_Manager(g_controllerID, 
		(uint_16) ABORT_REASON_RESPONSE_TIMEOUT);
        /* send error to app layer */
        g_phd_callback(g_controllerID, APP_PHD_ASSOCIATION_TIMEDOUT);
    }
}
/******************************************************************************
 *
 *    @name        PHD_Configuration_Timer_Callback
 *
 *    @brief       This function is called whenever configuration timeout 
 *                 occurs
 *
 *    @param       arg : Argument passed by Timer ISR (optional)
 *
 *    @return      None
 *
 *****************************************************************************
 * This function is called whenever no response is received by the device 
 * after sending the configuration event report within the configuration 
 * timeout time
 *****************************************************************************/
#ifdef TIMER_CALLBACK_ARG
static void PHD_Configuration_Timer_Callback(void* arg)
#else
static void PHD_Configuration_Timer_Callback(void)
#endif
{
#ifdef TIMER_CALLBACK_ARG
    UNUSED(arg)
#endif
    /* Send abort */
    PHD_Send_Abort_to_Manager(g_controllerID, 
		(uint_16) ABORT_REASON_RESPONSE_TIMEOUT);
}
/******************************************************************************
 *
 *    @name        PHD_Msr_Timer_Callback
 *
 *    @brief       This function is called whenever measurement timeout occurs
 *
 *    @param       arg : Argument passed by Timer ISR (optional)
 *
 *    @return      None
 *
 *****************************************************************************
 * This function is called whenever the response to the measurements is not 
 * sent by the host within the specified time
 *****************************************************************************/
#ifdef TIMER_CALLBACK_ARG
static void PHD_Msr_Timer_Callback(void* arg)
#else
static void PHD_Msr_Timer_Callback(void)
#endif
{
#ifdef TIMER_CALLBACK_ARG
    UNUSED(arg)
#endif
    /* Send abort */
    PHD_Send_Abort_to_Manager(g_controllerID, 
		(uint_16) ABORT_REASON_RESPONSE_TIMEOUT);
}
/******************************************************************************
 *
 *    @name        PHD_Disassociation_Timer_Callback
 *
 *    @brief       This function is called whenever disassociation timeout occurs
 *
 *    @param       arg : Argument passed by Timer ISR (optional)
 *
 *    @return      None
 *
 *****************************************************************************
 * This function is called whenever the timer expires after the disassociation 
 * request is sent by the device i.e. no packet received in response to the 
 * association release request
 *****************************************************************************/    
#ifdef TIMER_CALLBACK_ARG
static void PHD_Disassociation_Timer_Callback(void* arg)
#else
static void PHD_Disassociation_Timer_Callback(void)
#endif
{
#ifdef TIMER_CALLBACK_ARG
    UNUSED(arg)
#endif
    /* Send abort */
    PHD_Send_Abort_to_Manager(g_controllerID, 
		(uint_16) ABORT_REASON_RESPONSE_TIMEOUT);
}

/******************************************************************************
 *
 *    @name        PHD_Remove_Timer
 *
 *    @brief       This funtion calls the Timer api to remove the timer from 
 *                 the queue
 *
 *    @param       pindex : Pointer to Timer Index
 *
 *    @return      ERR_SUCCESS          : Timer removed successfully
 *                 ERR_INVALID_PARAM    : Inavlid timer index
 *
 *****************************************************************************
 * This function when called removes the timer specified by the timer index
 *****************************************************************************/
static uint_8 PHD_Remove_Timer(uint_8_ptr pindex)
{
#if MAX_TIMER_OBJECTS
    uint_8 err = (uint_8)ERR_INVALID_PARAM;
    if(*pindex != INVALID_TIMER_VALUE)
    {
        (void)RemoveTimerQ(*pindex);
        *pindex = INVALID_TIMER_VALUE;
        err = ERR_SUCCESS;
    }
    return err;
#else
    UNUSED(pindex)
	return ERR_SUCCESS;
#endif	
}
        
/******************************************************************************
 *
 *    @name        PHD_Add_Timer
 *
 *    @brief       This funtion calls the Timer api to add a timer to the queue
 *
 *    @param       pTimerObject : Pointer to Timer Object
 *
 *    @return      ERR_SUCCESS  : Timer added successfully
 *                 Others       : In case of error
 *
 *****************************************************************************
 * This function when called starts a timer 
 *****************************************************************************/
static uint_8 PHD_Add_Timer(PTIMER_OBJECT pTimerObject)
{
#if MAX_TIMER_OBJECTS    
	return AddTimerQ(pTimerObject);
#else
    UNUSED(pTimerObject)
	return ERR_SUCCESS;	
#endif	
}
