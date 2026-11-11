/**
  ******************************************************************************
  * @file    lib_clk.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   Clock library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_clk.h"

/**
  * @brief  Initializes the CPU, AHB and APB buses clocks according to the specified 
  *         parameters in the CLK_ClkInitStruct.
  *
  * @note   This function performs the following:
  *             1. If want to switch AHB clock source, enable BGP, enable 6.5M RC,
  *                AHB clock source switch to RCH first.
  *             2. configure clock (except AHB clock source configuration).     - optional
  *             3. configure AHB clock source.                                  - optional
  *             4. HCLK/PCLK divider configuration.                             - optional
  *
  * @note   CLK_InitTypeDef *CLK_ClkInitStruct
  *         [in]CLK_ClkInitStruct->ClockType, can use the '|' operator, the selection of parameters is as follows 
  *                 CLK_TYPE_ALL
  *                 CLK_TYPE_AHBSRC
  *                 CLK_TYPE_PLLL
  *                 CLK_TYPE_PLLH
  *                 CLK_TYPE_XTALH
  *                 CLK_TYPE_RTCCLK
  *                 CLK_TYPE_HCLK
  *                 CLK_TYPE_PCLK
  *
  *                 CLK_TYPE_ALL        All clocks' configurations is valid
  *                 CLK_TYPE_AHBSRC     CLK_ClkInitStruct->AHBSource(AHB Clock source configuration) is valid
  *                         [in]CLK_ClkInitStruct->AHBSource:
  *                                 CLK_AHBSEL_6_5MRC
  *                                 CLK_AHBSEL_6_5MXTAL
  *                                 CLK_AHBSEL_HSPLL
  *                                 CLK_AHBSEL_RTCCLK
  *                                 CLK_AHBSEL_LSPLL
  *                 CLK_TYPE_PLLL       CLK_ClkInitStruct->PLLL(PLLL configuration) is valid
  *                         [in]CLK_ClkInitStruct->PLLL.State:
  *                                 CLK_PLLL_ON            (PLLL.Source/Frequency configuration is valid)
  *                                 CLK_PLLL_OFF           (PLLL.Source/Frequency configuration is not valid)
  *                         [in]CLK_ClkInitStruct->PLLL.Source:
  *                                 CLK_PLLLSRC_RCL
  *                                 CLK_PLLLSRC_XTALL
  *                         [in]CLK_ClkInitStruct->PLLL.Frequency:
  *                                 CLK_PLLL_26_2144MHz
  *                                 CLK_PLLL_13_1072MHz
  *                                 CLK_PLLL_6_5536MHz
  *                                 CLK_PLLL_3_2768MHz
  *                                 CLK_PLLL_1_6384MHz
  *                                 CLK_PLLL_0_8192MHz
  *                                 CLK_PLLL_0_4096MHz
  *                                 CLK_PLLL_0_2048MHz
  *                 CLK_TYPE_PLLH       CLK_ClkInitStruct->PLLH(PLLH configuration) is valid
  *                         [in]CLK_ClkInitStruct->PLLH.State:
  *                                 CLK_PLLH_ON            (PLLH.Source/Frequency configuration is valid)
  *                                 CLK_PLLH_OFF           (PLLH.Source/Frequency configuration is not valid)
  *                         [in]CLK_ClkInitStruct->PLLH.Source:
  *                                 CLK_PLLHSRC_RCH
  *                                 CLK_PLLHSRC_XTALH
  *                         [in]CLK_ClkInitStruct->PLLH.Frequency:
  *                                 CLK_PLLH_13_1072MHz
  *                                 CLK_PLLH_16_384MHz
  *                                 CLK_PLLH_19_6608MHz
  *                                 CLK_PLLH_22_9376MHz
  *                                 CLK_PLLH_26_2144MHz
  *                                 CLK_PLLH_29_4912MHz
  *                                 CLK_PLLH_32_768MHz
  *                                 CLK_PLLH_36_0448MHz
  *                                 CLK_PLLH_39_3216MHz
  *                                 CLK_PLLH_42_5984MHz
  *                                 CLK_PLLH_45_8752MHz
  *                                 CLK_PLLH_49_152MHz
  *                 CLK_TYPE_XTALH      CLK_ClkInitStruct->XTALH(XTALH configuration) is valid
  *                         [in]CLK_ClkInitStruct->XTALH.State:
  *                                 CLK_XTALH_ON
  *                                 CLK_XTALH_OFF
  *                 CLK_TYPE_RTCCLK     CLK_ClkInitStruct->RTCCLK(RTCCLK configuration) is valid
  *                         [in]CLK_ClkInitStruct->RTCCLK.Source:
  *                                 CLK_RTCCLKSRC_XTALL
  *                                 CLK_RTCCLKSRC_RCL
  *                         [in]CLK_ClkInitStruct->RTCCLK.Divider:
  *                                 CLK_RTCCLKDIV_1
  *                                 CLK_RTCCLKDIV_4
  *                 CLK_TYPE_HCLK       CLK_ClkInitStruct->HCLK(AHB Clock(divider) configuration) is valid
  *                         [in]CLK_ClkInitStruct->HCLK.Divider:
  *                                 1 ~ 256
  *                 CLK_TYPE_PCLK       CLK_ClkInitStruct->PCLK(APB Clock(divider) configuration) is valid
  *                         [in]CLK_ClkInitStruct->PCLK.Divider:
  *                                 1 ~ 256
  *         
  * @param  CLK_ClkInitStruct pointer to an CLK_InitTypeDef structure that
  *         contains the configuration information for the clocks.
  *
  * @retval None 
  */
