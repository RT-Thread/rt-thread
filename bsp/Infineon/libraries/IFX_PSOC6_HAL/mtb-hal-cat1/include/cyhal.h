/*******************************************************************************
* File Name: cyhal.h
*
* Description:
* Top-level HAL header file that can be referenced to pull in all relevant
* drivers for the current device architecture. Not all of these may be
* supported in the current target device. The implementation must provide a
* cyhal_hw_types.h and a cyhal_drivers.h file in the include path for this
* to depend on.
* The cyhal_hw_types.h file must provide the following:
*   1) definitions for each of the resource types consumed by the HAL driver
*      functions.
*   2) A CYHAL_ISR_PRIORITY_DEFAULT define for the default interrupt priority
*   3) A CYHAL_MAIN_FLASH_BASE define for the base address of flash memory
*   4) OPTIONAL: Implementation specific header files can be used by creating
*      a #define in cyhal_hw_types.h with a name of CYHAL_<DRIVER>_IMPL_HEADER
*      and the value being the name of the header file.  eg:
*      #define CYHAL_GPIO_IMPL_HEADER "cyhal_gpio_impl.h"
* The cyhal_drivers.h file must simply be a list of include directives to pull
* in the relevant driver header files.
*
********************************************************************************
* \copyright
* Copyright 2018-2022 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/**
* \addtogroup group_hal_types HAL General Types/Macros
* This section documents the basic types and macros that are used by multiple HAL drivers.
*/

/**
* \addtogroup group_result Result Type
* \ingroup group_hal_types
*/

/**
* \addtogroup group_hal_availability HAL Driver Availability
* This section documents the macros that can be used to check if a specific driver is available
* for the current device. This includes macros for all HAL drivers that exist for any device, even
* those that are not applicable (included) with this library. This is intended to help write code
* that can port between device categories that might not have the same drivers available.
*/

/**
* \addtogroup group_hal HAL Drivers
* This section documents the drivers which form the stable API of the ModusToolboxâ„¢ HAL.
* In order to remain portable across platforms and HAL versions, applications should
* rely only on functionality documented in this section.
*/

/**
* \addtogroup group_hal_impl
*/

#pragma once

#if defined(CY_USING_HAL)
#include "cyhal_general_types.h"
#include "cyhal_hw_types.h"
#include "cyhal_drivers.h"
#endif

/** Macro specifying the major version number of the HAL API. Since there are multiple HAL library
 * implementations, this is not necessarily the same as the major version number of the library. It
 * is instead intended as a single version number that can be used across implementation libraries
 * to know what signatures to use in the case an API is updated in the future. Once an API is
 * available, its API will remain consistant across libraries sharing the same version here.
 * \note Support for new drivers/functionality may be added without changing the version number, to
 * check for whether a specific driver is available, the CYHAL_DRIVER_AVAILABLE_X macros defined in
 * \ref group_hal_availability should be used.
 * \def CYHAL_API_VERSION
*/

/**
* \ingroup group_hal_availability
* \{
*/

/** Macro specifying whether the ADC driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_ADC
*/
/** Macro specifying whether the Clock driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_CLOCK
*/
/** Macro specifying whether the COMP driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_COMP
*/
/** Macro specifying whether the CRC driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_CRC
*/
/** Macro specifying whether the DAC driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_DAC
*/
/** Macro specifying whether the DMA driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_DMA
*/
/** Macro specifying whether the EzI2C driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_EZI2C
*/
/** Macro specifying whether the Flash driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_FLASH
*/
/** Macro specifying whether the GPIO driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_GPIO
*/
/** Macro specifying whether the HwMgr driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_HWMGR
*/
/** Macro specifying whether the I2C driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_I2C
*/
/** Macro specifying whether the I2S driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_I2S
*/
/** Macro specifying whether the IPC driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_IPC
*/
/** Macro specifying whether the TX functionality is available on the I2S driver for the current device \def CYHAL_DRIVER_AVAILABLE_I2S_TX
*/
/** Macro specifying whether the RX functionality is available on the I2S driver for the current device \def CYHAL_DRIVER_AVAILABLE_I2S_RX
*/
/** Macro specifying whether the Interconnect driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_INTERCONNECT
*/
/** Macro specifying whether the KeyScan driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_KEYSCAN
*/
/** Macro specifying whether the LPTimer driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_LPTIMER
*/
/** Macro specifying whether the OpAmp driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_OPAMP
*/
/** Macro specifying whether the PDM/PCM driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_PDMPCM
*/
/** Macro specifying whether the PWM driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_PWM
*/
/** Macro specifying whether the QSPI driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_QSPI
*/
/** Macro specifying whether the QuadDec driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_QUADDEC
*/
/** Macro specifying whether the RTC driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_RTC
*/
/** Macro specifying whether the SDHC driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_SDHC
*/
/** Macro specifying whether the SDIO driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_SDIO
*/
/** Macro specifying whether the SPI driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_SPI
*/
/** Macro specifying whether the SysPM driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_SYSPM
*/
/** Macro specifying whether the System driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_SYSTEM
*/
/** Macro specifying whether the TDM driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_TDM
*/
/** Macro specifying whether the TX functionality is available on the TDM driver for the current device \def CYHAL_DRIVER_AVAILABLE_TDM_TX
*/
/** Macro specifying whether the RX functionality is available on the TDM driver for the current device \def CYHAL_DRIVER_AVAILABLE_TDM_RX
*/
/** Macro specifying whether the Timer driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_TIMER
*/
/** Macro specifying whether the TRNG driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_TRNG
*/
/** Macro specifying whether the UART driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_UART
*/
/** Macro specifying whether the USB Dev driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_USB_DEV
*/
/** Macro specifying whether the WDT driver is available for the current device \def CYHAL_DRIVER_AVAILABLE_WDT
*/

/** \} group_hal_availability */
