/**
  *********************************************************************************
  *
  * @file    ald_cmu.c
  * @brief   CMU module driver.
  *
  * @version V1.0
  * @date    13 Feb. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          13 Feb. 2023    Lisq            The first version
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
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    [..]
     *** System clock configure ***
     =================================
     [..]
       (+) If you don't change system clock, you can using ald_cmu_clock_config_default() API.
           It will select HRC as system clock. The system clock is 48MHz.
       (+) If you want to change system clock, you can using ald_cmu_clock_config() API.
           You can select one of the following as system clock:
             @ref CMU_CLOCK_HRC   4MHz or 48MHz
             @ref CMU_CLOCK_LRC   32000Hz
             @ref CMU_CLOCK_PLL   48MHz, 64MHz or 72MHz
             @ref CMU_CLOCK_HOSC  32000Hz, 4MHz, 8MHz, 12MHz, 16MHz, 20MHz, 24MHz
       (+) If you select CMU_CLOCK_PLL as system clock, it must config the PLL
           using ald_cmu_pll_config() API.
       (+) If you get current clock, you can using ald_cmu_get_clock() API.
  ******************************************************************************
  */

#include "ald_conf.h"

/** @addtogroup ES32VF2264_ALD
  * @{
  */

/** @defgroup CMU CMU
  * @brief CMU module driver
  * @{
  */

/**
  * @defgroup CMU_Private_Variables CMU Private Variables
  * @{
  */
uint32_t __system_clock  = 48000000U;
/**
  * @}
  */

/** @defgroup CMU_Private_Functions CMU Private Functions
  * @{
  */

/**
  * @brief  Update the current system clock. This function
  *         will be invoked, when system clock has changed.
  * @param  clock: The new clock.
  * @retval None
  */

static void cmu_clock_update(uint32_t clock)
{
    __system_clock = clock;

    if (clock > 1000000)
        ald_tick_init(TICK_INT_PRIORITY);

    return;
}

/**
  * @brief  CMU module interrupt handler
  * @retval None
  */
void ald_cmu_irq_handler(void)
{
    /* HOSC stop */
    if (READ_BIT(CMU->HOSMCR, CMU_HOSMCR_STPIF_MSK) && READ_BIT(CMU->HOSMCR, CMU_HOSMCR_STPIE_MSK))
    {
        SYSCFG_UNLOCK();
        SET_BIT(CMU->HOSMCR, CMU_HOSMCR_STPIF_MSK);
        SYSCFG_LOCK();

        if ((READ_BIT(CMU->HOSMCR, CMU_HOSMCR_FLAG_MSK))
                && ((READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) == 3)
                || ((READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) == 5))))
            cmu_clock_update(4000000);  /* HRC4M */

        ald_cmu_irq_cbk(ALD_CMU_HOSC_STOP);
    }

    /* HOSC start */
    if (READ_BIT(CMU->HOSMCR, CMU_HOSMCR_STRIF_MSK) && READ_BIT(CMU->HOSMCR, CMU_HOSMCR_STRIE_MSK))
    {
        SYSCFG_UNLOCK();
        SET_BIT(CMU->HOSMCR, CMU_HOSMCR_STRIF_MSK);
        SYSCFG_LOCK();

        if (!(READ_BIT(CMU->HOSMCR, CMU_HOSMCR_FLAG_MSK))
                && ((READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) == 3)))
        {
            if(READ_BITS(CMU->HOSCCFG, CMU_HOSCCFG_FREQ_MSK, CMU_HOSCCFG_FREQ_POSS) > 0x5)
                cmu_clock_update(4000000);  /* HOSC4M */
            else
                cmu_clock_update((READ_BITS(CMU->HOSCCFG, CMU_HOSCCFG_FREQ_MSK, CMU_HOSCCFG_FREQ_POSS) + 1) * 4000000);
        }

        ald_cmu_irq_cbk(ALD_CMU_HOSC_START);
    }

    /* PLL unlock */
    if (READ_BIT(CMU->PULMCR, CMU_PULMCR_ULKIF_MSK) && READ_BIT(CMU->PULMCR, CMU_PULMCR_ULKIE_MSK))
    {
        SYSCFG_UNLOCK();
        SET_BIT(CMU->PULMCR, CMU_PULMCR_ULKIF_MSK);
        SYSCFG_LOCK();

        if (READ_BIT(CMU->PULMCR, CMU_PULMCR_CLKS_MSK)
                && ((READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) == 3)
                || ((READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) == 5))))
            cmu_clock_update(4000000);  /* HRC4M */

        ald_cmu_irq_cbk(ALD_CMU_PLL_UNLOCK);
    }

    return;
}
/**
  * @}
  */

