/**
 ****************************************************************************************
 *
 * @file rwble_config.h
 *
 * @brief Configuration of the BLE protocol stack (max number of supported connections,
 * type of partitioning, etc.)
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

#ifndef RWBLE_CONFIG_H_
#define RWBLE_CONFIG_H_

/**
 ****************************************************************************************
 * @addtogroup ROOT
 * @{
 * @name BLE stack configuration
 * @{
 ****************************************************************************************
 */

#include "rwip_config.h"


/******************************************************************************************/
/* -------------------------   COEXISTENCE SETUP      ------------------------------------*/
/******************************************************************************************/

///WLAN coex
#define RW_BLE_WLAN_COEX        RW_WLAN_COEX
///WLAN test mode
#define RW_BLE_WLAN_COEX_TEST   RW_WLAN_COEX_TEST

/// MWS Coexistence
#define RW_BLE_MWS_COEX         RW_MWS_COEX
///WLAN test mode
#define RW_BLE_MWS_COEX_TEST    RW_MWS_COEX_TEST

///To let the HW using the default values set in the registers
#define RW_BLE_PTI_PRIO_AUTO    15



/// PTI configuration index
enum rwble_pti_config_idx
{
    BLE_PTI_CON_IDX,
    BLE_PTI_ADV_IDX,
    BLE_PTI_SCAN_IDX,
    BLE_PTI_INIT_IDX,
    BLE_PTI_IDX_MAX
};


/******************************************************************************************/
/* --------------------------   DEBUG SETUP       ----------------------------------------*/
/******************************************************************************************/

/// Flag indicating if tester emulator is available or not
#if defined(CFG_BLE_TESTER)
/// Flag indicating if tester emulator is available or not
#define BLE_TESTER              1
#else // defined (CFG_BLE_TESTER)
#define BLE_TESTER              0
#endif // defined (CFG_BLE_TESTER)

/// Flag indicating if debug mode is activated or not
#define BLE_DEBUG               RW_DEBUG
#define BLE_SWDIAG              RW_SWDIAG

/// Flag indicating if Read/Write memory commands are supported or not
#define BLE_DEBUG_MEM           RW_DEBUG_MEM

/// Flag indicating if Flash debug commands are supported or not
#define BLE_DEBUG_FLASH         RW_DEBUG_FLASH

/// Flag indicating if NVDS feature is supported or not
#define BLE_DEBUG_NVDS          RW_DEBUG_NVDS

/// Flag indicating if CPU stack profiling commands are supported or not
#define BLE_DEBUG_STACK_PROF    RW_DEBUG_STACK_PROF

/******************************************************************************************/
/* -------------------------   BLE SETUP      --------------------------------------------*/
/******************************************************************************************/

/// Exchange memory presence
#define BLE_EM_PRESENT              (BLE_EMB_PRESENT)

#define BLE_TEST_MODE_SUPPORT       (1)

/// Number of devices in the white list
#define BLE_WHITELIST_MAX           (BLE_CONNECTION_MAX + 2)

/// Number of devices in the Resolution Address List
/// This have to be tuned according to the core frequency. Worst case is having in scan mode
/// all IRK and valid in resolving list and device receive a Direct Adv Report that contains
/// RPAs for InitA and AdvA
#define BLE_RESOL_ADDR_LIST_MAX     (3)

/// Connection handle max
#define BLE_MAX_CONHDL              (BLE_CONNECTION_MAX)

/// Number of devices capacity for the scan filtering
#if (BLE_CENTRAL || BLE_OBSERVER)
#define BLE_DUPLICATE_FILTER_MAX    (10)
#endif //(BLE_CENTRAL || BLE_OBSERVER)

/** Size of the heap
 * - For KE messages: (N+1) x 256
 * - For LLC environment: N x 80 Bytes
 * - For LLD events/intervals: (2N+1) x (80 + 16)
 */
#if (BLE_CENTRAL || BLE_PERIPHERAL)
    #define BLE_HEAP_MSG_SIZE               (256 * (BLE_CONNECTION_MAX+1) + 80 * (BLE_CONNECTION_MAX) + 96 * (2*BLE_CONNECTION_MAX+1))
    /// Size required to allocate environment variable for one link
    #define BLE_HEAP_ENV_SIZE               (sizeof(struct llc_env_tag) + 4)
