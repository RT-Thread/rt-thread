/***************************************************************************//**
* \file cy_syspm_v3.c
* \version 5.91
*
* This driver provides the source code for API power management.
*
********************************************************************************
* \copyright
* Copyright (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
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

#include "cy_device.h"
#include "cy_sysclk.h"

#if defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)

#include "cy_syspm.h"

/*******************************************************************************
*       Internal Functions
*******************************************************************************/

/*******************************************************************************
*       Internal Defines
*******************************************************************************/

/* The define for number of callback roots */
#define CALLBACK_ROOT_NR                (5U)

/* The mask to unlock the Hibernate power mode */
#define HIBERNATE_UNLOCK_VAL                 ((uint32_t) 0x3Au << SRSS_PWR_HIBERNATE_UNLOCK_Pos)

/* The mask to set the Hibernate power mode */
#define SET_HIBERNATE_MODE                   ((HIBERNATE_UNLOCK_VAL |\
                                               SRSS_PWR_HIBERNATE_FREEZE_Msk |\
                                               SRSS_PWR_HIBERNATE_HIBERNATE_Msk))

/* The mask to retain the Hibernate power mode status */
#define HIBERNATE_RETAIN_STATUS_MASK         ((SRSS_PWR_HIBERNATE_TOKEN_Msk |\
                                               SRSS_PWR_HIBERNATE_MASK_HIBALARM_Msk |\
                                               SRSS_PWR_HIBERNATE_MASK_HIBWDT_Msk |\
                                               SRSS_PWR_HIBERNATE_POLARITY_HIBPIN_Msk |\
                                               SRSS_PWR_HIBERNATE_MASK_HIBPIN_Msk))

/** The mask for the Hibernate wakeup sources */
#define HIBERNATE_WAKEUP_MASK               ((SRSS_PWR_HIBERNATE_MASK_HIBALARM_Msk |\
                                              SRSS_PWR_HIBERNATE_MASK_HIBWDT_Msk |\
                                              SRSS_PWR_HIBERNATE_POLARITY_HIBPIN_Msk |\
                                              SRSS_PWR_HIBERNATE_MASK_HIBPIN_Msk))

/** The define to update the token to indicate the transition into Hibernate */
#define HIBERNATE_TOKEN                    ((uint32_t) 0x1BU << SRSS_PWR_HIBERNATE_TOKEN_Pos)

/* The wait time for transition into the minimum regulator current mode
*/
#define SET_MIN_CURRENT_MODE_DELAY_US        (1U)

/* The wait delay time that occurs before the active reference is settled.
*  Intermediate delay is used in transition into the normal regulator current
*  mode
*/
#define ACT_REF_SETTLE_DELAY_US              (6U)

/* The wait delay time that occurs after the active reference is settled.
*  Final delay is used in transition into the normal regulator current mode
*/
#define SET_NORMAL_CURRENT_MODE_DELAY_US     (1U)

/* The internal define of the tries number in the
* Cy_SysPm_SystemSetMinRegulatorCurrent() function
*/
#define WAIT_DELAY_TRIES                (100U)

/* The internal define of the tries number in the
* Cy_SysPm_SystemSetMinRegulatorCurrent() function
*/
#define CY_SYSPM_CBUCK_BUSY_RETRY_COUNT         (100U)
#define CY_SYSPM_CBUCK_BUSY_RETRY_DELAY_MS      (1U)



/*******************************************************************************
*       Internal Variables
*******************************************************************************/

/* Array of the callback roots */
static cy_stc_syspm_callback_t* pmCallbackRoot[CALLBACK_ROOT_NR] = {(void *)0, (void *)0, (void *)0, (void *)0, (void *)0};

/* The array of the pointers to failed callback */
static cy_stc_syspm_callback_t* failedCallback[CALLBACK_ROOT_NR] = {(void *)0, (void *)0, (void *)0, (void *)0, (void *)0};

cy_en_syspm_status_t Cy_SysPm_CpuEnterSleep(cy_en_syspm_waitfor_t waitFor)
{
    uint32_t interruptState;
    uint32_t cbSleepRootIdx = (uint32_t) CY_SYSPM_SLEEP;
    cy_en_syspm_status_t retVal = CY_SYSPM_SUCCESS;

    CY_ASSERT_L3(CY_SYSPM_IS_WAIT_FOR_VALID(waitFor));

    /* Call registered callback functions with CY_SYSPM_CHECK_READY parameter */
    if (pmCallbackRoot[cbSleepRootIdx] != NULL)
    {
        retVal = Cy_SysPm_ExecuteCallback(CY_SYSPM_SLEEP, CY_SYSPM_CHECK_READY);
    }

    /* The CPU can switch into the Sleep power mode only when
    *  all executed registered callback functions with the CY_SYSPM_CHECK_READY
    *  parameter return CY_SYSPM_SUCCESS.
    */
    if(retVal == CY_SYSPM_SUCCESS)
    {
        /* Call the registered callback functions with
        * CY_SYSPM_BEFORE_TRANSITION parameter
        */
        interruptState = Cy_SysLib_EnterCriticalSection();
        if (pmCallbackRoot[cbSleepRootIdx] != NULL)
        {
            (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_SLEEP, CY_SYSPM_BEFORE_TRANSITION);
        }

        /* The CPU enters the Sleep power mode upon execution of WFI/WFE */
        SCB_SCR &= (uint32_t) ~SCB_SCR_SLEEPDEEP_Msk;

        if(waitFor != CY_SYSPM_WAIT_FOR_EVENT)
        {
            __WFI();
        }
        else
        {
            __WFE();
        }
        Cy_SysLib_ExitCriticalSection(interruptState);

        /* Call the registered callback functions with the
        *  CY_SYSPM_AFTER_TRANSITION parameter
        */
        if (pmCallbackRoot[cbSleepRootIdx] != NULL)
        {
            (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_SLEEP, CY_SYSPM_AFTER_TRANSITION);
        }
    }
    else
    {
        /* Execute callback functions with the CY_SYSPM_CHECK_FAIL parameter to
        *  undo everything done in the callback with the CY_SYSPM_CHECK_READY
        *  parameter
        */
        (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_SLEEP, CY_SYSPM_CHECK_FAIL);
        retVal = CY_SYSPM_FAIL;
    }
    return retVal;
}

cy_en_syspm_status_t Cy_SysPm_SystemLpActiveEnter(void)
{
    uint32_t interruptState;
    uint32_t cbSleepRootIdx = (uint32_t)CY_SYSPM_LPACTIVE_ENTER;
    cy_en_syspm_status_t retVal = CY_SYSPM_SUCCESS;

    /* Step-1: Wait until PWR_CTL.LPM_READY==1 to indicate low power circuits are ready. */
    if(!Cy_SysPm_IsLpmReady())
    {
        retVal = CY_SYSPM_FAIL;
    }
    else
    {
        /* Call registered callback functions with CY_SYSPM_CHECK_READY parameter */
        if (pmCallbackRoot[cbSleepRootIdx] != NULL)
        {
            retVal = Cy_SysPm_ExecuteCallback((cy_en_syspm_callback_type_t)cbSleepRootIdx, CY_SYSPM_CHECK_READY);
        }

        if (retVal == CY_SYSPM_SUCCESS)
        {
            /* The CPU can switch into the LPACTIVE power mode only when
            *  all executed registered callback functions with the CY_SYSPM_CHECK_READY
            *  parameter return CY_SYSPM_SUCCESS.
            */
            /* Call the registered callback functions with
            * CY_SYSPM_BEFORE_TRANSITION parameter
            */
            interruptState = Cy_SysLib_EnterCriticalSection();
            if (pmCallbackRoot[cbSleepRootIdx] != NULL)
            {
                (void) Cy_SysPm_ExecuteCallback((cy_en_syspm_callback_type_t)cbSleepRootIdx, CY_SYSPM_BEFORE_TRANSITION); /* Suppress a compiler warning about unused return value */
            }

            /* Configure the low-power operating mode for Linear Core regulator */
            if(Cy_SysPm_LdoIsEnabled())
            {
                SRSS_PWR_CTL2 |= _VAL2FLD(SRSS_PWR_CTL2_BGREF_LPMODE, 1u);
            }

            /* This wait time allows the circuits to remove their dependence on
            *  the Active mode circuits, such as Active Reference
            */
            Cy_SysLib_DelayUs(CY_SYSPM_ACTIVE_TO_LP_WAIT_US);

            Cy_SysLib_ExitCriticalSection(interruptState);

            /* Call the registered callback functions with the
            *  CY_SYSPM_AFTER_TRANSITION parameter
            */
            if (pmCallbackRoot[cbSleepRootIdx] != NULL)
            {
                (void) Cy_SysPm_ExecuteCallback((cy_en_syspm_callback_type_t)cbSleepRootIdx, CY_SYSPM_AFTER_TRANSITION); /* Suppress a compiler warning about unused return value */
            }
        }
        else
        {
            /* Execute callback functions with the CY_SYSPM_CHECK_FAIL parameter to
            *  undo everything done in the callback with the CY_SYSPM_CHECK_READY
            *  parameter
            */
            (void) Cy_SysPm_ExecuteCallback((cy_en_syspm_callback_type_t)cbSleepRootIdx, CY_SYSPM_CHECK_FAIL); /* Suppress a compiler warning about unused return value */
            retVal = CY_SYSPM_FAIL;
        }
    }
    return retVal;
}

