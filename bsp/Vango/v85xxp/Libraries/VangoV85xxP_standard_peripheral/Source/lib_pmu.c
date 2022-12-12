/**
  ******************************************************************************
  * @file    lib_pmu.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   PMU library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_pmu.h"
#include "lib_gpio.h"
#include "lib_CodeRAM.h"
#include "lib_clk.h"
#include "lib_cortex.h"

#define DSLEEPPASS_KEY  0xAA5555AA
#define DSLEEPEN_KEY    0x55AAAA55

/**
  * @brief  Enters deep-sleep mode.
  * @param  None
  * @retval 1: Current mode is debug mode, function failed.
  *         2: Enter deep-sleep mode failed.
  */
uint32_t PMU_EnterDSleepMode(void)
{
  uint32_t hclk;
  
  /* Current MODE is 0, debug mode, return error */
  if (!(PMU->STS & PMU_STS_MODE))
    return 1;
  
  /* Enter deep sleep when WKU event is cleared */
  while (PMU->DSLEEPEN & PMU_DSLEEPEN_WKU)
  {
  }
  
  /* Flash 1USCYCLE configure */
  hclk = CLK_GetHCLKFreq();
  if(hclk > 1000000)
  {
    MISC2->FLASHWC = (hclk/1000000)<<8;  
  }
  else
  {
    MISC2->FLASHWC = 0<<8; 
  }

  PMU->DSLEEPPASS = DSLEEPPASS_KEY;
  PMU->DSLEEPEN = DSLEEPEN_KEY;
  
  return 2;
}

/**
  * @brief  Enters idle mode.
  * @note   Any interrupt generates to CPU will break idle mode.
  * @param  None
  * @retval None
  */
void PMU_EnterIdleMode(void)
{
  /* Clear SLEEPDEEP bit of Cortex-M0 System Control Register */
  SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
  
  __WFI();
}

/**
  * @brief  Enters sleep mode.
  * @param  None
  * @retval 1: Current mode is debug mode, function failed.
  *         0: Quit sleep mode succeeded.
  */
uint32_t PMU_EnterSleepMode(void)
{
  uint32_t hclk;

  /* Current MODE is 0, debug mode, return error */
  if (!(PMU->STS & PMU_STS_MODE))
    return 1;
  
  /* Flash 1USCYCLE configure */
  hclk = CLK_GetHCLKFreq();
  if(hclk > 1000000)
  {
    MISC2->FLASHWC = (hclk/1000000)<<8;
  }
  else
  {
    MISC2->FLASHWC = 0<<8;
  }

  /* Set SLEEPDEEP bit of Cortex-M0 System Control Register */
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    
  __WFI();
  
  return 0;
}

/**
  * @brief  Enables or disables PMU interrupt.
  * @param  INTMask: can use the | operator
                PMU_INT_IOAEN
                PMU_INT_32K
                PMU_INT_6M
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void PMU_INTConfig(uint32_t INTMask, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_PMU_INT(INTMask));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));   
  
  if (NewState == ENABLE)
  {
    PMU->CONTROL |= INTMask;
  }
  else
  {
    PMU->CONTROL &= ~INTMask;
  }
}

/**
  * @brief  Gets PMU interrupt status.
  * @param  INTMask:
                PMU_INTSTS_32K
                PMU_INTSTS_6M
  * @retval 1:status set
            0:status reset
  */
uint8_t PMU_GetINTStatus(uint32_t INTMask)
{
  /* Check parameters */
  assert_parameters(IS_PMU_INTFLAGR(INTMask));

  if (PMU->STS&INTMask)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Clears PMU interrupt status.
  * @param  INTMask:specifies the flag to clear.
                This parameter can be any combination of the following values
                PMU_INTSTS_32K
                PMU_INTSTS_6M
  * @retval None
  */
void PMU_ClearINTStatus(uint32_t INTMask)
{
  /* Check parameters */
  assert_parameters(IS_PMU_INTFLAGC(INTMask));

  PMU->STS = INTMask;
}

/**
  * @brief  Gets Crystal status.
  * @param  Mask:
                PMU_STS_32K 
                PMU_STS_6M
  * @retval 1:status set
            0:status reset
  */
uint8_t PMU_GetCrystalStatus(uint32_t Mask)
{
  /* Check parameters */
  assert_parameters(IS_PMU_FLAG(Mask));
  
  if (PMU->STS&Mask)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Gest all IOA interrupt status.
  * @param  None
  * @retval IOA's interrupt status
  */
uint16_t PMU_GetIOAAllINTStatus(void)
{
  return (GPIOA->IOAINTSTS);
}

/**
  * @brief  Gest IOA interrupt status.
  * @param  INTMask:
                GPIO_Pin_0 ~ GPIO_Pin_15
  * @retval 1:status set
            0:status reset
  */
uint8_t PMU_GetIOAINTStatus(uint16_t INTMask)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_PINR(INTMask));  
  
  if (GPIOA->IOAINTSTS & INTMask)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Clears IOA interrupt status.
  * @param  INTMask:
                This parameter can be any combination of the following values
                GPIO_Pin_0 ~ GPIO_Pin_15
  * @retval None
  */
void PMU_ClearIOAINTStatus(uint16_t INTMask)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_PIN(INTMask)); 
  
  GPIOA->IOAINTSTS = INTMask;
}