/** @defgroup CMU_Public_Functions CMU Public Functions
  * @{
  */

/** @defgroup CMU_Public_Functions_Group1 System clock configuration
  * @brief    System clock configuration functions
  *
  ==============================================================================
              ##### System clock Configuration functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure system clock using default parameters.
      (+) Configure system clock using specified parameters.
      (+) Configure PLL using specified parameters.
      (+) Get system clock.
  * @{
  */

/**
  * @brief  Configure system clock using default.
  *         Select CMU_CLOCK_HRC(48MHz) as system clock and
  *         enable CMU_CLOCK_LRC(32000Hz).
  * @retval The status of ALD.
  */
ald_status_t ald_cmu_clock_config_default(void)
{
    uint32_t cnt = 4000, tmp;

    ald_flash_wait_config(2);

    SYSCFG_UNLOCK();

    WRITE_REG(CMU->CFGR, 0x0);

    tmp = READ_REG(CMU->CLKENR);
    /* Enable HRC48M */
    SET_BIT(tmp, CMU_CLKENR_HRC48MEN_MSK);
    WRITE_REG(CMU->CLKENR, tmp);

    for (cnt = 4000; cnt; --cnt);

    cnt = 4000;
    while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HRC48MACT_MSK))) && (--cnt));

    cnt = 4000;
    while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HRC48MRDY_MSK))) && (--cnt));

    /* Select HRC48M */
    MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, ALD_CMU_CLOCK_HRC48M << CMU_CSR_SYS_CMD_POSS);

    cnt = 4000;
    while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

    if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != ALD_CMU_CLOCK_HRC48M)
    {
        SYSCFG_LOCK();
        return ALD_ERROR;
    }

    cmu_clock_update(48000000);

    SYSCFG_LOCK();

    return ALD_OK;
}

/**
  * @brief  Configure system clock using specified parameters
  * @param  clk: The parameter can be one of the following:
  *           @arg @ref CMU_CLOCK_HRC  4MHz or 48MHz
  *           @arg @ref CMU_CLOCK_LRC  32kHz
  *           @arg @ref CMU_CLOCK_PLL  48MHz, 64MHz, 72MHz
  *           @arg @ref CMU_CLOCK_HOSC 4MHz, 8MHz, 12MHz, 16MHz, 20MHz, 24MHz
  * @param  clock: The clock which will be set. the value depends
  *         on the parameter of clk.
  * @retval The status of ALD.
  */
