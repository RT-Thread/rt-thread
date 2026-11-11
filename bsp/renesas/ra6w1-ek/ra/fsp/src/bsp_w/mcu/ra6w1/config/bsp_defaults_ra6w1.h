/**
 * \addtogroup PLA_BSP_CONFIG
 * \{
 * \addtogroup BSP_CONFIG_DEFAULTS
 * \{
 */

/**
 ****************************************************************************************
 *
 * @file bsp_defaults_ra6w1.h
 *
 * @brief Board Support Package. Device-specific system configuration default values.
 *
 * Copyright (c) 2023-2024 Renesas Electronics. All rights reserved.
 *
 * This software ("Software") is owned by Renesas Electronics.
 *
 * By using this Software you agree that Renesas Electronics retains all
 * intellectual property and proprietary rights in and to this Software and any
 * use, reproduction, disclosure or distribution of the Software without express
 * written permission or a license agreement from Renesas Electronics is
 * strictly prohibited. This Software is solely for use on or in conjunction
 * with Renesas Electronics products.
 *
 * EXCEPT AS OTHERWISE PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, THE
 * SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. EXCEPT AS OTHERWISE
 * PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, IN NO EVENT SHALL
 * RENESAS ELECTRONICS BE LIABLE FOR ANY DIRECT, SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THE SOFTWARE.
 *
 ****************************************************************************************
 */

#ifndef BSP_DEFAULTS_RA6W1_H_
#define BSP_DEFAULTS_RA6W1_H_

#if (DEVICE_FAMILY == DA1640X)

/* Deprecated configuration options must not be defined by the application. */

 #define DG_CONFIG_NA_87X_MSG               DG_CONFIG_NOT_APPLICABLE_MSG " for the DA1640x device family."
 #define DG_CONFIG_NA_87X_FORCE_ZERO_MSG    DG_CONFIG_NA_87X_MSG " Forcing to 0 (not used)."
 #define DG_CONFIG_TIMER_NA_MSG             DG_CONFIG_NA_87X_MSG " Use the generic dg_configUSE_HW_TIMER instead."

 #ifdef dg_configTim1Prescaler
  #pragma message "dg_configTim1Prescaler" DG_CONFIG_NA_87X_MSG
  #undef  dg_configTim1Prescaler
 #endif

 #ifdef dg_configTim1PrescalerBitRange
  #pragma message "dg_configTim1PrescalerBitRange" DG_CONFIG_NA_87X_MSG
  #undef dg_configTim1PrescalerBitRange
 #endif

 #ifdef dg_configEXT_CRYSTAL_FREQ
  #pragma message "dg_configEXT_CRYSTAL_FREQ" DG_CONFIG_NA_87X_MSG
  #undef  dg_configEXT_CRYSTAL_FREQ
 #endif

 #ifdef dg_configUSER_CAN_USE_TIMER1
  #pragma message "dg_configUSER_CAN_USE_TIMER1" DG_CONFIG_NA_87X_MSG
  #undef  dg_configUSER_CAN_USE_TIMER1
 #endif

 #if (dg_configUSE_HW_RF != 0)
  #pragma message "dg_configUSE_HW_RF" DG_CONFIG_NA_87X_FORCE_ZERO_MSG
  #undef  dg_configUSE_HW_RF
  #define dg_configUSE_HW_RF    0
 #endif

 #if (dg_configUSE_HW_ECC != 0)
  #pragma message "dg_configUSE_HW_ECC" DG_CONFIG_NA_87X_FORCE_ZERO_MSG
  #undef  dg_configUSE_HW_ECC
  #define dg_configUSE_HW_ECC    0
 #endif

 #if (dg_configUSE_IF_PDM != 0)
  #pragma message "dg_configUSE_IF_PDM" DG_CONFIG_NA_87X_FORCE_ZERO_MSG
  #undef  dg_configUSE_IF_PDM
  #define dg_configUSE_IF_PDM    0
 #endif

 #if (dg_configUSE_HW_IRGEN != 0)
  #pragma message "dg_configUSE_HW_TEMPSENS" DG_CONFIG_NA_87X_FORCE_ZERO_MSG
  #undef  dg_configUSE_HW_IRGEN
  #define dg_configUSE_HW_IRGEN    0
 #endif

 #if (dg_configUSE_HW_SOC != 0)
  #pragma message "dg_configUSE_HW_SOC" DG_CONFIG_NA_87X_FORCE_ZERO_MSG
  #undef  dg_configUSE_HW_SOC
  #define dg_configUSE_HW_SOC    0
 #endif

 #if (dg_configUSE_HW_TIMER0 != 0)
  #pragma message "dg_configUSE_HW_TIMERX" DG_CONFIG_TIMER_NA_MSG
  #undef  dg_configUSE_HW_TIMER0
  #define dg_configUSE_HW_TIMER0    0
 #endif

 #if (dg_configUSE_HW_TIMER1 != 0)
  #pragma message "dg_configUSE_HW_TIMERX" DG_CONFIG_TIMER_NA_MSG
  #undef  dg_configUSE_HW_TIMER1
  #define dg_configUSE_HW_TIMER1    0
 #endif

 #if (dg_configUSE_HW_TIMER2 != 0)
  #pragma message "dg_configUSE_HW_TIMERX" DG_CONFIG_TIMER_NA_MSG
  #undef  dg_configUSE_HW_TIMER2
  #define dg_configUSE_HW_TIMER2    0
 #endif

