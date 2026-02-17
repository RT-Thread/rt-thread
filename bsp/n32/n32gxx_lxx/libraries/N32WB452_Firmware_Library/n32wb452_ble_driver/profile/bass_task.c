/*****************************************************************************
*         Nations Microcontroller Software Support
* ----------------------------------------------------------------------------
* Copyright (c) 2017, Nations Corporation
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* - Redistributions of source code must retain the above copyright notice,
* this list of conditions and the disclaimer below.
*
* Nations's name may not be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
* DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* ****************************************************************************/
/*****************************************************************************
* 文件名   :bass_task.c
* 功能描述:
* 版本:V 1.0.0
* 作者:
* 日期:
* ****************************************************************************/

/**
 ****************************************************************************************
 * @addtogroup BASSTASK
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"

#if (BLE_BATT_SERVER)

#include "gap.h"
#include "gattc_task.h"

#include "bass.h"
#include "bass_task.h"

#include "prf_utils.h"

#include "co_utils.h"

/*
 * GLOBAL FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */


/**
 ****************************************************************************************
 * @brief Handles reception of the @ref BAPS_ENABLE_REQ message.
 * The handler enables the Battery 'Profile' Server Role.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int bass_enable_req_handler(ke_msg_id_t const msgid,struct bass_enable_req const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{

    int msg_status = KE_MSG_SAVED;
    uint8_t state = ke_state_get(dest_id);
    uint8_t conidx = KE_IDX_GET(src_id);
    // check state of the task
    if (state == BASS_IDLE)
    {
        struct bass_env_tag* bass_env = PRF_ENV_GET(BASS, bass);
        // Check provided values
        if ((param->conidx > BLE_CONNECTION_MAX) || (gapc_get_conhdl(param->conidx) == GAP_INVALID_CONHDL))
        {
            // an error occurs, trigg it.
            struct bass_enable_rsp* rsp = KE_MSG_ALLOC(BASS_ENABLE_RSP, src_id,dest_id, bass_enable_rsp);
            rsp->conidx = param->conidx;
            rsp->status = (param->conidx > BLE_CONNECTION_MAX) ? GAP_ERR_INVALID_PARAM : PRF_ERR_REQ_DISALLOWED;
            ke_msg_send(rsp);
            msg_status = KE_MSG_CONSUMED;
        }
        else
        {
            // put task in a busy state
            msg_status = KE_MSG_NO_FREE;
            ke_state_set(dest_id, BASS_BUSY);
            bass_env->batt_lvl[conidx] = param->old_batt_lvl[conidx];
            bass_env->ntf_cfg[param->conidx] = param->ntf_cfg;
            bass_env->operation = ke_param2msg(param);
            bass_env->cursor = 0;
            // trigger notification
            bass_exe_operation();
        }
    }
    return msg_status;
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref BAPS_BATT_LEVEL_SEND_REQ message.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int bass_batt_level_upd_req_handler(ke_msg_id_t const msgid,struct bass_batt_level_upd_req const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{


    int msg_status = KE_MSG_SAVED;
    uint8_t state = ke_state_get(dest_id);
    // check state of the task
    if (state == BASS_IDLE)
    {
        struct bass_env_tag* bass_env = PRF_ENV_GET(BASS, bass);
        // Check provided values
        if ((param->bas_instance < bass_env->svc_nb) && (param->batt_level <= BAS_BATTERY_LVL_MAX))
        {
            // update the battery level value
            bass_env->batt_lvl[param->bas_instance] = param->batt_level;
            // put task in a busy state
            msg_status = KE_MSG_NO_FREE;
            ke_state_set(dest_id, BASS_BUSY);
            bass_env->operation = ke_param2msg(param);
            bass_env->cursor = 0;
            // trigger notification
            bass_exe_operation();
        }
        else
        {
            // an error occurs, trigg it.
            struct bass_batt_level_upd_rsp * rsp = KE_MSG_ALLOC(BASS_BATT_LEVEL_UPD_RSP, src_id,dest_id, bass_batt_level_upd_rsp);
            rsp->status = PRF_ERR_INVALID_PARAM;
            ke_msg_send(rsp);
            msg_status = KE_MSG_CONSUMED;
        }
    }
    return (msg_status);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the attribute info request message.
 *
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gattc_att_info_req_ind_handler(ke_msg_id_t const msgid,struct gattc_att_info_req_ind *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{

    struct gattc_att_info_cfm * cfm;
    uint8_t svc_idx = 0, att_idx = 0;
    // retrieve handle information
    uint8_t status = bass_get_att_idx(param->handle, &svc_idx, &att_idx);
    //Send write response
    cfm = KE_MSG_ALLOC(GATTC_ATT_INFO_CFM, src_id, dest_id, gattc_att_info_cfm);
    cfm->handle = param->handle;
    if (status == GAP_ERR_NO_ERROR)
    {
        // check if it's a client configuration char
        if (att_idx == BAS_IDX_BATT_LVL_NTF_CFG)
        {
            // CCC attribute length = 2
            cfm->length = 2;
        }
        // not expected request
        else
        {
            cfm->length = 0;
            status = ATT_ERR_WRITE_NOT_PERMITTED;
        }
    }
    cfm->status = status;
    ke_msg_send(cfm);
    return (KE_MSG_CONSUMED);
}


/**
 ****************************************************************************************
 * @brief Handles reception of the @ref GATTC_WRITE_REQ_IND message.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gattc_write_req_ind_handler(ke_msg_id_t const msgid, struct gattc_write_req_ind const *param,ke_task_id_t const dest_id, ke_task_id_t const src_id)
{

    struct gattc_write_cfm * cfm;
    uint8_t svc_idx = 0, att_idx = 0;
    uint8_t conidx = KE_IDX_GET(src_id);
    // retrieve handle information
    uint8_t status = bass_get_att_idx(param->handle, &svc_idx, &att_idx);
    // If the attribute has been found, status is GAP_ERR_NO_ERROR
    if (status == GAP_ERR_NO_ERROR)
    {
        struct bass_env_tag* bass_env = PRF_ENV_GET(BASS, bass);
        // Extract value before check
        uint16_t ntf_cfg = co_read16p(&param->value[0]);
        // Only update configuration if value for stop or notification enable
        if ((att_idx == BAS_IDX_BATT_LVL_NTF_CFG)&& ((ntf_cfg == PRF_CLI_STOP_NTFIND) || (ntf_cfg == PRF_CLI_START_NTF)))
        {
            // Conserve information in environment
            if (ntf_cfg == PRF_CLI_START_NTF)
            {
                // Ntf cfg bit set to 1
                bass_env->ntf_cfg[conidx] |= (BAS_BATT_LVL_NTF_SUP << svc_idx);
            }
            else
            {
                // Ntf cfg bit set to 0
                bass_env->ntf_cfg[conidx] &= ~(BAS_BATT_LVL_NTF_SUP << svc_idx);
            }

            // Inform APP of configuration change
            struct bass_batt_level_ntf_cfg_ind * ind = KE_MSG_ALLOC(BASS_BATT_LEVEL_NTF_CFG_IND,prf_dst_task_get(&(bass_env->prf_env), conidx), dest_id,bass_batt_level_ntf_cfg_ind);
            ind->conidx = conidx;
            ind->ntf_cfg = bass_env->ntf_cfg[conidx];
            ke_msg_send(ind);
        }
        else
        {
            status = PRF_APP_ERROR;
        }
    }
    //Send write response
    cfm = KE_MSG_ALLOC(GATTC_WRITE_CFM, src_id, dest_id, gattc_write_cfm);
    cfm->handle = param->handle;
    cfm->status = status;
    ke_msg_send(cfm);
    return (KE_MSG_CONSUMED);
}


/**
 ****************************************************************************************
 * @brief Handles reception of the @ref GATTC_READ_REQ_IND message.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gattc_read_req_ind_handler(ke_msg_id_t const msgid, struct gattc_read_req_ind const *param,ke_task_id_t const dest_id, ke_task_id_t const src_id)
{

    struct gattc_read_cfm * cfm;
    uint8_t svc_idx = 0, att_idx = 0;
    uint8_t conidx = KE_IDX_GET(src_id);
    // retrieve handle information
    uint8_t status = bass_get_att_idx(param->handle, &svc_idx, &att_idx);
    uint16_t length = 0;
    struct bass_env_tag* bass_env = PRF_ENV_GET(BASS, bass);
    // If the attribute has been found, status is GAP_ERR_NO_ERROR
    if (status == GAP_ERR_NO_ERROR)
    {
            // read notification information
            if (att_idx == BAS_IDX_BATT_LVL_VAL)
            {
                length = sizeof(uint8_t);
            }
            // read notification information
            else if (att_idx == BAS_IDX_BATT_LVL_NTF_CFG)
            {
                length = sizeof(uint16_t);
            }
            else if (att_idx == BAS_IDX_BATT_LVL_PRES_FMT)
            {
                length = PRF_CHAR_PRES_FMT_SIZE;
            }
            else
            {
                status = PRF_APP_ERROR;
            }
    }
    //Send write response
    cfm = KE_MSG_ALLOC_DYN(GATTC_READ_CFM, src_id, dest_id, gattc_read_cfm, length);
    cfm->handle = param->handle;
    cfm->status = status;
    cfm->length = length;

    if (status == GAP_ERR_NO_ERROR)
    {
            // read notification information
            if (att_idx == BAS_IDX_BATT_LVL_VAL)
            {
                cfm->value[conidx] = bass_env->batt_lvl[svc_idx];  //read batt_lvel
            }
            // retrieve notification config
            else if (att_idx == BAS_IDX_BATT_LVL_NTF_CFG)
            {
                uint16_t ntf_cfg = (bass_env->ntf_cfg[conidx] >> svc_idx & BAS_BATT_LVL_NTF_SUP) ? PRF_CLI_START_NTF : PRF_CLI_STOP_NTFIND;
                co_write16p(cfm->value, ntf_cfg);
            }
            // retrieve battery level format
            else if (att_idx == BAS_IDX_BATT_LVL_PRES_FMT)
            {
                prf_pack_char_pres_fmt(cfm->value, &(bass_env->batt_level_pres_format[svc_idx]));
            }
            else
            {
                    /* Not Possible */
            }
    }
    ke_msg_send(cfm);
    return (KE_MSG_CONSUMED);
}
/**
 ****************************************************************************************
 * @brief Handles @ref GATTC_CMP_EVT for GATTC_NOTIFY message meaning that Measurement
 * notification has been correctly sent to peer device (but not confirmed by peer device).
 * *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gattc_cmp_evt_handler(ke_msg_id_t const msgid,  struct gattc_cmp_evt const *param,ke_task_id_t const dest_id, ke_task_id_t const src_id)
{

    if (param->operation == GATTC_NOTIFY)
    {
        // continue operation execution
        bass_exe_operation();
    }
    return (KE_MSG_CONSUMED);
}

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Default State handlers definition
const struct ke_msg_handler bass_default_state[] =
{
    {BASS_ENABLE_REQ,               (ke_msg_func_t) bass_enable_req_handler},
    {BASS_BATT_LEVEL_UPD_REQ,       (ke_msg_func_t) bass_batt_level_upd_req_handler},
    {GATTC_ATT_INFO_REQ_IND,        (ke_msg_func_t) gattc_att_info_req_ind_handler},
    {GATTC_WRITE_REQ_IND,           (ke_msg_func_t) gattc_write_req_ind_handler},
    {GATTC_READ_REQ_IND,            (ke_msg_func_t) gattc_read_req_ind_handler},
    {GATTC_CMP_EVT,                 (ke_msg_func_t) gattc_cmp_evt_handler},
};

/// Specifies the message handlers that are common to all states.
const struct ke_state_handler bass_default_handler = KE_STATE_HANDLER(bass_default_state);

#endif     /* #if (BLE_BATT_SERVER) */

/// @} BASSTASK
