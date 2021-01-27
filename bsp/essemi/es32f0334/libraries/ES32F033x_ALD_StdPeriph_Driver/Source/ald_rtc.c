/**
  ******************************************************************************
  * @file    ald_rtc.c
  * @brief   RTC module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the RTC peripheral:
  *           + Initialization  functions
  *           + Time and date functions
  *           + Alarm functions
  *           + Time stamp functions
  *           + Tamper functions
  *           + Wake-up functions
  *           + Clock output functions
  *           + Peripheral Control functions
  * @version V1.0
  * @date    25 Apr 2017
  * @author  AE Team
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  ********************************************************************************
  * @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    [..]
      (+) Enable the RTC controller interface clock.
      (+) Select the RTC source clock(default LOSC).
      (+) Configure the RTC asynchronous prescaler, synchronous prescaler and hour
          format using the ald_rtc_init() function.

     *** Time and date operation ***
     =================================
     [..]
       (+) To configure the time use the ald_rtc_set_time() function.
       (+) To configure the date use the ald_rtc_set_date() function.
       (+) To read the time use the ald_rtc_get_time() function.
       (+) To read the date use the ald_rtc_get_date() function.

     *** Alarm operation ***
     ===================================
     [..]
       (+) To configure the alarm use ald_rtc_set_alarm() function
       (+) To read the alarm use ald_rtc_get_alarm() function
       (+) To cancel the alarm use ald_rtc_alarm_cmd() function

     *** Time stamp operation ***
     ===================================
     [..]
       (+) To configure the time stamp use ald_rtc_set_time_stamp() function
       (+) To read the time stamp use ald_rtc_get_time_stamp() function
       (+) To cancel the time stamp use ald_rtc_cancel_time_stamp() function

     *** Tamper operation ***
     ===================================
     [..]
       (+) To configure the tamper use ald_rtc_set_tamper() function
       (+) To cancel the tamper use ald_rtc_alarm_cmd() function

     *** Wake-up operation ***
     ===================================
     [..]
       (+) To configure the wake-up parameters use ald_rtc_set_wakeup() function
       (+) To read the re-load register value use ald_rtc_get_wakeup_timer_value() function
       (+) To cancel the wake-up use ald_rtc_cancel_wakeup() function

     *** Output clock operation ***
     ===================================
     [..]
       (+) To configure the clock output type use ald_rtc_set_clock_output() function
       (+) To cancel the clock output use ald_rtc_cancel_clock_output() function

     *** Control functions ***
     ===================================
     [..]
       (+) Configure interrupt enable/disable.
       (+) Enable/disable alarm.
       (+) Configure rtc shift.
       (+) Calibrate time.
       (+) Get interrupt source status.
       (+) Get interrupt flag status.
       (+) Clear interrupt flag.

  ==================================================================
                  ##### RTC and low power modes #####
  ==================================================================
  [..] The MCU can be woken up from a low power mode by an RTC alternate function.
  [..] The RTC alternate functions are the RTC alarms (Alarm A and Alarm B),
       RTC wake-up, RTC tamper event detection and RTC time stamp event detection.
       These RTC alternate functions can wake up the system from the Stop and
       Standby low power modes.
  [..] The system can also wake up from low power modes without depending
       on an external interrupt (Auto-wake-up mode), by using the RTC alarm
       or the RTC wake-up events.
  [..] The RTC provides a programmable time base for waking up from the Stop or
       Standby mode at regular intervals. Wake-up from STOP and STANDBY modes
       is possible only when the RTC clock source is LSE or LSI.

     *** RTC driver macros list ***
     =============================================
     [..]
       Below the list of most used macros in RTC driver.

      (+) RTC_UNLOCK() Disable the protect.
      (+) RTC_LOCK() Enable the protect.
      (+) RTC_BY_PASS_ENABLE() Enable the by-pass shadow register.
      (+) RTC_BY_PASS_DISABLE() Disable the by-pass shadow register.
      (+) RTC_SUMMER_TIME_ENABLE() Enable summer time.
      (+) RTC_SUMMER_TIME_DISABLE() Disable summer time.
      (+) RTC_WINTER_TIME_ENABLE() Enable winter time.
      (+) RTC_WINTER_TIME_DISABLE() Disable winter time.
     [..]
      (@) You can refer to the RTC driver header file for used the macros

    @endverbatim
  ******************************************************************************
  */

