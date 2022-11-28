/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __SUNXI_DISPLAY2_H__
#define __SUNXI_DISPLAY2_H__
#include <typedef.h>
#include <stdbool.h>

struct disp_manager;
struct disp_device;
struct disp_smbl;
struct disp_enhance;
struct disp_capture;

struct disp_color {
    unsigned char alpha;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

struct disp_rect {
    int x;
    int y;
    unsigned int width;
    unsigned int height;
};

struct disp_rectsz {
    unsigned int width;
    unsigned int height;
};

struct disp_position {
    int x;
    int y;
};

typedef enum disp_pixel_format {
    DISP_FORMAT_ARGB_8888 = 0x00,   /* MSB  A-R-G-B  LSB */
    DISP_FORMAT_ABGR_8888 = 0x01,
    DISP_FORMAT_RGBA_8888 = 0x02,
    DISP_FORMAT_BGRA_8888 = 0x03,
    DISP_FORMAT_XRGB_8888 = 0x04,
    DISP_FORMAT_XBGR_8888 = 0x05,
    DISP_FORMAT_RGBX_8888 = 0x06,
    DISP_FORMAT_BGRX_8888 = 0x07,
    DISP_FORMAT_RGB_888 = 0x08,
    DISP_FORMAT_BGR_888 = 0x09,
    DISP_FORMAT_RGB_565 = 0x0a,
    DISP_FORMAT_BGR_565 = 0x0b,
    DISP_FORMAT_ARGB_4444 = 0x0c,
    DISP_FORMAT_ABGR_4444 = 0x0d,
    DISP_FORMAT_RGBA_4444 = 0x0e,
    DISP_FORMAT_BGRA_4444 = 0x0f,
    DISP_FORMAT_ARGB_1555 = 0x10,
    DISP_FORMAT_ABGR_1555 = 0x11,
    DISP_FORMAT_RGBA_5551 = 0x12,
    DISP_FORMAT_BGRA_5551 = 0x13,
    DISP_FORMAT_A2R10G10B10                  = 0x14,
    DISP_FORMAT_A2B10G10R10                  = 0x15,
    DISP_FORMAT_R10G10B10A2                  = 0x16,
    DISP_FORMAT_B10G10R10A2                  = 0x17,
    DISP_FORMAT_1bpp_palette_LE              = 0x18,
    DISP_FORMAT_2bpp_palette_LE              = 0x19,
    DISP_FORMAT_4bpp_palette_LE              = 0x1a,
    DISP_FORMAT_8bpp_palette_LE              = 0x1b,
    /*
     * SP: semi-planar
     * P:planar
     * I:interleaved
     * UVUV: U in the LSBs;
     * VUVU: V in the LSBs
     */
    DISP_FORMAT_YUV444_I_AYUV = 0x40,   /* MSB  A-Y-U-V  LSB */
    DISP_FORMAT_YUV444_I_VUYA = 0x41,   /* MSB  V-U-Y-A  LSB */
    DISP_FORMAT_YUV422_I_YVYU = 0x42,   /* MSB  Y-V-Y-U  LSB */
    DISP_FORMAT_YUV422_I_YUYV = 0x43,   /* MSB  Y-U-Y-V  LSB */
    DISP_FORMAT_YUV422_I_UYVY = 0x44,   /* MSB  U-Y-V-Y  LSB */
    DISP_FORMAT_YUV422_I_VYUY = 0x45,   /* MSB  V-Y-U-Y  LSB */
    DISP_FORMAT_YUV444_P = 0x46,    /* MSB  P3-2-1-0 LSB,  YYYY UUUU VVVV */
    DISP_FORMAT_YUV422_P = 0x47,    /* MSB  P3-2-1-0 LSB   YYYY UU   VV */
    DISP_FORMAT_YUV420_P = 0x48,    /* MSB  P3-2-1-0 LSB   YYYY U    V (yu12)*/
    DISP_FORMAT_YUV411_P = 0x49,    /* MSB  P3-2-1-0 LSB   YYYY U    V */
    DISP_FORMAT_YUV422_SP_UVUV = 0x4a,  /* MSB  V-U-V-U  LSB */
    DISP_FORMAT_YUV422_SP_VUVU = 0x4b,  /* MSB  U-V-U-V  LSB */
    DISP_FORMAT_YUV420_SP_UVUV = 0x4c,
    DISP_FORMAT_YUV420_SP_VUVU = 0x4d,
    DISP_FORMAT_YUV411_SP_UVUV = 0x4e,
    DISP_FORMAT_YUV411_SP_VUVU = 0x4f,
    DISP_FORMAT_8BIT_GRAY = 0x50,
    DISP_FORMAT_YUV444_I_AYUV_10BIT          = 0x51,
    DISP_FORMAT_YUV444_I_VUYA_10BIT          = 0x52,
    DISP_FORMAT_YUV422_I_YVYU_10BIT          = 0x53,
    DISP_FORMAT_YUV422_I_YUYV_10BIT          = 0x54,
    DISP_FORMAT_YUV422_I_UYVY_10BIT          = 0x55,
    DISP_FORMAT_YUV422_I_VYUY_10BIT          = 0x56,
    DISP_FORMAT_YUV444_P_10BIT               = 0x57,
    DISP_FORMAT_YUV422_P_10BIT               = 0x58,
    DISP_FORMAT_YUV420_P_10BIT               = 0x59,
    DISP_FORMAT_YUV411_P_10BIT               = 0x5a,
    DISP_FORMAT_YUV422_SP_UVUV_10BIT         = 0x5b,
    DISP_FORMAT_YUV422_SP_VUVU_10BIT         = 0x5c,
    DISP_FORMAT_YUV420_SP_UVUV_10BIT         = 0x5d,
    DISP_FORMAT_YUV420_SP_VUVU_10BIT         = 0x5e,
    DISP_FORMAT_YUV411_SP_UVUV_10BIT         = 0x5f,
    DISP_FORMAT_YUV411_SP_VUVU_10BIT         = 0x60,
    DISP_FORMAT_YUV420_P_YV12                = 0x61,        /* MSB  P3-2-1-0 LSB   YYYY V    U DISP_FORMAT_YUV420_P */
    DISP_FORMAT_YUV420_P_YU12                = 0x62,        /* MSB  P3-2-1-0 LSB   YYYY U    V DISP_FORMAT_YUV420_P*/

    DISP_FORMAT_CSIRGB,
    DISP_UNKNOWN_VALUE,
    DISP_FORMAT_MAX,
}__disp_pixel_fmt_t;

enum disp_3d_out_mode {
    DISP_3D_OUT_MODE_CI_1 = 0x5,    /* column interlaved 1 */
    DISP_3D_OUT_MODE_CI_2 = 0x6,    /* column interlaved 2 */
    DISP_3D_OUT_MODE_CI_3 = 0x7,    /* column interlaved 3 */
    DISP_3D_OUT_MODE_CI_4 = 0x8,    /* column interlaved 4 */
    DISP_3D_OUT_MODE_LIRGB = 0x9,   /* line interleaved rgb */

