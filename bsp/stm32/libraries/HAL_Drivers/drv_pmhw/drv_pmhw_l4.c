/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2020-04-08     Sunwancn        first version
 */

#include <rtthread.h>

#if defined(RT_USING_PM)

#include <drv_pmhw.h>

/* ------------------ PM oscillator start ------------------ */
#if defined(PWR_CR5_R1MODE)
  /* STM32L4+ */
  #define OSC_CONF_SYS_FREQ_MAX       120U    /* Max system clock  MHz */
  #define OSC_CONF_SYS_FREQ_NORMAL    120U    /* Normal system clock  MHz */

  #define OSC_CONF_PLLM_FREQ_MIN      3U      /* Min pllm clock  MHz */
  #define OSC_CONF_PLLM_FREQ_MAX      8U      /* Max pllm clock  MHz */
  #define OSC_CONF_PLL_VCO_FREQ_MIN   64U     /* Min pll vco clock  MHz */
  #define OSC_CONF_PLL_VCO_FREQ_MAX   344U    /* Max pll vco clock  MHz */
  #define OSC_CONF_PLLM_DIV_MIN       1U      /* Min pllm divider */
  #define OSC_CONF_PLLM_DIV_MAX       16U     /* Max pllm divider */
  #define OSC_CONF_PLLN_MUL_MIN       8U      /* Min plln multiplier */
  #define OSC_CONF_PLLN_MUL_MAX       127U    /* Max plln multiplier */
  #define OSC_CONF_PLLR_DIV_MIN       2U      /* Min pllr divider */
  #define OSC_CONF_PLLR_DIV_MAX       8U      /* Max pllr divider */
  #define OSC_CONF_PLLQ_DIV_MIN       2U      /* Min pllq divider */
  #define OSC_CONF_PLLQ_DIV_MAX       8U      /* Max pllq divider */

  #define OSC_CONF_LOW_POW_RUN_FREQ   2U      /* Low-power Run mode frequency  MHz */
  #define PM_MSI_RANGE_MAX_NUMS       12U
  #define PM_POW_VOLT_SCALE_NUMS      3U
  #define FLASH_LATENCY_MAX_NUMS      6U
#else
  /* STM32L4 */
  #define OSC_CONF_SYS_FREQ_MAX       80U     /* Max system clock  MHz */
  #define OSC_CONF_SYS_FREQ_NORMAL    80U     /* Normal system clock  MHz */

  #define OSC_CONF_PLLM_FREQ_MIN      4U      /* Min pllm clock  MHz */
  #define OSC_CONF_PLLM_FREQ_MAX      16U     /* Max pllm clock  MHz */
  #define OSC_CONF_PLL_VCO_FREQ_MIN   64U     /* Min pll vco clock  MHz */
  #define OSC_CONF_PLL_VCO_FREQ_MAX   344U    /* Max pll vco clock  MHz */
  #define OSC_CONF_PLLM_DIV_MIN       1U      /* Min pllm divider */
  #define OSC_CONF_PLLM_DIV_MAX       8U      /* Max pllm divider */
  #define OSC_CONF_PLLN_MUL_MIN       8U      /* Min plln multiplier */
  #define OSC_CONF_PLLN_MUL_MAX       86U     /* Max plln multiplier */
  #define OSC_CONF_PLLR_DIV_MIN       2U      /* Min pllr divider */
  #define OSC_CONF_PLLR_DIV_MAX       8U      /* Max pllr divider */
  #define OSC_CONF_PLLQ_DIV_MIN       2U      /* Min pllq divider */
  #define OSC_CONF_PLLQ_DIV_MAX       8U      /* Max pllq divider */

  #define OSC_CONF_LOW_POW_RUN_FREQ   2U      /* Low-power Run mode frequency  MHz */
  #define PM_MSI_RANGE_MAX_NUMS       12U
  #define PM_POW_VOLT_SCALE_NUMS      2U
  #define FLASH_LATENCY_MAX_NUMS      5U
#endif

struct rcc_conf_struct
{
    rt_uint32_t mode;
    rt_uint32_t sysclk_source;
    rt_uint32_t clk48_source;
    rt_uint32_t pll_state;
    rt_uint32_t pllm;
    rt_uint32_t plln;
    rt_uint32_t pllr;
    rt_uint32_t pllq;
#if defined(RCC_PLLP_SUPPORT)
    rt_uint32_t pllp;
#endif
    rt_uint32_t ahb_div;
    rt_uint32_t latency;
    rt_uint32_t volt_scale;
    rt_uint32_t msi_range;
    rt_bool_t low_pow_run_en;
};
static struct rcc_conf_struct _rcc_conf[PM_RUN_MODE_MAX] = {0};

