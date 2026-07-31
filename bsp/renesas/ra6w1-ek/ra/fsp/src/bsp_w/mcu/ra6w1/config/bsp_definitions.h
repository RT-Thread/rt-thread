/**
 * \addtogroup PLA_BSP_CONFIG
 * \{
 * \addtogroup BSP_CONFIG_DEFINITIONS Configuration Definitions
 *
 * \brief Doxygen documentation is not yet available for this module.
 *        Please check the source code file(s)
 *
 *\{
 */

/**
 ****************************************************************************************
 *
 * @file bsp_definitions.h
 *
 * @brief Board Support Package. System Configuration file definitions.
 *
 * Copyright (c) 2023-2024 Renesas Electronics. All rights reserved.
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

#ifndef BSP_DEFINITIONS_H_
#define BSP_DEFINITIONS_H_

/* ------------------------------------ DEVICE DEFINITIONS -------------------------------------- */

#include "bsp_device_definitions.h"

/* ------------------------------------ Generic definitions ------------------------------------- */

#define PRO_DK_DA1469x_BRD                     1
#define PRO_DK_DA1468x_BRD                     2
#define FPGA_DA1469x_BRD                       3
#define FPGA_DA1468x_BRD                       4

#define LP_CLK_IS_ANALOG                       0
#define LP_CLK_IS_DIGITAL                      1

#define MODE_IS_MIRRORED                       0
#define MODE_IS_CACHED                         1
#define MODE_IS_RAM                            MODE_IS_MIRRORED

#define NON_VOLATILE_IS_OTP                    0 // Code is in OTP
#define NON_VOLATILE_IS_FLASH                  1 // Code is in QSPI Flash
#define NON_VOLATILE_IS_NONE                   2 // Debug mode! Code is in RAM!

#define EXT_CRYSTAL_IS_16M                     0
#define EXT_CRYSTAL_IS_32M                     1

#define DEVELOPMENT_MODE                       0 // Code is built for debugging
#define PRODUCTION_MODE                        1 // Code is built for production

#define FLASH_IS_NOT_CONNECTED                 0
#define FLASH_CONNECTED_TO_1V8                 1
#define FLASH_CONNECTED_TO_1V8P                2
#define FLASH_CONNECTED_TO_1V8F                3

#define BATTERY_TYPE_2xNIMH                    0
#define BATTERY_TYPE_3xNIMH                    1
#define BATTERY_TYPE_LICOO2                    2 // 2.5V discharge voltage, 4.20V charge voltage
#define BATTERY_TYPE_LIMN2O4                   3 // 2.5V discharge voltage, 4.20V charge voltage
#define BATTERY_TYPE_NMC                       4 // 2.5V discharge voltage, 4.20V charge voltage
#define BATTERY_TYPE_LIFEPO4                   5 // 2.5V discharge voltage, 3.65V charge voltage
#define BATTERY_TYPE_LINICOAIO2                6 // 3.0V discharge voltage, 4.20V charge voltage
#define BATTERY_TYPE_CUSTOM                    7
#define BATTERY_TYPE_NO_RECHARGE               8
#define BATTERY_TYPE_NO_BATTERY                9

#define BATTERY_TYPE_2xNIMH_ADC_VOLTAGE        (2785)
#define BATTERY_TYPE_3xNIMH_ADC_VOLTAGE        (4013)
#define BATTERY_TYPE_LICOO2_ADC_VOLTAGE        (3440)
#define BATTERY_TYPE_LIMN2O4_ADC_VOLTAGE       (3440)
#define BATTERY_TYPE_NMC_ADC_VOLTAGE           (3440)
#define BATTERY_TYPE_LIFEPO4_ADC_VOLTAGE       (2989)
#define BATTERY_TYPE_LINICOAIO2_ADC_VOLTAGE    (3440)

/*
 * Legacy DK motherboards, which are not supported by the SDK.
 * The definitions exist just so that we don't break compilation of old projects.
 */
#define BLACK_ORCA_MB_REV_A                    0
#define BLACK_ORCA_MB_REV_B                    1

/*
 * The supported DK motherboards.
 */
#define BLACK_ORCA_MB_REV_D                    2

#if (DEVICE_FAMILY == DA1468X)

/*
 * The cache associativity options.
 */
 #define CACHE_ASSOC_AS_IS                     (-1) /// leave as set by the ROM booter
 #define CACHE_ASSOC_DIRECT_MAP                0    /// direct-mapped
 #define CACHE_ASSOC_2_WAY                     1    /// 2-way set associative
 #define CACHE_ASSOC_4_WAY                     2    /// 4-way set associative

/*
 * The cache line size options.
 */
 #define CACHE_LINESZ_AS_IS                    (-1) /// leave as set by the ROM booter
 #define CACHE_LINESZ_8_BYTES                  0    /// 8 bytes
 #define CACHE_LINESZ_16_BYTES                 1    /// 16 bytes
 #define CACHE_LINESZ_32_BYTES                 2    /// 32 bytes
#endif /* DA1468X */

/*
 * The supported RF Front-End Modules
 */
#define FEM_NOFEM                              0
#define FEM_SKY66112_11                        1

/*
 * The BLE event notification user hook types
 */
#define BLE_EVENT_NOTIF_USER_ISR               0 /// User-defined hooks directly from ISR context
#define BLE_EVENT_NOTIF_USER_TASK              1 /// Notification of the user task, using task notifications.

/*
 * Definitions for the different USB suspend modes.
 */
#define USB_SUSPEND_MODE_NONE                  0 /// No action, just stop the PLL clock
#define USB_SUSPEND_MODE_PAUSE                 1 /// Pause the system and wake only from VBUS and USB interrupts
#define USB_SUSPEND_MODE_IDLE                  2 /// System state changes to idle

#define COEX_NONE                              0
#define COEX_LEGACY                            1
#define COEX_2WAY                              2
#define COEX_3WAY                              3

/*
 * Definitions DRIVE_STRENGTH for AA
 */
#define DRIVE_STRENGTH_2MA                     (0) ///< Sets pad drive strength 2 mA
#define DRIVE_STRENGTH_12MA                    (1) ///< Sets pad drive strength 12 mA
#define DRIVE_STRENGTH_4MA                     (2) ///< Sets pad drive strength 4 mA
#define DRIVE_STRENGTH_18MA                    (3) ///< Sets pad drive strength 18 mA

/*
 * Definitions DRIVE_STRENGTH for BA
 */
#define DRIVE_STRENGTH_BA_2MA                  (0) ///< Sets pad drive strength 2 mA
#define DRIVE_STRENGTH_BA_4MA                  (1) ///< Sets pad drive strength 4 mA
#define DRIVE_STRENGTH_BA_8MA                  (2) ///< Sets pad drive strength 8 mA
#define DRIVE_STRENGTH_BA_14MA                 (3) ///< Sets pad drive strength 14 mA

#endif /* BSP_DEFINITIONS_H_ */

/**
 \}
 \}
 */
