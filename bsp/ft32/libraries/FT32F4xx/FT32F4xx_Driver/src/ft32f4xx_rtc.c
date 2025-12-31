/**
  ******************************************************************************
  * @file               ft32f4xx_rtc.c
  * @author             FMD AE
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the Real-Time Clock (RTC) peripheral:
  *                 + Initialization
  *                 + Calendar (Time and Date) configuration
  *                 + Alarms (Alarm A and Alarm B) configuration
  *                 + Daylight Saving configuration
  *                 + Output pin Configuration
  *                 + Digital Calibration configuration
  *                 + Rough Digtial Calibration configuration
  *                 + TimeStamp configuration
  *                 + Tampers (tamp1 and tamp2)configuration
  *                 + Output Type Config configuration
  *                 + Shift control synchronisation
  *                 + Interrupts and flags management
  *                 + Auot WeakUp  Config configuration
  *                 + Backup Data Registers configuration
  * @version            V1.0.0
  * @data                   2025-03-25
    ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_rtc.h"
#include "ft32f4xx_rcc.h"

/* Masks Definition */
#define RTC_TR_RESERVED_MASK    ((uint32_t)0x007F7F7F)
#define RTC_DR_RESERVED_MASK    ((uint32_t)0x00FFFF3F)
#define RTC_TSTR_RESERVED_MASK  ((uint32_t)0x007F7F7F)
#define RTC_TSDR_RESERVED_MASK  ((uint32_t)0x00FFFF3F)
#define RTC_INIT_MASK           ((uint32_t)0xFFFFFFFF)
#define RTC_RSF_MASK            ((uint32_t)0xFFFFFFDF)
#define RTC_WUTR_MASK           ((uint32_t)0x0000FFFF)
#define RTC_FLAGS_MASK          ((uint32_t)(RTC_FLAG_RECALPF | RTC_FLAG_TAMP2F | RTC_FLAG_TAMP1F | \
                                            RTC_FLAG_TSOVF   | RTC_FLAG_TSF    | RTC_FLAG_WUTF   | \
                                            RTC_FLAG_ALRBF   | RTC_FLAG_ALRAF  | RTC_FLAG_INITF  | \
                                            RTC_FLAG_RSF     | RTC_FLAG_INITS  | RTC_FLAG_SHPF   | \
                                            RTC_FLAG_WUTWF   | RTC_FLAG_ALRBWF | RTC_FLAG_ALRAWF  ))

#define INITMODE_TIMEOUT         ((uint32_t) 0x00004000)
#define SYNCHRO_TIMEOUT          ((uint32_t) 0x00008000)
#define RECALPF_TIMEOUT          ((uint32_t) 0x00001000)
#define SHPF_TIMEOUT             ((uint32_t) 0x00001000)


static uint8_t RTC_ByteToBcd2(uint8_t Value);
static uint8_t RTC_Bcd2ToByte(uint8_t Value);

/**
  * @brief  Deinitializes the RTC registers to their default reset values.
  * @note   This function doesn't reset the RTC Clock source and RTC Backup Data
  *         registers.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC registers are deinitialized
  *          - ERROR: RTC registers are not deinitialized
  */
ErrorStatus RTC_DeInit(void)
{
    ErrorStatus status = ERROR;

    /* Disable the write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* Set Initialization mode */
    if (RTC_EnterInitMode() == ERROR)
    {
        status = ERROR;
    }
    else
    {
        /* Reset TR, DR and CR registers */
        RTC->TR        = (uint32_t)0x00000000;
        RTC->DR        = (uint32_t)0x00002101;
        RTC->CR        = (uint32_t)0x00000000;
        RTC->PRER      = (uint32_t)0x007F00FF;
        RTC->WUTR      = (uint32_t)0x0000FFFF;
        RTC->CALIBR    = (uint32_t)0x00000000;
        RTC->ALRMAR    = (uint32_t)0x00000000;
        RTC->ALRMBR    = (uint32_t)0x00000000;
        RTC->SHIFTR    = (uint32_t)0x00000000;
        RTC->CALR      = (uint32_t)0x00000000;
        RTC->ALRMASSR  = (uint32_t)0x00000000;
        RTC->ALRMBSSR  = (uint32_t)0x00000000;

        /* Reset ISR register and exit initialization mode */
        RTC->ISR = (uint32_t)0x00000000;

        /* Reset Tamper and alternate functions configuration register */
        RTC->TAFCR = (uint32_t)0x00000000;

        /* Wait till the RTC RSF flag is set */
        if (RTC_WaitForSynchro() == ERROR)
        {
            status = ERROR;
        }
        else
        {
            status = SUCCESS;
        }
    }

    /* Enable the write protection for RTC registers */
    RTC->WPR = 0xFF;

    return status;
}

/**
  * @brief  Initializes the RTC registers according to the specified parameters
  *         in RTC_InitStruct.
  * @param  RTC_InitStruct: pointer to a RTC_InitTypeDef structure that contains
  *         the configuration information for the RTC peripheral.
  * @note   The RTC Prescaler register is write protected and can be written in
  *         initialization mode only.
  *         The function use config hour format, async and sync value
  */
void RTC_SetInit(RTC_InitTypeDef* RTC_InitStruct)
{
    /* Check the parameters */
    assert_param(IS_RTC_HOUR_FORMAT(RTC_InitStruct->RTC_HourFormat));
    assert_param(IS_RTC_ASYNCH_PREDIV(RTC_InitStruct->RTC_AsynchPrediv));
    assert_param(IS_RTC_SYNCH_PREDIV(RTC_InitStruct->RTC_SynchPrediv));

    /* Clear RTC CR FMT Bit set 24 hour*/
    RTC->CR   &= ((uint32_t)~(RTC_CR_FMT));
    /* Set RTC_CR register */
    RTC->CR   |= ((uint32_t)(RTC_InitStruct->RTC_HourFormat));

    /*clear async and sync value*/
    RTC->PRER &= ~(RTC_PRER_PREDIV_A | RTC_PRER_PREDIV_S);

    /* Configure the RTC PRER */
    RTC->PRER |= (uint32_t)(RTC_InitStruct->RTC_SynchPrediv);
    RTC->PRER |= (uint32_t)(RTC_InitStruct->RTC_AsynchPrediv << 16);
}

/**
  * @brief  Fills each RTC_InitStruct member with its default value.
  * @param  RTC_InitStruct: pointer to a RTC_InitTypeDef structure which will be
  *         initialized.async lower than 0x7F,sync lower than 0x1FFF
  *         Use this function config specific value to Rtc_InitStruct
  * @retval None
  */
void RTC_StructInit(RTC_InitTypeDef* RTC_InitStruct)
{
    /* Initialize the RTC_HourFormat member */
    RTC_InitStruct->RTC_HourFormat = RTC_HourFormat_24 /*RTC_HourFormat_12*/;

    /* Initialize the RTC_AsynchPrediv member */
    RTC_InitStruct->RTC_AsynchPrediv = (uint32_t)0x7F;

    /* Initialize the RTC_SynchPrediv member */
    RTC_InitStruct->RTC_SynchPrediv = (uint32_t)0xFF;
}

/**
  * @brief  Enables or disables the RTC registers write protection.
  * @note   All the RTC registers are write protected except for RTC_ISR[13:8],
  *         RTC_TAFCR and RTC_BKPxR.
  * @note   Writing a wrong key reactivates the write protection.
  * @note   The protection mechanism is not affected by system reset.
  * @param  NewState: new state of the write protection.
  *          This parameter can be: ENABLE reactive write protect
  *                                 DISABLE open write protect.
  * @retval None
  */
void RTC_WriteProtectionCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the write protection for RTC registers */
        RTC->WPR = 0xFF;
    }
    else
    {
        /* Disable the write protection for RTC registers */
        RTC->WPR = 0xCA;
        RTC->WPR = 0x53;
    }
}

/**
  * @brief  Enters the RTC Initialization mode.
  * @note   The RTC Initialization mode is write protected, use the
  *         RTC_WriteProtectionCmd(DISABLE) open write protect
  *         before calling this function.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC is in Init mode
  *          - ERROR:   RTC is not in Init mode
  */
ErrorStatus RTC_EnterInitMode(void)
{
    __IO uint32_t initcounter = 0x00;
    ErrorStatus status = ERROR;
    uint32_t initstatus = 0x00;

    /* Check if the Initialization mode is set */
    if ((RTC->ISR & RTC_ISR_INITF) == (uint32_t)RESET)/*the init not be set*/
    {
        /* Set the Initialization mode */
        RTC->ISR |= RTC_ISR_INIT;

        /* Wait till RTC is in INIT state INITF be set
         * and if Time out is reached exit */
        do
        {
            initstatus = (uint32_t)(RTC->ISR & RTC_ISR_INITF);
            initcounter++;
        }
        while ((initcounter != INITMODE_TIMEOUT) && (initstatus == 0x00));

        if ((RTC->ISR & RTC_ISR_INITF) != RESET)/*check if initf be set*/
        {
            status = SUCCESS;/*initf has be set,enter init mode*/
        }
        else
        {
            status = ERROR;/*enter init mode has error*/
        }
    }
    else/*the init has be set*/
    {
        status = SUCCESS;
    }
    return (status);
}

/**
  * @brief  Exits the RTC Initialization mode
  * @note   When the initialization sequence is complete, the calendar restarts
  *         counting after 4 RTCCLK cycles.
  * @note   The RTC Initialization mode is write protected, use the
  *         RTC_WriteProtectionCmd(DISABLE) before calling this function.
  * @param  None
  * @retval None
  */
void RTC_ExitInitMode(void)
{
    /* Exit Initialization mode */
    RTC->ISR &= ~RTC_ISR_INIT;/* clear init bit */

    /*when BypassShadow is enable,should wait initf bit clear zero*/
    if ((RTC->CR & RTC_CR_BYPSHAD) == RTC_CR_BYPSHAD)
    {
        while ((RTC->ISR & RTC_ISR_INITF) != RESET) {}
    }
}

/**
  * @brief  Waits until the RTC Time and Date registers (RTC_TR and RTC_DR) are
  *         synchronized with RTC APB clock.
  * @note   The RTC Resynchronization mode is write protected, use the
  *         RTC_WriteProtectionCmd(DISABLE) before calling this function.
  * @note   To read the calendar through the shadow registers after Calendar
  *         initialization, calendar update or after wakeup from low power modes
  *         the software must first clear the RSF flag.
  *         The software must then wait until it is set again before reading
  *         the calendar, which means that the calendar registers have been
  *         correctly copied into the RTC_TR and RTC_DR shadow registers.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC registers are synchronised
  *          - ERROR: RTC registers are not synchronised
  */
ErrorStatus RTC_WaitForSynchro(void)
{
    __IO uint32_t synchrocounter = 0;
    ErrorStatus status = ERROR;
    uint32_t synchrostatus = 0x00;

    /* check if bypass shadow register */
    if ((RTC->CR & RTC_CR_BYPSHAD) != RESET)
    {
        /* Bypass shadow register,read calendar will
         * direct access rtc_ssr,rtc_tr and rtc_dr register */
        status = SUCCESS;
    }
    else/*read calendar from rtc_ssr,rtc_tr,rtc_dr's shadow register*/
    {
        /* Disable the write protection for RTC registers */
        RTC->WPR = 0xCA;
        RTC->WPR = 0x53;

        /* Clear RSF flag */
        RTC->ISR &= (uint32_t)RTC_RSF_MASK;

        /* Wait the registers to be synchronised */
        do
        {
            synchrostatus = (uint32_t)(RTC->ISR & RTC_ISR_RSF);/* rsf be set again */
            synchrocounter++;
        }
        while ((synchrocounter != SYNCHRO_TIMEOUT) && (synchrostatus == 0x00));

        /* check if RSF be set again */
        if ((RTC->ISR & RTC_ISR_RSF) != RESET)
        {
            /* while not in bypass mode, rsf be set again
             * the calendar update finish*/
            status = SUCCESS;
        }
        else
        {
            status = ERROR;
        }

        /* Disable the write protection for RTC registers */
        RTC->WPR = 0xFF;
    }

    return (status);
}