    DISP_3D_OUT_MODE_TB = 0x0,  /* top bottom */
    DISP_3D_OUT_MODE_FP = 0x1,  /* frame packing */
    DISP_3D_OUT_MODE_SSF = 0x2, /* side by side full */
    DISP_3D_OUT_MODE_SSH = 0x3, /* side by side half */
    DISP_3D_OUT_MODE_LI = 0x4,  /* line interleaved */
    DISP_3D_OUT_MODE_FA = 0xa,  /* field alternative */
};

enum disp_color_space {
    DISP_UNDEF = 0x00,
    DISP_UNDEF_F = 0x01,
    DISP_GBR = 0x100,
    DISP_BT709 = 0x101,
    DISP_FCC = 0x102,
    DISP_BT470BG = 0x103,
    DISP_BT601 = 0x104,
    DISP_SMPTE240M = 0x105,
    DISP_YCGCO = 0x106,
    DISP_BT2020NC = 0x107,
    DISP_BT2020C = 0x108,
    DISP_GBR_F = 0x200,
    DISP_BT709_F = 0x201,
    DISP_FCC_F = 0x202,
    DISP_BT470BG_F = 0x203,
    DISP_BT601_F = 0x204,
    DISP_SMPTE240M_F = 0x205,
    DISP_YCGCO_F = 0x206,
    DISP_BT2020NC_F = 0x207,
    DISP_BT2020C_F = 0x208,
    DISP_RESERVED = 0x300,
    DISP_RESERVED_F = 0x301,
};

typedef enum disp_color_space __disp_cs_mode_t;

enum disp_csc_type {
    DISP_CSC_TYPE_RGB        = 0,
    DISP_CSC_TYPE_YUV444     = 1,
    DISP_CSC_TYPE_YUV422     = 2,
    DISP_CSC_TYPE_YUV420     = 3,
};

enum disp_data_bits {
    DISP_DATA_8BITS    = 0,
    DISP_DATA_10BITS   = 1,
    DISP_DATA_12BITS   = 2,
    DISP_DATA_16BITS   = 3,
};
enum disp_dvi_hdmi {
    DISP_DVI_HDMI_UNDEFINED = 0,
    DISP_DVI = 1,
    DISP_HDMI = 2,
};
enum disp_scan_info {
    DISP_SCANINFO_NO_DATA = 0,
    OVERSCAN = 1,
    UNDERSCAN = 2,
};
enum disp_color_range {
    DISP_COLOR_RANGE_DEFAULT = 0, /*default*/
    DISP_COLOR_RANGE_0_255 = 1,
    DISP_COLOR_RANGE_16_235 = 2,
};

enum disp_output_type {
    DISP_OUTPUT_TYPE_NONE = 0,
    DISP_OUTPUT_TYPE_LCD = 1,
    DISP_OUTPUT_TYPE_TV = 2,
    DISP_OUTPUT_TYPE_HDMI = 4,
    DISP_OUTPUT_TYPE_VGA = 8,
    DISP_OUTPUT_TYPE_VDPO = 16,
    DISP_OUTPUT_TYPE_EDP    = 32, /*16 for vdpo*/
};

enum disp_tv_mode {
    DISP_TV_MOD_480I = 0,
    DISP_TV_MOD_576I = 1,
    DISP_TV_MOD_480P = 2,
    DISP_TV_MOD_576P = 3,
    DISP_TV_MOD_720P_50HZ = 4,
    DISP_TV_MOD_720P_60HZ = 5,
    DISP_TV_MOD_1080I_50HZ = 6,
    DISP_TV_MOD_1080I_60HZ = 7,
    DISP_TV_MOD_1080P_24HZ = 8,
    DISP_TV_MOD_1080P_50HZ = 9,
    DISP_TV_MOD_1080P_60HZ = 0xa,
    DISP_TV_MOD_1080P_24HZ_3D_FP = 0x17,
    DISP_TV_MOD_720P_50HZ_3D_FP = 0x18,
    DISP_TV_MOD_720P_60HZ_3D_FP = 0x19,
    DISP_TV_MOD_1080P_25HZ = 0x1a,
    DISP_TV_MOD_1080P_30HZ = 0x1b,
    DISP_TV_MOD_PAL = 0xb,
    DISP_TV_MOD_PAL_SVIDEO = 0xc,
    DISP_TV_MOD_NTSC = 0xe,
    DISP_TV_MOD_NTSC_SVIDEO = 0xf,
    DISP_TV_MOD_PAL_M = 0x11,
    DISP_TV_MOD_PAL_M_SVIDEO = 0x12,
    DISP_TV_MOD_PAL_NC = 0x14,
    DISP_TV_MOD_PAL_NC_SVIDEO = 0x15,
    DISP_TV_MOD_3840_2160P_30HZ = 0x1c,
    DISP_TV_MOD_3840_2160P_25HZ = 0x1d,
    DISP_TV_MOD_3840_2160P_24HZ = 0x1e,
    DISP_TV_MOD_4096_2160P_24HZ     = 0x1f,
    DISP_TV_MOD_4096_2160P_25HZ     = 0x20,
    DISP_TV_MOD_4096_2160P_30HZ     = 0x21,
    DISP_TV_MOD_3840_2160P_60HZ     = 0x22,
    DISP_TV_MOD_4096_2160P_60HZ     = 0x23,
    DISP_TV_MOD_3840_2160P_50HZ     = 0x24,
    DISP_TV_MOD_4096_2160P_50HZ     = 0x25,
    DISP_TV_MOD_2560_1440P_60HZ     = 0x26,
    DISP_TV_MOD_1440_2560P_70HZ     = 0x27,
    DISP_TV_MOD_1080_1920P_60HZ = 0x28,
    DISP_TV_MOD_1280_1024P_60HZ     = 0x41,
    DISP_TV_MOD_1024_768P_60HZ      = 0x42,
    DISP_TV_MOD_900_540P_60HZ       = 0x43,
    DISP_TV_MOD_1920_720P_60HZ      = 0x44,
    /* vga */
    DISP_VGA_MOD_640_480P_60 = 0x50,
    DISP_VGA_MOD_800_600P_60 = 0x51,
    DISP_VGA_MOD_1024_768P_60 = 0x52,
    DISP_VGA_MOD_1280_768P_60 = 0x53,
    DISP_VGA_MOD_1280_800P_60 = 0x54,
    DISP_VGA_MOD_1366_768P_60 = 0x55,
    DISP_VGA_MOD_1440_900P_60 = 0x56,
    DISP_VGA_MOD_1920_1080P_60 = 0x57,
    DISP_VGA_MOD_1920_1200P_60 = 0x58,
    DISP_TV_MOD_3840_1080P_30 = 0x59,
    DISP_VGA_MOD_1280_720P_60        = 0x5a,
    DISP_VGA_MOD_1600_900P_60        = 0x5b,
    DISP_VGA_MOD_MAX_NUM             = 0x5c,
    DISP_TV_MODE_NUM,
};

enum disp_exit_mode {
    DISP_EXIT_MODE_CLEAN_ALL = 0,
    DISP_EXIT_MODE_CLEAN_PARTLY = 1, /* only clean interrupt temply */
};

enum disp_buffer_flags {
    DISP_BF_NORMAL = 0, /* non-stereo */
    DISP_BF_STEREO_TB = 1 << 0, /* stereo top-bottom */
    DISP_BF_STEREO_FP = 1 << 1, /* stereo frame packing */
    DISP_BF_STEREO_SSH = 1 << 2,    /* stereo side by side half */
    DISP_BF_STEREO_SSF = 1 << 3,    /* stereo side by side full */
    DISP_BF_STEREO_LI = 1 << 4, /* stereo line interlace */
    /*
     * 2d plus depth to convert into 3d,
     * left and right image using the same frame buffer
     */
    DISP_BF_STEREO_2D_DEPTH  = 1 << 5,
};

enum disp_layer_mode {
    LAYER_MODE_BUFFER = 0,
    LAYER_MODE_COLOR = 1,
};

enum disp_scan_flags {
    DISP_SCAN_PROGRESSIVE = 0,
    DISP_SCAN_INTERLACED_ODD_FLD_FIRST = 1 << 0,
    DISP_SCAN_INTERLACED_EVEN_FLD_FIRST = 1 << 1,
};

enum disp_eotf {
    DISP_EOTF_RESERVED = 0x000,
    DISP_EOTF_BT709 = 0x001,
    DISP_EOTF_UNDEF = 0x002,
    DISP_EOTF_GAMMA22 = 0x004, /* SDR */
    DISP_EOTF_GAMMA28 = 0x005,
    DISP_EOTF_BT601 = 0x006,
    DISP_EOTF_SMPTE240M = 0x007,
    DISP_EOTF_LINEAR = 0x008,
    DISP_EOTF_LOG100 = 0x009,
    DISP_EOTF_LOG100S10 = 0x00a,
    DISP_EOTF_IEC61966_2_4 = 0x00b,
    DISP_EOTF_BT1361 = 0x00c,
    DISP_EOTF_IEC61966_2_1 = 0X00d,
    DISP_EOTF_BT2020_0 = 0x00e,
    DISP_EOTF_BT2020_1 = 0x00f,
    DISP_EOTF_SMPTE2084 = 0x010, /* HDR10 */
    DISP_EOTF_SMPTE428_1 = 0x011,
    DISP_EOTF_ARIB_STD_B67 = 0x012, /* HLG */
};
/* disp_atw_mode - mode for asynchronous time warp
 *
 * @NORMAL_MODE: dual buffer, left eye and right eye buffer is individual
 * @LEFT_RIGHT_MODE: single buffer, the left half of each line buffer
 *           is for left eye, the right half is for the right eye
 * @UP_DOWN_MODE: single buffer, the first half of the total buffer
 *        is for the left eye, the second half is for the right eye
 */
enum disp_atw_mode {
    NORMAL_MODE,
    LEFT_RIGHT_MODE,
    UP_DOWN_MODE,
};
struct disp_output {
    unsigned int type;
    unsigned int mode;
};

struct disp_rect64 {
    long long x;
    long long y;
    long long width;
    long long height;
};

struct disp_lbc_info {
    unsigned int is_lossy;
    unsigned int rc_en;
    unsigned int pitch;
    unsigned int seg_bit;
};
struct disp_fb_info {
    /* address of frame buffer,
     * single addr for interleaved fomart,
     * double addr for semi-planar fomart
     * triple addr for planar format
     */
    unsigned long long addr[3];
    struct disp_rectsz size[3];
    /* align for 3 comonent,unit: bytes */
    unsigned int align[3];
    enum disp_pixel_format format;
    enum disp_color_space color_space;  /* color space */
    unsigned int trd_right_addr[3]; /* right address of 3d fb */
    bool pre_multiply;  /* true: pre-multiply fb */
    struct disp_rect64 crop;    /* crop rectangle boundaries */
    enum disp_buffer_flags flags;
    enum disp_scan_flags scan;
    unsigned int             lbc_en;
    struct disp_lbc_info     lbc_info;
};

struct disp_layer_info {
    enum disp_layer_mode mode;
    unsigned char zorder;
    /* 0: pixel alpha;  1: global alpha;  2: global pixel alpha */
    unsigned char alpha_mode;
    unsigned char alpha_value;  /* global alpha value */
    struct disp_rect screen_win;    /* display window on the screen */
    bool b_trd_out;     /* 3d display */
    enum disp_3d_out_mode out_trd_mode; /* 3d display mode */
    union {
        unsigned int color; /* valid when LAYER_MODE_COLOR */
        struct disp_fb_info fb; /* valid when LAYER_MODE_BUFFER */
    };

