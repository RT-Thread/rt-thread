/**
* \copyright
* Copyright (c) 2018, Infineon Technologies AG
* All rights reserved.
*
* This software is provided with terms and conditions as specified in OPTIGA(TM) Trust X Evaluation Kit License Agreement.
* \endcopyright
*
* \author Infineon AG
*
* \file ifx_i2c_data_link_layer.c
*
* \brief   This file implements the IFX I2C Datalink Layer.
*
* \addtogroup  grIFXI2C
* @{
*/

/***********************************************************************************************************************
* HEADER FILES
**********************************************************************************************************************/
#include "ifx_i2c_data_link_layer.h"
#include "ifx_i2c_physical_layer.h"  // include lower layer header

/// @cond hidden
/***********************************************************************************************************************
* MACROS
**********************************************************************************************************************/
// Data Link layer internal states
#define DL_STATE_UNINIT                  (0x00)
#define DL_STATE_IDLE                   (0x01)
#define DL_STATE_TX                     (0x02)
#define DL_STATE_RX                     (0x03)
#define DL_STATE_ACK                    (0x04)
#define DL_STATE_RESEND                 (0x05)
#define DL_STATE_NACK                   (0x06)
#define DL_STATE_ERROR                  (0x08)
#define DL_STATE_DISCARD                (0x09)
#define DL_STATE_RX_DF					(0x0A)
#define DL_STATE_RX_CF					(0x0B)

// Data Link Layer Frame Control Constants
#define DL_FCTR_FTYPE_MASK              (0x80)
#define DL_FCTR_FTYPE_OFFSET            (7)
#define DL_FCTR_VALUE_CONTROL_FRAME     (0x01)

#define DL_FCTR_SEQCTR_MASK             (0x60)
#define DL_FCTR_SEQCTR_OFFSET           (5)
#define DL_FCTR_SEQCTR_VALUE_ACK        (0x00)
#define DL_FCTR_SEQCTR_VALUE_NACK       (0x01)
#define DL_FCTR_SEQCTR_VALUE_RESYNC     (0x02)
#define DL_FCTR_SEQCTR_VALUE_RFU        (0x03)

#define DL_FCTR_FRNR_MASK               (0x0C)
#define DL_FCTR_FRNR_OFFSET             (2)

#define DL_FCTR_ACKNR_MASK              (0x03)
#define DL_FCTR_ACKNR_OFFSET            (0)

// Data Link Layer frame counter max value
#define DL_MAX_FRAME_NUM                (0x03)

// Data link layer length
#define DL_CONTROL_FRAME_LENGTH         (5)

// Setup debug log statements
#if IFX_I2C_LOG_DL == 1
#define LOG_DL IFX_I2C_LOG
#else
#define LOG_DL(...) //printf(__VA_ARGS__)
#endif


/***********************************************************************************************************************
* ENUMS
**********************************************************************************************************************/
/***********************************************************************************************************************
* DATA STRUCTURES
***********************************************************************************************************************/
/***********************************************************************************************************************
* GLOBAL
***********************************************************************************************************************/
/***********************************************************************************************************************
* LOCAL ROUTINES
***********************************************************************************************************************/
/// Helper function to calculate CRC of a byte
_STATIC_H host_lib_status_t ifx_i2c_dl_calc_crc_byte(uint16_t wSeed, uint8_t bByte);
/// Helper function to calculate CRC of a frame
_STATIC_H host_lib_status_t ifx_i2c_dl_calc_crc(const uint8_t* p_data, uint16_t data_len);
/// Internal function to send frame
_STATIC_H host_lib_status_t ifx_i2c_dl_send_frame_internal(ifx_i2c_context_t *p_ctx,uint16_t frame_len,uint8_t seqctr_value, uint8_t resend);
/// Helper function to send resync
_STATIC_H host_lib_status_t ifx_i2c_dl_resync(ifx_i2c_context_t* p_ctx);
/// Helper function to resend frame
_STATIC_H void ifx_i2c_dl_resend_frame(ifx_i2c_context_t* p_ctx,uint8_t seqctr_value);
/// Data Link Layer state machine
_STATIC_H void ifx_i2c_pl_event_handler(ifx_i2c_context_t* p_ctx,host_lib_status_t event, const uint8_t* p_data, uint16_t data_len);

