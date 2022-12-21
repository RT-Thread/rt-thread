/**
 ****************************************************************************************
 *
 * @file rwble_hl_config.h
 *
 * @brief Configuration of the BLE protocol stack (max number of supported connections,
 * type of partitioning, etc.)
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef RWBLE_HL_CONFIG_H_
#define RWBLE_HL_CONFIG_H_

/**
 ****************************************************************************************
 * @addtogroup ROOT
 * @{
 * @name BLE stack configuration
 * @{
 ****************************************************************************************
 */

#include "rwble_hl_error.h"

/******************************************************************************************/
/* -------------------------   BLE PARTITIONING      -------------------------------------*/
/******************************************************************************************/


/******************************************************************************************/
/* --------------------------   INTERFACES        ----------------------------------------*/
/******************************************************************************************/


#if BLE_APP_PRESENT
#define APP_MAIN_TASK       TASK_APP
#else // BLE_APP_PRESENT
#define APP_MAIN_TASK       TASK_AHI
#endif // BLE_APP_PRESENT

// Host Controller Interface (Host side)
#define BLEHL_HCIH_ITF            HCIH_ITF

/******************************************************************************************/
/* --------------------------   COEX SETUP        ----------------------------------------*/
/******************************************************************************************/

///WLAN coex
#define BLEHL_WLAN_COEX          RW_WLAN_COEX
///WLAN test mode
#define BLEHL_WLAN_COEX_TEST     RW_WLAN_COEX_TEST

/******************************************************************************************/
/* --------------------------   HOST MODULES      ----------------------------------------*/
/******************************************************************************************/

#define BLE_GAPM                    1
#if (BLE_CENTRAL || BLE_PERIPHERAL)
#define BLE_GAPC                    1
#define BLE_GAPC_HEAP_ENV_SIZE      (sizeof(struct gapc_env_tag)  + KE_HEAP_MEM_RESERVED)
#else //(BLE_CENTRAL || BLE_PERIPHERAL)
#define BLE_GAPC                    0
#define BLE_GAPC_HEAP_ENV_SIZE      0
#endif //(BLE_CENTRAL || BLE_PERIPHERAL)

#if (BLE_CENTRAL || BLE_PERIPHERAL)
#define BLE_L2CM                    1
#define BLE_L2CC                    1
#define BLE_ATTM                    1
#define BLE_GATTM                   1
#define BLE_GATTC                   1
#define BLE_GATTC_HEAP_ENV_SIZE     (sizeof(struct gattc_env_tag)  + KE_HEAP_MEM_RESERVED)
#define BLE_L2CC_HEAP_ENV_SIZE      (sizeof(struct l2cc_env_tag)   + KE_HEAP_MEM_RESERVED)
#else //(BLE_CENTRAL || BLE_PERIPHERAL)
#define BLE_L2CM                    0
#define BLE_L2CC                    0
#define BLE_ATTC                    0
#define BLE_ATTS                    0
#define BLE_ATTM                    0
#define BLE_GATTM                   0
#define BLE_GATTC                   0
#define BLE_GATTC_HEAP_ENV_SIZE     0
#define BLE_L2CC_HEAP_ENV_SIZE      0
#endif //(BLE_CENTRAL || BLE_PERIPHERAL)

#define BLE_SMPM                    1
#if (BLE_CENTRAL || BLE_PERIPHERAL)
#define BLE_SMPC                    1
#else //(BLE_CENTRAL || BLE_PERIPHERAL)
#define BLE_SMPC                    0
#endif //(BLE_CENTRAL || BLE_PERIPHERAL)


/******************************************************************************************/
/* --------------------------   ATT DB            ----------------------------------------*/
/******************************************************************************************/

//ATT DB,Testing and Qualification related flags
#if (BLE_CENTRAL || BLE_PERIPHERAL)
    /// Support of External DB Management
    #if defined(CFG_EXT_DB)
        #define BLE_EXT_ATT_DB         1
    #else
        #define BLE_EXT_ATT_DB         0
    #endif // defined(CFG_EXT_DB)
#else
    #define BLE_EXT_ATT_DB         0
#endif // (BLE_CENTRAL || BLE_PERIPHERAL)
/******************************************************************************************/
/* --------------------------   PROFILES          ----------------------------------------*/
/******************************************************************************************/
#ifdef CFG_PRF
#define BLE_PROFILES      (1)
/// Number of Profile tasks managed by GAP manager.
#define BLE_NB_PROFILES   (CFG_NB_PRF)
#include "rwprf_config.h"
#else
#define BLE_PROFILES      (0)
#define BLE_NB_PROFILES   (0)
#endif // CFG_PRF


