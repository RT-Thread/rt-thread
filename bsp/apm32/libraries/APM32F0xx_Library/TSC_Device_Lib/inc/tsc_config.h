/*!
 * @file        tsc_config.h
 *
 * @brief       Acquisition parameters for APM32F0xx products.
 *
 * @version     V1.0.1
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __TSC_CONFIG_H
#define __TSC_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup TSC_Driver_Library TSC Driver Library
  @{
*/

/** @addtogroup TSC_Config_Driver TSC Config Driver
  @{
*/

/** @defgroup TSC_Config_Macros Macros
  @{
*/

/** @defgroup Common_Parameters_Number_Of_Elements
  @{
*/

/* The number of channels (1..24) */
#define TOUCH_TOTAL_CHANNELS (11)

/* The number of blocks (1..8) */
#define TOUCH_TOTAL_BLOCKS (3)

/* The number of "Extended" TouchKeys (0..24) */
#define TOUCH_TOTAL_TOUCHKEYS (5)

/* The number of "Basic" TouchKeys (0..24) */
#define TOUCH_TOTAL_TOUCHKEYS_B (0)

/* The number of "Extended" Linear and Rotary sensors (0..24) */
#define TOUCH_TOTAL_LINROTS (2)

/* The number of "Basic" Linear and Rotary sensors (0..24) */
#define TOUCH_TOTAL_LINROTS_B (0)

/** The number of sensors/objects (1..24)
 *  - Count all TouchKeys, Linear and Rotary sensors
 */
#define TOUCH_TOTAL_OBJECTS (7)

/**@} Common_Parameters_Number_Of_Elements */

/** @defgroup Common_Parameters_Optional_Features
  @{
*/

/** Record the last measure (0=No, 1=Yes)
 *  - If No the measure is recalculated using the Reference and Delta
 */
#define TOUCH_USE_MEAS (1)

/* Zone management usage (0=No, 1=Yes) */
#define TOUCH_USE_ZONE (0)

/* Proximity detection usage (0=No, 1=Yes) */
#define TOUCH_USE_PROX (1)

/** Use the Timer tick callback (0=No, 1=Yes)
 *  - When equal to 1, the function TSC_CallBack_TimerTick
 */
#define TOUCH_USE_TIMER_CALLBACK (0)

/** Acquisition interrupt mode (0=No, 1=Yes)
 *  - If No the TSC interrupt is not used.
 *  - If Yes the TSC interrupt is used.
 */
#define TOUCH_USE_ACQ_INTERRUPT (0)

/**@} Common_Parameters_Optional_Features */

/** @defgroup Common_Parameters_Acquisition_limits
  @{
*/

/** Minimum acquisition measurement (0..65535)
 *  - This is the minimum acceptable value for the acquisition measure.
 *  - The acquisition will be in error if the measure is below this value.
 */
#define TOUCH_ACQ_MIN (10)

/** Maximum acquisition measurement (255, 511, 1023, 2047, 8191, 16383)
 *  - This is the maximum acceptable value for the acquisition measure.
 *  - The acquisition will be in error if the measure is above this value.
 */
#define TOUCH_ACQ_MAX (8191)

/**@} Common_Parameters_Acquisition_limits */

/** @defgroup Common_Parameters_Calibration
  @{
*/
/** Number of calibration samples (4, 8, 16)
 *  - Low value = faster calibration but less precision.
 *  - High value = slower calibration but more precision.
 */
#define TOUCH_CALIB_SAMPLES (16)

/** Delay in measurement samples before starting the calibration (0..40)
 *  - This is useful if a noise filter is used.
 *  - Write 0 to disable the delay.
 */
#define TOUCH_CALIB_DELAY (0)

/**@} Common_Parameters_Calibration */

/** @defgroup Common_Parameters_Thresholds_for_TouchKey
  @{
*/

/** TouchKeys Proximity state input threshold (0..255)
 *  - Enter Proximity state if delta is above
 */
#define TOUCH_KEY_PROX_IN_TH (10)

/** TouchKeys Proximity state output threshold (0..255)
 *  - Exit Proximity state if delta is below
 */
#define TOUCH_KEY_PROX_OUT_TH (5)

/** TouchKeys Detect state input threshold (0..255)
 *  - Enter Detect state if delta is above
 */
#define TOUCH_KEY_DETECT_IN_TH (200)