static struct osc_conf_struct
{
    rt_uint32_t init;
    rt_uint32_t osc_type;
    rt_uint32_t osc_freq;
}
_osc_conf = {0};

static void (* _set_sysclock[PM_RUN_MODE_MAX])(void) = {0};
static const rt_uint32_t _volt_scale_tab[PM_POW_VOLT_SCALE_NUMS][3] =
{
    /* voltage range, frequency step for flash latency, max HCLK */
#if defined(PWR_CR5_R1MODE)
    /* STM32L4+ */
    {PWR_REGULATOR_VOLTAGE_SCALE2,        8U,  26U},
    {PWR_REGULATOR_VOLTAGE_SCALE1,       20U,  80U},
    {PWR_REGULATOR_VOLTAGE_SCALE1_BOOST, 20U, 120U},
#else
    {PWR_REGULATOR_VOLTAGE_SCALE2,        6U,  26U},
    {PWR_REGULATOR_VOLTAGE_SCALE1,       16U,  80U},
#endif
};
static const rt_uint16_t _msi_range_tab[PM_MSI_RANGE_MAX_NUMS] =
{
    100U, 200U, 400U, 800U, 1000U, 2000U, 4000U, 8000U, 16000U, 24000U, 32000U, 48000U
};

RT_WEAK rt_uint16_t stm32_run_freq[PM_RUN_MODE_MAX][2] =
{
    /* The actual frequency is 1/divisor MHz, divisor = {1, 1000} */
    /* {sysclk frequency, divisor} */
    {OSC_CONF_SYS_FREQ_MAX,    1},    /* High speed */
    {OSC_CONF_SYS_FREQ_NORMAL, 1},    /* Normal speed */
    {24,                       1},    /* Medium speed */
    {2,                        1},    /* Low speed, MSI clock 2.0 MHz */
};

/* Get the greatest common divisor by Stein algorithm */
static rt_uint32_t get_stein_div(rt_uint32_t x, rt_uint32_t y)
{
    rt_uint32_t tmp, cnt = 0;

    RT_ASSERT(x > 0 && y > 0);

    /* bigger --> x, smaller --> y */
    if (x < y)
    {
        tmp = x;
        x = y;
        y = tmp;
    }

    while (x != y)
    {
        if (x & 1U)
        {
            if (y & 1U)
            {
                y = (x - y) >> 1U;
                x -= y;
            }
            else
            {
                y >>= 1U;
            }
        }
        else
        {
            if (y & 1U)
            {
                x >>= 1U;
                if (x < y)
                {
                    tmp = x;
                    x = y;
                    y = tmp;
                }
            }
            else
            {
                x >>= 1U;
                y >>= 1U;
                ++cnt;
            }
        }
    }
    return (x << cnt);
}

/* Find the MSI frequency(KHz) range */
static rt_uint32_t find_msi_range(rt_uint32_t freq, rt_uint32_t *rp)
{
    rt_uint32_t i;
    for (i = 0U; i < PM_MSI_RANGE_MAX_NUMS; i++)
    {
        if ((_msi_range_tab[i] >= freq) || (i == PM_MSI_RANGE_MAX_NUMS - 1U))
        {
            freq = _msi_range_tab[i];
            *rp = i << RCC_CR_MSIRANGE_Pos;
            break;
        }
    }
    return freq;
}

/* Find flash read access latency */
static rt_uint32_t find_flash_latency(rt_uint32_t freq, rt_uint32_t fs)
{
    rt_uint32_t i;
    rt_uint32_t latency = ((rt_uint32_t)(FLASH_LATENCY_MAX_NUMS - 1U) << FLASH_ACR_LATENCY_Pos) & FLASH_ACR_LATENCY;
    for (i = 1; i <= FLASH_LATENCY_MAX_NUMS; i++)
    {
        if (freq <= fs * i)
        {
            latency = ((i - 1U) << FLASH_ACR_LATENCY_Pos) & FLASH_ACR_LATENCY;
            break;
        }
    }
    return latency;
}

/**
 * This function configure clock tree
 *
 * @return SYSCLK or HCLK frequency (MHz)
 */
