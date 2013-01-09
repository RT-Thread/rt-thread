/***************************************************************************//**
 * @file
 * @brief Low Energy Sensor (LESENSE) peripheral API
 * @author Energy Micro AS
 * @version 3.0.0
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/
#ifndef __EM_LESENSE_H
#define __EM_LESENSE_H

#include "em_part.h"

#if defined(LESENSE_COUNT) && (LESENSE_COUNT > 0)
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup LESENSE
 * @{
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */



/** @endcond */

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** Clock divisors for controlling the prescaling factor of the period
 *  counter.
 *  Note: these enumeration values are being used for different clock division
 *  related configuration parameters (hfPresc, lfPresc, pcPresc). */
typedef enum
{
  lesenseClkDiv_1   = 0, /**< Divide clock by 1. */
  lesenseClkDiv_2   = 1, /**< Divide clock by 2. */
  lesenseClkDiv_4   = 2, /**< Divide clock by 4. */
  lesenseClkDiv_8   = 3, /**< Divide clock by 8. */
  lesenseClkDiv_16  = 4, /**< Divide clock by 16. */
  lesenseClkDiv_32  = 5, /**< Divide clock by 32. */
  lesenseClkDiv_64  = 6, /**< Divide clock by 64. */
  lesenseClkDiv_128 = 7  /**< Divide clock by 128. */
} LESENSE_ClkPresc_TypeDef;


/** Scan modes. */
typedef enum
{
  /** New scan is started each time the period counter overflows. */
  lesenseScanStartPeriodic = LESENSE_CTRL_SCANMODE_PERIODIC,

  /** Single scan is performed when LESENSE_ScanStart() is called. */
  lesenseScanStartOneShot  = LESENSE_CTRL_SCANMODE_ONESHOT,

  /** New scan is triggered by pulse on PRS channel. */
  lesenseScanStartPRS      = LESENSE_CTRL_SCANMODE_PRS
} LESENSE_ScanMode_TypeDef;


/** PRS sources.
 *  Note: these enumeration values are being used for different PRS related
 *  configuration parameters. */
typedef enum
{
  lesensePRSCh0     = 0, /**< PRS channel 0. */
  lesensePRSCh1     = 1, /**< PRS channel 1. */
  lesensePRSCh2     = 2, /**< PRS channel 2. */
  lesensePRSCh3     = 3, /**< PRS channel 3. */
  lesensePRSCh4     = 4, /**< PRS channel 4. */
  lesensePRSCh5     = 5, /**< PRS channel 5. */
  lesensePRSCh6     = 6, /**< PRS channel 6. */
  lesensePRSCh7     = 7  /**< PRS channel 7. */
} LESENSE_PRSSel_TypeDef;


/** Locations of the alternate excitation function. */
typedef enum
{
  /** Alternate excitation is mapped to the LES_ALTEX pins. */
  lesenseAltExMapALTEX = LESENSE_CTRL_ALTEXMAP_ALTEX,

  /** Alternate excitation is mapped to the pins of the other ACMP. */
  lesenseAltExMapACMP  = LESENSE_CTRL_ALTEXMAP_ACMP
} LESENSE_AltExMap_TypeDef;


/** Result buffer interrupt and DMA trigger levels. */
typedef enum
{
  /** DMA and interrupt flags are set when result buffer is halffull. */
  lesenseBufTrigHalf = LESENSE_CTRL_BUFIDL_HALFFULL,

  /** DMA and interrupt flags set when result buffer is full. */
  lesenseBufTrigFull = LESENSE_CTRL_BUFIDL_FULL
} LESENSE_BufTrigLevel_TypeDef;


/** Modes of operation for DMA wakeup from EM2. */
typedef enum
{
  /** No DMA wakeup from EM2. */
  lesenseDMAWakeUpDisable  = LESENSE_CTRL_DMAWU_DISABLE,

  /** DMA wakeup from EM2 when data is valid in the result buffer. */
  lesenseDMAWakeUpBufValid = LESENSE_CTRL_DMAWU_BUFDATAV,

  /** DMA wakeup from EM2 when the resultbuffer is full/halffull, depending on
   *  RESBIDL configuration in LESENSE_CTRL register (selected by
   *  resBufTrigLevel in LESENSE_ResBufTrigLevel_TypeDef descriptor structure). */
  lesenseDMAWakeUpBufLevel = LESENSE_CTRL_DMAWU_BUFLEVEL
} LESENSE_DMAWakeUp_TypeDef;


/** Bias modes. */
typedef enum
{
  /** Duty cycle bias module between low power and high accuracy mode. */
  lesenseBiasModeDutyCycle = LESENSE_BIASCTRL_BIASMODE_DUTYCYCLE,

  /** Bias module is always in high accuracy mode. */
  lesenseBiasModeHighAcc   = LESENSE_BIASCTRL_BIASMODE_HIGHACC,

  /** Bias module is controlled by the EMU and not affected by LESENSE. */
  lesenseBiasModeDontTouch = LESENSE_BIASCTRL_BIASMODE_DONTTOUCH
} LESENSE_BiasMode_TypeDef;


/** Scan configuration. */
typedef enum
{
  /** The channel configuration registers (CHx_CONF) used are directly mapped to
   *  the channel number. */
  lesenseScanConfDirMap = LESENSE_CTRL_SCANCONF_DIRMAP,

  /** The channel configuration registers used are CHx+8_CONF for channels 0-7
   *  and CHx-8_CONF for channels 8-15. */
  lesenseScanConfInvMap = LESENSE_CTRL_SCANCONF_INVMAP,

  /** The channel configuration registers used toggles between CHX_SCANCONF and
   *  CHX+8_SCANCONF when channel x triggers. */
  lesenseScanConfToggle = LESENSE_CTRL_SCANCONF_TOGGLE,

  /** The decoder state defines the channel configuration register (CHx_CONF) to
   *  be used. */
  lesenseScanConfDecDef = LESENSE_CTRL_SCANCONF_DECDEF
} LESENSE_ScanConfSel_TypeDef;


/** DAC CHx data control configuration. */
typedef enum
{
  /** DAC channel x data is defined by DAC_CHxDATA register.
   *  Note: this value could be used for both DAC Ch0 and Ch1. */
  lesenseDACIfData = _LESENSE_PERCTRL_DACCH0DATA_DACDATA,

  /** DAC channel x data is defined by ACMPTHRES in LESENSE_CHx_INTERACT.
   *  Note: this value could be used for both DAC Ch0 and Ch1. */
  lesenseACMPThres = _LESENSE_PERCTRL_DACCH0DATA_ACMPTHRES
} LESENSE_ControlDACData_TypeDef;


