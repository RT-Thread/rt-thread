/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

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
#include "../../inc/fsp_common_api.h"
#include "bsp_compiler_support.h"
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
#define BSP_IRQ_DISABLED                       (0xFFU)

/* Vector Number offset */
#define BSP_VECTOR_NUM_OFFSET                  (32)
#define BSP_INTERRUPT_TYPE_OFFSET              (16U)

#define FSP_CONTEXT_SAVE
#define FSP_CONTEXT_RESTORE

#define BSP_PRV_CPU_FREQ_800_MHZ               (800000000U)  // CPU frequency is 800 MHz
#define BSP_PRV_CPU_FREQ_600_MHZ               (600000000U)  // CPU frequency is 600 MHz

#define BSP_PRV_ICLK_FREQ_200_MHZ              (200000000U)  // ICLK frequency is 200 MHz
#define BSP_PRV_ICLK_FREQ_150_MHZ              (150000000U)  // ICLK frequency is 150 MHz

#define BSP_PRV_PCLKH_FREQ_200_MHZ             (200000000U)  // PCLKH frequency is 200 MHz
#define BSP_PRV_PCLKH_FREQ_150_MHZ             (150000000U)  // PCLKH frequency is 150 MHz

#define BSP_PRV_PCLKM_FREQ_100_MHZ             (100000000U)  // PCLKM frequency is 100 MHz
#define BSP_PRV_PCLKM_FREQ_75_MHZ              (75000000U)   // PCLKM frequency is 750 MHz

#define BSP_PRV_PCLKL_FREQ_50_MHZ              (50000000U)   // PCLKL frequency is 50 MHz
#define BSP_PRV_PCLKL_FREQ_37_5_MHZ            (37500000U)   // PCLKL frequency is 37.5 MHz

#define BSP_PRV_PCLKADC_FREQ_25_MHZ            (25000000U)   // PCLKADC frequency is 25 MHz
#define BSP_PRV_PCLKADC_FREQ_18_75_MHZ         (18750000U)   // PCLKADC frequency is 18.75 MHz

#define BSP_PRV_PCLKGPTL_FREQ_400_MHZ          (400000000U)  // PCLKGPTL frequency is 400 MHz
#define BSP_PRV_PCLKGPTL_FREQ_300_MHZ          (300000000U)  // PCLKGPTL frequency is 300 MHz

#define BSP_PRV_PCLKSCI_FREQ_75_MHZ            (75000000U)   // PCLKSCI frequency is 75 MHz
#define BSP_PRV_PCLKSCI_FREQ_96_MHZ            (96000000U)   // PCLKSCI frequency is 96 MHz

#define BSP_PRV_PCLKSPI_FREQ_75_MHZ            (75000000U)   // PCLKSPI frequency is 75 MHz
#define BSP_PRV_PCLKSPI_FREQ_96_MHZ            (96000000U)   // PCLKSPI frequency is 96 MHz

#define BSP_PRV_PCLKCAN_FREQ_80_MHZ            (80000000U)   // PCLKCAN frequency is 80 MHz
#define BSP_PRV_PCLKCAN_FREQ_40_MHZ            (40000000U)   // PCLKCAN frequency is 40 MHz

#define BSP_PRV_CKIO_FREQ_100_MHZ              (100000000U)  // CKIO frequency is 100 MHz
#define BSP_PRV_CKIO_FREQ_75_MHZ               (75000000U)   // CKIO frequency is 75 MHz
#define BSP_PRV_CKIO_FREQ_66_7_MHZ             (66666666U)   // CKIO frequency is 66.7 MHz
#define BSP_PRV_CKIO_FREQ_50_MHZ               (50000000U)   // CKIO frequency is 50 MHz
#define BSP_PRV_CKIO_FREQ_40_MHZ               (40000000U)   // CKIO frequency is 40 MHz
#define BSP_PRV_CKIO_FREQ_37_5_MHZ             (37500000U)   // CKIO frequency is 37.5 MHz
#define BSP_PRV_CKIO_FREQ_33_3_MHZ             (33333333U)   // CKIO frequency is 33.3MHz
#define BSP_PRV_CKIO_FREQ_30_MHZ               (30000000U)   // CKIO frequency is 30 MHz
#define BSP_PRV_CKIO_FREQ_28_6_MHZ             (28571428U)   // CKIO frequency is 28.6 MHz
#define BSP_PRV_CKIO_FREQ_25_MHZ               (25000000U)   // CKIO frequency is 25 MHz
#define BSP_PRV_CKIO_FREQ_21_4_MHZ             (21428571U)   // CKIO frequency is 21.4 MHz
#define BSP_PRV_CKIO_FREQ_18_75_MHZ            (18750000U)   // CKIO frequency is 18.75 MHz
#define BSP_PRV_CKIO_FREQ_NOT_SUPPORTED        (0xFFFFFFFFU) // CKIO frequency is not supported

