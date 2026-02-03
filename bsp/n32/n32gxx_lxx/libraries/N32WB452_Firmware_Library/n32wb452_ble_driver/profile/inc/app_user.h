/**
 ****************************************************************************************
 *
 * @file app_user.h
 *
 * @brief user-defined service entry point
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */
#ifndef APP_USER_H_
#define APP_USER_H_



/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"     // SW configuration

#if (BLE_APP_USER)

#include <stdint.h>          // Standard Integer Definition
#include "ke_task.h"
#include "att.h"

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
extern struct app_env_tag app_env;

/// health thermometer application environment structure
struct app_user_rev_tag
{
   //todo
   uint16_t length;

 //  uint8_t data[ATT_VALUE_LEN_MAX/*__ARRAY_EMPTY*/];

    uint16_t receive_length;

    uint8_t *receive_data;

    bool  receive_flag;

    bool receive_header;

    uint16_t receive_current_length;
};

/*
 * GLOBAL VARIABLES DECLARATIONS
 ****************************************************************************************
 */

/// Health Thermomter Application environment
//extern struct app_user_env_tag app_user_env;

/// Table of message handlers
extern struct app_user_rev_tag app_user_env;

extern const struct ke_state_handler app_user_table_handler;

/*
 * FUNCTIONS DECLARATION
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 *
 * Health Thermometer Application Functions
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Initialize Health Thermometer Application
 ****************************************************************************************
 */
void app_user_init(void);

/**
 ****************************************************************************************
 * @brief Add a Health Thermometer instance in the DB
 ****************************************************************************************
 */
void app_user_add_users(void);

/**
 ****************************************************************************************
 * @brief Stop the interval measurement timer if used
 ****************************************************************************************
 */
void app_stop_timer (void);

/**
 ****************************************************************************************
 * @brief Enable the health thermometer profile
 ****************************************************************************************
 */
//void app_user_enable_prf(uint8_t conidx);

void app_user_data_send(void);

void app_user_mtu_temp_send(uint16_t mtu);

void app_user_updata_temp_send(uint8_t status);//,uint16_t intv_min, uint16_t intv_max, uint16_t latancy, uint16_t timesout);

void app_user_data_rec(uint16_t param_length , uint8_t * param_payload);


uint8_t app_user_data_notify(uint16_t param_length , uint8_t * param_payload, uint8_t att_idx);


#endif //(BLE_APP_USER)

/// @} APP

#endif // APP_HT_H_