#include "ald_rtc.h"
#include "ald_bkpc.h"
#include "ald_tsense.h"
#include "ald_syscfg.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup RTC RTC
  * @brief RTC module driver
  * @{
  */
#ifdef ALD_RTC

/** @addtogroup RTC_Private_Functions  RTC Private Functions
  * @{
  */
/**
  * @brief  Converts form 2 digit BCD to Binary.
  * @param  bcd: BCD value to be converted.
  * @retval Converted word.
  */
static uint32_t bcd_to_dec(uint32_t bcd)
{
	return ((bcd & 0xF) + ((bcd >> 4) & 0xF) * 10);
}

/**
  * @brief  Converts a 2 digit decimal to BCD format.
  * @param  dec: Byte to be converted.
  * @retval Converted byte.
  */
static uint32_t dec_to_bcd(uint32_t dec)
{
	return (((dec / 10) << 4) | (dec % 10));
}

/**
  * @brief  Time and Date consistency check.
  * @param  t_last: Last time.
  * @param  d_last: Last date.
  * @param  time: Current time.
  * @param  date: Current time.
  * @retval status:
  *           0 - Not consistency
  *           1 - Consistency
  */
static int32_t rtc_consistency_check(rtc_time_t *t_last,
			rtc_date_t *d_last, rtc_time_t *time, rtc_date_t *date)
{
	if (t_last->second != time->second)
		return 0;
	if (t_last->minute != time->minute)
		return 0;
	if (t_last->hour != time->hour)
		return 0;
	if (d_last->day != date->day)
		return 0;
	if (d_last->month != date->month)
		return 0;
	if (d_last->year != date->year)
		return 0;

	return 1;
}
/**
  * @}
  */

/** @defgroup RTC_Public_Functions RTC Public Functions
  * @{
  */

/** @defgroup RTC_Public_Functions_Group1 Initialization functions
  * @brief    Initialization functions
  *
  * @verbatim
 ===============================================================================
              ##### Initialization function #####
 ===============================================================================
   [..] This section provides functions allowing to initialize and configure the
         RTC Prescaler (Synchronous and Asynchronous), RTC Hour format, disable
         RTC registers Write protection.
         (#) The RTC Prescaler is programmed to generate the RTC 1Hz time base.
             It is split into 2 programmable prescalers to minimize power consumption.
             (++) A 7-bit asynchronous prescaler and a 13-bit synchronous prescaler.
             (++) When both prescalers are used, it is recommended to configure the
                 asynchronous prescaler to a high value to minimize power consumption.
         (#) All RTC registers are Write protected. Writing to the RTC registers
             is enabled by writing a key into the Write Protection register.

    @endverbatim
  * @{
  */

/**
  * @brief  Reset RTC register.
  * @retval None
  */
void ald_rtc_reset(void)
{
	RTC_UNLOCK();

	WRITE_REG(RTC->CON, 0x0);
	WRITE_REG(RTC->TAMPCON, 0x0);
	WRITE_REG(RTC->WUMAT, 0x0);
	WRITE_REG(RTC->IER, 0x0);
	WRITE_REG(RTC->IFCR, ~0x0);

	RTC_LOCK();
	return;
}

/**
  * @brief  Initialize the RTC module.
  * @param  init: Pointer to rtc_init_t structure which contains
  *         the configuration parameters.
  * @retval None
  */
void ald_rtc_init(rtc_init_t *init)
{
	assert_param(IS_RTC_HOUR_FORMAT(init->hour_format));
	assert_param(IS_RTC_OUTPUT_SEL(init->output));
	assert_param(IS_RTC_OUTPUT_POLARITY(init->output_polarity));

	ald_rtc_reset();
	RTC_UNLOCK();

	MODIFY_REG(RTC->CON, RTC_CON_HFM_MSK, init->hour_format << RTC_CON_HFM_POS);
	MODIFY_REG(RTC->CON, RTC_CON_EOS_MSK, init->output << RTC_CON_EOS_POSS);
	MODIFY_REG(RTC->CON, RTC_CON_POL_MSK, init->output_polarity << RTC_CON_POL_POS);
	MODIFY_REG(RTC->PSR, RTC_PSR_SPRS_MSK, init->synch_pre_div << RTC_PSR_SPRS_POSS);
	MODIFY_REG(RTC->PSR, RTC_PSR_APRS_MSK, init->asynch_pre_div << RTC_PSR_APRS_POSS);
	SET_BIT(RTC->CON, RTC_CON_GO_MSK);

	RTC_LOCK();
	return;
}

/**
  * @brief  Configure the RTC source.
  * @param  sel: RTC source type.
  * @retval None
  */
void ald_rtc_source_select(rtc_source_sel_t sel)
{
	assert_param(IS_RTC_SOURCE_SEL(sel));

	BKPC_UNLOCK();
	MODIFY_REG(BKPC->PCCR, BKPC_PCCR_RTCCS_MSK, sel << BKPC_PCCR_RTCCS_POSS);

	if (sel == RTC_SOURCE_LOSC) {
		SET_BIT(BKPC->CR, BKPC_CR_LOSCEN_MSK);
	}
	else if (sel == RTC_SOURCE_LRC) {
		SET_BIT(BKPC->CR, BKPC_CR_LRCEN_MSK);
	}
	else {
		; /* do nothing */
	}

	BKPC_LOCK();
	return;
}
/**
  * @}
  */

/** @defgroup RTC_Public_Functions_Group2 Time and Date functions
  * @brief    RTC Time and Date functions
  *
  * @verbatim
 ===============================================================================
                 ##### Time and Date functions #####
 ===============================================================================

 [..] This section provides functions allowing:
     [#]
       (+) To configure the time use the ald_rtc_set_time() function.
       (+) To configure the date use the ald_rtc_set_date() function.
       (+) To read the time use the ald_rtc_get_time() function.
       (+) To read the date use the ald_rtc_get_date() function.

    @endverbatim
  * @{
  */

/**
  * @brief  Set specified time.
  * @param  time: pointer to a rtc_time_t structure.
  * @param  format: Data format.
  * @retval ALD status.
  */
ald_status_t ald_rtc_set_time(rtc_time_t *time, rtc_format_t format)
{
	uint32_t tmp;

	assert_param(IS_RTC_FORMAT(format));

	if (format == RTC_FORMAT_DEC) {
		assert_param(IS_RTC_SECOND(time->second));
		assert_param(IS_RTC_MINUTE(time->minute));
		assert_param(IS_RTC_HOUR(time->hour));

		tmp = (dec_to_bcd(time->second)) |
			(dec_to_bcd(time->minute) << 8) |
			(dec_to_bcd(time->hour) << 16);
	}
	else {
		assert_param(IS_RTC_SECOND(bcd_to_dec(time->second)));
		assert_param(IS_RTC_MINUTE(bcd_to_dec(time->minute)));
		assert_param(IS_RTC_HOUR(bcd_to_dec(time->hour)));

		tmp = time->second | (time->minute << 8) | (time->hour << 16);
	}

	RTC_UNLOCK();
	WRITE_REG(RTC->TIME, tmp);
	RTC_LOCK();

	tmp = ald_get_tick();

	while (READ_BIT(RTC->CON, RTC_CON_BUSY_MSK)) {
		if ((ald_get_tick() - tmp) > RTC_TIMEOUT_VALUE)
			return TIMEOUT;
	}

	return OK;
}

/**
  * @brief  Set specified date.
  * @param  date: pointer to a rtc_date_t structure.
  * @param  format: Data format.
  * @retval ALD status.
  */
ald_status_t ald_rtc_set_date(rtc_date_t *date, rtc_format_t format)
{
	uint32_t tmp;

	assert_param(IS_RTC_FORMAT(format));

	if (format == RTC_FORMAT_DEC) {
		assert_param(IS_RTC_DAY(date->day));
		assert_param(IS_RTC_MONTH(date->month));
		assert_param(IS_RTC_YEAR(date->year));

		tmp = (dec_to_bcd(date->day)) |
			(dec_to_bcd(date->month) << 8) |
			(dec_to_bcd(date->year) << 16) |
			(dec_to_bcd(date->week) << 24);
	}
	else {
		assert_param(IS_RTC_DAY(bcd_to_dec(date->day)));
		assert_param(IS_RTC_MONTH(bcd_to_dec(date->month)));
		assert_param(IS_RTC_YEAR(bcd_to_dec(date->year)));

		tmp = date->day | (date->month << 8) |
			(date->year << 16) | (date->week << 24);
	}

	RTC_UNLOCK();
	WRITE_REG(RTC->DATE, tmp);
	RTC_LOCK();

	tmp = ald_get_tick();

	while (READ_BIT(RTC->CON, RTC_CON_BUSY_MSK)) {
		if ((ald_get_tick() - tmp) > RTC_TIMEOUT_VALUE)
			return TIMEOUT;
	}

	return OK;
}

/**
  * @brief  Get current time.
  * @param  time: pointer to a rtc_time_t structure.
  * @param  format: Data format.
  * @retval None
  */
void ald_rtc_get_time(rtc_time_t *time, rtc_format_t format)
{
	uint32_t tmp;

	assert_param(time != NULL);
	assert_param(IS_RTC_FORMAT(format));

	time->sub_sec = RTC->SSEC & 0xFFFF;
	tmp = RTC->TIME;

	if (format == RTC_FORMAT_DEC) {
		time->second = bcd_to_dec(tmp & 0x7F);
		time->minute = bcd_to_dec((tmp >> 8) & 0x7F);
		time->hour   = bcd_to_dec((tmp >> 16) & 0x7F);
	}
	else {
		time->second = tmp & 0x7F;
		time->minute = (tmp >> 8) & 0x7F;
		time->hour   = (tmp >> 16) & 0x7F;
	}

	return;
}

/**
  * @brief  Get current date.
  * @param  date: pointer to a rtc_date_t structure.
  * @param  format: Data format.
  * @retval None
  */
void ald_rtc_get_date(rtc_date_t *date, rtc_format_t format)
{
	uint32_t tmp = RTC->DATE;

	assert_param(date != NULL);
	assert_param(IS_RTC_FORMAT(format));

	if (format == RTC_FORMAT_DEC) {
		date->day   = bcd_to_dec(tmp & 0x3F);
		date->month = bcd_to_dec((tmp >> 8) & 0x1F);
		date->year  = bcd_to_dec((tmp >> 16) & 0xFF);
		date->week  = bcd_to_dec((tmp >> 24) & 0x7);
	}
	else {
		date->day   = tmp & 0x3F;
		date->month = (tmp >> 8) & 0x1F;
		date->year  = (tmp >> 16) & 0xFF;
		date->week  = (tmp >> 24) & 0x7;
	}

	return;
}

/**
  * @brief  Get time and date consistency.
  * @param  date: pointer to a rtc_date_t structure.
  * @param  time: pointer to a rtc_time_t structure.
  * @param  format: Data format.
  * @retval Status:
  *            0 - Consistency
  *           -1 - Not consistency
  */
int32_t ald_rtc_get_date_time(rtc_date_t *date, rtc_time_t *time, rtc_format_t format)
{
	int32_t nr = 3;
	rtc_date_t d_last;
	rtc_time_t t_last;

	while (nr--) {
		ald_rtc_get_time(&t_last, format);
		ald_rtc_get_date(&d_last, format);
		ald_rtc_get_time(time, format);
		ald_rtc_get_date(date, format);

		if (rtc_consistency_check(&t_last, &d_last, time, date))
			return 0;
	}

	return -1;
}
/**
  * @}
  */

/** @defgroup RTC_Public_Functions_Group3 Alarm functions
  * @brief    RTC alarm functions
  *
  * @verbatim
 ===============================================================================
                 ##### Alarm functions #####
 ===============================================================================

 [..] This section provides functions allowing:
     [#]
       (+) To configure the alarm use ald_rtc_set_alarm() function
       (+) To read the alarm use ald_rtc_get_alarm() function

    @endverbatim
  * @{
  */

/**
  * @brief  Set alarm.
  * @param  alarm: pointer to rtc_alarm_t struct.
  * @param  format: Data format.
  * @retval None
  */
void ald_rtc_set_alarm(rtc_alarm_t *alarm, rtc_format_t format)
{
	unsigned int tmp, ss_tmp;

	assert_param(IS_RTC_ALARM(alarm->idx));
	assert_param(IS_RTC_ALARM_SEL(alarm->sel));
	assert_param(IS_RTC_ALARM_SS_MASK(alarm->ss_mask));
	assert_param(IS_RTC_FORMAT(format));

	if (format == RTC_FORMAT_DEC) {
		assert_param(IS_RTC_SECOND(alarm->time.second));
		assert_param(IS_RTC_MINUTE(alarm->time.minute));
		assert_param(IS_RTC_HOUR(alarm->time.hour));

		tmp = (dec_to_bcd(alarm->time.second)) |
		      (dec_to_bcd(alarm->time.minute) << 8) |
		      (dec_to_bcd(alarm->time.hour) << 16) |
		      alarm->mask;

		if (alarm->sel == RTC_SELECT_DAY) {
			assert_param(IS_RTC_DAY(alarm->day));

			tmp |= (dec_to_bcd(alarm->day) << 24);
			tmp &= 0x7FFFFFFF; /* Reset bit31 */
		}
		else {
			tmp |= (1 << (alarm->week + 24));
			tmp |= 0x80000000; /* Set bit31 */
		}
	}
	else {
		assert_param(IS_RTC_SECOND(bcd_to_dec(alarm->time.second)));
		assert_param(IS_RTC_MINUTE(bcd_to_dec(alarm->time.minute)));
		assert_param(IS_RTC_HOUR(bcd_to_dec(alarm->time.hour)));

		tmp = alarm->time.second |
		      (alarm->time.minute << 8) |
		      (alarm->time.hour << 16) |
		      alarm->mask;

		if (alarm->sel == RTC_SELECT_DAY) {
			assert_param(IS_RTC_DAY(bcd_to_dec(alarm->day)));

			tmp |= (alarm->day << 24);
			tmp &= 0x7FFFFFFF; /* Reset bit31 */
		}
		else {
			tmp |= (1 << (alarm->week + 24));
			tmp |= 0x80000000; /* Set bit31 */
		}
	}

	ss_tmp = (alarm->time.sub_sec & 0x7F) |
	         (alarm->ss_mask << 24);

	RTC_UNLOCK();

	if (alarm->idx == RTC_ALARM_A) {
		WRITE_REG(RTC->ALMA, tmp);
		WRITE_REG(RTC->ALMASSEC, ss_tmp);
		SET_BIT(RTC->CON, RTC_CON_ALMAEN_MSK);
	}
	else {
		WRITE_REG(RTC->ALMB, tmp);
		WRITE_REG(RTC->ALMBSSEC, ss_tmp);
		SET_BIT(RTC->CON, RTC_CON_ALMBEN_MSK);
	}

	RTC_LOCK();
	return;
}

/**
  * @brief  Get alarm parameters.
  * @param  alarm: pointer to rtc_alarm_t struct.
  * @param  format: Data format.
  * @retval None
  */
void ald_rtc_get_alarm(rtc_alarm_t *alarm, rtc_format_t format)
{
	uint8_t week;
	uint32_t tmp, ss_tmp;

	assert_param(alarm != NULL);
	assert_param(IS_RTC_FORMAT(format));

	if (alarm->idx == RTC_ALARM_A) {
		tmp    = RTC->ALMA;
		ss_tmp = RTC->ALMASSEC;
	}
	else {
		tmp    = RTC->ALMB;
		ss_tmp = RTC->ALMBSSEC;
	}

	if ((tmp >> 31) & 0x1) {
		alarm->sel = RTC_SELECT_WEEK;
		week = ((tmp >> 24) & 0x7F);

		switch (week) {
		case 1:
			alarm->week = 0;
			break;
		case 2:
			alarm->week = 1;
			break;
		case 4:
			alarm->week = 2;
			break;
		case 8:
			alarm->week = 3;
			break;
		case 16:
			alarm->week = 4;
			break;
		case 32:
			alarm->week = 5;
			break;
		case 64:
			alarm->week = 6;
			break;
		default:
			break;
		}
	}
	else {
		alarm->sel = RTC_SELECT_DAY;

		if (format == RTC_FORMAT_DEC)
			alarm->day = bcd_to_dec((tmp >> 24) & 0x3F);
		else
			alarm->day = (tmp >> 24) & 0x3F;
	}

	if (format == RTC_FORMAT_DEC) {
		alarm->time.second  = bcd_to_dec(tmp & 0x7F);
		alarm->time.minute  = bcd_to_dec((tmp >> 8) & 0x7F);
		alarm->time.hour    = bcd_to_dec((tmp >> 16) & 0x3F);
	}
	else {
		alarm->time.second  = tmp & 0x7F;
		alarm->time.minute  = (tmp >> 8) & 0x7F;
		alarm->time.hour    = (tmp >> 16) & 0x3F;
	}

	alarm->time.sub_sec = ss_tmp & 0x7FFF;
	alarm->ss_mask      = (rtc_sub_second_mask_t)((ss_tmp >> 24) & 0xF);
	alarm->mask         = tmp & ALARM_MASK_ALL;

	return;
}
/**
  * @}
  */

/** @defgroup RTC_Public_Functions_Group4 Time stamp functions
  * @brief    RTC time stamp functions
  *
  * @verbatim
 ===============================================================================
                 ##### Time stamp functions #####
 ===============================================================================

 [..] This section provides functions allowing:
     [#]
       (+) To configure the time stamp use ald_rtc_set_time_stamp() function
       (+) To read the time stamp use ald_rtc_get_time_stamp() function
       (+) To cancel the time stamp use ald_rtc_cancel_time_stamp() function

    @endverbatim
  * @{
  */

/**
  * @brief  Set time stamp.
  * @param  sel: time stamp signal select:
  *           @arg RTC_TS_SIGNAL_SEL_TAMPER0
  *           @arg RTC_TS_SIGNAL_SEL_TAMPER1
  * @param  style: time stamp trigger style:
  *           @arg RTC_TS_RISING_EDGE
  *           @arg RTC_TS_FALLING_EDGE
  * @retval None
  */
void ald_rtc_set_time_stamp(rtc_ts_signal_sel_t sel, rtc_ts_trigger_style_t style)
{
	assert_param(IS_RTC_TS_SIGNAL(sel));
	assert_param(IS_RTC_TS_STYLE(style));

	RTC_UNLOCK();

	CLEAR_BIT(RTC->CON, RTC_CON_TSEN_MSK);
	MODIFY_REG(RTC->CON, RTC_CON_TSSEL_MSK, style << RTC_CON_TSSEL_POS);
	MODIFY_REG(RTC->CON, RTC_CON_TSPIN_MSK, sel << RTC_CON_TSPIN_POS);
	SET_BIT(RTC->CON, RTC_CON_TSEN_MSK);

	RTC_LOCK();
	return;
}

/**
  * @brief  Cancel time stamp.
  * @retval None
  */
void ald_rtc_cancel_time_stamp(void)
{
	RTC_UNLOCK();
	CLEAR_BIT(RTC->CON, RTC_CON_TSEN_MSK);
	RTC_LOCK();

	return;
}

/**
  * @brief  Get time stamp value.
  * @param  ts_time: pointer to rtc_time_t structure.
  * @param  ts_date: pointer to rtc_date_t structure.
  * @param  format: Data format.
  * @retval None
  */
void ald_rtc_get_time_stamp(rtc_time_t *ts_time, rtc_date_t *ts_date, rtc_format_t format)
{
	uint32_t tmp0, tmp1;

	assert_param(ts_time != NULL);
	assert_param(ts_date != NULL);
	assert_param(IS_RTC_FORMAT(format));

	ts_time->sub_sec = RTC->TSSSEC & 0xFFFF;
	tmp0 = RTC->TSTIME;
	tmp1 = RTC->TSDATE;

	if (format == RTC_FORMAT_DEC) {
		ts_time->second = bcd_to_dec(tmp0 & 0x7F);
		ts_time->minute = bcd_to_dec((tmp0 >> 8) & 0x7F);
		ts_time->hour   = bcd_to_dec((tmp0 >> 16) & 0x3F);
		ts_date->day    = bcd_to_dec(tmp1 & 0x3F);
		ts_date->month  = bcd_to_dec((tmp1 >> 8) & 0x1F);
		ts_date->year   = bcd_to_dec((tmp1 >> 16) & 0xFF);
		ts_date->week   = bcd_to_dec((tmp1 >> 24) & 0x7);
	}
	else {
		ts_time->second = tmp0 & 0x7F;
		ts_time->minute = (tmp0 >> 8) & 0x7F;
		ts_time->hour   = (tmp0 >> 16) & 0x3F;
		ts_date->day    = tmp1 & 0x3F;
		ts_date->month  = (tmp1 >> 8) & 0x1F;
		ts_date->year   = (tmp1 >> 16) & 0xFF;
		ts_date->week   = (tmp1 >> 24) & 0x7;
	}

	return;
}
/**
  * @}
  */

/** @defgroup RTC_Public_Functions_Group5 Tamper functions
  * @brief    RTC tamper functions
  *
  * @verbatim
 ===============================================================================
                 ##### Tamper functions #####
 ===============================================================================

 [..] This section provides functions allowing:
     [#]
       (+) To configure the tamper use ald_rtc_set_tamper() function
       (+) To cancel the tamper use ald_rtc_alarm_cmd() function

    @endverbatim
  * @{
  */
/**
  * @brief  Set tamper parameters.
  * @param  tamper: pointer to rtc_tamper_t structure.
  * @retval None
  */
void ald_rtc_set_tamper(rtc_tamper_t *tamper)
{
	assert_param(IS_RTC_TAMPER(tamper->idx));
	assert_param(IS_RTC_TAMPER_TRIGGER(tamper->trig));
	assert_param(IS_RTC_TAMPER_SAMPLING_FREQ(tamper->freq));
	assert_param(IS_RTC_TAMPER_DURATION(tamper->dur));
	assert_param(IS_FUNC_STATE(tamper->ts));

	RTC_UNLOCK();
	MODIFY_REG(RTC->TAMPCON, RTC_TAMPCON_TAMPTS_MSK, tamper->ts << RTC_TAMPCON_TAMPTS_POS);
	MODIFY_REG(RTC->TAMPCON, RTC_TAMPCON_TAMPCKS_MSK, tamper->freq << RTC_TAMPCON_TAMPCKS_POSS);
	MODIFY_REG(RTC->TAMPCON, RTC_TAMPCON_TAMPFLT_MSK, tamper->dur << RTC_TAMPCON_TAMPFLT_POSS);

	if (tamper->idx == RTC_TAMPER_0) {
		MODIFY_REG(RTC->TAMPCON, RTC_TAMPCON_TAMP0LV_MSK, tamper->trig << RTC_TAMPCON_TAMP0LV_POS);
		SET_BIT(RTC->TAMPCON, RTC_TAMPCON_TAMP0EN_MSK);
	}
	else {
		MODIFY_REG(RTC->TAMPCON, RTC_TAMPCON_TAMP1LV_MSK, tamper->trig << RTC_TAMPCON_TAMP1LV_POS);
		SET_BIT(RTC->TAMPCON, RTC_TAMPCON_TAMP1EN_MSK);
	}

	RTC_LOCK();
	return;
}

/**
  * @brief  Cancel tamper.
  * @param  idx: index of tamper:
  *           @arg RTC_TAMPER_0
  *           @arg RTC_TAMPER_1
  * @retval None
  */
void ald_rtc_cancel_tamper(rtc_tamper_idx_t idx)
{
	assert_param(IS_RTC_TAMPER(idx));

	RTC_UNLOCK();

	if (idx == RTC_TAMPER_0)
		CLEAR_BIT(RTC->TAMPCON, RTC_TAMPCON_TAMP0EN_MSK);
	else
		CLEAR_BIT(RTC->TAMPCON, RTC_TAMPCON_TAMP1EN_MSK);

	RTC_LOCK();
	return;
}
/**
  * @}
  */

/** @defgroup RTC_Public_Functions_Group6 Wake-up functions
  * @brief    RTC wake-up functions
  *
  * @verbatim
 ===============================================================================
                 ##### Wake-up functions #####
 ===============================================================================

 [..] This section provides functions allowing:
     [#]
       (+) To configure the wake-up parameters use ald_rtc_set_wakeup() function
       (+) To read the re-load register value use ald_rtc_get_wakeup_timer_value() function
       (+) To cancel the wake-up use ald_rtc_cancel_wakeup() function

    @endverbatim
  * @{
  */
/**
  * @brief  Set wake-up parameters.
  * @param  clock: pointer to rtc_wakeup_clock_t structure.
  * @param  value: re-load value.
  * @retval None
  */
void ald_rtc_set_wakeup(rtc_wakeup_clock_t clock, uint16_t value)
{
	assert_param(IS_RTC_WAKEUP_CLOCK(clock));

	RTC_UNLOCK();
	MODIFY_REG(RTC->CON, RTC_CON_WUCKS_MSK, clock << RTC_CON_WUCKS_POSS);
	WRITE_REG(RTC->WUMAT, value & 0xFFFF);
	SET_BIT(RTC->CON, RTC_CON_WUTE_MSK);
	RTC_LOCK();

	return;
}

/**
  * @brief  Cancel wake-up.
  * @retval None
  */
void ald_rtc_cancel_wakeup(void)
{
	RTC_UNLOCK();
	CLEAR_BIT(RTC->CON, RTC_CON_WUTE_MSK);
	RTC_LOCK();

	return;
}

/**
  * @brief  Get wake-up re-load register value.
  * @retval Value of re-load register.
  */
uint16_t ald_rtc_get_wakeup_timer_value(void)
{
	return RTC->WUMAT & 0xFFFF;
}
/**
  * @}
  */

/** @defgroup RTC_Public_Functions_Group7 Clock output functions
  * @brief    RTC clock output functions
  *
  * @verbatim
 ===============================================================================
                 ##### Clock output functions #####
 ===============================================================================

 [..] This section provides functions allowing:
     [#]
       (+) To configure the clock output type use ald_rtc_set_clock_output() function
       (+) To cancel the clock output use ald_rtc_cancel_clock_output() function

    @endverbatim
  * @{
  */
/**
  * @brief  Set clock output parameters.
  * @param  clock: pointer to rtc_clock_output_t structure.
  * @retval ALD status.
  */
ald_status_t ald_rtc_set_clock_output(rtc_clock_output_t clock)
{
	uint32_t cnt = 4000;
	assert_param(IS_RTC_CLOCK_OUTPUT(clock));

	SYSCFG_UNLOCK();

	if (clock == RTC_CLOCK_OUTPUT_EXA_1) {
		SET_BIT(CMU->CLKENR, CMU_CLKENR_PLL2EN_MSK);
		while ((READ_BIT(CMU->PLLCFG, CMU_PLLCFG_PLL2LCKN_MSK)) && (--cnt));
		cnt = 4000;
		while ((!(READ_BIT(CMU->CLKSR, CMU_CLKSR_PLL2RDY_MSK))) && (--cnt));
	}
	else {
		CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_PLL2EN_MSK);
	}

	SYSCFG_LOCK();
	RTC_UNLOCK();
	MODIFY_REG(RTC->CON, RTC_CON_CKOS_MSK, clock << RTC_CON_CKOS_POSS);
	SET_BIT(RTC->CON, RTC_CON_CKOE_MSK);
	RTC_LOCK();

	return OK;
}

