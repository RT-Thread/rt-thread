/**
 ****************************************************************************************
 *
 * @file app.c
 *
 * @brief Application entry point
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

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"             // SW configuration
#include "stdio.h"
#if (BLE_APP_PRESENT)
#include <string.h>

#include "app_task.h"                // Application task Definition
#include "app.h"                     // Application Definition
#include "gap.h"                     // GAP Definition
#include "gapm_task.h"               // GAP Manager Task API
#include "gapc_task.h"               // GAP Controller Task API
#include "gapm.h"
#include "co_bt.h"                   // Common BT Definition
#include "co_math.h"                 // Common Maths Definition
#include "interface.h"
#include "gattc_task.h"

#if (BLE_APP_SEC)
#include "app_sec.h"                 // Application security Definition
#endif // (BLE_APP_SEC)

#if (NVDS_SUPPORT)
#include "nvds.h"                    // NVDS Definitions
#endif //(NVDS_SUPPORT)

#if (BLE_APP_USER)
#include "app_user.h"                  // Health Thermometer Application Definitions
#endif
//#include "BtDrv.h"
#include "n32wb452_ble_api.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/// Default Device Name if no value can be found in NVDS
#define APP_DFLT_DEVICE_NAME            app_env.dev_name//
#define APP_DFLT_DEVICE_NAME_LEN        (sizeof(APP_DFLT_DEVICE_NAME))


#if (BLE_APP_HID)
// HID Mouse
#define DEVICE_NAME        "Hid Mouse"
#else
#define DEVICE_NAME        "NZ DEVICE"
#endif

#define DEVICE_NAME_SIZE    sizeof(DEVICE_NAME)

/**
 * UUID List part of ADV Data
 * --------------------------------------------------------------------------------------
 * x03 - Length
 * x03 - Complete list of 16-bit UUIDs available
 * x09\x18 - Health Thermometer Service UUID
 *   or
 * x12\x18 - HID Service UUID
 * --------------------------------------------------------------------------------------
 */

#if (BLE_APP_HT)
#define APP_HT_ADV_DATA_UUID        "\x03\x03\x09\x18"
#define APP_HT_ADV_DATA_UUID_LEN    (4)
#endif //(BLE_APP_HT)

#if (BLE_APP_HID)
#define APP_HID_ADV_DATA_UUID       "\x03\x03\x12\x18"
#define APP_HID_ADV_DATA_UUID_LEN   (4)
#endif //(BLE_APP_HID)


#if (BLE_APP_USER)
#define APP_USER_ADV_DATA_UUID       "\x03\x03\x00\xaa"
#define APP_USER_ADV_DATA_UUID_LEN    (4)
#endif //(BLE_APP_HT)


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

typedef void (*appm_add_svc_func_t)(void);

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/// List of service to add in the database
enum appm_svc_list
{

#if (BLE_APP_BATT)
    APPM_SVC_BATT,
#endif //(BLE_APP_BATT)

#if (BLE_APP_USER)
    APPM_SVC_USER,
#endif //(BLE_APP_USER)
    APPM_SVC_LIST_STOP,
};

/*
 * LOCAL VARIABLES DEFINITIONS
 ****************************************************************************************
 */

/// Application Task Descriptor
static const struct ke_task_desc TASK_DESC_APP = {NULL, &appm_default_handler,
           appm_state, APPM_STATE_MAX, APP_IDX_MAX
};

/// List of functions used to create the database
static const appm_add_svc_func_t appm_add_svc_func_list[APPM_SVC_LIST_STOP] =
{

#if (BLE_APP_USER)
    (appm_add_svc_func_t)app_user_add_users,
#endif //(BLE_APP_USER)

};

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Application Environment Structure
struct app_env_tag app_env;

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */
void app_default_feature_init(void)
{
    //wait to fill in the features
    app_env.max_mtu = 251;

}

void appm_init()
{

    // Reset the application manager environment
    memset(&app_env, 0, sizeof(app_env));
    // Create APP task
    ke_task_create(TASK_APP, &TASK_DESC_APP);
    // Initialize Task state
    ke_state_set(TASK_APP, APPM_INIT);

    app_default_feature_init();
    interface_sys.user_feature_init();

    // user Module init
#if (BLE_APP_USER)
    // Health Thermometer Module
    app_user_init();
#endif //(BLE_APP_USER)
}

bool appm_add_svc(void)
{
    // Indicate if more services need to be added in the database
    bool more_svc = false;
    // Check if another should be added in the database
    if (app_env.next_svc != APPM_SVC_LIST_STOP)
    {
       // ble_log(BLE_DEBUG,"",app_env.next_svc)
        ASSERT_INFO(appm_add_svc_func_list[app_env.next_svc] != NULL, app_env.next_svc, 1);

        // Call the function used to add the required service
        appm_add_svc_func_list[app_env.next_svc]();
        // Select following service to add
        app_env.next_svc++;
        more_svc = true;
    }
    return more_svc;
}

