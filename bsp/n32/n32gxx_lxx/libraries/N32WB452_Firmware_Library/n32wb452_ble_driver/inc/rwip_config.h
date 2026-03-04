/**
 ****************************************************************************************
 *
 * @file rwip_config.h
 *
 * @brief Configuration of the RW IP SW
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

#ifndef RWIP_CONFIG_H_
#define RWIP_CONFIG_H_
/**
 ****************************************************************************************
 * @addtogroup ROOT
 * @{
 *
 *  Information about RW SW IP options and flags
 *
 *        BT_DUAL_MODE             BT/BLE Dual Mode
 *        BT_STD_MODE              BT Only
 *        BLE_STD_MODE             BLE Only
 *
 *        BT_EMB_PRESENT           BT controller exists
 *        BLE_EMB_PRESENT          BLE controller exists
 *        BLE_HOST_PRESENT         BLE host exists
 *
 * @name RW Stack Configuration
 * @{
 ****************************************************************************************
 */
#define CFG_HOST
#define CFG_BLE
#define CFG_AHITLx
#define CFG_HCITL
#define CFG_APP
#define CFG_NVDS
#define CFG_DBGx
#define CFG_ALLROLESx  //CFG_BROADCASTER//CFG_PERIPHERAL
#define CFG_PERIPHERAL
#define CFG_ATTS
#define CFG_ATTC

#define CFG_SLEEP
#define CFG_UART_ENABLE


#define CFG_APP_SEC
#define CFG_APP_USER
//#define CFG_PRF_BASS
//#define CFG_APP_BATT
#define CFG_PRF_HTPTx
/*支持的最大连接数*/
#define CFG_CON            1


#define CFG_APP_HTx
#define CFG_PRF
#define CFG_NB_PRF        1   //1



#if defined(CFG_DBG)
#define PLF_DEBUG          1
#else //CFG_DBG
#define PLF_DEBUG          0
#endif //CFG_DBG

/*
 * DEFINES
 ****************************************************************************************
 */

/******************************************************************************************/
/* -------------------------   QUALIFICATION FLAG     ------------------------------------*/
/******************************************************************************************/
//Downgrade the stack to version 4.0   /*harry modify: if only support bt4.0, let it be 1*/
#define BLE_QUALIF              0


/******************************************************************************************/
/* --------------------------   GENERAL SETUP       --------------------------------------*/
/******************************************************************************************/

/// Flag indicating if stack is compiled in dual or single mode
#if defined(CFG_BT)
    #define BLE_STD_MODE                     0
    #if defined(CFG_BLE)
        #define BT_DUAL_MODE                 1
        #define BT_STD_MODE                  0
    #else // CFG_BLE
        #define BT_DUAL_MODE                 0
        #define BT_STD_MODE                  1
    #endif // CFG_BLE
#elif defined(CFG_BLE)
    #define BT_DUAL_MODE                     0
    #define BT_STD_MODE                      0
    #define BLE_STD_MODE                     1
#endif // CFG_BT

/******************************************************************************************/
/* -------------------------   STACK PARTITIONING      -----------------------------------*/
/******************************************************************************************/

#if (BT_DUAL_MODE)
    #define BT_EMB_PRESENT              1
    #define BLE_EMB_PRESENT             1
    #define HCI_PRESENT                 1
    #define BLE_HOST_PRESENT            0
    #define BLE_APP_PRESENT             0
#elif (BT_STD_MODE)
    #define BT_EMB_PRESENT              1
    #define BLE_EMB_PRESENT             0
    #define HCI_PRESENT                 1
    #define BLE_HOST_PRESENT            0
    #define BLE_APP_PRESENT             0
#elif (BLE_STD_MODE)
    #define BT_EMB_PRESENT              0
    #define HCI_PRESENT                 1
    #if defined(CFG_EMB)
        #define BLE_EMB_PRESENT         1
    #else
        #define BLE_EMB_PRESENT         0
    #endif //CFG_EMB
    #if defined(CFG_HOST)
        #define BLE_HOST_PRESENT        1
    #else
        #define BLE_HOST_PRESENT        0
    #endif //CFG_HOST
    #if defined(CFG_APP)
        #define BLE_APP_PRESENT         1
    #else
        #define BLE_APP_PRESENT         0
    #endif //CFG_APP
#endif // BT_DUAL_MODE / BT_STD_MODE / BLE_STD_MODE

#define EA_PRESENT                      (BT_EMB_PRESENT || BLE_EMB_PRESENT)

/******************************************************************************************/
/* -------------------------   INTERFACES DEFINITIONS      -------------------------------*/
/******************************************************************************************/

/// Application Host Interface
#if defined(CFG_AHITL)
#define AHI_TL_SUPPORT       1
#else // defined(CFG_AHITL)
#define AHI_TL_SUPPORT       0
#endif // defined(CFG_AHITL)


/// Host Controller Interface Support (defines if HCI parser is present or not)
#if defined(CFG_HCITL)
#define HCI_TL_SUPPORT      1
#else //defined(CFG_HCITL)
#define HCI_TL_SUPPORT      0
#endif //defined(CFG_HCITL)


