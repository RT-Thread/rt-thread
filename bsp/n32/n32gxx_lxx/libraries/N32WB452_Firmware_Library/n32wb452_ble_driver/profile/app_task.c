/**
 ****************************************************************************************
 *
 * @file appm_task.c
 *
 * @brief RW APP Task implementation
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup APPTASK
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"          // SW configuration

#if (BLE_APP_PRESENT)

#include "app_task.h"             // Application Manager Task API
#include "app.h"                  // Application Manager Definition
#include "gapc_task.h"            // GAP Controller Task API
#include "gapm_task.h"            // GAP Manager Task API
#include "ble_arch.h"                // Platform Definitions
#include <string.h>
#include "ke_timer.h"             // Kernel timer
#include "ke_task.h"
#include "gattc_task.h"
#include "interface.h"
#include "n32wb452_ble_api.h"

#if (BLE_APP_SEC)
#include "app_sec.h"              // Security Module Definition
#endif //(BLE_APP_SEC)

#if (BLE_APP_HT)
#include "app_ht.h"               // Health Thermometer Module Definition
#include "htpt_task.h"
#endif //(BLE_APP_HT)

#if (BLE_APP_DIS)
#include "app_dis.h"              // Device Information Module Definition
#include "diss_task.h"
#endif //(BLE_APP_DIS)

//#if (BLE_APP_BATT)
//#include "app_batt.h"             // Battery Module Definition
//#include "bass_task.h"
//#endif //(BLE_APP_BATT)

#if (BLE_APP_HID)
#include "app_hid.h"              // HID Module Definition
#include "hogpd_task.h"
#endif //(BLE_APP_HID)

#ifdef BLE_APP_AM0
#include "am0_app.h"             // Audio Mode 0 Application
#endif //defined(BLE_APP_AM0)

#if (DISPLAY_SUPPORT)
#include "app_display.h"          // Application Display Definition
#endif //(DISPLAY_SUPPORT)


#if (BLE_APP_USER)
#include "app_user.h"               // Health Thermometer Module Definition
#include "user_task.h"
#endif //(BLE_APP_HT)
#include "app.h"

#ifdef N32WB452_BT_API
#include "n32wb452_log_level.h"
#endif

/*
 * LOCAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */

extern uint8_t bda_cmd;

static uint8_t appm_get_handler(const struct ke_state_handler *handler_list,
                                ke_msg_id_t msgid,
                                void *param,
                                ke_task_id_t src_id)
{
    // Counter
    uint8_t counter;

    // Get the message handler function by parsing the message table
    for (counter = handler_list->msg_cnt; 0 < counter; counter--)
    {
        struct ke_msg_handler handler =/* (struct ke_msg_handler)*/(*(handler_list->msg_table + counter - 1));

        if ((handler.id == msgid) ||
            (handler.id == KE_MSG_DEFAULT_HANDLER))
        {
            // If handler is NULL, message should not have been received in this state
            ASSERT_ERR(handler.func);

            return (uint8_t)(handler.func(msgid, param, TASK_APP, src_id));
        }
    }

    // If we are here no handler has been found, drop the message
    return (KE_MSG_CONSUMED);
}

