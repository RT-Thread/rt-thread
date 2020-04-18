/**
 **************************************************************************
 * File Name    : at32f4xx_rcc.c
 * Description  : at32f4xx RCC source file
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_rcc.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup RCC
  * @brief RCC driver modules
  * @{
  */

/** @defgroup RCC_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup RCC_Private_Defines
  * @{
  */

/* ------------ RCC registers bit address in the alias region ----------- */
#define RCC_OFFSET                  (RCC_BASE - PERIPH_BASE)

/* --- CTRL Register ---*/

/* Alias word address of HSIEN bit */
#define CTRL_OFFSET                 (RCC_OFFSET + 0x00)
#define HSIEN_BitPos                0x00
#define CTRL_HSIEN_BB               (PERIPH_BB_BASE + (CTRL_OFFSET * 32) + (HSIEN_BitPos * 4))

/* Alias word address of PLLEN bit */
#define PLLEN_BitPos                0x18
#define CTRL_PLLEN_BB               (PERIPH_BB_BASE + (CTRL_OFFSET * 32) + (PLLEN_BitPos * 4))

/* Alias word address of HSECFDEN bit */
#define HSECFDEN_BitPos             0x13
#define CTRL_HSECFDEN_BB            (PERIPH_BB_BASE + (CTRL_OFFSET * 32) + (HSECFDEN_BitPos * 4))

#define HSICAL_BitPos               (8)
#if defined (AT32F403xx)
#define HSITWK_BitPos               (3)
#else
#define HSITWK_BitPos               (2)
#endif

/* --- CFG Register ---*/

/* Alias word address of USBPSC bit */
#define CFG_OFFSET                  (RCC_OFFSET + 0x04)

/* --- BDC Register ---*/
#if defined (AT32F415xx)
/* Alias word address of ERTCEN bit */
#define BDC_OFFSET                  (RCC_OFFSET + 0x20)
#define ERTCEN_BitPos                0x0F
#define BDC_ERTCEN_BB                (PERIPH_BB_BASE + (BDC_OFFSET * 32) + (ERTCEN_BitPos * 4))
#else
/* Alias word address of RTCEN bit */
#define BDC_OFFSET                  (RCC_OFFSET + 0x20)
#define RTCEN_BitPos                0x0F
#define BDC_RTCEN_BB                (PERIPH_BB_BASE + (BDC_OFFSET * 32) + (RTCEN_BitPos * 4))
#endif

/* Alias word address of BDRST bit */
#define BDRST_BitPos                0x10
#define BDC_BDRST_BB                (PERIPH_BB_BASE + (BDC_OFFSET * 32) + (BDRST_BitPos * 4))

/* --- CTRLSTS Register ---*/

/* Alias word address of LSIEN bit */
#define CTRLSTS_OFFSET              (RCC_OFFSET + 0x24)
#define LSIEN_BitPos                0x00
#define CTRLSTS_LSIEN_BB            (PERIPH_BB_BASE + (CTRLSTS_OFFSET * 32) + (LSIEN_BitPos * 4))

#define MISC_OFFSET                (RCC_OFFSET + 0x30)

/* ---------------------- RCC registers bit mask ------------------------ */

/* CFG register bit mask */
#define CFG_PLL_Mask                RCC_CFG_PLLCFG_MASK

#define CFG_ADCPSC_Pos              ((uint32_t)14)
#define CFG_ADCPSCBit2_IdxMask      ((uint32_t)4)

#define CFG_ADCPSC_Rst_Mask         ((uint32_t)~RCC_CFG_ADCPSC)
#define CFG_ADCPSC_Set_Mask         ((uint32_t)0x0000C000)
#define CFG_ADCPSCBit2_Set_Mask     ((uint32_t)0x10000000)

/* RCC Flag Mask */
#define FLAG_Mask                   ((uint8_t)0x1F)

/* CLKINT register byte 2 (Bits[15:8]) base address */
#define CLKINT_BYTE2_EN_ADDR        ((uint32_t)0x40021009)

/* CLKINT register byte 3 (Bits[23:16]) base address */
#define CLKINT_BYTE3_CLR_ADDR       ((uint32_t)0x4002100A)

/* BDC register base address */
#define BDC_BYTE0_LSE_ADDR          (PERIPH_BASE + BDC_OFFSET)

/* MISC register base address */
#define MISC_BYTE0_HSICALKEY_ADDR   (PERIPH_BASE + MISC_OFFSET)
#define MISC_HSICAL_ENABLE_KEY      ((uint8_t)0x5A)
#define MISC_HSICAL_DISABLE_KEY     ((uint8_t)0x0)

/**
  * @}
  */

/** @defgroup RCC_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup RCC_Private_Variables
  * @{
  */
static __I uint8_t APBAHBPscTable[8] = {1, 2, 3, 4, 6, 7, 8, 9};
static __I uint8_t ADCPscTable[8] = {2, 4, 6, 8, 2, 12, 8, 16};

/**
  * @}
  */

/** @defgroup RCC_Private_FunctionPrototypes
  * @{
  */
static void RCC_HSEENDelay(uint32_t);

/**
  * @}
  */

/** @defgroup RCC_Private_Functions
  * @{
  */

/**
  * @brief  Resets the RCC clock configuration to the default reset state.
  * @param  None
  * @retval None
  */
void RCC_Reset(void)
{
  /* Set HSIEN bit */
  RCC->CTRL |= (uint32_t)0x00000001;

  /* Reset SYSCLKSEL, AHBPSC, APB1PSC, APB2PSC, ADCPSC and CLKOUT bits */
  RCC->CFG &= (uint32_t)0xE8FF0000;

  /* Reset HSEEN, HSECFDEN and PLLEN bits */
  RCC->CTRL &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYPS bit */
  RCC->CTRL &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLRC, PLLHSEPSC, PLLMUL, PLLFREQRANGE, and USBPSC bits */
  RCC->CFG &= (uint32_t)0x1700FFFF;

  /* Disable all interrupts and clear pending bits  */
  RCC->CLKINT = 0x009F0000;

  /* Reset USB768B, CLKOUT[3], HSICAL_KEY[7:0] */
  RCC->MISC &= 0xFEFEFF00;
}

/**
  * @brief  Configures the External High Speed oscillator (HSE).
  * @note   HSE can not be stopped if it is used directly or through the PLL as system clock.
  * @param  RCC_HSE: specifies the new state of the HSE.
  *   This parameter can be one of the following values:
  *     @arg RCC_HSE_DISABLE: HSE oscillator OFF
  *     @arg RCC_HSE_ENABLE: HSE oscillator ON
  *     @arg RCC_HSE_BYPASS: HSE oscillator bypassed with external clock
  * @retval None
  */
