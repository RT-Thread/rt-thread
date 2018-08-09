/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
/* Disclaimer: This client implementation of the Apple Notification Center Service can and will be changed at any time by Nordic Semiconductor ASA.
 * Server implementations such as the ones found in iOS can be changed at any time by Apple and may cause this client implementation to stop working.
 */

#include "ancs_app_attr_get.h"
#include "nrf_ble_ancs_c.h"
#include "ancs_tx_buffer.h"
#include "sdk_macros.h"
#include "nrf_log.h"
#include "string.h"

#define GATTC_OPCODE_SIZE                1      /**< Size of the GATTC OPCODE. */
#define GATTC_ATTR_HANDLE_SIZE           4      /**< Size of the Attribute handle Size. */


#define ANCS_GATTC_WRITE_PAYLOAD_LEN_MAX (BLE_GATT_ATT_MTU_DEFAULT - GATTC_OPCODE_SIZE - GATTC_ATTR_HANDLE_SIZE)  /**< Maximum Length of the data we can send in one write. */


/**@brief Enum to keep track of the state based encoding while requesting App attributes. */
typedef enum
{
    APP_ATTR_COMMAND_ID, /**< Currently encoding the Command ID. */
    APP_ATTR_APP_ID,     /**< Currently encoding the App ID. */
    APP_ATTR_ATTR_ID,    /**< Currently encoding the Attribute ID. */
    APP_ATTR_DONE        /**< Encoding done. */
}encode_app_attr_t;


/**@brief Function for determening if an attribute is desired to get.
 *
 * @param[in] p_ancs iOS notification structure. This structure must be supplied by
 *                   the application. It identifies the particular client instance to use.
 *
 * @return True  If it is requested
 * @return False If it is not be requested.
*/
static bool app_attr_is_requested(ble_ancs_c_t * p_ancs, uint32_t attr_id)
{
    if (p_ancs->ancs_app_attr_list[attr_id].get == true)
    {
        return true;
    }
    return false;
}

/**@brief Function for counting the number of attributes that will be requested upon a Get App Attribute.
 *
 * @param[in] p_ancs iOS notification structure. This structure must be supplied by
 *                   the application. It identifies the particular client instance to use.
 *
 * @return           Number of attributes that will be requested upon a Get App Attribute.
*/
static uint32_t app_attr_nb_to_get(ble_ancs_c_t * p_ancs)
{
    uint32_t attr_nb_to_get = 0;
    for (uint32_t i = 0; i < (sizeof(p_ancs->ancs_app_attr_list)/sizeof(ble_ancs_c_attr_list_t)); i++)
    {
        if (app_attr_is_requested(p_ancs,i))
        {
            attr_nb_to_get++;
        }
    }
    return attr_nb_to_get;
}


/**@brief Function for encoding the Command ID as part of assembling a "Get App Attributes" command.
 *
 * @param[in] conn_handle  Connection handle for where the prepared write will be executed.
 * @param[in] handle_value The handle that will receive the execute command.
 * @param[in] p_offset     Pointer to the offset for the write.
 * @param[in] p_index      Pointer to the length encoded so far for the current write.
 * @param[in,out] p_msg    Pointer to the tx message that has been filled out and will be added to
 *                         tx queue in this function.
 */
static void queued_write_tx_message(uint16_t       conn_handle,
                                    uint16_t       handle_value,
                                    uint16_t     * p_offset,
                                    uint32_t     * p_index,
                                    tx_message_t * p_msg)
{
    NRF_LOG_DEBUG("Starting new TX message.");

    p_msg->conn_handle                         = conn_handle;
    p_msg->type                                = WRITE_REQ;
    p_msg->req.write_req.gattc_params.len      = *p_index;
    p_msg->req.write_req.gattc_params.handle   = handle_value;
    p_msg->req.write_req.gattc_params.p_value  = p_msg->req.write_req.gattc_value;

    p_msg->req.write_req.gattc_params.offset   = *p_offset;

    p_msg->req.write_req.gattc_params.write_op = BLE_GATT_OP_PREP_WRITE_REQ;

    tx_buffer_insert(p_msg);
}


/**@brief Function for encoding the Command ID as part of assembling a "Get App Attributes" command.
 *
 * @param[in]     p_ancs     iOS notification structure. This structure must be supplied by
 *                           the application. It identifies the particular client instance to use.
 * @param[in]     p_index    Pointer to the length encoded so far for the current write.
 * @param[in]     p_offset   Pointer to the accumulated offset for the next write.
 * @param[in,out] p_msg      Pointer to the tx message that will be filled out in this function.
 */
