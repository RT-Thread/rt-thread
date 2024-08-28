/*
 * Copyright 2022-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_VBAT_H_
#define FSL_VBAT_H_

#include "fsl_common.h"

/*!
 * @addtogroup mcx_vbat
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief VBAT driver version 2.3.1. */
#define FSL_VBAT_DRIVER_VERSION (MAKE_VERSION(2, 3, 1))
/*@}*/

#if !defined(VBAT_LDORAMC_RET_MASK)
#define VBAT_LDORAMC_RET_MASK   (0xF00U)
#define VBAT_LDORAMC_RET_SHIFT  (8U) 
#define VBAT_LDORAMC_RET(x)     (((uint32_t)(((uint32_t)(x)) << VBAT_LDORAMC_RET_SHIFT)) & VBAT_LDORAMC_RET_MASK)
#endif 

/*!
 * @brief The enumeration of VBAT module status.
 */
enum
{
    kStatus_VBAT_Fro16kNotEnabled = MAKE_STATUS(kStatusGroup_VBAT, 0),      /*!< Internal 16kHz free running
                                                                                 oscillator not enabled. */
    kStatus_VBAT_BandgapNotEnabled     = MAKE_STATUS(kStatusGroup_VBAT, 1), /*!< Bandgap not enabled. */
    kStatus_VBAT_WrongCapacitanceValue = MAKE_STATUS(kStatusGroup_VBAT, 2), /*!< Wrong capacitance for
                                                                                selected oscillator mode. */
    kStatus_VBAT_ClockMonitorLocked = MAKE_STATUS(kStatusGroup_VBAT, 3),    /*!< Clock monitor locked. */
    kStatus_VBAT_OSC32KNotReady     = MAKE_STATUS(kStatusGroup_VBAT, 4),    /*!< OSC32K not ready. */
    kStatus_VBAT_LDONotReady        = MAKE_STATUS(kStatusGroup_VBAT, 5),    /*!< LDO not ready. */
    kStatus_VBAT_TamperLocked       = MAKE_STATUS(kStatusGroup_VBAT, 6),    /*!< Tamper locked. */
};

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_STATUS_REG) && FSL_FEATURE_MCX_VBAT_HAS_STATUS_REG)
/*!
 * @brief The enumeration of VBAT status flags.
 *
 * @anchor vbat_status_flag_t
 */
enum _vbat_status_flag
{
    kVBAT_StatusFlagPORDetect     = VBAT_STATUSA_POR_DET_MASK,     /*!< VBAT domain has been reset */
    kVBAT_StatusFlagWakeupPin     = VBAT_STATUSA_WAKEUP_FLAG_MASK, /*!< A falling edge is detected on the wakeup pin. */
    kVBAT_StatusFlagBandgapTimer0 = VBAT_STATUSA_TIMER0_FLAG_MASK, /*!< Bandgap Timer0 period reached. */
    kVBAT_StatusFlagBandgapTimer1 = VBAT_STATUSA_TIMER1_FLAG_MASK, /*!< Bandgap Timer1 period reached. */
    kVBAT_StatusFlagLdoReady      = VBAT_STATUSA_LDO_RDY_MASK,     /*!< LDO is enabled and ready. */
    kVBAT_StatusFlagOsc32kReady   = VBAT_STATUSA_OSC_RDY_MASK,     /*!< OSC32k is enabled and clock is ready. */
#if defined(VBAT_STATUSA_CLOCK_DET_MASK)
    kVBAT_StatusFlagClockDetect = VBAT_STATUSA_CLOCK_DET_MASK,   /*!< The clock monitor has detected an error. */
#endif                                                           /* VBAT_STATUSA_CLOCK_DET_MASK */
    kVBAT_StatusFlagConfigDetect = VBAT_STATUSA_CONFIG_DET_MASK, /*!< Configuration error detected. */
#if defined(VBAT_STATUSA_VOLT_DET_MASK)
    kVBAT_StatusFlagVoltageDetect = VBAT_STATUSA_VOLT_DET_MASK, /*!< Voltage monitor has detected
                                                                    an error with VBAT supply. */
#endif                                                          /* VBAT_STATUSA_VOLT_DET_MASK */
#if defined(VBAT_STATUSA_TEMP_DET_MASK)
    kVBAT_StatusFlagTemperatureDetect = VBAT_STATUSA_TEMP_DET_MASK, /*!< Temperature monitor has detected an error. */
#endif                                                              /* VBAT_STATUSA_TEMP_DET_MASK */
#if defined(VBAT_STATUSA_SEC0_DET_MASK)
    kVBAT_StatusFlagSec0Detect = VBAT_STATUSA_SEC0_DET_MASK,       /*!< Security input 0 has detected an error. */
#endif                                                             /* VBAT_STATUSA_SEC0_DET_MASK */
    kVBAT_StatusFlagInterrupt0Detect = VBAT_STATUSA_IRQ0_DET_MASK, /*!< Interrupt 0 asserted. */
    kVBAT_StatusFlagInterrupt1Detect = VBAT_STATUSA_IRQ1_DET_MASK, /*!< Interrupt 1 asserted. */
    kVBAT_StatusFlagInterrupt2Detect = VBAT_STATUSA_IRQ2_DET_MASK, /*!< Interrupt 2 asserted. */
    kVBAT_StatusFlagInterrupt3Detect = VBAT_STATUSA_IRQ3_DET_MASK, /*!< Interrupt 2 asserted. */
};

/*!
 * @brief The enumeration of VBAT interrupt enable.
 *
 * @anchor vbat_interrupt_enable_t
 */
enum _vbat_interrupt_enable
{
    kVBAT_InterruptEnablePORDetect = VBAT_IRQENA_POR_DET_MASK,         /*!< Enable POR detect interrupt. */
    kVBAT_InterruptEnableWakeupPin = VBAT_IRQENA_WAKEUP_FLAG_MASK,     /*!< Enable the interrupt when a falling edge is
                                                                           detected on the wakeup pin. */
    kVBAT_InterruptEnableBandgapTimer0 = VBAT_IRQENA_TIMER0_FLAG_MASK, /*!< Enable the interrupt if Bandgap
                                                                           Timer0 period reached. */
    kVBAT_InterruptEnableBandgapTimer1 = VBAT_IRQENA_TIMER1_FLAG_MASK, /*!< Enable the interrupt if Bandgap
                                                                           Timer1 period reached. */
    kVBAT_InterruptEnableLdoReady    = VBAT_IRQENA_LDO_RDY_MASK,       /*!< Enable LDO ready interrupt. */
    kVBAT_InterruptEnableOsc32kReady = VBAT_IRQENA_OSC_RDY_MASK,       /*!< Enable OSC32K ready interrupt. */
#if defined(VBAT_IRQENA_CLOCK_DET_MASK)
    kVBAT_InterruptEnableClockDetect = VBAT_IRQENA_CLOCK_DET_MASK, /*!< Enable clock monitor detect interrupt. */
#endif                                                             /* VBAT_IRQENA_CLOCK_DET_MASK */
    kVBAT_InterruptEnableConfigDetect =
        VBAT_IRQENA_CONFIG_DET_MASK, /*!< Enable configuration error detected interrupt. */
#if defined(VBAT_IRQENA_VOLT_DET_MASK)
    kVBAT_InterruptEnableVoltageDetect = VBAT_IRQENA_VOLT_DET_MASK, /*!< Enable voltage monitor detect interrupt. */
#endif                                                              /* VBAT_IRQENA_VOLT_DET_MASK */
#if defined(VBAT_IRQENA_TEMP_DET_MASK)
    kVBAT_InterruptEnableTemperatureDetect = VBAT_IRQENA_TEMP_DET_MASK, /*!< Enable temperature monitor detect
                                                                            interrupt. */
#endif                                                                  /* VBAT_IRQENA_TEMP_DET_MASK */
#if defined(VBAT_IRQENA_SEC0_DET_MASK)
    kVBAT_InterruptEnableSec0Detect = VBAT_IRQENA_SEC0_DET_MASK, /*!< Enable security input 0 detect interrupt. */
#endif                                                           /* VBAT_IRQENA_SEC0_DET_MASK */
    kVBAT_InterruptEnableInterrupt0 = VBAT_IRQENA_IRQ0_DET_MASK, /*!< Enable the interrupt0. */
    kVBAT_InterruptEnableInterrupt1 = VBAT_IRQENA_IRQ1_DET_MASK, /*!< Enable the interrupt1. */
    kVBAT_InterruptEnableInterrupt2 = VBAT_IRQENA_IRQ2_DET_MASK, /*!< Enable the interrupt2. */
    kVBAT_InterruptEnableInterrupt3 = VBAT_IRQENA_IRQ3_DET_MASK, /*!< Enable the interrupt3. */

