/**
  ******************************************************************************
  * @file    system_at32f4xx.c
  * @author  Artery Technology
  * @version V1.0.0
  * @date    2019-05-27
  * @brief   CMSIS Cortex-M4 system source file
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, ARTERYTEK SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2018 ArteryTek</center></h2>
  ******************************************************************************
  */ 

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup at32f4xx_system
  * @{
  */

/** @addtogroup at32f4xx_System_Private_Includes
  * @{
  */

#include "at32f4xx.h"

/**
  * @}
  */

/** @addtogroup at32f4xx_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup at32f4xx_System_Private_Defines
  * @{
  */

/*!< Uncomment the line corresponding to the desired System clock (SYSCLK)
   frequency (after reset the HSI is used as SYSCLK source)

   IMPORTANT NOTE:
   ==============
   1. After each device reset the HSI is used as System clock source.

   2. Please make sure that the selected System clock doesn't exceed your device's
      maximum frequency.

   3. If none of the define below is enabled, the HSI is used as System clock
    source.

   4. The System clock configuration functions provided within this file assume that:
        - For at32f4xx devices, an external 8MHz crystal is used to drive the System clock.
     If you are using different crystal you have to adapt those functions accordingly.

      Clock (MHz)
          PLL from HSE or HSI
          SYSCLK	    HCLK	PCLK2	PCLK1
          24	        24	    24	    24
          36	        36	    36	    36
          48	        48	    48	    24
          56	        56	    56	    28
          72	        72	    72	    36
          96	        96	    48	    48
          108	        108	    54	    54
          120	        120	    60	    60
          144	        144	    72	    72
          150	        150	    75	    75
          168	        168	    84	    84
          176	        176	    88	    88
          192	        192	    96	    96
          200	        200	    100	    100
          224	        224	    112	    112
          240	        240	    120	    120
    */

#if defined (AT32F403xx) || defined (AT32F413xx) || \
    defined (AT32F415xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
/* #define SYSCLK_FREQ_HSE          HSE_VALUE */
/* #define SYSCLK_FREQ_24MHz        24000000 */
/* #define SYSCLK_FREQ_36MHz        36000000 */
/* #define SYSCLK_FREQ_48MHz        48000000 */
/* #define SYSCLK_FREQ_56MHz        56000000 */
/* #define SYSCLK_FREQ_72MHz        72000000 */
/* #define SYSCLK_FREQ_96MHz        96000000 */
/* #define SYSCLK_FREQ_108MHz       108000000 */
/* #define SYSCLK_FREQ_120MHz       120000000 */
/* #define SYSCLK_FREQ_144MHz       144000000 */
/* #define SYSCLK_FREQ_24MHz_HSI    24000000 */
/* #define SYSCLK_FREQ_36MHz_HSI    36000000 */
/* #define SYSCLK_FREQ_48MHz_HSI    48000000 */
/* #define SYSCLK_FREQ_56MHz_HSI    56000000 */
/* #define SYSCLK_FREQ_72MHz_HSI    72000000 */
/* #define SYSCLK_FREQ_96MHz_HSI    96000000 */
/* #define SYSCLK_FREQ_108MHz_HSI   108000000 */
/* #define SYSCLK_FREQ_120MHz_HSI   120000000 */
/* #define SYSCLK_FREQ_144MHz_HSI   144000000 */
#endif

#if defined (AT32F415xx)
/* #define SYSCLK_FREQ_150MHz       150000000 */
/* #define SYSCLK_FREQ_150MHz_HSI   150000000 */
#endif

#if defined (AT32F403xx) || defined (AT32F413xx) || \
    defined (AT32F403Axx)|| defined (AT32F407xx)
/* #define SYSCLK_FREQ_168MHz       168000000 */
/* #define SYSCLK_FREQ_176MHz       176000000 */
/* #define SYSCLK_FREQ_192MHz       192000000 */
/* #define SYSCLK_FREQ_200MHz       200000000 */
/* #define SYSCLK_FREQ_168MHz_HSI   168000000 */
/* #define SYSCLK_FREQ_176MHz_HSI   176000000 */
/* #define SYSCLK_FREQ_192MHz_HSI   192000000 */
/* #define SYSCLK_FREQ_200MHz_HSI   200000000 */
#endif

#if defined (AT32F403Axx)|| defined (AT32F407xx)
/* #define SYSCLK_FREQ_224MHz       224000000 */
/* #define SYSCLK_FREQ_240MHz       240000000 */
/* #define SYSCLK_FREQ_224MHz_HSI   224000000 */
/* #define SYSCLK_FREQ_240MHz_HSI   240000000 */
#endif

/*!< Uncomment the following line if you need to use external SRAM mounted
     (AT32 High density and XL-density devices) as data memory */

/* #define DATA_IN_ExtSRAM */

/*!< Uncomment the following line if you need to relocate your vector Table in
     Internal SRAM. */
/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x0 /*!< Vector Table base offset field. 
This value must be a multiple of 0x200. */


/**
  * @}
  */

/** @addtogroup at32f4xx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup at32f4xx_System_Private_Variables
  * @{
  */

/*******************************************************************************
*  Clock Definitions
*******************************************************************************/
#ifdef SYSCLK_FREQ_HSE
uint32_t SystemCoreClock         = SYSCLK_FREQ_HSE;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_24MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_24MHz;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_36MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_36MHz;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_48MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_48MHz;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_56MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_56MHz;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_72MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_72MHz;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_96MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_96MHz;        /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_108MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_108MHz;       /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_120MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_120MHz;       /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_144MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_144MHz;       /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_150MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_150MHz;       /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_168MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_168MHz;       /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_176MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_176MHz;       /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_192MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_192MHz;       /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_200MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_200MHz;       /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_224MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_224MHz;       /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_240MHz
uint32_t SystemCoreClock         = SYSCLK_FREQ_240MHz;       /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_24MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_24MHz_HSI;    /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_36MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_36MHz_HSI;    /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_48MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_48MHz_HSI;    /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_56MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_56MHz_HSI;    /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_72MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_72MHz_HSI;    /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_96MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_96MHz_HSI;    /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_108MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_108MHz_HSI;    /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_120MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_120MHz_HSI;    /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_144MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_144MHz_HSI;    /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_150MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_150MHz_HSI;    /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_168MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_168MHz_HSI;    /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_176MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_176MHz_HSI;    /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_192MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_192MHz_HSI;    /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_200MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_200MHz_HSI;    /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_224MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_224MHz_HSI;    /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_240MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_240MHz_HSI;    /*!< System Clock Frequency (Core Clock) */
#else /*!< HSI Selected as System Clock source */
#define SYSCLK_FREQ_HSI            HSI_VALUE
uint32_t SystemCoreClock         = HSI_VALUE;        /*!< System Clock Frequency (Core Clock) */
#endif

__I uint8_t AHBPscTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
/**
  * @}
  */

/** @addtogroup at32f4xx_System_Private_FunctionPrototypes
  * @{
  */

static void SetSysClock(void);

#ifdef SYSCLK_FREQ_HSE
static void SetSysClockToHSE(void);
#elif defined SYSCLK_FREQ_24MHz
static void SetSysClockTo24M(void);
#elif defined SYSCLK_FREQ_36MHz
static void SetSysClockTo36M(void);
#elif defined SYSCLK_FREQ_48MHz
static void SetSysClockTo48M(void);
#elif defined SYSCLK_FREQ_56MHz
static void SetSysClockTo56M(void);
#elif defined SYSCLK_FREQ_72MHz
static void SetSysClockTo72M(void);
#elif defined SYSCLK_FREQ_96MHz
static void SetSysClockTo96M(void);
#elif defined SYSCLK_FREQ_108MHz
static void SetSysClockTo108M(void);
#elif defined SYSCLK_FREQ_120MHz
static void SetSysClockTo120M(void);
#elif defined SYSCLK_FREQ_144MHz
static void SetSysClockTo144M(void);
#elif defined SYSCLK_FREQ_150MHz
static void SetSysClockTo150M(void);
#elif defined SYSCLK_FREQ_168MHz
static void SetSysClockTo168M(void);
#elif defined SYSCLK_FREQ_176MHz
static void SetSysClockTo176M(void);
#elif defined SYSCLK_FREQ_192MHz
static void SetSysClockTo192M(void);
#elif defined SYSCLK_FREQ_200MHz
static void SetSysClockTo200M(void);
#elif defined SYSCLK_FREQ_224MHz
static void SetSysClockTo224M(void);
#elif defined SYSCLK_FREQ_240MHz
static void SetSysClockTo240M(void);
#elif defined SYSCLK_FREQ_24MHz_HSI
static void SetSysClockTo24MHSI(void);
#elif defined SYSCLK_FREQ_36MHz_HSI
static void SetSysClockTo36MHSI(void);
#elif defined SYSCLK_FREQ_48MHz_HSI
static void SetSysClockTo48MHSI(void);
#elif defined SYSCLK_FREQ_56MHz_HSI
static void SetSysClockTo56MHSI(void);
#elif defined SYSCLK_FREQ_72MHz_HSI
static void SetSysClockTo72MHSI(void);
#elif defined SYSCLK_FREQ_96MHz_HSI
static void SetSysClockTo96MHSI(void);
#elif defined SYSCLK_FREQ_108MHz_HSI
static void SetSysClockTo108MHSI(void);
#elif defined SYSCLK_FREQ_120MHz_HSI
static void SetSysClockTo120MHSI(void);
#elif defined SYSCLK_FREQ_144MHz_HSI
static void SetSysClockTo144MHSI(void);
#elif defined SYSCLK_FREQ_150MHz_HSI
static void SetSysClockTo150MHSI(void);
#elif defined SYSCLK_FREQ_168MHz_HSI
static void SetSysClockTo168MHSI(void);
#elif defined SYSCLK_FREQ_176MHz_HSI
static void SetSysClockTo176MHSI(void);
#elif defined SYSCLK_FREQ_192MHz_HSI
static void SetSysClockTo192MHSI(void);
#elif defined SYSCLK_FREQ_200MHz_HSI
static void SetSysClockTo200MHSI(void);
#elif defined SYSCLK_FREQ_224MHz_HSI
static void SetSysClockTo224MHSI(void);
#elif defined SYSCLK_FREQ_240MHz_HSI
static void SetSysClockTo240MHSI(void);
#endif

#ifdef DATA_IN_ExtSRAM
static void SystemInit_ExtMemCtrl(void);
#endif /* DATA_IN_ExtSRAM */

/**
  * @}
  */

/** @addtogroup at32f4xx_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system
  *         Initialize the Embedded Flash Interface, the PLL and update the
  *         SystemCoreClock variable.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
void SystemInit (void)
{
#if defined (AT32F415xx)
  /* Enable low power mode, 0x40007050[bit2] */
  RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_PWR, ENABLE);
  *(volatile uint8_t *)(0x40007050) |= (uint8_t)(0x1 << 2);
  RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_PWR, DISABLE);
