/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024/03/04     ShichengChu    first version
 */

#ifndef __DRV_RTC_H__
#define __DRV_RTC_H__

#include "pinctrl.h"
#include "mmio.h"

#define CVI_RTC_BASE 0x05026000U
#define RTC_ALARM_O  17
#define CVI_RTC_CTRL_BASE 0x05025000U
#define CLK_EN_0 0x03002000U
#define CLK_RTC_25M_BIT (1 << 8)

/* CVITEK RTC registers */
#define CVI_RTC_ANA_CALIB               0x0
#define CVI_RTC_SEC_PULSE_GEN           0x4
#define CVI_RTC_ALARM_TIME              0x8
#define CVI_RTC_ALARM_ENABLE            0xC
#define CVI_RTC_SET_SEC_CNTR_VALUE      0x10
#define CVI_RTC_SET_SEC_CNTR_TRIG       0x14
#define CVI_RTC_SEC_CNTR_VALUE          0x18
#define CVI_RTC_APB_RDATA_SEL           0x3C
#define CVI_RTC_POR_DB_MAGIC_KEY        0x68
#define CVI_RTC_EN_PWR_WAKEUP           0xBC
#define CVI_RTC_PWR_DET_SEL             0x140

/* CVITEK RTC MACRO registers */
#define RTC_MACRO_DA_CLEAR_ALL          0x480
#define RTC_MACRO_DA_SOC_READY          0x48C
#define RTC_MACRO_RO_T                  0x4A8
#define RTC_MACRO_RG_SET_T              0x498

/* CVITEK RTC CTRL registers */
#define CVI_RTC_FC_COARSE_EN            0x40
#define CVI_RTC_FC_COARSE_CAL           0x44
#define CVI_RTC_FC_FINE_EN              0x48
#define CVI_RTC_FC_FINE_CAL             0x50

#define RTC_SEC_MAX_VAL     0xFFFFFFFF

#define RTC_OFFSET_SN 0x5201800

#endif /* __DRV_RTC_H__ */