ald_status_t ald_cmu_clock_config(ald_cmu_clock_t clk, uint32_t clock)
{
    uint32_t cnt = 8000;

    ald_flash_wait_config(2);

    assert_param(IS_CMU_CLOCK(clk));
    SYSCFG_UNLOCK();

    switch (clk) {
    case ALD_CMU_CLOCK_HRC48M:
        assert_param(clock == 48000000);

        SET_BIT(CMU->CLKENR, CMU_CLKENR_HRC48MEN_MSK);

        for (cnt = 4000; cnt; --cnt);
        cnt = 4000;
        while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HRC48MACT_MSK))) && (--cnt));
        cnt = 4000;
        while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HRC48MRDY_MSK))) && (--cnt));

        MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, ALD_CMU_CLOCK_HRC48M << CMU_CSR_SYS_CMD_POSS);

        cnt = 4000;
        while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

        if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != ALD_CMU_CLOCK_HRC48M)
        {
            SYSCFG_LOCK();
            return ALD_ERROR;
        }

        cmu_clock_update(clock);

        break;

    case ALD_CMU_CLOCK_LRC:

        assert_param(clock == 32000);

        cnt = 4000;
        while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_LRCRDY_MSK))) && (--cnt));

        MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, ALD_CMU_CLOCK_LRC << CMU_CSR_SYS_CMD_POSS);

        cnt = 4000;
        while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

        if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != ALD_CMU_CLOCK_LRC)
        {
            SYSCFG_LOCK();
            return ALD_ERROR;
        }

        cmu_clock_update(clock);

        break;

    case ALD_CMU_CLOCK_HOSC:
        assert_param(clock == 4000000 || clock == 8000000 || clock == 12000000 ||
                     clock == 16000000 || clock == 20000000 || clock == 24000000);

        if(clock > 12000000)
            SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSCFLYBPS_MSK);  /* HOSC > 12MHz, enable HOSC Bypass Filter */

        SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK);

        MODIFY_REG(CMU->HOSCCFG, CMU_HOSCCFG_FREQ_MSK, clock / 4000000 - 1);

        for (cnt = 8000; cnt; --cnt);

        cnt = 4000;

        while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HOSCACT_MSK))) && (--cnt));

        cnt = 4000;

        while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HOSCRDY_MSK))) && (--cnt));

        MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, ALD_CMU_CLOCK_HOSC << CMU_CSR_SYS_CMD_POSS);

        cnt = 4000;
        while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

        if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != ALD_CMU_CLOCK_HOSC)
        {
            SYSCFG_LOCK();
            return ALD_ERROR;
        }

        cmu_clock_update(clock);
        break;

    case ALD_CMU_CLOCK_PLL:
        assert_param(clock == 72000000 || clock == 64000000 || clock == 48000000);

        SET_BIT(CMU->CLKENR, CMU_CLKENR_PLLEN_MSK);

        for (cnt = 4000; cnt; --cnt);

        cnt = 4000;

        while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_PLLACT_MSK))) && (--cnt));

        cnt = 4000;

        while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_PLLRDY_MSK))) && (--cnt));

        MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, ALD_CMU_CLOCK_PLL << CMU_CSR_SYS_CMD_POSS);

        cnt = 4000;
        while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

        if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != ALD_CMU_CLOCK_PLL)
        {
            SYSCFG_LOCK();
            return ALD_ERROR;
        }

        cmu_clock_update(clock);

        break;

    case ALD_CMU_CLOCK_HRC4M:
        assert_param(clock == 4000000);

        SET_BIT(CMU->CLKENR, CMU_CLKENR_HRC4MEN_MSK);

        for (cnt = 4000; cnt; --cnt);

        cnt = 4000;

        while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HRC4MACT_MSK))) && (--cnt));

        cnt = 4000;

        while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HRC4MRDY_MSK))) && (--cnt));

        MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, ALD_CMU_CLOCK_HRC4M << CMU_CSR_SYS_CMD_POSS);

        cnt = 4000;
        while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));

        if (READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) != ALD_CMU_CLOCK_HRC4M)
        {
            SYSCFG_LOCK();
            return ALD_ERROR;
        }

        cmu_clock_update(clock);

        break;

    default:
        break;
    }

    SYSCFG_LOCK();
    return ALD_OK;
}

/**
  * @brief  Configure PLL using specified parameters.
  * @param  input: The input clock type.
  * @param  output: The output clock which can be 48MHz/64MHz/72MHz.
  * @retval None
  */