/* ------------------------------- Peripherals -------------------------------------------------- */

/**
 * \addtogroup PERIPHERALS_690 Peripherals for DA1487x
 *
 * \brief Peripheral Selection for the DA1487x Device Family
 *
 * When enabled the specific low level driver is included in the compilation of the SDK.
 * - 0 : Disabled
 * - 1 : Enabled
 *
 * The default option can be overridden in the application configuration file.
 *
 * \{
 * Driver                         | Setting                                | Default option
 * ------------------------------ | -------------------------------------- | :------------------:
 * AES HASH                       | dg_configUSE_HW_AES_HASH               | 0
 * Cache Controller               | dg_configUSE_HW_CACHE                  | 1
 * HW charger                     | dg_configUSE_HW_CHARGER                | 0
 * Clock driver                   | dg_configUSE_HW_CLK                    | 1
 * Clock and Power Manager        | dg_configUSE_HW_CPM                    | 1
 * Direct Memory Access           | dg_configUSE_HW_DMA                    | 1
 * Haptic Controller / ERM        | dg_configUSE_HW_ERM                    | 0
 * General Purpose A-D  Converter | dg_configUSE_HW_GPADC                  | 1
 * General Purpose I/O            | dg_configUSE_HW_GPIO                   | 1
 * Inter-Integrated Circuit       | dg_configUSE_HW_I2C                    | 0
 * ISO7816                        | dg_configUSE_HW_ISO7816                | 0
 * LCD controller                 | dg_configUSE_HW_LCDC                   | 0
 * Haptic Controller / LRA        | dg_configUSE_HW_LRA                    | 0
 * Memory Protection Unit         | dg_configUSE_HW_MPU                    | 0
 * OQSPI controller               | dg_configUSE_HW_OQSPI                  | 1
 * OTP controller                 | dg_configUSE_HW_OTPC                   | 1
 * Domain Driver                  | dg_configUSE_HW_PD                     | 1
 * Power Domains Controller       | dg_configUSE_HW_PDC                    | 1
 * Power Manager                  | dg_configUSE_HW_PMU                    | 1
 * QSPI controller                | dg_configUSE_HW_QSPI                   | 0
 * Real Time Clock                | dg_configUSE_HW_RTC                    | 1
 * Analog-Digital Converter       | dg_configUSE_HW_SDADC                  | 1
 * Sensor Node Controller         | dg_configUSE_HW_SENSOR_NODE            | 0
 * Motor Controller               | dg_configUSE_HW_SMOTOR                 | 0
 * Serial Peripheral Interface    | dg_configUSE_HW_SPI                    | 0
 * System                         | dg_configUSE_HW_SYS                    | 1
 * Timer                          | dg_configUSE_HW_TIMER                  | 1
 * True Random Generator          | dg_configUSE_HW_TRNG                   | 1
 * UART                           | dg_configUSE_HW_UART                   | 1
 * USB                            | dg_configUSE_HW_USB                    | 0
 * USB charger                    | dg_configUSE_HW_USB_CHARGER            | 0
 * Wakeup timer                   | dg_configUSE_HW_WKUP                   | 1
 * PCM                            | dg_configUSE_HW_PCM                    | 0
 * PDM                            | dg_configUSE_HW_PDM                    | 0
 * APU SRC                        | dg_configUSE_HW_APU_SRC                | 0
 */

