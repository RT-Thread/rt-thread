/***************************************************************************//**
* \file cyhal_syspm.c
*
* \brief
* Provides a high level interface for interacting with the Infineon power
* management and system clock configuration. This interface abstracts out the
* chip specific details. If any chip specific functionality is necessary, or
* performance is critical the low level functions can be used directly.
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
#if defined(COMPONENT_CAT1)
/**
 * \addtogroup group_hal_impl_syspm System Power Management
 * \ingroup group_hal_impl
 * \{
 * \section section_hal_impl_syspm_set_system
 *
 * The callback mode \ref CYHAL_SYSPM_AFTER_DS_WFI_TRANSITION is only applicable
 * for CAT1B devices.
 *
 * Setting the system state is unsupported on CAT1C devices. For CAT1C devices,
 * \ref CYHAL_SYSPM_RSLT_ERR_NOT_SUPPORTED will be returned in the function \ref cyhal_syspm_set_system_state.
 *
 * \} group_hal_impl_pwm
 */
#elif defined(COMPONENT_CAT2)
/**
 * \addtogroup group_hal_impl_syspm System Power Management
 * \ingroup group_hal_impl
 * \{
 * \section section_hal_impl_syspm_set_system
 *
 * Setting the system state is unsupported on CAT2 devices. For CAT2 devices,
 * \ref CYHAL_SYSPM_RSLT_ERR_NOT_SUPPORTED will be returned in the function \ref cyhal_syspm_set_system_state.
 *
 * \} group_hal_impl_pwm
 */
#endif

#include <limits.h>
#include <string.h>
#include "cyhal_system.h"
#include "cyhal_syspm.h"
#include "cy_syspm.h"
#include "cy_utils.h"
#include "cyhal_utils.h"
#if (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && defined(CY_IP_MXS40SSRSS)
#include "cyabs_rtos_dsram.h"
#endif
#if defined(COMPONENT_CAT1B)
#include "system_cat1b.h"
#endif

#if (CYHAL_DRIVER_AVAILABLE_LPTIMER != 0)
#include "cyhal_lptimer.h"
#endif /* (CYHAL_DRIVER_AVAILABLE_LPTIMER != 0) */

#if (CYHAL_DRIVER_AVAILABLE_SYSPM)

