/**
 * @file hal_rtc.c
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#include "hal_rtc.h"
#include "bl808_hbn.h"
static uint64_t current_timestamp = 0;

/**
 * @brief rtc init withc sleep time
 *
 * @param sleep_time
 */
void rtc_init(uint64_t sleep_time)
{
    uint32_t tmpVal;
    uint32_t comp_l, comp_h;

    /* Clear & Disable RTC counter */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);
    /* Clear RTC control bit0 */
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal & 0xfffffff0);

    /* Get current RTC timer */
    /* Tigger RTC val read */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_RTC_TIME_H);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_RTC_TIME_LATCH);
    BL_WR_REG(HBN_BASE, HBN_RTC_TIME_H, tmpVal);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_RTC_TIME_LATCH);
    BL_WR_REG(HBN_BASE, HBN_RTC_TIME_H, tmpVal);

    /* Read RTC val */
    comp_l = BL_RD_REG(HBN_BASE, HBN_RTC_TIME_L);
    comp_h = (BL_RD_REG(HBN_BASE, HBN_RTC_TIME_H) & 0xff);

    /* calculate RTC Comp time */
    comp_l += (uint32_t)((sleep_time * 32768) & 0xFFFFFFFF);
    comp_h += (uint32_t)(((sleep_time * 32768) >> 32) & 0xFFFFFFFF);

    /* Set RTC Comp time  */
    BL_WR_REG(HBN_BASE, HBN_TIME_L, comp_l);
    BL_WR_REG(HBN_BASE, HBN_TIME_H, comp_h & 0xff);

    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);
    /* Set interrupt delay option */
    tmpVal =
        BL_SET_REG_BITS_VAL(tmpVal, HBN_RTC_DLY_OPTION, HBN_RTC_INT_DELAY_0T);
    /* Set RTC compare mode */
    tmpVal |= (HBN_RTC_COMP_BIT0_39 << 1);
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal);

    /* Enable RTC Counter */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_CTL);
    /* Set RTC control bit0 */
    BL_WR_REG(HBN_BASE, HBN_CTL, tmpVal | 0x01);
}

void rtc_set_timestamp(uint64_t time_stamp)
{
    current_timestamp = time_stamp;
}
/**
 * @bref Get rtc value
 *
 */
uint64_t rtc_get_timestamp(void)
{
    uint32_t tmpVal;
    uint64_t time_l;
    uint64_t time_h;

    /* Tigger RTC val read */
    tmpVal = BL_RD_REG(HBN_BASE, HBN_RTC_TIME_H);
    tmpVal = BL_SET_REG_BIT(tmpVal, HBN_RTC_TIME_LATCH);
    BL_WR_REG(HBN_BASE, HBN_RTC_TIME_H, tmpVal);
    tmpVal = BL_CLR_REG_BIT(tmpVal, HBN_RTC_TIME_LATCH);
    BL_WR_REG(HBN_BASE, HBN_RTC_TIME_H, tmpVal);

    /* Read RTC val */
    time_l = BL_RD_REG(HBN_BASE, HBN_RTC_TIME_L);
    time_h = (BL_RD_REG(HBN_BASE, HBN_RTC_TIME_H) & 0xff);

    return (((time_h << 32 | time_l) >> 15) + current_timestamp);
}
