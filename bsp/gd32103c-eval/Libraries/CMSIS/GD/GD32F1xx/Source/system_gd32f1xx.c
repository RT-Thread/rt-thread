/**
  ******************************************************************************
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer System Source File.
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup GD32f10x_system
  * @{
  */

/** @addtogroup GD32f10x_System_Private_Includes
  * @{
  */

#include "gd32f10x.h"

/**
  * @}
  */

/** @addtogroup GD32f10x_System_Private_Variables
  * @{
  */

/* Uncomment the corresponding line to configure system clock that you need  */
/* The clock is from HSE oscillator clock  */
//#define SYSCLK_FREQ_HSE    HSE_VALUE
//#define SYSCLK_FREQ_24MHz  24000000
//#define SYSCLK_FREQ_36MHz  36000000
//#define SYSCLK_FREQ_48MHz  48000000
//#define SYSCLK_FREQ_56MHz  56000000
//#define SYSCLK_FREQ_72MHz  72000000
//#define SYSCLK_FREQ_96MHz  96000000
#define SYSCLK_FREQ_108MHz  108000000

/* Uncomment the corresponding line to configure system clock that you need  */
/* The clock is from HSI oscillator clock  */
//#define SYSCLK_FREQ_48MHz_HSI  48000000
//#define SYSCLK_FREQ_72MHz_HSI  72000000
//#define SYSCLK_FREQ_108MHz_HSI  108000000

/* ---------------------- RCC registers mask -------------------------------- */

/* RCC GCCR_HSIEN mask */
#define  SYS_GCCR_HSIEN_SET                                 ((uint32_t)0x00000001)

/* RCC GCFGR_Reset mask */
#define  SYS_GCFGR_RESET_CL                                 ((uint32_t)0xE0FF0000)
#define  SYS_GCFGR_RESET                                    ((uint32_t)0xE8FF0000)

/* RCC GCCR_HSEEN_CKMEN_PLLEN masks */
#define  SYS_GCCR_HSEEN_CKMEN_PLLEN_RESET                   ((uint32_t)0xFEF6FFFF)

/* RCC GCCR_HSEBPS mask */
#define  SYS_GCCR_HSEBPS_RESET                              ((uint32_t)0xFFFBFFFF)

/* RCC GCFGR_PLLSEL_PLLPREDV_PLLMF masks */
#define  SYS_GCFGR_PLLSEL_PLLPREDV_PLLMF_USBPS_RESET        ((uint32_t)0xF700FFFF)
#define  SYS_GCFGR_PLLSEL_PLLPREDV_PLLMF_USBPS_RESET_CL     ((uint32_t)0xDF00FFFF)

/* RCC GCCR_PLL2EN_PLL3EN masks */
#define  SYS_GCCR_PLL2EN_PLL3EN_RESET                       ((uint32_t)0xEBFFFFFF)

/* RCC GCFGR2 reset */
#define  SYS_GCFGR2_RESET                                   ((uint32_t)0x00000000)

/* RCC GCIR_INT ans FLAG masks */
#define  SYS_GCIR_INT_FLAG_RESET                            ((uint32_t)0x009F0000)
#define  SYS_GCIR_INT_FLAG_RESET_CL                         ((uint32_t)0x00FF0000)

#define  SYS_GCCR_HSEEN_HSEBPS_RESET                        ((uint32_t)0xFFF8FFFF)

/* RCC GCCR_HSIADJ masks */
#define  SYS_GCCR_HSIADJ_OFFSET                             ((uint32_t)0x00000003)


#define  SYS_RCC_GCFGR_PLLMF_3_0                            ((uint32_t)0x003C0000) /*!< PLLMF[3:0] Bits */

/* RCC HSI clock divided by 2 masks */
#define  SYS_HSI_CLOCK_DIVIDED_2                            ((uint32_t)0x00000001)



/**
  * @}
  */


/** @addtogroup GD32F10x_System_Private_Variables
  * @{
  */

/*******************************************************************************
*  System Clock Select
*******************************************************************************/
#ifdef SYSCLK_FREQ_HSE
    uint32_t SystemCoreClock         = SYSCLK_FREQ_HSE;
#elif defined SYSCLK_FREQ_24MHz
    uint32_t SystemCoreClock         = SYSCLK_FREQ_24MHz;
#elif defined SYSCLK_FREQ_36MHz
    uint32_t SystemCoreClock         = SYSCLK_FREQ_36MHz;
#elif defined SYSCLK_FREQ_48MHz
    uint32_t SystemCoreClock         = SYSCLK_FREQ_48MHz;
#elif defined SYSCLK_FREQ_56MHz
    uint32_t SystemCoreClock         = SYSCLK_FREQ_56MHz;
#elif defined SYSCLK_FREQ_72MHz
    uint32_t SystemCoreClock         = SYSCLK_FREQ_72MHz;
#elif defined SYSCLK_FREQ_96MHz
    uint32_t SystemCoreClock         = SYSCLK_FREQ_96MHz;
#elif defined SYSCLK_FREQ_108MHz
    uint32_t SystemCoreClock         = SYSCLK_FREQ_108MHz;
#elif defined SYSCLK_FREQ_48MHz_HSI
    uint32_t SystemCoreClock         = SYSCLK_FREQ_48MHz_HSI;
#elif defined SYSCLK_FREQ_72MHz_HSI
    uint32_t SystemCoreClock         = SYSCLK_FREQ_72MHz_HSI;