/** DAC channel x conversion mode configuration. */
typedef enum
{
  /** LESENSE doesn't control DAC channel x.
   *  Note: this value could be used for both DAC Ch0 and Ch1. */
  lesenseDACConvModeDisable    = _LESENSE_PERCTRL_DACCH0CONV_DISABLE,

  /** DAC channel x is driven in continuous mode.
   *  Note: this value could be used for both DAC Ch0 and Ch1. */
  lesenseDACConvModeContinuous = _LESENSE_PERCTRL_DACCH0CONV_CONTINUOUS,

  /** DAC channel x is driven in sample hold mode.
   *  Note: this value could be used for both DAC Ch0 and Ch1. */
  lesenseDACConvModeSampleHold = _LESENSE_PERCTRL_DACCH0CONV_SAMPLEHOLD,

  /** DAC channel x is driven in sample off mode.
   *  Note: this value could be used for both DAC Ch0 and Ch1. */
  lesenseDACConvModeSampleOff  = _LESENSE_PERCTRL_DACCH0CONV_SAMPLEOFF
} LESENSE_ControlDACConv_TypeDef;


/** DAC channel x output mode configuration. */
typedef enum
{
  /** DAC CHx output to pin and ACMP/ADC disabled.
   *  Note: this value could be used for both DAC Ch0 and Ch1. */
  lesenseDACOutModeDisable    = _LESENSE_PERCTRL_DACCH0OUT_DISABLE,

  /** DAC CHx output to pin enabled, output to ADC and ACMP disabled.
   *  Note: this value could be used for both DAC Ch0 and Ch1. */
  lesenseDACOutModePin        = _LESENSE_PERCTRL_DACCH0OUT_PIN,

  /** DAC CHx output to pin disabled, output to ADC and ACMP enabled.
   *  Note: this value could be used for both DAC Ch0 and Ch1. */
  lesenseDACOutModeADCACMP    = _LESENSE_PERCTRL_DACCH0OUT_ADCACMP,

  /** DAC CHx output to pin, ADC, and ACMP enabled.
   *  Note: this value could be used for both DAC Ch0 and Ch1. */
  lesenseDACOutModePinADCACMP = _LESENSE_PERCTRL_DACCH0OUT_PINADCACMP
} LESENSE_ControlDACOut_TypeDef;


/**  DAC reference configuration. */
typedef enum
{
  /** DAC uses VDD reference. */
  lesenseDACRefVdd     = LESENSE_PERCTRL_DACREF_VDD,

  /** DAC uses bandgap reference. */
  lesenseDACRefBandGap = LESENSE_PERCTRL_DACREF_BANDGAP
} LESENSE_DACRef_TypeDef;


/** ACMPx control configuration. */
typedef enum
{
  /** LESENSE does not control the ACMPx.
   *  Note: this value could be used for both ACMP0 and ACMP1. */
  lesenseACMPModeDisable  = _LESENSE_PERCTRL_ACMP0MODE_DISABLE,

  /** LESENSE controls the input mux of ACMPx.
   *  Note: this value could be used for both ACMP0 and ACMP1. */
  lesenseACMPModeMux      = _LESENSE_PERCTRL_ACMP0MODE_MUX,

  /** LESENSE controls the input mux of and the threshold value of ACMPx.
   *  Note: this value could be used for both ACMP0 and ACMP1. */
  lesenseACMPModeMuxThres = _LESENSE_PERCTRL_ACMP0MODE_MUXTHRES
} LESENSE_ControlACMP_TypeDef;


/** Warm up modes. ACMP and DAC duty cycle mode configuration. */
typedef enum
{
  /** ACMPs and DACs are shut down when LESENSE is idle. */
  lesenseWarmupModeNormal   = LESENSE_PERCTRL_WARMUPMODE_NORMAL,

  /** ACMPs are kept powered up when LESENSE is idle. */
  lesenseWarmupModeACMP     = LESENSE_PERCTRL_WARMUPMODE_KEEPACMPWARM,

  /** The DAC is kept powered up when LESENSE is idle. */
  lesenseWarmupModeDAC      = LESENSE_PERCTRL_WARMUPMODE_KEEPDACWARM,

  /** ACMPs and the DAC are kept powered up when LESENSE is idle. */
  lesenseWarmupModeKeepWarm = LESENSE_PERCTRL_WARMUPMODE_KEEPACMPDACWARM
} LESENSE_WarmupMode_TypeDef;


/** Decoder input source configuration. */
typedef enum
{
  /** The SENSORSTATE register is used as input to the decoder. */
  lesenseDecInputSensorSt = LESENSE_DECCTRL_INPUT_SENSORSTATE,

  /** PRS channels are used as input to the decoder. */
  lesenseDecInputPRS      = LESENSE_DECCTRL_INPUT_PRS
} LESENSE_DecInput_TypeDef;


/** Compare source selection for sensor sampling. */
typedef enum
{
  /** Counter output will be used in comparison. */
  lesenseSampleModeCounter = LESENSE_CH_INTERACT_SAMPLE_COUNTER,

  /** ACMP output will be used in comparison. */
  lesenseSampleModeACMP    = LESENSE_CH_INTERACT_SAMPLE_ACMP
} LESENSE_ChSampleMode_TypeDef;


/** Interrupt generation setup for CHx interrupt flag. */
typedef enum
{
  /** No interrupt is generated. */
  lesenseSetIntNone    = LESENSE_CH_INTERACT_SETIF_NONE,

  /** Set interrupt flag if the sensor triggers. */
  lesenseSetIntLevel   = LESENSE_CH_INTERACT_SETIF_LEVEL,

  /** Set interrupt flag on positive edge of the sensor state. */
  lesenseSetIntPosEdge = LESENSE_CH_INTERACT_SETIF_POSEDGE,

  /** Set interrupt flag on negative edge of the sensor state. */
  lesenseSetIntNegEdge = LESENSE_CH_INTERACT_SETIF_NEGEDGE
} LESENSE_ChIntMode_TypeDef;


/** Channel pin mode for the excitation phase of the scan sequence. */
typedef enum
{
  /** Channel pin is disabled. */
  lesenseChPinExDis    = LESENSE_CH_INTERACT_EXMODE_DISABLE,

  /** Channel pin is configured as push-pull, driven HIGH. */
  lesenseChPinExHigh   = LESENSE_CH_INTERACT_EXMODE_HIGH,

  /** Channel pin is configured as push-pull, driven LOW. */
  lesenseChPinExLow    = LESENSE_CH_INTERACT_EXMODE_LOW,

  /** DAC output (only available on channel 0, 1, 2, 3, 12, 13, 14 and 15) */
  lesenseChPinExDACOut = LESENSE_CH_INTERACT_EXMODE_DACOUT
} LESENSE_ChPinExMode_TypeDef;


