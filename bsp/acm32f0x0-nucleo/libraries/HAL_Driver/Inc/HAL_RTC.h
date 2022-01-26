/*
  ******************************************************************************
  * @file    HAL_RTC.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of RTC HAL module.
  ******************************************************************************
*/

#ifndef __HAL_RTC_H__
#define __HAL_RTC_H__

#include "ACM32Fxx_HAL.h"

/************************************************************************************/
/*                             Registers Bits Definition                            */
/************************************************************************************/

/****************  Bit definition for RTC IE Register  ***********************/
#define RTC_IE_STP2RIE       (BIT16)
#define RTC_IE_STP2FIE       (BIT15)
#define RTC_IE_STP1RIE       (BIT14)
#define RTC_IE_STP1FIE       (BIT13)
#define RTC_IE_ADJ32         (BIT12)
#define RTC_IE_ALM           (BIT11)
#define RTC_IE_1KHZ          (BIT10)
#define RTC_IE_256HZ         (BIT9)
#define RTC_IE_64HZ          (BIT8)
#define RTC_IE_16HZ          (BIT7)
#define RTC_IE_8HZ           (BIT6)
#define RTC_IE_4HZ           (BIT5)
#define RTC_IE_2HZ           (BIT4)
#define RTC_IE_SEC           (BIT3)
#define RTC_IE_MIN           (BIT2)
#define RTC_IE_HOUR          (BIT1)
#define RTC_IE_DATE          (BIT0)

/****************  Bit definition for RTC SR Register  ***********************/
#define RTC_SR_STP2RIE       (BIT16)
#define RTC_SR_STP2FIE       (BIT15)
#define RTC_SR_STP1RIE       (BIT14)
#define RTC_SR_STP1FIE       (BIT13)
#define RTC_SR_ADJ32         (BIT12)
#define RTC_SR_ALM           (BIT11)
#define RTC_SR_1KHZ          (BIT10)
#define RTC_SR_256HZ         (BIT9)
#define RTC_SR_64HZ          (BIT8)
#define RTC_SR_16HZ          (BIT7)
#define RTC_SR_8HZ           (BIT6)
#define RTC_SR_4HZ           (BIT5)
#define RTC_SR_2HZ           (BIT4)
#define RTC_SR_SEC           (BIT3)
#define RTC_SR_MIN           (BIT2)
#define RTC_SR_HOUR          (BIT1)
#define RTC_SR_DATE          (BIT0)

/****************  Bit definition for RTC CR Register  ***********************/
#define RTC_CR_TAMPFLTCLK    (BIT22)
#define RTC_CR_TS2EDGE       (BIT21)
#define RTC_CR_TAMP2FLT      (BIT19|BIT20)
#define RTC_CR_TAMP2FLTEN    (BIT18)
#define RTC_CR_TAMP2FCLR     (BIT17)
#define RTC_CR_TAMP2RCLR     (BIT16)
#define RTC_CR_TS1EDGE       (BIT15)
#define RTC_CR_TAMP1FLT      (BIT13|BIT14)
#define RTC_CR_TAMP1FLTEN    (BIT12)
#define RTC_CR_ALM_MKSD      (BIT11)
#define RTC_CR_ALM_MSKH      (BIT10)
#define RTC_CR_ALM_MSKM      (BIT9)
#define RTC_CR_TAMP1FCLR     (BIT8)
#define RTC_CR_TAMP1RCLR     (BIT7)
#define RTC_CR_TAMP2EN       (BIT6)
#define RTC_CR_TAMP1EN       (BIT5)
#define RTC_CR_ALM_EN        (BIT4)
#define RTC_CR_FSEL          (BIT0|BIT1|BIT2|BIT3)

