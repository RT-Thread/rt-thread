/***************************************************************************//**
 * @file
 * @brief Analog to Digital Converter (ADC) peripheral API
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
#ifndef __EM_ADC_H
#define __EM_ADC_H

#include <stdbool.h>
#include "em_part.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup ADC
 * @{
 ******************************************************************************/

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** Acquisition time (in ADC clock cycles). */
typedef enum
{
  adcAcqTime1   = _ADC_SINGLECTRL_AT_1CYCLE,    /**< 1 clock cycle. */
  adcAcqTime2   = _ADC_SINGLECTRL_AT_2CYCLES,   /**< 2 clock cycles. */
  adcAcqTime4   = _ADC_SINGLECTRL_AT_4CYCLES,   /**< 4 clock cycles. */
  adcAcqTime8   = _ADC_SINGLECTRL_AT_8CYCLES,   /**< 8 clock cycles. */
  adcAcqTime16  = _ADC_SINGLECTRL_AT_16CYCLES,  /**< 16 clock cycles. */
  adcAcqTime32  = _ADC_SINGLECTRL_AT_32CYCLES,  /**< 32 clock cycles. */
  adcAcqTime64  = _ADC_SINGLECTRL_AT_64CYCLES,  /**< 64 clock cycles. */
  adcAcqTime128 = _ADC_SINGLECTRL_AT_128CYCLES, /**< 128 clock cycles. */
  adcAcqTime256 = _ADC_SINGLECTRL_AT_256CYCLES  /**< 256 clock cycles. */
} ADC_AcqTime_TypeDef;


/** Lowpass filter mode. */
typedef enum
{
  /** No filter or decoupling capacitor. */
  adcLPFilterBypass = _ADC_CTRL_LPFMODE_BYPASS,

  /** On-chip RC filter. */
  adcLPFilterRC     = _ADC_CTRL_LPFMODE_RCFILT,

  /** On-chip decoupling capacitor. */
  adcLPFilterDeCap  = _ADC_CTRL_LPFMODE_DECAP
} ADC_LPFilter_TypeDef;


/** Oversample rate select. */
typedef enum
{
  /** 2 samples per conversion result. */
  adcOvsRateSel2    = _ADC_CTRL_OVSRSEL_X2,

  /** 4 samples per conversion result. */
  adcOvsRateSel4    = _ADC_CTRL_OVSRSEL_X4,

  /** 8 samples per conversion result. */
  adcOvsRateSel8    = _ADC_CTRL_OVSRSEL_X8,

  /** 16 samples per conversion result. */
  adcOvsRateSel16   = _ADC_CTRL_OVSRSEL_X16,

  /** 32 samples per conversion result. */
  adcOvsRateSel32   = _ADC_CTRL_OVSRSEL_X32,

  /** 64 samples per conversion result. */
  adcOvsRateSel64   = _ADC_CTRL_OVSRSEL_X64,

  /** 128 samples per conversion result. */
  adcOvsRateSel128  = _ADC_CTRL_OVSRSEL_X128,

  /** 256 samples per conversion result. */
  adcOvsRateSel256  = _ADC_CTRL_OVSRSEL_X256,

  /** 512 samples per conversion result. */
  adcOvsRateSel512  = _ADC_CTRL_OVSRSEL_X512,

  /** 1024 samples per conversion result. */
  adcOvsRateSel1024 = _ADC_CTRL_OVSRSEL_X1024,

  /** 2048 samples per conversion result. */
  adcOvsRateSel2048 = _ADC_CTRL_OVSRSEL_X2048,

  /** 4096 samples per conversion result. */
  adcOvsRateSel4096 = _ADC_CTRL_OVSRSEL_X4096
} ADC_OvsRateSel_TypeDef;