    unsigned int id; /* frame id, the id of frame display currently */
};

struct disp_layer_config {
    struct disp_layer_info info;
    bool enable;
    unsigned int channel;
    unsigned int layer_id;
};

/* disp_atw_info - asynchronous time wrap infomation
 *
 * @used: indicate if the atw funtion is used
 * @mode: atw mode
 * @b_row: the row number of the micro block
 * @b_col: the column number of the micro block
 * @cof_fd: dma_buf fd for the buffer contaied coefficient for atw
 */
struct disp_atw_info {
    bool used;
    enum disp_atw_mode mode;
    unsigned int b_row;
    unsigned int b_col;
    int cof_fd;
};
/**
 * disp_vdpo_config
 */
struct disp_vdpo_config {
    unsigned int data_seq_sel;
    unsigned int dclk_invt;
    unsigned int dclk_dly_num;
    unsigned int spl_type_u;
    unsigned int spl_type_v;
};
/* disp_fb_info2 - image buffer info v2
 *
 * @fd: dma_buf  fd for frame buffer
 * @size: size<width,height> for each buffer, unit:pixels
 * @align: align for each buffer, unit:bytes
 * @format: pixel format
 * @color_space: color space
 * @trd_right_fd: dma_buf fd for the right-eye frame buffer,
 *                  valid when frame-packing 3d buffer input
 * @pre_multiply: indicate the pixel use premultiplied alpha
 * @crop: crop rectangle for buffer to be display
 * @flag: indicate stereo/non-stereo buffer
 * @scan: indicate interleave/progressive scan type, and the scan order
 * @depth: depth perception for stereo image, only valid when stereo image input
 *            unit: pixel
 * @fbd_en: indicate if enable fbd function
 * @lbc_en: indicate if enable lbc function
 * @metadata_fd: dma_buf fd for the buffer contained metadata for fbc/hdr
 * @metadata_size: the size of metadata buffer, unit:bytes
 * @metadata_flag: the flag to indicate the type of metadata buffer
 *  0     : no metadata
 *  1 << 0: hdr static metadata
 *  1 << 1: hdr dynamic metadata
 *  1 << 4: frame buffer compress(fbc) metadata
 *  x     : all type could be "or" together
 */
struct disp_fb_info2 {
    int                      fd;
    struct disp_rectsz       size[3];
    unsigned int             align[3];
    enum disp_pixel_format   format;
    enum disp_color_space    color_space;
    int                      trd_right_fd;
    bool                     pre_multiply;
    struct disp_rect64       crop;
    enum disp_buffer_flags   flags;
    enum disp_scan_flags     scan;
    enum disp_eotf           eotf;
    int                      depth;
    unsigned int             fbd_en;
    unsigned int             lbc_en;
    struct disp_lbc_info     lbc_info;
    int                      metadata_fd;
    unsigned int             metadata_size;
    unsigned int             metadata_flag;
};

/* disp_layer_info2 - layer info v2
 *
 * @mode: buffer/clolor mode, when in color mode, the layer is widthout buffer
 * @zorder: the zorder of layer, 0~max-layer-number
 * @alpha_mode:
 *  0: pixel alpha;
 *  1: global alpha
 *  2: mixed alpha, compositing width pixel alpha before global alpha
 * @alpha_value: global alpha value, valid when alpha_mode is not pixel alpha
 * @screen_win: the rectangle on the screen for fb to be display
 * @b_trd_out: indicate if 3d display output
 * @out_trd_mode: 3d output mode, valid when b_trd_out is true
 * @color: the color value to be display, valid when layer is in color mode
 * @fb: the framebuffer info related width the layer, valid when in buffer mode
 * @id: frame id, the user could get the frame-id display currently by
 *  DISP_LAYER_GET_FRAME_ID ioctl
 * @atw: asynchronous time wrap information
 */
struct disp_layer_info2 {
    enum disp_layer_mode      mode;
    unsigned char             zorder;
    unsigned char             alpha_mode;
    unsigned char             alpha_value;
    struct disp_rect          screen_win;
    bool                      b_trd_out;
    enum disp_3d_out_mode     out_trd_mode;
    union {
        unsigned int            color;
        struct disp_fb_info2    fb;
    };