void RCC_HSEConfig(uint32_t RCC_HSE)
{
  /* Check the parameters */
  assert_param(IS_RCC_HSE(RCC_HSE));
  /* Reset HSEEN and HSEBYPS bits before configuring the HSE ------------------*/
  /* Reset HSEEN bit */
  RCC->CTRL &= ~RCC_CTRL_HSEEN;
  /* Reset HSEBYPS bit */
  RCC->CTRL &= ~RCC_CTRL_HSEBYPS;

  /* Configure HSE (RCC_HSE_DISABLE is already covered by the code section above) */
  switch(RCC_HSE)
  {
  case RCC_HSE_ENABLE:
    /* Set HSEEN bit */
    RCC->CTRL |= RCC_CTRL_HSEEN;
    break;

  case RCC_HSE_BYPASS:
    /* Set HSEBYPS and HSEEN bits */
    RCC->CTRL |= RCC_CTRL_HSEBYPS | RCC_CTRL_HSEEN;
    break;

  default:
    break;
  }
}

/**
  * @brief  Waits for HSE start-up.
  * @param  None
  * @retval An ErrorStatus enumuration value:
  * - SUCCESS: HSE oscillator is stable and ready to use
  * - ERROR: HSE oscillator not yet ready
  */
ErrorStatus RCC_WaitForHSEStable(void)
{
  __IO uint32_t StartUpCounter = 0;
  ErrorStatus status = ERROR;
  FlagStatus HSEStatus = RESET;

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC_GetFlagStatus(RCC_FLAG_HSESTBL);
    StartUpCounter++;
  }
  while((StartUpCounter != HSE_STARTUP_TIMEOUT) && (HSEStatus == RESET));
  
  /* Delay for HSE Stable */
  RCC_HSEENDelay(HSE_STABLE_DELAY);

  if (RCC_GetFlagStatus(RCC_FLAG_HSESTBL) != RESET)
  {
    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }

  return (status);
}

/**
  * @brief  Adjusts the Internal High Speed oscillator (HSI) calibration value.
  * @param  HSITweakValue: specifies the calibration trimming value.
  *   This parameter must be a number between 0 and 0x1F.
  * @retval None
  */
void RCC_SetHSITweakValue(uint8_t HSITweakValue)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_RCC_TWEAK_VALUE(HSITweakValue));
  tmpreg = RCC->CTRL;
  /* Clear HSITWK[4:0] bits */
  tmpreg &= ~RCC_CTRL_HSITWK;
  /* Set the HSITWK[4:0] bits according to HSITweakValue value */
  tmpreg |= (uint32_t)HSITweakValue << HSITWK_BitPos;
  /* Store the new value */
  RCC->CTRL = tmpreg;
}


/**
  * @brief  Adjusts the Internal High Speed oscillator (HSI) calibration value.
  * @param  HSICalibValue: specifies the calibration value.
  *   This parameter must be a number between 0 and 0xFF.
  * @retval None
  */
void RCC_SetHSICalibValue(uint8_t HSICalibValue)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_RCC_CALIB_VALUE(HSICalibValue));

  /* Enable write HSICAL */
  *(__IO uint8_t *) MISC_BYTE0_HSICALKEY_ADDR = MISC_HSICAL_ENABLE_KEY;

  /* Get RCC_CTRL and clear HSICAL bits */
  tmpreg = RCC->CTRL & (~RCC_CTRL_HSICAL);
  /* Set the HSICAL[7:0] bits according to HSICalibValue value */
  tmpreg |= (uint32_t)HSICalibValue << HSICAL_BitPos;
  /* Store the new value */
  RCC->CTRL = tmpreg;

  /* Disable write HSICAL */
  *(__IO uint8_t *) MISC_BYTE0_HSICALKEY_ADDR = MISC_HSICAL_DISABLE_KEY;
}


/**
  * @brief  Enables or disables the Internal High Speed oscillator (HSI).
  * @note   HSI can not be stopped if it is used directly or through the PLL as system clock.
  * @param  NewState: new state of the HSI. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_HSICmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CTRL_HSIEN_BB = (uint32_t)NewState;
}

/**
  * @brief  Configures the PLL clock source and multiplication factor.
  * @note   This function must be used only when the PLL is disabled.
  * @param  RCC_PLLRefClk: specifies the PLL entry clock source.
  *   This parameter can be one of the following values:
  *     @arg RCC_PLLRefClk_HSI_Div2: HSI oscillator clock divided by 2 selected as PLL clock entry
  *     @arg RCC_PLLRefClk_HSE_Div1: HSE oscillator clock selected as PLL clock entry
  *     @arg RCC_PLLRefClk_HSE_Div2: HSE oscillator clock divided by 2 selected as PLL clock entry
  * @param  RCC_PLLMult: specifies the PLL multiplication factor.
  *   			This parameter can be RCC_PLLMult_x where x:[2,64]
  * @param  RCC_PLLRange: specifies the PLL frequency range
  *     @arg RCC_Range_LessEqual_72Mhz: When PLL output is less than or equal to 72 MHz.
  *     @arg RCC_Range_GreatThan_72Mhz: When PLL output is greater than 72 MHz.
  *
  * @retval None
  */
void RCC_PLLConfig(uint32_t RCC_PLLRefClk, uint32_t RCC_PLLMult, uint32_t RCC_PLLRange)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RCC_PLL_CFG(RCC_PLLRefClk));
  assert_param(IS_RCC_PLL_MULT(RCC_PLLMult));
  assert_param(IS_RCC_PLL_RANGE(RCC_PLLRange));

  tmpreg = RCC->CFG;
  /* Clear PLLRC, PLLHSEPSC and PLLMULT[5:0] bits */
  tmpreg &= CFG_PLL_Mask;
  /* Set the PLL configuration bits */
  tmpreg |= RCC_PLLRefClk | RCC_PLLMult | RCC_PLLRange;
  /* Store the new value */
  RCC->CFG = tmpreg;
}

/**
  * @brief  Enables or disables the PLL.
  * @note   The PLL can not be disabled if it is used as system clock.
  * @param  NewState: new state of the PLL. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_PLLCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) CTRL_PLLEN_BB = (uint32_t)NewState;
}

/**
  * @brief  Configures the system clock (SYSCLK).
  * @param  RCC_SYSCLKSelect: specifies the clock source used as system clock.
  *   This parameter can be one of the following values:
  *     @arg RCC_SYSCLKSelction_HSI: HSI selected as system clock
  *     @arg RCC_SYSCLKSelction_HSE: HSE selected as system clock
  *     @arg RCC_SYSCLKSelction_PLL: PLL selected as system clock
  * @retval None
  */
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSelect)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_RCC_SYSCLK_CFG(RCC_SYSCLKSelect));
  tmpreg = RCC->CFG;
  /* Clear SYSCLKSEL[1:0] bits */
  tmpreg &= ~RCC_CFG_SYSCLKSEL;
  /* Set SYSCLKSEL[1:0] bits according to RCC_SYSCLKSelect value */
  tmpreg |= RCC_SYSCLKSelect;
  /* Store the new value */
  RCC->CFG = tmpreg;
}

/**
  * @brief  Returns the clock source used as system clock.
  * @param  None
  * @retval The clock source used as system clock. The returned value can
  *   be one of the following:
  *     - 0x00: HSI used as system clock
  *     - 0x04: HSE used as system clock
  *     - 0x08: PLL used as system clock
  */