#endif

#if defined (__FPU_USED) && (__FPU_USED == 1U)
  SCB->CPACR |= ((3U << 10U * 2U) |         /* set CP10 Full Access */
                 (3U << 11U * 2U)  );       /* set CP11 Full Access */
#endif

  /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
  /* Set HSIEN bit */
  BIT_SET(RCC->CTRL, RCC_CTRL_HSIEN);

  /* Reset SW, AHBPSC, APB1PSC, APB2PSC, ADCPSC and CLKOUT bits */
  BIT_CLEAR(RCC->CFG, RCC_CFG_SYSCLKSEL | RCC_CFG_AHBPSC | \
            RCC_CFG_APB1PSC | RCC_CFG_APB2PSC | \
            RCC_CFG_ADCPSC | RCC_CFG_CLKOUT);

  /* Reset HSEEN, HSECFDEN and PLLEN bits */
  BIT_CLEAR(RCC->CTRL, RCC_CTRL_HSEEN | RCC_CTRL_HSECFDEN | \
            RCC_CTRL_PLLEN);

  /* Reset HSEBYPS bit */
  BIT_CLEAR(RCC->CTRL, RCC_CTRL_HSEBYPS);

  /* Reset PLLRC, PLLHSEPSC, PLLMUL, USBPSC and PLLRANGE bits */
  BIT_CLEAR(RCC->CFG, RCC_CFG_PLLRC | RCC_CFG_PLLHSEPSC | \
            RCC_CFG_PLLMULT | RCC_CFG_USBPSC | RCC_CFG_PLLRANGE);

  /* Reset USB768B, CLKOUT[3], HSICAL_KEY[7:0] */
  BIT_CLEAR(RCC->MISC, 0x010100FF);

  /* Disable all interrupts and clear pending bits  */
  RCC->CLKINT = RCC_CLKINT_LSISTBLFC | RCC_CLKINT_LSESTBLFC | \
                RCC_CLKINT_HSISTBLFC | RCC_CLKINT_HSESTBLFC | \
                RCC_CLKINT_PLLSTBLFC | RCC_CLKINT_HSECFDFC;