static rt_uint16_t clock_tree_config(struct rcc_conf_struct *conf, rt_uint32_t freq_base, rt_uint32_t freq_hclk)
{
    rt_uint32_t freq, freq_div, div, divm, divr, divq, mul, fs, i, freq_vco = 0U;
    rt_bool_t find = RT_FALSE;
    rt_bool_t usbclk_use_pll = RT_TRUE;

    freq_div = stm32_run_freq[conf->mode][1];

    RT_ASSERT(conf != RT_NULL && freq_hclk > 0);
    RT_ASSERT(freq_div == 1U || freq_div == 1000U);

    freq = freq_base = freq_base / 1000U * freq_div;

    if (_osc_conf.osc_type == RCC_OSCILLATORTYPE_MSI)
    {
        find_msi_range(freq_base * 1000U / freq_div, &conf->msi_range);
    }

    if (freq_div == 1 && conf->pll_state == RCC_PLL_ON && freq_hclk >= OSC_CONF_PLL_VCO_FREQ_MIN / OSC_CONF_PLLR_DIV_MAX)
    {
        /* Use PLL */
        conf->sysclk_source = RCC_SYSCLKSOURCE_PLLCLK;

#if defined(RCC_PLLSAI1_SUPPORT) && (defined(USB_OTG_FS) || defined(USB)) && !defined(PWR_CR5_R1MODE)
        /* Not STM32L4+ */
        if (_rcc_conf[PM_RUN_MODE_NORMAL_SPEED].clk48_source == RCC_USBCLKSOURCE_PLLSAI1)
        {
            /* Get the PLLM divider */
            divm = conf->pllm = _rcc_conf[PM_RUN_MODE_NORMAL_SPEED].pllm;

            while (1)
            {
                /* Get the PLLN multiplier */
                mul = (freq_hclk << 1U) * divm / get_stein_div((freq_hclk << 1U), freq_base);
                freq_vco = freq_base * mul / divm;

                i = 1U;
                while (mul * i < OSC_CONF_PLLN_MUL_MIN || freq_vco * i < OSC_CONF_PLL_VCO_FREQ_MIN)
                    i++;
                mul *= i;
                freq_vco *= i;
                /* Get the PLLR divider */
                divr = freq_vco / freq_hclk;

                if (freq_vco <= OSC_CONF_PLL_VCO_FREQ_MAX && mul <= OSC_CONF_PLLN_MUL_MAX
                        && divr <= OSC_CONF_PLLR_DIV_MAX)
                {
                    /* Correct */
                    freq = freq_vco / divr;
                    conf->plln = mul;
                    conf->pllr = divr & 0xfe;
                    conf->pllq = _rcc_conf[PM_RUN_MODE_NORMAL_SPEED].pllq;
                    conf->ahb_div = RCC_SYSCLK_DIV1;

                    break;
                }

                /* Does not meet the optimal frequency */
                freq_hclk--;
                if (freq_hclk < OSC_CONF_PLL_VCO_FREQ_MIN / OSC_CONF_PLLR_DIV_MAX)
                {
                    rt_kprintf("error: Incorrect system frequency settings.\n");
                    RT_ASSERT(0);
                    break;
                }
            }
        }
        else
#endif
        {
            while (1)
            {
#if (defined(USB_OTG_FS) || defined(USB)) && (defined(RT_USING_USB_HOST) || defined(RT_USING_USB_DEVICE))
                if (usbclk_use_pll && (((freq_hclk % 48U == 0) && (freq_hclk / 48U <= 4U))
                                       || ((48U % freq_hclk == 0) && (48U / freq_hclk <= 4U))))
                {
                    if (freq_hclk / 48U > 0)
                    {
                        div = get_stein_div((freq_hclk << 1U), freq_base);
                    }
                    else
                    {
                        div = get_stein_div((48U << 1U), freq_base);
                    }
                }
                else
                {
                    div = get_stein_div((freq_hclk << 1U), freq_base);
                }
#else
                usbclk_use_pll = RT_FALSE;
                div = get_stein_div((freq_hclk << 1U), freq_base);
#endif
                mul = (freq_hclk << 1U) / div;
                div = (freq_base / div) << 1U;

                i = 1U;
                while (!find)
                {
                    /* Get the PLLN multiplier */
                    while (mul * i < OSC_CONF_PLLN_MUL_MIN || div * i < OSC_CONF_PLLM_DIV_MIN * OSC_CONF_PLLR_DIV_MIN)
                        i++;
                    mul *= i;
                    div *= i;

                    if (mul > OSC_CONF_PLLN_MUL_MAX || div > OSC_CONF_PLLM_DIV_MAX * OSC_CONF_PLLR_DIV_MAX)
                        break;

                    /* Get the PLLM divider */
                    for (divm = OSC_CONF_PLLM_DIV_MAX; divm >= OSC_CONF_PLLM_DIV_MIN; divm--)
                    {
                        freq = freq_base / divm;
                        freq_vco = freq * mul;
                        if (freq < OSC_CONF_PLLM_FREQ_MIN || div / divm < OSC_CONF_PLLR_DIV_MIN
                                || freq_vco < OSC_CONF_PLL_VCO_FREQ_MIN)
                            continue;
                        if (freq > OSC_CONF_PLLM_FREQ_MAX || div / divm > OSC_CONF_PLLR_DIV_MAX
                                || freq_vco > OSC_CONF_PLL_VCO_FREQ_MAX)
                            break;

                        if (div % divm == 0)
                        {
                            divr = freq_vco / freq_hclk;
                            /* Get the PLLQ divider */
#if (defined(USB_OTG_FS) || defined(USB)) && (defined(RT_USING_USB_HOST) || defined(RT_USING_USB_DEVICE))
                            divq = freq_vco / 48U;
                            if (divq > OSC_CONF_PLLQ_DIV_MAX)
                                continue;
                            if (divq < OSC_CONF_PLLQ_DIV_MIN)
                                break;
                            conf->clk48_source = RCC_USBCLKSOURCE_PLL;
#else
                            divq = OSC_CONF_PLLQ_DIV_MAX;
#endif
                            find = RT_TRUE;
                            break;
                        }
                    }
                    i++;
                }

                if (find)
                    break;

                /* Does not meet the optimal frequency */
#if (defined(USB_OTG_FS) || defined(USB)) && defined(RCC_HSI48_SUPPORT) && !defined(PWR_CR5_R1MODE) && \
    (defined(RT_USING_USB_HOST) || defined(RT_USING_USB_DEVICE))
                if (usbclk_use_pll)
                {
                    usbclk_use_pll = RT_FALSE;
                    conf->clk48_source = RCC_USBCLKSOURCE_HSI48;
                }
                else
#endif
                {
                    freq_hclk--;
                    usbclk_use_pll = RT_TRUE;
                    if (freq_hclk < (OSC_CONF_PLL_VCO_FREQ_MIN / OSC_CONF_PLLR_DIV_MAX))
                    {
                        rt_kprintf("error: Incorrect system frequency settings.\n");
                        RT_ASSERT(0);
                        break;
                    }
                }
            }

            freq = freq_vco / divr;

            conf->pllm = divm;
            conf->plln = mul;
            conf->pllr = divr & 0xfe;
            conf->pllq = divq & 0xfe;
            conf->ahb_div = RCC_SYSCLK_DIV1;
        }
#if defined(RCC_PLLP_SUPPORT)
        conf->pllp = _rcc_conf[PM_RUN_MODE_NORMAL_SPEED].pllp;
#endif
    }
    else
    {
        conf->pll_state = RCC_PLL_OFF;

        /* Select MSI and find the MSI frequency range */
        conf->sysclk_source = RCC_SYSCLKSOURCE_MSI;

        freq_hclk = freq_hclk * 1000U / freq_div;
        freq_div = 1000U;
        freq = find_msi_range(freq_hclk, &conf->msi_range);
        conf->ahb_div = RCC_SYSCLK_DIV1;

        stm32_run_freq[conf->mode][1] = freq_div;

        /* Configure the Low-power Run mode */
        if ((freq / freq_div) <= OSC_CONF_LOW_POW_RUN_FREQ)
            conf->low_pow_run_en = RT_TRUE;
        else
            conf->low_pow_run_en = RT_FALSE;
    }

    (void)freq_vco;
    (void)div;
    (void)divm;
    (void)divr;
    (void)divq;
    (void)mul;
    (void)find;
    (void)usbclk_use_pll;

    /* Find voltage scales range */
    conf->volt_scale = _volt_scale_tab[PM_POW_VOLT_SCALE_NUMS - 1U][0];
    fs = _volt_scale_tab[0][1];
    for (i = 0; i < PM_POW_VOLT_SCALE_NUMS; i++)
    {
        if ((freq / freq_div) <= _volt_scale_tab[i][2])
        {
            conf->volt_scale = _volt_scale_tab[i][0];
            /* frequency step for flash latency */
            fs = _volt_scale_tab[i][1];
            break;
        }
    }

    conf->latency = find_flash_latency(freq / freq_div, fs);

    return (rt_uint16_t)freq;
}