uint8_t RCC_GetSYSCLKSelction(void)
{
  return ((uint8_t)(RCC->CFG & RCC_CFG_SYSCLKSTS));
}

/**
  * @brief  Configures the AHB clock (HCLK).
  * @param  RCC_SYSCLK_Div: defines the AHB clock divider. This clock is derived from
  *   the system clock (SYSCLK).
  *   This parameter can be one of the following values:
  *     @arg RCC_SYSCLK_Div1: AHB clock = SYSCLK
  *     @arg RCC_SYSCLK_Div2: AHB clock = SYSCLK/2
  *     @arg RCC_SYSCLK_Div4: AHB clock = SYSCLK/4
  *     @arg RCC_SYSCLK_Div8: AHB clock = SYSCLK/8
  *     @arg RCC_SYSCLK_Div16: AHB clock = SYSCLK/16
  *     @arg RCC_SYSCLK_Div64: AHB clock = SYSCLK/64
  *     @arg RCC_SYSCLK_Div128: AHB clock = SYSCLK/128
  *     @arg RCC_SYSCLK_Div256: AHB clock = SYSCLK/256
  *     @arg RCC_SYSCLK_Div512: AHB clock = SYSCLK/512
  * @retval None
  */
void RCC_AHBCLKConfig(uint32_t RCC_SYSCLK_Div)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_RCC_AHBCLK(RCC_SYSCLK_Div));
  tmpreg = RCC->CFG;
  /* Clear AHBPSC[3:0] bits */
  tmpreg &= ~RCC_CFG_AHBPSC;
  /* Set AHBPSC[3:0] bits according to RCC_SYSCLK_Div value */
  tmpreg |= RCC_SYSCLK_Div;
  /* Store the new value */
  RCC->CFG = tmpreg;
}

/**
  * @brief  Configures the Low Speed APB clock (PCLK1).
  * @param  RCC_HCLK_Div: defines the APB1 clock divider. This clock is derived from
  *   the AHB clock (HCLK).
  *   This parameter can be one of the following values:
  *     @arg RCC_AHBCLK_Div1: APB1 clock = HCLK
  *     @arg RCC_AHBCLK_Div2: APB1 clock = HCLK/2
  *     @arg RCC_AHBCLK_Div4: APB1 clock = HCLK/4
  *     @arg RCC_AHBCLK_Div8: APB1 clock = HCLK/8
  *     @arg RCC_AHBCLK_Div16: APB1 clock = HCLK/16
  * @retval None
  */
void RCC_APB1CLKConfig(uint32_t RCC_HCLK_Div)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_RCC_APBCLK(RCC_HCLK_Div));
  tmpreg = RCC->CFG;
  /* Clear APB1PSC[2:0] bits */
  tmpreg &= ~RCC_CFG_APB1PSC;
  /* Set APB1PSC[2:0] bits according to RCC_HCLK_Div value */
  tmpreg |= RCC_HCLK_Div;
  /* Store the new value */
  RCC->CFG = tmpreg;
}

/**
  * @brief  Configures the High Speed APB clock (PCLK2).
  * @param  RCC_HCLK_Div: defines the APB2 clock divider. This clock is derived from
  *   the AHB clock (HCLK).
  *   This parameter can be one of the following values:
  *     @arg RCC_AHBCLK_Div1: APB2 clock = HCLK
  *     @arg RCC_AHBCLK_Div2: APB2 clock = HCLK/2
  *     @arg RCC_AHBCLK_Div4: APB2 clock = HCLK/4
  *     @arg RCC_AHBCLK_Div8: APB2 clock = HCLK/8
  *     @arg RCC_AHBCLK_Div16: APB2 clock = HCLK/16
  * @retval None
  */
void RCC_APB2CLKConfig(uint32_t RCC_HCLK_Div)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_RCC_APBCLK(RCC_HCLK_Div));
  tmpreg = RCC->CFG;
  /* Clear APB2PSC[2:0] bits */
  tmpreg &= ~RCC_CFG_APB2PSC;
  /* Set APB2PSC[2:0] bits according to RCC_HCLK_Div value */
  tmpreg |= RCC_HCLK_Div << 3;
  /* Store the new value */
  RCC->CFG = tmpreg;
}

/**
  * @brief  Enables or disables the specified RCC interrupts.
  * @param  RCC_INT: specifies the RCC interrupt sources to be enabled or disabled.
  *   this parameter can be any combination of the following values.
  *     @arg RCC_INT_LSISTBL: LSI ready interrupt
  *     @arg RCC_INT_LSESTBL: LSE ready interrupt
  *     @arg RCC_INT_HSISTBL: HSI ready interrupt
  *     @arg RCC_INT_HSESTBL: HSE ready interrupt
  *     @arg RCC_INT_PLLSTBL: PLL ready interrupt
  *
  * @param  NewState: new state of the specified RCC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_INTConfig(uint8_t RCC_INT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_INT_EN(RCC_INT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Perform Byte access to RCC_CLKINT bits to enable the selected interrupts */
    *(__IO uint8_t *) CLKINT_BYTE2_EN_ADDR |= RCC_INT;
  }
  else
  {
    /* Perform Byte access to RCC_CLKINT bits to disable the selected interrupts */
    *(__IO uint8_t *) CLKINT_BYTE2_EN_ADDR &= (uint8_t)~RCC_INT;
  }
}

/**
  * @brief  Configures the USB clock (USBCLK).
  * @param  RCC_USBCLKSelect: specifies the USB clock source. This clock is
  *   derived from the PLL output.
  *   This parameter can be one of the following values:
  *     @arg RCC_USBCLKSelection_PLL_Div1_5:  PLL clock divided by 1.5 selected as USB clock source
  *     @arg RCC_USBCLKSelection_PLL_Div1:    PLL clock selected as USB clock source
  *     @arg RCC_USBCLKSelection_PLL_Div2_5:  PLL clock divided by 2.5 selected as USB clock source
  *     @arg RCC_USBCLKSelection_PLL_Div2:    PLL clock divided by 2 selected as USB clock source
  *     @arg RCC_USBCLKSelection_PLL_Div3_5:  PLL clock divided by 3.5 selected as USB clock source
  *     @arg RCC_USBCLKSelection_PLL_Div3:    PLL clock divided by 3 selected as USB clock source
  *     @arg RCC_USBCLKSelection_PLL_Div4:    PLL clock divided by 4 selected as USB clock source
  * @retval None
  */
void RCC_USBCLKConfig(uint32_t RCC_USBCLKSelect)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RCC_USBCLK_CFG(RCC_USBCLKSelect));

  tmpreg = RCC->CFG;
  /* Clear USBPSC[2:0] bits */
  tmpreg &= ~RCC_CFG_USBPSC;
  /* Set USBPSC[2:0] bits according to RCC_USBCLKSelect value */
  tmpreg |= RCC_USBCLKSelect;
  /* Store the new value */
  RCC->CFG = tmpreg;
}

