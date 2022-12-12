/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_base.h"
#include <hal_bsp.h>

#if defined(RKMCU_RK2108)

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup PM
 *  @{
 */

/** @defgroup PM_How_To_Use How To Use
 *  @{

 The PM driver can be used as follows:

 - Invoke HAL_SYS_Suspend() when system will enter suspend.

 @} */

/** @defgroup PM_Private_Definition Private Definition
 *  @{
 */

/********************* Private MACRO Definition ******************************/

/* for pm_runtime */
#define SLEEP_INPUT_RATE     32000
#define EXPONENT_OF_FRAC_PLL 24
#define RK_PLL_MODE_SLOW     0
#define RK_PLL_MODE_NORMAL   1
#define RK_PLL_MODE_DEEP     2

#define PLL_POSTDIV1_SHIFT 12
#define PLL_POSTDIV1_MASK  0x7 << PLL_POSTDIV1_SHIFT
#define PLL_POSTDIV2_SHIFT 6
#define PLL_POSTDIV2_MASK  0x7 << PLL_POSTDIV2_SHIFT

#define PLL_GET_POSTDIV1(x) \
        (((uint32_t)(x) & (PLL_POSTDIV1_MASK)) >> PLL_POSTDIV1_SHIFT)
#define PLL_GET_POSTDIV2(x) \
    (((uint32_t)(x) & (PLL_POSTDIV2_MASK)) >> PLL_POSTDIV2_SHIFT)
#define UART_CLK_GET_MUX(clk) HAL_CRU_ClkGetMux(CLK_GET_MUX((clk)))
#define GPLL_RUNTIME_RATE     (PLL_INPUT_OSC_RATE * 2)

#define PVTM_KHZ          (1000)
#define PVTM_CALC_CNT_KHZ (PLL_INPUT_OSC_RATE / PVTM_KHZ)
#define PVTM_TARGET_KHZ   (32)
#define PVTM_CALC_CNT     0x200

#define SLEEP_COUNT_TO_MS(ms) (ms * SLEEP_INPUT_RATE / 1000)
/********************* Private Structure Definition **************************/
struct UART_REG_SAVE {
    uint32_t DLL;
    uint32_t DLH;
    uint32_t IER;
    uint32_t LCR;
    uint32_t MCR;
};
/********************* Private Variable Definition ***************************/
HAL_UNUSED static uint64_t pmTimerLastCount;
HAL_UNUSED static uint64_t pmTimerLowCount;
HAL_UNUSED static uint32_t pmIRQPendingFlag;

#if defined(HAL_PM_RUNTIME_MODULE_ENABLED) || defined(HAL_PM_SLEEP_MODULE_ENABLED)
static uint8_t pvtm32kEn = 0;
#endif
/********************* Private Function Definition ***************************/
#if defined(HAL_PM_RUNTIME_MODULE_ENABLED) || defined(HAL_PM_SLEEP_MODULE_ENABLED)
static void PVTM_ClkEnable(void)
{
    struct GRF_REG *pGrf = GRF;

    pGrf->PVTM_CON0 = VAL_MASK_WE(GRF_PVTM_CON0_PVTM_OSC_EN_MASK,
                                  GRF_PVTM_CON0_PVTM_OSC_EN_MASK);
}

static void PVTM_ClkDisable(void)
{
    struct GRF_REG *pGrf = GRF;

    pGrf->PVTM_CON0 = VAL_MASK_WE(GRF_PVTM_CON0_PVTM_OSC_EN_MASK,
                                  0);
}

static void PVTM_ClkRateConfig(uint32_t khz)
{
    uint32_t pvtm_freq_khz, pvtm_div;
    struct GRF_REG *pGrf = GRF;

    pGrf->PVTM_CON0 = 0xffff0000;
    PVTM_ClkEnable();

    pGrf->PVTM_CON1 = PVTM_CALC_CNT;

    pGrf->PVTM_CON0 = VAL_MASK_WE(GRF_PVTM_CON0_PVTM_START_MASK,
                                  GRF_PVTM_CON0_PVTM_START_MASK);

    /* pmugrf_pvtm_st0 will be clear after PVTM start,
     * which will cost about 6 cycles of pvtm at least.
     * So we wait 30 cycles of pvtm for security.
     */
    while (pGrf->PVTM_STATUS1 < 30) {
        ;
    }
    while (!(pGrf->PVTM_STATUS0 & GRF_PVTM_STATUS0_PVTM_FREQ_DONE_MASK)) {
        ;
    }

    pvtm_freq_khz =
        ((pGrf->PVTM_STATUS1) * PVTM_CALC_CNT_KHZ + PVTM_CALC_CNT / 2) / PVTM_CALC_CNT;
    pvtm_div = (pvtm_freq_khz + khz / 2) / khz;

    if (pvtm_div > 0xfff) {
        pvtm_div = 0xfff;
    }

    pGrf->PVTM_CON0 = VAL_MASK_WE(GRF_PVTM_CON0_PVTM_START_MASK,
                                  0);
    pGrf->PVTM_CON0 = VAL_MASK_WE(GRF_PVTM_CON0_PVTM_CLKOUT_DIV_MASK,
                                  pvtm_div << GRF_PVTM_CON0_PVTM_CLKOUT_DIV_SHIFT);
}
#endif

#ifdef HAL_PM_RUNTIME_MODULE_ENABLED
static uint32_t PM_GetPllPostDivEven(uint32_t rateIn, uint32_t rateOut, uint32_t *postDiv1, uint32_t *postDiv2)
{
    uint32_t div1, div2, div;

    div = rateIn / rateOut;
    if (div < 7) {
        *postDiv1 = div;
        *postDiv2 = 1;

        return 0;
    }

    for (div2 = 2; div2 <= 6;) {
        div1 = div / div2;
        if (div1 <= 7) {
            break;
        }
        div2 += 2;
    }
    if (div1 < div2) {
        return 2;
    }

    *postDiv1 = div1;
    *postDiv2 = div2;

    if ((div1 * div2) != div) {
        return 1;
    } else {
        return 0;
    }
}

static void PM_CruAsEnable(uint8_t en)
{
#ifdef HAL_CRU_AS_FEATURE_ENABLED
    HAL_CRU_AsEnable(1, en);
    HAL_CRU_AsEnable(2, en);
    HAL_CRU_AsEnable(3, en);
    HAL_CRU_AsEnable(4, en);
#endif
}

static uint32_t PM_RuntimeEnter(ePM_RUNTIME_idleMode idleMode)
{
    uint32_t gpllCon1, gpllDiv2, gpllDiv2New;
    uint32_t gpllCon0 = 0, gpllDiv1, gpllDiv1New;
    uint32_t clkSelCon2 = 0, clkSelCon33 = 0, clkSelCon40 = 0;
    uint32_t cruMode;
    uint32_t gpllRateNew;
    uint32_t mDiv;
    static uint32_t gpllRate;
    const struct PM_RUNTIME_INFO *pdata = HAL_PM_RuntimeGetData();

#ifdef HAL_WDT_DYNFREQ_FEATURE_ENABLED
    uint32_t tmpDiv;
    static uint32_t pmDynWdtFreqNor;
    static uint32_t pmWdtFreq;
    static uint32_t pmDynWdtFreq;
#endif

    if (PM_DISPLAY_REQUESTED(pdata)) {
        return HAL_BIT(PM_RUNTIME_TYPE_DISPLAY);
    }

    if (PM_UART_REQUESTED(pdata)) {
        if ((PM_UART_REQUESTED(pdata) & HAL_BIT(0)) &&
            (UART_CLK_GET_MUX(CLK_UART0) != SCLK_UART0_SEL_XIN_OSC0_FUNC)) {
            return HAL_BIT(PM_RUNTIME_TYPE_UART);
        } else if ((PM_UART_REQUESTED(pdata) & HAL_BIT(1)) &&
                   (UART_CLK_GET_MUX(CLK_UART1) != SCLK_UART1_SEL_XIN_OSC0_FUNC)) {
            return HAL_BIT(PM_RUNTIME_TYPE_UART);
        } else if ((PM_UART_REQUESTED(pdata) & HAL_BIT(2)) &&
                   (UART_CLK_GET_MUX(CLK_UART2) != SCLK_UART2_SEL_XIN_OSC0_FUNC)) {
            return HAL_BIT(PM_RUNTIME_TYPE_UART);
        }
    }

    if (PM_I2C_REQUESTED(pdata)) {
        return HAL_BIT(PM_RUNTIME_TYPE_I2C);
    }

    if (PM_HS_INTF_REQUESTED(pdata)) {
        return HAL_BIT(PM_RUNTIME_TYPE_HS_INTF);
    }

    if (PM_SPI_REQUESTED(pdata)) {
        return HAL_BIT(PM_RUNTIME_TYPE_SPI);
    }

    if (idleMode == PM_RUNTIME_IDLE_DEEP1) {
        if (!pvtm32kEn) {
            PVTM_ClkRateConfig(PVTM_TARGET_KHZ / 8);
            pvtm32kEn = 1;
        } else {
            PVTM_ClkEnable();
        }
    }

    PM_CruAsEnable(0);
    if (!gpllRate) {
        gpllRate = HAL_CRU_ClkGetFreq(PLL_GPLL);
    }

#ifdef HAL_WDT_DYNFREQ_FEATURE_ENABLED
    if (!pmWdtFreq) {
        pmWdtFreq = HAL_CRU_ClkGetFreq(PCLK_WDT);
        tmpDiv = (gpllRate / pmWdtFreq);
        pmDynWdtFreq = PLL_INPUT_OSC_RATE / tmpDiv;
        pmDynWdtFreqNor = GPLL_RUNTIME_RATE / tmpDiv;
    }
#endif
    if (idleMode == PM_RUNTIME_IDLE_DEEP || idleMode == PM_RUNTIME_IDLE_DEEP1) {
        cruMode = CRU->CRU_MODE_CON00 |
                  MASK_TO_WE(CRU_CRU_MODE_CON00_CLK_GPLL_MODE_MASK);
        gpllCon1 = CRU->GPLL_CON[1] |
                   MASK_TO_WE(CRU_GPLL_CON1_PLLPD0_MASK);

        clkSelCon33 = CRU->CRU_CLKSEL_CON[33] |
                      MASK_TO_WE(CRU_CRU_CLKSEL_CON33_HCLK_M4_DIV_MASK);
        clkSelCon2 = CRU->CRU_CLKSEL_CON[2] |
                     MASK_TO_WE(CRU_CRU_CLKSEL_CON02_SCLK_SHRM_DIV_MASK);
        clkSelCon40 = CRU->CRU_CLKSEL_CON[40] |
                      MASK_TO_WE(CRU_CRU_CLKSEL_CON40_ACLK_LOGIC_DIV_MASK);

        CRU->CRU_MODE_CON00 =
            VAL_MASK_WE(CRU_CRU_MODE_CON00_CLK_GPLL_MODE_MASK,
                        RK_PLL_MODE_SLOW << CRU_CRU_MODE_CON00_CLK_GPLL_MODE_SHIFT);

        CRU->CRU_CLKSEL_CON[33] =
            VAL_MASK_WE(CRU_CRU_CLKSEL_CON33_HCLK_M4_DIV_MASK, 0);
        CRU->CRU_CLKSEL_CON[2] =
            VAL_MASK_WE(CRU_CRU_CLKSEL_CON02_SCLK_SHRM_DIV_MASK, 0);
        CRU->CRU_CLKSEL_CON[40] =
            VAL_MASK_WE(CRU_CRU_CLKSEL_CON40_ACLK_LOGIC_DIV_MASK, 0);

        HAL_ASSERT(!(CRU->GPLL_CON[1] & CRU_GPLL_CON1_PLLPD0_MASK));
        HAL_ASSERT(!(CRU->GPLL_CON[1] & CRU_GPLL_CON1_PLLPDSEL_MASK));

#ifdef HAL_WDT_DYNFREQ_FEATURE_ENABLED
        HAL_WDT_DynFreqUpdata(pmDynWdtFreq);
#endif

        CRU->GPLL_CON[1] = VAL_MASK_WE(CRU_GPLL_CON1_PLLPD0_MASK,
                                       CRU_GPLL_CON1_PLLPD0_MASK);

        if (idleMode == PM_RUNTIME_IDLE_DEEP1) {
            CRU->CRU_MODE_CON00 =
                VAL_MASK_WE(CRU_CRU_MODE_CON00_CLK_GPLL_MODE_MASK,
                            RK_PLL_MODE_DEEP << CRU_CRU_MODE_CON00_CLK_GPLL_MODE_SHIFT);
        }
    } else if (idleMode == PM_RUNTIME_IDLE_NORMAL) {
        cruMode = 0;
        clkSelCon2 = 0;

        HAL_ASSERT(HAL_CRU_ClkGetFreq(HCLK_M4) > GPLL_RUNTIME_RATE);
        gpllRate = HAL_CRU_ClkGetFreq(PLL_GPLL);

        gpllCon1 = CRU->GPLL_CON[1] |
                   MASK_TO_WE(CRU_GPLL_CON1_POSTDIV2_MASK);
        gpllCon0 = CRU->GPLL_CON[0] |
                   MASK_TO_WE(CRU_GPLL_CON0_POSTDIV1_MASK);

        gpllDiv1 = PLL_GET_POSTDIV1(gpllCon0);
        gpllDiv2 = PLL_GET_POSTDIV2(gpllCon1);

        gpllRate = (gpllRate * gpllDiv1 * gpllDiv2);

        if (PM_GetPllPostDivEven(gpllRate, GPLL_RUNTIME_RATE, &gpllDiv1New, &gpllDiv2New) >= 2) {
            return UINT32_MAX;
        }

        gpllRateNew = gpllRate / (gpllDiv1New * gpllDiv2New);
        mDiv = gpllRateNew / GPLL_RUNTIME_RATE;

        HAL_ASSERT(mDiv > 0);
        HAL_ASSERT((gpllRateNew * mDiv) >= GPLL_RUNTIME_RATE);

        if (mDiv > 0) {
            mDiv -= 1;
        }

#ifdef HAL_WDT_DYNFREQ_FEATURE_ENABLED
        HAL_WDT_DynFreqUpdata(pmDynWdtFreqNor);
#endif

        clkSelCon33 = CRU->CRU_CLKSEL_CON[33] |
                      MASK_TO_WE(CRU_CRU_CLKSEL_CON33_HCLK_M4_DIV_MASK);

        CRU->GPLL_CON[0] = VAL_MASK_WE(CRU_GPLL_CON0_POSTDIV1_MASK,
                                       gpllDiv1New << CRU_GPLL_CON0_POSTDIV1_SHIFT);

        CRU->GPLL_CON[1] = VAL_MASK_WE(CRU_GPLL_CON1_POSTDIV2_MASK,
                                       gpllDiv2New << CRU_GPLL_CON1_POSTDIV2_SHIFT);

        CRU->CRU_CLKSEL_CON[33] = VAL_MASK_WE(CRU_CRU_CLKSEL_CON33_HCLK_M4_DIV_MASK,
                                              mDiv << CRU_CRU_CLKSEL_CON33_HCLK_M4_DIV_SHIFT);
    } else {
        goto _ret_err;
    }

    __DSB();
    __WFI();

    if (idleMode == PM_RUNTIME_IDLE_DEEP || idleMode == PM_RUNTIME_IDLE_DEEP1) {
        CRU->GPLL_CON[1] = gpllCon1;
        CRU->CRU_CLKSEL_CON[33] = clkSelCon33;
        CRU->CRU_CLKSEL_CON[2] = clkSelCon2;
        CRU->CRU_CLKSEL_CON[40] = clkSelCon40;

        while ((CRU->GPLL_CON[1] & CRU_CPLL_CON1_PLL_LOCK_MASK) !=
               CRU_CPLL_CON1_PLL_LOCK_MASK) {
            ;
        }
        CRU->CRU_MODE_CON00 = cruMode;
        if (idleMode == PM_RUNTIME_IDLE_DEEP1) {
            PVTM_ClkDisable();
        }
    } else if (idleMode == PM_RUNTIME_IDLE_NORMAL) {
        CRU->CRU_CLKSEL_CON[33] = clkSelCon33;
        CRU->GPLL_CON[1] = gpllCon1;
        CRU->GPLL_CON[0] = gpllCon0;
    }
#ifdef HAL_WDT_DYNFREQ_FEATURE_ENABLED
    HAL_WDT_DynFreqResume();
#endif

    PM_CruAsEnable(1);

    return 0;
_ret_err:

    return UINT32_MAX;
}

uint32_t HAL_PM_RuntimeEnter(ePM_RUNTIME_idleMode idleMode)
{
    uint32_t ret;

    if (idleMode) {
        ret = PM_RuntimeEnter(idleMode);
    } else {
        ret = UINT32_MAX;
    }

    if (!idleMode || ret) {
        __DSB();
        __WFI();
    }

    return ret;
}

#endif

#ifdef HAL_PM_SLEEP_MODULE_ENABLED
HAL_UNUSED static void SOC_GetWakeupStatus(struct PMU_REG *pPmu)
{
    HAL_DBG("\nwakeup source:\n");
    if (pPmu->WAKEUP_STATUS & (1 << PMU_WAKEUP_STATUS_WAKEUP_PWRMODE_INT_STATUS_SHIFT)) {
        HAL_DBG("\tPower mode state machine wakeup status by interrupt\n");
    }
    if (pPmu->WAKEUP_STATUS & (1 << PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_GPIO_INT_STATUS_SHIFT)) {
        HAL_DBG("\tPower mode state machine wakeup status by gpio interrupt\n");
    }
    if (pPmu->WAKEUP_STATUS & (1 << PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_TIMEOUT_STATUS_SHIFT)) {
        HAL_DBG("\tPower mode state machine wakeup status by timeout\n");
    }
    if (pPmu->WAKEUP_STATUS & (1 << PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_DSP_SFT_STATUS_SHIFT)) {
        HAL_DBG("\tPower mode state machine wakeup status by DSP software\n");
    }
    if (pPmu->WAKEUP_STATUS & (1 << PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_TIMER_STATUS_SHIFT)) {
        HAL_DBG("\tPower mode state machine wakeup status by timer interrupt\n");
    }
    if (pPmu->WAKEUP_STATUS & (1 << PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_VAD_STATUS_SHIFT)) {
        HAL_DBG("\tPower mode state machine wakeup status by vad\n");
    }
    if (pPmu->WAKEUP_STATUS & (1 << PMU_WAKEUP_STATUS_WAKEUP_DSP_INT_STATUS_SHIFT)) {
        HAL_DBG("\tDSP auto power down state machine wakeup status by interrupt\n");
    }
    if (pPmu->WAKEUP_STATUS & (1 << PMU_WAKEUP_STATUS_DSP_WAKEUP_GPIO_INT_STATUS_SHIFT)) {
        HAL_DBG("\tDSP auto power down state machine wakeup status by gpio interrupt\n");
    }
    if (pPmu->WAKEUP_STATUS & (1 << PMU_WAKEUP_STATUS_DSP_WAKEUP_TIMEOUT_STATUS_SHIFT)) {
        HAL_DBG("\tDSP auto power down state machine wakeup status by timeout\n");
    }
    if (pPmu->WAKEUP_STATUS & (1 << PMU_WAKEUP_STATUS_DSP_WAKEUP_SFT_STATUS_SHIFT)) {
        HAL_DBG("\tDSP auto power down state machine wakeup status by MCU software\n");
    }
    if (pPmu->WAKEUP_STATUS & (1 << PMU_WAKEUP_STATUS_DSP_WAKEUP_TIMER_STATUS_SHIFT)) {
        HAL_DBG("\tauto power down state machine wakeup status by timer\n");
    }
    if (pPmu->WAKEUP_STATUS & (1 << PMU_WAKEUP_STATUS_DSP_WAKEUP_VAD_STATUS_SHIFT)) {
        HAL_DBG("\tDSP auto power down state machine wakeup status by vad\n");
    }

    pPmu->WAKEUP_STATUS = (1 << PMU_WAKEUP_STATUS_WAKEUP_PWRMODE_INT_STATUS_SHIFT) |
                          (1 << PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_GPIO_INT_STATUS_SHIFT) |
                          (1 << PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_TIMEOUT_STATUS_SHIFT) |
                          (1 << PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_DSP_SFT_STATUS_SHIFT) |
                          (1 << PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_TIMER_STATUS_SHIFT) |
                          (1 << PMU_WAKEUP_STATUS_PWRMODE_WAKEUP_VAD_STATUS_SHIFT) |
                          (1 << PMU_WAKEUP_STATUS_WAKEUP_DSP_INT_STATUS_SHIFT) |
                          (1 << PMU_WAKEUP_STATUS_DSP_WAKEUP_GPIO_INT_STATUS_SHIFT) |
                          (1 << PMU_WAKEUP_STATUS_DSP_WAKEUP_TIMEOUT_STATUS_SHIFT) |
                          (1 << PMU_WAKEUP_STATUS_DSP_WAKEUP_SFT_STATUS_SHIFT) |
                          (1 << PMU_WAKEUP_STATUS_DSP_WAKEUP_TIMER_STATUS_SHIFT) |
                          (1 << PMU_WAKEUP_STATUS_DSP_WAKEUP_VAD_STATUS_SHIFT);
}

HAL_UNUSED static void SOC_FastBootEnable(struct GRF_REG *pGrf)
{
#ifdef HAL_PM_CPU_SLEEP_MODULE_ENABLED
    pGrf->FAST_BOOT_ADDR = (uint32_t)HAL_CPU_DoResume;
    pGrf->FAST_BOOT_EN = 1;
#endif
}

HAL_UNUSED static void SOC_FastBootDisable(struct GRF_REG *pGrf)
{
#ifdef HAL_PM_CPU_SLEEP_MODULE_ENABLED
    pGrf->FAST_BOOT_EN = 0;
#endif
}

HAL_UNUSED static void SOC_SleepModeInit(struct PMU_REG *pPmu)
{
    uint32_t mask = 0, value = 0;

    mask = PMU_PWRMODE_CON_POWER_MODE_EN_MASK |
           PMU_PWRMODE_CON_OSC_DISABLE_MASK |
           PMU_PWRMODE_CON_PMU_USE_LF_MASK |
           PMU_PWRMODE_CON_PLL_PD_EN_MASK |
           PMU_PWRMODE_CON_LOGIC_PD_EN_MASK |
           PMU_PWRMODE_CON_PWRMODE_LDO_ADJ_EN_MASK |
           PMU_PWRMODE_CON_BYPASS_PLL_LOCK_MASK |
           PMU_PWRMODE_CON_BYPASS_HF_EN_MASK |
           PMU_PWRMODE_CON_GLOBAL_INT_DISABLE_CFG_MASK |
           PMU_PWRMODE_CON_SHRM_PD_EN_MASK |
           PMU_PWRMODE_CON_SHRM_MEM_RETPD_EN_MASK;

    value = (1 << PMU_PWRMODE_CON_POWER_MODE_EN_SHIFT) |
            /*(1 << PMU_PWRMODE_CON_PMU_USE_LF_SHIFT) |*/
            (1 << PMU_PWRMODE_CON_PLL_PD_EN_SHIFT) |
            (1 << PMU_PWRMODE_CON_LOGIC_PD_EN_SHIFT) |
            (1 << PMU_PWRMODE_CON_PWRMODE_LDO_ADJ_EN_SHIFT) |
            /*(1 << PMU_PWRMODE_CON_BYPASS_PLL_LOCK_SHIFT) |*/
            /*(1 << PMU_PWRMODE_CON_BYPASS_HF_EN_SHIFT) |*/
            (1 << PMU_PWRMODE_CON_SHRM_PD_EN_SHIFT) |
            (1 << PMU_PWRMODE_CON_SHRM_MEM_RETPD_EN_SHIFT);

    /* if PD_DSP and PD_AUDIO power down, PMU low frequency mode enable */
    if (pPmu->PWRDN_ST &
        ((1 << PMU_PWRDN_ST_PD_AUDIO_PWR_STAT_SHIFT) | (1 << PMU_PWRDN_ST_PD_DSP_PWR_STAT_SHIFT))) {
        value |= (1 << PMU_PWRMODE_CON_PMU_USE_LF_SHIFT) |
                 (1 << PMU_PWRMODE_CON_OSC_DISABLE_SHIFT);
        pPmu->PWRMODE_LDO_ADJ_CNT = SLEEP_COUNT_TO_MS(1);
        pPmu->PLLLOCK_CNT = SLEEP_COUNT_TO_MS(1);
        pPmu->DSP_LDO_ADJ_CNT = SLEEP_COUNT_TO_MS(1);
        pPmu->OSC_CNT = SLEEP_COUNT_TO_MS(1);

        if (!pvtm32kEn) {
            PVTM_ClkRateConfig(PVTM_TARGET_KHZ);
            pvtm32kEn = 1;
        } else {
            PVTM_ClkEnable();
        }
    }
    pPmu->PWRMODE_CON = VAL_MASK_WE(mask, value);

    if (pPmu->PWRMODE_CON & (1 << PMU_PWRMODE_CON_LOGIC_PD_EN_SHIFT)) {
        mask = PMU_BUS_CLR_CLR_LOGIC_MASK;
        value = (1 << PMU_BUS_CLR_CLR_LOGIC_SHIFT);
        pPmu->BUS_CLR |= VAL_MASK_WE(mask, value);
    }

    if (pPmu->PWRMODE_CON & (1 << PMU_PWRMODE_CON_SHRM_MEM_RETPD_EN_SHIFT)) {
        mask = PMU_SHRM_CON1_PWRMODE_SHRM_PWRDWN_EN_MASK |
               PMU_SHRM_CON1_PWRMODE_SHRM_RET2N_MASK;
        value = (0xf << PMU_SHRM_CON1_PWRMODE_SHRM_PWRDWN_EN_SHIFT);
        pPmu->SHRM_CON1 = VAL_MASK_WE(mask, value);

        mask = PMU_BUS_CLR_CLR_SHRM_MASK;
        value = (1 << PMU_BUS_CLR_CLR_SHRM_SHIFT);
        pPmu->BUS_CLR |= VAL_MASK_WE(mask, value);
    }

    if (pPmu->PWRMODE_CON & (1 << PMU_PWRMODE_CON_PWRMODE_LDO_ADJ_EN_SHIFT)) {
        mask = PMU_LDO_CON1_PWRMODE_LDOCORE_ADJ_MASK;
        pPmu->LDO_CON[1] = VAL_MASK_WE(mask, 0x10);
    }

    if (pPmu->PWRMODE_CON & (1 << PMU_PWRMODE_CON_PLL_PD_EN_SHIFT)) {
        mask = PMU_PLL_CON_PLL_PD_CFG_MASK;
        /* if PD_DSP and PD_AUDIO power down, CPLL, GPLL and 32K PLL power down by hardware */
        if (pPmu->PWRDN_ST &
            ((1 << PMU_PWRDN_ST_PD_AUDIO_PWR_STAT_SHIFT) | (1 << PMU_PWRDN_ST_PD_DSP_PWR_STAT_SHIFT))) {
            pPmu->PLL_CON = VAL_MASK_WE(mask, 0x07);
        } else {
            pPmu->PLL_CON = VAL_MASK_WE(mask, 0x05);
        }
    }

    if (pPmu->PWRMODE_CON & (1 << PMU_PWRMODE_CON_PMU_USE_LF_SHIFT)) {
        mask = PMU_SFT_CON_PMU_LF_MODE_CFG_MASK;
        value = (1 << PMU_SFT_CON_PMU_LF_MODE_CFG_SHIFT);
        pPmu->SFT_CON = VAL_MASK_WE(mask, value);
    }
}

HAL_UNUSED static void SOC_WakeupSourceConfig(struct PMU_REG *pPmu)
{
    uint32_t mask = 0, value = 0;

    mask = PMU_WAKEUP_CFG6_GPIO_INT_EN_MASK |
           PMU_WAKEUP_CFG6_TIMER_EN_MASK;
    value = (1 << PMU_WAKEUP_CFG6_GPIO_INT_EN_SHIFT) |
            (1 << PMU_WAKEUP_CFG6_TIMER_EN_SHIFT);
    pPmu->WAKEUP_CFG6 = VAL_MASK_WE(mask, value);
}

HAL_UNUSED static void SOC_SleepModeReinit(struct PMU_REG *pPmu)
{
    uint32_t mask = 0, value = 0;

    mask = PMU_PWRMODE_CON_POWER_MODE_EN_MASK |
           PMU_PWRMODE_CON_PLL_PD_EN_MASK |
           PMU_PWRMODE_CON_LOGIC_PD_EN_MASK |
           PMU_PWRMODE_CON_PWRMODE_LDO_ADJ_EN_MASK |
           PMU_PWRMODE_CON_BYPASS_PLL_LOCK_MASK |
           PMU_PWRMODE_CON_BYPASS_HF_EN_MASK |
           PMU_PWRMODE_CON_GLOBAL_INT_DISABLE_CFG_MASK |
           PMU_PWRMODE_CON_SHRM_PD_EN_MASK |
           PMU_PWRMODE_CON_SHRM_MEM_RETPD_EN_MASK;
    pPmu->PWRMODE_CON = VAL_MASK_WE(mask, value);
    if (pPmu->PWRDN_ST &
        ((1 << PMU_PWRDN_ST_PD_AUDIO_PWR_STAT_SHIFT) | (1 << PMU_PWRDN_ST_PD_DSP_PWR_STAT_SHIFT))) {
        PVTM_ClkDisable();
    }
}

HAL_UNUSED static void SOC_PutChar(char c, struct UART_REG *pUart)
{
    if (pUart) {
        pUart->THR = c;
        while ((pUart->USR & UART_USR_BUSY)) {
            ;
        }
    }
}

HAL_UNUSED static void SOC_UartSave(struct UART_REG_SAVE *pUartSave, struct UART_REG *pUart)
{
    if (pUartSave && pUart) {
        while (!(pUart->USR & UART_USR_TX_FIFO_EMPTY)) {
            ;
        }
        pUartSave->LCR = pUart->LCR;
        pUartSave->IER = pUart->IER;
        pUartSave->MCR = pUart->MCR;
        if (pUart->USR & UART_USR_BUSY) {
            HAL_DelayMs(10);
        }
        if (pUart->USR & UART_USR_BUSY) {
            pUart->SRR = UART_SRR_XFR | UART_SRR_RFR;
        }
        pUart->LCR = UART_LCR_DLAB;
        pUartSave->DLL = pUart->DLL;
        pUartSave->DLH = pUart->DLH;
        pUart->LCR = pUartSave->LCR;
    }
}

HAL_UNUSED static void SOC_UartRestore(struct UART_REG_SAVE *pUartSave, struct UART_REG *pUart)
{
    if (pUartSave && pUart) {
        pUart->SRR = UART_SRR_XFR | UART_SRR_RFR | UART_SRR_UR;
        pUart->MCR = UART_MCR_LOOP;
        pUart->LCR = UART_LCR_DLAB;
        pUart->DLL = pUartSave->DLL;
        pUart->DLH = pUartSave->DLH;
        pUart->LCR = pUartSave->LCR;
        pUart->IER = pUartSave->IER;
        pUart->FCR = UART_FCR_ENABLE_FIFO;
        pUart->MCR = pUartSave->MCR;
    }
}

#ifdef HAL_PM_CPU_SLEEP_MODULE_ENABLED
static int SOC_SuspendEnter(uint32_t flag)
{
    HAL_DCACHE_CleanInvalidate();
    __WFI();

    /* The PD_LOGIC power down when in power mode, the code will not execute
     */
    pmIRQPendingFlag = 1;
    HAL_CPU_DoResume();

    return HAL_OK;
}
#endif

/** @} */
/********************* Public Function Definition ****************************/
/** @defgroup PM_Exported_Functions_Group5 Other Functions
 *  @{
 */

HAL_Status HAL_PM_TimerStart(uint64_t timeoutCount, bool needTimeout)
{
    pmTimerLastCount = HAL_GetSysTimerCount();
    pmTimerLowCount = 0;

    return 0;
}

HAL_Status HAL_PM_TimerStop(void)
{
    return 0;
}

uint64_t HAL_PM_GetTimerCount(void)
{
    return HAL_GetSysTimerCount() - pmTimerLastCount;
}

int HAL_SYS_Suspend(struct PM_SUSPEND_INFO *suspendInfo)
{
#ifdef HAL_PM_CPU_SLEEP_MODULE_ENABLED
    struct PMU_REG *pPmu = PMU;
    struct GRF_REG *pGrf = GRF;
    struct UART_REG *pUart = NULL;
    struct UART_REG_SAVE pUartSave = { 0 };
    uint64_t timerCount;

    HAL_ASSERT(suspendInfo != NULL);

#ifdef HAL_SYSTICK_MODULE_ENABLED
    SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);
#endif

#ifdef HAL_UART_MODULE_ENABLED
    if (suspendInfo->flag.uartValid) {
        if (suspendInfo->flag.uartChannel == 0) {
            pUart = UART0;
        } else if (suspendInfo->flag.uartChannel == 1) {
            pUart = UART1;
        } else if (suspendInfo->flag.uartChannel == 2) {
            pUart = UART2;
        }
    }
#endif

    SOC_PutChar('0', pUart);
    SOC_SleepModeInit(pPmu);
    SOC_PutChar('1', pUart);
    SOC_FastBootEnable(pGrf);
    SOC_PutChar('2', pUart);
    SOC_WakeupSourceConfig(pPmu);
    SOC_PutChar('3', pUart);
    HAL_NVIC_SuspendSave();
    SOC_PutChar('4', pUart);
    HAL_SCB_SuspendSave();
    SOC_PutChar('5', pUart);
    SOC_UartSave(&pUartSave, pUart);
    timerCount = HAL_GetSysTimerCount();
    HAL_CPU_SuspendEnter(suspendInfo->suspendFlag, SOC_SuspendEnter);
    pmTimerLowCount = HAL_GetSysTimerCount() - timerCount;
    SOC_SleepModeReinit(pPmu);
    SOC_UartRestore(&pUartSave, pUart);
    SOC_PutChar('5', pUart);
    if (pmIRQPendingFlag == 0) {
        SOC_PutChar('4', pUart);
        BSP_MPU_Init();
        HAL_DCACHE_Enable();
        HAL_DCACHE_EnableInt();
        HAL_ICACHE_Enable();
        HAL_ICACHE_EnableInt();
    }
    pmIRQPendingFlag = 0;
    SOC_PutChar('3', pUart);
    HAL_SCB_ResumeRestore();
    SOC_PutChar('2', pUart);
    HAL_NVIC_ResumeRestore();
    SOC_PutChar('1', pUart);
    SOC_GetWakeupStatus(pPmu);
    SOC_FastBootDisable(pGrf);
    SOC_PutChar('0', pUart);
#ifdef HAL_SYSTICK_MODULE_ENABLED
    HAL_SYSTICK_CLKSourceConfig(HAL_SYSTICK_CLKSRC_EXT);
    HAL_SYSTICK_Enable();
#endif

    HAL_DBG("\n");
#endif

    return HAL_OK;
}

/** @} */
#endif

/** @} */

/** @} */

#endif /* RKMCU_RK2108 */
