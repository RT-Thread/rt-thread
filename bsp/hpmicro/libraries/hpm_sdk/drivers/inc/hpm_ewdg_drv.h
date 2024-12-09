/*
 * Copyright (c) 2023-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_EWDG_DRV_H
#define HPM_EWDG_DRV_H

#include "hpm_common.h"
#include "hpm_ewdg_regs.h"
#include "hpm_soc_feature.h"

/**
 * @brief EWDG driver APIs
 * @defgroup ewdg_interface EWDG driver APIs
 * @addtogroup ewdg_interface
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief EWDG error codes
 */
enum {
    status_ewdg_tick_out_of_range = MAKE_STATUS(status_group_ewdg, 0),  /*!< The tick is out of range */
    status_ewdg_div_out_of_range = MAKE_STATUS(status_group_ewdg, 1),   /*!< Clock Divider is out of range */
    status_ewdg_feature_unsupported = MAKE_STATUS(status_group_ewdg, 2), /*!< Feature is not supported */
};

/**
 * @brief EWDG Password Definitions
 *
 * @defgroup ewdg_password_def EWDG Password definitions
 * @{
 */
#define EWDG_REFRESH_UNLOCK_PASSWORD_DEFAULT (0xED09U)          /*!< Default EWDG Refresh Password */
#define EWDG_UPDATE_PASSWORD_DEFAULT         (0xECF9U)          /*!< Default EWDG Update Password */
#define EWDG_REFRESH_UNLOCK_FIXED_KEY        (0x55AAU)          /*!< EWDG Unlock Fixed key */
#define EWDG_REFRESH_KEY                     (0x5A45524FUL)     /*!< EWDG Refresh key */
/**
 * @}
 */

/**
 * @brief EWDG Events
 *
 * @defgroup ewdg_event EWDG Event definitions
 * @{
 */
#define EWDG_EVENT_PARITY_ERROR                 (1UL << 6)    /*!< Parity Error Event */
#define EWDG_EVENT_TIMEOUT_RESET                (1UL << 5)    /*!< Timeout Reset Event */
#define EWDG_EVENT_TIMEOUT_INTERRUPT            (1UL << 4)    /*!< Timeout Interrupt Event */
#define EWDG_EVENT_CFG_REG_UPDATE_UNLOCK_FAIL   (1UL << 3)    /*!< Update Unlock Fail Event */
#define EWDG_EVENT_CFG_REG_UPDATE_VIOLATION     (1UL << 2)    /*!< Update Violation Event */
#define EWDG_EVENT_REFRESH_UNLOCK_FAIL          (1UL << 1)    /*!< Refresh Unlock Fail Event */
#define EWDG_EVENT_REFRESH_VIOLATION            (1UL << 0)    /*!< Refresh Violation Event */
/**
 * @}
 */

/**
 * @brief EWDG Interrupts
 * @defgroup ewdg_interrupt EWDG interrupt definitions
 * @{
 */
#define EWDG_INT_PARITY_FAIL            (1UL << 2)      /*!< Parity Error Interrupt */
#define EWDG_INT_CTRL_REG_UNLOCK_FAIL   (1UL << 4)      /*!< Unlock Control Register Fail Interrupt */
#define EWDG_INT_CTRL_REG_UPDATE_FAIL   (1UL << 6)      /*!< Update Control Register Violation Interrupt */
#define EWDG_INT_TIMEOUT                (1UL << 16)     /*!< Watchdog Timeout Interrupt */
#define EWDG_INT_REFRESH_UNLOCK_FAIL    (1UL << 20)     /*!< Refresh Register Unlock Fail interrupt */
#define EWDG_INT_REFRESH_VIOLATION      (1UL << 22)     /*!< Refresh Register Violation interrupt */
/*! All Interrupt masks */
#define EWDG_INT_ALL    (EWDG_INT_PARITY_FAIL | EWDG_INT_CTRL_REG_UNLOCK_FAIL | EWDG_INT_CTRL_REG_UPDATE_FAIL | \
                         EWDG_INT_TIMEOUT | EWDG_INT_REFRESH_UNLOCK_FAIL | EWDG_INT_REFRESH_VIOLATION)
/**
 * @}
 */

/**
 * @brief EWDG Resets
 *
 * @defgroup ewdg_reset_source EWDG reset source definitions
 * @{
 */
