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
* \file ifx_i2c.c
*
* \brief   This file implements the wrapper API Layer for IFX I2C protocol v1.65.
*
* \addtogroup  grIFXI2C
* @{
*/

/***********************************************************************************************************************
* HEADER FILES
**********************************************************************************************************************/
#include "ifx_i2c.h"
#include "ifx_i2c_transport_layer.h"
#include "pal_os_event.h"

/// @cond hidden
/***********************************************************************************************************************
* MACROS
**********************************************************************************************************************/

// IFX I2C states
#define IFX_I2C_STATE_UNINIT         (0x01)
#define IFX_I2C_STATE_IDLE           (0x02)
#define IFX_I2C_STATUS_BUSY          (0x03)
#define IFX_I2C_STATUS_NOT_BUSY      (0x04)
                                     
/// IFX I2C Reset states     
#define IFX_I2C_STATE_RESET_PIN_LOW        (0xB1)
#define IFX_I2C_STATE_RESET_PIN_HIGH       (0xB2)
#define IFX_I2C_STATE_RESET_INIT           (0xB3)
    
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
/// Transport Layer event handler
void ifx_i2c_tl_event_handler(ifx_i2c_context_t* p_ctx,host_lib_status_t event, const uint8_t* p_data, uint16_t data_len);

/// Performs initialization
static host_lib_status_t ifx_i2c_init(ifx_i2c_context_t* ifx_i2c_context);

//lint --e{526} suppress "This API is defined in ifx_i2c_physical_layer. Since it is a low level API, 
//to avoid exposing, header file is not included "
extern host_lib_status_t ifx_i2c_pl_write_slave_address(ifx_i2c_context_t *p_ctx, uint8_t slave_address, uint8_t storage_type);
/// @endcond
/***********************************************************************************************************************
* API PROTOTYPES
**********************************************************************************************************************/
/**
 * Initializes the IFX I2C protocol stack for the given context.
 * <br>
 * <br>
 * \image html ifx_i2c_open.png "ifx_i2c_open()" width=20cm
 *
 *<b>Pre Conditions:</b>
 * - None<br>
 *
 *<b>API Details:</b>
 * - Performs a reset sequence.<br>
 * - Initializes the I2C slave device.<br>
 * - Initializes the ifx i2c protocol stack and registers the event callbacks.
 * - Negotiates the frame size and bit rate with the I2C slave.<br>
 *<br>
 *
 *<b>User Input:</b><br>
 * - The input #ifx_i2c_context_t p_ctx must not be NULL.
 * - The following parameters in #ifx_i2c_context_t must be initialized with appropriate values <br>
 *   - <b>slave address</b> : Address of I2C slave
 *   - <b>frame_size</b> : Frame size in bytes.Minimum supported value is 16 bytes.<br> 
 *              - It is recommended not to use a value greater than the slave's frame size.
 *              - The user specified frame size is written to I2C slave's frame size register.
 *                The frame size register is read back from I2C slave.
 *                This frame value is used by the ifx-i2c protocol even if it is not equal to the user specified value.
 *
 *   - <b>frequency</b> : Frequency/speed of I2C master in KHz.
 *              - This must be lowest of the maximum frequency supported by the devices (master/slave) connected on the bus.
 *              - Initial negotiation starts with a frequency of 100KHz.
 *              - If the user specified frequency is more than 400 KHz, the I2C slave is configured to operate in "Fm+" mode, 
 *                otherwise the I2C slave is configured for "SM & Fm" mode. <br>
 *              - If the user specified frequency frequency negotiation fails, the I2C master frequency remains at 100KHz<br>
 * 
 *   - <b>upper_layer_event_handler</b> : Upper layer event handler.This is invoked when #ifx_i2c_open() is asynchronously completed.
 *   - <b>upper_layer_ctx</b> : Context of upper layer.
 *   - <b>p_slave_vdd_pin</b> : GPIO pin for VDD. If not set, cold reset is not done. 
 *   - <b>p_slave_reset_pin</b> : GPIO pin for Reset. If not set, warm reset is not done.
 *
 *<b>Notes:</b>
 * - The values of registers MAX_SCL_FREQU and DATA_REG_LEN, read from slave are not validated.
 * - At present, only single instance of #ifx_i2c_context_t is supported.
 *
 *<br>
 *
 * \param[in,out] p_ctx   Pointer to #ifx_i2c_context_t
 *
 * \retval  #IFX_I2C_STACK_SUCCESS        
 * \retval  #IFX_I2C_STACK_ERROR
 */
host_lib_status_t ifx_i2c_open(ifx_i2c_context_t *p_ctx)
{	
    host_lib_status_t api_status = (int32_t)IFX_I2C_STACK_ERROR;
    
    //If api status is not busy, proceed
    if ((IFX_I2C_STATUS_BUSY != p_ctx->status))
    {
        p_ctx->p_pal_i2c_ctx->upper_layer_ctx = p_ctx;      
        p_ctx->reset_type = (uint8_t)IFX_I2C_COLD_RESET;
        p_ctx->reset_state = IFX_I2C_STATE_RESET_PIN_LOW;
        p_ctx->do_pal_init = TRUE;
        p_ctx->state = IFX_I2C_STATE_UNINIT;

        // Init GPIO and OS event PAL
        pal_gpio_init();
        pal_os_event_init();

        api_status = ifx_i2c_init(p_ctx);
        if(IFX_I2C_STACK_SUCCESS == api_status)
        {
            p_ctx->status = IFX_I2C_STATUS_BUSY;
        }
    }

    return api_status;
}

/**
 * Resets the I2C slave and initializes the IFX I2C protocol stack for the given context.
 * <br>
 * <br>
 * \image html ifx_i2c_reset.png "ifx_i2c_reset()" width=20cm
 *
 *<b>Pre Conditions:</b>
 * - IFX I2C protocol stack must be initialized.<br>
 *
 *<b>API Details:</b>
 * - Resets the I2C slave.<br>
 * - Initializes the ifx i2c protocol stack.<br>
 * - Re-Initializes and negotiates the frame size and bit rate with the I2C slave.
 *   The values remain same as that in previous #ifx_i2c_open().<br>
 *<br>
 *
 *<b>User Input:</b><br>
 * - The input #ifx_i2c_context_t p_ctx must not be NULL.
 *
 *<b>Notes:</b>
 *   For COLD and WARM reset type: If the gpio(vdd and/or reset) pins are not configured, 
 *   the API continues without any failure return status<br>
 *
 * \param[in,out] p_ctx   Pointer to #ifx_i2c_context_t
 * \param[in,out] reset_type   type of reset
 *
 * \retval  #IFX_I2C_STACK_SUCCESS 
 * \retval  #IFX_I2C_STACK_ERROR
 */
host_lib_status_t ifx_i2c_reset(ifx_i2c_context_t *p_ctx, ifx_i2c_reset_type_t reset_type)
{
    host_lib_status_t api_status = (int32_t)IFX_I2C_STACK_ERROR;
    
    // Proceed, if not busy and in idle state
    if ((IFX_I2C_STATE_IDLE == p_ctx->state) && (IFX_I2C_STATUS_BUSY != p_ctx->status))
    {        
        p_ctx->reset_type = (uint8_t)reset_type;
        p_ctx->reset_state = IFX_I2C_STATE_RESET_PIN_LOW;
        p_ctx->do_pal_init = FALSE;

        api_status = ifx_i2c_init(p_ctx);
        if(IFX_I2C_STACK_SUCCESS == api_status)
        {
            p_ctx->status = IFX_I2C_STATUS_BUSY;
        }
    }
    return api_status;
}

/**

 * Sends a command and receives a response for the command.<br>
 * <br>
 * \image html ifx_i2c_transceive.png "ifx_i2c_transceive()" width=20cm
 *
 *
 *<b>Pre Conditions:</b>
 * - IFX I2C protocol stack must be initialized.<br>
 *
 *<b>API Details:</b>
 * - Transmit data(Command) to I2C slave.<br>
 * - Receive data(Response) from I2C slave.<br>
 *<br>
 *
 *<b>User Input:</b><br>
 * - The input #ifx_i2c_context_t p_ctx must not be NULL.
 * - The following parameters in #ifx_i2c_context_t must be initialized with appropriate values <br>
 *   - <b>upper_layer_event_handler</b> : Upper layer event handler, if it is different from that in #ifx_i2c_open().
 *     This is invoked when #ifx_i2c_transceive is asynchronously completed.
 *   - <b>upper_layer_ctx</b> : Context of upper layer, if it is different from that in #ifx_i2c_open.
 *
 *<b>Notes:</b>
 * - The actual number of bytes received is stored in p_rx_buffer_len. In case of error,p_rx_buffer_len is set to 0.<br>
 * - If the size of p_rx_buffer is zero or insufficient to copy the response bytes then
 *   #IFX_I2C_STACK_MEM_ERROR error is returned.
 *
 * \param[in,out] p_ctx   Pointer to #ifx_i2c_context_t
 * \param[in]     p_data    Pointer to the write data buffer
 * \param[in]     p_data_length   Pointer to the length of the write data buffer
 * \param[in,out] p_rx_buffer     Pointer to the receive data buffer
 * \param[in,out] p_rx_buffer_len    Pointer to the length of the receive data buffer 
 *
 * \retval  #IFX_I2C_STACK_SUCCESS 
 * \retval  #IFX_I2C_STACK_ERROR
 * \retval  #IFX_I2C_STACK_MEM_ERROR
 */
host_lib_status_t ifx_i2c_transceive(ifx_i2c_context_t *p_ctx,const uint8_t* p_data, const uint16_t* p_data_length, 
                                     uint8_t* p_rx_buffer, uint16_t* p_rx_buffer_len)
{
    host_lib_status_t api_status = (int32_t)IFX_I2C_STACK_ERROR;
    // Proceed, if not busy and in idle state
    if ((IFX_I2C_STATE_IDLE == p_ctx->state) && (IFX_I2C_STATUS_BUSY != p_ctx->status))
    { 
        p_ctx->p_upper_layer_rx_buffer = p_rx_buffer;
        p_ctx->p_upper_layer_rx_buffer_len = p_rx_buffer_len;
        api_status = ifx_i2c_tl_transceive(p_ctx,(uint8_t*)p_data, (*p_data_length),
                                           (uint8_t*)p_rx_buffer , p_rx_buffer_len);
        if (IFX_I2C_STACK_SUCCESS == api_status)
        {
            p_ctx->status = IFX_I2C_STATUS_BUSY;
        }
    }
    return api_status;
}


/**
 * Closes the IFX I2C protocol stack for a given context.
 * <br>
 * <br>
 * \image html ifx_i2c_close.png "ifx_i2c_close()" width=20cm
 *
 *<b>Pre Conditions:</b>
 * - None<br>
 *
 *<b>API Details:</b>
 * - De-Initializes the I2C slave device.<br>
 * - Power downs the I2C slave.<br>
 *<br>
 *
 *<b>User Input:</b><br>
 * - The input #ifx_i2c_context_t p_ctx must not be NULL.
 *
 *<b>Notes:</b>
 *
 * \param[in,out] p_ctx   Pointer to #ifx_i2c_context_t
 *
 * \retval  #IFX_I2C_STACK_SUCCESS 
 */
host_lib_status_t ifx_i2c_close(ifx_i2c_context_t *p_ctx)
{
    host_lib_status_t api_status = (int32_t)IFX_I2C_STACK_ERROR;
    // Proceed, if not busy and in idle state
    if (IFX_I2C_STATUS_BUSY != p_ctx->status)
    { 
		api_status = IFX_I2C_STACK_SUCCESS;
        //lint --e{534} suppress "Return value is not required to be checked"
        // Close I2C master
        pal_i2c_deinit(p_ctx->p_pal_i2c_ctx);
        // Also power off the device
        pal_gpio_set_low(p_ctx->p_slave_vdd_pin);
        pal_gpio_set_low(p_ctx->p_slave_reset_pin);
        
        ifx_i2c_tl_event_handler(p_ctx,IFX_I2C_STACK_SUCCESS,NULL,0);
        p_ctx->state = IFX_I2C_STATE_UNINIT;
        p_ctx->status = IFX_I2C_STATUS_NOT_BUSY;
    }
    return api_status;
}

/**
* Writes new I2C slave Address to the target device.<br>
* 
*<b>Pre Conditions:</b>
* - IFX I2C protocol stack must be initialized.<br>
*
*<b>API Details:</b>
*  - This API is implemented in synchronous mode.
*  - If the write fails due to the following reasons, this API repeats the write for #PL_POLLING_MAX_CNT times
*    with a fixed interval of #PL_POLLING_INVERVAL_US microseconds and exits with respective return status.
*    - I2C bus is in busy state, returns #IFX_I2C_STACK_BUSY
*    - No-acknowledge(NACK) received from slave, returns #IFX_I2C_STACK_ERROR
*    - I2C errors, returns #IFX_I2C_STACK_ERROR
*  - Only bits [6:0] from  parameter "slave_address" are considered as slave address. Hence the bit 7 is ignored.
*  - Slave address validation is not done in the implementation. Provide a valid slave address as input.
*
*<b>Notes:</b>
* - If persistent mode is selected, the ifx i2c context slave address will be over-written with the new slave address.
*   Even after ifx i2c open/reset, all future executions will use the new slave address.<br>
* - If volatile mode is selected, the pal_i2c_context slave address will be over-written with the new slave address.
*   This persists only till the next ifx_i2c open/reset is called.
*
* \param[in,out] p_ctx              Pointer to #ifx_i2c_context_t
* \param[in]     slave_address      Holds new slave address[7 Bit] to be set.
* \param[in]     persistent         0 - To set the Slave address until next reset.<br>
*                                   Non-zero - To set the slave address to persistent memory.
* 
* \retval  #IFX_I2C_STACK_SUCCESS
* \retval  #IFX_I2C_STACK_ERROR
*/
host_lib_status_t ifx_i2c_set_slave_address(ifx_i2c_context_t *p_ctx, uint8_t slave_address, uint8_t persistent)
{
    host_lib_status_t api_status = (int32_t)IFX_I2C_STACK_ERROR;

    if ((IFX_I2C_STATE_IDLE == p_ctx->state))
    {
        p_ctx->p_pal_i2c_ctx->upper_layer_ctx = p_ctx;
        
        api_status = ifx_i2c_pl_write_slave_address(p_ctx, slave_address, persistent);
    }
    
    return api_status;
}

/// @cond hidden
//lint --e{715} suppress "This is ignored as ifx_i2c_event_handler_t handler function prototype requires this argument"
void ifx_i2c_tl_event_handler(ifx_i2c_context_t* p_ctx,host_lib_status_t event, const uint8_t* p_data, uint16_t data_len)
{
    // If there is no upper layer handler, don't do anything and return
    if (NULL != p_ctx->upper_layer_event_handler)
    {
        p_ctx->upper_layer_event_handler(p_ctx->p_upper_layer_ctx,event);
    }
    p_ctx->status = IFX_I2C_STATUS_NOT_BUSY;
    switch(p_ctx->state)
    {
        case IFX_I2C_STATE_UNINIT:
            if (IFX_I2C_STACK_SUCCESS == event)
            {
                p_ctx->state = IFX_I2C_STATE_IDLE;
            }
            break;
        default:
            break;
    }
}


static host_lib_status_t ifx_i2c_init(ifx_i2c_context_t* p_ifx_i2c_context)
{    
    host_lib_status_t api_status = IFX_I2C_STACK_ERROR;
	
	if ((p_ifx_i2c_context->reset_type == (uint8_t)IFX_I2C_WARM_RESET)||
	    (p_ifx_i2c_context->reset_type == (uint8_t)IFX_I2C_COLD_RESET))
	{
		switch(p_ifx_i2c_context->reset_state)
		{
			case IFX_I2C_STATE_RESET_PIN_LOW:
				// Setting the Vdd & Reset pin to low 
				if (p_ifx_i2c_context->reset_type == (uint8_t)IFX_I2C_COLD_RESET)
				{
					pal_gpio_set_low(p_ifx_i2c_context->p_slave_vdd_pin);
				}
				pal_gpio_set_low(p_ifx_i2c_context->p_slave_reset_pin);
				p_ifx_i2c_context->reset_state = IFX_I2C_STATE_RESET_PIN_HIGH;
				pal_os_event_register_callback_oneshot((register_callback)ifx_i2c_init,
                                                       (void *)p_ifx_i2c_context, RESET_LOW_TIME_MSEC);
				api_status = IFX_I2C_STACK_SUCCESS;
				break;
            
			case IFX_I2C_STATE_RESET_PIN_HIGH:
				// Setting the Vdd & Reset pin to high 
				if (p_ifx_i2c_context->reset_type == (uint8_t)IFX_I2C_COLD_RESET)
				{
					pal_gpio_set_high(p_ifx_i2c_context->p_slave_vdd_pin);
				}
				pal_gpio_set_high(p_ifx_i2c_context->p_slave_reset_pin);
				p_ifx_i2c_context->reset_state = IFX_I2C_STATE_RESET_INIT;
				pal_os_event_register_callback_oneshot((register_callback)ifx_i2c_init,
                                                       (void *)p_ifx_i2c_context, STARTUP_TIME_MSEC);
				api_status = IFX_I2C_STACK_SUCCESS;
				break;
            
			case IFX_I2C_STATE_RESET_INIT:
				//Frequency and frame size negotiation
				api_status = ifx_i2c_tl_init(p_ifx_i2c_context,ifx_i2c_tl_event_handler);
				break;
			default:
				break;
		}
	}
	//soft reset
	else
	{
		p_ifx_i2c_context->pl.request_soft_reset = (uint8_t)TRUE;	//Soft reset
		api_status = ifx_i2c_tl_init(p_ifx_i2c_context,ifx_i2c_tl_event_handler);
	}	

    return api_status;
}
/// @endcond
/**
* @}
*/
