/***************************************************************************//**
* \file cy_wdt.c
* \version 1.50
*
*  This file provides the source code to the API for the WDT driver.
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

#if defined (CY_IP_MXS28SRSS)|| defined (CY_IP_MXS40SSRSS ) || defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3) || defined (CY_IP_MXS22SRSS )

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
* The WDT match value is 4096.
* None of ignore bits are set: the whole WDT counter bits are checked against
* the match value.
*
* \sideeffect
* This function clears the WDT interrupt.
*
*******************************************************************************/
void Cy_WDT_Init(void)
{
    /* Unlock the WDT by two writes */
    SRSS_WDT_CTL = ((SRSS_WDT_CTL & (uint32_t)(~SRSS_WDT_CTL_WDT_LOCK_Msk)) | CY_SRSS_WDT_LOCK_BIT0);
    SRSS_WDT_CTL |= CY_SRSS_WDT_LOCK_BIT1;

    Cy_WDT_Disable();
    Cy_WDT_SetMatch(CY_SRSS_WDT_DEFAULT_MATCH_VALUE);
    Cy_WDT_SetIgnoreBits(CY_SRSS_WDT_DEFAULT_IGNORE_BITS);
    Cy_WDT_ClearInterrupt();
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
    SRSS_WDT_CTL |= _VAL2FLD(SRSS_WDT_CTL_WDT_LOCK, CY_SRSS_WDT_LOCK_BITS);
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
    return (0u != _FLD2VAL(SRSS_WDT_CTL_WDT_LOCK, SRSS_WDT_CTL));
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
    SRSS_WDT_CTL = ((SRSS_WDT_CTL & (uint32_t)(~SRSS_WDT_CTL_WDT_LOCK_Msk)) | CY_SRSS_WDT_LOCK_BIT0);

    SRSS_WDT_CTL |= CY_SRSS_WDT_LOCK_BIT1;
}


/*******************************************************************************
* Function Name: Cy_WDT_SetMatch
****************************************************************************//**
*
* Configures the WDT counter match comparison value. The Watchdog timer
* should be unlocked before changing the match value. Call the Cy_WDT_Unlock()
* function to unlock the WDT.
*
* \param match
* The valid valid range is [0-65535]. The value to be used to match
* against the counter.
*
*******************************************************************************/
void Cy_WDT_SetMatch(uint32_t match)
{
    CY_ASSERT_L2(CY_WDT_IS_MATCH_VAL_VALID(match));

    if (false == Cy_WDT_Locked())
    {
        SRSS_WDT_MATCH = _CLR_SET_FLD32U((SRSS_WDT_MATCH), SRSS_WDT_MATCH_MATCH, match);
    }
}

/*******************************************************************************
* Function Name: Cy_WDT_SetIgnoreBits
****************************************************************************//**
*
* Configures the number of the most significant bits of the Watchdog timer that
* are not checked against the match. Unlock the Watchdog timer before
* ignoring the bits setting. Call the Cy_WDT_Unlock() API to unlock the WDT.
*
* \param bitsNum
* The number of the most significant bits. The valid range is [0-15].
* The bitsNum over 12 are considered as 12.
*
* \details The value of bitsNum controls the time-to-reset of the Watchdog timer
* This happens after 3 successive matches.
*
* \warning This function changes the WDT interrupt period, therefore
* the device can go into an infinite WDT reset loop. This may happen
* if a WDT reset occurs faster that a device start-up.
*
*******************************************************************************/
void Cy_WDT_SetIgnoreBits(uint32_t bitsNum)
{
    CY_ASSERT_L1(CY_WDT_IS_IGNORE_BITS_VALID(bitsNum));
    (void)bitsNum;

    if (false == Cy_WDT_Locked())
    {
#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS)
        SRSS_WDT_MATCH2 = _CLR_SET_FLD32U((SRSS_WDT_MATCH2), SRSS_WDT_MATCH2_IGNORE_BITS_ABOVE, (WDT_MAX_IGNORE_BITS - bitsNum));
#else
        SRSS_WDT_MATCH = _CLR_SET_FLD32U((SRSS_WDT_MATCH), SRSS_WDT_MATCH_IGNORE_BITS, bitsNum);
#endif
    }
}


#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_WDT_SetMatchBits
****************************************************************************//**
*
* Configures the bit position above which the bits will be ignored for match.
*
* \param bitPos
* The bit position above which the match should be ignored.
*
* \details The value of bitPos controls the time-to-reset of the Watchdog timer
* This happens after 3 successive matches.
*
* \warning This function changes the WDT interrupt period, therefore
* the device can go into an infinite WDT reset loop. This may happen
* if a WDT reset occurs faster that a device start-up.
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
void Cy_WDT_SetMatchBits(uint32_t bitPos)
{
    CY_ASSERT_L2(CY_WDT_IS_IGNORE_BITS_ABOVE_VALID(bitPos));
    (void)bitPos;

    if (false == Cy_WDT_Locked())
    {
        SRSS_WDT_MATCH2 = _CLR_SET_FLD32U((SRSS_WDT_MATCH2), SRSS_WDT_MATCH2_IGNORE_BITS_ABOVE, bitPos);
    }
}
#endif

/*******************************************************************************
* Function Name: Cy_WDT_ClearInterrupt
****************************************************************************//**
*
* Clears the WDT match flag which is set every time the WDT counter reaches a
* WDT match value. Two unserviced interrupts lead to a system reset
* (i.e. at the third match).
*
*******************************************************************************/
void Cy_WDT_ClearInterrupt(void)
{
    #if CY_CPU_CORTEX_M4 && defined(CY_DEVICE_SECURE)
        CY_PRA_REG32_SET(CY_PRA_INDX_SRSS_SRSS_INTR, _VAL2FLD(SRSS_SRSS_INTR_WDT_MATCH, 1U));
    #else
        SRSS_SRSS_INTR = _VAL2FLD(SRSS_SRSS_INTR_WDT_MATCH, 1U);
    #endif

    /* Read the interrupt register to ensure that the initial clearing write has
    * been flushed out to the hardware.
    */
    (void) SRSS_SRSS_INTR;
}


/*******************************************************************************
* Function Name: Cy_WDT_ClearWatchdog
****************************************************************************//**
*
* Clears ("feeds") the watchdog, to prevent a XRES device reset.
* This function simply call Cy_WDT_ClearInterrupt() function.
*
*******************************************************************************/
void Cy_WDT_ClearWatchdog(void)
{
    Cy_WDT_ClearInterrupt();
}

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXS28SRSS, CY_IP_MXS40SRSS */

/* [] END OF FILE */
