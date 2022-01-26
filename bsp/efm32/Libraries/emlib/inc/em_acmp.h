/***************************************************************************//**
 * @file
 * @brief Analog Comparator (ACMP) peripheral API
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
#ifndef __EM_ACMP_H
#define __EM_ACMP_H

#include <stdint.h>
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
 * @addtogroup ACMP
 * @{
 ******************************************************************************/

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** Resistor values used for capacative sense. See the datasheet for your
 *  device for details on each resistor value. */
typedef enum
{
  /** resistor value 0 */
  acmpResistor0 = _ACMP_INPUTSEL_CSRESSEL_RES0,
  /** resistor value 1 */
  acmpResistor1 = _ACMP_INPUTSEL_CSRESSEL_RES1,
  /** resistor value 2 */
  acmpResistor2 = _ACMP_INPUTSEL_CSRESSEL_RES2,
  /** resistor value 3 */
  acmpResistor3 = _ACMP_INPUTSEL_CSRESSEL_RES3
} ACMP_CapsenseResistor_TypeDef;

/** Hysteresis level. See datasheet for your device for details on each
 *  level. */
typedef enum
{
  acmpHysteresisLevel0 = _ACMP_CTRL_HYSTSEL_HYST0, /**< Hysteresis level 0 */
  acmpHysteresisLevel1 = _ACMP_CTRL_HYSTSEL_HYST1, /**< Hysteresis level 1 */
  acmpHysteresisLevel2 = _ACMP_CTRL_HYSTSEL_HYST2, /**< Hysteresis level 2 */
  acmpHysteresisLevel3 = _ACMP_CTRL_HYSTSEL_HYST3, /**< Hysteresis level 3 */
  acmpHysteresisLevel4 = _ACMP_CTRL_HYSTSEL_HYST4, /**< Hysteresis level 4 */
  acmpHysteresisLevel5 = _ACMP_CTRL_HYSTSEL_HYST5, /**< Hysteresis level 5 */
  acmpHysteresisLevel6 = _ACMP_CTRL_HYSTSEL_HYST6, /**< Hysteresis level 6 */
  acmpHysteresisLevel7 = _ACMP_CTRL_HYSTSEL_HYST7  /**< Hysteresis level 7 */
} ACMP_HysteresisLevel_TypeDef;

/** ACMP warmup time. The delay is measured in HFPERCLK cycles and should
 *  be at least 10 us. */
typedef enum
{
  /** 4 HFPERCLK cycles warmup */
  acmpWarmTime4   = _ACMP_CTRL_WARMTIME_4CYCLES,
  /** 8 HFPERCLK cycles warmup */
  acmpWarmTime8   = _ACMP_CTRL_WARMTIME_8CYCLES,
  /** 16 HFPERCLK cycles warmup */
  acmpWarmTime16  = _ACMP_CTRL_WARMTIME_16CYCLES,
  /** 32 HFPERCLK cycles warmup */
  acmpWarmTime32  = _ACMP_CTRL_WARMTIME_32CYCLES,
  /** 64 HFPERCLK cycles warmup */
  acmpWarmTime64  = _ACMP_CTRL_WARMTIME_64CYCLES,
  /** 128 HFPERCLK cycles warmup */
  acmpWarmTime128 = _ACMP_CTRL_WARMTIME_128CYCLES,
  /** 256 HFPERCLK cycles warmup */
  acmpWarmTime256 = _ACMP_CTRL_WARMTIME_256CYCLES,
  /** 512 HFPERCLK cycles warmup */
  acmpWarmTime512 = _ACMP_CTRL_WARMTIME_512CYCLES
} ACMP_WarmTime_TypeDef;

/** ACMP inputs. Note that scaled VDD and bandgap references can only be used
 *  as negative inputs. */
typedef enum
{
  /** Channel 0 */
  acmpChannel0    = _ACMP_INPUTSEL_NEGSEL_CH0,
  /** Channel 1 */
  acmpChannel1    = _ACMP_INPUTSEL_NEGSEL_CH1,
  /** Channel 2 */
  acmpChannel2    = _ACMP_INPUTSEL_NEGSEL_CH2,
  /** Channel 3 */
  acmpChannel3    = _ACMP_INPUTSEL_NEGSEL_CH3,
  /** Channel 4 */
  acmpChannel4    = _ACMP_INPUTSEL_NEGSEL_CH4,
  /** Channel 5 */
  acmpChannel5    = _ACMP_INPUTSEL_NEGSEL_CH5,
  /** Channel 6 */
  acmpChannel6    = _ACMP_INPUTSEL_NEGSEL_CH6,
  /** Channel 7 */
  acmpChannel7    = _ACMP_INPUTSEL_NEGSEL_CH7,
  /** 1.25V internal reference */
  acmpChannel1V25 = _ACMP_INPUTSEL_NEGSEL_1V25,
  /** 2.5V internal reference */
  acmpChannel2V5  = _ACMP_INPUTSEL_NEGSEL_2V5,
  /** Scaled VDD reference */
  acmpChannelVDD  = _ACMP_INPUTSEL_NEGSEL_VDD,
#if defined(_EFM32_GIANT_FAMILY) || defined(_EFM32_TINY_FAMILY)
  /** DAC0 channel 0 */
  acmpChannelDAC0Ch0 = _ACMP_INPUTSEL_NEGSEL_DAC0CH0,
  /** DAC0 channel 1 */
  acmpChannelDAC0Ch1 = _ACMP_INPUTSEL_NEGSEL_DAC0CH1,
#endif
} ACMP_Channel_TypeDef;