#define BSP_PRV_XSPI_CLK_FREQ_133_3_MHZ        (133333333U)  // XSPI_CLK frequency is 133.3 MHz
#define BSP_PRV_XSPI_CLK_FREQ_100_MHZ          (100000000U)  // XSPI_CLK frequency is 100.0 MHz
#define BSP_PRV_XSPI_CLK_FREQ_75_MHZ           (75000000U)   // XSPI_CLK frequency is 75.0 MHz
#define BSP_PRV_XSPI_CLK_FREQ_50_MHZ           (50000000U)   // XSPI_CLK frequency is 50.0 MHz
#define BSP_PRV_XSPI_CLK_FREQ_37_5_MHZ         (37500000U)   // XSPI_CLK frequency is 37.5 MHz
#define BSP_PRV_XSPI_CLK_FREQ_25_MHZ           (25000000U)   // XSPI_CLK frequency is 25.0 MHz
#define BSP_PRV_XSPI_CLK_FREQ_12_5_MHZ         (12500000U)   // XSPI_CLK frequency is 12.5 MHz
#define BSP_PRV_XSPI_CLK_FREQ_NOT_SUPPORTED    (0xFFFFFFFFU) // XSPI_CLK frequency is not supported

/** Macro to log and return error without an assertion. */
#ifndef FSP_RETURN

 #define FSP_RETURN(err)    FSP_ERROR_LOG((err)); \
    return err;
#endif

/** This function is called before returning an error code. To stop on a runtime error, define fsp_error_log in
 * user code and do required debugging (breakpoints, stack dump, etc) in this function.*/
#if (1 == BSP_CFG_ERROR_LOG)

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

/* Function-like macro used to wait for a condition to be met with timeout,
 * most often used to wait for hardware register updates. */
#define BSP_HARDWARE_REGISTER_WAIT_WTIH_TIMEOUT(reg, required_value, timeout) \
    while ((timeout))                                                         \
    {                                                                         \
        if ((required_value) == (reg))                                        \
        {                                                                     \
            break;                                                            \
        }                                                                     \
        (timeout)--;                                                          \
    }

#ifndef BSP_CFG_IRQ_MASK_LEVEL_FOR_CRITICAL_SECTION
 #define BSP_CFG_IRQ_MASK_LEVEL_FOR_CRITICAL_SECTION    (0U)
#endif

/* This macro defines a variable for saving previous mask value */
#ifndef FSP_CRITICAL_SECTION_DEFINE

 #define FSP_CRITICAL_SECTION_DEFINE              uintptr_t old_mask_level = 0U
#endif

/* These macros abstract methods to save and restore the interrupt state. */
#define FSP_CRITICAL_SECTION_GET_CURRENT_STATE    __get_ICC_PMR
#define FSP_CRITICAL_SECTION_SET_STATE            __set_ICC_PMR
#define FSP_CRITICAL_SECTION_IRQ_MASK_SET         ((uint8_t) (BSP_CFG_IRQ_MASK_LEVEL_FOR_CRITICAL_SECTION << \
                                                              BSP_FEATURE_BSP_IRQ_PRIORITY_POS_BIT))

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

/* Number of Cortex processor exceptions. */
#define FSP_PRIV_CORTEX_PROCESSOR_EXCEPTIONS    (32U)

/** Used to signify that the requested IRQ vector is not defined in this system. */
#define FSP_INVALID_VECTOR                      ((IRQn_Type) - 33)

/* This macro Enable or Disable interrupts. */
#define BSP_INTERRUPT_ENABLE                    __asm volatile ("cpsie i"); \
    __asm volatile ("isb");