    unsigned int              id;
    struct disp_atw_info      atw;
};

/* disp_layer_config2 - layer config v2
 *
 * @info: layer info
 * @enable: indicate to enable/disable the layer
 * @channel: the channel index of the layer, 0~max-channel-number
 * @layer_id: the layer index of the layer widthin it's channel
 */
struct disp_layer_config2 {
    struct disp_layer_info2 info;
    bool enable;
    unsigned int channel;
    unsigned int layer_id;
};
/* disp_palette_config - palette config
 *
 * @num: the num of palette
 * @data: the palette data, each palette data takes 4 bytes,show as below
 *      bits            description
 *      31:24           alpha value
 *      23:16           red value
 *      15:8            green value
 *      7:0             blue value
 * @channel: the channel index of the layer, 0~max-channel-number
 */
struct disp_palette_config {
    unsigned int num;
    void *data;
    unsigned int channel;
};
/**
 * match rule: 0/1:always match;
 *             2:match if min<=color<=max;
 *             3:match if color>max or color<min
 */
struct disp_colorkey {
    struct disp_color ck_max;
    struct disp_color ck_min;
    unsigned int red_match_rule;
    unsigned int green_match_rule;
    unsigned int blue_match_rule;
};

struct disp_s_frame {
    enum disp_pixel_format format;
    struct disp_rectsz size[3];
    struct disp_rect crop;
    unsigned long long addr[3];
};

struct disp_capture_info {
    /* capture the whole screen if window eq ZERO */
    struct disp_rect window;
    struct disp_s_frame out_frame;
};

/* disp_s_frame2 - display simple frame buffer
 *
 * @format: pixel format of fb
 * @size: size for each plane
 * @crop: crop zone to be fill image data
 * @fd: dma_buf fd
 */
struct disp_s_frame2 {
    enum disp_pixel_format format;
    struct disp_rectsz size[3];
    struct disp_rect crop;
    int fd;
};

/* disp_capture_info2 - display capture information
 *
 * @window: the rectange on the screen to be capture
 * @out_frame: the framebuffer to be restore capture image data
 */
struct disp_capture_info2 {
    struct disp_rect window;
    struct disp_s_frame2 out_frame;
};

struct disp_capture_fmt {
    enum disp_pixel_format format;   /* write-back ouput format, doson't support YUV ouput yet */
    struct disp_rect window;         /* source crop */
    struct disp_rect crop;           /* output crop */
};

struct disp_capture_buffer {
    int handle;                      /* Unique integer id represent this buffer */
    enum disp_pixel_format format;   /* write-back ouput format */
    struct disp_rect window;         /* source crop */
    struct disp_rect crop;           /* output crop */
    struct disp_rectsz size[3];