#if BLE_HOST_PRESENT
#if BLE_EMB_PRESENT
#define H4TL_SUPPORT      (AHI_TL_SUPPORT)
#else // !BLE_EMB_PRESENT
#define H4TL_SUPPORT      ((AHI_TL_SUPPORT) + (HCI_TL_SUPPORT))
#endif // BLE_EMB_PRESENT
#else // !BLE_HOST_PRESENT
#define H4TL_SUPPORT      (HCI_TL_SUPPORT)
#endif // BLE_HOST_PRESENT

/// TCI LMP trace support
#define TCI_LMP_ENABLED                             0

/******************************************************************************************/
/* --------------------------   BLE COMMON DEFINITIONS      ------------------------------*/
/******************************************************************************************/
/// Kernel Heap memory sized reserved for allocate dynamically connection environment
#define KE_HEAP_MEM_RESERVED        (4)

#if defined(CFG_BLE)
/// Application role definitions
#define BLE_BROADCASTER   (defined(CFG_BROADCASTER) || defined(CFG_ALLROLES))
#define BLE_OBSERVER      (defined(CFG_OBSERVER)    || defined(CFG_ALLROLES))
#define BLE_PERIPHERAL    (defined(CFG_PERIPHERAL)  || defined(CFG_ALLROLES))
#define BLE_CENTRAL       (defined(CFG_CENTRAL)     || defined(CFG_ALLROLES))

#if (!BLE_BROADCASTER) && (!BLE_OBSERVER) && (!BLE_PERIPHERAL) && (!BLE_CENTRAL)
    #error "No application role defined"
#endif /* #if (!BLE_BROADCASTER) && (!BLE_OBSERVER) && (!BLE_PERIPHERAL) && (!BLE_CENTRAL) */


/// Maximum number of simultaneous connections
#if (BLE_CENTRAL)
    #define BLE_CONNECTION_MAX      (CFG_CON)
#elif (BLE_PERIPHERAL)
    #define BLE_CONNECTION_MAX      (1)
#else
    #define BLE_CONNECTION_MAX      (0)
#endif /* #if (BLE_CENTRAL) */

/// Maximum number of audio connections
#if defined(CFG_AUDIO)
#if (BLE_CENTRAL || BLE_PERIPHERAL)
#define BLE_AUDIO      (1)
#define BLE_AUDIO_CONNECT_MAX    (CFG_AUDIO_CON)
#else
#define BLE_AUDIO      (0)
#endif /*(BLE_CENTRAL || BLE_PERIPHERAL)*/
#else
#define BLE_AUDIO      (0)
#endif /*defined(CFG_AUDIO)*/

/// Number of TX data buffer
#if ((BLE_CONNECTION_MAX == 1) || (BLE_CONNECTION_MAX == 0))
#if (BLE_CENTRAL || BLE_PERIPHERAL)
#define BLE_TX_BUFF_DATA            (3)
#else
#define BLE_TX_BUFF_DATA            (0)
#endif //(BLE_CENTRAL || BLE_PERIPHERAL)
#else
#define BLE_TX_BUFF_DATA            (BLE_CONNECTION_MAX) // Worst case (one way 251 bytes every 7.5ms)
#endif //((BLE_CONNECTION_MAX == 1) || (BLE_CONNECTION_MAX == 0))

#if (BLE_CENTRAL || BLE_PERIPHERAL)
/// Number of TX advertising buffer
#define BLE_TX_BUFF_ADV             (3) // Worst case (1 for CONNECT_REQ, 1 for ADV_DATA and 1 for SCAN_RESP_DATA)
/// Number of TX control buffer
#define BLE_TX_BUFF_CNTL            (BLE_CONNECTION_MAX) // Worst case (1 dedicated packet by link)
#else
/// Margin used for LL fragmentation (DLE feature)
//#define BLE_TX_DESC_MARGING_DLE     (0)
#if (BLE_BROADCASTER)
/// Number of TX advertising descriptors
#define BLE_TX_BUFF_ADV             (2)
/// Number of TX control descriptors
#define BLE_TX_BUFF_CNTL            (0)
#else
/// Number of TX advertising descriptors
#define BLE_TX_BUFF_ADV             (1)
/// Number of TX control descriptors
#define BLE_TX_BUFF_CNTL            (0)
#endif // BLE_BROADCASTER
#endif //(BLE_CENTRAL || BLE_PERIPHERAL)

/// Number of elements in the TX Descriptor pool
// Dedicated for DATA
// Worst case (1 packets (251 bytes) fragmented into 27 byte =  10)
#define BLE_TX_DESC_DATA            ((BLE_TX_BUFF_DATA) * 10)
// Dedicated for CONTROL
#define BLE_TX_DESC_CNTL            (BLE_TX_BUFF_CNTL)
// Dedicated for ADVERTISING
#define BLE_TX_DESC_ADV             (BLE_TX_BUFF_ADV)

/// Number of TX Buffers
#define BLE_TX_BUFFER_CNT           (BLE_TX_BUFF_DATA)

/// Total number of elements in the TX Descriptor pool
#define BLE_TX_DESC_CNT             (BLE_TX_DESC_CNTL + BLE_TX_DESC_ADV + BLE_TX_DESC_DATA)


