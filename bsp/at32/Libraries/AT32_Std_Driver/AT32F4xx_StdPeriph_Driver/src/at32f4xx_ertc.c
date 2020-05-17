/**
 **************************************************************************
 * File Name    : at32f4xx_ertc.c
 * Description  : at32f4xx ERTC source file
 * Date         : 2018-03-15
 * Version      : V1.0.4
 **************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_ertc.h"
#include "at32f4xx_rcc.h"
/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup ERTC 
  * @brief ERTC driver modules
  * @{
  */

#if defined (AT32F415xx)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Masks Definition */
#define ERTC_TIME_RESERVED_MASK    ((uint32_t)0x007F7F7F)
#define ERTC_DATE_RESERVED_MASK    ((uint32_t)0x00FFFF3F) 
#define ERTC_INIT_MASK             ((uint32_t)0xFFFFFFFF)  
#define ERTC_RSF_MASK              ((uint32_t)0xFFFFFF5F)
#define ERTC_FLAGS_MASK            ((uint32_t)(ERTC_FLAG_TSOF | ERTC_FLAG_TSF | ERTC_FLAG_WATF | \
                                            ERTC_FLAG_ALBF | ERTC_FLAG_ALAF | ERTC_FLAG_INITF | \
                                            ERTC_FLAG_RSF | ERTC_FLAG_INITS | ERTC_FLAG_WATWF | \
                                            ERTC_FLAG_ALBWF | ERTC_FLAG_ALAWF | ERTC_FLAG_TP1F | \
                                            ERTC_FLAG_TP2F | ERTC_FLAG_RECALPDF | ERTC_FLAG_SFP))

#define INITMODE_TMROUT           ((uint32_t) 0x00010000)
#define SYNCHRO_TMROUT            ((uint32_t) 0x00020000)
#define RECALPDF_TMROUT           ((uint32_t) 0x00020000)
#define SFP_TMROUT                ((uint32_t) 0x00001000)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t ERTC_ByteToBcd2(uint8_t Value);
static uint8_t ERTC_Bcd2ToByte(uint8_t Value);

/* Private functions ---------------------------------------------------------*/

/** @defgroup RTC_Private_Functions
  * @{
  */ 


/**
  * @brief  Deinitializes the ERTC registers to their default reset values.
  * @note   This function doesn't reset the ERTC Clock source and ERTC Backup Data
  *         registers.       
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ERTC registers are deinitialized
  *          - ERROR: ERTC registers are not deinitialized
  */
ErrorStatus ERTC_Reset(void)
{
  __IO uint32_t wutcounter = 0x00;
  uint32_t wutwfstatus = 0x00;
  ErrorStatus status = ERROR;
  
  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;

  /* Set Initialization mode */
  if (ERTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
  }  
  else
  {
    /* Reset TIME, DATE and CTRL registers */
    ERTC->TIME = (uint32_t)0x00000000;
    ERTC->DATE = (uint32_t)0x00002101;
    /* Reset All CTRL bits except CTRL[2:0] */
    ERTC->CTRL &= (uint32_t)0x00000007;
  
    /* Wait till ERTC WUTWF flag is set and if Time out is reached exit */
    do
    {
      wutwfstatus = ERTC->ISTS & ERTC_ISTS_WATWF;
      wutcounter++;  
    } while((wutcounter != INITMODE_TMROUT) && (wutwfstatus == 0x00));
    
    if ((ERTC->ISTS & ERTC_ISTS_WATWF) == RESET)
    {
      status = ERROR;
    }
    else
    {
      /* Reset all ERTC CTRL register bits */
      ERTC->CTRL &= (uint32_t)0x00000000;
      ERTC->WATR  = (uint32_t)0x0000FFFF;
      ERTC->PSC   = (uint32_t)0x007F00FF;
      ERTC->CAL   = (uint32_t)0x00000000;
      ERTC->ALA   = (uint32_t)0x00000000;        
      ERTC->ALB   = (uint32_t)0x00000000;
      ERTC->SFCTR = (uint32_t)0x00000000;
      ERTC->CCR   = (uint32_t)0x00000000;
      ERTC->ALASBS = (uint32_t)0x00000000;
      ERTC->ALBSBS = (uint32_t)0x00000000;
      
      /* Reset ISTS register and exit initialization mode */
      ERTC->ISTS = (uint32_t)0x00000000;
      
      /* Reset Tamper and alternate functions configuration register */
      ERTC->TPAF = 0x00000000;
  
      if(ERTC_WaitForSynchro() == ERROR)
      {
        status = ERROR;
      }
      else
      {
        status = SUCCESS;      
      }
    }
  }
  
  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF;  
  
  return status;
}

/**
  * @brief  Initializes the ERTC registers according to the specified parameters 
  *         in ERTC_InitStruct.
  * @param  ERTC_InitStruct: pointer to a ERTC_InitType structure that contains 
  *         the configuration information for the ERTC peripheral.
  * @note   The ERTC Prescaler register is write protected and can be written in 
  *         initialization mode only.  
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ERTC registers are initialized
  *          - ERROR: ERTC registers are not initialized  
  */
ErrorStatus ERTC_Init(ERTC_InitType* ERTC_InitStruct)
{
  ErrorStatus status = ERROR;
  
  /* Check the parameters */
  assert_param(IS_ERTC_HOUR_FORMAT(ERTC_InitStruct->ERTC_HourFormat));
  assert_param(IS_ERTC_ASYNCH_PRDIV(ERTC_InitStruct->ERTC_AsynchPrediv));
  assert_param(IS_ERTC_SYNCH_PRDIV(ERTC_InitStruct->ERTC_SynchPrediv));

  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;

  /* Set Initialization mode */
  if (ERTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
  } 
  else
  {
    /* Clear ERTC CTRL FMT Bit */
    ERTC->CTRL &= ((uint32_t)~(ERTC_CTRL_HFM));
    /* Set RTC_CR register */
    ERTC->CTRL |=  ((uint32_t)(ERTC_InitStruct->ERTC_HourFormat));
  
    /* Configure the ERTC PSC */
    ERTC->PSC = (uint32_t)(ERTC_InitStruct->ERTC_SynchPrediv);
    ERTC->PSC |= (uint32_t)(ERTC_InitStruct->ERTC_AsynchPrediv << 16);

    /* Exit Initialization mode */
    ERTC_ExitInitMode();

    status = SUCCESS;    
  }
  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF; 
  
  return status;
}

/**
  * @brief  Fills each ERTC_InitStruct member with its default value.
  * @param  ERTC_InitStruct: pointer to a ERTC_InitType structure which will be 
  *         initialized.
  * @retval None
  */
void ERTC_StructInit(ERTC_InitType* ERTC_InitStruct)
{
  /* Initialize the ERTC_HourFormat member */
  ERTC_InitStruct->ERTC_HourFormat = ERTC_HourFormat_24;
    
  /* Initialize the ERTC_AsynchPrediv member */
  ERTC_InitStruct->ERTC_AsynchPrediv = (uint32_t)0x7F;

  /* Initialize the ERTC_SynchPrediv member */
  ERTC_InitStruct->ERTC_SynchPrediv = (uint32_t)0xFF; 
}

/**
  * @brief  Enables or disables the ERTC registers write protection.
  * @note   All the ERTC registers are write protected except for RTC_ISR[13:8], 
  *         RTC_TAFCR and RTC_BKPxR.
  * @note   Writing a wrong key reactivates the write protection.
  * @note   The protection mechanism is not affected by system reset.  
  * @param  NewState: new state of the write protection.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ERTC_WriteProtectionCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
    
  if (NewState != DISABLE)
  {
    /* Enable the write protection for ERTC registers */
    ERTC->WPR = 0xFF;   
  }
  else
  {
    /* Disable the write protection for ERTC registers */
    ERTC->WPR = 0xCA;
    ERTC->WPR = 0x53;    
  }
}

/**
  * @brief  Enters the ERTC Initialization mode.
  * @note   The ERTC Initialization mode is write protected, use the 
  *         ERTC_WriteProtectionCmd(DISABLE) before calling this function.    
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ERTC is in Init mode
  *          - ERROR: ERTC is not in Init mode  
  */
ErrorStatus ERTC_EnterInitMode(void)
{
  __IO uint32_t initcounter = 0x00;
  ErrorStatus status = ERROR;
  uint32_t initstatus = 0x00;
     
  /* Check if the Initialization mode is set */
  if ((ERTC->ISTS & ERTC_ISTS_INITF) == (uint32_t)RESET)
  {
    /* Set the Initialization mode */
    ERTC->ISTS = (uint32_t)ERTC_INIT_MASK;
    
    /* Wait till ERTC is in INIT state and if Time out is reached exit */
    do
    {
      initstatus = ERTC->ISTS & ERTC_ISTS_INITF;
      initcounter++;  
    } while((initcounter != INITMODE_TMROUT) && (initstatus == 0x00));
    
    if ((ERTC->ISTS & ERTC_ISTS_INITF) != RESET)
    {
      status = SUCCESS;
    }
    else
    {
      status = ERROR;
    }        
  }
  else
  {
    status = SUCCESS;  
  } 
    
  return (status);  
}

/**
  * @brief  Exits the ERTC Initialization mode.
  * @note   When the initialization sequence is complete, the calendar restarts 
  *         counting after 4 RTCCLK cycles.  
  * @note   The ERTC Initialization mode is write protected, use the 
  *         ERTC_WriteProtectionCmd(DISABLE) before calling this function.      
  * @param  None
  * @retval None
  */
void ERTC_ExitInitMode(void)
{ 
  /* Exit Initialization mode */
  ERTC->ISTS &= (uint32_t)~ERTC_ISTS_INITM;  
}

/**
  * @brief  Waits until the ERTC Time and Date registers (RTC_TR and RTC_DR) are 
  *         synchronized with ERTC APB clock.
  * @note   The ERTC Resynchronization mode is write protected, use the 
  *         ERTC_WriteProtectionCmd(DISABLE) before calling this function. 
  * @note   To read the calendar through the shadow registers after Calendar 
  *         initialization, calendar update or after wakeup from low power modes 
  *         the software must first clear the RSF flag. 
  *         The software must then wait until it is set again before reading 
  *         the calendar, which means that the calendar registers have been 
  *         correctly copied into the RTC_TR and RTC_DR shadow registers.   
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ERTC registers are synchronised
  *          - ERROR: ERTC registers are not synchronised
  */
ErrorStatus ERTC_WaitForSynchro(void)
{
  __IO uint32_t synchrocounter = 0;
  ErrorStatus status = ERROR;
  uint32_t synchrostatus = 0x00;

  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;
    
  /* Clear RSF flag */
  ERTC->ISTS &= (uint32_t)ERTC_RSF_MASK;
    
  /* Wait the registers to be synchronised */
  do
  {
    synchrostatus = ERTC->ISTS & ERTC_ISTS_RSF;
    synchrocounter++;  
  } while((synchrocounter != SYNCHRO_TMROUT) && (synchrostatus == 0x00));
    
  if ((ERTC->ISTS & ERTC_ISTS_RSF) != RESET)
  {
    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }        

  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF; 
    
  return (status); 
}

/**
  * @brief  Enables or disables the ERTC reference clock detection.
  * @param  NewState: new state of the ERTC reference clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ERTC reference clock detection is enabled
  *          - ERROR: ERTC reference clock detection is disabled  
  */
