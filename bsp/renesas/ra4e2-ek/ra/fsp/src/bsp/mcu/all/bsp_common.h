/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_COMMON_H
#define BSP_COMMON_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/* C99 includes. */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

/* Different compiler support. */
#include "../../inc/api/fsp_common_api.h"
#include "bsp_compiler_support.h"

/* BSP module includes */
#include "../../src/bsp/mcu/all/bsp_tfu.h"
#include "../../src/bsp/mcu/all/bsp_sdram.h"
#include "../../src/bsp/mcu/all/bsp_mmf.h"
#include "../../src/bsp/mcu/all/bsp_ipc.h"

#include "bsp_linker_info.h"

#include "bsp_cfg.h"

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** Used to signify that an ELC event is not able to be used as an interrupt. */
#define BSP_IRQ_DISABLED    (0xFFU)

/* Version of this module's code and API. */

#if 1 == BSP_CFG_RTOS                  /* ThreadX */
 #include "tx_user.h"
 #if defined(TX_ENABLE_EVENT_TRACE) || defined(TX_ENABLE_EXECUTION_CHANGE_NOTIFY)
  #include "tx_port.h"
  #define FSP_CONTEXT_SAVE       tx_isr_start((uint32_t) R_FSP_CurrentIrqGet());
  #define FSP_CONTEXT_RESTORE    tx_isr_end((uint32_t) R_FSP_CurrentIrqGet());
 #else
  #define FSP_CONTEXT_SAVE
  #define FSP_CONTEXT_RESTORE
 #endif
#else
 #define FSP_CONTEXT_SAVE
 #define FSP_CONTEXT_RESTORE
#endif

/** Macro that can be defined in order to enable logging in FSP modules. */
#ifndef FSP_LOG_PRINT
 #define FSP_LOG_PRINT(X)
#endif

/** Macro to log and return error without an assertion. */
#ifndef FSP_RETURN

 #define FSP_RETURN(err)    FSP_ERROR_LOG((err)); \
    return err;
#endif

/** This function is called before returning an error code. To stop on a runtime error, define fsp_error_log in
 * user code and do required debugging (breakpoints, stack dump, etc) in this function.*/
#if (1 == BSP_CFG_ASSERT)

 #ifndef FSP_ERROR_LOG
  #define FSP_ERROR_LOG(err) \
    fsp_error_log((err), __FILE__, __LINE__);
 #endif
#else

 #define FSP_ERROR_LOG(err)
#endif

/** Default assertion calls ::FSP_ERROR_RETURN if condition "a" is false. Used to identify incorrect use of API's in FSP
 * functions. */
#if (3 == BSP_CFG_ASSERT)
 #define FSP_ASSERT(a)
#elif (2 == BSP_CFG_ASSERT)
 #define FSP_ASSERT(a)    {assert(a);}
#else
 #define FSP_ASSERT(a)    FSP_ERROR_RETURN((a), FSP_ERR_ASSERTION)
#endif                                 // ifndef FSP_ASSERT

/** All FSP error codes are returned using this macro. Calls ::FSP_ERROR_LOG function if condition "a" is false. Used
 * to identify runtime errors in FSP functions. */

#define FSP_ERROR_RETURN(a, err)                        \
    {                                                   \
        if ((a))                                        \
        {                                               \
            (void) 0;                  /* Do nothing */ \
        }                                               \
        else                                            \
        {                                               \
            FSP_ERROR_LOG(err);                         \
            return err;                                 \
        }                                               \
    }

/* Function-like macro used to wait for a condition to be met, most often used to wait for hardware register updates.
 * This macro can be redefined to add a timeout if necessary. */
#ifndef FSP_HARDWARE_REGISTER_WAIT
 #define FSP_HARDWARE_REGISTER_WAIT(reg, required_value)    while (reg != required_value) { /* Wait. */}
#endif

#ifndef FSP_REGISTER_READ

/* Read a register and discard the result. */
 #define FSP_REGISTER_READ(A)    __ASM volatile ("" : : "r" (A));
#endif

