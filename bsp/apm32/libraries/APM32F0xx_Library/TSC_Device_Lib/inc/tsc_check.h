/*!
 * @file        tsc_check.h
 *
 * @brief       This file contains the check of all parameters defined in the
 *              common configuration file.
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
#ifndef __TOUCH_CHECK_H
#define __TOUCH_CHECK_H

/** @addtogroup TSC_Driver_Library TSC Driver Library
  @{
*/

/** @addtogroup TSC_Check_Driver TSC Check Driver
  @{
*/

/* Local check */
#if ((TOUCH_TOTAL_CHANNELS < 1) || (TOUCH_TOTAL_CHANNELS > 24))
    #error "TOUCH_TOTAL_CHANNELS can be (1 .. 24)."
#endif

#if ((TOUCH_TOTAL_BLOCKS < 1) || (TOUCH_TOTAL_BLOCKS > 8))
    #error "TOUCH_TOTAL_BLOCKS can be (1 .. 8)."
#endif

#if ((TOUCH_TOTAL_TOUCHKEYS < 0) || (TOUCH_TOTAL_TOUCHKEYS > 24))
    #error "TOUCH_TOTAL_TOUCHKEYS can be (0 .. 24)."
#endif

#if ((TOUCH_TOTAL_TOUCHKEYS_B < 0) || (TOUCH_TOTAL_TOUCHKEYS_B > 24))
    #error "TOUCH_TOTAL_TOUCHKEYS_B can be (0 .. 24)."
#endif

#if ((TOUCH_TOTAL_LINROTS < 0) || (TOUCH_TOTAL_LINROTS > 24))
    #error "TOUCH_TOTAL_LINROTS can be (0 .. 24)."
#endif

#if ((TOUCH_TOTAL_LINROTS_B < 0) || (TOUCH_TOTAL_LINROTS_B > 24))
    #error "TOUCH_TOTAL_LINROTS_B can be (0 .. 24)."
#endif

#if ((TOUCH_TOTAL_OBJECTS < 1) || (TOUCH_TOTAL_OBJECTS > 24))
    #error "TOUCH_TOTAL_OBJECTS can be (1 .. 24)."
#endif

#if ((TOUCH_TOTAL_KEYS + TOUCH_TOTAL_LNRTS) > 24)
    #error "The Sum of TouchKeys and Linear/Rotary sensors exceeds 24."
#endif

#ifndef TOUCH_TSC_GPIO_CONFIG
    #error "Please Config TOUCH_TSC_GPIO_CONFIG."
#endif

#if ((TOUCH_TSC_GPIO_CONFIG < 0) || (TOUCH_TSC_GPIO_CONFIG > 1))
    #error "TOUCH_TSC_GPIO_CONFIG can be (0 .. 1)."
#endif

#ifndef TOUCH_TSC_CTPHSEL
    #error "Please Config TOUCH_TSC_CTPHSEL."
#endif

#if ((TOUCH_TSC_CTPHSEL < 0) || (TOUCH_TSC_CTPHSEL > 15))
    #error "TOUCH_TSC_CTPHSEL can be (0 .. 15)."
#endif

#ifndef TOUCH_TSC_CTPLSEL
    #error "Please Config TOUCH_TSC_CTPLSEL."
#endif

#if ((TOUCH_TSC_CTPLSEL < 0) || (TOUCH_TSC_CTPLSEL > 15))
    #error "TOUCH_TSC_CTPLSEL can be (0 .. 15)."
#endif

#ifndef TOUCH_TSC_PGCDFSEL
    #error "Please Config TOUCH_TSC_PGCDFSEL."
#endif

#if ((TOUCH_TSC_PGCDFSEL < 0) || (TOUCH_TSC_PGCDFSEL > 7))
    #error "TOUCH_TSC_PGCDFSEL can be (0 .. 7)."
#endif

#if (TOUCH_ACQ_MAX > 0) && (TOUCH_ACQ_MAX < 256)
    #define TOUCH_TSC_MCNTVSEL 0 /*!< 255 */
#endif

#if (TOUCH_ACQ_MAX > 255) && (TOUCH_ACQ_MAX < 512)
    #define TOUCH_TSC_MCNTVSEL 1 /*!< 511 */
#endif

#if (TOUCH_ACQ_MAX > 511) && (TOUCH_ACQ_MAX < 1024)
    #define TOUCH_TSC_MCNTVSEL 2 /*!< 1023 */