/** Channel pin mode for the idle phase of the scan sequence. */
typedef enum
{
  /** Channel pin is disabled in idle phase.
   *  Note: this value could be used for all channels. */
  lesenseChPinIdleDis    = _LESENSE_IDLECONF_CH0_DISABLE,

  /** Channel pin is configured as push-pull, driven HIGH in idle phase.
   *  Note: this value could be used for all channels. */
  lesenseChPinIdleHigh   = _LESENSE_IDLECONF_CH0_HIGH,

  /** Channel pin is configured as push-pull, driven LOW in idle phase.
   *  Note: this value could be used for all channels. */
  lesenseChPinIdleLow    = _LESENSE_IDLECONF_CH0_LOW,

  /** Channel pin is connected to DAC CH0 output in idle phase.
   *  Note: only applies to channel 0, 1, 2, 3. */
  lesenseChPinIdleDACCh0 = _LESENSE_IDLECONF_CH0_DACCH0,

  /** Channel pin is connected to DAC CH1 output in idle phase.
   *  Note: only applies to channel 12, 13, 14, 15. */
  lesenseChPinIdleDACCh1 = _LESENSE_IDLECONF_CH12_DACCH1
} LESENSE_ChPinIdleMode_TypeDef;


/** Clock used for excitation and sample delay timing. */
typedef enum
{
  /** LFACLK (LF clock) is used. */
  lesenseClkLF = _LESENSE_CH_INTERACT_EXCLK_LFACLK,

  /** AUXHFRCO (HF clock) is used. */
  lesenseClkHF = _LESENSE_CH_INTERACT_EXCLK_AUXHFRCO
} LESENSE_ChClk_TypeDef;


/** Compare modes for counter comparison. */
typedef enum
{
  /** Set interrupt flag if counter value is less than CTRTHRESHOLD, or if the
   *  ACMP output is 0. */
  lesenseCompModeLess        = LESENSE_CH_EVAL_COMP_LESS,

  /** Set interrupt flag if counter value is greater than, or equal to
   *  CTRTHRESHOLD, or if the ACMP output is 1. */
  lesenseCompModeGreaterOrEq = LESENSE_CH_EVAL_COMP_GE
} LESENSE_ChCompMode_TypeDef;


/** Idle phase configuration of alternate excitation channels. */
typedef enum
{
  /** ALTEX output is disabled in idle phase.
   *  Note: this value could be used for all alternate excitation channels. */
  lesenseAltExPinIdleDis  = _LESENSE_ALTEXCONF_IDLECONF0_DISABLE,

  /** ALTEX output is high in idle phase.
   *  Note: this value could be used for all alternate excitation channels. */
  lesenseAltExPinIdleHigh = _LESENSE_ALTEXCONF_IDLECONF0_HIGH,

  /** ALTEX output is low in idle phase.
   *  Note: this value could be used for all alternate excitation channels. */
  lesenseAltExPinIdleLow  = _LESENSE_ALTEXCONF_IDLECONF0_LOW
} LESENSE_AltExPinIdle_TypeDef;


/** Transition action modes. */
typedef enum
{
  /** No PRS pulses generated (if PRSCOUNT == 0).
   *  Do not count (if PRSCOUNT == 1). */
  lesenseTransActNone        = LESENSE_ST_TCONFA_PRSACT_NONE,

  /** Generate pulse on LESPRS0 (if PRSCOUNT == 0). */
  lesenseTransActPRS0        = LESENSE_ST_TCONFA_PRSACT_PRS0,

  /** Generate pulse on LESPRS1 (if PRSCOUNT == 0). */
  lesenseTransActPRS1        = LESENSE_ST_TCONFA_PRSACT_PRS1,

  /** Generate pulse on LESPRS0 and LESPRS1 (if PRSCOUNT == 0). */
  lesenseTransActPRS01       = LESENSE_ST_TCONFA_PRSACT_PRS01,

  /** Generate pulse on LESPRS2 (for both PRSCOUNT == 0 and PRSCOUNT == 1). */
  lesenseTransActPRS2        = LESENSE_ST_TCONFA_PRSACT_PRS2,

  /** Generate pulse on LESPRS0 and LESPRS2 (if PRSCOUNT == 0). */
  lesenseTransActPRS02       = LESENSE_ST_TCONFA_PRSACT_PRS02,

  /** Generate pulse on LESPRS1 and LESPRS2 (if PRSCOUNT == 0). */
  lesenseTransActPRS12       = LESENSE_ST_TCONFA_PRSACT_PRS12,

  /** Generate pulse on LESPRS0, LESPRS1 and LESPRS2  (if PRSCOUNT == 0). */
  lesenseTransActPRS012      = LESENSE_ST_TCONFA_PRSACT_PRS012,

  /** Count up (if PRSCOUNT == 1). */
  lesenseTransActUp          = LESENSE_ST_TCONFA_PRSACT_UP,

  /** Count down (if PRSCOUNT == 1). */
  lesenseTransActDown        = LESENSE_ST_TCONFA_PRSACT_DOWN,

  /** Count up and generate pulse on LESPRS2 (if PRSCOUNT == 1). */
  lesenseTransActUpAndPRS2   = LESENSE_ST_TCONFA_PRSACT_UPANDPRS2,

  /** Count down and generate pulse on LESPRS2 (if PRSCOUNT == 1). */
  lesenseTransActDownAndPRS2 = LESENSE_ST_TCONFA_PRSACT_DOWNANDPRS2
} LESENSE_StTransAct_TypeDef;


/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** Core control (LESENSE_CTRL) descriptor structure. */
typedef struct
{
  /** Select scan start mode to control how the scan start is being triggered.*/
  LESENSE_ScanMode_TypeDef     scanStart;

  /** Select PRS source for scan start if scanMode is set to lesensePrsPulse. */
  LESENSE_PRSSel_TypeDef       prsSel;

  /** Select scan configuration register usage strategy. */
  LESENSE_ScanConfSel_TypeDef  scanConfSel;

  /** Set to true to invert ACMP0 output. */
  bool                         invACMP0;

  /** Set to true to invert ACMP1 output. */
  bool                         invACMP1;

  /** Set to true to sample both ACMPs simultaneously. */
  bool                         dualSample;

  /** Set to true in order to to store SCANRES in RAM (accessible via RESDATA)
   *  after each scan. */
  bool                         storeScanRes;

  /** Set to true in order to always make LESENSE write to the result buffer,
   *  even if it is full. */
  bool                         bufOverWr;

  /** Select trigger conditions for interrupt and DMA. */
  LESENSE_BufTrigLevel_TypeDef bufTrigLevel;

  /** Configure trigger condition for DMA wakeup from EM2. */
  LESENSE_DMAWakeUp_TypeDef    wakeupOnDMA;

  /** Select bias mode. */
  LESENSE_BiasMode_TypeDef     biasMode;

  /** Set to true to keep LESENSE running in debug mode. */
  bool                         debugRun;
} LESENSE_CoreCtrlDesc_TypeDef;

