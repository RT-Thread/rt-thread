/**
 * \{
 * \addtogroup MIDDLEWARE_CONFIG_DEFAULTS
 *
 * \brief Middleware default configuration values
 *
 * The following tags are used to describe the type of each configuration option.
 * \{
 */

/**
 ****************************************************************************************
 *
 * @file middleware_defaults.h
 *
 * @brief Middleware. System Configuration file default values.
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

#ifndef MIDDLEWARE_DEFAULTS_H_
#define MIDDLEWARE_DEFAULTS_H_

/**
 * \addtogroup ADAPTER_SELECTION Adapters enabled by default
 *
 * \brief Adapter selection
 *
 * When enabled the specific adapter is included in the compilation of the SDK.
 * - 0 : Disabled
 * - 1 : Enabled
 *
 * The default option can be overridden in the application configuration file.
 *
 * \{
 * Adapter                        | Setting                                | Default option
 * ------------------------------ | -------------------------------------- | :------------------:
 * Table not yet fixed | dg_configXXXXX_ADAPTER                   | 1
 *
 */

/* -------------------------------- Adapters (ad_*) selection -------------------------------- */

#ifndef dg_configFLASH_ADAPTER
 #define dg_configFLASH_ADAPTER       (0)
#endif

#ifndef dg_configI2C_ADAPTER
 #define dg_configI2C_ADAPTER         (0)
#endif

#ifndef dg_configNVMS_ADAPTER
 #define dg_configNVMS_ADAPTER        (0)
#endif

#ifndef dg_configNVMS_FLASH_CACHE
 #define dg_configNVMS_FLASH_CACHE    (0)
#endif

#ifndef dg_configNVMS_VES
 #define dg_configNVMS_VES            (0)
#endif

#ifndef dg_configSPI_ADAPTER
 #define dg_configSPI_ADAPTER         (0)
#endif

#ifndef dg_configUART_ADAPTER
 #define dg_configUART_ADAPTER        (0)
#endif

#ifndef dg_configGPADC_ADAPTER
 #define dg_configGPADC_ADAPTER       (0)
#endif

#ifndef dg_configSDADC_ADAPTER
 #define dg_configSDADC_ADAPTER       (0)
#endif

#ifdef dg_configTEMPSENS_ADAPTER
 #error "Configuration option dg_configTEMPSENS_ADAPTER  is no longer supported"
#endif

#ifdef dg_configBATTERY_ADAPTER
 #error "Configuration option dg_configBATTERY_ADAPTER  is no longer supported"
#endif

#ifndef dg_configNVPARAM_ADAPTER
 #define dg_configNVPARAM_ADAPTER             (0)
#endif

#ifndef dg_configNVPARAM_APP_AREA
 #define dg_configNVPARAM_APP_AREA            (0)
#endif

#ifndef dg_configCRYPTO_ADAPTER
 #define dg_configCRYPTO_ADAPTER              (0)
#endif

#ifndef dg_configKEYBOARD_SCANNER_ADAPTER
 #define dg_configKEYBOARD_SCANNER_ADAPTER    (0)
#endif

#if ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))
 #ifndef dg_configSYS_AUDIO_MGR
  #define dg_configSYS_AUDIO_MGR              (0)
 #endif
#endif                                 /* DEVICE_FAMILY */

#if (DEVICE_FAMILY == DA1468X)

 #ifndef dg_configRF_ADAPTER
  #define dg_configRF_ADAPTER    (0)
 #endif

 #if (dg_configSNC_ADAPTER == 1)
  #error "dg_configSNC_ADAPTER is not supported in DA14680 devices"
 #else
  #undef dg_configSNC_ADAPTER
  #define dg_configSNC_ADAPTER    (0)
 #endif

 #if (dg_configISO7816_ADAPTER == 1)
  #error "dg_configISO7816_ADAPTER is not supported in DA14680 devices"
 #else
  #undef dg_configISO7816_ADAPTER
  #define dg_configISO7816_ADAPTER    (0)
 #endif

 #if (dg_configLCDC_ADAPTER == 1)
  #error "dg_configLCDC_ADAPTER is not supported in DA14680 devices"
 #else
  #undef dg_configLCDC_ADAPTER
  #define dg_configLCDC_ADAPTER    (0)
 #endif

 #if (dg_configPMU_ADAPTER == 1)
  #error "dg_configPMU_ADAPTER is not supported in DA14680 devices"
 #else
  #undef dg_configPMU_ADAPTER
  #define dg_configPMU_ADAPTER    (0)
 #endif

 #if (dg_configHAPTIC_ADAPTER == 1)
  #error "dg_configHAPTIC_ADAPTER is not supported in DA14680 devices"
 #else
  #undef dg_configHAPTIC_ADAPTER
  #define dg_configHAPTIC_ADAPTER    (0)
 #endif

