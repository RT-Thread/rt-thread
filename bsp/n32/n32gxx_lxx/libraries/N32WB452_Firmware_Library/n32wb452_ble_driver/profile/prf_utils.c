/**
 ****************************************************************************************
 *
 * @file prf_utils.c
 *
 * @brief Implementation of Profile Utilities
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */


/**
 ****************************************************************************************
 * @addtogroup PRF_UTILS
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"
#if (BLE_PROFILES)
#if (BLE_SERVER_PRF || BLE_CLIENT_PRF)

#include <stdint.h>
#include <stdbool.h>
#include "ke_task.h"
#include "attm.h"
#include "gattc_task.h"
#include "prf_utils.h"
#include "gap.h"
#include "gapc.h"

#include "ke_mem.h"
#include "co_utils.h"
#include "co_error.h"

#endif /* (BLE_SERVER_PRF || BLE_CLIENT_PRF) */

/*
 * LOCAL FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */

/*
 * EXPORTED FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */

#if (BLE_BATT_SERVER)
void prf_pack_char_pres_fmt(uint8_t *packed_val, const struct prf_char_pres_fmt* char_pres_fmt)
{
    *packed_val =               char_pres_fmt->format;
    *(packed_val + 1) =         char_pres_fmt->exponent;
    co_write16p(packed_val + 2, char_pres_fmt->unit);
    *(packed_val + 4) =         char_pres_fmt->name_space;
    co_write16p(packed_val + 5, char_pres_fmt->description);
}
#endif // (BLE_BATT_SERVER)

#if (BLE_BATT_CLIENT)
void prf_unpack_char_pres_fmt(const uint8_t *packed_val, struct prf_char_pres_fmt* char_pres_fmt)
{

    char_pres_fmt->format       = *packed_val;
    char_pres_fmt->exponent     = *(packed_val + 1);
    char_pres_fmt->unit         = co_read16p(packed_val + 2);
    char_pres_fmt->name_space    = *(packed_val + 4);
    char_pres_fmt->description  = co_read16p(packed_val + 5);
}
#endif // (BLE_BATT_CLIENT)


#if (BLE_CLIENT_PRF)
void prf_read_char_send(prf_env_t *prf_env, uint8_t conidx,
                        uint16_t shdl, uint16_t ehdl, uint16_t valhdl)
{
    struct gattc_read_cmd * req  = KE_MSG_ALLOC(GATTC_READ_CMD, KE_BUILD_ID(TASK_GATTC, conidx),
            prf_src_task_get(prf_env, conidx), gattc_read_cmd);
    //request type
    req->operation                       = GATTC_READ;
    req->nb                             = 1;
    req->req.simple.offset              = 0;
    req->req.simple.length              = 0;
    req->req.simple.handle              = valhdl;

    //send request to GATT
    ke_msg_send(req);
}

void prf_register_atthdl2gatt(prf_env_t *prf_env, uint8_t conidx, struct prf_svc *svc)
{
    if (svc->shdl != ATT_INVALID_HANDLE)
    {
        //register profile task in gatt for indication/notifications
        struct gattc_reg_to_peer_evt_cmd * reg = KE_MSG_ALLOC(GATTC_REG_TO_PEER_EVT_CMD,
                KE_BUILD_ID(TASK_GATTC, conidx), prf_src_task_get(prf_env, conidx),
                gattc_reg_to_peer_evt_cmd);

        reg->operation =  GATTC_REGISTER;
        reg->start_hdl = svc->shdl;
        reg->end_hdl =   svc->ehdl;

        ke_msg_send(reg);
    }
}

