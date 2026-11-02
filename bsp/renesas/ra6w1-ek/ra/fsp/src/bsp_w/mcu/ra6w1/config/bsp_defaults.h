/**
 * \addtogroup PLA_BSP_CONFIG
 * \{
 * \addtogroup BSP_CONFIG_DEFAULTS BSP Default Configuration Values
 *
 * \brief Board support package default configuration values
 * \{
 */

/**
 ****************************************************************************************
 *
 * @file bsp_defaults.h
 *
 * @brief Board Support Package. System configuration default values.
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

#ifndef BSP_DEFAULTS_H_
#define BSP_DEFAULTS_H_

#include "../bsp_feature.h"

/* ---------------------------------------------------------------------------------------------- */

#if DEVICE_FPGA

/* Use FPGA-specific definitions first! */
 #include "bsp_defaults_fpga.h"
#endif

/* ----------------------------------- Deprecated Configuration --------------------------------- */

/* Deprecated configuration options must not be defined by the application. */

#define DG_CONFIG_DEPRECATED_MSG        " must not be defined by the application. This option is NO LONGER SUPPORTED"
#define DG_CONFIG_NOT_APPLICABLE_MSG    " must not be defined by the application. It is NOT APPLICABLE"

#ifdef dg_configPOWER_CONFIG
 #error "dg_configPOWER_CONFIG must not be defined by the application. This option is NO LONGER SUPPORTED." \
    " There's a single power configuration setup."
#endif

#ifdef dg_configFORCE_DEEP_SLEEP
 #error "dg_configFORCE_DEEP_SLEEP must not be defined by the application. This option is NO LONGER SUPPORTED." \
    " Forcing the system to enter into clockless sleep during deep sleep is no longer supported."
#endif

#ifdef dg_configMEM_RETENTION_MODE_PRESERVE_IMAGE
 #error \
    "dg_configMEM_RETENTION_MODE_PRESERVE_IMAGE must not be defined by the application. This option is NO LONGER SUPPORTED."
#endif

#ifdef dg_configUSE_ADC
 #error "dg_configUSE_ADC must not be defined by the application. This option is NO LONGER SUPPORTED." \
    " Specify the ADC block you wish to configure (i.e. dg_configUSE_HW_GPADC)."
#endif

#ifdef dg_configCONFIG_HEADER_IN_FLASH
 #error "dg_configCONFIG_HEADER_IN_FLASH must not be defined by the application. This option is NO LONGER SUPPORTED." \
    " The values of the trim registers are not anymore taken from the Flash."
#endif

#ifdef dg_configPOWER_EXT_1V8_PERIPHERALS
 #error "dg_configPOWER_EXT_1V8_PERIPHERALS must not be defined by the application. This option is NO LONGER SUPPORTED." \
    " Use dg_configPOWER_1V8P instead!"
#endif

#ifdef dg_configUSE_HW_TEMPSENS
 #error "dg_configUSE_HW_TEMPSENS must not be defined by the application. This option is NO LONGER SUPPORTED." \
    " Use dg_configUSE_HW_GPADC and HW_GPADC_INPUT_SE_TEMPSENS instead!"
#endif

#ifdef dg_configINITIAL_SLEEP_DELAY_TIME
 #pragma message "dg_configINITIAL_SLEEP_DELAY_TIME" DG_CONFIG_DEPRECATED_MSG ". At startup, the system will stay " \
    "active for at least dg_configXTAL32K_SETTLE_TIME before it is allowed to go to sleep."
#endif

#ifdef dg_configPOWER_FLASH
 #pragma message "dg_configPOWER_FLASH" DG_CONFIG_DEPRECATED_MSG
 #undef  dg_configPOWER_FLASH
#endif

/* --------------------------------- Clock settings -------------------------------------------- */

/**
 * \addtogroup CLOCK_SETTINGS Clock Settings (Low Power, XTAL etc.)
 *
 * \brief Settings for the different clock-types of the chip
 * \{
 */