void CLK_ClockConfig(CLK_InitTypeDef *CLK_ClkInitStruct)
{
  uint32_t tmp;
  
  assert_parameters(IS_CLK_TYPE(CLK_ClkInitStruct->ClockType));
  
  if (CLK_ClkInitStruct->ClockType & CLK_TYPE_AHBSRC)
  {
    /* Enable BGP */
    ANA->REG3 &= ~ANA_REG3_BGPPD;
    /* Enable 6.5M RC */
    ANA->REG3 &= ~ANA_REG3_RCHPD;  
   
    /* AHB clock source switch to RCH */
    MISC2->CLKSEL = 0;
  }

  ANA->REGA &= ~BIT6;
  
  /*---------- XTALH configuration ----------*/
  if ((CLK_ClkInitStruct->ClockType) & CLK_TYPE_XTALH)
  {
    assert_parameters(IS_CLK_XTALHSTA(CLK_ClkInitStruct->XTALH.State));
    
    /* XTALH state configure */
    ANA->REG3 &= ~ANA_REG3_XOHPDN;
    ANA->REG3 |= CLK_ClkInitStruct->XTALH.State;
   
  }
 
  /*-------------------- PLLL configuration --------------------*/
  if ((CLK_ClkInitStruct->ClockType) & CLK_TYPE_PLLL)
  {
    assert_parameters(IS_CLK_PLLLSRC(CLK_ClkInitStruct->PLLL.Source));
    assert_parameters(IS_CLK_PLLLSTA(CLK_ClkInitStruct->PLLL.State));
    assert_parameters(IS_CLK_PLLLFRQ(CLK_ClkInitStruct->PLLL.Frequency));
    
    /* PLLL state configure */
    if (CLK_ClkInitStruct->PLLL.State == CLK_PLLL_ON)
    {      
      /* power up PLLL */
      ANA->REG3 |= ANA_REG3_PLLLPDN; 
       
      /* Configure PLLL frequency */
      tmp = ANA->REG9;
      tmp &= ~ANA_REG9_PLLLSEL;
      tmp |= CLK_ClkInitStruct->PLLL.Frequency;
      ANA->REG9 = tmp;
      
      /* Configure PLLL input clock selection */
      tmp = PMU->CONTROL;
      tmp &= ~PMU_CONTROL_PLLL_SEL;
      tmp |= CLK_ClkInitStruct->PLLL.Source;
      PMU->CONTROL = tmp;
    }
    else
    {
      /* power down PLLL */
      ANA->REG3 &= ~ANA_REG3_PLLLPDN; 
    }
  }
  
  /*-------------------- PLLH configuration --------------------*/
  if ((CLK_ClkInitStruct->ClockType) & CLK_TYPE_PLLH)
  {
    assert_parameters(IS_CLK_PLLHSRC(CLK_ClkInitStruct->PLLH.Source));
    assert_parameters(IS_CLK_PLLHSTA(CLK_ClkInitStruct->PLLH.State));
    assert_parameters(IS_CLK_PLLHFRQ(CLK_ClkInitStruct->PLLH.Frequency));
    
    /* PLLH state configure */
    if (CLK_ClkInitStruct->PLLH.State == CLK_PLLH_ON)
    {
      /* Power up PLLH */
      ANA->REG3 |= ANA_REG3_PLLHPDN;

      /* Configure PLLH frequency */
      tmp = ANA->REG9;
      tmp &= ~ANA_REG9_PLLHSEL;
      tmp |= CLK_ClkInitStruct->PLLH.Frequency;
      ANA->REG9 = tmp;
      
      /* Clock input source, XTALH, XOH power on*/
      if (CLK_ClkInitStruct->PLLH.Source == CLK_PLLHSRC_XTALH)
      {
        ANA->REG3 |= ANA_REG3_XOHPDN;
      }
      
      /* Configure PLLH input clock selection */
      tmp = PMU->CONTROL;
      tmp &= ~PMU_CONTROL_PLLH_SEL;
      tmp |= CLK_ClkInitStruct->PLLH.Source;
      PMU->CONTROL = tmp;
    }
    else
    {
      /* Power down PLLH */
      ANA->REG3 &= ~ANA_REG3_PLLHPDN;
    }
  }
  
  /*---------- RTCCLK configuration ----------*/
  if ((CLK_ClkInitStruct->ClockType) & CLK_TYPE_RTCCLK)
  {
    assert_parameters(IS_CLK_RTCSRC(CLK_ClkInitStruct->RTCCLK.Source));
    assert_parameters(IS_CLK_RTCDIV(CLK_ClkInitStruct->RTCCLK.Divider));
    
    /* RTCCLK source(optional) */
    tmp = PMU->CONTROL;
    tmp &= ~PMU_CONTROL_RTCCLK_SEL;
    tmp |= CLK_ClkInitStruct->RTCCLK.Source;
    PMU->CONTROL = tmp;

    /*----- RTCCLK Divider -----*/
    RTC_PrescalerConfig(CLK_ClkInitStruct->RTCCLK.Divider);
  }
  
  /*---------- AHB clock source configuration ----------*/
  if ((CLK_ClkInitStruct->ClockType) & CLK_TYPE_AHBSRC)
  {
    assert_parameters(IS_CLK_AHBSRC(CLK_ClkInitStruct->AHBSource));
    
    /* clock source: 6.5M RC */
    if (CLK_ClkInitStruct->AHBSource == CLK_AHBSEL_6_5MRC)
    {
      /* clock source configuration */
      MISC2->CLKSEL = CLK_ClkInitStruct->AHBSource;
    }
    
    /* clock source: 6_5MXTAL */
    else if (CLK_ClkInitStruct->AHBSource == CLK_AHBSEL_6_5MXTAL)
    {
      /* Power up 6.5M xtal */
      ANA->REG3 |= ANA_REG3_XOHPDN; 
      /* clock source configuration */
      MISC2->CLKSEL = CLK_ClkInitStruct->AHBSource;    
    }
    
    /* clock source: PLLH */
    else if (CLK_ClkInitStruct->AHBSource == CLK_AHBSEL_HSPLL)
    {
      /* Power up PLLH */
      ANA->REG3 |= ANA_REG3_PLLHPDN;
      /* while loop until PLLL is lock */
      while (!(ANA->CMPOUT & ANA_CMPOUT_LOCKH))
      {
      }
      /* clock source configuration */
      MISC2->CLKSEL = CLK_ClkInitStruct->AHBSource;  
    }
    
    /* clock source: PLLL */
    else if (CLK_ClkInitStruct->AHBSource == CLK_AHBSEL_LSPLL)
    {
      /* Power up PLLL */
      ANA->REG3 |= ANA_REG3_PLLLPDN;
      /* while loop until PLLL is lock */
      while (!(ANA->CMPOUT & ANA_CMPOUT_LOCKL))
      {
      }
      /* clock source configuration */
      MISC2->CLKSEL = CLK_ClkInitStruct->AHBSource;  
    }
    /* clock source: RTCCLK */
    else
    {
      /* clock source configuration */
      MISC2->CLKSEL = CLK_ClkInitStruct->AHBSource;
    }
  }

  /*---------- HCLK configuration ----------*/
  if ((CLK_ClkInitStruct->ClockType) & CLK_TYPE_HCLK)
  {
    assert_parameters(IS_CLK_HCLKDIV(CLK_ClkInitStruct->HCLK.Divider));
    
    MISC2->CLKDIVH = (CLK_ClkInitStruct->HCLK.Divider) - 1;
  } 
  
  /*---------- PCLK configuration ----------*/
  if ((CLK_ClkInitStruct->ClockType) & CLK_TYPE_PCLK)
  {
    assert_parameters(IS_CLK_PCLKDIV(CLK_ClkInitStruct->PCLK.Divider));
    
    MISC2->CLKDIVP = (CLK_ClkInitStruct->PCLK.Divider) - 1;
  }   
}

