/*!
 * @file        tsc_acq.c
 *
 * @brief       This file contains all functions to manage the acquisition in general.
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

/* Includes */
#include "tsc.h"
#include "tsc_acq.h"
#include "apm32f0xx_int.h"

/** @addtogroup TSC_Driver_Library TSC Driver Library
  @{
*/

/** @addtogroup TSC_Acquisition_Driver TSC Acquisition Driver
  @{
*/

/** @defgroup TSC_Acquisition_Macros Macros
  @{
*/

/**@} end of group TSC_Acquisition_Macros */

/** @defgroup TSC_Acquisition_Enumerations Enumerations
  @{
*/

/**@} end of group TSC_Acquisition_Enumerations */

/** @defgroup TSC_Acquisition_Structures Structures
  @{
*/

/**@} end of group TSC_Acquisition_Structures */

/** @defgroup TSC_Acquisition_Variables Variables
  @{
*/

uint32_t DelayDischarge;

/**@} end of group TSC_Acquisition_Variables */

/** @defgroup TSC_Acquisition_Functions Functions
  @{
*/

void SoftDelay(uint32_t val);

/*!
 * @brief       Output Open-Drain for Sampling Capacitor in GPIOA
 *
 * @param       None
 *
 * @retval      pin value
 */
uint32_t TSC_Acq_GPIOA_SAMPCAP(void)
{
    uint32_t pin = 0;
#if TOUCH_TSC_GROUP1_IO1 == SAMPCAP
    pin |= GPIO_PIN_0;
#endif
#if TOUCH_TSC_GROUP1_IO2 == SAMPCAP
    pin |= GPIO_PIN_1;
#endif
#if TOUCH_TSC_GROUP1_IO3 == SAMPCAP
    pin |= GPIO_PIN_2;
#endif
#if TOUCH_TSC_GROUP1_IO4 == SAMPCAP
    pin |= GPIO_PIN_3;
#endif
#if TOUCH_TSC_GROUP2_IO1 == SAMPCAP
    pin |= GPIO_PIN_4;
#endif
#if TOUCH_TSC_GROUP2_IO2 == SAMPCAP
    pin |= GPIO_PIN_5;
#endif
#if TOUCH_TSC_GROUP2_IO3 == SAMPCAP
    pin |= GPIO_PIN_6;
#endif
#if TOUCH_TSC_GROUP2_IO4 == SAMPCAP
    pin |= GPIO_PIN_7;
#endif
#if TOUCH_TSC_GROUP4_IO1 == SAMPCAP
    pin |= GPIO_PIN_9;
#endif
#if TOUCH_TSC_GROUP4_IO2 == SAMPCAP
    pin |= GPIO_PIN_10;
#endif
#if TOUCH_TSC_GROUP4_IO3 == SAMPCAP
    pin |= GPIO_PIN_11;
#endif
#if TOUCH_TSC_GROUP4_IO4 == SAMPCAP
    pin |= GPIO_PIN_12;
#endif
    return pin;
}

/*!
 * @brief       Output Open-Drain for Sampling Capacitor in GPIOB
 *
 * @param       None
 *
 * @retval      pin value
 */
uint32_t TSC_Acq_GPIOB_SAMPCAP(void)
{
    uint32_t pin = 0;
#if TOUCH_TSC_GROUP3_IO2 == SAMPCAP
    pin |= GPIO_PIN_0;
#endif
#if TOUCH_TSC_GROUP3_IO3 == SAMPCAP
    pin |= GPIO_PIN_1;
#endif
#if TOUCH_TSC_GROUP3_IO4 == SAMPCAP
    pin |= GPIO_PIN_2;
#endif
#if TOUCH_TSC_GROUP5_IO1 == SAMPCAP
    pin |= GPIO_PIN_3;
#endif
#if TOUCH_TSC_GROUP5_IO2 == SAMPCAP
    pin |= GPIO_PIN_4;
#endif
#if TOUCH_TSC_GROUP5_IO3 == SAMPCAP
    pin |= GPIO_PIN_6;
#endif
#if TOUCH_TSC_GROUP5_IO4 == SAMPCAP
    pin |= GPIO_PIN_7;
#endif
#if TOUCH_TSC_GROUP6_IO1 == SAMPCAP
    pin |= GPIO_PIN_11;
#endif
#if TOUCH_TSC_GROUP6_IO2 == SAMPCAP
    pin |= GPIO_PIN_12;
#endif
#if TOUCH_TSC_GROUP6_IO3 == SAMPCAP
    pin |= GPIO_PIN_13;
#endif
#if TOUCH_TSC_GROUP6_IO4 == SAMPCAP
    pin |= GPIO_PIN_14;
#endif
    return pin;
}

/*!
 * @brief       Output Open-Drain for Sampling Capacitor in GPIOC
 *
 * @param       None
 *
 * @retval      pin value
 */
uint32_t TSC_Acq_GPIOC_SAMPCAP(void)
{
    uint32_t pin = 0;
#if TOUCH_TSC_GROUP3_IO1 == SAMPCAP
    pin |= GPIO_PIN_5;
#endif
    return pin;
}

/*!
 * @brief       Output Open-Drain for Sampling Capacitor in GPIOD
 *
 * @param       None
 *
 * @retval      pin value
 */
#if (TSC_GROUP8_ENABLED > 0)
uint32_t TSC_Acq_GPIOD_SAMPCAP(void)
{
    uint32_t pin = 0;
#if TOUCH_TSC_GROUP8_IO1 == SAMPCAP
    pin |= GPIO_PIN_12;
#endif
#if TOUCH_TSC_GROUP8_IO2 == SAMPCAP
    pin |= GPIO_PIN_13;
#endif
#if TOUCH_TSC_GROUP8_IO3 == SAMPCAP
    pin |= GPIO_PIN_14;
#endif
#if TOUCH_TSC_GROUP8_IO4 == SAMPCAP
    pin |= GPIO_PIN_15;
#endif
    return pin;
}
#endif

/*!
 * @brief       Output Open-Drain for Sampling Capacitor in GPIOE
 *
 * @param       None
 *
 * @retval      pin value
 */
#if (TSC_GROUP7_ENABLED > 0)
uint32_t TSC_Acq_GPIOE_SAMPCAP(void)
{
    pin = 0;
#if TOUCH_TSC_GROUP7_IO1 == SAMPCAP
    pin |= GPIO_PIN_2;
#endif
#if TOUCH_TSC_GROUP7_IO2 == SAMPCAP
    pin |= GPIO_PIN_3;
#endif
#if TOUCH_TSC_GROUP7_IO3 == SAMPCAP
    pin |= GPIO_PIN_4;
#endif
#if TOUCH_TSC_GROUP7_IO4 == SAMPCAP
    pin |= GPIO_PIN_5;
#endif
    return pin;
}
#endif