#elif defined SYSCLK_FREQ_108MHz_HSI
    uint32_t SystemCoreClock         = SYSCLK_FREQ_108MHz_HSI;
#else /*!< HSI Selected as System Clock source */
    uint32_t SystemCoreClock         = HSI_VALUE;        /*!< System Clock Frequency (Core Clock) */
#endif

__I uint8_t AHBPrescTableList[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

/**
  * @}
  */

/** @addtogroup GD32f10x_System_Private_FunctionPrototypes
  * @{
  */

static void SetSysClock(void);

#ifdef SYSCLK_FREQ_HSE
    static void SetSysClockToHSE(void);
#elif defined SYSCLK_FREQ_24MHz
    static void SetSysClockTo24(void);
#elif defined SYSCLK_FREQ_36MHz
    static void SetSysClockTo36(void);
#elif defined SYSCLK_FREQ_48MHz
    static void SetSysClockTo48(void);
#elif defined SYSCLK_FREQ_56MHz
    static void SetSysClockTo56(void);
#elif defined SYSCLK_FREQ_72MHz
    static void SetSysClockTo72(void);
#elif defined SYSCLK_FREQ_96MHz
    static void SetSysClockTo96(void);
#elif defined SYSCLK_FREQ_108MHz
    static void SetSysClockTo108(void);
#elif defined SYSCLK_FREQ_48MHz_HSI
    static void SetSysClockTo48HSI(void);
#elif defined SYSCLK_FREQ_72MHz_HSI
    static void SetSysClockTo72HSI(void);
#elif defined SYSCLK_FREQ_108MHz_HSI
    static void SetSysClockTo108HSI(void);
#endif


/**
  * @}
  */

/** @addtogroup GD32f10x_System_Private_Functions
  * @{
  */

/**
  * @brief  Initialize the Embedded Flash Interface, the PLL and set the
  *         SystemCoreClock variable.
  * @param  None
  * @retval None
  */

void SystemInit(void)
{
    /* Set RCC GCCR_HSIEN mask */
    RCC->GCCR |= SYS_GCCR_HSIEN_SET;

    /* Reset SCS[1:0], AHBPS[3:0], APB1PS[2:0],APB2PS[2:0], ADCPS[2:0],CKOTUSEL[2:0] bits */
#ifdef GD32F10X_CL
    RCC->GCFGR &= SYS_GCFGR_RESET_CL;
#else
    RCC->GCFGR &= SYS_GCFGR_RESET;
#endif /* GD32F10X_CL */

    /* Reset HSEEN, CKMEN and PLLEN bits */
    RCC->GCCR &= SYS_GCCR_HSEEN_CKMEN_PLLEN_RESET;

    /* Reset HSEBPS bit */
    RCC->GCCR &= SYS_GCCR_HSEBPS_RESET;

    /* Reset PLLSEL, PLLPREDV and PLLMF[4:0] USBPS/OTGPS bits */
#ifdef GD32F10X_CL
    RCC->GCFGR &= SYS_GCFGR_PLLSEL_PLLPREDV_PLLMF_USBPS_RESET_CL;
#else
    RCC->GCFGR &= SYS_GCFGR_PLLSEL_PLLPREDV_PLLMF_USBPS_RESET;
#endif /* GD32F10X_CL */

#ifdef GD32F10X_CL
    /* Reset PLL2EN and PLL3EN bits */
    RCC->GCCR &= SYS_GCCR_PLL2EN_PLL3EN_RESET;

    /* Reset GCFGR2 register */
    RCC->GCFGR2 = SYS_GCFGR2_RESET ;

    /* Disable all interrupts and clear flag bits */
    RCC->GCIR = SYS_GCIR_INT_FLAG_RESET_CL;
#else
    /* Disable all interrupts and clear flag bits */
    RCC->GCIR = SYS_GCIR_INT_FLAG_RESET;
#endif /* GD32F10X_CL */

    /* Configure the System clock frequency, AHB, APB2 and APB1 prescalers */
    /* Configure the Flash Latency cycles and enable prefetch buffer */
    SetSysClock();
}

/**
  * @brief  Update SystemCoreClock according to RCC Register Values
  * @note   Update the SystemCoreClock variable values, when the core clock (HCLK) changes.
  *         Otherwise, any configuration based on this variable will be wrong.
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate(void)
{
    uint32_t temp = 0, pllmf = 0, pllmf4 = 0, pllselect = 0, presc = 0;

#ifdef  GD32F10X_CL
    uint32_t prediv1select = 0, prediv1factor = 0, prediv2factor = 0, pll2mf = 0;
#endif /* GD32F10X_CL */

    /* Get CK_SYS source -------------------------------------------------------*/
    temp = RCC->GCFGR & RCC_GCFGR_SCSS;

    switch (temp) {
    case 0x00:  /* HSI used as CK_SYS */
        SystemCoreClock = HSI_VALUE;
        break;
    case 0x04:  /* HSE used as CK_SYS */
        SystemCoreClock = HSE_VALUE;
        break;
    case 0x08:  /* PLL used as CK_SYS */
#ifdef  GD32F10X_CL
        /* Get PLL clock source and multiplication factor ----------------------*/
        /* Get PLLMF[3:0] */
        pllmf = RCC->GCFGR & SYS_RCC_GCFGR_PLLMF_3_0;
        /* Get PLLMF[4] */
        pllmf4 = RCC->GCFGR & RCC_GCFGR_PLLMF_4;

        pllmf4 = ((pllmf4 >> 29) * 15);

        pllmf = (pllmf >> 18) + pllmf4;
        if (pllmf != 0x0D) {
            pllmf += 2;
        } else {
            /* PLL multiplication factor = PLL input clock * 6.5 */
            pllmf = 13 / 2;
        }

        pllselect = RCC->GCFGR & RCC_GCFGR_PLLSEL;
        if (pllselect == 0x00) {
            /* HSI clock divided by 2 selected as PLL clock source */
            SystemCoreClock = (HSI_VALUE >> SYS_HSI_CLOCK_DIVIDED_2) * pllmf;
        } else {
            /* PREDIV1 selected as PLL clock entry */

            /* Get PREDIV1 clock source and division factor */
            prediv1select = RCC->GCFGR2 & RCC_GCFGR2_PREDV1SEL;
            prediv1factor = (RCC->GCFGR2 & RCC_GCFGR2_PREDV1) + 1;

            if (prediv1select == 0) {
                /* HSE clock selected as PREDIV1 clock entry */
                SystemCoreClock = (HSE_VALUE / prediv1factor) * pllmf;
            } else {
                /* PLL2 clock selected as PREDIV1 clock entry */
                /* Get PREDIV2 division factor and PLL2 multiplication factor */
                prediv2factor = ((RCC->GCFGR2 & RCC_GCFGR2_PREDV2) >> 4) + 1;
                pll2mf = ((RCC->GCFGR2 & RCC_GCFGR2_PLL2MF) >> 8);
                if (pll2mf != 15) {
                    pll2mf += 2;
                } else {
                    pll2mf += 5;
                }
                SystemCoreClock = (((HSE_VALUE / prediv2factor) * pll2mf) / prediv1factor) * pllmf;
            }
        }
#else
        /* Get PLL clock source and multiplication factor ----------------------*/
        /* Get PLLMF[3:0] */
        pllmf = RCC->GCFGR & SYS_RCC_GCFGR_PLLMF_3_0;
        /* Get PLLMF[4] */
        pllmf4 = RCC->GCFGR & RCC_GCFGR_PLLMF_4;

        pllmf4 = ((pllmf4 >> 27) * 15);
        pllmf = (pllmf >> 18) + pllmf4 + 2;


        pllselect = RCC->GCFGR & RCC_GCFGR_PLLSEL;
        if (pllselect == 0x00) {
            /* HSI clock divided by 2 selected as PLL clock source */
            SystemCoreClock = (HSI_VALUE >> SYS_HSI_CLOCK_DIVIDED_2) * pllmf;
        } else {
            if ((RCC->GCFGR & RCC_GCFGR_PLLPREDV) != (uint32_t)RESET) {
                /* HSE clock divided by 2 */
                SystemCoreClock = (HSE_VALUE >> 1) * pllmf;
            } else {
                SystemCoreClock = HSE_VALUE * pllmf;
            }
        }
#endif
        break;
    default: /* HSI used as system clock */
        SystemCoreClock = HSI_VALUE;
        break;
    }

    /* Get AHB prescaler */
    temp = RCC->GCFGR & RCC_GCFGR_AHBPS;
    temp = temp >> 4;
    presc = AHBPrescTableList[temp];
    /* Get AHB clock frequency */
    SystemCoreClock = SystemCoreClock >> presc;
}