/**
  * @brief  Configures Wake-up pin functions.
  * @param  IOAx:   GPIO_Pin_0 ~ GPIO_Pin_15
            Wakeup_Event:
                    IOA_DISABLE
                    IOA_RISING
                    IOA_FALLING
                    IOA_HIGH
                    IOA_LOW
                    IOA_EDGEBOTH
  * @retval None
  */
void PMU_WakeUpPinConfig(uint32_t IOAx, uint32_t Wakeup_Event)
{
  uint32_t tmp;
  uint32_t posision = 0x00U;
  uint32_t iocurrent = 0x00U;
  
  /* Check parameters */
  assert_parameters(IS_GPIO_PINR(IOAx));   
  assert_parameters(IS_PMU_WAKEUP(Wakeup_Event));   
  
  while ((IOAx >> posision) != 0U)
  {
    /* Get current io position */
    iocurrent = IOAx & (0x01U << posision);
    
    if (iocurrent)
    {
      /* Current IO Input configure*/
      GPIOA->OEN |= iocurrent;
      GPIOA->IE  |= iocurrent;
      
      tmp = GPIOA->IOAWKUEN;
      tmp &= ~(3U << (2 * posision));
      switch (Wakeup_Event)
      {
      /* Disable wake-up function */
      default:
      case IOA_DISABLE:
        break;
       
      /* wake-up function: Rising */
      case IOA_RISING:
        GPIOA->DAT &= ~iocurrent;
        tmp |= 1 << (2 * posision);
        break;
        
      /* wake-up function: falling */
      case IOA_FALLING:
        GPIOA->DAT |= iocurrent;
        tmp |= 1 << (2 * posision);
        break;

      /* wake-up function: high level */
      case IOA_HIGH:
        GPIOA->DAT &= ~iocurrent;
        tmp |= 2 << (2 * posision);
        break;  
        
      /* wake-up function: low level */
      case IOA_LOW:
        GPIOA->DAT |= iocurrent;
        tmp |= 2 << (2 * posision);
        break;
        
      /* wake-up function: both edge */
      case IOA_EDGEBOTH:
        tmp |= 3 << (2 * posision);
        break;
      }
      GPIOA->IOAWKUEN  = tmp;
    }
    posision++;
  }
}

/**
  * @brief  Enters deep-sleep mode with low-power configuration.
  *
  * @param  InitStruct : pointer to PMU_LowPWRTypeDef
               COMP1Power:
                       PMU_COMP1PWR_ON
                       PMU_COMP1PWR_OFF
               COMP2Power:
                       PMU_COMP2PWR_ON
                       PMU_COMP2PWR_OFF
               TADCPower:
                       PMU_TADCPWR_ON
                       PMU_TADCPWR_OFF
               BGPPower:
                       PMU_BGPPWR_ON
                       PMU_BGPPWR_OFF
               AVCCPower:
                       PMU_AVCCPWR_ON
                       PMU_AVCCPWR_OFF
               VDCINDetector:
                       PMU_VDCINDET_ENABLE
                       PMU_VDCINDET_DISABLE
               VDDDetector:
                       PMU_VDDDET_ENABLE
                       PMU_VDDDET_DISABLE
               APBPeriphralDisable:
                       PMU_APB_ALL
                       PMU_APB_DMA
                       PMU_APB_I2C
                       PMU_APB_SPI1
                       PMU_APB_UART0
                       PMU_APB_UART1
                       PMU_APB_UART2
                       PMU_APB_UART3
                       PMU_APB_UART4   
                       PMU_APB_UART5
                       PMU_APB_ISO78160
                       PMU_APB_ISO78161
                       PMU_APB_TIMER
                       PMU_APB_MISC
                       PMU_APB_U32K0
                       PMU_APB_U32K1
                       PMU_APB_SPI2
                       PMU_APB_SPI3
                AHBPeriphralDisable:
                       PMU_AHB_ALL
                       PMU_AHB_DMA
                       PMU_AHB_GPIO
                       PMU_AHB_LCD
                       PMU_AHB_CRYPT
  
  * @note   This function performs the following:
                Comparator 1 power control            ON or OFF(optional)
                Comparator 2 power control            ON or OFF(optional)
                Tiny ADC power control                ON or OFF(optional)
                Bandgap power control                 ON or OFF(optional)
                AVCC power control                    ON or OFF(optional)
                VDCIN detector control                Disable or Enable(optional)
                VDD detector control                  Disable or Enable(optional)
                Disable AHB/APB periphral clock       Modules(optional)
                Disable AVCC output
                Disable ADC
                Disable resistance division for ADC input signal
                Enable LCD

            If 5V power supply, AVCCPower should be ON, if 3.3V power supply, AVCCPower should be OFF.
  
  * @retval 1: Current MODE is debug mode, enter deep-sleep mode failed.    
            2: VDCIN is not drop before enter deep-sleep mode or Failure to enter deep sleep mode.

  */