/** Default configuration for LESENSE_CtrlDesc_TypeDef structure. */
#define LESENSE_CORECTRL_DESC_DEFAULT                                                                 \
  {                                                                                                   \
    lesenseScanStartPeriodic,  /* Start new scan each time the period counter overflows. */           \
    lesensePRSCh0,             /* Default PRS channel is selected. */                                 \
    lesenseScanConfDirMap,     /* Direct mapping SCANCONF register usage strategy. */                 \
    false,                     /* Don't invert ACMP0 output. */                                       \
    false,                     /* Don't invert ACMP1 output. */                                       \
    false,                     /* Disable dual sampling. */                                           \
    true,                      /* Store scan result after each scan. */                               \
    true,                      /* Overwrite result buffer register even if it is full. */             \
    lesenseBufTrigHalf,        /* Trigger interrupt and DMA request if result buffer is half full. */ \
    lesenseDMAWakeUpDisable,   /* Don't wake up on DMA from EM2. */                                   \
    lesenseBiasModeDontTouch,  /* Don't touch bias configuration. */                                  \
    true                       /* Keep LESENSE running in debug mode. */                              \
  }


/** LESENSE timing control descriptor structure. */
typedef struct
{
  /** Set the number of LFACLK cycles to delay sensor interaction on
   *  each channel. Valid range: 0-3 (2 bit). */
  uint8_t startDelay;
} LESENSE_TimeCtrlDesc_TypeDef;

/** Default configuration for LESENSE_TimeCtrlDesc_TypeDef structure. */
#define LESENSE_TIMECTRL_DESC_DEFAULT    0U


/** LESENSE peripheral control descriptor structure. */
typedef struct
{
  /** Configure DAC channel 0 data control. */
  LESENSE_ControlDACData_TypeDef dacCh0Data;

  /** Configure how LESENSE controls conversion on DAC channel 0. */
  LESENSE_ControlDACConv_TypeDef dacCh0ConvMode;

  /** Configure how LESENSE controls output on DAC channel 0. */
  LESENSE_ControlDACOut_TypeDef  dacCh0OutMode;

  /** Configure DAC channel 1 data control. */
  LESENSE_ControlDACData_TypeDef dacCh1Data;

  /** Configure how LESENSE controls conversion on DAC channel 1. */
  LESENSE_ControlDACConv_TypeDef dacCh1ConvMode;

  /** Configure how LESENSE controls output on DAC channel 1. */
  LESENSE_ControlDACOut_TypeDef  dacCh1OutMode;

  /** Configure the prescaling factor for the LESENSE - DAC interface.
   *  Valid range: 0-31 (5bit). */
  uint8_t                        dacPresc;

  /** Configure the DAC reference to be used. Set to #lesenseDACRefVdd to use
   *  VDD and set to #lesenseDACRefBandGap to use bandgap as reference. */
  LESENSE_DACRef_TypeDef         dacRef;

  /** Configure how LESENSE controls ACMP 0. */
  LESENSE_ControlACMP_TypeDef    acmp0Mode;

  /** Configure how LESENSE controls ACMP 1. */
  LESENSE_ControlACMP_TypeDef    acmp1Mode;

  /** Configure how LESENSE controls ACMPs and the DAC in idle mode. */
  LESENSE_WarmupMode_TypeDef     warmupMode;
} LESENSE_PerCtrlDesc_TypeDef;

/** Default configuration for LESENSE_PerCtrl_TypeDef structure. */
#define LESENSE_PERCTRL_DESC_DEFAULT \
  {                                  \
    lesenseDACIfData,          /**/  \
    lesenseDACConvModeDisable, /**/  \
    lesenseDACOutModeDisable,  /**/  \
    lesenseDACIfData,          /**/  \
    lesenseDACConvModeDisable, /**/  \
    lesenseDACOutModeDisable,  /**/  \
    0U,                        /**/  \
    lesenseDACRefVdd,          /**/  \
    lesenseACMPModeMuxThres,   /**/  \
    lesenseACMPModeMuxThres,   /**/  \
    lesenseWarmupModeKeepWarm, /**/  \
  }


/** LESENSE decoder control descriptor structure. */
typedef struct
{
  /** Select the input to the LESENSE decoder. */
  LESENSE_DecInput_TypeDef decInput;

  /** Initial state of the LESENSE decoder. */
  uint32_t                 initState;

  /** Set to enable the decoder to check the present state in addition
   *  to the states defined in DECCONF. */
  bool                     chkState;

  /** When set, a transition from state x in the decoder will set interrupt flag
   *  CHx. */
  bool                     intMap;

  /** Set to enable hysteresis in the decoder for suppressing changes on PRS
   *  channel 0. */
  bool                     hystPRS0;

  /** Set to enable hysteresis in the decoder for suppressing changes on PRS
   *  channel 1. */
  bool                     hystPRS1;

  /** Set to enable hysteresis in the decoder for suppressing changes on PRS
   *  channel 2. */
  bool                     hystPRS2;

  /** Set to enable hysteresis in the decoder for suppressing interrupt
   *  requests. */
  bool                     hystIRQ;

  /** Set to enable count mode on decoder PRS channels 0 and 1 to produce
   *  outputs which can be used by a PCNT to count up or down. */
  bool                     prsCount;

  /** Select PRS channel input for bit 0 of the LESENSE decoder. */
  LESENSE_PRSSel_TypeDef   prsChSel0;

  /** Select PRS channel input for bit 1 of the LESENSE decoder. */
  LESENSE_PRSSel_TypeDef   prsChSel1;

  /** Select PRS channel input for bit 2 of the LESENSE decoder. */
  LESENSE_PRSSel_TypeDef   prsChSel2;

  /** Select PRS channel input for bit 3 of the LESENSE decoder. */
  LESENSE_PRSSel_TypeDef   prsChSel3;
} LESENSE_DecCtrlDesc_TypeDef;

/** Default configuration for LESENSE_PerCtrl_TypeDef structure. */
#define LESENSE_DECCTRL_DESC_DEFAULT \
  {                                  \
    lesenseDecInputSensorSt, /**/    \
    0U,                      /**/    \
    false,                   /**/    \
    true,                    /**/    \
    true,                    /**/    \
    true,                    /**/    \
    true,                    /**/    \
    true,                    /**/    \
    false,                   /**/    \
    lesensePRSCh0,           /**/    \
    lesensePRSCh1,           /**/    \
    lesensePRSCh2,           /**/    \
    lesensePRSCh3,           /**/    \
  }


/** LESENSE module initialization structure. */
typedef struct
{
  /** LESENSE core configuration parameters. */
  LESENSE_CoreCtrlDesc_TypeDef coreCtrl;

  /** LESENSE timing configuration parameters. */
  LESENSE_TimeCtrlDesc_TypeDef timeCtrl;

  /** LESENSE peripheral configuration parameters. */
  LESENSE_PerCtrlDesc_TypeDef  perCtrl;

  /** LESENSE decoder configuration parameters. */
  LESENSE_DecCtrlDesc_TypeDef  decCtrl;
} LESENSE_Init_TypeDef;