/*******************************************************************************
 ******************************   STRUCTS   ************************************
 ******************************************************************************/

/** Capsense initialization structure. */
typedef struct
{
  /** Full bias current. See the ACMP chapter about bias and response time in
   *  the reference manual for details. */
  bool                          fullBias;

  /** Half bias current. See the ACMP chapter about bias and response time in
   *  the reference manual for details. */
  bool                          halfBias;

  /** Bias current. See the ACMP chapter about bias and response time in the
   *  reference manual for details. Valid values are in the range 0-7. */
  uint32_t                      biasProg;

  /** Warmup time. This is measured in HFPERCLK cycles and should be
   *  about 10us in wall clock time. */
  ACMP_WarmTime_TypeDef         warmTime;

  /** Hysteresis level */
  ACMP_HysteresisLevel_TypeDef  hysteresisLevel;

  /** Resistor used in the capacative sensing circuit. For values see
   *  your device datasheet. */
  ACMP_CapsenseResistor_TypeDef resistor;

  /** Low power reference enabled. This setting, if enabled, reduces the
   *  power used by the VDD and bandgap references. */
  bool                          lowPowerReferenceEnabled;

  /** Vdd reference value. VDD_SCALED = VDD × VDDLEVEL × 50mV/3.8V.
   *  Valid values are in the range 0-63. */
  uint32_t                      vddLevel;

  /** If true, ACMP is being enabled after configuration. */
  bool                          enable;
} ACMP_CapsenseInit_TypeDef;

/** Default config for capacitive sense mode initialization. */
#define ACMP_CAPSENSE_INIT_DEFAULT                        \
  { false,              /* fullBias */                    \
    false,              /* halfBias */                    \
    0x7,                /* biasProg */                    \
    acmpWarmTime512,    /* 512 cycle warmup to be safe */ \
    acmpHysteresisLevel5,                                 \
    acmpResistor3,                                        \
    false,              /* low power reference */         \
    0x3D,               /* VDD level */                   \
    true                /* Enable after init. */          \
  }

/** ACMP initialization structure. */
typedef struct
{
  /** Full bias current. See the ACMP chapter about bias and response time in
   *  the reference manual for details. */
  bool                         fullBias;

  /** Half bias current. See the ACMP chapter about bias and response time in
   *  the reference manual for details. */
  bool                         halfBias;

  /** Bias current. See the ACMP chapter about bias and response time in the
   *  reference manual for details. Valid values are in the range 0-7. */
  uint32_t                     biasProg;

  /** Enable setting the interrupt flag on falling edge */
  bool                         interruptOnFallingEdge;

  /** Enable setting the interrupt flag on rising edge */
  bool                         interruptOnRisingEdge;

  /** Warmup time. This is measured in HFPERCLK cycles and should be
   *  about 10us in wall clock time. */
  ACMP_WarmTime_TypeDef        warmTime;

  /** Hysteresis level */
  ACMP_HysteresisLevel_TypeDef hysteresisLevel;

  /** Inactive value emitted by the ACMP during warmup */
  bool                         inactiveValue;

  /** Low power reference enabled. This setting, if enabled, reduces the
   *  power used by the VDD and bandgap references. */
  bool                         lowPowerReferenceEnabled;

  /** Vdd reference value. VDD_SCALED = VDD × VDDLEVEL × 50mV/3.8V.
   *  Valid values are in the range 0-63. */
  uint32_t                     vddLevel;

  /** If true, ACMP is being enabled after configuration. */
  bool                         enable;
} ACMP_Init_TypeDef;

/** Default config for ACMP regular initialization. */
#define ACMP_INIT_DEFAULT                                                     \
  { false,              /* fullBias */                                        \
    false,              /* halfBias */                                        \
    0x7,                /* biasProg */                                        \
    false,              /* No interrupt on falling edge. */                   \
    false,              /* No interrupt on rising edge. */                    \
    acmpWarmTime512,    /* 512 cycle warmup to be safe */                     \
    acmpHysteresisLevel5,                                                     \
    false,              /* Disabled emitting inactive value during warmup. */ \
    false,              /* low power reference */                             \
    0x3D,               /* VDD level */                                       \
    true                /* Enable after init. */                              \
  }