/*!
 * @brief       Output Push-Pull for Channel and Shield GPIOA
 *
 * @param       None
 *
 * @retval      pin value
 */
uint32_t TSC_Acq_GPIOA_CHANNEL_SHIELD(void)
{
    uint32_t pin = 0;
#if (TOUCH_TSC_GROUP1_IO1 == CHANNEL) || (TOUCH_TSC_GROUP1_IO1 == SHIELD)
    pin |= GPIO_PIN_0;
#endif
#if (TOUCH_TSC_GROUP1_IO2 == CHANNEL) || (TOUCH_TSC_GROUP1_IO2 == SHIELD)
    pin |= GPIO_PIN_1;
#endif
#if (TOUCH_TSC_GROUP1_IO3 == CHANNEL) || (TOUCH_TSC_GROUP1_IO3 == SHIELD)
    pin |= GPIO_PIN_2;
#endif
#if (TOUCH_TSC_GROUP1_IO4 == CHANNEL) || (TOUCH_TSC_GROUP1_IO4 == SHIELD)
    pin |= GPIO_PIN_3;
#endif
#if (TOUCH_TSC_GROUP2_IO1 == CHANNEL) || (TOUCH_TSC_GROUP2_IO1 == SHIELD)
    pin |= GPIO_PIN_4;
#endif
#if (TOUCH_TSC_GROUP2_IO2 == CHANNEL) || (TOUCH_TSC_GROUP2_IO2 == SHIELD)
    pin |= GPIO_PIN_5;
#endif
#if (TOUCH_TSC_GROUP2_IO3 == CHANNEL) || (TOUCH_TSC_GROUP2_IO3 == SHIELD)
    pin |= GPIO_PIN_6;
#endif
#if (TOUCH_TSC_GROUP2_IO4 == CHANNEL) || (TOUCH_TSC_GROUP2_IO4 == SHIELD)
    pin |= GPIO_PIN_7;
#endif
#if (TOUCH_TSC_GROUP4_IO1 == CHANNEL) || (TOUCH_TSC_GROUP4_IO1 == SHIELD)
    pin |= GPIO_PIN_9;
#endif
#if (TOUCH_TSC_GROUP4_IO2 == CHANNEL) || (TOUCH_TSC_GROUP4_IO2 == SHIELD)
    pin |= GPIO_PIN_10;
#endif
#if (TOUCH_TSC_GROUP4_IO3 == CHANNEL) || (TOUCH_TSC_GROUP4_IO3 == SHIELD)
    pin |= GPIO_PIN_11;
#endif
#if (TOUCH_TSC_GROUP4_IO4 == CHANNEL) || (TOUCH_TSC_GROUP4_IO4 == SHIELD)
    pin |= GPIO_PIN_12;
#endif
    return pin;
}

/*!
 * @brief       Output Push-Pull for Channel and Shield GPIOB
 *
 * @param       None
 *
 * @retval      pin value
 */
uint32_t TSC_Acq_GPIOB_CHANNEL_SHIELD(void)
{
    uint32_t pin = 0;
#if (TOUCH_TSC_GROUP3_IO2 == CHANNEL) || (TOUCH_TSC_GROUP3_IO2 == SHIELD)
    pin |= GPIO_PIN_0;
#endif
#if (TOUCH_TSC_GROUP3_IO3 == CHANNEL) || (TOUCH_TSC_GROUP3_IO3 == SHIELD)
    pin |= GPIO_PIN_1;
#endif
#if (TOUCH_TSC_GROUP3_IO4 == CHANNEL) || (TOUCH_TSC_GROUP3_IO4 == SHIELD)
    pin |= GPIO_PIN_2;
#endif
#if (TOUCH_TSC_GROUP5_IO1 == CHANNEL) || (TOUCH_TSC_GROUP5_IO1 == SHIELD)
    pin |= GPIO_PIN_3;
#endif
#if (TOUCH_TSC_GROUP5_IO2 == CHANNEL) || (TOUCH_TSC_GROUP5_IO2 == SHIELD)
    pin |= GPIO_PIN_4;
#endif
#if (TOUCH_TSC_GROUP5_IO3 == CHANNEL) || (TOUCH_TSC_GROUP5_IO3 == SHIELD)
    pin |= GPIO_PIN_6;
#endif
#if (TOUCH_TSC_GROUP5_IO4 == CHANNEL) || (TOUCH_TSC_GROUP5_IO4 == SHIELD)
    pin |= GPIO_PIN_7;
#endif
#if (TOUCH_TSC_GROUP6_IO1 == CHANNEL) || (TOUCH_TSC_GROUP6_IO1 == SHIELD)
    pin |= GPIO_PIN_11;
#endif
#if (TOUCH_TSC_GROUP6_IO2 == CHANNEL) || (TOUCH_TSC_GROUP6_IO2 == SHIELD)
    pin |= GPIO_PIN_12;
#endif
#if (TOUCH_TSC_GROUP6_IO3 == CHANNEL) || (TOUCH_TSC_GROUP6_IO3 == SHIELD)
    pin |= GPIO_PIN_13;
#endif
#if (TOUCH_TSC_GROUP6_IO4 == CHANNEL) || (TOUCH_TSC_GROUP6_IO4 == SHIELD)
    pin |= GPIO_PIN_14;
#endif
    return pin;
}

/*!
 * @brief       Output Push-Pull for Channel and Shield GPIOC
 *
 * @param       None
 *
 * @retval      pin value
 */
uint32_t TSC_Acq_GPIOC_CHANNEL_SHIELD(void)
{
    uint32_t pin = 0;
#if (TOUCH_TSC_GROUP3_IO1 == CHANNEL) || (TOUCH_TSC_GROUP3_IO1 == SHIELD)
    pin |= GPIO_PIN_5;
#endif
    return pin;
}

/*!
 * @brief       Output Push-Pull for Channel and Shield GPIOD
 *
 * @param       None
 *
 * @retval      pin value
 */
