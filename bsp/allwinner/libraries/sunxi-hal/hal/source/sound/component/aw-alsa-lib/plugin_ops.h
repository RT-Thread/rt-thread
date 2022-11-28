/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the people's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef SX_INLINES
#define SX_INLINES
static inline u_int32_t sx24(u_int32_t x)
{
    if(x&0x00800000)
        return x|0xFF000000;
    return x&0x00FFFFFF;
}
static inline u_int32_t sx24s(u_int32_t x)
{
    if(x&0x00008000)
        return x|0x000000FF;
    return x&0xFFFFFF00;
}
#endif

#define as_u8(ptr) (*(u_int8_t*)(ptr))
#define as_u16(ptr) (*(u_int16_t*)(ptr))
#define as_u32(ptr) (*(u_int32_t*)(ptr))
#define as_u64(ptr) (*(u_int64_t*)(ptr))
#define as_s8(ptr) (*(int8_t*)(ptr))
#define as_s16(ptr) (*(int16_t*)(ptr))
#define as_s32(ptr) (*(int32_t*)(ptr))
#define as_s64(ptr) (*(int64_t*)(ptr))
#define as_float(ptr) (*(float_t*)(ptr))
#define as_double(ptr) (*(double_t*)(ptr))

#define as_u8c(ptr) (*(const u_int8_t*)(ptr))
#define as_u16c(ptr) (*(const u_int16_t*)(ptr))
#define as_u32c(ptr) (*(const u_int32_t*)(ptr))
#define as_u64c(ptr) (*(const u_int64_t*)(ptr))
#define as_s8c(ptr) (*(const int8_t*)(ptr))
#define as_s16c(ptr) (*(const int16_t*)(ptr))
#define as_s32c(ptr) (*(const int32_t*)(ptr))
#define as_s64c(ptr) (*(const int64_t*)(ptr))
#define as_floatc(ptr) (*(const float_t*)(ptr))
#define as_doublec(ptr) (*(const double_t*)(ptr))

#define _get_triple_le(ptr) (*(u_int8_t*)(ptr) | (u_int32_t)*((u_int8_t*)(ptr) + 1) << 8 | (u_int32_t)*((u_int8_t*)(ptr) + 2) << 16)
#define _get_triple_be(ptr) ((u_int32_t)*(u_int8_t*)(ptr) << 16 | (u_int32_t)*((u_int8_t*)(ptr) + 1) << 8 | *((u_int8_t*)(ptr) + 2))
#define _put_triple_le(ptr,val) do { \
    u_int8_t *_tmp = (u_int8_t *)(ptr); \
    u_int32_t _val = (val); \
    _tmp[0] = _val; \
    _tmp[1] = _val >> 8; \
    _tmp[2] = _val >> 16; \
} while(0)
#define _put_triple_be(ptr,val) do { \
    u_int8_t *_tmp = (u_int8_t *)(ptr); \
    u_int32_t _val = (val); \
    _tmp[0] = _val >> 16; \
    _tmp[1] = _val >> 8; \
    _tmp[2] = _val; \
} while(0)

#ifdef SNDRV_LITTLE_ENDIAN
#define _get_triple(ptr) _get_triple_le(ptr)
#define _get_triple_s(ptr) _get_triple_be(ptr)
#define _put_triple(ptr,val) _put_triple_le(ptr,val)
#define _put_triple_s(ptr,val) _put_triple_be(ptr,val)
#else
#define _get_triple(ptr) _get_triple_be(ptr)
#define _get_triple_s(ptr) _get_triple_le(ptr)
#define _put_triple(ptr,val) _put_triple_be(ptr,val)
#define _put_triple_s(ptr,val) _put_triple_le(ptr,val)
#endif

#ifdef COPY_LABELS
static void *copy_labels[5] = {
    &&copy_8,
    &&copy_16,
    &&copy_24
    &&copy_32,
    &&copy_64
};
#endif

#ifdef COPY_END
while(0) {
copy_8: as_s8(dst) = as_s8c(src); goto COPY_END;
copy_16: as_s16(dst) = as_s16c(src); goto COPY_END;
copy_24: memcpy(dst,src,3); goto COPY_END;
copy_32: as_s32(dst) = as_s32c(src); goto COPY_END;
copy_64: as_s64(dst) = as_s64c(src); goto COPY_END;
}
#endif