/**
  * @brief  Enables or disables AHB Periphral clock.
  * @param  Periphral: can use the '|' operator
                CLK_AHBPERIPHRAL_DMA     
                CLK_AHBPERIPHRAL_GPIO  
                CLK_AHBPERIPHRAL_LCD
                CLK_AHBPERIPHRAL_CRYPT
            NewState:
                ENABLE
                DISABLE
  * @retval None.
  */
void CLK_AHBPeriphralCmd(uint32_t Periphral, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_CLK_AHBPERIPHRAL(Periphral));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    MISC2->HCLKEN |= Periphral;
  }
  else
  {
    MISC2->HCLKEN &= ~Periphral;
  }
}

/**
  * @brief  Enables or disables APB Periphral clock.
  * @param  Periphral: can use the '|' operator
                 CLK_APBPERIPHRAL_DMA       
                 CLK_APBPERIPHRAL_I2C       
                 CLK_APBPERIPHRAL_SPI1 
                 CLK_APBPERIPHRAL_SPI2
                 CLK_APBPERIPHRAL_UART0     
                 CLK_APBPERIPHRAL_UART1     
                 CLK_APBPERIPHRAL_UART2     
                 CLK_APBPERIPHRAL_UART3     
                 CLK_APBPERIPHRAL_UART4     
                 CLK_APBPERIPHRAL_UART5     
                 CLK_APBPERIPHRAL_ISO78160     
                 CLK_APBPERIPHRAL_ISO78161     
                 CLK_APBPERIPHRAL_TIMER       
                 CLK_APBPERIPHRAL_MISC      
                 CLK_APBPERIPHRAL_MISC2  
                 CLK_APBPERIPHRAL_PMU       
                 CLK_APBPERIPHRAL_RTC       
                 CLK_APBPERIPHRAL_ANA       
                 CLK_APBPERIPHRAL_U32K0     
                 CLK_APBPERIPHRAL_U32K1     
            NewState:
                ENABLE
                DISABLE
  * @retval None.
  */
