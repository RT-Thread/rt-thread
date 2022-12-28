/*!
 * @file        system_apm32f10x.c
 *
 * @brief       CMSIS Cortex-M3 Device Peripheral Access Layer System Source File
 *
 * @version     V1.0.4
 *
 * @date        2022-12-01
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/*Includes*/
#include "apm32f10x.h"

/** @addtogroup CMSIS
  @{
*/

/** @addtogroup APM32F10x_System
  * @brief APM32F10x system configuration
  @{
*/

/** @defgroup System_Macros
  @{
*/

//#define SYSTEM_CLOCK_HSE    HSE_VALUE
//#define SYSTEM_CLOCK_24MHz  (24000000)
//#define SYSTEM_CLOCK_36MHz  (36000000)
//#define SYSTEM_CLOCK_48MHz  (48000000)
//#define SYSTEM_CLOCK_56MHz  (56000000)
#define SYSTEM_CLOCK_72MHz  (72000000)
//#define SYSTEM_CLOCK_96MHz  (96000000)

/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET     0x00

/**@} end of group System_Macros*/

/** @defgroup System_Variables
  @{
*/

#ifdef SYSTEM_CLOCK_HSE
    uint32_t SystemCoreClock         = SYSTEM_CLOCK_HSE;
#elif defined SYSTEM_CLOCK_24MHz
    uint32_t SystemCoreClock         = SYSTEM_CLOCK_24MHz;
#elif defined SYSTEM_CLOCK_36MHz
    uint32_t SystemCoreClock         = SYSTEM_CLOCK_36MHz;
#elif defined SYSTEM_CLOCK_48MHz
    uint32_t SystemCoreClock         = SYSTEM_CLOCK_48MHz;
#elif defined SYSTEM_CLOCK_56MHz
    uint32_t SystemCoreClock         = SYSTEM_CLOCK_56MHz;
#elif defined SYSTEM_CLOCK_72MHz
    uint32_t SystemCoreClock         = SYSTEM_CLOCK_72MHz;
#else
    uint32_t SystemCoreClock         = SYSTEM_CLOCK_96MHz;
#endif

/**@} end of group System_Variables */

/** @defgroup System_Functions
  @{
*/

static void SystemClockConfig(void);

#ifdef SYSTEM_CLOCK_HSE
    static void SystemClockHSE(void);
#elif defined SYSTEM_CLOCK_24MHz
    static void SystemClock24M(void);
#elif defined SYSTEM_CLOCK_36MHz
    static void SystemClock36M(void);
#elif defined SYSTEM_CLOCK_48MHz
    static void SystemClock48M(void);
#elif defined SYSTEM_CLOCK_56MHz
    static void SystemClock56M(void);
#elif defined SYSTEM_CLOCK_72MHz
    static void SystemClock72M(void);
#elif defined SYSTEM_CLOCK_96MHz
    static void SystemClock96M(void);
#endif

/*!
 * @brief       Setup the microcontroller system
 *
 * @param       None
 *
 * @retval      None
 *
 */
void SystemInit(void)
{
    /* Set HSIEN bit */
    RCM->CTRL_B.HSIEN = BIT_SET;

#ifdef APM32F10X_CL
    RCM->CFG &= (uint32_t) 0xF0FF0000;
#else
    /* Reset SCLKSEL, AHBPSC, APB1PSC, APB2PSC, ADCPSC and MCOSEL bits */
    RCM->CFG &= (uint32_t) 0xF8FF0000;
#endif /* APM32F10X_CL */

    /* Reset HSEEN, CSSEN and PLLEN bits */
    RCM->CTRL &= (uint32_t) 0xFEF6FFFF;
    /* Reset HSEBCFG bit */
    RCM->CTRL_B.HSEBCFG = BIT_RESET;
    /* Reset PLLSRCSEL, PLLHSEPSC, PLLMULCFG and USBDIV bits */
    RCM->CFG &= (uint32_t) 0xFF80FFFF;

#ifdef APM32F10X_CL
    /* Reset PLL2ON and PLL3ON bits */
    RCM->CTRL &= (uint32_t) 0xEBFFFFFF;
    /* Disable all interrupts and clear pending bits  */
    RCM->INT = 0x00FF0000;
    /* Reset CFG2 register */
    RCM->CFG2 = 0x00000000;
#else
    /* Disable all interrupts and clear pending bits */
    RCM->INT = 0x009F0000;
#endif /* APM32F10X_CL */

    SystemClockConfig();

#ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET;
#else
    SCB->VTOR = FMC_BASE | VECT_TAB_OFFSET;
#endif
}