#define EWDG_RST_PARITY_FAIL            (1UL << 3)      /*!< Parity Error Reset */
#define EWDG_RST_CTRL_REG_UNLOCK_FAIL   (1UL << 5)      /*!< Unlock Control Register Fail Reset */
#define EWDG_RST_CTRL_REG_UPDATE_FAIL   (1UL << 7)      /*!< Update Control Register Violation Reset */
#define EWDG_RST_TIMEOUT                (1UL << 17)     /*!< Watchdog Timeout Reset */
#define EWDG_RST_REFRESH_UNLOCK_FAIL    (1UL << 21)     /*!< Refresh Register Unlock Fail Reset */
#define EWDG_RST_REFRESH_VIOLATION      (1UL << 23)     /*!< Refresh Register Violation Reset */
/*! All Reset masks */
#define EWDG_RST_ALL    (EWDG_RST_PARITY_FAIL | EWDG_RST_CTRL_REG_UNLOCK_FAIL | EWDG_RST_CTRL_REG_UPDATE_FAIL | \
                         EWDG_RST_TIMEOUT | EWDG_RST_REFRESH_UNLOCK_FAIL | EWDG_RST_REFRESH_VIOLATION)
/**
 * @}
 */



/**
 * @brief EWDG Refresh Unlock Methods
 */
typedef enum {
    /*! Use the Unlock Password directly */
    ewdg_refresh_unlock_method_password = 0,
    /*! Use password[14:0] | password[15] */
    ewdg_refresh_unlock_method_ring_left_shift_password_by_1 = 1,
    /*! Use fixed key: 0x55AA */
    ewdg_refresh_unlock_method_fixed_key = 2,
    /*! Use last_password[14:0] | (last_password[15] ^ password[0]) */
    ewdg_refresh_unlock_method_ring_left_shift_password_by_1_bit0_xor_password_bit0 = 3,
    /*! Max allowed range */
    ewdg_refresh_unlock_method_max = ewdg_refresh_unlock_method_ring_left_shift_password_by_1_bit0_xor_password_bit0
} ewdg_refresh_unlock_method_t;

/**
 * @brief EWDG Clock source for internal counter
 */
typedef enum {
    ewdg_cnt_clk_src_bus_clk,        /*!< Clock is from BUS clock */
    ewdg_cnt_clk_src_ext_osc_clk,    /*!< Clock is from External OSC */
} ewdg_cnt_clk_sel_t;

/**
 * @brief EWDG Lower Window Limitations
 */
typedef enum {
    /*! Refresh should be issued after 8/16 of timeout period */
    ewdg_window_lower_timeout_period_8_div_16 = 0,
    /*! Refresh should be issued after 10/16 of timeout period */
    ewdg_window_lower_timeout_period_10_div_16 = 1,
    /*! Refresh should be issued after 12/16 of timeout period */
    ewdg_window_lower_timeout_period_12_div_16 = 2,
    /*! Refresh should be issued after 14/16 of timeout period */
    ewdg_window_lower_timeout_period_14_div_16 = 3,
    /*! Maximum allowed limit value */
    ewdg_window_lower_timeout_period_max = ewdg_window_lower_timeout_period_14_div_16
} ewdg_window_low_limit_t;

/**
 * @brief EWDG Upper Window Limitations
 *
 * The Actual Upper Window = Lower Window + Upper Window Limit
 */
typedef enum {
    ewdg_window_upper_timeout_period_8_div_16 = 0,     /*!< 8/16 of timeout_reset_val */
    ewdg_window_upper_timeout_period_1_div_16 = 1,     /*!< 1/16 of timeout_reset_val */
    ewdg_window_upper_timeout_period_2_div_16 = 2,     /*!< 2/16 of timeout_reset_val */
    ewdg_window_upper_timeout_period_3_div_16 = 3,     /*!< 3/16 of timeout_reset_val */
    ewdg_window_upper_timeout_period_4_div_16 = 4,     /*!< 4/16 of timeout_reset_val */
    ewdg_window_upper_timeout_period_5_div_16 = 5,     /*!< 5/16 of timeout_reset_val */
    ewdg_window_upper_timeout_period_6_div_16 = 6,     /*!< 6/16 of timeout_reset_val */
    ewdg_window_upper_timeout_period_7_div_16 = 8,     /*!< 7/16 of timeout_reset_val */
    /*! Maximum allowed upper limit */
    ewdg_window_upper_timeout_period_max = ewdg_window_upper_timeout_period_7_div_16
} ewdg_window_upper_limit_t;

typedef enum {
    ewdg_low_power_mode_halt = 0,               /*!< Watchdog is halted in low power mode */
    ewdg_low_power_mode_work_clock_normal = 1,  /*!< Watchdog is will work with normal clock in low power mode */
} ewdg_low_power_mode_t;