    kVBAT_AllInterruptsEnable =
        (VBAT_IRQENA_POR_DET_MASK | VBAT_IRQENA_WAKEUP_FLAG_MASK | VBAT_IRQENA_TIMER0_FLAG_MASK |
         VBAT_IRQENA_TIMER1_FLAG_MASK | VBAT_IRQENA_LDO_RDY_MASK | VBAT_IRQENA_OSC_RDY_MASK |
         VBAT_IRQENA_CONFIG_DET_MASK | VBAT_IRQENA_IRQ0_DET_MASK | VBAT_IRQENA_IRQ1_DET_MASK |
         VBAT_IRQENA_IRQ2_DET_MASK | VBAT_IRQENA_IRQ3_DET_MASK), /*!< Enable all interrupts. */
};

/*!
 * @brief The enumeration of VBAT wakeup enable.
 *
 * @anchor vbat_wakeup_enable_t
 */
enum _vbat_wakeup_enable
{
    kVBAT_WakeupEnablePORDetect = VBAT_WAKENA_POR_DET_MASK,         /*!< Enable POR detect wakeup. */
    kVBAT_WakeupEnableWakeupPin = VBAT_WAKENA_WAKEUP_FLAG_MASK,     /*!< Enable wakeup feature when a falling edge is
                                                                        detected on the wakeup pin. */
    kVBAT_WakeupEnableBandgapTimer0 = VBAT_WAKENA_TIMER0_FLAG_MASK, /*!< Enable wakeup feature when bandgap
                                                                        timer0 period reached. */
    kVBAT_WakeupEnableBandgapTimer1 = VBAT_WAKENA_TIMER1_FLAG_MASK, /*!< Enable wakeup feature when bandgap
                                                                        timer1 period reached. */
    kVBAT_WakeupEnableLdoReady    = VBAT_WAKENA_LDO_RDY_MASK,       /*!< Enable wakeup when LDO ready. */
    kVBAT_WakeupEnableOsc32kReady = VBAT_WAKENA_OSC_RDY_MASK,       /*!< Enable wakeup when OSC32k ready. */
#if defined(VBAT_WAKENA_CLOCK_DET_MASK)
    kVBAT_WakeupEnableClockDetect =
        VBAT_WAKENA_CLOCK_DET_MASK, /*!< Enable wakeup when clock monitor detect an error. */
#endif                              /* VBAT_WAKENA_CLOCK_DET_MASK */
    kVBAT_WakeupEnableConfigDetect = VBAT_WAKENA_CONFIG_DET_MASK, /*!< Enable wakeup when
                                                                      configuration error detected. */
#if defined(VBAT_WAKENA_VOLT_DET_MASK)
    kVBAT_WakeupEnableVoltageDetect = VBAT_WAKENA_VOLT_DET_MASK, /*!< Enable wakeup when voltage monitor detect an
                                                                     error. */
#endif                                                           /* VBAT_WAKENA_VOLT_DET_MASK */
#if defined(VBAT_WAKENA_TEMP_DET_MASK)
    kVBAT_WakeupEnableTemperatureDetect = VBAT_WAKENA_TEMP_DET_MASK, /*!< Enable wakeup when temperature monitor
                                                                         detect an error. */
#endif                                                               /* VBAT_WAKENA_TEMP_DET_MASK */
#if defined(VBAT_WAKENA_SEC0_DET_MASK)
    kVBAT_WakeupEnableSec0Detect = VBAT_WAKENA_SEC0_DET_MASK, /*!< Enable wakeup when security input 0 detect an
                                                                  error. */
#endif                                                        /* VBAT_WAKENA_SEC0_DET_MASK */
    kVBAT_WakeupEnableInterrupt0 = VBAT_WAKENA_IRQ0_DET_MASK, /*!< Enable wakeup when interrupt0 asserted. */
    kVBAT_WakeupEnableInterrupt1 = VBAT_WAKENA_IRQ1_DET_MASK, /*!< Enable wakeup when interrupt1 asserted. */
    kVBAT_WakeupEnableInterrupt2 = VBAT_WAKENA_IRQ2_DET_MASK, /*!< Enable wakeup when interrupt2 asserted. */
    kVBAT_WakeupEnableInterrupt3 = VBAT_WAKENA_IRQ3_DET_MASK, /*!< Enable wakeup when interrupt3 asserted. */

    kVBAT_AllWakeupsEnable = (VBAT_WAKENA_POR_DET_MASK | VBAT_WAKENA_WAKEUP_FLAG_MASK | VBAT_WAKENA_TIMER0_FLAG_MASK |
                              VBAT_WAKENA_TIMER1_FLAG_MASK | VBAT_WAKENA_LDO_RDY_MASK | VBAT_WAKENA_OSC_RDY_MASK |
                              VBAT_WAKENA_CONFIG_DET_MASK | VBAT_WAKENA_IRQ0_DET_MASK | VBAT_WAKENA_IRQ1_DET_MASK |
                              VBAT_WAKENA_IRQ2_DET_MASK | VBAT_WAKENA_IRQ3_DET_MASK

#if defined(VBAT_WAKENA_CLOCK_DET_MASK)
                              | VBAT_WAKENA_CLOCK_DET_MASK

#endif /* VBAT_WAKENA_CLOCK_DET_MASK */
#if defined(VBAT_WAKENA_VOLT_DET_MASK)
                              | VBAT_WAKENA_VOLT_DET_MASK

#endif /* VBAT_WAKENA_VOLT_DET_MASK */
#if defined(VBAT_WAKENA_TEMP_DET_MASK)
                              | VBAT_WAKENA_TEMP_DET_MASK

#endif /* VBAT_WAKENA_TEMP_DET_MASK */
#if defined(VBAT_WAKENA_SEC0_DET_MASK)
                              | VBAT_WAKENA_SEC0_DET_MASK

#endif                           /* VBAT_WAKENA_SEC0_DET_MASK */
                              ), /*!< Enable all wakeup. */
};
#endif /* FSL_FEATURE_MCX_VBAT_HAS_STATUS_REG */

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_TAMPER_REG) && FSL_FEATURE_MCX_VBAT_HAS_TAMPER_REG)
/*!
 * @brief The enumeration of VBAT tamper enable.
 */
enum _vbat_tamper_enable
{
    kVBAT_TamperEnablePOR         = VBAT_TAMPERA_POR_DET_MASK, /*!< Enable tamper if POR asserted in STATUS register. */
    kVBAT_TamperEnableClockDetect = VBAT_TAMPERA_CLOCK_DET_MASK, /*!< Enable tamper if clock monitor detect an error. */
    kVBAT_TamperEnableConfigDetect =
        VBAT_TAMPERA_CONFIG_DET_MASK,                             /*!< Enable tamper if configuration error detected. */
    kVBAT_TamperEnableVoltageDetect = VBAT_TAMPERA_VOLT_DET_MASK, /*!< Enable tamper if voltage monitor detect an
                                                                      error. */
    kVBAT_TamperEnableTemperatureDetect = VBAT_TAMPERA_TEMP_DET_MASK, /*!< Enable tamper if temperature monitor
                                                                          detect an error. */
    kVBAT_TamperEnableSec0Detect = VBAT_TAMPERA_SEC0_DET_MASK,        /*!< Enable tamper if security input 0 detect an
                                                                          error. */
};
#endif /* FSL_FEATURE_MCX_VBAT_HAS_TAMPER_REG */

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_BANDGAP_TIMER) && FSL_FEATURE_MCX_VBAT_HAS_BANDGAP_TIMER)
/*!
 * @brief The enumeration of bandgap timer id, VBAT support two bandgap timers.
 *
 * @anchor vbat_bandgap_timer_id_t
 */
enum _vbat_bandgap_timer_id
{
    kVBAT_BandgapTimer0 = 1U << 0U, /*!< Bandgap Timer0. */
    kVBAT_BandgapTimer1 = 1U << 1U, /*!< Bandgap Timer1. */
};
#endif /* FSL_FEATURE_MCX_VBAT_HAS_BANDGAP_TIMER */

/*!
 * @brief The enumeration of connections for OSC32K/FRO32K output clock to other modules.
 *
 * @anchor vbat_clock_enable_t
 */
