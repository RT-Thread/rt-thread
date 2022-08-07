/***************************************************************************//**
* \file ns_system_cyw20829.c
* \version 1.0
*
* The device system-source file.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
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

#if defined (CY_DEVICE_CYW20829)
#include <stdbool.h>
#include "system_cyw20829.h"
#include "cy_syslib.h"
#include "cy_wdt.h"
#include "cy_sysclk.h"
#include "cy_syspm.h"

CY_MISRA_DEVIATE_BLOCK_START('ARRAY_VS_SINGLETON', 1, \
'Checked manually. Using pointer as an array will not corrupt or misinterpret adjacent memory locations.');
CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 18.1', 1, \
'Checked manually. Dereferencing a pointer to one beyond the end of an array will not result in undefined behaviour.');
CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 18.3', 1, \
'Checked manually. Attempting to make comparisons between pointers will not result in undefined behaviour.');
CY_MISRA_FP_BLOCK_START('MISRA C-2012 Rule 8.6', 2, \
'Checked manually. The definition is a part of linker script or application.');

/*******************************************************************************
* SystemCoreClockUpdate()
*******************************************************************************/

/** Default HFClk frequency in Hz */
#define CY_CLK_HFCLK0_FREQ_HZ_DEFAULT       (8000000UL)

/** Default PeriClk frequency in Hz */
#define CY_CLK_PERICLK_FREQ_HZ_DEFAULT      (8000000UL)

/** Default system core frequency in Hz */
#define CY_CLK_SYSTEM_FREQ_HZ_DEFAULT       (8000000UL)

/** Default PSVP FLL frequency in Hz */
#define CY_SYSCLK_PSVP_FLL_FREQ             (48000000UL)

/**
* Holds the (Cortex-M33) system core clock,
* which is the system clock frequency supplied to the SysTick timer and the
* processor core clock.
* This variable implements CMSIS Core global variable.
* Refer to the [CMSIS documentation]
* (http://www.keil.com/pack/doc/CMSIS/Core/html/group__system__init__gr.html "System and Clock Configuration")
* for more details.
* This variable can be used by debuggers to query the frequency
* of the debug timer or to configure the trace clock speed.
*
* \attention Compilers must be configured to avoid removing this variable in case
* the application program is not using it. Debugging systems require the variable
* to be physically present in memory so that it can be examined to configure the debugger. */
uint32_t SystemCoreClock = CY_CLK_SYSTEM_FREQ_HZ_DEFAULT;

/** Holds the HFClk0 clock frequency. Updated by \ref SystemCoreClockUpdate(). */
uint32_t cy_Hfclk0FreqHz  = CY_CLK_HFCLK0_FREQ_HZ_DEFAULT;

/** Holds the PeriClk clock frequency. Updated by \ref SystemCoreClockUpdate(). */
uint32_t cy_PeriClkFreqHz = CY_CLK_PERICLK_FREQ_HZ_DEFAULT;

/*******************************************************************************
* SystemCoreClockUpdate (void)
*******************************************************************************/

/* Do not use these definitions directly in your application */
#define CY_DELAY_MS_OVERFLOW_THRESHOLD  (0x8000u)
#define CY_DELAY_1K_THRESHOLD           (1000u)
#define CY_DELAY_1K_MINUS_1_THRESHOLD   (CY_DELAY_1K_THRESHOLD - 1u)
#define CY_DELAY_1M_THRESHOLD           (1000000u)
#define CY_DELAY_1M_MINUS_1_THRESHOLD   (CY_DELAY_1M_THRESHOLD - 1u)
uint32_t cy_delayFreqHz   = CY_CLK_SYSTEM_FREQ_HZ_DEFAULT;

uint32_t cy_delayFreqKhz  = (CY_CLK_SYSTEM_FREQ_HZ_DEFAULT + CY_DELAY_1K_MINUS_1_THRESHOLD) /
                            CY_DELAY_1K_THRESHOLD;

uint8_t cy_delayFreqMhz  = (uint8_t)((CY_CLK_SYSTEM_FREQ_HZ_DEFAULT + CY_DELAY_1M_MINUS_1_THRESHOLD) /
                            CY_DELAY_1M_THRESHOLD);

uint32_t cy_delay32kMs    = CY_DELAY_MS_OVERFLOW_THRESHOLD *
                            ((CY_CLK_SYSTEM_FREQ_HZ_DEFAULT + CY_DELAY_1K_MINUS_1_THRESHOLD) / CY_DELAY_1K_THRESHOLD);

#if defined (FLASH_BOOT)

