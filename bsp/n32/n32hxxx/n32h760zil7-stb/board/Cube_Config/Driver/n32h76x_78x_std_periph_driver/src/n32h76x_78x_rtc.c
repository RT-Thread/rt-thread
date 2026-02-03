/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_rtc.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "n32h76x_78x_rtc.h"

static uint8_t RTC_ByteToBcd2(uint8_t Value);
static uint8_t RTC_Bcd2ToByte(uint8_t Value);

/**
*\*\name    RTC_DeInit.
*\*\fun     Deinitializes the RTC registers to their default reset values.
*\*\param   none
*\*\return  ErrorStatus
*\*\            - SUCCESS: RTC registers are deinitialized
*\*\            - ERROR: RTC registers are not deinitialized
*\*\
**/
ErrorStatus RTC_DeInit(void)
{
    __IO uint32_t wutcounter = 0x00;
    uint32_t wutwfstatus;
    ErrorStatus status;

    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Set Initialization mode */
    if (RTC_EnterInitMode() == ERROR)
    {
        status = ERROR;
    }
    else
    {
        /* Reset TSH, DAT and CTRL registers */
        RTC->TSH  = (uint32_t)0x00000000;
        RTC->DATE = (uint32_t)0x00002101;

        /* Reset All CTRL bits except CTRL[2:0] */
        RTC->CTRL &= (uint32_t)0x00000007;

        /* Wait till RTC WTWF flag is set and if Time out is reached exit */
        do
        {
            wutwfstatus = RTC->INITSTS & RTC_INITSTS_WTWF;
            wutcounter++;
        }
        while ((wutcounter != INITMODE_TIMEOUT) && (wutwfstatus == 0x00));

        if ((RTC->INITSTS & RTC_INITSTS_WTWF) == RESET)
        {
            status = ERROR;
        }
        else
        {
            /* Reset all RTC CTRL register bits */
            RTC->CTRL   &= (uint32_t)0x00000000;
            RTC->WKUPT   = (uint32_t)0x0000FFFF;
            RTC->PRE     = (uint32_t)0x007F00FF;
            RTC->ALARMA  = (uint32_t)0x00000000;
            RTC->ALARMB  = (uint32_t)0x00000000;
            RTC->CALIB   = (uint32_t)0x00000000;
            RTC->ALRMASS = (uint32_t)0x00000000;
            RTC->ALRMBSS = (uint32_t)0x00000000;

            /* Reset INTSTS register and exit initialization mode */
            RTC->INITSTS = (uint32_t)0x00000000;

            RTC->OPT     = (uint32_t)0x00000000;


            /* Wait till the RTC RSYF flag is set */
            if (RTC_WaitForSynchro() == ERROR)
            {
                status = ERROR;
            }
            else
            {
                status = SUCCESS;
            }
        }
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;

    return status;
}

/**
*\*\name    RTC_Init.
*\*\fun     RTC_InitStruct pointer to a RTC_InitType structure that contains
*\*\        the configuration information for the RTC peripheral
*\*\param   RTC_InitStruct
*\*\            - RTC_HourFormat
*\*\                - RTC_24HOUR_FORMAT
*\*\                - RTC_12HOUR_FORMAT
*\*\            - RTC_AsynchPrediv  the value is selected in the 1-0x7F range 
*\*\            - RTC_SynchPrediv   the value must lower than 0x7FFF
*\*\return  ErrorStatus
*\*\            - SUCCESS: RTC registers are deinitialized
*\*\            - ERROR: RTC registers are not deinitialized
*\*\
**/
ErrorStatus RTC_Init(RTC_InitType* RTC_InitStruct)
{
    ErrorStatus status;
    uint16_t i;

    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Set Initialization mode */
    if (RTC_EnterInitMode() == ERROR)
    {
        status = ERROR;
    }
    else
    {
        /* Clear RTC CTRL HFMT Bit */
        RTC->CTRL &= ((uint32_t) ~(RTC_CTRL_HFMT));
        /* Set RTC_CTRL register */
        RTC->CTRL |= ((uint32_t)(RTC_InitStruct->RTC_HourFormat));

        /* Configure the RTC PRE */
        RTC->PRE = (uint32_t)(RTC_InitStruct->RTC_SynchPrediv);
        RTC->PRE |= (uint32_t)(RTC_InitStruct->RTC_AsynchPrediv << 16);

        /* Exit Initialization mode */
        RTC_ExitInitMode();

        status = SUCCESS;
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;

    /* Delay for the RTC prescale effect */
    for(i = 0; i < 0x2FF; i++)
    {
        /* NOP */
    };

    return status;
}

/**
*\*\name    RTC_StructInit.
*\*\fun     Fills each RTC_InitStruct member with its default value.
*\*\param   RTC_InitStruct :    RTC_InitStruct pointer to a RTC_InitType structure which will beinitialized.
*\*\            - RTC_HourFormat
*\*\                - RTC_24HOUR_FORMAT
*\*\                - RTC_12HOUR_FORMAT
*\*\            - RTC_AsynchPrediv  the value is selected in the 1-0x7F range 
*\*\            - RTC_SynchPrediv   the value must lower than 0x7FFF
*\*\return  none
**/
void RTC_StructInit(RTC_InitType* RTC_InitStruct)
{
    /* Initialize the RTC_HourFormat member */
    RTC_InitStruct->RTC_HourFormat = RTC_24HOUR_FORMAT;

    /* Initialize the RTC_AsynchPrediv member */
    RTC_InitStruct->RTC_AsynchPrediv = (uint32_t)0x7F;

    /* Initialize the RTC_SynchPrediv member */
    RTC_InitStruct->RTC_SynchPrediv = (uint32_t)0xFF;
}

/**
*\*\name    RTC_EnableWriteProtection.
*\*\fun     Enable or disable the RTC registers write protection.
 *\*\param  Cmd :
 *\*\          - ENABLE
 *\*\          - DISABLE
*\*\return  none
**/
void RTC_EnableWriteProtection(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the write protection for RTC registers */
        RTC->WRP = 0xFF;
    }
    else
    {
        /* Disable the write protection for RTC registers */
        RTC->WRP = 0xCA;
        RTC->WRP = 0x53;
    }
}

/**
*\*\name    RTC_EnterInitMode.
*\*\fun     Enters the RTC Initialization mode.
*\*\param   none
*\*\return   ErrorStatus
*\*\            - SUCCESS: RTC is in Init mode
*\*\            - ERROR: RTC is not in Init mode
**/
ErrorStatus RTC_EnterInitMode(void)
{
    __IO uint32_t initcounter = 0x00;
    ErrorStatus status;
    uint32_t initstatus;

    /* Check if the Initialization mode is set */
    if ((RTC->INITSTS & RTC_INITSTS_INITF) == (uint32_t)RESET)
    {
        /* Set the Initialization mode */
        RTC->INITSTS = (uint32_t)RTC_INITSTS_INITM;

        /* Wait till RTC is in INIT state and if Time out is reached exit */
        do
        {
            initstatus = RTC->INITSTS & RTC_INITSTS_INITF;
            initcounter++;
        }
        while ((initcounter != INITMODE_TIMEOUT) && (initstatus == 0x00));

        if ((RTC->INITSTS & RTC_INITSTS_INITF) != RESET)
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
*\*\name    RTC_ExitInitMode.
*\*\fun     When the initialization sequence is complete, the calendar restarts counting after 4 RTCCLK cycles.
*\*\param   none
*\*\return  none
**/
void RTC_ExitInitMode(void)
{
    /* Exit Initialization mode */
    RTC->INITSTS &= (uint32_t)~RTC_INITSTS_INITM;
}

/**
*\*\name    RTC_WaitForSynchro.
*\*\fun     Waits until the RTC Time and Date registers (RTC_TSH and RTC_DATE) are synchronized with RTC APB clock.
*\*\param   none
*\*\return  ErrorStatus :
*\*\            - SUCCESS:  RTC registers are synchronised
*\*\            - ERROR:    RTC registers are not synchronised
**/
ErrorStatus RTC_WaitForSynchro(void)
{
    __IO uint32_t synchrocounter = 0;
    ErrorStatus status;
    uint32_t synchrostatus;

    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Clear RSYF flag */
    RTC->INITSTS &= (uint32_t)RTC_RSF_MASK;

    /* Wait the registers to be synchronised and 5500ms timeout */
    do
    {
        synchrostatus = RTC->INITSTS & RTC_INITSTS_RSYF;
        synchrocounter++;
    }
    while ((synchrocounter < SYNCHRO_TIMEOUT) && (synchrostatus == 0x00U));

    if ((RTC->INITSTS & RTC_INITSTS_RSYF) != RESET)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;

    return (status);
}


/**
*\*\name    RTC_EnableRefClock.
*\*\fun     Enables or disables the RTC reference clock detection.
 *\*\param  Cmd :
 *\*\          - ENABLE
 *\*\          - DISABLE
*\*\return  none
**/
ErrorStatus RTC_EnableRefClock(FunctionalState Cmd)
{
    ErrorStatus status;

    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Set Initialization mode */
    if (RTC_EnterInitMode() == ERROR)
    {
        status = ERROR;
    }
    else
    {
        if (Cmd != DISABLE)
        {
            /* Enable the RTC reference clock detection */
            RTC->CTRL |= RTC_CTRL_REFCLKEN;
        }
        else
        {
            /* Disable the RTC reference clock detection */
            RTC->CTRL &= ~RTC_CTRL_REFCLKEN;
        }

        /* Exit Initialization mode */
        RTC_ExitInitMode();

        status = SUCCESS;
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;

    return status;
}


/**
*\*\name    RTC_EnableBypassShadow.
*\*\fun     When the Bypass Shadow is enabled the calendar value are taken directly from the Calendar counter
 *\*\param  Cmd :
 *\*\          - ENABLE
 *\*\          - DISABLE
*\*\return  none
**/
void RTC_EnableBypassShadow(FunctionalState Cmd)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    if (Cmd != DISABLE)
    {
        /* Set the BYPS bit */
        RTC->CTRL |= (uint8_t)RTC_CTRL_BYPS;
    }
    else
    {
        /* Reset the BYPS bit */
        RTC->CTRL &= (uint8_t)~RTC_CTRL_BYPS;
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_ConfigTime.
*\*\fun     Calendar value read from Shadow register.
 *\*\param  RTC_Format :
 *\*\          - RTC_FORMAT_BIN
 *\*\          - RTC_FORMAT_BCD
*\*\param   RTC_TimeStruct : RTC_TimeStruct pointer to a RTC_TimeType structure that contains
*\*\        the time configuration information for the RTC.When the user does not need to configure this
*\*\        parameter, note that NULL can be passed in.
*\*\            - Hours
*\*\                - if RTC_AM_H12 is select the value in the 0-23 range
*\*\                - if RTC_PM_H12 is select the value in the 1-12 range
*\*\            - Minutes  the value set in the 0-59 range
*\*\            - Seconds  the value set in the 0-59 range
*\*\            - H12
*\*\                - RTC_AM_H12
*\*\                - RTC_PM_H12
*\*\return  none
**/
ErrorStatus RTC_ConfigTime(uint32_t RTC_Format, RTC_TimeType* RTC_TimeStruct)
{
    uint32_t tmpregister;
    ErrorStatus status;

    /* Check the input parameters format */
    if (RTC_Format != RTC_FORMAT_BIN)
    {
        tmpregister = (((uint32_t)(RTC_TimeStruct->Hours) << 16) | ((uint32_t)(RTC_TimeStruct->Minutes) << 8)
                       | ((uint32_t)RTC_TimeStruct->Seconds) | ((uint32_t)(RTC_TimeStruct->H12) << 16));
    }
    else
    {
        tmpregister =
            (uint32_t)(((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->Hours) << 16)
                       | ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->Minutes) << 8)
                       | ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->Seconds)) | (((uint32_t)RTC_TimeStruct->H12) << 16));
    }

    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Set Initialization mode */
    if (RTC_EnterInitMode() == ERROR)
    {
        status = ERROR;
    }
    else
    {
        /* Set the RTC_TSH register */
        RTC->TSH = (uint32_t)(tmpregister & RTC_TR_RESERVED_MASK);

        /* Exit Initialization mode */
        RTC_ExitInitMode();

        /* If  RTC_CTRL_BYPS bit = 0, wait for synchro else this check is not needed */
        if ((RTC->CTRL & RTC_CTRL_BYPS) == RESET)
        {
            if (RTC_WaitForSynchro() == ERROR)
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

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;

    /* Waits until the RTC Time and Date registers
    (RTC_TSH and RTC_DATE) are  synchronized with RTC APB clock. */
    if(status != ERROR)
    {
        status = RTC_WaitForSynchro();
    }

    return status;
}

/**
*\*\name    RTC_TimeStructInit.
*\*\fun     Fills each RTC_TimeStruct member with its default value
*\*\        (Time = 00h:00 min:00sec).
*\*\param   RTC_TimeStruct : RTC_TimeStruct pointer to a RTC_TimeType structure that contains
*\*\                         the time configuration information for the RTC.
*\*\            - Hours
*\*\                - if RTC_AM_H12 is select the value in the 0-23 range
*\*\                - if RTC_PM_H12 is select the value in the 1-12 range
*\*\            - Minutes  the value set in the 0-59 range
*\*\            - Seconds  the value set in the 0-59 range
*\*\            - H12
*\*\                - RTC_AM_H12
*\*\                - RTC_PM_H12
*\*\return  none
**/
void RTC_TimeStructInit(RTC_TimeType* RTC_TimeStruct)
{
    /* Time = 00h:00min:00sec */
    RTC_TimeStruct->H12     = RTC_AM_H12;
    RTC_TimeStruct->Hours   = 0;
    RTC_TimeStruct->Minutes = 0;
    RTC_TimeStruct->Seconds = 0;
}

/**
*\*\name    RTC_GetTime.
*\*\fun     Get the RTC current Time.
*\*\param   RTC_Format : specifies the format of the returned parameters.
*\*\            - RTC_FORMAT_BIN
*\*\            - RTC_FORMAT_BCD
*\*\param   RTC_TimeStruct : RTC_TimeStruct pointer to a RTC_TimeType structure.
*\*\return  none
**/
void RTC_GetTime(uint32_t RTC_Format, RTC_TimeType* RTC_TimeStruct)
{
    uint32_t tmpregister;

    /* Get the RTC_TSH register */
    tmpregister = (uint32_t)(RTC->TSH & RTC_TR_RESERVED_MASK);

    /* Fill the structure fields with the read parameters */
    RTC_TimeStruct->Hours   = (uint8_t)((tmpregister & (RTC_TSH_HOT | RTC_TSH_HOU)) >> 16);
    RTC_TimeStruct->Minutes = (uint8_t)((tmpregister & (RTC_TSH_MIT | RTC_TSH_MIU)) >> 8);
    RTC_TimeStruct->Seconds = (uint8_t)(tmpregister & (RTC_TSH_SCT | RTC_TSH_SCU));
    RTC_TimeStruct->H12     = (uint8_t)((tmpregister & (RTC_TSH_APM)) >> 16);

    /* Check the input parameters format */
    if (RTC_Format == RTC_FORMAT_BIN)
    {
        /* Convert the structure parameters to Binary format */
        RTC_TimeStruct->Hours   = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->Hours);
        RTC_TimeStruct->Minutes = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->Minutes);
        RTC_TimeStruct->Seconds = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->Seconds);
    }
}