/*
 * MESSAGE HANDLERS
 ****************************************************************************************
 */

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
static int appm_adv_timeout_handler(ke_msg_id_t const msgid,
                                   void const *param,
                                   ke_task_id_t const dest_id,
                                   ke_task_id_t const src_id)
{
    #if (BLE_APP_HID)
    #else
    // Stop advertising
    appm_stop_advertising();
    #endif

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles ready indication from the GAP. - Reset the stack
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapm_device_ready_ind_handler(ke_msg_id_t const msgid,
                                         void const *param,
                                         ke_task_id_t const dest_id,
                                         ke_task_id_t const src_id)
{

    // Application has not been initialized
    ASSERT_ERR(ke_state_get(dest_id) == APPM_INIT);

    // Reset the stack
    struct gapm_reset_cmd* cmd = KE_MSG_ALLOC(GAPM_RESET_CMD,
                                              TASK_GAPM, TASK_APP,
                                              gapm_reset_cmd);

    cmd->operation = GAPM_RESET;
    ke_msg_send(cmd);
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles GAP manager command complete events.
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int appm_gapm_cmp_evt_handler(ke_msg_id_t const msgid,
                                struct gapm_cmp_evt const *param,
                                ke_task_id_t const dest_id,
                                ke_task_id_t const src_id)
{
    ble_log(BLE_DEBUG,"operation:%x\r\n",param->operation);
    ble_log(BLE_DEBUG,"status:%x\r\n",param->status);
    switch (param->operation)
    {
    // Reset completed
        case(GAPM_RESET):
        {
            if (param->status == GAP_ERR_NO_ERROR)//GAP_ERR_NO_ERROR
            {
                // Set Device configuration
                struct gapm_set_dev_config_cmd *cmd = KE_MSG_ALLOC(GAPM_SET_DEV_CONFIG_CMD,
                                                      TASK_GAPM, TASK_APP,
                                                      gapm_set_dev_config_cmd);
                // Set the operation
                cmd->operation = GAPM_SET_DEV_CONFIG;
                // Set the device role - Peripheral
                cmd->role      = GAP_ROLE_PERIPHERAL;
                // Set Data length parameters

                cmd->max_mtu = 255;//app_env.max_mtu;//512; //pts test
                cmd->pairing_mode = app_env.pairing_mode;//GAPM_PAIRING_LEGACY;

                memcpy(cmd->addr.addr, app_env.bdaddr.addr, 6);
                cmd->addr_type = app_env.bdaddr_type;
                cmd->sugg_max_tx_octets = BLE_MIN_OCTETS;
                cmd->sugg_max_tx_time   = BLE_MIN_TIME;
                cmd->max_mtu   =  app_env.max_mtu;

                cmd->att_cfg    |= GAPM_MASK_ATT_SVC_CHG_EN;
                // load IRK
                memcpy(cmd->irk.key, app_env.loc_irk, KEY_LEN);

                // Send message
                ke_msg_send(cmd);
            }
            else
            {
                ASSERT_ERR(0);
            }
        }
        break;

        case (GAPM_SET_DEV_CONFIG):
        {
            //ASSERT_INFO(param->status == GAP_ERR_NO_ERROR, param->operation, param->status);
            // Go to the create db state
            ke_state_set(TASK_APP, APPM_CREATE_DB);

            // Add the first required service in the database
            // and wait for the PROFILE_ADDED_IND
            appm_add_svc();
        }
        break;

        case (GAPM_PROFILE_TASK_ADD):
        {
            struct gapm_gen_rand_nb_cmd *cmd = KE_MSG_ALLOC(GAPM_GEN_RAND_NB_CMD,
                                                            TASK_GAPM, TASK_APP,
                                                            gapm_gen_rand_nb_cmd);

            cmd->operation   = GAPM_GEN_RAND_NB;
            app_env.rand_cnt = 1;
            ke_msg_send(cmd);
        }
        break;

        case (GAPM_GEN_RAND_NB) :
        {
            if (app_env.rand_cnt == 1)
            {
                // Generate a second random number
                app_env.rand_cnt++;
                struct gapm_gen_rand_nb_cmd *cmd = KE_MSG_ALLOC(GAPM_GEN_RAND_NB_CMD,
                                                                TASK_GAPM, TASK_APP,
                                                                gapm_gen_rand_nb_cmd);

                cmd->operation = GAPM_GEN_RAND_NB;
                ke_msg_send(cmd);
            }
            else
            {
                // Prepare the GAPM_START_ADVERTISE_CMD message
                struct gapm_set_irk_cmd *cmd = KE_MSG_ALLOC(GAPM_SET_IRK_CMD,
                                                        TASK_GAPM, TASK_APP,
                                                        gapm_set_irk_cmd);

                app_env.rand_cnt=0;
                /// GAPM requested operation:
                ///  - GAPM_SET_IRK: Set device configuration
                cmd->operation = GAPM_SET_IRK;
                memcpy(&cmd->irk.key[0], &app_env.loc_irk[0], KEY_LEN);
                ke_msg_send(cmd);
            }
        }
        break;

        case (GAPM_SET_IRK):
        {
             ASSERT_INFO(param->status == GAP_ERR_NO_ERROR, param->operation, param->status);
            // Add the next requested service
            app_env.rand_cnt = 0;

            if (!appm_add_svc())
            {
                // Go to the ready state
                // ke_state_set(TASK_APP, APPM_READY);
                // No more service to add, start advertising
                // appm_start_advertising();
                struct gapm_get_dev_info_cmd* dev_cmd = KE_MSG_ALLOC(GAPM_GET_DEV_INFO_CMD ,
                    TASK_GAPM, TASK_APP, gapm_get_dev_info_cmd);

                // fill parameters
                dev_cmd->operation = GAPM_GET_DEV_BDADDR;

                ke_msg_send(dev_cmd);


            }
        }
        break;
        case (GAPM_GET_DEV_BDADDR):
            ke_state_set(TASK_APP, APPM_READY);
            //start advertinsing
            appm_start_advertising();
            break;

        case (GAPM_ADV_NON_CONN):
        case (GAPM_ADV_UNDIRECT):
        case (GAPM_ADV_DIRECT):
        case (GAPM_ADV_DIRECT_LDC):
        case (GAPM_UPDATE_ADVERTISE_DATA):
        {
            ASSERT_INFO(param->status == GAP_ERR_NO_ERROR, param->operation, param->status);
        }
        break;


        default:
        {
            // Drop the message
        }
        break;
    }

    return (KE_MSG_CONSUMED);
}

static int gapc_get_dev_info_req_ind_handler(ke_msg_id_t const msgid,
        struct gapc_get_dev_info_req_ind const *param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id)
{
    switch (param->req)
    {
        case GAPC_DEV_NAME:
        {
            struct gapc_get_dev_info_cfm * cfm = KE_MSG_ALLOC_DYN(GAPC_GET_DEV_INFO_CFM,
                                                    src_id, dest_id,
                                                    gapc_get_dev_info_cfm, APP_DEVICE_NAME_MAX_LEN);
            cfm->req = param->req;
            cfm->info.name.length = appm_get_dev_name(cfm->info.name.value);

            // Send message
            ke_msg_send(cfm);
        }
        break;

    case GAPC_DEV_APPEARANCE:
        {
            // Allocate message
            struct gapc_get_dev_info_cfm *cfm = KE_MSG_ALLOC(GAPC_GET_DEV_INFO_CFM,
                                                src_id, dest_id,
                                                gapc_get_dev_info_cfm);
            cfm->req = param->req;
            // Set the device appearance
#if (BLE_APP_HT)
            // Generic Thermometer - TODO: Use a flag
            cfm->info.appearance = 728;
#elif (BLE_APP_HID)
            // HID Mouse
            cfm->info.appearance = 962;
#else
            // No appearance
            cfm->info.appearance = 0;
#endif

            // Send message
            ke_msg_send(cfm);
        }
        break;

    case GAPC_DEV_SLV_PREF_PARAMS:
        {
            // Allocate message
            struct gapc_get_dev_info_cfm *cfm = KE_MSG_ALLOC(GAPC_GET_DEV_INFO_CFM,
                                                src_id, dest_id,
                                                gapc_get_dev_info_cfm);
            cfm->req = param->req;
            // Slave preferred Connection interval Min
            cfm->info.slv_params.con_intv_min = 100;
            // Slave preferred Connection interval Max
            cfm->info.slv_params.con_intv_max = 200;
            // Slave preferred Connection latency
            cfm->info.slv_params.slave_latency  = 4;
            // Slave preferred Link supervision timeout
            cfm->info.slv_params.conn_timeout    = 600;  // 2s (500*10ms)

            // Send message
            ke_msg_send(cfm);
        }
        break;

    default: /* Do Nothing */
        break;
    }


    return (KE_MSG_CONSUMED);
}
/**
 ****************************************************************************************
 * @brief Handles GAPC_SET_DEV_INFO_REQ_IND message.
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapc_set_dev_info_req_ind_handler(ke_msg_id_t const msgid,
        struct gapc_set_dev_info_req_ind const *param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id)
{
    // Set Device configuration
    struct gapc_set_dev_info_cfm* cfm = KE_MSG_ALLOC(GAPC_SET_DEV_INFO_CFM, src_id, dest_id,
                                                     gapc_set_dev_info_cfm);
    // Reject to change parameters
    cfm->status = GAP_ERR_REJECTED;
    cfm->req = param->req;
    // Send message
    ke_msg_send(cfm);

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles connection complete event from the GAP. Enable all required profiles
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapc_connection_req_ind_handler(ke_msg_id_t const msgid,
        struct gapc_connection_req_ind const *param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id)
{
    app_env.conidx = KE_IDX_GET(src_id);
    app_env.rx_data.RxTotalLen =0;
    app_env.rx_data.RxCurrentLen=0;

    // Check if the received Connection Handle was valid

    //BT_add_white_list(param->peer_addr.addr,param->peer_addr_type);

    if (app_env.conidx != GAP_INVALID_CONIDX)
    {
        // Retrieve the connection info from the parameters
        app_env.conhdl = param->conhdl;

        // Clear the advertising timeout timer
        if (ke_timer_active(APP_ADV_TIMEOUT_TIMER, TASK_APP))
        {
            ke_timer_clear(APP_ADV_TIMEOUT_TIMER, TASK_APP);
        }

        // Send connection confirmation
        struct gapc_connection_cfm *cfm = KE_MSG_ALLOC(GAPC_CONNECTION_CFM,
                KE_BUILD_ID(TASK_GAPC, app_env.conidx), TASK_APP,
                gapc_connection_cfm);

        // 设置邦定认证模式 为  GAP_AUTH_REQ_NO_MITM_BOND
        cfm->auth      = GAP_AUTH_REQ_NO_MITM_BOND;

        // Send the message
        ke_msg_send(cfm);

        // ke_state_set(dest_id, APPM_CONNECTED);
        ke_state_set(TASK_APP, APPM_CONNECTED);
        if (g_pcallback) {
            g_pcallback(BT_EVENT_CONNECTED, NULL, 0, 0);
        }
        g_connnet_start = 1;

        /*--------------------------------------------------------------
         * ENABLE REQUIRED PROFILES
         *--------------------------------------------------------------*/
//        #if (BLE_APP_BATT)
//        // Enable Battery Service
//        app_batt_enable_prf(app_env.conhdl);
//        #endif //(BLE_APP_BATT)


        #if (BLE_APP_USER)
        //app_user_enable_prf(app_env.conhdl);
        #endif


    }
    else
    {
        // No connection has been establish, restart advertising
        appm_start_advertising();
    }
    //
    //

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles GAP controller command complete events.
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int appm_gapc_cmp_evt_handler(ke_msg_id_t const msgid,
                                struct gapc_cmp_evt const *param,
                                ke_task_id_t const dest_id,
                                ke_task_id_t const src_id)
{
    switch (param->operation)
    {

        case (GAPC_UPDATE_PARAMS):
        {
//        extern uint32_t need_rsp_type;
//        if (need_rsp_type == 0xcc )
//        {
//                app_user_updata_temp_send(param->status);
//        }
        }
        break;

        default:
        {
        }
        break;
    }

    return (KE_MSG_CONSUMED);
}
static int appm_gapc_param_updated_req_ind_handler(ke_msg_id_t const msgid,
                                struct gapc_param_update_req_ind const *param,
                                ke_task_id_t const dest_id,
                                ke_task_id_t const src_id)
{


    struct gapc_param_update_cfm *cmd = KE_MSG_ALLOC(GAPC_PARAM_UPDATE_CFM,
                KE_BUILD_ID(TASK_GAPC, app_env.conidx), TASK_APP,
                gapc_param_update_cfm);

    cmd->accept = true;
    cmd->ce_len_min = 0xFFFF;
    cmd->ce_len_max = 0xFFFF;
    ke_msg_send(cmd);
    return (KE_MSG_CONSUMED);
}


/**
 ****************************************************************************************
 * @brief Handles disconnection complete event from the GAP.
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapc_disconnect_ind_handler(ke_msg_id_t const msgid,
                                      struct gapc_disconnect_ind const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{

    // Go to the ready state
    ke_state_set(TASK_APP, APPM_READY);

    #if (BLE_APP_HT)
    // Stop interval timer
    app_stop_timer();
    #endif //(BLE_APP_HT)

    #if (DISPLAY_SUPPORT)
    // Update Connection State screen
    app_display_set_con(false);
    #endif //(DISPLAY_SUPPORT)

    app_env.rx_data.RxTotalLen =0;
    app_env.rx_data.RxCurrentLen=0;
    appm_start_advertising();


    return (KE_MSG_CONSUMED);
}


static int gapm_profile_added_ind_handler(ke_msg_id_t const msgid,
                                          struct gapm_profile_added_ind *param,
                                          ke_task_id_t const dest_id,
                                          ke_task_id_t const src_id)
{
    // Current State
    uint8_t state            = ke_state_get(dest_id);
    if (state == APPM_CREATE_DB)
    {
        switch (param->prf_task_id)
        {
            #if defined (BLE_APP_AM0)
            case (TASK_ID_AM0_HAS):
            {
                am0_app_set_prf_task(param->prf_task_nb);
            }
            break;
#endif // defined (BLE_APP_AM0)

             #if BLE_APP_USER
            case (TASK_ID_USER):
            {

            } break;
            #endif // defined (BLE_APP_USER)
        default: /* Nothing to do */
            break;
        }
    }
    else
    {
        ASSERT_INFO(0, state, src_id);
    }

    return KE_MSG_CONSUMED;
}