/*!
 * @brief       Update SystemCoreClock variable according to Clock Register Values
 *              The SystemCoreClock variable contains the core clock (HCLK)
 *
 * @param       None
 *
 * @retval      None
 *
 */
void SystemCoreClockUpdate(void)
{
#ifdef APM32F10X_CL
    uint32_t sysClock, pllMull, pllSource, pll2Mull, pllPsc1, pllPsc2;
#else
    uint32_t sysClock, pllMull, pllSource;
#endif

    /* get sys clock */
    sysClock = RCM->CFG_B.SCLKSEL;

    switch (sysClock)
    {
        /* sys clock is HSI */
        case 0:
            sysClock = HSI_VALUE;
            break;

        /* sys clock is HSE */
        case 1:
            sysClock = HSE_VALUE;
            break;

        /* sys clock is PLL */
        case 2:
#ifdef APM32F10X_CL
            /* NOTE : PLL is the same as PLL1 */
            pllSource = RCM->CFG_B.PLL1SRCSEL;

            /* PLL entry clock source is HSE */
            if (pllSource)
            {
                /* PLLPSC1 prescaler factor */
                pllPsc1 = (RCM->CFG2_B.PLLPSC1 + 1);

                /* PLL entry clock source is PLL2 */
                if (RCM->CFG2_B.PLLPSC1SRC)
                {
                    pll2Mull = (RCM->CFG2_B.PLL2MUL != 15) ? (RCM->CFG2_B.PLL2MUL + 2) : 20;
                    pllPsc2 = RCM->CFG2_B.PLLPSC2 + 1;

                    pllSource = ((HSE_VALUE / pllPsc2) * pll2Mull) / pllPsc1;
                }
                /* PLL entry clock source is HSE */
                else
                {
                    pllSource = HSE_VALUE / pllPsc1;
                }
            }
            /* PLL entry clock source is HSI/2 */
            else
            {
                pllSource = HSI_VALUE >> 1;
            }

            pllMull = RCM->CFG_B.PLL1MULCFG;
            if (pllMull == 13)
            {
                /* For 6.5 multiplication factor */
                sysClock = pllSource * pllMull / 2;
            }
            else
            {
                sysClock = pllSource * (pllMull + 2);
            }
#else
            pllMull = RCM->CFG_B.PLL1MULCFG + 2;
            pllSource = RCM->CFG_B.PLL1SRCSEL;

            /* PLL entry clock source is HSE */
            if (pllSource == BIT_SET)
            {
                sysClock = HSE_VALUE * pllMull;

                /* HSE clock divided by 2 */
                if (pllSource == RCM->CFG_B.PLLHSEPSC)
                {
                    sysClock >>= 1;
                }
            }
            /* PLL entry clock source is HSI/2 */
            else
            {
                sysClock = (HSI_VALUE >> 1) * pllMull;
            }
#endif
            break;

        default:
            sysClock  = HSI_VALUE;
            break;
    }

    SystemCoreClock = sysClock;
}

/*!
 * @brief       Configures the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers
 *
 * @param       None
 *
 * @retval      None
 *
 */
static void SystemClockConfig(void)
{
#ifdef SYSTEM_CLOCK_HSE
    SystemClockHSE();
#elif defined SYSTEM_CLOCK_24MHz
    SystemClock24M();
#elif defined SYSTEM_CLOCK_36MHz
    SystemClock36M();
#elif defined SYSTEM_CLOCK_48MHz
    SystemClock48M();
#elif defined SYSTEM_CLOCK_56MHz
    SystemClock56M();
#elif defined SYSTEM_CLOCK_72MHz
    SystemClock72M();
#elif defined SYSTEM_CLOCK_96MHz
    SystemClock96M();
#endif
}

