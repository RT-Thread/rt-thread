/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32l43x_rtc.c
 * @author Nations
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "n32l43x_rtc.h"

/** @addtogroup n32l43x_StdPeriph_Driver
 * @{
 */

/** @addtogroup RTC
 * @brief RTC driver modules
 * @{
 */

/* Masks Definition */
#define RTC_TR_RESERVED_MASK   ((uint32_t)0x007F7F7F)
#define RTC_DATE_RESERVED_MASK ((uint32_t)0x00FFFF3F)

#define RTC_RSF_MASK           ((uint32_t)0xFFFFFFDF)
#define RTC_FLAGS_MASK                                                                                                 \
    ((uint32_t)(RTC_FLAG_TISOVF | RTC_FLAG_TISF | RTC_FLAG_WTF | RTC_FLAG_ALBF | RTC_FLAG_ALAF | RTC_FLAG_INITF        \
                | RTC_FLAG_RSYF | RTC_FLAG_INITSF | RTC_FLAG_WTWF | RTC_FLAG_ALBWF | RTC_FLAG_ALAWF | RTC_FLAG_RECPF   \
                | RTC_FLAG_SHOPF))

#define INITMODE_TIMEOUT ((uint32_t)0x00002000)
#define SYNCHRO_TIMEOUT  ((uint32_t)0x00008000)
#define RECALPF_TIMEOUT  ((uint32_t)0x00001000)
#define SHPF_TIMEOUT     ((uint32_t)0x00002000)

static uint8_t RTC_ByteToBcd2(uint8_t Value);
static uint8_t RTC_Bcd2ToByte(uint8_t Value);

/** @addtogroup RTC_Private_Functions
 * @{
 */

/** @addtogroup RTC_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================
    [..] This section provide functions allowing to initialize and configure the
         RTC Prescaler (Synchronous and Asynchronous), RTC Hour format, disable
         RTC registers Write protection, enter and exit the RTC initialization mode,
         RTC registers synchronization check and reference clock detection enable.
         (#) The RTC Prescaler is programmed to generate the RTC 1Hz time base.
             It is split into 2 programmable prescalers to minimize power consumption.
             (++) A 7-bit asynchronous prescaler and A 13-bit synchronous prescaler.
             (++) When both prescalers are used, it is recommended to configure the
                 asynchronous prescaler to a high value to minimize consumption.
         (#) All RTC registers are Write protected. Writing to the RTC registers
             is enabled by writing a key into the Write Protection register, RTC_WRP.
         (#) To Configure the RTC Calendar, user application should enter
             initialization mode. In this mode, the calendar counter is stopped
             and its value can be updated. When the initialization sequence is
             complete, the calendar restarts counting after 4 RTCCLK cycles.
         (#) To read the calendar through the shadow registers after Calendar
             initialization, calendar update or after wakeup from low power modes
             the software must first clear the RSYF flag. The software must then
             wait until it is set again before reading the calendar, which means
             that the calendar registers have been correctly copied into the
             RTC_TSH and RTC_DATE shadow registers.The RTC_WaitForSynchro() function
             implements the above software sequence (RSYF clear and RSYF check).

@endverbatim
  * @{
  */

/**
 * @brief  Deinitializes the RTC registers to their default reset values.
 * @note   This function doesn't reset the RTC Clock source and RTC Backup Data
 *         registers.
 * @return An ErrorStatus enumeration value:
 *          - SUCCESS: RTC registers are deinitialized
 *          - ERROR: RTC registers are not deinitialized
 */