#elif ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))

 #ifndef dg_configSNC_ADAPTER
  #define dg_configSNC_ADAPTER        (0)
 #endif

 #ifndef dg_configISO7816_ADAPTER
  #define dg_configISO7816_ADAPTER    (0)
 #endif

 #ifndef dg_configLCDC_ADAPTER
  #define dg_configLCDC_ADAPTER       (0)
 #endif

 #ifndef dg_configPMU_ADAPTER
  #define dg_configPMU_ADAPTER        (0)
 #endif

 #ifndef dg_configHAPTIC_ADAPTER
  #define dg_configHAPTIC_ADAPTER     (0)
 #elif dg_configHAPTIC_ADAPTER
  #if (!(dg_configUSE_HW_ERM || dg_configUSE_HW_LRA))
   #error \
    "Configuration option dg_configHAPTIC_ADAPTER also requires either the dg_configUSE_HW_LRA or the dg_configUSE_HW_ERM configuration options to be set."
  #endif
 #endif

 #ifdef dg_configRF_ADAPTER
  #error "dg_configRF_ADAPTER is not supported in DA14690 devices"
 #endif

#endif                                 /* DEVICE_FAMILY */

/* ---------------------------------------------------------------------------------------------- */

/**
 * \}
 */

/**
 * \addtogroup CONSOLE_IO_SETTINGS Console I/O Settings
 *
 * \brief Console IO configuration settings
 *
 * \{
 * Description                               | Setting                    | Default option
 * ----------------------------------------- | -------------------------- | :---------------:
 * Enable serial console module              | dg_configUSE_CONSOLE       | 0
 * Enable serial console stubbed API         | dg_configUSE_CONSOLE_STUBS | 0
 * Enable Command Line Interface module      | dg_configUSE_CLI           | 0
 * Enable Command Line Interface stubbed API | dg_configUSE_CLI_STUBS     | 0
 *
 * \see console.h cli.h
 *
 * \note CLI module requires dg_configUSE_CONSOLE to be enabled.
 */

/* -------------------------------------- Console IO configuration settings --------------------- */

#ifndef dg_configUSE_CONSOLE
 #define dg_configUSE_CONSOLE          (0)
#endif

#ifndef dg_configUSE_CONSOLE_STUBS
 #define dg_configUSE_CONSOLE_STUBS    (0)
#endif

#ifndef dg_configUSE_CLI
 #define dg_configUSE_CLI              (0)
#endif

#ifndef dg_configUSE_CLI_STUBS
 #define dg_configUSE_CLI_STUBS        (0)
#endif

/* ---------------------------------------------------------------------------------------------- */

/**
 * \}
 */

/**
 * \addtogroup MIDDLEWARE_DEBUG_SETTINGS Debug Settings
 *
 * \{
 */

/* -------------------------------------- Debug settings ---------------------------------------- */

/**
 * \brief Enable task monitoring.
 *
 * \note Task monitoring can only be enabled if RTT or RETARGET is enabled
 */
#ifndef dg_configENABLE_TASK_MONITORING
 #define dg_configENABLE_TASK_MONITORING    (0)
#endif

#if ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))

/**
 * \brief Enable Micro Trace Buffer
 *
 * \note MTB is available only on Cortex-M33.
 *
 */
 #ifndef dg_configENABLE_MTB
  #define dg_configENABLE_MTB    (0)
 #endif
#endif                                 /* DEVICE_FAMILY */

/* ---------------------------------------------------------------------------------------------- */

/* ---------------------------------- OS related configuration ---------------------------------- */

/**
 * \brief Monitor OS heap allocations
 */