#if defined SYSTEM_CLOCK_HSE
/*!
 * @brief       Selects HSE as System clock source and configure HCLK, PCLK2 and PCLK1 prescalers
 *
 * @param       None
 *
 * @retval      None
 *
 */
static void SystemClockHSE(void)
{
    __IO uint32_t i;

    RCM->CTRL_B.HSEEN = BIT_SET;

    for (i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if (RCM->CTRL_B.HSERDYFLG)
        {
            break;
        }
    }

    if (RCM->CTRL_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->CTRL1_B.PBEN = BIT_SET;

#ifdef APM32F10X_CL

        if (HSE_VALUE <= 24000000)
        {
            /* Flash 0 wait state */
            FMC->CTRL1_B.WS = 0;
        }
        else
        {
            /* Flash 1 wait state */
            FMC->CTRL1_B.WS = 1;
        }

#else
        /* Flash 0 wait state */
        FMC->CTRL1_B.WS = 0;
#endif /* APM32F10X_CL */

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC = 0X00;
        /* PCLK2 = HCLK */
        RCM->CFG_B.APB2PSC = 0;
        /* PCLK1 = HCLK */
        RCM->CFG_B.APB1PSC = 0;

        /* Select HSE as system clock source */
        RCM->CFG_B.SCLKSEL = 1;

        /* Wait till HSE is used as system clock source */
        while (RCM->CFG_B.SCLKSELSTS != 0x01);
    }
}

#elif defined SYSTEM_CLOCK_24MHz
/*!
 * @brief       Sets System clock frequency to 24MHz and configure HCLK, PCLK2 and PCLK1 prescalers
 *
 * @param       None
 *
 * @retval      None
 *
 */
static void SystemClock24M(void)
{
    __IO uint32_t i;

    RCM->CTRL_B.HSEEN = BIT_SET;

    for (i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if (RCM->CTRL_B.HSERDYFLG)
        {
            break;
        }
    }

    if (RCM->CTRL_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->CTRL1_B.PBEN = BIT_SET;
        /* Flash 0 wait state */
        FMC->CTRL1_B.WS = 0;

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC = 0X00;
        /* PCLK2 = HCLK */
        RCM->CFG_B.APB2PSC = 0;
        /* PCLK1 = HCLK */
        RCM->CFG_B.APB1PSC = 0;

#ifdef APM32F10X_CL
        /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz (HSE is 25MHz for APM32F10X_CL) */
        /* PLL configuration: PLLCLK = (PLL2 / 10) * 6 = 24 MHz */

        RCM->CFG2_B.PLLPSC2 = 4;
        RCM->CFG2_B.PLL2MUL = 0x06;

        RCM->CFG2_B.PLLPSC1SRC = 1;
        RCM->CFG2_B.PLLPSC1 = 9;

        /* Enable PLL2 */
        RCM->CTRL_B.PLL2EN = 1;
        /* Wait till PLL2 is ready */
        while (RCM->CTRL_B.PLL2RDYFLG == BIT_RESET);

        RCM->CFG_B.PLL1SRCSEL = 1;
        RCM->CFG_B.PLL1MULCFG = 4;
#else
        /*  PLL configuration: PLLCLK = (HSE / 2) * 6 = 24 MHz */
        /* PLL: (HSE / 2) * 6 */
        RCM->CFG_B.PLL1SRCSEL = 1;
        RCM->CFG_B.PLLHSEPSC = 1;
        RCM->CFG_B.PLL1MULCFG = 4;
#endif /* APM32F10X_CL */

        /* Enable PLL */
        RCM->CTRL_B.PLL1EN = 1;

        /* Wait PLL Ready */
        while (RCM->CTRL_B.PLL1RDYFLG == BIT_RESET);

        /* Select PLL as system clock source */
        RCM->CFG_B.SCLKSEL = 2;

        /* Wait till PLL is used as system clock source */
        while (RCM->CFG_B.SCLKSELSTS != 0x02);
    }
}

