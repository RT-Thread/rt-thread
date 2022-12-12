/**
  ******************************************************************************
  * @file    lib_rtc.h 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   RTC library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_RTC_H
#define __LIB_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
   
/* RTC Time struct */
typedef struct
{
  uint32_t Year;
  uint32_t Month;
  uint32_t Date;
  uint32_t WeekDay;
  uint32_t Hours;
  uint32_t Minutes;
  uint32_t Seconds;
  uint32_t SubSeconds;
} RTC_TimeTypeDef;

/* RTC Alarm Time struct */
typedef struct
{
  uint32_t AlarmHours;
  uint32_t AlarmMinutes;
  uint32_t AlarmSeconds;
  uint32_t AlarmSubSeconds;
}RTC_AlarmTypeDef;

#define RTC_ACCURATE     0
#define RTC_INACCURATE   1
#define IS_RTC_ACCURATESEL(__ACCURATESEL__)  (((__ACCURATESEL__) == RTC_ACCURATE) ||\
                                              ((__ACCURATESEL__) == RTC_INACCURATE))

/**************  Bits definition for RTC_WKUCNT register     ******************/
#define RTC_WKUCNT_CNTSEL_0           (0x0U << RTC_WKUCNT_CNTSEL_Pos)
#define RTC_WKUCNT_CNTSEL_1           (0x1U << RTC_WKUCNT_CNTSEL_Pos)
#define RTC_WKUCNT_CNTSEL_2           (0x2U << RTC_WKUCNT_CNTSEL_Pos)
#define RTC_WKUCNT_CNTSEL_3           (0x3U << RTC_WKUCNT_CNTSEL_Pos)

/**************  Bits definition for RTC_PSCA register       ******************/
#define RTC_PSCA_PSCA_0               (0x0U << RTC_PSCA_PSCA_Pos)
#define RTC_PSCA_PSCA_1               (0x1U << RTC_PSCA_PSCA_Pos)
//#define RTC_PSCA_PSCA_2               (0x2U << RTC_PSCA_PSCA_Pos)
//#define RTC_PSCA_PSCA_3               (0x3U << RTC_PSCA_PSCA_Pos)

/****************************** RTC Instances *********************************/
#define IS_RTC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == RTC)

//INT
#define RTC_INT_ALARM       RTC_INTSTS_INTSTS10
#define RTC_INT_CEILLE      RTC_INTSTS_INTSTS8
#define RTC_INT_WKUCNT      RTC_INTSTS_INTSTS6
#define RTC_INT_MIDNIGHT    RTC_INTSTS_INTSTS5
#define RTC_INT_WKUHOUR     RTC_INTSTS_INTSTS4
#define RTC_INT_WKUMIN      RTC_INTSTS_INTSTS3
#define RTC_INT_WKUSEC      RTC_INTSTS_INTSTS2
#define RTC_INT_TIMEILLE    RTC_INTSTS_INTSTS1
#define RTC_INT_ITVSITV     RTC_INTSTS_INTSTS0
#define RTC_INT_Msk        (0x57FUL)

//INTSTS
#define RTC_INTSTS_ALARM      RTC_INTSTS_INTSTS10 
#define RTC_INTSTS_CEILLE     RTC_INTSTS_INTSTS8  
#define RTC_INTSTS_WKUCNT     RTC_INTSTS_INTSTS6
#define RTC_INTSTS_MIDNIGHT   RTC_INTSTS_INTSTS5
#define RTC_INTSTS_WKUHOUR    RTC_INTSTS_INTSTS4
#define RTC_INTSTS_WKUMIN     RTC_INTSTS_INTSTS3
#define RTC_INTSTS_WKUSEC     RTC_INTSTS_INTSTS2
#define RTC_INTSTS_TIMEILLE   RTC_INTSTS_INTSTS1
#define RTC_INTSTS_ITVSITV   RTC_INTSTS_INTSTS0
#define RTC_INTSTS_Msk       (0x57FUL)

//CNTCLK
#define RTC_WKUCNT_RTCCLK     RTC_WKUCNT_CNTSEL_0 
#define RTC_WKUCNT_2048       RTC_WKUCNT_CNTSEL_1
#define RTC_WKUCNT_512        RTC_WKUCNT_CNTSEL_2
#define RTC_WKUCNT_128        RTC_WKUCNT_CNTSEL_3

//Prescaler
#define RTC_CLKDIV_1          RTC_PSCA_PSCA_0
#define RTC_CLKDIV_4          RTC_PSCA_PSCA_1