/**
*\*\name    RTC_GetSubSecond.
*\*\fun     Gets the RTC current Calendar Subseconds value.
*\*\return  RTC current Calendar Subseconds value.
**/
uint32_t RTC_GetSubSecond(void)
{
    uint32_t tmpregister;

    /* Get subseconds values from the correspondent registers*/
    tmpregister = (uint32_t)(RTC->SUBS);

    return (tmpregister);
}

/**
*\*\name    RTC_SetDate.
*\*\fun     Set RTC Calendar current date.
*\*\param   RTC_Format : specifies the format of the returned parameters.
*\*\          - RTC_FORMAT_BIN
*\*\          - RTC_FORMAT_BCD
*\*\param   RTC_DateStruct : RTC_DateStruct pointer to a RTC_DateType structure that contains
*\*\        the date configuration information for the RTC,note that NULL can be passed in.
*\*\            - WeekDay
*\*\                - RTC_WEEKDAY_MONDAY
*\*\                - RTC_WEEKDAY_TUESDAY
*\*\                - RTC_WEEKDAY_WEDNESDAY
*\*\                - RTC_WEEKDAY_THURSDAY
*\*\                - RTC_WEEKDAY_FRIDAY
*\*\                - RTC_WEEKDAY_SATURDAY
*\*\                - RTC_WEEKDAY_SUNDAY
*\*\            - Month
*\*\                - RTC_MONTH_JANUARY
*\*\                - RTC_MONTH_FEBRURY
*\*\                - RTC_MONTH_MARCH
*\*\                - RTC_MONTH_APRIL
*\*\                - RTC_MONTH_MAY
*\*\                - RTC_MONTH_JUNE
*\*\                - RTC_MONTH_JULY
*\*\                - RTC_MONTH_AUGUST
*\*\                - RTC_MONTH_SEPTEMBER
*\*\                - RTC_MONTH_OCTOBER
*\*\                - RTC_MONTH_NOVEMBER
*\*\                - RTC_MONTH_DECEMBER
*\*\            - Date    the value in the 1-31 range
*\*\            - Year    the value in the 0-99 range
*\*\return  ErrorStatus
*\*\            - SUCCESS:  RTC Date register is configured
*\*\            - ERROR:    RTCDate register is not configured
**/
ErrorStatus RTC_SetDate(uint32_t RTC_Format, RTC_DateType* RTC_DateStruct)
{
    uint32_t tmpregister;
    ErrorStatus status;

    if ((RTC_Format == RTC_FORMAT_BIN) && ((RTC_DateStruct->Month & (uint8_t)0x10) == (uint8_t)0x10))
    {
        RTC_DateStruct->Month = (RTC_DateStruct->Month & (uint8_t)0xEF) + (uint8_t)0x0A;
    }

    /* Check the input parameters format */
    if (RTC_Format != RTC_FORMAT_BIN)
    {
        tmpregister = ((((uint32_t)RTC_DateStruct->Year) << 16) | (((uint32_t)RTC_DateStruct->Month) << 8)
                       | ((uint32_t)RTC_DateStruct->Date) | (((uint32_t)RTC_DateStruct->WeekDay) << 13));
    }
    else
    {
        tmpregister = (((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->Year) << 16)
                       | ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->Month) << 8)
                       | ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->Date)) | ((uint32_t)RTC_DateStruct->WeekDay << 13));
    }

    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Set Initialization mode */
    if (RTC_EnterInitMode() == ERROR)
    {
        status = ERROR;
    }
    else
    {
        /* Set the RTC_DATE register */
        RTC->DATE = (uint32_t)(tmpregister & RTC_DATE_RESERVED_MASK);

        /* Exit Initialization mode */
        RTC_ExitInitMode();

        /* If  RTC_CTRL_BYPS bit = 0, wait for synchro else this check is not needed */
        if ((RTC->CTRL & RTC_CTRL_BYPS) == RESET)
        {
            if (RTC_WaitForSynchro() == ERROR)
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

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;

    /* Waits until the RTC Time and Date registers
    (RTC_TSH and RTC_DATE) are  synchronized with RTC APB clock. */
    if(ERROR != status)
    {
        status = RTC_WaitForSynchro();
    }

    return status;
}


/**
*\*\name    RTC_DateStructInit.
*\*\fun     Fills each RTC_DateStruct member with its default value (Monday, January 01 xx00).
*\*\param   RTC_DateStruct : RTC_DateStruct pointer to a RTC_DateType structure that contains
*\*\                       the date configuration information for the RTC.
*\*\            - WeekDay
*\*\                - RTC_WEEKDAY_MONDAY
*\*\                - RTC_WEEKDAY_TUESDAY
*\*\                - RTC_WEEKDAY_WEDNESDAY
*\*\                - RTC_WEEKDAY_THURSDAY
*\*\                - RTC_WEEKDAY_FRIDAY
*\*\                - RTC_WEEKDAY_SATURDAY
*\*\                - RTC_WEEKDAY_SUNDAY
*\*\            - Month
*\*\                - RTC_MONTH_JANUARY
*\*\                - RTC_MONTH_FEBRURY
*\*\                - RTC_MONTH_MARCH
*\*\                - RTC_MONTH_APRIL
*\*\                - RTC_MONTH_MAY
*\*\                - RTC_MONTH_JUNE
*\*\                - RTC_MONTH_JULY
*\*\                - RTC_MONTH_AUGUST
*\*\                - RTC_MONTH_SEPTEMBER
*\*\                - RTC_MONTH_OCTOBER
*\*\                - RTC_MONTH_NOVEMBER
*\*\                - RTC_MONTH_DECEMBER
*\*\            - Date    the value in the 1-31 range
*\*\            - Year    the value in the 0-99 range
*\*\return  none
**/
void RTC_DateStructInit(RTC_DateType* RTC_DateStruct)
{
    /* Monday, January 01 xx00 */
    RTC_DateStruct->WeekDay = RTC_WEEKDAY_MONDAY;
    RTC_DateStruct->Date    = 1;
    RTC_DateStruct->Month   = RTC_MONTH_JANUARY;
    RTC_DateStruct->Year    = 0;
}
/**
*\*\name    RTC_GetDate.
*\*\fun     Get the RTC current date.
*\*\param   RTC_Format : specifies the format of the returned parameters.
*\*\            - RTC_FORMAT_BIN
*\*\            - RTC_FORMAT_BCD
*\*\param   RTC_DateType : RTC_DateStruct pointer to a RTC_DateType structure that will
*\*\                       contain the returned current date configuration.
*\*\return  none
**/
void RTC_GetDate(uint32_t RTC_Format, RTC_DateType* RTC_DateStruct)
{
    uint32_t tmpregister;

    /* Get the RTC_TSH register */
    tmpregister = (uint32_t)(RTC->DATE & RTC_DATE_RESERVED_MASK);

    /* Fill the structure fields with the read parameters */
    RTC_DateStruct->Year    = (uint8_t)((tmpregister & (RTC_DATE_YRT | RTC_DATE_YRU)) >> 16);
    RTC_DateStruct->Month   = (uint8_t)((tmpregister & (RTC_DATE_MOT | RTC_DATE_MOU)) >> 8);
    RTC_DateStruct->Date    = (uint8_t)(tmpregister & (RTC_DATE_DAT | RTC_DATE_DAU));
    RTC_DateStruct->WeekDay = (uint8_t)((tmpregister & (RTC_DATE_WDU)) >> 13);

    /* Check the input parameters format */
    if (RTC_Format == RTC_FORMAT_BIN)
    {
        /* Convert the structure parameters to Binary format */
        RTC_DateStruct->Year  = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->Year);
        RTC_DateStruct->Month = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->Month);
        RTC_DateStruct->Date  = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->Date);
    }
}

