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
* 文件名   :app_batt.c
* 功能描述:
* 版本:V 1.0.0
* 作者:
* 日期:
* ****************************************************************************/


#include "rwip_config.h"     // SW configuration

#if (BLE_APP_BATT)

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "app_batt.h"                // Battery Application Module Definitions
#include "app.h"                     // Application Definitions
#include "app_task.h"                // application task definitions
#include "bass_task.h"               // health thermometer functions
#include "co_bt.h"
#include "prf_types.h"               // Profile common types definition
#include "ble_arch.h"                    // Platform Definitions
#include "prf.h"
#include "bass.h"
#include "string.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Battery Application Module Environment Structure
struct app_batt_env_tag app_batt_env;

/*
 * GLOBAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */

void app_batt_init(void)
{
    // Reset the environment
    memset(&app_batt_env, 0, sizeof(struct app_batt_env_tag));
    // Initial battery level: 100
    app_batt_env.batt_lvl = app_env.batt_lvl;   // set battery init level;
}

void app_batt_add_bas(void)
{
    struct bass_db_cfg* db_cfg;
    // Allocate the BASS_CREATE_DB_REQ
    struct gapm_profile_task_add_cmd *req = KE_MSG_ALLOC_DYN(GAPM_PROFILE_TASK_ADD_CMD,TASK_GAPM, TASK_APP,gapm_profile_task_add_cmd, sizeof(struct bass_db_cfg));
    // Fill message
    req->operation   = GAPM_PROFILE_TASK_ADD;
    req->sec_lvl     = PERM(SVC_AUTH, DISABLE);  //设置权限
    req->prf_task_id = TASK_ID_BASS;
    req->app_task    = TASK_APP;
    req->start_hdl   = 0;
    // Set parameters
    db_cfg = (struct bass_db_cfg* ) req->param;
    // Add a BAS instance
    db_cfg->bas_nb      = 1;
    // Sending of notifications is supported
    db_cfg->features[0] = BAS_BATT_LVL_NTF_SUP;
    // Send the message
    ke_msg_send(req);
}



void app_batt_enable_prf(uint8_t conidx)
{
    app_batt_env.conidx = conidx;
    // Allocate the message
    struct bass_enable_req * req = KE_MSG_ALLOC(BASS_ENABLE_REQ,prf_get_task_from_id(TASK_ID_BASS),TASK_APP,bass_enable_req);
    // Fill in the parameter structure
    req->conidx = conidx;
    // NTF initial status - Disabled
    req->ntf_cfg = PRF_CLI_STOP_NTFIND;
    req->old_batt_lvl[0]   =  app_batt_env.batt_lvl;  //  init battery level
    // Send the message
    ke_msg_send(req);
}


// notify battery level
void app_batt_send_lvl(uint8_t batt_lvl)
{
    ASSERT_ERR(batt_lvl <= BAS_BATTERY_LVL_MAX);
    // Allocate the message
    struct bass_batt_level_upd_req * req = KE_MSG_ALLOC(BASS_BATT_LEVEL_UPD_REQ, prf_get_task_from_id(TASK_ID_BASS),TASK_APP,bass_batt_level_upd_req);
    // Fill in the parameter structure
    req->bas_instance = 0;
    req->batt_level   = batt_lvl;
    app_batt_env.batt_lvl = batt_lvl;
    // Send the message
    ke_msg_send(req);
}

static int bass_batt_level_ntf_cfg_ind_handler(ke_msg_id_t const msgid,struct bass_batt_level_ntf_cfg_ind const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    return (KE_MSG_CONSUMED);
}

static int batt_level_upd_handler(ke_msg_id_t const msgid,struct bass_batt_level_upd_rsp const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    return (KE_MSG_CONSUMED);
}


/**
 ****************************************************************************************
 * @brief
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int app_batt_msg_dflt_handler(ke_msg_id_t const msgid,void const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    return (KE_MSG_CONSUMED);
}

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Default State handlers definition
const struct ke_msg_handler app_batt_msg_handler_list[] =
{
    // Note: first message is latest message checked by kernel so default is put on top.
    {KE_MSG_DEFAULT_HANDLER,        (ke_msg_func_t)app_batt_msg_dflt_handler},
    {BASS_BATT_LEVEL_NTF_CFG_IND,   (ke_msg_func_t)bass_batt_level_ntf_cfg_ind_handler},
    {BASS_BATT_LEVEL_UPD_RSP,       (ke_msg_func_t)batt_level_upd_handler},
};

const struct ke_state_handler app_batt_table_handler =  {&app_batt_msg_handler_list[0], (sizeof(app_batt_msg_handler_list)/sizeof(struct ke_msg_handler))};

#endif //BLE_APP_BATT

