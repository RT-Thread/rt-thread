/**
  ******************************************************************************
  * @file         ft32f4xx_epwm.h
  * @author       FMD AE
  * @brief        This file contains all the functions prototypes for the EPWM
  *               firmware library.
  * @version      V1.0.0
  * @data         2025-03-25
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_EPWM_H
#define __FT32F4XX_EPWM_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"

/** @addtogroup EPWM
  * @{
  */




/* Exported types ------------------------------------------------------------*/

/**
  * @brief Enumeration to define the pulse width modulation (PWM) action
  */
typedef enum
{
    EPWM_ActionQual_Disabled = 0,
    EPWM_ActionQual_Clear,
    EPWM_ActionQual_Set,
    EPWM_ActionQual_Toggle
} EPWM_ActionQual_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) high speed
  */
typedef enum
{
    EPWM_HspClkDiv_by_1 = (0 << 7),
    EPWM_HspClkDiv_by_2 = (1 << 7),
    EPWM_HspClkDiv_by_4 = (2 << 7),
    EPWM_HspClkDiv_by_6 = (3 << 7),
    EPWM_HspClkDiv_by_8 = (4 << 7),
    EPWM_HspClkDiv_by_10 = (5 << 7),
    EPWM_HspClkDiv_by_12 = (6 << 7),
    EPWM_HspClkDiv_by_14 = (7 << 7)
} EPWM_HspClkDiv_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) clock
  */
typedef enum
{
    EPWM_ClkDiv_by_1 = (0 << 10),
    EPWM_ClkDiv_by_2 = (1 << 10),
    EPWM_ClkDiv_by_4 = (2 << 10),
    EPWM_ClkDiv_by_8 = (3 << 10),
    EPWM_ClkDiv_by_16 = (4 << 10),
    EPWM_ClkDiv_by_32 = (5 << 10),
    EPWM_ClkDiv_by_64 = (6 << 10),
    EPWM_ClkDiv_by_128 = (7 << 10)
} EPWM_ClkDiv_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) chopping
  */
typedef enum
{
    EPWM_ChoppingClkFreq_SysClkOut_by_1 = (0 << 5),
    EPWM_ChoppingClkFreq_SysClkOut_by_2 = (1 << 5),
    EPWM_ChoppingClkFreq_SysClkOut_by_3 = (2 << 5),
    EPWM_ChoppingClkFreq_SysClkOut_by_4 = (3 << 5),
    EPWM_ChoppingClkFreq_SysClkOut_by_5 = (4 << 5),
    EPWM_ChoppingClkFreq_SysClkOut_by_6 = (5 << 5),
    EPWM_ChoppingClkFreq_SysClkOut_by_7 = (6 << 5),
    EPWM_ChoppingClkFreq_SysClkOut_by_8 = (7 << 5)
} EPWM_ChoppingClkFreq_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) chopping
  */
typedef enum
{
    EPWM_ChoppingDutyCycle_One_Eighth = (0 << 8),
    EPWM_ChoppingDutyCycle_Two_Eighths = (1 << 8),
    EPWM_ChoppingDutyCycle_Three_Eighths = (2 << 8),
    EPWM_ChoppingDutyCycle_Four_Eighths = (3 << 8),
    EPWM_ChoppingDutyCycle_Five_Eighths = (4 << 8),
    EPWM_ChoppingDutyCycle_Six_Eighths = (5 << 8),
    EPWM_ChoppingDutyCycle_Seven_Eighths = (6 << 8)
} EPWM_ChoppingDutyCycle_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) chopping
  */
typedef enum
{
    EPWM_ChoppingPulseWidth_One_Eighth_SysClkOut = (0 << 1),
    EPWM_ChoppingPulseWidth_Two_Eighths_SysClkOut = (1 << 1),
    EPWM_ChoppingPulseWidth_Three_Eighths_SysClkOut = (2 << 1),
    EPWM_ChoppingPulseWidth_Four_Eighths_SysClkOut = (3 << 1),
    EPWM_ChoppingPulseWidth_Five_Eighths_SysClkOut = (4 << 1),
    EPWM_ChoppingPulseWidth_Six_Eighths_SysClkOut = (5 << 1),
    EPWM_ChoppingPulseWidth_Seven_Eighths_SysClkOut = (6 << 1),
    EPWM_ChoppingPulseWidth_Eight_Eighths_SysClkOut = (7 << 1),
    EPWM_ChoppingPulseWidth_Nine_Eighths_SysClkOut = (8 << 1),
    EPWM_ChoppingPulseWidth_Ten_Eighths_SysClkOut = (9 << 1),
    EPWM_ChoppingPulseWidth_Eleven_Eighths_SysClkOut = (10 << 1),
    EPWM_ChoppingPulseWidth_Twelve_Eighths_SysClkOut = (11 << 1),
    EPWM_ChoppingPulseWidth_Thirteen_Eighths_SysClkOut = (12 << 1),
    EPWM_ChoppingPulseWidth_Fourteen_Eighths_SysClkOut = (13 << 1),
    EPWM_ChoppingPulseWidth_Fifteen_Eighths_SysClkOut = (14 << 1),
    EPWM_ChoppingPulseWidth_Sixteen_Eighths_SysClkOut = (15 << 1)
} EPWM_ChoppingPulseWidth_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) counter modes
  */
