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
* \brief This file implements the prototype declarations of pal i2c
*
* \addtogroup  grPAL
* @{
*/

#ifndef _PAL_I2C_H_
#define _PAL_I2C_H_

/**********************************************************************************************************************
 * HEADER FILES
 *********************************************************************************************************************/

#include "pal.h"

/**********************************************************************************************************************
 * MACROS
 *********************************************************************************************************************/
/// Event returned when I2C master completes execution
#define PAL_I2C_EVENT_SUCCESS (0x0000)
/// Event returned when I2C master operation fails
#define PAL_I2C_EVENT_ERROR   (0x0001)
/// Event returned when lower level I2C bus is busy
#define PAL_I2C_EVENT_BUSY    (0x0002)

/**********************************************************************************************************************
 * ENUMS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DATA STRUCTURES
 *********************************************************************************************************************/
/** @brief PAL I2C context structure */
typedef struct pal_i2c
{
    /// Pointer to I2C master platform specific context
    void* p_i2c_hw_config;
    /// I2C slave address
    uint8_t slave_address;
    /// Pointer to store the callers context information
    void* upper_layer_ctx;
    /// Pointer to store the callers handler
    void* upper_layer_event_handler;
    
} pal_i2c_t;

/**********************************************************************************************************************
 * API Prototypes
 *********************************************************************************************************************/
/**
 * @brief Initializes the I2C master.
 */
pal_status_t pal_i2c_init(const pal_i2c_t* p_i2c_context);

/**
 * @brief Sets the I2C Master bitrate
 */
pal_status_t pal_i2c_set_bitrate(const pal_i2c_t* p_i2c_context, uint16_t bitrate);

/**
 * @brief Writes to I2C bus.
 */
pal_status_t pal_i2c_write(pal_i2c_t* p_i2c_context, uint8_t* p_data , uint16_t length);

/**
 * @brief Reads from I2C bus.
 */
pal_status_t pal_i2c_read(pal_i2c_t* p_i2c_context, uint8_t* p_data , uint16_t length);

/**
 * @brief De-initializes the I2C master.
 */
pal_status_t pal_i2c_deinit(const pal_i2c_t* p_i2c_context);

#endif /* _PAL_I2C_H_ */

/**
* @}
*/