/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

void ACMP_CapsenseInit(ACMP_TypeDef *acmp, const ACMP_CapsenseInit_TypeDef *init);
void ACMP_CapsenseChannelSet(ACMP_TypeDef *acmp, ACMP_Channel_TypeDef channel);
void ACMP_ChannelSet(ACMP_TypeDef *acmp, ACMP_Channel_TypeDef negSel, ACMP_Channel_TypeDef posSel);
void ACMP_Disable(ACMP_TypeDef *acmp);
void ACMP_Enable(ACMP_TypeDef *acmp);
void ACMP_GPIOSetup(ACMP_TypeDef *acmp, uint32_t location, bool enable, bool invert);
void ACMP_Init(ACMP_TypeDef *acmp, const ACMP_Init_TypeDef *init);
void ACMP_Reset(ACMP_TypeDef *acmp);

/***************************************************************************//**
 * @brief
 *   Clear one or more pending ACMP interrupts.
 *
 * @param[in] acmp
 *   Pointer to ACMP peripheral register block.
 *
 * @param[in] flags
 *   Pending ACMP interrupt source to clear. Use a bitwise logic OR combination
 *   of valid interrupt flags for the ACMP module (ACMP_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void ACMP_IntClear(ACMP_TypeDef *acmp, uint32_t flags)
{
  acmp->IFC = flags;
}


/***************************************************************************//**
 * @brief
 *   Disable one or more ACMP interrupts.
 *
 * @param[in] acmp
 *   Pointer to ACMP peripheral register block.
 *
 * @param[in] flags
 *   ACMP interrupt sources to disable. Use a bitwise logic OR combination of
 *   valid interrupt flags for the ACMP module (ACMP_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void ACMP_IntDisable(ACMP_TypeDef *acmp, uint32_t flags)
{
  acmp->IEN &= ~(flags);
}


/***************************************************************************//**
 * @brief
 *   Enable one or more ACMP interrupts.
 *
 * @note
 *   Depending on the use, a pending interrupt may already be set prior to
 *   enabling the interrupt. Consider using ACMP_IntClear() prior to enabling
 *   if such a pending interrupt should be ignored.
 *
 * @param[in] acmp
 *   Pointer to ACMP peripheral register block.
 *
 * @param[in] flags
 *   ACMP interrupt sources to enable. Use a bitwise logic OR combination of
 *   valid interrupt flags for the ACMP module (ACMP_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void ACMP_IntEnable(ACMP_TypeDef *acmp, uint32_t flags)
{
  acmp->IEN |= flags;
}


/***************************************************************************//**
 * @brief
 *   Get pending ACMP interrupt flags.
 *
 * @note
 *   The event bits are not cleared by the use of this function.
 *
 * @param[in] acmp
 *   Pointer to ACMP peripheral register block.
 *
 * @return
 *   ACMP interrupt sources pending. A bitwise logic OR combination of valid
 *   interrupt flags for the ACMP module (ACMP_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t ACMP_IntGet(ACMP_TypeDef *acmp)
{
  return(acmp->IF);
}


/***************************************************************************//**
 * @brief
 *   Get enabled and pending ACMP interrupt flags.
 *   Useful for handling more interrupt sources in the same interrupt handler.
 *
 * @param[in] usart
 *   Pointer to ACMP peripheral register block.
 *
 * @note
 *   Interrupt flags are not cleared by the use of this function.
 *
 * @return
 *   Pending and enabled ACMP interrupt sources.
 *   The return value is the bitwise AND combination of
 *   - the OR combination of enabled interrupt sources in ACMPx_IEN_nnn
 *     register (ACMPx_IEN_nnn) and
 *   - the OR combination of valid interrupt flags of the ACMP module
 *     (ACMPx_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t ACMP_IntGetEnabled(ACMP_TypeDef *acmp)
{
  uint32_t tmp;

  /* Store ACMPx->IEN in temporary variable in order to define explicit order
   * of volatile accesses. */
  tmp = acmp->IEN;

  /* Bitwise AND of pending and enabled interrupts */
  return acmp->IF & tmp;
}


/***************************************************************************//**
 * @brief
 *   Set one or more pending ACMP interrupts from SW.
 *
 * @param[in] acmp
 *   Pointer to ACMP peripheral register block.
 *
 * @param[in] flags
 *   ACMP interrupt sources to set to pending. Use a bitwise logic OR
 *   combination of valid interrupt flags for the ACMP module (ACMP_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void ACMP_IntSet(ACMP_TypeDef *acmp, uint32_t flags)
{
  acmp->IFS = flags;
}

/** @} (end addtogroup ACMP) */
/** @} (end addtogroup EM_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EM_ACMP_H */
