/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __HAL_RTC_H__
#define __HAL_RTC_H__

/** @addtogroup hal_rtc RTC
 *  rtc hal API.
 *
 *  @{
 */

#include <stdint.h>

#define HOSAL_RTC_FORMAT_DEC 1 /**< RTC DEC format */
#define HOSAL_RTC_FORMAT_BCD 2 /**< RTC BCD format */

/**
 * @brief rtc config struct
 */
typedef struct {
    uint8_t format; /**< time formart DEC or BCD */
} hosal_rtc_config_t;

/**
 * @brief rtc dev struct
 */
typedef struct {
    uint8_t       port;   /**< rtc port */
    hosal_rtc_config_t  config; /**< rtc config */
    void         *priv;   /**< priv data */
} hosal_rtc_dev_t;

/**
 * @brief RTC time struct
 */
typedef struct {
    uint8_t sec;     /**< DEC format:value range from 0 to 59, BCD format:value range from 0x00 to 0x59 */
    uint8_t min;     /**< DEC format:value range from 0 to 59, BCD format:value range from 0x00 to 0x59 */
    uint8_t hr;      /**< DEC format:value range from 0 to 23, BCD format:value range from 0x00 to 0x23 */
    uint8_t date;    /**< DEC format:value range from 1 to 31, BCD format:value range from 0x01 to 0x31 */
    uint8_t month;   /**< DEC format:value range from 1 to 12, BCD format:value range from 0x01 to 0x12 */
    uint16_t year;   /**< DEC format:value range from 0 to 9999, BCD format:value range from 0x0000 to 0x9999 */
} hosal_rtc_time_t;

/**
 * @brief This function will initialize the on board CPU real time clock
 *
 *
 * @param[in]  rtc  rtc device
 *
 * @return  
 *     - 0 : success
 *     - other : fail 
 */
int hosal_rtc_init(hosal_rtc_dev_t *rtc);

/**
 * @brief This function will set MCU RTC time to a new value.
 *
 * @param[in]   rtc   rtc device
 * @param[in]   time  pointer to a time structure
 *
 * @return  
 *     - 0 : success
 *     - other : fail 
 */
int hosal_rtc_set_time(hosal_rtc_dev_t *rtc, const hosal_rtc_time_t *time);

/**
 * @brief This function will return the value of time read from the on board CPU real time clock.
 *
 * @param[in]   rtc   rtc device
 * @param[out]  time  pointer to a time structure
 *
 * @return  
 *     - 0 : success
 *     - other : fail 
 */
int hosal_rtc_get_time(hosal_rtc_dev_t *rtc, hosal_rtc_time_t *time);

/**
 * @brief This function will set MCU RTC time to a new value.
 *
 * @param[in]   rtc   rtc device
 * @param[in]   time_stamp  new time value
 *
 * @return  
 *     - 0 : success
 *     - other : fail 
 */
int hosal_rtc_set_count(hosal_rtc_dev_t *rtc, uint64_t *time_stamp);

/**
 * @brief This function will return the value of time read from the on board CPU real time clock.
 *
 * @param[in]   rtc   rtc device
 * @param[in]   time_stamp new time value 
 *
 * @return  
 *     - 0 : success
 *     - other : fail 
 */
int hosal_rtc_get_count(hosal_rtc_dev_t *rtc, uint64_t *time_stamp);

/**
 * @brief De-initialises an RTC interface, Turns off an RTC hardware interface
 *
 * @param[in]  RTC  the interface which should be de-initialised
 *
 * @return  
 *     - 0 : success
 *     - other : fail 
 */
int hosal_rtc_finalize(hosal_rtc_dev_t *rtc);

/** @} */

#endif /* HAL_RTC_H */