#ifdef CONV_LABELS
/* src_wid src_endswap sign_toggle dst_wid dst_endswap */
static void *const conv_labels[4 * 2 * 2 * 4 * 2] = {
    &&conv_xxx1_xxx1,    /*  8h ->  8h */
    &&conv_xxx1_xxx1,    /*  8h ->  8s */
    &&conv_xxx1_xx10,    /*  8h -> 16h */
    &&conv_xxx1_xx01,    /*  8h -> 16s */
    &&conv_xxx1_x100,    /*  8h -> 24h */
    &&conv_xxx1_001x,    /*  8h -> 24s */
    &&conv_xxx1_1000,    /*  8h -> 32h */
    &&conv_xxx1_0001,    /*  8h -> 32s */
    &&conv_xxx1_xxx9,    /*  8h ^>  8h */
    &&conv_xxx1_xxx9,    /*  8h ^>  8s */
    &&conv_xxx1_xx90,    /*  8h ^> 16h */
    &&conv_xxx1_xx09,    /*  8h ^> 16s */
    &&conv_xxx1_x900,    /*  8h ^> 24h */
    &&conv_xxx1_009x,    /*  8h ^> 24s */
    &&conv_xxx1_9000,    /*  8h ^> 32h */
    &&conv_xxx1_0009,    /*  8h ^> 32s */
    &&conv_xxx1_xxx1,    /*  8s ->  8h */
    &&conv_xxx1_xxx1,    /*  8s ->  8s */
    &&conv_xxx1_xx10,    /*  8s -> 16h */
    &&conv_xxx1_xx01,    /*  8s -> 16s */
    &&conv_xxx1_x100,    /*  8s -> 24h */
    &&conv_xxx1_001x,    /*  8s -> 24s */
    &&conv_xxx1_1000,    /*  8s -> 32h */
    &&conv_xxx1_0001,    /*  8s -> 32s */
    &&conv_xxx1_xxx9,    /*  8s ^>  8h */
    &&conv_xxx1_xxx9,    /*  8s ^>  8s */
    &&conv_xxx1_xx90,    /*  8s ^> 16h */
    &&conv_xxx1_xx09,    /*  8s ^> 16s */
    &&conv_xxx1_x900,    /*  8s ^> 24h */
    &&conv_xxx1_009x,    /*  8s ^> 24s */
    &&conv_xxx1_9000,    /*  8s ^> 32h */
    &&conv_xxx1_0009,    /*  8s ^> 32s */
    &&conv_xx12_xxx1,    /* 16h ->  8h */
    &&conv_xx12_xxx1,    /* 16h ->  8s */
    &&conv_xx12_xx12,    /* 16h -> 16h */
    &&conv_xx12_xx21,    /* 16h -> 16s */
    &&conv_xx12_x120,    /* 16h -> 24h */
    &&conv_xx12_021x,    /* 16h -> 24s */
    &&conv_xx12_1200,    /* 16h -> 32h */
    &&conv_xx12_0021,    /* 16h -> 32s */
    &&conv_xx12_xxx9,    /* 16h ^>  8h */
    &&conv_xx12_xxx9,    /* 16h ^>  8s */
    &&conv_xx12_xx92,    /* 16h ^> 16h */
    &&conv_xx12_xx29,    /* 16h ^> 16s */
    &&conv_xx12_x920,    /* 16h ^> 24h */
    &&conv_xx12_029x,    /* 16h ^> 24s */
    &&conv_xx12_9200,    /* 16h ^> 32h */
    &&conv_xx12_0029,    /* 16h ^> 32s */
    &&conv_xx12_xxx2,    /* 16s ->  8h */
    &&conv_xx12_xxx2,    /* 16s ->  8s */
    &&conv_xx12_xx21,    /* 16s -> 16h */
    &&conv_xx12_xx12,    /* 16s -> 16s */
    &&conv_xx12_x210,    /* 16s -> 24h */
    &&conv_xx12_012x,    /* 16s -> 24s */
    &&conv_xx12_2100,    /* 16s -> 32h */
    &&conv_xx12_0012,    /* 16s -> 32s */
    &&conv_xx12_xxxA,    /* 16s ^>  8h */
    &&conv_xx12_xxxA,    /* 16s ^>  8s */
    &&conv_xx12_xxA1,    /* 16s ^> 16h */
    &&conv_xx12_xx1A,    /* 16s ^> 16s */
    &&conv_xx12_xA10,    /* 16s ^> 24h */
    &&conv_xx12_01Ax,    /* 16s ^> 24s */
    &&conv_xx12_A100,    /* 16s ^> 32h */
    &&conv_xx12_001A,    /* 16s ^> 32s */
    &&conv_x123_xxx1,    /* 24h ->  8h */
    &&conv_x123_xxx1,    /* 24h ->  8s */
    &&conv_x123_xx12,    /* 24h -> 16h */
    &&conv_x123_xx21,    /* 24h -> 16s */
    &&conv_x123_x123,    /* 24h -> 24h */
    &&conv_x123_321x,    /* 24h -> 24s */
    &&conv_x123_1230,    /* 24h -> 32h */
    &&conv_x123_0321,    /* 24h -> 32s */
    &&conv_x123_xxx9,    /* 24h ^>  8h */
    &&conv_x123_xxx9,    /* 24h ^>  8s */
    &&conv_x123_xx92,    /* 24h ^> 16h */
    &&conv_x123_xx29,    /* 24h ^> 16s */
    &&conv_x123_x923,    /* 24h ^> 24h */
    &&conv_x123_329x,    /* 24h ^> 24s */
    &&conv_x123_9230,    /* 24h ^> 32h */
    &&conv_x123_0329,    /* 24h ^> 32s */
    &&conv_123x_xxx3,    /* 24s ->  8h */
    &&conv_123x_xxx3,    /* 24s ->  8s */
    &&conv_123x_xx32,    /* 24s -> 16h */
    &&conv_123x_xx23,    /* 24s -> 16s */
    &&conv_123x_x321,    /* 24s -> 24h */
    &&conv_123x_123x,    /* 24s -> 24s */
    &&conv_123x_3210,    /* 24s -> 32h */
    &&conv_123x_0123,    /* 24s -> 32s */
    &&conv_123x_xxxB,    /* 24s ^>  8h */
    &&conv_123x_xxxB,    /* 24s ^>  8s */
    &&conv_123x_xxB2,    /* 24s ^> 16h */
    &&conv_123x_xx2B,    /* 24s ^> 16s */
    &&conv_123x_xB21,    /* 24s ^> 24h */
    &&conv_123x_12Bx,    /* 24s ^> 24s */
    &&conv_123x_B210,    /* 24s ^> 32h */
    &&conv_123x_012B,    /* 24s ^> 32s */
    &&conv_1234_xxx1,    /* 32h ->  8h */
    &&conv_1234_xxx1,    /* 32h ->  8s */
    &&conv_1234_xx12,    /* 32h -> 16h */
    &&conv_1234_xx21,    /* 32h -> 16s */
    &&conv_1234_x123,    /* 32h -> 24h */
    &&conv_1234_321x,    /* 32h -> 24s */
    &&conv_1234_1234,    /* 32h -> 32h */
    &&conv_1234_4321,    /* 32h -> 32s */
    &&conv_1234_xxx9,    /* 32h ^>  8h */
    &&conv_1234_xxx9,    /* 32h ^>  8s */
    &&conv_1234_xx92,    /* 32h ^> 16h */
    &&conv_1234_xx29,    /* 32h ^> 16s */
    &&conv_1234_x923,    /* 32h ^> 24h */
    &&conv_1234_329x,    /* 32h ^> 24s */
    &&conv_1234_9234,    /* 32h ^> 32h */
    &&conv_1234_4329,    /* 32h ^> 32s */
    &&conv_1234_xxx4,    /* 32s ->  8h */
    &&conv_1234_xxx4,    /* 32s ->  8s */
    &&conv_1234_xx43,    /* 32s -> 16h */
    &&conv_1234_xx34,    /* 32s -> 16s */
    &&conv_1234_x432,    /* 32s -> 24h */
    &&conv_1234_234x,    /* 32s -> 24s */
    &&conv_1234_4321,    /* 32s -> 32h */
    &&conv_1234_1234,    /* 32s -> 32s */
    &&conv_1234_xxxC,    /* 32s ^>  8h */
    &&conv_1234_xxxC,    /* 32s ^>  8s */
    &&conv_1234_xxC3,    /* 32s ^> 16h */
    &&conv_1234_xx3C,    /* 32s ^> 16s */
    &&conv_1234_xC32,    /* 32s ^> 24h */
    &&conv_1234_23Cx,    /* 32s ^> 24s */
    &&conv_1234_C321,    /* 32s ^> 32h */
    &&conv_1234_123C,    /* 32s ^> 32s */
};
#endif