/** Default configuration for LESENSE_Init_TypeDef structure. */
#define LESENSE_INIT_DEFAULT                        \
  {                                                 \
    .coreCtrl = LESENSE_CORECTRL_DESC_DEFAULT, /* Default core control parameters. */ \
    .timeCtrl = LESENSE_TIMECTRL_DESC_DEFAULT, /* Default time control parameters. */ \
    .perCtrl  = LESENSE_PERCTRL_DESC_DEFAULT,  /* Default peripheral control parameters. */ \
    .decCtrl  = LESENSE_DECCTRL_DESC_DEFAULT   /* Default decoder control parameters. */ \
  }


/** Channel descriptor structure. */
typedef struct
{
  /** Set to enable scan channel CHx. */
  bool                          enaScanCh;

  /** Set to enable CHx pin. */
  bool                          enaPin;

  /** Enable/disable channel interrupts after configuring all the sensor channel
   *  parameters. */
  bool                          enaInt;

  /** Configure channel pin mode for the excitation phase of the scan sequence.
   *  Note: OPAOUT is only available on channels 2, 3, 4, and 5. */
  LESENSE_ChPinExMode_TypeDef   chPinExMode;

  /** Configure channel pin idle setup in LESENSE idle phase. */
  LESENSE_ChPinIdleMode_TypeDef chPinIdleMode;

  /** Set to use alternate excite pin for excitation. */
  bool                          useAltEx;

  /** Set to enable the result from this channel being shifted into the decoder
   *  register. */
  bool                          shiftRes;

  /** Set to invert the result bit stored in SCANRES register. */
  bool                          invRes;

  /** Set to store the counter value in RAM (accessible via RESDATA) and make
   *  the comparison result available in the SCANRES register. */
  bool                          storeCntRes;

  /** Select clock used for excitation timing. */
  LESENSE_ChClk_TypeDef         exClk;

  /** Select clock used for sample delay timing. */
  LESENSE_ChClk_TypeDef         sampleClk;

  /** Configure excitation time. Excitation will last exTime+1 excitation clock
   *  cycles. Valid range: 0-63 (6 bits). */
  uint8_t                       exTime;

  /** Configure sample delay. Sampling will occur after sampleDelay+1 sample
   *  clock cycles. Valid range: 0-127 (7 bits). */
  uint8_t                       sampleDelay;

  /** Configure measure delay. Sensor measuring is delayed for measDelay
   *  excitation clock cycles. Valid range: 0-127 (7 bits). */
  uint8_t                       measDelay;

  /** Configure ACMP threshold.
   *  If perCtrl.dacCh0Data or perCtrl.dacCh1Data is set to #lesenseDACIfData,
   *  acmpThres defines the 12-bit DAC data in the corresponding data register
   *  of the DAC interface (DACn_CH0DATA and DACn_CH1DATA).
   *  In this case, the valid range is: 0-4095 (12 bits).
   *  If perCtrl.dacCh0Data or perCtrl.dacCh1Data is set to #lesenseACMPThres,
   *  acmpThres defines the 6-bit Vdd scaling factor of ACMP negative input
   *  (VDDLEVEL in ACMP_INPUTSEL register).
   *  In this case, the valid range is: 0-63 (6 bits). */
  uint16_t                     acmpThres;

  /** Select if ACMP output or counter output should be used in comparison. */
  LESENSE_ChSampleMode_TypeDef sampleMode;

  /** Configure interrupt generation mode for CHx interrupt flag. */
  LESENSE_ChIntMode_TypeDef    intMode;

  /** Configure decision threshold for counter comparison.
   *  Valid range: 0-65535 (16 bits). */
  uint16_t                     cntThres;

  /** Select mode for counter comparison. */
  LESENSE_ChCompMode_TypeDef   compMode;
} LESENSE_ChDesc_TypeDef;


/** Configuration structure for all scan channels. */
typedef struct
{
  /** Channel descriptor for all 16 channels. */
  LESENSE_ChDesc_TypeDef Ch[16];
} LESENSE_ChAll_TypeDef;

/** Default configuration for scan channel. */
#define LESENSE_CH_CONF_DEFAULT                                                                       \
  {                                                                                                   \
    true,                  /* Enable scan channel. */                                                 \
    true,                  /* Enable the assigned pin on scan channel. */                             \
    true,                  /* Enable interrupts on channel. */                                        \
    lesenseChPinExHigh,    /* Channel pin is high during the excitation period. */                    \
    lesenseChPinIdleLow,   /* Channel pin is low during the idle period. */                           \
    false,                 /* Don't use alternate excitation pins for excitation. */                  \
    false,                 /* Disabled to shift results from this channel to the decoder register. */ \
    false,                 /* Disabled to invert the scan result bit. */                              \
    false,                 /* Disabled to store counter value in the result buffer. */                \
    lesenseClkLF,          /* Use the LF clock for excitation timing. */                              \
    lesenseClkLF,          /* Use the LF clock for sample timing. */                                  \
    0x03U,                 /* Excitation time is set to 3(+1) excitation clock cycles. */             \
    0x09U,                 /* Sample delay is set to 9(+1) sample clock cycles. */                    \
    0x06U,                 /* Measure delay is set to 6 excitation clock cycles.*/                    \
    0x00U,                 /* ACMP threshold has been set to 0. */                                    \
    lesenseSampleModeACMP, /* ACMP output will be used in comparison. */                              \
    lesenseSetIntNone,     /* No interrupt is generated by the channel. */                            \
    0xFFU,                 /* Counter threshold has bee set to 0xFF. */                               \
    lesenseCompModeLess    /* Compare mode has been set to trigger interrupt on "less". */            \
  }

/** Default configuration for all sensor channels. */
#define LESENSE_SCAN_CONF_DEFAULT                     \
  {                                                   \
    {                                                 \
      LESENSE_CH_CONF_DEFAULT, /* Scan channel 0. */  \
      LESENSE_CH_CONF_DEFAULT, /* Scan channel 1. */  \
      LESENSE_CH_CONF_DEFAULT, /* Scan channel 2. */  \
      LESENSE_CH_CONF_DEFAULT, /* Scan channel 3. */  \
      LESENSE_CH_CONF_DEFAULT, /* Scan channel 4. */  \
      LESENSE_CH_CONF_DEFAULT, /* Scan channel 5. */  \
      LESENSE_CH_CONF_DEFAULT, /* Scan channel 6. */  \
      LESENSE_CH_CONF_DEFAULT, /* Scan channel 7. */  \
      LESENSE_CH_CONF_DEFAULT, /* Scan channel 8. */  \
      LESENSE_CH_CONF_DEFAULT, /* Scan channel 9. */  \
      LESENSE_CH_CONF_DEFAULT, /* Scan channel 10. */ \
      LESENSE_CH_CONF_DEFAULT, /* Scan channel 11. */ \
      LESENSE_CH_CONF_DEFAULT, /* Scan channel 12. */ \
      LESENSE_CH_CONF_DEFAULT, /* Scan channel 13. */ \
      LESENSE_CH_CONF_DEFAULT, /* Scan channel 14. */ \
      LESENSE_CH_CONF_DEFAULT, /* Scan channel 15. */ \
    }                                                 \
  }


