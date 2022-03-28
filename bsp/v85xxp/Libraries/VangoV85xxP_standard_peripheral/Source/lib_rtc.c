/**
  ******************************************************************************
  * @file    lib_rtc.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   RTC library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_rtc.h"

#define RTCPWD_KEY    0x5AA55AA5
#define RTCCE_SETKEY  0xA55AA55B
#define RTCCE_CLRKEY  0xA55AA55A

/**
  * @brief  Enables or disables RTC registers write protection. 
  * @param  NewState:
  *             ENABLE      
  *             DISABLE
  * @retval None
  */
void RTC_WriteProtection(uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  /* Enable RTC Write-Protection */
  if (NewState != DISABLE)
  {
    RTC->PWD = RTCPWD_KEY;
    RTC->CE = RTCCE_CLRKEY;
  }
  /* Disable RTC Write-Protection */
  else
  {
    RTC->PWD = RTCPWD_KEY;
    RTC->CE = RTCCE_SETKEY;       
  }
}

/**
  * @brief  Waits until the RTC registers (be W/R protected) are synchronized
  *         with RTC APB clock.
  * @note   The RTC Resynchronization mode is write protected, use the 
  *         RTC_WriteProtection(DISABLE) before calling this function.
  *           Write-Operation process as follows: 
  *             1. RTC_WriteProtection(DISABLE);  
  *             2. RTC Registers write operation(only first write-operation be 
  *                valid on the same register).
  *             3. RTC_WriteProtection(ENABLE); 
  *             4. RTC_WaitForSynchro();  Wait until the RTC registers be 
  *                synchronized by calling this function.
  * @retval None
  */
void RTC_WaitForSynchro(void)
{
  while (RTC->CE & RTC_CE_BSY)
  {
  }
}

/**
  * @brief      Writes RTC registers(continuous/be write-protected). 
  * @param[in]  StartAddr   the start address of registers be written
  * @param[in]  wBuffer     pointer to write
  * @param[in]  Len         number of registers be written
  * @retval     None
  */
void RTC_WriteRegisters(uint32_t StartAddr, const uint32_t *wBuffer, uint8_t Len)
{
  uint8_t cnt;
  
  /* Parameter check */
  assert_parameters(IS_RTC_REGOP_STARTADDR(StartAddr));

  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();  
  
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);
  
  /* Write registers */
  for (cnt=0; cnt<Len; cnt++)
  {
    *(volatile uint32_t *)(StartAddr) = *(wBuffer++);
    StartAddr += 4;
  }
  
  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
}

/**
  * @brief      Reads RTC registers(continuous/be read-protected). 
  * @param[in]  StartAddr   the start address of registers be read
  * @param[out] rBuffer     pointer to read
  * @param[in]  Len         number of registers be read
  * @retval     None
  */
void RTC_ReadRegisters(uint32_t StartAddr, uint32_t *rBuffer, uint8_t Len)
{
  __IO uint32_t tmp;
  uint8_t cnt;
  
  /* Parameter check */
  assert_parameters(IS_RTC_REGOP_STARTADDR(StartAddr));

  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  
  /* Dummy read-operation to RTC->LOAD */
  tmp = RTC->LOAD;
  tmp += 1; 
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  
  /* Read registers */
  for (cnt=0; cnt<Len; cnt++)
  {
    *(rBuffer++) = *(volatile uint32_t *)(StartAddr);
    StartAddr += 4;
  }
}

/**
  * @brief  Sets RTC current time.
  * @param  sTime: Pointer to Time structure
  *         AccurateSel:
  *             RTC_ACCURATE
  *             RTC_INACCURATE
  * @retval None
  */
