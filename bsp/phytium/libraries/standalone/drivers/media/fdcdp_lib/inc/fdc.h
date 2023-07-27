/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fdc.h
 * Date: 2022-09-05 22:53:24
 * LastEditTime: 2022-09-05 22:53:24
 * Description:  This file is for defining the dc config and function
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 *  1.0  Wangzq     2022/12/20   Modify the format and establish the version
 */

#ifndef FDC_H
#define FDC_H
/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fparameters.h"
#include "ferror_code.h"
#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/
#define FMEDIA_DC_SUCCESS FT_SUCCESS

#define FDC_FALSE 0
#define FDC_TRUE 1


#define FDC_GOP_MAX_MODENUM 11

#define FDC_PCCON_BUFFER_SIZE (1 * 1024 * 1024)

/**************************** Type Definitions *******************************/
typedef enum
{
    FDC_MULTI_MODE_CLONE = 0,
    FDC_MULTI_MODE_HORIZONTAL,
    FDC_MULTI_MODE_VERTICAL,

    FDC_MULTI_MODE
} FDcMultiMode;

typedef enum
{
    FDC_ROT_0 = 0,
    FDC_FLIP_X,
    FDC_FLIP_Y,
    FDC_FLIP_XY,
    FDC_ROT_90,
    FDC_ROT_180,
    FDC_ROT_270,
} FDcRotType;

typedef enum
{
    FDC_RESET_CORE = 0,
    FDC_RESET_AXI,
    FDC_RESET_AHB,
} FDcRestType;

typedef enum
{
    FDC_PHY_DPI,
    FDC_PHY_DP,
} FDcPhyOutPutType;
/*
 * Frame buffer mode.
 * Used in ConfFramebufferSetConfig()
 */
typedef enum
{
    FDC_PHY_LINEAR,
    FDC_PHY_TIILED,
} FDcPhyTilingType;

typedef enum
{
    FDC_FORMAT_X4R4G4B4 = 0x0,
    FDC_FORMAT_A4R4G4B4,
    FDC_FORMAT_X1R5G5B5,
    FDC_FORMAT_A1R5G5B5,
    FDC_FORMAT_R5G6B5,
    FDC_FORMAT_X8R8G8B8,
    FDC_FORMAT_A8R8G8B8,
    FDC_FORMAT_YUY2,
    FDC_FORMAT_UYVY,
    FDC_FORMAT_INDEX8,
    FDC_FORMAT_MONOCHROME,
    FDC_FORMAT_YV12 = 0x0F,
    FDC_FORMAT_A8,
    FDC_FORMAT_NV12,
    FDC_FORMAT_NV16,
    FDC_FORMAT_RG16,
    FDC_FORMAT_RB,
    FDC_FORMAT_NV12_10BIT,
    FDC_FORMAT_A2R10G10B10,
    FDC_FORMAT_NV16_10BIT,
    FDC_FORMAT_INDEX1,
    FDC_FORMAT_INDEX2,
    FDC_FORMAT_INDEX4,
    FDC_FORMAT_P010
} FDcVideoFormate;

typedef enum
{
    FDC_OUTPUT_RGB565 = 0,
    FDC_OUTPUT_RGB666,
    FDC_OUTPUT_RGB888,
    FDC_OUTPUT_RGB1010,
} FDcOutputColor;

typedef struct
{
    u32 instance_id;         /* dc id */
    uintptr dcch_baseaddr;   /* DC channel register address*/
    uintptr dcctrl_baseaddr; /* DC control register address */
    u32 irq_num;             /* Device intrrupt id */
} FDcConfig;

typedef struct
{
    u32 total_line;        /*  Total Number of  lines. */
    u32 visble_line;       /*  Visible Number of  lines */     
    u32 sync_start;        /* Start of  sync pulse. */
    u32 sync_end;          /* End of  sync pulse. */
    boolean sync_polarity; /* Polarity of the  sync pulse.1 - positive , 0 - negative.  */
} FDcDisplayTimmingConfig;

typedef struct
{
    FDcDisplayTimmingConfig horizontal;
    FDcDisplayTimmingConfig vertical;
    boolean timing_dirty;      /* if value is FDC_TRUE , when using the FDcCoreCommit interface, the parameters will be updated  */
} FDcSyncParameter; /* horizontal and vertical  timing parameter */

typedef struct
{
    u32 color_format;      /* color format. */
    uintptr framebuffer_p;     /* Starting address of the frame buffer. */
    u32 tiling_mode;       /* tile mode */
    u32 yuv_type;          /* unused , reserved */
    u32 stride;            /* memory image line span , --- FDcWidthToStride */
    u32 a_stride;          /* Processing is consistent with memory image line spans */
    boolean fb_dirty;      /* if value is FDC_TRUE , when using the FDcCoreCommit interface, the parameters will be updated  */
} FDcDisplayFramebuffer;