static int rcc_conf_init(void)
{
    rt_uint32_t mode = PM_RUN_MODE_NORMAL_SPEED;
    struct rcc_conf_struct *conf = &_rcc_conf[mode];
    struct osc_conf_struct *osc = &_osc_conf;

    if (!osc->init)
    {
        /* Clone the main clock tree */
        switch (__HAL_RCC_GET_SYSCLK_SOURCE())
        {
        case RCC_SYSCLKSOURCE_STATUS_HSE:  /* HSE used as system clock */
            conf->pll_state = RCC_PLL_OFF;
            conf->sysclk_source = RCC_SYSCLKSOURCE_HSE;
            osc->osc_type = RCC_OSCILLATORTYPE_HSE;
            osc->osc_freq = HSE_VALUE / 1000U;
            break;
        case RCC_SYSCLKSOURCE_STATUS_PLLCLK:  /* PLL used as system clock */
            conf->pll_state = RCC_PLL_ON;
            conf->sysclk_source = RCC_SYSCLKSOURCE_PLLCLK;

            if (__HAL_RCC_GET_PLL_OSCSOURCE() == RCC_PLLSOURCE_HSE)
            {
                osc->osc_type = RCC_OSCILLATORTYPE_HSE;
                osc->osc_freq = HSE_VALUE / 1000U;
            }
            else if (__HAL_RCC_GET_PLL_OSCSOURCE() == RCC_PLLSOURCE_HSI)
            {
                osc->osc_type = RCC_OSCILLATORTYPE_HSI;
                osc->osc_freq = HSI_VALUE / 1000U;
            }
            else
            {
                conf->msi_range = __HAL_RCC_GET_MSI_RANGE();
                osc->osc_type = RCC_OSCILLATORTYPE_MSI;
                osc->osc_freq = _msi_range_tab[conf->msi_range >> RCC_CR_MSIRANGE_Pos];
            }
            break;
        case RCC_SYSCLKSOURCE_STATUS_HSI:    /* HSI used as system clock source */
            conf->pll_state = RCC_PLL_OFF;
            conf->sysclk_source = RCC_SYSCLKSOURCE_HSI;
            osc->osc_type = RCC_OSCILLATORTYPE_HSI;
            osc->osc_freq = HSI_VALUE / 1000U;
            break;
        case RCC_SYSCLKSOURCE_STATUS_MSI:  /* MSI used as system clock source */
        default:  /* MSI used as system clock */
            conf->pll_state = RCC_PLL_OFF;
            conf->sysclk_source = RCC_SYSCLKSOURCE_MSI;
            conf->msi_range = __HAL_RCC_GET_MSI_RANGE();
            osc->osc_type = RCC_OSCILLATORTYPE_MSI;
            osc->osc_freq = _msi_range_tab[conf->msi_range >> RCC_CR_MSIRANGE_Pos];
            break;
        }

        /* Get the normal run speed register settings */
        if (conf->pll_state == RCC_PLL_ON)
        {
            conf->pllm = ((RCC->PLLCFGR & RCC_PLLCFGR_PLLM) >> RCC_PLLCFGR_PLLM_Pos) + 1U;
            conf->plln = (RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos;
            conf->pllr = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> RCC_PLLCFGR_PLLR_Pos) + 1U) << 1U;
            conf->pllq = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLQ) >> RCC_PLLCFGR_PLLQ_Pos) + 1U) << 1U;
