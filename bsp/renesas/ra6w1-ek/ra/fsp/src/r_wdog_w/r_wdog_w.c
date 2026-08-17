/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_wdog_w.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define WDOG_W_OPEN                         (0x00574454ULL)

#define WDOG_W_NMI_ON_EXPIRATION            (0U)
#define WDOG_W_RESET_ON_EXPIRATION          (1U)

/**
 * At least 3 low power clock cycles required for the new value to be synchronized. In the worst case scenario this is equal to 93.75 us.
 * Several additional PCLK cycles are required as well. In the worst case scenario, PCLK runs at 250KHz (i.e. 4us clock period).
 */
#define WDOG_W_PRV_SYNC_DELAY_US            (10) // 10us per sync delay iteration
#define WDOG_W_PRV_WAIT_TIMEOUT_TICK        (13) // Up to 130us delay for synchronization

#if defined(WDTSYS_WDTSYS_REG_WDTSYS_VAL_Msk)
 #define WDOG_W_REG                         WDTSYS->WDTSYS_REG
 #define WDOG_W_VAL_FIELD                   WDTSYS->WDTSYS_REG_b.WDTSYS_VAL
 #define WDOG_W_VAL_NEG_FIELD               WDTSYS->WDTSYS_REG_b.WDTSYS_VAL_NEG
#elif defined(SYS_WDOG_WATCHDOG_REG_WDOG_VAL_Msk)
 #define WDOG_W_REG                         SYS_WDOG->WATCHDOG_REG
 #define WDOG_W_VAL_FIELD                   SYS_WDOG->WATCHDOG_REG_b.WDOG_VAL
 #define WDOG_W_VAL_NEG_FIELD               SYS_WDOG->WATCHDOG_REG_b.WDOG_VAL_NEG
#endif
#if defined(WDTSYS_WDTSYS_CTRL_REG_WDTSYS_NMI_RST_Msk)
 #define WDOG_W_NMI_RST_FIELD               WDTSYS->WDTSYS_CTRL_REG_b.WDTSYS_NMI_RST
 #define WDOG_W_WRITE_BUSY_FIELD            WDTSYS->WDTSYS_CTRL_REG_b.WDTSYS_WRITE_BUSY
 #define WDOG_W_FREEZE_ENABLE               WDTSYS->WDTSYS_CTRL_REG_b.WDTSYS_FREEZE_EN
 #define WDOG_W_WINDOWED_MODE_ENABLE        WDTSYS->WDTSYS_CTRL_REG_b.WDTSYS_WINDOW_EN
#elif defined(SYS_WDOG_WATCHDOG_CTRL_REG_NMI_RST_Msk)
 #define WDOG_W_NMI_RST_FIELD               SYS_WDOG->WATCHDOG_CTRL_REG_b.NMI_RST
 #define WDOG_W_WRITE_BUSY_FIELD            SYS_WDOG->WATCHDOG_CTRL_REG_b.WRITE_BUSY
 #define WDOG_W_FREEZE_ENABLE               SYS_WDOG->WATCHDOG_CTRL_REG_b.WDOG_FREEZE_EN
#endif
#if defined(WDTSYS_WDTSYS_WINDOW_HIGH_REG_WDTSYS_HIGH_THR_Msk)
 #define WDOG_W_WINDOWED_MODE_HIGH_THRES    WDTSYS->WDTSYS_WINDOW_HIGH_REG