cy_en_syspm_status_t Cy_SysPm_SystemLpActiveExit(void)
{
    uint32_t interruptState;
    uint32_t cbSleepRootIdx = (uint32_t)CY_SYSPM_LPACTIVE_EXIT;
    cy_en_syspm_status_t retVal = CY_SYSPM_SUCCESS;

    /* Call registered callback functions with CY_SYSPM_CHECK_READY parameter */
    if (pmCallbackRoot[cbSleepRootIdx] != NULL)
    {
        retVal = Cy_SysPm_ExecuteCallback((cy_en_syspm_callback_type_t)cbSleepRootIdx, CY_SYSPM_CHECK_READY);
    }

    if (retVal == CY_SYSPM_SUCCESS)
    {
        /* The CPU can switch into the LPACTIVE power mode only when
        *  all executed registered callback functions with the CY_SYSPM_CHECK_READY
        *  parameter return CY_SYSPM_SUCCESS.
        */
        /* Call the registered callback functions with
        * CY_SYSPM_BEFORE_TRANSITION parameter
        */
        interruptState = Cy_SysLib_EnterCriticalSection();
        if (pmCallbackRoot[cbSleepRootIdx] != NULL)
        {
            (void) Cy_SysPm_ExecuteCallback((cy_en_syspm_callback_type_t)cbSleepRootIdx, CY_SYSPM_BEFORE_TRANSITION); /* Suppress a compiler warning about unused return value */
        }

        /* This wait time allows setting Active Reference */
        Cy_SysLib_DelayUs(CY_SYSPM_LP_TO_ACTIVE_WAIT_BEFORE_US);

        /* Configure the normal operation mode */
        SRSS_PWR_CTL2 &= ((uint32_t) (~SRSS_PWR_CTL2_BGREF_LPMODE_Msk));

        /* This wait time allows setting Active Reference */
        Cy_SysLib_DelayUs(CY_SYSPM_LP_TO_ACTIVE_WAIT_AFTER_US);

        Cy_SysLib_ExitCriticalSection(interruptState);

        /* Call the registered callback functions with the
        *  CY_SYSPM_AFTER_TRANSITION parameter
        */
        if (pmCallbackRoot[cbSleepRootIdx] != NULL)
        {
            (void) Cy_SysPm_ExecuteCallback((cy_en_syspm_callback_type_t)cbSleepRootIdx, CY_SYSPM_AFTER_TRANSITION); /* Suppress a compiler warning about unused return value */
        }
    }
    else
    {
        /* Execute callback functions with the CY_SYSPM_CHECK_FAIL parameter to
        *  undo everything done in the callback with the CY_SYSPM_CHECK_READY
        *  parameter
        */
        (void) Cy_SysPm_ExecuteCallback((cy_en_syspm_callback_type_t)cbSleepRootIdx, CY_SYSPM_CHECK_FAIL); /* Suppress a compiler warning about unused return value */
        retVal = CY_SYSPM_FAIL;
    }
    return retVal;
}

bool Cy_SysPm_IsSystemLpActiveEnabled(void)
{
    return (_FLD2BOOL(SRSS_PWR_CTL2_BGREF_LPMODE, SRSS_PWR_CTL2)? true : false);
}

cy_en_syspm_status_t Cy_SysPm_CpuEnterDeepSleep(cy_en_syspm_waitfor_t waitFor)
{
    uint32_t interruptState;
    uint32_t cbDeepSleepRootIdx = (uint32_t) CY_SYSPM_DEEPSLEEP;
    cy_en_syspm_status_t retVal = CY_SYSPM_SUCCESS;

    CY_ASSERT_L3(CY_SYSPM_IS_WAIT_FOR_VALID(waitFor));

    //Check if LPM is ready
    if(!Cy_SysPm_IsLpmReady())
    {
        retVal = CY_SYSPM_FAIL;
    }
    else
    {
        /* Call the registered callback functions with the CY_SYSPM_CHECK_READY
        *  parameter
        */
        if (pmCallbackRoot[cbDeepSleepRootIdx] != NULL)
        {
            retVal = Cy_SysPm_ExecuteCallback((cy_en_syspm_callback_type_t)cbDeepSleepRootIdx, CY_SYSPM_CHECK_READY);
        }

        /* The CPU can switch into the Deep Sleep power mode only when
        *  all executed registered callback functions with the CY_SYSPM_CHECK_READY
        *  parameter return CY_SYSPM_SUCCESS
        */
        if (retVal == CY_SYSPM_SUCCESS)
        {
            /* Call the registered callback functions with the
            * CY_SYSPM_BEFORE_TRANSITION parameter
            */
            interruptState = Cy_SysLib_EnterCriticalSection();
            if (pmCallbackRoot[cbDeepSleepRootIdx] != NULL)
            {
                (void) Cy_SysPm_ExecuteCallback((cy_en_syspm_callback_type_t)cbDeepSleepRootIdx, CY_SYSPM_BEFORE_TRANSITION);
            }
                /* The CPU enters Deep Sleep mode upon execution of WFI/WFE
                 * use Cy_SysPm_SetDeepSleepMode to set various deepsleep modes TBD*/
                SCB_SCR |= SCB_SCR_SLEEPDEEP_Msk;

                if(waitFor != CY_SYSPM_WAIT_FOR_EVENT)
                {
                    __WFI();
                }
                else
                {
                    __WFE();
                }

            Cy_SysLib_ExitCriticalSection(interruptState);
        }
        if (retVal == CY_SYSPM_SUCCESS)
        {
            /* Call the registered callback functions with the CY_SYSPM_AFTER_TRANSITION
            *  parameter
            */
            if (pmCallbackRoot[cbDeepSleepRootIdx] != NULL)
            {
                (void) Cy_SysPm_ExecuteCallback((cy_en_syspm_callback_type_t)cbDeepSleepRootIdx, CY_SYSPM_AFTER_TRANSITION);
            }
        }
        else
        {
            /* Execute callback functions with the CY_SYSPM_CHECK_FAIL parameter to
            *  undo everything done in the callback with the CY_SYSPM_CHECK_READY
            *  parameter
            */
            if (pmCallbackRoot[cbDeepSleepRootIdx] != NULL)
            {
                (void) Cy_SysPm_ExecuteCallback((cy_en_syspm_callback_type_t)cbDeepSleepRootIdx, CY_SYSPM_CHECK_FAIL);
            }
        }
    }
    return retVal;
}

cy_en_syspm_status_t Cy_SysPm_SystemEnterHibernate(void)
{
    cy_en_syspm_status_t retVal = CY_SYSPM_SUCCESS;
    uint32_t cbHibernateRootIdx = (uint32_t) CY_SYSPM_HIBERNATE;
    /* Call the registered callback functions with the
    * CY_SYSPM_CHECK_READY parameter
    */
    if (pmCallbackRoot[cbHibernateRootIdx] != NULL)
    {
        retVal = Cy_SysPm_ExecuteCallback(CY_SYSPM_HIBERNATE, CY_SYSPM_CHECK_READY);
    }

    /* The system can switch into Hibernate power mode only when
    *  all executed registered callback functions with CY_SYSPM_CHECK_READY
    *  parameter return CY_SYSPM_SUCCESS.
    */
    if(retVal == CY_SYSPM_SUCCESS)
    {
        /* Call registered callback functions with CY_SYSPM_BEFORE_TRANSITION
        *  parameter
        */
        (void) Cy_SysLib_EnterCriticalSection();
        if (pmCallbackRoot[cbHibernateRootIdx] != NULL)
        {
            (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_HIBERNATE, CY_SYSPM_BEFORE_TRANSITION);
        }

        /* Preserve the token that will be retained through a wakeup sequence.
         * This could be used by Cy_SysLib_GetResetReason() to differentiate
         * Wakeup from a general reset event.
         * Preserve the wakeup source(s) configuration.
         */
        SRSS_PWR_HIBERNATE = (SRSS_PWR_HIBERNATE & HIBERNATE_WAKEUP_MASK) | HIBERNATE_TOKEN;

        /* Disable overriding by the peripherals the next pin-freeze command */
        SRSS_PWR_HIBERNATE |= SET_HIBERNATE_MODE;

        /* The second write causes freezing of I/O cells to save the I/O-cell state */
        SRSS_PWR_HIBERNATE |= SET_HIBERNATE_MODE;

        /* Third write cause system to enter Hibernate */
        SRSS_PWR_HIBERNATE |= SET_HIBERNATE_MODE;

        /* Read register to make sure it is settled */
        (void) SRSS_PWR_HIBERNATE;

        /* Wait for transition */
        __WFI();

        /* The callback function calls with the CY_SYSPM_AFTER_TRANSITION
        * parameter in the Hibernate power mode are not applicable as system
        * wake-up was made on system reboot.
        */

        /* A wakeup from Hibernate is performed by toggling of the wakeup
        * pins, or WDT matches, or Backup domain alarm expires. This depends on
        * what item is configured in the Hibernate register. After a wakeup
        * event, a normal Boot procedure occurs.
        * There is no need to exit from the critical section.
        */
    }
    else
    {
        /* Execute callback functions with the CY_SYSPM_CHECK_FAIL parameter to
        * undo everything done in the callback with the CY_SYSPM_CHECK_READY
        * parameter. The return value should be CY_SYSPM_SUCCESS.
        */
        (void) Cy_SysPm_ExecuteCallback(CY_SYSPM_HIBERNATE, CY_SYSPM_CHECK_FAIL);
        retVal = CY_SYSPM_FAIL;
    }
    return retVal;
}