/****************  Bit definition for RTC_PMU CR Register  ***********************/
#define RPMU_CR_WU6FILEN            BIT29
#define RPMU_CR_WU5FILEN            BIT28
#define RPMU_CR_WU4FILEN            BIT27
#define RPMU_CR_WU3FILEN            BIT26
#define RPMU_CR_WU2FILEN            BIT25
#define RPMU_CR_WU1FILEN            BIT24
#define RPMU_CR_EWUP6               BIT21
#define RPMU_CR_EWUP5               BIT20
#define RPMU_CR_EWUP4               BIT19
#define RPMU_CR_EWUP3               BIT18
#define RPMU_CR_EWUP2               BIT17
#define RPMU_CR_EWUP1               BIT16
#define RPMU_CR_BORRST_EN           BIT12
#define RPMU_CR_WK_TIME            (BIT9|BIT10|BIT11)
#define RPMU_CR_STB_EN              BIT8
#define RPMU_CR_BDRST               BIT6
#define RPMU_CR_RTCEN               BIT5
#define RPMU_CR_RTCSEL             (BIT2|BIT3)
#define RPMU_CR_CWUF                BIT1
#define RPMU_CR_CSBF                BIT0

/****************  Bit definition for RTC_PMU ANACR Register  ***********************/
#define RPMU_SR_BORWUF              BIT13
#define RPMU_SR_IWDTWUF             BIT12
#define RPMU_SR_RSTWUF              BIT11
#define RPMU_SR_RTCWUF              BIT10
#define RPMU_SR_WUP6F               BIT6
#define RPMU_SR_WUP5F               BIT5
#define RPMU_SR_WUP4F               BIT4
#define RPMU_SR_WUP3F               BIT3
#define RPMU_SR_WUP2F               BIT2
#define RPMU_SR_WUP1F               BIT1
#define RPMU_SR_SBF                 BIT0

/****************  Bit definition for RTC_PMU ANACR Register  ***********************/
#define RPMU_ANACR_BOR_CFG                 (BIT24|BIT25)
#define RPMU_ANACR_BOR_EN                   BIT23
#define RPMU_ANACR_LPBGR_TRIM              (BIT20|BIT21|BIT22)
#define RPMU_ANACR_RC32K_TRIM              (BIT10|BIT11|BIT12|BIT13|BIT14|BIT15)
#define RPMU_ANACR_RC32K_RDY                BIT9
#define RPMU_ANACR_RC32K_EN                 BIT8
#define RPMU_ANACR_XTLDRV_2                 BIT5
#define RPMU_ANACR_XTLDRV_1                 BIT4
#define RPMU_ANACR_XTLDRV_0                 BIT3
#define RPMU_ANACR_XTLDRV                  (BIT3|BIT4|BIT5)
#define RPMU_ANACR_XTLBYO                   BIT2
#define RPMU_ANACR_XTLRDY                   BIT1
#define RPMU_ANACR_XTLEN                    BIT0


/** @defgroup ClockSource
  * @{
  */
#define RTC_CLOCK_RC32K       (0x00000000)
#define RTC_CLOCK_XTL         (0x00000004)
/**
  * @}
  */


/** @defgroup Clock_Compensation
  * @{
  */
#define COMPENSATION_INCREASE      (0x00000000)
#define COMPENSATION_DECREASE      (0x00000400)
/**
  * @}
  */


/** @defgroup RTC_Month_Date_Definitions RTC Month Date Definitions
  * @{
  */

/* Coded in BCD format */
#define RTC_MONTH_JANUARY           (0x01)
#define RTC_MONTH_FEBRUARY          (0x02)
#define RTC_MONTH_MARCH             (0x03)
#define RTC_MONTH_APRIL             (0x04)
#define RTC_MONTH_MAY               (0x05)
#define RTC_MONTH_JUNE              (0x06)
#define RTC_MONTH_JULY              (0x07)
#define RTC_MONTH_AUGUST            (0x08)
#define RTC_MONTH_SEPTEMBER         (0x09)
#define RTC_MONTH_OCTOBER           (0x10)
#define RTC_MONTH_NOVEMBER          (0x11)
#define RTC_MONTH_DECEMBER          (0x12)
/**
  * @}
  */


/** @defgroup RTC_WeekDay_Definitions RTC WeekDay Definitions
  * @{
  */
#define RTC_WEEKDAY_MONDAY          (0x01)
#define RTC_WEEKDAY_TUESDAY         (0x02)
#define RTC_WEEKDAY_WEDNESDAY       (0x03)
#define RTC_WEEKDAY_THURSDAY        (0x04)
#define RTC_WEEKDAY_FRIDAY          (0x05)
#define RTC_WEEKDAY_SATURDAY        (0x06)
#define RTC_WEEKDAY_SUNDAY          (0x07)
/**
  * @}
  */