/**
  * @brief  Configures the ADC clock (ADCCLK).
  * @param  RCC_PCLK2_Div: defines the ADC clock divider. This clock is derived from
  *   the APB2 clock (PCLK2).
  *   This parameter can be one of the following values:
  *     @arg RCC_APB2CLK_Div2:  ADC clock = PCLK2/2
  *     @arg RCC_APB2CLK_Div4:  ADC clock = PCLK2/4
  *     @arg RCC_APB2CLK_Div6:  ADC clock = PCLK2/6
  *     @arg RCC_APB2CLK_Div8:  ADC clock = PCLK2/8
  *     @arg RCC_APB2CLK_Div12: ADC clock = PCLK2/12
  *     @arg RCC_APB2CLK_Div16: ADC clock = PCLK2/16
  * @retval None
  */
void RCC_ADCCLKConfig(uint32_t RCC_PCLK2_Div)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_RCC_ADCCLK(RCC_PCLK2_Div));
  tmpreg = RCC->CFG;
  /* Clear ADCPSC[2:0] bits */
  tmpreg &= CFG_ADCPSC_Rst_Mask;
  /* Set ADCPSC[2:0] bits according to RCC_PCLK2_Div value */
  tmpreg |= RCC_PCLK2_Div;
  /* Store the new value */
  RCC->CFG = tmpreg;
}

/**
  * @brief  Configures the External Low Speed oscillator (LSE).
  * @param  RCC_LSE: specifies the new state of the LSE.
  *   This parameter can be one of the following values:
  *     @arg RCC_LSE_DISABLE: LSE oscillator OFF
  *     @arg RCC_LSE_ENABLE:  LSE oscillator ON
  *     @arg RCC_LSE_BYPASS:  LSE oscillator bypassed with external clock
  * @retval None  
  */
void RCC_LSEConfig(uint8_t RCC_LSE)
{
  /* Check the parameters */
  assert_param(IS_RCC_LSE(RCC_LSE));
  /* Reset LSEEN and LSEBYPS bits before configuring the LSE ------------------*/
  /* Reset LSEEN bit */
  *(__IO uint8_t *) BDC_BYTE0_LSE_ADDR = RCC_LSE_DISABLE;
  /* Reset LSEBYPS bit */
  *(__IO uint8_t *) BDC_BYTE0_LSE_ADDR = RCC_LSE_DISABLE;

  /* Configure LSE (RCC_LSE_DISABLE is already covered by the code section above) */
  switch(RCC_LSE)
  {
  case RCC_LSE_ENABLE:
    /* Set LSEEN bit */
    *(__IO uint8_t *) BDC_BYTE0_LSE_ADDR = RCC_LSE_ENABLE;
    break;

  case RCC_LSE_BYPASS:
    /* Set LSEBYPS and LSEEN bits */
    *(__IO uint8_t *) BDC_BYTE0_LSE_ADDR = RCC_LSE_BYPASS | RCC_LSE_ENABLE;
    break;

  default:
    break;
  }
}

/**
  * @brief  Enables or disables the Internal Low Speed oscillator (LSI).
  * @note   LSI can not be disabled if the IWDG is running.
  * @param  NewState: new state of the LSI. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_LSICmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CTRLSTS_LSIEN_BB = (uint32_t)NewState;
}

#if defined (AT32F415xx)
/**
  * @brief  Configures the ERTC clock (ERTCCLK).
  * @note   Once the ERTC clock is selected it can't be changed unless the Backup domain is reset.
  * @param  RCC_ERTCCLKSelect: specifies the ERTC clock source.
  *   This parameter can be one of the following values:
  *     @arg RCC_ERTCCLKSelection_LSE: LSE selected as ERTC clock
  *     @arg RCC_ERTCCLKSelection_LSI: LSI selected as ERTC clock
  *     @arg RCC_ERTCCLKSelection_HSE_Div128: HSE clock divided by 128 selected as ERTC clock
  * @retval None
  */
void RCC_ERTCCLKConfig(uint32_t RCC_ERTCCLKSelect)
{
  /* Check the parameters */
  assert_param(IS_RCC_ERTCCLK_SEL(RCC_ERTCCLKSelect));
  /* Select the RTC clock source */
  RCC->BDC |= RCC_ERTCCLKSelect;
}
#else
/**
  * @brief  Configures the RTC clock (RTCCLK).
  * @note   Once the RTC clock is selected it can't be changed unless the Backup domain is reset.
  * @param  RCC_RTCCLKSelect: specifies the RTC clock source.
  *   This parameter can be one of the following values:
  *     @arg RCC_RTCCLKSelection_LSE: LSE selected as RTC clock
  *     @arg RCC_RTCCLKSelection_LSI: LSI selected as RTC clock
  *     @arg RCC_RTCCLKSelection_HSE_Div128: HSE clock divided by 128 selected as RTC clock
  * @retval None
  */
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSelect)
{
  /* Check the parameters */
  assert_param(IS_RCC_RTCCLK_SEL(RCC_RTCCLKSelect));
  /* Select the RTC clock source */
  RCC->BDC |= RCC_RTCCLKSelect;
}
#endif

#if defined (AT32F415xx)
/**
  * @brief  Enables or disables the ERTC clock.
  * @note   This function must be used only after the ERTC clock was selected using the RCC_ERTCCLKConfig function.
  * @param  NewState: new state of the ERTC clock. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ERTCCLKCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) BDC_ERTCEN_BB = (uint32_t)NewState;
}
#else
/**
  * @brief  Enables or disables the RTC clock.
  * @note   This function must be used only after the RTC clock was selected using the RCC_RTCCLKConfig function.
  * @param  NewState: new state of the RTC clock. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_RTCCLKCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) BDC_RTCEN_BB = (uint32_t)NewState;
}
#endif
/**
  * @brief  Returns the frequencies of different on chip clocks.
  * @param  RCC_Clocks: pointer to a RCC_ClockType structure which will hold
  *         the clocks frequencies.
  * @note   The result of this function could be not correct when using
  *         fractional value for HSE crystal.
  * @retval None
  */
