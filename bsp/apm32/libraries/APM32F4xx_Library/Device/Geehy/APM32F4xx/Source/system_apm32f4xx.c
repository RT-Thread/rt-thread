/*!
 * @file        system_apm32f4xx.c
 *
 * @brief       CMSIS Cortex-M4 Device Peripheral Access Layer System Source File
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "apm32f4xx.h"
#include "system_apm32f4xx.h"

/** @addtogroup CMSIS
  @{
*/

/** @addtogroup APM32F4xx_System
  * @brief APM32F4xx system configuration
  @{
*/

/** @defgroup System_Macros
  @{
*/

/* Uncomment the following line if you need to use external SRAM as data memory  */
/* #define DATA_IN_ExtSRAM */

/* Uncomment the following line if you need to relocate your vector Table in Internal SRAM. */
/* #define VECT_TAB_SRAM */

/* Vector Table base offset field. This value must be a multiple of 0x200. */
#define VECT_TAB_OFFSET  0x00

/* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_B) * PLL_A */
#define PLL_B      8

/* USB OTG FS, SDIO and RNG Clock =  PLL_VCO / PLL_D */
#define PLL_D      7

#define PLL_A      336
/* SYSCLK = PLL_VCO / PLL_C */
#define PLL_C      2

/**@} end of group System_Macros*/

/** @defgroup System_Variables
  @{
*/

/**
 * @brief    APM32F4xx_System_Private_Variables
 */

uint32_t SystemCoreClock = 168000000;

__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

/**@} end of group System_Variables */

/** @defgroup System_Functions
  @{
*/

/**
 * @brief    APM32F4xx_System_Private_FunctionPrototypes
 */

static void SystemClockConfig(void);

#if defined(DATA_IN_ExtSRAM)
    static void SystemInit_ExtSRAM(void);
#endif /* DATA_IN_ExtSRAM */

/*!
 * @brief       Setup the microcontroller system
 *
 * @param       None
 *
 * @retval      None
 */
void SystemInit(void)
{
    /* FPU settings */
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); //!< set CP10 and CP11 Full Access
#endif
    /* Reset the RCM clock configuration to the default reset state */
    /* Set HSIEN bit */
    RCM->CTRL_B.HSIEN = BIT_SET;

    /* Reset CFG register */
    RCM->CFG = 0x00000000;

    /* Reset HSEEN, CSSEN and PLL1EN bits */
    RCM->CTRL &= (uint32_t)0xFEF6FFFF;

    /* Reset PLL1CFG register */
    RCM->PLL1CFG = 0x24003010;

    /* Reset HSEBCFG bit */
    RCM->CTRL &= (uint32_t)0xFFFBFFFF;

    /* Disable all interrupts */
    RCM->INT = 0x00000000;

#if defined(DATA_IN_ExtSRAM)
    SystemInit_ExtSRAM();
#endif /* DATA_IN_ExtSRAM */

    SystemClockConfig();

    /* Configure the Vector Table location add offset address */
#ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
#else
    SCB->VTOR = FMC_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH */
#endif
}

/*!
 * @brief       Update SystemCoreClock variable according to Clock Register Values
 *              The SystemCoreClock variable contains the core clock (HCLK)
 *
 * @param       None
 *
 * @retval      None
 */
void SystemCoreClockUpdate(void)
{
    uint32_t sysClock, pllvco, pllc, pllClock, pllb;

    /* Get SYSCLK source */
    sysClock = RCM->CFG_B.SCLKSWSTS;

    switch (sysClock)
    {
    case 0:
        SystemCoreClock = HSI_VALUE;
        break;

    case 1:
        SystemCoreClock = HSE_VALUE;
        break;

    case 2:
        pllClock = RCM->PLL1CFG_B.PLL1CLKS;
        pllb = RCM->PLL1CFG_B.PLLB;

        if (pllClock == 0)
        {
            /* HSI used as PLL clock source */
            pllvco = (HSI_VALUE / pllb) * (RCM->PLL1CFG_B.PLL1A); //!< PLL_VCO = (HSI_VALUE / PLL_B) * PLL_A */
        }
        else
        {
            /* HSE used as PLL clock source */
            pllvco = (HSE_VALUE / pllb) * (RCM->PLL1CFG_B.PLL1A); //!< PLL_VCO = (HSE_VALUE / PLL_B) * PLL_A */
        }

        pllc = ((RCM->PLL1CFG_B.PLL1C) + 1) * 2;
        SystemCoreClock = pllvco / pllc;
        break;

    default:
        SystemCoreClock = HSI_VALUE;
        break;
    }

    /* Compute HCLK frequency */
    /* Get HCLK prescaler */
    sysClock = AHBPrescTable[(RCM->CFG_B.AHBPSC)];
    /* HCLK frequency */
    SystemCoreClock >>= sysClock;
}

/*!
 * @brief     Configures the System clock source, PLL Multiplier and Divider factors,
 *            AHB/APBx prescalers and Flash settings
 *
 * @param     None
 *
 * @retval    None
 */
