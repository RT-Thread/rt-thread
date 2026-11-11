/***************************************************************************//**
 * @file
 * @brief Analog to Digital Converter (ADC) Peripheral API
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
#include "em_adc.h"
#include "em_cmu.h"
#include "em_assert.h"

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup ADC
 * @brief Analog to Digital Converter (ADC) Peripheral API
 * @{
 ******************************************************************************/

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/** Validation of ADC register block pointer reference for assert statements. */
#define ADC_REF_VALID(ref)    ((ref) == ADC0)

/** Max ADC clock */
#define ADC_MAX_CLOCK    13000000

/** Min ADC clock */
#define ADC_MIN_CLOCK    32000

/** @endcond */


/*******************************************************************************
 ***************************   LOCAL FUNCTIONS   *******************************
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/***************************************************************************//**
 * @brief
 *   Load SCAN calibrate register with predefined values for a certain
 *   reference.
 *
 * @details
 *   During production, calibration values are made and stored in the device
 *   information page for known references. Notice that for external references,
 *   calibration values must be determined explicitly, and this function
 *   will not modify the calibration register.
 *
 * @param[in] adc
 *   Pointer to ADC peripheral register block.
 *
 * @param[in] ref
 *   Reference to load calibrated values for. No values are loaded for
 *   external references.
 ******************************************************************************/
static void ADC_CalibrateLoadScan(ADC_TypeDef *adc, ADC_Ref_TypeDef ref)
{
  uint32_t cal;

  /* Load proper calibration data depending on selected reference */
  /* NOTE: We use ...SCAN... defines below, they are the same as */
  /* similar ...SINGLE... defines. */
  switch (ref)
  {
  case adcRef1V25:
    cal  = adc->CAL & ~(_ADC_CAL_SCANOFFSET_MASK | _ADC_CAL_SCANGAIN_MASK);
    cal |= ((DEVINFO->ADC0CAL0 & _DEVINFO_ADC0CAL0_1V25_GAIN_MASK) >>
            _DEVINFO_ADC0CAL0_1V25_GAIN_SHIFT) << _ADC_CAL_SCANGAIN_SHIFT;
    cal |= ((DEVINFO->ADC0CAL0 & _DEVINFO_ADC0CAL0_1V25_OFFSET_MASK) >>
            _DEVINFO_ADC0CAL0_1V25_OFFSET_SHIFT) << _ADC_CAL_SCANOFFSET_SHIFT;
    adc->CAL = cal;
    break;

  case adcRef2V5:
    cal  = adc->CAL & ~(_ADC_CAL_SCANOFFSET_MASK | _ADC_CAL_SCANGAIN_MASK);
    cal |= ((DEVINFO->ADC0CAL0 & _DEVINFO_ADC0CAL0_2V5_GAIN_MASK) >>
            _DEVINFO_ADC0CAL0_2V5_GAIN_SHIFT) << _ADC_CAL_SCANGAIN_SHIFT;
    cal |= ((DEVINFO->ADC0CAL0 & _DEVINFO_ADC0CAL0_2V5_OFFSET_MASK) >>
            _DEVINFO_ADC0CAL0_2V5_OFFSET_SHIFT) << _ADC_CAL_SCANOFFSET_SHIFT;
    adc->CAL = cal;
    break;

  case adcRefVDD:
    cal  = adc->CAL & ~(_ADC_CAL_SCANOFFSET_MASK | _ADC_CAL_SCANGAIN_MASK);
    cal |= ((DEVINFO->ADC0CAL1 & _DEVINFO_ADC0CAL1_VDD_GAIN_MASK) >>
            _DEVINFO_ADC0CAL1_VDD_GAIN_SHIFT) << _ADC_CAL_SCANGAIN_SHIFT;
    cal |= ((DEVINFO->ADC0CAL1 & _DEVINFO_ADC0CAL1_VDD_OFFSET_MASK) >>
            _DEVINFO_ADC0CAL1_VDD_OFFSET_SHIFT) << _ADC_CAL_SCANOFFSET_SHIFT;
    adc->CAL = cal;
    break;

  case adcRef5VDIFF:
    cal  = adc->CAL & ~(_ADC_CAL_SCANOFFSET_MASK | _ADC_CAL_SCANGAIN_MASK);
    cal |= ((DEVINFO->ADC0CAL1 & _DEVINFO_ADC0CAL1_5VDIFF_GAIN_MASK) >>
            _DEVINFO_ADC0CAL1_5VDIFF_GAIN_SHIFT) << _ADC_CAL_SCANGAIN_SHIFT;
    cal |= ((DEVINFO->ADC0CAL1 & _DEVINFO_ADC0CAL1_5VDIFF_OFFSET_MASK) >>
            _DEVINFO_ADC0CAL1_5VDIFF_OFFSET_SHIFT) << _ADC_CAL_SCANOFFSET_SHIFT;
    adc->CAL = cal;
    break;

  case adcRef2xVDD:
    /* Gain value not of relevance for this reference, leave as is */
    cal  = adc->CAL & ~_ADC_CAL_SCANOFFSET_MASK;
    cal |= ((DEVINFO->ADC0CAL2 & _DEVINFO_ADC0CAL2_2XVDDVSS_OFFSET_MASK) >>
            _DEVINFO_ADC0CAL2_2XVDDVSS_OFFSET_SHIFT) << _ADC_CAL_SCANOFFSET_SHIFT;
    adc->CAL = cal;
    break;

  /* For external references, the calibration must be determined for the */
  /* specific application and set explicitly. */
  default:
    break;
  }
}

