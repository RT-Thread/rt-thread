/***************************************************************************//**
 * @file
 * @brief Digital to Analog Converter (DAC) peripheral API
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
#ifndef __EM_DAC_H
#define __EM_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "em_part.h"

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup DAC
 * @{
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/** Validation of DAC register block pointer reference for assert statements. */
#define DAC_REF_VALID(ref)    ((ref) == DAC0)

/** @endcond */

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** Conversion mode. */
typedef enum
{
  dacConvModeContinuous = _DAC_CTRL_CONVMODE_CONTINUOUS, /**< Continuous mode. */
  dacConvModeSampleHold = _DAC_CTRL_CONVMODE_SAMPLEHOLD, /**< Sample/hold mode. */
  dacConvModeSampleOff  = _DAC_CTRL_CONVMODE_SAMPLEOFF   /**< Sample/shut off mode. */
} DAC_ConvMode_TypeDef;

/** Output mode. */
typedef enum
{
  dacOutputDisable = _DAC_CTRL_OUTMODE_DISABLE, /**< Output to pin and ADC disabled. */
  dacOutputPin     = _DAC_CTRL_OUTMODE_PIN,     /**< Output to pin only. */
  dacOutputADC     = _DAC_CTRL_OUTMODE_ADC,     /**< Output to ADC only */
  dacOutputPinADC  = _DAC_CTRL_OUTMODE_PINADC   /**< Output to pin and ADC. */
} DAC_Output_TypeDef;


/** Peripheral Reflex System signal used to trigger single sample. */
typedef enum
{
  dacPRSSELCh0 = _DAC_CH0CTRL_PRSSEL_PRSCH0, /**< PRS channel 0. */
  dacPRSSELCh1 = _DAC_CH0CTRL_PRSSEL_PRSCH1, /**< PRS channel 1. */
  dacPRSSELCh2 = _DAC_CH0CTRL_PRSSEL_PRSCH2, /**< PRS channel 2. */
  dacPRSSELCh3 = _DAC_CH0CTRL_PRSSEL_PRSCH3, /**< PRS channel 3. */
  dacPRSSELCh4 = _DAC_CH0CTRL_PRSSEL_PRSCH4, /**< PRS channel 4. */
  dacPRSSELCh5 = _DAC_CH0CTRL_PRSSEL_PRSCH5, /**< PRS channel 5. */
  dacPRSSELCh6 = _DAC_CH0CTRL_PRSSEL_PRSCH6, /**< PRS channel 6. */
  dacPRSSELCh7 = _DAC_CH0CTRL_PRSSEL_PRSCH7  /**< PRS channel 7. */
} DAC_PRSSEL_TypeDef;


/** Reference voltage for DAC. */
typedef enum
{
  dacRef1V25 = _DAC_CTRL_REFSEL_1V25, /**< Internal 1.25V bandgap reference. */
  dacRef2V5  = _DAC_CTRL_REFSEL_2V5,  /**< Internal 2.5V bandgap reference. */
  dacRefVDD  = _DAC_CTRL_REFSEL_VDD   /**< VDD reference. */
} DAC_Ref_TypeDef;


/** Refresh interval. */
typedef enum
{
  dacRefresh8  = _DAC_CTRL_REFRSEL_8CYCLES,  /**< Refresh every 8 prescaled cycles. */
  dacRefresh16 = _DAC_CTRL_REFRSEL_16CYCLES, /**< Refresh every 16 prescaled cycles. */
  dacRefresh32 = _DAC_CTRL_REFRSEL_32CYCLES, /**< Refresh every 32 prescaled cycles. */
  dacRefresh64 = _DAC_CTRL_REFRSEL_64CYCLES  /**< Refresh every 64 prescaled cycles. */
} DAC_Refresh_TypeDef;


/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** DAC init structure, common for both channels. */
typedef struct
{
  /** Refresh interval. Only used if REFREN bit set for a DAC channel. */
  DAC_Refresh_TypeDef  refresh;

  /** Reference voltage to use. */
  DAC_Ref_TypeDef      reference;

  /** Output mode */
  DAC_Output_TypeDef   outMode;

  /** Conversion mode. */
  DAC_ConvMode_TypeDef convMode;

  /**
   * Prescaler used to get DAC clock. Derived as follows:
   * DACclk=HFPERclk/(2^prescale). The DAC clock should be <= 1MHz.
   */
  uint8_t              prescale;

  /** Enable/disable use of low pass filter on output. */
  bool                 lpEnable;

  /** Enable/disable reset of prescaler on ch0 start. */
  bool                 ch0ResetPre;

  /** Enable/disable output enable control by CH1 PRS signal. */
  bool                 outEnablePRS;

  /** Enable/disable sine mode. */
  bool                 sineEnable;

  /** Select if single ended or differential mode. */
  bool                 diff;
} DAC_Init_TypeDef;

