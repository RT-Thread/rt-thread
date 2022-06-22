/**************************************************************************//**
 * @file     nu_rtc.h
 * @version  V3.00
 * @brief    M480 series RTC driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
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
/*  RTC Time Attribute Constant Definitions                                                                */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_CLOCK_12            0UL               /*!< RTC as 12-hour time scale with AM and PM indication \hideinitializer */
#define RTC_CLOCK_24            1UL               /*!< RTC as 24-hour time scale \hideinitializer */
#define RTC_AM                  1UL               /*!< RTC as AM indication \hideinitializer */
#define RTC_PM                  2UL               /*!< RTC as PM indication \hideinitializer */

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
/*  RTC Miscellaneous Constant Definitions                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_WAIT_COUNT          0xFFFFFFFFUL      /*!< Initial Time-out Value \hideinitializer */
#define RTC_YEAR2000            2000UL            /*!< RTC Reference for compute year data \hideinitializer */
#define RTC_FCR_REFERENCE       32761UL           /*!< RTC Reference for frequency compensation \hideinitializer */


#define RTC_TAMPER0_SELECT (0x1ul << 0)     /*!< Select Tamper 0 \hideinitializer */
#define RTC_TAMPER1_SELECT (0x1ul << 1)     /*!< Select Tamper 1 \hideinitializer */
#define RTC_TAMPER2_SELECT (0x1ul << 2)     /*!< Select Tamper 2 \hideinitializer */
#define RTC_TAMPER3_SELECT (0x1ul << 3)     /*!< Select Tamper 3 \hideinitializer */
#define RTC_TAMPER4_SELECT (0x1ul << 4)     /*!< Select Tamper 4 \hideinitializer */
#define RTC_TAMPER5_SELECT (0x1ul << 5)     /*!< Select Tamper 5 \hideinitializer */
#define MAX_TAMPER_PIN_NUM 6ul              /*!< Tamper Pin number \hideinitializer */

#define RTC_TAMPER_HIGH_LEVEL_DETECT 1ul    /*!< Tamper pin detect voltage level is high \hideinitializer */
#define RTC_TAMPER_LOW_LEVEL_DETECT  0ul    /*!< Tamper pin detect voltage level is low  \hideinitializer */

#define RTC_TAMPER_DEBOUNCE_ENABLE   1ul    /*!< Enable RTC tamper pin de-bounce function \hideinitializer */
#define RTC_TAMPER_DEBOUNCE_DISABLE  0ul    /*!< Disable RTC tamper pin de-bounce function \hideinitializer */

#define RTC_PAIR0_SELECT (0x1ul << 0)       /*!< Select Pair 0 \hideinitializer */
#define RTC_PAIR1_SELECT (0x1ul << 1)       /*!< Select Pair 1 \hideinitializer */
#define RTC_PAIR2_SELECT (0x1ul << 2)       /*!< Select Pair 2 \hideinitializer */
#define MAX_PAIR_NUM     3ul                /*!< Pair number \hideinitializer */

#define RTC_2POW10_CLK  (0x0 << RTC_TAMPCTL_DYNRATE_Pos) /*!< 1024 RTC clock cycles \hideinitializer */
#define RTC_2POW11_CLK  (0x1 << RTC_TAMPCTL_DYNRATE_Pos) /*!< 1024 x 2 RTC clock cycles \hideinitializer */
#define RTC_2POW12_CLK  (0x2 << RTC_TAMPCTL_DYNRATE_Pos) /*!< 1024 x 4 RTC clock cycles \hideinitializer */
#define RTC_2POW13_CLK  (0x3 << RTC_TAMPCTL_DYNRATE_Pos) /*!< 1024 x 6 RTC clock cycles \hideinitializer */
#define RTC_2POW14_CLK  (0x4 << RTC_TAMPCTL_DYNRATE_Pos) /*!< 1024 x 8 RTC clock cycles \hideinitializer */
#define RTC_2POW15_CLK  (0x5 << RTC_TAMPCTL_DYNRATE_Pos) /*!< 1024 x 16 RTC clock cycles \hideinitializer */
#define RTC_2POW16_CLK  (0x6 << RTC_TAMPCTL_DYNRATE_Pos) /*!< 1024 x 32 RTC clock cycles \hideinitializer */
#define RTC_2POW17_CLK  (0x7 << RTC_TAMPCTL_DYNRATE_Pos) /*!< 1024 x 64 RTC clock cycles \hideinitializer */

#define REF_RANDOM_PATTERN    0x0 /*!< The new reference pattern is generated by random number generator when the reference pattern run out \hideinitializer */
#define REF_PREVIOUS_PATTERN  0x1 /*!< The new reference pattern is repeated previous random value when the reference pattern run out \hideinitializer */
#define REF_SEED              0x3 /*!< The new reference pattern is repeated from SEED (RTC_TAMPSEED[31:0]) when the reference pattern run out \hideinitializer */

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
#define RTC_CLEAR_ALARM_INT_FLAG()      (RTC->INTSTS = RTC_INTSTS_ALMIF_Msk)

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
#define RTC_CLEAR_TICK_INT_FLAG()       (RTC->INTSTS = RTC_INTSTS_TICKIF_Msk)

/**
  * @brief      Clear RTC Tamper Interrupt Flag
  *
  * @param      u32TamperFlag   Tamper interrupt flag. It consists of:    \n
  *                             - \ref RTC_INTSTS_TAMP0IF_Msk    \n
  *                             - \ref RTC_INTSTS_TAMP1IF_Msk    \n
  *                             - \ref RTC_INTSTS_TAMP2IF_Msk    \n
  *                             - \ref RTC_INTSTS_TAMP3IF_Msk    \n
  *                             - \ref RTC_INTSTS_TAMP4IF_Msk    \n
  *                             - \ref RTC_INTSTS_TAMP5IF_Msk
  *
  * @return     None
  *
  * @details    This macro is used to clear RTC snooper pin interrupt flag.
  * \hideinitializer
  */
