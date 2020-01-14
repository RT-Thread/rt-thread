/**
  *********************************************************************************
  *
  * @file    ald_pmu.c
  * @brief   PMU module driver.
  *
  * @version V1.0
  * @date    04 Dec 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#include "ald_pmu.h"
#include "ald_bkpc.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup PMU PMU
  * @brief PMU module driver
  * @{
  */
#ifdef ALD_PMU


/** @defgroup PMU_Private_Functions PMU Private Functions
  * @{
  */

/**
  * @brief  PMU module interrupt handler
  * @retval None
  */
void ald_lvd_irq_handler(void)
{
	SYSCFG_UNLOCK();
	SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDCIF_MSK);
	SYSCFG_LOCK();

	return;
}
/**
  * @}
  */

/** @defgroup PMU_Public_Functions PMU Public Functions
  * @{
  */

/** @addtogroup PMU_Public_Functions_Group1 Low Power Mode
  * @brief Low power mode select functions
  *
  * @verbatim
  ==============================================================================
              ##### Low power mode select functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Enter stop1 mode.
      (+) Enter stop2 mode.
      (+) Enter standby mode.
      (+) Get wakeup status.
      (+) Clear wakeup status.

    @endverbatim
  * @{
  */

/**
  * @brief  Enter stop1 mode
  * @retval None
  */
void ald_pmu_stop1_enter(void)
{
	SYSCFG_UNLOCK();
	SET_BIT(PMU->CR0, PMU_CR0_LPSTOP_MSK);
	MODIFY_REG(PMU->CR0, PMU_CR0_LPM_MSK, PMU_LP_STOP1 << PMU_CR0_LPM_POSS);
	SYSCFG_LOCK();

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	__WFI();
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	return;
}

/**
  * @brief  Enter stop2 mode
  * @retval None
  */
void ald_pmu_stop2_enter(void)
{
	SYSCFG_UNLOCK();
	SET_BIT(PMU->CR0, PMU_CR0_LPSTOP_MSK);
	MODIFY_REG(PMU->CR0, PMU_CR0_LPM_MSK, PMU_LP_STOP2 << PMU_CR0_LPM_POSS);
	SYSCFG_LOCK();

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	__WFI();
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	return;
}

/**
  * @brief  Enter standby mode
  * @param  port: The port whick wake up the standby mode.
  * @param  level: Wakeup level.
  * @retval None
  */
void ald_pmu_standby_enter(bkpc_wakeup_port_t port, bkpc_wakeup_level_t level)
{
	ald_bkpc_standby_wakeup_config(port, level);

	SYSCFG_UNLOCK();
	SET_BIT(PMU->CR0, PMU_CR0_LPSTOP_MSK);
	MODIFY_REG(PMU->CR0, PMU_CR0_LPM_MSK, PMU_LP_STANDBY << PMU_CR0_LPM_POSS);
	SYSCFG_LOCK();

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	__WFI();
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	return;
}

/**
  * @brief  Configures low power mode. The system clock must
  *         be less than 2MHz. Such as: LOSC or LRC.
  * @param  vol: LDO output voltage select in low power mode.
  * @param  state: New state, ENABLE/DISABLE;
  * @retval None
  */
void ald_pmu_lprun_config(pmu_ldo_lpmode_output_t vol, type_func_t state)
{
	assert_param(IS_FUNC_STATE(state));
	SYSCFG_UNLOCK();

	if (state) {
		assert_param(IS_PMU_LDO_LPMODE_OUTPUT(vol));

		MODIFY_REG(PMU->CR0, PMU_CR0_LPVS_MSK, vol << PMU_CR0_LPVS_POSS);
		SET_BIT(PMU->CR0, PMU_CR0_LPRUN_MSK);
	}
	else {
		CLEAR_BIT(PMU->CR0, PMU_CR0_LPRUN_MSK);
	}

	SYSCFG_LOCK();
	return;
}

/**
  * @brief  Get wakup status.
  * @param  sr: Status bit.
  * @retval Status.
  */
flag_status_t ald_pmu_get_status(pmu_status_t sr)
{
	assert_param(IS_PMU_STATUS(sr));

	if (READ_BIT(PMU->SR, sr))
		return SET;

	return RESET;
}

/**
  * @brief  Clear wakup status.
  * @param  sr: Status bit.
  * @retval None
  */
void ald_pmu_clear_status(pmu_status_t sr)
{
	assert_param(IS_PMU_STATUS(sr));
	SYSCFG_UNLOCK();

	if (sr == PMU_SR_WUF)
		SET_BIT(PMU->CR0, PMU_CR0_CWUF_MSK);
	else if (sr == PMU_SR_STANDBYF)
		SET_BIT(PMU->CR0, PMU_CR0_CSTANDBYF_MSK);
	else
		;/* do nothing */

	SYSCFG_LOCK();
	return;
}

/**
  * @brief  Configure peripheral power
  * @param  perh: The peripheral
  * @param  state: ENABLE/DISABLE
  * @retval None
  */
void ald_pmu_perh_power_config(pmu_perh_power_t perh, type_func_t state)
{
	assert_param(IS_PMU_PERH_POWER(perh));
	assert_param(IS_FUNC_STATE(state));

	SYSCFG_UNLOCK();

	if (state)
		SET_BIT(PMU->PWRCR, perh);
	else
		CLEAR_BIT(PMU->PWRCR, perh);

	SYSCFG_LOCK();
	return;
}
/**
  * @}
  */

/** @addtogroup PMU_Public_Functions_Group2 LVD Configure
  * @brief LVD configure functions
  *
  * @verbatim
  ==============================================================================
              ##### LVD configure functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure lvd parameters.

    @endverbatim
  * @{
  */

/**
  * @brief  Configure lvd using specified parameters.
  * @param  sel: LVD threshold voltage.
  * @param  mode: LVD trigger mode.
  * @param  state: New state, ENABLE/DISABLE;
  * @retval None
  */
void ald_pmu_lvd_config(pmu_lvd_voltage_sel_t sel, pmu_lvd_trigger_mode_t mode, type_func_t state)
{
	assert_param(IS_FUNC_STATE(state));
	SYSCFG_UNLOCK();

	if (state) {
		assert_param(IS_PMU_LVD_VOL_SEL(sel));
		assert_param(IS_PMU_LVD_TRIGGER_MODE(mode));

		MODIFY_REG(PMU->LVDCR, PMU_LVDCR_LVDS_MSK, sel << PMU_LVDCR_LVDS_POSS);
		MODIFY_REG(PMU->LVDCR, PMU_LVDCR_LVIFS_MSK, mode << PMU_LVDCR_LVIFS_POSS);
		SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDFLT_MSK);
		SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDCIF_MSK);
		SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDIE_MSK);
		SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDEN_MSK);
	}
	else {
		SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDCIF_MSK);
		CLEAR_BIT(PMU->LVDCR, PMU_LVDCR_LVDIE_MSK);
		CLEAR_BIT(PMU->LVDCR, PMU_LVDCR_LVDEN_MSK);
	}

	SYSCFG_LOCK();
	return;
}
/**
  * @}
  */


/**
  * @}
  */
#endif /* ALD_PMU */
/**
  * @}
  */

/**
  * @}
  */
