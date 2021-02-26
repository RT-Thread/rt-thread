/**
  *********************************************************************************
  *
  * @file    utils.c
  * @brief   This file contains the Utilities functions/types for the driver.
  *
  * @version V1.0
  * @date    07 Nov 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#include <string.h>
#include "utils.h"
#include "ald_dma.h"
#include "ald_cmu.h"


/** @defgroup ES32FXXX_ALD EASTSOFT ES32F3xx ALD
  * @brief Shanghai Eastsoft Microelectronics Cortex-M Chip Abstraction Layer Driver(ALD)
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
#define __ALD_VERSION_MAIN	(0x01) /**< [31:24] main version */
#define __ALD_VERSION_SUB1	(0x00) /**< [23:16] sub1 version */
#define __ALD_VERSION_SUB2	(0x00) /**< [15:8]  sub2 version */
#define __ALD_VERSION_RC	(0x00) /**< [7:0]  release candidate */
#define __ALD_VERSION		((__ALD_VERSION_MAIN << 24) | \
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
static __IO uint32_t lib_tick;
uint32_t __systick_interval = SYSTICK_INTERVAL_1MS;
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
  * @brief  This function Configures time base source, NVIC and DMA.
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
	NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_2);
	ald_cmu_clock_config_default();
	ald_tick_init(TICK_INT_PRIORITY);
#ifdef ALD_DMA
	ald_cmu_perh_clock_config(CMU_PERH_DMA, ENABLE);
	ald_dma_init(DMA0);
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
	NVIC_SetPriority(SysTick_IRQn, prio);
	SysTick_Config(ald_cmu_get_sys_clock() / SYSTICK_INTERVAL_1MS);

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
void ald_systick_interval_select(systick_interval_t value)
{
	assert_param(IS_SYSTICK_INTERVAL(value));

	SysTick_Config(ald_cmu_get_sys_clock() / value);
	__systick_interval = value;

	if (TICK_INT_PRIORITY != 15)
		NVIC_SetPriority(SysTick_IRQn, TICK_INT_PRIORITY);

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
__weak void ald_delay_ms(__IO uint32_t delay)
{
	uint32_t tick, __delay;

	switch (__systick_interval) {
	case SYSTICK_INTERVAL_1MS:
		__delay = delay;
		break;

	case SYSTICK_INTERVAL_10MS:
		__delay = delay / 10;
		break;

	case SYSTICK_INTERVAL_100MS:
		__delay = delay / 100;
		break;

	case SYSTICK_INTERVAL_1000MS:
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
  * @brief  Suspend Tick increment.
  * @note   In the default implementation, SysTick timer is the source of time base.
  *         It is used to generate interrupts at regular time intervals.
  *         Once ald_suspend_tick() is called, the the SysTick interrupt
  *         will be disabled and so Tick increment is suspended.
  * @note   This function is declared as __weak to be overwritten
  *         in case of other implementations in user file.
  * @retval None
  */
__weak void ald_suspend_tick(void)
{
	CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief  Resume Tick increment.
  * @note   In the default implementation, SysTick timer is the source of
  *         time base. It is used to generate interrupts at regular time
  *         intervals. Once ald_resume_tick() is called, the the SysTick
  *         interrupt will be enabled and so Tick increment is resumed.
  * @note   This function is declared as __weak to be overwritten
  *         in case of other implementations in user file.
  * @retval None
  */
__weak void ald_resume_tick(void)
{
	SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
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
				return TIMEOUT;
		}
	}
	else {
		while ((IS_BIT_SET(*reg, bit))) {
			if (((ald_get_tick()) - tick) > timeout)
				return TIMEOUT;
		}
	}

	return OK;
}

/**
  * @brief  Configure interrupt.
  * @param  irq: Interrunpt type.
  * @param  preempt_prio: preempt priority(0-3).
  * @param  sub_prio: sub-priority(0-3).
  * @param  status: Status.
  *           @arg ENABLE
  *           @arg DISABLE
  * @retval None
  */
void ald_mcu_irq_config(IRQn_Type irq, uint8_t preempt_prio, uint8_t sub_prio, type_func_t status)
{
	uint32_t pri;
	uint8_t sub_bw, pre_bw;
	uint8_t sub_mask = 0xF;

	assert_param(IS_FUNC_STATE(status));
	assert_param(IS_PREEMPT_PRIO(preempt_prio));
	assert_param(IS_SUB_PRIO(sub_prio));

	if (status == ENABLE) {
		pre_bw     = 7 - (((SCB->AIRCR) >> 8) & 7);
		sub_bw     = 4 - pre_bw;
		sub_mask >>= pre_bw;

		pri  = preempt_prio << sub_bw;
		pri |= sub_prio & sub_mask;

		NVIC_SetPriority(irq, pri);
		NVIC_EnableIRQ(irq);
	}
	else {
		NVIC_DisableIRQ(irq);
	}

	return;
}

/**
  * @brief  Initialize core timestamp.
  * @retval None
  */
void ald_mcu_timestamp_init(void)
{
	DEM_CR    |= (uint32_t)DEM_CR_TRCENA;
	DWT_CYCCNT = 0x0;
	DWT_CR    |= (uint32_t)DWT_CR_CYCCNTEA;

	return;
}

/**
  * @brief  Get core timestamp.
  * @retval None
  */
uint32_t ald_mcu_get_timestamp(void)
{
	return (uint32_t)DWT_CYCCNT;
}

/**
  * @brief  Get the CPU ID.
  * @retval CPU ID.
  */
uint32_t ald_mcu_get_cpu_id(void)
{
	return SCB->CPUID;
}

/**
  * @brief  Get the UID.
  * @param  buf: Pointer to UID, len: 12Bytes(96-bits)
  * @retval None
  */
void ald_mcu_get_uid(uint8_t *buf)
{
	memcpy(&buf[0], (void *)MCU_UID0_ADDR, 4);
	memcpy(&buf[4], (void *)MCU_UID1_ADDR, 4);
	memcpy(&buf[8], (void *)MCU_UID2_ADDR, 4);

	return;
}

/**
  * @brief  Get the CHIPID
  * @retval CHPID
  */
uint32_t ald_mcu_get_chipid(void)
{
	return (uint32_t)*(uint32_t *)MCU_CHIPID_ADDR;
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