/***
 * @brief EWDG Function Control Configurations
 */
typedef struct {
    ewdg_cnt_clk_sel_t cnt_clk_sel;                     /*!< Clock source for counter */
    bool enable_window_mode;                            /*!< Enable window mode */
    ewdg_window_low_limit_t window_lower_limit;         /*!< Lower limit of the window */
    /*! Upper limit of the window
     * The real upper window = (window_lower_limit/8 + window_upper_limit/16) * timeout_reset_val
     */
    ewdg_window_upper_limit_t window_upper_limit;

    bool enable_config_lock;                            /*!< Enable Lock for the Configuration Registers */

    bool enable_refresh_period;                         /*!< Enable Refresh period */
    bool enable_refresh_lock;                           /*!< Enable Refresh lock */
    ewdg_refresh_unlock_method_t refresh_unlock_method; /*!< Method to unlock REFRESH_REG */

    bool enable_overtime_self_clear;                    /*!< Enable Over time self clear */

    bool keep_running_in_debug_mode;                    /*!< Keep running even in debug mode */
    ewdg_low_power_mode_t low_power_mode;               /*!< Watchdog behavior in low power mode */
    /*!
     * Select timeout value type
     *  - true: use the IP-level value (in terms of EWDG counter ticks)
     *  - false: Use the user friendly timeout value (in terms of microseconds)
     */
    bool use_lowlevel_timeout;
    union {
        struct {
            uint32_t timeout_interrupt_us;  /*!< Timeout value for interrupt (in terms of microseconds) */
            uint32_t timeout_reset_us;      /*!< Timeout value for reset (in terms of microseconds */
        };
        struct {
            uint32_t timeout_interrupt_val;           /*!< Timeout value for interrupt (in terms of counter ticks) */
            /*! Timeout value for reset (in terms of counter ticks
             *  Note: timeout_reset_val must > timeout_interrupt_val
             */
            uint32_t timeout_reset_val;
            uint32_t clock_div_by_power_of_2; /*!< Power of 2 Divider */
        };
    };

    uint16_t refresh_period_in_bus_cycles;              /*!< Refresh period */
    uint16_t refresh_unlock_password;                   /*!< Password for unlocking write to REFRESH_REG */

    uint16_t ctrl_reg_update_password;                  /*!< Update Password */
    uint16_t ctrl_reg_update_period_bus_clk_x_128;      /*!< Update Period */
} ewdg_func_ctrl_config_t;

/**
 * @brief EWDG Reset and Interrupt Configurations
 */
typedef struct {
    bool enable_ctrl_parity_fail_interrupt;         /*!< Enable Parity Fail Interrupt */
    bool enable_ctrl_parity_fail_reset;             /*!< Enable Parity Fail Reset */
    bool enable_ctrl_unlock_fail_interrupt;         /*!< Enable Control Register Unlock Fail Interrupt */
    bool enable_ctrl_unlock_fail_reset;             /*!< Enable Control Register Unlock Fail Reset */
    bool enable_ctrl_update_violation_interrupt;    /*!< Enable Control Register Update Violation Interrupt */
    bool enable_ctrl_update_violation_reset;        /*!< Enable Control Register Update Violation Reset */
    bool enable_timeout_interrupt;                  /*!< Enable Timeout Interrupt */
    bool enable_timeout_reset;                      /*!< Enable Timeout Reset */
    bool enable_refresh_unlock_fail_interrupt;      /*!< Enable Refresh Unlock Fail Interrupt */
    bool enable_refresh_unlock_fail_reset;          /*!< Enable Refresh Unlock Fail Reset */
    bool enable_refresh_violation_interrupt;        /*!< Enable Refresh Violation Interrupt */
    bool enable_refresh_violation_reset;            /*!< Enable Refresh Violation Reset */
} ewdg_interrupt_reset_config_t;

/**
 * @brief Enhanced Watchdog Configuration Structure
 */
typedef struct {
    ewdg_interrupt_reset_config_t int_rst_config;   /*!< Error Control Configuration */
    ewdg_func_ctrl_config_t ctrl_config;            /*!< Function Control Configuration */
    bool enable_watchdog;                           /*!< Enable Watchdog */
    uint32_t cnt_src_freq;                          /*!< Frequency for the clock used as the counter clock source */
} ewdg_config_t;