/**
  * @brief  Enables or disables the RTC reference clock detection.
  * @param  NewState: new state of the RTC reference clock.
  *          This parameter can be: ENABLE or DISABLE.
  */
void RTC_RefClockCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the RTC reference clock detection */
        RTC->CR |= (uint32_t)RTC_CR_REFCKON;
    }
    else
    {
        /* Disable the RTC reference clock detection */
        RTC->CR &= (uint32_t)(~RTC_CR_REFCKON);
    }

}

/**
  * @brief  Enables or Disables the Bypass Shadow feature.
  * @note   When the Bypass Shadow is enabled the calendar value are taken
  *         directly from the Calendar counter.
  * @param  NewState: new state of the Bypass Shadow feature.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
*/
void RTC_BypassShadowCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Set the BYPSHAD bit */
        RTC->CR |= (uint32_t)RTC_CR_BYPSHAD;
    }
    else
    {
        /* Reset the BYPSHAD bit */
        RTC->CR &= (uint32_t)(~RTC_CR_BYPSHAD);
    }
}
/**
  * @}
  */

/**
  * @brief  Set the RTC current time.
  * @param  RTC_Format: specifies the format of the entered parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_Format_BIN:  Binary data format
  *            @arg RTC_Format_BCD:  BCD data format
  * @param  RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure that contains
  *                        the time configuration information for the RTC.
  *                        rtc's hours minutes and seconds,that rtc_h12 represent am/pm
  */
void RTC_SetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct)
{
    uint32_t tmpreg = 0;

    /* Check the parameters if RTC_Format_BIN or RTC_Format_BCD */
    assert_param(IS_RTC_FORMAT(RTC_Format));

    /* check rtc time format if binary */
    if (RTC_Format == RTC_Format_BIN)
    {
        /* check if hour format is 12 or 24 */
        if ((RTC->CR & RTC_CR_FMT) != (uint32_t)RESET)
        {
            /* set rtc_hours format is 12
             * check rtc hour if in range 0-12
             * set hour is am/pm */
            assert_param(IS_RTC_HOUR12(RTC_TimeStruct->RTC_Hours));
            assert_param(IS_RTC_H12(RTC_TimeStruct->RTC_H12));
        }
        else
        {
            /* set rtc_hours format is 24 */
            RTC_TimeStruct->RTC_H12 = 0x00;
            /* check hour if in range 0-23 */
            assert_param(IS_RTC_HOUR24(RTC_TimeStruct->RTC_Hours));
        }
        /* check rtc minutes and seconds in right range */
        assert_param(IS_RTC_MINUTES(RTC_TimeStruct->RTC_Minutes));
        assert_param(IS_RTC_SECONDS(RTC_TimeStruct->RTC_Seconds));
    }
    else/* rtc time format is bcd */
    {
        /* check if hour format is 12 or 24 */
        if ((RTC->CR & RTC_CR_FMT) != (uint32_t)RESET)
        {
            /* set rtc_hours format is 12 and am/pm
             * convert bcd to binary and set am/pm*/
            tmpreg = RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours);
            /* check hour if in range 0-12 */
            assert_param(IS_RTC_HOUR12(tmpreg));
            assert_param(IS_RTC_H12(RTC_TimeStruct->RTC_H12));
        }
        else
        {
            /* set rtc_hours format is 24 */
            RTC_TimeStruct->RTC_H12 = 0x00;
            /* check hour if in range 0-23 */
            assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours)));
        }
        /* check rtc minutes and seconds in right range */
        assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Minutes)));
        assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Seconds)));
    }

    /* Check the input parameters format */
    if (RTC_Format != RTC_Format_BIN)
    {
        /* rtc time format is binary */
        tmpreg = (((uint32_t)(RTC_TimeStruct->RTC_H12) << 22)    | \
                  ((uint32_t)(RTC_TimeStruct->RTC_Hours) << 16)  | \
                  ((uint32_t)(RTC_TimeStruct->RTC_Minutes) << 8) | \
                  ((uint32_t) RTC_TimeStruct->RTC_Seconds));
    }
    else
    {
        /* rtc time format is bcd
         * convert byte to bcd */
        tmpreg = (uint32_t)((((uint32_t)RTC_TimeStruct->RTC_H12) << 22)                   | \
                            ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Hours) << 16)  | \
                            ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Minutes) << 8) | \
                            ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Seconds)));
    }

    /* Set the RTC_TR register */
    RTC->TR = (uint32_t)(tmpreg & RTC_TR_RESERVED_MASK);
}

/**
  * @brief  Fills each RTC_TimeStruct member with its default value
  *         (Time = 00h:00min:00sec).
  * @param  RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure which will be
  *         initialized.
  * @retval None
  */
void RTC_TimeStructInit(RTC_TimeTypeDef* RTC_TimeStruct)
{
    /* Time = 00h:00min:00sec */
    RTC_TimeStruct->RTC_H12 = RTC_H12_AM;
    RTC_TimeStruct->RTC_Hours = 0;
    RTC_TimeStruct->RTC_Minutes = 0;
    RTC_TimeStruct->RTC_Seconds = 0;
}

/**
  * @brief  Get the RTC current Time.
  * @param  RTC_Format: specifies the format of the returned parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_Format_BIN:  Binary data format
  *            @arg RTC_Format_BCD:  BCD data format
  * @param RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure that will
  *                        contain the returned current time configuration.
  * @retval None
  */
void RTC_GetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));

    /* Get the RTC_TR register */
    /* the get's rtc time is bcd format*/
    tmpreg = (uint32_t)(RTC->TR & RTC_TR_RESERVED_MASK);

    /* Fill the structure fields with the read parameters */
    RTC_TimeStruct->RTC_Hours   = (uint8_t)((tmpreg & (RTC_TR_HT | RTC_TR_HU)) >> 16);
    RTC_TimeStruct->RTC_Minutes = (uint8_t)((tmpreg & (RTC_TR_MNT | RTC_TR_MNU)) >> 8);
    RTC_TimeStruct->RTC_Seconds = (uint8_t)(tmpreg & (RTC_TR_ST | RTC_TR_SU));
    RTC_TimeStruct->RTC_H12     = (uint8_t)((tmpreg & (RTC_TR_PM)) >> 22);

    /* Check the input parameters format */
    if (RTC_Format == RTC_Format_BIN)
    {
        /* want get the binary format rtc time */
        /* Convert the structure parameters to Binary format */
        RTC_TimeStruct->RTC_Hours   = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours);
        RTC_TimeStruct->RTC_Minutes = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Minutes);
        RTC_TimeStruct->RTC_Seconds = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Seconds);
    }
}

/**
  * @brief  Gets the RTC current Calendar Subseconds value.
  * @note   This function freeze the Time and Date registers after reading the
  *         SSR register.
  * @param  None
  * @retval RTC current Calendar Subseconds value.
  */
uint32_t RTC_GetSubSecond(void)
{
    uint32_t tmpreg = 0;

    /* Get subseconds values from the correspondent registers*/
    tmpreg = (uint32_t)(RTC->SSR);

    /* Read DR register to unfroze calendar registers */
    (void)(RTC->DR);

    return (tmpreg);
}

/**
  * @brief  Set the RTC current date.
  * @param  RTC_Format: specifies the format of the entered parameters.
  *          This parameter can be  one of the following values:
  *            @arg RTC_Format_BIN:  Binary data format
  *            @arg RTC_Format_BCD:  BCD data format
  * @param  RTC_DateStruct: pointer to a RTC_DateTypeDef structure that contains
  *                         the date configuration information for the RTC.
  */
void RTC_SetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));

    /* check rtc_month's mt if is 1 */
    if ((RTC_Format == RTC_Format_BIN) && ((RTC_DateStruct->RTC_Month & 0x10) == 0x10))
    {
        /* rtc_month's mt is 1,convert as low 4 bits expression */
        RTC_DateStruct->RTC_Month = (RTC_DateStruct->RTC_Month & (uint32_t)~(0x10)) + 0x0A;
    }
    if (RTC_Format == RTC_Format_BIN)
    {
        /* rtc_date is binary
         * check the rtc date in right range */
        assert_param(IS_RTC_YEAR(RTC_DateStruct->RTC_Year));
        assert_param(IS_RTC_MONTH(RTC_DateStruct->RTC_Month));
        assert_param(IS_RTC_DATE(RTC_DateStruct->RTC_Date));
    }
    else
    {
        /* rtc_date is bcd need convert as binary
         * check the rtc date in right range */
        assert_param(IS_RTC_YEAR(RTC_Bcd2ToByte(RTC_DateStruct->RTC_Year)));
        assert_param(IS_RTC_MONTH(RTC_Bcd2ToByte(RTC_DateStruct->RTC_Month)));
        assert_param(IS_RTC_DATE(RTC_Bcd2ToByte(RTC_DateStruct->RTC_Date)));
    }
    /* check the weekday in right range */
    assert_param(IS_RTC_WEEKDAY(RTC_DateStruct->RTC_WeekDay));

    /* Check the input parameters format */
    if (RTC_Format != RTC_Format_BIN)
    {
        /* rtc_datestruct as binary format */
        tmpreg = ((((uint32_t)RTC_DateStruct->RTC_Year) << 16) | \
                  (((uint32_t)RTC_DateStruct->RTC_Month) << 8) | \
                  ((uint32_t)RTC_DateStruct->RTC_Date) | \
                  (((uint32_t)RTC_DateStruct->RTC_WeekDay) << 13));
    }
    else
    {
        /* rtc_datestruct as bcd format
         * need convert as binary format */
        tmpreg = (((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Year) << 16) | \
                  ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Month) << 8) | \
                  ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Date)) | \
                  ((uint32_t)RTC_DateStruct->RTC_WeekDay << 13));
    }

    /* Set the RTC_DR register */
    RTC->DR = (uint32_t)(tmpreg & RTC_DR_RESERVED_MASK);
}

/**
  * @brief  Fills each RTC_DateStruct member with its default value
  *         (Monday, January 01 xx00).
  * @param  RTC_DateStruct: pointer to a RTC_DateTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void RTC_DateStructInit(RTC_DateTypeDef* RTC_DateStruct)
{
    /* Monday, January 01 xx00 */
    RTC_DateStruct->RTC_WeekDay = RTC_Weekday_Monday;
    RTC_DateStruct->RTC_Date = 1;
    RTC_DateStruct->RTC_Month = RTC_Month_January;
    RTC_DateStruct->RTC_Year = 0;
}

/**
  * @brief  Get the RTC current date.
  * @param  RTC_Format: specifies the format of the returned parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_Format_BIN: Binary data format
  *            @arg RTC_Format_BCD: BCD data format
  * @param RTC_DateStruct: pointer to a RTC_DateTypeDef structure that will
  *                        contain the returned current date configuration.
  * @retval None
  */