void prf_unregister_atthdl2gatt(prf_env_t *prf_env, uint8_t conidx, struct prf_svc *svc)
{
    if (svc->shdl != ATT_INVALID_HANDLE)
    {
        //un register profile task in gatt for indication/notifications
        struct gattc_reg_to_peer_evt_cmd * reg = KE_MSG_ALLOC(GATTC_REG_TO_PEER_EVT_CMD,
                KE_BUILD_ID(TASK_GATTC, conidx), prf_src_task_get(prf_env, conidx),
                gattc_reg_to_peer_evt_cmd);

        reg->operation =  GATTC_UNREGISTER;
        reg->start_hdl = svc->shdl;
        reg->end_hdl =   svc->ehdl;

        ke_msg_send(reg);
    }
}


void prf_disc_svc_send(prf_env_t *prf_env, uint8_t conidx, uint16_t uuid)
{
    //send GATT discover primary services by UUID request
    struct gattc_sdp_svc_disc_cmd * svc_req = KE_MSG_ALLOC_DYN(GATTC_SDP_SVC_DISC_CMD,
            KE_BUILD_ID(TASK_GATTC, conidx), prf_src_task_get(prf_env, conidx),
            gattc_sdp_svc_disc_cmd, ATT_UUID_16_LEN);

    //gatt request type: by UUID
    svc_req->operation         = GATTC_SDP_DISC_SVC;
    //start handle;
    svc_req->start_hdl        = ATT_1ST_REQ_START_HDL;
    //end handle
    svc_req->end_hdl          = ATT_1ST_REQ_END_HDL;

    // UUID search
    svc_req->uuid_len = ATT_UUID_16_LEN;

    //set the first two bytes to the value array, LSB to MSB:Health Thermometer Service UUID first
    co_write16p(&(svc_req->uuid[0]), uuid);

    //send the message to GATT, which will send back the response when it gets it
    ke_msg_send(svc_req);
}



void prf_gatt_write(prf_env_t *prf_env, uint8_t conidx,
                    uint16_t handle, uint8_t* value, uint16_t length, uint8_t operation)
{
    if (handle != ATT_INVALID_HANDLE)
    {
        struct gattc_write_cmd *wr_char = KE_MSG_ALLOC_DYN(GATTC_WRITE_CMD,
                KE_BUILD_ID(TASK_GATTC, conidx), prf_src_task_get(prf_env, conidx),
                gattc_write_cmd, length);

        // Offset
        wr_char->offset         = 0x0000;
        // cursor always 0
        wr_char->cursor         = 0x0000;
        // Write Type
        wr_char->operation       = operation;
        // Characteristic Value attribute handle
        wr_char->handle         = handle;
        // Value Length
        wr_char->length         = length;
        // Auto Execute
        wr_char->auto_execute   = true;
        // Value
        memcpy(&wr_char->value[0], value, length);

        // Send the message
        ke_msg_send(wr_char);
    }
}

void prf_gatt_write_ntf_ind(prf_env_t *prf_env, uint8_t conidx, uint16_t handle, uint16_t ntf_ind_cfg)
{
    uint8_t value[2];

    // put value in air format
    co_write16p((&value[0]), ntf_ind_cfg);
    // write value over GATT
    prf_gatt_write(prf_env, conidx, handle, value, 2, GATTC_WRITE);
}

uint8_t prf_check_svc_char_validity(uint8_t nb_chars,
                                    const struct prf_char_inf* chars,
                                    const struct prf_char_def* chars_req)
{
    uint8_t status = GAP_ERR_NO_ERROR;
    uint8_t i;

    for(i = 0; ((i < nb_chars) && (status == GAP_ERR_NO_ERROR)); i++)
    {
        if (chars[i].char_hdl == ATT_INVALID_HANDLE)
        {
            //If Characteristic is not present, check requirements
            if (chars_req[i].req_flag == ATT_MANDATORY)
            {
                status = PRF_ERR_STOP_DISC_CHAR_MISSING;
            }
        }
        else
        {
            //If Characteristic is present, check properties
            if ((chars[i].prop & chars_req[i].prop_mand) != chars_req[i].prop_mand)
            {
                status = PRF_ERR_STOP_DISC_WRONG_CHAR_PROP;
            }
        }
    }

    return (status);
}