void ald_cmu_pll_config(ald_cmu_pll_input_t input, ald_cmu_pll_output_t output)
{
    uint32_t cnt = 4000;

    assert_param(IS_CMU_PLL_INPUT(input));
    assert_param(IS_CMU_PLL_OUTPUT(output));

    SYSCFG_UNLOCK();

    if(READ_BITS(CMU->CSR, CMU_CSR_SYS_STU_MSK, CMU_CSR_SYS_STU_POSS) == ALD_CMU_CLOCK_PLL)
    {
        SET_BIT(CMU->CLKENR, CMU_CLKENR_HRC48MEN_MSK);

        for (cnt = 4000; cnt; --cnt);

        cnt = 4000;
        while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HRC48MACT_MSK))) && (--cnt));

        cnt = 4000;
        while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HRC48MRDY_MSK))) && (--cnt));

        MODIFY_REG(CMU->CSR, CMU_CSR_SYS_CMD_MSK, ALD_CMU_CLOCK_HRC48M << CMU_CSR_SYS_CMD_POSS);

        cnt = 4000;
        while (READ_BIT(CMU->CSR, CMU_CSR_SYS_RDYN_MSK) && (--cnt));
    }

    if (input == ALD_CMU_PLL_INPUT_HRC4M)
    {
        SET_BIT(CMU->CLKENR, CMU_CLKENR_HRC4MEN_MSK);
    }
    else
    {
        SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK);

        if(input == ALD_CMU_PLL_INPUT_HOSC4M)
        {
            MODIFY_REG(CMU->HOSCCFG, CMU_HOSCCFG_FREQ_MSK, 0);
        }
        else if(input == ALD_CMU_PLL_INPUT_HOSC8M)
        {
            MODIFY_REG(CMU->HOSCCFG, CMU_HOSCCFG_FREQ_MSK, 1);
        }
        else if(input == ALD_CMU_PLL_INPUT_HOSC16M)
        {
            /* HOSC > 12MHz, enable HOSC Bypass Filter */
            SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSCFLYBPS_MSK);
            MODIFY_REG(CMU->HOSCCFG, CMU_HOSCCFG_FREQ_MSK, 3);
        }

        cnt = 20000;
        while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_HOSCRDY_MSK))) && (--cnt));
    }

    CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_PLLEN_MSK);

    MODIFY_REG(CMU->PLLCFG, CMU_PLLCFG_REFS_MSK, input << CMU_PLLCFG_REFS_POSS);
    MODIFY_REG(CMU->PLLCFG, CMU_PLLCFG_CLKOS_MSK, output << CMU_PLLCFG_CLKOS_POSS);

    SET_BIT(CMU->PULMCR, CMU_PULMCR_EN_MSK);
    MODIFY_REG(CMU->PULMCR, CMU_PULMCR_MODE_MSK, 0x2 << CMU_PULMCR_MODE_POSS);

    SYSCFG_LOCK();
    return;
}

/**
  * @brief  Gets current system clock.
  * @retval The value of system clock.
  */
uint32_t ald_cmu_get_clock(void)
{
    return __system_clock;
}

/**
  * @}
  */

/**
  * @brief  Configure the bus division.
  * @param  bus: The type of bus:
  *          @arg CMU_SYS
  *          @arg CMU_PCLK
  * @param  div: The value of divider.
  * @retval None
  */
void ald_cmu_div_config(ald_cmu_bus_t bus, ald_cmu_div_t div)
{
    assert_param(IS_CMU_BUS(bus));
    assert_param(IS_CMU_DIV(div));

    SYSCFG_UNLOCK();

    switch (bus)
    {
        case ALD_CMU_SYS:
            MODIFY_REG(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, div << CMU_CFGR_SYSDIV_POSS);
            ald_tick_init(TICK_INT_PRIORITY);
            break;

        case ALD_CMU_PCLK:
            MODIFY_REG(CMU->CFGR, CMU_CFGR_PCLKDIV_MSK, div << CMU_CFGR_PCLKDIV_POSS);
            break;

        default:
            break;
    }

    SYSCFG_LOCK();
    return;
}

/**
  * @brief  Get SYS clock.
  * @retval The value of SYS clock.
  */