#if (TSC_GROUP8_ENABLED > 0)
uint32_t TSC_Acq_GPIOD_CHANNEL_SHIELD(void)
{
    uint32_t pin = 0;
#if (TOUCH_TSC_GROUP8_IO1 == CHANNEL) || (TOUCH_TSC_GROUP8_IO1 == SHIELD)
    pin |= GPIO_PIN_12;
#endif
#if (TOUCH_TSC_GROUP8_IO2 == CHANNEL) || (TOUCH_TSC_GROUP8_IO2 == SHIELD)
    pin |= GPIO_PIN_13;
#endif
#if (TOUCH_TSC_GROUP8_IO3 == CHANNEL) || (TOUCH_TSC_GROUP8_IO3 == SHIELD)
    pin |= GPIO_PIN_14;
#endif
#if (TOUCH_TSC_GROUP8_IO4 == CHANNEL) || (TOUCH_TSC_GROUP8_IO4 == SHIELD)
    pin |= GPIO_PIN_15;
#endif
    return pin;
}
#endif

/*!
 * @brief       Output Push-Pull for Channel and Shield GPIOE
 *
 * @param       None
 *
 * @retval      pin value
 */
#if (TSC_GROUP7_ENABLED > 0)
uint32_t TSC_Acq_GPIOE_CHANNEL_SHIELD(void)
{
    uint32_t pin = 0;
#if (TOUCH_TSC_GROUP7_IO1 == CHANNEL) || (TOUCH_TSC_GROUP7_IO1 == SHIELD)
    pin |= GPIO_PIN_2;
#endif
#if (TOUCH_TSC_GROUP7_IO2 == CHANNEL) || (TOUCH_TSC_GROUP7_IO2 == SHIELD)
    pin |= GPIO_PIN_3;
#endif
#if (TOUCH_TSC_GROUP7_IO3 == CHANNEL) || (TOUCH_TSC_GROUP7_IO3 == SHIELD)
    pin |= GPIO_PIN_4;
#endif
#if (TOUCH_TSC_GROUP7_IO4 == CHANNEL) || (TOUCH_TSC_GROUP7_IO4 == SHIELD)
    pin |= GPIO_PIN_5;
#endif
    return pin;
#endif

    /*!
     * @brief       Alternate-Function AF3 for GPIOA in ALFL register
     *
     * @param       None
     *
     * @retval      ALFL value
     */
    uint32_t TSC_Acq_GPIOA_AF3_L(void)
    {
        uint32_t val_ALFL = 0;
#if TOUCH_TSC_GROUP1_IO1 != NU
        val_ALFL |= (uint32_t)((uint32_t)3 << (0 * 4));
#endif
#if TOUCH_TSC_GROUP1_IO2 != NU
        val_ALFL |= (uint32_t)((uint32_t)3 << (1 * 4));
#endif
#if TOUCH_TSC_GROUP1_IO3 != NU
        val_ALFL |= (uint32_t)((uint32_t)3 << (2 * 4));
#endif
#if TOUCH_TSC_GROUP1_IO4 != NU
        val_ALFL |= (uint32_t)((uint32_t)3 << (3 * 4));
#endif
#if TOUCH_TSC_GROUP2_IO1 != NU
        val_ALFL |= (uint32_t)((uint32_t)3 << (4 * 4));
#endif
#if TOUCH_TSC_GROUP2_IO2 != NU
        val_ALFL |= (uint32_t)((uint32_t)3 << (5 * 4));
#endif
#if TOUCH_TSC_GROUP2_IO3 != NU
        val_ALFL |= (uint32_t)((uint32_t)3 << (6 * 4));
#endif
#if TOUCH_TSC_GROUP2_IO4 != NU
        val_ALFL |= (uint32_t)((uint32_t)3 << (7 * 4));
#endif
        return val_ALFL;
    }

    /*!
     * @brief       Alternate-Function AF3 for GPIOA in ALFH register
     *
     * @param       None
     *
     * @retval      ALFH value
     */
    uint32_t TSC_Acq_GPIOA_AF3_H(void)
    {
        uint32_t val_ALFH = 0;
#if TOUCH_TSC_GROUP4_IO1 != NU
        val_ALFH |= (uint32_t)((uint32_t)3 << (1 * 4));
#endif
#if TOUCH_TSC_GROUP4_IO2 != NU
        val_ALFH |= (uint32_t)((uint32_t)3 << (2 * 4));
#endif
#if TOUCH_TSC_GROUP4_IO3 != NU
        val_ALFH |= (uint32_t)((uint32_t)3 << (3 * 4));
#endif
#if TOUCH_TSC_GROUP4_IO4 != NU
        val_ALFH |= (uint32_t)((uint32_t)3 << (4 * 4));
#endif
        return val_ALFH;
    }

    /*!
     * @brief       Alternate-Function AF3 for GPIOB in ALFL register
     *
     * @param       None
     *
     * @retval      ALFL value
     */
    uint32_t TSC_Acq_GPIOB_AF3_L(void)
    {
        uint32_t val_ALFL = 0;
#if TOUCH_TSC_GROUP3_IO2 != NU
        val_ALFL |= (uint32_t)((uint32_t)3 << (0 * 4));
#endif
#if TOUCH_TSC_GROUP3_IO3 != NU
        val_ALFL |= (uint32_t)((uint32_t)3 << (1 * 4));
#endif
#if TOUCH_TSC_GROUP3_IO4 != NU
        val_ALFL |= (uint32_t)((uint32_t)3 << (2 * 4));
#endif
#if TOUCH_TSC_GROUP5_IO1 != NU
        val_ALFL |= (uint32_t)((uint32_t)3 << (3 * 4));
#endif
#if TOUCH_TSC_GROUP5_IO2 != NU
        val_ALFL |= (uint32_t)((uint32_t)3 << (4 * 4));
#endif
#if TOUCH_TSC_GROUP5_IO3 != NU
        val_ALFL |= (uint32_t)((uint32_t)3 << (6 * 4));
#endif
#if TOUCH_TSC_GROUP5_IO4 != NU
        val_ALFL |= (uint32_t)((uint32_t)3 << (7 * 4));
#endif
        return val_ALFL;
    }

    /*!
     * @brief       Alternate-Function AF3 for GPIOB in ALFH register
     *
     * @param       None
     *
     * @retval      ALFH value
     */
    uint32_t TSC_Acq_GPIOB_AF3_H(void)
    {
        uint32_t val_ALFH = 0;
#if TOUCH_TSC_GROUP6_IO1 != NU
        val_ALFH |= (uint32_t)((uint32_t)3 << (3 * 4));
#endif
#if TOUCH_TSC_GROUP6_IO2 != NU
        val_ALFH |= (uint32_t)((uint32_t)3 << (4 * 4));
#endif
#if TOUCH_TSC_GROUP6_IO3 != NU
        val_ALFH |= (uint32_t)((uint32_t)3 << (5 * 4));
#endif
#if TOUCH_TSC_GROUP6_IO4 != NU
        val_ALFH |= (uint32_t)((uint32_t)3 << (6 * 4));
#endif
        return val_ALFH;
    }

    /*!
     * @brief       Alternate-Function AF1 for GPIOD in ALFH register
     *
     * @param       None
     *
     * @retval      ALFH value
     */
#if (TSC_GROUP8_ENABLED > 0)
    uint32_t TSC_Acq_GPIOD_AF1_H(void)
    {
        uint32_t val_ALFH = 0;
#if TOUCH_TSC_GROUP8_IO1 != NU
        val_ALFH |= (uint32_t)((uint32_t)1 << (4 * 4));
#endif
#if TOUCH_TSC_GROUP8_IO2 != NU
        val_ALFH |= (uint32_t)((uint32_t)1 << (5 * 4));
#endif
#if TOUCH_TSC_GROUP8_IO3 != NU
        val_ALFH |= (uint32_t)((uint32_t)1 << (6 * 4));
#endif
#if TOUCH_TSC_GROUP8_IO4 != NU
        val_ALFH |= (uint32_t)((uint32_t)1 << (7 * 4));
#endif
        return val_ALFH;
    }
#endif

    /*!
     * @brief       Alternate-Function AF1 for GPIOE in ALFL register
     *
     * @param       None
     *
     * @retval      ALFL value
     */
#if (TSC_GROUP7_ENABLED > 0)
    uint32_t TSC_Acq_GPIOE_AF1_L(void)
    {
        uint32_t val_ALFL = 0;
#if TOUCH_TSC_GROUP7_IO1 != NU
        val_ALFL |= (uint32_t)((uint32_t)1 << (2 * 4));
#endif
#if TOUCH_TSC_GROUP7_IO2 != NU
        val_ALFL |= (uint32_t)((uint32_t)1 << (3 * 4));
#endif
#if TOUCH_TSC_GROUP7_IO3 != NU
        val_ALFL |= (uint32_t)((uint32_t)1 << (4 * 4));
#endif
#if TOUCH_TSC_GROUP7_IO4 != NU
        val_ALFL |= (uint32_t)((uint32_t)1 << (5 * 4));
#endif
        return val_ALFL;
    }
#endif

    /*!
     * @brief       Disable Schmitt trigger hysteresis GPIO in IOHCTRL register
     *
     * @param       None
     *
     * @retval      IOHCTRL value
     */
    uint32_t TSC_Acq_Schmitt_Trigger_Hysteresis(void)
    {
        uint32_t val_IOHCTRL = 0xFFFFFFFF;
#if TOUCH_TSC_GROUP1_IO1 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 0);
#endif
#if TOUCH_TSC_GROUP1_IO2 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 1);
#endif
#if TOUCH_TSC_GROUP1_IO3 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 2);
#endif
#if TOUCH_TSC_GROUP1_IO4 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 3);
#endif
#if TOUCH_TSC_GROUP2_IO1 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 4);
#endif
#if TOUCH_TSC_GROUP2_IO2 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 5);
#endif
#if TOUCH_TSC_GROUP2_IO3 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 6);
#endif
#if TOUCH_TSC_GROUP2_IO4 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 7);
#endif
#if TOUCH_TSC_GROUP3_IO1 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 8);
#endif
#if TOUCH_TSC_GROUP3_IO2 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 9);
#endif
#if TOUCH_TSC_GROUP3_IO3 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 10);
#endif
#if TOUCH_TSC_GROUP3_IO4 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 11);
#endif
#if TOUCH_TSC_GROUP4_IO1 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 12);
#endif
#if TOUCH_TSC_GROUP4_IO2 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 13);
#endif
#if TOUCH_TSC_GROUP4_IO3 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 14);
#endif
#if TOUCH_TSC_GROUP4_IO4 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 15);
#endif
#if TOUCH_TSC_GROUP5_IO1 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 16);
#endif
#if TOUCH_TSC_GROUP5_IO2 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 17);
#endif
#if TOUCH_TSC_GROUP5_IO3 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 18);
#endif
#if TOUCH_TSC_GROUP5_IO4 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 19);
#endif
#if TOUCH_TSC_GROUP6_IO1 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 20);
#endif
#if TOUCH_TSC_GROUP6_IO2 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 21);
#endif
#if TOUCH_TSC_GROUP6_IO3 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 22);
#endif
#if TOUCH_TSC_GROUP6_IO4 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 23);
#endif
#if (TSC_GROUP7_ENABLED > 0)
#if TOUCH_TSC_GROUP7_IO1 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 24);
#endif
#if TOUCH_TSC_GROUP7_IO2 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 25);
#endif
#if TOUCH_TSC_GROUP7_IO3 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 26);
#endif
#if TOUCH_TSC_GROUP7_IO4 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 27);
#endif
#endif /*!< TSC_GROUP7_ENABLED */
#if (TSC_GROUP8_ENABLED > 0)
#if TOUCH_TSC_GROUP8_IO1 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 28);
#endif
#if TOUCH_TSC_GROUP8_IO2 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 29);
#endif
#if TOUCH_TSC_GROUP8_IO3 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 30);
#endif
#if TOUCH_TSC_GROUP8_IO4 != NU
        val_IOHCTRL &= (uint32_t)~((uint32_t)1 << 31);
#endif
#endif /*!< TSC_GROUP8_ENABLED */
        return val_IOHCTRL;
    }

    /*!
     * @brief       Sampling Capacitor GPIO in IOSMPCTRL register
     *
     * @param       None
     *
     * @retval      IOSMPCTRL value
     */
    uint32_t TSC_Acq_Sampling_Capacitor(void)
    {
        uint32_t val_IOSMPCTRL = 0;
#if TOUCH_TSC_GROUP1_IO1 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 0);
#endif
#if TOUCH_TSC_GROUP1_IO2 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 1);
#endif
#if TOUCH_TSC_GROUP1_IO3 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 2);
#endif
#if TOUCH_TSC_GROUP1_IO4 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 3);
#endif
#if TOUCH_TSC_GROUP2_IO1 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 4);
#endif
#if TOUCH_TSC_GROUP2_IO2 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 5);
#endif
#if TOUCH_TSC_GROUP2_IO3 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 6);
#endif
#if TOUCH_TSC_GROUP2_IO4 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 7);
#endif
#if TOUCH_TSC_GROUP3_IO1 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 8);
#endif
#if TOUCH_TSC_GROUP3_IO2 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 9);
#endif
#if TOUCH_TSC_GROUP3_IO3 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 10);
#endif
#if TOUCH_TSC_GROUP3_IO4 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 11);
#endif
#if TOUCH_TSC_GROUP4_IO1 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 12);
#endif
#if TOUCH_TSC_GROUP4_IO2 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 13);
#endif
#if TOUCH_TSC_GROUP4_IO3 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 14);
#endif
#if TOUCH_TSC_GROUP4_IO4 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 15);
#endif
#if TOUCH_TSC_GROUP5_IO1 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 16);
#endif
#if TOUCH_TSC_GROUP5_IO2 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 17);
#endif
#if TOUCH_TSC_GROUP5_IO3 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 18);
#endif
#if TOUCH_TSC_GROUP5_IO4 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 19);
#endif
#if TOUCH_TSC_GROUP6_IO1 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 20);
#endif
#if TOUCH_TSC_GROUP6_IO2 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 21);
#endif
#if TOUCH_TSC_GROUP6_IO3 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 22);
#endif
#if TOUCH_TSC_GROUP6_IO4 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 23);
#endif
#if (TSC_GROUP7_ENABLED > 0)
#if TOUCH_TSC_GROUP7_IO1 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 24);
#endif
#if TOUCH_TSC_GROUP7_IO2 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 25);
#endif
#if TOUCH_TSC_GROUP7_IO3 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 26);
#endif
#if TOUCH_TSC_GROUP7_IO4 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 27);
#endif
#endif /*!< TSC_GROUP7_ENABLED */
#if (TSC_GROUP8_ENABLED > 0)
#if TOUCH_TSC_GROUP8_IO1 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 28);
#endif
#if TOUCH_TSC_GROUP8_IO2 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 29);
#endif
#if TOUCH_TSC_GROUP8_IO3 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 30);
#endif
#if TOUCH_TSC_GROUP8_IO4 == SAMPCAP
        val_IOSMPCTRL |= (uint32_t)((uint32_t)1 << 31);
#endif
#endif /*!< TSC_GROUP8_ENABLED */
        return val_IOSMPCTRL;
    }

    /*!
     * @brief       Config the Touch Sensing GPIO
     *
     * @param       None
     *
     * @retval      None
     *
     * @note        NU:      Not Used IO
     *              CHANNEL: Channel IO
     *              SHIELD:  Channel IO but not acquired
     *              SAMPCAP: Sampling Capacitor IO
     */
    void TSC_Acq_ConfigGPIO(void)
    {
        GPIO_Config_T gpioConfig;

        RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA | RCM_AHB_PERIPH_GPIOB | RCM_AHB_PERIPH_GPIOC);
#if (TSC_GROUP7_ENABLED > 0) || (TSC_GROUP8_ENABLED > 0)
        RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOD | RCM_AHB_PERIPH_GPIOE);