/****************************************************************
 *
 * This check is performed to select suitable ASM API with respect to core
 *
 * The macros __CORE__ , __ARM7EM__ and __ARM_ARCH_8M_BASE__ are undefined for GCC, but defined(__IAR_SYSTEMS_ICC__) is false for GCC, so
 * the left half of the || expression evaluates to false for GCC regardless of the values of these macros. */

#if (defined(__IICARM__) && defined(RENESAS_CORTEX_M23)) || defined(RENESAS_CORTEX_M4)
 #ifndef BSP_CFG_IRQ_MASK_LEVEL_FOR_CRITICAL_SECTION
  #define BSP_CFG_IRQ_MASK_LEVEL_FOR_CRITICAL_SECTION    (0U)
 #endif
#else
 #ifdef BSP_CFG_IRQ_MASK_LEVEL_FOR_CRITICAL_SECTION
  #undef BSP_CFG_IRQ_MASK_LEVEL_FOR_CRITICAL_SECTION
 #endif
 #define BSP_CFG_IRQ_MASK_LEVEL_FOR_CRITICAL_SECTION    (0U)
#endif

/* This macro defines a variable for saving previous mask value */
#ifndef FSP_CRITICAL_SECTION_DEFINE

 #define FSP_CRITICAL_SECTION_DEFINE               uint32_t old_mask_level = 0U
#endif

/* These macros abstract methods to save and restore the interrupt state for different architectures. */
#if (0 == BSP_CFG_IRQ_MASK_LEVEL_FOR_CRITICAL_SECTION)
 #define FSP_CRITICAL_SECTION_GET_CURRENT_STATE    __get_PRIMASK
 #define FSP_CRITICAL_SECTION_SET_STATE            __set_PRIMASK
 #define FSP_CRITICAL_SECTION_IRQ_MASK_SET         (1U)
#else
 #define FSP_CRITICAL_SECTION_GET_CURRENT_STATE    __get_BASEPRI
 #define FSP_CRITICAL_SECTION_SET_STATE            __set_BASEPRI
 #define FSP_CRITICAL_SECTION_IRQ_MASK_SET         ((uint8_t) (BSP_CFG_IRQ_MASK_LEVEL_FOR_CRITICAL_SECTION << \
                                                               (8U - __NVIC_PRIO_BITS)))
#endif

/** This macro temporarily saves the current interrupt state and disables interrupts. */
#ifndef FSP_CRITICAL_SECTION_ENTER
 #define FSP_CRITICAL_SECTION_ENTER                            \
    old_mask_level = FSP_CRITICAL_SECTION_GET_CURRENT_STATE(); \
    FSP_CRITICAL_SECTION_SET_STATE(FSP_CRITICAL_SECTION_IRQ_MASK_SET)
#endif

/** This macro restores the previously saved interrupt state, reenabling interrupts. */
#ifndef FSP_CRITICAL_SECTION_EXIT
 #define FSP_CRITICAL_SECTION_EXIT              FSP_CRITICAL_SECTION_SET_STATE(old_mask_level)
#endif

/* Number of Cortex processor exceptions, used as an offset from XPSR value for the IRQn_Type macro. */
#define FSP_PRIV_CORTEX_PROCESSOR_EXCEPTIONS    (16U)

/** Used to signify that the requested IRQ vector is not defined in this system. */
#define FSP_INVALID_VECTOR                      ((IRQn_Type) - 33)

/* Private definition used in bsp_clocks and R_FSP_SystemClockHzGet. Each bitfield in SCKDIVCR is up to 4 bits wide. */
#if (BSP_CFG_MCU_PART_SERIES == 8)
 #define FSP_PRV_SCKDIVCR_DIV_MASK              (0xFU)
#else
 #define FSP_PRV_SCKDIVCR_DIV_MASK              (0x7U)
#endif

/* Use the secure registers for secure projects and flat projects. */
#if !BSP_TZ_NONSECURE_BUILD && BSP_FEATURE_TZ_HAS_TRUSTZONE
 #define FSP_PRIV_TZ_USE_SECURE_REGS            (1)
#else
 #define FSP_PRIV_TZ_USE_SECURE_REGS            (0)
#endif

