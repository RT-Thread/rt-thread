/**
  ******************************************************************************
  * @file    lib_wdt.c 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
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
  * @brief  Enable WDT timer.
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
  * @brief  Disable WDT timer.
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
  * @brief  Clear WDT counter.
  * @param  None
  * @retval None
  */
void WDT_Clear(void)
{
  PMU->WDTCLR = WDTCLR_KEY;
}

/**
  * @brief  Set WDT counting period.
  * @param  counting period:
               WDT_2_SECS
               WDT_1_SECS
               WDT_0_5_SECS
               WDT_0_25_SECS
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
  * @brief  Get WDT counter value.
  * @param  None
  * @retval current counter value.
  */
uint16_t WDT_GetCounterValue(void)
{
  return (PMU->WDTCLR & PMU_WDTCLR_WDTCNT);
}

/*********************************** END OF FILE ******************************/