/**
  * @brief  Cancel clock output.
  * @retval None
  */
void ald_rtc_cancel_clock_output(void)
{
	RTC_UNLOCK();
	CLEAR_BIT(RTC->CON, RTC_CON_CKOE_MSK);
	RTC_LOCK();

	return;
}
/**
  * @}
  */

/** @defgroup RTC_Public_Functions_Group8 Control functions
  * @brief    RTC control functions
  *
  * @verbatim
 ===============================================================================
                 ##### Control functions #####
 ===============================================================================

 [..] This section provides functions allowing:
     [#]
       (+) Configure interrupt enable/disable.
       (+) Enable/disable alarm.
       (+) Configure rtc shift.
       (+) Calibrate time.
       (+) Get interrupt source status.
       (+) Get interrupt flag status.
       (+) Clear interrupt flag.

    @endverbatim
  * @{
  */
/**
  * @brief  Enable/disable the specified RTC interrupts.
  * @param  it: Specifies the RTC interrupt sources to be enabled or disabled.
  *         This parameter can be one of the @ref rtc_it_t.
  * @param  state: New state of the specified RTC interrupts.
  *         This parameter can be:
  *           @arg ENABLE
  *           @arg DISABLE
  * @retval None
  */
void ald_rtc_interrupt_config(rtc_it_t it, type_func_t state)
{
	assert_param(IS_RTC_IT(it));
	assert_param(IS_FUNC_STATE(state));

	RTC_UNLOCK();

	if (state == ENABLE)
		SET_BIT(RTC->IER, it);
	else
		CLEAR_BIT(RTC->IER, it);

	RTC_LOCK();
	return;
}