#define RTC_CLEAR_TAMPER_INT_FLAG(u32TamperFlag)    (RTC->INTSTS = (u32TamperFlag))

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
#define RTC_GET_ALARM_INT_FLAG()        ((RTC->INTSTS & RTC_INTSTS_ALMIF_Msk)? 1:0)

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
#define RTC_GET_TICK_INT_FLAG()         ((RTC->INTSTS & RTC_INTSTS_TICKIF_Msk)? 1:0)

/**
  * @brief      Get RTC Tamper Interrupt Flag
  *
  * @param      None
  *
  * @retval     0   RTC snooper pin interrupt did not occur
  * @retval     1   RTC snooper pin interrupt occurred
  *
  * @details    This macro indicates RTC snooper pin interrupt occurred or not.
  * \hideinitializer
  */
#define RTC_GET_TAMPER_INT_FLAG()      ((RTC->INTSTS & (0x3F00))? 1:0)

/**
  * @brief      Get RTC TAMPER Interrupt Status
  *
  * @param      None
  *
  * @retval     RTC_INTSTS_TAMP0IF_Msk    Tamper 0 interrupt flag is generated
  * @retval     RTC_INTSTS_TAMP1IF_Msk    Tamper 1 interrupt flag is generated
  * @retval     RTC_INTSTS_TAMP2IF_Msk    Tamper 2 interrupt flag is generated
  * @retval     RTC_INTSTS_TAMP3IF_Msk    Tamper 3 interrupt flag is generated
  * @retval     RTC_INTSTS_TAMP4IF_Msk    Tamper 4 interrupt flag is generated
  * @retval     RTC_INTSTS_TAMP5IF_Msk    Tamper 5 interrupt flag is generated
  *
  * @details    This macro indicates RTC snooper pin interrupt occurred or not.
  * \hideinitializer
  */
#define RTC_GET_TAMPER_INT_STATUS()      ((RTC->INTSTS & (0x3F00)))

/**
  * @brief      Read Spare Register
  *
  * @param[in]  u32RegNum   The spare register number, 0~19.
  *
  * @return     Spare register content
  *
  * @details    Read the specify spare register content.
  * @note       The returned value is valid only when SPRRDY(SPRCTL[7] SPR Register Ready) bit is set. \n
  *             And its controlled by RTC Access Enable Register.
  * \hideinitializer
  */
#define RTC_READ_SPARE_REGISTER(u32RegNum)                  (RTC->SPR[(u32RegNum)])

/**
  * @brief      Write Spare Register
  *
  * @param[in]  u32RegNum    The spare register number, 0~19.
  * @param[in]  u32RegValue  The spare register value.
  *
  * @return     None
  *
  * @details    Write specify data to spare register.
  * @note       This macro is effect only when SPRRDY(SPRCTL[7] SPR Register Ready) bit is set. \n
  *             And its controlled by RTC Access Enable Register(RTC_RWEN).
  * \hideinitializer
  */
#define RTC_WRITE_SPARE_REGISTER(u32RegNum, u32RegValue)    (RTC->SPR[(u32RegNum)] = (u32RegValue))

/* Declare these inline functions here to avoid MISRA C 2004 rule 8.1 error */
__STATIC_INLINE void RTC_WaitAccessEnable(void);

/**
  * @brief      Wait RTC Access Enable
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This function is used to enable the maximum RTC read/write accessible time.
  */
__STATIC_INLINE void RTC_WaitAccessEnable(void)
{
    while((RTC->RWEN & RTC_RWEN_RTCBUSY_Msk) == RTC_RWEN_RTCBUSY_Msk)
    {
    }

    if(!(SYS->CSERVER & 0x1))
    {
        /* To wait RWENF bit is cleared and enable RWENF bit (Access Enable bit) again */
        RTC->RWEN = RTC_WRITE_KEY;
    }

    /* To wait RWENF bit is set and user can access the protected-register of RTC from now on */
    while((RTC->RWEN & RTC_RWEN_RWENF_Msk) == (uint32_t)0x0)
    {
    }
}

void RTC_Open(S_RTC_TIME_DATA_T *sPt);
void RTC_Close(void);
void RTC_32KCalibration(int32_t i32FrequencyX10000);
void RTC_GetDateAndTime(S_RTC_TIME_DATA_T *sPt);
void RTC_GetAlarmDateAndTime(S_RTC_TIME_DATA_T *sPt);
void RTC_SetDateAndTime(S_RTC_TIME_DATA_T *sPt);
void RTC_SetAlarmDateAndTime(S_RTC_TIME_DATA_T *sPt);
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
void RTC_EnableSpareAccess(void);
void RTC_DisableSpareRegister(void);
void RTC_StaticTamperEnable(uint32_t u32TamperSelect, uint32_t u32DetecLevel, uint32_t u32DebounceEn);
void RTC_StaticTamperDisable(uint32_t u32TamperSelect);
void RTC_DynamicTamperEnable(uint32_t u32PairSel, uint32_t u32DebounceEn, uint32_t u32Pair1Source, uint32_t u32Pair2Source);
void RTC_DynamicTamperDisable(uint32_t u32PairSel);
void RTC_DynamicTamperConfig(uint32_t u32ChangeRate, uint32_t u32SeedReload, uint32_t u32RefPattern, uint32_t u32Seed);

/*@}*/ /* end of group RTC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group RTC_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_RTC_H__ */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
