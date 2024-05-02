/**
  **************************************************************************
  * @file     at32a423_ertc.c
  * @brief    contains all the functions for the ertc firmware library
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#include "at32a423_conf.h"

/** @addtogroup AT32A423_periph_driver
  * @{
  */

/** @defgroup ERTC
  * @brief ERTC driver modules
  * @{
  */

#ifdef ERTC_MODULE_ENABLED

/** @defgroup ERTC_private_functions
  * @{
  */

#define ERTC_TIMEOUT         ((uint32_t) 0x00360000)

/**
  * @brief  number conversion to bcd code.
  * @param  num: number(0~99)
  * @retval bcd code.
  */
uint8_t ertc_num_to_bcd(uint8_t num)
{
  uint8_t bcd_h = 0, bcd_l = 0;

  bcd_h = num / 10;
  bcd_l = num % 10;

  return  ((uint8_t)(bcd_h << 4) | bcd_l);
}

/**
  * @brief  bcd code conversion to number.
  * @param  bcd: bcd code(0~99).
  * @retval number.
  */
uint8_t ertc_bcd_to_num(uint8_t bcd)
{
  return ((((uint8_t)(bcd & (uint8_t)0xF0) >> 4) * 10) + (bcd & (uint8_t)0x0F));
}

/**
  * @brief  enable write protection.
  * @param  none.
  * @retval none
  */
void ertc_write_protect_enable(void)
{
  ERTC->wp = 0xFF;
}

/**
  * @brief  disable write protection.
  * @param  none.
  * @retval none
  */
void ertc_write_protect_disable(void)
{
  ERTC->wp = 0xCA;
  ERTC->wp = 0x53;
}

/**
  * @brief  ertc wait register update finish.
  * @param  none.
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ertc_wait_update(void)
{
  uint32_t timeout = ERTC_TIMEOUT * 2;

  /* clear updf flag */
  ERTC->sts = ~(ERTC_UPDF_FLAG | 0x00000080) | (ERTC->sts_bit.imen << 7);

  while(ERTC->sts_bit.updf == 0)
  {
    if(timeout == 0)
    {
      return ERROR;
    }

    timeout--;
  }

  return SUCCESS;
}

/**
  * @brief  ertc wait flag status.
  * @param  flag: flag to wait.
  *         this parameter can be one of the following values:
  *         - ERTC_ALAWF_FLAG: alarm a register allows write flag.
  *         - ERTC_ALBWF_FLAG: alarm b register allows write flag.
  *         - ERTC_WATWF_FLAG: wakeup timer register allows write flag.
  *         - ERTC_TADJF_FLAG: time adjustment flag.
  *         - ERTC_CALUPDF_FLAG: calibration value update completed flag.
  * @param  status: status to wait.
  *         this parameter can be one of the following values:
  *         - SET.
  *         - RESET.
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ertc_wait_flag(uint32_t flag, flag_status status)
{
  uint32_t timeout = ERTC_TIMEOUT;

  while(ertc_flag_get(flag) == status)
  {
    if(timeout == 0)
    {
      /* enable write protection */
      ertc_write_protect_enable();

      return ERROR;
    }

    timeout--;
  }

  return SUCCESS;
}

/**
  * @brief  ertc enter init mode.
  * @param  none.
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ertc_init_mode_enter(void)
{
  uint32_t timeout = ERTC_TIMEOUT * 2;

  if(ERTC->sts_bit.imf == 0)
  {
    /* enter init mode */
    ERTC->sts = 0xFFFFFFFF;

    while(ERTC->sts_bit.imf == 0)
    {
      if(timeout == 0)
      {
        /* enable write protection */
        ertc_write_protect_enable();

        return ERROR;
      }

      timeout--;
    }
  }

  return SUCCESS;
}

/**
  * @brief  ertc exit init mode.
  * @param  none.
  * @retval none.
  */
void ertc_init_mode_exit(void)
{
  ERTC->sts = 0xFFFFFF7F;

  /* wait register update finish */
  ertc_wait_update();
}

/**
  * @brief  ertc reset all register.
  * @param  none.
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ertc_reset(void)
{
  /* disable write protection */
  ertc_write_protect_disable();

  ERTC->ctrl = (uint32_t)0x00000000;

  /* enter init mode */
  if(ertc_init_mode_enter() != SUCCESS)
  {
    return ERROR;
  }

  /* reset register */
  ERTC->time   = (uint32_t)0x00000000;
  ERTC->date   = (uint32_t)0x00002101;
  ERTC->ctrl   = (uint32_t)0x00000000;
  ERTC->div    = (uint32_t)0x007F00FF;
  ERTC->wat    = (uint32_t)0x0000FFFF;
  ERTC->ala    = (uint32_t)0x00000000;
  ERTC->alb    = (uint32_t)0x00000000;
  ERTC->tadj   = (uint32_t)0x00000000;
  ERTC->scal   = (uint32_t)0x00000000;
  ERTC->tamp   = (uint32_t)0x00000000;
  ERTC->alasbs = (uint32_t)0x00000000;
  ERTC->albsbs = (uint32_t)0x00000000;
  ERTC->sts    = (uint32_t)0x00000000;

  /* wait calendar update */
  ertc_wait_update();

  /* enable write protection */
  ertc_write_protect_enable();

  return SUCCESS;
}

