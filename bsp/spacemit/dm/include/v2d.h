/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __SPACEMIT_V2D_H__
#define __SPACEMIT_V2D_H__

#include <stdbool.h>
#include <stdint.h>
#include <sys/ioctl.h>

#define V2D_BUFFER_MAX_SIZE         (64U * 1024U * 1024U)

typedef enum SPACEMIT_V2D_SCALER_MODE_E
{
    V2D_NO_SCALE    =0,
    V2D_SCALE_DOWN  =1,
    V2D_SCALE_UP    =2,
} V2D_SCALER_MODE_E;

typedef enum SPACEMIT_V2D_INPUT_LAYER_E
{
    V2D_INPUT_LAYER0    =0,
    V2D_INPUT_LAYER1    =1,
    V2D_INPUT_LAYER_NUM =2,
} V2D_INPUT_LAYER_E;

typedef enum SPACEMIT_V2D_FUNCTION_MODE_E
{
    V2D_FUNC_DISABLE=0,
    V2D_FUNC_ENABLE =1,
} V2D_FUNCTION_MODE_E;

typedef enum SPACEMIT_V2D_DITHER_E
{
    V2D_NO_DITHER   =0,
    V2D_DITHER_4X4  =1,
    V2D_DITHER_8X8  =2,
} V2D_DITHER_E;

typedef enum SPACEMIT_V2D_ROTATE_ANGLE
{
    V2D_ROT_0       =0,
    V2D_ROT_90      =1,
    V2D_ROT_180     =2,
    V2D_ROT_270     =3,
    V2D_ROT_MIRROR  =4,
    V2D_ROT_FLIP    =5,
} V2D_ROTATE_ANGLE_E;

typedef enum SPACEMIT_V2D_BLENDCMD_E
{
    V2D_BLENDCMD_ALPHA  = 0,
    V2D_BLENDCMD_ROP2   = 1,
    V2D_BLENDCMD_BUTT
} V2D_BLENDCMD_E;

typedef enum SPACEMIT_V2D_MASKCMD_E
{
    V2D_MASKCMD_DISABLE     = 0,
    V2D_MASKCMD_NORMAL      = 1,
    V2D_MASKCMD_AS_VALUE    = 2,
    V2D_MASKCMD_BUTT
} V2D_MASKCMD_E;

typedef enum SPACEMIT_V2D_BLENDALPHA_SOURCE_E
{
    V2D_BLENDALPHA_SOURCE_PIXEL     = 0,
    V2D_BLENDALPHA_SOURCE_GOLBAL    = 1,
    V2D_BLENDALPHA_SOURCE_MASK      = 2,
    V2D_BLENDALPHA_SOURCE_BUTT
} V2D_BLENDALPHA_SOURCE_E;

typedef enum SPACEMIT_V2D_BLEND_PRE_ALPHA_FUNC_E
{
    V2D_BLEND_PRE_ALPHA_FUNC_DISABLE                = 0,
    V2D_BLEND_PRE_ALPHA_FUNC_GLOBAL_MULTI_SOURCE    = 1,
    V2D_BLEND_PRE_ALPHA_FUNC_MASK_MULTI_SOURCE      = 2,
    V2D_BLEND_PRE_ALPHA_FUNC_BUTT
} V2D_BLEND_PRE_ALPHA_FUNC_E;

typedef enum SPACEMIT_V2D_BLEND_MODE_E
{
    V2D_BLEND_ZERO = 0x0,
    V2D_BLEND_ONE,
    V2D_BLEND_SRC_ALPHA,
    V2D_BLEND_ONE_MINUS_SRC_ALPHA,
    V2D_BLEND_DST_ALPHA,
    V2D_BLEND_ONE_MINUS_DST_ALPHA,
    V2D_BLEND_BUTT
}V2D_BLEND_MODE_E;

typedef enum SPACEMIT_V2D_ROP2_MODE_E
{
    V2D_ROP2_BLACK      =0,
    V2D_ROP2_NOTMERGEPEN=1,
    V2D_ROP2_MASKNOTPEN =2,
    V2D_ROP2_NOTCOPYPEN =3,
    V2D_ROP2_MASKPENNOT =4,
    V2D_ROP2_NOT        =5,
    V2D_ROP2_XORPEN     =6,
    V2D_ROP2_NOTMASKPEN =7,
    V2D_ROP2_MASKPEN    =8,
    V2D_ROP2_NOTXORPEN  =9,
    V2D_ROP2_NOP        =10,
    V2D_ROP2_MERGENOTPEN=11,
    V2D_ROP2_COPYPEN    =12,
    V2D_ROP2_MERGEPENNOT=13,
    V2D_ROP2_MERGEPEN   =14,
    V2D_ROP2_WHITE      =15,
    V2D_ROP2_BUTT       =16
}V2D_ROP2_MODE_E;