void RCC_GetClocksFreq(RCC_ClockType* RCC_Clocks)
{
#if defined (AT32F415xx)
  uint32_t pllcfgen = 0, pllfref = 0, pllns = 0, pllms = 0, pllfr = 0;
  uint32_t retfref = 0, retfr = 0; 
#endif
  uint32_t tmp = 0, pllmult = 0, pllrefclk = 0, psc = 0;

  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFG & RCC_CFG_SYSCLKSTS;

  switch (tmp)
  {
  case 0x00:  /* HSI used as system clock */
    RCC_Clocks->SYSCLK_Freq = HSI_VALUE;
    break;

  case 0x04:  /* HSE used as system clock */
    RCC_Clocks->SYSCLK_Freq = HSE_VALUE;
    break;

  case 0x08:  /* PLL used as system clock */
#if defined (AT32F415xx)
    /* Get_ClocksFreq for PLLconfig2 */
    pllcfgen = BIT_READ(RCC->PLL, PLL_CFGEN_MASK);

    if(pllcfgen == PLL_CFGEN_ENABLE)
    {
      pllfref = BIT_READ(RCC->PLL, PLL_FREF_MASK);
      pllns = BIT_READ(RCC->PLL, PLL_NS_MASK);
      pllms = BIT_READ(RCC->PLL, PLL_MS_MASK);
      pllfr = BIT_READ(RCC->PLL, PLL_FR_MASK);

      RCC_FREF_VALUE(pllfref, retfref);
      RCC_FR_VALUE(pllfr, retfr);

      RCC_Clocks->SYSCLK_Freq = (retfref * (pllns >> PLL_NS_POS)) / \
      ((pllms >> PLL_MS_POS) * retfr) * 1000000;
    }else
#endif
    {
      /* Get PLL clock source and multiplication factor ----------------------*/
      pllmult = BIT_READ(RCC->CFG, RCC_CFG_PLLMULT);
      pllrefclk = RCC->CFG & RCC_CFG_PLLRC;
      pllmult = RCC_GET_PLLMULT(pllmult);
  
      if (pllrefclk == 0x00)
      {
        /* HSI oscillator clock divided by 2 selected as PLL clock entry */
        RCC_Clocks->SYSCLK_Freq = (HSI_VALUE >> 1) * pllmult;
      }
      else
      {
        /* HSE selected as PLL clock entry */
        if ((RCC->CFG & RCC_CFG_PLLHSEPSC) != (uint32_t)RESET)
        {
          /* HSE oscillator clock divided by 2 */
          RCC_Clocks->SYSCLK_Freq = (HSE_VALUE >> 1) * pllmult;
        }
        else
        {
          RCC_Clocks->SYSCLK_Freq = HSE_VALUE * pllmult;
        }
      }
    }
#if !defined (AT32F415xx)
    if (((RCC->CFG & RCC_CFG_PLLRANGE) == 0) && (RCC_Clocks->SYSCLK_Freq > RCC_PLL_RANGE))
    {
      /* Not setup PLLRANGE, fixed in 72 MHz */
      RCC_Clocks->SYSCLK_Freq = RCC_PLL_RANGE;
    }
#endif
    break;

  default:
    RCC_Clocks->SYSCLK_Freq = HSI_VALUE;
    break;
  }

  /* Compute HCLK, PCLK1, PCLK2 and ADCCLK clocks frequencies ----------------*/
  /* Get HCLK prescaler */
  tmp = (RCC->CFG & (RCC_CFG_AHBPSC ^ RCC_CFG_AHBPSC_3)) >> 4;
  psc = (RCC->CFG & RCC_CFG_AHBPSC_3) ? APBAHBPscTable[tmp] : 0;

  /* HCLK clock frequency */
  RCC_Clocks->AHBCLK_Freq = RCC_Clocks->SYSCLK_Freq >> psc;
  /* Get PCLK1 prescaler */
  tmp = (RCC->CFG & (RCC_CFG_APB1PSC ^ RCC_CFG_APB1PSC_2)) >> 8;
  psc = (RCC->CFG & RCC_CFG_APB1PSC_2) ? APBAHBPscTable[tmp] : 0;
  /* PCLK1 clock frequency */
  RCC_Clocks->APB1CLK_Freq = RCC_Clocks->AHBCLK_Freq >> psc;
  /* Get PCLK2 prescaler */
  tmp = (RCC->CFG & (RCC_CFG_APB2PSC ^ RCC_CFG_APB2PSC_2)) >> 11;
  psc = (RCC->CFG & RCC_CFG_APB2PSC_2) ? APBAHBPscTable[tmp] : 0;
  /* PCLK2 clock frequency */
  RCC_Clocks->APB2CLK_Freq = RCC_Clocks->AHBCLK_Freq >> psc;

  /* Get ADCCLK prescaler */
  tmp = (RCC->CFG & CFG_ADCPSC_Set_Mask) >> CFG_ADCPSC_Pos;

  if (RCC->CFG & CFG_ADCPSCBit2_Set_Mask)
  {
    tmp |= CFG_ADCPSCBit2_IdxMask;
  }

  psc = ADCPscTable[tmp];
  /* ADCCLK clock frequency */
  RCC_Clocks->ADCCLK_Freq = RCC_Clocks->APB2CLK_Freq / psc;
}