/** Peripheral Reflex System signal used to trigger single sample. */
typedef enum
{
  adcPRSSELCh0 = _ADC_SINGLECTRL_PRSSEL_PRSCH0, /**< PRS channel 0. */
  adcPRSSELCh1 = _ADC_SINGLECTRL_PRSSEL_PRSCH1, /**< PRS channel 1. */
  adcPRSSELCh2 = _ADC_SINGLECTRL_PRSSEL_PRSCH2, /**< PRS channel 2. */
  adcPRSSELCh3 = _ADC_SINGLECTRL_PRSSEL_PRSCH3, /**< PRS channel 3. */
  adcPRSSELCh4 = _ADC_SINGLECTRL_PRSSEL_PRSCH4, /**< PRS channel 4. */
  adcPRSSELCh5 = _ADC_SINGLECTRL_PRSSEL_PRSCH5, /**< PRS channel 5. */
  adcPRSSELCh6 = _ADC_SINGLECTRL_PRSSEL_PRSCH6, /**< PRS channel 6. */
  adcPRSSELCh7 = _ADC_SINGLECTRL_PRSSEL_PRSCH7  /**< PRS channel 7. */
} ADC_PRSSEL_TypeDef;


/** Reference to ADC sample. */
typedef enum
{
  /** Internal 1.25V reference. */
  adcRef1V25      = _ADC_SINGLECTRL_REF_1V25,

  /** Internal 2.5V reference. */
  adcRef2V5       = _ADC_SINGLECTRL_REF_2V5,

  /** Buffered VDD. */
  adcRefVDD       = _ADC_SINGLECTRL_REF_VDD,

  /** Internal differential 5V reference. */
  adcRef5VDIFF    = _ADC_SINGLECTRL_REF_5VDIFF,

  /** Single ended ext. ref. from pin 6. */
  adcRefExtSingle = _ADC_SINGLECTRL_REF_EXTSINGLE,

  /** Differential ext. ref. from pin 6 and 7. */
  adcRef2xExtDiff = _ADC_SINGLECTRL_REF_2XEXTDIFF,

  /** Unbuffered 2xVDD. */
  adcRef2xVDD     = _ADC_SINGLECTRL_REF_2XVDD
} ADC_Ref_TypeDef;


/** Sample resolution. */
typedef enum
{
  adcRes12Bit = _ADC_SINGLECTRL_RES_12BIT, /**< 12 bit sampling. */
  adcRes8Bit  = _ADC_SINGLECTRL_RES_8BIT,  /**< 8 bit sampling. */
  adcRes6Bit  = _ADC_SINGLECTRL_RES_6BIT,  /**< 6 bit sampling. */
  adcResOVS   = _ADC_SINGLECTRL_RES_OVS    /**< Oversampling. */
} ADC_Res_TypeDef;


/** Single sample input selection. */
typedef enum
{
  /* Differential mode disabled */
  adcSingleInpCh0      = _ADC_SINGLECTRL_INPUTSEL_CH0,      /**< Channel 0. */
  adcSingleInpCh1      = _ADC_SINGLECTRL_INPUTSEL_CH1,      /**< Channel 1. */
  adcSingleInpCh2      = _ADC_SINGLECTRL_INPUTSEL_CH2,      /**< Channel 2. */
  adcSingleInpCh3      = _ADC_SINGLECTRL_INPUTSEL_CH3,      /**< Channel 3. */
  adcSingleInpCh4      = _ADC_SINGLECTRL_INPUTSEL_CH4,      /**< Channel 4. */
  adcSingleInpCh5      = _ADC_SINGLECTRL_INPUTSEL_CH5,      /**< Channel 5. */
  adcSingleInpCh6      = _ADC_SINGLECTRL_INPUTSEL_CH6,      /**< Channel 6. */
  adcSingleInpCh7      = _ADC_SINGLECTRL_INPUTSEL_CH7,      /**< Channel 7. */
  adcSingleInpTemp     = _ADC_SINGLECTRL_INPUTSEL_TEMP,     /**< Temperature reference. */
  adcSingleInpVDDDiv3  = _ADC_SINGLECTRL_INPUTSEL_VDDDIV3,  /**< VDD divided by 3. */
  adcSingleInpVDD      = _ADC_SINGLECTRL_INPUTSEL_VDD,      /**< VDD. */
  adcSingleInpVSS      = _ADC_SINGLECTRL_INPUTSEL_VSS,      /**< VSS. */
  adcSingleInpVrefDiv2 = _ADC_SINGLECTRL_INPUTSEL_VREFDIV2, /**< Vref divided by 2. */
  adcSingleInpDACOut0  = _ADC_SINGLECTRL_INPUTSEL_DAC0OUT0, /**< DAC output 0. */
  adcSingleInpDACOut1  = _ADC_SINGLECTRL_INPUTSEL_DAC0OUT1, /**< DAC output 1. */
  /* TBD: Use define when available */
  adcSingleInpATEST    = 15,                                /**< ATEST. */

  /* Differential mode enabled */
  adcSingleInpCh0Ch1   = _ADC_SINGLECTRL_INPUTSEL_CH0CH1,   /**< Positive Ch0, negative Ch1. */
  adcSingleInpCh2Ch3   = _ADC_SINGLECTRL_INPUTSEL_CH2CH3,   /**< Positive Ch2, negative Ch3. */
  adcSingleInpCh4Ch5   = _ADC_SINGLECTRL_INPUTSEL_CH4CH5,   /**< Positive Ch4, negative Ch5. */
  adcSingleInpCh6Ch7   = _ADC_SINGLECTRL_INPUTSEL_CH6CH7,   /**< Positive Ch6, negative Ch7. */
  /* TBD: Use define when available */
  adcSingleInpDiff0    = 4                                  /**< Differential 0. */
} ADC_SingleInput_TypeDef;