//PLLDIVSOUCE
#define RTC_PLLDIVSOURCE_PCLK   0
#define RTC_PLLDIVSOURCE_PLLL   (0x1U << RTC_CTL_RTCPLLCLKSEL_Pos)

//RTC_ITV
#define RTC_ITV_SEC         (0x80)
#define RTC_ITV_MIN         (1 << RTC_ITV_ITV_Pos)
#define RTC_ITV_HOUR        (2 << RTC_ITV_ITV_Pos)
#define RTC_ITV_DAY         (3 << RTC_ITV_ITV_Pos)
#define RTC_ITV_500MS       (4 << RTC_ITV_ITV_Pos)
#define RTC_ITV_250MS       (5 << RTC_ITV_ITV_Pos)
#define RTC_ITV_125MS       (6 << RTC_ITV_ITV_Pos)
#define RTC_ITV_62MS        (7 << RTC_ITV_ITV_Pos)
#define RTC_ITV_SITVSEC     (7 << RTC_ITV_ITV_Pos)
//RTC_SITV
#define RTC_SITV_EN         (1 << RTC_SITV_SITVEN_Pos) //Control Multi Second interval.1:enable; 0:disable.

/* Private macros ------------------------------------------------------------*/
#define IS_RTC_REGOP_STARTADDR(__STARTADDR__)  (((__STARTADDR__) & 0x3U) == 0U)
/* Year      0 ~ 99 */  
#define IS_RTC_TIME_YEAR(__YEAR__)  ((__YEAR__) < 0x9AU)
/* Month     1 ~ 12 */ 
#define IS_RTC_TIME_MONTH(__MONTH__)  (((__MONTH__) > 0x0U) && ((__MONTH__) < 0x13U))
/* Date      1 ~ 31 */ 
#define IS_RTC_TIME_DATE(__DATE__)  (((__DATE__) > 0x0U) && ((__DATE__) < 0x32U))
/* Weekday   0 ~ 6 */
#define IS_RTC_TIME_WEEKDAY(__WEEKDAY__)  ((__WEEKDAY__) < 0x7U)
/* Hours     0 ~ 23 */
#define IS_RTC_TIME_HOURS(__HOURS__)  ((__HOURS__) < 0x24U)
/* Minutes   0 ~ 59 */
#define IS_RTC_TIME_MINS(__MINS__)  ((__MINS__) < 0x5AU)
/* Seconds   0 ~ 59 */
#define IS_RTC_TIME_SECS(__SECS__)  ((__SECS__) < 0x5AU)
/* SubSeconds   0 ~ 0x999 */
#define IS_RTC_TIME_SubSECS(__SubSECS__)  ((__SubSECS__) < 0x1000U)

/* Alarm time   0 ~ 0x999 */
#define IS_RTC_ALARMTIME(__ALARMTIME__)  ((__ALARMTIME__) < 0x1E0000U)

#define IS_RTC_INT(__INT__)  ((((__INT__) & RTC_INT_Msk) != 0U) &&\
                              (((__INT__) & ~RTC_INT_Msk) == 0U))

#define IS_RTC_INTFLAGR(__INTFLAGR_)  (((__INTFLAGR_) == RTC_INTSTS_CEILLE)   ||\
                                       ((__INTFLAGR_) == RTC_INTSTS_WKUCNT)   ||\
                                       ((__INTFLAGR_) == RTC_INTSTS_MIDNIGHT) ||\
                                       ((__INTFLAGR_) == RTC_INTSTS_WKUHOUR)  ||\
                                       ((__INTFLAGR_) == RTC_INTSTS_WKUMIN)   ||\
                                       ((__INTFLAGR_) == RTC_INTSTS_WKUSEC)   ||\
                                       ((__INTFLAGR_) == RTC_INTSTS_ALARM)    ||\
                                       ((__INTFLAGR_) == RTC_INTSTS_TIMEILLE) ||\
                                       ((__INTFLAGR_) == RTC_INTSTS_ITVSITV))

#define IS_RTC_INTFLAGC(__INTFLAGC__)  ((((__INTFLAGC__) & RTC_INTSTS_Msk) != 0U) &&\
                                        (((__INTFLAGC__) & ~RTC_INTSTS_Msk) == 0U))

#define IS_RTC_WKUSEC_PERIOD(__PERIOD__)  ((__PERIOD__) < 0x41U)

#define IS_RTC_WKUMIN_PERIOD(__PERIOD__)  ((__PERIOD__) < 0x41U)