#ifdef DATA_IN_ExtSRAM
  SystemInit_ExtMemCtrl();
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
  *             or HSI_VALUE(*) multiplied by the PLL factors.
  *
  *         (*) HSI_VALUE is a constant defined in at32f4xx.h file (default value
  *             8 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature.
  *
  *         (**) HSE_VALUE is a constant defined in at32f4xx.h file (default value
  *              8 MHz or 25 MHz, depedning on the product used), user has to ensure
  *              that HSE_VALUE is same as the real frequency of the crystal used.
  *              Otherwise, this function may have wrong result.
  *
  *         - The result of this function could be not correct when using fractional
  *           value for HSE crystal.
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate (void)
{
  uint32_t tmp = 0, pllmult = 0, pllrefclk = 0, tempcfg = 0;

  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFG & RCC_CFG_SYSCLKSTS;

  switch (tmp)
  {
  case RCC_CFG_SYSCLKSTS_HSI:  /* HSI used as system clock */
    SystemCoreClock = HSI_VALUE;
    break;

  case RCC_CFG_SYSCLKSTS_HSE:  /* HSE used as system clock */
    SystemCoreClock = HSE_VALUE;
    break;

  case RCC_CFG_SYSCLKSTS_PLL:  /* PLL used as system clock */
    /* Get PLL clock source and multiplication factor ----------------------*/
    pllrefclk = RCC->CFG & RCC_CFG_PLLRC;
    tempcfg = RCC->CFG;
    pllmult = RCC_GET_PLLMULT(tempcfg);

    if (pllrefclk == RCC_PLLRefClk_HSI_Div2)
    {
      /* HSI oscillator clock divided by 2 selected as PLL clock entry */
      SystemCoreClock = (HSI_VALUE >> 1) * pllmult;
    }
    else
    {
      /* HSE selected as PLL clock entry */
      if ((RCC->CFG & RCC_CFG_PLLHSEPSC) != (uint32_t)RESET)
      {
        /* HSE oscillator clock divided by 2 */
        SystemCoreClock = (HSE_VALUE >> 1) * pllmult;
      }
      else
      {
        SystemCoreClock = HSE_VALUE * pllmult;
      }
    }

    break;

  default:
    SystemCoreClock = HSI_VALUE;
    break;
  }

  /* Compute HCLK clock frequency ----------------*/
  /* Get HCLK prescaler */
  tmp = AHBPscTable[((RCC->CFG & RCC_CFG_AHBPSC) >> 4)];
  /* HCLK clock frequency */
  SystemCoreClock >>= tmp;
}

/**
  * @brief  Configures the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers.
  * @param  None
  * @retval None
  */
static void SetSysClock(void)
{
#ifdef SYSCLK_FREQ_HSE
  SetSysClockToHSE();
#elif defined SYSCLK_FREQ_24MHz
  SetSysClockTo24M();
#elif defined SYSCLK_FREQ_36MHz
  SetSysClockTo36M();
#elif defined SYSCLK_FREQ_48MHz
  SetSysClockTo48M();
#elif defined SYSCLK_FREQ_56MHz
  SetSysClockTo56M();
#elif defined SYSCLK_FREQ_72MHz
  SetSysClockTo72M();
#elif defined SYSCLK_FREQ_96MHz
  SetSysClockTo96M();
#elif defined SYSCLK_FREQ_108MHz
  SetSysClockTo108M();
#elif defined SYSCLK_FREQ_120MHz
  SetSysClockTo120M();
#elif defined SYSCLK_FREQ_144MHz
  SetSysClockTo144M();
#elif defined SYSCLK_FREQ_150MHz
  SetSysClockTo150M();
#elif defined SYSCLK_FREQ_168MHz
  SetSysClockTo168M();
#elif defined SYSCLK_FREQ_176MHz
  SetSysClockTo176M();
#elif defined SYSCLK_FREQ_192MHz
  SetSysClockTo192M();
#elif defined SYSCLK_FREQ_200MHz
  SetSysClockTo200M();
#elif defined SYSCLK_FREQ_224MHz
  SetSysClockTo224M();
#elif defined SYSCLK_FREQ_240MHz
  SetSysClockTo240M();
#elif defined SYSCLK_FREQ_24MHz_HSI
  SetSysClockTo24MHSI();
#elif defined SYSCLK_FREQ_36MHz_HSI
  SetSysClockTo36MHSI();
#elif defined SYSCLK_FREQ_48MHz_HSI
  SetSysClockTo48MHSI();
#elif defined SYSCLK_FREQ_56MHz_HSI
  SetSysClockTo56MHSI();
#elif defined SYSCLK_FREQ_72MHz_HSI
  SetSysClockTo72MHSI();
#elif defined SYSCLK_FREQ_96MHz_HSI
  SetSysClockTo96MHSI();
#elif defined SYSCLK_FREQ_108MHz_HSI
  SetSysClockTo108MHSI();
#elif defined SYSCLK_FREQ_120MHz_HSI
  SetSysClockTo120MHSI();
#elif defined SYSCLK_FREQ_144MHz_HSI
  SetSysClockTo144MHSI();
#elif defined SYSCLK_FREQ_150MHz_HSI
  SetSysClockTo150MHSI();
#elif defined SYSCLK_FREQ_168MHz_HSI
  SetSysClockTo168MHSI();
#elif defined SYSCLK_FREQ_176MHz_HSI
  SetSysClockTo176MHSI();
#elif defined SYSCLK_FREQ_192MHz_HSI
  SetSysClockTo192MHSI();
#elif defined SYSCLK_FREQ_200MHz_HSI
  SetSysClockTo200MHSI();
#elif defined SYSCLK_FREQ_224MHz_HSI
  SetSysClockTo224MHSI();
#elif defined SYSCLK_FREQ_240MHz_HSI
  SetSysClockTo240MHSI();
#endif

  /* If none of the define above is enabled, the HSI is used as System clock
     source (default after reset) */
}

/**
  * @brief  Setup the external memory controller. Called in startup_at32f4xx.s
  *          before jump to __main
  * @param  None
  * @retval None
  */
#ifdef DATA_IN_ExtSRAM
/**
  * @brief  Setup the external memory controller.
  *         Called in startup_at32f4xx_xx.s/.c before jump to main.
  * 	      This function configures the external SRAM mounted
  *         (AT32 High density devices). This SRAM will be used as program
  *         data memory (including heap and stack).
  * @param  None
  * @retval None
  */
void SystemInit_ExtMemCtrl(void)
{
  /* Enable XMC clock */
  RCC->AHBEN = RCC_AHBEN_SRAMEN | RCC_AHBEN_FLASHEN | RCC_AHBEN_XMCEN;

  /* Enable GPIOD, GPIOE, GPIOF and GPIOG clocks */
  RCC->APB2EN = RCC_APB2EN_GPIODEN | RCC_APB2EN_GPIOEEN | RCC_APB2EN_GPIOFEN | RCC_APB2EN_GPIOGEN;

  /* ---------------  SRAM Data lines, NOE and NWE configuration ---------------*/
  /*----------------  SRAM Address lines configuration -------------------------*/
  /*----------------  NOE and NWE configuration --------------------------------*/
  /*----------------  NE3 configuration ----------------------------------------*/
  /*----------------  NBL0, NBL1 configuration ---------------------------------*/

  GPIOD->CTRLL = 0x44BB44BB;
  GPIOD->CTRLH = 0xBBBBBBBB;

  GPIOE->CTRLL = 0xB44444BB;
  GPIOE->CTRLH = 0xBBBBBBBB;

  GPIOF->CTRLL = 0x44BBBBBB;
  GPIOF->CTRLH = 0xBBBB4444;

  GPIOG->CTRLL = 0x44BBBBBB;
  GPIOG->CTRLH = 0x44444B44;

  /*----------------  XMC Configuration ---------------------------------------*/
  /*----------------  Enable XMC Bank1_SRAM Bank ------------------------------*/

  XMC_Bank1->BK1CTRLR[4] = 0x00001011;
  XMC_Bank1->BK1CTRLR[5] = 0x00000200;
}
#endif /* DATA_IN_ExtSRAM */

#ifndef SYSCLK_FREQ_HSI
#ifdef AT32F403xx
/**
  * @brief  Delay to wait for HSE stable.
  * @note   This function should be used before reading the HSESTBL flag.
  * @param  None
  * @retval None
  */
static void WaitHseStbl(uint32_t delay)
{
  uint32_t i;

  for(i = 0; i < delay; i++)
    ;
}
#endif
#endif /* SYSCLK_FREQ_HSI */

#ifdef SYSCLK_FREQ_HSE
/**
  * @brief  Selects HSE as System clock source and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockToHSE(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CTRL & RCC_CTRL_HSESTBL;
    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
#ifdef AT32F403xx 
  WaitHseStbl(HSE_STABLE_DELAY);
#endif
  if ((RCC->CTRL & RCC_CTRL_HSESTBL) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_0;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV1;

    /* PCLK1 = HCLK */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV1;

    /* Select HSE as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_HSE;

    /* Wait till HSE is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != (uint32_t)0x04)
    {
    }
  }
  else
  {
    /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
}
#elif defined SYSCLK_FREQ_24MHz
/**
  * @brief  Sets System clock frequency to 24MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo24M(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CTRL & RCC_CTRL_HSESTBL;
    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
#ifdef AT32F403xx 
  WaitHseStbl(HSE_STABLE_DELAY);
#endif
  if ((RCC->CTRL & RCC_CTRL_HSESTBL) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_0;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV1;

    /* PCLK1 = HCLK */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV1;

    /*  PLL configuration:  = (HSE / 2) * 6 = 24 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLHSEPSC_HSE_DIV2 | RCC_CFG_PLLMULT6);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
  }
  else
  {
    /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
}
#elif defined SYSCLK_FREQ_36MHz
/**
  * @brief  Sets System clock frequency to 36MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo36M(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CTRL & RCC_CTRL_HSESTBL;
    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
#ifdef AT32F403xx 
  WaitHseStbl(HSE_STABLE_DELAY);
#endif
  if ((RCC->CTRL & RCC_CTRL_HSESTBL) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_1;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV1;

    /* PCLK1 = HCLK */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV1;

    /*  PLL configuration: PLLCLK = (HSE / 2) * 9 = 36 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLHSEPSC_HSE_DIV2 | RCC_CFG_PLLMULT9);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
  }
  else
  {
    /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
}
#elif defined SYSCLK_FREQ_48MHz
/**
  * @brief  Sets System clock frequency to 48MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo48M(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CTRL & RCC_CTRL_HSESTBL;
    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
#ifdef AT32F403xx 
  WaitHseStbl(HSE_STABLE_DELAY);
#endif
  if ((RCC->CTRL & RCC_CTRL_HSESTBL) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_1;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV1;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = HSE * 6 = 48 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLMULT6);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
  }
  else
  {
    /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
}

#elif defined SYSCLK_FREQ_56MHz
/**
  * @brief  Sets System clock frequency to 56MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo56M(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CTRL & RCC_CTRL_HSESTBL;
    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
#ifdef AT32F403xx 
  WaitHseStbl(HSE_STABLE_DELAY);
#endif
  if ((RCC->CTRL & RCC_CTRL_HSESTBL) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_1;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV1;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /* PLL configuration: PLLCLK = HSE * 7 = 56 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLMULT7);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
  }
  else
  {
    /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
}

#elif defined SYSCLK_FREQ_72MHz
/**
  * @brief  Sets System clock frequency to 72MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo72M(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CTRL & RCC_CTRL_HSESTBL;
    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
#ifdef AT32F403xx 
  WaitHseStbl(HSE_STABLE_DELAY);
#endif
  if ((RCC->CTRL & RCC_CTRL_HSESTBL) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV1;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLMULT9);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
  }
  else
  {
    /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
}

#elif defined SYSCLK_FREQ_96MHz
/**
  * @brief  Sets System clock frequency to 96MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo96M(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CTRL & RCC_CTRL_HSESTBL;
    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
#ifdef AT32F403xx 
  WaitHseStbl(HSE_STABLE_DELAY);
#endif
  if ((RCC->CTRL & RCC_CTRL_HSESTBL) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = HSE * 12 = 96 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
#if defined (AT32F415xx)
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLMULT12);
#else
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLMULT12 | RCC_CFG_PLLRANGE_GT72MHZ);
#endif

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
  }
  else
  {
    /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
}

#elif defined SYSCLK_FREQ_108MHz
/**
  * @brief  Sets System clock frequency to 108MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo108M(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CTRL & RCC_CTRL_HSESTBL;
    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
#ifdef AT32F403xx 
  WaitHseStbl(HSE_STABLE_DELAY);
#endif
  if ((RCC->CTRL & RCC_CTRL_HSESTBL) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_3;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = (HSE/2) * 27 = 108 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;

#if defined (AT32F415xx)
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLHSEPSC_HSE_DIV2 | RCC_CFG_PLLMULT27);
#else
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLHSEPSC_HSE_DIV2 | RCC_CFG_PLLMULT27 \
                           | RCC_CFG_PLLRANGE_GT72MHZ);
#endif
    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
  }
  else
  {
    /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
}

#elif defined SYSCLK_FREQ_120MHz
/**
  * @brief  Sets System clock frequency to 120MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo120M(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CTRL & RCC_CTRL_HSESTBL;
    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
#ifdef AT32F403xx 
  WaitHseStbl(HSE_STABLE_DELAY);
#endif
  if ((RCC->CTRL & RCC_CTRL_HSESTBL) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_3;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = HSE * 15 = 120 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;

#if defined (AT32F415xx)
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLMULT15);
#else
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLMULT15 | RCC_CFG_PLLRANGE_GT72MHZ);
#endif

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx) || defined (AT32F415xx)
    RCC_StepModeCmd(ENABLE);
#endif
    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx) || defined (AT32F415xx)
    RCC_StepModeCmd(DISABLE);
#endif
  }
  else
  {
    /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
}

#elif defined SYSCLK_FREQ_144MHz
/**
  * @brief  Sets System clock frequency to 144MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo144M(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CTRL & RCC_CTRL_HSESTBL;
    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
#ifdef AT32F403xx 
  WaitHseStbl(HSE_STABLE_DELAY);
#endif
  if ((RCC->CTRL & RCC_CTRL_HSESTBL) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_4;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = HSE * 18 = 144 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    
#if defined (AT32F415xx)
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLMULT18);
#else
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLMULT18 | RCC_CFG_PLLRANGE_GT72MHZ);
#endif

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx) || defined (AT32F415xx)
    RCC_StepModeCmd(ENABLE);
#endif
    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx) || defined (AT32F415xx)
    RCC_StepModeCmd(DISABLE);
#endif
  }
  else
  {
    /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
}

#elif defined SYSCLK_FREQ_150MHz
/**
  * @brief  Sets System clock frequency to 150MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo150M(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CTRL & RCC_CTRL_HSESTBL;
    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
#ifdef AT32F403xx 
  WaitHseStbl(HSE_STABLE_DELAY);
#endif
  if ((RCC->CTRL & RCC_CTRL_HSESTBL) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_4;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = (HSE * 75) / (1 * 4) = 150 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE);
    RCC_PLLconfig2(PLL_FREF_8M, 75, 1, PLL_FR_4);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx) || defined (AT32F415xx)
    RCC_StepModeCmd(ENABLE);
#endif
    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx) || defined (AT32F415xx)
    RCC_StepModeCmd(DISABLE);
#endif
  }
  else
  {
    /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
}

#elif defined SYSCLK_FREQ_168MHz
/**
  * @brief  Sets System clock frequency to 168MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo168M(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CTRL & RCC_CTRL_HSESTBL;
    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
#ifdef AT32F403xx 
  WaitHseStbl(HSE_STABLE_DELAY);
#endif
  if ((RCC->CTRL & RCC_CTRL_HSESTBL) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = HSE * 21 = 168 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLMULT21 | RCC_CFG_PLLRANGE_GT72MHZ);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(ENABLE);
#endif
    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(DISABLE);
#endif
  }
  else
  {
    /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
}

#elif defined SYSCLK_FREQ_176MHz
/**
  * @brief  Sets System clock frequency to 176MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo176M(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CTRL & RCC_CTRL_HSESTBL;
    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
#ifdef AT32F403xx 
  WaitHseStbl(HSE_STABLE_DELAY);
#endif
  if ((RCC->CTRL & RCC_CTRL_HSESTBL) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = HSE * 22 = 176 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLMULT22 | RCC_CFG_PLLRANGE_GT72MHZ);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(ENABLE);
#endif
    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(DISABLE);
#endif
  }
  else
  {
    /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
}

#elif defined SYSCLK_FREQ_192MHz
/**
  * @brief  Sets System clock frequency to 192MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo192M(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CTRL & RCC_CTRL_HSESTBL;
    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
#ifdef AT32F403xx 
  WaitHseStbl(HSE_STABLE_DELAY);
#endif
  if ((RCC->CTRL & RCC_CTRL_HSESTBL) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = HSE * 24 = 192 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLMULT24 | RCC_CFG_PLLRANGE_GT72MHZ);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(ENABLE);
#endif
    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(DISABLE);
#endif
  }
  else
  {
    /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
}

#elif defined SYSCLK_FREQ_200MHz
/**
  * @brief  Sets System clock frequency to 200MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo200M(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CTRL & RCC_CTRL_HSESTBL;
    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
#ifdef AT32F403xx 
  WaitHseStbl(HSE_STABLE_DELAY);
#endif
  if ((RCC->CTRL & RCC_CTRL_HSESTBL) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = HSE * 25 = 200 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLMULT25 | RCC_CFG_PLLRANGE_GT72MHZ);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(ENABLE);
#endif
    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(DISABLE);
#endif
  }
  else
  {
    /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
}

#elif defined SYSCLK_FREQ_224MHz
/**
  * @brief  Sets System clock frequency to 224MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo224M(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CTRL & RCC_CTRL_HSESTBL;
    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
#ifdef AT32F403xx 
  WaitHseStbl(HSE_STABLE_DELAY);
#endif
  if ((RCC->CTRL & RCC_CTRL_HSESTBL) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = HSE * 28 = 224 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLMULT28 | RCC_CFG_PLLRANGE_GT72MHZ);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(ENABLE);
#endif
    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(DISABLE);
#endif
  }
  else
  {
    /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
}

#elif defined SYSCLK_FREQ_240MHz
/**
  * @brief  Sets System clock frequency to 240MHz and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo240M(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSE */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CTRL & RCC_CTRL_HSESTBL;
    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
#ifdef AT32F403xx 
  WaitHseStbl(HSE_STABLE_DELAY);
#endif
  if ((RCC->CTRL & RCC_CTRL_HSESTBL) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = HSE * 30 = 240 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSE | RCC_CFG_PLLMULT30 | RCC_CFG_PLLRANGE_GT72MHZ);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(ENABLE);
#endif
    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(DISABLE);
#endif
  }
  else
  {
    /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
}

