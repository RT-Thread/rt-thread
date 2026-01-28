/**
 ****************************************************************************************
 *
 * @file user.c
 *
 * @brief user defined.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup USER
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"
#include "app.h"

#if (BLE_APP_USER)
#include "attm.h"
#include "user.h"
#include "user_task.h"
#include "co_utils.h"
#include "co_endian.h"
#include "prf_utils.h"

#include "ke_mem.h"
//#include "interface.h"
#include "ble_arch.h"

#ifdef N32WB452_BT_API
#include "n32wb452_ble_api.h"

extern bt_attr_param * g_bt_init;
#endif
//#include "att.h"
/*
 * HTPT PROFILE ATTRIBUTES
 *****************************************************************************************/


/// Full HTS Database Description - Used to add attributes into the database

const struct attm_desc user_att_db[USER_IDX_NB] =
{
    // FF00 Service Declaration
    [USER_IDX_SVC]                   =   {ATT_DECL_PRIMARY_SERVICE, PERM(RD, ENABLE), 0, 0},

    // FF01 Characteristic Declaration
    [USER_IDX_WRITE_NOTIFY_CHAR]       =   {ATT_DECL_CHARACTERISTIC, PERM(RD, ENABLE) | PERM(WRITE_REQ, ENABLE), 0, 0},
    //  Characteristic Value

#ifndef BLE_OTA_WRITE_CHAR_EN

    //  Characteristic Value
    [USER_IDX_WRITE_NOTIFY_VAL]         =   {ATT_CHAR_WRITE_NOTIFY, PERM(WRITE_COMMAND, ENABLE)|PERM(NTF, ENABLE), PERM(RI, ENABLE), 0x300},
      //Client Characteristic Configuration Descriptor
    [USER_IDX_WRITE_NOTIFY_CFG]       =   {ATT_DESC_CLIENT_CHAR_CFG, PERM(RD, ENABLE) | PERM(WRITE_REQ, ENABLE), 0/*PERM(RI, ENABLE)*/, 0x200},
#endif
#ifdef BLE_OTA_WRITE_CHAR_EN
    //  Characteristic Value
    [USER_IDX_WRITE_NOTIFY_VAL] = {ATT_CHAR_WRITE_NOTIFY,
                                   PERM(WRITE_REQ, ENABLE) | PERM(WRITE_COMMAND, ENABLE) /*|PERM(NTF, ENABLE)*/,
                                   0 /*PERM(RI, ENABLE)*/,
                                   0x300},
    // Client Characteristic Configuration Descriptor
    [USER_IDX_WRITE_NOTIFY_CFG] = {ATT_DESC_CLIENT_CHAR_CFG,
                                   PERM(RD, ENABLE) | PERM(WRITE_REQ, ENABLE),
                                   0 /*PERM(RI, ENABLE)*/,
                                   0x200},

    //  Characteristic Declaration
    [USER_IDX_READ_NOTIFY_CHAR]        =   {ATT_DECL_CHARACTERISTIC, PERM(RD, ENABLE), 0, 0},
    // Characteristic Value
    [USER_IDX_READ_NOTIFY_VAL] = {ATT_CHAR_READ_NOTIFY,
                                  /*PERM(RD, ENABLE) |*/ PERM(NTF, ENABLE),
                                  (/*PERM(RI, ENABLE)|*/ PERM(NTF, ENABLE)),
                                  0x200},
    //[USER_IDX_READ_NOTIFY_VAL]         =   {ATT_CHAR_READ_NOTIFY, PERM(RD, ENABLE) |PERM(NTF, ENABLE), (PERM(RI, ENABLE)|PERM(NTF, ENABLE)), 0x200},
    //Client Characteristic Configuration Descriptor
    [USER_IDX_WRITE_NOTIFY2_CFG]       =   {ATT_DESC_CLIENT_CHAR_CFG, PERM(RD, ENABLE) | /* PERM(WP,ENABLE)|*/PERM(WRITE_REQ, ENABLE), 0/*PERM(RI, ENABLE)*/, 0x200},
#endif
};

#ifdef N32WB452_BT_API
uint16_t get_user_character_perm(uint16_t perm)
{
    uint16_t ret = 0;

//    ble_log(BLE_DEBUG,"PERM(WRITE_COMMAND, ENABLE) = %0x.\r\n", PERM(WRITE_COMMAND, ENABLE));
//    ble_log(BLE_DEBUG,"PERM(NTF, ENABLE) = %0x.\r\n", PERM(NTF, ENABLE));

    if (perm & BT_RD_PERM) {
        ret |= PERM(RD, ENABLE);
    }

    if (perm & BT_WRITE_PERM) {
        ret |= PERM(WRITE_COMMAND, ENABLE);
//        ble_log(BLE_DEBUG,"ret1 = %x.\r\n", ret);
    }

    if (perm & BT_WRITE_REQ_PERM) {
        ret |= PERM(WRITE_REQ, ENABLE);
    }

    if (perm & BT_NTF_PERM) {
        ret |= PERM(NTF, ENABLE);
//        ble_log(BLE_DEBUG,"ret2 = %x.\r\n", ret);
    }

    return ret;
}
#endif

