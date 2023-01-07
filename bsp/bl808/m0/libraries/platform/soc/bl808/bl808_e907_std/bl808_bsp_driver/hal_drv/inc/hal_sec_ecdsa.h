/**
 * @file hal_sec_ecdsa.h
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
#ifndef __HAL_SEC_ECDSA__H__
#define __HAL_SEC_ECDSA__H__

#include "hal_common.h"

typedef enum {
    ECP_SECP256R1 = 0,
    ECP_SECP256K1 = 1,
    ECP_TYPE_MAX = 2,
} sec_ecp_type;

typedef struct
{
    sec_ecp_type ecpId;
    uint32_t *privateKey;
    uint32_t *publicKeyx;
    uint32_t *publicKeyy;
} sec_ecdsa_handle_t;

typedef struct
{
    sec_ecp_type ecpId;
} sec_ecdh_handle_t;

int sec_ecdsa_init(sec_ecdsa_handle_t *handle, sec_ecp_type id);
int sec_ecdsa_deinit(sec_ecdsa_handle_t *handle);
int sec_ecdsa_sign(sec_ecdsa_handle_t *handle, const uint32_t *random_k, const uint32_t *hash, uint32_t hashLenInWord, uint32_t *r, uint32_t *s);
int sec_ecdsa_verify(sec_ecdsa_handle_t *handle, const uint32_t *hash, uint32_t hashLen, const uint32_t *r, const uint32_t *s);
int sec_ecdsa_get_private_key(sec_ecdsa_handle_t *handle, uint32_t *private_key);
int sec_ecdsa_get_public_key(sec_ecdsa_handle_t *handle, const uint32_t *private_key, const uint32_t *pRx, const uint32_t *pRy);

int sec_ecdh_init(sec_ecdh_handle_t *handle, sec_ecp_type id);
int sec_ecdh_deinit(sec_ecdh_handle_t *handle);
int sec_ecdh_get_encrypt_key(sec_ecdh_handle_t *handle, const uint32_t *pkX, const uint32_t *pkY, const uint32_t *private_key, const uint32_t *pRx, const uint32_t *pRy);
int sec_ecdh_get_public_key(sec_ecdh_handle_t *handle, const uint32_t *private_key, const uint32_t *pRx, const uint32_t *pRy);
int sec_ecc_get_random_value(uint32_t *randomData, uint32_t *maxRef, uint32_t size);

#define SEC_CODEPATH_STATE_SIGN             0x48672386

#endif