void RTC_SetTime(RTC_TimeTypeDef *sTime, uint32_t AccurateSel)
{
  uint32_t subsec,sec,alarmctl;

  /* Parameter check */
  assert_parameters(IS_RTC_TIME_YEAR(sTime->Year));
  assert_parameters(IS_RTC_TIME_MONTH(sTime->Month));
  assert_parameters(IS_RTC_TIME_DATE(sTime->Date)); 
  assert_parameters(IS_RTC_TIME_WEEKDAY(sTime->WeekDay)); 
  assert_parameters(IS_RTC_TIME_HOURS(sTime->Hours)); 
  assert_parameters(IS_RTC_TIME_MINS(sTime->Minutes)); 
  assert_parameters(IS_RTC_TIME_SECS(sTime->Seconds));
  if (AccurateSel == RTC_ACCURATE)
    assert_parameters(IS_RTC_TIME_SubSECS(sTime->SubSeconds));
  assert_parameters(IS_RTC_ACCURATESEL(AccurateSel));

  subsec = sTime->SubSeconds;
  subsec = subsec -(subsec>>8)*156 -((subsec&0xFF)>>4)*6;
  sec = sTime->Seconds;
  sec = sec - (sec>>4)*6;
  subsec = sec * 32768 + subsec * 32768 / 1000;

  alarmctl = RTC->ALARMCTL;
  if (AccurateSel == RTC_ACCURATE)
    alarmctl |= RTC_ALARMCTL_TIME_CNT_EN;
  else
    alarmctl &= ~RTC_ALARMCTL_TIME_CNT_EN;
  
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);

  /* Write RTC time registers */
  RTC->TIME = subsec;
  RTC->SEC  = sTime->Seconds;
  RTC->MIN  = sTime->Minutes;
  RTC->HOUR = sTime->Hours;
  RTC->DAY  = sTime->Date;
  RTC->WEEK = sTime->WeekDay;
  RTC->MON  = sTime->Month;
  RTC->YEAR = sTime->Year;
  RTC->ALARMCTL = alarmctl;

  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
}

/**
  * @brief  Gets RTC current time.
  * @param[out]  gTime: Pointer to Time structure
  * @param[in]  AccurateSel:
  *                 RTC_ACCURATE
  *                 RTC_INACCURATE
  * @retval None
*/
void RTC_GetTime(RTC_TimeTypeDef *gTime, uint32_t AccurateSel)
{
  __IO uint32_t dummy_data = 0;
  uint32_t subsec,sec;

  /* Parameter check */
  assert_parameters(IS_RTC_ACCURATESEL(AccurateSel));
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  
  /* Dummy read-operation to RTC->LOAD register */
  dummy_data = RTC->LOAD;
  dummy_data += 1;
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  
  /* Read RTC time registers */
  gTime->Seconds  = RTC->SEC;
  gTime->Minutes  = RTC->MIN;
  gTime->Hours    = RTC->HOUR;
  gTime->Date     = RTC->DAY;
  gTime->WeekDay  = RTC->WEEK;
  gTime->Month    = RTC->MON;
  gTime->Year     = RTC->YEAR;
  subsec          = RTC->TIME;

  if (AccurateSel == RTC_ACCURATE)
  {
    sec = subsec/32768;
    sec = sec + (sec/10)*6;
    gTime->Seconds = sec;
    subsec = (subsec%32768)*1000/32768;
    subsec = subsec + ((subsec%100)/10)*6 + (subsec/100)*156;
    gTime->SubSeconds = subsec;
  }
  else
  {
    gTime->SubSeconds = 0;
  }
}

/**
  * @brief  Enables or disables the RTC Sub Seconds.
  * @param  NewState:
  *             ENABLE
  *             DISABLE
  * @retval None
  */
void RTC_SubSecondCmd(uint32_t NewState)
{
  uint32_t tmp;

  /* Parameter check */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  tmp = RTC->ALARMCTL;
  if (NewState == ENABLE)
  {
    tmp |= RTC_ALARMCTL_TIME_CNT_EN;
  }
  else
  {
    tmp &= ~RTC_ALARMCTL_TIME_CNT_EN;
  }

  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);

  RTC->ALARMCTL = tmp;

  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
}

/**
  * @brief  Sets the RTC Alarm.
  * @param  RTC_AlarmStruct: pointer to a RTC_AlarmTypeDef structure that 
  *                          contains the alarm configuration parameters. 
  *         AccurateSel:
  *             RTC_ACCURATE
  *             RTC_INACCURATE
  * @retval None
  */
