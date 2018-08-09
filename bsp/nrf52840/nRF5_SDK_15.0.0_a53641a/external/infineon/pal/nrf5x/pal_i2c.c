/**
* \copyright
* Copyright(c) 2018, Infineon Technologies AG
* All rights reserved.
*
* This software is provided with terms and conditions as specified in OPTIGA(TM) Trust X Evaluation Kit License Agreement.
* \endcopyright
*
* \author Infineon AG
*
* \file
*
* \brief This file implements the platform abstraction layer(pal) APIs for I2C.
*
* \addtogroup  grPAL
* @{
*/

/**********************************************************************************************************************
 * HEADER FILES
 *********************************************************************************************************************/
#include "pal_i2c.h"
#include "ifx_i2c.h"
#include "nrf_twi_mngr.h"

/// @cond hidden

/**********************************************************************************************************************
 * MACROS
 *********************************************************************************************************************/
#define PAL_I2C_MASTER_MAX_BITRATE  (400)

/** @brief PIN for I2C SCL to Infineon OPTIGA Trust X device */
#define OPTIGA_PIN_I2C_SCL   (27)
/** @brief PIN for I2C SDA to Infineon OPTIGA Trust X device */
#define OPTIGA_PIN_I2C_SDA   (26)

/** @brief I2C driver instance */
#define TWI_INSTANCE_ID             0

/** @brief Maximal number of pending I2C transactions */
#define MAX_PENDING_TRANSACTIONS    5

/*********************************************************************************************************************
 * LOCAL DATA
 *********************************************************************************************************************/

/* Pointer to the current pal i2c context */
static pal_i2c_t * gp_pal_i2c_current_ctx;

/** @brief Definition of TWI manager instance */
NRF_TWI_MNGR_DEF(m_app_twi, MAX_PENDING_TRANSACTIONS, TWI_INSTANCE_ID);

/** @brief Definition of TWI manager transfer instance */
static nrf_twi_mngr_transfer_t    m_transfer;

/** @brief Definition of TWI manager transaction instance */
static nrf_twi_mngr_transaction_t m_transaction;

/**********************************************************************************************************************
 * LOCAL ROUTINES
 *********************************************************************************************************************/

/**
 * Pal I2C event handler function to invoke the registered upper layer callback<br>
 *
 *<b>API Details:</b>
 *  - This function implements the platform specific i2c event handling mechanism<br>
 *  - It calls the registered upper layer function after completion of the I2C read/write operations<br>
 *  - The respective event status are explained below.
 *   - #PAL_I2C_EVENT_ERROR when I2C fails due to low level failures(NACK/I2C protocol errors)
 *   - #PAL_I2C_EVENT_SUCCESS when operation is successfully completed
 *
 * \param[in] p_pal_i2c_ctx   Pointer to the pal i2c context #pal_i2c_t
 * \param[in] event           Status of the event reported after read/write completion or due to I2C errors
 *
 */
static void app_twi_callback(ret_code_t result, void * p_user_data)
{
    app_event_handler_t upper_layer_handler;
    //lint --e{611} suppress "void* function pointer is type casted to app_event_handler_t type"
    upper_layer_handler = (app_event_handler_t)gp_pal_i2c_current_ctx->upper_layer_event_handler;

    if (result == NRF_SUCCESS)
    {
        upper_layer_handler(gp_pal_i2c_current_ctx->upper_layer_ctx, PAL_I2C_EVENT_SUCCESS);
    }
    else
    {
        upper_layer_handler(gp_pal_i2c_current_ctx->upper_layer_ctx, PAL_I2C_EVENT_ERROR);
    }
}

/// @endcond

/**********************************************************************************************************************
 * API IMPLEMENTATION
 *********************************************************************************************************************/

/**
 * API to initialize the i2c master with the given context.
 * <br>
 *
 *<b>API Details:</b>
 * - The platform specific initialization of I2C master has to be implemented as part of this API, if required.<br>
 * - If the target platform does not demand explicit initialization of i2c master
 *   (Example: If the platform driver takes care of init after the reset), it would not be required to implement.<br>
 * - The implementation must take care the following scenarios depending upon the target platform selected.
 *   - The implementation must handle the acquiring and releasing of the I2C bus before initializing the I2C master to
 *     avoid interrupting the ongoing slave I2C transactions using the same I2C master.
 *   - If the I2C bus is in busy state, the API must not initialize and return #PAL_STATUS_I2C_BUSY status.
 *   - Repeated initialization must be taken care with respect to the platform requirements. (Example: Multiple users/applications  
 *     sharing the same I2C master resource)
 *
 *<b>User Input:</b><br>
 * - The input #pal_i2c_t p_i2c_context must not be NULL.<br>
 *
 * \param[in] p_i2c_context   Pal i2c context to be initialized
 *
 * \retval  #PAL_STATUS_SUCCESS  Returns when the I2C master init it successfull
 * \retval  #PAL_STATUS_FAILURE  Returns when the I2C init fails.
 */