cy_en_syspm_status_t Cy_SysPm_SystemSetMinRegulatorCurrent(void)
{
    cy_en_syspm_status_t retVal = CY_SYSPM_CANCELED;

    /* Check if the power circuits are ready to enter into regulator minimum
    *  current mode
    */
    if (Cy_SysPm_IsLpmReady())
    {
        SRSS_PWR_CTL2 |= (SRSS_PWR_CTL2_BGREF_LPMODE_Msk);

        /* This wait time allows the circuits to remove their dependence on
        *  the Active mode circuits, such as active Reference
        */
        Cy_SysLib_DelayUs(SET_MIN_CURRENT_MODE_DELAY_US);

        retVal = CY_SYSPM_SUCCESS;
    }

    return retVal;
}

cy_en_syspm_status_t Cy_SysPm_SystemSetNormalRegulatorCurrent(void)
{
    cy_en_syspm_status_t retVal = CY_SYSPM_TIMEOUT;

    /* Disable the low-power for Bandgap reference circuit */
    SRSS_PWR_CTL2 &= (uint32_t) ~SRSS_PWR_CTL2_BGREF_LPMODE_Msk;

    /* This wait time allows setting active Reference */
    Cy_SysLib_DelayUs(ACT_REF_SETTLE_DELAY_US);

    retVal= CY_SYSPM_SUCCESS;

    return retVal;
}

bool Cy_SysPm_IsBgRefCtrl(void)
{
    return (0U != _FLD2VAL(SRSS_PWR_CTL2_BGREF_LPMODE, SRSS_PWR_CTL2));
}

void Cy_SysPm_BgRefCtrl(bool enable)
{
    if(enable)
    {
        SRSS_PWR_CTL2 |= (uint32_t) SRSS_PWR_CTL2_BGREF_LPMODE_Msk;
    }
    else
    {
        SRSS_PWR_CTL2 &= (uint32_t) ~SRSS_PWR_CTL2_BGREF_LPMODE_Msk;
    }
}

cy_en_syspm_status_t Cy_SysPm_LdoSetMode(cy_en_syspm_ldo_mode_t mode)
{
    CY_ASSERT_L3(CY_SYSPM_IS_LDO_MODE_VALID(mode));

    cy_en_syspm_status_t retVal = CY_SYSPM_CANCELED;

    switch (mode)
    {
        case CY_SYSPM_LDO_MODE_NORMAL:
        {
            retVal = Cy_SysPm_SystemSetNormalRegulatorCurrent();
        }
        break;

        case CY_SYSPM_LDO_MODE_MIN:
        {
            retVal = Cy_SysPm_SystemSetMinRegulatorCurrent();
        }
        break;

        case CY_SYSPM_LDO_MODE_DISABLED:
        {
            /* Disable the LDO, Deep Sleep, nWell, and Retention regulators */
            SRSS_PWR_CTL2 |= (_VAL2FLD(SRSS_PWR_CTL2_DPSLP_REG_DIS, 1U) |
                             _VAL2FLD(SRSS_PWR_CTL2_LINREG_DIS, 1U));

            retVal = CY_SYSPM_SUCCESS;
        }
        break;

        default:
            retVal = CY_SYSPM_FAIL;
        break;
    }

    return retVal;
}

cy_en_syspm_ldo_mode_t Cy_SysPm_LdoGetMode(void)
{
    cy_en_syspm_ldo_mode_t retVal;

    if (!Cy_SysPm_LdoIsEnabled())
    {
        retVal = CY_SYSPM_LDO_MODE_DISABLED;
    }
    else if (Cy_SysPm_SystemIsMinRegulatorCurrentSet())
    {
        retVal = CY_SYSPM_LDO_MODE_MIN;
    }
    else
    {
        retVal = CY_SYSPM_LDO_MODE_NORMAL;
    }

    return retVal;
}

bool Cy_SysPm_LdoIsEnabled(void)
{
    return ((0U != _FLD2VAL(SRSS_PWR_CTL2_LINREG_DIS, SRSS_PWR_CTL2)) ? false : true);
}


void Cy_SysPm_CpuSleepOnExit(bool enable)
{
    if(enable)
    {
        /* Enable sleep-on-exit feature */
        SCB_SCR |= SCB_SCR_SLEEPONEXIT_Msk;
    }
    else
    {
        /* Disable sleep-on-exit feature */
        SCB_SCR &= (uint32_t) ~(SCB_SCR_SLEEPONEXIT_Msk);
    }
}

void Cy_SysPm_SetHibernateWakeupSource(uint32_t wakeupSource)
{
    CY_ASSERT_L3(CY_SYSPM_IS_WAKE_UP_SOURCE_VALID(wakeupSource));

    uint32_t polarityMask = 0U;

    if (0U != _FLD2VAL(SRSS_PWR_HIBERNATE_POLARITY_HIBPIN, wakeupSource))
    {
        /* Reconfigure the wakeup pins and LPComp polarity based on the input */
        if (0U != (wakeupSource & CY_SYSPM_HIB_WAKEUP_LPCOMP0_MASK))
        {
            polarityMask |= CY_SYSPM_HIB_WAKEUP_LPCOMP0_POLARITY_HIGH_MASK;
        }

        if (0U != (wakeupSource & CY_SYSPM_HIB_WAKEUP_LPCOMP1_MASK))
        {
            polarityMask |= CY_SYSPM_HIB_WAKEUP_LPCOMP1_POLARITY_HIGH_MASK;
        }

        if (0U != (wakeupSource & CY_SYSPM_HIB_WAKEUP_PIN0_MASK))
        {
            polarityMask |= CY_SYSPM_HIB_WAKEUP_PIN0_POLARITY_HIGH_MASK;
        }

        if (0U != (wakeupSource & CY_SYSPM_HIB_WAKEUP_PIN1_MASK))
        {
            polarityMask |= CY_SYSPM_HIB_WAKEUP_PIN1_POLARITY_HIGH_MASK;
        }
    }

    SRSS_PWR_HIBERNATE = (SRSS_PWR_HIBERNATE & (uint32_t) ~polarityMask) | wakeupSource;

    /* Read register to make sure it is settled */
    (void) SRSS_PWR_HIBERNATE;
}

void Cy_SysPm_ClearHibernateWakeupSource(uint32_t wakeupSource)
{
    CY_ASSERT_L3(CY_SYSPM_IS_WAKE_UP_SOURCE_VALID(wakeupSource));

    uint32_t clearWakeupSourceMask = wakeupSource & (uint32_t) ~SRSS_PWR_HIBERNATE_POLARITY_HIBPIN_Msk;

    if (0U != _FLD2VAL(SRSS_PWR_HIBERNATE_POLARITY_HIBPIN, wakeupSource))
    {
        /* Clear the high active level of the requested sources */
        if ((uint32_t) CY_SYSPM_HIBERNATE_LPCOMP0_HIGH == (wakeupSource & (uint32_t) CY_SYSPM_HIBERNATE_LPCOMP0_HIGH))
        {
            clearWakeupSourceMask |= CY_SYSPM_HIB_WAKEUP_LPCOMP0_POLARITY_HIGH_MASK;
        }

        if ((uint32_t) CY_SYSPM_HIBERNATE_LPCOMP1_HIGH == (wakeupSource & (uint32_t) CY_SYSPM_HIBERNATE_LPCOMP1_HIGH))
        {
            clearWakeupSourceMask |= CY_SYSPM_HIB_WAKEUP_LPCOMP1_POLARITY_HIGH_MASK;
        }

        if ((uint32_t) CY_SYSPM_HIBERNATE_PIN0_HIGH == (wakeupSource & (uint32_t) CY_SYSPM_HIBERNATE_PIN0_HIGH))
        {
            clearWakeupSourceMask |= CY_SYSPM_HIB_WAKEUP_PIN0_POLARITY_HIGH_MASK;
        }

        if ((uint32_t) CY_SYSPM_HIBERNATE_PIN1_HIGH == (wakeupSource & (uint32_t) CY_SYSPM_HIBERNATE_PIN1_HIGH))
        {
            clearWakeupSourceMask |= CY_SYSPM_HIB_WAKEUP_PIN1_POLARITY_HIGH_MASK;
        }
    }

    SRSS_PWR_HIBERNATE &= (uint32_t) ~clearWakeupSourceMask;

    /* Read register to make sure it is settled */
    (void) SRSS_PWR_HIBERNATE;
}