/* Put certain BSP variables in uninitialized RAM when initializing BSP early. */
#if BSP_CFG_EARLY_INIT
 #define BSP_SECTION_EARLY_INIT                 BSP_PLACE_IN_SECTION(BSP_SECTION_NOINIT)
#else
 #define BSP_SECTION_EARLY_INIT
#endif

/* Used to determine if this project is part of a multicore FSP Solution. */
#if defined(BSP_PARTITION_FLASH_CPU1_S_START)
 #define BSP_MULTICORE_PROJECT    (1)
#else
 #define BSP_MULTICORE_PROJECT    (0)
#endif

#if (BSP_TZ_SECURE_BUILD || BSP_TZ_NONSECURE_BUILD) && BSP_FEATURE_TZ_VERSION == 2
BSP_CMSE_NONSECURE_ENTRY uint8_t  R_BSP_NSC_STYPE3_RegU8Read(uint8_t volatile const * p_reg);
BSP_CMSE_NONSECURE_ENTRY uint16_t R_BSP_NSC_STYPE3_RegU16Read(uint16_t volatile const * p_reg);
BSP_CMSE_NONSECURE_ENTRY uint32_t R_BSP_NSC_STYPE3_RegU32Read(uint32_t volatile const * p_reg);

#endif

#if BSP_FEATURE_TZ_HAS_TRUSTZONE && BSP_TZ_NONSECURE_BUILD && BSP_FEATURE_TZ_VERSION == 2

/*
 * If the STYPE3 register's security attribution is set to secure, the non-secure application must read the register
 * from the secure application using the provided non-secure callable functions.
 */
 #define FSP_STYPE3_REG8_READ(X, S)     (!(S) ? X : (R_BSP_NSC_STYPE3_RegU8Read((uint8_t const volatile *) &X)))
 #define FSP_STYPE3_REG16_READ(X, S)    (!(S) ? X : (R_BSP_NSC_STYPE3_RegU16Read((uint16_t const volatile *) &X)))
 #define FSP_STYPE3_REG32_READ(X, S)    (!(S) ? X : (R_BSP_NSC_STYPE3_RegU32Read((uint32_t const volatile *) &X)))
#elif BSP_FEATURE_TZ_HAS_TRUSTZONE && BSP_TZ_SECURE_BUILD && BSP_FEATURE_TZ_VERSION == 2

/*******************************************************************************************************************//**
 * Read a non-secure 8-bit STYPE3 register in the secure state.
 *
 * @param[in]  p_reg The address of the non-secure register.
 *
 * @return     Value read from the register.
 **********************************************************************************************************************/
__STATIC_INLINE uint8_t R_BSP_S_STYPE3_RegU8Read (uint8_t volatile const * p_reg)
{
    p_reg = (uint8_t volatile const *) ((uint32_t) p_reg | BSP_FEATURE_TZ_NS_OFFSET);

    return *p_reg;
}

/*******************************************************************************************************************//**
 * Read a non-secure 16-bit STYPE3 register in the secure state.
 *
 * @param[in]  p_reg The address of the non-secure register.
 *
 * @return     Value read from the register.
 **********************************************************************************************************************/
__STATIC_INLINE uint16_t R_BSP_S_STYPE3_RegU16Read (uint16_t volatile const * p_reg)
{
    p_reg = (uint16_t volatile const *) ((uint32_t) p_reg | BSP_FEATURE_TZ_NS_OFFSET);

    return *p_reg;
}

/*******************************************************************************************************************//**
 * Read a non-secure 32-bit STYPE3 register in the secure state.
 *
 * @param[in]  p_reg The address of the non-secure register.
 *
 * @return     Value read from the register.
 **********************************************************************************************************************/
__STATIC_INLINE uint32_t R_BSP_S_STYPE3_RegU32Read (uint32_t volatile const * p_reg)
{
    p_reg = (uint32_t volatile const *) ((uint32_t) p_reg | BSP_FEATURE_TZ_NS_OFFSET);

    return *p_reg;
}