/**
  * @brief  Enables or disables the AHB peripheral clock.
  * @param  RCC_AHBPeriph: specifies the AHB peripheral to gates its clock.
  *   This parameter can be any combination of the
  *   following values:
  *     @arg RCC_AHBPERIPH_DMA1
  *     @arg RCC_AHBPERIPH_DMA2
  *     @arg RCC_AHBPERIPH_SRAM
  *     @arg RCC_AHBPERIPH_FLASH
  *     @arg RCC_AHBPERIPH_CRC
  *     @arg RCC_AHBPERIPH_XMC
  *     @arg RCC_AHBPERIPH_SDIO1
  *     @arg RCC_AHBPERIPH_SDIO2
  *
  * @note SRAM and FLASH clock can be disabled only during sleep mode.
  * @param  NewState: new state of the specified peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->AHBEN |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBEN &= ~RCC_AHBPeriph;
  }
}

/**
  * @brief  Enables or disables the High Speed APB (APB2) peripheral clock.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to gates its clock.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_APB2PERIPH_AFIO,   RCC_APB2PERIPH_GPIOA,   RCC_APB2PERIPH_GPIOB,
  *          RCC_APB2PERIPH_GPIOC,  RCC_APB2PERIPH_GPIOD,   RCC_APB2PERIPH_GPIOE,
  *          RCC_APB2PERIPH_GPIOF,  RCC_APB2PERIPH_GPIOG,   RCC_APB2PERIPH_ADC1,
  *          RCC_APB2PERIPH_ADC2,   RCC_APB2PERIPH_TMR1,    RCC_APB2PERIPH_SPI1,
  *          RCC_APB2PERIPH_TMR8,   RCC_APB2PERIPH_USART1,  RCC_APB2PERIPH_ADC3,
  *          RCC_APB2PERIPH_TMR15,  RCC_APB2PERIPH_TMR9,    RCC_APB2PERIPH_TMR10,
  *          RCC_APB2PERIPH_TMR11
  * @param  NewState: new state of the specified peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB2EN |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2EN &= ~RCC_APB2Periph;
  }
}

/**
  * @brief  Enables or disables the Low Speed APB (APB1) peripheral clock.
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to gates its clock.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_APB1PERIPH_TMR2,   RCC_APB1PERIPH_TMR3,   RCC_APB1PERIPH_TMR4,
  *          RCC_APB1PERIPH_TMR5,   RCC_APB1PERIPH_TMR6,   RCC_APB1PERIPH_TMR7,
  *          RCC_APB1PERIPH_WWDG,   RCC_APB1PERIPH_SPI2,   RCC_APB1PERIPH_SPI3,
  *          RCC_APB1PERIPH_SPI4,   RCC_APB1PERIPH_USART2, RCC_APB1PERIPH_USART3,
  *          RCC_APB1Periph_USART4, RCC_APB1Periph_USART5, RCC_APB1PERIPH_I2C1,
  *          RCC_APB1PERIPH_I2C2,   RCC_APB1PERIPH_I2C3,   RCC_APB1PERIPH_USB,
  *          RCC_APB1PERIPH_CAN1,   RCC_APB1PERIPH_BKP,    RCC_APB1PERIPH_PWR,
  *          RCC_APB1PERIPH_DAC,    RCC_APB1PERIPH_TMR12,  RCC_APB1PERIPH_TMR13,
  *          RCC_APB1PERIPH_TMR14
  * @param  NewState: new state of the specified peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB1EN |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1EN &= ~RCC_APB1Periph;
  }
}

#if defined (AT32F403Axx) || defined (AT32F407xx)
/**
  * @brief  Forces or releases High Speed AHB Bus reset.
  * @param  RCC_AHBPeriph: specifies the AHB peripheral to reset.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_AHBPERIPH_ETHMAC
  * @param  NewState: new state of the specified peripheral reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->AHBRST |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBRST &= ~RCC_AHBPeriph;
  }
}
#endif

/**
  * @brief  Forces or releases High Speed APB (APB2) peripheral reset.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to reset.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_APB2PERIPH_AFIO,  RCC_APB2PERIPH_GPIOA,  RCC_APB2PERIPH_GPIOB,
  *          RCC_APB2PERIPH_GPIOC, RCC_APB2PERIPH_GPIOD,  RCC_APB2PERIPH_GPIOE,
  *          RCC_APB2PERIPH_GPIOF, RCC_APB2PERIPH_GPIOG,  RCC_APB2PERIPH_ADC1,
  *          RCC_APB2PERIPH_ADC2,  RCC_APB2PERIPH_TMR1,   RCC_APB2PERIPH_SPI1,
  *          RCC_APB2PERIPH_TMR8,  RCC_APB2PERIPH_USART1, RCC_APB2PERIPH_ADC3,
  *          RCC_APB2PERIPH_TMR15, RCC_APB2PERIPH_TMR9,   RCC_APB2PERIPH_TMR10,
  *          RCC_APB2PERIPH_TMR11
  * @param  NewState: new state of the specified peripheral reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB2RST |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2RST &= ~RCC_APB2Periph;
  }
}

/**
  * @brief  Forces or releases Low Speed APB (APB1) peripheral reset.
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to reset.
  *   This parameter can be any combination of the following values:
  *     @arg RCC_APB1PERIPH_TMR2,   RCC_APB1PERIPH_TMR3,   RCC_APB1PERIPH_TMR4,
  *          RCC_APB1PERIPH_TMR5,   RCC_APB1PERIPH_TMR6,   RCC_APB1PERIPH_TMR7,
  *          RCC_APB1PERIPH_WWDG,   RCC_APB1PERIPH_SPI2,   RCC_APB1PERIPH_SPI3,
  *          RCC_APB1PERIPH_SPI4,   RCC_APB1PERIPH_USART2, RCC_APB1PERIPH_USART3,
  *          RCC_APB1Periph_USART4, RCC_APB1Periph_USART5, RCC_APB1PERIPH_I2C1,
  *          RCC_APB1PERIPH_I2C2,   RCC_APB1PERIPH_I2C3,   RCC_APB1PERIPH_USB,
  *          RCC_APB1PERIPH_CAN1,   RCC_APB1PERIPH_BKP,    RCC_APB1PERIPH_PWR,
  *          RCC_APB1PERIPH_DAC,    RCC_APB1PERIPH_TMR12,  RCC_APB1PERIPH_TMR13,
  *          RCC_APB1PERIPH_TMR14
  * @param  NewState: new state of the specified peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB1RST |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1RST &= ~RCC_APB1Periph;
  }
}

/**
  * @brief  Forces or releases the Backup domain reset.
  * @param  NewState: new state of the Backup domain reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_BackupResetCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) BDC_BDRST_BB = (uint32_t)NewState;
}

/**
  * @brief  Enables or disables the Clock Security System.
  * @param  NewState: new state of the Clock Security System..
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_HSEClockFailureDetectorCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  *(__IO uint32_t *) CTRL_HSECFDEN_BB = (uint32_t)NewState;
}

#if defined (AT32F403xx)
/**
  * @brief  Selects the clock source to output on CLKOUT pin.
  * @param  RCC_CLKOUT: specifies the clock source to output.
  *   This parameter can be one of the following values:
  *     @arg RCC_CLKOUT_NOCLK:    No clock selected
  *     @arg RCC_CLKOUT_SYSCLK:   System clock selected
  *     @arg RCC_CLKOUT_HSI:      HSI oscillator clock selected
  *     @arg RCC_CLKOUT_HSE:      HSE oscillator clock selected
  *     @arg RCC_CLKOUT_PLL_Div2: PLL clock divided by 2 selected
  *     @arg RCC_CLKOUT_PLL_Div4: PLL clock divided by 4 selected
  *     @arg RCC_CLKOUT_USB:      USB clock selected
  *     @arg RCC_CLKOUT_ADC:      ADC clock selected
  * @retval None
  */
void RCC_CLKOUTConfig(uint32_t RCC_CLKOUT)
{
    uint32_t tmpreg = 0;

		/* Check the parameters */
		assert_param(IS_RCC_CLKOUT(RCC_CLKOUT));

    if((RCC_CLKOUT >> 28) == 0)
		{
			// Clear CLKOUT[3];
			RCC->MISC &= ~RCC_MISC_CLKOUT_3;

			tmpreg = RCC->CFG;
			/* Clear CLKOUT[2:0] bits */
			tmpreg &= ~RCC_CFG_CLKOUT;
			/* Set CLKOUT[2:0] bits according to RCC_CLKOUT value */
			tmpreg |= RCC_CLKOUT;
			/* Store the new value */
			RCC->CFG = tmpreg;
		}
		else if((RCC_CLKOUT >> 28) == 1)
		{
			// Set CLKOUT[3];
			RCC->MISC &= ~RCC_MISC_CLKOUT_3;
			RCC->MISC |= RCC_MISC_CLKOUT_3;

			tmpreg = RCC->CFG;
			/* Clear CLKOUT[2:0] bits */
			tmpreg &= ~RCC_CFG_CLKOUT;
			/* Set CLKOUT[2:0] bits according to RCC_CLKOUT value */
			tmpreg |= (RCC_CLKOUT & 0xFFFFFFF);
			/* Store the new value */
			RCC->CFG = tmpreg;
		}
}
#else
/**
  * @brief  Selects the clock source to output on CLKOUT pin.
  * @param  RCC_CLKOUT: specifies the clock source to output.
  *   This parameter can be one of the following values:
  *     @arg RCC_CLKOUT_NOCLK:    No clock selected
  *     @arg RCC_CLKOUT_SYSCLK:   System clock selected
  *     @arg RCC_CLKOUT_HSI:      HSI oscillator clock selected
  *     @arg RCC_CLKOUT_HSE:      HSE oscillator clock selected
  *     @arg RCC_CLKOUT_PLL_Div2: PLL clock divided by 2 selected
  *     @arg RCC_CLKOUT_PLL_Div4: PLL clock divided by 4 selected
  *     @arg RCC_CLKOUT_USB:      USB clock selected
  *     @arg RCC_CLKOUT_ADC:      ADC clock selected
  * @note Just only at32f413xx & at32f415xx
  *     @arg RCC_CLKOUT_LSI:      LSI clock selected
  *     @arg RCC_CLKOUT_LSE:      LSE clock selected
  * @param  RCC_CLKOUTPRE: specifies the clock output prescaler.
  *   This parameter can be one of the following values:
  *     @arg RCC_MCOPRE_1  : division by 1 applied to CLKOUT clock
  *     @arg RCC_MCOPRE_2  : division by 2 applied to CLKOUT clock
  *     @arg RCC_MCOPRE_4  : division by 4 applied to CLKOUT clock
  *     @arg RCC_MCOPRE_8  : division by 8 applied to CLKOUT clock
  *     @arg RCC_MCOPRE_16 : division by 16 applied to CLKOUT clock
  *     @arg RCC_MCOPRE_64 : division by 64 applied to CLKOUT clock
  *     @arg RCC_MCOPRE_128: division by 128 applied to CLKOUT clock
  *     @arg RCC_MCOPRE_256: division by 256 applied to CLKOUT clock
  *     @arg RCC_MCOPRE_512: division by 512 applied to CLKOUT clock
  * @retval None
  */