#if defined(__cplusplus)
extern "C"
{
#endif

/* Check if the SysTick is enabled */
#define _cyhal_syspm_is_systick_enabled() (SysTick->CTRL & SysTick_CTRL_ENABLE_Msk)

/* Disable the SysTick */
#define _cyhal_syspm_disable_systick() (SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk)

/* Enable the SysTick */
#define _cyhal_syspm_enable_systick()  (SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk)

/* Hz to KHz */
#define _CYHAL_HZ_TO_KHZ_CONVERSION_FACTOR         1000

/* The first entry in the callback chain is always reserved for the user set
 * cyhal_syspm_register_callback callback. This may be set to a sentinel value
 * indicating it is the end of the list. All subsequent slots are where
 * peripheral drivers are tracked. This makes it very easy to determine whether
 * the user registered a callback and to make sure we run that first. */
static cyhal_syspm_callback_data_t* _cyhal_syspm_callback_ptr = CYHAL_SYSPM_END_OF_LIST;
static cyhal_syspm_callback_data_t* _cyhal_syspm_peripheral_callback_ptr = CYHAL_SYSPM_END_OF_LIST;

static uint16_t _cyhal_deep_sleep_lock = 0;

static uint32_t _cyhal_syspm_supply_voltages[((size_t)CYHAL_VOLTAGE_SUPPLY_MAX) + 1] = { 0 };

static bool _cyhal_systick_disable = false;
static bool _cyhal_disable_systick_before_sleep_deepsleep = false;

#define SYSPM_CALLBACK_ORDER    (10u)

static cy_stc_syspm_callback_params_t _cyhal_syspm_cb_params_default = {NULL, NULL};
static const cy_stc_syspm_callback_t _cyhal_syspm_cb_default =
{
    .callback = NULL,
    .type = CY_SYSPM_SLEEP,
    .skipMode = 0,
    .callbackParams = &_cyhal_syspm_cb_params_default,
    .prevItm = NULL,
    .nextItm = NULL,
    .order = SYSPM_CALLBACK_ORDER,
};

static cy_stc_syspm_callback_t _cyhal_syspm_sleep;
static cy_stc_syspm_callback_t _cyhal_syspm_deepsleep;
static cy_stc_syspm_callback_t _cyhal_syspm_hibernate;
#if defined(COMPONENT_CAT1A)
static cy_stc_syspm_callback_t _cyhal_syspm_lp;
static cy_stc_syspm_callback_t _cyhal_syspm_normal;
#elif defined(COMPONENT_CAT1B)
static cy_stc_syspm_callback_t _cyhal_syspm_lp;
static cy_stc_syspm_callback_t _cyhal_syspm_normal;
static cy_stc_syspm_callback_t _cyhal_syspm_deepsleep_ram;
static cy_stc_syspm_callback_t _cyhal_syspm_deepsleep_off;
#endif /* defined(COMPONENT_CAT1A) */

static cyhal_syspm_callback_data_t* _cyhal_syspm_call_all_pm_callbacks(
    cyhal_syspm_callback_data_t* entry, bool* allow, cyhal_syspm_callback_state_t state, cyhal_syspm_callback_mode_t mode)
{
    while(entry != CYHAL_SYSPM_END_OF_LIST)
    {
        if (entry->callback != NULL &&
            (entry->states & state) == state &&
            (entry->ignore_modes & mode) != mode)
        {
            *allow = entry->callback(state, mode, entry->args) || mode != CYHAL_SYSPM_CHECK_READY;
            if (!(*allow))
            {
                // Do not increment pointer so that backtracking stop at the correct location
                break;
            }
        }
        entry = entry->next;
    }
    return entry;
}

static void _cyhal_syspm_backtrack_all_pm_callbacks(cyhal_syspm_callback_data_t* start, cyhal_syspm_callback_data_t* end, cyhal_syspm_callback_state_t state)
{
    while(start != end)
    {
        if (start->callback != NULL &&
            (start->states & state) == state &&
            (start->ignore_modes & CYHAL_SYSPM_CHECK_FAIL) != CYHAL_SYSPM_CHECK_FAIL)
        {
            start->callback(state, CYHAL_SYSPM_CHECK_FAIL, start->args);
        }
        start = start->next;
    }
}

static cy_en_syspm_status_t _cyhal_syspm_common_cb(cy_en_syspm_callback_mode_t mode, cyhal_syspm_callback_state_t state)
{
    // The PDL function that wrap around this callback enters critical section, this function does not need to enter critical section.
    cyhal_syspm_callback_mode_t hal_mode = _cyhal_utils_convert_pdltohal_pm_mode(mode);
    bool allow = true;

    cyhal_syspm_callback_data_t *first, *second;
    if (hal_mode == CYHAL_SYSPM_CHECK_FAIL || hal_mode == CYHAL_SYSPM_AFTER_TRANSITION || hal_mode == CYHAL_SYSPM_AFTER_DS_WFI_TRANSITION)
    {
        first = _cyhal_syspm_peripheral_callback_ptr;
        second = _cyhal_syspm_callback_ptr;
    }
    else
    {
        second = _cyhal_syspm_peripheral_callback_ptr;
        first = _cyhal_syspm_callback_ptr;
    }

    cyhal_syspm_callback_data_t* first_current = _cyhal_syspm_call_all_pm_callbacks(first, &allow, state, hal_mode);
    cyhal_syspm_callback_data_t* second_current = allow
        ? _cyhal_syspm_call_all_pm_callbacks(second, &allow, state, hal_mode)
        : second;

    if (!allow && (CYHAL_SYSPM_CHECK_READY == hal_mode))
    {
        _cyhal_syspm_backtrack_all_pm_callbacks(second, second_current, state);
        _cyhal_syspm_backtrack_all_pm_callbacks(first, first_current, state);
    }

    return allow ? CY_SYSPM_SUCCESS : CY_SYSPM_FAIL;
}

static cy_en_syspm_status_t _cyhal_syspm_cb_sleep_deepsleep(cy_en_syspm_callback_mode_t mode, cyhal_syspm_callback_state_t state)
{
    cy_en_syspm_status_t status = _cyhal_syspm_common_cb(mode, state);
    // No need to test status here, as it only gets set when mode == CYHAL_SYSPM_CHECK_READY
    if (mode == CY_SYSPM_BEFORE_TRANSITION)
    {
        _cyhal_systick_disable = _cyhal_syspm_is_systick_enabled() && _cyhal_disable_systick_before_sleep_deepsleep;
        if (_cyhal_systick_disable)
        {
            _cyhal_syspm_disable_systick();
        }
    }
    else if (mode == CY_SYSPM_AFTER_TRANSITION)
    {
        if (_cyhal_systick_disable)
        {
            _cyhal_syspm_enable_systick();
        }
    }
    return status;
}

static cy_en_syspm_status_t _cyhal_syspm_cb_sleep(cy_stc_syspm_callback_params_t *callback_params, cy_en_syspm_callback_mode_t mode)
{
    CY_UNUSED_PARAMETER(callback_params);
    return _cyhal_syspm_cb_sleep_deepsleep(mode, CYHAL_SYSPM_CB_CPU_SLEEP);
}
static cy_en_syspm_status_t _cyhal_syspm_cb_deepsleep(cy_stc_syspm_callback_params_t *callback_params, cy_en_syspm_callback_mode_t mode)
{
    if((mode == CY_SYSPM_CHECK_READY) && (_cyhal_deep_sleep_lock != 0))
    {
        return CY_SYSPM_FAIL;
    }
    CY_UNUSED_PARAMETER(callback_params);
    return _cyhal_syspm_cb_sleep_deepsleep(mode, CYHAL_SYSPM_CB_CPU_DEEPSLEEP);
}
static cy_en_syspm_status_t _cyhal_syspm_cb_hibernate(cy_stc_syspm_callback_params_t *callback_params, cy_en_syspm_callback_mode_t mode)
{
    CY_UNUSED_PARAMETER(callback_params);
    return _cyhal_syspm_common_cb(mode, CYHAL_SYSPM_CB_SYSTEM_HIBERNATE);
}
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B)
static cy_en_syspm_status_t _cyhal_syspm_cb_normal(cy_stc_syspm_callback_params_t *callback_params, cy_en_syspm_callback_mode_t mode)
{
    CY_UNUSED_PARAMETER(callback_params);
    cy_en_syspm_status_t status = _cyhal_syspm_common_cb(mode, CYHAL_SYSPM_CB_SYSTEM_NORMAL);

#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1C)
    if (mode == CY_SYSPM_AFTER_TRANSITION)
    {
        uint32_t hfclk_freq_mhz = Cy_SysClk_ClkHfGetFrequency(0) / 1000000;
        Cy_SysLib_SetWaitStates(false, hfclk_freq_mhz);
    }
#endif /* defined(COMPONENT_CAT1A) */
    return status;
}
static cy_en_syspm_status_t _cyhal_syspm_cb_lp(cy_stc_syspm_callback_params_t *callback_params, cy_en_syspm_callback_mode_t mode)
{
    CY_UNUSED_PARAMETER(callback_params);
    cy_en_syspm_status_t status = _cyhal_syspm_common_cb(mode, CYHAL_SYSPM_CB_SYSTEM_LOW);

    if (mode == CY_SYSPM_BEFORE_TRANSITION)
    {
        uint32_t hfclk_freq_mhz = Cy_SysClk_ClkHfGetFrequency(0) / 1000000;
        Cy_SysLib_SetWaitStates(true, hfclk_freq_mhz);
    }
    return status;
}
#endif
#if defined(COMPONENT_CAT1B)
static cy_en_syspm_status_t _cyhal_syspm_cb_deepsleep_ram(cy_stc_syspm_callback_params_t *callback_params, cy_en_syspm_callback_mode_t mode)
{
    CY_UNUSED_PARAMETER(callback_params);
    if ((mode == CY_SYSPM_CHECK_READY) && (_cyhal_deep_sleep_lock != 0))
    {
        return CY_SYSPM_FAIL;
    }
    return _cyhal_syspm_common_cb(mode, CYHAL_SYSPM_CB_CPU_DEEPSLEEP/*_RAM*/);
}
static cy_en_syspm_status_t _cyhal_syspm_cb_deepsleep_off(cy_stc_syspm_callback_params_t *callback_params, cy_en_syspm_callback_mode_t mode)
{
    CY_UNUSED_PARAMETER(callback_params);
    return _cyhal_syspm_common_cb(mode, CYHAL_SYSPM_CB_CPU_DEEPSLEEP/*_OFF*/);
}
#endif