uint8_t PMU_EnterDSleep_LowPower(PMU_LowPWRTypeDef *InitStruct)
{
  uint32_t tmp;
  uint32_t hclk;

  /* Check parameters */  
  assert_parameters(IS_PMU_COMP1PWR(InitStruct->COMP1Power));
  assert_parameters(IS_PMU_COMP2PWR(InitStruct->COMP2Power));
  assert_parameters(IS_PMU_TADCPWR(InitStruct->TADCPower));
  assert_parameters(IS_PMU_BGPPWR(InitStruct->BGPPower));
  assert_parameters(IS_PMU_AVCCPWR(InitStruct->AVCCPower));
  assert_parameters(IS_PMU_VDCINDET(InitStruct->VDCINDetector));
  assert_parameters(IS_PMU_VDDDET(InitStruct->VDDDetector));
  
  /* Current MODE is 0, debug mode, return error */
  if (!(PMU->STS & PMU_STS_MODE))
    return 1;
  
  /* Disable AVCC output */
  ANA->REGF &= ~ANA_REGF_AVCCOEN;
  
  /* Disable ADC */
  ANA->ADCCTRL2 &= ~ANA_ADCCTRL2_ADC_EN;
 
  /* Disable resistor division for ADC input signal */
  ANA->ADCCTRL1 &= ~ANA_ADCCTRL1_RESDIV_CHx;
  
  /******** Comparator 1 power control ********/
  ANA->REG3 &= ~ANA_REG3_CMP1PDN;
  ANA->REG3 |= InitStruct->COMP1Power;
  
  /******** Comparator 2 power control ********/
  ANA->REG3 &= ~ANA_REG3_CMP2PDN;
  ANA->REG3 |= InitStruct->COMP2Power;
  
  /******** Tiny ADC power control ********/
  tmp = ANA->REGF;
  tmp &= ~ANA_REGF_ADTPDN;
  tmp |= InitStruct->TADCPower;
  ANA->REGF = tmp;
  
  /******** BGP power control ********/
  ANA->REG3 &= ~ANA_REG3_BGPPD;
  ANA->REG3 |= InitStruct->BGPPower;
  
  /******** AVCC power control ********/
  tmp = ANA->REG8;
  tmp &= ~ANA_REG8_AVCCLDOPD;
  tmp |= InitStruct->AVCCPower;
  ANA->REG8 = tmp;
  
  /******** LCD controller power control ********/
  /* LCD should be ENABLE */
  tmp = LCD->CTRL;
  tmp |= LCD_CTRL_EN;
  LCD->CTRL = tmp;

  tmp = ANA->REG7;
  tmp |= BIT7;
  ANA->REG7 = tmp;

  /******** VDCIN detector control ********/ 
  tmp = ANA->REGA;
  tmp &= ~ANA_REGA_VDCINDETPD;
  tmp |= InitStruct->VDCINDetector;
  ANA->REGA = tmp;
 
  /******** VDD detector control *********/
  tmp = ANA->REG9;
  tmp &= ~ANA_REG9_VDDDETPD;
  tmp |= InitStruct->VDDDetector;
  ANA->REG9 = tmp;
  
  /******** AHB Periphral clock disable selection ********/
  tmp = MISC2->HCLKEN;
  tmp &= ~((InitStruct->AHBPeriphralDisable) & PMU_AHB_ALL);
  MISC2->HCLKEN = tmp;
  
  /******** APB Periphral clock disable selection ********/
  tmp = MISC2->PCLKEN;
  tmp &= ~((InitStruct->APBPeriphralDisable) & PMU_APB_ALL);
  MISC2->PCLKEN = tmp;
    
  if ((InitStruct->VDCINDetector) != PMU_VDCINDET_DISABLE)
  {
    if (!(ANA->CMPOUT & ANA_CMPOUT_VDCINDROP))
    {
      return 2;
    }
  }
  // make sure WKU is 0 before entering deep-sleep mode
  while (PMU->DSLEEPEN & PMU_DSLEEPEN_WKU);
  
  /* Flash 1USCYCLE configure */
  hclk = CLK_GetHCLKFreq();
  if(hclk > 1000000)
  {
    MISC2->FLASHWC = (hclk/1000000)<<8;  
  }
  else
  {
    MISC2->FLASHWC = 0<<8; 
  }

  /* Enter deep-sleep mode */
  PMU->DSLEEPPASS = DSLEEPPASS_KEY;
  PMU->DSLEEPEN = DSLEEPEN_KEY;

  return 2;
}