/**
  * @brief  Enable/Disable alarm.
  * @param  idx: index of alarm:
  *           @arg RTC_ALARM_A
  *           @arg RTC_ALARM_B
  * @param  state: New status of the specified alarm:
  *           @arg ENABLE
  *           @arg DISABLE
  * @retval None
  */
void ald_rtc_alarm_cmd(rtc_alarm_idx_t idx, type_func_t state)
{
	assert_param(IS_RTC_ALARM(idx));
	assert_param(IS_FUNC_STATE(state));

	RTC_UNLOCK();

	if (idx == RTC_ALARM_A)
		MODIFY_REG(RTC->CON, RTC_CON_ALMAEN_MSK, state << RTC_CON_ALMAEN_POS);
	else
		MODIFY_REG(RTC->CON, RTC_CON_ALMBEN_MSK, state << RTC_CON_ALMBEN_POS);

	RTC_LOCK();
	return;
}

/**
  * @brief  Set shift parameters.
  * @param  add_1s: Enable/Disable added 1 second.
  * @param  sub_ss: value of sub-sconde.
  * @retval ALD status.
  */
ald_status_t ald_rtc_set_shift(type_func_t add_1s, uint16_t sub_ss)
{
	uint32_t tick;

	assert_param(IS_FUNC_STATE(add_1s));
	assert_param(IS_SHIFT_SUB_SS(sub_ss));

	RTC_UNLOCK();
	MODIFY_REG(RTC->SSECTR, RTC_SSECTR_TRIM_MSK, sub_ss << RTC_SSECTR_TRIM_POSS);
	MODIFY_REG(RTC->SSECTR, RTC_SSECTR_INC_MSK, add_1s << RTC_SSECTR_INC_POS);
	RTC_LOCK();

	tick = ald_get_tick();

	while (READ_BIT(RTC->CON, RTC_CON_SSEC_MSK)) {
		if ((ald_get_tick() - tick) > RTC_TIMEOUT_VALUE)
			return TIMEOUT;
	}

	return OK;
}