void RCC_CLKOUTConfig(uint32_t RCC_CLKOUT, uint32_t RCC_CLKOUTPRE)
{
    uint32_t tmpreg = 0;

		/* Check the parameters */
		assert_param(IS_RCC_CLKOUT(RCC_CLKOUT));
    assert_param(IS_RCC_MCO(RCC_CLKOUTPRE));
  
    /* Config MCOPRE */
    RCC->MISC &= ~RCC_MCOPRE_MASK;
    RCC->MISC |= RCC_CLKOUTPRE;

    if((RCC_CLKOUT >> 28) == 0)
		{
			// Clear CLKOUT[3];
			RCC->MISC &= ~RCC_MISC_CLKOUT_3;

			tmpreg = RCC->CFG;
			/* Clear CLKOUT[2:0] bits */
			tmpreg &= ~RCC_CFG_CLKOUT;
			/* Set CLKOUT[2:0] bits according to RCC_CLKOUT value */
			tmpreg |= RCC_CLKOUT;
			/* Store the new value */
			RCC->CFG = tmpreg;
		}
		else if((RCC_CLKOUT >> 28) == 1)
		{
			// Set CLKOUT[3];
			RCC->MISC &= ~RCC_MISC_CLKOUT_3;
			RCC->MISC |= RCC_MISC_CLKOUT_3;

			tmpreg = RCC->CFG;
			/* Clear CLKOUT[2:0] bits */
			tmpreg &= ~RCC_CFG_CLKOUT;
			/* Set CLKOUT[2:0] bits according to RCC_CLKOUT value */
			tmpreg |= (RCC_CLKOUT & 0xFFFFFFF);
			/* Store the new value */
			RCC->CFG = tmpreg;
		}
}
#endif
/**
  * @brief  Checks whether the specified RCC flag is set or not.
  * @param  RCC_Flag: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg RCC_FLAG_HSISTBL:  HSI oscillator clock ready
  *     @arg RCC_FLAG_HSESTBL:  HSE oscillator clock ready
  *     @arg RCC_FLAG_PLLSTBL:  PLL clock ready
  *     @arg RCC_FLAG_LSESTBL:  LSE oscillator clock ready
  *     @arg RCC_FLAG_LSISTBL:  LSI oscillator clock ready
  *     @arg RCC_FLAG_PINRST:   Pin reset
  *     @arg RCC_FLAG_PORST:    POR/PDR reset
  *     @arg RCC_FLAG_SWRST:    Software reset
  *     @arg RCC_FLAG_IWDGRST:  Independent Watchdog reset
  *     @arg RCC_FLAG_WWDGRST:  Window Watchdog reset
  *     @arg RCC_FLAG_LPRST:    Low Power reset
  *
  * @retval The new state of RCC_Flag (SET or RESET).
  */
FlagStatus RCC_GetFlagStatus(uint8_t RCC_Flag)
{
  uint32_t tmp = 0;
  uint32_t statusreg = 0;
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_RCC_FLAG(RCC_Flag));

  /* Get the RCC register index */
  tmp = RCC_Flag >> 5;

  if (tmp == 1)               /* The flag to check is in CTRL register */
  {
    statusreg = RCC->CTRL;
  }
  else if (tmp == 2)          /* The flag to check is in BDC register */
  {
    statusreg = RCC->BDC;
  }
  else                       /* The flag to check is in CTRLSTS register */
  {
    statusreg = RCC->CTRLSTS;
  }

  /* Get the flag position */
  tmp = RCC_Flag & FLAG_Mask;

  if ((statusreg & ((uint32_t)1 << tmp)) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* Return the flag status */
  return bitstatus;
}

/**
  * @brief  Clears the RCC reset flags.
  * @note   The reset flags are: RCC_FLAG_PINRST, RCC_FLAG_PORST, RCC_FLAG_SWRST,
  *   RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST, RCC_FLAG_LPRST
  * @param  None
  * @retval None
  */
void RCC_ClearFlag(void)
{
  /* Set RSTFC bit to clear the reset flags */
  RCC->CTRLSTS |= RCC_CTRLSTS_RSTFC;
}

/**
  * @brief  Checks whether the specified RCC interrupt has occurred or not.
  * @param  RCC_INT: specifies the RCC interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg RCC_INT_LSISTBL: LSI ready interrupt
  *     @arg RCC_INT_LSESTBL: LSE ready interrupt
  *     @arg RCC_INT_HSISTBL: HSI ready interrupt
  *     @arg RCC_INT_HSESTBL: HSE ready interrupt
  *     @arg RCC_INT_PLLSTBL: PLL ready interrupt
  *     @arg RCC_INT_HSECFD:  Clock Security System interrupt
  *
  * @retval The new state of RCC_INT (SET or RESET).
  */
ITStatus RCC_GetINTStatus(uint8_t RCC_INT)
{
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_RCC_INT_STS(RCC_INT));

  /* Check the status of the specified RCC interrupt */
  if ((RCC->CLKINT & RCC_INT) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* Return the RCC_INT status */
  return  bitstatus;
}

/**
  * @brief  Clears the RCC's interrupt pending bits.
  * @param  RCC_INT: specifies the interrupt pending bit to clear.
  *   This parameter can be any combination of the
  *   following values:
  *     @arg RCC_INT_LSISTBL: LSI ready interrupt
  *     @arg RCC_INT_LSESTBL: LSE ready interrupt
  *     @arg RCC_INT_HSISTBL: HSI ready interrupt
  *     @arg RCC_INT_HSESTBL: HSE ready interrupt
  *     @arg RCC_INT_PLLSTBL: PLL ready interrupt
  *
  *     @arg RCC_INT_HSECFD: Clock Security System interrupt
  * @retval None
  */