/// Number of receive buffers in the RX ring. This number defines the interrupt
/// rate during a connection event. An interrupt is asserted every BLE_RX_BUFFER_CNT/2
/// reception. This number has an impact on the size of the exchange memory. This number
/// may have to be increased when CPU is very slow to free the received data, in order not
/// to overflow the RX ring of buffers.

#if (BLE_CENTRAL || BLE_PERIPHERAL)
    /// Number of RX Descriptors
    #define BLE_RX_DESC_CNT             (8)
#elif (BLE_BROADCASTER)
    #define BLE_RX_DESC_CNT             (1)
#else
    #define BLE_RX_DESC_CNT             (4)
#endif //(BLE_CENTRAL || BLE_PERIPHERAL)
/// Number of RX Buffers
#define BLE_RX_BUFFER_CNT               (BLE_RX_DESC_CNT)

/// Max advertising reports before sending the info to the host
#define BLE_ADV_REPORTS_MAX             1


/// Define Number of AUDIO TX/RX buffers per voice channel
#if (BLE_AUDIO)
    #if defined(CFG_AUDIO_AOAHI)
        // 3 buffers per connection using audio over AHI TL
        #define BLE_NB_INPUT_BUFF_PER_VC          (3)
        #define BLE_NB_OUTPUT_BUFF_PER_VC         (3)
    #else // defined(CFG_AUDIO_AOAHI)
        // 2 buffers if a codec is available
        #define BLE_NB_INPUT_BUFF_PER_VC          (2)
        #define BLE_NB_OUTPUT_BUFF_PER_VC         (2)
    #endif // defined(CFG_AUDIO_AOAHI)
    // add one more buffer for fake reception and fake transmit
    #define BLE_TX_AUDIO_BUFFER_CNT   ((BLE_AUDIO_CONNECT_MAX * BLE_NB_INPUT_BUFF_PER_VC)  + 1)
    #define BLE_RX_AUDIO_BUFFER_CNT   ((BLE_AUDIO_CONNECT_MAX * BLE_NB_OUTPUT_BUFF_PER_VC) + 1)
#endif // (BLE_AUDIO)
#endif //defined(CFG_BLE)


/******************************************************************************************/
/* --------------------------   DISPLAY SETUP        -------------------------------------*/
/******************************************************************************************/

/// Display controller enable/disable
#if defined(CFG_DISPLAY)
#define DISPLAY_SUPPORT      1
#else
#define DISPLAY_SUPPORT      0
#endif //CFG_DISPLAY


/******************************************************************************************/
/* --------------------------      RTC SETUP         -------------------------------------*/
/******************************************************************************************/

/// RTC enable/disable
#if defined(CFG_RTC)
#define RTC_SUPPORT      1
#else
#define RTC_SUPPORT      0
#endif //CFG_DISPLAY

/******************************************************************************************/
/* --------------------------      PS2 SETUP         -------------------------------------*/
/******************************************************************************************/

/// PS2 enable/disable
#if defined(CFG_PS2)
#define PS2_SUPPORT      1
#else
#define PS2_SUPPORT      0
#endif //CFG_PS2


/******************************************************************************************/
/* -------------------------   DEEP SLEEP SETUP      -------------------------------------*/
/******************************************************************************************/

/// DEEP SLEEP enable
#if defined(CFG_SLEEP) && (BLE_EMB_PRESENT || BT_EMB_PRESENT)
    #define DEEP_SLEEP                              1
#else
    #define DEEP_SLEEP                              0
#endif /* CFG_SLEEP */

/// Use 32K Hz Clock if set to 1 else 32,768k is used
#define HZ32000                                     0

/// Time to wake-up Radio Module (in us)
#define SLEEP_RM_WAKEUP_DELAY                       625
/// Time for stabilization of the high frequency oscillator following a sleep-timer expiry (in us)
#define SLEEP_OSC_NORMAL_WAKEUP_DELAY               5000
/// Time for stabilization of the high frequency oscillator following an external wake-up request (in us)
#define SLEEP_OSC_EXT_WAKEUP_DELAY                  5000


/******************************************************************************************/
/* -------------------------    PROCESSOR SETUP      -------------------------------------*/
/******************************************************************************************/

/// 8 BIT processor
#define PROC_8BITS                        0

/******************************************************************************************/
/* --------------------------   RADIO SETUP       ----------------------------------------*/
/******************************************************************************************/

/// Power control features
#define RF_TXPWR                            1
/// Class of device
#define RF_CLASS1                           0

/******************************************************************************************/
/* -------------------------   COEXISTENCE SETUP      ------------------------------------*/
/******************************************************************************************/

/// WLAN Coexistence
#if 1/*defined(CFG_WLAN_COEX)*/
    #define RW_WLAN_COEX                 1
    #define RW_WLAN_COEX_TEST            (defined(CFG_WLAN_COEX_TEST))
#else
    #define RW_WLAN_COEX                 0
    #define RW_WLAN_COEX_TEST            0
#endif // defined(CFG_WLAN_COEX)

/// MWS Coexistence
#if defined(CFG_MWS_COEX)
    #define RW_MWS_COEX                 1
    #define RW_MWS_COEX_TEST            (defined(CFG_MWS_COEX_TEST))
#else
    #define RW_MWS_COEX                 0
    #define RW_MWS_COEX_TEST            0