/**
 * \brief Source of Low Power clock used (LP_CLK_IS_ANALOG, LP_CLK_IS_DIGITAL)
 */
#ifndef dg_configLP_CLK_SOURCE
 #define dg_configLP_CLK_SOURCE    LP_CLK_IS_ANALOG
#endif

#if ((dg_configLP_CLK_SOURCE == LP_CLK_IS_DIGITAL) && (BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_LP_CLK_RCX))
 #error "When the LP source is digital (External), the option BSP_CLOCKS_SOURCE_LP_CLK_RCX is invalid!"
#endif

/**
 * \brief External LP type
 *
 * - 0: a crystal is connected to XTAL32Kp and XTALK32Km
 * - 1: a digital clock is provided.
 *
 * \note the frequency of the digital clock must be 32KHz or 32.768KHz and be always running.
 */
#ifndef dg_configEXT_LP_IS_DIGITAL
 #define dg_configEXT_LP_IS_DIGITAL    (0)
#endif

/**
 * \brief Minimum sleep time
 *
 *  No power savings if we enter sleep when the sleep time is less than N LP cycles.
 *
 *  \note It should be ~3msec but this may vary.
 */
#ifndef dg_configMIN_SLEEP_TIME
 #if (DEVICE_FAMILY == DA1640X)

  #ifndef BSP_DEVICE_REVISION
   #error "BSP_DEVICE_REVISION is not defined"
  #endif
  #ifndef DEVICE_REV_A
   #error "DEVICE_REV_A is not defined"
  #endif
  #ifndef DEVICE_REV_B
   #error "DEVICE_REV_B is not defined"
  #endif

  #if BSP_DEVICE_REVISION == DEVICE_REV_B
   #if (dg_configCODE_LOCATION == NON_VOLATILE_IS_FLASH)
    #define    MIN_SCALE_MS           (6) /* BA min 6 msec */
   #else
    #define    MIN_SCALE_MS           (4) /* BA min 4 msec */
   #endif
  #else // BSP_DEVICE_REVISION == DEVICE_REV_B
   #if (dg_configCODE_LOCATION == NON_VOLATILE_IS_FLASH)
    #define    MIN_SCALE_MS           (7) /* AA min 7 msec */
   #else
    #define    MIN_SCALE_MS           (6) /* AA min 6 msec */
   #endif
  #endif // (DEVICE_VERSION == DEVICE_VER_B)

  #if ((BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_LP_CLK_RCX) || \
    (BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_LP_CLK_XTAL32K))
   #define dg_configMIN_SLEEP_TIME    (33 * MIN_SCALE_MS)
  #elif (BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_LP_CLK_RCX)
   #define dg_configMIN_SLEEP_TIME    cm_rcx_us_2_lpcycles_low_acc((1000 * MIN_SCALE_MS))
  #else                                                                  /* LP_CLK_ANY */
/* Must be defined in the custom_config_<>.h file. It should be ~3msec but this may vary. */
  #endif
 #else                                                                   // (DEVICE_FAMILY != DA1640X)
  #if ((BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_LP_CLK_RCX) || \
    (BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_LP_CLK_XTAL32K))
   #define dg_configMIN_SLEEP_TIME    (33 * 3)                           /* 3 msec */
  #elif (BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_LP_CLK_RCX)
   #define dg_configMIN_SLEEP_TIME    cm_rcx_us_2_lpcycles_low_acc(3000) /* 3 msec */
  #else /* LP_CLK_ANY */
/* Must be defined in the custom_config_<>.h file. It should be ~3msec but this may vary. */
  #endif
 #endif // (DEVICE_FAMILY == DA1640X)
#endif

/**
 * \}
 */

/* ----------------------------------- Image Configuration -------------------------------------- */