/*
 * If the STYPE3 register's security attribution is set to non-secure, the secure application must read the register
 * using the non-secure aliased address.
 */
 #define FSP_STYPE3_REG8_READ(X, S)     ((S) ? (X) : R_BSP_S_STYPE3_RegU8Read((uint8_t const volatile *) &X))
 #define FSP_STYPE3_REG16_READ(X, S)    ((S) ? (X) : R_BSP_S_STYPE3_RegU16Read((uint16_t const volatile *) &X))
 #define FSP_STYPE3_REG32_READ(X, S)    ((S) ? (X) : R_BSP_S_STYPE3_RegU32Read((uint32_t const volatile *) &X))
#else
 #define FSP_STYPE3_REG8_READ(X, S)     (X)
 #define FSP_STYPE3_REG16_READ(X, S)    (X)
 #define FSP_STYPE3_REG32_READ(X, S)    (X)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Different warm start entry locations in the BSP. */
typedef enum e_bsp_warm_start_event
{
    BSP_WARM_START_RESET = 0,          ///< Called almost immediately after reset. No C runtime environment, clocks, or IRQs.
    BSP_WARM_START_POST_CLOCK,         ///< Called after clock initialization. No C runtime environment or IRQs.
    BSP_WARM_START_POST_C              ///< Called after clocks and C runtime environment have been set up
} bsp_warm_start_event_t;

/* Private enum used in R_FSP_SystemClockHzGet.  Maps clock name to base bit in SCKDIVCR. */
typedef enum e_fsp_priv_clock
{
    FSP_PRIV_CLOCK_PCLKD  = 0,
    FSP_PRIV_CLOCK_PCLKC  = 4,
    FSP_PRIV_CLOCK_PCLKB  = 8,
    FSP_PRIV_CLOCK_PCLKA  = 12,
    FSP_PRIV_CLOCK_BCLK   = 16,
    FSP_PRIV_CLOCK_PCLKE  = 20,
    FSP_PRIV_CLOCK_ICLK   = 24,
    FSP_PRIV_CLOCK_FCLK   = 28,
    FSP_PRIV_CLOCK_CPUCLK = 32,
    FSP_PRIV_CLOCK_UNUSED = 255,       ///< Sentinel value for unused clock
} fsp_priv_clock_t;

/* Private enum used in R_FSP_SciSpiClockHzGe.  Maps clock name to base bit in SCISPICKCR. */
typedef enum e_fsp_priv_source_clock
{
    FSP_PRIV_CLOCK_HOCO     = 0,       ///< The high speed on chip oscillator
    FSP_PRIV_CLOCK_MOCO     = 1,       ///< The middle speed on chip oscillator
    FSP_PRIV_CLOCK_LOCO     = 2,       ///< The low speed on chip oscillator
    FSP_PRIV_CLOCK_MAIN_OSC = 3,       ///< The main oscillator
    FSP_PRIV_CLOCK_SUBCLOCK = 4,       ///< The subclock oscillator
    FSP_PRIV_CLOCK_PLL      = 5,       ///< The PLL output
    FSP_PRIV_CLOCK_PLL1P    = 5,       ///< The PLL1P output
    FSP_PRIV_CLOCK_PLL2     = 6,       ///< The PLL2 output
    FSP_PRIV_CLOCK_PLL2P    = 6,       ///< The PLL2P output
    FSP_PRIV_CLOCK_PLL1Q    = 7,       ///< The PLL1Q output
    FSP_PRIV_CLOCK_PLL1R    = 8,       ///< The PLL1R output
    FSP_PRIV_CLOCK_PLL2Q    = 9,       ///< The PLL2Q output
    FSP_PRIV_CLOCK_PLL2R    = 10,      ///< The PLL2R output
} fsp_priv_source_clock_t;

typedef struct st_bsp_unique_id
{
    union
    {
        uint32_t unique_id_words[4];
        uint8_t  unique_id_bytes[16];
    };
} bsp_unique_id_t;

typedef struct st_bsp_part_number
{
    union
    {
        uint32_t part_number_words[4];
        uint8_t  part_number_bytes[16];
    };
} bsp_part_number_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
uint32_t R_BSP_SourceClockHzGet(fsp_priv_source_clock_t clock);

/***********************************************************************************************************************
 * Global variables (defined in other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Inline Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Return active interrupt vector number value
 *
 * @return     Active interrupt vector number value
 **********************************************************************************************************************/