static inline bool _cyhal_syspm_is_registered(cyhal_syspm_callback_data_t *callback)
{
    // If callback->next is NULL it must not be registered since all registered
    // next ptrs in the list must point to the next callback or be equal to
    // CYHAL_SYSPM_END_OF_LIST
    return (callback->next != NULL);
}

static void _cyhal_syspm_add_callback_to_list(cyhal_syspm_callback_data_t **list, cyhal_syspm_callback_data_t *add)
{
    uint32_t intr_status = cyhal_system_critical_section_enter();
    if(!_cyhal_syspm_is_registered(add))
    {
        add->next = *list;
        *list = add;
    }
    cyhal_system_critical_section_exit(intr_status);
}

static void _cyhal_syspm_remove_callback_from_list(cyhal_syspm_callback_data_t **list, cyhal_syspm_callback_data_t *rmv)
{
    uint32_t intr_status = cyhal_system_critical_section_enter();
    while(*list != CYHAL_SYSPM_END_OF_LIST)
    {
        if (*list == rmv)
        {
            *list = rmv->next;
            rmv->next = NULL;
            break;
        }
        list = &((*list)->next);
    }
    cyhal_system_critical_section_exit(intr_status);
}

void _cyhal_syspm_register_peripheral_callback(cyhal_syspm_callback_data_t *callback_data)
{
    CY_ASSERT(callback_data != NULL);
    _cyhal_syspm_add_callback_to_list(&_cyhal_syspm_peripheral_callback_ptr, callback_data);
}

