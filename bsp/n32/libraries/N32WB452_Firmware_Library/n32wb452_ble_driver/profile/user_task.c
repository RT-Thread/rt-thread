/**
 ****************************************************************************************
 *
 * @file user_task.c
 *
 * @brief
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup HTPTTASK
 * @{
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"

#if (BLE_APP_USER)
#include "app.h"
#include "gap.h"
#include "gattc_task.h"
#include "attm.h"
#include "user.h"
#include "user_task.h"
#include "prf_utils.h"
#include "app_user.h"
#include "app_task.h"
#include "ke_mem.h"
#include "co_utils.h"
//#include "interface.h"
#include "ble_arch.h"
#include "ke_timer.h"

#ifdef N32WB452_BT_API
#include "n32wb452_data_fifo.h"
#include "n32wb452_ble_api.h"
#include "n32wb452_log_level.h"

extern uint8_t rx_fff5_chr[300];
extern uint16_t rx_fff5_len;
extern uint8_t rx_fff5_flag;
extern uint16_t rvc_total;

extern bt_event_callback_handler_t g_pcallback;

#endif

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */
//#include "Bkey_user.h"
/**
 ****************************************************************************************
 * @brief Handles reception of the @ref HTPT_ENABLE_REQ message.
 * The handler enables the Health Thermometer Profile Thermometer Role.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int user_enable_req_handler(ke_msg_id_t const msgid,
                                   struct user_enable_req const *param,
                                   ke_task_id_t const dest_id,
                                   ke_task_id_t const src_id)
{
    uint8_t status = PRF_ERR_REQ_DISALLOWED;
    // check state of the task
    if (gapc_get_conhdl(param->conidx) != GAP_INVALID_CONHDL)
    {
        // restore Bond Data
        struct user_env_tag *user_env =  PRF_ENV_GET(USER, user);
        user_env->ntf_ind_cfg[param->conidx] = param->ntf_ind_cfg;
        status = GAP_ERR_NO_ERROR;

    }

    // send response
    struct user_enable_rsp *rsp = KE_MSG_ALLOC(USER_ENABLE_RSP, src_id, dest_id, user_enable_rsp);
    rsp->conidx = param->conidx;
    rsp->status = status;
    ke_msg_send(rsp);

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref HTPT_TEMP_SEND_REQ message.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int user_data_notify_req_handler(ke_msg_id_t const msgid,
                                        struct user_notify_req const *param,
                                        ke_task_id_t const dest_id,
                                        ke_task_id_t const src_id)
{
    // Status
    int msg_status = KE_MSG_SAVED;
    uint8_t state = ke_state_get(dest_id);
  
    // check state of the task
    if (state == USER_IDLE)
    {
        // Get the address of the environment
        struct user_env_tag *user_env = PRF_ENV_GET(USER, user);

        // for intermediate measurement, feature must be enabled
        if (/*!(param->send_param_length) &&*/ (!USER_IS_FEATURE_SUPPORTED(user_env->features, USER_DATA_NOTIFY_CHAR_SUP)))
        {
            struct user_notify_rsp *rsp = KE_MSG_ALLOC(USER_NOTIFY_RSP, src_id, dest_id, user_notify_rsp);
            rsp->status = PRF_ERR_FEATURE_NOT_SUPPORTED;
            ke_msg_send(rsp);
        }
        else
        {
            // allocate operation to execute
            user_env->operation    = (struct user_op *) ke_malloc(sizeof(struct user_op) + param->send_param_length, KE_MEM_ATT_DB);

            // Initialize operation parameters
            user_env->operation->cursor  = 0;
            user_env->operation->dest_id = src_id;
            user_env->operation->conidx  = GAP_INVALID_CONIDX;

            // Stable measurement indication or intermediate measurement notification

            user_env->operation->op      = user_env->ntf_ind_cfg[param->att_idx+1];// USER_DATA_NTF;
            //蓝牙 notify handle
            user_env->operation->handle  = USER_HANDLE(param->att_idx);


            //Pack the temperature measurement value
 
            user_env->operation->length  = param->send_param_length;
            memcpy(&(user_env->operation->data[0]), param->send_param_payload, user_env->operation->length);
            // put task in a busy state

            ke_state_set(dest_id, USER_BUSY);

            user_exe_operation();
        }

        msg_status = KE_MSG_CONSUMED;
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
static int user_gattc_att_info_req_ind_handler(ke_msg_id_t const msgid,
        struct gattc_att_info_req_ind *param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id)
{