/**
  * @brief  Enters sleep mode with low-power configuration.
  *
  * @param  InitStruct : pointer to PMU_LowPWRTypeDef
               COMP1Power:
                       PMU_COMP1PWR_ON
                       PMU_COMP1PWR_OFF
               COMP2Power:
                       PMU_COMP2PWR_ON
                       PMU_COMP2PWR_OFF
               TADCPower:
                       PMU_TADCPWR_ON
                       PMU_TADCPWR_OFF
               BGPPower:
                       PMU_BGPPWR_ON
                       PMU_BGPPWR_OFF
               AVCCPower:
                       PMU_AVCCPWR_ON
                       PMU_AVCCPWR_OFF
               VDCINDetector:
                       PMU_VDCINDET_ENABLE
                       PMU_VDCINDET_DISABLE
               VDDDetector:
                       PMU_VDDDET_ENABLE
                       PMU_VDDDET_DISABLE
               APBPeriphralDisable:
                       PMU_APB_ALL
                       PMU_APB_DMA
                       PMU_APB_I2C
                       PMU_APB_SPI1
                       PMU_APB_SPI2
                       PMU_APB_UART0
                       PMU_APB_UART1
                       PMU_APB_UART2
                       PMU_APB_UART3
                       PMU_APB_UART4   
                       PMU_APB_UART5
                       PMU_APB_ISO78160
                       PMU_APB_ISO78161
                       PMU_APB_TIMER
                       PMU_APB_MISC
                       PMU_APB_U32K0
                       PMU_APB_U32K1
                       PMU_APB_SPI3
                AHBPeriphralDisable:    
                       PMU_AHB_ALL
                       PMU_AHB_DMA
                       PMU_AHB_GPIO
                       PMU_AHB_LCD
                       PMU_AHB_CRYPT 

  * @note   This function performs the following:
                Comparator 1 power control            ON or OFF(optional)
                Comparator 2 power control            ON or OFF(optional)
                Tiny ADC power control                ON or OFF(optional)
                Bandgap power control                 ON or OFF(optional)
                AVCC power control                    ON or OFF(optional)
                VDCIN detector control                Disable or Enable(optional)
                VDD detector control                  Disable or Enable(optional)
                Disable AHB/APB periphral clock       Modules(optional)
                Disable AVCC output
                Disable ADC
                Disable resistance division for ADC input signal
                Enable LCD

             If 5V power supply, AVCCPower should be ON, if 3.3V power supply, AVCCPower should be OFF.
                
  * @retval     2: VDCIN is not drop before enter sleep mode(failed).
                1: Current mode is debug mode, enter sleep mode failed.
                0: Quit from sleep mode success.
*/
uint8_t PMU_EnterSleep_LowPower(PMU_LowPWRTypeDef *InitStruct)
{
  uint32_t tmp;
  uint32_t hclk;

  /* Check parameters */
  assert_parameters(IS_PMU_COMP1PWR(InitStruct->COMP1Power));
  assert_parameters(IS_PMU_COMP2PWR(InitStruct->COMP2Power));
  assert_parameters(IS_PMU_TADCPWR(InitStruct->TADCPower));
  assert_parameters(IS_PMU_BGPPWR(InitStruct->BGPPower));
  assert_parameters(IS_PMU_AVCCPWR(InitStruct->AVCCPower));
  assert_parameters(IS_PMU_VDCINDET(InitStruct->VDCINDetector));
  assert_parameters(IS_PMU_VDDDET(InitStruct->VDDDetector));
  
  /* Current MODE is 0, debug mode, return error */
  if (!(PMU->STS & PMU_STS_MODE))
    return 1;
  
  /* Disable AVCC output */
  ANA->REGF &= ~ANA_REGF_AVCCOEN;
  
  /* Disable ADC */
  ANA->ADCCTRL2 &= ~ANA_ADCCTRL2_ADC_EN;
  
  /* Disable resistor division for ADC input signal */
  ANA->ADCCTRL1 &= ~ANA_ADCCTRL1_RESDIV_CHx ;
  
  /******** Comparator 1 power control ********/
  ANA->REG3 &= ~ANA_REG3_CMP1PDN;
  ANA->REG3 |= InitStruct->COMP1Power;
  
  /******** Comparator 2 power control ********/
  ANA->REG3 &= ~ANA_REG3_CMP2PDN;
  ANA->REG3 |= InitStruct->COMP2Power;
 
  
  /******** Tiny ADC power control ********/
  tmp = ANA->REGF;
  tmp &= ~ANA_REGF_ADTPDN;
  tmp |= InitStruct->TADCPower;
  ANA->REGF = tmp;
  
  /******** BGP power control ********/
  ANA->REG3 &= ~ANA_REG3_BGPPD;
  ANA->REG3 |= InitStruct->BGPPower;
  
  /******** AVCC power control ********/
  tmp = ANA->REG8;
  tmp &= ~ANA_REG8_AVCCLDOPD;
  tmp |= InitStruct->AVCCPower;
  ANA->REG8 = tmp;
  
  /******** LCD controller power control ********/
  /* LCD should be ENABLE */
  tmp = LCD->CTRL;
  tmp |= LCD_CTRL_EN;
  LCD->CTRL = tmp;

  tmp = ANA->REG7;
  tmp |= BIT7;
  ANA->REG7 = tmp;
  
  /******** VDCIN detector control ********/ 
  tmp = ANA->REGA;
  tmp &= ~ANA_REGA_VDCINDETPD;
  tmp |= InitStruct->VDCINDetector;
  ANA->REGA = tmp;

  /******** VDD detector control *********/
  tmp = ANA->REG9;
  tmp &= ~ANA_REG9_VDDDETPD;
  tmp |= InitStruct->VDDDetector;
  ANA->REG9 = tmp;
   
  /******** AHB Periphral clock disable selection ********/
  tmp = MISC2->HCLKEN;
  tmp &= ~((InitStruct->AHBPeriphralDisable) & PMU_AHB_ALL);
  MISC2->HCLKEN = tmp;
  
  /******** APB Periphral clock disable selection ********/
  tmp = MISC2->PCLKEN;
  tmp &= ~((InitStruct->APBPeriphralDisable) & PMU_APB_ALL);
  MISC2->PCLKEN = tmp;
  
  if ((InitStruct->VDCINDetector) != PMU_VDCINDET_DISABLE)
  {
    if (!(ANA->CMPOUT & ANA_CMPOUT_VDCINDROP))
    {
      return 2;
    }
  }
  
  /* Flash 1USCYCLE configure */
  hclk = CLK_GetHCLKFreq();
  if(hclk > 1000000)
  {
    MISC2->FLASHWC = (hclk/1000000)<<8;  
  }
  else
  {
    MISC2->FLASHWC = 0<<8;
  }

  /* Set SLEEPDEEP bit of Cortex-M0 System Control Register */
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk; 
  __WFI();
  
  return 0;
}


