/**
****************************************************************************************
*
* @file rwip.h
*
* @brief RW IP SW main module
*
* Copyright (C) RivieraWaves 2009-2015
*
*
****************************************************************************************
*/
#ifndef _RWIP_H_
#define _RWIP_H_

/**
 ****************************************************************************************
 * @addtogroup ROOT
 * @brief Entry points of the RW IP stacks/modules
 *
 * This module contains the primitives that allow an application accessing and running the
 * RW IP protocol stacks / modules.
 *
 * @{
 ****************************************************************************************
 */

#include "rwip_config.h"          // stack configuration

#include <stdint.h>               // standard integer definitions
#include <stdbool.h>              // standard boolean definitions

/// retrieve 10ms time according to clock time
#define RWIP_CLOCK_TO_10MS_TIME(clock)   ((clock) >> 4)
/// retrieve clock time according to 10ms time
#define RWIP_10MS_TIME_TO_CLOCK(time)    ((time)  << 4)
/// Invalid target time
#define RWIP_INVALID_TARGET_TIME         (0xFFFFFFFFL)

#if (DEEP_SLEEP)
/// Definition of the bits preventing the system from sleeping
enum prevent_sleep
{
    /// Flag indicating that the wake up process is ongoing
    RW_WAKE_UP_ONGOING = 0x0001,
    /// Flag indicating that an TX transfer is ongoing on Transport Layer
    RW_TL_TX_ONGOING = 0x0002,
    /// Flag indicating that an RX transfer is ongoing on Transport Layer
    RW_TL_RX_ONGOING = 0x0004,
    /// Flag indicating HCI timeout is ongoing
    RW_AHI_TIMEOUT = 0x0008,
    /// Flag indicating that an encryption is ongoing
    RW_CRYPT_ONGOING = 0x0010,
    /// Flag indicating that a element deletion is on going
    RW_DELETE_ELT_ONGOING = 0x0020,
    /// Flag indicating that controller shall not sleep due to not CSB LPO_Allowed
    RW_CSB_NOT_LPO_ALLOWED = 0x0040,
    /// Flag indicating the MWS/WLAN Event Generator is in operation
    RW_MWS_WLAN_EVENT_GENERATOR_ACTIVE = 0x0080
};
#endif //DEEP_SLEEP



/**
 * External interface type types.
 */
enum rwip_eif_types
{
    /// Host Controller Interface - Controller part
    RWIP_EIF_HCIC,

    /// Host Controller Interface - Host part
    RWIP_EIF_HCIH,

    /// Application Host interface
    RWIP_EIF_AHI,
};


/// Enumeration of External Interface status codes
enum rwip_eif_status
{
    /// EIF status OK
    RWIP_EIF_STATUS_OK,
    /// EIF status KO
    RWIP_EIF_STATUS_ERROR,

#if (BLE_EMB_PRESENT == 0)
    /// External interface detached
    RWIP_EIF_STATUS_DETACHED,
    /// External interface attached
    RWIP_EIF_STATUS_ATTACHED,
#endif // (BLE_EMB_PRESENT == 0)
};

/// Enumeration of RF modulations
enum rwip_rf_mod
{
    MOD_GFSK  = 0x01,
    MOD_DQPSK = 0x02,
    MOD_8DPSK = 0x03,
};

/// API functions of the RF driver that are used by the BLE or BT software
struct rwip_rf_api
{
    /// Function called upon HCI reset command reception
    void (*reset)(void);
    /// Function called to enable/disable force AGC mechanism (true: en / false : dis)
    void (*force_agc_enable)(bool);
    /// Function called when TX power has to be decreased for a specific link id
    bool (*txpwr_dec)(uint8_t);
    /// Function called when TX power has to be increased for a specific link id
    bool (*txpwr_inc)(uint8_t);
    /// Function called when TX power has to be set to max for a specific link id
    void (*txpwr_max_set)(uint8_t);
    /// Function called to convert a TX power CS power field into the corresponding value in dBm
    uint8_t (*txpwr_dbm_get)(uint8_t, uint8_t);
    /// Function called to convert a power in dBm into a control structure tx power field
    uint8_t (*txpwr_cs_get)(int8_t);
    /// Function called to convert the RSSI read from the control structure into a real RSSI
    int8_t (*rssi_convert)(uint8_t);
    /// Function used to read a RF register
    uint32_t (*reg_rd)(uint16_t);
    /// Function used to write a RF register
    void (*reg_wr)(uint16_t, uint32_t);
    /// Function called to put the RF in deep sleep mode
    void (*sleep)(void);
    /// Index of maximum TX power
    uint8_t txpwr_max;
    /// RSSI high threshold ('real' signed value in dBm)
    int8_t rssi_high_thr;
    /// RSSI low threshold ('real' signed value in dBm)
    int8_t rssi_low_thr;
    /// interferer threshold ('real' signed value in dBm)
    int8_t rssi_interf_thr;
    /// RF wakeup delay (in slots)
    uint8_t wakeup_delay;
};