/** Acquisition time (in ADC clock cycles). */
typedef enum
{
  /** Start single conversion. */
  adcStartSingle        = ADC_CMD_SINGLESTART,

  /** Start scan sequence. */
  adcStartScan          = ADC_CMD_SCANSTART,

  /**
   * Start scan sequence and single conversion, typically used when tailgating
   * single conversion after scan sequence.
   */
  adcStartScanAndSingle = ADC_CMD_SCANSTART | ADC_CMD_SINGLESTART
} ADC_Start_TypeDef;


/** Warm-up mode. */
typedef enum
{
  /** ADC shutdown after each conversion. */
  adcWarmupNormal          = _ADC_CTRL_WARMUPMODE_NORMAL,

  /** Do not warm-up bandgap references. */
  adcWarmupFastBG          = _ADC_CTRL_WARMUPMODE_FASTBG,

  /** Reference selected for scan mode kept warm.*/
  adcWarmupKeepScanRefWarm = _ADC_CTRL_WARMUPMODE_KEEPSCANREFWARM,

  /** ADC and reference selected for scan mode kept warm.*/
  adcWarmupKeepADCWarm     = _ADC_CTRL_WARMUPMODE_KEEPADCWARM
} ADC_Warmup_TypeDef;


/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** ADC init structure, common for single conversion and scan sequence. */
typedef struct
{
  /**
   * Oversampling rate select. In order to have any effect, oversampling must
   * be enabled for single/scan mode.
   */
  ADC_OvsRateSel_TypeDef ovsRateSel;

  /** Lowpass or decoupling capacitor filter to use. */
  ADC_LPFilter_TypeDef   lpfMode;

  /** Warm-up mode to use for ADC. */
  ADC_Warmup_TypeDef     warmUpMode;

  /**
   * Timebase used for ADC warm up. Select N to give (N+1)HFPERCLK cycles.
   * (Additional delay is added for bandgap references, please refer to the
   * reference manual.) Normally, N should be selected so that the timebase
   * is at least 1 us. See ADC_TimebaseCalc() for a way to obtain
   * a suggested timebase of at least 1 us.
   */
  uint8_t                timebase;

  /** Clock division factor N, ADC clock =  HFPERCLK / (N + 1). */
  uint8_t                prescale;

  /** Enable/disable conversion tailgating. */
  bool                   tailgate;
} ADC_Init_TypeDef;

/** Default config for ADC init structure. */
#define ADC_INIT_DEFAULT                                                     \
  { adcOvsRateSel2,                /* 2x oversampling (if enabled). */       \
    adcLPFilterBypass,             /* No input filter selected. */           \
    adcWarmupNormal,               /* ADC shutdown after each conversion. */ \
    _ADC_CTRL_TIMEBASE_DEFAULT,    /* Use HW default value. */               \
    _ADC_CTRL_PRESC_DEFAULT,       /* Use HW default value. */               \
    false                          /* Do not use tailgate. */                \
  }