typedef struct
{
    boolean data_enable_polarity; /* Data Enable polarity , 1 - positive , 0 - negative. */
    boolean data_polarity;        /* Data polarity , 1 - positive , 0 - negative. */
    boolean clock_polarity;       /* Clock polarity , 1 - positive , 0 - negative. */
    boolean panel_dirty;          /* if value is FDC_TRUE , when using the FDcCoreCommit interface, the parameters will be updated  */
} FDcDisplayPanel;

typedef struct
{
#define gama_index_max 256
    boolean gamma_enable; /*enable the gamma*/
    u32 gamma;
    boolean gamma_dirty; /* if value is FDC_TRUE , when using the FDcCoreCommit interface, the parameters will be updated  */
} FDcDisplayGamma;

typedef struct
{
    boolean enable;
    u32 red_channel;      /* red channel of dither*/
    u32 green_channel;    /* red green of dither*/
    u32 blue_channel;     /* blue channel of dither*/
    u32 table_low;        /* the low level of dither*/
    u32 table_high;       /* the high level of dither*/
    boolean dither_dirty; /* if value is FDC_TRUE , when using the FDcCoreCommit interface, the parameters will be updated  */
} FDcDisplayDither;

typedef struct
{
    boolean outputenable;
    u32 output_type; /* Output format , 0 - DPI mode , 1 - DP mode. */

    /* dp mode */
    u32 dp_format; /* DC output color format, 0 - 565 , 1 - RGB666 , 2 - RGB888 , 3 - RGB101010. */

    /* dpi mode  */
    u32 dpi_type;          /* the dc output mode */
    u32 dpi_format;        /* DC output type , 1 - RGB666 , 2 - RGB888 , 3 - RGB101010. */
    u32 dpi_actime;        /* DC active time*/
    u32 dpi_period[2];     /*the period time of dc */
    u32 dpi_eor_assert[2]; /* params, unused*/
    u32 dpi_cs_assert[2];  /* params, unused*/
    boolean dpi_polarity;  /*the polarity of output data */
    boolean output_dirty;  /* if value is FDC_TRUE , when using the FDcCoreCommit interface, the parameters will be updated  */

} FDcDisplayDpMode;

typedef struct
{
    boolean enable;
    uintptr phys_addr;    /* Address of the cursor shape. */
    u32 type;             /* Cursor type , 0 - disable , 1 - mask mode , 2 - argb mode. */
    u32 x;                /* X location of cursor's hotspot. */
    u32 y;                /* Y location of cursor's hotspot. */
    u32 hot_x;            /* Vertical offset to cursor hotspot. */
    u32 hot_y;            /* Horizontal offset to cursor hotspot. */
    u32 bg_color;         /* The background color for Masked cursors . Format is ARGB8888. */
    u32 fg_color;         /* The foreground color for Masked cursors . Format is ARGB8888. */
    boolean cursor_dirty; /* if value is FDC_TRUE , when using the FDcCoreCommit interface, the parameters will be updated  */
} FDcDisplayCursor;

typedef struct
{
    uintptr y_address;
    uintptr u_address;
    uintptr v_address;
    u32 u_stride;
    u32 v_stride;
    u32 rot_angle;
    u32 alpha_mode;
    u32 alpha_value;
    /* Original size in pixel before rotation and scale. */
    u32 width;
    u32 height;
    u32 tile_mode;
    u32 scale;
    u32 scale_factorx;
    u32 scale_factory;
    u32 filter_tap;
    u32 horizontal_filtertap;
#define HOR_KERNEL_MAX 128
    u32 horkernel[128];
#define VER_KERNEL_MAX 128
    u32 verkernel[128];
    u32 swizzle;
    u32 uv_swizzle;
    u32 color_key;
    u32 colorkey_high;
    u32 bg_color;
    u32 trans_parency;
    u32 clear_fb;
    u32 clear_value;
    u32 initial_offsetx;
    u32 initial_offsety;
    u32 compressed;
} FDcDisplayVideoMode;

typedef struct
{
    u32 pixelclock; /* the pixelclock of dc */
    u32 horpixel;   /*horizontal pixel */
    u32 verpixel;   /*vertical pixel */
    FDcSyncParameter FDcSyncParameter;
} FDcDtdTable;

