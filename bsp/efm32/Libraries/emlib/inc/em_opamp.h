/**************************************************************************//**
 * @file
 * @brief Operational Amplifier (OPAMP) peripheral API
 * @author Energy Micro AS
 * @version 3.0.0
 ******************************************************************************
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
 *****************************************************************************/
#ifndef __EM_OPAMP_H
#define __EM_OPAMP_H

#include "em_part.h"
#if defined(OPAMP_PRESENT) && (OPAMP_COUNT == 1)

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "em_dac.h"

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup OPAMP
 * @{
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/** Validation of DAC OPA number for assert statements. */
#define DAC_OPA_VALID(opa)    ((opa) <= OPA2)

/** @endcond */

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** OPAMP selector values. */
typedef enum
{
  OPA0 = 0,                   /**< Select OPA0. */
  OPA1 = 1,                   /**< Select OPA1. */
  OPA2 = 2                    /**< Select OPA2. */
} OPAMP_TypeDef;

/** OPAMP negative terminal input selection values. */
typedef enum
{
  opaNegSelDisable   = DAC_OPA0MUX_NEGSEL_DISABLE,    /**< Input disabled.               */
  opaNegSelUnityGain = DAC_OPA0MUX_NEGSEL_UG,         /**< Unity gain feedback path.     */
  opaNegSelResTap    = DAC_OPA0MUX_NEGSEL_OPATAP,     /**< Feedback resistor ladder tap. */
  opaNegSelNegPad    = DAC_OPA0MUX_NEGSEL_NEGPAD      /**< Negative pad as input.        */
} OPAMP_NegSel_TypeDef;

/** OPAMP positive terminal input selection values. */
typedef enum
{
  opaPosSelDisable    = DAC_OPA0MUX_POSSEL_DISABLE,   /**< Input disabled.          */
  opaPosSelDac        = DAC_OPA0MUX_POSSEL_DAC,       /**< DAC as input (not OPA2). */
  opaPosSelPosPad     = DAC_OPA0MUX_POSSEL_POSPAD,    /**< Positive pad as input.   */
  opaPosSelOpaIn      = DAC_OPA0MUX_POSSEL_OPA0INP,   /**< Input from OPAx.         */
  opaPosSelResTapOpa0 = DAC_OPA0MUX_POSSEL_OPATAP     /**< Feedback resistor ladder tap from OPA0. */
} OPAMP_PosSel_TypeDef;

/** OPAMP output terminal selection values. */
typedef enum
{
  opaOutModeDisable = DAC_OPA0MUX_OUTMODE_DISABLE,    /**< OPA output disabled.        */
  opaOutModeMain    = DAC_OPA0MUX_OUTMODE_MAIN,       /**< Main output to pin enabled. */
  opaOutModeAlt     = DAC_OPA0MUX_OUTMODE_ALT,        /**< Alternate output(s) enabled (not OPA2).     */
  opaOutModeAll     = DAC_OPA0MUX_OUTMODE_ALL         /**< Both main and alternate enabled (not OPA2). */
} OPAMP_OutMode_TypeDef;

/** OPAMP gain values. */
typedef enum
{
  opaResSelDefault    = DAC_OPA0MUX_RESSEL_DEFAULT,  /**< Default value when resistor ladder is unused. */
  opaResSelR2eq0_33R1 = DAC_OPA0MUX_RESSEL_RES0,     /**< R2 = 0.33 * R1 */
  opaResSelR2eqR1     = DAC_OPA0MUX_RESSEL_RES1,     /**< R2 = R1        */
  opaResSelR1eq1_67R1 = DAC_OPA0MUX_RESSEL_RES2,     /**< R2 = 1.67 R1   */
  opaResSelR2eq2R1    = DAC_OPA0MUX_RESSEL_RES3,     /**< R2 = 2 * R1    */
  opaResSelR2eq3R1    = DAC_OPA0MUX_RESSEL_RES4,     /**< R2 = 3 * R1    */
  opaResSelR2eq4_33R1 = DAC_OPA0MUX_RESSEL_RES5,     /**< R2 = 4.33 * R1 */
  opaResSelR2eq7R1    = DAC_OPA0MUX_RESSEL_RES6,     /**< R2 = 7 * R1    */
  opaResSelR2eq15R1   = DAC_OPA0MUX_RESSEL_RES7      /**< R2 = 15 * R1   */
} OPAMP_ResSel_TypeDef;

/** OPAMP resistor ladder input selector values. */
typedef enum
{
  opaResInMuxDisable = DAC_OPA0MUX_RESINMUX_DISABLE,   /**< Resistor ladder disabled. */
  opaResInMuxOpaIn   = DAC_OPA0MUX_RESINMUX_OPA0INP,   /**< Input from OPAx.          */
  opaResInMuxNegPad  = DAC_OPA0MUX_RESINMUX_NEGPAD,    /**< Input from negative pad.  */
  opaResInMuxPosPad  = DAC_OPA0MUX_RESINMUX_POSPAD,    /**< Input from positive pad.  */
  opaResInMuxVss     = DAC_OPA0MUX_RESINMUX_VSS        /**< Input connected to Vss.   */
} OPAMP_ResInMux_TypeDef;

/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** OPAMP init structure. */
typedef struct
{
  OPAMP_NegSel_TypeDef   negSel;              /**< Select input source for negative terminal.    */
  OPAMP_PosSel_TypeDef   posSel;              /**< Select input source for positive terminal.    */
  OPAMP_OutMode_TypeDef  outMode;             /**< Output terminal connection.                   */
  OPAMP_ResSel_TypeDef   resSel;              /**< Select R2/R1 resistor ratio.                  */
  OPAMP_ResInMux_TypeDef resInMux;            /**< Select input source for resistor ladder.      */
  uint32_t               outPen;              /**< Select alternate output terminal connections. */
  uint32_t               bias;                /**< Set OPAMP bias current.                       */
  bool                   halfBias;            /**< Divide OPAMP bias current by 2.               */
  bool                   lpfPosPadDisable;    /**< Disable low pass filter on positive pad.      */
  bool                   lpfNegPadDisable;    /**< Disable low pass filter on negative pad.      */
  bool                   nextOut;             /**< Enable NEXTOUT signal source.                 */
  bool                   npEn;                /**< Enable positive pad.                          */
  bool                   ppEn;                /**< Enable negative pad.                          */
  bool                   shortInputs;         /**< Short OPAMP input terminals.                  */
  bool                   hcmDisable;          /**< Disable input rail-to-rail capability.        */
  bool                   defaultOffset;       /**< Use factory calibrated opamp offset value.    */
  uint32_t               offset;              /**< Opamp offset value when @ref defaultOffset is false.*/
} OPAMP_Init_TypeDef;

/** Configuration of OPA0/1 in unity gain voltage follower mode.       */
#define OPA_INIT_UNITY_GAIN                                                       \
  {                                                                               \
    opaNegSelUnityGain,             /* Unity gain.                             */ \
    opaPosSelPosPad,                /* Pos input from pad.                     */ \
    opaOutModeMain,                 /* Main output enabled.                    */ \
    opaResSelDefault,               /* Resistor ladder is not used.            */ \
    opaResInMuxDisable,             /* Resistor ladder disabled.               */ \
    0,                              /* No alternate outputs enabled.           */ \
    _DAC_BIASPROG_BIASPROG_DEFAULT, /* Default bias setting.             */       \
    _DAC_BIASPROG_HALFBIAS_DEFAULT, /* Default half-bias setting.        */       \
    false,                          /* No low pass filter on pos pad.          */ \
    false,                          /* No low pass filter on neg pad.          */ \
    false,                          /* No nextout output enabled.              */ \
    false,                          /* Neg pad disabled.                       */ \
    true,                           /* Pos pad enabled, used as signal input.  */ \
    false,                          /* No shorting of inputs.                  */ \
    false,                          /* Rail-to-rail input enabled.             */ \
    true,                           /* Use factory calibrated opamp offset.    */ \
    0                               /* Opamp offset value (not used).          */ \
  }

/** Configuration of OPA2 in unity gain voltage follower mode.         */
#define OPA_INIT_UNITY_GAIN_OPA2                                                  \
  {                                                                               \
    opaNegSelUnityGain,             /* Unity gain.                             */ \
    opaPosSelPosPad,                /* Pos input from pad.                     */ \
    opaOutModeMain,                 /* Main output enabled.                    */ \
    opaResSelDefault,               /* Resistor ladder is not used.            */ \
    opaResInMuxDisable,             /* Resistor ladder disabled.               */ \
    DAC_OPA0MUX_OUTPEN_OUT0,        /* Alternate output 0 enabled.             */ \
    _DAC_BIASPROG_BIASPROG_DEFAULT, /* Default bias setting.             */       \
    _DAC_BIASPROG_HALFBIAS_DEFAULT, /* Default half-bias setting.        */       \
    false,                          /* No low pass filter on pos pad.          */ \
    false,                          /* No low pass filter on neg pad.          */ \
    false,                          /* No nextout output enabled.              */ \
    false,                          /* Neg pad disabled.                       */ \
    true,                           /* Pos pad enabled, used as signal input.  */ \
    false,                          /* No shorting of inputs.                  */ \
    false,                          /* Rail-to-rail input enabled.             */ \
    true,                           /* Use factory calibrated opamp offset.    */ \
    0                               /* Opamp offset value (not used).          */ \
  }

/** Configuration of OPA0/1 in non-inverting amplifier mode.           */
#define OPA_INIT_NON_INVERTING                                                    \
  {                                                                               \
    opaNegSelResTap,                /* Neg input from resistor ladder tap.     */ \
    opaPosSelPosPad,                /* Pos input from pad.                     */ \
    opaOutModeMain,                 /* Main output enabled.                    */ \
    opaResSelR2eq0_33R1,            /* R2 = 1/3 R1                             */ \
    opaResInMuxNegPad,              /* Resistor ladder input from neg pad.     */ \
    0,                              /* No alternate outputs enabled.           */ \
    _DAC_BIASPROG_BIASPROG_DEFAULT, /* Default bias setting.             */       \
    _DAC_BIASPROG_HALFBIAS_DEFAULT, /* Default half-bias setting.        */       \
    false,                          /* No low pass filter on pos pad.          */ \
    false,                          /* No low pass filter on neg pad.          */ \
    false,                          /* No nextout output enabled.              */ \
    true,                           /* Neg pad enabled, used as signal ground. */ \
    true,                           /* Pos pad enabled, used as signal input.  */ \
    false,                          /* No shorting of inputs.                  */ \
    false,                          /* Rail-to-rail input enabled.             */ \
    true,                           /* Use factory calibrated opamp offset.    */ \
    0                               /* Opamp offset value (not used).          */ \
  }

/** Configuration of OPA2 in non-inverting amplifier mode.             */
#define OPA_INIT_NON_INVERTING_OPA2                                               \
  {                                                                               \
    opaNegSelResTap,                /* Neg input from resistor ladder tap.     */ \
    opaPosSelPosPad,                /* Pos input from pad.                     */ \
    opaOutModeMain,                 /* Main output enabled.                    */ \
    opaResSelR2eq0_33R1,            /* R2 = 1/3 R1                             */ \
    opaResInMuxNegPad,              /* Resistor ladder input from neg pad.     */ \
    DAC_OPA0MUX_OUTPEN_OUT0,        /* Alternate output 0 enabled.             */ \
    _DAC_BIASPROG_BIASPROG_DEFAULT, /* Default bias setting.             */       \
    _DAC_BIASPROG_HALFBIAS_DEFAULT, /* Default half-bias setting.        */       \
    false,                          /* No low pass filter on pos pad.          */ \
    false,                          /* No low pass filter on neg pad.          */ \
    false,                          /* No nextout output enabled.              */ \
    true,                           /* Neg pad enabled, used as signal ground. */ \
    true,                           /* Pos pad enabled, used as signal input.  */ \
    false,                          /* No shorting of inputs.                  */ \
    false,                          /* Rail-to-rail input enabled.             */ \
    true,                           /* Use factory calibrated opamp offset.    */ \
    0                               /* Opamp offset value (not used).          */ \
  }

/** Configuration of OPA0/1 in inverting amplifier mode.               */
#define OPA_INIT_INVERTING                                                        \
  {                                                                               \
    opaNegSelResTap,                /* Neg input from resistor ladder tap.     */ \
    opaPosSelPosPad,                /* Pos input from pad.                     */ \
    opaOutModeMain,                 /* Main output enabled.                    */ \
    opaResSelR2eqR1,                /* R2 = R1                                 */ \
    opaResInMuxNegPad,              /* Resistor ladder input from neg pad.     */ \
    0,                              /* No alternate outputs enabled.           */ \
    _DAC_BIASPROG_BIASPROG_DEFAULT, /* Default bias setting.             */       \
    _DAC_BIASPROG_HALFBIAS_DEFAULT, /* Default half-bias setting.        */       \
    false,                          /* No low pass filter on pos pad.          */ \
    false,                          /* No low pass filter on neg pad.          */ \
    false,                          /* No nextout output enabled.              */ \
    true,                           /* Neg pad enabled, used as signal input.  */ \
    true,                           /* Pos pad enabled, used as signal ground. */ \
    false,                          /* No shorting of inputs.                  */ \
    false,                          /* Rail-to-rail input enabled.             */ \
    true,                           /* Use factory calibrated opamp offset.    */ \
    0                               /* Opamp offset value (not used).          */ \
  }

/** Configuration of OPA2 in inverting amplifier mode.                 */
#define OPA_INIT_INVERTING_OPA2                                                   \
  {                                                                               \
    opaNegSelResTap,                /* Neg input from resistor ladder tap.     */ \
    opaPosSelPosPad,                /* Pos input from pad.                     */ \
    opaOutModeMain,                 /* Main output enabled.                    */ \
    opaResSelR2eqR1,                /* R2 = R1                                 */ \
    opaResInMuxNegPad,              /* Resistor ladder input from neg pad.     */ \
    DAC_OPA0MUX_OUTPEN_OUT0,        /* Alternate output 0 enabled.             */ \
    _DAC_BIASPROG_BIASPROG_DEFAULT, /* Default bias setting.             */       \
    _DAC_BIASPROG_HALFBIAS_DEFAULT, /* Default half-bias setting.        */       \
    false,                          /* No low pass filter on pos pad.          */ \
    false,                          /* No low pass filter on neg pad.          */ \
    false,                          /* No nextout output enabled.              */ \
    true,                           /* Neg pad enabled, used as signal input.  */ \
    true,                           /* Pos pad enabled, used as signal ground. */ \
    false,                          /* No shorting of inputs.                  */ \
    false,                          /* Rail-to-rail input enabled.             */ \
    true,                           /* Use factory calibrated opamp offset.    */ \
    0                               /* Opamp offset value (not used).          */ \
  }

/** Configuration of OPA0 in cascaded non-inverting amplifier mode.    */
#define OPA_INIT_CASCADED_NON_INVERTING_OPA0                                      \
  {                                                                               \
    opaNegSelResTap,                /* Neg input from resistor ladder tap.     */ \
    opaPosSelPosPad,                /* Pos input from pad.                     */ \
    opaOutModeAll,                  /* Both main and alternate outputs.        */ \
    opaResSelR2eq0_33R1,            /* R2 = 1/3 R1                             */ \
    opaResInMuxNegPad,              /* Resistor ladder input from neg pad.     */ \
    0,                              /* No alternate outputs enabled.           */ \
    _DAC_BIASPROG_BIASPROG_DEFAULT, /* Default bias setting.             */       \
    _DAC_BIASPROG_HALFBIAS_DEFAULT, /* Default half-bias setting.        */       \
    false,                          /* No low pass filter on pos pad.          */ \
    false,                          /* No low pass filter on neg pad.          */ \
    true,                           /* Pass output to next stage (OPA1).       */ \
    true,                           /* Neg pad enabled, used as signal ground. */ \
    true,                           /* Pos pad enabled, used as signal input.  */ \
    false,                          /* No shorting of inputs.                  */ \
    false,                          /* Rail-to-rail input enabled.             */ \
    true,                           /* Use factory calibrated opamp offset.    */ \
    0                               /* Opamp offset value (not used).          */ \
  }

/** Configuration of OPA1 in cascaded non-inverting amplifier mode.    */
#define OPA_INIT_CASCADED_NON_INVERTING_OPA1                                      \
  {                                                                               \
    opaNegSelResTap,                /* Neg input from resistor ladder tap.     */ \
    opaPosSelOpaIn,                 /* Pos input from OPA0 output.             */ \
    opaOutModeAll,                  /* Both main and alternate outputs.        */ \
    opaResSelR2eq0_33R1,            /* R2 = 1/3 R1                             */ \
    opaResInMuxNegPad,              /* Resistor ladder input from neg pad.     */ \
    0,                              /* No alternate outputs enabled.           */ \
    _DAC_BIASPROG_BIASPROG_DEFAULT, /* Default bias setting.             */       \
    _DAC_BIASPROG_HALFBIAS_DEFAULT, /* Default half-bias setting.        */       \
    false,                          /* No low pass filter on pos pad.          */ \
    false,                          /* No low pass filter on neg pad.          */ \
    true,                           /* Pass output to next stage (OPA2).       */ \
    true,                           /* Neg pad enabled, used as signal ground. */ \
    false,                          /* Pos pad disabled.                       */ \
    false,                          /* No shorting of inputs.                  */ \
    false,                          /* Rail-to-rail input enabled.             */ \
    true,                           /* Use factory calibrated opamp offset.    */ \
    0                               /* Opamp offset value (not used).          */ \
  }

/** Configuration of OPA2 in cascaded non-inverting amplifier mode.    */
#define OPA_INIT_CASCADED_NON_INVERTING_OPA2                                      \
  {                                                                               \
    opaNegSelResTap,                /* Neg input from resistor ladder tap.     */ \
    opaPosSelOpaIn,                 /* Pos input from OPA1 output.             */ \
    opaOutModeMain,                 /* Main output enabled.                    */ \
    opaResSelR2eq0_33R1,            /* R2 = 1/3 R1                             */ \
    opaResInMuxNegPad,              /* Resistor ladder input from neg pad.     */ \
    DAC_OPA0MUX_OUTPEN_OUT0,        /* Alternate output 0 enabled.             */ \
    _DAC_BIASPROG_BIASPROG_DEFAULT, /* Default bias setting.             */       \
    _DAC_BIASPROG_HALFBIAS_DEFAULT, /* Default half-bias setting.        */       \
    false,                          /* No low pass filter on pos pad.          */ \
    false,                          /* No low pass filter on neg pad.          */ \
    false,                          /* No nextout output enabled.              */ \
    true,                           /* Neg pad enabled, used as signal ground. */ \
    false,                          /* Pos pad disabled.                       */ \
    false,                          /* No shorting of inputs.                  */ \
    false,                          /* Rail-to-rail input enabled.             */ \
    true,                           /* Use factory calibrated opamp offset.    */ \
    0                               /* Opamp offset value (not used).          */ \
  }

/** Configuration of OPA0 in cascaded inverting amplifier mode.        */
#define OPA_INIT_CASCADED_INVERTING_OPA0                                          \
  {                                                                               \
    opaNegSelResTap,                /* Neg input from resistor ladder tap.     */ \
    opaPosSelPosPad,                /* Pos input from pad.                     */ \
    opaOutModeAll,                  /* Both main and alternate outputs.        */ \
    opaResSelR2eqR1,                /* R2 = R1                                 */ \
    opaResInMuxNegPad,              /* Resistor ladder input from neg pad.     */ \
    0,                              /* No alternate outputs enabled.           */ \
    _DAC_BIASPROG_BIASPROG_DEFAULT, /* Default bias setting.             */       \
    _DAC_BIASPROG_HALFBIAS_DEFAULT, /* Default half-bias setting.        */       \
    false,                          /* No low pass filter on pos pad.          */ \
    false,                          /* No low pass filter on neg pad.          */ \
    true,                           /* Pass output to next stage (OPA1).       */ \
    true,                           /* Neg pad enabled, used as signal input.  */ \
    true,                           /* Pos pad enabled, used as signal ground. */ \
    false,                          /* No shorting of inputs.                  */ \
    false,                          /* Rail-to-rail input enabled.             */ \
    true,                           /* Use factory calibrated opamp offset.    */ \
    0                               /* Opamp offset value (not used).          */ \
  }

/** Configuration of OPA1 in cascaded inverting amplifier mode.        */
#define OPA_INIT_CASCADED_INVERTING_OPA1                                          \
  {                                                                               \
    opaNegSelResTap,                /* Neg input from resistor ladder tap.     */ \
    opaPosSelPosPad,                /* Pos input from pad.                     */ \
    opaOutModeAll,                  /* Both main and alternate outputs.        */ \
    opaResSelR2eqR1,                /* R2 = R1                                 */ \
    opaResInMuxOpaIn,               /* Resistor ladder input from OPA0.        */ \
    0,                              /* No alternate outputs enabled.           */ \
    _DAC_BIASPROG_BIASPROG_DEFAULT, /* Default bias setting.             */       \
    _DAC_BIASPROG_HALFBIAS_DEFAULT, /* Default half-bias setting.        */       \
    false,                          /* No low pass filter on pos pad.          */ \
    false,                          /* No low pass filter on neg pad.          */ \
    true,                           /* Pass output to next stage (OPA2).       */ \
    false,                          /* Neg pad disabled.                       */ \
    true,                           /* Pos pad enabled, used as signal ground. */ \
    false,                          /* No shorting of inputs.                  */ \
    false,                          /* Rail-to-rail input enabled.             */ \
    true,                           /* Use factory calibrated opamp offset.    */ \
    0                               /* Opamp offset value (not used).          */ \
  }

/** Configuration of OPA2 in cascaded inverting amplifier mode.        */
#define OPA_INIT_CASCADED_INVERTING_OPA2                                          \
  {                                                                               \
    opaNegSelResTap,                /* Neg input from resistor ladder tap.     */ \
    opaPosSelPosPad,                /* Pos input from pad.                     */ \
    opaOutModeMain,                 /* Main output enabled.                    */ \
    opaResSelR2eqR1,                /* R2 = R1                                 */ \
    opaResInMuxOpaIn,               /* Resistor ladder input from OPA1.        */ \
    DAC_OPA0MUX_OUTPEN_OUT0,        /* Alternate output 0 enabled.             */ \
    _DAC_BIASPROG_BIASPROG_DEFAULT, /* Default bias setting.             */       \
    _DAC_BIASPROG_HALFBIAS_DEFAULT, /* Default half-bias setting.        */       \
    false,                          /* No low pass filter on pos pad.          */ \
    false,                          /* No low pass filter on neg pad.          */ \
    false,                          /* No nextout output enabled.              */ \
    false,                          /* Neg pad disabled.                       */ \
    true,                           /* Pos pad enabled, used as signal ground. */ \
    false,                          /* No shorting of inputs.                  */ \
    false,                          /* Rail-to-rail input enabled.             */ \
    true,                           /* Use factory calibrated opamp offset.    */ \
    0                               /* Opamp offset value (not used).          */ \
  }

/** Configuration of OPA0 in two-opamp differential driver mode.       */
#define OPA_INIT_DIFF_DRIVER_OPA0                                                 \
  {                                                                               \
    opaNegSelUnityGain,             /* Unity gain.                             */ \
    opaPosSelPosPad,                /* Pos input from pad.                     */ \
    opaOutModeAll,                  /* Both main and alternate outputs.        */ \
    opaResSelDefault,               /* Resistor ladder is not used.            */ \
    opaResInMuxDisable,             /* Resistor ladder disabled.               */ \
    0,                              /* No alternate outputs enabled.           */ \
    _DAC_BIASPROG_BIASPROG_DEFAULT, /* Default bias setting.             */       \
    _DAC_BIASPROG_HALFBIAS_DEFAULT, /* Default half-bias setting.        */       \
    false,                          /* No low pass filter on pos pad.          */ \
    false,                          /* No low pass filter on neg pad.          */ \
    true,                           /* Pass output to next stage (OPA1).       */ \
    false,                          /* Neg pad disabled.                       */ \
    true,                           /* Pos pad enabled, used as signal input.  */ \
    false,                          /* No shorting of inputs.                  */ \
    false,                          /* Rail-to-rail input enabled.             */ \
    true,                           /* Use factory calibrated opamp offset.    */ \
    0                               /* Opamp offset value (not used).          */ \
  }

/** Configuration of OPA1 in two-opamp differential driver mode.       */
#define OPA_INIT_DIFF_DRIVER_OPA1                                                 \
  {                                                                               \
    opaNegSelResTap,                /* Neg input from resistor ladder tap.     */ \
    opaPosSelPosPad,                /* Pos input from pad.                     */ \
    opaOutModeMain,                 /* Main output enabled.                    */ \
    opaResSelR2eqR1,                /* R2 = R1                                 */ \
    opaResInMuxOpaIn,               /* Resistor ladder input from OPA0.        */ \
    0,                              /* No alternate outputs enabled.           */ \
    _DAC_BIASPROG_BIASPROG_DEFAULT, /* Default bias setting.             */       \
    _DAC_BIASPROG_HALFBIAS_DEFAULT, /* Default half-bias setting.        */       \
    false,                          /* No low pass filter on pos pad.          */ \
    false,                          /* No low pass filter on neg pad.          */ \
    false,                          /* No nextout output enabled.              */ \
    false,                          /* Neg pad disabled.                       */ \
    true,                           /* Pos pad enabled, used as signal ground. */ \
    false,                          /* No shorting of inputs.                  */ \
    false,                          /* Rail-to-rail input enabled.             */ \
    true,                           /* Use factory calibrated opamp offset.    */ \
    0                               /* Opamp offset value (not used).          */ \
  }

/** Configuration of OPA0 in three-opamp differential receiver mode.   */
#define OPA_INIT_DIFF_RECEIVER_OPA0                                               \
  {                                                                               \
    opaNegSelUnityGain,             /* Unity gain.                             */ \
    opaPosSelPosPad,                /* Pos input from pad.                     */ \
    opaOutModeAll,                  /* Both main and alternate outputs.        */ \
    opaResSelR2eqR1,                /* R2 = R1                                 */ \
    opaResInMuxNegPad,              /* Resistor ladder input from neg pad.     */ \
    0,                              /* No alternate outputs enabled.           */ \
    _DAC_BIASPROG_BIASPROG_DEFAULT, /* Default bias setting.             */       \
    _DAC_BIASPROG_HALFBIAS_DEFAULT, /* Default half-bias setting.        */       \
    false,                          /* No low pass filter on pos pad.          */ \
    false,                          /* No low pass filter on neg pad.          */ \
    true,                           /* Pass output to next stage (OPA2).       */ \
    true,                           /* Neg pad enabled, used as signal ground. */ \
    true,                           /* Pos pad enabled, used as signal input.  */ \
    false,                          /* No shorting of inputs.                  */ \
    false,                          /* Rail-to-rail input enabled.             */ \
    true,                           /* Use factory calibrated opamp offset.    */ \
    0                               /* Opamp offset value (not used).          */ \
  }

/** Configuration of OPA1 in three-opamp differential receiver mode.   */
#define OPA_INIT_DIFF_RECEIVER_OPA1                                               \
  {                                                                               \
    opaNegSelUnityGain,             /* Unity gain.                             */ \
    opaPosSelPosPad,                /* Pos input from pad.                     */ \
    opaOutModeAll,                  /* Both main and alternate outputs.        */ \
    opaResSelDefault,               /* Resistor ladder is not used.            */ \
    opaResInMuxDisable,             /* Disable resistor ladder.                */ \
    0,                              /* No alternate outputs enabled.           */ \
    _DAC_BIASPROG_BIASPROG_DEFAULT, /* Default bias setting.             */       \
    _DAC_BIASPROG_HALFBIAS_DEFAULT, /* Default half-bias setting.        */       \
    false,                          /* No low pass filter on pos pad.          */ \
    false,                          /* No low pass filter on neg pad.          */ \
    true,                           /* Pass output to next stage (OPA2).       */ \
    false,                          /* Neg pad disabled.                       */ \
    true,                           /* Pos pad enabled, used as signal input.  */ \
    false,                          /* No shorting of inputs.                  */ \
    false,                          /* Rail-to-rail input enabled.             */ \
    true,                           /* Use factory calibrated opamp offset.    */ \
    0                               /* Opamp offset value (not used).          */ \
  }

/** Configuration of OPA2 in three-opamp differential receiver mode.   */
#define OPA_INIT_DIFF_RECEIVER_OPA2                                               \
  {                                                                               \
    opaNegSelResTap,                /* Input from resistor ladder tap.         */ \
    opaPosSelResTapOpa0,            /* Input from OPA0 resistor ladder tap.    */ \
    opaOutModeMain,                 /* Main output enabled.                    */ \
    opaResSelR2eqR1,                /* R2 = R1                                 */ \
    opaResInMuxOpaIn,               /* Resistor ladder input from OPA1.        */ \
    DAC_OPA0MUX_OUTPEN_OUT0,        /* Enable alternate output 0.              */ \
    _DAC_BIASPROG_BIASPROG_DEFAULT, /* Default bias setting.             */       \
    _DAC_BIASPROG_HALFBIAS_DEFAULT, /* Default half-bias setting.        */       \
    false,                          /* No low pass filter on pos pad.          */ \
    false,                          /* No low pass filter on neg pad.          */ \
    false,                          /* No nextout output enabled.              */ \
    false,                          /* Neg pad disabled.                       */ \
    false,                          /* Pos pad disabled.                       */ \
    false,                          /* No shorting of inputs.                  */ \
    false,                          /* Rail-to-rail input enabled.             */ \
    true,                           /* Use factory calibrated opamp offset.    */ \
    0                               /* Opamp offset value (not used).          */ \
  }

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

void      OPAMP_Disable(DAC_TypeDef *dac, OPAMP_TypeDef opa);
void      OPAMP_Enable(DAC_TypeDef *dac, OPAMP_TypeDef opa, const OPAMP_Init_TypeDef *init);

/** @} (end addtogroup OPAMP) */
/** @} (end addtogroup EM_Library) */

#ifdef __cplusplus
}
#endif

#endif /* defined( OPAMP_PRESENT ) && ( OPAMP_COUNT == 1 ) */
#endif /* __EM_DAC_H */