void _cyhal_syspm_unregister_peripheral_callback(cyhal_syspm_callback_data_t *callback_data)
{
    CY_ASSERT(callback_data != NULL);
    _cyhal_syspm_remove_callback_from_list(&_cyhal_syspm_peripheral_callback_ptr, callback_data);
}

static bool _cyhal_syspm_register_cb(cy_stc_syspm_callback_t *data, cy_en_syspm_callback_type_t type, Cy_SysPmCallback callback)
{
    memcpy(data, &_cyhal_syspm_cb_default, sizeof(cy_stc_syspm_callback_t));
    data->callback = callback;
    data->type = type;
    return Cy_SysPm_RegisterCallback(data);
}


/******************************************************************************
 ******************************** Public APIs *********************************
 *****************************************************************************/

cy_rslt_t cyhal_syspm_init(void)
{
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
    /* Check the IO status. If current status is frozen, unfreeze the system. */
    if (Cy_SysPm_GetIoFreezeStatus())
    {
        /* Unfreeze the system */
        Cy_SysPm_IoUnfreeze();
    }
#endif /* defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) */

    cy_rslt_t rslt = CY_RSLT_SUCCESS;
    if (!_cyhal_syspm_register_cb(&_cyhal_syspm_sleep, CY_SYSPM_SLEEP, _cyhal_syspm_cb_sleep)
        || !_cyhal_syspm_register_cb(&_cyhal_syspm_deepsleep, CY_SYSPM_DEEPSLEEP, _cyhal_syspm_cb_deepsleep)
        || !_cyhal_syspm_register_cb(&_cyhal_syspm_hibernate, CY_SYSPM_HIBERNATE, _cyhal_syspm_cb_hibernate)
#if defined(COMPONENT_CAT1A)
        || !_cyhal_syspm_register_cb(&_cyhal_syspm_normal, CY_SYSPM_LP, _cyhal_syspm_cb_normal)
        || !_cyhal_syspm_register_cb(&_cyhal_syspm_lp, CY_SYSPM_ULP, _cyhal_syspm_cb_lp)
#elif defined(COMPONENT_CAT1B)
        || !_cyhal_syspm_register_cb(&_cyhal_syspm_lp, CY_SYSPM_LPACTIVE_ENTER, _cyhal_syspm_cb_lp)
        || !_cyhal_syspm_register_cb(&_cyhal_syspm_normal, CY_SYSPM_LPACTIVE_EXIT, _cyhal_syspm_cb_normal)
        || !_cyhal_syspm_register_cb(&_cyhal_syspm_deepsleep_ram, CY_SYSPM_DEEPSLEEP_RAM, _cyhal_syspm_cb_deepsleep_ram)
        || !_cyhal_syspm_register_cb(&_cyhal_syspm_deepsleep_off, CY_SYSPM_DEEPSLEEP_OFF, _cyhal_syspm_cb_deepsleep_off)
#endif /* defined(COMPONENT_CAT1A)*/
    )
        {
            rslt = CYHAL_SYSPM_RSLT_INIT_ERROR;
        }
    return rslt;
}