/**
  * @brief  Configure the System clock frequency, AHB, APB2 and APB1 prescalers.
  * @param  None
  * @retval None
  */


static void SetSysClock(void)
{
#ifdef SYSCLK_FREQ_HSE
    SetSysClockToHSE();
#elif defined SYSCLK_FREQ_24MHz
    SetSysClockTo24();
#elif defined SYSCLK_FREQ_36MHz
    SetSysClockTo36();
#elif defined SYSCLK_FREQ_48MHz
    SetSysClockTo48();
#elif defined SYSCLK_FREQ_56MHz
    SetSysClockTo56();
#elif defined SYSCLK_FREQ_72MHz
    SetSysClockTo72();
#elif defined SYSCLK_FREQ_96MHz
    SetSysClockTo96();
#elif defined SYSCLK_FREQ_108MHz
    SetSysClockTo108();
#elif defined SYSCLK_FREQ_48MHz_HSI
    SetSysClockTo48HSI();
#elif defined SYSCLK_FREQ_72MHz_HSI
    SetSysClockTo72HSI();
#elif defined SYSCLK_FREQ_108MHz_HSI
    SetSysClockTo108HSI();
#endif

}

#ifdef SYSCLK_FREQ_HSE
/**
  * @brief  Select HSE as System clock source and configure AHB, APB2
  *         and APB1 prescalers.
  * @param  None
  * @retval None
  */
