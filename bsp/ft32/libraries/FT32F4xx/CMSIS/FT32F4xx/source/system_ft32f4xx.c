/**
  ******************************************************************************
  * @file               system_ft32f4xx.h
  * @author             FMD AE
  * @brief              CMSIS FT32F4xx Device Peripheral Access Layer Header File.
  * @version            V1.0.0
  * @data                   2025-03-03
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup FT32f4xx_system
  * @{
  */

/** @addtogroup FT32f114xx_System_Private_Includes
  * @{
  */

#include "ft32f4xx.h"

/**
  * @}
  */

/** @addtogroup FT32f114xx_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup FT32F114xx_System_Private_Defines
  * @{
  */

// #define SYSCLK_FREQ_HSE     HSI_VALUE
// #define SYSCLK_FREQ_105MHz  105000000   /* Value of Internal clk in Hz */
// #define SYSCLK_FREQ_180MHz  180000000   /* Value of Internal clk in Hz */
#define SYSCLK_FREQ_210MHz    210000000   /* Value of Internal clk in Hz */
/**
  * @}
  */

/** @addtogroup FT32f114xx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup FT32f114xx_System_Private_Variables
  * @{
  */
/*******************************************************************************
*  Clock Definitions
*******************************************************************************/
#ifdef SYSCLK_FREQ_HSE
    uint32_t SystemCoreClock         = SYSCLK_FREQ_HSE;           /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_105MHz
    uint32_t SystemCoreClock         = SYSCLK_FREQ_105MHz;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_180MHz
    uint32_t SystemCoreClock         = SYSCLK_FREQ_180MHz;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_210MHz
    uint32_t SystemCoreClock         = SYSCLK_FREQ_210MHz;        /*!< System Clock Frequency (Core Clock) */
#else /*!< HSI Selected as System Clock source */
    uint32_t SystemCoreClock         = HSI_VALUE;        /*!< System Clock Frequency (Core Clock) */
#endif
__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

/**
  * @}
  */

/** @addtogroup FT32f114xx_System_Private_FunctionPrototypes
  * @{
  */

static void SetSysClock(void);

#ifdef SYSCLK_FREQ_HSE
    static void SetSysClockToHSE(void);
#elif defined SYSCLK_FREQ_105MHz
    static void SetSysClockTo105(void);
#elif defined SYSCLK_FREQ_180MHz
    static void SetSysClockTo180(void);
#elif defined SYSCLK_FREQ_210MHz
    static void SetSysClockTo210(void);
#endif
/**
  * @}
  */

/** @addtogroup FT32f114xx_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system.
  *         Initialize the Embedded Flash Interface, the PLL and update the
  *         SystemCoreClock variable.
  * @param  None
  * @retval None
  */
void SystemInit(void)
{
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10 and CP11 Full Access */
#endif
    /* Set HSION bit */
    RCC->CR |= (uint32_t)0x00000001;

    /* Reset SW[1:0], HPRE[3:0], PPRE1[2:0], PREE2[2:0] and MCOSEL[2:0] bits */
    RCC->CFGR &= (uint32_t)0x80FFC00C;

    /* Reset HSEON, CSSON , PLLON and PLL2ON bits */
    RCC->CR &= (uint32_t)0xFAF6FFFF;

    /* Reset HSEBYP bit */
    RCC->CR &= (uint32_t)0xFFFBFFFF;

    /* Reset PLLR[2:0], PLLREN, PLLQ[3:0], PLLQEN, PLLP[2:0],
     * PLLPEN, PLLSRC, PLLN[7:0], PLLM[4:0] bits */
    RCC->PLLCFGR &= (uint32_t)0xE0008020;

    /* Reset PLL2R[2:0], PLL2REN, PLL2Q[3:0], PLL2QEN, PLL2SRC, PLL2N[7:0] and PLL2M[4:0] bits */
    RCC->PLL2CFGR &= (uint32_t)0xE00F8020;

    /* Reset HSI48ON bit */
    RCC->CR2 &= (uint32_t)0xFFFEFFFF;

    /* Disable all interrupts */
    RCC->CIR = 0x00000000;

    /* Configure the System clock frequency, AHB/APBx prescalers and Flash settings */
    SetSysClock();

    RCC->APB1ENR |= RCC_APB1ENR_CRSEN;
    CRS->CR &= ~(0x3F << 8);
    CRS->CR |= (((*(uint32_t*)0x1FFF0A28) & 0x3F) << 8);
    RCC->APB1ENR &= ~RCC_APB1ENR_CRSEN;

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN | RCC_APB2ENR_ADCEN;
    if ((VREFBUF->VREFBUF_CSR & 0x4) == 0x4) //2.5V
    {
        VREFBUF->VREFBUF_CCR = 0;
        VREFBUF->VREFBUF_CCR = ((*(uint32_t*)0x1FFF0A20) & 0x3F00) >> 16;
        ADC1->CALFACT = (*(uint32_t*)0x1FFF0A3C);
        ADC2->CALFACT = (*(uint32_t*)0x1FFF0A40);
        ADC3->CALFACT = (*(uint32_t*)0x1FFF0A44);
    }
    else // 2.048V
    {
        VREFBUF->VREFBUF_CCR = 0;
        VREFBUF->VREFBUF_CCR = ((*(uint32_t*)0x1FFF0A20) & 0x3F);
        ADC1->CALFACT = (*(uint32_t*)0x1FFF0A30);
        ADC2->CALFACT = (*(uint32_t*)0x1FFF0A34);
        ADC3->CALFACT = (*(uint32_t*)0x1FFF0A38);
    }
    RCC->APB2ENR &= ~(RCC_APB2ENR_SYSCFGEN | RCC_APB2ENR_ADCEN);
}

