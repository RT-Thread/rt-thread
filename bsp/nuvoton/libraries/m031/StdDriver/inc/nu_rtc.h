/******************************************************************************
 * @file     nu_rtc.h
 * @version  V1.00
 * $Revision: 4 $
 * $Date: 18/06/07 2:32p $
 * @brief    M031 series Real Time Clock(RTC) driver header file
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#ifndef __NU_RTC_H__
#define __NU_RTC_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup RTC_Driver RTC Driver
  @{
*/

/** @addtogroup RTC_EXPORTED_CONSTANTS RTC Exported Constants
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/*  RTC Initial Keyword Constant Definitions                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_INIT_KEY            0xA5EB1357UL    /*!< RTC Initiation Key to make RTC leaving reset state \hideinitializer */
#define RTC_WRITE_KEY           0x0000A965UL    /*!< RTC Register Access Enable Key to enable RTC read/write accessible and kept 1024 RTC clock \hideinitializer */
/*---------------------------------------------------------------------------------------------------------*/
/*  RTC Frequency Compensation Definitions                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_INTEGER_32752       (0x0ul << RTC_FREQADJ_INTEGER_Pos )    /*!< RTC Frequency is 32752HZ \hideinitializer */
#define RTC_INTEGER_32753       (0x1ul << RTC_FREQADJ_INTEGER_Pos )    /*!< RTC Frequency is 32753HZ \hideinitializer */
#define RTC_INTEGER_32754       (0x2ul << RTC_FREQADJ_INTEGER_Pos )    /*!< RTC Frequency is 32754HZ \hideinitializer */
#define RTC_INTEGER_32755       (0x3ul << RTC_FREQADJ_INTEGER_Pos )    /*!< RTC Frequency is 32755HZ \hideinitializer */
#define RTC_INTEGER_32756       (0x4ul << RTC_FREQADJ_INTEGER_Pos )    /*!< RTC Frequency is 32756HZ \hideinitializer */
#define RTC_INTEGER_32757       (0x5ul << RTC_FREQADJ_INTEGER_Pos )    /*!< RTC Frequency is 32757HZ \hideinitializer */
#define RTC_INTEGER_32758       (0x6ul << RTC_FREQADJ_INTEGER_Pos )    /*!< RTC Frequency is 32758HZ \hideinitializer */
#define RTC_INTEGER_32759       (0x7ul << RTC_FREQADJ_INTEGER_Pos )    /*!< RTC Frequency is 32759HZ \hideinitializer */
#define RTC_INTEGER_32760       (0x8ul << RTC_FREQADJ_INTEGER_Pos )    /*!< RTC Frequency is 32760HZ \hideinitializer */
#define RTC_INTEGER_32761       (0x9ul << RTC_FREQADJ_INTEGER_Pos )    /*!< RTC Frequency is 32761HZ \hideinitializer */
#define RTC_INTEGER_32762       (0xaul << RTC_FREQADJ_INTEGER_Pos )    /*!< RTC Frequency is 32762HZ \hideinitializer */
#define RTC_INTEGER_32763       (0xbul << RTC_FREQADJ_INTEGER_Pos )    /*!< RTC Frequency is 32763HZ \hideinitializer */
#define RTC_INTEGER_32764       (0xcul << RTC_FREQADJ_INTEGER_Pos )    /*!< RTC Frequency is 32764HZ \hideinitializer */
#define RTC_INTEGER_32765       (0xdul << RTC_FREQADJ_INTEGER_Pos )    /*!< RTC Frequency is 32765HZ \hideinitializer */
#define RTC_INTEGER_32766       (0xeul << RTC_FREQADJ_INTEGER_Pos )    /*!< RTC Frequency is 32766HZ \hideinitializer */
#define RTC_INTEGER_32767       (0xful << RTC_FREQADJ_INTEGER_Pos )    /*!< RTC Frequency is 32767HZ \hideinitializer */
#define RTC_INTEGER_32768       (0x10ul << RTC_FREQADJ_INTEGER_Pos )   /*!< RTC Frequency is 32768HZ \hideinitializer */
#define RTC_INTEGER_32769       (0x11ul << RTC_FREQADJ_INTEGER_Pos )   /*!< RTC Frequency is 32769HZ \hideinitializer */
#define RTC_INTEGER_32770       (0x12ul << RTC_FREQADJ_INTEGER_Pos )   /*!< RTC Frequency is 32770HZ \hideinitializer */
#define RTC_INTEGER_32771       (0x13ul << RTC_FREQADJ_INTEGER_Pos )   /*!< RTC Frequency is 32771HZ \hideinitializer */
#define RTC_INTEGER_32772       (0x14ul << RTC_FREQADJ_INTEGER_Pos )   /*!< RTC Frequency is 32772HZ \hideinitializer */
#define RTC_INTEGER_32773       (0x15ul << RTC_FREQADJ_INTEGER_Pos )   /*!< RTC Frequency is 32773HZ \hideinitializer */
#define RTC_INTEGER_32774       (0x16ul << RTC_FREQADJ_INTEGER_Pos )   /*!< RTC Frequency is 32774HZ \hideinitializer */
#define RTC_INTEGER_32775       (0x17ul << RTC_FREQADJ_INTEGER_Pos )   /*!< RTC Frequency is 32775HZ \hideinitializer */
#define RTC_INTEGER_32776       (0x18ul << RTC_FREQADJ_INTEGER_Pos )   /*!< RTC Frequency is 32776HZ \hideinitializer */
#define RTC_INTEGER_32777       (0x19ul << RTC_FREQADJ_INTEGER_Pos )   /*!< RTC Frequency is 32777HZ \hideinitializer */
#define RTC_INTEGER_32778       (0x1aul << RTC_FREQADJ_INTEGER_Pos )   /*!< RTC Frequency is 32778HZ \hideinitializer */
#define RTC_INTEGER_32779       (0x1bul << RTC_FREQADJ_INTEGER_Pos )   /*!< RTC Frequency is 32779HZ \hideinitializer */
#define RTC_INTEGER_32780       (0x1cul << RTC_FREQADJ_INTEGER_Pos )   /*!< RTC Frequency is 32780HZ \hideinitializer */
#define RTC_INTEGER_32781       (0x1dul << RTC_FREQADJ_INTEGER_Pos )   /*!< RTC Frequency is 32781HZ \hideinitializer */
#define RTC_INTEGER_32782       (0x1eul << RTC_FREQADJ_INTEGER_Pos )   /*!< RTC Frequency is 32782HZ \hideinitializer */
#define RTC_INTEGER_32783       (0x1ful << RTC_FREQADJ_INTEGER_Pos )   /*!< RTC Frequency is 32783HZ \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  RTC Time Attribute Constant Definitions                                                                */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_CLOCK_12            0UL             /*!< RTC as 12-hour time scale with AM and PM indication \hideinitializer */
#define RTC_CLOCK_24            1UL             /*!< RTC as 24-hour time scale \hideinitializer */
#define RTC_AM                  1UL             /*!< RTC as AM indication \hideinitializer */
#define RTC_PM                  2UL             /*!< RTC as PM indication \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  RTC Tick Period Constant Definitions                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_TICK_1_SEC          0x0UL           /*!< RTC time tick period is 1 second \hideinitializer */
#define RTC_TICK_1_2_SEC        0x1UL           /*!< RTC time tick period is 1/2 second \hideinitializer */
#define RTC_TICK_1_4_SEC        0x2UL           /*!< RTC time tick period is 1/4 second \hideinitializer */
#define RTC_TICK_1_8_SEC        0x3UL           /*!< RTC time tick period is 1/8 second \hideinitializer */
#define RTC_TICK_1_16_SEC       0x4UL           /*!< RTC time tick period is 1/16 second \hideinitializer */
#define RTC_TICK_1_32_SEC       0x5UL           /*!< RTC time tick period is 1/32 second \hideinitializer */
#define RTC_TICK_1_64_SEC       0x6UL           /*!< RTC time tick period is 1/64 second \hideinitializer */
#define RTC_TICK_1_128_SEC      0x7UL           /*!< RTC time tick period is 1/128 second \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  RTC Day of Week Constant Definitions                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_SUNDAY              0x0UL           /*!< Day of the Week is Sunday \hideinitializer */
#define RTC_MONDAY              0x1UL           /*!< Day of the Week is Monday \hideinitializer */
#define RTC_TUESDAY             0x2UL           /*!< Day of the Week is Tuesday \hideinitializer */
#define RTC_WEDNESDAY           0x3UL           /*!< Day of the Week is Wednesday \hideinitializer */
#define RTC_THURSDAY            0x4UL           /*!< Day of the Week is Thursday \hideinitializer */
#define RTC_FRIDAY              0x5UL           /*!< Day of the Week is Friday \hideinitializer */
#define RTC_SATURDAY            0x6UL           /*!< Day of the Week is Saturday \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  RTC Miscellaneous Constant Definitions                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_YEAR2000            2000UL          /*!< RTC Reference for compute year data \hideinitializer */
#define RTC_FCR_REFERENCE       32761UL           /*!< RTC Reference for frequency compensation \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  RTC Clock Source Constant Definitions                                                                  */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_CLKSRC_LXT          0x0UL           /*!< Clock Source from LXT \hideinitializer */
#define RTC_CLKSRC_LIRC         0x1UL           /*!< Clock Source from LIRC \hideinitializer */