/**
  * @brief  Set calibation
  * @param  config: pointer to rtc_cali_t structure.
  * @retval None
  */
void ald_rtc_set_cali(rtc_cali_t *config)
{
	assert_param(IS_RTC_CALI_FREQ(config->cali_freq));
	assert_param(IS_RTC_CALI_TC(config->tc));
	assert_param(IS_RTC_CALC_FREQ(config->calc_freq));
	assert_param(IS_RTC_CALI_CALC(config->calc));
	assert_param(IS_FUNC_STATE(config->acc));

	RTC_UNLOCK();
	RTC_CALI_UNLOCK();

	MODIFY_REG(RTC->CALCON, RTC_CALCON_CALP_MSK, config->cali_freq << RTC_CALCON_CALP_POSS);
	MODIFY_REG(RTC->CALCON, RTC_CALCON_TCM_MSK, config->tc << RTC_CALCON_TCM_POSS);
	MODIFY_REG(RTC->CALCON, RTC_CALCON_TCP_MSK, config->calc_freq << RTC_CALCON_TCP_POSS);
	MODIFY_REG(RTC->CALCON, RTC_CALCON_ALG_MSK, config->calc << RTC_CALCON_ALG_POS);
	MODIFY_REG(RTC->CALCON, RTC_CALCON_DCMACC_MSK, config->acc << RTC_CALCON_DCMACC_POS);
	SET_BIT(RTC->CALCON, RTC_CALCON_CALEN_MSK);

	RTC_CALI_LOCK();
	RTC_LOCK();

	return;
}