static void SetSysClockToHSE(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* CK_SYS, AHB, APB2 and APB1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->GCCR |= ((uint32_t)RCC_GCCR_HSEEN);

    /* Wait till HSE is ready and if Time out is reached exit */
    do {
        HSEStatus = RCC->GCCR & RCC_GCCR_HSESTB;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->GCCR & RCC_GCCR_HSESTB) != RESET) {
        HSEStatus = (uint32_t)0x01;
    } else {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01) {
        /* AHB = CK_SYS not divided */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_AHBPS_DIV1;

        /* APB2 = AHB not divided */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB2PS_DIV1;

        /* APB1 = AHB is divided 2 */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB1PS_DIV2;

        /* Select HSE as system clock source */
        RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_SCS));
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_SCS_HSE;

        /* Wait till HSE is used as system clock source */
        while ((RCC->GCFGR & (uint32_t)RCC_GCFGR_SCSS) != (uint32_t)0x04) {
        }
    } else {
    }
}
#elif defined SYSCLK_FREQ_24MHz
/**
  * @brief  Set System clock frequency to 24MHz and configure AHB, APB1, and APB2 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo24(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* CK_SYS, AHB, APB2 and APB1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->GCCR |= ((uint32_t)RCC_GCCR_HSEEN);

    /* Wait till HSE is ready and if Time out is reached exit */
    do {
        HSEStatus = RCC->GCCR & RCC_GCCR_HSESTB;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->GCCR & RCC_GCCR_HSESTB) != RESET) {
        HSEStatus = (uint32_t)0x01;
    } else {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01) {
        /* AHB = CK_SYS not divided */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_AHBPS_DIV1;

        /* APB2 = AHB not divided */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB2PS_DIV1;

        /* APB1 = AHB is divided 2 */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB1PS_DIV2;

#ifdef GD32F10X_CL
        /* Configure PLLs ------------------------------------------------------*/

        /* PLL configuration: PLLCLK = PREDIV1 * 6 = 24 MHz */

        RCC->GCFGR &= (uint32_t)~(RCC_GCFGR_PLLPREDV | RCC_GCFGR_PLLSEL | RCC_GCFGR_PLLMF);
        RCC->GCFGR |= (uint32_t)(RCC_GCFGR_PLLPREDV_PREDIV1 | RCC_GCFGR_PLLSEL_PREDIV1 | RCC_GCFGR_PLLMF6);

        /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
        /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 10 = 4 MHz */

        RCC->GCFGR2 &= (uint32_t)~(RCC_GCFGR2_PREDV2 | RCC_GCFGR2_PLL2MF |
                                   RCC_GCFGR2_PREDV1 | RCC_GCFGR2_PREDV1SEL);
        RCC->GCFGR2 |= (uint32_t)(RCC_GCFGR2_PREDV2_DIV5 | RCC_GCFGR2_PLL2MF8 |
                                  RCC_GCFGR2_PREDV1SEL_PLL2 | RCC_GCFGR2_PREDV1_DIV10);

        /* Enable PLL2 */
        RCC->GCCR |= RCC_GCCR_PLL2EN;
        /* Wait till PLL2 is ready */
        while ((RCC->GCCR & RCC_GCCR_PLL2STB) == 0) {
        }
#else
        /* PLL configuration: PLLCLK = (HSE /2)* 6 = 24 MHz */
        RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_PLLSEL | RCC_GCFGR_PLLPREDV | RCC_GCFGR_PLLMF));
        RCC->GCFGR |= (uint32_t)(RCC_GCFGR_PLLPREDV_HSE_DIV2 | RCC_GCFGR_PLLSEL_HSE | RCC_GCFGR_PLLMF6);

#endif /* GD32F10X_CL */

        /* Enable PLL */
        RCC->GCCR |= RCC_GCCR_PLLEN;

        /* Wait till PLL is ready */
        while ((RCC->GCCR & RCC_GCCR_PLLSTB) == 0) {
        }

        /* Select PLL as system clock source */
        RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_SCS));
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_SCS_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->GCFGR & (uint32_t)RCC_GCFGR_SCSS) != (uint32_t)0x08) {
        }
    } else {
    }
}

#elif defined SYSCLK_FREQ_36MHz
/**
  * @brief  Set System clock frequency to 36MHz and configure AHB, APB1, and APB2 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo36(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* CK_SYS, AHB, APB2 and APB1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->GCCR |= ((uint32_t)RCC_GCCR_HSEEN);

    /* Wait till HSE is ready and if Time out is reached exit */
    do {
        HSEStatus = RCC->GCCR & RCC_GCCR_HSESTB;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->GCCR & RCC_GCCR_HSESTB) != RESET) {
        HSEStatus = (uint32_t)0x01;
    } else {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01) {
        /* AHB = CK_SYS not divided */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_AHBPS_DIV1;

        /* APB2 = AHB not divided */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB2PS_DIV1;

        /* APB1 = AHB is divided 2 */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB1PS_DIV2;

#ifdef GD32F10X_CL
        /* Configure PLLs ------------------------------------------------------*/
        /* PLL configuration: PLLCLK = PREDIV1 * 9 = 36 MHz */
        RCC->GCFGR &= (uint32_t)~(RCC_GCFGR_PLLPREDV | RCC_GCFGR_PLLSEL | RCC_GCFGR_PLLMF);
        RCC->GCFGR |= (uint32_t)(RCC_GCFGR_PLLSEL_PREDIV1 | RCC_GCFGR_PLLMF9);

        /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
        /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 10 = 4 MHz */

        RCC->GCFGR2 &= (uint32_t)~(RCC_GCFGR2_PREDV2 | RCC_GCFGR2_PLL2MF |
                                   RCC_GCFGR2_PREDV1 | RCC_GCFGR2_PREDV1SEL);
        RCC->GCFGR2 |= (uint32_t)(RCC_GCFGR2_PREDV2_DIV5 | RCC_GCFGR2_PLL2MF8 |
                                  RCC_GCFGR2_PREDV1SEL_PLL2 | RCC_GCFGR2_PREDV1_DIV10);

        /* Enable PLL2 */
        RCC->GCCR |= RCC_GCCR_PLL2EN;
        /* Wait till PLL2 is ready */
        while ((RCC->GCCR & RCC_GCCR_PLL2STB) == 0) {
        }

#else
        /* PLL configuration: PLLCLK = (HSE /2)* 9 = 36 MHz */
        RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_PLLSEL | RCC_GCFGR_PLLPREDV | RCC_GCFGR_PLLMF));
        RCC->GCFGR |= (uint32_t)(RCC_GCFGR_PLLPREDV_HSE_DIV2 | RCC_GCFGR_PLLSEL_HSE | RCC_GCFGR_PLLMF9);

