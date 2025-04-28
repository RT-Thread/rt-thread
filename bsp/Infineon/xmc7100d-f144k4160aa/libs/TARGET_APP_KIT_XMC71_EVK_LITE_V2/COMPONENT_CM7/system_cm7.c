/***************************************************************************//**
* \file system_cm7.c
* \version 1.2
*
* The device system-source file.
*
********************************************************************************
* \copyright
* Copyright 2021-2024 Cypress Semiconductor Corporation
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

#include <stdbool.h>
#include "cy_device.h"
#include "cy_device_headers.h"
#include "cy_syslib.h"
#include "cy_sysclk.h"
#include "cy_wdt.h"


void Cy_DefaultUserHandler(void);

#define DEFAULT_HANDLER_NAME                            Cy_DefaultUserHandler

CY_NOINIT cy_israddress Cy_SystemIrqUserTable[CPUSS_SYSTEM_INT_NR] ;

CY_NOINIT cy_israddress * Cy_SysInt_SystemIrqUserTableRamPointer ;


/*******************************************************************************
* SystemCoreClockUpdate()
*******************************************************************************/

/** Default HFClk frequency in Hz */
#define CY_CLK_HFCLK0_FREQ_HZ_DEFAULT       (8000000UL)

/** Default PeriClk frequency in Hz */
#define CY_CLK_PERICLK_FREQ_HZ_DEFAULT      (8000000UL)

/** Default system core frequency in Hz */
#define CY_CLK_SYSTEM_FREQ_HZ_DEFAULT       (8000000UL)

/** Holds the CLK_SLOW(Cortex-M0+) or CLK_FAST0(Cortex-M7_0) or CLK_FAST(Cortex-M7_1) system core clock */
CY_NOINIT uint32_t SystemCoreClock ;

/** Holds the HFClk0 clock frequency. Updated by \ref SystemCoreClockUpdate().  Note that the HfClk0 does not source any CPU core directly. */
CY_NOINIT uint32_t cy_Hfclk0FreqHz ;

/** Holds the PeriClk clock frequency. Updated by \ref SystemCoreClockUpdate(). */
CY_NOINIT uint32_t cy_PeriClkFreqHz ;

/** Holds the AHB frequency. Updated by \ref SystemCoreClockUpdate(). */
CY_NOINIT uint32_t cy_AhbFreqHz ;

/*******************************************************************************
* SystemCoreClockUpdate (void)
*******************************************************************************/

/* Do not use these definitions directly in your application */
#define CY_DELAY_MS_OVERFLOW_THRESHOLD  (0x8000u)
#define CY_DELAY_1K_THRESHOLD           (1000u)
#define CY_DELAY_1K_MINUS_1_THRESHOLD   (CY_DELAY_1K_THRESHOLD - 1u)
#define CY_DELAY_1M_THRESHOLD           (1000000u)
#define CY_DELAY_1M_MINUS_1_THRESHOLD   (CY_DELAY_1M_THRESHOLD - 1u)

CY_NOINIT uint32_t cy_delayFreqHz ;

CY_NOINIT uint32_t cy_delayFreqKhz ;

CY_NOINIT uint32_t cy_delayFreqMhz ;


/*******************************************************************************
* Function Name: SystemInit
****************************************************************************//**
* \cond
* Initializes the system:
* - Unlocks and disables WDT.
* - Calls the Cy_SystemInit() function.
* - Calls \ref SystemCoreClockUpdate().
* \endcond
*******************************************************************************/
void SystemInit(void)
{

    /* if CM0+ is not enabled then unlock and disable WDT */
#ifdef __CM0P_PRESENT
    #if (__CM0P_PRESENT == 0)

    /* Release reset for all groups IP except group 0 */
    (void)Cy_SysClk_PeriGroupSetSlaveCtl(1, CY_SYSCLK_PERI_GROUP_SL_CTL, 0xFFFFU); /* Suppress a compiler warning about unused return value */
    (void)Cy_SysClk_PeriGroupSetSlaveCtl(2, CY_SYSCLK_PERI_GROUP_SL_CTL, 0xFFFFU); /* Suppress a compiler warning about unused return value */
    (void)Cy_SysClk_PeriGroupSetSlaveCtl(3, CY_SYSCLK_PERI_GROUP_SL_CTL, 0xFFFFU); /* Suppress a compiler warning about unused return value */
    (void)Cy_SysClk_PeriGroupSetSlaveCtl(4, CY_SYSCLK_PERI_GROUP_SL_CTL, 0xFFFFU); /* Suppress a compiler warning about unused return value */
    (void)Cy_SysClk_PeriGroupSetSlaveCtl(5, CY_SYSCLK_PERI_GROUP_SL_CTL, 0xFFFFU); /* Suppress a compiler warning about unused return value */
    (void)Cy_SysClk_PeriGroupSetSlaveCtl(6, CY_SYSCLK_PERI_GROUP_SL_CTL, 0xFFFFU); /* Suppress a compiler warning about unused return value */
    (void)Cy_SysClk_PeriGroupSetSlaveCtl(8, CY_SYSCLK_PERI_GROUP_SL_CTL, 0xFFFFU); /* Suppress a compiler warning about unused return value */
    (void)Cy_SysClk_PeriGroupSetSlaveCtl(9, CY_SYSCLK_PERI_GROUP_SL_CTL, 0xFFFFU); /* Suppress a compiler warning about unused return value */

    /* Unlock and disable WDT */
        Cy_WDT_Unlock();
        Cy_WDT_Disable();

    #endif /* (__CM0P_PRESENT == 0) */
#endif /* __CM0P_PRESENT */

    Cy_SystemInit();
    SystemCoreClockUpdate();

    SystemIrqInit();
}