/** @defgroup RTC_Alarm_Mode Definitions
  * @{
  */
#define RTC_ALARM_WEEK_MODE       (0x00000000)
#define RTC_ALARM_DAY_MODE        (0x80000000)
/**
  * @}
  */


/** @defgroup RTC_AlarmInterrupt Definitions
  * @{
  */
#define RTC_ALARM_INT_ENABLE       (0x00000000)
#define RTC_ALARM_INT_DISABLE      (0x00000001)
/**
  * @}
  */


/** @defgroup RTC_DayMask Definitions
  * @{
  */
#define RTC_ALARM_DAY_MASK_ENABLE       RTC_CR_ALM_MKSD
#define RTC_ALARM_DAY_MASK_DISABLE      (0x00000000)
/**
  * @}
  */


/** @defgroup RTC_HourMask Definitions
  * @{
  */
#define RTC_ALARM_HOUR_MASK_ENABLE       RTC_CR_ALM_MSKH
#define RTC_ALARM_HOUR_MASK_DISABLE      (0x00000000)
/**
  * @}
  */


/** @defgroup RTC_MinMask Definitions
  * @{
  */
#define RTC_ALARM_MIN_MASK_ENABLE       RTC_CR_ALM_MSKM
#define RTC_ALARM_MIN_MASK_DISABLE      (0x00000000)
/**
  * @}
  */


/** @defgroup RTC_Alarm_WeekSelect Definitions
  * @{
  */
#define RTC_ALARM_WEEK_SUNDAY       (0x01000000)
#define RTC_ALARM_WEEK_MONDAY       (0x02000000)
#define RTC_ALARM_WEEK_TUESDAY      (0x04000000)
#define RTC_ALARM_WEEK_WEDNESDAY    (0x08000000)
#define RTC_ALARM_WEEK_THURSDAY     (0x10000000)
#define RTC_ALARM_WEEK_FRIDAY       (0x20000000)
#define RTC_ALARM_WEEK_SATURDAY     (0x40000000)
/**
  * @}
  */


/** @defgroup RTC_Temper_edge Definitions
  * @{
  */
#define RTC_TEMP_EDGE_RISING       (0x00000000)
#define RTC_TEMP_EDGE_FALLING      (0x00000001)
/**
  * @}
  */


/** @defgroup RTC_TemperInterrupt Definitions
  * @{
  */
#define RTC_TEMP_INT_DISABLE      (0x00000000)
#define RTC_TEMP_INT_ENABLE       (0x00000001)
/**
  * @}
  */


/** @defgroup RTC_ClearBackup Definitions
  * @{
  */
#define RTC_TEMP_CLEAR_DISABLE       (0x00000000)
#define RTC_TEMP_CLEAR_ENABLE        (0x00000001)
/**
  * @}
  */


/** @defgroup RTC_TemperFilter Definitions
  * @{
  */
#define RTC_TEMP_FILTER_DISABLE         (0x00000000)
#define RTC_TEMP_FILTER_512_RTCCLK      (0x00000001)
#define RTC_TEMP_FILTER_1_RTCCLK        (0x00000002)
#define RTC_TEMP_FILTER_2_RTCCLK        (0x00000003)
#define RTC_TEMP_FILTER_4_RTCCLK        (0x00000004)
#define RTC_TEMP_FILTER_8_RTCCLK        (0x00000005)
/**
  * @}
  */


/**
  * @brief  RTC Temper index definition
  */
typedef enum
{
    RTC_TEMPER_1,
    RTC_TEMPER_2,
}enum_Temper_t;
/**
  * @}
  */


/**
  * @brief  RTC wakeup source form standby
  */
