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
* \file ifx_i2c.h
*
* \brief   This file defines the API prototype for IFX I2C protocol v1.65 wrapper.
*
* \addtogroup  grIFXI2C
* @{
*/

#ifndef _IFXI2C_H_
#define _IFXI2C_H_

#ifdef __cplusplus
extern "C" {
#endif
    
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "Datatypes.h"
#include "ifx_i2c_config.h"
/***********************************************************************************************************************
* MACROS
***********************************************************************************************************************/  
  
/***********************************************************************************************************************

* ENUMS
***********************************************************************************************************************/

/** @brief IFX I2C Reset types */
typedef enum ifx_i2c_reset_type
{
	/// Cold reset. Both reset pin and vdd pin are toggled low and then high
    IFX_I2C_COLD_RESET = 0U,
    /// Soft reset. 0x0000 is written to IFX-I2C Soft reset register
	IFX_I2C_SOFT_RESET = 1U,
    /// Warm reset. Only reset pin is toggled low and then high
    IFX_I2C_WARM_RESET = 2U 
} ifx_i2c_reset_type_t;
/***********************************************************************************************************************
* DATA STRUCTURES
***********************************************************************************************************************/
/***********************************************************************************************************************
* API PROTOTYPES
**********************************************************************************************************************/
 
/**
 * \brief   Initializes the IFX I2C protocol stack for a given context.
 */
host_lib_status_t ifx_i2c_open(ifx_i2c_context_t *p_ctx);

/**
 * \brief   Resets the I2C slave.
 */
host_lib_status_t ifx_i2c_reset(ifx_i2c_context_t *p_ctx, ifx_i2c_reset_type_t reset_type);

/**
 * \brief   Sends a command and receives a response for the command.
 */
host_lib_status_t ifx_i2c_transceive(ifx_i2c_context_t *p_ctx,const uint8_t* p_data, const uint16_t* p_data_length, 
                          uint8_t* p_buffer, uint16_t* p_buffer_len);

/**
 * \brief   Closes the IFX I2C protocol stack for a given context.
 */
host_lib_status_t ifx_i2c_close(ifx_i2c_context_t *p_ctx);

/**
 * \brief   Sets the slave address of the target device.
 */
host_lib_status_t ifx_i2c_set_slave_address(ifx_i2c_context_t *p_ctx, uint8_t slave_address, uint8_t persistent);

#ifdef __cplusplus
}
#endif
#endif /* _IFXI2C_H_ */
/**
 * @}
 **/