typedef enum
{
    EPWM_CounterMode_Up = (0 << 0),
    EPWM_CounterMode_Down = (1 << 0),
    EPWM_CounterMode_UpDown = (2 << 0),
    EPWM_CounterMode_Stop = (3 << 0)
} EPWM_CounterMode_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) deadband
  */
typedef enum
{
    EPWM_DeadBandInputMode_EPWMxA_Rising_and_Falling = (0 << 4),
    EPWM_DeadBandInputMode_EPWMxA_Falling_EPWMxB_Rising = (1 << 4),
    EPWM_DeadBandInputMode_EPWMxA_Rising_EPWMxB_Falling = (2 << 4),
    EPWM_DeadBandInputMode_EPWMxB_Rising_and_Falling = (3 << 4)
} EPWM_DeadBandInputMode_e;


/**
  * @brief Enumeration to define the pulse width modulation (PWM) deadband
  */
typedef enum
{
    EPWM_DeadBandOutputMode_Bypass = (0 << 0),
    EPWM_DeadBandOutputMode_EPWMxA_Disable_EPWMxB_Falling = (1 << 0),
    EPWM_DeadBandOutputMode_EPWMxA_Rising_EPWMxB_Disable = (2 << 0),
    EPWM_DeadBandOutputMode_EPWMxA_Rising_EPWMxB_Falling = (3 << 0)
} EPWM_DeadBandOutputMode_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) deadband
  */
typedef enum
{
    EPWM_DeadBandPolarity_EPWMxA_EPWMxB = (0 << 2),
    EPWM_DeadBandPolarity_EPWMxA_Inverted = (1 << 2),
    EPWM_DeadBandPolarity_EPWMxB_Inverted = (2 << 2),
    EPWM_DeadBandPolarity_EPWMxA_Inverted_EPWMxB_Inverted = (3 << 2)
} EPWM_DeadBandPolarity_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) digital
  */
typedef enum
{
    EPWM_DigitalCompare_A_High = 0,
    EPWM_DigitalCompare_A_Low = 4,
    EPWM_DigitalCompare_B_High = 8,
    EPWM_DigitalCompare_B_Low = 12
} EPWM_DigitalCompare_Input_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) digital
  */
typedef enum
{
    EPWM_DigitalCompare_InputSel_TZ1 = (0 << 0),
    EPWM_DigitalCompare_InputSel_TZ2 = (1 << 0),
    EPWM_DigitalCompare_InputSel_TZ3 = (2 << 0),
    EPWM_DigitalCompare_InputSel_COMP1OUT = (8 << 0),
    EPWM_DigitalCompare_InputSel_COMP2OUT = (9 << 0),
    EPWM_DigitalCompare_InputSel_COMP3OUT = (10 << 0)
} EPWM_DigitalCompare_InputSel_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) digital
  */
typedef enum
{
    EPWM_DigitalCompare_FilterSrc_DCAEVT1 = 0,
    EPWM_DigitalCompare_FilterSrc_DCAEVT2,
    EPWM_DigitalCompare_FilterSrc_DCBEVT1,
    EPWM_DigitalCompare_FilterSrc_DCBEVT2
} EPWM_DigitalCompare_FilterSrc_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) digital
  */
typedef enum
{
    EPWM_DigitalCompare_PulseSel_CTRPRD = 0,
    EPWM_DigitalCompare_PulseSel_CTR0
} EPWM_DigitalCompare_PulseSel_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) high
  */
typedef enum
{
    EPWM_HrControlMode_Duty = (0 << 2),
    EPWM_HrControlMode_Phase = (1 << 2)
} EPWM_HrControlMode_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) high
  */
typedef enum
{
    EPWM_HrEdgeMode_Disabled = (0 << 0),
    EPWM_HrEdgeMode_Rising = (1 << 0),
    EPWM_HrEdgeMode_Falling = (2 << 0),
    EPWM_HrEdgeMode_Both = (3 << 0)
} EPWM_HrEdgeMode_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) high
  */
typedef enum
{
    EPWM_HrShadowMode_CTR_EQ_0 = (0 << 3),
    EPWM_HrShadowMode_CTR_EQ_PRD = (1 << 3),
    EPWM_HrShadowMode_CTR_EQ_0_OR_PRD = (2 << 3)
} EPWM_HrShadowMode_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) interrupt
  */
typedef enum
{
    EPWM_IntMode_CounterEqualZero = (1 << 0),
    EPWM_IntMode_CounterEqualPeriod = (2 << 0),
    EPWM_IntMode_CounterEqualZeroOrPeriod = (3 << 0),
    EPWM_IntMode_CounterEqualCmpAIncr = (4 << 0),
    EPWM_IntMode_CounterEqualCmpADecr = (5 << 0),
    EPWM_IntMode_CounterEqualCmpBIncr = (6 << 0),
    EPWM_IntMode_CounterEqualCmpBDecr = (7 << 0)
} EPWM_IntMode_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) interrupt
  */
typedef enum
{
    EPWM_IntPeriod_Disable = (0 << 0),
    EPWM_IntPeriod_FirstEvent = (1 << 0),
    EPWM_IntPeriod_SecondEvent = (2 << 0),
    EPWM_IntPeriod_ThirdEvent = (3 << 0)
} EPWM_IntPeriod_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) load modes
  */