/**
  * @brief  ertc division set.
  * @param  div_a: division a (0~0x7F).
  * @param  div_b: division b (0~0x7FFF).
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ertc_divider_set(uint16_t div_a, uint16_t div_b)
{
  /* disable write protection */
  ertc_write_protect_disable();

  /* enter init mode */
  if(ertc_init_mode_enter() != SUCCESS)
  {
    return ERROR;
  }

  /* config the ertc divider */
  ERTC->div_bit.diva = div_a;
  ERTC->div_bit.divb = div_b;

  /* exit init mode */
  ertc_init_mode_exit();

  /* enable write protection */
  ertc_write_protect_enable();

  return SUCCESS;
}

/**
  * @brief  ertc hour mode set.
  * @param  mode: hour mode.
  *         this parameter can be one of the following values:
  *         - ERTC_HOUR_MODE_24: 24-hour format.
  *         - ERTC_HOUR_MODE_12: 12-hour format.
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ertc_hour_mode_set(ertc_hour_mode_set_type mode)
{
  /* disable write protection */
  ertc_write_protect_disable();

  /* enter init mode */
  if(ertc_init_mode_enter() != SUCCESS)
  {
    return ERROR;
  }

  /* write register */
  ERTC->ctrl_bit.hm = mode;

  /* exit init mode */
  ertc_init_mode_exit();

  /* enable write protection */
  ertc_write_protect_enable();

  return SUCCESS;
}

/**
  * @brief  set date.
  * @param  year: year (0~99).
  * @param  month: month (1~12).
  * @param  date: date (1~31).
  * @param  week: week (1~7).
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ertc_date_set(uint8_t year, uint8_t month, uint8_t date, uint8_t week)
{
  ertc_reg_date_type reg;

  reg.date = 0;

  reg.date_bit.y  = ertc_num_to_bcd(year);
  reg.date_bit.m  = ertc_num_to_bcd(month);
  reg.date_bit.d  = ertc_num_to_bcd(date);
  reg.date_bit.wk = week;

  /* disable write protection */
  ertc_write_protect_disable();

  /* enter init mode */
  if(ertc_init_mode_enter() != SUCCESS)
  {
    return ERROR;
  }

  /* set the ertc_date register */
  ERTC->date = reg.date;

  /* exit init mode */
  ertc_init_mode_exit();

  /* enable write protection */
  ertc_write_protect_enable();

  return SUCCESS;
}

/**
  * @brief  set time.
  * @param  hour: hour (0~23).
  * @param  min: minute (0~59).
  * @param  sec: second (0~59).
  * @param  ampm: hour mode.
  *         this parameter can be one of the following values:
  *         - ERTC_24H: 24-hour format.
  *         - ERTC_AM: 12-hour format, ante meridiem.
  *         - ERTC_PM: 12-hour format, post meridiem.
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ertc_time_set(uint8_t hour, uint8_t min, uint8_t sec, ertc_am_pm_type ampm)
{
  ertc_reg_time_type reg;

  reg.time = 0;

  reg.time_bit.h = ertc_num_to_bcd(hour);
  reg.time_bit.m = ertc_num_to_bcd(min);
  reg.time_bit.s = ertc_num_to_bcd(sec);
  reg.time_bit.ampm = ampm;

  /* disable write protection */
  ertc_write_protect_disable();

  /* enter init mode */
  if(ertc_init_mode_enter() != SUCCESS)
  {
    return ERROR;
  }

  ERTC->time = reg.time;

  /* exit init mode */
  ertc_init_mode_exit();

  /* enable write protection */
  ertc_write_protect_enable();

  return SUCCESS;
}

/**
  * @brief  get calendar
  * @param  time: ertc time.
  * @retval none.
  */
void ertc_calendar_get(ertc_time_type* time)
{
  ertc_reg_time_type reg_tm;
  ertc_reg_date_type reg_dt;

  reg_tm.time = ERTC->time;
  reg_dt.date = ERTC->date;

  time->hour  = ertc_bcd_to_num(reg_tm.time_bit.h);
  time->min   = ertc_bcd_to_num(reg_tm.time_bit.m);
  time->sec   = ertc_bcd_to_num(reg_tm.time_bit.s);
  time->ampm  = (ertc_am_pm_type)reg_tm.time_bit.ampm;

  time->year  = ertc_bcd_to_num(reg_dt.date_bit.y);
  time->month = ertc_bcd_to_num(reg_dt.date_bit.m);
  time->day   = ertc_bcd_to_num(reg_dt.date_bit.d);
  time->week  = reg_dt.date_bit.wk;
}

/**
  * @brief  get current sub second.
  * @param  none.
  * @retval sub second.
  */
uint32_t ertc_sub_second_get(void)
{
  uint32_t reg = 0;

  reg = ERTC->sbs;

  (void) (ERTC->date);

  return (reg);
}

/**
  * @brief  set which bits are irrelevant to the alarm match.
  * @param  alarm_x: select the alarm.
  *         this parameter can be one of the following values:
  *         - ERTC_ALA: alarm a.
  *         - ERTC_ALB: alarm b.
  * @param  mask: select which bits are irrelevant to the alarm match.
  *         this parameter can be one of the following values:
  *         - ERTC_ALARM_MASK_NONE: match all.
  *         - ERTC_ALARM_MASK_SEC: don't match seconds.
  *         - ERTC_ALARM_MASK_MIN: don't match minute.
  *         - ERTC_ALARM_MASK_HOUR: don't match hour.
  *         - ERTC_ALARM_MASK_DATE_WEEK: don't match date or week.
  *         - ERTC_ALARM_MASK_ALL: don't match all.
  * @param  alarm: alarm para.
  * @retval none.
  */