#define IS_RTC_WKUHOUR_PERIOD(__PERIOD__)  ((__PERIOD__) < 0x21U)

#define IS_RTC_WKUCNT_PERIOD(__PERIOD__)  ((__PERIOD__) < 0x1000001U)

#define IS_RTC_WKUCNT_CNTSEL(__CNTSEL__)  (((__CNTSEL__) == RTC_WKUCNT_RTCCLK) ||\
                                           ((__CNTSEL__) == RTC_WKUCNT_2048)   ||\
                                           ((__CNTSEL__) == RTC_WKUCNT_512)    ||\
                                           ((__CNTSEL__) == RTC_WKUCNT_128))

#define IS_RTC_CLKDIV(__CLKDIV__)  (((__CLKDIV__) == RTC_CLKDIV_1) ||\
                                    ((__CLKDIV__) == RTC_CLKDIV_4))

#define IS_RTC_PLLDIVSOURCE(__PLLDIVSOURCE__)  (((__PLLDIVSOURCE__) == RTC_PLLDIVSOURCE_PCLK) ||\
                                                ((__PLLDIVSOURCE__) == RTC_PLLDIVSOURCE_PLLL))

#define IS_RTC_ITV(__ITV__)        (((__ITV__) == RTC_ITV_SEC)     ||\
                                    ((__ITV__) == RTC_ITV_MIN)     ||\
                                    ((__ITV__) == RTC_ITV_HOUR)    ||\
                                    ((__ITV__) == RTC_ITV_DAY)    ||\
                                    ((__ITV__) == RTC_ITV_500MS)   ||\
                                    ((__ITV__) == RTC_ITV_250MS)   ||\
                                    ((__ITV__) == RTC_ITV_125MS)   ||\
                                    ((__ITV__) == RTC_ITV_62MS)   ||\
                                    ((__ITV__) == RTC_ITV_SITVSEC))

#define IS_RTC_SITV(__SITV__)  ((__SITV__) < 64U)

/* Exported Functions ------------------------------------------------------- */
/* RTC Exported Functions Group1: 
                                  Time functions -----------------------------*/
void RTC_SetTime(RTC_TimeTypeDef *sTime, uint32_t AccurateSel);
void RTC_GetTime(RTC_TimeTypeDef *gTime, uint32_t AccurateSel);
void RTC_SubSecondCmd(uint32_t NewState);
/* RTC Exported Functions Group2: 
                                  Alarms configuration functions -------------*/
void RTC_SetAlarm(RTC_AlarmTypeDef *RTC_AlarmStruct, uint32_t AccurateSel);
void RTC_GetAlarm(RTC_AlarmTypeDef *RTC_AlarmStruct, uint32_t AccurateSel);
void RTC_AlarmCmd(uint32_t NewState);
void RTC_AlarmAccurateCmd(uint32_t NewState);
/* RTC Exported Functions Group3: 
                                  Registers operation functions --------------*/
void RTC_WriteProtection(uint32_t NewState);
void RTC_WaitForSynchro(void);
void RTC_WriteRegisters(uint32_t StartAddr, const uint32_t *wBuffer, uint8_t Len);
void RTC_ReadRegisters(uint32_t StartAddr, uint32_t *rBuffer, uint8_t Len);
/* RTC Exported Functions Group4: 
                                  Interrupt functions ------------------------*/
void RTC_INTConfig(uint32_t INTMask, uint32_t NewState);
uint8_t RTC_GetINTStatus(uint32_t FlagMask); 
void RTC_ClearINTStatus(uint32_t FlagMask);

/* RTC Exported Functions Group5: 
                                  Wake-up functions --------------------------*/
void RTC_WKUSecondsConfig(uint8_t nPeriod);
void RTC_WKUMinutesConfig(uint8_t nPeriod);
void RTC_WKUHoursConfig(uint8_t nPeriod);
void RTC_WKUCounterConfig(uint32_t nClock,uint32_t CNTCLK);
void RTC_WAKE_ITV(uint8_t nType);
void RTC_WAKE_SITV(uint8_t nPeriod);
uint32_t RTC_GetWKUCounterValue(void);
/* RTC Exported Functions Group6: 
                                  MISC functions -----------------------------*/
void RTC_PrescalerConfig(uint32_t Prescaler);
void RTC_PLLDIVConfig(uint32_t DIVSource,uint32_t nfrequency);
void RTC_PLLDIVOutputCmd(uint8_t NewState);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_RTC_H */

/*********************************** END OF FILE ******************************/