/***************************************************************************//**
 * @brief
 *   Load SINGLE calibrate register with predefined values for a certain
 *   reference.
 *
 * @details
 *   During production, calibration values are made and stored in the device
 *   information page for known references. Notice that for external references,
 *   calibration values must be determined explicitly, and this function
 *   will not modify the calibration register.
 *
 * @param[in] adc
 *   Pointer to ADC peripheral register block.
 *
 * @param[in] ref
 *   Reference to load calibrated values for. No values are loaded for
 *   external references.
 ******************************************************************************/
static void ADC_CalibrateLoadSingle(ADC_TypeDef *adc, ADC_Ref_TypeDef ref)
{
  uint32_t cal;

  /* Load proper calibration data depending on selected reference */
  /* NOTE: We use ...SCAN... defines below, they are the same as */
  /* similar ...SINGLE... defines. */
  switch (ref)
  {
  case adcRef1V25:
    cal  = adc->CAL & ~(_ADC_CAL_SINGLEOFFSET_MASK | _ADC_CAL_SINGLEGAIN_MASK);
    cal |= ((DEVINFO->ADC0CAL0 & _DEVINFO_ADC0CAL0_1V25_GAIN_MASK) >>
            _DEVINFO_ADC0CAL0_1V25_GAIN_SHIFT) << _ADC_CAL_SINGLEGAIN_SHIFT;
    cal |= ((DEVINFO->ADC0CAL0 & _DEVINFO_ADC0CAL0_1V25_OFFSET_MASK) >>
            _DEVINFO_ADC0CAL0_1V25_OFFSET_SHIFT) << _ADC_CAL_SINGLEOFFSET_SHIFT;
    adc->CAL = cal;
    break;

  case adcRef2V5:
    cal  = adc->CAL & ~(_ADC_CAL_SINGLEOFFSET_MASK | _ADC_CAL_SINGLEGAIN_MASK);
    cal |= ((DEVINFO->ADC0CAL0 & _DEVINFO_ADC0CAL0_2V5_GAIN_MASK) >>
            _DEVINFO_ADC0CAL0_2V5_GAIN_SHIFT) << _ADC_CAL_SINGLEGAIN_SHIFT;
    cal |= ((DEVINFO->ADC0CAL0 & _DEVINFO_ADC0CAL0_2V5_OFFSET_MASK) >>
            _DEVINFO_ADC0CAL0_2V5_OFFSET_SHIFT) << _ADC_CAL_SINGLEOFFSET_SHIFT;
    adc->CAL = cal;
    break;

  case adcRefVDD:
    cal  = adc->CAL & ~(_ADC_CAL_SINGLEOFFSET_MASK | _ADC_CAL_SINGLEGAIN_MASK);
    cal |= ((DEVINFO->ADC0CAL1 & _DEVINFO_ADC0CAL1_VDD_GAIN_MASK) >>
            _DEVINFO_ADC0CAL1_VDD_GAIN_SHIFT) << _ADC_CAL_SINGLEGAIN_SHIFT;
    cal |= ((DEVINFO->ADC0CAL1 & _DEVINFO_ADC0CAL1_VDD_OFFSET_MASK) >>
            _DEVINFO_ADC0CAL1_VDD_OFFSET_SHIFT) << _ADC_CAL_SINGLEOFFSET_SHIFT;
    adc->CAL = cal;
    break;

  case adcRef5VDIFF:
    cal  = adc->CAL & ~(_ADC_CAL_SINGLEOFFSET_MASK | _ADC_CAL_SINGLEGAIN_MASK);
    cal |= ((DEVINFO->ADC0CAL1 & _DEVINFO_ADC0CAL1_5VDIFF_GAIN_MASK) >>
            _DEVINFO_ADC0CAL1_5VDIFF_GAIN_SHIFT) << _ADC_CAL_SINGLEGAIN_SHIFT;
    cal |= ((DEVINFO->ADC0CAL1 & _DEVINFO_ADC0CAL1_5VDIFF_OFFSET_MASK) >>
            _DEVINFO_ADC0CAL1_5VDIFF_OFFSET_SHIFT) << _ADC_CAL_SINGLEOFFSET_SHIFT;
    adc->CAL = cal;
    break;

  case adcRef2xVDD:
    /* Gain value not of relevance for this reference, leave as is */
    cal  = adc->CAL & ~_ADC_CAL_SINGLEOFFSET_MASK;
    cal |= ((DEVINFO->ADC0CAL2 & _DEVINFO_ADC0CAL2_2XVDDVSS_OFFSET_MASK) >>
            _DEVINFO_ADC0CAL2_2XVDDVSS_OFFSET_SHIFT) << _ADC_CAL_SINGLEOFFSET_SHIFT;
    adc->CAL = cal;
    break;

  /* For external references, the calibration must be determined for the */
  /* specific application and set explicitly. */
  default:
    break;
  }
}