/// Internal API for priority
struct rwip_prio
{
    ///value
    uint8_t value;
    ///Increment
    uint8_t increment;
};

/// Internal API for COEX
struct rwip_coex
{
    ///Coexistence control field
    uint8_t coex_cntl;
};


/**
 ****************************************************************************************
 * @brief Function called when packet transmission/reception is finished.

 * @param[in]  dummy  Dummy data pointer returned to callback when operation is over.
 * @param[in]  status Ok if action correctly performed, else reason status code.
 *****************************************************************************************
 */
typedef void (*rwip_eif_callback) (void*, uint8_t);

/**
 * Transport layer communication interface.
 */
struct rwip_eif_api
{
    /**
     *************************************************************************************
     * @brief Starts a data reception.
     *
     * @param[out] bufptr      Pointer to the RX buffer
     * @param[in]  size        Size of the expected reception
     * @param[in]  callback    Pointer to the function called back when transfer finished
     * @param[in]  dummy       Dummy data pointer returned to callback when reception is finished
     *************************************************************************************
     */
    void (*read) (uint8_t *bufptr, uint32_t size, rwip_eif_callback callback, void* dummy);

    /**
     *************************************************************************************
     * @brief Starts a data transmission.
     *
     * @param[in]  bufptr      Pointer to the TX buffer
     * @param[in]  size        Size of the transmission
     * @param[in]  callback    Pointer to the function called back when transfer finished
     * @param[in]  dummy       Dummy data pointer returned to callback when transmission is finished
     *************************************************************************************
     */
    void (*write)(uint8_t *bufptr, uint32_t size, rwip_eif_callback callback, void* dummy);

    /**
     *************************************************************************************
     * @brief Enable Interface flow.
     *************************************************************************************
     */
    void (*flow_on)(void);

    /**
     *************************************************************************************
     * @brief Disable Interface flow.
     *
     * @return True if flow has been disabled, False else.
     *************************************************************************************
     */
    bool (*flow_off)(void);
};

/*
 * VARIABLE DECLARATION
*****************************************************************************************
 */

/// API for RF driver
extern struct rwip_rf_api rwip_rf;
#if (BLE_EMB_PRESENT || BT_EMB_PRESENT)
/// API for dual mode priority
extern const struct rwip_prio rwip_priority[RWIP_PRIO_IDX_MAX];
/// API for COEX
extern const uint8_t rwip_coex_cfg[RWIP_COEX_CFG_MAX];
#endif //#if (BLE_EMB_PRESENT || BT_EMB_PRESENT)

/*
 * MACROS
 ****************************************************************************************
 */