/// @endcond
/***********************************************************************************************************************
* API PROTOTYPES
**********************************************************************************************************************/
host_lib_status_t ifx_i2c_dl_init(ifx_i2c_context_t *p_ctx,ifx_i2c_event_handler_t handler)
{
    LOG_DL("[IFX-DL]: Init\n");
	
    p_ctx->dl.state = DL_STATE_UNINIT;
    // Initialize Physical Layer (and register event handler)
    if (ifx_i2c_pl_init(p_ctx, ifx_i2c_pl_event_handler) != IFX_I2C_STACK_SUCCESS)
    {
        return IFX_I2C_STACK_ERROR;
    }

    // Initialize internal variables
    p_ctx->dl.upper_layer_event_handler = handler;
    p_ctx->dl.state = DL_STATE_IDLE;
    p_ctx->dl.tx_seq_nr = DL_MAX_FRAME_NUM;
    p_ctx->dl.rx_seq_nr = DL_MAX_FRAME_NUM;
    p_ctx->dl.resynced = 0;
    p_ctx->dl.error = 0;
    p_ctx->dl.p_tx_frame_buffer = p_ctx->tx_frame_buffer;
    p_ctx->dl.p_rx_frame_buffer = p_ctx->rx_frame_buffer;

    return IFX_I2C_STACK_SUCCESS;
}

host_lib_status_t ifx_i2c_dl_send_frame(ifx_i2c_context_t *p_ctx,uint16_t frame_len)
{
	LOG_DL("[IFX-DL]: Start TX Frame\n");
    // State must be idle and payload available
    if (p_ctx->dl.state != DL_STATE_IDLE || !frame_len)
    {
        return IFX_I2C_STACK_ERROR;
    }

    p_ctx->dl.state = DL_STATE_TX;
    p_ctx->dl.retransmit_counter = 0;
    p_ctx->dl.action_rx_only = 0;
	p_ctx->dl.tx_buffer_size = frame_len;
    p_ctx->dl.data_poll_timeout = PL_TRANS_TIMEOUT_MS;
    
    return ifx_i2c_dl_send_frame_internal(p_ctx,frame_len, DL_FCTR_SEQCTR_VALUE_ACK, 0);
}

host_lib_status_t ifx_i2c_dl_receive_frame(ifx_i2c_context_t *p_ctx)
{
    LOG_DL("[IFX-DL]: Start RX Frame\n");

    if (p_ctx->dl.state != DL_STATE_IDLE)
    {
        return IFX_I2C_STACK_ERROR;
    }

    // Set internal state
    p_ctx->dl.state = DL_STATE_RX;
    p_ctx->dl.retransmit_counter = 0;
    p_ctx->dl.action_rx_only = 1;
    p_ctx->dl.frame_start_time = pal_os_timer_get_time_in_milliseconds();
    p_ctx->dl.data_poll_timeout = TL_MAX_EXIT_TIMEOUT*1000;

    return ifx_i2c_pl_receive_frame(p_ctx);
}

_STATIC_H host_lib_status_t ifx_i2c_dl_calc_crc_byte(uint16_t wSeed, uint8_t bByte)
{
    uint16_t wh1;
    uint16_t wh2;
    uint16_t wh3;
    uint16_t wh4;

    wh1 = (wSeed ^ bByte) & 0xFF;
    wh2 = wh1 & 0x0F;
    wh3 = ((uint16_t)(wh2 << 4)) ^ wh1;
    wh4 = wh3 >> 4;

    return ((uint16_t)((((uint16_t)((((uint16_t)(wh3 << 1)) ^ wh4) << 4)) ^ wh2) << 3)) ^ wh4
        ^ (wSeed >> 8);
}

_STATIC_H host_lib_status_t ifx_i2c_dl_calc_crc(const uint8_t* p_data, uint16_t data_len)
{
    uint16_t i;
    uint16_t crc = 0;

    for (i = 0; i < data_len; i++)
    {
        crc = ifx_i2c_dl_calc_crc_byte(crc, p_data[i]);
    }

    return crc;
}