void CLK_APBPeriphralCmd(uint32_t Periphral, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_CLK_APBPERIPHRAL(Periphral));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    MISC2->PCLKEN |= Periphral;
  }
  else
  {
    MISC2->PCLKEN &= ~Periphral;
  }
}

/**
  * @brief  Returns the HCLK frequency
  * @param  None
  * @retval HCLK frequency
  */
uint32_t CLK_GetHCLKFreq(void)
{
  uint32_t ahb_clksrc;
  uint32_t ahb_div;
  uint32_t pllh_frq;
  uint32_t plll_frq;
  uint32_t rtcclk_div;
  uint32_t hclk; 
  
  /* Get current AHB clock source */
  ahb_clksrc = MISC2->CLKSEL & MISC2_CLKSEL_CLKSEL;
  /* Get AHB clock divider */
  ahb_div = (MISC2->CLKDIVH & MISC2_CLKDIVH_CLKDIVH) + 1;
  
  switch (ahb_clksrc)
  {
  /* AHB Clock source : 6.5M RC */
  case MISC2_CLKSEL_CLKSEL_RCOH:
    hclk = 6553600 / ahb_div;
    break;
  
  /* AHB Clock source : 6.5M XTAL */
  case MISC2_CLKSEL_CLKSEL_XOH:
    hclk = 6553600 / ahb_div;
    break;
   
  /* AHB Clock source : PLLH */
  case MISC2_CLKSEL_CLKSEL_PLLH:
    /* Get PLLH Frequency */
    pllh_frq = ANA->REG9 & ANA_REG9_PLLHSEL;
    switch (pllh_frq)
    {
    case ANA_REG9_PLLHSEL_X2:
      hclk = 13107200 / ahb_div;
      break;
      
    case ANA_REG9_PLLHSEL_X2_5:
      hclk = 16384000 / ahb_div;
      break;
      
    case ANA_REG9_PLLHSEL_X3:
      hclk = 19660800 / ahb_div;
      break;
      
    case ANA_REG9_PLLHSEL_X3_5:
      hclk = 22937600 / ahb_div;
      break;
      
    case ANA_REG9_PLLHSEL_X4:
      hclk = 26214400 / ahb_div;
      break;
      
    case ANA_REG9_PLLHSEL_X4_5:
      hclk = 29491200 / ahb_div;
      break;
 
    case ANA_REG9_PLLHSEL_X5:
      hclk = 32768000 / ahb_div;
      break;
      
    case ANA_REG9_PLLHSEL_X5_5:
      hclk = 36044800 / ahb_div;
      break;
  
    case ANA_REG9_PLLHSEL_X6:
      hclk = 39321600 / ahb_div;
      break;
      
    case ANA_REG9_PLLHSEL_X6_5:
      hclk = 42598400 / ahb_div;
      break;
      
    case ANA_REG9_PLLHSEL_X7:
      hclk = 45875200 / ahb_div;
      break;
  
    case ANA_REG9_PLLHSEL_X7_5:
      hclk = 49152000 / ahb_div;
      break;
      
    default:
      hclk = 0;
      break;
    }
    break;
   
  /* AHB Clock source : RTCCLK */
  case MISC2_CLKSEL_CLKSEL_RTCCLK:
    /* Get current RTC clock divider */
    rtcclk_div = RTC->PSCA & RTC_PSCA_PSCA;
    if (rtcclk_div == RTC_PSCA_PSCA_0)
    {
      hclk = 32768 / ahb_div;
    }
    else if (rtcclk_div == RTC_PSCA_PSCA_1)
    {
      hclk = 8192 / ahb_div;
    }
    else
    {
      hclk = 0;
    }
    break;
    
  /* AHB Clock source : PLLL */
  case MISC2_CLKSEL_CLKSEL_PLLL:
    /* Get PLLL Frequency */
    plll_frq = ANA->REG9 & ANA_REG9_PLLLSEL;
    switch (plll_frq)
    {
    case ANA_REG9_PLLLSEL_26M:
      hclk = 26214400 / ahb_div;
      break;
      
    case ANA_REG9_PLLLSEL_13M:
      hclk = 13107200 / ahb_div;
      break; 
      
    case ANA_REG9_PLLLSEL_6_5M:
      hclk = 6553600 / ahb_div;
      break;
      
    case ANA_REG9_PLLLSEL_3_2M:
      hclk = 3276800 / ahb_div;
      break;
      
    case ANA_REG9_PLLLSEL_1_6M:
      hclk = 1638400 / ahb_div;
      break;
      
    case ANA_REG9_PLLLSEL_800K:
      hclk = 819200 / ahb_div;
      break;
      
    case ANA_REG9_PLLLSEL_400K:
      hclk = 409600 / ahb_div;
      break;
      
    case ANA_REG9_PLLLSEL_200K:
      hclk = 204800 / ahb_div;
      break;
      
    default:
      hclk = 0;
      break;
    }
    break;
    
  default:
    hclk = 0;
    break;
  }
  
  return (hclk);
}