bool Cy_SysPm_RegisterCallback(cy_stc_syspm_callback_t* handler)
{
    bool retVal = false;

    /* Verify the input parameters. */
    if ((handler != NULL) && (handler->callbackParams != NULL) && (handler->callback != NULL))
    {
        uint32_t callbackRootIdx = (uint32_t) handler->type;

        /* If the callback list is not empty. */
        if (pmCallbackRoot[callbackRootIdx] != NULL)
        {
            cy_stc_syspm_callback_t* curCallback = pmCallbackRoot[callbackRootIdx];
            cy_stc_syspm_callback_t* insertPos  = curCallback;

            /* Find the callback after which the new callback is to be
             * inserted. Ensure the given callback has not been registered.
             */
            while ((NULL != curCallback->nextItm) && (curCallback != handler))
            {
                curCallback = curCallback->nextItm;
                /* Callbacks with the same order value are stored in the order
                 * they are registered.
                 */
                if (curCallback->order <= handler->order)
                {
                    insertPos = curCallback;
                }
            }
            /* If the callback has not been registered. */
            if (curCallback != handler)
            {
                /* If the callback is to be inserted at the beginning of the list. */
                if ((insertPos->prevItm == NULL) && (handler->order < insertPos->order))
                {
                    handler->nextItm = insertPos;
                    handler->prevItm = NULL;
                    handler->nextItm->prevItm = handler;
                    pmCallbackRoot[callbackRootIdx] = handler;
                }
                else
                {
                    handler->nextItm = insertPos->nextItm;
                    handler->prevItm = insertPos;

                    /* If the callback is not inserted at the end of the list. */
                    if (handler->nextItm != NULL)
                    {
                        handler->nextItm->prevItm = handler;
                    }
                    insertPos->nextItm = handler;
                }
                retVal = true;
            }
        }
        else
        {
            /* The callback list is empty. */
            pmCallbackRoot[callbackRootIdx] = handler;
            handler->nextItm = NULL;
            handler->prevItm = NULL;
            retVal = true;
        }
    }
    return retVal;
}

bool Cy_SysPm_UnregisterCallback(cy_stc_syspm_callback_t const *handler)
{
    bool retVal = false;

    if (handler != NULL)
    {
        uint32_t callbackRootIdx = (uint32_t) handler->type;
        cy_stc_syspm_callback_t* curCallback = pmCallbackRoot[callbackRootIdx];

        /* Search requested callback item in the linked list */
        while (curCallback != NULL)
        {
            /* Requested callback is found */
            if (curCallback == handler)
            {
                retVal = true;
                break;
            }

            /* Go to next callback item in the linked list */
            curCallback = curCallback->nextItm;
        }

        if (retVal)
        {
            /* Requested callback is first in the list */
            if (pmCallbackRoot[callbackRootIdx] == handler)
            {
                /* Check whether this the only callback registered */
                if (pmCallbackRoot[callbackRootIdx]->nextItm != NULL)
                {
                    pmCallbackRoot[callbackRootIdx] = pmCallbackRoot[callbackRootIdx]->nextItm;
                    pmCallbackRoot[callbackRootIdx]->prevItm = NULL;
                }
                else
                {
                    /* We had only one callback */
                    pmCallbackRoot[callbackRootIdx] = NULL;
                }
            }
            else
            {
                /* Update links of related to unregistered callback items */
                curCallback->prevItm->nextItm = curCallback->nextItm;

                if (curCallback->nextItm != NULL)
                {
                    curCallback->nextItm->prevItm = curCallback->prevItm;
                }
            }
        }
    }

    return retVal;
}

cy_en_syspm_status_t Cy_SysPm_ExecuteCallback(cy_en_syspm_callback_type_t type, cy_en_syspm_callback_mode_t mode)
{
    CY_ASSERT_L3(CY_SYSPM_IS_CALLBACK_TYPE_VALID(type));
    CY_ASSERT_L3(CY_SYSPM_IS_CALLBACK_MODE_VALID(mode));

    static cy_stc_syspm_callback_t* lastExecutedCallback = NULL;
    cy_en_syspm_status_t retVal = CY_SYSPM_SUCCESS;
    cy_stc_syspm_callback_t* curCallback = pmCallbackRoot[(uint32_t) type];
    cy_stc_syspm_callback_params_t curParams;

    if ((mode == CY_SYSPM_BEFORE_TRANSITION) || (mode == CY_SYSPM_CHECK_READY))
    {
        /* Execute registered callbacks with order from first registered to the
        *  last registered. Stop executing if CY_SYSPM_FAIL was returned in
        *  CY_SYSPM_CHECK_READY mode
        */
        while ((curCallback != NULL) && ((retVal != CY_SYSPM_FAIL) || (mode != CY_SYSPM_CHECK_READY)))
        {
            /* The modes defined in the .skipMode element are not executed */
            if (0UL == ((uint32_t) mode & curCallback->skipMode))
            {
                /* Update elements for local callback parameter values */
                curParams.base = curCallback->callbackParams->base;
                curParams.context = curCallback->callbackParams->context;

                retVal = curCallback->callback(&curParams, mode);

                /* Update callback pointer with value of executed callback.
                * Such update is required to execute further callbacks in
                * backward order after exit from LP mode or to undo
                * configuration after callback returned fail: from last called
                * to first registered.
                */
                lastExecutedCallback = curCallback;
            }
            curCallback = curCallback->nextItm;
        }

        if (mode == CY_SYSPM_CHECK_READY)
        {
            /* Update the pointer to  the failed callback with the result of the callback execution.
            *  If the callback fails, the value of the pointer will be updated
            *  with the address of the callback which returned CY_SYSPM_FAIL, else,
            *  it will be updated with NULL.
            */
            if(retVal == CY_SYSPM_FAIL)
            {
                failedCallback[(uint32_t) type] = lastExecutedCallback;
            }
            else
            {
                failedCallback[(uint32_t) type] = NULL;
            }
        }
    }
    else
    {
        /* Execute registered callbacks with order from lastCallback or last
        * executed to the first registered callback. Such a flow is required if
        * a previous callback function returned CY_SYSPM_FAIL or a previous
        * callback mode was CY_SYSPM_BEFORE_TRANSITION. Such an order is
        * required to undo configurations in correct backward order.
        */
        if (mode != CY_SYSPM_CHECK_FAIL)
        {
            while (curCallback->nextItm != NULL)
            {
                curCallback = curCallback->nextItm;
            }
        }
        else
        {
            /* Skip last executed callback that returns CY_SYSPM_FAIL, as this
            *  callback already knows that it failed.
            */
            curCallback = lastExecutedCallback;

            if (curCallback != NULL)
            {
                curCallback = curCallback->prevItm;
            }
        }

        /* Execute callback functions with required type and mode */
        while (curCallback != NULL)
        {
            /* The modes defined in the .skipMode element are not executed */
            if (0UL == ((uint32_t) mode & curCallback->skipMode))
            {
                /* Update elements for local callback parameter values */
                curParams.base = curCallback->callbackParams->base;
                curParams.context = curCallback->callbackParams->context;

                retVal = curCallback->callback(&curParams, mode);
            }
            curCallback = curCallback->prevItm;
        }
    }

    return retVal;
}

cy_stc_syspm_callback_t* Cy_SysPm_GetFailedCallback(cy_en_syspm_callback_type_t type)
{
    return failedCallback[(uint32_t) type];
}

/*******************************************************************************
* Function Name: Cy_SysPm_IoFreeze
****************************************************************************//**
*
* Freezes IOs.
*
* Freezes the IO cells directly to save the IO-cell state on a wakeup from the
* Hibernate. Do not call this function before entering the
* Hibernate mode, because Cy_SysPm_Hibernate() function freezes the IO cells.
*
******************************************************************************/
void Cy_SysPm_IoFreeze(void)
{
    uint32_t interruptState;
    uint32_t regValue;

    interruptState = Cy_SysLib_EnterCriticalSection();

    /* Check the FREEZE state to avoid a recurrent IO-cells freeze attempt,
    * because the second call to this function will cause an accidental switch
    * to the hibernate mode (the system will enter the hibernate mode immediately
    * after writing to the hibernate bit because both UNLOCK and FREEZE were set
    * correctly in the previous call to this function).
    */
    if(!Cy_SysPm_IoIsFrozen())
    {
        /* Clear the unlock field for correct freeze of the IO cells */
        SRSS_PWR_HIBERNATE = _CLR_SET_FLD32U((SRSS_PWR_HIBERNATE), SRSS_PWR_HIBERNATE_UNLOCK, 0u);

        /* Disable overriding by the peripherals the next pin-freeze command */
        SRSS_PWR_HIBERNATE |=  CY_SYSPM_PWR_HIBERNATE_UNLOCK |
                                _VAL2FLD(SRSS_PWR_HIBERNATE_FREEZE, 1u) |
                                _VAL2FLD(SRSS_PWR_HIBERNATE_HIBERNATE, 1u);

        /* If Read is after Write, read this register two times to delay
        *  enough time for internal settling.
        */
        (void) SRSS_PWR_HIBERNATE;
        (void) SRSS_PWR_HIBERNATE;

        /* The second Write causes freeze of IO cells to save the IO-cell state */
        regValue = SRSS_PWR_HIBERNATE;
        SRSS_PWR_HIBERNATE = regValue;
    }
    Cy_SysLib_ExitCriticalSection(interruptState);
}

void Cy_SysPm_IoUnfreeze(void)
{
    uint32_t interruptState;
    interruptState = Cy_SysLib_EnterCriticalSection();

    /* Preserve the last reset reason and wakeup polarity. Then, unfreeze I/O:
     * write PWR_HIBERNATE.FREEZE=0, .UNLOCK=0x3A, .HIBERANTE=0
     */
    SRSS_PWR_HIBERNATE = (SRSS_PWR_HIBERNATE & HIBERNATE_RETAIN_STATUS_MASK) | HIBERNATE_UNLOCK_VAL;

    /* Lock the Hibernate mode:
    * write PWR_HIBERNATE.HIBERNATE=0, UNLOCK=0x00, HIBERANTE=0
    */
    SRSS_PWR_HIBERNATE &= HIBERNATE_RETAIN_STATUS_MASK;

    /* Read register to make sure it is settled */
    (void) SRSS_PWR_HIBERNATE;

    Cy_SysLib_ExitCriticalSection(interruptState);
}