#endif

#if (TOUCH_ACQ_MAX > 1023) && (TOUCH_ACQ_MAX < 2048)
    #define TOUCH_TSC_MCNTVSEL 3 /*!< 2047 */
#endif

#if (TOUCH_ACQ_MAX > 2047) && (TOUCH_ACQ_MAX < 4096)
    #define TOUCH_TSC_MCNTVSEL 4 /*!< 4095 */
#endif

#if (TOUCH_ACQ_MAX > 4095) && (TOUCH_ACQ_MAX < 8192)
    #define TOUCH_TSC_MCNTVSEL 5 /*!< 8191 */
#endif

#if (TOUCH_ACQ_MAX > 8191)
    #define TOUCH_TSC_MCNTVSEL 6 /*!< 16383 */
#endif

#ifndef TOUCH_TSC_MCNTVSEL
    #error "Please Config TOUCH_TSC_MCNTVSEL."
#endif

#if ((TOUCH_TSC_MCNTVSEL < 0) || (TOUCH_TSC_MCNTVSEL > 6))
    #error "TOUCH_TSC_MCNTVSEL can be (0 .. 6)."
#endif

#ifndef TOUCH_TSC_IODEF
    #error "Please Config TOUCH_TSC_IODEF."
#endif

#if ((TOUCH_TSC_IODEF < 0) || (TOUCH_TSC_IODEF > 1))
    #error "TOUCH_TSC_IODEF can be (0 .. 1)."
#endif

#ifndef TOUCH_TSC_AMCFG
    #error "Please Config TOUCH_TSC_AMCFG."
#endif

#if ((TOUCH_TSC_AMCFG < 0) || (TOUCH_TSC_AMCFG > 1))
    #error "TOUCH_TSC_AMCFG can be (0 .. 1)."
#endif

#ifndef TOUCH_TSC_SYNC_PIN
    #error "Please Config TOUCH_TSC_SYNC_PIN."
#endif

#if ((TOUCH_TSC_SYNC_PIN < 0) || (TOUCH_TSC_SYNC_PIN > 1))
    #error "TOUCH_TSC_SYNC_PIN can be (0 .. 1)."
#endif

#ifndef TOUCH_TSC_SYNC_POL
    #error "Please Config TOUCH_TSC_SYNC_POL."
#endif

#if ((TOUCH_TSC_SYNC_POL < 0) || (TOUCH_TSC_SYNC_POL > 1))
    #error "TOUCH_TSC_SYNC_POL can be (0 .. 1)."
#endif

#ifndef TOUCH_TSC_USE_SSEN
    #error "Please Config TOUCH_TSC_USE_SSEN."
#endif

#if ((TOUCH_TSC_USE_SSEN < 0) || (TOUCH_TSC_USE_SSEN > 1))
    #error "TOUCH_TSC_USE_SSEN can be (0 .. 1)."
#endif

#ifndef TOUCH_TSC_SSERRVSEL
    #error "Please Config TOUCH_TSC_SSERRVSEL."
#endif

#if ((TOUCH_TSC_SSERRVSEL < 0) || (TOUCH_TSC_SSERRVSEL > 127))
    #error "TOUCH_TSC_SSERRVSEL can be (0 .. 127)."
#endif

#ifndef TOUCH_TSC_SSCDFSEL
    #error "Please Config TOUCH_TSC_SSCDFSEL."
#endif

#if ((TOUCH_TSC_SSCDFSEL < 0) || (TOUCH_TSC_SSCDFSEL > 1))
    #error "TOUCH_TSC_SSCDFSEL can be (0 .. 1)."
#endif

#ifdef TSC_GROUP7_ENABLED
    #undef TSC_GROUP7_ENABLED
#endif

#if (TOUCH_TSC_GROUP7_IO1 != NU) || (TOUCH_TSC_GROUP7_IO2 != NU) || (TOUCH_TSC_GROUP7_IO3 != NU) || (TOUCH_TSC_GROUP7_IO4 != NU)
    #define TSC_GROUP7_ENABLED (1)
#endif

#ifdef TSC_GROUP8_ENABLED
    #undef TSC_GROUP8_ENABLED
#endif