/** TouchKeys Detect state output threshold (0..255)
 *  - Exit Detect state if delta is below
 */
#define TOUCH_KEY_DETECT_OUT_TH (150)

/** TouchKeys re-Calibration threshold (0..255)
 *  - @warning The value is inverted in the sensor state machine
 *  - Enter Calibration state if delta is below
 */
#define TOUCH_KEY_CALIB_TH (150)

/** TouchKey, Linear and Rotary sensors thresholds coefficient (0..4)
 *  This multiplier coefficient is applied on Detect and Re-Calibration thresholds only.
 *  - 0: disabled
 *  - 1: thresholds x 2
 *  - 2: thresholds x 4
 *  - 3: thresholds x 8
 *  - 4: thresholds x 16
 */
#define TOUCH_COEFF_TH (0)

/**@} Common_Parameters_Thresholds_for_TouchKey */

/** @defgroup Common_Parameters_Thresholds_For_Linear_Rotary
  @{
*/

/** Linear/Rotary Proximity state input threshold (0..255)
 *  - Enter Proximity state if delta is above
 */
#define TOUCH_LINROT_PROX_IN_TH (10)

/** Linear/Rotary Proximity state output threshold (0..255)
 * - Exit Proximity state if delta is below
 */
#define TOUCH_LINROT_PROX_OUT_TH (5)

/** Linear/Rotary Detect state input threshold (0..255)
 *  - Enter Detect state if delta is above
 */
#define TOUCH_LINROT_DETECT_IN_TH (20)

/** Linear/Rotary Detect state output threshold (0..255)
 *  - Exit Detect state if delta is below
 */
#define TOUCH_LINROT_DETECT_OUT_TH (15)

/** Linear/Rotary Re-Calibration threshold (0..255)
 *  - @warning The value is inverted in the sensor state machine
 *  - Enter Calibration state if delta is below
 */
#define TOUCH_LINROT_CALIB_TH (30)

/** Linear/Rotary Delta normalization (0=No, 1=Yes)
 * - When this parameter is set, a coefficient is applied on all Delta of all sensors
 *   in order to normalize them and to improve the position calculation.
 * - These coefficients must be defined in a constant table
 * - The MSB is the coefficient integer part, the LSB is the coefficient real part.
 *  Examples:
 * - To apply a factor 1.10:
 *   0x01 to the MSB
 *   0x1A to the LSB (0.10 x 256 = 25.6 -> rounded to 26 = 0x1A)
 * - To apply a factor 0.90:
 *   0x00 to the MSB
 *   0xE6 to the LSB (0.90 x 256 = 230.4 -> rounded to 230 = 0xE6)
 */
#define TOUCH_LINROT_USE_NORMDELTA (0)

/**@} Common_Parameters_Thresholds_For_Linear_Rotary */

/** @defgroup Common_Parameters_Used_Linear_Rotary
  @{
*/

/** Select which Linear and Rotary sensors you use in your application.
 *  - 0 = Not Used
 *  - 1 = Used
 *
 *  LIN = Linear sensor
 *  ROT = Rotary sensor
 *  M1 = Mono electrodes design with 0/255 position at extremities of the sensor
 *  M2 = Mono electrodes design
 *  H = Half-ended electrodes design
 *  D = Dual electrodes design
 */
#define TOUCH_USE_3CH_LIN_M1 (1)
#define TOUCH_USE_3CH_LIN_M2 (1)
#define TOUCH_USE_3CH_LIN_H  (1)
#define TOUCH_USE_3CH_ROT_M  (1)

#define TOUCH_USE_4CH_LIN_M1 (1)
#define TOUCH_USE_4CH_LIN_M2 (1)
#define TOUCH_USE_4CH_LIN_H  (1)
#define TOUCH_USE_4CH_ROT_M  (1)

#define TOUCH_USE_5CH_LIN_M1 (1)
#define TOUCH_USE_5CH_LIN_M2 (1)
#define TOUCH_USE_5CH_LIN_H  (1)
#define TOUCH_USE_5CH_ROT_M  (1)
#define TOUCH_USE_5CH_ROT_D  (1)

#define TOUCH_USE_6CH_LIN_M1 (1)
#define TOUCH_USE_6CH_LIN_M2 (1)
#define TOUCH_USE_6CH_LIN_H  (1)
#define TOUCH_USE_6CH_ROT_M  (1)

