/**
  ******************************************************************************
  * @file    ald_rtchw.h
  * @brief   Header file of RTCHW Module driver.
  *
  * @version V1.0
  * @date    16 Nov 2019
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          16 Nov 2019     AE Team         The first version
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
  **********************************************************************************
  */

#ifndef __ALD_RTCHW_H__
#define __ALD_RTCHW_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup RTCHW
  * @{
  */

/** @defgroup RTCHW_Public_Types RTCHW Public Types
  * @{
  */
/**
  * @brief Hardware calibration algorithm
  */
typedef enum {
	RTC_CALI_MODE_NORMAL = 0U,	/**< Normal mode */
	RTC_CALI_MODE_SLEEP  = 1U,	/**< Low power mode */
} rtc_hw_cali_mode_t;

/**
  * @brief the parameters table of rtc calibration
  */
typedef  struct {
	uint32_t  MODE_CALI;		/**< Calibration Mode */
	uint32_t  RTC_CALCR;		/**< CALCR */
	uint32_t  RTC_TEMPBDR;		/**< TEMPBDR */
	uint32_t  TEMP_TBDR;		/**< TBDR */
	uint32_t  RTC_LTAXR;		/**< LTAXR */
	uint32_t  RTC_HTAXR;		/**< HTAXR */
	uint32_t  RTC_LTCAR;		/**< LTCAR */
	uint32_t  RTC_LTCBR;		/**< LTCBR */
	uint32_t  RTC_LTCCR;		/**< LTCCR */
	uint32_t  RTC_LTCDR;		/**< LTCDR */
	uint32_t  RTC_HTCAR;		/**< HTCAR */
	uint32_t  RTC_HTCBR;		/**< HTCBR */
	uint32_t  RTC_HTCCR;		/**< HTCCR */
	uint32_t  RTC_HTCDR;		/**< HTCDR */
	uint32_t  TEMP_LTGR;		/**< LTGR */
	uint32_t  TEMP_HTGR;		/**< HTGR */
	uint32_t  TEMP_CR;		/**< CR */
	uint32_t  rsv0;			/**< Reserved */
	uint32_t  RTC_LTCER;		/**< LTCER */
	uint32_t  RTC_HTCER;		/**< HTCER */
	uint32_t  TEMP_PEAK;		/**< PEAK */
	uint32_t  FREQ_PEAK;		/**< PEAK */
	uint32_t  TEMP_CALI;		/**< CALI */
	uint32_t  TEMP_CALI_AFTER;	/**< AFTER */
	uint32_t  TEMP_TCALBDR;		/**< TCALBDR */
	uint32_t  TEMP_TCALBDR_MINUS;	/**< TCALBDR_MINUS */
	uint32_t  rsv1[4];		/**< Reserved */
	uint32_t  SUM;			/**< SUM */
	uint32_t  SUM_MINUS;		/**< SUM_MINUS */
} RTCINFO_TypeDef;

/**
  * @brief Hardware calibration structure
  */
typedef struct {
	int16_t  offset_rtc_bdr;	/**< offset:0x00 */
	int16_t  offset_temp_bdr;	/**< offset:0x02 */
	int16_t  offset_ltaxr;		/**< offset:0x04 */
	int16_t  offset_htaxr;		/**< offset:0x06 */
	int16_t  offset_ltcar;		/**< offset:0x08 */
	int16_t  offset_ltcbr;		/**< offset:0x0A */
	int16_t  offset_ltccr;		/**< offset:0x0C */
	int16_t  offset_ltcdr;		/**< offset:0x0E */
	int16_t  offset_htcar;		/**< offset:0x10 */
	int16_t  offset_htcbr;		/**< offset:0x12 */
	int16_t  offset_htccr;		/**< offset:0x14 */
	int16_t  offset_htcdr;		/**< offset:0x16 */
	int16_t  offset_ltgr;		/**< offset:0x18 */
	int16_t  offset_htgr;		/**< offset:0x1A */
	int16_t  offset_ltcer;		/**< offset:0x1C */
	int16_t  offset_htcer;		/**< offset:0x1E */
	int16_t  offset_temp_peak;	/**< offset:0x20 */
	int16_t  offset_freq_peak;	/**< offset:0x22 */
	int16_t  offset_tcalbdr;	/**< offset:0x24 */
	int16_t  crc;			/**< offset:0x26 */
	int16_t  rsv[8];
} rtc_hw_cali_offset_t;
/**
  * @}
  */
/** @defgroup RTCHW_Private_Macros RTCHW Private Macros
  * @{
  */
#ifndef RTC_LOCK
#define RTC_LOCK()	(WRITE_REG(RTC->WPR, 0x0U))
#define RTC_UNLOCK()	(WRITE_REG(RTC->WPR, 0x55AAAA55U))
#endif

#ifndef TSENSE_LOCK
#define TSENSE_LOCK()	(WRITE_REG(TSENSE->WPR, 0x0U))
#define TSENSE_UNLOCK()	(WRITE_REG(TSENSE->WPR, 0xA55A9669U))
#endif

#define RTCINFO	((RTCINFO_TypeDef *)0x81000U)
/**
  * @}
  */

/** @addtogroup RTCHW_Public_Functions
  * @{
  */
/* Calibration functions */
void ald_rtc_hw_auto_cali(rtc_hw_cali_offset_t *config, rtc_hw_cali_mode_t mode);
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
#ifdef __cplusplus
}
#endif
#endif