#ifdef CONV_END
while(0) {
conv_xxx1_xxx1: as_u8(dst) = as_u8c(src); goto CONV_END;
conv_xxx1_xx10: as_u16(dst) = (u_int16_t)as_u8c(src) << 8; goto CONV_END;
conv_xxx1_xx01: as_u16(dst) = (u_int16_t)as_u8c(src); goto CONV_END;
conv_xxx1_x100: as_u32(dst) = sx24((u_int32_t)as_u8c(src) << 16); goto CONV_END;
conv_xxx1_001x: as_u32(dst) = sx24s((u_int32_t)as_u8c(src) << 8); goto CONV_END;
conv_xxx1_1000: as_u32(dst) = (u_int32_t)as_u8c(src) << 24; goto CONV_END;
conv_xxx1_0001: as_u32(dst) = (u_int32_t)as_u8c(src); goto CONV_END;
conv_xxx1_xxx9: as_u8(dst) = as_u8c(src) ^ 0x80; goto CONV_END;
conv_xxx1_xx90: as_u16(dst) = (u_int16_t)(as_u8c(src) ^ 0x80) << 8; goto CONV_END;
conv_xxx1_xx09: as_u16(dst) = (u_int16_t)(as_u8c(src) ^ 0x80); goto CONV_END;
conv_xxx1_x900: as_u32(dst) = sx24((u_int32_t)(as_u8c(src) ^ 0x80) << 16); goto CONV_END;
conv_xxx1_009x: as_u32(dst) = sx24s((u_int32_t)(as_u8c(src) ^ 0x80) << 8); goto CONV_END;
conv_xxx1_9000: as_u32(dst) = (u_int32_t)(as_u8c(src) ^ 0x80) << 24; goto CONV_END;
conv_xxx1_0009: as_u32(dst) = (u_int32_t)(as_u8c(src) ^ 0x80); goto CONV_END;
conv_xx12_xxx1: as_u8(dst) = as_u16c(src) >> 8; goto CONV_END;
conv_xx12_xx12: as_u16(dst) = as_u16c(src); goto CONV_END;
conv_xx12_xx21: as_u16(dst) = bswap_16(as_u16c(src)); goto CONV_END;
conv_xx12_x120: as_u32(dst) = sx24((u_int32_t)as_u16c(src) << 8); goto CONV_END;
conv_xx12_021x: as_u32(dst) = sx24s((u_int32_t)bswap_16(as_u16c(src)) << 8); goto CONV_END;
conv_xx12_1200: as_u32(dst) = (u_int32_t)as_u16c(src) << 16; goto CONV_END;
conv_xx12_0021: as_u32(dst) = (u_int32_t)bswap_16(as_u16c(src)); goto CONV_END;
conv_xx12_xxx9: as_u8(dst) = (as_u16c(src) >> 8) ^ 0x80; goto CONV_END;
conv_xx12_xx92: as_u16(dst) = as_u16c(src) ^ 0x8000; goto CONV_END;
conv_xx12_xx29: as_u16(dst) = bswap_16(as_u16c(src)) ^ 0x80; goto CONV_END;
conv_xx12_x920: as_u32(dst) = sx24((u_int32_t)(as_u16c(src) ^ 0x8000) << 8); goto CONV_END;
conv_xx12_029x: as_u32(dst) = sx24s((u_int32_t)(bswap_16(as_u16c(src)) ^ 0x80) << 8); goto CONV_END;
conv_xx12_9200: as_u32(dst) = (u_int32_t)(as_u16c(src) ^ 0x8000) << 16; goto CONV_END;
conv_xx12_0029: as_u32(dst) = (u_int32_t)(bswap_16(as_u16c(src)) ^ 0x80); goto CONV_END;
conv_xx12_xxx2: as_u8(dst) = as_u16c(src) & 0xff; goto CONV_END;
conv_xx12_x210: as_u32(dst) = sx24((u_int32_t)bswap_16(as_u16c(src)) << 8); goto CONV_END;
conv_xx12_012x: as_u32(dst) = sx24s((u_int32_t)as_u16c(src) << 8); goto CONV_END;
conv_xx12_2100: as_u32(dst) = (u_int32_t)bswap_16(as_u16c(src)) << 16; goto CONV_END;
conv_xx12_0012: as_u32(dst) = (u_int32_t)as_u16c(src); goto CONV_END;
conv_xx12_xxxA: as_u8(dst) = (as_u16c(src) ^ 0x80) & 0xff; goto CONV_END;
conv_xx12_xxA1: as_u16(dst) = bswap_16(as_u16c(src) ^ 0x80); goto CONV_END;
conv_xx12_xx1A: as_u16(dst) = as_u16c(src) ^ 0x80; goto CONV_END;
conv_xx12_xA10: as_u32(dst) = sx24((u_int32_t)bswap_16(as_u16c(src) ^ 0x80) << 8); goto CONV_END;
conv_xx12_01Ax: as_u32(dst) = sx24s((u_int32_t)(as_u16c(src) ^ 0x80) << 8); goto CONV_END;
conv_xx12_A100: as_u32(dst) = (u_int32_t)bswap_16(as_u16c(src) ^ 0x80) << 16; goto CONV_END;
conv_xx12_001A: as_u32(dst) = (u_int32_t)(as_u16c(src) ^ 0x80); goto CONV_END;
conv_x123_xxx1: as_u8(dst) = as_u32c(src) >> 16; goto CONV_END;
conv_x123_xx12: as_u16(dst) = as_u32c(src) >> 8; goto CONV_END;
conv_x123_xx21: as_u16(dst) = bswap_16(as_u32c(src) >> 8); goto CONV_END;
conv_x123_x123: as_u32(dst) = sx24(as_u32c(src)); goto CONV_END;
conv_x123_321x: as_u32(dst) = sx24s(bswap_32(as_u32c(src))); goto CONV_END;
conv_x123_1230: as_u32(dst) = as_u32c(src) << 8; goto CONV_END;
conv_x123_0321: as_u32(dst) = bswap_32(as_u32c(src)) >> 8; goto CONV_END;
conv_x123_xxx9: as_u8(dst) = (as_u32c(src) >> 16) ^ 0x80; goto CONV_END;
conv_x123_xx92: as_u16(dst) = (as_u32c(src) >> 8) ^ 0x8000; goto CONV_END;
conv_x123_xx29: as_u16(dst) = bswap_16(as_u32c(src) >> 8) ^ 0x80; goto CONV_END;
conv_x123_x923: as_u32(dst) = sx24(as_u32c(src) ^ 0x800000); goto CONV_END;
conv_x123_329x: as_u32(dst) = sx24s(bswap_32(as_u32c(src)) ^ 0x8000); goto CONV_END;
conv_x123_9230: as_u32(dst) = (as_u32c(src) ^ 0x800000) << 8; goto CONV_END;
conv_x123_0329: as_u32(dst) = (bswap_32(as_u32c(src)) >> 8) ^ 0x80; goto CONV_END;
conv_123x_xxx3: as_u8(dst) = (as_u32c(src) >> 8) & 0xff; goto CONV_END;
conv_123x_xx32: as_u16(dst) = bswap_16(as_u32c(src) >> 8); goto CONV_END;
conv_123x_xx23: as_u16(dst) = (as_u32c(src) >> 8) & 0xffff; goto CONV_END;
conv_123x_x321: as_u32(dst) = sx24(bswap_32(as_u32c(src))); goto CONV_END;
conv_123x_123x: as_u32(dst) = sx24s(as_u32c(src)); goto CONV_END;
conv_123x_3210: as_u32(dst) = bswap_32(as_u32c(src)) << 8; goto CONV_END;
conv_123x_0123: as_u32(dst) = as_u32c(src) >> 8; goto CONV_END;
conv_123x_xxxB: as_u8(dst) = ((as_u32c(src) >> 8) & 0xff) ^ 0x80; goto CONV_END;
conv_123x_xxB2: as_u16(dst) = bswap_16((as_u32c(src) >> 8) ^ 0x80); goto CONV_END;
conv_123x_xx2B: as_u16(dst) = ((as_u32c(src) >> 8) & 0xffff) ^ 0x80; goto CONV_END;
conv_123x_xB21: as_u32(dst) = sx24(bswap_32(as_u32c(src)) ^ 0x800000); goto CONV_END;
conv_123x_12Bx: as_u32(dst) = sx24s(as_u32c(src) ^ 0x8000); goto CONV_END;
conv_123x_B210: as_u32(dst) = bswap_32(as_u32c(src) ^ 0x8000) << 8; goto CONV_END;
conv_123x_012B: as_u32(dst) = (as_u32c(src) >> 8) ^ 0x80; goto CONV_END;
conv_1234_xxx1: as_u8(dst) = as_u32c(src) >> 24; goto CONV_END;
conv_1234_xx12: as_u16(dst) = as_u32c(src) >> 16; goto CONV_END;
conv_1234_xx21: as_u16(dst) = bswap_16(as_u32c(src) >> 16); goto CONV_END;
conv_1234_x123: as_u32(dst) = sx24(as_u32c(src) >> 8); goto CONV_END;
conv_1234_321x: as_u32(dst) = sx24s(bswap_32(as_u32c(src)) << 8); goto CONV_END;
conv_1234_1234: as_u32(dst) = as_u32c(src); goto CONV_END;
conv_1234_4321: as_u32(dst) = bswap_32(as_u32c(src)); goto CONV_END;
conv_1234_xxx9: as_u8(dst) = (as_u32c(src) >> 24) ^ 0x80; goto CONV_END;
conv_1234_xx92: as_u16(dst) = (as_u32c(src) >> 16) ^ 0x8000; goto CONV_END;
conv_1234_xx29: as_u16(dst) = bswap_16(as_u32c(src) >> 16) ^ 0x80; goto CONV_END;
conv_1234_x923: as_u32(dst) = sx24((as_u32c(src) >> 8) ^ 0x800000); goto CONV_END;
conv_1234_329x: as_u32(dst) = sx24s((bswap_32(as_u32c(src)) ^ 0x80) << 8); goto CONV_END;
conv_1234_9234: as_u32(dst) = as_u32c(src) ^ 0x80000000; goto CONV_END;
conv_1234_4329: as_u32(dst) = bswap_32(as_u32c(src)) ^ 0x80; goto CONV_END;
conv_1234_xxx4: as_u8(dst) = as_u32c(src) & 0xff; goto CONV_END;
conv_1234_xx43: as_u16(dst) = bswap_16(as_u32c(src)); goto CONV_END;
conv_1234_xx34: as_u16(dst) = as_u32c(src) & 0xffff; goto CONV_END;
conv_1234_x432: as_u32(dst) = sx24(bswap_32(as_u32c(src)) >> 8); goto CONV_END;
conv_1234_234x: as_u32(dst) = sx24s(as_u32c(src) << 8); goto CONV_END;
conv_1234_xxxC: as_u8(dst) = (as_u32c(src) & 0xff) ^ 0x80; goto CONV_END;
conv_1234_xxC3: as_u16(dst) = bswap_16(as_u32c(src) ^ 0x80); goto CONV_END;
conv_1234_xx3C: as_u16(dst) = (as_u32c(src) & 0xffff) ^ 0x80; goto CONV_END;
conv_1234_xC32: as_u32(dst) = sx24((bswap_32(as_u32c(src)) >> 8) ^ 0x800000); goto CONV_END;
conv_1234_23Cx: as_u32(dst) = sx24s((as_u32c(src) ^ 0x80) << 8); goto CONV_END;
conv_1234_C321: as_u32(dst) = bswap_32(as_u32c(src) ^ 0x80); goto CONV_END;
conv_1234_123C: as_u32(dst) = as_u32c(src) ^ 0x80; goto CONV_END;
}
#endif