/*@}*/ /* end of group RTC_EXPORTED_CONSTANTS */


/** @addtogroup RTC_EXPORTED_STRUCTS RTC Exported Structs
  @{
*/
/**
  * @details    RTC define Time Data Struct
  */
typedef struct
{
    uint32_t u32Year;           /*!< Year value */
    uint32_t u32Month;          /*!< Month value */
    uint32_t u32Day;            /*!< Day value */
    uint32_t u32DayOfWeek;      /*!< Day of week value */
    uint32_t u32Hour;           /*!< Hour value */
    uint32_t u32Minute;         /*!< Minute value */
    uint32_t u32Second;         /*!< Second value */
    uint32_t u32TimeScale;      /*!< 12-Hour, 24-Hour */
    uint32_t u32AmPm;           /*!< Only Time Scale select 12-hr used */
} S_RTC_TIME_DATA_T;

/*@}*/ /* end of group RTC_EXPORTED_STRUCTS */


/** @addtogroup RTC_EXPORTED_FUNCTIONS RTC Exported Functions
  @{
*/

/**
  * @brief      Indicate is Leap Year or not
  *
  * @param      None
  *
  * @retval     0   This year is not a leap year
  * @retval     1   This year is a leap year
  *
  * @details    According to current date, return this year is leap year or not.
  * \hideinitializer
  */
