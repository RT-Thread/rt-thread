/**
  ******************************************************************************
  * @file    lib_wdt.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   WDT library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_wdt.h"

#define WDTPASS_KEY 0xAA5555AA
#define WDTCLR_KEY  0x55AAAA55

/**
  * @brief  Enables WDT timer.
  * @param  None
  * @retval None
  */
void WDT_Enable(void)
{
  PMU->WDTPASS = WDTPASS_KEY;
  PMU->WDTEN |= PMU_WDTEN_WDTEN;
  
  PMU->WDTPASS = WDTPASS_KEY;
  PMU->WDTEN |= PMU_WDTEN_WDTEN;
}

/**
  * @brief  Disables WDT timer.
  * @param  None
  * @retval None
  */
void WDT_Disable(void)
{
  PMU->WDTPASS = WDTPASS_KEY;
  PMU->WDTEN &= ~PMU_WDTEN_WDTEN;
  
  PMU->WDTPASS = WDTPASS_KEY;
  PMU->WDTEN &= ~PMU_WDTEN_WDTEN;
}

/**
  * @brief  Clears WDT counter.
  * @param  None
  * @retval None
  */
void WDT_Clear(void)
{
  PMU->WDTCLR = WDTCLR_KEY;
}

/**
  * @brief  Configures WDT counting period.
  * @param  counting period:
               WDT_2_SECS
               WDT_4_SECS
               WDT_8_SECS
               WDT_16_SECS
  * @retval None
  */
void WDT_SetPeriod(uint32_t period)
{
  uint32_t tmp;
  
  assert_parameters(IS_WDT_PERIOD(period));
    
  tmp = PMU->WDTEN;
  tmp &= ~PMU_WDTEN_WDTSEL;
  tmp |= period;
  PMU->WDTPASS = WDTPASS_KEY;
  PMU->WDTEN = tmp;
}

/**
  * @brief  Gets WDT counter value.
  * @param  None
  * @retval current counter value.
  */
uint16_t WDT_GetCounterValue(void)
{
  return (PMU->WDTCLR & PMU_WDTCLR_WDTCNT);
}

/*********************************** END OF FILE ******************************/
