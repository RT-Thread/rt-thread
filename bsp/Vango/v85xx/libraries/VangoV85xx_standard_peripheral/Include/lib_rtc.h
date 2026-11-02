/**
  ******************************************************************************
  * @file    lib_rtc.h 
  * @author  Application Team
  * @version V4.5.0
  * @date    2019-05-14
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
} RTC_TimeTypeDef;
  
//INT
#define RTC_INT_CEILLE      RTC_INTEN_INTEN8
#define RTC_INT_ACDONE      RTC_INTEN_INTEN7
#define RTC_INT_WKUCNT      RTC_INTEN_INTEN6
#define RTC_INT_MIDNIGHT    RTC_INTEN_INTEN5
#define RTC_INT_WKUHOUR     RTC_INTEN_INTEN4
#define RTC_INT_WKUMIN      RTC_INTEN_INTEN3
#define RTC_INT_WKUSEC      RTC_INTEN_INTEN2
#define RTC_INT_TIMEILLE    RTC_INTEN_INTEN1
#define RTC_INT_Msk        (0x1FEUL)

//INTSTS
#define RTC_INTSTS_CEILLE     RTC_INTSTS_INTSTS8  
#define RTC_INTSTS_ACDONE     RTC_INTSTS_INTSTS7
#define RTC_INTSTS_WKUCNT     RTC_INTSTS_INTSTS6
#define RTC_INTSTS_MIDNIGHT   RTC_INTSTS_INTSTS5
#define RTC_INTSTS_WKUHOUR    RTC_INTSTS_INTSTS4
#define RTC_INTSTS_WKUMIN     RTC_INTSTS_INTSTS3
#define RTC_INTSTS_WKUSEC     RTC_INTSTS_INTSTS2
#define RTC_INTSTS_TIMEILLE   RTC_INTSTS_INTSTS1
#define RTC_INTSTS_Msk       (0x1FEUL)

/* RTC AutoCal struct */
typedef struct
{
  uint32_t Period;
  uint32_t ATDelay;
  uint32_t ATClockSource;
  uint32_t ADCSource;
} RTC_AutCalType;
//ATDelay
#define RTC_ATDELAY_15MS      RTC_ACCTRL_ACDEL_0
#define RTC_ATDELAY_31MS      RTC_ACCTRL_ACDEL_1
#define RTC_ATDELAY_62MS      RTC_ACCTRL_ACDEL_2
#define RTC_ATDELAY_125MS     RTC_ACCTRL_ACDEL_3
//ATClockSource
#define RTC_ATCS_DISABLE      RTC_ACCTRL_ACCLK_0
#define RTC_ATCS_SEC          RTC_ACCTRL_ACCLK_1
#define RTC_ATCS_MIN          RTC_ACCTRL_ACCLK_2
#define RTC_ATCS_HOUR         RTC_ACCTRL_ACCLK_3
//ADCSource
#define RTC_ADCS_DATA        (0)
#define RTC_ADCS_PORT         RTC_ACCTRL_ADCSEL

//CNTCLK
#define RTC_WKUCNT_RTCCLK     RTC_WKUCNT_CNTSEL_0 
#define RTC_WKUCNT_2048       RTC_WKUCNT_CNTSEL_1
#define RTC_WKUCNT_512        RTC_WKUCNT_CNTSEL_2
#define RTC_WKUCNT_128        RTC_WKUCNT_CNTSEL_3

//Prescaler
#define RTC_CLKDIV_1          RTC_PSCA_PSCA_0
#define RTC_CLKDIV_4          RTC_PSCA_PSCA_1
   
/* Private macros ------------------------------------------------------------*/
#define IS_RTC_REGOP_STARTADDR(__STARTADDR__)  (((__STARTADDR__) & 0x3U) == 0U)
/* Year      0 ~ 99 */  
#define IS_RTC_TIME_YEAR(__YEAR__)  ((__YEAR__) < 0x9AU)
/* Month     1 ~ 12 */ 
#define IS_RTC_TIME_MONTH(__MONTH__)  (((__MONTH__) > 0x0U) && ((__MONTH__) < 0x13U))
/* Date      1 ~ 31 */ 
#define IS_RTC_TIME_DATE(__DATE__)  (((__DATE__) > 0x0U) && ((__DATE__) < 0x32))
/* Weekday   0 ~ 6 */
#define IS_RTC_TIME_WEEKDAY(__WEEKDAY__)  ((__WEEKDAY__) < 0x7U)
/* Hours     0 ~ 23 */
#define IS_RTC_TIME_HOURS(__HOURS__)  ((__HOURS__) < 0x24)
/* Minutes   0 ~ 59 */
#define IS_RTC_TIME_MINS(__MINS__)  ((__MINS__) < 0x5A)
/* Seconds   0 ~ 59 */
#define IS_RTC_TIME_SECS(__SECS__)  ((__SECS__) < 0x5A)

#define IS_RTC_INT(__INT__)  ((((__INT__) & RTC_INT_Msk) != 0U) &&\
                              (((__INT__) & ~RTC_INT_Msk) == 0U))

#define IS_RTC_INTFLAGR(__INTFLAGR_)  (((__INTFLAGR_) == RTC_INTSTS_CEILLE)   ||\
                                       ((__INTFLAGR_) == RTC_INTSTS_ACDONE)   ||\
                                       ((__INTFLAGR_) == RTC_INTSTS_WKUCNT)   ||\
                                       ((__INTFLAGR_) == RTC_INTSTS_MIDNIGHT) ||\
                                       ((__INTFLAGR_) == RTC_INTSTS_WKUHOUR)  ||\
                                       ((__INTFLAGR_) == RTC_INTSTS_WKUMIN)   ||\
                                       ((__INTFLAGR_) == RTC_INTSTS_WKUSEC)   ||\
                                       ((__INTFLAGR_) == RTC_INTSTS_TIMEILLE))