#endif
#if defined(WDTSYS_WDTSYS_WINDOW_LOW_REG_WDTSYS_LOW_THR_Msk)
 #define WDOG_W_WINDOWED_MODE_LOW_THRES     WDTSYS->WDTSYS_WINDOW_LOW_REG
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * wdt_prv_ns_callback)(wdt_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile wdt_prv_ns_callback)(wdt_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Public function prototypes
 **********************************************************************************************************************/

#if BSP_MCU_GROUP_RA6W1
void bsp_wdt_freeze_cfg(void);

#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void r_wdog_w_nmi_internal_callback(const uint32_t * p_exception_args);

static fsp_err_t r_wdog_w_parameter_checking(wdog_w_instance_ctrl_t * const p_instance_ctrl,
                                             wdt_cfg_t const * const        p_cfg);
static void r_wdog_w_freeze(void);
static void r_wdog_w_unfreeze(void);

#if WDOG_W_CFG_NMI_SUPPORTED
static void r_wdog_w_nmi_initialize(wdog_w_instance_ctrl_t * const p_instance_ctrl, wdt_cfg_t const * const p_cfg);

#endif

static fsp_err_t r_wdog_w_not_busy_wait(void);

static fsp_err_t r_wdog_w_timeout_write(uint32_t timeout);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** Global pointer to control structure for use by the NMI callback.  */
static volatile wdog_w_instance_ctrl_t * gp_wdt_ctrl = NULL;

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/** Watchdog implementation of WDOG_W Driver  */
const wdt_api_t g_wdt_on_wdog_w =
{
    .open        = R_WDOG_W_Open,
    .refresh     = R_WDOG_W_Refresh,
    .statusGet   = R_WDOG_W_StatusGet,
    .statusClear = R_WDOG_W_StatusClear,
    .counterGet  = R_WDOG_W_CounterGet,
    .timeoutGet  = R_WDOG_W_TimeoutGet,
    .callbackSet = R_WDOG_W_CallbackSet,
};

/*******************************************************************************************************************//**
 * @addtogroup WDOG_W
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configure the watchdog timer. Implements @ref wdt_api_t::open.
 *
 * This function should only be called once. Subsequent calls will have no effect.
 *
 * Example:
 * @snippet r_wdog_w_example.c R_WDOG_W_Open
 *
 * @retval FSP_SUCCESS              WDT successfully configured.
 * @retval FSP_ERR_ASSERTION        Null pointer, or one or more configuration options is invalid.
 * @retval FSP_ERR_ALREADY_OPEN     Module is already open.  This module can only be opened once.
 * @retval FSP_ERR_INVALID_STATE    The security state of the NMI and the module do not match.
 **********************************************************************************************************************/
fsp_err_t R_WDOG_W_Open (wdt_ctrl_t * const p_ctrl, wdt_cfg_t const * const p_cfg)
{
    wdog_w_instance_ctrl_t * p_instance_ctrl = (wdog_w_instance_ctrl_t *) p_ctrl;
    fsp_err_t                err;

    /* Check validity of the parameters */
    err = r_wdog_w_parameter_checking(p_instance_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    p_instance_ctrl->timeout = p_cfg->timeout;

#ifdef CRG_TOP_CLK_CTRL_REG_WDTSYS_CLK_SEL_Msk

    /* Apply clock source settings */
    CRG_TOP->CLK_CTRL_REG_b.WDTSYS_CLK_SEL = ((wdog_w_extended_cfg_t *) p_cfg->p_extend)->wdt_clk_src;
#endif

    /* Stop the watchdog, in case it is running. It is possible only for NMI. */
    WDOG_W_FREEZE_ENABLE = 1;
    R_BSP_PeripheralFreeze(BSP_FREEZE_PERIPHERAL_SYS_WDOG);

#if WDOG_W_CFG_NMI_SUPPORTED
    if (WDT_RESET_CONTROL_NMI == p_cfg->reset_control)
    {
        /* Register callback with BSP NMI ISR and set NMI mode. */
        r_wdog_w_nmi_initialize(p_instance_ctrl, p_cfg);
    }

#else

    /* Eliminate toolchain warning when NMI output is not being used.  */
    FSP_PARAMETER_NOT_USED(r_wdog_w_nmi_internal_callback);
#endif

    if (WDT_RESET_CONTROL_RESET == p_cfg->reset_control)
    {
        /*
         * Defer setting the NMI_RST field until the first call to R_WDOG_W_Refresh(),
         * to avoid immediate start of the countdown. The watchdog cannot be frozen once it is set
         * to trigger a reset on expiration.
         */
    }

#ifdef WDTSYS_WDTSYS_CTRL_REG_WDTSYS_WINDOW_EN_Msk
    if (((p_cfg->window_start < p_cfg->timeout) || (p_cfg->window_end > 0)) &&
        (p_cfg->window_start > p_cfg->window_end))
    {
        WDOG_W_WINDOWED_MODE_LOW_THRES  = p_cfg->window_end;
        WDOG_W_WINDOWED_MODE_HIGH_THRES = p_cfg->window_start;
        WDOG_W_WINDOWED_MODE_ENABLE     = 1;
    }
    else
    {
        WDOG_W_WINDOWED_MODE_ENABLE = 0;
    }
#endif

    p_instance_ctrl->p_cfg    = p_cfg;
    p_instance_ctrl->wdt_open = WDOG_W_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Read timeout information for the watchdog timer. Implements @ref wdt_api_t::timeoutGet.
 *
 * @retval FSP_SUCCESS              WDT timeout information retrieved successfully.
 * @retval FSP_ERR_ASSERTION        Null Pointer.
 * @retval FSP_ERR_NOT_OPEN         Instance control block is not initialized.
 **********************************************************************************************************************/
fsp_err_t R_WDOG_W_TimeoutGet (wdt_ctrl_t * const p_ctrl, wdt_timeout_values_t * const p_timeout)
{
    const wdog_w_instance_ctrl_t * p_instance_ctrl = (wdog_w_instance_ctrl_t *) p_ctrl;

#if WDOG_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_timeout);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(WDOG_W_OPEN == p_instance_ctrl->wdt_open, FSP_ERR_NOT_OPEN);
#endif

    p_timeout->timeout_clocks     = p_instance_ctrl->timeout;
    p_timeout->clock_frequency_hz = BSP_FEATURE_WDT_CLOCK_FREQUENCY;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set timeout value.
 *
 * @retval FSP_SUCCESS              WDT timeout value is set successfully.
 * @retval FSP_ERR_ASSERTION        Null Pointer.
 * @retval FSP_ERR_NOT_OPEN         Instance control block is not initialized.
 * @retval FSP_ERR_INVALID_SIZE     WDT timeout value is out of range.
 **********************************************************************************************************************/
fsp_err_t R_WDOG_W_TimeoutSet (wdt_ctrl_t * p_ctrl, uint32_t timeout)
{
    wdog_w_instance_ctrl_t * p_instance_ctrl = (wdog_w_instance_ctrl_t *) p_ctrl;

#if WDOG_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(WDOG_W_OPEN == p_instance_ctrl->wdt_open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN((WDOG_W_TIMEOUT_MIN <= timeout) && (WDOG_W_TIMEOUT_MAX >= timeout), FSP_ERR_INVALID_SIZE);
#endif

    /* Set the timeout value */
    p_instance_ctrl->timeout = timeout;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Refresh the watchdog timer. Implements @ref wdt_api_t::refresh.
 *
 * In addition to refreshing the watchdog counter this function can be used to start the counter.
 *
 * Example:
 * @snippet r_wdog_w_example.c R_WDOG_W_Refresh
 *
 * @retval FSP_SUCCESS              WDT successfully refreshed.
 * @retval FSP_ERR_ASSERTION        p_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN         Instance control block is not initialized.
 * @retval FSP_ERR_IN_USE           The watchdog is busy writing and the count value cannot be refreshed.
 *
 * @note When windowed mode is used: a) if the refresh is attempted before the high threshold is reached, nothing happens;
 *                                   b) if the refresh is attempted after the low threshold is reached, a reset is triggered.
 * @note This function reloads the watchdog timer counter value with the timeout period configured by Open.
 **********************************************************************************************************************/
fsp_err_t R_WDOG_W_Refresh (wdt_ctrl_t * const p_ctrl)
{
    fsp_err_t err;
    const wdog_w_instance_ctrl_t * p_instance_ctrl = (wdog_w_instance_ctrl_t *) p_ctrl;

#if WDOG_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(WDOG_W_OPEN == p_instance_ctrl->wdt_open, FSP_ERR_NOT_OPEN);
#endif

    err = r_wdog_w_timeout_write(p_instance_ctrl->timeout);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_IN_USE);

    if (WDT_RESET_CONTROL_RESET == p_instance_ctrl->p_cfg->reset_control)
    {
        /* Reset mode, the countdown starts immediately when NMI_RST is set to 1 and NMI_RST cannot be cleared. */
        WDOG_W_NMI_RST_FIELD = WDOG_W_RESET_ON_EXPIRATION;
    }
    else
    {
        /* NMI mode, NMI_RST is 0 already, only need to unfreeze the counter. */
        R_BSP_PeripheralUnFreeze(BSP_FREEZE_PERIPHERAL_SYS_WDOG);
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Read the WDT status flags. Implements @ref wdt_api_t::statusGet.
 *
 * Indicates both status and error conditions.
 *
 * Example:
 * @snippet r_wdog_w_example.c R_WDOG_W_StatusGet
 *
 * @retval FSP_SUCCESS              WDT status successfully read.
 * @retval FSP_ERR_ASSERTION        Null pointer as a parameter.
 * @retval FSP_ERR_NOT_OPEN         Instance control block is not initialized.
 * @retval FSP_ERR_UNSUPPORTED      This function is only valid if the watchdog generates an NMI when an error occurs.
 *
 * @note When the WDT is configured to output a reset on underflow or refresh error reading the status serves no purpose
 *       as they will always indicate that no underflow has occurred and there is no refresh error.
 *       Reading the status and error flags is only valid when NMI is enabled.
 **********************************************************************************************************************/
fsp_err_t R_WDOG_W_StatusGet (wdt_ctrl_t * const p_ctrl, wdt_status_t * const p_status)
{
#if WDOG_W_CFG_NMI_SUPPORTED
 #if WDOG_W_CFG_PARAM_CHECKING_ENABLE
    wdog_w_instance_ctrl_t * p_instance_ctrl = (wdog_w_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_status);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(WDOG_W_OPEN == p_instance_ctrl->wdt_open, FSP_ERR_NOT_OPEN);
 #else
    FSP_PARAMETER_NOT_USED(p_ctrl);
 #endif

    if (WDOG_W_VAL_NEG_FIELD)
    {
        *p_status = WDT_STATUS_UNDERFLOW;
    }
    else
    {
        *p_status = WDT_STATUS_NO_ERROR;
    }

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
 * @retval FSP_ERR_UNSUPPORTED      This function is not supported.
 **********************************************************************************************************************/
fsp_err_t R_WDOG_W_StatusClear (wdt_ctrl_t * const p_ctrl, const wdt_status_t status)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(status);

    /* This function is not supported. */
    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Read the current count value of the WDT. Implements @ref wdt_api_t::counterGet.
 *
 * Example:
 * @snippet r_wdog_w_example.c R_WDOG_W_CounterGet
 *
 * @retval FSP_SUCCESS          WDT current count successfully read.
 * @retval FSP_ERR_ASSERTION    Null pointer passed as a parameter.
 * @retval FSP_ERR_NOT_OPEN     Instance control block is not initialized.
 * @retval FSP_ERR_IN_USE       The watchdog is busy writing and the count value cannot be read.
 **********************************************************************************************************************/
fsp_err_t R_WDOG_W_CounterGet (wdt_ctrl_t * const p_ctrl, uint32_t * const p_count)
{
#if WDOG_W_CFG_PARAM_CHECKING_ENABLE
    wdog_w_instance_ctrl_t * p_instance_ctrl = (wdog_w_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_count);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(WDOG_W_OPEN == p_instance_ctrl->wdt_open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    fsp_err_t err = r_wdog_w_not_busy_wait();
    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_IN_USE);

    *p_count = WDOG_W_VAL_FIELD;

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
fsp_err_t R_WDOG_W_CallbackSet (wdt_ctrl_t * const          p_ctrl,
                                void (                    * p_callback)(wdt_callback_args_t *),
                                void * const                p_context,
                                wdt_callback_args_t * const p_callback_memory)
{
    wdog_w_instance_ctrl_t * p_instance_ctrl = (wdog_w_instance_ctrl_t *) p_ctrl;

#if WDOG_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(WDOG_W_OPEN == p_instance_ctrl->wdt_open, FSP_ERR_NOT_OPEN);
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if WDOG_W_CFG_PARAM_CHECKING_ENABLE

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
 * Freeze/unfreeze the watchdog timer.
 *
 * Example:
 * @snippet r_wdog_w_example.c R_WDOG_W_Freeze
 *
 * @retval  FSP_SUCCESS                  Freeze watchdog timer successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NOT_ENABLED          Freezing watchdog timer is not allowed.
 *
 * @note The watchdog timer can only be frozen in the following configurations. Otherwise, this function has no effect.
 *       - NMI Support: Enabled
 *       - Reset Control: NMI Generated
 **********************************************************************************************************************/
fsp_err_t R_WDOG_W_Freeze (wdt_ctrl_t * const p_ctrl, bool freeze)
{
#if WDOG_W_CFG_PARAM_CHECKING_ENABLE
    wdog_w_instance_ctrl_t * p_instance_ctrl = (wdog_w_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(WDOG_W_OPEN == p_instance_ctrl->wdt_open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    if (WDOG_W_NMI_ON_EXPIRATION != WDOG_W_NMI_RST_FIELD)
    {
        FSP_RETURN(FSP_ERR_NOT_ENABLED);
    }

    if (freeze)
    {
        r_wdog_w_freeze();
        r_wdog_w_not_busy_wait();
    }
    else
    {
        r_wdog_w_unfreeze();
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup WDOG_W)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Internal NMI ISR callback which calls the user provided callback passing the context provided by the user.
 *
 * @param[in]    p_exception_args   Pointer to exception arguments.
 **********************************************************************************************************************/
static void r_wdog_w_nmi_internal_callback (const uint32_t * p_exception_args)
{
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

            /* When the input of callback argument is NULL,
             * the pointer to the exception arguments is passed to the callback. */
            if (NULL == gp_wdt_ctrl->p_context)
            {
                p_args->p_context = (void *) p_exception_args;
            }
            else
            {
                p_args->p_context = gp_wdt_ctrl->p_context;
            }

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
 * Initialize the NMI.
 *
 * @param[in]    p_instance_ctrl   Pointer to instance control structure
 * @param[in]    p_cfg             Pointer to configuration structure
 **********************************************************************************************************************/
#if WDOG_W_CFG_NMI_SUPPORTED
static void r_wdog_w_nmi_initialize (wdog_w_instance_ctrl_t * const p_instance_ctrl, wdt_cfg_t const * const p_cfg)
{
    /* Initialize global pointer to WDT for NMI callback use.  */
    gp_wdt_ctrl = p_instance_ctrl;

    R_BSP_GroupNmiWrite(r_wdog_w_nmi_internal_callback);

    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;

    WDOG_W_NMI_RST_FIELD = WDOG_W_NMI_ON_EXPIRATION;

    /* Some devices have multiple NMI sources, we need to enable the one from WDT. */
 #ifdef ICU_ICU_NMIER_REG_ICU_WDTSYS_EN_Msk

    /* Enable watchdog timer as an NMI source. */
    ICU->ICU_NMIER_REG = ICU_ICU_NMIER_REG_ICU_WDTSYS_EN_Msk;
 #endif
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
 * @retval FSP_ERR_INVALID_SIZE     Timeout value setting is out of range.
 **********************************************************************************************************************/
static fsp_err_t r_wdog_w_parameter_checking (wdog_w_instance_ctrl_t * const p_instance_ctrl,
                                              wdt_cfg_t const * const        p_cfg)
{
#if WDOG_W_CFG_PARAM_CHECKING_ENABLE

    /* Check that control and config structure pointers are valid. */
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(WDOG_W_OPEN != p_instance_ctrl->wdt_open, FSP_ERR_ALREADY_OPEN);

    /* Ensure this module is in the same security state as the NMI */
 #if defined(BSP_TZ_NONSECURE_BUILD) && BSP_TZ_NONSECURE_BUILD
    FSP_ERROR_RETURN(SCB->AIRCR & SCB_AIRCR_BFHFNMINS_Msk, FSP_ERR_INVALID_STATE);
 #elif defined(BSP_TZ_SECURE_BUILD) && BSP_TZ_SECURE_BUILD
    FSP_ERROR_RETURN(!(SCB->AIRCR & SCB_AIRCR_BFHFNMINS_Msk), FSP_ERR_INVALID_STATE);
 #endif

    /* Check timeout parameter is within range. */
    FSP_ASSERT((p_cfg->timeout >= WDOG_W_TIMEOUT_MIN) && (p_cfg->timeout <= WDOG_W_TIMEOUT_MAX));

 #if WDOG_W_CFG_NMI_SUPPORTED

    /* Register callback with BSP NMI ISR. */
    if (WDT_RESET_CONTROL_NMI == p_cfg->reset_control)
    {
        FSP_ASSERT(NULL != p_cfg->p_callback);
    }
    else
    {
        FSP_ASSERT(NULL == p_cfg->p_callback);
    }

 #else
    FSP_ASSERT(WDT_RESET_CONTROL_RESET == p_cfg->reset_control);
    FSP_ASSERT(NULL == p_cfg->p_callback);
 #endif
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(p_cfg);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Busy-wait until WRITE_BUSY becomes 0, with a timeout WDOG_W_PRV_WAIT_TIMEOUT_TICK
 **********************************************************************************************************************/
static fsp_err_t r_wdog_w_not_busy_wait (void)
{
    uint8_t timeout;

    for (timeout = WDOG_W_PRV_WAIT_TIMEOUT_TICK; WDOG_W_WRITE_BUSY_FIELD && timeout; timeout--)
    {
        R_BSP_SoftwareDelay(WDOG_W_PRV_SYNC_DELAY_US, BSP_DELAY_UNITS_MICROSECONDS);
    }

    FSP_ERROR_RETURN((timeout > 0) || !WDOG_W_WRITE_BUSY_FIELD, FSP_ERR_IN_USE);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Write the watchdog counter value.
 *
 * @param[in]   timeout      The timeout value, in watchdog ticks.
 **********************************************************************************************************************/
static fsp_err_t r_wdog_w_timeout_write (uint32_t timeout)
{
    fsp_err_t err;

    err = r_wdog_w_not_busy_wait();
    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_IN_USE);

    WDOG_W_REG = timeout;

    return r_wdog_w_not_busy_wait();
}

/*******************************************************************************************************************//**
 * Freeze the watchdog timer.
 **********************************************************************************************************************/
static void r_wdog_w_freeze (void)
{
    WDOG_W_FREEZE_ENABLE = 1;
    R_BSP_PeripheralFreeze(BSP_FREEZE_PERIPHERAL_SYS_WDOG);
}

/*******************************************************************************************************************//**
 * Unfreeze the watchdog timer.
 **********************************************************************************************************************/
static void r_wdog_w_unfreeze (void)
{
    WDOG_W_FREEZE_ENABLE = 1;
    R_BSP_PeripheralUnFreeze(BSP_FREEZE_PERIPHERAL_SYS_WDOG);
    WDOG_W_FREEZE_ENABLE = 0;
}

#if BSP_MCU_GROUP_RA6W1
void bsp_wdt_freeze_cfg (void)
{
    /* Stub function - Do not remove !!!
     * This function should be compiled instead of the Weak bsp_wdt_freeze_cfg.
     * Details:
     * WDT is enabled by default.
     * In case wdt module does not include in the project, WDT should be disabled.
     * bsp_wdt_freeze_cfg weak function - will disable WDT in case wdt module is not included.
     * bsp_wdt_freeze_cfg normal function - will do nothing, hence WDT remains enabled in case wdt included. */
}

#endif