#if !defined (__ARMCC_VERSION)
void bootstrapInit(void)
{
    typedef struct
    {
        uint32_t* dest;
        uint32_t  wlen;
    } __bootstrap_zero_table_t;

    extern const __bootstrap_zero_table_t __bootstrapzero_table_start__;
    extern const __bootstrap_zero_table_t __bootstrapzero_table_end__;

    /* Initialize .cy_l1bss section to zero */
    for (__bootstrap_zero_table_t const* pTable = &__bootstrapzero_table_start__; pTable < &__bootstrapzero_table_end__; ++pTable)
    {
        for(uint32_t i=0u; i<pTable->wlen; ++i)
        {
            pTable->dest[i] = 0u;
        }
    }
}
#endif
#endif /* FLASH_BOOT */

/*******************************************************************************
* Function Name: SystemInit_CAT1B_CM33
****************************************************************************//**
*
* Initializes the system:
* - Unlocks and disables WDT.
* - Calls Cy_PDL_Init() function to define the driver library.
* - Calls the Cy_SystemInit() function.
* - Calls \ref SystemCoreClockUpdate().
*
*******************************************************************************/
void SystemInit_CAT1B_CM33(void)
{
    /* Release reset for all groups IP except group 0 */
    (void)Cy_SysClk_PeriGroupSetSlaveCtl(1, CY_SYSCLK_PERI_GROUP_SL_CTL2, 0x0U); /* typecast void to suppress a compiler warning about unused return value */
    (void)Cy_SysClk_PeriGroupSetSlaveCtl(2, CY_SYSCLK_PERI_GROUP_SL_CTL2, 0x0U); /* typecast void to suppress a compiler warning about unused return value */

    (void)Cy_SysClk_PeriGroupSetSlaveCtl(1, CY_SYSCLK_PERI_GROUP_SL_CTL, 0xFFFFFFFFU); /* typecast void to suppress a compiler warning about unused return value */
    (void)Cy_SysClk_PeriGroupSetSlaveCtl(2, CY_SYSCLK_PERI_GROUP_SL_CTL, 0xFFFFFFFFU); /* typecast void to suppress a compiler warning about unused return value */
    (void)Cy_SysClk_PeriGroupSetSlaveCtl(3, CY_SYSCLK_PERI_GROUP_SL_CTL, 0xFFFFFFFFU); /* typecast void to suppress a compiler warning about unused return value */

    Cy_PDL_Init(CY_DEVICE_CFG);
    (void)Cy_SystemInit(); /* typecast void to suppress a compiler warning about unused return value */

    if(CY_SYSPM_WARM_BOOT_MODE == Cy_SysPm_GetBootMode())
    {
        /* Unfreeze the IO's which are frozen during DEEPSLEEP-RAM and DEEPSLEEP-OFF Entry */
        if(Cy_SysPm_DeepSleepIoIsFrozen())
        {
            Cy_SysPm_DeepSleepIoUnfreeze();
        }
    }
    else
    {
        /* Reset BT IP only during cold boot */
        (void)Cy_SysClk_PeriGroupSetSlaveCtl(3, CY_SYSCLK_PERI_GROUP_SL_CTL2, 0x0U); /* typecast void to suppress a compiler warning about unused return value */
    }

    /* Unlock and disable WDT */
    Cy_WDT_Unlock();
    Cy_WDT_Disable();

    SystemCoreClockUpdate();
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
     /* Empty weak function.
     */
     __NOP(); /* No operation */
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
    uint32_t pathFreqHz;
    uint32_t clkHfPath;

    /* Get frequency for the high-frequency clock # 0 */
    clkHfPath = CY_SYSCLK_CLK_CORE_HF_PATH_NUM;

    pathFreqHz = Cy_SysClk_ClkHfGetFrequency(clkHfPath);

    SystemCoreClock = pathFreqHz;

    cy_Hfclk0FreqHz = SystemCoreClock;

    /* Get frequency for the high-frequency clock # 2 , whcih is used for PERI PCLK*/
    clkHfPath = CY_SYSCLK_CLK_PERI_HF_PATH_NUM;

    pathFreqHz = Cy_SysClk_ClkHfGetFrequency(clkHfPath);

    cy_PeriClkFreqHz = pathFreqHz;

    /* Sets clock frequency for Delay API */
    cy_delayFreqHz = SystemCoreClock;
    cy_delayFreqMhz = (uint8_t)((cy_delayFreqHz + CY_DELAY_1M_MINUS_1_THRESHOLD) / CY_DELAY_1M_THRESHOLD);
    cy_delayFreqKhz = (cy_delayFreqHz + CY_DELAY_1K_MINUS_1_THRESHOLD) / CY_DELAY_1K_THRESHOLD;
    cy_delay32kMs   = CY_DELAY_MS_OVERFLOW_THRESHOLD * cy_delayFreqKhz;
}

CY_MISRA_BLOCK_END('MISRA C-2012 Rule 8.6');
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 18.3');
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 18.1');
CY_MISRA_BLOCK_END('ARRAY_VS_SINGLETON');

#endif /* defined (CY_DEVICE_CYW20829) */
/* [] END OF FILE */