uint32_t RTC_GetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));

    /* Get the RTC_TR register */
    tmpreg = (uint32_t)(RTC->DR & RTC_DR_RESERVED_MASK);

    /* Fill the structure fields with the read parameters */
    /* the rtc_date format as bcd */
    RTC_DateStruct->RTC_Year    = (uint8_t)((tmpreg & (RTC_DR_YT | RTC_DR_YU)) >> 16);
    RTC_DateStruct->RTC_Month   = (uint8_t)((tmpreg & (RTC_DR_MT | RTC_DR_MU)) >> 8);
    RTC_DateStruct->RTC_Date    = (uint8_t)(tmpreg & (RTC_DR_DT | RTC_DR_DU));
    RTC_DateStruct->RTC_WeekDay = (uint8_t)((tmpreg & (RTC_DR_WDU)) >> 13);

    /* Check the input parameters format */
    /* the rtc_date format as binary */
    if (RTC_Format == RTC_Format_BIN)
    {
        /* Convert the structure parameters to Binary format */
        RTC_DateStruct->RTC_Year    = (uint8_t) RTC_Bcd2ToByte(RTC_DateStruct->RTC_Year);
        RTC_DateStruct->RTC_Month   = (uint8_t) RTC_Bcd2ToByte(RTC_DateStruct->RTC_Month);
        RTC_DateStruct->RTC_Date    = (uint8_t) RTC_Bcd2ToByte(RTC_DateStruct->RTC_Date);
        RTC_DateStruct->RTC_WeekDay = (uint8_t)(RTC_DateStruct->RTC_WeekDay);
    }
    return 0;
}
/**
  * @}
  */


/**
  * @brief  Set the specified RTC Alarm.
  * @note   The Alarm register can only be written when the corresponding
  *         Alarm is disabled (Use the RTC_AlarmaCmd(DISABLE)).
  * @param  RTC_Format: specifies the format of the returned parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_Format_BIN: Binary data format
  *            @arg RTC_Format_BCD: BCD data format
  * @param  RTC_Alarm: specifies the alarm to be configured.
  *          This parameter can be one of the following values:
  *            @arg RTC_Alarm_A: to select Alarm A
  *            @arg RTC_Alarm_B: to select Alarm B
  * @param  RTC_AlarmStruct: pointer to a RTC_AlarmTypeDef structure that
  *                          contains the alarm configuration parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_AlarmTime: RTC_Hours RTC_Minutes RTC_Seconds RTC_H12
  *            @arg RTC_AlarmMask: RTC_AlarmMask_None    RTC_AlarmMask_DateWeekDay
  *                                RTC_AlarmMask_Hours   RTC_AlarmMask_Minutes
  *                                RTC_AlarmMask_Seconds RTC_AlarmMask_All
  *            @arg RTC_AlarmDateWeekDaySel:RTC_AlarmDateWeekDaySel_Date
  *                                         RTC_AlarmDateWeekDaySel_WeekDay
  *            @arg RTC_AlarmDateWeekDay:date range 1-31
  *                                      RTC_Weekday_Monday    RTC_Weekday_Tuesday
  *                                      RTC_Weekday_Wednesday RTC_Weekday_Thursday
  *                                      RTC_Weekday_Friday    RTC_Weekday_Saturday
  *                                      RTC_Weekday_Sunday
  * @retval None
  */
void RTC_SetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));/* config alarma/alarmb register's struct format */
    assert_param(IS_RTC_ALARM(RTC_Alarm));/* choose alarma/alarmb */
    assert_param(IS_RTC_ALARM_MASK(RTC_AlarmStruct->RTC_AlarmMask));/* config alarm mask */
    assert_param(IS_RTC_ALARM_DATE_WEEKDAY_SEL(RTC_AlarmStruct->RTC_AlarmDateWeekDaySel));/* config alarm wdsel */

    if (RTC_Format == RTC_Format_BIN)/* rtc alarma/alarmb struct format is binary */
    {
        if ((RTC->CR & RTC_CR_FMT) != (uint32_t)RESET)/* rtc hour format is 12 */
        {
            /* check alarma/alarmb's hour range in 0-12 */
            assert_param(IS_RTC_HOUR12(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
            assert_param(IS_RTC_H12(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12));
        }
        else/* rtc hour format is 24 */
        {
            /* check alarma/alarmb's hour range in 0-23 */
            RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = 0x00;
            assert_param(IS_RTC_HOUR24(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
        }
        /* check alarma/alarmb's minutes and seconds in right range */
        assert_param(IS_RTC_MINUTES(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes));
        assert_param(IS_RTC_SECONDS(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds));

        /* judgement alarma/alarmb's wdsel=0 or 1 */
        if (RTC_AlarmStruct->RTC_AlarmDateWeekDaySel == RTC_AlarmDateWeekDaySel_Date)
        {
            /* while wdsel=0 check DU[3:0] if express day */
            assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(RTC_AlarmStruct->RTC_AlarmDateWeekDay));
        }
        else
        {
            /* while wdsel=1 check DU[3:0] if express weekday */
            assert_param(IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(RTC_AlarmStruct->RTC_AlarmDateWeekDay));
        }
    }
    else/* rtc alarma/alarmb struct format is bcd */
    {
        if ((RTC->CR & RTC_CR_FMT) != (uint32_t)RESET)
        {
            /* check alarma/alarmb's hour range in 0-12 */
            tmpreg = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours);
            assert_param(IS_RTC_HOUR12(tmpreg));
            assert_param(IS_RTC_H12(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12));
        }
        else/* rtc hour format is 24 */
        {
            /* check alarma/alarmb's hour range in 0-23 */
            RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = 0x00;
            assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours)));
        }
        /* check alarma/alarmb's minutes and seconds in right range */
        assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes)));
        assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds)));

        /* judgement alarma/alarmb's wdsel=0 or 1 */
        if (RTC_AlarmStruct->RTC_AlarmDateWeekDaySel == RTC_AlarmDateWeekDaySel_Date)
        {
            /* while wdsel=0 check DU[3:0] if express day */
            tmpreg = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDateWeekDay);
            assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(tmpreg));
        }
        else
        {
            /* while wdsel=1 check DU[3:0] if express weekday */
            tmpreg = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDateWeekDay);
            assert_param(IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(tmpreg));
        }
    }

    /* Check the input parameters format */
    if (RTC_Format != RTC_Format_BIN)
    {
        tmpreg = (((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours) << 16) | \
                  ((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes) << 8) | \
                  ((uint32_t)RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds) | \
                  ((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12) << 22) | \
                  ((uint32_t)(RTC_AlarmStruct->RTC_AlarmDateWeekDay) << 24) | \
                  ((uint32_t)RTC_AlarmStruct->RTC_AlarmDateWeekDaySel) | \
                  ((uint32_t)RTC_AlarmStruct->RTC_AlarmMask));
    }
    else
    {
        tmpreg = (((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours) << 16) | \
                  ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes) << 8) | \
                  ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds)) | \
                  ((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12) << 22) | \
                  ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDateWeekDay) << 24) | \
                  ((uint32_t)RTC_AlarmStruct->RTC_AlarmDateWeekDaySel) | \
                  ((uint32_t)RTC_AlarmStruct->RTC_AlarmMask));
    }

    if (RTC_Alarm == RTC_Alarm_A)
    {
        /* Configure the Alarm register */
        RTC->ALRMAR = (uint32_t)tmpreg;
    }
    else if (RTC_Alarm == RTC_Alarm_B)
    {
        /* Configure the Alarm register */
        RTC->ALRMBR = (uint32_t)tmpreg;
    }

}

/**
  * @brief  Fills each RTC_AlarmStruct member with its default value
  *         (Time = 00h:00mn:00sec / Date = 1st day of the month/Mask =
  *         all fields are masked).
  * @param  RTC_AlarmStruct: pointer to a @ref RTC_AlarmTypeDef structure which
  *         will be initialized.
  * @retval None
  */
void RTC_AlarmStructInit(RTC_AlarmTypeDef* RTC_AlarmStruct)
{
    /* Alarm Time Settings : Time = 00h:00mn:00sec */
    RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = RTC_H12_AM;
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = 0;
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = 0;
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = 0;

    /* Alarm Date Settings : Date = 1st day of the month */
    RTC_AlarmStruct->RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
    RTC_AlarmStruct->RTC_AlarmDateWeekDay = 1;

    /* Alarm Masks Settings : Mask =  all fields are not masked */
    RTC_AlarmStruct->RTC_AlarmMask = RTC_AlarmMask_None;
}

/**
  * @brief  Get the RTC Alarm value and masks.
  * @param  RTC_Format: specifies the format of the output parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_Format_BIN: Binary data format
  *            @arg RTC_Format_BCD: BCD data format
  * @param  RTC_Alarm: specifies the alarm to be read.
  *          This parameter can be one of the following values:
  *            @arg RTC_Alarm_A: to select Alarm A
  *            @arg RTC_Alarm_B: to select Alarm B
  * @param  RTC_AlarmStruct: pointer to a RTC_AlarmTypeDef structure that will
  *                          contains the output alarm configuration values.
  *          This parameter can be one of the following values:
  *            @arg RTC_AlarmTime: RTC_Hours RTC_Minutes RTC_Seconds RTC_H12
  *            @arg RTC_AlarmMask: RTC_AlarmMask_None    RTC_AlarmMask_DateWeekDay
  *                                RTC_AlarmMask_Hours   RTC_AlarmMask_Minutes
  *                                RTC_AlarmMask_Seconds RTC_AlarmMask_All
  *            @arg RTC_AlarmDateWeekDaySel:RTC_AlarmDateWeekDaySel_Date
  *                                         RTC_AlarmDateWeekDaySel_WeekDay
  *            @arg RTC_AlarmDateWeekDay:date range 1-31
  *                                      RTC_Weekday_Monday    RTC_Weekday_Tuesday
  *                                      RTC_Weekday_Wednesday RTC_Weekday_Thursday
  *                                      RTC_Weekday_Friday    RTC_Weekday_Saturday
  *                                      RTC_Weekday_Sunday
  * @retval None
  */
void RTC_GetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));
    assert_param(IS_RTC_ALARM(RTC_Alarm));

    if (RTC_Alarm == RTC_Alarm_A)
    {
        /* Get the RTC_ALRMAR register */
        tmpreg = (uint32_t)(RTC->ALRMAR);
    }
    else if (RTC_Alarm == RTC_Alarm_B)
    {
        /* Get the RTC_ALRMBR register */
        tmpreg = (uint32_t)(RTC->ALRMBR);
    }

    /* Fill the structure with the read parameters */
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours   = (uint32_t)((tmpreg & (RTC_ALRMAR_HT  | RTC_ALRMAR_HU)) >> 16);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = (uint32_t)((tmpreg & (RTC_ALRMAR_MNT | RTC_ALRMAR_MNU)) >> 8);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = (uint32_t)(tmpreg & (RTC_ALRMAR_ST  | RTC_ALRMAR_SU));
    RTC_AlarmStruct->RTC_AlarmTime.RTC_H12     = (uint32_t)((tmpreg &  RTC_ALRMAR_PM) >> 22);
    RTC_AlarmStruct->RTC_AlarmDateWeekDay      = (uint32_t)((tmpreg & (RTC_ALRMAR_DT  | RTC_ALRMAR_DU)) >> 24);
    RTC_AlarmStruct->RTC_AlarmDateWeekDaySel   = (uint32_t)(tmpreg &  RTC_ALRMAR_WDSEL);
    RTC_AlarmStruct->RTC_AlarmMask             = (uint32_t)(tmpreg &  RTC_AlarmMask_All);

    if (RTC_Format == RTC_Format_BIN)
    {
        RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours   = RTC_Bcd2ToByte(RTC_AlarmStruct -> RTC_AlarmTime.RTC_Hours);
        RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = RTC_Bcd2ToByte(RTC_AlarmStruct -> RTC_AlarmTime.RTC_Minutes);
        RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = RTC_Bcd2ToByte(RTC_AlarmStruct -> RTC_AlarmTime.RTC_Seconds);
        RTC_AlarmStruct->RTC_AlarmDateWeekDay      = RTC_Bcd2ToByte(RTC_AlarmStruct -> RTC_AlarmDateWeekDay);
    }
}

/**
  * @brief  Enables or disables the specified RTC Alarm.
  * @param  RTC_Alarm: specifies the alarm to be configured.
  *          This parameter can be any combination of the following values:
  *            @arg RTC_Alarm_A: to select Alarm A
  *            @arg RTC_Alarm_B: to select Alarm B
  * @param  NewState: new state of the specified alarm.
  *          This parameter can be: ENABLE or DISABLE.
  */