/** Scan sequence init structure. */
typedef struct
{
  /**
   * Peripheral reflex system trigger selection. Only applicable if @p prsEnable
   * is enabled.
   */
  ADC_PRSSEL_TypeDef  prsSel;

  /** Acquisition time (in ADC clock cycles). */
  ADC_AcqTime_TypeDef acqTime;

  /**
   * Sample reference selection. Notice that for external references, the
   * ADC calibration register must be set explicitly.
   */
  ADC_Ref_TypeDef     reference;

  /** Sample resolution. */
  ADC_Res_TypeDef     resolution;

  /**
   * Input scan selection. If single ended (@p diff is false), use logical
   * combination of ADC_SCANCTRL_INPUTMASK_CHx defines. If differential input
   * (@p diff is true), use logical combination of ADC_SCANCTRL_INPUTMASK_CHxCHy
   * defines. (Notice underscore prefix for defines used.)
   */
  uint32_t            input;

  /** Select if single ended or differential input. */
  bool                diff;

  /** Peripheral reflex system trigger enable. */
  bool                prsEnable;

  /** Select if left adjustment should be done. */
  bool                leftAdjust;

  /** Select if continuous conversion until explicit stop. */
  bool                rep;
} ADC_InitScan_TypeDef;

/** Default config for ADC scan init structure. */
#define ADC_INITSCAN_DEFAULT                                                        \
  { adcPRSSELCh0,              /* PRS ch0 (if enabled). */                          \
    adcAcqTime1,               /* 1 ADC_CLK cycle acquisition time. */              \
    adcRef1V25,                /* 1.25V internal reference. */                      \
    adcRes12Bit,               /* 12 bit resolution. */                             \
    0,                         /* No input selected. */                             \
    false,                     /* Single ended input. */                            \
    false,                     /* PRS disabled. */                                  \
    false,                     /* Right adjust. */                                  \
    false                      /* Deactivate conversion after one scan sequence. */ \
  }


/** Single conversion init structure. */
typedef struct
{
  /**
   * Peripheral reflex system trigger selection. Only applicable if @p prsEnable
   * is enabled.
   */
  ADC_PRSSEL_TypeDef      prsSel;

  /** Acquisition time (in ADC clock cycles). */
  ADC_AcqTime_TypeDef     acqTime;

  /**
   * Sample reference selection. Notice that for external references, the
   * ADC calibration register must be set explicitly.
   */
  ADC_Ref_TypeDef         reference;

  /** Sample resolution. */
  ADC_Res_TypeDef         resolution;

  /**
   * Sample input selection, use single ended or differential input according
   * to setting of @p diff.
   */
  ADC_SingleInput_TypeDef input;

  /** Select if single ended or differential input. */
  bool                    diff;

  /** Peripheral reflex system trigger enable. */
  bool                    prsEnable;

  /** Select if left adjustment should be done. */
  bool                    leftAdjust;

  /** Select if continuous conversion until explicit stop. */
  bool                    rep;
} ADC_InitSingle_TypeDef;

/** Default config for ADC single conversion init structure. */
#define ADC_INITSINGLE_DEFAULT                                                      \
  { adcPRSSELCh0,              /* PRS ch0 (if enabled). */                          \
    adcAcqTime1,               /* 1 ADC_CLK cycle acquisition time. */              \
    adcRef1V25,                /* 1.25V internal reference. */                      \
    adcRes12Bit,               /* 12 bit resolution. */                             \
    adcSingleInpCh0,           /* CH0 input selected. */                            \
    false,                     /* Single ended input. */                            \
    false,                     /* PRS disabled. */                                  \
    false,                     /* Right adjust. */                                  \
    false                      /* Deactivate conversion after one scan sequence. */ \
  }


/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Get single conversion result.
 *
 * @note
 *   Do only use if single conversion data valid.
 *
 * @param[in] adc
 *   Pointer to ADC peripheral register block.
 *
 * @return
 *
 ******************************************************************************/