#else
    #define BLE_HEAP_MSG_SIZE               (256)
    /// Size required to allocate environment variable for one link
    #define BLE_HEAP_ENV_SIZE               (4)
#endif /* #if (BLE_CENTRAL || BLE_PERIPHERAL) */


/******************************************************************************************/
/* --------------------------   RADIO SETUP       ----------------------------------------*/
/******************************************************************************************/
/// Class of device
#define RF_CLASS1                            0

/******************************************************************************************/
/* --------------------------   REGISTER SETUP       --------------------------------------*/
/******************************************************************************************/

#define RW_BLE_CUST1_INST                    0

/******************************************************************************************/
/* --------------------------   SCHEDULING SETUP       --------------------------------------*/
/******************************************************************************************/

/// EA programming latency for only 1 activity
#define RWBLE_PROG_LATENCY_DFT         (2)
/// EA asap latency
#define RWBLE_ASAP_LATENCY             (2)
/// Instant value mask
#define RWBLE_INSTANT_MASK         (0x0000FFFF)

/******************************************************************************************/
/* -----------------------   SUPPORTED HCI COMMANDS       --------------------------------*/
/******************************************************************************************/

//byte0
#define BLE_CMDS_BYTE0      BLE_DISC_CMD
//byte2
#define BLE_CMDS_BYTE2      BLE_RD_REM_VERS_CMD
//byte5
#define BLE_CMDS_BYTE5      (BLE_SET_EVT_MSK_CMD | BLE_RESET_CMD)
//byte10
#define BLE_CMDS_BYTE10     (BLE_HL_NB_CMP_PKT_CMD | BLE_RD_TX_PWR_CMD\
                            |BLE_HL_BUF_SIZE_CMD | BLE_SET_CTRL_TO_HL_FCTRL_CMD)
//byte14
#define BLE_CMDS_BYTE14     (BLE_RD_LOC_VERS_CMD | BLE_RD_LOC_SUP_FEAT_CMD\
                            |BLE_RD_BUF_SIZE_CMD)
//byte15
#define BLE_CMDS_BYTE15     (BLE_RD_BD_ADDR_CMD | BLE_RD_RSSI_CMD)
#if !(BLE_QUALIF)
//byte22
#define BLE_CMDS_BYTE22     (BLE_SET_EVT_MSK_PG2_CMD)
#else
//byte22
#define BLE_CMDS_BYTE22     0
#endif
//byte25
#define BLE_CMDS_BYTE25     (BLE_LE_SET_EVT_MSK_CMD | BLE_LE_RD_BUF_SIZE_CMD\
                            |BLE_LE_RD_LOC_SUP_FEAT_CMD | BLE_LE_SET_RAND_ADDR_CMD\
                            |BLE_LE_SET_ADV_PARAM_CMD | BLE_LE_RD_ADV_TX_PWR_CMD\
                            |BLE_LE_SET_ADV_DATA_CMD)
//byte26
#define BLE_CMDS_BYTE26     (BLE_LE_SET_SC_RSP_DATA_CMD | BLE_LE_SET_ADV_EN_CMD\
                            |BLE_LE_SET_SC_PARAM_CMD | BLE_LE_SET_SC_EN_CMD\
                            |BLE_LE_CREAT_CNX_CMD | BLE_LE_CREAT_CNX_CNL_CMD\
                            |BLE_LE_RD_WL_SIZE_CMD | BLE_LE_CLEAR_WL_CMD)
//byte27
#define BLE_CMDS_BYTE27     (BLE_LE_ADD_DEV_WL_CMD | BLE_LE_REM_DEV_WL_CMD\
                            |BLE_LE_CNX_UPDATE_CMD | BLE_LE_SET_HL_CH_CLASS_CMD\
                            |BLE_LE_RD_CH_MAP_CMD | BLE_LE_RD_REM_USED_FEAT_CMD\
                            |BLE_LE_ENCRYPT_CMD | BLE_LE_RAND_CMD)
//byte28
#define BLE_CMDS_BYTE28     (BLE_LE_START_ENC_CMD | BLE_LE_LTK_REQ_RPLY_CMD\
                            |BLE_LE_LTK_REQ_NEG_RPLY_CMD | BLE_LE_RD_SUPP_STATES_CMD\
                            |BLE_LE_RX_TEST_CMD | BLE_LE_TX_TEST_CMD\
                            |BLE_LE_STOP_TEST_CMD)