#if (TOUCH_TSC_GROUP8_IO1 != NU) || (TOUCH_TSC_GROUP8_IO2 != NU) || (TOUCH_TSC_GROUP8_IO3 != NU) || (TOUCH_TSC_GROUP8_IO4 != NU)
    #define TSC_GROUP8_ENABLED (1)
#endif

#ifndef TOUCH_DELAY_DISCHARGE_ALL
    #error "Please Config TOUCH_DELAY_DISCHARGE_ALL."
#endif

#if ((TOUCH_DELAY_DISCHARGE_ALL < 0) || (TOUCH_DELAY_DISCHARGE_ALL > 65535))
    #error "TOUCH_DELAY_DISCHARGE_ALL can be (0 .. 65535)."
#endif

/* Global check */
#ifndef TOUCH_TOTAL_CHANNELS
    #error "Please Config TOUCH_TOTAL_CHANNELS."
#endif

#ifndef TOUCH_TOTAL_BLOCKS
    #error "Please Config TOUCH_TOTAL_BLOCKS."
#endif

#ifndef TOUCH_TOTAL_TOUCHKEYS
    #error "Please Config TOUCH_TOTAL_TOUCHKEYS."
#endif

#ifndef TOUCH_TOTAL_TOUCHKEYS_B
    #error "Please Config TOUCH_TOTAL_TOUCHKEYS_B."
#endif

#ifndef TOUCH_TOTAL_LINROTS
    #error "Please Config TOUCH_TOTAL_LINROTS."
#endif

#ifndef TOUCH_TOTAL_LINROTS_B
    #error "Please Config TOUCH_TOTAL_LINROTS_B."
#endif

#ifndef TOUCH_TOTAL_OBJECTS
    #error "Please Config TOUCH_TOTAL_OBJECTS."
#endif

#define TOUCH_TOTAL_KEYS (TOUCH_TOTAL_TOUCHKEYS + TOUCH_TOTAL_TOUCHKEYS_B)
#define TOUCH_TOTAL_LNRTS (TOUCH_TOTAL_LINROTS + TOUCH_TOTAL_LINROTS_B)

#if ((TOUCH_TOTAL_KEYS == 0) && (TOUCH_TOTAL_LNRTS == 0))
    #error "Please Config TouchKey and Linear/Rotary sensors."
#endif

#ifndef TOUCH_CALIB_SAMPLES
    #error "Please Config TOUCH_CALIB_SAMPLES."
#endif

#if ((TOUCH_CALIB_SAMPLES != 4) && (TOUCH_CALIB_SAMPLES != 8) && (TOUCH_CALIB_SAMPLES != 16))
    #error "TOUCH_CALIB_SAMPLES can be (4, 8, 16)."
#endif

#ifndef TOUCH_CALIB_DELAY
    #error "Please Config TOUCH_CALIB_DELAY."
#endif

#if ((TOUCH_CALIB_DELAY < 0) || (TOUCH_CALIB_DELAY > 40))
    #error "TOUCH_CALIB_DELAY can be (0..40)."
#endif

#ifndef TOUCH_ACQ_MIN
    #error "Please Config TOUCH_ACQ_MIN."
#endif

#ifndef TOUCH_ACQ_MAX
    #error "Please Config TOUCH_ACQ_MAX."
#endif

#if ((TOUCH_ACQ_MIN < 1) || (TOUCH_ACQ_MIN > (TOUCH_ACQ_MAX-1)))
    #error "TOUCH_ACQ_MIN can be (1 .. ACQ_MAX-1)."
#endif

#if ((TOUCH_ACQ_MAX < (TOUCH_ACQ_MIN+1)) || (TOUCH_ACQ_MAX > 50000))
    #error "TOUCH_ACQ_MAX can be (ACQ_MIN+1 .. 50000)."
#endif

#ifndef TOUCH_KEY_PROX_IN_TH
    #error "Please Config TOUCH_KEY_PROX_IN_TH."
#endif

#ifndef TOUCH_KEY_PROX_OUT_TH
    #error "Please Config TOUCH_KEY_PROX_OUT_TH."
#endif

#if ((TOUCH_KEY_PROX_OUT_TH < 0) || (TOUCH_KEY_PROX_OUT_TH > (TOUCH_KEY_PROX_IN_TH-1)))
    #error "TOUCH_KEY_PROX_OUT_TH can be (0 .. TOUCH_KEY_PROX_IN_TH-1)."
#endif