typedef enum SPACEMIT_V2D_COLOR_FORMAT_E
{
    V2D_COLOR_FORMAT_RGB888     =0,
    V2D_COLOR_FORMAT_RGBX8888   =1,
    V2D_COLOR_FORMAT_RGBA8888   =2,
    V2D_COLOR_FORMAT_ARGB8888   =3,
    V2D_COLOR_FORMAT_RGB565     =4,
    V2D_COLOR_FORMAT_NV12       =5,
    V2D_COLOR_FORMAT_RGBA5658   =6,
    V2D_COLOR_FORMAT_ARGB8565   =7,
    V2D_COLOR_FORMAT_A8         =8,
    V2D_COLOR_FORMAT_Y8         =9,
    V2D_COLOR_FORMAT_L8_RGBA8888=10,
    V2D_COLOR_FORMAT_L8_RGB888  =11,
    V2D_COLOR_FORMAT_L8_RGB565  =12,
    V2D_COLOR_FORMAT_BGR888     =13,
    V2D_COLOR_FORMAT_BGRX8888   =14,
    V2D_COLOR_FORMAT_BGRA8888   =15,
    V2D_COLOR_FORMAT_ABGR8888   =16,
    V2D_COLOR_FORMAT_BGR565     =17,
    V2D_COLOR_FORMAT_NV21       =18,
    V2D_COLOR_FORMAT_BGRA5658   =19,
    V2D_COLOR_FORMAT_ABGR8565   =20,
    V2D_COLOR_FORMAT_L8_BGRA8888=21,
    V2D_COLOR_FORMAT_L8_BGR888  =22,
    V2D_COLOR_FORMAT_L8_BGR565  =23,
    V2D_COLOR_FORMAT_BUTT,
}V2D_COLOR_FORMAT_E;

typedef enum SPACEMIT_V2D_CSC_MODE_E
{
    V2D_CSC_MODE_RGB_2_BT601WIDE            =0,
    V2D_CSC_MODE_BT601WIDE_2_RGB            =1,
    V2D_CSC_MODE_RGB_2_BT601NARROW          =2,
    V2D_CSC_MODE_BT601NARROW_2_RGB          =3,
    V2D_CSC_MODE_RGB_2_BT709WIDE            =4,
    V2D_CSC_MODE_BT709WIDE_2_RGB            =5,
    V2D_CSC_MODE_RGB_2_BT709NARROW          =6,
    V2D_CSC_MODE_BT709NARROW_2_RGB          =7,
    V2D_CSC_MODE_BT601WIDE_2_BT709WIDE      =8,
    V2D_CSC_MODE_BT601WIDE_2_BT709NARROW    =9,
    V2D_CSC_MODE_BT601WIDE_2_BT601NARROW    =10,
    V2D_CSC_MODE_BT601NARROW_2_BT709WIDE    =11,
    V2D_CSC_MODE_BT601NARROW_2_BT709NARROW  =12,
    V2D_CSC_MODE_BT601NARROW_2_BT601WIDE    =13,
    V2D_CSC_MODE_BT709WIDE_2_BT601WIDE      =14,
    V2D_CSC_MODE_BT709WIDE_2_BT601NARROW    =15,
    V2D_CSC_MODE_BT709WIDE_2_BT709NARROW    =16,
    V2D_CSC_MODE_BT709NARROW_2_BT601WIDE    =17,
    V2D_CSC_MODE_BT709NARROW_2_BT601NARROW  =18,
    V2D_CSC_MODE_BT709NARROW_2_BT709WIDE    =19,
    V2D_CSC_MODE_RGB_2_GREY                 =20,
    V2D_CSC_MODE_RGB_2_RGB                  =21,
    V2D_CSC_MODE_BUTT                       =22,
} V2D_CSC_MODE_E;

typedef enum SPACEMIT_FBC_DECODER_MODE_E
{
    FBC_DECODER_MODE_SCAN_LINE            =0,
    FBC_DECODER_MODE_LDC_Y                =1,
    FBC_DECODER_MODE_LDC_UV               =2,
    FBC_DECODER_MODE_H264_32x16           =3,
    FBC_DECODER_MODE_H265_32x32           =4,
    FBC_DECODER_MODE_BUTT                 =5,
} FBC_DECODER_MODE_E;

typedef enum SPACEMIT_FBC_DECODER_FORMAT_E
{
    FBC_DECODER_FORMAT_NV12               =0,
    FBC_DECODER_FORMAT_RGB888             =1,
    FBC_DECODER_FORMAT_ARGB8888           =2,
    FBC_DECODER_FORMAT_RGB565             =3,
    FBC_DECODER_FORMAT_BUTT               =4,
} FBC_DECODER_FORMAT_E;

typedef struct
{
    uint16_t x; /* left */
    uint16_t y; /* top */
    uint16_t w; /* crop width */
    uint16_t h; /* crop height */
} V2D_AREA_S;

typedef struct SPACEMIT_V2D_FILLCOLOR_S
{
    uint32_t colorvalue;
    V2D_COLOR_FORMAT_E format;
} V2D_FILLCOLOR_S;

typedef struct SPACEMIT_V2D_BACKGROUND_S
{
    V2D_FILLCOLOR_S fillcolor;
    bool enable;
} V2D_BACKGROUND_S;

