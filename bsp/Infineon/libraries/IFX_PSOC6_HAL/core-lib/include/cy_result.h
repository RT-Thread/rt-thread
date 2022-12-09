/***********************************************************************************************//**
 * \file cy_result.h
 *
 * \brief
 * Basic function result handling. Defines a simple type for conveying
 * information about whether something succeeded or details about any issues
 * that were detected.
 *
 ***************************************************************************************************
 * \copyright
 * Copyright 2018-2021 Cypress Semiconductor Corporation (an Infineon company) or
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
 **************************************************************************************************/

/**
 * \addtogroup group_result Result Type
 * \ingroup group_abstraction
 * \{
 * \anchor anchor_general_description
 * \brief Defines a type and related utilities for function result handling.
 *
 * The @ref cy_rslt_t type is a structured bitfield which encodes information about result type,
 * the originating module, and a code for the specific error (or warning etc). In order to extract
 * these individual fields from a @ref cy_rslt_t value, the utility macros @ref CY_RSLT_GET_TYPE,
 * @ref CY_RSLT_GET_MODULE, and @ref CY_RSLT_GET_CODE are provided. Alternatively, a newer
 * @ref cy_rslt_decode_t, union was created to help make the decoding process easier. The
 * @ref cy_rslt_decode_t also uses enums for the type and module to make decoding even easier.
 * Example uses of both approaches are shown below:
 *
 * Decoding @ref cy_rslt_t directly:
 * \code
 * cy_rslt_t result = cy_hal_do_operation(arg);
 *
 * // Will be CY_RSLT_TYPE_INFO, CY_RSLT_TYPE_WARNING, CY_RSLT_TYPE_ERROR, or CY_RSLT_TYPE_FATAL
 * uint8_t type = CY_RSLT_GET_TYPE(result)
 *
 * // See the "Modules" section for possible values
 * uint16_t module_id = CY_RSLT_GET_MODULE(result);
 *
 * // Specific error codes are defined by each module
 * uint16_t error_code = CY_RSLT_GET_CODE(result);
 *
 * printf("type=%d, module=%d, code=%d\n", type, module_id, error_code);
 * \endcode
 *
 * Using @ref cy_rslt_decode_t to decode:
 * \code
 * cy_rslt_decode_t result;
 * result.raw = cy_hal_do_operation(arg);
 *
 * printf("type=%d, module=%d, code=%d\n", result.type, result.module, result.code);
 * \endcode
 */

#pragma once

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

/** \cond INTERNAL */
/** Mask for the bit at position "x" */
#define CY_BIT_MASK(x)                     ((1UL << (x)) - 1U)

/** Bit position of the result type */
#define CY_RSLT_TYPE_POSITION              (16U)
/** Bit width of the result type */
#define CY_RSLT_TYPE_WIDTH                 (2U)
/** Bit position of the module identifier */
#define CY_RSLT_MODULE_POSITION            (18U)
/** Bit width of the module identifier */
#define CY_RSLT_MODULE_WIDTH               (14U)
/** Bit position of the submodule identifier */
#define CY_RSLT_SUBMODULE_POSITION         (8U)
/** Bit width of the submodule identifier */
#define CY_RSLT_SUBMODULE_WIDTH            (8U)
/** Bit position of the result code */
#define CY_RSLT_CODE_POSITION              (0U)
/** Bit width of the result code */
#define CY_RSLT_CODE_WIDTH                 (16U)

/** Mask for the result type */
#define CY_RSLT_TYPE_MASK                  CY_BIT_MASK(CY_RSLT_TYPE_WIDTH)
/** Mask for the module identifier */
#define CY_RSLT_MODULE_MASK                CY_BIT_MASK(CY_RSLT_MODULE_WIDTH)
/** Mask for the result code */
#define CY_RSLT_CODE_MASK                  CY_BIT_MASK(CY_RSLT_CODE_WIDTH)
/** Mask for submodule identifier */
#define CY_RSLT_SUBMODULE_MASK             CY_BIT_MASK(CY_RSLT_SUBMODULE_WIDTH)