#if !(BLE_QUALIF)
//byte32
#define BLE_CMDS_BYTE32     (BLE_RD_AUTH_PAYL_TO_CMD | BLE_WR_AUTH_PAYL_TO_CMD)
//byte33
#define BLE_CMDS_BYTE33     (BLE_LE_REM_CON_PARA_REQ_RPLY_CMD | BLE_LE_REM_CON_PARA_REQ_NEG_RPLY_CMD\
                            | BLE_LE_SET_DATA_LEN_CMD | BLE_LE_RD_SUGGTED_DFT_DATA_LEN_CMD)
//byte34
#define BLE_CMDS_BYTE34     ( BLE_LE_WR_SUGGTED_DFT_DATA_LEN_CMD    \
                             | BLE_LE_RD_LOC_P256_PUB_KEY_CMD       \
                             | BLE_LE_GEN_DH_KEY_CMD                \
                             | BLE_LE_ADD_DEV_TO_RESOLV_LIST_CMD    \
                             | BLE_LE_REM_DEV_FROM_RESOLV_LIST_CMD  \
                             | BLE_LE_CLEAR_RESOLV_LIST_CMD         \
                             | BLE_LE_RD_RESOLV_LIST_SIZE_CMD       \
                             | BLE_LE_RD_PEER_RESOLV_ADDR_CMD)
//byte35
#define BLE_CMDS_BYTE35     (  BLE_LE_RD_LOCAL_RESOLV_ADDR_CMD    \
                             | BLE_LE_SET_ADDR_RESOL_CMD          \
                             | BLE_LE_SET_RESOLV_PRIV_ADDR_TO_CMD \
                             | BLE_LE_RD_MAX_DATA_LEN_CMD)
#else
//byte32
#define BLE_CMDS_BYTE32     0
//byte33
#define BLE_CMDS_BYTE33     0
//byte34
#define BLE_CMDS_BYTE34     0
//byte35
#define BLE_CMDS_BYTE35     0
#endif // BLE_QUALIF

/******************************************************************************************/
/* -------   SUPPORTED VALUES FOR DATA LENGTH EXTENSION COMMANDS   -----------------------*/
/******************************************************************************************/
#define BLE_TESTMODE_MAX_OCTETS     (255)
//8 bits preamble
#define BLE_PREAMBLE_TIME         (8)
//32 bits Access Code
#define BLE_ACCESS_CODE_BIT_SIZE  (32)
//16 bits header
#define BLE_HEADER_BIT_SIZE       (16)
//32bits MIC
#define BLE_MIC_BIT_SIZE          (32)
//24 bits CRC
#define BLE_CRC_BIT_SIZE          (24)
//8 bits preamble
#define BLE_PREAMBLE_SIZE         (1)
//4 bytes Access Code
#define BLE_ACCESS_CODE_SIZE      (4)
//2 bytes header
#define BLE_HEADER_SIZE           (2)
//4 bytes MIC
#define BLE_MIC_SIZE              (4)
//3 bytes CRC
#define BLE_CRC_SIZE              (3)

#define BLE_COMMON_BIT_SIZE       (BLE_ACCESS_CODE_BIT_SIZE + BLE_HEADER_BIT_SIZE + BLE_CRC_BIT_SIZE)
/******************************************************************************************/
/* --------------------------   DLE SETUP       ----------------------------------------*/
/******************************************************************************************/



#define BLE_MIN_OCTETS  (27)
#define BLE_MIN_TIME    (328)
#if !(BLE_QUALIF)
#define BLE_MAX_OCTETS  (251)
#define BLE_MAX_TIME    (2120)
#else
#define BLE_MAX_OCTETS  (27)
#define BLE_MAX_TIME    (328)
#endif
// Max number of descriptor to be linked under IRQ context to avoid CPU overload
#define BLE_NB_MAX_CHUNKS   (10)
/******************************************************************************************/
/* --------------------------   PROCEDURE STARTUP ----------------------------------------*/
/******************************************************************************************/

#define BLE_DLE_PROCEDURE   (1 << 0)
#define BLE_PHY_PROCEDURE   (1 << 1)

/// @} BLE stack configuration
/// @} ROOT

#endif // RWBLE_CONFIG_H_