typedef enum
{
    EPWM_LoadMode_Zero = 0,
    EPWM_LoadMode_Period,
    EPWM_LoadMode_Either,
    EPWM_LoadMode_Freeze
} EPWM_LoadMode_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) numbers
  */
typedef enum
{
    EPWM_Number_1 = 0,
    EPWM_Number_2,
    EPWM_Number_3,
    EPWM_Number_4,
    EPWM_Number_5,
    EPWM_Number_6,
    EPWM_Number_7
} EPWM_Number_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) period load
  */
typedef enum
{
    EPWM_PeriodLoad_Shadow = (0 << 3),
    EPWM_PeriodLoad_Immediate = (1 << 3)
} EPWM_PeriodLoad_e;


/**
  * @brief Enumeration to define the pulse width modulation (PWM) phase
  */
typedef enum
{
    EPWM_PhaseDir_CountDown = (0 << 13),
    EPWM_PhaseDir_CountUp = (1 << 13)
} EPWM_PhaseDir_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) run modes
  */
//typedef enum
//{
//    EPWM_RunMode_SoftStopAfterIncr=(0 << 14),
//    EPWM_RunMode_SoftStopAfterDecr=(0 << 14),
//    EPWM_RunMode_SoftStopAfterCycle=(1 << 14),
//    EPWM_RunMode_FreeRun=(2 << 14)
//} EPWM_RunMode_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) shadow modes
  */
typedef enum
{
    EPWM_ShadowMode_Shadow = 0,
    EPWM_ShadowMode_Immediate
} EPWM_ShadowMode_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) shadow status
  */
typedef enum
{
    EPWM_ShadowStatus_NotFull = 0,
    EPWM_ShadowStatus_Full
} EPWM_ShadowStatus_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) start of
  */
typedef enum
{
    EPWM_SocPeriod_Disable = 0,
    EPWM_SocPeriod_FirstEvent,
    EPWM_SocPeriod_SecondEvent,
    EPWM_SocPeriod_ThirdEvent
} EPWM_SocPeriod_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) start of
  */
typedef enum
{
    EPWM_SocPulseSrc_DcEvt = 0,
    EPWM_SocPulseSrc_CounterEqualZero,
    EPWM_SocPulseSrc_CounterEqualPeriod,
    EPWM_SocPulseSrc_CounterEqualZeroOrPeriod,
    EPWM_SocPulseSrc_CounterEqualCmpAIncr,
    EPWM_SocPulseSrc_CounterEqualCmpADecr,
    EPWM_SocPulseSrc_CounterEqualCmpBIncr,
    EPWM_SocPulseSrc_CounterEqualCmpBDecr
} EPWM_SocPulseSrc_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) sync modes
  */
typedef enum
{
    EPWM_SyncMode_EPWMxSYNC = (0 << 4),
    EPWM_SyncMode_CounterEqualZero = (1 << 4),
    EPWM_SyncMode_CounterEqualCounterCompareZero = (2 << 4),
    EPWM_SyncMode_Disable = (3 << 4)
} EPWM_SyncMode_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) trip zone
  */
typedef enum
{
    EPWM_TripZoneSrc_CycleByCycle_TZ1_NOT = (1 << 0),
    EPWM_TripZoneSrc_CycleByCycle_TZ2_NOT = (1 << 1),
    EPWM_TripZoneSrc_CycleByCycle_TZ3_NOT = (1 << 2),
    EPWM_TripZoneSrc_CycleByCycle_TZ4_NOT = (1 << 3),
    EPWM_TripZoneSrc_CycleByCycle_TZ5_NOT = (1 << 4),
    EPWM_TripZoneSrc_CycleByCycle_TZ6_NOT = (1 << 5),
    EPWM_TripZoneSrc_CycleByCycle_CmpA = (1 << 6),
    EPWM_TripZoneSrc_CycleByCycle_CmpB = (1 << 7),
    EPWM_TripZoneSrc_OneShot_TZ1_NOT = (1 << 8),
    EPWM_TripZoneSrc_OneShot_TZ2_NOT = (1 << 9),
    EPWM_TripZoneSrc_OneShot_TZ3_NOT = (1 << 10),
    EPWM_TripZoneSrc_OneShot_TZ4_NOT = (1 << 11),
    EPWM_TripZoneSrc_OneShot_TZ5_NOT = (1 << 12),
    EPWM_TripZoneSrc_OneShot_TZ6_NOT = (1 << 13),
    EPWM_TripZoneSrc_OneShot_CmpA = (1 << 14),
    EPWM_TripZoneSrc_OneShot_CmpB = (1 << 15)
} EPWM_TripZoneSrc_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) trip zone
  */
typedef enum
{
    EPWM_TripZoneState_HighImp = 0,
    EPWM_TripZoneState_EPWM_High,
    EPWM_TripZoneState_EPWM_Low,
    EPWM_TripZoneState_DoNothing
} EPWM_TripZoneState_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) trip zone
  */