#ifdef GET16_LABELS
/* src_wid src_endswap sign_toggle */
static void *const get16_labels[4 * 2 * 2 + 4 * 3] = {
    &&get16_1_10,    /*  8h -> 16h */
    &&get16_1_90,    /*  8h ^> 16h */
    &&get16_1_10,    /*  8s -> 16h */
    &&get16_1_90,    /*  8s ^> 16h */
    &&get16_12_12,   /* 16h -> 16h */
    &&get16_12_92,   /* 16h ^> 16h */
    &&get16_12_21,   /* 16s -> 16h */
    &&get16_12_A1,   /* 16s ^> 16h */
    &&get16_0123_12, /* 24h -> 16h */
    &&get16_0123_92, /* 24h ^> 16h */
    &&get16_1230_32, /* 24s -> 16h */
    &&get16_1230_B2, /* 24s ^> 16h */
    &&get16_1234_12, /* 32h -> 16h */
    &&get16_1234_92, /* 32h ^> 16h */
    &&get16_1234_43, /* 32s -> 16h */
    &&get16_1234_C3, /* 32s ^> 16h */
    /* 3bytes format */
    &&get16_123_12,  /* 24h -> 16h */
    &&get16_123_92,  /* 24h ^> 16h */
    &&get16_123_32,  /* 24s -> 16h */
    &&get16_123_B2,  /* 24s ^> 16h */
    &&get16_123_12_20,   /* 20h -> 16h */
    &&get16_123_92_20,   /* 20h ^> 16h */
    &&get16_123_32_20,   /* 20s -> 16h */
    &&get16_123_B2_20,   /* 20s ^> 16h */
    &&get16_123_12_18,   /* 18h -> 16h */
    &&get16_123_92_18,   /* 18h ^> 16h */
    &&get16_123_32_18,   /* 18s -> 16h */
    &&get16_123_B2_18,   /* 18s ^> 16h */
};
#endif

#ifdef GET16_END
while(0) {
get16_1_10: sample = (u_int16_t)as_u8c(src) << 8; goto GET16_END;
get16_1_90: sample = (u_int16_t)(as_u8c(src) ^ 0x80) << 8; goto GET16_END;
get16_12_12: sample = as_u16c(src); goto GET16_END;
get16_12_92: sample = as_u16c(src) ^ 0x8000; goto GET16_END;
get16_12_21: sample = bswap_16(as_u16c(src)); goto GET16_END;
get16_12_A1: sample = bswap_16(as_u16c(src) ^ 0x80); goto GET16_END;
get16_0123_12: sample = as_u32c(src) >> 8; goto GET16_END;
get16_0123_92: sample = (as_u32c(src) >> 8) ^ 0x8000; goto GET16_END;
get16_1230_32: sample = bswap_16(as_u32c(src) >> 8); goto GET16_END;
get16_1230_B2: sample = bswap_16((as_u32c(src) >> 8) ^ 0x80); goto GET16_END;
get16_1234_12: sample = as_u32c(src) >> 16; goto GET16_END;
get16_1234_92: sample = (as_u32c(src) >> 16) ^ 0x8000; goto GET16_END;
get16_1234_43: sample = bswap_16(as_u32c(src)); goto GET16_END;
get16_1234_C3: sample = bswap_16(as_u32c(src) ^ 0x80); goto GET16_END;
get16_123_12: sample = _get_triple(src) >> 8; goto GET16_END;
get16_123_92: sample = (_get_triple(src) >> 8) ^ 0x8000; goto GET16_END;
get16_123_32: sample = _get_triple_s(src) >> 8; goto GET16_END;
get16_123_B2: sample = (_get_triple_s(src) >> 8) ^ 0x8000; goto GET16_END;
get16_123_12_20: sample = _get_triple(src) >> 4; goto GET16_END;
get16_123_92_20: sample = (_get_triple(src) >> 4) ^ 0x8000; goto GET16_END;
get16_123_32_20: sample = _get_triple_s(src) >> 4; goto GET16_END;
get16_123_B2_20: sample = (_get_triple_s(src) >> 4) ^ 0x8000; goto GET16_END;
get16_123_12_18: sample = _get_triple(src) >> 2; goto GET16_END;
get16_123_92_18: sample = (_get_triple(src) >> 2) ^ 0x8000; goto GET16_END;
get16_123_32_18: sample = _get_triple_s(src) >> 2; goto GET16_END;
get16_123_B2_18: sample = (_get_triple_s(src) >> 2) ^ 0x8000; goto GET16_END;
}
#endif

#ifdef PUT16_LABELS
/* dst_wid dst_endswap sign_toggle */
static void *const put16_labels[4 * 2 * 2 + 4 * 3] = {
    &&put16_12_1,        /* 16h ->  8h */
    &&put16_12_9,        /* 16h ^>  8h */
    &&put16_12_1,        /* 16h ->  8s */
    &&put16_12_9,        /* 16h ^>  8s */
    &&put16_12_12,       /* 16h -> 16h */
    &&put16_12_92,       /* 16h ^> 16h */
    &&put16_12_21,       /* 16h -> 16s */
    &&put16_12_29,       /* 16h ^> 16s */
    &&put16_12_0120,     /* 16h -> 24h */
    &&put16_12_0920,     /* 16h ^> 24h */
    &&put16_12_0210,     /* 16h -> 24s */
    &&put16_12_0290,     /* 16h ^> 24s */
    &&put16_12_1200,     /* 16h -> 32h */
    &&put16_12_9200,     /* 16h ^> 32h */
    &&put16_12_0021,     /* 16h -> 32s */
    &&put16_12_0029,     /* 16h ^> 32s */
    /* 3bytes format */
    &&put16_12_120,      /* 16h -> 24h */
    &&put16_12_920,      /* 16h ^> 24h */
    &&put16_12_021,      /* 16h -> 24s */
    &&put16_12_029,      /* 16h ^> 24s */
    &&put16_12_120_20,   /* 16h -> 20h */
    &&put16_12_920_20,   /* 16h ^> 20h */
    &&put16_12_021_20,   /* 16h -> 20s */
    &&put16_12_029_20,   /* 16h ^> 20s */
    &&put16_12_120_18,   /* 16h -> 18h */
    &&put16_12_920_18,   /* 16h ^> 18h */
    &&put16_12_021_18,   /* 16h -> 18s */
    &&put16_12_029_18,   /* 16h ^> 18s */
};
#endif