ErrorStatus ERTC_RefClockCmd(FunctionalState NewState)
{ 
  ErrorStatus status = ERROR;
  
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;
    
  /* Set Initialization mode */
  if (ERTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
  } 
  else
  {  
    if (NewState != DISABLE)
    {
      /* Enable the ERTC reference clock detection */
      ERTC->CTRL |= ERTC_CTRL_RFCKON;   
    }
    else
    {
      /* Disable the ERTC reference clock detection */
      ERTC->CTRL &= ~ERTC_CTRL_RFCKON;    
    }
    /* Exit Initialization mode */
    ERTC_ExitInitMode();
    
    status = SUCCESS;
  }
  
  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF;  
  
  return status; 
}

/**
  * @brief  Enables or Disables the Bypass Shadow feature.
  * @note   When the Bypass Shadow is enabled the calendar value are taken 
  *         directly from the Calendar counter.
  * @param  NewState: new state of the Bypass Shadow feature.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
*/
void ERTC_BypassShadowCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;
  
  if (NewState != DISABLE)
  {
    /* Set the BYPSHAD bit */
    ERTC->CTRL |= (uint8_t)ERTC_CTRL_BYPSHDW;
  }
  else
  {
    /* Reset the BYPSHAD bit */
    ERTC->CTRL &= (uint8_t)~ERTC_CTRL_BYPSHDW;
  }

  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF;
}

/**
  * @}
  */

/** @defgroup RTC_Group2 Time and Date configuration functions
 *  @brief   Time and Date configuration functions 
 *
@verbatim   
 ===============================================================================
                 ##### Time and Date configuration functions #####
 ===============================================================================  
 
 [..] This section provide functions allowing to program and read the ERTC Calendar
      (Time and Date).

@endverbatim
  * @{
  */

/**
  * @brief  Set the ERTC current time.
  * @param  ERTC_Format: specifies the format of the entered parameters.
  *          This parameter can be  one of the following values:
  *            @arg ERTC_Format_BIN:  Binary data format 
  *            @arg ERTC_Format_BCD:  BCD data format
  * @param  ERTC_TimeStruct: pointer to a ERTC_TimeType structure that contains 
  *                        the time configuration information for the ERTC.     
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ERTC Time register is configured
  *          - ERROR: ERTC Time register is not configured
  */
ErrorStatus ERTC_SetTimeValue(uint32_t ERTC_Format, ERTC_TimeType* ERTC_TimeStruct)
{
  uint32_t tmpreg = 0;
  ErrorStatus status = ERROR;
    
  /* Check the parameters */
  assert_param(IS_ERTC_FORMAT(ERTC_Format));
  
  if (ERTC_Format == ERTC_Format_BIN)
  {
    if ((ERTC->CTRL & ERTC_CTRL_HFM) != (uint32_t)RESET)
    {
      assert_param(IS_ERTC_HOUR12(ERTC_TimeStruct->ERTC_Hours));
      assert_param(IS_ERTC_H12(ERTC_TimeStruct->ERTC_AMPM));
    } 
    else
    {
      ERTC_TimeStruct->ERTC_AMPM = 0x00;
      assert_param(IS_ERTC_HOUR24(ERTC_TimeStruct->ERTC_Hours));
    }
    assert_param(IS_ERTC_MINUTES(ERTC_TimeStruct->ERTC_Minutes));
    assert_param(IS_ERTC_SECONDS(ERTC_TimeStruct->ERTC_Seconds));
  }
  else
  {
    if ((ERTC->CTRL & ERTC_CTRL_HFM) != (uint32_t)RESET)
    {
      tmpreg = ERTC_Bcd2ToByte(ERTC_TimeStruct->ERTC_Hours);
      assert_param(IS_ERTC_HOUR12(tmpreg));
      assert_param(IS_ERTC_H12(ERTC_TimeStruct->ERTC_AMPM)); 
    } 
    else
    {
      ERTC_TimeStruct->ERTC_AMPM = 0x00;
      assert_param(IS_ERTC_HOUR24(ERTC_Bcd2ToByte(ERTC_TimeStruct->ERTC_Hours)));
    }
    assert_param(IS_ERTC_MINUTES(ERTC_Bcd2ToByte(ERTC_TimeStruct->ERTC_Minutes)));
    assert_param(IS_ERTC_SECONDS(ERTC_Bcd2ToByte(ERTC_TimeStruct->ERTC_Seconds)));
  }
  
  /* Check the input parameters format */
  if (ERTC_Format != ERTC_Format_BIN)
  {
    tmpreg = (((uint32_t)(ERTC_TimeStruct->ERTC_Hours) << 16) | \
             ((uint32_t)(ERTC_TimeStruct->ERTC_Minutes) << 8) | \
             ((uint32_t)ERTC_TimeStruct->ERTC_Seconds) | \
             ((uint32_t)(ERTC_TimeStruct->ERTC_AMPM) << 16)); 
  }  
  else
  {
    tmpreg = (uint32_t)(((uint32_t)ERTC_ByteToBcd2(ERTC_TimeStruct->ERTC_Hours) << 16) | \
                   ((uint32_t)ERTC_ByteToBcd2(ERTC_TimeStruct->ERTC_Minutes) << 8) | \
                   ((uint32_t)ERTC_ByteToBcd2(ERTC_TimeStruct->ERTC_Seconds)) | \
                   (((uint32_t)ERTC_TimeStruct->ERTC_AMPM) << 16));
  }  

  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;

  /* Set Initialization mode */
  if (ERTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
  } 
  else
  {
    /* Set the RTC_TR register */
    ERTC->TIME = (uint32_t)(tmpreg & ERTC_TIME_RESERVED_MASK);

    /* Exit Initialization mode */
    ERTC_ExitInitMode(); 

    /* If  ERTC_CTRL_BYPSHDW bit = 0, wait for synchro else this check is not needed */
    if ((ERTC->CTRL & ERTC_CTRL_BYPSHDW) == RESET)
    {
    if(ERTC_WaitForSynchro() == ERROR)
    {
      status = ERROR;
    }
    else
    {
      status = SUCCESS;
    }
  }
    else
    {
      status = SUCCESS;
    }
  }
  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF; 
    
  return status;
}

/**
  * @brief  Fills each ERTC_TimeStruct member with its default value
  *         (Time = 00h:00min:00sec).
  * @param  ERTC_TimeStruct: pointer to a ERTC_TimeType structure which will be 
  *         initialized.
  * @retval None
  */
void ERTC_TimeStructInit(ERTC_TimeType* ERTC_TimeStruct)
{
  /* Time = 00h:00min:00sec */
  ERTC_TimeStruct->ERTC_AMPM = ERTC_H12_AM;
  ERTC_TimeStruct->ERTC_Hours = 0;
  ERTC_TimeStruct->ERTC_Minutes = 0;
  ERTC_TimeStruct->ERTC_Seconds = 0; 
}

/**
  * @brief  Get the ERTC current Time.
  * @param  ERTC_Format: specifies the format of the returned parameters.
  *          This parameter can be  one of the following values:
  *            @arg ERTC_Format_BIN:  Binary data format 
  *            @arg ERTC_Format_BCD:  BCD data format
  * @param  ERTC_TimeStruct: pointer to a ERTC_TimeType structure that will 
  *                        contain the returned current time configuration.     
  * @retval None
  */
void ERTC_GetTimeValue(uint32_t ERTC_Format, ERTC_TimeType* ERTC_TimeStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_ERTC_FORMAT(ERTC_Format));

  /* Get the RTC_TR register */
  tmpreg = (uint32_t)(ERTC->TIME & ERTC_TIME_RESERVED_MASK); 
  
  /* Fill the structure fields with the read parameters */
  ERTC_TimeStruct->ERTC_Hours = (uint8_t)((tmpreg & (ERTC_TIME_HT | ERTC_TIME_HU)) >> 16);
  ERTC_TimeStruct->ERTC_Minutes = (uint8_t)((tmpreg & (ERTC_TIME_MT | ERTC_TIME_MU)) >>8);
  ERTC_TimeStruct->ERTC_Seconds = (uint8_t)(tmpreg & (ERTC_TIME_ST | ERTC_TIME_SU));
  ERTC_TimeStruct->ERTC_AMPM = (uint8_t)((tmpreg & (ERTC_TIME_AMPM)) >> 16);  

  /* Check the input parameters format */
  if (ERTC_Format == ERTC_Format_BIN)
  {
    /* Convert the structure parameters to Binary format */
    ERTC_TimeStruct->ERTC_Hours = (uint8_t)ERTC_Bcd2ToByte(ERTC_TimeStruct->ERTC_Hours);
    ERTC_TimeStruct->ERTC_Minutes = (uint8_t)ERTC_Bcd2ToByte(ERTC_TimeStruct->ERTC_Minutes);
    ERTC_TimeStruct->ERTC_Seconds = (uint8_t)ERTC_Bcd2ToByte(ERTC_TimeStruct->ERTC_Seconds);   
  }
}

/**
  * @brief  Gets the ERTC current Calendar Sub seconds value.
  * @note   This function freeze the Time and Date registers after reading the 
  *         SBSR register.
  * @param  None
  * @retval ERTC current Calendar Sub seconds value.
  */
uint32_t ERTC_GetSubSecondValue(void)
{
  uint32_t tmpreg = 0;
  
  /* Get sub seconds values from the correspondent registers*/
  tmpreg = (uint32_t)(ERTC->SBSR);
  
  /* Read DATE register to unfroze calendar registers */
  (void) (ERTC->DATE);
  
  return (tmpreg);
}

/**
  * @brief  Set the ERTC current date.
  * @param  ERTC_Format: specifies the format of the entered parameters.
  *          This parameter can be  one of the following values:
  *            @arg ERTC_Format_BIN:  Binary data format 
  *            @arg ERTC_Format_BCD:  BCD data format
  * @param  ERTC_DateStruct: pointer to a ERTC_DateType structure that contains 
  *                         the date configuration information for the ERTC.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ERTC Date register is configured
  *          - ERROR: ERTC Date register is not configured
  */