#define BSP_INTERRUPT_DISABLE                   __asm volatile ("cpsid i"); \
    __asm volatile ("isb");

/** In the event of an unrecoverable error the BSP will by default call the __BKPT() intrinsic function which will
 *  alert the user of the error. The user can override this default behavior by defining their own
 *  BSP_CFG_HANDLE_UNRECOVERABLE_ERROR macro.
 */
#if !defined(BSP_CFG_HANDLE_UNRECOVERABLE_ERROR)

 #define BSP_CFG_HANDLE_UNRECOVERABLE_ERROR(x)    __BKPT((x))
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

/* Private enum used in R_FSP_SystemClockHzGet. */
typedef enum e_fsp_priv_clock
{
    FSP_PRIV_CLOCK_CPU0      = 0,
    FSP_PRIV_CLOCK_CPU1      = 1,
    FSP_PRIV_CLOCK_ICLK      = 2,
    FSP_PRIV_CLOCK_PCLKH     = 3,
    FSP_PRIV_CLOCK_PCLKM     = 4,
    FSP_PRIV_CLOCK_PCLKL     = 5,
    FSP_PRIV_CLOCK_PCLKADC   = 6,
    FSP_PRIV_CLOCK_PCLKGPTL  = 7,
    FSP_PRIV_CLOCK_PCLKSPI0  = 8,
    FSP_PRIV_CLOCK_PCLKSPI1  = 9,
    FSP_PRIV_CLOCK_PCLKSPI2  = 10,
    FSP_PRIV_CLOCK_PCLKSPI3  = 11,
    FSP_PRIV_CLOCK_PCLKSCI0  = 12,
    FSP_PRIV_CLOCK_PCLKSCI1  = 13,
    FSP_PRIV_CLOCK_PCLKSCI2  = 14,
    FSP_PRIV_CLOCK_PCLKSCI3  = 15,
    FSP_PRIV_CLOCK_PCLKSCI4  = 16,
    FSP_PRIV_CLOCK_PCLKSCI5  = 17,
    FSP_PRIV_CLOCK_PCLKCAN   = 18,
    FSP_PRIV_CLOCK_CKIO      = 19,
    FSP_PRIV_CLOCK_XSPI0_CLK = 20,
    FSP_PRIV_CLOCK_XSPI1_CLK = 21,
} fsp_priv_clock_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

extern const uint32_t g_bsp_system_clock_select[][2];
extern const uint32_t g_bsp_system_clock_select_ckio[][2];
extern const uint32_t g_bsp_system_clock_select_xspi_clk[][2];

extern IRQn_Type g_current_interrupt_num[];
extern uint8_t   g_current_interrupt_pointer;

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
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
    /* Return the current interrupt number. */
    return g_current_interrupt_num[(g_current_interrupt_pointer - 1U)];
}

/*******************************************************************************************************************//**
 * Gets the frequency of a system clock.
 *
 * @return     Frequency of requested clock in Hertz.
 **********************************************************************************************************************/