pal_status_t pal_i2c_init(const pal_i2c_t* p_i2c_context)
{
    nrf_drv_twi_config_t const config = {
           .scl                = OPTIGA_PIN_I2C_SCL,
           .sda                = OPTIGA_PIN_I2C_SDA,
           .frequency          = (nrf_drv_twi_frequency_t) NRF_TWI_FREQ_400K,
           .interrupt_priority = APP_IRQ_PRIORITY_LOWEST,
           .clear_bus_init     = false
        };

    // Initialize I2C driver
    if (nrf_twi_mngr_init(&m_app_twi, &config) != NRF_SUCCESS)
    {
        return PAL_STATUS_FAILURE;
    }
    return PAL_STATUS_SUCCESS;
}

/**
 * API to de-initialize the I2C master with the specified context.
 * <br>
 *
 *<b>API Details:</b>
 * - The platform specific de-initialization of I2C master has to be implemented as part of this API, if required.<br>
 * - If the target platform does not demand explicit de-initialization of i2c master
 *   (Example: If the platform driver takes care of init after the reset), it would not be required to implement.<br>
 * - The implementation must take care the following scenarios depending upon the target platform selected.
 *   - The implementation must handle the acquiring and releasing of the I2C bus before de-initializing the I2C master to
 *     avoid interrupting the ongoing slave I2C transactions using the same I2C master.
 *   - If the I2C bus is in busy state, the API must not de-initialize and return #PAL_STATUS_I2C_BUSY status.
 *   - This API must ensure that multiple users/applications sharing the same I2C master resource is not impacted.
 *
 *<b>User Input:</b><br>
 * - The input #pal_i2c_t p_i2c_context must not be NULL.<br>
 *
 * \param[in] p_i2c_context   I2C context to be de-initialized
 *
 * \retval  #PAL_STATUS_SUCCESS  Returns when the I2C master de-init it successfull
 * \retval  #PAL_STATUS_FAILURE  Returns when the I2C de-init fails.
 */
pal_status_t pal_i2c_deinit(const pal_i2c_t* p_i2c_context)
{
    nrf_twi_mngr_uninit(&m_app_twi);
    return PAL_STATUS_SUCCESS;
}

/**
 * Platform abstraction layer API to write the data to I2C slave.
 * <br>
 * <br>
 * \image html pal_i2c_write.png "pal_i2c_write()" width=20cm
 *
 *
 *<b>API Details:</b>
 * - The API attempts to write if the I2C bus is free, else it returns busy status #PAL_STATUS_I2C_BUSY<br>
 * - The bus is released only after the completion of transmission or after completion of error handling.<br>
 * - The API invokes the upper layer handler with the respective event status as explained below.
 *   - #PAL_I2C_EVENT_BUSY when I2C bus in busy state
 *   - #PAL_I2C_EVENT_ERROR when API fails
 *   - #PAL_I2C_EVENT_SUCCESS when operation is successfully completed asynchronously
 *<br>
 *
 *<b>User Input:</b><br>
 * - The input #pal_i2c_t p_i2c_context must not be NULL.<br>
 * - The upper_layer_event_handler must be initialized in the p_i2c_context before invoking the API.<br>
 *
 *<b>Notes:</b><br> 
 *  - Otherwise the below implementation has to be updated to handle different bitrates based on the input context.<br>
 *  - The caller of this API must take care of the guard time based on the slave's requirement.<br>
 *
 * \param[in] p_i2c_context  Pointer to the pal I2C context #pal_i2c_t
 * \param[in] p_data         Pointer to the data to be written
 * \param[in] length         Length of the data to be written
 *
 * \retval  #PAL_STATUS_SUCCESS  Returns when the I2C write is invoked successfully
 * \retval  #PAL_STATUS_FAILURE  Returns when the I2C write fails.
 * \retval  #PAL_STATUS_I2C_BUSY Returns when the I2C bus is busy. 
 */
pal_status_t pal_i2c_write(pal_i2c_t* p_i2c_context,uint8_t* p_data , uint16_t length)
{
    gp_pal_i2c_current_ctx = p_i2c_context;

    m_transfer.p_data    = p_data;
    m_transfer.length    = length;
    m_transfer.operation = NRF_TWI_MNGR_WRITE_OP(IFX_I2C_BASE_ADDR);
    m_transfer.flags     = 0;

    m_transaction.callback            = app_twi_callback;
    m_transaction.number_of_transfers = 1;
    m_transaction.p_required_twi_cfg  = NULL;
    m_transaction.p_transfers         = &m_transfer;
    m_transaction.p_user_data         = (void*) PAL_STATUS_SUCCESS;

    if (nrf_twi_mngr_schedule(&m_app_twi, &m_transaction) != NRF_SUCCESS)
    {
        app_twi_callback(NRF_ERROR_BUSY, 0);
    }

    return PAL_STATUS_SUCCESS;
}