/** Alternate excitation descriptor structure. */
typedef struct
{
  /** Configure alternate excitation pins. If set, the corresponding alternate
   *  excitation pin is enabled. */
  bool                         enablePin;

  /** Configure idle phase setup of alternate excitation pins. */
  LESENSE_AltExPinIdle_TypeDef idleConf;

  /** Configure how to control the external alternate excitation pins. Only
  *  applies if altExMap has been set to lesenseAltExMapALTEX.
  *  If true, the excitation happens on the corresponding alternate excitation
  *  pin during the excitation periods of all enabled channels.
  *  If false, the excitation happens on the corresponding alternate excitation
  *  pin ONLY during the excitation period of the corresponding channel. */
  bool                         alwaysEx;
} LESENSE_AltExDesc_TypeDef;


/** Configuration structure for alternate excitation. */
typedef struct
{
  /** Select alternate excitation mapping. */
  LESENSE_AltExMap_TypeDef  altExMap;

  /** Alternate excitation channel descriptors. */
  LESENSE_AltExDesc_TypeDef AltEx[8];
} LESENSE_ConfAltEx_TypeDef;

/** Default configuration for alternate excitation channel. */
#define LESENSE_ALTEX_CH_CONF_DEFAULT                                          \
  {                                                                            \
    true,                  /* Alternate excitation enabled.*/                  \
    lesenseAltExIdleDis,   /* Alternate excitation pin is disabled in idle. */ \
    false                  /* Excite only for corresponding channel. */        \
  }

/** Default configuration for all alternate excitation channels. */
#define LESENSE_ALTEX_CONF_DEFAULT                                         \
  {                                                                        \
    lesenseAltExMapACMP,                                                   \
    {                                                                      \
      LESENSE_ALTEX_CH_CONF_DEFAULT, /* Alternate excitation channel 0. */ \
      LESENSE_ALTEX_CH_CONF_DEFAULT, /* Alternate excitation channel 1. */ \
      LESENSE_ALTEX_CH_CONF_DEFAULT, /* Alternate excitation channel 2. */ \
      LESENSE_ALTEX_CH_CONF_DEFAULT, /* Alternate excitation channel 3. */ \
      LESENSE_ALTEX_CH_CONF_DEFAULT, /* Alternate excitation channel 4. */ \
      LESENSE_ALTEX_CH_CONF_DEFAULT, /* Alternate excitation channel 5. */ \
      LESENSE_ALTEX_CH_CONF_DEFAULT, /* Alternate excitation channel 6. */ \
      LESENSE_ALTEX_CH_CONF_DEFAULT  /* Alternate excitation channel 7. */ \
    }                                                                      \
  }


/** Decoder state condition descriptor structure. */
typedef struct
{
  /** Configure compare value. State transition is triggered when sensor state
   *  equals to this value. Valid range: 0-15 (4 bits). */
  uint8_t                    compVal;

  /** Configure compare mask. Set bit X to exclude sensor X from evaluation.
   *  Note: decoder can handle sensor inputs from up to 4 sensors, therefore
   *  this mask is 4 bit long. */
  uint8_t                    compMask;

  /** Configure index of state to be entered if the sensor state equals to
   *  compVal. Valid range: 0-15 (4 bits). */
  uint8_t                    nextState;

  /** Configure which PRS action to perform when sensor state equals to
   *  compVal. */
  LESENSE_StTransAct_TypeDef prsAct;

  /** If enabled, interrupt flag is set when sensor state equals to compVal. */
  bool                       setInt;
} LESENSE_DecStCond_TypeDef;

/** Default configuration for decoder state condition. */
#define LESENSE_ST_CONF_DEFAULT                                          \
  {                                                                      \
    0x0FU,               /* Compare value set to 0x0F. */                \
    0x00U,               /* All decoder inputs masked. */                \
    0U,                  /* Next state is state 0. */                    \
    lesenseTransActNone, /* No PRS action performed on compare match. */ \
    false                /* No interrupt triggered on compare match. */  \
  }


/** Decoder state x configuration structure. */
typedef struct
{
  /** If enabled, the state descriptor pair in the next location will also be
   *  evaluated. */
  bool                      chainDesc;

  /** State condition descriptor A (high level descriptor of
   *  LESENSE_STx_DECCONFA). */
  LESENSE_DecStCond_TypeDef confA;

  /** State condition descriptor B (high level descriptor of
   *  LESENSE_STx_DECCONFB). */
  LESENSE_DecStCond_TypeDef confB;
} LESENSE_DecStDesc_TypeDef;


/** Configuration structure for the decoder. */
typedef struct
{
  /** Descriptor of the 16 decoder states. */
  LESENSE_DecStDesc_TypeDef St[16];
} LESENSE_DecStAll_TypeDef;

/** Default configuration for all decoder states. */
#define LESENSE_DECODER_CONF_DEFAULT                                                                                 \
  {  /* chain |   Descriptor A         |   Descriptor B   */ \
    {                                                                                                                \
      { false, LESENSE_ST_CONF_DEFAULT, LESENSE_ST_CONF_DEFAULT }, /* Decoder state 0. */                            \
      { false, LESENSE_ST_CONF_DEFAULT, LESENSE_ST_CONF_DEFAULT }, /* Decoder state 1. */                            \
      { false, LESENSE_ST_CONF_DEFAULT, LESENSE_ST_CONF_DEFAULT }, /* Decoder state 2. */                            \
      { false, LESENSE_ST_CONF_DEFAULT, LESENSE_ST_CONF_DEFAULT }, /* Decoder state 3. */                            \
      { false, LESENSE_ST_CONF_DEFAULT, LESENSE_ST_CONF_DEFAULT }, /* Decoder state 4. */                            \
      { false, LESENSE_ST_CONF_DEFAULT, LESENSE_ST_CONF_DEFAULT }, /* Decoder state 5. */                            \
      { false, LESENSE_ST_CONF_DEFAULT, LESENSE_ST_CONF_DEFAULT }, /* Decoder state 6. */                            \
      { false, LESENSE_ST_CONF_DEFAULT, LESENSE_ST_CONF_DEFAULT }, /* Decoder state 7. */                            \
      { false, LESENSE_ST_CONF_DEFAULT, LESENSE_ST_CONF_DEFAULT }, /* Decoder state 8. */                            \
      { false, LESENSE_ST_CONF_DEFAULT, LESENSE_ST_CONF_DEFAULT }, /* Decoder state 9. */                            \
      { false, LESENSE_ST_CONF_DEFAULT, LESENSE_ST_CONF_DEFAULT }, /* Decoder state 10. */                           \
      { false, LESENSE_ST_CONF_DEFAULT, LESENSE_ST_CONF_DEFAULT }, /* Decoder state 11. */                           \
      { false, LESENSE_ST_CONF_DEFAULT, LESENSE_ST_CONF_DEFAULT }, /* Decoder state 12. */                           \
      { false, LESENSE_ST_CONF_DEFAULT, LESENSE_ST_CONF_DEFAULT }, /* Decoder state 13. */                           \
      { false, LESENSE_ST_CONF_DEFAULT, LESENSE_ST_CONF_DEFAULT }, /* Decoder state 14. */                           \
      { false, LESENSE_ST_CONF_DEFAULT, LESENSE_ST_CONF_DEFAULT } /* Decoder state 15. */                            \
    }                                                                                                                \
  }

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/
void LESENSE_Init(LESENSE_Init_TypeDef const *init, bool const reqReset);
void LESENSE_Reset(void);