    int fd;
    int width;                       /* buffer width  in pixels */
    int height;                      /* buffer height in pixels */
};

struct disp_capture_handle {
    int handle;    /* unique integer id represent a capture buffer */
    int fencefd;   /* fence fd for this buffer */
};

enum disp_capture_extend_cmd {
    DISP_CAPTURE_E_SET_FMT,
    DISP_CAPTURE_E_BUFFER_LIST_INIT,
    DISP_CAPTURE_E_BUFFER_LIST_CLEAR,
    DISP_CAPTURE_E_ACQUIRE_BUFFER,
    DISP_CAPTURE_E_RELEASE_BUFFER,
    DISP_CAPTURE_E_CTRL,
};

/* disp_device_config - display deivce config
 *
 * @type: output type
 * @mode: output mode
 * @format: data format
 * @bits:   data bits
 * @eotf:   electro-optical transfer function
 *      SDR  : DISP_EOTF_GAMMA22
 *      HDR10: DISP_EOTF_SMPTE2084
 *      HLG  : DISP_EOTF_ARIB_STD_B67
 * @cs:     color space type
 *      DISP_BT601: SDR for SD resolution(< 720P)
 *      DISP_BT709: SDR for HD resolution(>= 720P)
 *      DISP_BT2020NC: HDR10 or HLG or wide-color-gamut
 * @dvi_hdmi: output mode
 *        DVI: DISP_DVI
 *        HDMI: DISP_HDMI
 * @range:    RGB/YUV quantization range
 *          DEFUALT: limited range when sending a CE video format
 *                   full range when sending an IT video format
 *          LIMITED: color limited range from 16 to 235
 *          FULL: color full range from 0 to 255
 * @scan info:
 *        DISP_SCANINFO_NO_DATA: overscan if it is a CE format,
 *                               underscan if it is an IT format
 *        OVERSCAN: composed for overscan display
 *        UNDERSCAN: composed for underscan display
 * @aspect_ratio: active format aspect ratio
 */
struct disp_device_config {
    enum disp_output_type       type;
    enum disp_tv_mode           mode;
    enum disp_csc_type          format;
    enum disp_data_bits         bits;
    enum disp_eotf              eotf;
    enum disp_color_space       cs;
    enum disp_dvi_hdmi          dvi_hdmi;
    enum disp_color_range       range;
    enum disp_scan_info         scan;
    unsigned int                aspect_ratio;
    unsigned int                reserve1;
};

/* disp_device_dynamic_config - display deivce dynamic config
 *
 * @metadata_fd: dma_buf fd for the buffer contained metadata for fbc/hdr
 * @metadata_size: the size of metadata buffer, unit:bytes
 * @metadata_flag: the flag to indicate the type of metadata buffer
 *  0     : no metadata
 *  1 << 0: hdr static metadata
 *  1 << 1: hdr dynamic metadata
 *  1 << 4: frame buffer compress(fbc) metadata
 *  x     : all type could be "or" together
 * @vmap:vmap a block contigous phys memory into virtual space
 * @vunmap: release virtual mapping obtained by vmap()
 */
struct disp_device_dynamic_config {
    int          metadata_fd;
    unsigned int             metadata_size;
    unsigned int             metadata_flag;
    void *(*vmap)(unsigned long phys_addr, unsigned long size);
    void (*vunmap)(const void *vaddr);
};
struct disp_video_timings {
    unsigned int vic;   /* video information code */
    unsigned int tv_mode;
    unsigned int pixel_clk;
    unsigned int pixel_repeat; /* pixel repeat (pixel_repeat+1) times */
    unsigned int x_res;
    unsigned int y_res;
    unsigned int hor_total_time;
    unsigned int hor_back_porch;
    unsigned int hor_front_porch;
    unsigned int hor_sync_time;
    unsigned int ver_total_time;
    unsigned int ver_back_porch;
    unsigned int ver_front_porch;
    unsigned int ver_sync_time;
    unsigned int hor_sync_polarity; /* 0: negative, 1: positive */
    unsigned int ver_sync_polarity; /* 0: negative, 1: positive */
    bool b_interlace;
    unsigned int vactive_space;
    unsigned int trd_mode;
    unsigned long      dclk_rate_set; /*unit: hz */
    unsigned long long frame_period; /* unit: ns */
    int                start_delay; /* unit: line */
};

enum disp_fb_mode {
    FB_MODE_SCREEN0 = 0,
    FB_MODE_SCREEN1 = 1,
    FB_MODE_SCREEN2 = 2,
    FB_MODE_DUAL_SAME_SCREEN_TB = 3,/* two screen, top buffer for screen0, bottom buffer for screen1 */
    FB_MODE_DUAL_DIFF_SCREEN_SAME_CONTENTS = 4,/* two screen, they have same contents; */
};

struct disp_fb_create_info {
    enum disp_fb_mode fb_mode;
    enum disp_layer_mode mode;
    unsigned int buffer_num;
    unsigned int width;
    unsigned int height;