cy_rslt_t cyhal_syspm_hibernate(cyhal_syspm_hibernate_source_t wakeup_source)
{
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
    /* Defines for mapping hal hibernate sources to pdl */
    static const uint32_t source_map[] =
    {
        0u,                                        // Default value, no wakeup
        (uint32_t)CY_SYSPM_HIBERNATE_LPCOMP0_LOW,  // CYHAL_SYSPM_HIBERNATE_LPCOMP0_LOW
        (uint32_t)CY_SYSPM_HIBERNATE_LPCOMP0_HIGH, // CYHAL_SYSPM_HIBERNATE_LPCOMP0_HIGH
        (uint32_t)CY_SYSPM_HIBERNATE_LPCOMP1_LOW,  // CYHAL_SYSPM_HIBERNATE_LPCOMP1_LOW
        (uint32_t)CY_SYSPM_HIBERNATE_LPCOMP1_HIGH, // CYHAL_SYSPM_HIBERNATE_LPCOMP1_HIGH
        (uint32_t)CY_SYSPM_HIBERNATE_RTC_ALARM,    // CYHAL_SYSPM_HIBERNATE_RTC_ALARM
        (uint32_t)CY_SYSPM_HIBERNATE_WDT,          // CYHAL_SYSPM_HIBERNATE_WDT
        (uint32_t)CY_SYSPM_HIBERNATE_PIN0_LOW,     // CYHAL_SYSPM_HIBERNATE_PINA_LOW
        (uint32_t)CY_SYSPM_HIBERNATE_PIN0_HIGH,    // CYHAL_SYSPM_HIBERNATE_PINA_HIGH
        (uint32_t)CY_SYSPM_HIBERNATE_PIN1_LOW,     // CYHAL_SYSPM_HIBERNATE_PINB_LOW
        (uint32_t)CY_SYSPM_HIBERNATE_PIN1_HIGH,    // CYHAL_SYSPM_HIBERNATE_PINB_HIGH
    };

    Cy_SysPm_SetHibernateWakeupSource(_cyhal_utils_convert_flags(source_map, sizeof(source_map) / sizeof(uint32_t), (uint32_t)wakeup_source));
    return Cy_SysPm_SystemEnterHibernate();
#elif defined(COMPONENT_CAT2)
    CY_UNUSED_PARAMETER(wakeup_source);
    return CYHAL_SYSPM_RSLT_ERR_NOT_SUPPORTED;
#endif /* defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C) */
}