    struct user_env_tag *user_env = PRF_ENV_GET(USER, user);

    uint8_t att_idx = USER_IDX(param->handle);
    struct gattc_att_info_cfm *cfm;

    //Send write response
    cfm = KE_MSG_ALLOC(GATTC_ATT_INFO_CFM, src_id, dest_id, gattc_att_info_cfm);
    cfm->handle = param->handle;


    ke_msg_send(cfm);

    return (KE_MSG_CONSUMED);
}




 

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref GL2C_CODE_ATT_WR_CMD_IND message.
 * The handler compares the new values with current ones and notifies them if they changed.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int user_gattc_write_req_ind_handler(ke_msg_id_t const msgid,
                                       struct gattc_write_req_ind const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id)
{
#ifdef N32WB452_BT_API
    int32_t ret;
#endif


    struct user_env_tag *user_env = PRF_ENV_GET(USER, user);
    uint8_t status = ATT_ERR_NO_ERROR;
    int msg_status = KE_MSG_CONSUMED;
    uint8_t conidx  = KE_IDX_GET(src_id);
    // to check if confirmation message should be send
    uint8_t att_idx = USER_IDX(param->handle);
//    uint32_t i;
   // ble_log(BLE_DEBUG,"%d\r\n",att_idx);
    if (param->length > USER_DATA_LEN_MAX)
    {
        status = PRF_ERR_UNEXPECTED_LEN;
    }
    else
    {
//      printf("user_gattc_write_req_ind_handler, idx = %x\r\n", att_idx);
        switch (att_idx)
        {
            case USER_IDX_WRITE_NOTIFY_VAL:    
            {
#ifdef N32WB452_BT_API

                ble_log(BLE_DEBUG,"w[%x,%d].\r\n", param->value, param->length);
                ret = fifo_write(param->value, param->length);
                if (ret != E_OK) {
                    ble_log(BLE_DEBUG,"write err.\r\n");
                }

                if (g_pcallback) {
                    (*g_pcallback)(BT_EVENT_RCV_DATA, param->value, param->length, att_idx);
                }
#else

                // test for  NK-bluetooth apk test 
                ble_log(BLE_DEBUG,"curlen=%d,totallen=%d,buf=0x%x[basebuf:%x].\r\n", app_env.rx_data.RxCurrentLen, app_env.rx_data.RxTotalLen, param->value, app_env.rx_data.RxBuf);
                ble_log(BLE_DEBUG,"RECV[%02x]: ",param->length);
                for(i=0; i<param->length; i++)
                {
                    ble_log(BLE_DEBUG,"%02X, ",param->value[i]);
                }
                ble_log(BLE_DEBUG,"\r\n");
                ble_log(BLE_DEBUG,"1 curlen=%d, TotalLen = %d.\r\n", app_env.rx_data.RxCurrentLen, app_env.rx_data.RxTotalLen);

                if (app_env.rx_data.RxTotalLen == 0)
                {
                    app_env.rx_data.RxCurrentLen =  0;
                    app_env.rx_data.RxTotalLen = param->value[0] + (param->value[1]<<8) + 2;
                    ble_log(BLE_DEBUG,"2RxTotalLen = %d.\r\n", app_env.rx_data.RxTotalLen);

                    ASSERT_ERR( app_env.rx_data.RxTotalLen < RX_DAT_BUF_SIZE );                       
                }
                
                memcpy(app_env.rx_data.RxBuf+app_env.rx_data.RxCurrentLen, param->value,param->length);
                app_env.rx_data.RxCurrentLen += param->length;
                if (app_env.rx_data.RxCurrentLen >= app_env.rx_data.RxTotalLen)
                {
                    ble_log(BLE_DEBUG,"3data_notify[%d,%d].\r\n", app_env.rx_data.RxCurrentLen, app_env.rx_data.RxTotalLen);

                    app_user_data_notify(app_env.rx_data.RxTotalLen, app_env.rx_data.RxBuf,  USER_IDX_WRITE_NOTIFY_VAL);
                    app_env.rx_data.RxTotalLen = 0;
                    app_env.rx_data.RxCurrentLen  = 0;
                }
#endif
            }

            break;
#ifdef BLE_OTA_WRITE_CHAR_EN
            case USER_IDX_WRITE_NOTIFY2_CFG:
            {                
                status = user_update_ntf_ind_cfg(conidx, USER_DATA_NTF, PRF_CLI_START_NTF, att_idx, co_read16p(param->value));                                  
            }
            break;
#endif
            case USER_IDX_WRITE_NOTIFY_CFG: //0xFFF5 NOTIFY ENABLE
            {           
                status = user_update_ntf_ind_cfg(conidx, USER_DATA_NTF, PRF_CLI_START_NTF, att_idx, co_read16p(param->value));                      
            }
            break;

            default:
            {
                status = ATT_ERR_REQUEST_NOT_SUPPORTED;                     
            }
            break;
        }
    }
    //Send write response
    struct gattc_write_cfm *cfm = KE_MSG_ALLOC(GATTC_WRITE_CFM, src_id, dest_id, gattc_write_cfm);
    cfm->handle = param->handle;
    cfm->status = status;
    ke_msg_send(cfm);