    unsigned int output_width;  /* used when scaler mode */
    unsigned int output_height; /* used when scaler mode */
};

enum disp_init_mode {
    DISP_INIT_MODE_SCREEN0 = 0, /* fb0 for screen0 */
    DISP_INIT_MODE_SCREEN1 = 1, /* fb0 for screen1 */
    DISP_INIT_MODE_SCREEN2 = 2, /* fb0 for screen1 */
    DISP_INIT_MODE_TWO_DIFF_SCREEN = 3,/* fb0 for screen0 and fb1 for screen1 */
    DISP_INIT_MODE_TWO_SAME_SCREEN = 4,/* fb0(up buffer for screen0, down buffer for screen1) */
    DISP_INIT_MODE_TWO_DIFF_SCREEN_SAME_CONTENTS = 5,/* fb0 for two different screen(screen0 layer is normal layer, screen1 layer is scaler layer); */
};

struct disp_tv_func {
    int (*tv_enable)(u32 sel);
    int (*tv_disable)(u32 sel);
    int (*tv_suspend)(u32 sel);
    int (*tv_resume)(u32 sel);
    int (*tv_get_mode)(u32 sel);
    int (*tv_set_mode)(u32 sel, enum disp_tv_mode tv_mod);
    int (*tv_get_input_csc)(u32 sel);
    int (*tv_get_video_timing_info)(u32 sel,
                     struct disp_video_timings **
                     video_info);
    int (*tv_mode_support)(u32 sel, enum disp_tv_mode mode);
    int (*tv_hot_plugging_detect)(u32 state);
    int (*tv_set_enhance_mode)(u32 sel, u32 mode);
    int (*tv_irq_enable)(u32 sel, u32 irq_id, u32 en);
    int (*tv_irq_query)(u32 sel);
    unsigned int (*tv_get_cur_line)(u32 sel);
    int (*vdpo_set_config)(u32 sel, struct disp_vdpo_config *p_cfg);
    int (*tv_get_startdelay)(u32 sel);
    void (*tv_show_builtin_patten)(u32 sel, u32 patten);
};

/* disp_vdevice_interface_para - vdevice interaface parameter
 *
 * @intf:interface
 *  0:hv, 1:cpu, 3:lvds, 4:dsi
 * @sub_intf:  sub interface
 *  rgb interface: 0:parallel hv, 8:serial hv, 10:dummy rgb
 *                     11: rgb dummy, 12: ccir656
 *  cpu interface: 0:18 pin, 10:9pin, 12:6pin, 8:16pin, 14:8pin
 *  lvds interface:0:single link, 1:dual link
 *  dsi inerafce:   0:video mode, 1:command mode, 2: video burst mode
 * @sequence:output sequence
 *  rgb output: 0:rgb rgb, 1:rgb brg, 2:rgb gbr, 4:brg rgb
 *                  5:brg brg, 6:brg gbr
 *  8:grb rgb, 9:grb brg, 10:grb gbr
 *  yuv output:0:yuyv, 1: yvyu, 2:uyvy, 3:vyuy
 * @fdelay:yuv eav/sav F line delay
 *  0: F toggle right after active video line
 *  1: delay 2 line(CCIR NTSC)
 *  2: delay 3 line(CCIR PAL)
 * @clk_phase:clk phase
 *  0: 0 degree, 1:90 degree, 2: 180 degree, 3:270 degree
 * @sync_polarity:sync signals polarity
 *  0: vsync active low,hsync active low
 *  1: vsync active high,hsync active low
 *  2: vsync active low,hsync active high
 *  3: vsync active high,hsync active high
 */
struct disp_vdevice_interface_para {
    unsigned int intf;
    unsigned int sub_intf;
    unsigned int sequence;
    unsigned int fdelay;
    unsigned int clk_phase;
    unsigned int sync_polarity;
    unsigned int ccir_clk_div;
    unsigned int input_csc;/*not need to config for user*/
};

struct disp_vdevice_source_ops {
    int (*tcon_enable)(struct disp_device *dispdev);
    int (*tcon_disable)(struct disp_device *dispdev);
    int (*tcon_simple_enable)(struct disp_device *dispdev);
    int (*tcon_simple_disable)(struct disp_device *dispdev);
};

struct disp_device_func {
    int (*enable)(void);
    int (*smooth_enable)(void);
    int (*disable)(void);
    int (*set_mode)(u32 mode);
    int (*mode_support)(u32 mode);
    int (*get_HPD_status)(void);
    int (*get_input_csc)(void);
    int (*get_input_color_range)(void);
    int (*get_video_timing_info)(struct disp_video_timings **video_info);
    int (*suspend)(void);
    int (*resume)(void);
    int (*early_suspend)(void);
    int (*late_resume)(void);
    int (*get_interface_para)(void *para);
    int (*set_static_config)(struct disp_device_config *config);
    int (*get_static_config)(struct disp_device_config *config);
    int (*set_dynamic_config)(struct disp_device_dynamic_config *config);
    int (*get_dynamic_config)(struct disp_device_dynamic_config *config);