enum _vbat_clock_enable
{
    kVBAT_EnableClockToDomain0 = 1U << 0U, /*!< Enable clock to power domain0. */
    kVBAT_EnableClockToDomain1 = 1U << 1U, /*!< Enable clock to power domain1. */
    kVBAT_EnableClockToDomain2 = 1U << 2U, /*!< Enable clock to power domain2. */
    kVBAT_EnableClockToDomain3 = 1U << 3U, /*!< Enable clock to power domain3. */
};
#define kVBAT_EnableClockToVddBat   kVBAT_EnableClockToDomain0
#define kVBAT_EnableClockToVddSys   kVBAT_EnableClockToDomain1
#define kVBAT_EnableClockToVddWake  kVBAT_EnableClockToDomain2
#define kVBAT_EnableClockToVddMain  kVBAT_EnableClockToDomain3

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_LDOCTL_REG) && FSL_FEATURE_MCX_VBAT_HAS_LDOCTL_REG)
/*!
 * @brief The enumeration of SRAM arrays that controlled by VBAT.
 * @anchor vbat_ram_array_t
 */
enum _vbat_ram_array
{
    kVBAT_SramArray0 = 1U << 0U, /*!< Specify SRAM array0 that controlled by VBAT. */
    kVBAT_SramArray1 = 1U << 1U, /*!< Specify SRAM array1 that controlled by VBAT. */
    kVBAT_SramArray2 = 1U << 2U, /*!< Specify SRAM array2 that controlled by VBAT. */
    kVBAT_SramArray3 = 1U << 3U, /*!< Specify SRAM array3 that controlled by VBAT. */
};
#endif /* FSL_FEATURE_MCX_VBAT_HAS_LDOCTL_REG */

/*!
 * @brief The enumeration of bandgap refresh period.
 */
typedef enum _vbat_bandgap_refresh_period
{
    kVBAT_BandgapRefresh7P8125ms = 0U, /*!< Bandgap refresh every 7.8125ms. */
    kVBAT_BandgapRefresh15P625ms = 1U, /*!< Bandgap refresh every 15.625ms. */
    kVBAT_BandgapRefresh31P25ms  = 2U, /*!< Bandgap refresh every 31.25ms. */
    kVBAT_BandgapRefresh62P5ms   = 3U, /*!< Bandgap refresh every 62.5ms. */
} vbat_bandgap_refresh_period_t;

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_BANDGAP_TIMER) && FSL_FEATURE_MCX_VBAT_HAS_BANDGAP_TIMER)
/*!
 * @brief The enumeration of bandgap timer0 timeout period.
 */
typedef enum _vbat_bandgap_timer0_timeout_period
{
    kVBAT_BangapTimer0Timeout1s      = 0U, /*!< Bandgap timer0 timerout every 1s. */
    kVBAT_BangapTimer0Timeout500ms   = 1U, /*!< Bandgap timer0 timerout every 500ms. */
    kVBAT_BangapTimer0Timeout250ms   = 2U, /*!< Bandgap timer0 timerout every 250ms. */
    kVBAT_BangapTimer0Timeout125ms   = 3U, /*!< Bandgap timer0 timerout every 125ms. */
    kVBAT_BangapTimer0Timeout62P5ms  = 4U, /*!< Bandgap timer0 timerout every 62.5ms. */
    kVBAT_BangapTimer0Timeout31P25ms = 5U, /*!< Bandgap timer0 timerout every 31.25ms. */
} vbat_bandgap_timer0_timeout_period_t;
#endif /* FSL_FEATURE_MCX_VBAT_HAS_BANDGAP_TIMER */

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_OSCCTL_REG) && FSL_FEATURE_MCX_VBAT_HAS_OSCCTL_REG)
/*!
 * @brief The enumeration of osc32k operate mode, including Bypass mode, low power switched mode and so on.
 */
typedef enum _vbat_osc32k_operate_mode
{
    kVBAT_Osc32kEnabledToTransconductanceMode = 0U, /*!< Set to transconductance mode. */
    kVBAT_Osc32kEnabledToLowPowerBackupMode   = 1U, /*!< Set to low power backup mode. */
    kVBAT_Osc32kEnabledToLowPowerSwitchedMode = 2U, /*!< Set to low power switched mode. */
} vbat_osc32k_operate_mode_t;

/*!
 * @brief The enumeration of OSC32K load capacitance.
 */
typedef enum _vbat_osc32k_load_capacitance_select
{
    kVBAT_Osc32kCrystalLoadCap0pF =
        0U,                         /*!< Internal capacitance bank is enabled, set the internal capacitance to 0 pF. */
    kVBAT_Osc32kCrystalLoadCap2pF,  /*!< Internal capacitance bank is enabled, set the internal capacitance to 2 pF. */
    kVBAT_Osc32kCrystalLoadCap4pF,  /*!< Internal capacitance bank is enabled, set the internal capacitance to 4 pF. */
    kVBAT_Osc32kCrystalLoadCap6pF,  /*!< Internal capacitance bank is enabled, set the internal capacitance to 6 pF. */
    kVBAT_Osc32kCrystalLoadCap8pF,  /*!< Internal capacitance bank is enabled, set the internal capacitance to 8 pF. */
    kVBAT_Osc32kCrystalLoadCap10pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 10 pF. */
    kVBAT_Osc32kCrystalLoadCap12pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 12 pF. */
    kVBAT_Osc32kCrystalLoadCap14pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 14 pF. */
    kVBAT_Osc32kCrystalLoadCap16pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 16 pF. */
    kVBAT_Osc32kCrystalLoadCap18pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 18 pF. */
    kVBAT_Osc32kCrystalLoadCap20pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 20 pF. */
    kVBAT_Osc32kCrystalLoadCap22pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 22 pF. */
    kVBAT_Osc32kCrystalLoadCap24pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 24 pF. */
    kVBAT_Osc32kCrystalLoadCap26pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 26 pF. */
    kVBAT_Osc32kCrystalLoadCap28pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 28 pF. */
    kVBAT_Osc32kCrystalLoadCap30pF, /*!< Internal capacitance bank is enabled, set the internal capacitance to 30 pF. */
    kVBAT_Osc32kCrystalLoadCapBankDisabled = 0xF0U, /*!< Internal capacitance bank is disabled. */
} vbat_osc32k_load_capacitance_select_t;

/*!
 * @brief The enumeration of start-up time of the oscillator.
 */
typedef enum _vbat_osc32k_start_up_time
{
    kVBAT_Osc32kStartUpTime8Sec = 0U, /*!< Configure the start-up time as 8 seconds. */
    kVBAT_Osc32kStartUpTime4Sec,      /*!< Configure the start-up time as 4 seconds. */
    kVBAT_Osc32kStartUpTime2Sec,      /*!< Configure the start-up time as 2 seconds. */
    kVBAT_Osc32kStartUpTime1Sec,      /*!< Configure the start-up time as 1 seconds. */
    kVBAT_Osc32kStartUpTime0P5Sec,    /*!< Configure the start-up time as 0.5 seconds. */
    kVBAT_Osc32kStartUpTime0P25Sec,   /*!< Configure the start-up time as 0.25 seconds. */
    kVBAT_Osc32kStartUpTime0P125Sec,  /*!< Configure the start-up time as 0.125 seconds. */
    kVBAT_Osc32kStartUpTime0P5MSec,   /*!< Configure the start-up time as 0.5 milliseconds. */
} vbat_osc32k_start_up_time_t;
#endif /* FSL_FEATURE_MCX_VBAT_HAS_OSCCTL_REG */

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_SWICTL_REG) && FSL_FEATURE_MCX_VBAT_HAS_SWICTL_REG)
/*!
 * @brief The enumeration of VBAT module supplies.
 */
typedef enum _vbat_internal_module_supply
{
    kVBAT_ModuleSuppliedByVddBat = 0U, /*!< VDD_BAT supplies VBAT modules. */
    kVBAT_ModuleSuppliedByVddSys = 1U, /*!< VDD_SYS supplies VBAT modules. */
} vbat_internal_module_supply_t;
#endif /* FSL_FEATURE_MCX_VBAT_HAS_SWICTL_REG */

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_CLKMON_REG) && FSL_FEATURE_MCX_VBAT_HAS_CLKMON_REG)
/*!
 * @brief The enumeration of VBAT clock monitor divide trim value
 */
typedef enum _vbat_clock_monitor_divide_trim
{
    kVBAT_ClockMonitorOperateAt1kHz = 0U, /*!< Clock monitor operates at 1 kHz. */
    kVBAT_ClockMonitorOperateAt64Hz = 1U, /*!< Clock monitor operates at 64 Hz. */
} vbat_clock_monitor_divide_trim_t;

/*!
 * @brief The enumeration of VBAT clock monitor frequency trim value used to adjust the clock monitor assert.
 */