typedef enum
{
    RTC_WAKEUP_RTC_INT = 0,
    RTC_WAKEUP_WKUP1  = 0x00010000,  // PA0
    RTC_WAKEUP_WKUP2  = 0x00020000,  // PC13
    RTC_WAKEUP_WKUP3  = 0x00040000,  // PA2
    RTC_WAKEUP_WKUP4  = 0x00080000,  // PC5
    RTC_WAKEUP_WKUP5  = 0x00100000,  // PB5
    RTC_WAKEUP_WKUP6  = 0x00200000,  // PB15
    RTC_WAKEUP_STAMP2 = (RTC_IE_STP2RIE | RTC_IE_STP2FIE),
    RTC_WAKEUP_STAMP1 = (RTC_IE_STP1RIE | RTC_IE_STP1FIE),
    RTC_WAKEUP_32S    = RTC_IE_ADJ32,
    RTC_WAKEUP_ALARM  = RTC_IE_ALM,
    RTC_WAKEUP_SEC    = RTC_IE_SEC,
    RTC_WAKEUP_MIN    = RTC_IE_MIN,
    RTC_WAKEUP_HOUR   = RTC_IE_HOUR,
    RTC_WAKEUP_DATE   = RTC_IE_DATE,
}enum_WKUP_t;

#define STANDBY_WAKEUP_RISING     0
#define STANDBY_WAKEUP_FALLING    1

/**
  * @}
  */

/**
  * @brief  Check RTC wakeup source form standby
  */
#define RTC_WAKEUP_SOURCE_BORWUF    (0x00002000)
#define RTC_WAKEUP_SOURCE_IWDTWUF   (0x00001000)
#define RTC_WAKEUP_SOURCE_RSTWUF    (0x00000800)
#define RTC_WAKEUP_SOURCE_RTCWUF    (0x00000400)
#define RTC_WAKEUP_SOURCE_WKUP6     (0x00000040)
#define RTC_WAKEUP_SOURCE_WKUP5     (0x00000020)
#define RTC_WAKEUP_SOURCE_WKUP4     (0x00000010)
#define RTC_WAKEUP_SOURCE_WKUP3     (0x00000008)
#define RTC_WAKEUP_SOURCE_WKUP2     (0x00000004)
#define RTC_WAKEUP_SOURCE_WKUP1     (0x00000002)
/**
  * @}
  */

/**
  * @brief  RTC Configuration Structure definition
  */
typedef struct
{
    uint32_t u32_ClockSource;           /*!< The RTC Clock Source to be configured.
                                             This parameter can be a value of @ref ClockSource */

    uint32_t u32_Compensation;          /*!< The RTC Clock Compensation to be configured.
                                             This parameter can be a value of @ref Clock_Compensation */

    uint32_t u32_CompensationValue;     /*!< The RTC Clock Compensation Value to be configured.
                                             This parameter must be a number between Min_Data = 0x000 and Max_Data = 0x1FF */
}RTC_ConfigTypeDef;


/**
  * @brief  RTC Date structure definition
  */
typedef struct
{
    uint8_t u8_Year;     /*!< Specifies the RTC Date Year.
                              This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x99 */

    uint8_t u8_Month;    /*!< Specifies the RTC Date Month (in BCD format).
                              This parameter can be a value of @ref RTC_Month_Date_Definitions */

    uint8_t u8_Date;     /*!< Specifies the RTC Date.
                              This parameter must be a number between Min_Data = 0x01 and Max_Data = 0x31 */

    uint8_t u8_WeekDay;  /*!< Specifies the RTC Date WeekDay.
                              This parameter can be a value of @ref RTC_WeekDay_Definitions */
}RTC_DateTypeDef;
/* Attention: Year、Month、Date、Week use BCD code */


/**
  * @brief  RTC Time structure definition
  */
typedef struct
{
    uint8_t u8_Hours;       /*!< Specifies the RTC Time Hour.
                                 This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x23 */

    uint8_t u8_Minutes;     /*!< Specifies the RTC Time Minutes.
                                 This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x59 */

    uint8_t u8_Seconds;     /*!< Specifies the RTC Time Seconds.
                                 This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x59 */
}RTC_TimeTypeDef;
/* Attention: Hour、Minute、Second use BCD code */


/**
  * @brief  RTC Time structure definition
  */