static encode_app_attr_t app_attr_encode_cmd_id(ble_ancs_c_t  * p_ancs,
                                                uint32_t      * index,
                                                tx_message_t  * p_msg)
{
    NRF_LOG_DEBUG("Encoding Command ID");

    // Encode Command ID.
    p_msg->req.write_req.gattc_value[(*index)++] = BLE_ANCS_COMMAND_ID_GET_APP_ATTRIBUTES;
    return APP_ATTR_APP_ID;
}

/**@brief Function for encoding the App Identifier as part of assembling a "Get App Attributes" command.
 *
 * @param[in] p_ancs     iOS notification structure. This structure must be supplied by
 *                       the application. It identifies the particular client instance to use.
 * @param[in] p_app_id   The App ID for the App which we will request App Attributes for.
 * @param[in] app_id_len Length of the App ID.
 * @param[in] p_index    Pointer to the length encoded so far for the current write.
 * @param[in] p_offset   Pointer to the accumulated offset for the next write.
 * @param[in] p_app_id_bytes_encoded_count Variable to keep count of the encoded APP ID bytes.
 *                                         As long as it is lower than the length of the App ID,
 *                                         parsing will continue.
 */
static encode_app_attr_t app_attr_encode_app_id(ble_ancs_c_t  * p_ancs,
                                                uint32_t      * p_index,
                                                uint16_t      * p_offset,
                                                tx_message_t  * p_msg,
                                                const uint8_t * p_app_id,
                                                const uint32_t  app_id_len,
                                                uint32_t      * p_app_id_bytes_encoded_count)
{
    NRF_LOG_DEBUG("Encoding APP ID");
    if (*p_index >= ANCS_GATTC_WRITE_PAYLOAD_LEN_MAX)
    {
        queued_write_tx_message(p_ancs->conn_handle, p_ancs->service.control_point_char.handle_value, p_offset, p_index, p_msg);
        *(p_offset) += *p_index;
        *p_index = 0;
    }

    //Encode App Identifier.
    if (*p_app_id_bytes_encoded_count == app_id_len)
    {
        p_msg->req.write_req.gattc_value[(*p_index)++] = '\0';
        (*p_app_id_bytes_encoded_count)++;
    }
    NRF_LOG_DEBUG("%c", p_app_id[(*p_app_id_bytes_encoded_count)]);
    if (*p_app_id_bytes_encoded_count < app_id_len)
    {
        p_msg->req.write_req.gattc_value[(*p_index)++] = p_app_id[(*p_app_id_bytes_encoded_count)++];
    }
    if (*p_app_id_bytes_encoded_count > app_id_len)
    {
        return APP_ATTR_ATTR_ID;
    }
    return APP_ATTR_APP_ID;
}

/**@brief Function for encoding the Attribute ID as part of assembling a "Get App Attributes" command.
 *
 * @param[in] p_ancs iOS notification structure. This structure must be supplied by
 *
 * @param[in]     p_index      Pointer to the length encoded so far for the current write.
 * @param[in]     p_offset     Pointer to the accumulated offset for the next write.
 * @param[in,out] p_msg        Pointer to the tx message that will be filled out in this function.
 * @param[in]     p_attr_count Pointer to a variable that iterates the possible App Attributes.
 */
static encode_app_attr_t app_attr_encode_attr_id(ble_ancs_c_t  * p_ancs,
                                                 uint32_t      * p_index,
                                                 uint16_t      * p_offset,
                                                 tx_message_t  * p_msg,
                                                 uint32_t      * p_attr_count,
                                                 uint32_t      * attr_get_total_nb)
{
    NRF_LOG_DEBUG("Encoding Attribute ID");
    if ((*p_index) >= ANCS_GATTC_WRITE_PAYLOAD_LEN_MAX)
    {
        queued_write_tx_message(p_ancs->conn_handle,
                                p_ancs->service.control_point_char.handle_value,
                                p_offset, p_index, p_msg);
        *(p_offset) += *p_index;
        *p_index = 0;
    }
    //Encode Attribute ID.
    if (*p_attr_count < BLE_ANCS_NB_OF_APP_ATTR)
    {
        if (app_attr_is_requested(p_ancs, *p_attr_count))
        {
            p_msg->req.write_req.gattc_value[(*p_index)] = *p_attr_count;
            p_ancs->number_of_requested_attr++;
            (*p_index)++;
            NRF_LOG_DEBUG("offset %i", *p_offset);
        }
        (*p_attr_count)++;
    }
    if (*p_attr_count == BLE_ANCS_NB_OF_APP_ATTR)
    {
        return APP_ATTR_DONE;
    }
    return APP_ATTR_APP_ID;
}

