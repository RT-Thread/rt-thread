/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FSL_POWER_MANAGER_H__
#define __FSL_POWER_MANAGER_H__

#include <stdint.h>
#include <stdbool.h>

#include "fsl_smc_hal.h"

/*!
 * @addtogroup power_manager
 * @{
 */


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Power modes enumeration.
 *
 * Defines power mode. Used in the power mode configuration structure
 * (power_manager_user_config_t). From ARM core perspective, power modes
 * can be generally divided to run modes (high-speed run, run, and
 * very low power run), sleep (wait and very low power wait), and deep sleep modes
 * (all stop modes).
 * List of power modes supported by a specific chip along with requirements for entering
 * and exiting of these modes can be found in the chip documentation.
 * List of all supported power modes:\n
 *  \li kPowerManagerHsrun - High speed run mode. Chip-specific.
 *  \li kPowerManagerRun - Run mode. All Kinetis chips.
 *  \li kPowerManagerVlpr - Very low power run mode. All Kinetis chips.
 *  \li kPowerManagerWait - Wait mode. All Kinetis chips.
 *  \li kPowerManagerVlpw - Very low power wait mode. All Kinetis chips.
 *  \li kPowerManagerStop - Stop mode. All Kinetis chips.
 *  \li kPowerManagerVlps - Very low power stop mode. All Kinetis chips.
 *  \li kPowerManagerPstop1 - Partial stop 1 mode. Chip-specific.
 *  \li kPowerManagerPstop2 - Partial stop 2 mode. Chip-specific.
 *  \li kPowerManagerLls - Low leakage stop mode. All Kinetis chips.
 *  \li kPowerManagerLls2 - Low leakage stop 2 mode. Chip-specific.
 *  \li kPowerManagerLls3 - Low leakage stop 3 mode. Chip-specific.
 *  \li kPowerManagerVlls0 - Very low leakage stop 0 mode. Chip-specific.
 *  \li kPowerManagerVlls1 - Very low leakage stop 1 mode. All Kinetis chips.
 *  \li kPowerManagerVlls2 - Very low leakage stop 2 mode. All Kinetis chips.
 *  \li kPowerManagerVlls3 - Very low leakage stop 3 mode. All Kinetis chips.
 */
typedef enum _power_manager_modes {
#if FSL_FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE
    kPowerManagerHsrun,            /*!< High-speed run mode. All Kinetis chips. @internal gui name="High speed run mode" */
#endif
    kPowerManagerRun,              /*!< Run mode. All Kinetis chips. @internal gui name="Run mode" */
    kPowerManagerVlpr,             /*!< Very low power run mode. All Kinetis chips. @internal gui name="Very low power run mode" */
    kPowerManagerWait,             /*!< Wait mode. All Kinetis chips. @internal gui name="Wait mode" */
    kPowerManagerVlpw,             /*!< Very low power wait mode. All Kinetis chips. @internal gui name="Very low power wait mode" */
    kPowerManagerStop,             /*!< Stop mode. All Kinetis chips. @internal gui name="Stop mode" */
    kPowerManagerVlps,             /*!< Very low power stop mode. All Kinetis chips. @internal gui name="Very low power stop mode" */
#if FSL_FEATURE_SMC_HAS_PSTOPO
    kPowerManagerPstop1,           /*!< Partial stop 1 mode. Chip-specific. @internal gui name="Partial stop 1 mode" */
    kPowerManagerPstop2,           /*!< Partial stop 2 mode. Chip-specific. @internal gui name="Partial stop 2 mode" */
#endif
#if FSL_FEATURE_SMC_HAS_LOW_LEAKAGE_STOP_MODE    
    kPowerManagerLls,              /*!< Low leakage stop mode. All Kinetis chips. @internal gui name="Low leakage stop mode" */
#endif    
#if FSL_FEATURE_SMC_HAS_LLS_SUBMODE
    kPowerManagerLls2,             /*!< Low leakage stop 2 mode. Chip-specific. @internal gui name="Low leakage stop 2 mode" */
    kPowerManagerLls3,             /*!< Low leakage stop 3 mode. Chip-specific. @internal gui name="Low leakage stop 3 mode" */
#endif
#if FSL_FEATURE_SMC_HAS_STOP_SUBMODE0
    kPowerManagerVlls0,            /*!< Very low leakage stop 0 mode. All Kinetis chips. @internal gui name="Very low leakage stop 0 mode" */
#endif    
    kPowerManagerVlls1,            /*!< Very low leakage stop 1 mode. All Kinetis chips. @internal gui name="Very low leakage stop 1 mode" */
#if FSL_FEATURE_SMC_HAS_STOP_SUBMODE2
    kPowerManagerVlls2,            /*!< Very low leakage stop 2 mode. All Kinetis chips. @internal gui name="Very low leakage stop 2 mode" */
#endif
    kPowerManagerVlls3,            /*!< Very low leakage stop 3 mode. All Kinetis chips. @internal gui name="Very low leakage stop 3 mode" */
    kPowerManagerMax
} power_manager_modes_t;

