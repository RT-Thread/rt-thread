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
#include "utils_tlv_bl.h"

int utils_tlv_bl_pack_bool(uint32_t *buf, int buf_sz, bool val)
{
    if (buf_sz < CFG_ELEMENT_TYPE_SIZE_BOOLEAN) {
        return UTILS_TLV_BL_ERROR_CODE_BUF_TOO_SMALL;
    }
    *buf = val;//XXX caution for unaligned access

    return CFG_ELEMENT_TYPE_SIZE_BOOLEAN;
}

int utils_tlv_bl_pack_uint32(uint32_t *buf, int buf_sz, uint32_t val)
{
    if (buf_sz < CFG_ELEMENT_TYPE_SIZE_UINT32) {
        return UTILS_TLV_BL_ERROR_CODE_BUF_TOO_SMALL;
    }
    *buf = val;//XXX caution for unaligned access

    return CFG_ELEMENT_TYPE_SIZE_UINT32;
}

int utils_tlv_bl_unpack_bool(uint32_t *buf, int buf_sz, bool *val)
{
    if (buf_sz < CFG_ELEMENT_TYPE_SIZE_BOOLEAN) {
        return UTILS_TLV_BL_ERROR_CODE_BUF_TOO_SMALL;
    }
    *val = (*buf) ? true : false;// XXX caution for unaligned access

    return CFG_ELEMENT_TYPE_SIZE_BOOLEAN;
}

int utils_tlv_bl_unpack_uint32(uint32_t *buf, int buf_sz, uint32_t *val)
{
    if (buf_sz < CFG_ELEMENT_TYPE_SIZE_UINT32) {
        return UTILS_TLV_BL_ERROR_CODE_BUF_TOO_SMALL;
    }
    *val = (*buf);//XXX caution for unaligned access

    return CFG_ELEMENT_TYPE_SIZE_BOOLEAN;
}

int utils_tlv_bl_pack_auto(uint32_t *buf, int buf_sz, uint16_t type, void *arg1)
{
    int ret = UTILS_TLV_BL_ERROR_CODE_UNKOWN;

    switch (type) {
        case CFG_ELEMENT_TYPE_BOOLEAN:
        {
            ret = utils_tlv_bl_pack_bool(buf, buf_sz, *(bool*)arg1 ? true : false);
        }
        break;
        case CFG_ELEMENT_TYPE_SINT8:
        {
            //TODO
        }
        break;
        case CFG_ELEMENT_TYPE_UINT8:
        {
            //TODO
        }
        break;
        case CFG_ELEMENT_TYPE_SINT16:
        {
            //TODO
        }
        break;
        case CFG_ELEMENT_TYPE_UINT16:
        {
            //TODO
        }
        break;
        case CFG_ELEMENT_TYPE_SINT32:
        {
            //TODO
        }
        break;
        case CFG_ELEMENT_TYPE_UINT32:
        {
            ret = utils_tlv_bl_pack_uint32(buf, buf_sz, *(uint32_t*)arg1);
        }
        break;
        case CFG_ELEMENT_TYPE_STRING:
        {
            //TODO
        }
        break;
        default:
        {
            /*empty*/
        }
    }

    return ret;
}

int utils_tlv_bl_unpack_auto(uint32_t *buf, int buf_sz, uint16_t type, void *arg1)
{
    int ret = UTILS_TLV_BL_ERROR_CODE_UNKOWN;

    switch (type) {
        case CFG_ELEMENT_TYPE_BOOLEAN:
        {
            bool val = true;

            ret = utils_tlv_bl_unpack_bool(buf, buf_sz, &val);
            *(bool*)arg1 = val;
        }
        break;
        case CFG_ELEMENT_TYPE_SINT8:
        {
            //TODO
        }
        break;
        case CFG_ELEMENT_TYPE_UINT8:
        {
            //TODO
        }
        break;
        case CFG_ELEMENT_TYPE_SINT16:
        {
            //TODO
        }
        break;
        case CFG_ELEMENT_TYPE_UINT16:
        {
            //TODO
        }
        break;
        case CFG_ELEMENT_TYPE_SINT32:
        {
            //TODO
        }
        break;
        case CFG_ELEMENT_TYPE_UINT32:
        {
            uint32_t val = 0;

            ret = utils_tlv_bl_unpack_uint32(buf, buf_sz, &val);
            *(uint32_t*)arg1 = val;
        }
        break;
        case CFG_ELEMENT_TYPE_STRING:
        {
            //TODO
        }
        break;
        default:
        {
            /*empty*/
        }
    }

    return ret;
}
