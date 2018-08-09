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
* \file ifx_i2c_physical_layer.c
*
* \brief   This file implements the IFX I2C Physical Layer.
*
* \addtogroup  grIFXI2C
* @{
*/

/***********************************************************************************************************************
* HEADER FILES
**********************************************************************************************************************/
#include "ifx_i2c_physical_layer.h"
#include "pal_os_event.h"

/// @cond hidden
/***********************************************************************************************************************
* MACROS
**********************************************************************************************************************/
// Physical Layer Register addresses
#define PL_REG_DATA                     (0x80)
#define PL_REG_DATA_REG_LEN             (0x81)
#define PL_REG_I2C_STATE                (0x82)
#define PL_REG_BASE_ADDR                (0x83)
#define PL_REG_MAX_SCL_FREQU            (0x84)
#define PL_REG_SOFT_RESET               (0x88)
#define PL_REG_I2C_MODE                 (0x89)
                                        
// Physical Layer Register lengths      
#define PL_REG_LEN_I2C_STATE            (4)
#define PL_REG_LEN_MAX_SCL_FREQU        (4)
#define PL_REG_LEN_I2C_MODE             (2)
#define PL_REG_LEN_DATA_REG_LEN         (2)
#define PL_REG_LEN_SOFT_RESET			(2)
#define PL_REG_LEN_BASE_ADDR			(2)

// Physical Layer State Register masks
#define PL_REG_I2C_STATE_RESPONSE_READY (0x40)
#define PL_REG_I2C_STATE_SOFT_RESET     (0x08)

// Physical Layer low level interface constants
#define PL_ACTION_READ_REGISTER         (0x01)
#define PL_ACTION_WRITE_REGISTER        (0x02)
#define PL_I2C_CMD_WRITE                (0x01)
#define PL_I2C_CMD_READ                 (0x02)

// Physical Layer high level interface constants
#define PL_ACTION_WRITE_FRAME           (0x01)
#define PL_ACTION_READ_FRAME            (0x02)
#define PL_STATE_UNINIT                 (0x00)
#define PL_STATE_INIT                   (0x01)
#define PL_STATE_READY                  (0x02)
#define PL_STATE_DATA_AVAILABLE         (0x03)
#define PL_STATE_RXTX                   (0x04)
#define PL_STATE_SOFT_RESET             (0x05)
    
//Physical Layer negotiation constants
#define PL_INIT_SET_DATA_REG_LEN        (0x11)
#define PL_INIT_GET_DATA_REG_LEN        (0x22)
#define PL_INIT_GET_FREQ_REG            (0x33)
#define PL_INIT_SET_FREQ_REG            (0x44)
#define PL_INIT_READ_FREQ               (0x55)
#define PL_INIT_VERIFY_FREQ             (0x66)
#define PL_INIT_AGREE_FREQ              (0x77)
#define PL_INIT_VERIFY_DATA_REG         (0x88)
#define PL_INIT_GET_STATUS_REG          (0x99)
#define PL_INIT_DONE                    (0xAA)
#define PL_INIT_SET_FREQ_DEFAULT        (0xBB)

//Physical layer soft reset states
#define PL_RESET_INIT                   (0xA1)
#define PL_RESET_WRITE                  (0xA2)
#define PL_RESET_STARTUP                (0xA3)

#define PL_REG_I2C_MODE_PERSISTANT      (0x80)
#define PL_REG_I2C_MODE_SM_FM           (0x03)
#define PL_REG_I2C_MODE_FM_PLUS         (0x04)
#define PL_SM_FM_MAX_FREQUENCY          (0x190)
#define PL_DEFAULT_FREQUENCY            (0x64)
#define PL_REG_BASE_ADDR_PERSISTANT     (0x80)
#define PL_REG_BASE_ADDR_VOLATILE       (0x00)

// Physical Layer Base Address Register mask
#define PL_REG_I2C_BASE_ADDRESS_MASK     (0x7F)

// Setup debug log statements
#if IFX_I2C_LOG_PL == 1
#define LOG_PL IFX_I2C_LOG
#else
#define LOG_PL(...) //printf(__VA_ARGS__)
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

static host_lib_status_t pal_event_status;

/***********************************************************************************************************************
* LOCAL ROUTINES
***********************************************************************************************************************/
/// Physical Layer low level interface function
static void ifx_i2c_pl_read_register(ifx_i2c_context_t *p_ctx,uint8_t reg_addr, uint16_t reg_len);
/// Physical Layer low level interface function
static void ifx_i2c_pl_write_register(ifx_i2c_context_t *p_ctx,uint8_t reg_addr, uint16_t reg_len, const uint8_t* p_content);
/// Physical Layer high level interface timer callback (Status register polling)
static void ifx_i2c_pl_status_poll_callback(void *p_ctx);
/// Physical Layer intermediate state machine (Negotiation with slave)
static void ifx_i2c_pl_negotiation_event_handler(void *p_input_ctx);
/// Physical Layer intermediate state machine(Set bit rate)
static host_lib_status_t ifx_i2c_pl_set_bit_rate(ifx_i2c_context_t *p_ctx, uint16_t bitrate);
/// Physical Layer intermediate state machine (soft reset)
static void ifx_i2c_pl_soft_reset(ifx_i2c_context_t *p_ctx);
/// Physical Layer high level interface state machine (read/write frames)
static void ifx_i2c_pl_frame_event_handler(ifx_i2c_context_t *p_ctx,host_lib_status_t event);
/// Physical Layer low level interface timer callback (I2C Nack/Busy polling)
static void ifx_i2c_pal_poll_callback(void *p_ctx);
/// Physical Layer low level guard time callback
static void ifx_i2c_pl_guard_time_callback(void *p_ctx);
/// Physical Layer low level interface state machine (read/write registers)
static void ifx_i2c_pl_pal_event_handler(void *p_ctx, host_lib_status_t event);
/// Physical layer low level event handler for set slave address
static void ifx_i2c_pl_pal_slave_addr_event_handler(void *p_input_ctx, host_lib_status_t event);
  
/// @endcond
/***********************************************************************************************************************
* API PROTOTYPES
**********************************************************************************************************************/
/// Physical Layer high level interface function
host_lib_status_t ifx_i2c_pl_init(ifx_i2c_context_t *p_ctx,ifx_i2c_event_handler_t handler)
{
    LOG_PL("[IFX-PL]: Init\n");
	        
    p_ctx->pl.upper_layer_event_handler = handler;
    p_ctx->pl.frame_state = PL_STATE_UNINIT;
    p_ctx->pl.negotiate_state = PL_INIT_SET_FREQ_DEFAULT;
    p_ctx->p_pal_i2c_ctx->slave_address = p_ctx->slave_address;
    p_ctx->p_pal_i2c_ctx->upper_layer_event_handler = (void *) ifx_i2c_pl_pal_event_handler;
    p_ctx->pl.retry_counter = PL_POLLING_MAX_CNT;
    if(TRUE == p_ctx->do_pal_init)
    {
        // Initialize I2C driver
        if (PAL_STATUS_SUCCESS != pal_i2c_init(p_ctx->p_pal_i2c_ctx))
        {
            return IFX_I2C_STACK_ERROR;
        }
    }
    // Set Physical Layer internal state
    if(p_ctx->pl.request_soft_reset == (uint8_t)TRUE)
    {
		//Set the soft reset request to initial state to read register
		p_ctx->pl.request_soft_reset = PL_INIT_GET_STATUS_REG;
        p_ctx->pl.frame_state = PL_STATE_SOFT_RESET;
    }
    else
    {
        p_ctx->pl.frame_state = PL_STATE_INIT;       
    }
    
    ifx_i2c_pl_frame_event_handler(p_ctx,IFX_I2C_STACK_SUCCESS);
    
    return IFX_I2C_STACK_SUCCESS;
}

/// Physical Layer high level interface function
host_lib_status_t ifx_i2c_pl_send_frame(ifx_i2c_context_t *p_ctx,uint8_t* p_frame, uint16_t frame_len)
{
    // Physical Layer must be idle, set requested action
    if (p_ctx->pl.frame_state != PL_STATE_INIT && p_ctx->pl.frame_state != PL_STATE_READY)
    {
        return IFX_I2C_STACK_ERROR;
    }
    p_ctx->pl.frame_action = PL_ACTION_WRITE_FRAME;

    // Store reference to frame for sending it later
    p_ctx->pl.p_tx_frame   = p_frame;
    p_ctx->pl.tx_frame_len = frame_len;

    ifx_i2c_pl_frame_event_handler(p_ctx,IFX_I2C_STACK_SUCCESS);
    return IFX_I2C_STACK_SUCCESS;
}

/// Physical Layer high level interface function
host_lib_status_t ifx_i2c_pl_receive_frame(ifx_i2c_context_t *p_ctx)
{
    // Physical Layer must be idle, set requested action
    if (p_ctx->pl.frame_state != PL_STATE_INIT && p_ctx->pl.frame_state != PL_STATE_READY)
    {
        return IFX_I2C_STACK_ERROR;
    }
    p_ctx->pl.frame_action = PL_ACTION_READ_FRAME;

    ifx_i2c_pl_frame_event_handler(p_ctx,IFX_I2C_STACK_SUCCESS);
    return IFX_I2C_STACK_SUCCESS;
}

host_lib_status_t ifx_i2c_pl_write_slave_address(ifx_i2c_context_t *p_ctx, uint8_t slave_address, uint8_t persistent)
{    
    host_lib_status_t status = IFX_I2C_STACK_ERROR;
    app_event_handler_t * temp_upper_layer_event_handler;

    /// @cond hidden
    #define PAL_WRITE_INIT_STATUS      (0x00FF)
    #define ADDRESS_OFFSET              (0x02)
    #define BASE_ADDRESS_REG_OFFSET     (0x00)
    #define MODE_OFFSET                 (0x01)
    #define POLLING_INTERVAL            (0x01)
    #define DELAY_FOR_COMPLETION        (0x0A)
    /// @endcond

    //lint --e{611} suppress "void* function pointer is type casted to app_event_handler_t type"
    //ifx i2c wrapper api for setting slave address in synchronous. hence the event handler is backed up.
    temp_upper_layer_event_handler = (app_event_handler_t *)(p_ctx->p_pal_i2c_ctx->upper_layer_event_handler);
    //since the lower level APIs are asynchronous, a temporary event handler for set slave address is assigned
    p_ctx->p_pal_i2c_ctx->upper_layer_event_handler = (void *) ifx_i2c_pl_pal_slave_addr_event_handler;

    p_ctx->pl.buffer[BASE_ADDRESS_REG_OFFSET] = PL_REG_BASE_ADDR;
    p_ctx->pl.buffer[MODE_OFFSET] = PL_REG_BASE_ADDR_VOLATILE;
    //supported base addresses are 0x00 - 0x7F. Hence 8th bit is ignored
    p_ctx->pl.buffer[ADDRESS_OFFSET] = slave_address & PL_REG_I2C_BASE_ADDRESS_MASK;
    p_ctx->pl.buffer_tx_len = 1 + PL_REG_LEN_BASE_ADDR;

    if(PL_REG_BASE_ADDR_VOLATILE != persistent)
    {
        p_ctx->pl.buffer[MODE_OFFSET] = PL_REG_BASE_ADDR_PERSISTANT;
    }

    p_ctx->pl.retry_counter   = PL_POLLING_MAX_CNT;

    while(p_ctx->pl.retry_counter)
    {
        pal_event_status = PAL_WRITE_INIT_STATUS;

        //lint --e{534} suppress "Return value is not required to be checked"
        pal_i2c_write(p_ctx->p_pal_i2c_ctx,p_ctx->pl.buffer, p_ctx->pl.buffer_tx_len);
        while(PAL_WRITE_INIT_STATUS == pal_event_status){};
        if(PAL_I2C_EVENT_SUCCESS == pal_event_status)
        {
            break;
        }
        p_ctx->pl.retry_counter--;
        pal_os_timer_delay_in_milliseconds(POLLING_INTERVAL);
    }

    if(PAL_I2C_EVENT_SUCCESS == pal_event_status)
    {
        p_ctx->p_pal_i2c_ctx->slave_address = p_ctx->pl.buffer[ADDRESS_OFFSET];
        if(PL_REG_BASE_ADDR_VOLATILE != persistent)
        {
            p_ctx->slave_address = p_ctx->pl.buffer[ADDRESS_OFFSET];
        }
        pal_os_timer_delay_in_milliseconds(DELAY_FOR_COMPLETION);
        status = IFX_I2C_STACK_SUCCESS;
    }
    //restoring the backed up event handler 
    p_ctx->p_pal_i2c_ctx->upper_layer_event_handler = temp_upper_layer_event_handler;
        
    /// @cond hidden
    #undef PAL_WRITE_INIT_STATUS
    #undef ADDRESS_OFFSET 
    #undef BASE_ADDRESS_REG_OFFSET 
    #undef MODE_OFFSET
    #undef POLLING_INTERVAL
    #undef DELAY_FOR_COMPLETION
    /// @endcond
    
    return status;
}

static void ifx_i2c_pl_read_register(ifx_i2c_context_t *p_ctx,uint8_t reg_addr, uint16_t reg_len)
{
    LOG_PL("[IFX-PL]: Read register %x len %d\n", reg_addr, reg_len);

    // Prepare transmit buffer to write register address
    p_ctx->pl.buffer[0]     = reg_addr;
    p_ctx->pl.buffer_tx_len = 1;

    // Set low level interface variables and start transmission
    p_ctx->pl.buffer_rx_len   = reg_len;
    p_ctx->pl.register_action = PL_ACTION_READ_REGISTER;
    p_ctx->pl.retry_counter   = PL_POLLING_MAX_CNT;
    p_ctx->pl.i2c_cmd         = PL_I2C_CMD_WRITE;

    //lint --e{534} suppress "Return value is not required to be checked"
    pal_i2c_write(p_ctx->p_pal_i2c_ctx,p_ctx->pl.buffer, p_ctx->pl.buffer_tx_len);
}


static void ifx_i2c_pl_write_register(ifx_i2c_context_t *p_ctx,uint8_t reg_addr, uint16_t reg_len, const uint8_t* p_content)
{
    LOG_PL("[IFX-PL]: Write register %x len %d\n", reg_addr, reg_len);

    // Prepare transmit buffer to write register address and content
    p_ctx->pl.buffer[0] = reg_addr;
    memcpy(p_ctx->pl.buffer + 1, p_content, reg_len);
    p_ctx->pl.buffer_tx_len = 1 + reg_len;

    // Set Physical Layer low level interface variables and start transmission
    p_ctx->pl.register_action = PL_ACTION_WRITE_REGISTER;
    p_ctx->pl.retry_counter   = PL_POLLING_MAX_CNT;
    p_ctx->pl.i2c_cmd         = PL_I2C_CMD_WRITE;
    //lint --e{534} suppress "Return value is not required to be checked"
    pal_i2c_write(p_ctx->p_pal_i2c_ctx,p_ctx->pl.buffer, p_ctx->pl.buffer_tx_len);
}


static void ifx_i2c_pl_status_poll_callback(void *p_ctx)
{
    LOG_PL("[IFX-PL]: Status poll Timer elapsed  -> Read STATUS register\n");
    ifx_i2c_pl_read_register((ifx_i2c_context_t*)p_ctx,PL_REG_I2C_STATE, PL_REG_LEN_I2C_STATE);
}

static host_lib_status_t ifx_i2c_pl_set_bit_rate(ifx_i2c_context_t *p_ctx, uint16_t bitrate)
{
    host_lib_status_t status;
    void* pal_ctx_upper_layer_handler;
    // Save upper layer context in pal
    pal_ctx_upper_layer_handler = p_ctx->p_pal_i2c_ctx->upper_layer_event_handler;   
    // Pass context as NULL to avoid callback invocation
    p_ctx->p_pal_i2c_ctx->upper_layer_event_handler  = NULL;
    status = pal_i2c_set_bitrate(p_ctx->p_pal_i2c_ctx , bitrate);    
    // Restore callback
    p_ctx->p_pal_i2c_ctx->upper_layer_event_handler  = pal_ctx_upper_layer_handler;
    if(PAL_I2C_EVENT_SUCCESS != status)
    {
        if (p_ctx->pl.retry_counter--)
        {
            LOG_PL("[IFX-PL]: Set bit rate failed, Retry setting.\n");
            pal_os_event_register_callback_oneshot(ifx_i2c_pl_negotiation_event_handler,((void*)p_ctx),PL_POLLING_INVERVAL_US);
            status = IFX_I2C_STACK_BUSY;
        }
        else
        {
           status = IFX_I2C_STACK_ERROR;
        }
    }
    else
    {
        status = IFX_I2C_STACK_SUCCESS;
    }
     
    return status;
    
}
static void ifx_i2c_pl_negotiation_event_handler(void *p_input_ctx)
{
    host_lib_status_t event = (uint8_t)IFX_I2C_STACK_ERROR;
    uint8_t continue_negotiation;
    ifx_i2c_context_t* p_ctx = (ifx_i2c_context_t*)p_input_ctx;
	uint8_t i2c_mode_value[2];
    uint8_t max_frame_size[2] = { (uint8_t)(p_ctx->frame_size >> 8), (uint8_t)(p_ctx->frame_size) };
    uint16_t buffer_len = 0;
    uint16_t slave_frequency;
	uint16_t slave_frame_len;
    uint8_t* p_buffer = NULL;
    
    do
    {
        continue_negotiation = FALSE;
        LOG_PL("[IFX-PL]: Negotiation started\n");
        switch(p_ctx->pl.negotiate_state)
        {
            // Set initial frequency to PL_DEFAULT_FREQUENCY to be able to negotiate with slave
            case PL_INIT_SET_FREQ_DEFAULT:
            {
                // Default frequency set to master
                event = ifx_i2c_pl_set_bit_rate(p_input_ctx,PL_DEFAULT_FREQUENCY);
                if(IFX_I2C_STACK_SUCCESS == event)
                {
                    p_ctx->pl.negotiate_state = PL_INIT_GET_FREQ_REG;
                    continue_negotiation = TRUE;
                }
                else if (IFX_I2C_STACK_ERROR == event)
                {
                    p_ctx->pl.negotiate_state = PL_INIT_DONE;
                    p_buffer = NULL;
                    buffer_len = 0;
                }               
            }
            break;
            // Read the current Max frequency supported by slave
            case PL_INIT_GET_FREQ_REG:
            {
                p_ctx->pl.negotiate_state = PL_INIT_SET_FREQ_REG;
                ifx_i2c_pl_read_register(p_ctx,PL_REG_MAX_SCL_FREQU, PL_REG_LEN_MAX_SCL_FREQU);
            }
            break;
            // Set the I2C mode register
            case PL_INIT_SET_FREQ_REG:
            {                          
                slave_frequency = (p_ctx->pl.buffer[2] << 8) | p_ctx->pl.buffer[3];
                
                i2c_mode_value[0] = PL_REG_I2C_MODE_PERSISTANT;
                if((p_ctx->frequency > PL_SM_FM_MAX_FREQUENCY)&&(slave_frequency<=PL_SM_FM_MAX_FREQUENCY))
                {
                    //Change to FM+ mode if slave's current supported frequency is below user's requested frequency
                    i2c_mode_value[1] = PL_REG_I2C_MODE_FM_PLUS;
                    p_ctx->pl.negotiate_state = PL_INIT_READ_FREQ;
                    ifx_i2c_pl_write_register(p_ctx,PL_REG_I2C_MODE, PL_REG_LEN_I2C_MODE, i2c_mode_value);
                }
                else if((p_ctx->frequency <= PL_SM_FM_MAX_FREQUENCY)&&(slave_frequency>PL_SM_FM_MAX_FREQUENCY))
                {
                    //Change to SM&FM mode if slave's current supported frequency is above user's requested frequency
                    i2c_mode_value[1] = PL_REG_I2C_MODE_SM_FM;
                    p_ctx->pl.negotiate_state = PL_INIT_READ_FREQ;
                    ifx_i2c_pl_write_register(p_ctx,PL_REG_I2C_MODE, PL_REG_LEN_I2C_MODE, i2c_mode_value);
                }
                else
                {
                    p_ctx->pl.negotiate_state = PL_INIT_VERIFY_FREQ;
					continue_negotiation = TRUE;
                }                         
            }
            break;
            // After setting I2C mode register, read the slave's supported frequency
            case PL_INIT_READ_FREQ:
            {
                p_ctx->pl.negotiate_state = PL_INIT_VERIFY_FREQ;
                ifx_i2c_pl_read_register(p_ctx,PL_REG_MAX_SCL_FREQU, PL_REG_LEN_MAX_SCL_FREQU);
            }
            break;
            // Verify the requested frequency and slave's supported frequency    
            case PL_INIT_VERIFY_FREQ:
            {
                slave_frequency = (p_ctx->pl.buffer[2] << 8) | p_ctx->pl.buffer[3];
                if(p_ctx->frequency > slave_frequency)
                {
                    LOG_PL("[IFX-PL]: Unexpected frequency in MAX_SCL_FREQU\n");
                    p_buffer = NULL;
                    buffer_len = 0;
                    p_ctx->pl.negotiate_state = PL_INIT_DONE;
                }
                else
                {
                    p_ctx->pl.negotiate_state = PL_INIT_AGREE_FREQ;
                }
                continue_negotiation = TRUE;
            } 
            break; 
            // Frequency negotiated, Set frequency at master
            case PL_INIT_AGREE_FREQ:
            {
                // Frequency negotiation between master and slave is complete
                event = ifx_i2c_pl_set_bit_rate(p_input_ctx, p_ctx->frequency);
                if(IFX_I2C_STACK_SUCCESS == event)
                {
                    p_ctx->pl.negotiate_state = PL_INIT_SET_DATA_REG_LEN;
                    continue_negotiation = TRUE;
                }
                else if (IFX_I2C_STACK_ERROR == event)
                {
                    p_ctx->pl.negotiate_state = PL_INIT_DONE;
                    p_buffer = NULL;
                    buffer_len = 0;
                }              
            }
            break;    
            // Start frame length negotiation by writing the requested frame length
            case PL_INIT_SET_DATA_REG_LEN:
            {
                p_ctx->pl.negotiate_state = PL_INIT_GET_DATA_REG_LEN;
                ifx_i2c_pl_write_register(p_ctx,PL_REG_DATA_REG_LEN, sizeof(max_frame_size), max_frame_size);
            }
            break;
            // Read the frame length to verify
            case PL_INIT_GET_DATA_REG_LEN:
            {
                p_ctx->pl.negotiate_state = PL_INIT_VERIFY_DATA_REG;
                ifx_i2c_pl_read_register(p_ctx,PL_REG_DATA_REG_LEN,PL_REG_LEN_DATA_REG_LEN);
            }
            break;
            // Check is slave accepted the new frame length
            case PL_INIT_VERIFY_DATA_REG:
            {
				p_ctx->pl.negotiate_state = PL_INIT_DONE;
				slave_frame_len = (p_ctx->pl.buffer[0] << 8) | p_ctx->pl.buffer[1]; 
                // Error if slave's frame length is more than requested frame length
				if(p_ctx->frame_size >= slave_frame_len)
				{
					p_ctx->frame_size = slave_frame_len;
					event = IFX_I2C_STACK_SUCCESS;
				}
                p_buffer = NULL;
                buffer_len = 0;
				continue_negotiation = TRUE;
            }
            break;
            case PL_INIT_DONE:
            {   
                if(IFX_I2C_STACK_SUCCESS == event)
                {                
                    p_ctx->pl.frame_state = PL_STATE_READY;
                }
                else
                {
                    p_ctx->pl.frame_state = PL_STATE_UNINIT;
                }
                // Negotiation between master and slave is complete
                p_ctx->pl.upper_layer_event_handler(p_ctx,event, p_buffer, buffer_len);
            }
            break;
            default:
                break;    
        }  
    }while(continue_negotiation);
}


static void ifx_i2c_pl_frame_event_handler(ifx_i2c_context_t *p_ctx,host_lib_status_t event)
{
    uint16_t frame_size;
    if (event != IFX_I2C_STACK_SUCCESS)
    {
        p_ctx->pl.frame_state = PL_STATE_READY;
        // I2C read or write failed, report to upper layer
        p_ctx->pl.upper_layer_event_handler(p_ctx,event, 0, 0);
    }
    else
    {  
        switch(p_ctx->pl.frame_state)
        {
            // Perform soft reset
            case PL_STATE_SOFT_RESET:
            {			
                ifx_i2c_pl_soft_reset(p_ctx);
            }
            break;
            // Negotiate frame and frequency with slave
            case PL_STATE_INIT:
            {
                ifx_i2c_pl_negotiation_event_handler(p_ctx);
            }
            break;
            // Check status of slave data
            case PL_STATE_READY:
            {
                // Start polling status register
                p_ctx->pl.frame_state			= PL_STATE_DATA_AVAILABLE;
                ifx_i2c_pl_read_register(p_ctx,PL_REG_I2C_STATE, PL_REG_LEN_I2C_STATE);
            }
            break;
            // Do read/write frame
            case PL_STATE_DATA_AVAILABLE:
            {
                // Read frame, if response is ready. Ignore busy flag
                if ((p_ctx->pl.frame_action == PL_ACTION_READ_FRAME)
                && (p_ctx->pl.buffer[0] & PL_REG_I2C_STATE_RESPONSE_READY))
                {
                    frame_size = (p_ctx->pl.buffer[2] << 8) | p_ctx->pl.buffer[3];
                    if ((frame_size > 0) && (frame_size <= p_ctx->frame_size))
                    {
                        p_ctx->pl.frame_state = PL_STATE_RXTX;
                        ifx_i2c_pl_read_register(p_ctx,PL_REG_DATA, frame_size);
                    }
                    else
                    {
                        // Continue polling STATUS register if retry limit is not reached
                        if ((pal_os_timer_get_time_in_milliseconds() - p_ctx->dl.frame_start_time) < p_ctx->dl.data_poll_timeout)
                        {
                            pal_os_event_register_callback_oneshot(ifx_i2c_pl_status_poll_callback, (void *)p_ctx, PL_DATA_POLLING_INVERVAL_US);
                        }
                        else
                        {
                            p_ctx->pl.frame_state = PL_STATE_READY;
                            p_ctx->pl.upper_layer_event_handler(p_ctx,IFX_I2C_STACK_ERROR, 0, 0);
                        }
                    }
                }
                // Write frame is slave is not busy
                else if (p_ctx->pl.frame_action == PL_ACTION_WRITE_FRAME)
                {
                    // Write frame if device is not busy, otherwise wait and poll STATUS again later
                    p_ctx->pl.frame_state = PL_STATE_RXTX;
                    ifx_i2c_pl_write_register(p_ctx,PL_REG_DATA, p_ctx->pl.tx_frame_len, (uint8_t*)p_ctx->pl.p_tx_frame);
                }
                // Continue checking the slave status register
                else
                {
                    // Continue polling STATUS register if retry limit is not reached
                    if ((pal_os_timer_get_time_in_milliseconds() - p_ctx->dl.frame_start_time) < p_ctx->dl.data_poll_timeout)
                    {
                        pal_os_event_register_callback_oneshot(ifx_i2c_pl_status_poll_callback, (void *)p_ctx, PL_DATA_POLLING_INVERVAL_US);
                    }
                    else
                    {
                        p_ctx->pl.frame_state = PL_STATE_READY;
                        p_ctx->pl.upper_layer_event_handler(p_ctx,IFX_I2C_STACK_ERROR, 0, 0);
                    }
                }
            }
            break;
            // Frame reading is complete
            case PL_STATE_RXTX:
            {
                // Writing/reading of frame to/from DATA register complete
                p_ctx->pl.frame_state = PL_STATE_READY;
                p_ctx->pl.upper_layer_event_handler(p_ctx,IFX_I2C_STACK_SUCCESS, p_ctx->pl.buffer, p_ctx->pl.buffer_rx_len);
            }
            break;
            default:
                break; 
        }
    }
}

static void ifx_i2c_pal_poll_callback(void *p_ctx)
{
    ifx_i2c_context_t* p_local_ctx = (ifx_i2c_context_t *)p_ctx;
    if (p_local_ctx->pl.i2c_cmd == PL_I2C_CMD_WRITE)
    {
        LOG_PL("[IFX-PL]: Poll Timer elapsed -> Restart TX\n");
        //lint --e{534} suppress "Return value is not required to be checked"
        pal_i2c_write(p_local_ctx->p_pal_i2c_ctx, p_local_ctx->pl.buffer, p_local_ctx->pl.buffer_tx_len);
    }
    else if (p_local_ctx->pl.i2c_cmd == PL_I2C_CMD_READ)
    {
        LOG_PL("[IFX-PL]: Poll Timer elapsed  -> Restart Read Register -> Start TX\n");
        //lint --e{534} suppress "Return value is not required to be checked"
        pal_i2c_read(p_local_ctx->p_pal_i2c_ctx,p_local_ctx->pl.buffer, p_local_ctx->pl.buffer_rx_len);
    }
}


static void ifx_i2c_pl_guard_time_callback(void *p_ctx)
{
    ifx_i2c_context_t* p_local_ctx = (ifx_i2c_context_t*)p_ctx;
    if (p_local_ctx->pl.register_action == PL_ACTION_READ_REGISTER)
    {
    	if (p_local_ctx->pl.i2c_cmd == PL_I2C_CMD_WRITE)
    	{
    		LOG_PL("[IFX-PL]: GT done-> Start RX\n");
			p_local_ctx->pl.i2c_cmd = PL_I2C_CMD_READ;
			//lint --e{534} suppress "Return value is not required to be checked"
            pal_i2c_read(p_local_ctx->p_pal_i2c_ctx,p_local_ctx->pl.buffer, p_local_ctx->pl.buffer_rx_len);
    	}
    	else if (p_local_ctx->pl.i2c_cmd == PL_I2C_CMD_READ)
    	{
    		LOG_PL("[IFX-PL]: GT done -> REG is read\n");
    		ifx_i2c_pl_frame_event_handler(p_local_ctx,IFX_I2C_STACK_SUCCESS);
    	}
    }
    else if (p_local_ctx->pl.register_action == PL_ACTION_WRITE_REGISTER)
	{
    	LOG_PL("[IFX-PL]: GT done -> REG written\n");
    	ifx_i2c_pl_frame_event_handler(p_local_ctx,IFX_I2C_STACK_SUCCESS);
	}
}

static void ifx_i2c_pl_pal_event_handler(void *p_ctx, host_lib_status_t event)
{   
    ifx_i2c_context_t* p_local_ctx = (ifx_i2c_context_t*)p_ctx;     
    switch (event)
    {
        case PAL_I2C_EVENT_ERROR:            
        case PAL_I2C_EVENT_BUSY:
            // Error event usually occurs when the device is in sleep mode and needs time to wake up
            if (p_local_ctx->pl.retry_counter--)
            {
				LOG_PL("[IFX-PL]: PAL Error -> Continue polling\n");
                pal_os_event_register_callback_oneshot(ifx_i2c_pal_poll_callback,p_local_ctx,PL_POLLING_INVERVAL_US);
            }
            else
            {
                LOG_PL("[IFX-PL]: PAL Error -> Stop\n");
                ifx_i2c_pl_frame_event_handler(p_local_ctx,IFX_I2C_FATAL_ERROR);
            }
            break;
            
        case PAL_I2C_EVENT_SUCCESS:
            LOG_PL("[IFX-PL]: PAL Success -> Wait Guard Time\n");
            pal_os_event_register_callback_oneshot(ifx_i2c_pl_guard_time_callback,p_local_ctx,PL_GUARD_TIME_INTERVAL_US);
            break;
        default:
            break;
    }
}


static void ifx_i2c_pl_soft_reset(ifx_i2c_context_t *p_ctx)
{
    uint8_t i2c_mode_value[2] = {0};
	switch(p_ctx->pl.request_soft_reset)
	{
		case PL_INIT_GET_STATUS_REG:
			p_ctx->pl.request_soft_reset = PL_RESET_WRITE;
			//Read the status register to check if soft reset is supported
			ifx_i2c_pl_read_register(p_ctx, PL_REG_I2C_STATE, PL_REG_LEN_I2C_STATE);
			break;

		case PL_RESET_WRITE:
			//Mask for soft reset bit(5th bit) from the 1st byte of status register
			p_ctx->pl.buffer[0] &= PL_REG_I2C_STATE_SOFT_RESET;	
			if(p_ctx->pl.buffer[0] == PL_REG_I2C_STATE_SOFT_RESET)
			{
				p_ctx->pl.request_soft_reset = PL_RESET_STARTUP;
				//Write 88 register with 0 value
				ifx_i2c_pl_write_register(p_ctx, PL_REG_SOFT_RESET, PL_REG_LEN_SOFT_RESET, i2c_mode_value);
			}
			else
			{
				//Soft reset is not supported by the slave
				p_ctx->pl.frame_state = PL_STATE_UNINIT;
				ifx_i2c_pl_frame_event_handler(p_ctx, IFX_I2C_STACK_ERROR);
			}
			break;
            
		case PL_RESET_STARTUP:
			p_ctx->pl.request_soft_reset= PL_RESET_INIT;
			pal_os_event_register_callback_oneshot((register_callback)ifx_i2c_pl_soft_reset, (void *)p_ctx, STARTUP_TIME_MSEC);
			break;

		case PL_RESET_INIT:
			p_ctx->pl.frame_state = PL_STATE_INIT;
			ifx_i2c_pl_frame_event_handler(p_ctx,IFX_I2C_STACK_SUCCESS);
			break;

        default:
            break;
	}    
}

//lint --e{715} suppress "This is used for synchromous implementation, hence p_ctx not used"
//lint --e{818} suppress "This is ignored as upper layer handler function prototype requires this argument"
static void ifx_i2c_pl_pal_slave_addr_event_handler(void *p_ctx, host_lib_status_t event)
{
    pal_event_status = event;
}