#endif // defined(CFG_MWS_COEX)

/******************************************************************************************/
/* -------------------------   DM ARBITRATION SETUP      ---------------------------------*/
/******************************************************************************************/

#if BT_DUAL_MODE
/**
 * Dual mode arbitration margin (in us)
 *
 * BREDRMARGIN/BLEMARGIN corresponding to a timing value that allows the RF to power-down properly before any other
 * activity. This is radio dependent.
 */
#define DM_ARB_MARGIN      40
#endif //BT_DUAL_MODE

/******************************************************************************************/
/* -------------------------   CHANNEL ASSESSMENT SETUP      -----------------------------*/
/******************************************************************************************/

/// Channel Assessment
#if defined(CFG_BLE)
#if (defined(CFG_CHNL_ASSESS) && BLE_CENTRAL)
    #define BLE_CHNL_ASSESS        (1)
#else
    #define BLE_CHNL_ASSESS        (0)
#endif //(defined(CFG_CHNL_ASSESS) && BLE_CENTRAL)
#endif //defined(CFG_BLE)

/******************************************************************************************/
/* --------------------   SECURE CONNECTIONS SETUP  --------------------------------------*/
/******************************************************************************************/
#if defined(CFG_SEC_CON)
    #define SECURE_CONNECTIONS        (1)
    #if defined(CFG_ECC_16_BITS_ALGO)
        #define ECC_MULT_ALGO_TYPE        (16)
    #else // !defined(CFG_ECC_16_BITS_ALGO)
        #define ECC_MULT_ALGO_TYPE        (32)
    #endif // defined(CFG_ECC_16_BITS_ALGO)
    #if defined(CFG_CRYPTO_UT)
        #define CRYPTO_UT                 (1)
    #else //defined(CFG_CRYPTO_UT)
        #define CRYPTO_UT                 (0)
    #endif //defined(CFG_CRYPTO_UT)
#else // !defined(CFG_SEC_CON)
    #define SECURE_CONNECTIONS        (0)
    #define CRYPTO_UT                 (0)
#endif // defined(CFG_SEC_CON)

/******************************************************************************************/
/* ----------------------------     AUDIO  SETUP      ------------------------------------*/
/******************************************************************************************/

/// Flag indicating if audio is available or not
#if defined(CFG_HW_AUDIO)
#define HW_AUDIO             1
#else // defined (CFG_BLE_AUDIO)
#define HW_AUDIO             0
#endif // defined (CFG_BLE_AUDIO)

/******************************************************************************************/
/* --------------------------   DEBUG SETUP       ----------------------------------------*/
/******************************************************************************************/

/// Flag indicating if debug mode is activated or not
#if defined(CFG_DBG)
    #define RW_DEBUG                        ((BLE_EMB_PRESENT) || (BT_EMB_PRESENT) || (BLE_HOST_PRESENT))
#if (BLE_EMB_PRESENT || BT_EMB_PRESENT)
    #define RW_SWDIAG                       1
#else
    #define RW_SWDIAG                       0
#endif
    #define KE_PROFILING                    1
#else
    #define RW_DEBUG                        0
    #define RW_SWDIAG                       0
    #define KE_PROFILING                    0
#endif /* CFG_DBG */

/// Flag indicating if Read/Write memory commands are supported or not
#if defined(CFG_DBG_MEM)
    #define RW_DEBUG_MEM               1
#else //CFG_DBG_MEM
    #define RW_DEBUG_MEM               0
#endif //CFG_DBG_MEM

/// Flag indicating if Flash debug commands are supported or not
#if defined(CFG_DBG_FLASH)
    #define RW_DEBUG_FLASH                  1
#else //CFG_DBG_FLASH
    #define RW_DEBUG_FLASH                  0
#endif //CFG_DBG_FLASH

/// Flag indicating if NVDS feature is supported or not
#if defined(CFG_DBG_NVDS)
    #define RW_DEBUG_NVDS                   1
#else //CFG_DBG_NVDS
    #define RW_DEBUG_NVDS                   0
#endif //CFG_DBG_NVDS

/// Flag indicating if CPU stack profiling commands are supported or not
#if defined(CFG_DBG_STACK_PROF)
    #define RW_DEBUG_STACK_PROF             1
#else
    #define RW_DEBUG_STACK_PROF             0
#endif // defined (CFG_DBG_STACK_PROF)

/// Modem back to back setup
#define MODEM2MODEM                          0
/// Special clock testing
#define CLK_WRAPPING                         0

/******************************************************************************************/
/* --------------------------      NVDS SETUP       --------------------------------------*/
/******************************************************************************************/

/// Flag indicating if NVDS feature is supported or not
#if defined(CFG_NVDS)
    #define NVDS_SUPPORT                    1
#else //CFG_DBG_NVDS
    #define NVDS_SUPPORT                    0
#endif //CFG_DBG_NVDS

/******************************************************************************************/
/* --------------------------      MISC SETUP       --------------------------------------*/
/******************************************************************************************/
/// Manufacturer: RivieraWaves SAS
#define RW_COMP_ID                           0x0060

/// Bluetooth technologies version
#define RW_BT40_VERSION                      (6)
#define RW_BT41_VERSION                      (7)
#define RW_BT42_VERSION                      (8)