typedef enum _vbat_clock_monitor_freq_trim
{
    kVBAT_ClockMonitorAssert2Cycle = 0U, /*!< Clock monitor assert 2 cycles after expected edge. */
    kVBAT_ClockMonitorAssert4Cycle = 1U, /*!< Clock monitor assert 4 cycles after expected edge. */
    kVBAT_ClockMonitorAssert6Cycle = 2U, /*!< Clock monitor assert 8 cycles after expected edge. */
    kVBAT_ClockMonitorAssert8Cycle = 3U, /*!< Clock monitor assert 8 cycles after expected edge. */
} vbat_clock_monitor_freq_trim_t;
#endif /* FSL_FEATURE_MCX_VBAT_HAS_CLKMON_REG */

/*!
 * @brief The structure of internal 16kHz free running oscillator attributes.
 */
typedef struct _vbat_fro16k_config
{
    bool enableFRO16k;              /*!< Enable/disable internal 16kHz free running oscillator. */
    uint8_t enabledConnectionsMask; /*!< The mask of connected modules to enable FRO16k clock output.  */
} vbat_fro16k_config_t;

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_CLKMON_REG) && FSL_FEATURE_MCX_VBAT_HAS_CLKMON_REG)
/*!
 * @brief The structure of internal clock monitor, including divide trim and frequency trim.
 */
typedef struct _vbat_clock_monitor_config
{
    vbat_clock_monitor_divide_trim_t divideTrim : 1U; /* !< Divide trim value, please
                                                    refer to @ref vbat_clock_monitor_divide_trim_t */
    vbat_clock_monitor_freq_trim_t freqTrim : 2U;     /*!< Frequency trim value used to adjust the clock monitor
                                                     assert, please refer to @ref vbat_clock_monitor_freq_trim_t. */
    bool lock : 1U;                                   /*!< Lock the clock monitor control after enabled. */
} vbat_clock_monitor_config_t;
#endif /* FSL_FEATURE_MCX_VBAT_HAS_CLKMON_REG */

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_TAMPER_REG) && FSL_FEATURE_MCX_VBAT_HAS_TAMPER_REG)
/*!
 * @brief The structure of Tamper configuration.
 */
typedef struct _vbat_tamper_config
{
    bool enableVoltageDetect : 1U;     /*!< Enable/disable voltage detection. */
    bool enableTemperatureDetect : 1U; /*!< Enable/disable temperature detection. */
    bool lock : 1U;                    /*!< Lock the tamper control after enabled. */
} vbat_tamper_config_t;
#endif /* FSL_FEATURE_MCX_VBAT_HAS_TAMPER_REG */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name FRO16K Control Interfaces
 * @{
 */

/*!
 * @brief Configure internal 16kHz free running oscillator, including enabel FRO16k, gate FRO16k output.
 *
 * @param base VBAT peripheral base address.
 * @param config Pointer to @ref vbat_fro16k_config_t structure.
 */
void VBAT_ConfigFRO16k(VBAT_Type *base, const vbat_fro16k_config_t *config);

/*!
 * @brief Enable/disable internal 16kHz free running oscillator.
 *
 * @param base VBAT peripheral base address.
 * @param enable Used to enable/disable 16kHz FRO.
 *          - \b true Enable internal 16kHz free running oscillator.
 *          - \b false Disable internal 16kHz free running oscillator.
 */
static inline void VBAT_EnableFRO16k(VBAT_Type *base, bool enable)
{
    if (enable)
    {
        base->FROCTLA |= VBAT_FROCTLA_FRO_EN_MASK;
#if (defined(VBAT_FROCTLB_INVERSE_MASK))
        base->FROCTLB &= ~VBAT_FROCTLB_INVERSE_MASK;
#endif /* VBAT_FROCTLB_INVERSE_MASK */
    }
    else
    {
        base->FROCTLA &= ~VBAT_FROCTLA_FRO_EN_MASK;
#if (defined(VBAT_FROCTLB_INVERSE_MASK))
        base->FROCTLB |= VBAT_FROCTLB_INVERSE_MASK;
#endif /* VBAT_FROCTLB_INVERSE_MASK */
    }
}

/*!
 * @brief Check if internal 16kHz free running oscillator is enabled.
 *
 * @param base VBAT peripheral base address.
 *
 * @retval true The internal 16kHz Free running oscillator is enabled.
 * @retval false The internal 16kHz Free running oscillator is enabled.
 */
static inline bool VBAT_CheckFRO16kEnabled(VBAT_Type *base)
{
    return (bool)((base->FROCTLA & VBAT_FROCTLA_FRO_EN_MASK) == VBAT_FROCTLA_FRO_EN_MASK);
}

/*!
 * @brief Enable FRO16kHz output clock to selected modules.
 *
 * @param base VBAT peripheral base address.
 * @param connectionsMask The mask of modules that FRO16k is connected, should be the OR'ed
 *                        value of @ref vbat_clock_enable_t.
 */
static inline void VBAT_UngateFRO16k(VBAT_Type *base, uint8_t connectionsMask)
{
    base->FROCLKE |= VBAT_FROCLKE_CLKE(connectionsMask);
}

/*!
 * @brief Disable FRO16kHz output clock to selected modules.
 *
 * @param base VBAT peripheral base address.
 * @param connectionsMask The OR'ed value of @ref vbat_clock_enable_t.
 */
static inline void VBAT_GateFRO16k(VBAT_Type *base, uint8_t connectionsMask)
{
    base->FROCLKE &= ~VBAT_FROCLKE_CLKE(connectionsMask);
}

/*!
 * @brief Lock settings of internal 16kHz free running oscillator, please note that if locked 16kHz FRO's settings can
 * not be updated until the next POR.
 *
 * @note Please note that the operation to ungate/gate FRO 16kHz output clock can not be locked by this function.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_LockFRO16kSettings(VBAT_Type *base)
{
    base->FROLCKA |= VBAT_FROLCKA_LOCK_MASK;
#if (defined(VBAT_FROLCKB_LOCK_MASK))
    base->FROLCKB &= ~VBAT_FROLCKB_LOCK_MASK;
#endif /* VBAT_FROLCKB_LOCK_MASK */
}

/*!
 * @brief Check if FRO16K settings are locked.
 *
 * @param base VBAT peripheral base address.
 *
 * @return @c true in case of FRO16k settings are locked, @c false in case of FRO16k settings are not locked.
 */
static inline bool VBAT_CheckFRO16kSettingsLocked(VBAT_Type *base)
{
    return ((base->FROLCKA & VBAT_FROLCKA_LOCK_MASK) != 0UL);
}

/*! @} */

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_OSCCTL_REG) && FSL_FEATURE_MCX_VBAT_HAS_OSCCTL_REG)
/*!
 * @name OSC32K Control Interfaces
 * @{
 */

/*!
 * @brief Enable/disable 32K Crystal Oscillator.
 *
 * @param base VBAT peripheral base address.
 * @param enable Used to enable/disable 32k Crystal Oscillator:
 *         - \b true Enable crystal oscillator and polling status register to check clock is ready.
 *         - \b false Disable crystal oscillator.
 */
static inline void VBAT_EnableCrystalOsc32k(VBAT_Type *base, bool enable)
{
    if (enable)
    {
        base->OSCCTLA |= VBAT_OSCCTLA_OSC_EN_MASK;
        base->OSCCTLB &= ~VBAT_OSCCTLA_OSC_EN_MASK;

        /* Polling status register to check clock is ready. */
        while ((base->STATUSA & VBAT_STATUSA_OSC_RDY_MASK) == 0UL)
        {}
    }
    else
    {
        base->OSCCTLA &= ~VBAT_OSCCTLA_OSC_EN_MASK;
        base->OSCCTLB |= VBAT_OSCCTLA_OSC_EN_MASK;
    }
}

/*!
 * @brief Bypass 32k crystal oscillator, the clock is still output by oscillator but this clock is the same as clock
 * provided on EXTAL pin.
 *
 * @note In bypass mode, oscillator must be enabled; To exit bypass mode, oscillator must be disabled.
 *
 * @param base VBAT peripheral base address.
 * @param enableBypass Used to enter/exit bypass mode:
 *          - \b true Enter into bypass mode;
 *          - \b false Exit bypass mode.
 */
static inline void VBAT_BypassCrystalOsc32k(VBAT_Type *base, bool enableBypass)
{
    if (enableBypass)
    {
        base->OSCCTLA |= (VBAT_OSCCTLA_OSC_EN_MASK | VBAT_OSCCTLA_OSC_BYP_EN_MASK);
        base->OSCCTLB &= ~(VBAT_OSCCTLA_OSC_EN_MASK | VBAT_OSCCTLA_OSC_BYP_EN_MASK);
    }
    else
    {
        base->OSCCTLA &= ~(VBAT_OSCCTLA_OSC_EN_MASK | VBAT_OSCCTLA_OSC_BYP_EN_MASK);
        base->OSCCTLB |= (VBAT_OSCCTLA_OSC_EN_MASK | VBAT_OSCCTLA_OSC_BYP_EN_MASK);
    }
}

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_OSCCTLA_FINE_AMP_GAIN_BIT) && FSL_FEATURE_MCX_VBAT_HAS_OSCCTLA_FINE_AMP_GAIN_BIT) 
/*!
 * @brief Adjust 32k crystal oscillator amplifier gain.
 *
 * @param base VBAT peripheral base address.
 * @param coarse Specify amplifier coarse trim value.
 * @param fine Specify amplifier fine trim value.
 */