/**
  * @brief  Returns the PLLL frequency
  * @param  None
  * @retval PLLL frequency
  */
uint32_t CLK_GetPLLLFreq(void)
{
  uint32_t plll_frq;

  if (!(ANA->REG3 & ANA_REG3_PLLLPDN))
    return 0;
  /* Get PLLL Frequency */
  plll_frq = ANA->REG9 & ANA_REG9_PLLLSEL;
  switch (plll_frq)
  {
    case ANA_REG9_PLLLSEL_26M:
      plll_frq = 26214400;
      break;
      
    case ANA_REG9_PLLLSEL_13M:
      plll_frq = 13107200;
      break; 
      
    case ANA_REG9_PLLLSEL_6_5M:
      plll_frq = 6553600;
      break;
      
    case ANA_REG9_PLLLSEL_3_2M:
      plll_frq = 3276800;
      break;
      
    case ANA_REG9_PLLLSEL_1_6M:
      plll_frq = 1638400;
      break;
      
    case ANA_REG9_PLLLSEL_800K:
      plll_frq = 819200;
      break;
      
    case ANA_REG9_PLLLSEL_400K:
      plll_frq = 409600;
      break;
      
    case ANA_REG9_PLLLSEL_200K:
      plll_frq = 204800;
      break;

    default:
      plll_frq = 0;
      break;
  }
  
  return (plll_frq);
}