typedef struct SPACEMIT_V2D_SOLIDCOLOR_S
{
    V2D_FILLCOLOR_S fillcolor;
    bool enable;
} V2D_SOLIDCOLOR_S;

typedef struct SPACEMIT_V2D_PALETTE_S
{
    uint8_t palVal[1024];
    int len;
} V2D_PALETTE_S;

typedef struct SPACEMIT_FBC_DECODER_S
{
    int fd;
    uint32_t headerAddr_h;
    uint32_t headerAddr_l;
    uint16_t bboxLeft;
    uint16_t bboxRight;
    uint16_t bboxTop;
    uint16_t bboxBottom;
    bool rgb_pack_en;
    bool is_split;
    FBC_DECODER_MODE_E   enFbcdecMode;
    FBC_DECODER_FORMAT_E enFbcdecFmt;
} FBC_DECODER_S;

typedef FBC_DECODER_FORMAT_E FBC_ENCODER_FORMAT_E;
typedef struct SPACEMIT_FBC_ENCODER_S
{
    int fd;
    int offset;
    uint32_t headerAddr_h;
    uint32_t headerAddr_l;
    uint32_t payloadAddr_h;
    uint32_t payloadAddr_l;
    uint16_t bboxLeft;
    uint16_t bboxRight;
    uint16_t bboxTop;
    uint16_t bboxBottom;
    bool is_split;
    FBC_ENCODER_FORMAT_E enFbcencFmt;
} FBC_ENCODER_S;

typedef struct SPACEMIT_V2D_SURFACE_S
{
    struct
    {
        bool fbc_enable;
        int fd;
        int offset;
        uint32_t phyaddr_y_l;
        uint32_t phyaddr_y_h;
        uint32_t phyaddr_uv_l;
        uint32_t phyaddr_uv_h;
        uint16_t w;
        uint16_t h;
        uint16_t stride;
        V2D_COLOR_FORMAT_E format;
    };
    union
    {
        FBC_DECODER_S fbcDecInfo;
        FBC_ENCODER_S fbcEncInfo;
    };
    V2D_SOLIDCOLOR_S solidcolor;
} V2D_SURFACE_S;

typedef struct
{
    V2D_BLEND_MODE_E srcColorFactor;
    V2D_BLEND_MODE_E dstColorFactor;
    V2D_BLEND_MODE_E srcAlphaFactor;
    V2D_BLEND_MODE_E dstAlphaFactor;
} V2D_BLEND_FACTOR_S;

typedef struct
{
    V2D_ROP2_MODE_E colorRop2Code;
    V2D_ROP2_MODE_E alphaRop2Code;
} V2D_ROP2_CODE_S;

typedef struct
{
    V2D_BLENDALPHA_SOURCE_E blend_alpha_source;
    V2D_BLEND_PRE_ALPHA_FUNC_E blend_pre_alpha_func;
    uint8_t global_alpha;
    union
    {
        V2D_BLEND_FACTOR_S stBlendFactor;
        V2D_ROP2_CODE_S stRop2Code;
    };
    V2D_AREA_S blend_area;
} V2D_BLEND_LAYER_CONF_S;

typedef struct
{
    V2D_BLENDCMD_E blend_cmd;
    V2D_BACKGROUND_S bgcolor;
    V2D_MASKCMD_E mask_cmd;
    V2D_AREA_S blend_mask_area;
    V2D_BLEND_LAYER_CONF_S blendlayer[V2D_INPUT_LAYER_NUM];
} V2D_BLEND_CONF_S;

typedef struct
{
    V2D_SURFACE_S layer0;
    V2D_SURFACE_S layer1;
    V2D_SURFACE_S mask;
    V2D_SURFACE_S dst;
    V2D_AREA_S l0_rect;
    V2D_AREA_S l1_rect;
    V2D_AREA_S mask_rect;
    V2D_AREA_S dst_rect;
    V2D_BLEND_CONF_S blendconf;
    V2D_ROTATE_ANGLE_E l0_rt;
    V2D_ROTATE_ANGLE_E l1_rt;
    V2D_CSC_MODE_E l0_csc;
    V2D_CSC_MODE_E l1_csc;
    V2D_DITHER_E dither;
    V2D_PALETTE_S palette;
} V2D_PARAM_S;

typedef struct 
{
    V2D_PARAM_S param;
    int32_t acquireFencefd;
    int32_t completeFencefd;
} V2D_SUBMIT_TASK_S;

typedef struct
{
    uint32_t size;
    uint64_t phys_addr;
    void *virt_addr;
} V2D_BUFFER_S;

#define V2D_IOC_MAGIC               'V'
#define V2D_SUBMIT                  _IOWR(V2D_IOC_MAGIC, 0, V2D_SUBMIT_TASK_S)
#define V2D_ALLOC_BUFFER            _IOWR(V2D_IOC_MAGIC, 1, V2D_BUFFER_S)
#define V2D_FREE_BUFFER             _IOW(V2D_IOC_MAGIC, 2, V2D_BUFFER_S)
#define V2D_RESET                   _IO(V2D_IOC_MAGIC, 3)

#endif /* __SPACEMIT_V2D_H__ */