/** @endcond */

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Initialize ADC.
 *
 * @details
 *   Initializes common parts for both single conversion and scan sequence.
 *   In addition, single and/or scan control configuration must be done, please
 *   refer to ADC_InitSingle() and ADC_InitScan() respectively.
 *
 * @note
 *   This function will stop any ongoing conversion.
 *
 * @param[in] adc
 *   Pointer to ADC peripheral register block.
 *
 * @param[in] init
 *   Pointer to ADC initialization structure.
 ******************************************************************************/
void ADC_Init(ADC_TypeDef *adc, const ADC_Init_TypeDef *init)
{
  uint32_t tmp;

  EFM_ASSERT(ADC_REF_VALID(adc));

  /* Make sure conversion is not in progress */
  adc->CMD = ADC_CMD_SINGLESTOP | ADC_CMD_SCANSTOP;

  tmp = ((uint32_t)(init->ovsRateSel) << _ADC_CTRL_OVSRSEL_SHIFT) |
        (((uint32_t)(init->timebase) << _ADC_CTRL_TIMEBASE_SHIFT) & _ADC_CTRL_TIMEBASE_MASK) |
        (((uint32_t)(init->prescale) << _ADC_CTRL_PRESC_SHIFT) & _ADC_CTRL_PRESC_MASK) |
        ((uint32_t)(init->lpfMode) << _ADC_CTRL_LPFMODE_SHIFT) |
        ((uint32_t)(init->warmUpMode) << _ADC_CTRL_WARMUPMODE_SHIFT);

  if (init->tailgate)
  {
    tmp |= ADC_CTRL_TAILGATE;
  }

  adc->CTRL = tmp;
}


/***************************************************************************//**
 * @brief
 *   Initialize ADC scan sequence.
 *
 * @details
 *   Please refer to ADC_StartScan() for starting scan sequence.
 *
 *   When selecting an external reference, the gain and offset calibration
 *   must be set explicitly (CAL register). For other references, the
 *   calibration is updated with values defined during manufacturing.
 *
 * @note
 *   This function will stop any ongoing scan sequence.
 *
 * @param[in] adc
 *   Pointer to ADC peripheral register block.
 *
 * @param[in] init
 *   Pointer to ADC initialization structure.
 ******************************************************************************/