/**
 ****************************************************************************************
 * @brief Handles reception of all messages sent from the lower layers to the application
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int appm_msg_handler(ke_msg_id_t const msgid,
                            void *param,
                            ke_task_id_t const dest_id,
                            ke_task_id_t const src_id)
{
    // Retrieve identifier of the task from received message
    ke_task_id_t src_task_id = MSG_T(msgid);
    // Message policy
    uint8_t msg_pol          = KE_MSG_CONSUMED;

    switch (src_task_id)
    {
        case (TASK_ID_GAPC):
        {
            #if (BLE_APP_SEC)
            if ((msgid >= GAPC_BOND_CMD) &&
                (msgid <= GAPC_SECURITY_IND))
            {
                // Call the Security Module
                msg_pol = appm_get_handler(&app_sec_table_handler, msgid, param, src_id);
            }
            #endif //(BLE_APP_SEC)
            // else drop the message
        }
        break;

        case (TASK_ID_GATTC):
        {
            // Service Changed - Drop
        } break;

        #if (BLE_APP_HT)
        case (TASK_ID_HTPT):
        {
            // Call the Health Thermometer Module
            msg_pol = appm_get_handler(&app_ht_table_handler, msgid, param, src_id);
        }
        break;
#endif //(BLE_APP_HT)

        #if (BLE_APP_DIS)
        case (TASK_ID_DISS):
        {
            // Call the Device Information Module
            msg_pol = appm_get_handler(&app_dis_table_handler, msgid, param, src_id);
        }
        break;
#endif //(BLE_APP_DIS)

        #if (BLE_APP_HID)
    case(TASK_ID_HOGPD):
        {
            // Call the HID Module
            msg_pol = appm_get_handler(&app_hid_table_handler, msgid, param, src_id);
        }
        break;
#endif //(BLE_APP_HID)

//        #if (BLE_APP_BATT)
//    case(TASK_ID_BASS):
//        {
//            // Call the Battery Module
//            msg_pol = appm_get_handler(&app_batt_table_handler, msgid, param, src_id);
//        }
//        break;
//#endif //(BLE_APP_BATT)

        #if defined(BLE_APP_AM0)
        case (TASK_ID_AM0):
        {
            // Call the Audio Mode 0 Module
            msg_pol = appm_get_handler(&am0_app_table_handler, msgid, param, src_id);
        }
        break;
        case (TASK_ID_AM0_HAS):
        {
            // Call the Audio Mode 0 Module
            msg_pol = appm_get_handler(&am0_app_has_table_handler, msgid, param, src_id);
        }
        break;
#endif // defined(BLE_APP_AM0)
#if (BLE_APP_USER)
    case(TASK_ID_USER):
        {
            // Call the Health Thermometer Module
            msg_pol = appm_get_handler(&app_user_table_handler, msgid, param, src_id);
        }
        break;
#endif //(BLE_APP_HT)
    default:
        {
            #if (BLE_APP_HT)
            if (msgid == APP_HT_MEAS_INTV_TIMER)
            {
                msg_pol = appm_get_handler(&app_ht_table_handler, msgid, param, src_id);
            }
            #endif //(BLE_APP_HT)

            #if (BLE_APP_HID)
            if (msgid == APP_HID_MOUSE_TIMEOUT_TIMER)
            {
                msg_pol = appm_get_handler(&app_hid_table_handler, msgid, param, src_id);
            }
#endif //(BLE_APP_HID)
        }
        break;
    }

    return (msg_pol);
}

/**
 ****************************************************************************************
 * @brief Handles reception of random number generated message
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int appm_gapm_gen_rand_nb_ind_handler(ke_msg_id_t const msgid, struct gapm_gen_rand_nb_ind *param,
                                        ke_task_id_t const dest_id, ke_task_id_t const src_id)
{

    if (app_env.rand_cnt==1)      // First part of IRK
    {
        memcpy(&app_env.loc_irk[0], &param->randnb.nb[0], 8);
    }
    else if (app_env.rand_cnt==2) // Second part of IRK
    {
        memcpy(&app_env.loc_irk[8], &param->randnb.nb[0], 8);
    }

    return KE_MSG_CONSUMED;
}
/*
 * GLOBAL VARIABLES DEFINITION
 ****************************************************************************************
 */