/* -------------------------------- Peripherals (hw_*) selection -------------------------------- */

 #ifndef dg_configUSE_HW_AES_HASH
  #define dg_configUSE_HW_AES_HASH    (0)
 #endif

 #ifndef dg_configUSE_HW_CACHE
  #define dg_configUSE_HW_CACHE       (1)
 #endif

 #ifndef dg_configUSE_HW_CHARGER
  #define dg_configUSE_HW_CHARGER     (0)
 #endif

 #ifndef dg_configUSE_HW_CLK
  #define dg_configUSE_HW_CLK         (1)
 #endif

 #ifndef dg_configUSE_HW_CPM
  #define dg_configUSE_HW_CPM         (0)
 #endif

 #ifndef dg_configUSE_HW_DMA
  #define dg_configUSE_HW_DMA         (1)
 #endif

 #ifndef dg_configUSE_HW_KDMA
  #define dg_configUSE_HW_KDMA        (0)
 #endif

 #ifndef dg_configUSE_HW_ERM
  #define dg_configUSE_HW_ERM         (0)
 #endif

 #ifndef dg_configUSE_HW_GPADC
  #define dg_configUSE_HW_GPADC       (0)
 #endif

 #if 0                                 /* TODO : Check this needs */
/* XXX workaround for bug2522A_155: PLL calibration does not work properly */
/* XXX GPADC is used for PLL workaround in case there isn't trimmed value for PLL_SYS_CTRL3_REG */
  #if !DEVICE_FPGA
   #if (dg_configUSE_HW_GPADC == 0)
    #error "dg_configUSE_HW_GPADC should be 1 in order to properly trim the PLL clock"
   #endif
  #endif
 #endif

 #ifndef dg_configUSE_HW_GPIO
  #define dg_configUSE_HW_GPIO       (1)
 #endif

 #ifndef dg_configUSE_HW_I2C
  #define dg_configUSE_HW_I2C        (0)
 #endif

 #ifndef dg_configUSE_HW_ISO7816
  #define dg_configUSE_HW_ISO7816    (0)
 #endif

 #ifndef dg_configUSE_HW_LCDC
  #define dg_configUSE_HW_LCDC       (0)
 #endif

 #ifndef dg_configUSE_HW_LRA
  #define dg_configUSE_HW_LRA        (0)
 #endif

 #ifndef dg_configUSE_HW_MPU
  #define dg_configUSE_HW_MPU        (0)
 #endif

 #ifndef dg_configUSE_HW_OQSPI
  #define dg_configUSE_HW_OQSPI      (1)
 #endif

 #ifndef dg_configUSE_HW_OTPC
  #define dg_configUSE_HW_OTPC       (1)
 #endif

 #ifndef dg_configUSE_HW_PD
  #define dg_configUSE_HW_PD         (0)
 #endif

 #ifndef dg_configUSE_HW_PDC
  #define dg_configUSE_HW_PDC        (0)
 #endif

 #ifndef dg_configUSE_HW_PMU
  #define dg_configUSE_HW_PMU        (0)
 #endif

 #ifndef dg_configUSE_HW_QSPI
  #define dg_configUSE_HW_QSPI       (0)
 #endif

 #ifndef dg_configUSE_HW_QSPI2
  #define dg_configUSE_HW_QSPI2      (0)
 #elif (dg_configUSE_HW_QSPI2 == 1)
  #error "DA1640X has no QSPI2"
 #endif

 #ifndef dg_configUSE_HW_RTC
  #define dg_configUSE_HW_RTC            (1)
 #endif

 #ifndef dg_configUSE_HW_SDADC
  #define dg_configUSE_HW_SDADC          (0)
 #endif

 #ifndef dg_configUSE_HW_SENSOR_NODE
  #define dg_configUSE_HW_SENSOR_NODE    (0)
 #endif

 #ifndef dg_configUSE_HW_SMOTOR
  #define dg_configUSE_HW_SMOTOR         (0)
 #endif

 #ifndef dg_configUSE_HW_SPI
  #define dg_configUSE_HW_SPI            (0)
 #endif

 #ifndef dg_configUSE_HW_SYS
  #define dg_configUSE_HW_SYS            (0)
 #endif

 #ifndef dg_configUSE_HW_TIMER
  #define dg_configUSE_HW_TIMER          (1)
 #endif

 #ifndef dg_configUSE_HW_TRNG
  #define dg_configUSE_HW_TRNG           (0)
 #endif

 #ifndef dg_configUSE_HW_UART
  #define dg_configUSE_HW_UART           (1)
 #endif

 #ifndef dg_configUSE_HW_USB
  #define dg_configUSE_HW_USB            (0)
 #endif

 #ifndef dg_configUSE_HW_USB_CHARGER
  #define dg_configUSE_HW_USB_CHARGER    (0)
 #endif

 #ifndef dg_configUSE_HW_WKUP
  #define dg_configUSE_HW_WKUP           (0)
 #endif

 #ifndef dg_configUSE_HW_PCM
  #define dg_configUSE_HW_PCM            (0)
 #endif

 #ifndef dg_configUSE_HW_PDM
  #define dg_configUSE_HW_PDM            (0)
 #endif

 #ifndef dg_configUSE_HW_APU_SRC
  #define dg_configUSE_HW_APU_SRC        (0)
 #endif

 #ifndef dg_configUSE_HW_SDEMMC
  #define dg_configUSE_HW_SDEMMC         (1)
 #endif

 #ifndef dg_configUSE_HW_SDIO
  #define dg_configUSE_HW_SDIO           (1)
 #endif

 #ifndef dg_configUSE_HW_PRNG
  #define dg_configUSE_HW_PRNG           (1)
 #endif