/**
 * \addtogroup IMAGE_CONFIGURATION_SETTINGS Image configuration settings
 *
 * \brief Image configuration settings
 *
 * \{
 */

/**
 * \brief The motherboard revision we compile for.
 */
#ifndef dg_configBLACK_ORCA_MB_REV
 #define dg_configBLACK_ORCA_MB_REV            BLACK_ORCA_MB_REV_D
#endif

/**
 * \brief Controls how the image is built.
 *
 *  - DEVELOPMENT_MODE: various debugging options are included.
 *  - PRODUCTION_MODE: all code used for debugging is removed.
 */
#ifndef dg_configIMAGE_SETUP
 #define dg_configIMAGE_SETUP                  DEVELOPMENT_MODE
#endif

/**
 * \brief When set to 1, the delay at the start of execution of the Reset_Handler is skipped.
 *
 * \details This delay is added in order to facilitate proper programming of the Flash or QSPI\n
 *        launcher invocation. Without it, there is no guarantee that the execution of the image\n
 *        will not proceed, altering the default configuration of the system from the one that the\n
 *        bootloader leaves it.
 */
#ifndef dg_configSKIP_MAGIC_CHECK_AT_START
 #define dg_configSKIP_MAGIC_CHECK_AT_START    (0)
#endif

/**
 * \brief When set to 1, the QSPI copy will be emulated when in DEVELOPMENT_MODE (Not Applicable!).
 */
#ifndef dg_configEMULATE_QSPI_COPY
 #define dg_configEMULATE_QSPI_COPY            (0)
#endif

/**
 * \}
 */

/* ----------------------------------- System Configuration ------------------------------------- */

/**
 * \addtogroup SYSTEM_CONFIGURATION_SETTINGS System configuration settings
 *
 * \brief Generic System Configuration Settings
 *
 * \{
 */

/**
 * \brief Image copy time
 *
 * The number of LP cycles needed for the application's image data to be copied from the OTP
 * (or QSPI) to the RAM in mirrored mode.
 *
 * \warning MUST BE SMALLER THAN dg_configMIN_SLEEP_TIME !!!
 */
#if (dg_configEXEC_MODE != MODE_IS_MIRRORED)
 #undef dg_configIMAGE_COPY_TIME
 #define dg_configIMAGE_COPY_TIME     (0)
#elif !defined(dg_configIMAGE_COPY_TIME)
 #if ((BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_LP_CLK_RCX) || \
    (BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_LP_CLK_XTAL32K))
  #define dg_configIMAGE_COPY_TIME    (64)
 #elif (BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_LP_CLK_RCX)
  #define dg_configIMAGE_COPY_TIME    cm_rcx_us_2_lpcycles(1950)
 #endif
#endif

/**
 * \brief Brown-out Detection
 *
 * - 1: used
 * - 0: not used
 */
#ifndef dg_configUSE_BOD
 #define dg_configUSE_BOD                     (0)
#endif

/**
 * \brief Reset value for Watchdog.
 *
 * See WATCHDOG_REG:WDOG_VAL field.
 */
#ifndef dg_configWDOG_RESET_VALUE
 #define dg_configWDOG_RESET_VALUE            (0xFF)
#endif

/**
 * \brief Watchdog notify interval
 *
 * Interval (in milliseconds) for common timer which can be used to trigger tasks in order to notify
 * watchdog. Can be set to 0 in order to disable timer code entirely.
 */
#ifndef dg_configWDOG_NOTIFY_TRIGGER_TMO
 #define dg_configWDOG_NOTIFY_TRIGGER_TMO     (0)
#endif

/**
 * \brief Abort a clock modification if it will cause an error to the SysTick counter
 *
 * - 1: on
 * - 0: off
 */
#ifndef dg_configABORT_IF_SYSTICK_CLK_ERR
 #define dg_configABORT_IF_SYSTICK_CLK_ERR    (0)
#endif