__STATIC_INLINE IRQn_Type R_FSP_CurrentIrqGet (void)
{
    xPSR_Type xpsr_value;
    xpsr_value.w = __get_xPSR();

    return (IRQn_Type) (xpsr_value.b.ISR - FSP_PRIV_CORTEX_PROCESSOR_EXCEPTIONS);
}

/*******************************************************************************************************************//**
 * Gets the frequency of a system clock.
 *
 * @return     Frequency of requested clock in Hertz.
 **********************************************************************************************************************/
__STATIC_INLINE uint32_t R_FSP_SystemClockHzGet (fsp_priv_clock_t clock)
{
    /* Check if the provided clock is an unused clock. */
    if (FSP_PRIV_CLOCK_UNUSED == clock)
    {
        return 0;
    }

#if !BSP_FEATURE_CGC_REGISTER_SET_B
    uint32_t sckdivcr  = FSP_STYPE3_REG32_READ(R_SYSTEM->SCKDIVCR, BSP_CFG_CLOCKS_SECURE);
    uint32_t clock_div = (sckdivcr >> clock) & FSP_PRV_SCKDIVCR_DIV_MASK;

 #if BSP_FEATURE_CGC_HAS_CPUCLK
    if (FSP_PRIV_CLOCK_CPUCLK == clock)
    {
        return SystemCoreClock;
    }

    /* Get CPUCLK divisor */
  #if BSP_FEATURE_CGC_SCKDIVCR2_HAS_EXTRA_CLOCKS
   #if (BSP_CFG_CPU_CORE == 1)
    uint32_t cpuclk_div =
        (FSP_STYPE3_REG16_READ(R_SYSTEM->SCKDIVCR2, BSP_CFG_CLOCKS_SECURE) & R_SYSTEM_SCKDIVCR2_CPUCK1_Msk) >>
        R_SYSTEM_SCKDIVCR2_CPUCK1_Pos;
   #else
    uint32_t cpuclk_div = FSP_STYPE3_REG16_READ(R_SYSTEM->SCKDIVCR2, BSP_CFG_CLOCKS_SECURE) & FSP_PRV_SCKDIVCR_DIV_MASK;
   #endif
  #else
    uint32_t cpuclk_div = FSP_STYPE3_REG8_READ(R_SYSTEM->SCKDIVCR2, BSP_CFG_CLOCKS_SECURE) & FSP_PRV_SCKDIVCR_DIV_MASK;
  #endif

    /* Determine if either divisor is a multiple of 3 */
    if ((cpuclk_div | clock_div) & 8U)
    {
        /* Convert divisor settings to their actual values */
        cpuclk_div = (cpuclk_div & 8U) ? (3U << (cpuclk_div & 7U)) : (1U << cpuclk_div);
        clock_div  = (clock_div & 8U) ? (3U << (clock_div & 7U)) : (1U << clock_div);

        /* Calculate clock with multiplication and division instead of shifting */
        return (SystemCoreClock * cpuclk_div) / clock_div;
    }
    else
    {
        return (SystemCoreClock << cpuclk_div) >> clock_div;
    }

 #else
    uint32_t iclk_div = (sckdivcr >> FSP_PRIV_CLOCK_ICLK) & FSP_PRV_SCKDIVCR_DIV_MASK;

    return (SystemCoreClock << iclk_div) >> clock_div;
 #endif
#else
    FSP_PARAMETER_NOT_USED(clock);

    return SystemCoreClock;
#endif
}

/*******************************************************************************************************************//**
 * Converts a clock's CKDIVCR register value to a clock divider (Eg: SPICKDIVCR).
 *
 * @return     Clock Divider
 **********************************************************************************************************************/