void appm_disconnect(void)
{
    struct gapc_disconnect_cmd *cmd = KE_MSG_ALLOC(GAPC_DISCONNECT_CMD,KE_BUILD_ID(TASK_GAPC, app_env.conidx), TASK_APP,gapc_disconnect_cmd);
    cmd->operation = GAPC_DISCONNECT;
    cmd->reason    = CO_ERROR_REMOTE_USER_TERM_CON;
    ke_msg_send(cmd); // Send the message
}

void appm_start_advertising(void)
{
    if (ke_state_get(TASK_APP) == APPM_READY)
    {
        // Prepare the GAPM_START_ADVERTISE_CMD message
        struct gapm_start_advertise_cmd *cmd = KE_MSG_ALLOC(GAPM_START_ADVERTISE_CMD,TASK_GAPM, TASK_APP,gapm_start_advertise_cmd);
        cmd->op.code        = app_env.adv_para.adv_type;
        cmd->op.addr_src    = GAPM_STATIC_ADDR;             // app_env.adv_para.addr_type_own;  //public static addr private  static addr
        cmd->channel_map    = app_env.adv_para.channel_map; // BTstack_data.user_config.adv_para.channel_map;//
        cmd->intv_min       = app_env.adv_para.adv_int_min;
        cmd->intv_max       = app_env.adv_para.adv_int_max;
        cmd->info.host.mode = app_env.adv_para.discover_mode;

        //ASSERT_ERR( app_env.adv_data_len > (GAP_ADV_DATA_LEN-3) );

        memcpy(cmd->info.host.adv_data, app_env.adv_data_buf, app_env.adv_data_len);
        cmd->info.host.adv_data_len  =  app_env.adv_data_len;



        //ASSERT_ERR(app_env.adv_data_len > GAP_SCAN_RSP_DATA_LEN);

        memcpy(cmd->info.host.scan_rsp_data, app_env.scan_rsp_data_buf, app_env.scan_rsp_data_len);
        cmd->info.host.scan_rsp_data_len  =  app_env.scan_rsp_data_len;

        // Send the message
        ke_msg_send(cmd);
        ke_state_set(TASK_APP, APPM_ADVERTISING);
        if (g_pcallback) {
            g_pcallback(BT_EVENT_DISCONNECTD, NULL, 0, 0);
        }
        g_connnet_start = 0;
    }

}

void appm_stop_advertising(void)
{
    if (ke_state_get(TASK_APP) == APPM_ADVERTISING)
    {
        // Go in ready state
        ke_state_set(TASK_APP, APPM_READY);
        // Prepare the GAPM_CANCEL_CMD message
        struct gapm_cancel_cmd *cmd = KE_MSG_ALLOC(GAPM_CANCEL_CMD,TASK_GAPM, TASK_APP,gapm_cancel_cmd);
        cmd->operation = GAPM_CANCEL;
        // Send the message
        ke_msg_send(cmd);
    }
}

void appm_set_mtu(void)
{
    // Prepare the GAPC_PARAM_UPDATE_CMD message
    struct gattc_exc_mtu_cmd *cmd = KE_MSG_ALLOC(GATTC_EXC_MTU_CMD,KE_BUILD_ID(TASK_GATTC, app_env.conidx), TASK_APP,gattc_exc_mtu_cmd);
    cmd->operation = GATTC_MTU_EXCH;
    cmd->seq_num = 0;
    // Send the message
    ke_msg_send(cmd);
}

void BT_set_mtu(uint16_t mtu)
{
    app_env.max_mtu = mtu;

    gapm_set_max_mtu(mtu);

    appm_set_mtu();
}

void appm_update_param(struct gapc_conn_param *conn_param)
{
    // Prepare the GAPC_PARAM_UPDATE_CMD message

    struct gapc_param_update_cmd *cmd = KE_MSG_ALLOC(GAPC_PARAM_UPDATE_CMD,KE_BUILD_ID(TASK_GAPC, app_env.conidx), TASK_APP,gapc_param_update_cmd);
    cmd->operation  = GAPC_UPDATE_PARAMS;
    cmd->intv_min   = conn_param->intv_min;
    cmd->intv_max   = conn_param->intv_max;
    cmd->latency    = conn_param->latency;
    cmd->time_out   = conn_param->time_out;
    // not used by a slave device
    cmd->ce_len_min = 0xFFFF;
    cmd->ce_len_max = 0xFFFF;
    // Send the message
    ke_msg_send(cmd);
}

uint8_t appm_get_dev_name(uint8_t *name)
{
    // copy name to provided pointer
    memcpy(name, app_env.dev_name, app_env.dev_name_len);
    // return name length
    return app_env.dev_name_len;
}

#endif //(BLE_APP_PRESENT)