#ifdef PUT16_END
while (0) {
put16_12_1: as_u8(dst) = sample >> 8; goto PUT16_END;
put16_12_9: as_u8(dst) = (sample >> 8) ^ 0x80; goto PUT16_END;
put16_12_12: as_u16(dst) = sample; goto PUT16_END;
put16_12_92: as_u16(dst) = sample ^ 0x8000; goto PUT16_END;
put16_12_21: as_u16(dst) = bswap_16(sample); goto PUT16_END;
put16_12_29: as_u16(dst) = bswap_16(sample) ^ 0x80; goto PUT16_END;
put16_12_0120: as_u32(dst) = sx24((u_int32_t)sample << 8); goto PUT16_END;
put16_12_0920: as_u32(dst) = sx24((u_int32_t)(sample ^ 0x8000) << 8); goto PUT16_END;
put16_12_0210: as_u32(dst) = sx24s((u_int32_t)bswap_16(sample) << 8); goto PUT16_END;
put16_12_0290: as_u32(dst) = sx24s((u_int32_t)(bswap_16(sample) ^ 0x80) << 8); goto PUT16_END;
put16_12_1200: as_u32(dst) = (u_int32_t)sample << 16; goto PUT16_END;
put16_12_9200: as_u32(dst) = (u_int32_t)(sample ^ 0x8000) << 16; goto PUT16_END;
put16_12_0021: as_u32(dst) = (u_int32_t)bswap_16(sample); goto PUT16_END;
put16_12_0029: as_u32(dst) = (u_int32_t)bswap_16(sample) ^ 0x80; goto PUT16_END;
put16_12_120: _put_triple(dst, (u_int32_t)sample << 8); goto PUT16_END;
put16_12_920: _put_triple(dst, (u_int32_t)(sample ^ 0x8000) << 8); goto PUT16_END;
put16_12_021: _put_triple_s(dst, (u_int32_t)sample << 8); goto PUT16_END;
put16_12_029: _put_triple_s(dst, (u_int32_t)(sample ^ 0x8000) << 8); goto PUT16_END;
put16_12_120_20: _put_triple(dst, (u_int32_t)sample << 4); goto PUT16_END;
put16_12_920_20: _put_triple(dst, (u_int32_t)(sample ^ 0x8000) << 4); goto PUT16_END;
put16_12_021_20: _put_triple_s(dst, (u_int32_t)sample << 4); goto PUT16_END;
put16_12_029_20: _put_triple_s(dst, (u_int32_t)(sample ^ 0x8000) << 4); goto PUT16_END;
put16_12_120_18: _put_triple(dst, (u_int32_t)sample << 2); goto PUT16_END;
put16_12_920_18: _put_triple(dst, (u_int32_t)(sample ^ 0x8000) << 2); goto PUT16_END;
put16_12_021_18: _put_triple_s(dst, (u_int32_t)sample << 2); goto PUT16_END;
put16_12_029_18: _put_triple_s(dst, (u_int32_t)(sample ^ 0x8000) << 2); goto PUT16_END;
}
#endif

#ifdef CONV24_LABELS
#define GET32_LABELS
#define PUT32_LABELS
#endif

#ifdef GET32_LABELS
/* src_wid src_endswap sign_toggle */
static void *const get32_labels[4 * 2 * 2 + 4 * 3] = {
    &&get32_1_1000,      /*  8h -> 32h */
    &&get32_1_9000,      /*  8h ^> 32h */
    &&get32_1_1000,      /*  8s -> 32h */
    &&get32_1_9000,      /*  8s ^> 32h */
    &&get32_12_1200,     /* 16h -> 32h */
    &&get32_12_9200,     /* 16h ^> 32h */
    &&get32_12_2100,     /* 16s -> 32h */
    &&get32_12_A100,     /* 16s ^> 32h */
    &&get32_0123_1230,   /* 24h -> 32h */
    &&get32_0123_9230,   /* 24h ^> 32h */
    &&get32_1230_3210,   /* 24s -> 32h */
    &&get32_1230_B210,   /* 24s ^> 32h */
    &&get32_1234_1234,   /* 32h -> 32h */
    &&get32_1234_9234,   /* 32h ^> 32h */
    &&get32_1234_4321,   /* 32s -> 32h */
    &&get32_1234_C321,   /* 32s ^> 32h */
    /* 3bytes format */
    &&get32_123_1230,    /* 24h -> 32h */
    &&get32_123_9230,    /* 24h ^> 32h */
    &&get32_123_3210,    /* 24s -> 32h */
    &&get32_123_B210,    /* 24s ^> 32h */
    &&get32_123_1230_20,     /* 20h -> 32h */
    &&get32_123_9230_20,     /* 20h ^> 32h */
    &&get32_123_3210_20,     /* 20s -> 32h */
    &&get32_123_B210_20,     /* 20s ^> 32h */
    &&get32_123_1230_18,     /* 18h -> 32h */
    &&get32_123_9230_18,     /* 18h ^> 32h */
    &&get32_123_3210_18,     /* 18s -> 32h */
    &&get32_123_B210_18,     /* 18s ^> 32h */
};
#endif

#ifdef CONV24_END
#define GET32_END __conv24_get
#endif

#ifdef GET32_END
while (0) {
get32_1_1000: sample = (u_int32_t)as_u8c(src) << 24; goto GET32_END;
get32_1_9000: sample = (u_int32_t)(as_u8c(src) ^ 0x80) << 24; goto GET32_END;
get32_12_1200: sample = (u_int32_t)as_u16c(src) << 16; goto GET32_END;
get32_12_9200: sample = (u_int32_t)(as_u16c(src) ^ 0x8000) << 16; goto GET32_END;
get32_12_2100: sample = (u_int32_t)bswap_16(as_u16c(src)) << 16; goto GET32_END;
get32_12_A100: sample = (u_int32_t)bswap_16(as_u16c(src) ^ 0x80) << 16; goto GET32_END;
get32_0123_1230: sample = as_u32c(src) << 8; goto GET32_END;
get32_0123_9230: sample = (as_u32c(src) << 8) ^ 0x80000000; goto GET32_END;
get32_1230_3210: sample = bswap_32(as_u32c(src) >> 8); goto GET32_END;
get32_1230_B210: sample = bswap_32((as_u32c(src) >> 8) ^ 0x80); goto GET32_END;
get32_1234_1234: sample = as_u32c(src); goto GET32_END;
get32_1234_9234: sample = as_u32c(src) ^ 0x80000000; goto GET32_END;
get32_1234_4321: sample = bswap_32(as_u32c(src)); goto GET32_END;
get32_1234_C321: sample = bswap_32(as_u32c(src) ^ 0x80); goto GET32_END;
get32_123_1230: sample = _get_triple(src) << 8; goto GET32_END;
get32_123_9230: sample = (_get_triple(src) << 8) ^ 0x80000000; goto GET32_END;
get32_123_3210: sample = _get_triple_s(src) << 8; goto GET32_END;
get32_123_B210: sample = (_get_triple_s(src) << 8) ^ 0x80000000; goto GET32_END;
get32_123_1230_20: sample = _get_triple(src) << 12; goto GET32_END;
get32_123_9230_20: sample = (_get_triple(src) << 12) ^ 0x80000000; goto GET32_END;
get32_123_3210_20: sample = _get_triple_s(src) << 12; goto GET32_END;
get32_123_B210_20: sample = (_get_triple_s(src) << 12) ^ 0x80000000; goto GET32_END;
get32_123_1230_18: sample = _get_triple(src) << 14; goto GET32_END;
get32_123_9230_18: sample = (_get_triple(src) << 14) ^ 0x80000000; goto GET32_END;
get32_123_3210_18: sample = _get_triple_s(src) << 14; goto GET32_END;
get32_123_B210_18: sample = (_get_triple_s(src) << 14) ^ 0x80000000; goto GET32_END;
}
#endif

#ifdef CONV24_END
__conv24_get: goto *put;
#define PUT32_END CONV24_END
#endif

