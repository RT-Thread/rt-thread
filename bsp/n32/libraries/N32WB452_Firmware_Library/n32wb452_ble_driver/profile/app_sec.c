/**
 ****************************************************************************************
 *
 * @file app_sec.c
 *
 * @brief Application Security Entry Point
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

#include "rwip_config.h"
#include <stdbool.h>
//#include "ble_arch.h"

#if (BLE_APP_SEC)

#include <string.h>
#include "co_math.h"
#include "gapc_task.h"      // GAP Controller Task API Definition
#include "gapm_task.h"      // GAPM task API definition
#include "gap.h"            // GAP Definition
#include "gapc.h"           // GAPC Definition
#include "gapm.h"
#include "prf_types.h"

#include "app.h"            // Application API Definition
#include "app_sec.h"        // Application Security API Definition
#include "app_task.h"       // Application Manager API Definition
#include "interface.h"

#if (NVDS_SUPPORT)
#include "nvds.h"           // NVDS API Definitions
#endif //(NVDS_SUPPORT)
/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Application Security Environment Structure
struct app_sec_env_tag app_sec_env;



//struct current_bond_info_t current_bond_info;
/*
 * GLOBAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */

static int app_sec_msg_dflt_handler(ke_msg_id_t const msgid,
                                        void*param,
                                    ke_task_id_t const dest_id,
                                    ke_task_id_t const src_id)
{
    return (KE_MSG_CONSUMED);
}

void app_sec_init()
{
    /*------------------------------------------------------
     * RETRIEVE BOND STATUS
     *------------------------------------------------------*/
    #if (NVDS_SUPPORT)
    uint8_t length = NVDS_LEN_PERIPH_BONDED;
    // Get bond status from NVDS
    if (nvds_get(NVDS_TAG_PERIPH_BONDED, &length, (uint8_t *)&app_sec_env.bonded) != NVDS_OK)
    {
        // If read value is invalid, set status to not bonded
        app_sec_env.bonded = false;
    }
/************************************************************************************************************/
    uint8_t length1 = NVDS_LEN_DEVICE_NUM;

    if (nvds_get(NVDS_TAG_DEVICE_NUM, &length1, &app_sec_env.device_num) != NVDS_OK)
    {
        // If read value is invalid, set device number to 0
        app_sec_env.device_num = 0;
    }
/************************************************************************************************************/



    #endif //(NVDS_SUPPORT)
}


void app_sec_send_security_req(uint8_t conidx)
{

      //start to security cmd
      struct gapc_security_cmd *cmd = KE_MSG_ALLOC(GAPC_SECURITY_CMD,
                 KE_BUILD_ID(TASK_GAPC, app_env.conidx), TASK_APP, gapc_security_cmd);// Security request
      cmd->operation = GAPC_SECURITY_REQ;

      cmd->auth = GAP_AUTH_REQ_NO_MITM_BOND;

      //iocap will select MITM or not

      // Send the message
      ke_msg_send(cmd);
}