/** \endcond */

/**
 * \{
 * @name Fields
 * Utility macros for constructing result values and extracting individual fields from existing
 * results.
 */

/**
 * @brief Get the value of the result type field
 * @param x the @ref cy_rslt_t value from which to extract the result type
 */
#define CY_RSLT_GET_TYPE(x)                (((x) >> CY_RSLT_TYPE_POSITION) & CY_RSLT_TYPE_MASK)
/**
 * @brief Get the value of the module identifier field
 * @param x the @ref cy_rslt_t value from which to extract the module id
 */
#define CY_RSLT_GET_MODULE(x)              (((x) >> CY_RSLT_MODULE_POSITION) & CY_RSLT_MODULE_MASK)
/**
 * @brief Get the value of the result code field
 * @param x the @ref cy_rslt_t value from which to extract the result code
 */
#define CY_RSLT_GET_CODE(x)                (((x) >> CY_RSLT_CODE_POSITION) & CY_RSLT_CODE_MASK)

/** \} fields */

/**
 * \{
 * @name Result Types
 * Defines codes to identify the type of result.
 */

/**
 * Defines codes to identify the type of result
 */
typedef enum
{
    /** The result code is informational-only */
    CY_RSLT_TYPE_INFO = 0U,
    /** The result code is warning of a problem but will proceed */
    CY_RSLT_TYPE_WARNING = 1U,
    /** The result code is an error */
    CY_RSLT_TYPE_ERROR = 2U,
    /** The result code is a fatal error */
    CY_RSLT_TYPE_FATAL = 3U
} cy_en_rslt_type_t;

/** \} severity */


/**
 * \{
 * @name Modules
 * @anchor anchor_modules
 * Defines codes to identify the module from which an error originated.
 * For some large libraries, a range of module codes is defined here;
 * see the library documentation for values corresponding to individual modules.
 * Valid range is 0x0000-0x4000.
 */

/** Base module identifier for peripheral driver library drivers (0x0000 - 0x007F) */
#define CY_RSLT_MODULE_DRIVERS_PDL_BASE             (0x0000U)
/** \cond INTERNAL */
/** Deprecated. Base module identifier for wireless host driver library modules (0x0080 - 0x00FF) */
#define CY_RSLT_MODULE_DRIVERS_WHD_BASE             (0x0080U)
/** Deprecated. Use @ref CY_RSLT_MODULE_ABSTRACTION_HAL */
#define CY_RSLT_MODULE_ABSTRACTION_HAL_BASE         (0x0100U)
/** Deprecated. Base module identifier for Board Libraries (0x01A0 - 0x01BF) */
#define CY_RSLT_MODULE_BOARD_LIB_BASE               (0x01A0U)
/** Deprecated. Base module identifier for Shield Board Libraries (0x01B8 - 0x01BF) */
#define CY_RSLT_MODULE_BOARD_SHIELD_BASE            (0x01B8U)
/** Deprecated. Base module identifier for Board Hardware Libraries (0x01C0 - 0x01FF) */
#define CY_RSLT_MODULE_BOARD_HARDWARE_BASE          (0x01C0U)
/** Deprecated. Base module identifier for Middleware Libraries (0x0200 - 0x02FF) */
#define CY_RSLT_MODULE_MIDDLEWARE_BASE              (0x0200U)
/** Deprecated. Base identifier for environment abstraction modules (0x0184 - 0x019F) */
#define CY_RSLT_MODULE_ABSTRACTION_ENV              (0x0184U)
/** \endcond */


/**
 * Define codes to identify the module from which an error originated.
 * @note This is provided as a debugging convenience tool, not as a definitive
 * list of all module IDs. Due to the distributed nature of ModusToolbox™, each
 * library has its own release schedule. It is possible that some module IDs
 * may not appear in the enumeration yet. Missing items are expected to be
 * added over time.
 */