void RTC_SetAlarm(RTC_AlarmTypeDef *RTC_AlarmStruct, uint32_t AccurateSel)
{
  uint32_t subsec,sec,alarmctl;
  /* Parameter check */
  assert_parameters(IS_RTC_TIME_HOURS(RTC_AlarmStruct->AlarmHours)); 
  assert_parameters(IS_RTC_TIME_MINS(RTC_AlarmStruct->AlarmMinutes)); 
  assert_parameters(IS_RTC_TIME_SECS(RTC_AlarmStruct->AlarmSeconds)); 
  if (AccurateSel == RTC_ACCURATE)
    assert_parameters(IS_RTC_TIME_SubSECS(RTC_AlarmStruct->AlarmSubSeconds));
  assert_parameters(IS_RTC_ACCURATESEL(AccurateSel));

  subsec = RTC_AlarmStruct->AlarmSubSeconds;
  subsec = subsec -(subsec>>8)*156 -((subsec&0xFF)>>4)*6;
  sec = RTC_AlarmStruct->AlarmSeconds;
  sec = sec - (sec>>4)*6;
  subsec = sec * 32768 + subsec * 32768 / 1000;

  alarmctl = RTC->ALARMCTL;
  if (AccurateSel == RTC_ACCURATE)
    alarmctl &= ~RTC_ALARMCTL_ALARM_INACCURATE;
  else
    alarmctl |= RTC_ALARMCTL_ALARM_INACCURATE;
  
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);

  RTC->ALARMHOUR = RTC_AlarmStruct->AlarmHours;
  RTC->ALARMMIN = RTC_AlarmStruct->AlarmMinutes;
  RTC->ALARMSEC = RTC_AlarmStruct->AlarmSeconds;
  RTC->ALARMTIME = subsec;
  RTC->ALARMCTL = alarmctl;
  /* Write RTC time registers */
  
  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
}

/**
  * @brief  Gets the RTC Alarm.
  * @param[out]  RTC_AlarmStruct: pointer to a RTC_AlarmTypeDef structure that will 
  *                          contains the output alarm configuration values.
  * @param[in]  AccurateSel:
  *                 RTC_ACCURATE
  *                 RTC_INACCURATE
  * @retval None
  */
void RTC_GetAlarm(RTC_AlarmTypeDef *RTC_AlarmStruct, uint32_t AccurateSel)
{
  uint32_t sec,subsec;

  /* Parameter check */
  assert_parameters(IS_RTC_ACCURATESEL(AccurateSel));

  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  
  /* Read RTC time registers */
  RTC_AlarmStruct->AlarmHours = RTC->ALARMHOUR;
  RTC_AlarmStruct->AlarmMinutes = RTC->ALARMMIN;
  RTC_AlarmStruct->AlarmSeconds = RTC->ALARMSEC;
  subsec = RTC->ALARMTIME;

  if (AccurateSel == RTC_ACCURATE)
  {
    sec = subsec/32768;
    sec = sec + (sec/10)*6;
    RTC_AlarmStruct->AlarmSeconds = sec;
    subsec = (subsec%32768)*1000/32768;
    subsec = subsec + ((subsec%100)/10)*6 + (subsec/100)*156;
    RTC_AlarmStruct->AlarmSubSeconds = subsec;
  }
  else
  {
    RTC_AlarmStruct->AlarmSubSeconds = 0;
  }
}

/**
  * @brief  Enables or disables the RTC Alarm.
  * @param  NewState:
  *             ENABLE
  *             DISABLE
  * @retval None
  */
void RTC_AlarmCmd(uint32_t NewState)
{
  uint32_t tmp;
  /* Parameter check */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  tmp = RTC->ALARMCTL;
  if (NewState == ENABLE)
  {
    tmp |= (RTC_ALARMCTL_ALARM_EN);
  }
  else
  {
    tmp &= ~(RTC_ALARMCTL_ALARM_EN);
  }

  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();  
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);

  RTC->ALARMCTL = tmp;

  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
}

/**
  * @brief  Enables or disables the RTC alarm accurate.
  * @param  NewState:
  *             ENABLE
  *             DISABLE
  * @retval None
  */
void RTC_AlarmAccurateCmd(uint32_t NewState)
{
  uint32_t tmp = 0;
  /* Parameter check */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  tmp = RTC->ALARMCTL;
  if (NewState == ENABLE)
  {
    tmp &= ~RTC_ALARMCTL_ALARM_INACCURATE;
  }
  else
  {
    tmp |= RTC_ALARMCTL_ALARM_INACCURATE;
  }

  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();  
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);

  RTC->ALARMCTL = tmp;

  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
}

/**
  * @brief  Enables or disables RTC interrupt.
  * @param  INTMask: can use the '|' operator
                RTC_INT_ALARM
                RTC_INT_CEILLE
                RTC_INT_ACDONE
                RTC_INT_WKUCNT
                RTC_INT_MIDNIGHT
                RTC_INT_WKUHOUR 
                RTC_INT_WKUMIN 
                RTC_INT_WKUSEC
                RTC_INT_TIMEILLE 
                RTC_INT_ITVSITV
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void RTC_INTConfig(uint32_t INTMask, uint32_t NewState)
{
  /* Parameter check */
  assert_parameters(IS_RTC_INT(INTMask));  
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if (NewState == ENABLE)
    RTC->INTEN |= INTMask;
  else
    RTC->INTEN &= ~INTMask;
}

