/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef OCC_CURVE_P256_H
#define OCC_CURVE_P256_H

#include "occ_sc_p256.h"


// (x,y) only jacobian coordinates
typedef struct {
    occ_mod_p256 x;
    occ_mod_p256 y;
} occ_cp_p256;


// load r.x from bytes, recover r.y
// returns 0 if r is a legal curve point, -1 otherwise
int occ_curve_p256_from32bytes(occ_cp_p256 *r, const uint8_t p[32]);

// load point from bytes
// returns 0 if r is a legal curve point, -1 otherwise
int occ_curve_p256_from64bytes(occ_cp_p256 *r, const uint8_t p[64]);

// store p.x to bytes
void occ_curve_p256_to32bytes(uint8_t r[32], occ_cp_p256 *p);

// store point to bytes
void occ_curve_p256_to64bytes(uint8_t r[64], occ_cp_p256 *p);

// r = p * s
// r = [0,0] if p = [0,0] or s mod q = 0
// returns -1 if r = [0,0], 0 if 0 < s < q, 1 if s > q
int occ_curve_p256_scalarmult(occ_cp_p256 *r, const occ_cp_p256 *p, const occ_sc_p256 *s);

// r = basePoint * s
// r = [0,0] if s mod q = 0
// returns -1 if r = [0,0], 0 if 0 < s < q, 1 if s > q
int occ_curve_p256_scalarmult_base(occ_cp_p256 *r, const occ_sc_p256 *s);

#endif
