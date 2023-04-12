/*!
 * @file        system_apm32e10x.c
 *
 * @brief       CMSIS Cortex-M3 Device Peripheral Access Layer System Source File
 *
 * @version     V1.0.2
 *
 * @date        2022-12-31
 *
 * @attention
 *
 *  Copyright (C) 2021-2023 Geehy Semiconductor
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

#include "apm32e10x.h"

/** @addtogroup CMSIS
  @{
*/

/** @addtogroup APM32E10x_System
  * @brief APM32E10x system configuration
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
//#define SYSTEM_CLOCK_120MHz  (120000000)

/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET     0x00

/**@} end of group System_Macros */

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
#elif defined SYSTEM_CLOCK_96MHz
uint32_t SystemCoreClock         = SYSTEM_CLOCK_96MHz;
#else
uint32_t SystemCoreClock         = SYSTEM_CLOCK_120MHz;
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
#elif defined SYSTEM_CLOCK_120MHz
static void SystemClock120M(void);
#endif

/*!
 * @brief       Setup the microcontroller system
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void SystemInit (void)
{
    /** Set HSIEN bit */
    RCM->CTRL_B.HSIEN = BIT_SET;
    /** Reset SCLKSW, AHBPSC, APB1PSC, APB2PSC, ADCPSC and MCOSEL bits */
    RCM->CFG &= (uint32_t)0xF8FF0000;
    /** Reset HSEEN, CSSEN and PLLEN bits */
    RCM->CTRL &= (uint32_t)0xFEF6FFFF;
    /** Reset HSEBCFG bit */
    RCM->CTRL_B.HSEBCFG = BIT_RESET;
    /** Reset PLLSRCSEL, PLLHSEPSC, PLLMULCFG and USBDIV bits */
    RCM->CFG &= (uint32_t)0xFF80FFFF;
    /** Disable all interrupts and clear pending bits */
    RCM->INT = 0x009F0000;

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
 * @note
 */
void SystemCoreClockUpdate (void)
{
    uint32_t sysClock, pllMull, pllSource, Prescaler;
    uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

    sysClock = RCM->CFG_B.SCLKSWSTS;

    switch(sysClock)
    {
        /** sys clock is HSI */
        case 0:
            SystemCoreClock = HSI_VALUE;
        break;

        /** sys clock is HSE */
        case 1:
            SystemCoreClock = HSE_VALUE;
        break;

        /** sys clock is PLL */
        case 2:
            pllMull = RCM->CFG_B.PLLMULCFG + 2;
            pllSource = RCM->CFG_B.PLLSRCSEL;

            /** PLL entry clock source is HSE */
            if(pllSource == BIT_SET)
            {
                SystemCoreClock = HSE_VALUE * pllMull;

                /** HSE clock divided by 2 */
                if(pllSource == RCM->CFG_B.PLLHSEPSC)
                {
                    SystemCoreClock >>= 1;
                }
            }
            /** PLL entry clock source is HSI/2 */
            else
            {
                SystemCoreClock = (HSI_VALUE >> 1) * pllMull;
            }
            break;

        default:
            SystemCoreClock  = HSI_VALUE;
        break;
    }

    Prescaler = AHBPrescTable[RCM->CFG_B.AHBPSC];
    SystemCoreClock >>= Prescaler;
}

/*!
 * @brief       Configures the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
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
#elif defined SYSTEM_CLOCK_120MHz
    SystemClock120M();
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
 * @note
 */