/**
*\*\name    RTC_SetAlarm.
*\*\fun     Set the specified RTC Alarm.
*\*\param   RTC_Format : specifies the format of the returned parameters.
*\*\            - RTC_FORMAT_BIN
*\*\            - RTC_FORMAT_BCD
*\*\param   RTC_Alarm : RTC_Alarm specifies the alarm to be configured.
*\*\            - RTC_A_ALARM
*\*\            - RTC_B_ALARM
*\*\param   RTC_AlarmStruct : RTC_AlarmStruct pointer to a RTC_AlarmType structure that
*\*\                          contains the alarm configuration parameters.
*\*\            - AlarmTime   RTC_TimeStruct pointer to a RTC_TimeType structure that contains
*\*\                         the time configuration information for the RTC.
*\*\            - Hours
*\*\                - if RTC_AM_H12 is select the value in the 0-23 range
*\*\                - if RTC_PM_H12 is select the value in the 1-12 range
*\*\            - Minutes  the value set in the 0-59 range
*\*\            - Seconds  the value set in the 0-59 range
*\*\            - H12
*\*\                - RTC_AM_H12
*\*\                - RTC_PM_H12
*\*\            - AlarmMask
*\*\                - RTC_ALARMMASK_NONE
*\*\                - RTC_ALARMMASK_WEEKDAY
*\*\                - RTC_ALARMMASK_HOURS
*\*\                - RTC_ALARMMASK_MINUTES
*\*\                - RTC_ALARMMASK_SECONDS
*\*\                - RTC_ALARMMASK_ALL
*\*\            - DateWeekMode
*\*\                - RTC_ALARM_SEL_WEEKDAY_DATE
*\*\                - RTC_ALARM_SEL_WEEKDAY_WEEKDAY
*\*\            - DateWeekValue
*\*\                - RTC_WEEKDAY_MONDAY
*\*\                - RTC_WEEKDAY_TUESDAY
*\*\                - RTC_WEEKDAY_WEDNESDAY
*\*\                - RTC_WEEKDAY_THURSDAY
*\*\                - RTC_WEEKDAY_FRIDAY
*\*\                - RTC_WEEKDAY_SATURDAY
*\*\                - RTC_WEEKDAY_SUNDAY
*\*\return  none
**/
void RTC_SetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmType* RTC_AlarmStruct)
{
    uint32_t tmpregister;

    /* Check the input parameters format */
    if (RTC_Format != RTC_FORMAT_BIN)
    {
        tmpregister =
            (((uint32_t)(RTC_AlarmStruct->AlarmTime.Hours) << 16)
             | ((uint32_t)(RTC_AlarmStruct->AlarmTime.Minutes) << 8) | ((uint32_t)RTC_AlarmStruct->AlarmTime.Seconds)
             | ((uint32_t)(RTC_AlarmStruct->AlarmTime.H12) << 16) | ((uint32_t)(RTC_AlarmStruct->DateWeekValue) << 24)
             | ((uint32_t)RTC_AlarmStruct->DateWeekMode) | ((uint32_t)RTC_AlarmStruct->AlarmMask));
    }
    else
    {
        tmpregister = (((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->AlarmTime.Hours) << 16)
                       | ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->AlarmTime.Minutes) << 8)
                       | ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->AlarmTime.Seconds))
                       | ((uint32_t)(RTC_AlarmStruct->AlarmTime.H12) << 16)
                       | ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->DateWeekValue) << 24)
                       | ((uint32_t)RTC_AlarmStruct->DateWeekMode) | ((uint32_t)RTC_AlarmStruct->AlarmMask));
    }

    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Configure the Alarm register */
    if (RTC_Alarm == RTC_A_ALARM)
    {
        RTC->ALARMA = (uint32_t)tmpregister;
    }
    else
    {
        RTC->ALARMB = (uint32_t)tmpregister;
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_AlarmStructInit.
*\*\fun     Fills each RTC_AlarmStruct member with its default value
*\*\        (Time = 00h:00mn:00sec / Date = 1st day of the month/Mask =
*\*\        all fields are masked).
*\*\param   RTC_AlarmStruct : RTC_AlarmStruct pointer to a RTC_AlarmType structure that
*\*\                          contains the alarm configuration parameters.
*\*\            - AlarmTime   RTC_TimeStruct pointer to a RTC_TimeType structure that contains
*\*\                         the time configuration information for the RTC.
*\*\            - Hours
*\*\                - if RTC_AM_H12 is select the value in the 0-23 range
*\*\                - if RTC_PM_H12 is select the value in the 1-12 range
*\*\            - Minutes  the value set in the 0-59 range
*\*\            - Seconds  the value set in the 0-59 range
*\*\            - H12
*\*\                - RTC_AM_H12
*\*\                - RTC_PM_H12
*\*\            - AlarmMask
*\*\                - RTC_ALARMMASK_NONE
*\*\                - RTC_ALARMMASK_WEEKDAY
*\*\                - RTC_ALARMMASK_HOURS
*\*\                - RTC_ALARMMASK_MINUTES
*\*\                - RTC_ALARMMASK_SECONDS
*\*\                - RTC_ALARMMASK_ALL
*\*\            - DateWeekMode
*\*\                - RTC_ALARM_SEL_WEEKDAY_DATE
*\*\                - RTC_ALARM_SEL_WEEKDAY_WEEKDAY
*\*\            - DateWeekValue
*\*\                - RTC_WEEKDAY_MONDAY
*\*\                - RTC_WEEKDAY_TUESDAY
*\*\                - RTC_WEEKDAY_WEDNESDAY
*\*\                - RTC_WEEKDAY_THURSDAY
*\*\                - RTC_WEEKDAY_FRIDAY
*\*\                - RTC_WEEKDAY_SATURDAY
*\*\                - RTC_WEEKDAY_SUNDAY
*\*\return  none
**/
void RTC_AlarmStructInit(RTC_AlarmType* RTC_AlarmStruct)
{
    /* Alarm Time Settings : Time = 00h:00mn:00sec */
    RTC_AlarmStruct->AlarmTime.H12     = RTC_AM_H12;
    RTC_AlarmStruct->AlarmTime.Hours   = 0;
    RTC_AlarmStruct->AlarmTime.Minutes = 0;
    RTC_AlarmStruct->AlarmTime.Seconds = 0;

    /* Alarm Date Settings : Date = 1st day of the month */
    RTC_AlarmStruct->DateWeekMode  = RTC_ALARM_SEL_WEEKDAY_DATE;
    RTC_AlarmStruct->DateWeekValue = 1;

    /* Alarm Masks Settings : Mask =  all fields are not masked */
    RTC_AlarmStruct->AlarmMask = RTC_ALARMMASK_NONE;
}

/**
*\*\name    RTC_GetAlarm.
*\*\fun     Get the RTC Alarm value and masks.
*\*\param   RTC_Format : specifies the format of the output parameters.
*\*\            - RTC_FORMAT_BIN
*\*\            - RTC_FORMAT_BCD
*\*\param   RTC_Alarm : specifies the alarm to be read.
*\*\            - RTC_A_ALARM
*\*\            - RTC_B_ALARM
*\*\param   RTC_AlarmStruct : pointer to a RTC_AlarmType structure that will
*\*\        contains the output alarm configuration values.
*\*\
*\*\return  none
**/
void RTC_GetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmType* RTC_AlarmStruct)
{
    uint32_t tmpregister;

    /* Get the RTC_ALARMx register */
    if (RTC_Alarm == RTC_A_ALARM)
    {
        tmpregister = (uint32_t)(RTC->ALARMA);
    }
    else
    {
        tmpregister = (uint32_t)(RTC->ALARMB);
    }

    /* Fill the structure with the read parameters */
    RTC_AlarmStruct->AlarmTime.Hours   = (uint8_t)((tmpregister & (RTC_ALARMA_HOT | RTC_ALARMA_HOU)) >> 16);
    RTC_AlarmStruct->AlarmTime.Minutes = (uint8_t)((tmpregister & (RTC_ALARMA_MIT | RTC_ALARMA_MIU)) >> 8);
    RTC_AlarmStruct->AlarmTime.Seconds = (uint8_t)(tmpregister & (RTC_ALARMA_SET | RTC_ALARMA_SEU));
    RTC_AlarmStruct->AlarmTime.H12     = (uint8_t)((tmpregister & RTC_ALARMA_APM) >> 16);
    RTC_AlarmStruct->DateWeekValue     = (uint8_t)((tmpregister & (RTC_ALARMA_DTT | RTC_ALARMA_DTU)) >> 24);
    RTC_AlarmStruct->DateWeekMode      = (uint32_t)(tmpregister & RTC_ALARMA_WKDSEL);
    RTC_AlarmStruct->AlarmMask         = (uint32_t)(tmpregister & RTC_ALARMMASK_ALL);

    if (RTC_Format == RTC_FORMAT_BIN)
    {
        RTC_AlarmStruct->AlarmTime.Hours   = RTC_Bcd2ToByte(RTC_AlarmStruct->AlarmTime.Hours);
        RTC_AlarmStruct->AlarmTime.Minutes = RTC_Bcd2ToByte(RTC_AlarmStruct->AlarmTime.Minutes);
        RTC_AlarmStruct->AlarmTime.Seconds = RTC_Bcd2ToByte(RTC_AlarmStruct->AlarmTime.Seconds);
        RTC_AlarmStruct->DateWeekValue     = RTC_Bcd2ToByte(RTC_AlarmStruct->DateWeekValue);
    }
}

