/**
  *********************************************************************************
  *
  * @file    ald_utils.c
  * @brief   This file contains the Utilities functions/types for the driver.
  *
  * @version V1.0
  * @date    8 Feb. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          8 Feb. 2023     Lisq            The first version
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  * SPDX-License-Identifier: Apache-2.0
  *
  * Licensed under the Apache License, Version 2.0 (the License); you may
  * not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  * www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an AS IS BASIS, WITHOUT
  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  **********************************************************************************
  */

#include <string.h>
#include "ald_conf.h"

/** @defgroup EASTSOFT ES32VF2264 ALD
  * @brief Shanghai Eastsoft Microelectronics E902 Chip Abstraction Layer Driver(ALD)
  * @{
  */

/** @defgroup UTILS Utils
  * @brief Utils module driver
  * @{
  */

/** @defgroup ALD_Private_Constants Private Constants
  * @brief ALD Private Constants
  * @{
  */

/**
  * @brief ALD version number
  */
#define __ALD_VERSION_MAIN  (0x01) /**< [31:24] main version */
#define __ALD_VERSION_SUB1  (0x00) /**< [23:16] sub1 version */
#define __ALD_VERSION_SUB2  (0x00) /**< [15:8]  sub2 version */
#define __ALD_VERSION_RC    (0x00) /**< [7:0]  release candidate */
#define __ALD_VERSION       ((__ALD_VERSION_MAIN << 24) | \
                                 (__ALD_VERSION_SUB1 << 16) | \
                                 (__ALD_VERSION_SUB2 << 8 ) | \
                                 (__ALD_VERSION_RC))
/**
  * @}
  */

/** @defgroup ALD_Private_Variables Private Variables
  * @{
  */
/** @brief lib_tick: Increase by one millisecond
  */
__IO uint32_t lib_tick;
uint32_t __systick_interval = ALD_SYSTICK_INTERVAL_1MS;
/**
  * @}
  */


/** @defgroup ALD_Public_Functions Public Functions
  * @{
  */

/** @defgroup ALD_Public_Functions_Group1 Initialization Function
  * @brief    Initialization functions
  *
  * @verbatim
 ===============================================================================
              ##### Initialization functions #####
 ===============================================================================
   [..]  This section provides functions allowing to:
      (+) Initializes interface, the NVIC allocation and initial clock
          configuration. It initializes the source of time base also when timeout
          is needed and the backup domain when enabled.
      (+) Configure The time base source to have 1ms time base with a dedicated
          Tick interrupt priority.
        (++) Systick timer is used by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms.
        (++) Time base configuration function (ald_tick_init()) is called automatically
             at the beginning of the program after reset by ald_cmu_init() or at
         any time when clock is configured.
        (++) Source of time base is configured  to generate interrupts at regular
             time intervals. Care must be taken if ald_delay_ms() is called from a
             peripheral ISR process, the Tick interrupt line must have higher priority
            (numerically lower) than the peripheral interrupt. Otherwise the caller
            ISR process will be blocked.
       (++) functions affecting time base configurations are declared as __weak
             to make  override possible  in case of other implementations in user file.
      (+) Configure the interval of Systick interrupt.

    @endverbatim
  * @{
  */

/**
  * @brief  This function Configures time base source, CLINT and DMA.
  * @note   This function is called at the beginning of program after reset and before
  *         the clock configuration.
  * @note   The time base configuration is based on MSI clock when exiting from Reset.
  *         Once done, time base tick start incrementing.
  *         In the default implementation, Systick is used as source of time base.
  *         The tick variable is incremented each 1ms in its ISR.
  * @retval None
  */
void ald_cmu_init(void)
{
    ald_cmu_clock_config_default();
    ald_tick_init(TICK_INT_PRIORITY);
#ifdef ALD_DMA
    ald_cmu_perh_clock_config(ALD_CMU_PERH_DMA, ENABLE);
    ald_dma_init();
#endif
    return;
}

/**
  * @brief  This function configures the source of the time base.
  *         The time source is configured to have 1ms time base with a dedicated
  *         Tick interrupt priority.
  * @note   In the default implementation, SysTick timer is the source of time base.
  *         It is used to generate interrupts at regular time intervals.
  *         Care must be taken if ald_delay_ms() is called from a peripheral ISR process,
  *         The SysTick interrupt must have higher priority (numerically lower)
  *         than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
  *         The function is declared as __weak to be overwritten in case of other
  *         implementation in user file.
  * @param  prio: Tick interrupt priority.
  * @retval None
  */
__weak void ald_tick_init(uint32_t prio)
{
    /* Configure the SysTick IRQ */
    csi_coret_config(ald_cmu_get_sys_clock() / ALD_SYSTICK_INTERVAL_1MS, CLINT_IRQn);
    csi_vic_set_prio(CLINT_IRQn, prio);
    csi_vic_enable_sirq(CLINT_IRQn);

    return;
}

/**
  * @brief  Selects the interval of systick interrupt.
  * @param  value: The value of interval:
  *           @arg @ref SYSTICK_INTERVAL_1MS    1 millisecond
  *           @arg @ref SYSTICK_INTERVAL_10MS   10 milliseconds
  *           @arg @ref SYSTICK_INTERVAL_100MS  100 milliseconds
  *           @arg @ref SYSTICK_INTERVAL_1000MS 1 second
  * @retval None
  */
void ald_systick_interval_select(ald_systick_interval_t value)
{
    assert_param(IS_SYSTICK_INTERVAL(value));

    if (value == 0)
        return;

    csi_coret_config(ald_cmu_get_sys_clock() / value, CLINT_IRQn);
    __systick_interval = value;

    if (TICK_INT_PRIORITY != 15)
        csi_vic_set_prio(CLINT_IRQn, TICK_INT_PRIORITY);

    return;
}
/**
  * @}
  */