ErrorStatus RTC_DeInit(void)
{
    __IO uint32_t wutcounter = 0x00;
    uint32_t wutwfstatus     = 0x00;
    ErrorStatus status       = ERROR;
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
       } while ((wutcounter != INITMODE_TIMEOUT) && (wutwfstatus == 0x00));
       if ((RTC->INITSTS & RTC_INITSTS_WTWF) == RESET)
       {
           status = ERROR;
       }
       else
       {
          /* Reset all RTC CTRL register bits */
          RTC->CTRL &= (uint32_t)0x00000000;
          RTC->WKUPT   = (uint32_t)0x0000FFFF;
          RTC->PRE     = (uint32_t)0x007F00FF;
          RTC->ALARMA  = (uint32_t)0x00000000;
          RTC->ALARMB  = (uint32_t)0x00000000;
          RTC->SCTRL   = (uint32_t)0x00000000;
          RTC->CALIB   = (uint32_t)0x00000000;
          RTC->ALRMASS = (uint32_t)0x00000000;
          RTC->ALRMBSS = (uint32_t)0x00000000;
          /* Reset INTSTS register and exit initialization mode */
          RTC->INITSTS = (uint32_t)0x00000000;
          RTC->OPT         = (uint32_t)0x00000000;
          RTC->TSCWKUPCTRL = (uint32_t)0x00000008;
          RTC->TSCWKUPCNT  = (uint32_t)0x000002FE;
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
 * @brief  Initializes the RTC registers according to the specified parameters
 *         in RTC_InitStruct.
 * @param RTC_InitStruct pointer to a RTC_InitType structure that contains
 *         the configuration information for the RTC peripheral.
 * @note   The RTC Prescaler register is write protected and can be written in
 *         initialization mode only.
 * @return An ErrorStatus enumeration value:
 *          - SUCCESS: RTC registers are initialized
 *          - ERROR: RTC registers are not initialized
 */
ErrorStatus RTC_Init(RTC_InitType* RTC_InitStruct)
{
    ErrorStatus status = ERROR;
    uint32_t i =0;
    /* Check the parameters */
    assert_param(IS_RTC_HOUR_FORMAT(RTC_InitStruct->RTC_HourFormat));
    assert_param(IS_RTC_PREDIV_ASYNCH(RTC_InitStruct->RTC_AsynchPrediv));
    assert_param(IS_RTC_PREDIV_SYNCH(RTC_InitStruct->RTC_SynchPrediv));
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
    for(i=0;i<0x2FF;i++);
    return status;
}

/**
 * @brief  Fills each RTC_InitStruct member with its default value.
 * @param RTC_InitStruct pointer to a RTC_InitType structure which will be
 *         initialized.
 */
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
 * @brief  Enables or disables the RTC registers write protection.
 * @note   All the RTC registers are write protected except for RTC_INITSTS[13:8].
 * @note   Writing a wrong key reactivates the write protection.
 * @note   The protection mechanism is not affected by system reset.
 * @param Cmd new state of the write protection.
 *   This parameter can be: ENABLE or DISABLE.
 */
void RTC_EnableWriteProtection(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
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
 * @brief  Enters the RTC Initialization mode.
 * @note   The RTC Initialization mode is write protected, use the
 *         RTC_EnableWriteProtection(DISABLE) before calling this function.
 * @return An ErrorStatus enumeration value:
 *          - SUCCESS: RTC is in Init mode
 *          - ERROR: RTC is not in Init mode
 */
ErrorStatus RTC_EnterInitMode(void)
{
    __IO uint32_t initcounter = 0x00;
    ErrorStatus status        = ERROR;
    uint32_t initstatus       = 0x00;
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
       } while ((initcounter != INITMODE_TIMEOUT) && (initstatus == 0x00));
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
 * @brief  Exits the RTC Initialization mode.
 * @note   When the initialization sequence is complete, the calendar restarts
 *         counting after 4 RTCCLK cycles.
 * @note   The RTC Initialization mode is write protected, use the
 *         RTC_EnableWriteProtection(DISABLE) before calling this function.
 */
void RTC_ExitInitMode(void)
{
    /* Exit Initialization mode */
    RTC->INITSTS &= (uint32_t)~RTC_INITSTS_INITM;
}

/**
 * @brief  Waits until the RTC Time and Date registers (RTC_TSH and RTC_DATE) are
 *         synchronized with RTC APB clock.
 * @note   The RTC Resynchronization mode is write protected, use the
 *         RTC_EnableWriteProtection(DISABLE) before calling this function.
 * @note   To read the calendar through the shadow registers after Calendar
 *         initialization, calendar update or after wakeup from low power modes
 *         the software must first clear the RSYF flag.
 *         The software must then wait until it is set again before reading
 *         the calendar, which means that the calendar registers have been
 *         correctly copied into the RTC_TSH and RTC_DATE shadow registers.
 * @return An ErrorStatus enumeration value:
 *          - SUCCESS: RTC registers are synchronised
 *          - ERROR: RTC registers are not synchronised
 */
ErrorStatus RTC_WaitForSynchro(void)
{
    __IO uint32_t synchrocounter = 0;
    ErrorStatus status           = ERROR;
    uint32_t synchrostatus       = 0x00;
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;
    /* Clear RSYF flag */
    RTC->INITSTS &= (uint32_t)RTC_RSF_MASK;
    /* Wait the registers to be synchronised */
    do
    {
       synchrostatus = RTC->INITSTS & RTC_INITSTS_RSYF;
       synchrocounter++;
    } while ((synchrocounter != SYNCHRO_TIMEOUT) && (synchrostatus == 0x00));
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
 * @brief  Enables or disables the RTC reference clock detection.
 * @param Cmd new state of the RTC reference clock.
 *   This parameter can be: ENABLE or DISABLE.
 * @return An ErrorStatus enumeration value:
 *          - SUCCESS: RTC reference clock detection is enabled
 *          - ERROR: RTC reference clock detection is disabled
 */
ErrorStatus RTC_EnableRefClock(FunctionalState Cmd)
{
    ErrorStatus status = ERROR;
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
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
 * @brief  Enables or Disables the Bypass Shadow feature.
 * @note   When the Bypass Shadow is enabled the calendar value are taken
 *         directly from the Calendar counter.
 * @param Cmd new state of the Bypass Shadow feature.
 *         This parameter can be: ENABLE or DISABLE.
 */
void RTC_EnableBypassShadow(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
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
 * @}
 */

/** @addtogroup RTC_Group2 Time and Date configuration functions
 *  @brief   Time and Date configuration functions
 *
@verbatim
 ===============================================================================
               ##### Time and Date configuration functions #####
 ===============================================================================
    [..] This section provide functions allowing to program and read the RTC
         Calendar (Time and Date).

@endverbatim
  * @{
  */

/**
 * @brief  Set the RTC current time.
 * @param RTC_Format specifies the format of the entered parameters.
 *   This parameter can be  one of the following values:
 *     @arg RTC_FORMAT_BIN Binary data format.
 *     @arg RTC_FORMAT_BCD BCD data format.
 * @param RTC_TimeStruct pointer to a RTC_TimeType structure that contains
 *                        the time configuration information for the RTC.
 * @return An ErrorStatus enumeration value:
 *          - SUCCESS: RTC Time register is configured
 *          - ERROR: RTC Time register is not configured
 */
ErrorStatus RTC_ConfigTime(uint32_t RTC_Format, RTC_TimeType* RTC_TimeStruct)
{
    uint32_t tmpregister = 0;
    ErrorStatus status   = ERROR;
    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));
    if (RTC_Format == RTC_FORMAT_BIN)
    {
       if ((RTC->CTRL & RTC_CTRL_HFMT) != (uint32_t)RESET)
       {
          assert_param(IS_RTC_12HOUR(RTC_TimeStruct->Hours));
          assert_param(IS_RTC_H12(RTC_TimeStruct->H12));
       }
       else
       {
          RTC_TimeStruct->H12 = 0x00;
          assert_param(IS_RTC_24HOUR(RTC_TimeStruct->Hours));
       }
       assert_param(IS_RTC_MINUTES(RTC_TimeStruct->Minutes));
       assert_param(IS_RTC_SECONDS(RTC_TimeStruct->Seconds));
    }
    else
    {
       if ((RTC->CTRL & RTC_CTRL_HFMT) != (uint32_t)RESET)
       {
          tmpregister = RTC_Bcd2ToByte(RTC_TimeStruct->Hours);
          assert_param(IS_RTC_12HOUR(tmpregister));
          assert_param(IS_RTC_H12(RTC_TimeStruct->H12));
       }
       else
       {
          RTC_TimeStruct->H12 = 0x00;
          assert_param(IS_RTC_24HOUR(RTC_Bcd2ToByte(RTC_TimeStruct->Hours)));
       }
       assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(RTC_TimeStruct->Minutes)));
       assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(RTC_TimeStruct->Seconds)));
    }
    /* Check the input parameters format */
    if (RTC_Format != RTC_FORMAT_BIN)
    {
       tmpregister = (((uint32_t)(RTC_TimeStruct->Hours) << 16) | ((uint32_t)(RTC_TimeStruct->Minutes) << 8)
                     | ((uint32_t)RTC_TimeStruct->Seconds) | ((uint32_t)(RTC_TimeStruct->H12) << 16));
    }
    else
    {
       tmpregister =(uint32_t)(((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->Hours) << 16)
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
    status=RTC_WaitForSynchro();
    return status;
}

/**
 * @brief  Fills each RTC_TimeStruct member with its default value
 *         (Time = 00h:00min:00sec).
 * @param RTC_TimeStruct pointer to a RTC_TimeType structure which will be
 *         initialized.
 */
void RTC_TimeStructInit(RTC_TimeType* RTC_TimeStruct)
{
    /* Time = 00h:00min:00sec */
    RTC_TimeStruct->H12     = RTC_AM_H12;
    RTC_TimeStruct->Hours   = 0;
    RTC_TimeStruct->Minutes = 0;
    RTC_TimeStruct->Seconds = 0;
}

/**
 * @brief  Get the RTC current Time.
 * @param RTC_Format specifies the format of the returned parameters.
 *   This parameter can be  one of the following values:
 *     @arg RTC_FORMAT_BIN Binary data format.
 *     @arg RTC_FORMAT_BCD BCD data format.
 * @param RTC_TimeStruct pointer to a RTC_TimeType structure that will
 *                        contain the returned current time configuration.
 */
void RTC_GetTime(uint32_t RTC_Format, RTC_TimeType* RTC_TimeStruct)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));
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
 * @brief  Gets the RTC current Calendar Subseconds value.
 * @return RTC current Calendar Subseconds value.
 */
uint32_t RTC_GetSubSecond(void)
{
    uint32_t tmpregister = 0;
    /* Get subseconds values from the correspondent registers*/
    tmpregister = (uint32_t)(RTC->SUBS);
    return (tmpregister);
}

/**
 * @brief  Set the RTC current date.
 * @param RTC_Format specifies the format of the entered parameters.
 *   This parameter can be  one of the following values:
 *     @arg RTC_FORMAT_BIN Binary data format.
 *     @arg RTC_FORMAT_BCD BCD data format.
 * @param RTC_DateStruct pointer to a RTC_DateType structure that contains
 *                         the date configuration information for the RTC.
 * @return An ErrorStatus enumeration value:
 *          - SUCCESS: RTC Date register is configured
 *          - ERROR: RTC Date register is not configured
 */
ErrorStatus RTC_SetDate(uint32_t RTC_Format, RTC_DateType* RTC_DateStruct)
{
    uint32_t tmpregister = 0;
    ErrorStatus status   = ERROR;
    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));
    if ((RTC_Format == RTC_FORMAT_BIN) && ((RTC_DateStruct->Month & 0x10) == 0x10))
    {
        RTC_DateStruct->Month = (RTC_DateStruct->Month & (uint32_t) ~(0x10)) + 0x0A;
    }
    if (RTC_Format == RTC_FORMAT_BIN)
    {
        assert_param(IS_RTC_YEAR(RTC_DateStruct->Year));
        assert_param(IS_RTC_MONTH(RTC_DateStruct->Month));
        assert_param(IS_RTC_DATE(RTC_DateStruct->Date));
    }
    else
    {
        assert_param(IS_RTC_YEAR(RTC_Bcd2ToByte(RTC_DateStruct->Year)));
        tmpregister = RTC_Bcd2ToByte(RTC_DateStruct->Month);
        assert_param(IS_RTC_MONTH(tmpregister));
        tmpregister = RTC_Bcd2ToByte(RTC_DateStruct->Date);
        assert_param(IS_RTC_DATE(tmpregister));
    }
    assert_param(IS_RTC_WEEKDAY(RTC_DateStruct->WeekDay));
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
    status=RTC_WaitForSynchro();
    return status;
}