typedef enum
{
    /** Module identifier for the SAR driver. Asset(s): (mtb-pdl-cat1, mtb-pdl-cat2) */
    CY_RSLT_MODULE_DRIVER_SAR = 0x0001,
    /** Module identifier for the Device Firmware Update (DFU) driver. Asset(s): (dfu) */
    CY_RSLT_MODULE_DRIVER_DFU = 0x0006,
    /** Module identifier for the Capsense driver. Asset(s): (capsense) */
    CY_RSLT_MODULE_DRIVER_CAPSENSE = 0x0007,
    /** Module identifier for the USB Device driver. Asset(s): (usbdev) */
    CY_RSLT_MODULE_DRIVER_USB_DEV = 0x0008,
    /** Module identifier for the Continuous Time Block (CTB) driver. Asset(s): (mtb-pdl-cat1) */
    CY_RSLT_MODULE_DRIVER_CTB = 0x000b,
    /** Module identifier for the Crypto driver. Asset(s): (mtb-pdl-cat1) */
    CY_RSLT_MODULE_DRIVER_CRYPTO = 0x000c,
    /** Module identifier for the SysPm driver. Asset(s): (mtb-pdl-cat1, mtb-pdl-cat2) */
    CY_RSLT_MODULE_DRIVER_SYSPM = 0x0010,
    /** Module identifier for the SysLib driver. Asset(s): (mtb-pdl-cat1, mtb-pdl-cat2) */
    CY_RSLT_MODULE_DRIVER_SYSLIB = 0x0011,
    /** Module identifier for the SysClk driver. Asset(s): (mtb-pdl-cat1, mtb-pdl-cat2) */
    CY_RSLT_MODULE_DRIVER_SYSCLK = 0x0012,
    /** Module identifier for the DMA driver. Asset(s): (mtb-pdl-cat1) */
    CY_RSLT_MODULE_DRIVER_DMA = 0x0013,
    /** Module identifier for the Flash driver. Asset(s): (mtb-pdl-cat1, mtb-pdl-cat2) */
    CY_RSLT_MODULE_DRIVER_FLASH = 0x0014,
    /** Module identifier for the SysInt driver. Asset(s): (mtb-pdl-cat1, mtb-pdl-cat2) */
    CY_RSLT_MODULE_DRIVER_SYSINT = 0x0015,
    /** Module identifier for the GPIO driver. Asset(s): (mtb-pdl-cat1, mtb-pdl-cat2) */
    CY_RSLT_MODULE_DRIVER_GPIO = 0x0016,
    /** Module identifier for the Programmable Analog Sub System (PASS) driver. Asset(s):
       (mtb-pdl-cat1) */
    CY_RSLT_MODULE_DRIVER_SYSANALOG = 0x0017,
    /** Module identifier for the Continuous Time DAC (CTDAC) driver. Asset(s): (mtb-pdl-cat1) */
    CY_RSLT_MODULE_DRIVER_CTDAC = 0x0019,
    /** Module identifier for the eFuse driver. Asset(s): (mtb-pdl-cat1) */
    CY_RSLT_MODULE_DRIVER_EFUSE = 0x001a,
    /** Module identifier for the Emulated EEPROM driver. Asset(s): (emeeprom) */
    CY_RSLT_MODULE_DRIVER_EM_EEPROM = 0x001b,
    /** Module identifier for the Profile driver. Asset(s): (mtb-pdl-cat1) */
    CY_RSLT_MODULE_DRIVER_PROFILE = 0x001e,
    /** Module identifier for the I2S driver. Asset(s): (mtb-pdl-cat1) */
    CY_RSLT_MODULE_DRIVER_I2S = 0x0020,
    /** Module identifier for the IPC driver. Asset(s): (mtb-pdl-cat1) */
    CY_RSLT_MODULE_DRIVER_IPC = 0x0022,
    /** Module identifier for the Low Power Comparator (LPCOMP) driver. Asset(s): (mtb-pdl-cat1) */
    CY_RSLT_MODULE_DRIVER_LPCOMP = 0x0023,
    /** Module identifier for the PDM-PCM driver. Asset(s): (mtb-pdl-cat1) */
    CY_RSLT_MODULE_DRIVER_PDM_PCM = 0x0026,
    /** Module identifier for the RTC driver. Asset(s): (mtb-pdl-cat1) */
    CY_RSLT_MODULE_DRIVER_RTC = 0x0028,
    /** Module identifier for the Serial Communications Block (SCB) driver.
       Asset(s): (mtb-pdl-cat1, mtb-pdl-cat2) */
    CY_RSLT_MODULE_DRIVER_SCB = 0x002a,
    /** Module identifier for the Serial Memory Interface (SMIF) driver. Asset(s): (mtb-pdl-cat1) */
    CY_RSLT_MODULE_DRIVER_SMIF = 0x002c,
    /** Module identifier for the Timer/Counter/PWM (TCPWM) driver.
       Asset(s): (mtb-pdl-cat1, mtb-pdl-cat2) */
    CY_RSLT_MODULE_DRIVER_TCPWM = 0x002d,
    /** Module identifier for the Protection driver. Asset(s): (mtb-pdl-cat1) */
    CY_RSLT_MODULE_DRIVER_PROT = 0x0030,
    /** Module identifier for the TRIGMUX driver. Asset(s): (mtb-pdl-cat1, mtb-pdl-cat2) */
    CY_RSLT_MODULE_DRIVER_TRIGMUX = 0x0033,
    /** Module identifier for the WDT driver. Asset(s): (mtb-pdl-cat1, mtb-pdl-cat2) */
    CY_RSLT_MODULE_DRIVER_WDT = 0x0034,
    /** Module identifier for the (WDC / MCWDT) driver. Asset(s): (mtb-pdl-cat1, mtb-pdl-cat2) */
    CY_RSLT_MODULE_DRIVER_MCWDT = 0x0035,
    /** Module identifier for the LVD driver. Asset(s): (mtb-pdl-cat1) */
    CY_RSLT_MODULE_DRIVER_LVD = 0x0039,
    /** Module identifier for the SD_HOST driver. Asset(s): (mtb-pdl-cat1) */
    CY_RSLT_MODULE_DRIVER_SD_HOST = 0x003a,
    /** Module identifier for the USBFS driver. Asset(s): (mtb-pdl-cat1) */
    CY_RSLT_MODULE_DRIVER_USBFS = 0x003b,
    /** Module identifier for the DMAC driver. Asset(s): (mtb-pdl-cat1, mtb-pdl-cat2) */
    CY_RSLT_MODULE_DRIVER_DMAC = 0x003f,
    /** Module identifier for the SegLCD driver. Asset(s): (mtb-pdl-cat1) */
    CY_RSLT_MODULE_DRIVER_SEGLCD = 0x0040,
    /** Module identifier for the CSD driver. Asset(s): (mtb-pdl-cat1, mtb-pdl-cat2) */
    CY_RSLT_MODULE_DRIVER_CSD = 0x0041,
    /** Module identifier for the SmartIO driver. Asset(s): (mtb-pdl-cat1, mtb-pdl-cat2) */
    CY_RSLT_MODULE_DRIVER_SMARTIO = 0x0042,
    /** Module identifier for the CSDIDAC driver. Asset(s): (csdidac) */
    CY_RSLT_MODULE_DRIVER_CSDIDAC = 0x0044,
    /** Module identifier for the CAN FD driver. Asset(s): (mtb-pdl-cat1, mtb-pdl-cat2) */
    CY_RSLT_MODULE_DRIVER_CANFD = 0x0045,
    /** Module identifier for the MSC driver. Asset(s): (mtb-pdl-cat2) */
    CY_RSLT_MODULE_DRIVER_MSC = 0x0047,
    /** Module identifier for the WiFi Host Driver. Asset(s): (wifi-host-driver) */
    CY_RSLT_MODULE_DRIVER_WHD = 0x0080,

    /** Module identifier for the Hardware Abstraction Layer.
       Asset(s): (mtb-hal-cat1, mtb-hal-cat2, ...) */
    CY_RSLT_MODULE_ABSTRACTION_HAL = 0x0100,
    /** Module identifier for board support package. Asset(s): (BSPs) */
    CY_RSLT_MODULE_ABSTRACTION_BSP = 0x0180,
    /** Module identifier for file system abstraction */
    CY_RSLT_MODULE_ABSTRACTION_FS = 0x0181,
    /** Module identifier for resource abstraction. Asset(s): (abstraction-resource) */
    CY_RSLT_MODULE_ABSTRACTION_RESOURCE = 0x0182,
    /** Module identifier for RTOS abstraction. Asset(s): (abstraction-rtos) */
    CY_RSLT_MODULE_ABSTRACTION_OS = 0x0183,

    /** Module identifier for the Retarget IO Board Library. Asset(s): (retarget-io) */
    CY_RSLT_MODULE_BOARD_LIB_RETARGET_IO = 0x1A0,
    /** Module identifier for the RGB LED Board Library. Asset(s): (rgb-led) */
    CY_RSLT_MODULE_BOARD_LIB_RGB_LED = 0x01A1,
    /** Module identifier for the Serial Flash Board Library. Asset(s): (serial-flash) */
    CY_RSLT_MODULE_BOARD_LIB_SERIAL_FLASH = 0x01A2,
    /** Module identifier for the WiFi Host Driver + Board Support Integration Library.
       Asset(s): (whd-bsp-integration) */
    CY_RSLT_MODULE_BOARD_LIB_WHD_INTEGRATION = 0x01A3,

    /** Module identifier for Shield Board CY8CKIT-028-EPD. Asset(s): (CY8CKIT-028-EPD) */
    CY_RSLT_MODULE_BOARD_SHIELD_028_EPD = 0x01B8,
    /** Module identifier for Shield Board CY8CKIT-028-TFT. Asset(s): (CY8CKIT-028-TFT) */
    CY_RSLT_MODULE_BOARD_SHIELD_028_TFT = 0x01B9,
    /** Module identifier for Shield Board CY8CKIT-032. Asset(s): (CY8CKIT-032) */
    CY_RSLT_MODULE_BOARD_SHIELD_032 = 0x01BA,
    /** Module identifier for Shield Board CY8CKIT-028-SENSE. Asset(s): (CY8CKIT-028-SENSE) */
    CY_RSLT_MODULE_BOARD_SHIELD_028_SENSE = 0x01BB,

    /** Module identifier for the BMI160 Motion Sensor Library. Asset(s): (sensor-motion-bmi160) */
    CY_RSLT_MODULE_BOARD_HARDWARE_BMI160 = 0x01C0,
    /** Module identifier for the E2271CS021 E-Ink Controller Library.
       Asset(s): (display-eink-e2271cs021) */
    CY_RSLT_MODULE_BOARD_HARDWARE_E2271CS021 = 0x01C1,
    /** Module identifier for the NTC GPIO Thermistor Library. Asset(s): (thermistor) */
    CY_RSLT_MODULE_BOARD_HARDWARE_THERMISTOR = 0x01C2,
    /** Module identifier for the SSD1306 OLED Controller Library.
       Asset(s): (display-oled-ssd1306) */
    CY_RSLT_MODULE_BOARD_HARDWARE_SSD1306 = 0x01C3,
    /** Module identifier for the ST7789V TFT Controller Library. Asset(s): (display-tft-st7789v) */
    CY_RSLT_MODULE_BOARD_HARDWARE_ST7789V = 0x01C4,
    /** Module identifier for the Light Sensor Library. Asset(s): (sensor-light) */
    CY_RSLT_MODULE_BOARD_HARDWARE_LIGHT_SENSOR = 0x01C5,
    /** Module identifier for the AK4954A Audio Codec Library. Asset(s): (audio-codec-ak4954a) */
    CY_RSLT_MODULE_BOARD_HARDWARE_AK4954A = 0x01C6,
    /** Module identifier for the BMI160 Motion Sensor Library.
       Asset(s): (sensor-orientation-bmx160) */
    CY_RSLT_MODULE_BOARD_HARDWARE_BMX160 = 0x01C7,
    /** Module identifier for the XENSIV™  DPS3XX Pressure Sensor Library */
    CY_RSLT_MODULE_BOARD_HARDWARE_DPS3XX = 0x01C8,
    /** Module identifier for the WM8960 Audio Codec Library */
    CY_RSLT_MODULE_BOARD_HARDWARE_WM8960 = 0x01C9,

    /** Module identifier for the MDNS library. Asset(s): (mdns) */
    CY_RSLT_MODULE_MIDDLEWARE_MNDS = 0x200,
    /** Module identifier for the ASW IoT library. Asset(s): (aws-iot) */
    CY_RSLT_MODULE_MIDDLEWARE_AWS = 0x201,
    /** Module identifier for the JSON parser library. Asset(s): (connectivity-utilities) */
    CY_RSLT_MODULE_MIDDLEWARE_JSON = 0x202,
    /** Module identifier for the Linked List library. Asset(s): (connectivity-utilities) */
    CY_RSLT_MODULE_MIDDLEWARE_LINKED_LIST = 0x203,
    /** Module identifier for the Command Console library. Asset(s): (command-console) */
    CY_RSLT_MODULE_MIDDLEWARE_COMMAND_CONSOLE = 0x204,
    /** Module identifier for the HTTP Server library. Asset(s): (http-server) */
    CY_RSLT_MODULE_MIDDLEWARE_HTTP_SERVER = 0x205,
    /** Module identifier for the Enterprise Security library. Asset(s): (enterprise-security) */
    CY_RSLT_MODULE_MIDDLEWARE_ENTERPRISE_SECURITY = 0x206,
    /** Module identifier for the TCP/IP library. Asset(s): (connectivity-utilities) */
    CY_RSLT_MODULE_MIDDLEWARE_TCPIP = 0x207,
    /** Module identifier for the Generic middleware library.
       Asset(s): (connectivity-utilities, wifi-mw-core) */
    CY_RSLT_MODULE_MIDDLEWARE_MW = 0x208,
    /** Module identifier for the TLS library. Asset(s): (cy-mbedtls) */
    CY_RSLT_MODULE_MIDDLEWARE_TLS = 0x209,
    /** Module identifier for the Secure Sockets library. Asset(s): (secure-sockets) */
    CY_RSLT_MODULE_MIDDLEWARE_SECURE_SOCKETS = 0x20a,
    /** Module identifier for the WiFi Connection Manager library (WCM).
       Asset(s): (wifi-connection-manager) */
    CY_RSLT_MODULE_MIDDLEWARE_WCM = 0x20b,
    /** Module identifier for the lwIP WHD port library. Asset(s): (wifi-mw-core) */
    CY_RSLT_MODULE_MIDDLEWARE_LWIP_WHD_PORT = 0x20c,
    /** Module identifier for the OTA Update library. Asset(s): (anycloud-ota) */
    CY_RSLT_MODULE_MIDDLEWARE_OTA_UPDATE = 0x20d,
    /** Module identifier for the HTTP Clinet library. Asset(s): (http-client) */
    CY_RSLT_MODULE_MIDDLEWARE_HTTP_CLIENT = 0x20e,
    /** Module identifier for the Machine Learning(ML) library. Asset(s): (ml-middleware) */
    CY_RSLT_MODULE_MIDDLEWARE_ML = 0x20f,

    /** Module identifier for the KV Store Middleware Library. Asset(s): (kv-store) */
    CY_RSLT_MODULE_MIDDLEWARE_KVSTORE = 0x250,
    /** Module identifier for the LIN Middleware Library. Asset(s): (lin) */
    CY_RSLT_MODULE_MIDDLEWARE_LIN = 0x0251
} cy_en_rslt_module_t;