/*!
 * @brief Power Manager success code and error codes.
 *
 * Used as return value of Power Manager functions.
 */
typedef enum _power_manager_error_code {
    kPowerManagerSuccess,                  /*!< Success */
    kPowerManagerError,                    /*!< Some error occurs. */
    kPowerManagerErrorOutOfRange,          /*!< Configuration index out of range. */
    kPowerManagerErrorSwitch,              /*!< Error occurs during mode switch. */
    kPowerManagerErrorNotificationBefore,  /*!< Error occurs during send "BEFORE" notification. */
    kPowerManagerErrorNotificationAfter,   /*!< Error occurs during send "AFTER" notification.  */
    kPowerManagerErrorClock                /*!< Error occurs due to wrong clock setup for power modes */
} power_manager_error_code_t;

/*!
 * @brief Power Manager policies.
 *
 * Defines whether the power mode change is forced or not. Used to specify whether
 * the mode switch initiated by the POWER_SYS_SetMode() depends on the callback
 * notification results. For kPowerManagerPolicyForcible, the power mode is changed
 * regardless of the results, while kPowerManagerPolicyAgreement policy is used
 * the POWER_SYS_SetMode() is exited when any of the callbacks returns error code.
 * See also POWER_SYS_SetMode() description.
 */
typedef enum _power_manager_policy {
    kPowerManagerPolicyAgreement,      /*!< POWER_SYS_SetMode() method is exited when any of the callbacks returns error code. @internal gui name="Agreement policy" */ 
    kPowerManagerPolicyForcible        /*!< Power mode is changed regardless of the results. @internal gui name="Forcible policy" */
} power_manager_policy_t;

/*! @brief The Power Manager notification type. Used to notify registered callbacks */
typedef enum _power_manager_notify
{
    kPowerManagerNotifyRecover = 0x00U,  /*!< Notify IP to recover to previous work state.      */
    kPowerManagerNotifyBefore  = 0x01U,  /*!< Notify IP that system  changes power setting.  */
    kPowerManagerNotifyAfter   = 0x02U,  /*!< Notify IP that have changed to new power setting. */
} power_manager_notify_t;

/*!
 * @brief The callback type, indicates what kinds of notification this callback handles.
 *
 * Used in the callback configuration structures (power_manager_callback_user_config_t) 
 * to specify when the registered callback is called during power mode change initiated by 
 * POWER_SYS_SetMode().
 * Callback can be invoked in following situations:
 *  - before the power mode change (Callback return value can affect POWER_SYS_SetMode()
 *    execution. Refer to the  POWER_SYS_SetMode() and power_manager_policy_t documentation).
 *  - after entering one of the run modes or after exiting from one of the (deep) sleep power
 *    modes back to the run mode.
 *  - after unsuccessful attempt to switch power mode
 */
typedef enum _power_manager_callback_type {
    kPowerManagerCallbackBefore      = 0x01U, /*!< Before callback. @internal gui name="Before" */
    kPowerManagerCallbackAfter       = 0x02U, /*!< After callback. @internal gui name="After" */
    kPowerManagerCallbackBeforeAfter = 0x03U, /*!< Before-After callback. @internal gui name="Before-After" */
} power_manager_callback_type_t;

/*!
 * @brief Callback-specific data.
 *
 * Reference to data of this type is passed during callback registration. The reference is
 * part of the power_manager_callback_user_config_t structure and is passed to the callback during 
 * power mode change notifications.
 */
typedef void power_manager_callback_data_t;