/** @defgroup ALD_Public_Functions_Group2 Control functions
  * @brief    Control functions
  *
  * @verbatim
 ===============================================================================
                      ##### Control functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Provide a tick value in millisecond
      (+) Provide a blocking delay in millisecond
      (+) Suspend the time base source interrupt
      (+) Resume the time base source interrupt
      (+) Get the ALD version
      (+) Waiting for flag
      (+) Configure the interrupt
      (+) Provide system tick value
      (+) Initialize core timestamp
      (+) Get core timestamp
      (+) Get CPU ID
      (+) Get UID
      (+) Get CHIPID

    @endverbatim
  * @{
  */

/**
  * @brief  This function invoked by Systick ISR.
  * @note   This function is declared as __weak to be overwritten in case of
  *         other implementations in user file.
  * @retval None
  */
__weak void ald_systick_irq_cbk(void)
{
    /* do nothing */
    return;
}

/**
  * @brief  This function is called to increment a global variable "lib_tick"
  *         used as application time base.
  * @note   In the default implementation, this variable is incremented each 1ms
  *         in Systick ISR.
  * @note   This function is declared as __weak to be overwritten in case of other
  *         implementations in user file.
  * @retval None
  */
__weak void ald_inc_tick(void)
{
    ++lib_tick;
    ald_systick_irq_cbk();
}

/**
  * @brief  Provides a tick value in millisecond.
  * @note   This function is declared as __weak to be overwritten in case of other
  *         implementations in user file.
  * @retval tick value
  */
__weak uint32_t ald_get_tick(void)
{
    return lib_tick;
}

/**
  * @brief  This function provides accurate delay (in milliseconds) based
  *         on variable incremented.
  * @note   In the default implementation, SysTick timer is the source of time base.
  *         It is used to generate interrupts at regular time intervals where lib_tick
  *         is incremented.
  * @note   This function is declared as __weak to be overwritten in case of other
  *         implementations in user file.
  * @param  delay: specifies the delay time length, in milliseconds.
  * @retval None
  */
__weak void ald_delay_1ms(__IO uint32_t delay)
{
    uint32_t tick, __delay;

    switch (__systick_interval) {
    case ALD_SYSTICK_INTERVAL_1MS:
        __delay = delay;
        break;

    case ALD_SYSTICK_INTERVAL_10MS:
        __delay = delay / 10;
        break;

    case ALD_SYSTICK_INTERVAL_100MS:
        __delay = delay / 100;
        break;

    case ALD_SYSTICK_INTERVAL_1000MS:
        __delay = delay / 1000;
        break;

    default:
        __delay = delay;
        break;
    }

    tick    = ald_get_tick();
    __delay = __delay == 0 ? 1 : __delay;

    while ((ald_get_tick() - tick) < __delay)
        ;
}

/**
  * @brief  This function provides accurate delay (in microseconds) based
  *         on variable incremented.
  * @note   In the default implementation, SysTick timer is the source of time base.
  *         It is used to generate interrupts at regular time intervals where lib_tick
  *         is incremented.
  * @note   This function is declared as __weak to be overwritten in case of other
  *         implementations in user file.
  * @param  delay: specifies the delay time length, in microseconds(us).
  * @retval None
  */
__weak void ald_delay_1us(__IO uint32_t delay)
{
    uint32_t start, now, delta, us_tick;
    start = CORET->MTIME;
    us_tick = ald_cmu_get_sys_clock() / 1000000UL;
    do
    {
        now = CORET->MTIME;
        delta = now - start;
    }
    while (delta <  (us_tick * delay));
}

/**
  * @brief  This method returns the ALD revision
  * @retval version: 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t ald_get_ald_version(void)
{
    return __ALD_VERSION;
}

/**
  * @brief  Configure the flash wait period.
  * @param  cycle: The period.
  * @retval None
  */
void ald_flash_wait_config(uint8_t cycle)
{
    uint32_t tmp;

    tmp = MSC->MEMWAIT;
    MODIFY_REG(tmp, MSC_MEMWAIT_FLASH_W_MSK, (0x30U | cycle) << MSC_MEMWAIT_FLASH_W_POSS);
    MSC->MEMWAIT = tmp;

    return;
}

/**
  * @brief  Waiting the specified bit in the register change to SET/RESET.
  * @param  reg: The register address.
  * @param  bit: The specified bit.
  * @param  status: The status for waiting.
  * @param  timeout: Timeout duration.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_wait_flag(uint32_t *reg, uint32_t bit, flag_status_t status, uint32_t timeout)
{
    uint32_t tick = ald_get_tick();

    assert_param(timeout > 0);

    if (status == SET) {
        while (!(IS_BIT_SET(*reg, bit))) {
            if (((ald_get_tick()) - tick) > timeout)
                return ALD_TIMEOUT;
        }
    }
    else {
        while ((IS_BIT_SET(*reg, bit))) {
            if (((ald_get_tick()) - tick) > timeout)
                return ALD_TIMEOUT;
        }
    }

    return ALD_OK;
}

/**
  * @brief  Configure interrupt.
  * @param  irq: Interrunpt type.
  * @param  prio: preempt priority(0-7). The larger the prio value, the higher the priority.
  * @param  status: Status.
  *           @arg ENABLE
  *           @arg DISABLE
  * @retval None
  */
void ald_mcu_irq_config(IRQn_Type irq, uint8_t prio, type_func_t status)
{
    assert_param(IS_FUNC_STATE(status));

    if (status == ENABLE)
    {
        csi_vic_set_prio(irq, prio);
        csi_vic_enable_sirq(irq);
    }
    else
    {
        csi_vic_disable_sirq(irq);
    }

    return;
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