_STATIC_H host_lib_status_t ifx_i2c_dl_send_frame_internal(ifx_i2c_context_t *p_ctx,uint16_t frame_len,
    uint8_t seqctr_value, uint8_t resend)
{
    uint16_t crc;
    uint16_t ack_nr = p_ctx->dl.rx_seq_nr;
	uint8_t* p_buffer;

    LOG_DL("[IFX-DL]: TX Frame len %d\n", frame_len);
    // In case of sending a NACK the next frame is referenced
    if (seqctr_value == DL_FCTR_SEQCTR_VALUE_NACK)
    {
        ack_nr = (p_ctx->dl.rx_seq_nr + 1) & DL_MAX_FRAME_NUM;
    }
    if(seqctr_value == DL_FCTR_SEQCTR_VALUE_RESYNC)
    {
        ack_nr = 0;
		// Use rx buffer to send resync
		p_buffer = p_ctx->dl.p_rx_frame_buffer;
    }
	else
	{
		p_buffer = p_ctx->dl.p_tx_frame_buffer;
	}
    // Set sequence control value (ACK or NACK) and referenced frame number
    p_buffer[0] = (uint8_t)(ack_nr << DL_FCTR_ACKNR_OFFSET);
    p_buffer[0] |= (uint8_t)(seqctr_value << DL_FCTR_SEQCTR_OFFSET);

    if (frame_len) // Data frame
    {
        // Increment and set frame transmit sequence number
        if ((!resend)||(p_ctx->dl.resynced))
        {
            p_ctx->dl.tx_seq_nr = (p_ctx->dl.tx_seq_nr + 1) & DL_MAX_FRAME_NUM;
        }
        p_buffer[0] |= (uint8_t)(p_ctx->dl.tx_seq_nr << DL_FCTR_FRNR_OFFSET);
	    // Reset resync received
        p_ctx->dl.resynced = 0;
    }
    else // Control frame
    {
        p_buffer[0] |= DL_FCTR_FTYPE_MASK;
    }

    // Set frame length
    p_buffer[1] = (uint8_t)(frame_len >> 8);
    p_buffer[2] = (uint8_t)frame_len;

    // Calculate frame CRC
    crc = ifx_i2c_dl_calc_crc(p_buffer, 3 + frame_len);
    p_buffer[3 + frame_len] = (uint8_t) (crc >> 8);
    p_buffer[4 + frame_len] = (uint8_t)crc;

    // Transmit frame
    return ifx_i2c_pl_send_frame(p_ctx,p_buffer, DL_HEADER_SIZE + frame_len);
}

_STATIC_H host_lib_status_t ifx_i2c_dl_resync(ifx_i2c_context_t* p_ctx)
{
    host_lib_status_t api_status = IFX_I2C_STACK_SUCCESS;
    // Reset tx and rx counters
    p_ctx->dl.tx_seq_nr = DL_MAX_FRAME_NUM;
    p_ctx->dl.rx_seq_nr = DL_MAX_FRAME_NUM;
    p_ctx->dl.resynced = 1;
    LOG_DL("[IFX-DL]: Send Re-Sync Frame\n"); 
    p_ctx->dl.state = DL_STATE_RESEND;
    api_status = ifx_i2c_dl_send_frame_internal(p_ctx,0,DL_FCTR_SEQCTR_VALUE_RESYNC,0);
    return api_status;
}

_STATIC_H void ifx_i2c_dl_resend_frame(ifx_i2c_context_t* p_ctx,uint8_t seqctr_value)
{
    host_lib_status_t status;
    // If exit timeout not violated
	uint32_t current_time_stamp = pal_os_timer_get_time_in_milliseconds();
    if ((current_time_stamp - p_ctx->tl.api_start_time) < (TL_MAX_EXIT_TIMEOUT * 1000))
    {
        if(p_ctx->dl.retransmit_counter == DL_TRANS_REPEAT)
        {
            LOG_DL("[IFX-DL]: Re-Sync counters\n");  
			p_ctx->dl.retransmit_counter = 0;
            status = ifx_i2c_dl_resync(p_ctx);
        }
        else
        {
			LOG_DL("[IFX-DL]: Re-TX Frame\n");
			p_ctx->dl.retransmit_counter++;            
            p_ctx->dl.state = DL_STATE_TX;
            status = ifx_i2c_dl_send_frame_internal(p_ctx,p_ctx->dl.tx_buffer_size,seqctr_value, 1);           
        }
        // Handle error in above case by sending NACK
        if (IFX_I2C_STACK_SUCCESS != status)
        {
            p_ctx->dl.state  = DL_STATE_NACK;
        }
    }
    else
    {
        p_ctx->dl.state = DL_STATE_ERROR;
    }
}

