/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#if defined(__ICCARM__)
 #define WEAK_ERROR_ATTRIBUTE
 #define WEAK_INIT_ATTRIBUTE
 #pragma weak fsp_error_log                            = fsp_error_log_internal
 #pragma weak bsp_init                                 = bsp_init_internal
#elif defined(__GNUC__)

 #define WEAK_ERROR_ATTRIBUTE    __attribute__((weak, alias("fsp_error_log_internal")))

 #define WEAK_INIT_ATTRIBUTE     __attribute__((weak, alias("bsp_init_internal")))
#endif

#define FSP_SECTION_VERSION      ".version"

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/** Prototype of initialization function called before main.  This prototype sets the weak association of this
 * function to an internal example implementation. If this function is defined in the application code, the
 * application code version is used. */

void bsp_init(void * p_args) WEAK_INIT_ATTRIBUTE;

void bsp_init_internal(void * p_args); /// Default initialization function

#if ((1 == BSP_CFG_ERROR_LOG) || (1 == BSP_CFG_ASSERT))

/** Prototype of function called before errors are returned in FSP code if BSP_CFG_ERROR_LOG is set to 1.  This
 * prototype sets the weak association of this function to an internal example implementation. */

void fsp_error_log(fsp_err_t err, const char * file, int32_t line) WEAK_ERROR_ATTRIBUTE;

void fsp_error_log_internal(fsp_err_t err, const char * file, int32_t line); /// Default error logger function

#endif

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/* FSP pack version structure. */
static BSP_DONT_REMOVE const fsp_pack_version_t g_fsp_version BSP_PLACE_IN_SECTION (FSP_SECTION_VERSION) =
{
    .version_id_b =
    {
        .minor = FSP_VERSION_MINOR,
        .major = FSP_VERSION_MAJOR,
        .build = FSP_VERSION_BUILD,
        .patch = FSP_VERSION_PATCH
    }
};

/* Public FSP version name. */
static BSP_DONT_REMOVE const uint8_t g_fsp_version_string[] BSP_PLACE_IN_SECTION(FSP_SECTION_VERSION) =
    FSP_VERSION_STRING;

/* Unique FSP version ID. */
static BSP_DONT_REMOVE const uint8_t g_fsp_version_build_string[] BSP_PLACE_IN_SECTION(FSP_SECTION_VERSION) =
    FSP_VERSION_BUILD_STRING;

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Get the FSP version based on compile time macros.
 *
 * @param[out] p_version        Memory address to return version information to.
 *
 * @retval FSP_SUCCESS          Version information stored.
 * @retval FSP_ERR_ASSERTION    The parameter p_version is NULL.
 **********************************************************************************************************************/
fsp_err_t R_FSP_VersionGet (fsp_pack_version_t * const p_version)
{
#if BSP_CFG_PARAM_CHECKING_ENABLE

    /** Verify parameters are valid */
    FSP_ASSERT(NULL != p_version);
#endif

    *p_version = g_fsp_version;

    return FSP_SUCCESS;
}

#if ((1 == BSP_CFG_ERROR_LOG) || (1 == BSP_CFG_ASSERT))

/*******************************************************************************************************************//**
 * Default error logger function, used only if fsp_error_log is not defined in the user application.
 *
 * @param[in]  err     The error code encountered.
 * @param[in]  file    The file name in which the error code was encountered.
 * @param[in]  line    The line number at which the error code was encountered.
 **********************************************************************************************************************/
void fsp_error_log_internal (fsp_err_t err, const char * file, int32_t line)
{
    /** Do nothing. Do not generate any 'unused' warnings. */
    FSP_PARAMETER_NOT_USED(err);
    FSP_PARAMETER_NOT_USED(file);
    FSP_PARAMETER_NOT_USED(line);
}

#endif

/** @} (end addtogroup BSP_MCU) */

/*******************************************************************************************************************//**
 * Default initialization function, used only if bsp_init is not defined in the user application.
 **********************************************************************************************************************/
void bsp_init_internal (void * p_args)
{
    /* Do nothing. */
    FSP_PARAMETER_NOT_USED(p_args);
}

#if defined(__ARMCC_VERSION)

/*******************************************************************************************************************//**
 * Default implementation of assert for AC6.
 **********************************************************************************************************************/
__attribute__((weak, noreturn))
void __aeabi_assert (const char * expr, const char * file, int line)
{
    FSP_PARAMETER_NOT_USED(expr);
    FSP_PARAMETER_NOT_USED(file);
    FSP_PARAMETER_NOT_USED(line);
    __BKPT(0);
    while (1)
    {
        /* Do nothing. */
    }
}

#elif defined(__GNUC__)

/* The default assert implementation for GCC brings in printing/formatting code.  FSP overrides the default assert
 * behavior to reduce code size. */

 #if !BSP_CFG_USE_STANDARD_ASSERT

/*******************************************************************************************************************//**
 * Default implementation of assert for GCC.
 **********************************************************************************************************************/
BSP_WEAK_REFERENCE void __assert_func (const char * file, int line, const char * func, const char * expr)
{
    FSP_PARAMETER_NOT_USED(file);
    FSP_PARAMETER_NOT_USED(line);
    FSP_PARAMETER_NOT_USED(func);
    FSP_PARAMETER_NOT_USED(expr);
    __BKPT(0);
    while (1)
    {
        /* Do nothing. */
    }
}

 #endif

#endif