void RTC_AlarmCmd(uint32_t RTC_Alarm, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RTC_CMD_ALARM(RTC_Alarm));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Configure the Alarm state */
    if (NewState != DISABLE)
    {
        RTC->CR |= (uint32_t)RTC_Alarm;/* enable rtc alarma or alarmb */
    }
    else
    {
        /* Disable the Alarm in RTC_CR register */
        RTC->CR &= (uint32_t)~RTC_Alarm;
    }
}

/**
  * @brief  Configure the RTC AlarmA/B Subseconds value and mask.
  * @note   This function is performed only when the Alarm is disabled.
  * @param  RTC_Alarm: specifies the alarm to be configured.
  *          This parameter can be one of the following values:
  *            @arg RTC_Alarm_A: to select Alarm A
  *            @arg RTC_Alarm_B: to select Alarm B
  * @param  RTC_AlarmSubSecondValue: specifies the Subseconds value.
  *          This parameter can be a value from 0 to 0x00007FFF.
  * @param  RTC_AlarmSubSecondMask:  specifies the Subseconds Mask.
  *          This parameter can be any combination of the following values:
  *            @arg RTC_AlarmSubSecondMask_All: All Alarm SS fields are masked.
  *                                             There is no comparison on sub seconds for Alarm.
  *            @arg RTC_AlarmSubSecondMask_SS14_1: SS[14:1] are don't care in Alarm comparison.
  *                                                Only SS[0] is compared
  *            @arg RTC_AlarmSubSecondMask_SS14_2: SS[14:2] are don't care in Alarm comparison.
  *                                                Only SS[1:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_3: SS[14:3] are don't care in Alarm comparison.
  *                                                Only SS[2:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_4: SS[14:4] are don't care in Alarm comparison.
  *                                                Only SS[3:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_5: SS[14:5] are don't care in Alarm comparison.
  *                                                Only SS[4:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_6: SS[14:6] are don't care in Alarm comparison.
  *                                                Only SS[5:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_7: SS[14:7] are don't care in Alarm comparison.
  *                                                Only SS[6:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_8: SS[14:8] are don't care in Alarm comparison.
  *                                                Only SS[7:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_9: SS[14:9] are don't care in Alarm comparison.
  *                                                Only SS[8:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_10: SS[14:10] are don't care in Alarm comparison.
  *                                                 Only SS[9:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_11: SS[14:11] are don't care in Alarm comparison.
  *                                                 Only SS[10:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_12: SS[14:12] are don't care in Alarm comparison.
  *                                                 Only SS[11:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14_13: SS[14:13] are don't care in Alarm comparison.
  *                                                 Only SS[12:0] are compared
  *            @arg RTC_AlarmSubSecondMask_SS14: SS[14] is don't care in Alarm comparison.
  *                                              Only SS[13:0] are compared
  *            @arg RTC_AlarmSubSecondMask_None: SS[14:0] are compared and must match to activate alarm
  * @retval None
  */
void RTC_AlarmSubSecondConfig(uint32_t RTC_Alarm, uint32_t RTC_AlarmSubSecondValue, uint8_t RTC_AlarmSubSecondMask)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RTC_ALARM(RTC_Alarm));
    assert_param(IS_RTC_ALARM_SUB_SECOND_VALUE(RTC_AlarmSubSecondValue));
    assert_param(IS_RTC_ALARM_SUB_SECOND_MASK(RTC_AlarmSubSecondMask));

    /* Configure the Alarm A or Alarm B SubSecond registers */
    tmpreg = (uint32_t)(((uint32_t)(RTC_AlarmSubSecondValue)) | ((uint32_t)(RTC_AlarmSubSecondMask) << 24));

    if (RTC_Alarm == RTC_Alarm_A)
    {
        /* Configure the AlarmA SubSecond register */
        RTC->ALRMASSR = (uint32_t)tmpreg;
    }
    else if (RTC_Alarm == RTC_Alarm_B)
    {
        /* Configure the AlarmB SubSecond register */
        RTC->ALRMBSSR = (uint32_t)tmpreg;
    }
}

/**
  * @brief  Gets the RTC Alarm Subseconds value.
  * @param  RTC_Alarm: specifies the alarm to be read.
  *          This parameter can be one of the following values:
  *            @arg RTC_Alarm_A: to select Alarm A
  *            @arg RTC_Alarm_B: to select Alarm B
  * @param  None
  * @retval RTC Alarm Subseconds value.
  */
uint32_t RTC_GetAlarmSubSecond(uint32_t RTC_Alarm)
{
    uint32_t tmpreg = 0;

    if (RTC_Alarm == RTC_Alarm_A)
    {
        /* Get the RTC_ALRMAR register */
        tmpreg = (uint32_t)((RTC->ALRMASSR) & RTC_ALRMASSR_SS);
    }
    else if (RTC_Alarm == RTC_Alarm_B)
    {
        /* Get the RTC_ALRMBR register */
        tmpreg = (uint32_t)((RTC->ALRMBSSR) & RTC_ALRMBSSR_SS);
    }

    return (tmpreg);
}
/**
  * @}
  */



/**
  * @brief  Adds or substract one hour from the current time.
  * @param  RTC_DayLightSaveOperation: the value of hour adjustment.
  *          This parameter can be one of the following values:
  *            @arg RTC_DayLightSaving_SUB1H: Substract one hour (winter time)
  *            @arg RTC_DayLightSaving_ADD1H: Add one hour (summer time)
  * @param  RTC_StoreOperation: Specifies the value to be written in the BCK bit
  *                             in CR register to store the operation.
  *          This parameter can be one of the following values:
  *            @arg RTC_StoreOperation_Reset: BKP Bit Reset
  *            @arg RTC_StoreOperation_Set: BKP Bit Set
  * @retval None
  */
void RTC_DayLightSavingConfig(uint32_t RTC_DayLightSaving, uint32_t RTC_StoreOperation)
{
    /* Check the parameters */
    assert_param(IS_RTC_DAYLIGHT_SAVING(RTC_DayLightSaving));
    assert_param(IS_RTC_STORE_OPERATION(RTC_StoreOperation));

    /* Clear the bits to be configured */
    RTC->CR &= (uint32_t)~(RTC_CR_BKP);

    /* Configure the RTC_CR register */
    /* Based on the parameter config DayLightSaving ADD1H/SUB1H
     * and StoreOperation set/clear RTC_CR[BKP]*/
    RTC->CR |= (uint32_t)(RTC_DayLightSaving | RTC_StoreOperation);
}

/**
  * @brief  Returns the RTC Day Light Saving stored operation.
  * @param  None
  * @retval RTC Day Light Saving stored operation.
  *          - RTC_StoreOperation_Reset
  *          - RTC_StoreOperation_Set
  */
uint32_t RTC_GetStoreOperation(void)
{
    return (RTC->CR & RTC_CR_BKP);
}

/**
  * @}
  */

/**
  * @brief  Configures the RTC output source (AFO_ALARM).
  * @param  RTC_Output: Specifies which signal will be routed to the RTC output.
  *          This parameter can be one of the following values:
  *            @arg RTC_Output_Disable: No output selected
  *            @arg RTC_Output_AlarmA: signal of AlarmA mapped to output
  *            @arg RTC_Output_AlarmB: signal of AlarmB mapped to output
  *            @arg RTC_Output_WakeUp: signal of WakeUp mapped to output
  * @param  RTC_OutputPolarity: Specifies the polarity of the output signal.
  *          This parameter can be one of the following:
  *            @arg RTC_OutputPolarity_High: The output pin is high when the
  *                                          ALRAF is high (depending on OSEL)
  *            @arg RTC_OutputPolarity_Low: The output pin is low when the
  *                                         ALRAF is high (depending on OSEL)
  * @retval None
  */
void RTC_OutputConfig(uint32_t RTC_Output, uint32_t RTC_OutputPolarity)
{
    /* Check the parameters */
    assert_param(IS_RTC_OUTPUT(RTC_Output));
    assert_param(IS_RTC_OUTPUT_POL(RTC_OutputPolarity));

    /* Clear the bits before configured */
    RTC->CR &= (uint32_t)~(RTC_CR_OSEL | RTC_CR_POL);

    /* Configure the output selection and polarity
     * select rtc_alarm output is alraf/alrbf/wutf
     * and rtc_alarm output polarity is high/low*/
    RTC->CR |= (uint32_t)(RTC_Output | RTC_OutputPolarity);
}
/**
  * @}
  */


/**
  * @brief  Enables or disables the RTC_CALIB output through the relative pin.
  * @param  NewState: new state of the digital calibration Output.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_CalibOutputCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the RTC_CALIB output */
        RTC->CR |= (uint32_t)RTC_CR_COE;
    }
    else
    {
        /* Disable the RTC_CALIB output */
        RTC->CR &= (uint32_t)~RTC_CR_COE;
    }

}

/**
  * @brief  Configure the Calibration Pinout (RTC_CALIB) Selection (512Hz or 1Hz).
  * @param  RTC_CalibOutput: Select the Calibration output Selection .
  *          This parameter can be one of the following values:
  *            @arg RTC_CalibOutput_512Hz: A signal has a regular waveform at 512Hz.
  *            @arg RTC_CalibOutput_1Hz: A signal has a regular waveform at 1Hz.
  * @retval None
*/
void RTC_CalibOutputConfig(uint32_t RTC_CalibOutput)
{
    /* Check the parameters */
    assert_param(IS_RTC_CALIB_OUTPUT(RTC_CalibOutput));

    /*clear flags before config*/
    RTC->CR &= (uint32_t)~(RTC_CR_COSEL);

    /* Configure the RTC_CR register
     * Based on parameter RTC_CalibOutput_512Hz/1Hz*/
    RTC->CR |= (uint32_t)RTC_CalibOutput;

}

/**
  * @brief  Configures the Smooth Calibration Settings.
  * @param  RTC_SmoothCalibPeriod: Select the Smooth Calibration Period.
  *          This parameter can be can be one of the following values:
  *            @arg RTC_SmoothCalibPeriod_32sec: The smooth calibration periode is 32s.
  *            @arg RTC_SmoothCalibPeriod_16sec: The smooth calibration periode is 16s.
  *            @arg RTC_SmoothCalibPeriod_8sec: The smooth calibartion periode is 8s.
  * @param  RTC_SmoothCalibPlusPulses: Select to Set or reset the CALP bit.
  *          This parameter can be one of the following values:
  *            @arg RTC_SmoothCalibPlusPulses_Set: Add one RTCCLK puls every 2**11 pulses.
  *            @arg RTC_SmoothCalibPlusPulses_Reset: No RTCCLK pulses are added.
  * @param  RTC_SmoothCalibMinusPulsesValue: Select the value of CALM[8:0] bits.
  *          This parameter can be one any value from 0 to 0x000001FF.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Calib registers are configured
  *          - ERROR: RTC Calib registers are not configured
*/
ErrorStatus RTC_SmoothCalibConfig(uint32_t RTC_SmoothCalibPeriod,
                                  uint32_t RTC_SmoothCalibPlusPulses,
                                  uint32_t RTC_SmoothCalibMinusPulsesValue)
{
    ErrorStatus status = ERROR;
    uint32_t recalpfcount = 0;

    /* Check the parameters satisfy format*/
    assert_param(IS_RTC_SMOOTH_CALIB_PERIOD(RTC_SmoothCalibPeriod));
    assert_param(IS_RTC_SMOOTH_CALIB_PLUS(RTC_SmoothCalibPlusPulses));
    assert_param(IS_RTC_SMOOTH_CALIB_MINUS(RTC_SmoothCalibMinusPulsesValue));

    /* check if a calibration is pending*/
    if ((RTC->ISR & RTC_ISR_RECALPF) != RESET)
    {
        /* wait until the Calibration is completed*/
        while (((RTC->ISR & RTC_ISR_RECALPF) != RESET) && (recalpfcount != RECALPF_TIMEOUT))
        {
            recalpfcount++;
        }
    }

    /* check if the calibration pending is completed or if there is no calibration operation at all*/
    if ((RTC->ISR & RTC_ISR_RECALPF) == RESET)
    {
        /* Configure the Smooth calibration settings */
        RTC->CALR = (uint32_t)((uint32_t)RTC_SmoothCalibPeriod     | \
                               (uint32_t)RTC_SmoothCalibPlusPulses | \
                               (uint32_t)RTC_SmoothCalibMinusPulsesValue);
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }

    return (ErrorStatus)(status);
}
/**
  * @}
  */

