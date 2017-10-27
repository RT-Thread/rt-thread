/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/**@file
 *
 * @defgroup sdk_nrf_dfu_req_handler Request handling
 * @{
 * @ingroup  sdk_nrf_dfu
 */

#ifndef NRF_DFU_REQ_HANDLER_H__
#define NRF_DFU_REQ_HANDLER_H__

#include <stdint.h>
#include <stdbool.h>
#include "nrf_dfu_types.h"
#include "nrf_dfu_handling_error.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**@brief DFU object types.
 */
typedef enum
{
    NRF_DFU_OBJ_TYPE_INVALID,                   /**< Invalid object type.*/
    NRF_DFU_OBJ_TYPE_COMMAND,                   /**< Command object packet.*/
    NRF_DFU_OBJ_TYPE_DATA,                      /**< Data object.*/
} nrf_dfu_obj_type_t;


/**@brief DFU request operation codes.
 *
 * @details The DFU transport layer creates request events of these types. The implementation of @ref nrf_dfu_req_handler_on_req handles requests of these types.
 */
typedef enum
{

    NRF_DFU_OBJECT_OP_NONE          = 0,        /**< No operation set. */
    NRF_DFU_OBJECT_OP_CREATE        = 1,        /**< Create operation. The length of the request indicates the required size. When called, the created object is selected. */
    NRF_DFU_OBJECT_OP_WRITE         = 2,        /**< Write operation. When called, offset and CRC of the selected object are reported back. */
    NRF_DFU_OBJECT_OP_EXECUTE       = 3,        /**< Execute operation. When called, the selected object is executed. */
    NRF_DFU_OBJECT_OP_CRC           = 4,        /**< Calculate checksum operation. When called, offset and CRC of the selected object are reported back. */
    NRF_DFU_OBJECT_OP_SELECT        = 6,        /**< Select operation. When called, the object of the given type is selected, and information about the object is reported back. */
    NRF_DFU_OBJECT_OP_OTHER         = 7,        /**< A user-defined DFU request type. The application must define how to interpret the request. */
} nrf_dfu_req_op_t;


#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
  // Anonymous unions are enabled by default.
#endif


/** @brief Definition of a DFU request sent from the transport layer.
 *
 * @details When the transport layer gets a DFU event, it calls the function @ref nrf_dfu_req_handler_on_req to handle the DFU request.
 */
typedef struct
{
    nrf_dfu_req_op_t    req_type;       /**< Request operation type. */

    union
    {
        struct
        {
            uint32_t        obj_type;       /**< Object type of the object to be created for a request of type @ref NRF_DFU_OBJECT_OP_CREATE. */
            uint32_t        object_size;    /**< Size of the object to be created for a request of type @ref NRF_DFU_OBJECT_OP_CREATE. Note that the object size is not the same as the size of the firmware. */
        };

        struct
        {
            uint8_t *   p_req;      /**< Pointer to an array holding the serialized version of the request. */
            uint32_t    req_len;    /**< Length of the request array. */
        };
    };
} nrf_dfu_req_t;


/** @brief Response used during DFU operations.
 */
typedef struct
{
    union
    {
        struct
        {
            uint8_t *       p_res;          /**< Pointer to an array holding the serialized version of the response. */
            uint32_t        res_len;        /**< Length of the response array. */
        };

        struct
        {
            uint32_t        max_size;       /**< Maximum size of the object of a given type. */
            uint32_t        offset;         /**< Current offset. */
            uint32_t        crc;            /**< Current CRC. */
        };
    };
} nrf_dfu_res_t;

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
  // Leave anonymous unions enabled.
#elif defined(__GNUC__)
  // Anonymous unions are enabled by default.
#endif


/** @brief Function for initializing the request handling module.
 *
 * @details This function initializes the flash with or without the SoftDevice, depending on the project configuration.
 *
 * @retval NRF_SUCCESS             If the operation was successful.
 * @retval NRF_ERROR_INVALID_STATE If the fstorage module could not be initiated or the SoftDevice could not set the event handler.
 */
uint32_t nrf_dfu_req_handler_init(void);


/** @brief  Function type for handling a DFU request.
 *
 * @param[in,out]   p_context   Pointer to context-specific RAM required for
 *                              running the command request.
 *                              This value may be NULL if the command request
 *                              does not require context-specific RAM.
 * @param[in,out]   p_req       Pointer to the structure holding the DFU request.
 * @param[in,out]   p_res       Pointer to the structure holding the DFU response.
 *
 * @retval NRF_DFU_RES_CODE_SUCCESS     If the command request was executed successfully.
 *                                      Any other error code indicates that the request
 *                                      could not be handled.
 */
nrf_dfu_res_code_t nrf_dfu_req_handler_on_req(void * p_context, nrf_dfu_req_t * p_req, nrf_dfu_res_t * p_res);


/** @brief Function for resetting the device when the DFU process is complete.
 *
 *  @details    Checks if the DFU transfer is complete. If it is complete, all transports are closed down
 *              and reset is called.
 */
void nrf_dfu_req_handler_reset_if_dfu_complete(void);


#ifdef __cplusplus
}
#endif

#endif // NRF_DFU_REQ_HANDLER_H__

/** @} */