/**
  * @brief  Gets RTC interrupt status.
  * @param  INTMask:
                RTC_INTSTS_ALARM
                RTC_INTSTS_CEILLE
                RTC_INTSTS_WKUCNT
                RTC_INTSTS_MIDNIGHT
                RTC_INTSTS_WKUHOUR 
                RTC_INTSTS_WKUMIN 
                RTC_INTSTS_WKUSEC
                RTC_INTSTS_TIMEILLE 
                RTC_INTSTS_ITVSITV
    * @retval 1: status set
              0: status reset.
  */
uint8_t RTC_GetINTStatus(uint32_t FlagMask)
{
  /* Parameter check */
  assert_parameters(IS_RTC_INTFLAGR(FlagMask));    

  if (RTC->INTSTS&FlagMask)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Clears RTC interrupt status.
  * @param  INTMask: can use the '|' operator
                RTC_INTSTS_ALARM
                RTC_INTSTS_CEILLE
                RTC_INTSTS_WKUCNT
                RTC_INTSTS_MIDNIGHT
                RTC_INTSTS_WKUHOUR 
                RTC_INTSTS_WKUMIN 
                RTC_INTSTS_WKUSEC
                RTC_INTSTS_TIMEILLE 
                RTC_INTSTS_ITVSITV
  * @retval  None
  */
void RTC_ClearINTStatus(uint32_t FlagMask)
{
  /* Parameter check */
  assert_parameters(IS_RTC_INTFLAGC(FlagMask));
  
  RTC->INTSTS = FlagMask;
}

/*
  * @brief  Configures Multi-second wake up function.
  * @param  nPeriod£ºN seconds interval.
  * @note   For the first interrupt generated by calling this function, it may 
  *         have < 1 sec error if the new WKUSEC number(parameter) is not equal 
  *         to current WKUSEC number.  If the new WKUSEC is equal to current WKUSEC, 
  *         the first interrupt time may have 0~(WKUSEC +1) variation.  
  *         To avoid this problem, set an alternative parameter (like 1) by calling
  *         this function, then set the correct parameter to it.
  * @retval None
  */
void RTC_WKUSecondsConfig(uint8_t nPeriod)
{
  /* Parameter check */
  assert_parameters(IS_RTC_WKUSEC_PERIOD(nPeriod));  

  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);

  /* Write registers */
  RTC->WKUSEC = nPeriod - 1;

  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();  
}

/*
  * @brief  Configures Multi-minute wake up function.
  * @param  nPeriod£ºN minute interval.
  * @note   For the first interrupt generated by calling this function, it may 
  *         have < 1 min error if the new WKUMIN number(parameter) is not equal 
  *         to current WKUMIN number.  If the new WKUMIN is equal to current WKUMIN, 
  *         the first interrupt time may have 0~(WKUMIN +1) variation.  
  *         To avoid this problem, set an alternative parameter (like 1) by calling
  *         this function, then set the correct parameter to it.
  * @retval None
  */
void RTC_WKUMinutesConfig(uint8_t nPeriod)
{
  /* Parameter check */
  assert_parameters(IS_RTC_WKUMIN_PERIOD(nPeriod)); 

  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);

  /* Write registers */
  RTC->WKUMIN = nPeriod - 1;

  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();  
}

/*
  * @brief  Configures Multi-hour wake up function.
  * @param  nPeriod£ºN hour interval.
  * @note   For the first interrupt generated by calling this function, it may 
  *         have < 1 hour error if the new WKUHOUR number(parameter) is not equal 
  *         to current WKUHOUR number.  If the new WKUHOUR is equal to current WKUHOUR, 
  *         the first interrupt time may have 0~(WKUHOUR +1) variation.  
  *         To avoid this problem, set an alternative parameter (like 1) by calling
  *         this function, then set the correct parameter to it.
  * @retval None
  */
void RTC_WKUHoursConfig(uint8_t nPeriod)
{
  /* Parameter check */
  assert_parameters(IS_RTC_WKUHOUR_PERIOD(nPeriod));

  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);

  /* Write registers */
  RTC->WKUHOUR = nPeriod - 1;

  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro(); 
}

/**
  * @brief  Configures RTC counter wake up function.
  * @param  nClock: 
            CNTCLK:
                RTC_WKUCNT_RTCCLK
                RTC_WKUCNT_2048
                RTC_WKUCNT_512
                RTC_WKUCNT_128
  * @retval None
  */