/**@} Common_Parameters_Used_Linear_Rotary */

/** @defgroup Common_Parameters_Position_Linear_Rotary
  @{
*/

/** Position resolution in number of bits (1..8)
 *  - A Low value will result in a low resolution and will be less subject to noise.
 *  - A High value will result in a high resolution and will be more subject to noise.
 */
#define TOUCH_LINROT_RESOLUTION (7)

/** Direction change threshold in position unit (0..255)
 *  - Defines the default threshold used during the change direction process.
 *  - A Low value will result in a faster direction change.
 *  - A High value will result in a slower direction change.
 */
#define TOUCH_LINROT_DIR_CHG_POS (10)

/** Direction change debounce (0..63)
 *  - Defines the default integrator counter used during the change direction process.
 *  - This counter is decremented when the same change in the position is detected and the direction will
 *    change after this counter reaches zero.
 *  - A Low value will result in a faster direction change.
 *  - A High value will result in a slower direction change.
 */
#define TOUCH_LINROT_DIR_CHG_DEB (1)

/**@} Common_Parameters_Position_Linear_Rotary */

/** @defgroup Common_Parameters_Debounce_Counters
  @{
*/

/** Proximity state debounce in samples unit (0..63)
 *  - A Low value will result in a higher sensitivity during the Proximity detection but with less noise filtering.
 *  - A High value will result in improving the system noise immunity but will increase the system response time.
 */
#define TOUCH_DEBOUNCE_PROX (3)

/** Detect state debounce in samples unit (0..63)
 *  - A Low value will result in a higher sensitivity during the detection but with less noise filtering.
 *  - A High value will result in improving the system noise immunity but will increase the system response time.
 */
#define TOUCH_DEBOUNCE_DETECT (3)

/** Release state debounce in samples unit (0..63)
 *  - A Low value will result in a higher sensitivity during the end-detection but with less noise filtering.
 *  - A High value will result in a lower sensitivity during the end-detection but with more noise filtering.
 */
#define TOUCH_DEBOUNCE_RELEASE (3)

/** Re-calibration state debounce in samples unit (0..63)
 *  - A Low value will result in a higher sensitivity during the recalibration but with less noise filtering.
 *  - A High value will result in a lower sensitivity during the recalibration but with more noise filtering.
 */
#define TOUCH_DEBOUNCE_CALIB (3)

/** Error state debounce in samples unit (0..63)
 *  - A Low value will result in a higher sensitivity to enter in error state.
 *  - A High value will result in a lower sensitivity to enter in error state.
 */
#define TOUCH_DEBOUNCE_ERROR (3)

/**@} Common_Parameters_Debounce_Counters */

/** @defgroup Common_Parameters_Environment_Change_System (ECS)
  @{
*/

/** Environment Change System Different K factor (0..255)
 *  - The higher value is K, the faster is the response time.
 */
#define TOUCH_ECS_K_DIFFER (10)

/** Environment Change System Same K factor (0..255)
 *  - The higher value is K, the faster is the response time.
 */
#define TOUCH_ECS_K_SAME (20)

/** Environment Change System delay in msec (0..5000)
 *  - The ECS will be started after this delay and when all sensors are in Release state.
 */
#define TOUCH_ECS_DELAY (500)

/**@} Common_Parameters_Environment_Change_System */

/** @defgroup Common_Parameters_Detection_Time_Out (DTO)
  @{
*/

/** Detection Time Out delay in seconds (0..63)
 *  - Value 0: DTO processing not compiled in the code (to gain size if not used).
 *  - Value 1: Default time out infinite.
 *  - Value between 2 and 63: Default time out between value n-1 and n.
 *  - Examples:
 *      - With a DTO equal to 2, the time out is between 1s and 2s.
 *      - With a DTO equal to 63, the time out is between 62s and 63s.
 *
 *@note The DTO can be changed in run-time by the application only if the
 *      default value is between 1 and 63.
 */
#define TOUCH_DTO (0)

/**@} Common_Parameters_Detection_Time_Out */

/** @defgroup Common_Parameters_Detection_Exclusion_System (DXS)
  @{
*/

/** Detection Exclusion System (0=No, 1=Yes) */
#define TOUCH_USE_DXS (0)

/**@} Common_Parameters_Detection_Exclusion_System */