typedef enum
{
    EPWM_TripZoneFlag_Global = (1 << 0),    //!< Global Trip Zone flag
    EPWM_TripZoneFlag_CBC = (1 << 1),       //!< Cycle by cycle Trip Zone flag
    EPWM_TripZoneFlag_OST = (1 << 2),       //!< One Shot Trip Zone flag
    EPWM_TripZoneFlag_DCAEVT1 = (1 << 3),   //!< Digital Compare A Event 1 Trip Zone flag
    EPWM_TripZoneFlag_DCAEVT2 = (1 << 4),   //!< Digital Compare A Event 2 Trip Zone flag
    EPWM_TripZoneFlag_DCBEVT1 = (1 << 5),   //!< Digital Compare B Event 1 Trip Zone flag
    EPWM_TripZoneFlag_DCBEVT2 = (1 << 6)    //!< Digital Compare B Event 2 Trip Zone flag
} EPWM_TripZoneFlag_e;

/**
  * @brief Enumeration to define the pulse width modulation (PWM) trip zone
  */
typedef enum
{
    EPWM_TripZoneDCEventSel_Disabled = (0 << 0),       //!< Event Disabled
    EPWM_TripZoneDCEventSel_DCxHL_DCxLX = (1 << 0),    //!< Compare H = Low, Compare L = Don't Care
    EPWM_TripZoneDCEventSel_DCxHH_DCxLX = (2 << 0),    //!< Compare H = High, Compare L = Don't Care
    EPWM_TripZoneDCEventSel_DCxHX_DCxLL = (3 << 0),    //!< Compare H = Don't Care, Compare L = Low
    EPWM_TripZoneDCEventSel_DCxHX_DCxLH = (4 << 0),    //!< Compare H = Don't Care, Compare L = High
    EPWM_TripZoneDCEventSel_DCxHL_DCxLH = (5 << 0)     //!< Compare H = Low, Compare L = High
} EPWM_TripZoneDCEventSel_e;







/* Exported constants --------------------------------------------------------*/

#define EPWM_AQCTL_ZRO_BITS              (3 << 0)
#define EPWM_AQCTL_PRD_BITS              (3 << 2)
#define EPWM_AQCTL_CAU_BITS              (3 << 4)
#define EPWM_AQCTL_CAD_BITS              (3 << 6)
#define EPWM_AQCTL_CBU_BITS              (3 << 8)
#define EPWM_AQCTL_CBD_BITS              (3 << 10)
#define EPWM_CMPCTL_LOADAMODE_BITS       (3 << 0)
#define EPWM_CMPCTL_LOADBMODE_BITS       (3 << 2)
#define EPWM_CMPCTL_SHDWAMODE_BITS       (1 << 4)
#define EPWM_CMPCTL_SHDWBMODE_BITS       (1 << 6)
#define EPWM_CMPCTL_SHDWAFULL_BITS       (1 << 5)
#define EPWM_CMPCTL_SHDWBFULL_BITS       (1 << 7)
#define EPWM_DBCTL_OUTMODE_BITS          (3 << 0)
#define EPWM_DBCTL_POLSEL_BITS           (3 << 2)
#define EPWM_DBCTL_INMODE_BITS           (3 << 4)
#define EPWM_DBCTL_HALFCYCLE_BITS        (1 << 15)
#define EPWM_ETCLR_INT_BITS              (1 << 0)
#define EPWM_ETCLR_SOCA_BITS             (1 << 2)
#define EPWM_ETCLR_SOCB_BITS             (1 << 3)
#define EPWM_ETPS_INTPRD_BITS            (3 << 0)
#define EPWM_ETPS_INTCNT_BITS            (3 << 2)
#define EPWM_ETPS_SOCAPRD_BITS           (3 << 8)
#define EPWM_ETPS_SOCACNT_BITS           (3 << 10)
#define EPWM_ETPS_SOCBPRD_BITS           (3 << 12)
#define EPWM_ETPS_SOCBCNT_BITS           (3 << 14)
#define EPWM_ETSEL_INTSEL_BITS           (7 << 0)
#define EPWM_ETSEL_INTEN_BITS            (1 << 3)
#define EPWM_ETSEL_SOCASEL_BITS          (7 << 8)
#define EPWM_ETSEL_SOCAEN_BITS           (1 << 11)
#define EPWM_ETSEL_SOCBSEL_BITS          (7 << 12)
#define EPWM_ETSEL_SOCBEN_BITS           (1 << 15)
#define EPWM_PCCTL_CHPEN_BITS            (1 << 0)
#define EPWM_PCCTL_OSHTWTH_BITS          (15 << 1)
#define EPWM_PCCTL_CHPFREQ_BITS          (7 << 5)
#define EPWM_PCCTL_CHPDUTY_BITS          (7 << 8)
#define EPWM_HRCNFG_EDGMODE_BITS         (3 << 0)
#define EPWM_HRCNFG_CTLMODE_BITS         (1 << 2)
#define EPWM_HRCNFG_HRLOAD_BITS          (3 << 3)
#define EPWM_HRCNFG_SELOUTB_BITS         (1 << 5)
#define EPWM_HRCNFG_AUTOCONV_BITS        (1 << 6)
#define EPWM_HRCNFG_SWAPAB_BITS          (1 << 7)
#define EPWM_HRPPWR_MEPOFF_BITS          (1 << 0)
#define EPWM_HRPPWR_MEPSFO_BITS          (1 << 1)
#define EPWM_HRPCTL_HRPE_BITS            (1 << 0)
#define EPWM_HRPCTL_EPWMSYNCSEL_BITS     (1 << 1)
#define EPWM_HRPCTL_TBPHSHRLOADE_BITS    (1 << 2)
#define EPWM_TBCTL_CTRMODE_BITS          (3 << 0)
#define EPWM_TBCTL_PHSEN_BITS            (1 << 2)
#define EPWM_TBCTL_PRDLD_BITS            (1 << 3)
#define EPWM_TBCTL_SYNCOSEL_BITS         (3 << 4)
#define EPWM_TBCTL_SWFSYNC_BITS          (1 << 6)
#define EPWM_TBCTL_HSPCLKDIV_BITS        (7 << 7)
#define EPWM_TBCTL_CLKDIV_BITS           (7 << 10)
#define EPWM_TBCTL_PHSDIR_BITS           (1 << 13)
#define EPWM_TBCTL_FREESOFT_BITS         (3 << 14)
#define EPWM_TZCLR_INT_BITS              (1 << 0)
#define EPWM_TZCLR_CBC_BITS              (1 << 1)
#define EPWM_TZCLR_OST_BITS              (1 << 2)
#define EPWM_TZCLR_DCAEVT1_BITS          (1 << 3)
#define EPWM_TZCLR_DCAEVT2_BITS          (1 << 4)
#define EPWM_TZCLR_DCBEVT1_BITS          (1 << 5)
#define EPWM_TZCLR_DCBEVT2_BITS          (1 << 6)
#define EPWM_TZCTL_TZA_BITS              (3 << 0)
#define EPWM_TZCTL_TZB_BITS              (3 << 2)
#define EPWM_TZCTL_DCAEVT1_BITS          (3 << 4)
#define EPWM_TZCTL_DCAEVT2_BITS          (3 << 6)
#define EPWM_TZCTL_DCBEVT1_BITS          (3 << 8)
#define EPWM_TZCTL_DCBEVT2_BITS          (3 << 10)
#define EPWM_TZFRC_CBC_BITS              (1 << 1)
#define EPWM_TZFRC_OST_BITS              (1 << 2)
#define EPWM_TZFRC_DCAEVT1_BITS          (1 << 3)
#define EPWM_TZFRC_DCAEVT2_BITS          (1 << 4)
#define EPWM_TZFRC_DCBEVT1_BITS          (1 << 5)
#define EPWM_TZFRC_DCBEVT2_BITS          (1 << 6)
#define EPWM_TZDCSEL_DCAEVT1_BITS        (7 << 0)
#define EPWM_TZDCSEL_DCAEVT2_BITS        (7 << 3)
#define EPWM_TZDCSEL_DCBEVT1_BITS        (7 << 6)
#define EPWM_TZDCSEL_DCBEVT2_BITS        (7 << 9)
#define EPWM_DCTRIPSEL_DCAHCOMPSEL_BITS  (15 << 0)
#define EPWM_DCTRIPSEL_DCALCOMPSEL_BITS  (15 << 4)
#define EPWM_DCTRIPSEL_DCBHCOMPSEL_BITS  (15 << 8)
#define EPWM_DCTRIPSEL_DCBLCOMPSEL_BITS  (15 << 12)
#define EPWM_DCFCTL_SRCSEL_BITS          (3 << 0)
#define EPWM_DCFCTL_BLANKE_BITS          (1 << 2)
#define EPWM_DCFCTL_BLANKINV_BITS        (1 << 3)
#define EPWM_DCFCTL_PULSESEL_BITS        (3 << 4)