/**
 * \brief Maximum adapters count
 *
 * Should be equal to the number of Adapters used by the Application. It can be larger (up to 254)
 * than needed, at the expense of increased Retention Memory requirements. It cannot be 0.
 */
#ifndef dg_configPM_MAX_ADAPTERS_CNT
 #define dg_configPM_MAX_ADAPTERS_CNT         (16)
#endif

/**
 * \brief Maximum sleep defer time
 *
 * The maximum time sleep can be deferred via a call to pm_defer_sleep_for(). It is in clock cycles
 * in the case of the XTAL32K and in usec in the case of RCX.
 * \note  It should be > 3.5msec.
 */
#ifndef dg_configPM_MAX_ADAPTER_DEFER_TIME
 #if ((BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_LP_CLK_RCX) || \
    (BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_LP_CLK_XTAL32K))
  #define dg_configPM_MAX_ADAPTER_DEFER_TIME    (128)
 #elif (BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_LP_CLK_RCX)
  #define dg_configPM_MAX_ADAPTER_DEFER_TIME    cm_rcx_us_2_lpcycles(4000)
 #else                                 /* LP_CLK_ANY */
/* Must be defined in the custom_config_<>.h file. It should be > 3.5msec. */
 #endif
#endif

/**
 * \brief Apply ADC Gain Error correction.
 *
 * - 1: used
 * - 0: not used
 *
 * The default setting is: 1.
 */
#ifndef dg_configUSE_ADC_GAIN_ERROR_CORRECTION
 #define dg_configUSE_ADC_GAIN_ERROR_CORRECTION    (1)
#endif

/**
 * \brief Image copy time
 *
 * The number of LP cycles needed for the application's image data to be copied from the OTP
 * (or QSPI) to the RAM in mirrored mode.
 *
 * \warning MUST BE SMALLER THAN dg_configMIN_SLEEP_TIME !!!
 */
#if (dg_configEXEC_MODE != MODE_IS_MIRRORED)
 #undef dg_configIMAGE_COPY_TIME
 #define dg_configIMAGE_COPY_TIME     (0)
#elif !defined(dg_configIMAGE_COPY_TIME)
 #if ((BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_LP_CLK_RCX) || \
    (BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_LP_CLK_XTAL32K))
  #define dg_configIMAGE_COPY_TIME    (64)
 #elif (BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_LP_CLK_RCX)
  #define dg_configIMAGE_COPY_TIME    cm_rcx_us_2_lpcycles(1950)
 #else                                 /* LP_CLK_ANY */
/* Must be defined in the custom_config_<>.h file. */
 #endif
#endif

/**
 * \brief When set to 1, the system will go to sleep and never exit allowing for the sleep current to be
 *        measured.
 */
#ifndef dg_configTESTMODE_MEASURE_SLEEP_CURRENT
 #define dg_configTESTMODE_MEASURE_SLEEP_CURRENT    (0)
#endif

/**
 * \}
 */

/* ----------------------------------- USB Configuration ---------------------------------------- */

/**
 * \addtogroup USB_SETTINGS USB configuration settings
 *
 * \brief USB configuration settings
 *
 * \{
 */

/**
 * \brief Controls how the system will behave when the USB i/f is suspended.
 *
 * \details When the USB Node is suspended by the USB Host, the application may have to act in
 *          order to comply with the USB specification (consume less than 2.5mA). The available
 *          options are:
 *          0: do nothing
 *          1: pause system clock => the LP clock is stopped and only VBUS and USB irqs are handled
 *          2: pause application => The system is not paused but the application must stop all
 *             timers and make sure all tasks are blocked.
 *
 *          Both in modes 1 and 2, the application must make sure that all external peripherals are
 *          either powered off or placed in the lowest power consumption mode.
 */
#ifndef dg_configUSB_SUSPEND_MODE
 #define dg_configUSB_SUSPEND_MODE    USB_SUSPEND_MODE_NONE