/**
 * @brief  Fills each RTC_DateStruct member with its default value
 *         (Monday, January 01 xx00).
 * @param RTC_DateStruct pointer to a RTC_DateType structure which will be
 *         initialized.
 */
void RTC_DateStructInit(RTC_DateType* RTC_DateStruct)
{
    /* Monday, January 01 xx00 */
    RTC_DateStruct->WeekDay = RTC_WEEKDAY_MONDAY;
    RTC_DateStruct->Date    = 1;
    RTC_DateStruct->Month   = RTC_MONTH_JANUARY;
    RTC_DateStruct->Year    = 0;
}

/**
 * @brief  Get the RTC current date.
 * @param RTC_Format specifies the format of the returned parameters.
 *   This parameter can be one of the following values:
 *     @arg RTC_FORMAT_BIN Binary data format.
 *     @arg RTC_FORMAT_BCD BCD data format.
 * @param RTC_DateStruct pointer to a RTC_DateType structure that will
 *                        contain the returned current date configuration.
 */
void RTC_GetDate(uint32_t RTC_Format, RTC_DateType* RTC_DateStruct)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));
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
 * @}
 */

/** @addtogroup RTC_Group3 Alarms configuration functions
 *  @brief   Alarms (Alarm A and Alarm B) configuration functions
 *
@verbatim
 ===============================================================================
         ##### Alarms (Alarm A and Alarm B) configuration functions #####
 ===============================================================================
    [..] This section provide functions allowing to program and read the RTC
         Alarms.

@endverbatim
  * @{
  */

/**
 * @brief  Set the specified RTC Alarm.
 * @note   The Alarm register can only be written when the corresponding Alarm
 *         is disabled (Use the RTC_EnableAlarm(DISABLE)).
 * @param RTC_Format specifies the format of the returned parameters.
 *   This parameter can be one of the following values:
 *     @arg RTC_FORMAT_BIN Binary data format.
 *     @arg RTC_FORMAT_BCD BCD data format.
 * @param RTC_Alarm specifies the alarm to be configured.
 *   This parameter can be one of the following values:
 *     @arg RTC_A_ALARM to select Alarm A.
 *     @arg RTC_B_ALARM to select Alarm B.
 * @param RTC_AlarmStruct pointer to a RTC_AlarmType structure that
 *                          contains the alarm configuration parameters.
 */
void RTC_SetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmType* RTC_AlarmStruct)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));
    assert_param(IS_RTC_ALARM_SEL(RTC_Alarm));
    assert_param(IS_ALARM_MASK(RTC_AlarmStruct->AlarmMask));
    assert_param(IS_RTC_ALARM_WEEKDAY_SEL(RTC_AlarmStruct->DateWeekMode));
    if (RTC_Format == RTC_FORMAT_BIN)
    {
       if ((RTC->CTRL & RTC_CTRL_HFMT) != (uint32_t)RESET)
       {
          assert_param(IS_RTC_12HOUR(RTC_AlarmStruct->AlarmTime.Hours));
          assert_param(IS_RTC_H12(RTC_AlarmStruct->AlarmTime.H12));
       }
       else
       {
          RTC_AlarmStruct->AlarmTime.H12 = 0x00;
          assert_param(IS_RTC_24HOUR(RTC_AlarmStruct->AlarmTime.Hours));
       }
       assert_param(IS_RTC_MINUTES(RTC_AlarmStruct->AlarmTime.Minutes));
       assert_param(IS_RTC_SECONDS(RTC_AlarmStruct->AlarmTime.Seconds));
       if (RTC_AlarmStruct->DateWeekMode == RTC_ALARM_SEL_WEEKDAY_DATE)
       {
          assert_param(IS_RTC_ALARM_WEEKDAY_DATE(RTC_AlarmStruct->DateWeekValue));
       }
       else
       {
          assert_param(IS_RTC_ALARM_WEEKDAY_WEEKDAY(RTC_AlarmStruct->DateWeekValue));
       }
    }
    else
    {
      if ((RTC->CTRL & RTC_CTRL_HFMT) != (uint32_t)RESET)
      {
         tmpregister = RTC_Bcd2ToByte(RTC_AlarmStruct->AlarmTime.Hours);
         assert_param(IS_RTC_12HOUR(tmpregister));
         assert_param(IS_RTC_H12(RTC_AlarmStruct->AlarmTime.H12));
      }
      else
      {
         RTC_AlarmStruct->AlarmTime.H12 = 0x00;
         assert_param(IS_RTC_24HOUR(RTC_Bcd2ToByte(RTC_AlarmStruct->AlarmTime.Hours)));
      }
      assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(RTC_AlarmStruct->AlarmTime.Minutes)));
      assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(RTC_AlarmStruct->AlarmTime.Seconds)));
      if (RTC_AlarmStruct->DateWeekMode == RTC_ALARM_SEL_WEEKDAY_DATE)
      {
         tmpregister = RTC_Bcd2ToByte(RTC_AlarmStruct->DateWeekValue);
         assert_param(IS_RTC_ALARM_WEEKDAY_DATE(tmpregister));
      }
      else
      {
         tmpregister = RTC_Bcd2ToByte(RTC_AlarmStruct->DateWeekValue);
         assert_param(IS_RTC_ALARM_WEEKDAY_WEEKDAY(tmpregister));
      }
    }
    /* Check the input parameters format */
    if (RTC_Format != RTC_FORMAT_BIN)
    {
        tmpregister = (((uint32_t)(RTC_AlarmStruct->AlarmTime.Hours) << 16)
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
 * @brief  Fills each RTC_AlarmStruct member with its default value
 *         (Time = 00h:00mn:00sec / Date = 1st day of the month/Mask =
 *         all fields are masked).
 * @param RTC_AlarmStruct pointer to a @ref RTC_AlarmType structure which
 *         will be initialized.
 */
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
 * @brief  Get the RTC Alarm value and masks.
 * @param RTC_Format specifies the format of the output parameters.
 *   This parameter can be one of the following values:
 *     @arg RTC_FORMAT_BIN Binary data format.
 *     @arg RTC_FORMAT_BCD BCD data format.
 * @param RTC_Alarm specifies the alarm to be read.
 *   This parameter can be one of the following values:
 *     @arg RTC_A_ALARM to select Alarm A.
 *     @arg RTC_B_ALARM to select Alarm B.
 * @param RTC_AlarmStruct pointer to a RTC_AlarmType structure that will
 *                          contains the output alarm configuration values.
 */
void RTC_GetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmType* RTC_AlarmStruct)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));
    assert_param(IS_RTC_ALARM_SEL(RTC_Alarm));
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
    RTC_AlarmStruct->AlarmTime.Hours   = (uint32_t)((tmpregister & (RTC_ALARMA_HOT | RTC_ALARMA_HOU)) >> 16);
    RTC_AlarmStruct->AlarmTime.Minutes = (uint32_t)((tmpregister & (RTC_ALARMA_MIT | RTC_ALARMA_MIU)) >> 8);
    RTC_AlarmStruct->AlarmTime.Seconds = (uint32_t)(tmpregister & (RTC_ALARMA_SET | RTC_ALARMA_SEU));
    RTC_AlarmStruct->AlarmTime.H12     = (uint32_t)((tmpregister & RTC_ALARMA_APM) >> 16);
    RTC_AlarmStruct->DateWeekValue     = (uint32_t)((tmpregister & (RTC_ALARMA_DTT | RTC_ALARMA_DTU)) >> 24);
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
 * @brief  Enables or disables the specified RTC Alarm.
 * @param RTC_Alarm specifies the alarm to be configured.
 *   This parameter can be any combination of the following values:
 *     @arg RTC_A_ALARM to select Alarm A.
 *     @arg RTC_B_ALARM to select Alarm B.
 * @param Cmd new state of the specified alarm.
 *   This parameter can be: ENABLE or DISABLE.
 * @return An ErrorStatus enumeration value:
 *          - SUCCESS: RTC Alarm is enabled/disabled
 *          - ERROR: RTC Alarm is not enabled/disabled
 */
