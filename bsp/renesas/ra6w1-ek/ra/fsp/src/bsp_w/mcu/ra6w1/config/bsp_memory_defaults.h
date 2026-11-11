/**
 * \addtogroup PLA_BSP_CONFIG
 * \{
 * \addtogroup BSP_MEMORY_DEFAULTS Memory Default Configuration Values
 *
 * \brief BSP memory default configuration values
 * \{
 */

/**
 ****************************************************************************************
 *
 * @file bsp_memory_defaults.h
 *
 * @brief Board Support Package. Memory Configuration file default values.
 *
 * Copyright (c) 2023 Renesas Electronics. All rights reserved.
 *
 * This software ("Software") is owned by Renesas Electronics.
 *
 * By using this Software you agree that Renesas Electronics retains all
 * intellectual property and proprietary rights in and to this Software and any
 * use, reproduction, disclosure or distribution of the Software without express
 * written permission or a license agreement from Renesas Electronics is
 * strictly prohibited. This Software is solely for use on or in conjunction
 * with Renesas Electronics products.
 *
 * EXCEPT AS OTHERWISE PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, THE
 * SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. EXCEPT AS OTHERWISE
 * PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, IN NO EVENT SHALL
 * RENESAS ELECTRONICS BE LIABLE FOR ANY DIRECT, SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THE SOFTWARE.
 *
 ****************************************************************************************
 */

#ifndef BSP_MEMORY_DEFAULTS_H_
#define BSP_MEMORY_DEFAULTS_H_

#define PARTITION2(...)
#include "partition_table.h"
#undef PARTITION2

/* ---------------------------------------------------------------------------------------------- */

/*************************************************************************************************\
 * Default configuration for retention RAM
 */
#if !defined(RELEASE_BUILD) && (dg_configOPTIMAL_RETRAM == 1)

/* WARNING: retRAM optimizations are disabled in DEBUG builds! */
 #undef dg_configOPTIMAL_RETRAM
 #define dg_configOPTIMAL_RETRAM    (0)
#elif (dg_configEXEC_MODE != MODE_IS_CACHED)

/* WARNING: retRAM optimizations are not applicable in MIRRORED mode! */
 #undef dg_configOPTIMAL_RETRAM
 #define dg_configOPTIMAL_RETRAM    (0)
#endif

/* -------------------------- INCLUDE MEMORY LAYOUT CONFIGURATION ------------------------------- */

#if (DEVICE_FAMILY == DA1640X)
 #include "bsp_memory_defaults_ra6w1.h"
#endif

#endif                                 /* BSP_MEMORY_DEFAULTS_H_ */

/**
 * \}
 *
 * \}
 */

/* EOF */