static inline void VBAT_AdjustCrystalOsc32kAmplifierGain(VBAT_Type *base, uint8_t coarse, uint8_t fine)
{
    base->OSCCTLA = ((base->OSCCTLA & ~(VBAT_OSCCTLA_COARSE_AMP_GAIN_MASK | VBAT_OSCCTLA_FINE_AMP_GAIN_MASK)) |
                     (VBAT_OSCCTLA_COARSE_AMP_GAIN(coarse) | VBAT_OSCCTLA_FINE_AMP_GAIN(fine)));
    base->OSCCTLB = ((base->OSCCTLB & ~(VBAT_OSCCTLA_COARSE_AMP_GAIN_MASK | VBAT_OSCCTLA_FINE_AMP_GAIN_MASK)) |
                     (VBAT_OSCCTLA_COARSE_AMP_GAIN(~coarse) | VBAT_OSCCTLA_FINE_AMP_GAIN(~fine)));
}
#else
/*!
 * @brief Adjust 32k crystal oscillator amplifier gain.
 *
 * @param base VBAT peripheral base address.
 * @param coarse Specify amplifier coarse trim value.
 */
static inline void VBAT_AdjustCrystalOsc32kAmplifierGain(VBAT_Type *base, uint8_t coarse)
{
    base->OSCCTLA = (base->OSCCTLA & ~VBAT_OSCCTLA_COARSE_AMP_GAIN_MASK) | (VBAT_OSCCTLA_COARSE_AMP_GAIN(coarse));
    base->OSCCTLB = (base->OSCCTLB & ~VBAT_OSCCTLA_COARSE_AMP_GAIN_MASK) | (VBAT_OSCCTLA_COARSE_AMP_GAIN(~(uint32_t)coarse));        
}

#endif /*  */

/*!
 * @brief Set 32k crystal oscillator mode and load capacitance for the XTAL/EXTAL pin.
 *
 * @param base VBAT peripheral base address.
 * @param operateMode Specify the crystal oscillator mode, please refer to @ref vbat_osc32k_operate_mode_t.
 * @param xtalCap Specify the internal capacitance for the XTAL pin from the capacitor bank.
 * @param extalCap Specify the internal capacitance for the EXTAL pin from the capacitor bank.
 *
 * @retval kStatus_VBAT_WrongCapacitanceValue The load capacitance value to set is not align with operate mode's
 * requirements.
 * @retval kStatus_Success Success to set operate mode and load capacitance.
 */
status_t VBAT_SetCrystalOsc32kModeAndLoadCapacitance(VBAT_Type *base,
                                                     vbat_osc32k_operate_mode_t operateMode,
                                                     vbat_osc32k_load_capacitance_select_t xtalCap,
                                                     vbat_osc32k_load_capacitance_select_t extalCap);

/*!
 * @brief Trim 32k crystal oscillator startup time.
 *
 * @param base VBAT peripheral base address.
 * @param startupTime Specify the startup time of the oscillator.
 */
static inline void VBAT_TrimCrystalOsc32kStartupTime(VBAT_Type *base, vbat_osc32k_start_up_time_t startupTime)
{
    base->OSCCFGA = ((base->OSCCFGA & ~(VBAT_OSCCFGA_INIT_TRIM_MASK)) | VBAT_OSCCFGA_INIT_TRIM(startupTime));
    base->OSCCFGB = ((base->OSCCFGB & ~(VBAT_OSCCFGA_INIT_TRIM_MASK)) | VBAT_OSCCFGA_INIT_TRIM(~((uint32_t)startupTime)));
}

/*!
 * @brief Set crystal oscillator comparator trim value when oscillator is set as low power switch mode.
 *
 * @param base VBAT peripheral base address.
 * @param comparatorTrimValue Comparator trim value, ranges from 0 to 7.
 */
static inline void VBAT_SetOsc32kSwitchModeComparatorTrimValue(VBAT_Type *base, uint8_t comparatorTrimValue)
{
    base->OSCCFGA = ((base->OSCCFGA & ~VBAT_OSCCFGA_CMP_TRIM_MASK) | VBAT_OSCCFGA_CMP_TRIM(comparatorTrimValue));
    base->OSCCFGB = ((base->OSCCFGB & ~VBAT_OSCCFGA_CMP_TRIM_MASK) | VBAT_OSCCFGA_CMP_TRIM(~((uint32_t)comparatorTrimValue)));
}

/*!
 * @brief Set crystal oscillator delay trim value when oscillator is set as low power switch mode.
 *
 * @param base VBAT peripheral base address.
 * @param delayTrimValue Delay trim value, ranges from 0 to 15.
 */
static inline void VBAT_SetOsc32kSwitchModeDelayTrimValue(VBAT_Type *base, uint8_t delayTrimValue)
{
    base->OSCCFGA = ((base->OSCCFGA & ~VBAT_OSCCFGA_DLY_TRIM_MASK) | VBAT_OSCCFGA_DLY_TRIM(delayTrimValue));
    base->OSCCFGB = ((base->OSCCFGB & ~VBAT_OSCCFGA_DLY_TRIM_MASK) | VBAT_OSCCFGA_DLY_TRIM(~((uint32_t)delayTrimValue)));
}

/*!
 * @brief Set crystal oscillator capacitor trim value when oscillator is set as low power switch mode.
 *
 * @param base VBAT peripheral base address.
 * @param capacitorTrimValue Capacitor value to trim, ranges from 0 to 3.
 */
static inline void VBAT_SetOsc32kSwitchModeCapacitorTrimValue(VBAT_Type *base, uint8_t capacitorTrimValue)
{
    base->OSCCFGA = ((base->OSCCFGA & ~VBAT_OSCCFGA_CAP_TRIM_MASK) | VBAT_OSCCFGA_CAP_TRIM(capacitorTrimValue));
    base->OSCCFGB = ((base->OSCCFGB & ~VBAT_OSCCFGA_CAP_TRIM_MASK) | VBAT_OSCCFGA_CAP_TRIM(~((uint32_t)capacitorTrimValue)));
}

/*!
 * @brief Lock Osc32k settings, after locked all writes to the Oscillator registers are blocked.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_LookOsc32kSettings(VBAT_Type *base)
{
    base->OSCLCKA |= VBAT_OSCLCKA_LOCK_MASK;
    base->OSCLCKB &= ~VBAT_OSCLCKB_LOCK_MASK;
}

/*!
 * @brief Unlock Osc32k settings.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_UnlockOsc32kSettings(VBAT_Type *base)
{
    base->OSCLCKA &= ~VBAT_OSCLCKA_LOCK_MASK;
    base->OSCLCKB |= VBAT_OSCLCKB_LOCK_MASK;
}

/*!
 * @brief Check if osc32k settings are locked.
 *
 * @param base VBAT peripheral base address.
 * @return \c true in case of osc32k settings are locked, \c false in case of osc32k settings are not locked.
 */
static inline bool VBAT_CheckOsc32kSettingsLocked(VBAT_Type *base)
{
    return ((base->OSCLCKA & VBAT_OSCLCKA_LOCK_MASK) != 0UL);
}

/*!
 * @brief Enable OSC32k output clock to selected modules.
 *
 * @param base VBAT peripheral base address.
 * @param connectionsMask The OR'ed value of @ref vbat_clock_enable_t.
 */
static inline void VBAT_UngateOsc32k(VBAT_Type *base, uint8_t connectionsMask)
{
    base->OSCCLKE |= VBAT_OSCCLKE_CLKE(connectionsMask);
}

/*!
 * @brief Disable OSC32k output clock to selected modules.
 *
 * @param base VBAT peripheral base address.
 * @param connectionsMask The OR'ed value of @ref vbat_clock_enable_t.
 */
static inline void VBAT_GateOsc32k(VBAT_Type *base, uint8_t connectionsMask)
{
    base->OSCCLKE &= ~VBAT_OSCCLKE_CLKE(connectionsMask);
}

/*! @} */
#endif /* FSL_FEATURE_MCX_VBAT_HAS_OSCCTL_REG */

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_LDOCTL_REG) && FSL_FEATURE_MCX_VBAT_HAS_LDOCTL_REG)
/*!
 * @name RAM_LDO Control Interfaces
 * @{
 */