ErrorStatus RTC_EnableAlarm(uint32_t RTC_Alarm, FunctionalState Cmd)
{
    __IO uint32_t alarmcounter = 0x00;
    uint32_t alarmstatus       = 0x00;
    ErrorStatus status         = ERROR;
    /* Check the parameters */
    assert_param(IS_RTC_ALARM_ENABLE(RTC_Alarm));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
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
       } while ((alarmcounter != INITMODE_TIMEOUT) && (alarmstatus == 0x00));
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
 * @brief  Configure the RTC AlarmA/B Subseconds value and mask.*
 * @note   This function is performed only when the Alarm is disabled.
 * @param RTC_Alarm specifies the alarm to be configured.
 *   This parameter can be one of the following values:
 *     @arg RTC_A_ALARM to select Alarm A.
 *     @arg RTC_B_ALARM to select Alarm B.
 * @param RTC_AlarmSubSecondValue specifies the Subseconds value.
 *   This parameter can be a value from 0 to 0x00007FFF.
 * @param RTC_AlarmSubSecondMask specifies the Subseconds Mask.
 *   This parameter can be any combination of the following values:
 *     @arg RTC_SUBS_MASK_ALL All Alarm SS fields are masked.
 *                                      There is no comparison on sub seconds for Alarm.
 *     @arg RTC_SUBS_MASK_SS14_1 SS[14:1] are don't care in Alarm comparison.
 *                                         Only SS[0] is compared
 *     @arg RTC_SUBS_MASK_SS14_2 SS[14:2] are don't care in Alarm comparison.
 *                                          Only SS[1:0] are compared
 *     @arg RTC_SUBS_MASK_SS14_3 SS[14:3] are don't care in Alarm comparison.
 *                                          Only SS[2:0] are compared
 *     @arg RTC_SUBS_MASK_SS14_4 SS[14:4] are don't care in Alarm comparison.
 *                                          Only SS[3:0] are compared
 *     @arg RTC_SUBS_MASK_SS14_5 SS[14:5] are don't care in Alarm comparison.
 *                                          Only SS[4:0] are compared.
 *     @arg RTC_SUBS_MASK_SS14_6 SS[14:6] are don't care in Alarm comparison.
 *                                          Only SS[5:0] are compared.
 *     @arg RTC_SUBS_MASK_SS14_7 SS[14:7] are don't care in Alarm comparison.
 *                                          Only SS[6:0] are compared.
 *     @arg RTC_SUBS_MASK_SS14_8 SS[14:8] are don't care in Alarm comparison.
 *                                          Only SS[7:0] are compared.
 *     @arg RTC_SUBS_MASK_SS14_9 SS[14:9] are don't care in Alarm comparison.
 *                                          Only SS[8:0] are compared.
 *     @arg RTC_SUBS_MASK_SS14_10 SS[14:10] are don't care in Alarm comparison.
 *                                          Only SS[9:0] are compared.
 *     @arg RTC_SUBS_MASK_SS14_11 SS[14:11] are don't care in Alarm comparison.
 *                                          Only SS[10:0] are compared.
 *     @arg RTC_SUBS_MASK_SS14_12 SS[14:12] are don't care in Alarm comparison.
 *                                          Only SS[11:0] are compared.
 *     @arg RTC_SUBS_MASK_SS14_13 SS[14:13] are don't care in Alarm comparison.
 *                                          Only SS[12:0] are compared.
 *     @arg RTC_SUBS_MASK_SS14_14 SS[14] is don't care in Alarm comparison.
 *                                          Only SS[13:0] are compared.
 *     @arg RTC_SUBS_MASK_NONE SS[14:0] are compared and must match
 *                                          to activate alarm.
 */
void RTC_ConfigAlarmSubSecond(uint32_t RTC_Alarm, uint32_t RTC_AlarmSubSecondValue, uint32_t RTC_AlarmSubSecondMask)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RTC_ALARM_SEL(RTC_Alarm));
    assert_param(IS_RTC_ALARM_SUB_SECOND_VALUE(RTC_AlarmSubSecondValue));
    assert_param(IS_RTC_ALARM_SUB_SECOND_MASK_MODE(RTC_AlarmSubSecondMask));
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
 * @brief  Gets the RTC Alarm Subseconds value.
 * @param RTC_Alarm specifies the alarm to be read.
 *   This parameter can be one of the following values:
 *     @arg RTC_A_ALARM to select Alarm A.
 *     @arg RTC_B_ALARM to select Alarm B.
 * @return RTC Alarm Subseconds value.
 */
uint32_t RTC_GetAlarmSubSecond(uint32_t RTC_Alarm)
{
    uint32_t tmpregister = 0;
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
 * @}
 */

/** @addtogroup RTC_Group4 WakeUp Timer configuration functions
 *  @brief   WakeUp Timer configuration functions
 *
@verbatim
 ===============================================================================
               ##### WakeUp Timer configuration functions #####
 ===============================================================================
    [..] This section provide functions allowing to program and read the RTC WakeUp.

@endverbatim
  * @{
  */

/**
 * @brief  Configures the RTC Wakeup clock source.
 * @note   The WakeUp Clock source can only be changed when the RTC WakeUp
 *         is disabled (Use the RTC_EnableWakeUp(DISABLE)).
 * @param RTC_WakeUpClock Wakeup Clock source.
 *   This parameter can be one of the following values:
 *            @arg RTC_WKUPCLK_RTCCLK_DIV16 RTC Wakeup Counter Clock = RTCCLK/16.
 *            @arg RTC_WKUPCLK_RTCCLK_DIV8 RTC Wakeup Counter Clock = RTCCLK/8.
 *            @arg RTC_WKUPCLK_RTCCLK_DIV4 RTC Wakeup Counter Clock = RTCCLK/4.
 *            @arg RTC_WKUPCLK_RTCCLK_DIV2 RTC Wakeup Counter Clock = RTCCLK/2.
 *            @arg RTC_WKUPCLK_CK_SPRE_16BITS RTC Wakeup Counter Clock = CK_SPRE.
 *            @arg RTC_WKUPCLK_CK_SPRE_17BITS RTC Wakeup Counter Clock = CK_SPRE.
 */