/*
 * LOCAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */
static uint8_t user_init(struct prf_task_env *env, uint16_t *start_hdl, uint16_t app_task,uint8_t sec_lvl, struct user_db_cfg *params)
{
#ifdef N32WB452_BT_API
    //uint16_t perm;
    volatile struct attm_desc user_att_db_api_define[USER_IDX_NB] = {0};
#endif

    // Service content flag
    uint16_t cfg_flag = (1<<USER_IDX_NB) - 1;
    // DB Creation Status
    uint8_t status = ATT_ERR_NO_ERROR;
    cfg_flag = co_btohs(cfg_flag);

#ifdef N32WB452_BT_API0
    if (g_bt_init) {
        //设置其他默认服务
        memcpy((void*)user_att_db_api_define, (void*)user_att_db, sizeof(user_att_db_api_define));

        //配置用户定义服务和character
        if (g_bt_init->service[0].character[0].uuid \
            && (g_bt_init->service[0].character[0].permission & BT_WRITE_PERM)
            && (g_bt_init->service[0].character[0].permission & BT_NTF_PERM)) {
            user_att_db_api_define[USER_IDX_WRITE_NOTIFY_VAL].uuid = ATT_UUID_16(g_bt_init->service[0].character[0].uuid);
            user_att_db_api_define[USER_IDX_WRITE_NOTIFY_VAL].perm = get_user_character_perm(g_bt_init->service[0].character[0].permission);
            user_att_db_api_define[USER_IDX_WRITE_NOTIFY_VAL].ext_perm = 0;
            user_att_db_api_define[USER_IDX_WRITE_NOTIFY_VAL].max_size = 0x300;
        }

        user_att_db_api_define[USER_IDX_WRITE_NOTIFY_VAL].uuid = ATT_UUID_16(g_bt_init->service[0].character[0].uuid);

        status = attm_svc_create_db(start_hdl, (uint16_t)g_bt_init->service[0].svc_uuid, (uint8_t *)&cfg_flag,USER_IDX_NB, NULL, env->task, &user_att_db_api_define[0],(sec_lvl & (PERM_MASK_SVC_DIS | PERM_MASK_SVC_AUTH | PERM_MASK_SVC_EKS)) | PERM(SVC_MI, DISABLE));
    } else {
        status = attm_svc_create_db(start_hdl, (uint16_t)ATT_SVC_UKEY_SERVICE, (uint8_t *)&cfg_flag,USER_IDX_NB, NULL, env->task, &user_att_db[0],(sec_lvl & (PERM_MASK_SVC_DIS | PERM_MASK_SVC_AUTH | PERM_MASK_SVC_EKS)) | PERM(SVC_MI, DISABLE));
    }
#else
        status = attm_svc_create_db(start_hdl, (uint16_t)ATT_SVC_UKEY_SERVICE, (uint8_t *)&cfg_flag,USER_IDX_NB, NULL, env->task, &user_att_db[0],(sec_lvl & (PERM_MASK_SVC_DIS | PERM_MASK_SVC_AUTH | PERM_MASK_SVC_EKS)) | PERM(SVC_MI, DISABLE));
#endif
    if (status == ATT_ERR_NO_ERROR)
    {
        //-------------------- allocate memory required for the profile  ---------------------
        struct user_env_tag *user_env =
            (struct user_env_tag *) ke_malloc(sizeof(struct user_env_tag), KE_MEM_ATT_DB);

        // allocate PROXR required environment variable
        env->env = (prf_env_t *) user_env;

        user_env->shdl     = *start_hdl;
        user_env->prf_env.app_task = app_task | (PERM_GET(sec_lvl, SVC_MI) ? PERM(PRF_MI, ENABLE) : PERM(PRF_MI, DISABLE));
        user_env->prf_env.prf_task = env->task | PERM(PRF_MI, DISABLE);

        // initialize environment variable
        env->id                     = TASK_ID_USER;
        env->desc.idx_max           = 1;
        env->desc.state             = user_env->state;
        env->desc.default_handler   = &user_default_handler;

        //Save features on the environment
        user_env->features      = params->features;
        user_env->operation     = NULL;
        memset(user_env->ntf_ind_cfg, 0 , sizeof(user_env->ntf_ind_cfg));

        // service is ready, go into an Idle state
        ke_state_set(env->task, USER_IDLE);
    }
    return (status);
}


static void user_destroy(struct prf_task_env *env)
{
    struct user_env_tag *user_env = (struct user_env_tag *) env->env;

    // free profile environment variables
    if (user_env->operation != NULL)
    {
        ke_free(user_env->operation);
    }


    env->env = NULL;
    ke_free(user_env);
}

static void user_create(struct prf_task_env *env, uint8_t conidx)
{
    /* Clear configuration for this connection */
    struct user_env_tag *user_env = (struct user_env_tag *) env->env;
    //user_env->ntf_ind_cfg[conidx] = 0x03;
    user_env->ntf_ind_cfg[USER_IDX_WRITE_NOTIFY_CFG] = USER_DATA_NTF;
#ifdef BLE_OTA_WRITE_CHAR_EN
    user_env->ntf_ind_cfg[USER_IDX_WRITE_NOTIFY2_CFG] = USER_DATA_NTF;
#endif
}