/** \} modules */

/**
 * @brief Provides the result of an operation as a structured bitfield.
 *
 * @note A newer version @ref cy_rslt_decode_t is also available for improved
 * debugging experience.
 *
 * See the \ref anchor_general_description "General Description"
 * for more details on structure and usage.
 */
typedef uint32_t cy_rslt_t;

/**
 * @brief Provides the result of an operation as a structured bitfield.
 *
 * This is an updated version of @ref cy_rslt_t that pulls the individual
 * fields out into their own members for easier readability. The organization
 * and meaning of items is exactly the same. The new version can be used as follows:
 * cy_rslt_decode_t result;
 * result.raw = my_function_that_returns_cy_rslt_t();
 *
 * See the @ref anchor_general_description "General Description"
 * for more details on structure and usage.
 */
typedef union
{
    cy_rslt_t raw;                                          //!< The raw uint32/cy_rslt_t value
    /** Anonymous struct breaking out each of the fields of the result type */
    struct
    {
        uint16_t code : CY_RSLT_CODE_WIDTH;                 //!< The 16bit result code
        cy_en_rslt_type_t type : CY_RSLT_TYPE_WIDTH;        //!< The  2bit result type
        cy_en_rslt_module_t module : CY_RSLT_MODULE_WIDTH;  //!< The 14bit module id
    };
} cy_rslt_decode_t;