/**
  * @brief  Enables or disables the RTC Rough Calibration.
  * @param  NewState: new state of the digital calibration Output.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_RoughCalibration(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the RTC Rough Calibration */
        RTC->CR |= (uint32_t)RTC_CR_DCE;
    }
    else
    {
        /* Disable the RTC Rough Calibration */
        RTC->CR &= (uint32_t)~RTC_CR_DCE;
    }

}

/**
  * @brief  Configures the Rough Digtial Calibration Settings.
  * @param  RTC_RoughCalibPlority: Select to Set or reset the DCS bit.
  *         This parameter can be one of the following values:
  *           @arg RTC_RoughCalibSymbol_Positive: Add calendar update frequence.
  *           @arg RTC_RoughCalibSymbol_Negative: Substract calendar update frequence.
  * @param  RTC_RoughCalibMinusPulsesValue: Select the value of DC[4:0] bits.
  *         This parameter can be one any value from 0 to 0x000001F.
*/
void RTC_RoughDigtialCalibConfig(uint32_t RTC_RoughCalibPolarity,
                                 uint32_t RTC_RoughCalibMinusPulsesValue)
{

    /* Check the parameters satisfy format*/
    assert_param(IS_RTC_ROUGH_CALIB_SYMBOL(RTC_RoughCalibPolarity));
    assert_param(IS_RTC_ROUGH_CALIB_DC_VALUE(RTC_RoughCalibMinusPulsesValue));

    /* clear the bits before config */
    RTC->CALIBR &= (uint32_t)~(RTC_CALIBR_DCS | RTC_CALIBR_DC);

    /* Configure the Smooth calibration settings */
    RTC->CALIBR |= (uint32_t)((uint32_t)RTC_RoughCalibPolarity | \
                              (uint32_t)RTC_RoughCalibMinusPulsesValue);
}
/**
  * @}
  */


/**
  * @brief  Enables or Disables the RTC TimeStamp functionality with
  *         the specified time stamp pin stimulating edge.
  * @param  RTC_TimeStampEdge: Specifies the pin edge on which the
  *         TimeStamp is activated.
  *         This parameter can be one of the following:
  *            @arg RTC_TimeStampEdge_Rising: the Time stamp event occurs on the rising
  *                                           edge of the related pin.
  *            @arg RTC_TimeStampEdge_Falling:the Time stamp event occurs on the
  *                                           falling edge of the related pin.
  * @param  NewState: new state of the TimeStamp.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_TimeStampCmd(uint32_t RTC_TimeStampEdge, FunctionalState NewState)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RTC_TIMESTAMP_EDGE(RTC_TimeStampEdge));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Get the RTC_CR register and clear the bits before configured */
    tmpreg = (uint32_t)(RTC->CR & (uint32_t)~(RTC_CR_TSEDGE | RTC_CR_TSE));

    /* Get the new configuration */
    if (NewState != DISABLE)
    {
        /* Enable Timestamp and config occur edge */
        tmpreg |= (uint32_t)(RTC_TimeStampEdge | RTC_CR_TSE);
    }
    else
    {
        /* Not Enable Timestamp */
        tmpreg |= (uint32_t)(RTC_TimeStampEdge);
    }

    /* Configure the Time Stamp TSEDGE and Enable bits */
    RTC->CR = (uint32_t)tmpreg;
}

/**
  * @brief  Get the RTC TimeStamp value and masks.
  * @param  RTC_Format: specifies the format of the output parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_Format_BIN: Binary data format
  *            @arg RTC_Format_BCD: BCD data format
  * @param RTC_StampTimeStruct: pointer to a RTC_TimeTypeDef structure that will
  *                             contains the TimeStamp time values.
  * @param RTC_StampDateStruct: pointer to a RTC_DateTypeDef structure that will
  *                             contains the TimeStamp date values.
  * @retval None
  */
void RTC_GetTimeStamp(uint32_t RTC_Format,
                      RTC_TimeTypeDef* RTC_StampTimeStruct,
                      RTC_DateTypeDef* RTC_StampDateStruct)
{
    uint32_t tmptime = 0, tmpdate = 0;

    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));

    /* Get the TimeStamp time and date registers values */
    tmptime = (uint32_t)(RTC->TSTR & RTC_TSTR_RESERVED_MASK);
    tmpdate = (uint32_t)(RTC->TSDR & RTC_TSDR_RESERVED_MASK);

    /* Fill the Time structure fields with the read parameters */
    RTC_StampTimeStruct->RTC_Hours   = (uint8_t)((tmptime & (RTC_TSTR_HT  | RTC_TSTR_HU)) >> 16);
    RTC_StampTimeStruct->RTC_Minutes = (uint8_t)((tmptime & (RTC_TSTR_MNT | RTC_TSTR_MNU)) >> 8);
    RTC_StampTimeStruct->RTC_Seconds = (uint8_t)(tmptime & (RTC_TSTR_ST  | RTC_TSTR_SU));
    RTC_StampTimeStruct->RTC_H12     = (uint8_t)((tmptime & (RTC_TSTR_PM)) >> 22);

    /* Fill the Date structure fields with the read parameters */
    RTC_StampDateStruct->RTC_Year    = 0;
    RTC_StampDateStruct->RTC_Month   = (uint8_t)((tmpdate & (RTC_TSDR_MT | RTC_TSDR_MU)) >> 8);
    RTC_StampDateStruct->RTC_Date    = (uint8_t)(tmpdate & (RTC_TSDR_DT | RTC_TSDR_DU));
    RTC_StampDateStruct->RTC_WeekDay = (uint8_t)((tmpdate & (RTC_TSDR_WDU)) >> 13);

    /* Check the input parameters format */
    if (RTC_Format == RTC_Format_BIN)
    {
        /* Convert the Time structure parameters to Binary format */
        RTC_StampTimeStruct->RTC_Hours   = (uint8_t)RTC_Bcd2ToByte(RTC_StampTimeStruct->RTC_Hours);
        RTC_StampTimeStruct->RTC_Minutes = (uint8_t)RTC_Bcd2ToByte(RTC_StampTimeStruct->RTC_Minutes);
        RTC_StampTimeStruct->RTC_Seconds = (uint8_t)RTC_Bcd2ToByte(RTC_StampTimeStruct->RTC_Seconds);

        /* Convert the Date structure parameters to Binary format */
        RTC_StampDateStruct->RTC_Month   = (uint8_t)RTC_Bcd2ToByte(RTC_StampDateStruct->RTC_Month);
        RTC_StampDateStruct->RTC_Date    = (uint8_t)RTC_Bcd2ToByte(RTC_StampDateStruct->RTC_Date);
        RTC_StampDateStruct->RTC_WeekDay = (uint8_t)RTC_Bcd2ToByte(RTC_StampDateStruct->RTC_WeekDay);
    }
}

/**
  * @brief  Get the RTC timestamp Subseconds value.
  * @param  None
  * @retval RTC current timestamp Subseconds value.
  */
uint32_t RTC_GetTimeStampSubSecond(void)
{
    /* Get timestamp subseconds values from the correspondent registers */
    return (uint32_t)(RTC->TSSSR);
}
/**
  * @}
  */

/**
  * @brief  Configures the select Tamper pin edge.
  * @param  RTC_Tamper: Selected tamper pin.
  *         This parameter can be any combination of the following values:
  *            @arg RTC_Tamper_1: Select Tamper 1.
  *            @arg RTC_Tamper_2: Select Tamper 2.
  * @param  RTC_TamperTrigger: Specifies the trigger on the tamper pin that
  *                            stimulates tamper event.
  *          This parameter can be one of the following values:
  *            @arg RTC_TamperTrigger_RisingEdge:  Rising Edge of the tamper pin causes tamper event.
  *            @arg RTC_TamperTrigger_FallingEdge: Falling Edge of the tamper pin causes tamper event.
  *            @arg RTC_TamperTrigger_LowLevel:    Low Level of the tamper pin causes tamper event.
  *            @arg RTC_TamperTrigger_HighLevel:   High Level of the tamper pin causes tamper event.
  * @retval None
  */
void RTC_TamperTriggerConfig(uint32_t RTC_Tamper, uint32_t RTC_TamperTrigger)
{
    /* Check the parameters */
    assert_param(IS_RTC_TAMPER(RTC_Tamper));
    assert_param(IS_RTC_TAMPER_TRIGGER(RTC_TamperTrigger));

    /* while tampflt==00,the pin edge trigger tamper event */
    if (RTC_TamperTrigger == RTC_TamperTrigger_RisingEdge)
    {
        /* Configure the RTC_TAFCR register */
        /* Clear Tamp1trg or Tamp2trg */
        RTC->TAFCR &= (uint32_t)((uint32_t)~(RTC_Tamper << 1));
    }

    if (RTC_TamperTrigger == RTC_TamperTrigger_FallingEdge)
    {
        /* Configure the RTC_TAFCR register */
        /* Set Tamp1trg or Tamp2trg */
        RTC->TAFCR |= (uint32_t)(RTC_Tamper << 1);
    }

    /* while tampflt!=00,the pin level trigger tamper event */
    if (RTC_TamperTrigger == RTC_TamperTrigger_LowLevel)
    {
        /* Configure the RTC_TAFCR register */
        /* Clear Tamp1trg or Tamp2trg */
        RTC->TAFCR &= (uint32_t)((uint32_t)~(RTC_Tamper << 1));
    }

    if (RTC_TamperTrigger == RTC_TamperTrigger_HighLevel)
    {
        /* Configure the RTC_TAFCR register */
        /* Set Tamp1trg or Tamp2trg */
        RTC->TAFCR |= (uint32_t)(RTC_Tamper << 1);
    }
}

/**
  * @brief  Enables or Disables the Tamper detection.
  * @param  RTC_Tamper: Selected tamper pin.
  *         This parameter can be any combination of the following values:
  *            @arg RTC_Tamper_1: Select Tamper 1.
  *            @arg RTC_Tamper_2: Select Tamper 2.
  * @param  NewState: new state of the tamper pin.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_TamperCmd(uint32_t RTC_Tamper, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RTC_TAMPER(RTC_Tamper));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected Tamper1 or Tamper2 pin */
        RTC->TAFCR |= (uint32_t)RTC_Tamper;
    }
    else
    {
        /* Disable the selected Tamper1 or Tamper2 pin */
        RTC->TAFCR &= (uint32_t)~RTC_Tamper;
    }
}

/**
  * @brief  Configures the Tampers Filter.
  * @param  RTC_TamperFilter: Specifies the tampers filter.
  *         This parameter can be one of the following values:
  *            @arg RTC_TamperFilter_Disable: Tamper filter is disabled.
  *            @arg RTC_TamperFilter_2Sample: Tamper is activated after 2
  *                                           consecutive samples at the active level
  *            @arg RTC_TamperFilter_4Sample: Tamper is activated after 4
  *                                           consecutive samples at the active level
  *            @arg RTC_TamperFilter_8Sample: Tamper is activated after 8
  *                                           consecutive samples at the active level
  * @retval None
  */