cy_rslt_t cyhal_syspm_set_system_state(cyhal_syspm_system_state_t state)
{
#if defined(COMPONENT_CAT2) || defined(COMPONENT_CAT1C)
    CY_UNUSED_PARAMETER(state);
    return CYHAL_SYSPM_RSLT_ERR_NOT_SUPPORTED;
#else
    cy_rslt_t rslt;

    /* The wait states are changed in the common syspm handler after
     * state change is allowed and all handlers are called to take into
     * account any frequency change that might happen as a part of the
     * power management handlers
     */
    switch (state)
    {
        case CYHAL_SYSPM_SYSTEM_NORMAL:
#if defined(CY_IP_MXS40SSRSS)
            rslt = Cy_SysPm_SystemLpActiveExit();
#else
            rslt = Cy_SysPm_SystemEnterLp();
#endif
            break;
        case CYHAL_SYSPM_SYSTEM_LOW:
#if defined(CY_IP_MXS40SSRSS)
            rslt = Cy_SysPm_SystemLpActiveEnter();
#else
            rslt = Cy_SysPm_SystemEnterUlp();
#endif
            break;
        default:
            /* Should never get here */
            CY_ASSERT(false);
            rslt = CYHAL_SYSPM_RSLT_BAD_ARGUMENT;
            break;
    }
    return rslt;
#endif /* defined(COMPONENT_CAT2) */
}

void cyhal_syspm_register_callback(cyhal_syspm_callback_data_t *callback_data)
{
    CY_ASSERT(callback_data != NULL);
    _cyhal_syspm_add_callback_to_list(&_cyhal_syspm_callback_ptr, callback_data);
}

void cyhal_syspm_unregister_callback(cyhal_syspm_callback_data_t *callback_data)
{
    CY_ASSERT(callback_data != NULL);
    _cyhal_syspm_remove_callback_from_list(&_cyhal_syspm_callback_ptr, callback_data);
}

void cyhal_syspm_lock_deepsleep(void)
{
    CY_ASSERT(_cyhal_deep_sleep_lock != USHRT_MAX);
    uint32_t intr_status = cyhal_system_critical_section_enter();
    _cyhal_deep_sleep_lock++;
    cyhal_system_critical_section_exit(intr_status);
}

void cyhal_syspm_unlock_deepsleep(void)
{
    CY_ASSERT(_cyhal_deep_sleep_lock != 0U);
    uint32_t intr_status = cyhal_system_critical_section_enter();
    _cyhal_deep_sleep_lock--;
    cyhal_system_critical_section_exit(intr_status);
}


#if defined(CY_IP_MXS40SSRSS) && (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE))
cy_rslt_t _cyhal_syspm_enter_deepsleep_ram(void)
{
    cy_rslt_t retVal;
    uint32_t dsramIntState;

    retVal = Cy_SysPm_SetupDeepSleepRAM(CY_SYSPM_PRE_DSRAM, &dsramIntState); /* Pre DSRAM checks */
    if(retVal == CY_RSLT_SUCCESS)
    {
        System_Store_NVIC_Reg();
        cyabs_rtos_enter_dsram(); /* Enter WFI with context saved */
        System_Restore_NVIC_Reg();

        Cy_SysPm_SetupDeepSleepRAM(CY_SYSPM_POST_DSRAM, &dsramIntState); /* Post DSRAM Checks */
    }
    return retVal;
}
#endif


cy_rslt_t cyhal_syspm_deepsleep(void)
{
    if(_cyhal_deep_sleep_lock != 0)
    {
        return CYHAL_SYSPM_RSLT_DEEPSLEEP_LOCKED;
    }
    else
    {
#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
#if defined(CY_IP_MXS40SSRSS) && (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE))
        if(Cy_SysPm_GetDeepSleepMode() == CY_SYSPM_MODE_DEEPSLEEP_RAM)
        {
            return _cyhal_syspm_enter_deepsleep_ram();
        }
        else
#endif
        {
            return Cy_SysPm_CpuEnterDeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
        }
#elif defined(COMPONENT_CAT2)
        return Cy_SysPm_CpuEnterDeepSleep();
#endif
    }
}