#ifndef dg_configTRACK_OS_HEAP
 #define dg_configTRACK_OS_HEAP    (0)
#endif

/* ---------------------------------------------------------------------------------------------- */

/**
 * \}
 */

/* ---------------------------------- SYSTEM CONFIGURATION ------------------------------------ */

/**
 * \brief Enable gpadc monitoring.
 *
 * \note The application must not explicitly set dg_configUSE_SYS_ADC to 1.\n
 *       Use instead dg_configRF_ENABLE_RECALIBRATION\n
 */

#ifndef dg_configUSE_SYS_ADC
 #define dg_configUSE_SYS_ADC        (0)
#endif

/**
 * \brief When set to 1, the sys charger service is used to charge the battery.
 */
#ifndef dg_configUSE_SYS_CHARGER
 #define dg_configUSE_SYS_CHARGER    (0)
#endif

/**
 * \brief When set to 1, the sys usb service is used to manage:
 *        - VBUS attach / detach and  USB suspend / resume operations.
 *        - Notifications towards SDK and applications.
 *        - Suspend / resume sleep.
 *        - Suspend / resume DC/DC if in use.
 *
 * \note The service is automatically enabled when charging or USB enumeration
 *       are involved (see dg_configUSE_SYS_CHARGER , dg_configUSE_USB_ENUMERATION).
 *       It's recommended to be enabled when:
 *       - The power supply is a non rechargeable battery and the application is not
 *         interested in USB enumeration.
 *       - The only source of power supply is VBUS e.g a USB dongle.
 */
#ifndef dg_configUSE_SYS_USB
 #define dg_configUSE_SYS_USB        (0)
#endif

/* ---------------------------------------------------------------------------------------------- */

/* ----------------------------------- Driver dependencies -------------------------------------- */

/* If USB charger is enebled, we need to enable GPADC and Battery adapters as well */
#if (dg_configUSE_USB_CHARGER == 1)
 #undef dg_configGPADC_ADAPTER
 #define dg_configGPADC_ADAPTER    (1)
#endif

/*
 * SYS_CHARGER will else enable SYS_USB which implements the USB and VBUS interrupt handlers
 */
#if (dg_configUSE_SYS_CHARGER == 1)
 #undef dg_configUSE_HW_USB_CHARGER
 #define dg_configUSE_HW_USB_CHARGER    (1)
 #undef dg_configUSE_HW_CHARGER
 #define dg_configUSE_HW_CHARGER        (1)
 #undef dg_configUSE_HW_USB
 #define dg_configUSE_HW_USB            (1)
 #undef dg_configUSE_SYS_USB
 #define dg_configUSE_SYS_USB           (1)
#endif

/*
 * For USB_ENUMERATION to work, SYS_USB is also enabled, and library usb_lib needs to be linked
 * with the active project
 */
#if (dg_configUSE_USB_ENUMERATION == 1)
 #undef dg_configUSE_SYS_USB
 #define dg_configUSE_SYS_USB          (1)
 #ifndef dg_configUSB_SUSPEND_MODE
  #define dg_configUSB_SUSPEND_MODE    USB_SUSPEND_MODE_NONE
 #elif (dg_configUSB_SUSPEND_MODE == USB_SUSPEND_MODE_PAUSE)
  #if ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))
   #error "USB_SUSPEND_MODE_PAUSE is currently not supported"
  #endif
 #endif
#endif

/*
 * SYS_USB can be explicitly enabled, even if dg_configUSE_SYS_CHARGER and dg_configUSE_USB_ENUMERATION
 * are not used. This will enable the VBUS and USB interrupt handlers, but no functionality will be
 * attached to them
 */
#if (dg_configUSE_SYS_USB == 1)
 #undef dg_configUSE_HW_USB
 #define dg_configUSE_HW_USB             (1)
 #if (DEVICE_FAMILY == DA1468X)
  #undef dg_configUSE_HW_USB_CHARGER
  #define dg_configUSE_HW_USB_CHARGER    (1)
 #endif
#endif