void RTC_TamperFilterConfig(uint32_t RTC_TamperFilter)
{
    /* Check the parameters */
    assert_param(IS_RTC_TAMPER_FILTER(RTC_TamperFilter));

    /* Clear TAMPFLT[1:0] bits in the RTC_TAFCR register */
    RTC->TAFCR &= (uint32_t)~(RTC_TAFCR_TAMPFLT);

    /* Configure the RTC_TAFCR register */
    RTC->TAFCR |= (uint32_t)RTC_TamperFilter;
}

/**
  * @brief  Configures the Tampers Sampling Frequency.
  * @param  RTC_TamperSamplingFreq: Specifies the tampers Sampling Frequency.
  *         This parameter can be one of the following values:
  *          @arg RTC_TamperSamplingFreq_RTCCLK_Div32768: Tamper inputs sampled frequency = RTCCLK / 32768
  *          @arg RTC_TamperSamplingFreq_RTCCLK_Div16384: Tamper inputs sampled frequency = RTCCLK / 16384
  *          @arg RTC_TamperSamplingFreq_RTCCLK_Div8192:  Tamper inputs sampled frequency = RTCCLK / 8192
  *          @arg RTC_TamperSamplingFreq_RTCCLK_Div4096:  Tamper inputs sampled frequency = RTCCLK / 4096
  *          @arg RTC_TamperSamplingFreq_RTCCLK_Div2048:  Tamper inputs sampled frequency = RTCCLK / 2048
  *          @arg RTC_TamperSamplingFreq_RTCCLK_Div1024:  Tamper inputs sampled frequency = RTCCLK / 1024
  *          @arg RTC_TamperSamplingFreq_RTCCLK_Div512:   Tamper inputs sampled frequency = RTCCLK / 512
  *          @arg RTC_TamperSamplingFreq_RTCCLK_Div256:   Tamper inputs sampled frequency = RTCCLK / 256
  * @retval None
  */
void RTC_TamperSamplingFreqConfig(uint32_t RTC_TamperSamplingFreq)
{
    /* Check the parameters */
    assert_param(IS_RTC_TAMPER_SAMPLING_FREQ(RTC_TamperSamplingFreq));

    /* Clear TAMPFREQ[2:0] bits in the RTC_TAFCR register */
    RTC->TAFCR &= (uint32_t)~(RTC_TAFCR_TAMPFREQ);

    /* Configure the RTC_TAFCR register */
    RTC->TAFCR |= (uint32_t)RTC_TamperSamplingFreq;
}

/**
  * @brief Configures the Tampers Pins input Precharge Duration.
  * @param RTC_TamperPrechargeDuration: Specifies the Tampers Pins input Precharge Duration.
  *        This parameter can be one of the following values:
  *           @arg RTC_TamperPrechargeDuration_1RTCCLK: Tamper pins are precharged 1 RTCCLK
  *           @arg RTC_TamperPrechargeDuration_2RTCCLK: Tamper pins are precharged 2 RTCCLK
  *           @arg RTC_TamperPrechargeDuration_4RTCCLK: Tamper pins are precharged 4 RTCCLK
  *           @arg RTC_TamperPrechargeDuration_8RTCCLK: Tamper pins are precharged 8 RTCCLK
  * @retval None
  */
void RTC_TamperPinsPrechargeDuration(uint32_t RTC_TamperPrechargeDuration)
{
    /* Check the parameters */
    assert_param(IS_RTC_TAMPER_PRECHARGE_DURATION(RTC_TamperPrechargeDuration));

    /* Clear TAMPPRCH[1:0] bits in the RTC_TAFCR register */
    RTC->TAFCR &= (uint32_t)~(RTC_TAFCR_TAMPPRCH);

    /* Configure the RTC_TAFCR register */
    RTC->TAFCR |= (uint32_t)RTC_TamperPrechargeDuration;
}

/**
  * @brief  Enables or Disables the TimeStamp on Tamper Detection Event.
  * @note   The timestamp is valid even the TSE bit in tamper control register
  *         is reset.
  * @param  NewState: new state of the timestamp on tamper event.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_TimeStampOnTamperDetectionCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Save timestamp on tamper detection event */
        /* tamp event trigger timestamp */
        RTC->TAFCR |= (uint32_t)RTC_TAFCR_TAMPTS;
    }
    else
    {
        /* Tamper detection does not cause a timestamp to be saved */
        RTC->TAFCR &= (uint32_t)~RTC_TAFCR_TAMPTS;
    }
}

/**
  * @brief  Enables or Disables the Precharge of Tamper pin.
  * @param  NewState: new state of tamper pull up.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_TamperPullUpCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable precharge of the selected Tamper pin */
        /* precharge tamp pin before sampled */
        RTC->TAFCR &= (uint32_t)~RTC_TAFCR_TAMPPUDIS;
    }
    else
    {
        /* Disable precharge of the selected Tamper pin */
        /* Forbidded tamp pins precharge function */
        RTC->TAFCR |= (uint32_t)RTC_TAFCR_TAMPPUDIS;
    }
}
/**
  * @}
  */

/**
  * @brief  Configures the RTC Output Pin mode.
  * @param  RTC_OutputType: specifies the RTC Output (PC13) pin mode.
  *         This parameter can be one of the following values:
  *          @arg RTC_OutputType_OpenDrain: RTC Output (PC13) is configured in
  *                                    Open Drain mode.
  *          @arg RTC_OutputType_PushPull:  RTC Output (PC13) is configured in
  *                                    Push Pull mode.
  * @retval None
  */
void RTC_OutputTypeConfig(uint32_t RTC_OutputType)
{
    /* Check the parameters */
    assert_param(IS_RTC_OUTPUT_TYPE(RTC_OutputType));

    RTC->TAFCR &= (uint32_t)~(RTC_TAFCR_PC13VALUE);
    RTC->TAFCR |= (uint32_t)(RTC_OutputType);
}
/**
  * @}
  */

/**
  * @brief  Configures the RTC Output Pin mode.
  * @param  RTC_OutputMode: specifies the RTC Output (PC13) pin mode.
  *         This parameter can be one of the following values:
  *          @arg RTC_PC13_OutputType_GPIO: RTC Output (PC13) is configured in
  *                                    gpio.
  *          @arg RTC_PC13_OutputType_PushPull:  RTC Output (PC13) is configured in
  *                                    Push Pull mode.
  * @retval None
  */
void RTC_OutputModeConfig(uint32_t RTC_OutputMode)
{
    /* Check the parameters */
    assert_param(IS_RTC_PC13_OUTPUT_TYPE(RTC_OutputMode));

    RTC->TAFCR &= (uint32_t)~(RTC_TAFCR_PC13MODE);
    RTC->TAFCR |= (uint32_t)(RTC_OutputMode);
}
/**
  * @}
  */

/**
  * @brief  Configures the RTC Pc15 Output Pin mode.
  * @param  RTC_Pc15_OutputType: specifies the RTC Output (PC15) pin mode.
  *         This parameter can be one of the following values:
  *          @arg RTC_PC15_OutputType_GPIO:     RTC Output (PC15) is configured by gpio.
  *          @arg RTC_PC15_OutputType_PushPull: RTC Output (PC15) is configured Push Pull mode.
  * @param  RTC_Pc15_OutputData: specifies the RTC Output (PC15) data.
  *         This parameter can be one of the following values:
  *          @arg RTC_PC15_OutputData_0: RTC Output Data (PC15) is configured 0.
  *          @arg RTC_PC15_OutputData_1: RTC Output Data (PC15) is configured 1.
  * @retval None
  */
void RTC_Pc15_OutputTypeDataConfig(uint32_t RTC_Pc15_OutputType, uint32_t RTC_Pc15_OutputData)
{
    /* Check the parameters */
    assert_param(IS_RTC_PC15_OUTPUT_TYPE(RTC_Pc15_OutputType));
    assert_param(IS_RTC_PC15_OUTPUT_DATA(RTC_Pc15_OutputData));

    /*clear pc15mode and value*/
    RTC->TAFCR &= ~(uint32_t)(RTC_PC15_OutputType_PushPull | RTC_PC15_OutputData_1);

    /* config pc14mode and value */
    RTC->TAFCR |= (uint32_t)(RTC_Pc15_OutputType | RTC_Pc15_OutputData);
}
/**
  * @}
  */

/**
  * @brief  Configures the RTC Pc14 Output Pin mode.
  * @param  RTC_Pc14_OutputType: specifies the RTC Output (PC14) pin mode.
  *         This parameter can be one of the following values:
  *          @arg RTC_PC14_OutputType_GPIO:     RTC Output (PC14) is configured by gpio.
  *          @arg RTC_PC14_OutputType_PushPull: RTC Output (PC14) is configured Push Pull mode.
  * @param  RTC_Pc14_OutputData: specifies the RTC Output (PC14) data.
  *         This parameter can be one of the following values:
  *          @arg RTC_PC14_OutputData_0: RTC Output Data (PC14) is configured 0.
  *          @arg RTC_PC14_OutputData_1: RTC Output Data (PC14) is configured 1.
  * @retval None
  */
void RTC_Pc14_OutputTypeDataConfig(uint32_t RTC_Pc14_OutputType, uint32_t RTC_Pc14_OutputData)
{
    /* Check the parameters */
    assert_param(IS_RTC_PC14_OUTPUT_TYPE(RTC_Pc14_OutputType));
    assert_param(IS_RTC_PC14_OUTPUT_DATA(RTC_Pc14_OutputData));

    /*clear pc14mode and value*/
    RTC->TAFCR &= ~(uint32_t)(RTC_PC14_OutputType_PushPull | RTC_PC14_OutputData_1);

    /* config pc14mode and value */
    RTC->TAFCR |= (uint32_t)(RTC_Pc14_OutputType | RTC_Pc14_OutputData);
}
/**
  * @}
  */

/**
  * @brief  Configures the Synchronization Shift Control Settings.
  * @note   When REFCKON is set, firmware must not write to Shift control register
  * @param  RTC_ShiftAdd1S: Select to add or not 1 second to the time Calendar.
  *         This parameter can be one of the following values :
  *          @arg RTC_ShiftAdd1S_Set:   Add one second to the clock calendar.
  *          @arg RTC_ShiftAdd1S_Reset: No effect.
  * @param  RTC_ShiftSubFS: Select the number of Second Fractions to Substitute.
  *         This parameter can be one any value from 0 to 0x7FFF.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Shift registers are configured
  *          - ERROR:   RTC Shift registers are not configured
*/
ErrorStatus RTC_SynchroShiftConfig(uint32_t RTC_ShiftAdd1S, uint32_t RTC_ShiftSubFS)
{
    ErrorStatus status = ERROR;
    uint32_t shpfcount = 0;

    /* Check the parameters */
    assert_param(IS_RTC_SHIFT_ADD1S(RTC_ShiftAdd1S));
    assert_param(IS_RTC_SHIFT_SUBFS(RTC_ShiftSubFS));

    /* Check if a Shift is pending*/
    if ((RTC->ISR & RTC_ISR_SHPF) != RESET)
    {
        /* Wait until the shift is completed*/
        while (((RTC->ISR & RTC_ISR_SHPF) != RESET) && (shpfcount != SHPF_TIMEOUT))
        {
            shpfcount++;
        }
    }

    /* Check if the Shift pending is completed or if there is no Shift operation at all*/
    if ((RTC->ISR & RTC_ISR_SHPF) == RESET)
    {
        /* check if the reference clock detection is disabled */
        if ((RTC->CR & RTC_CR_REFCKON) == RESET)
        {
            /* Configure the Shift settings */
            RTC->SHIFTR = (uint32_t)(uint32_t)(RTC_ShiftSubFS) | (uint32_t)(RTC_ShiftAdd1S);
            status = SUCCESS;/* reference clock detection is disabled, shiftr can be config */
        }
        else
        {
            status = ERROR;/* reference clock detection is enabled, shiftr can not config */
        }
    }
    else
    {
        status = ERROR;/* shpf be set, shiftr can not config */
    }

    return (ErrorStatus)(status);
}
/**
  * @}
  */

