/***************************************************************************//**
 * @file
 * @brief Energy management unit (EMU) peripheral API
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
#ifndef __EM_EMU_H
#define __EM_EMU_H

#include <stdbool.h>
#include "em_part.h"
#include "em_bitband.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup EMU
 * @{
 ******************************************************************************/

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

#if defined(_EFM32_GIANT_FAMILY)
/** EM4 duty oscillator */
typedef enum
{
  /** Select ULFRCO as duty oscillator in EM4 */
  emuEM4Osc_ULFRCO = EMU_EM4CONF_OSC_ULFRCO,
  /** Select LFXO as duty oscillator in EM4 */
  emuEM4Osc_LFXO = EMU_EM4CONF_OSC_LFXO,
  /** Select LFRCO as duty oscillator in EM4 */
  emuEM4Osc_LFRCO = EMU_EM4CONF_OSC_LFRCO
} EMU_EM4Osc_TypeDef;

/** Backup Power Voltage Probe types */
typedef enum
{
  /** Disable voltage probe */
  emuProbe_Disable = EMU_BUCTRL_PROBE_DISABLE,
  /** Connect probe to VDD_DREG */
  emuProbe_VDDDReg = EMU_BUCTRL_PROBE_VDDDREG,
  /** Connect probe to BU_IN */
  emuProbe_BUIN    = EMU_BUCTRL_PROBE_BUIN,
  /** Connect probe to BU_OUT */
  emuProbe_BUOUT   = EMU_BUCTRL_PROBE_BUOUT
} EMU_Probe_TypeDef;

/** Backup Power Domain resistor selection */
typedef enum
{
  /** Main power and backup power connected with RES0 series resistance */
  emuRes_Res0 = EMU_PWRCONF_PWRRES_RES0,
  /** Main power and backup power connected with RES1 series resistance */
  emuRes_Res1 = EMU_PWRCONF_PWRRES_RES1,
  /** Main power and backup power connected with RES2 series resistance */
  emuRes_Res2 = EMU_PWRCONF_PWRRES_RES2,
  /** Main power and backup power connected with RES3 series resistance */
  emuRes_Res3 = EMU_PWRCONF_PWRRES_RES3,
} EMU_Resistor_TypeDef;

/** Backup Power Domain power connection */
typedef enum
{
  /** No connection between main and backup power */
  emuPower_None = EMU_BUINACT_PWRCON_NONE,
  /** Main power and backup power connected through diode,
      allowing current from backup to main only */
  emuPower_BUMain = EMU_BUINACT_PWRCON_BUMAIN,
  /** Main power and backup power connected through diode,
      allowing current from main to backup only */
  emuPower_MainBU = EMU_BUINACT_PWRCON_MAINBU,
  /** Main power and backup power connected without diode */
  emuPower_NoDiode = EMU_BUINACT_PWRCON_NODIODE,
} EMU_Power_TypeDef;

/** BOD threshold setting selector, active or inactive mode */
typedef enum
{
  /** Configure BOD threshold for active mode */
  emuBODMode_Active,
  /** Configure BOD threshold for inactive mode */
  emuBODMode_Inactive,
} EMU_BODMode_TypeDef;
#endif

/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

#if defined(_EFM32_GIANT_FAMILY)
/** Energy Mode 4 initialization structure  */
typedef struct
{
  /** Lock configuration of regulator, BOD and oscillator */
  bool               lockConfig;
  /** EM4 duty oscillator */
  EMU_EM4Osc_TypeDef osc;
  /** Wake up on EM4 BURTC interrupt */
  bool               buRtcWakeup;
  /** Enable EM4 voltage regulator */
  bool               vreg;
} EMU_EM4Init_TypeDef;

/** Default initialization of EM4 configuration */
#define EMU_EM4INIT_DEFAULT    \
  {   false,             /* Dont't lock configuration after it's been set */ \
      emuEM4Osc_ULFRCO,  /* Use default ULFRCO oscillator  */ \
      true,              /* Wake up on EM4 BURTC interrupt */ \
      true,              /* Enable VREG */ \
  }

/** Backup Power Domain Initialization structure */
typedef struct
{
  /* Backup Power Domain power configuration */

  /** Voltage probe select, selects ADC voltage */
  EMU_Probe_TypeDef probe;
  /** Enable BOD calibration mode */
  bool              bodCal;
  /** Enable BU_STAT status pin for active BU mode */
  bool              statusPinEnable;

  /* Backup Power Domain connection configuration */
  /** Power domain resistor */
  EMU_Resistor_TypeDef resistor;
  /** BU_VOUT strong enable */
  bool                 voutStrong;
  /** BU_VOUT medium enable */
  bool                 voutMed;
  /** BU_VOUT weak enable */
  bool                 voutWeak;
  /** Power connection, when not in Backup Mode */
  EMU_Power_TypeDef  inactivePower;
  /** Power connection, when in Backup Mode */
  EMU_Power_TypeDef  activePower;
  /** Enable backup power domain, and release reset, enable BU_VIN pin  */
  bool               enable;
} EMU_BUPDInit_TypeDef;

