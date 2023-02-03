/**
 * @file hal_flash.h
 * @brief
 *
 * Copyright 2019-2030 Bouffalolab team
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
#ifndef __HAL_FLASH__H__
#define __HAL_FLASH__H__

#include "hal_common.h"
#include "bl808_sflash.h"

#define FLASH_NOT_DETECT  0x10
#define BL_FLASH_XIP_BASE 0//BL808_FLASH_XIP_BASE

uint32_t flash_get_jedecid(void);
BL_Err_Type flash_init(void);
BL_Err_Type flash_read_jedec_id(uint8_t *data);
BL_Err_Type flash_read_via_xip(uint32_t addr, uint8_t *data, uint32_t len);
BL_Err_Type flash_read(uint32_t addr, uint8_t *data, uint32_t len);
BL_Err_Type flash_write(uint32_t addr, uint8_t *data, uint32_t len);
BL_Err_Type flash_erase(uint32_t startaddr, uint32_t len);
BL_Err_Type flash_set_cache(uint8_t cont_read, uint8_t cache_enable, uint8_t cache_way_disable, uint32_t flash_offset);
BL_Err_Type flash_get_cfg(uint8_t **cfg_addr, uint32_t *len);

#endif
