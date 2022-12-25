/**
 * @file hal_sec_hash.h
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
#ifndef __HAL_SEC_HASH__H__
#define __HAL_SEC_HASH__H__

#include "drv_device.h"
#include "hal_common.h"

enum sec_hash_index_type {
    SEC_HASH0_INDEX,
    SEC_HASH_MAX_INDEX
};

enum sec_hash_type {
    SEC_HASH_SHA1,
    SEC_HASH_SHA224,
    SEC_HASH_SHA256,
    SEC_HASH_SHA384,
    SEC_HASH_SHA512,
    SEC_HASH_UNKNOWN
};

typedef struct sec_hash_device {
    struct device parent;
    uint32_t shaBuf[64 / 4];     /*!< Data not processed but in this temp buffer */
    uint32_t shaPadding[64 / 4]; /*!< Padding data */
    uint8_t type;                /*!< Sha has feed data */
} sec_hash_device_t;

typedef struct
{
    uint32_t shaBuf[64 / 4];     /*!< Data not processed but in this temp buffer */
    uint32_t shaPadding[64 / 4]; /*!< Padding data */
    uint8_t type;                /*!< Sha has feed data */
} sec_hash_handle_t;

int sec_hash_init(sec_hash_handle_t *handle, uint8_t type);
int sec_hash_deinit(sec_hash_handle_t *handle);
int sec_hash_update(sec_hash_handle_t *handle, const void *buffer, uint32_t size);
int sec_hash_finish(sec_hash_handle_t *handle, void *buffer);
int sec_hash_sha256_register(enum sec_hash_index_type index, const char *name);
int sec_hash_sha224_register(enum sec_hash_index_type index, const char *name);

#endif