/**
 * @brief Check whether the Control Registers are locked
 *
 * @param [in] ptr EWDG base
 *
 * @retval true Control Registers are locked
 * @retval false Control Registers are unlocked
 */
static inline bool ewdg_is_ctrl_reg_locked(EWDG_Type *ptr)
{
    return ((ptr->CTRL0 & EWDG_CTRL0_CFG_LOCK_MASK) != 0U);
}

/**
 * @brief Get the Divider for Counter Clock
 *
 * @param [in] ptr EWDG base
 *
 * @return divider value
 */
static inline uint32_t ewdg_get_count_clk_divider(EWDG_Type *ptr)
{
    return (1UL << EWDG_CTRL0_DIV_VALUE_GET(ptr->CTRL0));
}

/**
 * @brief Check whether the Refresh register is locked
 *
 * @param [in] ptr EWDG base
 *
 * @retval true Control Registers are locked
 * @retval false Control Registers are unlocked
 */
static inline bool ewdg_is_refresh_locked(EWDG_Type *ptr)
{
    return ((ptr->CTRL0 & EWDG_CTRL0_REF_LOCK_MASK) != 0U);
}

/**
 * @brief Unlock Write to Control Registers
 *
 * @param  [in] ptr EWDG base
 */
static inline void ewdg_unlock_ctrl_regs(EWDG_Type *ptr)
{
    uint32_t ctrl_update_prot = ptr->CFG_PROT;
    ptr->CFG_PROT = ctrl_update_prot;
}

/**
 * @brief Write Refresh Magic Number to EWDG Refresh register
 * @param  [in] ptr EWDG base
 */
static inline void ewdg_write_refresh_reg(EWDG_Type *ptr)
{
    ptr->WDT_REFRESH_REG = EWDG_REFRESH_KEY;
}

/**
 * @brief Get the Timeout Reset ticks
 * @param [in] ptr EWDG base
 * @return Timeout Reset ticks
 */
static inline uint32_t ewdg_get_timeout_reset_ticks(EWDG_Type *ptr)
{
    return ptr->OT_RST_VAL;
}

#if !defined(EWDG_SOC_SUPPORT_TIMEOUT_INTERRUPT) || (EWDG_SOC_SUPPORT_TIMEOUT_INTERRUPT == 1)
/**
 * @brief Get the Timeout Interrupt ticks
 * @param [in] ptr EWDG base
 * @return Timeout Interrupt ticks
 */
static inline uint32_t ewdg_get_timeout_interrupt_ticks(EWDG_Type *ptr)
{
    return ptr->OT_INT_VAL;
}
#endif

/**
 * @brief Clear Interrupt Status for EWDG
 *
 * @note The TIMEOUT_INT_EVENT cannot be cleared directly, it needs to be cleared by the refresh sequence
 *
 * @param [in] ptr EWDG base
 * @param [in] mask Status Mask Bits, @ref ewdg_event
 */
static inline void ewdg_clear_status_flags(EWDG_Type *ptr, uint32_t mask)
{
    ptr->WDT_STATUS = mask;
}

/**
 * @brief Get the Status of EWDG
 *
 * @param [in] ptr EWDG base
 *
 * @return STATUS register value
 */
static inline uint32_t ewdg_get_status_flags(EWDG_Type *ptr)
{
    return ptr->WDT_STATUS;
}

/**
 * @brief Get the Refresh Unlock Mechanism
 * @param  [in] ptr EWDG base
 * @return EWDG refresh unlock method
 */
static inline ewdg_refresh_unlock_method_t ewdg_get_refresh_unlock_method(EWDG_Type *ptr)
{
    return (ewdg_refresh_unlock_method_t) (EWDG_CTRL0_REF_UNLOCK_MEC_GET(ptr->CTRL0));
}

/**
 * @brief Enable EWDG
 *
 * This function enables the functionality of the EWDG and start the watchdog timer
 *
 * @param  [in] ptr EWDG base
 *
 * @note Once the EWDG is enabled,
 *      - if the software needs to update the control register, the update unlock must be
 *       performed first if the control register lock is enabled.
 *
 */
void ewdg_enable(EWDG_Type *ptr);


/**
 * @brief Disable EWDG
 * @param  [in] ptr EWDG base
 */
void ewdg_disable(EWDG_Type *ptr);

/**
 * @brief Initialize the Control function for EWDG
 *
 * @param [in] ptr EWDG base
 * @param [in] config Control Function Configuration
 * @param [in] cnt_src_freq Source frequency for EWDG counter
 *
 * @retval status_invalid_argument Invalid argument was detected
 * @retval status_success No error happened
 */