#endif /* GD32F10X_CL */

        /* Enable PLL */
        RCC->GCCR |= RCC_GCCR_PLLEN;

        /* Wait till PLL is ready */
        while ((RCC->GCCR & RCC_GCCR_PLLSTB) == 0) {
        }

        /* Select PLL as system clock source */
        RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_SCS));
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_SCS_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->GCFGR & (uint32_t)RCC_GCFGR_SCSS) != (uint32_t)0x08) {
        }
    } else {
    }
}
#elif defined SYSCLK_FREQ_48MHz
/**
  * @brief  Set System clock frequency to 48MHz and configure AHB, APB1, and APB2 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo48(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* CK_SYS, AHB, APB2 and APB1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->GCCR |= ((uint32_t)RCC_GCCR_HSEEN);

    /* Wait till HSE is ready and if Time out is reached exit */
    do {
        HSEStatus = RCC->GCCR & RCC_GCCR_HSESTB;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->GCCR & RCC_GCCR_HSESTB) != RESET) {
        HSEStatus = (uint32_t)0x01;
    } else {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01) {
        /* AHB = CK_SYS not divided */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_AHBPS_DIV1;

        /* APB2 = AHB not divided */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB2PS_DIV1;

        /* APB1 = AHB is divided 2 */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB1PS_DIV2;

#ifdef GD32F10X_CL
        /* Configure PLLs ------------------------------------------------------*/

        /* PLL configuration: PLLCLK = PREDIV1 * 6 = 48 MHz */
        RCC->GCFGR &= (uint32_t)~(RCC_GCFGR_PLLPREDV | RCC_GCFGR_PLLSEL | RCC_GCFGR_PLLMF);
        RCC->GCFGR |= (uint32_t)(RCC_GCFGR_PLLSEL_PREDIV1 | RCC_GCFGR_PLLMF6);
        /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
        /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 5 = 8 MHz */

        RCC->GCFGR2 &= (uint32_t)~(RCC_GCFGR2_PREDV2 | RCC_GCFGR2_PLL2MF |
                                   RCC_GCFGR2_PREDV1 | RCC_GCFGR2_PREDV1SEL);
        RCC->GCFGR2 |= (uint32_t)(RCC_GCFGR2_PREDV2_DIV5 | RCC_GCFGR2_PLL2MF8 |
                                  RCC_GCFGR2_PREDV1SEL_PLL2 | RCC_GCFGR2_PREDV1_DIV5);



        /* Enable PLL2 */
        RCC->GCCR |= RCC_GCCR_PLL2EN;
        /* Wait till PLL2 is ready */
        while ((RCC->GCCR & RCC_GCCR_PLL2STB) == 0) {
        }

#else
        /* PLL configuration: PLLCLK = HSE * 6 = 48 MHz */
        RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_PLLSEL | RCC_GCFGR_PLLPREDV | RCC_GCFGR_PLLMF));
        RCC->GCFGR |= (uint32_t)(RCC_GCFGR_PLLPREDV_HSE | RCC_GCFGR_PLLSEL_HSE | RCC_GCFGR_PLLMF6);

#endif /* GD32F10X_CL */

        /* Enable PLL */
        RCC->GCCR |= RCC_GCCR_PLLEN;

        /* Wait till PLL is ready */
        while ((RCC->GCCR & RCC_GCCR_PLLSTB) == 0) {
        }

        /* Select PLL as system clock source */
        RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_SCS));
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_SCS_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->GCFGR & (uint32_t)RCC_GCFGR_SCSS) != (uint32_t)0x08) {
        }
    } else {
    }
}

