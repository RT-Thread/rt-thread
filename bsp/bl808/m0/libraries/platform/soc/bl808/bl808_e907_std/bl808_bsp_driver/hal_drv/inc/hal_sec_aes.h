/**
 * @file hal_sec_aes.h
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
#ifndef __HAL_SEC_AES__H__
#define __HAL_SEC_AES__H__

#include "hal_common.h"

typedef enum {
    SEC_AES_CBC,
    SEC_AES_CTR,
    SEC_AES_XTS,
    SEC_AES_ECB
} sec_aes_type;

typedef enum {
    SEC_AES_KEY_128,
    SEC_AES_KEY_256,
    SEC_AES_KEY_192
} sec_aes_key_type;

typedef struct sec_aes_handle_t {
    sec_aes_type aes_type;
    sec_aes_key_type key_type;
} sec_aes_handle_t;

typedef enum {
    SEC_AES_DIR_ENCRYPT,
    SEC_AES_DIR_DECRYPT
} sec_aes_dir_type;

int sec_aes_init(sec_aes_handle_t *handle, sec_aes_type aes_tye, sec_aes_key_type key_type);
int sec_aes_setkey(sec_aes_handle_t *handle, const uint8_t *key, uint8_t key_len, const uint8_t *nonce, uint8_t dir);
int sec_aes_encrypt(sec_aes_handle_t *handle, const uint8_t *in, uint32_t len, size_t offset, uint8_t *out);
int sec_aes_decrypt(sec_aes_handle_t *handle, const uint8_t *in, uint32_t len, size_t offset, uint8_t *out);
int sec_aes_deinit(sec_aes_handle_t *handle);

#endif