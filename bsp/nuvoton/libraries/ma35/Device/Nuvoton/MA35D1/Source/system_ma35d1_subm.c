/**************************************************************************//**
 * @file     startup_subm.c
 * @brief    CMSIS Cortex-M4 Core Peripheral Access Layer Source File
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#include "NuMicro.h"


/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock  = __SYSTEM_CLOCK;    /*!< System Clock Frequency (Core Clock)*/
uint32_t CyclesPerUs      = (__HSI / 1000000UL); /* Cycles per micro second */


/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate(void)             /* Get Core Clock Frequency      */
{

    /* Update System Core Clock */
    SystemCoreClock = 180000000;
    CyclesPerUs = (SystemCoreClock + 500000UL) / 1000000UL;

}

/**
  * @brief      Set PF.2 and PF.3 to input mode
  * @param      None
  * @return     None
  * @details    GPIO default state could be configured as input or quasi through user config.
  *             To use HXT, PF.2 and PF.3 must not set as quasi mode. This function changes
  *             PF.2 and PF.3 to input mode no matter which mode they are working at.
  */


/**
 * @brief  Initialize the System
 *
 * @param  none
 * @return none
 */
void SystemInit(void)
{
    /* Add your system initialize code here.
       Do not use global variables because this function is called before
       reaching pre-main. RW section maybe overwritten afterwards.          */


    /* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1U) && (__FPU_USED == 1U)
    SCB->CPACR |= ((3UL << 10 * 2) |               /* set CP10 Full Access */
                   (3UL << 11 * 2));               /* set CP11 Full Access */
#endif


}