#elif defined SYSCLK_FREQ_56MHz
/**
  * @brief  Set System clock frequency to 56MHz and configure AHB, APB1, and APB2 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo56(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* CK_SYS, AHB, APB2 and APB1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->GCCR |= ((uint32_t)RCC_GCCR_HSEEN);

    /* Wait till HSE is ready and if Time out is reached exit */
    do {
        HSEStatus = RCC->GCCR & RCC_GCCR_HSESTB;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->GCCR & RCC_GCCR_HSESTB) != RESET) {
        HSEStatus = (uint32_t)0x01;
    } else {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01) {
        /* AHB = CK_SYS not divided */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_AHBPS_DIV1;

        /* APB2 = AHB not divided */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB2PS_DIV1;

        /* APB1 = AHB is divided 2 */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB1PS_DIV2;

#ifdef GD32F10X_CL
        /* Configure PLLs ------------------------------------------------------*/

        /* PLL configuration: PLLCLK = PREDIV1 * 7 = 56 MHz */
        RCC->GCFGR &= (uint32_t)~(RCC_GCFGR_PLLPREDV | RCC_GCFGR_PLLSEL | RCC_GCFGR_PLLMF);
        RCC->GCFGR |= (uint32_t)(RCC_GCFGR_PLLSEL_PREDIV1 | RCC_GCFGR_PLLMF7);
        /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
        /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 5 = 8 MHz */

        RCC->GCFGR2 &= (uint32_t)~(RCC_GCFGR2_PREDV2 | RCC_GCFGR2_PLL2MF |
                                   RCC_GCFGR2_PREDV1 | RCC_GCFGR2_PREDV1SEL);
        RCC->GCFGR2 |= (uint32_t)(RCC_GCFGR2_PREDV2_DIV5 | RCC_GCFGR2_PLL2MF8 |
                                  RCC_GCFGR2_PREDV1SEL_PLL2 | RCC_GCFGR2_PREDV1_DIV5);

        /* Enable PLL2 */
        RCC->GCCR |= RCC_GCCR_PLL2EN;
        /* Wait till PLL2 is ready */
        while ((RCC->GCCR & RCC_GCCR_PLL2STB) == 0) {
        }

#else
        /* PLL configuration: PLLCLK = HSE * 7 = 56 MHz */
        RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_PLLSEL | RCC_GCFGR_PLLPREDV | RCC_GCFGR_PLLMF));
        RCC->GCFGR |= (uint32_t)(RCC_GCFGR_PLLPREDV_HSE | RCC_GCFGR_PLLSEL_HSE | RCC_GCFGR_PLLMF7);

#endif /* GD32F10X_CL */

        /* Enable PLL */
        RCC->GCCR |= RCC_GCCR_PLLEN;

        /* Wait till PLL is ready */
        while ((RCC->GCCR & RCC_GCCR_PLLSTB) == 0) {
        }

        /* Select PLL as system clock source */
        RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_SCS));
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_SCS_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->GCFGR & (uint32_t)RCC_GCFGR_SCSS) != (uint32_t)0x08) {
        }
    } else {
    }
}

#elif defined SYSCLK_FREQ_72MHz
/**
  * @brief  Set System clock frequency to 72MHz and configure AHB, APB1, and APB2 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo72(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* CK_SYS, AHB, APB2 and APB1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->GCCR |= ((uint32_t)RCC_GCCR_HSEEN);

    /* Wait till HSE is ready and if Time out is reached exit */
    do {
        HSEStatus = RCC->GCCR & RCC_GCCR_HSESTB;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->GCCR & RCC_GCCR_HSESTB) != RESET) {
        HSEStatus = (uint32_t)0x01;
    } else {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01) {
        /* AHB = CK_SYS not divided */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_AHBPS_DIV1;

        /* APB2 = AHB not divided */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB2PS_DIV1;

        /* APB1 = AHB is divided 2 */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB1PS_DIV2;

#ifdef GD32F10X_CL
        /* Configure PLLs ------------------------------------------------------*/

        /* PLL configuration: PLLCLK = PREDIV1 * 9 = 72 MHz */
        RCC->GCFGR &= (uint32_t)~(RCC_GCFGR_PLLPREDV | RCC_GCFGR_PLLSEL | RCC_GCFGR_PLLMF);
        RCC->GCFGR |= (uint32_t)(RCC_GCFGR_PLLSEL_PREDIV1 | RCC_GCFGR_PLLMF9);

        /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
        /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 5 = 8 MHz */

        RCC->GCFGR2 &= (uint32_t)~(RCC_GCFGR2_PREDV2 | RCC_GCFGR2_PLL2MF |
                                   RCC_GCFGR2_PREDV1 | RCC_GCFGR2_PREDV1SEL);
        RCC->GCFGR2 |= (uint32_t)(RCC_GCFGR2_PREDV2_DIV5 | RCC_GCFGR2_PLL2MF8 |
                                  RCC_GCFGR2_PREDV1SEL_PLL2 | RCC_GCFGR2_PREDV1_DIV5);

        /* Enable PLL2 */
        RCC->GCCR |= RCC_GCCR_PLL2EN;
        /* Wait till PLL2 is ready */
        while ((RCC->GCCR & RCC_GCCR_PLL2STB) == 0) {
        }

#else
        /* PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
        RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_PLLSEL | RCC_GCFGR_PLLPREDV | RCC_GCFGR_PLLMF));
        RCC->GCFGR |= (uint32_t)(RCC_GCFGR_PLLPREDV_HSE | RCC_GCFGR_PLLSEL_HSE | RCC_GCFGR_PLLMF9);

#endif /* GD32F10X_CL */

        /* Enable PLL */
        RCC->GCCR |= RCC_GCCR_PLLEN;

        /* Wait till PLL is ready */
        while ((RCC->GCCR & RCC_GCCR_PLLSTB) == 0) {
        }

        /* Select PLL as system clock source */
        RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_SCS));
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_SCS_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->GCFGR & (uint32_t)RCC_GCFGR_SCSS) != (uint32_t)0x08) {
        }
    } else {
    }
}
#elif defined SYSCLK_FREQ_96MHz
/**
  * @brief  Set System clock frequency to 96MHz and configure AHB, APB1, and APB2 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo96(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* CK_SYS, AHB, APB2 and APB1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->GCCR |= ((uint32_t)RCC_GCCR_HSEEN);

    /* Wait till HSE is ready and if Time out is reached exit */
    do {
        HSEStatus = RCC->GCCR & RCC_GCCR_HSESTB;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->GCCR & RCC_GCCR_HSESTB) != RESET) {
        HSEStatus = (uint32_t)0x01;
    } else {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01) {
        /* AHB = CK_SYS not divided */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_AHBPS_DIV1;

        /* APB2 = AHB not divided */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB2PS_DIV1;

        /* APB1 = AHB is divided 2 */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB1PS_DIV2;

#ifdef GD32F10X_CL
        /* Configure PLLs ------------------------------------------------------*/

        /* PLL configuration: PLLCLK = PREDIV1 * 12 = 96 MHz */
        RCC->GCFGR &= (uint32_t)~(RCC_GCFGR_PLLPREDV | RCC_GCFGR_PLLSEL | RCC_GCFGR_PLLMF);
        RCC->GCFGR |= (uint32_t)(RCC_GCFGR_PLLSEL_PREDIV1 | RCC_GCFGR_PLLMF12);

        /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */
        /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 5 = 8 MHz */

        RCC->GCFGR2 &= (uint32_t)~(RCC_GCFGR2_PREDV2 | RCC_GCFGR2_PLL2MF |
                                   RCC_GCFGR2_PREDV1 | RCC_GCFGR2_PREDV1SEL);
        RCC->GCFGR2 |= (uint32_t)(RCC_GCFGR2_PREDV2_DIV5 | RCC_GCFGR2_PLL2MF8 |
                                  RCC_GCFGR2_PREDV1SEL_PLL2 | RCC_GCFGR2_PREDV1_DIV5);

        /* Enable PLL2 */
        RCC->GCCR |= RCC_GCCR_PLL2EN;
        /* Wait till PLL2 is ready */
        while ((RCC->GCCR & RCC_GCCR_PLL2STB) == 0) {
        }

#else
        /* PLL configuration: PLLCLK = HSE * 12 = 96 MHz */
        RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_PLLSEL | RCC_GCFGR_PLLPREDV | RCC_GCFGR_PLLMF));
        RCC->GCFGR |= (uint32_t)(RCC_GCFGR_PLLPREDV_HSE | RCC_GCFGR_PLLSEL_HSE | RCC_GCFGR_PLLMF12);