static void SystemClockConfig(void)
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
        /* Select regulator voltage output Scale 1 mode */
        RCM->APB1CLKEN_B.PMUEN = BIT_SET;
        PMU->CTRL_B.VOSSEL = BIT_SET;

        /* HCLK = SYSCLK / 1*/
        RCM->CFG_B.AHBPSC = 0x0000;

        /* PCLK2 = HCLK / 2*/
        RCM->CFG_B.APB2PSC = 0x04;

        /* PCLK1 = HCLK / 4*/
        RCM->CFG_B.APB1PSC = 0x05;

        /* Configure the main PLL */
        RCM->PLL1CFG = PLL_B | (PLL_A << 6) | (((PLL_C >> 1) - 1) << 16) | (PLL_D << 24);
        RCM->PLL1CFG_B.PLL1CLKS = 0x01;

        /* Enable the main PLL */
        RCM->CTRL_B.PLL1EN = BIT_SET;

        /* Wait till the main PLL is ready */
        while (RCM->CTRL_B.PLL1RDYFLG == 0)
        {
        }

        /* Configure Flash prefetch, Instruction cache, Data cache and wait state */
        FMC->ACCTRL = 0x05 | BIT8 | BIT9 | BIT10;

        /* Select the main PLL as system clock source */
        RCM->CFG_B.SCLKSEL = RESET;
        RCM->CFG_B.SCLKSEL = 0x02;

        /* Wait till the main PLL is used as system clock source */
        while ((RCM->CFG_B.SCLKSWSTS) != 0x02)
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock configuration. */
    }
}

#if defined (DATA_IN_ExtSRAM)

/*!
 * @brief     Setup the external memory controller. Called in startup_apm32f4xx.s before jump to main.
 *            This function configures the external SRAM
 *            This SRAM will be used as program data memory (including heap and stack).
 *
 * @param     None
 *
 * @retval    None
 */
void SystemInit_ExtSRAM(void)
{
    /* Enable GPIOD, GPIOE, GPIOF and GPIOG interface clock */
    RCM->AHB1CLKEN |= 0x00000078;

    /* Connect PDx pins to FMC Alternate function */
    GPIOD->ALFL  = 0x00cc00cc;
    GPIOD->ALFH  = 0xcccccccc;
    /* Configure PDx pins in Alternate function mode */
    GPIOD->MODE  = 0xaaaa0a0a;
    /* Configure PDx pins speed to 100 MHz */
    GPIOD->OSSEL = 0xffff0f0f;
    /* Configure PDx pins Output type to push-pull */
    GPIOD->OMODE = 0x00000000;
    /* No pull-up, pull-down for PDx pins */
    GPIOD->PUPD  = 0x00000000;

    /* Connect PEx pins to FMC Alternate function */
    GPIOE->ALFL  = 0xcccccccc;
    GPIOE->ALFH  = 0xcccccccc;
    /* Configure PEx pins in Alternate function mode */
    GPIOE->MODE  = 0xaaaaaaaa;
    /* Configure PEx pins speed to 100 MHz */
    GPIOE->OSSEL = 0xffffffff;
    /* Configure PEx pins Output type to push-pull */
    GPIOE->OMODE = 0x00000000;
    /* No pull-up, pull-down for PEx pins */
    GPIOE->PUPD  = 0x00000000;

    /* Connect PFx pins to FMC Alternate function */
    GPIOF->ALFL  = 0x00cccccc;
    GPIOF->ALFH  = 0xcccc0000;
    /* Configure PFx pins in Alternate function mode */
    GPIOF->MODE  = 0xaa000aaa;
    /* Configure PFx pins speed to 100 MHz */
    GPIOF->OSSEL = 0xff000fff;
    /* Configure PFx pins Output type to push-pull */
    GPIOF->OMODE = 0x00000000;
    /* No pull-up, pull-down for PFx pins */
    GPIOF->PUPD  = 0x00000000;

    /* Connect PGx pins to FMC Alternate function */
    GPIOG->ALFL  = 0x00cccccc;
    GPIOG->ALFH  = 0x000000c0;
    /* Configure PGx pins in Alternate function mode */
    GPIOG->MODE  = 0x00080aaa;
    /* Configure PGx pins speed to 100 MHz */
    GPIOG->OSSEL = 0x000c0fff;
    /* Configure PGx pins Output type to push-pull */
    GPIOG->OMODE = 0x00000000;
    /* No pull-up, pull-down for PGx pins */
    GPIOG->PUPD  = 0x00000000;

    /* FMC Configuration */
    /* Enable the FMC/SMC interface clock */
    RCM->AHB3CLKEN |= 0x00000001;

    /* Configure and enable Bank1_SRAM2 */
    SMC_Bank1->CSCTRL2  = 0x00001011;
    SMC_Bank1->CSTIM2   = 0x00000201;
    SMC_Bank1E->WRTTIM2 = 0x0fffffff;
}
#endif /* DATA_IN_ExtSRAM */

/**@} end of group System_Functions */
/**@} end of group APM32F4xx_System */
/**@} end of group CMSIS */