#define RTC_IS_LEAP_YEAR()              (RTC->LEAPYEAR & RTC_LEAPYEAR_LEAPYEAR_Msk ? 1:0)

/**
  * @brief      Clear RTC Alarm Interrupt Flag
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to clear RTC alarm interrupt flag.
  * \hideinitializer
  */
#define RTC_CLEAR_ALARM_INT_FLAG()   (RTC->INTSTS = RTC_INTSTS_ALMIF_Msk)

/**
  * @brief      Clear RTC Tick Interrupt Flag
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to clear RTC tick interrupt flag.
  * \hideinitializer
  */
#define RTC_CLEAR_TICK_INT_FLAG()    (RTC->INTSTS = RTC_INTSTS_TICKIF_Msk)

/**
  * @brief      Get RTC Alarm Interrupt Flag
  *
  * @param      None
  *
  * @retval     0   RTC alarm interrupt did not occur
  * @retval     1   RTC alarm interrupt occurred
  *
  * @details    This macro indicates RTC alarm interrupt occurred or not.
  * \hideinitializer
  */
#define RTC_GET_ALARM_INT_FLAG()         ((RTC->INTSTS & RTC_INTSTS_ALMIF_Msk)? 1:0)

/**
  * @brief      Get RTC Time Tick Interrupt Flag
  *
  * @param      None
  *
  * @retval     0   RTC time tick interrupt did not occur
  * @retval     1   RTC time tick interrupt occurred
  *
  * @details    This macro indicates RTC time tick interrupt occurred or not.
  * \hideinitializer
  */