/**
  * @brief  Cancel calibration
  * @retval None
  */
void ald_rtc_cancel_cali(void)
{
	RTC_CALI_UNLOCK();
	CLEAR_BIT(RTC->CALCON, RTC_CALCON_CALEN_MSK);
	RTC_CALI_LOCK();

	return;
}

/**
  * @brief  Get calibration status.
  * @retval ALD status.
  */
ald_status_t ald_rtc_get_cali_status(void)
{
	if (READ_BIT(RTC->CALCON, RTC_CALCON_ERR_MSK))
		return ERROR;
	else
		return OK;
}

/**
  * @brief  Write temperature value.
  * @param  temp: the value of temperature.
  * @retval None
  */
void ald_rtc_write_temp(uint16_t temp)
{
	RTC_CALI_UNLOCK();
	MODIFY_REG(RTC->TEMPR, RTC_TEMPR_VAL_MSK, temp << RTC_TEMPR_VAL_POSS);
	RTC_CALI_LOCK();

	return;
}

/**
  * @brief  Get the status of RTC interrupt source.
  * @param  it: Specifies the RTC interrupt source.
  *         This parameter can be one of the @ref rtc_it_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
it_status_t ald_rtc_get_it_status(rtc_it_t it)
{
	assert_param(IS_RTC_IT(it));

	if (READ_BIT(RTC->IER, it))
		return SET;

	return RESET;
}

/**
  * @brief  Get the status of RTC interrupt flag.
  * @param  flag: Specifies the RTC interrupt flag.
  *         This parameter can be one of the @ref rtc_flag_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_rtc_get_flag_status(rtc_flag_t flag)
{
	assert_param(IS_RTC_IF(flag));

	if (READ_BIT(RTC->IFR, flag))
		return SET;

	return RESET;
}

/** @brief  Clear the specified RTC pending flag.
  * @param  flag: specifies the flag to check.
  * @retval None.
  */
void ald_rtc_clear_flag_status(rtc_flag_t flag)
{
	assert_param(IS_RTC_IF(flag));

	RTC_UNLOCK();
	WRITE_REG(RTC->IFCR, flag);
	RTC_LOCK();

	return;
}
/**
  * @}
  */
/**
  * @}
  */
#endif /* ALD_RTC */
/**
  * @}
  */
/**
  * @}
  */