/**
  * @brief  Update SystemCoreClock according to Clock Register Values
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  *
  * @note   Each time the core clock (HCLK) changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.
  *
  * @note   - The system frequency computed by this function is not the real
  *           frequency in the chip. It is calculated based on the predefined
  *           constant and the selected clock source:
  *
  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(*)
  *
  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(**)
  *
  *           - If SYSCLK source is PLL, SystemCoreClock will contain the HSE_VALUE(**)
  *             or HSI_VALUE(*) multiplied/divided by the PLL factors.
  *
  *         (*) HSI_VALUE is a constant defined in FT32f4xx.h file (default value
  *             8 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature.
  *
  *         (**) HSE_VALUE is a constant defined in FT32f4xx.h file (default value
  *              8 MHz), user has to ensure that HSE_VALUE is same as the real
  *              frequency of the crystal used. Otherwise, this function may
  *              have wrong result.
  *
  *         - The result of this function could be not correct when using fractional
  *           value for HSE crystal.
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate(void)
{
    uint32_t tmp = 0, pllm = 0, plln = 0, pllp = 0, pllvco = 0, pllsource = 0;

    /* Get SYSCLK source -------------------------------------------------------*/
    tmp = RCC->CFGR & RCC_CFGR_SWS;

    switch (tmp)
    {
    case 0x00:  /* HSI used as system clock */
        SystemCoreClock = HSI_VALUE;
        break;
    case 0x01:  /* HSE used as system clock */
        SystemCoreClock = HSE_VALUE;
        break;
    case 0x02:  /* PLL used as system clock */
        /* PLL_VCO = (HSI_VALUE  / PLLM ) * PLLN ----------------------
         * SYSCLK  = PLL_VCO / PLLP
         * */
        pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
        plln = (RCC->PLLCFGR & RCC_PLLCFGR_PLLN >> 6);
        pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC >> 14);

        if (pllsource == 0)   /* HSI uses as PLL clock source */
        {

            pllvco = (HSI_VALUE / pllm);
        }
        else                  /* HSE uses as PLL clock source */
        {
            pllvco = (HSE_VALUE / pllm);
        }

        if (RCC->PLLCFGR & RCC_PLLCFGR_PLLP >> 17)  /* PLLP != 0 */
        {
            pllp = (RCC->PLLCFGR & RCC_PLLCFGR_PLLP >> 17) + 1U;
        }
        else                                        /* PLLP == 0 , prescaler is 2 */
        {
            pllp = (RCC->PLLCFGR & RCC_PLLCFGR_PLLP >> 17) + 2U;
        }

        pllvco = pllvco * plln ;
        SystemCoreClock = pllvco / pllp;
        break;
    default: /* HSI used as system clock */
        SystemCoreClock = HSI_VALUE;
        break;
    }
    /* Compute HCLK clock frequency ----------------*/
    /* Get HCLK prescaler */
    tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
    /* HCLK clock frequency */
    SystemCoreClock >>= tmp;
}



/**
  * @brief  Configures the System clock frequency, HCLK, PCLK prescalers.
  * @param  None
  * @retval None
  */
static void SetSysClock(void)
{
#ifdef SYSCLK_FREQ_HSE
    SetSysClockToHSE();
#elif defined SYSCLK_FREQ_105MHz
    SetSysClockTo105();
#elif defined SYSCLK_FREQ_180MHz
    SetSysClockTo180();
#elif defined SYSCLK_FREQ_210MHz
    SetSysClockTo210();
#endif

    /* If none of the define above is enabled, the HSI is used as System clock
       source (default after reset) */
}

#ifdef SYSCLK_FREQ_HSE
/**
  * @brief  Selects HSE as System clock source and configure HCLK, PCLK
  *         prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockToHSE(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK configuration ----------------------------------------*/
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    }
    while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer and set Flash Latency */
        if (HSE_VALUE <= 30000000) /* clk <= 30MHz ,latancy=0 */
        {
            FLASH->RDC = FLASH_ACR_PRFTBE | ((uint32_t)0x00000000);
        }
        else                       /* clk > 30MHz ,latancy=1 */
        {
            FLASH->RDC = FLASH_ACR_PRFTBE | ((uint32_t)0x00000001);
        }

        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;

        /* PCLK1 = HCLK/2, PCLK2 = HCLK/2 */
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV2);

        /* Select HSE as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSE;

        /* Wait till HSE is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_HSE)
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this error */
    }
}