/** @defgroup Common_Parameters_Miscellaneous_Parameters
  @{
*/

/** Timing tick frequency in Hz (125, 250, 500, 1000, 2000)
 *  - Result to a timing interrupt respectively every 8ms, 4ms, 2ms, 1ms, 0.5ms
 */
#define TOUCH_TICK_FREQ (1000)

/** Delay for discharging Cx and Cs capacitors (0..65535)
 *  - The value corresponds to the Softdelay function parameter.
 *  -  500 gives around  53 delay whatever HCLK
 *  - 1000 gives around 106 delay whatever HCLK
 *  - 2000 gives around 210 delay whatever HCLK
 */
#define TOUCH_DELAY_DISCHARGE_ALL (1000)

/**@} Common_Parameters_Miscellaneous_Parameters */

/** @defgroup APM32F0xx_Parameters_GPIOs_Configuration
  @{
*/

/** TSC GPIOs Configuration selection (0..1)
 *  - 0: Manual. The TSC GPIOs configuration must be done by the application code.
 *  - 1: Automatic. The TOUCH_TSC_GROUPx_IOy parameters below must be filled up.
 *  The TSC GPIOs configuration is automatically done by the Touch driver.
 */
#define TOUCH_TSC_GPIO_CONFIG (1)

/* DO NOT CHANGE THESE VALUES */
/* These defines must be applied to the TOUCH_TSC_GROUPx_IOy parameters below */
#define NU      (0) /*!< Not Used IO */
#define CHANNEL (1) /*!< Channel IO */
#define SHIELD  (2) /*!< Shield IO (= Channel IO but not acquired) */
#define SAMPCAP (3) /*!< Sampling Capacitor IO */

/* If TOUCH_TSC_GPIO_CONFIG=0 these parameters are ignored */
/* If TOUCH_TSC_GPIO_CONFIG=1 assign each TOUCH_TSC_GROUPx_IOy parameters below */

#define TOUCH_TSC_GROUP1_IO1  SAMPCAP       /*!< PA0 */
#define TOUCH_TSC_GROUP1_IO2  CHANNEL       /*!< PA1 */
#define TOUCH_TSC_GROUP1_IO3  CHANNEL       /*!< PA2 */
#define TOUCH_TSC_GROUP1_IO4  NU            /*!< PA3 */

#define TOUCH_TSC_GROUP2_IO1  SAMPCAP       /*!< PA4 */
#define TOUCH_TSC_GROUP2_IO2  CHANNEL       /*!< PA5 */
#define TOUCH_TSC_GROUP2_IO3  CHANNEL       /*!< PA6 */
#define TOUCH_TSC_GROUP2_IO4  CHANNEL       /*!< PA7 */

#define TOUCH_TSC_GROUP3_IO1  SAMPCAP       /*!< PC5 */
#define TOUCH_TSC_GROUP3_IO2  NU            /*!< PB0 */
#define TOUCH_TSC_GROUP3_IO3  CHANNEL       /*!< PB1 */
#define TOUCH_TSC_GROUP3_IO4  CHANNEL       /*!< PB2 */

#define TOUCH_TSC_GROUP4_IO1  SAMPCAP       /*!< PA9 */
#define TOUCH_TSC_GROUP4_IO2  NU            /*!< PA10 */
#define TOUCH_TSC_GROUP4_IO3  CHANNEL       /*!< PA11 */
#define TOUCH_TSC_GROUP4_IO4  CHANNEL       /*!< PA12 */

#define TOUCH_TSC_GROUP5_IO1  NU            /*!< PB3 */
#define TOUCH_TSC_GROUP5_IO2  NU            /*!< PB4 */
#define TOUCH_TSC_GROUP5_IO3  NU            /*!< PB6 */
#define TOUCH_TSC_GROUP5_IO4  NU            /*!< PB7 */

#define TOUCH_TSC_GROUP6_IO1  SAMPCAP       /*!< PB11 */
#define TOUCH_TSC_GROUP6_IO2  NU            /*!< PB12 */
#define TOUCH_TSC_GROUP6_IO3  CHANNEL       /*!< PB13 */
#define TOUCH_TSC_GROUP6_IO4  CHANNEL       /*!< PB14 */

