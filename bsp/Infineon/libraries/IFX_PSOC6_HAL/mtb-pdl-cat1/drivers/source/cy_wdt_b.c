/***************************************************************************//**
* \file cy_wdt_b.c
* \version 1.50
*
*  This file provides the source code to the API for the WDT version B driver.
*
********************************************************************************
* \copyright
* Copyright 2016-2020 Cypress Semiconductor Corporation
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

#if defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)

#include "cy_wdt.h"

#if defined(__cplusplus)
extern "C" {
#endif


/*******************************************************************************
* Function Name: Cy_WDT_Init
****************************************************************************//**
*
* Initializes the Watchdog timer to its default state.
*
* The given default setting of the WDT:
* The WDT is unlocked and disabled.
* The WDT Lower Limit value is set to 0 and Lower action to None.
* The WDT Warn Limit value is set to 0 and Warn action to None.
* The WDT Upper Limit value is set to 32000 (1 second) and Upper action to Reset.
* The WDT is locked again.
*
*******************************************************************************/
void Cy_WDT_Init(void)
{
    /* Unlock the WDT registers by two writes */
    Cy_WDT_Unlock();

    Cy_WDT_Disable();
    /* Set upper limit = 32000 (1sec) */
    Cy_WDT_SetLowerLimit(CY_WDT_DEFAULT_LOWER_LIMIT);
    Cy_WDT_SetUpperLimit(CY_WDT_DEFAULT_UPPER_LIMIT);
    Cy_WDT_SetWarnLimit(CY_WDT_DEFAULT_WARN_LIMIT);
    Cy_WDT_SetLowerAction(CY_WDT_LOW_UPPER_LIMIT_ACTION_NONE);
    Cy_WDT_SetUpperAction(CY_WDT_LOW_UPPER_LIMIT_ACTION_RESET);
    Cy_WDT_SetWarnAction(CY_WDT_WARN_ACTION_NONE);

    /* Lock the WDT registers */
    Cy_WDT_Lock();
}

/*******************************************************************************
* Function Name: Cy_WDT_Lock
****************************************************************************//**
*
* Locks out configuration changes to the Watchdog Timer register.
*
* After this function is called, the WDT configuration cannot be changed until
* Cy_WDT_Unlock() is called.
*
* \warning
* The WDT lock state is not retained during system Deep Sleep. After the wakeup
* from system Deep Sleep the WDT is locked.
*
*******************************************************************************/
void Cy_WDT_Lock(void)
{
    SRSS_WDT_LOCK |= _VAL2FLD(WDT_LOCK_WDT_LOCK, CY_SRSS_WDT_LOCK_BITS);
}


/*******************************************************************************
* Function Name: Cy_WDT_Locked
****************************************************************************//**
*
* Returns the WDT lock state.
*
* \return
* True - if WDT is locked.
* False - if WDT is unlocked.
*
*******************************************************************************/
bool Cy_WDT_Locked(void)
{
    /* Prohibits writing to the WDT registers and other CLK_LF */
    return (0u != _FLD2VAL(WDT_LOCK_WDT_LOCK, SRSS_WDT_LOCK));
}


/*******************************************************************************
* Function Name: Cy_WDT_Unlock
****************************************************************************//**
*
* Unlocks the Watchdog Timer configuration register.
*
* \warning
* The WDT lock state is not retained during system Deep Sleep. After the wakeup
* from system Deep Sleep the WDT is locked.
*
*******************************************************************************/
void Cy_WDT_Unlock(void)
{
    /* The WDT lock is to be removed by two writes */
    SRSS_WDT_LOCK = ((SRSS_WDT_LOCK & (uint32_t)(~WDT_LOCK_WDT_LOCK_Msk)) | CY_SRSS_WDT_LOCK_BIT0);

    SRSS_WDT_LOCK |= CY_SRSS_WDT_LOCK_BIT1;
}

/*******************************************************************************
* Function Name: Cy_WDT_ClearInterrupt
****************************************************************************//**
*
* Clears the WDT match flag which is set as configured by WDT action and limits.
*
*******************************************************************************/
void Cy_WDT_ClearInterrupt(void)
{
    SRSS_WDT_INTR = _VAL2FLD(WDT_INTR_WDT, 1U);

    /* Read the interrupt register to ensure that the initial clearing write has
    * been flushed out to the hardware.
    */
    (void) SRSS_WDT_INTR;
}

/*******************************************************************************
* Function Name: Cy_WDT_ClearWatchdog
****************************************************************************//**
*
* Clears ("feeds") the watchdog, to prevent a XRES device reset.
* This function simply call Cy_WDT_SetService() function.
*
*******************************************************************************/
void Cy_WDT_ClearWatchdog(void)
{
    Cy_WDT_Unlock();
    Cy_WDT_SetService();
    Cy_WDT_Lock();
}