#if defined(RCC_PLLP_SUPPORT)
  #if defined(RCC_PLLP_DIV_2_31_SUPPORT)
            conf->pllp = (RCC->PLLCFGR & RCC_PLLCFGR_PLLPDIV) >> RCC_PLLCFGR_PLLPDIV_Pos;
  #else
            conf->pllp = (RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> RCC_PLLCFGR_PLLP_Pos;
  #endif
#endif
        }
#if defined(RCC_PLLP_SUPPORT)
        else
        {
            conf->pllp = RCC_PLLP_DIV7;
        }
#endif
#if defined(USB_OTG_FS) || defined(USB)
        conf->clk48_source = RCC->CCIPR & RCC_CCIPR_CLK48SEL;
#endif
        conf->ahb_div = RCC->CFGR & RCC_CFGR_HPRE;
        conf->latency = FLASH->ACR & FLASH_ACR_LATENCY;
        conf->volt_scale = HAL_PWREx_GetVoltageRange();
        stm32_run_freq[mode][0] = HAL_RCC_GetSysClockFreq() / 1000000U;

        /* Initialize the _rcc_conf[] arrays */
        for (mode = PM_RUN_MODE_HIGH_SPEED; mode < PM_RUN_MODE_MAX; mode++)
        {
            conf = &_rcc_conf[mode];
            conf->mode = mode;

            switch (mode)
            {
            case PM_RUN_MODE_HIGH_SPEED:
                _set_sysclock[mode] = stm32_systemclock_high;
                if (stm32_run_freq[mode][0] > stm32_run_freq[PM_RUN_MODE_NORMAL_SPEED][0])
                {
                    conf->pll_state = RCC_PLL_ON;
                    stm32_run_freq[mode][0] = clock_tree_config(conf, osc->osc_freq, stm32_run_freq[mode][0]);
                }
                else
                {
                    rt_memcpy(conf, &_rcc_conf[PM_RUN_MODE_NORMAL_SPEED], sizeof(struct rcc_conf_struct));
                    stm32_run_freq[mode][0] = stm32_run_freq[PM_RUN_MODE_NORMAL_SPEED][0];
                }
                break;
            case PM_RUN_MODE_NORMAL_SPEED:
                _set_sysclock[mode] = stm32_systemclock_normal;
                break;
            case PM_RUN_MODE_MEDIUM_SPEED:
                _set_sysclock[mode] = stm32_systemclock_medium;
                conf->pll_state = RCC_PLL_ON;
                stm32_run_freq[mode][0] = clock_tree_config(conf, osc->osc_freq, stm32_run_freq[mode][0]);
                break;
            case PM_RUN_MODE_LOW_SPEED:
                _set_sysclock[mode] = stm32_systemclock_low;
                conf->pll_state = RCC_PLL_OFF;
                stm32_run_freq[mode][0] = clock_tree_config(conf, osc->osc_freq, stm32_run_freq[mode][0]);
                break;
            default:
                RT_ASSERT(0);
                break;
            }
        }

        osc->init = 1U;
    }

    return 0;
}
INIT_DEVICE_EXPORT(rcc_conf_init);