static  int gatt_set_mtu_ind_handler(ke_msg_id_t const msgid, struct gattc_mtu_changed_ind const *param,
                                 ke_task_id_t const dest_id, ke_task_id_t const src_id)
{
    extern uint32_t need_rsp_type ;
    app_env.max_mtu = param->mtu;
//if (need_rsp_type == 0xbb )
//{
//        app_user_mtu_temp_send(param->mtu);
//        need_rsp_type = 0;
//}

    return (KE_MSG_CONSUMED);
}


static int gapc_param_updated_ind_handler(ke_msg_id_t const msgid,
                                     struct gapc_param_updated_ind const *param,
                                     ke_task_id_t const dest_id,
                                     ke_task_id_t const src_id)
{
    app_env.con_interval = param->con_interval;
    app_env.con_latency = param->con_latency;
    app_env.con_time_out =    param->sup_to;
    return (KE_MSG_CONSUMED);
}

static int gapm_read_wlistsize_req_ind_handler(ke_msg_id_t const msgid,
                                        struct gapm_white_list_size_ind const *param,
                                        ke_task_id_t const dest_id,
                                        ke_task_id_t const src_id)
{

    app_env.wlst_size = param->size;
    return (KE_MSG_CONSUMED);
}

static int gapm_read_bda_req_ind_handler(ke_msg_id_t const msgid,
                                        struct gapm_dev_bdaddr_ind const *param,
                                        ke_task_id_t const dest_id,
                                        ke_task_id_t const src_id)
{

    return (KE_MSG_CONSUMED);
}