hpm_stat_t ewdg_init_ctrl_func(EWDG_Type *ptr, ewdg_func_ctrl_config_t *config, uint32_t cnt_src_freq);

/**
 * @brief Initialize the Error function for EWDG
 *
 * @param [in] ptr EWDG base
 * @param [in] config Error Function Configuration
 *
 * @retval status_invalid_argument Invalid argument was detected
 * @retval status_success No error happened
 */
hpm_stat_t ewdg_init_interrupt_reset(EWDG_Type *ptr, ewdg_interrupt_reset_config_t *config);

/**
 * @brief Get default configuration for EWDG
 * @param [in] ptr EWDG base
 * @param [out] config EWDG Configuration
 */
void ewdg_get_default_config(EWDG_Type *ptr, ewdg_config_t *config);

/**
 * @brief Initialize the EWDG module
 *
 * @param [in] ptr EWDG base
 * @param [in] config EWDG configuration
 *
 * @retval status_invalid_argument Invalid argument was detected
 * @retval status_success No error happened
 */
hpm_stat_t ewdg_init(EWDG_Type *ptr, ewdg_config_t *config);

/**
 * @brief Unlock the write to refresh register
 *
 * @param [in] ptr EWDG base
 *
 * @retval status_invalid_argument Invalid argument was detected
 * @retval status_success No error happened
 */
hpm_stat_t ewdg_unlock_refresh(EWDG_Type *ptr);

/**
 * @brief Refresh EWDG
 *
 * @param [in] ptr EWDG base
 *
 * @retval status_invalid_argument Invalid argument was detected
 * @retval status_success No error happened
 */
hpm_stat_t ewdg_refresh(EWDG_Type *ptr);

/**
 * @brief Get the Divided Counter Clock Frequency for EWDG
 *
 * @param [in] ptr EWDG base
 * @param [in] src_clk_freq Source clock of the Counter clock
 *
 * @return divided Counter clock Frequency
 */
uint32_t ewdg_get_count_clock_freq(EWDG_Type *ptr, uint32_t src_clk_freq);

/**
 * @brief Convert the timeout in terms of microseconds to the timeout in terms of timeout ticks
 *
 * @param [in] src_clk_freq Clock Frequency of the counter clock source
 * @param [in] timeout_us Timeout in terms of microseconds
 *
 * @return timeout in terms of counter clock ticks
 */
uint64_t ewdg_convert_timeout_us_to_timeout_ticks(uint32_t src_clk_freq, uint32_t timeout_us);

/**
 * @brief Convert the timeout in terms of timeout ticks to the timeout in terms of microseconds
 *
 * @param [in] ptr EWDG base
 * @param [in] src_clk_freq Clock Frequency of the counter clock source
 * @param [in] timeout_ticks Timeout in terms of ticks
 *
 * @return timeout in terms of counter clock ticks
 */
uint32_t ewdg_convert_timeout_ticks_to_timeout_us(EWDG_Type *ptr, uint32_t src_clk_freq, uint32_t timeout_ticks);

/**
 * @brief Enable EWDG interrupt
 * @param [in] ptr EWDG base
 * @param [in] mask Interrupt Mask, valid value refer to @ref ewdg_interrupt
 */
void ewdg_enable_interrupt(EWDG_Type *ptr, uint32_t mask);

/**
 * @brief Disable EWDG interrupt
 * @param [in] ptr EWDG base
 * @param [in] mask Interrupt Mask, valid value refer to @ref ewdg_interrupt
 */
void ewdg_disable_interrupt(EWDG_Type *ptr, uint32_t mask);

/**
 * @brief Enable EWDG Reset
 * @param [in] ptr EWDG base
 * @param [in] mask Reset Mask, valid value refer to @ref ewdg_reset_source
 */
void ewdg_enable_reset(EWDG_Type *ptr, uint32_t mask);

/**
 * @brief Disable EWDG Reset
 * @param [in] ptr EWDG base
 * @param [in] mask Reset Mask, valid value refer to @ref ewdg_reset_source
 */
void ewdg_disable_reset(EWDG_Type *ptr, uint32_t mask);

/**
 * @brief Switch the EWDG clock source
 * @param [in] ptr EWDG base
 * @param [in] clk_sel Clock source selection for EWDG counter
 */
void ewdg_switch_clock_source(EWDG_Type *ptr, ewdg_cnt_clk_sel_t clk_sel);


#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* HPM_EWDG_DRV_H */