#endif

        /* Alternate function Output Open-Drain for Sampling Capacitor IOs */
        gpioConfig.mode    = GPIO_MODE_AF;
        gpioConfig.outtype = GPIO_OUT_TYPE_OD;
        gpioConfig.speed   = GPIO_SPEED_2MHz;
        gpioConfig.pupd    = GPIO_PUPD_NO;

        /* GPIOA */
        gpioConfig.pin = TSC_Acq_GPIOA_SAMPCAP();
        GPIO_Config(GPIOA, &gpioConfig);

        /* GPIOB */
        gpioConfig.pin = TSC_Acq_GPIOB_SAMPCAP();
        GPIO_Config(GPIOB, &gpioConfig);

        /* GPIOC */
        gpioConfig.pin = TSC_Acq_GPIOC_SAMPCAP();
        GPIO_Config(GPIOC, &gpioConfig);

        /* GPIOD */
#if (TSC_GROUP8_ENABLED > 0)
        gpioConfig.pin = TSC_Acq_GPIOD_SAMPCAP();
        GPIO_Config(GPIOD, &gpioConfig);
#endif

        /* GPIOE */
#if (TSC_GROUP7_ENABLED > 0)
        gpioConfig.pin = TSC_Acq_GPIOE_SAMPCAP();
        GPIO_Config(GPIOE, &gpioConfig);