/******************************************************************************************/
/* -------------------------   BT / BLE / BLE HL CONFIG    -------------------------------*/
/******************************************************************************************/

#if (BT_EMB_PRESENT)
#include "rwbt_config.h"    // bt stack configuration
#endif //BT_EMB_PRESENT

#if (BLE_EMB_PRESENT) || (BLE_HOST_PRESENT)
#include "rwble_config.h"   // ble stack configuration
#endif //BLE_EMB_PRESENT

#if (BLE_HOST_PRESENT)
#include "rwble_hl_config.h"  // ble Host stack configuration
#endif //BLE_HOST_PRESENT

#if defined(CFG_AUDIO_AM0)
#include "rwam0_config.h"     // Audio Mode 0 configuration
#endif // defined(CFG_AUDIO_AM0)

#if defined(CFG_APP)
#include "rwapp_config.h"     // Audio Mode 0 configuration
#endif // defined(CFG_APP)



/******************************************************************************************/
/* -------------------------   KERNEL SETUP          -------------------------------------*/
/******************************************************************************************/

/// Flag indicating Kernel is supported
#define KE_SUPPORT  (BLE_EMB_PRESENT || BT_EMB_PRESENT || BLE_HOST_PRESENT || BLE_APP_PRESENT)


/// Event types definition
enum KE_EVENT_TYPE
{
    #if DISPLAY_SUPPORT
    KE_EVENT_DISPLAY         ,
    #endif //DISPLAY_SUPPORT

    #if RTC_SUPPORT
    KE_EVENT_RTC_1S_TICK     ,
    #endif //RTC_SUPPORT

    #ifdef CFG_AUDIO_RSA
    KE_EVENT_RSA_SIGN,
    #endif // CFG_AUDIO_RSA

    #if SECURE_CONNECTIONS
    KE_EVENT_ECC_MULTIPLICATION,
    #endif // SECURE_CONNECTIONS

    #if BLE_EMB_PRESENT
    KE_EVENT_BLE_CRYPT       ,
    #endif //BLE_EMB_PRESENT

    KE_EVENT_KE_MESSAGE      ,  // 0
    KE_EVENT_KE_TIMER        ,  // 1

    #if (AHI_TL_SUPPORT)
    KE_EVENT_AHI_TX_DONE     ,
    #endif //(AHI_TL_SUPPORT)


    #if H4TL_SUPPORT   //  2
    KE_EVENT_H4TL_TX         ,
    #if (BLE_EMB_PRESENT || BT_EMB_PRESENT)
    KE_EVENT_H4TL_CMD_HDR_RX ,
    KE_EVENT_H4TL_CMD_PLD_RX ,
    #endif //(BLE_EMB_PRESENT || BT_EMB_PRESENT)
    #endif //H4TL_SUPPORT

    #if (BLE_HOST_PRESENT)
    #if (BLE_L2CC)
    KE_EVENT_L2CAP_TX        ,// 3
    #endif //(BLE_L2CC)
    #endif// (BLE_HOST_PRESENT)

    #if BT_EMB_PRESENT
    KE_EVENT_BT_PSCAN_PROC   ,
    #endif //BT_EMB_PRESENT

    #if BLE_EMB_PRESENT
    KE_EVENT_BLE_EVT_DEFER   ,
    KE_EVENT_BLE_EVT_DELETE  ,
    #endif //BLE_EMB_PRESENT

    #if defined(CFG_AUDIO_AOAHI)
    KE_EVENT_BLE_AUDIO_DEFER ,
    #endif // defined(CFG_AUDIO_AOAHI)

    KE_EVENT_MAX             ,
};

/// Tasks types definition
enum KE_TASK_TYPE
{
#if (BT_EMB_PRESENT)   //0
    // BT Controller Tasks44
    TASK_LM,
    TASK_LC,
    TASK_LB,
    TASK_LD,
    TASK_HCI,
#endif // (BT_EMB_PRESENT)

#if (BLE_EMB_PRESENT)         //0
    // Link Layer Tasks
    TASK_LLM ,
    TASK_LLC ,
    TASK_LLD ,
#endif // (BLE_EMB_PRESENT)

#if ((BLE_EMB_PRESENT) || (BT_EMB_PRESENT))      //0
    TASK_DBG,
#endif // ((BLE_EMB_PRESENT) || (BT_EMB_PRESENT))

#if (DISPLAY_SUPPORT)             //0
    TASK_DISPLAY,
#endif // (DISPLAY_SUPPORT)

#if (BLE_APP_PRESENT)
    TASK_APP,
#endif // (BLE_APP_PRESENT)

#if (BLE_HOST_PRESENT)
    TASK_L2CC,    // L2CAP Controller Task
    TASK_GATTM,   // Generic Attribute Profile Manager Task
    TASK_GATTC,   // Generic Attribute Profile Controller Task
    TASK_GAPM,    // Generic Access Profile Manager
    TASK_GAPC,    // Generic Access Profile Controller

    // allocate a certain number of profiles task
    TASK_PRF_MAX = (TASK_GAPC + BLE_NB_PROFILES),