/*!
 * @brief Enable/disable Bandgap.
 *
 * @note The FRO16K must be enabled before enabling the bandgap.
 * @note This setting can be locked by VBAT_LockRamLdoSettings() function.
 *
 * @param base VBAT peripheral base address.
 * @param enable Used to enable/disable bandgap.
 *      - \b true Enable the bandgap.
 *      - \b false Disable the bandgap.
 *
 * @retval kStatus_Success Success to enable/disable the bandgap.
 * @retval kStatus_VBAT_Fro16kNotEnabled Fail to enable the bandgap due to FRO16k is not enabled previously.
 */
status_t VBAT_EnableBandgap(VBAT_Type *base, bool enable);

/*!
 * @brief Check if bandgap is enabled.
 *
 * @param base VBAT peripheral base address.
 *
 * @retval true The bandgap is enabled.
 * @retval false The bandgap is disabled.
 */
static inline bool VBAT_CheckBandgapEnabled(VBAT_Type *base)
{
    return (bool)((base->LDOCTLA & VBAT_LDOCTLA_BG_EN_MASK) == VBAT_LDOCTLA_BG_EN_MASK);
}

/*!
 * @brief Enable/disable bandgap low power refresh mode.
 *
 * @note For lowest power consumption, refresh mode must be enabled.
 * @note This setting can be locked by VBAT_LockRamLdoSettings() function.
 *
 * @param base VBAT peripheral base address.
 * @param enableRefreshMode Used to enable/disable bandgap low power refresh mode.
 *          - \b true Enable bandgap low power refresh mode.
 *          - \b false Disable bandgap low power refresh mode.
 */
static inline void VBAT_EnableBandgapRefreshMode(VBAT_Type *base, bool enableRefreshMode)
{
    if (enableRefreshMode)
    {
        base->LDOCTLA |= VBAT_LDOCTLA_REFRESH_EN_MASK;
        base->LDOCTLB &= ~VBAT_LDOCTLA_REFRESH_EN_MASK;
    }
    else
    {
        base->LDOCTLA &= ~VBAT_LDOCTLA_REFRESH_EN_MASK;
        base->LDOCTLB |= VBAT_LDOCTLA_REFRESH_EN_MASK;
    }
}

/*!
 * @brief Enable/disable Backup RAM Regulator(RAM_LDO).
 *
 * @note This setting can be locked by VBAT_LockRamLdoSettings() function.
 *
 * @param base VBAT peripheral base address.
 * @param enable Used to enable/disable RAM_LDO.
 *          - \b true Enable backup SRAM regulator.
 *          - \b false Disable backup SRAM regulator.
 *
 * @retval kStatusSuccess Success to enable/disable backup SRAM regulator.
 * @retval kStatus_VBAT_Fro16kNotEnabled Fail to enable backup SRAM regulator due to FRO16k is not enabled previously.
 * @retval kStatus_VBAT_BandgapNotEnabled Fail to enable backup SRAM regulator due to the bandgap is not enabled
 * previously.
 */
status_t VBAT_EnableBackupSRAMRegulator(VBAT_Type *base, bool enable);

/*!
 * @brief Lock settings of RAM_LDO, please note that if locked then RAM_LDO's settings
 * can not be updated until the next POR.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_LockRamLdoSettings(VBAT_Type *base)
{
    base->LDOLCKA |= VBAT_LDOLCKA_LOCK_MASK;
    base->LDOLCKB &= ~VBAT_LDOLCKA_LOCK_MASK;
}

/*!
 * @brief Check if RAM_LDO settings is locked.
 *
 * @param base VBAT peripheral base address.
 * @return @c true in case of RAM_LDO settings are locked, @c false in case of RAM_LDO settings are unlocked.
 */
static inline bool VBAT_CheckRamLdoSettingsLocked(VBAT_Type *base)
{
    return ((base->LDOLCKA & VBAT_LDOLCKA_LOCK_MASK) != 0UL);
}

/*!
 * @brief Switch the SRAM to be powered by LDO_RAM.
 *
 * @note This function can be used to switch the SRAM to the VBAT retention supply at any time, but please note that the
 * SRAM must not be accessed during this time.
 * @note Invoke this function to switch power supply before switching off external power.
 * @note RAM_LDO must be enabled before invoking this function.
 * @note To access the SRAM arrays retained by the LDO_RAM, please invoke VBAT_SwitchSRAMPowerBySocSupply(), after
 * external power is switched back on.
 *
 * @param base VBAT peripheral base address.
 *
 * @retval kStatusSuccess Success to Switch SRAM powered by VBAT.
 * @retval kStatus_VBAT_Fro16kNotEnabled Fail to switch SRAM powered by VBAT due to FRO16K not enabled previously.
 */
status_t VBAT_SwitchSRAMPowerByLDOSRAM(VBAT_Type *base);

/*!
 * @brief Switch the RAM to be powered by Soc Supply in software mode.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_SwitchSRAMPowerBySocSupply(VBAT_Type *base)
{
    base->LDORAMC &= ~VBAT_LDORAMC_SWI_MASK;
    base->LDORAMC &= ~VBAT_LDORAMC_ISO_MASK;
}

/*!
 * @brief Power off selected SRAM array in low power modes.
 *
 * @param base VBAT peripheral base address.
 * @param sramMask The mask of SRAM array to power off, should be the OR'ed value of @ref vbat_ram_array_t.
 */
static inline void VBAT_PowerOffSRAMsInLowPowerModes(VBAT_Type *base, uint8_t sramMask)
{
    base->LDORAMC |= (uint32_t)VBAT_LDORAMC_RET(sramMask);
}

/*!
 * @brief Retain selected SRAM array in low power modes.
 *
 * @param base VBAT peripheral base address.
 * @param sramMask The mask of SRAM array to retain, should be the OR'ed value of @ref vbat_ram_array_t.
 */
static inline void VBAT_RetainSRAMsInLowPowerModes(VBAT_Type *base, uint8_t sramMask)
{
    base->LDORAMC &= ~(uint32_t)VBAT_LDORAMC_RET(sramMask);
}

/*!
 * @brief Enable/disable SRAM isolation.
 *
 * @param base VBAT peripheral base address.
 * @param enable Used to enable/disable SRAM violation.
 *          - \b true SRAM will be isolated.
 *          - \b false SRAM state follows the SoC power modes.
 */
static inline void VBAT_EnableSRAMIsolation(VBAT_Type *base, bool enable)
{
    if (enable)
    {
        base->LDORAMC |= VBAT_LDORAMC_ISO_MASK;
    }
    else
    {
        base->LDORAMC &= ~VBAT_LDORAMC_ISO_MASK;
    }
}

/*! @} */
#endif /* FSL_FEATURE_MCX_VBAT_HAS_RAM_LDO */

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_BANDGAP_TIMER) && FSL_FEATURE_MCX_VBAT_HAS_BANDGAP_TIMER)
/*! @name Bandgap Timer Control Interfaces
 * @{
 */

/*!
 * @brief Enable/disable Bandgap timer.
 *
 * @note The bandgap timer is available when the bandgap is enabled and are clocked by the FRO16k.
 *
 * @param base VBAT peripheral base address.
 * @param enable Used to enable/disable bandgap timer.
 * @param timerIdMask The mask of bandgap timer Id, should be the OR'ed value of @ref vbat_bandgap_timer_id_t.
 *
 * @retval kStatus_Success Success to enable/disable selected bandgap timer.
 * @retval kStatus_VBAT_Fro16kNotEnabled Fail to enable/disable selected bandgap timer due to FRO16k not enabled
 * previously.
 * @retval kStatus_VBAT_BandgapNotEnabled Fail to enable/disable selected bandgap timer due to bandgap not enabled
 * previously.
 */
status_t VBAT_EnableBandgapTimer(VBAT_Type *base, bool enable, uint8_t timerIdMask);

/*!
 * @brief Set bandgap timer0 timeout value.
 *
 * @note The timeout value can only be changed when the timer is disabled.
 *
 * @param base VBAT peripheral base address.
 * @param timeoutPeriod Bandgap timer timeout value, please refer to @ref vbat_bandgap_timer0_timeout_period_t.
 */
void VBAT_SetBandgapTimer0TimeoutValue(VBAT_Type *base, vbat_bandgap_timer0_timeout_period_t timeoutPeriod);

/*!
 * @brief Set bandgap timer1 timeout value.
 *
 * @note The timeout value can only be changed when the timer is disabled.
 *
 * @param base VBAT peripheral base address.
 * @param timeoutPeriod The bandgap timerout 1 period, in number of seconds, ranging from 0 to 65535s.
 */
void VBAT_SetBandgapTimer1TimeoutValue(VBAT_Type *base, uint32_t timeoutPeriod);