/**
  * @brief  Enter idle mode with flash deep standby.
  * @param  None
  * @retval None
  */
#ifndef __GNUC__
void PMU_EnterIdle_LowPower(void)
{
  uint32_t hclk;
		
  /* Flash 1USCYCLE configure */
  hclk = CLK_GetHCLKFreq();
  if(hclk > 1000000)
  {
    MISC2->FLASHWC = (hclk/1000000)<<8;  
  }
  else 
  {
    MISC2->FLASHWC = 0<<8; 
  }
  
  PMU_EnterIdle_FlashDSTB();
}
#endif

/**
  * @brief  Configures IOA wake-up source about sleep mode.
  * @param  IOAx:   GPIO_Pin_0 ~ GPIO_Pin_15
            Wakeup_Event:
                    IOA_DISABLE
                    IOA_RISING
                    IOA_FALLING
                    IOA_HIGH
                    IOA_LOW
                    IOA_EDGEBOTH 
           Priority: The preemption priority for the IRQn channel.
                     This parameter can be a value between 0 and 3.
  * @retval 
  */
void PMU_SleepWKUSRCConfig_IOA(uint16_t IOAx, uint32_t Wakeup_Event, uint32_t Priority)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_PINR(IOAx));   
  assert_parameters(IS_PMU_WAKEUP(Wakeup_Event)); 
  
  /* Disable PMU interrupt in NVIC */
  NVIC_DisableIRQ(PMU_IRQn);
  /* Wake-up pins configuration */
  PMU_WakeUpPinConfig(IOAx, Wakeup_Event);
  /* Clear interrupt flag */
  GPIOA->IOAINTSTS = IOAx;
  /* Enable PMU interrupt */
  PMU->CONTROL |= PMU_CONTROL_INT_IOA_EN;
  CORTEX_SetPriority_ClearPending_EnableIRQ(PMU_IRQn, Priority);
}

