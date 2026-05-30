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
* 文件名   :bass.c
* 功能描述:
* 版本:V 1.0.0
* 作者:
* 日期:
* ****************************************************************************/


/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"

#if (BLE_BATT_SERVER)
#include "bass.h"
#include "bass_task.h"
#include "prf_utils.h"
#include "prf.h"

#include "ke_mem.h"

/*
 * BAS ATTRIBUTES DEFINITION
 ****************************************************************************************
 */

/// Full BAS Database Description - Used to add attributes into the database
const struct attm_desc bas_att_db[BAS_IDX_NB] =
{
    // Battery Service Declaration
    [BAS_IDX_SVC] =   {ATT_DECL_PRIMARY_SERVICE,  PERM(RD, ENABLE), 0, 0},
    // Battery Level Characteristic Declaration
    [BAS_IDX_BATT_LVL_CHAR]        =   {ATT_DECL_CHARACTERISTIC,   PERM(RD, ENABLE), 0, 0},
    // Battery Level Characteristic Value
    [BAS_IDX_BATT_LVL_VAL]         =   {ATT_CHAR_BATTERY_LEVEL,    PERM(RD, ENABLE), PERM(RI, ENABLE), 0},
    // Battery Level Characteristic - Client Characteristic Configuration Descriptor
    [BAS_IDX_BATT_LVL_NTF_CFG]     =   {ATT_DESC_CLIENT_CHAR_CFG,  PERM(RD, ENABLE)|PERM(WRITE_REQ, ENABLE), 0, 0},
    // Battery Level Characteristic - Characteristic Presentation Format Descriptor
    [BAS_IDX_BATT_LVL_PRES_FMT]    =   {ATT_DESC_CHAR_PRES_FORMAT, PERM(RD, ENABLE), PERM(RI, ENABLE), 0},
};


/*
 * LOCAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Initialization of the BASS module.
 * This function performs all the initializations of the Profile module.
 *  - Creation of database (if it's a service)
 *  - Allocation of profile required memory
 *  - Initialization of task descriptor to register application
 *      - Task State array
 *      - Number of tasks
 *      - Default task handler
 *
 * @param[out]    env        Collector or Service allocated environment data.
 * @param[in|out] start_hdl  Service start handle (0 - dynamically allocated), only applies for services.
 * @param[in]     app_task   Application task number.
 * @param[in]     sec_lvl    Security level (AUTH, EKS and MI field of @see enum attm_value_perm_mask)
 * @param[in]     param      Configuration parameters of profile collector or service (32 bits aligned)
 *
 * @return status code to know if profile initialization succeed or not.
 ****************************************************************************************
 */