#if TOUCH_COEFF_TH == 0
    #if ((TOUCH_KEY_PROX_IN_TH < (TOUCH_KEY_PROX_OUT_TH+1)) || (TOUCH_KEY_PROX_IN_TH > (TOUCH_KEY_DETECT_OUT_TH-1)))
        #error "TOUCH_KEY_PROX_IN_TH can be (TOUCH_KEY_PROX_OUT_TH+1 .. TOUCH_KEY_DETECT_OUT_TH-1)."
    #endif
#endif

#ifndef TOUCH_LINROT_PROX_IN_TH
    #error "Please Config TOUCH_LINROT_PROX_IN_TH."
#endif

#ifndef TOUCH_LINROT_PROX_OUT_TH
    #error "Please Config TOUCH_LINROT_PROX_OUT_TH."
#endif

#if ((TOUCH_LINROT_PROX_OUT_TH < 0) || (TOUCH_LINROT_PROX_OUT_TH > (TOUCH_LINROT_PROX_IN_TH-1)))
    #error "TOUCH_LINROT_PROX_OUT_TH can be (0 .. TOUCH_LINROT_PROX_IN_TH-1)."
#endif

#if TOUCH_COEFF_TH == 0
    #if ((TOUCH_LINROT_PROX_IN_TH < (TOUCH_LINROT_PROX_OUT_TH+1)) || (TOUCH_LINROT_PROX_IN_TH > (TOUCH_LINROT_DETECT_OUT_TH-1)))
        #error "TOUCH_LINROT_PROX_IN_TH can be (TOUCH_LINROT_PROX_OUT_TH+1 .. TOUCH_LINROT_DETECT_OUT_TH-1)."
    #endif
#endif

#ifndef TOUCH_KEY_DETECT_IN_TH
    #error "Please Config TOUCH_KEY_DETECT_IN_TH."
#endif

#ifndef TOUCH_KEY_DETECT_OUT_TH
    #error "Please Config TOUCH_KEY_DETECT_OUT_TH."
#endif

#if TOUCH_COEFF_TH == 0
    #if ((TOUCH_KEY_DETECT_OUT_TH < (TOUCH_KEY_PROX_IN_TH+1)) || (TOUCH_KEY_DETECT_OUT_TH > (TOUCH_KEY_DETECT_IN_TH-1)))
        #error "TOUCH_KEY_DETECT_OUT_TH can be (TOUCH_KEY_PROX_IN_TH+1 .. TOUCH_KEY_DETECT_IN_TH-1)."
    #endif
#endif

#if ((TOUCH_KEY_DETECT_IN_TH < (TOUCH_KEY_DETECT_OUT_TH+1)) || (TOUCH_KEY_DETECT_IN_TH > 255))
    #error "TOUCH_KEY_DETECT_IN_TH can be (TOUCH_KEY_DETECT_OUT_TH+1 .. 255)."
#endif

#ifndef TOUCH_LINROT_DETECT_IN_TH
    #error "Please Config TOUCH_LINROT_DETECT_IN_TH."
#endif

#ifndef TOUCH_LINROT_DETECT_OUT_TH
    #error "Please Config TOUCH_LINROT_DETECT_OUT_TH."
#endif

#if TOUCH_COEFF_TH == 0
    #if ((TOUCH_LINROT_DETECT_OUT_TH < (TOUCH_LINROT_PROX_IN_TH+1)) || (TOUCH_LINROT_DETECT_OUT_TH > (TOUCH_LINROT_DETECT_IN_TH-1)))
        #error "TOUCH_LINROT_DETECT_OUT_TH can be (TOUCH_LINROT_PROX_IN_TH+1 .. TOUCH_LINROT_DETECT_IN_TH-1)."
    #endif
#endif

#if ((TOUCH_LINROT_DETECT_IN_TH < (TOUCH_LINROT_DETECT_OUT_TH+1)) || (TOUCH_LINROT_DETECT_IN_TH > 255))
    #error "TOUCH_LINROT_DETECT_IN_TH can be (TOUCH_LINROT_DETECT_OUT_TH+1 .. 255)."
#endif

#ifndef TOUCH_KEY_CALIB_TH
    #error "Please Config TOUCH_KEY_CALIB_TH."
#endif

#if ((TOUCH_KEY_CALIB_TH < 0) || (TOUCH_KEY_CALIB_TH > 255))
    #error "TOUCH_KEY_CALIB_TH can be (0 .. 255)."
