/**********************************************************************************
 *
 * @file    ald_conf.h
 * @brief   Enable/Disable the peripheral module.
 *
 * @date    23 Feb. 2023
 * @author  AE Team
 * @note
 *          Change Logs:
 *          Date            Author          Notes
 *          23 Feb. 2023    Lisq            the first version
 *
 * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 **********************************************************************************
 */
#ifndef   __ALD_CONF_H__
#define   __ALD_CONF_H__

/* Exported Macros ----------------------------------------------------------- */
/* Includes ------------------------------------------------------------------ */
#define ALD_I2C
#define ALD_GPIO
#define ALD_TIMER
#define ALD_ADC
#define ALD_DMA
#define ALD_SPI
/* #define ALD_IWDT */
/* #define ALD_WWDT */
/* #define ALD_CRC */
#define ALD_UART
#define ALD_CMU
/* #define ALD_DBGC */
/* #define ALD_PIS */
#define ALD_PMU
/* #define ALD_RMU */
#define ALD_SYSCFG
/* #define ALD_TYPE */
#define ALD_UTILS

#ifdef ALD_I2C
    #include "ald_i2c.h"
#endif /* ALD_I2C */

#ifdef ALD_GPIO
    #include "ald_gpio.h"
#endif /* MD_GPIO */

#ifdef ALD_TIMER
    #include "ald_timer.h"
#endif /* ALD_TIMER */

#ifdef ALD_ADC
    #include "ald_adc.h"
#endif /* ALD_ADC */

#ifdef ALD_DMA
    #include "ald_dma.h"
#endif /* ALD_DMA */

#ifdef ALD_SPI
    #include "ald_spi.h"
#endif /* ALD_SPI */

#ifdef ALD_IWDT
    #include "ald_iwdt.h"
#endif /* ALD_IWDT */

#ifdef ALD_WWDT
    #include "ald_wwdt.h"
#endif /* ALD_WWDT */

#ifdef ALD_CRC
    #include "ald_crc.h"
#endif /* ALD_CRC */

#ifdef ALD_UART
    #include "ald_uart.h"
#endif /* ALD_UART */

#ifdef ALD_CMU
    #include "ald_cmu.h"
#endif /* ALD_CMU */

#ifdef ALD_DBGC
    #include "ald_dbgc.h"
#endif /* ALD_DBGC */

#ifdef ALD_PIS
    #include "ald_pis.h"
#endif /* ALD_PIS */

#ifdef ALD_PMU
    #include "ald_pmu.h"
#endif /* ALD_PMU */

#ifdef ALD_RMU
    #include "ald_rmu.h"
#endif /* ALD_RMU */

#ifdef ALD_SYSCFG
    #include "ald_syscfg.h"
#endif /* ALD_SYSCFG */

#ifdef ALD_UTILS
    #include "ald_utils.h"
#endif /* ALD_UTILS */

#ifdef ALD_TYPE
    #include "type.h"
#endif /* ALD_TYPE */

#define TICK_INT_PRIORITY   3

/* Exported Types ------------------------------------------------------------ */
/* Exported Variables -------------------------------------------------------- */
/* Exported Constants -------------------------------------------------------- */
/* Exported Functions -------------------------------------------------------- */

#endif /*__MD_CONF_H__*/

/************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