/*! @} */
#endif /* FSL_FEATURE_MCX_VBAT_HAS_BANDGAP_TIMER */

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_SWICTL_REG) && FSL_FEATURE_MCX_VBAT_HAS_SWICTL_REG)
/*! @name Switch Control Interfaces
 * @{
 */

/*!
 * @brief Control the VBAT internal switch in active mode, VBAT modules can be suppiled by VDD_BAT and VDD_SYS.
 *
 * @param base VBAT peripheral base address.
 * @param supply Used to control the VBAT internal switch.
 */
static inline void VBAT_SwitchVBATModuleSupplyActiveMode(VBAT_Type *base, vbat_internal_module_supply_t supply)
{
    if (supply == kVBAT_ModuleSuppliedByVddBat)
    {
        base->SWICTLA &= ~VBAT_SWICTLA_SWI_EN_MASK;
        base->SWICTLB |= VBAT_SWICTLA_SWI_EN_MASK;
    }
    else
    {
        base->SWICTLA |= VBAT_SWICTLA_SWI_EN_MASK;
        base->SWICTLB &= ~VBAT_SWICTLA_SWI_EN_MASK;
    }
}

/*!
 * @brief Get VBAT module supply in active mode.
 *
 * @param base VBAT peripheral base address.
 * @return VDD_SYS supplies VBAT modules or VDD_BAT supplies VBAT modules, in type of @ref
 * vbat_internal_module_supply_t.
 */
static inline vbat_internal_module_supply_t VBAT_GetVBATModuleSupply(VBAT_Type *base)
{
    return (vbat_internal_module_supply_t)(uint8_t)(base->SWICTLA & VBAT_SWICTLA_SWI_EN_MASK);
}

/*!
 * @brief Control the VBAT internal switch in low power modes.
 *
 * @note If VBAT modules are supplied by VDD_SYS in low power modes, VBAT module will also supplied by VDD_SYS in active
 * mode.
 *
 * @param base VBAT peripheral base address.
 * @param supply Used to specify which voltage input supply VBAT modules in low power mode.
 */
static inline void VBAT_SwitchVBATModuleSupplyLowPowerMode(VBAT_Type *base, vbat_internal_module_supply_t supply)
{
    if (supply == kVBAT_ModuleSuppliedByVddBat)
    {
        base->SWICTLA &= ~VBAT_SWICTLA_LP_EN_MASK;
        base->SWICTLB |= VBAT_SWICTLA_LP_EN_MASK;
    }
    else
    {
        base->SWICTLA |= VBAT_SWICTLA_SWI_EN_MASK;
        base->SWICTLB &= ~VBAT_SWICTLA_SWI_EN_MASK;
        base->SWICTLA |= VBAT_SWICTLA_LP_EN_MASK;
        base->SWICTLB &= ~VBAT_SWICTLA_LP_EN_MASK;
    }
}

/*!
 * @brief Lock switch control, if locked all writes to the switch registers will be blocked.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_LockSwitchControl(VBAT_Type *base)
{
    base->SWILCKA |= VBAT_SWILCKA_LOCK_MASK;
    base->SWILCKB &= ~VBAT_SWILCKB_LOCK_MASK;
}

/*!
 * @brief Unlock switch control.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_UnlockSwitchControl(VBAT_Type *base)
{
    base->SWILCKA &= ~VBAT_SWILCKA_LOCK_MASK;
    base->SWILCKB |= VBAT_SWILCKB_LOCK_MASK;
}

/*!
 * @brief Check if switch control is locked.
 *
 * @param base VBAT peripheral base address.
 *
 * @retval false switch control is not locked.
 * @retval true  switch control is locked, any writes to related registers are blocked.
 */
static inline bool VBAT_CheckSwitchControlLocked(VBAT_Type *base)
{
    return ((base->SWILCKA & VBAT_SWILCKA_LOCK_MASK) != 0UL);
}

/*! @} */
#endif /* FSL_FEATURE_MCX_VBAT_HAS_SWICTL_REG */

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_CLKMON_REG) && FSL_FEATURE_MCX_VBAT_HAS_CLKMON_REG)
/*!
 * @name Clock Monitor Interfaces
 * @{
 */

/*!
 * @brief Initialize the VBAT clock monitor, enable clock monitor and set the clock monitor configuration.
 *
 * @note Both FRO16K and OSC32K should be enabled and stable before invoking this function.
 *
 * @param base VBAT peripheral base address.
 * @param config Pointer to @ref vbat_clock_monitor_config_t structure.
 *
 * @retval kStatus_Success Clock monitor is initialized successfully.
 * @retval kStatus_VBAT_Fro16kNotEnabled FRO16K is not enabled.
 * @retval kStatus_VBAT_Osc32kNotReady OSC32K is not ready.
 * @retval kStatus_VBAT_ClockMonitorLocked Clock monitor is locked.
 */
status_t VBAT_InitClockMonitor(VBAT_Type *base, const vbat_clock_monitor_config_t *config);

/*!
 * @brief Deinitialize the VBAT clock monitor.
 *
 * @param base VBAT peripheral base address.
 *
 * @retval kStatus_Success Clock monitor is de-initialized successfully.
 * @retval kStatus_VBAT_ClockMonitorLocked Control of Clock monitor is locked.
 */
status_t VBAT_DeinitMonitor(VBAT_Type *base);

/*!
 * @brief Enable/disable clock monitor.
 *
 * @param base VBAT peripheral base address.
 * @param enable Switcher to enable/disable clock monitor:
 *         - true: enable clock monitor;
 *        - false: disable clock monitor.
 */
static inline void VBAT_EnableClockMonitor(VBAT_Type *base, bool enable)
{
    if (enable)
    {
        base->MONCTLA |= VBAT_MONCTLA_MON_EN_MASK;
        base->MONCTLB &= ~VBAT_MONCTLA_MON_EN_MASK;
    }
    else
    {
        base->MONCTLA &= ~VBAT_MONCTLA_MON_EN_MASK;
        base->MONCTLB |= VBAT_MONCTLA_MON_EN_MASK;
    }
}

/*!
 * @brief Set clock monitor's divide trim, avaiable value is #kVBAT_ClockMonitorOperateAt1kHz and
 * #kVBAT_ClockMonitorOperateAt64Hz
 *
 * @param base VBAT peripheral base address.
 * @param divideTrim Specify divide trim value, please refer to @ref vbat_clock_monitor_divide_trim_t.
 */
static inline void VBAT_SetClockMonitorDivideTrim(VBAT_Type *base, vbat_clock_monitor_divide_trim_t divideTrim)
{
    base->MONCFGA = (base->MONCFGA & ~VBAT_MONCFGA_DIVIDE_TRIM_MASK) | VBAT_MONCFGA_DIVIDE_TRIM(divideTrim);
    base->MONCFGB = (base->MONCFGB & ~VBAT_MONCFGA_DIVIDE_TRIM_MASK) | VBAT_MONCFGA_DIVIDE_TRIM(~divideTrim);
}

/*!
 * @brief Set clock monitor's frequency trim, avaiable value is #kVBAT_ClockMonitorAssert2Cycle,
 * #kVBAT_ClockMonitorAssert4Cycle, #kVBAT_ClockMonitorAssert6Cycle and #kVBAT_ClockMonitorAssert8Cycle.
 *
 * @param base VBAT peripheral base address.
 * @param freqTrim Specify frequency trim value, please refer to @ref vbat_clock_monitor_freq_trim_t.
 */
static inline void VBAT_SetClockMonitorFrequencyTrim(VBAT_Type *base, vbat_clock_monitor_freq_trim_t freqTrim)
{
    base->MONCFGA = (base->MONCFGA & ~VBAT_MONCFGA_FREQ_TRIM_MASK) | VBAT_MONCFGA_FREQ_TRIM(freqTrim);
    base->MONCFGB = (base->MONCFGB & ~VBAT_MONCFGA_FREQ_TRIM_MASK) | VBAT_MONCFGA_FREQ_TRIM(~freqTrim);
}

/*!
 * @brief Lock clock monitor enable/disable control.
 *
 * @note If locked, it is not allowed to change clock monitor enable/disable control.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_LockClockMonitorControl(VBAT_Type *base)
{
    base->MONLCKA |= VBAT_MONLCKA_LOCK_MASK;
    base->MONLCKB &= ~VBAT_MONLCKA_LOCK_MASK;
}

/*!
 * @brief Unlock clock monitor enable/disable control.
 *
 * @param base VBTA peripheral base address.
 */
static inline void VBAT_UnlockClockMonitorControl(VBAT_Type *base)
{
    base->MONLCKA &= ~VBAT_MONLCKA_LOCK_MASK;
    base->MONLCKB |= VBAT_MONLCKA_LOCK_MASK;
}