#ifdef PUT32_LABELS
/* dst_wid dst_endswap sign_toggle */
static void *const put32_labels[4 * 2 * 2 + 4 * 3] = {
    &&put32_1234_1,      /* 32h ->  8h */
    &&put32_1234_9,      /* 32h ^>  8h */
    &&put32_1234_1,      /* 32h ->  8s */
    &&put32_1234_9,      /* 32h ^>  8s */
    &&put32_1234_12,     /* 32h -> 16h */
    &&put32_1234_92,     /* 32h ^> 16h */
    &&put32_1234_21,     /* 32h -> 16s */
    &&put32_1234_29,     /* 32h ^> 16s */
    &&put32_1234_0123,   /* 32h -> 24h */
    &&put32_1234_0923,   /* 32h ^> 24h */
    &&put32_1234_3210,   /* 32h -> 24s */
    &&put32_1234_3290,   /* 32h ^> 24s */
    &&put32_1234_1234,   /* 32h -> 32h */
    &&put32_1234_9234,   /* 32h ^> 32h */
    &&put32_1234_4321,   /* 32h -> 32s */
    &&put32_1234_4329,   /* 32h ^> 32s */
    /* 3bytes format */
    &&put32_1234_123,    /* 32h -> 24h */
    &&put32_1234_923,    /* 32h ^> 24h */
    &&put32_1234_321,    /* 32h -> 24s */
    &&put32_1234_329,    /* 32h ^> 24s */
    &&put32_1234_123_20,     /* 32h -> 24h */
    &&put32_1234_923_20,     /* 32h ^> 24h */
    &&put32_1234_321_20,     /* 32h -> 24s */
    &&put32_1234_329_20,     /* 32h ^> 24s */
    &&put32_1234_123_18,     /* 32h -> 24h */
    &&put32_1234_923_18,     /* 32h ^> 24h */
    &&put32_1234_321_18,     /* 32h -> 24s */
    &&put32_1234_329_18,     /* 32h ^> 24s */
};
#endif

#ifdef CONV24_LABELS
#undef GET32_LABELS
#undef PUT32_LABELS
#endif

#ifdef PUT32_END
while (0) {
put32_1234_1: as_u8(dst) = sample >> 24; goto PUT32_END;
put32_1234_9: as_u8(dst) = (sample >> 24) ^ 0x80; goto PUT32_END;
put32_1234_12: as_u16(dst) = sample >> 16; goto PUT32_END;
put32_1234_92: as_u16(dst) = (sample >> 16) ^ 0x8000; goto PUT32_END;
put32_1234_21: as_u16(dst) = bswap_16(sample >> 16); goto PUT32_END;
put32_1234_29: as_u16(dst) = bswap_16(sample >> 16) ^ 0x80; goto PUT32_END;
put32_1234_0123: as_u32(dst) = sx24(sample >> 8); goto PUT32_END;
put32_1234_0923: as_u32(dst) = sx24((sample >> 8) ^ 0x800000); goto PUT32_END;
put32_1234_3210: as_u32(dst) = sx24s(bswap_32(sample) << 8); goto PUT32_END;
put32_1234_3290: as_u32(dst) = sx24s((bswap_32(sample) ^ 0x80) << 8); goto PUT32_END;
put32_1234_1234: as_u32(dst) = sample; goto PUT32_END;
put32_1234_9234: as_u32(dst) = sample ^ 0x80000000; goto PUT32_END;
put32_1234_4321: as_u32(dst) = bswap_32(sample); goto PUT32_END;
put32_1234_4329: as_u32(dst) = bswap_32(sample) ^ 0x80; goto PUT32_END;
put32_1234_123: _put_triple(dst, sample >> 8); goto PUT32_END;
put32_1234_923: _put_triple(dst, (sample ^ 0x80000000) >> 8); goto PUT32_END;
put32_1234_321: _put_triple_s(dst, sample >> 8); goto PUT32_END;
put32_1234_329: _put_triple_s(dst, (sample ^ 0x80000000) >> 8); goto PUT32_END;
put32_1234_123_20: _put_triple(dst, sample >> 12); goto PUT32_END;
put32_1234_923_20: _put_triple(dst, (sample ^ 0x80000000) >> 12); goto PUT32_END;
put32_1234_321_20: _put_triple_s(dst, sample >> 12); goto PUT32_END;
put32_1234_329_20: _put_triple_s(dst, (sample ^ 0x80000000) >> 12); goto PUT32_END;
put32_1234_123_18: _put_triple(dst, sample >> 14); goto PUT32_END;
put32_1234_923_18: _put_triple(dst, (sample ^ 0x80000000) >> 14); goto PUT32_END;
put32_1234_321_18: _put_triple_s(dst, sample >> 14); goto PUT32_END;
put32_1234_329_18: _put_triple_s(dst, (sample ^ 0x80000000) >> 14); goto PUT32_END;
}
#endif

#ifdef CONV24_END
#undef GET32_END
#undef PUT32_END
#endif

#ifdef GETU_LABELS
/* width endswap sign_toggle */
static void *const getu_labels[4 * 2 * 2] = {
    &&getu_1_1,     /*  8h ->  8h */
    &&getu_1_9,     /*  8h ^>  8h */
    &&getu_1_1,     /*  8s ->  8h */
    &&getu_1_9,     /*  8s ^>  8h */
    &&getu_12_12,       /* 16h -> 16h */
    &&getu_12_92,       /* 16h ^> 16h */
    &&getu_12_21,       /* 16s -> 16h */
    &&getu_12_A1,       /* 16s ^> 16h */
    &&getu_0123_0123,   /* 24h -> 24h */
    &&getu_0123_0923,   /* 24h ^> 24h */
    &&getu_1230_0321,   /* 24s -> 24h */
    &&getu_1230_0B21,   /* 24s ^> 24h */
    &&getu_1234_1234,   /* 32h -> 32h */
    &&getu_1234_9234,   /* 32h ^> 32h */
    &&getu_1234_4321,   /* 32s -> 32h */
    &&getu_1234_C321,   /* 32s ^> 32h */
};
#endif

#ifdef GETU_END
while (0) {
getu_1_1: sample = as_u8c(src); goto GETU_END;
getu_1_9: sample = as_u8c(src) ^ 0x80; goto GETU_END;
getu_12_12: sample = as_u16c(src); goto GETU_END;
getu_12_92: sample = as_u16c(src) ^ 0x8000; goto GETU_END;
getu_12_21: sample = bswap_16(as_u16c(src)); goto GETU_END;
getu_12_A1: sample = bswap_16(as_u16c(src) ^ 0x80); goto GETU_END;
getu_0123_0123: sample = sx24(as_u32c(src)); goto GETU_END;
getu_0123_0923: sample = sx24(as_u32c(src) ^ 0x800000); goto GETU_END;
getu_1230_0321: sample = sx24(bswap_32(as_u32c(src))); goto GETU_END;
getu_1230_0B21: sample = sx24(bswap_32(as_u32c(src) ^ 0x8000)); goto GETU_END;
getu_1234_1234: sample = as_u32c(src); goto GETU_END;
getu_1234_9234: sample = as_u32c(src) ^ 0x80000000; goto GETU_END;
getu_1234_4321: sample = bswap_32(as_u32c(src)); goto GETU_END;
getu_1234_C321: sample = bswap_32(as_u32c(src) ^ 0x80); goto GETU_END;
}
#endif

#ifdef PUT32F_LABELS
/* type (0 = float, 1 = float64), endswap */
static void *const put32float_labels[2 * 2] = {
    &&put32f_1234_1234F,    /* 32h -> (float)h */
    &&put32f_1234_4321F,    /* 32h -> (float)s */
    &&put32f_1234_1234D,    /* 32h -> (float64)h */
    &&put32f_1234_4321D,    /* 32h -> (float64)s */
};
#endif

#ifdef PUT32F_END
put32f_1234_1234F: as_float(dst) = (float_t)((int32_t)sample) / (float_t)0x80000000UL; goto PUT32F_END;
put32f_1234_4321F: tmp_float.f = (float_t)((int32_t)sample) / (float_t)0x80000000UL;
           as_u32(dst) = bswap_32(tmp_float.i); goto PUT32F_END;