/**
  * @brief  Configures RTC wake-up source about sleep mode.
  * @param  Wakeup_Event:
                This parameter can be any combination of the following values
                PMU_RTCEVT_ALARM
                PMU_RTCEVT_WKUCNT
                PMU_RTCEVT_MIDNIGHT
                PMU_RTCEVT_WKUHOUR 
                PMU_RTCEVT_WKUMIN 
                PMU_RTCEVT_WKUSEC
                PMU_RTCEVT_TIMEILLE 
                PMU_RTCEVT_ITVSITV
           Priority: The preemption priority for the IRQn channel.
                     This parameter can be a value between 0 and 3.
  * @retval 
  */
void PMU_SleepWKUSRCConfig_RTC(uint32_t Wakeup_Event, uint32_t Priority)
{
  /* Check parameters */
  assert_parameters(IS_PMU_RTCEVT(Wakeup_Event));
  
  /* Disable RTC interrupt in NVIC */
  NVIC_DisableIRQ(RTC_IRQn);
  /* Clear interrupt flag */
  RTC->INTSTS = Wakeup_Event;
  /* Enable RTC interrupt */
  RTC->INTEN |= Wakeup_Event;
  CORTEX_SetPriority_ClearPending_EnableIRQ(RTC_IRQn, Priority);
}
/**
  * @brief  Configures IOA wake-up source about deep-sleep mode.
  * @param  IOAx:   GPIO_Pin_0 ~ GPIO_Pin_15
            Wakeup_Event:
                    IOA_DISABLE
                    IOA_RISING
                    IOA_FALLING
                    IOA_HIGH
                    IOA_LOW
                    IOA_EDGEBOTH 
  * @retval 
  */
void PMU_DeepSleepWKUSRCConfig_IOA(uint16_t IOAx, uint32_t Wakeup_Event)
{
  /* Check parameters */
  assert_parameters(IS_GPIO_PINR(IOAx));   
  assert_parameters(IS_PMU_WAKEUP(Wakeup_Event)); 
  
  /* Wake-up pins configuration */
  PMU_WakeUpPinConfig(IOAx, Wakeup_Event);
  /* Clear interrupt flag */
  GPIOA->IOAINTSTS = IOAx;
}

/**
  * @brief  Configures RTC wake-up source about deep-sleep mode.
  * @param  Wakeup_Event:
                This parameter can be any combination of the following values
                PMU_RTCEVT_ALARM
                PMU_RTCEVT_WKUCNT
                PMU_RTCEVT_MIDNIGHT
                PMU_RTCEVT_WKUHOUR 
                PMU_RTCEVT_WKUMIN 
                PMU_RTCEVT_WKUSEC
                PMU_RTCEVT_TIMEILLE 
                PMU_RTCEVT_ITVSITV
  * @retval 
  */
void PMU_DeepSleepWKUSRCConfig_RTC(uint32_t Wakeup_Event)
{
  /* Check parameters */
  assert_parameters(IS_PMU_RTCEVT(Wakeup_Event));
  
  /* Clear interrupt flag */
  RTC->INTSTS = Wakeup_Event;
  /* Enable RTC interrupt */
  RTC->INTEN |= Wakeup_Event;
}

/**
  * @brief  Configures the deep sleep behavior when VDD/VDCIN is not drop.
  * @param  VDCIN_PDNS:
                PMU_VDCINPDNS_0  , can't enter deep-sleep mode when VDCIN is not drop
                                   can wake-up mcu from deep-sleep, when VDCIN is not drop.
                PMU_VDCINPDNS_1  , The condition for entering deep sleep mode is independent of VDCIN.
            VDD_PDNS: 
                PMU_VDDPDNS_0  , can't enter deep-sleep mode when VDD is not drop(>Threshold)
                                 can wake-up mcu from deep-sleep, when VDD is not drop.
                PMU_VDDPDNS_1  , The condition for entering deep sleep mode is independent of VDD.
  * @retval None
  */
void PMU_PDNDSleepConfig(uint32_t VDCIN_PDNS, uint32_t VDD_PDNS)
{
  uint32_t tmp;

  /* Check parameters */  
  assert_parameters(IS_PMU_VDCINPDNS(VDCIN_PDNS));
  assert_parameters(IS_PMU_VDDPDNS(VDD_PDNS));   
    
  tmp = ANA->CTRL;
  tmp &= ~(ANA_CTRL_PDNS | ANA_CTRL_PDNS2);
  tmp |= (VDCIN_PDNS | VDD_PDNS);

  ANA->CTRL = tmp;
}