ErrorStatus ERTC_SetDateValue(uint32_t ERTC_Format, ERTC_DateType* ERTC_DateStruct)
{
  uint32_t tmpreg = 0;
  ErrorStatus status = ERROR;
  
  /* Check the parameters */
  assert_param(IS_ERTC_FORMAT(ERTC_Format));

  if ((ERTC_Format == ERTC_Format_BIN) && ((ERTC_DateStruct->ERTC_Month & 0x10) == 0x10))
  {
    ERTC_DateStruct->ERTC_Month = (ERTC_DateStruct->ERTC_Month & (uint32_t)~(0x10)) + 0x0A;
  }  
  if (ERTC_Format == ERTC_Format_BIN)
  {
    assert_param(IS_ERTC_YEAR(ERTC_DateStruct->ERTC_Year));
    assert_param(IS_ERTC_MONTH(ERTC_DateStruct->ERTC_Month));
    assert_param(IS_ERTC_DATE(ERTC_DateStruct->ERTC_Date));
  }
  else
  {
    assert_param(IS_ERTC_YEAR(ERTC_Bcd2ToByte(ERTC_DateStruct->ERTC_Year)));
    tmpreg = ERTC_Bcd2ToByte(ERTC_DateStruct->ERTC_Month);
    assert_param(IS_ERTC_MONTH(tmpreg));
    tmpreg = ERTC_Bcd2ToByte(ERTC_DateStruct->ERTC_Date);
    assert_param(IS_ERTC_DATE(tmpreg));
  }
  assert_param(IS_ERTC_WEEK(ERTC_DateStruct->ERTC_WeekDay));

  /* Check the input parameters format */
  if (ERTC_Format != ERTC_Format_BIN)
  {
    tmpreg = ((((uint32_t)ERTC_DateStruct->ERTC_Year) << 16) | \
              (((uint32_t)ERTC_DateStruct->ERTC_Month) << 8) | \
              ((uint32_t)ERTC_DateStruct->ERTC_Date) | \
              (((uint32_t)ERTC_DateStruct->ERTC_WeekDay) << 13)); 
  }  
  else
  {
    tmpreg = (((uint32_t)ERTC_ByteToBcd2(ERTC_DateStruct->ERTC_Year) << 16) | \
              ((uint32_t)ERTC_ByteToBcd2(ERTC_DateStruct->ERTC_Month) << 8) | \
              ((uint32_t)ERTC_ByteToBcd2(ERTC_DateStruct->ERTC_Date)) | \
              ((uint32_t)ERTC_DateStruct->ERTC_WeekDay << 13));
  }

  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;

  /* Set Initialization mode */
  if (ERTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
  } 
  else
  {
    /* Set the RTC_DR register */
    ERTC->DATE = (uint32_t)(tmpreg & ERTC_DATE_RESERVED_MASK);

    /* Exit Initialization mode */
    ERTC_ExitInitMode(); 

    /* If  ERTC_CTRL_BYPSHDW bit = 0, wait for synchro else this check is not needed */
    if ((ERTC->CTRL & ERTC_CTRL_BYPSHDW) == RESET)
    {
    if(ERTC_WaitForSynchro() == ERROR)
    {
      status = ERROR;
    }
    else
    {
      status = SUCCESS;
    }
  }
    else
    {
      status = SUCCESS;
    }
  }
  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF;   
  
  return status;
}

/**
  * @brief  Fills each ERTC_DateStruct member with its default value
  *         (Monday, January 01 xx00).
  * @param  ERTC_DateStruct: pointer to a ERTC_DateType structure which will be 
  *         initialized.
  * @retval None
  */
void ERTC_DateStructInit(ERTC_DateType* ERTC_DateStruct)
{
  /* Monday, January 01 xx00 */
  ERTC_DateStruct->ERTC_WeekDay = ERTC_Week_MON;
  ERTC_DateStruct->ERTC_Date = 1;
  ERTC_DateStruct->ERTC_Month = ERTC_Month_JAN;
  ERTC_DateStruct->ERTC_Year = 0;
}

/**
  * @brief  Get the ERTC current date. 
  * @param  ERTC_Format: specifies the format of the returned parameters.
  *          This parameter can be one of the following values:
  *            @arg ERTC_Format_BIN: Binary data format 
  *            @arg ERTC_Format_BCD: BCD data format
  * @param ERTC_DateStruct: pointer to a ERTC_DateType structure that will 
  *                        contain the returned current date configuration.     
  * @retval None
  */
void ERTC_GetDateValue(uint32_t ERTC_Format, ERTC_DateType* ERTC_DateStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_ERTC_FORMAT(ERTC_Format));
  
  /* Get the RTC_TR register */
  tmpreg = (uint32_t)(ERTC->DATE & ERTC_DATE_RESERVED_MASK); 

  /* Fill the structure fields with the read parameters */
  ERTC_DateStruct->ERTC_Year = (uint8_t)((tmpreg & (ERTC_DATE_YT | ERTC_DATE_YU)) >> 16);
  ERTC_DateStruct->ERTC_Month = (uint8_t)((tmpreg & (ERTC_DATE_MT | ERTC_DATE_MU)) >> 8);
  ERTC_DateStruct->ERTC_Date = (uint8_t)(tmpreg & (ERTC_DATE_DT | ERTC_DATE_DU));
  ERTC_DateStruct->ERTC_WeekDay = (uint8_t)((tmpreg & (ERTC_DATE_WK)) >> 13);

  /* Check the input parameters format */
  if (ERTC_Format == ERTC_Format_BIN)
  {
    /* Convert the structure parameters to Binary format */
    ERTC_DateStruct->ERTC_Year = (uint8_t)ERTC_Bcd2ToByte(ERTC_DateStruct->ERTC_Year);
    ERTC_DateStruct->ERTC_Month = (uint8_t)ERTC_Bcd2ToByte(ERTC_DateStruct->ERTC_Month);
    ERTC_DateStruct->ERTC_Date = (uint8_t)ERTC_Bcd2ToByte(ERTC_DateStruct->ERTC_Date);
  }
}

/**
  * @}
  */

/** @defgroup RTC_Group3 Alarms configuration functions
 *  @brief   Alarms (Alarm A and Alarm B) configuration functions 
 *
@verbatim   
 ===============================================================================
         ##### Alarms A and B configuration functions #####
 ===============================================================================  
 
 [..] This section provide functions allowing to program and read the ERTC Alarms.

@endverbatim
  * @{
  */

/**
  * @brief  Set the specified ERTC Alarm.
  * @note   The Alarm register can only be written when the corresponding Alarm
  *         is disabled (Use the ERTC_AlarmCmd(DISABLE)).    
  * @param  ERTC_Format: specifies the format of the returned parameters.
  *          This parameter can be one of the following values:
  *            @arg ERTC_Format_BIN: Binary data format 
  *            @arg ERTC_Format_BCD: BCD data format
  * @param  ERTC_Alarm: specifies the alarm to be configured.
  *          This parameter can be one of the following values:
  *            @arg ERTC_AlA: to select Alarm A
  *            @arg ERTC_AlB: to select Alarm B  
  * @param  ERTC_AlarmStruct: pointer to a ERTC_AlarmType structure that 
  *                          contains the alarm configuration parameters.     
  * @retval None
  */
void ERTC_SetAlarmValue(uint32_t ERTC_Format, uint32_t ERTC_Alarm, ERTC_AlarmType* ERTC_AlarmStruct)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_ERTC_FORMAT(ERTC_Format));
  assert_param(IS_ERTC_ALARM(ERTC_Alarm));
  assert_param(IS_ALARM_MASK(ERTC_AlarmStruct->ERTC_AlarmMask));
  assert_param(IS_ERTC_ALARM_DATE_WEEK_SEL(ERTC_AlarmStruct->ERTC_AlarmDateWeekSel));

  if (ERTC_Format == ERTC_Format_BIN)
  {
    if ((ERTC->CTRL & ERTC_CTRL_HFM) != (uint32_t)RESET)
    {
      assert_param(IS_ERTC_HOUR12(ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Hours));
      assert_param(IS_ERTC_H12(ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_AMPM));
    } 
    else
    {
      ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_AMPM = 0x00;
      assert_param(IS_ERTC_HOUR24(ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Hours));
    }
    assert_param(IS_ERTC_MINUTES(ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Minutes));
    assert_param(IS_ERTC_SECONDS(ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Seconds));
    
    if(ERTC_AlarmStruct->ERTC_AlarmDateWeekSel == ERTC_AlarmDateWeekSel_Date)
    {
      assert_param(IS_ERTC_ALARM_DATE_WEEK_DATE(ERTC_AlarmStruct->ERTC_AlarmDateWeek));
    }
    else
    {
      assert_param(IS_ERTC_ALARM_DATE_WEEK_WEEK(ERTC_AlarmStruct->ERTC_AlarmDateWeek));
    }
  }
  else
  {
    if ((ERTC->CTRL & ERTC_CTRL_HFM) != (uint32_t)RESET)
    {
      tmpreg = ERTC_Bcd2ToByte(ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Hours);
      assert_param(IS_ERTC_HOUR12(tmpreg));
      assert_param(IS_ERTC_H12(ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_AMPM));
    } 
    else
    {
      ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_AMPM = 0x00;
      assert_param(IS_ERTC_HOUR24(ERTC_Bcd2ToByte(ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Hours)));
    }
    
    assert_param(IS_ERTC_MINUTES(ERTC_Bcd2ToByte(ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Minutes)));
    assert_param(IS_ERTC_SECONDS(ERTC_Bcd2ToByte(ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Seconds)));
    
    if(ERTC_AlarmStruct->ERTC_AlarmDateWeekSel == ERTC_AlarmDateWeekSel_Date)
    {
      tmpreg = ERTC_Bcd2ToByte(ERTC_AlarmStruct->ERTC_AlarmDateWeek);
      assert_param(IS_ERTC_ALARM_DATE_WEEK_DATE(tmpreg));    
    }
    else
    {
      tmpreg = ERTC_Bcd2ToByte(ERTC_AlarmStruct->ERTC_AlarmDateWeek);
      assert_param(IS_ERTC_ALARM_DATE_WEEK_WEEK(tmpreg));      
    }    
  }

  /* Check the input parameters format */
  if (ERTC_Format != ERTC_Format_BIN)
  {
    tmpreg = (((uint32_t)(ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Hours) << 16) | \
              ((uint32_t)(ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Minutes) << 8) | \
              ((uint32_t)ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Seconds) | \
              ((uint32_t)(ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_AMPM) << 16) | \
              ((uint32_t)(ERTC_AlarmStruct->ERTC_AlarmDateWeek) << 24) | \
              ((uint32_t)ERTC_AlarmStruct->ERTC_AlarmDateWeekSel) | \
              ((uint32_t)ERTC_AlarmStruct->ERTC_AlarmMask)); 
  }  
  else
  {
    tmpreg = (((uint32_t)ERTC_ByteToBcd2(ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Hours) << 16) | \
              ((uint32_t)ERTC_ByteToBcd2(ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Minutes) << 8) | \
              ((uint32_t)ERTC_ByteToBcd2(ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Seconds)) | \
              ((uint32_t)(ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_AMPM) << 16) | \
              ((uint32_t)ERTC_ByteToBcd2(ERTC_AlarmStruct->ERTC_AlarmDateWeek) << 24) | \
              ((uint32_t)ERTC_AlarmStruct->ERTC_AlarmDateWeekSel) | \
              ((uint32_t)ERTC_AlarmStruct->ERTC_AlarmMask)); 
  } 

  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;

  /* Configure the Alarm register */
  if (ERTC_Alarm == ERTC_AlA)
  {
    ERTC->ALA = (uint32_t)tmpreg;
  }
  else
  {
    ERTC->ALB = (uint32_t)tmpreg;
  }

  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF;   
}

/**
  * @brief  Fills each ERTC_AlarmStruct member with its default value
  *         (Time = 00h:00mn:00sec / Date = 1st day of the month/Mask =
  *         all fields are masked).
  * @param  ERTC_AlarmStruct: pointer to a @ref ERTC_AlarmType structure which
  *         will be initialized.
  * @retval None
  */
void ERTC_AlarmStructInit(ERTC_AlarmType* ERTC_AlarmStruct)
{
  /* Alarm Time Settings : Time = 00h:00mn:00sec */
  ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_AMPM = ERTC_H12_AM;
  ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Hours = 0;
  ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Minutes = 0;
  ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Seconds = 0;

  /* Alarm Date Settings : Date = 1st day of the month */
  ERTC_AlarmStruct->ERTC_AlarmDateWeekSel = ERTC_AlarmDateWeekSel_Date;
  ERTC_AlarmStruct->ERTC_AlarmDateWeek = 1;

  /* Alarm Masks Settings : Mask =  all fields are not masked */
  ERTC_AlarmStruct->ERTC_AlarmMask = ERTC_AlarmMask_None;
}