put32f_1234_1234D: as_double(dst) = (double_t)((int32_t)sample) / (double_t)0x80000000UL; goto PUT32F_END;
put32f_1234_4321D: tmp_double.d = (double_t)((int32_t)sample) / (double_t)0x80000000UL;
           as_u64(dst) = bswap_64(tmp_double.l); goto PUT32F_END;
#endif

#ifdef GET32F_LABELS
/* type (0 = float, 1 = float64), endswap */
static void *const get32float_labels[2 * 2] = {
    &&get32f_1234F_1234,    /* (float)h -> 32h */
    &&get32f_4321F_1234,    /* (float)s -> 32h */
    &&get32f_1234D_1234,    /* (float64)h -> 32h */
    &&get32f_4321D_1234,    /* (float64)s -> 32h */
};
#endif

#ifdef GET32F_END
get32f_1234F_1234: tmp_float.f = as_floatc(src);
           if (tmp_float.f >= 1.0)
            sample = 0x7fffffff;
           else if (tmp_float.f <= -1.0)
            sample = 0x80000000;
           else
            sample = (int32_t)(tmp_float.f * (float_t)0x80000000UL);
           goto GET32F_END;
get32f_4321F_1234: tmp_float.i = bswap_32(as_u32c(src));
           if (tmp_float.f >= 1.0)
            sample = 0x7fffffff;
           else if (tmp_float.f <= -1.0)
            sample = 0x80000000;
           else
            sample = (int32_t)(tmp_float.f * (float_t)0x80000000UL);
           goto GET32F_END;
get32f_1234D_1234: tmp_double.d = as_doublec(src);
           if (tmp_double.d >= 1.0)
            sample = 0x7fffffff;
           else if (tmp_double.d <= -1.0)
            sample = 0x80000000;
           else
            sample = (int32_t)(tmp_double.d * (double_t)0x80000000UL);
           goto GET32F_END;
get32f_4321D_1234: tmp_double.l = bswap_64(as_u64c(src));
           if (tmp_double.d >= 1.0)
            sample = 0x7fffffff;
           else if (tmp_double.d <= -1.0)
            sample = 0x80000000;
           else
            sample = (int32_t)(tmp_double.d * (double_t)0x80000000UL);
           goto GET32F_END;
#endif

#ifdef NORMS_LABELS
static inline void _norms(const void *src, void *dst,
              int src_wid,
              int dst_sign, int dst_wid, int dst_end)
{
    int32_t s;
    switch (src_wid) {
    case 8:
        s = *(int32_t*)src;
        if (s >= 0x7f)
            goto _max;
        else if (s <= -0x80)
            goto _min;
        break;
    case 16:
        s = *(int32_t*)src;
        if (s >= 0x7fff)
            goto _max;
        else if (s <= -0x8000)
            goto _min;
        break;
    case 24:
        s = *(int32_t*)src;
        if (s >= 0x7fffff)
            goto _max;
        else if (s <= -0x800000)
            goto _min;
        break;
    case 32:
    {
        int64_t s64;
        s64 = *(int64_t*)src;
        if (s64 >= 0x7fffffff)
            goto _max;
        else if (s64 <= -0x80000000)
            goto _min;
        s = s64;
        break;
    }
    default:
        assert(0);
        return;
    }
    if (src_wid < dst_wid) {
        unsigned int bits = dst_wid - src_wid;
        s *= 1 << bits;
    } else if (src_wid > dst_wid) {
        unsigned int bits = src_wid - dst_wid;
        s = (s + (1 << (bits - 1))) / (1 << bits);
    }
    if (!dst_sign)
        s += (1U << (dst_wid - 1));
    switch (dst_wid) {
    case 8:
        *(u_int8_t*)dst = s;
        break;
    case 16:
        if (dst_end)
            s = bswap_16(s);
        *(u_int16_t*)dst = s;
        break;
    case 24:
    case 32:
        if (dst_end)
            s = bswap_32(s);
        *(u_int32_t*)dst = s;
        break;
    }
    return;

 _min:
    switch (dst_wid) {
    case 8:
        if (dst_sign)
            *(u_int8_t*)dst = 0x80;
        else
            *(u_int8_t*)dst = 0;
        break;
    case 16:
        if (dst_sign)
            *(u_int16_t*)dst = dst_end ? 0x0080 : 0x8000;
        else
            *(u_int16_t*)dst = 0;
        break;
    case 24:
        if (dst_sign)
            *(u_int32_t*)dst = dst_end ? 0x00008000 : 0x00800000;
        else
            *(u_int32_t*)dst = 0;
        break;
    case 32:
        if (dst_sign)
            *(u_int32_t*)dst = dst_end ? 0x00000080 : 0x80000000;
        else
            *(u_int32_t*)dst = 0;
        break;
    default:
        assert(0);
        break;
    }
    return;

 _max:
    switch (dst_wid) {
    case 8:
        if (dst_sign)
            *(u_int8_t*)dst = 0x7f;
        else
            *(u_int8_t*)dst = 0xff;
        break;
    case 16:
        if (dst_sign)
            *(u_int16_t*)dst = dst_end ? 0xff7f : 0x7fff;
        else
            *(u_int16_t*)dst = 0;
        break;
    case 24:
        if (dst_sign)
            *(u_int32_t*)dst = dst_end ? 0xffff7f00 : 0x007fffff;
        else
            *(u_int32_t*)dst = 0;
        break;
    case 32:
        if (dst_sign)
            *(u_int32_t*)dst = dst_end ? 0xffffff7f : 0x7fffffff;
        else
            *(u_int32_t*)dst = 0;
        break;
    default:
        assert(0);
        break;
    }
    return;
}

/* src_wid dst_sign dst_wid dst_end */
static void *const norms_labels[4 * 2 * 4 * 2] = {
    &&norms_8_u8,           /*  s8 -> u8 */
    &&norms_8_u8,           /*  s8 -> u8 */
    &&norms_8_u16h,         /*  s8 -> u16h */
    &&norms_8_u16s,         /*  s8 -> u16s */
    &&norms_8_u24h,         /*  s8 -> u24h */
    &&norms_8_u24s,         /*  s8 -> u24s */
    &&norms_8_u32h,         /*  s8 -> u32h */
    &&norms_8_u32s,         /*  s8 -> u32s */
    &&norms_8_s8,           /*  s8 -> s8 */
    &&norms_8_s8,           /*  s8 -> s8 */
    &&norms_8_s16h,         /*  s8 -> s16h */
    &&norms_8_s16s,         /*  s8 -> s16s */
    &&norms_8_s24h,         /*  s8 -> s24h */
    &&norms_8_s24s,         /*  s8 -> s24s */
    &&norms_8_s32h,         /*  s8 -> s32h */
    &&norms_8_s32s,         /*  s8 -> s32s */
    &&norms_16_u8,          /* s16 -> u8 */
    &&norms_16_u8,          /* s16 -> u8 */
    &&norms_16_u16h,    /* s16 -> u16h */
    &&norms_16_u16s,    /* s16 -> u16s */
    &&norms_16_u24h,    /* s16 -> u24h */
    &&norms_16_u24s,    /* s16 -> u24s */
    &&norms_16_u32h,    /* s16 -> u32h */
    &&norms_16_u32s,    /* s16 -> u32s */
    &&norms_16_s8,      /* s16 -> s8 h*/
    &&norms_16_s8,      /* s16 -> s8 */
    &&norms_16_s16h,    /* s16 -> s16h */
    &&norms_16_s16s,    /* s16 -> s16s */
    &&norms_16_s24h,    /* s16 -> s24h */
    &&norms_16_s24s,    /* s16 -> s24s */
    &&norms_16_s32h,    /* s16 -> s32h */
    &&norms_16_s32s,    /* s16 -> s32s */
    &&norms_24_u8,      /* s24 -> u8 */
    &&norms_24_u8,      /* s24 -> u8 */
    &&norms_24_u16h,    /* s24 -> u16h */
    &&norms_24_u16s,    /* s24 -> u16s */
    &&norms_24_u24h,    /* s24 -> u24h */
    &&norms_24_u24s,    /* s24 -> u24s */
    &&norms_24_u32h,    /* s24 -> u32h */
    &&norms_24_u32s,    /* s24 -> u32s */
    &&norms_24_s8,      /* s24 -> s8 */
    &&norms_24_s8,      /* s24 -> s8 */
    &&norms_24_s16h,    /* s24 -> s16h */
    &&norms_24_s16s,    /* s24 -> s16s */
    &&norms_24_s24h,    /* s24 -> s24h */
    &&norms_24_s24s,    /* s24 -> s24s */
    &&norms_24_s32h,    /* s24 -> s32h */
    &&norms_24_s32s,    /* s24 -> s32s */
    &&norms_32_u8,      /* s32 -> u8 */
    &&norms_32_u8,      /* s32 -> u8 */
    &&norms_32_u16h,    /* s32 -> u16h */
    &&norms_32_u16s,    /* s32 -> u16s */
    &&norms_32_u24h,    /* s32 -> u24h */
    &&norms_32_u24s,    /* s32 -> u24s */
    &&norms_32_u32h,    /* s32 -> u32h */
    &&norms_32_u32s,    /* s32 -> u32s */
    &&norms_32_s8,      /* s32 -> s8 */
    &&norms_32_s8,      /* s32 -> s8 */
    &&norms_32_s16h,    /* s32 -> s16h */
    &&norms_32_s16s,    /* s32 -> s16s */
    &&norms_32_s24h,    /* s32 -> s24h */
    &&norms_32_s24s,    /* s32 -> s24s */
    &&norms_32_s32h,    /* s32 -> s32h */
    &&norms_32_s32s,    /* s32 -> s32s */
};
#endif