#endif

        /* Alternate function Output Push-Pull for Channel and Shield IOs */
        gpioConfig.outtype = GPIO_OUT_TYPE_PP;

        /* GPIOA */
        gpioConfig.pin = TSC_Acq_GPIOA_CHANNEL_SHIELD();
        GPIO_Config(GPIOA, &gpioConfig);

        /* GPIOB */
        gpioConfig.pin = TSC_Acq_GPIOB_CHANNEL_SHIELD();
        GPIO_Config(GPIOB, &gpioConfig);

        /* GPIOC */
        gpioConfig.pin = TSC_Acq_GPIOC_CHANNEL_SHIELD();
        GPIO_Config(GPIOC, &gpioConfig);

        /* GPIOD */
#if (TSC_GROUP8_ENABLED > 0)
        gpioConfig.pin = TSC_Acq_GPIOD_CHANNEL_SHIELD();
        GPIO_Config(GPIOD, &gpioConfig);
#endif

        /* GPIOE */
#if (TSC_GROUP7_ENABLED > 0)
        gpioConfig.pin = TSC_Acq_GPIOE_CHANNEL_SHIELD();
        GPIO_Config(GPIOE, &gpioConfig);
#endif

        /* Config Alternate-Function AF3 for GPIOA and GPIOB */
        /* GPIOA */
        GPIOA->ALFL |= TSC_Acq_GPIOA_AF3_L();
        GPIOA->ALFH |= TSC_Acq_GPIOA_AF3_H();

        /* GPIOB */
        GPIOB->ALFL |= TSC_Acq_GPIOB_AF3_L();
        GPIOB->ALFH |= TSC_Acq_GPIOB_AF3_H();

        /* Config Alternate-Function AF1 for GPIOD and GPIOE */
        /* GPIOD */
#if (TSC_GROUP8_ENABLED > 0)
        GPIOD->ALFH |= TSC_Acq_GPIOD_AF1_H();
#endif

        /* GPIOE */
#if (TSC_GROUP7_ENABLED > 0)
        GPIOE->ALFL |= TSC_Acq_GPIOE_AF1_L();
