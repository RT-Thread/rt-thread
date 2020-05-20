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
/* STM32F0 */
#define OSC_CONF_SYS_FREQ_MAX       48U     /* Max system clock  MHz */
#define OSC_CONF_PLL_SYS_FREQ_MIN   16U     /* Min system clock with pll on  MHz */
#define OSC_CONF_PLL_VI_FREQ_MIN    1U      /* Min pll vco input clock  MHz */
#define OSC_CONF_PLL_VI_FREQ_MAX    24U     /* Max pll vco input clock  MHz */
#define OSC_CONF_PLL_PREDIV_MIN     1U      /* Min pll prescaler */
#define OSC_CONF_PLL_PREDIV_MAX     16U     /* Max pll prescaler */
#define OSC_CONF_PLL_MUL_MIN        2U      /* Min pll multiplier */
#define OSC_CONF_PLL_MUL_MAX        16U     /* Max pll multiplier */

#define FLASH_LATENCY_MAX_NUMS      2U
#define FLASH_LATENCY_FREQ          24U     /* FLASH_LATENCY increasing frequency  MHz */

struct PM_RCC_conf
{
    rt_uint32_t mode;
    rt_uint32_t sysclk_source;
#if defined(RCC_CFGR3_USBSW_HSI48) && (defined(RT_USING_USB_HOST) || defined(RT_USING_USB_DEVICE))
    rt_uint32_t clk48_source;
#endif
    rt_uint32_t pll_state;
    rt_uint32_t pll_prediv;
    rt_uint32_t pll_mul;
    rt_uint32_t ahb_div;
    rt_uint32_t latency;
};
static struct PM_RCC_conf _pm_conf[PM_RUN_MODE_MAX] = {0};

static struct PM_RCC_Osc
{
    rt_uint32_t init;
    rt_uint32_t osc_type;
    rt_uint32_t osc_freq;
    rt_uint32_t pll_prediv_min;
    rt_uint32_t pll_prediv_max;
}
_pm_osc = {0};

static void (* _pm_set_sysclock[PM_RUN_MODE_MAX])(void) = {0};

