/***************************************************************************//**
 * @file
 * @brief Energy management unit (EMU) peripheral API for EFM32.
 * @author Energy Micro AS
 * @version 2.3.2
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2010 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * This source code is the property of Energy Micro AS. The source and compiled
 * code may only be used on Energy Micro "EFM32" microcontrollers.
 *
 * This copyright notice may not be removed from the source code nor changed.
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
#ifndef __EFM32_EMU_H
#define __EFM32_EMU_H

#include <stdbool.h>
#include "efm32.h"
#include "efm32_bitband.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup EFM32_Library
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

  /* Backup Power Domain inactive configuration */
  /** Power connection, when not in Backup Mode */
  EMU_Power_TypeDef  inactivePower;
  /** Threshold range for backup BOD sensing on VDD_DREG, when not in Backup Mode */
  uint32_t           inactiveThresRange;
  /** Threshold for backup BOD sesning on VDD_DREG, when not in Backup Mode */
  uint32_t           inactiveThreshold;

  /* Backup Power Domain active configuration */
  /** Power connection, when in Backup Mode */
  EMU_Power_TypeDef  activePower;
  /** Threshold range for backup BOD sensing when in Backup Mode */
  uint32_t           activeThresRange;
  /** Threshold for backup BOD sesning on VDD_DREG, when in Backup Mode */
  uint32_t           activeThreshold;

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
    0,                /* Default threshold range for backup BOD sense (inactive mode) */ \
    0,                /* Default threshold for backup BOD snese (inactive mode) */       \
                                                                                         \
    emuPower_None,    /* No connection between main and backup power (active mode) */  \
    0,                /* Default threshold range for backup BOD sense (active mode) */ \
    0,                /* Default threshold for backup BOD snese (active mode) */       \
                                                                                       \
    true              /* Enable BUPD enter on BOD, enable BU_VIN pin, release BU reset  */                   \
  }
#endif

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Enter energy mode 1 (EM1).
 ******************************************************************************/
static __INLINE void EMU_EnterEM1(void)
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
void EMU_BUPDInit(EMU_BUPDInit_TypeDef *budpdInit);

/***************************************************************************//**
 * @brief
 *   Disable BU_VIN support
 * @param[in] enable
 *   If true, enables BU_VIN input pin support, if false disables it
 ******************************************************************************/
static __INLINE void EMU_BUPinEnable(bool enable)
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
static __INLINE void EMU_Lock(void)
{
  EMU->LOCK = EMU_LOCK_LOCKKEY_LOCK;
}


/***************************************************************************//**
 * @brief
 *   Unlock the EMU so that writing to locked registers again is possible.
 ******************************************************************************/
static __INLINE void EMU_Unlock(void)
{
  EMU->LOCK = EMU_LOCK_LOCKKEY_UNLOCK;
}

/***************************************************************************//**
 * @brief
 *   Block entering EM2 or higher number energy modes.
 ******************************************************************************/
static __INLINE void EMU_EM2Block(void)
{
  BITBAND_Peripheral(&(EMU->CTRL), _EMU_CTRL_EM2BLOCK_SHIFT, 1U);
}

/***************************************************************************//**
 * @brief
 *   Unblock entering EM2 or higher number energy modes.
 ******************************************************************************/
static __INLINE void EMU_EM2UnBlock(void)
{
  BITBAND_Peripheral(&(EMU->CTRL), _EMU_CTRL_EM2BLOCK_SHIFT, 0U);
}


/** @} (end addtogroup EMU) */
/** @} (end addtogroup EFM32_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EFM32_EMU_H */