#define EPWM_TBCTL_EALLOW_BITS             TBCTL_EALLOW
#define EPWM_MEP_INT_BITS                  MEPINT_MEPCAL

/** @defgroup EPWM_TZ_flags_definition
  * @{
  */

#define EPWM_TZ_FLAG_INT          TZFLG_INT
#define EPWM_TZ_FLAG_CBC          TZFLG_CBC
#define EPWM_TZ_FLAG_OST          TZFLG_OST
#define EPWM_TZ_FLAG_DCAEVT1      TZFLG_DCAEVT1
#define EPWM_TZ_FLAG_DCAEVT2      TZFLG_DCAEVT2
#define EPWM_TZ_FLAG_DCBEVT1      TZFLG_DCBEVT1
#define EPWM_TZ_FLAG_DCBEVT2      TZFLG_DCBEVT2

#define IS_EPWM_TZ_GET_FLAG(FLAG) (((FLAG) == EPWM_TZ_FLAG_INT)     || \
                                   ((FLAG) == EPWM_TZ_FLAG_CBC)     || \
                                   ((FLAG) == EPWM_TZ_FLAG_OST)     || \
                                   ((FLAG) == EPWM_TZ_FLAG_DCAEVT1) || \
                                   ((FLAG) == EPWM_TZ_FLAG_DCAEVT2) || \
                                   ((FLAG) == EPWM_TZ_FLAG_DCBEVT1) || \
                                   ((FLAG) == EPWM_TZ_FLAG_DCBEVT2))
/**
  * @}
  */



/** @defgroup EPWM_ET_flags_definition
  * @{
  */
#define EPWM_ET_FLAG_INT          ETFLG_INT
#define EPWM_ET_FLAG_SOCA         ETFLG_SOCA
#define EPWM_ET_FLAG_SOCB         ETFLG_SOCB