/* Warning: this group is available on some devices only */
#define TOUCH_TSC_GROUP7_IO1  NU       /*!< PE2 */
#define TOUCH_TSC_GROUP7_IO2  NU       /*!< PE3 */
#define TOUCH_TSC_GROUP7_IO3  NU       /*!< PE4 */
#define TOUCH_TSC_GROUP7_IO4  NU       /*!< PE5 */

/* Warning: this group is available on some devices only */
#define TOUCH_TSC_GROUP8_IO1  NU       /*!< PD12 */
#define TOUCH_TSC_GROUP8_IO2  NU       /*!< PD13 */
#define TOUCH_TSC_GROUP8_IO3  NU       /*!< PD14 */
#define TOUCH_TSC_GROUP8_IO4  NU       /*!< PD15 */

/**@} APM32F0xx_Parameters_GPIOs_Configuration */

/** @defgroup APM32F0xx_Parameters_Charge_Transfer_Pulses
  @{
*/

/** Charge Transfer Pulse High (0..15)
 *  - 0: 1 x tPGCLK
 *  - 1: 2 x tPGCLK
 *  - ...
 *  - 15: 16 x tPGCLK
 */
#define TOUCH_TSC_CTPHSEL (1)

/** Charge Transfer Pulse Low (0..15)
 *  - 0: 1 x tPGCLK
 *  - 1: 2 x tPGCLK
 *  - ...
 *  - 15: 16 x tPGCLK
 */
#define TOUCH_TSC_CTPLSEL (1)

/** Pulse Generator Clock Divide Factor Select (0..7)
 *  - 0: fPGCLK = fHCLK
 *  - 1: fPGCLK = fHCLK/2
 *  - ...
 *  - 7: fPGCLK = fHCLK/128
 */
#define TOUCH_TSC_PGCDFSEL (3)

/**@} APM32F0xx_Parameters_Charge_Transfer_Pulses */

/** @defgroup APM32F0xx_Parameters_GPIOs
  @{
*/

/** TSC IOs default mode when no on-going acquisition (0..1)
 *    - 0: Output push-pull low
 *    - 1: Input floating
 * @note To ensure a correct operation in noisy environment, this parameter should
 * be configured to output push-pull low.
 */
#define TOUCH_TSC_IODEF (0)

/** Acquisition Mode (0..1)
 *  - 0: Normal acquisition mode
 *  - 1: Synchronized acquisition mode
 */
#define TOUCH_TSC_AMCFG (0)

/** Synchronization Pin (0..1)
 *  - 0: PB8
 *  - 1: PB10
 */
#define TOUCH_TSC_SYNC_PIN (0)

/** Synchronization Polarity (0..1)
 *  - 0: Falling edge only
 *  - 1: Rising edge and high level
 */
#define TOUCH_TSC_SYNC_POL (0)

/**@} APM32F0xx_Parameters_GPIOs */

/** @addtogroup APM32F0xx_Parameters_Spread_Spectrum
  @{
*/

/* Use Spread Spectrum (0=No, 1=Yes) */
#define TOUCH_TSC_USE_SSEN (0)

/** Spread Spectrum Error Value Select (0..127)
 *  - 0: 1 x tSSCLK
 *  - 1: 2 x tSSCLK
 *  - ...
 *  - 127: 128 x tSSCLK
 */
#define TOUCH_TSC_SSERRVSEL (0)

/** Spread Spectrum Clock Divide Factor Select (0..1)
 *  - 0: fSSCLK = fHCLK
 *  - 1: fSSCLK = fHCLK/2
 */
#define TOUCH_TSC_SSCDFSEL (0)

/**@} APM32F0xx_Parameters_Spread_Spectrum */

/* Includes */
/* Must be placed last */
#include "tsc_check.h"

#ifdef __cplusplus
}
#endif

#endif /* __TSC_CONFIG_H */

/**@} end of group TSC_Config_Macros */

/** @defgroup TSC_Config_Enumerations Enumerations
  @{
*/

/**@} end of group TSC_Config_Enumerations */

/** @defgroup TSC_Config_Structures Structures
  @{
*/

/**@} end of group TSC_Config_Structures */

/** @defgroup TSC_Config_Variables Variables
  @{
*/

/**@} end of group TSC_Config_Variables */

/** @defgroup TSC_Config_Functions Functions
  @{
*/

/**@} end of group TSC_Config_Functions */
/**@} end of group TSC_Config_Driver */
/**@} end of group TSC_Driver_Library */