/**
  * @brief  Get the ERTC Alarm value and masks.
  * @param  ERTC_Format: specifies the format of the output parameters.
  *          This parameter can be one of the following values:
  *            @arg ERTC_Format_BIN: Binary data format 
  *            @arg ERTC_Format_BCD: BCD data format
  * @param  ERTC_Alarm: specifies the alarm to be read.
  *          This parameter can be one of the following values:
  *            @arg ERTC_AlA: to select Alarm A
  *            @arg ERTC_AlB: to select Alarm B  
  * @param  ERTC_AlarmStruct: pointer to a ERTC_AlarmType structure that will 
  *                          contains the output alarm configuration values.     
  * @retval None
  */
void ERTC_GetAlarmValue(uint32_t ERTC_Format, uint32_t ERTC_Alarm, ERTC_AlarmType* ERTC_AlarmStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_ERTC_FORMAT(ERTC_Format));
  assert_param(IS_ERTC_ALARM(ERTC_Alarm)); 

  /* Get the RTC_ALRMxR register */
  if (ERTC_Alarm == ERTC_AlA)
  {
    tmpreg = (uint32_t)(ERTC->ALA);
  }
  else
  {
    tmpreg = (uint32_t)(ERTC->ALB);
  }

  /* Fill the structure with the read parameters */
  ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Hours = (uint32_t)((tmpreg & (ERTC_ALA_HT | \
                                                     ERTC_ALA_HU)) >> 16);
  ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Minutes = (uint32_t)((tmpreg & (ERTC_ALA_MT | \
                                                     ERTC_ALA_MU)) >> 8);
  ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Seconds = (uint32_t)(tmpreg & (ERTC_ALA_ST | \
                                                     ERTC_ALA_SU));
  ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_AMPM = (uint32_t)((tmpreg & ERTC_ALA_AMPM) >> 16);
  ERTC_AlarmStruct->ERTC_AlarmDateWeek = (uint32_t)((tmpreg & (ERTC_ALA_DT | ERTC_ALA_DU)) >> 24);
  ERTC_AlarmStruct->ERTC_AlarmDateWeekSel = (uint32_t)(tmpreg & ERTC_ALA_WKSEL);
  ERTC_AlarmStruct->ERTC_AlarmMask = (uint32_t)(tmpreg & ERTC_AlarmMask_All);

  if (ERTC_Format == ERTC_Format_BIN)
  {
    ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Hours = ERTC_Bcd2ToByte(ERTC_AlarmStruct-> \
                                                        ERTC_AlarmTime.ERTC_Hours);
    ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Minutes = ERTC_Bcd2ToByte(ERTC_AlarmStruct-> \
                                                        ERTC_AlarmTime.ERTC_Minutes);
    ERTC_AlarmStruct->ERTC_AlarmTime.ERTC_Seconds = ERTC_Bcd2ToByte(ERTC_AlarmStruct-> \
                                                        ERTC_AlarmTime.ERTC_Seconds);
    ERTC_AlarmStruct->ERTC_AlarmDateWeek = ERTC_Bcd2ToByte(ERTC_AlarmStruct->ERTC_AlarmDateWeek);
  }  
}

/**
  * @brief  Enables or disables the specified ERTC Alarm.
  * @param  ERTC_Alarm: specifies the alarm to be configured.
  *          This parameter can be any combination of the following values:
  *            @arg ERTC_AlA: to select Alarm A
  *            @arg ERTC_AlB: to select Alarm B  
  * @param  NewState: new state of the specified alarm.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ERTC Alarm is enabled/disabled
  *          - ERROR: ERTC Alarm is not enabled/disabled  
  */
ErrorStatus ERTC_AlarmCmd(uint32_t ERTC_Alarm, FunctionalState NewState)
{
  __IO uint32_t alarmcounter = 0x00;
  uint32_t alarmstatus = 0x00;
  ErrorStatus status = ERROR;
    
  /* Check the parameters */
  assert_param(IS_ERTC_CMD_ALARM(ERTC_Alarm));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;

  /* Configure the Alarm state */
  if (NewState != DISABLE)
  {
    ERTC->CTRL |= (uint32_t)ERTC_Alarm;

    status = SUCCESS;    
  }
  else
  { 
    /* Disable the Alarm in RTC_CR register */
    ERTC->CTRL &= (uint32_t)~ERTC_Alarm;
   
    /* Wait till ERTC ALRxWF flag is set and if Time out is reached exit */
    do
    {
      alarmstatus = ERTC->ISTS & (ERTC_Alarm >> 8);
      alarmcounter++;  
    } while((alarmcounter != INITMODE_TMROUT) && (alarmstatus == 0x00));
    
    if ((ERTC->ISTS & (ERTC_Alarm >> 8)) == RESET)
    {
      status = ERROR;
    } 
    else
    {
      status = SUCCESS;
    }        
  } 

  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF; 
  
  return status;
}

/**
  * @brief  Configure the ERTC AlarmA/B Sub seconds value and mask.*
  * @note   This function is performed only when the Alarm is disabled. 
  * @param  ERTC_Alarm: specifies the alarm to be configured.
  *   This parameter can be one of the following values:
  *     @arg ERTC_AlA: to select Alarm A
  *     @arg ERTC_AlB: to select Alarm B
  * @param  ERTC_AlarmSubSecondValue: specifies the Sub seconds value.
  *   This parameter can be a value from 0 to 0x00007FFF.
  * @param  ERTC_AlarmSubSecondMask:  specifies the Sub seconds Mask.
  *   This parameter can be any combination of the following values:
  *     @arg ERTC_AlarmSubSecondMask_All    : All Alarm SS fields are masked.
  *                                          There is no comparison on sub seconds for Alarm.
  *     @arg ERTC_AlarmSubSecondMask_SBS14_1 : SS[14:1] are don't care in Alarm comparison.
  *                                          Only SS[0] is compared
  *     @arg ERTC_AlarmSubSecondMask_SBS14_2 : SS[14:2] are don't care in Alarm comparison.
  *                                          Only SS[1:0] are compared
  *     @arg ERTC_AlarmSubSecondMask_SBS14_3 : SS[14:3] are don't care in Alarm comparison.
  *                                          Only SS[2:0] are compared
  *     @arg ERTC_AlarmSubSecondMask_SBS14_4 : SS[14:4] are don't care in Alarm comparison.
  *                                          Only SS[3:0] are compared
  *     @arg ERTC_AlarmSubSecondMask_SBS14_5 : SS[14:5] are don't care in Alarm comparison.
  *                                          Only SS[4:0] are compared
  *     @arg ERTC_AlarmSubSecondMask_SBS14_6 : SS[14:6] are don't care in Alarm comparison.
  *                                          Only SS[5:0] are compared
  *     @arg ERTC_AlarmSubSecondMask_SBS14_7 : SS[14:7] are don't care in Alarm comparison.
  *                                          Only SS[6:0] are compared
  *     @arg ERTC_AlarmSubSecondMask_SBS14_8 : SS[14:8] are don't care in Alarm comparison.
  *                                          Only SS[7:0] are compared
  *     @arg ERTC_AlarmSubSecondMask_SBS14_9 : SS[14:9] are don't care in Alarm comparison.
  *                                          Only SS[8:0] are compared
  *     @arg ERTC_AlarmSubSecondMask_SBS14_10: SS[14:10] are don't care in Alarm comparison.
  *                                          Only SS[9:0] are compared
  *     @arg ERTC_AlarmSubSecondMask_SBS14_11: SS[14:11] are don't care in Alarm comparison.
  *                                          Only SS[10:0] are compared
  *     @arg ERTC_AlarmSubSecondMask_SBS14_12: SS[14:12] are don't care in Alarm comparison.
  *                                          Only SS[11:0] are compared
  *     @arg ERTC_AlarmSubSecondMask_SBS14_13: SS[14:13] are don't care in Alarm comparison.
  *                                          Only SS[12:0] are compared
  *     @arg ERTC_AlarmSubSecondMask_SBS14   : SS[14] is don't care in Alarm comparison.
  *                                          Only SS[13:0] are compared
  *     @arg ERTC_AlarmSubSecondMask_None   : SS[14:0] are compared and must match
  *                                          to activate alarm
  * @retval None
  */
void ERTC_AlarmSubSecondConfig(uint32_t ERTC_Alarm, uint32_t ERTC_AlarmSubSecondValue, uint32_t ERTC_AlarmSubSecondMask)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_ERTC_ALARM(ERTC_Alarm));
  assert_param(IS_ERTC_ALARM_SUB_SECOND_VALUE(ERTC_AlarmSubSecondValue));
  assert_param(IS_ERTC_ALARM_SUB_SECOND_MASK(ERTC_AlarmSubSecondMask));
  
  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;
  
  /* Configure the Alarm A or Alarm B Sub Second registers */
  tmpreg = (uint32_t) (uint32_t)(ERTC_AlarmSubSecondValue) | (uint32_t)(ERTC_AlarmSubSecondMask);
  
  if (ERTC_Alarm == ERTC_AlA)
  {
    /* Configure the Alarm A Sub Second register */
    ERTC->ALASBS = tmpreg;
  }
  else
  {
    /* Configure the Alarm B Sub Second register */
    ERTC->ALBSBS = tmpreg;
  }

  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF;

}

/**
  * @brief  Gets the ERTC Alarm Sub seconds value.
  * @param  ERTC_Alarm: specifies the alarm to be read.
  *   This parameter can be one of the following values:
  *     @arg ERTC_AlA: to select Alarm A
  *     @arg ERTC_AlB: to select Alarm B
  * @param  None
  * @retval ERTC Alarm Sub seconds value.
  */
uint32_t ERTC_GetAlarmSubSecond(uint32_t ERTC_Alarm)
{
  uint32_t tmpreg = 0;
  
  /* Get the RTC_ALRMxR register */
  if (ERTC_Alarm == ERTC_AlA)
  {
    tmpreg = (uint32_t)((ERTC->ALASBS) & ERTC_ALASBS_SBS);
  }
  else
  {
    tmpreg = (uint32_t)((ERTC->ALBSBS) & ERTC_ALBSBS_SBS);
  } 
  
  return (tmpreg);
}

/**
  * @}
  */

/** @defgroup RTC_Group4 WakeUp Timer configuration functions
 *  @brief   WakeUp Timer configuration functions 
 *
@verbatim   
 ===============================================================================
                 ##### WakeUp Timer configuration functions #####
 ===============================================================================  

 [..] This section provide functions allowing to program and read the ERTC WakeUp.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the ERTC Wakeup clock source.
  * @note   The WakeUp Clock source can only be changed when the ERTC WakeUp
  *         is disabled (Use the ERTC_WakeUpCmd(DISABLE)).      
  * @param  ERTC_WakeUpClock: Wakeup Clock source.
  *          This parameter can be one of the following values:
  *            @arg ERTC_WakeUpClockSelect_RTCCLK_Div16: ERTC Wakeup Counter Clock = RTCCLK/16
  *            @arg ERTC_WakeUpClockSelect_RTCCLK_Div8: ERTC Wakeup Counter Clock = RTCCLK/8
  *            @arg ERTC_WakeUpClockSelect_RTCCLK_Div4: ERTC Wakeup Counter Clock = RTCCLK/4
  *            @arg ERTC_WakeUpClockSelect_RTCCLK_Div2: ERTC Wakeup Counter Clock = RTCCLK/2
  *            @arg ERTC_WakeUpClockSelect_CK_SPRE_16bits: ERTC Wakeup Counter Clock = CK_SPRE
  *            @arg ERTC_WakeUpClockSelect_CK_SPRE_17bits: ERTC Wakeup Counter Clock = CK_SPRE
  * @retval None
  */