#define IS_RTC_INTFLAGC(__INTFLAGC__)  ((((__INTFLAGC__) & RTC_INTSTS_Msk) != 0U) &&\
                                        (((__INTFLAGC__) & ~RTC_INTSTS_Msk) == 0U))

#define IS_RTC_AUTOCAL_RELOAD(__RELOAD__)  (((__RELOAD__) == RTC_AUTORELOAD_DISABLE) ||\
                                            ((__RELOAD__) == RTC_AUTORELOAD_ENABLE))

#define IS_RTC_AUTOCAL_ATDLY(__ATDLY__)  (((__ATDLY__) == RTC_ATDELAY_15MS) ||\
                                          ((__ATDLY__) == RTC_ATDELAY_31MS) ||\
                                          ((__ATDLY__) == RTC_ATDELAY_62MS) ||\
                                          ((__ATDLY__) == RTC_ATDELAY_125MS))

#define IS_RTC_AUTOCAL_ATCS(__ATCS__)  (((__ATCS__) == RTC_ATCS_DISABLE) ||\
                                        ((__ATCS__) == RTC_ATCS_SEC)     ||\
                                        ((__ATCS__) == RTC_ATCS_MIN)     ||\
                                        ((__ATCS__) == RTC_ATCS_HOUR))

#define IS_RTC_AUTOCAL_ADCSRC(__ADCSRC__)  (((__ADCSRC__) == RTC_ADCS_DATA) ||\
                                            ((__ADCSRC__) == RTC_ADCS_PORT))

#define IS_RTC_AUTOCAL_PERIOD(__PERIOD__)  ((__PERIOD__) < 64U)

#define IS_RTC_WKUSEC_PERIOD(__PERIOD__)  (((__PERIOD__) < 0x41U) && ((__PERIOD__) > 0U))

#define IS_RTC_WKUMIN_PERIOD(__PERIOD__)  (((__PERIOD__) < 0x41U) && ((__PERIOD__) > 0U))

#define IS_RTC_WKUHOUR_PERIOD(__PERIOD__)  (((__PERIOD__) < 0x21U) && ((__PERIOD__) > 0U))

#define IS_RTC_WKUCNT_PERIOD(__PERIOD__)  (((__PERIOD__) < 0x1000001U) && ((__PERIOD__) > 0U))

#define IS_RTC_WKUCNT_CNTSEL(__CNTSEL__)  (((__CNTSEL__) == RTC_WKUCNT_RTCCLK) ||\
                                           ((__CNTSEL__) == RTC_WKUCNT_2048)   ||\
                                           ((__CNTSEL__) == RTC_WKUCNT_512)    ||\
                                           ((__CNTSEL__) == RTC_WKUCNT_128))

#define IS_RTC_CLKDIV(__CLKDIV__)  (((__CLKDIV__) == RTC_CLKDIV_1) ||\
                                    ((__CLKDIV__) == RTC_CLKDIV_4))

/* Exported Functions ------------------------------------------------------- */
/* RTC Exported Functions Group1: 
                                  Time functions -----------------------------*/
void RTC_SetTime(RTC_TimeTypeDef *sTime);
void RTC_GetTime(RTC_TimeTypeDef *gTime);
/* RTC Exported Functions Group2: 
                                  Registers operation functions --------------*/
void RTC_WriteProtection(uint32_t NewState);
void RTC_WaitForSynchro(void);
void RTC_WriteRegisters(uint32_t StartAddr, const uint32_t *wBuffer, uint8_t Len);
void RTC_ReadRegisters(uint32_t StartAddr, uint32_t *rBuffer, uint8_t Len);
/* RTC Exported Functions Group3: 
                                  Interrupt functions ------------------------*/
void RTC_INTConfig(uint32_t INTMask, uint32_t NewState);
uint8_t RTC_GetINTStatus(uint32_t FlagMask); 
void RTC_ClearINTStatus(uint32_t FlagMask);
/* RTC Exported Functions Group4: 
                                  AutoCal functions --------------------------*/
void RTC_AutoCalStructInit(RTC_AutCalType *RTCAC_InitStruct);
void RTC_AutoCalInit(RTC_AutCalType *InitStruct);
void RTC_TrigSourceConfig(uint32_t TrigSource, uint32_t Period);
uint32_t RTC_AutoCalCmd(uint32_t NewState);
void RTC_StartAutoCalManual(void);
void RTC_WaitForAutoCalManual(void);
uint8_t RTC_GetACBusyFlag(void);
/* RTC Exported Functions Group5: 
                                  Wake-up functions --------------------------*/
void RTC_WKUSecondsConfig(uint8_t nPeriod);
void RTC_WKUMinutesConfig(uint8_t nPeriod);
void RTC_WKUHoursConfig(uint8_t nPeriod);
void RTC_WKUCounterConfig(uint32_t nClock,uint32_t CNTCLK);
uint32_t RTC_GetWKUCounterValue(void);
/* RTC Exported Functions Group6: 
                                  MISC functions -----------------------------*/
void RTC_PrescalerConfig(uint32_t Prescaler);
void RTC_PLLDIVConfig(uint32_t nfrequency);
void RTC_PLLDIVOutputCmd(uint8_t NewState);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_RTC_H */

/*********************************** END OF FILE ******************************/
