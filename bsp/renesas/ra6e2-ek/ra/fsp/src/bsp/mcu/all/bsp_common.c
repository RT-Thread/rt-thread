/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

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
#if BSP_FEATURE_TZ_VERSION == 2 && BSP_TZ_SECURE_BUILD == 1
static bool bsp_valid_register_check(uint32_t               register_address,
                                     uint32_t const * const p_register_table,
                                     uint32_t               register_table_length);

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

#if BSP_FEATURE_TZ_VERSION == 2 && BSP_TZ_SECURE_BUILD == 1

/*******************************************************************************************************************//**
 * Read a secure 8-bit STYPE3 register in the non-secure state.
 *
 * @param[in]  p_reg The address of the secure register.
 *
 * @return     Value read from the register.
 **********************************************************************************************************************/
BSP_CMSE_NONSECURE_ENTRY uint8_t R_BSP_NSC_STYPE3_RegU8Read (uint8_t volatile const * p_reg)
{
    uint8_t volatile * p_reg_s = (uint8_t volatile *) ((uint32_t) p_reg & ~BSP_FEATURE_TZ_NS_OFFSET);

    /* Table of secure registers that may be read from the non-secure application. */
    static const uint32_t valid_addresses[] =
    {
        (uint32_t) &R_SYSTEM->SCKDIVCR2,
        (uint32_t) &R_SYSTEM->SCKSCR,
        (uint32_t) &R_SYSTEM->SPICKDIVCR,
        (uint32_t) &R_SYSTEM->SPICKCR,
        (uint32_t) &R_SYSTEM->SCICKDIVCR,
        (uint32_t) &R_SYSTEM->SCICKCR,
        (uint32_t) &R_SYSTEM->CANFDCKCR,
        (uint32_t) &R_SYSTEM->PLLCR,
        (uint32_t) &R_SYSTEM->PLL2CR,
        (uint32_t) &R_SYSTEM->MOCOCR,
        (uint32_t) &R_SYSTEM->OPCCR,
    };

    if (bsp_valid_register_check((uint32_t) p_reg_s, valid_addresses,
                                 sizeof(valid_addresses) / sizeof(valid_addresses[0])))
    {
        return *p_reg_s;
    }

    /* Generate a trustzone access violation by accessing the non-secure aliased address. */
    return *((uint8_t volatile *) ((uint32_t) p_reg | BSP_FEATURE_TZ_NS_OFFSET));
}

/*******************************************************************************************************************//**
 * Read a secure 16-bit STYPE3 register in the non-secure state.
 *
 * @param[in]  p_reg The address of the secure register.
 *
 * @return     Value read from the register.
 **********************************************************************************************************************/
BSP_CMSE_NONSECURE_ENTRY uint16_t R_BSP_NSC_STYPE3_RegU16Read (uint16_t volatile const * p_reg)
{
    uint16_t volatile * p_reg_s = (uint16_t volatile *) ((uint32_t) p_reg & ~BSP_FEATURE_TZ_NS_OFFSET);

    /* Table of secure registers that may be read from the non-secure application. */
    static const uint32_t valid_addresses[] =
    {
        (uint32_t) &R_DTC->DTCSTS,
    };

    if (bsp_valid_register_check((uint32_t) p_reg_s, valid_addresses,
                                 sizeof(valid_addresses) / sizeof(valid_addresses[0])))
    {
        return *p_reg_s;
    }

    /* Generate a trustzone access violation by accessing the non-secure aliased address. */
    return *((uint16_t volatile *) ((uint32_t) p_reg | BSP_FEATURE_TZ_NS_OFFSET));
}

/*******************************************************************************************************************//**
 * Read a secure 32-bit STYPE3 register in the non-secure state.
 *
 * @param[in]  p_reg The address of the secure register.
 *
 * @return     Value read from the register.
 **********************************************************************************************************************/
BSP_CMSE_NONSECURE_ENTRY uint32_t R_BSP_NSC_STYPE3_RegU32Read (uint32_t volatile const * p_reg)
{
    uint32_t volatile * p_reg_s = (uint32_t volatile *) ((uint32_t) p_reg & ~BSP_FEATURE_TZ_NS_OFFSET);

    /* Table of secure registers that may be read from the non-secure application. */
    static const uint32_t valid_addresses[] =
    {
        (uint32_t) &R_SYSTEM->SCKDIVCR,
    };

    if (bsp_valid_register_check((uint32_t) p_reg_s, valid_addresses,
                                 sizeof(valid_addresses) / sizeof(valid_addresses[0])))
    {
        return *p_reg_s;
    }

    /* Generate a trustzone access violation by accessing the non-secure aliased address. */
    return *((uint32_t volatile *) ((uint32_t) p_reg | BSP_FEATURE_TZ_NS_OFFSET));
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

#if BSP_FEATURE_TZ_VERSION == 2 && BSP_TZ_SECURE_BUILD == 1

/*******************************************************************************************************************//**
 * Check if a register address should be accessible by the non-secure application.
 **********************************************************************************************************************/
static bool bsp_valid_register_check (uint32_t               register_address,
                                      uint32_t const * const p_register_table,
                                      uint32_t               register_table_length)
{
    bool valid = false;

    /* Check if the given address is valid. */
    for (uint32_t i = 0; i < register_table_length; i++)
    {
        if (p_register_table[i] == register_address)
        {
            valid = true;
            break;
        }
    }

    return valid;
}

#endif