#endif

/**
 * \brief Enable the DMA for reading/writing data to USB EP.\n
 * By default the USB DMA is not enabled.\n
 * To enable the DMA for the USB, set this the macro to value (1) in the custom_config_xxx.h file.\n
 * When the USB DMA is enabled, the default end points with DMA are EP1 and EP2. \n
 * It is possible only one TX and one RX end point to use DMA.\n
 * User can choose a different pair of end points to use the DMA as needed according to app requirements.\n
 * To change the end points using DMA, set in the the custom_config_xxx.h file the desired values for the macros:
 * \par \c dg_configUSB_TX_DMA_EP
 * valid values: 1,3,5\n
 * default value: 1
 * \par \c dg_configUSB_RX_DMA_EP
 * valid values: 2,4,6\n
 * default value: 2
 */
#ifndef dg_configUSB_DMA_SUPPORT
 #define dg_configUSB_DMA_SUPPORT     (0)
#endif

/**
 * \brief The USB TX end point (D-->H) to enable the DMA.\n
 * User can choose a different pair of end points to use the DMA as needed according to app requirements.\n
 * To change the TX end point using DMA, set in the the custom_config_xxx.h file the desired value for this macros.
 * \par \c dg_configUSB_TX_DMA_EP
 * valid values: 1,3,5\n
 * default value: 1
 */
#ifndef dg_configUSB_TX_DMA_EP
 #define dg_configUSB_TX_DMA_EP       (1)
#endif

/**
 * \brief The USB RX end point (D-->H) to enable the DMA.\n
 * User can choose a different pair of end points to use the DMA as needed according to app requirements.\n
 * To change the RX end point using DMA, set in the the custom_config_xxx.h file the desired value for this macros.
 * \par \c dg_configUSB_RX_DMA_EP
 * valid values: 2,4,6\n
 * default value: 2
 */
#ifndef dg_configUSB_RX_DMA_EP
 #define dg_configUSB_RX_DMA_EP       (2)
#endif

/**
 * \}
 */

/* ----------------------------------- Flash Configuration -------------------------------------- */

/**
 * \addtogroup FLASH_SETTINGS Flash configuration settings
 *
 * \brief Flash configuration settings
 *
 * \{
 */

/* Backward compatibility check */

#if defined(dg_configPOWER_FLASH) || defined(dg_configFLASH_POWER_OFF)
 #define PRINT_POWER_RAIL_SETUP
#endif

/**
 * \brief Enable the Flash Auto-detection mode for QSPIC
 *
 * \warning THIS WILL GREATLY INCREASE THE CODE SIZE AND RETRAM USAGE!!! MAKE SURE YOUR PROJECT
 *          CAN SUPPORT THIS.
 */
#ifndef dg_configFLASH_AUTODETECT
 #define dg_configFLASH_AUTODETECT                (0)
#endif

/**
 * \brief Offset of the image if not placed at the beginning of QSPI Flash.
 */
#ifndef dg_configIMAGE_FLASH_OFFSET
 #define dg_configIMAGE_FLASH_OFFSET              (0)
#endif

/**
 * \brief Set the flash page size.
 */
#ifndef dg_configFLASH_MAX_WRITE_SIZE
 #define dg_configFLASH_MAX_WRITE_SIZE            (128)
#endif

/**
 * \brief Disable background operations.
 *
 * When enabled, outstanding QSPI operations will take place during sleep time
 * increasing the efficiency.
 *
 * - 1 : Disabled
 * - 0 : Enabled
 */
#ifndef dg_configDISABLE_BACKGROUND_FLASH_OPS
 #define dg_configDISABLE_BACKGROUND_FLASH_OPS    (1)
#endif

/**
 * \}
 */

/* ----------------------------------- Cache Configuration -------------------------------------- */

/**
 * \addtogroup CACHE_SETTINGS Cache configuration settings
 *
 * \brief Cache configuration settings
 *
 * \{
 */