/**
 * \}
 */

/* ------------------------------- Clock Settings ----------------------------------------------- */

/**
 * \addtogroup CLOCK_SETTINGS
 *
 * \{
 */

 #if (BSP_CFG_LP_CLOCK_SOURCE != BSP_CLOCKS_SOURCE_CLOCK_RCX) && \
    (BSP_CFG_LP_CLOCK_SOURCE != BSP_CLOCKS_SOURCE_CLOCK_XTALK)
  #error "BSP_CFG_LP_CLOCK_SOURCE has invalid setting"
 #endif

 #ifndef dg_configXTAL40M_FREQ
  #define dg_configXTAL40M_FREQ        (40000000)
 #endif

 #ifndef dg_configXTAL80M_FREQ
  #define dg_configXTAL80M_FREQ        (80000000)
 #endif

 #ifndef dg_configDIVN_FREQ
  #define dg_configDIVN_FREQ           (40000000)
 #endif

 #ifndef dg_configPLL480M_FREQ
  #define dg_configPLL480M_FREQ        (480000000)
 #endif

 #ifndef dg_configPLL320M_FREQ
  #define dg_configPLL320M_FREQ        (320000000)
 #endif

 #ifndef dg_configPLL192M_FREQ
  #define dg_configPLL192M_FREQ        (192000000)
 #endif

 #ifndef dg_configPLL160M_FREQ
  #define dg_configPLL160M_FREQ        (160000000)
 #endif

 #ifndef dg_configPLL137M_FREQ
  #define dg_configPLL137M_FREQ        (137142857)
 #endif

 #ifndef dg_configPLL106M_FREQ
  #define dg_configPLL106M_FREQ        (106666666)
 #endif

 #ifndef dg_configPLL80M_FREQ
  #define dg_configPLL80M_FREQ         (80000000)
 #endif

 #ifndef dg_configPERI80M_FREQ
  #define dg_configPERI80M_FREQ        (80000000)
 #endif

 #ifndef dg_configPERI40M_FREQ
  #define dg_configPERI40M_FREQ        (40000000)
 #endif

 #ifndef dg_configPERIOCS32K_FREQ
  #define dg_configPERIOCS32K_FREQ     (32000)
 #endif

 #ifndef dg_configPERICRY32K_FREQ
  #define dg_configPERICRY32K_FREQ     (32768)
 #endif

/**
 * \brief Vaule of the RC32K oscilator frequency in Hz
 */
 #ifndef dg_configRC32K_FREQ
  #define dg_configRC32K_FREQ          (32000)
 #endif

 #ifndef dg_configXTAL32K_FREQ
  #define dg_configXTAL32K_FREQ        (32768)
 #endif

 #ifndef dg_configXTAL40M_32K_FREQ
  #define dg_configXTAL40M_32K_FREQ    (32000)
 #endif

/**
 * \brief Acceptable clock tick drift (in parts per million) for the Low-power clock
 */
 #ifndef dg_configLP_CLK_DRIFT
  #if BSP_CFG_LP_CLOCK_SOURCE == BSP_CLOCKS_SOURCE_CLOCK_RCX
   #define dg_configLP_CLK_DRIFT    (500) // ppm
  #else
   #define dg_configLP_CLK_DRIFT    (50)  // ppm
  #endif
 #endif

/**
 * \brief Time needed for the settling of the LP clock, in msec.
 */
 #ifndef dg_configXTAL32K_SETTLE_TIME
  #if dg_configLP_CLK_SOURCE == LP_CLK_IS_ANALOG
   #define dg_configXTAL32K_SETTLE_TIME    (1300)
  #else
   #define dg_configXTAL32K_SETTLE_TIME    (1000)
  #endif
 #endif

/**
 * \brief XTAL40M settle time
 *
 * Time needed for the settling of the XTAL40M, in usec.
 *
 * \note If set to zero, the settling time will be automatically adjusted.
 */
 #ifndef dg_configXTAL40M_SETTLE_TIME_IN_USEC
  #define dg_configXTAL40M_SETTLE_TIME_IN_USEC    (0x0)
 #endif