    #ifdef BLE_AUDIO_AM0_TASK
    TASK_AM0,     // BLE Audio Mode 0 Task
    #endif // BLE_AUDIO_AM0_TASK
#endif // (BLE_HOST_PRESENT)

#if (AHI_TL_SUPPORT)
    TASK_AHI,
#endif // (AHI_TL_SUPPORT)

    /// Maximum number of tasks
    TASK_MAX,

    TASK_NONE = 0xFF,
};

/// Kernel memory heaps types.
enum
{
    /// Memory allocated for environment variables
    KE_MEM_ENV,
    #if (BLE_HOST_PRESENT)
    /// Memory allocated for Attribute database
    KE_MEM_ATT_DB,
    #endif // (BLE_HOST_PRESENT)
    /// Memory allocated for kernel messages
    KE_MEM_KE_MSG,
    /// Non Retention memory block
    KE_MEM_NON_RETENTION,
    KE_MEM_BLOCK_MAX,
};



#if (BT_EMB_PRESENT)
#define BT_HEAP_MSG_SIZE_      BT_HEAP_MSG_SIZE
#define BT_HEAP_ENV_SIZE_      BT_HEAP_ENV_SIZE
#else
#define BT_HEAP_MSG_SIZE_      0
#define BT_HEAP_ENV_SIZE_      0
#endif //BT_EMB_PRESENT

#if (BLE_EMB_PRESENT)
#define BLE_HEAP_MSG_SIZE_     BLE_HEAP_MSG_SIZE
#define BLE_HEAP_ENV_SIZE_     BLE_HEAP_ENV_SIZE
#else
#define BLE_HEAP_MSG_SIZE_     0
#define BLE_HEAP_ENV_SIZE_     0
#endif //BLE_EMB_PRESENT

#if (BLE_HOST_PRESENT)

#define BLEHL_HEAP_MSG_SIZE_   BLEHL_HEAP_MSG_SIZE
#define BLEHL_HEAP_ENV_SIZE_   BLEHL_HEAP_ENV_SIZE
#define BLEHL_HEAP_DB_SIZE_    BLEHL_HEAP_DB_SIZE
#else
#define BLEHL_HEAP_MSG_SIZE_   0
#define BLEHL_HEAP_ENV_SIZE_   0
#define BLEHL_HEAP_DB_SIZE_    0
#endif //BLE_HOST_PRESENT

/// Kernel Message Heap
#define RWIP_HEAP_MSG_SIZE         (  BT_HEAP_MSG_SIZE_      + \
                                    BLE_HEAP_MSG_SIZE_     + \
                                    BLEHL_HEAP_MSG_SIZE_      )

/// Number of link in kernel environment
#define KE_NB_LINK_IN_HEAP_ENV   1 // 4 by bottle

/// Size of Environment heap
#define RWIP_HEAP_ENV_SIZE         ( BT_HEAP_ENV_SIZE_         + \
                                     ( BLE_HEAP_ENV_SIZE_      + \
                                       BLEHL_HEAP_ENV_SIZE_ )    \
                                     * KE_NB_LINK_IN_HEAP_ENV )

/// Size of Attribute database heap
#define RWIP_HEAP_DB_SIZE         (  BLEHL_HEAP_DB_SIZE  )

/// Size of non retention heap - 512 bytes per ble link plus 4096 bytes for data throughput should be sufficient and should be tuned
#if (BLE_EMB_PRESENT || BLE_HOST_PRESENT)
#define RWIP_HEAP_NON_RET_SIZE    (( 512 * BLE_CONNECTION_MAX ) + 3072)
#else
#define RWIP_HEAP_NON_RET_SIZE    ( 1024 )
#endif

/// Minimum sleep time to enter in deep sleep (in half slot).
#define RWIP_MINIMUM_SLEEP_TIME                (1)

/******************************************************************************************/
/* -------------------------        BT-BLE COEX        -----------------------------------*/
/******************************************************************************************/
#if (BLE_EMB_PRESENT || BT_EMB_PRESENT)
/// Enable and diable definition for the PTI
///Enable TX busy signal
#define RWIP_PTI_TXEN           1
///Disable TX busy signal
#define RWIP_PTI_TXDIS          0
/// Tx busy position
#define RWIP_TXBSY_POS          0

///Enable RX busy signal
#define RWIP_PTI_RXEN           1
///Disable RX busy signal
#define RWIP_PTI_RXDIS          0
/// Rx busy position
#define RWIP_RXBSY_POS          1

///Enable do not abort TX
#define RWIP_PTI_DNABORTEN      1
///Disable do not abort TX
#define RWIP_PTI_DNABORTDIS     0
/// Do not abort busy position
#define RWIP_DNABORT_POS        2

///Allows Tx operation in the current frame.
#define RWIP_MWS_TXEN           0
///Prevent from any Tx operation in the current frame.
#define RWIP_MWS_TXDIS          1
/// MWS transmit disable position
#define RWIP_MWSTXDSB_POS       3

///Allows Rx operation in the current frame.
#define RWIP_MWS_RXEN           0
///Prevent from any Rx operation in the current frame.
#define RWIP_MWS_RXDIS          1
/// MWS transmit disable position
#define RWIP_MWSRXDSB_POS       4

