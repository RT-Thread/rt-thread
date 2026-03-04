/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file system_n32l40x.c
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "n32l40x.h"

/* Uncomment the line corresponding to the desired System clock (SYSCLK)
   frequency (after reset the HSI is used as SYSCLK source)

   IMPORTANT NOTE:
   ==============
   1. After each device reset the HSI is used as System clock source.

   2. Please make sure that the selected System clock doesn't exceed your
   device's maximum frequency.

   3. If none of the define below is enabled, the HSI is used as System clock
    source.

   4. The System clock configuration functions provided within this file assume
   that:
        - For Low, Medium and High density Value line devices an external 8MHz
          crystal is used to drive the System clock.
        - For Low, Medium and High density devices an external 8MHz crystal is
          used to drive the System clock.
        - For Connectivity line devices an external 25MHz crystal is used to
   drive the System clock. If you are using different crystal you have to adapt
   those functions accordingly.
    */

#define SYSCLK_USE_MSI     0
#define SYSCLK_USE_HSI     1
#define SYSCLK_USE_HSE     2
#define SYSCLK_USE_HSI_PLL 3
#define SYSCLK_USE_HSE_PLL 4

#ifndef SYSCLK_FREQ
#define SYSCLK_FREQ 64000000
#endif

/*
* SYSCLK_SRC *
** SYSCLK_USE_MSI      **
** SYSCLK_USE_HSI      **
** SYSCLK_USE_HSE      **
** SYSCLK_USE_HSI_PLL  **
** SYSCLK_USE_HSE_PLL  **
*/
#ifndef SYSCLK_SRC
#define SYSCLK_SRC SYSCLK_USE_HSE_PLL
#endif

#define PLL_DIV2_DISABLE 0x00000000
#define PLL_DIV2_ENABLE 0x00000002
#define SRAM_VOL   (__IO unsigned*)(0x40001800 + 0x20)
#define ConfigSRAMVoltage(vale) do{(*SRAM_VOL ) &= (~(uint32_t)(1 <<25));(*SRAM_VOL ) |= (uint32_t)(vale <<25);}while (0) //vale only equal to 0,1
#if SYSCLK_SRC == SYSCLK_USE_MSI

    #if (SYSCLK_FREQ == MSI_VALUE_L0)
        #define MSI_CLK 0
    #elif (SYSCLK_FREQ == MSI_VALUE_L1)
        #define MSI_CLK 1
    #elif (SYSCLK_FREQ == MSI_VALUE_L2)
        #define MSI_CLK 2
    #elif (SYSCLK_FREQ == MSI_VALUE_L3)
        #define MSI_CLK 3
    #elif (SYSCLK_FREQ == MSI_VALUE_L4)
        #define MSI_CLK 4
    #elif (SYSCLK_FREQ == MSI_VALUE_L5)
        #define MSI_CLK 5
    #elif (SYSCLK_FREQ == MSI_VALUE_L6)
        #define MSI_CLK 6
    #else
        #error SYSCL_FREQ must be set to MSI_VALUE_Lx(x=0~6)
    #endif

#elif SYSCLK_SRC == SYSCLK_USE_HSI

    #if SYSCLK_FREQ != HSI_VALUE
        #error SYSCL_FREQ must be set to HSI_VALUE
    #endif

#elif SYSCLK_SRC == SYSCLK_USE_HSE

    #ifndef HSE_VALUE
        #error HSE_VALUE must be defined!
    #endif

    #if SYSCLK_FREQ != HSE_VALUE
        #error SYSCL_FREQ must be set to HSE_VALUE
    #endif