void RTC_ConfigWakeUpClock(uint32_t RTC_WakeUpClock)
{
    /* Check the parameters */
    assert_param(IS_RTC_WKUP_CLOCK(RTC_WakeUpClock));
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
 * @brief  Configures the RTC Wakeup counter.
 * @note   The RTC WakeUp counter can only be written when the RTC WakeUp.
 *         is disabled (Use the RTC_EnableWakeUp(DISABLE)).
 * @param RTC_WakeUpCounter specifies the WakeUp counter.
 *   This parameter can be a value from 0x0000 to 0xFFFF.
 */
void RTC_SetWakeUpCounter(uint32_t RTC_WakeUpCounter)
{
    /* Check the parameters */
    assert_param(IS_RTC_WKUP_COUNTER(RTC_WakeUpCounter));
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;
    /* Configure the Wakeup Timer counter */
    RTC->WKUPT = (uint32_t)RTC_WakeUpCounter;
    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
 * @brief  Returns the RTC WakeUp timer counter value.
 * @return The RTC WakeUp Counter value.
 */
uint32_t RTC_GetWakeUpCounter(void)
{
    /* Get the counter value */
    return ((uint32_t)(RTC->WKUPT & RTC_WKUPT_WKUPT));
}

/**
 * @brief  Enables or Disables the RTC WakeUp timer.
 * @param Cmd new state of the WakeUp timer.
 *   This parameter can be: ENABLE or DISABLE.
 */
ErrorStatus RTC_EnableWakeUp(FunctionalState Cmd)
{
    __IO uint32_t wutcounter = 0x00;
    uint32_t wutwfstatus     = 0x00;
    ErrorStatus status       = ERROR;
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
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
       } while ((wutcounter != INITMODE_TIMEOUT) && (wutwfstatus == 0x00));
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
 * @}
 */

/** @addtogroup RTC_Group5 Daylight Saving configuration functions
 *  @brief   Daylight Saving configuration functions
 *
@verbatim
 ===============================================================================
              ##### Daylight Saving configuration functions #####
 ===============================================================================
    [..] This section provide functions allowing to configure the RTC DayLight Saving.

@endverbatim
  * @{
  */

/**
 * @brief  Adds or substract one hour from the current time.
 * @param RTC_DayLightSaving the value of hour adjustment.
 *   This parameter can be one of the following values:
 *     @arg RTC_DAYLIGHT_SAVING_SUB1H Substract one hour (winter time).
 *     @arg RTC_DAYLIGHT_SAVING_ADD1H Add one hour (summer time).
 * @param RTC_StoreOperation Specifies the value to be written in the BCK bit
 *                            in CTRL register to store the operation.
 *   This parameter can be one of the following values:
 *            @arg RTC_STORE_OPERATION_RESET BCK Bit Reset.
 *            @arg RTC_STORE_OPERATION_SET BCK Bit Set.
 */
void RTC_ConfigDayLightSaving(uint32_t RTC_DayLightSaving, uint32_t RTC_StoreOperation)
{
    /* Check the parameters */
    assert_param(IS_RTC_DAYLIGHT_SAVING(RTC_DayLightSaving));
    assert_param(IS_RTC_STORE_OPERATION(RTC_StoreOperation));
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
 * @brief  Returns the RTC Day Light Saving stored operation.
 * @return RTC Day Light Saving stored operation.
 *          - RTC_STORE_OPERATION_RESET
 *          - RTC_STORE_OPERATION_SET
 */
uint32_t RTC_GetStoreOperation(void)
{
    return (RTC->CTRL & RTC_CTRL_BAKP);
}

/**
 * @}
 */




/**
 * @brief  Configures the RTC output source (AFO_ALARM).
 * @param RTC_Output Specifies which signal will be routed to the RTC output.
 *   This parameter can be one of the following values:
 *     @arg RTC_OUTPUT_DIS No output selected
 *     @arg RTC_OUTPUT_ALA signal of AlarmA mapped to output.
 *     @arg RTC_OUTPUT_ALB signal of AlarmB mapped to output.
 *     @arg RTC_OUTPUT_WKUP signal of WakeUp mapped to output.
 * @param RTC_OutputPolarity Specifies the polarity of the output signal.
 *   This parameter can be one of the following:
 *     @arg RTC_OUTPOL_HIGH The output pin is high when the
 *                                 ALRAF/ALRBF/WUTF is high (depending on OSEL).
 *     @arg RTC_OUTPOL_LOW The output pin is low when the
 *                                 ALRAF/ALRBF/WUTF is high (depending on OSEL).
 */
void RTC_ConfigOutput(uint32_t RTC_Output, uint32_t RTC_OutputPolarity)
{
    /* Check the parameters */
    assert_param(IS_RTC_OUTPUT_MODE(RTC_Output));
    assert_param(IS_RTC_OUTPUT_POL(RTC_OutputPolarity));
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
 * @}
 */

/** @addtogroup RTC_Group7 Coarse and Smooth Calibrations configuration functions
 *  @brief   Coarse and Smooth Calibrations configuration functions
 *
@verbatim
 ===============================================================================
        ##### Coarse and Smooth Calibrations configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
 * @brief  Enables or disables the RTC clock to be output through the relative
 *         pin.
 * @param Cmd new state of the coarse calibration Output.
 *   This parameter can be: ENABLE or DISABLE.
 */
void RTC_EnableCalibOutput(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
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
 * @brief  Configure the Calibration Pinout (RTC_CALIB) Selection (1Hz or 512Hz).
 * @param RTC_CalibOutput Select the Calibration output Selection .
 *   This parameter can be one of the following values:
 *     @arg RTC_CALIB_OUTPUT_256HZ A signal has a regular waveform at 256Hz.
 *     @arg RTC_CALIB_OUTPUT_1HZ A signal has a regular waveform at 1Hz.
 */
void RTC_ConfigCalibOutput(uint32_t RTC_CalibOutput)
{
    /* Check the parameters */
    assert_param(IS_RTC_CALIB_OUTPUT(RTC_CalibOutput));
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
 * @brief  Configures the Smooth Calibration Settings.
 * @param RTC_SmoothCalibPeriod Select the Smooth Calibration Period.
 *   This parameter can be can be one of the following values:
 *     @arg SMOOTH_CALIB_32SEC The smooth calibration periode is 32s.
 *     @arg SMOOTH_CALIB_16SEC The smooth calibration periode is 16s.
 *     @arg SMOOTH_CALIB_8SEC The smooth calibartion periode is 8s.
 * @param RTC_SmoothCalibPlusPulses Select to Set or reset the CALP bit.
 *   This parameter can be one of the following values:
 *     @arg RTC_SMOOTH_CALIB_PLUS_PULSES_SET Add one RTCCLK puls every 2**11 pulses.
 *     @arg RTC_SMOOTH_CALIB_PLUS_PULSES__RESET No RTCCLK pulses are added.
 * @param RTC_SmouthCalibMinusPulsesValue Select the value of CALM[8:0] bits.
 *   This parameter can be one any value from 0 to 0x000001FF.
 * @return An ErrorStatus enumeration value:
 *          - SUCCESS: RTC Calib registers are configured
 *          - ERROR: RTC Calib registers are not configured
 */
ErrorStatus RTC_ConfigSmoothCalib(uint32_t RTC_SmoothCalibPeriod,
                                  uint32_t RTC_SmoothCalibPlusPulses,
                                  uint32_t RTC_SmouthCalibMinusPulsesValue)
{
    ErrorStatus status    = ERROR;
    uint32_t recalpfcount = 0;
    /* Check the parameters */
    assert_param(IS_RTC_SMOOTH_CALIB_PERIOD_SEL(RTC_SmoothCalibPeriod));
    assert_param(IS_RTC_SMOOTH_CALIB_PLUS(RTC_SmoothCalibPlusPulses));
    assert_param(IS_RTC_SMOOTH_CALIB_MINUS(RTC_SmouthCalibMinusPulsesValue));
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
 * @}
 */

/** @addtogroup RTC_Group8 TimeStamp configuration functions
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
 * @brief  Enables or Disables the RTC TimeStamp functionality with the
 *         specified time stamp pin stimulating edge.
 * @param RTC_TimeStampEdge Specifies the pin edge on which the TimeStamp is
 *         activated.
 *   This parameter can be one of the following:
 *     @arg RTC_TIMESTAMP_EDGE_RISING the Time stamp event occurs on the rising
 *                                    edge of the related pin.
 *     @arg RTC_TIMESTAMP_EDGE_FALLING the Time stamp event occurs on the
 *                                     falling edge of the related pin.
 * @param Cmd new state of the TimeStamp.
 *   This parameter can be: ENABLE or DISABLE.
 */
void RTC_EnableTimeStamp(uint32_t RTC_TimeStampEdge, FunctionalState Cmd)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RTC_TIMESTAMP_EDGE_MODE(RTC_TimeStampEdge));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
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
 * @brief  Get the RTC TimeStamp value and masks.
 * @param RTC_Format specifies the format of the output parameters.
 *   This parameter can be one of the following values:
 *     @arg RTC_FORMAT_BIN Binary data format
 *     @arg RTC_FORMAT_BCD BCD data format
 * @param RTC_StampTimeStruct pointer to a RTC_TimeType structure that will
 *                             contains the TimeStamp time values.
 * @param RTC_StampDateStruct pointer to a RTC_DateType structure that will
 *                             contains the TimeStamp date values.
 */
void RTC_GetTimeStamp(uint32_t RTC_Format, RTC_TimeType* RTC_StampTimeStruct, RTC_DateType* RTC_StampDateStruct)
{
    uint32_t tmptime = 0, tmpdate = 0;
    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));
    /* Get the TimeStamp time and date registers values */
    tmptime = (uint32_t)(RTC->TST & RTC_TR_RESERVED_MASK);
    tmpdate = (uint32_t)(RTC->TSD & RTC_DATE_RESERVED_MASK);
    /* Fill the Time structure fields with the read parameters */
    RTC_StampTimeStruct->Hours   = (uint8_t)((tmptime & (RTC_TSH_HOT | RTC_TSH_HOU)) >> 16);
    RTC_StampTimeStruct->Minutes = (uint8_t)((tmptime & (RTC_TSH_MIT | RTC_TSH_MIU)) >> 8);
    RTC_StampTimeStruct->Seconds = (uint8_t)(tmptime & (RTC_TSH_SCT | RTC_TSH_SCU));
    RTC_StampTimeStruct->H12     = (uint8_t)((tmptime & (RTC_TSH_APM)) >> 16);
    /* Fill the Date structure fields with the read parameters */
    RTC_StampDateStruct->Year    = (uint8_t)((tmpdate & (RTC_DATE_YRT | RTC_DATE_YRU)) >> 16);
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
 * @brief  Get the RTC timestamp Subseconds value.
 * @return RTC current timestamp Subseconds value.
 */
uint32_t RTC_GetTimeStampSubSecond(void)
{
    /* Get timestamp subseconds values from the correspondent registers */
    return (uint32_t)(RTC->TSSS);
}

/**
 * @}
 */

/** @addtogroup RTC_Group11 Output Type Config configuration functions
 *  @brief   Output Type Config configuration functions
 *
@verbatim
 ===============================================================================
             ##### Output Type Config configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
 * @brief  Configures the RTC Output Pin mode.
 * @param RTC_OutputType specifies the RTC Output (PC13) pin mode.
 *   This parameter can be one of the following values:
 *     @arg RTC_OUTPUT_OPENDRAIN RTC Output (PC13) is configured in
 *                                    Open Drain mode.
 *     @arg RTC_OUTPUT_PUSHPULL RTC Output (PC13) is configured in
 *                                    Push Pull mode.
 */
void RTC_ConfigOutputType(uint32_t RTC_OutputType)
{
    /* Check the parameters */
    assert_param(IS_RTC_OUTPUT_TYPE(RTC_OutputType));
    RTC->OPT &= (uint32_t) ~(RTC_OPT_TYPE);
    RTC->OPT |= (uint32_t)(RTC_OutputType);
}

/**
 * @}
 */

/** @addtogroup RTC_Group12 Shift control synchronisation functions
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
 * @param RTC_ShiftAdd1S Select to add or not 1 second to the time Calendar.
 *   This parameter can be one of the following values :
 *     @arg RTC_SHIFT_ADD1S_ENABLE Add one second to the clock calendar.
 *     @arg RTC_SHIFT_ADD1S_DISABLE No effect.
 * @param RTC_ShiftSubFS Select the number of Second Fractions to Substitute.
 *         This parameter can be one any value from 0 to 0x7FFF.
 * @return An ErrorStatus enumeration value:
 *          - SUCCESS: RTC Shift registers are configured
 *          - ERROR: RTC Shift registers are not configured
 */
ErrorStatus RTC_ConfigSynchroShift(uint32_t RTC_ShiftAdd1S, uint32_t RTC_ShiftSubFS)
{
    ErrorStatus status = ERROR;
    uint32_t shpfcount = 0;
    /* Check the parameters */
    assert_param(IS_RTC_SHIFT_ADD1S(RTC_ShiftAdd1S));
    assert_param(IS_RTC_SHIFT_SUBFS(RTC_ShiftSubFS));
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
 * @}
 */

/** @addtogroup RTC_Group13 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
 *
@verbatim
 ===============================================================================
            ##### Interrupts and flags management functions #####
 ===============================================================================
    [..] All RTC interrupts are connected to the EXTI controller.
         (+) To enable the RTC Alarm interrupt, the following sequence is required:
         (+) Configure and enable the EXTI Line 17 in interrupt mode and select
             the rising edge sensitivity using the EXTI_InitPeripheral() function.
         (+) Configure and enable the RTC_Alarm IRQ channel in the NVIC using
             the NVIC_Init() function.
         (+) Configure the RTC to generate RTC alarms (Alarm A and/or Alarm B)
             using the RTC_SetAlarm() and RTC_EnableAlarm() functions.

         (+) To enable the RTC Wakeup interrupt, the following sequence is required:
         (+) Configure and enable the EXTI Line 20 in interrupt mode and select
             the rising edge sensitivity using the EXTI_InitPeripheral() function.
         (+) Configure and enable the RTC_WKUP IRQ channel in the NVIC using the
             NVIC_Init() function.
         (+) Configure the RTC to generate the RTC wakeup timer event using the
             RTC_ConfigWakeUpClock(), RTC_SetWakeUpCounter() and RTC_EnableWakeUp()
             functions.

         (+) To enable the RTC Tamper interrupt, the following sequence is required:
         (+) Configure and enable the EXTI Line 19 in interrupt mode and select
             the rising edge sensitivity using the EXTI_InitPeripheral() function.
         (+) Configure and enable the TAMP_STAMP IRQ channel in the NVIC using
             the NVIC_Init() function.
         (+) Configure the RTC to detect the RTC tamper event using the
             RTC_TamperTriggerConfig() and RTC_TamperCmd() functions.

         (+) To enable the RTC TimeStamp interrupt, the following sequence is
             required:
         (+) Configure and enable the EXTI Line 19 in interrupt mode and select
             the rising edge sensitivity using the EXTI_InitPeripheral() function.
         (+) Configure and enable the TAMP_STAMP IRQ channel in the NVIC using
             the NVIC_Init() function.
         (+) Configure the RTC to detect the RTC time-stamp event using the
             RTC_EnableTimeStamp() functions.

@endverbatim
  * @{
  */

/**
 * @brief  Enables or disables the specified RTC interrupts.
 * @param RTC_INT specifies the RTC interrupt sources to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg RTC_INT_TS Time Stamp interrupt mask.
 *     @arg RTC_INT_WUT WakeUp Timer interrupt mask.
 *     @arg RTC_INT_ALRB Alarm B interrupt mask.
 *     @arg RTC_INT_ALRA Alarm A interrupt mask.
 * @param Cmd new state of the specified RTC interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 */
void RTC_ConfigInt(uint32_t RTC_INT, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_RTC_CONFIG_INT(RTC_INT));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;
    if (Cmd != DISABLE)
    {
       /* Configure the Interrupts in the RTC_CTRL register */
       RTC->CTRL |= (uint32_t)(RTC_INT & ~RTC_TMPCFG_TPINTEN);
    }
    else
    {
       /* Configure the Interrupts in the RTC_CTRL register */
       RTC->CTRL &= (uint32_t) ~(RTC_INT & (uint32_t)~RTC_TMPCFG_TPINTEN);
    }
    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
 * @brief  Checks whether the specified RTC flag is set or not.
 * @param RTC_FLAG specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg RTC_FLAG_RECPF RECALPF event flag.
 *     @arg RTC_FLAG_TAMP3F: Tamper 3 event flag.
 *     @arg RTC_FLAG_TAMP2F: Tamper 2 event flag.
 *     @arg RTC_FLAG_TAMP1F: Tamper 1 event flag.
 *     @arg RTC_FLAG_TISOVF Time Stamp OverFlow flag.
 *     @arg RTC_FLAG_TISF Time Stamp event flag.
 *     @arg RTC_FLAG_WTF WakeUp Timer flag.
 *     @arg RTC_FLAG_ALBF Alarm B flag.
 *     @arg RTC_FLAG_ALAF Alarm A flag.
 *     @arg RTC_FLAG_INITF Initialization mode flag.
 *     @arg RTC_FLAG_RSYF Registers Synchronized flag.
 *     @arg RTC_FLAG_INITSF Registers Configured flag.
 *     @arg RTC_FLAG_SHOPF Shift operation pending flag.
 *     @arg RTC_FLAG_WTWF WakeUp Timer Write flag.
 *     @arg RTC_FLAG_ALBWF Alarm B Write flag.
 *     @arg RTC_FLAG_ALAWF Alarm A write flag.
 * @return The new state of RTC_FLAG (SET or RESET).
 */
FlagStatus RTC_GetFlagStatus(uint32_t RTC_FLAG)
{
    FlagStatus bitstatus = RESET;
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RTC_GET_FLAG(RTC_FLAG));
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
 * @brief  Clears the RTC's pending flags.
 * @param RTC_FLAG specifies the RTC flag to clear.
 *   This parameter can be any combination of the following values:.
 *     @arg RTC_FLAG_TAMP3F: Tamper 3 event flag.
 *     @arg RTC_FLAG_TAMP2F: Tamper 2 event flag.
 *     @arg RTC_FLAG_TAMP1F: Tamper 1 event flag.
 *     @arg RTC_FLAG_TISOVF Time Stamp Overflow flag.
 *     @arg RTC_FLAG_TISF Time Stamp event flag.
 *     @arg RTC_FLAG_WTF WakeUp Timer flag.
 *     @arg RTC_FLAG_ALBF Alarm B flag.
 *     @arg RTC_FLAG_ALAF Alarm A flag.
 *     @arg RTC_FLAG_RSYF Registers Synchronized flag.
 */
void RTC_ClrFlag(uint32_t RTC_FLAG)
{
    /* Check the parameters */
    assert_param(IS_RTC_CLEAR_FLAG(RTC_FLAG));
    /* Clear the Flags in the RTC_INITSTS register */
    RTC->INITSTS = (uint32_t)(
        (uint32_t)(~((RTC_FLAG | RTC_INITSTS_INITM) & 0x0001FFFF) | (uint32_t)(RTC->INITSTS & RTC_INITSTS_INITM)));
}

/**
 * @brief  Checks whether the specified RTC interrupt has occurred or not.
 * @param RTC_INT specifies the RTC interrupt source to check.
 *   This parameter can be one of the following values:
 *     @arg RTC_INT_TS Time Stamp interrupt.
 *     @arg RTC_INT_WUT WakeUp Timer interrupt.
 *     @arg RTC_INT_ALRB Alarm B interrupt.
 *     @arg RTC_INT_ALRA Alarm A interrupt.
 * @return The new state of RTC_INT (SET or RESET).
 */
INTStatus RTC_GetITStatus(uint32_t RTC_INT)
{
    INTStatus bitstatus  = RESET;
    uint32_t tmpregister = 0, enablestatus = 0;
    uint8_t tamperEnable = 0;
    /* Check the parameters */
    assert_param(IS_RTC_GET_INT(RTC_INT));
    /* Get the Interrupt enable Status */
    if ((RTC_INT == RTC_INT_TAMP1) || (RTC_INT == RTC_INT_TAMP2)|| (RTC_INT == RTC_INT_TAMP3))
    {
       tamperEnable = ((RTC->TMPCFG & 0x00ff0000)>>16);
       if (tamperEnable > 0)
       {
          enablestatus = SET;
       }
    }
    else
    {
       enablestatus = (uint32_t)((RTC->CTRL & RTC_INT));
    }
    /* Get the Interrupt pending bit */
    tmpregister = (uint32_t)((RTC->INITSTS & (uint32_t)(RTC_INT >> 4)));
    /* Get the status of the Interrupt */
    if ((enablestatus != (uint32_t)RESET) && ((tmpregister & 0x0000FFFF) != (uint32_t)RESET))
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
 * @brief  Clears the RTC's interrupt pending bits.
 * @param RTC_INT specifies the RTC interrupt pending bit to clear.
 *   This parameter can be any combination of the following values:
 *     @arg RTC_INT_TS Time Stamp interrupt
 *     @arg RTC_INT_WUT WakeUp Timer interrupt
 *     @arg RTC_INT_ALRB Alarm B interrupt
 *     @arg RTC_INT_ALRA Alarm A interrupt
 */
void RTC_ClrIntPendingBit(uint32_t RTC_INT)
{
    uint32_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_RTC_CLEAR_INT(RTC_INT));
    /* Get the RTC_INITSTS Interrupt pending bits mask */
    tmpregister = (uint32_t)(RTC_INT >> 4);
    /* Clear the interrupt pending bits in the RTC_INITSTS register */
    RTC->INITSTS = (uint32_t)(
        (uint32_t)(~((tmpregister | RTC_INITSTS_INITM) & 0x0000FFFF) | (uint32_t)(RTC->INITSTS & RTC_INITSTS_INITM)));
}

/**
 * @}
 */

/**
 * @brief  Converts a 2 digit decimal to BCD format.
 * @param Value Byte to be converted.
 * @return Converted byte
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
 * @param Value BCD value to be converted.
 * @return Converted word
 */
static uint8_t RTC_Bcd2ToByte(uint8_t Value)
{
    uint8_t tmp = 0;
    tmp = ((uint8_t)(Value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
    return (tmp + (Value & (uint8_t)0x0F));
}
/**
 * @brief  Enable wakeup tsc functionand wakeup by the set time
 * @param  count wakeup time.
 */
void RTC_EnableWakeUpTsc(uint32_t count)
{
    // Wait until bit RTC_TSCWKUPCTRL_WKUPOFF is 1
    while (!(RTC->TSCWKUPCTRL & RTC_TSCWKUPCTRL_WKUPOFF))
    {
    }
    // enter config  wakeup cnt mode
    RTC->TSCWKUPCTRL = RTC_TSCWKUPCTRL_WKUPCNF;
    // config tsc wakeup cnt ,tsc wakeup module counting cycle = WAKUPCNT * LSE/LSI
    RTC->TSCWKUPCNT = count;
    // exit config wakeup cnt mode
    RTC->TSCWKUPCTRL &= ~(RTC_TSCWKUPCTRL_WKUPCNF);
    while (!(RTC->TSCWKUPCTRL & RTC_TSCWKUPCTRL_WKUPOFF))
    {
    }
    // TSC wakeup enable
    RTC->TSCWKUPCTRL = RTC_TSCWKUPCTRL_WKUPEN;
}

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
  * @param  RTC_Tamper: Selected tamper pin.
  *   This parameter can be any combination of the following values:
  *     @arg RTC_Tamper_1: Select Tamper 1.
  *     @arg RTC_Tamper_2: Select Tamper 2.
  *     @arg RTC_Tamper_3: Select Tamper 3.
  * @param  RTC_TamperTrigger: Specifies the trigger on the tamper pin that
  *                            stimulates tamper event.
  *   This parameter can be one of the following values:
  *     @arg RTC_TamperTrigger_RisingEdge: Rising Edge of the tamper pin causes tamper event.
  *     @arg RTC_TamperTrigger_FallingEdge: Falling Edge of the tamper pin causes tamper event.
  *     @arg RTC_TamperTrigger_LowLevel: Low Level of the tamper pin causes tamper event.
  *     @arg RTC_TamperTrigger_HighLevel: High Level of the tamper pin causes tamper event.
  * @retval None
  */
void RTC_TamperTriggerConfig(uint32_t RTC_Tamper, uint32_t RTC_TamperTrigger)
{
    /* Check the parameters */
    assert_param(IS_RTC_TAMPER(RTC_Tamper));
    assert_param(IS_RTC_TAMPER_TRIGGER(RTC_TamperTrigger));
    if (RTC_Tamper == RTC_TAMPER_3)
    {
       RTC_TamperTrigger <<= 5;
    }
    if (RTC_Tamper == RTC_TAMPER_2)
    {
       RTC_TamperTrigger <<= 3;
    }
    /* Configure the RTC_TAMPCR register */
    RTC->TMPCFG |= (uint32_t)(RTC_Tamper | RTC_TamperTrigger);
}

/**
  * @brief  Enables or Disables the Tamper detection.
  * @param  RTC_Tamper: Selected tamper pin.
  *   This parameter can be any combination of the following values:
  *     @arg RTC_TAMPER_1: Select Tamper 1.
  *     @arg RTC_TAMPER_2: Select Tamper 2.
  *     @arg RTC_TAMPER_3: Select Tamper 3.
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
       /* Enable the selected Tamper pin */
       RTC->TMPCFG |= (uint32_t)RTC_Tamper;
    }
    else
    {
       /* Disable the selected Tamper pin */
       RTC->TMPCFG &= (uint32_t)~RTC_Tamper;
    }
}

/**
  * @brief  Configures the Tampers Filter.
  * @param  RTC_TamperFilter: Specifies the tampers filter.
  *   This parameter can be one of the following values:
  *     @arg RTC_TamperFilter_Disable: Tamper filter is disabled.
  *     @arg RTC_TamperFilter_2Sample: Tamper is activated after 2 consecutive
  *                                    samples at the active level.
  *     @arg RTC_TamperFilter_4Sample: Tamper is activated after 4 consecutive
  *                                    samples at the active level.
  *     @arg RTC_TamperFilter_8Sample: Tamper is activated after 8 consecutive
  *                                    samples at the active level.
  * @retval None
  */
void RTC_TamperFilterConfig(uint32_t RTC_TamperFilter)
{
    /* Check the parameters */
    assert_param(IS_RTC_TAMPER_FILTER(RTC_TamperFilter));
    /* Clear TAMPFLT[1:0] bits in the RTC_TAMPCR register */
    RTC->TMPCFG &= (uint32_t)~(RTC_TMPCFG_TPFLT);
    /* Configure the RTC_TAMPCR register */
    RTC->TMPCFG |= (uint32_t)RTC_TamperFilter;
}

/**
  * @brief  Configures the Tampers Sampling Frequency.
  * @param  RTC_TamperSamplingFreq: Specifies the tampers Sampling Frequency.
  *   This parameter can be one of the following values:
  *     @arg RTC_TamperSamplingFreq_RTCCLK_Div32768: Each of the tamper inputs are sampled
  *                                           with a frequency =  RTCCLK / 32768
  *     @arg RTC_TamperSamplingFreq_RTCCLK_Div16384: Each of the tamper inputs are sampled
  *                                           with a frequency =  RTCCLK / 16384
  *     @arg RTC_TamperSamplingFreq_RTCCLK_Div8192: Each of the tamper inputs are sampled
  *                                           with a frequency =  RTCCLK / 8192
  *     @arg RTC_TamperSamplingFreq_RTCCLK_Div4096: Each of the tamper inputs are sampled
  *                                           with a frequency =  RTCCLK / 4096
  *     @arg RTC_TamperSamplingFreq_RTCCLK_Div2048: Each of the tamper inputs are sampled
  *                                           with a frequency =  RTCCLK / 2048
  *     @arg RTC_TamperSamplingFreq_RTCCLK_Div1024: Each of the tamper inputs are sampled
  *                                           with a frequency =  RTCCLK / 1024
  *     @arg RTC_TamperSamplingFreq_RTCCLK_Div512: Each of the tamper inputs are sampled
  *                                           with a frequency =  RTCCLK / 512
  *     @arg RTC_TamperSamplingFreq_RTCCLK_Div256: Each of the tamper inputs are sampled
  *                                           with a frequency =  RTCCLK / 256
  * @retval None
  */
void RTC_TamperSamplingFreqConfig(uint32_t RTC_TamperSamplingFreq)
{
    /* Check the parameters */
    assert_param(IS_RTC_TAMPER_SAMPLING_FREQ(RTC_TamperSamplingFreq));
    /* Clear TAMPFREQ[2:0] bits in the RTC_TAMPCR register */
    RTC->TMPCFG &= (uint32_t)~(RTC_TAMPCR_TAMPFREQ);
    /* Configure the RTC_TAMPCR register */
    RTC->TMPCFG |= (uint32_t)RTC_TamperSamplingFreq;
}

/**
  * @brief  Configures the Tampers Pins input Precharge Duration.
  * @param  RTC_TamperPrechargeDuration: Specifies the Tampers Pins input
  *         Precharge Duration.
  *   This parameter can be one of the following values:
  *     @arg RTC_TamperPrechargeDuration_1RTCCLK: Tamper pins are pre-charged before sampling during 1 RTCCLK cycle.
  *     @arg RTC_TamperPrechargeDuration_2RTCCLK: Tamper pins are pre-charged before sampling during 2 RTCCLK cycle.
  *     @arg RTC_TamperPrechargeDuration_4RTCCLK: Tamper pins are pre-charged before sampling during 4 RTCCLK cycle.
  *     @arg RTC_TamperPrechargeDuration_8RTCCLK: Tamper pins are pre-charged before sampling during 8 RTCCLK cycle.
  * @retval None
  */
void RTC_TamperPinsPrechargeDuration(uint32_t RTC_TamperPrechargeDuration)
{
    /* Check the parameters */
    assert_param(IS_RTC_TAMPER_PRECHARGE_DURATION(RTC_TamperPrechargeDuration));
    /* Clear TAMPPRCH[1:0] bits in the RTC_TAMPCR register */
    RTC->TMPCFG &= (uint32_t)~(RTC_TMPCFG_TPPRCH);
    /* Configure the RTC_TAMPCR register */
    RTC->TMPCFG |= (uint32_t)RTC_TamperPrechargeDuration;
}

/**
  * @brief  Enables or Disables the TimeStamp on Tamper Detection Event.
  * @note   The timestamp is valid even the TSEN bit in tamper control register
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
     RTC->TMPCFG |= (uint32_t)RTC_TMPCFG_TPTS;
  }
  else
  {
     /* Tamper detection does not cause a timestamp to be saved */
     RTC->TMPCFG &= (uint32_t)~RTC_TMPCFG_TPTS;
  }
}