/*!
 * @brief Check if clock monitor enable/disable control is locked.
 *
 * @note If locked, it is not allowed to change clock monitor enable/disable control.
 *
 * @param base VBAT peripheral base address.
 *
 * @retval false clock monitor enable/disable control is not locked.
 * @retval true  clock monitor enable/disable control is locked, any writes to related registers are blocked.
 */
static inline bool VBAT_CheckClockMonitorControlLocked(VBAT_Type *base)
{
    return ((base->MONLCKA & VBAT_MONLCKA_LOCK_MASK) != 0UL);
}

/*! @} */
#endif /* FSL_FEATURE_VBAT_HAS_CLOCK_MONITOR */

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_TAMPER_REG) && FSL_FEATURE_MCX_VBAT_HAS_TAMPER_REG)
/*! @name Tamper Control Interfaces
 *
 */

/*!
 * @brief Initialize tamper control.
 *
 * @note Both FRO16K and bandgap should be enabled before calling this function.
 *
 * @param base VBAT peripheral base address.
 * @param config Pointer to @ref vbat_tamper_config_t structure.
 *
 * @retval kStatus_Success Tamper is initialized successfully.
 * @retval kStatus_VBAT_TamperLocked Tamper control is locked.
 * @retval kStatus_VBAT_BandgapNotEnabled Bandgap is not enabled.
 * @retval kStatus_VBAT_Fro16kNotEnabled FRO 16K is not enabled.
 */
status_t VBAT_InitTamper(VBAT_Type *base, const vbat_tamper_config_t *config);

/*!
 * @brief De-initialize tamper control.
 *
 * @param base VBAT peripheral base address.
 *
 * @retval kStatus_Success Tamper is de-initialized successfully.
 * @retval kStatus_VBAT_TamperLocked Tamper control is locked.
 */
status_t VBAT_DeinitTamper(VBAT_Type *base);

/*!
 * @brief Enable tampers for VBAT.
 *
 * @param base VBAT peripheral base address.
 * @param tamperEnableMask Mask of tamper to be enabled, should be the OR'ed value of @ref _vbat_tamper_enable.
 */
static inline void VBAT_EnableTamper(VBAT_Type *base, uint32_t tamperEnableMask)
{
    base->TAMPERA |= tamperEnableMask;
    base->TAMPERB &= ~tamperEnableMask;
}

/*!
 * @brief Disable tampers for VBAT.
 *
 * @param base VBAT peripheral base address.
 * @param tamperEnableMask Mask of tamper to be disabled, should be the OR'ed value of @ref _vbat_tamper_enable.
 */
static inline void VBAT_DisableTamper(VBAT_Type *base, uint32_t tamperEnableMask)
{
    base->TAMPERA &= ~tamperEnableMask;
    base->TAMPERB |= tamperEnableMask;
}

/*!
 * @brief Get tamper enable information.
 *
 * @param base VBAT peripheral base address.
 *
 * @return Mask of tamper enable information, should be the OR'ed value of @ref _vbat_tamper_enable.
 */
static inline uint32_t VBAT_GetTamperEnableInfo(VBAT_Type *base)
{
    return base->TAMPERA;
}

/*!
 * @brief Lock tamper control, if locked, it is not allowed to change tamper control.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_LockTamperControl(VBAT_Type *base)
{
    base->TAMLCKA |= VBAT_TAMLCKA_LOCK_MASK;
    base->TAMLCKB &= ~VBAT_TAMLCKA_LOCK_MASK;
}

/*!
 * @brief Unlock tamper control.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_UnlockTamperControl(VBAT_Type *base)
{
    base->TAMLCKA &= ~VBAT_TAMLCKA_LOCK_MASK;
    base->TAMLCKB |= VBAT_TAMLCKA_LOCK_MASK;
}

/*!
 * @brief Check if tamper control is locked.
 *
 * @param base VBAT peripheral base address.
 *
 * @retval false Tamper control is not locked.
 * @retval true  Tamper control is locked, any writes to related registers are blocked.
 */
static inline bool VBAT_CheckTamperControlLocked(VBAT_Type *base)
{
    return ((base->TAMLCKA & VBAT_TAMLCKA_LOCK_MASK) != 0UL);
}

/*! @} */
#endif /* FSL_FEATURE_VBAT_HAS_TAMPER */

#if (defined(FSL_FEATURE_MCX_VBAT_HAS_STATUS_REG) && FSL_FEATURE_MCX_VBAT_HAS_STATUS_REG)
/*! @name Status, Interrupt, Wakeup Control Interfaces
 * @{
 */

/*!
 * @brief Get VBAT status flags
 *
 * @param base VBAT peripheral base address.
 * @return The asserted status flags, should be the OR'ed value of @ref vbat_status_flag_t.
 */
static inline uint32_t VBAT_GetStatusFlags(VBAT_Type *base)
{
    return (uint32_t)(base->STATUSA);
}

/*!
 * @brief Clear VBAT status flags.
 *
 * @param base VBAT peripheral base address.
 * @param mask The mask of status flags to be cleared, should be the OR'ed value of @ref vbat_status_flag_t except
 *              @ref kVBAT_StatusFlagLdoReady, @ref kVBAT_StatusFlagOsc32kReady, @ref kVBAT_StatusFlagInterrupt0Detect,
 *              @ref kVBAT_StatusFlagInterrupt1Detect, @ref kVBAT_StatusFlagInterrupt2Detect,
 *              @ref kVBAT_StatusFlagInterrupt3Detect.
 */
static inline void VBAT_ClearStatusFlags(VBAT_Type *base, uint32_t mask)
{
    base->STATUSA = mask;
    base->STATUSB = ~mask;
}

/*!
 * @brief Enable interrupts for the VBAT module, such as POR detect interrupt, Wakeup Pin interrupt and so on.
 *
 * @param base VBAT peripheral base address.
 * @param mask The mask of interrupts to be enabled, should be the OR'ed value of @ref vbat_interrupt_enable_t.
 */
static inline void VBAT_EnableInterrupts(VBAT_Type *base, uint32_t mask)
{
    base->IRQENA |= mask;
    base->IRQENB &= (uint32_t)~mask;
}

/*!
 * @brief Disable interrupts for the VBAT module, such as POR detect interrupt, wakeup pin interrupt and so on.
 *
 * @param base VBAT peripheral base address.
 * @param mask The mask of interrupts to be disabled, should be the OR'ed value of @ref vbat_interrupt_enable_t.
 */
static inline void VBAT_DisableInterrupts(VBAT_Type *base, uint32_t mask)
{
    base->IRQENA &= ~mask;
    base->IRQENB |= mask;
}

/*!
 * @brief Enable wakeup for the VBAT module, such as POR detect wakeup, wakeup pin wakeup and so on.
 *
 * @param base VBAT peripheral base address.
 * @param mask The mask of enumerators in @ref vbat_wakeup_enable_t.
 */
static inline void VBAT_EnableWakeup(VBAT_Type *base, uint32_t mask)
{
    base->WAKENA |= mask;
    base->WAKENB &= ~mask;
}

/*!
 * @brief Disable wakeup for VBAT module, such as POR detect wakeup, wakeup pin wakeup and so on.
 *
 * @param base VBAT peripheral base address.
 * @param mask The mask of enumerators in @ref vbat_wakeup_enable_t.
 */
static inline void VBAT_DisableWakeup(VBAT_Type *base, uint32_t mask)
{
    base->WAKENA &= ~mask;
    base->WAKENB |= mask;
}

/*!
 * @brief Lock VBAT interrupt and wakeup settings, please note that if locked the interrupt and wakeup settings can not
 * be updated until the next POR.
 *
 * @param base VBAT peripheral base address.
 */
static inline void VBAT_LockInterruptWakeupSettings(VBAT_Type *base)
{
    base->LOCKA |= VBAT_LOCKA_LOCK_MASK;
}

/*!
 * @brief Set the default state of the WAKEUP_b pin output when no enabled wakeup source is asserted.
 *
 * @param base VBAT peripheral base address.
 * @param assert Used to set default state of the WAKEUP_b pin output:
 *          - \b true WAKEUP_b output state is logic one;
 *          - \b false WAKEUP_b output state is logic zero.
 */
static inline void VBAT_SetWakeupPinDefaultState(VBAT_Type *base, bool assert)
{
    if (assert)
    {
        base->WAKECFG |= VBAT_WAKECFG_OUT_MASK;
    }
    else
    {
        base->WAKECFG &= ~VBAT_WAKECFG_OUT_MASK;
    }
}

/*! @} */
#endif /* FSL_FEATURE_MCX_VBAT_HAS_STATUS_REG */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* FSL_VBAT_H__ */