/**
 * \brief Enable XTAL40M upon system wake-up
 *
 * If set to 1 the PDC will enable XTAL40M when it wakes-up M33
 *
 */
 #ifndef dg_configENABLE_XTAL40M_ON_WAKEUP
  #define dg_configENABLE_XTAL40M_ON_WAKEUP       (1)
 #endif

/**
 * \brief The number of LP clock cycles required to check the voltage of an LDO during startup
 */
 #ifndef dg_configVOLTAGE_CHECK_LP_CYCLES
  #define dg_configVOLTAGE_CHECK_LP_CYCLES        (5)
 #endif

/**
 * \brief The number of LP clock cycles required for the HW FSM to detect the wake-up signal
 */
 #ifndef dg_configHW_FSM_WAKEUP_CYCLES
  #define dg_configHW_FSM_WAKEUP_CYCLES           (3)
 #endif

/**
 * \brief The number of LP clock cycles required for the system to start-up
 */
 #ifndef dg_configSYSTEM_STARTUP_CYCLES

// 4 @ SRAM Boot
// unstable 12, stable 16?/20  @ Cache Boot 1.8V, Fully discharged PWR
// unstable 33, stable 36?/40  @ Cache Boot 3.3V, Fully discharged PWR
// max 100 @ VSIM contidion
  #define dg_configSYSTEM_STARTUP_CYCLES                                      (100)
 #endif

/**
 * \brief RC32 wake-up time in slow wake-up mode
 *
 * This is the maximum time, in LP cycles, needed to wake-up the chip and start executing code
 * using RC32 in slow wake-up mode.
 *
 * \note Wake-up time calculation:
 *              dg_configHW_FSM_WAKEUP_CYCLES cycles for wake-up
 *              1 additional cycle for slow wake-up
 *              2 cycles for V30 (worst case Vclamp -> 3V)
 *              1 cycle for BG
 *              dg_configVOLTAGE_CHECK_LP_CYCLES cycles for V12 and V14
 *              dg_configVOLTAGE_CHECK_LP_CYCLES cycles for V18P
 *              dg_configVOLTAGE_CHECK_LP_CYCLES cycles for V18
 *              dg_configSYSTEM_STARTUP_CYCLES cycles for system start-up
 */
 #define dg_configWAKEUP_RC32_TIME_SLOW                                       (dg_configHW_FSM_WAKEUP_CYCLES + 4 +    \
                                                                               3 * dg_configVOLTAGE_CHECK_LP_CYCLES + \
                                                                               dg_configSYSTEM_STARTUP_CYCLES)

/**
 * \brief RC32 wake-up time in fast wake-up mode
 *
 * This is the maximum time, in LP cycles, needed to wake-up the chip and start executing code
 * using RC32 in fast wake-up mode.
 *
 * \note Wake-up time calculation:
 *              dg_configHW_FSM_WAKEUP_CYCLES cycles for wake-up
 *              dg_configVOLTAGE_CHECK_LP_CYCLES cycles for V12 (worst case 0.75V -> 0.9V)
 *              dg_configSYSTEM_STARTUP_CYCLES cycles for system start-up
 */
 #define dg_configWAKEUP_RC32_TIME_FAST                                       (dg_configHW_FSM_WAKEUP_CYCLES +    \
                                                                               dg_configVOLTAGE_CHECK_LP_CYCLES + \
                                                                               dg_configSYSTEM_STARTUP_CYCLES)

/**
 * \brief RC32 wake-up time
 *
 * This is the maximum time, in LP cycles, needed to wake-up the chip and start executing code
 * using RC32 in ultra-fast wake-up mode.
 *
 * \note Wake-up time calculation:
 *              dg_configHW_FSM_WAKEUP_CYCLES cycles for wake-up
 *              dg_configSYSTEM_STARTUP_CYCLES cycles for system start-up
 */
 #define dg_configWAKEUP_RC32_TIME_ULTRA_FAST                                 (dg_configHW_FSM_WAKEUP_CYCLES + \
                                                                               dg_configSYSTEM_STARTUP_CYCLES)

/**
 * \brief XTAL32M trimming default settings
 */
 #ifndef dg_configDEFAULT_CLK_FREQ_TRIM_REG__XTAL32M_TRIM__VALUE
  #define dg_configDEFAULT_CLK_FREQ_TRIM_REG__XTAL32M_TRIM__VALUE             (0x120)
 #endif

 #ifndef dg_configDEFAULT_XTAL32M_CTRL0_REG__XTAL32M_CXCOMP_ENABLE__VALUE
  #define dg_configDEFAULT_XTAL32M_CTRL0_REG__XTAL32M_CXCOMP_ENABLE__VALUE    (0x0)
 #endif

 #ifndef dg_configUSE_CLOCK_MGR
  #ifdef OS_BAREMETAL
   #define dg_configUSE_CLOCK_MGR                                             (0)
  #elif defined(OS_FREERTOS)
   #define dg_configUSE_CLOCK_MGR                                             (0)
  #endif
 #endif