/**
*\*\name    RTC_EnableAlarm.
*\*\fun     Enables or disables the specified RTC Alarm.
*\*\param   RTC_Alarm : specifies the alarm to be configured.
*\*\            - RTC_A_ALARM
*\*\            - RTC_B_ALARM
 *\*\param  Cmd :
 *\*\          - ENABLE
 *\*\          - DISABLE
*\*\return  ErrorStatus :
*\*\            - SUCCESS: RTC Alarm set succeed
*\*\            - ERROR:   RTC Alarm set failed
**/
ErrorStatus RTC_EnableAlarm(uint32_t RTC_Alarm, FunctionalState Cmd)
{
    __IO uint32_t alarmcounter = 0x00;
    uint32_t alarmstatus;
    ErrorStatus status;

    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Configure the Alarm state */
    if (Cmd != DISABLE)
    {
        RTC->CTRL |= (uint32_t)RTC_Alarm;

        status = SUCCESS;
    }
    else
    {
        /* Disable the Alarm in RTC_CTRL register */
        RTC->CTRL &= (uint32_t)~RTC_Alarm;

        /* Wait till RTC ALxWF flag is set and if Time out is reached exit */
        do
        {
            alarmstatus = RTC->INITSTS & (RTC_Alarm >> 8);
            alarmcounter++;
        }
        while ((alarmcounter != INITMODE_TIMEOUT) && (alarmstatus == 0x00));

        if ((RTC->INITSTS & (RTC_Alarm >> 8)) == RESET)
        {
            status = ERROR;
        }
        else
        {
            status = SUCCESS;
        }
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;

    return status;
}

/**
*\*\name    RTC_ConfigAlarmSubSecond.
*\*\fun     Configure the RTC AlarmA/B Subseconds value and mask
*\*\param   RTC_Alarm : specifies the alarm to be configured.
*\*\            - RTC_A_ALARM : select Alarm A.
*\*\            - RTC_B_ALARM : select Alarm B.
*\*\param   RTC_AlarmSubSecondValue : specifies the Subseconds value, the value in the 0-0x00007FFF range
*\*\param   RTC_AlarmSubSecondMask : specifies the Subseconds Mask.
*\*\            - RTC_SUBS_MASK_ALL     : Alarm SS fields are masked There is no comparison on sub seconds for Alarm.
*\*\            - RTC_SUBS_MASK_SS14_1  : SS[14:1] are don't care in Alarm comparison Only SS[0] is compared
*\*\            - RTC_SUBS_MASK_SS14_2  : SS[14:2] are don't care in Alarm comparison Only SS[1:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_3  : SS[14:3] are don't care in Alarm comparison Only SS[2:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_4  : SS[14:4] are don't care in Alarm comparison Only SS[3:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_5  : SS[14:5] are don't care in Alarm comparison Only SS[4:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_6  : SS[14:6] are don't care in Alarm comparison Only SS[5:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_7  : SS[14:7] are don't care in Alarm comparison Only SS[6:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_8  : SS[14:8] are don't care in Alarm comparison Only SS[7:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_9  : SS[14:9] are don't care in Alarm comparison Only SS[8:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_10 : SS[14:10] are don't care in Alarm comparison Only SS[9:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_11 : SS[14:11] are don't care in Alarm comparison Only SS[10:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_12 : SS[14:12] are don't care in Alarm comparison Only SS[11:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_13 : SS[14:13] are don't care in Alarm comparison Only SS[12:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_14 : SS[14] is don't care in Alarm comparison Only SS[13:0] are compared.
*\*\            - RTC_SUBS_MASK_NONE    : SS[14:0] are compared and must match to activate alarm.
*\*\return  None
**/
void RTC_ConfigAlarmSubSecond(uint32_t RTC_Alarm, uint32_t RTC_AlarmSubSecondValue, uint32_t RTC_AlarmSubSecondMask)
{
    uint32_t tmpregister;

    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Configure the Alarm A or Alarm B SubSecond registers */
    tmpregister = (uint32_t)(uint32_t)(RTC_AlarmSubSecondValue) | (uint32_t)(RTC_AlarmSubSecondMask);

    if (RTC_Alarm == RTC_A_ALARM)
    {
        /* Configure the AlarmA SubSecond register */
        RTC->ALRMASS = tmpregister;
    }
    else
    {
        /* Configure the Alarm B SubSecond register */
        RTC->ALRMBSS = tmpregister;
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}


/**
*\*\name    RTC_GetAlarmSubSecond.
*\*\fun     Gets the RTC Alarm Subseconds value.
*\*\param   RTC_Alarm : specifies the alarm to be read.
*\*\            - RTC_A_ALARM : select Alarm A.
*\*\            - RTC_B_ALARM : select Alarm B.
*\*\return  RTC Alarm Subseconds value.
**/
uint32_t RTC_GetAlarmSubSecond(uint32_t RTC_Alarm)
{
    uint32_t tmpregister;

    /* Get the RTC_ALARMx register */
    if (RTC_Alarm == RTC_A_ALARM)
    {
        tmpregister = (uint32_t)((RTC->ALRMASS) & RTC_ALRMASS_SSV);
    }
    else
    {
        tmpregister = (uint32_t)((RTC->ALRMBSS) & RTC_ALRMBSS_SSV);
    }

    return (tmpregister);
}



/**
*\*\name    RTC_ConfigWakeUpClock.
*\*\fun     Configures the RTC Wakeup clock source.
*\*\param   RTC_WakeUpClock : RTC_WakeUpClock Wakeup Clock source.
*\*\            - RTC_WKUPCLK_RTCCLK_DIV16 : RTC Wakeup Counter Clock = RTCCLK/16.
*\*\            - RTC_WKUPCLK_RTCCLK_DIV8 : RTC Wakeup Counter Clock = RTCCLK/8.
*\*\            - RTC_WKUPCLK_RTCCLK_DIV4 : RTC Wakeup Counter Clock = RTCCLK/4.
*\*\            - RTC_WKUPCLK_RTCCLK_DIV2 : RTC Wakeup Counter Clock = RTCCLK/2.
*\*\            - RTC_WKUPCLK_CK_SPRE_16BITS : RTC Wakeup Counter Clock = CK_SPRE.
*\*\            - RTC_WKUPCLK_CK_SPRE_17BITS : RTC Wakeup Counter Clock = CK_SPRE,and wakeup timer count is 2^16.
*\*\return  none
**/
void RTC_ConfigWakeUpClock(uint32_t RTC_WakeUpClock)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Clear the Wakeup Timer clock source bits in CTRL register */
    RTC->CTRL &= (uint32_t)~RTC_CTRL_WKUPSEL;

    /* Configure the clock source */
    RTC->CTRL |= (uint32_t)RTC_WakeUpClock;

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_SetWakeUpCounter.
*\*\fun     Configures the RTC Wakeup counter.
*\*\param   RTC_WakeUpCounter : specifies the WakeUp counter, the value in the 0-0xFFFF range
*\*\return  none
**/
void RTC_SetWakeUpCounter(uint32_t RTC_WakeUpCounter)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Configure the Wakeup Timer counter */
    RTC->WKUPT = (uint32_t)RTC_WakeUpCounter;

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_GetWakeUpCounter.
*\*\fun     Returns the RTC WakeUp timer counter value.
*\*\param   none
*\*\return  The RTC WakeUp Counter value.
**/
uint32_t RTC_GetWakeUpCounter(void)
{
    /* Get the counter value */
    return ((uint32_t)(RTC->WKUPT & RTC_WKUPT_WKUPT));
}

/**
*\*\name    RTC_EnableWakeUp
*\*\fun     Enables or disables the RTC WakeUp timer.
*\*\param  Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  ErrorStatus :
*\*\            - SUCCESS: RTC wakeup configured succeed
*\*\            - ERROR:   RTC wakeup configured failed
**/
ErrorStatus RTC_EnableWakeUp(FunctionalState Cmd)
{
    __IO uint32_t wutcounter = 0x00;
    uint32_t wutwfstatus;
    ErrorStatus status;

    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    if (Cmd != DISABLE)
    {
        /* Enable the Wakeup Timer */
        RTC->CTRL |= (uint32_t)RTC_CTRL_WTEN;
        status = SUCCESS;
    }
    else
    {
        /* Disable the Wakeup Timer */
        RTC->CTRL &= (uint32_t)~RTC_CTRL_WTEN;

        /* Wait till RTC WTWF flag is set and if Time out is reached exit */
        do
        {
            wutwfstatus = RTC->INITSTS & RTC_INITSTS_WTWF;
            wutcounter++;
        }
        while ((wutcounter != INITMODE_TIMEOUT) && (wutwfstatus == 0x00));

        if ((RTC->INITSTS & RTC_INITSTS_WTWF) == RESET)
        {
            status = ERROR;
        }
        else
        {
            status = SUCCESS;
        }
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;

    return status;
}

/**
*\*\name    RTC_ConfigDayLightSaving
*\*\fun     Adds or substract one hour from the current time.
*\*\param   RTC_DayLightSaving : the value of hour adjustment.
*\*\            - RTC_DAYLIGHT_SAVING_SUB1H : Substract one hour (winter time).
*\*\            - RTC_DAYLIGHT_SAVING_ADD1H : Add one hour (summer time).
*\*\param   RTC_StoreOperation : Specifies the value to be written in the BCK bit
*\*\        in CTRL register to store the operation.
*\*\            - RTC_STORE_OPERATION_RESET :  BCK Bit Reset.
*\*\            - RTC_STORE_OPERATION_SET : BCK Bit Set.
*\*\return  none
**/
void RTC_ConfigDayLightSaving(uint32_t RTC_DayLightSaving, uint32_t RTC_StoreOperation)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Clear the bits to be configured */
    RTC->CTRL &= (uint32_t) ~(RTC_CTRL_BAKP);
    /* Clear the SU1H and AD1H bits to be configured */
    RTC->CTRL &= (uint32_t) ~(RTC_CTRL_SU1H & RTC_CTRL_AD1H);
    /* Configure the RTC_CTRL register */
    RTC->CTRL |= (uint32_t)(RTC_DayLightSaving | RTC_StoreOperation);

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_GetStoreOperation
*\*\fun     Returns the RTC Day Light Saving stored operation.
*\*\return  RTC Day Light Saving stored operation.
*\*\            - RTC_STORE_OPERATION_RESET
*\*\            - RTC_STORE_OPERATION_SET
**/
uint32_t RTC_GetStoreOperation(void)
{
    return (RTC->CTRL & RTC_CTRL_BAKP);
}

/**
*\*\name    RTC_EnableCalOVDetect
*\*\fun     Enable the RTC calendar overflow detection mechanism.
*\*\param  Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RTC_EnableCalOVDetect(FunctionalState Cmd)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    if (Cmd != DISABLE)
    {
        /* Set the CAOVEN bit */
        RTC->CTRL |= (uint8_t)RTC_CTRL_CAOVEN;
    }
    else
    {
        /* Reset the CAOVEN bit */
        RTC->CTRL &= (uint8_t)~RTC_CTRL_CAOVEN;
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_ConfigOutput
*\*\fun     Configures the RTC output source.
*\*\param   RTC_Output : RTC_Output Specifies which signal will be routed to the RTC output.
*\*\            - RTC_OUTPUT_DIS : No output selected
*\*\            - RTC_OUTPUT_ALA : signal of AlarmA mapped to output.
*\*\            - RTC_OUTPUT_ALB : signal of AlarmB mapped to output.
*\*\            - RTC_OUTPUT_WKUP: signal of WakeUp mapped to output.
*\*\param   RTC_OutputPolarity : Specifies the polarity of the output signal.
*\*\            - RTC_OUTPOL_HIGH: The output pin is high when the ALRAF/ALRBF/WUTF is high (depending on OSEL).
*\*\            - RTC_OUTPOL_LOW : The output pin is low when the ALRAF/ALRBF/WUTF is high (depending on OSEL).
*\*\return  none
**/
void RTC_ConfigOutput(uint32_t RTC_Output, uint32_t RTC_OutputPolarity)
{
    __IO uint32_t temp = 0;

    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Clear the bits to be configured */
    RTC->CTRL &= (uint32_t) ~(RTC_CTRL_OUTSEL | RTC_CTRL_OPOL);

    /* Configure the output selection and polarity */
    RTC->CTRL |= (uint32_t)(RTC_Output | RTC_OutputPolarity);

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_EnableTampOutput
*\*\fun     Enable or disable the RTC tamper output .
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RTC_EnableTampOutput(FunctionalState Cmd)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    if (Cmd != DISABLE)
    {
        /* Enable the RTC tamper output */
        RTC->CTRL |= (uint32_t)RTC_CTRL_TAMPOE;
    }
    else
    {
        /* Disable the RTC tamper output */
        RTC->CTRL &= (uint32_t)~RTC_CTRL_TAMPOE;
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_EnableCalibOutput
*\*\fun     Enable or disable the RTC calibration clock to be output through the relative pin.
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RTC_EnableCalibOutput(FunctionalState Cmd)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    if (Cmd != DISABLE)
    {
        /* Enable the RTC clock output */
        RTC->CTRL |= (uint32_t)RTC_CTRL_COEN;
    }
    else
    {
        /* Disable the RTC clock output */
        RTC->CTRL &= (uint32_t)~RTC_CTRL_COEN;
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_ConfigCalibOutput
*\*\fun     Configure the Calibration Pinout (RTC_CALIB) Selection (1Hz or 256Hz).
*\*\param   RTC_CalibOutput Select the Calibration output Selection .
*\*\            - RTC_CALIB_OUTPUT_256HZ : A signal has a regular waveform at 256Hz.
*\*\            - RTC_CALIB_OUTPUT_1HZ   : A signal has a regular waveform at 1Hz.
*\*\return  none
**/
void RTC_ConfigCalibOutput(uint32_t RTC_CalibOutput)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /*clear flags before config*/
    RTC->CTRL &= (uint32_t) ~(RTC_CTRL_CALOSEL);

    /* Configure the RTC_CTRL register */
    RTC->CTRL |= (uint32_t)RTC_CalibOutput;

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_ConfigSmoothCalib
*\*\fun     Configures the Smooth Calibration Settings.
*\*\param   RTC_SmoothCalibPeriod : RTC_SmoothCalibPeriod Select the Smooth Calibration Period.
*\*\            - SMOOTH_CALIB_32SEC : The smooth calibration periode is 32s.
*\*\            - SMOOTH_CALIB_16SEC : The smooth calibration periode is 16s.
*\*\            - SMOOTH_CALIB_8SEC  : The smooth calibartion periode is 8s.
*\*\param   RTC_SmoothCalibPlusPulses : Set or reset the CALP bit.
*\*\            - RTC_SMOOTH_CALIB_PLUS_PULSES_SET : Add one RTCCLK puls every 2**11 pulses.
*\*\            - RTC_SMOOTH_CALIB_PLUS_PULSES_RESET : No RTCCLK pulses are added.
*\*\param   RTC_SmouthCalibMinusPulsesValue : Set the value of CALM[8:0] bits, the value in the 0-0x000001FF range
*\*\return  ErrorStatus
*\*\            - SUCCESS : RTC Calib registers are configured
*\*\            - ERROR   : RTC Calib registers are not configured
**/
ErrorStatus RTC_ConfigSmoothCalib(uint32_t RTC_SmoothCalibPeriod,
                                  uint32_t RTC_SmoothCalibPlusPulses,
                                  uint32_t RTC_SmouthCalibMinusPulsesValue)
{
    ErrorStatus status;
    uint32_t recalpfcount = 0;

    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* check if a calibration is pending*/
    if ((RTC->INITSTS & RTC_INITSTS_RECPF) != RESET)
    {
        /* wait until the Calibration is completed*/
        while (((RTC->INITSTS & RTC_INITSTS_RECPF) != RESET) && (recalpfcount != RECALPF_TIMEOUT))
        {
            recalpfcount++;
        }
    }

    /* check if the calibration pending is completed or if there is no calibration operation at all*/
    if ((RTC->INITSTS & RTC_INITSTS_RECPF) == RESET)
    {
        /* Configure the Smooth calibration settings */
        RTC->CALIB = (uint32_t)((uint32_t)RTC_SmoothCalibPeriod | (uint32_t)RTC_SmoothCalibPlusPulses
                                | (uint32_t)RTC_SmouthCalibMinusPulsesValue);

        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;

    return (ErrorStatus)(status);
}

/**
*\*\name    RTC_EnableInterEventTimeStamp
*\*\fun     Enables or disables the RTC internal event trigger TimeStamp functionality.
 *\*\param  Cmd :
 *\*\          - ENABLE
 *\*\          - DISABLE
*\*\return  none
**/
void RTC_EnableInterEventTimeStamp(FunctionalState Cmd)
{
    uint32_t tmpregister;

    /* Get the RTC_CTRL register and clear the bits to be configured */
    tmpregister = (uint32_t)(RTC->CTRL & (uint32_t) ~(RTC_CTRL_IETSEN));

    /* Get the new configuration */
    if (Cmd != DISABLE)
    {
        tmpregister |= (uint32_t)(RTC_CTRL_IETSEN);
    }
    else
    {
        tmpregister &= ~(uint32_t)(RTC_CTRL_IETSEN);
    }

    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Configure the Time Stamp TSEDGE and Enable bits */
    RTC->CTRL = (uint32_t)tmpregister;

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_EnableTimeStamp
*\*\fun     Enables or disables the RTC TimeStamp functionality with the specified time stamp pin stimulating edge.
*\*\param   RTC_TimeStampEdge : Specifies the pin edge on which the TimeStamp is activated.
*\*\            - RTC_TIMESTAMP_EDGE_RISING : the Time stamp event occurs on the rising edge of the related pin.
*\*\            - RTC_TIMESTAMP_EDGE_FALLING : the Time stamp event occurs on the falling edge of the related pin.
 *\*\param  Cmd :
 *\*\          - ENABLE
 *\*\          - DISABLE
*\*\return  none
**/
void RTC_EnableTimeStamp(uint32_t RTC_TimeStampEdge, FunctionalState Cmd)
{
    uint32_t tmpregister;

    /* Get the RTC_CTRL register and clear the bits to be configured */
    tmpregister = (uint32_t)(RTC->CTRL & (uint32_t) ~(RTC_CTRL_TEDGE | RTC_CTRL_TSEN));

    /* Get the new configuration */
    if (Cmd != DISABLE)
    {
        tmpregister |= (uint32_t)(RTC_TimeStampEdge | RTC_CTRL_TSEN);
    }
    else
    {
        tmpregister |= (uint32_t)(RTC_TimeStampEdge);
    }

    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Configure the Time Stamp TSEDGE and Enable bits */
    RTC->CTRL = (uint32_t)tmpregister;

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_GetTimeStamp
*\*\fun     Get the RTC TimeStamp value and masks.
*\*\param   RTC_Format : specifies the format of the output parameters.
*\*\            - RTC_FORMAT_BIN : Binary data format
*\*\            - RTC_FORMAT_BCD : BCD data format
*\*\param   RTC_StampTimeStruct : pointer to a RTC_TimeType structure that will
*\*\        contains the TimeStamp time values.
*\*\param   RTC_StampDateStruct : pointer to a RTC_DateType structure that will
*\*\        contains the TimeStamp date values.
*\*\return  none
**/
void RTC_GetTimeStamp(uint32_t RTC_Format, RTC_TimeType* RTC_StampTimeStruct, RTC_DateType* RTC_StampDateStruct)
{
    uint32_t tmptime, tmpdate;

    /* Get the TimeStamp time and date registers values */
    tmptime = (uint32_t)(RTC->TST & RTC_TR_RESERVED_MASK);
    tmpdate = (uint32_t)(RTC->TSD & RTC_DATE_RESERVED_MASK);

    /* Fill the Time structure fields with the read parameters */
    RTC_StampTimeStruct->Hours   = (uint8_t)((tmptime & (RTC_TST_HOT | RTC_TST_HOU)) >> 16);
    RTC_StampTimeStruct->Minutes = (uint8_t)((tmptime & (RTC_TST_MIT | RTC_TST_MIU)) >> 8);
    RTC_StampTimeStruct->Seconds = (uint8_t)(tmptime & (RTC_TST_SET | RTC_TST_SEU));
    RTC_StampTimeStruct->H12     = (uint8_t)((tmptime & (RTC_TST_APM)) >> 16);

    /* Fill the Date structure fields with the read parameters */
    RTC_StampDateStruct->Month   = (uint8_t)((tmpdate & (RTC_DATE_MOT | RTC_DATE_MOU)) >> 8);
    RTC_StampDateStruct->Date    = (uint8_t)(tmpdate & (RTC_DATE_DAT | RTC_DATE_DAU));
    RTC_StampDateStruct->WeekDay = (uint8_t)((tmpdate & (RTC_DATE_WDU)) >> 13);

    /* Check the input parameters format */
    if (RTC_Format == RTC_FORMAT_BIN)
    {
        /* Convert the Time structure parameters to Binary format */
        RTC_StampTimeStruct->Hours   = (uint8_t)RTC_Bcd2ToByte(RTC_StampTimeStruct->Hours);
        RTC_StampTimeStruct->Minutes = (uint8_t)RTC_Bcd2ToByte(RTC_StampTimeStruct->Minutes);
        RTC_StampTimeStruct->Seconds = (uint8_t)RTC_Bcd2ToByte(RTC_StampTimeStruct->Seconds);

        /* Convert the Date structure parameters to Binary format */
        RTC_StampDateStruct->Month   = (uint8_t)RTC_Bcd2ToByte(RTC_StampDateStruct->Month);
        RTC_StampDateStruct->Date    = (uint8_t)RTC_Bcd2ToByte(RTC_StampDateStruct->Date);
        RTC_StampDateStruct->WeekDay = (uint8_t)RTC_Bcd2ToByte(RTC_StampDateStruct->WeekDay);
    }
}

/**
*\*\name    RTC_GetTimeStampSubSecond
*\*\fun     Get the RTC timestamp Subseconds value.
*\*\param   none
*\*\return  RTC current timestamp Subseconds value.
**/
uint32_t RTC_GetTimeStampSubSecond(void)
{
    /* Get timestamp subseconds values from the correspondent registers */
    return (uint32_t)(RTC->TSSS);
}


/**
*\*\name    RTC_ConfigOutputType
*\*\fun     Configures the RTC Output Pin mode.
*\*\param   RTC_OutputType : specifies the RTC Output (PC13) pin mode.
*\*\            - RTC_OUTPUT_OPENDRAIN : RTC Output (PC13) is configured in  Open Drain mode.
*\*\            - RTC_OUTPUT_PUSHPULL : RTC Output (PC13) is configured in Push Pull mode.
*\*\return  none
**/
void RTC_ConfigOutputType(uint32_t RTC_OutputType)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    RTC->OPT &= (uint32_t) ~(RTC_OPT_TYPE);
    RTC->OPT |= (uint32_t)(RTC_OutputType);

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_ConfigPWREvtSig
*\*\fun     Configures the RTC PWR event signal type.
*\*\param   signal_type :
*\*\          - RTC_PWR_SIGNAL_PULSE
*\*\          - RTC_PWR_SIGNAL_LEVEL
*\*\return  none
**/
void RTC_ConfigPWREvtSig(uint32_t signal_type)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    RTC->OPT &= (uint32_t) ~(RTC_OPT_PWREST);

    RTC->OPT |= (uint32_t)(signal_type);

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_ConfigOutputPullUp
*\*\fun     Configures the RTC Output PullUp .
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RTC_ConfigOutputPullUp(FunctionalState Cmd)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    RTC->OPT &= (uint32_t) ~(RTC_OPT_OUTPU);

    if(Cmd != DISABLE)
    {
        RTC->OPT |= (uint32_t)(RTC_OPT_OUTPU);
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_EnableOutput2
*\*\fun     Enable or disable the RTC output2 .
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RTC_EnableOutput2(FunctionalState Cmd)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    if (Cmd != DISABLE)
    {
        /* Enable the RTC output2 */
        RTC->OPT |= (uint32_t)RTC_OPT_OUTMAP;
    }
    else
    {
        /* Disable the RTC output2 */
        RTC->OPT &= (uint32_t)~RTC_OPT_OUTMAP;
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_ConfigOutputDuty
*\*\fun     Configures the RTC Output duty cycle.
*\*\param   Cmd :
*\*\          - RTC_Output_Duty_50
*\*\          - RTC_Output_Duty_DIV
*\*\return  none
**/
void RTC_ConfigOutputDuty(uint32_t duty_cycle)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    RTC->OPT &= (uint32_t) ~(RTC_Output_Duty_DIV);

    RTC->OPT |= (uint32_t)(duty_cycle);

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}


/**
*\*\name    RTC_ConfigSynchroShift
*\*\fun     Configures the Synchronization Shift Control Settings.
*\*\param   RTC_ShiftAdd1S : Select to add or not 1 second to the time Calendar.
*\*\            - RTC_SHIFT_SUB1S_DISABLE : Add one second to the clock calendar.
*\*\            - RTC_SHIFT_SUB1S_ENABLE : No effect.
*\*\param   RTC_ShiftSubFS : Select the number of Second Fractions to Substitute.
*\*\          This parameter can be one any value from 0 to 0x7FFF.
*\*\return  ErrorStatus :
*\*\            - SUCCESS : RTC Shift registers are configured
*\*\            - ERROR : RTC Shift registers are not configured
**/
ErrorStatus RTC_ConfigSynchroShift(uint32_t RTC_ShiftAdd1S, uint32_t RTC_ShiftSubFS)
{
    ErrorStatus status;
    uint32_t shpfcount = 0;

    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Check if a Shift is pending*/
    if ((RTC->INITSTS & RTC_INITSTS_SHOPF) != RESET)
    {
        /* Wait until the shift is completed*/
        while (((RTC->INITSTS & RTC_INITSTS_SHOPF) != RESET) && (shpfcount != SHPF_TIMEOUT))
        {
            shpfcount++;
        }
    }

    /* Check if the Shift pending is completed or if there is no Shift operation at all*/
    if ((RTC->INITSTS & RTC_INITSTS_SHOPF) == RESET)
    {
        /* check if the reference clock detection is disabled */
        if ((RTC->CTRL & RTC_CTRL_REFCLKEN) == RESET)
        {
            /* Configure the Shift settings */
            RTC->SCTRL = (uint32_t)(uint32_t)(RTC_ShiftSubFS) | (uint32_t)(RTC_ShiftAdd1S);

            if (RTC_WaitForSynchro() == ERROR)
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

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;

    return (ErrorStatus)(status);
}


/**
*\*\name    RTC_ConfigInt
*\*\fun     Enables or disables the specified RTC interrupts.
*\*\param   RTC_INT : specifies the RTC interrupt sources to be enabled .
*\*\            - RTC_INT_TS  : TimeStamp interrupt mask.
*\*\            - RTC_INT_WUT : WakeUp Timer interrupt mask.
*\*\            - RTC_INT_ALRB : Alarm B interrupt mask.
*\*\            - RTC_INT_ALRA : Alarm A interrupt mask.
*\*\            - RTC_INT_CAOV : Calendar overflow interrupt mask.
*\*\param  Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RTC_ConfigInt(uint32_t RTC_INT, FunctionalState Cmd)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    if (Cmd != DISABLE)
    {
        /* Configure the Interrupts in the RTC_CTRL register */
        RTC->CTRL |= (uint32_t)RTC_INT;
    }
    else
    {
        /* Configure the Interrupts in the RTC_CTRL register */
        RTC->CTRL &= (uint32_t) ~(RTC_INT);
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_GetFlagStatus
*\*\fun     Checks whether the specified RTC flag is set or not.
*\*\param   RTC_FLAG : specifies the flag to check.
*\*\          - RTC_FLAG_BPRAM_ERFRF : BKP_SRAM erase operation is in progress flag
*\*\          - RTC_FLAG_ITISF   : Internal Time Stamp event flag.
*\*\          - RTC_FLAG_CALOVF  : Calendar Overflow flag.
*\*\          - RTC_FLAG_TAMP8F  : Tamp8 detect flag.
*\*\          - RTC_FLAG_TAMP7F  : Tamp7 detect flag.
*\*\          - RTC_FLAG_TAMP6F  : Tamp6 detect flag.
*\*\          - RTC_FLAG_TAMP5F  : Tamp5 detect flag.
*\*\          - RTC_FLAG_TAMP4F  : Tamp4 detect flag.
*\*\          - RTC_FLAG_RECPF   : RECALPF event flag.
*\*\          - RTC_FLAG_TAMP3F  : Tamp3 detect flag.
*\*\          - RTC_FLAG_TAMP2F  : Tamp2 detect flag.
*\*\          - RTC_FLAG_TAMP1F  : Tamp1 detect flag.
*\*\          - RTC_FLAG_TISOVF  : Time Stamp OverFlow flag.
*\*\          - RTC_FLAG_TISF    : Time Stamp event flag.
*\*\          - RTC_FLAG_WTF     : WakeUp Timer flag.
*\*\          - RTC_FLAG_ALBF    : Alarm B flag.
*\*\          - RTC_FLAG_ALAF    : Alarm A flag.
*\*\          - RTC_FLAG_INITF   : Initialization mode flag.
*\*\          - RTC_FLAG_RSYF    : Registers Synchronized flag.
*\*\          - RTC_FLAG_INITSF  : Registers Configured flag.
*\*\          - RTC_FLAG_SHOPF   : Shift operation pending flag.
*\*\          - RTC_FLAG_WTWF    : WakeUp Timer Write flag.
*\*\          - RTC_FLAG_ALBWF   : Alarm B Write flag.
*\*\          - RTC_FLAG_ALAWF   : Alarm A write flag.
*\*\return  FlagStatus
*\*\          - SET   : the flag is set
*\*\          - RESET : the flag is reset
**/
FlagStatus RTC_GetFlagStatus(uint32_t RTC_FLAG)
{
    FlagStatus bitstatus;
    uint32_t tmpregister;

    /* Get all the flags */
    tmpregister = (uint32_t)(RTC->INITSTS & RTC_FLAGS_MASK);

    /* Return the status of the flag */
    if ((tmpregister & RTC_FLAG) != (uint32_t)RESET)
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
*\*\name    RTC_ClrFlag
*\*\fun     Clears the RTC's flags.
*\*\param   RTC_FLAG : RTC_FLAG specifies the RTC flag to clear.
*\*\          - RTC_FLAG_ITISF   : Internal Time Stamp event flag.
*\*\          - RTC_FLAG_CALOVF  : Calendar Overflow flag.
*\*\          - RTC_FLAG_TAMP8F  : Tamp8 detect flag.
*\*\          - RTC_FLAG_TAMP7F  : Tamp7 detect flag.
*\*\          - RTC_FLAG_TAMP6F  : Tamp6 detect flag.
*\*\          - RTC_FLAG_TAMP5F  : Tamp5 detect flag.
*\*\          - RTC_FLAG_TAMP4F  : Tamp4 detect flag.
*\*\          - RTC_FLAG_TAMP3F  : Tamp3 detect flag.
*\*\          - RTC_FLAG_TAMP2F  : Tamp2 detect flag.
*\*\          - RTC_FLAG_TAMP1F  : Tamp1 detect flag.
*\*\          - RTC_FLAG_TISOVF  : Time Stamp Overflow flag.
*\*\          - RTC_FLAG_TISF    : Time Stamp event flag.
*\*\          - RTC_FLAG_WTF     : WakeUp Timer flag
*\*\          - RTC_FLAG_ALBF    : Alarm B flag.
*\*\          - RTC_FLAG_ALAF    : Alarm A flag.
*\*\          - RTC_FLAG_RSYF    : Registers Synchronized flag.
*\*\return  none
**/
void RTC_ClrFlag(uint32_t RTC_FLAG)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Clear the Flags in the RTC_INITSTS register */
    RTC->INITSTS = (uint32_t)((uint32_t)(~((RTC_FLAG | RTC_INITSTS_INITM) & (uint32_t)0x00FFFFFF) |
                                         (uint32_t)(RTC->INITSTS & RTC_INITSTS_INITM)));

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_GetITStatus
*\*\fun     Checks whether the specified RTC interrupt has occurred or not.
*\*\param   RTC_INT : specifies the RTC interrupt source to check.
*\*\          - RTC_INT_CAOV : Calendar overflow interrupt.
*\*\          - RTC_INT_TAMP8 : Tamper8 interrupt.
*\*\          - RTC_INT_TAMP7 : Tamper7 interrupt.
*\*\          - RTC_INT_TAMP6 : Tamper6 interrupt.
*\*\          - RTC_INT_TAMP5 : Tamper5 interrupt.
*\*\          - RTC_INT_TAMP4 : Tamper4 interrupt.
*\*\          - RTC_INT_TAMP3 : Tamper3 interrupt.
*\*\          - RTC_INT_TAMP2 : Tamper2 interrupt.
*\*\          - RTC_INT_TAMP1 : Tamper1 interrupt.
*\*\          - RTC_INT_TS    : Timestamp interrupt.
*\*\          - RTC_INT_WUT   : WakeUp Timer interrupt.
*\*\          - RTC_INT_ALRB  : Alarm B interrupt.
*\*\          - RTC_INT_ALRA  : Alarm A interrupt.
*\*\return  INTStatus
*\*\          - SET   : the flag is set
*\*\          - RESET : the flag is reset
**/
INTStatus RTC_GetITStatus(uint32_t RTC_INT)
{
    INTStatus bitstatus;
    uint32_t tmpregister, enablestatus = 0;
    uint32_t tamperEnable;
    uint32_t tampernum;
    uint8_t i;

    /* Get the Interrupt enable Status */
    if ((RTC_INT == RTC_INT_TAMP1) || (RTC_INT == RTC_INT_TAMP2) ||  (RTC_INT == RTC_INT_TAMP3) ||
            (RTC_INT == RTC_INT_TAMP4) || (RTC_INT == RTC_INT_TAMP5) || (RTC_INT == RTC_INT_TAMP6) ||
            (RTC_INT == RTC_INT_TAMP7) ||  (RTC_INT == RTC_INT_TAMP8))
    {
        for(i = 0; i < 9; i++)
        {
            if((RTC_INT >> (i + 17)) & (uint32_t)0x01)
            {
                if(i < 3)
                {
                    tampernum = i;
                    break;
                }
                else if(i > 3)
                {
                    tampernum = i - 1;
                    break;
                }
            }
        }

        tamperEnable = RTC->TMPCTRL[tampernum] & RTC_TMPCTRL_TPINTEN;

        if (tamperEnable != (uint32_t)RESET)
        {
            enablestatus = (uint32_t)0x00000001;
        }
    }
    else
    {
        enablestatus = (uint32_t)((RTC->CTRL & RTC_INT));
    }

    if(RTC_INT == RTC_INT_CAOV)
    {
        /* Get the Interrupt pending bit */
        tmpregister = (uint32_t)((RTC->INITSTS & (uint32_t)(RTC_INT >> 5)));
    }
    else
    {
        /* Get the Interrupt pending bit */
        tmpregister = (uint32_t)((RTC->INITSTS & (uint32_t)(RTC_INT >> 4)));
    }

    /* Get the status of the Interrupt */
    if ((enablestatus != (uint32_t)RESET) && ((tmpregister & (uint32_t)0x001FFFFF) != (uint32_t)RESET))
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
*\*\name    RTC_ClrIntPendingBit
*\*\fun     Clears the RTC's interrupt pending bits.
*\*\param   RTC_INT : specifies the RTC interrupt pending bit to clear.
*\*\          - RTC_INT_CAOV : Calendar overflow interrupt.
*\*\          - RTC_INT_TAMP8 : Tamper8 interrupt.
*\*\          - RTC_INT_TAMP7 : Tamper7 interrupt.
*\*\          - RTC_INT_TAMP6 : Tamper6 interrupt.
*\*\          - RTC_INT_TAMP5 : Tamper5 interrupt.
*\*\          - RTC_INT_TAMP4 : Tamper4 interrupt.
*\*\          - RTC_INT_TAMP3 : Tamper3 interrupt.
*\*\          - RTC_INT_TAMP2 : Tamper2 interrupt.
*\*\          - RTC_INT_TAMP1 : Tamper1 interrupt.
*\*\          - RTC_INT_TS    : Timestamp interrupt.
*\*\          - RTC_INT_WUT   : WakeUp Timer interrupt
*\*\          - RTC_INT_ALRB  : Alarm B interrupt
*\*\          - RTC_INT_ALRA  : Alarm A interrupt
*\*\return  none
**/
void RTC_ClrIntPendingBit(uint32_t RTC_INT)
{
    uint32_t tmpregister;

    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Get the RTC_INITSTS Interrupt pending bits mask */
    tmpregister = (uint32_t)(RTC_INT >> 4);

    /* Clear the interrupt pending bits in the RTC_INITSTS register */
    RTC->INITSTS = (uint32_t)((uint32_t)(~((tmpregister | RTC_INITSTS_INITM) & (uint32_t)0x01FFFFFF) |
                                         (uint32_t)(RTC->INITSTS & RTC_INITSTS_INITM)));

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_TamperTriggerConfig
*\*\fun     Configures the select Tamper pin edge.
*\*\param   RTC_Tamper: Selected tamper pin.
*\*\          - RTC_TAMPER_1: Select Tamper 1.
*\*\          - RTC_TAMPER_2: Select Tamper 2.
*\*\          - RTC_TAMPER_3: Select Tamper 3.
*\*\          - RTC_TAMPER_4: Select Tamper 4.
*\*\          - RTC_TAMPER_5: Select Tamper 5.
*\*\          - RTC_TAMPER_6: Select Tamper 6.
*\*\          - RTC_TAMPER_7: Select Tamper 7.
*\*\          - RTC_TAMPER_8: Select Tamper 8.
*\*\param   RTC_TamperTrigger: Specifies the trigger on the tamper pin that stimulates tamper event.
*\*\          - RTC_TamperTrigger_RisingEdge: Rising Edge of the tamper pin causes tamper event.
*\*\          - RTC_TamperTrigger_FallingEdge: Falling Edge of the tamper pin causes tamper event.
*\*\          - RTC_TamperTrigger_LowLevel: Low Level of the tamper pin causes tamper event.
*\*\          - RTC_TamperTrigger_HighLevel: High Level of the tamper pin causes tamper event.
*\*\return  none
**/
void RTC_TamperTriggerConfig(uint32_t RTC_Tamper, uint32_t RTC_TamperTrigger)
{
    uint32_t tmaper_trigger = RTC_TamperTrigger;

    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    RTC->TMPCTRL[RTC_Tamper] &= (uint32_t)(~RTC_TMPCTRL_TPTRG);

    /* Configure the RTC_TAMPCTRL register */
    RTC->TMPCTRL[RTC_Tamper] |= tmaper_trigger;

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;

}

/**
*\*\name    RTC_TamperCmd
*\*\fun     Enables or disables the specified Tamper detection.
*\*\param   RTC_Tamper: Selected tamper pin.
*\*\          - RTC_TAMPER_1: Select Tamper 1.
*\*\          - RTC_TAMPER_2: Select Tamper 2.
*\*\          - RTC_TAMPER_3: Select Tamper 3.
*\*\          - RTC_TAMPER_4: Select Tamper 4.
*\*\          - RTC_TAMPER_5: Select Tamper 5.
*\*\          - RTC_TAMPER_6: Select Tamper 6.
*\*\          - RTC_TAMPER_7: Select Tamper 7.
*\*\          - RTC_TAMPER_8: Select Tamper 8.
*\*\param  NewState :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RTC_TamperCmd(uint32_t RTC_Tamper, FunctionalState NewState)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    if (NewState != DISABLE)
    {
        /* Enable the selected Tamper pin */
        RTC->TMPCTRL[RTC_Tamper] |= (uint32_t)RTC_TMPCTRL_TPEN;
    }
    else
    {
        /* Disable the selected Tamper pin */
        RTC->TMPCTRL[RTC_Tamper] &= (uint32_t)~RTC_TMPCTRL_TPEN;
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_TamperFilterConfig
*\*\fun     Configures the Tampers Filter.
*\*\param   RTC_TamperFilter: Selected tamper pin.
*\*\            - RTC_TamperFilter_Disable: Tamper filter is disabled.
*\*\            - RTC_TamperFilter_2Sample: Tamper is activated after 2 consecutive samples at the active level.
*\*\            - RTC_TamperFilter_4Sample: Tamper is activated after 4 consecutive samples at the active level.
*\*\            - RTC_TamperFilter_8Sample: Tamper is activated after 8 consecutive samples at the active level.
*\*\return  none
**/
void RTC_TamperFilterConfig(uint32_t RTC_TamperFilter)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Clear TAMPFLT[1:0] bits in the RTC_TAMPCR register */
    RTC->TMPCFG &= (uint32_t)~(RTC_TMPCFG_TPFLT);

    /* Configure the RTC_TAMPCR register */
    RTC->TMPCFG |= (uint32_t)RTC_TamperFilter;

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_TamperSamplingFreqConfig
*\*\fun     Configures the Tampers Sampling Frequency.
*\*\param   RTC_TamperSamplingFreq: Selected tamper pin.
*\*\            - RTC_TamperSamplingFreq_RTCCLK_Div32768
*\*\            - RTC_TamperSamplingFreq_RTCCLK_Div16384
*\*\            - RTC_TamperSamplingFreq_RTCCLK_Div8192
*\*\            - RTC_TamperSamplingFreq_RTCCLK_Div4096
*\*\            - RTC_TamperSamplingFreq_RTCCLK_Div2048
*\*\            - RTC_TamperSamplingFreq_RTCCLK_Div1024
*\*\            - RTC_TamperSamplingFreq_RTCCLK_Div512
*\*\            - RTC_TamperSamplingFreq_RTCCLK_Div256
*\*\return  none
**/
void RTC_TamperSamplingFreqConfig(uint32_t RTC_TamperSamplingFreq)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Clear TAMPFREQ[2:0] bits in the RTC_TAMPCR register */
    RTC->TMPCFG &= (uint32_t)~(RTC_TAMPCR_TAMPFREQ);

    /* Configure the RTC_TAMPCR register */
    RTC->TMPCFG |= (uint32_t)RTC_TamperSamplingFreq;

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_TamperPinsPrechargeDuration
*\*\fun     Configures the Tampers Pins input Precharge Duration.
*\*\param   RTC_TamperPrechargeDuration: Selected tamper pin.
*\*\            - RTC_TamperPrechargeDuration_1RTCCLK
*\*\            - RTC_TamperPrechargeDuration_2RTCCLK
*\*\            - RTC_TamperPrechargeDuration_4RTCCLK
*\*\            - RTC_TamperPrechargeDuration_8RTCCLK
*\*\return  none
**/
void RTC_TamperPinsPrechargeDuration(uint32_t RTC_TamperPrechargeDuration)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    /* Clear TAMPPRCH[1:0] bits in the RTC_TAMPCR register */
    RTC->TMPCFG &= (uint32_t)~(RTC_TMPCFG_TPPRCH);

    /* Configure the RTC_TAMPCR register */
    RTC->TMPCFG |= (uint32_t)RTC_TamperPrechargeDuration;

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}


/**
*\*\name    RTC_TimeStampOnTamperDetectionCmd
*\*\fun     The timestamp is valid or invalid even the TSEN bit in tamper control register is reset.
*\*\param   NewState :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RTC_TimeStampOnTamperDetectionCmd(FunctionalState NewState)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    if (NewState != DISABLE)
    {
        /* Save timestamp on tamper detection event */
        RTC->TMPCFG |= (uint32_t)RTC_TMPCFG_TPTS;
    }
    else
    {
        /* Tamper detection does not cause a timestamp to be saved */
        RTC->TMPCFG &= (uint32_t)~RTC_TMPCFG_TPTS;
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_TamperPullUpCmd
*\*\fun     Enables or disables the Precharge of Tamper pin.
*\*\param   NewState :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RTC_TamperPullUpCmd(FunctionalState NewState)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    if (NewState != DISABLE)
    {
        /* Enable precharge of the selected Tamper pin */
        RTC->TMPCFG &= (uint32_t)~RTC_TMPCFG_TPPUDIS;
    }
    else
    {
        /* Disable precharge of the selected Tamper pin */
        RTC->TMPCFG |= (uint32_t)RTC_TMPCFG_TPPUDIS;
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_EnableTampErase
*\*\fun     Enables or disables the tamper event erase backup register.
*\*\param   RTC_Tamper: Selected tamper event.
*\*\          - RTC_TAMPER_1: Select Tamper 1 erase backup register.
*\*\          - RTC_TAMPER_2: Select Tamper 2 erase backup register.
*\*\          - RTC_TAMPER_3: Select Tamper 3 erase backup register.
*\*\          - RTC_TAMPER_4: Select Tamper 4 erase backup register.
*\*\          - RTC_TAMPER_5: Select Tamper 5 erase backup register.
*\*\          - RTC_TAMPER_6: Select Tamper 6 erase backup register.
*\*\          - RTC_TAMPER_7: Select Tamper 7 erase backup register.
*\*\          - RTC_TAMPER_8: Select Tamper 8 erase backup register.
*\*\param  NewState :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RTC_EnableTampErase(uint32_t RTC_Tamper, FunctionalState NewState)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    if (NewState != DISABLE)
    {
        /* Enable tamper event erase backup register */
        RTC->TMPCTRL[RTC_Tamper] &= (uint32_t)~RTC_TMPCTRL_TPNOE;
    }
    else
    {
        /* Disable tamper event erase backup register */
        RTC->TMPCTRL[RTC_Tamper] |= (uint32_t)RTC_TMPCTRL_TPNOE;
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_TamperAllIECmd
*\*\fun     Enables or disables all Tamper interrupt.
*\*\param   RTC_Tamper: Selected tamper pin.
*\*\          - RTC_TAMPER_1: Select Tamper 1.
*\*\          - RTC_TAMPER_2: Select Tamper 2.
*\*\          - RTC_TAMPER_3: Select Tamper 3.
*\*\          - RTC_TAMPER_4: Select Tamper 4.
*\*\          - RTC_TAMPER_5: Select Tamper 5.
*\*\          - RTC_TAMPER_6: Select Tamper 6.
*\*\          - RTC_TAMPER_7: Select Tamper 7.
*\*\          - RTC_TAMPER_8: Select Tamper 8.
*\*\param  NewState :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RTC_TamperMskCmd(uint32_t RTC_Tamper, FunctionalState NewState)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    if (NewState != DISABLE)
    {
        /* Enable the selected Tamper mask */
        RTC->TMPCTRL[RTC_Tamper] |= (uint32_t)RTC_TMPCTRL_TPMF;
    }
    else
    {
        /* Disable the selected Tamper mask */
        RTC->TMPCTRL[RTC_Tamper] &= (uint32_t)~RTC_TMPCTRL_TPMF;
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}


/**
*\*\name    RTC_TamperIECmd
*\*\fun     Enables or disables the Tamper interrupt.
*\*\param   RTC_Tamper: Selected tamper pin.
*\*\          - RTC_TAMPER_1: Select Tamper 1.
*\*\          - RTC_TAMPER_2: Select Tamper 2.
*\*\          - RTC_TAMPER_3: Select Tamper 3.
*\*\          - RTC_TAMPER_4: Select Tamper 4.
*\*\          - RTC_TAMPER_5: Select Tamper 5.
*\*\          - RTC_TAMPER_6: Select Tamper 6.
*\*\          - RTC_TAMPER_7: Select Tamper 7.
*\*\          - RTC_TAMPER_8: Select Tamper 8.
*\*\param  NewState :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void RTC_TamperIECmd(uint32_t RTC_Tamper, FunctionalState NewState)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    if (NewState != DISABLE)
    {
        /* Enable the selected Tamper pin */
        RTC->TMPCTRL[RTC_Tamper] |= (uint32_t)RTC_TMPCTRL_TPINTEN;
    }
    else
    {
        /* Disable the selected Tamper pin */
        RTC->TMPCTRL[RTC_Tamper] &= (uint32_t)~RTC_TMPCTRL_TPINTEN;
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_BKUPRgWrite
*\*\fun     Write data to backup register.
*\*\param   register_num: register_num value can be from 1 to 32
*\*\param   Data : Data write to backup register
*\*\return  none
**/
void RTC_BKUPRgWrite(uint8_t register_num, uint32_t Data)
{
    uint32_t tmpregister;

    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;

    tmpregister = (uint32_t) & (RTC->BKP1);

    if(register_num > 0 && register_num <= 32)
    {
        tmpregister += (((uint32_t)register_num - 1) * 4);
        /* Write data to specified register */
        *(__IO uint32_t *)tmpregister = Data;
    }

    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_BKUPRgRead
*\*\fun     Read data from backup register.
*\*\param   register_num: register_num value can be from 1 to 32
*\*\param   Data : Data write to backup register
*\*\return  none
**/
uint32_t RTC_BKUPRgRead(uint8_t register_num)
{
    uint32_t tmpregister, value = 0;

    tmpregister = (uint32_t) & (RTC->BKP1);

    if(register_num > 0 && register_num <= 32)
    {
        tmpregister += (((uint32_t)register_num - 1) * 4);
        value = *(__IO uint32_t *)tmpregister;
    }

    return value;
}

/**
*\*\name    RTC_ByteToBcd2
*\*\fun     Converts a 2 digit decimal to BCD format.
*\*\param   value : Value Byte to be converted.
*\*\return  Converted byte
**/
static uint8_t RTC_ByteToBcd2(uint8_t Value)
{
    uint8_t bcdhigh = 0;
    uint8_t temp_value = Value;

    while (temp_value >= 10)
    {
        bcdhigh++;
        temp_value -= 10;
    }

    return ((uint8_t)(bcdhigh << 4) | temp_value);
}

/**
*\*\name    RTC_Bcd2ToByte
*\*\fun     Convert from 2 digit BCD to Binary.
*\*\param   Value : Value BCD value to be converted.
*\*\return  Converted byte
**/
static uint8_t RTC_Bcd2ToByte(uint8_t Value)
{
    uint8_t tmp;
    tmp = ((uint8_t)(Value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
    return (tmp + (Value & (uint8_t)0x0F));
}