uint8_t prf_check_svc_char_uuid128_validity(uint8_t nb_chars,
                                    const struct prf_char_inf* chars,
                                    const struct prf_char_uuid128_def* chars_req)
{
    uint8_t status = GAP_ERR_NO_ERROR;
    uint8_t i;

    for(i = 0; ((i < nb_chars) && (status == GAP_ERR_NO_ERROR)); i++)
    {
        if (chars[i].char_hdl == ATT_INVALID_HANDLE)
        {
            //If Characteristic is not present, check requirements
            if (chars_req[i].req_flag == ATT_MANDATORY)
            {
                status = PRF_ERR_STOP_DISC_CHAR_MISSING;
            }
        }
        else
        {
            //If Characteristic is present, check properties
            if ((chars[i].prop & chars_req[i].prop_mand) != chars_req[i].prop_mand)
            {
                status = PRF_ERR_STOP_DISC_WRONG_CHAR_PROP;
            }
        }
    }

    return (status);
}


uint8_t prf_check_svc_char_desc_validity(uint8_t descs_size,
                                         const struct prf_char_desc_inf* descs,
                                         const struct prf_char_desc_def* descs_req,
                                         const struct prf_char_inf* chars)
{
    uint8_t status = GAP_ERR_NO_ERROR;
    uint8_t i;

    for(i = 0; ((i < descs_size) && (status == GAP_ERR_NO_ERROR)) ; i++)
    {
        if (descs[i].desc_hdl == ATT_INVALID_HANDLE)
        {
            //If Descriptor is missing, check if it is mandatory
            if (descs_req[i].req_flag == ATT_MANDATORY)
            {
                //Check if Char is present
                if (chars[descs_req[i].char_code].char_hdl != ATT_INVALID_HANDLE)
                {
                    //Char. is present and descriptor not, error
                    status = PRF_ERR_STOP_DISC_CHAR_MISSING;
                }
            }
        }
    }

    return (status);
}


uint8_t prf_check_svc_char_desc_uuid128_validity(uint8_t descs_size,
                                         const struct prf_char_desc_inf* descs,
                                         const struct prf_char_desc_uuid128_def* descs_req,
                                         const struct prf_char_inf* chars)
{
    uint8_t status = GAP_ERR_NO_ERROR;
    uint8_t i;

    for(i = 0; ((i < descs_size) && (status == GAP_ERR_NO_ERROR)) ; i++)
    {
        if (descs[i].desc_hdl == ATT_INVALID_HANDLE)
        {
            //If Descriptor is missing, check if it is mandatory
            if (descs_req[i].req_flag == ATT_MANDATORY)
            {
                //Check if Char is present
                if (chars[descs_req[i].char_code].char_hdl != ATT_INVALID_HANDLE)
                {
                    //Char. is present and descriptor not, error
                    status = PRF_ERR_STOP_DISC_CHAR_MISSING;
                }
            }
        }
    }

    return (status);
}

