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
/* Disclaimer: This client implementation of the Apple Notification Center Service can and will be changed at any time by Nordic Semiconductor ASA.
 * Server implementations such as the ones found in iOS can be changed at any time by Apple and may cause this client implementation to stop working.
 */

 #include "nrf_ble_ancs_c.h"
 #include "ancs_attr_parser.h"
 #include "nrf_log.h"


static bool all_req_attrs_parsed(ble_ancs_c_t * p_ancs)
{
    if (p_ancs->parse_info.expected_number_of_attrs == 0)
    {
        return true;
    }
    return false;
}

static bool attr_is_requested(ble_ancs_c_t * p_ancs, ble_ancs_c_attr_t attr)
{
    if(p_ancs->parse_info.p_attr_list[attr.attr_id].get == true)
    {
        return true;
    }
    return false;
}


/**@brief Function for parsing command id and notification id.
 *        Used in the @ref parse_get_notif_attrs_response state machine.
 *
 * @details UID and command ID will be received only once at the beginning of the first
 *          GATTC notification of a new attribute request for a given iOS notification.
 *
 * @param[in] p_ancs     Pointer to an ANCS instance to which the event belongs.
 * @param[in] p_data_src Pointer to data that was received from the Notification Provider.
 * @param[in] index      Pointer to an index that helps us keep track of the current data to be parsed.
 *
 * @return The next parse state.
 */
static ble_ancs_c_parse_state_t command_id_parse(ble_ancs_c_t  * p_ancs,
                                                           const uint8_t * p_data_src,
                                                           uint32_t      * index)
{
    ble_ancs_c_parse_state_t parse_state;

    p_ancs->parse_info.command_id = (ble_ancs_c_cmd_id_val_t) p_data_src[(*index)++];

    switch (p_ancs->parse_info.command_id)
    {
        case BLE_ANCS_COMMAND_ID_GET_NOTIF_ATTRIBUTES:
            p_ancs->evt.evt_type = BLE_ANCS_C_EVT_NOTIF_ATTRIBUTE;
            p_ancs->parse_info.p_attr_list  = p_ancs->ancs_notif_attr_list;
            p_ancs->parse_info.nb_of_attr   = BLE_ANCS_NB_OF_NOTIF_ATTR;
            parse_state                     = NOTIF_UID;
            break;

        case BLE_ANCS_COMMAND_ID_GET_APP_ATTRIBUTES:
            p_ancs->evt.evt_type = BLE_ANCS_C_EVT_APP_ATTRIBUTE;
            p_ancs->parse_info.p_attr_list  = p_ancs->ancs_app_attr_list;
            p_ancs->parse_info.nb_of_attr   = BLE_ANCS_NB_OF_APP_ATTR;
            parse_state                     = APP_ID;
            break;

        default:
            //no valid command_id, abort the rest of the parsing procedure.
            NRF_LOG_DEBUG("Invalid Command ID");
            parse_state = DONE;
            break;
    }
    return parse_state;
}


static ble_ancs_c_parse_state_t notif_uid_parse(ble_ancs_c_t  * p_ancs,
                                                const uint8_t * p_data_src,
                                                uint32_t      * index)
{
     p_ancs->evt.notif_uid = uint32_decode(&p_data_src[*index]);
     *index               += sizeof(uint32_t);
     return ATTR_ID;
}

static ble_ancs_c_parse_state_t app_id_parse(ble_ancs_c_t  * p_ancs,
                                             const uint8_t * p_data_src,
                                             uint32_t      * index)
{
    p_ancs->evt.app_id[p_ancs->parse_info.current_app_id_index] = p_data_src[(*index)++];

    if(p_ancs->evt.app_id[p_ancs->parse_info.current_app_id_index] != '\0')
    {
        p_ancs->parse_info.current_app_id_index++;
        return APP_ID;
    }
    else
    {
        return ATTR_ID;
    }
}

/**@brief Function for parsing the id of an iOS attribute.
 *        Used in the @ref parse_get_notif_attrs_response state machine.
 *
 * @details We only request attributes that are registered with @ref ble_ancs_c_attr_add
 *          once they have been reveiced we stop parsing.
 *
 * @param[in] p_ancs     Pointer to an ANCS instance to which the event belongs.
 * @param[in] p_data_src Pointer to data that was received from the Notification Provider.
 * @param[in] index      Pointer to an index that helps us keep track of the current data to be parsed.
 *
 * @return The next parse state.
 */