/// Bit masking
#define RWIP_COEX_BIT_MASK      1

/// Coex configuration index
enum rwip_coex_config_idx
{
    #if (BT_EMB_PRESENT)
    RWIP_COEX_MSSWITCH_IDX ,
    RWIP_COEX_SNIFFATT_IDX ,
    RWIP_COEX_PAGE_IDX,
    RWIP_COEX_PSCAN_IDX,
    RWIP_COEX_INQ_IDX,
    RWIP_COEX_INQRES_IDX,
    RWIP_COEX_SCORSVD_IDX,
    RWIP_COEX_BCAST_IDX,
    RWIP_COEX_CONNECT_IDX,
    #endif //#if (BT_EMB_PRESENT)
    #if (BLE_EMB_PRESENT)
    RWIP_COEX_CON_IDX,
    RWIP_COEX_CON_DATA_IDX,
    RWIP_COEX_ADV_IDX,
    RWIP_COEX_SCAN_IDX,
    RWIP_COEX_INIT_IDX,
    #endif // #if (BLE_EMB_PRESENT)
    /// Max configuration index
    RWIP_COEX_CFG_MAX,
};
/******************************************************************************************/
/* -------------------------     BT-BLE PRIORITIES     -----------------------------------*/
/******************************************************************************************/
/// Priority index definition
enum rwip_prio_idx
{
    #if (BT_EMB_PRESENT)
    /// ACL event default priority
    RWIP_PRIO_ACL_DFT_IDX,
    /// ACL event priority with activity
    RWIP_PRIO_ACL_ACT_IDX,
    /// ACL Role Switch event default priority
    RWIP_PRIO_ACL_RSW_IDX,
    /// ACL sniff event default priority
    RWIP_PRIO_ACL_SNIFF_DFT_IDX,
    /// ACL sniff transition event default priority
    RWIP_PRIO_ACL_SNIFF_TRANS_IDX,
    #if MAX_NB_SYNC
    /// SCO event default priority
    RWIP_PRIO_SCO_DFT_IDX,
    #endif //MAX_NB_SYNC
    /// Broadcast ACL event default priority
    RWIP_PRIO_BCST_DFT_IDX,
    /// Broadcast ACL event with LMP activity priority
    RWIP_PRIO_BCST_ACT_IDX,
    /// CSB RX event default priority
    RWIP_PRIO_CSB_RX_DFT_IDX,
    /// CSB TX event default priority
    RWIP_PRIO_CSB_TX_DFT_IDX,
    /// Inquiry event default priority
    RWIP_PRIO_INQ_DFT_IDX,
    /// Inquiry Scan event default priority
    RWIP_PRIO_ISCAN_DFT_IDX,
    /// Page event default priority
    RWIP_PRIO_PAGE_DFT_IDX,
    /// Page event default priority
    RWIP_PRIO_PAGE_1ST_PKT_IDX,
    /// Page first packet event default priority
    RWIP_PRIO_PCA_DFT_IDX,
    /// Page scan event default priority
    RWIP_PRIO_PSCAN_DFT_IDX,
    /// Page scan event priority increment when canceled
    RWIP_PRIO_PSCAN_1ST_PKT_IDX,
    /// Synchronization Scan event default priority
    RWIP_PRIO_SSCAN_DFT_IDX,
    /// Synchronization Train event default priority
    RWIP_PRIO_STRAIN_DFT_IDX,
    #endif //#if (BT_EMB_PRESENT)
    #if (BLE_EMB_PRESENT)
    /// Default priority for scanning events
    RWIP_PRIO_SCAN_IDX,
    /// Default priority for initiating events
    RWIP_PRIO_INIT_IDX,
    /// Default priority for Le connection establishment
    RWIP_PRIO_LE_ESTAB_IDX,
    /// Default priority for Idle connection
    RWIP_PRIO_LE_CON_IDLE_IDX,
    /// Default priority for active connect events
    RWIP_PRIO_LE_CON_ACT_IDX,
    /// Default priority for advertising events
    RWIP_PRIO_ADV_IDX,
    /// Default priority for advertising high duty cycle events
    RWIP_PRIO_ADV_HDC_IDX,
    #endif // #if (BLE_EMB_PRESENT)
    RWIP_PRIO_IDX_MAX
};
/// Default priority value definition
enum rwip_prio_dft
{
    #if (BT_EMB_PRESENT)
    /// ACL event default priority
    RWIP_PRIO_ACL_DFT               = 5,
    /// ACL event priority with activity
    RWIP_PRIO_ACL_ACT               = 10,
    /// ACL Role Switch event default priority
    RWIP_PRIO_ACL_RSW               = 20,
    /// ACL sniff event default priority
    RWIP_PRIO_ACL_SNIFF_DFT         = 15,
    /// ACL sniff transition event default priority
    RWIP_PRIO_ACL_SNIFF_TRANS       = 10,
    #if MAX_NB_SYNC
    /// SCO event default priority
    RWIP_PRIO_SCO_DFT               = 18,
    #endif //MAX_NB_SYNC
    /// Broadcast ACL event default priority
    RWIP_PRIO_BCST_DFT              = 5,
    /// Broadcast ACL event with LMP activity priority
    RWIP_PRIO_BCST_ACT              = 10,
    /// CSB RX event default priority
    RWIP_PRIO_CSB_RX_DFT            = 10,
    /// CSB TX event default priority
    RWIP_PRIO_CSB_TX_DFT            = 10,
    /// Inquiry event default priority
    RWIP_PRIO_INQ_DFT               = 5,
    /// Inquiry Scan event default priority
    RWIP_PRIO_ISCAN_DFT             = 5,
    /// Page event default priority
    RWIP_PRIO_PAGE_DFT              = 8,
    /// Page first packet event default priority
    RWIP_PRIO_PAGE_1ST_PKT          = 20,
    /// PCA event default priority
    RWIP_PRIO_PCA_DFT               = 20,
    /// Page scan event default priority
    RWIP_PRIO_PSCAN_DFT             = 8,
    /// Page scan event priority increment when canceled
    RWIP_PRIO_PSCAN_1ST_PKT         = 20,
    /// Synchronization Scan event default priority
    RWIP_PRIO_SSCAN_DFT             = 10,
    /// Synchronization Train event default priority
    RWIP_PRIO_STRAIN_DFT            = 10,
    #endif //#if (BT_EMB_PRESENT)
    #if (BLE_EMB_PRESENT)
    /// Default priority for scanning events
    RWIP_PRIO_SCAN_DFT              = 5,
    /// Default priority for initiating events
    RWIP_PRIO_INIT_DFT              = 10,
    /// Default priority for LE connection establishment
    RWIP_PRIO_LE_ESTAB_DFT          = 20,
    /// Default priority for Idle connection
    RWIP_PRIO_LE_CON_IDLE_DFT       = 10,
    /// Default priority for active connect events
    RWIP_PRIO_LE_CON_ACT_DFT        = 15,
    /// Default priority for advertising events
    RWIP_PRIO_ADV_DFT               = 5,
    /// Default priority for advertising high duty cycle events
    RWIP_PRIO_ADV_HDC_DFT           = 10,
    #endif // #if (BLE_EMB_PRESENT)
    /// Max priority
    RWIP_PRIO_MAX                   = 31,
};