static uint8_t bass_init (struct prf_task_env* env, uint16_t* start_hdl, uint16_t app_task, uint8_t sec_lvl,  struct bass_db_cfg* params)
{

    uint16_t shdl[BASS_NB_BAS_INSTANCES_MAX];
    struct bass_env_tag* bass_env = NULL;
    // Status
    uint8_t status = GAP_ERR_NO_ERROR;
    // Counter
    uint8_t i;

    // Check number of BAS instances
    if ((params->bas_nb > 0) && (params->bas_nb <= BASS_NB_BAS_INSTANCES_MAX))
    {
            //-------------------- allocate memory required for the profile  ---------------------
            bass_env = (struct bass_env_tag* ) ke_malloc(sizeof(struct bass_env_tag), KE_MEM_ATT_DB);
            memset(bass_env, 0 , sizeof(struct bass_env_tag));
            // Save number of BAS
            bass_env->svc_nb = params->bas_nb;
            for (i = 0; ((i < params->bas_nb) && (status == GAP_ERR_NO_ERROR)); i++)
            {
                // Service content flag
                uint8_t cfg_flag = BAS_CFG_FLAG_MANDATORY_MASK;
                // Save database configuration
                bass_env->features |= (params->features[i]) << i;
                bass_env->batt_level_pres_format[i] = params->batt_level_pres_format[i];

                // Check if notifications are supported
                if (params->features[i] == BAS_BATT_LVL_NTF_SUP)
                {
                    cfg_flag |= BAS_CFG_FLAG_NTF_SUP_MASK;
                }

                // Check if multiple instances
                if (bass_env->svc_nb > 1)
                {
                    cfg_flag |= BAS_CFG_FLAG_MTP_BAS_MASK;
                }

                shdl[i] = *start_hdl;

                //Create BAS in the DB
                //------------------ create the attribute database for the profile -------------------
                status = attm_svc_create_db(&(shdl[i]), ATT_SVC_BATTERY_SERVICE, (uint8_t *)&cfg_flag,BAS_IDX_NB, NULL, env->task, bas_att_db,(sec_lvl & (PERM_MASK_SVC_DIS | PERM_MASK_SVC_AUTH | PERM_MASK_SVC_EKS)));
                //Set optional permissions
                if (status == GAP_ERR_NO_ERROR)
                {
                    // update start handle for next service - only useful if multiple service, else not used.
                    // 4 characteristics + optional notification characteristic.
                    *start_hdl = shdl[i] + BAS_IDX_NB - ((params->features[i] == BAS_BATT_LVL_NTF_SUP) ? 0 : 1);
                    //Set optional permissions
                    if (params->features[i] == BAS_BATT_LVL_NTF_SUP)
                    {
                        // Battery Level characteristic value permissions
                        uint16_t perm = PERM(RD, ENABLE) | PERM(NTF, ENABLE);
                        attm_att_set_permission(shdl[i] + BAS_IDX_BATT_LVL_VAL, perm, 0);
                    }
                }
                // Reset configuration flag
                cfg_flag = BAS_CFG_FLAG_MANDATORY_MASK;
            }
    }
    else
    {
            status = PRF_ERR_INVALID_PARAM;
    }

    //-------------------- Update profile task information  ---------------------
    if (status == ATT_ERR_NO_ERROR)
    {
            // allocate BASS required environment variable
            env->env = (prf_env_t*) bass_env;
            *start_hdl = shdl[0];
            bass_env->start_hdl = *start_hdl;
            bass_env->prf_env.app_task = app_task | (PERM_GET(sec_lvl, SVC_MI) ? PERM(PRF_MI, ENABLE) : PERM(PRF_MI, DISABLE));
            bass_env->prf_env.prf_task = env->task | PERM(PRF_MI, DISABLE);
            // initialize environment variable
            env->id                     = TASK_ID_BASS;
            env->desc.idx_max           = BASS_IDX_MAX;
            env->desc.state             = bass_env->state;
            env->desc.default_handler   = &bass_default_handler;
            // service is ready, go into an Idle state
            ke_state_set(env->task, BASS_IDLE);
    }
    else if (bass_env != NULL)
    {
            ke_free(bass_env);
    }
    return (status);
}
/**
 ****************************************************************************************
 * @brief Destruction of the BASS module - due to a reset for instance.
 * This function clean-up allocated memory (attribute database is destroyed by another
 * procedure)
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 ****************************************************************************************
 */
static void bass_destroy(struct prf_task_env* env)
{

    struct bass_env_tag* bass_env = (struct bass_env_tag*) env->env;
    // clear on-going operation
    if (bass_env->operation != NULL)
    {
        ke_free(bass_env->operation);
    }
    // free profile environment variables
    env->env = NULL;
    ke_free(bass_env);
}

/**
 ****************************************************************************************
 * @brief Handles Connection creation
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 * @param[in]        conidx     Connection index
 ****************************************************************************************
 */
static void bass_create(struct prf_task_env* env, uint8_t conidx)
{

    struct bass_env_tag* bass_env = (struct bass_env_tag*) env->env;
    ASSERT_ERR(conidx < BLE_CONNECTION_MAX);
    // force notification config to zero when peer device is connected
    bass_env->ntf_cfg[conidx] = 0;
}

/**
 ****************************************************************************************
 * @brief Handles Disconnection
 *
 * @param[in|out]    env        Collector or Service allocated environment data.
 * @param[in]        conidx     Connection index
 * @param[in]        reason     Detach reason
 ****************************************************************************************
 */