uint32_t ald_cmu_get_sys_clock(void)
{
    uint32_t sys_div = READ_BITS(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, CMU_CFGR_SYSDIV_POSS);

    return __system_clock >> sys_div;
}

/**
  * @brief  Get APB clock.
  * @retval The value of APB clock.
  */
uint32_t ald_cmu_get_pclk_clock(void)
{
    uint32_t sys_div  = READ_BITS(CMU->CFGR, CMU_CFGR_SYSDIV_MSK, CMU_CFGR_SYSDIV_POSS);
    uint32_t apb_div = READ_BITS(CMU->CFGR, CMU_CFGR_PCLKDIV_MSK, CMU_CFGR_PCLKDIV_POSS);

    return (__system_clock >> sys_div) >> apb_div;
}

/**
  * @}
  */

/** @defgroup CMU_Public_Functions_Group3 Clock safe configure
  * @brief    Clock safe configure functions
  *
  * @verbatim
  ==============================================================================
              ##### Clock safe configure functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Enable/Disable outer high crystal safe mode.
      (+) Enable/Disable outer low crystal safe mode.
      (+) Enable/Disable PLL safe mode.
      (+) Interrupt callback function.

    @endverbatim
  * @{
  */

/**
  * @brief  Enable/Disable outer high crystal safe mode.
  * @param  clock: the value of outer crystal frequency.
  * @param  status: The new status.
  * @retval None
  */
void ald_cmu_hosc_safe_config(ald_cmu_hosc_range_t clock, type_func_t status)
{
    assert_param(IS_CMU_HOSC_RANGE(clock));
    assert_param(IS_FUNC_STATE(status));

    SYSCFG_UNLOCK();

    if (status)
    {
        SET_BIT(CMU->HOSMCR, CMU_HOSMCR_STPIF_MSK);
        MODIFY_REG(CMU->HOSMCR, CMU_HOSMCR_FRQS_MSK, clock << CMU_HOSMCR_FRQS_POSS);
        SET_BIT(CMU->HOSMCR, CMU_HOSMCR_EN_MSK);
        SET_BIT(CMU->HOSMCR, CMU_HOSMCR_STPIE_MSK);

        ald_mcu_irq_config(CMU_IRQn, 3, ENABLE);
    }
    else
    {
        CLEAR_BIT(CMU->HOSMCR, CMU_HOSMCR_EN_MSK);
        CLEAR_BIT(CMU->HOSMCR, CMU_HOSMCR_STPIE_MSK);

        if (READ_BIT(CMU->PULMCR, CMU_PULMCR_EN_MSK) == 0)
            ald_mcu_irq_config(CMU_IRQn, 3, DISABLE);
    }

    SYSCFG_LOCK();
    return;
}

/**
  * @brief  Enable/Disable PLL1 safe mode.
  * @param  status: The new status.
  * @retval None
  */
void ald_cmu_pll_safe_config(type_func_t status)
{
    assert_param(IS_FUNC_STATE(status));
    SYSCFG_UNLOCK();

    if (status)
    {
        SET_BIT(CMU->PULMCR, CMU_PULMCR_ULKIF_MSK);
        MODIFY_REG(CMU->PULMCR, CMU_PULMCR_MODE_MSK, 2 << CMU_PULMCR_MODE_POSS);
        SET_BIT(CMU->PULMCR, CMU_PULMCR_EN_MSK);
        SET_BIT(CMU->PULMCR, CMU_PULMCR_ULKIE_MSK);

        ald_mcu_irq_config(CMU_IRQn, 3, ENABLE);
    }
    else
    {
        CLEAR_BIT(CMU->PULMCR, CMU_PULMCR_EN_MSK);
        CLEAR_BIT(CMU->PULMCR, CMU_PULMCR_ULKIE_MSK);

        if (READ_BIT(CMU->HOSMCR, CMU_HOSMCR_EN_MSK) == 0)
            ald_mcu_irq_config(CMU_IRQn, 3, DISABLE);
    }

    SYSCFG_LOCK();
    return;
}