/**
  * @brief  Enables or disables the specified RTC interrupts.
  * @param  RTC_IT_ENABLE: specifies the RTC interrupt sources to
  *                        be enabled or disabled.
  *         This parameter can be any combination of the following values:
  *           @arg RTC_IT_TS_EN:   Time Stamp interrupt mask
  *           @arg RTC_IT_WUT_EN:  WakeUp Timer interrupt mask
  *           @arg RTC_IT_ALRB_EN: Alarm B interrupt mask
  *           @arg RTC_IT_ALRA_EN: Alarm A interrupt mask
  *           @arg RTC_IT_TAMP_EN: Tamper event interrupt mask
  * @param  NewState: new state of the specified RTC interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_ITConfig(uint32_t RTC_IT_ENABLE, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RTC_CONFIG_IT(RTC_IT_ENABLE));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Configure the Interrupts in the RTC_CR register */
        RTC->CR    |= (uint32_t)(RTC_IT_ENABLE & ~RTC_TAFCR_TAMPIE);
        /* Configure the Tamper Interrupt in the RTC_TAFCR */
        RTC->TAFCR |= (uint32_t)(RTC_IT_ENABLE & RTC_TAFCR_TAMPIE);
    }
    else
    {
        /* Configure the Interrupts in the RTC_CR register */
        RTC->CR    &= (uint32_t)~(RTC_IT_ENABLE & ~RTC_TAFCR_TAMPIE);
        /* Configure the Tamper Interrupt in the RTC_TAFCR */
        RTC->TAFCR &= (uint32_t)~(RTC_IT_ENABLE & RTC_TAFCR_TAMPIE);
    }
}

/**
  * @brief  Checks whether the specified RTC flag is set or not.
  * @param  RTC_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg RTC_FLAG_RECALPF: RECALPF event flag
  *            @arg RTC_FLAG_TAMP2F:  Tamper 2 event flag
  *            @arg RTC_FLAG_TAMP1F:  Tamper 1 event flag
  *            @arg RTC_FLAG_TSOVF:   Time Stamp OverFlow flag
  *            @arg RTC_FLAG_TSF:     Time Stamp event flag
  *            @arg RTC_FLAG_WUTF:    Auto WakeUp Timer flag
  *            @arg RTC_FLAG_ALRBF:   Alarm B flag
  *            @arg RTC_FLAG_ALRAF:   Alarm A flag
  *            @arg RTC_FLAG_INITF:   Initialization mode flag
  *            @arg RTC_FLAG_RSF:     Calendar Shadow Registers Synchronized flag
  *            @arg RTC_FLAG_INITS:   Calendar initialization flag
  *            @arg RTC_FLAG_SHPF:    Shift Operation Pending flag
  *            @arg RTC_FLAG_WUTWF:   Auto Weakup Register allow write flag
  *            @arg RTC_FLAG_ALRBWF:  Alarma Registers allow write flag
  *            @arg RTC_FLAG_ALRAWF:  Alarmb Registers allow write flag
  * @retval The new state of RTC_FLAG (SET or RESET).
  */
FlagStatus RTC_GetFlagStatus(uint32_t RTC_FLAG)
{
    FlagStatus bitstatus = RESET;
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RTC_GET_FLAG(RTC_FLAG));

    /* Get all the flags */
    tmpreg = (uint32_t)(RTC->ISR & RTC_FLAGS_MASK);

    /* Return the status of the flag */
    /* Check Rtc_Flag if be set */
    if ((tmpreg & RTC_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;/* rtc_flag be set */
    }
    else
    {
        bitstatus = RESET;/* rtc_flag not be set */
    }
    return bitstatus;
}

/**
  * @brief  Clears the RTC's pending flags.
  * @param  RTC_FLAG: specifies the RTC flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg RTC_FLAG_TAMP2F: Tamper 2 event flag
  *            @arg RTC_FLAG_TAMP1F: Tamper 1 event flag
  *            @arg RTC_FLAG_TSOVF:  Time Stamp Overflow flag
  *            @arg RTC_FLAG_TSF:    Time Stamp event flag
  *            @arg RTC_FLAG_WUTF:   aUTO WakeUp Timer flag
  *            @arg RTC_FLAG_ALRBF:  Alarm B flag
  *            @arg RTC_FLAG_ALRAF:  Alarm A flag
  *            @arg RTC_FLAG_RSF:    Calendar Shadow Registers Synchronized flag
  * @retval None
  */
void RTC_ClearFlag(uint32_t RTC_FLAG)
{
    /* Check the parameters */
    assert_param(IS_RTC_CLEAR_FLAG(RTC_FLAG));

    /* Clear the Flags in the RTC_ISR register */
    RTC->ISR &= ~(uint32_t)RTC_FLAG;
}

/**
  * @brief  Checks whether the specified RTC interrupt has occurred or not.
  * @param  RTC_IT_ENABLE: specifies the RTC interrupt source to check.
  *         This parameter can be one of the following values:
  *           @arg RTC_IT_TS_EN:   Time Stamp interrupt
  *           @arg RTC_IT_WUT_EN:  Auto WakeUp Timer interrupt
  *           @arg RTC_IT_ALRB_EN: Alarm B interrupt
  *           @arg RTC_IT_ALRA_EN: Alarm A interrupt
  *           @arg RTC_IT_TAMP_EN: Tamper interrupt
  * @retval The new state of RTC_IT (SET or RESET).
  */
ITStatus RTC_GetITStatus(uint32_t RTC_IT_ENABLE)
{
    ITStatus bitstatus = RESET;
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RTC_GET_IT(RTC_IT_ENABLE));

    if (RTC_IT_ENABLE == RTC_IT_TAMP_EN)
    {
        /* Get rtc_tamp interrupt enable */
        tmpreg = (uint32_t)(RTC->TAFCR & RTC_TAFCR_TAMPIE);
        /* Check rtc_tamp interrupt if be enable */
        if (tmpreg != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    else
    {
        /* Get rtc_cr register's interrupt enable */
        tmpreg = (uint32_t)(RTC->CR & RTC_IT_ENABLE);
        /* Check rtc_cr register's interrupt if be enable */
        if (tmpreg != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }

    return bitstatus;
}

/**
  * @brief  Clears the RTC's interrupt pending bits.
  * @param  RTC_IT_FLAG: specifies the RTC interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *            @arg RTC_IT_TS: Time Stamp interrupt
  *            @arg RTC_IT_WUT: WakeUp Timer interrupt
  *            @arg RTC_IT_ALRB: Alarm B interrupt
  *            @arg RTC_IT_ALRA: Alarm A interrupt
  *            @arg RTC_IT_TAMP1: Tamper1 event interrupt
  *            @arg RTC_IT_TAMP2: Tamper2 event interrupt
  * @retval None
  */
void RTC_ClearITPendingBit(uint32_t RTC_IT_FLAG)
{

    /* Check the parameters */
    assert_param(IS_RTC_CLEAR_IT(RTC_IT_FLAG));

    /* Clear the interrupt pending bits in the RTC_ISR register */
    RTC->ISR &= (uint32_t)~((uint32_t)RTC_IT_FLAG);
}
/**
  * @}
  */

/**
  * @brief  Enables or Disables the Auto Weakup.
  * @note   The auto weakup is valid even the WUTE bit in rtc control register
  *         is defaut reset.
  * @param  NewState: new state of the timestamp on tamper event.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_WeakUpCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable Auto WeakUp Function */
        RTC->CR |= (uint32_t)RTC_CR_WUTE;
    }
    else
    {
        /* Disable Auto WeakUp Function  */
        RTC->CR &= (uint32_t)~RTC_CR_WUTE;
    }
}

/**
  * @brief  Configures the Auto WeakUp Counter.
  * @param  RTC_WeakUp_Counter: Specifies the tampers filter.
  *         This parameter only on the range of 0~0xFFFF
  * @retval None
  */
void RTC_SetWeakUpCounter(uint32_t RTC_WeakUp_Counter)
{
    /* Check the parameters */
    assert_param(IS_RTC_WKUP_COUNTER(RTC_WeakUp_Counter));

    /* Clear WUTR[15:0] bits in the RTC_WUTR register */
    RTC->WUTR &= (uint32_t)~(RTC_WUTR_MASK);

    /* Configure the RTC_WUTR register */
    RTC->WUTR |= (uint32_t)RTC_WeakUp_Counter;
}

/**
  * @brief  Get the Auto WeakUp Counter.
  * @param  RTC_WeakUp_Counter: Specifies the tampers filter.
  *         This parameter only on the range of 0~0xFFFF
  * @retval None
  */
uint32_t RTC_GetWeakUpCounter(void)
{
    /* Return the RTC_WUTR register */
    return (uint32_t)(RTC->WUTR);
}

/**
  * @brief  Configures the Auto WeakUp Counting Frequency.
  * @param  RTC_WeakUpCountFreq: Specifies the tampers Sampling Frequency.
  *         This parameter can be one of the following values:
  *          @arg RTC_WeakUp_RTCCLK_Div16:   Auto WeakUp Counting frequency = RTCCLK/16
  *          @arg RTC_WeakUp_RTCCLK_Div8:    Auto WeakUp Counting frequency = RTCCLK/8
  *          @arg RTC_WeakUp_RTCCLK_Div4:    Auto WeakUp Counting frequency = RTCCLK/4
  *          @arg RTC_WeakUp_RTCCLK_Div2:    Auto WeakUp Counting frequency = RTCCLK/2
  *          @arg RTC_WeakUp_RTCCLK_CkSpre4: Auto WeakUp Counting frequency = CK_SPRE4
  *          @arg RTC_WeakUp_RTCCLK_CkSpre5: Auto WeakUp Counting frequency = CK_SPRE5
  *          @arg RTC_WeakUp_RTCCLK_CkSpre6: Auto WeakUp Counting frequency = CK_SPRE6
  *          @arg RTC_WeakUp_RTCCLK_CkSpre7: Auto WeakUp Counting frequency = CK_SPRE7
  * @retval None
  */
void RTC_WeakUpCountFreqConfig(uint32_t RTC_WeakUpCountFreq)
{
    /* Check the parameters */
    assert_param(IS_RTC_WKUP_COUNTER(RTC_WeakUpCountFreq));

    /* Clear WUCKSEL[2:0] bits in the RTC_CR register */
    RTC->CR &= (uint32_t)~(RTC_CR_WUCKSEL);

    /* Configure the RTC_CR register */
    RTC->CR |= (uint32_t)RTC_WeakUpCountFreq;
}

/**
  * @brief  Configures the BackUp Register Data.
  * @param  RTC_BackUpReg:choose rtc backup reg
  *         This parameter can be one of the following values:
  *          @arg RTC_BackUp0Reg:  choose bkp0r  reg
  *          @arg RTC_BackUp1Reg:  choose bkp1r  reg
  *          @arg RTC_BackUp2Reg:  choose bkp2r  reg
  *          @arg RTC_BackUp3Reg:  choose bkp3r  reg
  *          @arg RTC_BackUp4Reg:  choose bkp4r  reg
  *          @arg RTC_BackUp5Reg:  choose bkp5r  reg
  *          @arg RTC_BackUp6Reg:  choose bkp6r  reg
  *          @arg RTC_BackUp7Reg:  choose bkp7r  reg
  *          @arg RTC_BackUp8Reg:  choose bkp8r  reg
  *          @arg RTC_BackUp9Reg:  choose bkp9r  reg
  *          @arg RTC_BackUp10Reg: choose bkp10r reg
  *          @arg RTC_BackUp11Reg: choose bkp11r reg
  *          @arg RTC_BackUp12Reg: choose bkp12r reg
  *          @arg RTC_BackUp13Reg: choose bkp13r reg
  *          @arg RTC_BackUp14Reg: choose bkp14r reg
  *          @arg RTC_BackUp15Reg: choose bkp15r reg
  *          @arg RTC_BackUp16Reg: choose bkp16r reg
  *          @arg RTC_BackUp17Reg: choose bkp17r reg
  *          @arg RTC_BackUp18Reg: choose bkp18r reg
  *          @arg RTC_BackUp19Reg: choose bkp19r reg
  * @param  RTC_BackUpRegData: Specifies the rtc backup register data.
  *         This parameter can be only range of the 0~0xFFFFFFFF:
  * @retval None
  */