void ERTC_WakeUpClockConfig(uint32_t ERTC_WakeUpClock)
{
  /* Check the parameters */
  assert_param(IS_ERTC_WAKEUP_CLOCK_SELECT(ERTC_WakeUpClock));

  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;

  /* Clear the Wakeup Timer clock source bits in CTRL register */
  ERTC->CTRL &= (uint32_t)~ERTC_CTRL_WACKSEL;

  /* Configure the clock source */
  ERTC->CTRL |= (uint32_t)ERTC_WakeUpClock;
  
  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF; 
}

/**
  * @brief  Configures the ERTC Wakeup counter.
  * @note   The ERTC WakeUp counter can only be written when the ERTC WakeUp
  *         is disabled (Use the ERTC_WakeUpCmd(DISABLE)).        
  * @param  ERTC_WakeUpCounter: specifies the WakeUp counter.
  *          This parameter can be a value from 0x0000 to 0xFFFF. 
  * @retval None
  */
void ERTC_SetWakeUpCounter(uint32_t ERTC_WakeUpCounter)
{
  /* Check the parameters */
  assert_param(IS_ERTC_WAKEUP_COUNTER(ERTC_WakeUpCounter));
  
  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;
  
  /* Configure the Wakeup Timer counter */
  ERTC->WATR = (uint32_t)ERTC_WakeUpCounter;
  
  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF; 
}

/**
  * @brief  Returns the ERTC WakeUp timer counter value.
  * @param  None
  * @retval The ERTC WakeUp Counter value.
  */
uint32_t ERTC_GetWakeUpCounter(void)
{
  /* Get the counter value */
  return ((uint32_t)(ERTC->WATR & ERTC_WATR_WAREV));
}

/**
  * @brief  Enables or Disables the ERTC WakeUp timer.
  * @param  NewState: new state of the WakeUp timer.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
ErrorStatus ERTC_WakeUpCmd(FunctionalState NewState)
{
  __IO uint32_t wutcounter = 0x00;
  uint32_t wutwfstatus = 0x00;
  ErrorStatus status = ERROR;
  
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;

  if (NewState != DISABLE)
  {
    /* Enable the Wakeup Timer */
    ERTC->CTRL |= (uint32_t)ERTC_CTRL_WATE;
    status = SUCCESS;    
  }
  else
  {
    /* Disable the Wakeup Timer */
    ERTC->CTRL &= (uint32_t)~ERTC_CTRL_WATE;
    /* Wait till ERTC WUTWF flag is set and if Time out is reached exit */
    do
    {
      wutwfstatus = ERTC->ISTS & ERTC_ISTS_WATWF;
      wutcounter++;  
    } while((wutcounter != INITMODE_TMROUT) && (wutwfstatus == 0x00));
    
    if ((ERTC->ISTS & ERTC_ISTS_WATWF) == RESET)
    {
      status = ERROR;
    }
    else
    {
      status = SUCCESS;
    }    
  }

  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF; 
  
  return status;
}

/**
  * @}
  */

/** @defgroup RTC_Group5 Daylight Saving configuration functions
 *  @brief   Daylight Saving configuration functions 
 *
@verbatim   
 ===============================================================================
              ##### Daylight Saving configuration functions #####
 ===============================================================================  

 [..] This section provide functions allowing to configure the ERTC DayLight Saving.

@endverbatim
  * @{
  */

/**
  * @brief  Adds or substract one hour from the current time.
  * @param  RTC_DayLightSaveOperation: the value of hour adjustment. 
  *          This parameter can be one of the following values:
  *            @arg ERTC_DayLightSaving_SUB1H: Substract one hour (winter time)
  *            @arg ERTC_DayLightSaving_ADD1H: Add one hour (summer time)
  * @param  ERTC_StoreOperation: Specifies the value to be written in the BCK bit 
  *                            in CTRL register to store the operation.
  *          This parameter can be one of the following values:
  *            @arg ERTC_StoreOperation_Reset: BCK Bit Reset
  *            @arg ERTC_StoreOperation_Set: BCK Bit Set
  * @retval None
  */
void ERTC_DayLightSavingConfig(uint32_t ERTC_DayLightSaving, uint32_t ERTC_StoreOperation)
{
  /* Check the parameters */
  assert_param(IS_ERTC_DAYLIGHT_SAVING(ERTC_DayLightSaving));
  assert_param(IS_ERTC_STORE_OPERATION(ERTC_StoreOperation));

  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;

  /* Clear the bits to be configured */
  ERTC->CTRL &= (uint32_t)~(ERTC_CTRL_BKP);

  /* Configure the RTC_CR register */
  ERTC->CTRL |= (uint32_t)(ERTC_DayLightSaving | ERTC_StoreOperation);

  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF; 
}

/**
  * @brief  Returns the ERTC Day Light Saving stored operation.
  * @param  None
  * @retval ERTC Day Light Saving stored operation.
  *          - ERTC_StoreOperation_Reset
  *          - ERTC_StoreOperation_Set       
  */
uint32_t ERTC_GetStoreOperation(void)
{
  return (ERTC->CTRL & ERTC_CTRL_BKP);
}

/**
  * @}
  */

/** @defgroup RTC_Group6 Output pin Configuration function
 *  @brief   Output pin Configuration function 
 *
@verbatim   
 ===============================================================================
                 ##### Output pin Configuration function #####
 ===============================================================================  

 [..] This section provide functions allowing to configure the ERTC Output source.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the ERTC output source (AFO_ALARM).
  * @param  ERTC_Output: Specifies which signal will be routed to the ERTC output. 
  *          This parameter can be one of the following values:
  *            @arg ERTC_Output_Disable: No output selected
  *            @arg ERTC_Output_AlarmA: signal of AlarmA mapped to output
  *            @arg ERTC_Output_AlarmB: signal of AlarmB mapped to output
  *            @arg ERTC_Output_WakeUp: signal of WakeUp mapped to output
  * @param  ERTC_OutputPolarity: Specifies the polarity of the output signal. 
  *          This parameter can be one of the following:
  *            @arg ERTC_OutputPolarity_High: The output pin is high when the 
  *                                 ALRAF/ALRBF/WUTF is high (depending on OSEL)
  *            @arg ERTC_OutputPolarity_Low: The output pin is low when the 
  *                                 ALRAF/ALRBF/WUTF is high (depending on OSEL)
  * @retval None
  */
void ERTC_OutputConfig(uint32_t ERTC_Output, uint32_t ERTC_OutputPolarity)
{
  /* Check the parameters */
  assert_param(IS_ERTC_OUTPUT(ERTC_Output));
  assert_param(IS_ERTC_OUTPUT_OPOL(ERTC_OutputPolarity));

  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;

  /* Clear the bits to be configured */
  ERTC->CTRL &= (uint32_t)~(ERTC_CTRL_OSEL | ERTC_CTRL_OPOL);

  /* Configure the output selection and polarity */
  ERTC->CTRL |= (uint32_t)(ERTC_Output | ERTC_OutputPolarity);

  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF; 
}

/**
  * @}
  */

/** @defgroup RTC_Group7 Digital Calibration configuration functions
 *  @brief   Coarse Calibration configuration functions 
 *
@verbatim   
 ===============================================================================
              ##### Digital Calibration configuration functions #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Configures the Coarse calibration parameters.
  * @param  ERTC_CalSign: specifies the sign of the coarse calibration value.
  *          This parameter can be  one of the following values:
  *            @arg ERTC_DataCalSign_Positive: The value sign is positive 
  *            @arg ERTC_DataCalSign_Negative: The value sign is negative
  * @param  Value: value of coarse calibration expressed in ppm (coded on 5 bits).
  *    
  * @note   This Calibration value should be between 0 and 63 when using negative
  *         sign with a 2-ppm step.
  *           
  * @note   This Calibration value should be between 0 and 126 when using positive
  *         sign with a 4-ppm step.
  *           
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ERTC Coarse calibration are initialized
  *          - ERROR: ERTC Coarse calibration are not initialized     
  */
ErrorStatus ERTC_CoarseCalConfig(uint32_t ERTC_CalSign, uint32_t Value)
{
  ErrorStatus status = ERROR;
   
  /* Check the parameters */
  assert_param(IS_ERTC_DATACAL_SIGN(ERTC_CalSign));
  assert_param(IS_ERTC_DATACAL_VALUE(Value)); 

  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;

  /* Set Initialization mode */
  if (ERTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
  } 
  else
  {
    /* Set the coarse calibration value */
    ERTC->CAL = (uint32_t)(ERTC_CalSign | Value);
    /* Exit Initialization mode */
    ERTC_ExitInitMode();
    
    status = SUCCESS;
  } 

  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF; 
  
  return status;
}

/**
  * @brief  Enables or disables the Coarse calibration process.
  * @param  NewState: new state of the Coarse calibration.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ERTC Coarse calibration are enabled/disabled
  *          - ERROR: ERTC Coarse calibration are not enabled/disabled    
  */
ErrorStatus ERTC_CoarseCalCmd(FunctionalState NewState)
{
  ErrorStatus status = ERROR;
  
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;
  
  /* Set Initialization mode */
  if (ERTC_EnterInitMode() == ERROR)
  {
    status =  ERROR;
  }
  else
  {
    if (NewState != DISABLE)
    {
      /* Enable the Coarse Calibration */
      ERTC->CTRL |= (uint32_t)ERTC_CTRL_CDCE;
    }
    else
    { 
      /* Disable the Coarse Calibration */
      ERTC->CTRL &= (uint32_t)~ERTC_CTRL_CDCE;
    }
    /* Exit Initialization mode */
    ERTC_ExitInitMode();
    
    status = SUCCESS;
  } 
  
  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF; 
  
  return status;
}

/**
  * @brief  Enables or disables the ERTC clock to be output through the relative pin.
  * @param  NewState: new state of the digital calibration Output.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ERTC_CalOutputCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;
  
  if (NewState != DISABLE)
  {
    /* Enable the ERTC clock output */
    ERTC->CTRL |= (uint32_t)ERTC_CTRL_CALOE;
  }
  else
  { 
    /* Disable the ERTC clock output */
    ERTC->CTRL &= (uint32_t)~ERTC_CTRL_CALOE;
  }
  
  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF; 
}

/**
  * @brief  Configure the Calibration Pinout (RTC_CALIB) Selection (1Hz or 512Hz).
  * @param  ERTC_CalOutput : Select the Calibration output Selection .
  *   This parameter can be one of the following values:
  *     @arg ERTC_CalOutput_512Hz: A signal has a regular waveform at 512Hz. 
  *     @arg ERTC_CalOutput_1Hz  : A signal has a regular waveform at 1Hz.
  * @retval None
*/
void ERTC_CalOutputConfig(uint32_t ERTC_CalOutput)
{
  /* Check the parameters */
  assert_param(IS_ERTC_CAL_OUTPUT(ERTC_CalOutput));

  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;
  
  /*clear flags before configuration */
  ERTC->CTRL &= (uint32_t)~(ERTC_CTRL_CALSEL);

  /* Configure the RTC_CR register */
  ERTC->CTRL |= (uint32_t)ERTC_CalOutput;

  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF;
}