/**
 * Platform abstraction layer API to read the data from I2C slave.
 * <br>
 * <br>
 * \image html pal_i2c_read.png "pal_i2c_read()" width=20cm
 *
 *<b>API Details:</b>
 * - The API attempts to read if the I2C bus is free, else it returns busy status #PAL_STATUS_I2C_BUSY<br>
 * - The bus is released only after the completion of reception or after completion of error handling.<br>
 * - The API invokes the upper layer handler with the respective event status as explained below.
 *   - #PAL_I2C_EVENT_BUSY when I2C bus in busy state
 *   - #PAL_I2C_EVENT_ERROR when API fails
 *   - #PAL_I2C_EVENT_SUCCESS when operation is successfully completed asynchronously
 *<br>
 *
 *<b>User Input:</b><br>
 * - The input #pal_i2c_t p_i2c_context must not be NULL.<br>
 * - The upper_layer_event_handler must be initialized in the p_i2c_context before invoking the API.<br>
 *
 *<b>Notes:</b><br> 
 *  - Otherwise the below implementation has to be updated to handle different bitrates based on the input context.<br>
 *  - The caller of this API must take care of the guard time based on the slave's requirement.<br>
 *
 * \param[in]  p_i2c_context  pointer to the PAL i2c context #pal_i2c_t
 * \param[in]  p_data         Pointer to the data buffer to store the read data
 * \param[in]  length         Length of the data to be read
 *
 * \retval  #PAL_STATUS_SUCCESS  Returns when the I2C read is invoked successfully
 * \retval  #PAL_STATUS_FAILURE  Returns when the I2C read fails.
 * \retval  #PAL_STATUS_I2C_BUSY Returns when the I2C bus is busy.
 */
pal_status_t pal_i2c_read(pal_i2c_t* p_i2c_context , uint8_t* p_data , uint16_t length)
{
    gp_pal_i2c_current_ctx = p_i2c_context;

    m_transfer.p_data    = p_data;
    m_transfer.length    = length;
    m_transfer.operation = NRF_TWI_MNGR_READ_OP(IFX_I2C_BASE_ADDR);
    m_transfer.flags     = 0;

    m_transaction.callback            = app_twi_callback;
    m_transaction.number_of_transfers = 1;
    m_transaction.p_required_twi_cfg  = 0;
    m_transaction.p_transfers         = &m_transfer;
    m_transaction.p_user_data         = (void*) PAL_STATUS_SUCCESS;

    if (nrf_twi_mngr_schedule(&m_app_twi, &m_transaction) != NRF_SUCCESS)
    {
        app_twi_callback(NRF_ERROR_BUSY, 0);
    }

    return PAL_STATUS_SUCCESS;
}
   
/**
 * Platform abstraction layer API to set the bitrate/speed(KHz) of I2C master.
 * <br>
 *
 *<b>API Details:</b>
 * - Sets the bitrate of I2C master if the I2C bus is free, else it returns busy status #PAL_STATUS_I2C_BUSY<br>
 * - The bus is released after the setting the bitrate.<br>
 * - This API must take care of setting the bitrate to I2C master's maximum supported value. 
 * - Eg. In XMC4500, the maximum supported bitrate is 400 KHz. If the supplied bitrate is greater than 400KHz, the API will 
 *   set the I2C master's bitrate to 400KHz.
 * - Use the #PAL_I2C_MASTER_MAX_BITRATE macro to specify the maximum supported bitrate value for the target platform.
 * - If upper_layer_event_handler is initialized, the upper layer handler is invoked with the respective event 
 *   status listed below.
 *   - #PAL_I2C_EVENT_BUSY when I2C bus in busy state
 *   - #PAL_I2C_EVENT_ERROR when API fails to set the bit rate 
 *   - #PAL_I2C_EVENT_SUCCESS when operation is successful
 *<br>
 *
 *<b>User Input:</b><br>
 * - The input #pal_i2c_t  p_i2c_context must not be NULL.<br>
 *
 * \param[in] p_i2c_context  Pointer to the pal i2c context
 * \param[in] bitrate        Bitrate to be used by i2c master in KHz
 *
 * \retval  #PAL_STATUS_SUCCESS  Returns when the setting of bitrate is successfully completed
 * \retval  #PAL_STATUS_FAILURE  Returns when the setting of bitrate fails.
 * \retval  #PAL_STATUS_I2C_BUSY Returns when the I2C bus is busy.
 */
pal_status_t pal_i2c_set_bitrate(const pal_i2c_t* p_i2c_context , uint16_t bitrate)
{
    // Bitrate is fixed to the maximum frequency on this platform (400K)
    return PAL_STATUS_SUCCESS;
}

/**
* @}
*/