__STATIC_INLINE uint32_t R_FSP_ClockDividerGet (uint32_t ckdivcr)
{
    if (2U >= ckdivcr)
    {

        /* clock_div:
         * - Clock Divided by 1: 0
         * - Clock Divided by 2: 1
         * - Clock Divided by 4: 2
         */
        return 1U << ckdivcr;
    }
    else if (3U == ckdivcr)
    {

        /* Clock Divided by 6 */
        return 6U;
    }
    else if (4U == ckdivcr)
    {

        /* Clock Divided by 8 */
        return 8U;
    }
    else if (5U == ckdivcr)
    {

        /* Clock Divided by 3 */
        return 3U;
    }
    else if (6U == ckdivcr)
    {

        /* Clock Divided by 5 */
        return 5;
    }
    else if (7U == ckdivcr)
    {

        /* Clock Divided by 10 */
        return 10;
    }
    else
    {
        /* The remaining case is ckdivcr = 8 which divides the clock by 16. */
    }

    /* Clock Divided by 16 */
    return 16U;
}

#if BSP_FEATURE_BSP_HAS_SCISPI_CLOCK

/*******************************************************************************************************************//**
 * Gets the frequency of a SCI/SPI clock.
 *
 * @return     Frequency of requested clock in Hertz.
 **********************************************************************************************************************/
__STATIC_INLINE uint32_t R_FSP_SciSpiClockHzGet (void)
{
    uint32_t                scispidivcr = R_SYSTEM->SCISPICKDIVCR;
    uint32_t                clock_div   = R_FSP_ClockDividerGet(scispidivcr & FSP_PRV_SCKDIVCR_DIV_MASK);
    fsp_priv_source_clock_t scispicksel = (fsp_priv_source_clock_t) R_SYSTEM->SCISPICKCR_b.SCISPICKSEL;

    return R_BSP_SourceClockHzGet(scispicksel) / clock_div;
}

#endif
#if BSP_FEATURE_BSP_HAS_SPI_CLOCK

/*******************************************************************************************************************//**
 * Gets the frequency of a SPI clock.
 *
 * @return     Frequency of requested clock in Hertz.
 **********************************************************************************************************************/
__STATIC_INLINE uint32_t R_FSP_SpiClockHzGet (void)
{
    uint32_t                spidivcr  = FSP_STYPE3_REG8_READ(R_SYSTEM->SPICKDIVCR, BSP_CFG_CLOCKS_SECURE);
    uint32_t                clock_div = R_FSP_ClockDividerGet(spidivcr & FSP_PRV_SCKDIVCR_DIV_MASK);
    fsp_priv_source_clock_t spicksel  =
        (fsp_priv_source_clock_t) ((FSP_STYPE3_REG8_READ(R_SYSTEM->SPICKCR,
                                                         BSP_CFG_CLOCKS_SECURE) & R_SYSTEM_SPICKCR_CKSEL_Msk) >>
                                   R_SYSTEM_SPICKCR_CKSEL_Pos);

    return R_BSP_SourceClockHzGet(spicksel) / clock_div;
}

#endif
#if BSP_FEATURE_BSP_HAS_SCI_CLOCK

/*******************************************************************************************************************//**
 * Gets the frequency of a SCI clock.
 *
 * @return     Frequency of requested clock in Hertz.
 **********************************************************************************************************************/
__STATIC_INLINE uint32_t R_FSP_SciClockHzGet (void)
{
    uint32_t                scidivcr  = FSP_STYPE3_REG8_READ(R_SYSTEM->SCICKDIVCR, BSP_CFG_CLOCKS_SECURE);
    uint32_t                clock_div = R_FSP_ClockDividerGet(scidivcr & FSP_PRV_SCKDIVCR_DIV_MASK);
    fsp_priv_source_clock_t scicksel  =
        (fsp_priv_source_clock_t) (FSP_STYPE3_REG8_READ(R_SYSTEM->SCICKCR,
                                                        BSP_CFG_CLOCKS_SECURE) & R_SYSTEM_SCICKCR_SCICKSEL_Msk >>
                                   R_SYSTEM_SCICKCR_SCICKSEL_Pos);

    return R_BSP_SourceClockHzGet(scicksel) / clock_div;
}

#endif

/*******************************************************************************************************************//**
 * Get unique ID for this device.
 *
 * @return  A pointer to the unique identifier structure
 **********************************************************************************************************************/