/**
 ****************************************************************************************
 * @brief Handles reception of bond request command
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapc_bond_req_ind_handler(ke_msg_id_t const msgid,struct gapc_bond_req_ind const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    struct gapc_bond_cfm *cfm = KE_MSG_ALLOC(GAPC_BOND_CFM,src_id, TASK_APP,gapc_bond_cfm);
    switch (param->request)
    {
        case (GAPC_PAIRING_REQ):
        {
            cfm->request = GAPC_PAIRING_RSP;
            cfm->accept = true;

            // OOB information
            cfm->data.pairing_feat.oob            = GAP_OOB_AUTH_DATA_NOT_PRESENT;
            // Encryption key size
            cfm->data.pairing_feat.key_size       = KEY_LEN;
            // IO capabilities
            cfm->data.pairing_feat.iocap          = app_env.iocap;
            // Authentication requirements
            cfm->data.pairing_feat.auth           = GAP_AUTH_REQ_NO_MITM_BOND; //GAP_AUTH_REQ_NO_MITM_BOND;

            cfm->data.pairing_feat.ikey_dist      = GAP_KDIST_NONE;
            //Responder key distribution
            cfm->data.pairing_feat.rkey_dist      = GAP_KDIST_ENCKEY;
            //Security requirements
            cfm->data.pairing_feat.sec_req        = GAP_NO_SEC;

        }
        break;

        case(GAPC_LTK_EXCH):
        {

            uint8_t counter;

            cfm->data.ltk.ediv = (uint16_t)( (co_rand_word() + app_env.loc_irk[1]*256 + app_env.loc_irk[0]) );

            for(counter = 0; counter < RAND_NB_LEN; counter++)
            {
                cfm->data.ltk.randnb.nb[counter] = (uint8_t)((co_rand_word() + app_env.loc_irk[counter])  );
            }

            for(counter = 0; counter < KEY_LEN; counter++)
            {
                cfm->data.ltk.ltk.key[counter]    = (uint8_t)((co_rand_word() + app_env.loc_irk[counter]) );
            }

            cfm->request = GAPC_LTK_EXCH;

            cfm->accept = true;

#if (NVDS_SUPPORT)

            switch (app_sec_env.device_num % 5)
            {
                case 0:
                    if (nvds_put(NVDS_TAG_LTK, NVDS_LEN_LTK, (uint8_t *)&cfm->data.ltk) != NVDS_OK)
                    {
                        ASSERT_ERR(0);
                    }
                    break;
                case 1:
                    if (nvds_put(NVDS_TAG_LTK1, NVDS_LEN_LTK1, (uint8_t *)&cfm->data.ltk) != NVDS_OK)
                    {
                        ASSERT_ERR(0);
                    }
                    break;
                case 2:
                    if (nvds_put(NVDS_TAG_LTK2, NVDS_LEN_LTK2, (uint8_t *)&cfm->data.ltk) != NVDS_OK)
                    {
                        ASSERT_ERR(0);
                    }
                    break;
                case 3:
                    if (nvds_put(NVDS_TAG_LTK3, NVDS_LEN_LTK3, (uint8_t *)&cfm->data.ltk) != NVDS_OK)
                    {
                        ASSERT_ERR(0);
                    }
                    break;

                case 4:
                    if (nvds_put(NVDS_TAG_LTK4, NVDS_LEN_LTK4, (uint8_t *)&cfm->data.ltk) != NVDS_OK)
                    {
                        ASSERT_ERR(0);
                    }
                    break;
                default:
                    break;
            }
            app_sec_env.device_num = (app_sec_env.device_num + 1) % 5;

            uint8_t device_num[1]={0};
            uint8_t length = NVDS_LEN_DEVICE_NUM;
            nvds_get(NVDS_TAG_DEVICE_NUM, &length, device_num);

            if (device_num[0]<app_sec_env.device_num)
            {
                if (nvds_put(NVDS_TAG_DEVICE_NUM, NVDS_LEN_DEVICE_NUM,&app_sec_env.device_num) != NVDS_OK)
                {
                    // An error has occurred during access to the NVDS
                    ASSERT_ERR(0);
                }
            }
#endif // #if (NVDS_SUPPORT)
        }
        break;


        case (GAPC_IRK_EXCH):
        {
            #if (NVDS_SUPPORT)
            uint8_t addr_len = BD_ADDR_LEN;
            #endif //(NVDS_SUPPORT)

            cfm->request = GAPC_IRK_EXCH;
            cfm->accept  = true;

            // Load IRK
            memcpy(cfm->data.irk.irk.key, app_env.loc_irk, KEY_LEN);
            // load device address
            cfm->data.irk.addr.addr_type = ADDR_PUBLIC;
            #if (NVDS_SUPPORT)
            if (nvds_get(NVDS_TAG_BD_ADDRESS, &addr_len, cfm->data.irk.addr.addr.addr) != NVDS_OK)
            #endif //(NVDS_SUPPORT)
            {
                ASSERT_ERR(0);
            }
        }
        break;


        case (GAPC_TK_EXCH):
        {
            if (param->data.tk_type == GAP_TK_DISPLAY)
            {
                cfm->request = GAPC_TK_EXCH;
                cfm->accept = true;

                memset(cfm->data.tk.key, 0, KEY_LEN);
                cfm->data.tk.key[0] = (uint8_t)((app_env.pin_code & 0x000000FF) >>  0);
                cfm->data.tk.key[1] = (uint8_t)((app_env.pin_code & 0x0000FF00) >>  8);
                cfm->data.tk.key[2] = (uint8_t)((app_env.pin_code & 0x00FF0000) >> 16);
                cfm->data.tk.key[3] = (uint8_t)((app_env.pin_code & 0xFF000000) >> 24);

            }
            else
            {
                ASSERT_ERR(0);
            }

        }
        break;

        default:
        {
            ASSERT_ERR(0);
        }
        break;
    }

    // Send the message
   // interface_env.delay_ms(5);
    ke_msg_send(cfm);

    return (KE_MSG_CONSUMED);
}



/**
 ****************************************************************************************
 * @brief Handles reception of bond indication
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapc_bond_ind_handler(ke_msg_id_t const msgid,struct gapc_bond_ind const *param,ke_task_id_t const dest_id,ke_task_id_t const src_id)
{
    switch (param->info)
    {
        case (GAPC_PAIRING_SUCCEED):
        {
            // Update the bonding status in the environment
            app_sec_env.bonded = true;
            ke_state_set(TASK_APP, APPM_ENCRYPTED);//lizhk add
            // Update the bonding status in the environment
            #if (PLF_NVDS)
//          if (nvds_put(NVDS_TAG_PERIPH_BONDED, NVDS_LEN_PERIPH_BONDED,(uint8_t *)&app_sec_env.bonded) != NVDS_OK)
//            {
//                // An error has occurred during access to the NVDS
//                ASSERT_ERR(0);
//            }
//           gapc_save_bond_info();

            #endif //(PLF_NVDS)

        }
        break;

        case (GAPC_REPEATED_ATTEMPT):
        {
            appm_disconnect();
        }
        break;

        case (GAPC_IRK_EXCH):
        {
        }
        break;

        case (GAPC_PAIRING_FAILED):
        {
            app_sec_send_security_req(0);
        }
        break;

        // In Secure Connections we get BOND_IND with SMPC calculated LTK
        case (GAPC_LTK_EXCH) :
        {

        }
        break;

        case (GAPC_CSRK_EXCH) :
        {

        }
        break;

        default:
        {
            ASSERT_ERR(0);
        }
        break;
    }

    return (KE_MSG_CONSUMED);
}
extern void BT_handle(void);
static int gapc_encrypt_req_ind_handler(ke_msg_id_t const msgid,
                                        struct gapc_encrypt_req_ind const *param,
                                        ke_task_id_t const dest_id,
                                        ke_task_id_t const src_id)
{
    #if (NVDS_SUPPORT)
    // LTK value
    struct gapc_ltk ltk;
    // Length
    uint8_t length = NVDS_LEN_LTK;

    #endif // #if (NVDS_SUPPORT)

    // Prepare the GAPC_ENCRYPT_CFM message
    struct gapc_encrypt_cfm *cfm = KE_MSG_ALLOC(GAPC_ENCRYPT_CFM,src_id, TASK_APP,gapc_encrypt_cfm);
    cfm->found    = false;
    //移出未使用变量 app_sec_env.bonded


    #if (NVDS_SUPPORT)
    // Retrieve the required informations from NVD
    uint8_t err = 1;

    uint8_t device_num[1]={0};
    uint8_t length1 = NVDS_LEN_DEVICE_NUM;
    nvds_get(NVDS_TAG_DEVICE_NUM, &length1, device_num);

    for(uint8_t i=0;i<device_num[0];i++)
    {
        switch (i+1)
            {
        case 1:
         err = nvds_get(NVDS_TAG_LTK, &length, (uint8_t *)&ltk);
        break;

        case 2:
         err = nvds_get(NVDS_TAG_LTK1, &length, (uint8_t *)&ltk);
        break;

        case 3:
         err = nvds_get(NVDS_TAG_LTK2, &length, (uint8_t *)&ltk);
        break;

        case 4:
         err = nvds_get(NVDS_TAG_LTK3, &length, (uint8_t *)&ltk);
        break;

        case 5:
         err = nvds_get(NVDS_TAG_LTK4, &length, (uint8_t *)&ltk);
        break;

        default:
            break;

        }

        if (err == NVDS_OK)
        {
            // Check if the provided EDIV and Rand Nb values match with the stored values

            if ((param->ediv == ltk.ediv) &&!memcmp(&param->rand_nb.nb[0], &ltk.randnb.nb[0], sizeof(struct rand_nb)))
            {
                cfm->found    = true;
                cfm->key_size = 16;
                memcpy(&cfm->ltk, &ltk.ltk, sizeof(struct gap_sec_key));
                app_env.con_device_num = i;
                ke_state_set(TASK_APP,APPM_ENCRYPTED);

                break;
            }

        }
    }
    uint8_t found_flag = cfm->found;
    #endif // #if (NVDS_SUPPORT)
    ke_msg_send(cfm);

    if (found_flag == false)
    {
        uint8_t schedule_num = 10;
        while (schedule_num--)
        {
            BT_handle();
        }
        eif_delay_ms(200);
        app_sec_send_security_req(0);
    }


    return (KE_MSG_CONSUMED);
}


static int gapc_encrypt_ind_handler(ke_msg_id_t const msgid,
                                    struct gapc_encrypt_ind const *param,
                                    ke_task_id_t const dest_id,
                                    ke_task_id_t const src_id)
{
    ke_state_set(TASK_APP, APPM_ENCRYPTED);
    return (KE_MSG_CONSUMED);
}



 /*
  * LOCAL VARIABLE DEFINITIONS
  ****************************************************************************************
  */

/// Default State handlers definition
const struct ke_msg_handler app_sec_msg_handler_list[] =
{
    // Note: first message is latest message checked by kernel so default is put on top.
    {KE_MSG_DEFAULT_HANDLER,  (ke_msg_func_t)app_sec_msg_dflt_handler},

    {GAPC_BOND_REQ_IND,       (ke_msg_func_t)gapc_bond_req_ind_handler},
    {GAPC_BOND_IND,           (ke_msg_func_t)gapc_bond_ind_handler},

    {GAPC_ENCRYPT_REQ_IND,    (ke_msg_func_t)gapc_encrypt_req_ind_handler},
    {GAPC_ENCRYPT_IND,        (ke_msg_func_t)gapc_encrypt_ind_handler},
};

const struct ke_state_handler app_sec_table_handler ={&app_sec_msg_handler_list[0], (sizeof(app_sec_msg_handler_list) / sizeof(struct ke_msg_handler))};

#endif //(BLE_APP_SEC)



/// @} APP
