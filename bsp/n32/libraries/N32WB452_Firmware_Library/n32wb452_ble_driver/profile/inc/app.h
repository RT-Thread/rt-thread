/**
 ****************************************************************************************
 *
 * @file app.h
 *
 * @brief Application entry point
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

#ifndef APP_H_
#define APP_H_

/**
 ****************************************************************************************
 * @addtogroup APP
 * @ingroup RICOW
 *
 * @brief Application entry point.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"     // SW configuration

#if (BLE_APP_PRESENT)

#include <stdint.h>          // Standard Integer Definition
#include <co_bt.h>           // Common BT Definitions
#include "ble_arch.h"
#include "gapc.h"            // GAPC Definitions
#include "gap.h"

#if (NVDS_SUPPORT)
#include "nvds.h"
#endif // (NVDS_SUPPORT)

/*
 * DEFINES
 ****************************************************************************************
 */
/// Maximal length of the Device Name value
#define APP_DEVICE_NAME_MAX_LEN      (16)

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

#if (NVDS_SUPPORT)
#ifdef default
/// List of Application NVDS TAG identifiers
enum app_nvds_tag
{
    /// BLE Application Advertising data
    NVDS_TAG_APP_BLE_ADV_DATA           = 0x0B,
    NVDS_LEN_APP_BLE_ADV_DATA           = 32,

    /// BLE Application Scan response data
    NVDS_TAG_APP_BLE_SCAN_RESP_DATA     = 0x0C,
    NVDS_LEN_APP_BLE_SCAN_RESP_DATA     = 32,

    /// Mouse Sample Rate
    NVDS_TAG_MOUSE_SAMPLE_RATE          = 0x38,
    NVDS_LEN_MOUSE_SAMPLE_RATE          = 1,
    /// Peripheral Bonded
    NVDS_TAG_PERIPH_BONDED              = 0x39,
    NVDS_LEN_PERIPH_BONDED              = 1,
    /// Mouse NTF Cfg
    NVDS_TAG_MOUSE_NTF_CFG              = 0x3A,
    NVDS_LEN_MOUSE_NTF_CFG              = 2,
    /// Mouse Timeout value
    NVDS_TAG_MOUSE_TIMEOUT              = 0x3B,
    NVDS_LEN_MOUSE_TIMEOUT              = 2,
    /// Peer Device BD Address
    NVDS_TAG_PEER_BD_ADDRESS            = 0x3C,
    NVDS_LEN_PEER_BD_ADDRESS            = 7,
    /// Mouse Energy Safe
    NVDS_TAG_MOUSE_ENERGY_SAFE          = 0x3D,
    NVDS_LEN_MOUSE_SAFE_ENERGY          = 2,
    /// EDIV (2bytes), RAND NB (8bytes),  LTK (16 bytes), Key Size (1 byte)
    NVDS_TAG_LTK                        = 0x3E,
    NVDS_LEN_LTK                        = 28,
    /// PAIRING
    NVDS_TAG_PAIRING                    = 0x3F,
    NVDS_LEN_PAIRING                    = 54,
};
#else
enum app_nvds_tag
{
    /// BLE Application Advertising data
    NVDS_TAG_APP_BLE_ADV_DATA           = 0x0B,
    NVDS_LEN_APP_BLE_ADV_DATA           = 32,

    /// BLE Application Scan response data
    NVDS_TAG_APP_BLE_SCAN_RESP_DATA     = 0x0C,
    NVDS_LEN_APP_BLE_SCAN_RESP_DATA     = 32,

    /// Peripheral Bonded
    NVDS_TAG_PERIPH_BONDED              = 0x39,
    NVDS_LEN_PERIPH_BONDED              = 1,

    /// Peer Device BD Address
    NVDS_TAG_PEER_BD_ADDRESS            = 0x3A,
    NVDS_LEN_PEER_BD_ADDRESS            = 7,

    NVDS_TAG_PEER_BD_ADDRESS1            = 0x3B,
    NVDS_LEN_PEER_BD_ADDRESS1            = 7,

    NVDS_TAG_PEER_BD_ADDRESS2            = 0x3C,
    NVDS_LEN_PEER_BD_ADDRESS2            = 7,

    NVDS_TAG_PEER_BD_ADDRESS3            = 0x3D,
    NVDS_LEN_PEER_BD_ADDRESS3            = 7,

    NVDS_TAG_PEER_BD_ADDRESS4            = 0x3E,
    NVDS_LEN_PEER_BD_ADDRESS4            = 7,

    NVDS_TAG_DEVICE_NUM                  = 0x3F,
    NVDS_LEN_DEVICE_NUM                  = 1,

    /// EDIV (2bytes), RAND NB (8bytes),  LTK (16 bytes), Key Size (1 byte)
    NVDS_TAG_LTK                        = 0x40,
    NVDS_LEN_LTK                        = 28,

    NVDS_TAG_LTK1                        = 0x41,
    NVDS_LEN_LTK1                        = 28,

    NVDS_TAG_LTK2                        = 0x42,
    NVDS_LEN_LTK2                        = 28,