typedef struct
{
    uint32_t u32_AlarmMode;         /*!< Specifies the RTC alarm Mode.
                                         This parameter can be a value of @ref RTC_Alarm_Mode */

    uint32_t u32_AlarmInterrupt;    /*!< Specifies the RTC alarm interrupt Enable or Disable.
                                         This parameter can be a value of @ref RTC_AlarmInterrupt */

    uint32_t u32_DayMask;           /*!< Specifies the RTC alarm Day/Week Mask.
                                         This parameter can be a value of @ref RTC_DayMask */

    uint32_t u32_HourMask;          /*!< Specifies the RTC alarm Hour Mask.
                                         This parameter can be a value of @ref RTC_HourMask */

    uint32_t u32_MinMask;           /*!< Specifies the RTC alarm Min Mask.
                                         This parameter can be a value of @ref RTC_MinMask */

    uint32_t u32_AlarmWeek;         /*!< Specifies the RTC alarm week select(Select WeekMode this parameter is valid).
                                         This parameter can be a value of @ref RTC_Alarm_WeekSelect */

    uint32_t u32_AlarmDay;          /*!< Specifies the RTC alarm day  select(Select DayMode this parameter is valid).
                                         This parameter must be a number between Min_Data = 0x01 and Max_Data = 0x31 */

    uint32_t u32_Hours;             /*!< Specifies the RTC alarm Hour.
                                         This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x23 */

    uint32_t u32_Minutes;           /*!< Specifies the RTC alarm Minutes.
                                         This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x59 */

    uint32_t u32_Seconds;           /*!< Specifies the RTC alarm Seconds.
                                         This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x59 */
}RTC_AlarmTypeDef;


/**
  * @brief  RTC Temper structure definition
  */
typedef struct
{
    uint32_t u32_TemperEdge;      /*!< Specifies the RTC Temper edge select.
                                       This parameter can be a value of @ref RTC_Temper_edge */

    uint32_t u32_InterruptEN;     /*!< Specifies the RTC Temper interrupt enable.
                                       This parameter can be a value of @ref RTC_TemperInterrupt */

    uint32_t u32_ClearBackup;     /*!< Specifies the RTC Temper clear backup register.
                                       This parameter can be a value of @ref RTC_ClearBackup */

    uint32_t u32_Filter;          /*!< Specifies the RTC Temper Filter select.
                                       This parameter can be a value of @ref RTC_TemperFilter */
}RTC_TemperTypeDef;


/** @brief  PC13 function select
  * @param  __FUNC__: PC13 function select.
  *         This parameter can be 0: GPIO，1：RTC Fout，2：RTC tamper 3：PC13 Value
  */
#define __HAL_RTC_PC13_SEL(__FUNC__)    (PMU->IOSEL |= (PMU->IOSEL & ~(0x3)) | (__FUNC__))

/** @brief  PC14 function select
  * @param  __FUNC__: PC14 function select.
  *         This parameter can be 0: GPIO，1：PC14 Value
  */
#define __HAL_RTC_PC14_SEL(__FUNC__)    (PMU->IOSEL |= (PMU->IOSEL & ~(0x3 << 3)) | (__FUNC__ << 3))

/** @brief  PC15 function select
  * @param  __FUNC__: PC15 function select.
  *         This parameter can be 0: GPIO，1：PC15 Value
  */
#define __HAL_RTC_PC15_SEL(__FUNC__)    (PMU->IOSEL |= (PMU->IOSEL & ~(0x3 << 5)) | (__FUNC__ << 5))

/** @brief  PC13 Value set
  * @param  __FUNC__: PC13 Value set.
  *         This parameter can be 0: set，1：claer
  */
#define __HAL_RTC_PC13_VALUE(__VALUE__)    (PMU->IOSEL |= (PMU->IOSEL & ~(1 << 8)) | (__VALUE__ << 8))

/** @brief  PC14 Value set
  * @param  __FUNC__: PC14 Value set.
  *         This parameter can be 0: set，1：claer
  */
#define __HAL_RTC_PC14_VALUE(__VALUE__)    (PMU->IOSEL |= (PMU->IOSEL & ~(1 << 9)) | (__VALUE__ << 9))

/** @brief  PC15 Value set
  * @param  __FUNC__: PC15 Value set.
  *         This parameter can be 0: set，1：claer
  */
#define __HAL_RTC_PC15_VALUE(__VALUE__)    (PMU->IOSEL |= (PMU->IOSEL & ~(1 << 10)) | (__VALUE__ << 10))

