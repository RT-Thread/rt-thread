/**
 * @file hal_sec_dsa.h
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
#ifndef __HAL_SEC_DSA__H__
#define __HAL_SEC_DSA__H__

#include "hal_common.h"

typedef struct sec_dsa_crt_cfg_tag {
    uint32_t *dP;
    uint32_t *dQ;
    uint32_t *qInv;
    uint32_t *p;
    uint32_t *invR_p;
    uint32_t *primeN_p;
    uint32_t *q;
    uint32_t *invR_q;
    uint32_t *primeN_q;
} sec_dsa_crt_cfg_t;

typedef struct
{
    uint32_t size;
    uint32_t crtSize;
    uint32_t *n;
    uint32_t *e;
    uint32_t *d;
    sec_dsa_crt_cfg_t crtCfg;
} sec_dsa_handle_t;

int sec_dsa_init(sec_dsa_handle_t *handle, uint32_t size);
int sec_dsa_mexp_binary(uint32_t size, const uint32_t *a, const uint32_t *b, const uint32_t *c, uint32_t *r);
int sec_dsa_mexp_mont(uint32_t size, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *invR_c, uint32_t *primeN_c, uint32_t *r);
int sec_dsa_decrypt_crt(uint32_t size, uint32_t *c, sec_dsa_crt_cfg_t *crtCfg, uint32_t *d, uint32_t *r);
int sec_dsa_sign(sec_dsa_handle_t *handle, const uint32_t *hash, uint32_t hashLenInWord, uint32_t *s);
int sec_dsa_verify(sec_dsa_handle_t *handle, const uint32_t *hash, uint32_t hashLenInWord, const uint32_t *s);

#endif