void ertc_alarm_mask_set(ertc_alarm_type alarm_x, uint32_t mask)
{
  uint32_t reg;

  /* disable write protection */
  ertc_write_protect_disable();

  if(alarm_x == ERTC_ALA)
  {
    reg = ERTC->ala;

    reg &= ~ERTC_ALARM_MASK_ALL;
    reg |= mask;

    ERTC->ala= reg;
  }
  else
  {
    reg = ERTC->alb;

    reg &= ~ERTC_ALARM_MASK_ALL;
    reg |= mask;

    ERTC->alb= reg;
  }

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  alarm week or date mode select.
  * @param  alarm_x: select the alarm.
  *         this parameter can be one of the following values:
  *         - ERTC_ALA: alarm a.
  *         - ERTC_ALB: alarm b.
  * @param  wk: week or date mode select.
  *         this parameter can be one of the following values:
  *         - ERTC_SLECT_DATE: slect date mode.
  *         - ERTC_SLECT_WEEK: slect week mode.
  * @retval none.
  */
void ertc_alarm_week_date_select(ertc_alarm_type alarm_x, ertc_week_date_select_type wk)
{
  /* disable write protection */
  ertc_write_protect_disable();

  if(alarm_x == ERTC_ALA)
  {
    ERTC->ala_bit.wksel = wk;
  }
  else
  {
    ERTC->alb_bit.wksel = wk;
  }

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  set alarm.
  * @param  alarm_x: select the alarm.
  *         this parameter can be one of the following values:
  *         - ERTC_ALA: alarm a.
  *         - ERTC_ALB: alarm b.
  * @param  week_day: week or date.
  *         - week: 1~7.
  *         - date: 1~31.
  * @param  hour: hour (0~23).
  * @param  min: minute (0~59).
  * @param  sec: second (0~59).
  * @param  ampm: hour mode.
  *         this parameter can be one of the following values:
  *         - ERTC_24H: 24-hour format.
  *         - ERTC_AM: 12-hour format, ante meridiem.
  *         - ERTC_PM: 12-hour format, post meridiem.
  * @param  alarm: alarm para.
  * @retval none.
  */
void ertc_alarm_set(ertc_alarm_type alarm_x, uint8_t week_date, uint8_t hour, uint8_t min, uint8_t sec, ertc_am_pm_type ampm)
{
  ertc_reg_alarm_type reg;

  if(alarm_x == ERTC_ALA)
  {
    reg.ala = ERTC->ala;
  }
  else
  {
    reg.ala = ERTC->alb;
  }

  reg.ala_bit.d = ertc_num_to_bcd(week_date);
  reg.ala_bit.h = ertc_num_to_bcd(hour);
  reg.ala_bit.m = ertc_num_to_bcd(min);
  reg.ala_bit.s = ertc_num_to_bcd(sec);
  reg.ala_bit.ampm = ampm;

  /* disable write protection */
  ertc_write_protect_disable();

  if(alarm_x == ERTC_ALA)
  {
    ERTC->ala= reg.ala;
  }
  else
  {
    ERTC->alb = reg.ala;
  }

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  set alarm sub second.
  * @param  alarm_x: select the alarm.
  *         this parameter can be one of the following values:
  *         - ERTC_ALA: alarm a.
  *         - ERTC_ALB: alarm b.
  * @param  value: sub second value.
  * @param  mask: sub second mask.
  *         this parameter can be one of the following values:
  *         - ERTC_ALARM_SBS_MASK_ALL: do not match the sub-second.
  *         - ERTC_ALARM_SBS_MASK_14_1: only compare bit [0].
  *         - ERTC_ALARM_SBS_MASK_14_2: only compare bit [1:0].
  *         - ERTC_ALARM_SBS_MASK_14_3: only compare bit [2:0].
  *         - ERTC_ALARM_SBS_MASK_14_4: only compare bit [3:0].
  *         - ERTC_ALARM_SBS_MASK_14_5: only compare bit [4:0].
  *         - ERTC_ALARM_SBS_MASK_14_6: only compare bit [5:0].
  *         - ERTC_ALARM_SBS_MASK_14_7: only compare bit [6:0].
  *         - ERTC_ALARM_SBS_MASK_14_8: only compare bit [7:0].
  *         - ERTC_ALARM_SBS_MASK_14_9: only compare bit [8:0].
  *         - ERTC_ALARM_SBS_MASK_14_10: only compare bit [9:0].
  *         - ERTC_ALARM_SBS_MASK_14_11: only compare bit [10:0].
  *         - ERTC_ALARM_SBS_MASK_14_12: only compare bit [11:0].
  *         - ERTC_ALARM_SBS_MASK_14_13: only compare bit [12:0].
  *         - ERTC_ALARM_SBS_MASK_14: only compare bit [13:0].
  *         - ERTC_ALARM_SBS_MASK_NONE:  compare bit [14:0].
  * @retval none.
  */
void ertc_alarm_sub_second_set(ertc_alarm_type alarm_x, uint32_t value, ertc_alarm_sbs_mask_type mask)
{
  /* disable write protection */
  ertc_write_protect_disable();

  if(alarm_x == ERTC_ALA)
  {
    ERTC->alasbs_bit.sbsmsk = mask;
    ERTC->alasbs_bit.sbs = value;
  }
  else
  {
    ERTC->albsbs_bit.sbsmsk = mask;
    ERTC->albsbs_bit.sbs = value;
  }

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  enable or disable alarm clock.
  * @param  alarm_x: select the alarm.
  *         this parameter can be one of the following values:
  *         - ERTC_ALA: alarm a.
  *         - ERTC_ALB: alarm b.
  * @param  new_state (TRUE or FALSE).
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ertc_alarm_enable(ertc_alarm_type alarm_x, confirm_state new_state)
{
  /* disable write protection */
  ertc_write_protect_disable();

  if(alarm_x == ERTC_ALA)
  {
    ERTC->ctrl_bit.alaen = new_state;

    if(new_state == FALSE)
    {
      if(ertc_wait_flag(ERTC_ALAWF_FLAG, RESET) != SUCCESS)
      {
        return ERROR;
      }
    }
  }
  else
  {
    ERTC->ctrl_bit.alben = new_state;

    if(new_state == FALSE)
    {
      if(ertc_wait_flag(ERTC_ALBWF_FLAG, RESET) != SUCCESS)
      {
        return ERROR;
      }
    }
  }

  /* enable write protection */
  ertc_write_protect_enable();

  return SUCCESS;
}

/**
  * @brief  get alarm value.
  * @param  alarm_x: select the alarm.
  *         this parameter can be one of the following values:
  *         - ERTC_ALA: alarm a.
  *         - ERTC_ALB: alarm b.
  * @param  alarm: alarm para.
  * @retval none.
  */
void ertc_alarm_get(ertc_alarm_type alarm_x, ertc_alarm_value_type* alarm)
{
  ertc_reg_alarm_type reg;

  reg.ala = 0;

  if(alarm_x == ERTC_ALA)
  {
    reg.ala = ERTC->ala;
  }
  else
  {
    reg.ala = ERTC->alb;
  }

  alarm->day           = ertc_bcd_to_num(reg.ala_bit.d);
  alarm->week          = ertc_bcd_to_num(reg.ala_bit.d);
  alarm->hour          = ertc_bcd_to_num(reg.ala_bit.h);
  alarm->min           = ertc_bcd_to_num(reg.ala_bit.m);
  alarm->sec           = ertc_bcd_to_num(reg.ala_bit.s);
  alarm->ampm          = (ertc_am_pm_type)reg.ala_bit.ampm;
  alarm->week_date_sel = reg.ala_bit.wksel;
  alarm->mask          = reg.ala & ERTC_ALARM_MASK_ALL;
}

/**
  * @brief  get alarm sub second.
  * @param  alarm_x: select the alarm.
  *         this parameter can be one of the following values:
  *         - ERTC_ALA: alarm a.
  *         - ERTC_ALB: alarm b.
  * @retval sub second.
  */
uint32_t ertc_alarm_sub_second_get(ertc_alarm_type alarm_x)
{
  if(alarm_x == ERTC_ALA)
  {
    return (ERTC->alasbs_bit.sbs);
  }
  else
  {
    return (ERTC->albsbs_bit.sbs);
  }
}

/**
  * @brief  set wakeup timer clock.
  * @param  clock: wakeup timer clock source.
  *         this parameter can be one of the following values:
  *         - ERTC_WAT_CLK_ERTCCLK_DIV16: ERTC_CLK / 16.
  *         - ERTC_WAT_CLK_ERTCCLK_DIV8: ERTC_CLK / 8.
  *         - ERTC_WAT_CLK_ERTCCLK_DIV4: ERTC_CLK / 4.
  *         - ERTC_WAT_CLK_ERTCCLK_DIV2: ERTC_CLK / 2.
  *         - ERTC_WAT_CLK_CK_B_16BITS: CK_B, wakeup counter = ERTC_WAT
  *         - ERTC_WAT_CLK_CK_B_17BITS: CK_B, wakeup counter = ERTC_WAT + 65535.
  * @retval none.
  */
void ertc_wakeup_clock_set(ertc_wakeup_clock_type clock)
{
  /* disable write protection */
  ertc_write_protect_disable();

  ERTC->ctrl_bit.watclk = clock;

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  set wakeup counter.
  * @param  counter: wakeup counter(0~65535).
  * @retval none.
  */
void ertc_wakeup_counter_set(uint32_t counter)
{
  /* disable write protection */
  ertc_write_protect_disable();

  ERTC->wat_bit.val = counter;

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  get wakeup counter.
  * @param  none.
  * @retval wakeup counter.
  */
uint16_t ertc_wakeup_counter_get(void)
{
  return ERTC->wat_bit.val;
}

/**
  * @brief  enable or disable wakeup timer.
  * @param  new_state (TRUE or FALSE).
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ertc_wakeup_enable(confirm_state new_state)
{
  /* disable write protection */
  ertc_write_protect_disable();

  ERTC->ctrl_bit.waten = new_state;

  if(new_state == FALSE)
  {
    if(ertc_wait_flag(ERTC_WATWF_FLAG, RESET) != SUCCESS)
    {
      return ERROR;
    }
  }

  /* enable write protection */
  ertc_write_protect_enable();

  return SUCCESS;
}

/**
  * @brief  config the smooth calibration.
  * @param  period: calibration period.
  *         this parameter can be one of the following values:
  *         - ERTC_SMOOTH_CAL_PERIOD_32: 32 second calibration period.
  *         - ERTC_SMOOTH_CAL_PERIOD_16: 16 second calibration period.
  *         - ERTC_SMOOTH_CAL_PERIOD_8: 8 second calibration period.
  * @param  clk_add: add clock.
  *         this parameter can be one of the following values:
  *         - ERTC_SMOOTH_CAL_CLK_ADD_0: do not increase clock.
  *         - ERTC_SMOOTH_CAL_CLK_ADD_512: add 512 clocks.
  * @param  clk_dec: decrease clock(0~511).
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ertc_smooth_calibration_config(ertc_smooth_cal_period_type period, ertc_smooth_cal_clk_add_type clk_add, uint32_t clk_dec)
{
  ertc_reg_scal_type reg;

  /* disable write protection */
  ertc_write_protect_disable();

  if(ertc_wait_flag(ERTC_CALUPDF_FLAG, SET) != SUCCESS)
  {
    return ERROR;
  }

  reg.scal = 0;

  switch (period)
  {
    case ERTC_SMOOTH_CAL_PERIOD_32:
      break;
    case ERTC_SMOOTH_CAL_PERIOD_16:
       reg.scal_bit.cal16 = 1;
      break;
    case ERTC_SMOOTH_CAL_PERIOD_8:
       reg.scal_bit.cal8 = 1;
      break;
    default:
      break;
  }

  reg.scal_bit.add = clk_add;
  reg.scal_bit.dec = clk_dec;

  ERTC->scal = reg.scal;

  /* enable write protection */
  ertc_write_protect_enable();

  return SUCCESS;
}

/**
  * @brief  calibration output source select.
  * @param  output: output source.
  *         this parameter can be one of the following values:
  *         - ERTC_CAL_OUTPUT_512HZ: output 512 hz.
  *         - ERTC_CAL_OUTPUT_1HZ: output 1 hz.
  * @retval none.
  */
void ertc_cal_output_select(ertc_cal_output_select_type output)
{
  /* disable write protection */
  ertc_write_protect_disable();

  ERTC->ctrl_bit.calosel = output;

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  enable or disable calibration output.
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void ertc_cal_output_enable(confirm_state new_state)
{
  /* disable write protection */
  ertc_write_protect_disable();

  ERTC->ctrl_bit.caloen = new_state;

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  adjust the time.
  * @param  add1s: second operation.
  *         this parameter can be one of the following values:
  *         - ERTC_TIME_ADD_NONE: none operation.
  *         - ERTC_TIME_ADD_1S: add 1 second.
  * @param  decsbs: decrease sub second(0~0x7FFF).
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ertc_time_adjust(ertc_time_adjust_type add1s, uint32_t decsbs)
{
  ertc_reg_tadj_type reg;

  reg.tadj = 0;

  /* disable write protection */
  ertc_write_protect_disable();

  if(ertc_wait_flag(ERTC_TADJF_FLAG, SET) != SUCCESS)
  {
    return ERROR;
  }

  /* check if the reference clock detection is disabled */
  if(ERTC->ctrl_bit.rcden == 0)
  {
    reg.tadj_bit.add1s = add1s;
    reg.tadj_bit.decsbs = decsbs;

    ERTC->tadj = reg.tadj;

    if(ertc_wait_update() == ERROR)
    {
      return ERROR;
    }
  }
  else
  {
    return ERROR;
  }

  /* enable write protection */
  ertc_write_protect_enable();

  return SUCCESS;
}

/**
  * @brief  config the daylight saving time.
  * @param  operation: time adjust.
  *         this parameter can be one of the following values:
  *         - ERTC_DST_ADD_1H: add 1 hour.
  *         - ERTC_DST_DEC_1H: dec 1 hour.
  * @param  save: operation save.
  *         this parameter can be one of the following values:
  *         - ERTC_DST_SAVE_0: set the bpr register value to 0.
  *         - ERTC_DST_SAVE_1: set the bpr register value to 1.
  * @retval none.
  */
void ertc_daylight_set(ertc_dst_operation_type operation, ertc_dst_save_type save)
{
  /* disable write protection */
  ertc_write_protect_disable();

  if(operation == ERTC_DST_ADD_1H)
  {
    ERTC->ctrl_bit.add1h = 1;
  }
  else
  {
    ERTC->ctrl_bit.dec1h = 1;
  }

  ERTC->ctrl_bit.bpr = save;

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  get the bpr value.
  * @param  none.
  * @retval bpr value.
  */
uint8_t ertc_daylight_bpr_get(void)
{
  return ERTC->ctrl_bit.bpr;
}

/**
  * @brief  enable or disable refer clock detect.
  * @param  new_state (TRUE or FALSE).
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ertc_refer_clock_detect_enable(confirm_state new_state)
{
  /* disable write protection */
  ertc_write_protect_disable();

  /* enter init mode */
  if(ertc_init_mode_enter() != SUCCESS)
  {
    return ERROR;
  }

  /* write register */
  ERTC->ctrl_bit.rcden = new_state;

  /* exit init mode */
  ertc_init_mode_exit();

  /* enable write protection */
  ertc_write_protect_enable();

  return SUCCESS;
}

/**
  * @brief  enable or disable direct read mode.
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void ertc_direct_read_enable(confirm_state new_state)
{
  /* disable write protection */
  ertc_write_protect_disable();

  ERTC->ctrl_bit.dren = new_state;

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  set the output mode.
  * @param  source: output source.
  *         this parameter can be one of the following values:
  *         - ERTC_OUTPUT_DISABLE: diable output.
  *         - ERTC_OUTPUT_ALARM_A: output alarm a event.
  *         - ERTC_OUTPUT_ALARM_B: output alarm b event.
  *         - ERTC_OUTPUT_WAKEUP: output wakeup event.
  * @param  polarity: output polarity.
  *         this parameter can be one of the following values:
  *         - ERTC_OUTPUT_POLARITY_HIGH: when the event occurs, the output is high.
  *         - ERTC_OUTPUT_POLARITY_LOW: when the event occurs, the output is low.
  * @param  type: output type.
  *         this parameter can be one of the following values:
  *         - ERTC_OUTPUT_TYPE_OPEN_DRAIN: open drain output.
  *         - ERTC_OUTPUT_TYPE_PUSH_PULL: push pull output.
  * @retval none.
  */
void ertc_output_set(ertc_output_source_type source, ertc_output_polarity_type polarity, ertc_output_type type)
{
  /* disable write protection */
  ertc_write_protect_disable();

  ERTC->ctrl_bit.outp = polarity;

  ERTC->tamp_bit.outtype = type;

  ERTC->ctrl_bit.outsel = source;

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  timestamp detection pin selection.
  * @param  pin: data register
  *         this parameter can be one of the following values:
  *         - ERTC_PIN_PC13: pc13 is used as timestamp detection pin.
  *         - ERTC_PIN_PA0: pa0 is used as timestamp detection pin.
  * @retval data value.
  */
void ertc_timestamp_pin_select(ertc_pin_select_type pin)
{
  /* disable write protection */
  ertc_write_protect_disable();

  ERTC->tamp_bit.tspin = pin;

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  set the timestamp valid edge.
  * @param  edge: calibration period.
  *         this parameter can be one of the following values:
  *         - ERTC_TIMESTAMP_EDGE_RISING : rising edge trigger.
  *         - ERTC_TIMESTAMP_EDGE_FALLING: falling edge trigger.
  * @retval none.
  */
void ertc_timestamp_valid_edge_set(ertc_timestamp_valid_edge_type edge)
{
  /* disable write protection */
  ertc_write_protect_disable();

  ERTC->ctrl_bit.tsedg = edge;

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  enable or disable timestamp.
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void ertc_timestamp_enable(confirm_state new_state)
{
  /* disable write protection */
  ertc_write_protect_disable();

  ERTC->ctrl_bit.tsen = new_state;

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  get the timestamp.
  * @param  time: time.
  * @param  date: date.
  * @retval none.
  */
void ertc_timestamp_get(ertc_time_type* time)
{
  ertc_reg_tstm_type tmtime;
  ertc_reg_tsdt_type tmdate;

  tmtime.tstm = ERTC->tstm;
  tmdate.tsdt = ERTC->tsdt;

  time->year  = 0;
  time->month = ertc_bcd_to_num(tmdate.tsdt_bit.m);
  time->day   = ertc_bcd_to_num(tmdate.tsdt_bit.d);
  time->week  = ertc_bcd_to_num(tmdate.tsdt_bit.wk);
  time->hour  = ertc_bcd_to_num(tmtime.tstm_bit.h);
  time->min   = ertc_bcd_to_num(tmtime.tstm_bit.m);
  time->sec   = ertc_bcd_to_num(tmtime.tstm_bit.s);
  time->ampm  = (ertc_am_pm_type)tmtime.tstm_bit.ampm;
}

/**
  * @brief  get the timestamp sub second.
  * @param  none.
  * @retval timestamp sub second.
  */
uint32_t ertc_timestamp_sub_second_get(void)
{
  return ERTC->tssbs_bit.sbs;
}

/**
  * @brief  tamper 1 detection pin selection.
  * @param  pin: data register
  *         this parameter can be one of the following values:
  *         - ERTC_PIN_PC13: pc13 is used as tamper 1 detection pin.
  *         - ERTC_PIN_PA0: pa0 is used as tamper 1 detection pin.
  * @retval data value.
  */
void ertc_tamper_1_pin_select(ertc_pin_select_type pin)
{
  /* disable write protection */
  ertc_write_protect_disable();

  ERTC->tamp_bit.tp1pin = pin;

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  enable or disable tamper pin pull up.
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void ertc_tamper_pull_up_enable(confirm_state new_state)
{
  /* disable write protection */
  ertc_write_protect_disable();

  ERTC->tamp_bit.tppu = !new_state;

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  set the tamper pin pre-charge time.
  * @param  precharge: tamper detection pre-charge time
  *         this parameter can be one of the following values:
  *         - ERTC_TAMPER_PR_1_ERTCCLK: pre-charge time is 1 ERTC_CLK.
  *         - ERTC_TAMPER_PR_2_ERTCCLK: pre-charge time is 2 ERTC_CLK.
  *         - ERTC_TAMPER_PR_4_ERTCCLK: pre-charge time is 4 ERTC_CLK.
  *         - ERTC_TAMPER_PR_8_ERTCCLK: pre-charge time is 8 ERTC_CLK.
  * @retval none.
  */
void ertc_tamper_precharge_set(ertc_tamper_precharge_type precharge)
{
  /* disable write protection */
  ertc_write_protect_disable();

  ERTC->tamp_bit.tppr = precharge;

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  set the tamper filter time.
  * @param  filter: tamper filter.
  *         this parameter can be one of the following values:
  *         - ERTC_TAMPER_FILTER_DISABLE: disable filter function.
  *         - ERTC_TAMPER_FILTER_2: 2 consecutive samples arw valid, effective tamper event.
  *         - ERTC_TAMPER_FILTER_4: 4 consecutive samples arw valid, effective tamper event.
  *         - ERTC_TAMPER_FILTER_8: 8 consecutive samples arw valid, effective tamper event.
  * @retval none.
  */
void ertc_tamper_filter_set(ertc_tamper_filter_type filter)
{
  /* disable write protection */
  ertc_write_protect_disable();

  ERTC->tamp_bit.tpflt = filter;

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  set the tamper detection frequency.
  * @param  freq: tamper detection frequency.
  *         this parameter can be one of the following values:
  *         - ERTC_TAMPER_FREQ_DIV_32768: ERTC_CLK / 32768.
  *         - ERTC_TAMPER_FREQ_DIV_16384: ERTC_CLK / 16384.
  *         - ERTC_TAMPER_FREQ_DIV_8192: ERTC_CLK / 8192.
  *         - ERTC_TAMPER_FREQ_DIV_4096: ERTC_CLK / 4096.
  *         - ERTC_TAMPER_FREQ_DIV_2048: ERTC_CLK / 2048.
  *         - ERTC_TAMPER_FREQ_DIV_1024: ERTC_CLK / 1024.
  *         - ERTC_TAMPER_FREQ_DIV_512: ERTC_CLK / 512.
  *         - ERTC_TAMPER_FREQ_DIV_256: ERTC_CLK / 256.
  * @retval none.
  */
void ertc_tamper_detect_freq_set(ertc_tamper_detect_freq_type freq)
{
  /* disable write protection */
  ertc_write_protect_disable();

  ERTC->tamp_bit.tpfreq = freq;

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  set the tamper trigger.
  * @param  tamper_x: select the tamper.
  *         this parameter can be one of the following values:
  *         - ERTC_TAMPER_1: tamper 1.
  *         - ERTC_TAMPER_2: tamper 2.
  * @param  trigger: tamper valid edge.
  *         this parameter can be one of the following values:
  *         - ERTC_TAMPER_EDGE_RISING: rising gedge.
  *         - ERTC_TAMPER_EDGE_FALLING: falling gedge.
  *         - ERTC_TAMPER_EDGE_LOW: low level.
  *         - ERTC_TAMPER_EDGE_HIGH: high level.
  * @param  alarm: alarm para.
  * @retval none.
  */
void ertc_tamper_valid_edge_set(ertc_tamper_select_type tamper_x, ertc_tamper_valid_edge_type trigger)
{
  /* disable write protection */
  ertc_write_protect_disable();

  if(tamper_x == ERTC_TAMPER_1)
  {
    ERTC->tamp_bit.tp1edg = trigger;
  }
  else
  {
    ERTC->tamp_bit.tp2edg = trigger;
  }

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  enable or disable trigger timestamp when tamper event occurs.
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void ertc_tamper_timestamp_enable(confirm_state new_state)
{
  /* disable write protection */
  ertc_write_protect_disable();

  ERTC->tamp_bit.tptsen = new_state;

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  enable or disable tamper.
  * @param  tamper_x: select the tamper.
  *         this parameter can be one of the following values:
  *         - ERTC_TAMPER_1: tamper 1.
  *         - ERTC_TAMPER_2: tamper 2.
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void ertc_tamper_enable(ertc_tamper_select_type tamper_x, confirm_state new_state)
{
  /* disable write protection */
  ertc_write_protect_disable();

  if(tamper_x == ERTC_TAMPER_1)
  {
    ERTC->tamp_bit.tp1en = new_state;
  }
  else
  {
    ERTC->tamp_bit.tp2en = new_state;
  }

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  enable or disable interrupt.
  * @param  source: interrupts sources
  *         this parameter can be any combination of the following values:
  *         - ERTC_TP_INT: tamper interrupt.
  *         - ERTC_ALA_INT: alarm a interrupt.
  *         - ERTC_ALB_INT: alarm b interrupt.
  *         - ERTC_WAT_INT: wakeup timer interrupt.
  *         - ERTC_TS_INT: timestamp interrupt.
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void ertc_interrupt_enable(uint32_t source, confirm_state new_state)
{
  /* disable write protection */
  ertc_write_protect_disable();

  if(source & ERTC_TP_INT)
  {
    if(new_state != FALSE)
    {
      ERTC->tamp |= ERTC_TP_INT;
    }
    else
    {
      ERTC->tamp &= ~ERTC_TP_INT;
    }

    source &= ~ERTC_TP_INT;
  }

  if(new_state != FALSE)
  {
    ERTC->ctrl |= source;
  }
  else
  {
    ERTC->ctrl &= ~source;
  }

  /* enable write protection */
  ertc_write_protect_enable();
}

/**
  * @brief  get interrupt status
  * @param  source
  *         this parameter can be one of the following values:
  *         - ERTC_TP_INT: tamper interrupt.
  *         - ERTC_ALA_INT: alarm a interrupt.
  *         - ERTC_ALB_INT: alarm b interrupt.
  *         - ERTC_WAT_INT: wakeup timer interrupt.
  *         - ERTC_TS_INT: timestamp interrupt.
  * @retval flag_status (SET or RESET)
  */
flag_status ertc_interrupt_get(uint32_t source)
{
  if(source & ERTC_TP_INT)
  {
    if((ERTC->tamp & ERTC_TP_INT) != RESET)
    {
      return SET;
    }
    else
    {
      return RESET;
    }
  }

  if((ERTC->ctrl & source) != RESET)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  get flag status.
  * @param  flag: specifies the flag to check.
  *         this parameter can be one of the following values:
  *         - ERTC_ALAWF_FLAG: alarm a register allows write flag.
  *         - ERTC_ALBWF_FLAG: alarm b register allows write flag.
  *         - ERTC_WATWF_FLAG: wakeup timer register allows write flag.
  *         - ERTC_TADJF_FLAG: time adjustment flag.
  *         - ERTC_INITF_FLAG: calendar initialization flag.
  *         - ERTC_UPDF_FLAG: calendar update flag.
  *         - ERTC_IMF_FLAG: enter initialization mode flag.
  *         - ERTC_ALAF_FLAG: alarm clock a flag.
  *         - ERTC_ALBF_FLAG: alarm clock b flag.
  *         - ERTC_WATF_FLAG: wakeup timer flag.
  *         - ERTC_TSF_FLAG: timestamp flag.
  *         - ERTC_TSOF_FLAG: timestamp overflow flag.
  *         - ERTC_TP1F_FLAG: tamper detection 1 flag.
  *         - ERTC_TP2F_FLAG: tamper detection 2 flag.
  *         - ERTC_CALUPDF_FLAG: calibration value update completed flag.
  * @retval the new state of flag (SET or RESET).
  */
flag_status ertc_flag_get(uint32_t flag)
{
  if((ERTC->sts & flag) != (uint32_t)RESET)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  get interrupt flag status.
  * @param  flag: specifies the flag to check.
  *         this parameter can be one of the following values:
  *         - ERTC_ALAF_FLAG: alarm clock a flag.
  *         - ERTC_ALBF_FLAG: alarm clock b flag.
  *         - ERTC_WATF_FLAG: wakeup timer flag.
  *         - ERTC_TSF_FLAG: timestamp flag.
  *         - ERTC_TP1F_FLAG: tamper detection 1 flag.
  *         - ERTC_TP2F_FLAG: tamper detection 2 flag.
  * @retval the new state of flag (SET or RESET).
  */
flag_status ertc_interrupt_flag_get(uint32_t flag)
{
  __IO uint32_t iten = 0;

  switch(flag)
  {
    case ERTC_ALAF_FLAG:
      iten = ERTC->ctrl_bit.alaien;
      break;
    case ERTC_ALBF_FLAG:
      iten = ERTC->ctrl_bit.albien;
      break;
    case ERTC_WATF_FLAG:
      iten = ERTC->ctrl_bit.watien;
      break;
    case ERTC_TSF_FLAG:
      iten = ERTC->ctrl_bit.tsien;
      break;
    case ERTC_TP1F_FLAG:
    case ERTC_TP2F_FLAG:
      iten = ERTC->tamp_bit.tpien;
      break;

    default:
      break;
  }

  if(((ERTC->sts & flag) != (uint32_t)RESET) && (iten))
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  clear flag status
  * @param  flag: specifies the flag to clear.
  *         this parameter can be any combination of the following values:
  *         - ERTC_ALAWF_FLAG: alarm a register allows write flag.
  *         - ERTC_ALBWF_FLAG: alarm b register allows write flag.
  *         - ERTC_WATWF_FLAG: wakeup timer register allows write flag.
  *         - ERTC_TADJF_FLAG: time adjustment flag.
  *         - ERTC_INITF_FLAG: calendar initialization flag.
  *         - ERTC_UPDF_FLAG: calendar update flag.
  *         - ERTC_IMF_FLAG: enter initialization mode flag.
  *         - ERTC_ALAF_FLAG: alarm clock a flag.
  *         - ERTC_ALBF_FLAG: alarm clock b flag.
  *         - ERTC_WATF_FLAG: wakeup timer flag.
  *         - ERTC_TSF_FLAG: timestamp flag.
  *         - ERTC_TSOF_FLAG: timestamp overflow flag.
  *         - ERTC_TP1F_FLAG: tamper detection 1 flag.
  *         - ERTC_TP2F_FLAG: tamper detection 2 flag.
  *         - ERTC_CALUPDF_FLAG: calibration value update completed flag.
  * @retval none
  */
void ertc_flag_clear(uint32_t flag)
{
  ERTC->sts = ~(flag | 0x00000080) | (ERTC->sts_bit.imen << 7);
}

/**
  * @brief  write data to the bpr register.
  * @param  dt: data register
  *         this parameter can be one of the following values:
  *         - ERTC_DT1
  *         - ERTC_DT2
  *         - ...
  *         - ERTC_DT19
  *         - ERTC_DT20
  * @param  data: data to be write.
  * @retval none.
  */
void ertc_bpr_data_write(ertc_dt_type dt, uint32_t data)
{
  __IO uint32_t reg = 0;

  reg = ERTC_BASE + 0x50 + (dt * 4);

  *(__IO uint32_t *)reg = data;
}

/**
  * @brief  read data from bpr register.
  * @param  dt: data register
  *         this parameter can be one of the following values:
  *         - ERTC_DT1
  *         - ERTC_DT2
  *         - ...
  *         - ERTC_DT19
  *         - ERTC_DT20
  * @retval data value.
  */
uint32_t ertc_bpr_data_read(ertc_dt_type dt)
{
  __IO uint32_t reg = 0;

  reg = ERTC_BASE + 0x50 + (dt * 4);

  return (*(__IO uint32_t *)reg);
}

/**
  * @}
  */

#endif

/**
  * @}
  */

/**
  * @}
  */