#elif defined SYSCLK_FREQ_105MHz
/**
  * @brief  Sets System clock frequency to 105MHz and configure HCLK, PCLK
  *         prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo105(void)
{
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    /* SYSCLK, HCLK, PCLK configuration ----------------------------------------*/
    /* Enable HSI */
    RCC->CR |= ((uint32_t)RCC_CR_HSION);

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CR & RCC_CR_HSIRDY;
        StartUpCounter++;
    }
    while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSIRDY) != RESET)
    {
        HSIStatus = (uint32_t)0x01;
    }
    else
    {
        HSIStatus = (uint32_t)0x00;
    }

    if (HSIStatus == (uint32_t)0x01)
    {

        RCC->PLLCFGR |= (uint32_t)((105 << 6)               | // PLLN=105
                                   RCC_PLLCFGR_PLLSRC_HSI |   // Source : HSI
                                   RCC_PLLCFGR_PLLPEN     |   // Enable PLLP
                                   (8 << 0)) ;                // PLLM=8, PLLPCLK=VCO/8
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while (((RCC->CR) & (uint32_t)RCC_CR_PLLRDY) != (uint32_t)RCC_CR_PLLRDY) //wait PLLRDY
        {
        }

        /* Enable Prefetch Buffer(default is enable) and set Flash Latency */
        FLASH->RDC |= (uint32_t)(0x3 << 0);

        /* Select PLL as system clock source */
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while (((RCC->CFGR) & (uint32_t)RCC_CFGR_SWS_PLL) != (uint32_t)RCC_CFGR_SWS_PLL)
        {
        }
    }

}
else
{
    /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
}
}
#elif defined SYSCLK_FREQ_180MHz
/**
  * @brief  Sets System clock frequency to 180MHz and configure HCLK, PCLK
  *         prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo180(void)
{
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    /* SYSCLK, HCLK, PCLK configuration ----------------------------------------*/
    /* Enable HSI */
    RCC->CR |= ((uint32_t)RCC_CR_HSION);

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CR & RCC_CR_HSIRDY;
        StartUpCounter++;
    }
    while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSIRDY) != RESET)
    {
        HSIStatus = (uint32_t)0x01;
    }
    else
    {
        HSIStatus = (uint32_t)0x00;
    }

    if (HSIStatus == (uint32_t)0x01)
    {

        RCC->PLLCFGR |= (uint32_t)((45 << 6)                | // PLLN=45
                                   RCC_PLLCFGR_PLLSRC_HSI |   // Source : HSI
                                   RCC_PLLCFGR_PLLPEN     |   // Enable PLLP
                                   (2 << 0)) ;                // PLLM=2, PLLPCLK=VCO/2
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while (((RCC->CR) & (uint32_t)RCC_CR_PLLRDY) != (uint32_t)RCC_CR_PLLRDY) //wait PLLRDY
        {
        }

        /* Enable Prefetch Buffer(default is enable) and set Flash Latency */
        FLASH->RDC |= (uint32_t)(0x5 << 0);

        /* Select PLL as system clock source */
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while (((RCC->CFGR) & (uint32_t)RCC_CFGR_SWS_PLL) != (uint32_t)RCC_CFGR_SWS_PLL)
        {
        }
    }

    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this error */
    }
}
#elif defined SYSCLK_FREQ_210MHz
/**
  * @brief  Sets System clock frequency to 210MHz and configure HCLK, PCLK
  *         prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo210(void)
{
    __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    /* SYSCLK, HCLK, PCLK configuration ----------------------------------------*/
    /* Enable HSI */
    RCC->CR |= ((uint32_t)RCC_CR_HSION);

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CR & RCC_CR_HSIRDY;
        StartUpCounter++;
    }
    while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSIRDY) != RESET)
    {
        HSIStatus = (uint32_t)0x01;
    }
    else
    {
        HSIStatus = (uint32_t)0x00;
    }

    if (HSIStatus == (uint32_t)0x01)
    {

        RCC->PLLCFGR |= (uint32_t)((105 << 6)               | // PLLN=105
                                   RCC_PLLCFGR_PLLSRC_HSI |   // Source : HSI
                                   RCC_PLLCFGR_PLLPEN     |   // Enable PLLP
                                   (4 << 0)) ;                // PLLM=4, PLLPCLK=VCO/2
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while (((RCC->CR) & (uint32_t)RCC_CR_PLLRDY) != (uint32_t)RCC_CR_PLLRDY) //wait PLLRDY
        {
        }

        /* Enable Prefetch Buffer(default is enable) and set Flash Latency */
        FLASH->RDC |= (uint32_t)(0x6 << 0);

        /* Select PLL as system clock source */
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while (((RCC->CFGR) & (uint32_t)RCC_CFGR_SWS_PLL) != (uint32_t)RCC_CFGR_SWS_PLL)
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
             configuration. User can add here some code to deal with this error */
    }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