void RTC_WKUCounterConfig(uint32_t nClock,uint32_t CNTCLK)
{
  /* Parameter check */
  assert_parameters(IS_RTC_WKUCNT_PERIOD(nClock));
  assert_parameters(IS_RTC_WKUCNT_CNTSEL(CNTCLK));

  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);

  /* Write registers */
  RTC->WKUCNT = (CNTCLK & RTC_WKUCNT_CNTSEL) | ((nClock & RTC_WKUCNT_WKUCNT) -1 );

  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();   
}

/**
  * @brief  Configures RTC ITV wake up function.
  * @param  nType:
              RTC_ITV_SEC
              RTC_ITV_MIN
              RTC_ITV_HOUR
              RTC_ITV_DAY
              RTC_ITV_500MS
              RTC_ITV_250MS 
              RTC_ITV_125MS 
              RTC_ITV_62MS
  * @retval None
  */
void RTC_WAKE_ITV(uint8_t nType)
{
  /* Parameter check */
  assert_parameters(IS_RTC_ITV(nType));

  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);
    
  RTC->ITV = nType;
  RTC->SITV = 0;

  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();  
}

/**
  * @brief  Configures RTC SITV wake up function.
  * @param  nPeriod:1~63
  * @retval None
  */
void RTC_WAKE_SITV(uint8_t nPeriod)
{
  /* Parameter check */
  assert_parameters(IS_RTC_SITV(nPeriod));

  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);

  RTC->ITV = RTC_ITV_SITVSEC;
  RTC->SITV = RTC_SITV_SITVEN | (nPeriod - 1);

  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();  
}

/**
  * @brief  Gets RTC wake-up counter value.      
  * @retval RTC wake-up counter value
  */
uint32_t RTC_GetWKUCounterValue(void)
{
  return RTC->WKUCNTR;
}

/**
  * @brief      Configures RTC clock prescaler. 
  * @param[in]  Prescaler:
  *                     RTC_CLKDIV_1
  *                     RTC_CLKDIV_4
  * @retval     None
  */
void RTC_PrescalerConfig(uint32_t Prescaler)
{
  uint32_t tmp;
  
  /* Parameter check */
  assert_parameters(IS_RTC_CLKDIV(Prescaler));  
  
  tmp = RTC->PSCA;
  tmp &= ~RTC_PSCA_PSCA;
  tmp |= Prescaler;

  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();
  /* Disable RTC Registers write-protection */
  RTC_WriteProtection(DISABLE);

  RTC->PSCA = tmp;

  /* Enable RTC Registers write-protection */
  RTC_WriteProtection(ENABLE);
  /* Wait until the RTC registers be synchronized */
  RTC_WaitForSynchro();   
}

/**
  * @brief  Configures RTC PLLDIV clock-source and frequency.
  * @param  Source:
                RTC_PLLDIVSOURCE_PLLL
                RTC_PLLDIVSOURCE_PCLK
            nfrequency(HZ): the frequency of RTC PLLDIV output configuration.
  * @note   Ensure clocks be configured by calling function CLK_ClockConfig(), 
  *         get correct PCLK frequency by calling function CLK_GetPCLKFreq().
  * @retval None
  */
void RTC_PLLDIVConfig(uint32_t DIVSource,uint32_t nfrequency)
{
  /* Parameter check */
  assert_parameters(IS_RTC_PLLDIVSOURCE(DIVSource));
  
  if (DIVSource == RTC_PLLDIVSOURCE_PLLL)
  {
    RTC->CTL |= RTC_CTL_RTCPLLCLKSEL;
    if (nfrequency == 0)
    {
      RTC->DIV = RTC_DIV_RTCDIV;
    }
    else
    {
      RTC->DIV = CLK_GetPLLLFreq()/2/nfrequency - 1;
    }
  }
  else
  {
    RTC->CTL &= ~RTC_CTL_RTCPLLCLKSEL;
    if (nfrequency == 0)
    {
      RTC->DIV = RTC_DIV_RTCDIV;
    }
    else
    {
      RTC->DIV = CLK_GetPLLLFreq()/2/nfrequency - 1;
    }
  }
}

/**
  * @brief  Enables or disables RTC PLLDIV output function.
  * @param  NewState:
  *             ENABLE
  *             DISABLE
  * @retval None
  */
void RTC_PLLDIVOutputCmd(uint8_t NewState)
{
  /* Parameter check */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)   RTC->CTL |= RTC_CTL_RTCPLLOE;
  else                      RTC->CTL &= ~RTC_CTL_RTCPLLOE;
}


/*********************************** END OF FILE ******************************/