/** Default config for DAC init structure. */
#define DAC_INIT_DEFAULT                                                 \
  { dacRefresh8,              /* Refresh every 8 prescaled cycles. */    \
    dacRef1V25,               /* 1.25V internal reference. */            \
    dacOutputPin,             /* Output to pin only. */                  \
    dacConvModeContinuous,    /* Continuous mode. */                     \
    0,                        /* No prescaling. */                       \
    false,                    /* Do not enable low pass filter. */       \
    false,                    /* Do not reset prescaler on ch0 start. */ \
    false,                    /* DAC output enable always on. */         \
    false,                    /* Disable sine mode. */                   \
    false                     /* Single ended mode. */                   \
  }


/** DAC channel init structure. */
typedef struct
{
  /** Enable channel. */
  bool               enable;

  /**
   * Peripheral reflex system trigger enable. If false, channel is triggered
   * by writing to CHnDATA.
   */
  bool               prsEnable;

  /**
   * Enable/disable automatic refresh of channel. Refresh interval must be
   * defined in common control init, please see DAC_Init().
   */
  bool               refreshEnable;

  /**
   * Peripheral reflex system trigger selection. Only applicable if @p prsEnable
   * is enabled.
   */
  DAC_PRSSEL_TypeDef prsSel;
} DAC_InitChannel_TypeDef;

/** Default config for DAC channel init structure. */
#define DAC_INITCHANNEL_DEFAULT                                           \
  { false,              /* Leave channel disabled when init done. */      \
    false,              /* Disable PRS triggering. */                     \
    false,              /* Channel not refreshed automatically. */        \
    dacPRSSELCh0        /* Select PRS ch0 (if PRS triggering enabled). */ \
  }


/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

void DAC_Enable(DAC_TypeDef *dac, unsigned int ch, bool enable);
void DAC_Init(DAC_TypeDef *dac, const DAC_Init_TypeDef *init);
void DAC_InitChannel(DAC_TypeDef *dac,
                     const DAC_InitChannel_TypeDef *init,
                     unsigned int ch);

/***************************************************************************//**
 * @brief
 *   Clear one or more pending DAC interrupts.
 *
 * @param[in] dac
 *   Pointer to DAC peripheral register block.
 *
 * @param[in] flags
 *   Pending DAC interrupt source to clear. Use a bitwise logic OR combination of
 *   valid interrupt flags for the DAC module (DAC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void DAC_IntClear(DAC_TypeDef *dac, uint32_t flags)
{
  dac->IFC = flags;
}


/***************************************************************************//**
 * @brief
 *   Disable one or more DAC interrupts.
 *
 * @param[in] dac
 *   Pointer to DAC peripheral register block.
 *
 * @param[in] flags
 *   DAC interrupt sources to disable. Use a bitwise logic OR combination of
 *   valid interrupt flags for the DAC module (DAC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void DAC_IntDisable(DAC_TypeDef *dac, uint32_t flags)
{
  dac->IEN &= ~(flags);
}


/***************************************************************************//**
 * @brief
 *   Enable one or more DAC interrupts.
 *
 * @note
 *   Depending on the use, a pending interrupt may already be set prior to
 *   enabling the interrupt. Consider using DAC_IntClear() prior to enabling
 *   if such a pending interrupt should be ignored.
 *
 * @param[in] dac
 *   Pointer to DAC peripheral register block.
 *
 * @param[in] flags
 *   DAC interrupt sources to enable. Use a bitwise logic OR combination of
 *   valid interrupt flags for the DAC module (DAC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void DAC_IntEnable(DAC_TypeDef *dac, uint32_t flags)
{
  dac->IEN |= flags;
}


/***************************************************************************//**
 * @brief
 *   Get pending DAC interrupt flags.
 *
 * @note
 *   The event bits are not cleared by the use of this function.
 *
 * @param[in] dac
 *   Pointer to DAC peripheral register block.
 *
 * @return
 *   DAC interrupt sources pending. A bitwise logic OR combination of valid
 *   interrupt flags for the DAC module (DAC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t DAC_IntGet(DAC_TypeDef *dac)
{
  return(dac->IF);
}


/***************************************************************************//**
 * @brief
 *   Set one or more pending DAC interrupts from SW.
 *
 * @param[in] dac
 *   Pointer to DAC peripheral register block.
 *
 * @param[in] flags
 *   DAC interrupt sources to set to pending. Use a bitwise logic OR combination
 *   of valid interrupt flags for the DAC module (DAC_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void DAC_IntSet(DAC_TypeDef *dac, uint32_t flags)
{
  dac->IFS = flags;
}

uint8_t DAC_PrescaleCalc(uint32_t dacFreq, uint32_t hfperFreq);
void DAC_Reset(DAC_TypeDef *dac);

/** @} (end addtogroup DAC) */
/** @} (end addtogroup EM_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EM_DAC_H */