uint32_t LESENSE_ScanFreqSet(uint32_t refFreq, uint32_t const scanFreq);
void LESENSE_ScanModeSet(LESENSE_ScanMode_TypeDef const scanMode,
                         bool const start);

void LESENSE_StartDelaySet(uint8_t const startDelay);

void LESENSE_ClkDivSet(LESENSE_ChClk_TypeDef const clk,
                       LESENSE_ClkPresc_TypeDef const clkDiv);

void LESENSE_ChannelAllConfig(LESENSE_ChAll_TypeDef const *confChAll);
void LESENSE_ChannelConfig(LESENSE_ChDesc_TypeDef const *confCh,
                           uint32_t const chIdx);
void LESENSE_ChannelEnable(uint8_t const chIdx,
                           bool const enaScanCh,
                           bool const enaPin);
void LESENSE_ChannelEnableMask(uint16_t chMask, uint16_t pinMask);
void LESENSE_ChannelTimingSet(uint8_t const chIdx,
                              uint8_t const exTime,
                              uint8_t const sampleDelay,
                              uint8_t const measDelay);
void LESENSE_ChannelThresSet(uint8_t const chIdx,
                             uint16_t const acmpThres,
                             uint16_t const cntThres);

void LESENSE_AltExConfig(LESENSE_ConfAltEx_TypeDef const *confAltEx);

void LESENSE_DecoderStateAllConfig(LESENSE_DecStAll_TypeDef const *confDecStAll);
void LESENSE_DecoderStateConfig(LESENSE_DecStDesc_TypeDef const *confDecSt,
                                uint32_t const decSt);
void LESENSE_DecoderStateSet(uint32_t decSt);
uint32_t LESENSE_DecoderStateGet(void);

__STATIC_INLINE void LESENSE_ScanStart(void);
__STATIC_INLINE void LESENSE_ScanStop(void);
__STATIC_INLINE void LESENSE_DecoderStart(void);
__STATIC_INLINE void LESENSE_DecoderStop(void);
__STATIC_INLINE void LESENSE_ResultBufferClear(void);

__STATIC_INLINE uint32_t LESENSE_StatusGet(void);
__STATIC_INLINE void LESENSE_StatusWait(uint32_t flag);
__STATIC_INLINE uint32_t LESENSE_ChannelActiveGet(void);
__STATIC_INLINE uint32_t LESENSE_ScanResultGet(void);
__STATIC_INLINE uint32_t LESENSE_ScanResultDataGet(void);
__STATIC_INLINE uint32_t LESENSE_ScanResultDataBufferGet(uint32_t idx);
__STATIC_INLINE uint32_t LESENSE_SensorStateGet(void);
__STATIC_INLINE void LESENSE_RAMPowerDown(void);

__STATIC_INLINE void LESENSE_IntClear(uint32_t flags);
__STATIC_INLINE void LESENSE_IntEnable(uint32_t flags);
__STATIC_INLINE void LESENSE_IntDisable(uint32_t flags);
__STATIC_INLINE void LESENSE_IntSet(uint32_t flags);
__STATIC_INLINE uint32_t LESENSE_IntGet(void);
__STATIC_INLINE uint32_t LESENSE_IntGetEnabled(void);


/***************************************************************************//**
 * @brief
 *   Start scanning of sensors.
 ******************************************************************************/
__STATIC_INLINE void LESENSE_ScanStart(void)
{
  /* Start scanning of sensors */
  LESENSE->CMD = LESENSE_CMD_START;
}


/***************************************************************************//**
 * @brief
 *   Stop scanning of sensors.
 *
 * @note
 *   If issued during a scan, the command takes effect after scan completion.
 ******************************************************************************/
__STATIC_INLINE void LESENSE_ScanStop(void)
{
  /* Stop scanning of sensors */
  LESENSE->CMD = LESENSE_CMD_STOP;
}


/***************************************************************************//**
 * @brief
 *   Start LESENSE decoder.
 ******************************************************************************/
__STATIC_INLINE void LESENSE_DecoderStart(void)
{
  /* Start decoder */
  LESENSE->CMD = LESENSE_CMD_DECODE;
}


/***************************************************************************//**
 * @brief
 *   Stop LESENSE decoder.
 *
 * @details
 *   This function disables the LESENSE decoder by setting the command to the
 *   LESENSE_DECCTRL register.
 ******************************************************************************/
__STATIC_INLINE void LESENSE_DecoderStop(void)
{
  /* Stop the decoder */
  LESENSE->DECCTRL |= LESENSE_DECCTRL_DISABLE;
}


/***************************************************************************//**
 * @brief
 *   Clear result buffer.
 ******************************************************************************/
__STATIC_INLINE void LESENSE_ResultBufferClear(void)
{
  LESENSE->CMD = LESENSE_CMD_CLEARBUF;
}


/***************************************************************************//**
 * @brief
 *   Get the current status of LESENSE.
 *
 * @return
 *   This function returns the value of LESENSE_STATUS register that
 *   contains the OR combination of the following status bits:
 *   @li LESENSE_STATUS_RESV - Result data valid. Set when data is available
 *   in the result buffer. Cleared when the buffer is empty.
 *   @li LESENSE_STATUS_RESFULL - Result buffer full. Set when the result
 *   buffer is full.
 *   @li LESENSE_STATUS_RUNNING - LESENSE is active.
 *   @li LESENSE_STATUS_SCANACTIVE - LESENSE is currently interfacing sensors.
 ******************************************************************************/
__STATIC_INLINE uint32_t LESENSE_StatusGet(void)
{
  return LESENSE->STATUS;
}


/***************************************************************************//**
 * @brief
 *   Wait until the status of LESENSE is equal to what requested.
 *
 * @details
 *   This function is polling the LESENSE_STATUS register and waits until the
 *   requested combination of flags are set.
 *
 * @param[in] flag
 *   The OR combination of the following status bits:
 *   @li LESENSE_STATUS_BUFDATAV - Result data valid. Set when data is available
 *   in the result buffer. Cleared when the buffer is empty.
 *   @li LESENSE_STATUS_BUFHALFFULL - Result buffer half full. Set when the
 *   result buffer is half full.
 *   @li LESENSE_STATUS_BUFFULL - Result buffer full. Set when the result
 *   buffer is full.
 *   @li LESENSE_STATUS_RUNNING - LESENSE is active.
 *   @li LESENSE_STATUS_SCANACTIVE - LESENSE is currently interfacing sensors.
 *   @li LESENSE_STATUS_DACACTIVE - The DAC interface is currently active.
 ******************************************************************************/