#elif defined SYSTEM_CLOCK_36MHz
/*!
 * @brief       Sets System clock frequency to 36MHz and configure HCLK, PCLK2 and PCLK1 prescalers
 *
 * @param       None
 *
 * @retval      None
 *
 */
static void SystemClock36M(void)
{
    __IO uint32_t i;

    RCM->CTRL_B.HSEEN = BIT_SET;

    for (i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if (RCM->CTRL_B.HSERDYFLG)
        {
            break;
        }
    }

    if (RCM->CTRL_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->CTRL1_B.PBEN = BIT_SET;
        /* Flash 1 wait state */
        FMC->CTRL1_B.WS = 1;

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC = 0X00;
        /* PCLK2 = HCLK */
        RCM->CFG_B.APB2PSC = 0;
        /* PCLK1 = HCLK */
        RCM->CFG_B.APB1PSC = 0;

#ifdef APM32F10X_CL
        /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz (HSE is 25MHz for APM32F10X_CL) */
        /* PLL configuration: PLLCLK = (PLL2 / 10) * 9 = 36 MHz */

        RCM->CFG2_B.PLLPSC2 = 4;
        RCM->CFG2_B.PLL2MUL = 0x06;

        RCM->CFG2_B.PLLPSC1SRC = 1;
        RCM->CFG2_B.PLLPSC1 = 9;

        /* Enable PLL2 */
        RCM->CTRL_B.PLL2EN = 1;
        /* Wait till PLL2 is ready */
        while (RCM->CTRL_B.PLL2RDYFLG == BIT_RESET);

        RCM->CFG_B.PLL1SRCSEL = 1;
        RCM->CFG_B.PLL1MULCFG = 7;
#else
        /*  PLL configuration: PLLCLK = (HSE / 2) * 9 = 36 MHz */
        /* PLL: (HSE / 2) * 9 */
        RCM->CFG_B.PLL1SRCSEL = 1;
        RCM->CFG_B.PLLHSEPSC = 1;
        RCM->CFG_B.PLL1MULCFG = 7;
#endif

        /* Enable PLL */
        RCM->CTRL_B.PLL1EN = 1;

        /* Wait PLL Ready */
        while (RCM->CTRL_B.PLL1RDYFLG == BIT_RESET);

        /* Select PLL as system clock source */
        RCM->CFG_B.SCLKSEL = 2;

        /* Wait till PLL is used as system clock source */
        while (RCM->CFG_B.SCLKSELSTS != 0x02);
    }
}

#elif defined SYSTEM_CLOCK_48MHz
/*!
 * @brief       Sets System clock frequency to 46MHz and configure HCLK, PCLK2 and PCLK1 prescalers
 *
 * @param       None
 *
 * @retval      None
 *
 */
static void SystemClock48M(void)
{
    __IO uint32_t i;

    RCM->CTRL_B.HSEEN = BIT_SET;

    for (i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if (RCM->CTRL_B.HSERDYFLG)
        {
            break;
        }
    }

    if (RCM->CTRL_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->CTRL1_B.PBEN = BIT_SET;
        /* Flash 1 wait state */
        FMC->CTRL1_B.WS = 1;

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC = 0X00;
        /* PCLK2 = HCLK */
        RCM->CFG_B.APB2PSC = 0;
        /* PCLK1 = HCLK / 2 */
        RCM->CFG_B.APB1PSC = 4;

#ifdef APM32F10X_CL
        /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz (HSE is 25MHz for APM32F10X_CL) */
        /* PLL configuration: PLLCLK = (PLL2 / 5) * 6 = 48 MHz */

        RCM->CFG2_B.PLLPSC2 = 4;
        RCM->CFG2_B.PLL2MUL = 0x06;

        RCM->CFG2_B.PLLPSC1SRC = 1;
        RCM->CFG2_B.PLLPSC1 = 0x4;

        /* Enable PLL2 */
        RCM->CTRL_B.PLL2EN = 1;
        /* Wait till PLL2 is ready */
        while (RCM->CTRL_B.PLL2RDYFLG == BIT_RESET);

        RCM->CFG_B.PLL1SRCSEL = 1;
        RCM->CFG_B.PLL1MULCFG = 4;
#else
        /* PLL: HSE * 6 */
        RCM->CFG_B.PLL1SRCSEL = 1;
        RCM->CFG_B.PLL1MULCFG = 4;
#endif

        /* Enable PLL */
        RCM->CTRL_B.PLL1EN = 1;

        /* Wait PLL Ready */
        while (RCM->CTRL_B.PLL1RDYFLG == BIT_RESET);

        /* Select PLL as system clock source */
        RCM->CFG_B.SCLKSEL = 2;

        /* Wait till PLL is used as system clock source */
        while (RCM->CFG_B.SCLKSELSTS != 0x02);
    }
}