/**
  * @brief  Configures the Smooth Calibration Settings.
  * @param  ERTC_SmoothCalPeriod : Select the Smooth Calibration Period.
  *   This parameter can be can be one of the following values:
  *     @arg ERTC_SmoothCalPeriod_32sec : The smooth calibration period is 32s.
  *     @arg ERTC_SmoothCalPeriod_16sec : The smooth calibration period is 16s.
  *     @arg ERTC_SmoothCalPeriod_8sec  : The smooth calibration period is 8s.
  * @param  ERTC_SmoothCalPlusPulses : Select to Set or reset the CALP bit.
  *   This parameter can be one of the following values:
  *     @arg ERTC_SmoothCalAddPulses_Set  : Add one RTCCLK pulse every 2**11 pulses.
  *     @arg ERTC_SmoothCalAddPulses_Reset: No RTCCLK pulses are added.
  * @param  ERTC_SmouthCalMinusPulsesValue: Select the value of CALM[8:0] bits.
  *   This parameter can be one any value from 0 to 0x000001FF.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ERTC Calib registers are configured
  *          - ERROR: ERTC Calib registers are not configured
*/
ErrorStatus ERTC_SmoothCalConfig(uint32_t ERTC_SmoothCalPeriod,
                                  uint32_t ERTC_SmoothCalPlusPulses,
                                  uint32_t ERTC_SmouthCalMinusPulsesValue)
{
  ErrorStatus status = ERROR;
  uint32_t recalpfcount = 0;

  /* Check the parameters */
  assert_param(IS_ERTC_SMOOTH_CAL_PERIOD(ERTC_SmoothCalPeriod));
  assert_param(IS_ERTC_SMOOTH_CAL_ADD(ERTC_SmoothCalPlusPulses));
  assert_param(IS_ERTC_SMOOTH_CAL_VALUE(ERTC_SmouthCalMinusPulsesValue));

  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;
  
  /* check if a calibration is pending*/
  if ((ERTC->ISTS & ERTC_ISTS_RECALPDF) != RESET)
  {
    /* wait until the Calibration is completed*/
    while (((ERTC->ISTS & ERTC_ISTS_RECALPDF) != RESET) && (recalpfcount != RECALPDF_TMROUT))
    {
      recalpfcount++;
    }
  }

  /* check if the calibration pending is completed or if there is no calibration operation at all*/
  if ((ERTC->ISTS & ERTC_ISTS_RECALPDF) == RESET)
  {
    /* Configure the Smooth calibration settings */
    ERTC->CCR = (uint32_t)((uint32_t)ERTC_SmoothCalPeriod | (uint32_t)ERTC_SmoothCalPlusPulses | (uint32_t)ERTC_SmouthCalMinusPulsesValue);

    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }

  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF;
  
  return (ErrorStatus)(status);
}

/**
  * @}
  */


/** @defgroup RTC_Group8 TimeStamp configuration functions
 *  @brief   TimeStamp configuration functions 
 *
@verbatim   
 ===============================================================================
                 ##### TimeStamp configuration functions #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Enables or Disables the ERTC TimeStamp functionality with the 
  *         specified time stamp pin stimulating edge.
  * @param  ERTC_TimeStampEdge: Specifies the pin edge on which the TimeStamp is 
  *         activated.
  *          This parameter can be one of the following:
  *            @arg ERTC_TimeStampEdge_Rising: the Time stamp event occurs on the rising 
  *                                    edge of the related pin.
  *            @arg ERTC_TimeStampEdge_Falling: the Time stamp event occurs on the 
  *                                     falling edge of the related pin.
  * @param  NewState: new state of the TimeStamp.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ERTC_TimeStampCmd(uint32_t ERTC_TimeStampEdge, FunctionalState NewState)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_ERTC_TIMESTAMP_EDGE(ERTC_TimeStampEdge));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Get the RTC_CR register and clear the bits to be configured */
  tmpreg = (uint32_t)(ERTC->CTRL & (uint32_t)~(ERTC_CTRL_TSEDGE | ERTC_CTRL_TSE));

  /* Get the new configuration */
  if (NewState != DISABLE)
  {
    tmpreg |= (uint32_t)(ERTC_TimeStampEdge | ERTC_CTRL_TSE);
  }
  else
  {
    tmpreg |= (uint32_t)(ERTC_TimeStampEdge);
  }

  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;

  /* Configure the Time Stamp TSEDGE and Enable bits */
  ERTC->CTRL = (uint32_t)tmpreg;

  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF; 
}

/**
  * @brief  Get the ERTC TimeStamp value and masks.
  * @param  ERTC_Format: specifies the format of the output parameters.
  *          This parameter can be one of the following values:
  *            @arg ERTC_Format_BIN: Binary data format 
  *            @arg ERTC_Format_BCD: BCD data format
  * @param ERTC_StampTimeStruct: pointer to a ERTC_TimeType structure that will 
  *                             contains the TimeStamp time values. 
  * @param ERTC_StampDateStruct: pointer to a ERTC_DateType structure that will 
  *                             contains the TimeStamp date values.     
  * @retval None
  */
void ERTC_GetTimeStamp(uint32_t ERTC_Format, ERTC_TimeType* ERTC_StampTimeStruct, 
                                      ERTC_DateType* ERTC_StampDateStruct)
{
  uint32_t tmptime = 0, tmpdate = 0;

  /* Check the parameters */
  assert_param(IS_ERTC_FORMAT(ERTC_Format));

  /* Get the TimeStamp time and date registers values */
  tmptime = (uint32_t)(ERTC->TSTM & ERTC_TIME_RESERVED_MASK);
  tmpdate = (uint32_t)(ERTC->TSDT & ERTC_DATE_RESERVED_MASK);

  /* Fill the Time structure fields with the read parameters */
  ERTC_StampTimeStruct->ERTC_Hours = (uint8_t)((tmptime & (ERTC_TIME_HT | ERTC_TIME_HU)) >> 16);
  ERTC_StampTimeStruct->ERTC_Minutes = (uint8_t)((tmptime & (ERTC_TIME_MT | ERTC_TIME_MU)) >> 8);
  ERTC_StampTimeStruct->ERTC_Seconds = (uint8_t)(tmptime & (ERTC_TIME_ST | ERTC_TIME_SU));
  ERTC_StampTimeStruct->ERTC_AMPM = (uint8_t)((tmptime & (ERTC_TIME_AMPM)) >> 16);  

  /* Fill the Date structure fields with the read parameters */
  ERTC_StampDateStruct->ERTC_Year = 0;
  ERTC_StampDateStruct->ERTC_Month = (uint8_t)((tmpdate & (ERTC_DATE_MT | ERTC_DATE_MU)) >> 8);
  ERTC_StampDateStruct->ERTC_Date = (uint8_t)(tmpdate & (ERTC_DATE_DT | ERTC_DATE_DU));
  ERTC_StampDateStruct->ERTC_WeekDay = (uint8_t)((tmpdate & (ERTC_DATE_WK)) >> 13);

  /* Check the input parameters format */
  if (ERTC_Format == ERTC_Format_BIN)
  {
    /* Convert the Time structure parameters to Binary format */
    ERTC_StampTimeStruct->ERTC_Hours = (uint8_t)ERTC_Bcd2ToByte(ERTC_StampTimeStruct->ERTC_Hours);
    ERTC_StampTimeStruct->ERTC_Minutes = (uint8_t)ERTC_Bcd2ToByte(ERTC_StampTimeStruct->ERTC_Minutes);
    ERTC_StampTimeStruct->ERTC_Seconds = (uint8_t)ERTC_Bcd2ToByte(ERTC_StampTimeStruct->ERTC_Seconds);

    /* Convert the Date structure parameters to Binary format */
    ERTC_StampDateStruct->ERTC_Month = (uint8_t)ERTC_Bcd2ToByte(ERTC_StampDateStruct->ERTC_Month);
    ERTC_StampDateStruct->ERTC_Date = (uint8_t)ERTC_Bcd2ToByte(ERTC_StampDateStruct->ERTC_Date);
    ERTC_StampDateStruct->ERTC_WeekDay = (uint8_t)ERTC_Bcd2ToByte(ERTC_StampDateStruct->ERTC_WeekDay);
  }
}

/**
  * @brief  Get the ERTC timestamp Sub seconds value.
  * @param  None
  * @retval ERTC current timestamp Sub seconds value.
  */
uint32_t ERTC_GetTimeStampSubSecond(void)
{
  /* Get timestamp sub seconds values from the correspondent registers */
  return (uint32_t)(ERTC->TSSBS);
}

/**
  * @}
  */

/** @defgroup RTC_Group9 Tampers configuration functions
 *  @brief   Tampers configuration functions 
 *
@verbatim   
 ===============================================================================
                 ##### Tampers configuration functions #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Configures the select Tamper pin edge.
  * @param  ERTC_Tamper: Selected tamper pin.
  *          This parameter can be ERTC_TAMP_1 or ERTC_Tamper 2
  * @param  ERTC_TamperTrigger: Specifies the trigger on the tamper pin that 
  *         stimulates tamper event. 
  *   This parameter can be one of the following values:
  *     @arg ERTC_TamperTrig_RisingEdge: Rising Edge of the tamper pin causes tamper event.
  *     @arg ERTC_TamperTrig_FallingEdge: Falling Edge of the tamper pin causes tamper event.
  *     @arg ERTC_TamperTrig_LowLevel: Low Level of the tamper pin causes tamper event.
  *     @arg ERTC_TamperTrig_HighLevel: High Level of the tamper pin causes tamper event.
  * @retval None
  */
void ERTC_TamperTriggerConfig(uint32_t ERTC_Tamper, uint32_t ERTC_TamperTrigger)
{
  /* Check the parameters */
  assert_param(IS_ERTC_TAMP(ERTC_Tamper)); 
  assert_param(IS_ERTC_TAMPER_TRIG(ERTC_TamperTrigger));
 
  if (ERTC_TamperTrigger == ERTC_TamperTrig_RisingEdge)
  {  
    /* Configure the RTC_TAFCR register */
    ERTC->TPAF &= (uint32_t)((uint32_t)~(ERTC_Tamper << 1));	
  }
  else
  { 
    /* Configure the RTC_TAFCR register */
    ERTC->TPAF |= (uint32_t)(ERTC_Tamper << 1);  
  }  
}

/**
  * @brief  Enables or Disables the Tamper detection.
  * @param  ERTC_Tamper: Selected tamper pin.
  *          This parameter can be ERTC_TAMP_1 or ERTC_TAMP_2
  * @param  NewState: new state of the tamper pin.
  *          This parameter can be: ENABLE or DISABLE.                   
  * @retval None
  */
void ERTC_TamperCmd(uint32_t ERTC_Tamper, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ERTC_TAMP(ERTC_Tamper));  
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected Tamper pin */
    ERTC->TPAF |= (uint32_t)ERTC_Tamper;
  }
  else
  {
    /* Disable the selected Tamper pin */
    ERTC->TPAF &= (uint32_t)~ERTC_Tamper;    
  }  
}

/**
  * @brief  Configures the Tampers Filter.
  * @param  ERTC_TamperFilter: Specifies the tampers filter.
  *   This parameter can be one of the following values:
  *     @arg ERTC_TamperFilter_Disable: Tamper filter is disabled.
  *     @arg ERTC_TamperFilter_2Sample: Tamper is activated after 2 consecutive 
  *                                    samples at the active level 
  *     @arg ERTC_TamperFilter_4Sample: Tamper is activated after 4 consecutive 
  *                                    samples at the active level
  *     @arg ERTC_TamperFilter_8Sample: Tamper is activated after 8 consecutive 
  *                                    samples at the active level 
  * @retval None
  */
void ERTC_TamperFilterConfig(uint32_t ERTC_TamperFilter)
{
  /* Check the parameters */
  assert_param(IS_ERTC_TAMPER_FILTER(ERTC_TamperFilter));
   
  /* Clear TAMPFLT[1:0] bits in the RTC_TAFCR register */
  ERTC->TPAF &= (uint32_t)~(ERTC_TPAF_TMFLT);

  /* Configure the RTC_TAFCR register */
  ERTC->TPAF |= (uint32_t)ERTC_TamperFilter;
}