#define IS_EPWM_ET_GET_FLAG(FLAG) (((FLAG) == EPWM_ET_FLAG_INT)  || \
                                   ((FLAG) == EPWM_ET_FLAG_SOCA) || \
                                   ((FLAG) == EPWM_ET_FLAG_SOCB))
/**
  * @}
  */


/** @defgroup EPWM_MEP_flags_definition
  * @{
  */

#define EPWM_MEP_FLAG_INT         MEPFLG_MEPCAL

#define IS_EPWM_MEP_GET_FLAG(FLAG) ((FLAG) == EPWM_MEP_FLAG_INT)
/**
  * @}
  */




/**
  * @brief Defines the pulse width modulation (PWM) handle
  */
typedef struct _EPWM_Obj_ *EPWM_Handle;


/* Exported functions ------------------------------------------------------- */

/* Time-Base Configuration functions *********************************/
void EALLOW(EPWM_TypeDef* EPWMx);
void EDIS(EPWM_TypeDef* EPWMx);
void EPWM_setPhaseDir(EPWM_TypeDef* EPWMx, const EPWM_PhaseDir_e phaseDir);
void EPWM_setClkDiv(EPWM_TypeDef* EPWMx, const EPWM_ClkDiv_e clkDiv);
void EPWM_setHighSpeedClkDiv(EPWM_TypeDef* EPWMx, const EPWM_HspClkDiv_e clkDiv);
void EPWM_setSwSync(EPWM_TypeDef* EPWMx);
void EPWM_forceSync(EPWM_TypeDef* EPWMx);
void EPWM_setSyncMode(EPWM_TypeDef* EPWMx, const EPWM_SyncMode_e syncMode);
void EPWM_setPeriodLoad(EPWM_TypeDef* EPWMx, const EPWM_PeriodLoad_e periodLoad);
void EPWM_disableCounterLoad(EPWM_TypeDef* EPWMx);
void EPWM_enableCounterLoad(EPWM_TypeDef* EPWMx);
void EPWM_setCounterMode(EPWM_TypeDef* EPWMx, const EPWM_CounterMode_e counterMode);

void EPWM_setCount(EPWM_TypeDef* EPWMx, const uint16_t count);
void EPWM_setPeriod(EPWM_TypeDef* EPWMx, const uint16_t period);
void EPWM_setPeriodHr(EPWM_TypeDef* EPWMx, const uint16_t period);
void EPWM_setPhase(EPWM_TypeDef* EPWMx, const uint16_t phase);
//void EPWM_setRunMode(EPWM_TypeDef* EPWMx, const EPWM_RunMode_e runMode);

uint16_t EPWM_getPeriod(EPWM_TypeDef* EPWMx);


/* Counter-Compare Configuration functions *********************************/
void EPWM_setCmpA(EPWM_TypeDef* EPWMx, const uint16_t pwmData);
void EPWM_setCmpB(EPWM_TypeDef* EPWMx, const uint16_t pwmData);
void EPWM_setCmpAHr(EPWM_TypeDef* EPWMx, const uint16_t pwmData);
void EPWM_write_CmpA(EPWM_TypeDef* EPWMx, const int16_t pwmData);
void EPWM_write_CmpB(EPWM_TypeDef* EPWMx, const int16_t pwmData);
void EPWM_setShadowMode_CmpA(EPWM_TypeDef* EPWMx, const EPWM_ShadowMode_e shadowMode);
void EPWM_setShadowMode_CmpB(EPWM_TypeDef* EPWMx, const EPWM_ShadowMode_e shadowMode);
void EPWM_setLoadMode_CmpA(EPWM_TypeDef* EPWMx, const EPWM_LoadMode_e loadMode);
void EPWM_setLoadMode_CmpB(EPWM_TypeDef* EPWMx, const EPWM_LoadMode_e loadMode);

uint16_t EPWM_getCmpA(EPWM_TypeDef* EPWMx);
uint16_t EPWM_getCmpAHr(EPWM_TypeDef* EPWMx);
uint16_t EPWM_getCmpB(EPWM_TypeDef* EPWMx);


//EPWM_Handle EPWM_init(void *pMemory, const size_t numBytes);


/* Action-Qualifier Configuration functions *********************************/
void EPWM_setActionQual_CntDown_CmpA_PwmA(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual);
void EPWM_setActionQual_CntDown_CmpA_PwmB(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual);
void EPWM_setActionQual_CntDown_CmpB_PwmA(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual);
void EPWM_setActionQual_CntDown_CmpB_PwmB(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual);
void EPWM_setActionQual_CntUp_CmpA_PwmA(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual);
void EPWM_setActionQual_CntUp_CmpA_PwmB(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual);
void EPWM_setActionQual_CntUp_CmpB_PwmA(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual);
void EPWM_setActionQual_CntUp_CmpB_PwmB(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual);
void EPWM_setActionQual_Period_PwmA(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual);
void EPWM_setActionQual_Period_PwmB(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual);
void EPWM_setActionQual_Zero_PwmA(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual);
void EPWM_setActionQual_Zero_PwmB(EPWM_TypeDef* EPWMx, const EPWM_ActionQual_e actionQual);