/**
  * @brief  Enables or Disables the Precharge of Tamper pin.
  * @param  NewState: new state of tamper pull up.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_TamperPullUpCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
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
}

/**
  * @brief  Enables or Disables the TAMPTS.
  * @param  NewState: new state of TAMPTS.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_TamperTAMPTSCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
       /* Enable precharge of the selected Tamper pin */
       RTC->TMPCFG |= (uint32_t)RTC_TMPCFG_TPTS;
    }
    else
    {
       /* Disable precharge of the selected Tamper pin */
       RTC->TMPCFG &= (uint32_t)~RTC_TMPCFG_TPTS;
    }
}

/**
  * @brief  Enables or Disables the Tamper detection.
  * @param  RTC_Tamper: Selected tamper pin.
  *   This parameter can be any combination of the following values:
  *     @arg RTC_TAMPER1_INT: Select Tamper 1.
  *     @arg RTC_TAMPER2_INT: Select Tamper 2.
  *     @arg RTC_TAMPER3_INT: Select Tamper 3.
  * @param  NewState: new state of the tamper pin.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_TamperIECmd(uint32_t TAMPxIE, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RTC_TAMPER(TAMPxIE));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
     /* Enable the selected Tamper pin */
     RTC->TMPCFG |= (uint32_t)TAMPxIE;
  }
  else
  {
     /* Disable the selected Tamper pin */
     RTC->TMPCFG &= (uint32_t)~TAMPxIE;
  }
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