void prf_extract_svc_info(const struct gattc_sdp_svc_ind* param,
        uint8_t nb_chars, const struct prf_char_def* chars_req, struct prf_char_inf* chars,
        uint8_t nb_descs, const struct prf_char_desc_def* descs_req, struct prf_char_desc_inf* descs)
{
    //Counters
    uint8_t svc_char;
    uint8_t svc_desc;
    uint8_t fnd_att;

    for (fnd_att=0; fnd_att< (param->end_hdl - param->start_hdl); fnd_att++)
    {
        if (param->info[fnd_att].att_type == GATTC_SDP_ATT_CHAR)
        {
            uint16_t char_hdl = param->start_hdl+ 1 + fnd_att;
            uint16_t val_hdl  = param->info[fnd_att].att_char.handle;
            uint8_t  val_prop = param->info[fnd_att].att_char.prop;
            uint8_t  char_idx = fnd_att;

            // check that value handle is in a valid range
            if ((val_hdl <= param->end_hdl) && (val_hdl > (param->start_hdl + fnd_att)))
            {
                // retrieve value index
                uint8_t val_idx = (val_hdl - param->start_hdl - 1);

                //Look over requested characteristics
                for (svc_char=0; svc_char<nb_chars ; svc_char++)
                {
                    // check if attribute is valid
                    if ((chars[svc_char].char_hdl == ATT_INVALID_HDL)
                            && attm_uuid16_comp((uint8_t*)param->info[val_idx].att.uuid,
                                                param->info[val_idx].att.uuid_len, chars_req[svc_char].uuid))
                    {
                        //Save properties and handles
                        chars[svc_char].char_hdl       = char_hdl;
                        chars[svc_char].val_hdl        = val_hdl;
                        chars[svc_char].prop           = val_prop;

                        // find end of characteristic handle and discover descriptors
                        do
                        {
                            fnd_att++;

                            // found a descriptor
                            if (param->info[fnd_att].att_type == GATTC_SDP_ATT_DESC)
                            {
                                //Retrieve characteristic descriptor handle using UUID
                                for(svc_desc = 0; svc_desc<nb_descs; svc_desc++)
                                {
                                    // check if it's expected descriptor
                                    if ((descs[svc_desc].desc_hdl == ATT_INVALID_HANDLE)
                                        && (descs_req[svc_desc].char_code == svc_char)
                                        && (attm_uuid16_comp((uint8_t*)param->info[fnd_att].att.uuid,
                                                param->info[fnd_att].att.uuid_len, descs_req[svc_desc].uuid)))
                                    {
                                        descs[svc_desc].desc_hdl = param->start_hdl + 1 + fnd_att;
                                        // search for next descriptor
                                        break;
                                    }
                                }
                            }
                        } while (((param->start_hdl+ 1 + fnd_att) <= param->end_hdl)
                                && (param->info[fnd_att].att_type != GATTC_SDP_ATT_CHAR)
                                && (param->info[fnd_att].att_type != GATTC_SDP_INC_SVC));

                        // return to previous valid value
                        fnd_att--;
                        // previous handle was end of the characteristic
                        chars[svc_char].char_ehdl_off    = fnd_att - char_idx;

                        // search next characteristic
                        break;
                    }
                }
            }
        }
    }
}


void prf_extract_svc_uuid128_info(const struct gattc_sdp_svc_ind* param,
        uint8_t nb_chars, const struct prf_char_uuid128_def* chars_uuid128_req, struct prf_char_inf* chars,
        uint8_t nb_descs, const struct prf_char_desc_uuid128_def* descs_uuid128_req, struct prf_char_desc_inf* descs)
{
    //Counters
    uint8_t svc_char;
    uint8_t svc_desc;
    uint8_t fnd_att;

    for (fnd_att=0; fnd_att< (param->end_hdl - param->start_hdl); fnd_att++)
    {
        if (param->info[fnd_att].att_type == GATTC_SDP_ATT_CHAR)
        {
            uint16_t char_hdl = param->start_hdl+ 1 + fnd_att;
            uint16_t val_hdl  = param->info[fnd_att].att_char.handle;
            uint8_t  val_prop = param->info[fnd_att].att_char.prop;
            uint8_t  char_idx = fnd_att;

            // check that value handle is in a valid range
            if ((val_hdl <= param->end_hdl) && (val_hdl > (param->start_hdl + fnd_att)))
            {
                // retrieve value index
                uint8_t val_idx = (val_hdl - param->start_hdl - 1);

                //Look over requested characteristics
                for (svc_char=0; svc_char<nb_chars ; svc_char++)
                {
                    // check if attribute is valid
                    if ((chars[svc_char].char_hdl == ATT_INVALID_HDL)
                            && attm_uuid_comp((uint8_t*)param->info[val_idx].att.uuid,
                                                param->info[val_idx].att.uuid_len, &chars_uuid128_req[svc_char].uuid[0], chars_uuid128_req[svc_char].uuid_len))
                    {
                        //Save properties and handles
                        chars[svc_char].char_hdl       = char_hdl;
                        chars[svc_char].val_hdl        = val_hdl;
                        chars[svc_char].prop           = val_prop;

                        // find end of characteristic handle and discover descriptors
                        do
                        {
                            fnd_att++;

                            // found a descriptor
                            if (param->info[fnd_att].att_type == GATTC_SDP_ATT_DESC)
                            {
                                //Retrieve characteristic descriptor handle using UUID
                                for(svc_desc = 0; svc_desc<nb_descs; svc_desc++)
                                {
                                    // check if it's expected descriptor
                                    if ((descs[svc_desc].desc_hdl == ATT_INVALID_HANDLE)
                                        && (descs_uuid128_req[svc_desc].char_code == svc_char)
                                        && (attm_uuid_comp((uint8_t*)param->info[fnd_att].att.uuid,
                                                param->info[fnd_att].att.uuid_len, descs_uuid128_req[svc_desc].uuid, descs_uuid128_req[svc_desc].uuid_len)))
                                    {
                                        descs[svc_desc].desc_hdl = param->start_hdl + 1 + fnd_att;
                                        // search for next descriptor
                                        break;
                                    }
                                }
                            }
                        } while (((param->start_hdl+ 1 + fnd_att) <= param->end_hdl)
                                && (param->info[fnd_att].att_type != GATTC_SDP_ATT_CHAR)
                                && (param->info[fnd_att].att_type != GATTC_SDP_INC_SVC));

                        // return to previous valid value
                        fnd_att--;
                        // previous handle was end of the characteristic
                        chars[svc_char].char_ehdl_off    = fnd_att - char_idx;

                        // search next characteristic
                        break;
                    }
                }
            }
        }
    }
}