#endif

        RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_TSC);

        /* Disable Schmitt trigger hysteresis on all used TSC IOs */
        TSC->IOHCTRL &= TSC_Acq_Schmitt_Trigger_Hysteresis();

        /* Config Sampling Capacitor IOs */
        TSC->IOSMPCTRL |= TSC_Acq_Sampling_Capacitor();
    }

    /*!
     * @brief       Configurate the acquisition module
     *
     * @param       None
     *
     * @retval      pointer to a TSC_STATUS_T structure
     */
    TSC_STATUS_T TSC_Acq_Config(void)
    {
#if TOUCH_TSC_GPIO_CONFIG > 0
        TSC_Acq_ConfigGPIO();
#endif

        RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_TSC);

        /* TSC enabled */
        TSC->CTRL = 0x01;

        /* Config CTPHSEL */
#if TOUCH_TSC_CTPHSEL > 0
        TSC->CTRL |= (uint32_t)((uint32_t)TOUCH_TSC_CTPHSEL << 28) & 0xF0000000;
#endif

        /* Config CTPLSEL */
#if TOUCH_TSC_CTPLSEL > 0
        TSC->CTRL |= (uint32_t)((uint32_t)TOUCH_TSC_CTPLSEL << 24) & 0x0F000000;
#endif

        /* Config Spread Spectrum */
#if TOUCH_TSC_USE_SSEN > 0
        TSC->CTRL |= (uint32_t)((uint32_t)TOUCH_TSC_USE_SSEN  << 16) & 0x00010000;
        TSC->CTRL |= (uint32_t)((uint32_t)TOUCH_TSC_SSERRVSEL << 17) & 0x00FE0000;
        TSC->CTRL |= (uint32_t)((uint32_t)TOUCH_TSC_SSCDFSEL  << 15) & 0x00008000;
#endif

        /* Config Prescaler */
#if TOUCH_TSC_PGCDFSEL > 0
        TSC->CTRL |= (uint32_t)((uint32_t)TOUCH_TSC_PGCDFSEL << 12) & 0x00007000;
#endif

        /* Config Max Count */
#if TOUCH_TSC_MCNTVSEL > 0
        TSC->CTRL |= (uint32_t)((uint32_t)TOUCH_TSC_MCNTVSEL << 5) & 0x000000E0;
#endif

        /* Config IO default in Output PP Low to discharge all capacitors */
        TSC->CTRL &= (uint32_t)(~(1 << 4));

        /* Config Synchronization Mode */
#if TOUCH_TSC_AMCFG > 0
        /* Config Synchronization Pin in Alternate-Function mode */
        RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOB);

#if TOUCH_TSC_SYNC_PIN == 0 /*!< PB8 */
        GPIOB->MODE  &= 0xFFFCFFFF;
        GPIOB->MODE  |= 0x00020000;
        GPIOB->ALFH  |= 0x00000003;
#else /*!< PB10 */
        GPIOB->MODE  &= 0xFFCFFFFF;
        GPIOB->MODE  |= 0x00200000;
        GPIOB->ALFH  |= 0x00000300;
#endif

        /* Config Synchronization Polarity */
        TSC->CTRL |= (uint32_t)((uint32_t)TOUCH_TSC_SYNC_POL << 3) & 0x00000008;

        /* Config acquisition mode */
        TSC->CTRL |= (uint32_t)((uint32_t)TOUCH_TSC_AMCFG << 2) & 0x00000004;
#endif

#if TOUCH_USE_ACQ_INTERRUPT > 0
        /* Config both EOAIEN and MCEIEN interrupts */
        TSC->INTEN |= 0x03;
        /* Configure NVIC */
        NVIC_EnableIRQRequest(TSC_IRQn, 0)
