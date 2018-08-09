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

#ifndef _OPTIGA_COMMS_H_
#define _OPTIGA_COMMS_H_
/**********************************************************************************************************************
 * HEADER FILES
 *********************************************************************************************************************/
#include "Datatypes.h"

/**********************************************************************************************************************
 * MACROS
 *********************************************************************************************************************/

/// Succesfull execution
#define OPTIGA_COMMS_SUCCESS        0x0000
/// Error in execution
#define OPTIGA_COMMS_ERROR          0x0001
/// Busy, doing operation
#define OPTIGA_COMMS_BUSY           0x0002

/**********************************************************************************************************************
 * DATA STRUCTURES
 *********************************************************************************************************************/

/** @brief optiga comms structure */
typedef struct optiga_comms
{
    /// Comms structure pointer
    void* comms_ctx;  
    /// Upper layer contect
    void* upper_layer_ctx;
    /// Upper layer handler
    app_event_handler_t upper_layer_handler; 
    /// Optiga comms state
    uint8_t state;
}optiga_comms_t;

extern optiga_comms_t optiga_comms;

/**********************************************************************************************************************
 * API Prototypes
 *********************************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief   Opens the communication channel with OPTIGA.
 */
LIBRARY_EXPORTS host_lib_status_t optiga_comms_open(optiga_comms_t *p_ctx);

/**
 * \brief   Resets the OPTIGA.
 */
LIBRARY_EXPORTS host_lib_status_t optiga_comms_reset(optiga_comms_t *p_ctx,uint8_t reset_type);

/**
 * \brief   Sends and receives the APDU.
 */
LIBRARY_EXPORTS host_lib_status_t optiga_comms_transceive(optiga_comms_t *p_ctx,const uint8_t* p_data, 
                                                          const uint16_t* p_data_length,
                                                          uint8_t* p_buffer, uint16_t* p_buffer_len);

/**
 * \brief   Closes the communication channel with OPTIGA.
 */
LIBRARY_EXPORTS host_lib_status_t optiga_comms_close(optiga_comms_t *p_ctx);

/**
* @}
*/

#endif /*_OPTIGA_COMMS_H_*/