/**
 * \}
 */

/* ------------------------------- System configuration settings -------------------------------- */

/**
 * \addtogroup SYSTEM_CONFIGURATION_SETTINGS
 *
 * \{
 */

/**
 * \brief Reset value for Watchdog when system is idle.
 */
 #ifndef dg_configWDOG_IDLE_RESET_VALUE
  #define dg_configWDOG_IDLE_RESET_VALUE    (SYS_WDOG_WATCHDOG_REG_WDOG_VAL_Msk >> SYS_WDOG_WATCHDOG_REG_WDOG_VAL_Pos)
 #endif

/**
 * \brief Maximum watchdog tasks
 *
 * Maximum number of tasks that the Watchdog Service can monitor. It can be larger (up to 32) than
 * needed, at the expense of increased Retention Memory requirement.
 */
 #ifndef dg_configWDOG_MAX_TASKS_CNT
  #define dg_configWDOG_MAX_TASKS_CNT       (64)
 #endif

/**
 * \brief Extend maximum watchdog tasks
 *
 * When set to 1, maximum number of tasks can be larger (up to 64).
 */
 #ifndef dg_configWDOG_EXT
  #define dg_configWDOG_EXT                 (1)
 #endif

/*
 * \brief When set to 1, the LEDs are used from M33.
 *        When set to 0, the LEDs are used from SNC.
 */
 #ifndef dg_configM33_USES_LEDS
  #define dg_configM33_USES_LEDS            (1)
 #endif

/*
 * \brief When set to 1, the GPIO configuration becomes static, i.e. it does not change during runtime.
 *        When set to 0, the GPIO configuration can change during runtime.
 *
 * \note If SNC is enabled (i.e. dg_configUSE_HW_SENSOR_NODE == 1), the GPIO configuration must be
 *       static, thus dg_configUSE_STATIC_IO_CONFIG is set to 1
 */
 #if dg_configUSE_HW_SENSOR_NODE
  #undef dg_configUSE_STATIC_IO_CONFIG
  #define dg_configUSE_STATIC_IO_CONFIG     (1)
 #else
  #ifndef dg_configUSE_STATIC_IO_CONFIG
   #define dg_configUSE_STATIC_IO_CONFIG    (0)
  #endif
 #endif

/**
 * \}
 */

/* -------------------------------------- Flash settings ---------------------------------------- */

/**
 * \addtogroup FLASH_SETTINGS
 *
 * \{
 */

/**
 * \brief When set to 1, the 1V8 rail is powered, when the system is in active state.
 * When set to 2 the rail configuration will be defined by the application
 */
 #ifndef dg_configPOWER_1V8_ACTIVE
  #define dg_configPOWER_1V8_ACTIVE    (2)
 #else
  #if (dg_configPOWER_1V8_ACTIVE == 0) && (dg_configFLASH_CONNECTED_TO == FLASH_CONNECTED_TO_1V8)
   #error \
    "Flash is connected to the 1V8 rail but the rail is turned off. Please do not set dg_configPOWER_1V8_ACTIVE to 0."
  #endif
 #endif

/**
 * \brief When set to 1, the 1V8 is powered during sleep.
 * When set to 2 the rail configuration will be defined by the application
 */
 #ifndef dg_configPOWER_1V8_SLEEP
  #define dg_configPOWER_1V8_SLEEP    (2)
 #endif

/**
 * \brief When set to 1, the 1V8P rail is powered.
 */
 #ifdef dg_configPOWER_1V8P
  #if defined(dg_configPOWER_1V8P_ACTIVE) || defined(dg_configPOWER_1V8P_SLEEP)
   #error "dg_configPOWER_1V8P cannot be used when dg_configPOWER_1V8P_ACTIVE or dg_configPOWER_1V8P_SLEEP is used"
  #else
   #if dg_configPOWER_1V8P == 1
    #define dg_configPOWER_1V8P_ACTIVE    (1)
    #define dg_configPOWER_1V8P_SLEEP     (1)
   #else
    #error \
    "GPADC digital logic is connected to the 1V8P rail but the rail is turned off. Please do not set dg_configPOWER_1V8P to 0."
   #endif
  #endif
 #endif