/// Get Event status flag
#define RWIP_COEX_GET(coex_cfg_idx, bit_field) \
                (uint8_t)(((rwip_coex_cfg[RWIP_COEX_ ## coex_cfg_idx ##_IDX]) >> RWIP_ ## bit_field ## _POS ) & RWIP_COEX_BIT_MASK)

/*
 * FUNCTION DECLARATION
*****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Initializes the RW BT SW.
 *
 ****************************************************************************************
 */
void rwip_init(uint32_t error);

/**
 ****************************************************************************************
 * @brief Reset the RW BT SW.
 *
 ****************************************************************************************
 */
void rwip_reset(void);

/**
 ****************************************************************************************
 * @brief Gives FW/HW versions of RW-BT stack.
 *
 ****************************************************************************************
 */
void rwip_version(uint8_t* fw_version, uint8_t* hw_version);

/**
 ****************************************************************************************
 * @brief Schedule all pending events.
 *
 ****************************************************************************************
 */
void rwip_schedule(void);

/**
 ****************************************************************************************
 * @brief Invoke the sleep function.
 *
 * @return  true: processor sleep allowed, false otherwise
 ****************************************************************************************
 */
bool rwip_sleep(void);

#if DEEP_SLEEP
/**
 ****************************************************************************************
 * @brief Handle wake-up.
 ****************************************************************************************
 */
void rwip_wakeup(void);

/**
 ****************************************************************************************
 * @brief Handle end of wake-up.
 ****************************************************************************************
 */
void rwip_wakeup_end(void);

/**
 ****************************************************************************************
 * @brief Set the wake-up delay
 *
 * @param[in] wakeup_delay   Wake-up delay in us
 ****************************************************************************************
 */
void rwip_wakeup_delay_set(uint16_t wakeup_delay);

/**
 ****************************************************************************************
 * @brief Set a bit in the prevent sleep bit field, in order to prevent the system from
 *        going to sleep
 *
 * @param[in] prv_slp_bit   Bit to be set in the prevent sleep bit field
 ****************************************************************************************
 */
void rwip_prevent_sleep_set(uint16_t prv_slp_bit);

/**
 ****************************************************************************************
 * @brief Clears a bit in the prevent sleep bit field, in order to allow the system
 *        going to sleep
 *
 * @param[in] prv_slp_bit   Bit to be cleared in the prevent sleep bit field
 ****************************************************************************************
 */
void rwip_prevent_sleep_clear(uint16_t prv_slp_bit);

/**
 ****************************************************************************************
 * @brief Check if sleep mode is enable
 *
 * @return    true if sleep is enable, false otherwise
 ****************************************************************************************
 */
bool rwip_sleep_enable(void);

/**
 ****************************************************************************************
 * @brief Check if external wake-up is enable
 *
 * @return    true if external wakeup is enable, false otherwise
 ****************************************************************************************
 */
bool rwip_ext_wakeup_enable(void);

/**
 ****************************************************************************************
 * @brief Converts a duration in lp cycles into a duration is us.
 *
 * The function converts a duration in lp cycles into a duration is us, according to the
 * low power clock frequency (32768Hz or 32000Hz).
 *
 * To do this the following formulae are applied:
 *
 *   Tus = x*30.517578125 = 30*x + x/2 + x/64 + x/512 for a 32.768kHz clock or
 *   Tus = x*31.25        = 31*x + x/4                for a 32kHz clock
 *
 * @note This function is also performing a compensation of accumulated drift created by
 * rounding present in the algorithm
 *
 * @param[in] lpcycles    duration in lp cycles
 *
 * @return duration in us
 ****************************************************************************************
 */
uint32_t rwip_sleep_lpcycles_2_us(uint32_t lpcycles);


/**
 ****************************************************************************************
 * @brief Converts a duration in us into a duration in lp cycles.
 *
 * The function converts a duration in us into a duration is lp cycles, according to the
 * low power clock frequency (32768Hz or 32000Hz).
 *
 * @param[in] us    duration in us
 *
 * @return duration in lpcycles
 ****************************************************************************************
 */
uint32_t rwip_us_2_lpcycles(uint32_t us);
#endif // DEEP_SLEEP

#if (BT_EMB_PRESENT)

#if PCA_SUPPORT
/**
 ****************************************************************************************
 * @brief Check if clock dragging limitation
 *
 * @return    true if clock dragging must be used
 ****************************************************************************************
 */
bool rwip_pca_clock_dragging_only(void);
#endif //PCA_SUPPORT

/**
 ****************************************************************************************
 * @brief Set current time
 *
 * @param clock value in half-slots
 ****************************************************************************************
 */
void rwip_time_set(uint32_t clock);
#endif // (BT_EMB_PRESENT)

#if (BT_EMB_PRESENT || BLE_EMB_PRESENT)
#if (RW_MWS_COEX)
/**
 ****************************************************************************************
 * @brief Enable/Disable the MWS coexistence interface.
 *
 * @param[in]   CoexSetting     Coexistence value
 *
 ****************************************************************************************
 */
void rwip_mwscoex_set(bool state);
#endif //RW_MWS_COEX

#if (RW_WLAN_COEX)
/**
 ****************************************************************************************
 * @brief Enable/Disable the Wireless LAN coexistence interface.
 *
 * @param[in]   CoexSetting     Coexistence value
 *
 ****************************************************************************************
 */
void rwip_wlcoex_set(bool state);
#endif //RW_WLAN_COEX
#endif //(BT_EMB_PRESENT || BLE_EMB_PRESENT)

/**
 ****************************************************************************************
 * @brief Function to implement in platform in order to retrieve expected external
 * interface such as UART for Host Control Interface.
 *
 * @param[in] type external interface type (@see rwip_eif_types)
 *
 * @return External interface api structure
 ****************************************************************************************
 */

extern const struct rwip_eif_api spi_api;

extern const struct rwip_eif_api uart_api;




///@} ROOT

#endif // _RWIP_H_