/**
  * @brief  Enables or disables BGP power.
  * @param  NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void PMU_BGPCmd(uint32_t NewState)
{
  /* Check parameters */  
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 

  if (NewState == ENABLE)
    ANA->REG3 &= ~ANA_REG3_BGPPD;
  else
    ANA->REG3 |= ANA_REG3_BGPPD;
}

/**
  * @brief  Configures VDD alarm threshold voltage.
  * @param  CheckTHR:
                PMU_VDDALARM_4_5V
                PMU_VDDALARM_4_2V
                PMU_VDDALARM_3_9V
                PMU_VDDALARM_3_6V
                PMU_VDDALARM_3_2V   
                PMU_VDDALARM_2_9V   
                PMU_VDDALARM_2_6V   
                PMU_VDDALARM_2_3V 
            CheckFrequency:
                PMU_VDDALARM_CHKFRE_NOCHECK
                PMU_VDDALARM_CHKFRE_30US
  * @retval None
  */
void PMU_VDDAlarmConfig(uint32_t CheckTHR,uint32_t CheckFrequency)
{
  uint32_t tmp;

  /* Check parameters */ 
  assert_parameters(IS_PMU_VDDALARM_THR(CheckTHR));
  assert_parameters(IS_PMU_VDDALARM_CHKFRE(CheckFrequency));

  /*        Configure CheckTHR         */
  tmp = ANA->REG8;
  tmp &= ~ANA_REG8_VDDPVDSEL;
  tmp |= CheckTHR;
  ANA->REG8 = tmp;

  /*        Configure CheckFrequency         */
  tmp = ANA->CMPCTL;
  tmp &= ~ANA_CMPCTL_VDDALARM_CHK_FRQ_SEL;
  tmp |= CheckFrequency;
  ANA->CMPCTL = tmp;

  if (CheckFrequency == PMU_VDDALARM_CHKFRE_NOCHECK)
  {
    ANA->REG9 |= ANA_REG9_VDDDETPD;
  }
  else
  {
    ANA->REG9 &= ~ANA_REG9_VDDDETPD;
  }
}

/**
  * @brief  Gets VDD alarm status.
  * @param  None
  * @retval POWALARM status
                0: Voltage of VDD is higher than threshold.
                1: Voltage of VDD is lower than threshold.
  */
uint8_t PMU_GetVDDAlarmStatus(void)
{
  if (ANA->CMPOUT & ANA_CMPOUT_VDDALARM)
    return 1;
  else
    return 0;
}

/**
  * @brief  Gets current MODE pin status.
  * @param  None
  * @retval MODE pin status
  *           0: Debug mode.
  *           1: Normal mode.
  */
uint8_t PMU_GetModeStatus(void)
{
  if(PMU->STS & PMU_STS_MODE)
    return 1;
  else
    return 0;
}

/**
  * @brief  Enables or disables AVCC.
  * @param  NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void PMU_AVCCCmd(uint32_t NewState)
{
  /* Check parameters */ 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
    ANA->REG8 &= ~ANA_REG8_AVCCLDOPD;
  else
    ANA->REG8 |= ANA_REG8_AVCCLDOPD;
}

/**
  * @brief  Enables or disables VDD33_O pin power.
  * @param  NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void PMU_AVCCOutputCmd(uint32_t NewState)
{
  /* Check parameters */ 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == DISABLE)
    ANA->REGF &= ~ANA_REGF_AVCCOEN;
  else
    ANA->REGF |= ANA_REGF_AVCCOEN;
}

/**
  * @brief  Enables or disables AVCC Low Voltage detector.
  * @param  NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void PMU_AVCCLVDetectorCmd(uint32_t NewState)
{
  /* Check parameters */ 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
    ANA->REG5 &= ~ANA_REG5_AVCCLVDETPD;
  else
    ANA->REG5 |= ANA_REG5_AVCCLVDETPD;
}

/**
  * @brief  Gets AVCC low power status.
  * @param  None
  * @retval low power status of AVCC
  *           0: status not set, AVCC is higher than 2.5V.
  *           1: status set, AVCC is lower than 2.5V.
  */
uint8_t PMU_GetAVCCLVStatus(void)
{
  if (ANA->CMPOUT & ANA_CMPOUT_AVCCLV)
    return 1;
  else
    return 0;
}

/**
  * @brief  Enables or disables VDCIN decector.
  * @param  NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void PMU_VDCINDetectorCmd(uint32_t NewState)
{
  /* Check parameters */ 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
    ANA->REGA &= ~ANA_REGA_VDCINDETPD;
  else
    ANA->REGA |= ANA_REGA_VDCINDETPD;
}