RT_WEAK rt_uint16_t pm_run_freq[PM_RUN_MODE_MAX][2] =
{
    /* The actual frequency is 1/divisor MHz, divisor = {1, 1000} */
    /* {sysclk frequency, divisor} */
    {48, 1},    /* High speed */
    {48, 1},    /* Normal speed */
    {16, 1},    /* Medium speed */
    {2,  1},    /* Low speed, this is HCLK */
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

/**
 * This function configure clock tree
 *
 * @return SYSCLK or HCLK frequency
 */
static rt_uint16_t pm_hw_clk_config(struct PM_RCC_conf *conf, rt_uint32_t freq_base, rt_uint32_t freq_hclk)
{
    rt_uint32_t freq, freq_div, div, mul, i;

    freq_div = pm_run_freq[conf->mode][1];

    RT_ASSERT(conf != RT_NULL && freq_hclk > 0);
    RT_ASSERT(freq_div == 1U || freq_div == 1000U);

    freq_base = freq_base / 1000U * freq_div;

    if (freq_div == 1 && conf->pll_state == RCC_PLL_ON && freq_hclk >= OSC_CONF_PLL_SYS_FREQ_MIN)
    {
        /* Use PLL */
        conf->sysclk_source = RCC_SYSCLKSOURCE_PLLCLK;

        while (1)
        {
            div = get_stein_div(freq_hclk, freq_base);
            mul = freq_hclk / div;
            div = freq_base / div;

            /* Get the PLL multiplier and divider */
            i = 1U;
            while (mul * i < OSC_CONF_PLL_MUL_MIN || div * i < _pm_osc.pll_prediv_min)
                i++;
            mul *= i;
            div *= i;

            if (mul > OSC_CONF_PLL_MUL_MAX || (freq_base / div) < OSC_CONF_PLL_VI_FREQ_MIN \
                    || div > _pm_osc.pll_prediv_max)
            {
                /* Does not meet the optimal frequency */
                freq_hclk--;
                if (freq_hclk < OSC_CONF_PLL_SYS_FREQ_MIN)
                {
                    rt_kprintf("error: Incorrect system frequency settings.\n");
                    RT_ASSERT(0);
                    break;
                }
            }
            else
            {
                /* Correct multiplier and divider */
                break;
            }
        }

        freq = freq_base * mul / div;
#if defined(RCC_CFGR3_USBSW_HSI48) && (defined(RT_USING_USB_HOST) || defined(RT_USING_USB_DEVICE))
        if (freq == 48U)
            conf->clk48_source = RCC_USBCLKSOURCE_PLL;
        else
            conf->clk48_source = RCC_USBCLKSOURCE_HSI48;
#endif

        conf->pll_prediv = ((div - 1U) << RCC_CFGR2_PREDIV_Pos) & RCC_CFGR2_PREDIV;
        conf->pll_mul = ((mul - 2U) << RCC_CFGR_PLLMUL_Pos) & RCC_CFGR_PLLMUL;
        conf->ahb_div = RCC_SYSCLK_DIV1;
    }
    else
    {
        conf->pll_state = RCC_PLL_OFF;

        /* Select HSI for SYSCLK source */
        freq_base = HSI_VALUE / 1000000U * freq_div;
        conf->sysclk_source = RCC_SYSCLKSOURCE_HSI;

        /* Get AHB divider */
        for (div = 0U; div <= 8U; div++)
        {
            if (div == 8U || (freq_base >> div) <= freq_hclk)
                break;
        }
        freq = freq_base >> div;
        if (div) div += 7U;
        conf->ahb_div = (div << RCC_CFGR_HPRE_Pos) & RCC_CFGR_HPRE;
    }

    (void)div;
    (void)mul;

    /* Find flash access latency */
    conf->latency = ((rt_uint32_t)(FLASH_LATENCY_MAX_NUMS - 1U) << FLASH_ACR_LATENCY_Pos) & FLASH_ACR_LATENCY;
    for (i = 1; i <= FLASH_LATENCY_MAX_NUMS; i++)
    {
        if ((freq / freq_div) <= FLASH_LATENCY_FREQ * i)
        {
            conf->latency = ((i - 1U) << FLASH_ACR_LATENCY_Pos) & FLASH_ACR_LATENCY;
            break;
        }
    }

    return (rt_uint16_t)freq;
}

static int pm_rcc_conf_init(void)
{
    rt_uint32_t tmpreg, mode = PM_RUN_MODE_NORMAL_SPEED;
    struct PM_RCC_conf *conf = &_pm_conf[mode];
    struct PM_RCC_Osc *osc = &_pm_osc;

    if (!osc->init)
    {
        osc->pll_prediv_min = OSC_CONF_PLL_PREDIV_MIN;
        osc->pll_prediv_max = OSC_CONF_PLL_PREDIV_MAX;

        tmpreg = RCC->CFGR;

        switch (tmpreg & RCC_CFGR_SWS)
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

            if ((tmpreg & RCC_CFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
            {
                osc->osc_type = RCC_OSCILLATORTYPE_HSE;
                osc->osc_freq = HSE_VALUE / 1000U;
            }
#if defined(RCC_CFGR_PLLSRC_HSI48_PREDIV)
            else if ((tmpreg & RCC_CFGR_PLLSRC) == RCC_PLLSOURCE_HSI48)
            {
                osc->osc_type = RCC_OSCILLATORTYPE_HSI48;
                osc->osc_freq = HSI48_VALUE / 1000U;
            }
#endif /* RCC_CFGR_PLLSRC_HSI48_PREDIV */
            else
            {
                osc->osc_type = RCC_OSCILLATORTYPE_HSI;
                osc->osc_freq = HSI_VALUE / 1000U;

#if !(defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F070x6) || defined(STM32F071xB) || \
      defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || defined(STM32F091xC) || \
      defined(STM32F098xx) || defined(STM32F030xC))
                osc->pll_prediv_min = osc->pll_prediv_max = 2U;
#endif
            }
            break;
#if defined(RCC_CFGR_SWS_HSI48)
        case RCC_SYSCLKSOURCE_STATUS_HSI48:    /* HSI48 used as system clock source */
            conf->pll_state = RCC_PLL_OFF;
            conf->sysclk_source = RCC_SYSCLKSOURCE_HSI48;
            osc->osc_type = RCC_OSCILLATORTYPE_HSI48;
            osc->osc_freq = HSI48_VALUE / 1000U;
            break;
#endif /* RCC_CFGR_SWS_HSI48 */
        case RCC_SYSCLKSOURCE_STATUS_HSI:  /* HSI used as system clock source */
        default:  /* HSI used as system clock */
            conf->pll_state = RCC_PLL_OFF;
            conf->sysclk_source = RCC_SYSCLKSOURCE_HSI;
            osc->osc_type = RCC_OSCILLATORTYPE_HSI;
            osc->osc_freq = HSI_VALUE / 1000U;
            break;
        }

        /* Get the normal run speed register settings */
        if (conf->pll_state == RCC_PLL_ON)
        {
            conf->pll_mul = RCC->CFGR & RCC_CFGR_PLLMUL;
            conf->pll_prediv = RCC->CFGR2 & RCC_CFGR2_PREDIV;
        }
        conf->ahb_div = RCC->CFGR & RCC_CFGR_HPRE;
        conf->latency = FLASH->ACR & FLASH_ACR_LATENCY;
#if defined(RCC_CFGR3_USBSW_HSI48) && (defined(RT_USING_USB_HOST) || defined(RT_USING_USB_DEVICE))
        conf->clk48_source = RCC->CFGR3 & RCC_CFGR3_USBSW;
#endif

        /* Initialize the _pm_conf[] arrays */
        for (mode = PM_RUN_MODE_HIGH_SPEED; mode < PM_RUN_MODE_MAX; mode++)
        {
            conf = &_pm_conf[mode];
            conf->mode = mode;

            switch (mode)
            {
            case PM_RUN_MODE_HIGH_SPEED:
                _pm_set_sysclock[mode] = pm_system_clock_high;
                if (pm_run_freq[mode][0] > pm_run_freq[PM_RUN_MODE_NORMAL_SPEED][0])
                {
                    conf->pll_state = RCC_PLL_ON;
                    pm_run_freq[mode][0] = pm_hw_clk_config(conf, osc->osc_freq, pm_run_freq[mode][0]);
                }
                else
                {
                    rt_memcpy(conf, &_pm_conf[PM_RUN_MODE_NORMAL_SPEED], sizeof(struct PM_RCC_conf));
                    pm_run_freq[mode][0] = pm_run_freq[PM_RUN_MODE_NORMAL_SPEED][0];
                }
                break;
            case PM_RUN_MODE_NORMAL_SPEED:
                _pm_set_sysclock[mode] = pm_system_clock_normal;
                break;
            case PM_RUN_MODE_MEDIUM_SPEED:
                _pm_set_sysclock[mode] = pm_system_clock_medium;
                conf->pll_state = RCC_PLL_ON;
                pm_run_freq[mode][0] = pm_hw_clk_config(conf, osc->osc_freq, pm_run_freq[mode][0]);
                break;
            case PM_RUN_MODE_LOW_SPEED:
                _pm_set_sysclock[mode] = pm_system_clock_low;
                conf->pll_state = RCC_PLL_OFF;
                pm_run_freq[mode][0] = pm_hw_clk_config(conf, osc->osc_freq, pm_run_freq[mode][0]);
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
INIT_DEVICE_EXPORT(pm_rcc_conf_init);

/* System Clock Configuration */
static void systemclock_run(struct PM_RCC_conf *conf)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = _pm_osc.osc_type;
    if (_pm_osc.osc_type == RCC_OSCILLATORTYPE_HSE)
    {
        RCC_OscInitStruct.HSEState = RCC_HSE_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    }
#if defined(RCC_CFGR_SWS_HSI48)
    else if (_pm_osc.osc_type == RCC_OSCILLATORTYPE_HSI48)
    {
        RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI48;
    }
#endif /* RCC_CFGR_SWS_HSI48 */
    else
    {
        RCC_OscInitStruct.HSIState = RCC_HSI_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    }

    RCC_OscInitStruct.PLL.PLLState = conf->pll_state;
    if (conf->pll_state == RCC_PLL_ON)
    {
        RCC_OscInitStruct.PLL.PREDIV = conf->pll_prediv;
        RCC_OscInitStruct.PLL.PLLMUL = conf->pll_mul;
    }

#if defined(RCC_CFGR3_USBSW_HSI48) && (defined(RT_USING_USB_HOST) || defined(RT_USING_USB_DEVICE))
    if (conf->clk48_source == RCC_USBCLKSOURCE_HSI48);
    {
        RCC_OscInitStruct.OscillatorType |= RCC_OSCILLATORTYPE_HSI48;
        RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
    }
#endif

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /* Reconfigure the SYSCLK and HCLK */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK;
    RCC_ClkInitStruct.SYSCLKSource = conf->sysclk_source;
    RCC_ClkInitStruct.AHBCLKDivider = conf->ahb_div;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, conf->latency) != HAL_OK)
    {
        Error_Handler();
    }

#if defined(RCC_CFGR3_USBSW_HSI48) && (defined(RT_USING_USB_HOST) || defined(RT_USING_USB_DEVICE))
    __HAL_RCC_USB_CONFIG(conf->clk48_source);
#endif
}

static void sysclock_msi_on(rt_uint32_t mode)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    (void)mode;

    if ((__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_SYSCLKSOURCE_STATUS_HSI)
            || (__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_SYSCLKSOURCE_STATUS_PLLCLK
                && _pm_osc.osc_type != RCC_OSCILLATORTYPE_HSI))
    {
        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
        RCC_OscInitStruct.HSIState = RCC_HSI_ON;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;  /* No update on PLL */
        if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
        {
            Error_Handler();
        }
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
}

static void sysclock_msi_off(rt_uint32_t mode)
{
    if (_pm_osc.osc_type != RCC_OSCILLATORTYPE_HSI && _pm_conf[mode].sysclk_source != RCC_SYSCLKSOURCE_HSI)
        __HAL_RCC_HSI_DISABLE();
}

/**
  * @brief  Configures system clock after wake-up from STOP: enable MSI or HSI, PLL
  *         and select PLL as system clock source.
  * @param  None
  * @retval None
  */
static void sysclock_reconfig(rt_uint32_t mode)
{
    sysclock_msi_on(mode);

    _pm_set_sysclock[mode]();
}

/* System Clock Configuration On High Speed */
RT_WEAK void pm_system_clock_high(void)
{
    systemclock_run(&_pm_conf[PM_RUN_MODE_HIGH_SPEED]);
}

/* System Clock Configuration On Normal Speed */
RT_WEAK void pm_system_clock_normal(void)
{
    systemclock_run(&_pm_conf[PM_RUN_MODE_NORMAL_SPEED]);
}

/* System Clock Configuration On Medium Speed */
RT_WEAK void pm_system_clock_medium(void)
{
    systemclock_run(&_pm_conf[PM_RUN_MODE_MEDIUM_SPEED]);
}

/* System Clock Configuration On Low Speed */
RT_WEAK void pm_system_clock_low(void)
{
    systemclock_run(&_pm_conf[PM_RUN_MODE_LOW_SPEED]);
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
void pm_hw_sleep(struct rt_pm *pm, rt_uint8_t mode)
{
    switch (mode)
    {
    case PM_SLEEP_MODE_NONE:
        break;

    case PM_SLEEP_MODE_IDLE:
    case PM_SLEEP_MODE_LIGHT:
        HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
        break;

    case PM_SLEEP_MODE_DEEP:
        /* Disable SysTick interrupt */
        CLEAR_BIT(SysTick->CTRL, (rt_uint32_t)SysTick_CTRL_TICKINT_Msk);
        /* Enter STOP mode  */
        HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
        /* Enable SysTick interrupt */
        SET_BIT(SysTick->CTRL, (rt_uint32_t)SysTick_CTRL_TICKINT_Msk);
        /* Re-configure the system clock */
        sysclock_reconfig(pm->run_mode);
        break;

    case PM_SLEEP_MODE_STANDBY:
    case PM_SLEEP_MODE_SHUTDOWN:
        __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
        /* Enter STANDBY mode */
        HAL_PWR_EnterSTANDBYMode();
        break;

    default:
        RT_ASSERT(0);
        break;
    }
}

void pm_hw_run(struct rt_pm *pm, rt_uint8_t mode)
{
    static rt_uint32_t last_mode;
    static char *run_str[] = PM_RUN_MODE_NAMES;

    if (mode == last_mode)
        return;

    if (pm_run_freq[mode][0] != pm_run_freq[last_mode][0])
    {
        sysclock_msi_on(last_mode);

        _pm_set_sysclock[mode]();

        sysclock_msi_off(mode);

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
               run_str[mode], pm_run_freq[mode][0], (pm_run_freq[mode][1] == 1) ? "M" : "K");

    if ((pm_run_freq[mode][0] / pm_run_freq[mode][1]) > OSC_CONF_SYS_FREQ_MAX)
        rt_kprintf("warning: The frequency has over than %d MHz\n", OSC_CONF_SYS_FREQ_MAX);
}

#endif /* defined(RT_USING_PM) */