#elif defined SYSCLK_FREQ_24MHz_HSI
/**
  * @brief  Sets System clock frequency to 24MHz from HSI and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo24MHSI(void)
{
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSI */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

  /* Wait till HSI is ready and if Time out is reached exit */
  do
  {
    HSIStatus = RCC->CTRL & RCC_CTRL_HSISTBL;
    StartUpCounter++;
  }
  while((HSIStatus == 0) && (StartUpCounter != 0xFFFF));

  if ((RCC->CTRL & RCC_CTRL_HSISTBL) != RESET)
  {
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }

  if (HSIStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_0;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV1;

    /* PCLK1 = HCLK */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV1;

    /*  PLL configuration: PLLCLK = (HSI/2) * 6 = 24 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT6);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
  }
}

#elif defined SYSCLK_FREQ_36MHz_HSI
/**
  * @brief  Sets System clock frequency to 36MHz from HSI and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo36MHSI(void)
{
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSI */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

  /* Wait till HSI is ready and if Time out is reached exit */
  do
  {
    HSIStatus = RCC->CTRL & RCC_CTRL_HSISTBL;
    StartUpCounter++;
  }
  while((HSIStatus == 0) && (StartUpCounter != 0xFFFF));

  if ((RCC->CTRL & RCC_CTRL_HSISTBL) != RESET)
  {
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }

  if (HSIStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_1;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV1;

    /* PCLK1 = HCLK */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV1;

    /*  PLL configuration: PLLCLK = (HSI/2) * 9 = 36 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT9);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
  }
}

#elif defined SYSCLK_FREQ_48MHz_HSI
/**
  * @brief  Sets System clock frequency to 48MHz from HSI and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo48MHSI(void)
{
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSI */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

  /* Wait till HSI is ready and if Time out is reached exit */
  do
  {
    HSIStatus = RCC->CTRL & RCC_CTRL_HSISTBL;
    StartUpCounter++;
  }
  while((HSIStatus == 0) && (StartUpCounter != 0xFFFF));

  if ((RCC->CTRL & RCC_CTRL_HSISTBL) != RESET)
  {
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }

  if (HSIStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_1;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV1;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = (HSI/2) * 12 = 48 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT12);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
  }
}