#elif SYSCLK_SRC == SYSCLK_USE_HSI_PLL

    #ifndef HSI_VALUE
        #error HSI_VALUE must be defined!
    #endif

    #if ((SYSCLK_FREQ % (HSI_VALUE / 2)) == 0) && (SYSCLK_FREQ / (HSI_VALUE / 2) >= 2)                                     \
        && (SYSCLK_FREQ / (HSI_VALUE / 2) <= 32)

        #define PLLSRC_DIV 2
        #define PLL_DIV    PLL_DIV2_DISABLE
        #define PLL_MUL    (SYSCLK_FREQ / (HSI_VALUE / 2))

    #elif (SYSCLK_FREQ % HSI_VALUE == 0) && (SYSCLK_FREQ / HSI_VALUE >= 2) && (SYSCLK_FREQ / HSI_VALUE <= 32)

        #define PLLSRC_DIV 1
        #define PLL_DIV    PLL_DIV2_DISABLE
        #define PLL_MUL    (SYSCLK_FREQ / HSI_VALUE)

    #elif ((SYSCLK_FREQ % (HSI_VALUE / 4)) == 0) && (SYSCLK_FREQ / (HSI_VALUE / 4) >= 2)                                     \
          && (SYSCLK_FREQ / (HSI_VALUE / 4) <= 32)

        #define PLLSRC_DIV 2
        #define PLL_DIV    PLL_DIV2_ENABLE
        #define PLL_MUL    (SYSCLK_FREQ / (HSI_VALUE / 4))

    #else
        #error Cannot make a PLL multiply factor to SYSCLK_FREQ.
    #endif

#elif SYSCLK_SRC == SYSCLK_USE_HSE_PLL

    #ifndef HSE_VALUE
        #error HSE_VALUE must be defined!
    #endif

    #if ((SYSCLK_FREQ % (HSE_VALUE / 2)) == 0) && (SYSCLK_FREQ / (HSE_VALUE / 2) >= 2)                                     \
        && (SYSCLK_FREQ / (HSE_VALUE / 2) <= 32)

        #define PLLSRC_DIV 2
        #define PLL_DIV    PLL_DIV2_DISABLE
        #define PLL_MUL    (SYSCLK_FREQ / (HSE_VALUE / 2))

    #elif (SYSCLK_FREQ % HSE_VALUE == 0) && (SYSCLK_FREQ / HSE_VALUE >= 2) && (SYSCLK_FREQ / HSE_VALUE <= 32)

        #define PLLSRC_DIV 1
        #define PLL_DIV    PLL_DIV2_DISABLE
        #define PLL_MUL    (SYSCLK_FREQ / HSE_VALUE)

    #elif ((SYSCLK_FREQ % (HSE_VALUE / 4)) == 0) && (SYSCLK_FREQ / (HSE_VALUE / 4) >= 2)                                     \
          && (SYSCLK_FREQ / (HSE_VALUE / 4) <= 32)

        #define PLLSRC_DIV 2
        #define PLL_DIV    PLL_DIV2_ENABLE
        #define PLL_MUL    (SYSCLK_FREQ / (HSE_VALUE / 4))

    #else
        #error Cannot make a PLL multiply factor to SYSCLK_FREQ.
    #endif

#else
#error wrong value for SYSCLK_SRC
#endif

/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET 0x0 /*!< Vector Table base offset field. This value must be a multiple of 0x200. */

/*******************************************************************************
 *  Clock Definitions
 *******************************************************************************/
uint32_t SystemCoreClock = SYSCLK_FREQ; /*!< System Clock Frequency (Core Clock) */

const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const uint32_t MSIClockTable[7] = {MSI_VALUE_L0, MSI_VALUE_L1, MSI_VALUE_L2, MSI_VALUE_L3,
                                   MSI_VALUE_L4, MSI_VALUE_L5, MSI_VALUE_L6};

static void SetSysClock(void);

#ifdef DATA_IN_ExtSRAM
static void SystemInit_ExtMemCtl(void);
#endif /* DATA_IN_ExtSRAM */

/**
 * @brief  Setup the microcontroller system
 *         Initialize the Embedded Flash Interface, the PLL and update the
 *         SystemCoreClock variable.
 * @note   This function should be used only after reset.
 */