/*!
 * @brief Power mode user configuration structure.
 *
 * This structure defines Kinetis power mode with additional power options and specifies
 * transition to and out of this mode. Application may define multiple power modes and
 * switch between them. List of defined power modes is passed to the Power Manager during
 * initialization as an array of references to structures of this type (see POWER_SYS_Init()).
 * Power modes can be switched by calling POWER_SYS_SetMode() which accepts index to the list
 * of power modes passed during manager initialization. Currently used power mode can be
 * retrieved by calling POWER_SYS_GetLastMode(), which returns index of the current power mode, or
 * by POWER_SYS_GetLastModeConfig(), which returns reference to the structure of current mode.
 * List of power mode configuration structure members depends on power options available
 * for specific chip. Complete list contains:
 *  mode - Kinetis power mode. List of available modes is chip-specific. See power_manager_modes_t
 *   list of modes. This item is common for all Kinetis chips.
 *  sleepOnExitOption - Controls whether the sleep-on-exit option value is used (when set to true)
 *   or ignored (when set to false). See sleepOnExitValue. This item is common for all Kinetis chips.
 *  sleepOnExitValue - When set to true, ARM core returns to sleep (Kinetis wait modes) or deep sleep
 *   state (Kinetis stop modes) after interrupt service finishes. When set to false, core stays
 *   woken-up. This item is common for all Kinetis chips.
 *  lowPowerWakeUpOnInterruptOption - Controls whether the wake-up-on-interrupt option value is used
 *   (when set to true) or ignored (when set to false). See lowPowerWakeUpOnInterruptValue. This
 *   item is chip-specific.
 *  lowPowerWakeUpOnInterruptValue - When set to true, system exits to Run mode when any interrupt occurs while in
 *   Very low power run, Very low power wait or Very low power stop mode. This item is chip-specific.
 *  powerOnResetDetectionOption - Controls whether the power on reset detection option value is used
 *   (when set to true) or ignored (when set to false). See powerOnResetDetectionValue. This item is
 *   chip-specific.
 *  powerOnResetDetectionValue - When set to true, power on reset detection circuit is enabled in
 *   Very low leakage stop 0 mode. When set to false, circuit is disabled. This item is chip-specific.
 *  RAM2PartitionOption - Controls whether the RAM2 partition power option value is used (when set to
 *   true) or ignored (when set to false). See RAM2PartitionValue. This item is chip-specific.
 *  RAM2PartitionValue - When set to true, RAM2 partition content is retained through Very low
 *   leakage stop 2 mode. When set to false, RAM2 partition power is disabled and memory content lost.
 *   This item is chip-specific.
 *  lowPowerOscillatorOption - Controls whether the Low power oscillator power option value is used
 *   (when set to true) or ignored (when set to false). See lowPowerOscillatorValue. This item is
 *   chip-specific.
 *  lowPowerOscillatorValue - When set to true, the 1 kHz Low power oscillator is enabled in any
 *   Low leakage or Very low leakage stop mode. When set to false, oscillator is disabled in these modes.
 *   This item is chip-specific.
 * @internal gui name="Power manager configuration" id="power_managerCfg"
 */
typedef struct _power_manager_mode_user_config {
    power_manager_modes_t mode;  /*!< Power mode. @internal gui name="Power mode" id="mode" */
    bool sleepOnExitValue;       /*!< true - Sleep or deep sleep after interrupt service finished, false - core stays woken-up. @internal gui name="Sleep on Exit" id="sleepOnExitValue" */
#if FSL_FEATURE_SMC_HAS_LPWUI
    smc_lpwui_option_t lowPowerWakeUpOnInterruptValue;  /*!< true - Wake-up on interrupt from Very low power run, Very low power wait or Very low power stop mode, false - Wake-up on interrupt disabled for these modes. @internal gui name="Low power Wake-Up on interrupt" id="lowPowerWakeUpOnInterruptValue" */
#endif
#if FSL_FEATURE_SMC_HAS_PORPO
    smc_por_option_t powerOnResetDetectionValue;  /*!< true - Power on reset detection circuit is enabled in Very low leakage stop 0 mode, false - Power on reset detection circuit is disabled. @internal gui name="Power on reset detection in VLLS0" id="powerOnResetDetectionValue" */
#endif
#if FSL_FEATURE_SMC_HAS_RAM2_POWER_OPTION
    smc_ram2_option_t RAM2PartitionValue;  /*!< true - RAM2 partition content is retained through Very low leakage stop 2 mode, false - RAM2 partition power is disabled and memory content lost. @internal gui name="RAM2 partition" id="RAM2PartitionValue" */
#endif
#if FSL_FEATURE_SMC_HAS_PSTOPO
    smc_pstop_option_t  partialStopOptionValue;  /*!< Defines Normal stop mode, or Partial Stop with both system and bus clocks disabled, or Partial Stop with system clock disabled and bus clock enabled. @internal gui name="Partial stop option" id="partialStopOptionValue" */
#endif
#if FSL_FEATURE_SMC_HAS_LPOPO
    smc_lpo_option_t lowPowerOscillatorValue;  /*!< true - The 1 kHz Low power oscillator is enabled in any Low leakage or Very low leakage stop mode - false, oscillator is disabled in these modes. @internal gui name="Low power oscillator" id="lowPowerOscillatorValue" */
#endif
} power_manager_user_config_t;