#elif defined SYSCLK_FREQ_56MHz_HSI
/**
  * @brief  Sets System clock frequency to 56MHz from HSI and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo56MHSI(void)
{
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSI */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

  /* Wait till HSI is ready and if Time out is reached exit */
  do
  {
    HSIStatus = RCC->CTRL & RCC_CTRL_HSISTBL;
    StartUpCounter++;
  }
  while((HSIStatus == 0) && (StartUpCounter != 0xFFFF));

  if ((RCC->CTRL & RCC_CTRL_HSISTBL) != RESET)
  {
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }

  if (HSIStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_1;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV1;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = (HSI/2) * 14 = 56 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT14);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
  }
}

#elif defined SYSCLK_FREQ_72MHz_HSI
/**
  * @brief  Sets System clock frequency to 72MHz from HSI and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo72MHSI(void)
{
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSI */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

  /* Wait till HSI is ready and if Time out is reached exit */
  do
  {
    HSIStatus = RCC->CTRL & RCC_CTRL_HSISTBL;
    StartUpCounter++;
  }
  while((HSIStatus == 0) && (StartUpCounter != 0xFFFF));

  if ((RCC->CTRL & RCC_CTRL_HSISTBL) != RESET)
  {
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }

  if (HSIStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV1;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = (HSI/2) * 18 = 72 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT18);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
  }
}