void SystemInit(void)
{
    /* FPU settings
     * ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10 and CP11 Full Access */
#endif

    /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
    /* Set MSIEN bit */
    RCC->CTRLSTS |= (uint32_t)0x00000004;

    /* Reset SW, HPRE, PPRE1, PPRE2 and MCO bits */
    RCC->CFG &= (uint32_t)0xF8FFC000;

    /* Reset HSEON, CLKSSEN and PLLEN bits */
    RCC->CTRL &= (uint32_t)0xFEF6FFFF;

    /* Reset HSEBYP bit */
    RCC->CTRL &= (uint32_t)0xFFFBFFFF;

    /* Reset PLLSRC, PLLXTPRE, PLLMUL, MCOPRES and USBPRES bits */
    RCC->CFG &= (uint32_t)0x0700FFFF;

    /* Reset CFG2 register */
    RCC->CFG2 = 0x00007000;

    /* Reset CFG3 register */
    RCC->CFG3 = 0x00003800;

    /* Reset RDCTRL register */
    RCC->RDCTRL = 0x00000000;

    /* Reset PLLHSIPRE register */
    RCC->PLLHSIPRE = 0x00000000;

    /* Disable all interrupts and clear pending bits  */
    RCC->CLKINT = 0x04BF8000;

    /* Enable ex mode */
    RCC->APB1PCLKEN |= RCC_APB1PCLKEN_PWREN;

    if ((PWR->CTRL1 & PWR_CTRL1_MRSEL2) == PWR_CTRL1_MRSEL2)
    {
        ConfigSRAMVoltage(1);
    }
    /* Enable ICACHE and Prefetch Buffer */
    FLASH->AC |= (uint32_t)(FLASH_AC_ICAHEN | FLASH_AC_PRFTBFEN);

    /* Checks whether the Low Voltage Mode status is SET or RESET */
    if ((FLASH->AC & FLASH_AC_LVMF) != RESET)
    {
        /* FLASH Low Voltage Mode Disable */
        FLASH->AC &= (uint32_t)(~FLASH_AC_LVMEN);
    }

#ifdef DATA_IN_ExtSRAM
    SystemInit_ExtMemCtl();
#endif /* DATA_IN_ExtSRAM */

    /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
    /* Configure the Flash Latency cycles and enable prefetch buffer */
    SetSysClock();

#ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. */
#else
    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. */
#endif
}

/**
 * @brief  Update SystemCoreClock variable according to Clock Register Values.
 *         The SystemCoreClock variable contains the core clock (HCLK), it can
 *         be used by the user application to setup the SysTick timer or
 * configure other parameters.
 *
 * @note   Each time the core clock (HCLK) changes, this function must be called
 *         to update SystemCoreClock variable value. Otherwise, any
 * configuration based on this variable will be incorrect.
 *
 * @note   - The system frequency computed by this function is not the real
 *           frequency in the chip. It is calculated based on the predefined
 *           constant and the selected clock source:
 *
 *           - If SYSCLK source is MSI, SystemCoreClock will contain the
 * MSI_VALUE(*)
 *
 *           - If SYSCLK source is HSI, SystemCoreClock will contain the
 * HSI_VALUE(**)
 *
 *           - If SYSCLK source is HSE, SystemCoreClock will contain the
 * HSE_VALUE(***)
 *
 *           - If SYSCLK source is PLL, SystemCoreClock will contain the
 * HSE_VALUE(***) or HSI_VALUE(**) multiplied by the PLL factors.
 *
 *         (*) MSI_VALUE is a constant defined in n32l40x.h file (default value
 *             4 MHz, 100KHz/200KHz/400KHz/800KHz/1MHz/2MHz/4MHz ) but the real
 *             value may vary depending on the variations in voltage and temperature.
 *
 *         (**) HSI_VALUE is a constant defined in n32l40x.h file (default value
 *             8 MHz) but the real value may vary depending on the variations
 *             in voltage and temperature.
 *
 *         (***) HSE_VALUE is a constant defined in n32l40x.h file (default value
 *              8 MHz or 25 MHz, depedning on the product used), user has to
 *              ensure that HSE_VALUE is same as the real frequency of the crystal used.
 *              Otherwise, this function may have wrong result.
 *
 *         - The result of this function could be not correct when using
 * fractional value for HSE crystal.
 */