#elif defined SYSTEM_CLOCK_56MHz
/*!
 * @brief       Sets System clock frequency to 56MHz and configure HCLK, PCLK2 and PCLK1 prescalers
 *
 * @param       None
 *
 * @retval      None
 *
 */
static void SystemClock56M(void)
{
    __IO uint32_t i;

    RCM->CTRL_B.HSEEN = BIT_SET;

    for (i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if (RCM->CTRL_B.HSERDYFLG)
        {
            break;
        }
    }

    if (RCM->CTRL_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->CTRL1_B.PBEN = BIT_SET;
        /* Flash 2 wait state */
        FMC->CTRL1_B.WS = 2;

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC = 0X00;
        /* PCLK2 = HCLK */
        RCM->CFG_B.APB2PSC = 0;
        /* PCLK1 = HCLK / 2 */
        RCM->CFG_B.APB1PSC = 4;

#ifdef APM32F10X_CL
        /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz (HSE is 25MHz for APM32F10X_CL) */
        /* PLL configuration: PLLCLK = (PLL2 / 5) * 7 = 56 MHz */

        RCM->CFG2_B.PLLPSC2 = 4;
        RCM->CFG2_B.PLL2MUL = 0x06;

        RCM->CFG2_B.PLLPSC1SRC = 1;
        RCM->CFG2_B.PLLPSC1 = 0x4;

        /* Enable PLL2 */
        RCM->CTRL_B.PLL2EN = 1;
        /* Wait till PLL2 is ready */
        while (RCM->CTRL_B.PLL2RDYFLG == BIT_RESET);

        RCM->CFG_B.PLL1SRCSEL = 1;
        RCM->CFG_B.PLL1MULCFG = 5;
#else
        /* PLL: HSE * 7 */
        RCM->CFG_B.PLL1SRCSEL = 1;
        RCM->CFG_B.PLL1MULCFG = 5;
#endif

        /* Enable PLL */
        RCM->CTRL_B.PLL1EN = 1;

        /* Wait PLL Ready */
        while (RCM->CTRL_B.PLL1RDYFLG == BIT_RESET);

        /* Select PLL as system clock source */
        RCM->CFG_B.SCLKSEL = 2;

        /* Wait till PLL is used as system clock source */
        while (RCM->CFG_B.SCLKSELSTS != 0x02);
    }
}

#elif defined SYSTEM_CLOCK_72MHz
/*!
 * @brief       Sets System clock frequency to 72MHz and configure HCLK, PCLK2 and PCLK1 prescalers
 *
 * @param       None
 *
 * @retval      None
 *
 */