cy_rslt_t cyhal_syspm_tickless_sleep_deepsleep(cyhal_lptimer_t *obj, uint32_t desired_ms, uint32_t *actual_ms, bool deep_sleep)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;

    #if (CYHAL_DRIVER_AVAILABLE_LPTIMER != 0)
    CY_ASSERT(obj != NULL);
    uint32_t initial_ticks;
    uint32_t sleep_ticks;
    cyhal_lptimer_info_t timer_info;

    *actual_ms = 0;

    if(desired_ms > 0)
    {
        cyhal_lptimer_get_info(obj, &timer_info);

        //lp_ticks = ms * lp_rate_khz
        sleep_ticks = (uint32_t)(((uint64_t)(desired_ms - 1) * timer_info.frequency_hz) / _CYHAL_HZ_TO_KHZ_CONVERSION_FACTOR);

        result = cyhal_lptimer_set_delay(obj, sleep_ticks);
        initial_ticks = cyhal_lptimer_read(obj);
        if(result == CY_RSLT_SUCCESS)
        {
            /* Disabling and enabling the system timer is handled in _cyhal_syspm_common_cb in order
             * to prevent loosing kernel ticks when sleep/deep-sleep is rejected causing the time spent
             * in the callback handlers to check if the system can make the sleep/deep-sleep transition
             * to be not accounted for.
             */
            _cyhal_disable_systick_before_sleep_deepsleep = true;
            cyhal_lptimer_enable_event(obj, CYHAL_LPTIMER_COMPARE_MATCH, CYHAL_ISR_PRIORITY_DEFAULT, true);

            result = deep_sleep ? cyhal_syspm_deepsleep() : cyhal_syspm_sleep();

            if(result == CY_RSLT_SUCCESS)
            {
                uint32_t final_ticks = cyhal_lptimer_read(obj);
                uint32_t ticks = (final_ticks < initial_ticks)
                                ? (timer_info.max_counter_value - initial_ticks) + final_ticks
                                : final_ticks - initial_ticks;
                *actual_ms = (uint32_t)(((uint64_t)ticks * _CYHAL_HZ_TO_KHZ_CONVERSION_FACTOR) / timer_info.frequency_hz);
            }

            cyhal_lptimer_enable_event(obj, CYHAL_LPTIMER_COMPARE_MATCH, CYHAL_ISR_PRIORITY_DEFAULT, false);
            _cyhal_disable_systick_before_sleep_deepsleep = false;
        }
    }

    #else
    /* no lptimer available on currently selected device */
    result = CYHAL_SYSPM_RSLT_ERR_NOT_SUPPORTED;
    CY_UNUSED_PARAMETER(obj);
    CY_UNUSED_PARAMETER(desired_ms);
    CY_UNUSED_PARAMETER(actual_ms);
    CY_UNUSED_PARAMETER(deep_sleep);
    #endif /* (CYHAL_DRIVER_AVAILABLE_LPTIMER != 0) */

    return result;
}


void cyhal_syspm_set_supply_voltage(cyhal_syspm_voltage_supply_t supply, uint32_t mvolts)
{
    CY_ASSERT((size_t)supply <= CYHAL_VOLTAGE_SUPPLY_MAX);
    _cyhal_syspm_supply_voltages[(size_t)supply] = mvolts;
}

uint32_t cyhal_syspm_get_supply_voltage(cyhal_syspm_voltage_supply_t supply)
{
    CY_ASSERT((size_t)supply <= CYHAL_VOLTAGE_SUPPLY_MAX);
    return _cyhal_syspm_supply_voltages[(size_t)supply];
}

#if defined(__cplusplus)
}
#endif

#endif // CYHAL_DRIVER_AVAILABLE_SYSPM