void RCC_ClearINTPendingBit(uint8_t RCC_INT)
{
  /* Check the parameters */
  assert_param(IS_RCC_INT_CLR(RCC_INT));

  /* Perform Byte access to RCC_CLKINT[23:16] bits to clear the selected interrupt
     pending bits */
  *(__IO uint8_t *) CLKINT_BYTE3_CLR_ADDR = RCC_INT;
}

/**
  * @brief  Delay After HSE Enable,.
  * @param  delay: Number Of Nops.
  * @retval None
  */
static void RCC_HSEENDelay(uint32_t delay)
{
  uint32_t i;

  for(i = 0; i < delay; i++)
    ;
}

#if defined (AT32F413xx) || defined (AT32F415xx) || \
    defined (AT32F403Axx)|| defined (AT32F407xx)
/**
  * @brief  Enables or disables the Auto Step Mode.
  * @note   This function called when sysclk greater than 108Mhz.
  * @param  NewState: new state of the Step Mode. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_StepModeCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if(ENABLE == NewState)
	{
    RCC->MISC2 |= RCC_MISC2_AUTO_STEP_EN;
	}
	else
	{
    RCC->MISC2 &= ~RCC_MISC2_AUTO_STEP_EN;
	}
}

/**
  * @brief  Enables or disables to get USB clock source from HSI 48M directly.
  * @note   Attention: If enable, the hsi clock frequency also has fixed 48M.
  * @param  NewState: new state of the USB clock source. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_HSI2USB48M(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if(ENABLE == NewState)
	{
    RCC->MISC  |= RCC_MISC_HSI_DIV_EN;
    RCC->MISC2 |= RCC_MISC2_HSI_FOR_USB;
	}
	else
	{
    RCC->MISC  &= ~RCC_MISC_HSI_DIV_EN;
    RCC->MISC2 &= ~RCC_MISC2_HSI_FOR_USB;
	}
}
#endif

#if defined (AT32F403Axx)|| defined (AT32F407xx)
/**
  * @brief  HSE Divider configura.
  * @note   This function config HSE divider.
  * @param  HSEDiv: RCC_HSE_DIV_2. HSE divider 2 for pll.
  *                 RCC_HSE_DIV_3. HSE divider 3 for pll.
  *                 RCC_HSE_DIV_4. HSE divider 4 for pll.
  *                 RCC_HSE_DIV_5. HSE divider 5 for pll.
  * @retval None
  */
void RCC_HSEDivConfig(uint32_t HSEDiv)
{
  /* Check the parameters */
  assert_param(IS_RCC_HSEDIV(HSEDiv));

  RCC->MISC2 &= ~RCC_HSE_DIV_MASK;
  RCC->MISC2 |= HSEDiv;
}
#endif

#if defined (AT32F413xx) || defined (AT32F403Axx) || \
    defined (AT32F407xx)
/**
  * @brief  Enables or disables the USB INT remap.
  * @note   Remap the default USB_HP_IRQn & USB_LP_IRQn (19,20) to other IRQns(73, 74).
  * @param  NewState: new state of the USB INT remap. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_USBINTRemap(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if(ENABLE == NewState)
	{
    RCC->INTCTRL |= RCC_INTCTRL_USB_INT_CTRL;
	}
	else
	{
    RCC->INTCTRL &= ~RCC_INTCTRL_USB_INT_CTRL;
	}
}

/**
  * @brief  Enables or disables MCO output to TMR10_CH0.
  * @note   This function can enable MCO inner connect to TMR10_CH0.
  * @param  NewState: new state of the MCO to TMR10_CH0. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_MCO2TMR10(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if(ENABLE == NewState)
	{
    RCC->TEST  |= RCC_TEST_MCO2TMR_EN;
	}
	else
	{
    RCC->TEST  &= ~RCC_TEST_MCO2TMR_EN;
	}
}
#endif

#if defined (AT32F415xx)
/**
  * @brief  Config pll with RCC_PLL.
  * @note   This function can usd RCC_PLL register to config pll, not RCC_CFG_MULT.
  *                        PLL_freq_n_Mhz * PLL_ns
  *         PLL clock = -------------------------------
  *                           PLL_ms * PLL_fr_n
  *         ATTEMTION:
  *                  31 <= PLL_ns <= 500
  *                  1  <= PLL_ms <= 15
  *
  *                       PLL_freq_n_Mhz * PLL_ns
  *         500Mhz <=  ------------------------------ <= 1000Mhz
  *                               PLL_ms
  * @param  PLL_fref: The freqence of PLL source clock.
  *     @arg PLL_FREF_4M :  reference clock 4Mhz
  *     @arg PLL_FREF_6M :  reference clock 6Mhz
  *     @arg PLL_FREF_8M :  reference clock 8Mhz
  *     @arg PLL_FREF_12M:  reference clock 12Mhz
  *     @arg PLL_FREF_16M:  reference clock 16Mhz
  *     @arg PLL_FREF_25M:  reference clock 25Mhz
  * @param  PLL_ns: PLL register ns value.
  * @param  PLL_ms: PLL register ms value.
  * @param  PLL_fr: VCO output divider
  *     @arg PLL_FR_1 :  output divider 1
  *     @arg PLL_FR_2 :  output divider 2
  *     @arg PLL_FR_4 :  output divider 4
  *     @arg PLL_FR_8 :  output divider 8
  *     @arg PLL_FR_16:  output divider 16
  *     @arg PLL_FR_32:  output divider 32
  * @retval None
  */
void RCC_PLLconfig2(uint32_t PLL_fref, uint32_t PLL_ns, uint32_t PLL_ms, uint32_t PLL_fr)
{
	volatile uint32_t result = 0;
  uint32_t pll_reg = 0, ret = 0;

  assert_param(IS_RCC_FR(PLL_fr));
  assert_param(IS_RCC_FREF(PLL_fref));
  assert_param(IS_RCC_NS_VALUE(PLL_ns));
  assert_param(IS_RCC_MS_VALUE(PLL_ms));

  RCC_FREF_VALUE(PLL_fref, ret);

  result = PLL_ns * ret / PLL_ms;

  assert_param(IS_RCC_RESULT_VALUE(result));

  pll_reg = RCC->PLL;

  /* Clear PLL */
  pll_reg &= ~(PLL_FR_MASK | PLL_MS_MASK | PLL_NS_MASK | PLL_FREF_MASK | PLL_CFGEN_MASK);

  /* Config pll */
  pll_reg |= (PLL_fref | (PLL_ns << PLL_NS_POS) | (PLL_ms << PLL_MS_POS) | PLL_fr);

  /* Enable PLLGEN */
  pll_reg |= PLL_CFGEN_ENABLE;

  RCC->PLL = pll_reg;
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