void SystemCoreClockUpdate(void)
{
    uint32_t tmp = 0, pllmull = 0, pllsource = 0, plldiv2 = 0;
    uint8_t msi_clk = 0;

    /* Get SYSCLK source
     * -------------------------------------------------------*/
    tmp = RCC->CFG & RCC_CFG_SCLKSTS;

    /* Get MSI clock
     * -------------------------------------------------------*/
    msi_clk = (uint8_t) ((RCC->CTRLSTS & RCC_CTRLSTS_MSIRANGE)>>4);

    switch (tmp)
    {
    case 0x00: /* MSI used as system clock */
        SystemCoreClock = MSIClockTable[msi_clk];
        break;
    case 0x04: /* HSI used as system clock */
        SystemCoreClock = HSI_VALUE;
        break;
    case 0x08: /* HSE used as system clock */
        SystemCoreClock = HSE_VALUE;
        break;
    case 0x0C: /* PLL used as system clock */

        /* Get PLL clock source and multiplication factor
         * ----------------------*/
        pllmull   = RCC->CFG & RCC_CFG_PLLMULFCT;
        pllsource = RCC->CFG & RCC_CFG_PLLSRC;
        plldiv2   = RCC->PLLHSIPRE & RCC_PLLHSIPRE_PLLSRCDIV;

        if ((pllmull & RCC_CFG_PLLMULFCT_4) == 0)
        {
            pllmull = (pllmull >> 18) + 2; // PLLMUL[4]=0
        }
        else
        {
            pllmull = ((pllmull >> 18) - 496) + 1; // PLLMUL[4]=1
        }

        if (pllsource == 0x00)
        {
            /* HSI selected as PLL clock entry */
            if ((RCC->PLLHSIPRE & RCC_PLLHSIPRE_PLLSRCDIV) != (uint32_t)RESET)
            { /* HSI oscillator clock divided by 2 */
                SystemCoreClock = (HSI_VALUE >> 1) * pllmull;
            }
            else
            {
                SystemCoreClock = HSI_VALUE * pllmull;
            }
        }
        else
        {
            /* HSE selected as PLL clock entry */
            if ((RCC->CFG & RCC_CFG_PLLHSEPRES) != (uint32_t)RESET)
            { /* HSE oscillator clock divided by 2 */
                SystemCoreClock = (HSE_VALUE >> 1) * pllmull;
            }
            else
            {
                SystemCoreClock = HSE_VALUE * pllmull;
            }
        }

        if (plldiv2 == 0x02)
        {
            /* PLL source clock divided by 2 selected as PLL clock entry */
            SystemCoreClock >>= 1;
        }

        break;

    default:
        SystemCoreClock = MSIClockTable[msi_clk];
        break;
    }

    /* Compute HCLK clock frequency ----------------*/
    /* Get HCLK prescaler */
    tmp = AHBPrescTable[((RCC->CFG & RCC_CFG_AHBPRES) >> 4)];
    /* HCLK clock frequency */
    SystemCoreClock >>= tmp;
}

/**
 * @brief  Configures the System PWR level to 1.0V
 * .
 */