/*******************************************************************************
* Function Name: SystemIrqInit
****************************************************************************//**
*
* The function is called during device startup.
*
*******************************************************************************/
void SystemIrqInit(void)
{
    for (int i=0; i<(int)CPUSS_SYSTEM_INT_NR; i++)
    {
        Cy_SystemIrqUserTable[i] = DEFAULT_HANDLER_NAME;
    }

    Cy_SysInt_SystemIrqUserTableRamPointer = Cy_SystemIrqUserTable;
}

/*******************************************************************************
* Function Name: Cy_SystemInit
****************************************************************************//**
*
* The function is called during device startup.
*
*******************************************************************************/
__WEAK void Cy_SystemInit(void)
{
     /* Empty weak function. The actual implementation to be in the user application
      * as strong function.
     */
}

/*******************************************************************************
* Function Name: SystemCoreClockUpdate
****************************************************************************//**
*
* Gets core clock frequency and updates \ref SystemCoreClock, \ref
* cy_Hfclk0FreqHz, and \ref cy_PeriClkFreqHz.
*
* Updates global variables used by the \ref Cy_SysLib_Delay(), \ref
* Cy_SysLib_DelayUs(), and \ref Cy_SysLib_DelayCycles().
*
*******************************************************************************/
void SystemCoreClockUpdate (void)
{
    /* Get frequency for the fast clock source of the core we are currently building for. */
    #if defined (CORE_NAME_CM7_0) && (CORE_NAME_CM7_0 == 1)
    SystemCoreClock = Cy_SysClk_ClkFastSrcGetFrequency(0);
    #else
    SystemCoreClock = Cy_SysClk_ClkFastSrcGetFrequency(1);
    #endif

    /* This is part of the clock tree for the CM0+; do not use for CM7 clock calculations. */
    cy_Hfclk0FreqHz = Cy_SysClk_ClkHfGetFrequency(CY_SYSCLK_CLK_CORE_HF_PATH_NUM);

    /* Get frequency for the high-frequency clock # 2 , which is used for PERI PCLK. */
    cy_PeriClkFreqHz = Cy_SysClk_ClkHfGetFrequency(CY_SYSCLK_CLK_PERI_HF_PATH_NUM);

    /* Sets clock frequency for Delay API */
    cy_delayFreqHz = SystemCoreClock;
    cy_delayFreqMhz = (uint32_t)((cy_delayFreqHz + CY_DELAY_1M_MINUS_1_THRESHOLD) / CY_DELAY_1M_THRESHOLD);
    cy_delayFreqKhz = (cy_delayFreqHz + CY_DELAY_1K_MINUS_1_THRESHOLD) / CY_DELAY_1K_THRESHOLD;

    /* Get the frequency of AHB source, CLK HF0 is the source for AHB*/
    cy_AhbFreqHz = Cy_SysClk_ClkHfGetFrequency(0UL);
}


/*******************************************************************************
* Function Name: Cy_DefaultUserHandler
****************************************************************************//**
*
*The Handler is called when the CPU attempts to call IRQ that has not been mapped to user functions.
*
*
*******************************************************************************/
void Cy_DefaultUserHandler(void)
{
    // This IRQ occurred because CPU attempted to call IRQ that has not been mapped to user function
    while(1);
}


/*******************************************************************************
* Function Name: CM7_CpuIntr_Handler
****************************************************************************//**
*
* The Inline handler for CPU interrupt.
* The system interrupt mapped to CPU interrupt will be fetched and executed
*
*******************************************************************************/
CY_SECTION_ITCM_BEGIN
void CM7_CpuIntr_Handler(uint8_t intrNum)
{
    uint32_t system_int_idx;
    cy_israddress handler;

#ifdef CORE_NAME_CM7_0
    if((_FLD2VAL(CPUSS_CM7_0_INT_STATUS_SYSTEM_INT_VALID, CPUSS_CM7_0_INT_STATUS[intrNum])))
    {
        system_int_idx = _FLD2VAL(CPUSS_CM7_0_INT_STATUS_SYSTEM_INT_IDX, CPUSS_CM7_0_INT_STATUS[intrNum]);
        handler = Cy_SystemIrqUserTable[system_int_idx];
        handler(); // jump to system interrupt handler
    }
#endif
#ifdef CORE_NAME_CM7_1
    if((_FLD2VAL(CPUSS_CM7_1_INT_STATUS_SYSTEM_INT_VALID, CPUSS_CM7_1_INT_STATUS[intrNum])))
    {
        system_int_idx = _FLD2VAL(CPUSS_CM7_1_INT_STATUS_SYSTEM_INT_IDX, CPUSS_CM7_1_INT_STATUS[intrNum]);
        handler = Cy_SystemIrqUserTable[system_int_idx];
        handler(); // jump to system interrupt handler
    }
#endif
    NVIC_ClearPendingIRQ((IRQn_Type)intrNum);
}
CY_SECTION_ITCM_END