#define RTC_GET_TICK_INT_FLAG()          ((RTC->INTSTS & RTC_INTSTS_TICKIF_Msk)? 1:0)

/**
  * @brief      Enable RTC Tick Wake-up Function
  *
 * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to enable RTC tick interrupt wake-up function.
  * \hideinitializer
  */
#define RTC_ENABLE_TICK_WAKEUP()         ((RTC->INTEN |= RTC_INTEN_TICKIEN_Msk))

/**
  * @brief      Disable RTC Tick Wake-up Function
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to disable RTC tick interrupt wake-up function.
  * \hideinitializer
  */
#define RTC_DISABLE_TICK_WAKEUP()        ((RTC->INTEN &= ~RTC_INTEN_TICKIEN_Msk));

/**
 * @brief      Enable RTC Alarm Wake-up Function
 *
 * @param      None
 *
 * @return     None
 *
 * @details    This macro is used to enable RTC Alarm interrupt wake-up function.
 * \hideinitializer
 */
#define RTC_ENABLE_ALARM_WAKEUP()         ((RTC->INTEN |= RTC_INTEN_ALMIEN_Msk))

/**
  * @brief      Disable RTC Alarm Wake-up Function
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to disable RTC Alarm interrupt wake-up function.
  * \hideinitializer
  */
#define RTC_DISABLE_ALARM_WAKEUP()        ((RTC->INTEN &= ~RTC_INTEN_ALMIEN_Msk));

/**
  * @brief      Select RTC Clock Source
  *
  * @param[in]  u32ClkSrc      Specify the clock source. It consists of:
  *                                     - \ref RTC_CLKSRC_LXT   : Clock source from LXT
  *                                     - \ref RTC_CLKSRC_LIRC  : Clock source from LIRC
  * @return     None
  *
  * @details    This macro is used to select RTC clock source.
  * \hideinitializer
  */
#define RTC_CLKSRCSEL(u32ClkSrc)        ((RTC->LXTCTL &= ~RTC_LXTCTL_C32KS_Msk) | u32ClkSrc);

void RTC_Open(S_RTC_TIME_DATA_T *psPt);
void RTC_Close(void);
void RTC_32KCalibration(int32_t i32FrequencyX10000);
void RTC_GetDateAndTime(S_RTC_TIME_DATA_T *psPt);
void RTC_GetAlarmDateAndTime(S_RTC_TIME_DATA_T *psPt);
void RTC_SetDateAndTime(S_RTC_TIME_DATA_T *psPt);
void RTC_SetAlarmDateAndTime(S_RTC_TIME_DATA_T *psPt);
void RTC_SetDate(uint32_t u32Year, uint32_t u32Month, uint32_t u32Day, uint32_t u32DayOfWeek);
void RTC_SetTime(uint32_t u32Hour, uint32_t u32Minute, uint32_t u32Second, uint32_t u32TimeMode, uint32_t u32AmPm);
void RTC_SetAlarmDate(uint32_t u32Year, uint32_t u32Month, uint32_t u32Day);
void RTC_SetAlarmTime(uint32_t u32Hour, uint32_t u32Minute, uint32_t u32Second, uint32_t u32TimeMode, uint32_t u32AmPm);
void RTC_SetAlarmDateMask(uint8_t u8IsTenYMsk, uint8_t u8IsYMsk, uint8_t u8IsTenMMsk, uint8_t u8IsMMsk, uint8_t u8IsTenDMsk, uint8_t u8IsDMsk);
void RTC_SetAlarmTimeMask(uint8_t u8IsTenHMsk, uint8_t u8IsHMsk, uint8_t u8IsTenMMsk, uint8_t u8IsMMsk, uint8_t u8IsTenSMsk, uint8_t u8IsSMsk);
uint32_t RTC_GetDayOfWeek(void);
void RTC_SetTickPeriod(uint32_t u32TickSelection);
void RTC_EnableInt(uint32_t u32IntFlagMask);
void RTC_DisableInt(uint32_t u32IntFlagMask);

/*@}*/ /* end of group RTC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group RTC_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_RTC_H__ */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