void ConfigMRVoltage1V(void)
{
    uint32_t  i=0;
    ConfigSRAMVoltage(1);                  //SRAM read margin setting switch in 0.9/lprun mode: use low voltage mode settings and 1.0v use normal mode
    PWR->CTRL1 &= (uint32_t)(~PWR_CTRL1_MRSEL);
    PWR->CTRL1 |= PWR_CTRL1_MRSEL2;        //MR=1.0V
    while ((PWR->STS2 &PWR_STS2_MRF) != 0);               // wait VOSF to be 0 first
    for(i=0;i<0x2A;i++);
    while ((PWR->STS2 & PWR_STS2_MRF) != PWR_STS2_MRF);   // wait VOSF to be 1 then
}
/**
 * @brief  Configures the System clock frequency, HCLK, PCLK2 and PCLK1
 * prescalers.
 */
static void SetSysClock(void)
{
    uint32_t rcc_cfg        = 0;
    uint32_t rcc_pllhsipre  = 0;
    uint32_t StartUpCounter = 0;

#if (SYSCLK_SRC == SYSCLK_USE_MSI)
    uint8_t i=0;
    bool MSIStatus = 0;
    /* Config MSI */
    RCC->CTRLSTS &= 0xFFFFFF8F;
    /*Delay for while*/
    for(i=0;i<0x30;i++);
    RCC->CTRLSTS |= (((uint32_t)MSI_CLK) << 4);
    /*Delay for while*/
    for(i=0;i<0x30;i++);
    /* Enable MSI */
    RCC->CTRLSTS |= ((uint32_t)RCC_CTRLSTS_MSIEN);

    /* Wait till MSI is ready and if Time out is reached exit */
    do
    {
        MSIStatus = RCC->CTRLSTS & RCC_CTRLSTS_MSIRD;
        StartUpCounter++;
    } while ((MSIStatus == 0) && (StartUpCounter != MSI_STARTUP_TIMEOUT));

    MSIStatus = ((RCC->CTRLSTS & RCC_CTRLSTS_MSIRD) != RESET);
    if (!MSIStatus)
    {
        /* If MSI fails to start-up, the application will have wrong clock
         * configuration. User can add here some code to deal with this error */
        SystemCoreClock = MSI_VALUE_L6;
        return;
    }

#elif ((SYSCLK_SRC == SYSCLK_USE_HSI) || (SYSCLK_SRC == SYSCLK_USE_HSI_PLL))

    bool HSIStatus = 0;
    /* Enable HSI */
    RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CTRL & RCC_CTRL_HSIRDF;
        StartUpCounter++;
    } while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    HSIStatus = ((RCC->CTRL & RCC_CTRL_HSIRDF) != RESET);
    if (!HSIStatus)
    {
        /* If HSI fails to start-up, the application will have wrong clock
         * configuration. User can add here some code to deal with this error */
        SystemCoreClock = MSI_VALUE_L6;
        return;
    }

#elif ((SYSCLK_SRC == SYSCLK_USE_HSE) || (SYSCLK_SRC == SYSCLK_USE_HSE_PLL))

    bool HSEStatus = 0;
    /* Enable HSE */
    RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CTRL & RCC_CTRL_HSERDF;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    HSEStatus = ((RCC->CTRL & RCC_CTRL_HSERDF) != RESET);
    if (!HSEStatus)
    {
        /* If HSE fails to start-up, the application will have wrong clock
         * configuration. User can add here some code to deal with this error */
        SystemCoreClock = MSI_VALUE_L6;
        return;
    }
#endif

    ConfigMRVoltage1V();

    /* Flash wait state
        0: HCLK <= 32M
        1: HCLK <= 64M
     */
    FLASH->AC &= (uint32_t)((uint32_t)~FLASH_AC_LATENCY);
    FLASH->AC |= (uint32_t)((SYSCLK_FREQ - 1) / 32000000);

    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPRES_DIV1;

    /* PCLK2 max 32M */
    if (SYSCLK_FREQ > 54000000)
    {
        RCC->CFG |= (uint32_t)RCC_CFG_APB2PRES_DIV2;
    }
    else
    {
        RCC->CFG |= (uint32_t)RCC_CFG_APB2PRES_DIV1;
    }

    /* PCLK1 max 16M */
    if (SYSCLK_FREQ > 54000000)
    {
        RCC->CFG |= (uint32_t)RCC_CFG_APB1PRES_DIV4;
    }
    else if (SYSCLK_FREQ > 27000000)
    {
        RCC->CFG |= (uint32_t)RCC_CFG_APB1PRES_DIV2;
    }
    else
    {
        RCC->CFG |= (uint32_t)RCC_CFG_APB1PRES_DIV1;
    }