void RTC_BackUpRegConfig(uint32_t RTC_BackUpReg, uint32_t RTC_BackUpRegData)
{
    /* Check the parameters */
    assert_param(IS_RTC_BACKUP_REG(RTC_BackUpReg));
    assert_param(IS_RTC_BACKUP_DATA(RTC_BackUpRegData));

    if (RTC_BackUpReg == RTC_BackUp0Reg)
    {
        /* Clear BackUp0 register */
        RTC->BKP0R &= (uint32_t)~(RTC_BKP0R);

        /* Configure the RTC_BKP0R register */
        RTC->BKP0R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp1Reg)
    {
        /* Clear BackUp1 register */
        RTC->BKP1R &= (uint32_t)~(RTC_BKP1R);

        /* Configure the RTC_BKP1R register */
        RTC->BKP1R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp2Reg)
    {
        /* Clear BackUp2 register */
        RTC->BKP2R &= (uint32_t)~(RTC_BKP2R);

        /* Configure the RTC_BKP2R register */
        RTC->BKP2R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp3Reg)
    {
        /* Clear BackUp3 register */
        RTC->BKP3R &= (uint32_t)~(RTC_BKP3R);

        /* Configure the RTC_BKP3R register */
        RTC->BKP3R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp4Reg)
    {
        /* Clear BackUp4 register */
        RTC->BKP4R &= (uint32_t)~(RTC_BKP4R);

        /* Configure the RTC_BKP4R register */
        RTC->BKP4R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp5Reg)
    {
        /* Clear BackUp5 register */
        RTC->BKP5R &= (uint32_t)~(RTC_BKP5R);

        /* Configure the RTC_BKP5R register */
        RTC->BKP5R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp6Reg)
    {
        /* Clear BackUp6 register */
        RTC->BKP6R &= (uint32_t)~(RTC_BKP6R);

        /* Configure the RTC_BKP6R register */
        RTC->BKP6R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp7Reg)
    {
        /* Clear BackUp7 register */
        RTC->BKP7R &= (uint32_t)~(RTC_BKP7R);

        /* Configure the RTC_BKP7R register */
        RTC->BKP7R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp8Reg)
    {
        /* Clear BackUp8 register */
        RTC->BKP8R &= (uint32_t)~(RTC_BKP8R);

        /* Configure the RTC_BKP8R register */
        RTC->BKP8R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp9Reg)
    {
        /* Clear BackUp9 register */
        RTC->BKP9R &= (uint32_t)~(RTC_BKP9R);

        /* Configure the RTC_BKP9R register */
        RTC->BKP9R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp10Reg)
    {
        /* Clear BackUp10 register */
        RTC->BKP10R &= (uint32_t)~(RTC_BKP10R);

        /* Configure the RTC_BKP10R register */
        RTC->BKP10R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp11Reg)
    {
        /* Clear BackUp11 register */
        RTC->BKP11R &= (uint32_t)~(RTC_BKP11R);

        /* Configure the RTC_BKP11R register */
        RTC->BKP11R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp12Reg)
    {
        /* Clear BackUp12 register */
        RTC->BKP12R &= (uint32_t)~(RTC_BKP12R);

        /* Configure the RTC_BKP12R register */
        RTC->BKP12R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp13Reg)
    {
        /* Clear BackUp13 register */
        RTC->BKP13R &= (uint32_t)~(RTC_BKP13R);

        /* Configure the RTC_BKP13R register */
        RTC->BKP13R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp14Reg)
    {
        /* Clear BackUp14 register */
        RTC->BKP14R &= (uint32_t)~(RTC_BKP14R);

        /* Configure the RTC_BKP14R register */
        RTC->BKP14R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp15Reg)
    {
        /* Clear BackUp15 register */
        RTC->BKP15R &= (uint32_t)~(RTC_BKP15R);

        /* Configure the RTC_BKP15R register */
        RTC->BKP15R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp16Reg)
    {
        /* Clear BackUp16 register */
        RTC->BKP16R &= (uint32_t)~(RTC_BKP16R);

        /* Configure the RTC_BKP16R register */
        RTC->BKP16R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp17Reg)
    {
        /* Clear BackUp17 register */
        RTC->BKP17R &= (uint32_t)~(RTC_BKP17R);

        /* Configure the RTC_BKP17R register */
        RTC->BKP17R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp18Reg)
    {
        /* Clear BackUp18 register */
        RTC->BKP18R &= (uint32_t)~(RTC_BKP18R);

        /* Configure the RTC_BKP18R register */
        RTC->BKP18R |= (uint32_t)RTC_BackUpRegData;
    }

    if (RTC_BackUpReg == RTC_BackUp19Reg)
    {
        /* Clear BackUp19 register */
        RTC->BKP19R &= (uint32_t)~(RTC_BKP19R);

        /* Configure the RTC_BKP19R register */
        RTC->BKP19R |= (uint32_t)RTC_BackUpRegData;
    }
}

/**
  * @brief  Get the RTC BackUp Register value.
  * @param  RTC_BackUpReg:choose rtc backup reg
  *         This parameter can be one of the following values:
  *          @arg RTC_BackUp0Reg:  choose bkp0r  reg
  *          @arg RTC_BackUp1Reg:  choose bkp1r  reg
  *          @arg RTC_BackUp2Reg:  choose bkp2r  reg
  *          @arg RTC_BackUp3Reg:  choose bkp3r  reg
  *          @arg RTC_BackUp4Reg:  choose bkp4r  reg
  *          @arg RTC_BackUp5Reg:  choose bkp5r  reg
  *          @arg RTC_BackUp6Reg:  choose bkp6r  reg
  *          @arg RTC_BackUp7Reg:  choose bkp7r  reg
  *          @arg RTC_BackUp8Reg:  choose bkp8r  reg
  *          @arg RTC_BackUp9Reg:  choose bkp9r  reg
  *          @arg RTC_BackUp10Reg: choose bkp10r reg
  *          @arg RTC_BackUp11Reg: choose bkp11r reg
  *          @arg RTC_BackUp12Reg: choose bkp12r reg
  *          @arg RTC_BackUp13Reg: choose bkp13r reg
  *          @arg RTC_BackUp14Reg: choose bkp14r reg
  *          @arg RTC_BackUp15Reg: choose bkp15r reg
  *          @arg RTC_BackUp16Reg: choose bkp16r reg
  *          @arg RTC_BackUp17Reg: choose bkp17r reg
  *          @arg RTC_BackUp18Reg: choose bkp18r reg
  *          @arg RTC_BackUp19Reg: choose bkp19r reg
  *  * @retval RTC current BackUp Register value.
  */
uint32_t RTC_GetBackUpReg(uint32_t RTC_BackUpReg)
{
    /* Get  BackUp Register values from the correspondent registers */
    /* Check the parameters */
    assert_param(IS_RTC_BACKUP_REG(RTC_BackUpReg));

    if (RTC_BackUpReg == RTC_BackUp0Reg)
    {
        /* Return the RTC_BKP0R register */
        return (uint32_t)(RTC->BKP0R);
    }

    if (RTC_BackUpReg == RTC_BackUp1Reg)
    {
        /* Return the RTC_BKP1R register */
        return (uint32_t)(RTC->BKP1R);
    }

    if (RTC_BackUpReg == RTC_BackUp2Reg)
    {
        /* Return the RTC_BKP2R register */
        return (uint32_t)(RTC->BKP2R);
    }

    if (RTC_BackUpReg == RTC_BackUp3Reg)
    {
        /* Return the RTC_BKP3R register */
        return (uint32_t)(RTC->BKP3R);
    }

    if (RTC_BackUpReg == RTC_BackUp4Reg)
    {
        /* Return the RTC_BKP4R register */
        return (uint32_t)(RTC->BKP4R);
    }

    if (RTC_BackUpReg == RTC_BackUp5Reg)
    {
        /* Return the RTC_BKP5R register */
        return (uint32_t)(RTC->BKP5R);
    }

    if (RTC_BackUpReg == RTC_BackUp6Reg)
    {
        /* Return the RTC_BKP6R register */
        return (uint32_t)(RTC->BKP6R);
    }

    if (RTC_BackUpReg == RTC_BackUp7Reg)
    {
        /* Return the RTC_BKP7R register */
        return (uint32_t)(RTC->BKP7R);
    }

    if (RTC_BackUpReg == RTC_BackUp8Reg)
    {
        /* Return the RTC_BKP8R register */
        return (uint32_t)(RTC->BKP8R);
    }

    if (RTC_BackUpReg == RTC_BackUp9Reg)
    {
        /* Return the RTC_BKP9R register */
        return (uint32_t)(RTC->BKP9R);
    }

    if (RTC_BackUpReg == RTC_BackUp10Reg)
    {
        /* Return the RTC_BKP10R register */
        return (uint32_t)(RTC->BKP10R);
    }

    if (RTC_BackUpReg == RTC_BackUp11Reg)
    {
        /* Return the RTC_BKP11R register */
        return (uint32_t)(RTC->BKP11R);
    }

    if (RTC_BackUpReg == RTC_BackUp12Reg)
    {
        /* Return the RTC_BKP12R register */
        return (uint32_t)(RTC->BKP12R);
    }

    if (RTC_BackUpReg == RTC_BackUp13Reg)
    {
        /* Return the RTC_BKP13R register */
        return (uint32_t)(RTC->BKP13R);
    }

    if (RTC_BackUpReg == RTC_BackUp14Reg)
    {
        /* Return the RTC_BKP14R register */
        return (uint32_t)(RTC->BKP14R);
    }

    if (RTC_BackUpReg == RTC_BackUp15Reg)
    {
        /* Return the RTC_BKP15R register */
        return (uint32_t)(RTC->BKP15R);
    }

    if (RTC_BackUpReg == RTC_BackUp16Reg)
    {
        /* Return the RTC_BKP16R register */
        return (uint32_t)(RTC->BKP16R);
    }

    if (RTC_BackUpReg == RTC_BackUp17Reg)
    {
        /* Return the RTC_BKP17R register */
        return (uint32_t)(RTC->BKP17R);
    }

    if (RTC_BackUpReg == RTC_BackUp18Reg)
    {
        /* Return the RTC_BKP18R register */
        return (uint32_t)(RTC->BKP18R);
    }

    if (RTC_BackUpReg == RTC_BackUp19Reg)
    {
        /* Return the RTC_BKP19R register */
        return (uint32_t)(RTC->BKP19R);
    }
    return 0;
}






/**
  * @}
  */


/**
  * @brief  Converts a 2 digit decimal to BCD format.
  * @param  Value: Byte to be converted.
  * @retval Converted byte
  */
static uint8_t RTC_ByteToBcd2(uint8_t Value)
{
    uint8_t bcdhigh = 0;

    while (Value >= 10)
    {
        bcdhigh++;
        Value -= 10;
    }

    return ((uint8_t)(bcdhigh << 4) | Value);
}

/**
  * @brief  Convert from 2 digit BCD to Binary.
  * @param  Value: BCD value to be converted.
  * @retval Converted word
  */
static uint8_t RTC_Bcd2ToByte(uint8_t Value)
{
    uint8_t tmp = 0;
    tmp = ((uint8_t)(Value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
    return (tmp + (Value & (uint8_t)0x0F));
}

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