static int gapm_read_txpower_req_ind_handler(ke_msg_id_t const msgid,
                                        struct gapm_dev_adv_tx_power_ind const *param,
                                        ke_task_id_t const dest_id,
                                        ke_task_id_t const src_id)
{

    return (KE_MSG_CONSUMED);
}
static int gapm_read_RSSI_req_ind_handler(ke_msg_id_t const msgid,
                                        struct gapc_con_rssi_ind const *param,
                                        ke_task_id_t const dest_id,
                                        ke_task_id_t const src_id)
{
    app_env.rssi = param->rssi;
    return (KE_MSG_CONSUMED);
}
/* Default State handlers definition. */
const struct ke_msg_handler appm_default_state[] =
{
    // Note: first message is latest message checked by kernel so default is put on top.
    {KE_MSG_DEFAULT_HANDLER,    (ke_msg_func_t)appm_msg_handler},

    {APP_ADV_TIMEOUT_TIMER,     (ke_msg_func_t)appm_adv_timeout_handler},
    {GAPM_DEVICE_READY_IND,     (ke_msg_func_t)gapm_device_ready_ind_handler},
    {GAPM_CMP_EVT,              (ke_msg_func_t)appm_gapm_cmp_evt_handler},
    {GAPC_GET_DEV_INFO_REQ_IND, (ke_msg_func_t)gapc_get_dev_info_req_ind_handler},
    {GAPC_SET_DEV_INFO_REQ_IND, (ke_msg_func_t)gapc_set_dev_info_req_ind_handler},
    {GAPC_CONNECTION_REQ_IND,   (ke_msg_func_t)gapc_connection_req_ind_handler},
    {GAPC_CMP_EVT,              (ke_msg_func_t)appm_gapc_cmp_evt_handler},
    {GAPC_DISCONNECT_IND,       (ke_msg_func_t)gapc_disconnect_ind_handler},
    {GAPM_PROFILE_ADDED_IND,    (ke_msg_func_t)gapm_profile_added_ind_handler},
    {GAPM_GEN_RAND_NB_IND,      (ke_msg_func_t)appm_gapm_gen_rand_nb_ind_handler},
    {GAPM_WHITE_LIST_SIZE_IND,  (ke_msg_func_t)gapm_read_wlistsize_req_ind_handler},
    {GAPM_DEV_BDADDR_IND,       (ke_msg_func_t)gapm_read_bda_req_ind_handler},
    {GAPM_DEV_ADV_TX_POWER_IND, (ke_msg_func_t)gapm_read_txpower_req_ind_handler},
    {GAPC_CON_RSSI_IND,         (ke_msg_func_t)gapm_read_RSSI_req_ind_handler},
    {GATTC_MTU_CHANGED_IND,     (ke_msg_func_t)gatt_set_mtu_ind_handler},
    {GAPC_PARAM_UPDATED_IND,    (ke_msg_func_t)gapc_param_updated_ind_handler},
    {GAPC_PARAM_UPDATE_REQ_IND, (ke_msg_func_t)appm_gapc_param_updated_req_ind_handler},

};

/* Specifies the message handlers that are common to all states. */
const struct ke_state_handler appm_default_handler = KE_STATE_HANDLER(appm_default_state);

/* Defines the place holder for the states of all the task instances. */
ke_state_t appm_state[APP_IDX_MAX];

#endif //(BLE_APP_PRESENT)

/// @} APPTASK