    /*for hdmi cec*/
    s32 (*cec_standby_request)(void);
    s32 (*cec_send_one_touch_play)(void);
};

struct disp_vdevice_init_data {
    char name[32];
    u32 disp;
    u32 fix_timing;
    enum disp_output_type type;
    struct disp_device_func func;
};

enum disp_tv_dac_source {
    DISP_TV_DAC_SRC_COMPOSITE = 0,
    DISP_TV_DAC_SRC_LUMA = 1,
    DISP_TV_DAC_SRC_CHROMA = 2,
    DISP_TV_DAC_SRC_Y = 4,
    DISP_TV_DAC_SRC_PB = 5,
    DISP_TV_DAC_SRC_PR = 6,
    DISP_TV_DAC_SRC_NONE = 7,
};

enum disp_tv_output {
    DISP_TV_NONE = 0,
    DISP_TV_CVBS = 1,
    DISP_TV_YPBPR = 2,
    DISP_TV_SVIDEO = 4,
    DISP_VGA = 5,
};

enum tag_DISP_CMD {
    /* ----disp global---- */
    DISP_SYS_SHOW = 0x00,
    DISP_RESERVE1 = 0x01,
    DISP_SET_BKCOLOR = 0x03,
    DISP_GET_BKCOLOR = 0x04,
    DISP_SET_COLORKEY = 0x05,
    DISP_GET_COLORKEY = 0x06,
    DISP_GET_SCN_WIDTH = 0x07,
    DISP_GET_SCN_HEIGHT = 0x08,
    DISP_GET_OUTPUT_TYPE = 0x09,
    DISP_SET_EXIT_MODE = 0x0A,
    DISP_VSYNC_EVENT_EN = 0x0B,
    DISP_BLANK = 0x0C,
    DISP_SHADOW_PROTECT = 0x0D,
    DISP_HWC_COMMIT = 0x0E,
    DISP_DEVICE_SWITCH = 0x0F,
    DISP_GET_OUTPUT = 0x10,
    DISP_SET_COLOR_RANGE = 0x11,
    DISP_GET_COLOR_RANGE = 0x12,
    DISP_HWC_CUSTOM = 0x13,
    DISP_DEVICE_SET_CONFIG = 0x14,
    DISP_DEVICE_GET_CONFIG = 0x15,