#endif /* GD32F10X_CL */

        /* Enable PLL */
        RCC->GCCR |= RCC_GCCR_PLLEN;

        /* Wait till PLL is ready */
        while ((RCC->GCCR & RCC_GCCR_PLLSTB) == 0) {
        }

        /* Select PLL as system clock source */
        RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_SCS));
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_SCS_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->GCFGR & (uint32_t)RCC_GCFGR_SCSS) != (uint32_t)0x08) {
        }
    } else {
    }
}

#elif defined SYSCLK_FREQ_108MHz
/**
  * @brief  Set System clock frequency to 108MHz and configure AHB, APB1, and APB2 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo108(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* CK_SYS, AHB, APB2 and APB1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->GCCR |= ((uint32_t)RCC_GCCR_HSEEN);

    /* Wait till HSE is ready and if Time out is reached exit */
    do {
        HSEStatus = RCC->GCCR & RCC_GCCR_HSESTB;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->GCCR & RCC_GCCR_HSESTB) != RESET) {
        HSEStatus = (uint32_t)0x01;
    } else {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01) {
        /* AHB = CK_SYS not divided */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_AHBPS_DIV1;
        /* APB2 = AHB not divided */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB2PS_DIV1;
        /* APB1 = AHB is divided 2 */
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB1PS_DIV2;

#ifdef GD32F10X_CL
        /* Configure PLLs ------------------------------------------------------*/

        /* PLL configuration: PLLCLK = PREDIV1 * 9 = 108 MHz */
        RCC->GCFGR &= (uint32_t)~(RCC_GCFGR_PLLPREDV | RCC_GCFGR_PLLSEL | RCC_GCFGR_PLLMF);
        RCC->GCFGR |= (uint32_t)(RCC_GCFGR_PLLPREDV_PREDIV1 | RCC_GCFGR_PLLSEL_PREDIV1 | RCC_GCFGR_PLLMF9);

        /* PLL2 configuration: PLL2CLK = (HSE / 5) * 12 = 60 MHz */
        /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 5 = 12 MHz */

        RCC->GCFGR2 &= (uint32_t)~(RCC_GCFGR2_PREDV2 | RCC_GCFGR2_PLL2MF |
                                   RCC_GCFGR2_PREDV1 | RCC_GCFGR2_PREDV1SEL);
        RCC->GCFGR2 |= (uint32_t)(RCC_GCFGR2_PREDV2_DIV5 | RCC_GCFGR2_PLL2MF12 |
                                  RCC_GCFGR2_PREDV1SEL_PLL2 | RCC_GCFGR2_PREDV1_DIV5);

        /* Enable PLL2 */
        RCC->GCCR |= RCC_GCCR_PLL2EN;
        /* Wait till PLL2 is ready */
        while ((RCC->GCCR & RCC_GCCR_PLL2STB) == 0) {
        }

#else
        /* PLL configuration: PLLCLK = (HSE/2) * 27 = 108 MHz */
        RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_PLLSEL | RCC_GCFGR_PLLPREDV | RCC_GCFGR_PLLMF));
        RCC->GCFGR |= (uint32_t)(RCC_GCFGR_PLLPREDV_HSE_DIV2 | RCC_GCFGR_PLLSEL_HSE | RCC_GCFGR_PLLMF27);

