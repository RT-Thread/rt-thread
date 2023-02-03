/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __UTILS_TLV_BL_H__
#define __UTILS_TLV_BL_H__
#include <stdint.h>
#include <stdbool.h>

#define CFG_ELEMENT_TYPE_SIZE_BOOLEAN                 (4)
#define CFG_ELEMENT_TYPE_SIZE_UINT32                  (4)
#define UTILS_TLV_BL_ERROR_CODE_BUF_TOO_SMALL         (-1)
#define UTILS_TLV_BL_ERROR_CODE_UNKOWN                (-2)
// Wi-Fi CFG API
enum CFG_ELEMENT_TYPE {
    CFG_ELEMENT_TYPE_UNKNOWN,
    CFG_ELEMENT_TYPE_BOOLEAN,
    CFG_ELEMENT_TYPE_SINT8,
    CFG_ELEMENT_TYPE_UINT8,
    CFG_ELEMENT_TYPE_SINT16,
    CFG_ELEMENT_TYPE_UINT16,
    CFG_ELEMENT_TYPE_SINT32,
    CFG_ELEMENT_TYPE_UINT32,
    CFG_ELEMENT_TYPE_STRING,
};

enum CFG_ELEMENT_TYPE_OPS
{
    CFG_ELEMENT_TYPE_OPS_SET,
    CFG_ELEMENT_TYPE_OPS_GET,
    CFG_ELEMENT_TYPE_OPS_RESET,
    CFG_ELEMENT_TYPE_OPS_DUMP_DEBUG,
    CFG_ELEMENT_TYPE_OPS_UNKNOWN,
};

int utils_tlv_bl_pack_bool(uint32_t *buf, int buf_sz, bool val);
int utils_tlv_bl_pack_uint8(uint32_t *buf, int buf_sz, uint8_t val);
int utils_tlv_bl_pack_int8(uint32_t *buf, int buf_sz, int8_t val);
int utils_tlv_bl_pack_uint16(uint32_t *buf, int buf_sz, uint16_t val);
int utils_tlv_bl_pack_int16(uint32_t *buf, int buf_sz, int16_t val);
int utils_tlv_bl_pack_uint32(uint32_t *buf, int buf_sz, uint32_t val);
int utils_tlv_bl_pack_int32(uint32_t *buf, int buf_sz, int32_t val);
int utils_tlv_bl_pack_string(uint32_t *buf, int buf_sz, const char *str);
int utils_tlv_bl_pack_auto(uint32_t *buf, int buf_sz, uint16_t type, void *arg1);

int utils_tlv_bl_unpack_bool(uint32_t *buf, int buf_sz, bool *val);
int utils_tlv_bl_unpack_uint8(uint32_t *buf, int buf_sz, uint8_t *val);
int utils_tlv_bl_unpack_int8(uint32_t *buf, int buf_sz, int8_t *val);
int utils_tlv_bl_unpack_uint16(uint32_t *buf, int buf_sz, uint16_t *val);
int utils_tlv_bl_unpack_int16(uint32_t *buf, int buf_sz, int16_t *val);
int utils_tlv_bl_unpack_uint32(uint32_t *buf, int buf_sz, uint32_t *val);
int utils_tlv_bl_unpack_int32(uint32_t *buf, int buf_sz, int32_t *val);
int utils_tlv_bl_unpack_string(uint32_t *buf, int buf_sz, char *str, int size);
int utils_tlv_bl_unpack_auto(uint32_t *buf, int buf_sz, uint16_t type, void *arg1);
#endif