#endif

#ifndef TOUCH_LINROT_CALIB_TH
    #error "Please Config TOUCH_LINROT_CALIB_TH."
#endif

#if ((TOUCH_LINROT_CALIB_TH < 0) || (TOUCH_LINROT_CALIB_TH > 255))
    #error "TOUCH_LINROT_CALIB_TH can be (0 .. 255)."
#endif

#ifndef TOUCH_LINROT_USE_NORMDELTA
    #error "Please Config TOUCH_LINROT_USE_NORMDELTA."
#endif

#if ((TOUCH_LINROT_USE_NORMDELTA < 0) || (TOUCH_LINROT_USE_NORMDELTA > 1))
    #error "TOUCH_LINROT_USE_NORMDELTA can be (0 .. 1)."
#endif

#ifndef TOUCH_COEFF_TH
    #error "Please Config TOUCH_COEFF_TH."
#endif

#if ((TOUCH_COEFF_TH < 0) || (TOUCH_COEFF_TH > 4))
    #error "TOUCH_COEFF_TH can be (0 .. 4)."
#endif

#ifndef TOUCH_LINROT_DIR_CHG_POS
    #error "Please Config TOUCH_LINROT_DIR_CHG_POS."
#endif

#if ((TOUCH_LINROT_DIR_CHG_POS < 0) || (TOUCH_LINROT_DIR_CHG_POS > 255))
    #error "TOUCH_LINROT_DIR_CHG_POS can be (0 .. 255)."
#endif

#ifndef TOUCH_LINROT_RESOLUTION
    #error "Please Config TOUCH_LINROT_RESOLUTION."
#endif

#if ((TOUCH_LINROT_RESOLUTION < 1) || (TOUCH_LINROT_RESOLUTION > 8))
    #error "TOUCH_LINROT_RESOLUTION can be (1 .. 8)."
#endif

#ifndef TOUCH_DEBOUNCE_PROX
    #error "Please Config TOUCH_DEBOUNCE_PROX."
#endif

#if ((TOUCH_DEBOUNCE_PROX < 0) || (TOUCH_DEBOUNCE_PROX > 63))
    #error "TOUCH_DEBOUNCE_PROX can be (0 .. 63)."
#endif

#ifndef TOUCH_DEBOUNCE_DETECT
    #error "Please Config TOUCH_DEBOUNCE_DETECT."
#endif

#if ((TOUCH_DEBOUNCE_DETECT < 0) || (TOUCH_DEBOUNCE_DETECT > 63))
    #error "TOUCH_DEBOUNCE_DETECT can be (0 .. 63)."
#endif

#ifndef TOUCH_DEBOUNCE_RELEASE
    #error "Please Config TOUCH_DEBOUNCE_RELEASE."
#endif

#if ((TOUCH_DEBOUNCE_RELEASE < 0) || (TOUCH_DEBOUNCE_RELEASE > 63))
    #error "TOUCH_DEBOUNCE_RELEASE can be (0 .. 63)."
#endif

#ifndef TOUCH_DEBOUNCE_CALIB
    #error "Please Config TOUCH_DEBOUNCE_CALIB."
#endif

#if ((TOUCH_DEBOUNCE_CALIB < 0) || (TOUCH_DEBOUNCE_CALIB > 63))
    #error "TOUCH_DEBOUNCE_CALIB can be (0 .. 63)."
#endif

#ifndef TOUCH_DEBOUNCE_ERROR
    #error "Please Config TOUCH_DEBOUNCE_ERROR."
#endif

#if ((TOUCH_DEBOUNCE_ERROR < 0) || (TOUCH_DEBOUNCE_ERROR > 63))
    #error "TOUCH_DEBOUNCE_ERROR can be (0 .. 63)."
#endif

#ifndef TOUCH_LINROT_DIR_CHG_DEB
    #error "Please Config TOUCH_LINROT_DIR_CHG_DEB."
#endif

#if ((TOUCH_LINROT_DIR_CHG_DEB < 0) || (TOUCH_LINROT_DIR_CHG_DEB > 63))
    #error "TOUCH_LINROT_DIR_CHG_DEB can be (0 .. 63)."
#endif

#ifndef TOUCH_ECS_K_DIFFER
    #error "Please Config TOUCH_ECS_K_DIFFER."
#endif