typedef enum
{
    FDC_DISPLAY_ID_640_480 = 0,
    FDC_DISPLAY_ID_800_600,
    FDC_DISPLAY_ID_1024_768,
    FDC_DISPLAY_ID_1280_720,
    FDC_DISPLAY_ID_1366_768,
    FDC_DISPLAY_ID_1920_1080,
    FDC_DISPLAY_ID_1600_1200,
    FDC_DISPLAY_ID_1280_800,
    FDC_DISPLAY_ID_800_480,
    FDC_DISPLAY_ID_1280_768,
    FDC_DISPLAY_ID_1280_1024,
    FDC_DISPLAY_ID_MAX_NUM

} FDcDisplayId;

typedef struct
{
    u32 width;
    u32 height;
    u32 color_depth;  /*  value follow the  DISPLAY_REFRESH_RATE_XX */
    u32 refresh_rate; /*  value follow the  DISPLAY_COLOR_DEPTH_XX */
    FDcDisplayId id;
} FDcDisplaySetting;

typedef struct
{
    FDcDtdTable dtd_table; /*the table of dtd params*/
    FDcSyncParameter sync_parameter[FDC_GOP_MAX_MODENUM];
    FDcDisplayFramebuffer framebuffer;
    FDcDisplayPanel panel;
    FDcDisplayGamma gamma;
    FDcDisplayDither dither;
    FDcDisplayDpMode dp_mode;
    FDcDisplayVideoMode video_mode; /*the params of video*/
    FDcDisplayCursor cursor;
    FDcDisplaySetting  display_setting[FDC_DISPLAY_ID_MAX_NUM];
} FDcCurrentConfig;

typedef struct
{
    FDcCurrentConfig fdc_current_config;
    FDcConfig config;
    u32 multi_mode; /* The display mode of the device , including clone, horizontal and vertical display*/
} FDcCtrl;

/************************** Function Prototypes ******************************/

/*Initialization of dc configuration parameter */
FError FDcConfigInit(FDcCtrl *instance_p, FDcDisplaySetting *gop_mode, u32 mode_id);

/*config the panel data of core data */
void FDcPanelSetConfig(FDcCtrl *instance_p, boolean data_enable_polarity, boolean data_polarity, boolean clock_Polarity);

/* set the horizontal timing parameter */
void FDcDisplaySetHorizontal(FDcCtrl *instance_p, u32 mode_id, u32 total_pixels, u32 line_pixels, u32 hsync_start, u32 hsync_end, boolean hsync_polarity);

/* set the vertical timing parameter */
void FDcDisplaySetVertical(FDcCtrl *instance_p, u32 mode_id, u32 line_pixels, u32 total_pixels, u32 vsync_start, u32 vsync_end, boolean vsync_polarity);

/* select core data about dc output mode , DP mode or DPI mode */
void FDcOutputSelect(FDcCtrl *instance_p, FDcPhyOutPutType output_type);

/* config core data about dc output formort , DP mode or DPI mode */
void FDcOutputDpformat(FDcCtrl *instance_p, FDcOutputColor format);

/* config tilemode and color format of vedio */
void FDcTilemodeSetConfig(FDcCtrl *instance_p, FDcVideoFormate format, FDcPhyTilingType tiling);

/* core data config about framebuffer parameter */
void FDcFramebufferSetFramebuffer(FDcCtrl *instance_p, FDcDisplayVideoMode *fdc_video_params);

/* config core data about dither enable */
void FDcDitherEnable(FDcCtrl *instance_p, boolean enable);

/* enable core data about gamma */
void FDcGammaEnable(FDcCtrl *instance_p, boolean enable);

/* config register about all dc parameters include video framebuffer  address and stride
the main function interface to set the dc parameters*/
FError FDcCoreCommit(FDcCtrl *instance_p, u32 mode_id);

/* commit display configuration about timing parameter*/
void FDcDisplayCommit(FDcCtrl *instance_p, u32 mode_id);

/* config register about dc output mode， DP or DPI */
void FDcOutputCommit(FDcCtrl *instance_p);

/* config register about panel */
void FDcPanelCommit(FDcCtrl *instance_p);

/* config register about cursor parameter */
void FDcCursorCommit(FDcCtrl *instance_p);

/* enable the cursor */
void FDcCursorEnable(FDcCtrl *instance_p, boolean enable);

/* config core data about cursor hotspot */
void FDcCursorSetHotspot(FDcCtrl *instance_p, uintptr x, uintptr y);

/* config core data about location of the cursor on the owning display */
void FDcCursorSetPos(FDcCtrl *instance_p, uintptr x, uintptr y);

/* Config register about vedio parameter and framebuffer */
void FDcFramebufferCommit(FDcCtrl *instance_p);

/* according to the width, calculate the stride */
FError FDcWidthToStride(u32 width, u32 color_depth, u32 multi_mode);

#ifdef __cplusplus
}
#endif

#endif

