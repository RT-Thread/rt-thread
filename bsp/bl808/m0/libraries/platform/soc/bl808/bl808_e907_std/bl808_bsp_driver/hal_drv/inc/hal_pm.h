/**
 * @file hal_pm.h
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
#ifndef __HAL_PM__H__
#define __HAL_PM__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_common.h"
enum pm_pds_sleep_level {
    PM_PDS_LEVEL_1 = 1,
    PM_PDS_LEVEL_2 = 2,
    PM_PDS_LEVEL_3 = 3,
    PM_PDS_LEVEL_7 = 7,
};

enum pm_hbn_sleep_level {
    PM_HBN_LEVEL_0,
    PM_HBN_LEVEL_1,
    PM_HBN_LEVEL_2,
};

/**
 *  @brief HBN BOR threshold type definition
 */
typedef enum {
    HBN_BOR_THRES_2P05V = 0, /*!< BOR threshold 2.05V */
    HBN_BOR_THRES_2P10V,     /*!< BOR threshold 2.10V */
    HBN_BOR_THRES_2P15V,     /*!< BOR threshold 2.15V */
    HBN_BOR_THRES_2P20V,     /*!< BOR threshold 2.20V */
    HBN_BOR_THRES_2P25V,     /*!< BOR threshold 2.25V */
    HBN_BOR_THRES_2P30V,     /*!< BOR threshold 2.30V */
    HBN_BOR_THRES_2P35V,     /*!< BOR threshold 2.35V */
    HBN_BOR_THRES_2P40V,     /*!< BOR threshold 2.40V */
} HBN_BOR_THRES_Type;

/**
 *  @brief HBN BOR mode type definition
 */
typedef enum {
    HBN_BOR_MODE_POR_INDEPENDENT, /*!< POR is independent of BOR */
    HBN_BOR_MODE_POR_RELEVANT,    /*!< POR is relevant to BOR */
} HBN_BOR_MODE_Type;

enum pm_event_type {
    PM_HBN_WAKEUP_EVENT_NONE,
    PM_HBN_GPIO9_WAKEUP_EVENT,
    PM_HBN_GPIO10_WAKEUP_EVENT,
    PM_HBN_GPIO11_WAKEUP_EVENT,
    PM_HBN_GPIO12_WAKEUP_EVENT,
    PM_HBN_GPIO13_WAKEUP_EVENT,
    PM_HBN_GPIO14_WAKEUP_EVENT,
    PM_HBN_GPIO15_WAKEUP_EVENT,
    PM_HBN_GPIO40_WAKEUP_EVENT,
    PM_HBN_GPIO41_WAKEUP_EVENT,
    PM_HBN_RTC_WAKEUP_EVENT,
    PM_HBN_BOD_WAKEUP_EVENT,
    PM_HBN_ACOMP0_WAKEUP_EVENT,
    PM_HBN_ACOMP1_WAKEUP_EVENT,
};

void pm_pds_mask_all_wakeup_src(void);
void pm_pds_mode_enter(enum pm_pds_sleep_level pds_level, uint32_t sleep_time);
void pm_hbn_out0_irq_register(void);
void pm_hbn_out1_irq_register(void);
void HBN_OUT0_IRQ(void);
void HBN_OUT1_IRQ(void);
void pm_irq_callback(enum pm_event_type event);
void pm_pds_irq_register(void);
void PDS_WAKEUP_IRQ(void);
#endif
