/**********************************************************************
* $Id$      lpc_rtc.h           2011-06-02
*//**
* @file     lpc_rtc.h
* @brief    Contains all macro definitions and function prototypes
*           support for RTC firmware library on LPC
* @version  1.0
* @date     02. June. 2011
* @author   NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @defgroup RTC   RTC (Real Time Clock)
 * @ingroup LPC_CMSIS_FwLib_Drivers
 * @{
 */

#ifndef __LPC_RTC_H_
#define __LPC_RTC_H_

/* Includes ------------------------------------------------------------------- */
#include "LPC407x_8x_177x_8x.h"
#include "lpc_types.h"


#ifdef __cplusplus
extern "C"
{
#endif


/* Private Macros ------------------------------------------------------------- */
/** @defgroup RTC_Private_Macros RTC Private Macros
 * @{
 */

/* ----------------------- BIT DEFINITIONS ----------------------------------- */
/* Miscellaneous register group --------------------------------------------- */
/**********************************************************************
* ILR register definitions
**********************************************************************/
/** ILR register mask */
#define RTC_ILR_BITMASK         ((0x00000003))

/** Bit inform the source interrupt is counter increment*/
#define RTC_IRL_RTCCIF          ((1<<0))

/** Bit inform the source interrupt is alarm match*/
#define RTC_IRL_RTCALF          ((1<<1))

/**********************************************************************
* CCR register definitions
**********************************************************************/
/** CCR register mask */
#define RTC_CCR_BITMASK         ((0x00000013))

/** Clock enable */
#define RTC_CCR_CLKEN           ((1<<0))

/** Clock reset */
#define RTC_CCR_CTCRST          ((1<<1))

/** Calibration counter enable */
#define RTC_CCR_CCALEN          ((1<<4))

/**********************************************************************
* CIIR register definitions
**********************************************************************/
/** Counter Increment Interrupt bit for second */
#define RTC_CIIR_IMSEC          ((1<<0))

/** Counter Increment Interrupt bit for minute */
#define RTC_CIIR_IMMIN          ((1<<1))

/** Counter Increment Interrupt bit for hour */
#define RTC_CIIR_IMHOUR         ((1<<2))

/** Counter Increment Interrupt bit for day of month */
#define RTC_CIIR_IMDOM          ((1<<3))

/** Counter Increment Interrupt bit for day of week */
#define RTC_CIIR_IMDOW          ((1<<4))

/** Counter Increment Interrupt bit for day of year */
#define RTC_CIIR_IMDOY          ((1<<5))

/** Counter Increment Interrupt bit for month */
#define RTC_CIIR_IMMON          ((1<<6))

/** Counter Increment Interrupt bit for year */
#define RTC_CIIR_IMYEAR         ((1<<7))

/** CIIR bit mask */
#define RTC_CIIR_BITMASK        ((0xFF))

/**********************************************************************
* AMR register definitions
**********************************************************************/
/** Counter Increment Select Mask bit for second */
#define RTC_AMR_AMRSEC          ((1<<0))

/** Counter Increment Select Mask bit for minute */
#define RTC_AMR_AMRMIN          ((1<<1))

/** Counter Increment Select Mask bit for hour */
#define RTC_AMR_AMRHOUR         ((1<<2))

/** Counter Increment Select Mask bit for day of month */
#define RTC_AMR_AMRDOM          ((1<<3))

/** Counter Increment Select Mask bit for day of week */
#define RTC_AMR_AMRDOW          ((1<<4))

/** Counter Increment Select Mask bit for day of year */
#define RTC_AMR_AMRDOY          ((1<<5))

/** Counter Increment Select Mask bit for month */
#define RTC_AMR_AMRMON          ((1<<6))

/** Counter Increment Select Mask bit for year */
#define RTC_AMR_AMRYEAR         ((1<<7))

/** AMR bit mask */
#define RTC_AMR_BITMASK         ((0xFF))

/**********************************************************************
* RTC_AUX register definitions
**********************************************************************/
/** RTC Oscillator Fail detect flag */
#define RTC_AUX_RTC_OSCF        ((1<<4))

/**********************************************************************
* RTC_AUXEN register definitions
**********************************************************************/
/** Oscillator Fail Detect interrupt enable*/
#define RTC_AUXEN_RTC_OSCFEN    ((1<<4))

/* Consolidated time register group ----------------------------------- */
/**********************************************************************
* Consolidated Time Register 0 definitions
**********************************************************************/
#define RTC_CTIME0_SECONDS_MASK     ((0x3F))
#define RTC_CTIME0_MINUTES_MASK     ((0x3F00))
#define RTC_CTIME0_HOURS_MASK       ((0x1F0000))
#define RTC_CTIME0_DOW_MASK         ((0x7000000))

/**********************************************************************
* Consolidated Time Register 1 definitions
**********************************************************************/
#define RTC_CTIME1_DOM_MASK         ((0x1F))
#define RTC_CTIME1_MONTH_MASK       ((0xF00))
#define RTC_CTIME1_YEAR_MASK        ((0xFFF0000))

/**********************************************************************
* Consolidated Time Register 2 definitions
**********************************************************************/
#define RTC_CTIME2_DOY_MASK         ((0xFFF))

/**********************************************************************
* Time Counter Group and Alarm register group
**********************************************************************/
/** SEC register mask */
#define RTC_SEC_MASK            (0x0000003F)

/** MIN register mask */
#define RTC_MIN_MASK            (0x0000003F)

/** HOUR register mask */
#define RTC_HOUR_MASK           (0x0000001F)

/** DOM register mask */
#define RTC_DOM_MASK            (0x0000001F)

/** DOW register mask */
#define RTC_DOW_MASK            (0x00000007)

/** DOY register mask */
#define RTC_DOY_MASK            (0x000001FF)

/** MONTH register mask */
#define RTC_MONTH_MASK          (0x0000000F)

/** YEAR register mask */
#define RTC_YEAR_MASK           (0x00000FFF)


/** Maximum value of second */
#define RTC_SECOND_MAX      59

/** Maximum value of minute*/
#define RTC_MINUTE_MAX      59

/** Maximum value of hour*/
#define RTC_HOUR_MAX        23

/** Minimum value of month*/
#define RTC_MONTH_MIN       1

/** Maximum value of month*/
#define RTC_MONTH_MAX       12

/** Minimum value of day of month*/
#define RTC_DAYOFMONTH_MIN  1

/** Maximum value of day of month*/
#define RTC_DAYOFMONTH_MAX  31

/** Maximum value of day of week*/
#define RTC_DAYOFWEEK_MAX   6

/** Minimum value of day of year*/
#define RTC_DAYOFYEAR_MIN   1

/** Maximum value of day of year*/
#define RTC_DAYOFYEAR_MAX   366

/** Maximum value of year*/
#define RTC_YEAR_MAX        4095

/**********************************************************************
* Calibration register
**********************************************************************/
/** Calibration value */
#define RTC_CALIBRATION_CALVAL_MASK     ((0x1FFFF))

/** Calibration direction */
#define RTC_CALIBRATION_LIBDIR          ((1<<17))

/** Calibration max value */
#define RTC_CALIBRATION_MAX             ((0x20000))

/** Calibration definitions */
#define RTC_CALIB_DIR_FORWARD           ((uint8_t)(0))
#define RTC_CALIB_DIR_BACKWARD          ((uint8_t)(1))

/**********************************************************************
* Event Monitor/Recorder Control register
**********************************************************************/
#define RTC_ERCTRL_EV0_INTWAKE_ENABLE       (1<<0)
#define RTC_ERCTRL_EV0_GPCLEAR_ENABLE       (1<<1)
#define RTC_ERCTRL_EV0_POS_EDGE             (1<<2)
#define RTC_ERCTRL_EV0_NEG_EDGE             (0<<2)
#define RTC_ERCTRL_EV0_INPUT_ENABLE         (1<<3)

#define RTC_ERCTRL_EV1_INTWAKE_ENABLE       (1<<10)
#define RTC_ERCTRL_EV1_GPCLEAR_ENABLE       (1<<11)
#define RTC_ERCTRL_EV1_POS_EDGE             (1<<12)
#define RTC_ERCTRL_EV1_NEG_EDGE             (0<<12)
#define RTC_ERCTRL_EV1_INPUT_ENABLE         (1<<13)


#define RTC_ERCTRL_EV2_INTWAKE_ENABLE       (1<<20)
#define RTC_ERCTRL_EV2_GPCLEAR_ENABLE       (1<<21)
#define RTC_ERCTRL_EV2_POS_EDGE             (1<<22)
#define RTC_ERCTRL_EV2_NEG_EDGE             (0<<22)
#define RTC_ERCTRL_EV2_INPUT_ENABLE         (1<<23)

#define RTC_ERCTRL_MODE_MASK                (((uint32_t)3)<<30)
#define RTC_ERCTRL_MODE_CLK_DISABLE         (((uint32_t)0)<<30)
#define RTC_ERCTRL_MODE_16HZ                (((uint32_t)1)<<30)
#define RTC_ERCTRL_MODE_64HZ                (((uint32_t)2)<<30)
#define RTC_ERCTRL_MODE_1KHZ                (((uint32_t)3)<<30)

#define RTC_ER_INPUT_CHANNEL_NUM            (3)

/**********************************************************************
* Event Monitor/Recorder Status register
**********************************************************************/
#define RTC_ER_STATUS_EV0_BIT               (0)
#define RTC_ER_STATUS_EV1_BIT               (1)
#define RTC_ER_STATUS_EV2_BIT               (2)
#define RTC_ER_STATUS_GPCLEARED_BIT         (3)
#define RTC_ER_STATUS_WAKEUP_BIT            (31)

#define RTC_ER_EVENTS_ON_EV0_FLG            (1<<RTC_ER_STATUS_EV0_BIT)
#define RTC_ER_EVENTS_ON_EV1_FLG            (1<<RTC_ER_STATUS_EV1_BIT)
#define RTC_ER_EVENTS_ON_EV2_FLG            (1<<RTC_ER_STATUS_EV2_BIT)
#define RTC_ER_STATUS_GP_CLEARED_FLG        (1<<RTC_ER_STATUS_GPCLEARED_BIT)
#define RTC_ER_STATUS_WAKEUP_REQ_PENDING    (((uint32_t)1)<<RTC_ER_STATUS_WAKEUP_BIT)
/**********************************************************************
* Event Monitor/Recorder Counter register
**********************************************************************/
#define RTC_ER_EV0_COUNTER(n)               (n&0x07)
#define RTC_ER_EV1_COUNTER(n)               ((n>>8)&0x07)
#define RTC_ER_EV2_COUNTER(n)               ((n>>16)&0x07)

/**********************************************************************
* Event Monitor/Recorder TimeStamp register
**********************************************************************/
#define RTC_ER_TIMESTAMP_SEC(n)             (n&0x3F)
#define RTC_ER_TIMESTAMP_MIN(n)             ((n>>6)&0x3F)
#define RTC_ER_TIMESTAMP_HOUR(n)            ((n>>12)&0x1F)
#define RTC_ER_TIMESTAMP_DOY(n)             ((n>>17)&0x1FF)

/**
 * @}
 */


/* Public Types --------------------------------------------------------------- */
/** @defgroup RTC_Public_Types RTC Public Types
 * @{
 */

/** @brief Time structure definitions for easy manipulate the data */
typedef struct 
{
    /** Seconds Register */
    uint32_t SEC;
    /** Minutes Register */
    uint32_t MIN;
    /** Hours Register */
    uint32_t HOUR;
    /** Day of Month Register */
    uint32_t DOM;
    /** Day of Week Register */
    uint32_t DOW;
    /** Day of Year Register */
    uint32_t DOY;
    /** Months Register */
    uint32_t MONTH;
    /** Years Register */
    uint32_t YEAR;
} RTC_TIME_Type;

/** @brief RTC interrupt source */
typedef enum 
{
    /**  Counter Increment Interrupt */
    RTC_INT_COUNTER_INCREASE = RTC_IRL_RTCCIF,
    /** The alarm interrupt */
    RTC_INT_ALARM = RTC_IRL_RTCALF,
} RTC_INT_OPT;


/** @brief RTC time type option */
typedef enum 
{
    /** Second */
    RTC_TIMETYPE_SECOND = 0,
    /** Month */
    RTC_TIMETYPE_MINUTE = 1,
    /** Hour */
    RTC_TIMETYPE_HOUR = 2,
    /** Day of week */
    RTC_TIMETYPE_DAYOFWEEK = 3,
    /** Day of month */
    RTC_TIMETYPE_DAYOFMONTH = 4,
    /** Day of year */
    RTC_TIMETYPE_DAYOFYEAR = 5,
    /** Month */
    RTC_TIMETYPE_MONTH = 6,
    /** Year */
    RTC_TIMETYPE_YEAR = 7,
} RTC_TIMETYPE_Num;

/** @brief Event Monitor/Recording Input Channel configuration */
typedef struct
{
    Bool    EventOnPosEdge; // Event occurs on positive edge on the channel
    Bool    IntWake;        // Create interrupt and wake-up request if there is an event
    Bool    GPClear;        // Clear GP registers of RTC if there is an event.
} RTC_ER_CHANNEL_Init_Type;

/** @brief Event Monitor/Recording configuration */
typedef struct
{
    RTC_ER_CHANNEL_Init_Type InputChannel[RTC_ER_INPUT_CHANNEL_NUM];
    uint32_t                 Clk;   // Sample clock on input channel. (Hz)
} RTC_ER_CONFIG_Type;

/** @brief Event Monitor/Recording TimeStamp Type */
typedef struct 
{
    /** Seconds Register */
    uint32_t SEC;
    /** Minutes Register */
    uint32_t MIN;
    /** Hours Register */
    uint32_t HOUR;
    /** Day of Year Register */
    uint32_t DOY;
} RTC_ER_TIMESTAMP_Type;


/**
 * @}
 */



/* Public Functions ----------------------------------------------------------- */
/** @defgroup RTC_Public_Functions RTC Public Functions
 * @{
 */

void RTC_Init (LPC_RTC_TypeDef *RTCx);
void RTC_DeInit(LPC_RTC_TypeDef *RTCx);
void RTC_ResetClockTickCounter(LPC_RTC_TypeDef *RTCx);
void RTC_Cmd (LPC_RTC_TypeDef *RTCx, FunctionalState NewState);
void RTC_CntIncrIntConfig (LPC_RTC_TypeDef *RTCx, uint32_t CntIncrIntType, \
                                FunctionalState NewState);
void RTC_AlarmIntConfig (LPC_RTC_TypeDef *RTCx, uint32_t AlarmTimeType, \
                                FunctionalState NewState);
void RTC_SetTime (LPC_RTC_TypeDef *RTCx, uint32_t Timetype, uint32_t TimeValue);
uint32_t RTC_GetTime(LPC_RTC_TypeDef *RTCx, uint32_t Timetype);
void RTC_SetFullTime (LPC_RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime);
void RTC_GetFullTime (LPC_RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime);
void RTC_SetAlarmTime (LPC_RTC_TypeDef *RTCx, uint32_t Timetype, uint32_t ALValue);
uint32_t RTC_GetAlarmTime (LPC_RTC_TypeDef *RTCx, uint32_t Timetype);
void RTC_SetFullAlarmTime (LPC_RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime);
void RTC_GetFullAlarmTime (LPC_RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime);
IntStatus RTC_GetIntPending (LPC_RTC_TypeDef *RTCx, uint32_t IntType);
void RTC_ClearIntPending (LPC_RTC_TypeDef *RTCx, uint32_t IntType);
void RTC_CalibCounterCmd(LPC_RTC_TypeDef *RTCx, FunctionalState NewState);
void RTC_CalibConfig(LPC_RTC_TypeDef *RTCx, uint32_t CalibValue, uint8_t CalibDir);
void RTC_WriteGPREG (LPC_RTC_TypeDef *RTCx, uint8_t Channel, uint32_t Value);
uint32_t RTC_ReadGPREG (LPC_RTC_TypeDef *RTCx, uint8_t Channel);

void    RTC_ER_InitConfigStruct(RTC_ER_CONFIG_Type* pConfig);
Status  RTC_ER_Init(RTC_ER_CONFIG_Type* pConfig);
Status  RTC_ER_Cmd(uint8_t channel, FunctionalState state);
uint8_t RTC_ER_GetEventCount(uint8_t channel);
uint32_t RTC_ER_GetStatus(void);
Bool    RTC_ER_WakupReqPending(void);
Bool    RTC_ER_GPCleared(void);
Status  RTC_ER_GetFirstTimeStamp(uint8_t channel, RTC_ER_TIMESTAMP_Type* pTimeStamp);
Status  RTC_ER_GetLastTimeStamp(uint8_t channel, RTC_ER_TIMESTAMP_Type* pTimeStamp);
void    RTC_ER_ClearStatus(uint32_t status);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __LPC_RTC_H_ */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