/*! @brief Power notification structure passed to the registered callback function. */
typedef struct _power_notify_struct
{
    uint8_t targetPowerConfigIndex;    /*!< Target power configuration index. */
    power_manager_user_config_t const *targetPowerConfigPtr; /*!< Pointer to target power configuration */
    power_manager_policy_t policy;     /*!< Clock transition policy.          */
    power_manager_notify_t notifyType; /*!< Clock notification type.          */
} power_manager_notify_struct_t;

/*!
 * @brief Callback prototype.
 *
 * Declaration of callback. It is common for registered callbacks.
 * Reference to function of this type is part of power_manager_callback_user_config_t callback 
 * configuration structure.
 * Depending on callback type, function of this prototype is called during the power mode change
 * (see POWER_SYS_SetMode()) before the mode change, after it or in both cases to notify about
 * the change progress (see power_manager_callback_type_t). When called, type of the notification
 * is passed as parameter along with reference to entered power mode configuration structure
 * (see power_manager_notify_struct_t) and any data passed during the callback registration (see
 * power_manager_callback_data_t).
 * When notified before the mode change, depending on the power mode change policy (see
 * power_manager_policy_t) the callback may deny the mode change by returning any error code different
 * from kPowerManagerSuccess (see POWER_SYS_SetMode()).
 * @param notify Notification structure. 
 * @param dataPtr Callback data. Refers to the data passed during callback registration. Intended to
 *  pass any driver or application data such as internal state information.
 * @return An error code or kPowerManagerSuccess.
 */
typedef power_manager_error_code_t (* power_manager_callback_t)(
    power_manager_notify_struct_t * notify,
    power_manager_callback_data_t * dataPtr
);

/*!
 * @brief callback configuration structure
 *
 * This structure holds configuration of callbacks passed
 * to the Power Manager during its initialization.
 * Callbacks of this type are expected to be statically
 * allocated.
 * This structure contains following application-defined data:
 *  callback - pointer to the callback function
 *  callbackType - specifies when the callback is called
 *  callbackData - pointer to the data passed to the callback.
 */
typedef struct _power_manager_callback_user_config {
    power_manager_callback_t callback;
    power_manager_callback_type_t callbackType;
    power_manager_callback_data_t * callbackData;
} power_manager_callback_user_config_t;

/*!
 * @brief Power Manager internal state structure.
 *
 * Power Manager internal structure. Contains data necessary for Power Manager proper
 * function. Stores references to registered power mode configurations,
 * callbacks, information about their numbers and other internal data.
 * This structure is statically allocated and initialized after POWER_SYS_Init() call.
 */