__STATIC_INLINE void LESENSE_StatusWait(uint32_t flag)
{
  while (!(LESENSE->STATUS & flag))
    ;
}


/***************************************************************************//**
 * @brief
 *   Get the currently active channel index.
 *
 * @return
 *   This function returns the value of LESENSE_CHINDEX register that
 *   contains the index of the currently active channel (0-15).
 ******************************************************************************/
__STATIC_INLINE uint32_t LESENSE_ChannelActiveGet(void)
{
  return LESENSE->CURCH;
}


/***************************************************************************//**
 * @brief
 *   Get the latest scan comparison result (1 bit / channel).
 *
 * @return
 *   This function returns the value of LESENSE_SCANRES register that
 *   contains the comparison result of the last scan on all channels.
 *   Bit x is set if a comparison triggered on channel x, which means that the
 *   LESENSE counter met the comparison criteria set in LESENSE_CHx_EVAL by
 *   COMPMODE and CNTTHRES.
 ******************************************************************************/
__STATIC_INLINE uint32_t LESENSE_ScanResultGet(void)
{
  return LESENSE->SCANRES;
}


/***************************************************************************//**
 * @brief
 *   Get the oldest unread data from the result buffer.
 *
 * @note
 *   Make sure that the STORERES bit is set in LESENSE_CHx_EVAL, or
 *   STRSCANRES bit is set in LESENSE_CTRL, otherwise this function will return
 *   undefined value.
 *
 * @return
 *   This function returns the value of LESENSE_RESDATA register that
 *   contains the oldest unread counter result from the result buffer.
 ******************************************************************************/
__STATIC_INLINE uint32_t LESENSE_ScanResultDataGet(void)
{
  return LESENSE->BUFDATA;
}


/***************************************************************************//**
 * @brief
 *   Get data from the result data buffer.
 *
 * @note
 *   Make sure that the STORERES bit is set in LESENSE_CHx_EVAL, or
 *   STRSCANRES bit is set in LESENSE_CTRL, otherwise this function will return
 *   undefined value.
 *
 * @param[in]
 *   Result data buffer index. Valid range: 0-15.
 *
 * @return
 *   This function returns the selected word from the result data buffer.
 ******************************************************************************/
__STATIC_INLINE uint32_t LESENSE_ScanResultDataBufferGet(uint32_t idx)
{
  /* Note: masking is needed to avoid over-indexing! */
  return LESENSE->BUF[idx & 0x0FU].DATA;
}

/***************************************************************************//**
 * @brief
 *   Get the current state of the LESENSE sensor.
 *
 * @return
 *   This function returns the value of LESENSE_SENSORSTATE register that
 *   represents the current state of the LESENSE sensor.
 ******************************************************************************/
__STATIC_INLINE uint32_t LESENSE_SensorStateGet(void)
{
  return LESENSE->SENSORSTATE;
}


/***************************************************************************//**
 * @brief
 *   Shut off power to the LESENSE RAM, disables LESENSE.
 *
 * @details
 *   This function shuts off the LESENSE RAM in order to decrease the leakage
 *   current of EFM32 if LESENSE is not used in your application.
 *
 * @note
 *   Warning! Once the LESENSE RAM is powered down, it cannot be powered up
 *   again.
 ******************************************************************************/
__STATIC_INLINE void LESENSE_RAMPowerDown(void)
{
  /* Power down LESENSE RAM */
  LESENSE->POWERDOWN = LESENSE_POWERDOWN_RAM;
}


/***************************************************************************//**
 * @brief
 *   Clear one or more pending LESENSE interrupts.
 *
 * @param[in] flags
 *   Pending LESENSE interrupt sources to clear. Use a set of interrupt flags
 *   OR-ed together to clear multiple interrupt sources of the LESENSE module
 *   (LESENSE_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void LESENSE_IntClear(uint32_t flags)
{
  LESENSE->IFC = flags;
}


/***************************************************************************//**
 * @brief
 *   Enable one or more LESENSE interrupts.
 *
 * @param[in] flags
 *   LESENSE interrupt sources to enable. Use a set of interrupt flags OR-ed
 *   together to enable multiple interrupt sources of the LESENSE module
 *   (LESENSE_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void LESENSE_IntEnable(uint32_t flags)
{
  LESENSE->IEN |= flags;
}


/***************************************************************************//**
 * @brief
 *   Disable one or more LESENSE interrupts.
 *
 * @param[in] flags
 *   LESENSE interrupt sources to disable. Use a set of interrupt flags OR-ed
 *   together to disable multiple interrupt sources of the LESENSE module
 *   (LESENSE_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void LESENSE_IntDisable(uint32_t flags)
{
  LESENSE->IEN &= ~(flags);
}


/***************************************************************************//**
 * @brief
 *   Set one or more pending LESENSE interrupts from SW.
 *
 * @param[in] flags
 *   LESENSE interrupt sources to set to pending. Use a set of interrupt
 *   flags OR-ed together to set multiple interrupt sources of the LESENSE
 *   module (LESENSE_IFS_nnn).
 ******************************************************************************/
__STATIC_INLINE void LESENSE_IntSet(uint32_t flags)
{
  LESENSE->IFS = flags;
}


/***************************************************************************//**
 * @brief
 *   Get pending LESENSE interrupt flags.
 *
 * @note
 *   The event bits are not cleared by the use of this function.
 *
 * @return
 *   Pending LESENSE interrupt sources. The OR combination of valid interrupt
 *   flags of the LESENSE module (LESENSE_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t LESENSE_IntGet(void)
{
  return LESENSE->IF;
}


/***************************************************************************//**
 * @brief
 *   Get enabled and pending LESENSE interrupt flags.
 *
 * @details
 *   Useful for handling more interrupt sources in the same interrupt handler.
 *
 * @note
 *   The event bits are not cleared by the use of this function.
 *
 * @return
 *   Pending and enabled LESENSE interrupt sources.
 *   The return value is the bitwise AND combination of
 *   - the OR combination of enabled interrupt sources in LESENSE_IEN_nnn
 *   register (LESENSE_IEN_nnn) and
 *   - the OR combination of valid interrupt flags of the LESENSE module
 *   (LESENSE_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t LESENSE_IntGetEnabled(void)
{
  uint32_t tmp;

  /* Store LESENSE->IEN in temporary variable in order to define explicit order
   * of volatile accesses. */
  tmp = LESENSE->IEN;

  /* Bitwise AND of pending and enabled interrupts */
  return LESENSE->IF & tmp;
}


/** @} (end addtogroup LESENSE) */
/** @} (end addtogroup EM_Library) */

#ifdef __cplusplus
}
#endif

#endif /* defined(LESENSE_COUNT) && (LESENSE_COUNT > 0) */

#endif /* __EM_LESENSE_H */