/**
  * @brief  Configures the Tampers Sampling Frequency.
  * @param  ERTC_TamperSamplingFreq: Specifies the tampers Sampling Frequency.
  *   This parameter can be one of the following values:
  *     @arg ERTC_TamperSamplingFreq_CLK_Div32768: Each of the tamper inputs are sampled
  *                                           with a frequency =  RTCCLK / 32768
  *     @arg ERTC_TamperSamplingFreq_CLK_Div16384: Each of the tamper inputs are sampled
  *                                           with a frequency =  RTCCLK / 16384
  *     @arg ERTC_TamperSamplingFreq_CLK_Div8192: Each of the tamper inputs are sampled
  *                                           with a frequency =  RTCCLK / 8192
  *     @arg ERTC_TamperSamplingFreq_CLK_Div4096: Each of the tamper inputs are sampled
  *                                           with a frequency =  RTCCLK / 4096
  *     @arg ERTC_TamperSamplingFreq_CLK_Div2048: Each of the tamper inputs are sampled
  *                                           with a frequency =  RTCCLK / 2048
  *     @arg ERTC_TamperSamplingFreq_CLK_Div1024: Each of the tamper inputs are sampled
  *                                           with a frequency =  RTCCLK / 1024
  *     @arg ERTC_TamperSamplingFreq_CLK_Div512: Each of the tamper inputs are sampled
  *                                           with a frequency =  RTCCLK / 512  
  *     @arg ERTC_TamperSamplingFreq_CLK_Div256: Each of the tamper inputs are sampled
  *                                           with a frequency =  RTCCLK / 256  
  * @retval None
  */
void ERTC_TamperSamplingFreqConfig(uint32_t ERTC_TamperSamplingFreq)
{
  /* Check the parameters */
  assert_param(IS_ERTC_TAMPER_SAMPLING_FREQ(ERTC_TamperSamplingFreq));
 
  /* Clear TAMPFREQ[2:0] bits in the RTC_TAFCR register */
  ERTC->TPAF &= (uint32_t)~(ERTC_TPAF_TMFREQ);

  /* Configure the RTC_TAFCR register */
  ERTC->TPAF |= (uint32_t)ERTC_TamperSamplingFreq;
}

/**
  * @brief  Configures the Tampers Pins input Precharge Duration.
  * @param  ERTC_TamperPrechargeDuration: Specifies the Tampers Pins input
  *         Precharge Duration.
  *   This parameter can be one of the following values:
  *     @arg ERTC_TamperPrechargeDuration_1RTCCLK: Tamper pins are precharged before sampling during 1 RTCCLK cycle
  *     @arg ERTC_TamperPrechargeDuration_2RTCCLK: Tamper pins are precharged before sampling during 2 RTCCLK cycle
  *     @arg ERTC_TamperPrechargeDuration_4RTCCLK: Tamper pins are precharged before sampling during 4 RTCCLK cycle    
  *     @arg ERTC_TamperPrechargeDuration_8RTCCLK: Tamper pins are precharged before sampling during 8 RTCCLK cycle
  * @retval None
  */
void ERTC_TamperPinsPrechargeDuration(uint32_t ERTC_TamperPrechargeDuration)
{
  /* Check the parameters */
  assert_param(IS_ERTC_TAMPER_PRECHARGE_DURATION(ERTC_TamperPrechargeDuration));
   
  /* Clear TAMPPRCH[1:0] bits in the RTC_TAFCR register */
  ERTC->TPAF &= (uint32_t)~(ERTC_TPAF_TMPRCH);

  /* Configure the RTC_TAFCR register */
  ERTC->TPAF |= (uint32_t)ERTC_TamperPrechargeDuration;
}

/**
  * @brief  Enables or Disables the TimeStamp on Tamper Detection Event.
  * @note   The timestamp is valid even the TSE bit in tamper control register 
  *         is reset.   
  * @param  NewState: new state of the timestamp on tamper event.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ERTC_TimeStampOnTamperDetectionCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
   
  if (NewState != DISABLE)
  {
    /* Save timestamp on tamper detection event */
    ERTC->TPAF |= (uint32_t)ERTC_TPAF_TMTS;
  }
  else
  {
    /* Tamper detection does not cause a timestamp to be saved */
    ERTC->TPAF &= (uint32_t)~ERTC_TPAF_TMTS;    
  }
}

/**
  * @brief  Enables or Disables the Precharge of Tamper pin.
  * @param  NewState: new state of tamper pull up.
  *   This parameter can be: ENABLE or DISABLE.                   
  * @retval None
  */
void ERTC_TamperPullUpCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
 if (NewState != DISABLE)
  {
    /* Enable precharge of the selected Tamper pin */
    ERTC->TPAF &= (uint32_t)~ERTC_TPAF_TMPUDIS; 
  }
  else
  {
    /* Disable precharge of the selected Tamper pin */
    ERTC->TPAF |= (uint32_t)ERTC_TPAF_TMPUDIS;    
  } 
}

/**
  * @}
  */

/** @defgroup RTC_Group10 Backup Data Registers configuration functions
 *  @brief   Backup Data Registers configuration functions  
 *
@verbatim   
 ===============================================================================
             ##### Backup Data Registers configuration functions ##### 
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Writes a data in a specified ERTC Backup data register.
  * @param  ERTC_BKP_DT: ERTC Backup data Register number.
  *          This parameter can be: ERTC_BKP_DTx where x can be from 0 to 19 to 
  *                          specify the register.
  * @param  Data: Data to be written in the specified ERTC Backup data register.                     
  * @retval None
  */
void ERTC_WriteBackupRegister(uint32_t ERTC_BKP_DT, uint32_t Data)
{
  __IO uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_ERTC_BKP(ERTC_BKP_DT));

  tmp = ERTC_BASE + 0x50;
  tmp += (ERTC_BKP_DT * 4);

  /* Write the specified register */
  *(__IO uint32_t *)tmp = (uint32_t)Data;
}

/**
  * @brief  Reads data from the specified ERTC Backup data Register.
  * @param  ERTC_BKP_DT: ERTC Backup data Register number.
  *          This parameter can be: ERTC_BKP_DTx where x can be from 0 to 19 to 
  *                          specify the register.                   
  * @retval None
  */
uint32_t ERTC_ReadBackupRegister(uint32_t ERTC_BKP_DT)
{
  __IO uint32_t tmp = 0;
  
  /* Check the parameters */
  assert_param(IS_ERTC_BKP(ERTC_BKP_DT));

  tmp = ERTC_BASE + 0x50;
  tmp += (ERTC_BKP_DT * 4);
  
  /* Read the specified register */
  return (*(__IO uint32_t *)tmp);
}

/**
  * @}
  */

/** @defgroup RTC_Group11 ERTC Tamper and TimeStamp Pins Selection and Output Type Config configuration functions
 *  @brief   ERTC Tamper and TimeStamp Pins Selection and Output Type Config 
 *           configuration functions  
 *
@verbatim   
 ==================================================================================================
 ##### ERTC Tamper and TimeStamp Pins Selection and Output Type Config configuration functions ##### 
 ==================================================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Selects the ERTC Tamper Pin.
  * @param  ERTC_TamperPin: specifies the ERTC Tamper Pin.
  *          This parameter can be one of the following values:
  *            @arg ERTC_TAMPPIN_Default: RTC_AF1 is used as ERTC Tamper Pin.
  *            @arg ERTC_TAMPPIN_Pos1: RTC_AF2 is selected as ERTC Tamper Pin.    
  * @retval None
  */
void ERTC_TamperPinSelection(uint32_t ERTC_TamperPin)
{
  /* Check the parameters */
  assert_param(IS_ERTC_TAMP_PIN(ERTC_TamperPin));
  
  ERTC->TPAF &= (uint32_t)~(ERTC_TPAF_TMPINSEL);
  ERTC->TPAF |= (uint32_t)(ERTC_TamperPin);  
}

/**
  * @brief  Selects the ERTC TimeStamp Pin.
  * @param  ERTC_TimeStampPin: specifies the ERTC TimeStamp Pin.
  *          This parameter can be one of the following values:
  *            @arg ERTC_TimeStampPin_PC13: PC13 is selected as ERTC TimeStamp Pin.
  *            @arg ERTC_TimeStampPin_PI8: PI8 is selected as ERTC TimeStamp Pin.    
  * @retval None
  */
void ERTC_TimeStampPinSelection(uint32_t ERTC_TimeStampPin)
{
  /* Check the parameters */
  assert_param(IS_ERTC_TIMESTAMP_PIN(ERTC_TimeStampPin));
  
  ERTC->TPAF &= (uint32_t)~(ERTC_TPAF_TSINSEL);
  ERTC->TPAF |= (uint32_t)(ERTC_TimeStampPin);  
}

/**
  * @brief  Configures the ERTC Output Pin mode. 
  * @param  ERTC_OutputType: specifies the ERTC Output (PC13) pin mode.
  *          This parameter can be one of the following values:
  *            @arg ERTC_OutputType_OpenDrain: ERTC Output (PC13) is configured in 
  *                                    Open Drain mode.
  *            @arg ERTC_OutputType_PushPull:  ERTC Output (PC13) is configured in 
  *                                    Push Pull mode.    
  * @retval None
  */
void ERTC_OutputTypeConfig(uint32_t ERTC_OutputType)
{
  /* Check the parameters */
  assert_param(IS_ERTC_OUTPUT_TYPE(ERTC_OutputType));
  
  ERTC->TPAF &= (uint32_t)~(ERTC_TPAF_ALAOUTTYPE);
  ERTC->TPAF |= (uint32_t)(ERTC_OutputType);  
}

/**
  * @}
  */

/** @defgroup RTC_Group12 Shift control synchronisation functions
 *  @brief   Shift control synchronisation functions 
 *
@verbatim   
 ===============================================================================
              ##### Shift control synchronisation functions #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Configures the Synchronization Shift Control Settings.
  * @note   When REFCKON is set, firmware must not write to Shift control register 
  * @param  ERTC_ShiftAdd1S : Select to add or not 1 second to the time Calendar.
  *   This parameter can be one of the following values :
  *     @arg ERTC_ShiftAdd1S_Set  : Add one second to the clock calendar. 
  *     @arg ERTC_ShiftAdd1S_Reset: No effect.
  * @param  ERTC_ShiftSubFS: Select the number of Second Fractions to Substitute.
  *         This parameter can be one any value from 0 to 0x7FFF.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ERTC Shift registers are configured
  *          - ERROR: ERTC Shift registers are not configured
*/
ErrorStatus ERTC_SynchroShiftConfig(uint32_t ERTC_ShiftAdd1S, uint32_t ERTC_ShiftSubFS)
{
  ErrorStatus status = ERROR;
  uint32_t shpfcount = 0;

  /* Check the parameters */
  assert_param(IS_ERTC_SHIFT_ADD1S(ERTC_ShiftAdd1S));
  assert_param(IS_ERTC_SHIFT_SUBFS(ERTC_ShiftSubFS));

  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;
  
  /* Check if a Shift is pending*/
  if ((ERTC->ISTS & ERTC_ISTS_SFP) != RESET)
  {
    /* Wait until the shift is completed*/
    while (((ERTC->ISTS & ERTC_ISTS_SFP) != RESET) && (shpfcount != SFP_TMROUT))
    {
      shpfcount++;
    }
  }

  /* Check if the Shift pending is completed or if there is no Shift operation at all*/
  if ((ERTC->ISTS & ERTC_ISTS_SFP) == RESET)
  {
    /* check if the reference clock detection is disabled */
    if((ERTC->CTRL & ERTC_CTRL_RFCKON) == RESET)
    {
      /* Configure the Shift settings */
      ERTC->SFCTR = (uint32_t)(uint32_t)(ERTC_ShiftSubFS) | (uint32_t)(ERTC_ShiftAdd1S);
    
      if(ERTC_WaitForSynchro() == ERROR)
      {
        status = ERROR;
      }
      else
      {
        status = SUCCESS;
      }
    }
    else
    {
      status = ERROR;
    }
  }
  else
  {
    status = ERROR;
  }

  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF;
  
  return (ErrorStatus)(status);
}