__STATIC_INLINE bsp_unique_id_t const * R_BSP_UniqueIdGet (void)
{
#if BSP_FEATURE_TZ_VERSION == 2 && BSP_TZ_NONSECURE_BUILD == 1

    return (bsp_unique_id_t *) (BSP_FEATURE_BSP_UNIQUE_ID_POINTER | BSP_FEATURE_TZ_NS_OFFSET);
#else

    return (bsp_unique_id_t *) BSP_FEATURE_BSP_UNIQUE_ID_POINTER;
#endif
}

/*******************************************************************************************************************//**
 * Get part number for this device.
 *
 * @param[out] p_part_number    Memory address to return MCU's part number to.
 *
 * @retval FSP_SUCCESS          Part number information stored.
 * @retval FSP_ERR_ASSERTION    The parameter p_part_number is NULL.
 * @retval FSP_ERR_NOT_FOUND    An error occurred when retrieving data from part number register.
 **********************************************************************************************************************/
__STATIC_INLINE fsp_err_t R_BSP_PartNumberGet (bsp_part_number_t * const p_part_number)
{
#if BSP_CFG_PARAM_CHECKING_ENABLE

    /** Verify parameters are valid */
    if (NULL == p_part_number)
    {
        return FSP_ERR_ASSERTION;
    }
#endif

    /* Pointer to Part Numbering Register PNR */
#if BSP_FEATURE_TZ_VERSION == 2 && BSP_TZ_NONSECURE_BUILD == 1
    bsp_part_number_t * p_pnr = (bsp_part_number_t *) (BSP_FEATURE_BSP_PART_NUMBER_POINTER | BSP_FEATURE_TZ_NS_OFFSET);
#else
    bsp_part_number_t * p_pnr = (bsp_part_number_t *) BSP_FEATURE_BSP_PART_NUMBER_POINTER;
#endif

    /* In case part number is following the right order
     * for example: R 7 F A 8 E 1 A F D C F B_ _ _ */
    if (p_pnr->part_number_bytes[0] == 'R')
    {
        memcpy(p_part_number, p_pnr, sizeof(bsp_part_number_t));
    }
    /* In case part number is in reverse order, 'R' letter should be in position 12
     * for example: K N C 3 7 0 1 E 0 A F 7 R _ _ _ */
    else if (p_pnr->part_number_bytes[12] == 'R')
    {
        for (uint8_t i = 0; i < sizeof(bsp_part_number_t); i++)
        {
            if (i <= 12)
            {
                p_part_number->part_number_bytes[i] = p_pnr->part_number_bytes[12 - i];
            }
            else
            {
                p_part_number->part_number_bytes[i] = p_pnr->part_number_bytes[i];
            }
        }
    }
    else
    {
        return FSP_ERR_NOT_FOUND;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disables the flash cache.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_FlashCacheDisable (void)
{
#if BSP_FEATURE_BSP_FLASH_CACHE
    R_FCACHE->FCACHEE = 0U;
#endif

#ifdef R_CACHE
 #if BSP_FEATURE_BSP_CODE_CACHE_VERSION == 2
    uint32_t volatile * p_ccactl = &R_CACHE->CCACTL;
    uint32_t volatile * p_ccawta = &R_CACHE->CCAWTA;

  #if BSP_TZ_SECURE_BUILD && BSP_FEATURE_TZ_VERSION == 2
    if (1 == R_CPSCU->CACHESAR_b.CACHESA)
    {
        /* Access CCACTL using the non-secure alias. */
        p_ccactl = (uint32_t volatile *) ((uint32_t) p_ccactl | BSP_FEATURE_TZ_NS_OFFSET);

        /* Access CCAWTA using the non-secure alias. */
        p_ccawta = (uint32_t volatile *) ((uint32_t) p_ccawta | BSP_FEATURE_TZ_NS_OFFSET);
    }
  #endif

    /* Writeback and flush cache when disabling
     * Refer to the CCAFCT register description in the relevant hardware manual */
    if (*p_ccawta & R_CACHE_CCAWTA_WT_Msk)
    {
        *p_ccactl = R_CACHE_CCACTL_FC_Msk;
    }
    else
    {
        *p_ccactl = R_CACHE_CCACTL_FC_Msk | R_CACHE_CCACTL_WB_Msk;
    }

    FSP_HARDWARE_REGISTER_WAIT(R_CACHE->CCAFCT, 0U);
 #else

    /* Disable the C-Cache. */
    R_CACHE->CCACTL = 0U;
 #endif
#endif
}

/*******************************************************************************************************************//**
 * Enables the flash cache.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_FlashCacheEnable (void)
{
#if BSP_FEATURE_BSP_FLASH_CACHE

    /* Invalidate the flash cache and wait until it is invalidated. (See section 55.3.2.2 "Operation" of the Flash Cache
     * in the RA6M3 manual R01UH0878EJ0100). */
    R_FCACHE->FCACHEIV = 1U;
    FSP_HARDWARE_REGISTER_WAIT(R_FCACHE->FCACHEIV, 0U);

    /* Enable flash cache. */
    R_FCACHE->FCACHEE = 1U;
#endif

#ifdef R_CACHE
 #if BSP_FEATURE_BSP_CODE_CACHE_VERSION == 1

    /* Configure the C-Cache line size. */
    R_CACHE->CCALCF = BSP_CFG_C_CACHE_LINE_SIZE;

    /* Enable the C-Cache. */
    R_CACHE->CCACTL = 1U;
 #else
    uint32_t volatile * p_ccactl = &R_CACHE->CCACTL;

    /* Flush cache before enabling */
    R_CACHE->CCAFCT_b.FC = 1;

    /* Check that no flush or writeback are ongoing before enabling
     * Refer to the CCAFCT register description in the relevant hardware manual */
    FSP_HARDWARE_REGISTER_WAIT(R_CACHE->CCAFCT, 0U);

  #if BSP_TZ_SECURE_BUILD && BSP_FEATURE_TZ_VERSION == 2
    if (1 == R_CPSCU->CACHESAR_b.CACHESA)
    {
        /* Access CCACTL using the non-secure alias. */
        p_ccactl = (uint32_t volatile *) ((uint32_t) p_ccactl | BSP_FEATURE_TZ_NS_OFFSET);
    }
  #endif

    /* Enable the C-Cache. */
    *p_ccactl = 1U;
 #endif
#endif
}

#if BSP_FEATURE_CGC_SCKDIVCR2_HAS_EXTRA_CLOCKS && !BSP_SECONDARY_CORE_BUILD && defined(BSP_PARTITION_FLASH_CPU1_S_START)
 #define BSP_CPU1ACTCSR_KEY_CODE    0xA5

/*******************************************************************************************************************//**
 * Sets the secondary core VTOR and activates the secondary core.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_SecondaryCoreStart (void)
{
    /* Setup secondary CPU vector table */
    R_CPU_CTRL->CPU1INITVTOR = (uint32_t) BSP_PARTITION_FLASH_CPU1_S_START;

    /* When debugging multicore projects, CPU1 may already be activated by the debugger with CPU1WAITCR set to 1.
     * This allows the debugger to connect to CPU1 prior to it being started by CPU0.
     * If this is the case, then the secondary core must be started by clearing CPU1WAITCR. */
    R_CPU_CTRL->CPU1WAITCR = 0;

    /* Activate secondary CPU by setting key code and activation request in CPU1ACTCSR */
    R_CPU_CTRL->CPU1ACTCSR = (BSP_CPU1ACTCSR_KEY_CODE << R_CPU_CTRL_CPU1ACTCSR_KEY_Pos) |
                             R_CPU_CTRL_CPU1ACTCSR_ACTREQ_Msk;
}

#endif

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
#if  (1 == BSP_CFG_ASSERT)

/** Prototype of default function called before errors are returned in FSP code if BSP_CFG_LOG_ERRORS is set to 1. */
void fsp_error_log(fsp_err_t err, const char * file, int32_t line);

#endif

/** In the event of an unrecoverable error the BSP will by default call the __BKPT() intrinsic function which will
 *  alert the user of the error. The user can override this default behavior by defining their own
 *  BSP_CFG_HANDLE_UNRECOVERABLE_ERROR macro.
 */
#if !defined(BSP_CFG_HANDLE_UNRECOVERABLE_ERROR)

 #define BSP_CFG_HANDLE_UNRECOVERABLE_ERROR(x)    __BKPT((x))
#endif

/** @} (end addtogroup BSP_MCU) */

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