/* System Clock Configuration */
static void systemclock_run(struct rcc_conf_struct *conf)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};

#if defined(PWR_CR5_R1MODE)
    /* STM32L4+ */
    if (HAL_IS_BIT_CLR(PWR->CR5, PWR_CR5_R1MODE) && conf->volt_scale == PWR_REGULATOR_VOLTAGE_SCALE2)
    {
        /* PWR_REGULATOR_VOLTAGE_SCALE1_BOOST --> PWR_REGULATOR_VOLTAGE_SCALE2 */
        /* with AHB prescaler divider 2 as first step */
        RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK;
        RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
        if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
        {
            Error_Handler();
        }
    }
#endif

    if ((conf->pll_state == RCC_PLL_ON && _osc_conf.osc_type == RCC_OSCILLATORTYPE_HSE)
            || conf->sysclk_source == RCC_SYSCLKSOURCE_HSE)
    {
        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
        RCC_OscInitStruct.HSEState = RCC_HSE_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    }
    else if ((conf->pll_state == RCC_PLL_ON && _osc_conf.osc_type == RCC_OSCILLATORTYPE_HSI)
             || conf->sysclk_source == RCC_SYSCLKSOURCE_HSI)
    {
        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
        RCC_OscInitStruct.HSIState = RCC_HSI_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    }
    else
    {
        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
        RCC_OscInitStruct.MSIState = RCC_MSI_ON;
        RCC_OscInitStruct.MSIClockRange = conf->msi_range;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
    }

    RCC_OscInitStruct.PLL.PLLState = conf->pll_state;
    if (conf->pll_state == RCC_PLL_ON)
    {
        RCC_OscInitStruct.PLL.PLLM = conf->pllm;
        RCC_OscInitStruct.PLL.PLLN = conf->plln;
        RCC_OscInitStruct.PLL.PLLR = conf->pllr;
        RCC_OscInitStruct.PLL.PLLQ = conf->pllq;
#if defined(RCC_PLLP_SUPPORT)
        RCC_OscInitStruct.PLL.PLLP = conf->pllp;
#endif
    }

#if defined(RCC_HSI48_SUPPORT) && (defined(RT_USING_USB_HOST) || defined(RT_USING_USB_DEVICE))
    if (conf->clk48_source == RCC_USBCLKSOURCE_HSI48)
    {
        RCC_OscInitStruct.OscillatorType |= RCC_OSCILLATORTYPE_HSI48;
        RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
    }
#endif

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /* Reconfigure the SYSCLK clocks dividers */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK;
    RCC_ClkInitStruct.SYSCLKSource = conf->sysclk_source;