#elif defined SYSCLK_FREQ_96MHz_HSI
/**
  * @brief  Sets System clock frequency to 96MHz from HSI and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo96MHSI(void)
{
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSI */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

  /* Wait till HSI is ready and if Time out is reached exit */
  do
  {
    HSIStatus = RCC->CTRL & RCC_CTRL_HSISTBL;
    StartUpCounter++;
  }
  while((HSIStatus == 0) && (StartUpCounter != 0xFFFF));

  if ((RCC->CTRL & RCC_CTRL_HSISTBL) != RESET)
  {
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }

  if (HSIStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = (HSI/2) * 24 = 96 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;

#if defined (AT32F415xx)
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT24);
#else
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT24 | RCC_CFG_PLLRANGE_GT72MHZ);
#endif

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
  }
}

#elif defined SYSCLK_FREQ_108MHz_HSI
/**
  * @brief  Sets System clock frequency to 108MHz from HSI and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo108MHSI(void)
{
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSI */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

  /* Wait till HSI is ready and if Time out is reached exit */
  do
  {
    HSIStatus = RCC->CTRL & RCC_CTRL_HSISTBL;
    StartUpCounter++;
  }
  while((HSIStatus == 0) && (StartUpCounter != 0xFFFF));

  if ((RCC->CTRL & RCC_CTRL_HSISTBL) != RESET)
  {
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }

  if (HSIStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_3;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = (HSI/2) * 27 = 108 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;

#if defined (AT32F415xx)
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT27);
#else
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT27 | RCC_CFG_PLLRANGE_GT72MHZ);
#endif

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
  }
}