#ifndef   BLE_ATTS
#if (BLE_CENTRAL || BLE_PERIPHERAL || defined(CFG_ATTS))
#define BLE_ATTS                    1
#else
#define BLE_ATTS                    0
#endif // (BLE_CENTRAL || BLE_PERIPHERAL || defined(CFG_ATTS))
#endif // BLE_ATTS


#ifndef   BLE_ATTC
#if (BLE_CENTRAL || defined(CFG_ATTC))
#define BLE_ATTC                    1
#else
#define BLE_ATTC                    0
#endif // (BLE_CENTRAL || defined(CFG_ATTC))
#endif // BLE_ATTC

#ifndef   BLE_LECB
#if (BLE_CENTRAL || BLE_PERIPHERAL)
#define BLE_LECB                    0//1
#else
#define BLE_LECB                    0
#endif // (BLE_CENTRAL || defined(CFG_ATTC))
#endif // BLE_ATTC


/// Attribute Server
#if (BLE_ATTS)
#define BLE_ATTS                    1
#else
#define BLE_ATTS                    0
#endif //(BLE_ATTS)


/// Size of the heap
#if (BLE_CENTRAL || BLE_PERIPHERAL)
    /// some heap must be reserved for attribute database
    #if (BLE_ATTS || BLE_ATTC)
        #define BLEHL_HEAP_DB_SIZE                 512//(1024)//  (3072) by bottle
    #else
        #define BLEHL_HEAP_DB_SIZE                 (0)
    #endif /* (BLE_ATTS || BLE_ATTC) */

    #define BLEHL_HEAP_MSG_SIZE                    (256 + 256 * BLE_CONNECTION_MAX)
#else
    #define BLEHL_HEAP_MSG_SIZE                    (256)
    #define BLEHL_HEAP_DB_SIZE                     (0)
#endif /* #if (BLE_CENTRAL || BLE_PERIPHERAL) */




/// Number of BLE HL tasks
#define BLEHL_TASK_SIZE       BLE_HOST_TASK_SIZE + BLE_PRF_TASK_SIZE

/// Size of environment variable needed on BLE Host Stack for one link
#define BLEHL_HEAP_ENV_SIZE ( BLE_GAPC_HEAP_ENV_SIZE       +  \
                              BLE_GATTC_HEAP_ENV_SIZE      +  \
                              BLE_L2CC_HEAP_ENV_SIZE)







/*
 * DEFINES - Mandatory for BLE Host Layers
 ****************************************************************************************
 */
/// Maximum time to remain advertising when in the Limited
/// Discover able mode: TGAP(lim_adv_timeout)
/// required value: 180s: (18000 for ke timer)
#define GAP_TMR_LIM_ADV_TIMEOUT                             0x4650

/// Minimum time to perform scanning when performing
/// the General Discovery procedure: TGAP(gen_disc_scan_min)
/// recommended value: 10.24s: (1024 for ke timer)
#define GAP_TMR_GEN_DISC_SCAN                               0x0300

/// Minimum time to perform scanning when performing the
/// Limited Discovery procedure: TGAP(lim_disc_scan_min)
/// recommended value: 10.24s: (1024 for ke timer)
#define GAP_TMR_LIM_DISC_SCAN                               0x0300

/// Minimum time interval between private address change
/// TGAP(private_addr_int)
/// recommended value: 15 minutes; 0x01F4 for PTS
/// 0x3A98 is 150 seconds; 0xEA60 is 10 minutes
#define GAP_TMR_PRIV_ADDR_INT                               0x3A98


/// Timer used in connection parameter update procedure
/// TGAP(conn_param_timeout)
/// recommended value: 30 s: (3000 for ke timer) / *10ms
#define GAP_TMR_CONN_PARAM_TIMEOUT                          0x0BB8

/// Timer used in LE credit based connection procedure
/// TGAP(lecb_conn_timeout)
/// recommended value: 30 s: (3000 for ke timer)
#define GAP_TMR_LECB_CONN_TIMEOUT                           0x0BB8

/// Timer used in LE credit based disconnection procedure
/// TGAP(lecb_disconn_timeout)
/// recommended value: 30 s: (3000 for ke timer)
#define GAP_TMR_LECB_DISCONN_TIMEOUT                        0x0BB8

/// Maximal authorized MTU value
#define GAP_MAX_LE_MTU                                     (517)

/// Maximum GAP device name size
#define GAP_MAX_NAME_SIZE                                  (0x20)

/// Maximum Transmission Unit
#define ATT_DEFAULT_MTU                                 (23)
/// 30 seconds transaction timer
#define ATT_TRANS_RTX                                  (0x0BB8)
/// Acceptable encryption key size - strict access
#define ATT_SEC_ENC_KEY_SIZE                            (0x10)

/// Maximum attribute value length
#define ATT_MAX_VALUE                                   (GAP_MAX_LE_MTU)


/// @} BLE stack configuration
/// @} ROOT

#endif // RWBLE_HL_CONFIG_H_