/* @brief  PC13、PC14、PC15 pull up or pull down */
#define __HAL_RTC_PC13_PULL_UP_ENABLE()       (PMU->IOCR |=  BIT0)
#define __HAL_RTC_PC13_PULL_UP_DISABLE()      (PMU->IOCR &= ~BIT0)
#define __HAL_RTC_PC13_PULL_DOWN_ENABLE()     (PMU->IOCR |=  BIT1)
#define __HAL_RTC_PC13_PULL_DOWN_DISABLE()    (PMU->IOCR &= ~BIT1)

#define __HAL_RTC_PC14_PULL_UP_ENABLE()       (PMU->IOCR |=  BIT8)
#define __HAL_RTC_PC14_PULL_UP_DISABLE()      (PMU->IOCR &= ~BIT8)
#define __HAL_RTC_PC14_PULL_DOWN_ENABLE()     (PMU->IOCR |=  BIT9)
#define __HAL_RTC_PC14_PULL_DOWN_DISABLE()    (PMU->IOCR &= ~BIT9)

#define __HAL_RTC_PC15_PULL_UP_ENABLE()       (PMU->IOCR |=  BIT16)
#define __HAL_RTC_PC15_PULL_UP_DISABLE()      (PMU->IOCR &= ~BIT16)
#define __HAL_RTC_PC15_PULL_DOWN_ENABLE()     (PMU->IOCR |=  BIT17)
#define __HAL_RTC_PC15_PULL_DOWN_DISABLE()    (PMU->IOCR &= ~BIT17)

/* @brief  PC13、PC14、PC15 digit or analog */
#define __HAL_RTC_PC13_ANALOG()    (PMU->IOCR |=  BIT6)
#define __HAL_RTC_PC13_DIGIT()     (PMU->IOCR &= ~BIT6)

#define __HAL_RTC_PC14_ANALOG()    (PMU->IOCR |=  BIT14)
#define __HAL_RTC_PC14_DIGIT()     (PMU->IOCR &= ~BIT14)

#define __HAL_RTC_PC15_ANALOG()    (PMU->IOCR |=  BIT22)
#define __HAL_RTC_PC15_DIGIT()     (PMU->IOCR &= ~BIT22)


/** @defgroup  RTC Private Macros
  * @{
  */
#define IS_RTC_CLOCKSRC(__CLOCKSRC__)     (((__CLOCKSRC__) == RTC_CLOCK_RC32K) || \
                                           ((__CLOCKSRC__) == RTC_CLOCK_XTL))

#define IS_RTC_COMPENSATION(__COMPENSATION__)     (((__COMPENSATION__) == COMPENSATION_INCREASE) || \
                                                   ((__COMPENSATION__) == COMPENSATION_DECREASE))

#define IS_RTC_YEAR(__YEAR__)       ((__YEAR__) <= 0x99)

#define IS_RTC_MONTH(__MONTH__)     (((__MONTH__) == RTC_MONTH_JANUARY)   || \
                                     ((__MONTH__) == RTC_MONTH_FEBRUARY)  || \
                                     ((__MONTH__) == RTC_MONTH_MARCH)     || \
                                     ((__MONTH__) == RTC_MONTH_APRIL)     || \
                                     ((__MONTH__) == RTC_MONTH_MAY)       || \
                                     ((__MONTH__) == RTC_MONTH_JUNE)      || \
                                     ((__MONTH__) == RTC_MONTH_JULY)      || \
                                     ((__MONTH__) == RTC_MONTH_AUGUST)    || \
                                     ((__MONTH__) == RTC_MONTH_SEPTEMBER) || \
                                     ((__MONTH__) == RTC_MONTH_OCTOBER)   || \
                                     ((__MONTH__) == RTC_MONTH_NOVEMBER)  || \
                                     ((__MONTH__) == RTC_MONTH_DECEMBER))

#define IS_RTC_DAY(__DAY__)          ((__DAY__) >= 0x01 && (__DAY__) <= 0x31)

#define IS_RTC_WEEKDAY(__WEEKDAY__)   (((__WEEKDAY__) == RTC_WEEKDAY_MONDAY)    || \
                                       ((__WEEKDAY__) == RTC_WEEKDAY_TUESDAY)   || \
                                       ((__WEEKDAY__) == RTC_WEEKDAY_WEDNESDAY) || \
                                       ((__WEEKDAY__) == RTC_WEEKDAY_THURSDAY)  || \
                                       ((__WEEKDAY__) == RTC_WEEKDAY_FRIDAY)    || \
                                       ((__WEEKDAY__) == RTC_WEEKDAY_SATURDAY)  || \
                                       ((__WEEKDAY__) == RTC_WEEKDAY_SUNDAY))

