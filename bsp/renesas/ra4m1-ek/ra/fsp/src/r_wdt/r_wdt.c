/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_wdt.h"
#include "bsp_api.h"
#include "bsp_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define WDT_OPEN                         (0X00574454ULL)

/* On multi core MCU, core0 uses WDT0 settings on OFS0, and core1 uses WDT1 settings on OFS3*/
#if 1 == BSP_CFG_CPU_CORE              // Core1
 #ifdef BSP_CFG_OPTION_SETTING_OFS3_SEC
  #define BSP_CFG_OPTION_SETTING_OFSX    BSP_CFG_OPTION_SETTING_OFS3_SEC
 #else
  #define BSP_CFG_OPTION_SETTING_OFSX    BSP_CFG_OPTION_SETTING_OFS3
 #endif
 #define R_WDTX                          R_WDT1
#else
 #define BSP_CFG_OPTION_SETTING_OFSX     BSP_CFG_OPTION_SETTING_OFS0
 #define R_WDTX                          R_WDT
#endif

/* Lookup functions for WDT settings.  Using function like macro for stringification. */
#define WDT_PRV_OFSX_SETTING_GET(setting)    (((uint32_t) BSP_CFG_OPTION_SETTING_OFSX >> \
                                               WDT_PRV_OFSX_ ## setting ## _BIT) & WDT_PRV_OFSX_ ## setting ## _MASK);