/* PWM-Chopper Configuration functions *********************************/
void EPWM_enableChopping(EPWM_TypeDef* EPWMx);
void EPWM_disableChopping(EPWM_TypeDef* EPWMx);
void EPWM_setChoppingClkFreq(EPWM_TypeDef* EPWMx, const EPWM_ChoppingClkFreq_e clkFreq);
void EPWM_setChoppingDutyCycle(EPWM_TypeDef* EPWMx, const EPWM_ChoppingDutyCycle_e dutyCycle);
void EPWM_setChoppingPulseWidth(EPWM_TypeDef* EPWMx, const EPWM_ChoppingPulseWidth_e pulseWidth);


/* Dead-Band Configuration functions *********************************/
void EPWM_decrementDeadBandFallingEdgeDelay(EPWM_TypeDef* EPWMx);
void EPWM_decrementDeadBandRisingEdgeDelay(EPWM_TypeDef* EPWMx);
void EPWM_setDeadBandFallingEdgeDelay(EPWM_TypeDef* EPWMx, const uint16_t delay);
void EPWM_setDeadBandInputMode(EPWM_TypeDef* EPWMx, const EPWM_DeadBandInputMode_e inputMode);
void EPWM_setDeadBandOutputMode(EPWM_TypeDef* EPWMx, const EPWM_DeadBandOutputMode_e outputMode);
void EPWM_setDeadBandPolarity(EPWM_TypeDef* EPWMx, const EPWM_DeadBandPolarity_e polarity);
void EPWM_setDeadBandRisingEdgeDelay(EPWM_TypeDef* EPWMx, const uint16_t delay);
void EPWM_disableDeadBand(EPWM_TypeDef* EPWMx);
void EPWM_disableDeadBandHalfCycle(EPWM_TypeDef* EPWMx);
void EPWM_enableDeadBandHalfCycle(EPWM_TypeDef* EPWMx);
void EPWM_incrementDeadBandFallingEdgeDelay(EPWM_TypeDef* EPWMx);
void EPWM_incrementDeadBandRisingEdgeDelay(EPWM_TypeDef* EPWMx);

uint16_t EPWM_getDeadBandFallingEdgeDelay(EPWM_TypeDef* EPWMx);
uint16_t EPWM_getDeadBandRisingEdgeDelay(EPWM_TypeDef* EPWMx);


/* Trip-Zone Configuration functions *********************************/
void EPWM_setTripZoneFilter(EPWM_TypeDef* EPWMx, uint8_t FILTER);
void EPWM_setTripZoneDCEventSelect_DCAEVT1(EPWM_TypeDef* EPWMx, const EPWM_TripZoneDCEventSel_e tripZoneEvent);
void EPWM_setTripZoneDCEventSelect_DCAEVT2(EPWM_TypeDef* EPWMx, const EPWM_TripZoneDCEventSel_e tripZoneEvent);
void EPWM_setTripZoneDCEventSelect_DCBEVT1(EPWM_TypeDef* EPWMx, const EPWM_TripZoneDCEventSel_e tripZoneEvent);
void EPWM_setTripZoneDCEventSelect_DCBEVT2(EPWM_TypeDef* EPWMx, const EPWM_TripZoneDCEventSel_e tripZoneEvent);
void EPWM_setTripZoneState_DCAEVT1(EPWM_TypeDef* EPWMx, const EPWM_TripZoneState_e tripZoneState);
void EPWM_setTripZoneState_DCAEVT2(EPWM_TypeDef* EPWMx, const EPWM_TripZoneState_e tripZoneState);
void EPWM_setTripZoneState_DCBEVT1(EPWM_TypeDef* EPWMx, const EPWM_TripZoneState_e tripZoneState);
void EPWM_setTripZoneState_DCBEVT2(EPWM_TypeDef* EPWMx, const EPWM_TripZoneState_e tripZoneState);
void EPWM_setTripZoneState_TZA(EPWM_TypeDef* EPWMx, const EPWM_TripZoneState_e tripZoneState);
void EPWM_setTripZoneState_TZB(EPWM_TypeDef* EPWMx, const EPWM_TripZoneState_e tripZoneState);
void EPWM_setOneShotTrip(EPWM_TypeDef* EPWMx);
void EPWM_clearOneShotTrip(EPWM_TypeDef* EPWMx);
void EPWM_clearTripZone(EPWM_TypeDef* EPWMx, const EPWM_TripZoneFlag_e tripZoneFlag);
void EPWM_disableTripZones(EPWM_TypeDef* EPWMx);
void EPWM_disableTripZoneInt(EPWM_TypeDef* EPWMx, const EPWM_TripZoneFlag_e interruptSource);
void EPWM_disableTripZoneSrc(EPWM_TypeDef* EPWMx, const EPWM_TripZoneSrc_e src);
void EPWM_enableTripZoneInt(EPWM_TypeDef* EPWMx, const EPWM_TripZoneFlag_e interruptSource);
void EPWM_enableTripZoneSrc(EPWM_TypeDef* EPWMx, const EPWM_TripZoneSrc_e src);

FlagStatus EPWM_TripZone_GetFlagStatus(EPWM_TypeDef* EPWMx, uint16_t TZ_FLAG);