#define IS_RTC_HOUR(__HOUR__)    ((__HOUR__) <= 0x23)

#define IS_RTC_MIN(__MIN__)      ((__MIN__) <= 0x59)

#define IS_RTC_SEC(__SEC__)      ((__SEC__) <= 0x60)


#define IS_RTC_ALARM_MODE(__MODE__)      (((__MODE__) == RTC_ALARM_WEEK_MODE) || \
                                          ((__MODE__) == RTC_ALARM_DAY_MODE))

#define IS_RTC_ALARM_INT(__INT__)        (((__INT__) == RTC_ALARM_INT_ENABLE) || \
                                          ((__INT__) == RTC_ALARM_INT_DISABLE))

#define IS_RTC_ALARM_DAY_MASK(__MASKD__)     (((__MASKD__) == RTC_ALARM_DAY_MASK_ENABLE) || \
                                              ((__MASKD__) == RTC_ALARM_DAY_MASK_DISABLE))

#define IS_RTC_ALARM_HOUR_MASK(__MASKH__)    (((__MASKH__) == RTC_ALARM_HOUR_MASK_ENABLE) || \
                                              ((__MASKH__) == RTC_ALARM_HOUR_MASK_DISABLE))

#define IS_RTC_ALARM_MIN_MASK(__MASKM__)     (((__MASKM__) == RTC_ALARM_MIN_MASK_ENABLE) || \
                                              ((__MASKM__) == RTC_ALARM_MIN_MASK_DISABLE))

#define IS_RTC_ALARM_WEEKDAY(__WEEKDAY__)    (((__WEEKDAY__) == RTC_ALARM_WEEK_SUNDAY)    || \
                                              ((__WEEKDAY__) == RTC_ALARM_WEEK_MONDAY)    || \
                                              ((__WEEKDAY__) == RTC_ALARM_WEEK_TUESDAY)   || \
                                              ((__WEEKDAY__) == RTC_ALARM_WEEK_WEDNESDAY) || \
                                              ((__WEEKDAY__) == RTC_ALARM_WEEK_THURSDAY)  || \
                                              ((__WEEKDAY__) == RTC_ALARM_WEEK_FRIDAY)    || \
                                              ((__WEEKDAY__) == RTC_ALARM_WEEK_SATURDAY)  || \
                                              ((__WEEKDAY__) >= 0x01000000 && (__WEEKDAY__) <= 0x7F000000))


#define IS_RTC_TEMP_EDGE(__EDGE__)           (((__EDGE__) == RTC_TEMP_EDGE_RISING) || \
                                              ((__EDGE__) == RTC_TEMP_EDGE_FALLING))

#define IS_RTC_TEMP_INT(__INT__)             (((__INT__) == RTC_TEMP_INT_ENABLE) || \
                                              ((__INT__) == RTC_TEMP_INT_DISABLE))

#define IS_RTC_TEMP_CLEAR_BACKUP(__CLEAR__)    (((__CLEAR__) == RTC_TEMP_CLEAR_DISABLE) || \
                                                ((__CLEAR__) == RTC_TEMP_CLEAR_ENABLE))

#define IS_RTC_TEMP_FILTER(__FILTER__)         (((__FILTER__) == RTC_TEMP_FILTER_DISABLE)    || \
                                                ((__FILTER__) == RTC_TEMP_FILTER_512_RTCCLK) || \
                                                ((__FILTER__) == RTC_TEMP_FILTER_1_RTCCLK)   || \
                                                ((__FILTER__) == RTC_TEMP_FILTER_2_RTCCLK)   || \
                                                ((__FILTER__) == RTC_TEMP_FILTER_4_RTCCLK)   || \
                                                ((__FILTER__) == RTC_TEMP_FILTER_8_RTCCLK))
/**
  * @}
  */