#ifdef NORMS_END
norms_8_u8: _norms(src, dst,  8, 0,  8, 0); goto NORMS_END;
norms_8_u16h:   _norms(src, dst,  8, 0,  16, 0); goto NORMS_END;
norms_8_u16s:   _norms(src, dst,  8, 0,  16, 1); goto NORMS_END;
norms_8_u24h:   _norms(src, dst,  8, 0,  24, 0); goto NORMS_END;
norms_8_u24s:   _norms(src, dst,  8, 0,  24, 1); goto NORMS_END;
norms_8_u32h:   _norms(src, dst,  8, 0,  32, 0); goto NORMS_END;
norms_8_u32s:   _norms(src, dst,  8, 0,  32, 1); goto NORMS_END;
norms_8_s8: _norms(src, dst,  8, 1,  8, 0); goto NORMS_END;
norms_8_s16h:   _norms(src, dst,  8, 1,  16, 0); goto NORMS_END;
norms_8_s16s:   _norms(src, dst,  8, 1,  16, 1); goto NORMS_END;
norms_8_s24h:   _norms(src, dst,  8, 1,  24, 0); goto NORMS_END;
norms_8_s24s:   _norms(src, dst,  8, 1,  24, 1); goto NORMS_END;
norms_8_s32h:   _norms(src, dst,  8, 1,  32, 0); goto NORMS_END;
norms_8_s32s:   _norms(src, dst,  8, 1,  32, 1); goto NORMS_END;
norms_16_u8:    _norms(src, dst, 16, 0,  8, 0); goto NORMS_END;
norms_16_u16h:  _norms(src, dst, 16, 0,  16, 0); goto NORMS_END;
norms_16_u16s:  _norms(src, dst, 16, 0,  16, 1); goto NORMS_END;
norms_16_u24h:  _norms(src, dst, 16, 0,  24, 0); goto NORMS_END;
norms_16_u24s:  _norms(src, dst, 16, 0,  24, 1); goto NORMS_END;
norms_16_u32h:  _norms(src, dst, 16, 0,  32, 0); goto NORMS_END;
norms_16_u32s:  _norms(src, dst, 16, 0,  32, 1); goto NORMS_END;
norms_16_s8:    _norms(src, dst, 16, 1,  8, 0); goto NORMS_END;
norms_16_s16h:  _norms(src, dst, 16, 1,  16, 0); goto NORMS_END;
norms_16_s16s:  _norms(src, dst, 16, 1,  16, 1); goto NORMS_END;
norms_16_s24h:  _norms(src, dst, 16, 1,  24, 0); goto NORMS_END;
norms_16_s24s:  _norms(src, dst, 16, 1,  24, 1); goto NORMS_END;
norms_16_s32h:  _norms(src, dst, 16, 1,  32, 0); goto NORMS_END;
norms_16_s32s:  _norms(src, dst, 16, 1,  32, 1); goto NORMS_END;
norms_24_u8:    _norms(src, dst, 24, 0,  8, 0); goto NORMS_END;
norms_24_u16h:  _norms(src, dst, 24, 0,  16, 0); goto NORMS_END;
norms_24_u16s:  _norms(src, dst, 24, 0,  16, 1); goto NORMS_END;
norms_24_u24h:  _norms(src, dst, 24, 0,  24, 0); goto NORMS_END;
norms_24_u24s:  _norms(src, dst, 24, 0,  24, 1); goto NORMS_END;
norms_24_u32h:  _norms(src, dst, 24, 0,  32, 0); goto NORMS_END;
norms_24_u32s:  _norms(src, dst, 24, 0,  32, 1); goto NORMS_END;
norms_24_s8:    _norms(src, dst, 24, 1,  8, 0); goto NORMS_END;
norms_24_s16h:  _norms(src, dst, 24, 1,  16, 0); goto NORMS_END;
norms_24_s16s:  _norms(src, dst, 24, 1,  16, 1); goto NORMS_END;
norms_24_s24h:  _norms(src, dst, 24, 1,  24, 0); goto NORMS_END;
norms_24_s24s:  _norms(src, dst, 24, 1,  24, 1); goto NORMS_END;
norms_24_s32h:  _norms(src, dst, 24, 1,  32, 0); goto NORMS_END;
norms_24_s32s:  _norms(src, dst, 24, 1,  32, 1); goto NORMS_END;
norms_32_u8:    _norms(src, dst, 32, 0,  8, 0); goto NORMS_END;
norms_32_u16h:  _norms(src, dst, 32, 0,  16, 0); goto NORMS_END;
norms_32_u16s:  _norms(src, dst, 32, 0,  16, 1); goto NORMS_END;
norms_32_u24h:  _norms(src, dst, 32, 0,  24, 0); goto NORMS_END;
norms_32_u24s:  _norms(src, dst, 32, 0,  24, 1); goto NORMS_END;
norms_32_u32h:  _norms(src, dst, 32, 0,  32, 0); goto NORMS_END;
norms_32_u32s:  _norms(src, dst, 32, 0,  32, 1); goto NORMS_END;
norms_32_s8:    _norms(src, dst, 32, 1,  8, 0); goto NORMS_END;
norms_32_s16h:  _norms(src, dst, 32, 1,  16, 0); goto NORMS_END;
norms_32_s16s:  _norms(src, dst, 32, 1,  16, 1); goto NORMS_END;
norms_32_s24h:  _norms(src, dst, 32, 1,  24, 0); goto NORMS_END;
norms_32_s24s:  _norms(src, dst, 32, 1,  24, 1); goto NORMS_END;
norms_32_s32h:  _norms(src, dst, 32, 1,  32, 0); goto NORMS_END;
norms_32_s32s:  _norms(src, dst, 32, 1,  32, 1); goto NORMS_END;
#endif


#undef as_u8
#undef as_u16
#undef as_u32
#undef as_s8
#undef as_s16
#undef as_s32
#undef as_float
#undef as_double

#undef as_u8c
#undef as_u16c
#undef as_u32c
#undef as_s8c
#undef as_s16c
#undef as_s32c
#undef as_floatc
#undef as_doublec

#undef _get_triple
#undef _get_triple_s
#undef _get_triple_le
#undef _get_triple_be
#undef _put_triple
#undef _put_triple_s
#undef _put_triple_le
#undef _put_triple_be