/* Event-Trigger Configuration functions *********************************/
void EPWM_clearIntFlag(EPWM_TypeDef* EPWMx);
void EPWM_clearSocAFlag(EPWM_TypeDef* EPWMx);
void EPWM_clearSocBFlag(EPWM_TypeDef* EPWMx);
void EPWM_setSocAPeriod(EPWM_TypeDef* EPWMx, const EPWM_SocPeriod_e intPeriod);
void EPWM_setSocAPulseSrc(EPWM_TypeDef* EPWMx, const EPWM_SocPulseSrc_e pulseSrc);
void EPWM_setSocBPeriod(EPWM_TypeDef* EPWMx, const EPWM_SocPeriod_e intPeriod);
void EPWM_setSocBPulseSrc(EPWM_TypeDef* EPWMx, const EPWM_SocPulseSrc_e pulseSrc);
void EPWM_setIntMode(EPWM_TypeDef* EPWMx, const EPWM_IntMode_e intMode);
void EPWM_setIntPeriod(EPWM_TypeDef* EPWMx, const EPWM_IntPeriod_e intPeriod);
void EPWM_disableInt(EPWM_TypeDef* EPWMx);
void EPWM_disableSocAPulse(EPWM_TypeDef* EPWMx);
void EPWM_disableSocBPulse(EPWM_TypeDef* EPWMx);
void EPWM_enableInt(EPWM_TypeDef* EPWMx);
void EPWM_enableSocAPulse(EPWM_TypeDef* EPWMx);
void EPWM_enableSocBPulse(EPWM_TypeDef* EPWMx);

uint16_t EPWM_getIntCount(EPWM_TypeDef* EPWMx);
uint16_t EPWM_getSocACount(EPWM_TypeDef* EPWMx);
uint16_t EPWM_getSocBCount(EPWM_TypeDef* EPWMx);

FlagStatus EPWM_EventTrigger_GetFlagStatus(EPWM_TypeDef* EPWMx, uint16_t ET_FLAG);


/* Digital-Compare Configuration functions *********************************/
void EPWM_setDigitalCompareFilterSource(EPWM_TypeDef* EPWMx, const EPWM_DigitalCompare_FilterSrc_e input);
void EPWM_setDigitalCompareBlankingPulse(EPWM_TypeDef* EPWMx, const EPWM_DigitalCompare_PulseSel_e pulseSelect);
void EPWM_setDigitalCompareFilterOffset(EPWM_TypeDef* EPWMx, const uint16_t offset);
void EPWM_setDigitalCompareFilterWindow(EPWM_TypeDef* EPWMx, const uint16_t window);
void EPWM_setDigitalCompareInput(EPWM_TypeDef* EPWMx, const EPWM_DigitalCompare_Input_e input, const EPWM_DigitalCompare_InputSel_e inputSel);
void EPWM_setDigitalCompareAEvent1(EPWM_TypeDef* EPWMx, const uint16_t  selectFilter, const uint16_t  disableSync, const uint16_t  enableSoc, const uint16_t  generateSync);
void EPWM_setDigitalCompareAEvent2(EPWM_TypeDef* EPWMx, const uint16_t  selectFilter, const uint16_t  disableSync);
void EPWM_setDigitalCompareBEvent1(EPWM_TypeDef* EPWMx, const uint16_t  selectFilter, const uint16_t  disableSync, const uint16_t  enableSoc, const uint16_t  generateSync);
void EPWM_setDigitalCompareBEvent2(EPWM_TypeDef* EPWMx, const uint16_t  selectFilter, const uint16_t  disableSync);
void EPWM_disableDigitalCompareBlankingWindow(EPWM_TypeDef* EPWMx);
void EPWM_disableDigitalCompareBlankingWindowInversion(EPWM_TypeDef* EPWMx);
void EPWM_enableDigitalCompareBlankingWindow(EPWM_TypeDef* EPWMx);
void EPWM_enableDigitalCompareBlankingWindowInversion(EPWM_TypeDef* EPWMx);


/* HR-PWM Configuration functions *********************************/
void EPWM_disableAutoConvert(EPWM_TypeDef* EPWMx);
void EPWM_disableHrPeriod(EPWM_TypeDef* EPWMx);
void EPWM_disableHrPhaseSync(EPWM_TypeDef* EPWMx);
void EPWM_disableMEPCalibrationOff(EPWM_TypeDef* EPWMx);
void EPWM_enableAutoConvert(EPWM_TypeDef* EPWMx);
void EPWM_enableHrPeriod(EPWM_TypeDef* EPWMx);
void EPWM_enableHrPhaseSync(EPWM_TypeDef* EPWMx);
void EPWM_enableMEPCalibrationOff(EPWM_TypeDef* EPWMx);
void EPWM_setHrControlMode(EPWM_TypeDef* EPWMx, const EPWM_HrControlMode_e controlMode);
void EPWM_setHrEdgeMode(EPWM_TypeDef* EPWMx, const EPWM_HrEdgeMode_e edgeMode);
void EPWM_setHrShadowMode(EPWM_TypeDef* EPWMx, const EPWM_HrShadowMode_e shadowMode);

void EPWM_clearMepFlag(EPWM_TypeDef* EPWMx);
FlagStatus EPWM_MepCalibration_GetFlagStatus(EPWM_TypeDef* EPWMx, uint16_t MEP_FLAG);
uint8_t EPWM_enableMEPSFO(EPWM_TypeDef* EPWMx);
void EPWM_disableMEPSFO(EPWM_TypeDef* EPWMx);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /*__FT32F4XX_EPWM_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