/**
  * @}
  */

/** @defgroup RTC_Group13 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions  
 *
@verbatim   
 ===============================================================================
              ##### Interrupts and flags management functions #####
 ===============================================================================  
 [..] All ERTC interrupts are connected to the EXTI controller.
 
   (+) To enable the ERTC Alarm interrupt, the following sequence is required:
       (++) Configure and enable the EXTI Line 17 in interrupt mode and select 
            the rising edge sensitivity using the EXTI_Init() function.
       (++) Configure and enable the ERTC_Alarm IRQ channel in the NVIC using the 
            NVIC_Init() function.
       (++) Configure the ERTC to generate ERTC alarms (Alarm A and/or Alarm B) using
            the ERTC_SetAlarmValue() and ERTC_AlarmCmd() functions.

   (+) To enable the ERTC Wakeup interrupt, the following sequence is required:
       (++) Configure and enable the EXTI Line 22 in interrupt mode and select the
            rising edge sensitivity using the EXTI_Init() function.
       (++) Configure and enable the RTC_WKUP IRQ channel in the NVIC using the 
            NVIC_Init() function.
       (++) Configure the ERTC to generate the ERTC wakeup timer event using the 
            ERTC_WakeUpClockConfig(), ERTC_SetWakeUpCounter() and ERTC_WakeUpCmd() 
            functions.

   (+) To enable the ERTC Tamper interrupt, the following sequence is required:
       (++) Configure and enable the EXTI Line 21 in interrupt mode and select 
            the rising edge sensitivity using the EXTI_Init() function.
       (++) Configure and enable the TAMP_STAMP IRQ channel in the NVIC using the
            NVIC_Init() function.
       (++) Configure the ERTC to detect the ERTC tamper event using the 
            ERTC_TamperTriggerConfig() and ERTC_TamperCmd() functions.

   (+) To enable the ERTC TimeStamp interrupt, the following sequence is required:
       (++) Configure and enable the EXTI Line 21 in interrupt mode and select the
            rising edge sensitivity using the EXTI_Init() function.
       (++) Configure and enable the TAMP_STAMP IRQ channel in the NVIC using the 
            NVIC_Init() function.
       (++) Configure the ERTC to detect the ERTC time stamp event using the 
            ERTC_TimeStampCmd() functions.

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified ERTC interrupts.
  * @param  ERTC_INT: specifies the ERTC interrupt sources to be enabled or disabled. 
  *          This parameter can be any combination of the following values:
  *            @arg ERTC_INT_TS:  Time Stamp interrupt mask
  *            @arg ERTC_INT_WAT:  WakeUp Timer interrupt mask
  *            @arg ERTC_INT_ALB:  Alarm B interrupt mask
  *            @arg ERTC_INT_ALA:  Alarm A interrupt mask
  *            @arg ERTC_INT_TAMP: Tamper event interrupt mask
  * @param  NewState: new state of the specified ERTC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ERTC_INTConfig(uint32_t ERTC_INT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ERTC_CONFIG_INT(ERTC_INT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for ERTC registers */
  ERTC->WPR = 0xCA;
  ERTC->WPR = 0x53;

  if (NewState != DISABLE)
  {
    /* Configure the Interrupts in the RTC_CR register */
    ERTC->CTRL |= (uint32_t)(ERTC_INT & ~ERTC_TPAF_TMIE);
    /* Configure the Tamper Interrupt in the RTC_TAFCR */
    ERTC->TPAF |= (uint32_t)(ERTC_INT & ERTC_TPAF_TMIE);
  }
  else
  {
    /* Configure the Interrupts in the RTC_CR register */
    ERTC->CTRL &= (uint32_t)~(ERTC_INT & (uint32_t)~ERTC_TPAF_TMIE);
    /* Configure the Tamper Interrupt in the RTC_TAFCR */
    ERTC->TPAF &= (uint32_t)~(ERTC_INT & ERTC_TPAF_TMIE);
  }
  /* Enable the write protection for ERTC registers */
  ERTC->WPR = 0xFF; 
}

/**
  * @brief  Checks whether the specified ERTC flag is set or not.
  * @param  ERTC_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg ERTC_FLAG_RECALPDF: RECALPF event flag.
  *            @arg ERTC_FLAG_TP1F: Tamper 1 event flag
  *            @arg ERTC_FLAG_TP2F: Tamper 2 event flag
  *            @arg ERTC_FLAG_TSOF: Time Stamp OverFlow flag
  *            @arg ERTC_FLAG_TSF: Time Stamp event flag
  *            @arg ERTC_FLAG_WATF: WakeUp Timer flag
  *            @arg ERTC_FLAG_ALBF: Alarm B flag
  *            @arg ERTC_FLAG_ALAF: Alarm A flag
  *            @arg ERTC_FLAG_INITF: Initialization mode flag
  *            @arg ERTC_FLAG_RSF: Registers Synchronized flag
  *            @arg ERTC_FLAG_INITS: Registers Configured flag
  *            @arg ERTC_FLAG_SFP: Shift operation pending flag.
  *            @arg ERTC_FLAG_WATWF: WakeUp Timer Write flag
  *            @arg ERTC_FLAG_ALBWF: Alarm B Write flag
  *            @arg ERTC_FLAG_ALAWF: Alarm A write flag
  * @retval The new state of ERTC_FLAG (SET or RESET).
  */
FlagStatus ERTC_GetFlagStatus(uint32_t ERTC_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_ERTC_GET_FLAG(ERTC_FLAG));
  
  /* Get all the flags */
  tmpreg = (uint32_t)(ERTC->ISTS & ERTC_FLAGS_MASK);
  
  /* Return the status of the flag */
  if ((tmpreg & ERTC_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the ERTC's pending flags.
  * @param  ERTC_FLAG: specifies the ERTC flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg ERTC_FLAG_TP1F: Tamper 1 event flag
  *            @arg ERTC_FLAG_TP2F: Tamper 2 event flag
  *            @arg ERTC_FLAG_TSOF: Time Stamp Overflow flag 
  *            @arg ERTC_FLAG_TSF: Time Stamp event flag
  *            @arg ERTC_FLAG_WATF: WakeUp Timer flag
  *            @arg ERTC_FLAG_ALBF: Alarm B flag
  *            @arg ERTC_FLAG_ALAF: Alarm A flag
  *            @arg ERTC_FLAG_RSF: Registers Synchronized flag
  * @retval None
  */
void ERTC_ClearFlag(uint32_t ERTC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_ERTC_CLEAR_FLAG(ERTC_FLAG));

  /* Clear the Flags in the RTC_ISR register */
  ERTC->ISTS = (uint32_t)((uint32_t)(~((ERTC_FLAG | ERTC_ISTS_INITM)& 0x0000FFFF) | (uint32_t)(ERTC->ISTS & ERTC_ISTS_INITM)));  
}

/**
  * @brief  Checks whether the specified ERTC interrupt has occurred or not.
  * @param  ERTC_INT: specifies the ERTC interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg ERTC_INT_TS: Time Stamp interrupt 
  *            @arg ERTC_INT_WAT: WakeUp Timer interrupt 
  *            @arg ERTC_INT_ALB: Alarm B interrupt 
  *            @arg ERTC_INT_ALA: Alarm A interrupt 
  *            @arg ERTC_INT_TAMP1: Tamper 1 event interrupt
  *            @arg ERTC_INT_TAMP2: Tamper 2 event interrupt
  * @retval The new state of ERTC_INT (SET or RESET).
  */
ITStatus ERTC_GetINTStatus(uint32_t ERTC_INT)
{
  ITStatus bitstatus = RESET;
  uint32_t tmpreg = 0, enablestatus = 0;
 
  /* Check the parameters */
  assert_param(IS_ERTC_GET_INT(ERTC_INT));
  
  /* Get the TAMPER Interrupt enable bit and pending bit */
  tmpreg = (uint32_t)(ERTC->TPAF & (ERTC_TPAF_TMIE));
 
  /* Get the Interrupt enable Status */
  enablestatus = (uint32_t)((ERTC->CTRL & ERTC_INT) | (tmpreg & (ERTC_INT >> 15)) | (tmpreg & (ERTC_INT >> 16)));
  
  /* Get the Interrupt pending bit */
  tmpreg = (uint32_t)((ERTC->ISTS & (uint32_t)(ERTC_INT >> 4)));
  
  /* Get the status of the Interrupt */
  if ((enablestatus != (uint32_t)RESET) && ((tmpreg & 0x0000FFFF) != (uint32_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the ERTC's interrupt pending bits.
  * @param  ERTC_INT: specifies the ERTC interrupt pending bit to clear.
  *          This parameter can be any combination of the following values:
  *            @arg ERTC_INT_TS: Time Stamp interrupt 
  *            @arg ERTC_INT_WAT: WakeUp Timer interrupt 
  *            @arg ERTC_INT_ALB: Alarm B interrupt 
  *            @arg ERTC_INT_ALA: Alarm A interrupt 
  *            @arg ERTC_INT_TAMP1: Tamper 1 event interrupt
  *            @arg ERTC_INT_TAMP2: Tamper 2 event interrupt 
  * @retval None
  */
void ERTC_ClearINTPendingBINT(uint32_t ERTC_INT)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_ERTC_CLEAR_INT(ERTC_INT));

  /* Get the RTC_ISR Interrupt pending bits mask */
  tmpreg = (uint32_t)(ERTC_INT >> 4);

  /* Clear the interrupt pending bits in the RTC_ISR register */
  ERTC->ISTS = (uint32_t)((uint32_t)(~((tmpreg | ERTC_ISTS_INITM)& 0x0000FFFF) | (uint32_t)(ERTC->ISTS & ERTC_ISTS_INITM))); 
}

/**
  * @}
  */

/**
  * @brief  Converts a 2 digit decimal to BCD format.
  * @param  Value: Byte to be converted.
  * @retval Converted byte
  */
static uint8_t ERTC_ByteToBcd2(uint8_t Value)
{
  uint8_t bcdhigh = 0;
  
  while (Value >= 10)
  {
    bcdhigh++;
    Value -= 10;
  }
  
  return  ((uint8_t)(bcdhigh << 4) | Value);
}

/**
  * @brief  Convert from 2 digit BCD to Binary.
  * @param  Value: BCD value to be converted.
  * @retval Converted word
  */
static uint8_t ERTC_Bcd2ToByte(uint8_t Value)
{
  uint8_t tmp = 0;
  tmp = ((uint8_t)(Value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
  return (tmp + (Value & (uint8_t)0x0F));
}

/**
  * @}
  */ 

#endif /* AT32F415xx */

/**
  * @}
  */ 

/**
  * @}
  */ 

