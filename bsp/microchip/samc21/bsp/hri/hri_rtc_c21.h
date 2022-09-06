/**
 * \file
 *
 * \brief SAM RTC
 *
 * Copyright (c) 2017-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#ifdef _SAMC21_RTC_COMPONENT_
#ifndef _HRI_RTC_C21_H_INCLUDED_
#define _HRI_RTC_C21_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <hal_atomic.h>

#if defined(ENABLE_RTC_CRITICAL_SECTIONS)
#define RTC_CRITICAL_SECTION_ENTER() CRITICAL_SECTION_ENTER()
#define RTC_CRITICAL_SECTION_LEAVE() CRITICAL_SECTION_LEAVE()
#else
#define RTC_CRITICAL_SECTION_ENTER()
#define RTC_CRITICAL_SECTION_LEAVE()
#endif

typedef uint16_t hri_rtcmode0_ctrla_reg_t;
typedef uint16_t hri_rtcmode0_intenset_reg_t;
typedef uint16_t hri_rtcmode0_intflag_reg_t;
typedef uint16_t hri_rtcmode1_comp_reg_t;
typedef uint16_t hri_rtcmode1_count_reg_t;
typedef uint16_t hri_rtcmode1_ctrla_reg_t;
typedef uint16_t hri_rtcmode1_intenset_reg_t;
typedef uint16_t hri_rtcmode1_intflag_reg_t;
typedef uint16_t hri_rtcmode1_per_reg_t;
typedef uint16_t hri_rtcmode2_ctrla_reg_t;
typedef uint16_t hri_rtcmode2_intenset_reg_t;
typedef uint16_t hri_rtcmode2_intflag_reg_t;
typedef uint32_t hri_rtcalarm_alarm_reg_t;
typedef uint32_t hri_rtcmode0_comp_reg_t;
typedef uint32_t hri_rtcmode0_count_reg_t;
typedef uint32_t hri_rtcmode0_evctrl_reg_t;
typedef uint32_t hri_rtcmode0_syncbusy_reg_t;
typedef uint32_t hri_rtcmode1_evctrl_reg_t;
typedef uint32_t hri_rtcmode1_syncbusy_reg_t;
typedef uint32_t hri_rtcmode2_alarm_reg_t;
typedef uint32_t hri_rtcmode2_clock_reg_t;
typedef uint32_t hri_rtcmode2_evctrl_reg_t;
typedef uint32_t hri_rtcmode2_syncbusy_reg_t;
typedef uint8_t  hri_rtc_dbgctrl_reg_t;
typedef uint8_t  hri_rtc_freqcorr_reg_t;
typedef uint8_t  hri_rtcalarm_mask_reg_t;
typedef uint8_t  hri_rtcmode2_mask_reg_t;

static inline void hri_rtcmode0_wait_for_sync(const void *const hw, hri_rtcmode0_syncbusy_reg_t reg)
{
	while (((Rtc *)hw)->MODE0.SYNCBUSY.reg & reg) {
	};
}

static inline bool hri_rtcmode0_is_syncing(const void *const hw, hri_rtcmode0_syncbusy_reg_t reg)
{
	return ((Rtc *)hw)->MODE0.SYNCBUSY.reg & reg;
}

static inline void hri_rtcmode1_wait_for_sync(const void *const hw, hri_rtcmode1_syncbusy_reg_t reg)
{
	while (((Rtc *)hw)->MODE1.SYNCBUSY.reg & reg) {
	};
}

static inline bool hri_rtcmode1_is_syncing(const void *const hw, hri_rtcmode1_syncbusy_reg_t reg)
{
	return ((Rtc *)hw)->MODE1.SYNCBUSY.reg & reg;
}

static inline void hri_rtcmode2_wait_for_sync(const void *const hw, hri_rtcmode2_syncbusy_reg_t reg)
{
	while (((Rtc *)hw)->MODE2.SYNCBUSY.reg & reg) {
	};
}

static inline bool hri_rtcmode2_is_syncing(const void *const hw, hri_rtcmode2_syncbusy_reg_t reg)
{
	return ((Rtc *)hw)->MODE2.SYNCBUSY.reg & reg;
}

static inline void hri_rtcalarm_set_ALARM_SECOND_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg |= RTC_MODE2_ALARM_SECOND(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcalarm_alarm_reg_t hri_rtcalarm_get_ALARM_SECOND_bf(const void *const hw, uint8_t submodule_index,
                                                                        hri_rtcalarm_alarm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_SECOND(mask)) >> RTC_MODE2_ALARM_SECOND_Pos;
	return tmp;
}

static inline void hri_rtcalarm_write_ALARM_SECOND_bf(const void *const hw, uint8_t submodule_index,
                                                      hri_rtcalarm_alarm_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp &= ~RTC_MODE2_ALARM_SECOND_Msk;
	tmp |= RTC_MODE2_ALARM_SECOND(data);
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcalarm_clear_ALARM_SECOND_bf(const void *const hw, uint8_t submodule_index,
                                                      hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg &= ~RTC_MODE2_ALARM_SECOND(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcalarm_toggle_ALARM_SECOND_bf(const void *const hw, uint8_t submodule_index,
                                                       hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg ^= RTC_MODE2_ALARM_SECOND(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcalarm_alarm_reg_t hri_rtcalarm_read_ALARM_SECOND_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_SECOND_Msk) >> RTC_MODE2_ALARM_SECOND_Pos;
	return tmp;
}

static inline void hri_rtcalarm_set_ALARM_MINUTE_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg |= RTC_MODE2_ALARM_MINUTE(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcalarm_alarm_reg_t hri_rtcalarm_get_ALARM_MINUTE_bf(const void *const hw, uint8_t submodule_index,
                                                                        hri_rtcalarm_alarm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_MINUTE(mask)) >> RTC_MODE2_ALARM_MINUTE_Pos;
	return tmp;
}

static inline void hri_rtcalarm_write_ALARM_MINUTE_bf(const void *const hw, uint8_t submodule_index,
                                                      hri_rtcalarm_alarm_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp &= ~RTC_MODE2_ALARM_MINUTE_Msk;
	tmp |= RTC_MODE2_ALARM_MINUTE(data);
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcalarm_clear_ALARM_MINUTE_bf(const void *const hw, uint8_t submodule_index,
                                                      hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg &= ~RTC_MODE2_ALARM_MINUTE(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcalarm_toggle_ALARM_MINUTE_bf(const void *const hw, uint8_t submodule_index,
                                                       hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg ^= RTC_MODE2_ALARM_MINUTE(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcalarm_alarm_reg_t hri_rtcalarm_read_ALARM_MINUTE_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_MINUTE_Msk) >> RTC_MODE2_ALARM_MINUTE_Pos;
	return tmp;
}

static inline void hri_rtcalarm_set_ALARM_HOUR_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg |= RTC_MODE2_ALARM_HOUR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcalarm_alarm_reg_t hri_rtcalarm_get_ALARM_HOUR_bf(const void *const hw, uint8_t submodule_index,
                                                                      hri_rtcalarm_alarm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_HOUR(mask)) >> RTC_MODE2_ALARM_HOUR_Pos;
	return tmp;
}

static inline void hri_rtcalarm_write_ALARM_HOUR_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_rtcalarm_alarm_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp &= ~RTC_MODE2_ALARM_HOUR_Msk;
	tmp |= RTC_MODE2_ALARM_HOUR(data);
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcalarm_clear_ALARM_HOUR_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg &= ~RTC_MODE2_ALARM_HOUR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcalarm_toggle_ALARM_HOUR_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg ^= RTC_MODE2_ALARM_HOUR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcalarm_alarm_reg_t hri_rtcalarm_read_ALARM_HOUR_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_HOUR_Msk) >> RTC_MODE2_ALARM_HOUR_Pos;
	return tmp;
}

static inline void hri_rtcalarm_set_ALARM_DAY_bf(const void *const hw, uint8_t submodule_index,
                                                 hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg |= RTC_MODE2_ALARM_DAY(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcalarm_alarm_reg_t hri_rtcalarm_get_ALARM_DAY_bf(const void *const hw, uint8_t submodule_index,
                                                                     hri_rtcalarm_alarm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_DAY(mask)) >> RTC_MODE2_ALARM_DAY_Pos;
	return tmp;
}

static inline void hri_rtcalarm_write_ALARM_DAY_bf(const void *const hw, uint8_t submodule_index,
                                                   hri_rtcalarm_alarm_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp &= ~RTC_MODE2_ALARM_DAY_Msk;
	tmp |= RTC_MODE2_ALARM_DAY(data);
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcalarm_clear_ALARM_DAY_bf(const void *const hw, uint8_t submodule_index,
                                                   hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg &= ~RTC_MODE2_ALARM_DAY(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcalarm_toggle_ALARM_DAY_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg ^= RTC_MODE2_ALARM_DAY(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcalarm_alarm_reg_t hri_rtcalarm_read_ALARM_DAY_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_DAY_Msk) >> RTC_MODE2_ALARM_DAY_Pos;
	return tmp;
}

static inline void hri_rtcalarm_set_ALARM_MONTH_bf(const void *const hw, uint8_t submodule_index,
                                                   hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg |= RTC_MODE2_ALARM_MONTH(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcalarm_alarm_reg_t hri_rtcalarm_get_ALARM_MONTH_bf(const void *const hw, uint8_t submodule_index,
                                                                       hri_rtcalarm_alarm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_MONTH(mask)) >> RTC_MODE2_ALARM_MONTH_Pos;
	return tmp;
}

static inline void hri_rtcalarm_write_ALARM_MONTH_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_rtcalarm_alarm_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp &= ~RTC_MODE2_ALARM_MONTH_Msk;
	tmp |= RTC_MODE2_ALARM_MONTH(data);
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcalarm_clear_ALARM_MONTH_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg &= ~RTC_MODE2_ALARM_MONTH(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcalarm_toggle_ALARM_MONTH_bf(const void *const hw, uint8_t submodule_index,
                                                      hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg ^= RTC_MODE2_ALARM_MONTH(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcalarm_alarm_reg_t hri_rtcalarm_read_ALARM_MONTH_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_MONTH_Msk) >> RTC_MODE2_ALARM_MONTH_Pos;
	return tmp;
}

static inline void hri_rtcalarm_set_ALARM_YEAR_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg |= RTC_MODE2_ALARM_YEAR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcalarm_alarm_reg_t hri_rtcalarm_get_ALARM_YEAR_bf(const void *const hw, uint8_t submodule_index,
                                                                      hri_rtcalarm_alarm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_YEAR(mask)) >> RTC_MODE2_ALARM_YEAR_Pos;
	return tmp;
}

static inline void hri_rtcalarm_write_ALARM_YEAR_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_rtcalarm_alarm_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp &= ~RTC_MODE2_ALARM_YEAR_Msk;
	tmp |= RTC_MODE2_ALARM_YEAR(data);
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcalarm_clear_ALARM_YEAR_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg &= ~RTC_MODE2_ALARM_YEAR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcalarm_toggle_ALARM_YEAR_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg ^= RTC_MODE2_ALARM_YEAR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcalarm_alarm_reg_t hri_rtcalarm_read_ALARM_YEAR_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_YEAR_Msk) >> RTC_MODE2_ALARM_YEAR_Pos;
	return tmp;
}

static inline void hri_rtcalarm_set_ALARM_reg(const void *const hw, uint8_t submodule_index,
                                              hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg |= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcalarm_alarm_reg_t hri_rtcalarm_get_ALARM_reg(const void *const hw, uint8_t submodule_index,
                                                                  hri_rtcalarm_alarm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtcalarm_write_ALARM_reg(const void *const hw, uint8_t submodule_index,
                                                hri_rtcalarm_alarm_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg = data;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcalarm_clear_ALARM_reg(const void *const hw, uint8_t submodule_index,
                                                hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg &= ~mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcalarm_toggle_ALARM_reg(const void *const hw, uint8_t submodule_index,
                                                 hri_rtcalarm_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg ^= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcalarm_alarm_reg_t hri_rtcalarm_read_ALARM_reg(const void *const hw, uint8_t submodule_index)
{
	return ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].ALARM.reg;
}

static inline void hri_rtcalarm_set_MASK_SEL_bf(const void *const hw, uint8_t submodule_index,
                                                hri_rtcalarm_mask_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].MASK.reg |= RTC_MODE2_MASK_SEL(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcalarm_mask_reg_t hri_rtcalarm_get_MASK_SEL_bf(const void *const hw, uint8_t submodule_index,
                                                                   hri_rtcalarm_mask_reg_t mask)
{
	uint8_t tmp;
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].MASK.reg;
	tmp = (tmp & RTC_MODE2_MASK_SEL(mask)) >> RTC_MODE2_MASK_SEL_Pos;
	return tmp;
}

static inline void hri_rtcalarm_write_MASK_SEL_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_rtcalarm_mask_reg_t data)
{
	uint8_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].MASK.reg;
	tmp &= ~RTC_MODE2_MASK_SEL_Msk;
	tmp |= RTC_MODE2_MASK_SEL(data);
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].MASK.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcalarm_clear_MASK_SEL_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_rtcalarm_mask_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].MASK.reg &= ~RTC_MODE2_MASK_SEL(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcalarm_toggle_MASK_SEL_bf(const void *const hw, uint8_t submodule_index,
                                                   hri_rtcalarm_mask_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].MASK.reg ^= RTC_MODE2_MASK_SEL(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcalarm_mask_reg_t hri_rtcalarm_read_MASK_SEL_bf(const void *const hw, uint8_t submodule_index)
{
	uint8_t tmp;
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].MASK.reg;
	tmp = (tmp & RTC_MODE2_MASK_SEL_Msk) >> RTC_MODE2_MASK_SEL_Pos;
	return tmp;
}

static inline void hri_rtcalarm_set_MASK_reg(const void *const hw, uint8_t submodule_index,
                                             hri_rtcalarm_mask_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].MASK.reg |= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcalarm_mask_reg_t hri_rtcalarm_get_MASK_reg(const void *const hw, uint8_t submodule_index,
                                                                hri_rtcalarm_mask_reg_t mask)
{
	uint8_t tmp;
	tmp = ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].MASK.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtcalarm_write_MASK_reg(const void *const hw, uint8_t submodule_index,
                                               hri_rtcalarm_mask_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].MASK.reg = data;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcalarm_clear_MASK_reg(const void *const hw, uint8_t submodule_index,
                                               hri_rtcalarm_mask_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].MASK.reg &= ~mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcalarm_toggle_MASK_reg(const void *const hw, uint8_t submodule_index,
                                                hri_rtcalarm_mask_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((RtcMode2 *)hw)->Mode2Alarm[submodule_index].MASK.reg ^= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcalarm_mask_reg_t hri_rtcalarm_read_MASK_reg(const void *const hw, uint8_t submodule_index)
{
	return ((RtcMode2 *)hw)->Mode2Alarm[submodule_index].MASK.reg;
}

static inline void hri_rtcmode2_set_ALARM_SECOND_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg |= RTC_MODE2_ALARM_SECOND(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_alarm_reg_t hri_rtcmode2_get_ALARM_SECOND_bf(const void *const hw, uint8_t submodule_index,
                                                                        hri_rtcmode2_alarm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_SECOND(mask)) >> RTC_MODE2_ALARM_SECOND_Pos;
	return tmp;
}

static inline void hri_rtcmode2_write_ALARM_SECOND_bf(const void *const hw, uint8_t submodule_index,
                                                      hri_rtcmode2_alarm_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp &= ~RTC_MODE2_ALARM_SECOND_Msk;
	tmp |= RTC_MODE2_ALARM_SECOND(data);
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_ALARM_SECOND_bf(const void *const hw, uint8_t submodule_index,
                                                      hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg &= ~RTC_MODE2_ALARM_SECOND(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_ALARM_SECOND_bf(const void *const hw, uint8_t submodule_index,
                                                       hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg ^= RTC_MODE2_ALARM_SECOND(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_alarm_reg_t hri_rtcmode2_read_ALARM_SECOND_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_SECOND_Msk) >> RTC_MODE2_ALARM_SECOND_Pos;
	return tmp;
}

static inline void hri_rtcmode2_set_ALARM_MINUTE_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg |= RTC_MODE2_ALARM_MINUTE(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_alarm_reg_t hri_rtcmode2_get_ALARM_MINUTE_bf(const void *const hw, uint8_t submodule_index,
                                                                        hri_rtcmode2_alarm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_MINUTE(mask)) >> RTC_MODE2_ALARM_MINUTE_Pos;
	return tmp;
}

static inline void hri_rtcmode2_write_ALARM_MINUTE_bf(const void *const hw, uint8_t submodule_index,
                                                      hri_rtcmode2_alarm_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp &= ~RTC_MODE2_ALARM_MINUTE_Msk;
	tmp |= RTC_MODE2_ALARM_MINUTE(data);
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_ALARM_MINUTE_bf(const void *const hw, uint8_t submodule_index,
                                                      hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg &= ~RTC_MODE2_ALARM_MINUTE(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_ALARM_MINUTE_bf(const void *const hw, uint8_t submodule_index,
                                                       hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg ^= RTC_MODE2_ALARM_MINUTE(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_alarm_reg_t hri_rtcmode2_read_ALARM_MINUTE_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_MINUTE_Msk) >> RTC_MODE2_ALARM_MINUTE_Pos;
	return tmp;
}

static inline void hri_rtcmode2_set_ALARM_HOUR_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg |= RTC_MODE2_ALARM_HOUR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_alarm_reg_t hri_rtcmode2_get_ALARM_HOUR_bf(const void *const hw, uint8_t submodule_index,
                                                                      hri_rtcmode2_alarm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_HOUR(mask)) >> RTC_MODE2_ALARM_HOUR_Pos;
	return tmp;
}

static inline void hri_rtcmode2_write_ALARM_HOUR_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_rtcmode2_alarm_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp &= ~RTC_MODE2_ALARM_HOUR_Msk;
	tmp |= RTC_MODE2_ALARM_HOUR(data);
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_ALARM_HOUR_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg &= ~RTC_MODE2_ALARM_HOUR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_ALARM_HOUR_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg ^= RTC_MODE2_ALARM_HOUR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_alarm_reg_t hri_rtcmode2_read_ALARM_HOUR_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_HOUR_Msk) >> RTC_MODE2_ALARM_HOUR_Pos;
	return tmp;
}

static inline void hri_rtcmode2_set_ALARM_DAY_bf(const void *const hw, uint8_t submodule_index,
                                                 hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg |= RTC_MODE2_ALARM_DAY(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_alarm_reg_t hri_rtcmode2_get_ALARM_DAY_bf(const void *const hw, uint8_t submodule_index,
                                                                     hri_rtcmode2_alarm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_DAY(mask)) >> RTC_MODE2_ALARM_DAY_Pos;
	return tmp;
}

static inline void hri_rtcmode2_write_ALARM_DAY_bf(const void *const hw, uint8_t submodule_index,
                                                   hri_rtcmode2_alarm_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp &= ~RTC_MODE2_ALARM_DAY_Msk;
	tmp |= RTC_MODE2_ALARM_DAY(data);
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_ALARM_DAY_bf(const void *const hw, uint8_t submodule_index,
                                                   hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg &= ~RTC_MODE2_ALARM_DAY(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_ALARM_DAY_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg ^= RTC_MODE2_ALARM_DAY(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_alarm_reg_t hri_rtcmode2_read_ALARM_DAY_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_DAY_Msk) >> RTC_MODE2_ALARM_DAY_Pos;
	return tmp;
}

static inline void hri_rtcmode2_set_ALARM_MONTH_bf(const void *const hw, uint8_t submodule_index,
                                                   hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg |= RTC_MODE2_ALARM_MONTH(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_alarm_reg_t hri_rtcmode2_get_ALARM_MONTH_bf(const void *const hw, uint8_t submodule_index,
                                                                       hri_rtcmode2_alarm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_MONTH(mask)) >> RTC_MODE2_ALARM_MONTH_Pos;
	return tmp;
}

static inline void hri_rtcmode2_write_ALARM_MONTH_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_rtcmode2_alarm_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp &= ~RTC_MODE2_ALARM_MONTH_Msk;
	tmp |= RTC_MODE2_ALARM_MONTH(data);
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_ALARM_MONTH_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg &= ~RTC_MODE2_ALARM_MONTH(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_ALARM_MONTH_bf(const void *const hw, uint8_t submodule_index,
                                                      hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg ^= RTC_MODE2_ALARM_MONTH(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_alarm_reg_t hri_rtcmode2_read_ALARM_MONTH_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_MONTH_Msk) >> RTC_MODE2_ALARM_MONTH_Pos;
	return tmp;
}

static inline void hri_rtcmode2_set_ALARM_YEAR_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg |= RTC_MODE2_ALARM_YEAR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_alarm_reg_t hri_rtcmode2_get_ALARM_YEAR_bf(const void *const hw, uint8_t submodule_index,
                                                                      hri_rtcmode2_alarm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_YEAR(mask)) >> RTC_MODE2_ALARM_YEAR_Pos;
	return tmp;
}

static inline void hri_rtcmode2_write_ALARM_YEAR_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_rtcmode2_alarm_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp &= ~RTC_MODE2_ALARM_YEAR_Msk;
	tmp |= RTC_MODE2_ALARM_YEAR(data);
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_ALARM_YEAR_bf(const void *const hw, uint8_t submodule_index,
                                                    hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg &= ~RTC_MODE2_ALARM_YEAR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_ALARM_YEAR_bf(const void *const hw, uint8_t submodule_index,
                                                     hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg ^= RTC_MODE2_ALARM_YEAR(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_alarm_reg_t hri_rtcmode2_read_ALARM_YEAR_bf(const void *const hw, uint8_t submodule_index)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp = (tmp & RTC_MODE2_ALARM_YEAR_Msk) >> RTC_MODE2_ALARM_YEAR_Pos;
	return tmp;
}

static inline void hri_rtcmode2_set_ALARM_reg(const void *const hw, uint8_t submodule_index,
                                              hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg |= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_alarm_reg_t hri_rtcmode2_get_ALARM_reg(const void *const hw, uint8_t submodule_index,
                                                                  hri_rtcmode2_alarm_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtcmode2_write_ALARM_reg(const void *const hw, uint8_t submodule_index,
                                                hri_rtcmode2_alarm_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg = data;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_ALARM_reg(const void *const hw, uint8_t submodule_index,
                                                hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg &= ~mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_ALARM_reg(const void *const hw, uint8_t submodule_index,
                                                 hri_rtcmode2_alarm_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg ^= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_alarm_reg_t hri_rtcmode2_read_ALARM_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].ALARM.reg;
}

static inline void hri_rtcmode2_set_MASK_SEL_bf(const void *const hw, uint8_t submodule_index,
                                                hri_rtcmode2_mask_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].MASK.reg |= RTC_MODE2_MASK_SEL(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_mask_reg_t hri_rtcmode2_get_MASK_SEL_bf(const void *const hw, uint8_t submodule_index,
                                                                   hri_rtcmode2_mask_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].MASK.reg;
	tmp = (tmp & RTC_MODE2_MASK_SEL(mask)) >> RTC_MODE2_MASK_SEL_Pos;
	return tmp;
}

static inline void hri_rtcmode2_write_MASK_SEL_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_rtcmode2_mask_reg_t data)
{
	uint8_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].MASK.reg;
	tmp &= ~RTC_MODE2_MASK_SEL_Msk;
	tmp |= RTC_MODE2_MASK_SEL(data);
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].MASK.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_MASK_SEL_bf(const void *const hw, uint8_t submodule_index,
                                                  hri_rtcmode2_mask_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].MASK.reg &= ~RTC_MODE2_MASK_SEL(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_MASK_SEL_bf(const void *const hw, uint8_t submodule_index,
                                                   hri_rtcmode2_mask_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].MASK.reg ^= RTC_MODE2_MASK_SEL(mask);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_mask_reg_t hri_rtcmode2_read_MASK_SEL_bf(const void *const hw, uint8_t submodule_index)
{
	uint8_t tmp;
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].MASK.reg;
	tmp = (tmp & RTC_MODE2_MASK_SEL_Msk) >> RTC_MODE2_MASK_SEL_Pos;
	return tmp;
}

static inline void hri_rtcmode2_set_MASK_reg(const void *const hw, uint8_t submodule_index,
                                             hri_rtcmode2_mask_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].MASK.reg |= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_mask_reg_t hri_rtcmode2_get_MASK_reg(const void *const hw, uint8_t submodule_index,
                                                                hri_rtcmode2_mask_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].MASK.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtcmode2_write_MASK_reg(const void *const hw, uint8_t submodule_index,
                                               hri_rtcmode2_mask_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].MASK.reg = data;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_MASK_reg(const void *const hw, uint8_t submodule_index,
                                               hri_rtcmode2_mask_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].MASK.reg &= ~mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_MASK_reg(const void *const hw, uint8_t submodule_index,
                                                hri_rtcmode2_mask_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].MASK.reg ^= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_mask_reg_t hri_rtcmode2_read_MASK_reg(const void *const hw, uint8_t submodule_index)
{
	return ((Rtc *)hw)->MODE2.Mode2Alarm[submodule_index].MASK.reg;
}

static inline bool hri_rtcmode0_get_INTFLAG_PER0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_PER0) >> RTC_MODE0_INTFLAG_PER0_Pos;
}

static inline void hri_rtcmode0_clear_INTFLAG_PER0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_PER0;
}

static inline bool hri_rtcmode0_get_INTFLAG_PER1_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_PER1) >> RTC_MODE0_INTFLAG_PER1_Pos;
}

static inline void hri_rtcmode0_clear_INTFLAG_PER1_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_PER1;
}

static inline bool hri_rtcmode0_get_INTFLAG_PER2_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_PER2) >> RTC_MODE0_INTFLAG_PER2_Pos;
}

static inline void hri_rtcmode0_clear_INTFLAG_PER2_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_PER2;
}

static inline bool hri_rtcmode0_get_INTFLAG_PER3_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_PER3) >> RTC_MODE0_INTFLAG_PER3_Pos;
}

static inline void hri_rtcmode0_clear_INTFLAG_PER3_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_PER3;
}

static inline bool hri_rtcmode0_get_INTFLAG_PER4_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_PER4) >> RTC_MODE0_INTFLAG_PER4_Pos;
}

static inline void hri_rtcmode0_clear_INTFLAG_PER4_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_PER4;
}

static inline bool hri_rtcmode0_get_INTFLAG_PER5_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_PER5) >> RTC_MODE0_INTFLAG_PER5_Pos;
}

static inline void hri_rtcmode0_clear_INTFLAG_PER5_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_PER5;
}

static inline bool hri_rtcmode0_get_INTFLAG_PER6_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_PER6) >> RTC_MODE0_INTFLAG_PER6_Pos;
}

static inline void hri_rtcmode0_clear_INTFLAG_PER6_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_PER6;
}

static inline bool hri_rtcmode0_get_INTFLAG_PER7_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_PER7) >> RTC_MODE0_INTFLAG_PER7_Pos;
}

static inline void hri_rtcmode0_clear_INTFLAG_PER7_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_PER7;
}

static inline bool hri_rtcmode0_get_INTFLAG_CMP0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_CMP0) >> RTC_MODE0_INTFLAG_CMP0_Pos;
}

static inline void hri_rtcmode0_clear_INTFLAG_CMP0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_CMP0;
}

static inline bool hri_rtcmode0_get_INTFLAG_OVF_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_OVF) >> RTC_MODE0_INTFLAG_OVF_Pos;
}

static inline void hri_rtcmode0_clear_INTFLAG_OVF_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_OVF;
}

static inline bool hri_rtcmode0_get_interrupt_PER0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_PER0) >> RTC_MODE0_INTFLAG_PER0_Pos;
}

static inline void hri_rtcmode0_clear_interrupt_PER0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_PER0;
}

static inline bool hri_rtcmode0_get_interrupt_PER1_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_PER1) >> RTC_MODE0_INTFLAG_PER1_Pos;
}

static inline void hri_rtcmode0_clear_interrupt_PER1_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_PER1;
}

static inline bool hri_rtcmode0_get_interrupt_PER2_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_PER2) >> RTC_MODE0_INTFLAG_PER2_Pos;
}

static inline void hri_rtcmode0_clear_interrupt_PER2_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_PER2;
}

static inline bool hri_rtcmode0_get_interrupt_PER3_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_PER3) >> RTC_MODE0_INTFLAG_PER3_Pos;
}

static inline void hri_rtcmode0_clear_interrupt_PER3_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_PER3;
}

static inline bool hri_rtcmode0_get_interrupt_PER4_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_PER4) >> RTC_MODE0_INTFLAG_PER4_Pos;
}

static inline void hri_rtcmode0_clear_interrupt_PER4_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_PER4;
}

static inline bool hri_rtcmode0_get_interrupt_PER5_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_PER5) >> RTC_MODE0_INTFLAG_PER5_Pos;
}

static inline void hri_rtcmode0_clear_interrupt_PER5_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_PER5;
}

static inline bool hri_rtcmode0_get_interrupt_PER6_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_PER6) >> RTC_MODE0_INTFLAG_PER6_Pos;
}

static inline void hri_rtcmode0_clear_interrupt_PER6_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_PER6;
}

static inline bool hri_rtcmode0_get_interrupt_PER7_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_PER7) >> RTC_MODE0_INTFLAG_PER7_Pos;
}

static inline void hri_rtcmode0_clear_interrupt_PER7_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_PER7;
}

static inline bool hri_rtcmode0_get_interrupt_CMP0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_CMP0) >> RTC_MODE0_INTFLAG_CMP0_Pos;
}

static inline void hri_rtcmode0_clear_interrupt_CMP0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_CMP0;
}

static inline bool hri_rtcmode0_get_interrupt_OVF_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_OVF) >> RTC_MODE0_INTFLAG_OVF_Pos;
}

static inline void hri_rtcmode0_clear_interrupt_OVF_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_OVF;
}

static inline hri_rtcmode0_intflag_reg_t hri_rtcmode0_get_INTFLAG_reg(const void *const          hw,
                                                                      hri_rtcmode0_intflag_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE0.INTFLAG.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_rtcmode0_intflag_reg_t hri_rtcmode0_read_INTFLAG_reg(const void *const hw)
{
	return ((Rtc *)hw)->MODE0.INTFLAG.reg;
}

static inline void hri_rtcmode0_clear_INTFLAG_reg(const void *const hw, hri_rtcmode0_intflag_reg_t mask)
{
	((Rtc *)hw)->MODE0.INTFLAG.reg = mask;
}

static inline bool hri_rtcmode1_get_INTFLAG_PER0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_PER0) >> RTC_MODE1_INTFLAG_PER0_Pos;
}

static inline void hri_rtcmode1_clear_INTFLAG_PER0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_PER0;
}

static inline bool hri_rtcmode1_get_INTFLAG_PER1_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_PER1) >> RTC_MODE1_INTFLAG_PER1_Pos;
}

static inline void hri_rtcmode1_clear_INTFLAG_PER1_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_PER1;
}

static inline bool hri_rtcmode1_get_INTFLAG_PER2_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_PER2) >> RTC_MODE1_INTFLAG_PER2_Pos;
}

static inline void hri_rtcmode1_clear_INTFLAG_PER2_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_PER2;
}

static inline bool hri_rtcmode1_get_INTFLAG_PER3_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_PER3) >> RTC_MODE1_INTFLAG_PER3_Pos;
}

static inline void hri_rtcmode1_clear_INTFLAG_PER3_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_PER3;
}

static inline bool hri_rtcmode1_get_INTFLAG_PER4_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_PER4) >> RTC_MODE1_INTFLAG_PER4_Pos;
}

static inline void hri_rtcmode1_clear_INTFLAG_PER4_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_PER4;
}

static inline bool hri_rtcmode1_get_INTFLAG_PER5_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_PER5) >> RTC_MODE1_INTFLAG_PER5_Pos;
}

static inline void hri_rtcmode1_clear_INTFLAG_PER5_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_PER5;
}

static inline bool hri_rtcmode1_get_INTFLAG_PER6_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_PER6) >> RTC_MODE1_INTFLAG_PER6_Pos;
}

static inline void hri_rtcmode1_clear_INTFLAG_PER6_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_PER6;
}

static inline bool hri_rtcmode1_get_INTFLAG_PER7_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_PER7) >> RTC_MODE1_INTFLAG_PER7_Pos;
}

static inline void hri_rtcmode1_clear_INTFLAG_PER7_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_PER7;
}

static inline bool hri_rtcmode1_get_INTFLAG_CMP0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_CMP0) >> RTC_MODE1_INTFLAG_CMP0_Pos;
}

static inline void hri_rtcmode1_clear_INTFLAG_CMP0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_CMP0;
}

static inline bool hri_rtcmode1_get_INTFLAG_CMP1_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_CMP1) >> RTC_MODE1_INTFLAG_CMP1_Pos;
}

static inline void hri_rtcmode1_clear_INTFLAG_CMP1_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_CMP1;
}

static inline bool hri_rtcmode1_get_INTFLAG_OVF_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_OVF) >> RTC_MODE1_INTFLAG_OVF_Pos;
}

static inline void hri_rtcmode1_clear_INTFLAG_OVF_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_OVF;
}

static inline bool hri_rtcmode1_get_interrupt_PER0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_PER0) >> RTC_MODE1_INTFLAG_PER0_Pos;
}

static inline void hri_rtcmode1_clear_interrupt_PER0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_PER0;
}

static inline bool hri_rtcmode1_get_interrupt_PER1_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_PER1) >> RTC_MODE1_INTFLAG_PER1_Pos;
}

static inline void hri_rtcmode1_clear_interrupt_PER1_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_PER1;
}

static inline bool hri_rtcmode1_get_interrupt_PER2_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_PER2) >> RTC_MODE1_INTFLAG_PER2_Pos;
}

static inline void hri_rtcmode1_clear_interrupt_PER2_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_PER2;
}

static inline bool hri_rtcmode1_get_interrupt_PER3_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_PER3) >> RTC_MODE1_INTFLAG_PER3_Pos;
}

static inline void hri_rtcmode1_clear_interrupt_PER3_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_PER3;
}

static inline bool hri_rtcmode1_get_interrupt_PER4_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_PER4) >> RTC_MODE1_INTFLAG_PER4_Pos;
}

static inline void hri_rtcmode1_clear_interrupt_PER4_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_PER4;
}

static inline bool hri_rtcmode1_get_interrupt_PER5_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_PER5) >> RTC_MODE1_INTFLAG_PER5_Pos;
}

static inline void hri_rtcmode1_clear_interrupt_PER5_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_PER5;
}

static inline bool hri_rtcmode1_get_interrupt_PER6_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_PER6) >> RTC_MODE1_INTFLAG_PER6_Pos;
}

static inline void hri_rtcmode1_clear_interrupt_PER6_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_PER6;
}

static inline bool hri_rtcmode1_get_interrupt_PER7_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_PER7) >> RTC_MODE1_INTFLAG_PER7_Pos;
}

static inline void hri_rtcmode1_clear_interrupt_PER7_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_PER7;
}

static inline bool hri_rtcmode1_get_interrupt_CMP0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_CMP0) >> RTC_MODE1_INTFLAG_CMP0_Pos;
}

static inline void hri_rtcmode1_clear_interrupt_CMP0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_CMP0;
}

static inline bool hri_rtcmode1_get_interrupt_CMP1_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_CMP1) >> RTC_MODE1_INTFLAG_CMP1_Pos;
}

static inline void hri_rtcmode1_clear_interrupt_CMP1_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_CMP1;
}

static inline bool hri_rtcmode1_get_interrupt_OVF_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTFLAG.reg & RTC_MODE1_INTFLAG_OVF) >> RTC_MODE1_INTFLAG_OVF_Pos;
}

static inline void hri_rtcmode1_clear_interrupt_OVF_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = RTC_MODE1_INTFLAG_OVF;
}

static inline hri_rtcmode1_intflag_reg_t hri_rtcmode1_get_INTFLAG_reg(const void *const          hw,
                                                                      hri_rtcmode1_intflag_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE1.INTFLAG.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_rtcmode1_intflag_reg_t hri_rtcmode1_read_INTFLAG_reg(const void *const hw)
{
	return ((Rtc *)hw)->MODE1.INTFLAG.reg;
}

static inline void hri_rtcmode1_clear_INTFLAG_reg(const void *const hw, hri_rtcmode1_intflag_reg_t mask)
{
	((Rtc *)hw)->MODE1.INTFLAG.reg = mask;
}

static inline bool hri_rtcmode2_get_INTFLAG_PER0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_PER0) >> RTC_MODE2_INTFLAG_PER0_Pos;
}

static inline void hri_rtcmode2_clear_INTFLAG_PER0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_PER0;
}

static inline bool hri_rtcmode2_get_INTFLAG_PER1_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_PER1) >> RTC_MODE2_INTFLAG_PER1_Pos;
}

static inline void hri_rtcmode2_clear_INTFLAG_PER1_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_PER1;
}

static inline bool hri_rtcmode2_get_INTFLAG_PER2_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_PER2) >> RTC_MODE2_INTFLAG_PER2_Pos;
}

static inline void hri_rtcmode2_clear_INTFLAG_PER2_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_PER2;
}

static inline bool hri_rtcmode2_get_INTFLAG_PER3_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_PER3) >> RTC_MODE2_INTFLAG_PER3_Pos;
}

static inline void hri_rtcmode2_clear_INTFLAG_PER3_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_PER3;
}

static inline bool hri_rtcmode2_get_INTFLAG_PER4_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_PER4) >> RTC_MODE2_INTFLAG_PER4_Pos;
}

static inline void hri_rtcmode2_clear_INTFLAG_PER4_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_PER4;
}

static inline bool hri_rtcmode2_get_INTFLAG_PER5_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_PER5) >> RTC_MODE2_INTFLAG_PER5_Pos;
}

static inline void hri_rtcmode2_clear_INTFLAG_PER5_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_PER5;
}

static inline bool hri_rtcmode2_get_INTFLAG_PER6_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_PER6) >> RTC_MODE2_INTFLAG_PER6_Pos;
}

static inline void hri_rtcmode2_clear_INTFLAG_PER6_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_PER6;
}

static inline bool hri_rtcmode2_get_INTFLAG_PER7_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_PER7) >> RTC_MODE2_INTFLAG_PER7_Pos;
}

static inline void hri_rtcmode2_clear_INTFLAG_PER7_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_PER7;
}

static inline bool hri_rtcmode2_get_INTFLAG_ALARM0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_ALARM0) >> RTC_MODE2_INTFLAG_ALARM0_Pos;
}

static inline void hri_rtcmode2_clear_INTFLAG_ALARM0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_ALARM0;
}

static inline bool hri_rtcmode2_get_INTFLAG_OVF_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_OVF) >> RTC_MODE2_INTFLAG_OVF_Pos;
}

static inline void hri_rtcmode2_clear_INTFLAG_OVF_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_OVF;
}

static inline bool hri_rtcmode2_get_interrupt_PER0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_PER0) >> RTC_MODE2_INTFLAG_PER0_Pos;
}

static inline void hri_rtcmode2_clear_interrupt_PER0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_PER0;
}

static inline bool hri_rtcmode2_get_interrupt_PER1_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_PER1) >> RTC_MODE2_INTFLAG_PER1_Pos;
}

static inline void hri_rtcmode2_clear_interrupt_PER1_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_PER1;
}

static inline bool hri_rtcmode2_get_interrupt_PER2_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_PER2) >> RTC_MODE2_INTFLAG_PER2_Pos;
}

static inline void hri_rtcmode2_clear_interrupt_PER2_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_PER2;
}

static inline bool hri_rtcmode2_get_interrupt_PER3_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_PER3) >> RTC_MODE2_INTFLAG_PER3_Pos;
}

static inline void hri_rtcmode2_clear_interrupt_PER3_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_PER3;
}

static inline bool hri_rtcmode2_get_interrupt_PER4_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_PER4) >> RTC_MODE2_INTFLAG_PER4_Pos;
}

static inline void hri_rtcmode2_clear_interrupt_PER4_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_PER4;
}

static inline bool hri_rtcmode2_get_interrupt_PER5_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_PER5) >> RTC_MODE2_INTFLAG_PER5_Pos;
}

static inline void hri_rtcmode2_clear_interrupt_PER5_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_PER5;
}

static inline bool hri_rtcmode2_get_interrupt_PER6_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_PER6) >> RTC_MODE2_INTFLAG_PER6_Pos;
}

static inline void hri_rtcmode2_clear_interrupt_PER6_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_PER6;
}

static inline bool hri_rtcmode2_get_interrupt_PER7_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_PER7) >> RTC_MODE2_INTFLAG_PER7_Pos;
}

static inline void hri_rtcmode2_clear_interrupt_PER7_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_PER7;
}

static inline bool hri_rtcmode2_get_interrupt_ALARM0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_ALARM0) >> RTC_MODE2_INTFLAG_ALARM0_Pos;
}

static inline void hri_rtcmode2_clear_interrupt_ALARM0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_ALARM0;
}

static inline bool hri_rtcmode2_get_interrupt_OVF_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTFLAG.reg & RTC_MODE2_INTFLAG_OVF) >> RTC_MODE2_INTFLAG_OVF_Pos;
}

static inline void hri_rtcmode2_clear_interrupt_OVF_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_OVF;
}

static inline hri_rtcmode2_intflag_reg_t hri_rtcmode2_get_INTFLAG_reg(const void *const          hw,
                                                                      hri_rtcmode2_intflag_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE2.INTFLAG.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_rtcmode2_intflag_reg_t hri_rtcmode2_read_INTFLAG_reg(const void *const hw)
{
	return ((Rtc *)hw)->MODE2.INTFLAG.reg;
}

static inline void hri_rtcmode2_clear_INTFLAG_reg(const void *const hw, hri_rtcmode2_intflag_reg_t mask)
{
	((Rtc *)hw)->MODE2.INTFLAG.reg = mask;
}

static inline void hri_rtcmode0_set_INTEN_PER0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_PER0;
}

static inline bool hri_rtcmode0_get_INTEN_PER0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTENSET.reg & RTC_MODE0_INTENSET_PER0) >> RTC_MODE0_INTENSET_PER0_Pos;
}

static inline void hri_rtcmode0_write_INTEN_PER0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_PER0;
	} else {
		((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_PER0;
	}
}

static inline void hri_rtcmode0_clear_INTEN_PER0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_PER0;
}

static inline void hri_rtcmode0_set_INTEN_PER1_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_PER1;
}

static inline bool hri_rtcmode0_get_INTEN_PER1_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTENSET.reg & RTC_MODE0_INTENSET_PER1) >> RTC_MODE0_INTENSET_PER1_Pos;
}

static inline void hri_rtcmode0_write_INTEN_PER1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_PER1;
	} else {
		((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_PER1;
	}
}

static inline void hri_rtcmode0_clear_INTEN_PER1_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_PER1;
}

static inline void hri_rtcmode0_set_INTEN_PER2_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_PER2;
}

static inline bool hri_rtcmode0_get_INTEN_PER2_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTENSET.reg & RTC_MODE0_INTENSET_PER2) >> RTC_MODE0_INTENSET_PER2_Pos;
}

static inline void hri_rtcmode0_write_INTEN_PER2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_PER2;
	} else {
		((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_PER2;
	}
}

static inline void hri_rtcmode0_clear_INTEN_PER2_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_PER2;
}

static inline void hri_rtcmode0_set_INTEN_PER3_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_PER3;
}

static inline bool hri_rtcmode0_get_INTEN_PER3_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTENSET.reg & RTC_MODE0_INTENSET_PER3) >> RTC_MODE0_INTENSET_PER3_Pos;
}

static inline void hri_rtcmode0_write_INTEN_PER3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_PER3;
	} else {
		((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_PER3;
	}
}

static inline void hri_rtcmode0_clear_INTEN_PER3_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_PER3;
}

static inline void hri_rtcmode0_set_INTEN_PER4_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_PER4;
}

static inline bool hri_rtcmode0_get_INTEN_PER4_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTENSET.reg & RTC_MODE0_INTENSET_PER4) >> RTC_MODE0_INTENSET_PER4_Pos;
}

static inline void hri_rtcmode0_write_INTEN_PER4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_PER4;
	} else {
		((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_PER4;
	}
}

static inline void hri_rtcmode0_clear_INTEN_PER4_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_PER4;
}

static inline void hri_rtcmode0_set_INTEN_PER5_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_PER5;
}

static inline bool hri_rtcmode0_get_INTEN_PER5_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTENSET.reg & RTC_MODE0_INTENSET_PER5) >> RTC_MODE0_INTENSET_PER5_Pos;
}

static inline void hri_rtcmode0_write_INTEN_PER5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_PER5;
	} else {
		((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_PER5;
	}
}

static inline void hri_rtcmode0_clear_INTEN_PER5_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_PER5;
}

static inline void hri_rtcmode0_set_INTEN_PER6_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_PER6;
}

static inline bool hri_rtcmode0_get_INTEN_PER6_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTENSET.reg & RTC_MODE0_INTENSET_PER6) >> RTC_MODE0_INTENSET_PER6_Pos;
}

static inline void hri_rtcmode0_write_INTEN_PER6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_PER6;
	} else {
		((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_PER6;
	}
}

static inline void hri_rtcmode0_clear_INTEN_PER6_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_PER6;
}

static inline void hri_rtcmode0_set_INTEN_PER7_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_PER7;
}

static inline bool hri_rtcmode0_get_INTEN_PER7_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTENSET.reg & RTC_MODE0_INTENSET_PER7) >> RTC_MODE0_INTENSET_PER7_Pos;
}

static inline void hri_rtcmode0_write_INTEN_PER7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_PER7;
	} else {
		((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_PER7;
	}
}

static inline void hri_rtcmode0_clear_INTEN_PER7_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_PER7;
}

static inline void hri_rtcmode0_set_INTEN_CMP0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_CMP0;
}

static inline bool hri_rtcmode0_get_INTEN_CMP0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTENSET.reg & RTC_MODE0_INTENSET_CMP0) >> RTC_MODE0_INTENSET_CMP0_Pos;
}

static inline void hri_rtcmode0_write_INTEN_CMP0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_CMP0;
	} else {
		((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_CMP0;
	}
}

static inline void hri_rtcmode0_clear_INTEN_CMP0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_CMP0;
}

static inline void hri_rtcmode0_set_INTEN_OVF_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_OVF;
}

static inline bool hri_rtcmode0_get_INTEN_OVF_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.INTENSET.reg & RTC_MODE0_INTENSET_OVF) >> RTC_MODE0_INTENSET_OVF_Pos;
}

static inline void hri_rtcmode0_write_INTEN_OVF_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_OVF;
	} else {
		((Rtc *)hw)->MODE0.INTENSET.reg = RTC_MODE0_INTENSET_OVF;
	}
}

static inline void hri_rtcmode0_clear_INTEN_OVF_bit(const void *const hw)
{
	((Rtc *)hw)->MODE0.INTENCLR.reg = RTC_MODE0_INTENSET_OVF;
}

static inline void hri_rtcmode0_set_INTEN_reg(const void *const hw, hri_rtcmode0_intenset_reg_t mask)
{
	((Rtc *)hw)->MODE0.INTENSET.reg = mask;
}

static inline hri_rtcmode0_intenset_reg_t hri_rtcmode0_get_INTEN_reg(const void *const           hw,
                                                                     hri_rtcmode0_intenset_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE0.INTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_rtcmode0_intenset_reg_t hri_rtcmode0_read_INTEN_reg(const void *const hw)
{
	return ((Rtc *)hw)->MODE0.INTENSET.reg;
}

static inline void hri_rtcmode0_write_INTEN_reg(const void *const hw, hri_rtcmode0_intenset_reg_t data)
{
	((Rtc *)hw)->MODE0.INTENSET.reg = data;
	((Rtc *)hw)->MODE0.INTENCLR.reg = ~data;
}

static inline void hri_rtcmode0_clear_INTEN_reg(const void *const hw, hri_rtcmode0_intenset_reg_t mask)
{
	((Rtc *)hw)->MODE0.INTENCLR.reg = mask;
}

static inline void hri_rtcmode1_set_INTEN_PER0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_PER0;
}

static inline bool hri_rtcmode1_get_INTEN_PER0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTENSET.reg & RTC_MODE1_INTENSET_PER0) >> RTC_MODE1_INTENSET_PER0_Pos;
}

static inline void hri_rtcmode1_write_INTEN_PER0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_PER0;
	} else {
		((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_PER0;
	}
}

static inline void hri_rtcmode1_clear_INTEN_PER0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_PER0;
}

static inline void hri_rtcmode1_set_INTEN_PER1_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_PER1;
}

static inline bool hri_rtcmode1_get_INTEN_PER1_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTENSET.reg & RTC_MODE1_INTENSET_PER1) >> RTC_MODE1_INTENSET_PER1_Pos;
}

static inline void hri_rtcmode1_write_INTEN_PER1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_PER1;
	} else {
		((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_PER1;
	}
}

static inline void hri_rtcmode1_clear_INTEN_PER1_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_PER1;
}

static inline void hri_rtcmode1_set_INTEN_PER2_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_PER2;
}

static inline bool hri_rtcmode1_get_INTEN_PER2_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTENSET.reg & RTC_MODE1_INTENSET_PER2) >> RTC_MODE1_INTENSET_PER2_Pos;
}

static inline void hri_rtcmode1_write_INTEN_PER2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_PER2;
	} else {
		((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_PER2;
	}
}

static inline void hri_rtcmode1_clear_INTEN_PER2_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_PER2;
}

static inline void hri_rtcmode1_set_INTEN_PER3_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_PER3;
}

static inline bool hri_rtcmode1_get_INTEN_PER3_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTENSET.reg & RTC_MODE1_INTENSET_PER3) >> RTC_MODE1_INTENSET_PER3_Pos;
}

static inline void hri_rtcmode1_write_INTEN_PER3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_PER3;
	} else {
		((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_PER3;
	}
}

static inline void hri_rtcmode1_clear_INTEN_PER3_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_PER3;
}

static inline void hri_rtcmode1_set_INTEN_PER4_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_PER4;
}

static inline bool hri_rtcmode1_get_INTEN_PER4_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTENSET.reg & RTC_MODE1_INTENSET_PER4) >> RTC_MODE1_INTENSET_PER4_Pos;
}

static inline void hri_rtcmode1_write_INTEN_PER4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_PER4;
	} else {
		((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_PER4;
	}
}

static inline void hri_rtcmode1_clear_INTEN_PER4_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_PER4;
}

static inline void hri_rtcmode1_set_INTEN_PER5_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_PER5;
}

static inline bool hri_rtcmode1_get_INTEN_PER5_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTENSET.reg & RTC_MODE1_INTENSET_PER5) >> RTC_MODE1_INTENSET_PER5_Pos;
}

static inline void hri_rtcmode1_write_INTEN_PER5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_PER5;
	} else {
		((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_PER5;
	}
}

static inline void hri_rtcmode1_clear_INTEN_PER5_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_PER5;
}

static inline void hri_rtcmode1_set_INTEN_PER6_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_PER6;
}

static inline bool hri_rtcmode1_get_INTEN_PER6_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTENSET.reg & RTC_MODE1_INTENSET_PER6) >> RTC_MODE1_INTENSET_PER6_Pos;
}

static inline void hri_rtcmode1_write_INTEN_PER6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_PER6;
	} else {
		((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_PER6;
	}
}

static inline void hri_rtcmode1_clear_INTEN_PER6_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_PER6;
}

static inline void hri_rtcmode1_set_INTEN_PER7_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_PER7;
}

static inline bool hri_rtcmode1_get_INTEN_PER7_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTENSET.reg & RTC_MODE1_INTENSET_PER7) >> RTC_MODE1_INTENSET_PER7_Pos;
}

static inline void hri_rtcmode1_write_INTEN_PER7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_PER7;
	} else {
		((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_PER7;
	}
}

static inline void hri_rtcmode1_clear_INTEN_PER7_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_PER7;
}

static inline void hri_rtcmode1_set_INTEN_CMP0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_CMP0;
}

static inline bool hri_rtcmode1_get_INTEN_CMP0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTENSET.reg & RTC_MODE1_INTENSET_CMP0) >> RTC_MODE1_INTENSET_CMP0_Pos;
}

static inline void hri_rtcmode1_write_INTEN_CMP0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_CMP0;
	} else {
		((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_CMP0;
	}
}

static inline void hri_rtcmode1_clear_INTEN_CMP0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_CMP0;
}

static inline void hri_rtcmode1_set_INTEN_CMP1_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_CMP1;
}

static inline bool hri_rtcmode1_get_INTEN_CMP1_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTENSET.reg & RTC_MODE1_INTENSET_CMP1) >> RTC_MODE1_INTENSET_CMP1_Pos;
}

static inline void hri_rtcmode1_write_INTEN_CMP1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_CMP1;
	} else {
		((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_CMP1;
	}
}

static inline void hri_rtcmode1_clear_INTEN_CMP1_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_CMP1;
}

static inline void hri_rtcmode1_set_INTEN_OVF_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_OVF;
}

static inline bool hri_rtcmode1_get_INTEN_OVF_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.INTENSET.reg & RTC_MODE1_INTENSET_OVF) >> RTC_MODE1_INTENSET_OVF_Pos;
}

static inline void hri_rtcmode1_write_INTEN_OVF_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_OVF;
	} else {
		((Rtc *)hw)->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_OVF;
	}
}

static inline void hri_rtcmode1_clear_INTEN_OVF_bit(const void *const hw)
{
	((Rtc *)hw)->MODE1.INTENCLR.reg = RTC_MODE1_INTENSET_OVF;
}

static inline void hri_rtcmode1_set_INTEN_reg(const void *const hw, hri_rtcmode1_intenset_reg_t mask)
{
	((Rtc *)hw)->MODE1.INTENSET.reg = mask;
}

static inline hri_rtcmode1_intenset_reg_t hri_rtcmode1_get_INTEN_reg(const void *const           hw,
                                                                     hri_rtcmode1_intenset_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE1.INTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_rtcmode1_intenset_reg_t hri_rtcmode1_read_INTEN_reg(const void *const hw)
{
	return ((Rtc *)hw)->MODE1.INTENSET.reg;
}

static inline void hri_rtcmode1_write_INTEN_reg(const void *const hw, hri_rtcmode1_intenset_reg_t data)
{
	((Rtc *)hw)->MODE1.INTENSET.reg = data;
	((Rtc *)hw)->MODE1.INTENCLR.reg = ~data;
}

static inline void hri_rtcmode1_clear_INTEN_reg(const void *const hw, hri_rtcmode1_intenset_reg_t mask)
{
	((Rtc *)hw)->MODE1.INTENCLR.reg = mask;
}

static inline void hri_rtcmode2_set_INTEN_PER0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_PER0;
}

static inline bool hri_rtcmode2_get_INTEN_PER0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTENSET.reg & RTC_MODE2_INTENSET_PER0) >> RTC_MODE2_INTENSET_PER0_Pos;
}

static inline void hri_rtcmode2_write_INTEN_PER0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_PER0;
	} else {
		((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_PER0;
	}
}

static inline void hri_rtcmode2_clear_INTEN_PER0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_PER0;
}

static inline void hri_rtcmode2_set_INTEN_PER1_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_PER1;
}

static inline bool hri_rtcmode2_get_INTEN_PER1_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTENSET.reg & RTC_MODE2_INTENSET_PER1) >> RTC_MODE2_INTENSET_PER1_Pos;
}

static inline void hri_rtcmode2_write_INTEN_PER1_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_PER1;
	} else {
		((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_PER1;
	}
}

static inline void hri_rtcmode2_clear_INTEN_PER1_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_PER1;
}

static inline void hri_rtcmode2_set_INTEN_PER2_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_PER2;
}

static inline bool hri_rtcmode2_get_INTEN_PER2_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTENSET.reg & RTC_MODE2_INTENSET_PER2) >> RTC_MODE2_INTENSET_PER2_Pos;
}

static inline void hri_rtcmode2_write_INTEN_PER2_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_PER2;
	} else {
		((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_PER2;
	}
}

static inline void hri_rtcmode2_clear_INTEN_PER2_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_PER2;
}

static inline void hri_rtcmode2_set_INTEN_PER3_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_PER3;
}

static inline bool hri_rtcmode2_get_INTEN_PER3_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTENSET.reg & RTC_MODE2_INTENSET_PER3) >> RTC_MODE2_INTENSET_PER3_Pos;
}

static inline void hri_rtcmode2_write_INTEN_PER3_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_PER3;
	} else {
		((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_PER3;
	}
}

static inline void hri_rtcmode2_clear_INTEN_PER3_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_PER3;
}

static inline void hri_rtcmode2_set_INTEN_PER4_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_PER4;
}

static inline bool hri_rtcmode2_get_INTEN_PER4_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTENSET.reg & RTC_MODE2_INTENSET_PER4) >> RTC_MODE2_INTENSET_PER4_Pos;
}

static inline void hri_rtcmode2_write_INTEN_PER4_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_PER4;
	} else {
		((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_PER4;
	}
}

static inline void hri_rtcmode2_clear_INTEN_PER4_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_PER4;
}

static inline void hri_rtcmode2_set_INTEN_PER5_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_PER5;
}

static inline bool hri_rtcmode2_get_INTEN_PER5_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTENSET.reg & RTC_MODE2_INTENSET_PER5) >> RTC_MODE2_INTENSET_PER5_Pos;
}

static inline void hri_rtcmode2_write_INTEN_PER5_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_PER5;
	} else {
		((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_PER5;
	}
}

static inline void hri_rtcmode2_clear_INTEN_PER5_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_PER5;
}

static inline void hri_rtcmode2_set_INTEN_PER6_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_PER6;
}

static inline bool hri_rtcmode2_get_INTEN_PER6_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTENSET.reg & RTC_MODE2_INTENSET_PER6) >> RTC_MODE2_INTENSET_PER6_Pos;
}

static inline void hri_rtcmode2_write_INTEN_PER6_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_PER6;
	} else {
		((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_PER6;
	}
}

static inline void hri_rtcmode2_clear_INTEN_PER6_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_PER6;
}

static inline void hri_rtcmode2_set_INTEN_PER7_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_PER7;
}

static inline bool hri_rtcmode2_get_INTEN_PER7_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTENSET.reg & RTC_MODE2_INTENSET_PER7) >> RTC_MODE2_INTENSET_PER7_Pos;
}

static inline void hri_rtcmode2_write_INTEN_PER7_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_PER7;
	} else {
		((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_PER7;
	}
}

static inline void hri_rtcmode2_clear_INTEN_PER7_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_PER7;
}

static inline void hri_rtcmode2_set_INTEN_ALARM0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_ALARM0;
}

static inline bool hri_rtcmode2_get_INTEN_ALARM0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTENSET.reg & RTC_MODE2_INTENSET_ALARM0) >> RTC_MODE2_INTENSET_ALARM0_Pos;
}

static inline void hri_rtcmode2_write_INTEN_ALARM0_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_ALARM0;
	} else {
		((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_ALARM0;
	}
}

static inline void hri_rtcmode2_clear_INTEN_ALARM0_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_ALARM0;
}

static inline void hri_rtcmode2_set_INTEN_OVF_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_OVF;
}

static inline bool hri_rtcmode2_get_INTEN_OVF_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.INTENSET.reg & RTC_MODE2_INTENSET_OVF) >> RTC_MODE2_INTENSET_OVF_Pos;
}

static inline void hri_rtcmode2_write_INTEN_OVF_bit(const void *const hw, bool value)
{
	if (value == 0x0) {
		((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_OVF;
	} else {
		((Rtc *)hw)->MODE2.INTENSET.reg = RTC_MODE2_INTENSET_OVF;
	}
}

static inline void hri_rtcmode2_clear_INTEN_OVF_bit(const void *const hw)
{
	((Rtc *)hw)->MODE2.INTENCLR.reg = RTC_MODE2_INTENSET_OVF;
}

static inline void hri_rtcmode2_set_INTEN_reg(const void *const hw, hri_rtcmode2_intenset_reg_t mask)
{
	((Rtc *)hw)->MODE2.INTENSET.reg = mask;
}

static inline hri_rtcmode2_intenset_reg_t hri_rtcmode2_get_INTEN_reg(const void *const           hw,
                                                                     hri_rtcmode2_intenset_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE2.INTENSET.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_rtcmode2_intenset_reg_t hri_rtcmode2_read_INTEN_reg(const void *const hw)
{
	return ((Rtc *)hw)->MODE2.INTENSET.reg;
}

static inline void hri_rtcmode2_write_INTEN_reg(const void *const hw, hri_rtcmode2_intenset_reg_t data)
{
	((Rtc *)hw)->MODE2.INTENSET.reg = data;
	((Rtc *)hw)->MODE2.INTENCLR.reg = ~data;
}

static inline void hri_rtcmode2_clear_INTEN_reg(const void *const hw, hri_rtcmode2_intenset_reg_t mask)
{
	((Rtc *)hw)->MODE2.INTENCLR.reg = mask;
}

static inline bool hri_rtcmode0_get_SYNCBUSY_SWRST_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.SYNCBUSY.reg & RTC_MODE0_SYNCBUSY_SWRST) >> RTC_MODE0_SYNCBUSY_SWRST_Pos;
}

static inline bool hri_rtcmode0_get_SYNCBUSY_ENABLE_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.SYNCBUSY.reg & RTC_MODE0_SYNCBUSY_ENABLE) >> RTC_MODE0_SYNCBUSY_ENABLE_Pos;
}

static inline bool hri_rtcmode0_get_SYNCBUSY_FREQCORR_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.SYNCBUSY.reg & RTC_MODE0_SYNCBUSY_FREQCORR) >> RTC_MODE0_SYNCBUSY_FREQCORR_Pos;
}

static inline bool hri_rtcmode0_get_SYNCBUSY_COUNT_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.SYNCBUSY.reg & RTC_MODE0_SYNCBUSY_COUNT) >> RTC_MODE0_SYNCBUSY_COUNT_Pos;
}

static inline bool hri_rtcmode0_get_SYNCBUSY_COMP0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.SYNCBUSY.reg & RTC_MODE0_SYNCBUSY_COMP0) >> RTC_MODE0_SYNCBUSY_COMP0_Pos;
}

static inline bool hri_rtcmode0_get_SYNCBUSY_COUNTSYNC_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE0.SYNCBUSY.reg & RTC_MODE0_SYNCBUSY_COUNTSYNC) >> RTC_MODE0_SYNCBUSY_COUNTSYNC_Pos;
}

static inline hri_rtcmode0_syncbusy_reg_t hri_rtcmode0_get_SYNCBUSY_reg(const void *const           hw,
                                                                        hri_rtcmode0_syncbusy_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE0.SYNCBUSY.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_rtcmode0_syncbusy_reg_t hri_rtcmode0_read_SYNCBUSY_reg(const void *const hw)
{
	return ((Rtc *)hw)->MODE0.SYNCBUSY.reg;
}

static inline bool hri_rtcmode1_get_SYNCBUSY_SWRST_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.SYNCBUSY.reg & RTC_MODE1_SYNCBUSY_SWRST) >> RTC_MODE1_SYNCBUSY_SWRST_Pos;
}

static inline bool hri_rtcmode1_get_SYNCBUSY_ENABLE_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.SYNCBUSY.reg & RTC_MODE1_SYNCBUSY_ENABLE) >> RTC_MODE1_SYNCBUSY_ENABLE_Pos;
}

static inline bool hri_rtcmode1_get_SYNCBUSY_FREQCORR_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.SYNCBUSY.reg & RTC_MODE1_SYNCBUSY_FREQCORR) >> RTC_MODE1_SYNCBUSY_FREQCORR_Pos;
}

static inline bool hri_rtcmode1_get_SYNCBUSY_COUNT_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.SYNCBUSY.reg & RTC_MODE1_SYNCBUSY_COUNT) >> RTC_MODE1_SYNCBUSY_COUNT_Pos;
}

static inline bool hri_rtcmode1_get_SYNCBUSY_PER_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.SYNCBUSY.reg & RTC_MODE1_SYNCBUSY_PER) >> RTC_MODE1_SYNCBUSY_PER_Pos;
}

static inline bool hri_rtcmode1_get_SYNCBUSY_COMP0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.SYNCBUSY.reg & RTC_MODE1_SYNCBUSY_COMP0) >> RTC_MODE1_SYNCBUSY_COMP0_Pos;
}

static inline bool hri_rtcmode1_get_SYNCBUSY_COMP1_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.SYNCBUSY.reg & RTC_MODE1_SYNCBUSY_COMP1) >> RTC_MODE1_SYNCBUSY_COMP1_Pos;
}

static inline bool hri_rtcmode1_get_SYNCBUSY_COUNTSYNC_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE1.SYNCBUSY.reg & RTC_MODE1_SYNCBUSY_COUNTSYNC) >> RTC_MODE1_SYNCBUSY_COUNTSYNC_Pos;
}

static inline hri_rtcmode1_syncbusy_reg_t hri_rtcmode1_get_SYNCBUSY_reg(const void *const           hw,
                                                                        hri_rtcmode1_syncbusy_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE1.SYNCBUSY.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_rtcmode1_syncbusy_reg_t hri_rtcmode1_read_SYNCBUSY_reg(const void *const hw)
{
	return ((Rtc *)hw)->MODE1.SYNCBUSY.reg;
}

static inline bool hri_rtcmode2_get_SYNCBUSY_SWRST_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.SYNCBUSY.reg & RTC_MODE2_SYNCBUSY_SWRST) >> RTC_MODE2_SYNCBUSY_SWRST_Pos;
}

static inline bool hri_rtcmode2_get_SYNCBUSY_ENABLE_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.SYNCBUSY.reg & RTC_MODE2_SYNCBUSY_ENABLE) >> RTC_MODE2_SYNCBUSY_ENABLE_Pos;
}

static inline bool hri_rtcmode2_get_SYNCBUSY_FREQCORR_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.SYNCBUSY.reg & RTC_MODE2_SYNCBUSY_FREQCORR) >> RTC_MODE2_SYNCBUSY_FREQCORR_Pos;
}

static inline bool hri_rtcmode2_get_SYNCBUSY_CLOCK_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.SYNCBUSY.reg & RTC_MODE2_SYNCBUSY_CLOCK) >> RTC_MODE2_SYNCBUSY_CLOCK_Pos;
}

static inline bool hri_rtcmode2_get_SYNCBUSY_ALARM0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.SYNCBUSY.reg & RTC_MODE2_SYNCBUSY_ALARM0) >> RTC_MODE2_SYNCBUSY_ALARM0_Pos;
}

static inline bool hri_rtcmode2_get_SYNCBUSY_MASK0_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.SYNCBUSY.reg & RTC_MODE2_SYNCBUSY_MASK0) >> RTC_MODE2_SYNCBUSY_MASK0_Pos;
}

static inline bool hri_rtcmode2_get_SYNCBUSY_CLOCKSYNC_bit(const void *const hw)
{
	return (((Rtc *)hw)->MODE2.SYNCBUSY.reg & RTC_MODE2_SYNCBUSY_CLOCKSYNC) >> RTC_MODE2_SYNCBUSY_CLOCKSYNC_Pos;
}

static inline hri_rtcmode2_syncbusy_reg_t hri_rtcmode2_get_SYNCBUSY_reg(const void *const           hw,
                                                                        hri_rtcmode2_syncbusy_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.SYNCBUSY.reg;
	tmp &= mask;
	return tmp;
}

static inline hri_rtcmode2_syncbusy_reg_t hri_rtcmode2_read_SYNCBUSY_reg(const void *const hw)
{
	return ((Rtc *)hw)->MODE2.SYNCBUSY.reg;
}

static inline void hri_rtcmode0_set_CTRLA_SWRST_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg |= RTC_MODE0_CTRLA_SWRST;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_SWRST);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode0_get_CTRLA_SWRST_bit(const void *const hw)
{
	uint16_t tmp;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_SWRST);
	tmp = ((Rtc *)hw)->MODE0.CTRLA.reg;
	tmp = (tmp & RTC_MODE0_CTRLA_SWRST) >> RTC_MODE0_CTRLA_SWRST_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode0_set_CTRLA_ENABLE_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg |= RTC_MODE0_CTRLA_ENABLE;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_SWRST | RTC_MODE0_SYNCBUSY_ENABLE | RTC_MODE0_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode0_get_CTRLA_ENABLE_bit(const void *const hw)
{
	uint16_t tmp;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_SWRST | RTC_MODE0_SYNCBUSY_ENABLE | RTC_MODE0_SYNCBUSY_COUNTSYNC);
	tmp = ((Rtc *)hw)->MODE0.CTRLA.reg;
	tmp = (tmp & RTC_MODE0_CTRLA_ENABLE) >> RTC_MODE0_CTRLA_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode0_write_CTRLA_ENABLE_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.CTRLA.reg;
	tmp &= ~RTC_MODE0_CTRLA_ENABLE;
	tmp |= value << RTC_MODE0_CTRLA_ENABLE_Pos;
	((Rtc *)hw)->MODE0.CTRLA.reg = tmp;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_SWRST | RTC_MODE0_SYNCBUSY_ENABLE | RTC_MODE0_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_CTRLA_ENABLE_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg &= ~RTC_MODE0_CTRLA_ENABLE;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_SWRST | RTC_MODE0_SYNCBUSY_ENABLE | RTC_MODE0_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_CTRLA_ENABLE_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg ^= RTC_MODE0_CTRLA_ENABLE;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_SWRST | RTC_MODE0_SYNCBUSY_ENABLE | RTC_MODE0_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_set_CTRLA_MATCHCLR_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg |= RTC_MODE0_CTRLA_MATCHCLR;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode0_get_CTRLA_MATCHCLR_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE0.CTRLA.reg;
	tmp = (tmp & RTC_MODE0_CTRLA_MATCHCLR) >> RTC_MODE0_CTRLA_MATCHCLR_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode0_write_CTRLA_MATCHCLR_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.CTRLA.reg;
	tmp &= ~RTC_MODE0_CTRLA_MATCHCLR;
	tmp |= value << RTC_MODE0_CTRLA_MATCHCLR_Pos;
	((Rtc *)hw)->MODE0.CTRLA.reg = tmp;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_CTRLA_MATCHCLR_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg &= ~RTC_MODE0_CTRLA_MATCHCLR;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_CTRLA_MATCHCLR_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg ^= RTC_MODE0_CTRLA_MATCHCLR;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_set_CTRLA_COUNTSYNC_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg |= RTC_MODE0_CTRLA_COUNTSYNC;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_SWRST | RTC_MODE0_SYNCBUSY_ENABLE | RTC_MODE0_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode0_get_CTRLA_COUNTSYNC_bit(const void *const hw)
{
	uint16_t tmp;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_SWRST | RTC_MODE0_SYNCBUSY_ENABLE | RTC_MODE0_SYNCBUSY_COUNTSYNC);
	tmp = ((Rtc *)hw)->MODE0.CTRLA.reg;
	tmp = (tmp & RTC_MODE0_CTRLA_COUNTSYNC) >> RTC_MODE0_CTRLA_COUNTSYNC_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode0_write_CTRLA_COUNTSYNC_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.CTRLA.reg;
	tmp &= ~RTC_MODE0_CTRLA_COUNTSYNC;
	tmp |= value << RTC_MODE0_CTRLA_COUNTSYNC_Pos;
	((Rtc *)hw)->MODE0.CTRLA.reg = tmp;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_SWRST | RTC_MODE0_SYNCBUSY_ENABLE | RTC_MODE0_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_CTRLA_COUNTSYNC_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg &= ~RTC_MODE0_CTRLA_COUNTSYNC;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_SWRST | RTC_MODE0_SYNCBUSY_ENABLE | RTC_MODE0_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_CTRLA_COUNTSYNC_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg ^= RTC_MODE0_CTRLA_COUNTSYNC;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_SWRST | RTC_MODE0_SYNCBUSY_ENABLE | RTC_MODE0_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_set_CTRLA_MODE_bf(const void *const hw, hri_rtcmode0_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg |= RTC_MODE0_CTRLA_MODE(mask);
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode0_ctrla_reg_t hri_rtcmode0_get_CTRLA_MODE_bf(const void *const        hw,
                                                                      hri_rtcmode0_ctrla_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE0.CTRLA.reg;
	tmp = (tmp & RTC_MODE0_CTRLA_MODE(mask)) >> RTC_MODE0_CTRLA_MODE_Pos;
	return tmp;
}

static inline void hri_rtcmode0_write_CTRLA_MODE_bf(const void *const hw, hri_rtcmode0_ctrla_reg_t data)
{
	uint16_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.CTRLA.reg;
	tmp &= ~RTC_MODE0_CTRLA_MODE_Msk;
	tmp |= RTC_MODE0_CTRLA_MODE(data);
	((Rtc *)hw)->MODE0.CTRLA.reg = tmp;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_CTRLA_MODE_bf(const void *const hw, hri_rtcmode0_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg &= ~RTC_MODE0_CTRLA_MODE(mask);
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_CTRLA_MODE_bf(const void *const hw, hri_rtcmode0_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg ^= RTC_MODE0_CTRLA_MODE(mask);
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode0_ctrla_reg_t hri_rtcmode0_read_CTRLA_MODE_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE0.CTRLA.reg;
	tmp = (tmp & RTC_MODE0_CTRLA_MODE_Msk) >> RTC_MODE0_CTRLA_MODE_Pos;
	return tmp;
}

static inline void hri_rtcmode0_set_CTRLA_PRESCALER_bf(const void *const hw, hri_rtcmode0_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg |= RTC_MODE0_CTRLA_PRESCALER(mask);
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode0_ctrla_reg_t hri_rtcmode0_get_CTRLA_PRESCALER_bf(const void *const        hw,
                                                                           hri_rtcmode0_ctrla_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE0.CTRLA.reg;
	tmp = (tmp & RTC_MODE0_CTRLA_PRESCALER(mask)) >> RTC_MODE0_CTRLA_PRESCALER_Pos;
	return tmp;
}

static inline void hri_rtcmode0_write_CTRLA_PRESCALER_bf(const void *const hw, hri_rtcmode0_ctrla_reg_t data)
{
	uint16_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.CTRLA.reg;
	tmp &= ~RTC_MODE0_CTRLA_PRESCALER_Msk;
	tmp |= RTC_MODE0_CTRLA_PRESCALER(data);
	((Rtc *)hw)->MODE0.CTRLA.reg = tmp;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_CTRLA_PRESCALER_bf(const void *const hw, hri_rtcmode0_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg &= ~RTC_MODE0_CTRLA_PRESCALER(mask);
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_CTRLA_PRESCALER_bf(const void *const hw, hri_rtcmode0_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg ^= RTC_MODE0_CTRLA_PRESCALER(mask);
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode0_ctrla_reg_t hri_rtcmode0_read_CTRLA_PRESCALER_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE0.CTRLA.reg;
	tmp = (tmp & RTC_MODE0_CTRLA_PRESCALER_Msk) >> RTC_MODE0_CTRLA_PRESCALER_Pos;
	return tmp;
}

static inline void hri_rtcmode0_set_CTRLA_reg(const void *const hw, hri_rtcmode0_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg |= mask;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_SWRST | RTC_MODE0_SYNCBUSY_ENABLE | RTC_MODE0_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode0_ctrla_reg_t hri_rtcmode0_get_CTRLA_reg(const void *const hw, hri_rtcmode0_ctrla_reg_t mask)
{
	uint16_t tmp;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_SWRST | RTC_MODE0_SYNCBUSY_ENABLE | RTC_MODE0_SYNCBUSY_COUNTSYNC);
	tmp = ((Rtc *)hw)->MODE0.CTRLA.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtcmode0_write_CTRLA_reg(const void *const hw, hri_rtcmode0_ctrla_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg = data;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_SWRST | RTC_MODE0_SYNCBUSY_ENABLE | RTC_MODE0_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_CTRLA_reg(const void *const hw, hri_rtcmode0_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg &= ~mask;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_SWRST | RTC_MODE0_SYNCBUSY_ENABLE | RTC_MODE0_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_CTRLA_reg(const void *const hw, hri_rtcmode0_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.CTRLA.reg ^= mask;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_SWRST | RTC_MODE0_SYNCBUSY_ENABLE | RTC_MODE0_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode0_ctrla_reg_t hri_rtcmode0_read_CTRLA_reg(const void *const hw)
{
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_SWRST | RTC_MODE0_SYNCBUSY_ENABLE | RTC_MODE0_SYNCBUSY_COUNTSYNC);
	return ((Rtc *)hw)->MODE0.CTRLA.reg;
}

static inline void hri_rtcmode1_set_CTRLA_SWRST_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.CTRLA.reg |= RTC_MODE1_CTRLA_SWRST;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_SWRST);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode1_get_CTRLA_SWRST_bit(const void *const hw)
{
	uint16_t tmp;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_SWRST);
	tmp = ((Rtc *)hw)->MODE1.CTRLA.reg;
	tmp = (tmp & RTC_MODE1_CTRLA_SWRST) >> RTC_MODE1_CTRLA_SWRST_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode1_set_CTRLA_ENABLE_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.CTRLA.reg |= RTC_MODE1_CTRLA_ENABLE;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_SWRST | RTC_MODE1_SYNCBUSY_ENABLE | RTC_MODE1_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode1_get_CTRLA_ENABLE_bit(const void *const hw)
{
	uint16_t tmp;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_SWRST | RTC_MODE1_SYNCBUSY_ENABLE | RTC_MODE1_SYNCBUSY_COUNTSYNC);
	tmp = ((Rtc *)hw)->MODE1.CTRLA.reg;
	tmp = (tmp & RTC_MODE1_CTRLA_ENABLE) >> RTC_MODE1_CTRLA_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode1_write_CTRLA_ENABLE_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE1.CTRLA.reg;
	tmp &= ~RTC_MODE1_CTRLA_ENABLE;
	tmp |= value << RTC_MODE1_CTRLA_ENABLE_Pos;
	((Rtc *)hw)->MODE1.CTRLA.reg = tmp;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_SWRST | RTC_MODE1_SYNCBUSY_ENABLE | RTC_MODE1_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_CTRLA_ENABLE_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.CTRLA.reg &= ~RTC_MODE1_CTRLA_ENABLE;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_SWRST | RTC_MODE1_SYNCBUSY_ENABLE | RTC_MODE1_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_CTRLA_ENABLE_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.CTRLA.reg ^= RTC_MODE1_CTRLA_ENABLE;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_SWRST | RTC_MODE1_SYNCBUSY_ENABLE | RTC_MODE1_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_set_CTRLA_COUNTSYNC_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.CTRLA.reg |= RTC_MODE1_CTRLA_COUNTSYNC;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_SWRST | RTC_MODE1_SYNCBUSY_ENABLE | RTC_MODE1_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode1_get_CTRLA_COUNTSYNC_bit(const void *const hw)
{
	uint16_t tmp;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_SWRST | RTC_MODE1_SYNCBUSY_ENABLE | RTC_MODE1_SYNCBUSY_COUNTSYNC);
	tmp = ((Rtc *)hw)->MODE1.CTRLA.reg;
	tmp = (tmp & RTC_MODE1_CTRLA_COUNTSYNC) >> RTC_MODE1_CTRLA_COUNTSYNC_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode1_write_CTRLA_COUNTSYNC_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE1.CTRLA.reg;
	tmp &= ~RTC_MODE1_CTRLA_COUNTSYNC;
	tmp |= value << RTC_MODE1_CTRLA_COUNTSYNC_Pos;
	((Rtc *)hw)->MODE1.CTRLA.reg = tmp;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_SWRST | RTC_MODE1_SYNCBUSY_ENABLE | RTC_MODE1_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_CTRLA_COUNTSYNC_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.CTRLA.reg &= ~RTC_MODE1_CTRLA_COUNTSYNC;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_SWRST | RTC_MODE1_SYNCBUSY_ENABLE | RTC_MODE1_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_CTRLA_COUNTSYNC_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.CTRLA.reg ^= RTC_MODE1_CTRLA_COUNTSYNC;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_SWRST | RTC_MODE1_SYNCBUSY_ENABLE | RTC_MODE1_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_set_CTRLA_MODE_bf(const void *const hw, hri_rtcmode1_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.CTRLA.reg |= RTC_MODE1_CTRLA_MODE(mask);
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_ctrla_reg_t hri_rtcmode1_get_CTRLA_MODE_bf(const void *const        hw,
                                                                      hri_rtcmode1_ctrla_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE1.CTRLA.reg;
	tmp = (tmp & RTC_MODE1_CTRLA_MODE(mask)) >> RTC_MODE1_CTRLA_MODE_Pos;
	return tmp;
}

static inline void hri_rtcmode1_write_CTRLA_MODE_bf(const void *const hw, hri_rtcmode1_ctrla_reg_t data)
{
	uint16_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE1.CTRLA.reg;
	tmp &= ~RTC_MODE1_CTRLA_MODE_Msk;
	tmp |= RTC_MODE1_CTRLA_MODE(data);
	((Rtc *)hw)->MODE1.CTRLA.reg = tmp;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_CTRLA_MODE_bf(const void *const hw, hri_rtcmode1_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.CTRLA.reg &= ~RTC_MODE1_CTRLA_MODE(mask);
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_CTRLA_MODE_bf(const void *const hw, hri_rtcmode1_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.CTRLA.reg ^= RTC_MODE1_CTRLA_MODE(mask);
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_ctrla_reg_t hri_rtcmode1_read_CTRLA_MODE_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE1.CTRLA.reg;
	tmp = (tmp & RTC_MODE1_CTRLA_MODE_Msk) >> RTC_MODE1_CTRLA_MODE_Pos;
	return tmp;
}

static inline void hri_rtcmode1_set_CTRLA_PRESCALER_bf(const void *const hw, hri_rtcmode1_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.CTRLA.reg |= RTC_MODE1_CTRLA_PRESCALER(mask);
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_ctrla_reg_t hri_rtcmode1_get_CTRLA_PRESCALER_bf(const void *const        hw,
                                                                           hri_rtcmode1_ctrla_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE1.CTRLA.reg;
	tmp = (tmp & RTC_MODE1_CTRLA_PRESCALER(mask)) >> RTC_MODE1_CTRLA_PRESCALER_Pos;
	return tmp;
}

static inline void hri_rtcmode1_write_CTRLA_PRESCALER_bf(const void *const hw, hri_rtcmode1_ctrla_reg_t data)
{
	uint16_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE1.CTRLA.reg;
	tmp &= ~RTC_MODE1_CTRLA_PRESCALER_Msk;
	tmp |= RTC_MODE1_CTRLA_PRESCALER(data);
	((Rtc *)hw)->MODE1.CTRLA.reg = tmp;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_CTRLA_PRESCALER_bf(const void *const hw, hri_rtcmode1_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.CTRLA.reg &= ~RTC_MODE1_CTRLA_PRESCALER(mask);
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_CTRLA_PRESCALER_bf(const void *const hw, hri_rtcmode1_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.CTRLA.reg ^= RTC_MODE1_CTRLA_PRESCALER(mask);
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_ctrla_reg_t hri_rtcmode1_read_CTRLA_PRESCALER_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE1.CTRLA.reg;
	tmp = (tmp & RTC_MODE1_CTRLA_PRESCALER_Msk) >> RTC_MODE1_CTRLA_PRESCALER_Pos;
	return tmp;
}

static inline void hri_rtcmode1_set_CTRLA_reg(const void *const hw, hri_rtcmode1_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.CTRLA.reg |= mask;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_SWRST | RTC_MODE1_SYNCBUSY_ENABLE | RTC_MODE1_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_ctrla_reg_t hri_rtcmode1_get_CTRLA_reg(const void *const hw, hri_rtcmode1_ctrla_reg_t mask)
{
	uint16_t tmp;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_SWRST | RTC_MODE1_SYNCBUSY_ENABLE | RTC_MODE1_SYNCBUSY_COUNTSYNC);
	tmp = ((Rtc *)hw)->MODE1.CTRLA.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtcmode1_write_CTRLA_reg(const void *const hw, hri_rtcmode1_ctrla_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.CTRLA.reg = data;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_SWRST | RTC_MODE1_SYNCBUSY_ENABLE | RTC_MODE1_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_CTRLA_reg(const void *const hw, hri_rtcmode1_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.CTRLA.reg &= ~mask;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_SWRST | RTC_MODE1_SYNCBUSY_ENABLE | RTC_MODE1_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_CTRLA_reg(const void *const hw, hri_rtcmode1_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.CTRLA.reg ^= mask;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_SWRST | RTC_MODE1_SYNCBUSY_ENABLE | RTC_MODE1_SYNCBUSY_COUNTSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_ctrla_reg_t hri_rtcmode1_read_CTRLA_reg(const void *const hw)
{
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_SWRST | RTC_MODE1_SYNCBUSY_ENABLE | RTC_MODE1_SYNCBUSY_COUNTSYNC);
	return ((Rtc *)hw)->MODE1.CTRLA.reg;
}

static inline void hri_rtcmode2_set_CTRLA_SWRST_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg |= RTC_MODE2_CTRLA_SWRST;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_SWRST);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode2_get_CTRLA_SWRST_bit(const void *const hw)
{
	uint16_t tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_SWRST);
	tmp = ((Rtc *)hw)->MODE2.CTRLA.reg;
	tmp = (tmp & RTC_MODE2_CTRLA_SWRST) >> RTC_MODE2_CTRLA_SWRST_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode2_set_CTRLA_ENABLE_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg |= RTC_MODE2_CTRLA_ENABLE;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_SWRST | RTC_MODE2_SYNCBUSY_ENABLE | RTC_MODE2_SYNCBUSY_CLOCKSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode2_get_CTRLA_ENABLE_bit(const void *const hw)
{
	uint16_t tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_SWRST | RTC_MODE2_SYNCBUSY_ENABLE | RTC_MODE2_SYNCBUSY_CLOCKSYNC);
	tmp = ((Rtc *)hw)->MODE2.CTRLA.reg;
	tmp = (tmp & RTC_MODE2_CTRLA_ENABLE) >> RTC_MODE2_CTRLA_ENABLE_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode2_write_CTRLA_ENABLE_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.CTRLA.reg;
	tmp &= ~RTC_MODE2_CTRLA_ENABLE;
	tmp |= value << RTC_MODE2_CTRLA_ENABLE_Pos;
	((Rtc *)hw)->MODE2.CTRLA.reg = tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_SWRST | RTC_MODE2_SYNCBUSY_ENABLE | RTC_MODE2_SYNCBUSY_CLOCKSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_CTRLA_ENABLE_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg &= ~RTC_MODE2_CTRLA_ENABLE;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_SWRST | RTC_MODE2_SYNCBUSY_ENABLE | RTC_MODE2_SYNCBUSY_CLOCKSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_CTRLA_ENABLE_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg ^= RTC_MODE2_CTRLA_ENABLE;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_SWRST | RTC_MODE2_SYNCBUSY_ENABLE | RTC_MODE2_SYNCBUSY_CLOCKSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_set_CTRLA_CLKREP_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg |= RTC_MODE2_CTRLA_CLKREP;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode2_get_CTRLA_CLKREP_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE2.CTRLA.reg;
	tmp = (tmp & RTC_MODE2_CTRLA_CLKREP) >> RTC_MODE2_CTRLA_CLKREP_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode2_write_CTRLA_CLKREP_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.CTRLA.reg;
	tmp &= ~RTC_MODE2_CTRLA_CLKREP;
	tmp |= value << RTC_MODE2_CTRLA_CLKREP_Pos;
	((Rtc *)hw)->MODE2.CTRLA.reg = tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_CTRLA_CLKREP_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg &= ~RTC_MODE2_CTRLA_CLKREP;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_CTRLA_CLKREP_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg ^= RTC_MODE2_CTRLA_CLKREP;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_set_CTRLA_MATCHCLR_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg |= RTC_MODE2_CTRLA_MATCHCLR;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode2_get_CTRLA_MATCHCLR_bit(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE2.CTRLA.reg;
	tmp = (tmp & RTC_MODE2_CTRLA_MATCHCLR) >> RTC_MODE2_CTRLA_MATCHCLR_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode2_write_CTRLA_MATCHCLR_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.CTRLA.reg;
	tmp &= ~RTC_MODE2_CTRLA_MATCHCLR;
	tmp |= value << RTC_MODE2_CTRLA_MATCHCLR_Pos;
	((Rtc *)hw)->MODE2.CTRLA.reg = tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_CTRLA_MATCHCLR_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg &= ~RTC_MODE2_CTRLA_MATCHCLR;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_CTRLA_MATCHCLR_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg ^= RTC_MODE2_CTRLA_MATCHCLR;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_set_CTRLA_CLOCKSYNC_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg |= RTC_MODE2_CTRLA_CLOCKSYNC;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_SWRST | RTC_MODE2_SYNCBUSY_ENABLE | RTC_MODE2_SYNCBUSY_CLOCKSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode2_get_CTRLA_CLOCKSYNC_bit(const void *const hw)
{
	uint16_t tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_SWRST | RTC_MODE2_SYNCBUSY_ENABLE | RTC_MODE2_SYNCBUSY_CLOCKSYNC);
	tmp = ((Rtc *)hw)->MODE2.CTRLA.reg;
	tmp = (tmp & RTC_MODE2_CTRLA_CLOCKSYNC) >> RTC_MODE2_CTRLA_CLOCKSYNC_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode2_write_CTRLA_CLOCKSYNC_bit(const void *const hw, bool value)
{
	uint16_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.CTRLA.reg;
	tmp &= ~RTC_MODE2_CTRLA_CLOCKSYNC;
	tmp |= value << RTC_MODE2_CTRLA_CLOCKSYNC_Pos;
	((Rtc *)hw)->MODE2.CTRLA.reg = tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_SWRST | RTC_MODE2_SYNCBUSY_ENABLE | RTC_MODE2_SYNCBUSY_CLOCKSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_CTRLA_CLOCKSYNC_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg &= ~RTC_MODE2_CTRLA_CLOCKSYNC;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_SWRST | RTC_MODE2_SYNCBUSY_ENABLE | RTC_MODE2_SYNCBUSY_CLOCKSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_CTRLA_CLOCKSYNC_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg ^= RTC_MODE2_CTRLA_CLOCKSYNC;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_SWRST | RTC_MODE2_SYNCBUSY_ENABLE | RTC_MODE2_SYNCBUSY_CLOCKSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_set_CTRLA_MODE_bf(const void *const hw, hri_rtcmode2_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg |= RTC_MODE2_CTRLA_MODE(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_ctrla_reg_t hri_rtcmode2_get_CTRLA_MODE_bf(const void *const        hw,
                                                                      hri_rtcmode2_ctrla_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE2.CTRLA.reg;
	tmp = (tmp & RTC_MODE2_CTRLA_MODE(mask)) >> RTC_MODE2_CTRLA_MODE_Pos;
	return tmp;
}

static inline void hri_rtcmode2_write_CTRLA_MODE_bf(const void *const hw, hri_rtcmode2_ctrla_reg_t data)
{
	uint16_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.CTRLA.reg;
	tmp &= ~RTC_MODE2_CTRLA_MODE_Msk;
	tmp |= RTC_MODE2_CTRLA_MODE(data);
	((Rtc *)hw)->MODE2.CTRLA.reg = tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_CTRLA_MODE_bf(const void *const hw, hri_rtcmode2_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg &= ~RTC_MODE2_CTRLA_MODE(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_CTRLA_MODE_bf(const void *const hw, hri_rtcmode2_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg ^= RTC_MODE2_CTRLA_MODE(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_ctrla_reg_t hri_rtcmode2_read_CTRLA_MODE_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE2.CTRLA.reg;
	tmp = (tmp & RTC_MODE2_CTRLA_MODE_Msk) >> RTC_MODE2_CTRLA_MODE_Pos;
	return tmp;
}

static inline void hri_rtcmode2_set_CTRLA_PRESCALER_bf(const void *const hw, hri_rtcmode2_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg |= RTC_MODE2_CTRLA_PRESCALER(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_ctrla_reg_t hri_rtcmode2_get_CTRLA_PRESCALER_bf(const void *const        hw,
                                                                           hri_rtcmode2_ctrla_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE2.CTRLA.reg;
	tmp = (tmp & RTC_MODE2_CTRLA_PRESCALER(mask)) >> RTC_MODE2_CTRLA_PRESCALER_Pos;
	return tmp;
}

static inline void hri_rtcmode2_write_CTRLA_PRESCALER_bf(const void *const hw, hri_rtcmode2_ctrla_reg_t data)
{
	uint16_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.CTRLA.reg;
	tmp &= ~RTC_MODE2_CTRLA_PRESCALER_Msk;
	tmp |= RTC_MODE2_CTRLA_PRESCALER(data);
	((Rtc *)hw)->MODE2.CTRLA.reg = tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_CTRLA_PRESCALER_bf(const void *const hw, hri_rtcmode2_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg &= ~RTC_MODE2_CTRLA_PRESCALER(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_CTRLA_PRESCALER_bf(const void *const hw, hri_rtcmode2_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg ^= RTC_MODE2_CTRLA_PRESCALER(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_ctrla_reg_t hri_rtcmode2_read_CTRLA_PRESCALER_bf(const void *const hw)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE2.CTRLA.reg;
	tmp = (tmp & RTC_MODE2_CTRLA_PRESCALER_Msk) >> RTC_MODE2_CTRLA_PRESCALER_Pos;
	return tmp;
}

static inline void hri_rtcmode2_set_CTRLA_reg(const void *const hw, hri_rtcmode2_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg |= mask;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_SWRST | RTC_MODE2_SYNCBUSY_ENABLE | RTC_MODE2_SYNCBUSY_CLOCKSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_ctrla_reg_t hri_rtcmode2_get_CTRLA_reg(const void *const hw, hri_rtcmode2_ctrla_reg_t mask)
{
	uint16_t tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_SWRST | RTC_MODE2_SYNCBUSY_ENABLE | RTC_MODE2_SYNCBUSY_CLOCKSYNC);
	tmp = ((Rtc *)hw)->MODE2.CTRLA.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtcmode2_write_CTRLA_reg(const void *const hw, hri_rtcmode2_ctrla_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg = data;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_SWRST | RTC_MODE2_SYNCBUSY_ENABLE | RTC_MODE2_SYNCBUSY_CLOCKSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_CTRLA_reg(const void *const hw, hri_rtcmode2_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg &= ~mask;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_SWRST | RTC_MODE2_SYNCBUSY_ENABLE | RTC_MODE2_SYNCBUSY_CLOCKSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_CTRLA_reg(const void *const hw, hri_rtcmode2_ctrla_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CTRLA.reg ^= mask;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_SWRST | RTC_MODE2_SYNCBUSY_ENABLE | RTC_MODE2_SYNCBUSY_CLOCKSYNC);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_ctrla_reg_t hri_rtcmode2_read_CTRLA_reg(const void *const hw)
{
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_SWRST | RTC_MODE2_SYNCBUSY_ENABLE | RTC_MODE2_SYNCBUSY_CLOCKSYNC);
	return ((Rtc *)hw)->MODE2.CTRLA.reg;
}

static inline void hri_rtcmode0_set_EVCTRL_PEREO0_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg |= RTC_MODE0_EVCTRL_PEREO0;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode0_get_EVCTRL_PEREO0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp = (tmp & RTC_MODE0_EVCTRL_PEREO0) >> RTC_MODE0_EVCTRL_PEREO0_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode0_write_EVCTRL_PEREO0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp &= ~RTC_MODE0_EVCTRL_PEREO0;
	tmp |= value << RTC_MODE0_EVCTRL_PEREO0_Pos;
	((Rtc *)hw)->MODE0.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_EVCTRL_PEREO0_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg &= ~RTC_MODE0_EVCTRL_PEREO0;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_EVCTRL_PEREO0_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg ^= RTC_MODE0_EVCTRL_PEREO0;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_set_EVCTRL_PEREO1_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg |= RTC_MODE0_EVCTRL_PEREO1;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode0_get_EVCTRL_PEREO1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp = (tmp & RTC_MODE0_EVCTRL_PEREO1) >> RTC_MODE0_EVCTRL_PEREO1_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode0_write_EVCTRL_PEREO1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp &= ~RTC_MODE0_EVCTRL_PEREO1;
	tmp |= value << RTC_MODE0_EVCTRL_PEREO1_Pos;
	((Rtc *)hw)->MODE0.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_EVCTRL_PEREO1_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg &= ~RTC_MODE0_EVCTRL_PEREO1;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_EVCTRL_PEREO1_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg ^= RTC_MODE0_EVCTRL_PEREO1;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_set_EVCTRL_PEREO2_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg |= RTC_MODE0_EVCTRL_PEREO2;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode0_get_EVCTRL_PEREO2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp = (tmp & RTC_MODE0_EVCTRL_PEREO2) >> RTC_MODE0_EVCTRL_PEREO2_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode0_write_EVCTRL_PEREO2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp &= ~RTC_MODE0_EVCTRL_PEREO2;
	tmp |= value << RTC_MODE0_EVCTRL_PEREO2_Pos;
	((Rtc *)hw)->MODE0.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_EVCTRL_PEREO2_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg &= ~RTC_MODE0_EVCTRL_PEREO2;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_EVCTRL_PEREO2_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg ^= RTC_MODE0_EVCTRL_PEREO2;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_set_EVCTRL_PEREO3_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg |= RTC_MODE0_EVCTRL_PEREO3;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode0_get_EVCTRL_PEREO3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp = (tmp & RTC_MODE0_EVCTRL_PEREO3) >> RTC_MODE0_EVCTRL_PEREO3_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode0_write_EVCTRL_PEREO3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp &= ~RTC_MODE0_EVCTRL_PEREO3;
	tmp |= value << RTC_MODE0_EVCTRL_PEREO3_Pos;
	((Rtc *)hw)->MODE0.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_EVCTRL_PEREO3_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg &= ~RTC_MODE0_EVCTRL_PEREO3;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_EVCTRL_PEREO3_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg ^= RTC_MODE0_EVCTRL_PEREO3;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_set_EVCTRL_PEREO4_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg |= RTC_MODE0_EVCTRL_PEREO4;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode0_get_EVCTRL_PEREO4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp = (tmp & RTC_MODE0_EVCTRL_PEREO4) >> RTC_MODE0_EVCTRL_PEREO4_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode0_write_EVCTRL_PEREO4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp &= ~RTC_MODE0_EVCTRL_PEREO4;
	tmp |= value << RTC_MODE0_EVCTRL_PEREO4_Pos;
	((Rtc *)hw)->MODE0.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_EVCTRL_PEREO4_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg &= ~RTC_MODE0_EVCTRL_PEREO4;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_EVCTRL_PEREO4_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg ^= RTC_MODE0_EVCTRL_PEREO4;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_set_EVCTRL_PEREO5_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg |= RTC_MODE0_EVCTRL_PEREO5;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode0_get_EVCTRL_PEREO5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp = (tmp & RTC_MODE0_EVCTRL_PEREO5) >> RTC_MODE0_EVCTRL_PEREO5_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode0_write_EVCTRL_PEREO5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp &= ~RTC_MODE0_EVCTRL_PEREO5;
	tmp |= value << RTC_MODE0_EVCTRL_PEREO5_Pos;
	((Rtc *)hw)->MODE0.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_EVCTRL_PEREO5_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg &= ~RTC_MODE0_EVCTRL_PEREO5;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_EVCTRL_PEREO5_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg ^= RTC_MODE0_EVCTRL_PEREO5;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_set_EVCTRL_PEREO6_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg |= RTC_MODE0_EVCTRL_PEREO6;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode0_get_EVCTRL_PEREO6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp = (tmp & RTC_MODE0_EVCTRL_PEREO6) >> RTC_MODE0_EVCTRL_PEREO6_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode0_write_EVCTRL_PEREO6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp &= ~RTC_MODE0_EVCTRL_PEREO6;
	tmp |= value << RTC_MODE0_EVCTRL_PEREO6_Pos;
	((Rtc *)hw)->MODE0.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_EVCTRL_PEREO6_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg &= ~RTC_MODE0_EVCTRL_PEREO6;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_EVCTRL_PEREO6_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg ^= RTC_MODE0_EVCTRL_PEREO6;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_set_EVCTRL_PEREO7_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg |= RTC_MODE0_EVCTRL_PEREO7;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode0_get_EVCTRL_PEREO7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp = (tmp & RTC_MODE0_EVCTRL_PEREO7) >> RTC_MODE0_EVCTRL_PEREO7_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode0_write_EVCTRL_PEREO7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp &= ~RTC_MODE0_EVCTRL_PEREO7;
	tmp |= value << RTC_MODE0_EVCTRL_PEREO7_Pos;
	((Rtc *)hw)->MODE0.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_EVCTRL_PEREO7_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg &= ~RTC_MODE0_EVCTRL_PEREO7;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_EVCTRL_PEREO7_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg ^= RTC_MODE0_EVCTRL_PEREO7;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_set_EVCTRL_CMPEO0_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg |= RTC_MODE0_EVCTRL_CMPEO0;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode0_get_EVCTRL_CMPEO0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp = (tmp & RTC_MODE0_EVCTRL_CMPEO0) >> RTC_MODE0_EVCTRL_CMPEO0_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode0_write_EVCTRL_CMPEO0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp &= ~RTC_MODE0_EVCTRL_CMPEO0;
	tmp |= value << RTC_MODE0_EVCTRL_CMPEO0_Pos;
	((Rtc *)hw)->MODE0.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_EVCTRL_CMPEO0_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg &= ~RTC_MODE0_EVCTRL_CMPEO0;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_EVCTRL_CMPEO0_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg ^= RTC_MODE0_EVCTRL_CMPEO0;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_set_EVCTRL_OVFEO_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg |= RTC_MODE0_EVCTRL_OVFEO;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode0_get_EVCTRL_OVFEO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp = (tmp & RTC_MODE0_EVCTRL_OVFEO) >> RTC_MODE0_EVCTRL_OVFEO_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode0_write_EVCTRL_OVFEO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp &= ~RTC_MODE0_EVCTRL_OVFEO;
	tmp |= value << RTC_MODE0_EVCTRL_OVFEO_Pos;
	((Rtc *)hw)->MODE0.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_EVCTRL_OVFEO_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg &= ~RTC_MODE0_EVCTRL_OVFEO;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_EVCTRL_OVFEO_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg ^= RTC_MODE0_EVCTRL_OVFEO;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_set_EVCTRL_reg(const void *const hw, hri_rtcmode0_evctrl_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg |= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode0_evctrl_reg_t hri_rtcmode0_get_EVCTRL_reg(const void *const         hw,
                                                                    hri_rtcmode0_evctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE0.EVCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtcmode0_write_EVCTRL_reg(const void *const hw, hri_rtcmode0_evctrl_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg = data;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_EVCTRL_reg(const void *const hw, hri_rtcmode0_evctrl_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg &= ~mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_EVCTRL_reg(const void *const hw, hri_rtcmode0_evctrl_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.EVCTRL.reg ^= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode0_evctrl_reg_t hri_rtcmode0_read_EVCTRL_reg(const void *const hw)
{
	return ((Rtc *)hw)->MODE0.EVCTRL.reg;
}

static inline void hri_rtcmode1_set_EVCTRL_PEREO0_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg |= RTC_MODE1_EVCTRL_PEREO0;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode1_get_EVCTRL_PEREO0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp = (tmp & RTC_MODE1_EVCTRL_PEREO0) >> RTC_MODE1_EVCTRL_PEREO0_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode1_write_EVCTRL_PEREO0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp &= ~RTC_MODE1_EVCTRL_PEREO0;
	tmp |= value << RTC_MODE1_EVCTRL_PEREO0_Pos;
	((Rtc *)hw)->MODE1.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_EVCTRL_PEREO0_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg &= ~RTC_MODE1_EVCTRL_PEREO0;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_EVCTRL_PEREO0_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg ^= RTC_MODE1_EVCTRL_PEREO0;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_set_EVCTRL_PEREO1_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg |= RTC_MODE1_EVCTRL_PEREO1;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode1_get_EVCTRL_PEREO1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp = (tmp & RTC_MODE1_EVCTRL_PEREO1) >> RTC_MODE1_EVCTRL_PEREO1_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode1_write_EVCTRL_PEREO1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp &= ~RTC_MODE1_EVCTRL_PEREO1;
	tmp |= value << RTC_MODE1_EVCTRL_PEREO1_Pos;
	((Rtc *)hw)->MODE1.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_EVCTRL_PEREO1_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg &= ~RTC_MODE1_EVCTRL_PEREO1;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_EVCTRL_PEREO1_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg ^= RTC_MODE1_EVCTRL_PEREO1;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_set_EVCTRL_PEREO2_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg |= RTC_MODE1_EVCTRL_PEREO2;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode1_get_EVCTRL_PEREO2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp = (tmp & RTC_MODE1_EVCTRL_PEREO2) >> RTC_MODE1_EVCTRL_PEREO2_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode1_write_EVCTRL_PEREO2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp &= ~RTC_MODE1_EVCTRL_PEREO2;
	tmp |= value << RTC_MODE1_EVCTRL_PEREO2_Pos;
	((Rtc *)hw)->MODE1.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_EVCTRL_PEREO2_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg &= ~RTC_MODE1_EVCTRL_PEREO2;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_EVCTRL_PEREO2_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg ^= RTC_MODE1_EVCTRL_PEREO2;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_set_EVCTRL_PEREO3_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg |= RTC_MODE1_EVCTRL_PEREO3;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode1_get_EVCTRL_PEREO3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp = (tmp & RTC_MODE1_EVCTRL_PEREO3) >> RTC_MODE1_EVCTRL_PEREO3_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode1_write_EVCTRL_PEREO3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp &= ~RTC_MODE1_EVCTRL_PEREO3;
	tmp |= value << RTC_MODE1_EVCTRL_PEREO3_Pos;
	((Rtc *)hw)->MODE1.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_EVCTRL_PEREO3_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg &= ~RTC_MODE1_EVCTRL_PEREO3;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_EVCTRL_PEREO3_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg ^= RTC_MODE1_EVCTRL_PEREO3;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_set_EVCTRL_PEREO4_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg |= RTC_MODE1_EVCTRL_PEREO4;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode1_get_EVCTRL_PEREO4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp = (tmp & RTC_MODE1_EVCTRL_PEREO4) >> RTC_MODE1_EVCTRL_PEREO4_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode1_write_EVCTRL_PEREO4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp &= ~RTC_MODE1_EVCTRL_PEREO4;
	tmp |= value << RTC_MODE1_EVCTRL_PEREO4_Pos;
	((Rtc *)hw)->MODE1.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_EVCTRL_PEREO4_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg &= ~RTC_MODE1_EVCTRL_PEREO4;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_EVCTRL_PEREO4_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg ^= RTC_MODE1_EVCTRL_PEREO4;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_set_EVCTRL_PEREO5_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg |= RTC_MODE1_EVCTRL_PEREO5;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode1_get_EVCTRL_PEREO5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp = (tmp & RTC_MODE1_EVCTRL_PEREO5) >> RTC_MODE1_EVCTRL_PEREO5_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode1_write_EVCTRL_PEREO5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp &= ~RTC_MODE1_EVCTRL_PEREO5;
	tmp |= value << RTC_MODE1_EVCTRL_PEREO5_Pos;
	((Rtc *)hw)->MODE1.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_EVCTRL_PEREO5_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg &= ~RTC_MODE1_EVCTRL_PEREO5;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_EVCTRL_PEREO5_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg ^= RTC_MODE1_EVCTRL_PEREO5;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_set_EVCTRL_PEREO6_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg |= RTC_MODE1_EVCTRL_PEREO6;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode1_get_EVCTRL_PEREO6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp = (tmp & RTC_MODE1_EVCTRL_PEREO6) >> RTC_MODE1_EVCTRL_PEREO6_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode1_write_EVCTRL_PEREO6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp &= ~RTC_MODE1_EVCTRL_PEREO6;
	tmp |= value << RTC_MODE1_EVCTRL_PEREO6_Pos;
	((Rtc *)hw)->MODE1.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_EVCTRL_PEREO6_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg &= ~RTC_MODE1_EVCTRL_PEREO6;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_EVCTRL_PEREO6_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg ^= RTC_MODE1_EVCTRL_PEREO6;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_set_EVCTRL_PEREO7_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg |= RTC_MODE1_EVCTRL_PEREO7;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode1_get_EVCTRL_PEREO7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp = (tmp & RTC_MODE1_EVCTRL_PEREO7) >> RTC_MODE1_EVCTRL_PEREO7_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode1_write_EVCTRL_PEREO7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp &= ~RTC_MODE1_EVCTRL_PEREO7;
	tmp |= value << RTC_MODE1_EVCTRL_PEREO7_Pos;
	((Rtc *)hw)->MODE1.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_EVCTRL_PEREO7_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg &= ~RTC_MODE1_EVCTRL_PEREO7;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_EVCTRL_PEREO7_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg ^= RTC_MODE1_EVCTRL_PEREO7;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_set_EVCTRL_CMPEO0_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg |= RTC_MODE1_EVCTRL_CMPEO0;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode1_get_EVCTRL_CMPEO0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp = (tmp & RTC_MODE1_EVCTRL_CMPEO0) >> RTC_MODE1_EVCTRL_CMPEO0_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode1_write_EVCTRL_CMPEO0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp &= ~RTC_MODE1_EVCTRL_CMPEO0;
	tmp |= value << RTC_MODE1_EVCTRL_CMPEO0_Pos;
	((Rtc *)hw)->MODE1.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_EVCTRL_CMPEO0_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg &= ~RTC_MODE1_EVCTRL_CMPEO0;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_EVCTRL_CMPEO0_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg ^= RTC_MODE1_EVCTRL_CMPEO0;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_set_EVCTRL_CMPEO1_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg |= RTC_MODE1_EVCTRL_CMPEO1;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode1_get_EVCTRL_CMPEO1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp = (tmp & RTC_MODE1_EVCTRL_CMPEO1) >> RTC_MODE1_EVCTRL_CMPEO1_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode1_write_EVCTRL_CMPEO1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp &= ~RTC_MODE1_EVCTRL_CMPEO1;
	tmp |= value << RTC_MODE1_EVCTRL_CMPEO1_Pos;
	((Rtc *)hw)->MODE1.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_EVCTRL_CMPEO1_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg &= ~RTC_MODE1_EVCTRL_CMPEO1;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_EVCTRL_CMPEO1_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg ^= RTC_MODE1_EVCTRL_CMPEO1;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_set_EVCTRL_OVFEO_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg |= RTC_MODE1_EVCTRL_OVFEO;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode1_get_EVCTRL_OVFEO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp = (tmp & RTC_MODE1_EVCTRL_OVFEO) >> RTC_MODE1_EVCTRL_OVFEO_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode1_write_EVCTRL_OVFEO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp &= ~RTC_MODE1_EVCTRL_OVFEO;
	tmp |= value << RTC_MODE1_EVCTRL_OVFEO_Pos;
	((Rtc *)hw)->MODE1.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_EVCTRL_OVFEO_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg &= ~RTC_MODE1_EVCTRL_OVFEO;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_EVCTRL_OVFEO_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg ^= RTC_MODE1_EVCTRL_OVFEO;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_set_EVCTRL_reg(const void *const hw, hri_rtcmode1_evctrl_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg |= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_evctrl_reg_t hri_rtcmode1_get_EVCTRL_reg(const void *const         hw,
                                                                    hri_rtcmode1_evctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE1.EVCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtcmode1_write_EVCTRL_reg(const void *const hw, hri_rtcmode1_evctrl_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg = data;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_EVCTRL_reg(const void *const hw, hri_rtcmode1_evctrl_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg &= ~mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_EVCTRL_reg(const void *const hw, hri_rtcmode1_evctrl_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.EVCTRL.reg ^= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_evctrl_reg_t hri_rtcmode1_read_EVCTRL_reg(const void *const hw)
{
	return ((Rtc *)hw)->MODE1.EVCTRL.reg;
}

static inline void hri_rtcmode2_set_EVCTRL_PEREO0_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg |= RTC_MODE2_EVCTRL_PEREO0;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode2_get_EVCTRL_PEREO0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp = (tmp & RTC_MODE2_EVCTRL_PEREO0) >> RTC_MODE2_EVCTRL_PEREO0_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode2_write_EVCTRL_PEREO0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp &= ~RTC_MODE2_EVCTRL_PEREO0;
	tmp |= value << RTC_MODE2_EVCTRL_PEREO0_Pos;
	((Rtc *)hw)->MODE2.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_EVCTRL_PEREO0_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg &= ~RTC_MODE2_EVCTRL_PEREO0;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_EVCTRL_PEREO0_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg ^= RTC_MODE2_EVCTRL_PEREO0;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_set_EVCTRL_PEREO1_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg |= RTC_MODE2_EVCTRL_PEREO1;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode2_get_EVCTRL_PEREO1_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp = (tmp & RTC_MODE2_EVCTRL_PEREO1) >> RTC_MODE2_EVCTRL_PEREO1_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode2_write_EVCTRL_PEREO1_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp &= ~RTC_MODE2_EVCTRL_PEREO1;
	tmp |= value << RTC_MODE2_EVCTRL_PEREO1_Pos;
	((Rtc *)hw)->MODE2.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_EVCTRL_PEREO1_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg &= ~RTC_MODE2_EVCTRL_PEREO1;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_EVCTRL_PEREO1_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg ^= RTC_MODE2_EVCTRL_PEREO1;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_set_EVCTRL_PEREO2_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg |= RTC_MODE2_EVCTRL_PEREO2;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode2_get_EVCTRL_PEREO2_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp = (tmp & RTC_MODE2_EVCTRL_PEREO2) >> RTC_MODE2_EVCTRL_PEREO2_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode2_write_EVCTRL_PEREO2_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp &= ~RTC_MODE2_EVCTRL_PEREO2;
	tmp |= value << RTC_MODE2_EVCTRL_PEREO2_Pos;
	((Rtc *)hw)->MODE2.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_EVCTRL_PEREO2_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg &= ~RTC_MODE2_EVCTRL_PEREO2;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_EVCTRL_PEREO2_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg ^= RTC_MODE2_EVCTRL_PEREO2;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_set_EVCTRL_PEREO3_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg |= RTC_MODE2_EVCTRL_PEREO3;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode2_get_EVCTRL_PEREO3_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp = (tmp & RTC_MODE2_EVCTRL_PEREO3) >> RTC_MODE2_EVCTRL_PEREO3_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode2_write_EVCTRL_PEREO3_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp &= ~RTC_MODE2_EVCTRL_PEREO3;
	tmp |= value << RTC_MODE2_EVCTRL_PEREO3_Pos;
	((Rtc *)hw)->MODE2.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_EVCTRL_PEREO3_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg &= ~RTC_MODE2_EVCTRL_PEREO3;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_EVCTRL_PEREO3_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg ^= RTC_MODE2_EVCTRL_PEREO3;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_set_EVCTRL_PEREO4_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg |= RTC_MODE2_EVCTRL_PEREO4;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode2_get_EVCTRL_PEREO4_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp = (tmp & RTC_MODE2_EVCTRL_PEREO4) >> RTC_MODE2_EVCTRL_PEREO4_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode2_write_EVCTRL_PEREO4_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp &= ~RTC_MODE2_EVCTRL_PEREO4;
	tmp |= value << RTC_MODE2_EVCTRL_PEREO4_Pos;
	((Rtc *)hw)->MODE2.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_EVCTRL_PEREO4_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg &= ~RTC_MODE2_EVCTRL_PEREO4;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_EVCTRL_PEREO4_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg ^= RTC_MODE2_EVCTRL_PEREO4;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_set_EVCTRL_PEREO5_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg |= RTC_MODE2_EVCTRL_PEREO5;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode2_get_EVCTRL_PEREO5_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp = (tmp & RTC_MODE2_EVCTRL_PEREO5) >> RTC_MODE2_EVCTRL_PEREO5_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode2_write_EVCTRL_PEREO5_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp &= ~RTC_MODE2_EVCTRL_PEREO5;
	tmp |= value << RTC_MODE2_EVCTRL_PEREO5_Pos;
	((Rtc *)hw)->MODE2.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_EVCTRL_PEREO5_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg &= ~RTC_MODE2_EVCTRL_PEREO5;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_EVCTRL_PEREO5_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg ^= RTC_MODE2_EVCTRL_PEREO5;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_set_EVCTRL_PEREO6_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg |= RTC_MODE2_EVCTRL_PEREO6;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode2_get_EVCTRL_PEREO6_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp = (tmp & RTC_MODE2_EVCTRL_PEREO6) >> RTC_MODE2_EVCTRL_PEREO6_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode2_write_EVCTRL_PEREO6_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp &= ~RTC_MODE2_EVCTRL_PEREO6;
	tmp |= value << RTC_MODE2_EVCTRL_PEREO6_Pos;
	((Rtc *)hw)->MODE2.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_EVCTRL_PEREO6_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg &= ~RTC_MODE2_EVCTRL_PEREO6;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_EVCTRL_PEREO6_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg ^= RTC_MODE2_EVCTRL_PEREO6;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_set_EVCTRL_PEREO7_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg |= RTC_MODE2_EVCTRL_PEREO7;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode2_get_EVCTRL_PEREO7_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp = (tmp & RTC_MODE2_EVCTRL_PEREO7) >> RTC_MODE2_EVCTRL_PEREO7_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode2_write_EVCTRL_PEREO7_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp &= ~RTC_MODE2_EVCTRL_PEREO7;
	tmp |= value << RTC_MODE2_EVCTRL_PEREO7_Pos;
	((Rtc *)hw)->MODE2.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_EVCTRL_PEREO7_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg &= ~RTC_MODE2_EVCTRL_PEREO7;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_EVCTRL_PEREO7_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg ^= RTC_MODE2_EVCTRL_PEREO7;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_set_EVCTRL_ALARMEO0_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg |= RTC_MODE2_EVCTRL_ALARMEO0;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode2_get_EVCTRL_ALARMEO0_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp = (tmp & RTC_MODE2_EVCTRL_ALARMEO0) >> RTC_MODE2_EVCTRL_ALARMEO0_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode2_write_EVCTRL_ALARMEO0_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp &= ~RTC_MODE2_EVCTRL_ALARMEO0;
	tmp |= value << RTC_MODE2_EVCTRL_ALARMEO0_Pos;
	((Rtc *)hw)->MODE2.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_EVCTRL_ALARMEO0_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg &= ~RTC_MODE2_EVCTRL_ALARMEO0;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_EVCTRL_ALARMEO0_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg ^= RTC_MODE2_EVCTRL_ALARMEO0;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_set_EVCTRL_OVFEO_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg |= RTC_MODE2_EVCTRL_OVFEO;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtcmode2_get_EVCTRL_OVFEO_bit(const void *const hw)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp = (tmp & RTC_MODE2_EVCTRL_OVFEO) >> RTC_MODE2_EVCTRL_OVFEO_Pos;
	return (bool)tmp;
}

static inline void hri_rtcmode2_write_EVCTRL_OVFEO_bit(const void *const hw, bool value)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp &= ~RTC_MODE2_EVCTRL_OVFEO;
	tmp |= value << RTC_MODE2_EVCTRL_OVFEO_Pos;
	((Rtc *)hw)->MODE2.EVCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_EVCTRL_OVFEO_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg &= ~RTC_MODE2_EVCTRL_OVFEO;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_EVCTRL_OVFEO_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg ^= RTC_MODE2_EVCTRL_OVFEO;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_set_EVCTRL_reg(const void *const hw, hri_rtcmode2_evctrl_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg |= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_evctrl_reg_t hri_rtcmode2_get_EVCTRL_reg(const void *const         hw,
                                                                    hri_rtcmode2_evctrl_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE2.EVCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtcmode2_write_EVCTRL_reg(const void *const hw, hri_rtcmode2_evctrl_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg = data;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_EVCTRL_reg(const void *const hw, hri_rtcmode2_evctrl_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg &= ~mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_EVCTRL_reg(const void *const hw, hri_rtcmode2_evctrl_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.EVCTRL.reg ^= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_evctrl_reg_t hri_rtcmode2_read_EVCTRL_reg(const void *const hw)
{
	return ((Rtc *)hw)->MODE2.EVCTRL.reg;
}

static inline void hri_rtc_set_DBGCTRL_DBGRUN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.DBGCTRL.reg |= RTC_DBGCTRL_DBGRUN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtc_get_DBGCTRL_DBGRUN_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Rtc *)hw)->MODE0.DBGCTRL.reg;
	tmp = (tmp & RTC_DBGCTRL_DBGRUN) >> RTC_DBGCTRL_DBGRUN_Pos;
	return (bool)tmp;
}

static inline void hri_rtc_write_DBGCTRL_DBGRUN_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.DBGCTRL.reg;
	tmp &= ~RTC_DBGCTRL_DBGRUN;
	tmp |= value << RTC_DBGCTRL_DBGRUN_Pos;
	((Rtc *)hw)->MODE0.DBGCTRL.reg = tmp;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_DBGCTRL_DBGRUN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.DBGCTRL.reg &= ~RTC_DBGCTRL_DBGRUN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_DBGCTRL_DBGRUN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.DBGCTRL.reg ^= RTC_DBGCTRL_DBGRUN;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_set_DBGCTRL_reg(const void *const hw, hri_rtc_dbgctrl_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.DBGCTRL.reg |= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_dbgctrl_reg_t hri_rtc_get_DBGCTRL_reg(const void *const hw, hri_rtc_dbgctrl_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Rtc *)hw)->MODE0.DBGCTRL.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtc_write_DBGCTRL_reg(const void *const hw, hri_rtc_dbgctrl_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.DBGCTRL.reg = data;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_DBGCTRL_reg(const void *const hw, hri_rtc_dbgctrl_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.DBGCTRL.reg &= ~mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_DBGCTRL_reg(const void *const hw, hri_rtc_dbgctrl_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.DBGCTRL.reg ^= mask;
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_dbgctrl_reg_t hri_rtc_read_DBGCTRL_reg(const void *const hw)
{
	return ((Rtc *)hw)->MODE0.DBGCTRL.reg;
}

static inline void hri_rtc_set_FREQCORR_SIGN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.FREQCORR.reg |= RTC_FREQCORR_SIGN;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline bool hri_rtc_get_FREQCORR_SIGN_bit(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Rtc *)hw)->MODE0.FREQCORR.reg;
	tmp = (tmp & RTC_FREQCORR_SIGN) >> RTC_FREQCORR_SIGN_Pos;
	return (bool)tmp;
}

static inline void hri_rtc_write_FREQCORR_SIGN_bit(const void *const hw, bool value)
{
	uint8_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.FREQCORR.reg;
	tmp &= ~RTC_FREQCORR_SIGN;
	tmp |= value << RTC_FREQCORR_SIGN_Pos;
	((Rtc *)hw)->MODE0.FREQCORR.reg = tmp;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_FREQCORR_SIGN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.FREQCORR.reg &= ~RTC_FREQCORR_SIGN;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_FREQCORR_SIGN_bit(const void *const hw)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.FREQCORR.reg ^= RTC_FREQCORR_SIGN;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_set_FREQCORR_VALUE_bf(const void *const hw, hri_rtc_freqcorr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.FREQCORR.reg |= RTC_FREQCORR_VALUE(mask);
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_freqcorr_reg_t hri_rtc_get_FREQCORR_VALUE_bf(const void *const hw, hri_rtc_freqcorr_reg_t mask)
{
	uint8_t tmp;
	tmp = ((Rtc *)hw)->MODE0.FREQCORR.reg;
	tmp = (tmp & RTC_FREQCORR_VALUE(mask)) >> RTC_FREQCORR_VALUE_Pos;
	return tmp;
}

static inline void hri_rtc_write_FREQCORR_VALUE_bf(const void *const hw, hri_rtc_freqcorr_reg_t data)
{
	uint8_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.FREQCORR.reg;
	tmp &= ~RTC_FREQCORR_VALUE_Msk;
	tmp |= RTC_FREQCORR_VALUE(data);
	((Rtc *)hw)->MODE0.FREQCORR.reg = tmp;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_FREQCORR_VALUE_bf(const void *const hw, hri_rtc_freqcorr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.FREQCORR.reg &= ~RTC_FREQCORR_VALUE(mask);
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_FREQCORR_VALUE_bf(const void *const hw, hri_rtc_freqcorr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.FREQCORR.reg ^= RTC_FREQCORR_VALUE(mask);
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_freqcorr_reg_t hri_rtc_read_FREQCORR_VALUE_bf(const void *const hw)
{
	uint8_t tmp;
	tmp = ((Rtc *)hw)->MODE0.FREQCORR.reg;
	tmp = (tmp & RTC_FREQCORR_VALUE_Msk) >> RTC_FREQCORR_VALUE_Pos;
	return tmp;
}

static inline void hri_rtc_set_FREQCORR_reg(const void *const hw, hri_rtc_freqcorr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.FREQCORR.reg |= mask;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_freqcorr_reg_t hri_rtc_get_FREQCORR_reg(const void *const hw, hri_rtc_freqcorr_reg_t mask)
{
	uint8_t tmp;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	tmp = ((Rtc *)hw)->MODE0.FREQCORR.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtc_write_FREQCORR_reg(const void *const hw, hri_rtc_freqcorr_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.FREQCORR.reg = data;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_clear_FREQCORR_reg(const void *const hw, hri_rtc_freqcorr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.FREQCORR.reg &= ~mask;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtc_toggle_FREQCORR_reg(const void *const hw, hri_rtc_freqcorr_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.FREQCORR.reg ^= mask;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtc_freqcorr_reg_t hri_rtc_read_FREQCORR_reg(const void *const hw)
{
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_MASK);
	return ((Rtc *)hw)->MODE0.FREQCORR.reg;
}

static inline void hri_rtcmode0_set_COUNT_COUNT_bf(const void *const hw, hri_rtcmode0_count_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.COUNT.reg |= RTC_MODE0_COUNT_COUNT(mask);
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COUNT);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode0_count_reg_t hri_rtcmode0_get_COUNT_COUNT_bf(const void *const        hw,
                                                                       hri_rtcmode0_count_reg_t mask)
{
	uint32_t tmp;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COUNT);
	tmp = ((Rtc *)hw)->MODE0.COUNT.reg;
	tmp = (tmp & RTC_MODE0_COUNT_COUNT(mask)) >> RTC_MODE0_COUNT_COUNT_Pos;
	return tmp;
}

static inline void hri_rtcmode0_write_COUNT_COUNT_bf(const void *const hw, hri_rtcmode0_count_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.COUNT.reg;
	tmp &= ~RTC_MODE0_COUNT_COUNT_Msk;
	tmp |= RTC_MODE0_COUNT_COUNT(data);
	((Rtc *)hw)->MODE0.COUNT.reg = tmp;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COUNT);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_COUNT_COUNT_bf(const void *const hw, hri_rtcmode0_count_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.COUNT.reg &= ~RTC_MODE0_COUNT_COUNT(mask);
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COUNT);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_COUNT_COUNT_bf(const void *const hw, hri_rtcmode0_count_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.COUNT.reg ^= RTC_MODE0_COUNT_COUNT(mask);
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COUNT);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode0_count_reg_t hri_rtcmode0_read_COUNT_COUNT_bf(const void *const hw)
{
	uint32_t tmp;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COUNT);
	tmp = ((Rtc *)hw)->MODE0.COUNT.reg;
	tmp = (tmp & RTC_MODE0_COUNT_COUNT_Msk) >> RTC_MODE0_COUNT_COUNT_Pos;
	return tmp;
}

static inline void hri_rtcmode0_set_COUNT_reg(const void *const hw, hri_rtcmode0_count_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.COUNT.reg |= mask;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COUNT);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode0_count_reg_t hri_rtcmode0_get_COUNT_reg(const void *const hw, hri_rtcmode0_count_reg_t mask)
{
	uint32_t tmp;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COUNT);
	tmp = ((Rtc *)hw)->MODE0.COUNT.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtcmode0_write_COUNT_reg(const void *const hw, hri_rtcmode0_count_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.COUNT.reg = data;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COUNT);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_COUNT_reg(const void *const hw, hri_rtcmode0_count_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.COUNT.reg &= ~mask;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COUNT);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_COUNT_reg(const void *const hw, hri_rtcmode0_count_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.COUNT.reg ^= mask;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COUNT);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode0_count_reg_t hri_rtcmode0_read_COUNT_reg(const void *const hw)
{
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COUNT);
	return ((Rtc *)hw)->MODE0.COUNT.reg;
}

static inline void hri_rtcmode1_set_COUNT_COUNT_bf(const void *const hw, hri_rtcmode1_count_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.COUNT.reg |= RTC_MODE1_COUNT_COUNT(mask);
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COUNT);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_count_reg_t hri_rtcmode1_get_COUNT_COUNT_bf(const void *const        hw,
                                                                       hri_rtcmode1_count_reg_t mask)
{
	uint16_t tmp;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COUNT);
	tmp = ((Rtc *)hw)->MODE1.COUNT.reg;
	tmp = (tmp & RTC_MODE1_COUNT_COUNT(mask)) >> RTC_MODE1_COUNT_COUNT_Pos;
	return tmp;
}

static inline void hri_rtcmode1_write_COUNT_COUNT_bf(const void *const hw, hri_rtcmode1_count_reg_t data)
{
	uint16_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE1.COUNT.reg;
	tmp &= ~RTC_MODE1_COUNT_COUNT_Msk;
	tmp |= RTC_MODE1_COUNT_COUNT(data);
	((Rtc *)hw)->MODE1.COUNT.reg = tmp;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COUNT);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_COUNT_COUNT_bf(const void *const hw, hri_rtcmode1_count_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.COUNT.reg &= ~RTC_MODE1_COUNT_COUNT(mask);
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COUNT);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_COUNT_COUNT_bf(const void *const hw, hri_rtcmode1_count_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.COUNT.reg ^= RTC_MODE1_COUNT_COUNT(mask);
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COUNT);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_count_reg_t hri_rtcmode1_read_COUNT_COUNT_bf(const void *const hw)
{
	uint16_t tmp;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COUNT);
	tmp = ((Rtc *)hw)->MODE1.COUNT.reg;
	tmp = (tmp & RTC_MODE1_COUNT_COUNT_Msk) >> RTC_MODE1_COUNT_COUNT_Pos;
	return tmp;
}

static inline void hri_rtcmode1_set_COUNT_reg(const void *const hw, hri_rtcmode1_count_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.COUNT.reg |= mask;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COUNT);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_count_reg_t hri_rtcmode1_get_COUNT_reg(const void *const hw, hri_rtcmode1_count_reg_t mask)
{
	uint16_t tmp;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COUNT);
	tmp = ((Rtc *)hw)->MODE1.COUNT.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtcmode1_write_COUNT_reg(const void *const hw, hri_rtcmode1_count_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.COUNT.reg = data;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COUNT);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_COUNT_reg(const void *const hw, hri_rtcmode1_count_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.COUNT.reg &= ~mask;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COUNT);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_COUNT_reg(const void *const hw, hri_rtcmode1_count_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.COUNT.reg ^= mask;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COUNT);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_count_reg_t hri_rtcmode1_read_COUNT_reg(const void *const hw)
{
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COUNT);
	return ((Rtc *)hw)->MODE1.COUNT.reg;
}

static inline void hri_rtcmode2_set_CLOCK_SECOND_bf(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg |= RTC_MODE2_CLOCK_SECOND(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_clock_reg_t hri_rtcmode2_get_CLOCK_SECOND_bf(const void *const        hw,
                                                                        hri_rtcmode2_clock_reg_t mask)
{
	uint32_t tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp = (tmp & RTC_MODE2_CLOCK_SECOND(mask)) >> RTC_MODE2_CLOCK_SECOND_Pos;
	return tmp;
}

static inline void hri_rtcmode2_write_CLOCK_SECOND_bf(const void *const hw, hri_rtcmode2_clock_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp &= ~RTC_MODE2_CLOCK_SECOND_Msk;
	tmp |= RTC_MODE2_CLOCK_SECOND(data);
	((Rtc *)hw)->MODE2.CLOCK.reg = tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_CLOCK_SECOND_bf(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg &= ~RTC_MODE2_CLOCK_SECOND(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_CLOCK_SECOND_bf(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg ^= RTC_MODE2_CLOCK_SECOND(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_clock_reg_t hri_rtcmode2_read_CLOCK_SECOND_bf(const void *const hw)
{
	uint32_t tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp = (tmp & RTC_MODE2_CLOCK_SECOND_Msk) >> RTC_MODE2_CLOCK_SECOND_Pos;
	return tmp;
}

static inline void hri_rtcmode2_set_CLOCK_MINUTE_bf(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg |= RTC_MODE2_CLOCK_MINUTE(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_clock_reg_t hri_rtcmode2_get_CLOCK_MINUTE_bf(const void *const        hw,
                                                                        hri_rtcmode2_clock_reg_t mask)
{
	uint32_t tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp = (tmp & RTC_MODE2_CLOCK_MINUTE(mask)) >> RTC_MODE2_CLOCK_MINUTE_Pos;
	return tmp;
}

static inline void hri_rtcmode2_write_CLOCK_MINUTE_bf(const void *const hw, hri_rtcmode2_clock_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp &= ~RTC_MODE2_CLOCK_MINUTE_Msk;
	tmp |= RTC_MODE2_CLOCK_MINUTE(data);
	((Rtc *)hw)->MODE2.CLOCK.reg = tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_CLOCK_MINUTE_bf(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg &= ~RTC_MODE2_CLOCK_MINUTE(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_CLOCK_MINUTE_bf(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg ^= RTC_MODE2_CLOCK_MINUTE(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_clock_reg_t hri_rtcmode2_read_CLOCK_MINUTE_bf(const void *const hw)
{
	uint32_t tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp = (tmp & RTC_MODE2_CLOCK_MINUTE_Msk) >> RTC_MODE2_CLOCK_MINUTE_Pos;
	return tmp;
}

static inline void hri_rtcmode2_set_CLOCK_HOUR_bf(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg |= RTC_MODE2_CLOCK_HOUR(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_clock_reg_t hri_rtcmode2_get_CLOCK_HOUR_bf(const void *const        hw,
                                                                      hri_rtcmode2_clock_reg_t mask)
{
	uint32_t tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp = (tmp & RTC_MODE2_CLOCK_HOUR(mask)) >> RTC_MODE2_CLOCK_HOUR_Pos;
	return tmp;
}

static inline void hri_rtcmode2_write_CLOCK_HOUR_bf(const void *const hw, hri_rtcmode2_clock_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp &= ~RTC_MODE2_CLOCK_HOUR_Msk;
	tmp |= RTC_MODE2_CLOCK_HOUR(data);
	((Rtc *)hw)->MODE2.CLOCK.reg = tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_CLOCK_HOUR_bf(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg &= ~RTC_MODE2_CLOCK_HOUR(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_CLOCK_HOUR_bf(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg ^= RTC_MODE2_CLOCK_HOUR(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_clock_reg_t hri_rtcmode2_read_CLOCK_HOUR_bf(const void *const hw)
{
	uint32_t tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp = (tmp & RTC_MODE2_CLOCK_HOUR_Msk) >> RTC_MODE2_CLOCK_HOUR_Pos;
	return tmp;
}

static inline void hri_rtcmode2_set_CLOCK_DAY_bf(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg |= RTC_MODE2_CLOCK_DAY(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_clock_reg_t hri_rtcmode2_get_CLOCK_DAY_bf(const void *const        hw,
                                                                     hri_rtcmode2_clock_reg_t mask)
{
	uint32_t tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp = (tmp & RTC_MODE2_CLOCK_DAY(mask)) >> RTC_MODE2_CLOCK_DAY_Pos;
	return tmp;
}

static inline void hri_rtcmode2_write_CLOCK_DAY_bf(const void *const hw, hri_rtcmode2_clock_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp &= ~RTC_MODE2_CLOCK_DAY_Msk;
	tmp |= RTC_MODE2_CLOCK_DAY(data);
	((Rtc *)hw)->MODE2.CLOCK.reg = tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_CLOCK_DAY_bf(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg &= ~RTC_MODE2_CLOCK_DAY(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_CLOCK_DAY_bf(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg ^= RTC_MODE2_CLOCK_DAY(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_clock_reg_t hri_rtcmode2_read_CLOCK_DAY_bf(const void *const hw)
{
	uint32_t tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp = (tmp & RTC_MODE2_CLOCK_DAY_Msk) >> RTC_MODE2_CLOCK_DAY_Pos;
	return tmp;
}

static inline void hri_rtcmode2_set_CLOCK_MONTH_bf(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg |= RTC_MODE2_CLOCK_MONTH(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_clock_reg_t hri_rtcmode2_get_CLOCK_MONTH_bf(const void *const        hw,
                                                                       hri_rtcmode2_clock_reg_t mask)
{
	uint32_t tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp = (tmp & RTC_MODE2_CLOCK_MONTH(mask)) >> RTC_MODE2_CLOCK_MONTH_Pos;
	return tmp;
}

static inline void hri_rtcmode2_write_CLOCK_MONTH_bf(const void *const hw, hri_rtcmode2_clock_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp &= ~RTC_MODE2_CLOCK_MONTH_Msk;
	tmp |= RTC_MODE2_CLOCK_MONTH(data);
	((Rtc *)hw)->MODE2.CLOCK.reg = tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_CLOCK_MONTH_bf(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg &= ~RTC_MODE2_CLOCK_MONTH(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_CLOCK_MONTH_bf(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg ^= RTC_MODE2_CLOCK_MONTH(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_clock_reg_t hri_rtcmode2_read_CLOCK_MONTH_bf(const void *const hw)
{
	uint32_t tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp = (tmp & RTC_MODE2_CLOCK_MONTH_Msk) >> RTC_MODE2_CLOCK_MONTH_Pos;
	return tmp;
}

static inline void hri_rtcmode2_set_CLOCK_YEAR_bf(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg |= RTC_MODE2_CLOCK_YEAR(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_clock_reg_t hri_rtcmode2_get_CLOCK_YEAR_bf(const void *const        hw,
                                                                      hri_rtcmode2_clock_reg_t mask)
{
	uint32_t tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp = (tmp & RTC_MODE2_CLOCK_YEAR(mask)) >> RTC_MODE2_CLOCK_YEAR_Pos;
	return tmp;
}

static inline void hri_rtcmode2_write_CLOCK_YEAR_bf(const void *const hw, hri_rtcmode2_clock_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp &= ~RTC_MODE2_CLOCK_YEAR_Msk;
	tmp |= RTC_MODE2_CLOCK_YEAR(data);
	((Rtc *)hw)->MODE2.CLOCK.reg = tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_CLOCK_YEAR_bf(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg &= ~RTC_MODE2_CLOCK_YEAR(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_CLOCK_YEAR_bf(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg ^= RTC_MODE2_CLOCK_YEAR(mask);
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_clock_reg_t hri_rtcmode2_read_CLOCK_YEAR_bf(const void *const hw)
{
	uint32_t tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp = (tmp & RTC_MODE2_CLOCK_YEAR_Msk) >> RTC_MODE2_CLOCK_YEAR_Pos;
	return tmp;
}

static inline void hri_rtcmode2_set_CLOCK_reg(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg |= mask;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_clock_reg_t hri_rtcmode2_get_CLOCK_reg(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	uint32_t tmp;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	tmp = ((Rtc *)hw)->MODE2.CLOCK.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtcmode2_write_CLOCK_reg(const void *const hw, hri_rtcmode2_clock_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg = data;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_clear_CLOCK_reg(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg &= ~mask;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode2_toggle_CLOCK_reg(const void *const hw, hri_rtcmode2_clock_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE2.CLOCK.reg ^= mask;
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode2_clock_reg_t hri_rtcmode2_read_CLOCK_reg(const void *const hw)
{
	hri_rtcmode2_wait_for_sync(hw, RTC_MODE2_SYNCBUSY_MASK_);
	return ((Rtc *)hw)->MODE2.CLOCK.reg;
}

static inline void hri_rtcmode1_set_PER_PER_bf(const void *const hw, hri_rtcmode1_per_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.PER.reg |= RTC_MODE1_PER_PER(mask);
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_PER);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_per_reg_t hri_rtcmode1_get_PER_PER_bf(const void *const hw, hri_rtcmode1_per_reg_t mask)
{
	uint16_t tmp;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_PER);
	tmp = ((Rtc *)hw)->MODE1.PER.reg;
	tmp = (tmp & RTC_MODE1_PER_PER(mask)) >> RTC_MODE1_PER_PER_Pos;
	return tmp;
}

static inline void hri_rtcmode1_write_PER_PER_bf(const void *const hw, hri_rtcmode1_per_reg_t data)
{
	uint16_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE1.PER.reg;
	tmp &= ~RTC_MODE1_PER_PER_Msk;
	tmp |= RTC_MODE1_PER_PER(data);
	((Rtc *)hw)->MODE1.PER.reg = tmp;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_PER);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_PER_PER_bf(const void *const hw, hri_rtcmode1_per_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.PER.reg &= ~RTC_MODE1_PER_PER(mask);
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_PER);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_PER_PER_bf(const void *const hw, hri_rtcmode1_per_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.PER.reg ^= RTC_MODE1_PER_PER(mask);
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_PER);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_per_reg_t hri_rtcmode1_read_PER_PER_bf(const void *const hw)
{
	uint16_t tmp;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_PER);
	tmp = ((Rtc *)hw)->MODE1.PER.reg;
	tmp = (tmp & RTC_MODE1_PER_PER_Msk) >> RTC_MODE1_PER_PER_Pos;
	return tmp;
}

static inline void hri_rtcmode1_set_PER_reg(const void *const hw, hri_rtcmode1_per_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.PER.reg |= mask;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_PER);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_per_reg_t hri_rtcmode1_get_PER_reg(const void *const hw, hri_rtcmode1_per_reg_t mask)
{
	uint16_t tmp;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_PER);
	tmp = ((Rtc *)hw)->MODE1.PER.reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtcmode1_write_PER_reg(const void *const hw, hri_rtcmode1_per_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.PER.reg = data;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_PER);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_PER_reg(const void *const hw, hri_rtcmode1_per_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.PER.reg &= ~mask;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_PER);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_PER_reg(const void *const hw, hri_rtcmode1_per_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.PER.reg ^= mask;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_PER);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_per_reg_t hri_rtcmode1_read_PER_reg(const void *const hw)
{
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_PER);
	return ((Rtc *)hw)->MODE1.PER.reg;
}

static inline void hri_rtcmode0_set_COMP_COMP_bf(const void *const hw, uint8_t index, hri_rtcmode0_comp_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.COMP[index].reg |= RTC_MODE0_COMP_COMP(mask);
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COMP0);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode0_comp_reg_t hri_rtcmode0_get_COMP_COMP_bf(const void *const hw, uint8_t index,
                                                                    hri_rtcmode0_comp_reg_t mask)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE0.COMP[index].reg;
	tmp = (tmp & RTC_MODE0_COMP_COMP(mask)) >> RTC_MODE0_COMP_COMP_Pos;
	return tmp;
}

static inline void hri_rtcmode0_write_COMP_COMP_bf(const void *const hw, uint8_t index, hri_rtcmode0_comp_reg_t data)
{
	uint32_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE0.COMP[index].reg;
	tmp &= ~RTC_MODE0_COMP_COMP_Msk;
	tmp |= RTC_MODE0_COMP_COMP(data);
	((Rtc *)hw)->MODE0.COMP[index].reg = tmp;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COMP0);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_COMP_COMP_bf(const void *const hw, uint8_t index, hri_rtcmode0_comp_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.COMP[index].reg &= ~RTC_MODE0_COMP_COMP(mask);
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COMP0);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_COMP_COMP_bf(const void *const hw, uint8_t index, hri_rtcmode0_comp_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.COMP[index].reg ^= RTC_MODE0_COMP_COMP(mask);
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COMP0);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode0_comp_reg_t hri_rtcmode0_read_COMP_COMP_bf(const void *const hw, uint8_t index)
{
	uint32_t tmp;
	tmp = ((Rtc *)hw)->MODE0.COMP[index].reg;
	tmp = (tmp & RTC_MODE0_COMP_COMP_Msk) >> RTC_MODE0_COMP_COMP_Pos;
	return tmp;
}

static inline void hri_rtcmode0_set_COMP_reg(const void *const hw, uint8_t index, hri_rtcmode0_comp_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.COMP[index].reg |= mask;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COMP0);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode0_comp_reg_t hri_rtcmode0_get_COMP_reg(const void *const hw, uint8_t index,
                                                                hri_rtcmode0_comp_reg_t mask)
{
	uint32_t tmp;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COMP0);
	tmp = ((Rtc *)hw)->MODE0.COMP[index].reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtcmode0_write_COMP_reg(const void *const hw, uint8_t index, hri_rtcmode0_comp_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.COMP[index].reg = data;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COMP0);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_clear_COMP_reg(const void *const hw, uint8_t index, hri_rtcmode0_comp_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.COMP[index].reg &= ~mask;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COMP0);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode0_toggle_COMP_reg(const void *const hw, uint8_t index, hri_rtcmode0_comp_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE0.COMP[index].reg ^= mask;
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COMP0);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode0_comp_reg_t hri_rtcmode0_read_COMP_reg(const void *const hw, uint8_t index)
{
	hri_rtcmode0_wait_for_sync(hw, RTC_MODE0_SYNCBUSY_COMP0);
	return ((Rtc *)hw)->MODE0.COMP[index].reg;
}

static inline void hri_rtcmode1_set_COMP_COMP_bf(const void *const hw, uint8_t index, hri_rtcmode1_comp_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.COMP[index].reg |= RTC_MODE1_COMP_COMP(mask);
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COMP0 | RTC_MODE1_SYNCBUSY_COMP1);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_comp_reg_t hri_rtcmode1_get_COMP_COMP_bf(const void *const hw, uint8_t index,
                                                                    hri_rtcmode1_comp_reg_t mask)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE1.COMP[index].reg;
	tmp = (tmp & RTC_MODE1_COMP_COMP(mask)) >> RTC_MODE1_COMP_COMP_Pos;
	return tmp;
}

static inline void hri_rtcmode1_write_COMP_COMP_bf(const void *const hw, uint8_t index, hri_rtcmode1_comp_reg_t data)
{
	uint16_t tmp;
	RTC_CRITICAL_SECTION_ENTER();
	tmp = ((Rtc *)hw)->MODE1.COMP[index].reg;
	tmp &= ~RTC_MODE1_COMP_COMP_Msk;
	tmp |= RTC_MODE1_COMP_COMP(data);
	((Rtc *)hw)->MODE1.COMP[index].reg = tmp;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COMP0 | RTC_MODE1_SYNCBUSY_COMP1);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_COMP_COMP_bf(const void *const hw, uint8_t index, hri_rtcmode1_comp_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.COMP[index].reg &= ~RTC_MODE1_COMP_COMP(mask);
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COMP0 | RTC_MODE1_SYNCBUSY_COMP1);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_COMP_COMP_bf(const void *const hw, uint8_t index, hri_rtcmode1_comp_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.COMP[index].reg ^= RTC_MODE1_COMP_COMP(mask);
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COMP0 | RTC_MODE1_SYNCBUSY_COMP1);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_comp_reg_t hri_rtcmode1_read_COMP_COMP_bf(const void *const hw, uint8_t index)
{
	uint16_t tmp;
	tmp = ((Rtc *)hw)->MODE1.COMP[index].reg;
	tmp = (tmp & RTC_MODE1_COMP_COMP_Msk) >> RTC_MODE1_COMP_COMP_Pos;
	return tmp;
}

static inline void hri_rtcmode1_set_COMP_reg(const void *const hw, uint8_t index, hri_rtcmode1_comp_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.COMP[index].reg |= mask;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COMP0 | RTC_MODE1_SYNCBUSY_COMP1);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_comp_reg_t hri_rtcmode1_get_COMP_reg(const void *const hw, uint8_t index,
                                                                hri_rtcmode1_comp_reg_t mask)
{
	uint16_t tmp;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COMP0 | RTC_MODE1_SYNCBUSY_COMP1);
	tmp = ((Rtc *)hw)->MODE1.COMP[index].reg;
	tmp &= mask;
	return tmp;
}

static inline void hri_rtcmode1_write_COMP_reg(const void *const hw, uint8_t index, hri_rtcmode1_comp_reg_t data)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.COMP[index].reg = data;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COMP0 | RTC_MODE1_SYNCBUSY_COMP1);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_clear_COMP_reg(const void *const hw, uint8_t index, hri_rtcmode1_comp_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.COMP[index].reg &= ~mask;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COMP0 | RTC_MODE1_SYNCBUSY_COMP1);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline void hri_rtcmode1_toggle_COMP_reg(const void *const hw, uint8_t index, hri_rtcmode1_comp_reg_t mask)
{
	RTC_CRITICAL_SECTION_ENTER();
	((Rtc *)hw)->MODE1.COMP[index].reg ^= mask;
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COMP0 | RTC_MODE1_SYNCBUSY_COMP1);
	RTC_CRITICAL_SECTION_LEAVE();
}

static inline hri_rtcmode1_comp_reg_t hri_rtcmode1_read_COMP_reg(const void *const hw, uint8_t index)
{
	hri_rtcmode1_wait_for_sync(hw, RTC_MODE1_SYNCBUSY_COMP0 | RTC_MODE1_SYNCBUSY_COMP1);
	return ((Rtc *)hw)->MODE1.COMP[index].reg;
}

/* Below section is for legacy hri apis name, not recommended to use below left side apis in application */
#define hri_rtcmode2_set_DBGCTRL_DBGRUN_bit(a) hri_rtc_set_DBGCTRL_DBGRUN_bit(a)
#define hri_rtcmode2_get_DBGCTRL_DBGRUN_bit(a) hri_rtc_get_DBGCTRL_DBGRUN_bit(a)
#define hri_rtcmode2_write_DBGCTRL_DBGRUN_bit(a, b) hri_rtc_write_DBGCTRL_DBGRUN_bit(a, b)
#define hri_rtcmode2_clear_DBGCTRL_DBGRUN_bit(a) hri_rtc_clear_DBGCTRL_DBGRUN_bit(a)
#define hri_rtcmode2_toggle_DBGCTRL_DBGRUN_bit(a) hri_rtc_toggle_DBGCTRL_DBGRUN_bit(a)
#define hri_rtcmode2_set_DBGCTRL_reg(a, b) hri_rtc_set_DBGCTRL_reg(a, b)
#define hri_rtcmode2_get_DBGCTRL_reg(a, b) hri_rtc_get_DBGCTRL_reg(a, b)
#define hri_rtcmode2_write_DBGCTRL_reg(a, b) hri_rtc_write_DBGCTRL_reg(a, b)
#define hri_rtcmode2_clear_DBGCTRL_reg(a, b) hri_rtc_clear_DBGCTRL_reg(a, b)
#define hri_rtcmode2_toggle_DBGCTRL_reg(a, b) hri_rtc_toggle_DBGCTRL_reg(a, b)
#define hri_rtcmode2_read_DBGCTRL_reg(a) hri_rtc_read_DBGCTRL_reg(a)
#define hri_rtcmode2_set_FREQCORR_SIGN_bit(a) hri_rtc_set_FREQCORR_SIGN_bit(a)
#define hri_rtcmode2_get_FREQCORR_SIGN_bit(a) hri_rtc_get_FREQCORR_SIGN_bit(a)
#define hri_rtcmode2_write_FREQCORR_SIGN_bit(a, b) hri_rtc_write_FREQCORR_SIGN_bit(a, b)
#define hri_rtcmode2_clear_FREQCORR_SIGN_bit(a) hri_rtc_clear_FREQCORR_SIGN_bit(a)
#define hri_rtcmode2_toggle_FREQCORR_SIGN_bit(a) hri_rtc_toggle_FREQCORR_SIGN_bit(a)
#define hri_rtcmode2_set_FREQCORR_VALUE_bf(a, b) hri_rtc_set_FREQCORR_VALUE_bf(a, b)
#define hri_rtcmode2_get_FREQCORR_VALUE_bf(a, b) hri_rtc_get_FREQCORR_VALUE_bf(a, b)
#define hri_rtcmode2_write_FREQCORR_VALUE_bf(a, b) hri_rtc_write_FREQCORR_VALUE_bf(a, b)
#define hri_rtcmode2_clear_FREQCORR_VALUE_bf(a, b) hri_rtc_clear_FREQCORR_VALUE_bf(a, b)
#define hri_rtcmode2_toggle_FREQCORR_VALUE_bf(a, b) hri_rtc_toggle_FREQCORR_VALUE_bf(a, b)
#define hri_rtcmode2_read_FREQCORR_VALUE_bf(a) hri_rtc_read_FREQCORR_VALUE_bf(a)
#define hri_rtcmode2_set_FREQCORR_reg(a, b) hri_rtc_set_FREQCORR_reg(a, b)
#define hri_rtcmode2_get_FREQCORR_reg(a, b) hri_rtc_get_FREQCORR_reg(a, b)
#define hri_rtcmode2_write_FREQCORR_reg(a, b) hri_rtc_write_FREQCORR_reg(a, b)
#define hri_rtcmode2_clear_FREQCORR_reg(a, b) hri_rtc_clear_FREQCORR_reg(a, b)
#define hri_rtcmode2_toggle_FREQCORR_reg(a, b) hri_rtc_toggle_FREQCORR_reg(a, b)
#define hri_rtcmode2_read_FREQCORR_reg(a) hri_rtc_read_FREQCORR_reg(a)
#define hri_rtcmode0_set_DBGCTRL_DBGRUN_bit(a) hri_rtc_set_DBGCTRL_DBGRUN_bit(a)
#define hri_rtcmode0_get_DBGCTRL_DBGRUN_bit(a) hri_rtc_get_DBGCTRL_DBGRUN_bit(a)
#define hri_rtcmode0_write_DBGCTRL_DBGRUN_bit(a, b) hri_rtc_write_DBGCTRL_DBGRUN_bit(a, b)
#define hri_rtcmode0_clear_DBGCTRL_DBGRUN_bit(a) hri_rtc_clear_DBGCTRL_DBGRUN_bit(a)
#define hri_rtcmode0_toggle_DBGCTRL_DBGRUN_bit(a) hri_rtc_toggle_DBGCTRL_DBGRUN_bit(a)
#define hri_rtcmode0_set_DBGCTRL_reg(a, b) hri_rtc_set_DBGCTRL_reg(a, b)
#define hri_rtcmode0_get_DBGCTRL_reg(a, b) hri_rtc_get_DBGCTRL_reg(a, b)
#define hri_rtcmode0_write_DBGCTRL_reg(a, b) hri_rtc_write_DBGCTRL_reg(a, b)
#define hri_rtcmode0_clear_DBGCTRL_reg(a, b) hri_rtc_clear_DBGCTRL_reg(a, b)
#define hri_rtcmode0_toggle_DBGCTRL_reg(a, b) hri_rtc_toggle_DBGCTRL_reg(a, b)
#define hri_rtcmode0_read_DBGCTRL_reg(a) hri_rtc_read_DBGCTRL_reg(a)
#define hri_rtcmode0_set_FREQCORR_SIGN_bit(a) hri_rtc_set_FREQCORR_SIGN_bit(a)
#define hri_rtcmode0_get_FREQCORR_SIGN_bit(a) hri_rtc_get_FREQCORR_SIGN_bit(a)
#define hri_rtcmode0_write_FREQCORR_SIGN_bit(a, b) hri_rtc_write_FREQCORR_SIGN_bit(a, b)
#define hri_rtcmode0_clear_FREQCORR_SIGN_bit(a) hri_rtc_clear_FREQCORR_SIGN_bit(a)
#define hri_rtcmode0_toggle_FREQCORR_SIGN_bit(a) hri_rtc_toggle_FREQCORR_SIGN_bit(a)
#define hri_rtcmode0_set_FREQCORR_VALUE_bf(a, b) hri_rtc_set_FREQCORR_VALUE_bf(a, b)
#define hri_rtcmode0_get_FREQCORR_VALUE_bf(a, b) hri_rtc_get_FREQCORR_VALUE_bf(a, b)
#define hri_rtcmode0_write_FREQCORR_VALUE_bf(a, b) hri_rtc_write_FREQCORR_VALUE_bf(a, b)
#define hri_rtcmode0_clear_FREQCORR_VALUE_bf(a, b) hri_rtc_clear_FREQCORR_VALUE_bf(a, b)
#define hri_rtcmode0_toggle_FREQCORR_VALUE_bf(a, b) hri_rtc_toggle_FREQCORR_VALUE_bf(a, b)
#define hri_rtcmode0_read_FREQCORR_VALUE_bf(a) hri_rtc_read_FREQCORR_VALUE_bf(a)
#define hri_rtcmode0_set_FREQCORR_reg(a, b) hri_rtc_set_FREQCORR_reg(a, b)
#define hri_rtcmode0_get_FREQCORR_reg(a, b) hri_rtc_get_FREQCORR_reg(a, b)
#define hri_rtcmode0_write_FREQCORR_reg(a, b) hri_rtc_write_FREQCORR_reg(a, b)
#define hri_rtcmode0_clear_FREQCORR_reg(a, b) hri_rtc_clear_FREQCORR_reg(a, b)
#define hri_rtcmode0_toggle_FREQCORR_reg(a, b) hri_rtc_toggle_FREQCORR_reg(a, b)
#define hri_rtcmode0_read_FREQCORR_reg(a) hri_rtc_read_FREQCORR_reg(a)
#define hri_rtcmode1_set_DBGCTRL_DBGRUN_bit(a) hri_rtc_set_DBGCTRL_DBGRUN_bit(a)
#define hri_rtcmode1_get_DBGCTRL_DBGRUN_bit(a) hri_rtc_get_DBGCTRL_DBGRUN_bit(a)
#define hri_rtcmode1_write_DBGCTRL_DBGRUN_bit(a, b) hri_rtc_write_DBGCTRL_DBGRUN_bit(a, b)
#define hri_rtcmode1_clear_DBGCTRL_DBGRUN_bit(a) hri_rtc_clear_DBGCTRL_DBGRUN_bit(a)
#define hri_rtcmode1_toggle_DBGCTRL_DBGRUN_bit(a) hri_rtc_toggle_DBGCTRL_DBGRUN_bit(a)
#define hri_rtcmode1_set_DBGCTRL_reg(a, b) hri_rtc_set_DBGCTRL_reg(a, b)
#define hri_rtcmode1_get_DBGCTRL_reg(a, b) hri_rtc_get_DBGCTRL_reg(a, b)
#define hri_rtcmode1_write_DBGCTRL_reg(a, b) hri_rtc_write_DBGCTRL_reg(a, b)
#define hri_rtcmode1_clear_DBGCTRL_reg(a, b) hri_rtc_clear_DBGCTRL_reg(a, b)
#define hri_rtcmode1_toggle_DBGCTRL_reg(a, b) hri_rtc_toggle_DBGCTRL_reg(a, b)
#define hri_rtcmode1_read_DBGCTRL_reg(a) hri_rtc_read_DBGCTRL_reg(a)
#define hri_rtcmode1_set_FREQCORR_SIGN_bit(a) hri_rtc_set_FREQCORR_SIGN_bit(a)
#define hri_rtcmode1_get_FREQCORR_SIGN_bit(a) hri_rtc_get_FREQCORR_SIGN_bit(a)
#define hri_rtcmode1_write_FREQCORR_SIGN_bit(a, b) hri_rtc_write_FREQCORR_SIGN_bit(a, b)
#define hri_rtcmode1_clear_FREQCORR_SIGN_bit(a) hri_rtc_clear_FREQCORR_SIGN_bit(a)
#define hri_rtcmode1_toggle_FREQCORR_SIGN_bit(a) hri_rtc_toggle_FREQCORR_SIGN_bit(a)
#define hri_rtcmode1_set_FREQCORR_VALUE_bf(a, b) hri_rtc_set_FREQCORR_VALUE_bf(a, b)
#define hri_rtcmode1_get_FREQCORR_VALUE_bf(a, b) hri_rtc_get_FREQCORR_VALUE_bf(a, b)
#define hri_rtcmode1_write_FREQCORR_VALUE_bf(a, b) hri_rtc_write_FREQCORR_VALUE_bf(a, b)
#define hri_rtcmode1_clear_FREQCORR_VALUE_bf(a, b) hri_rtc_clear_FREQCORR_VALUE_bf(a, b)
#define hri_rtcmode1_toggle_FREQCORR_VALUE_bf(a, b) hri_rtc_toggle_FREQCORR_VALUE_bf(a, b)
#define hri_rtcmode1_read_FREQCORR_VALUE_bf(a) hri_rtc_read_FREQCORR_VALUE_bf(a)
#define hri_rtcmode1_set_FREQCORR_reg(a, b) hri_rtc_set_FREQCORR_reg(a, b)
#define hri_rtcmode1_get_FREQCORR_reg(a, b) hri_rtc_get_FREQCORR_reg(a, b)
#define hri_rtcmode1_write_FREQCORR_reg(a, b) hri_rtc_write_FREQCORR_reg(a, b)
#define hri_rtcmode1_clear_FREQCORR_reg(a, b) hri_rtc_clear_FREQCORR_reg(a, b)
#define hri_rtcmode1_toggle_FREQCORR_reg(a, b) hri_rtc_toggle_FREQCORR_reg(a, b)
#define hri_rtcmode1_read_FREQCORR_reg(a) hri_rtc_read_FREQCORR_reg(a)

#ifdef __cplusplus
}
#endif

#endif /* _HRI_RTC_C21_H_INCLUDED */
#endif /* _SAMC21_RTC_COMPONENT_ */