bool Cy_SysPm_IoIsFrozen(void)
{
    return (0U != _FLD2VAL(SRSS_PWR_HIBERNATE_FREEZE, SRSS_PWR_HIBERNATE));
}

void Cy_SysPm_CpuSendWakeupEvent(void)
{
    __SEV();
}

bool Cy_SysPm_IsLpmReady(void)
{
    return (_FLD2BOOL(SRSS_PWR_CTL_LPM_READY, SRSS_PWR_CTL)? true : false);
}

void Cy_SysPm_BackupSetSupply(cy_en_syspm_vddbackup_control_t vddBackControl)
{
    CY_UNUSED_PARAMETER(vddBackControl);

#if (SRSS_BACKUP_VBCK_PRESENT)
    CY_ASSERT_L3(CY_SYSPM_IS_VDDBACKUP_VALID(vddBackControl));

    BACKUP_CTL = _CLR_SET_FLD32U((BACKUP_CTL), BACKUP_CTL_VDDBAK_CTL, (uint32_t) vddBackControl);
#endif
}


cy_en_syspm_vddbackup_control_t Cy_SysPm_BackupGetSupply(void)
{
#if (SRSS_BACKUP_VBCK_PRESENT)
    uint32_t retVal;
    retVal = _FLD2VAL(BACKUP_CTL_VDDBAK_CTL, BACKUP_CTL);

    return ((cy_en_syspm_vddbackup_control_t) retVal);
#else
    return (CY_SYSPM_VDDBACKUP_DEFAULT);
#endif
}


void Cy_SysPm_BackupEnableVoltageMeasurement(void)
{
#if (SRSS_BACKUP_VBCK_PRESENT)
    BACKUP_CTL |= BACKUP_CTL_VBACKUP_MEAS_Msk;
#endif
}


void Cy_SysPm_BackupDisableVoltageMeasurement(void)
{
#if (SRSS_BACKUP_VBCK_PRESENT)
    BACKUP_CTL &= ((uint32_t) ~BACKUP_CTL_VBACKUP_MEAS_Msk);
#endif
}


void Cy_SysPm_BackupSuperCapCharge(cy_en_syspm_sc_charge_key_t key)
{
    CY_UNUSED_PARAMETER(key);

#if (SRSS_BACKUP_VBCK_PRESENT)
    CY_ASSERT_L3(CY_SYSPM_IS_SC_CHARGE_KEY_VALID(key));

    if(key == CY_SYSPM_SC_CHARGE_ENABLE)
    {
        BACKUP_CTL = _CLR_SET_FLD32U((BACKUP_CTL), BACKUP_CTL_EN_CHARGE_KEY, (uint32_t) CY_SYSPM_SC_CHARGE_ENABLE);
    }
    else
    {
        BACKUP_CTL &= ((uint32_t) ~BACKUP_CTL_EN_CHARGE_KEY_Msk);
    }
#endif
}

void Cy_SysPm_BackupWordStore(uint32_t wordIndex, uint32_t *wordSrcPointer, uint32_t wordSize)
{
    CY_ASSERT_L3(CY_SYSPM_IS_WORD_INDEX_VALID(wordIndex));
    CY_ASSERT_L3(CY_SYSPM_IS_WORD_SIZE_VALID(wordSize + wordIndex));

    while(wordSize != 0UL)
    {
        BACKUP_BREG[wordIndex] = *wordSrcPointer;

        wordIndex++;
        wordSrcPointer++;
        wordSize--;
    }
}

void Cy_SysPm_BackupWordReStore(uint32_t wordIndex, uint32_t *wordDstPointer, uint32_t wordSize)
{
    CY_ASSERT_L3(CY_SYSPM_IS_WORD_INDEX_VALID(wordIndex));
    CY_ASSERT_L3(CY_SYSPM_IS_WORD_SIZE_VALID(wordSize + wordIndex));

    while(wordSize != 0UL)
    {
        *wordDstPointer = BACKUP_BREG[wordIndex];

        wordIndex++;
        wordDstPointer++;
        wordSize--;
    }
}

cy_en_syspm_status_t Cy_SysPm_SetSRAMMacroPwrMode(cy_en_syspm_sram_index_t sramNum, uint32_t sramMacroNum, cy_en_syspm_sram_pwr_mode_t sramPwrMode)
{
    cy_en_syspm_status_t status = CY_SYSPM_BAD_PARAM;

    CY_ASSERT_L1( sramNum < CPUSS_SRAM_COUNT );

    if(sramNum == CY_SYSPM_SRAM0_MEMORY)
    {
        CY_ASSERT_L1( sramMacroNum < CPUSS_RAMC0_MACRO_NR );
        if (sramMacroNum < CPUSS_RAMC0_MACRO_NR)
        {
            CPUSS_RAM0_PWR_MACRO_CTL(sramMacroNum) = _VAL2FLD(CPUSS_RAM0_PWR_MACRO_CTL_VECTKEYSTAT, CY_SYSPM_PWR_MACRO_CTL_WRITE_KEY) |
                                                _VAL2FLD(CPUSS_RAM0_PWR_MACRO_CTL_PWR_MODE, sramPwrMode);
            status = CY_SYSPM_SUCCESS;
        }
    }
    else if(sramNum == CY_SYSPM_SRAM1_MEMORY)
    {
        CY_ASSERT_L1( CPUSS_RAMC1_PRESENT );
        CY_ASSERT_L1( sramMacroNum == 0UL );

        CPUSS_RAM1_PWR_CTL = _VAL2FLD(CPUSS_RAM1_PWR_CTL_VECTKEYSTAT, CY_SYSPM_PWR_MACRO_CTL_WRITE_KEY) |
                                    _VAL2FLD(CPUSS_RAM1_PWR_CTL_PWR_MODE, sramPwrMode);
        status = CY_SYSPM_SUCCESS;
    }
    else if(sramNum == CY_SYSPM_SRAM2_MEMORY)
    {
        CY_ASSERT_L1( CPUSS_RAMC2_PRESENT );
        CY_ASSERT_L1( sramMacroNum == 0UL );

        CPUSS_RAM2_PWR_CTL = _VAL2FLD(CPUSS_RAM2_PWR_CTL_VECTKEYSTAT, CY_SYSPM_PWR_MACRO_CTL_WRITE_KEY) |
                                    _VAL2FLD(CPUSS_RAM2_PWR_CTL_PWR_MODE, sramPwrMode);
        status = CY_SYSPM_SUCCESS;
    }
    else
    {
        /* Invalid SRAM Number */
    }

    return status;
}


cy_en_syspm_sram_pwr_mode_t Cy_SysPm_GetSRAMMacroPwrMode(cy_en_syspm_sram_index_t sramNum, uint32_t sramMacroNum)
{
    uint32_t retVal = (uint32_t)CY_SYSPM_SRAM_PWR_MODE_INVALID;

    CY_ASSERT_L1( sramNum < CPUSS_SRAM_COUNT );

    if(sramNum == CY_SYSPM_SRAM0_MEMORY)
    {
        CY_ASSERT_L1( sramMacroNum < CPUSS_RAMC0_MACRO_NR );
        if (sramMacroNum < CPUSS_RAMC0_MACRO_NR)
        {
            retVal = _FLD2VAL(CPUSS_RAM0_PWR_MACRO_CTL_PWR_MODE, CPUSS_RAM0_PWR_MACRO_CTL(sramMacroNum));
        }
    }
    else if(sramNum == CY_SYSPM_SRAM1_MEMORY)
    {
        CY_ASSERT_L1( sramMacroNum == 0UL );
        retVal = _FLD2VAL(CPUSS_RAM1_PWR_CTL_PWR_MODE, CPUSS_RAM1_PWR_CTL);
    }
    else if(sramNum == CY_SYSPM_SRAM2_MEMORY)
    {
        CY_ASSERT_L1( sramMacroNum == 0UL );
        retVal = _FLD2VAL(CPUSS_RAM2_PWR_CTL_PWR_MODE, CPUSS_RAM2_PWR_CTL);
    }
    else
    {
        /* Invalid SRAM Number */
    }
    return (cy_en_syspm_sram_pwr_mode_t)retVal;
}


