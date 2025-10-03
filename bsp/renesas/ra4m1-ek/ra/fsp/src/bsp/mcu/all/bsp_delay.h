/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BSP_DELAY_H
#define BSP_DELAY_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

#include "bsp_compiler_support.h"

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* The number of cycles required per software delay loop. */
#ifndef BSP_DELAY_LOOP_CYCLES
 #if defined(RENESAS_CORTEX_M85)

/* On M85 cores, code alignment can affect execution speed. bsp_prv_software_delay_loop is aligned to 8 bytes for
 * GCC and AC6, but IAR does not support aligning code. The below ensures the correct loop cycle count is used in
 * this case. */
  #if defined(__ICCARM__)
   #define BSP_DELAY_LOOP_CYCLES    (((uint32_t) bsp_prv_software_delay_loop & 0x6) ? 2 : 1)
  #else
   #define BSP_DELAY_LOOP_CYCLES    (1)
  #endif

/* On devices with Flash LP, ROM reads take an additional cycle when ICLK is greater than 32 MHz. */
 #elif BSP_FEATURE_CGC_HAS_MEMWAIT && !BSP_FEATURE_BSP_FLASH_CACHE && (BSP_FEATURE_BSP_CODE_CACHE_VERSION == 0)
  #define BSP_DELAY_LOOP_CYCLES     (4 + (2 * (uint32_t) (SystemCoreClock > 32000000)))
 #else
  #define BSP_DELAY_LOOP_CYCLES     (4)
 #endif
#endif

/* Calculates the number of delay loops to pass to bsp_prv_software_delay_loop to achieve at least the requested cycle
 * count delay. This is 1 loop longer than optimal if cycles is a multiple of BSP_DELAY_LOOP_CYCLES, but it ensures
 * the requested number of loops is at least 1 since bsp_prv_software_delay_loop cannot be called with a loop count
 * of 0. */
#define BSP_DELAY_LOOPS_CALCULATE(cycles)    (((cycles) / BSP_DELAY_LOOP_CYCLES) + 1U)

/** Available delay units for R_BSP_SoftwareDelay(). These are ultimately used to calculate a total # of microseconds */
typedef enum
{
    BSP_DELAY_UNITS_SECONDS      = 1000000, ///< Requested delay amount is in seconds
    BSP_DELAY_UNITS_MILLISECONDS = 1000,    ///< Requested delay amount is in milliseconds
    BSP_DELAY_UNITS_MICROSECONDS = 1        ///< Requested delay amount is in microseconds
} bsp_delay_units_t;

/** @} (end addtogroup BSP_MCU) */

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
BSP_ATTRIBUTE_STACKLESS void bsp_prv_software_delay_loop(uint32_t loop_cnt);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