void ADC_InitScan(ADC_TypeDef *adc, const ADC_InitScan_TypeDef *init)
{
  uint32_t tmp;

  EFM_ASSERT(ADC_REF_VALID(adc));

  /* Make sure scan sequence is not in progress */
  adc->CMD = ADC_CMD_SCANSTOP;

  /* Load proper calibration data depending on selected reference */
  ADC_CalibrateLoadScan(adc, init->reference);

  tmp = ((uint32_t)(init->prsSel) << _ADC_SCANCTRL_PRSSEL_SHIFT) |
        ((uint32_t)(init->acqTime) << _ADC_SCANCTRL_AT_SHIFT) |
        ((uint32_t)(init->reference) << _ADC_SCANCTRL_REF_SHIFT) |
        init->input |
        ((uint32_t)(init->resolution) << _ADC_SCANCTRL_RES_SHIFT);

  if (init->prsEnable)
  {
    tmp |= ADC_SCANCTRL_PRSEN;
  }

  if (init->leftAdjust)
  {
    tmp |= ADC_SCANCTRL_ADJ_LEFT;
  }

  if (init->diff)
  {
    tmp |= ADC_SCANCTRL_DIFF;
  }

  if (init->rep)
  {
    tmp |= ADC_SCANCTRL_REP;
  }

  adc->SCANCTRL = tmp;
}


/***************************************************************************//**
 * @brief
 *   Initialize single ADC sample conversion.
 *
 * @details
 *   Please refer to ADC_StartSingle() for starting single conversion.
 *
 *   When selecting an external reference, the gain and offset calibration
 *   must be set explicitly (CAL register). For other references, the
 *   calibration is updated with values defined during manufacturing.
 *
 * @note
 *   This function will stop any ongoing single conversion.
 *
 * @param[in] adc
 *   Pointer to ADC peripheral register block.
 *
 * @param[in] init
 *   Pointer to ADC initialization structure.
 ******************************************************************************/
void ADC_InitSingle(ADC_TypeDef *adc, const ADC_InitSingle_TypeDef *init)
{
  uint32_t tmp;

  EFM_ASSERT(ADC_REF_VALID(adc));

  /* Make sure single conversion is not in progress */
  adc->CMD = ADC_CMD_SINGLESTOP;

  /* Load proper calibration data depending on selected reference */
  ADC_CalibrateLoadSingle(adc, init->reference);

  tmp = ((uint32_t)(init->prsSel) << _ADC_SINGLECTRL_PRSSEL_SHIFT) |
        ((uint32_t)(init->acqTime) << _ADC_SINGLECTRL_AT_SHIFT) |
        ((uint32_t)(init->reference) << _ADC_SINGLECTRL_REF_SHIFT) |
        ((uint32_t)(init->input) << _ADC_SINGLECTRL_INPUTSEL_SHIFT) |
        ((uint32_t)(init->resolution) << _ADC_SINGLECTRL_RES_SHIFT);

  if (init->prsEnable)
  {
    tmp |= ADC_SINGLECTRL_PRSEN;
  }

  if (init->leftAdjust)
  {
    tmp |= ADC_SINGLECTRL_ADJ_LEFT;
  }

  if (init->diff)
  {
    tmp |= ADC_SINGLECTRL_DIFF;
  }

  if (init->rep)
  {
    tmp |= ADC_SINGLECTRL_REP;
  }

  adc->SINGLECTRL = tmp;
}


/***************************************************************************//**
 * @brief
 *   Calculate prescaler value used to determine ADC clock.
 *
 * @details
 *   The ADC clock is given by: HFPERCLK / (prescale + 1).
 *
 * @param[in] adcFreq ADC frequency wanted. The frequency will automatically
 *   be adjusted to be within valid range according to reference manual.
 *
 * @param[in] hfperFreq Frequency in Hz of reference HFPER clock. Set to 0 to
 *   use currently defined HFPER clock setting.
 *
 * @return
 *   Prescaler value to use for ADC in order to achieve a clock value
 *   <= @p adcFreq.
 ******************************************************************************/