/* RTC stamp1 interrupt enable、disable */
#define __HAL_RTC_ENABLE_STAMP1_IT         (RTC->IE |= (RTC_IE_STP1RIE | RTC_IE_STP1FIE))
#define __HAL_RTC_DISABLE_STAMP1_IT        (RTC->IE &= ~(RTC_IE_STP1RIE | RTC_IE_STP1FIE))

/* RTC stamp2 interrupt enable、disable */
#define __HAL_RTC_ENABLE_STAMP2_IT         (RTC->IE |= (RTC_IE_STP2RIE | RTC_IE_STP2FIE))
#define __HAL_RTC_DISABLE_STAMP2_IT        (RTC->IE &= ~(RTC_IE_STP2RIE | RTC_IE_STP2FIE))

/* RTC 32S interrupt enable、disable */
#define __HAL_RTC_ENABLE_32S_IT            (RTC->IE |= RTC_IE_ADJ32)
#define __HAL_RTC_DISABLE_32S_IT           (RTC->IE &= ~RTC_IE_ADJ32)

/* RTC alarm interrupt enable、disable */
#define __HAL_RTC_ENABLE_ALM_IT            (RTC->IE |= RTC_IE_ALM)
#define __HAL_RTC_DISABLE_ALM_IT           (RTC->IE &= RTC_IE_ALM)

/* RTC sec interrupt enable、disable */
#define __HAL_RTC_ENABLE_SEC_IT            (RTC->IE |= RTC_IE_SEC)
#define __HAL_RTC_DISABLE_SEC_IT           (RTC->IE &= ~RTC_IE_SEC)

/* RTC Minutes interrupt enable、disable */
#define __HAL_RTC_ENABLE_MIN_IT            (RTC->IE |= RTC_IE_MIN)
#define __HAL_RTC_DISABLE_MIN_IT           (RTC->IE &= ~RTC_IE_MIN)

/* RTC Hour interrupt enable、disable */
#define __HAL_RTC_ENABLE_HOUR_IT           (RTC->IE |= RTC_IE_HOUR)
#define __HAL_RTC_DISABLE_HOUR_IT          (RTC->IE &= ~RTC_IE_HOUR)

/* RTC Date interrupt enable、disable */
#define __HAL_RTC_ENABLE_DATE_IT           (RTC->IE |= RTC_IE_DATE)
#define __HAL_RTC_DISABLE_DATE_IT          (RTC->IE &= ~RTC_IE_DATE)

/* HAL_RTC_Config */
HAL_StatusTypeDef HAL_RTC_Config(RTC_ConfigTypeDef *hrtc);

/* HAL_RTC_SetTime */
void HAL_RTC_SetTime(RTC_TimeTypeDef *fp_Time);

/* HAL_RTC_GetTime */
void HAL_RTC_GetTime(RTC_TimeTypeDef *fp_Time);

/* HAL_RTC_SetDate */
void HAL_RTC_SetDate(RTC_DateTypeDef *fp_Date);

/* HAL_RTC_GetDate */
void HAL_RTC_GetDate(RTC_DateTypeDef *fp_Date);


/* HAL_RTC_AlarmConfig */
void HAL_RTC_AlarmConfig(RTC_AlarmTypeDef *fp_Alarm);

/* HAL_RTC_AlarmEnable */
void HAL_RTC_AlarmEnable(void);

/* HAL_RTC_AlarmDisable */
void HAL_RTC_AlarmDisable(void);

/* HAL_RTC_Tamper */
void HAL_RTC_Tamper(enum_Temper_t fe_Temper, RTC_TemperTypeDef *fp_Temper);

/* HAL_RTC_TamperEnable */
void HAL_RTC_TamperEnable(enum_Temper_t fe_Temper);

/* HAL_RTC_TamperDisable */
void HAL_RTC_TamperDisable(enum_Temper_t fe_Temper);

/* HAL_RTC_Standby_Wakeup */
void HAL_RTC_Standby_Wakeup(enum_WKUP_t fe_Wakeup, uint32_t fu32_Edge);

/* HAL_RTC_Get_StandbyStatus */
bool HAL_RTC_Get_StandbyStatus(void);

/* HAL_RTC_Get_StandbyWakeupSource */
uint32_t HAL_RTC_Get_StandbyWakeupSource(void);

#endif