static void user_cleanup(struct prf_task_env *env, uint8_t conidx, uint8_t reason)
{
    /* Clear configuration for this connection */
    struct user_env_tag *user_env = (struct user_env_tag *) env->env;
    user_env->ntf_ind_cfg[USER_IDX_WRITE_NOTIFY_CFG] = USER_DATA_NTF_IND_DISABLE;
#ifdef BLE_OTA_WRITE_CHAR_EN
    user_env->ntf_ind_cfg[USER_IDX_WRITE_NOTIFY2_CFG] = USER_DATA_NTF_IND_DISABLE;
#endif

}


/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// HTPT Task interface required by profile manager
const struct prf_task_cbs user_itf =
{
    (prf_init_fnct) user_init,
    user_destroy,
    user_create,
    user_cleanup,
};




const struct prf_task_cbs *user_prf_itf_get(void)
{
    return &user_itf;
}


uint16_t user_att_hdl_get(struct user_env_tag *user_env, uint8_t att_idx)
{
    uint16_t handle = user_env->shdl;

    handle += att_idx;

    return handle;
}

uint8_t user_att_idx_get(struct user_env_tag *user_env, uint16_t handle)
{
    uint16_t handle_ref = user_env->shdl;
    uint8_t att_idx = ATT_INVALID_IDX;

    if (handle >handle_ref)
    {
         att_idx = handle - handle_ref;
    }

    return att_idx;
}

void user_exe_operation(void)
{
    struct user_env_tag *user_env = PRF_ENV_GET(USER, user);

    ASSERT_ERR(user_env->operation != NULL);

    bool finished = true;

    while (user_env->operation->cursor < BLE_CONNECTION_MAX)
    {
        // check if this type of event is enabled
        if (( (  /*user_env->ntf_ind_cfg[user_env->operation->cursor] & */ user_env->operation->op) != 0) /*&& (user_env->operation->conidx != user_env->operation->cursor)*/)
        {
            // trigger the event
            struct gattc_send_evt_cmd *evt = KE_MSG_ALLOC_DYN(GATTC_SEND_EVT_CMD,KE_BUILD_ID(TASK_GATTC , user_env->operation->cursor), prf_src_task_get(&user_env->prf_env, 0),gattc_send_evt_cmd, user_env->operation->length);
            evt->operation = (user_env->operation->op != USER_DATA_NTF) ? GATTC_INDICATE : GATTC_NOTIFY;
            evt->length    = user_env->operation->length;
            evt->handle    = user_env->operation->handle;
            memcpy(evt->value, user_env->operation->data, evt->length);
            ke_msg_send(evt);

            finished = false;
            user_env->operation->cursor++;
            break;
        }
        user_env->operation->cursor++;
    }

    // check if operation is finished
    if (finished)
    {

        // do not send response if operation has been locally requested
        if (user_env->operation->dest_id != prf_src_task_get(&user_env->prf_env, 0))
        {

            // send response to requester
            struct user_upd_rsp *rsp = KE_MSG_ALLOC(((user_env->operation->op == USER_DATA_NTF) ? USER_NOTIFY_RSP : USER_INTV_RSP),user_env->operation->dest_id, prf_src_task_get(&user_env->prf_env, 0),user_upd_rsp);
            rsp->status = GAP_ERR_NO_ERROR;
            ke_msg_send(rsp);
        }

        // free operation
        ke_free(user_env->operation);
        user_env->operation = NULL;
        // go back to idle state
        ke_state_set(prf_src_task_get(&(user_env->prf_env), 0), USER_IDLE);
    }
}



uint8_t user_update_ntf_ind_cfg(uint8_t conidx, uint8_t cfg, uint16_t valid_val, uint8_t idx, uint16_t value)
{
    struct user_env_tag *user_env = PRF_ENV_GET(USER, user);
    uint8_t status = GAP_ERR_NO_ERROR;

    if ((value != valid_val) && (value != PRF_CLI_STOP_NTFIND))
    {
        status = PRF_APP_ERROR;
    }

    user_env->ntf_ind_cfg[idx] = value;
//    else if (value == valid_val)
//    {
//        user_env->ntf_ind_cfg[idx]|= cfg;
//    }
//    else
//    {
//        user_env->ntf_ind_cfg[idx] &= ~cfg;
//    }

    if (status == GAP_ERR_NO_ERROR)
    {
        // no msg handler   blank  by ding.yuanwwu
        // inform application that notification/indication configuration has changed
//        struct user_cfg_indntf_ind *ind = KE_MSG_ALLOC(USER_CFG_INDNTF_IND, prf_dst_task_get(&user_env->prf_env, conidx), prf_src_task_get(&user_env->prf_env, conidx),user_cfg_indntf_ind);
//        ind->conidx      = conidx;
//        ind->ntf_ind_cfg = user_env->ntf_ind_cfg[conidx];
//        ke_msg_send(ind);
    }

    return (status);
}

#endif //BLE_HT_THERMOM