#if defined(PWR_CR5_R1MODE)
    /* STM32L4+ */
    if (conf->volt_scale == PWR_REGULATOR_VOLTAGE_SCALE1_BOOST)
    {
        /* with AHB prescaler divider 2 as first step */
        RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
        if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
        {
            Error_Handler();
        }

        /* AHB prescaler divider as second step */
        RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK;
    }
#endif
    RCC_ClkInitStruct.AHBCLKDivider = conf->ahb_div;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, conf->latency) != HAL_OK)
    {
        Error_Handler();
    }

#if (defined(USB_OTG_FS) || defined(USB)) && (defined(RT_USING_USB_HOST) || defined(RT_USING_USB_DEVICE))
    __HAL_RCC_USB_CONFIG(conf->clk48_source);
#endif
}

static void systemclock_msi_on(rt_uint32_t mode)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    struct rcc_conf_struct *conf = &_rcc_conf[mode];
    rt_uint32_t freq, sysclk_source;
    rt_uint32_t latency = FLASH_LATENCY_0;

    sysclk_source = __HAL_RCC_GET_SYSCLK_SOURCE();
    if (sysclk_source == RCC_SYSCLKSOURCE_STATUS_MSI ||
        (sysclk_source == RCC_SYSCLKSOURCE_STATUS_PLLCLK && __HAL_RCC_GET_PLL_OSCSOURCE() == RCC_PLLSOURCE_MSI))
    {
        freq = _msi_range_tab[conf->msi_range >> RCC_CR_MSIRANGE_Pos] / 1000U;
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
    }
    else
    {
        freq = HSI_VALUE / 1000000U;
        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
        RCC_OscInitStruct.HSIState = RCC_HSI_ON;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE; /* No update on PLL */
        if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
        {
            Error_Handler();
        }
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    latency = find_flash_latency(freq, _volt_scale_tab[conf->volt_scale][1]);
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, latency) != HAL_OK)
    {
        Error_Handler();
    }
}

static void systemclock_msi_off(rt_uint32_t mode)
{
    if (_osc_conf.osc_type != RCC_OSCILLATORTYPE_HSI && _rcc_conf[mode].sysclk_source != RCC_SYSCLKSOURCE_HSI)
        __HAL_RCC_HSI_DISABLE();
    else if (_osc_conf.osc_type != RCC_OSCILLATORTYPE_MSI && _rcc_conf[mode].sysclk_source != RCC_SYSCLKSOURCE_MSI)
        __HAL_RCC_MSI_DISABLE();
}

/**
  * @brief  Configures system clock after wake-up from STOP: enable MSI or HSI, PLL
  *         and select PLL as system clock source.
  * @param  None
  * @retval None
  */
static void systemclock_reconfig(rt_uint32_t mode)
{
    if (__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_MSI && _rcc_conf[mode].sysclk_source == RCC_SYSCLKSOURCE_MSI)
        return;

    systemclock_msi_on(mode);
    _set_sysclock[mode]();
}

/* System Clock Configuration On High Speed */
RT_WEAK void stm32_systemclock_high(void)
{
    systemclock_run(&_rcc_conf[PM_RUN_MODE_HIGH_SPEED]);
}

/* System Clock Configuration On Normal Speed */
RT_WEAK void stm32_systemclock_normal(void)
{
    systemclock_run(&_rcc_conf[PM_RUN_MODE_NORMAL_SPEED]);
}

/* System Clock Configuration On Medium Speed */
RT_WEAK void stm32_systemclock_medium(void)
{
    systemclock_run(&_rcc_conf[PM_RUN_MODE_MEDIUM_SPEED]);
}

/* System Clock Configuration On Low Speed */
RT_WEAK void stm32_systemclock_low(void)
{
    systemclock_run(&_rcc_conf[PM_RUN_MODE_LOW_SPEED]);
}

/* --------------------- PM oscillator end --------------------- */

#if defined(RT_USING_SERIAL)
static void uart_console_reconfig(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    rt_device_control(rt_console_get_device(), RT_DEVICE_CTRL_CONFIG, &config);
}
#endif

/**
 * This function will put STM32 into sleep mode.
 *
 * @param pm pointer to power manage structure
 */