    return (msg_status);
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
static int user_gattc_read_req_ind_handler(ke_msg_id_t const msgid, struct gattc_read_req_ind const *param,
                                      ke_task_id_t const dest_id, ke_task_id_t const src_id)
{
    struct user_env_tag *user_env = PRF_ENV_GET(USER, user);
    uint8_t value_size = 0;
    uint8_t status = ATT_ERR_NO_ERROR;
    uint8_t value[USER_DATA_LEN_MAX];
    // retrieve handle information
    uint8_t att_idx = USER_IDX(param->handle);
    switch (att_idx)
    {
#ifdef BLE_OTA_WRITE_CHAR_EN
        case USER_IDX_READ_NOTIFY_VAL:
        {
#if 1 // lizhk add, fff7 read encryption status.
            if (ke_state_get(TASK_APP)!= APPM_ENCRYPTED)
            {
                memcpy(value, (uint8_t *)"\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 20);
                value_size = 20;
            }
            else
            {
                memcpy(value, (uint8_t *)"\x17\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 20);
                value_size = 20;
            }
#endif
            break;
        }
#endif
        
        case USER_IDX_WRITE_NOTIFY_CFG:
#if BLE_OTA_WRITE_CHAR_EN
        case USER_IDX_WRITE_NOTIFY2_CFG:
        {
            *(uint16_t *)value = user_env->ntf_ind_cfg[att_idx];  
            value_size = 2;
        }    
        break;
#endif

        default:
        {
            status = ATT_ERR_REQUEST_NOT_SUPPORTED;
        }
        break;
    }
    // Send data to peer device
    struct gattc_read_cfm *cfm = KE_MSG_ALLOC_DYN(GATTC_READ_CFM, src_id, dest_id, gattc_read_cfm, value_size);
    cfm->length = value_size;
    memcpy(cfm->value, value, value_size);
    cfm->handle = param->handle;
    cfm->status = status;   
    ke_msg_send(cfm);// Send value to peer device.
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles @ref GATTC_CMP_EVT for GATTC_NOTIFY and GATT_INDICATE message meaning
 * that Measurement notification/indication has been correctly sent to peer device
 *
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int user_gattc_cmp_evt_handler(ke_msg_id_t const msgid, struct gattc_cmp_evt const *param,
                                 ke_task_id_t const dest_id, ke_task_id_t const src_id)
{
    // continue operation execution

    user_exe_operation();

    return (KE_MSG_CONSUMED);
}


/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */



/// Default State handlers definition
const struct ke_msg_handler user_default_state[] =
{
    {USER_ENABLE_REQ,            (ke_msg_func_t) user_enable_req_handler},
    {USER_NOTIFY_REQ,            (ke_msg_func_t) user_data_notify_req_handler},
        
    {GATTC_ATT_INFO_REQ_IND,     (ke_msg_func_t) user_gattc_att_info_req_ind_handler},
    {GATTC_WRITE_REQ_IND,        (ke_msg_func_t) user_gattc_write_req_ind_handler},
    {GATTC_READ_REQ_IND,         (ke_msg_func_t) user_gattc_read_req_ind_handler},
    {GATTC_CMP_EVT,              (ke_msg_func_t) user_gattc_cmp_evt_handler},
        
};


///Specifies the message handlers that are common to all states.
const struct ke_state_handler user_default_handler = KE_STATE_HANDLER(user_default_state);
//const struct ke_state_handler user1_default_handler = KE_STATE_HANDLER(user1_default_state);
//const struct ke_state_handler user2_default_handler = KE_STATE_HANDLER(user2_default_state);

#endif //BLE_HT_THERMOM

/// @} HTPTTASK