/**
 * \brief When set to 1, the 1V8P rail is powered, when the system is in active state.
 * When set to 2 the rail configuration will be defined by the application
 */
 #ifndef dg_configPOWER_1V8P_ACTIVE
  #define dg_configPOWER_1V8P_ACTIVE    (2)
 #else
  #if dg_configPOWER_1V8P_ACTIVE == 0
   #error \
    "GPADC digital logic is connected to the 1V8P rail but the rail is turned off. Please do not set dg_configPOWER_1V8P_ACTIVE to 0."
  #endif
 #endif

 #if defined(dg_configPOWER_1V8P_ACTIVE) && (dg_configPOWER_1V8P_ACTIVE == 0) && \
    (dg_configFLASH_CONNECTED_TO == FLASH_CONNECTED_TO_1V8P || dg_configFLASH_CONNECTED_TO == FLASH_CONNECTED_TO_1V8F)
  #error \
    "Flash is connected to the 1V8P rail but the rail is turned off. Please do not set dg_configPOWER_1V8P_ACTIVE to 0."
 #endif

 #if (dg_configFLASH_CONNECTED_TO == FLASH_CONNECTED_TO_1V8P || dg_configFLASH_CONNECTED_TO == FLASH_CONNECTED_TO_1V8F) \
    && defined(dg_configFLASH_POWER_OFF) && defined(dg_configPOWER_1V8P_SLEEP) && (dg_configPOWER_1V8P_SLEEP == 0)
  #error \
    "Both dg_configFLASH_POWER_OFF and dg_configPOWER_1V8P_SLEEP are defined! Please use dg_configPOWER_1V8P_SLEEP only!"
 #endif

 #if (dg_configFLASH_CONNECTED_TO == FLASH_CONNECTED_TO_1V8) && defined(dg_configFLASH_POWER_OFF) && \
    defined(dg_configPOWER_1V8_SLEEP)
  #error \
    "Both dg_configFLASH_POWER_OFF and dg_configPOWER_1V8_SLEEP are defined. Please use dg_configPOWER_1V8_SLEEP only!"
 #endif

/**
 * \brief When set to 1, the 1V8P is powered during sleep.
 * When set to 2 the rail configuration will be defined by the application
 */
 #ifndef dg_configPOWER_1V8P_SLEEP
  #define dg_configPOWER_1V8P_SLEEP    (2)
 #else
  #if dg_configPOWER_1V8P_SLEEP == 0
   #error \
    "GPADC digital logic is connected to the 1V8P rail but the rail is turned off. Please do not set dg_configPOWER_1V8P_SLEEP to 0."
  #endif
 #endif

/**
 * \brief When set to 1, the Flash is powered off during sleep.
 */
 #ifndef dg_configFLASH_POWER_OFF

// dg_configFLASH_POWER_OFF will only be allowed to be defined to 1 if dg_configFLASH_CONNECTED_TO == FLASH_CONNECTED_TO_1V8P or FLASH_CONNECTED_TO_1V8F
// and dg_configPOWER_1V8P_SLEEP == 1
  #if (((dg_configFLASH_CONNECTED_TO == FLASH_CONNECTED_TO_1V8) && defined(dg_configPOWER_1V8_SLEEP) &&                 \
    (dg_configPOWER_1V8_SLEEP == 0)) ||                                                                                 \
    ((dg_configFLASH_CONNECTED_TO == FLASH_CONNECTED_TO_1V8P || dg_configFLASH_CONNECTED_TO == FLASH_CONNECTED_TO_1V8F) \
    && defined(dg_configPOWER_1V8P_SLEEP) && (dg_configPOWER_1V8P_SLEEP == 0)))
   #define dg_configFLASH_POWER_OFF    (1)
  #else
   #define dg_configFLASH_POWER_OFF    (0)
  #endif
 #endif                                /* dg_configFLASH_POWER_OFF */

/**
 * \brief Enable the Auto-detection mode for QSPIC2 device
 *
 * \warning THIS WILL GREATLY INCREASE THE CODE SIZE AND RETRAM USAGE!!! MAKE SURE YOUR PROJECT
 *          CAN SUPPORT THIS.
 */
 #ifndef dg_configQSPIC2_DEV_AUTODETECT
  #define dg_configQSPIC2_DEV_AUTODETECT    (0)
 #endif

 #if dg_configQSPIC2_DEV_AUTODETECT == 0

/**
 * \brief The QSPI  2 Driver header file to include
 *
 * The header file must be in the include path of the compiler
 */
  #ifndef dg_configQSPIC2_DEV_HEADER_FILE
   #define dg_configQSPIC2_DEV_HEADER_FILE    "psram_aps6404jsq.h"
  #endif