cy_en_syspm_status_t Cy_SysPm_SetSRAMPwrMode(cy_en_syspm_sram_index_t sramNum, cy_en_syspm_sram_pwr_mode_t sramPwrMode)
{
    uint32 idx;

    cy_en_syspm_status_t status = CY_SYSPM_BAD_PARAM;
    CY_ASSERT_L1( sramNum < CPUSS_SRAM_COUNT );

    if(sramNum == CY_SYSPM_SRAM0_MEMORY)
    {
        for(idx = 0UL; idx < CPUSS_RAMC0_MACRO_NR; idx++)
        {
            CPUSS_RAM0_PWR_MACRO_CTL(idx) = _VAL2FLD(CPUSS_RAM0_PWR_MACRO_CTL_VECTKEYSTAT, CY_SYSPM_PWR_MACRO_CTL_WRITE_KEY) |
                                        _VAL2FLD(CPUSS_RAM0_PWR_MACRO_CTL_PWR_MODE, sramPwrMode);
        }
        status = CY_SYSPM_SUCCESS;
    }
    else if(sramNum == CY_SYSPM_SRAM1_MEMORY)
    {
        CY_ASSERT_L1( CPUSS_RAMC1_PRESENT );
        CPUSS_RAM1_PWR_CTL = _VAL2FLD(CPUSS_RAM1_PWR_CTL_VECTKEYSTAT, CY_SYSPM_PWR_MACRO_CTL_WRITE_KEY) |
                                        _VAL2FLD(CPUSS_RAM1_PWR_CTL_PWR_MODE, sramPwrMode);
        status = CY_SYSPM_SUCCESS;

    }
    else if(sramNum == CY_SYSPM_SRAM2_MEMORY)
    {
        CY_ASSERT_L1( CPUSS_RAMC2_PRESENT );
        CPUSS_RAM2_PWR_CTL = _VAL2FLD(CPUSS_RAM2_PWR_CTL_VECTKEYSTAT, CY_SYSPM_PWR_MACRO_CTL_WRITE_KEY) |
                                        _VAL2FLD(CPUSS_RAM2_PWR_CTL_PWR_MODE, sramPwrMode);
        status = CY_SYSPM_SUCCESS;

    }
    else
    {
        /* Invalid SRAM Number */
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_SysPm_ReadStatus
****************************************************************************//**
*
* Reads the status of the core(s).
*
* \return The current power mode. See \ref group_syspm_return_status.
*
*******************************************************************************/
uint32_t Cy_SysPm_ReadStatus(void)
{
    uint32_t interruptState;
    uint32_t pmStatus = 0u;
    interruptState = Cy_SysLib_EnterCriticalSection();

    /* Check whether CM7_0 is in the deep sleep mode*/
    if((0u != _FLD2VAL(CPUSS_CM7_0_STATUS_SLEEPING, CPUSS_CM7_0_STATUS)) &&
       (0u != _FLD2VAL(CPUSS_CM7_0_STATUS_SLEEPDEEP, CPUSS_CM7_0_STATUS)))
    {
        pmStatus |= CY_SYSPM_STATUS_CM7_0_DEEPSLEEP;
    }
    /* Check whether CM7_0 is in the sleep mode*/
    else if(0u != _FLD2VAL(CPUSS_CM7_0_STATUS_SLEEPING, CPUSS_CM7_0_STATUS))
    {
        pmStatus |= CY_SYSPM_STATUS_CM7_0_SLEEP;
    }
    else
    {
        pmStatus |= CY_SYSPM_STATUS_CM7_0_ACTIVE;
    }

    /* Check whether CM7_1 is in the deep sleep mode*/
    if((0u != _FLD2VAL(CPUSS_CM7_1_STATUS_SLEEPING, CPUSS_CM7_1_STATUS)) &&
       (0u != _FLD2VAL(CPUSS_CM7_1_STATUS_SLEEPDEEP, CPUSS_CM7_1_STATUS)))
    {
        pmStatus |= CY_SYSPM_STATUS_CM7_1_DEEPSLEEP;
    }
    /* Check whether CM7_1 is in the sleep mode*/
    else if(0u != _FLD2VAL(CPUSS_CM7_1_STATUS_SLEEPING, CPUSS_CM7_1_STATUS))
    {
        pmStatus |= CY_SYSPM_STATUS_CM7_1_SLEEP;
    }
    else
    {
        pmStatus |= CY_SYSPM_STATUS_CM7_1_ACTIVE;
    }


    /* Check whether CM0p is in the deep sleep mode*/
    if((0u != _FLD2VAL(CPUSS_CM0_STATUS_SLEEPING, CPUSS_CM0_STATUS)) &&
       (0u != _FLD2VAL(CPUSS_CM0_STATUS_SLEEPDEEP, CPUSS_CM0_STATUS)))
    {
        pmStatus |= (uint32_t) CY_SYSPM_STATUS_CM0_DEEPSLEEP;
    }
    /* Check whether CM0p is in the sleep mode*/
    else if (0u != _FLD2VAL(CPUSS_CM0_STATUS_SLEEPING, CPUSS_CM0_STATUS))
    {
        pmStatus |= CY_SYSPM_STATUS_CM0_SLEEP;
    }
    else
    {
        pmStatus |= CY_SYSPM_STATUS_CM0_ACTIVE;
    }

    /* Check whether the device is in LPACTIVE mode or not */
    if(Cy_SysPm_IsSystemLpActiveEnabled())
    {
        pmStatus |= CY_SYSPM_STATUS_SYSTEM_LOWPOWER;
    }

    Cy_SysLib_ExitCriticalSection(interruptState);

    return(pmStatus);
}

bool Cy_SysPm_Cm7IsActive(uint8_t core)
{
    bool status = false;

    if(core == CORE_CM7_0)
    {
        status = ((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_CM7_0_ACTIVE) != 0u);
    }
    else if(core == CORE_CM7_1)
    {
        status = ((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_CM7_1_ACTIVE) != 0u);
    }
    else
    {
        /* CM7 Not active */
    }

    return status;
}

bool Cy_SysPm_Cm7IsSleep(uint8_t core)
{
    bool status = false;

    if(core == CORE_CM7_0)
    {
        status = ((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_CM7_0_SLEEP) != 0u);
    }
    else if(core == CORE_CM7_1)
    {
        status = ((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_CM7_1_SLEEP) != 0u);
    }
    else
    {
        /* CM7 Not active */
    }

    return status;
}

bool Cy_SysPm_Cm7IsDeepSleep(uint8_t core)
{
    bool status = false;

    if(core == CORE_CM7_0)
    {
        status = ((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_CM7_0_DEEPSLEEP) != 0u);
    }
    else if(core == CORE_CM7_1)
    {
        status = ((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_CM7_1_DEEPSLEEP) != 0u);
    }
    else
    {
        /* CM7 Not active */
    }

    return status;
}

bool Cy_SysPm_Cm7IsLowPower(uint8_t core)
{
    bool status = false;

    if(core == CORE_CM7_0)
    {
        return((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_CM7_0_LOWPOWER) != 0u);
    }
    else if(core == CORE_CM7_1)
    {
        return((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_CM7_1_LOWPOWER) != 0u);
    }
    else
    {
        /* CM7 Not active */
    }

    return status;
}

bool Cy_SysPm_Cm0IsActive(void)
{
    return((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_CM0_ACTIVE) != 0u);
}

bool Cy_SysPm_Cm0IsSleep(void)
{
    return((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_CM0_SLEEP) != 0u);
}

bool Cy_SysPm_Cm0IsDeepSleep(void)
{
    return((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_CM0_DEEPSLEEP) != 0u);
}

bool Cy_SysPm_Cm0IsLowPower(void)
{
    return((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_CM0_LOWPOWER) != 0u);
}

bool Cy_SysPm_IsSystemLp(void)
{
    return((Cy_SysPm_ReadStatus() & CY_SYSPM_STATUS_SYSTEM_LOWPOWER) != 0u);
}


void Cy_SysPm_PmicEnable(void)
{
    if(CY_SYSPM_PMIC_UNLOCK_KEY == _FLD2VAL(BACKUP_PMIC_CTL_UNLOCK, BACKUP_PMIC_CTL))
    {
        BACKUP_PMIC_CTL =
        _VAL2FLD(BACKUP_PMIC_CTL_UNLOCK, CY_SYSPM_PMIC_UNLOCK_KEY) |
        _VAL2FLD(BACKUP_PMIC_CTL_PMIC_EN_OUTEN, 1u) |
        _VAL2FLD(BACKUP_PMIC_CTL_PMIC_EN, 1u);
    }
}


void Cy_SysPm_PmicDisable(cy_en_syspm_pmic_wakeup_polarity_t polarity)
{
    if(CY_SYSPM_PMIC_UNLOCK_KEY == _FLD2VAL(BACKUP_PMIC_CTL_UNLOCK, BACKUP_PMIC_CTL))
    {
        BACKUP_PMIC_CTL =
        (_VAL2FLD(BACKUP_PMIC_CTL_UNLOCK, CY_SYSPM_PMIC_UNLOCK_KEY) |
         _CLR_SET_FLD32U(BACKUP_PMIC_CTL, BACKUP_PMIC_CTL_POLARITY, polarity)) &
        ((uint32_t) ~ _VAL2FLD(BACKUP_PMIC_CTL_PMIC_EN, 1u));
    }
}


void Cy_SysPm_PmicAlwaysEnable(void)
{
    BACKUP_PMIC_CTL |= _VAL2FLD(BACKUP_PMIC_CTL_PMIC_ALWAYSEN, 1u);
}


void Cy_SysPm_PmicEnableOutput(void)
{
    if(CY_SYSPM_PMIC_UNLOCK_KEY == _FLD2VAL(BACKUP_PMIC_CTL_UNLOCK, BACKUP_PMIC_CTL))
    {
        BACKUP_PMIC_CTL |=
        _VAL2FLD(BACKUP_PMIC_CTL_UNLOCK, CY_SYSPM_PMIC_UNLOCK_KEY) | _VAL2FLD(BACKUP_PMIC_CTL_PMIC_EN_OUTEN, 1u);
    }
}


void Cy_SysPm_PmicDisableOutput(void)
{
    if(CY_SYSPM_PMIC_UNLOCK_KEY == _FLD2VAL(BACKUP_PMIC_CTL_UNLOCK, BACKUP_PMIC_CTL))
    {
        BACKUP_PMIC_CTL =
        (BACKUP_PMIC_CTL | _VAL2FLD(BACKUP_PMIC_CTL_UNLOCK, CY_SYSPM_PMIC_UNLOCK_KEY)) &
        ((uint32_t) ~ _VAL2FLD(BACKUP_PMIC_CTL_PMIC_EN_OUTEN, 1u));
    }
}


void Cy_SysPm_PmicLock(void)
{
    BACKUP_PMIC_CTL = _CLR_SET_FLD32U(BACKUP_PMIC_CTL, BACKUP_PMIC_CTL_UNLOCK, 0u);
}


void Cy_SysPm_PmicUnlock(void)
{
    BACKUP_PMIC_CTL = _CLR_SET_FLD32U(BACKUP_PMIC_CTL, BACKUP_PMIC_CTL_UNLOCK, CY_SYSPM_PMIC_UNLOCK_KEY);
}


bool Cy_SysPm_PmicIsEnabled(void)
{
    return(0u != _FLD2VAL(BACKUP_PMIC_CTL_PMIC_EN, BACKUP_PMIC_CTL));
}


bool Cy_SysPm_PmicIsOutputEnabled(void)
{
    return (0U != _FLD2VAL(BACKUP_PMIC_CTL_PMIC_EN_OUTEN, BACKUP_PMIC_CTL));
}


bool Cy_SysPm_PmicIsLocked(void)
{
    return((_FLD2VAL(BACKUP_PMIC_CTL_UNLOCK, BACKUP_PMIC_CTL) == CY_SYSPM_PMIC_UNLOCK_KEY) ? false : true);
}

void Cy_SysPm_OvdEnable(cy_en_syspm_ovd_sel_t ovdSel)
{
    switch(ovdSel)
    {
    case CY_SYSPM_OVD_ON_VDDD:
      SRSS_PWR_SSV_CTL |= SRSS_PWR_SSV_CTL_OVDVDDD_ENABLE_Msk;
      break;

    case CY_SYSPM_OVD_ON_VDDA:
      SRSS_PWR_SSV_CTL |= SRSS_PWR_SSV_CTL_OVDVDDA_ENABLE_Msk;
      break;

    case CY_SYSPM_OVD_ON_VCCD:
      SRSS_PWR_SSV_CTL |= SRSS_PWR_SSV_CTL_OVDVCCD_ENABLE_Msk;
      break;

    default:
      (void)SRSS_PWR_SSV_STATUS; /* To Fix Coverity */
      break;
    }
}


void Cy_SysPm_OvdDisable(cy_en_syspm_ovd_sel_t ovdSel)
{
    switch(ovdSel)
    {
    case CY_SYSPM_OVD_ON_VDDD:
      SRSS_PWR_SSV_CTL &= (uint32_t) ~SRSS_PWR_SSV_CTL_OVDVDDD_ENABLE_Msk;
      break;

    case CY_SYSPM_OVD_ON_VDDA:
      SRSS_PWR_SSV_CTL &= (uint32_t) ~SRSS_PWR_SSV_CTL_OVDVDDA_ENABLE_Msk;
      break;

    case CY_SYSPM_OVD_ON_VCCD:
      SRSS_PWR_SSV_CTL &= (uint32_t) ~SRSS_PWR_SSV_CTL_OVDVCCD_ENABLE_Msk;
      break;

    default:
      (void)SRSS_PWR_SSV_STATUS; /* To Fix Coverity */
      break;
    }
}


void Cy_SysPm_OvdVdddSelect(cy_en_syspm_ovd_vddd_sel_t ovdVdddSel)
{
    SRSS_PWR_SSV_CTL = _CLR_SET_FLD32U(SRSS_PWR_SSV_CTL, SRSS_PWR_SSV_CTL_OVDVDDD_VSEL, ovdVdddSel);
}


void Cy_SysPm_OvdVddaSelect(cy_en_syspm_ovd_vdda_sel_t ovdVddaSel)
{
    SRSS_PWR_SSV_CTL = _CLR_SET_FLD32U(SRSS_PWR_SSV_CTL, SRSS_PWR_SSV_CTL_OVDVDDA_VSEL, ovdVddaSel);
}


void Cy_SysPm_OvdActionSelect(cy_en_syspm_ovd_action_select_t ovdActionSelect)
{
    CY_ASSERT(CY_OVD_CHECK_ACTION_CFG(ovdActionSelect));

    SRSS_PWR_SSV_CTL = _CLR_SET_FLD32U(SRSS_PWR_SSV_CTL, SRSS_PWR_SSV_CTL_OVDVDDA_ACTION, ovdActionSelect);
}


void Cy_SysPm_BodEnable(cy_en_syspm_bod_sel_t bodSel)
{
    switch(bodSel)
    {
    case CY_SYSPM_BOD_ON_VDDD:
      SRSS_PWR_SSV_CTL |= SRSS_PWR_SSV_CTL_BODVDDD_ENABLE_Msk;
      break;

    case CY_SYSPM_BOD_ON_VDDA:
      SRSS_PWR_SSV_CTL |= SRSS_PWR_SSV_CTL_BODVDDA_ENABLE_Msk;
      break;

    case CY_SYSPM_BOD_ON_VCCD:
      SRSS_PWR_SSV_CTL |= SRSS_PWR_SSV_CTL_BODVCCD_ENABLE_Msk;
      break;

    default:
      (void)SRSS_PWR_SSV_STATUS; /* To Fix Coverity */
      break;
    }
}


void Cy_SysPm_BodDisable(cy_en_syspm_bod_sel_t bodSel)
{
    switch(bodSel)
    {
    case CY_SYSPM_BOD_ON_VDDD:
      SRSS_PWR_SSV_CTL &= (uint32_t) ~SRSS_PWR_SSV_CTL_BODVDDD_ENABLE_Msk;
      break;

    case CY_SYSPM_BOD_ON_VDDA:
      SRSS_PWR_SSV_CTL &= (uint32_t) ~SRSS_PWR_SSV_CTL_BODVDDA_ENABLE_Msk;
      break;

    case CY_SYSPM_BOD_ON_VCCD:
      SRSS_PWR_SSV_CTL &= (uint32_t) ~SRSS_PWR_SSV_CTL_BODVCCD_ENABLE_Msk;
      break;

    default:
      (void)SRSS_PWR_SSV_STATUS; /* To Fix Coverity */
      break;
    }
}


void Cy_SysPm_BodVdddSelect(cy_en_syspm_bod_vddd_sel_t bodVdddSel)
{
    SRSS_PWR_SSV_CTL = _CLR_SET_FLD32U(SRSS_PWR_SSV_CTL, SRSS_PWR_SSV_CTL_BODVDDD_VSEL, bodVdddSel);
}


void Cy_SysPm_BodVddaSelect(cy_en_syspm_bod_vdda_sel_t bodVddaSel)
{
    SRSS_PWR_SSV_CTL = _CLR_SET_FLD32U(SRSS_PWR_SSV_CTL, SRSS_PWR_SSV_CTL_BODVDDA_VSEL, bodVddaSel);
}


void Cy_SysPm_BodActionSelect(cy_en_syspm_bod_action_select_t bodActionSelect)
{
    CY_ASSERT(CY_BOD_CHECK_ACTION_CFG(bodActionSelect));

    SRSS_PWR_SSV_CTL = _CLR_SET_FLD32U(SRSS_PWR_SSV_CTL, SRSS_PWR_SSV_CTL_BODVDDA_ACTION, bodActionSelect);
}


bool Cy_SysPm_SupplySupervisionStatus(cy_en_syspm_supply_entity_select_t supplyEntitySelect)
{
    bool returnStatus = false;

    CY_ASSERT_L3(CY_OVD_CHECK_SUPPLY_ENTITY(supplyEntitySelect));

    switch(supplyEntitySelect)
    {
    case CY_SYSPM_ENTITY_BOD_VDDD:
      returnStatus = (0u != _FLD2VAL(SRSS_PWR_SSV_STATUS_BODVDDD_OK, SRSS_PWR_SSV_STATUS));
      break;

    case CY_SYSPM_ENTITY_BOD_VDDA:
      returnStatus = (0u != _FLD2VAL(SRSS_PWR_SSV_STATUS_BODVDDA_OK, SRSS_PWR_SSV_STATUS));
      break;

    case CY_SYSPM_ENTITY_BOD_VCCD:
      returnStatus = (0u != _FLD2VAL(SRSS_PWR_SSV_STATUS_BODVCCD_OK, SRSS_PWR_SSV_STATUS));
      break;

    case CY_SYSPM_ENTITY_OVD_VDDD:
      returnStatus = (0u != _FLD2VAL(SRSS_PWR_SSV_STATUS_OVDVDDD_OK, SRSS_PWR_SSV_STATUS));
      break;

    case CY_SYSPM_ENTITY_OVD_VDDA:
      returnStatus = (0u != _FLD2VAL(SRSS_PWR_SSV_STATUS_OVDVDDA_OK, SRSS_PWR_SSV_STATUS));
      break;

    case CY_SYSPM_ENTITY_OVD_VCCD:
      returnStatus = (0u != _FLD2VAL(SRSS_PWR_SSV_STATUS_OVDVCCD_OK, SRSS_PWR_SSV_STATUS));
      break;

    default:
      (void)SRSS_PWR_SSV_STATUS; /* To Fix Coverity */
      break;
    }

    return (returnStatus);
}

bool Cy_SysPm_SystemIsMinRegulatorCurrentSet(void)
{
    uint32_t regMask = Cy_SysPm_LdoIsEnabled() ? CY_SYSPM_PWR_CIRCUITS_LPMODE_ACTIVE_LDO_MASK : CY_SYSPM_PWR_CIRCUITS_LPMODE_ACTIVE_BUCK_MASK;

    return ((SRSS_PWR_CTL & regMask) == regMask);
}

void Cy_SysPm_LinearRegDisable(void)
{
    SRSS_PWR_CTL2 |= SRSS_PWR_CTL2_LINREG_DIS_Msk;
}

void Cy_SysPm_LinearRegEnable(void)
{
    SRSS_PWR_CTL2 &= (uint32_t) ~SRSS_PWR_CTL2_LINREG_DIS_Msk;
}

bool Cy_SysPm_LinearRegGetStatus(void)
{
    return (_FLD2BOOL(SRSS_PWR_CTL2_LINREG_OK, SRSS_PWR_CTL2));
}

void Cy_SysPm_DeepSleepRegDisable(void)
{
    SRSS_PWR_CTL2 |= SRSS_PWR_CTL2_DPSLP_REG_DIS_Msk;
}

void Cy_SysPm_DeepSleepRegEnable(void)
{
    SRSS_PWR_CTL2 &= (uint32_t) ~SRSS_PWR_CTL2_DPSLP_REG_DIS_Msk;
}

bool Cy_SySPm_IsDeepSleepRegEnabled(void)
{
    return(0u == _FLD2VAL(SRSS_PWR_CTL2_DPSLP_REG_DIS, SRSS_PWR_CTL2));
}

void Cy_SysPm_ReghcSelectMode(cy_en_syspm_reghc_mode_t mode)
{
    CY_REG32_CLR_SET(SRSS_PWR_REGHC_CTL, SRSS_PWR_REGHC_CTL_REGHC_MODE, mode);
}

cy_en_syspm_reghc_mode_t Cy_SysPm_ReghcGetMode(void)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to cy_en_syspm_reghc_mode_t enum.');
    return (cy_en_syspm_reghc_mode_t)(_FLD2VAL(SRSS_PWR_REGHC_CTL_REGHC_MODE, SRSS_PWR_REGHC_CTL));
}

void Cy_SysPm_ReghcSelectDriveOut(cy_en_syspm_reghc_drive_out_t drvOut)
{
    CY_REG32_CLR_SET(SRSS_PWR_REGHC_CTL, SRSS_PWR_REGHC_CTL_REGHC_PMIC_DRV_VOUT, drvOut);
}

cy_en_syspm_reghc_drive_out_t Cy_SysPm_ReghcGetDriveOut(void)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to cy_en_syspm_reghc_drive_out_t enum.');
    return (cy_en_syspm_reghc_drive_out_t)(_FLD2VAL(SRSS_PWR_REGHC_CTL_REGHC_PMIC_DRV_VOUT, SRSS_PWR_REGHC_CTL));
}