static void SystemClockHSE(void)
{
    __IO uint32_t i;

    RCM->CTRL_B.HSEEN= BIT_SET;

    for(i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if(RCM->CTRL_B.HSERDYFLG)
        {
            break;
        }
    }

    if(RCM->CTRL_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->CTRL1_B.PBEN = BIT_SET;
        /* Flash 0 wait state */
        FMC->CTRL1_B.WS = 0;

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC= 0X00;
        /* PCLK2 = HCLK */
        RCM->CFG_B.APB2PSC= 0;
        /* PCLK1 = HCLK */
        RCM->CFG_B.APB1PSC = 0;

        /* Select HSE as system clock source */
        RCM->CFG_B.SCLKSW = 1;

        /** Wait till HSE is used as system clock source */
        while(RCM->CFG_B.SCLKSWSTS!= 0x01);
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
 * @note
 */
static void SystemClock24M(void)
{
    __IO uint32_t i;

    RCM->CTRL_B.HSEEN= BIT_SET;

    for(i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if(RCM->CTRL_B.HSERDYFLG)
        {
            break;
        }
    }

    if(RCM->CTRL_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->CTRL1_B.PBEN = BIT_SET;
        /* Flash 0 wait state */
        FMC->CTRL1_B.WS = 0;

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC= 0X00;
        /* PCLK2 = HCLK */
        RCM->CFG_B.APB2PSC= 0;
        /* PCLK1 = HCLK */
        RCM->CFG_B.APB1PSC = 0;

        /** PLL: (HSE / 2) * 6 */
        RCM->CFG_B.PLLSRCSEL = 1;
        RCM->CFG_B.PLLHSEPSC = 1;
        RCM->CFG_B.PLLMULCFG = 4;

        /** Enable PLL */
        RCM->CTRL_B.PLLEN = 1;
        /** Wait PLL Ready */
        while(RCM->CTRL_B.PLLRDYFLG == BIT_RESET);

        /* Select PLL as system clock source */
        RCM->CFG_B.SCLKSW = 2;
        /* Wait till PLL is used as system clock source */
        while(RCM->CFG_B.SCLKSWSTS!= 0x02);
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
 * @note
 */
static void SystemClock36M(void)
{
    __IO uint32_t i;

    RCM->CTRL_B.HSEEN= BIT_SET;

    for(i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if(RCM->CTRL_B.HSERDYFLG)
        {
            break;
        }
    }

    if(RCM->CTRL_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->CTRL1_B.PBEN = BIT_SET;
        /* Flash 1 wait state */
        FMC->CTRL1_B.WS = 1;

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC= 0X00;
        /* PCLK2 = HCLK */
        RCM->CFG_B.APB2PSC= 0;
        /* PCLK1 = HCLK */
        RCM->CFG_B.APB1PSC = 0;

        /** PLL: (HSE / 2) * 9 */
        RCM->CFG_B.PLLSRCSEL = 1;
        RCM->CFG_B.PLLHSEPSC = 1;
        RCM->CFG_B.PLLMULCFG = 7;

        /** Enable PLL */
        RCM->CTRL_B.PLLEN = 1;
        /** Wait PLL Ready */
        while(RCM->CTRL_B.PLLRDYFLG == BIT_RESET);

        /* Select PLL as system clock source */
        RCM->CFG_B.SCLKSW = 2;
        /* Wait till PLL is used as system clock source */
        while(RCM->CFG_B.SCLKSWSTS != 0x02);
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
 * @note
 */
static void SystemClock48M(void)
{
    __IO uint32_t i;

    RCM->CTRL_B.HSEEN= BIT_SET;

    for(i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if(RCM->CTRL_B.HSERDYFLG)
        {
            break;
        }
    }

    if(RCM->CTRL_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->CTRL1_B.PBEN = BIT_SET;
        /* Flash 1 wait state */
        FMC->CTRL1_B.WS = 1;

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC= 0X00;
        /* PCLK2 = HCLK */
        RCM->CFG_B.APB2PSC= 0;
        /* PCLK1 = HCLK / 2 */
        RCM->CFG_B.APB1PSC = 4;

        /** PLL: HSE * 6 */
        RCM->CFG_B.PLLSRCSEL = 1;
        RCM->CFG_B.PLLMULCFG = 4;

        /** Enable PLL */
        RCM->CTRL_B.PLLEN = 1;
        /** Wait PLL Ready */
        while(RCM->CTRL_B.PLLRDYFLG == BIT_RESET);

        /* Select PLL as system clock source */
        RCM->CFG_B.SCLKSW = 2;
        /* Wait till PLL is used as system clock source */
        while(RCM->CFG_B.SCLKSWSTS!= 0x02);
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
 * @note
 */
static void SystemClock56M(void)
{
    __IO uint32_t i;

    RCM->CTRL_B.HSEEN= BIT_SET;

    for(i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if(RCM->CTRL_B.HSERDYFLG)
        {
            break;
        }
    }

    if(RCM->CTRL_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->CTRL1_B.PBEN = BIT_SET;
        /* Flash 2 wait state */
        FMC->CTRL1_B.WS = 2;

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC= 0X00;
        /* PCLK2 = HCLK */
        RCM->CFG_B.APB2PSC= 0;
        /* PCLK1 = HCLK / 2 */
        RCM->CFG_B.APB1PSC = 4;

        /** PLL: HSE * 7 */
        RCM->CFG_B.PLLSRCSEL = 1;
        RCM->CFG_B.PLLMULCFG = 5;

        /** Enable PLL */
        RCM->CTRL_B.PLLEN = 1;
        /** Wait PLL Ready */
        while(RCM->CTRL_B.PLLRDYFLG == BIT_RESET);

        /* Select PLL as system clock source */
        RCM->CFG_B.SCLKSW = 2;
        /* Wait till PLL is used as system clock source */
        while(RCM->CFG_B.SCLKSWSTS!= 0x02);
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
 * @note
 */
static void SystemClock72M(void)
{
    __IO uint32_t i;

    RCM->CTRL_B.HSEEN= BIT_SET;

    for(i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if(RCM->CTRL_B.HSERDYFLG)
        {
            break;
        }
    }

    if(RCM->CTRL_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->CTRL1_B.PBEN = BIT_SET;
        /* Flash 2 wait state */
        FMC->CTRL1_B.WS = 2;

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC= 0X00;
        /* PCLK2 = HCLK */
        RCM->CFG_B.APB2PSC= 0;
        /* PCLK1 = HCLK / 2 */
        RCM->CFG_B.APB1PSC = 4;

        /** PLL: HSE * 9 */
        RCM->CFG_B.PLLSRCSEL = 1;
        RCM->CFG_B.PLLMULCFG = 7;

        /** Enable PLL */
        RCM->CTRL_B.PLLEN = 1;
        /** Wait PLL Ready */
        while(RCM->CTRL_B.PLLRDYFLG == BIT_RESET);

        /* Select PLL as system clock source */
        RCM->CFG_B.SCLKSW = 2;
        /* Wait till PLL is used as system clock source */
        while(RCM->CFG_B.SCLKSWSTS!= 0x02);
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
 * @note
 */
static void SystemClock96M(void)
{
    __IO uint32_t i;

    RCM->CTRL_B.HSEEN= BIT_SET;

    for(i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if(RCM->CTRL_B.HSERDYFLG)
        {
            break;
        }
    }

    if(RCM->CTRL_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->CTRL1_B.PBEN = BIT_SET;
        /* Flash 3 wait state */
        FMC->CTRL1_B.WS = 3;

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC= 0X00;
        /* PCLK2 = HCLK */
        RCM->CFG_B.APB2PSC= 0;
        /* PCLK1 = HCLK / 2 */
        RCM->CFG_B.APB1PSC = 4;

        /** PLL: HSE * 12 */
        RCM->CFG_B.PLLSRCSEL = 1;
        RCM->CFG_B.PLLMULCFG = 10;

        /** Enable PLL */
        RCM->CTRL_B.PLLEN = 1;
        /** Wait PLL Ready */
        while(RCM->CTRL_B.PLLRDYFLG == BIT_RESET);

        /* Select PLL as system clock source */
        RCM->CFG_B.SCLKSW = 2;
        /* Wait till PLL is used as system clock source */
        while(RCM->CFG_B.SCLKSWSTS!= 0x02);
    }
}

#elif defined SYSTEM_CLOCK_120MHz
/*!
 * @brief       Sets System clock frequency to 96MHz and configure HCLK, PCLK2 and PCLK1 prescalers
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
static void SystemClock120M(void)
{
    __IO uint32_t i;

    RCM->CTRL_B.HSEEN= BIT_SET;

    for(i = 0; i < HSE_STARTUP_TIMEOUT; i++)
    {
        if(RCM->CTRL_B.HSERDYFLG)
        {
            break;
        }
    }

    if(RCM->CTRL_B.HSERDYFLG)
    {
        /* Enable Prefetch Buffer */
        FMC->CTRL1_B.PBEN = BIT_SET;
        /* Flash 3 wait state */
        FMC->CTRL1_B.WS = 3;

        /* HCLK = SYSCLK */
        RCM->CFG_B.AHBPSC= 0X00;
        /* PCLK2 = HCLK */
        RCM->CFG_B.APB2PSC= 0;
        /* PCLK1 = HCLK / 2 */
        RCM->CFG_B.APB1PSC = 4;

        /** PLL: HSE * 15 */
        RCM->CFG_B.PLLSRCSEL = 1;
        RCM->CFG_B.PLLMULCFG = 13;

        /** Enable PLL */
        RCM->CTRL_B.PLLEN = 1;
        /** Wait PLL Ready */
        while(RCM->CTRL_B.PLLRDYFLG == BIT_RESET);

        /* Select PLL as system clock source */
        RCM->CFG_B.SCLKSW = 2;
        /* Wait till PLL is used as system clock source */
        while(RCM->CFG_B.SCLKSWSTS!= 0x02);
    }
}
#endif

/**@} end of group System_Functions */
/**@} end of group APM32E10x_System */
/**@} end of group CMSIS */