__STATIC_INLINE uint32_t ADC_DataSingleGet(ADC_TypeDef *adc)
{
  return(adc->SINGLEDATA);
}


/***************************************************************************//**
 * @brief
 *   Get scan result.
 *
 * @note
 *   Do only use if scan data valid.
 *
 * @param[in] adc
 *   Pointer to ADC peripheral register block.
 ******************************************************************************/
__STATIC_INLINE uint32_t ADC_DataScanGet(ADC_TypeDef *adc)
{
  return(adc->SCANDATA);
}


void ADC_Init(ADC_TypeDef *adc, const ADC_Init_TypeDef *init);
void ADC_InitScan(ADC_TypeDef *adc, const ADC_InitScan_TypeDef *init);
void ADC_InitSingle(ADC_TypeDef *adc, const ADC_InitSingle_TypeDef *init);

/***************************************************************************//**
 * @brief
 *   Clear one or more pending ADC interrupts.
 *
 * @param[in] adc
 *   Pointer to ADC peripheral register block.
 *
 * @param[in] flags
 *   Pending ADC interrupt source to clear. Use a bitwise logic OR combination
 *   of valid interrupt flags for the ADC module (ADC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void ADC_IntClear(ADC_TypeDef *adc, uint32_t flags)
{
  adc->IFC = flags;
}


/***************************************************************************//**
 * @brief
 *   Disable one or more ADC interrupts.
 *
 * @param[in] adc
 *   Pointer to ADC peripheral register block.
 *
 * @param[in] flags
 *   ADC interrupt sources to disable. Use a bitwise logic OR combination of
 *   valid interrupt flags for the ADC module (ADC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void ADC_IntDisable(ADC_TypeDef *adc, uint32_t flags)
{
  adc->IEN &= ~(flags);
}


/***************************************************************************//**
 * @brief
 *   Enable one or more ADC interrupts.
 *
 * @note
 *   Depending on the use, a pending interrupt may already be set prior to
 *   enabling the interrupt. Consider using ADC_IntClear() prior to enabling
 *   if such a pending interrupt should be ignored.
 *
 * @param[in] adc
 *   Pointer to ADC peripheral register block.
 *
 * @param[in] flags
 *   ADC interrupt sources to enable. Use a bitwise logic OR combination of
 *   valid interrupt flags for the ADC module (ADC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void ADC_IntEnable(ADC_TypeDef *adc, uint32_t flags)
{
  adc->IEN |= flags;
}


/***************************************************************************//**
 * @brief
 *   Get pending ADC interrupt flags.
 *
 * @note
 *   The event bits are not cleared by the use of this function.
 *
 * @param[in] adc
 *   Pointer to ADC peripheral register block.
 *
 * @return
 *   ADC interrupt sources pending. A bitwise logic OR combination of valid
 *   interrupt flags for the ADC module (ADC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t ADC_IntGet(ADC_TypeDef *adc)
{
  return(adc->IF);
}


/***************************************************************************//**
 * @brief
 *   Set one or more pending ADC interrupts from SW.
 *
 * @param[in] adc
 *   Pointer to ADC peripheral register block.
 *
 * @param[in] flags
 *   ADC interrupt sources to set to pending. Use a bitwise logic OR combination
 *   of valid interrupt flags for the ADC module (ADC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void ADC_IntSet(ADC_TypeDef *adc, uint32_t flags)
{
  adc->IFS = flags;
}

uint8_t ADC_PrescaleCalc(uint32_t adcFreq, uint32_t hfperFreq);


/***************************************************************************//**
 * @brief
 *   Start scan sequence and/or single conversion.
 *
 * @param[in] adc
 *   Pointer to ADC peripheral register block.
 *
 * @param[in] cmd
 *   Command indicating which type of sampling to start.
 ******************************************************************************/
__STATIC_INLINE void ADC_Start(ADC_TypeDef *adc, ADC_Start_TypeDef cmd)
{
  adc->CMD = (uint32_t)cmd;
}

void ADC_Reset(ADC_TypeDef *adc);
uint8_t ADC_TimebaseCalc(uint32_t hfperFreq);

/** @} (end addtogroup ADC) */
/** @} (end addtogroup EM_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EM_ADC_H */