void stm32_sleep(struct rt_pm *pm, rt_uint8_t mode)
{
    switch (mode)
    {
    case PM_SLEEP_MODE_NONE:
        break;

    case PM_SLEEP_MODE_IDLE:
        if (pm->run_mode == PM_RUN_MODE_LOW_SPEED)
        {
            /* Enter LP SLEEP Mode, Enable low-power regulator */
            HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
        }
        else
        {
            /* Enter SLEEP Mode, Main regulator is ON */
            HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
        }
        break;

    case PM_SLEEP_MODE_LIGHT:
        if (pm->run_mode == PM_RUN_MODE_LOW_SPEED)
        {
            __HAL_FLASH_SLEEP_POWERDOWN_ENABLE();
            /* Enter LP SLEEP Mode, Enable low-power regulator */
            HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
            __HAL_FLASH_SLEEP_POWERDOWN_DISABLE();
        }
        else
        {
            /* Enter SLEEP Mode, Main regulator is ON */
            HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
        }
        break;

    case PM_SLEEP_MODE_DEEP:
        /* Disable SysTick interrupt */
        CLEAR_BIT(SysTick->CTRL, (rt_uint32_t)SysTick_CTRL_TICKINT_Msk);

        if (pm->run_mode == PM_RUN_MODE_LOW_SPEED)
        {
            /* Clear LPR bit to back the normal run mode */
            CLEAR_BIT(PWR->CR1, PWR_CR1_LPR);
            /* Enter STOP 2 mode  */
            HAL_PWREx_EnterSTOP2Mode(PWR_STOPENTRY_WFI);
            /* Set Regulator parameter to lowpower run mode */
            SET_BIT(PWR->CR1, PWR_CR1_LPR);
        }
        else
        {
            /* Enter STOP 2 mode  */
            HAL_PWREx_EnterSTOP2Mode(PWR_STOPENTRY_WFI);
        }

        /* Enable SysTick interrupt */
        SET_BIT(SysTick->CTRL, (rt_uint32_t)SysTick_CTRL_TICKINT_Msk);
        /* Re-configure the system clock */
        systemclock_reconfig(pm->run_mode);
        break;

    case PM_SLEEP_MODE_STANDBY:
        __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
        /* Enter STANDBY mode */
        HAL_PWR_EnterSTANDBYMode();
        break;

    case PM_SLEEP_MODE_SHUTDOWN:
        __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
        /* Enter SHUTDOWNN mode */
        HAL_PWREx_EnterSHUTDOWNMode();
        break;

    default:
        RT_ASSERT(0);
        break;
    }
}

void stm32_run(struct rt_pm *pm, rt_uint8_t mode)
{
    static rt_uint32_t last_mode;
    static char *run_str[] = PM_RUN_MODE_NAMES;
    struct rcc_conf_struct sconf = _rcc_conf[mode];

    if (mode == last_mode)
        return;

    if (stm32_run_freq[mode][0] != stm32_run_freq[last_mode][0])
    {
        if (_rcc_conf[last_mode].low_pow_run_en && !sconf.low_pow_run_en)
        {
            /* Disable the Low-power Run mode */
            HAL_PWREx_DisableLowPowerRunMode();
        }

        systemclock_msi_on(last_mode);

        if (mode < last_mode)
        {
            /* Frequency increase */
            HAL_PWREx_ControlVoltageScaling(sconf.volt_scale);

            _set_sysclock[mode]();
        }
        else
        {
            /* Frequency reduce */
            _set_sysclock[mode]();

            HAL_PWREx_ControlVoltageScaling(sconf.volt_scale);
        }

        if (sconf.volt_scale == PWR_REGULATOR_VOLTAGE_SCALE2 || _osc_conf.osc_type == RCC_OSCILLATORTYPE_MSI)
        {
            /* Configure the wake up from stop clock to MSI */
            __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_MSI);
        }
        else
        {
            /* Configure the wake up from stop clock to HSI */
            __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_HSI);
        }

        if (sconf.low_pow_run_en)
        {
            /* Enable the Low-power Run mode */
            HAL_PWREx_EnableLowPowerRunMode();
        }

        systemclock_msi_off(mode);

#if defined(RT_USING_SERIAL)
        /* Re-Configure the UARTs */
        uart_console_reconfig();
#endif
        /* Re-Configure the Systick time */
        HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / RT_TICK_PER_SECOND);
        /* Re-Configure the Systick */
        HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    }

    last_mode = mode;
    rt_kprintf("switch to %s mode, frequency = %d %sHz\n",
               run_str[mode], stm32_run_freq[mode][0], (stm32_run_freq[mode][1] == 1) ? "M" : "K");

    if ((stm32_run_freq[mode][0] / stm32_run_freq[mode][1]) > OSC_CONF_SYS_FREQ_MAX)
        rt_kprintf("warning: The frequency has over than %d MHz\n", OSC_CONF_SYS_FREQ_MAX);
}

#endif /* defined(RT_USING_PM) */