/*******************************************************************************
* Function Name: Cy_WDT_SetLowerLimit
****************************************************************************//**
*
* Set lower limit for watchdog.
*
* \param match - Value to be matched
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_WDT_SetLowerLimit(uint32_t match)
{
    SRSS_WDT_LOWER_LIMIT = match;
}

/*******************************************************************************
* Function Name: Cy_WDT_SetUpperLimit
****************************************************************************//**
*
* Set upper limit for watchdog.
*
* \param match - Value to be matched
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_WDT_SetUpperLimit(uint32_t match)
{
    SRSS_WDT_UPPER_LIMIT = match;
}

/*******************************************************************************
* Function Name: Cy_WDT_SetWarnLimit
****************************************************************************//**
*
* Set warn limit for watchdog.
*
* \param match - Value to be matched
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_WDT_SetWarnLimit(uint32_t match)
{
    SRSS_WDT_WARN_LIMIT = match;
}

/*******************************************************************************
* Function Name: Cy_WDT_SetLowerAction
****************************************************************************//**
*
* Set action taken if this watchdog is serviced before LOWER_LIMIT is reached.
*
* \param action
* \ref cy_en_wdt_lower_upper_action_t
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_WDT_SetLowerAction(cy_en_wdt_lower_upper_action_t action)
{
    CY_REG32_CLR_SET(SRSS_WDT_CONFIG, WDT_CONFIG_LOWER_ACTION, action);
}

/*******************************************************************************
* Function Name: Cy_WDT_SetUpperAction
****************************************************************************//**
*
* Set action taken if this watchdog is not serviced before UPPER_LIMIT is reached.
*
* \param action
* \ref cy_en_wdt_lower_upper_action_t
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_WDT_SetUpperAction(cy_en_wdt_lower_upper_action_t action)
{
    CY_REG32_CLR_SET(SRSS_WDT_CONFIG, WDT_CONFIG_UPPER_ACTION, action);
}

/*******************************************************************************
* Function Name: Cy_WDT_SetWarnAction
****************************************************************************//**
*
* Set action taken when the count value reaches WARN_LIMIT.
*
* \param action
* \ref cy_en_wdt_warn_action_t
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_WDT_SetWarnAction(cy_en_wdt_warn_action_t action)
{
    CY_REG32_CLR_SET(SRSS_WDT_CONFIG, WDT_CONFIG_WARN_ACTION, action);
}

/*******************************************************************************
* Function Name: Cy_WDT_SetAutoService
****************************************************************************//**
*
* Set automatically service when the count value reaches WARN_LIMIT.
* This function is used for WARN_LIMIT.
*
* \param enable
* \ref cy_en_wdt_enable_t
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_WDT_SetAutoService(cy_en_wdt_enable_t enable)
{
    CY_REG32_CLR_SET(SRSS_WDT_CONFIG, WDT_CONFIG_AUTO_SERVICE, enable);
}

/*******************************************************************************
* Function Name: Cy_WDT_SetDeepSleepPause
****************************************************************************//**
*
* Set whether the WDT counter runs/pauses when the system is in DEEPSLEEP.
*
* \param enable
* \ref cy_en_wdt_enable_t
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_WDT_SetDeepSleepPause(cy_en_wdt_enable_t enable)
{
    CY_REG32_CLR_SET(SRSS_WDT_CONFIG, WDT_CONFIG_DPSLP_PAUSE, enable);
}

/*******************************************************************************
* Function Name: Cy_WDT_SetHibarnatePause
****************************************************************************//**
*
* Set whether the WDT counter runs/pauses when the system is in HIBERNATE.
*
* \param enable
* \ref cy_en_wdt_enable_t
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_WDT_SetHibernatePause(cy_en_wdt_enable_t enable)
{
    CY_REG32_CLR_SET(SRSS_WDT_CONFIG, WDT_CONFIG_HIB_PAUSE, enable);
}

/*******************************************************************************
* Function Name: Cy_WDT_SetDebugRun
****************************************************************************//**
*
* Set the debug run value. It needs when using debugger.
*
* \param enable
* \ref cy_en_wdt_enable_t
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_WDT_SetDebugRun(cy_en_wdt_enable_t enable)
{
    CY_REG32_CLR_SET(SRSS_WDT_CONFIG, WDT_CONFIG_DEBUG_RUN, enable);
}

/*******************************************************************************
* Function Name: Cy_WDT_SetService
****************************************************************************//**
*
* Set service of the watchdog. This resets the count value to zero.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_WDT_SetService(void)
{
    SRSS_WDT_SERVICE = WDT_SERVICE_SERVICE_Msk;
}

#if defined(__cplusplus)
}
#endif

#endif /* */

/* [] END OF FILE */