/* If RF recalibration is enabled or RCX is used as low power clock, we need to enable SNC and GPADC as well */
#if (dg_configRF_ENABLE_RECALIBRATION || (BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_RCX && \
                                          defined(OS_FREERTOS)))
 #undef dg_configUSE_HW_GPADC
 #define dg_configUSE_HW_GPADC             (1)
 #undef dg_configGPADC_ADAPTER
 #define dg_configGPADC_ADAPTER            (1)
 #if ((DEVICE_FAMILY == DA1469X) || (DEVICE_FAMILY == DA1487X))
  #if (dg_configRF_ENABLE_RECALIBRATION)
   #undef dg_configUSE_SYS_ADC
   #define dg_configUSE_SYS_ADC            (1)
  #endif
  #undef dg_configUSE_SNC_HW_GPADC
  #define dg_configUSE_SNC_HW_GPADC        (1)
  #undef dg_configUSE_HW_SENSOR_NODE
  #define dg_configUSE_HW_SENSOR_NODE      (1)
  #undef dg_configSNC_ADAPTER
  #define dg_configSNC_ADAPTER             (1)
  #undef dg_configUSE_STATIC_IO_CONFIG
  #define dg_configUSE_STATIC_IO_CONFIG    (1)
 #endif
#endif

/**
 *
 * \brief RTC-to-PDC event period, in 10ms
 *
 * When RCX is set as the low power clock or RF calibration is enabled and Real Time Clock is used
 * dg_configRTC_PDC_EVENT_PERIOD defines the RTC-to-PDC event period that will be used for RTC event controller
 * configuration.
 *
 */
#if (dg_configRF_ENABLE_RECALIBRATION || (BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_RCX && \
                                          defined(OS_FREERTOS)))
 #ifndef dg_configRTC_PDC_EVENT_PERIOD
  #define dg_configRTC_PDC_EVENT_PERIOD    (100) // in 10ms
 #endif
#else
 #ifdef dg_configRTC_PDC_EVENT_PERIOD
  #undef dg_configRTC_PDC_EVENT_PERIOD
 #endif
#endif

/**
 *
 * \brief RCX calibration polling interval counter
 *
 * dg_configRCX_CAL_POLL_INT defines the number of RTC-to-PDC events that SYS_RCX ucode should wait before executing its code.
 *
 */
#if (BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_RCX && defined(OS_FREERTOS))
 #ifndef dg_configRCX_CAL_POLL_INT
  #define dg_configRCX_CAL_POLL_INT    (1) // in dg_configRTC_PDC_EVENT_PERIOD * 10ms - calibration interval = 1sec
 #endif
#endif

/**
 *
 * \brief RF calibration polling interval counter
 *
 * dg_configRF_CAL_POLL_INT defines the number of RTC-to-PDC events that SYS_ADC ucode should wait before executing its code
 * when RF calibration is enabled.
 *
 */
#if (dg_configRF_ENABLE_RECALIBRATION)
 #ifndef dg_configRF_CAL_POLL_INT
  #define dg_configRF_CAL_POLL_INT    (1) // in dg_configRTC_PDC_EVENT_PERIOD * 10ms - calibration interval = 1sec
 #endif
#endif

/* If RF is enabled, we need to enable GPADC adapter as well */
#if  dg_configRF_ADAPTER
 #undef dg_configGPADC_ADAPTER
 #define dg_configGPADC_ADAPTER    (1)
#endif

/*
 * \brief Enable the RTC correction mechanism
 *
 * When RCX is set as the low power clock and Real Time Clock is used (i.e. dg_configUSE_HW_RTC is defined),
 * setting this macro to 1 enables the RTC correction mechanism.
 */
#if (BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_RCX && defined(OS_FREERTOS) && dg_configUSE_HW_RTC)
 #ifndef dg_configRTC_CORRECTION
  #define dg_configRTC_CORRECTION    (1)
 #endif
#else
 #if dg_configRTC_CORRECTION
  #pragma \
    message "dg_configRTC_CORRECTION is only used in RTOS based projects when RCX is set as low power clock. Forcing to 0."
  #undef dg_configRTC_CORRECTION
  #define dg_configRTC_CORRECTION    (0)
 #endif
#endif

/* ---------------------------------------------------------------------------------------------- */

#endif                                 /* MIDDLEWARE_DEFAULTS_H_ */

/**
 \}
 \}
 */