/**
  * @brief  Get current clock source.
  * @retval Status:
  *              - 0: Current clock is PLL
  *              - 1: Current clock is HRC
  */
uint32_t ald_cmu_pulmcr_current_clock_source_get(void)
{
    return READ_BITS(CMU->PULMCR, CMU_PULMCR_CLKS_MSK, CMU_PULMCR_CLKS_POS);
}

/**
  * @brief  Get clock state.
  * @param  sr: The state type, see @ref cmu_clock_state_t.
  * @retval SET/RESET
  */
flag_status_t ald_cmu_get_clock_state(ald_cmu_clock_state_t sr)
{
    assert_param(IS_CMU_CLOCK_STATE(sr));

    if (READ_BIT(CMU->CLKSR, sr))
        return SET;

    return RESET;
}

/**
  * @brief  Interrupt callback function.
  * @note   This function is declared as __weak to be overwritten in case of other
  *         implementations in user file.
  * @retval None
  */
__weak void ald_cmu_irq_cbk(ald_cmu_security_t se)
{
    return;
}
/**
  * @}
  */

/** @defgroup CMU_Public_Functions_Group4 Clock output configure
  * @brief    Clock output configure functions
  *
  * @verbatim
  ==============================================================================
              ##### Clock output configure functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the high-speed clock output.
      (+) Configure the low-speed clock output.

    @endverbatim
  * @{
  */

/**
  * @brief  Configure the high-speed clock output.
  * @param  sel: Select the source:
  *           @arg CMU_OUTPUT_HIGH_SEL_HOSC
  *           @arg CMU_OUTPUT_HIGH_SEL_HOSM
  *           @arg CMU_OUTPUT_HIGH_SEL_HRC4M
  *           @arg CMU_OUTPUT_HIGH_SEL_LRC
  *           @arg CMU_OUTPUT_HIGH_SEL_SYSCLK
  *           @arg CMU_OUTPUT_HIGH_SEL_HOSC32K
  *           @arg CMU_OUTPUT_HIGH_SEL_HRC48M
  *           @arg CMU_OUTPUT_HIGH_SEL_PLL
  * @param  div: The value of divider:
  *           @arg CMU_OUTPUT_DIV_1
  *           @arg CMU_OUTPUT_DIV_2
  *           @arg CMU_OUTPUT_DIV_4
  *           @arg CMU_OUTPUT_DIV_8
  *           @arg CMU_OUTPUT_DIV_16
  *           @arg CMU_OUTPUT_DIV_32
  *           @arg CMU_OUTPUT_DIV_64
  *           @arg CMU_OUTPUT_DIV_128
  * @param  status: The new status.
  * @retval None
  */
void ald_cmu_output_high_clock_config(ald_cmu_output_high_sel_t sel,
        ald_cmu_output_high_div_t div, type_func_t status)
{
    assert_param(IS_CMU_OUTPUT_HIGH_SEL(sel));
    assert_param(IS_CMU_OUTPUT_HIGH_DIV(div));
    assert_param(IS_FUNC_STATE(status));

    SYSCFG_UNLOCK();

    if (status)
    {
        MODIFY_REG(CMU->CLKOCR, CMU_CLKOCR_HSCOS_MSK, sel << CMU_CLKOCR_HSCOS_POSS);
        MODIFY_REG(CMU->CLKOCR, CMU_CLKOCR_HSCODIV_MSK, div << CMU_CLKOCR_HSCODIV_POSS);
        SET_BIT(CMU->CLKOCR, CMU_CLKOCR_HSCOEN_MSK);
    }
    else
    {
        CLEAR_BIT(CMU->CLKOCR, CMU_CLKOCR_HSCOEN_MSK);
    }

    SYSCFG_LOCK();
    return;
}