/** Default */
#define EMU_BUPDINIT_DEFAULT                                                \
  { emuProbe_Disable, /* Do not enable voltage probe */                     \
    false,            /* Disable BOD calibration mode */                    \
    false,            /* Disable BU_STAT pin for backup mode indication */  \
                                                                            \
    emuRes_Res0,      /* RES0 series resistance between main and backup power */ \
    false,            /* Don't enable strong switch */                           \
    false,            /* Don't enable medium switch */                           \
    false,            /* Don't enable weak switch */                             \
                                                                                 \
    emuPower_None,    /* No connection between main and backup power (inactive mode) */  \
    emuPower_None,    /* No connection between main and backup power (active mode) */    \
    true              /* Enable BUPD enter on BOD, enable BU_VIN pin, release BU reset  */  \
  }
#endif

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Enter energy mode 1 (EM1).
 ******************************************************************************/
__STATIC_INLINE void EMU_EnterEM1(void)
{
  /* Just enter Cortex-M3 sleep mode */
  SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
  __WFI();
}


void EMU_EnterEM2(bool restore);
void EMU_EnterEM3(bool restore);
void EMU_EnterEM4(void);
void EMU_MemPwrDown(uint32_t blocks);
void EMU_UpdateOscConfig(void);
#if defined(_EFM32_GIANT_FAMILY)
void EMU_EM4Init(EMU_EM4Init_TypeDef *em4init);
void EMU_BUPDInit(EMU_BUPDInit_TypeDef *bupdInit);
void EMU_BUThresholdSet(EMU_BODMode_TypeDef mode, uint32_t value);
void EMU_BUThresRangeSet(EMU_BODMode_TypeDef mode, uint32_t value);

/***************************************************************************//**
 * @brief
 *   Enable or disable EM4 lock configuration
 * @param[in] enable
 *   If true, locks down EM4 configuration
 ******************************************************************************/
__STATIC_INLINE void EMU_EM4Lock(bool enable)
{
  BITBAND_Peripheral(&(EMU->EM4CONF), _EMU_EM4CONF_LOCKCONF_SHIFT, enable);
}

/***************************************************************************//**
 * @brief
 *   Halts until backup power functionality is ready
 ******************************************************************************/
__STATIC_INLINE void EMU_BUReady(void)
{
  while(!(EMU->STATUS & EMU_STATUS_BURDY));
}

/***************************************************************************//**
 * @brief
 *   Disable BU_VIN support
 * @param[in] enable
 *   If true, enables BU_VIN input pin support, if false disables it
 ******************************************************************************/
__STATIC_INLINE void EMU_BUPinEnable(bool enable)
{
  BITBAND_Peripheral(&(EMU->ROUTE), _EMU_ROUTE_BUVINPEN_SHIFT, enable);
}
#endif

/***************************************************************************//**
 * @brief
 *   Lock the EMU in order to protect all its registers against unintended
 *   modification.
 *
 * @note
 *   If locking the EMU registers, they must be unlocked prior to using any
 *   EMU API functions modifying EMU registers. An exception to this is the
 *   energy mode entering API (EMU_EnterEMn()), which can be used when the
 *   EMU registers are locked.
 ******************************************************************************/
__STATIC_INLINE void EMU_Lock(void)
{
  EMU->LOCK = EMU_LOCK_LOCKKEY_LOCK;
}


/***************************************************************************//**
 * @brief
 *   Unlock the EMU so that writing to locked registers again is possible.
 ******************************************************************************/
__STATIC_INLINE void EMU_Unlock(void)
{
  EMU->LOCK = EMU_LOCK_LOCKKEY_UNLOCK;
}

/***************************************************************************//**
 * @brief
 *   Block entering EM2 or higher number energy modes.
 ******************************************************************************/
__STATIC_INLINE void EMU_EM2Block(void)
{
  BITBAND_Peripheral(&(EMU->CTRL), _EMU_CTRL_EM2BLOCK_SHIFT, 1U);
}

/***************************************************************************//**
 * @brief
 *   Unblock entering EM2 or higher number energy modes.
 ******************************************************************************/
__STATIC_INLINE void EMU_EM2UnBlock(void)
{
  BITBAND_Peripheral(&(EMU->CTRL), _EMU_CTRL_EM2BLOCK_SHIFT, 0U);
}


/** @} (end addtogroup EMU) */
/** @} (end addtogroup EM_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EM_EMU_H */