#endif /* GD32F10X_CL */

        /* Enable PLL */
        RCC->GCCR |= RCC_GCCR_PLLEN;

        /* Wait till PLL is ready */
        while ((RCC->GCCR & RCC_GCCR_PLLSTB) == 0) {
        }

        /* Select PLL as system clock source */
        RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_SCS));
        RCC->GCFGR |= (uint32_t)RCC_GCFGR_SCS_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->GCFGR & (uint32_t)RCC_GCFGR_SCSS) != (uint32_t)0x08) {
        }
    } else {
    }
}
#elif defined SYSCLK_FREQ_48MHz_HSI
/**
  * @brief  Set System clock frequency to 48MHz and configure AHB, APB1, and APB2 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo48HSI(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* CK_SYS, AHB, APB2 and APB1 configuration ---------------------------*/

    /* AHB = CK_SYS not divided */
    RCC->GCFGR |= (uint32_t)RCC_GCFGR_AHBPS_DIV1;

    /* APB2 = AHB not divided */
    RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB2PS_DIV1;

    /* APB1 = AHB is divided 2 */
    RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB1PS_DIV2;

    /* Configure PLLs ------------------------------------------------------*/

    /* PLL configuration: PLLCLK = (HSI/2) * 12 = 48 MHz */
    RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_PLLSEL | RCC_GCFGR_PLLMF));
    RCC->GCFGR |= (uint32_t)(RCC_GCFGR_PLLSEL_HSI_DIV2 | RCC_GCFGR_PLLMF12);

    /* Enable PLL */
    RCC->GCCR |= RCC_GCCR_PLLEN;

    /* Wait till PLL is ready */
    while ((RCC->GCCR & RCC_GCCR_PLLSTB) == 0) {
    }

    /* Select PLL as system clock source */
    RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_SCS));
    RCC->GCFGR |= (uint32_t)RCC_GCFGR_SCS_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->GCFGR & (uint32_t)RCC_GCFGR_SCSS) != (uint32_t)0x08) {
    }
}
#elif defined SYSCLK_FREQ_72MHz_HSI
/**
  * @brief  Set System clock frequency to 72MHz and configure AHB, APB1, and APB2 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo72HSI(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* CK_SYS, AHB, APB2 and APB1 configuration ---------------------------*/

    /* AHB = CK_SYS not divided */
    RCC->GCFGR |= (uint32_t)RCC_GCFGR_AHBPS_DIV1;

    /* APB2 = AHB not divided */
    RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB2PS_DIV1;

    /* APB1 = AHB is divided 2 */
    RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB1PS_DIV2;

    /* Configure PLLs ------------------------------------------------------*/

    /* PLL configuration: PLLCLK = (HSI/2) * 18 = 72 MHz */
    RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_PLLSEL | RCC_GCFGR_PLLMF));
    RCC->GCFGR |= (uint32_t)(RCC_GCFGR_PLLSEL_HSI_DIV2 | RCC_GCFGR_PLLMF18);

    /* Enable PLL */
    RCC->GCCR |= RCC_GCCR_PLLEN;

    /* Wait till PLL is ready */
    while ((RCC->GCCR & RCC_GCCR_PLLSTB) == 0) {
    }

    /* Select PLL as system clock source */
    RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_SCS));
    RCC->GCFGR |= (uint32_t)RCC_GCFGR_SCS_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->GCFGR & (uint32_t)RCC_GCFGR_SCSS) != (uint32_t)0x08) {
    }
}

#elif defined SYSCLK_FREQ_108MHz_HSI
/**
  * @brief  Set System clock frequency to 108MHz and configure AHB, APB1, and APB2 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo108HSI(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* CK_SYS, AHB, APB2 and APB1 configuration ---------------------------*/

    /* AHB = CK_SYS not divided */
    RCC->GCFGR |= (uint32_t)RCC_GCFGR_AHBPS_DIV1;

    /* APB2 = AHB not divided */
    RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB2PS_DIV1;

    /* APB1 = AHB is divided 2 */
    RCC->GCFGR |= (uint32_t)RCC_GCFGR_APB1PS_DIV2;

    /* Configure PLLs ------------------------------------------------------*/

    /* PLL configuration: PLLCLK = (HSI/2) * 27 = 108 MHz */
    RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_PLLSEL | RCC_GCFGR_PLLPREDV | RCC_GCFGR_PLLMF));
    RCC->GCFGR |= (uint32_t)(RCC_GCFGR_PLLSEL_HSI_DIV2 | RCC_GCFGR_PLLMF27);

    /* Enable PLL */
    RCC->GCCR |= RCC_GCCR_PLLEN;

    /* Wait till PLL is ready */
    while ((RCC->GCCR & RCC_GCCR_PLLSTB) == 0) {
    }

    /* Select PLL as system clock source */
    RCC->GCFGR &= (uint32_t)((uint32_t)~(RCC_GCFGR_SCS));
    RCC->GCFGR |= (uint32_t)RCC_GCFGR_SCS_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->GCFGR & (uint32_t)RCC_GCFGR_SCSS) != (uint32_t)0x08) {
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