static void SystemClock72M(void)
{
    __IO uint32_t i;

    RCM->CTRL_B.HSEEN = BIT_SET;

    for (i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if (RCM->CTRL_B.HSERDYFLG)
        {
            break;
        }
    }

    if (RCM->CTRL_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->CTRL1_B.PBEN = BIT_SET;
        /* Flash 2 wait state */
        FMC->CTRL1_B.WS = 2;

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC = 0X00;
        /* PCLK2 = HCLK */
        RCM->CFG_B.APB2PSC = 0;
        /* PCLK1 = HCLK / 2 */
        RCM->CFG_B.APB1PSC = 4;

#ifdef APM32F10X_CL
        /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz (HSE is 25MHz for APM32F10X_CL) */
        /* PLL configuration: PLLCLK = (PLL2 / 5) * 9 = 72 MHz */

        RCM->CFG2_B.PLLPSC2 = 4;
        RCM->CFG2_B.PLL2MUL = 0x06;

        RCM->CFG2_B.PLLPSC1SRC = 1;
        RCM->CFG2_B.PLLPSC1 = 0x4;

        /* Enable PLL2 */
        RCM->CTRL_B.PLL2EN = 1;
        /* Wait till PLL2 is ready */
        while (RCM->CTRL_B.PLL2RDYFLG == BIT_RESET);

        RCM->CFG_B.PLL1SRCSEL = 1;
        RCM->CFG_B.PLL1MULCFG = 7;
#else
        /* PLL: HSE * 9 */
        RCM->CFG_B.PLL1SRCSEL = 1;
        RCM->CFG_B.PLL1MULCFG = 7;
#endif

        /* Enable PLL */
        RCM->CTRL_B.PLL1EN = 1;

        /* Wait PLL Ready */
        while (RCM->CTRL_B.PLL1RDYFLG == BIT_RESET);

        /* Select PLL as system clock source */
        RCM->CFG_B.SCLKSEL = 2;

        /* Wait till PLL is used as system clock source */
        while (RCM->CFG_B.SCLKSELSTS != 0x02);
    }

}

#elif defined SYSTEM_CLOCK_96MHz
/*!
 * @brief       Sets System clock frequency to 96MHz and configure HCLK, PCLK2 and PCLK1 prescalers
 *
 * @param       None
 *
 * @retval      None
 *
 */
static void SystemClock96M(void)
{
    __IO uint32_t i;

    RCM->CTRL_B.HSEEN = BIT_SET;

    for (i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if (RCM->CTRL_B.HSERDYFLG)
        {
            break;
        }
    }

    if (RCM->CTRL_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->CTRL1_B.PBEN = BIT_SET;
        /* Flash 3 wait state */
        FMC->CTRL1_B.WS = 3;

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC = 0X00;
        /* PCLK2 = HCLK */
        RCM->CFG_B.APB2PSC = 0;
        /* PCLK1 = HCLK / 2 */
        RCM->CFG_B.APB1PSC = 4;

#ifdef APM32F10X_CL
        /* PLL2 configuration: PLL2CLK = (HSE / 5) * 12 = 60 MHz (HSE is 25MHz for APM32F10X_CL) */
        /* PLL configuration: PLLCLK = (PLL2 / 5) * 8 = 96 MHz */

        RCM->CFG2_B.PLLPSC2 = 4;
        RCM->CFG2_B.PLL2MUL = 10;

        RCM->CFG2_B.PLLPSC1SRC = 1;
        RCM->CFG2_B.PLLPSC1 = 4;

        /* Enable PLL2 */
        RCM->CTRL_B.PLL2EN = 1;
        /* Wait till PLL2 is ready */
        while (RCM->CTRL_B.PLL2RDYFLG == BIT_RESET);

        RCM->CFG_B.PLL1SRCSEL = 1;
        RCM->CFG_B.PLL1MULCFG = 6;
#else
        /* PLL: HSE * 12 */
        RCM->CFG_B.PLL1SRCSEL = 1;
        RCM->CFG_B.PLL1MULCFG = 10;
#endif

        /* Enable PLL */
        RCM->CTRL_B.PLL1EN = 1;

        /* Wait PLL Ready */
        while (RCM->CTRL_B.PLL1RDYFLG == BIT_RESET);

        /* Select PLL as system clock source */
        RCM->CFG_B.SCLKSEL = 2;

        /* Wait till PLL is used as system clock source */
        while (RCM->CFG_B.SCLKSELSTS != 0x02);
    }
}
#endif

/**@} end of group System_Functions */
/**@} end of group APM32F10x_System */
/**@} end of group CMSIS */