static ble_ancs_c_parse_state_t attr_id_parse(ble_ancs_c_t  * p_ancs,
                                              const uint8_t * p_data_src,
                                              uint32_t      * index)
{
        p_ancs->evt.attr.attr_id     = p_data_src[(*index)++];

        if (p_ancs->evt.attr.attr_id >= p_ancs->parse_info.nb_of_attr)
        {
            NRF_LOG_DEBUG("Attribute ID Invalid.\r\n");
            return DONE;
        }
        p_ancs->evt.attr.p_attr_data = p_ancs->parse_info.p_attr_list[p_ancs->evt.attr.attr_id].p_attr_data;

        if (all_req_attrs_parsed(p_ancs))
        {
            NRF_LOG_DEBUG("All requested attributes received. \r\n");
            return DONE;
        }
        else
        {
            if (attr_is_requested(p_ancs, p_ancs->evt.attr))
            {
                p_ancs->parse_info.expected_number_of_attrs--;
            }
            NRF_LOG_DEBUG("Attribute ID %i \r\n", p_ancs->evt.attr.attr_id);
            return ATTR_LEN1;
        }
}


/**@brief Function for parsing the length of an iOS attribute.
 *        Used in the @ref parse_get_notif_attrs_response state machine.
 *
 * @details The Length is 2 bytes. Since there is a chance we reveice the bytes in two different
 *          GATTC notifications, we parse only the first byte here and then set the state machine
 *          ready to parse the next byte.
 *
 * @param[in] p_ancs     Pointer to an ANCS instance to which the event belongs.
 * @param[in] p_data_src Pointer to data that was received from the Notification Provider.
 * @param[in] index      Pointer to an index that helps us keep track of the current data to be parsed.
 *
 * @return The next parse state.
 */
static ble_ancs_c_parse_state_t attr_len1_parse(ble_ancs_c_t * p_ancs, const uint8_t * p_data_src, uint32_t * index)
{
    p_ancs->evt.attr.attr_len = p_data_src[(*index)++];
    return ATTR_LEN2;
}

/**@brief Function for parsing the length of an iOS attribute.
 *        Used in the @ref parse_get_notif_attrs_response state machine.
 *
 * @details Second byte of the length field. If the length is zero, it means that the attribute is not
 *          present and the state machine is set to parse the next attribute.
 *
 * @param[in] p_ancs     Pointer to an ANCS instance to which the event belongs.
 * @param[in] p_data_src Pointer to data that was received from the Notification Provider.
 * @param[in] index      Pointer to an index that helps us keep track of the current data to be parsed.
 *
 * @return The next parse state.
 */
static ble_ancs_c_parse_state_t attr_len2_parse(ble_ancs_c_t * p_ancs, const uint8_t * p_data_src, uint32_t * index)
{
    p_ancs->evt.attr.attr_len |= (p_data_src[(*index)++] << 8);
    p_ancs->parse_info.current_attr_index = 0;

    if (p_ancs->evt.attr.attr_len != 0)
    {
        //If the attribute has a length but there is no allocated space for this attribute
        if((p_ancs->parse_info.p_attr_list[p_ancs->evt.attr.attr_id].attr_len == 0) ||
           (p_ancs->parse_info.p_attr_list[p_ancs->evt.attr.attr_id].p_attr_data == NULL))
        {
            return ATTR_SKIP;
        }
        else
        {
            return ATTR_DATA;
        }
    }
    else
    {

        NRF_LOG_DEBUG("Attribute LEN %i \r\n", p_ancs->evt.attr.attr_len);
        if(attr_is_requested(p_ancs, p_ancs->evt.attr))
        {
            p_ancs->evt_handler(&p_ancs->evt);
        }
        if(all_req_attrs_parsed(p_ancs))
        {
            return DONE;
        }
        else
        {
            return ATTR_ID;
        }
    }
}


/**@brief Function for parsing the data of an iOS attribute.
 *        Used in the @ref parse_get_notif_attrs_response state machine.
 *
 * @details Read the data of the attribute into our local buffer.
 *
 * @param[in] p_ancs     Pointer to an ANCS instance to which the event belongs.
 * @param[in] p_data_src Pointer to data that was received from the Notification Provider.
 * @param[in] index      Pointer to an index that helps us keep track of the current data to be parsed.
 *
 * @return The next parse state.
 */