uint8_t ADC_PrescaleCalc(uint32_t adcFreq, uint32_t hfperFreq)
{
  uint32_t ret;

  /* Make sure selected ADC clock is within valid range */
  if (adcFreq > ADC_MAX_CLOCK)
  {
    adcFreq = ADC_MAX_CLOCK;
  }
  else if (adcFreq < ADC_MIN_CLOCK)
  {
    adcFreq = ADC_MIN_CLOCK;
  }

  /* Use current HFPER frequency? */
  if (!hfperFreq)
  {
    hfperFreq = CMU_ClockFreqGet(cmuClock_HFPER);
  }

  ret = (hfperFreq + adcFreq - 1) / adcFreq;
  if (ret)
  {
    ret--;
  }

  return (uint8_t)ret;
}


/***************************************************************************//**
 * @brief
 *   Reset ADC to same state as after a HW reset.
 *
 * @note
 *   The ROUTE register is NOT reset by this function, in order to allow for
 *   centralized setup of this feature.
 *
 * @param[in] adc
 *   Pointer to ADC peripheral register block.
 ******************************************************************************/
void ADC_Reset(ADC_TypeDef *adc)
{
  uint32_t cal;

  /* Stop conversions, before resetting other registers. */
  adc->CMD        = ADC_CMD_SINGLESTOP | ADC_CMD_SCANSTOP;
  adc->SINGLECTRL = _ADC_SINGLECTRL_RESETVALUE;
  adc->SCANCTRL   = _ADC_SCANCTRL_RESETVALUE;
  adc->CTRL       = _ADC_CTRL_RESETVALUE;
  adc->IEN        = _ADC_IEN_RESETVALUE;
  adc->IFC        = _ADC_IFC_MASK;
  adc->BIASPROG   = _ADC_BIASPROG_RESETVALUE;

  cal  = adc->CAL & ~(_ADC_CAL_SINGLEOFFSET_MASK | _ADC_CAL_SINGLEGAIN_MASK);
  cal |= ((DEVINFO->ADC0CAL0 & _DEVINFO_ADC0CAL0_1V25_GAIN_MASK) >>
          _DEVINFO_ADC0CAL0_1V25_GAIN_SHIFT) << _ADC_CAL_SINGLEGAIN_SHIFT;
  cal |= ((DEVINFO->ADC0CAL0 & _DEVINFO_ADC0CAL0_1V25_OFFSET_MASK) >>
          _DEVINFO_ADC0CAL0_1V25_OFFSET_SHIFT) << _ADC_CAL_SINGLEOFFSET_SHIFT;
  adc->CAL = cal;

  /* Do not reset route register, setting should be done independently */
}


/***************************************************************************//**
 * @brief
 *   Calculate timebase value in order to get a timebase providing at least 1us.
 *
 * @param[in] hfperFreq Frequency in Hz of reference HFPER clock. Set to 0 to
 *   use currently defined HFPER clock setting.
 *
 * @return
 *   Timebase value to use for ADC in order to achieve at least 1 us.
 ******************************************************************************/
uint8_t ADC_TimebaseCalc(uint32_t hfperFreq)
{
  if (!hfperFreq)
  {
    hfperFreq = CMU_ClockFreqGet(cmuClock_HFPER);

    /* Just in case, make sure we get non-zero freq for below calculation */
    if (!hfperFreq)
    {
      hfperFreq = 1;
    }
  }
#if defined(_EFM32_GIANT_FAMILY)
  /* Handle errata on Giant Gecko, max TIMEBASE is 5 bits wide or max 0x1F */
  /* cycles. This will give a warmp up time of e.g. 0.645us, not the       */
  /* required 1us when operating at 48MHz. One must also increase acqTime  */
  /* to compensate for the missing clock cycles, adding up to 1us in total.*/
  /* See reference manual for details. */
  if( hfperFreq > 32000000 )
  {
    hfperFreq = 32000000;
  }
#endif
  /* Determine number of HFPERCLK cycle >= 1us */
  hfperFreq += 999999;
  hfperFreq /= 1000000;

  /* Return timebase value (N+1 format) */
  return (uint8_t)(hfperFreq - 1);
}


/** @} (end addtogroup ADC) */
/** @} (end addtogroup EM_Library) */
