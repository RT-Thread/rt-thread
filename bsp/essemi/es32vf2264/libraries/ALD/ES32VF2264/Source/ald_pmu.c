/**
  *********************************************************************************
  *
  * @file    ald_pmu.c
  * @brief   PMU module driver.
  *
  * @version V1.0
  * @date    08 Mar. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          08 Mar. 2023    Lisq            The first version
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

#include "ald_pmu.h"

/** @addtogroup ES32VF2264_ALD
  * @{
  */

/** @defgroup PMU PMU
  * @brief PMU module driver
  * @{
  */
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
      (+) Get wakeup status.
      (+) Clear wakeup status.

    @endverbatim
  * @{
  */

/**
  * @brief  Get wakup status.
  * @param  sr: Status bit.
  * @retval Status.
  */
flag_status_t ald_pmu_get_status(ald_pmu_status_t sr)
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
void ald_pmu_clear_status(ald_pmu_status_t sr)
{
    assert_param(IS_PMU_STATUS(sr));
    SYSCFG_UNLOCK();

    if (sr == ALD_PMU_SR_WUF)
        SET_BIT(PMU->CR, PMU_CR_CWUF_MSK);
    else
        ;/* do nothing */

    SYSCFG_LOCK();
    return;
}

/**
  * @}
  */

/**
  * @brief  Enter stop mode
  * @retval None
  */
void ald_pmu_stop_enter(void)
{
    SYSCFG_UNLOCK();
    MODIFY_REG(PMU->CR, PMU_CR_LPM_MSK, ALD_PMU_LP_STOP << PMU_CR_LPM_POSS);
    CLEAR_BIT(PMU->CR, PMU_CR_VROSCEN_MSK);
    MODIFY_REG(PMU->CR, PMU_CR_LPSTOP_MSK | PMU_CR_BGSTOP_MSK | \
               PMU_CR_STPRTNEN_MSK | PMU_CR_FSTOP_MSK, \
               1 << PMU_CR_LPSTOP_POS | 1 << PMU_CR_BGSTOP_POS \
               | 1 << PMU_CR_STPRTNEN_POS | 1 << PMU_CR_FSTOP_POS);
    /* WKEVNSEL is only for testing, and user should set it to be 0x10. */
    MODIFY_REG(PMU->CR, PMU_CR_WKEVNSEL_MSK, (0x10 << PMU_CR_WKEVNSEL_POSS));
    SYSCFG_LOCK();

    csi_cpu_sleep_wfi(MEXSTATUS_SLEEP_DEEP);

    __WFI();
}

/**
  * @brief  Enter sleep mode
  * @retval None
  */
void ald_pmu_sleep_enter(void)
{
    SYSCFG_UNLOCK();
    MODIFY_REG(PMU->CR, PMU_CR_LPM_MSK, ALD_PMU_LP_STOP << PMU_CR_LPM_POSS);
    /* WKEVNSEL is only for testing, and user should set it to be 0x10. */
    MODIFY_REG(PMU->CR, PMU_CR_WKEVNSEL_MSK, (0x10 << PMU_CR_WKEVNSEL_POSS));
    SYSCFG_LOCK();

    csi_cpu_sleep_wfi(MEXSTATUS_SLEEP_LIGHT);

    __WFI();
}

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
void ald_pmu_lvd_config(ald_pmu_lvd_voltage_sel_t sel, ald_pmu_lvd_trigger_mode_t mode, type_func_t state)
{
    assert_param(IS_FUNC_STATE(state));
    SYSCFG_UNLOCK();

    if (state) {
        assert_param(IS_PMU_LVD_VOL_SEL(sel));
        assert_param(IS_PMU_LVD_TRIGGER_MODE(mode));

        MODIFY_REG(PMU->LVDCR, PMU_LVDCR_LVDS_MSK, sel << PMU_LVDCR_LVDS_POSS);
        MODIFY_REG(PMU->LVDCR, PMU_LVDCR_LVDIFS_MSK, mode << PMU_LVDCR_LVDIFS_POSS);
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
/**
  * @}
  */

/**
  * @}
  */