typedef struct _power_manager_state {
    power_manager_user_config_t const ** configs;   /*!< Pointer to power configure table.*/
    uint8_t configsNumber;                         /*!< Number of power configurations */
    power_manager_callback_user_config_t ** staticCallbacks; /*!< Pointer to callback table. */
    uint8_t staticCallbacksNumber;                 /*!< Maximum number of callback configurations */
    uint8_t errorCallbackIndex;                    /*!< Index of callback returns error. */
    uint8_t currentConfig;                         /*!< Index of current configuration.  */  
} power_manager_state_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Power Manager initialization for operation.
 *
 * This function initializes the Power Manager and its run-time state structure.
 * Reference to an array of power mode configuration structures has to be passed
 * as a parameter along with a parameter specifying its size. At least one power mode
 * configuration is required. Optionally, reference to the array of predefined
 * callbacks can be passed with its size parameter.
 * For details about callbacks, refer to the power_manager_callback_user_config_t.
 * As Power Manager stores only references to array of these structures, they have
 * to exist while Power Manager is used.
 * It is expected that prior to the POWER_SYS_Init() call the write-once protection
 * register was configured appropriately allowing for entry to all required low power
 * modes.
 * The following is an example of how to set up two power modes and three
 * callbacks, and initialize the Power Manager with structures containing their settings.
 * The example shows two possible ways the configuration structures can be stored
 * (ROM or RAM), although it is expected that they are placed in the read-only
 * memory to save the RAM space. (Note: In the example it is assumed that the programmed chip
 * doesn't support any optional power options described in the power_manager_user_config_t)
 * :
 * @code
    const power_manager_user_config_t waitConfig = {
        kPowerManagerVlpw,
        true,
        true,
    };

    const power_manager_callback_user_config_t callbackCfg0 = {
        callback0,
        kPowerManagerCallbackBefore,
        &callback_data0
    };

    const power_manager_callback_user_config_t callbackCfg1 = {
        callback1,
        kPowerManagerCallbackAfter,
        &callback_data1
    };

    const power_manager_callback_user_config_t callbackCfg2 = {
        callback2,
        kPowerManagerCallbackBeforeAfter,
        &callback_data2
    };

    const power_manager_callback_user_config_t * const callbacks[] = {&callbackCfg0, &callbackCfg1, &callbackCfg2};

    void main(void)
    {
        power_manager_user_config_t idleConfig;
        power_manager_user_config_t *powerConfigs[] = {&idleConfig, &waitConfig};

        idleConfig.mode = kPowerManagerVlps;
        idleConfig.sleepOnExitOption = true;
        idleConfig.sleepOnExitValue = false;

        POWER_SYS_Init(&powerConfigs, 2U, &callbacks, 3U);

        POWER_SYS_SetMode(0U, kPowerManagerPolicyAgreement);

    }
 * @endcode
 *
 * @param powerConfigsPtr A pointer to an array with references to all power
 *  configurations which is handled by the Power Manager.
 * @param configsNumber Number of power configurations. Size of powerConfigsPtr
 *  array.
 * @param callbacksPtr A pointer to an array with references to callback configurations.
 *  If there are no callbacks to register during Power Manager initialization, use NULL value.
 * @param callbacksNumber Number of registered callbacks. Size of callbacksPtr
 *  array.
 * @return An error code or kPowerManagerSuccess.
 */
power_manager_error_code_t POWER_SYS_Init(power_manager_user_config_t const ** powerConfigsPtr,
                                          uint8_t configsNumber,
                                          power_manager_callback_user_config_t ** callbacksPtr,
                                          uint8_t callbacksNumber);

/*!
 * @brief This function deinitializes the Power Manager.
 *
 * @return An error code or kPowerManagerSuccess.
 */
power_manager_error_code_t POWER_SYS_Deinit(void);

/*!
 * @brief This function configures the power mode.
 *
 * This function switches to one of the defined power modes. Requested mode number is passed
 * as an input parameter. This function notifies all registered callback functions before
 * the mode change (using  kPowerManagerCallbackBefore set as callback type parameter),
 * sets specific power options defined in the power mode configuration and enters the specified
 * mode. In case of run modes (for example, Run, Very low power run, or High speed run), this function
 * also invokes all registered callbacks after the mode change (using kPowerManagerCallbackAfter).
 * In case of sleep or deep sleep modes, if the requested mode is not exited through
 * a reset, these notifications are sent after the core wakes up.
 * Callbacks are invoked in the following order: All registered callbacks are notified
 * ordered by index in the callbacks array (see callbacksPtr parameter of POWER_SYS_Init()).
 * The same order is used for before and after switch notifications.
 * The notifications before the power mode switch can be used to obtain confirmation about
 * the change from registered callbacks. If any registered callback denies the power
 * mode change, further execution of this function depends on mode change policy: the mode
 * change is either forced (kPowerManagerPolicyForcible) or exited (kPowerManagerPolicyAgreement).
 * When mode change is forced, the result of the before switch notifications are ignored. If
 * agreement is required, if any callback returns an error code then further notifications
 * before switch notifications are cancelled and all already notified callbacks are re-invoked
 * with kPowerManagerCallbackAfter set as callback type parameter. The index of the callback
 * which returned error code during pre-switch notifications is stored (any error codes during
 * callbacks re-invocation are ignored) and POWER_SYS_GetErrorCallback() can be used to get it.
 * Regardless of the policies, if any callback returned an error code, an error code denoting in which phase
 * the error occurred is returned when POWER_SYS_SetMode() exits.
 * It is possible to enter any mode supported by the processor. Refer to the chip reference manual
 * for list of available power modes. If it is necessary to switch into intermediate power mode prior to
 * entering requested mode (for example, when switching from Run into Very low power wait through Very low
 * power run mode), then the intermediate mode is entered without invoking the callback mechanism.
 *
 * @param powerModeIndex Requested power mode represented as an index into
 *  array of user-defined power mode configurations passed to the POWER_SYS_Init().
 * @param policy Transaction policy
 * @return An error code or kPowerManagerSuccess.
 */
power_manager_error_code_t POWER_SYS_SetMode(uint8_t powerModeIndex, power_manager_policy_t policy);

/*!
 * @brief This function returns power mode set as the last one.
 *
 * This function returns index of power mode which was set using POWER_SYS_SetMode() as the last one.
 * If the power mode was entered even though some of the registered callback denied the mode change,
 * or if any of the callbacks invoked after the entering/restoring run mode failed, then the return
 * code of this function has kPowerManagerError value.
 *
 * @param powerModeIndexPtr Power mode which has been set represented as an index into array of power mode
 * configurations passed to the POWER_SYS_Init().
 * @return An error code or kPowerManagerSuccess.
 */
power_manager_error_code_t POWER_SYS_GetLastMode(uint8_t *powerModeIndexPtr);

/*!
 * @brief This function returns user configuration structure of power mode set as the last one.
 *
 * This function returns reference to configuration structure which was set using POWER_SYS_SetMode()
 * as the last one. If the current power mode was entered even though some of the registered callback denied
 * the mode change, or if any of the callbacks invoked after the entering/restoring run mode failed, then
 * the return code of this function has kPowerManagerError value.
 *
 * @param powerModePtr Pointer to power mode configuration structure of power mode set as last one.
 * @return An error code or kPowerManagerSuccess.
 */
power_manager_error_code_t POWER_SYS_GetLastModeConfig(power_manager_user_config_t const ** powerModePtr);

/*!
 * @brief This function returns the currently running power mode.
 *
 * This function reads hardware settings and returns currently running power mode. Generally,
 * this function can return only kPowerManagerRun, kPowerManagerVlpr or kPowerManagerHsrun value.
 *
  * @return Currently used run power mode.
 */
power_manager_modes_t POWER_SYS_GetCurrentMode(void);

/*!
 * @brief This function returns the last failed notification callback.
 *
 * This function returns index of the last callback that failed during the power mode switch while
 * the last POWER_SYS_SetMode() was called. If the last POWER_SYS_SetMode() call ended successfully 
 * value equal to callbacks number is returned. Returned value represents index in the array of 
 * static call-backs.
 *
 * @return Callback index of last failed callback or value equal to callbacks count.
 */
uint8_t POWER_SYS_GetErrorCallbackIndex(void);

/*!
 * @brief This function returns the last failed notification callback configuration structure.
 *
 * This function returns pointer to configuration structure of the last callback that failed during 
 * the power mode switch while the last POWER_SYS_SetMode() was called. 
 * If the last POWER_SYS_SetMode() call ended successfully value NULL is returned. 
 *
 * @return Pointer to the callback configuration which returns error.
 */
power_manager_callback_user_config_t* POWER_SYS_GetErrorCallback(void);

/*!
 * @brief This function returns whether very low power mode is running.
 *
 * This function is used to detect whether very low power mode is running.
 *
 * @return Returns true if processor runs in very low power mode, otherwise false.
 */
bool POWER_SYS_GetVeryLowPowerModeStatus(void);

/*!
 * @brief This function returns whether reset was caused by low leakage wake up.
 *
 * This function is used to check that processor exited low leakage power mode
 * through reset.
 *
 * @return Returns true if processor was reset by low leakage wake up,
 *  otherwise false.
 */
bool POWER_SYS_GetLowLeakageWakeupResetStatus(void);

/*!
 * @brief Gets the acknowledge isolation flag.
 *
 * This function is used to check certain peripherals and the I/O pads are in a latched state 
 * as a result of having been in a VLLS mode.
 *
 * After recovery from VLLS, the LLWU continues to detect wake-up events until the user has 
 * acknowledged the wake-up via POWER_SYS_ClearAckIsolation()
 * 
 * @return Returns true if ACK isolation is set.
 */
bool POWER_SYS_GetAckIsolation(void);

/*!
 * @brief Clears the acknowledge isolation flag.
 *
 * This function  clears the ACK Isolation flag. Clearing releases the I/O pads and certain 
 * peripherals to their normal run mode state.
 *
 * After recovery from VLLS, the LLWU continues to detect wake-up events until the user has 
 * acknowledged the wake-up via POWER_SYS_ClearAckIsolation()
 * 
 */
void POWER_SYS_ClearAckIsolation(void);

#include "../src/power/fsl_power_manager_common.h"

#if FSL_FEATURE_SOC_LLWU_COUNT
/*!
 * The LLWU module becomes functional on entry into a low-leakage power mode. After
 * recovery from LLS, the LLWU is immediately disabled. After recovery from VLLS, the
 * LLWU continues to detect wake-up events until the user has acknowledged the wake-up
 * via POWER_SYS_ClearAckIsolation().
 * 
 * LLS modes:
 * The wake-up events due to external wake-up inputs and internal module wake-up inputs
 * result in an interrupt flow when exiting LLS. A reset event due to RESET pin assertion
 * results in a reset flow when exiting LLS.
 * 
 * VLLS modes:
 * All wakeup and reset events result in VLLS exit via a reset flow.
 * 
 * The LLWU is not active in all non-low leakage modes where detection and control logic
 * are in a static state. The LLWU registers are accessible in non-low leakage modes and are
 * available for configuring and reading status when bus transactions are possible.
 */

#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE
/*!
 * @brief This function allows to set wake up module in low leakage wake up unit (LLWU).
 * Each of the available wake-up sources can be individually enabled or disabled.
 * 
 * The LLWU is not active in all non-low leakage modes where detection and control logic
 * are in a static state. The LLWU registers are accessible in non-low leakage modes and are
 * available for configuring and reading status when bus transactions are possible.
 *
 * After recovery from VLLS, the LLWU continues to detect wake-up events until the user has 
 * acknowledged the wake-up via POWER_SYS_ClearAckIsolation()
 *
 * @param module Wake up module name which is set.
 * @param enable Specifies if wake up from module is enabled (true) or disabled (false).
 */
void POWER_SYS_SetWakeupModule(power_wakeup_module_t module,bool enable);

/*!
 * @brief This function allows to get wake up module flag in LLWU.
 * 
 * For internal peripherals that are capable of running in a low-leakage power mode, such as
 * a real time clock module or CMP module, the flag from the associated peripheral is
 * accessible and returned by this function.
 * 
 * The flag  needs to be cleared in the peripheral instead of clearing in LLWU.
 *
 * @param module Wake up module name.
 * @return Returns true if module flag is set.
 */
bool POWER_SYS_GetWakeupModuleFlag(power_wakeup_module_t module);

#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN
/*!
 * @brief This function allows to set wake up pin in low leakage wake up unit (LLWU) and allows to configure
 * pin electrical parameters if GPIO pin configuration is passed as parameter.
 * Each of the available wake-up sources can be individually enabled or disabled.
 *
 * The LLWU is not active in all non-low leakage modes where detection and control logic
 * are in a static state. The LLWU registers are accessible in non-low leakage modes and are
 * available for configuring and reading status when bus transactions are possible.
 *
 * After recovery from VLLS, the LLWU continues to detect wake-up events until the user has 
 * acknowledged the wake-up via POWER_SYS_ClearAckIsolation()
 * 
 * @param pin Wake up pin name which is set.
 * @param pinMode pin configuration mode defined in llwu_external_pin_modes_t.
 * @param config optional parameter. If passed GPIO pin configuration GPIO pin is configured.
 */
void POWER_SYS_SetWakeupPin(power_wakeup_pin_t pin, llwu_external_pin_modes_t pinMode, const gpio_input_pin_t * config);

/*!
 * @brief This function allows to get wake up pin flag in low leakage wake up unit (LLWU).
 * 
 * @param pin Wake up pin name.
 * @return Returns pin wake up flag.
 */
bool POWER_SYS_GetWakeupPinFlag(power_wakeup_pin_t pin);

/*!
 * @brief This function allows to clear wake up pin flag in low leakage wake up unit (LLWU).
 * 
 * @param pin Wake up pin name
 */
void POWER_SYS_ClearWakeupPinFlag(power_wakeup_pin_t pin);

#endif
#endif

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_POWER_MANAGER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