void Cy_SysPm_ReghcAdjustOutputVoltage(cy_en_syspm_reghc_vadj_t trim)
{
    CY_REG32_CLR_SET(SRSS_PWR_REGHC_CTL, SRSS_PWR_REGHC_CTL_REGHC_VADJ, trim);
}

void Cy_SysPm_ReghcDisableIntSupplyWhileExtActive(void)
{
    SRSS_PWR_REGHC_CTL &= (uint32_t) ~SRSS_PWR_REGHC_CTL_REGHC_PMIC_USE_LINREG_Msk;
}

void Cy_SysPm_ReghcEnableIntSupplyWhileExtActive(void)
{
    SRSS_PWR_REGHC_CTL |= SRSS_PWR_REGHC_CTL_REGHC_PMIC_USE_LINREG_Msk;
}


void Cy_SysPm_ReghcDisablePmicEnableOutput(void)
{
    SRSS_PWR_REGHC_CTL &= (uint32_t) ~SRSS_PWR_REGHC_CTL_REGHC_PMIC_CTL_OUTEN_Msk;
    SRSS_PWR_REGHC_CTL &= (uint32_t) ~SRSS_PWR_REGHC_CTL_REGHC_PMIC_CTL_POLARITY_Msk;
}

void Cy_SysPm_ReghcEnablePmicEnableOutput(bool polarity)
{
    SRSS_PWR_REGHC_CTL |= SRSS_PWR_REGHC_CTL_REGHC_PMIC_CTL_OUTEN_Msk;

    if(polarity)
    {
        SRSS_PWR_REGHC_CTL |= SRSS_PWR_REGHC_CTL_REGHC_PMIC_CTL_POLARITY_Msk;
    }
    else
    {
        SRSS_PWR_REGHC_CTL &= (uint32_t) ~SRSS_PWR_REGHC_CTL_REGHC_PMIC_CTL_POLARITY_Msk;
    }
}

