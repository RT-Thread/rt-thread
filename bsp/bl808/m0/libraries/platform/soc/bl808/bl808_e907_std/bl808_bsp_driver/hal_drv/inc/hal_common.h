/**
 * @file hal_common.h
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
#ifndef __HAL_COMMON__H__
#define __HAL_COMMON__H__

#include "bl808_common.h"

typedef enum {
    HAL_REBOOT_AS_BOOTPIN,           /*!< reboot as bootpin level */
    HAL_REBOOT_FROM_INTERFACE,       /*!< reboot from interface, download mode */
    HAL_REBOOT_FROM_MEDIA,           /*!< reboot from media, running mode */
    HAL_REBOOT_MAX                   /*!< reboot max value */
} hal_reboot_cfg_t;

void cpu_global_irq_enable(void);
void cpu_global_irq_disable(void);
void hal_por_reset(void);
void hal_system_reset(void);
void hal_cpu_reset(void);
void hal_reboot_config(hal_reboot_cfg_t rbot);
void hal_get_chip_id(uint8_t chip_id[8]);
void hal_dcache_clean_all(void);
void hal_dcache_invalid_all(void);
void hal_dcache_clean_invalid_all(void);
void hal_dcache_clean_byaddr(uintptr_t addr, uint32_t len);
void hal_dcache_invalidate_byaddr(uintptr_t addr, uint32_t len);
void hal_dcache_clean_invalidate_byaddr(uintptr_t addr, uint32_t len);

#endif
