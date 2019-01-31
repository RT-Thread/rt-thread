/**
  *********************************************************************************
  *
  * @file    ald_pmu.c
  * @brief   PMU module driver.
  *
  * @version V1.0
  * @date    04 Dec 2017
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
void LVD_Handler(void)
{
    SYSCFG_UNLOCK();
    SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDCIF_MSK);
    SYSCFG_LOCK();

    lvd_irq_cbk();
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
void pmu_stop1_enter(void)
{
    SYSCFG_UNLOCK();
    MODIFY_REG(PMU->CR, PMU_CR_LPM_MSK, PMU_LP_STOP1 << PMU_CR_LPM_POSS);
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
void pmu_stop2_enter(void)
{
    SYSCFG_UNLOCK();
    MODIFY_REG(PMU->CR, PMU_CR_LPM_MSK, PMU_LP_STOP2 << PMU_CR_LPM_POSS);
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
  * @retval None
  */
void pmu_standby_enter(pmu_standby_wakeup_sel_t port)
{
    assert_param(IS_PMU_STANDBY_PORT_SEL(port));

    if (port != PMU_STANDBY_PORT_NONE)
    {
        BKPC_UNLOCK();
        MODIFY_REG(BKPC->CR, BKPC_CR_WKPS_MSK, port << BKPC_CR_WKPS_POSS);
        SET_BIT(BKPC->CR, BKPC_CR_WKPEN_MSK);
        BKPC_LOCK();

        SYSCFG_UNLOCK();
        MODIFY_REG(PMU->CR, PMU_CR_WKPS_MSK, port << PMU_CR_WKPS_POSS);
        SET_BIT(PMU->CR, PMU_CR_WKPEN_MSK);
        MODIFY_REG(PMU->CR, PMU_CR_LPM_MSK, PMU_LP_STANDBY << PMU_CR_LPM_POSS);
        SYSCFG_LOCK();
    }

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    __WFI();
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    return;
}

/**
  * @brief  Get wakup status.
  * @param  sr: Status bit.
  * @retval Status.
  */
flag_status_t pmu_get_status(pmu_status_t sr)
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
void pmu_clear_status(pmu_status_t sr)
{
    assert_param(IS_PMU_STATUS(sr));
    SYSCFG_UNLOCK();

    if (sr == PMU_SR_WUF)
        SET_BIT(PMU->CR, PMU_CR_CWUF_MSK);
    else
        SET_BIT(PMU->CR, PMU_CR_CSTANDBYF_MSK);

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
      (+) Interrupt callback function.

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
void pmu_lvd_config(pmu_lvd_voltage_sel_t sel, pmu_lvd_trigger_mode_t mode, type_func_t state)
{
    assert_param(IS_FUNC_STATE(state));
    SYSCFG_UNLOCK();

    if (state)
    {
        assert_param(IS_PMU_LVD_VOL_SEL(sel));
        assert_param(IS_PMU_LVD_TRIGGER_MODE(mode));

        MODIFY_REG(PMU->LVDCR, PMU_LVDCR_LVDS_MSK, sel << PMU_LVDCR_LVDS_POSS);
        MODIFY_REG(PMU->LVDCR, PMU_LVDCR_LVIFS_MSK, mode << PMU_LVDCR_LVIFS_POSS);
        SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDFLT_MSK);
        SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDCIF_MSK);
        SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDIE_MSK);
        SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDEN_MSK);
    }
    else
    {
        SET_BIT(PMU->LVDCR, PMU_LVDCR_LVDCIF_MSK);
        CLEAR_BIT(PMU->LVDCR, PMU_LVDCR_LVDIE_MSK);
        CLEAR_BIT(PMU->LVDCR, PMU_LVDCR_LVDEN_MSK);
    }

    SYSCFG_LOCK();
    return;
}

/**
  * @brief  Interrupt callback function.
  * @note   This function is declared as __weak to be overwritten in case of other
  *         implementations in user file.
  * @retval None
  */
__weak void lvd_irq_cbk(void)
{
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
