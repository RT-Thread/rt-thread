/**
****************************************************************************************
*
* @file app_user.c
*
* @brief Health Thermometer Application entry point
*
* Copyright (C) RivieraWaves 2009-2015
*
*
****************************************************************************************
*/

/**
 ****************************************************************************************
 * @addtogroup APP
 * @{
 ****************************************************************************************
 */

#include "rwip_config.h"     // SW configuration
#include "n32wb452_ble_api.h"
#if (BLE_APP_USER)

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "app_user.h"                  // Health Thermometer Application Definitions
#include "app.h"                     // Application Definitions
#include "app_task.h"                // application task definitions

#include "co_bt.h"
#include "prf_types.h"
#include "prf_utils.h"
#include "ble_arch.h"                    // Platform Definitions
#include "gapm_task.h"

#include "co_math.h"
#include "ke_timer.h"
#include "prf.h"
#include "user_task.h"
#include "user.h"
#include "co_utils.h"
#include "gattc.h"
#include "gapm.h"
//#include "interface.h"

#include "co_math.h"


#if (DISPLAY_SUPPORT)
#include "app_display.h"
#include "display.h"
#endif //DISPLAY_SUPPORT
//#include "Bkey_user.h"

#define DEMO_APP



//uint8_t whitelistsize = 0;

//INT8 rssivalue = 0;
/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
struct app_user_rev_tag app_user_env;
/*
 * LOCAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */
uint32_t need_rsp_type = 0;
void app_user_init(void)
{
    memset(&app_user_env, 0, sizeof(app_user_env));
    ke_timer_set(GAPM_DEVICE_READY_IND, TASK_APP, 10); //10M后复位
}



void add_users(uint16_t prf_task_id)
{
    struct user_db_cfg *db_cfg;

    struct gapm_profile_task_add_cmd *req = KE_MSG_ALLOC_DYN(GAPM_PROFILE_TASK_ADD_CMD,TASK_GAPM, TASK_APP,gapm_profile_task_add_cmd, sizeof(struct user_db_cfg));
    // Fill message
    req->operation = GAPM_PROFILE_TASK_ADD;
    req->sec_lvl =  PERM(SVC_AUTH, DISABLE);
    req->prf_task_id = prf_task_id;
    req->app_task = TASK_APP;
    req->start_hdl = 0;

    // Set parameters
    db_cfg = (struct user_db_cfg *) req->param;
    //
    db_cfg->features = (USER_READ_WRITE_CHAR_SUP | USER_DATA_NOTIFY_CHAR_SUP | USER_DATA_WRITE_CHAR_SUP);
    db_cfg->txlen = USER_DATA_LEN_MAX;
    db_cfg->rxlen = USER_DATA_LEN_MAX;

    // Send the message
    ke_msg_send(req);
}

void app_user_add_users(void)
{
    add_users(TASK_ID_USER);
}

static uint8_t data_notify_onePackage(uint16_t param_length , uint8_t *param_payload, uint16_t task_id, uint8_t att_idx)
{
    struct user_notify_req *req = KE_MSG_ALLOC_DYN(USER_NOTIFY_REQ,
                                  prf_get_task_from_id(task_id),
                                  TASK_APP,
                                  user_notify_req, param_length);
    req->send_param_length = param_length;
    req->att_idx = att_idx;
    memcpy(req->send_param_payload, param_payload, param_length);
    ke_msg_send(req);
    for(int i=0; i<8; i++)
    {
        BT_handle();
    }
    return 0;
}
uint8_t data_notify(uint16_t param_length , uint8_t *param_payload, uint16_t task_id, uint8_t att_idx)
{
    uint16_t mtu_num = 0;
    mtu_num = gattc_get_mtu(app_env.conidx) - 3;
    while (param_length)
    {
        struct user_notify_req *req = KE_MSG_ALLOC_DYN(USER_NOTIFY_REQ,
                                      prf_get_task_from_id(task_id),
                                      TASK_APP,
                                      user_notify_req, mtu_num);



        if (param_length > mtu_num)
        {
            req->send_param_length = mtu_num;
            memcpy(req->send_param_payload, param_payload, mtu_num);
            req->att_idx = att_idx;
            ke_msg_send(req);
            param_length -= mtu_num;
            param_payload += mtu_num;
        }
        else
        {
            req->send_param_length = param_length;
            req->att_idx = att_idx;
            memcpy(req->send_param_payload, param_payload, param_length);
            ke_msg_send(req);
            param_length = 0;
        }
    }
    return 1;

}

#if 0
uint8_t app_user_data_notify(uint16_t param_length , uint8_t *param_payload, uint8_t att_idx)
{
    data_notify(param_length, param_payload, TASK_ID_USER, att_idx);
    return 0;
}
#else
uint8_t app_user_data_notify(uint16_t param_length , uint8_t *param_payload, uint8_t att_idx)
{
    uint16_t mtu_num = 0;
    mtu_num = gattc_get_mtu(app_env.conidx) - 3;
    while (param_length)
    {
        if (param_length > mtu_num)
        {
            data_notify_onePackage(mtu_num , param_payload, TASK_ID_USER, att_idx);
            param_length -= mtu_num;
            param_payload += mtu_num;
        }
        else
        {
            data_notify_onePackage(param_length , param_payload, TASK_ID_USER, att_idx);
            param_length = 0;
        }
    }
    return 0;
}
#endif


// static uint8_t Speed_buf[7] ;
//void app_user_mtu_temp_send(uint16_t mtu)
//{

//

//    Speed_buf[0] = 0x05;

//    Speed_buf[1] = 0x00;

//    Speed_buf[2] = 0xAA;

//    Speed_buf[3] = 0xBB;

//    Speed_buf[4] = 0x00;

//    Speed_buf[5] = mtu % 256;

//    Speed_buf[6] = mtu / 256;

//    app_user_data_notify(7, Speed_buf);
//}

//static uint8_t data_buf[13] ;
//void app_user_updata_temp_send(uint8_t status)//,uint16_t intv_min, uint16_t intv_max, uint16_t latancy, uint16_t timesout)
//{

//

//    data_buf[0] = 0x0B;

//    data_buf[1] = 0x00;

//    data_buf[2] = 0xAA;

//    data_buf[3] = 0xCC;

//    data_buf[4] = status;

//    data_buf[5] = app_env.con_intv_min % 256;
//    data_buf[6] = app_env.con_intv_min / 256;
//    data_buf[7] = app_env.con_intv_max % 256;
//    data_buf[8] = app_env.con_intv_max / 256;
//    data_buf[9] =  app_env.con_latency % 256;
//    data_buf[10] = app_env.con_latency / 256;
//    data_buf[11] = app_env.con_time_out % 256;
//    data_buf[12] = app_env.con_time_out / 256;

//    app_user_data_notify(13, data_buf);
//}





/**
 ****************************************************************************************
 * @brief Handles health thermometer timer
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int app_user_msg_handler(ke_msg_id_t const msgid,
                                void const *param,
                                ke_task_id_t const dest_id,
                                ke_task_id_t const src_id)
{
    // todo

    return (KE_MSG_CONSUMED);
}

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */


/// Default State handlers definition
const struct ke_msg_handler app_user_msg_handler_list[] =
{
    // Note: first message is latest message checked by kernel so default is put on top.
    {KE_MSG_DEFAULT_HANDLER, (ke_msg_func_t)app_user_msg_handler},

};

const struct ke_state_handler app_user_table_handler =
{&app_user_msg_handler_list[0], (sizeof(app_user_msg_handler_list) / sizeof(struct ke_msg_handler))};

#endif //BLE_APP_USER

/// @} APP
