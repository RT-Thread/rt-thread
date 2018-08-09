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
* \file
*
* \brief This file implements optiga comms abstraction layer for IFX I2C Protocol.
*
* \addtogroup  grOptigaComms
* @{
*/

/**********************************************************************************************************************
 * HEADER FILES
 *********************************************************************************************************************/
#include "optiga_comms.h"
#include "ifx_i2c.h"
/// @cond hidden
/**********************************************************************************************************************
 * MACROS
 *********************************************************************************************************************/
 /// Optiga comms is in use
 #define OPTIGA_COMMS_INUSE     (0x01)
 /// Optiga comms is free
 #define OPTIGA_COMMS_FREE      (0x00)
/**********************************************************************************************************************
 * LOCAL DATA
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * LOCAL ROUTINES
 *********************************************************************************************************************/
static host_lib_status_t check_optiga_comms_state(optiga_comms_t *p_ctx);
static void ifx_i2c_event_handler(void* upper_layer_ctx, host_lib_status_t event);

/// @endcond
/**********************************************************************************************************************
 * API IMPLEMENTATION
 *********************************************************************************************************************/

/**
 * Initializes the commmunication with OPTIGA.<br>
 *
 *<b>Pre Conditions:</b>
 * - None<br>
 *
 *<b>API Details:</b>
 * - Initializes OPTIGA and establishes the communication channel.<br>
 * - Initializes the ifx i2c protocol stack and registers the event callbacks.<br>
 * - Negotiates the frame size and bit rate with the OPTIGA.<br>
 *<br>
 *
 *<b>User Input:</b><br>
 * - The input #optiga_comms_t p_ctx must not be NULL.<br>
 * - The following parameters in #optiga_comms_t must be initialized with appropriate values.<br>
 *      - The <b>comms_ctx</b> must be initialized with a valid #ifx_i2c_context.<br>
 *      - The <b>upper_layer_event_handler</b> parameter must be properly initialized.
 *          This is invoked when #optiga_comms_open is asynchronously completed.<br>
 *      - The <b>upper_layer_ctx</b> must be properly initialized.<br>
 *
 *<b>Notes:</b>
 * - None<br>
 *
 *<br>
 * \param[in,out] p_ctx   Pointer to optiga comms context
 *
 * \retval  #OPTIGA_COMMS_SUCCESS
 * \retval  #OPTIGA_COMMS_ERROR
 */
host_lib_status_t optiga_comms_open(optiga_comms_t *p_ctx)
{
    host_lib_status_t status = OPTIGA_COMMS_ERROR;
    if (OPTIGA_COMMS_SUCCESS == check_optiga_comms_state(p_ctx))
    {
        ((ifx_i2c_context_t*)(p_ctx->comms_ctx))->p_upper_layer_ctx = (void*)p_ctx;
        ((ifx_i2c_context_t*)(p_ctx->comms_ctx))->upper_layer_event_handler = ifx_i2c_event_handler;
        status = ifx_i2c_open((ifx_i2c_context_t*)(p_ctx->comms_ctx)); 
        if (IFX_I2C_STACK_SUCCESS != status)
        {
            p_ctx->state = OPTIGA_COMMS_FREE;
        }
    }
    return status; 
}

/**
 * Resets the OPTIGA.<br>
 *
 *<b>Pre Conditions:</b>
 * - Communication channel must be established with OPTIGA.<br>
 *
 *<b>API Details:</b>
 * - Resets the OPTIGA device.<br>
 * - Initializes the ifx i2c protocol stack.<br>
 * - Re-Initializes and negotiates the frame size and bit rate with the OPTIGA.
 *   The values remain same as that in previous #optiga_comms_open().<br>
 *<br>
 *
 *<b>User Input:</b><br>
 * - The input #optiga_comms_t p_ctx must not be NULL.
 *
 *<b>Notes:</b>
 *   For COLD and WARM reset type: If the gpio(vdd and/or reset) pins are not configured, 
 *   the API continues without returning error status<br>
 *
 *
 * \param[in,out] p_ctx        Pointer to #optiga_comms_t
 * \param[in,out] reset_type   type of reset
 *
 * \retval  #OPTIGA_COMMS_SUCCESS
 * \retval  #OPTIGA_COMMS_ERROR
 */
host_lib_status_t optiga_comms_reset(optiga_comms_t *p_ctx,uint8_t reset_type)
{
    host_lib_status_t status = OPTIGA_COMMS_ERROR;
    if (OPTIGA_COMMS_SUCCESS == check_optiga_comms_state(p_ctx))
    {
        ((ifx_i2c_context_t*)(p_ctx->comms_ctx))->p_upper_layer_ctx = (void*)p_ctx;
        ((ifx_i2c_context_t*)(p_ctx->comms_ctx))->upper_layer_event_handler = ifx_i2c_event_handler;
        status = ifx_i2c_reset((ifx_i2c_context_t*)(p_ctx->comms_ctx),(ifx_i2c_reset_type_t)reset_type); 
        if (IFX_I2C_STACK_SUCCESS != status)
        {
            p_ctx->state = OPTIGA_COMMS_FREE;
        }
    }
    return status;
}

/**
 * Sends a command to OPTIGA and receives a response.<br>
 *
 *
 *<b>Pre Conditions:</b>
 * - Communication channel must be established with OPTIGA.<br>
 *
 *<b>API Details:</b>
 * - Transmit data(Command) to OPTIGA.<br>
 * - Receive data(Response) from OPTIGA.<br>
 *<br>
 *
 *<b>User Input:</b><br>
 * - The input #optiga_comms_t p_ctx must not be NULL.<br>
 * - The following parameters in #optiga_comms_t must be initialized with appropriate values <br>
 *      - The <b>comms_ctx</b> must be initialized with a valid #ifx_i2c_context<br>
 *      - The <b>upper_layer_event_handler</b> parameter must be properly initialized, 
 *          if it is different from that in #optiga_comms_open().
 *          This is invoked when optiga_comms_transceive is asynchronously completed.<br>
 *      - The <b>upper_layer_ctx</b> must be properly initialized, 
 *          if it is different from that in #optiga_comms_open().<br>
 *
 *<b>Notes:</b>
 * - The actual number of bytes received is stored in p_buffer_len. In case of error, p_buffer_len is set to 0.<br>
 * - If the size of p_buffer is zero or insufficient to copy the response bytes then
 *   #IFX_I2C_STACK_MEM_ERROR error is returned.
 *
 *
 * \param[in,out] p_ctx             Pointer to #optiga_comms_t
 * \param[in]     p_data            Pointer to the write data buffer
 * \param[in]     p_data_length     Pointer to the length of the write data buffer
 * \param[in,out] p_buffer          Pointer to the receive data buffer
 * \param[in,out] p_buffer_len      Pointer to the length of the receive data buffer 
 *
 * \retval  #OPTIGA_COMMS_SUCCESS
 * \retval  #OPTIGA_COMMS_ERROR
 * \retval  #IFX_I2C_STACK_MEM_ERROR
 */
host_lib_status_t optiga_comms_transceive(optiga_comms_t *p_ctx,const uint8_t* p_data,
                                          const uint16_t* p_data_length, 
                                          uint8_t* p_buffer, uint16_t* p_buffer_len)
{
    host_lib_status_t status = OPTIGA_COMMS_ERROR;
    if (OPTIGA_COMMS_SUCCESS == check_optiga_comms_state(p_ctx))
    {
        ((ifx_i2c_context_t*)(p_ctx->comms_ctx))->p_upper_layer_ctx = (void*)p_ctx;
        ((ifx_i2c_context_t*)(p_ctx->comms_ctx))->upper_layer_event_handler = ifx_i2c_event_handler;
        status = (ifx_i2c_transceive((ifx_i2c_context_t*)(p_ctx->comms_ctx),p_data,p_data_length,p_buffer,p_buffer_len));
        if (IFX_I2C_STACK_SUCCESS != status)
        {
            p_ctx->state = OPTIGA_COMMS_FREE;
        }
    }
    return status;
}

/**
 * Closes the communication with OPTIGA.<br>
 *
 *<b>Pre Conditions:</b>
 * - None<br>
 *
 *<b>API Details:</b>
 * - De-Initializes the OPTIGA and closes the communication channel.<br>
 * - Power downs the OPTIGA.<br>
 *<br>
 *
 *<b>User Input:</b><br>
 * - The input #optiga_comms_t p_ctx must not be NULL.<br>
 * - The #optiga_comms_t comms_ctx must be initialized with a valid #ifx_i2c_context<br>
 *
 * \param[in,out] p_ctx             Pointer to #optiga_comms_t
 *
 * \retval  #OPTIGA_COMMS_SUCCESS
 * \retval  #OPTIGA_COMMS_ERROR
 */
host_lib_status_t optiga_comms_close(optiga_comms_t *p_ctx)
{
    host_lib_status_t status = OPTIGA_COMMS_ERROR;
    if (OPTIGA_COMMS_SUCCESS == check_optiga_comms_state(p_ctx))
    {      
        ((ifx_i2c_context_t*)(p_ctx->comms_ctx))->p_upper_layer_ctx = (void*)p_ctx;
        ((ifx_i2c_context_t*)(p_ctx->comms_ctx))->upper_layer_event_handler = ifx_i2c_event_handler;
        status = ifx_i2c_close((ifx_i2c_context_t*)(p_ctx->comms_ctx)); 
        if (IFX_I2C_STACK_SUCCESS != status)
        {
            p_ctx->state = OPTIGA_COMMS_FREE;
        } 
    }
    return status;
}

/// @cond hidden
static host_lib_status_t check_optiga_comms_state(optiga_comms_t *p_ctx)
{
    host_lib_status_t status = OPTIGA_COMMS_ERROR;
    if ((NULL != p_ctx) && (p_ctx->state != OPTIGA_COMMS_INUSE))
    {
        p_ctx->state = OPTIGA_COMMS_INUSE;
        status = OPTIGA_COMMS_SUCCESS;
    }
    return status;
}

//lint --e{818} suppress "This is ignored as upper layer handler function prototype requires this argument"
static void ifx_i2c_event_handler(void* upper_layer_ctx, host_lib_status_t event)
{
    void* ctx = ((optiga_comms_t*)upper_layer_ctx)->upper_layer_ctx;
    ((optiga_comms_t*)upper_layer_ctx)->upper_layer_handler(ctx,event);
    ((optiga_comms_t*)upper_layer_ctx)->state = OPTIGA_COMMS_FREE;
}

/// @endcond
/**
* @}
*/