#endif

        /* Configure the delay that will be used to discharge the capacitors */
        DelayDischarge = (uint32_t)((TOUCH_DELAY_DISCHARGE_ALL * (uint32_t)(SystemCoreClock / 1000000)) / 48);
        return TSC_STATUS_OK;
    }

    /*!
     * @brief       Configures a Block
     *
     * @param       idxBlock:  Index of the Block
     *
     * @retval      pointer to a TSC_STATUS_T structure
     */
    TSC_STATUS_T TSC_Acq_ConfigBlock(TSC_tIndex_T idxBlock)
    {
        uint32_t idxChannel;
        uint32_t objStatus;
        uint32_t Gx, IOy;
        CONST TSC_Block_T* block = &(TSC_Globals.Block_Array[idxBlock]);
        CONST TSC_Channel_Src_T* pchSrc = block->p_chSrc;
        CONST TSC_Channel_Dest_T* pchDest = block->p_chDest;

        /* Mark the current block processed */
        TSC_Globals.For_Block = idxBlock;
        /* Enable the Gx_IOy used as channels (channels + shield) */
        TSC->IOCHCTRL = block->msk_IOCHCTRL_channels;
        /* Enable acquisition on selected Groups */
        TSC->IOGCSTS = block->msk_IOGCSTS_groups;

        for (idxChannel = 0; idxChannel < block->NumChannel; idxChannel++)
        {
            /* Read Object status flag */
            objStatus = block->p_chData[pchDest->IdxDest].Flag.ObjStatus;

            if (objStatus != TSC_OBJ_STATUS_ON)
            {
                /* Read the Channel Group mask */
                Gx = pchSrc->msk_IOGCSTS_group;
                /* Stop acquisition of the Group */
                TSC->IOGCSTS &= (uint32_t)~Gx;

                if (objStatus == TSC_OBJ_STATUS_OFF)
                {
                    /* Read the Channel IO mask */
                    IOy = pchSrc->msk_IOCHCTRL_channel;
                    /* Stop Burst of the Channel */
                    TSC->IOCHCTRL &= (uint32_t)~IOy;
                }
            }
            /* Next channel */
            pchSrc++;
            pchDest++;
        }
        return TSC_STATUS_OK;
    }

    /*!
     * @brief       Start acquisition on a previously configured block
     *
     * @param       None
     *
     * @retval      None
     */
    void TSC_Acq_StartPerConfigBlock(void)
    {
        /* Clear both EOAIC and MCEIC flag */
        TSC->INTFCLR |= 0x03;

        /* Wait capacitors discharge */
        SoftDelay(DelayDischarge);

#if TOUCH_TSC_IODEF > 0
        /* Config IO default in Input Floating */
        TSC->CTRL |= (1 << 4);
#endif

        /* Start acquisition */
        TSC->CTRL |= 0x02;
    }

    /*!
     * @brief       Wait end of acquisition
     *
     * @param       None
     *
     * @retval      None
     */
    TSC_STATUS_T TSC_Acq_WaitBlockEOA(void)
    {
        TSC_STATUS_T retval = TSC_STATUS_BUSY;

        /* Check EOAFLG flag */
        if (TSC->INTSTS & 0x01)
        {
#if TOUCH_TSC_IODEF > 0
            /* Config IO default in Output PP Low to discharge all capacitors */
            TSC->CTRL &= (uint32_t)(~(1 << 4));
#endif

            /* Check MCEFLG flag */
            if (TSC->INTSTS & 0x02)
            {
                retval = TSC_STATUS_ERROR;
            }
            else
            {
                retval = TSC_STATUS_OK;
            }
        }
        return retval;
    }

    /*!
     * @brief       Return the current measure
     *
     * @param       index: Index of the measure source
     *
     * @retval      Measure
     */
    TSC_tMeas_T TSC_Acq_ReadMeasurVal(TSC_tIndex_T index)
    {
        return ((TSC_tMeas_T)(TSC->IOGxCNT[index].IOGCNT));
    }

    /*!
     * @brief       Compute the Delta value
     *
     * @param       refVal: Reference value
     *
     * @param       measVal: Measurement value
     *
     * @retval      Delta value
     */
    TSC_tDelta_T TSC_Acq_ComputeDelta(TSC_tRefer_T refVal, TSC_tMeas_T measVal)
    {
        return ((TSC_tDelta_T)(refVal - measVal));
    }

    /*!
     * @brief       Compute the Measurement value
     *
     * @param       refVal: Reference value
     *
     * @param       deltaVal: delta Delta value
     *
     * @retval      Measurement value
     */
    TSC_tMeas_T TSC_Acq_ComputeMeas(TSC_tRefer_T refVal, TSC_tDelta_T deltaVal)
    {
        return ((TSC_tMeas_T)(refVal - deltaVal));
    }

    /*!
     * @brief       Check noise (not used)
     *
     * @param       None
     *
     * @retval      pointer to a TSC_STATUS_T structure
     */
    TSC_ACQ_STATUS_T TSC_Acq_CheckNoise(void)
    {
        return TSC_ACQ_STATUS_OK;
    }

    /*!
     * @brief       Check if a filter must be used on the current channel (not used)
     *
     * @param       pCh: Pointer on the channel data information
     *
     * @retval      Result TRUE if a filter can be applied
     */
    TSC_BOOL_T TSC_Acq_UseFilter(TSC_Channel_Data_T * pCh)
    {
        return TSC_TRUE;
    }

    /*!
     * @brief       Test if the Reference is incorrect (not used)
     *
     * @param       pCh: Pointer on the channel data information
     *
     * @retval      Result TRUE if the Reference is out of range
     */
    TSC_BOOL_T TSC_Acq_TestReferenceRange(TSC_Channel_Data_T * pCh)
    {
        return TSC_FALSE;
    }

    /*!
     * @brief       Test if the measure has crossed the reference target (not used)
     *
     * @param       pCh: Pointer on the channel data information
     *
     * @param       newMeas: Measure of the last acquisition on this channel
     *
     * @retval      Result TRUE if the Reference is valid
     */
    TSC_BOOL_T TSC_Acq_TestFirstReference(TSC_Channel_Data_T * pCh, TSC_tMeas_T newMeas)
    {
        return TSC_TRUE;
    }

    /*!
     * @brief       Software delay (private routine)
     *
     * @param       val: Wait delay
     *
     * @retval      None
     *
     * @note        Measurements done with HCLK=48MHz and Keil/MDK-ARM compiler
     *              val =  500: ~ 53
     *              val = 1000: ~106
     *              val = 2000: ~210
     */
    void SoftDelay(uint32_t val)
    {
        uint32_t i;
        for (i = val; i > 0; i--)
        {}
    }

    /*!
     * @brief       Read all channels measurement of a Block, calculate delta
     *
     * @param       idxBlock: Index of the Block to access
     *
     * @param       mfilter: Pointer to the measure filter
     *
     * @param       dfilter: Pointer to the delta filter
     *
     * @retval      Status
     */
    TSC_STATUS_T TSC_Acq_ReadBlockResult(TSC_tIndex_T idxBlock, TSC_pMeasFilter_T mfilter, TSC_pDeltaFilter_T dfilter)
    {
        TSC_STATUS_T       retval = TSC_STATUS_OK;
        TSC_tIndex_T       idxChannel;
        TSC_tIndexDest_T   idxDest;
        TSC_tMeas_T        oldMeas, newMeas;
        TSC_tDelta_T       newDelta;
        CONST TSC_Block_T*   block = &(TSC_Globals.Block_Array[idxBlock]);
        CONST TSC_Channel_Dest_T* pchDest = block->p_chDest;
        CONST TSC_Channel_Src_T*  pchSrc = block->p_chSrc;

        /* For all channels in the block copy the measure + calculate delta and store them */
        for (idxChannel = 0; idxChannel < block->NumChannel; idxChannel++)
        {
            idxDest = pchDest->IdxDest;

            if (block->p_chData[idxDest].Flag.ObjStatus == TSC_OBJ_STATUS_ON)
            {
                block->p_chData[idxDest].Flag.DataReady = TSC_DATA_READY;
                newMeas = TSC_Acq_ReadMeasurVal(pchSrc->IdxSrc);

#if TOUCH_USE_MEAS > 0
                oldMeas = block->p_chData[idxDest].Meas;
#else
                oldMeas = newMeas;
#endif

#if TOUCH_USE_MEAS > 0
                block->p_chData[idxDest].Meas = newMeas;
#endif

                /* Check acquisition value min/max */
                if (newMeas > TSC_Params.AcqMax)
                {
                    block->p_chData[idxDest].Flag.AcqStatus = TSC_ACQ_STATUS_ERROR_MAX;
                    block->p_chData[idxDest].Delta = 0;
                    retval = TSC_STATUS_ERROR;
                }
                else
                {
                    if (newMeas < TSC_Params.AcqMin)
                    {
                        block->p_chData[idxDest].Flag.AcqStatus = TSC_ACQ_STATUS_ERROR_MIN;
                        block->p_chData[idxDest].Delta = 0;
                        retval = TSC_STATUS_ERROR;
                    }
                    else /*!< The measure is OK */
                    {
                        if (TSC_Acq_UseFilter(&block->p_chData[idxDest]) == 0)
                        {
                            block->p_chData[idxDest].Delta = TSC_Acq_ComputeDelta(block->p_chData[idxDest].Refer, newMeas);
                            block->p_chData[idxDest].Flag.AcqStatus = TSC_Acq_CheckNoise();
                        }
                        else
                        {
                            /* Measure filter*/
                            if (mfilter)
                            {
                                newMeas = mfilter(oldMeas, newMeas);
                                /* Store the measure */
#if TOUCH_USE_MEAS > 0
                                block->p_chData[idxDest].Meas = newMeas;
#endif
                            }

                            newDelta = TSC_Acq_ComputeDelta(block->p_chData[idxDest].Refer, newMeas);
                            block->p_chData[idxDest].Flag.AcqStatus = TSC_Acq_CheckNoise();

                            /* Delta filter */
                            if (dfilter == 0)
                            {
                                block->p_chData[idxDest].Delta = newDelta;
                            }
                            else
                            {
                                block->p_chData[idxDest].Delta = dfilter(newDelta);
                            }
                        }
                    }
                }
            }
            pchDest++;
            pchSrc++;
        }
        return retval;
    }

    /*!
     * @brief       Calibrate a Block
     *
     * @param       idxBlock: Index of the Block
     *
     * @retval      Status
     */
    TSC_STATUS_T TSC_Acq_CalibrateBlock(TSC_tIndex_T idxBlock)
    {
        TSC_STATUS_T         retval;
        TSC_STATUS_T         acqStatus;
        TSC_tIndex_T         idxChannel;
        TSC_tIndexDest_T     idxDest;
        TSC_tMeas_T          newMeas;
        static TSC_tIndex_T  goCalibration = 0;
        static TSC_tNum_T    doneCalibration = 0;
        static TSC_tNum_T    CalibDiv;
        CONST TSC_Block_T*    block;
        CONST  TSC_Channel_Dest_T* pchDest;
        CONST TSC_Channel_Src_T*   pchSrc;

        block = &(TSC_Globals.Block_Array[idxBlock]);

        if (goCalibration)/*!< Calibration is on-going */
        {
            acqStatus = TSC_Acq_WaitBlockEOA();

            switch (acqStatus)
            {
                case TSC_STATUS_OK:
                    pchDest = block->p_chDest;
                    pchSrc = block->p_chSrc;

                    for (idxChannel = 0; idxChannel < block->NumChannel; idxChannel++)
                    {
                        idxDest = pchDest->IdxDest;
                        newMeas = TSC_Acq_ReadMeasurVal(pchSrc->IdxSrc);

                        if ((newMeas < TSC_Params.AcqMin) || (newMeas > TSC_Params.AcqMax))
                        {
                            TSC_acq_ClearBlockData(idxBlock);
                            goCalibration = 0;
                            return TSC_STATUS_ERROR;
                        }
                        else
                        {
                            block->p_chData[idxDest].Refer += newMeas;
                        }
                        pchDest++;
                        pchSrc++;
                    }

                    doneCalibration--;
                    if (doneCalibration)
                    {
                        TSC_Acq_StartPerConfigBlock();
                        retval = TSC_STATUS_BUSY;
                    }
                    else
                    {
                        pchDest = block->p_chDest;

                        for (idxChannel = 0; idxChannel < block->NumChannel; idxChannel++)
                        {
                            idxDest = pchDest->IdxDest;
                            /* Divide the Reference by the number of samples */
                            block->p_chData[idxDest].Refer >>= CalibDiv;
                            pchDest++;
                        }
                        goCalibration = 0;
                        retval = TSC_STATUS_OK;
                    }
                    break;
                case TSC_STATUS_ERROR:
                    TSC_acq_ClearBlockData(idxBlock);
                    goCalibration = 0;
                    retval = TSC_STATUS_ERROR;
                    break;
                default:
                    retval = TSC_STATUS_BUSY;
                    break;
            }
        }
        else /*!< Calibration is done */
        {
            if (TSC_Params.NumCalibSample == 4)
            {
                CalibDiv = 2;
            }
            else if (TSC_Params.NumCalibSample == 16)
            {
                CalibDiv = 4;
            }
            else
            {
                TSC_Params.NumCalibSample =  8;
                CalibDiv = 3;
            }

            TSC_acq_ClearBlockData(idxBlock);

            if (TSC_Acq_ConfigBlock(idxBlock))
            {
                TSC_acq_ClearBlockData(idxBlock);
                goCalibration = 0;
                retval = TSC_STATUS_ERROR;
            }
            else
            {
                TSC_Acq_StartPerConfigBlock();
                goCalibration = 1;
                doneCalibration = TSC_Params.NumCalibSample;
                retval = TSC_STATUS_BUSY;
            }
        }
        return retval;
    }

    /*!
     * @brief       Clear Reference and delta on all channels of a Block
     *
     * @param       idxBlock: Index of the Block
     *
     * @retval      None
     */
    void TSC_acq_ClearBlockData(TSC_tIndex_T idxBlock)
    {
        TSC_tIndex_T      idxChannel;
        TSC_tIndexDest_T  idx_Dest;
        CONST TSC_Block_T*  block = &(TSC_Globals.Block_Array[idxBlock]);
        CONST TSC_Channel_Dest_T* pchDest = block->p_chDest;

        for (idxChannel = 0; idxChannel < block->NumChannel; idxChannel++)
        {
            idx_Dest = pchDest->IdxDest;
            block->p_chData[idx_Dest].Refer = 0;
            block->p_chData[idx_Dest].Delta = 0;
            pchDest++;
        }
    }

#if TOUCH_USE_ZONE > 0

    /*!
     * @brief       Configures a Zone
     *
     * @param       zone: Zone to configure
     *
     * @param       idxBlock: Index of the Block to access
     *
     * @retval      Status
     */
    TSC_STATUS_T TSC_Acq_ConfigZone(CONST TSC_Zone_T * zone, TSC_tIndex_T idxBlock)
    {
        TSC_STATUS_T retval;
        TSC_Globals.For_Zone = zone;

        do
        {
            retval = TSC_Acq_ConfigBlock(zone->indexBlock[idxBlock]);
            TSC_Globals.For_Block = zone->indexBlock[idxBlock];
            idxBlock++;
        }
        while ((idxBlock < zone->numBlock) && (retval == TSC_STATUS_ERROR));

        TSC_Globals.Index_For_Zone = idxBlock;

#if TOUCH_PXS_LOW_POWER_MODE > 0
        if (idxBlock < zone->numBlock)
        {
            resetPXSLowPower();
        }
#endif

        return (retval);
    }
#endif

    /**@} end of group TSC_Acquisition_Functions */
    /**@} end of group TSC_Acquisition_Driver */
    /**@} end of group TSC_Driver_Library */