#define WDT_PRV_WDTCR_SETTING_GET(setting,                                                    \
                                  wdtcr)     (((wdtcr >> WDT_PRV_WDTCR_ ## setting ## _BIT) & \
                                               WDT_PRV_WDTCR_ ## setting ## _MASK));
#define WDT_PRV_WDTCR_SETTING_SET(setting,                                                    \
                                  value)     ((value & WDT_PRV_WDTCR_ ## setting ## _MASK) << \
                                              WDT_PRV_WDTCR_ ## setting ## _BIT);

/* OFS0/OFS3 register settings. */
#define WDT_PRV_OFSX_AUTO_START_BIT          (17)
#define WDT_PRV_OFSX_TIMEOUT_BIT             (18)
#define WDT_PRV_OFSX_CLOCK_DIVISION_BIT      (20)
#define WDT_PRV_OFSX_WINDOW_END_BIT          (24)
#define WDT_PRV_OFSX_WINDOW_START_BIT        (26)
#define WDT_PRV_OFSX_NMI_REQUEST_BIT         (28)
#define WDT_PRV_OFSX_RESET_CONTROL_BIT       (28)
#define WDT_PRV_OFSX_STOP_CONTROL_BIT        (30)

#define WDT_PRV_OFSX_AUTO_START_MASK         (0x1U) // Bit 17
#define WDT_PRV_OFSX_TIMEOUT_MASK            (0x3U) // Bits 18-19
#define WDT_PRV_OFSX_CLOCK_DIVISION_MASK     (0xFU) // Bits 20-23
#define WDT_PRV_OFSX_WINDOW_END_MASK         (0x3U) // Bits 24-25
#define WDT_PRV_OFSX_WINDOW_START_MASK       (0x3U) // Bits 26-27
#define WDT_PRV_OFSX_NMI_REQUEST_MASK        (0x1U) // Bit 28
#define WDT_PRV_OFSX_RESET_CONTROL_MASK      (0x1U) // Bit 28
#define WDT_PRV_OFSX_STOP_CONTROL_MASK       (0x1U) // Bit 30
#define WDT_PRV_NMI_EN_MASK                  (0x2)

/* WDT register settings. */
#define WDT_PRV_WDTSR_COUNTER_MASK           (0x3FFFU)
#define WDT_PRV_WDTSR_FLAGS_MASK             (0xC000U)

#define WDT_PRV_WDTCR_TIMEOUT_BIT            (0)
#define WDT_PRV_WDTCR_CLOCK_DIVISION_BIT     (4)
#define WDT_PRV_WDTCR_WINDOW_END_BIT         (8)
#define WDT_PRV_WDTCR_WINDOW_START_BIT       (12)

#define WDT_PRV_WDTRCR_RESET_CONTROL_BIT     (7)
#define WDT_PRV_WDTCSTPR_STOP_CONTROL_BIT    (7)

#define WDT_PRV_WDTCR_TIMEOUT_MASK           (0x3U) // Bits 0-1
#define WDT_PRV_WDTCR_CLOCK_DIVISION_MASK    (0xFU) // Bits 4-7
#define WDT_PRV_WDTCR_WINDOW_END_MASK        (0x3U) // Bits 8-9
#define WDT_PRV_WDTCR_WINDOW_START_MASK      (0x3U) // Bits 12-13

/* Macros for start mode and NMI support. */
#if (BSP_CFG_OPTION_SETTING_OFSX >> WDT_PRV_OFSX_AUTO_START_BIT) & WDT_PRV_OFSX_AUTO_START_MASK
 #define WDT_PRV_REGISTER_START_MODE         (1)
 #define WDT_PRV_NMI_SUPPORTED               (WDT_CFG_REGISTER_START_NMI_SUPPORTED)
#else

/* Auto start mode */
 #define WDT_PRV_REGISTER_START_MODE         (0)
 #if (BSP_CFG_OPTION_SETTING_OFSX >> WDT_PRV_OFSX_NMI_REQUEST_BIT) & WDT_PRV_OFSX_NMI_REQUEST_MASK
  #define WDT_PRV_NMI_SUPPORTED              (0)
 #else
  #define WDT_PRV_NMI_SUPPORTED              (1)
 #endif
#endif

/* Refresh register values */
#define WDT_PRV_REFRESH_STEP_1               (0U)
#define WDT_PRV_REFRESH_STEP_2               (0xFFU)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * wdt_prv_ns_callback)(wdt_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile wdt_prv_ns_callback)(wdt_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void r_wdt_nmi_internal_callback(bsp_grp_irq_t irq);

static uint32_t r_wdt_clock_divider_get(wdt_clock_division_t division);

static fsp_err_t r_wdt_parameter_checking(wdt_instance_ctrl_t * const p_instance_ctrl, wdt_cfg_t const * const p_cfg);

#if WDT_PRV_NMI_SUPPORTED
static void r_wdt_nmi_initialize(wdt_instance_ctrl_t * const p_instance_ctrl, wdt_cfg_t const * const p_cfg);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

static const uint8_t g_wdtcr_timeout[] =
{
    0xFFU,                             // WDTCR value for WDT_TIMEOUT_128 (not supported by WDT).
    0xFFU,                             // WDTCR value for WDT_TIMEOUT_512 (not supported by WDT).
    0x00U,                             // WDTCR value for WDT_TIMEOUT_1024.
    0xFFU,                             // WDTCR value for WDT_TIMEOUT_2048 (not supported by WDT).
    0x01U,                             // WDTCR value for WDT_TIMEOUT_4096.
    0x02U,                             // WDTCR value for WDT_TIMEOUT_8192.
    0x03U,                             // WDTCR value for WDT_TIMEOUT_16384.
};

/* Convert WDT/IWDT timeout value to an integer */
static const uint32_t g_wdt_timeout[] =
{
    128U,
    512U,
    1024U,
    2048U,
    4096U,
    8192U,
    16384U
};

/* Converts WDT division enum to log base 2 of the division value, used to shift the PCLKB frequency. */
static const uint8_t g_wdt_division_lookup[] =
{
    0U,                                // log base 2(1)    = 0
    2U,                                // log base 2(4)    = 2
    4U,                                // log base 2(16)   = 4
    5U,                                // log base 2(32)   = 5
    6U,                                // log base 2(64)   = 6
    8U,                                // log base 2(256)  = 8
    9U,                                // log base 2(512)  = 9
    11U,                               // log base 2(2048) = 11
    13U,                               // log base 2(8192) = 13
};

/** Global pointer to control structure for use by the NMI callback.  */
static volatile wdt_instance_ctrl_t * gp_wdt_ctrl = NULL;

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/** Watchdog implementation of WDT Driver  */
const wdt_api_t g_wdt_on_wdt =
{
    .open        = R_WDT_Open,
    .refresh     = R_WDT_Refresh,
    .statusGet   = R_WDT_StatusGet,
    .statusClear = R_WDT_StatusClear,
    .counterGet  = R_WDT_CounterGet,
    .timeoutGet  = R_WDT_TimeoutGet,
    .callbackSet = R_WDT_CallbackSet,
};

/*******************************************************************************************************************//**
 * @addtogroup WDT WDT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configure the WDT in register start mode. In auto-start_mode the NMI callback can be registered. Implements
 * @ref wdt_api_t::open.
 *
 * This function should only be called once as WDT configuration registers can only be written to once so subsequent
 * calls will have no effect.
 *
 * Example:
 * @snippet r_wdt_example.c R_WDT_Open
 *
 * @retval FSP_SUCCESS              WDT successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_INVALID_STATE    The security state of the NMI and the module do not match.
 *
 * @note In auto start mode the only valid configuration option is for registering the callback for the NMI ISR if
 *       NMI output has been selected.
 **********************************************************************************************************************/
fsp_err_t R_WDT_Open (wdt_ctrl_t * const p_ctrl, wdt_cfg_t const * const p_cfg)
{
    wdt_instance_ctrl_t * p_instance_ctrl = (wdt_instance_ctrl_t *) p_ctrl;
    fsp_err_t             err;

    /* Check validity of the parameters */
    err = r_wdt_parameter_checking(p_instance_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Configuration only valid when WDT operating in register-start mode. */
#if WDT_PRV_REGISTER_START_MODE

    /* Register-start mode. */

 #if WDT_CFG_REGISTER_START_NMI_SUPPORTED
    if (p_cfg->reset_control == WDT_RESET_CONTROL_NMI)
    {
        /* Register callback with BSP NMI ISR. */
        r_wdt_nmi_initialize(p_instance_ctrl, p_cfg);
    }

 #else

    /* Eliminate toolchain warning when NMI output is not being used.  */
    FSP_PARAMETER_NOT_USED(r_wdt_nmi_internal_callback);
 #endif

    /* Set the configuration registers in register start mode. */
    R_WDTX->WDTRCR = (uint8_t) (p_cfg->reset_control << WDT_PRV_WDTRCR_RESET_CONTROL_BIT);

    uint32_t wdtcr = WDT_PRV_WDTCR_SETTING_SET(TIMEOUT, (uint16_t) g_wdtcr_timeout[p_cfg->timeout]);
    wdtcr |= WDT_PRV_WDTCR_SETTING_SET(CLOCK_DIVISION, (uint16_t) p_cfg->clock_division);
    wdtcr |= WDT_PRV_WDTCR_SETTING_SET(WINDOW_START, (uint16_t) p_cfg->window_start);
    wdtcr |= WDT_PRV_WDTCR_SETTING_SET(WINDOW_END, (uint16_t) p_cfg->window_end);

    R_WDTX->WDTCR    = (uint16_t) wdtcr;
    R_WDTX->WDTCSTPR = (uint8_t) (p_cfg->stop_control << WDT_PRV_WDTCSTPR_STOP_CONTROL_BIT);
#else

    /* Auto start mode. */
    /* Check for NMI output mode. */
 #if WDT_PRV_NMI_SUPPORTED

    /* Register callback with BSP NMI ISR. */
    r_wdt_nmi_initialize(p_instance_ctrl, p_cfg);
 #else

    /* Eliminate toolchain warning when NMI output is not being used.  */
    FSP_PARAMETER_NOT_USED(r_wdt_nmi_internal_callback);
 #endif
#endif

    p_instance_ctrl->wdt_open = WDT_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Read timeout information for the watchdog timer. Implements @ref wdt_api_t::timeoutGet.
 *
 * @retval FSP_SUCCESS              WDT timeout information retrieved successfully.
 * @retval FSP_ERR_ASSERTION        Null Pointer.
 * @retval FSP_ERR_NOT_OPEN         Instance control block is not initialized.
 **********************************************************************************************************************/
fsp_err_t R_WDT_TimeoutGet (wdt_ctrl_t * const p_ctrl, wdt_timeout_values_t * const p_timeout)
{
#if WDT_CFG_PARAM_CHECKING_ENABLE
    wdt_instance_ctrl_t * p_instance_ctrl = (wdt_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_timeout);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(WDT_OPEN == p_instance_ctrl->wdt_open, FSP_ERR_NOT_OPEN);
#endif
    FSP_PARAMETER_NOT_USED(p_ctrl);
    uint32_t             shift;
    uint32_t             index;
    uint32_t             timeout = 0;
    wdt_clock_division_t clock_division;
#if WDT_PRV_REGISTER_START_MODE

    /* Read the configuration of the watchdog */
    uint32_t wdtcr = R_WDTX->WDTCR;
    clock_division = (wdt_clock_division_t) WDT_PRV_WDTCR_SETTING_GET(CLOCK_DIVISION, wdtcr);
    timeout        = WDT_PRV_WDTCR_SETTING_GET(TIMEOUT, wdtcr);
#else                                  /* Auto start mode */
    clock_division = (wdt_clock_division_t) WDT_PRV_OFSX_SETTING_GET(CLOCK_DIVISION);
    timeout        = WDT_PRV_OFSX_SETTING_GET(TIMEOUT);
#endif

    /* Get timeout value from WDTCR register. */
    for (index = 0U; index < (sizeof(g_wdtcr_timeout)); index++)
    {
        if (g_wdtcr_timeout[index] == timeout)
        {
            p_timeout->timeout_clocks = g_wdt_timeout[index];
        }
    }

    /* Get the frequency of the clock supplying the watchdog */
    uint32_t pckb_frequency = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKB);
    shift = r_wdt_clock_divider_get(clock_division);

    p_timeout->clock_frequency_hz = pckb_frequency >> shift;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Refresh the watchdog timer. Implements @ref wdt_api_t::refresh.
 *
 * In addition to refreshing the watchdog counter this function can be used to start the counter in register start mode.
 *
 * Example:
 * @snippet r_wdt_example.c R_WDT_Refresh
 *
 * @retval FSP_SUCCESS              WDT successfully refreshed.
 * @retval FSP_ERR_ASSERTION        p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         Instance control block is not initialized.
 *
 * @note This function only returns FSP_SUCCESS. If the refresh fails due to being performed outside of the
 *       permitted refresh period the device will either reset or trigger an NMI ISR to run.
 **********************************************************************************************************************/
fsp_err_t R_WDT_Refresh (wdt_ctrl_t * const p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);

#if WDT_CFG_PARAM_CHECKING_ENABLE
    wdt_instance_ctrl_t * p_instance_ctrl = (wdt_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(WDT_OPEN == p_instance_ctrl->wdt_open, FSP_ERR_NOT_OPEN);
#endif

    R_WDTX->WDTRR = WDT_PRV_REFRESH_STEP_1;
    R_WDTX->WDTRR = WDT_PRV_REFRESH_STEP_2;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Read the WDT status flags. Implements @ref wdt_api_t::statusGet.
 *
 * Indicates both status and error conditions.
 *
 * Example:
 * @snippet r_wdt_example.c R_WDT_StatusGet
 *
 * @retval FSP_SUCCESS              WDT status successfully read.
 * @retval FSP_ERR_ASSERTION        Null pointer as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Instance control block is not initialized.
 * @retval FSP_ERR_UNSUPPORTED      This function is only valid if the watchdog generates an NMI when an error occurs.
 *
 * @note When the WDT is configured to output a reset on underflow or refresh error reading the status and error flags
 *       serves no purpose as they will always indicate that no underflow has occurred and there is no refresh error.
 *       Reading the status and error flags is only valid when interrupt request output is enabled.
 **********************************************************************************************************************/
fsp_err_t R_WDT_StatusGet (wdt_ctrl_t * const p_ctrl, wdt_status_t * const p_status)
{
#if WDT_PRV_NMI_SUPPORTED
 #if WDT_CFG_PARAM_CHECKING_ENABLE
    wdt_instance_ctrl_t * p_instance_ctrl = (wdt_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_status);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(WDT_OPEN == p_instance_ctrl->wdt_open, FSP_ERR_NOT_OPEN);
 #else
    FSP_PARAMETER_NOT_USED(p_ctrl);
 #endif

    /* Check for refresh or underflow errors. */
    *p_status = (wdt_status_t) (R_WDTX->WDTSR >> 14);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_status);

    /* This function is only supported when the NMI is used. */
    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Clear the WDT status and error flags. Implements @ref wdt_api_t::statusClear.
 *
 * Example:
 * @snippet r_wdt_example.c R_WDT_StatusClear
 *
 * @retval FSP_SUCCESS              WDT flag(s) successfully cleared.
 * @retval FSP_ERR_ASSERTION        Null pointer as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Instance control block is not initialized.
 * @retval FSP_ERR_UNSUPPORTED      This function is only valid if the watchdog generates an NMI when an error occurs.
 *
 * @note When the WDT is configured to output a reset on underflow or refresh error reading the status and error flags
 *       serves no purpose as they will always indicate that no underflow has occurred and there is no refresh error.
 *       Reading the status and error flags is only valid when interrupt request output is enabled.
 **********************************************************************************************************************/
fsp_err_t R_WDT_StatusClear (wdt_ctrl_t * const p_ctrl, const wdt_status_t status)
{
#if WDT_PRV_NMI_SUPPORTED
    uint16_t value;
    uint16_t read_value;

 #if WDT_CFG_PARAM_CHECKING_ENABLE
    wdt_instance_ctrl_t * p_instance_ctrl = (wdt_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(WDT_OPEN == p_instance_ctrl->wdt_open, FSP_ERR_NOT_OPEN);
 #else
    FSP_PARAMETER_NOT_USED(p_ctrl);
 #endif

    /* Casts to uint16_t to ensure value is handled as unsigned. */
    value = (uint16_t) status;

    /* Write zero to clear flags. */
    value = (uint16_t) ~value;
    value = (uint16_t) (value << 14);

    /* Read back status flags until required flag(s) cleared. */
    /* Flags cannot be cleared until the clock cycle after they are set.  */
    do
    {
        R_WDTX->WDTSR = value;
        read_value    = R_WDTX->WDTSR;

        /* Isolate flags to clear. */
        read_value &= (uint16_t) ((uint16_t) status << 14);
    } while (0U != read_value);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(status);

    /* This function is only supported when the NMI is used. */
    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Read the current count value of the WDT. Implements @ref wdt_api_t::counterGet.
 *
 * Example:
 * @snippet r_wdt_example.c R_WDT_CounterGet
 *
 * @retval FSP_SUCCESS          WDT current count successfully read.
 * @retval FSP_ERR_ASSERTION    Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN     Instance control block is not initialized.
 **********************************************************************************************************************/
fsp_err_t R_WDT_CounterGet (wdt_ctrl_t * const p_ctrl, uint32_t * const p_count)
{
#if WDT_CFG_PARAM_CHECKING_ENABLE
    wdt_instance_ctrl_t * p_instance_ctrl = (wdt_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_count);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(WDT_OPEN == p_instance_ctrl->wdt_open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    *p_count  = (uint32_t) R_WDTX->WDTSR;
    *p_count &= WDT_PRV_WDTSR_COUNTER_MASK;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements wdt_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_WDT_CallbackSet (wdt_ctrl_t * const          p_ctrl,
                             void (                    * p_callback)(wdt_callback_args_t *),
                             void * const                p_context,
                             wdt_callback_args_t * const p_callback_memory)
{
    wdt_instance_ctrl_t * p_instance_ctrl = (wdt_instance_ctrl_t *) p_ctrl;

#if WDT_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(WDT_OPEN == p_instance_ctrl->wdt_open, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if WDT_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    wdt_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                      CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_instance_ctrl->p_callback = callback_is_secure ? p_callback :
                                  (void (*)(wdt_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_instance_ctrl->p_callback = p_callback;
#endif
    p_instance_ctrl->p_context         = p_context;
    p_instance_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup WDT)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Internal NMI ISR callback which calls the user provided callback passing the context provided by the user.
 *
 * @param[in]    irq        IRQ which has triggered the NMI interrupt.
 **********************************************************************************************************************/
static void r_wdt_nmi_internal_callback (bsp_grp_irq_t irq)
{
    FSP_PARAMETER_NOT_USED(irq);

    /* Call user registered callback */
    if (NULL != gp_wdt_ctrl)
    {
        if (NULL != gp_wdt_ctrl->p_callback)
        {
            wdt_callback_args_t args;

            /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
             * stored in non-secure memory so they can be accessed by a non-secure callback function. */
            wdt_callback_args_t * p_args = gp_wdt_ctrl->p_callback_memory;
            if (NULL == p_args)
            {
                /* Store on stack */
                p_args = &args;
            }
            else
            {
                /* Save current arguments on the stack in case this is a nested interrupt. */
                args = *p_args;
            }

            p_args->p_context = gp_wdt_ctrl->p_context;

#if BSP_TZ_SECURE_BUILD

            /* p_callback can point to a secure function or a non-secure function. */
            if (!cmse_is_nsfptr(gp_wdt_ctrl->p_callback))
            {
                /* If p_callback is secure, then the project does not need to change security state. */
                gp_wdt_ctrl->p_callback(p_args);
            }
            else
            {
                /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
                wdt_prv_ns_callback p_callback = (wdt_prv_ns_callback) (gp_wdt_ctrl->p_callback);
                p_callback(p_args);
            }

#else

            /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
            gp_wdt_ctrl->p_callback(p_args);
#endif
            if (NULL != gp_wdt_ctrl->p_callback_memory)
            {
                /* Restore callback memory in case this is a nested interrupt. */
                *gp_wdt_ctrl->p_callback_memory = args;
            }
        }
    }
}

/*******************************************************************************************************************//**
 * Gets clock division shift value.
 *
 * @param[in]   division     Right shift value used to divide clock frequency.
 **********************************************************************************************************************/
static uint32_t r_wdt_clock_divider_get (wdt_clock_division_t division)
{
    uint32_t shift;

    if (WDT_CLOCK_DIVISION_128 == division)
    {
        shift = 7U;                    /* log base 2(128) = 7 */
    }
    else
    {
        shift = g_wdt_division_lookup[division];
    }

    return shift;
}

/*******************************************************************************************************************//**
 * Initialize the NMI.
 *
 * @param[in]    p_instance_ctrl   Pointer to instance control structure
 * @param[in]    p_cfg             Pointer to configuration structure
 **********************************************************************************************************************/
#if WDT_PRV_NMI_SUPPORTED
static void r_wdt_nmi_initialize (wdt_instance_ctrl_t * const p_instance_ctrl, wdt_cfg_t const * const p_cfg)
{
    /* Initialize global pointer to WDT for NMI callback use.  */
    gp_wdt_ctrl = p_instance_ctrl;

    /* NMI output mode. */
    R_BSP_GroupIrqWrite(BSP_GRP_IRQ_WDT_ERROR, r_wdt_nmi_internal_callback);

    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;

    /* Enable the WDT underflow/refresh error interrupt (will generate an NMI). NMIER bits cannot be cleared after reset,
     * so no need to read-modify-write. */
    R_ICU->NMIER = R_ICU_NMIER_WDTEN_Msk;
}

#endif

/*******************************************************************************************************************//**
 * Parameter checking function for WDT Open
 *
 * @param[in]    p_instance_ctrl   Pointer to instance control structure
 * @param[in]    p_cfg             Pointer to configuration structure
 *
 * @retval FSP_SUCCESS              WDT successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_INVALID_STATE    The security state of the NMI and the module do not match.
 **********************************************************************************************************************/
static fsp_err_t r_wdt_parameter_checking (wdt_instance_ctrl_t * const p_instance_ctrl, wdt_cfg_t const * const p_cfg)
{
#if WDT_CFG_PARAM_CHECKING_ENABLE

    /* Check that control and config structure pointers are valid. */
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(WDT_OPEN != p_instance_ctrl->wdt_open, FSP_ERR_ALREADY_OPEN);

    /* Ensure this module is in the same security state as the NMI */
 #if defined(BSP_TZ_NONSECURE_BUILD) && BSP_TZ_NONSECURE_BUILD
    FSP_ERROR_RETURN(SCB->AIRCR & SCB_AIRCR_BFHFNMINS_Msk, FSP_ERR_INVALID_STATE);
 #elif defined(BSP_TZ_SECURE_BUILD) && BSP_TZ_SECURE_BUILD
    FSP_ERROR_RETURN(!(SCB->AIRCR & SCB_AIRCR_BFHFNMINS_Msk), FSP_ERR_INVALID_STATE);
 #endif

    /* Check timeout parameter is supported by WDT. */

    /* Enum checking is done here because some enums in wdt_timeout_t are not supported by the WDT peripheral (they are
     * included for other implementations of the watchdog interface). */
    FSP_ASSERT((p_cfg->timeout == WDT_TIMEOUT_1024) || (p_cfg->timeout == WDT_TIMEOUT_4096) || \
               (p_cfg->timeout == WDT_TIMEOUT_8192) || (p_cfg->timeout == WDT_TIMEOUT_16384));

 #if WDT_PRV_REGISTER_START_MODE

    /* Register-start mode. */

  #if WDT_CFG_REGISTER_START_NMI_SUPPORTED

    /* Register callback with BSP NMI ISR. */
    if (p_cfg->reset_control == WDT_RESET_CONTROL_NMI)
    {
        FSP_ASSERT(NULL != p_cfg->p_callback);
    }
    else
    {
        FSP_ASSERT(NULL == p_cfg->p_callback);
    }

  #else
    FSP_ASSERT(p_cfg->reset_control == WDT_RESET_CONTROL_RESET);
  #endif
 #else

    /* Auto start mode. */

  #if WDT_PRV_NMI_SUPPORTED

    /* NMI output mode. */
    FSP_ASSERT(NULL != p_cfg->p_callback);
  #else
    FSP_ASSERT(NULL == p_cfg->p_callback);
  #endif
 #endif
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(p_cfg);
#endif

    return FSP_SUCCESS;
}