#if ((TOUCH_ECS_K_DIFFER < 0) || (TOUCH_ECS_K_DIFFER > 255))
    #error "TOUCH_ECS_K_DIFFER can be (0 .. 255)."
#endif

#ifndef TOUCH_ECS_K_SAME
    #error "Please Config TOUCH_ECS_K_SAME."
#endif

#if ((TOUCH_ECS_K_SAME < 0) || (TOUCH_ECS_K_SAME > 255))
    #error "TOUCH_ECS_K_SAME can be (0 .. 255)."
#endif

#ifndef TOUCH_ECS_DELAY
    #error "Please Config TOUCH_ECS_DELAY."
#endif

#if ((TOUCH_ECS_DELAY < 0) || (TOUCH_ECS_DELAY > 5000))
    #error "TOUCH_ECS_DELAY can be (0 .. 5000)."
#endif

#ifndef TOUCH_USE_MEAS
    #error "Please Config TOUCH_USE_MEAS."
#endif

#if ((TOUCH_USE_MEAS != 0) && (TOUCH_USE_MEAS != 1))
    #error "TOUCH_USE_MEAS can be (0 .. 1)."
#endif

#ifndef TOUCH_USE_PROX
    #error "Please Config TOUCH_USE_PROX."
#endif

#if ((TOUCH_USE_PROX != 0) && (TOUCH_USE_PROX != 1))
    #error "TOUCH_USE_PROX can be (0 .. 1)."
#endif

#ifndef TOUCH_USE_ZONE
    #error "Please Config TOUCH_USE_ZONE."
#endif

#if ((TOUCH_USE_ZONE != 0) && (TOUCH_USE_ZONE != 1))
    #error "TOUCH_USE_ZONE can be (0 .. 1)."
#endif

#ifndef TOUCH_USE_ACQ_INTERRUPT
    #error "Please Config TOUCH_USE_ACQ_INTERRUPT."
#endif

#if ((TOUCH_USE_ACQ_INTERRUPT != 0) && (TOUCH_USE_ACQ_INTERRUPT != 1))
    #error "TOUCH_USE_ACQ_INTERRUPT can be (0 .. 1)."
#endif

#ifndef TOUCH_DTO
    #error "Please Config TOUCH_DTO."
#endif

#if ((TOUCH_DTO < 0) || (TOUCH_DTO > 63))
    #error "TOUCH_DTO can be (0 .. 63)."
#endif

#ifndef TOUCH_TICK_FREQ
    #error "Please Config TOUCH_TICK_FREQ."
#endif

#if ((TOUCH_TICK_FREQ != 125) && (TOUCH_TICK_FREQ != 250) && (TOUCH_TICK_FREQ != 500) &&\
     (TOUCH_TICK_FREQ != 1000) && (TOUCH_TICK_FREQ != 2000))
#error "TOUCH_TICK_FREQ can be (125, 250, 500, 1000, 2000)."
#endif

#ifndef TOUCH_USE_DXS
    #error "Please Config TOUCH_USE_DXS."
#endif

#if ((TOUCH_USE_DXS < 0) || (TOUCH_USE_DXS > 1))
    #error "TOUCH_USE_DXS can be (0 .. 1)."
#endif

#ifndef TOUCH_USE_TIMER_CALLBACK
    #error "Please Config TOUCH_USE_TIMER_CALLBACK."
#endif

#if ((TOUCH_USE_TIMER_CALLBACK != 0) && (TOUCH_USE_TIMER_CALLBACK != 1))
    #error "TOUCH_USE_TIMER_CALLBACK can be (0 .. 1)."
#endif

#endif /* __TOUCH_CHECK_H */

/** @defgroup TSC_Check_Macros Macros
  @{
  */

/**@} end of group TSC_Check_Macros */

/** @defgroup TSC_Check_Enumerations Enumerations
  @{
  */

/**@} end of group TSC_Check_Enumerations */

/** @defgroup TSC_Check_Structures Structures
  @{
  */

/**@} end of group TSC_Check_Structures */

/** @defgroup TSC_Check_Variables Variables
  @{
  */

/**@} end of group TSC_Check_Variables */

/** @defgroup TSC_Check_Functions Functions
  @{
  */

/**@} end of group TSC_Check_Functions */

/**@} end of group TSC_Check_Driver */
/**@} end of group TSC_Driver_Library */