/**
  * @brief  Returns the PCLK frequency
  * @param  None       
  * @retval PCLK frequency
  */
uint32_t CLK_GetPCLKFreq(void)
{
  return ((CLK_GetHCLKFreq()) / ((MISC2->CLKDIVP & MISC2_CLKDIVP_CLKDIVP) + 1));
}

/**
  * @brief  Get the CLK_ClkInitStruct according to the internal 
  *         Clock configuration registers.
  *
  * @param  CLK_ClkInitStruct pointer to an CLK_ClkInitStruct structure that 
  *         contains the current clock configuration.
  *
  * @retval None
  */
void CLK_GetClockConfig(CLK_InitTypeDef *CLK_ClkInitStruct)
{
  /* Set all possible values for the Clock type parameter --------------------*/
  CLK_ClkInitStruct->ClockType = CLK_TYPE_ALL;
  
  /* Get AHB clock source ----------------------------------------------------*/
  CLK_ClkInitStruct->AHBSource      = (uint32_t)(MISC2->CLKSEL & MISC2_CLKSEL_CLKSEL);
  /* Get PLLL clock configration ---------------------------------------------*/
  CLK_ClkInitStruct->PLLL.Source    = (uint32_t)(PMU->CONTROL & PMU_CONTROL_PLLL_SEL);
  CLK_ClkInitStruct->PLLL.Frequency = (uint32_t)(ANA->REG9 & ANA_REG9_PLLLSEL);
  CLK_ClkInitStruct->PLLL.State     = (uint32_t)(ANA->REG3 & ANA_REG3_PLLLPDN);
  /* Get PLLH clock configuration --------------------------------------------*/
  CLK_ClkInitStruct->PLLH.Source    = (uint32_t)(PMU->CONTROL & PMU_CONTROL_PLLH_SEL);
  CLK_ClkInitStruct->PLLH.Frequency = (uint32_t)(ANA->REG9 & ANA_REG9_PLLHSEL);
  CLK_ClkInitStruct->PLLH.State     = (uint32_t)(ANA->REG3 & ANA_REG3_PLLHPDN);
  /* Get XTALH configuration -------------------------------------------------*/
  CLK_ClkInitStruct->XTALH.State    = (uint32_t)(ANA->REG3 & ANA_REG3_XOHPDN);
  /* Get HCLK(Divider) configuration -----------------------------------------*/
  CLK_ClkInitStruct->HCLK.Divider   = (uint32_t)((MISC2->CLKDIVH & MISC2_CLKDIVH_CLKDIVH) + 1);
  /* Get PCLK((Divider) configuration ----------------------------------------*/
  CLK_ClkInitStruct->PCLK.Divider   = (uint32_t)((MISC2->CLKDIVP & MISC2_CLKDIVP_CLKDIVP) + 1);
}

/**
  * @brief  Gets current external 6.5M crystal status.
  *
  * @param  None
  *
  * @retval 6.5M crystal status
  *           0: 6.5536M crystal is absent.
  *           1: 6.5536M crystal is present.
  */
uint8_t CLK_GetXTALHStatus(void)
{
  if (PMU->STS & PMU_STS_EXIST_6M)
    return (1);
  else
    return (0);
}

/**
  * @brief  Gets current external 32K crystal status.
  *
  * @param  None
  *
  * @retval 32K crystal status
  *           0: 32K crystal is absent
  *           1: 32K crystal is present.
  */
uint8_t CLK_GetXTALLStatus(void)
{
  if (PMU->STS & PMU_STS_EXIST_32K)
    return (1);
  else
    return (0);
}

/**
  * @brief  Gets PLL lock status.
  * @param  PLLStatus:
  *             CLK_STATUS_LOCKL
  *             CLK_STATUS_LOCKH
  * @retval PLL lock status
  *             0  PLL is not locked.
  *             1  PLL is locked.
  */
uint8_t CLK_GetPLLLockStatus(uint32_t PLLStatus)
{
  /* Check parameters */
  assert_parameters(IS_CLK_PLLLOCK(PLLStatus));
  
  if (ANA->CMPOUT & PLLStatus)
    return 1;
  else
    return 0;
}

/*********************************** END OF FILE ******************************/