/**
  * @brief  Configure the low-speed clock output.
  * @param  sel: Select the source:
  *           @arg CMU_OUTPUT_LOW_SEL_LRC
  *           @arg CMU_OUTPUT_LOW_SEL_BUZZ
  * @param  status: The new status.
  * @retval None
  */
void ald_cmu_output_low_clock_config(ald_cmu_output_low_sel_t sel, type_func_t status)
{
    assert_param(IS_CMU_OUTPUT_LOW_SEL(sel));
    assert_param(IS_FUNC_STATE(status));

    SYSCFG_UNLOCK();

    if (status)
    {
        MODIFY_REG(CMU->CLKOCR, CMU_CLKOCR_LSCOS_MSK, sel << CMU_CLKOCR_LSCOS_POSS);
        SET_BIT(CMU->CLKOCR, CMU_CLKOCR_LSCOEN_MSK);
    }
    else
    {
        CLEAR_BIT(CMU->CLKOCR, CMU_CLKOCR_LSCOEN_MSK);
    }

    SYSCFG_LOCK();
    return;
}
/**
  * @}
  */

/** @defgroup CMU_Public_Functions_Group5 Peripheral Clock configure
  * @brief    Peripheral clock configure functions
  *
  * @verbatim
  ==============================================================================
              ##### Peripheral clock configure functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure buzz clock.
      (+) Enable/Disable peripheral clock.

    @endverbatim
  * @{
  */

/**
  * @brief  Configure buzz clock.
  *         freq = sysclk / (2^(div + 1) * (dat + 1))
  * @param  div: The value of divider.
  * @param  dat: The value of coefficient.
  * @param  status: The new status.
  * @retval None
  */
void ald_cmu_buzz_config(ald_cmu_buzz_div_t div, uint16_t dat, type_func_t status)
{
    assert_param(IS_CMU_BUZZ_DIV(div));
    assert_param(IS_FUNC_STATE(status));

    SYSCFG_UNLOCK();

    if (status)
    {
        MODIFY_REG(CMU->BUZZCR, CMU_BUZZCR_DIV_MSK, div << CMU_BUZZCR_DIV_POSS);
        MODIFY_REG(CMU->BUZZCR, CMU_BUZZCR_DAT_MSK, dat << CMU_BUZZCR_DAT_POSS);
        SET_BIT(CMU->BUZZCR, CMU_BUZZCR_EN_MSK);
    }
    else
    {
        CLEAR_BIT(CMU->BUZZCR, CMU_BUZZCR_EN_MSK);
    }

    SYSCFG_LOCK();
    return;
}

/**
  * @brief  Enable/Disable peripheral clock.
  * @param  perh: The type of peripheral, you can see @ref cmu_perh_t
  * @param  status: The new status.
  * @retval None
  */
void ald_cmu_perh_clock_config(ald_cmu_perh_t perh, type_func_t status)
{
    uint32_t idx, pos;

    assert_param(IS_CMU_PERH(perh));
    assert_param(IS_FUNC_STATE(status));

    SYSCFG_UNLOCK();

    if (perh == ALD_CMU_PERH_ALL) {
        if (status) {
            WRITE_REG(CMU->AHBENR, ~0);
            WRITE_REG(CMU->APBENR, ~0);
        }
        else {
            WRITE_REG(CMU->AHBENR, 0);
            WRITE_REG(CMU->APBENR, 0);
        }

        SYSCFG_LOCK();
        return;
    }

    idx = ((uint32_t)perh >> 27) & 0x1;
    pos = perh & ~(0x1 << 27);

    if (status) {
        switch (idx) {
        case 0:
            SET_BIT(CMU->AHBENR, pos);
            break;

        case 1:
            SET_BIT(CMU->APBENR, pos);
            break;

        default:
            break;
        }
    }
    else {
        switch (idx) {
        case 0:
            CLEAR_BIT(CMU->AHBENR, pos);
            break;

        case 1:
            CLEAR_BIT(CMU->APBENR, pos);
            break;

        default:
            break;
        }
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