#if SYSCLK_SRC == SYSCLK_USE_MSI
    /* Select MSI as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t) ~(RCC_CFG_SCLKSW));
    RCC->CFG |= (uint32_t)RCC_CFG_SCLKSW_MSI;

    /* Wait till MSI is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SCLKSTS) != (uint32_t)0x00)
    {
    }
#elif SYSCLK_SRC == SYSCLK_USE_HSI
    /* Select HSI as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t) ~(RCC_CFG_SCLKSW));
    RCC->CFG |= (uint32_t)RCC_CFG_SCLKSW_HSI;

    /* Wait till HSI is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SCLKSTS) != (uint32_t)0x04)
    {
    }
#elif SYSCLK_SRC == SYSCLK_USE_HSE
    /* Select HSE as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t) ~(RCC_CFG_SCLKSW));
    RCC->CFG |= (uint32_t)RCC_CFG_SCLKSW_HSE;

    /* Wait till HSE is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SCLKSTS) != (uint32_t)0x08)
    {
    }
#elif SYSCLK_SRC == SYSCLK_USE_HSI_PLL || SYSCLK_SRC == SYSCLK_USE_HSE_PLL

    /* clear bits */
    RCC->CFG &= (uint32_t)((uint32_t) ~(RCC_CFG_PLLSRC | RCC_CFG_PLLHSEPRES | RCC_CFG_PLLMULFCT));
    RCC->PLLHSIPRE &= (uint32_t)((uint32_t) ~(RCC_PLLHSIPRE_PLLHSIPRE | RCC_PLLHSIPRE_PLLSRCDIV));

    /* set PLL source */
    rcc_cfg = RCC->CFG;
    rcc_cfg |= (SYSCLK_SRC == SYSCLK_USE_HSI_PLL ? RCC_CFG_PLLSRC_HSI : RCC_CFG_PLLSRC_HSE);
    /* PLL DIV */
    rcc_pllhsipre = RCC->PLLHSIPRE;

    #if SYSCLK_SRC == SYSCLK_USE_HSI_PLL
        rcc_pllhsipre |= (PLLSRC_DIV == 1 ? RCC_PLLHSIPRE_PLLHSIPRE_HSI : RCC_PLLHSIPRE_PLLHSIPRE_HSI_DIV2);
    #elif SYSCLK_SRC == SYSCLK_USE_HSE_PLL
        rcc_cfg |= (PLLSRC_DIV == 1 ? RCC_CFG_PLLHSEPRES_HSE : RCC_CFG_PLLHSEPRES_HSE_DIV2);
    #endif

    /* set PLL DIV */
    rcc_pllhsipre |= (PLL_DIV == PLL_DIV2_DISABLE ? RCC_PLLHSIPRE_PLLSRCDIV_DISABLE : RCC_PLLHSIPRE_PLLSRCDIV_ENABLE);

    /* set PLL multiply factor */
    #if PLL_MUL <= 16
        rcc_cfg |= (PLL_MUL - 2) << 18;
    #else
        rcc_cfg |= ((PLL_MUL - 17) << 18) | (1 << 27);
    #endif

    RCC->CFG       = rcc_cfg;
    RCC->PLLHSIPRE = rcc_pllhsipre;

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while ((RCC->CTRL & RCC_CTRL_PLLRDF) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t) ~(RCC_CFG_SCLKSW));
    RCC->CFG |= (uint32_t)RCC_CFG_SCLKSW_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SCLKSTS) != (uint32_t)0x0C)
    {
    }
#endif
}