void Cy_SysPm_ReghcEnablePmicStatusInput(bool polarity)
{
    SRSS_PWR_REGHC_CTL |= SRSS_PWR_REGHC_CTL_REGHC_PMIC_STATUS_INEN_Msk;

    if(polarity)
    {
        SRSS_PWR_REGHC_CTL |= SRSS_PWR_REGHC_CTL_REGHC_PMIC_STATUS_POLARITY_Msk;
    }
    else
    {
        SRSS_PWR_REGHC_CTL &= (uint32_t) ~SRSS_PWR_REGHC_CTL_REGHC_PMIC_STATUS_POLARITY_Msk;
    }

}

void Cy_SysPm_ReghcDisablePmicStatusInput(void)
{
    SRSS_PWR_REGHC_CTL &= (uint32_t) ~SRSS_PWR_REGHC_CTL_REGHC_PMIC_STATUS_INEN_Msk;
}

void Cy_SysPm_ReghcSetPmicStatusWaitTime(uint16_t waitTime)
{
    CY_REG32_CLR_SET(SRSS_PWR_REGHC_CTL, SRSS_PWR_REGHC_CTL_REGHC_PMIC_STATUS_WAIT, waitTime);
}

bool Cy_SysPm_ReghcIsConfigured(void)
{
    return (_FLD2BOOL(SRSS_PWR_REGHC_CTL_REGHC_CONFIGURED, SRSS_PWR_REGHC_CTL));
}

void Cy_SysPm_ReghcSetConfigured(void)
{
    SRSS_PWR_REGHC_CTL |= SRSS_PWR_REGHC_CTL_REGHC_CONFIGURED_Msk;
}

void Cy_SysPm_ReghcDisable(void)
{
    SRSS_PWR_REGHC_CTL2 &= (uint32_t) ~SRSS_PWR_REGHC_CTL2_REGHC_EN_Msk;
}

void Cy_SysPm_ReghcEnable(void)
{
    SRSS_PWR_REGHC_CTL2 |= SRSS_PWR_REGHC_CTL2_REGHC_EN_Msk;
}

void Cy_SysPm_ReghcDisablePmicStatusTimeout(void)
{
    SRSS_PWR_REGHC_CTL2 &= (uint32_t) ~SRSS_PWR_REGHC_CTL2_REGHC_PMIC_STATUS_TIMEOUT_Msk;
}

void Cy_SysPm_ReghcEnablePmicStatusTimeout(uint8_t timeout)
{
    CY_REG32_CLR_SET(SRSS_PWR_REGHC_CTL2, SRSS_PWR_REGHC_CTL2_REGHC_PMIC_STATUS_TIMEOUT, timeout);
}

bool Cy_SysPm_ReghcIsEnabled(void)
{
    return (_FLD2BOOL(SRSS_PWR_REGHC_STATUS_REGHC_ENABLED, SRSS_PWR_REGHC_STATUS));
}

bool Cy_SysPm_ReghcIsStatusOk(void)
{
    return (_FLD2BOOL(SRSS_PWR_REGHC_STATUS_REGHC_PMIC_STATUS_OK, SRSS_PWR_REGHC_STATUS));
}

bool Cy_SysPm_ReghcIsSequencerBusy(void)
{
    return (_FLD2BOOL(SRSS_PWR_REGHC_STATUS_REGHC_SEQ_BUSY, SRSS_PWR_REGHC_STATUS));
}

void Cy_SysPm_ReghcDisableVAdj(void)
{
    SRSS_PWR_REGHC_CTL4 |= SRSS_PWR_REGHC_CTL4_REGHC_PMIC_VADJ_DIS_Msk;
}

void Cy_SysPm_ReghcEnableVAdj(void)
{
    SRSS_PWR_REGHC_CTL4 &= (uint32_t) ~SRSS_PWR_REGHC_CTL4_REGHC_PMIC_VADJ_DIS_Msk;
}

void Cy_SysPm_ReghcDisablePmicInDeepSleep(void)
{
    SRSS_PWR_REGHC_CTL4 &= (uint32_t) ~SRSS_PWR_REGHC_CTL4_REGHC_PMIC_DPSLP_Msk;
}

void Cy_SysPm_ReghcEnablePmicInDeepSleep(void)
{
    SRSS_PWR_REGHC_CTL4 |= SRSS_PWR_REGHC_CTL4_REGHC_PMIC_DPSLP_Msk;
}

bool Cy_SysPm_ReghcIsOcdWithinLimits(void)
{
    return (_FLD2BOOL(SRSS_PWR_REGHC_STATUS_REGHC_OCD_OK, SRSS_PWR_REGHC_STATUS));
}

bool Cy_SysPm_ReghcIsCircuitEnabledAndOperating(void)
{
    return (_FLD2BOOL(SRSS_PWR_REGHC_STATUS_REGHC_CKT_OK, SRSS_PWR_REGHC_STATUS));
}


#endif /* (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3) */

/* [] END OF FILE */