_STATIC_H void ifx_i2c_pl_event_handler(ifx_i2c_context_t* p_ctx,host_lib_status_t event, const uint8_t* p_data, uint16_t data_len)
{
    uint8_t fctr = 0;
    uint8_t fr_nr = 0;
    uint8_t ack_nr = 0;
    uint8_t seqctr = 0;
    uint8_t current_event;
    uint8_t ftype;
    uint8_t continue_state_machine = TRUE;
    uint16_t packet_len = 0;
    uint16_t crc_received = 0;
    uint16_t crc_calculated = 0;
    LOG_DL("[IFX-DL]: #Enter DL Handler\n");
    do
    {
        if((event == IFX_I2C_FATAL_ERROR) && (DL_STATE_IDLE != p_ctx->dl.state))
        {	// Exit in case of fatal error
            LOG_DL("[IFX-DL]: Fatal error received\n");
            p_ctx->dl.state = DL_STATE_ERROR;
        }
        switch(p_ctx->dl.state)
        {
            case DL_STATE_IDLE:
            {
                current_event = (event != IFX_I2C_STACK_SUCCESS)?IFX_I2C_DL_EVENT_ERROR:IFX_I2C_DL_EVENT_TX_SUCCESS;
                continue_state_machine = FALSE;
                p_ctx->dl.upper_layer_event_handler(p_ctx,current_event, 0, 0);
            }      
            break;
            case DL_STATE_TX:
            {
                // If writing a frame failed retry sending
                if (event == IFX_I2C_STACK_ERROR)
                {
                    p_ctx->dl.state = DL_STATE_RESEND;
                    break;
                }
                LOG_DL("[IFX-DL]: Frame Sent\n");	
                // Transmission successful, start receiving frame
                p_ctx->dl.frame_start_time = pal_os_timer_get_time_in_milliseconds();
                p_ctx->dl.state = DL_STATE_RX;
                if (ifx_i2c_pl_receive_frame(p_ctx))
                {
                    p_ctx->dl.state  = DL_STATE_NACK;
                }
                else
                {
                    continue_state_machine = FALSE;
                }
            }
            break;
            case DL_STATE_RX:
            {
                if (event == IFX_I2C_STACK_ERROR)
                {	// If no frame was received retry sending
                    p_ctx->dl.state = DL_STATE_RESEND;
                    break;
                }
                // Received frame from device, start analyzing
                LOG_DL("[IFX-DL]: Received Frame of length %d\n",data_len);

                if (data_len < DL_HEADER_SIZE)
                {	// Received length is less than minimum size
                    LOG_DL("[IFX-DL]: received data_len < DL_HEADER_SIZE\n");
                    p_ctx->dl.state  = DL_STATE_NACK;
                    break;
                }              
                // Check transmit frame sequence number
                fctr = p_data[0];
                ftype = (fctr & DL_FCTR_FTYPE_MASK) >> DL_FCTR_FTYPE_OFFSET;
                seqctr = (fctr & DL_FCTR_SEQCTR_MASK) >> DL_FCTR_SEQCTR_OFFSET;
                ack_nr = (fctr & DL_FCTR_ACKNR_MASK) >> DL_FCTR_ACKNR_OFFSET;
                fr_nr = (fctr & DL_FCTR_FRNR_MASK) >> DL_FCTR_FRNR_OFFSET;
                packet_len = (p_data[1] << 8) | p_data[2];

                // Check frame CRC value
                crc_received = (p_data[data_len - 2] << 8) | p_data[data_len - 1];
                crc_calculated = ifx_i2c_dl_calc_crc(p_data, data_len - 2);              	
                p_ctx->dl.state = (ftype == DL_FCTR_VALUE_CONTROL_FRAME)?DL_STATE_RX_CF:DL_STATE_RX_DF;             
            }
            break;
            case DL_STATE_RX_DF:
            {
                LOG_DL("[IFX-DL]: Data Frame Received\n");			
                if ((crc_received != crc_calculated)||(packet_len == 0)||(data_len != DL_HEADER_SIZE + packet_len)||
                    (seqctr == DL_FCTR_SEQCTR_VALUE_RFU) ||	(seqctr == DL_FCTR_SEQCTR_VALUE_RESYNC))
                {	
                    // CRC,Length of data frame is 0/ SEQCTR has RFU/Re-sync in Data frame
                    LOG_DL("[IFX-DL]: NACK for CRC error,Data frame length is not correct,RFU in SEQCTR\n");
                    p_ctx->dl.state  = DL_STATE_NACK;
                    break;
                }
                if (fr_nr != ((p_ctx->dl.rx_seq_nr + 1) & DL_MAX_FRAME_NUM))
                {
                    LOG_DL("[IFX-DL]: Data frame number not expected\n");
                    p_ctx->dl.state  = DL_STATE_DISCARD;
                    continue_state_machine = FALSE;
                    //lint --e{534} suppress "Return value is not required to be checked"
                    ifx_i2c_dl_send_frame_internal(p_ctx,0, DL_FCTR_SEQCTR_VALUE_ACK, 0);
                    break;
                }				
                if (ack_nr != p_ctx->dl.tx_seq_nr)
                {	
                    // ack number error
                    LOG_DL("[IFX-DL]: Error in ack number\n");
                    //lint --e{534} suppress "Return value is not required to be checked"
                    p_ctx->dl.state = DL_STATE_DISCARD;
                    break;
                }				
                if (seqctr == DL_FCTR_SEQCTR_VALUE_NACK)
                {	
                    // NACK for transmitted frame
                    LOG_DL("[IFX-DL]: NACK received in data frame\n");
                    p_ctx->dl.state = DL_STATE_RESEND;		
                    break;	
                }
                p_ctx->dl.rx_seq_nr = (p_ctx->dl.rx_seq_nr + 1) & DL_MAX_FRAME_NUM;                  
                memcpy(p_ctx->dl.p_rx_frame_buffer, p_data, data_len);
                p_ctx->dl.rx_buffer_size = data_len;

                // Send control frame to acknowledge reception of this data frame
                LOG_DL("[IFX-DL]: Read Data Frame -> Send ACK\n");
                p_ctx->dl.retransmit_counter = 0;
                p_ctx->dl.state = DL_STATE_ACK;				
                continue_state_machine = FALSE;
                //lint --e{534} suppress "Return value is not required to be checked"
                ifx_i2c_dl_send_frame_internal(p_ctx,0, DL_FCTR_SEQCTR_VALUE_ACK, 0);
            }
            break;
            case DL_STATE_RX_CF:
            {
                LOG_DL("[IFX-DL]: Control Frame Received\n");		               
                // Discard Control frame when in receiver mode except for Re-Sync
                //lint --e{514} suppress "The check is intended to be done this way"
                if((p_ctx->dl.action_rx_only) ^ (seqctr == DL_FCTR_SEQCTR_VALUE_RESYNC))
                {	
                    //If control frame already received for data frame, ignore any received control frame
                    LOG_DL("[IFX-DL]: CF in receiver mode,Discard\n");
                    p_ctx->dl.state = DL_STATE_DISCARD;
                    break;
                }
                if (crc_received != crc_calculated)
                {	
                    // Re-Transmit frame in case of CF CRC error
                    LOG_DL("[IFX-DL]: Retransmit frame for CF CRC error\n");
                    p_ctx->dl.state = DL_STATE_RESEND;
                    break;
                }
                if((data_len > DL_CONTROL_FRAME_LENGTH)||(packet_len != 0))
                {	
                    // Control frame is more than 5/Control frame with non-zero FRNR/packet len is not 0
                    LOG_DL("[IFX-DL]: Errors in control frame\n");
                    p_ctx->dl.state = DL_STATE_DISCARD;
                    break;
                }
                if(seqctr == DL_FCTR_SEQCTR_VALUE_RESYNC)
                {	// Re-sync received
                    LOG_DL("[IFX-DL]: Re-Sync received\n");
                    p_ctx->dl.state = DL_STATE_DISCARD;
                    p_ctx->dl.resynced = 1;
                    p_ctx->dl.tx_seq_nr = DL_MAX_FRAME_NUM;
                    p_ctx->dl.rx_seq_nr = DL_MAX_FRAME_NUM;
                    break;
                }
                if((fr_nr!=0)||(seqctr == DL_FCTR_SEQCTR_VALUE_RFU)||(ack_nr != p_ctx->dl.tx_seq_nr))
                {	
                    // Control frame with non-zero FRNR/ ACK not received/ ack number != tx number
                    LOG_DL("[IFX-DL]: Errors in control frame\n");
                    p_ctx->dl.state = DL_STATE_DISCARD;
                    break;
                }               
                if (seqctr == DL_FCTR_SEQCTR_VALUE_NACK)
                {	
                    // NACK for transmitted frame
                    LOG_DL("[IFX-DL]: NACK received\n");
                    p_ctx->dl.state = DL_STATE_RESEND;		
                    break;	
                }	
                
                LOG_DL("[IFX-DL]: ACK received\n");
                // Report frame reception to upper layer and go in idle state
                p_ctx->dl.state = DL_STATE_IDLE;
                continue_state_machine = FALSE;  
                p_ctx->dl.upper_layer_event_handler(p_ctx,IFX_I2C_DL_EVENT_TX_SUCCESS, 0, 0);
            }
            break;
            case DL_STATE_DISCARD:
            {
                LOG_DL("[IFX-DL]: Discard frame\n");
                p_ctx->dl.state = DL_STATE_RX;
                continue_state_machine = FALSE;
                //lint --e{534} suppress "Return value is not required to be checked"
                ifx_i2c_pl_receive_frame(p_ctx);
            }            
            break;
            case DL_STATE_ACK:
            {
                LOG_DL("[IFX-DL]: ACK sent\n");
                if (event == IFX_I2C_STACK_ERROR)
                {	
                    // If writing the ACK frame failed, Re-Send
                    LOG_DL("[IFX-DL]: Physical Layer error -> Resend ACK\n");
                    p_ctx->dl.state = DL_STATE_RESEND;
                    break;
                }
                // Control frame successful transmitted
                p_ctx->dl.state = DL_STATE_IDLE;                  
                continue_state_machine = FALSE;
                if (p_ctx->dl.action_rx_only)
                {
                    p_ctx->dl.upper_layer_event_handler(p_ctx,IFX_I2C_DL_EVENT_RX_SUCCESS, p_ctx->dl.p_rx_frame_buffer + 3,
                    p_ctx->dl.rx_buffer_size - DL_HEADER_SIZE); 
                }
                else
                {
                    p_ctx->dl.upper_layer_event_handler(p_ctx,IFX_I2C_DL_EVENT_TX_SUCCESS | IFX_I2C_DL_EVENT_RX_SUCCESS,
                    p_ctx->dl.p_rx_frame_buffer + 3, p_ctx->dl.rx_buffer_size - DL_HEADER_SIZE);
                }
            }
            break;           
            case DL_STATE_NACK:
            {	
                // Sending NACK
                LOG_DL("[IFX-DL]: Sending NACK\n");
                p_ctx->dl.state = DL_STATE_TX;
                continue_state_machine = FALSE;
                //lint --e{534} suppress "Return value is not required to be checked"
                ifx_i2c_dl_send_frame_internal(p_ctx,0, DL_FCTR_SEQCTR_VALUE_NACK, 0);
            }
            break;		                    
            case DL_STATE_RESEND:
            {	
                //Resend frame
                ifx_i2c_dl_resend_frame(p_ctx,DL_FCTR_SEQCTR_VALUE_ACK);   
                if(p_ctx->dl.state != DL_STATE_ERROR)
                {
                    continue_state_machine = FALSE;
                }
            }
            break;           
            case DL_STATE_ERROR:
            {
				if(!p_ctx->dl.resynced)
				{
					p_ctx->dl.error = 1;
				}
                if(0 == p_ctx->dl.error)
                {
                    LOG_DL("[IFX-DL]: Exit error after fatal error\n");
                    //After sending resync, inform upper layer
                    p_ctx->dl.state = DL_STATE_IDLE;
                    p_ctx->dl.upper_layer_event_handler(p_ctx,IFX_I2C_DL_EVENT_ERROR, 0, 0);  
                }
                else
                {
                    LOG_DL("[IFX-DL]: Sending re-sync after fatal error\n");
                    // Send re-sync to slave on error
                    //lint --e{534} suppress "As this is last step, no effect of checking return code"
                    ifx_i2c_dl_resync(p_ctx);
					p_ctx->dl.state = DL_STATE_ERROR;
                    p_ctx->dl.error = 0;
                } 
                continue_state_machine = FALSE;
            }
            break;
            default:
                LOG_DL("[IFX-DL]: Default condition occurred. Exiting with error\n");
                p_ctx->dl.state = DL_STATE_IDLE;
                p_ctx->dl.upper_layer_event_handler(p_ctx,IFX_I2C_DL_EVENT_ERROR, 0, 0);
                continue_state_machine = FALSE;
                break;                
        }
    }while(continue_state_machine == TRUE);
    LOG_DL("[IFX-DL]: #Exiting DL Handler\n");
}