__STATIC_INLINE uint32_t R_FSP_SystemClockHzGet (fsp_priv_clock_t clock)
{
    uint32_t clock_hz = 0;
    uint32_t fselcpu0 = R_SYSC_S->SCKCR2_b.FSELCPU0;
#if (2 == BSP_FEATURE_BSP_CR52_CORE_NUM)
    uint32_t fselcpu1 = R_SYSC_S->SCKCR2_b.FSELCPU1;
#endif
    switch (clock)
    {
        case FSP_PRIV_CLOCK_CPU0:
        {
            clock_hz = g_bsp_system_clock_select[clock][R_SYSC_S->SCKCR2_b.DIVSELSUB] >> fselcpu0;
            break;
        }

        case FSP_PRIV_CLOCK_CPU1:
        {
#if (2 == BSP_FEATURE_BSP_CR52_CORE_NUM)
            clock_hz = g_bsp_system_clock_select[clock][R_SYSC_S->SCKCR2_b.DIVSELSUB] >> fselcpu1;
#endif
            break;
        }

        /* These iclk and pclk cases are intentionally combined. */
        case FSP_PRIV_CLOCK_ICLK:
        case FSP_PRIV_CLOCK_PCLKH:
        case FSP_PRIV_CLOCK_PCLKM:
        case FSP_PRIV_CLOCK_PCLKL:
        case FSP_PRIV_CLOCK_PCLKADC:
        case FSP_PRIV_CLOCK_PCLKGPTL:
        {
            clock_hz = g_bsp_system_clock_select[clock][R_SYSC_S->SCKCR2_b.DIVSELSUB];
            break;
        }

        case FSP_PRIV_CLOCK_PCLKSPI0:
        {
            clock_hz = g_bsp_system_clock_select[clock][R_SYSC_NS->SCKCR_b.SPI0ASYNCSEL];
            break;
        }

        case FSP_PRIV_CLOCK_PCLKSPI1:
        {
            clock_hz = g_bsp_system_clock_select[clock][R_SYSC_NS->SCKCR_b.SPI1ASYNCSEL];
            break;
        }

        case FSP_PRIV_CLOCK_PCLKSPI2:
        {
            clock_hz = g_bsp_system_clock_select[clock][R_SYSC_NS->SCKCR_b.SPI2ASYNCSEL];
            break;
        }

        case FSP_PRIV_CLOCK_PCLKSPI3:
        {
            clock_hz = g_bsp_system_clock_select[clock][R_SYSC_S->SCKCR2_b.SPI3ASYNCSEL];
            break;
        }

        case FSP_PRIV_CLOCK_PCLKSCI0:
        {
            clock_hz = g_bsp_system_clock_select[clock][R_SYSC_NS->SCKCR_b.SCI0ASYNCSEL];
            break;
        }

        case FSP_PRIV_CLOCK_PCLKSCI1:
        {
            clock_hz = g_bsp_system_clock_select[clock][R_SYSC_NS->SCKCR_b.SCI1ASYNCSEL];
            break;
        }

        case FSP_PRIV_CLOCK_PCLKSCI2:
        {
            clock_hz = g_bsp_system_clock_select[clock][R_SYSC_NS->SCKCR_b.SCI2ASYNCSEL];
            break;
        }

        case FSP_PRIV_CLOCK_PCLKSCI3:
        {
            clock_hz = g_bsp_system_clock_select[clock][R_SYSC_NS->SCKCR_b.SCI3ASYNCSEL];
            break;
        }

        case FSP_PRIV_CLOCK_PCLKSCI4:
        {
            clock_hz = g_bsp_system_clock_select[clock][R_SYSC_NS->SCKCR_b.SCI4ASYNCSEL];
            break;
        }

        case FSP_PRIV_CLOCK_PCLKSCI5:
        {
            clock_hz = g_bsp_system_clock_select[clock][R_SYSC_S->SCKCR2_b.SCI5ASYNCSEL];
            break;
        }

        case FSP_PRIV_CLOCK_PCLKCAN:
        {
            clock_hz = g_bsp_system_clock_select[clock][R_SYSC_NS->SCKCR_b.FSELCANFD];
            break;
        }

        case FSP_PRIV_CLOCK_CKIO:
        {
            uint32_t ckio = R_SYSC_NS->SCKCR_b.CKIO;
            clock_hz = g_bsp_system_clock_select_ckio[ckio][R_SYSC_S->SCKCR2_b.DIVSELSUB];
            break;
        }

        case FSP_PRIV_CLOCK_XSPI0_CLK:
        {
            uint32_t fselxspi0 = R_SYSC_NS->SCKCR_b.FSELXSPI0;
            clock_hz = g_bsp_system_clock_select_xspi_clk[fselxspi0][R_SYSC_NS->SCKCR_b.DIVSELXSPI0];
            break;
        }

        case FSP_PRIV_CLOCK_XSPI1_CLK:
        {
            uint32_t fselxspi1 = R_SYSC_NS->SCKCR_b.FSELXSPI1;
            clock_hz = g_bsp_system_clock_select_xspi_clk[fselxspi1][R_SYSC_NS->SCKCR_b.DIVSELXSPI1];
            break;
        }

        default:
        {
            break;
        }
    }

    return clock_hz;
}

#if ((1 == BSP_CFG_ERROR_LOG) || (1 == BSP_CFG_ASSERT))

/** Prototype of default function called before errors are returned in FSP code if BSP_CFG_LOG_ERRORS is set to 1. */
void fsp_error_log(fsp_err_t err, const char * file, int32_t line);

#endif

/** @} (end addtogroup BSP_MCU) */

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