/** @ref cy_rslt_t return value indicating success */
#define CY_RSLT_SUCCESS                    ((cy_rslt_t)0x00000000U)

/**
 * @brief Create a new @ref cy_rslt_t value that encodes the specified type, module, and result
 * code.
 * @param type one of @ref CY_RSLT_TYPE_INFO, @ref CY_RSLT_TYPE_WARNING,
 *  @ref CY_RSLT_TYPE_ERROR, @ref CY_RSLT_TYPE_FATAL
 * @param module Identifies the module where this result originated; see @ref anchor_modules
 * "Modules".
 * @param code a module-defined identifier to identify the specific situation that
 * this result describes.
 */
#define CY_RSLT_CREATE(type, module, code) \
    ((((uint16_t) (module) & CY_RSLT_MODULE_MASK) << CY_RSLT_MODULE_POSITION) | \
    ((((uint16_t) code) & CY_RSLT_CODE_MASK) << CY_RSLT_CODE_POSITION) | \
    ((((uint16_t) type) & CY_RSLT_TYPE_MASK) << CY_RSLT_TYPE_POSITION))

/**
 * @brief Create a new @ref cy_rslt_t value that encodes the specified type, module and
 * result code. This is a variant of @ref CY_RSLT_CREATE for result codes that need to handle
 * submodules as well.
 * @param type one of @ref CY_RSLT_TYPE_INFO, @ref CY_RSLT_TYPE_WARNING,
 *  @ref CY_RSLT_TYPE_ERROR, @ref CY_RSLT_TYPE_FATAL
 * @param module Identifies the module where this result originated; see @ref anchor_modules
 * "Modules".
 * @param submodule An asset defined subset of the module. The submodule consumes part
 * of the "code" section and thus the size of the valid code is then reduced.
 * @param code a module-defined identifier to identify the specific situation that
 * this result describes.
 */
#define CY_RSLT_CREATE_EX(type, module, submodule, code) \
    (((((uint16_t) module) & CY_RSLT_MODULE_MASK) << CY_RSLT_MODULE_POSITION) | \
    ((((((((uint16_t)submodule) & CY_RSLT_SUBMODULE_MASK) << CY_RSLT_SUBMODULE_POSITION) | \
    ((uint16_t) code)) & CY_RSLT_CODE_MASK) << CY_RSLT_CODE_POSITION)) | \
    ((((uint16_t) type) & CY_RSLT_TYPE_MASK) << CY_RSLT_TYPE_POSITION))

#ifdef __cplusplus
}
#endif

/** \} group_result */