/**@brief Function for writing the execute write command to a handle for a given connection.
 *
 * @param[in] conn_handle  Connection handle for where the prepared write will be executed.
 * @param[in] handle_value The handle that will receive the execute command.
 * @param[in] p_msg        Pointer to the message that will be filled out in this function and then
 *                         added to the tx queue.
 */
static void app_attr_execute_write(uint16_t conn_handle, uint16_t handle_value, tx_message_t * p_msg)
{
    NRF_LOG_DEBUG("Sending Execute Write.");
    memset(p_msg,0,sizeof(tx_message_t));

    p_msg->req.write_req.gattc_params.handle   = handle_value;
    p_msg->req.write_req.gattc_params.p_value  = p_msg->req.write_req.gattc_value;
    p_msg->req.write_req.gattc_params.offset   = 0;
    p_msg->req.write_req.gattc_params.write_op = BLE_GATT_OP_EXEC_WRITE_REQ;
    p_msg->req.write_req.gattc_params.flags    = BLE_GATT_EXEC_WRITE_FLAG_PREPARED_WRITE;

    p_msg->req.write_req.gattc_params.len       = 0;
    p_msg->conn_handle                          = conn_handle;
    p_msg->type                                 = WRITE_REQ;

    tx_buffer_insert(p_msg);
}


/**@brief Function for sending a get App Attributes request.
 *
 * @details Since the APP id may not fit in a single write, we use long write
 *          with a state machine to encode the Get App Attribute request.
 *
 * @param[in] p_ancs     iOS notification structure. This structure must be supplied by
 *                       the application. It identifies the particular client instance to use.
 * @param[in] p_app_id   The App ID for the App which we will request App Attributes for.
 * @param[in] app_id_len Length of the App ID.
 *
*/
static uint32_t app_attr_get(ble_ancs_c_t  * p_ancs,
                             const uint8_t * p_app_id,
                             uint32_t        app_id_len)
{
    uint32_t          index                      = 0;
    uint32_t          attr_bytes_encoded_count   = 0;
    uint16_t          offset                     = 0;
    uint32_t          app_id_bytes_encoded_count = 0;
    encode_app_attr_t state                      = APP_ATTR_COMMAND_ID;
    p_ancs->number_of_requested_attr             = 0;

    uint32_t     attr_get_total_nb = app_attr_nb_to_get(p_ancs);
    tx_message_t p_msg;

    memset(&p_msg, 0, sizeof(tx_message_t));

    while (state != APP_ATTR_DONE)
    {
        switch (state)
        {
            case APP_ATTR_COMMAND_ID:
                state = app_attr_encode_cmd_id(p_ancs,
                                               &index,
                                               &p_msg);
            break;
            case APP_ATTR_APP_ID:
                state = app_attr_encode_app_id(p_ancs,
                                               &index,
                                               &offset,
                                               &p_msg,
                                               p_app_id,
                                               app_id_len,
                                               &app_id_bytes_encoded_count);
            break;
            case APP_ATTR_ATTR_ID:
                state = app_attr_encode_attr_id(p_ancs,
                                                &index,
                                                &offset,
                                                &p_msg,
                                                &attr_bytes_encoded_count,
                                                &attr_get_total_nb);
                break;
            case APP_ATTR_DONE:
                break;
            default:
                break;
        }
    }
    queued_write_tx_message(p_ancs->conn_handle,
                            p_ancs->service.control_point_char.handle_value,
                            &offset,
                            &index,
                            &p_msg);

    app_attr_execute_write(p_ancs->conn_handle,
                           p_ancs->service.control_point_char.handle_value,
                           &p_msg);

    p_ancs->parse_info.expected_number_of_attrs = p_ancs->number_of_requested_attr;

    tx_buffer_process();
    return NRF_SUCCESS;
}


uint32_t ancs_c_app_attr_request(ble_ancs_c_t          * p_ancs,
                                         const uint8_t * p_app_id,
                                         uint32_t        len)
{
    uint32_t err_code;

    if (len == 0)
    {
        return NRF_ERROR_DATA_SIZE;
    }
    if (p_app_id[len] != '\0') // App id to be requestes must be NULL terminated
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    p_ancs->parse_info.parse_state = COMMAND_ID;
    err_code                       = app_attr_get(p_ancs, p_app_id, len);
    VERIFY_SUCCESS(err_code);
    return NRF_SUCCESS;
}