#elif defined SYSCLK_FREQ_120MHz_HSI
/**
  * @brief  Sets System clock frequency to 120MHz from HSI and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo120MHSI(void)
{
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSI */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

  /* Wait till HSI is ready and if Time out is reached exit */
  do
  {
    HSIStatus = RCC->CTRL & RCC_CTRL_HSISTBL;
    StartUpCounter++;
  }
  while((HSIStatus == 0) && (StartUpCounter != 0xFFFF));

  if ((RCC->CTRL & RCC_CTRL_HSISTBL) != RESET)
  {
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }

  if (HSIStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_3;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = (HSI/2) * 30 = 120 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;

#if defined (AT32F415xx)
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT30);
#else
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT30 | RCC_CFG_PLLRANGE_GT72MHZ);
#endif

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx) || defined (AT32F415xx)
    RCC_StepModeCmd(ENABLE);
#endif
    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx) || defined (AT32F415xx)
    RCC_StepModeCmd(DISABLE);
#endif
  }
}

#elif defined SYSCLK_FREQ_144MHz_HSI
/**
  * @brief  Sets System clock frequency to 144MHz from HSI and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo144MHSI(void)
{
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSI */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

  /* Wait till HSI is ready and if Time out is reached exit */
  do
  {
    HSIStatus = RCC->CTRL & RCC_CTRL_HSISTBL;
    StartUpCounter++;
  }
  while((HSIStatus == 0) && (StartUpCounter != 0xFFFF));

  if ((RCC->CTRL & RCC_CTRL_HSISTBL) != RESET)
  {
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }

  if (HSIStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_4;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = (HSI/2) * 36 = 144 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;

#if defined (AT32F415xx)
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT36);
#else
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT36 | RCC_CFG_PLLRANGE_GT72MHZ);
#endif

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx) || defined (AT32F415xx)
    RCC_StepModeCmd(ENABLE);
#endif
    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx) || defined (AT32F415xx)
    RCC_StepModeCmd(DISABLE);
#endif
  }
}

#elif defined SYSCLK_FREQ_150MHz_HSI
/**
  * @brief  Sets System clock frequency to 150MHz from HSI and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo150MHSI(void)
{
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSI */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

  /* Wait till HSI is ready and if Time out is reached exit */
  do
  {
    HSIStatus = RCC->CTRL & RCC_CTRL_HSISTBL;
    StartUpCounter++;
  }
  while((HSIStatus == 0) && (StartUpCounter != 0xFFFF));

  if ((RCC->CTRL & RCC_CTRL_HSISTBL) != RESET)
  {
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }

  if (HSIStatus == (uint32_t)0x01)
  {
#if defined (AT32F415xx)
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_4;    
#endif
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = ((HSI/2) * 150) / (1 * 4) = 150 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2);
    RCC_PLLconfig2(PLL_FREF_4M, 150, 1, PLL_FR_4);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx) || defined (AT32F415xx)
    RCC_StepModeCmd(ENABLE);
#endif
    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx) || defined (AT32F415xx)
    RCC_StepModeCmd(DISABLE);
#endif
  }
}