/**
 * \brief Set the size (in bytes) of the QSPI flash cacheable area.
 *
 * All reads from offset 0 up to (not including) offset dg_configCACHEABLE_QSPI_AREA_LEN
 * will be cached. In addition, any writes to this area will trigger cache flushing, to
 * avoid any cache incoherence.
 *
 * The size must be 64KB-aligned, due to the granularity of CACHE_CTRL2_REG[CACHE_LEN].
 *
 * Special values:
 *  *  0 : Turn off cache.
 *  * -1 : Don't configure cacheable area size (i.e. leave as set by booter).
 */
#ifndef dg_configCACHEABLE_QSPI_AREA_LEN
 #define dg_configCACHEABLE_QSPI_AREA_LEN    (-1)
#endif

/**
 * \brief Set the associativity of the cache.
 *
 * Available values:
 *  0   /// direct-mapped
 *  1   /// 2-way set associative
 *  2   /// 4-way set associative
 *  3   /// leave as set by the ROM booter
 */
#ifndef dg_configCACHE_ASSOCIATIVITY
 #define dg_configCACHE_ASSOCIATIVITY        (2)
#endif

/**
 * \brief Set the line size of the cache.
 *
 * Available values:
 *  0   /// 8 bytes
 *  1   /// 16 bytes
 *  2   /// 32 byte
 *  3   /// leave as set by the ROM booter
 */
#ifndef dg_configCACHE_LINESZ
 #define dg_configCACHE_LINESZ               (0)
#endif

/**
 * \}
 */

/* ----------------------------------- UART settings -------------------------------------------- */

/**
 * \addtogroup UART_SETTINGS UART configuration settings
 *
 * \brief UART configuration settings
 *
 * \{
 */

/**
 * \brief Circular DMA support for RX
 */
#ifndef dg_configUART_RX_CIRCULAR_DMA
 #define dg_configUART_RX_CIRCULAR_DMA              (0)
#endif

/**
 * \brief UART1's Circular DMA buffer size for RX
 */
#ifndef dg_configUART1_RX_CIRCULAR_DMA_BUF_SIZE
 #define dg_configUART1_RX_CIRCULAR_DMA_BUF_SIZE    (0)
#endif

/**
 * \brief UART2's Circular DMA buffer size for RX
 */
#ifndef dg_configUART2_RX_CIRCULAR_DMA_BUF_SIZE
 #define dg_configUART2_RX_CIRCULAR_DMA_BUF_SIZE    (0)
#endif

/**
 * \}
 */

/* ----------------------------------- RF Configuration ----------------------------------------- */

/**
 * \addtogroup RF_DRIVER_SETTINGS Radio Driver Settings
 *
 * \brief Doxygen documentation is not yet available for this module.
 *        Please check the source code file(s)
 * \{
 */

/**
 * \brief Set to 1 to enable the recalibration procedure.
 */
#if defined(CONFIG_USE_BLE)
 #ifndef dg_configRF_ENABLE_RECALIBRATION
  #define dg_configRF_ENABLE_RECALIBRATION    (1)
 #endif
#endif

/**
 * \}
 */

/* ----------------------------------- DEVICE-SPECIFIC CONFIGURATION ---------------------------- */

#if (DEVICE_FAMILY == DA1640X)

 #include "bsp_defaults_ra6w1.h"

#endif

/* ----------------------------------- DEBUG CONFIGURATION ------------------ ------------------- */

#include "bsp_debug.h"

/* ----------------------------------- MEMORY LAYOUT CONFIGURATION ------------------------------ */

#include "bsp_memory_defaults.h"

/* XXX ------------------------------- UNDISCLOSED DEFINITIONS ---------------------------------- */

#include "bsp_undisclosed_defs.h"

#endif                                 /* BSP_DEFAULTS_H_ */

/**
 \}
 \}
 */