    NVDS_TAG_LTK3                        = 0x43,
    NVDS_LEN_LTK3                        = 28,

    NVDS_TAG_LTK4                        = 0x44,
    NVDS_LEN_LTK4                        = 28,

};

#endif
enum app_loc_nvds_tag
{
    /// Audio mode 0 task
    NVDS_TAG_AM0_FIRST                  = NVDS_TAG_APP_SPECIFIC_FIRST,

    NVDS_TAG_AM0_LAST                   = NVDS_TAG_APP_SPECIFIC_FIRST+16,

    /// Local device Identity resolving key
    NVDS_TAG_LOC_IRK,
    /// Peer device Resolving identity key (+identity address)
    NVDS_TAG_PEER_IRK,
    /// size of local identity resolving key
    NVDS_LEN_LOC_IRK                    = KEY_LEN,
    /// size of Peer device identity resolving key (+identity address)
    NVDS_LEN_PEER_IRK                   = sizeof(struct gapc_irk),
};
#endif // (NVDS_SUPPORT)

/************************************************************************************************/
//add by bottle.mao

#define BD_ADDR_LEN 6

typedef uint8_t bd_addr[BD_ADDR_LEN];






//add by bottle.mao
struct devicc_adv_parameter
{
    //advert_data
    uint16_t adv_int_min;

    uint16_t adv_int_max;

    uint8_t adv_type;

    uint8_t addr_type_own;

    uint8_t channel_map;

    uint8_t adv_filter_policy;

    uint8_t discover_mode;
};






#define RX_DAT_BUF_SIZE 320

struct RX_BUF_S
{
    uint16_t RxCurrentLen;
    uint16_t RxTotalLen;
        // received data value
#ifndef N32WB452_BT_API
    uint8_t RxBuf[RX_DAT_BUF_SIZE];
#endif
        // received data length
};

/************************************************************************************************/

/// Application environment structure
struct app_env_tag
{


    /// send data timesout
    uint32_t timesout;

    /// Connection handle
    uint16_t conhdl;
      /// Connection interval
    uint16_t con_interval;
    uint16_t con_intv_min;
    uint16_t con_intv_max;
    uint16_t con_latency;
    uint16_t con_time_out;
    /// Advertising parameter
    struct devicc_adv_parameter adv_para;

    /// MTU
    uint16_t max_mtu;
    /// Received data information
    struct RX_BUF_S rx_data;


    /// Connection Index
    uint8_t  conidx;

    /// Last initialized profile
    uint8_t next_svc;

    /// Bonding status
    bool bonded;

    /// Device Name length
    uint8_t dev_name_len;
    /// Device Name
    uint8_t dev_name[APP_DEVICE_NAME_MAX_LEN];


    /// Counter used to generate IRK
    uint8_t rand_cnt;
    /// Local device IRK
    uint8_t loc_irk[KEY_LEN];

/*******************************************************************************/
   /// Connection security enable
    bool security_enable;

/// receivce data flag
    uint8_t rec_flag;

//*******************************************************************************/
/// Pairing mode
    uint8_t pairing_mode;
/// sec iocap
    uint8_t iocap;
/// Pin code required
    uint32_t pin_code;


/// RSSI value
    int8_t rssi;

/// White List size
    uint8_t wlst_size;

/// current connect device number
    uint8_t con_device_num;

/// local device bda
    struct bd_addr bdaddr;
/// addr type
    uint8_t bdaddr_type;

/// adv data buf
    uint8_t adv_data_buf[31];
/// adv data buf len
    uint8_t adv_data_len;

///  scan response data buf
    uint8_t scan_rsp_data_buf[31];

///  scan response data buf len
    uint8_t scan_rsp_data_len;

/// battery level
    uint8_t  batt_lvl;



/*******************************************************************************/
};



/// Application environment
extern struct app_env_tag app_env;



/**
 ****************************************************************************************
 * @brief Initialize the BLE demo application.
 ****************************************************************************************
 */
void appm_init(void);

/**
 ****************************************************************************************
 * @brief Add a required service in the database
 ****************************************************************************************
 */
bool appm_add_svc(void);

/**
 ****************************************************************************************
 * @brief Put the device in general discoverable and connectable mode
 ****************************************************************************************
 */
void appm_start_advertising(void);

/**
 ****************************************************************************************
 * @brief Put the device in non discoverable and non connectable mode
 ****************************************************************************************
 */
void appm_stop_advertising(void);

/**
 ****************************************************************************************
 * @brief Send to request to update the connection parameters
 ****************************************************************************************
 */
void appm_update_param(struct gapc_conn_param *conn_param);

void appm_set_mtu(void);

/**
 ****************************************************************************************
 * @brief Send a disconnection request
 ****************************************************************************************
 */
void appm_disconnect(void);

/**
 ****************************************************************************************
 * @brief Retrieve device name
 *
 * @param[out] device name
 *
 * @return name length
 ****************************************************************************************
 */
uint8_t appm_get_dev_name(uint8_t* name);


/**
 ****************************************************************************************
 * @brief Return if the device is currently bonded
 ****************************************************************************************
 */
bool app_sec_get_bond_status(void);


#endif

#endif