/**
 * \brief The QSPI 2 Driver configuration structure
 *
 * The configuration structure must be in the include path of the compiler
 */
  #ifndef dg_configQSPIC2_DEV_CONFIG
   #define dg_configQSPIC2_DEV_CONFIG         psram_aps6404jsq_config
  #endif

 #endif                                /* dg_configQSPIC2_DEV_AUTODETECT  == 0 */

 #if dg_configFLASH_AUTODETECT == 0

/**
 * \brief The Flash Driver header file to include
 *
 * The header file must be in the include path of the compiler
 */
  #ifndef dg_configFLASH_HEADER_FILE
   #define dg_configFLASH_HEADER_FILE    "qspi_mx25u3235.h"
  #endif                               /* dg_configFLASH_HEADER_FILE */

/**
 * \brief The Flash Driver configuration structure
 *
 * The configuration structure must be in the include path of the compiler
 */
  #ifndef dg_configFLASH_CONFIG
   #define dg_configFLASH_CONFIG         flash_mx25u3235_config
  #endif                               /* dg_configFLASH_CONFIG */

 #endif                                /* dg_configFLASH_AUTODETECT == 0 */

 #if (dg_configUSE_HW_QSPI == 1)

/**
 * \brief The base address for accessing the Flash memory connected to QSPIC2
 *
 * The base address is used in qspi_automode. Automode is using a single zero-based address region
 * for accessing the QSPI Flash devices connected to both QSPI controllers (QSPIC1 and QSPIC2).
 * Two address sub-regions are defined:
 *    Address region 1: 0..dg_configQSPI2_FLASH_BASE_ADDR-1
 *    Address region 2: starting at dg_configQSPI2_FLASH_BASE_ADDR
 * When QSPI Flash address is in region 1 then the device connected to QSPIC1 is accessed.
 * When QSPI Flash address is in region 2 then the device connected to QSPIC2 is accessed.
 * The maximum region size handled by each QSPI controller in automode is 32MBytes. The
 * default value of dg_configQSPI2_FLASH_BASE_ADDR is 0x2000000 allowing 32MBytes region
 * for each controller. The default value can be overridden and set to the size of the QSPI
 * Flash device connected to QSPIC1 to allow a continuous address space for both devices.
 */
  #ifndef dg_configQSPI2_FLASH_BASE_ADDR
   #define dg_configQSPI2_FLASH_BASE_ADDR    0x2000000
  #endif

 #endif                                /* dg_configUSE_HW_QSPI */

 #if (dg_configFLASH_AUTODETECT == 0) || (dg_configQSPIC2_DEV_AUTODETECT == 0)

/**
 * \brief Flash device configuration verification.
 *
 * When set to 1, the Flash device id configuration is checked against the JEDEC ID read
 * from the controller.
 *
 * Applicable only when flash auto detection is not enabled.
 */
  #ifndef dg_configFLASH_CONFIG_VERIFY
   #define dg_configFLASH_CONFIG_VERIFY    (0)
  #endif
 #endif                                /* (dg_configFLASH_AUTODETECT == 0) || (dg_configQSPIC2_DEV_AUTODETECT == 0) */

/**
 * \}
 */

/* ----------------------------------- Charger settings ----------------------------------------- */

/**
 * \addtogroup CHARGER_SETTINGS Charger configuration settings
 *
 * \{
 */

/**
 * \brief When set to 1, State of Charge function is enabled.
 */
 #ifndef dg_configUSE_SOC
  #define dg_configUSE_SOC    (0)
 #endif

/**
 * \}
 */

/* ----------------------------------- UART settings -------------------------------------------- */

/**
 * \addtogroup UART_SETTINGS
 *
 * \{
 */

/**
 * \brief UART3's software FIFO size
 */
 #ifndef dg_configUART3_SOFTWARE_FIFO_SIZE
  #define dg_configUART3_SOFTWARE_FIFO_SIZE          (0)
 #endif

/**
 * \brief UART3's Circular DMA buffer size for RX
 */
 #ifndef dg_configUART3_RX_CIRCULAR_DMA_BUF_SIZE
  #define dg_configUART3_RX_CIRCULAR_DMA_BUF_SIZE    (0)
 #endif

/**
 * \}
 */

/*
 */

/*------------------------------------ BOARDS DEFINITIONS ----------------------------------------*/

/**
 * \brief Set the board that is used.
 */
 #ifndef dg_configUSE_BOARD
  #include "boards/brd_io_config_ra6w1.h"
  #define dg_configUSE_BOARD
 #endif

#endif                                 /* DA1640X */

#endif                                 /* BSP_DEFAULTS_RA6W1_H_ */

/**
 * \}
 * \}
 */