    /* ----layer---- */
    DISP_LAYER_ENABLE = 0x40,
    DISP_LAYER_DISABLE = 0x41,
    DISP_LAYER_SET_INFO = 0x42,
    DISP_LAYER_GET_INFO = 0x43,
    DISP_LAYER_TOP = 0x44,
    DISP_LAYER_BOTTOM = 0x45,
    DISP_LAYER_GET_FRAME_ID = 0x46,
    DISP_LAYER_SET_CONFIG = 0x47,
    DISP_LAYER_GET_CONFIG = 0x48,
    /*
     * LAYER_S(G)ET_CONFIG2 takes disp_layer_config2,
     * it will support more featuras
     */
    DISP_LAYER_SET_CONFIG2 = 0x49,
    DISP_LAYER_GET_CONFIG2 = 0x4a,
    DISP_CHN_SET_PALETTE = 0x4b,
    /* ----hdmi---- */
    DISP_HDMI_SUPPORT_MODE = 0xc4,
    DISP_SET_TV_HPD = 0xc5,
    DISP_HDMI_GET_EDID = 0xc6,
    DISP_CEC_ONE_TOUCH_PLAY = 0xc7,

    /* ----lcd---- */
    DISP_LCD_ENABLE = 0x100,
    DISP_LCD_DISABLE = 0x101,
    DISP_LCD_SET_BRIGHTNESS = 0x102,
    DISP_LCD_GET_BRIGHTNESS = 0x103,
    DISP_LCD_BACKLIGHT_ENABLE = 0x104,
    DISP_LCD_BACKLIGHT_DISABLE = 0x105,
    DISP_LCD_SET_SRC = 0x106,
    DISP_LCD_SET_FPS = 0x107,
    DISP_LCD_GET_FPS = 0x108,
    DISP_LCD_GET_SIZE = 0x109,
    DISP_LCD_GET_MODEL_NAME = 0x10a,
    DISP_LCD_SET_GAMMA_TABLE = 0x10b,
    DISP_LCD_GAMMA_CORRECTION_ENABLE = 0x10c,
    DISP_LCD_GAMMA_CORRECTION_DISABLE = 0x10d,
    DISP_LCD_USER_DEFINED_FUNC = 0x10e,
    DISP_LCD_CHECK_OPEN_FINISH = 0x10f,
    DISP_LCD_CHECK_CLOSE_FINISH = 0x110,

    /*tv*/
    DISP_TV_SET_GAMMA_TABLE = 0x111,
    /* ---- capture --- */
    DISP_CAPTURE_START = 0x140,/* caputre screen and scaler to dram */
    DISP_CAPTURE_STOP = 0x141,
    DISP_CAPTURE_COMMIT = 0x142,
    DISP_CAPTURE_COMMIT2 = 0x143,
    DISP_CAPTURE_QUERY = 0x144,
    DISP_CAPTURE_EXTEND = 0x145,

    /* ---enhance --- */
    DISP_ENHANCE_ENABLE = 0x180,
    DISP_ENHANCE_DISABLE = 0x181,
    DISP_ENHANCE_GET_EN = 0x182,
    DISP_ENHANCE_SET_WINDOW = 0x183,
    DISP_ENHANCE_GET_WINDOW = 0x184,
    DISP_ENHANCE_SET_MODE = 0x185,
    DISP_ENHANCE_GET_MODE = 0x186,
    DISP_ENHANCE_DEMO_ENABLE = 0x187,
    DISP_ENHANCE_DEMO_DISABLE = 0x188,
    DISP_ENHANCE_SET_BRIGHT = 0x190,
    DISP_ENHANCE_GET_BRIGHT = 0x191,
    DISP_ENHANCE_SET_CONTRAST = 0x192,
    DISP_ENHANCE_GET_CONTRAST = 0x193,
    DISP_ENHANCE_SET_SATURATION = 0x194,
    DISP_ENHANCE_GET_SATURATION = 0x195,

    /* ---smart backlight --- */
    DISP_SMBL_ENABLE = 0x200,
    DISP_SMBL_DISABLE = 0x201,
    DISP_SMBL_GET_EN = 0x202,
    DISP_SMBL_SET_WINDOW = 0x203,
    DISP_SMBL_GET_WINDOW = 0x204,

    /* ---- for test */
    DISP_FB_REQUEST = 0x280,
    DISP_FB_RELEASE = 0x281,

    DISP_MEM_REQUEST = 0x2c0,
    DISP_MEM_RELEASE = 0x2c1,
    DISP_MEM_GETADR = 0x2c2,
    DISP_VDPO_SET_CONFIG = 0x2c3,

    /* --- rotation sw --- */
    DISP_ROTATION_SW_SET_ROT = 0x300,
    DISP_ROTATION_SW_GET_ROT = 0x301,

    DISP_EINK_UPDATE = 0x402,
    DISP_EINK_SET_TEMP = 0x403,
    DISP_EINK_GET_TEMP = 0x404,
    DISP_EINK_OVERLAP_SKIP = 0x405,
    DISP_EINK_UPDATE2 = 0x406,
};

enum {
    ROTATION_SW_0 = 0,
    ROTATION_SW_90 = 1,
    ROTATION_SW_180 = 2,
    ROTATION_SW_270 = 3,
};

#define FBIOGET_LAYER_HDL_0 0x4700
#define FBIOGET_LAYER_HDL_1 0x4701

#endif