static void bass_cleanup(struct prf_task_env* env, uint8_t conidx, uint8_t reason)
{

    struct bass_env_tag* bass_env = (struct bass_env_tag*) env->env;
    ASSERT_ERR(conidx < BLE_CONNECTION_MAX);
    // force notification config to zero when peer device is disconnected
    bass_env->ntf_cfg[conidx] = 0;
}


/**
 ****************************************************************************************
 * @brief  Trigger battery level notification
 *
 * @param bass_env profile environment
 * @param conidx   peer destination connection index
 * @param svc_idx  Service index
 ****************************************************************************************
 */
static void bass_notify_batt_lvl(struct bass_env_tag* bass_env, uint8_t conidx, uint8_t svc_idx)
{

    // Allocate the GATT notification message
    struct gattc_send_evt_cmd *batt_lvl = KE_MSG_ALLOC_DYN(GATTC_SEND_EVT_CMD,KE_BUILD_ID(TASK_GATTC, conidx), prf_src_task_get(&(bass_env->prf_env),0),gattc_send_evt_cmd, sizeof(uint8_t));
    // Fill in the parameter structure
    batt_lvl->operation = GATTC_NOTIFY;
    batt_lvl->handle = bass_get_att_handle(svc_idx, BAS_IDX_BATT_LVL_VAL);
    // pack measured value in database
    batt_lvl->length = sizeof(uint8_t);
    batt_lvl->value[0] = bass_env->batt_lvl[svc_idx];
    // send notification to peer device
    ke_msg_send(batt_lvl);
}

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// BASS Task interface required by profile manager
const struct prf_task_cbs bass_itf = {
    (prf_init_fnct) bass_init,
    bass_destroy,
    bass_create,
    bass_cleanup,
};

/*
 * GLOBAL FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */

const struct prf_task_cbs* bass_prf_itf_get(void)
{
   return &bass_itf;
}

uint16_t bass_get_att_handle(uint8_t svc_idx, uint8_t att_idx)
{


    struct bass_env_tag* bass_env = PRF_ENV_GET(BASS, bass);
    uint16_t handle = ATT_INVALID_HDL;
    uint8_t i = 0;
    if (svc_idx < bass_env ->svc_nb)
    {
        handle = bass_env->start_hdl;
        for(i = 0 ; i < svc_idx ; i++)
        {
            // update start handle for next service - only useful if multiple service, else not used.
            // 4 characteristics + optional notification characteristic.
            handle +=  BAS_IDX_NB - ((((bass_env->features >> i) & 0x01) == BAS_BATT_LVL_NTF_SUP) ? 0 : 1);
        }
        // increment index according to expected index
        if (att_idx < BAS_IDX_BATT_LVL_NTF_CFG)
        {
            handle += att_idx;
        }
        // Battery notification
        else if ((att_idx == BAS_IDX_BATT_LVL_NTF_CFG) && (((bass_env->features >> i) & 0x01) == BAS_BATT_LVL_NTF_SUP))
        {
            handle += BAS_IDX_BATT_LVL_NTF_CFG;
        }
        // Battery Level format
        else if ((att_idx == BAS_IDX_BATT_LVL_PRES_FMT) && (bass_env->svc_nb > 1))
        {
            handle += BAS_IDX_BATT_LVL_PRES_FMT  - ((((bass_env->features >> i) & 0x01) == BAS_BATT_LVL_NTF_SUP) ? 0 : 1);
        }
        else
        {
            handle = ATT_INVALID_HDL;
        }
    }
    return handle;
}