/// Default increment value definition
enum rwip_incr_dft
{
    #if (BT_EMB_PRESENT)
    /// ACL event default increment
    RWIP_INCR_ACL_DFT               = 1,
    /// ACL event increment with activity
    RWIP_INCR_ACL_ACT               = 1,
    /// ACL Role Switch event default increment
    RWIP_INCR_ACL_RSW               = 1,
    /// ACL sniff event default increment
    RWIP_INCR_ACL_SNIFF_DFT         = 1,
    /// ACL sniff transition event default increment
    RWIP_INCR_ACL_SNIFF_TRANS       = 1,
    #if MAX_NB_SYNC
    /// SCO event default increment
    RWIP_INCR_SCO_DFT               = 1,
    #endif //MAX_NB_SYNC
    /// Broadcast ACL event default increment
    RWIP_INCR_BCST_DFT              = 1,
    /// Broadcast ACL event with LMP activity increment
    RWIP_INCR_BCST_ACT              = 1,
    /// CSB RX event default increment
    RWIP_INCR_CSB_RX_DFT            = 1,
    /// CSB TX event default increment
    RWIP_INCR_CSB_TX_DFT            = 1,
    /// Inquiry event default increment
    RWIP_INCR_INQ_DFT               = 1,
    /// Inquiry Scan event default increment
    RWIP_INCR_ISCAN_DFT             = 1,
    /// Page event default increment
    RWIP_INCR_PAGE_DFT              = 1,
    /// Page event default increment
    RWIP_INCR_PAGE_1ST_PKT          = 2,
    /// Page first packet event default increment
    RWIP_INCR_PCA_DFT               = 1,
    /// Page scan event default increment
    RWIP_INCR_PSCAN_DFT             = 1,
    /// Page scan event increment increment when canceled
    RWIP_INCR_PSCAN_1ST_PKT         = 1,
    /// Synchronization Scan event default increment
    RWIP_INCR_SSCAN_DFT             = 1,
    /// Synchronization Train event default increment
    RWIP_INCR_STRAIN_DFT            = 1,
    #endif //#if (BT_EMB_PRESENT)
    #if (BLE_EMB_PRESENT)
    /// Default increment for scanning events
    RWIP_INCR_SCAN_DFT              = 1,
    /// Default increment for initiating events
    RWIP_INCR_INIT_DFT              = 1,
    /// Default increment for LE connection establishment
    RWIP_INCR_LE_ESTAB_DFT          = 1,
    /// Default increment for Idle connection
    RWIP_INCR_LE_CON_IDLE_DFT       = 1,
    /// Default increment for active connect events
    RWIP_INCR_LE_CON_ACT_DFT        = 11,
    /// Default increment for advertising events
    RWIP_INCR_ADV_DFT               = 1,
    /// Default increment for advertising high duty cycle events
    RWIP_INCR_ADV_HDC_PRIO_DFT      = 1,
    #endif // #if (BLE_EMB_PRESENT)
};
#endif //#if (BLE_EMB_PRESENT || BT_EMB_PRESENT)
/// @} BT Stack Configuration
/// @} ROOT

#endif //RWIP_CONFIG_H_