static ble_ancs_c_parse_state_t attr_data_parse(ble_ancs_c_t  * p_ancs,
                                                const uint8_t * p_data_src,
                                                uint32_t      * index)
{
    // We have not reached the end of the attribute, nor our max allocated internal size.
    // Proceed with copying data over to our buffer.
    if (   (p_ancs->parse_info.current_attr_index < p_ancs->parse_info.p_attr_list[p_ancs->evt.attr.attr_id].attr_len)
        && (p_ancs->parse_info.current_attr_index < p_ancs->evt.attr.attr_len))
    {
        //NRF_LOG_DEBUG("Byte copied to buffer: %c\r\n", p_data_src[(*index)]); // Un-comment this line to see every byte of an attribute as it is parsed. Commented out by default since it can overflow the uart buffer.
        p_ancs->evt.attr.p_attr_data[p_ancs->parse_info.current_attr_index++] = p_data_src[(*index)++];
    }

    // We have reached the end of the attribute, or our max allocated internal size.
    // Stop copying data over to our buffer. NUL-terminate at the current index.
    if ( (p_ancs->parse_info.current_attr_index == p_ancs->evt.attr.attr_len) ||
         (p_ancs->parse_info.current_attr_index == p_ancs->parse_info.p_attr_list[p_ancs->evt.attr.attr_id].attr_len - 1))
    {
        if (attr_is_requested(p_ancs, p_ancs->evt.attr))
        {
            p_ancs->evt.attr.p_attr_data[p_ancs->parse_info.current_attr_index] = '\0';
        }

        // If our max buffer size is smaller than the remaining attribute data, we must
        // increase index to skip the data until the start of the next attribute.
        if (p_ancs->parse_info.current_attr_index < p_ancs->evt.attr.attr_len)
        {
            return ATTR_SKIP;
        }
        NRF_LOG_DEBUG("Attribute finished!\r\n");
        if(attr_is_requested(p_ancs, p_ancs->evt.attr))
        {
            p_ancs->evt_handler(&p_ancs->evt);
        }
        if(all_req_attrs_parsed(p_ancs))
        {
            return DONE;
        }
        else
        {
            return ATTR_ID;
        }
    }
    return ATTR_DATA;
}


static ble_ancs_c_parse_state_t attr_skip(ble_ancs_c_t * p_ancs, const uint8_t * p_data_src, uint32_t * index)
{
    // We have not reached the end of the attribute, nor our max allocated internal size.
    // Proceed with copying data over to our buffer.
    if (p_ancs->parse_info.current_attr_index < p_ancs->evt.attr.attr_len)
    {
        p_ancs->parse_info.current_attr_index++;
        (*index)++;
    }
    // At the end of the attribute, determine if it should be passed to event handler and
    // continue parsing the next attribute ID if we are not done with all the attributes.
    if (p_ancs->parse_info.current_attr_index == p_ancs->evt.attr.attr_len)
    {
        if(attr_is_requested(p_ancs, p_ancs->evt.attr))
        {
            p_ancs->evt_handler(&p_ancs->evt);
        }
        if(all_req_attrs_parsed(p_ancs))
        {
            return DONE;
        }
        else
        {
            return ATTR_ID;
        }
    }
    return ATTR_SKIP;
}


void ancs_parse_get_attrs_response(ble_ancs_c_t  * p_ancs,
                                   const uint8_t * p_data_src,
                                   const uint16_t  hvx_data_len)
{
    uint32_t index;

    for (index = 0; index < hvx_data_len;)
    {
        switch (p_ancs->parse_info.parse_state)
        {
            case COMMAND_ID:
                p_ancs->parse_info.parse_state = command_id_parse(p_ancs, p_data_src, &index);
                break;

            case NOTIF_UID:
                p_ancs->parse_info.parse_state = notif_uid_parse(p_ancs, p_data_src, &index);
                break;

            case APP_ID:
                p_ancs->parse_info.parse_state = app_id_parse(p_ancs, p_data_src, &index);
                break;

            case ATTR_ID:
                p_ancs->parse_info.parse_state = attr_id_parse(p_ancs, p_data_src, &index);
                break;

            case ATTR_LEN1:
                p_ancs->parse_info.parse_state = attr_len1_parse(p_ancs, p_data_src, &index);
                break;

            case ATTR_LEN2:
                p_ancs->parse_info.parse_state = attr_len2_parse(p_ancs, p_data_src, &index);
                break;

            case ATTR_DATA:
                p_ancs->parse_info.parse_state = attr_data_parse(p_ancs, p_data_src, &index);
                break;

            case ATTR_SKIP:
                p_ancs->parse_info.parse_state = attr_skip(p_ancs, p_data_src, &index);
                break;

            case DONE:
                NRF_LOG_DEBUG("Parse state: Done \r\n");
                index = hvx_data_len;
                break;

            default:
                // Default case will never trigger intentionally. Go to the DONE state to minimize the consequences.
                p_ancs->parse_info.parse_state = DONE;
                break;
        }
    }
}