#endif //(BLE_CLIENT_PRF)

#if (BLE_CLIENT_PRF || BLE_TIP_SERVER || BLE_AN_SERVER || BLE_PAS_SERVER)

void prf_client_att_info_rsp(prf_env_t *prf_env, uint8_t conidx, uint16_t msg_id,
                             uint8_t status, struct gattc_read_ind const* read_ind)
{
    // retrieve value length
    uint16_t length = 0;
    if (status == GAP_ERR_NO_ERROR)
    {
        length = read_ind->length;
    }

    // prepare response
    struct prf_att_info *rsp = KE_MSG_ALLOC_DYN(msg_id,
            prf_dst_task_get(prf_env, conidx), prf_src_task_get(prf_env, conidx),
            prf_att_info, length);

    rsp->status     = status;
    rsp->handle     = ATT_INVALID_HDL;
    rsp->length     = length;

    // set value array
    if (read_ind != NULL)
    {
        rsp->handle = read_ind->handle;
        memcpy(&(rsp->value[0]), &(read_ind->value[0]), length);
    }

    ke_msg_send(rsp);
}
#endif //(BLE_CLIENT_PRF || BLE_TIP_SERVER || BLE_AN_SERVER || BLE_PAS_SERVER)


#if ((BLE_SERVER_PRF || BLE_CLIENT_PRF))

uint8_t prf_pack_date_time(uint8_t *packed_date, const struct prf_date_time* date_time)
{
    co_write16p(packed_date, date_time->year);
    *(packed_date + 2) = date_time->month;
    *(packed_date + 3) = date_time->day;
    *(packed_date + 4) = date_time->hour;
    *(packed_date + 5) = date_time->min;
    *(packed_date + 6) = date_time->sec;

    return 7;
}
uint8_t prf_unpack_date_time(uint8_t *packed_date, struct prf_date_time* date_time)
{
    date_time->year = co_read16p(&(packed_date[0]));
    date_time->month = packed_date[2];
    date_time->day   = packed_date[3];
    date_time->hour  = packed_date[4];
    date_time->min   = packed_date[5];
    date_time->sec   = packed_date[6];

    return 7;
}


#endif /* ((BLE_SERVER_PRF || BLE_CLIENT_PRF)) */
#endif // (BLE_PROFILES)
/// @} PRF_UTILS