#elif defined SYSCLK_FREQ_168MHz_HSI
/**
  * @brief  Sets System clock frequency to 168MHz from HSI and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo168MHSI(void)
{
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSI */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

  /* Wait till HSI is ready and if Time out is reached exit */
  do
  {
    HSIStatus = RCC->CTRL & RCC_CTRL_HSISTBL;
    StartUpCounter++;
  }
  while((HSIStatus == 0) && (StartUpCounter != 0xFFFF));

  if ((RCC->CTRL & RCC_CTRL_HSISTBL) != RESET)
  {
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }

  if (HSIStatus == (uint32_t)0x01)
  {
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = (HSI/2) * 42 = 168 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT42 | RCC_CFG_PLLRANGE_GT72MHZ);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(ENABLE);
#endif
    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(DISABLE);
#endif
  }
}
#elif defined SYSCLK_FREQ_176MHz_HSI
/**
  * @brief  Sets System clock frequency to 176MHz from HSI and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo176MHSI(void)
{
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSI */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

  /* Wait till HSI is ready and if Time out is reached exit */
  do
  {
    HSIStatus = RCC->CTRL & RCC_CTRL_HSISTBL;
    StartUpCounter++;
  }
  while((HSIStatus == 0) && (StartUpCounter != 0xFFFF));

  if ((RCC->CTRL & RCC_CTRL_HSISTBL) != RESET)
  {
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }

  if (HSIStatus == (uint32_t)0x01)
  {
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = (HSI/2) * 44 = 176 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT44 | RCC_CFG_PLLRANGE_GT72MHZ);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(ENABLE);
#endif
    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(DISABLE);
#endif
  }
}
#elif defined SYSCLK_FREQ_192MHz_HSI
/**
  * @brief  Sets System clock frequency to 192MHz from HSI and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo192MHSI(void)
{
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSI */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

  /* Wait till HSI is ready and if Time out is reached exit */
  do
  {
    HSIStatus = RCC->CTRL & RCC_CTRL_HSISTBL;
    StartUpCounter++;
  }
  while((HSIStatus == 0) && (StartUpCounter != 0xFFFF));

  if ((RCC->CTRL & RCC_CTRL_HSISTBL) != RESET)
  {
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }

  if (HSIStatus == (uint32_t)0x01)
  {
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = (HSI/2) * 48 = 192 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT48 | RCC_CFG_PLLRANGE_GT72MHZ);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(ENABLE);
#endif
    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(DISABLE);
#endif
  }
}
#elif defined SYSCLK_FREQ_200MHz_HSI
/**
  * @brief  Sets System clock frequency to 200MHz from HSI and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo200MHSI(void)
{
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSI */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

  /* Wait till HSI is ready and if Time out is reached exit */
  do
  {
    HSIStatus = RCC->CTRL & RCC_CTRL_HSISTBL;
    StartUpCounter++;
  }
  while((HSIStatus == 0) && (StartUpCounter != 0xFFFF));

  if ((RCC->CTRL & RCC_CTRL_HSISTBL) != RESET)
  {
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }

  if (HSIStatus == (uint32_t)0x01)
  {
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = (HSI/2) * 50 = 200 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT50 | RCC_CFG_PLLRANGE_GT72MHZ);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(ENABLE);
#endif
    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(DISABLE);
#endif
  }
}

#elif defined SYSCLK_FREQ_224MHz_HSI
/**
  * @brief  Sets System clock frequency to 224MHz from HSI and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo224MHSI(void)
{
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSI */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

  /* Wait till HSI is ready and if Time out is reached exit */
  do
  {
    HSIStatus = RCC->CTRL & RCC_CTRL_HSISTBL;
    StartUpCounter++;
  }
  while((HSIStatus == 0) && (StartUpCounter != 0xFFFF));

  if ((RCC->CTRL & RCC_CTRL_HSISTBL) != RESET)
  {
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }

  if (HSIStatus == (uint32_t)0x01)
  {
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = (HSI/2) * 56 = 224 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT56 | RCC_CFG_PLLRANGE_GT72MHZ);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(ENABLE);
#endif
    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(DISABLE);
#endif
  }
}

#elif defined SYSCLK_FREQ_240MHz_HSI
/**
  * @brief  Sets System clock frequency to 240MHz from HSI and configure HCLK, PCLK2
  *         and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockTo240MHSI(void)
{
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
  /* Enable HSI */
  RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

  /* Wait till HSI is ready and if Time out is reached exit */
  do
  {
    HSIStatus = RCC->CTRL & RCC_CTRL_HSISTBL;
    StartUpCounter++;
  }
  while((HSIStatus == 0) && (StartUpCounter != 0xFFFF));

  if ((RCC->CTRL & RCC_CTRL_HSISTBL) != RESET)
  {
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }

  if (HSIStatus == (uint32_t)0x01)
  {
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPSC_DIV1;

    /* PCLK2 = HCLK/2 */
    RCC->CFG &= 0xFFFFC7FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PSC_DIV2;

    /* PCLK1 = HCLK/2 */
    RCC->CFG &= 0xFFFFF8FF;
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PSC_DIV2;

    /*  PLL configuration: PLLCLK = (HSI/2) * 60 = 240 MHz */
    RCC->CFG &= RCC_CFG_PLLCFG_MASK;
    RCC->CFG |= (uint32_t)(RCC_CFG_PLLRC_HSI_DIV2 | RCC_CFG_PLLMULT60 | RCC_CFG_PLLRANGE_GT72MHZ);

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while((RCC->CTRL & RCC_CTRL_PLLSTBL) == 0)
    {
    }
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(ENABLE);
#endif
    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t)~(RCC_CFG_SYSCLKSEL));
    RCC->CFG |= (uint32_t)RCC_CFG_SYSCLKSEL_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SYSCLKSTS) != RCC_CFG_SYSCLKSTS_PLL)
    {
    }
#ifdef AT32F403xx
    WaitHseStbl(PLL_STABLE_DELAY);
#endif
#if defined (AT32F413xx) || defined (AT32F403Axx)|| \
    defined (AT32F407xx)
    RCC_StepModeCmd(DISABLE);
#endif
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

/******************* (C) COPYRIGHT 2018 ArteryTek *****END OF FILE****/ 