/**
  * @brief  Gets VDCIN drop status.
  * @param  None
  * @retval drop status of VDCIN
              0: status not set, VDCIN is not drop.
              1: status set, VDCIN is drop.
  */
uint8_t PMU_GetVDCINDropStatus(void)
{
  if (ANA->CMPOUT & ANA_CMPOUT_VDCINDROP)
    return 1;
  else
    return 0;
}

/**
  * @brief  Configures VDDALARM, VDCIN and AVCCDET de-bounce.
  * @param  DEBSel:
                0: No de-bounce.
                1: 2 RTCCLK de-bounce.
                2: 3 RTCCLK de-bounce.
                3: 4 RTCCLK de-bounce.
                4: 5 RTCCLK de-bounce.
                ...
                255: 256 RTCCLK de-bounce.
  * @retval None
  */
void PMU_PWRDEBSel(uint32_t DEBSel)
{
  uint32_t tmp;
  /* Check parameters */ 
  assert_parameters(IS_PMU_PWR_DEBSEL(DEBSel));

  tmp = ANA->CMPCTL;
  tmp &= ~ANA_CMPCTL_PWR_DEB_SEL;
  tmp |= (DEBSel << ANA_CMPCTL_PWR_DEB_SEL_Pos);
  ANA->CMPCTL = tmp;
}

/**
  * @brief  Discharges or not discharges the BAT battery.
  * @param  BATDisc:
                PMU_BAT1
                PMU_BATRTC
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void PMU_BATDischargeConfig(uint32_t BATDisc, uint32_t NewState)
{
  /* Check parameters */ 
  assert_parameters(IS_PMU_BATRTCDISC(BATDisc));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState == ENABLE)
    ANA->REG6 |= BATDisc;
  else
    ANA->REG6 &= ~BATDisc;
}


/**
  * @brief  Gets power status.
  * @param  StatusMask:
                PMU_PWRSTS_AVCCLV
                PMU_PWRSTS_VDCINDROP
                PMU_PWRSTS_VDDALARM
  * @retval power status
  *           1  status set
  *           0  status not set
  */
uint8_t PMU_GetPowerStatus(uint32_t StatusMask)
{
  if (ANA->CMPOUT & StatusMask)
    return 1;
  else
    return 0;
}

/**
  * @brief  Gets reset source status.
  * @param  Mask:
                PMU_RSTSRC_EXTRST
                PMU_RSTSRC_PORST
                PMU_RSTSRC_DPORST
                PMU_RSTSRC_WDTRST
                PMU_RSTSRC_SFTRST
                PMU_RSTSRC_MODERST
  * @retval 1: Reset status set
            0: Reset status reset
  */
uint8_t PMU_GetResetSource(uint32_t Mask)
{
  /* Check parameters */
  assert_parameters(PMU_RESETSRC(Mask));  

  if (PMU->STS & Mask)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Clears reset source status.
  * @param  Mask: can use the '|' operator
                PMU_RSTSRC_EXTRST
                PMU_RSTSRC_PORST
                PMU_RSTSRC_DPORST
                PMU_RSTSRC_WDTRST
                PMU_RSTSRC_SFTRST
                PMU_RSTSRC_MODERST
                PMU_RSTSRC_ALL
  * @retval None
  */
void PMU_ClearResetSource(uint32_t Mask)
{
  /* Check parameters */
  assert_parameters(PMU_RESETSRC_CLR(Mask));
  
  PMU->STS = Mask;
}

/**
  * @brief  Gets all reset source status.
  * @param  None
  * @retval All reset source status
  */
uint32_t PMU_GetAllResetSource(void)
{
  return (PMU->STS & PMU_RSTSRC_Msk);
}

/**
  * @brief  Gets deep-sleep wakeup source status.
  * @param  Mask:
                PMU_DSLEEPWKUSRC_MODE
                PMU_DSLEEPWKUSRC_XTAL
                PMU_DSLEEPWKUSRC_U32K
                PMU_DSLEEPWKUSRC_ANA
                PMU_DSLEEPWKUSRC_RTC
                PMU_DSLEEPWKUSRC_IOA
  * @retval 1: Wakeup status set
            0: Wakeup status reset
  */
uint8_t PMU_GetDSleepWKUSource(uint32_t Mask)
{
  /* Check parameters */
  assert_parameters(IS_PMU_DSLEEPWKUSRC(Mask));
  
  if (PMU->STS & Mask)
    return 1;
  else
    return 0;
}

/**
  * @brief  Gest deep-sleep wakeup source status.
  * @param  None
  * @retval All deep-sleep wakeup source status
  */
uint32_t PMU_GetAllDSleepWKUSource(void)
{
  return (PMU->STS & PMU_DSLEEPWKUSRC_Msk);
}

/*********************************** END OF FILE ******************************/