uint8_t bass_get_att_idx(uint16_t handle, uint8_t *svc_idx, uint8_t *att_idx)
{


    struct bass_env_tag* bass_env = PRF_ENV_GET(BASS, bass);
    uint16_t hdl_cursor = bass_env->start_hdl;
    uint8_t status = PRF_APP_ERROR;

    // Browse list of services
    // handle must be greater than current index
    for(*svc_idx = 0 ; (*svc_idx < bass_env->svc_nb) && (handle >= hdl_cursor) ; (*svc_idx)++)
    {
        // check if it's a mandatory index
        if (handle <= (hdl_cursor + BAS_IDX_BATT_LVL_VAL))
        {
            *att_idx = handle -hdl_cursor;
            status = GAP_ERR_NO_ERROR;
            break;
        }
        hdl_cursor += BAS_IDX_BATT_LVL_VAL;

        // check if it's a notify index
        if (((bass_env->features >> *svc_idx) & 0x01) == BAS_BATT_LVL_NTF_SUP)
        {
            hdl_cursor++;
            if (handle == hdl_cursor)
            {
                *att_idx = BAS_IDX_BATT_LVL_NTF_CFG;
                status = GAP_ERR_NO_ERROR;
                break;
            }
        }
        // check if it's battery level format
        if (bass_env->svc_nb > 1)
        {
            hdl_cursor++;
            if (handle == hdl_cursor)
            {
                *att_idx = BAS_IDX_BATT_LVL_PRES_FMT;
                status = GAP_ERR_NO_ERROR;
                break;
            }
        }
        hdl_cursor++;
    }
    return (status);
}

void bass_exe_operation(void)
{


    struct bass_env_tag* bass_env = PRF_ENV_GET(BASS, bass);
    ASSERT_ERR(bass_env->operation != NULL);
    bool finished = true;
    uint8_t conidx = GAP_INVALID_CONIDX;

    // Restoring connection information requested
    if (bass_env->operation->id == BASS_ENABLE_REQ)
    {
            struct bass_enable_req * enable = (struct bass_enable_req *) ke_msg2param(bass_env->operation);
            conidx = enable->conidx;
            // loop on all services to check if notification should be triggered
            while (bass_env->cursor < BASS_NB_BAS_INSTANCES_MAX)
            {
                if (((bass_env->ntf_cfg[enable->conidx] & (1 << bass_env->cursor)) != 0) && (enable->old_batt_lvl[bass_env->cursor] != bass_env->batt_lvl[bass_env->cursor]))
                {
                    // trigger notification
                    bass_notify_batt_lvl(bass_env, enable->conidx, bass_env->cursor);
                    finished = false;
                    bass_env->cursor++;
                    break;
                }
                bass_env->cursor++;
            }
    }
    // Battery level updated
    else if (bass_env->operation->id == BASS_BATT_LEVEL_UPD_REQ)
    {
            struct bass_batt_level_upd_req * update = (struct bass_batt_level_upd_req *) ke_msg2param(bass_env->operation);
            // loop on all connection
            while (bass_env->cursor < BLE_CONNECTION_MAX)
            {
                if ((bass_env->ntf_cfg[bass_env->cursor] & (1 << update->bas_instance)) != 0)
                {
                    // trigger notification
                    bass_notify_batt_lvl(bass_env, bass_env->cursor, update->bas_instance);
                    finished = false;
                    bass_env->cursor++;
                    break;
                }
                bass_env->cursor++;
            }
    }
    else
    {
            ASSERT_ERR(0);
    }

    // check if operation is finished
    if (finished)
    {
            // trigger response message
            if (bass_env->operation->id == BASS_ENABLE_REQ)
            {
                struct bass_enable_rsp * rsp = KE_MSG_ALLOC(BASS_ENABLE_RSP, bass_env->operation->src_id,bass_env->operation->dest_id, bass_enable_rsp);
                rsp->conidx = conidx;
                rsp->status = GAP_ERR_NO_ERROR;
                ke_msg_send(rsp);
            }
            else if (bass_env->operation->id == BASS_BATT_LEVEL_UPD_REQ)
            {
                struct bass_batt_level_upd_rsp * rsp = KE_MSG_ALLOC(BASS_BATT_LEVEL_UPD_RSP, bass_env->operation->src_id,bass_env->operation->dest_id, bass_batt_level_upd_rsp);
                rsp->status = GAP_ERR_NO_ERROR;
                ke_msg_send(rsp);
            }
            // free operation
            ke_free(bass_env->operation);
            bass_env->operation = NULL;
            // go back to idle state
            ke_state_set(prf_src_task_get(&(bass_env->prf_env), 0), BASS_IDLE);
    }
}


#endif // (BLE_BATT_SERVER)

/// @} BASS


